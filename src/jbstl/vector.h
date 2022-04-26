#pragma once
#include "def.h"

namespace jbstl {
	template<class T>
	class vector
	{
	public:
		vector() {
			m_pdata = alloc(m_capacity);
		}
		~vector() {
			if (m_pdata) {
				delete[] m_pdata;
				m_pdata = nullptr;
			}
		}

		void push_back(T val) {
			if (m_size >= m_capacity) {
				realloc();
			}
			m_pdata[m_size++] = val;
		}

		T& operator[](size_t pos) {
			return m_pdata[pos];
		}
		size_t size() const noexcept {
			return m_size;
		}
		size_t capacity() const noexcept {
			return m_capacity;
		}
		T* data() noexcept{
			return m_pdata;
		}
	private:
		T* alloc(size_t size) {
			return new T[size]{};
		}
		void realloc() {
			auto cap = m_capacity << 1;
			auto pdata = alloc(cap);
			for (size_t i = 0; i < m_size; ++i) {
				pdata[i] = m_pdata[i];
			}
			release();
			m_pdata = pdata;
			m_capacity = cap;
		}
		void release() {
			if (m_pdata) {
				delete[] m_pdata;
				m_pdata = nullptr;
			}
		}
	private:
		size_t m_capacity{1};
		size_t m_size{};
		T* m_pdata{};
	};
}