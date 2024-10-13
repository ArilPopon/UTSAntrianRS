#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct untuk menyimpan data pasien
typedef struct
{
    char name[50]; // Nama pasien
} Patient;

// Struct untuk merepresentasikan queue
typedef struct
{
    int front, rear;
    int capacity;
    Patient *queue; // Pointer ke array pasien
} Queue;

// Struct untuk menyimpan daftar pasien yang telah didaftarkan secara dinamis
typedef struct
{
    int total;         // Jumlah pasien yang telah terdaftar
    int capacity;      // Kapasitas dari array yang dialokasikan
    Patient *patients; // Pointer ke array pasien terdaftar
} RegisteredList;

// Fungsi untuk menginisialisasi antrian dengan kapasitas awal
void initializeQueue(Queue *q, int capacity)
{
    q->capacity = capacity;
    q->front = -1;
    q->rear = -1;
    q->queue = (Patient *)malloc(capacity * sizeof(Patient)); // Alokasi memori
}

// Fungsi untuk menginisialisasi daftar pasien terdaftar secara dinamis
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
void enqueue(Queue *q, RegisteredList *list, char name[])
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
    strcpy(q->queue[q->rear].name, name);
    printf("Pasien %s berhasil didaftarkan.\n", name);

    // Tambahkan pasien ke daftar pasien terdaftar
    if (list->total == list->capacity)
    {
        int newCapacity = list->capacity * 2;
        list->patients = (Patient *)realloc(list->patients, newCapacity * sizeof(Patient)); // Perbesar kapasitas daftar terdaftar
        list->capacity = newCapacity;
    }
    strcpy(list->patients[list->total].name, name);
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
    printf("Pasien %s diproses untuk pendaftaran.\n", q->queue[q->front].name);
    q->front++;

    // Reset antrian jika semua pasien telah diproses
    if (q->front > q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
}

// Fungsi untuk menampilkan isi antrian saat ini
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
        printf("%d. %s\n", i + 1, q->queue[i].name);
    }
}

// Fungsi untuk menampilkan daftar semua pasien yang telah didaftarkan
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
        printf("%d. %s\n", i + 1, list->patients[i].name);
    }
}

// Fungsi untuk membebaskan memori antrian
void freeQueue(Queue *q)
{
    free(q->queue);
}

// Fungsi untuk membebaskan memori daftar pasien terdaftar
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

    // Menu interaktif
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
            printf("Masukkan nama pasien: ");
            scanf("%s", name);
            enqueue(&q, &list, name); // Tambahkan ke antrian dan daftar pasien terdaftar
            break;
        case 2:
            dequeue(&q);
            break;
        case 3:
            displayQueue(&q);
            break;
        case 4:
            displayRegisteredPatients(&list);
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
