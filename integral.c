#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <math.h>

                                                                                     //functions from assembler file
double f1(double);
double f2(double);
double f3(double);
double f1_diff(double);
double f2_diff(double);
double f3_diff(double);

const char prt[2] = ":";
typedef double afunc(double);
double root(afunc *f, afunc *g, double a, double b, double eps1, afunc *f_diff, afunc *g_diff);
double integral(afunc *f, double a, double b, double eps2);

int itrs = 0;                                                                         //counter of iterations

double root(afunc *f, afunc *g, double a, double b, double eps1, afunc *f_diff, afunc *g_diff) {
   int incr = 0;                                                                      //does the function increase or decrease
   int cho = 0;                                                                       //does the graph of the function lay out below or above the chord
   int sign = 0;                                                                      //do the first and the second derivatives have the same sign
   if (f(a) - g(a) < 0)
      incr = 1;
   if ((f((a + b) / 2) - g((a + b) / 2)) > ((f(a) + f(b) - g(a) - g(b)) / 2))
      cho = 0;
   if (incr == cho)
      sign = 1;
                                                                                      //tangent (Newton's) method 
   if (sign == 1) {
      double d = b;
      double c = d;
      while ((f(c) - g(c)) * (f(c - eps1) - g(c - eps1)) > 0) {
         c = d - ((f(d) - g(d)) / (f_diff(d) - g_diff(d)));
         d = c;
         itrs++;
      }
      return c;
   }
   else {
      double d = a;
      double c = d;
      while ((f(c) - g(c)) * (f(c + eps1) - g(c + eps1)) > 0) {
         c = d - ((f(d) - g(d)) / (f_diff(d) - g_diff(d)));
         d = c;
         itrs++;
      }
      return c;
   }
}

double integral(afunc *f, double a, double b, double eps2) {                          //quadrature trapezoid formula
   int n = 20;
   double h = (b - a) / n, I = 0, In = 0, I2n;                                        //I is Integral
   for (int i = 0; i <= n; i++)
      I += f(a + i*h);
   I = h * (I - (f(a) / 2) - (f(a + n*h) / 2));
   n *= 2;
   I2n = I;
   while ((fabs(In - I2n) / 3) >= eps2) {
      I /= h;
      h = (b - a) / n;
      for (int i = 0; i <= n; i++)
         I += f(a + i*h);
      I = h * (I - (f(a) / 2) - (f(a + n*h) / 2));
      n *= 2;
      In = I2n;
      I2n = I;
   }
   I = I2n/2;
   return I;
}

char all_options[] = "--help и -h, которые выводят на печать все допустимые ключи командной строки.\n"
                          "--root и -r, которые печатают абсциссы точек пересечения кривых.\n"
                          "--iterations и -i, которые печатают число итераций, потребовавшихся на приближенное решение уравнений при поиске точек пересечения.\n"
                          "--test-root и -R, которые позволяют протестировать функцию root. Фактические параметры вызова root задаются единственным параметром этой опции в виде F1:F2:A:B:E:R, где F1, F2 — номера используемых функций, A, B, E — значения параметров a, b, eps1 функции root, R — правильный ответ (вычисленный аналитически). Программа должна вызывать функцию root с указанными параметрами, сравнивать результат с правильным ответом и выводить на экран полученный результат, абсолютную и относительную ошибку.\n"
                          "--test-integral и -I, которые позволяют протестировать функцию integral. Фактические параметры вызова integral задаются единственным параметром этой опции в виде F:A:B:E:R, где F—номера используемой функций, A, B, E — значения параметров a, b, eps2 функции integral, R — правильный ответ (вычисленный аналитически). Программа должна вызывать функцию integral с указанными параметрами, сравнивать результат с правильным ответом и выводить на экран полученный результат, абсолютную и относительную ошибку.\n";

static struct option long_opt[] = {
   {"help", 0, 0, 'h'},
   {"root", 0, 0, 'r'},
   {"iterations", 0, 0, 'i'},
   {"test-root", 1, 0, 'R'},
   {"test-integral", 1, 0, 'I'},
   {0,0,0,0}
};

