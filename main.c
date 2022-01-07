#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "odev3.h"


/*""
1– Create link list
2– Destroy linked list
3– Add node
4– Delete node
5– Search node
6– Display list (traverse list)
0- Stop
Öðrenci No
Ad
Soyad
Bölüm
Sniff
""*/

LIST* createList();//Bir bos bir liste olusturup geri dondurulur
NODE* createNode();//Yeni bir node olusturmak için kullanılır

void destroyList(LIST* pList);//Parametre olarak verilen listeyi yok eder
bool addNode(LIST* pList);//Listeye yeni bir node yani ogrenci eklenir
void deleteNode(LIST* pList,NODE* silinecekNode, float sOgrenciNo);//Key olarak silmek istedigimiz ogrencinin numarasi ile ogrenci bulup silinir
bool searchNode(LIST* pList,NODE* arananNode, float ogrenciNo);//Listede aramak istedigimiz bir ogrencinin numarasını alıp arastırma islemi gerceklestirir
void displayList(LIST* pList);//Liste bulunan ogrencilerin bilgilerini yazdırılır
bool fullListTest(LIST* List);//Liste dolu olup olmadigini kontrolu gerceklestirir
    float numara;
    int sinif;
    char ad[20], soyad[20], bolum[30];

int main()
{
    //Menuyu kullanıcıya sunulur
    printf("'1'\t-->Create Link List\n'2'\t-->Destroy Linked List\n'3'\t-->Add Node\n'4'\t-->Delete Node\n'5'\t-->Search Node\n'6'\t-->Display List\n'0'\t-->Cikis Icin\n\n");

    int secim = -1;
    float ogrenciNo;
    bool found;
    int ogrenciSayisi;

    int sayac = 0;

    LIST* pList;
    NODE* arananNode;
    NODE* newNode;




    while(secim!=0){//Stop istenildiğine kadar calışır
        printf("\nNe yapmak Istersiniz'1,2,3,4,5,6,0'? \n");
        scanf("%d",&secim);

        switch(secim){//Kullanıcının yapmak isteigine göre islem devam eder
            case 1://Yeni bir liste olusturmak icin
                pList = createList();
                break;

            case 2://Listeyi yok etmek için
                destroyList(pList);
                break;

            case 3://Listeye yeni bir node veya yeni ogrenci eklemek için
                printf("\nKac Ogrenci Girmek Istersiniz? \n");
                scanf("%d",&ogrenciSayisi);

                for(int i=0;i<ogrenciSayisi;i++){
                    addNode(pList);
                }
                /*while(sayac != ogrenciSayisi){//Kullanıcının eklemek istedigi ogrenci sayısına bagamlı olarak ekleme gerceklestirilir
                    addNode(pList);
                    sayac++;
                }*/
                break;

            case 4://Bir ogrenci silmek için
                printf("\nSilmek Istediginiz Ogrencinin Numarasini Giriniz: ");
                scanf("%f",&ogrenciNo);
                newNode = (NODE*)malloc(sizeof(NODE));

                deleteNode(pList,newNode,ogrenciNo);

                break;

            case 5://Bir ogrenci aramak için
                printf("\nAramak Istediginiz Ogrencinin Numarasini Giriniz: ");
                scanf("%f",&ogrenciNo);

                arananNode = (NODE*)malloc(sizeof(NODE));
                found = searchNode(pList,arananNode,ogrenciNo);
                if(found == true){
                    printf("\nAranan Ogrenci Bilgileri: ");
                    printf("Ad: %s\tSoyad: %s\tBolum: %s\tNo: %.0f\tSinif: %d\n",arananNode->ogrAd,arananNode->ogrSoyad,arananNode->ogrBolum,arananNode->ogrNo,arananNode->ogrSinif);
                }
                else{
                    printf("\nGirilen ogrenci numarasina ait bir ogrenci 'bulumamaktadir'!\n");
                }

                break;

            case 6://Ogrenci bilgileri yazdırmak için
                displayList(pList);
                break;

            case 0://Programı sonlandırmak için
                secim = 0;
                break;

        }

    }

    printf("Program sonlandirildi!!!");


    return 0;
}


