# Try to find cpputest
# See http://lancet.mit.edu/ga/
#
# Once run this will define: 
# 
# CppUTest_FOUND        = system has cpputest
#
# CppUTest_LIBRARIES    = full path to the libraries
# CppUTest_INCLUDE_DIR  = where to find headers 

FIND_PATH(CppUTest_INCLUDE_DIR
  NAMES
  CppUTest/Utest.h
  PATHS
  /usr/include
  /usr/local/include
  DOC "CppUTest header location"
)

#
# Find the library
#
FIND_LIBRARY(CppUTest_LIBRARY
  NAMES
  CppUTest
  PATHS
  /usr/lib
  /usr/local/lib
  /usr/lib/x86_64-linux-gnu
  DOC "CppUTest library location"
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CppUTest DEFAULT_MSG
	CppUTest_LIBRARY CppUTest_INCLUDE_DIR)

IF(CppUTest_INCLUDE_DIR AND CppUTest_LIBRARY)
	SET(CppUTest_INCLUDE_DIRS ${CppUTest_INCLUDE_DIR})
	SET(CppUTest_LIBRARIES	  ${CppUTest_LIBRARY})
ENDIF(CppUTest_INCLUDE_DIR AND CppUTest_LIBRARY)

MARK_AS_ADVANCED(CppUTest_INCLUDE_DIR)
MARK_AS_ADVANCED(CppUTest_LIBRARY)
