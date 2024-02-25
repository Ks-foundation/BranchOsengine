#include <stdio.h>
#include <math.h>

double d1(double S, double K, double r, double T, double sigma) {
    return (log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * sqrt(T));
}

double d2(double S, double K, double r, double T, double sigma) {
    return d1(S, K, r, T, sigma) - sigma * sqrt(T);
}

double black_scholes_call(double S, double K, double r, double T, double sigma) {
    double d1_value = d1(S, K, r, T, sigma);
    double d2_value = d2(S, K, r, T, sigma);
    return S * cdf(d1_value) - K * exp(-r * T) * cdf(d2_value);
}

double black_scholes_put(double S, double K, double r, double T, double sigma) {
    double d1_value = d1(S, K, r, T, sigma);
    double d2_value = d2(S, K, r, T, sigma);
    return K * exp(-r * T) * cdf(-d2_value) - S * cdf(-d1_value);
}

int main() {
    double S = 100;    // 주가
    double K = 100;    // 행사가
    double r = 0.05;   // 이자율
    double T = 1;      // 만기
    double sigma = 0.2;// 변동성

    printf("Call Option Price: %.2f\n", black_scholes_call(S, K, r, T, sigma));
    printf("Put Option Price: %.2f\n", black_scholes_put(S, K, r, T, sigma));

    return 0;
}
