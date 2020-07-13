uses GraphABC,Events;
type Tarr = array[0..10,0..10]of integer;
var  i,j:integer;
     a:Tarr;
     ok,k:integer;
     
procedure Init;
var 
i,j:integer;
begin
 for i:=1 to 3 do
     for j:=1 to 3 do
       rectangle(100*i+60,100*j-40,100*i+160,100*j+60);
end;
 
function Win(var b:Tarr):integer;
var okk,i,j:integer;
Begin
   okk:= 0;
   for i:= 1 to 3 do
       for j:= 1 to 3 do
           if a[i,j]<> 0
              then inc(okk);
              
   if okk <> 9 then okk:= 0;
 
   if (b[1,1]=b[2,1])and(b[2,1]=b[3,1])and(b[1,1]=b[3,1]) then okk:= b[1,1];
   if (b[1,2]=b[2,2])and(b[2,2]=b[3,2])and(b[1,2]=b[3,2]) then okk:= b[1,2];
   if (b[1,3]=b[2,3])and(b[2,3]=b[3,3])and(b[1,3]=b[3,3]) then okk:= b[1,3];
   if (b[1,1]=b[1,2])and(b[1,2]=b[1,3])and(b[1,1]=b[1,3]) then okk:= b[1,1];
   if (b[2,1]=b[2,2])and(b[2,2]=b[2,3])and(b[2,1]=b[2,3]) then okk:= b[2,1];
   if (b[3,1]=b[3,2])and(b[3,2]=b[3,3])and(b[3,1]=b[3,3]) then okk:= b[3,1];
   if (b[1,1]=b[2,2])and(b[2,2]=b[3,3])and(b[1,1]=b[3,3]) then okk:= b[1,1];
   if (b[3,1]=b[2,2])and(b[2,2]=b[1,3])and(b[3,1]=b[1,3]) then okk:= b[3,1];
   
   win:= okk;
End;
 
function mess(okk:integer):boolean;
var yes:boolean;
begin
    yes:= false;
    
    case okk of
    
         2 : begin
              TextOut(250,25,'КРЕСТИК ВЫЙГРАЛ!!!');
              yes:= true;
         end;
 
         3 : begin
                  TextOut(250,25,'НОЛИК ВЫЙГРАЛ!!!');
                  yes:= true;
              end;
         9 : begin
                  TextOut(250,25,'ПОБЕДИЛА ДРУЖБА!!!');
                  yes:= true;  
             end;
     end;       
end;
 
procedure Nolik(x,y:integer);
Begin
   SetPenWidth(15);
   SetPencolor(clRed);
   Circle(100*x+110,100*y+10,40);
   SetPenWidth(1);
   SetPenColor(clBlack);
end;
 
procedure Krestik(x,y:integer);
Begin
   SetPenWidth(15);
   SetPenColor(clBlue);
   MoveTo(100*x+70,100*y-25);
   LineTo(100*x+150,100*y+45);
   MoveTo(100*x+150,100*y-25);
   LineTo(100*x+70,100*y+45);
   SetPenWidth(1);
   SetPenColor(clBlack);
end;
 
procedure Comp_move;
var
   i,j:integer;
begin
    for i:=1 to 9 do
        for j:= 1 to 9 do
          if a[i,j] = 0
             then begin
                      a[i,j]:= 3;
                      nolik(i,j);
                      exit;
                  end;
end;
 
procedure MouseDown(x,y,mb:integer);
begin
   x:= x-60;
   y:= y+40;
   
   x:= x div 100;
   y:= y div 100;
 
  if a[x,y] = 1 then exit;
  
  if a[x,y]>1 then exit;
  
 
                if a[x,y] = 0
                   then begin
                             krestik(x,y);
                             a[x,y]:=2;
                             if mess(win(a))
                                then halt
 
                         end;
                 if not mess(win(a))then Comp_move;
 
   
                if mess(win(a))then halt;
  
end;
 
BEGIN
 
SetWindowCaption('Крестики нолики');
SetWindowSize(600,400);
 
 ok:=1;
 k:=1;
 
 for i:=0 to 10 do
    for j:=0 to 10 do a[i,j]:=1;
 
 for i:=1 to 3 do
    for j:=1 to 3 do
       a[i,j]:=0;
 
 Init;
 
 Nolik(2,2);
 a[2,2]:=3;
  
  onMouseDown:=MouseDown;

END.