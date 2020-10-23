import pandas as pd
import matplotlib.pyplot as plot
import sys

def ft_visual(file):
    df = pd.read_csv(file)

    plot.scatter(df['km'], df['price'])
    plot.xlabel('mileage')
    plot.ylabel('price')
    plot.show()

    mas = []
    with open("model.txt") as f:
        mas = list(map(float, f.read().strip().split('\n')))

    plot.scatter(df['km'], df['price'])
    plot.plot(df['km'], mas[0] + mas[1] * (df['km'] - mas[2]) / mas[3])
    plot.xlabel('mileage')
    plot.ylabel('price')
    plot.show()

if __name__ == "__main__":
    try:
        if (len(sys.argv) == 2):
            ft_visual(sys.argv[1])
        else:
            print("Error argv for python program")
    except Exception:
        print('Ошибка во время работы, не те аргументы!!!')