#include <iostream>
#include <cstring> // Su dung thu vien nay de dung ham strcmp
using namespace std;

// Khai bao cau truc Ngay sinh
struct Ngay {
    int ngay, thang, nam;
};

// Khai bao cau truc Sinh vien
struct SinhVien {
    char maSV[8];       // Ma sinh vien
    char hoTen[50];     // Ho ten
    int gioiTinh;       // Gioi tinh
    Ngay ngaySinh;      // Ngay thang nam sinh
    char diaChi[100];   // Dia chi
    char lop[12];       // Lop
    char khoa[7];       // Khoa
};

// Khai bao cau truc cho mot node trong danh sach lien ket don
struct Node {
    SinhVien duLieu; // Du lieu cua sinh vien
    Node *lienKet;   // Con tro den node tiep theo trong danh sach
};

// Khai bao cau truc danh sach lien ket
struct DanhSach {
    Node *dau;
    Node *cuoi;
};

// Ham khoi tao danh sach lien ket rong
void khoiTaoDanhSach(DanhSach &danhSach) {
    danhSach.dau = NULL;
    danhSach.cuoi = NULL;
}

// Ham tao node sinh vien moi
Node* taoNode(SinhVien sv) {
    Node* nodeMoi = new Node;
    nodeMoi->duLieu = sv;
    nodeMoi->lienKet = NULL;
    return nodeMoi;
}

// Ham them sinh vien vao danh sach theo thu tu ma sinh vien
void themSinhVienTheoThuTu(DanhSach &danhSach, SinhVien sv) {
    Node* nodeMoi = taoNode(sv);

    // Neu danh sach rong hoac sinh vien moi co ma nho hon ma sinh vien dau tien
    if (danhSach.dau == NULL || strcmp(nodeMoi->duLieu.maSV, danhSach.dau->duLieu.maSV) < 0) {
        nodeMoi->lienKet = danhSach.dau;
        danhSach.dau = nodeMoi;
        if (danhSach.cuoi == NULL) {
            danhSach.cuoi = nodeMoi;
        }
    } else {
        // Tim vi tri chen
        Node* truoc = danhSach.dau;
        Node* hienTai = danhSach.dau->lienKet;
        while (hienTai != NULL && strcmp(hienTai->duLieu.maSV, nodeMoi->duLieu.maSV) < 0) {
            truoc = hienTai;
            hienTai = hienTai->lienKet;
        }
        nodeMoi->lienKet = hienTai;
        truoc->lienKet = nodeMoi;
        if (hienTai == NULL) {
            danhSach.cuoi = nodeMoi;
        }
    }
}

// Ham nhap thong tin sinh vien
SinhVien nhapSinhVien() {
    SinhVien sv;
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;
    cin.ignore();
    cout << "Nhap ho ten: ";
    cin.getline(sv.hoTen, 50);
    cout << "Nhap gioi tinh (0: Nam, 1: Nu): ";
    cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh (dd mm yyyy): ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore();
    cout << "Nhap dia chi: ";
    cin.getline(sv.diaChi, 100);
    cout << "Nhap lop: ";
    cin.getline(sv.lop, 12);
    cout << "Nhap khoa: ";
    cin.getline(sv.khoa, 7);
    return sv;
}

// Ham hien thi danh sach sinh vien
void hienThiDanhSach(const DanhSach &danhSach) {
    Node* tam = danhSach.dau;
    if (tam == NULL) {
        cout << "Danh sach sinh vien trong." << endl;
        return;
    }
    while (tam != NULL) {
        cout << "Ma SV: " << tam->duLieu.maSV << endl;
        cout << "Ho Ten: " << tam->duLieu.hoTen << endl;
        cout << "Gioi Tinh: " << (tam->duLieu.gioiTinh == 0 ? "Nam" : "Nu") << endl;
        cout << "Ngay Sinh: " << tam->duLieu.ngaySinh.ngay << "/" << tam->duLieu.ngaySinh.thang << "/" << tam->duLieu.ngaySinh.nam << endl;
        cout << "Dia Chi: " << tam->duLieu.diaChi << endl;
        cout << "Lop: " << tam->duLieu.lop << endl;
        cout << "Khoa: " << tam->duLieu.khoa << endl;
        cout << "--------------------------" << endl;
        tam = tam->lienKet;
    }
}

// Ham loai bo cac sinh vien co cung ngay sinh
void loaiBoSinhVienCungNgaySinh(DanhSach &danhSach, const Ngay &ngay) {
    Node *truoc = NULL, *hienTai = danhSach.dau;
    bool timThay = false;

    while (hienTai != NULL) {
        // Kiem tra ngay sinh
        if (hienTai->duLieu.ngaySinh.ngay == ngay.ngay &&
            hienTai->duLieu.ngaySinh.thang == ngay.thang &&
            hienTai->duLieu.ngaySinh.nam == ngay.nam) {
            timThay = true;
            Node* tam = hienTai;
            if (truoc == NULL) { // Neu la node dau tien
                danhSach.dau = hienTai->lienKet;
            } else {
                truoc->lienKet = hienTai->lienKet;
            }
            hienTai = hienTai->lienKet;
            delete tam; // Xoa node khoi bo nho
        } else {
            truoc = hienTai;
            hienTai = hienTai->lienKet;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay sinh vien cung ngay sinh de loai bo." << endl;
    } else {
        cout << "Da loai bo cac sinh vien co cung ngay sinh." << endl;
    }
}

int main() {
    DanhSach danhSach;
    khoiTaoDanhSach(danhSach);

    // Nhap va them sinh vien vao danh sach
    int soLuong;
    cout << "Nhap so luong sinh vien: ";
    cin >> soLuong;
    for (int i = 0; i < soLuong; i++) {
        cout << "\nNhap thong tin sinh vien thu " << i + 1 << ":" << endl;
        SinhVien sv = nhapSinhVien();
        themSinhVienTheoThuTu(danhSach, sv);
    }

    // Hien thi danh sach sinh vien
    cout << "\nDanh sach sinh vien sap xep tang dan theo ma sinh vien:" << endl;
    hienThiDanhSach(danhSach);

    // Nhap ngay sinh de loai bo sinh vien
    Ngay ngay;
    cout << "\nNhap ngay sinh can loai bo (dd mm yyyy): ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;

    // Loai bo sinh vien co cung ngay sinh
    loaiBoSinhVienCungNgaySinh(danhSach, ngay);

    // Hien thi danh sach sinh vien sau khi loai bo
    cout << "\nDanh sach sinh vien sau khi loai bo:" << endl;
    hienThiDanhSach(danhSach);

    return 0;
}

