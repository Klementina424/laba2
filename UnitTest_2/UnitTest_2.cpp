#include "pch.h"
#include "CppUnitTest.h"
#include "..\Shannon-Fano\LinkedList.h"
#include "..\Shannon-Fano\Tree.h"
#include "..\Shannon-Fano\Decode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_2
{
	TEST_CLASS(UnitTest_2)
	{
	public:

		TEST_METHOD(Bubble_Sorting_1)
		{
			int* temp1 = new int[5];
			double* temp2 = new double[5]{ 1.01,1.02,1.03,1.04,1.05 };
			double* check = new double[5]{ 1.05,1.04,1.03,1.02,1.01 };

			for (int i = 0; i < 5; i++)
				temp1[i] = double(i);

			Bubble_Sort(temp1, temp2, 5);

			for (int i = 0; i < 5; ++i)
			{
				Assert::IsTrue(temp1[i] == double(4.0 - i));
				Assert::IsTrue(temp2[i] == check[i]);
			}
		}
		TEST_METHOD(Bubble_Sorting_2)
		{
			unsigned* temp1 = new unsigned[10]{ 1,2,3,4,5,6,7,8,9,10 };
			char* temp2 = new char[10]{ 'a', 'b', 'c', 'd', 'e','f','g','h','i','j' };

			unsigned* temp1_check = new unsigned[10]{ 10,9,8,7,6,5,4,3,2,1 };
			char* temp2_check = new char[10]{ 'j','i','h','g','f','e', 'd', 'c', 'b', 'a' };

			Bubble_Sort(temp1, temp2, 10);

			for (int i = 0; i < 10; ++i)
			{
				Assert::AreEqual(temp1[i], temp1_check[i]);
				Assert::AreEqual(temp2[i], temp2_check[i]);
			}
		}

		TEST_METHOD(Border_Search_1)
		{
			int* temp = new int[5]{ 100,40,30,20,10 };

			int border = Search_Border(temp, 0, 5);

			Assert::AreEqual(border, 0);
		}

		TEST_METHOD(Border_Search_2)
		{
			int* temp = new int[7]{ 10,6,5,4,3,2,1 };

			int border = Search_Border(temp, 0, 7);

			Assert::AreEqual(border, 1);
		}

		TEST_METHOD(Algorithm_Fano)
		{
			string str = "Happy Holidays!";

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

			unsigned* temp1 = new unsigned[Array_Size];
			char* temp2 = new char[Array_Size];

			Frequency.Fill_Array(Frequency.Get_Root(), temp1, "data");
			Frequency.Fill_Array(Frequency.Get_Root(), temp2, "key");

			Bubble_Sort(temp1, temp2, Array_Size);

			string zero = "";

			RB_TREE_Node<char, string> Symbols_Code;
			Symbols_Code.NIL_N_Root();

			Shannon_Fano(temp1, temp2, zero, zero, 0, Array_Size - 1, &Symbols_Code, Memory_Size_After);

			RB_TREE_Node<char, string> Symbols_Code_Check;
			Symbols_Code_Check.NIL_N_Root();
			Symbols_Code_Check.Insert('a', "111");
			Symbols_Code_Check.Insert('H', "110");
			Symbols_Code_Check.Insert('p', "101");
			Symbols_Code_Check.Insert('y', "100");
			Symbols_Code_Check.Insert('l', "011");
			Symbols_Code_Check.Insert('i', "0101");
			Symbols_Code_Check.Insert('d', "0100");
			Symbols_Code_Check.Insert('!', "0011");
			Symbols_Code_Check.Insert('o', "0010");
			Symbols_Code_Check.Insert(' ', "0001");
			Symbols_Code_Check.Insert('s', "0000");

			char keys[] = { 'a', 'H', 'p', 'y' , 'l', 'i', 'd', '!', 'o', ' ','s' };

			Assert::AreEqual(Memory_Size_Before, (unsigned)120);
			Assert::AreEqual(Memory_Size_After, (unsigned)51);
			for (int i = 0; i < 10; ++i)
				Assert::AreEqual(Symbols_Code[keys[i]], Symbols_Code_Check[keys[i]]);

			delete[] temp1;
			delete[] temp2;
		}

	};
}
