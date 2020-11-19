//заполняет массивы нулями
void hz();
//прорисовка сетки
void pole(int who=0);
//вывод моей сетки
void printIam();
//вывод сетки компа
void printcomp();
//функция инициализирует заполнение поля кораблями для меня и компа. затем начинает стрельбу
void zap ();
//расстановка моих кораблей  горизонтально
void zapgor(int& tip, int& flag);
//... вертикально
void zapver(int& tip, int& flag);
//расстановка кораблей компа
void zapbot ();
//красный крест (палуба, в которую попали)
void rc(int x, int y, int line=1);
//функция стрельбы
void fire();
//обводит поставленные и убитые корабли по горизонтали
void vokryggor(int x, int y, int tip, int who);
//обводит поставленные и убитые корабли по вертикали
void vokrygver(int x, int y, int tip, int who);
//ф-ция обводит убитые корабли
void obvodka(int x, int y, int line);
//проверка на победу
void pob();
