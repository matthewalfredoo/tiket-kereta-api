#ifndef KERETA_API_HEADER
#define KERETA_API_HEADER

#define strlength 100
#define banyakKelas 3
#define modalKereta 3500000
#define declareString (char *) malloc (strlength * sizeof(char))

typedef struct SKelas Kelas;
typedef struct SKeretaApi KA;
typedef struct SLinkedList LinkedList;

float pendapatan;

struct SKelas{
    char * nama;
    int daya_tampung;
    int daya_tampung_dipesan;
    float harga;
    int status60persen;
};


struct SKeretaApi{
    char * kode_kereta;
    char * destinasi;
    char * jam_keberangkatan;
    Kelas penumpang[banyakKelas];
    KA * nextKA;
};

struct SLinkedList{
    KA * head;
};

// void declareKelas(Kelas *K, char *nama, int daya_tampung, int dipesan, float harga);

/* Mengalokasikan kelas pada struct SKeretaApi */
Kelas declareKelas(int jenis);

/* Mengalokasikan memori tipe data turunan SKeretaApi */
KA * newKeretaApi (char * kode_kereta, char * destinasi, char * jam);

/* Menambahkan kereta baru pada LinkedList yang ada */
void TambahKereta(LinkedList * L, KA * kereta);

/* Menampilkan data per Kelas Penumpang */
void CetakInformasiKelas(Kelas K);

/* Traversal LinkedList menampilkan informasi masing-masing kereta */
void CetakInformasiKereta(LinkedList * L);

/* Menampilkan hanya data kode dan destinasi kereta */
void CetakPerInformasiSimple(LinkedList * L);

/* Menampilkan data per kereta */
void CetakPerInformasi(KA * kereta);

/* Mengurangi Daya Tampung Kelas karena pembelian tiket */
Kelas KurangDayaTampung(Kelas K, int banyak_tiket);

/* Membeli tiket dengan mengurangi jumlah daya tampung kelas */
void BeliTiket(LinkedList * L, char * kode, int pilihKelas, int banyak_tiket);

/* Mencari data kereta berdasarkan Kode Kereta */
int CariKereta(LinkedList * L, char * kode);

/* Mencari sisa kuota daya tampung suatu kelas */
int CariSisaTampung(Kelas K, int banyak_tiket);

/* Mencari suatu kelas dalam struct SKeretaApi */
int CariKelas(KA * kereta, int pilihKelas, int banyak_tiket);

/* Memperbaiki inputan yang mungkin tidak tepat, dikhususkan untuk inputan destinasi saat mencari destinasi */
char * FixInput (char * c);

/* Mencari data kereta berdasarkan Destinasi */
void CariKeretaDestinasi(LinkedList * L, char * destinasi);

/* Menampilkan pendapatan keseluruhan serta untung atau ruginya */
void CetakPendapatan();

/* Menentukan harga masing-masing kelas */
void TentukanHargaKelas(Kelas * K);

#endif