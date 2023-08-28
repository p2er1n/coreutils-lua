cat: cat.c cat.lua
	gcc -o cat cat.c -llua
echo: echo.c echo.lua
	gcc -o echo echo.c -llua

.PHONEY: clean
clean:
	rm cat echo

