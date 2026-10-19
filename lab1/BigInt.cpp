#include "BigInt.h"
#include <string>
#include <stdexcept>
#include <algorithm>

// конструкторы/деструктор
BigInt::BigInt() : size_(1), negative_(false) {
	digits_ = new char[1];
	digits_[0] = 0;
}

BigInt::BigInt(const std::string& value) {
	if (value.empty()) {
		throw std::invalid_argument("Строка пустая");
	}

	size_t start_ind = 0;
	if (value[0] == '-') {
		start_ind = 1;
		negative_ = true;
	}
	else if (value[0] == '+') {
		start_ind = 1;
		negative_ = false;
	}
	else {
		negative_ = false;
	}

	size_ = value.length() - start_ind;
	if (size_ == 0) {
		throw std::invalid_argument("Ошибка ввода");
	}
	digits_ = new char[size_];
	for (size_t i = 0; i < size_; i++) {
		if (value[size_ + start_ind - i - 1] < '0' || value[size_ + start_ind - i - 1] > '9') {
			delete[] digits_;
			throw std::invalid_argument("Ошибка ввода");
		}
		digits_[i] = value[size_ + start_ind - i - 1] - '0';
	}
	normalization();
}

BigInt::BigInt(const BigInt& BI) : size_(BI.size_), negative_(BI.negative_) {
	digits_ = new char[size_];
	for (size_t i = 0; i < size_; i++) {
		digits_[i] = BI.digits_[i];
	}
}

BigInt::BigInt(long long value) : BigInt(std::to_string(value)) {}

BigInt::~BigInt() {
	delete[] digits_;
}

// перегрузка операторов
BigInt& BigInt::operator=(const BigInt& BI) {
	if (this == &BI) {
		return *this;
	}

	size_ = BI.size_;
	negative_ = BI.negative_;

	delete[] digits_;
	digits_ = new char[size_];
	for (size_t i = 0; i < size_; i++) {
		digits_[i] = BI.digits_[i];
	}

	return *this;
}

std::ostream& operator<<(std::ostream& out, const BigInt& BI) {
	out << static_cast<std::string>(BI);
	return out;
}

BigInt::operator std::string() const {
	std::string bi = "";
	if (negative_) {
		bi.push_back('-');
	}
	for (size_t i = 0; i < size_; i++) {
		bi.push_back(static_cast<char>(digits_[size_ - 1 - i] + '0'));
	}
	return bi;
}

bool BigInt::operator==(const BigInt& BI) const {
	if (negative_ != BI.negative_) {
		return false;
	}
	if (size_ != BI.size_) {
		return false;
	}
	for (size_t i = 0; i < size_; i++) {
		if (digits_[i] != BI.digits_[i]) {
			return false;
		}
	}
	return true;
}

bool BigInt::operator!=(const BigInt& BI) const {
	return !(*this == BI);
}

// приватные методы
void BigInt::normalization() {
	while (size_ > 1 && digits_[size_ - 1] == 0) {
		size_--;
	}
	if (size_ == 1 && digits_[0] == 0) {
		negative_ = false;
	}
}

int BigInt::cmp_abs(const BigInt& BI) const {
	if (size_ > BI.size_) {
		return 1;
	}
	if (size_ < BI.size_) {
		return -1;
	}
	for (size_t i = 0; i < size_; i++) {
		if (digits_[size_ - i - 1] > BI.digits_[size_ - i - 1]) {
			return 1;
		}
		if (digits_[size_ - i - 1] < BI.digits_[size_ - i - 1]) {
			return -1;
		}
	}
	return 0;
}

char* BigInt::sum_abs(const BigInt& BI, size_t& res_size) const {
	size_t max_size = std::max(size_, BI.size_);
	char* result = new char[max_size + 1];
	int carry = 0;
	for (size_t i = 0; i < max_size; i++) {
		int dig_a = 0;
		int dig_b = 0;
		if (i < size_) {
			dig_a = digits_[i];
		}
		if (i < BI.size_) {
			dig_b = BI.digits_[i];
		}

		int sum = dig_a + dig_b + carry;
		result[i] = sum % 10;
		carry = sum / 10;
	}

	if (carry != 0) {
		result[max_size] = static_cast<char>(carry);
		res_size = max_size + 1;
	}
	else {
		res_size = max_size;
	}

	return result;
}

