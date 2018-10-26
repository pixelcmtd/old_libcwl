g++ -shared -fPIC libcwlcpp/libcwlcpp.cpp -s -o _build/libcwlcpp.so
echo * Built libcwlcpp
cd libcwlcs
dotnet msbuild /nologo /m /p:Configuration=Release /p:Platform=x64 /p:OutputPath=../_build/
echo * Built libcwlcs
cd ../libcwljava/src/de/chrissx/libcwl/java
javac *.java
jar cf ../../../../../../_build/libcwljava.jar *.class
cd ../../../../../..
echo * Built libcwljava
cd libcwlrs
cargo build --release
rm ../_build/libcwlrs.rlib
cp target/release/liblibcwlrs.rlib ../_build/libcwlrs.rlib
echo * Built libcwlrs
