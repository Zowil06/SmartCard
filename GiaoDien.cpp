#include "giaodien.h"	
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <sstream>
#include <iomanip>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

using namespace std;

void setColor(int color) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void veKhung(int width) 
{
    cout << char(218); 
    for (int i = 0; i < width - 2; ++i) cout << char(196);
    cout << char(191) << endl; 
}

void veDuoiKhung(int width) 
{
    cout << char(192);
    for (int i = 0; i < width - 2; ++i) cout << char(196);
    cout << char(217) << endl;
}

void hienThiDongHoDemNguoc(time_t thoiGianBatDau, int thoiGianThi) 
{
    time_t thoiGianHienTai = time(NULL);
    int thoiGianConLai = thoiGianThi - (thoiGianHienTai - thoiGianBatDau);
    
    if (thoiGianConLai < 0) thoiGianConLai = 0;
    
    int phut = thoiGianConLai / 60;
    int giay = thoiGianConLai % 60;
    
    int mauSac = 10; 
    if (thoiGianConLai < 60) mauSac = 14; //hien thi thong bao thoi gian, mau vang khi duoi 1 phut, mau do khi duoi 30s
    if (thoiGianConLai < 30) mauSac = 12; 
    
    setColor(mauSac);
    cout << "+--------------------------------------------------+\n";
    cout << "| THOI GIAN CON LAI: " << setfill('0') << setw(2) << phut << ":" 
         << setfill('0') << setw(2) << giay << "                         |\n";
    cout << "+--------------------------------------------------+\n";
    setColor(7); // Reset v? màu m?c d?nh
}

int hienThiMenu() 
{
    const int soLuaChon = 3;
    int luaChon = 0;
    string danhMuc[soLuaChon] = { "De so 1", "De so 2", "De so 3" };
    int chieuRong = 33;

    // Reset console settings before displaying menu
    system("cls");
    SetConsoleOutputCP(437); // Set to default code page for box drawing characters
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 11); // Light cyan

    while (true) {
        system("cls");
        
        // Use simple ASCII characters instead of extended box drawing characters
        cout << "+--------------------------------+" << endl;
        cout << "|       CHON BO CAU HOI          |" << endl;
        cout << "+--------------------------------+" << endl;
        
        SetConsoleTextAttribute(hConsole, 7); // Reset color

        cout << endl;
        for (int i = 0; i < soLuaChon; ++i) 
		{
            if (i == luaChon) 
			{
                SetConsoleTextAttribute(hConsole, 10); // highlight
                cout << char(175) << " >> [" << i + 1 << "] " << danhMuc[i] << " <<" << endl;
            } 
			else 
			{
                SetConsoleTextAttribute(hConsole, 7);
                cout << "     [" << i + 1 << "] " << danhMuc[i] << endl;
            }
        }

        SetConsoleTextAttribute(hConsole, 8);
        cout << "\nDung phim mui ten len xuong de chon, ENTER de xac nhan.\n";
        SetConsoleTextAttribute(hConsole, 7);

        int phim = _getch();
        if (phim == 224) phim = _getch();
        if (phim == KEY_UP) luaChon = (luaChon - 1 + soLuaChon) % soLuaChon;
        else if (phim == KEY_DOWN) luaChon = (luaChon + 1) % soLuaChon;
        else if (phim == KEY_ENTER) return luaChon + 1;
    }
}

char chonDapAnBangPhimMuiTen(const CauHoi& ch, int soThuTu, time_t thoiGianBatDau, int thoiGianThi) 
{
    int luaChon = 0;
    const int soDapAn = 4;
    char dapAnChar[4] = {'A', 'B', 'C', 'D'};
    time_t thoiGianHienTai;
    int thoiGianConLai;

    while (true) 
	{
        system("cls");
        
        
        hienThiDongHoDemNguoc(thoiGianBatDau, thoiGianThi);
        
        // Ki?m tra n?u h?t th?i gian
        thoiGianHienTai = time(NULL);
        thoiGianConLai = thoiGianThi - (thoiGianHienTai - thoiGianBatDau);
        if (thoiGianConLai <= 0) 
		{
            return 'X'; 
        }
        
        setColor(11);

        stringstream ss;
		ss << "Cau " << soThuTu << ": " << ch.cauHoi;
		string noiDung = ss.str();	
        int chieuRong = noiDung.length() + 4; 

        // V? khung trên
        cout << char(218); // góc trái trên
        for (int i = 0; i < chieuRong - 2; ++i) cout << char(196);
        cout << char(191) << endl;

        // N?i dung câu h?i
        cout << char(179) << " " << noiDung;
        int thieu = chieuRong - 2 - 1 - noiDung.length();
        while (thieu-- > 0) cout << ' ';
        cout << char(179) << endl;

        
        cout << char(192);
        for (int i = 0; i < chieuRong - 2; ++i) cout << char(196);
        cout << char(217) << endl;

        setColor(7);

       
        cout << endl;
        for (int i = 0; i < soDapAn; ++i) 
		{
            if (i == luaChon) 
			{
                setColor(10);
                cout << char(175) << " >> " << dapAnChar[i] << ". " << ch.luaChon[i] << " <<" << endl;
            } 
			else 
			{
                setColor(7);
                cout << "     " << dapAnChar[i] << ". " << ch.luaChon[i] << endl;
            }
        }

        setColor(8);
        cout << "\nDung phim mui ten len xuong de chon, ENTER de xac nhan.\n";
        setColor(7);

      
        if (_kbhit())
		{
            int phim = _getch();
            if (phim == 224) phim = _getch();
            if (phim == KEY_UP) luaChon = (luaChon - 1 + soDapAn) % soDapAn;
            else if (phim == KEY_DOWN) luaChon = (luaChon + 1) % soDapAn;
            else if (phim == KEY_ENTER) return dapAnChar[luaChon];
        }
        
        
        thoiGianHienTai = time(NULL);
        thoiGianConLai = thoiGianThi - (thoiGianHienTai - thoiGianBatDau);
        if (thoiGianConLai <= 0) 
		{
            return 'X'; 
        }
        
       
        Sleep(100);
    }
}
