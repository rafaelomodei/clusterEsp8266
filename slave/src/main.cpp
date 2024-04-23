#include <ESP8266WiFi.h>

// Função para ordenar um array usando Bucket Sort
void bucketSort(int arr[], int n)
{
    // Defina o número de baldes como 10 para simplificar
    const int num_buckets = 10;

    // Crie os baldes
    std::vector<int> buckets[num_buckets];

    // Coloque os elementos no balde apropriado
    for (int i = 0; i < n; i++)
    {
        int bucket_index = arr[i] / num_buckets;
        buckets[bucket_index].push_back(arr[i]);
    }

    // Ordenar individualmente cada balde e colocar de volta no array
    int index = 0;
    for (int i = 0; i < num_buckets; i++)
    {
        std::sort(buckets[i].begin(), buckets[i].end());
        for (int j = 0; j < buckets[i].size(); j++)
        {
            arr[index++] = buckets[i][j];
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(100);

    // Gerar uma lista de 100 mil elementos aleatórios
    const int tamanho_lista = 100;
    int lista_desordenada[tamanho_lista];
    for (int i = 0; i < tamanho_lista; i++)
    {
        lista_desordenada[i] = rand() % 100; // Números aleatórios entre 0 e 999999
    }

    int n = sizeof(lista_desordenada) / sizeof(lista_desordenada[0]);

    Serial.println("Array original:");
    for (int i = 0; i < n; i++)
    {
        Serial.print(lista_desordenada[i]);
        Serial.print(" ");
    }
    Serial.println();

    // Chame a função de ordenação Bucket Sort
    bucketSort(lista_desordenada, n);

    Serial.println("Array ordenado:");
    for (int i = 0; i < n; i++)
    {
        Serial.print(lista_desordenada[i]);
        Serial.print(" ");
    }
}

void loop()
{
    // nothing to do here
}
