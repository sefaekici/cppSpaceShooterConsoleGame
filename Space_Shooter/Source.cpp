#include <iostream>
#include <Windows.h>

using namespace std;

const int genislik = 80;
const int yukseklik = 20;

const int maxkarakterboyutu = 500; //MERMI,DUSMAN ICIN KULLANILACAK MAKSIMUM URETME MIKTARI.

char pencere[genislik][yukseklik];


const int ucakuzunlugu = 5; //UCAGIN KARAKTER BOYUTUNU BELIRLEYEN SABÝT.
int dusmanuzunlugu = 10;
int mermisayisi = 0;
int dusmansayisi = 0;
int puan = 0;

char sahne[genislik][yukseklik];
char tuslar[256];

int oyun = 1;



//YONLERÝ TUTMAK ICIN KULLANILAN ENUM YAPISI
enum YON
{
	YON_YUKARI = 1,
	YON_ASAGI = 2,
	YON_SAG = 3,
	YON_SOL = 4
};
//UCAK ICIN GEREKLI ELEMANLARI BARINDIRAN STRUCT YAPISI
struct UcakHucre
{
	int x;
	int y;
	YON yon;
	char karakter = 219;

};
//DUSMAN ICIN GEREKLI ELEMANLARI BARINDIRAN STRUCT YAPISI
struct DusmanHucre
{
	int dusman_x;
	int dusman_y;
	YON YON;
	const char dusman_karakter = 219;

};
//MERMI ICIN GEREKLI ELEMANLARI BARINDIRAN STRUCT YAPISI
struct MermiHucre
{
	int mermi_y;
	int mermi_x;
	YON mermi_yon;
	const char mermi_karakteri = 219;
};

//YAPYA UCAKKARAKTERÝN EKLENMESÝ
UcakHucre ucakkarakter[ucakuzunlugu];
//YAPYA MERMÝKARAKTERÝN EKLENMESÝ
DusmanHucre dusmankarakter[maxkarakterboyutu];
//YAPYA MERMÝKARAKTERÝN EKLENMESÝ
MermiHucre mermikarakter[maxkarakterboyutu];

//MAÝN ÝÇÝNDE ÇAÐRILDIÐINDA ÝSTENÝLEN KORDÝNATLARA GÝDEN FONKSÝYON
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}
//MAÝN ÝÇÝNDE ÇAÐRILDIÐINDA SAHNEYÝ ÇÝZMEYE YARAYAN FONKSÝYON
void sahneyi_ciz()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << sahne[x][y];
		}
		cout << endl;
	}
}
//SAHNEDE GEREKLÝ YERLERE GEREKLÝ KARAKTERLERÝ YERLEÞTÝREN FONKSÝYON
void sinirlari_olustur() {

	for (int x = 0; x < genislik; x++) {
		sahne[x][0] = 219;
		sahne[x][yukseklik - 1] = 219;
	}
	for (int y = 0; y < yukseklik; y++) {
		sahne[0][y] = 219;
		sahne[genislik - 1][y] = 219;
	}

}
//KURSORUN ANÝMASYON SIRASINDA GÖRÜNMESÝNÝ ENGELLEYEN FONKSÝYON
void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
//SAHNEDE OLUÞAN VE HAREKET EDEN CÝSÝMLERÝN ÝZLERÝNÝ SÝLMEK ÝÇÝN KULLANILAN FONKSÝYON
void sahneyitemizle() {
	for (int y = 0; y < yukseklik; y++) {
		for (int x = 0; x < genislik; x++) {
			sahne[x][y] = ' ';
		}

	}
}
//TUSLARIN SENKRON BÝR BÝÇÝMDE KULLANICIDAN ALINMASINI SAGLAYAN FONKSÝYON
void klavye_oku(char tuslar[]) {
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
}

