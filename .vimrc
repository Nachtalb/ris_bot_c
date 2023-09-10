autocmd BufWritePost main.c !cd build && make
autocmd BufWritePost CMakeLists.txt !cd build && cmake ..
