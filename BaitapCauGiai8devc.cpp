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
    int  gioiTinh;      // Gioi tinh
    Ngay ngaySinh;      // Ngay thang nam sinh
    char diaChi[100];   // Dia chi
    char lop[12];       // Lop
    char khoa[7];       // Khoa
};

// Khai bao cau truc cho mot node trong danh sach lien ket don
struct Node {
    SinhVien data; // Du lieu cua sinh vien
    Node *link;    // Con tro den node tiep theo trong danh sach
};

// Khai bao cau truc danh sach lien ket
struct List {
    Node *first;
    Node *last;
};

// Ham khoi tao danh sach lien ket rong
void initList(List &list) {
    list.first = NULL;
    list.last = NULL;
}

// Ham tao node sinh vien moi
Node* createNode(SinhVien sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = NULL;
    return newNode;
}

// Ham them sinh vien vao danh sach theo thu tu ma sinh vien
void addStudentSorted(List &list, SinhVien sv) {
    Node* newNode = createNode(sv);

    // Neu danh sach rong hoac sinh vien moi co ma nho hon ma sinh vien dau tien
    if (list.first == NULL || strcmp(newNode->data.maSV, list.first->data.maSV) < 0) {
        newNode->link = list.first;
        list.first = newNode;
        if (list.last == NULL) {
            list.last = newNode;
        }
    } else {
        // Tim vi tri chen
        Node* prev = list.first;
        Node* curr = list.first->link;
        while (curr != NULL && strcmp(curr->data.maSV, newNode->data.maSV) < 0) {
            prev = curr;
            curr = curr->link;
        }
        newNode->link = curr;
        prev->link = newNode;
        if (curr == NULL) {
            list.last = newNode;
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
void displayStudents(const List &list) {
    Node* temp = list.first;
    if (temp == NULL) {
        cout << "Danh sach sinh vien trong." << endl;
        return;
    }
    while (temp != NULL) {
        cout << "Ma SV: " << temp->data.maSV << endl;
        cout << "Ho Ten: " << temp->data.hoTen << endl;
        cout << "Gioi Tinh: " << (temp->data.gioiTinh == 0 ? "Nam" : "Nu") << endl;
        cout << "Ngay Sinh: " << temp->data.ngaySinh.ngay << "/" << temp->data.ngaySinh.thang << "/" << temp->data.ngaySinh.nam << endl;
        cout << "Dia Chi: " << temp->data.diaChi << endl;
        cout << "Lop: " << temp->data.lop << endl;
        cout << "Khoa: " << temp->data.khoa << endl;
        cout << "--------------------------" << endl;
        temp = temp->link;
    }
}

// Ham loai bo cac sinh vien co cung ngay sinh
void loaiBoSinhVienCungNgaySinh(List &list, const Ngay &ngay) {
    Node *prev = NULL, *curr = list.first;
    bool found = false;

    while (curr != NULL) {
        // Kiem tra ngay sinh
        if (curr->data.ngaySinh.ngay == ngay.ngay &&
            curr->data.ngaySinh.thang == ngay.thang &&
            curr->data.ngaySinh.nam == ngay.nam) {
            found = true;
            Node* temp = curr;
            if (prev == NULL) { // Neu la node dau tien
                list.first = curr->link;
            } else {
                prev->link = curr->link;
            }
            curr = curr->link;
            delete temp; // Xoa node khoi bo nho
        } else {
            prev = curr;
            curr = curr->link;
        }
    }

    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh de loai bo." << endl;
    } else {
        cout << "Da loai bo cac sinh vien co cung ngay sinh." << endl;
    }
}

int main() {
    List list;
    initList(list);

    // Nhap va them sinh vien vao danh sach
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "\nNhap thong tin sinh vien thu " << i + 1 << ":" << endl;
        SinhVien sv = nhapSinhVien();
        addStudentSorted(list, sv);
    }

    // Hien thi danh sach sinh vien
    cout << "\nDanh sach sinh vien sap xep tang dan theo ma sinh vien:" << endl;
    displayStudents(list);

    // Nhap ngay sinh de loai bo sinh vien
    Ngay ngay;
    cout << "\nNhap ngay sinh can loai bo (dd mm yyyy): ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;

    // Loai bo sinh vien co cung ngay sinh
    loaiBoSinhVienCungNgaySinh(list, ngay);

    // Hien thi danh sach sinh vien sau khi loai bo
    cout << "\nDanh sach sinh vien sau khi loai bo:" << endl;
    displayStudents(list);

    return 0;
}

