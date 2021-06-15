#include <memory>
#include <chrono>
#include <fstream>
#include "rclcpp/rclcpp.hpp"
#include <rclcpp/duration.hpp>
#include <rclcpp/clock.hpp>
#include "std_msgs/msg/string.hpp"
#include <iostream>
#include <yaml-cpp/yaml.h>
#include <bits/stdc++.h>
#include <string>
#include <dirent.h>
#include <thread>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

using namespace std;

using std::placeholders::_1;

struct order {
    int order;
    double cx;
    double cy;
    vector<struct product_part> products;
};

struct part {
    std::string part;
    double cx;
    double cy;
};

struct product_part {
    int id;
    std::string product;
    std::string part;
    double cx;
    double cy;
};

struct product {
    int id;
    std::string product;
    vector<struct part> parts;
};

vector<struct product> products;
double x_position;
double y_position;
std::string order_description = "";
int matrix_size = 0;
std::string configuration_path;
std::string orders_path;
struct order current_order;
visualization_msgs::msg::Marker rviz_marker;

class OrderOptimizer : public rclcpp::Node {
public:
    OrderOptimizer()
            : Node("OrderOptimizer") {
        subscription_1 = this->create_subscription<std_msgs::msg::String>(
                "CurrentPosition", 0, std::bind(&OrderOptimizer::current_position_callback, this, _1));
        subscription_2 = this->create_subscription<std_msgs::msg::String>(
                "NextOrder", 0, std::bind(&OrderOptimizer::next_order_callback, this, _1));
        publisher_1 = this->create_publisher<visualization_msgs::msg::MarkerArray>("order_path", 0);
    }

    void fill_marker() {
        rclcpp::Clock::SharedPtr my_time = std::make_shared<rclcpp::Clock>(RCL_ROS_TIME);

        rviz_marker.header.frame_id = "base_link";
        rviz_marker.ns = "my_knapp_namespace";
        rviz_marker.action = visualization_msgs::msg::Marker::ADD;
        rviz_marker.header.stamp = my_time->now();
        rviz_marker.lifetime = rclcpp::Duration(12345678);
        rviz_marker.pose.position.z = 0;
        rviz_marker.pose.orientation.x = 0.0;
        rviz_marker.pose.orientation.y = 0.0;
        rviz_marker.pose.orientation.z = 0.0;
        rviz_marker.pose.orientation.w = 1.0;
        rviz_marker.scale.x = 1;
        rviz_marker.scale.y = 0.1;
        rviz_marker.scale.z = 0.1;
        rviz_marker.color.a = 1.0; // Don't forget to set the alpha!
        rviz_marker.color.r = 0.0;
        rviz_marker.color.g = 1.0;
        rviz_marker.color.b = 0.0;
    }

    void fill_markers(visualization_msgs::msg::MarkerArray &marker_array, struct product_part pp_, int position) {

        rviz_marker.id = position;
        if (position + 1 == matrix_size) {
            rviz_marker.type = visualization_msgs::msg::Marker::CUBE;
        } else {
            rviz_marker.type = visualization_msgs::msg::Marker::CYLINDER;
        }
        rviz_marker.pose.position.x = pp_.cx;
        rviz_marker.pose.position.y = pp_.cy;
        marker_array.markers.push_back(rviz_marker);
    }

    // A utility function to find the vertex with minimum distance value, from
    // the set of vertices not yet included in shortest path tree
    int min_distance(double *dist, bool sptSet[], int V) {
        // Initialize min value
        int min = INT_MAX, min_index;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        return min_index;
    }

