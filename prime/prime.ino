const bool delayEnabled = false;
const bool debugEnabled = true;
const int cacheSize = 256;
long cache[cacheSize];
long primesFound = 0;

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

  for (int i=2; i<p/2; i++) {
    if (p % i == 0) {
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
  Serial.print(" in ");
  Serial.print(micros()/1000 - startTimeMs);
  Serial.println("ms");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Prime numbers:");
}

void loop() {
  long n = 1;
  const long startTimeMs = micros() / 1000;

  for (; n<12; n++) { 
    if (isPrime(n)) {
      ++primesFound;
      if (debugEnabled) {
        printResult(n, startTimeMs);
      }
    }
    if (delayEnabled) {
      delay(1000);
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
    
    if (delayEnabled) {
      delay(1000);
    }
  }
}
