#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct personel
{
    char isim[100];
    char TCKimlikNo[12];
    char telefon[12];
    char eposta[100];
    char adres[100];
 }per;

int kayitsayisi=0;
void kayitSay();
void secimYap();
void kayitEkle();
void kayitListele();
void kayitDuzenle(char isim[]);
void TCileBul(char tc[]);
void IsimileBul(char isim[]);
void kayitSil(char siltc[]);

int main()
{
    setlocale(LC_ALL, "Turkish");
    kayitSay();
    secimYap();
    return 0;
}

void kayitSay()
{
    FILE *fp;
    fp= fopen("personel.txt","rb");
    if(fp != NULL)
    {
        int sayac=0, kayit=0;
        while((fgetc(fp))!=EOF)
        {
            sayac++;
         if(sayac==sizeof(per))
         {
             kayit++;
             sayac=0;
         }
        }
        kayitsayisi=kayit;

        if(kayitsayisi<=0)
            printf("Kay�t Bulunamadi! Lutfen Yeni Personel Ekleyin!\n");
        else
            printf("%d adet Personel kayd� bulundu!\n",kayitsayisi);

    }
    else
    {
        printf("Dosya Bulunamadi!\n");
    }
    fclose(fp);

}

void secimYap()
{
    char aranantc[12];
    char arananisim[100];
    char duzenleisim[100];
    char silinecektc[12];

    printf("\n\n----��LEMLER----\n");
    printf("[1] Kay�t Ekle\n");
    printf("[2] Personel Listele\n");
    printf("[3] Kayd� D�zenle\n");
    printf("[4] TC Kimlik No ile Kay�t Bul\n");
    printf("[5] �sim ile Kay�t Bul\n");
    printf("[6] Kay�t Sil\n");
    printf("[0] ��k��\n\n");

    printf("L�tfen Se�im Yap�n�z >>> ");
    int secim;
    scanf("%d",&secim);

    switch(secim)
    {
        case 0:
            printf("G�le g�le");
            exit(1); break;
        case 1:
            kayitEkle(); break;
        case 2:
            if(kayitsayisi!=0)
            {
                kayitListele();
            }
            else
            {
                system("CLS");
                printf("Personel Kayd� Bulunamad�. Lutfen Kay�t Yap�n�z!\n\n");
                secimYap();
            }
            break;
        case 3:
            printf("L�tfen D�zenlenecek Kayda ait �sim giriniz >>> ");
            scanf("%s",duzenleisim);
            kayitDuzenle(duzenleisim);
            break;
        case 4:
            printf("L�tfen Aranacak TC giriniz >>> ");
            scanf("%s",aranantc);
            TCileBul(aranantc);
            break;
        case 5:
            printf("L�tfen Aranacak �sim giriniz >>> ");
            scanf("%s",arananisim);
            IsimileBul(arananisim);
            break;
        case 6:
            printf("L�tfen Silinecek TC giriniz >>> ");
            scanf("%s",silinecektc);
            kayitSil(silinecektc);
            break;
        default:
                printf("HATA: Bilinmeyen bir de�er girdiniz!\n");
    }
}

void kayitEkle()
{
    system("CLS"); //ekran temizler

    FILE *fp;

    if((fp=fopen("personel.txt","a+")) != NULL)
    {
        kayitsayisi++;

        printf("L�tfen Personel ismini Giriniz >>> ");
        scanf("%s",per.isim);

        printf("L�tfen Personel TCKN Giriniz >>> ");
        scanf("%s",per.TCKimlikNo);

        printf("L�tfen Personel Telefon Giriniz >>> ");
        scanf("%s",per.telefon);

        printf("L�tfen Personel ePosta Giriniz >>> ");
        scanf("%s",per.eposta);

        printf("L�tfen Personel Adres Giriniz >>> ");
        scanf("%s",per.adres);

        fwrite(&per, sizeof(per), 1, fp);

        fclose(fp);

        system("CLS");
        printf("Personel Kayd� Ba�ar�yla Tamamland�!\n\n");

        kayitSay();
        secimYap();




    }
}

void kayitListele()
{
        system("CLS");

        printf("*Personel Kay�tlar�*\n\n");

        FILE *fp;
        fp = fopen("personel.txt","rb");

        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
             printf("�sim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");
        }
        fclose(fp);

        kayitSay();
        secimYap();
}

