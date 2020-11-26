using System;
class Program {
  static void Main() {
    const int MAX_CITIZENS = 10000;
    const double EPS = 5e-5;
    double p = Convert.ToDouble(Console.ReadLine()); 
    double q = Convert.ToDouble(Console.ReadLine()); 
  
    for (int i = 1; i <= MAX_CITIZENS; i++) {
    if ((int)Math.Floor((double)i * p / 100.0 + EPS) + 1 <
      (int)Math.Ceiling((double)i * q / 100.0 - EPS)) {
        Console.WriteLine(i);
        break;
    }
  }
  }
}