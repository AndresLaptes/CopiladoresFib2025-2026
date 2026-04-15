func q(s: string, x: int, m: map<string,bool>) : string
   var q: array[3] of string
   s = q[x];
   q[0] = "156"; 
   return q[s] or (m[s] and s > "A");
endfunc

func main()
   var i,j: int
   var s,t: string
   var m1: map<string,bool>
   var m2,m3: map<int,string>
   var A: array[17] of bool
   var B: array[17] of string
   
   m2 = q("hello", i>2, m1);
   s = i>=j or m2[j]=="bye";
   B[s] = B[ m2[j] or not m1[t] ];

   while m1[s] do
       i = 2*j - 1;
       s[3*i] = not m1["hey"];
       if "grf" then
          i = A[i*2];
       else
          t = m2[i-3.4] * 4;
       endif
       j = C[i] / 2;
       t = A[j+1] or s[i] > 3;
       s = m3[B[0]] > "A" and m1[0];
   endwhile

   j = m3[i+3.4];
   m3 = m2;   
endfunc
