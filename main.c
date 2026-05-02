#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Sensor {
    int id;
    char type[50];
    float value;
    char time[30];
};

// TIME
void getTime(char *buffer) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", tm);
}

// LOWERCASE
void toLower(char *s) {
    for (int i = 0; s[i]; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
}

// STATUS LOGIC
char* getStatus(char type[], float value) {
    char t[50];
    strcpy(t, type);
    toLower(t);

    if (strstr(t, "gas") || strstr(t, "mq2")) {
        if (value <= 40) return "Safe";
        else if (value <= 60) return "Warning";
        else return "Danger";
    }

    if (strstr(t, "temp")) {
        if (value <= 35) return "Normal";
        else if (value <= 45) return "High";
        else return "Critical";
    }

    if (strstr(t, "smoke")) {
        if (value <= 50) return "Normal";
        else if (value <= 70) return "High";
        else return "Critical";
    }

    return "Unknown";
}

// ADD
void addData() {
    FILE *fp = fopen("sensor.dat", "ab");
    struct Sensor s;

    printf("Enter ID: ");
    scanf("%d", &s.id);

    printf("Enter Sensor Name: ");
    scanf(" %[^\n]", s.type);

    printf("Enter Value: ");
    scanf("%f", &s.value);

    getTime(s.time);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Added Successfully!\n");
}

// DISPLAY
void displayData() {
    FILE *fp = fopen("sensor.dat", "rb");
    struct Sensor s;

    printf("\nID     |    Type    |    Value    |   Status    |    Time  \n");
    printf("-------------------------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d | %s | %.2f | %s | %s\n",
               s.id, s.type, s.value,
               getStatus(s.type, s.value),
               s.time);
    }

    fclose(fp);
}

// SEARCH
void searchData() {
    FILE *fp = fopen("sensor.dat", "rb");
    struct Sensor s;
    int id, found = 0;

    printf("Enter ID: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("\nFOUND:\n%s | %.2f | %s | %s\n",
                   s.type, s.value,
                   getStatus(s.type, s.value),
                   s.time);
            found = 1;
        }
    }

    if (!found)
        printf("Not Found!\n");

    fclose(fp);
}

// UPDATE
void updateData() {
    FILE *fp = fopen("sensor.dat", "rb+");
    struct Sensor s;
    int id, found = 0;

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter new value: ");
            scanf("%f", &s.value);

            getTime(s.time);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Updated!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Not Found!\n");

    fclose(fp);
}

// DELETE
void deleteData() {
    FILE *fp = fopen("sensor.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct Sensor s;
    int id;

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != id)
            fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("sensor.dat");
    rename("temp.dat", "sensor.dat");

    printf("Deleted!\n");
}

// ALERT
void showAlert() {
    FILE *fp = fopen("sensor.dat", "rb");
    struct Sensor s;
    int found = 0;

    printf("\n--- ALERT DATA ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        char *status = getStatus(s.type, s.value);

        if (strcmp(status, "Danger") == 0 ||
            strcmp(status, "Critical") == 0) {

            printf("ALERT → %s | %.2f | %s\n",
                   s.type, s.value, status);
            found = 1;
        }
    }

    if (!found)
        printf("No Alerts Found!\n");

    fclose(fp);
}

// SORT (by value)
void sortData() {
    struct Sensor s[100];
    int count = 0;

    FILE *fp = fopen("sensor.dat", "rb");

    while (fread(&s[count], sizeof(struct Sensor), 1, fp))
        count++;

    fclose(fp);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (s[j].value > s[j+1].value) {
                struct Sensor temp = s[j];
                s[j] = s[j+1];
                s[j+1] = temp;
            }
        }
    }

    printf("\n--- SORTED DATA ---\n");

    for (int i = 0; i < count; i++) {
        printf("%d | %s | %.2f | %s\n",
               s[i].id,
               s[i].type,
               s[i].value,
               getStatus(s[i].type, s[i].value));
    }
}

// MAIN
int main() {
    int ch;

    while (1) {
        printf("\n==== SENSOR MANAGEMENT SYSTEM ====\n");
        printf("1. Add Data\n");
        printf("2. Display Data\n");
        printf("3. Search Data\n");
        printf("4. Update Data\n");
        printf("5. Delete Data\n");
        printf("6. Alert Data\n");
        printf("7. Sort Data\n");
        printf("8. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addData(); break;
            case 2: displayData(); break;
            case 3: searchData(); break;
            case 4: updateData(); break;
            case 5: deleteData(); break;
            case 6: showAlert(); break;
            case 7: sortData(); break;
            case 8: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}
