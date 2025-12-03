#include <iostream>
#include <string>
using namespace std;

struct tiketing {
    char nama[50];
    long long id;
    int kategori; // 0 = vip, 1 = reguler
};

const int MAX_VIP = 30;
const int MAX_REGULER = 70;

void tampilkanmenu() {
    cout << endl << "==== Manajemen Data Tiketing ====" << endl;
    cout << "1. Tambah Item" << endl;
    cout << "2. Tampilkan Semua Item" << endl;
    cout << "3. Lihat Stock Tiket" << endl;
    cout << "4. Sorting Data" << endl;
    cout << "5. Searching Data" << endl;
    cout << "6. Transfer Tiket" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilihan: ";
}

void tambahItem(tiketing data[], int &jumlah_item) {
    if (jumlah_item >= 50) {
        cout << "Data penuh!" << endl;
        return;
    }
    
    cout << "Masukkan Nama: ";
    cin.ignore();
    cin.getline(data[jumlah_item].nama, 50);
    
    // Validasi nama tidak boleh mengandung angka
    bool ada_angka = false;
    for (int i = 0; data[jumlah_item].nama[i] != '\0'; i++) {
        if (data[jumlah_item].nama[i] >= '0' && data[jumlah_item].nama[i] <= '9') {
            ada_angka = true;
            break;
        }
    }
    
    if (ada_angka) {
        cout << "Error! Nama tidak boleh mengandung angka!" << endl;
        return;
    }
    
    cout << "Masukkan ID (harus 4 angka): ";
    cin >> data[jumlah_item].id;
    
    // Validasi ID harus 4 angka (1000-9999)
    if (data[jumlah_item].id < 1000 || data[jumlah_item].id > 9999) {
        cout << "Error! ID harus tepat 4 angka (1000-9999)!" << endl;
        return;
    }
    
    // Validasi ID tidak boleh sama
    for (int i = 0; i < jumlah_item; i++) {
        if (data[i].id == data[jumlah_item].id) {
            cout << "Error! ID sudah digunakan!" << endl;
            return;
        }
    }
    
    cout << "Kategori (0=VIP, 1=Reguler): ";
    cin >> data[jumlah_item].kategori;
    
    // Validasi kategori harus 0 atau 1
    if (data[jumlah_item].kategori != 0 && data[jumlah_item].kategori != 1) {
        cout << "Error! Kategori hanya boleh 0 (VIP) atau 1 (Reguler)!" << endl;
        return;
    }
    
    // Hitung jumlah tiket VIP dan Reguler yang sudah ada
    int count_vip = 0, count_reguler = 0;
    for (int i = 0; i < jumlah_item; i++) {
        if (data[i].kategori == 0) {
            count_vip++;
        } else {
            count_reguler++;
        }
    }
    
    // Validasi kapasitas stock
    if (data[jumlah_item].kategori == 0 && count_vip >= MAX_VIP) {
        cout << "Error! Tiket VIP sudah penuh (maksimal " << MAX_VIP << " tiket)!" << endl;
        return;
    }
    
    if (data[jumlah_item].kategori == 1 && count_reguler >= MAX_REGULER) {
        cout << "Error! Tiket Reguler sudah penuh (maksimal " << MAX_REGULER << " tiket)!" << endl;
        return;
    }
    
    jumlah_item++;
    cout << "Data berhasil ditambahkan!" << endl;
}

void tampilkanSemua(tiketing data[], int jumlah_item) {
    if (jumlah_item == 0) {
        cout << "Tidak ada data!" << endl;
        return;
    }
    
    cout << "\n==== Data Tiketing ====" << endl;
    for (int i = 0; i < jumlah_item; i++) {
        cout << "Item " << i + 1 << endl;
        cout << "Nama: " << data[i].nama << endl;
        cout << "ID: " << data[i].id << endl;
        cout << "Kategori: " << (data[i].kategori == 0 ? "VIP" : "Reguler") << endl;
        cout << "---" << endl;
    }
}

