source_dirs=( multigen cmdlib scriptlib )

for i in "${source_dirs[@]}"
do
    cppcheck --enable=all ${i}/*.{c,h}
    clang-format -i ${i}/*.{c,h}
done
