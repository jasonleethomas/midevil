# Install script for directory: /home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/json" TYPE FILE FILES
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/version.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/reader.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/json.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/assertions.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/autolink.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/forwards.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/value.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/writer.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/config.h"
    "/home/jason/Documents/EEL4831/dev/project/libs/jsoncpp/include/json/features.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