char* BigInt::sub_abs(const BigInt& BI, size_t& res_size) const {
	char* result = new char[size_];
	int borrow = 0;
	for (size_t i = 0; i < size_; i++) {
		int dig_a = digits_[i];
		int dig_b = 0;
		if (i < BI.size_) {
			dig_b = BI.digits_[i];
		}

		int diff = dig_a - dig_b - borrow;
		if (diff < 0) {
			diff += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		result[i] = static_cast<char>(diff);
	}

	res_size = size_;
	while (res_size > 1 && result[res_size - 1] == 0) {
		res_size--;
	}

	return result;
}

// публичные методы
bool BigInt::operator>(const BigInt& BI) const {
	if (negative_ && !BI.negative_) {
		return false;
	}
	if (!negative_ && BI.negative_) {
		return true;
	}

	int cmp = this->cmp_abs(BI);
	if (cmp == 0) {
		return false;
	}

	if (negative_) {
		return cmp == -1;
	}
	else {
		return cmp == 1;
	}
}

bool BigInt::operator<(const BigInt& BI) const {
	if (*this > BI || *this == BI) {
		return false;
	}
	return true;
}

bool BigInt::operator>=(const BigInt& BI) const {
	if (*this > BI || *this == BI) {
		return true;
	}
	return false;
}

bool BigInt::operator<=(const BigInt& BI) const {
	if (*this < BI || *this == BI) {
		return true;
	}
	return false;
}

BigInt BigInt::operator-() const {
	BigInt result(*this);
	if (!(result.size_ == 1 && result.digits_[0] == 0)) {
		result.negative_ = !result.negative_;
	}

	return result;
}

BigInt& BigInt::operator+=(const BigInt& BI) {
	char* res = nullptr;
	size_t res_size = 0;
	bool ngtv = false;
	if (negative_ == BI.negative_) {
		res = sum_abs(BI, res_size);
		ngtv = negative_;
	}
	else {
		int cmp = cmp_abs(BI);
		if (cmp == 1) {
			res = sub_abs(BI, res_size);
			ngtv = negative_;
		}
		else if (cmp == -1) {
			res = BI.sub_abs(*this, res_size);
			ngtv = BI.negative_;
		}
		else {
			res = new char[1];
			res[0] = 0;
			res_size = 1;
			ngtv = false;
		}
	}

	delete[] digits_;
	digits_ = res;
	size_ = res_size;
	negative_ = ngtv;
	normalization();

	return *this;
}

BigInt BigInt::operator+(const BigInt& BI) const {
	BigInt res(*this);
	res += BI;
	return res;
}

BigInt& BigInt::operator-=(const BigInt& BI) {
	*this += -BI;
	return *this;
}

BigInt BigInt::operator-(const BigInt& BI) const {
	BigInt res(*this);
	res -= BI;
	return res;
}

BigInt& BigInt::operator++() {
	*this += BigInt("1");
	return *this;
}

BigInt& BigInt::operator--() {
	*this -= BigInt("1");
	return *this;
}

BigInt BigInt::operator++(int) {
	BigInt old(*this);
	++(*this);
	return old;
}

BigInt BigInt::operator--(int) {
	BigInt old(*this);
	--(*this);
	return old;
}

bool BigInt::operator!() const{
	return size_ == 1 && digits_[0] == 0;
}

BigInt& BigInt::operator*=(const BigInt& BI) {
	bool res_ngtv = negative_ != BI.negative_;
	BigInt mult1(*this);
	BigInt mult2(BI);
	mult1.negative_ = false;
	mult2.negative_ = false;

	BigInt result(0);
	while (mult2 > 0) {
		result += mult1;
		mult2--;
	}

	*this = result;
	if (!(*this)) {
		negative_ = false;
	}
	else {
		negative_ = res_ngtv;
	}

	return *this;
}

BigInt BigInt::operator*(const BigInt& BI) const {
	BigInt res(*this);
	res *= BI;
	return res;
}

BigInt& BigInt::operator/=(const BigInt& BI) {
	if (!BI) {
		throw std::invalid_argument("Деление на 0");
	}
	bool res_ngtv = negative_ != BI.negative_;
	BigInt divd(*this);
	BigInt divs(BI);
	divd.negative_ = false;
	divs.negative_ = false;

	BigInt result(0);
	while (divd >= divs) {
		result += 1;
		divd -= divs;
	}

	*this = result;
	if (!(*this)) {
		negative_ = false;
	}
	else {
		negative_ = res_ngtv;
	}

	return *this;
}

BigInt BigInt::operator/(const BigInt& BI) const {
	BigInt res(*this);
	res /= BI;
	return res;
}

BigInt operator+(long long value, const BigInt& BI) {
	BigInt res(value);
	res += BI;
	return res;
}

BigInt operator-(long long value, const BigInt& BI) {
	BigInt res(value);
	res -= BI;
	return res;
}

BigInt operator*(long long value, const BigInt& BI) {
	BigInt res(value);
	res *= BI;
	return res;
}

BigInt operator/(long long value, const BigInt& BI) {
	BigInt res(value);
	res /= BI;
	return res;
}

bool operator==(long long value, const BigInt& BI) {
	BigInt res(value);
	return res == BI;
}

bool operator!=(long long value, const BigInt& BI) {
	BigInt res(value);
	return res != BI;
}

bool operator>(long long value, const BigInt& BI) {
	BigInt res(value);
	return res > BI;
}

bool operator<(long long value, const BigInt& BI) {
	BigInt res(value);
	return res < BI;
}

bool operator>=(long long value, const BigInt& BI) {
	BigInt res(value);
	return res >= BI;
}

bool operator<=(long long value, const BigInt& BI) {
	BigInt res(value);
	return res <= BI;
}