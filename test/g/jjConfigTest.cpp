#include <fstream>
#include <iostream>
#include <string>
#include <cpunit>
#include "../jjConfig.h"

namespace jjConfigTest {

    //crear el archivo de prueba
    std::ofstream testfile("testfile", ios::trunc);
    std::cout<<"algo";
    testfile<<"casa=sarmiento"<<endl;
    testfile<<"float=3.141560"<<endl;
    testfile<<"num=casa"<<endl;
    testfile.close();

    jjConfig jj("testfile");

    CPUNIT_TEST(jjConfigTest, test_obtener_cadena1) {
	std::string s = jj.Valor("casa", "null");
	cpunit::assert_equals("cadena", s, "sarmiento");
    }
}
