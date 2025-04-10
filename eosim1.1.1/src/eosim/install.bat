mkdir %1
mkdir %1\lib
mkdir %1\include
mkdir %1\include\eosim
mkdir %1\include\eosim\core
mkdir %1\include\eosim\dist
mkdir %1\include\eosim\statics
mkdir %1\include\eosim\utils
copy .\core\*.hpp %1\include\eosim\core
copy .\dist\*.hpp %1\include\eosim\dist
copy .\statics\*.hpp %1\include\eosim\statics
copy .\utils\*.hpp %1\include\eosim\utils
make -f Makefile.windows