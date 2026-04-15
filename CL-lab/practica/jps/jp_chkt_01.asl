func main()
  var i,j: int
  var s1,s2: string
  var A: array[10] of string
  var B: array[10] of char
  
  s1 = s2;
  s1 = "hello";
  i = s1 * 2;
  s2 = i+1;
  s1 = 'q';
  read s2;
  if s2 == "q" then
     write s1;
     while s1 > "bye" and s1 != 'q' do
       A[s1] = s2;
       read s1;
     endwhile
  else
     A[i] = 13;
  endif
  A["13"] = 'i';
  B[j+1] = A[j+1];
  A = B;
  A[j-1] = B[j-1];
endfunc

