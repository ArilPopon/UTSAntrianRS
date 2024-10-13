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
    int front, rear; // Indeks front dan rear untuk antrian
    int capacity;    // Kapasitas saat ini dari antrian
    Patient *queue;  // Pointer ke array pasien yang dialokasikan secara dinamis
} Queue;

// Fungsi untuk menginisialisasi antrian dengan kapasitas awal
void initializeQueue(Queue *q, int capacity)
{
    q->capacity = capacity;
    q->front = -1;
    q->rear = -1;
    q->queue = (Patient *)malloc(capacity * sizeof(Patient)); // Alokasi memori dinamis untuk array
}

// Fungsi untuk memeriksa apakah antrian penuh
int isFull(Queue *q)
{
    return q->rear == q->capacity - 1; // Rear berada di indeks terakhir, antrian penuh
}

// Fungsi untuk memeriksa apakah antrian kosong
int isEmpty(Queue *q)
{
    return q->front == -1 || q->front > q->rear; // Front tidak valid, artinya antrian kosong
}

// Fungsi untuk menambahkan pasien ke antrian
void enqueue(Queue *q, char name[])
{
    if (isFull(q))
    {
        // Jika antrian penuh, perbesar kapasitas dua kali lipat
        int newCapacity = q->capacity * 2;
        q->queue = (Patient *)realloc(q->queue, newCapacity * sizeof(Patient));
        q->capacity = newCapacity;
        printf("Antrian penuh! Kapasitas ditingkatkan menjadi %d.\n", newCapacity);
    }
    if (isEmpty(q))
    {
        q->front = 0; // Jika antrian kosong, set front ke 0 (elemen pertama)
    }
    q->rear++;                            // Increment rear untuk posisi antrian berikutnya
    strcpy(q->queue[q->rear].name, name); // Salin nama pasien ke dalam antrian
    printf("Pasien %s berhasil didaftarkan.\n", name);
}

// Fungsi untuk memproses pasien dari antrian
void dequeue(Queue *q)
{
    if (isEmpty(q))
    { // Cek apakah antrian kosong
        printf("Antrian kosong! Tidak ada pasien yang bisa diproses.\n");
        return;
    }
    printf("Pasien %s diproses untuk pendaftaran.\n", q->queue[q->front].name); // Tampilkan pasien yang diproses
    q->front++;                                                                 // Geser indeks front ke pasien berikutnya
    if (q->front > q->rear)
    {                            // Jika front melewati rear, antrian kosong
        q->front = q->rear = -1; // Reset antrian
    }
}

// Fungsi untuk menampilkan isi antrian
void displayQueue(Queue *q)
{
    if (isEmpty(q))
    { // Cek apakah antrian kosong
        printf("Antrian kosong!\n");
        return;
    }
    printf("Antrian Pendaftaran Pasien:\n");
    for (int i = q->front; i <= q->rear; i++)
    {                                                // Loop dari front hingga rear untuk menampilkan semua pasien
        printf("%d. %s\n", i + 1, q->queue[i].name); // Tampilkan indeks dan nama pasien
    }
}

// Fungsi untuk membebaskan memori antrian
void freeQueue(Queue *q)
{
    free(q->queue); // Bebaskan memori yang dialokasikan untuk queue
}

int main()
{
    Queue q;                              // Deklarasi antrian
    int initialCapacity = 2;              // Kapasitas awal untuk antrian
    initializeQueue(&q, initialCapacity); // Inisialisasi antrian dengan kapasitas awal

    int choice;
    char name[50];

    // Menu Utama
    do
    {
        printf("\nMenu Pendaftaran Pasien:\n");
        printf("1. Daftarkan Pasien\n");
        printf("2. Proses Pendaftaran\n");
        printf("3. Tampilkan Antrian\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice); // Ambil input dari pengguna

        switch (choice)
        {
        case 1:
            printf("Masukkan nama pasien: ");
            scanf("%s", name); // Input nama pasien
            enqueue(&q, name); // Tambahkan pasien ke antrian
            break;
        case 2:
            dequeue(&q); // Proses pasien dari antrian
            break;
        case 3:
            displayQueue(&q); // Tampilkan isi antrian
            break;
        case 4:
            printf("Keluar dari program.\n");
            freeQueue(&q); // Bebaskan memori sebelum keluar
            break;
        default:
            printf("Pilihan tidak valid.\n");
        }
    } while (choice != 4); // Ulangi sampai pengguna memilih keluar

    return 0;
}
