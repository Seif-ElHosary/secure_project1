/*
 * sonar_test.c
 * Intentionally flawed code for testing SonarCloud.
 * Every function contains ONE deliberate issue, labeled in a comment.
 * DO NOT use this code in a real project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- VULNERABILITIES ---------- */

/* 1. Hardcoded credentials (security hotspot / vulnerability) */
const char *PASSWORD = "admin123";

/* 2. Buffer overflow: strcpy into a small buffer with no size check */
void copy_name(const char *input) {
    char buffer[8];
    strcpy(buffer, input);
    printf("Name: %s\n", buffer);
}

/* 3. Format string vulnerability: user input used as the format */
void print_message(const char *user_input) {
    printf(user_input);
}

/* 4. Command injection: user input passed straight to system() */
void ping_host(const char *host) {
    char cmd[100];
    sprintf(cmd, "ping -c 1 %s", host);
    system(cmd);
}

/* 5. Unbounded scanf into a fixed buffer */
void read_username(void) {
    char name[10];
    printf("Enter username: ");
    scanf("%s", name);
    printf("Hello %s\n", name);
}

/* ---------- BUGS ---------- */

/* 6. Memory leak: malloc without free */
void memory_leak(void) {
    int *numbers = malloc(10 * sizeof(int));
    numbers[0] = 42;
    printf("%d\n", numbers[0]);
}

/* 7. Null pointer dereference */
void null_pointer(void) {
    char *text = NULL;
    printf("%c\n", text[0]);
}

/* 8. Use after free */
void use_after_free(void) {
    int *value = malloc(sizeof(int));
    *value = 10;
    free(value);
    printf("%d\n", *value);
}

/* 9. Double free */
void double_free(void) {
    char *data = malloc(20);
    free(data);
    free(data);
}

/* 10. Off-by-one: loop goes one element past the end of the array */
void off_by_one(void) {
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i <= 5; i++) {
        printf("%d\n", arr[i]);
    }
}

/* 11. Uninitialized variable */
int uninitialized(void) {
    int result;
    return result + 1;
}

/* 12. Division by zero */
int divide_by_zero(void) {
    int a = 10;
    int b = 0;
    return a / b;
}

/* 13. fopen result not checked (possible NULL dereference) */
void write_file(void) {
    FILE *f = fopen("/tmp/output.txt", "w");
    fprintf(f, "hello\n");
    fclose(f);
}

/* ---------- CODE SMELLS ---------- */

/* 14. Identical branches in if/else */
int same_branches(int x) {
    if (x > 0) {
        return 1;
    } else {
        return 1;
    }
}

/* 15. Unused variable and dead code after return */
int dead_code(void) {
    int unused = 99;
    return 0;
    printf("This never runs\n");
}

/* 16. Magic numbers + overly nested logic */
int nested(int a, int b, int c) {
    if (a > 0) {
        if (b > 0) {
            if (c > 0) {
                if (a + b + c > 1000) {
                    return 7;
                }
            }
        }
    }
    return 0;
}

int main(void) {
    copy_name("ThisNameIsWayTooLong");
    memory_leak();
    use_after_free();
    return 0;
}
