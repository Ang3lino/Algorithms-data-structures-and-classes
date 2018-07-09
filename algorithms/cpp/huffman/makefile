
FILE = huff.cpp
EXTRAS = HuffNode.h MinHeap.h
EXTRAS_BIN = HuffNode.h.gch MinHeap.h.gch

build: huff.cpp 
	g++ huff.cpp ${EXTRAS} -g3 -std=c++11
	
#build: huff.cpp HuffNode.h.gch MinHeap.h.gch
#	g++ huff.cpp ${EXTRAS_BIN} -g3 -std=c++11
#HuffNode.h.gch: HuffNode.h
#	g++ -c -g3 HuffNode.h -std=c++11
#MinHeap.h.gch: MinHeap.h
#	g++ -c -g3 MinHeap.h -std=c++11