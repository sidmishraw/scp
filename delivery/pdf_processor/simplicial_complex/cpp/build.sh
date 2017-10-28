#! /bin/sh
# @Author: Wei-Chung Hunag
# @Date:   2017-05-17 23:45:08
# @Last Modified by:   Wei-Chung Hunag
# @Last Modified time: 2017-05-17 23:49:20

echo ""
echo "............................................"
echo "CS - 267 Project - Spring 2017"
echo "Author(s) - Michael, Sid, Sam, Wayne"
echo "............................................"
echo " "
echo "Building \`SimplicialComplexNewWin\`"
echo " "

dirname "$0"
cd `dirname $0`
g++ SimplicialComplexNewWin.cpp -o go

echo ""
echo "Thanks for using the tool."
echo ""