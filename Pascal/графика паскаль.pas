// Версия Pascal 3.6.2, сборка 2361. Написано студентом ВГТУ Ломакиным Никитой (бРК-191) //
program CourseWork6point2Prerelease;

// Вызов модулей //
uses GraphWPF;

// Блок переменных //
var
  isdefault, israndom, ismanual, isfromtext: boolean; // Флаги выбора
  mainscreen, lengthscreen, randomscreen, manualscreen, resultscreen1, resultscreen2, resultscreen3, newindow, hint: boolean; // Флаги экранов
  stb, er, allowk, ar1, ar2, ar3, ar4: boolean; // Флаги строк и ошибок
  M, N, lp, up: integer; // M - строки, N - столбцы; lp, up - нижняя и верхняя граница рандома
  s1, s2: string; // Основные строковые переменные
  ms: array [,] of real; // Основной массив
  v1, v2, v3, v4: array of real; // Векторы
  r, m1, n1: real; // Радиус и эквиваленты M и N в real
  inp, out: TEXT; // Файловые переменные
  
// Блок функций //
/// Хитбоксы для кнопок // x, y - координаты курсора; x1, y1 - координаты центра кнопки; rx - ширина, rx - длина // 
function hitbox(x, y, x1, y1, rx, ry: real): boolean;
begin
  if (x > x1 - (rx / 2)) and (x < x1 + (rx / 2)) and (y > y1 - (ry / 2)) and (y < y1 + (ry / 2)) then Result := true;
end;

/// Хитбоксы для кругов // x, y - координаты курсора; x1, y1 - координаты центра кнопки; r - радиус // 
function hitcircle(x, y, x1, y1, r: real): boolean;
begin
  if r > sqrt(sqr(x1 - x) + sqr(y1 - y)) then Result := true;
end;

/// Поиск наименьшего ненулевого элемента // mass - массив, в котором ведется поиск // 
function Sotse(mass: array [,] of real): real;
begin
  Result := mass[0, 0]; // Присваиваем результату первую ячейку вектора
  for j: integer := 0 to m - 1 do 
    for i: integer := 0 to n - 1 do
      if (abs(mass[j, i]) < abs(Result)) and (mass[j, i] <> 0) then Result := mass[j, i] // Сравниваем ее с другими и записываем в результат наименьшее значение6
      else if Result = 0 then Result := mass[j, i]; 
end;

/// Возвращает ближайшее к среднему арифметическому значение элемента вектора // vector - массив, в котором ведется поиск // 
function Mav(vector: array of real): real;
var
  arth: real;
begin
  for i: integer := 0 to vector.Length - 1 do // Складываем все элементы вектора
    arth := arth + vector[i]; 
  arth := arth / vector.Length; // Делим полученное число на количество элементов вектора
  Result := vector[0]; // Записываем в результат значение нулевой ячейки вектора
  for i: integer := 0 to vector.Length - 1 do 
    if abs(Result - arth) > abs(vector[i] - arth) then Result := vector[i]; // Путем сравненияя записываем в результат ближайшее к среднему арифметическому значение элемента вектора
end;

/// Возвращает радиус отображаемой на экране ячейки вектора //
function FindRad(): real;
begin
  Result := 600 / m; // Сначала делим максимальную высоту вектора на кол-во строк
  if Result * n > 900 then Result := 900 / n; // Если суммарний радиус по горисонтали выше определенного значения (900), то записываем в него 900 / n
  if Result * m > 600 then Result := 600 / n; // Если теперь суммарний радиус по вертикали выше определенного значения (600), то записываем в него 600 / n
end;

/// Преобразует Real в Integer //
function real.ToInt(): integer;
begin
  Result := Self.ToString.ToInteger;
end;
 
/// Проверяет можно ли без ошибок конвертировать поступившее значение в integer // Возвврвщает True, если ошибок не возникло и False, если возникло //
/// k - значение, которое будет преобразовывать
function TryToK(k: key): boolean; 
var
  crunch: integer;
begin
  try
    crunch := k.ToString.ToInteger;
  except
    on System.FormatException do crunch := 10;
  end;
  if crunch = 10 then Result := false
  else Result := true;
end;

/// Проверяет можно ли без ошибок конвертировать поступившее значение в integer // Возвврвщает True, если ошибок не возникло и False, если возникло //
/// k - значение, которое будет преобразовывать
function TryToK(k: char): boolean;
var
  crunch: integer;
begin
  try
    crunch := k.ToString.ToInteger;
  except
    on System.FormatException do crunch := 10;
  end;
  if crunch = 10 then Result := false
  else Result := true;
end;

// Блок рисования кнопок и окон //
/// Рисует прямоугольные кнопкиx // x,y - координаты центра кнопки, rx - ширина, rx - длина, C1 - цвет кнопки, s - название кнопки, h - высота шрифта, C2 - цвет шрифта //
procedure makeqbutton(x, y, rx, ry: real; C1: color; s: string; h: integer; C2: color);
begin
  Pen.Color := Colors.Black;
  Font.Size := h;
  Font.Color := C2;
  rectangle(x - (rx / 2), y - (ry / 2), rx, ry, C1);
  Pen.Color := Colors.Gray;
  Line(x - (rx / 2) + 1, y - (ry / 2) + 1, x - (rx / 2) + 1, y + (ry / 2) - 1);
  Line(x - (rx / 2) + 1, y + (ry / 2) - 1, x + (rx / 2) - 1, y + (ry / 2) - 1);
  DrawText(x - (rx / 2), y - (ry / 2), rx, ry, s);
end;

/// Рисует радио-кнопки // x,y - координаты центра радио-кнопки, r - радиус, C1 - цвет кнопки, s - название кнопки, h - высота шрифта, C2 - цвет шрифта // 
procedure makerbutton(x, y, r: real; C1: color; s: string; h: integer; C2: color);
begin
  Pen.Color := Colors.Black;
  if not (h = 0) then
  begin
    Font.Size := h;
    Font.Color := C2;
    circle(x, y, r, C1);
    arc(x, y, r + (r / 5), 270, 360);
    TextOut(x + (r / 2) + 27, y - (h / 2), s);
  end
  else circle(x, y, r, C1);