void lihatStock(tiketing data[], int jumlah_item) {
    int count_vip = 0, count_reguler = 0;
    
    for (int i = 0; i < jumlah_item; i++) {
        if (data[i].kategori == 0) {
            count_vip++;
        } else {
            count_reguler++;
        }
    }
    
    cout << "\n==== Stock Tiket ====" << endl;
    cout << "Tiket VIP:" << endl;
    cout << "  Terisi: " << count_vip << " / " << MAX_VIP << endl;
    cout << "  Tersisa: " << (MAX_VIP - count_vip) << endl;
    cout << "\nTiket Reguler:" << endl;
    cout << "  Terisi: " << count_reguler << " / " << MAX_REGULER << endl;
    cout << "  Tersisa: " << (MAX_REGULER - count_reguler) << endl;
}

void sortingData(tiketing data[], int jumlah_item) {
    if (jumlah_item == 0) {
        cout << "Tidak ada data untuk disortir!" << endl;
        return;
    }
    
    int pilihan_sort;
    cout << "\n==== Pilihan Sorting ====" << endl;
    cout << "1. Sorting berdasarkan Nama (A-Z)" << endl;
    cout << "2. Sorting berdasarkan ID (Ascending)" << endl;
    cout << "Pilihan: ";
    cin >> pilihan_sort;
    
    tiketing temp;
    
    if (pilihan_sort == 1) {
        // Bubble Sort berdasarkan Nama
        for (int i = 0; i < jumlah_item - 1; i++) {
            for (int j = 0; j < jumlah_item - i - 1; j++) {
                // Membandingkan nama menggunakan strcmp
                bool tukar = false;
                int k = 0;
                while (data[j].nama[k] != '\0' && data[j + 1].nama[k] != '\0') {
                    if (data[j].nama[k] > data[j + 1].nama[k]) {
                        tukar = true;
                        break;
                    } else if (data[j].nama[k] < data[j + 1].nama[k]) {
                        break;
                    }
                    k++;
                }
                
                if (tukar) {
                    temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
        cout << "Data berhasil disortir berdasarkan Nama!" << endl;
        
    } else if (pilihan_sort == 2) {
        // Bubble Sort berdasarkan ID
        for (int i = 0; i < jumlah_item - 1; i++) {
            for (int j = 0; j < jumlah_item - i - 1; j++) {
                if (data[j].id > data[j + 1].id) {
                    temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
        cout << "Data berhasil disortir berdasarkan ID!" << endl;
        
    } else {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }
    
    // Tampilkan data setelah sorting
    cout << "\n==== Data Setelah Sorting ====" << endl;
    for (int i = 0; i < jumlah_item; i++) {
        cout << "Item " << i + 1 << endl;
        cout << "Nama: " << data[i].nama << endl;
        cout << "ID: " << data[i].id << endl;
        cout << "Kategori: " << (data[i].kategori == 0 ? "VIP" : "Reguler") << endl;
        cout << "---" << endl;
    }
}

void searchingData(tiketing data[], int jumlah_item) {
    if (jumlah_item == 0) {
        cout << "Tidak ada data untuk dicari!" << endl;
        return;
    }
    
    int pilihan_search;
    cout << "\n==== Pilihan Searching ====" << endl;
    cout << "1. Searching berdasarkan Nama" << endl;
    cout << "2. Searching berdasarkan ID" << endl;
    cout << "Pilihan: ";
    cin >> pilihan_search;
    
    bool ditemukan = false;
    
    if (pilihan_search == 1) {
        char cari_nama[50];
        cout << "Masukkan Nama yang dicari: ";
        cin.ignore();
        cin.getline(cari_nama, 50);
        
        cout << "\n==== Hasil Pencarian ====" << endl;
        for (int i = 0; i < jumlah_item; i++) {
            // Membandingkan nama (case sensitive)
            bool cocok = true;
            int j = 0;
            while (cari_nama[j] != '\0' || data[i].nama[j] != '\0') {
                if (cari_nama[j] != data[i].nama[j]) {
                    cocok = false;
                    break;
                }
                if (cari_nama[j] == '\0' && data[i].nama[j] == '\0') {
                    break;
                }
                j++;
            }
            
            if (cocok) {
                cout << "Data Ditemukan!" << endl;
                cout << "Nama: " << data[i].nama << endl;
                cout << "ID: " << data[i].id << endl;
                cout << "Kategori: " << (data[i].kategori == 0 ? "VIP" : "Reguler") << endl;
                cout << "---" << endl;
                ditemukan = true;
            }
        }
        
        if (!ditemukan) {
            cout << "Data dengan nama \"" << cari_nama << "\" tidak ditemukan!" << endl;
        }
        
    } else if (pilihan_search == 2) {
        long long cari_id;
        cout << "Masukkan ID yang dicari: ";
        cin >> cari_id;
        
        cout << "\n==== Hasil Pencarian ====" << endl;
        for (int i = 0; i < jumlah_item; i++) {
            if (data[i].id == cari_id) {
                cout << "Data Ditemukan!" << endl;
                cout << "Nama: " << data[i].nama << endl;
                cout << "ID: " << data[i].id << endl;
                cout << "Kategori: " << (data[i].kategori == 0 ? "VIP" : "Reguler") << endl;
                cout << "---" << endl;
                ditemukan = true;
                break;
            }
        }
        
        if (!ditemukan) {
            cout << "Data dengan ID " << cari_id << " tidak ditemukan!" << endl;
        }
        
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
}

void transferTiket(tiketing data[], int jumlah_item) {
    if (jumlah_item == 0) {
        cout << "Tidak ada data untuk ditransfer!" << endl;
        return;
    }
    
    long long id_tiket;
    cout << "\n==== Transfer Tiket ====" << endl;
    cout << "Masukkan ID tiket yang akan ditransfer: ";
    cin >> id_tiket;
    
    // Cari tiket dengan ID
    int index = -1;
    for (int i = 0; i < jumlah_item; i++) {
        if (data[i].id == id_tiket) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        cout << "Error! Tiket dengan ID " << id_tiket << " tidak ditemukan!" << endl;
        return;
    }
    
    // Tampilkan data tiket lama
    cout << "\nData Tiket Saat Ini:" << endl;
    cout << "Nama: " << data[index].nama << endl;
    cout << "ID: " << data[index].id << endl;
    cout << "Kategori: " << (data[index].kategori == 0 ? "VIP" : "Reguler") << endl;
    
    // Input nama pemilik baru
    char nama_baru[50];
    
    cout << "\nMasukkan Nama Pemilik Baru: ";
    cin.ignore();
    cin.getline(nama_baru, 50);
    
    // Validasi nama tidak boleh mengandung angka
    bool ada_angka = false;
    for (int i = 0; nama_baru[i] != '\0'; i++) {
        if (nama_baru[i] >= '0' && nama_baru[i] <= '9') {
            ada_angka = true;
            break;
        }
    }
    
    if (ada_angka) {
        cout << "Error! Nama tidak boleh mengandung angka!" << endl;
        return;
    }
    
    // Update nama tiket
    for (int i = 0; nama_baru[i] != '\0' || i < 50; i++) {
        data[index].nama[i] = nama_baru[i];
        if (nama_baru[i] == '\0') break;
    }
    
    cout << "\nTiket berhasil ditransfer!" << endl;
    cout << "\nData Tiket Setelah Transfer:" << endl;
    cout << "Nama: " << data[index].nama << endl;
    cout << "ID: " << data[index].id << endl;
    cout << "Kategori: " << (data[index].kategori == 0 ? "VIP" : "Reguler") << endl;
}

int main() {
    tiketing konser[50];
    int jumlah_item = 0;
    int pilihan;
    
    do {
        tampilkanmenu();
        cin >> pilihan;
        
        switch (pilihan) {
            case 1: tambahItem(konser, jumlah_item); break;
            case 2: tampilkanSemua(konser, jumlah_item); break;
            case 3: lihatStock(konser, jumlah_item); break;
            case 4: sortingData(konser, jumlah_item); break;
            case 5: searchingData(konser, jumlah_item); break;
            case 6: transferTiket(konser, jumlah_item); break;
            case 0: cout << "Keluar....." << endl; break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 0);
    
    return 0;
}
