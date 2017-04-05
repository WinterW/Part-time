#ifndef COMM_H
#define COMM_H
const int INPUT_TEXT_WIDTH_BOUND = 5;
const int INPUT_TEXT_HEIGHT_BOUND = 2;
const int BUTTON_MISTAKE_REPAIR_START_MEASURE = 2;
const int BUTTON_ENSURE_INLINE_RANGE_MEASURE = 4;
const int WIDGET_WIDTH_MIN_VALUE = 200;
const int WIDGET_HEIGHT_MIN_VALUE = 100;

const QString GRAPHIC_VERIFICATION = "div input#authCodeInput._text";
const QString VERIFICATION_CODE = "div input#CheckCode._text";
const QString PHONE_NUM = "div input#msisdn._text";
const QString CONFIRM_BUTTON = "div input#authCodeSwitch._button";
const QString GET_VERIFY_CODE_BUTTON = "div input#sendSMS._button";
const QString COMMIT_BUTTON = "div.btn a.c";
const QString CONFIRM_PAY_BUTTON = "div#payDetail.payDetail.onkey a";
const QString CONFIRM_PAY_SUCCESS_BUTTON = "div.buy_success p.p2 a";

enum EnUrlLoadStatus{
    START_URL_LOAD_SUCCESSED,
    START_URL_LOAD_FAILED,
    DEST_URL_LOAD_SUCCESSED,
    DEST_URL_LOAD_FAILED
};
#endif // COMM_H
