# park-mail-ru-algorithms-M2


# 1. Хеш-таблица
	Все языки 	Python 3.7.3
Ограничение времени 	0.2 секунды 	0.8 секунд
Ограничение памяти 	15Mb 	45Mb
Ввод 	стандартный ввод или input.txt
Вывод 	стандартный вывод или output.txt

Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.

Вариант 1. Для разрешения коллизий используйте квадратичное пробирование.
i-ая проба g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
Вариант 2. Для разрешения коллизий используйте двойное хеширование.
Формат ввода

Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и следующей за ним через пробел строки, над которой проводится операция. Тип операции – один из трех символов: + означает добавление данной строки в множество; - означает удаление строки из множества; ? означает проверку принадлежности данной строки множеству. При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
Формат вывода

Программа должна вывести для каждой операции одну из двух строк OK или FAIL.

Для операции '?': OK, если элемент присутствует во множестве. FAIL иначе.

Для операции '+': FAIL, если добавляемый элемент уже присутствует во множестве и потому не может быть добавлен. OK иначе.

Для операции '-': OK, если элемент присутствовал во множестве и успешно удален. FAIL иначе.

# 2_1. Обход дерева в порядке in-order
Ограничение времени 	0.2 секунды
Ограничение памяти 	64Mb
Ввод 	стандартный ввод или input.txt
Вывод 	стандартный вывод или output.txt

Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root. Выведите элементы в порядке in-order (слева направо).

Рекурсия запрещена.

# 4_1. Солдаты
Ограничение времени 	1 секунда
Ограничение памяти 	20Mb
Ввод 	стандартный ввод или input.txt
Вывод 	стандартный вывод или output.txt

В одной военной части решили построить в одну шеренгу по росту. Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие, а в конце – самые низкие. За расстановку солдат отвечал прапорщик, который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать, перед каким солдатом в строе он должен становится. Требуемая скорость выполнения команды - O(log n).
Формат ввода

Первая строка содержит число N – количество команд (1 ≤ N ≤ 90 000). В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата, натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
Формат вывода

На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции, на которую должен встать этот солдат (все стоящие за ним двигаются назад). 

