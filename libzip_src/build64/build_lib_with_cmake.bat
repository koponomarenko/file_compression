
rem ** go to the current script directory
cd %~dp0

cmake .. -G"Visual Studio 10 Win64" -DCMAKE_PREFIX_PATH="C:\devel\installed\zlib64" -DCMAKE_INSTALL_PREFIX="C:\devel\installed\libzip64"
msbuild /P:Configuration=Debug INSTALL.vcxproj
msbuild /P:Configuration=Release INSTALL.vcxproj
