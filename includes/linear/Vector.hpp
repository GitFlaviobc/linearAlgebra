/* ********************************************************************************** */
/*                                                                                    */
/*                                                      :::::::::: :::::::::   :::::: */
/*   Vector.hpp                                        :+:        :+:    :+: :+:    : */
/*                                                    +:+        +:+    +:+ +:+       */
/*   By: flaviobc <github.com/GitFlaviobc>           :#::+::#   +#++:++#+  +#+        */
/*                                                  +#+        +#+    +#+ +#+         */
/*   Created: 2026/05/06 16:29:19 by flaviobc      #+#        #+#    #+# #+#    #+#   */
/*   Updated: 2026/05/06 18:13:22 by flaviobc     ###        #########   ########     */
/*                                                                                    */
/* ********************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <array>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <type_traits>

// ============================================================
//  Type constraints
// ============================================================

#define REQUIRE_FLOATING_POINT(T) static_assert(std::is_floating_point_v<T>, "T must be a floating-point type")

// ============================================================
//  Vector<K, N>
// ============================================================

template <typename K, std::size_t N>
class Vector {
	REQUIRE_FLOATING_POINT(K);
public:
	std::array<K, N> data{};

	Vector() = default;
	explicit Vector(std::array<K, N> arr) : data(arr) {}

	// Vector<float,3>{ 1.f, 0.f, 0.f }
	Vector(std::initializer_list<K> init) {
		std::size_t i = 0;
		for (auto v : init) data[i++] = v;
	}

	K& operator[](std::size_t i) { return data[i]; }
	const K& operator[](std::size_t i) const { return data[i]; }
	constexpr std::size_t size() const { return N; }

	// ── Ex 00 ────────────────────────────────────────────────
	Vector& add(const Vector& v) {
		for (std::size_t i = 0; i < N; ++i) data[i] += v[i];
		return *this;
	}
	Vector& sub(const Vector& v) {
		for (std::size_t i = 0; i < N; ++i) data[i] -= v[i];
		return *this;
	}
	Vector& scl(K a) {
		for (std::size_t i = 0; i < N; ++i) data[i] *= a;
		return *this;
	}

	// ── Ex 03 ────────────────────────────────────────────────
	K dot(const Vector& v) const {
		K r = K{};
		for (std::size_t i = 0; i < N; ++i) r = std::fma(data[i], v[i], r);
		return r;
	}

	// ── Ex 04 ────────────────────────────────────────────────
	K norm_1() const {
		K r = K{};
		for (std::size_t i = 0; i < N; ++i) r += std::abs(data[i]);
		return r;
	}
	K norm() const { return std::sqrt(dot(*this)); }
	K norm_inf() const {
		K r = K{};
		for (std::size_t i = 0; i < N; ++i) r = std::max(r, std::abs(data[i]));
		return r;
	}

};

	template <typename K, std::size_t N>
	std::ostream& operator<<(std::ostream& os, const Vector<K, N>& v) {
		for (std::size_t i = 0; i < N; ++i) os << "[" << v[i] << "]\n";
		return os;
	}

#endif