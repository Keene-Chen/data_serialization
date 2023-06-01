#include "libxl/libxl.h"
#include <stdio.h>

int main()
{
    BookHandle book = xlCreateXMLBook();
    if (book) {
        if (xlBookLoad(book, "/home/keenechen/Code_Test/data_serialization/res/example.xlsx")) {
            SheetHandle sheet = xlBookGetSheet(book, 0);
            if (sheet) {
                double d = xlSheetReadNum(sheet, 3, 1, 0);
                printf("Cell D4 is %.2f\n", d);
                xlSheetWriteNum(sheet, 3, 1, d + 2, 0);
                xlSheetWriteStr(sheet, 4, 1, "new string", 0);
            }

            if (xlBookSave(book, "/home/keenechen/Code_Test/data_serialization/res/example.xlsx"))
                printf("File example.xls has been modified.\n");
        }

        xlBookRelease(book);
    }

    return 0;
}
