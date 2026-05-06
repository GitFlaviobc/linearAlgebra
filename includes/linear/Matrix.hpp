/* ********************************************************************************** */
/*                                                                                    */
/*                                                      :::::::::: :::::::::   :::::: */
/*   Matrix.hpp                                        :+:        :+:    :+: :+:    : */
/*                                                    +:+        +:+    +:+ +:+       */
/*   By: flaviobc <github.com/GitFlaviobc>           :#::+::#   +#++:++#+  +#+        */
/*                                                  +#+        +#+    +#+ +#+         */
/*   Created: 2026/05/06 16:29:03 by flaviobc      #+#        #+#    #+# #+#    #+#   */
/*   Updated: 2026/05/06 18:25:14 by flaviobc     ###        #########   ########     */
/*                                                                                    */
/* ********************************************************************************** */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"
#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <optional>
#include <type_traits>

#ifndef REQUIRE_FLOATING_POINT
#define REQUIRE_FLOATING_POINT(T) static_assert(std::is_floating_point_v<T>, "T must be a floating-point type")
#endif

// ============================================================
//  Matrix<K, M, N>  (M rows, N cols)
// ============================================================

template <typename K, std::size_t M, std::size_t N>
class Matrix {
	REQUIRE_FLOATING_POINT(K);
public:
	std::array<std::array<K, N>, M> data{};

	Matrix() = default;
	explicit Matrix(std::array<std::array<K, N>, M> arr) : data(arr) {}

	// Matrix<float,2,2>{ {1.f,2.f}, {3.f,4.f} }
	Matrix(std::initializer_list<std::initializer_list<K>> init) {
		std::size_t r = 0;
		for (auto& row : init) {
			std::size_t c = 0;
			for (auto val : row) data[r][c++] = val;
			++r;
		}
	}

	std::array<K, N>& operator[](std::size_t i) { return data[i]; }
	const std::array<K, N>& operator[](std::size_t i) const { return data[i]; }
	K& at(std::size_t r, std::size_t c) { return data[r][c]; }
	const K& at(std::size_t r, std::size_t c) const { return data[r][c]; }

	constexpr std::size_t rows() const { return M; }
	constexpr std::size_t cols() const { return N; }
	constexpr bool is_square() const { return M == N; }

	// ── Ex 00 ────────────────────────────────────────────────
	Matrix& add(const Matrix& v) {
		for (std::size_t i = 0; i < M; ++i)
			for (std::size_t j = 0; j < N; ++j) data[i][j] += v[i][j];
		return *this;
	}
	Matrix& sub(const Matrix& v) {
		for (std::size_t i = 0; i < M; ++i)
			for (std::size_t j = 0; j < N; ++j) data[i][j] -= v[i][j];
		return *this;
	}
	Matrix& scl(K a) {
		for (std::size_t i = 0; i < M; ++i)
			for (std::size_t j = 0; j < N; ++j) data[i][j] *= a;
		return *this;
	}

	// ── Ex 07 ────────────────────────────────────────────────
	Vector<K, M> mul_vec(const Vector<K, N>& vec) const {
		Vector<K, M> result;
		for (std::size_t i = 0; i < M; ++i) {
			K sum = K{};
			for (std::size_t j = 0; j < N; ++j)
				sum = std::fma(data[i][j], vec[j], sum);
			result[i] = sum;
		}
		return result;
	}

	template <std::size_t P>
	Matrix<K, M, P> mul_mat(const Matrix<K, N, P>& mat) const {
		Matrix<K, M, P> result;
		for (std::size_t i = 0; i < M; ++i)
			for (std::size_t k = 0; k < N; ++k)
				for (std::size_t j = 0; j < P; ++j)
					result[i][j] = std::fma(data[i][k], mat[k][j], result[i][j]);
		return result;
	}

	// ── Ex 08 – trace (square only) ──────────────────────────
	K trace() const {
		static_assert(M == N, "Matrix must be square for trace");
		K r = K{};
		for (std::size_t i = 0; i < M; ++i) r += data[i][i];
		return r;
	}

	// ── Ex 09 – transpose ────────────────────────────────────
	Matrix<K, N, M> transpose() const {
		Matrix<K, N, M> result;
		for (std::size_t i = 0; i < M; ++i)
			for (std::size_t j = 0; j < N; ++j)
				result[j][i] = data[i][j];
		return result;
	}

