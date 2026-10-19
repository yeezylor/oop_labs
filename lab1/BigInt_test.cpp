#include <gtest/gtest.h>
#include "BigInt.h"

TEST(BI_test, default_constructor) {
	BigInt a;
	EXPECT_EQ(static_cast<std::string>(a), "0");
}

TEST(BI_test, string_constructor) {
	BigInt a("777777");
	EXPECT_EQ(static_cast<std::string>(a), "777777");

	BigInt b("-777777");
	EXPECT_EQ(static_cast<std::string>(b), "-777777");

	BigInt c("+777777");
	EXPECT_EQ(static_cast<std::string>(c), "777777");
}

TEST(BI_test, valid_constructor) {
	EXPECT_THROW(BigInt a(""), std::invalid_argument);
	EXPECT_THROW(BigInt("-"), std::invalid_argument);
	EXPECT_THROW(BigInt("+"), std::invalid_argument);
	EXPECT_THROW(BigInt("123abc"), std::invalid_argument);
}

TEST(BI_test, ll_constructor) {
	BigInt a(0LL);
	EXPECT_EQ(static_cast<std::string>(a), "0");

	BigInt b(9223372036854775807LL);
	EXPECT_EQ(static_cast<std::string>(b), "9223372036854775807");

	BigInt c(-9223372);
	EXPECT_EQ(static_cast<std::string>(c), "-9223372");
}

TEST(BI_comp, eq) {
	EXPECT_TRUE(BigInt("100") == BigInt(100));
	EXPECT_FALSE(BigInt("100") == BigInt(101));
	EXPECT_TRUE(BigInt("0") == BigInt("-0")); 
}

TEST(BI_comp, ineq) {
	EXPECT_TRUE(BigInt("100") != BigInt("-100"));
	EXPECT_FALSE(BigInt("50") != BigInt(50));
}
	
TEST(BI_comp, grtless) {
	EXPECT_TRUE(BigInt("100") > BigInt("99"));
	EXPECT_TRUE(BigInt("-50") > BigInt("-100"));

	EXPECT_TRUE(BigInt("99") < BigInt("100"));
	EXPECT_TRUE(BigInt("-100") < BigInt("-50"));

	EXPECT_TRUE(BigInt("100") >= BigInt("100"));
	EXPECT_TRUE(BigInt("101") >= BigInt("100"));

	EXPECT_TRUE(BigInt("-10") <= BigInt("0"));
}

TEST(arithmetic, add) {
    EXPECT_EQ(static_cast<std::string>(BigInt("12") + BigInt("34")), "46");

    EXPECT_EQ(static_cast<std::string>(BigInt("99") + BigInt("1")), "100");
    EXPECT_EQ(static_cast<std::string>(BigInt("999999") + BigInt("1")), "1000000");

    EXPECT_EQ(static_cast<std::string>(BigInt("-50") + BigInt("20")), "-30");
    EXPECT_EQ(static_cast<std::string>(BigInt("50") + BigInt("-20")), "30");
}

TEST(arithmetic, sub) {
    EXPECT_EQ(static_cast<std::string>(BigInt("100") - BigInt("1")), "99");
    EXPECT_EQ(static_cast<std::string>(BigInt("10") - BigInt("20")), "-10");

    EXPECT_EQ(static_cast<std::string>(BigInt("50") - BigInt("-50")), "100");
    EXPECT_EQ(static_cast<std::string>(BigInt("-50") - BigInt("-50")), "0");
}

TEST(arithmetic, mult) {
    EXPECT_EQ(static_cast<std::string>(BigInt("12") * BigInt("12")), "144");
    EXPECT_EQ(static_cast<std::string>(BigInt("-5") * BigInt("4")), "-20");
    EXPECT_EQ(static_cast<std::string>(BigInt("-6") * BigInt("-6")), "36");

    EXPECT_EQ(static_cast<std::string>(BigInt("999") * BigInt("0")), "0");
}

TEST(arithmetic, div) {
    EXPECT_EQ(static_cast<std::string>(BigInt("100") / BigInt("10")), "10");
    EXPECT_EQ(static_cast<std::string>(BigInt("105") / BigInt("10")), "10");
    EXPECT_EQ(static_cast<std::string>(BigInt("-20") / BigInt("5")), "-4");
    EXPECT_EQ(static_cast<std::string>(BigInt("-20") / BigInt("-4")), "5");

    EXPECT_THROW(BigInt("100") / BigInt("0"), std::invalid_argument);
}

TEST(unar_operators, minus) {
    BigInt a("42");
    EXPECT_EQ(static_cast<std::string>(-a), "-42");

    BigInt b("-100");
    EXPECT_EQ(static_cast<std::string>(-b), "100");

    BigInt zero("0");
    EXPECT_EQ(static_cast<std::string>(-zero), "0"); 
}

TEST(unar_operators, Not) {
    EXPECT_TRUE(!BigInt("0"));
    EXPECT_FALSE(!BigInt("1"));
    EXPECT_FALSE(!BigInt("-1"));
}

TEST(unar_operators, inc_dec) {
    BigInt a("99");
    EXPECT_EQ(static_cast<std::string>(++a), "100");
    EXPECT_EQ(static_cast<std::string>(a++), "100");
    EXPECT_EQ(static_cast<std::string>(a), "101");

    BigInt b("0");
    EXPECT_EQ(static_cast<std::string>(--b), "-1");
    EXPECT_EQ(static_cast<std::string>(b--), "-1");
    EXPECT_EQ(static_cast<std::string>(b), "-2");
}
/*
TEST(unar_operators, inc_dec2) {
    BigInt a("99");
    EXPECT_EQ("100", a);
}
*/