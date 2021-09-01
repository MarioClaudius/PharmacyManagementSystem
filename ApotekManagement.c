#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct akun								//Linked List & Stack
{
	char id[100];
	char pass[10];
	struct akun *next;
};

struct Obat								//Linked List & Stack
{
	int data;
	char nama[20];
	char guna[20];
	int jumlah;
	struct Obat *next; 
};

struct keranjang						//Linked List & Queue
{
	char nama[20];
	int jumlah;
	int harga;
	struct keranjang *next;
};

void DisplayTanggal(int waktu[6]);
void print_jam(int time[6]);
void tampilan_awal(int waktu[6]);
void menu_utama(int waktu[6]);
void menu_host(int waktu[6]);
void menu_user(int waktu[6]);
void menu_bantuan();
void menu_daftar();
void menu_sorting();
void konversi(char kata[20]);
void search_obat();
void tambah_obat();
void printDaftarObat();
void sort_penyakit();
void sort_obat();
void sort_harga();
void ubahDaftarObat();
void tambah_stok();
void search_penyakit();
void menu_searching();
void menu_ubahDaftarObat();
void menu_kurangObat();
void beli_obat();
void printKeranjang();
void hapusKeranjang();
void simpanFile();
void InputPassword(char input[10]);
void tambahHost();
void gantiPass(int waktu[6]);
void printTiket();
void swap(struct Obat *a, struct Obat *b);

struct akun *first = NULL;
struct Obat *pertama = NULL;
struct keranjang *head = NULL;
struct keranjang *tail = NULL;

char usName[10];								//digunakan untuk membantu ganti password dari username tertentu

int main()
{
	FILE *ptr = fopen ("Daftar_obat.txt", "r");								//Pembacaan file .txt
	int data, count=0, i;
	char nama[20], guna[20], id[10], pass[10];
	int jumlah;
	int waktu[6];
	
	while(fscanf(ptr, "%s\t%s\t%d\t%d\n", nama, guna, &jumlah, &data)!=EOF)			//Pembacaan file .txt. EOF = End of File
	{ 
		struct Obat *new = (struct Obat*) malloc(sizeof(struct Obat)); 
		strcpy (new->nama, nama);
		strcpy (new->guna, guna);
		new->jumlah = jumlah;
		new->data = data;
		new->next = pertama;
		pertama = new;
   	} 
   	fclose(ptr);
   	
   	FILE *hostPtr = fopen ("Daftar_host.txt", "r");							//Pembacaan file .txt
	
	while(fscanf(hostPtr, "%s\t%s\n", id, pass)!=EOF)							//Pembacaan file .txt. EOF = End of File
	{ 
		struct akun *newHost = (struct akun*) malloc(sizeof(struct akun)); 
		strcpy (newHost->id, id);
		strcpy (newHost->pass, pass);
		newHost->next = first;
		first = newHost;
   	} 
   	fclose(hostPtr);
   	
	tampilan_awal(waktu);
	menu_utama(waktu);
	simpanFile();
	
	exit(1);
	return 0;
}

void tampilan_awal(int waktu[6])
{
	int i;
	system("color F0");//bright white, black
	DisplayTanggal(waktu);
	printf("\n__________________________________________________________________");
	printf("\n||\t\t\t\t\t\t\t\t||");
	printf("\n||\t\t\tApotek Management\t\t\t||");
	printf("\n||______________________________________________________________||");
	printf("\n\n\t\tProgram ini dibuat oleh: \t\t");
	printf("\n\t\t     Mario Claudius\t\t");
	printf("\n\t\t     Tedi Setiawan\t\t\n\n");
	printf("NOW LOADING");
	for (i=0;i<3;i++)
	{
		printf(".");
		sleep(1);
	}
	system("cls");
}

void menu_utama(int waktu[6])
{	
	char pil[10];
	int menu = 0;
	
 	while(menu != 4)
 	{
	 	system("color B0");//light aqua, black
	 	DisplayTanggal(waktu);												//tanggal selalu di display / di refresh setiap kembali ke menu ini
	 	printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t  Selamat Datang di Menu Utama  \t\t||");
	 	printf("\n||______________________________________________________________||");
	    printf("\n||   Menu:\t\t\t\t\t\t\t||");
	    printf("\n||\t1. Host\t\t\t\t\t\t\t||");
	    printf("\n||\t2. User\t\t\t\t\t\t\t||");
	    printf("\n||\t3. Bantuan\t\t\t\t\t\t||");
	    printf("\n||\t4. Keluar\t\t\t\t\t\t||");
	    printf("\n||______________________________________________________________||");
	   	printf("\n\nPilihan: ");
	    scanf("%s", pil);
	    menu = atoi(pil);
	    system("cls");
	    switch (menu)
	    {
		    case 1: menu_host(waktu);break;
		    case 2: menu_user(waktu); break;
		    case 3: menu_bantuan(); break;
		    case 4: printf("\nTerima kasih telah menggunakan program kami\n\a"); break;
		    default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;
	    }
 	}
}

