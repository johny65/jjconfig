#include <iostream>
#include "../src/jjConfig.h"

using namespace std;

int main(){
    jjConfig c("test_file");
    
    c.SetValor("casa", "sarmiento");
    
    string s = c.Valor("casa", "ninguna");
    cout<<"casa (sarmiento): "<<s<<endl;
    
    c.SetValor("num", "casa");
    //cout<<strtod("77.7778", NULL)<<endl;
    float i = c.ValorDouble("num", 5);

    //c.SetValor("float", 3.14156);

    cout<<s<<" "<<i<<" "<<c.ValorDouble("float", 0.0)<<endl;
    if (c.ValorBool("v", false))
        cout<<"Correcto, v es true.\n";
    if (!c.ValorBool("f", true))
        cout<<"Correcto, f es false.\n";
    c.Guardar();
    
    return 0;
}