end;

/// Рисует окно в окне // x,y - координаты центра кнопки, rx - ширина, rx - длина, C1 - цвет внутренней части окна, s - текст окна, h - высота шрифта, C2 - цвет шрифта, С3 - цвет внешней части окна //
procedure makenwindow(x, y, rx, ry: real; C1: color; s, s1: string; h: integer; C2, C3: color);
begin
  Pen.Color := Colors.Black;
  Font.Size := h;
  Font.Color := C2;
  rectangle(x - (rx / 2), y - (ry / 2) - 30, rx, ry + 30, C3); // Внешняя часть окна
  rectangle(x - (rx / 2), y - (ry / 2), rx, ry, C1); // Внутренняя часть окна
  DrawText(x - (rx / 2), y - (ry / 2), rx, ry, s);
  Font.Size := h / 4;
  Font.Color := colors.Beige;
  TextOut(x - (rx / 2), y - (ry / 2) - 25, s1);
  Font.Color := Colors.Black;
  newindow := true; // Флаг включенного окна
end;

/// Рисует подсказку // line - текст подсказки //
procedure TakeAHint(line: string);
begin
  Pen.Color := Colors.Black;
  Font.Color := Colors.Black;
  Font.Name := 'Courier New'; // Моноширинный шрифт, чтобы буквы подсказки не разбегались
  Font.Size := 30;
  rectangle(66, 30, 900, 630, Colors.DimGray); // Внешняя часть окна
  rectangle(66, 60, 900, 600, Colors.Beige); // Внутренняя часть окна
  for i: integer := 0 to line.Length do // Рисуем с новой строки каждые 51 символ подсказки
    for j: integer := 1 to 51 do
      if i * 51 + j < line.Length + 1 then TextOut(60 + j * 17, 70 + i * 30, line[i * 51 + j])
      else break;
  Font.Size := 20;
  Font.Color := colors.Beige;
  Font.Name := 'Default';
  TextOut(512 - (900 / 2), 360 - (600 / 2) - 25, ' ПКМ, чтобы закрыть подсказку');
  Font.Color := Colors.Black;
  newindow := true; // Флаг включенного окна
  hint := true; // Флаг включенной подсказки
end;

// Блок доп. процедур рисования //
/// Выводит на экран элементы вектора, вписанные в прямоугольник // vector - вектор, который нужно вывести; x, y - координаты центра прямойгольника; w, h - его длина и ширина //
procedure ShowVector(vector: array of real; x, y, w, h: real);
begin
  FillRectangle(x - (w / 2) - 1, y - (h / 2) - 1, w + 2, h + 2, colors.Bisque); // Очистка места под вектор
  for j: integer := 0 to n - 1 do // Рисуем кнопки с первыми двумя знаками значения ячеек вектора
    if not (Vector[j].ToString.Length = 1) then 
      makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (j * r), y, r, r, colors.Beige, Vector[j].ToString[1] + Vector[j].ToString[2], Round(r - 8), Colors.Black)
    else makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (j * r), y, r, r, colors.Beige, Vector[j].ToString[1], Round(r - 8), Colors.Black)
end;

/// Выводит на экран ближайшее к среднему арифметическому значение вектора, вписанные в прямоугольник 
/// vector - вектор, который нужно вывести; x, y - координаты центра прямойгольника; w, h - его длина и ширина; fsize - размер шрифта; l2 - строка перед значением //
procedure ShowArVector(v: array of real; x, y, w, h: real; fsize: integer; l2: string);
begin
  FillRectangle(x - (w / 2), y - (h / 2), w, h, colors.Bisque);
  makeqbutton(x, y, w, h, colors.Beige, l2 + Mav(v).ToString, fsize, Colors.Black);
end;

// Блок рисования менюшек //
/// Рисует главное меню //
procedure MainMenu();
begin
  FillRectangle(0, 0, 1400, 790, colors.Bisque); // Очистка экрана
  makerbutton(50, 100, 15, Colors.Beige, 'По умолчанию', 28, Colors.Black);
  makerbutton(50, 150, 15, Colors.Beige, 'Рандом', 28, Colors.Black);
  makerbutton(50, 200, 15, Colors.Beige, 'Вручную', 28, Colors.Black);
  makerbutton(50, 250, 15, Colors.Beige, 'Из файла', 28, Colors.Black);
  makerbutton(512, 360, 200, Colors.Beige, 'Менюшка', 0, Colors.Black);
  makeqbutton(812, 100, 200, 50, Colors.Beige, 'Задание', 44, Colors.Black); 
  Font.Size := 100;
  DrawText(312, 160, 400, 400, 'Начать'); 
  Font.Size := 42;
  DrawText(50, 25, 170, 50, 'Настройки'); 
  Font.Size := 20;
  DrawText(660, 680, 400, 30, 'Powered by Mr.Lomkins, 2020'); // :)
  // Дефолтный выбор
  isdefault := true;
  circle(50, 100, 10, Colors.Black);
end;

/// Рисует экран выбора размера массива //
procedure Screenoflength();
begin
  m := 0; // Обнуляем значения, которые будут вводиться на этом экране
  n := 0;
  stb := false; // Second TextBox выключен, т.к изначально выбрана первая строка
  FillRectangle(0, 0, 1400, 790, colors.Bisque); // Очищаем экран
  Pen.Color := Colors.Black;
  Font.Size := 46;
  TextOut(55, 35, 'Введите размер массива:');
  TextOut(55, 265, 'Кликните на строку, чтобы выбрать ее.');
  TextOut(85, 120, 'M =');
  TextOut(85, 200, 'N =');
  makeqbutton(250, 150, 140, 50, colors.Beige, ' ', 2, Colors.Black); // Первый текстбокс
  Font.Size := 48;
  TextOut(185, 119, '|');
  makeqbutton(250, 225, 140, 50, colors.Beige, ' ', 2, Colors.Black); // Второй текстбокс
  makeqbutton(900, 675, 180, 50, colors.Beige, 'Далее', 46, Colors.Black);
  makeqbutton(125, 675, 200, 50, colors.Beige, 'Помощь', 46, Colors.Black);
  Pen.Color := Colors.Black;
