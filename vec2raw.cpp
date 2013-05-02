#include <iostream>
#include <itpp/itbase.h>
#include <fstream>

// convert -1.0 to +1.0 => 0 to 255
unsigned char double2byte(double d) {
   return (unsigned char)(128.0*d + 127.0) ;
}

unsigned char i_byte(std::complex<double>& c) {
   return double2byte(std::real(c));
}

unsigned char q_byte(std::complex<double>& c) {
   return double2byte(std::imag(c));
}

int main()
{
    std::string fn("/home/rupello/vmshared/baseband/capbuf_vzw_571Mhz.it"); 
    std::string fo("/home/rupello/vmshared/baseband/capbuf_vzw_571Mhz.raw"); 
    itpp::cvec capbuf;
    itpp::it_ifile itf(fn);
    std::ofstream outfile (fo.c_str(),std::ios::out|std::ios::binary);
    itf.seek("capbuf");
    itf >> capbuf;
    unsigned char iq[2] = {0,0};
    for(int i=0;i<capbuf.length();i++) {
       iq[0] = i_byte(capbuf[i]);
       iq[1] = q_byte(capbuf[i]);
       if(i<10){ 
           std::cout << (int)iq[0] << "," << (int)iq[1] 
                       << "," << std::real(capbuf[i])  
                       << "," << std::imag(capbuf[i]) << std::endl;
           }
       outfile.write((const char*)iq,2); 
    }
    outfile.close();

    itf.seek("fc");
    itpp::ivec fc_v;
    itf >> fc_v;

    itf.close();
    return 0;
}
