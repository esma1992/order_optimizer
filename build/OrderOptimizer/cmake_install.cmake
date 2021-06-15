# Install script for directory: /home/knapp/git/OrderOptimizer/src/OrderOptimizer

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/knapp/git/OrderOptimizer/install/OrderOptimizer")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/send_order" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/send_order")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/send_order"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer" TYPE EXECUTABLE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/send_order")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/send_order" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/send_order")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/send_order"
         OLD_RPATH "/home/knapp/ros2_foxy/install/rclcpp/lib:/home/knapp/ros2_foxy/install/libstatistics_collector/lib:/home/knapp/ros2_foxy/install/std_msgs/lib:/home/knapp/ros2_foxy/install/rcl/lib:/home/knapp/ros2_foxy/install/rcl_interfaces/lib:/home/knapp/ros2_foxy/install/rmw_implementation/lib:/home/knapp/ros2_foxy/install/rmw/lib:/home/knapp/ros2_foxy/install/rcl_logging_spdlog/lib:/home/knapp/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/knapp/ros2_foxy/install/libyaml_vendor/lib:/home/knapp/ros2_foxy/install/rosgraph_msgs/lib:/home/knapp/ros2_foxy/install/statistics_msgs/lib:/home/knapp/ros2_foxy/install/builtin_interfaces/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_c/lib:/home/knapp/ros2_foxy/install/rcpputils/lib:/home/knapp/ros2_foxy/install/rosidl_runtime_c/lib:/home/knapp/ros2_foxy/install/rcutils/lib:/home/knapp/ros2_foxy/install/tracetools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/send_order")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/receive_order" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/receive_order")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/receive_order"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer" TYPE EXECUTABLE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/receive_order")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/receive_order" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/receive_order")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/receive_order"
         OLD_RPATH "/home/knapp/ros2_foxy/install/rclcpp/lib:/home/knapp/ros2_foxy/install/libstatistics_collector/lib:/home/knapp/ros2_foxy/install/std_msgs/lib:/home/knapp/ros2_foxy/install/rcl/lib:/home/knapp/ros2_foxy/install/rcl_interfaces/lib:/home/knapp/ros2_foxy/install/rmw_implementation/lib:/home/knapp/ros2_foxy/install/rmw/lib:/home/knapp/ros2_foxy/install/rcl_logging_spdlog/lib:/home/knapp/ros2_foxy/install/rcl_yaml_param_parser/lib:/home/knapp/ros2_foxy/install/libyaml_vendor/lib:/home/knapp/ros2_foxy/install/rosgraph_msgs/lib:/home/knapp/ros2_foxy/install/statistics_msgs/lib:/home/knapp/ros2_foxy/install/builtin_interfaces/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_introspection_cpp/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_introspection_c/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_cpp/lib:/home/knapp/ros2_foxy/install/rosidl_typesupport_c/lib:/home/knapp/ros2_foxy/install/rcpputils/lib:/home/knapp/ros2_foxy/install/rosidl_runtime_c/lib:/home/knapp/ros2_foxy/install/rcutils/lib:/home/knapp/ros2_foxy/install/tracetools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OrderOptimizer/receive_order")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/OrderOptimizer")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/OrderOptimizer")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer/environment" TYPE FILE FILES "/home/knapp/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer/environment" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer/environment" TYPE FILE FILES "/home/knapp/ros2_foxy/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer/environment" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_index/share/ament_index/resource_index/packages/OrderOptimizer")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer/cmake" TYPE FILE FILES
    "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_core/OrderOptimizerConfig.cmake"
    "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/ament_cmake_core/OrderOptimizerConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OrderOptimizer" TYPE FILE FILES "/home/knapp/git/OrderOptimizer/src/OrderOptimizer/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/knapp/git/OrderOptimizer/build/OrderOptimizer/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
