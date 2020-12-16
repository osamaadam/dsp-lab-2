#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

#define WINDOW 5

struct ComplexNumber {
  float real, imag;
};

struct ComplexNumbers {
  ComplexNumbers() {
  }
  ComplexNumbers(std::vector<float> realIn, std::vector<float> imagIn) {
    real = realIn;
    imag = imagIn;
  }
  void appendPoint(float realIn, float imagIn) {
    real.push_back(realIn);
    imag.push_back(imagIn);
  }
  void appendPoint(ComplexNumber complexNumber) {
    real.push_back(complexNumber.real);
    imag.push_back(complexNumber.imag);
  }
  std::vector<float> real, imag;
};

ComplexNumber calculateFreq(float x, int n, int k, int N);
ComplexNumbers computeFFT(std::vector<float> x);
ComplexNumber freqShift(
  std::vector<float> orgX, std::vector<float> x, ComplexNumbers X, int k, int head);
void printOutput(std::vector<float> realN, std::vector<float> imagN);

int main() {
  const std::vector<float> x = {1, -5, 2, 7, 1, 7, 2, 4, 0, 9};
  ComplexNumbers output;

  int head = 0;
  int tail = WINDOW;
  std::vector<float> tempx(x.begin() + head, x.begin() + tail);
  const auto computedFFT = computeFFT(tempx);
  for (int i = 0; i < WINDOW; i++) {
    output.appendPoint(computedFFT.real[i], computedFFT.imag[i]);
  }
  head++;
  tail++;

  while (tail <= x.size()) {
    std::vector<float> tempx(x.begin() + head, x.begin() + tail);

    for (int k = 0; k < WINDOW; k++) {
      const auto tempX = freqShift(x, tempx, output, k, head);
      output.appendPoint(tempX);
    }
    head++;
    tail++;
  }

  printOutput(output.real, output.imag);
}

ComplexNumber freqShift(
  std::vector<float> orgX, std::vector<float> x, ComplexNumbers X, int k, int head) {
  ComplexNumber temp;
  const float SHIFT = 2 * M_PI * k / WINDOW;
  const int vecStart = WINDOW * (head - 1);
  const int vecEnd = vecStart + WINDOW - 1;
  const std::vector<float> realVec(X.real.begin() + vecStart, X.real.begin() + vecEnd);
  const std::vector<float> imagVec(X.imag.begin() + vecStart, X.imag.begin() + vecEnd);

  temp.real =
    ((realVec[k] + x[WINDOW - 1] - orgX[head - 1]) * cos(SHIFT)) - (imagVec[k] * sin(SHIFT));
  temp.imag =
    ((realVec[k] + x[WINDOW - 1] - orgX[head - 1]) * sin(SHIFT)) + (imagVec[k] * cos(SHIFT));

  return temp;
}

ComplexNumbers computeFFT(std::vector<float> x) {
  const int N = x.size();

  int n, k;
  std::vector<float> realN(N, 0), imagN(N, 0);

  for (k = 0; k < x.size(); k++) {
    realN[k] = 0;
    imagN[k] = 0;
    for (n = 0; n < N; n++) {
      const auto val = calculateFreq(x[n], n, k, N);
      realN[k] += val.real;
      imagN[k] += val.imag;
    }
  }

  const ComplexNumbers temp(realN, imagN);
  return temp;
}

ComplexNumber calculateFreq(float x, int n, int k, int N) {
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