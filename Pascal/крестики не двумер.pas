program tictac;
 
uses
  GraphAbc, ABCobjects;
 
var
  mas: array[1..9] of rectangleABC;
  wx, wy, ww, wh, hod, c1, c2: integer;
  res: RectangleABC;
  finish, x_won: boolean;
 
procedure Start;
begin
  finish := false;
  //Победили ли крестики
  x_won := false;
  //Крестики всегда ходят первыми! ;)
  hod := 0;
  SetWindowCaption('Ход: Крестики');
  ww := 80;
  wh := 80;
  wx := 0;
  wy := 0;
  res := new RectangleABC(0, 237, 238, 31, clSalmon);
  res.BorderWidth := 2;
  res.Text := IntToStr(c1) + '  -  Новая игра  -  ' + IntToStr(c2);
  for var i := 1 to 9 do 
  begin
    mas[i] := new RectangleABC(wx, wy, ww, wh, clLavender);
    mas[i].BorderWidth := 2;
    wx += 79;
    if i mod 3 = 0 then begin wy += 79; wx := 0; end;
  end;
  
end;
 
//Проверяем...
procedure Prov;
var
  i: integer;
begin
  //...горизонтали,
  i := 1;
  while (i <= 9) do
  begin
    if (mas[i].Text <> '') and (mas[i].Text = mas[i + 1].Text) and (mas[i + 1].Text = mas[i + 2].Text) then
    begin
      for var j := i to i + 2 do mas[j].Color := clGreen; finish := true;
      SetPenColor(clRed);
      Line(10, 38 + wh * (i div 3), 228, 38 + wh * (i div 3));
      if mas[i].Text = 'X' then begin x_won := true; c1 += 1; end
      else c2 += 1;
      break;
    end
    else 
      i += 3;
  end;
  
  //...вертикали,  
  i := 1;
  while (i <= 3) do
  begin
    if (mas[i].Text <> '') and (mas[i].Text = mas[i + 3].Text) and (mas[i + 3].Text = mas[i + 6].Text) then
    begin
      mas[i].Color := clGreen; mas[i + 3].Color := clGreen; mas[i + 6].Color := clGreen; finish := true;
      SetPenColor(clRed);
      Line(38 + (i - 1) * ww, 10, 38 + (i - 1) * ww, 3 * wh - 10);
      if mas[i].Text = 'X' then begin x_won := true; c1 += 1 end
      else c2 += 1;
      break;
    end
    else 
      i += 1;
  end;
  
  //...диагональ слева направо,  
  if (mas[1].Text <> '') and (mas[1].Text = mas[5].Text) and (mas[5].Text = mas[9].Text) then
  begin
    mas[1].Color := clGreen; mas[5].Color := clGreen; mas[9].Color := clGreen; finish := true;
    SetPenColor(clRed);
    Line(18, 18, 2 * ww + 58, 2 * wh + 58);
    if mas[1].Text = 'X' then begin x_won := true; c1 += 1; end
    else  c2 += 1;
  end;
  //...диагональ справа налево. 
  if (mas[3].Text <> '') and (mas[3].Text = mas[5].Text) and (mas[5].Text = mas[7].Text) then
  begin
    mas[3].Color := clGreen; mas[5].Color := clGreen; mas[7].Color := clGreen; finish := true;
    SetPenColor(clRed);
    Line(18, 58 + wh * 2, 2 * ww + 58, 18);
    if mas[3].Text = 'X' then begin x_won := true; c1 += 1 end
    else c2 += 1; 
  end;
  //Если кто-то победил...  
  if finish then
  //...то нам же нужно определить победителя, не так ли? 
  begin
    if x_won then SetWindowCaption('Крестики победили!')
    else SetWindowCaption('Нолики победили!');
  end
  //А вдруг ничья?
  else
    for var j := 1 to 9 do
      if mas[j].Text <> '' then begin
        if j = 9 then begin finish := true; SetWindowCaption('Ничья!'); end;
      end
      else break;
end;
 
//Лаконично обрабатываем нажатие :)
procedure MouseDown(xm, ym, mb: integer);
begin
  if (mb = 1) then
  begin
    if finish = false then  begin
      for var i := 1 to 9 do 
        if (mas[i].PtInside(xm, ym) = true)  and (mas[i].Text = '') then
        begin
          if hod mod 2 = 0 then begin mas[i].Text := 'X'; SetWindowCaption('Ход: Нолики'); end
          else begin mas[i].Text := 'O'; SetWindowCaption('Ход: Крестики'); end;
          hod += 1;
        end;     
      Prov;
    end;
    if (res.PtInside(xm, ym) = true) then  Start;
  end;
end;
 
 
begin
  SetWindowSize(238, 268);
  //Фиксируем размер окна
  Window.IsFixedSize := true;  
  Start;
  OnMouseDown := MouseDown;    
end.