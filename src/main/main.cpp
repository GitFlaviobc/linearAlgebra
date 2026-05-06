/* ********************************************************************************** */
/*                                                                                    */
/*                                                      :::::::::: :::::::::   :::::: */
/*   main.cpp                                          :+:        :+:    :+: :+:    : */
/*                                                    +:+        +:+    +:+ +:+       */
/*   By: flaviobc <github.com/GitFlaviobc>           :#::+::#   +#++:++#+  +#+        */
/*                                                  +#+        +#+    +#+ +#+         */
/*   Created: 2026/05/04 20:22:01 by flaviobc      #+#        #+#    #+# #+#    #+#   */
/*   Updated: 2026/05/06 18:30:55 by flaviobc     ###        #########   ########     */
/*                                                                                    */
/* ********************************************************************************** */

#include "linearAlgebra.hpp"
#include <iomanip>
#include <iostream>

static void section(const char* name) {
	std::cout << "\n" << name << "\n";
}

static void sub(const char* text) {
	std::cout << "  " << text << "\n";
}

// ── ex 00 ────────────────────────────────────────────────────

void test_ex00() {
	section("Ex 00 – Add / Sub / Scale");

	sub("vec add [2,3] + [5,7]");
	Vector<float,2> u{2.f,3.f}, v{5.f,7.f};
	u.add(v); std::cout << u;  // [7][10]

	sub("vec sub [2,3] - [5,7]");
	u = Vector<float,2>{2.f,3.f};
	u.sub(v); std::cout << u;  // [-3][-4]

	sub("vec scl [2,3] * 2");
	u = Vector<float,2>{2.f,3.f};
	u.scl(2.f); std::cout << u;  // [4][6]

	sub("mat add");
	Matrix<float,2,2> m1{ {1.f,2.f},{3.f,4.f} };
	Matrix<float,2,2> m2{ {7.f,4.f},{-2.f,2.f} };
	m1.add(m2); std::cout << m1;  // [8,6][1,6]

	sub("mat sub");
	m1 = Matrix<float,2,2>{ {1.f,2.f},{3.f,4.f} };
	m1.sub(m2); std::cout << m1;  // [-6,-2][5,2]

	sub("mat scl * 2");
	m1 = Matrix<float,2,2>{ {1.f,2.f},{3.f,4.f} };
	m1.scl(2.f); std::cout << m1;  // [2,4][6,8]
}

// ── ex 01 ────────────────────────────────────────────────────

void test_ex01() {
	section("Ex 01 – Linear Combination");

	Vector<float,3> e1{1.f,0.f,0.f}, e2{0.f,1.f,0.f}, e3{0.f,0.f,1.f};
	sub("e1,e2,e3 × [10,-2,0.5]");
	std::cout << linear_combination<float,3>({e1,e2,e3},{10.f,-2.f,0.5f}); // [10][-2][0.5]

	Vector<float,3> v1{1.f,2.f,3.f}, v2{0.f,10.f,-100.f};
	sub("v1,v2 × [10,-2]");
	std::cout << linear_combination<float,3>({v1,v2},{10.f,-2.f}); // [10][0][230]
}

// ── ex 02 ────────────────────────────────────────────────────

void test_ex02() {
	section("Ex 02 – Linear Interpolation");

	sub("scalars");
	std::cout << lerp(0.f,1.f,0.f)  << "\n";   // 0
	std::cout << lerp(0.f,1.f,1.f)  << "\n";   // 1
	std::cout << lerp(0.f,1.f,0.5f) << "\n";   // 0.5
	std::cout << lerp(21.f,42.f,0.3f) << "\n"; // 27.3

	sub("vectors");
	std::cout << lerp(Vector<float,2>{2.f,1.f}, Vector<float,2>{4.f,2.f}, 0.3f); // [2.6][1.3]

	sub("matrices");
	Matrix<float,2,2> ma{ {2.f,1.f},{3.f,4.f} };
	Matrix<float,2,2> mb{ {20.f,10.f},{30.f,40.f} };
	std::cout << lerp(ma, mb, 0.5f); // [11,5.5][16.5,22]
}

// ── ex 03 ────────────────────────────────────────────────────

void test_ex03() {
	section("Ex 03 – Dot Product");

	std::cout << Vector<float,2>{0.f,0.f}.dot(Vector<float,2>{1.f,1.f}) << "\n"; // 0
	std::cout << Vector<float,2>{1.f,1.f}.dot(Vector<float,2>{1.f,1.f}) << "\n"; // 2
	std::cout << Vector<float,2>{-1.f,6.f}.dot(Vector<float,2>{3.f,2.f}) << "\n"; // 9
}