	// ── Ex 10 – reduced row-echelon (Gauss-Jordan) ───────────
	Matrix row_echelon() const {
		Matrix mat = *this;
		std::size_t lead = 0;
		for (std::size_t r = 0; r < M; ++r) {
			if (lead >= N) break;
			std::size_t i = r;
			while (std::abs(mat[i][lead]) < K{1e-9}) {
				if (++i == M) { i = r; if (++lead == N) return mat; }
			}
			if (i != r) std::swap(mat[i], mat[r]);
			K pivot = mat[r][lead];
			for (std::size_t j = 0; j < N; ++j) mat[r][j] /= pivot;
			for (std::size_t k = 0; k < M; ++k) {
				if (k == r) continue;
				K factor = mat[k][lead];
				for (std::size_t j = 0; j < N; ++j)
					mat[k][j] = std::fma(-factor, mat[r][j], mat[k][j]);
			}
			++lead;
		}
		return mat;
	}

	// ── Ex 11 – determinant (n ≤ 4, square) ─────────────────
	K determinant() const {
		static_assert(M == N && M <= 4, "Determinant requires square matrix of size <= 4");
		if constexpr (M == 1) return data[0][0];
		else if constexpr (M == 2) return data[0][0]*data[1][1] - data[0][1]*data[1][0];
		else if constexpr (M == 3) return _det3(*this);
		else return _det4(*this);
	}

	// ── Ex 12 – inverse (square, returns optional) ───────────
	std::optional<Matrix<K, M, N>> inverse() const {
		static_assert(M == N, "Matrix must be square for inverse");
		Matrix<K, M, 2*N> aug;
		for (std::size_t i = 0; i < M; ++i) {
			for (std::size_t j = 0; j < N; ++j) aug[i][j] = data[i][j];
			aug[i][N + i] = K{1};
		}
		std::size_t lead = 0;
		for (std::size_t r = 0; r < M; ++r) {
			if (lead >= N) break;
			std::size_t i = r;
			while (std::abs(aug[i][lead]) < K{1e-9}) {
				if (++i == M) { i = r; if (++lead == N) return std::nullopt; }
			}
			if (i != r) std::swap(aug[i], aug[r]);
			K pivot = aug[r][lead];
			if (std::abs(pivot) < K{1e-9}) return std::nullopt;
			for (std::size_t j = 0; j < 2*N; ++j) aug[r][j] /= pivot;
			for (std::size_t k = 0; k < M; ++k) {
				if (k == r) continue;
				K factor = aug[k][lead];
				for (std::size_t j = 0; j < 2*N; ++j)
					aug[k][j] = std::fma(-factor, aug[r][j], aug[k][j]);
			}
			++lead;
		}
		Matrix result;
		for (std::size_t i = 0; i < M; ++i)
			for (std::size_t j = 0; j < N; ++j)
				result[i][j] = aug[i][N + j];
		return result;
	}

	// ── Ex 13 – rank ─────────────────────────────────────────
	std::size_t rank() const {
		auto ref = row_echelon();
		std::size_t r = 0;
		for (std::size_t i = 0; i < M; ++i) {
			bool nonzero = false;
			for (std::size_t j = 0; j < N; ++j)
				if (std::abs(ref[i][j]) > K{1e-9}) { nonzero = true; break; }
			if (nonzero) ++r;
		}
		return r;
	}

private:
	static K _det3(const Matrix<K,3,3>& m) {
		return m[0][0]*(m[1][1]*m[2][2] - m[1][2]*m[2][1])
			 - m[0][1]*(m[1][0]*m[2][2] - m[1][2]*m[2][0])
			 + m[0][2]*(m[1][0]*m[2][1] - m[1][1]*m[2][0]);
	}

	static K _det4(const Matrix<K,4,4>& m) {
		auto sub3 = [&](std::size_t sr, std::size_t sc) {
			Matrix<K,3,3> s;
			std::size_t ri = 0;
			for (std::size_t r = 0; r < 4; ++r) {
				if (r == sr) continue;
				std::size_t ci = 0;
				for (std::size_t c = 0; c < 4; ++c) {
					if (c == sc) continue;
					s[ri][ci++] = m[r][c];
				}
				++ri;
			}
			return s;
		};
		K det = K{};
		K sign = K{1};
		for (std::size_t j = 0; j < 4; ++j) {
			det += sign * m[0][j] * _det3(sub3(0, j));
			sign = -sign;
		}
		return det;
	}
};

template <typename K, std::size_t M, std::size_t N>
std::ostream& operator<<(std::ostream& os, const Matrix<K, M, N>& m) {
	for (std::size_t i = 0; i < M; ++i) {
		os << "[";
		for (std::size_t j = 0; j < N; ++j) {
			os << m[i][j];
			if (j + 1 < N) os << ", ";
		}
		os << "]\n";
	}
	return os;
}

#endif
