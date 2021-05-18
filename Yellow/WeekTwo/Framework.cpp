#include "TestFramework.cpp"

using namespace std;

bool IsPalindrom(const string &s){
    return true;
}

void TestEmptyString() {
    string str = "";
    AssertTrue(IsPalindrom(str), "TestEmptyString empty");
}

void TestOneSymbolString() {
    string str = "a";
    AssertTrue(IsPalindrom(str), "TestOneSymbolString a");
    str = "?";
    AssertTrue(IsPalindrom(str), "TestOneSymbolString ?");
    str = " ";
    AssertTrue(IsPalindrom(str), "TestOneSymbolString space");
    str = ".";
    AssertTrue(IsPalindrom(str), "TestOneSymbolString .");
    str = "/";
    AssertTrue(IsPalindrom(str), "TestOneSymbolString /");
}

void TestTwoSymbolString() {
    string str = "aa";
    AssertTrue(IsPalindrom(str), "TestTwoSymbolString aa");
    str = "??";
    AssertTrue(IsPalindrom(str), "TestTwoSymbolString ??");
    str = "  ";
    AssertTrue(IsPalindrom(str), "TestTwoSymbolString spacespace");
    str = "..";
    AssertTrue(IsPalindrom(str), "TestTwoSymbolString ..");
    str = "\\";
    AssertTrue(IsPalindrom(str), "TestTwoSymbolString \\");
    str = "//";
    AssertTrue(IsPalindrom(str), "TestTwoSymbolString //");
}

void TestAnnaPalindromString() {
    string str = "anna";
    AssertTrue(IsPalindrom(str), "TestAnnaPalindromString anna 1");
    str = " anna ";
    AssertTrue(IsPalindrom(str), "TestAnnaPalindromString anna 2");
    str = "  a n n a  ";
    AssertTrue(IsPalindrom(str), "TestAnnaPalindromString anna 3");

    str = " anna  ";
    AssertFalse(IsPalindrom(str), "TestAnnaPalindromString anna 4");
    str = " a nna  ";
    AssertFalse(IsPalindrom(str), "TestAnnaPalindromString anna 5");
    str = " a n na  ";
    AssertFalse(IsPalindrom(str), "TestAnnaPalindromString anna 6");
    str = " a n n a  ";
    AssertFalse(IsPalindrom(str), "TestAnnaPalindromString anna 7");
    str = "anna ";
    AssertFalse(IsPalindrom(str), "TestAnnaPalindromString anna 8");
    str = " anna";
    AssertFalse(IsPalindrom(str), "TestAnnaPalindromString anna 9");
}


void TestPopPalindromString() {
    string str = "pop";
    AssertTrue(IsPalindrom(str), "TestPopPalindromString pop 1");
    str = " pop ";
    AssertTrue(IsPalindrom(str), "TestPopPalindromString pop 2");
    str = " p o p ";
    AssertTrue(IsPalindrom(str), "TestPopPalindromString pop 3");
    str = "p.o.p";
    AssertTrue(IsPalindrom(str), "TestPopPalindromString pop 4");
    str = ".p.o.p.";
    AssertTrue(IsPalindrom(str), "TestPopPalindromString pop 5");

    str = " p o  p ";
    AssertFalse(IsPalindrom(str), "TestPopPalindromString pop 6");
    str = " p o  p  ";
    AssertFalse(IsPalindrom(str), "TestPopPalindromString pop 7");
    str = "  p o  p  ";
    AssertFalse(IsPalindrom(str), "TestPopPalindromString pop 8");

    str = "p&op";
    AssertFalse(IsPalindrom(str), "TestPopPalindromString pop 9");
    str = " .p.o.p.";
    AssertFalse(IsPalindrom(str), "TestPopPalindromString pop 10");
    str = ".p.o.p. ";
    AssertFalse(IsPalindrom(str), "TestPopPalindromString pop 11");
}


void TestSpace() {
    string str = " p  ";
    AssertFalse(IsPalindrom(str), "TestSpace 1");

    str = "   p";
    AssertFalse(IsPalindrom(str), "TestSpace 2");


    AssertTrue(IsPalindrom(" 7777777 "), "TestSpace 3");
    AssertTrue(IsPalindrom(" 7 77777 7 "), "TestSpace 4");
    AssertTrue(IsPalindrom(" 7 7 777 7 7 "), "TestSpace 5");
    AssertTrue(IsPalindrom(" 7 7 7 7 7 7 7 "), "TestSpace 6");
    AssertTrue(IsPalindrom(" 7 7 7  7 7 7 "), "TestSpace 7");
    AssertTrue(IsPalindrom(" 7 7 7   7 7 7 "), "TestSpace 8");
    AssertTrue(IsPalindrom("  7 7 7    7 7 7  "), "TestSpace 9");


    AssertFalse(IsPalindrom(" 7  7 7 7 7 7 7 "), "TestSpace 10");
    AssertFalse(IsPalindrom(" 7 7 7 7 7  7 7 "), "TestSpace 11");
    AssertFalse(IsPalindrom(" 7 7 7 7 7   7 7 "), "TestSpace 12");
    AssertFalse(IsPalindrom(" 7 77 7 7   7 7 "), "TestSpace 13");
    AssertFalse(IsPalindrom(" 7 7 7 7 7   77 "), "TestSpace 14");
    AssertFalse(IsPalindrom(" 7 77 7 7 7 7 "), "TestSpace 15");
    AssertFalse(IsPalindrom(" 7 777 7 7 7 "), "TestSpace 16");
    AssertFalse(IsPalindrom(" 7 7777 7 7 "), "TestSpace 17");
    AssertFalse(IsPalindrom("  7 7 7 7 7 7 7"), "TestSpace 18");
    AssertFalse(IsPalindrom("7 7 7 7 7 7 7  "), "TestSpace 19");
}

void TestPalindrom() {
    AssertTrue(IsPalindrom("madam"), "TestPalindrom 1");

    AssertFalse(IsPalindrom("adama"), " TestPalindrom adama 2");

    AssertTrue(IsPalindrom(""), "TestPalindrom \"\"");
    AssertTrue(IsPalindrom("7"), "TestPalindrom 7");
    AssertTrue(IsPalindrom("77"), "TestPalindrom 77");
    AssertTrue(IsPalindrom("777"), "TestPalindrom 777");
    AssertTrue(IsPalindrom("7777"), "TestPalindrom 7777");
    AssertTrue(IsPalindrom("77777"), "TestPalindrom 77777");
    AssertTrue(IsPalindrom("777777"), "TestPalindrom 777777");
    AssertTrue(IsPalindrom("7777777"), "TestPalindrom 7777777");
}

int main() {
    TestRunner tr;
    tr.RunTest(TestEmptyString, "TestEmptyString");
    tr.RunTest(TestOneSymbolString, "TestOneSymbolString");
    tr.RunTest(TestTwoSymbolString, "TestTwoSymbolString");
    tr.RunTest(TestAnnaPalindromString, "TestAnnaPalindromString");
    tr.RunTest(TestPopPalindromString, "TestPopPalindromString");
    tr.RunTest(TestSpace, "TestSpace");
    tr.RunTest(TestPalindrom, "TestPalindrom");
    return 0;
}
