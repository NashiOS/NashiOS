TOOLS_DIR=$SOURCE_DIR/Binary/Toolchain
CACHE_DIR=$TOOLS_DIR/Cache
BUILD_DIR=$TOOLS_DIR/Build
CROSS_DIR=$TOOLS_DIR/Cross

BINUTILS_VERSION=2.39
BINUTILS_PACKAGE=binutils-$BINUTILS_VERSION
BINUTILS_ARCHIVE=$BINUTILS_PACKAGE.tar.xz

GCC_VERSION=12.2.0
GCC_PACKAGE=gcc-$GCC_VERSION
GCC_ARCHIVE=$GCC_PACKAGE.tar.xz

MIRROR=http://ftp.gnu.org/gnu
PREFIX=$CROSS_DIR
CORES=$(nproc)

mkdir -p "$CACHE_DIR"
cd "$CACHE_DIR" || exit
wget -nc $MIRROR/binutils/$BINUTILS_ARCHIVE
wget -nc $MIRROR/gcc/$GCC_PACKAGE/$GCC_ARCHIVE

mkdir -p "$BUILD_DIR"
if [ ! -d "$BUILD_DIR/$BINUTILS_PACKAGE" ];then
    cd "$BUILD_DIR" || exit
    tar -xf "$CACHE_DIR/$BINUTILS_ARCHIVE"
fi

if [ ! -d "$BUILD_DIR/$GCC_PACKAGE" ];then
    cd "$BUILD_DIR" || exit
    tar -xf "$CACHE_DIR/$GCC_ARCHIVE"
fi

mkdir -p "$BUILD_DIR/BuildBinutils"
cd "$BUILD_DIR/BuildBinutils" || exit
../$BINUTILS_PACKAGE/configure --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j "$CORES"
make install

cd "$BUILD_DIR/$GCC_PACKAGE" || exit
./contrib/download_prerequisites

mkdir -p "$BUILD_DIR/BuildGcc"
cd "$BUILD_DIR/BuildGcc" || exit
../$GCC_PACKAGE/configure --target="$TARGET" --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j "$CORES" all-gcc all-target-libgcc
make install-gcc install-target-libgcc
