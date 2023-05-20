#include <stdio.h>
#define PRODUCT_A_PRICE 20
#define PRODUCT_B_PRICE 40
#define PRODUCT_C_PRICE 50
#define GIFT_WRAP_FEE 1
#define SHIPPING_PACKAGE_SIZE 10
#define SHIPPING_FEE 5
int main() {
    int productAQuantity, productBQuantity, productCQuantity;
    int productAGiftWrap, productBGiftWrap, productCGiftWrap;
    int totalQuantity, subtotal, shippingFee, giftWrapFee, totalAmount;
    int discountAmount = 0;
    char discountName[30];

// Input product quantities and gift wrap options
    printf("Enter the quantity of Product A: ");
    scanf("%d", &productAQuantity);
    printf("Is Product A wrapped as a gift? (0 for no, 1 for yes): ");
    scanf("%d", &productAGiftWrap);

    printf("Enter the quantity of Product B: ");
    scanf("%d", &productBQuantity);
    printf("Is Product B wrapped as a gift? (0 for no, 1 for yes): ");
    scanf("%d", &productBGiftWrap);

    printf("Enter the quantity of Product C: ");
    scanf("%d", &productCQuantity);
    printf("Is Product C wrapped as a gift? (0 for no, 1 for yes): ");
    scanf("%d", &productCGiftWrap);

// Calculate total quantity and subtotal
    totalQuantity = productAQuantity + productBQuantity + productCQuantity;
    subtotal = (productAQuantity * PRODUCT_A_PRICE) + (productBQuantity * PRODUCT_B_PRICE) + (productCQuantity * PRODUCT_C_PRICE);

 // Apply discount rules
    if (subtotal > 200) {
        discountAmount = 10;
        strcpy(discountName, "flat_10_discount");
    } else if (productAQuantity > 10 || productBQuantity > 10 || productCQuantity > 10) {
        int maxQuantity = productAQuantity;
        if (productBQuantity > maxQuantity)
            maxQuantity = productBQuantity;
        if (productCQuantity > maxQuantity)
            maxQuantity = productCQuantity;

        discountAmount = (maxQuantity * PRODUCT_A_PRICE + maxQuantity * PRODUCT_B_PRICE + maxQuantity * PRODUCT_C_PRICE) * 0.05;
        strcpy(discountName, "bulk_5_discount");
    } else if (totalQuantity > 20) {
        discountAmount = subtotal * 0.1;
        strcpy(discountName, "bulk_10_discount");
    } else if (totalQuantity > 30 && (productAQuantity > 15 || productBQuantity > 15 || productCQuantity > 15)) {
        int excessQuantity = (productAQuantity > 15 ? productAQuantity - 15 : 0) +
                            (productBQuantity > 15 ? productBQuantity - 15 : 0) +
                            (productCQuantity > 15 ? productCQuantity - 15 : 0);

        discountAmount = (excessQuantity * PRODUCT_A_PRICE + excessQuantity * PRODUCT_B_PRICE + excessQuantity * PRODUCT_C_PRICE) * 0.5;
        strcpy(discountName, "tiered_50_discount");
    }

 // Calculate shipping fee and gift wrap fee
    shippingFee = (totalQuantity / SHIPPING_PACKAGE_SIZE) * SHIPPING_FEE;
    giftWrapFee = (productAGiftWrap * productAQuantity + productBGiftWrap * productBQuantity + productCGiftWrap * productCQuantity) * GIFT_WRAP_FEE
