// класс факториал
class Factorial {

// функция для нахождения факториала
    public static int getFactorial(int f) {
        int result = 1;
        for (int i = 1; i <= f; i++) {
            result = result * i;
        }
        return result;
    }

    //главная функция
    public static void main(String[] args) {
        // находим значение вырожения
        double result = (2*getFactorial(5) + 3*getFactorial(8))/(getFactorial(6) + getFactorial(4));
        // выводим результат выражения на экран
        System.out.println("result = " + result);
    }
}