 #!/bin/bash
 #
 #   sudo apt install python3.8-dev
 # 
 ./bootstrap.sh --with-python-version=3.8
 ./b2 cxxflags=-fPIC link=static --stagedir=./stage