end;

/// Рисует экран выбора интервала значений //
procedure Screenofrandom();
begin
  lp := 0; // Обнуляем значения, которые будут вводиться на этом экране
  up := 0;
  stb := false; // Second TextBox выключен, т.к изначально выбрана первая строка
  FillRectangle(0, 0, 1400, 790, colors.Bisque); // Очищаем экран
  Pen.Color := Colors.Black;
  Font.Size := 46;
  TextOut(55, 35, 'Введите интервал значений массива:');
  TextOut(55, 265, 'Кликните на строку, чтобы выбрать ее.');
  TextOut(85, 120, 'От ');
  TextOut(85, 200, 'До ');
  makeqbutton(250, 150, 140, 50, colors.Beige, ' ', 2, Colors.Black); // Первый текстбокс
  Font.Size := 48;
  TextOut(185, 119, '|');
  makeqbutton(250, 225, 140, 50, colors.Beige, ' ', 2, Colors.Black); // Второй текстбокс
  makeqbutton(900, 675, 180, 50, colors.Beige, 'Далее', 46, Colors.Black);
  makeqbutton(125, 675, 200, 50, colors.Beige, 'Помощь', 46, Colors.Black);
  Pen.Color := Colors.Black;
  Setlength(s1, 0);
  Setlength(s2, 0);
end;

/// Рисует экран заполнения массива вручную или уже готовый массив // line1, line2 - строки названия второй и третьей кнопки
procedure Screenofmanual(line1, line2: string);
begin
  FillRectangle(0, 0, 1032, 730, colors.Bisque);
  r := FindRad; // Ищем радиус ячеек
  for i: integer := 0 to m - 1 do
    for j: integer := 0 to n - 1 do
      if ms[i, j].ToString.Length = 1 then 
        makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (j * r), r / 2 + (i * r) + (600 - (m * r)) / 2, r, r, colors.Beige, ms[i, j].ToString, Round(r - 8), Colors.Black)
      else 
        makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (j * r), r / 2 + (i * r) + (600 - (m * r)) / 2, r, r, colors.Beige, ms[i, j].ToString[1] + ms[i, j].ToString[2], Round(r - 8), Colors.Black);
  makeqbutton(125, 675, 200, 50, colors.Beige, 'Помощь', 46, Colors.Black);
  makeqbutton(512, 675, 400, 50, colors.Bisque, line1, 46, Colors.Black);
  makeqbutton(900, 675, 200, 50, colors.Beige, line2, 35, Colors.Black);
end;

/// Рисует экран с векторами//
procedure Screenofresult3();
begin
  FillRectangle(0, 0, 1032, 720, colors.Bisque);
  
  if (n < 61) and (n > 18) then // Ищем радиус
    r := 950 / n
  else r := 50;
  
  ar1 := false; // Сбрасываем флаги открытия среднего значения
  ar2 := false;
  ar3 := false;
  ar4 := false;
  
  ShowVector(v1, 516, 150, 950, 50); // Рисуем векторы
  ShowVector(v2, 516, 250, 950, 50);
  ShowVector(v3, 516, 350, 950, 50);
  ShowVector(v4, 516, 450, 950, 50);
  
  Font.Size := 40;
  Font.Color := colors.Black;
  for i: integer := 1 to 4 do
    Drawtext(516 - (950 / 2), 50 + 100 * i - (50 / 2) - 50, 950, 50, 'Вектор ' + i.ToString); // Подписываем вектора
  
  makeqbutton(125, 675, 200, 50, colors.Beige, 'Помощь', 46, Colors.Black);
  makeqbutton(512, 675, 400, 50, colors.Bisque, 'Искомые векторы', 46, Colors.Black);
  makeqbutton(900, 675, 200, 50, colors.Beige, 'Закрыть', 46, Colors.Black);
end;

// Блок управления окнами // 
/// Процедура закрытия подсказки или окна в окне // pr - процедура рисования нужного окна //
procedure unwindow(pr: procedure);
begin
  pr(); // Рисуем изначальное окно
  newindow := false; // Сбрасываем флаги 
  allowk := false;
  hint := false;
end;

/// Процедура закрытия подсказки или окна в окне // line1, line2 - названия второй и третьей кнопок //
procedure unwindowl(line1, line2: string);
begin
  Screenofmanual(line1, line2); // Рисуем изначальное окно
  newindow := false; // Сбрасываем флаги 
  allowk := false;
  hint := false;
end;

/// Процедура возвращения на главный экран с выводом ошибки // line - текст ошибки //
procedure HomeComing(line: string);
begin
  mainscreen := true; // Сбрасываем флаги 
  israndom := true;
  isfromtext := false;
  MainMenu; // Рисуем экран
  makenwindow(516, 360, 750, 75, Colors.Beige, line, ' ПКМ, чтобы закрыть это окно', 55, Colors.Black, Colors.DimGray); // Выводим ошибку
end;

// Блок вычислений //
/// Заполняет поступивший массив случайными числами // mass - массив, который нужно заполнить; lp1 - нижняя граница рандома; up1 - нижняя граница рандома //
procedure RndFill(mass: array [,] of real; lp1: integer; up1: integer);
begin
  for j: integer := 0 to m - 1 do 
    for i: integer := 0 to n - 1 do mass[j, i] := random(up1 - lp1) + lp1;
end;

/// Заполняет поступивший вектор строкой поступившего двумерного массива //
/// vector - поступивший вектор; mass - поступивший двумерный массив; VectorSize - размер вектора; line - номер строки поступившего двумерного массива //
procedure FillVector(var vector: array of real; mass: array [,] of real; VectorSize: integer; line: integer);
begin
  Setlength(vector, VectorSize);
  for i: integer := 0 to VectorSize - 1 do
    vector[i] := mass[line, i];
