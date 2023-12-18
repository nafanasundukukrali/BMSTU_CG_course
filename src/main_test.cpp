#include <scene/scene.h>
#include <QPixmap>
#include <QApplication>
#include <memory>
#include <stdlib.h>
#include <vector>
#include <string>
#include <locale>
#include <iostream>
#include <codecvt>
#include <fstream>
#include <experimental/random>

#define TEST_COUNT 10
#define TEST_MAX_ARRAY_SIZE 64
#define TEST_STEP 2

#define TEST_FILE_NAME "../test.txt"


int main(int argc, char* argv[])
{
    std::wcout << L"===== ТЕСТОВЫЙ РЕЖИМ =====" << std::endl;
    QApplication a(argc, argv);
    std::shared_ptr<QPixmap> _scene = std::make_shared<QPixmap>(1000, 900);
    std::wofstream file(TEST_FILE_NAME);
    if (!file.is_open())
        throw "Файл для записи тестовых данных не получилось открыть!";

    for (size_t i = 0; i <= TEST_MAX_ARRAY_SIZE; i += TEST_STEP)
    {
        Scene scene(_scene, i);
        size_t all_dur_1 = 0, all_dur_2 = 0;

        for (size_t j = 0; j < TEST_COUNT; j++)
        {
            scene.change_reflect_and_shine_k(Vector3D(0, 0, 0), 0);
            uint64_t start, end;
            start = clock();
            scene.draw();
            end = clock();
            size_t duration = end - start;
            all_dur_1 += duration;
            std::wcout << i << ' ' << j << ' ' << "no recurs " << duration << std::endl;
            scene.change_reflect_and_shine_k(Vector3D(1, 1, 1), 0);
            start = clock();
            scene.draw();
            end = clock();
            duration = end - start;
            all_dur_2 += duration;
            std::wcout << i << ' ' << j << ' ' << "recurs " << duration << std::endl;
        }

        file << std::setprecision(2) << std::fixed << all_dur_1 / double(TEST_COUNT) << std::endl;
        file << std::setprecision(2) << std::fixed << all_dur_2 / double(TEST_COUNT) << std::endl;
    }

    a.exit();
}