void menu_host(int waktu[6])
{
	char pil[10], id[10], pass[10], username[10], password[10];
	int menu, benar, i;
   	system("color 0F");//black, white
   	struct akun *check = first;
   	printf("Masukkan Id & Password!\n");
   	printf("Id: ");
   	scanf("%s", username);
   	printf("Password: ");
   	InputPassword(password);
   	system("cls");
   	
   	while(check!=NULL)																//Loop linked list akun yang datanya diambil dari file .txt
   	{																				//yang berisi username dan password
   		if(strcmp(username, check->id)==0 && strcmp(password, check->pass)==0)
   		{												//usName merupakan variabel global yang dipake untuk function gantiPass
   			strcpy(usName, username);
   			benar=1;									//flag tanda jika username dan password yang diinput user sesuai dengan
		}												//data username dan password di file .txt Data host
		check = check->next;
	}
	
	if(benar==1)								//Jika username dan password benar
	{
		printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t    Kamu masuk sebagai host   \t\t\t||");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||______________________________________________________________||\n\nNOW LOADING");
	 	for(i=0;i<3;i++)
	 	{
	 		printf(".");
	 		sleep(1);					//delay 1 detik
		}
		system("cls");
		while(menu!=5)
		{
			system("color e0");//light yellow, black
			DisplayTanggal(waktu);
			printf("\n__________________________________________________________________");
		 	printf("\n||\t\t\t\t\t\t\t\t||");
		 	printf("\n||\t\t  Selamat Datang di Menu Host  \t\t\t||");
		 	printf("\n||______________________________________________________________||");
		    printf("\n||   Menu:\t\t\t\t\t\t\t||");
		    printf("\n||\t1. Daftar obat\t\t\t\t\t\t||");
		    printf("\n||\t2. Ubah daftar Obat\t\t\t\t\t||");
		    printf("\n||\t3. Ganti password\t\t\t\t\t||");
		    printf("\n||\t4. Buat akun host baru\t\t\t\t\t||");
		    printf("\n||\t5. Log out\t\t\t\t\t\t||");
		    printf("\n||______________________________________________________________||");
		    printf("\n\nPilihan: ");
		    scanf("%s", pil);
			menu = atoi(pil);
		    system("cls");
		   	switch (menu)
			{
			    case 1: printDaftarObat(); getch(); system("cls"); break;
			    case 2: menu_ubahDaftarObat(); break;
			    case 3: gantiPass(waktu); break;
			    case 4: tambahHost(); break;
			    case 5: break;
			    default : printf("Masukkan input yang benar\n\n"); break;
			}
		}
	}
	else					//Jika username dan password salah
	{
		printf("Username atau Password Salah!!");
		sleep(1);
		system("cls");
		return(menu_utama(waktu));
	}	
}

void menu_user(int waktu[6])
{
	char pil[10];
	int i, menu = 0;
 	system("color 0F");//black, white
    printf("\n__________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t||");
 	printf("\n||\t\t\t\t\t\t\t\t||");
 	printf("\n||\t\t   Kamu masuk sebagai user   \t\t\t||");
 	printf("\n||\t\t\t\t\t\t\t\t||");
 	printf("\n||______________________________________________________________||\n\nNOW LOADING");
 	for(i=0;i<3;i++)
 	{
 		printf(".");
 		sleep(1);					//delay 1 detik
	}
	system("cls");
	while(menu != 5)
	{
		system("color e0");//light yellow, black
	 	DisplayTanggal(waktu);
	 	printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t  Selamat Datang di Menu User  \t\t\t||");
	 	printf("\n||______________________________________________________________||");
	    printf("\n||   Menu:\t\t\t\t\t\t\t||");
	    printf("\n||\t1. Lihat Daftar dan Beli Obat\t\t\t\t||");
	    printf("\n||\t2. Lihat Keranjang\t\t\t\t\t||");
	    printf("\n||\t3. Hapus item pertama keranjang\t\t\t\t||");
	    printf("\n||\t4. Print Tiket\t\t\t\t\t\t||");
	    printf("\n||\t5. Kembali ke menu utama\t\t\t\t||");
	    printf("\n||______________________________________________________________||");
	    printf("\n\nPilihan: ");
	    scanf("%s", pil);
	    menu = atoi(pil);
	    system("cls");
	    switch (menu)
	    {
	    	case 1: menu_daftar() ;break;
	      	case 2: printKeranjang(); break;
	      	case 3: hapusKeranjang(); break;
	      	case 4: printTiket(); break;
	      	case 5: break;
			default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;				//error handling
	    }
	}
}

void menu_daftar()
{
	int menu;
	char pil[10];
	while (menu!=4)
	{
		printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t  Selamat Datang di Menu Daftar Obat  \t\t||");
	 	printf("\n||______________________________________________________________||");
	    printf("\n||   Menu:\t\t\t\t\t\t\t||");
	    printf("\n||\t1. Sorting\t\t\t\t\t\t||");
	    printf("\n||\t2. Searching\t\t\t\t\t\t||");
	    printf("\n||\t3. Beli Obat\t\t\t\t\t\t||");
	    printf("\n||\t4. Kembali ke menu user\t\t\t\t\t||");
	    printf("\n||______________________________________________________________||");
	    printf("\n\nPilihan: ");
	    scanf("%s", pil);
	    menu = atoi(pil);
	    system("cls");
	    switch(menu)
	    {
	    	case 1: menu_sorting(); break;
	    	case 2: menu_searching(); break;
	    	case 3: beli_obat(); break;
	    	case 4: break;
	    	default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;
		}
	}	
}

