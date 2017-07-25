all:
	mkdir -p build && cd build && cmake .. && make && cd - && ./build/inihpp test.ini
clean:
	rm -rf build