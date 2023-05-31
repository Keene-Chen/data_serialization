#include <stdio.h>
#include <xlsxio_write.h>

int main(void)
{
    // open .xlsx file for writing (will overwrite if it already exists)
    xlsxiowriter handle;
    if ((handle = xlsxiowrite_open("../../res/xlsxio.xlsx", "MySheet1")) == NULL) {
        fprintf(stderr, "Error creating .xlsx file\n");
        return 1;
    }

    // write column names
    xlsxiowrite_add_column(handle, "Col1", 16);
    xlsxiowrite_add_column(handle, "Col2", 0);
    xlsxiowrite_next_row(handle);

    // write data
    int i;
    for (i = 0; i < 10; i++) {
        xlsxiowrite_add_cell_string(handle, "阿萨德");
        xlsxiowrite_add_cell_int(handle, i + 1);
        xlsxiowrite_next_row(handle);
    }

    // close .xlsx file
    xlsxiowrite_close(handle);
    return 0;
}