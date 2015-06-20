const bool debugEnabled = true;
const int cacheSize = 600;
int cache[cacheSize];
int primesFound = 0;

int cacheUsedSuccessfulCount = 0;
int cacheUsedUnsuccessfulCount = 0;

bool isPrime(int p) {
  if (p<2) {
    return false;
  }

  for (int k=0; k<primesFound && k<cacheSize; k++) {
    // Can p be divided by any of the already known prime numbers?
    if (p % cache[k] == 0) {
      cacheUsedSuccessfulCount++;
      return false;
    }
  }

  cacheUsedUnsuccessfulCount++;

  const int upTo = (int) sqrt(p);

  for (int i=2; i<upTo; i+=4) {
    if (p % i == 0 || p % (i+1) == 0 || p % (i+2) == 0 || p % (i+3) == 0) {
      return false;
    }
  }

  if (primesFound < cacheSize) {
    cache[primesFound++] = p;
  }
  return true;
}

void printResult(int n, long startTimeMs) {
  Serial.print(primesFound);
  Serial.print(" -> ");
  Serial.print(n);
  Serial.print(" [time: ");
  Serial.print(micros()/1000 - startTimeMs);
  Serial.print("ms, cache use: ");
  Serial.print(cacheUsedSuccessfulCount);
  Serial.print(":");
  Serial.print(cacheUsedUnsuccessfulCount);
  Serial.println("]");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Prime numbers:");
}

void loop() {
  int n = 1;
  const long startTimeMs = micros() / 1000;

  for (; n<12; n++) { 
    if (isPrime(n)) {
      ++primesFound;
      if (debugEnabled) {
        printResult(n, startTimeMs);
      }
    }
  }

  // n > 11
  for (; true; n++) { 
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0 || n % 11 == 0) {
      continue;
    }
  
    if (isPrime(n)) {
      ++primesFound;
      if (debugEnabled && primesFound % 200 == 0) {
        printResult(n, startTimeMs);
      }
    }
  }
}
