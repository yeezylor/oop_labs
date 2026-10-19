#pragma once
#include <string>
#include <iostream>

class BigInt {
public:
	BigInt();
	BigInt(const std::string& value);
	BigInt(const BigInt& BI);
	BigInt(long long value);
	~BigInt();

	BigInt& operator=(const BigInt& BI);
	friend std::ostream& operator<<(std::ostream& out, const BigInt& BI);
	explicit operator std::string() const;
	bool operator==(const BigInt& BI) const;
	bool operator!=(const BigInt& BI) const;
	bool operator>(const BigInt& BI) const;
	bool operator<(const BigInt& BI) const;
	bool operator>=(const BigInt& BI) const;
	bool operator<=(const BigInt& BI) const;
	bool operator!() const;
	BigInt operator-() const;
	BigInt& operator+=(const BigInt& BI);
	BigInt operator+(const BigInt& BI) const;
	BigInt& operator-=(const BigInt& BI);
	BigInt operator-(const BigInt& BI) const;
	BigInt& operator++();
	BigInt& operator--();
	BigInt operator++(int);
	BigInt operator--(int);
	BigInt& operator*=(const BigInt& BI);
	BigInt operator*(const BigInt& BI) const;
	BigInt& operator/=(const BigInt& BI);
	BigInt operator/(const BigInt& BI) const;

private:
	size_t size_;
	bool negative_;
	char* digits_;

	void normalization();
	int cmp_abs(const BigInt& BI) const;
	char* sum_abs(const BigInt& BI, size_t& res_size) const;
	char* sub_abs(const BigInt& A, size_t& res_size) const;
};

BigInt operator+(long long value, const BigInt& BI);
BigInt operator-(long long value, const BigInt& BI);
BigInt operator*(long long value, const BigInt& BI);
BigInt operator/(long long value, const BigInt& BI);
bool operator==(long long value, const BigInt& BI);
bool operator!=(long long value, const BigInt& BI);
bool operator>(long long value, const BigInt& BI);
bool operator<(long long value, const BigInt& BI);
bool operator>=(long long value, const BigInt& BI);
bool operator<=(long long value, const BigInt& BI);