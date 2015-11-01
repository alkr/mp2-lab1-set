// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h" 

TBitField::TBitField(int len)
{	if (len<0) 
throw invalid_argument("--"); else {
	BitLen=len;
	MemLen=(len+31)/sz;
	pMem=new TELEM[MemLen];
   for (int i=0;i<MemLen;i++)
	   pMem[i]=0;
}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen=bf.BitLen;
	MemLen=bf.MemLen;
	pMem=new TELEM[MemLen];
	for (int i=0;i<MemLen;i++)
		pMem[i]=bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
	pMem=NULL;

}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{ return n/sz;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{ if (n<0) throw invalid_argument("--");
    
	 return 1<<n%sz;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0)||(n>BitLen)) throw invalid_argument("--");
	pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]|GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n<0)||(n>BitLen)) throw invalid_argument("--");
	pMem[GetMemIndex(n)]=pMem[GetMemIndex(n)]&(~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{  if ((n<0)||(n>BitLen)) throw invalid_argument("--");
   if ((pMem[GetMemIndex(n)] & GetMemMask(n))>0 ) return 1; 
   else return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{ 
	BitLen=bf.BitLen; 
	MemLen=bf.MemLen; 
	if (pMem != NULL) 
	delete pMem; 
	pMem = new TELEM[MemLen]; 
	if (pMem!=NULL) 
		for (int i=0; i<MemLen; i++) 
			pMem[i]=bf.pMem[i]; 
	return *this; 
} 

int TBitField::operator==(const TBitField &bf) const // сравнение
{ int k=1;
  if (BitLen!=bf.BitLen) return 0; else 
  { for (int i=0;i<MemLen;i++)
		  if (pMem[i]!=bf.pMem[i])
		  {  k=0; break;
		  } 
  return k;
  }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{ int k=0;
  if (BitLen!=bf.BitLen) return 1; else 
  { for (int i=0;i<MemLen;i++)
		  if (pMem[i]!=bf.pMem[i])
		  {  k=1; break;
		  } 
  return k;
  }
}
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{ 
	int k=max(BitLen, bf.BitLen);
 TBitField aa(k);
 for (int i=0;i<MemLen;i++)
	 aa.pMem[i]=pMem[i];
 for(int i=0;i<aa.MemLen;i++)
	 aa.pMem[i]|=bf.pMem[i];
 return aa;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int k=max(BitLen, bf.BitLen);
 TBitField aa(k);
 for (int i=0;i<MemLen;i++)
	 aa.pMem[i]=pMem[i];
 for(int i=0;i<aa.MemLen;i++)
	 aa.pMem[i]&=bf.pMem[i];
 return aa;
}

TBitField TBitField::operator~(void) // отрицание
{ 
	TBitField aa(BitLen);
for (int i=0;i<MemLen; i++)
  aa.pMem[i]=~pMem[i];
int n = BitLen % sz;
  int k=1;
  for (int i=0;i<n;i++)
	   k*=2;
  k-=1;
  aa.pMem[MemLen-1]&=k;
    return aa;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
		char c;
	int len = bf.GetLength();
	for (int i = 0; i < len; ++i)
	{
		istr >> c;
		if (c == '1') bf.SetBit(i);
		else
		   if (c == '0') bf.ClrBit(i);
              else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
int len = bf.GetLength();
	for ( int i = 0; i < len; ++i )
		ostr << bf.GetBit(i) << ' ' ;
	    ostr << endl;
	return ostr;
}
