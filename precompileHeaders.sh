time g++-10.1 -std=c++11 -ggdb declarations/structures/*.h -o declarations/structures/*.h; echo Process returned $
echo "Precompiling constant headers"
for file in declarations/constants/*.h
do
	g++-10.1 -std=c++11 -ggdb -x c++-header "$file" -o "${file%.h}.h.gch"
	echo "$file precompiled successfully"
done
echo "Constant header files have been successfully compiled"

echo "Precompiling function headers"
for file in declarations/functions/*.h
do
	g++-10.1 -std=c++11 -ggdb -x c++-header "$file" -o "${file%.h}.h.gch"
	echo "$file precompiled successfully"
done
echo "Function header files have been successfully compiled"

echo "Precompiling structure headers"
for file in declarations/structures/*.h
do
	g++-10.1 -std=c++11 -ggdb -x c++-header "$file" -o "${file%.h}.h.gch"
	echo "$file precompiled successfully"
done
echo "Structure header files have benn successfully compiled"
