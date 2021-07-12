#ifndef UNTITLED3_PAYMENTMETHODS_H
#define UNTITLED3_PAYMENTMETHODS_H

using namespace std;

enum PaymentMethod {
    CASH, CARD, ONLINE_WALLET, BANK_TRANSFER, PROMO_CODE,
};

void printPaymentMethod(PaymentMethod paymentMethod) {
    switch (paymentMethod) {
        case CASH:
            cout << "cash";
            break;
        case CARD:
            cout << "bank сard";
            break;
        case ONLINE_WALLET:
            cout << "online wallet";
            break;
        case BANK_TRANSFER:
            cout << "bank transfer";
            break;
        case PROMO_CODE:
            cout << "promo code";
            break;
    }
}

#endif
