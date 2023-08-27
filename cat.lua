-- c_argv

for i,f_name in pairs(c_argv)
do
   if i ~= 1
   then
      local file = io.open(f_name, "r")
      if file
      then
	 for l in file:lines()
	 do
	    io.output():write(l)
	    io.output():write("\n")
	 end
	 file:close()
      else
	 print("opening file " .. "'" .. f_name .. "'" .. " failed!")
      end
   end
end   
