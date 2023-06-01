#include "libxl/libxl.h"
#include <stdio.h>

int main()
{
    BookHandle book = xlCreateXMLBook();
    if (book) {
        SheetHandle sheet = xlBookAddSheet(book, "Sheet1", 0);
        if (sheet) {
            FormatHandle dateFormat;

            xlSheetWriteStr(sheet, 2, 1, "Hello, World !", 0);
            xlSheetWriteNum(sheet, 3, 1, 1000, 0);

            dateFormat = xlBookAddFormat(book, 0);
            xlFormatSetNumFormat(dateFormat, NUMFORMAT_DATE);
            xlSheetWriteNum(sheet, 4, 1, xlBookDatePack(book, 2008, 4, 29, 0, 0, 0, 0), dateFormat);

            xlSheetSetCol(sheet, 1, 1, 12, 0, 0);
        }

        if (xlBookSave(book, "/home/keenechen/Code_Test/data_serialization/res/example.xlsx"))
            printf("File example.xls has been created.\n");
        xlBookRelease(book);
    }

    return 0;
}
