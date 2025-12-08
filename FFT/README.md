FFT!

frequency_spectrum에서 real_part는 그 주파수의 코사인파가 얼만큼인지, imaginary_part는 그 주파수의 사인파가 얼만큼인지를 나타낸다.
그러므로 그 둘을 하나로 나타냈을 때 주파수의 크기는 magnitude일 것이고 argument 즉, 파동이 얼마나 밀려있는 가도 알 수 있다.

정리하면, FFT는 하나의 신호를 구성하는 파동의 모든 정보를 담고 있다.

1. f축은 각 frequency를.
2. real, imaginary는 그 구성하는 파동의 magnitude를 (같은 주파수 cos, sin을 합성한 파동의 magnitude)
3. argument는 2번의 합성파의 위상을 알려준다.
4. 결국 1~3의 파동의 총합이 우리가 analyze하는 signal이 되는 것이다.

좋은 유튜브 비디오를 찾았다. Matlab에서 제공하는 FFT 비디오를 참고할 것!