// ── ex 04 ────────────────────────────────────────────────────

void test_ex04() {
	section("Ex 04 – Norms");

	auto pn = [](const auto& u) {
		std::cout << "1-norm=" << u.norm_1()
				  << "  2-norm=" << u.norm()
				  << "  inf-norm=" << u.norm_inf() << "\n";
	};
	pn(Vector<float,3>{0.f,0.f,0.f}); // 0, 0, 0
	pn(Vector<float,3>{1.f,2.f,3.f}); // 6, 3.742, 3
	pn(Vector<float,2>{-1.f,-2.f});   // 3, 2.236, 2
}

// ── ex 05 ────────────────────────────────────────────────────

void test_ex05() {
	section("Ex 05 – Cosine");

	std::cout << angle_cos(Vector<float,2>{1.f,0.f}, Vector<float,2>{1.f,0.f})   << "\n"; // 1
	std::cout << angle_cos(Vector<float,2>{1.f,0.f}, Vector<float,2>{0.f,1.f})   << "\n"; // 0
	std::cout << angle_cos(Vector<float,2>{-1.f,1.f},Vector<float,2>{1.f,-1.f})  << "\n"; // -1
	std::cout << angle_cos(Vector<float,2>{2.f,1.f}, Vector<float,2>{4.f,2.f})   << "\n"; // 1
	std::cout << angle_cos(Vector<float,3>{1.f,2.f,3.f},Vector<float,3>{4.f,5.f,6.f}) << "\n"; // 0.9746
}

// ── ex 06 ────────────────────────────────────────────────────

void test_ex06() {
	section("Ex 06 – Cross Product");

	std::cout << cross_product(Vector<float,3>{0.f,0.f,1.f}, Vector<float,3>{1.f,0.f,0.f}); // [0][1][0]
	std::cout << cross_product(Vector<float,3>{1.f,2.f,3.f}, Vector<float,3>{4.f,5.f,6.f}); // [-3][6][-3]
	std::cout << cross_product(Vector<float,3>{4.f,2.f,-3.f},Vector<float,3>{-2.f,-5.f,16.f}); // [17][-58][-16]
}

// ── ex 07 ────────────────────────────────────────────────────

void test_ex07() {
	section("Ex 07 – Matrix Multiplication");

	Matrix<float,2,2> id{ {1.f,0.f},{0.f,1.f} };
	Vector<float,2> vec{4.f,2.f};

	sub("I * [4,2]");
	std::cout << id.mul_vec(vec); // [4][2]

	sub("2I * [4,2]");
	std::cout << Matrix<float,2,2>{ {2.f,0.f},{0.f,2.f} }.mul_vec(vec); // [8][4]

	sub("[[2,-2],[-2,2]] * [4,2]");
	std::cout << Matrix<float,2,2>{ {2.f,-2.f},{-2.f,2.f} }.mul_vec(vec); // [4][-4]

	sub("I * I");
	std::cout << id.mul_mat(id);

	sub("I * [[2,1],[4,2]]");
	std::cout << id.mul_mat(Matrix<float,2,2>{ {2.f,1.f},{4.f,2.f} }); // [2,1][4,2]

	sub("[[3,-5],[6,8]] * [[2,1],[4,2]]");
	std::cout << Matrix<float,2,2>{ {3.f,-5.f},{6.f,8.f} }
				.mul_mat(Matrix<float,2,2>{ {2.f,1.f},{4.f,2.f} }); // [-14,-7][44,22]
}

// ── ex 08 ────────────────────────────────────────────────────

void test_ex08() {
	section("Ex 08 – Trace");

	std::cout << Matrix<float,2,2>{ {1.f,0.f},{0.f,1.f} }.trace() << "\n"; // 2
	std::cout << Matrix<float,3,3>{ {2.f,-5.f,0.f},{4.f,3.f,7.f},{-2.f,3.f,4.f} }.trace() << "\n"; // 9
	std::cout << Matrix<float,3,3>{ {-2.f,-8.f,4.f},{1.f,-23.f,4.f},{0.f,6.f,4.f} }.trace() << "\n"; // -21
}

// ── ex 09 ────────────────────────────────────────────────────

void test_ex09() {
	section("Ex 09 – Transpose");

	Matrix<float,2,3> m{ {1.f,2.f,3.f},{4.f,5.f,6.f} };
	sub("original 2x3"); std::cout << m;
	sub("transposed 3x2"); std::cout << m.transpose();
}