void menu_sorting()								
{
	int menu;
	char pil[10];
	while (menu!=4)
	{
		printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t  Selamat Datang di Menu Sorting  \t\t||");
	 	printf("\n||______________________________________________________________||");
	    printf("\n||   Menu:\t\t\t\t\t\t\t||");
	    printf("\n||\t1. Sort Obat\t\t\t\t\t\t||");
	    printf("\n||\t2. Sort Penyakit\t\t\t\t\t||");
	    printf("\n||\t3. Sort Harga\t\t\t\t\t\t||");
	    printf("\n||\t4. Kembali ke menu daftar obat\t\t\t\t||");
	    printf("\n||______________________________________________________________||");
	    printf("\n\nPilihan: ");
	    scanf("%s", pil);
	    menu = atoi(pil);
	    system("cls");
	    switch(menu)
	    {
	    	case 1: sort_obat(); printDaftarObat(); getch(); system("cls"); break;
	    	case 2: sort_penyakit(); printDaftarObat(); getch(); system("cls"); break;
	    	case 3: sort_harga(); printDaftarObat(); getch(); system("cls"); break;
	    	case 4: break;
	    	default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;
		}
	}
}

void menu_searching()
{
	int menu;
	char pil[10];
	while (menu!=3)
	{
		printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t  Selamat Datang di Menu Searching  \t\t||");
	 	printf("\n||______________________________________________________________||");
	    printf("\n||   Menu:\t\t\t\t\t\t\t||");
	    printf("\n||\t1. Search Obat\t\t\t\t\t\t||");
	    printf("\n||\t2. Search Penyakit\t\t\t\t\t||");
	    printf("\n||\t3. Kembali ke menu daftar obat\t\t\t\t||");
	    printf("\n||______________________________________________________________||");
	    printf("\n\nPilihan: ");
	    scanf("%s", pil);
	    menu = atoi(pil);
	    system("cls");
	    switch(menu)
	    {
	    	case 1: search_obat(); break;
	    	case 2: search_penyakit(); break;
	    	case 3: break;
	    	default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;
		}
	}
}
void menu_bantuan()
{
	printf("\n__________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t||");
 	printf("\n||                        Bantuan                               ||");
 	printf("\n||______________________________________________________________||\n");
 	printf("\nPada program ini terdapat menu untuk 2 jenis user yaitu Host dan User (Guest)\n");
 	printf("\nUntuk mengakses menu host diperlukan username dan password yang sesuai dengan database\n");
 	printf("Sedangkan untuk mengakses menu user (Guest) tidak diperlukan syarat apapun\n");
 	printf("Pada menu host, terdapat beberapa menu, yaitu :\n");
 	printf("1. Daftar Obat = Host dapat melihat daftar obat yang ada di database\n");
 	printf("2. Ubah Daftar Obat = Host dapat mengubah data obat di database (mengupdate stok,menambah jenis obat baru dan menghapus jenis obat dari data base)\n");
 	printf("3. Ganti Password = Host dapat mengganti password lama usernamenya dengan password baru\n");
 	printf("4. Buat akun host baru = Host juga dapat membuat akun host baru\n\n");
 	printf("Pada menu user, terdapat beberapa menu, yaitu : \n");
 	printf("1. Lihat daftar dan beli obat = User dapat melihat daftar obat yang tersedia dan memesan obat\n");
 	printf("   Pada menu ini, terdapat fitur sorting dan searching yang dapat membantu user mencari obat yang diinginkan\n");
 	printf("2. Lihat keranjang = User dapat melihat daftar item yang telah dipesan\n");
 	printf("3. Hapus item pertama keranjang = User dapat menghapus item paling atas di keranjang\n");
 	printf("4. Print tiket = User dapat print tiket pemesanan yang berisikan daftar item yang ada di keranjang sebelumnya\n");
 	getch();
	system("cls");
}

void DisplayTanggal(int waktu[6])					//function untuk menampilkan tanggal, data tanggal yang valid akan diambil nilai awalnya dari sini
{
	int i;
	char w[9], t[9];
	char jam[2];
	char menit[2];
	char tanggal[2];
	char bulan[2];
	char tahun[2];
	_strdate(w);  //Memasukkan tanggal hari ini ke array dalam bentuk mm/dd/yy
	_strtime(t);
	for(i=0;i<2;i++)
	{
		tanggal[i] = w[3+i];
	}
	waktu[0] = atoi(tanggal);
	for(i=0;i<2;i++)
	{
		bulan[i] = w[i];
	}
	waktu[1] = atoi(bulan);
	for(i= 0;i<2;i++)
	{
		tahun[i] = w[6+i];
	}
	waktu[2] = 2000 + atoi(tahun);
	printf( "Tanggal (dd/mm/yy): %d/%d/%d", waktu[0], waktu[1], waktu[2]);
	for(i=0;i<2;i++)
	{
		jam[i] = t[i];
	}
	waktu[3]=atoi(jam);
	for(i=0;i<2;i++)
	{
		menit[i] = t[3+i];
	}
	waktu[4]=atoi(menit);
	printf("\nJam: ");
	print_jam(waktu);
}

void print_jam(int time[6])
{
	if(time[3]<10 && time[4]<10)
	{
		printf("0%d:0%d", time[3], time[4]);
	}
	else if(time[3]<10 && time[4]>=10)
	{
		printf("0%d:%d", time[3], time[4]);
	}
	else if(time[3]>=10 && time[4]<10)
	{
		printf("%d:0%d", time[3], time[4]);
	}
	else
	{
		printf("%d:%d", time[3], time[4]);
	}
}

