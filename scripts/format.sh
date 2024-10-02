echo "Formatting [.cpp/.hpp] files"
find . -name '*.cpp' -o -name '*.hpp' | xargs clang-format -i