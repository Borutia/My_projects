var
f1:text;
f2:text;
a:array[1..100] of integer;
b:array[1..100] of integer;
n,i,j,m,s,k:integer;

begin
i:=0;
assign(f1,'C:\Users\Администратор\Desktop\input.txt');
reset(f1);
readln(f1,n);

while not eof(f1) do
begin
inc(i);
  read(f1,a[i]);
  end;
m:=i;

for i:=1 to n do
b[i]:=i;

assign(f2, 'C:\Users\Администратор\Desktop\output.txt');
rewrite(f2);
for i:=1 to n do
begin
s:=0;
k:=0;
for j:=1 to m do
begin
if (b[i]<>a[j]) then 
inc(s);
if (b[i]=a[j]-1) then
inc(k);
end;

if (s=m) and (k=0)  then
begin   
write(f2, b[i],' ');   
end;

end;

close(f1);
close(f2);

end.