void menu_ubahDaftarObat()
{
	int menu;
	char choice[10];
	while(menu != 4)
	{
		printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t  Pengubahan Daftar Obat  \t\t\t||");
	 	printf("\n||______________________________________________________________||");
	    printf("\n||   Menu:\t\t\t\t\t\t\t||");
	    printf("\n||\t1. Tambah Data Obat\t\t\t\t\t||");
	    printf("\n||\t2. Hapus Data Obat\t\t\t\t\t||");
	    printf("\n||\t3. Update Stok Obat\t\t\t\t\t||");
	    printf("\n||\t4. Kembali ke Menu Host\t\t\t\t\t||");
	    printf("\n||______________________________________________________________||");
	    printf("\n\nPilihan: ");
	    scanf("%s", choice);
	    system("cls");
	    menu = atoi(choice);
	    
	    switch(menu)
	    {
	    	case 1: tambah_obat();break;
	      	case 2: menu_kurangObat(); break;
	      	case 3: tambah_stok(); break;
	      	case 4: break;
	      	default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;
		}
	    system("cls");
	}	
}

void tambah_stok()									//Stack menggunakan Linked list
{
	struct Obat *stok = pertama;
	int indikator=0, jumlah;
	char obat[20];
	
	printf("\n__________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t||");
 	printf("\n||\t\t\t  Tambah Stok Obat  \t\t\t||");
 	printf("\n||______________________________________________________________||");
 	printf("\nMasukkan nama obat: ");
	scanf("%s", obat);
	konversi(obat);
	while(stok != NULL)												//Loop stack
	{
		if (strcmp((stok->nama), obat)==0)							//SEARCHING
		{															//Jika nama obat yang diinput host ada di daftar tabel obat (Stack obat)
			printf("Masukkan stok terbaru: ");						//maka host bisa menambah/mengupdate jumlah stok obat
			scanf("%d", &jumlah);
			stok->jumlah = jumlah;
			indikator++;											//flag jika nama obat yang diinput ada di stack
		}
		stok = stok->next;
	}
	if (indikator==0)						//kondisi jika nama obat yang diinput tidak ada di stack daftar obat
	{
		printf("\nMaaf obat yang kamu cari tidak ada di list");
	}
}

void tambah_obat()
{
	struct Obat *check = pertama;
	int data;
	char nama[20], guna[20];
	int jumlah, flag=0;
	printf("\n__________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t||");
 	printf("\n||\t\t\t  Tambah Daftar Obat  \t\t\t||");
 	printf("\n||______________________________________________________________||");
 	printf("\nMasukkan nama obat: ");
	scanf("%s", nama);
	konversi(nama);
	
 	while(check!=NULL)										//loop stack
 	{
 		if (strcmp(nama, check->nama)==0)					//SEARCHING
		{
		 	flag=1;											//Jika nama obat yang diinput user ada di stack daftar obat
		}													//maka flag = 1 (flag penanda jika input nama obat sudah ada
		check = check->next;	
	}
	
	if(flag==0)												//kondisi jika input nama obat tidak ada di stack daftar obat
	{
		printf("Masukkan kegunaan obat: ");
		scanf("%s", guna);
		konversi(guna);
		printf("Masukkan jumlah: ");
		scanf("%d", &jumlah);
		printf("Masukkan harga: ");
		scanf("%d", &data);
		struct Obat *new = (struct Obat*) malloc(sizeof(struct Obat));		//DYNAMIC MEMORY ALLOCATION
		strcpy (new->nama, nama);											//STACK
		strcpy (new->guna, guna);								//Memasukkan data obat yang ingin ditambah di daftar, yaitu:
		new->jumlah = jumlah;									//nama obat, kegunaan untuk penyakit tertentu, jumlah stok dan harga
		new->data = data;										//Menggunakan metode push dari stack untuk memasukkan data
		new->next = pertama;
		pertama = new;
		printDaftarObat();
	}
	else						//kondisi jika input nama obat sudah ada di daftar, sehingga tidak bisa menambah jenis obat yang sama
	{
		printf("Nama obat sudah ada di daftar, silahkan tambah stok saja");
		printf("\n\nTekan tombol apapun untuk ke menu ubah daftar obat");
	}
	getch();
	system("cls");
}