end;

/// Заполняет поступивший двумерный массив из файла // 
/// mass - поступивший двумерный массив; tex - файлловая переменная; m11 - переменная, куда записать кол-во строк; n11 - переменная, куда записать кол-во столбцов //
procedure TexinpV2(var mass: array [,] of real; var tex: TEXT; var m11: integer; var n11: integer);
var
  crunch: integer;
  nice: boolean;
begin
  reset(tex); // Открываем файл и заполняем из него массив (с провекой на возможные ошибки)
  repeat
    m11 += 1;
    n11 := 0;
    repeat
      n11 += 1;
      if crunch < n11 then crunch := n11;
      Setlength(mass, m11, crunch); // Устанавливаем максимальный размер массива, известный на данный момент
      try
        read(tex, mass[m11 - 1, n11 - 1]);
        if not (mass[m11 - 1, n11 - 1] = 0) then nice := true; // Флаг ошибки
      except
        on System.Exception do er := true;
      end;
    until eoln(tex);
  until eof(tex);
  close(tex);
  n11 := crunch;
  if (m11 < 4) or (n11 < 1) then HomeComing('Недостаточно строк! (M < 4)') // Проверяем на наличие ошибок и возвращаемся на главный экран, если они есть
  else
  if not nice then HomeComing('Файл пуст или полон нулей!')
  else if (m11 > 40) or (n11 > 60) then HomeComing('Слишком большой массив :(')
end;

/// Сохраняет элементы двумерного массива в файл с названием line1 //
procedure HelpToSave(line1: string);
begin
  Assign(out, line1);
  rewrite(out);
  for j: integer := 0 to m - 1 do 
  begin
    for i: integer := 0 to n - 1 do 
      write(out, ms[j, i] + ' ');
    writeln(out);
  end;
  close(out);
  makenwindow(516, 360, 750, 100, Colors.Beige, 'Cохранено в ' + line1, 'ПКМ, чтобы закрыть это окно', 60, Colors.Black, Colors.DimGray);
end;

/// Процедура сохранения векторов в файл//
procedure HelpToSaveR3();
begin
  Assign(out, 'Result3.txt');
  rewrite(out);
  for j: integer := 1 to 4 do
  begin
    writeln(out, 'Вектор ' + j.Tostring + ':');
    for i: integer := 0 to n - 1 do 
      if j = 1 then write(out, v1[i] + ' ')
      else if j = 2 then write(out, v2[i] + ' ')
      else if j = 3 then write(out, v3[i] + ' ')
      else if j = 4 then write(out, v4[i] + ' ');
    writeln(out);
    if j = 1 then writeln(out, 'Ближайшее к среднему арифметическому: ' + Mav(v1))
    else if j = 2 then writeln(out, 'Ближайшее к среднему арифметическому: ' + Mav(v2))
    else if j = 3 then writeln(out, 'Ближайшее к среднему арифметическому: ' + Mav(v3))
    else if j = 4 then writeln(out, 'Ближайшее к среднему арифметическому: ' + Mav(v4));
  end;
  close(out);
  makenwindow(516, 360, 750, 100, Colors.Beige, 'Cохранено в Result3.txt', 'ПКМ, чтобы закрыть это окно', 60, Colors.Black, Colors.DimGray);
end;

/// Процедура,вызывающая процедуры сохранения //
procedure SaveSomeResult();
begin
  if resultscreen1 or manualscreen then HelpToSave('Result1.txt');
  if resultscreen2 then HelpToSave('Result2.txt');
  if resultscreen3 then HelpToSaveR3();
end;

/// Делит каждый элемент поступившего двумерного массива на делитель // mass - поступивший двумерный массив, divider - делитель //
procedure Division(mass: array [,] of real; divider: real);
begin
  for j: integer := 0 to m - 1 do 
    for i: integer := 0 to n - 1 do mass[j, i] := mass[j, i] / divider;
end;

// Блок кнопок //
/// Обрабатывает нажатие на главную кнопку //
procedure Mainbutton();
begin
  Mainscreen := false;
  if israndom then // Рандом
  begin
    lengthscreen := true;
    Screenoflength;
  end;
  
  if ismanual then // Вручную
  begin
    lengthscreen := true;
    Screenoflength;
  end;
  
  if isfromtext then // Из текста
  begin
    Assign(inp, 'TextInput.txt');
    TexinpV2(ms, inp, m, n);
    if isfromtext then
    begin
      Screenofmanual('Исходный массив', 'Вычислить1');
      if er then 
        makenwindow(516, 360, 750, 75, Colors.Beige, 'Элементы неверного формата обнулены', ' ПКМ, чтобы закрыть это окно', 39, Colors.Black, Colors.DimGray);
      resultscreen1 := true;
    end;
  end;
  if isdefault then // Дефолт - рандом с предустановленными значениями
  begin
    m := 10;
    n := 10;
    Setlength(ms, m, n);
    RndFill(ms, -99, 99);
    resultscreen1 := true;
    Screenofmanual('Исходный массив', 'Вычислить1');
  end;
end;

/// Обрабатывает нажатие на радиокнопки // 
procedure RbHelp(b1, b2, b3, b4: boolean);
begin
  Pen.Color := Colors.Beige;
  isdefault := b1; // Устанавливаем нужные флаги
  israndom := b2;
  ismanual := b3;
  isfromtext := b4;
  if b1 then circle(50, 100, 10, colors.Black) // В зависимости от флагов "активируем" нужную радиокнопку
  else circle(50, 100, 12, colors.Beige);
  if b2 then circle(50, 150, 10, colors.Black)
  else circle(50, 150, 12, colors.Beige);
  if b3 then circle(50, 200, 10, colors.Black)
  else circle(50, 200, 12, colors.Beige);
  if b4 then circle(50, 250, 10, colors.Black)
  else circle(50, 250, 12, colors.Beige);
end;

