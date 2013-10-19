#include <fstream>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "../../lib/jjconfig.h"

using namespace std;

class jjConfigTest : public testing::Test {
public:
    static jjConfig *jj;
    
    static void SetUpTestCase() {
        //crear el archivo de prueba
        ofstream testfile("testfile", ios::trunc);
        testfile<<"casa=sarmiento"<<endl;
        testfile<<"float=3.141560"<<endl;
        testfile<<"nonum=casa"<<endl;
        testfile<<"num=42"<<endl;
        testfile<<"neg=-1001"<<endl;
        testfile<<"doubleneg=-2.5"<<endl;
        testfile.close();

        jj = new jjConfig("testfile");
    }
    
    static void TearDownTestCase() {
        delete jj;
        remove("testfile");
    }
};

jjConfig* jjConfigTest::jj = NULL;

TEST_F(jjConfigTest, test_obtener_cadena1) {
	string s = jj->Valor("casa", "null");
	ASSERT_EQ(s, "sarmiento");
}

TEST_F(jjConfigTest, test_obtener_cadena2) {
	string s = jj->Valor("nonum", "null");
	ASSERT_EQ(s, "casa");
}

TEST_F(jjConfigTest, test_obtener_entero) {
	int i = jj->ValorInt("num", 0);
	ASSERT_EQ(i, 42);
}

TEST_F(jjConfigTest, test_obtener_entero_negativo) {
	int i = jj->ValorInt("neg", -1);
	ASSERT_EQ(i, -1001);
}

TEST_F(jjConfigTest, test_obtener_entero_sin_signo) {
	unsigned int i = jj->ValorUInt("num", 0);
	ASSERT_EQ(i, 42);
}

TEST_F(jjConfigTest, test_obtener_double) {
	double f = jj->ValorDouble("float", -1.0);
	ASSERT_EQ(f, 3.141560);
}

TEST_F(jjConfigTest, test_obtener_double_negativo) {
	double f = jj->ValorDouble("doubleneg", -0.0);
	ASSERT_EQ(f, -2.5);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
