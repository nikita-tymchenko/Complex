// используем макросы для условной компиляции препроцессора. Код между #ifndef и #endif компилируется, если COMPLEX_H 
// в данный момент не определен командой препроцессора #define 
#ifndef COMPLEX_H
// директива определяет имя макроса
#define COMPLEX_H    
#define _USE_MATH_DEFINES
#include <cmath>    // подключаем библиотеку, определяющую набор функций для выполнения матем. операций и преобразований 
#include <cstdint>  // подключаем библиотеку, фиксирующую ширину целочисленных типов
#include <iostream>
//реализуем шаблонную версию класса Complex
//определенние шаблона класса
template < typename Type >    //параметр шаблона- тип хранимых элементов Type
//определение класса 
class Complex {
	//объявим публичные методы, которые будут доступны как внутри класса, так и в дочерних классах и объектах
public:
	//объявление конструктора, в котором действительная и мнимая часть инициализируются нулями по умолчанию
	Complex(Type Re = 0, Type Im = 0);
	//объявление конструктора, у которого есть тоько вещественная часть
	Complex(Type Re = 0);
	//деструктор
    ~Complex() { }
	
	//объявим методы, которые работают для модификации
	Type& Re();
	Type& Im();
	//объявим методы, которые работают для чтения
	Type const& Re() const;
	Type const& Im() const;

	//объявим методы, которые возвращают модуль и фазу в радианах и градусах
	Type Abs() const;
	Type Arg() const;
	Type ArgDeg() const;
	//объявим метод, который возвращает новое комплексно-сопряженное число типа Type
	Complex< Type > Conj() const;

	// определим приватные поля класса, которые будут доступны только внутри данного класса
private:
	Type re_;
	Type im_;

};

//определим методы, которые были объявлены внутри класса, можно переписать код, в котором объявление и определение всех методов будет внутри класса
//определим конструктор от двух аргументов
template < typename Type >
Complex< Type >::Complex(Type Re, Type Im) : re_(Re), im_(Im) 
{
}
//определим конструктор от одного аргумента
template < typename Type >
Complex< Type >::Complex(Type Re) : re_(Re), im_(0)
{
}

// определим метод, который возвращает вещественную часть, которую можно модифицировать
template < typename Type >
Type& Complex< Type >::Re() {
	return re_;
}
// определим метод, который возвращает мнимую часть, которую можно модифицировать
template < typename Type >
Type& Complex< Type >::Im() {
	return im_;
}
// определим метод, который возвращает вещественную часть, которую можно только считывать
template < typename Type >
Type const& Complex< Type >::Re() const {
	return re_;
}
// определим метод, который возвращает мнимую часть, которую можно только считывать
template < typename Type >
Type const& Complex< Type >::Im() const {
	return im_;
}

// определим метод, который возвращает модуль комплексного числа
template < typename Type >
Type Complex< Type >::Abs() const {
	return sqrt(re_ * re_ + im_ * im_);
}
//определим метод, который возвращает фазу в радианах. Для этого воспользуемся встроенной функцией atan2(y,x), которая возвращает 
//арктангенс величины y/x, лежащей в пределах от -pi до pi и не определена только для случая (0,0)
template < typename Type >
Type Complex< Type >::Arg() const {
	return atan2(im_, re_);
}
//определим метод, который возвращает фазу в градусах
template < typename Type >
Type Complex< Type >::ArgDeg() const {
	return this->Arg() * 180.0 / M_PI;    // с помощью ключевого слова this обращаемся к текущему экземпляру Arg()
}
//определим метод, который возвращает комплексно-сопряженное число
template < typename Type >
Complex< Type > Complex< Type >::Conj() const {
	Complex< Type > ComplexConj(re_, -im_);   //вводим локальную переменную, в которой будет храниться комплексно-сопряженное число
	return ComplexConj;
}

//для реализации 4го пункта будет необходимо перейти от показательной записи кч к алгебраической
//в экспоненциальной форме кч выглядит как z=abs*exp(i*arg), для перехода к алгебраической форме необходимо выполнить 
//следующие преобразования: re=abs*cos(arg), im=abs*sin(arg), z=re+i*im, тк по заданию abs=1, запись можно будет упростить
// 
// Фабричный метод, создающий комплексное число из фазы (радианы)
template <typename Type>
static Complex<Type> CreateComplexFromPhase(Type phase) {
	return Complex<Type>(std::cos(phase), std::sin(phase));
}

// Фабричный метод, создающий комплексное число из фазы (градусы)
template <typename Type>
static Complex<Type> CreateComplexFromPhaseDeg(Type phaseDeg) {
	Type phase = phaseDeg * M_PI / 180.0;
	return CreateComplexFromPhase(phase);
}

#endif // COMPLEX_H