/// Обрабатывает нажатие на первое "Далее" // 
procedure NextR();
begin
  Font.Size := 46;
  if (m < 4) or (n < 1) or (m > 40) or (n > 60) then TextOut(55, 320, 'Ошибка. 3 < M < 41, 0 < N < 61.')
  else
  if israndom then // Рандом
  begin
    stb := false; // Устранавливаем нужные флаги
    lengthscreen := false;
    randomscreen := true;
    SetLength(ms, m, n);
    Screenofrandom();
  end
  else 
  if ismanual then // Ручное заполнение
  begin
    stb := false;// Устранавливаем нужные флаги
    lengthscreen := false;
    manualscreen := true;
    SetLength(ms, m, n);
    Screenofmanual('Исходный массив', 'Вычислить1');
    Setlength(s1, 0); // Обнуляем повторно исполььзуемые строки
    Setlength(s2, 0);
  end;
end;

/// Обрабатывает нажатие на второе "Далее" // 
procedure NextR1();
begin
  if lp < up then 
  begin
    RndFill(ms, lp, up); // Заполняем массив
    resultscreen1 := true; // Устранавливаем нужные флаги
    randomscreen := false;
    Screenofmanual('Исходный массив', 'Вычислить1');
  end
  else TextOut(55, 320, 'Ошибка. "От" больше или равно "До".'); // Ошибка
end;

/// Обрабатывает нажатие на "Вычислить1" // 
procedure Compute(x, y: real);
begin
  if hitbox(x, y, 900, 675, 200, 50) then // Если попал, то
  begin
    resultscreen1 := false; // Устранавливаем нужные флаги
    manualscreen := false;
    resultscreen2 := true;
    Division(ms, Sotse(ms)); // Делим значения ячеек массива
    Screenofmanual('Искомый массив', 'Вычислить2');      
  end;
end;

/// Обрабатывает нажатие на "Вычислить2" // 
procedure Compute1(x, y: real);
begin
  if hitbox(x, y, 900, 675, 200, 50) then // Если попал, то
  begin
    resultscreen2 := false; // Устранавливаем нужные флаги
    resultscreen3 := true;
    FillVector(v1, ms, n, 0); // Заполняем векторы
    FillVector(v2, ms, n, 1);
    FillVector(v3, ms, n, 2);
    FillVector(v4, ms, n, 3);
    Screenofresult3();
  end;
end;

// Блок смешанной помощи //
/// Рисует на экране в нужном месте то, что нужно )o_o) // 
/// b - логическое значение, обычно stb; y2 - координата, где рисовать то, что нужно -_-; ss1, ss2 - то, что нужно начисовать Т_Т //
procedure HelpToHelp(var b: boolean; y2: real; var ss1, ss2: string);
begin
  b := not b; // Инвертируем логическое выражение
  makeqbutton(250, y2, 140, 50, colors.Beige, ' ', 2, Colors.Black);
  Font.Size := 48; 
  if not b then TextOut(185, 119, s1 + '|') // Рисуем то, что нужно так, как надо...
  else TextOut(185, 119, s1);
  if b then TextOut(185, 194, s2 + '|')
  else TextOut(185, 194, s2);
end;

// Блок помощи MouseDown //
/// Обработка нажатий на главном экране // x, y - координаты курсора // 
procedure MainmHelp(x, y: real);
begin
  if hitcircle(x, y, 50, 100, 15) then RbHelp(True, False, False, False); // Попадания по радио-кнопкам
  if hitcircle(x, y, 50, 150, 15) then RbHelp(False, True, False, False);
  if hitcircle(x, y, 50, 200, 15) then RbHelp(False, False, True, False);
  if hitcircle(x, y, 50, 250, 15) then RbHelp(False, False, False, True);
  if hitcircle(x, y, 512, 360, 200) then Mainbutton; // Попадание по главной кнопке
  if hitbox(x, y, 812, 100, 200, 50) then TakeAHint('Дан двухмерный массив размером M x N. Преобразовать его по правилу – разделить все элементы матрицы на элемент, наименьший по абсолютной величине. Из первых четырех строк массива сформировать четыре новых вектора (одномерные массивы). Для каждого вектора найти элемент ближайший к среднему арифметическому. Так как делить на ноль нельзя, программа будет делить элементы матрицы на наименьший "ненулевой" элемент :)');
  // ^ попадание по 'Задание'
end;

/// Обработка нажатий на экране выбора размера и интервала // mb - нажатие мыши; x, y - координаты курсора // 
procedure LenmHelp(mb: integer; x, y: real);
begin
  if hitbox(x, y, 250, 150, 140, 50) and stb and not newindow then HelpToHelp(stb, 225, s2, s1); // Попадания по текстбоксам
  if hitbox(x, y, 250, 225, 140, 50) and not stb and not newindow then HelpToHelp(stb, 150, s1, s2);
  if hitbox(x, y, 900, 675, 180, 50) and israndom and randomscreen and not newindow then NextR1(); // Попадания по "Далее"
  if hitbox(x, y, 900, 675, 180, 50) and (israndom or ismanual) and lengthscreen and not newindow then NextR();
  if hitbox(x, y, 125, 675, 200, 50) and lengthscreen then TakeAHint('На этом экране нужно ввести размер двумерного массива. Клик по строке, чтобы перейти на нее, или ENTER, чтобы перейти на следующую строку. Также ENTER перенесет Вас в следующее окно, если Вы находитесь на последней строке. M - количество строк, не должно бытьменьше 4 или больше 40. N - количество столбцов,   не должно быть равным нулю или превышать 60 :)');
  if hitbox(x, y, 125, 675, 200, 50) and randomscreen then TakeAHint('На этом экране нужно ввести интервал значений двумерного массива. Клик по строке, чтобы перейти на нее, или ENTER, чтобы перейти на следующую строку. Также ENTER перенесет Вас в следующее окно, если Вы находитесь на последней строке. Вам нужно ввести интервал значений, которые будут принимать элементы массива. Например От -100, До 100 :)');
  // ^ попадание по 'Помощь'
  if (mb = 2) and lengthscreen and newindow then unwindow(Screenoflength); // Очистка экрана по правому клику
  if (mb = 2) and randomscreen and newindow then unwindow(Screenofrandom);
