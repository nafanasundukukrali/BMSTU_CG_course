import matplotlib.pyplot as plt
import matplotlib
import numpy

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

    plt.plot(values_l, values_t[0], linestyle='solid', label='Отсуствие рекурсивной части алгоритма')
    plt.plot(values_l, values_t[1], linestyle='dashed', label='Выполнение рекурсивной части алгоритма')

    plt.xlabel('Количество фигур на сцене')
    plt.ylabel(r'Процессорное время (тики)')

    ax = plt.gca()
    ax.margins(0.001)

    plt.legend(fontsize=18)

    # plt.loglog()

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