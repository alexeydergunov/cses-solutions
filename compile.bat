@echo off

g++ ^
  -Wall ^
  -Wextra ^
  -pedantic ^
  -std=c++17 ^
  -O2 ^
  -Wshadow ^
  -Wformat=2 ^
  -Wfloat-equal ^
  -Wconversion ^
  -Wlogical-op ^
  -Wshift-overflow=2 ^
  -Wduplicated-cond ^
  -Wcast-qual ^
  -Wcast-align ^
  -D_GLIBCXX_DEBUG_PEDANTIC ^
  -D_FORTIFY_SOURCE=2 ^
  -fno-sanitize-recover ^
  -fstack-protector ^
  a.cpp

echo Compilation done
