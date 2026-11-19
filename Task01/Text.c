#include <stdio.h>
#include <ctype.h>
#include <string.h>

int word_count_manual(const char s[]) {
    int count = 0, inside = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (isspace((unsigned char)s[i])) inside = 0;
        else if (!inside) { count++; inside = 1; }
    }
    return count;
}

void uppercase_manual(char s[]) {
    for (int i = 0; s[i] != '\0'; i++)
        s[i] = (char)toupper((unsigned char)s[i]);
}

void reverse_manual(char s[]) {
    size_t left = 0, right = 0;
    while (s[right] != '\0') right++;
    if (right == 0) return;
    right--;
    while (left < right) {
        char t = s[left]; s[left] = s[right]; s[right] = t;
        left++; right--;
    }
}

int palindrome_manual(const char s[]) {
    int left = 0, right = 0;
    while (s[right] != '\0') right++;
    right--;
    while (left < right) {
        while (left < right && !isalpha((unsigned char)s[left])) left++;
        while (left < right && !isalpha((unsigned char)s[right])) right--;
        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right]))
            return 0;
        left++; right--;
    }
    return 1;
}

/* Library-based versions */
int word_count_library(const char s[]) {
    int count = 0, inside = 0;
    for (size_t i = 0; i < strlen(s); i++) { /* illustrative; manual scan is faster */
        if (isspace((unsigned char)s[i])) inside = 0;
        else if (!inside) { count++; inside = 1; }
    }
    return count;
}

int main(void) {
    const char message[] = " Meet at the library at 5 PM ";
    char text[] = "college feedback";
    char reverse_text[] = "college feedback";
    char safe_copy[12];
    const char tab_message[] = "One\tTwo   Three";

    printf("Words: %d\n", word_count_manual(message));
    printf("%d %d\n", palindrome_manual("Madam, I'm Adam"),
           palindrome_manual("Hello"));
    printf("Tab-separated message word count: %d\n", word_count_manual(tab_message));

    uppercase_manual(text);
    printf("Uppercase: %s\n", text);
    reverse_manual(reverse_text);
    printf("Reversed: %s\n", reverse_text);

    printf("Library word count: %d\n", word_count_library(message));
    /* snprintf limits the number of bytes written, including the null terminator. */
    snprintf(safe_copy, sizeof safe_copy, "%s", "A very long feedback message");
    printf("Safe truncated copy: %s\n", safe_copy);
    return 0;
}