void kayitDuzenle(char isim[100])
{
        system("CLS");
        FILE *fp;
        fp = fopen("personel.txt","rb");

        int sayac=0,bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            sayac++;
            if(strcmp(isim, per.isim)==0)
            {
                bulunansayisi++;
             printf("**** Bulunan Kay�t ****\n");
             printf("�sim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

             }

            if (bulunansayisi==1)
            {
                break;
            }
        }
        fclose(fp);

        if(bulunansayisi<=0)
        {
            system("CLS");
            printf("Aranan �sim kayd� bulunamad�. D�zenlemek i�in Yeniden �sim ile Arama Yapmak �stermisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                char duzenlenecekisim[100];
                printf("\nL�tfen D�zenlenecek Kayda ait �sim giriniz >>> ");
                scanf("%s",duzenlenecekisim);
                kayitDuzenle(duzenlenecekisim);
            }
        }
        else if (bulunansayisi==1)
        {
            printf("Bulunan Kayd� D�zenlemek �stedi�inize Eminmisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                //D�zenleme ��lemi Ba�

                FILE *fp;
                fp = fopen("personel.txt","rb+");

                printf("\n\nL�tfen Personelin YEN� ismini Giriniz >>> ");
                scanf("%s",per.isim);

                printf("\nL�tfen Personelin YEN� TCKN Giriniz >>> ");
                scanf("%s",per.TCKimlikNo);

                printf("\nL�tfen Personelin YEN� Telefon Giriniz >>> ");
                scanf("%s",per.telefon);

                printf("\nL�tfen Personelin YEN� ePosta Giriniz >>> ");
                scanf("%s",per.eposta);

                printf("\nL�tfen Personelin YEN� Adres Giriniz >>> ");
                scanf("%s",per.adres);


                fseek(fp, (sayac - 1) * sizeof(per), SEEK_SET); // imleci ilgili kay�ta getirdik.

                fwrite(&per, sizeof(per), 1, fp); // bas

                fclose(fp);


                //D�zenleme ��lemi Son

                system("CLS");
                kayitSay();
                printf("\n %s isimli personel kayd� ba�ar�yla d�zenlenmi�tir!",isim);

            }
        }
        secimYap();
}

void TCileBul(char tc[12])
{
        system("CLS");

        FILE *fp;
        fp = fopen("personel.txt","rb");

        int bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            if(strcmp(tc, per.TCKimlikNo)==0)
            {
                bulunansayisi++;
            printf("****Bulunan Kay�t****\n");
             printf("�sim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

            }
        }
        if(bulunansayisi<=0)
        {
            printf("Aranan TC kayd� bulunamad�!");
        }

        fclose(fp);
        secimYap();
}

void IsimileBul(char isim[100])
{
        system("CLS");

        FILE *fp;
        fp = fopen("personel.txt","rb");
        int bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            if(strcmp(isim, per.isim)==0)
            {
                bulunansayisi++;
            printf("****%d. Bulunan Kay�t****\n",bulunansayisi);
             printf("�sim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

            }
        }
        if(bulunansayisi<=0)
            printf("Aranan �sim ile kay�t bulunamad�!");
        else
            printf("Bulunan Toplam Kay�t Say�s�: %d",bulunansayisi);
        fclose(fp);
        secimYap();
}

void kayitSil(char siltc[12])
{
        system("CLS");

        FILE *fp;
        fp = fopen("personel.txt","rb");

        int bulunansayisi=0;
        while((fread(&per, sizeof(per), 1, fp)) !=0)
        {
            if(strcmp(siltc, per.TCKimlikNo)==0)
            {
                bulunansayisi++;
            printf("****Silinecek Kay�t****\n",bulunansayisi);
             printf("�sim: %s\n",per.isim);
             printf("TCKimlikNo: %s\n",per.TCKimlikNo);
             printf("Telefon: %s\n",per.telefon);
             printf("Eposta: %s\n",per.eposta);
             printf("Adres: %s\n",per.adres);
             printf("\n");

            }
        }
        fclose(fp);

        if(bulunansayisi<=0)
        {
            printf("Aranan TC kayd� bulunamad�. Silmek i�in Yeniden TC ile Arama Yapmak �stermisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                char silinecektc[12];
                printf("\nL�tfen TC giriniz >>> ");
                scanf("%s",silinecektc);
                kayitSil(silinecektc);
            }
        }
        else if (bulunansayisi>0)
        {
            printf("Bulunan Kayd� Silmek �stedi�inize Eminmisiniz? (E/H) >>> ");
            if (toupper(getche())=='E')
            {
                //Silme ��lemi Ba�

                FILE *fp;
                fp = fopen("personel.txt","rb");
                FILE *temp;
                temp = fopen("temp.txt","ab+");
                while((fread(&per, sizeof(per), 1, fp)) !=0)
                    {
                        if(strcmp(siltc, per.TCKimlikNo)==0)
                        {
                            continue; // e�er silinecek tc gelirse atla
                        }

                        fwrite(&per, sizeof(per), 1, temp);
                    }

                fclose(temp);
                fclose(fp);
                remove("personel.txt");
                rename("temp.txt","personel.txt");

                //Silme ��lemi Son
                system("CLS");
                kayitSay();
                printf("\n %s nolu TC Kay�tlardan Ba�ar�yla Silinmi�tir!",siltc);
            }
        }
        secimYap();
}