//UCAGIN YON DURUMUNA GÖRE KORDÝNATLARINDAKÝ DEGÝSÝMÝ BELÝRLEYEN FONKSÝYON
void ucagý_hareket_ettir() {

	for (int i = 0; i < ucakuzunlugu; i++) {
		switch (ucakkarakter[i].yon) {
		case YON_YUKARI:

			ucakkarakter[i].y--;
			break;

		case YON_ASAGI:
			ucakkarakter[i].y++;
			break;
		}
	}
}
//MERMÝNÝN SAHNENÝN NERESÝNDE OLUSACAGINI BELÝRLEYEN FONKSÝYON
void mermiolustur() {

	mermikarakter[mermisayisi].mermi_x = ucakkarakter[2].x + 1;
	mermikarakter[mermisayisi].mermi_y = ucakkarakter[2].y;
	mermisayisi++;
}

//KLAVYENÝN TUSLARININ NE YAPMASI GEREKTÝGÝNÝ BELÝRLEYEN FONKSÝYON
void klavye_kontrol()
{
	if (tuslar['W'] != 0)
	{
		for (int i = 0; i < ucakuzunlugu; i++) {
			ucakkarakter[i].yon = YON_YUKARI;
		}
		if (ucakkarakter[0].y > 0)
			ucagý_hareket_ettir();
	}


	if (tuslar['S'] != 0)
	{

		for (int i = 0; i < ucakuzunlugu; i++) {
			ucakkarakter[i].yon = YON_ASAGI;
		}
		if (ucakkarakter[4].y < yukseklik - 1)
			ucagý_hareket_ettir();
	}


	if (tuslar['P'] != 0)
	{
		mermiolustur();
	}
}

//UCAGIN SAHNEDEKÝ KORDÝNATLARINI BELÝRLEYEN FONKSÝYON
void ucak_olustur()
{
	ucakkarakter[0].x = 1;
	ucakkarakter[0].y = 1;
	ucakkarakter[1].x = 2;
	ucakkarakter[1].y = 2;
	ucakkarakter[2].x = 3;
	ucakkarakter[2].y = 3;
	ucakkarakter[3].x = 2;
	ucakkarakter[3].y = 4;
	ucakkarakter[4].x = 1;
	ucakkarakter[4].y = 5;


}
//KORDÝNATLARI BELÝRLENEN UCAGIN SAHNEYE YERLESTÝRÝLMESÝ
void ucagý_sahneye_yerlestir()
{
	for (int i = 0; i < ucakuzunlugu; i++) {
		int x = ucakkarakter[i].x;
		int y = ucakkarakter[i].y;
		sahne[x][y] = ucakkarakter[i].karakter;

	}
}

//KORDÝNATLARI BELÝRLENEN MERMININ SAHNEYE YERLESTÝRÝLMESÝ
void mermiyi_sahneye_yerlestir()
{

	for (int i = 0; i < mermisayisi; i++) {
		if (mermikarakter[i].mermi_x == genislik || mermikarakter[i].mermi_x == 0) {
			mermikarakter[i].mermi_x = 0;
			mermikarakter[i].mermi_y = yukseklik;
		}

		else {
			int x = mermikarakter[i].mermi_x;
			int y = mermikarakter[i].mermi_y;
			sahne[x][y] = mermikarakter[i].mermi_karakteri;
		}

	}
}
//MERMÝNÝN DURUMUNA GÖRE MERMÝYÝ SAHNEDE HAREKET ETTÝREN FONKSÝYON 
void mermiyi_hareket_ettir()
{

	for (int i = 0; i < mermisayisi; i++) {
		if (mermikarakter[i].mermi_x != genislik && mermikarakter[i].mermi_x != 0)
			mermikarakter[i].mermi_x++;

		if (mermikarakter[i].mermi_x == 0)
			mermikarakter[i].mermi_x = 0;
	}
}

