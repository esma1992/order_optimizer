# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_order_optimizer_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED order_optimizer_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(order_optimizer_FOUND FALSE)
  elseif(NOT order_optimizer_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(order_optimizer_FOUND FALSE)
  endif()
  return()
endif()
set(_order_optimizer_CONFIG_INCLUDED TRUE)

# output package information
if(NOT order_optimizer_FIND_QUIETLY)
  message(STATUS "Found order_optimizer: 0.1.0 (${order_optimizer_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'order_optimizer' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${order_optimizer_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(order_optimizer_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${order_optimizer_DIR}/${_extra}")
endforeach()
