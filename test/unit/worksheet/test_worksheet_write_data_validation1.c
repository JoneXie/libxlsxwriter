/*
 * Tests for the lib_xlsx_writer library.
 *
 * Copyright 2014-2017, John McNamara, jmcnamara@cpan.org
 *
 */

#include "../ctest.h"
#include "../helper.h"

#include "xlsxwriter/worksheet.h"


//Test the _write_data_validations() function.
CTEST(worksheet, write_data_validations01) {
    char* got;
    char exp[] = "<dataValidations count=\"1\"><dataValidation type=\"whole\" operator=\"greaterThan\" allowBlank=\"1\" showInputMessage=\"1\" showErrorMessage=\"1\" sqref=\"A1\"><formula1>0</formula1></dataValidation></dataValidations>";
    FILE* testfile = lxw_tmpfile(NULL);

    lxw_data_validation data_validation;
    data_validation.validate = 1;
    data_validation.criteria = 1;
    data_validation.value = 0;
    data_validation.ignore_blank = 2;
    data_validation.show_input = 2;
    data_validation.show_error = 2;

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_data_validation_cell(worksheet, 0, 0, &data_validation);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}

CTEST(worksheet, write_data_validations02) {
    char* got;
    char exp[] = "<dataValidations count=\"1\"><dataValidation type=\"whole\" operator=\"greaterThan\" sqref=\"A1\"><formula1>0</formula1></dataValidation></dataValidations>";
    FILE* testfile = lxw_tmpfile(NULL);

    lxw_data_validation data_validation;
    data_validation.validate = 1;
    data_validation.criteria = 1;
    data_validation.value = 0;
    data_validation.ignore_blank = 1;
    data_validation.show_input = 1;
    data_validation.show_error = 1;

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_data_validation_cell(worksheet, 0, 0, &data_validation);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}
