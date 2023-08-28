for i,v in ipairs(c_argv)
do
   if i ~= 1
   then
      dir,idx = opendir(v)
      table.sort(dir)
      print(v .. " - " .. #dir .. ":")
      for k,file in ipairs(dir)
      do
	 print(file)
      end
      closedir(idx)
   end
end   
