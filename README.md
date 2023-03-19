# OS_HW1
ИДЗ №1
Жуков Фёдор Сергеевич БПИ218
Сделано на 7 баллов

Задача: Разработать программу, которая «переворачивает» заданную позициями N1–N2 часть ASCII–строки символов (N1, N2 вводятся как параметры)

Программа на 4 (https://github.com/Fedosz/OS_HW1/tree/main/4)

Схема работы программы:
input.txt -> process1 (обработка входного файла) --pipe1> process2 (обработка строки) --pipe2> process3 -> output.txt

Произведено 5 тестов, каждый из которых приведен в папках программы.
Сами тесты: 
./hw test1.txt out1.txt 1 2 

./hw test2.txt out2.txt 1 4

./hw test3.txt out3.txt 2 5

./hw test4.txt out4.txt 2 8

./hw test5.txt out5.txt 0 4

test1: Easy             /        out1: Esay

test2: Harder            /       out2: Hedrar

test3: More hard          /      out3: Moh erard

test4: Closely the hardest /     out4: Clt ylesohe hardest

test5: number               /    out5: ebmunr

Схема работы программы на 5 (https://github.com/Fedosz/OS_HW1/tree/main/5):

input.txt -> process1 (обработка входного файла) --fifo1> process2 --fifo2> process3 -> output.txt

Схема работы программы на 6 (https://github.com/Fedosz/OS_HW1/tree/main/6):

input.txt -> process1 --pipe> process2 --pipe> process 1 -> output.txt

Схема работы программы на 7(https://github.com/Fedosz/OS_HW1/tree/main/7):

input.txt -> process1 --fifo> process2 --fifo> process 1 -> output.txt