void menu_kurangObat()
{
	int menu,count,i, indikator=0;
	char choice[10];
	char namaObat[20];
	struct Obat *cari;
	struct Obat *temp;
	struct Obat *simpan;
	while(menu != 3)
	{
		cari = pertama;
		temp = pertama;
		printf("\n__________________________________________________________________");
	 	printf("\n||\t\t\t\t\t\t\t\t||");
	 	printf("\n||\t\t  Menu Hapus Data Obat  \t\t\t||");
	 	printf("\n||______________________________________________________________||");
	    printf("\n||   Menu:\t\t\t\t\t\t\t||");
	    printf("\n||\t1. Hapus Nama Obat Tertentu\t\t\t\t||");
	    printf("\n||\t2. Hapus Data Obat Terakhir yang Dalam Daftar\t\t||");
	    printf("\n||\t3. Kembali ke Menu Ubah Daftar Obat\t\t\t||");
	    printf("\n||______________________________________________________________||");
	    printf("\n\nPilihan: ");
	    scanf("%s", choice);
	    system("cls");
	    menu = atoi(choice);
		system("cls");
		
		switch(menu)
		{
			case 1:
				printDaftarObat();
				count = 0;
				printf("Masukkan nama obat yang ingin dihapus: ");
				scanf("%s", namaObat);
				konversi(namaObat);
				system("cls");
				while(cari != NULL)									//Loop stack
				{														//SEARCHING & DYNAMIC MEMORY ALLOCATION
					if(strcmp(cari->nama,namaObat)==0 && count != 0)		//Kondisi untuk nama obat ada di stack daftar obat dan
					{														//bukan berada di bagian pertama stack
						simpan = cari->next;				
						temp = cari;						//Cara kerja:
						free(temp);							//Jika ingin menghapus node di tengah stack, maka perlu menyimpan alamat next nodenya
						cari = pertama;						//sebelum di-free. Lalu loop n-1 kali (n=count) dari awal dimana nantinya akan berhenti
						for(i=0;i<count-1;i++)				//pada node sebelum node yang telah dihapus untuk diganti alamat next nodenya dengan
						{									//alamat next node dari node yang telah dihapus
							cari = cari->next;			
						}								
						cari->next = simpan;				 
						printDaftarObat();					
						getch();							
						indikator++;						
					}
					else if (strcmp(cari->nama,namaObat)==0 && count == 0)		//kondisi jika nama obat ada di stack daftar obat dan
					{															//berada di bagian pertama stack
						pertama = pertama->next;			
						free(temp);						//DYNAMIC MEMORY ALLOCATION
						printDaftarObat();							//Cara kerjanya sama dengan sistem pop biasa pada stack
						getch();
						indikator++;
					}
					else
					{
						count++;							//untuk menghitung berapa kali loop untuk mencapai nama obat yang diinginkan di daftar
					}										
					cari = cari->next;
				}
				if(indikator == 0)								//kondisi jika nama obat yang diinput tidak ada di stack daftar obat
				{
					printf("Nama obat yang dicari tidak ditemukan");
					getch();
					system("cls");
					break;
				}
				break;
	      	case 2: 								//case dimana host ingin langsung menghapus jenis obat pertama di tabel
				pertama = pertama->next;			//implementasi pop pada stack
				free(temp);
				printDaftarObat();
				break;
	      	case 3: break;
	      	default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;
		}
		system("cls");
	}
}

void printDaftarObat()
{
	struct Obat *temp = pertama;
	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n||\t\t\t\tDaftar Obat\t\t\t\t\t ||");
 	printf("\n||_______________________________________________________________________________||\n");
 	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n|| Nama Obat\t\t| Kegunaan u/ penyakit  | Jumlah stok\t| Harga\t\t ||");
	printf("\n||_______________________________________________________________________________||\n");
	printf("||\t\t\t\t\t\t\t\t\t\t ||");
	if(temp == NULL)						//kondisi untuk mengecek apakah stack kosong atau tidak
	{
		printf("\n|| Kosong\t\t\t\t\t\t\t\t\t ||");
	}
	else									//kondisi jika stack tidak kosong
	{
		while(temp != NULL)							//Loop stack untuk print semua data
		{
			printf("\n|| %s       \t|", temp->nama);
			printf(" %s        \t|", temp->guna);
			printf(" %d\t\t|", temp->jumlah);
			printf(" %d\t\t ||", temp->data);
			temp = temp->next;
		}
	}
	printf("\n||_______________________________________________________________________________||\n");
}

void search_penyakit()
{
	char search[20];
	int indikator=0;
	struct Obat *cari = pertama;
	
	printf("Masukkan nama penyakit yang ingin dicari obatnya: ");
	scanf("%s", search);
	konversi(search);
	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n||\t\t\t\tDaftar Obat\t\t\t\t\t ||");
 	printf("\n||_______________________________________________________________________________||\n");
 	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n|| Nama Obat\t\t| Kegunaan u/ penyakit  | Jumlah stok\t| Harga\t\t ||");
	printf("\n||_______________________________________________________________________________||\n");
	printf("||\t\t\t\t\t\t\t\t\t\t ||");
	
	while(cari != NULL)							//Loop stack
	{											//SEARCHING
		if (strcmp((cari->guna), search)==0)
		{
			printf("\n|| %s       \t|", cari->nama);				//print semua data obat yang memiliki kegunaan untuk penyakit
			printf(" %s        \t|", cari->guna);					//yang sama dengan input user
			printf(" %d\t\t|", cari->jumlah);
			printf(" %d\t\t ||", cari->data);
			indikator++;
		}
		cari = cari->next;
	}
	
	if (indikator==0)						//kondisi jika penyakit yang dicari user tidak ada
	{
		printf("\n|| Kosong\t\t\t\t\t\t\t\t\t ||");
	}
	printf("\n||_______________________________________________________________________________||\n");
	getch();
	system("cls");
}

void search_obat()
{
	char search[20];
	int indikator=0;
	struct Obat *cariObat = pertama;
	
	printf("Masukkan nama obat yang ingin dicari: ");
	scanf("%s", search);
	konversi(search);
	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n||\t\t\t\tDaftar Obat\t\t\t\t\t ||");
 	printf("\n||_______________________________________________________________________________||\n");
 	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n|| Nama Obat\t\t| Kegunaan u/ penyakit  | Jumlah stok\t| Harga\t\t ||");
	printf("\n||_______________________________________________________________________________||\n");
	printf("||\t\t\t\t\t\t\t\t\t\t ||");
	
	while(cariObat != NULL)									//Loop stack
	{														//SEARCHING
		if (strcmp((cariObat->nama), search)==0)
		{
			printf("\n|| %s       \t|", cariObat->nama);		//print data obat yang memiliki nama obat yang sama dengan input user
			printf(" %s        \t|", cariObat->guna);
			printf(" %d\t\t|", cariObat->jumlah);
			printf(" %d\t\t ||", cariObat->data);
			indikator++;
		}
		cariObat = cariObat->next;
	}
	
	if (indikator==0)								//jika input nama obat dari user tidak ada di stack daftar
	{
		printf("\n|| Kosong\t\t\t\t\t\t\t\t\t ||");
	}
	printf("\n||_______________________________________________________________________________||\n");
	getch();
	system("cls");	
}

