
#!/usr/bin/env bash

cd proj/codelite
premake4 --file=../../premake4.lua codelite

cd ../codeblocks
premake4 --file=../../premake4.lua codeblocks

cd ../..