end;

/// Обработка нажатий на экране ручного заполнения// x, y - координаты курсора // 
procedure ManualmHelp(x, y: real);
begin
  m1 := (y - ((600 - (m * r)) / 2)) / r; // Узнаем номер строки и столбца
  n1 := (x - ((1032 - (n * r)) / 2)) / r;
  if m1 > 0 then m1 := Trunc(m1);
  if n1 > 0 then n1 := Trunc(n1);
  
  if not ((m1 > m - 1) or (n1 > n - 1) or (m1 < 0) or (n1 < 0)) and not hint then // Если нет ошибок, выводим значение массива или | в ячейку
  begin
    if ms[m1.ToInt, n1.ToInt] = 0 then makenwindow(516, 675, 750, 100, Colors.Beige, '|', 'ПКМ, чтобы закрыть это окно. M = ' + m1 + ' N = ' + n1, 80, Colors.Black, Colors.DimGray)
    else
      makenwindow(516, 675, 750, 100, Colors.Beige, ms[m1.ToInt, n1.ToInt].ToString + '|', 'ПКМ, чтобы закрыть это окно. M = ' + m1 + ' N = ' + n1, 80, Colors.Black, Colors.DimGray);
    allowk := true;
    if ms[m1.ToInt, n1.ToInt] <> 0 then s1 := ms[m1.ToInt, n1.ToInt].ToString // Записываем значение массива в s1 или, если оно равно 0, то обнуляем s1
    else Setlength(s1, 0);
  end;
  if hitbox(x, y, 125, 675, 200, 50) then TakeAHint('На этом экране нужно заполнить массив вручную. Левый клик по ячейке массива, чтобы увеличить содержимое или записать в нее новое значение. Правый клик по "Исходный массив", чтобы сохранить результат в файл. ENTER, чтобы перейти к следующей ячейке :)');
  // ^ попадание по 'Помощь'
end;

procedure ResmHelp(x, y: real);
var
  v, h: real;
begin
  if not hint then
  begin
    v := (y - ((600 - (m * r)) / 2)) / r; // Узнаем номер строки и столбца
    h := (x - ((1032 - (n * r)) / 2)) / r;
    if v > 0 then v := Trunc(v);
    if h > 0 then h := Trunc(h);
    
    if not ((v > m - 1) or (h > n - 1) or (h < 0) or (v < 0)) then // Если нет ошибок, выводим значение массива в ячейку
      makenwindow(516, 360, 750, 100, Colors.Beige, ms[v.ToInt, h.ToInt].ToString, 'ПКМ, чтобы закрыть это окно', 80, Colors.Black, Colors.DimGray);
  end;
  if hitbox(x, y, 125, 675, 200, 50) and resultscreen1 then TakeAHint('На этом экране показан исходный массив. Левый клик по ячейке массива, чтобы увеличить содержимое. Правый клик по "Исходный массив", чтобы сохранить результат в файл :)');
  if hitbox(x, y, 125, 675, 200, 50) and resultscreen2 then TakeAHint('На этом экране показан массив, полученный делением каждой его ячейки на минимальное его значение. Минимальное значение = ' + sotse(ms).ToString + ' Левый клик по ячейке массива, чтобы увеличить содержимое. Правый клик по "Искомый массив", чтобы сохранить результат в файл :)');
  // ^ попадание по 'Помощь'
  if resultscreen1 then Compute(x, y) // Попадание по "Вычислить1"
    else
  if resultscreen2 then Compute1(x, y); // Попадание по "Вычислить2"
end;

/// Обрабатывает нажатия мыши на третьем экране результатов и вызывает рисование либо вектора, либо ближайшего к среднему арифметическому
/// v - вектор; ar - флаг нажатия на этот вектор; y - координата рисования по оси у // 
procedure Res3Help(v: array of real; var ar: boolean; y: real);
begin
  if not ar then 
  begin
    ar := not ar;
    ShowArVector(v, 516, y, 950, 50, 46, 'Ближайшее к ср. ар. = ');
  end
  else
  if ar then 
  begin
    ar := not ar;
    ShowVector(v, 516, y, 950, 50);
  end;
end;

/// Обрабатывает попадания мыши правой кнопкой на третьем экране результатов // x,y - координаты курсора //
procedure Res3mHelp(x, y: real);
begin
  if newindow then unwindow(Screenofresult3);
  
  if not ar1 and hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 150, r * n, r) and not hint then Res3Help(v1, ar1, 150) // Попадания
  else
  if ar1 and hitbox(x, y, 516, 150, 950, 50) and not hint then Res3Help(v1, ar1, 150);
  if not ar2 and hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 250, r * n, r) and not hint then Res3Help(v2, ar2, 250)
  else
  if ar2 and hitbox(x, y, 516, 250, 950, 50) and not hint then Res3Help(v2, ar2, 250);
  if not ar3 and hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 350, r * n, r) and not hint then Res3Help(v3, ar3, 350)
  else
  if ar3 and hitbox(x, y, 516, 350, 950, 50) and not hint then Res3Help(v3, ar3, 350);
  if not ar4 and hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 450, r * n, r) and not hint then Res3Help(v4, ar4, 450)
  else
  if ar4 and hitbox(x, y, 516, 450, 950, 50) and not hint then Res3Help(v4, ar4, 450);
end;

/// Обрабатывает попадания мыши левой кнопкой на третьем экране результатов // x,y - координаты курсора //
procedure Res3mHelp1(x, y: real);
var
  h: integer;
  lin: integer;
