#include <fstream>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "../lib/jjconfig.h"

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
        //true: yes, y, true, t, sí, s, verdadero, v, on, 1
        testfile<<"bool1=yes"<<endl;
        testfile<<"bool2=y"<<endl;
        testfile<<"bool3=true"<<endl;
        testfile<<"bool4=t"<<endl;
        testfile<<"bool5=sí"<<endl;
        testfile<<"bool6=s"<<endl;
        testfile<<"bool7=verdadero"<<endl;
        testfile<<"bool8=v"<<endl;
        testfile<<"bool9=on"<<endl;
        testfile<<"bool10=1"<<endl;
        testfile<<"bool11=VerDaDERo"<<endl;
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

TEST_F(jjConfigTest, test_booleanos_positivos) {
    bool b1 = jj->ValorBool("bool1", false);
    ASSERT_TRUE(b1);
    
    bool b2 = jj->ValorBool("bool2", false);
    ASSERT_TRUE(b2);
    
    bool b3 = jj->ValorBool("bool3", false);
    ASSERT_TRUE(b3);
    
    bool b4 = jj->ValorBool("bool4", false);
    ASSERT_TRUE(b4);
    
    bool b5 = jj->ValorBool("bool5", false);
    ASSERT_TRUE(b5);
    
    bool b6 = jj->ValorBool("bool6", false);
    ASSERT_TRUE(b6);
    
    bool b7 = jj->ValorBool("bool7", false);
    ASSERT_TRUE(b7);
    
    bool b8 = jj->ValorBool("bool8", false);
    ASSERT_TRUE(b8);
    
    bool b9 = jj->ValorBool("bool9", false);
    ASSERT_TRUE(b9);
    
    bool b10 = jj->ValorBool("bool10", false);
    ASSERT_TRUE(b10);
}

TEST_F(jjConfigTest, test_booleanos_positivos_multiple_case) {
    bool b11 = jj->ValorBool("bool11", false);
    ASSERT_TRUE(b11);
}

TEST_F(jjConfigTest, test_booleanos_falsos) {
    bool b1 = jj->ValorBool("valor_que_no_existe", false);
    ASSERT_FALSE(b1);
    
    bool b2 = jj->ValorBool("num", true);
    ASSERT_FALSE(b2);
    
    bool b3 = jj->ValorBool("casa", true);
    ASSERT_FALSE(b3);
    
    bool b4 = jj->ValorBool("neg", true);
    ASSERT_FALSE(b4);
}

TEST_F(jjConfigTest, test_existe) {
    bool b = jj->Existe("casa");
    ASSERT_TRUE(b);
    
    bool b2 = jj->Existe("valor_que_no_existe");
    ASSERT_FALSE(b2);
    
    bool b3 = jj->Existe("nonum");
    ASSERT_TRUE(b3);

    jj->SetValor("valor_que_no_existe", true);
    bool b4 = jj->Existe("valor_que_no_existe");
    ASSERT_TRUE(b4);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
