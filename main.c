#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct untuk menyimpan data pasien
typedef struct
{
    char name[50];    // Nama pasien
    int number;       // Nomor urut pasien
    char service[50]; // Layanan yang dipilih
} Patient;

// Struct untuk merepresentasikan queue
typedef struct
{
    int front, rear;
    int capacity;
    Patient *queue; // Pointer ke array pasien yang dialokasikan secara dinamis
} Queue;

// Struct untuk menyimpan daftar pasien yang telah didaftarkan secara dinamis
typedef struct
{
    int total;         // Jumlah pasien yang telah terdaftar
    int capacity;      // Kapasitas dari array yang dialokasikan
    Patient *patients; // Pointer ke array pasien terdaftar
} RegisteredList;

int patientCounter = 0; // untuk no pasien

// Fungsi untuk menginisialisasi antrian
void initializeQueue(Queue *q, int capacity)
{
    q->capacity = capacity;
    q->front = -1;
    q->rear = -1;
    q->queue = (Patient *)malloc(capacity * sizeof(Patient)); // Alokasi memori
}

// Fungsi untuk menginisialisasi daftar pasien terdaftar
void initializeRegisteredList(RegisteredList *list, int capacity)
{
    list->total = 0;
    list->capacity = capacity;
    list->patients = (Patient *)malloc(capacity * sizeof(Patient)); // Alokasi memori awal
}

// Fungsi untuk memeriksa apakah antrian penuh
int isFull(Queue *q)
{
    return q->rear == q->capacity - 1;
}

// Fungsi untuk memeriksa apakah antrian kosong
int isEmpty(Queue *q)
{
    return q->front == -1 || q->front > q->rear;
}

// Fungsi untuk menambahkan pasien ke antrian
void enqueue(Queue *q, RegisteredList *list, char name[], char service[])
{
    if (isFull(q))
    {
        int newCapacity = q->capacity * 2;
        q->queue = (Patient *)realloc(q->queue, newCapacity * sizeof(Patient)); // Perbesar kapasitas antrian
        q->capacity = newCapacity;
        // printf("Antrian penuh! Kapasitas ditingkatkan menjadi %d.\n", newCapacity);
    }
    if (isEmpty(q))
    {
        q->front = 0;
    }
    q->rear++;

    // Tambahkan pasien ke antrian
    patientCounter++; // Tambah nomor urut pasien
    strcpy(q->queue[q->rear].name, name);
    strcpy(q->queue[q->rear].service, service); // Tetapkan layanan dokter
    q->queue[q->rear].number = patientCounter;  // Tetapkan nomor urut pasien
    printf("Pasien %s (Nomor %d, Layanan: %s) berhasil didaftarkan.\n", name, patientCounter, service);

    // Tambahkan pasien ke daftar pasien terdaftar
    if (list->total == list->capacity)
    {
        int newCapacity = list->capacity * 2;
        list->patients = (Patient *)realloc(list->patients, newCapacity * sizeof(Patient)); // Perbesar kapasitas daftar terdaftar
        list->capacity = newCapacity;
    }
    strcpy(list->patients[list->total].name, name);
    strcpy(list->patients[list->total].service, service); // Tetapkan layanan dokter di daftar terdaftar
    list->patients[list->total].number = patientCounter;  // Tetapkan nomor urut pasien
    list->total++;
}

// Fungsi untuk memproses pasien dari antrian
void dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Antrian kosong! Tidak ada pasien yang bisa diproses.\n");
        return;
    }
    printf("Nomor %d, %s Silahkan menuju %s.\n",
           q->queue[q->front].number, q->queue[q->front].name, q->queue[q->front].service);
    q->front++;

    // Reset antrian jika semua pasien telah diproses
    if (q->front > q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
}

// Fungsi menampilkan isi antrian saat ini
void displayQueue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Antrian kosong!\n");
        return;
    }
    printf("Antrian Pendaftaran Pasien:\n");
    for (int i = q->front; i <= q->rear; i++)
    {
        printf("Nomor %d, Nama: %s, Layanan: %s\n",
               q->queue[i].number, q->queue[i].name, q->queue[i].service);
    }
}

// Fungsi tampilkan daftar pasien yang terdaftar
void displayRegisteredPatients(RegisteredList *list)
{
    if (list->total == 0)
    {
        printf("Belum ada pasien yang terdaftar.\n");
        return;
    }
    printf("Daftar Semua Pasien yang Telah Didaftarkan:\n");
    for (int i = 0; i < list->total; i++)
    {
        printf("Nomor %d, Nama: %s, Layanan: %s\n", list->patients[i].number, list->patients[i].name, list->patients[i].service);
    }
}

// Fungsi bebaskan memori antrian
void freeQueue(Queue *q)
{
    free(q->queue);
}

// Fungsi bebaskan daftar pasien
void freeRegisteredList(RegisteredList *list)
{
    free(list->patients);
}

int main()
{
    Queue q;
    RegisteredList list;

    int initialCapacity = 2;                          // Kapasitas awal
    initializeQueue(&q, initialCapacity);             // Inisialisasi antrian
    initializeRegisteredList(&list, initialCapacity); // Inisialisasi daftar pasien terdaftar

    int choice;
    char name[50];
    int serviceChoice;
    char service[50];

    // Menu Utama
    do
    {
        printf("\nMenu Pendaftaran Pasien:\n");
        printf("1. Daftarkan Pasien\n");
        printf("2. Proses Pendaftaran\n");
        printf("3. Tampilkan Antrian Saat Ini\n");
        printf("4. Daftar Semua Pasien yang Telah Didaftarkan\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            getchar(); // Membersihkan buffer input agar tidak ada masalah dengan input nama
            printf("Masukkan nama pasien: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0; // Hapus karakter newline dari input

            printf("Pilih layanan dokter:\n");
            printf("1. Poliklinik Umum\n");
            printf("2. Poliklinik Penyakit Dalam\n");
            printf("3. Poliklinik Gigi\n");
            printf("4. Poliklinik Anak\n");
            printf("5. Poliklinik THT\n");
            printf("Pilihan layanan: ");
            scanf("%d", &serviceChoice);

            switch (serviceChoice)
            {
            case 1:
                strcpy(service, "Poliklinik Umum");
                break;
            case 2:
                strcpy(service, "Poliklinik Penyakit Dalam");
                break;
            case 3:
                strcpy(service, "Poliklinik Gigi");
                break;
            case 4:
                strcpy(service, "Poliklinik Anak");
                break;
            case 5:
                strcpy(service, "Poliklinik THT");
                break;
            default:
                printf("Pilihan tidak valid.\n");
                continue;
            }

            enqueue(&q, &list, name, service); // Tambahkan ke antrian dan daftar pasien
            break;
        case 2:
            dequeue(&q); // Proses Antrian
            break;
        case 3:
            displayQueue(&q); // Tampilkan Antrian
            break;
        case 4:
            displayRegisteredPatients(&list); // Tampilkan Daftar Pasien
            break;
        case 5:
            printf("Keluar dari program.\n");
            freeQueue(&q);
            freeRegisteredList(&list);
            break;
        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (choice != 5);

    return 0;
}
