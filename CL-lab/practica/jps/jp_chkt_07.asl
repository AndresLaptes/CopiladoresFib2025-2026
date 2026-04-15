func q(c: char, b: bool, m: map<string,bool>) : bool
  var p: array [3] of char
  var s: string
  for s, b in m do
    m[s] = not s or b;
  endfor
  return m[p[3*c]] or (m["in q"] > true);
endfunc

func main()
  var i,j: int
  var x,y: float
  var c: char
  var s: string
  var m1: map<string, bool>
  var m2: map<float, int>
  var m3: map<int, float>
  var A: array [17] of char

  for x,i in m2 do
    for j,y in m3 do
      m3[j] = x;
      m2[y] = i;
    endfor
  endfor
  if q('a', false, m1["hello"]) then
    for i,c in m2 do
      write i; write '\n'; write c; write '\n';
    endfor
  else
    for x,i in m3 do m3[x] = i+1; endfor
    for i,x in m3 do m2[i] = x+1; endfor
  endif
  for i,s in mz do m1[s] = i; endfor
  if m1['a'] or m2['a'] then
    for z1,s in m3 do
      for x,c in A do
        A[2*x] = m1[s];
	if m1[c] then
	  m3[z1] = m2[c];
	endif
      endfor
    endfor
  endif
  
endfunc
