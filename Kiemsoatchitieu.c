#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_GIAO_DICH 100
#define FILE_THU_NHAP "thu_nhap.txt"
#define FILE_CHI_TIEU "chi_tieu.txt"
#define FILE_DM_THU_NHAP "luu_danh_muc_thu_nhap.txt"
#define FILE_DM_CHI_TIEU "luu_danh_muc_chi_tieu.txt"

typedef struct {
    char danh_muc[50];
    float so_tien;
    char ghi_chu[100];
    time_t thoi_gian;
    bool local;
} GiaoDich;

GiaoDich chi_tieu[MAX_GIAO_DICH], thu_nhap[MAX_GIAO_DICH];
char danh_muc_thu_nhap[MAX_GIAO_DICH][50], danh_muc_chi_tieu[MAX_GIAO_DICH][50];
int so_tn = 0, so_ct = 0, so_dmtn = 0, so_dmct = 0;

int compareTime(const void *a, const void *b);
void printFormattedTime(time_t epochTime);

void load_ct_from_file();
void save_ct_to_file();
void them_gd_chi_tieu();

void load_dm_ct_from_file();
void save_dmtn_to_file();
void luu_dmct();
void chon_danh_muc_ct();

void load_tn_from_file();
void save_tn_to_file();
void them_gd_thu_nhap();

void load_dm_tn_from_file();
void save_dmtn_to_file();
void luu_dmtn();
void chon_danh_muc_tn();

void hien_thi_danh_sach_gd_theo_thoi_gian();
void cap_nhat_gd();
void xoa_gd();

int compareTime(const void *a, const void *b) {
    GiaoDich *gd1 = (GiaoDich *)a;
    GiaoDich *gd2 = (GiaoDich *)b;
    return difftime(gd2->thoi_gian, gd1->thoi_gian);
}