// ── ex 10 ────────────────────────────────────────────────────

void test_ex10() {
	section("Ex 10 – Row-Echelon Form");

	sub("identity");
	std::cout << Matrix<float,3,3>{ {1.f,0.f,0.f},{0.f,1.f,0.f},{0.f,0.f,1.f} }.row_echelon();

	sub("[[1,2],[3,4]]");
	std::cout << Matrix<float,2,2>{ {1.f,2.f},{3.f,4.f} }.row_echelon();

	sub("[[1,2],[2,4]] – rank 1");
	std::cout << Matrix<float,2,2>{ {1.f,2.f},{2.f,4.f} }.row_echelon();

	sub("3x5");
	std::cout << Matrix<float,3,5>{
		{8.f,5.f,-2.f,4.f,28.f},
		{4.f,2.5f,20.f,4.f,-4.f},
		{8.f,5.f,1.f,4.f,17.f}
	}.row_echelon();
}

// ── ex 11 ────────────────────────────────────────────────────

void test_ex11() {
	section("Ex 11 – Determinant");

	std::cout << Matrix<float,2,2>{ {1.f,-1.f},{-1.f,1.f} }.determinant() << "\n"; // 0
	std::cout << Matrix<float,3,3>{ {2.f,0.f,0.f},{0.f,2.f,0.f},{0.f,0.f,2.f} }.determinant() << "\n"; // 8
	std::cout << Matrix<float,3,3>{ {8.f,5.f,-2.f},{4.f,7.f,20.f},{7.f,6.f,1.f} }.determinant() << "\n"; // -174
	std::cout << Matrix<float,4,4>{
		{8.f,5.f,-2.f,4.f},
		{4.f,2.5f,20.f,4.f},
		{8.f,5.f,1.f,4.f},
		{28.f,-4.f,17.f,1.f}
	}.determinant() << "\n"; // 1032
}

// ── ex 12 ────────────────────────────────────────────────────

void test_ex12() {
	section("Ex 12 – Inverse");

	sub("identity");
	if (auto inv = Matrix<float,3,3>{ {1.f,0.f,0.f},{0.f,1.f,0.f},{0.f,0.f,1.f} }.inverse(); inv)
		std::cout << *inv;

	sub("2*I");
	if (auto inv = Matrix<float,3,3>{ {2.f,0.f,0.f},{0.f,2.f,0.f},{0.f,0.f,2.f} }.inverse(); inv)
		std::cout << *inv; // 0.5 on diagonal

	sub("general 3x3");
	if (auto inv = Matrix<float,3,3>{ {8.f,5.f,-2.f},{4.f,7.f,20.f},{7.f,6.f,1.f} }.inverse(); inv)
		std::cout << *inv;

	sub("singular [[1,-1],[-1,1]]");
	auto res = Matrix<float,2,2>{ {1.f,-1.f},{-1.f,1.f} }.inverse();
	std::cout << (res ? "has inverse" : "singular – no inverse") << "\n";
}

// ── ex 13 ────────────────────────────────────────────────────

void test_ex13() {
	section("Ex 13 – Rank");

	std::cout << Matrix<float,3,3>{ {1.f,0.f,0.f},{0.f,1.f,0.f},{0.f,0.f,1.f} }.rank() << "\n"; // 3

	std::cout << Matrix<float,3,4>{
		{1.f,2.f,0.f,0.f},
		{2.f,4.f,0.f,0.f},
		{-1.f,2.f,1.f,1.f}
	}.rank() << "\n"; // 2

	std::cout << Matrix<float,4,3>{
		{8.f,5.f,-2.f},
		{4.f,7.f,20.f},
		{7.f,6.f,1.f},
		{21.f,18.f,7.f}
	}.rank() << "\n"; // 3
}

// ── ex 14 ────────────────────────────────────────────────────

void test_ex14() {
	section("Ex 14 – Projection Matrix");

	std::cout << projection(
		3.14159265f / 2.f,  // 90 deg fov
		16.f / 9.f, // 16:9
		0.1f, // near
		100.f // far
	);
}

// ── main ─────────────────────────────────────────────────────

int main() {
	std::cout << std::fixed << std::setprecision(7);
	test_ex00(); test_ex01(); test_ex02(); test_ex03();
	test_ex04(); test_ex05(); test_ex06(); test_ex07();
	test_ex08(); test_ex09(); test_ex10(); test_ex11();
	test_ex12(); test_ex13(); test_ex14();
	return 0;
}
