/*
 * ШПАРГАЛКА: ввод-вывод в файлы на языке C (заголовок stdio.h)
 *
 * Файл можно скомпилировать и запустить. Программа создаёт временные файлы
 * и удаляет их в конце.
 *
 * ОБЩАЯ СХЕМА
 *     FILE* fp = fopen(имя, режим);    открыть
 *     if (fp == NULL) { ... }          проверить, что открылся
 *     ...                              читать или писать
 *     fclose(fp);                      закрыть
 *
 * РЕЖИМЫ fopen
 *     "r"   чтение; файл должен существовать
 *     "w"   запись; файл создаётся, старое содержимое стирается
 *     "a"   дозапись в конец; файл создаётся, если его нет
 *     "r+"  чтение и запись; файл должен существовать, не стирается
 *     "w+"  чтение и запись; содержимое стирается
 *     "a+"  чтение и дозапись в конец
 *     Буква b означает бинарный режим: "rb", "wb", "ab", "r+b".
 *
 * ЧТО ЧЕМ ЧИТАТЬ И ПИСАТЬ
 *     Символы             getc,    putc
 *     Строки              fgets,   fputs
 *     Значения по формату fscanf,  fprintf
 *     Блоки байтов        fread,   fwrite
 *
 * ЧТО ВОЗВРАЩАЕТСЯ ПРИ КОНЦЕ ФАЙЛА ИЛИ ОШИБКЕ
 *     fopen   NULL
 *     getc    EOF
 *     fgets   NULL
 *     fscanf  число прочитанных значений или EOF
 *     fread   число прочитанных элементов (может быть меньше запрошенного)
 */

/* Для Visual Studio: разрешает fopen и fscanf без предупреждения C4996. */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#define TEXT_FILE    "cheat_text.txt"
#define BIN_FILE     "cheat_bin.dat"
#define RENAMED_FILE "cheat_renamed.txt"


/* 1. ОТКРЫТИЕ И ЗАКРЫТИЕ. Результат fopen проверяем всегда. */
static int demo_open_close(void)
{
    FILE* fp = fopen(TEXT_FILE, "w");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }

    /* Закрываем только файл, который удалось открыть: fclose(NULL) нельзя. */
    fclose(fp);
    return 0;
}


/* 2. ПОСИМВОЛЬНО: putc и getc. */
static int demo_chars(void)
{
    const char* message = "Hello";
    size_t n = strlen(message);    /* strlen не считает завершающий '\0' */

    FILE* fp = fopen(TEXT_FILE, "w");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }
    for (size_t i = 0; i < n; i++)
        putc(message[i], fp);
    fclose(fp);

    fp = fopen(TEXT_FILE, "r");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }

    /* Только int: в char значение EOF нельзя надёжно отличить от символа. */
    int c;
    printf("chars: ");
    while ((c = getc(fp)) != EOF)
        putchar(c);
    putchar('\n');

    fclose(fp);
    return 0;
}


/* 3. ПОСТРОЧНО: fputs и fgets. */
static int demo_lines(void)
{
    FILE* fp = fopen(TEXT_FILE, "w");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }
    /* fputs не добавляет перевод строки сам. */
    fputs("first line\n", fp);
    fputs("second line\n", fp);
    fclose(fp);

    fp = fopen(TEXT_FILE, "r");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }

    /* fgets читает не больше sizeof buffer - 1 символов и оставляет '\n'. */
    char buffer[64];
    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        /* Убираем '\n'. У последней строки файла его может не быть. */
        buffer[strcspn(buffer, "\n")] = '\0';
        printf("line: [%s], length %zu\n", buffer, strlen(buffer));
    }

    fclose(fp);
    return 0;
}


/* 4. ПО ФОРМАТУ: fprintf и fscanf. */
static int demo_format(void)
{
    FILE* fp = fopen(TEXT_FILE, "w");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }
    fprintf(fp, "%s %d\n", "Tom", 23);
    fprintf(fp, "%s %d\n", "Ann", 31);
    fclose(fp);

    fp = fopen(TEXT_FILE, "r");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }

    /* Ширина %s на 1 меньше размера массива: нужно место для '\0'. */
    char name[20];
    int age;

    /* Сравниваем с числом ожидаемых значений, а не с EOF. */
    while (fscanf(fp, "%19s %d", name, &age) == 2)
        printf("person: %s, %d\n", name, age);

    fclose(fp);
    return 0;
}


/* 5. ДОЗАПИСЬ: режим "a" сохраняет содержимое файла. */
static int demo_append(void)
{
    FILE* fp = fopen(TEXT_FILE, "a");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }
    fprintf(fp, "%s %d\n", "Kim", 19);
    fclose(fp);
    return 0;
}