void printFormattedTime(time_t epochTime) {
    struct tm *localTime = localtime(&epochTime);
    if (localTime != NULL) {
        printf("%02d:%02d:%02d %02d/%02d/%d",
               localTime->tm_hour, localTime->tm_min, localTime->tm_sec,
               localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
    }
}

//////////////////////      LOAD AND SAVE FILE GIAO DICH CHI TIEU      //////////////////////

void load_ct_from_file() {
    FILE *f = fopen(FILE_CHI_TIEU, "r");
    if (f == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }
    while (fscanf(f, "%[^\n]", chi_tieu[so_ct].danh_muc) != EOF) {
        fscanf(f, "%f\n", &chi_tieu[so_ct].so_tien);
        fscanf(f, "%[^\n]", chi_tieu[so_ct].ghi_chu);
        fscanf(f, "%ld\n", &chi_tieu[so_ct].thoi_gian);
        so_ct++;
    }
    fclose(f);
}
void save_ct_to_file() {
    FILE *f = fopen(FILE_CHI_TIEU, "w");
    if (f == NULL) {
        printf("Khong the mo t-ep!\n");
        return;
    }
	int i;
	for (i = 0; i < so_ct; i++) {
    	fprintf(f, "%s\n", chi_tieu[i].danh_muc);
    	fprintf(f, "%f\n", chi_tieu[i].so_tien);
        fprintf(f, "%s\n", chi_tieu[i].ghi_chu);
        fprintf(f, "%ld\n", (long)chi_tieu[i].thoi_gian);
    }
    fclose(f);
}
void them_gd_chi_tieu(){
    char danh_muc[50];
    float so_tien;
    char ghi_chu[100];
    printf("Danh muc: ");
    while (getchar() != '\n');
    fgets(danh_muc, sizeof(danh_muc), stdin);
	danh_muc[strlen(danh_muc) - 1] = '\0';
    printf("So tien: ");
    scanf("%f", &so_tien);
    printf("Ghi chu: ");
    while (getchar() != '\n');
    fgets(ghi_chu, sizeof(ghi_chu), stdin);
    ghi_chu[strlen(ghi_chu) - 1] = '\0';
    time_t now;
    time(&now);
    strcpy(chi_tieu[so_ct].danh_muc, danh_muc);
    chi_tieu[so_ct].so_tien = so_tien;
    strcpy(chi_tieu[so_ct].ghi_chu, ghi_chu);
    chi_tieu[so_ct].thoi_gian = now;
    so_ct++;
    save_ct_to_file();
    bool save;
    printf("Ban co muon luu danh muc giao dich nay khong (1.Co, 0.Khong)?: ");
    scanf("%d", &save);
    if (save) luu_dmct();
}
void cap_nhat_gd_chi_tieu() {
    int i;
    printf("Danh sach cac giao dich chi tieu:\n");
    for (i = 0; i < so_ct; i++) {
        printf("%d. %s\n", i + 1, chi_tieu[i].danh_muc);
    }
    int choice;
    printf("Nhap so thu tu cua giao dich can cap nhat: ");
    scanf("%d", &choice);
    if (choice <= 0 || choice > so_ct) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    choice--;
    char danh_muc[50];
    float so_tien;
    char ghi_chu[100];
    printf("Nhap thong tin cap nhat cho giao dich %d:\n", choice + 1);
    printf("Danh muc: ");
    while (getchar() != '\n');
    fgets(danh_muc, sizeof(danh_muc), stdin);
    danh_muc[strlen(danh_muc) - 1] = '\0';
    printf("So tien: ");
    scanf("%f", &so_tien);
    printf("Ghi chu: ");
    while (getchar() != '\n');
    fgets(ghi_chu, sizeof(ghi_chu), stdin);
    ghi_chu[strlen(ghi_chu) - 1] = '\0';
    strcpy(chi_tieu[choice].danh_muc, danh_muc);
    chi_tieu[choice].so_tien = so_tien;
    strcpy(chi_tieu[choice].ghi_chu, ghi_chu);
    time_t now;
    time(&now);
    chi_tieu[choice].thoi_gian = now;
    save_ct_to_file();
    printf("Da cap nhat giao dich thanh cong!\n");
}
void xoa_gd_chi_tieu() {
    int i;
    printf("Danh sach cac giao dich chi tieu:\n");
    for (i = 0; i < so_ct; i++) {
        printf("%d. %s\n", i + 1, chi_tieu[i].danh_muc);
    }
    int choice;
    printf("Nhap so thu tu cua giao dich can xoa: ");
    scanf("%d", &choice);
    if (choice <= 0 || choice > so_ct) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    choice--;
    for (i = choice; i < so_ct - 1; i++) {
        chi_tieu[i] = chi_tieu[i + 1];
    }
    so_ct--;
    save_ct_to_file();
    printf("Da xoa giao dich thanh cong!\n");
}

//////////////////////      LOAD AND SAVE DANH MUC CHI TIEU      //////////////////////

void load_dm_ct_from_file() {
    FILE *f = fopen(FILE_DM_CHI_TIEU, "r");
    if (f == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }

    while (fscanf(f, "%[^\n]", danh_muc_chi_tieu[so_dmct]) != EOF) {
        char c;
        fscanf(f, "%c", &c);
        so_dmct++;
    }

    fclose(f);
}
void save_dmct_to_file() {
    FILE *f = fopen(FILE_DM_CHI_TIEU, "w");
    if (f == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }
	int i;
    for (i = 0; i < so_dmct; i++) {
    	fprintf(f, "%s\n", danh_muc_chi_tieu[i]);
    }
    fclose(f);
}
void luu_dmct(){
	strcpy(danh_muc_chi_tieu[so_dmct], chi_tieu[so_ct - 1].danh_muc);
	so_dmct++;
	printf("Luu danh muc thanh cong\n");
	save_dmct_to_file();
}
void chon_danh_muc_ct(){
	int i;
	for (i = 0; i < so_dmct; i++){
		printf("%d. %s\n", i + 1, danh_muc_chi_tieu[i]);
	}
	int choice;
	printf("Nhap lua chon cua ban: ");
	scanf("%d", &choice);
	strcpy(chi_tieu[so_ct].danh_muc, danh_muc_chi_tieu[choice - 1]);
	printf("Ban da chon danh muc: %s\n", danh_muc_chi_tieu[choice - 1]);
	float so_tien;
    char ghi_chu[100];
	printf("So tien: ");
    scanf("%f", &so_tien);
    printf("Ghi chu: ");
    while (getchar() != '\n');
    fgets(ghi_chu, sizeof(ghi_chu), stdin);
    ghi_chu[strlen(ghi_chu) - 1] = '\0';
    chi_tieu[so_ct].so_tien = so_tien;
    strcpy(chi_tieu[so_ct].ghi_chu, ghi_chu);
    time_t now;
    time(&now);
    chi_tieu[so_ct].thoi_gian = now;
    so_ct++;
    save_ct_to_file();
}


//////////////////////      LOAD AND SAVE FILE GIAO DICH THU NHAP      //////////////////////

void load_tn_from_file() {
    FILE *f = fopen(FILE_THU_NHAP, "r");
    if (f == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }
    while (fscanf(f, "%[^\n]", thu_nhap[so_tn].danh_muc) != EOF) {
        fscanf(f, "%f\n", &thu_nhap[so_tn].so_tien);
        fscanf(f, "%[^\n]", thu_nhap[so_tn].ghi_chu);
        fscanf(f, "%ld\n", &thu_nhap[so_tn].thoi_gian);
        so_tn++;
    }

    fclose(f);
}
void save_tn_to_file() {
    FILE *f = fopen(FILE_THU_NHAP, "w");
    if (f == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }
	int i;
    for (i = 0; i < so_tn; i++) {
    	fprintf(f, "%s\n", thu_nhap[i].danh_muc);
    	fprintf(f, "%f\n", thu_nhap[i].so_tien);
        fprintf(f, "%s\n", thu_nhap[i].ghi_chu);
        fprintf(f, "%ld\n", (long)thu_nhap[i].thoi_gian);
    }
    fclose(f);
}
void them_gd_thu_nhap(){
    char danh_muc[50];
    float so_tien;
    char ghi_chu[100];
    printf("Danh muc: ");
    while (getchar() != '\n');
    fgets(danh_muc, sizeof(danh_muc), stdin);
	danh_muc[strlen(danh_muc) - 1] = '\0';
    printf("So tien: ");
    scanf("%f", &so_tien);
    printf("Ghi chu: ");
    while (getchar() != '\n');
    fgets(ghi_chu, sizeof(ghi_chu), stdin);
    ghi_chu[strlen(ghi_chu) - 1] = '\0';
    time_t now;
    time(&now);
    strcpy(thu_nhap[so_tn].danh_muc, danh_muc);
    thu_nhap[so_tn].so_tien = so_tien;
    strcpy(thu_nhap[so_tn].ghi_chu, ghi_chu);
    thu_nhap[so_tn].thoi_gian = now;
    so_tn++;
    save_tn_to_file();
    bool save;
    printf("Ban co muon luu danh muc giao dich nay khong (1.Co, 0.Khong)?: ");
    scanf("%d", &save);
    if (save) luu_dmtn();
}
void cap_nhat_gd_thu_nhap() {
    int i;
    printf("Danh sach cac giao dich thu nhap:\n");
    for (i = 0; i < so_tn; i++) {
        printf("%d. %s\n", i + 1, thu_nhap[i].danh_muc);
    }
    int choice;
    printf("Nhap so thu tu cua giao dich can cap nhat: ");
    scanf("%d", &choice);
    if (choice <= 0 || choice > so_tn) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    choice--;
    char danh_muc[50];
    float so_tien;
    char ghi_chu[100];
    printf("Nhap thong tin cap nhat cho giao dich %d:\n", choice + 1);
    printf("Danh muc: ");
    while (getchar() != '\n');
    fgets(danh_muc, sizeof(danh_muc), stdin);
    danh_muc[strlen(danh_muc) - 1] = '\0';
    printf("So tien: ");
    scanf("%f", &so_tien);
    printf("Ghi chu: ");
    while (getchar() != '\n');
    fgets(ghi_chu, sizeof(ghi_chu), stdin);
    ghi_chu[strlen(ghi_chu) - 1] = '\0';
    strcpy(thu_nhap[choice].danh_muc, danh_muc);
    thu_nhap[choice].so_tien = so_tien;
    strcpy(thu_nhap[choice].ghi_chu, ghi_chu);
    time_t now;
    time(&now);
    thu_nhap[choice].thoi_gian = now;
    save_tn_to_file();
    printf("Da cap nhat giao dich thanh cong!\n");
}
void xoa_gd_thu_nhap() {
    int i;
    printf("Danh sach cac giao dich thu nhap:\n");
    for (i = 0; i < so_tn; i++) {
        printf("%d. %s\n", i + 1, thu_nhap[i].danh_muc);
    }
    int choice;
    printf("Nhap so thu tu cua giao dich can xoa: ");
    scanf("%d", &choice);
    if (choice <= 0 || choice > so_tn) {
        printf("Lua chon khong hop le!\n");
        return;
    }
    choice--;
    for (i = choice; i < so_tn - 1; i++) {
        thu_nhap[i] = thu_nhap[i + 1];
    }
    so_tn--;
    save_tn_to_file();
    printf("Da xoa giao dich thanh cong!\n");
}

//////////////////////      LOAD AND SAVE DANH MUC THU NHAP      //////////////////////

void load_dm_tn_from_file() {
    FILE *f = fopen(FILE_DM_THU_NHAP, "r");
    if (f == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }

    while (fscanf(f, "%[^\n]", danh_muc_thu_nhap[so_dmtn]) != EOF) {
        char c;
        fscanf(f, "%c", &c);
        so_dmtn++;
    }

    fclose(f);
}
void save_dmtn_to_file() {
    FILE *f = fopen(FILE_DM_THU_NHAP, "w");
    if (f == NULL) {
        printf("Khong the mo tep!\n");
        return;
    }
	int i;
    for (i = 0; i < so_dmtn; i++) {
    	fprintf(f, "%s\n", danh_muc_thu_nhap[i]);
    }
    fclose(f);
}
void luu_dmtn(){
	strcpy(danh_muc_thu_nhap[so_dmtn], thu_nhap[so_tn - 1].danh_muc);
	so_dmtn++;
	printf("Luu danh muc thanh cong\n");
	save_dmtn_to_file();
}
void chon_danh_muc_tn(){
	int i;
	for (i = 0; i < so_dmtn; i++){
		printf("%d. %s\n", i + 1, danh_muc_thu_nhap[i]);
	}
	int choice;
	printf("Nhap lua chon cua ban: ");
	scanf("%d", &choice);
	strcpy(thu_nhap[so_tn].danh_muc, danh_muc_thu_nhap[choice - 1]);
	printf("Ban da chon danh muc: %s\n", danh_muc_thu_nhap[choice - 1]);
	float so_tien;
    char ghi_chu[100];
	printf("So tien: ");
    scanf("%f", &so_tien);
    printf("Ghi chu: ");
    while (getchar() != '\n');
    fgets(ghi_chu, sizeof(ghi_chu), stdin);
    ghi_chu[strlen(ghi_chu) - 1] = '\0';
    thu_nhap[so_tn].so_tien = so_tien;
    strcpy(thu_nhap[so_tn].ghi_chu, ghi_chu);
    time_t now;
    time(&now);
    thu_nhap[so_tn].thoi_gian = now;
    so_tn++;
    save_tn_to_file();
}

void hien_thi_tat_ca_giao_dich_theo_thoi_gian() {
    GiaoDich tat_ca_giao_dich[so_tn + so_ct];
    int i;
    for (i = 0; i < so_tn; ++i) {
        tat_ca_giao_dich[i] = thu_nhap[i];
        tat_ca_giao_dich[i].local = 1;
    }
    for (i = 0; i < so_ct; ++i) {
        tat_ca_giao_dich[so_tn + i] = chi_tieu[i];
        tat_ca_giao_dich[so_tn + i].local = 0;
    }
    
    qsort(tat_ca_giao_dich, so_tn + so_ct, sizeof(GiaoDich), compareTime);

    printf("Tat ca giao dich theo thoi gian:\n");
    printf("+----+-------------------+-------------------+------------------------------------+----------------------+--------------------+\n");
    printf("|    |     DANH MUC      |      SO TIEN      |              GHI CHU               |       THOI GIAN      |   LOAI GIAO DICH   |\n");
    printf("+----+-------------------+-------------------+------------------------------------+----------------------+--------------------+\n");
    for (i = 0; i < so_tn + so_ct; ++i) {
        printf("| %-2d | %-17s | %-12.0f(VND) | %-34s |", i + 1, tat_ca_giao_dich[i].danh_muc, tat_ca_giao_dich[i].so_tien, tat_ca_giao_dich[i].ghi_chu);
        printFormattedTime(tat_ca_giao_dich[i].thoi_gian);
        if (tat_ca_giao_dich[i].local == 0) 
            printf("   |      CHI TIEU      |\n"); 
        else 
            printf("   |      THU NHAP      |\n");
    }
    printf("+----+-------------------+-------------------+------------------------------------+----------------------+--------------------+\n");
}


void tinh_tai_san_rong() {
    float tong_thu_nhap = 0.0;
    float tong_chi_tieu = 0.0;
    int i;
    for (i = 0; i < so_tn; i++) {
        tong_thu_nhap += thu_nhap[i].so_tien;
    }
    for (i = 0; i < so_ct; i++) {
        tong_chi_tieu += chi_tieu[i].so_tien;
    }
    float tai_san_rong = tong_thu_nhap - tong_chi_tieu;
    printf("Tai san rong cua ban la: %.2f\n", tai_san_rong);
    printf("\nNhan Enter de tiep tuc...");
    while (getchar() != '\n');
    getchar();
}

void phan_tich_chi_tieu() {
    typedef struct {
        char danh_muc[50];
        float tong_chi;
    } PhanTichChiTieu;

    PhanTichChiTieu phan_tich[MAX_GIAO_DICH];
    int so_phan_tich = 0;
    int i, j;
    for (i = 0; i < so_ct; ++i) {
        bool da_them = false;
        for (j = 0; j < so_phan_tich; ++j) {
            if (strcmp(chi_tieu[i].danh_muc, phan_tich[j].danh_muc) == 0) {
                phan_tich[j].tong_chi += chi_tieu[i].so_tien;
                da_them = true;
                break;
            }
        }
        if (!da_them) {
            strcpy(phan_tich[so_phan_tich].danh_muc, chi_tieu[i].danh_muc);
            phan_tich[so_phan_tich].tong_chi = chi_tieu[i].so_tien;
            so_phan_tich++;
        }
    }
    printf("Phan tich chi tieu theo danh muc:\n");
    for (i = 0; i < so_phan_tich; ++i) {
        printf("Danh muc: %s, Tong chi: %.2f\n", phan_tich[i].danh_muc, phan_tich[i].tong_chi);
    }
    printf("\nNhan Enter de tiep tuc...");
    while (getchar() != '\n');
    getchar();
}

int main() {
	load_tn_from_file();
    load_ct_from_file();
	load_dm_ct_from_file();
	load_dm_tn_from_file();
    int lua_chon;
    do {
      printf("\n+------------+------------+ MENU +------------+-------------+\n");
		printf("|  1. Them giao dich thu nhap                               |\n");
		printf("|  2. Cap nhat giao dich thu nhap                           |\n");
		printf("|  3. Xoa giao dich thu nhap                                |\n");
		printf("|  4. Them giao dich chi tieu                               |\n");
		printf("|  5. Cap nhat giao dich chi tieu                           |\n");
		printf("|  6. Xoa giao dich chi tieu                                |\n");
		printf("|  7. Hien thi danh sach giao dich theo thoi gian           |\n");
		printf("|  8. Tong ket thu chi                                      |\n");
		printf("|  9. Phan tich chi tieu                                    |\n");
		printf("|  0. Thoat                                                 |\n");
		printf("+------------+------------+ MENU +------------+-------------+\n");
		printf("Nhap lua chon: ");
scanf("%d", &lua_chon);


        switch (lua_chon) {
            case 1:{
            	int choice1;
            	printf("1. Thu nhap moi\n");
                printf("2. Thu nhap da luu\n");
                printf("0. Quay lai\n");
                printf("Nhap lua chon: ");
                scanf("%d", &choice1);
                switch(choice1){
                	case 1:{
                		them_gd_thu_nhap();
						break;
					}
					case 2:{
						if (so_dmtn == 0) printf("Khong co danh muc nao duoc luu.\n");
						else
						chon_danh_muc_tn();
						break;
					}
					case 0:{
						break;
					}
					default:{
						break;
					}
				}
                break;
			}
			case 2:{
				cap_nhat_gd_thu_nhap();
				break;
			}
			case 3:{
				xoa_gd_thu_nhap();
				break;
			}
            case 4:{
            	int choice2;
            	printf("1. Chi tieu moi\n");
                printf("2. Chi tieu da luu\n");
                printf("0. Quay lai\n");
                printf("Nhap lua chon: ");
                scanf("%d", &choice2);
                switch(choice2){
                	case 1:{
                		them_gd_chi_tieu();
						break;
					}
					case 2:{
						if (so_dmct == 0) printf("Khong co danh muc nao duoc luu.\n");
						else
						chon_danh_muc_ct();
						break;
					}
					case 0:{
						break;
					}
					default:{
						break;
					}
				}
                break;
            }
            case 5:{
            	cap_nhat_gd_chi_tieu();
				break;
			}
			case 6:{
				xoa_gd_chi_tieu();
				break;
			}
            case 7:{
                hien_thi_tat_ca_giao_dich_theo_thoi_gian();
                while (getchar() != '\n');
    		getchar();
                break;
            }
            case 8:{
            	tinh_tai_san_rong();
				break;
			}
			case 9:{
				phan_tich_chi_tieu();
				break;
			}
            case 0:
                printf("Ket thuc chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (lua_chon != 0);

    return 0;
}

