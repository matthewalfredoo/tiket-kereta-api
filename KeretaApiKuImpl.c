#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "KeretaApiKuHeader.h"

Kelas declareKelas(int jenis){
    Kelas K;
    K.nama = declareString;
    K.daya_tampung_dipesan = 0;
    K.status60persen = 0; // artinya kelas secara default tidak berstatus penumpang >= 60% kuota kelas
    switch (jenis)
    {
    case 0:
        strcpy(K.nama, "Biasa");
        K.daya_tampung = 100;
        K.harga = 20000;
        break;
    
    case 1:
        strcpy(K.nama, "Bisnis");
        K.daya_tampung = 50;
        K.harga = 35000;
        break;

    case 2:
        strcpy(K.nama, "Eksekutif");
        K.daya_tampung = 30;
        K.harga = 60000;
        break;

    default:
        break;
    }
    return K;
}

void CetakInformasiKelas(Kelas K){
    printf("Nama Kelas\t\t: %s\n", K.nama);
    printf("Harga Kelas\t\t: Rp. %.0f ", K.harga);
    if(K.status60persen == 1){
        printf(" => Harga naik 20%%, karena kuota yang dipesan sudah lebih dari 60%%");
    }
    printf("\n");
    printf("Daya Tampung Kelas\t: %d\n", K.daya_tampung);
    printf("Kuota tersisa\t\t: %d\n", (K.daya_tampung - K.daya_tampung_dipesan));
    printf("\n");
}

KA * newKeretaApi (char * kode_kereta, char * destinasi, char * jam){
    KA * kereta = (KA *) malloc (1 * sizeof(KA));
    kereta->kode_kereta = declareString;
    kereta->destinasi = declareString;
    kereta->jam_keberangkatan = declareString;
    
    strcpy(kereta->kode_kereta, kode_kereta);
    strcpy(kereta->destinasi, destinasi);
    strcpy(kereta->jam_keberangkatan, jam);
    int i;
    for(i = 0; i < banyakKelas; i++){
        kereta->penumpang[i] = declareKelas(i);
    }
    kereta->nextKA = NULL;

    return kereta;
}

void CetakPerInformasiSimple(LinkedList * L){
    KA * temp = L->head;
        
    printf("============================================\n");
    while(temp != NULL){
        printf("Kode Kereta: %s\t Destinasi: %s\n", temp->kode_kereta, temp->destinasi);
        printf("============================================\n");

        temp = temp->nextKA;
    }
}

void CetakPerInformasi(KA * kereta){
    int i;
    printf("===========================================\n");
    printf("Kode Kereta\t\t: %s\n", kereta->kode_kereta);
    printf("Destinasi Kereta\t: %s\n", kereta->destinasi);
    printf("Jam Keberangkatan\t: %s\n\n", kereta->jam_keberangkatan);
    printf("Informasi kelas untuk Kereta kode \"%s\"\n\n", kereta->kode_kereta);
    for(i = 0; i < banyakKelas; i++){
        printf("----- %d ------\n", (i+1));
        CetakInformasiKelas(kereta->penumpang[i]);
    }
    printf("===========================================\n");
}

void CetakInformasiKereta(LinkedList * L){
    KA *kereta = L->head;

    while (kereta != NULL){
        CetakPerInformasi(kereta);
        kereta = kereta->nextKA;
    }
    printf("\n");
}

void TambahKereta(LinkedList * L, KA * kereta){
    KA *temp = L->head;

    while(temp->nextKA != NULL){
        temp = temp->nextKA;
    }

    kereta->nextKA = NULL;
    temp->nextKA = kereta;
}

Kelas KurangDayaTampung(Kelas K, int banyak_tiket){
    K.daya_tampung_dipesan += banyak_tiket;
    
    float income = K.harga * banyak_tiket; //Pendapatan dari hasil penjualan tiket
    pendapatan += income;    
    return K;
}

void BeliTiket(LinkedList * L, char * kode, int pilihKelas, int banyak_tiket){
    pilihKelas--; //Karena ketika user memasukkan n, yang user maksudkan adalah n-1
    KA *temp = L->head;
    KA *kereta;

    while (temp != NULL){
        if(strcmp(temp->kode_kereta, kode) == 0){
            kereta = temp;
            break;
        }
        temp = temp->nextKA;
    }

    CariKelas(temp, pilihKelas, banyak_tiket);
}

