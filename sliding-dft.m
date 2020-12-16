clc;
clear;

x = [1, -5, 2, 7, 1, 7, 2, 4, 0, 9];
N = 5;

firstFFT = fft(x, N);
fftVectors = [firstFFT];

head = 2;
tail = head + N - 1;

while tail <= length(x)
  vecStart = N * (head - 2) + 1;
  vecEnd = N * (head - 2) + N;
  tempVector = fftVectors(vecStart: vecEnd);
  y = x(head: tail)
  k = [0: N-1];
  newVector = (tempVector(k + 1) - x(head - 1) + y(5)) .* exp(j * 2 * pi * k / N);
  fftVectors = [fftVectors, newVector];
  head += 1;
  tail += 1;
end

fftVectors
