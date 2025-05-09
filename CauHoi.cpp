#include "cauhoi.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

int docCauHoiTuFile(const string& tenFile, CauHoi danhSach[], int& soLuong) 
{
 	ifstream file(tenFile.c_str());

    if (!file.is_open()) 
	{
        cerr << "Khong the mo file cau hoi, vui long kiem tra lai"<< endl;
        return 0;
    }

    string dong;
    soLuong = 0;

    while (getline(file, dong) && soLuong < MAX_CAU_HOI) 
	{
        stringstream ss(dong);
        string temp;
        getline(ss, danhSach[soLuong].cauHoi, '?');
        for (int i = 0; i < 4; ++i) 
		{
            getline(ss, temp, '|');
            danhSach[soLuong].luaChon[i] = temp;
        }
        getline(ss, temp);
        danhSach[soLuong].dapAnDung = toupper(temp[0]);
        soLuong++;
    }

    file.close();
    return soLuong;
}