LIST* createList(){ //1-Create link list
    LIST* pList;
    pList = (LIST*)malloc(sizeof(LIST));

    if(pList == NULL)//Bellek tahsisi olmadıysa NULL dondurdun
        return NULL;
    else{
        pList->elemanSayisi = 0;
        pList->head = NULL;
        pList->rear = NULL;

        printf("\nBos Bir Liste Olusturulmus!!!\n");
    }

    return pList;
}
bool searchNode(LIST* pList,NODE* arananNode, float arananOgrenciNo){ //5– Search node
    NODE* testNode;
    testNode = pList->head;

    //Arama işlemi listenin başıyla başlayarak sonuna kadar arama olur
    while(testNode != NULL){

        if(testNode->ogrNo == arananOgrenciNo){
            arananNode->ogrNo = testNode->ogrNo;
            arananNode->ogrSinif = testNode->ogrSinif;
            strcpy(arananNode->ogrAd,testNode->ogrAd);
            strcpy(arananNode->ogrSoyad,testNode->ogrSoyad);
            strcpy(arananNode->ogrBolum,testNode->ogrBolum);
            arananNode->B = testNode->B;
            arananNode->F = testNode->F;

            return true;//Girien ogrenci numarasına ait liste bir ogrenci var
        }
        else{
            testNode = testNode->F;//Bir sonraki dugme gecsin... sonuna kadar
        }

    }
    return false;//Girien ogrenci numarasına ait listede bir ogrenci bulunmamatadir
}
bool fullListTest(LIST* pList){
    NODE* pNew;
    pNew = (NODE*)malloc(sizeof(NODE));
    if(pNew)
        return false;//Liste dolu degil
    else
        return true;
}

bool addNode(LIST* pList){ //3– Add node
    bool found;
    NODE* newNode;

    if(fullListTest(pList))//Liste dolu ekleme olmasın
        return false;

    newNode = createNode(newNode);

    found = searchNode(pList,newNode,newNode->ogrNo);
    if(found == false){//Listede ayni ogrenci yok yani bir ogrenci listede birden fazla bulunmaz
        if(pList->elemanSayisi == 0){//Bos listeye ekleme islemi gerceklesir
            newNode->B = NULL;
            newNode->F = NULL;
            pList->rear = newNode;
        }
        else{//Bos olmayan listeye ekleme
            newNode->F = pList->head;
            pList->head->B = newNode;
        }

        pList->head = newNode;
        (pList->elemanSayisi)++;
        return true;
    }
    else//Eklemek istedigimiz ogrenci listede var zaten
        return false;

}

void deleteNode(LIST* pList,NODE* silinecekNode, float sOgrenciNo){ //4– Delete node
    NODE* pPre;
    NODE* pSucc;
    bool found;

    found = searchNode(pList,silinecekNode,sOgrenciNo);//Silmek istenildigi ogrenci listede var mı yok mu?
    if(found == true){
        if(silinecekNode->B != NULL){
        pPre = silinecekNode->B;
        pPre->F = silinecekNode->F;
        }
        else{
            pList->head = pList->head->F;
        }

        if(silinecekNode->F != NULL){
            pSucc = silinecekNode->F;
            pSucc->B = silinecekNode->B;
        }
        else{
            pList->rear = pList->rear->B;
        }

        free(silinecekNode);//Tahsis edildigi bellek alanı serbest birakılır
        pList->elemanSayisi = (pList->elemanSayisi)-1;

        printf("\nGirilen Ogrenci Numarasina ait olan Ogrenci Basariyla Silinmistir!!!\n");
    }
    else{
        printf("\nGirilen Ogrenci Numarasina ait bir ogrenci Bulunmamaktadir!!!\n");
    }


}

void displayList(LIST* pList){ //6– Display list (traverse list)
    NODE* headNode;
    headNode = pList->head;
    int sayac = 1;
    printf("\n******************************Bilgileri Yazdirilir...******************************\n\n");
    if(pList->elemanSayisi == 0)
        printf("Bos Bir Liste!!!");
    else{
        printf("Listede %d ogrenci bulunmaktadir.\n",pList->elemanSayisi);
        while(headNode != NULL){
            printf("%d. Ogrencinin Bilgileri: \n",sayac);
            printf("Ad: %s\tSoyad: %s\tBolum: %s\tSinif: %d\tOgrenciNo: %.0f\n",headNode->ogrAd,headNode->ogrSoyad,headNode->ogrBolum,headNode->ogrSinif,headNode->ogrNo);
            headNode = headNode->F;
            sayac = sayac+1;
        }
    }

}

void destroyList(LIST* pList){ //2– Destroy linked list
    NODE* testNode;
    NODE* temp;
    testNode = pList->head;

    while(testNode != NULL){
        temp = testNode;
        testNode = testNode->F;
        free(temp);
    }
    //Tahsis edildigi bellek alanı serbest bırakılır
    free(testNode);
    free(pList);

    printf("\nOlusturulmus Girilen Listeyi Yok Edildi!!!\n");
}


NODE* createNode(NODE* newNode){//Yeni bir node olusturan
    newNode = (NODE*)malloc(sizeof(NODE));

    printf("\nOgrenci  NO Ad Soyad Bolum Sinif Giriniz: ");
    scanf("%f %s %s %s %d",&(numara),ad,soyad,bolum,&(sinif));


    newNode->ogrNo = numara;
    newNode->ogrSinif = sinif;

    strcpy(newNode->ogrAd,ad);
    strcpy(newNode->ogrSoyad,soyad);
    strcpy(newNode->ogrBolum,bolum);
    newNode->B = NULL;
    newNode->F = NULL;

    return newNode;
}