    // A utility function to print the constructed distance array
    void print_and_publish_solution(double *dist, int V, struct order order_, double **distances) {
        //ros::Publisher vis_pub = node_handle.advertise<visualization_msgs::msg::MarkerArray>( "order_path", 0 );

        visualization_msgs::msg::MarkerArray marker_array;
        fill_marker();

        std::cerr << "Working on order " << order_.order << "(" << order_description << ")" << std::endl;
        for (int i = 0; i < V - 1; i++) {
            bool found = false;
            for (int j = 0; j < V - 1; j++) {
                for (int k = 0; k < V - 1; k++) {
                    if (distances[i][j] == dist[k]) {
                        std::cerr << i + 1 << ".  Fetching " << order_.products.at(i).part << " for product "
                                  << order_.products.at(i).product << " at x: " << order_.products.at(i).cx << ", y: "
                                  << order_.products.at(i).cy << std::endl;
                        found = true;

                        fill_markers(marker_array, order_.products.at(j), i);

                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
        }
        std::cerr << V << ".  Delivering to destinatination x: " << order_.products.at(V - 1).cx << ", y: "
                  << order_.products.at(V - 1).cy << std::endl;

        fill_markers(marker_array, order_.products.at(V - 1), V - 1);

        publisher_1->publish(marker_array);
    }

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
    void dijkstra(double **graph, int src, int V, struct order order_) {
        double *dist = new double[V];// The output array.  dist[i] will hold the shortest
        // distance from src to i

        bool *sptSet = new bool[V]; // sptSet[i] will be true if vertex i is included in shortest
        // path tree or shortest distance from src to i is finalized

        // Initialize all distances as INFINITE and stpSet[] as false
        for (int i = 0; i < V; i++)
            dist[i] = INT_MAX, sptSet[i] = false;

        // Distance of source vertex from itself is always 0
        dist[src] = 0;

        // Find shortest path for all vertices
        for (int count = 0; count < V - 1; count++) {
            // Pick the minimum distance vertex from the set of vertices not
            // yet processed. u is always equal to src in the first iteration.
            int u = min_distance(dist, sptSet, V);

            // Mark the picked vertex as processed
            sptSet[u] = true;

            // Update dist value of the adjacent vertices of the picked vertex.
            for (int v = 0; v < V; v++)

                // Update dist[v] only if is not in sptSet, there is an edge from
                // u to v, and total weight of path from src to  v through u is
                // smaller than current value of dist[v]
                if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                    && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
        }

        // print the constructed distance array
    print_and_publish_solution(dist, V, order_, graph);
    }

    void fill_product_part(int id, std::string product, std::string part, double cx, double cy,
                           vector<struct product_part> &products_) {
        struct product_part product_part_;
        product_part_.id = id;
        product_part_.product = product;
        product_part_.part = part;
        product_part_.cx = cx;
        product_part_.cy = cy;
        products_.push_back(product_part_);
    }

    void read_orders(std::string config_file, int order_id) {
        std::cerr << config_file << std::endl;
        YAML::Node config = YAML::LoadFile(config_file);
        for (YAML::iterator it = config.begin(); it != config.end(); ++it) {
            const YAML::Node &orderr = *it;
            if (orderr["order"].as<int>() == order_id) {
                struct order order_;
                order_.order = orderr["order"].as<int>();
                order_.cx = orderr["cx"].as<double>();
                order_.cy = orderr["cy"].as<double>();
                const YAML::Node &this_products = orderr["products"];
                vector<int> product_ids;
                for (unsigned it2 = 0; it2 < this_products.size(); it2++) {
                    product_ids.push_back(this_products[it2].as<int>());
                }
                sort(product_ids.begin(), product_ids.end());

                unsigned it2 = 0;
                vector<struct product_part> products_;
                fill_product_part(0, "no part", "whole order", x_position, y_position, products_);
                for (auto pr:products) {
                    for (unsigned i = it2; i < this_products.size(); i++) {
                        if (pr.id == product_ids[i]) {
                            for (auto p:pr.parts) {
                                fill_product_part(pr.id, pr.product, p.part, p.cx, p.cy, products_);
                            }
                            it2++;
                            break;
                        }
                    }
                    if (it2 == this_products.size()) {
                        fill_product_part(0, "Whole package", "Goal", order_.cx, order_.cy, products_);
                        x_position = order_.cx;
                        y_position = order_.cy;
                        break;
                    }
                }

                order_.products = products_;
                current_order = order_;
                // TODO delete order from file
                break;
            }
        }
    }

    void create_distance_matrix(double **distances, struct order order_) {
        for (unsigned int i = 0; i < order_.products.size(); i++) {
            for (unsigned int j = 0; j < order_.products.size(); j++) {
                std::cerr << i << " " << j << std::endl;
                double x_distance = pow((order_.products.at(i).cx - order_.products.at(j).cx), 2);
                double y_distance = pow((order_.products.at(i).cy - order_.products.at(j).cy), 2);
                double euclidian_distance = sqrt(x_distance + y_distance);
                distances[i][j] = euclidian_distance;
            }
        }
    }

    void current_position_callback(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Current position: '%s'", msg->data.c_str());
        std::string s = msg->data.c_str();
        std::string delimiter = "|";
        x_position = stod(s.substr(0, s.find(delimiter)));
        y_position = stod(s.substr(1, s.find(delimiter)));

    }

    void next_order_callback(const std_msgs::msg::String::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "Next order: '%s'", msg->data.c_str());
        std::string s = msg->data.c_str();
        std::string delimiter = "|";
        std::string order_id_str = s.substr(0, s.find(delimiter));
        int order_id = stoi(order_id_str);
        order_description = s.substr(order_id_str.size() + delimiter.size(), s.size());

        // part with threads
        vector <std::string> order_files;
        if (auto dir = opendir(orders_path.c_str())) {
            while (auto f = readdir(dir)) {
                if (!f->d_name || f->d_name[0] == '.')
                    continue; // Skip everything that starts with a dot
                order_files.push_back(orders_path + "/" + f->d_name);

            }
            closedir(dir);
        }

        if (order_files.size() == 0) {
            std::cerr << "No YAML files found. Program will be aborted. Please give the right config directory! "
                      << std::endl;
            std::exit(1);
        }

        array<std::thread, 1> thread_objects;
        int f = 0;
        for (auto &t: thread_objects) {
            t = std::thread([=] { read_orders(order_files[f], order_id); });
            f++;
        }

        for (auto &t: thread_objects) {
            t.join();
        }

        // TODO remove order from yaml file since it will be processd / only idea

        std::cerr << "create matrix" << std::endl;
        // find all distances between order coordinates
        matrix_size = current_order.products.size();
        double **distances;
        distances = new double *[matrix_size];
        for (int i = 0; i < matrix_size; i++)
            distances[i] = new double[matrix_size];
        create_distance_matrix(distances, current_order);
        // calculate paths
        dijkstra(distances, 0, matrix_size, current_order);

        // free memory
        for (int i = 0; i < matrix_size; ++i) {
            delete[] distances[i];
        }
        delete[] distances;

        // TODO clear current_order variable
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_1;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_2;

    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr publisher_1;
};

void read_products() {
    YAML::Node config = YAML::LoadFile(configuration_path + "/products.yaml");
    for (YAML::iterator it = config.begin(); it != config.end(); ++it) {
        struct product product_;
        const YAML::Node &productt = *it;
        product_.id = productt["id"].as<int>();
        product_.product = productt["product"].as<std::string>();
        const YAML::Node &parts = productt["parts"];
        vector <part> parts_;
        for (unsigned it2 = 0; it2 < parts.size(); it2++) {
            struct part part_;
            part_.part = parts[it2]["part"].as<std::string>();
            part_.cx = parts[it2]["cx"].as<double>();
            part_.cy = parts[it2]["cy"].as<double>();
            parts_.push_back(part_);
        }
        product_.parts = parts_;
        products.push_back(product_);
    }
}

/*
 * TODO delete order from file
void delete_order(int order_id, std::string file_name)
{

}
*/
int main(int argc, char *argv[]) {
    //
    //check number of arguments
    //
    if (argc != 3) {
        std::cerr << "Usage: ros2 run order_optimizer OrderOptimizer " << std::endl;
        std::cerr << "       -p     ->     path to configuration files" << std::endl;
        return 1;
    }
    int parameters = 0;
    std::string error_message = "";
    std::string my_path;
    for (int i = 0; i < 2; i++) {
        std::string arg = argv[i];
        if (arg == "-p") {
            try {
                my_path = argv[i + 1];
                std::ifstream test(my_path);
                if (test) {
                    if (my_path[my_path.length() - 1] != '/')
                        my_path = my_path + '/';
                    std::ifstream orders_(my_path + "orders");
                    std::ifstream configuration(my_path + "configuration");
                    if ((orders_) && (configuration)) {
                        configuration_path = my_path + "configuration";
                        orders_path = my_path + "orders";
                        parameters++;
                    } else {
                        error_message = error_message +
                                        "Given not correct path. This path contains no configuration and orders folders. ";
                    }
                } else {
                    error_message = error_message + "Given path is not valid. Please add correct path. ";
                }
            }
            catch (int e) {
                error_message = error_message + "Problem with order description. Please add it correct.";
            }
        }
    }
    if (parameters != 1) {
        std::cerr << error_message << std::endl;
        std::cerr << "Usage: ros2 run order_optimizer OrderOptimizer -p <path to config files>" << std::endl;
        return 1;
    }

    read_products();

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OrderOptimizer>());
    rclcpp::shutdown();
    return 0;
}
