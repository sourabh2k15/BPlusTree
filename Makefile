OUTPUT = treesearch
INCLUDE_DIR = -Iincludes

CLASSES_DIR = classes
INCLUDE_CLASSES = $(CLASSES_DIR)/BPTree.cpp $(CLASSES_DIR)/BPTreeNodeElement.cpp $(CLASSES_DIR)/BPTreeNode.cpp 

DEPS = main.h BPTree.h BPTreeNode.h BPTreeNodeElement.h

all: treesearch

treesearch:
	g++ -std=c++14 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic $(INCLUDE_CLASSES) main.cpp $(INCLUDE_DIR) -o $(OUTPUT)

test: treesearch
	g++ tests/test1.cpp -o tests/bin/test1
	g++ tests/test2.cpp -o tests/bin/test2
	tests/bin/test1
	tests/bin/test2
clean:
	rm $(OUTPUT)
