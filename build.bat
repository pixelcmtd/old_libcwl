@echo off
rem build libcwlcpp by yourself
cd libcwlcs
dotnet msbuild /nologo /m /p:Configuration=Release /p:Platform=x64 /p:OutputPath=..\_build\
echo * Built libcwlcs
rem your path needs to have your jdk/bin in it
javac ../libcwljava/src/de/chrissx/libcwl/java/*.java
javac ../libcwljava/src/SevenZip/*.java
jar cf libcwljava.jar ../libcwljava/src/de/chrissx/libcwl/java/*.class ../libcwljava/src/SevenZip/*.class
echo * Built libcwljava
cd ../libcwlrs
cargo build --release
rm ..\_build\libcwlrs.rlib
cp target\release\liblibcwlrs.rlib ..\_build\libcwlrs.rlib
echo * Built libcwlrs
