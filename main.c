//140202014 Sevgi Alkan-160202097 Gülnihan Berberoğlu
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>


int main()
{
    // uygulama calisma suresi icin tanimlamalar..
    struct timeval start, stop;
    double saniye = 0;
    gettimeofday(&start, NULL);

    int karakter=0;
    int satirSayisi=0;

    FILE *dosya;

    // dosyayy sadece okuma modunda aciyoruz
    dosya = fopen("ogrenci_kayit_bilgileri.txt", "r");

    //dosyanin sonuna gelinceye kadar devam et
    while(!feof(dosya))
    {
        karakter = fgetc(dosya); // dosyadan bir karakter oku
        if(karakter == '\n') // eger karakter bir alt satira gecme karakteri ise  satir sayisini bir arttir.
        {
            satirSayisi++;
        }
    }

    fclose(dosya);  // satir sayisi bulma asamasinda dosya bozulmamasy icin kapat.

    int dosya_uzunluk = --satirSayisi; // satir sayisi bir fazla ciktigi icin bir eksiltip degiskene esitle.

    char Ad[dosya_uzunluk][20];
    char Soyad[dosya_uzunluk][20];
    char OgrNo[dosya_uzunluk][15];
    char KayitSirasi[dosya_uzunluk][5];
    char OgretimTuru[dosya_uzunluk][5];

    dosya = fopen("ogrenci_kayit_bilgileri.txt", "r+");

    int j,i,konrol;
    int secim;
    for(i=0; i<dosya_uzunluk; i++)
    {

        fscanf(dosya,"%s %s %s %s %s", &OgrNo[i], &Ad[i], &Soyad[i], &KayitSirasi[i], &OgretimTuru[i] );

        printf("%10s \t %10s \t %10s \t %5s \t %10s\n", OgrNo[i], Ad[i], Soyad[i], KayitSirasi[i], OgretimTuru[i] );
    }
        do{
    printf("Kayit Eklemek Ystiyor Musunuz(1-Evet/2-Hayyr)\n");
    scanf("%d", &secim);
    if(secim == 2)
    {
        break;
    }
    printf("Kayit Ekleme Y?lemi:\n");
    printf("Numara:\n");
    scanf("%s",OgrNo);
    printf("Ysim:\n");
    scanf("%s", Ad);
    printf("Soyad:\n");
    scanf("%s", Soyad);
    printf("Kayyt Sirasi:\n");
    scanf("%s", KayitSirasi);
    printf("Ogretim Turu:\n");
    scanf("%s", OgretimTuru);
    fseek(dosya, 0, SEEK_END);
    fprintf(dosya,"%7s \t %15s \t %10s \t %3s \t %5s\n", OgrNo, Ad, Soyad, KayitSirasi, OgretimTuru);

    }while(secim == 1);

    printf("Islemler Var Olan Dosya icin Devam Edecektir..");

    printf("\nTekrar eden ogrenciler silindi");
    printf("\nSilinen Adlar:\n");
    for(i=0; i<dosya_uzunluk; i++)
    {

        for(j=0; j<dosya_uzunluk; j++)
        {

            if( strcmp( Soyad[i],Soyad[j])==0  &&  strcmp(Ad[i],Ad[j])==0 &&  i!=j )
            {

                printf("%s %s\n", Ad[j], Soyad[j]);   // silinen ogrencinin adini ekrana yazdir

                int silinenKayitSirasi = atoi(KayitSirasi[j]);

                // burda tekrar eden ikinci ogrencinin yerine bosluk yazdiriyoruz. (tekrar eden ikinci kaydi sil)
                strcpy(Ad[j]," ");
                strcpy(Soyad[j]," ");
                strcpy(KayitSirasi[j]," ");
                strcpy(OgretimTuru[j]," ");
                strcpy(OgrNo[j]," ");

                if(silinenKayitSirasi!=0)
                {

                    // printf("silinen yeni ogrencinin sirasi : %d\n",silinenKayitSirasi);
                    int z;
                    for( z = 0 ; z<dosya_uzunluk; z++)
                    {

                        //--------------------------------------------------------------------
                        // silinen ogrencilerden sonra kayit siralarini guncelliyoruzz.
                        int silinenKayittanBuyukSira  = atoi(KayitSirasi[z]);
                        if(silinenKayittanBuyukSira > silinenKayitSirasi)
                        {

                            //gecici string degerini tanimladik.
                            //gecici str degiskenine gecici
                            sprintf(KayitSirasi[z], "%d", (silinenKayittanBuyukSira-1));
                            // printf("sonra :%s\n" , KayitSirasi[z]);
                        }

                        //---------------------------------------------------------------------------------

                        //degisen kayit sira ogrenci numarasina gore ogrenci numarasi olmayan ogrencilere numara veriyoruz.
                        if( strcmp("-", OgrNo[z] ) == 0 )
                        {

                            strcpy(OgrNo[z], "170" );

                            strcat(OgrNo[z], OgretimTuru[z] );

                            int geciciSira = strlen(KayitSirasi[z]);

                            switch(geciciSira)
                            {
                            case 3 :
                                strcat(OgrNo[z], KayitSirasi[z]);
                                break;
                            case 2 :
                                strcat(OgrNo[z], "0");
                                strcat(OgrNo[z], KayitSirasi[z]);
                                break;
                            case 1 :
                                strcat(OgrNo[z], "00");
                                strcat(OgrNo[z], KayitSirasi[z]);
                                break;
                            }


                            // printf("%s\n",OgrNo[z]);
                        }
                        //---------------------------------------------------------------------------------
                    }
                }

            }
        }
    }

    //Son olarak  isime gore siralanan ogrencileri , numara sirasina gore siralama yapiliyor..
    for(i=0; i<dosya_uzunluk; i++)
    {
        for( j = i+1; j < dosya_uzunluk; j++)
        {

            if( OgrNo[i] != " " && strcmp( OgrNo[i], OgrNo[j]) < 0 )
            {


                char gecici[1][10];


                strcpy(gecici,OgrNo[j]);
                strcpy(OgrNo[j],OgrNo[i]);
                strcpy(OgrNo[i],gecici);

                strcpy(gecici,Ad[j]);
                strcpy(Ad[j],Ad[i]);
                strcpy(Ad[i],gecici);

                strcpy(gecici,Soyad[j]);
                strcpy(Soyad[j],Soyad[i]);
                strcpy(Soyad[i],gecici);

                strcpy(gecici,KayitSirasi[j]);
                strcpy(KayitSirasi[j],KayitSirasi[i]);
                strcpy(KayitSirasi[i],gecici);

                strcpy(gecici,OgretimTuru[j]);
                strcpy(OgretimTuru[j],OgretimTuru[i]);
                strcpy(OgretimTuru[i],gecici);
            }

        }

    }
    fclose(dosya);

    FILE *yeni, *sinif1ogr1,*sinif1ogr2 ;
    yeni=fopen("ogrenci_kayit_bilgileri_yeni.txt","w");
    sinif1ogr1=fopen("sinif1ogr1.txt","w");
    sinif1ogr2=fopen("sinif1ogr2.txt","w");
    int sinif1ogr1_sayac = 0;
    int sinif1ogr2_sayac = 0;

    int sinif1ogr1_sayac1 = 0;
    int sinif1ogr2_sayac1 = 0;

    for(i=0; i<dosya_uzunluk; i++)
    {
        printf("%7s \t %15s \t %10s \t %3s \t\t %5s\n", OgrNo[i], Ad[i], Soyad[i], KayitSirasi[i], OgretimTuru[i]);
        fprintf(yeni,"%7s \t %15s \t %10s \t %3s \t %5s\n", OgrNo[i], Ad[i], Soyad[i], KayitSirasi[i], OgretimTuru[i]);

        if(atoi(OgretimTuru[i]) == 1)
        {

            fprintf(sinif1ogr1,"%7s \t %15s \t %10s \t %3s \t %5s\n", OgrNo[i], Ad[i], Soyad[i], KayitSirasi[i],OgretimTuru[i]);
            sinif1ogr1_sayac++;//esit dagilimda kullandigimiz 1.ogr ogrenci sayisi
            sinif1ogr1_sayac1++;//en az dagilimda kullandigimiz 1.ogr ogrenci sayisi
        }
        else if(atoi(OgretimTuru[i]) == 2)
        {

            fprintf(sinif1ogr2,"%7s \t %15s \t %10s \t %3s \t %5s\n", OgrNo[i], Ad[i], Soyad[i], KayitSirasi[i], OgretimTuru[i]);
            sinif1ogr2_sayac++;//esit dagilimda kullandigimiz 2.ogr ogrenci sayisi
            sinif1ogr2_sayac1++;//en az dagilimda kullandigimiz 2.ogr ogrenci sayisi
        }
    }


    int sinif_sayisi;
    printf("Sinif Sayisini Giriniz: \n");
    scanf("%d", &sinif_sayisi);
    int sinif_kapasitesi[sinif_sayisi];
    printf("\nSinif Kapasitelerini Giriniz:\n");

    for(i = 0; i < sinif_sayisi; i++)
    {

        //sinif kapasiteleri alinip diziye konuyor
        scanf("%d", &sinif_kapasitesi[i]);
    }

    printf("Dersi alan ogrenci sayisi:\n1. ogretim: %d \n2. ogretim: %d 'dir.", sinif1ogr1_sayac, sinif1ogr2_sayac);

    int gecici;
    printf("\nEsit Dagilim:\n");
    for(i = 0; i < sinif_sayisi - 1; i++)
    {

        //kucukten buyuge siraladik kapasiteleri
        for(j = i + 1; j < sinif_sayisi; j++)
        {
            if(sinif_kapasitesi[i] >= sinif_kapasitesi[j])
            {
                gecici = sinif_kapasitesi[i]; // Dizi[i] yi kaybetmemek için gecicide tutuyoruz
                sinif_kapasitesi[i] = sinif_kapasitesi[j]; //dizi[i] yi dizi[i] den daha küçük olan dizi[j] kaydediyoruz
                sinif_kapasitesi[j] = gecici; // Dizi[j] ye ise dizi[i] degerini kaydediyoruz. Bu degeri gecicide saklamistik
            }
        }
    }
    printf("\n1. ogretim - ");
    int sayac = 0;
    int esit_dagilim = 0;
    esit_dagilim = sinif1ogr1_sayac / sinif_sayisi;
    for(i = 0; i < sinif_sayisi; i++)
    {
        if(esit_dagilim >= sinif_kapasitesi[i])
        {
            printf("%d ", sinif_kapasitesi[i]);
            sinif1ogr1_sayac -= sinif_kapasitesi[i];
        }
        else
        {
            sayac++;
        }

    }
    //(1.ogrtimler için kalan ögrencileri siniflara esit olarak bölme islemini yaptik
    for(i = 0; i < sayac; i++)
    {

        printf("%d ", (sinif1ogr1_sayac/sayac));
    }

    printf("\n2. ogretim - ");
    sayac = 0;
    esit_dagilim = 0;
    esit_dagilim = sinif1ogr2_sayac / sinif_sayisi;
    for(i = 0; i < sinif_sayisi; i++)
    {

        if(esit_dagilim >= sinif_kapasitesi[i])
        {

            printf("%d ", sinif_kapasitesi[i]);
            sinif1ogr2_sayac -= sinif_kapasitesi[i];
        }
        else
        {
            sayac++;
        }
    }
    //(1.ögrtimler için kalan ögrencileri siniflara esit olarak bölme islemini yaptik
    for(i = 0; i < sayac; i++)
    {
        printf("%d ", (sinif1ogr2_sayac/sayac));
    }


    printf("\nEn az sinif dagilimi:\n");
    printf("1. ogretim - ");
    for(i = 0; i < sinif_sayisi; i++)
    {
        if(sinif_kapasitesi[i] <= sinif1ogr1_sayac1)
        {
            //(1.ögrtimler için) sinif kapasitesi ögrenci sayisindan kucuk olanlari olanlari ilk basta doldurup kalan ögrenciler için ayni kontrolü gerçeklestirdik
            printf("%d ", sinif_kapasitesi[i]);
            sinif1ogr1_sayac1 -= sinif_kapasitesi[i];
        }
        else
        {
            //(1.ögretimler için) kapasiteden kucuk olan ögrencileri de son olarak doldurduk
            printf("%d ", sinif1ogr1_sayac1);
            sinif1ogr1_sayac1 = 0;
        }
    }
    printf("\n2. ogretim - ");
    for(i = 0; i < sinif_sayisi; i++)
    {

        if(sinif_kapasitesi[i] <= sinif1ogr2_sayac1)
        {
            //(2.ögrtimler için) sinif kapasitesi ögrenci sayisindan kucuk olanlari ilk basta doldurup kalan ögrenciler için ayni kontrolü gerçeklestirdik
            printf("%d ", sinif_kapasitesi[i]);
            sinif1ogr2_sayac1 -= sinif_kapasitesi[i];
        }
        else
        {
            //(2.ögretimler için) kapasiteden kucuk olan ögrencileri de son olarak
            printf("%d ", sinif1ogr2_sayac1);
            sinif1ogr2_sayac1 = 0;
        }
    }

    fclose(yeni);

    //calisma suresinin  hesaplanip ekrana yazdirilmasi
    gettimeofday(&stop, NULL);
    saniye = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nUygulamanin saniye cinsinden calisma suresi  %f\n",saniye);

    return 0;
}
