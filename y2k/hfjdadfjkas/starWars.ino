#define  c3    7634
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049
#define  c4    3816    // 261 Hz 
#define  d4    3401    // 294 Hz 
#define  e4    3030    // 329 Hz 
#define  f4    2865    // 349 Hz 
#define  g4    2551    // 392 Hz 
#define  a4    2272    // 440 Hz 
#define  a4s   2146
#define  b4    2028    // 493 Hz 
#define  c5    1912    // 523 Hz
#define  d5    1706
#define  d5s   1608
#define  e5    1517    // 659 Hz
#define  f5    1433    // 698 Hz
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955

#define  R     0      // Define a special note, 'R', to represent a rest

int melody1[] = {  a4, R,  a4, R,  a4, R,  f4, R, c5, R,  a4, R,  f4, R, c5, R, a4, R,  e5, R,  e5, R,  e5, R,  f5, R, c5, R,  g5, R,  f5, R,  c5, R, a4, R};
int beats1[]  = {  50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5, 20, 5, 60, 80, 50, 20, 50, 20, 50, 20, 40, 5, 20, 5,  60, 10, 40, 5,  20, 5, 60, 40};

int MAX_COUNT = sizeof(melody1) / 2; // Melody length, for looping.

long tempo = 10000; // Set overall tempo
 
int pause = 1000; // Set length of pause between notes
 
int rest_count = 50; // Loop variable to increase Rest length (BLETCHEROUS HACK; See NOTES)

// Initialize core variables
int toneM = 0;
int beat = 0;
long duration  = 0;
int potVal = 0;

  void playMusic() {
    for (int i=0; i<MAX_COUNT; i++) {
    toneM = melody1[i];
    beat = beats1[i];
 
    duration = beat * tempo; // Set up timing
 
    playTone(); // A pause between notes
    delayMicroseconds(pause);
    }
  
 
for (int i=0; i<MAX_COUNT; i++) {
    

 
    duration = beat * tempo; // Set up timing
 
    playTone(); // A pause between notes
    delayMicroseconds(pause);
    }
  } 

void playTone() {
  long elapsed_time = 0;
  if (toneM > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {
 
      digitalWrite(6,HIGH);
      delayMicroseconds(toneM / 2);
 
      // DOWN
      digitalWrite(6, LOW);
      delayMicroseconds(toneM / 2);
 
      // Keep track of how long we pulsed
      elapsed_time += (toneM);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    } 
                                   
 }   
  


void silly() {
  digitalWrite(6, LOW);
  delay(100);
  digitalWrite(6, HIGH);
  delay(100);
}


