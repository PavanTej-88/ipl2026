#include <stdio.h>

union decision {
    unsigned char flags;
    struct field {
        int yc:1;
        int mc:1;
        int fc:1;
        int sa:1;
        int fv:1;
        int apt:1;
        int lk:1;
        int dec:1;
    } f;
};

union decision input() {
    union decision d;
    d.flags = 0;
    printf("Your choice (0/1): "); scanf("%d", &d.f.yc);
    printf("Mom's choice (0/1): "); scanf("%d", &d.f.mc);
    printf("Dad's choice (0/1): "); scanf("%d", &d.f.fc);
    printf("Socially ok (0/1): "); scanf("%d", &d.f.sa);
    printf("Financially ok (0/1): "); scanf("%d", &d.f.fv);
    printf("Got aptitude (0/1): "); scanf("%d", &d.f.apt);
    printf("You like it (0/1): "); scanf("%d", &d.f.lk);
    return d;
}

void make_decision(union decision *d) {
    d->f.dec = (d->f.yc && d->f.mc && d->f.fc && d->f.sa && d->f.fv && d->f.apt && d->f.lk) ? 1 : 0;
}

void print_decsion(union decision d) {
    printf("\n--- Your Decision Report ---\n");
    printf("You want it     : %s\n", &d.f.yc ? "Yes" : "No");
    printf("Mom approves    : %s\n", &d.f.mc ? "Yes" : "No");
    printf("Dad approves    : %s\n", &d.f.fc ? "Yes" : "No");
    printf("Society ok      : %s\n", &d.f.sa ? "Yes" : "No");
    printf("Money ok        : %s\n", &d.f.fv ? "Yes" : "No");
    printf("Have aptitude   : %s\n", &d.f.apt ? "Yes" : "No");
    printf("You like it     : %s\n", &d.f.lk ? "Yes" : "No");
    printf("Final decision  : %s\n", &d.f.dec ? "GO FOR IT!" : "Maybe not.");
}

void print_conclusion_based_on_flags(union decision d) {
    int n = d.flags;
    printf("\nFlags value: %d\n", n);
    if (n == 255)
        printf("Perfect score - everything lines up!\n");
    else if (n >= 128)
        printf("More than half the factors are in your favor.\n");
    else if (n >= 64)
        printf("A few things check out, but think more.\n");
    else
        printf("Too many things are against it right now.\n");
}

int main() {
    union decision d = input();
    make_decision(&d);
    print_decsion(d);
    print_conclusion_based_on_flags(d);
    return 0;
}