/* 6. БЛОКАМИ: fwrite и fread. Для бинарных данных режимы "wb" и "rb". */
static int demo_blocks(void)
{
    int numbers[5] = { 10, 20, 30, 40, 50 };
    size_t n = sizeof numbers / sizeof numbers[0];

    FILE* fp = fopen(BIN_FILE, "wb");
    if (fp == NULL)
    {
        perror(BIN_FILE);
        return -1;
    }
    size_t written = fwrite(numbers, sizeof numbers[0], n, fp);
    fclose(fp);

    int loaded[5];
    fp = fopen(BIN_FILE, "rb");
    if (fp == NULL)
    {
        perror(BIN_FILE);
        return -1;
    }
    /* Возвращается число элементов, а не байтов. */
    size_t got = fread(loaded, sizeof loaded[0], n, fp);
    fclose(fp);

    printf("blocks: written %zu, read %zu, last = %d\n", written, got, loaded[got - 1]);
    return 0;
}


/* 7. ПОЗИЦИЯ В ФАЙЛЕ: fseek, ftell, rewind.
 *    Точка отсчёта: SEEK_SET (начало), SEEK_CUR (текущая), SEEK_END (конец).
 *    В текстовом режиме надёжны только смещение 0 и значения от ftell. */
static int demo_seek(void)
{
    FILE* fp = fopen(BIN_FILE, "rb");
    if (fp == NULL)
    {
        perror(BIN_FILE);
        return -1;
    }

    /* Размер файла: переходим в конец и спрашиваем позицию. */
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    /* Читаем третий элемент (индекс 2). */
    int value = 0;
    fseek(fp, 2 * (long)sizeof value, SEEK_SET);
    size_t third = fread(&value, sizeof value, 1, fp);

    /* rewind возвращает в начало и сбрасывает признаки конца и ошибки. */
    int first = 0;
    rewind(fp);
    size_t head = fread(&first, sizeof first, 1, fp);

    fclose(fp);

    if (third == 1 && head == 1)
        printf("seek: size %ld bytes, a[2] = %d, a[0] = %d\n", size, value, first);
    return 0;
}


/* 8. ОШИБКИ: perror, feof, ferror. */
static int demo_errors(void)
{
    /* Этот файл нарочно не существует, сообщение об ошибке ожидаемо. */
    FILE* missing = fopen("no_such_file.txt", "r");
    if (missing == NULL)
        perror("expected error, no_such_file.txt");
    else
        fclose(missing);

    FILE* fp = fopen(TEXT_FILE, "r");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }

    int c;
    while ((c = getc(fp)) != EOF)
    {
        /* Пропускаем файл до конца. */
    }

    /* EOF означает и конец файла, и ошибку. Различаем их после цикла. */
    if (ferror(fp))
        puts("errors: read error");
    else if (feof(fp))
        puts("errors: reached end of file");

    fclose(fp);
    return 0;
}


/* 9. СТАНДАРТНЫЕ ПОТОКИ: stdout и stderr имеют тип FILE*.
 *    Одна функция может писать и в файл, и на экран. */
static void write_report(FILE* stream, const char* text)
{
    fprintf(stream, "report: %s\n", text);
}

static int demo_streams(void)
{
    write_report(stdout, "printed to the console");

    FILE* fp = fopen(TEXT_FILE, "w");
    if (fp == NULL)
    {
        perror(TEXT_FILE);
        return -1;
    }
    write_report(fp, "saved to the file");
    fclose(fp);
    return 0;
}


/* 10. ПЕРЕИМЕНОВАНИЕ И УДАЛЕНИЕ: rename и remove, при успехе возвращают 0.
 *     Файл перед этим должен быть закрыт. */
static int demo_rename_remove(void)
{
    /* В Windows rename не сработает, если новое имя уже занято. */
    remove(RENAMED_FILE);

    if (rename(TEXT_FILE, RENAMED_FILE) != 0)
    {
        perror("rename");
        return -1;
    }
    if (remove(RENAMED_FILE) != 0)
    {
        perror("remove");
        return -1;
    }
    if (remove(BIN_FILE) != 0)
    {
        perror("remove");
        return -1;
    }
    puts("cleanup: temporary files removed");
    return 0;
}


int main(void)
{
    if (demo_open_close() != 0) return 1;
    if (demo_chars() != 0) return 1;
    if (demo_lines() != 0) return 1;
    if (demo_format() != 0) return 1;
    if (demo_append() != 0) return 1;
    if (demo_blocks() != 0) return 1;
    if (demo_seek() != 0) return 1;
    if (demo_errors() != 0) return 1;
    if (demo_streams() != 0) return 1;
    if (demo_rename_remove() != 0) return 1;
    return 0;
}


/*
 * ЧАСТЫЕ ОШИБКИ
 *
 *     Нет проверки fp после fopen.
 *     char c вместо int c при чтении через getc.
 *     while (!feof(fp)) вместо проверки результата чтения: лишний проход.
 *     fscanf(..., "%20s", ...) для char name[20]: нужно "%19s".
 *     fscanf(...) != EOF вместо сравнения с числом значений.
 *     printf(buffer) вместо printf("%s", buffer).
 *     Файл не закрыт: данные могут остаться в буфере и не попасть в файл.
 *     Режим "w" вместо "a": старое содержимое стёрто.
 *     Текстовый режим для бинарных данных: в Windows \n заменяется на \r\n.
 */
