func addA(s : string) : string
  if s.length == 0 then
     return "null";
  else
     if s.length < 10 then
        return "1";
     else
        return 'X';
     endif
  endif
endfunc

func main()
  var i,j: int
  var s1,s2: string
  var A: array[10] of string
  var B: array[10] of char
  var c: char
  
  s1 = s1 + s2;
  s1 = s1 + 3.0;
  s1 = s1 / 3.0;
  s1 = x + s2;
  s1 = (j > 1) + 'a';
  s1 = j > 1 + 'a';
  s1 = 'b' + 'y' + 'e';
  s1 = 'b' +  y  + 'e';

  if s1 in s2 and
     'a' in s1 + addA('b') then
    write 1;
  else
    if s2 in 'b' == true then
      write 2;
    endif
    n = 'a' in s2 > c;
  endif

  if index(s2, s1) >= 0 then
     while index('a', s2) > c do
         s2 = s2 / 2;
     endwhile
  endif
  i = index(s1, 'a') - c;

  j = s2.length * s1;
  j = '3'.length + A;
  j = addA(14);

  A[j] = 'c';
  A["33"] = (A[7] + 1) * A[c];
  
endfunc

