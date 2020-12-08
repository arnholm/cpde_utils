# https://freetype.org/download.html
# https://download.savannah.gnu.org/releases/freetype/
# download latest, e.g.:  freetype-2.10.4.tar.gz
# 
# extract
cd freetype-2.10.4
# 
# a) Run cmake. The cmake step is generally the same on Windows and Linux.
#
cmake -B build -D CMAKE_DISABLE_FIND_PACKAGE_ZLIB=TRUE -D CMAKE_DISABLE_FIND_PACKAGE_BZip2=TRUE -D CMAKE_DISABLE_FIND_PACKAGE_PNG=TRUE -D CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz=TRUE -D CMAKE_DISABLE_FIND_PACKAGE_BrotliDec=TRUE 
#
# b) build library
#    Windows: Use Visual studio
#    Linux  : make
