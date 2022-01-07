#ifndef ODEV3_H_INCLUDED
#define ODEV3_H_INCLUDED

#endif // ODEV3_H_INCLUDED


typedef struct node{//NODE YAPISI
    struct node* B; //Backward nodu
    struct node* F; //Forward nodu
//ogrenciNo,Adi,Soyadi,Bolumu ve Sinifi
    float ogrNo;
    char ogrAd[20];
    char ogrSoyad[20];
    char ogrBolum[30];
    int ogrSinif;

}NODE;

typedef struct plist{//LISTE YAPISI
    int elemanSayisi;
    NODE* head;
    NODE* rear;
}LIST;