begin
  if hitbox(x, y, 900, 675, 200, 50) then Window.Close(); // Попадание по "Закрыть"
  if hitbox(x, y, 125, 675, 200, 50) then TakeAHint('На этом экране показаны 4 вектора, полученные из первых 4х строк массива. Левый клик по ячейке вектора, чтобы увеличить содержимое. Правый клик по вектору, чтобы посмотреть среднее арифметическое его элементов. Правый клик по "Искомые векторы", чтобы сохранить результат в файл :)');
  // ^ Попадание по помощи
  if hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 150, r * n, r) and not ar1 and not hint then lin := 1; // Попадания по ячейке массива леой кнопкой мыши
  if hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 250, r * n, r) and not ar2 and not hint then lin := 2;
  if hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 350, r * n, r) and not ar3 and not hint then lin := 3;
  if hitbox(x, y, (1032 - (n * r)) / 2  + (n * r / 2), 450, r * n, r) and not ar4 and not hint then lin := 4;
  if lin > 0 then
  begin
    h := Trunc((x - ((1032 - (n * r)) / 2)) / r);
    if lin = 1 then 
      makenwindow(516, 360, 750, 100, Colors.Beige, v1[h].ToString, 'ПКМ, чтобы закрыть это окно', 80, Colors.Black, Colors.DimGray);
    if lin = 2 then 
      makenwindow(516, 360, 750, 100, Colors.Beige, v2[h].ToString, 'ПКМ, чтобы закрыть это окно', 80, Colors.Black, Colors.DimGray);
    if lin = 3 then 
      makenwindow(516, 360, 750, 100, Colors.Beige, v3[h].ToString, 'ПКМ, чтобы закрыть это окно', 80, Colors.Black, Colors.DimGray);
    if lin = 4 then 
      makenwindow(516, 360, 750, 100, Colors.Beige, v4[h].ToString, 'ПКМ, чтобы закрыть это окно', 80, Colors.Black, Colors.DimGray);
    newindow := true;
  end;
end;

/// Вызывает Compute, если ms не пуст // x, y - координаты курсора //
procedure ComputemHelp(x, y: real);
begin
  if hitbox(x, y, 900, 675, 200, 50) then
    for i: integer := 0 to m - 1 do
      for j: integer := 0 to n - 1 do
        if ms[i, j] <> 0 then 
        begin
          Compute(x, y);
          break;
        end else
        if manualscreen then makenwindow(516, 360, 750, 100, Colors.Beige, 'Ваш массив пуст', 'ПКМ, чтобы закрыть это окно', 80, Colors.Black, Colors.DimGray);
end;

// Блок помощи KeyPress //
/// Обрабатывает нажатия клавиш на lengthscreen и randomscreen и выводит допустимые значения в указанное место на экране // 
/// k - значение нажатой клавиши; val - переменная, куда записывать значение клавиши; st - строка, где находится число целиком; x1, y1 - координаты вывода st; len - допустимая длина числа //
procedure KHelp(k: Char; var val: integer; var st: string; x1, y1: real; len: integer);
begin
  if (st.Length < len - 1) then
  begin
    if TryToK(k) then
    begin
      st := st + k;
      val := st.ToInteger;
    end;
    if not stb then makeqbutton(250, 150, 140, 50, colors.Beige, ' ', 2, Colors.Black);
    if stb then makeqbutton(250, 225, 140, 50, colors.Beige, ' ', 2, Colors.Black);
  end;
  Font.Size := 48;
  Font.Color := Colors.Black;
  Textout(x1, y1, st + '|');
end;

/// Обрабатывает нажатия клавиш при ручном заполнении массива и выводит допустимые значения в указанное место на экране // k - значение клавиши //
procedure ManualkHelp(k: char);
begin
  if (s1.Length < 8) then 
  begin
    if TryToK(k) then
    begin
      s1 := s1 + k;
      ms[m1.ToInt, n1.ToInt] := s1.ToReal;
      if s1.Length = 1 then 
        makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (n1 * r), r / 2 + (m1 * r) + (600 - (m * r)) / 2, r, r, colors.Beige, s1[1], Round(r - 8), Colors.Black)
      else 
        makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (n1 * r), r / 2 + (m1 * r) + (600 - (m * r)) / 2, r, r, colors.Beige, s1[1] + s1[2], Round(r - 8), Colors.Black);
    end;
  end;
  makenwindow(516, 675, 750, 100, Colors.Beige, s1 + '|', 'ПКМ, чтобы закрыть это окно. M = ' + m1 + ' N = ' + n1, 80, Colors.Black, Colors.DimGray);
end;

// Блок помощи KeyDown //
/// Обрабатывает нажатие клавиши BackSpace при lengthscreen и randomscreen // s - строка, которую нужно обработать; l, r - переменные, куда записывается значение s //
procedure KDBackHelp(var s: string; var l, r: integer);
begin
  Setlength(s, s.Length - 1); // Отнимаем у строковой переменной последний знак 
  try // Пытаемся записать значение s в l или r
    if lengthscreen then l := s.ToInteger;
    if randomscreen then r := s.ToInteger;
  except
    on System.FormatException do
      if lengthscreen then l := 0
      else if randomscreen then r := 0;
  end;
end;

/// Обрабатывает нажатие клавиши BackSpace при ручном заполнении массива //
procedure KDBackManHelp();
begin
  Setlength(s1, s1.Length - 1); // Отнимаем у строковой переменной последний знак 
  if not((s1.Length = 1) and (s1[1] = '-')) then
  if s1.Length > 0 then ms[m1.ToInt, n1.ToInt] := s1.ToReal; // Пытаемся записать значение s в ячейку массива
  if s1.Length = 0 then 
  begin // Выводим на экран ячейку массива
    ms[m1.ToInt, n1.ToInt] := 0;
    makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (n1 * r), r / 2 + (m1 * r) + (600 - (m * r)) / 2, r, r, colors.Beige, '0', Round(r - 8), Colors.Black);
  end
  else if s1.Length = 1 then
    makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (n1 * r), r / 2 + (m1 * r) + (600 - (m * r)) / 2, r, r, colors.Beige, s1[1], Round(r - 8), Colors.Black)
  else 
    makeqbutton(r / 2 + (1032 - (n * r)) / 2 + (n1 * r), r / 2 + (m1 * r) + (600 - (m * r)) / 2, r, r, colors.Beige, s1[1] + s1[2], Round(r - 8), Colors.Black);
  makenwindow(516, 675, 750, 100, Colors.Beige, s1 + '|', 'ПКМ, чтобы закрыть это окно. M = ' + m1 + ' N = ' + n1, 80, Colors.Black, Colors.DimGray)