//eps1 = 0.001
//eps2 = 0.001

int main(int argc, char* argv[]) {
   double eps1 = 0.0001, eps2 = 0.0001;
   double s = 0;
   double x1 = root(f1, f2, 1, 2, eps1, f1_diff, f2_diff);
   double x2 = root(f1, f3, -3, -1, eps1, f1_diff, f3_diff);
   double x3 = root(f2, f3, 0.65049, 1, eps1, f2_diff, f3_diff);
   double s1 = integral(f1, x2, x1, eps2);
   double s2 = integral(f2, x3, x1, eps2);
   double s3 = integral(f3, x2, x3, eps2);
   //double s4 = integral(f2, 0, x3, eps2) + integral(f3, x3, 1, eps2);
   s = s1 - s2 - s3;
   int res;
   while ((res = getopt_long(argc, argv, "hriR:I:", long_opt, NULL)) != -1) {
      char *other_options;
      switch(res) {
        case 'h':
          printf("%s", all_options); return 0;
        case 'r':
          printf("%lf %lf %lf", x1, x2, x3); return 0;
        case 'i':
          printf("%d", itrs); return 0;
        case 'R':
          other_options = strtok(optarg, prt);                                           //prt - parameter
          double (*f1_testr)(double);
          double (*f2_testr)(double);
          double (*f1_diff_testr)(double);
          double (*f2_diff_testr)(double);
          switch (other_options[0]) {
            case '1': f1_testr = &f1; f1_diff_testr = &f1_diff; break;
            case '2': f1_testr = &f2; f1_diff_testr = &f2_diff; break;
            case '3': f1_testr = &f3; f1_diff_testr = &f3_diff; break;
            default: f1_testr = &f1; f1_diff_testr = &f1_diff;
          }
          other_options = strtok(NULL, prt);
          switch (other_options[0]) {
            case '1': f2_testr = &f1; f2_diff_testr = &f1_diff; break;
            case '2': f2_testr = &f2; f2_diff_testr = &f2_diff; break;
            case '3': f2_testr = &f3; f2_diff_testr = &f3_diff; break;
            default: f2_testr = &f1; f2_diff_testr = &f1_diff;
          }
          other_options = strtok(NULL, prt);
          double a_testr = strtod(other_options, (char **)NULL);
          other_options = strtok(NULL, prt);
          double b_testr = strtod(other_options, (char **)NULL);
          other_options = strtok(NULL, prt);
          double eps1_testr = strtod(other_options, (char **)NULL);
          other_options = strtok(NULL, prt);
          double answer_testr = strtod(other_options, (char **)NULL);
          double result_testr = root(f1_testr, f2_testr, a_testr, b_testr,
                                             eps1_testr, f1_diff_testr, f2_diff_testr);
          printf("%lf %lf %lf\n", result_testr, result_testr - answer_testr,
                       result_testr / answer_testr - 1);
          break;
        case 'I':
          other_options = strtok(optarg, prt);
          double (*f1_testi)(double);
          switch (other_options[0]) {
            case '1': f1_testi = &f1; break;
            case '2': f1_testi = &f2; break;
            case '3': f1_testi = &f3; break;
            default: f1_testi = &f1;
          }
          other_options = strtok(NULL, prt);
          double a_testi = strtod(other_options, (char **)NULL);
          other_options = strtok(NULL, prt);
          double b_testi = strtod(other_options, (char **)NULL);
          other_options = strtok(NULL, prt);
          double eps1_testi = strtod(other_options, (char **)NULL);
          other_options = strtok(NULL, prt);
          double answer_testi = strtod(other_options, (char **)NULL);
          double result_testi = integral(f1_testi, a_testi, b_testi, eps1_testi);
          printf("%lf %lf %lf\n", result_testi, result_testi - answer_testi, result_testi / answer_testi - 1);
          break;
        default: break;
      }
   }
   if (argc == 1)
      printf("%lf", s);
   return 0;
}