void sort_penyakit()
{
	int swapped, menu;
	char pilihan[10];
	struct Obat *first;
	struct Obat *last = NULL;
	
	printf("Sorting berdasarkan: ");
	printf("\n 1. Ascending");
	printf("\n 2. Descending");
	printf("\nPilihan: ");
	scanf("%s", pilihan);
	menu = atoi(pilihan);
	system("cls");
	switch(menu)
	{
		case 1:
			do															//SORTING
			{
				swapped = 0;
				first = pertama;										//menggunakan konsep bubble sort
				while (first->next != last)
				{														//cara kerja:
					if (strcmp(first->guna, first->next->guna)>0)		//loop dari awal stack dan membandingkan data yang ingin dibandingkan
					{													//misal : nama obat / nama penyakit / Jumlah stok obat
						swap(first, first->next);						//jika terbalik maka akan diswap semua data structnya / nodenya
						swapped = 1;									//kecuali alamat next nodenya. Selama pada loop stack dari awal hingga akhir
					}													//masih ada data node yang diswap, maka akan ulang loop dari awal hingga akhir
					first = first->next;								//sampai suatu ketika loop stack dari awal hingga akhir sudah tidak ada
				}														//data yang diswap
				last = first;											//last disini menandakan titik terakhir loop (karena pada saat loop selesai,
			}															//titik terakhir sudah merupakan bilangan terbesar/terkecil sehingga tidak
			while(swapped);												//perlu dicek lagi
			break;
				
		case 2:
			do														//SORTING
			{
				swapped = 0;										//menggunakan bubble sort
				first = pertama;
				while (first->next != last)
				{
					if (strcmp(first->guna, first->next->guna)<0)
					{
						swap(first, first->next);
						swapped = 1;
					}
					first = first->next;
				}
				last = first;
			}	
			while(swapped);
			break;
		
		default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;	
	}
	system("cls");
}

void sort_obat()
{
	int swapped, menu;
	char pilihan[10];
	struct Obat *first;
	struct Obat *last = NULL;
	
	printf("Sorting berdasarkan: ");
	printf("\n 1. Ascending");
	printf("\n 2. Descending");
	printf("\nPilihan: ");
	scanf("%s", pilihan);
	menu = atoi(pilihan);
	system("cls");
	switch(menu)
	{
		case 1:															//SORTING
			do
			{															//menggunakan bubble sort
				swapped = 0;
				first = pertama;
				while (first->next != last)
				{
					if (strcmp(first->nama, first->next->nama)>0)
					{
						swap(first, first->next);
						swapped = 1;
					}
					first = first->next;
				}
				last = first;
			}	
			while(swapped);
			break;
				
		case 2:																//SORTING
			do
			{																//menggunakan bubble sort
				swapped = 0;
				first = pertama;
				while (first->next != last)
				{
					if (strcmp(first->nama, first->next->nama)<0)
					{
						swap(first, first->next);
						swapped = 1;
					}
					first = first->next;
				}
				last = first;
			}	
			while(swapped);
			break;
			
		default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;	
	}
	system("cls");
}

void sort_harga()
{
	int swapped, menu;
	char pilihan[10];
	struct Obat *first;
	struct Obat *last = NULL;
	
	printf("Sorting berdasarkan: ");
	printf("\n 1. Ascending");
	printf("\n 2. Descending");
	printf("\nPilihan: ");
	scanf("%s", pilihan);
	menu = atoi(pilihan);
	system("cls");
	switch(menu)
	{
		case 1:
			do															//SORTING
			{
				swapped = 0;											//menggunakan bubble sort
				first = pertama;
				while (first->next != last)
				{
					if (first->data > first->next->data)
					{
						swap(first, first->next);
						swapped = 1;
					}
					first = first->next;
				}
				last = first;
			}	
			while(swapped);
			break;
				
		case 2:
			do																//SORTING
			{	
				swapped = 0;												//menggunakan bubble sort
				first = pertama;
				while (first->next != last)
				{
					if (first->data < first->next->data)
					{
						swap(first, first->next);
						swapped = 1;
					}
					first = first->next;
				}
				last = first;
			}	
			while(swapped);
			break;
		default : printf("Masukkan input yang benar\n"), sleep(1), system("cls"); break;	
	}
	system("cls");
}

void swap(struct Obat *a, struct Obat *b)								//function untuk swap semua value data di struct/node pada stack kecuali
{																		//alamat next nodenya
	char temp_obat[20];
	int temp_jumlah;
	int temp_data;
	char temp_penyakit[20];
	
	strcpy (temp_obat, a->nama); 				//swap nama obat
    strcpy (a->nama, b->nama); 
    strcpy (b->nama, temp_obat);
    
    temp_jumlah = a->jumlah;
    a->jumlah = b->jumlah;						//swap jumlah stok obat
    b->jumlah = temp_jumlah;
    
    temp_data = a->data;
    a->data = b->data;							//swap harga obat
    b->data = temp_data;
    
	strcpy (temp_penyakit, a->guna); 
    strcpy (a->guna, b->guna); 					//swap kegunaan untuk penyakit
    strcpy (b->guna, temp_penyakit);
}