end;

/// Обрабатывает нажатие клавиши Enter при ручном заполнении массива //
procedure KDRetManHelp();
begin
  if n > n1 + 1 then n1 := n1 + 1 // Переход на след. ячейку
  else
  begin
    if m > m1 + 1 then 
    begin
      n1 := 0;
      m1 := m1 + 1;
    end
    else
    begin
      n1 := 0;
      m1 := 0;
    end;
  end;
  if ms[m1.ToInt, n1.ToInt] = 0 then makenwindow(516, 675, 750, 100, Colors.Beige, '|', 'ПКМ, чтобы закрыть это окно. M = ' + m1 + ' N = ' + n1, 80, Colors.Black, Colors.DimGray)
  else // Рисует окно с увеличенным значением ячейки
    makenwindow(516, 675, 750, 100, Colors.Beige, ms[m1.ToInt, n1.ToInt] + '|', 'ПКМ, чтобы закрыть это окно. M = ' + m1 + ' N = ' + n1, 80, Colors.Black, Colors.DimGray);
  if ms[m1.ToInt, n1.ToInt] <> 0 then s1 := ms[m1.ToInt, n1.ToInt].ToString // Записываем в строку значение ячейки массива или, если оно равно 0, обнуляем ее
  else Setlength(s1, 0);
end;

// Блок периферии //
/// Процедура события нажатия мыши // x, y - координаты мыши; mb - кнопка мыши //
procedure MD(x, y: real; mb: integer);
begin
  if mainscreen and (mb = 1) then MainmHelp(x, y)
  else if manualscreen then ManualmHelp(x, y)
  else if (resultscreen1 or resultscreen2) and (mb = 1) then ResmHelp(x, y) 
  else if resultscreen3 and (mb = 2) then Res3mHelp(x, y) 
  else if resultscreen3 and (mb = 1) then Res3mHelp1(x, y);
  if mainscreen and newindow and (mb = 2) then unwindow(MainMenu);
  if lengthscreen or randomscreen then LenmHelp(mb, x, y);
  if resultscreen1 and newindow and (mb = 2) then unwindowl('Исходный массив', 'Вычислить1');
  if resultscreen2 and newindow and (mb = 2) then unwindowl('Искомый массив', 'Вычислить2');
  if manualscreen and newindow and (mb = 2) then unwindowl('Исходный массив', 'Вычислить1');
  if manualscreen and (mb = 1) and not hint then ComputemHelp(x, y);
  if (resultscreen1 or resultscreen2 or resultscreen3 or manualscreen) and (mb = 2) and hitbox(x, y, 512, 675, 400, 50) and not hint then SaveSomeResult();
  
end;

/// Процедура события нажатия клавиши // k - клавиша //
procedure KD(k: key);// Процедура нажатия клавиши
begin
  if randomscreen and not stb and (s1.Length < 1) and ((k.ToString = 'OemMinus') or (k.ToString = 'Subtract')) and not newindow then s1 += '-';
  if randomscreen and stb and (s2.Length < 1) and ((k.ToString = 'OemMinus') or (k.ToString = 'Subtract')) and not newindow then s2 += '-';
  
  if resultscreen1 and (k.ToString = 'Return') then Compute(900, 675)
  else
  if resultscreen2 and (k.ToString = 'Return') then Compute1(900, 675);
  
  if (lengthscreen or randomscreen) and (k.ToString = 'Return') and not stb and not newindow then HelpToHelp(stb, 150, s1, s2)
  else 
  if lengthscreen and (k.ToString = 'Return') and stb and not newindow then NextR()
  else
  if randomscreen and (k.ToString = 'Return') and stb and not newindow then NextR1();
  
  if (lengthscreen or randomscreen) and not stb and (s1.Length > 0) and (k.ToString = 'Back') and not newindow then KDBackHelp(s1, m, lp);
  if (lengthscreen or randomscreen) and stb and (s2.Length > 0) and (k.ToString = 'Back') and not newindow then KDBackHelp(s2, n, up)
  else
  if (lengthscreen or randomscreen) and stb and ((s2.Length = 1) or (s2.Length = 0)) and (k.ToString = 'Back') and not newindow then HelpToHelp(stb, 225, s2, s1);
  
  if manualscreen and allowk and (s1.Length > 0) and (k.ToString = 'Back') then KDBackManHelp();
  if manualscreen and allowk and (k.ToString = 'Return') then KDRetManHelp();
  if manualscreen and allowk and (s1.Length < 1) and ((k.ToString = 'OemMinus') or (k.ToString = 'Subtract')) then s1 += '-';
end;

/// Процедура события зажатия клавиши // k - клавиша //
procedure KP(k: Char);
begin
  if lengthscreen and not stb and not newindow then KHelp(k, m, s1, 185, 120, 3);
  if lengthscreen and stb and not newindow then KHelp(k, n, s2, 185, 195, 3);
  if randomscreen and not stb and not newindow then KHelp(k, lp, s1, 185, 120, 5);
  if randomscreen and stb and not newindow then KHelp(k, up, s2, 185, 195, 5);
  if manualscreen and allowk then ManualkHelp(k);
end;

begin
  // Окно //
  Window.Caption := 'Курсовая работа по информатике 2020. Выполнил студент ВГТУ Ломакин Никита (бРК-191). Вариант 13';
  Window.Width := 1024;
  Window.Height := 720;
  Window.IsFixedSize := true;
  
  // События мыши и клавиатуры //
  OnMouseDown := MD;
  OnKeyDown := KD;
  OnKeyPress := KP;
  
  // Рисование меню //
  mainscreen := true;
  MainMenu();
end.