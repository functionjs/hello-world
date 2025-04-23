#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <atomic>
#include <vector>

// Глобальний лічильник для імен файлів, щоб забезпечити унікальність
std::atomic<int> thread_counter{0};
std::vector<pthread_t> threads;

           // Функція, що виконується паралельними потоками
          // -------------------------------------------------------------
         // -------------------------------------------------------------
        // -------------------------------------------------------------
        void* alarm_thread(void* arg) {
            int x = *(int*)arg;


            // Отримуємо унікальне ім'я файлу для кожного потоку
            int thread_id = thread_counter.fetch_add(1); // Атомарно збільшує лічильник і отримує унікальний ідентифікатор
             std::string filename = "alarm_" + std::to_string(thread_id) + ".txt";

            // Отримуємо поточний час початку
            auto start_time = std::chrono::system_clock::now();
            std::time_t start_time_t = std::chrono::system_clock::to_time_t(start_time);

             // Виводимо повідомлення про початок роботи в консоль
//             std::cout << "Thread with a delay of " << x << " seconds started. Start time: "
//                        << std::put_time(std::localtime(&start_time_t), "%Y-%m-%d %H:%M:%S") << std::endl;

            // Записуємо повідомлення про початок роботи у файл
            std::ofstream file(filename);
             if (file.is_open()) {
                  file << "Thread with a delay of " << x << " seconds started. Start time: "
                        << std::put_time(std::localtime(&start_time_t), "%Y-%m-%d %H:%M:%S") << "\n";
             } else {
                  std::cerr << "Error opening file: " << filename << std::endl;
                  return nullptr;
             }

             // Затримка на x секунд
             sleep(x);

            //  Отримуємо поточний час завершення
            auto end_time = std::chrono::system_clock::now();
            std::time_t end_time_t = std::chrono::system_clock::to_time_t(end_time);

             // Виводимо повідомлення про завершення роботи в консоль
//             std::cout << "Thread with a delay of " << x << " seconds finished. End time: "
//                        << std::put_time(std::localtime(&end_time_t), "%Y-%m-%d %H:%M:%S") << std::endl;

             // Записуємо повідомлення про завершення роботи у файл і закриваємо його
             file << "Thread with a delay of " << x << " seconds finished. End time: "
                   << std::put_time(std::localtime(&end_time_t), "%Y-%m-%d %H:%M:%S") << "\n";
             file.close();

               delete (int*)arg; // Звільняємо пам'ять, виділену для параметра

             pthread_exit(nullptr);
             return nullptr;
           }

int main() {
    while (true) {
        int x;
        std::cout << "Enter delay time in seconds (negative number to exit): ";
         std::cin >> x;

         if (x < 0) {
             std::cout << "Program terminated. Press any key to exit..." << std::endl;
              //std::cin.get(); // Чекаємо натискання будь-якої клавіші
              //std::cin.get(); // Другий get для виходу після натискання клавіші
              for (auto& thread_id : threads) {
                pthread_join(thread_id, nullptr);
              }
               break;
         } else if (x > 0) {
                  // Виділяємо пам'ять для параметра потоку
                  int* arg = new int(x);
     
                   pthread_t thread_id;
                  //  pthread_attr_t attr;
     
                  //  // Ініціалізуємо атрибути потоку
                  //   pthread_attr_init(&attr);
                  //    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

     
                      // Створюємо від'єднаний потік
                      if (pthread_create(&thread_id, nullptr, alarm_thread, arg) != 0) {
                        std::cerr << "Error creating thread." << std::endl;
                         delete arg; // Звільняємо пам'ять у разі помилки
                      } 
                      else {
                        threads.push_back(thread_id);
                      }
     
                  //     // Знищуємо атрибути потоку
                  // pthread_attr_destroy(&attr);
              } else {
                       std::cout << "Enter a positive number or a negative number to exit." << std::endl;
                     }
    }

     return 0;
}

