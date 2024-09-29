#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void preprocessBadCharHeuristic(char* pattern, int m, int badChar[256]) {
    for (int i = 0; i < 256; i++) {
        badChar[i] = -1; 
    }

    // Fill the actual value of last occurrence of a character in the pattern
    for (int i = 0; i < m; i++) {
        badChar[(int) pattern[i]] = i;
    }
}    

int* boyer_moore(char* text, char* pattern) {
  int* result = (int*) malloc(100 * sizeof(int));
    if (result == NULL) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }

    int n = strlen(text);    
    int m = strlen(pattern);
    int badChar[256];
    int count = 0;

    preprocessBadCharHeuristic(pattern, m, badChar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j of pattern while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[s + j]) {
            j--;
        }

        // If the pattern is present at the current shift, add the index to result
        if (j < 0) {
            result[count++] = s; // Store the starting index of the match
            
            // Shift the pattern to align the next character in the text with the last occurrence in the pattern
            s += (s + m < n) ? m - badChar[(int) text[s + m]] : 1;
        } else {
            // Shift the pattern so that the bad character in text aligns with the last occurrence in the pattern
            s += (j - badChar[(int) text[s + j]] > 1) ? j - badChar[(int) text[s + j]] : 1;
        }
    }

    result[count] = -1;
    return result;
}

int main() {
    char pattern[100];
    printf("Enter pattern you are looking for: ");
    scanf("%s", pattern);

    // Check if user is enter an empty pattern
    if (strlen(pattern) == 0) {
        printf("Error: Pattern cannot be empty\n");
        return 1;
    }

    // Open text file
    FILE *textFile = fopen("boyer-moore.txt", "r");
    if (textFile == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    fseek(textFile, 0, SEEK_END);  
    long fileSize = ftell(textFile);  
    fseek(textFile, 0, SEEK_SET); 

    printf("File size: %ld\n", fileSize);

    // Allocate memory for the file content plus terminating null character
    char *text = malloc(fileSize + 1);
    if (text == NULL) {
        printf("Error: Could not allocate memory\n");
        return 1;
    }

    fread(text, 1, fileSize, textFile);
    text[fileSize] = '\0';

    fclose(textFile);

    int* result = boyer_moore(text, pattern);   
    printf("Pattern found at index: ");
    for (int i = 0; i < 100; i++) {
        if (result[i] == -1) {
            break;
        }
        printf("%d ", result[i]);
    }

    free(result);
    free(text);
    return 0;
}