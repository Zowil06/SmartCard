#ifndef GIAODIEN_H
#define GIAODIEN_H

#include "cauhoi.h"
#include <ctime>


int hienThiMenu();// menu chon bo cau hoi

char chonDapAnBangPhimMuiTen(const CauHoi& ch, int soThuTu, time_t thoiGianBatDau, int thoiGianThi);

void hienThiDongHoDemNguoc(time_t thoiGianBatDau, int thoiGianThi);

#endif
