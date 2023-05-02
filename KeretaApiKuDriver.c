#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeretaApiKuHeader.h"

int main(){
    int i;
    /* Deklarasi Kereta Api */
    LinkedList * L = (LinkedList *) malloc (1 * sizeof(LinkedList));

    KA * kereta1, *kereta2, *kereta3 ;
    
    kereta1 = newKeretaApi("KA-01", "Medan", "12.00 WIB");
    kereta2 = newKeretaApi("KA-02", "Binjai", "13.00 WIB");
    kereta3 = newKeretaApi("KA-03", "Parapat", "17.00 WIB");

    L->head = kereta1;
    TambahKereta(L, kereta2);
    TambahKereta(L, kereta3);

    int pilihMenu;

    char pilihDestinasi [strlength]; // variabel untuk menu pilihan ke-2

    char pilihKodeKereta[strlength]; // variabel untuk menu pilihan ke-3
    int pilihKelas;     // variabel untuk menu pilihan ke-3
    int banyak_tiket;   // variabel untuk menu pilihan ke-3

    printf("====== Sistem Informasi Kereta Api-Ku ======");
    while(1 == 1){
        printf("\nPilih salah satu dari menu berikut\n");
        printf("1. Tampiklkan Semua Informasi Kereta\n");
        printf("2. Cari Kereta Berdasarkan Destinasi\n");
        printf("3. Beli Tiket\n");
        printf("4. Keluar (jika keluar maka seluruh kereta akan dianggap berjalan dan proses penghitungan dana akan dimulai)\n");

        scanf("%d", &pilihMenu);
        printf("\n");
        switch (pilihMenu){
        case 1:
            CetakInformasiKereta(L);
            break;

        case 2:
            printf("Cari kereta ke tujuan apa?\n");
            scanf (" %[^\t\n]s", pilihDestinasi);
            CariKeretaDestinasi(L, pilihDestinasi);
            break;

        case 3:
            CetakPerInformasiSimple(L);
            printf("Ingin Pesan untuk Kode Kereta Apa? (Inputan harus tepat dengan Kode Kereta dan bersifat case-sensitive)\n");
            scanf (" %[^\t\n]s", pilihKodeKereta);

            if(CariKereta(L, pilihKodeKereta) != 0){
                printf("Kelas Apa? (Pilih berdasarkan nomor Kelas)\n");
                scanf ("%d", &pilihKelas);
                if(!(pilihKelas >= 1 && pilihKelas <= 3)){
                    printf("Tidak tersedia kelas dengan nomor pilihan \"%d\". \n", pilihKelas);
                    break;
                }

                printf("Banyaknya tiket yang akan dipesan?\n");
                scanf("%d", &banyak_tiket);
                if(!(banyak_tiket > 0)){
                    printf("Banyak tiket yang dimasukkan tidak benar.\n");
                    break;
                }
                
                BeliTiket(L, pilihKodeKereta, pilihKelas, banyak_tiket);
            }
            break;

        case 4:
            CetakPendapatan();
            exit(0);
        
        default:
            printf("Pilihan tidak tepat");
            break;
        }
    }

    return 0;
}