//DUSMANIN RANDOM BÝR ÞEKÝLDE OLUSTURULMASI 
void dusman_olustur()
{

	int dusmany = 1 + rand() % 17;

	dusmankarakter[dusmansayisi].dusman_x = 81;
	dusmankarakter[dusmansayisi].dusman_y = dusmany;
	dusmansayisi++;

}
//DUSMANIN BUTUN HUCRELERININ AYNI ANDA HAREKET ETMESÝNÝ SAGLAYAN FONKSIYON 
void dusmani_hareket_ettir() {
	for (int i = 0; i < dusmansayisi; i++) {

		if (dusmankarakter[i].dusman_x == 0)
		{
			dusmankarakter[i].dusman_x = 0;
			dusmankarakter[i].dusman_y = 0;
		}
		else
			dusmankarakter[i].dusman_x--;
	}
}
//KORDINATLARI RANDOM SAYESÝNDE BELÝRLENEN DUSMANIN SAHNEYE YERLESMESINI SAGLAYAN FONKSIYON
void dusmani_sahneye_yerlestir() {
	for (int i = 0; i < dusmansayisi; i++) {

		if (dusmankarakter[i].dusman_x != 0)
		{
			int x = dusmankarakter[i].dusman_x;
			int y = dusmankarakter[i].dusman_y;

			sahne[x][y] = dusmankarakter[i].dusman_karakter;
			sahne[x][y + 1] = dusmankarakter[i].dusman_karakter;
			sahne[x + 1][y] = dusmankarakter[i].dusman_karakter;
			sahne[x + 1][y + 1] = dusmankarakter[i].dusman_karakter;
		}


	}
}
//DUSMAN ILE MERMININ KORDINATLARININ BIRBIRINE GORE DURUMUNU INCELEYEN FONKSIYON
void carpisma()
{
	for (int i = 0; i < dusmansayisi; i++)
		for (int j = 0; j < mermisayisi; j++)
			if (dusmankarakter[i].dusman_x == mermikarakter[j].mermi_x && dusmankarakter[i].dusman_y == mermikarakter[j].mermi_y ||
				dusmankarakter[i].dusman_x == mermikarakter[j].mermi_x && dusmankarakter[i].dusman_y + 1 == mermikarakter[j].mermi_y)
			{
				dusmankarakter[i].dusman_x = 0;
				dusmankarakter[i].dusman_y = 0;
				mermikarakter[i].mermi_x = yukseklik;
				mermikarakter[i].mermi_y = genislik;
				puan++;
			}
}
//UCAK ILE DUSMANIN KORDINATLARINI BIRBIRINE GORE INCELEYEN VE DEGER DONDUREN FONKSIYON
bool ucakcarpisma() {

	for (int i = 0; i < ucakuzunlugu; i++) {
		for (int j = 0; j < dusmansayisi; j++) {

			if (ucakkarakter[i].x == dusmankarakter[j].dusman_x && ucakkarakter[i].y == dusmankarakter[j].dusman_y ||
				ucakkarakter[i].x == dusmankarakter[j].dusman_x && ucakkarakter[i].y == dusmankarakter[j].dusman_y + 1
				)
			{
				oyun = 0;
			}
		}

	}
	return oyun;
}

int main()
{
	kursoruGizle();
	ucak_olustur();

	//SUREKLI DUSMAN GELMESINI ENGELLEMEK ICIN MOD KONTROLUNDE KULLANILACAK DEGISKEN
	int dusmanuret = 0;


	while (oyun) {



		sahneyitemizle();
		sinirlari_olustur();
		klavye_oku(tuslar);
		klavye_kontrol();

		ucagý_sahneye_yerlestir();
		mermiyi_sahneye_yerlestir();


		//DUSMAN URETME ARALIGINI BELIRLEYEN KONTROL DURUMU 
		if (dusmanuret % 25 == 0)
			dusman_olustur();

		dusmani_hareket_ettir();
		carpisma();
		dusmani_sahneye_yerlestir();
		mermiyi_hareket_ettir();

		carpisma();
		gotoxy(0, 0);

		oyun = ucakcarpisma();
		sahneyi_ciz();

		dusmanuret++;
	}


	system("cls");
	gotoxy(genislik / 2, yukseklik / 2);
	cout << "  GAME OVER..." << endl;
	gotoxy(genislik / 2, (yukseklik / 2) + 1);
	cout << "  PUANINIZ:" << puan << endl;
	cout << '\n';


	system("pause");
}