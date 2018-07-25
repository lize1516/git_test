INCLUDE=-I../lib/include
LIB=-L../lib/lib
LIB_NAME=-lmysqlclient
BIN=bin/
CUR=testCode/

.PHONY:all
all: $(BIN)net_cal $(BIN)insert $(BIN)select\
	   	$(BIN)delete $(BIN)update 

$(BIN)net_cal:$(CUR)add.c
	@gcc -o $@ $^
$(BIN)insert:$(CUR)insertData.c
	@gcc -o $@ $^ $(INCLUDE) $(LIB) $(LIB_NAME)
$(BIN)select:$(CUR)selectData.c
	@gcc -o $@ $^ $(INCLUDE) $(LIB) $(LIB_NAME)
$(BIN)delete:$(CUR)deleteData.c
	@gcc -o $@ $^ $(INCLUDE) $(LIB) $(LIB_NAME)
$(BIN)update:$(CUR)updateData.c
	@gcc -o $@ $^ $(INCLUDE) $(LIB) $(LIB_NAME)

.PHONY:clean
clean:
	rm $(BIN)net_cal $(BIN)insert $(BIN)select $(BIN)delete $(BIN)update
