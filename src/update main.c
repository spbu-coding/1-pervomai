#include <stdio.h>
#include <math.h>
#define error(...) (fprintf(stderr, __VA_ARGS__))

size_t size;

struct interval_t {
    double left_b;
    double right_b;
};

double calculate_midpoint_rule (double left_b, double right_b, int amount_squares){
    double sum = 0;
    double change = (right_b - left_b) / amount_squares;
    double left = left_b;
    double right = left + change;
    for (int i=0; i < amount_squares;i++){
        sum += sin((left + right)/2) * (right - left);
        left = right;
        right += change;
    }
    return sum;
}

double calculate_simpson_rule (double left_b, double right_b, int amount_squares){
    double sum = 0;
    double change = (right_b - left_b) / amount_squares;
    double left = left_b;
    double right = left + change;
    for (int i=0; i<amount_squares; i++){
        sum += ((right - left) / 6) * (sin(left) + 4 * sin((left + right) / 2) + sin(right));
        left = right;
        right += change;
    }
    return sum;
}

int reading_intervals(double *left_b, double *right_b){
    printf("Enter left border of interval: ");
    scanf("%lf", left_b);
    if (*left_b < 0){
        error("Value of left border must be larger or equal than 0\n");
        return -1;
    }
    if (*left_b > M_PI){
        error("Value of left border must be less or equal than %f\n",M_PI);
        return -1;
    }

    printf("Enter right border of interval: ");
    scanf("%lf", right_b);
    if (*right_b > M_PI){
        error("Value of right border must be less or equal than %f\n",M_PI);
        return -1;
    }
    if (*right_b < 0){
        error("Value of right border must be larger or equal than 0");
        return -1;
    }

    if (*left_b > *right_b) {
        error("Value of right border must be larger than value of left border\n");
        return -1;
    }
    return 1;
}

int main() {
    struct interval_t interval = {0,0};
    if (reading_intervals(&interval.left_b, &interval.right_b) < 0){
        return 1;
    };

    int amount_squares[] = {5, 10, 20, 100, 500, 1000};
    size = sizeof(amount_squares) / sizeof(amount_squares[0]);
    printf("Results: \n");
    for (int i = 0; i < size; ++i) {
        double sum1 = calculate_midpoint_rule(interval.left_b,interval.right_b,amount_squares[i]);
        double sum2 = calculate_simpson_rule(interval.left_b,interval.right_b,amount_squares[i]);
        printf("%d %.5lf %.5lf\n",amount_squares[i], sum1, sum2);
    }
    return 0;
}
