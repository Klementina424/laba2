#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Tree.h"
#include <string>
#include <iomanip>

using namespace std;

template<class ARRAY_TYPE_1, class ARRAY_TYPE_2>
void Bubble_Sort(ARRAY_TYPE_1* array_1, ARRAY_TYPE_2* array_2, int Array_Size)
{
	ARRAY_TYPE_1 temp_1;
	ARRAY_TYPE_2 temp_2;

	for (int i = 0; i < Array_Size; ++i)
	{
		for (int j = i + 1; j < Array_Size; ++j)
		{
			if (array_1[i] < array_1[j])
			{
				temp_1 = array_1[i];
				array_1[i] = array_1[j];
				array_1[j] = temp_1;
				temp_2 = array_2[i];
				array_2[i] = array_2[j];
				array_2[j] = temp_2;
			}
		}
	}
}

template<class ARRAY_TYPE>
unsigned Search_Border(ARRAY_TYPE* array, int start, int end)
{
	unsigned from_begin = 0, from_end = 0;
	int j = end - 1;

	for (int i = start; ; i++)
	{
		if (i == j)
		{
			return i;
		}
		from_begin += array[i];
		while (true)
		{
			if (from_end < from_begin)
				from_end += array[j--];
			else
				break;
			if (i == j)
			{
				return i;
			}

		}
		if (i == j)
		{
			return i;
		}
	}
}

void Algorithm_Fano(unsigned* freq, char* sym, string& Branch, string& Full_Branch, int start, int end, RB_TREE_Node<char, string>* Symbols_Code, unsigned& Memory_Size_After)
{
	unsigned m;
	string T_Branch = "";

	T_Branch = Full_Branch + Branch;
	if (start == end)
	{
		Memory_Size_After += T_Branch.length() * freq[start];
		Symbols_Code->Insert(sym[start], T_Branch);
		cout << sym[start] << "\t" << freq[start] << "\t\t" << T_Branch << endl;
		return;
	}
	m = Search_Border(freq, start, end);

	string zero = "0", one = "1";
	Algorithm_Fano(freq, sym, one, T_Branch, start, m, Symbols_Code, Memory_Size_After);
	Algorithm_Fano(freq, sym, zero, T_Branch, m + 1, end, Symbols_Code, Memory_Size_After);
}

void Decoding(string& str)
{
	
	cout << "Input string/text: " << str << "\n\n";

	unsigned Memory_Size_Before = str.length() * 8, Memory_Size_After = 0;

	RB_TREE_Node<char, unsigned> Frequency;
	Frequency.NIL_N_Root();

	for (int i = 0; i < str.length(); ++i)
	{
		try
		{
			Frequency.Insert(str[i], 1);
		}
		catch (int ex)
		{
			if (ex == -1)
				Frequency[str[i]]++;
		}
	}

	unsigned Array_Size = Frequency.Get_Size();

	unsigned* A = new unsigned[Array_Size];
	char* B = new char[Array_Size];

	Frequency.Fill_Array(Frequency.Get_Root(), A, "data");
	Frequency.Fill_Array(Frequency.Get_Root(), B, "key");

	Bubble_Sort(A, B, Array_Size);

	string zero = "";

	RB_TREE_Node<char, string> Symbols_Code;
	Symbols_Code.NIL_N_Root();
	setlocale(LC_ALL, "Russian");
	cout << "Символ:\tЧастота:\tКод:\n";
	Algorithm_Fano(A, B, zero, zero, 0, Array_Size - 1, &Symbols_Code, Memory_Size_After);
	cout << "\n Oбъем памяти, который занимают исходные строки: " << Memory_Size_Before << "\n Объем памяти, который занимают закодированные строки: " << Memory_Size_After << endl;
	cout << " Коэффициент сжатия: " << round((1 - ((double)Memory_Size_After / (double)Memory_Size_Before)) * 100) << "%\n";

	string Encoding_Result = "";
	for (int i = 0; i < str.length(); i++)
	{
		Encoding_Result += Symbols_Code[str[i]] + " ";
	}
	cout << "\n Результат кодирования:\n " << Encoding_Result << endl;

	RB_TREE_Node<string, char> Codes_Symbol;
	Codes_Symbol.NIL_N_Root();
	for (int i = 0; i < Array_Size; ++i)
	{
		Codes_Symbol.Insert(Symbols_Code[B[i]], B[i]);
	}

	string Decoding_Result = "", Code;
	for (int i = 0; i < Encoding_Result.length(); i++)
	{
		Code = "";
		while (true)
		{
			if (Encoding_Result[i] != ' ')
				Code += Encoding_Result[i++];
			else
				break;
		}
		Decoding_Result += Codes_Symbol[Code];
	}

	cout << "\n Результат декодирования:\n " << Decoding_Result << endl;

	delete[] A;
	delete[] B;
}
