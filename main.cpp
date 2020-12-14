#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#define N 10

struct ComplexNumber {
  float real, imag;
};

ComplexNumber calculateFreq(float x, int n, int k);
void printOutput(std::vector<float> realN, std::vector<float> imagN);

int main() {
  int n, k;
  const std::vector<float> x = {1, -5, 2, 7, 1, 7, 2, 4, 0, 9};
  std::vector<float> realN(N, 0), imagN(N, 0);

  for (k = 0; k < x.size(); k++) {
    realN[k] = 0;
    imagN[k] = 0;
    for (n = 0; n < N; n++) {
      const auto val = calculateFreq(x[n], n, k);
      realN[k] += val.real;
      imagN[k] += val.imag;
    }
  }

  printOutput(realN, imagN);
}

ComplexNumber calculateFreq(float x, int n, int k) {
  ComplexNumber temp;

  temp.real = x * cos(n * k * 2 * M_PI / N);
  temp.imag = x * sin(n * k * 2 * M_PI / N);

  return temp;
}

void printOutput(std::vector<float> realN, std::vector<float> imagN) {
  for (int n = 0; n < realN.size(); n++)
    std::cout << "(" << realN[n] << ", " << imagN[n] << "j"
              << ")"
              << "\n";
}