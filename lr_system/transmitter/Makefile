EXEC = socklib

$(EXEC): *.cpp
	g++ $^ -lserver -llog -lutils -std=c++17 -o $@

clean:
	rm -f $(EXEC) $(EXEC_DBG)