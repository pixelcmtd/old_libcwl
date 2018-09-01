g++ -shared libcwlcpp/libcwlcpp.cpp
cd libcwlcs
dotnet msbuild /m /p:Configuration=Release /p:Platform=x64 /p:OutputPath=../_build/
cd ../libcwljava/src/de/chrissx/libcwl/java
javac *.java
jar cf ../../../../../../_build/libcwljava.jar *.class
cd ../../../../../..
