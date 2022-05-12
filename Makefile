cc = g++
TARGET =a.out
out=*.out

$(TARGET): main.cpp
	$(cc) main.cpp -o $(TARGET)
	@echo "\nBuild completed successfully \n"

clean:
	rm $(out)
	@echo "\nClean completed successfully"
