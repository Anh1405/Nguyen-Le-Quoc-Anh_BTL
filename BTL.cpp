#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

// Dinh nghia cau truc Sinhvien de luu thong tin sinh vien
typedef struct {
    char MSV[MAX];      // Ma sinh vien
    char Hoten[MAX];    // Ho va ten
    char NS[MAX];       // Nam sinh
    char Lop[MAX];      // Lop
    float DTB;          // Diem trung binh
    char Diachi[MAX];   // Dia chi
} Sinhvien;

// Dinh nghia cau truc Node cho danh sach lien ket
typedef struct Node {
    Sinhvien data;      // Du lieu sinh vien
    struct Node* next;  // Con tro den node tiep theo
} Node;

// Tao node moi cho danh sach lien ket
Node* createNode(Sinhvien sv) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // Cap phat bo nho cho node moi
    if (newNode == NULL) {
        printf("Khong cap phat duoc bo nho\n"); // Bao loi neu cap phat that bai
        exit(1);
    }
    newNode->data = sv;     // Gan du lieu sinh vien cho node
    newNode->next = NULL;   // Thiet lap con tro next la NULL
    return newNode;         // Tra ve node moi
}

// Dem so node trong danh sach lien ket
int countNodes(Node* head) {
    int count = 0;              // Bien dem so sinh vien
    Node* current = head;       // Con tro duyet danh sach
    while (current != NULL) {   // Duyet qua tung node
        count++;                // Tang bien dem
        current = current->next;// Chuyen den node tiep theo
    }
    return count;               // Tra ve so luong node
}

// Nhap thong tin cho mot sinh vien
void nhapdanhsach1sv(Sinhvien* sv, int h) {
    printf("Nhap Ma sinh vien: ");
    scanf("%s", sv->MSV);   // Nhap ma sinh vien
    printf("Nhap ho va ten: ");
    getchar();              // Xoa ky tu thua trong bo dem
    fgets(sv->Hoten, MAX, stdin); // Nhap ho va ten
    sv->Hoten[strcspn(sv->Hoten, "\n")] = 0; // Xoa ky tu xuong dong
    printf("Nhap Nam sinh: ");
    scanf("%s", sv->NS);    // Nhap nam sinh
    printf("Nhap Lop: ");
    getchar();              // Xoa ky tu thua
    fgets(sv->Lop, MAX, stdin); // Nhap lop
    sv->Lop[strcspn(sv->Lop, "\n")] = 0; // Xoa ky tu xuong dong
    if (h == 1) { // He so 10
        do {
            printf("Nhap Diem Trung Binh (0->10): ");
            scanf("%f", &sv->DTB); // Nhap diem trung binh
            if (sv->DTB < 0 || sv->DTB > 10) {
                printf("Nhap lai Diem Trung Binh (0->10)\n"); // Yeu cau nhap lai neu diem khong hop le
            }
        } while (sv->DTB < 0 || sv->DTB > 10); // Kiem tra diem trong khoang 0-10
    } else if (h == 2) { // He so 4
        do {
            printf("Nhap Diem Trung Binh (0->4): ");
            scanf("%f", &sv->DTB); // Nhap diem trung binh
            if (sv->DTB < 0 || sv->DTB > 4) {
                printf("Nhap lai Diem Trung Binh (0->4)\n"); // Yeu cau nhap lai neu diem khong hop le
            }
        } while (sv->DTB < 0 || sv->DTB > 4); // Kiem tra diem trong khoang 0-4
    }
    printf("Nhap dia chi: ");
    getchar();              // Xoa ky tu thua
    fgets(sv->Diachi, MAX, stdin); // Nhap dia chi
    sv->Diachi[strcspn(sv->Diachi, "\n")] = 0; // Xoa ky tu xuong dong
}

