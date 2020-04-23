#include "stdafx.h"
#include "CppUnitTest.h"
#include "DllMatrix\DllMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		//operator[][]
		TEST_METHOD(MatrixSubscriptingTest)
		{
			// TODO: Your test code here
			CDllMatrix matrix = { { 1,2,3 } };
			Assert::AreEqual(matrix[0][2], 3, 0.0);
		}

		//operator ==
		TEST_METHOD(MatrixEqualsTest)
		{
			CDllMatrix m1 = { {1,2,3}, {4,5,6}, {7,8,9} };
			CDllMatrix m2 = { { 1,2,3 },{ 4,5,6 }, { 7,8,9 } };
			Assert::IsTrue(m1 == m2);
		}

		//operator !=
		TEST_METHOD(MatrixIsNotEqualsTest)
		{
			CDllMatrix m1 = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
			CDllMatrix m2 = { { 1,2,3 },{ 4,4,6 },{ 7,8,9 } };
			Assert::IsTrue(m1 != m2);
		}

		//operator +=
		TEST_METHOD(MatrixSumTest)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
			CDllMatrix m2 = { { 6, 7, 10 },{ 13, 4, 6 },{ 14, 12, 13 } };
			m1 += m2;
			CDllMatrix m3 = { { 7, 9, 13 },{ 17, 9, 12 },{ 21, 20, 22 } };
			Assert::IsTrue(m1 == m3);
		}

		//operator -=
		TEST_METHOD(MatrixSubTest)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
			CDllMatrix m2 = { { 3, -5, 21 },{ 40, -4, 26 },{ -18, 12, -63 } };
			m1 -= m2;
			CDllMatrix m3 = { { -2, 7, -18 },{ -36, 9, -20 },{ 25, -4, 72 } };
			Assert::IsTrue(m1 == m3);
		}

		//operator *=
		TEST_METHOD(MatrixMultiNumTest)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, -9 } };
			short int value = 5;
			m1 *= value;
			CDllMatrix m2 = { { 5, 10, 15 },{ 20, 25, 30 },{ 35, 40, -45 } };
			Assert::IsTrue(m1 == m2);
		}

		//operator +
		TEST_METHOD(MatrixSum2Test)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ -7, 8, -9 } };
			CDllMatrix m2 = { { 5, 10, 15 },{ 20, 25, 30 },{ 35, 40, -45 } };
			CDllMatrix m3 = m1 + m2;
			CDllMatrix m4 = { { 6, 12, 18 },{ 24, 30, 36 },{ 28, 48, -54 } };
			Assert::IsTrue(m3 == m4);
		}

		//operator -
		TEST_METHOD(MatrixSub2Test)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ -27, 8, 9 } };
			CDllMatrix m2 = { { 6, 12, 18 },{ 24, 30, 36 },{ 28, 48, -54 } };
			CDllMatrix m3 = m1 - m2;
			CDllMatrix m4 = { { -5, -10, -15 },{ -20, -25, -30 },{ -55, -40, 63 } };
			Assert::IsTrue(m3 == m4);
		}

		//operator *
		TEST_METHOD(MatrixMulNumLeftTest)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ -27, 8, 9 } };
			short int value = -4;
			CDllMatrix m2 = m1 * value;
			CDllMatrix m3 = { { -4, -8, -12 },{ -16, -20, -24 },{ 108, -32, -36 } };
			Assert::IsTrue(m2 == m3);
		}

		//operator *
		TEST_METHOD(MatrixMulNumRightTest)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ -27, 8, 9 } };
			short int value = 10;
			CDllMatrix m2 =  value * m1;
			CDllMatrix m3 = { { 10, 20, 30 },{ 40, 50, 60 },{ -270, 80, 90 } };
			Assert::IsTrue(m2 == m3);
		}

		//operator >>
		TEST_METHOD(MatrixInputTest)
		{
			CDllMatrix m1 = { { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
			char* input = "3 3\n1 2 3\n4 5 6\n7 8 9";
			std::stringstream in(input, std::ios_base::in);
			in >> m1;
			Assert::AreEqual(input, in.str().c_str());
		}

		//operator <<
		TEST_METHOD(MatrixOutputTest)
		{
			CDllMatrix m1 = {{ 4, 5, 6 },{ 7, 8, 9 } };
			char* output = "2 3\n4 5 6\n7 8 9";
			std::stringstream out/*(output, std::ios_base::out)*/;
			out << m1;
			Assert::AreEqual(output, out.str().c_str());
		}
	};
}