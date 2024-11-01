#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int tamanho;
    int tamanhoHeap;
} Heap;

int Pai(int i){
    return i/2;
}

int Esquerdo(int i) {
    return 2 * i;
}

int Direito(int i) {
    return 2 * i + 1;
}

void MaxHeapify(Heap *heap, int i) {
    int left = Esquerdo(i);
    int right = Direito(i);
    int maior;

    if (left < heap->tamanhoHeap && heap->arr[left] > heap->arr[i]) maior = left;
    else maior = i;

    if (right < heap->tamanhoHeap && heap->arr[right] > heap->arr[maior]) maior = right;

    if (maior != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[maior];
        heap->arr[maior] = temp;

        MaxHeapify(heap, maior);
    }
}

// Função ConstruirHeapMax
void ConstruirHeapMax(Heap *heap) {
    heap->tamanhoHeap = heap->tamanho;

    for (int i = heap->tamanho / 2 - 1; i >= 0; i--) MaxHeapify(heap, i);
}

void Heapsort(Heap *heap) {
    ConstruirHeapMax(heap);
    for (int i = heap->tamanho - 1; i >= 1; i--) {
        int temp = heap->arr[0];
        heap->arr[0] = heap->arr[i];
        heap->arr[i] = temp;

        heap->tamanhoHeap--;

        MaxHeapify(heap, 0);
    }
}

void ImprimirArray(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    Heap heap;
    heap.tamanho = 10;
    heap.tamanhoHeap = heap.tamanho;
    
    // Inicializando o heap com alguns valores
    int valores[] = {4, 10, 3, 5, 1, 6, 8, 9, 2, 7};
    for (int i = 0; i < heap.tamanho; i++) {
        heap.arr[i] = valores[i];
    }

    printf("Array original:\n");
    ImprimirArray(heap.arr, heap.tamanho);

    // Aplicando heapsort
    Heapsort(&heap);

    printf("Array ordenado:\n");
    ImprimirArray(heap.arr, heap.tamanho);

    return 0;
}
