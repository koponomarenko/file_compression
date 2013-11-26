file_compression
================
libzip-9f556511f9c9
<br />
zlib-1.2.8

----------------
**Line endings conversion:**
<br />
find /d/src/file_compression/zlib/ -type f -exec dos2unix -v --u2d "{}" \;

<br />
**Requirements:**<br />
for Windows: Visual Studio 2010, CMake 2.8


**Modifications were made to Zlib:**

To work around CMake bug which affects 64-bit Windows only
these lines were added at the end of zlib_src/CMakeLists.txt:
if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND MSVC)
    set_target_properties(zlibstatic PROPERTIES STATIC_LIBRARY_FLAGS "/machine:x64")
endif()


**Modifications were made to Libzip:**

To make static lib line in black was added at the end in file libzip_src/lib/CMakeLists.txt:
ADD_LIBRARY(zip SHARED ${LIBZIP_SOURCES} ${LIBZIP_EXTRA_FILES})
**ADD_LIBRARY(zipstatic STATIC ${LIBZIP_SOURCES} ${LIBZIP_EXTRA_FILES})**
SET_TARGET_PROPERTIES(zip PROPERTIES VERSION 3.0 SOVERSION 3 ) TARGET_LINK_LIBRARIES(zip ${ZLIB_LIBRARY})
