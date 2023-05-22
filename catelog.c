#include <stdio.h>

#define PRODUCT_COUNT 3
#define SHIPPING_RATE 5
#define GIFT_WRAP_FEE 1

struct Product {
    char name;
    int price;
    int quantity;
    int isGiftWrapped;
};

struct Discount {
    char name[20];
    float discountPercentage;
    int isApplicable;
};

void applyDiscount(struct Product *products, struct Discount *discount, int cartTotal) {
    int i;
    float maxDiscount = 0;
    int index = -1;

    for (i = 0; i < PRODUCT_COUNT; i++) {
        if (discount[i].isApplicable) {
            float discountAmount = products[i].price * products[i].quantity * discount[i].discountPercentage;
            if (discountAmount > maxDiscount) {
                maxDiscount = discountAmount;
                index = i;
            }
        }
    }

    if (index != -1) {
        printf("Discount Applied: %s\n", discount[index].name);
        printf("Discount Amount: $%.2f\n", maxDiscount);
        cartTotal -= maxDiscount;
    }
}

int main() {
    struct Product products[PRODUCT_COUNT];
    struct Discount discounts[PRODUCT_COUNT] = {
        {"flat_10_discount", 0.10, 0},
        {"bulk_5_discount", 0.05, 0},
        {"bulk_10_discount", 0.10, 0}
    };

    int i, cartTotal = 0;

    // Input product details
    for (i = 0; i < PRODUCT_COUNT; i++) {
        printf("Enter quantity for product %c: ", 'A' + i);
        scanf("%d", &products[i].quantity);
        printf("Is product %c gift wrapped? (1 for yes, 0 for no): ", 'A' + i);
        scanf("%d", &products[i].isGiftWrapped);

        switch (i) {
            case 0:
                products[i].name = 'A';
                products[i].price = 20;
                break;
            case 1:
                products[i].name = 'B';
                products[i].price = 40;
                break;
            case 2:
                products[i].name = 'C';
                products[i].price = 50;
                break;
        }

        cartTotal += products[i].price * products[i].quantity;
    }

    //discount
    if (cartTotal > 200) {
        discounts[0].isApplicable = 1;
    }

    for (i = 0; i < PRODUCT_COUNT; i++) {
        if (products[i].quantity > 10) {
            discounts[1].isApplicable = 1;
            break;
        }
    }

    int totalQuantity = 0;
    for (i = 0; i < PRODUCT_COUNT; i++) {
        totalQuantity += products[i].quantity;
    }

    if (totalQuantity > 20) {
        discounts[2].isApplicable = 1;
    }

    if (totalQuantity > 30) {
        for (i = 0; i < PRODUCT_COUNT; i++) {
            if (products[i].quantity > 15) {
                discounts[i].isApplicable = 1;
            }
        }
    }

    //giving discount
    applyDiscount(products, discounts, cartTotal);

    // Calculate shipping fee and gift wrap fee
    int totalUnits = 0;
    int shippingPackages = 0;
    int giftWrapFee = 0;

    for (i = 0; i < PRODUCT_COUNT; i++) {
        totalUnits += products[i].quantity;

        if (products[i].isGiftWrapped) {
            giftWrapFee += products[i].quantity;
        }
    }

    shippingPackages = totalUnits / 10;
    if (totalUnits % 10 != 0) {
        shippingPackages++;
    }

    int shippingFee = shippingPackages * SHIPPING_RATE;

    //subtotal
    int subTotal = cartTotal + shippingFee + giftWrapFee;

    //total
    int total = subTotal;

    printf("\n--- Order Summary ---\n");

    for (i = 0; i < PRODUCT_COUNT; i++) {
        printf("Product: %c\n", products[i].name);
        printf("Quantity: %d\n", products[i].quantity);
        printf("Total Amount: $%d\n", products[i].price * products[i].quantity);
    }

    printf("Subtotal: $%d\n", subTotal);
    printf("Shipping Fee: $%d\n", shippingFee);
    printf("Gift Wrap Fee: $%d\n", giftWrapFee);
    printf("Total: $%d\n", total);

    return 0;
}
