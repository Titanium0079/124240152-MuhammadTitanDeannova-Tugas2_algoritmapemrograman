#include <iostream>
using namespace std;

struct Node {
    string namaPasien;
    string keluhan;
    int no_antrian;

    Node *prev;
    Node *next;
};

Node *head, *tail, *cur, *del, *newNode;

bool isEmpty()
{
     if (head == nullptr)
        return true;
    else 
        return false;
}

void sisipPasien(string nama, string keluhan, int antrian) {
    newNode = new Node;
    newNode->namaPasien = nama;
    newNode->keluhan = keluhan;
    newNode->no_antrian = antrian;
    newNode->prev = newNode->next = nullptr;

    if (isEmpty()) {
        head = tail = newNode;
    } else if (antrian < head->no_antrian) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (antrian > tail->no_antrian) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else {
        cur = head;
        while (cur->no_antrian < antrian) {
            cur = cur->next;
        }
        newNode->prev = cur->prev;
        newNode->next = cur;
        cur->prev->next = newNode;
        cur->prev = newNode;
    }
    cout << "Pasien " << nama << " dengan antrian " << antrian << " berhasil ditambahkan." << endl;
}

void tampilkanDariAwal() {
    if (isEmpty()) {
        cout << "Tidak ada pasien di daftar anda" << endl;
        return;
    }

    cout << "\n=== Dari Awal ke Akhir ===" << endl;
    cur = head;
    int i = 1;
    while (cur != nullptr) {
        cout << i << ". " << cur->namaPasien << " | Antrian ke-" << cur->no_antrian << endl;
        i++;
        cur = cur->next;
    }
}

void tampilkanDariAkhir() {
    if (isEmpty()) {
        cout << "Tidak ada pasien di daftar anda" << endl;
        return;
    }

    cout << "\n=== Dari Akhir ke Awal ===" << endl;
    cur = tail;
    int i = 1;
    while (cur != nullptr) {
        cout << i << ". " << cur->namaPasien << " | Antrian ke-" << cur->no_antrian << endl;
        i++;
        cur = cur->prev;
    }
}


void cariPasien(int no_antrian) {
    if (isEmpty()) {
        cout << "Tidak ada Pasien dalam antrian." << endl;
        return;
    }

    cur = head;
    bool ditemukan = false;

    while (cur != nullptr) {
        if (cur->no_antrian == no_antrian) {
            cout << "\nPasien ditemukan!" << endl;
            cout << "Nama Pasien: " << cur->namaPasien << endl;
            cout << "Keluhan: " << cur->keluhan << endl;
            cout << "Antrian ke-" << cur->no_antrian << endl;
            ditemukan = true;
            break;
        }
        cur = cur->next;
    }

    if (!ditemukan) {
        cout << "Pasien dengan nomor antrian " << no_antrian << " tidak ditemukan." << endl;
    }
}


void hapusPasien(int no_antrian){
    if (isEmpty()) {
        cout << "Tidak ada pasien dalam daftar anda" << endl;
        return;
    }

    del = head;
    while (del != nullptr) {
        if (del->no_antrian == no_antrian) {
            if (del == head && del == tail) {
                head = tail = nullptr;
            } else if (del == head) {
                head = head->next;
                head->prev = nullptr;
            } else if (del == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            } else {
                del->prev->next = del->next;
                del->next->prev = del->prev;
            }
            cout << "Pasien dengan nomor antrian " << del->no_antrian << " berhasil dihapus." << endl;
            delete del;
            return;
        }
        del = del->next;
    }
    cout << "Pasien dengan nomor antrian " << no_antrian << " tidak ditemukan." << endl;
}


 int main(){
    bool logout = false;
    int pilihan;
    string namaPasien;
    string keluhan;
    int no_antrian;

    do{
        cout << "\n === MENU ANTRIAN PASIEN KLINIK SEHAT SELALU === \n" << endl;
        cout << "1. Tambah Data Pasien" << endl;
        cout << "2. Tampilkan Antrian dari Awal" << endl;
        cout << "3. Tampilkan Antrian dari Akhir" << endl;
        cout << "4. Cari Data Pasien" << endl;
        cout << "5. Hapus Data Pasien" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        
        switch (pilihan) 
        {
            case 1:
            cout << "Tambah Data Pasien" << endl;
            cout << "Masukkan Nama Pasien: ";
            cin.ignore();
            getline(cin, namaPasien);
            cout << "Masukkan Keluhan: ";
            getline(cin, keluhan);
            cout << "Masukkan Nomor Antrian: ";
            cin >> no_antrian;
            sisipPasien(namaPasien, keluhan, no_antrian);
            break;

            case 2:
            tampilkanDariAwal();
            break;

            case 3:
            tampilkanDariAkhir();
            break;

            case 4:
            cout << "Masukkan Nomor Antrian: ";
            cin >> no_antrian;
            cariPasien(no_antrian);
            break;

            case 5:
            cout << "Masukkan Nomor Antrian: ";
            cin >> no_antrian;
            hapusPasien(no_antrian);
            break;

            case 6:
            logout = true;
            cout << "Terimakasih telah menggunakan layanan kami!" << endl;
            break;
            
            default: 
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (!logout);

    return 0;
}
