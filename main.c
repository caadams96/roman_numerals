#include <stdio.h>
#include <string.h>

#define ROMAN_MAP_SIZE 7
#define LONG_TO_SHORT_MAP_SIZE 6

int roman_to_int(char *roman_numeral);
char *int_to_roman(int number);
char *concat(char *destination, char *source, int end);
void subsitute(char *input, char *substr, char *newstr);
int count(const char *string, char *substr);

// "LAZY" LOOKUP TABLES
int ROMAN_MAP_KEY[ROMAN_MAP_SIZE] = {1000, 500, 100, 50, 10, 5, 1};
char *ROMAN_MAP_VALUE[ROMAN_MAP_SIZE] = {"M", "D", "C", "L", "X", "V", "I"};

char *LONG_TO_SHORT_MAP_KEY[LONG_TO_SHORT_MAP_SIZE] = {
    "DCCCC", "CCCC", "LXXXX", "XXXX", "VIIII", "IIII"};
char *LONG_TO_SHORT_MAP_VALUE[LONG_TO_SHORT_MAP_SIZE] = {"CM", "CD", "XC",
                                                         "XL", "IX", "IV"};
/***************************************************/
int main() {
  printf("%s\n", int_to_roman(2844));

  /*
  for (int i = 0; i <= 50; ++i) {
    printf("%s\n", int_to_roman(i));
  }
  */

  static char rn[20] = "MMDCCCXLIV";
  
  printf("%d\n", roman_to_int(rn));
  
  return 0;
}
/***************************************************/
int count(const char *input, char *substr) {

  int count = 0;
  while ((input = strstr(input, substr))) {
    ++count;
    ++input;
  }
  return count;
}
/***************************************************/
int roman_to_int(char *roman_numeral) {
  int amount = 0;
  
  // invert map & search and replace any matching substrings 
  for (int i = 0; i <= LONG_TO_SHORT_MAP_SIZE - 1; ++i) {
    subsitute(roman_numeral, LONG_TO_SHORT_MAP_VALUE[i],
              LONG_TO_SHORT_MAP_KEY[i]);
  }

  for (int i = 0; i <= ROMAN_MAP_SIZE - 1; ++i) {
    amount += count(roman_numeral, ROMAN_MAP_VALUE[i]) * ROMAN_MAP_KEY[i];
  }
  return amount;
}
/***************************************************/

char *int_to_roman(int number_input) {
  static char roman_numeral[20];
  roman_numeral[0] = '\0';

  int difference = 0;
  int amount = 0;

  // build roman numeral string
  for (int i = 0; i <= ROMAN_MAP_SIZE - 1; ++i) {
    difference = number_input - (number_input % ROMAN_MAP_KEY[i]);
    amount = difference / ROMAN_MAP_KEY[i];
    concat(roman_numeral, ROMAN_MAP_VALUE[i], amount);
    number_input -= difference;
  }

  // search and replace any matching substrings
  for (int i = 0; i <= LONG_TO_SHORT_MAP_SIZE - 1; ++i) {
    subsitute(roman_numeral, LONG_TO_SHORT_MAP_KEY[i],
              LONG_TO_SHORT_MAP_VALUE[i]);
  }

  return roman_numeral;
}
/***************************************************/
char *concat(char *destination, char *source, int end) {
  for (int i = 0; i <= end - 1; ++i) {
    strcat(destination, source);
  }
  return destination;
}
/***************************************************/

void subsitute(char *input, char *substr, char *newstr) {
  char temp[1000]; // temporary buffer to hold modified string
  char *p;         // pointer to current position in input string
  int substr_len = strlen(substr); // length of substring to be replaced
  int newstr_len = strlen(newstr); // length of replacement string

  while ((p = strstr(input, substr))) {
    // copy input up to substring
    strncpy(temp, input, p - input);
    temp[p - input] = '\0';

    // add replacement string to temp buffer
    strcat(temp, newstr);

    // add remaining input string to temp buffer
    strcat(temp, p + substr_len);

    // copy temp buffer back to input string
    strcpy(input, temp);
  }
}

