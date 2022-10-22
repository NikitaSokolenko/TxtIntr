#include <iostream>
#include <cstdlib> // для функций strtol, exit
#include <unistd.h> // для функции getopt
#include <string>
#include <vector>

using namespace std;

// реализация интерфейса в виде класса
class Opts {
private:
 // константы с параметрами
 static constexpr int minPar = 3;
 static constexpr int maxPar = 5;
 string A = "summa";
 string S = "raznost";
 // атрибуты
 int Params = 0; // Кол-во параметров
 string Operation = "";
 bool Add = false; // Сложение
 bool Sub = false; // Вычитание
 vector <double> digits;
 double result = 0;
 void usage(const char* progName); //вывод подсказки и останов
public:
 Opts(int argc, char **argv); // конструктор
 // "геттеры" с результатами разбора параметров
 void count();
};


int main(int argc, char **argv)
{
 Opts op(argc, argv);
 op.count();
return 0;
}
// реализация конструктора - весь разбор ПКС здесь
Opts::Opts(int argc, char **argv)
{
 int opt;
 opt = getopt(argc, argv, "o:");
 switch (opt) {
 case 'o': // Операция
 Operation = optarg;
 if (Operation == A) {
 Add = true;}
 else if (Operation == S){
 Sub = true;}
 else {
 // если ошибка - сообщить и завершить
 usage(argv[0]);
 }
 break;
 case '?': // неверный параметр
 case ':': // нет значения у параметра
 usage(argv[0]); // сообщить и завершить
 }
  if (((Add == true) || (Sub == true)) ){
    for(; optind < argc; optind++){ 
        if (Params < maxPar){
        double d = strtod(argv[optind],nullptr);
        digits.push_back(d);
        Params +=1;
        } 
    }
 }
 if (Params<minPar){
 usage(argv[0]);}
}
// краткая справки и досрочное завершение программы
void Opts::usage(const char* progName)
{
 std::cout<<"Usage: "<<progName<<" -o summa^raznost <double> param1 param2 param3 [param4] [param5]\n";
 exit(1);
}
// считаем
void Opts::count(){
    result = digits[0];
    if (Add){
        for (int i = 1; i < digits.size(); i++){
            result += digits[i];
        }
    }
    else if(Sub){
        for (int i = 1; i < digits.size(); i++){
            result -= digits[i];
        }
    }
    cout<<result<<endl;
}
