#ifndef CAUHOI_H
#define CAUHOI_H

#include <string>
using namespace std;

const int MAX_CAU_HOI = 100;

struct CauHoi 
{
    string cauHoi;
    string luaChon[4];
    char dapAnDung;
};


int docCauHoiTuFile(const string& tenFile, CauHoi danhSach[], int& soLuong);

#endif
//khai bao struct va doc file
