import matplotlib.pyplot as plt
import matplotlib
import numpy as np
from scipy import linalg

TEST_MAX_LENGTH = 24
TEST_COUNT = 20
TEST_STEP = 2

values_t = {
    0: [],
    1: []
}

values_l = [i for i in range(0, TEST_MAX_LENGTH + 1, TEST_STEP)]


def get_data_from_files():
    with open("../../test.txt", "r") as file:
        sum_t = [0.0, 0.0]
        count = 0

        for line in file.readlines():
            num = list(map(float, line.split()))[0]

            values_t[count % 2].append(num)

            count += 1


def plot_time():
    matplotlib.rcParams.update({'font.size': 18})
    matplotlib.rcParams.update({'font.family': 'Times New Roman'})
    matplotlib.rcParams.update({'figure.figsize': (10, 7)})
    matplotlib.rcParams.update({'axes.prop_cycle': matplotlib.cycler(color=['black'])})

    plt.plot(values_l, values_t[0], 'o', label='Коэффициент отражения равен 0')
    plt.plot(values_l, values_t[1], 'v', label='Коэффицинт отражения не равен 0')

    plt.xlabel('Количество фигур на сцене')
    plt.ylabel(r'Процессорное время (тики)')

    ax = plt.gca()
    ax.margins(0.001)

    plt.legend(fontsize=18)

    # plt.loglog()

    plt.tight_layout()

    plt.show()

    val_t_1 = np.array(values_t[0])
    val_t_2 = np.array(values_t[1])
    val_x = np.array(values_l)
    # m = len(val_x)
    # X1 = np.stack((np.ones(m), val_x, val_x**8)).T
    # X2 = np.stack((np.ones(m), val_x, val_x**6)).T
    # beta1, resuaials1, _, _ = linalg.lstsq(X1, val_t_1)
    # beta2, residuals2, rank2, sv2 = linalg.lstsq(X2, val_t_2)
    # print(resuaials1)
    # print(residuals2)
    # print(beta1)
    # print(beta2)

    cof1, residuals1, _, _, _ = np.polyfit(val_x, val_t_1, 6, full=True)
    print(cof1)
    print(residuals1)
    p1 = np.poly1d(cof1)
    y_t_1 = p1(val_x)

    cof2, residuals2, _, _, _ = np.polyfit(val_x, val_t_2, 10, full=True)
    print(cof2)
    print(residuals2)
    p2 = np.poly1d(cof2)
    y_t_2 = p2(val_x)

    # plt.plot(values_l, X1@beta1, label='Апроксимация при коэффициенте отражения равному 0')
    # plt.plot(values_l, X2@beta2, linestyle='--', label='Апроксимация при при коэффициенте отражения не равному 0')
    # plt.plot(values_l, values_t[0], 'o', label='Отсуствие рекурсивной части алгоритма')
    # plt.plot(values_l, values_t[1], 'v', label='Выполнение рекурсивной части алгоритма')

    plt.plot(values_l, y_t_1, label='Апроксимация при коэффициенте отражения равному 0')
    plt.plot(values_l, y_t_2, linestyle='--', label='Апроксимация при при коэффициенте отражения не равному 0')
    plt.plot(values_l, values_t[0], 'o', label='Отсуствие рекурсивной части алгоритма')
    plt.plot(values_l, values_t[1], 'v', label='Выполнение рекурсивной части алгоритма')
    ax = plt.gca()
    ax.margins(0.001)

    plt.legend(fontsize=18)

    # plt.loglog()
    plt.xlabel('Количество фигур на сцене')
    plt.ylabel(r'Процессорное время (тики)')
    plt.tight_layout()
    plt.show()

# def plot_mem():
#     plt.plot(values_l, values_m[1], linestyle='solid', label='Сортировка Шелла')
#     plt.plot(values_l, values_m[2], 'd', linestyle='solid', label='Сортировка Перемешиванием')
#     plt.plot(values_l, values_m[3], linestyle='dashed', label='Плавная Сортировка')
#
#     plt.xlabel('Количество элементов в массиве')
#     plt.ylabel(r'Память (байт)')
#
#     ax = plt.gca()
#     ax.margins(0.001)
#
#     plt.legend(fontsize=10)
#
#     plt.loglog()
#
#     plt.tight_layout()
#
#     plt.show()


get_data_from_files()
plot_time()
# plot_mem()

for i in range(len(values_t[1])):
     print(f'   \\num{{{i * TEST_STEP}}} & \\num{{{values_t[0][i]}}}  & \\num{{{values_t[1][i]}}}  \\\\\\hline')

# print('-------')
#
# for i in range(len(values_m[1])):
#     print(f'   \\num{{{i * TEST_STEP}}} &