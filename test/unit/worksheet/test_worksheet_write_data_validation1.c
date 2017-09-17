/*
 * Tests for the lib_xlsx_writer library.
 *
 * Copyright 2014-2017, John McNamara, jmcnamara@cpan.org
 *
 */

#include "../ctest.h"
#include "../helper.h"

#include "xlsxwriter/worksheet.h"


/* 1. Test the _write_data_validations() function. */
CTEST(worksheet, write_data_validations01) {
    char* got;
    char exp[] = "<dataValidations count=\"1\"><dataValidation type=\"whole\" operator=\"greaterThan\" allowBlank=\"1\" showInputMessage=\"1\" showErrorMessage=\"1\" sqref=\"A1\"><formula1>0</formula1></dataValidation></dataValidations>";
    FILE* testfile = lxw_tmpfile(NULL);

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_select(worksheet);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}
