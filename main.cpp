#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "cauhoi.h"
#include "giaodien.h"

using namespace std;

void hoanVi(CauHoi& a, CauHoi& b) 
{
    CauHoi temp = a;
    a = b;
    b = temp;
}

int main() 
{
    bool quayLaiMenu = true;
    
    while (quayLaiMenu) 
	{
        
        system("cls");
        SetConsoleCP(437);
        SetConsoleOutputCP(437); 
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
        
        SetConsoleTextAttribute(hConsole, 11);
        cout << "+======================================+" << endl;
        cout << "|     CHAO MUNG DEN VOI PHAN MEM       |" << endl;
        cout << "|        THI TRAC NGHIEM C++           |" << endl;
        cout << "+======================================+" << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Nhan phim bat ky de bat dau...\n";
        _getch();

        // Display menu and get user choice
        int luaChonMenu = hienThiMenu();
        string tenFile;
        switch (luaChonMenu) 
		{
            case 1: tenFile = "questions1.txt"; break;
            case 2: tenFile = "questions2.txt"; break;
            case 3: tenFile = "questions3.txt"; break;
            default: return 0;
        }
        
        // Display instructions
        system("cls");
        SetConsoleTextAttribute(hConsole, 14);
        cout << "+--------------------------------------------------+" << endl;
        cout << "|                    LUU Y                         |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        cout << "| - Bai thi gom 10 cau hoi                         |" << endl;
        cout << "| - Moi cau dung duoc tinh diem                    |" << endl;
        cout << "| - Neu diem < 5: KHONG DAT                        |" << endl;
        cout << "| - Neu diem >= 5: DAT                             |" << endl;
        cout << "| - Thoi gian lam bai: 10 phut                     |" << endl;
        cout << "+--------------------------------------------------+" << endl;
        SetConsoleTextAttribute(hConsole, 8); 
        cout << "Nhan phim bat ky de bat dau lam bai...\n";
        _getch();

      
        CauHoi danhSach[MAX_CAU_HOI];
        int soLuong = 0;
        docCauHoiTuFile(tenFile, danhSach, soLuong);
        if (soLuong == 0) 
		{
            cout << "Khong co cau hoi nao!" << endl;
            Sleep(2000);
            continue; 
        }

        
        srand(time(0));
        for (int i = 0; i < soLuong; ++i) 
		{
            int j = rand() % soLuong;
            hoanVi(danhSach[i], danhSach[j]);
        }

        
        const int soCauThi = min(soLuong, 10);
        int diem = 0;
        char dapAnNguoiDung[10];
        
        
        const int THOI_GIAN_THI = 600; //tinh theo giay, quy doi 600 giay = 10 phut
        time_t thoiGianBatDau = time(NULL);
        bool hetThoiGian = false;

        
        for (int i = 0; i < soCauThi && !hetThoiGian; ++i) {
            
            char luaChon = chonDapAnBangPhimMuiTen(danhSach[i], i + 1, thoiGianBatDau, THOI_GIAN_THI);
            
            
            if (luaChon == 'X') {
                hetThoiGian = true;
                break;
            }
            
            
            dapAnNguoiDung[i] = luaChon;
            if (luaChon == danhSach[i].dapAnDung) 
			{
                PlaySound(TEXT("correct.wav"), NULL, SND_FILENAME | SND_ASYNC);
                diem++;
            } 
			else 
			{
                PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            
            time_t thoiGianHienTai = time(NULL);
            int thoiGianConLai = THOI_GIAN_THI - (thoiGianHienTai - thoiGianBatDau);
            if (thoiGianConLai <= 0) 
			{
                hetThoiGian = true;
                break;
            }

            
            cout << "\nNhan phim bat ky de tiep tuc...";
            _getch();
        }
        
        // Display time's up message if needed
        if (hetThoiGian) 
		{
            system("cls");
            SetConsoleTextAttribute(hConsole, 12); // Màu d?
            cout << "+--------------------------------------------------+" << endl;
            cout << "|              HET THOI GIAN LAM BAI!              |" << endl;
            cout << "+--------------------------------------------------+" << endl;
            SetConsoleTextAttribute(hConsole, 7); // Reset màu
            PlaySound(TEXT("wrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Sleep(2000); // Pause to show message
        }

        // Calculate score
        float diemSo = (float)diem / soCauThi * 10;
        string trangThai = (diemSo >= 5.0) ? "Dat" : "Khong dat";

        // Display results
        system("cls");
        SetConsoleTextAttribute(hConsole, 14); // Yellow for header
        cout << "+==================================================+" << endl;
        cout << "|                    KET QUA                       |" << endl;
        cout << "+==================================================+" << endl;
        SetConsoleTextAttribute(hConsole, 7); // Reset to default color

        // Display results in a simple, clear format
        cout << endl;
        SetConsoleTextAttribute(hConsole, 15); 
        cout << "  So cau hoi:     ";
        SetConsoleTextAttribute(hConsole, 7);
        cout << soCauThi << endl << endl;
        
        SetConsoleTextAttribute(hConsole, 15);
        cout << "  So cau dung:    ";
        SetConsoleTextAttribute(hConsole, 10); 
        cout << diem << endl << endl;
        
        SetConsoleTextAttribute(hConsole, 15);
        cout << "  So cau sai:     ";
        SetConsoleTextAttribute(hConsole, 12); 
        cout << (soCauThi - diem) << endl << endl;
        
        SetConsoleTextAttribute(hConsole, 15);
        cout << "  Diem so:        ";
        SetConsoleTextAttribute(hConsole, 11); 
        cout << fixed << setprecision(2) << diemSo << endl << endl;
        
        SetConsoleTextAttribute(hConsole, 15);
        cout << "  Trang thai:     ";
        if (diemSo >= 5.0) {
            SetConsoleTextAttribute(hConsole, 10); 
            cout << "DAT" << endl << endl;
        } else {
            SetConsoleTextAttribute(hConsole, 12);
            cout << "KHONG DAT" << endl << endl;
        }

        SetConsoleTextAttribute(hConsole, 14);
        cout << "+==================================================+" << endl;
        
        // Display navigation options
        SetConsoleTextAttribute(hConsole, 11); // Cyan for ESC option
        cout << "\n  Nhan ESC de quay lai menu chon de thi";
        SetConsoleTextAttribute(hConsole, 7); // Default for other option
        cout << " hoac phim bat ky khac de thoat..." << endl;
        
        // Wait for user input
        int phim = _getch();
        if (phim == 27) { // 27 la ma ascii cua esc
            quayLaiMenu = true; // Return to menu
        } 
		else 
		{
            quayLaiMenu = false; // Exit program
        }
    }

    return 0;
}
