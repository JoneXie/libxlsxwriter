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

    lxw_data_validation *data_validation = calloc(1, sizeof(lxw_data_validation));
    data_validation->validate = LXW_VALIDATION_TYPE_INTEGER;
    data_validation->criteria = LXW_VALIDATION_CRITERIA_GREATER_THAN;
    data_validation->value_number = 0;

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_data_validation_cell(worksheet, 0, 0, data_validation);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}

CTEST(worksheet, write_data_validations01a) {
    char* got;
    char exp[] = "<dataValidations count=\"1\"><dataValidation type=\"whole\" operator=\"greaterThan\" allowBlank=\"1\" showInputMessage=\"1\" showErrorMessage=\"1\" sqref=\"A1\"><formula1>0</formula1></dataValidation></dataValidations>";
    FILE* testfile = lxw_tmpfile(NULL);

    lxw_data_validation *data_validation = calloc(1, sizeof(lxw_data_validation));
    data_validation->validate = LXW_VALIDATION_TYPE_INTEGER;
    data_validation->criteria = LXW_VALIDATION_CRITERIA_GREATER_THAN;
    data_validation->value_number = 0;
    data_validation->ignore_blank = LXW_VALIDATION_ON;
    data_validation->show_input = LXW_VALIDATION_ON;
    data_validation->show_error = LXW_VALIDATION_ON;

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_data_validation_cell(worksheet, 0, 0, data_validation);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}

CTEST(worksheet, write_data_validations01b) {
    char* got;
    char exp[] = "<dataValidations count=\"1\"><dataValidation type=\"whole\" operator=\"greaterThan\" sqref=\"A1\"><formula1>0</formula1></dataValidation></dataValidations>";
    FILE* testfile = lxw_tmpfile(NULL);

    lxw_data_validation *data_validation = calloc(1, sizeof(lxw_data_validation));
    data_validation->validate = LXW_VALIDATION_TYPE_INTEGER;
    data_validation->criteria = LXW_VALIDATION_CRITERIA_GREATER_THAN;
    data_validation->value_number = 0;
    data_validation->ignore_blank = LXW_VALIDATION_OFF;
    data_validation->show_input = LXW_VALIDATION_OFF;
    data_validation->show_error = LXW_VALIDATION_OFF;

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_data_validation_cell(worksheet, 0, 0, data_validation);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}

CTEST(worksheet, write_data_validations02) {
    char* got;
    char exp[] = "<dataValidations count=\"1\"><dataValidation type=\"whole\" operator=\"greaterThan\" allowBlank=\"1\" showInputMessage=\"1\" showErrorMessage=\"1\" sqref=\"A2\"><formula1>E3</formula1></dataValidation></dataValidations>";
    FILE* testfile = lxw_tmpfile(NULL);

    lxw_data_validation *data_validation = calloc(1, sizeof(lxw_data_validation));
    data_validation->validate = LXW_VALIDATION_TYPE_INTEGER_FORMULA;
    data_validation->criteria = LXW_VALIDATION_CRITERIA_GREATER_THAN;
    data_validation->value_formula = "=E3";

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_data_validation_cell(worksheet, CELL("A2"), data_validation);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}

CTEST(worksheet, write_data_validations03) {
    char* got;
    char exp[] = "<dataValidations count=\"1\"><dataValidation type=\"decimal\" allowBlank=\"1\" showInputMessage=\"1\" showErrorMessage=\"1\" sqref=\"A3\"><formula1>0.1</formula1><formula2>0.5</formula2></dataValidation></dataValidations>";
    FILE* testfile = lxw_tmpfile(NULL);

    lxw_data_validation *data_validation = calloc(1, sizeof(lxw_data_validation));
    data_validation->validate = LXW_VALIDATION_TYPE_DECIMAL;
    data_validation->criteria = LXW_VALIDATION_CRITERIA_BETWEEN;
    data_validation->value_number = 0.1;
    data_validation->maximum_number = 0.5;

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;

    worksheet_data_validation_cell(worksheet, CELL("A3"), data_validation);
    _worksheet_write_data_validations(worksheet);

    RUN_XLSX_STREQ(exp, got);

    lxw_worksheet_free(worksheet);
}