int CariKelas(KA * kereta, int pilihKelas, int banyak_tiket){
    int i, exist = 0;
    for(i = 0; i < banyakKelas; i++){
        if(strcmp(kereta->penumpang[i].nama, kereta->penumpang[pilihKelas].nama) == 0){
            exist = 1;
        }
    }
    
    if(exist == 1){
        if(CariSisaTampung(kereta->penumpang[pilihKelas], banyak_tiket) == 0){
            printf("Kuota kelas sudah memenuhi atau banyak tiket yang Anda pesan melebihi sisa kuota untuk kelas \"%s\" pada kereta dengan kode \"%s\".\n", kereta->penumpang[pilihKelas].nama, kereta->kode_kereta);
            return 0;
        }

        Kelas beli_temp = kereta->penumpang[pilihKelas];
        beli_temp = KurangDayaTampung (beli_temp, banyak_tiket);

        kereta->penumpang[pilihKelas] = beli_temp;

        TentukanHargaKelas(&kereta->penumpang[pilihKelas]); //Mengirim alamat

        printf("\nStatus terbaru kereta dengan kode \"%s\" untuk kelas \"%s\" \n", kereta->kode_kereta, kereta->penumpang[pilihKelas].nama);
        CetakInformasiKelas(kereta->penumpang[pilihKelas]);
    }

    if(exist == 0){
        printf("Tidak ditemukan kelas dengan pilihan \"%d\" pada Kereta dengan Kode \"%s\"\n", pilihKelas, kereta->kode_kereta);
        printf("Pembelian tiket untuk kelas yang tidak ditemukan sebanyak %d tiket dibatalkan\n", banyak_tiket);
    }
}

void TentukanHargaKelas(Kelas * K){
    float dayaTampungPersen60 = 0.6 * (float) K->daya_tampung;
    
    float hargaPersen20 = 0.2 * K->harga;

    if(K->status60persen == 0 && K->daya_tampung_dipesan >= dayaTampungPersen60){
        K->harga += hargaPersen20;
        K->status60persen = 1;
    }
}

int CariSisaTampung(Kelas K, int banyak_tiket){
    int daya_tampung_sisa = K.daya_tampung - K.daya_tampung_dipesan;

    if(K.daya_tampung_dipesan == K.daya_tampung || banyak_tiket > daya_tampung_sisa ){
        return 0;
    }
}

int CariKereta(LinkedList * L, char * kode){
    KA *temp = L->head;

    while (temp != NULL){
        if(strcmp(temp->kode_kereta, kode) == 0){
            CetakPerInformasi(temp);
            break;
        }
        temp = temp->nextKA;
    }
    if(temp == NULL){
        printf("Kereta dengan kode \"%s\" tidak ditemukan\n", kode);
        return 0;
    }
    return 1;
}

char * FixInput(char * c){
    int i;
    c[0] = toupper(c[0]);
    
    for(i = 1; i < strlen(c); i++){
        c[i] = tolower(c[i]);
    }
    return c;
}

void CariKeretaDestinasi(LinkedList * L, char * destinasi){
    destinasi = FixInput(destinasi);

    KA *temp = L->head;

    while (temp != NULL){
        if(strcmp(temp->destinasi, destinasi) == 0){
            CetakPerInformasi(temp);
            break;
        }
        temp = temp->nextKA;
    }
    if(temp == NULL){
        printf("Kereta dengan destinasi ke \"%s\" tidak ditemukan\n", destinasi);
    }
}

void CetakPendapatan(){
    printf("Pendapatan Stasiun melalui keberangkatan hari ini adalah : Rp%.0f\n", pendapatan);
    
    float hasil_akhir;
    if (pendapatan > modalKereta){
        hasil_akhir = pendapatan - modalKereta;
        printf("Mendapatkan keuntungan, dengan jumlah keuntungannya adalah Rp%.0f\n", hasil_akhir);
    }
    
    if(pendapatan < modalKereta){
        hasil_akhir = modalKereta - pendapatan;
        printf("Mengalami kerugian, dengan total kerugian adalah Rp%.0f\n", hasil_akhir);
    }

    if(pendapatan == modalKereta){
        hasil_akhir = 0;
        printf("Tidak mendapatkan keuntungan maupun kerugian\n");
    }
}
