/* ********************************************************************************** */
/*                                                                                    */
/*                                                      :::::::::: :::::::::   :::::: */
/*   linearAlgebra.hpp                                 :+:        :+:    :+: :+:    : */
/*                                                    +:+        +:+    +:+ +:+       */
/*   By: flaviobc <github.com/GitFlaviobc>           :#::+::#   +#++:++#+  +#+        */
/*                                                  +#+        +#+    +#+ +#+         */
/*   Created: 2026/05/04 20:22:14 by flaviobc      #+#        #+#    #+# #+#    #+#   */
/*   Updated: 2026/05/06 18:00:02 by flaviobc     ###        #########   ########     */
/*                                                                                    */
/* ********************************************************************************** */

#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

#include "Vector.hpp"
#include "Matrix.hpp"
#include <vector>

// ============================================================
//  Ex 01 – linear_combination
// ============================================================

template <typename K, std::size_t N>
Vector<K, N> linear_combination(
	const std::vector<Vector<K, N>>& u,
	const std::vector<K>& coefs)
{
	REQUIRE_FLOATING_POINT(K);
	Vector<K, N> result;
	for (std::size_t k = 0; k < u.size(); ++k)
		for (std::size_t i = 0; i < N; ++i)
			result[i] = std::fma(coefs[k], u[k][i], result[i]);
	return result;
}

// ============================================================
//  Ex 02 – lerp
// ============================================================

// scalar specialisation
template <typename V>
V lerp(V u, V v, V t) { REQUIRE_FLOATING_POINT(V); return std::fma(t, v - u, u); }

// vector specialisation
template <typename K, std::size_t N>
Vector<K, N> lerp(const Vector<K, N>& u, const Vector<K, N>& v, K t) {
	REQUIRE_FLOATING_POINT(K);
	Vector<K, N> result;
	for (std::size_t i = 0; i < N; ++i)
		result[i] = std::fma(t, v[i] - u[i], u[i]);
	return result;
}

// matrix specialisation
template <typename K, std::size_t M, std::size_t N>
Matrix<K, M, N> lerp(const Matrix<K, M, N>& u, const Matrix<K, M, N>& v, K t) {
	REQUIRE_FLOATING_POINT(K);
	Matrix<K, M, N> result;
	for (std::size_t i = 0; i < M; ++i)
		for (std::size_t j = 0; j < N; ++j)
			result[i][j] = std::fma(t, v[i][j] - u[i][j], u[i][j]);
	return result;
}

// ============================================================
//  Ex 05 – angle_cos
// ============================================================

template <typename K, std::size_t N>
K angle_cos(const Vector<K, N>& u, const Vector<K, N>& v) {
	REQUIRE_FLOATING_POINT(K);
	return u.dot(v) / (u.norm() * v.norm());
}

// ============================================================
//  Ex 06 – cross_product (R3)
// ============================================================

template <typename K>
Vector<K, 3> cross_product(const Vector<K, 3>& u, const Vector<K, 3>& v) {
	REQUIRE_FLOATING_POINT(K);
	return Vector<K, 3>{
		u[1]*v[2] - u[2]*v[1],
		u[2]*v[0] - u[0]*v[2],
		u[0]*v[1] - u[1]*v[0]
	};
}

// ============================================================
//  Ex 14 – projection matrix
// ============================================================

inline Matrix<float, 4, 4> projection(float fov, float ratio, float near, float far) {
	float t = std::tan(fov / 2.f);
	Matrix<float, 4, 4> p;
	p[0][0] = 1.f / (ratio * t);
	p[1][1] = 1.f / t;
	p[2][2] = far / (far - near);
	p[2][3] = 1.f;
	p[3][2] = -(far * near) / (far - near);
	return p;
}

#endif
