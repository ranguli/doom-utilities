source_dirs=( multigen cmdlib scriplib )

for i in "${source_dirs[@]}"
do
    cppcheck --enable=all ${i}/*.{c,h}
    clang-format ${i}/*.{c,h}
done
