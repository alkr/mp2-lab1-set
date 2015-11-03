// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp) 
{ 
	MaxPower = mp;
} 
// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}


// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField aa(BitField);
	return aa;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{ 
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{ 
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
   BitField.ClrBit(Elem); 
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower=s.MaxPower;
	BitField=s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower!=s.MaxPower) return 0;
	else {
		return (BitField== s.BitField);
		
	}}

int TSet::operator!=(const TSet &s) const // сравнение
{
		return (BitField != s.BitField);
		
	
}

TSet TSet::operator+(const TSet &s) // объединение
{   int k = max(MaxPower, s.MaxPower);
	TSet aa(k);
    aa.BitField=(BitField|s.BitField);
	return aa;
	
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{ 
	if (Elem>BitField.GetLength())
		throw invalid_argument("--");
	else {
		TBitField  aa(MaxPower);
		aa=BitField;
		aa.SetBit(Elem);
		TSet bb(aa);
		return bb;
	}}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem>BitField.GetLength())
		throw invalid_argument("--");
	else {
		TBitField  aa(MaxPower);
		aa=BitField;
		aa.ClrBit(Elem);
		TSet bb(aa);
		return bb;
 
	}}

TSet TSet::operator*(const TSet &s) // пересечение
{ 
	TSet aa(BitField & s.BitField); 
return aa; 
}

TSet TSet::operator~(void) // дополнение
{
	TSet aa(~BitField);
	return aa;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}