// Doc thong tin sinh vien tu file
void docDanhSachTuFile(Node** head, int h) {
    char tenFile[MAX];
    printf("Nhap ten file chua danh sach sinh vien: ");
    getchar(); // Xoa ky tu thua
    fgets(tenFile, MAX, stdin);
    tenFile[strcspn(tenFile, "\n")] = 0; // Xoa ky tu xuong dong

    FILE* file = fopen(tenFile, "r");
    if (file == NULL) {
        printf("Khong the mo file %s\n", tenFile);
        return;
    }

    char line[512]; // Buffer de doc tung dong
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Xoa ky tu xuong dong
        Sinhvien sv;
        char* token = strtok(line, ",");
        if (token) strcpy(sv.MSV, token);
        else continue;

        token = strtok(NULL, ",");
        if (token) strcpy(sv.Hoten, token);
        else continue;

        token = strtok(NULL, ",");
        if (token) strcpy(sv.NS, token);
        else continue;

        token = strtok(NULL, ",");
        if (token) strcpy(sv.Lop, token);
        else continue;

        token = strtok(NULL, ",");
        if (token) sv.DTB = atof(token);
        else continue;

        token = strtok(NULL, ",");
        if (token) strcpy(sv.Diachi, token);
        else continue;

        // Kiem tra diem trung binh hop le
        if ((h == 1 && (sv.DTB < 0 || sv.DTB > 10)) || (h == 2 && (sv.DTB < 0 || sv.DTB > 4))) {
            printf("Diem trung binh cua sinh vien %s khong hop le, bo qua\n", sv.MSV);
            continue;
        }

        Node* newNode = createNode(sv);
        if (*head == NULL) {
            *head = newNode;
        } else {
            Node* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    fclose(file);
    printf("Da doc danh sach sinh vien tu file %s\n", tenFile);
}

// Xuat thong tin cua mot sinh vien
void xuatdanhsach1sv(Sinhvien* sv) {
    printf("| %-10s | %-20s | %-10s | %-19s | %-6.2f | %-20s |\n",
           sv->MSV, sv->Hoten, sv->NS, sv->Lop, sv->DTB, sv->Diachi); // In thong tin sinh vien theo dinh dang bang
}

// Nhap danh sach sinh vien vao danh sach lien ket
void nhapdanhsachmangsv(Node** head, int n, int h) {
    printf("Nhap danh sach cho %d sinh vien\n", n);
    for (int i = 0; i < n; i++) {
        printf("=== Sinh vien thu %d ===\n", i + 1);
        Sinhvien sv;
        nhapdanhsach1sv(&sv, h); // Nhap thong tin cho mot sinh vien
        Node* newNode = createNode(sv); // Tao node moi
        if (*head == NULL) {
            *head = newNode; // Neu danh sach rong, gan node moi lam dau
        } else {
            Node* current = *head; // Duyet den node cuoi
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode; // Them node moi vao cuoi danh sach
        }
    }
}

// Xuat danh sach sinh vien
void xuatdanhsachmangsv(Node* head) {
    if (head == NULL) {
        printf("Danh sach rong!\n"); // Bao loi neu danh sach rong
        return;
    }
    printf("\n========================== DANH SACH SINH VIEN ==========================\n");
    printf("+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    printf("| MSV        | Ho va ten            | Nam sinh   | Lop                 | DTB    | Dia chi              |\n");
    printf("+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    Node* current = head;
    while (current != NULL) {
        xuatdanhsach1sv(&current->data); // Sua loi ¤t->data thanh current->data
        current = current->next; // Chuyen den node tiep theo
    }
    printf("+------------+----------------------+------------+---------------------+--------+----------------------+\n\n");
}

// Sap xep danh sach theo ma sinh vien
void SapxepdanhsachtheoMSV(Node** head) {
    if (*head == NULL || (*head)->next == NULL) return; // Khong sap xep neu danh sach rong hoac chi co 1 node
    Node* current;
    Node* nextNode;
    Sinhvien temp;
    int swapped;
    do {
        swapped = 0;
        current = *head;
        while (current->next != NULL) {
            nextNode = current->next;
            if (strcmp(current->data.MSV, nextNode->data.MSV) > 0) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp; // Hoan doi du lieu giua hai node
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped); // Lap lai den khi khong con hoan doi
}

// Sap xep danh sach theo ho va ten
void SapxepdanhsachtheoHT(Node** head) {
    if (*head == NULL || (*head)->next == NULL) return;
    Node* current;
    Node* nextNode;
    Sinhvien temp;
    int swapped;
    do {
        swapped = 0;
        current = *head;
        while (current->next != NULL) {
            nextNode = current->next;
            if (strcmp(current->data.Hoten, nextNode->data.Hoten) > 0) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// Sap xep danh sach theo nam sinh
void SapxepdanhsachtheoNS(Node** head) {
    if (*head == NULL || (*head)->next == NULL) return;
    Node* current;
    Node* nextNode;
    Sinhvien temp;
    int swapped;
    do {
        swapped = 0;
        current = *head;
        while (current->next != NULL) {
            nextNode = current->next;
            if (strcmp(current->data.NS, nextNode->data.NS) > 0) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// Sap xep danh sach theo dia chi
void SapxepdanhsachtheoDiachi(Node** head) {
    if (*head == NULL || (*head)->next == NULL) return;
    Node* current;
    Node* nextNode;
    Sinhvien temp;
    int swapped;
    do {
        swapped = 0;
        current = *head;
        while (current->next != NULL) {
            nextNode = current->next;
            if (strcmp(current->data.Diachi, nextNode->data.Diachi) > 0) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// Sap xep danh sach theo diem trung binh (giam dan)
void SapxepdanhsachtheoDTB(Node** head) {
    if (*head == NULL || (*head)->next == NULL) return;
    Node* current;
    Node* nextNode;
    Sinhvien temp;
    int swapped;
    do {
        swapped = 0;
        current = *head;
        while (current->next != NULL) {
            nextNode = current->next;
            if (current->data.DTB < nextNode->data.DTB) {
                temp = current->data;
                current->data = nextNode->data;
                nextNode->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

// Thong ke sinh vien co diem trung binh duoi nguong hoc lai va ghi vao file
void thongkedanhsach(Node* head, int h) {
    FILE* file = fopen("Hoclai.txt", "w"); // Mo file de ghi
    if (file == NULL) {
        printf("Loi mo file\n"); // Bao loi neu khong mo duoc file
        return;
    }
    fprintf(file, "\n========================== DANH SACH SINH VIEN HOC LAI ==========================\n");
    fprintf(file, "+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    fprintf(file, "| MSV        | Ho va ten            | Nam sinh   | Lop                 | DTB    | Dia chi              |\n");
    fprintf(file, "+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    int dem = 0;
    Node* current = head;
    while (current != NULL) {
        // Kiem tra sinh vien co DTB duoi nguong hoc lai
        if ((h == 1 && current->data.DTB < 4) || (h == 2 && current->data.DTB < 1.6)) {
            fprintf(file, "| %-10s | %-20s | %-10s | %-19s | %-6.2f | %-20s |\n",
                    current->data.MSV, current->data.Hoten, current->data.NS,
                    current->data.Lop, current->data.DTB, current->data.Diachi);
            dem++;
        }
        current = current->next;
    }
    fprintf(file, "+------------+----------------------+------------+---------------------+--------+----------------------+\n\n");
    if (dem == 0) {
        fprintf(file, "Khong co sinh vien nao phai hoc lai\n"); // Thong bao neu khong co sinh vien nao
    }
    fclose(file); // Dong file
    printf("Da ghi danh sach sinh vien hoc lai vao Hoclai.txt\n");
}

// Xep loai hoc luc sinh vien dua tren diem trung binh
void sapxephocluc(Node* head, int* h) {
    printf("%-30s %-30s\n", "Ho va ten", "Xep luc");
    Node* current = head;
    if (*h == 1) { // Xep loai theo he so 10
        while (current != NULL) {
            if (current->data.DTB >= 0 && current->data.DTB < 4) {
                printf("%-30s %-30s\n", current->data.Hoten, "Kem");
            } else if (current->data.DTB >= 4 && current->data.DTB < 5.5) {
                printf("%-30s %-30s\n", current->data.Hoten, "Trung Binh Yeu");
            } else if (current->data.DTB >= 5.5 && current->data.DTB < 7) {
                printf("%-30s %-30s\n", current->data.Hoten, "Trung Binh");
            } else if (current->data.DTB >= 7 && current->data.DTB < 8.5) {
                printf("%-30s %-30s\n", current->data.Hoten, "Kha");
            } else if (current->data.DTB >= 8.5 && current->data.DTB <= 10) {
                printf("%-30s %-30s\n", current->data.Hoten, "Gioi");
            }
            current = current->next;
        }
    } else if (*h == 2) { // Xep loai theo he so 4
        while (current != NULL) {
            if (current->data.DTB >= 0 && current->data.DTB < 1.6) {
                printf("%-30s %-30s\n", current->data.Hoten, "Kem");
            } else if (current->data.DTB >= 1.6 && current->data.DTB < 2.2) {
                printf("%-30s %-30s\n", current->data.Hoten, "Trung Binh Yeu");
            } else if (current->data.DTB >= 2.2 && current->data.DTB < 2.8) {
                printf("%-30s %-30s\n", current->data.Hoten, "Trung Binh");
            } else if (current->data.DTB >= 2.8 && current->data.DTB < 3.4) {
                printf("%-30s %-30s\n", current->data.Hoten, "Kha");
            } else if (current->data.DTB >= 3.4 && current->data.DTB <= 4) {
                printf("%-30s %-30s\n", current->data.Hoten, "Gioi");
            }
            current = current->next;
        }
    }
}

// Ghi danh sach sinh vien vao file
void ghiFileDanhSach(char* tenFile, Node* head) {
    FILE* f = fopen(tenFile, "w"); // Mo file de ghi
    if (f == NULL) {
        printf("Khong the mo file %s de ghi!\n", tenFile); // Bao loi neu khong mo duoc
        return;
    }
    fprintf(f, "\n========================== DANH SACH SINH VIEN ==========================\n");
    fprintf(f, "+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    fprintf(f, "| MSV        | Ho va ten            | Nam sinh   | Lop                 | DTB    | Dia chi              |\n");
    fprintf(f, "+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    Node* current = head;
    while (current != NULL) {
        fprintf(f, "| %-10s | %-20s | %-10s | %-19s | %-6.2f | %-20s |\n",
                current->data.MSV, current->data.Hoten, current->data.NS,
                current->data.Lop, current->data.DTB, current->data.Diachi);
        current = current->next;
    }
    fprintf(f, "+------------+----------------------+------------+---------------------+--------+----------------------+\n\n");
    fclose(f); // Dong file
}

// Them mot sinh vien vao danh sach
void themsinhvien(Node** head, int h) {
    printf("Nhap sinh vien moi\n");
    Sinhvien sv;
    nhapdanhsach1sv(&sv, h); // Nhap thong tin sinh vien
    Node* newNode = createNode(sv); // Tao node moi
    if (*head == NULL) {
        *head = newNode; // Neu danh sach rong, gan node moi lam dau
    } else {
        Node* current = *head; // Duyet den node cuoi
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode; // Them node moi vao cuoi
    }
    printf("Them sinh vien thanh cong\n");
}

// Xoa mot sinh vien khoi danh sach
void xoasinhvien(Node** head, int h) {
    char msvcanxoa[50];
    printf("Nhap ma sinh vien: ");
    getchar();
    fgets(msvcanxoa, sizeof(msvcanxoa), stdin); // Nhap ma sinh vien can xoa
    msvcanxoa[strcspn(msvcanxoa, "\n")] = 0;

    Node* current = *head;
    Node* prev = NULL;
    int timthay = 0;

    while (current != NULL) {
        if (strcmp(msvcanxoa, current->data.MSV) == 0) {
            if (prev == NULL) {
                *head = current->next; // Xoa node dau
            } else {
                prev->next = current->next; // Xoa node giua hoac cuoi
            }
            free(current); // Giai phong bo nho
            timthay = 1;
            printf("Xoa sinh vien thanh cong\n");
            break;
        }
        prev = current;
        current = current->next;
    }
    if (!timthay) {
        printf("Khong tim thay sinh vien co MSV \"%s\"\n", msvcanxoa);
    }
}

// Chinh sua thong tin sinh vien
void chinhsua(Node** head, int h) {
    char Tensai[50];
    printf("Nhap ma sinh vien sai muon chinh sua: ");
    getchar();
    fgets(Tensai, 50, stdin); // Nhap ma sinh vien can chinh sua
    Tensai[strcspn(Tensai, "\n")] = 0;
    int timthay = 0;
    Node* current = *head;
    while (current != NULL) {
        if (strcmp(Tensai, current->data.MSV) == 0) {
            nhapdanhsach1sv(&current->data, h); // Nhap lai thong tin moi
            timthay = 1;
            printf("Chinh sua sinh vien thanh cong\n");
            break;
        }
        current = current->next;
    }
    if (!timthay) {
        printf("Khong tim thay sinh vien co MSV \"%s\"\n", Tensai);
    }
}

// Tim kiem sinh vien theo ma
void timkiem(Node* head) {
    char Timkiem[100];
    printf("Nhap MSSV muon tim: ");
    getchar();
    fgets(Timkiem, 100, stdin); // Nhap ma sinh vien can tim
    Timkiem[strcspn(Timkiem, "\n")] = 0;
    int timthay = 0;
    printf("\n========================== DANH SACH SINH VIEN ==========================\n");
    printf("+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    printf("| MSV        | Ho va ten            | Nam sinh   | Lop                 | DTB    | Dia chi              |\n");
    printf("+------------+----------------------+------------+---------------------+--------+----------------------+\n");
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->data.MSV, Timkiem) == 0) {
            xuatdanhsach1sv(&current->data); // Sua loi ¤t->data thanh current->data
            timthay = 1;
            break;
        }
        current = current->next;
    }
    printf("+------------+----------------------+------------+---------------------+--------+----------------------+\n\n");
    if (!timthay) {
        printf("Khong tim thay sinh vien co MSSV \"%s\"\n", Timkiem);
    }
}

// Chuyen diem trung binh sang he so 4
void diemheso4(Node* head, int* h) {
    if (*h == 2) {
        printf("Khong the chuyen vi day la diem he so 4\n"); // Bao loi neu da o he so 4
        return;
    }
    Node* current = head;
    while (current != NULL) {
        current->data.DTB = (current->data.DTB / 10) * 4; // Chuyen diem sang he so 4
        current = current->next;
    }
    printf("Da chuyen sang he so 4\n");
    *h = 2; // Cap nhat trang thai he so
}

// Chuyen diem trung binh sang he so 10
void diemheso10(Node* head, int* h) {
    if (*h == 1) {
        printf("Khong the chuyen vi day la diem he so 10\n"); // Bao loi neu da o he so 10
        return;
    }
    Node* current = head;
    while (current != NULL) {
        current->data.DTB = (current->data.DTB / 4) * 10; // Chuyen diem sang he so 10
        current = current->next;
    }
    printf("Da chuyen sang he so 10\n");
    *h = 1; // Cap nhat trang thai he so
}

// Thong ke ti le sinh vien theo hoc luc
void thongKeHocLuc(Node* head, int* h) {
    if (head == NULL) {
        printf("Danh sach rong!\n"); // Bao loi neu danh sach rong
        return;
    }
    int kem = 0, tbYeu = 0, trungBinh = 0, kha = 0, gioi = 0;
    int total = countNodes(head); // Dem tong so sinh vien
    Node* current = head;

    if (*h == 1) { // Thong ke theo he so 10
        while (current != NULL) {
            if (current->data.DTB >= 0 && current->data.DTB < 4) kem++;
            else if (current->data.DTB >= 4 && current->data.DTB < 5.5) tbYeu++;
            else if (current->data.DTB >= 5.5 && current->data.DTB < 7) trungBinh++;
            else if (current->data.DTB >= 7 && current->data.DTB < 8.5) kha++;
            else if (current->data.DTB >= 8.5 && current->data.DTB <= 10) gioi++;
            current = current->next;
        }
    } else if (*h == 2) { // Thong ke theo he so 4
        while (current != NULL) {
            if (current->data.DTB >= 0 && current->data.DTB < 1.6) kem++;
            else if (current->data.DTB >= 1.6 && current->data.DTB < 2.2) tbYeu++;
            else if (current->data.DTB >= 2.2 && current->data.DTB < 2.8) trungBinh++;
            else if (current->data.DTB >= 2.8 && current->data.DTB < 3.4) kha++;
            else if (current->data.DTB >= 3.4 && current->data.DTB <= 4) gioi++;
            current = current->next;
        }
    }

    // Tinh ti le phan tram
    float tiLeKem = (total > 0) ? (kem * 100.0 / total) : 0;
    float tiLeTbYeu = (total > 0) ? (tbYeu * 100.0 / total) : 0;
    float tiLeTrungBinh = (total > 0) ? (trungBinh * 100.0 / total) : 0;
    float tiLeKha = (total > 0) ? (kha * 100.0 / total) : 0;
    float tiLeGioi = (total > 0) ? (gioi * 100.0 / total) : 0;

    // In ket qua thong ke
    printf("\n=== THONG KE TI LE HOC LUC ===\n");
    printf("Tong so sinh vien: %d\n", total);
    printf("Hoc luc Kem: %d sinh vien (%.2f%%)\n", kem, tiLeKem);
    printf("Hoc luc Trung Binh Yeu: %d sinh vien (%.2f%%)\n", tbYeu, tiLeTbYeu);
    printf("Hoc luc Trung Binh: %d sinh vien (%.2f%%)\n", trungBinh, tiLeTrungBinh);
    printf("Hoc luc Kha: %d sinh vien (%.2f%%)\n", kha, tiLeKha);
    printf("Hoc luc Gioi: %d sinh vien (%.2f%%)\n", gioi, tiLeGioi);
    printf("================================\n\n");
}

// Hien thi menu chinh
int menuChinh() {
    int luaChon;
    printf("\n=========== MENU CHINH ===========\n");
    printf(" 1. Nhap danh sach sinh vien\n");
    printf(" 2. Nhap danh sach sinh vien tu file\n");
    printf(" 3. Xuat danh sach sinh vien\n");
    printf(" 4. Sap xep danh sach\n");
    printf(" 5. Thong ke sinh vien hoc lai\n");
    printf(" 6. Xep loai hoc luc sinh vien\n");
    printf(" 7. Xuat danh sach ra file\n");
    printf(" 8. Dieu chinh danh sach\n");
    printf(" 9. Tim kiem sinh vien\n");
    printf("10. Chuyen Diem Trung Binh\n");
    printf("11. Thong ke ti le hoc luc\n");
    printf(" 0. Thoat chuong trinh\n");
    printf("==================================\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &luaChon); // Nhap lua chon nguoi dung
    return luaChon;
}

// Ham chinh
int main() {
    Node* head = NULL; // Khoi tao danh sach lien ket rong
    int y, z, t, k;
    int h = 1; // Bien trang thai he so diem (1: he 10, 2: he 4)
    int danhap = 0; // Bien kiem tra danh sach da duoc nhap chua
    int luaChon;
    void (*menudieuchinh[3])(Node**, int) = {themsinhvien, xoasinhvien, chinhsua}; // Mang con tro ham cho menu dieu chinh

    do {
        luaChon = menuChinh(); // Hien thi menu va lay lua chon
        switch (luaChon) {
            case 1: {
                int n;
                printf("Nhap so luong sinh vien: ");
                scanf("%d", &n); // Nhap so luong sinh vien
                nhapdanhsachmangsv(&head, n, h); // Nhap danh sach
                danhap = 1; // Danh dau danh sach da duoc nhap
                break;
            }
            case 2: {
                docDanhSachTuFile(&head, h); // Nhap danh sach tu file
                danhap = 1; // Danh dau danh sach da duoc nhap
                break;
            }
            case 3:
                if (danhap)
                    xuatdanhsachmangsv(head); // Xuat danh sach neu da nhap
                else
                    printf("Vui long nhap danh sach truoc!\n");
                break;
            case 4:
                if (danhap) {
                    do {
                        printf("Ban muon sap xep hay khong [1.Co, 2.Khong]: ");
                        scanf("%d", &z);
                        if (z == 1) {
                            printf("Chon kieu sap xep: \n");
                            printf("\n=========== MENU SAP XEP ===========\n");
                            printf("1. Ho va ten\n");
                            printf("2. Ma Sinh Vien\n");
                            printf("3. Nam sinh\n");
                            printf("4. Diem trung binh\n");
                            printf("5. Dia chi\n");
                            printf("==================================\n");
                            scanf("%d", &y);
                            switch (y) {
                                case 1:
                                    SapxepdanhsachtheoHT(&head); // Sap xep theo ho ten
                                    printf("Sap xep theo Ho va ten:\n");
                                    xuatdanhsachmangsv(head);
                                    break;
                                case 2:
                                    SapxepdanhsachtheoMSV(&head); // Sap xep theo ma sinh vien
                                    printf("Sap xep theo MSV:\n");
                                    xuatdanhsachmangsv(head);
                                    break;
                                case 3:
                                    SapxepdanhsachtheoNS(&head); // Sap xep theo nam sinh
                                    printf("Sap xep theo Nam sinh:\n");
                                    xuatdanhsachmangsv(head);
                                    break;
                                case 4:
                                    SapxepdanhsachtheoDTB(&head); // Sap xep theo diem trung binh
                                    printf("Sap xep theo Diem TB (giam dan):\n");
                                    xuatdanhsachmangsv(head);
                                    break;
                                case 5:
                                    SapxepdanhsachtheoDiachi(&head); // Sap xep theo dia chi
                                    printf("Sap xep theo Dia chi:\n");
                                    xuatdanhsachmangsv(head);
                                    break;
                                default:
                                    printf("Lua chon khong hop le.\n");
                                    break;
                            }
                        } else if (z != 2) {
                            printf("Vui long nhap lai!\n");
                        }
                    } while (z != 2);
                } else {
                    printf("Vui long nhap danh sach truoc!\n");
                }
                break;
            case 5:
                if (danhap)
                    thongkedanhsach(head, h); // Thong ke sinh vien hoc lai
                else
                    printf("Vui long nhap danh sach truoc!\n");
                break;
            case 6:
                if (danhap)
                    sapxephocluc(head, &h); // Xep loai hoc luc
                else
                    printf("Vui long nhap danh sach truoc!\n");
                break;
            case 7:
                if (danhap) {
                    SapxepdanhsachtheoHT(&head);
                    ghiFileDanhSach("HT.txt", head); // Ghi danh sach theo ho ten
                    SapxepdanhsachtheoMSV(&head);
                    ghiFileDanhSach("MSV.txt", head); // Ghi danh sach theo ma sinh vien
                    SapxepdanhsachtheoNS(&head);
                    ghiFileDanhSach("NS.txt", head); // Ghi danh sach theo nam sinh
                    SapxepdanhsachtheoDTB(&head);
                    ghiFileDanhSach("DTB.txt", head); // Ghi danh sach theo diem trung binh
                    SapxepdanhsachtheoDiachi(&head);
                    ghiFileDanhSach("DC.txt", head); // Ghi danh sach theo dia chi
                    printf("Da xuat danh sach theo cac kieu sap xep ra cac file:\n");
                    printf("- HT.txt\n- MSV.txt\n- NS.txt\n- DTB.txt\n- DC.txt\n");
                } else {
                    printf("Vui long nhap danh sach truoc!\n");
                }
                break;
            case 8:
                if (danhap) {
                    do {
                        printf("\n=========== MENU DIEU CHINH ===========\n");
                        printf("1. Them danh sach sinh vien\n");
                        printf("2. Xoa Sinh Vien\n");
                        printf("3. Cap nhat sinh vien\n");
                        printf("0. Thoat\n");
                        printf("==================================\n");
                        scanf("%d", &t);
                        switch (t) {
                            case 1:
                                menudieuchinh[0](&head, h); // Them sinh vien
                                break;
                            case 2:
                                menudieuchinh[1](&head, h); // Xoa sinh vien
                                break;
                            case 3:
                                menudieuchinh[2](&head, h); // Cap nhat sinh vien
                                break;
                            case 0:
                                printf("Da Thoat!\n");
                                break;
                            default:
                                printf("Lua chon khong hop le, vui long thu lai.\n");
                                break;
                        }
                    } while (t != 0);
                } else {
                    printf("Vui long nhap danh sach truoc!\n");
                }
                break;
            case 9:
                if (danhap)
                    timkiem(head); // Tim kiem sinh vien
                else
                    printf("Vui long nhap danh sach truoc!\n");
                break;
            case 10:
                if (danhap) {
                    do {
                        printf("\n=========== MENU DOI DIEM TRUNG BINH ===========\n");
                        printf("1. He So 10\n");
                        printf("2. He so 4\n");
                        printf("0. Thoat\n");
                        printf("==================================\n");
                        scanf("%d", &k);
                        switch (k) {
                            case 1:
                                diemheso10(head, &h); // Chuyen sang he so 10
                                break;
                            case 2:
                                diemheso4(head, &h); // Chuyen sang he so 4
                                break;
                            case 0:
                                printf("Tam biet\n");
                                break;
                            default:
                                printf("Lua chon khong hop le, vui long thu lai.\n");
                                break;
                        }
                    } while (k != 0);
                } else {
                    printf("Vui long nhap danh sach truoc!\n");
                }
                break;
            case 11:
                if (danhap)
                    thongKeHocLuc(head, &h); // Thong ke ti le hoc luc
                else
                    printf("Vui long nhap danh sach truoc!\n");
                break;
            case 0:
                printf("Tam biet!\n");
                printf("Nguyen Le Quoc Anh -- MSSV: 6551071003\n"); 
                break;
            default:
                printf("Lua chon khong hop le, vui long thu lai.\n");
                break;
        }
    } while (luaChon != 0);

    // Giai phong bo nho danh sach lien ket
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp); // Giai phong tung node
    }

    return 0;
}
