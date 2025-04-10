mkdir $1 
mkdir $1/bin
mkdir $1/lib
mkdir $1/include
mkdir $1/include/eosim
mkdir $1/include/eosim/core
mkdir $1/include/eosim/dist
mkdir $1/include/eosim/statics
mkdir $1/include/eosim/utils
cp ./core/*.hpp $1/include/eosim/core
cp ./dist/*.hpp $1/include/eosim/dist
cp ./statics/*.hpp $1/include/eosim/statics
cp ./utils/*.hpp $1/include/eosim/utils
make -f Makefile.linux
