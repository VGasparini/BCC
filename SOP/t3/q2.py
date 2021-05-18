from math import ceil

# Funções utilitárias
def format_size(size):
    unit = ["B", "KB", "MB", "GB"]
    count = 0
    while size > 1024 ** (count + 1):
        count += 1
    size = round(size / (1024 ** count), 2)
    return f"{size} {unit[count]}"


def format_percentage(a, b):
    return "{:.3f}%".format(a / b * 100)


# Objeto descritor de arquivo
class File:
    def __init__(self, data):
        self.name, size = data.split()
        self.raw_size = int(size)

    def __gt__(self, other):
        if not isinstance(other, File):
            return True
        return self.raw_size > other.raw_size

    def __str__(self):
        formated_size = format_size(self.raw_size)
        return f"{self.name} - {formated_size}"


# Programa principal
if __name__ == "__main__":
    files_count = 0
    size_total = 0
    bigger_file = None
    zero_count = 0
    sizes = list()
    space_wasted = 0
    IO_BLOCK_SIZE = 4096
    space_allocated = 0

    with open("./lista-arqs", "r") as file_stream:
        for file_data in file_stream:
            file = File(file_data)
            files_count += 1
            bigger_file = max(bigger_file, file)
            zero_count += 1 if file.raw_size == 0 else 0
            size_total += file.raw_size
            space_allocated += ceil(file.raw_size / IO_BLOCK_SIZE) * IO_BLOCK_SIZE
            space_wasted += IO_BLOCK_SIZE - file.raw_size % IO_BLOCK_SIZE

            sizes.append(file.raw_size)

    sizes.sort()

    zeros_percentile = format_percentage(zero_count, files_count)

    mean = size_total / files_count
    leq_mean_percentile = format_percentage(
        sum(size <= mean for size in sizes), files_count
    )

    middle = files_count // 2
    if files_count % 2 == 0:
        median = sizes[middle]
    else:
        median = (sizes[middle] + sizes[middle + 1]) // 2

    count = 0
    while 2 ** count < median:
        count += 1

    ideal_block_size = 2 ** count
    ideal_block = format_size(ideal_block_size)

    one_block_count = sum(size <= ideal_block_size for size in sizes)
    one_block_count_percentile = format_percentage(one_block_count, files_count)
    bigger_file_ideal_size_blocks = ceil(bigger_file.raw_size / ideal_block_size)

    direct_pointers_size = IO_BLOCK_SIZE * 12
    simple_indirection_size = IO_BLOCK_SIZE ** 2 // 4
    double_indirection_size = IO_BLOCK_SIZE ** 3 // 16
    triple_indirection_size = IO_BLOCK_SIZE ** 4 // 64

    direct_pointers_count = sum(size <= direct_pointers_size for size in sizes)
    simple_indirection_count = sum(
        direct_pointers_size < size <= simple_indirection_size for size in sizes
    )
    double_indirection_count = sum(
        simple_indirection_size < size <= double_indirection_size for size in sizes
    )
    triple_indirection_count = sum(
        double_indirection_size < size <= triple_indirection_size for size in sizes
    )

    direct_pointers_percentile = format_percentage(direct_pointers_count, files_count)
    simple_indirection_percentile = format_percentage(
        simple_indirection_count, files_count
    )
    double_indirection_percentile = format_percentage(
        double_indirection_count, files_count
    )
    triple_indirection_percentile = format_percentage(
        triple_indirection_count, files_count
    )
    space_wasted_percentile = format_percentage(space_wasted, space_allocated)

    print("---=== Estatisticas ===---")
    print(f"{files_count} arquivos foram encontrados!")
    print(f"O maior arquivo encontrado foi {bigger_file}")
    print(
        f"Existem {zero_count} arquivos com tamanho igual a 0. Isso corresponde a {zeros_percentile} do total"
    )
    print(
        f"O tamanho médio é de {format_size(mean)}. {leq_mean_percentile} dos arquivos são de tamanho menor ou igual a esse média"
    )
    print(f"A mediana dos arquivos é {format_size(median)}")
    print(
        f"O menor tamanho de bloco tal que 50% dos arquivos ocupem apenas um bloco é de {format_size(ideal_block_size)}"
    )
    print(
        f"Caso fosse adotado blocos de {format_size(ideal_block_size)}, {one_block_count} arquivos utilizariam apenas um bloco, correspondendo a {one_block_count_percentile} dos arquivos."
    )
    print(
        f"O maior arquivo, {bigger_file}, utilizaria {bigger_file_ideal_size_blocks} blocos"
    )
    print("Considerando que os ponteiros de disco sejam de 32 bits")
    print(f"{direct_pointers_percentile} dos arquivos não precisam de indireção")
    print(f"{simple_indirection_percentile} dos arquivos precisam de indireção simples")
    print(f"{double_indirection_percentile} dos arquivos precisam de indireção dupla")
    print(f"{triple_indirection_percentile} dos arquivos precisam de indireção tripla")
    print(
        f"{space_wasted_percentile} do espaço alocado é desperdiçado por fragmentação interna. Isso corresponde a {format_size(space_wasted)} de espaço em disco"
    )
