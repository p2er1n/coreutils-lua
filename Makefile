bin_dir = $(shell if [ -d "./bin/" ] ; then echo "bin/" ; else mkdir "bin/" && echo "bin/" ; fi)
cat: cat.c cat.lua
	gcc -o ${bin_dir}cat cat.c -llua && cp ls.lua ${bin_dir}
echo: echo.c echo.lua
	gcc -o ${bin_dir}echo echo.c -llua && cp ls.lua ${bin_dir}
ls: ls.c ls.lua
	gcc -o ${bin_dir}ls ls.c -llua && cp ls.lua ${bin_dir}

.PHONEY: clean
clean:
	rm -rf ${bin_dir}

