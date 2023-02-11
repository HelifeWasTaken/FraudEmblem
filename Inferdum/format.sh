find . -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \) -print0 | grep -zv "build" | xargs -0 clang-format -i -style=file