void konversi(char kata[20])					//function untuk mengubah huruf depan kata input menjadi kapital sisanya tidak kapital/lowercase
{
	int i, n;
	n = strlen(kata);
	kata = strlwr(kata);
	for (i=0;i<n;i++)
	{
		if(i==0)
		{
			kata[i]=toupper(kata[i]);
		}
	}
}

void beli_obat()
{
	struct keranjang *newkeranjang;
	struct Obat *temp = pertama;
	struct keranjang *cek = head;
	struct keranjang *simpan;
	char namaObat[20];
	int jumlahObat, indikator = 0, isExist = 0;
	printf("Masukkan nama obat yang ingin dibeli: ");
	scanf("%s", namaObat);
	konversi(namaObat);
	while(cek != NULL)											//loop queue keranjang
	{
		if(strcmp(namaObat, cek->nama) == 0)					//cek apakah nama obat sudah ada di keranjang atau tidak
		{
			simpan = cek;				//menyimpan alamat node yang memiliki nama obat yang sama dengan input untuk nantinya diupdate jumlahnya
			isExist = 1;										//flag penanda jika nama obat sudah ada di keranjang
		}
		cek = cek-> next;
	}
	while(temp != NULL)								//loop stack obat
	{
		if(strcmp(temp->nama,namaObat)==0)				//SEARCHING (sequential)
		{
			if(newkeranjang != NULL)						
			{
				indikator++;
				printf("Masukkan jumlah obat yang ingin dibeli: ");
				scanf("%d", &jumlahObat);
				if (temp->jumlah - jumlahObat >= 0 && isExist == 1)					//kondisi jika jumlah obat yang dipesan masih tersedia
				{																	//dan ada di keranjang:
					simpan->jumlah = simpan->jumlah + jumlahObat;					//maka cukup update jumlah stok di stack obat dan jumlah 
					simpan->harga = simpan->jumlah * temp->data;					//pemesanan obat di keranjang
					temp->jumlah = temp->jumlah - jumlahObat;
				}
				else if(temp->jumlah - jumlahObat >= 0)
				{
					newkeranjang = malloc (sizeof(struct keranjang));		//DYNAMIC MEMORY ALLOCATION
					strcpy(newkeranjang->nama, namaObat);						//kondisi jika jumlah obat yang dipesan masih tersedia dan tidak ada
					newkeranjang->jumlah = jumlahObat;							//di keranjang:
					temp->jumlah = temp->jumlah - jumlahObat;					//maka perlu buat node baru dan update jumlah stok di stack obat
					newkeranjang->harga = jumlahObat * temp->data;
					newkeranjang->next = NULL;
					
					if(head == NULL)
					{
						head = newkeranjang;
					}
					else
					{
						tail->next = newkeranjang;
					}
					tail = newkeranjang;
				}
				else				//kondisi jika jumlah yang dipesan melebihi stok yang tersedia
				{
					printf("Stok obat yang anda pilih habis atau jumlah yang anda pilih melebihi stok yang tersedia");
					getch();
				}
			}
			else
			{
				printf("No memory available");
				getch();
			}
		}
		temp = temp->next;
	}

	if(indikator == 0)							//kondisi jika nama obat yang dicari tidak ada di daftar obat
	{
		printf("Nama obat yang dicari tidak ditemukan!\n");
		getch();
	}
	system("cls");
}

void printKeranjang()
{
	struct keranjang *temp = head;
	if(temp == NULL)
	{
		printf("Kosong");
		sleep(1);
	}
	else
	{
		while(temp != NULL)							//loop queue keranjang
		{
			printf("%s\n", temp->nama);
			printf("%d\n", temp->jumlah);
			printf("Rp %d\n\n", temp->harga);
			temp = temp->next;
			getch();
		}
	}
	system("cls");
}

void hapusKeranjang()						//function untuk menghapus item di keranjang
{
	struct keranjang *temp;
	struct Obat *tempObat = pertama;
	
	if(head==NULL)								//mengecek apakah queue kosong atau tidak
	{
		printf("Keranjang masih kosong");
		sleep(1);
		system("cls");
	}
	else
	{
		temp = head;
		head = head->next;
		while(tempObat != NULL)											//loop stack daftar obat
		{
			if(strcmp(temp->nama, tempObat->nama) == 0)					//SEARCHING
			{		
				tempObat->jumlah = tempObat->jumlah + temp->jumlah;		//menghapus item keranjang ini menggunakan konsep dequeue pada queue
			}
			tempObat = tempObat->next;
		}
		if(head == NULL)
		{
			tail = NULL;
		}
		free(temp);							//DYNAMIC MEMORY ALLOCATION
	}
}

void simpanFile()									//function untuk mengupdate data ke file
{
	struct Obat *simpan = pertama;
	FILE *sptr = fopen ("Daftar_obat.txt", "w");
	
	while(simpan != NULL)
	{
		fprintf(sptr, "%s\t%s\t%d\t%d\n", simpan->nama, simpan->guna, simpan->jumlah, simpan->data);
		simpan = simpan->next;	
	}
	
	fclose(sptr);
}

