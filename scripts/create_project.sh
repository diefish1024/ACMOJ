#!/bin/bash

PROJECT_ROOT="ACMOJ"
PROBLEM_PREFIX="P"
ROOT_CMAKE_FILE="CMakeLists.txt"

if [ ! -f "$ROOT_CMAKE_FILE" ]; then
  echo "错误：未找到根 $ROOT_CMAKE_FILE。"
  echo "请在 '$PROJECT_ROOT' 目录下运行此脚本。"
  exit 1
fi

read -p "请输入题目编号: " problem_number

if [ -z "$problem_number" ]; then
  echo "错误：未输入题目编号。"
  exit 1
fi

problem_dir="${PROBLEM_PREFIX}${problem_number}"

if [ -d "$problem_dir" ]; then
  echo "错误：题目文件夹 '$problem_dir' 已存在。"
  exit 1
fi

echo "创建题目文件夹: $problem_dir ..."

mkdir "$problem_dir"
if [ $? -ne 0 ]; then
  echo "错误：创建目录 '$problem_dir' 失败。"
  exit 1
fi
cd "$problem_dir" || { echo "错误：无法进入目录 '$problem_dir'"; exit 1; }

echo "创建 main.cpp..."
touch main.cpp

echo "创建 solution/ 和 Writeup.md..."
mkdir solution
touch solution/Writeup.md

echo "创建 CMakeLists.txt..."
cat << EOF > CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(${problem_dir})
add_executable(\${PROJECT_NAME} main.cpp)
EOF

cd ..

echo "更新根 $ROOT_CMAKE_FILE ..."

subdirectory_line="add_subdirectory(${problem_dir})"
if grep -Fxq "$subdirectory_line" "$ROOT_CMAKE_FILE"; then
  echo "'$subdirectory_line' 已存在于 $ROOT_CMAKE_FILE ，无需添加。"
else
  echo "" >> "$ROOT_CMAKE_FILE"
  echo "$subdirectory_line" >> "$ROOT_CMAKE_FILE"
  echo "已将 '$subdirectory_line' 添加到 $ROOT_CMAKE_FILE"
fi

echo ""
echo "Finish."
