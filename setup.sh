aclocal
autoheader
automake --force-missing --add-missing
autoconf

echo "bin directory: $PWD/bin"
./configure prefix=$PWD
make 
make install