void InputPassword(char input[10])						//function untuk ngeinput password
{
	int i = 0,count = 0,j;
	char dummy[10];
	while(1)
    {
    	input[i] = getch();
	    if(input[i] == 8)										//untuk ngecek apakah tombol backspace ditekan
	    {
	    	i--;
	    	if(i<0)
	    	{
	    		i++;
			}
			else
			{
				printf("\b \b");								//agar pada console terlihat bahwa asterisknya terhapus
			}
		}
		else if(input[i] == -32 || input[i] == 9 || input[i] == 32)						//Daftar ASCII:
		{																				//tombol tab = 9
			continue;																	//tombol spasi = 32
		}																				//tombol spesial = -32 (Contoh: arrow key,delete,dll)
		else if(input[i] == 13)															//tombol backspace = 8
		{																				//tombol enter = 13
			break;
		}
		else
		{
			printf("*");
			i++;
		}	
	}
	for(j=0;j<i;j++)
	{
		dummy[j] = input[j];									//untuk mencegah adanya kemunculan spasi akibat backspace
	}
	strcpy(input,dummy);
}

void tambahHost()
{
	struct akun *newAkun;
	newAkun = malloc(sizeof(struct akun));				//DYNAMIC MEMORY ALLOCATION
	char idNew[100], passNew[10];
	int panjang;
	
	if(newAkun!=NULL)
	{
		printf("Masukkan Id baru: ");
		scanf("%s", idNew);
		strcpy(newAkun->id, idNew);
		
		while(1)
		{
			printf("Masukkan Password baru: ");
			InputPassword(passNew);
			panjang = strlen(passNew);
			
			if(panjang<8)								//pembuatan password dibatasi maks hanya 7 character
			{
				strcpy(newAkun->pass, passNew);
				break;
			}
			else
			{
				printf("\n\nMasukkan password baru maksimal 7 karakter\n");
			}
		}
		
		newAkun->next = first;						//dalam menambah data akun, menggunakan konsep push pada stack
		first = newAkun;	
	}
	
	struct akun *simpan = first;
	FILE *hptr = fopen ("Daftar_host.txt", "w+");
	
	while(simpan != NULL)
	{
		fprintf(hptr, "%s\t%s\n", simpan->id, simpan->pass);
		simpan = simpan->next;	
	}
	
	fclose(hptr);
	system("cls");
}

void gantiPass(int waktu[6])
{
	struct akun *gantipass = first;
	char passbaru[10], password[10];
	int panjang;
	DisplayTanggal(waktu);
	printf("\n__________________________________________________________________");
	printf("\n||\t\t\t\t\t\t\t\t||");
	printf("\n||\t\t\t  Ganti password  \t\t\t||");
	printf("\n||______________________________________________________________||\n");
	
	while(gantipass!=NULL)
	{
		if(strcmp(gantipass->id, usName)==0)
		{
			printf("\nMasukkan password Lama: ");
			InputPassword(password);
			if(strcmp(password, gantipass->pass)==0)
			{
				
				while (1)
				{
					printf("\nMasukkan Password Baru: ");
					scanf("%s", passbaru);
					panjang = strlen(passbaru);
					if(panjang<8)
					{
						strcpy(gantipass->pass, passbaru);
						break;
					}
					else
					{
						printf("\nMasukkan password baru maksimal 7 karakter");
					}
				}
			}
			else
			{
				printf("\nPassword salah!!");
				sleep(1);
				system("cls");
				return (menu_host(waktu));
			}
		}
		gantipass = gantipass->next;
	}
	
	struct akun *ganti = first;
	FILE *gptr = fopen ("Daftar_host.txt", "w+");						//PENULISAN FILE
	
	while(ganti != NULL)										//loop linked list akun(STACK) untuk update data akun (username dan password) dari
	{															//linked list / stack akun
		fprintf(gptr, "%s\t%s\n", ganti->id, ganti->pass);
		ganti = ganti->next;	
	}
	
	fclose(gptr);
	system("cls");
}

void printTiket()
{
	struct Obat *tkt = pertama;
	struct keranjang *tiket = head;
	struct keranjang *tmp;
	int i, count=0;
	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n||\t\t\t\t\tTicket\t\t\t\t\t ||");
 	printf("\n||_______________________________________________________________________________||\n");
 	printf("\n___________________________________________________________________________________");
 	printf("\n||\t\t\t\t\t\t\t\t\t\t ||");
 	printf("\n|| Nama Obat\t\t| Kegunaan u/ penyakit  | Jumlah Beli\t| Harga\t\t ||");
	printf("\n||_______________________________________________________________________________||\n");
	printf("||\t\t\t\t\t\t\t\t\t\t ||");
	if(tiket == NULL)									//mengecek apakah keranjang kosong atau tidak
	{
		printf("\n|| Kosong\t\t\t\t\t\t\t\t\t ||");
	}
	else
	{
		while(tiket != NULL)
		{
			count++;									//untuk menghitung berapa data/node di linked list keranjang yang harus di-free/dihapus
			printf("\n|| %s       \t|", tiket->nama);				//print semua data keranjang untuk dijadikan tiket
			printf(" %s        \t|", tkt->guna);
			printf(" %d\t\t|", tiket->jumlah);
			printf(" %d\t\t ||", tiket->harga);
			tiket = tiket->next;
		}
	}
	printf("\n||_______________________________________________________________________________||\n");
	for(i=0;i<count;i++)				//menghapus semua keranjang
	{
		tmp = head;
		head = head->next;

		if(head == NULL)
		{
			tail = NULL;
		}
		free(tmp);
	}
	getch();
	system("cls");
}
