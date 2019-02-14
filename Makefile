
CROSS_COMPILE := 
#默认使用 g++
CC=$(CROSS_COMPILE)g++

#当前工程的根目录路径
ROOT_DIR=$(shell pwd)

#.o文件存放路径, 方便清理
OBJ_DIR=$(ROOT_DIR)/obj

appname=app

#不同编译器用不同的库, 主要是 iconv 库
INC = -I$(ROOT_DIR)/inc $(shell pkg-config --cflags opencv)
LIB = $(shell pkg-config --libs --static opencv)

#把所有 src/*.cpp 转换为 obj/*.o 并添加到obj
obj =${patsubst %.cpp,$(OBJ_DIR)/%.o,${notdir ${wildcard $(ROOT_DIR)/src/*.cpp}}}

#编译所用引用到的.cpp为.o文件
%.o:../src/%.cpp
	$(CC) -O3 -Wall -c $< $(INC) $(LIB) -o $@

$(appname):$(obj)
	@$(CC) -O3 -Wall -o $(ROOT_DIR)/$@ $(obj) $(INC) $(LIB)

clean:
	@rm -rf $(ROOT_DIR)/$(appname) $(OBJ_DIR)/*.o 


