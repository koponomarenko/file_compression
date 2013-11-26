
rem ** go to the current script directory
cd %~dp0

cmake .. -G"Visual Studio 10" -DCMAKE_INSTALL_PREFIX="C:\devel\installed\zlib"
msbuild /P:Configuration=Debug INSTALL.vcxproj
msbuild /P:Configuration=Release INSTALL.vcxproj
