import matplotlib.pyplot as plt


def read_data(file_path):
    with open(file_path, 'r') as file:
        data = file.readlines()

    # Convert each line into a float
    extracted_data = [float(line.strip()) for line in data if line.strip().replace('.', '', 1).isdigit()]
    return extracted_data


def plot_histogram(data):
    labels = ["Sekwencyjnie", "Równolegle\n(thread)", "Równolegle\n(thread + mutex)", "Równolegle\n(OpenMP)",
              "Równolegle\n(OpenMP + critical)"]
    plt.bar(labels, data, color='blue', edgecolor='black', alpha=0.7)

    # Add horizontal grid lines
    plt.grid(axis='y', linestyle='--', alpha=0.7)

    # Display values above bars
    for i, value in enumerate(data):
        plt.text(i, value + 1, f'{value:.2f}', ha='center', fontsize=10)

    plt.xlabel('Typ wykonania')
    plt.ylabel('Czas wykonania (ms)')
    plt.title('Czasy wykonania dla różnych metod (100,500)')
    plt.xticks(rotation=0)  # Straighten text labels
    plt.show()


def main():
    file_path = r'C:\Users\Yami\source\repos\Wspolbiezne1\Wspolbiezne1\output.txt'
    data = read_data(file_path)
    if data:
        plot_histogram(data)
    else:
        print("Brak poprawnych danych liczbowych w pliku.")


if __name__ == "__main__":
    main()
