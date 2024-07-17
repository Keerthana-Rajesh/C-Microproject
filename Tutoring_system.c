#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for users, sessions, progress, and assessments
typedef struct {
    int id;
    char name[50];
    char role[10]; // Admin, Tutor, Student
} User;

typedef struct {
    int id;
    int tutor_id;
    int student_id;
    char date[11]; // YYYY-MM-DD
    char time[6]; // HH:MM
    char subject[30];
} Session;

typedef struct {
    int student_id;
    int session_id;
    float progress; // 0.0 - 100.0
} Progress;

typedef struct {
    int student_id;
    int session_id;
    float score; // 0.0 - 100.0
} Assessment;

// Function prototypes
void addUser();
void displayUsers();
void scheduleSession();
void displaySessions();
void updateProgress();
void displayProgress();
void conductAssessment();
void displayAssessments();

// Main function
int main() {
    int choice;
    do {
        printf("\nTutoring System Menu\n");
        printf("1. Add User\n");
        printf("2. Display Users\n");
        printf("3. Schedule Session\n");
        printf("4. Display Sessions\n");
        printf("5. Update Progress\n");
        printf("6. Display Progress\n");
        printf("7. Conduct Assessment\n");
        printf("8. Display Assessments\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addUser();
                break;
            case 2:
                displayUsers();
                break;
            case 3:
                scheduleSession();
                break;
            case 4:
                displaySessions();
                break;
            case 5:
                updateProgress();
                break;
            case 6:
                displayProgress();
                break;
            case 7:
                conductAssessment();
                break;
            case 8:
                displayAssessments();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

// Add User function
void addUser() {
    FILE *fp = fopen("users.dat", "ab");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    User u;
    printf("Enter User ID: ");
    scanf("%d", &u.id);
    printf("Enter Name: ");
    scanf("%s", u.name);
    printf("Enter Role (Admin/Tutor/Student): ");
    scanf("%s", u.role);

    fwrite(&u, sizeof(User), 1, fp);
    fclose(fp);

    printf("User added successfully!\n");
}

// Display Users function
void displayUsers() {
    FILE *fp = fopen("users.dat", "rb");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    User u;
    while (fread(&u, sizeof(User), 1, fp)) {
        printf("ID: %d, Name: %s, Role: %s\n", u.id, u.name, u.role);
    }
    fclose(fp);
}

// Schedule Session function
void scheduleSession() {
    FILE *fp = fopen("sessions.dat", "ab");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    Session s;
    printf("Enter Session ID: ");
    scanf("%d", &s.id);
    printf("Enter Tutor ID: ");
    scanf("%d", &s.tutor_id);
    printf("Enter Student ID: ");
    scanf("%d", &s.student_id);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", s.date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", s.time);
    printf("Enter Subject: ");
    scanf("%s", s.subject);

    fwrite(&s, sizeof(Session), 1, fp);
    fclose(fp);

    printf("Session scheduled successfully!\n");
}

// Display Sessions function
void displaySessions() {
    FILE *fp = fopen("sessions.dat", "rb");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    Session s;
    while (fread(&s, sizeof(Session), 1, fp)) {
        printf("ID: %d, Tutor ID: %d, Student ID: %d, Date: %s, Time: %s, Subject: %s\n", s.id, s.tutor_id, s.student_id, s.date, s.time, s.subject);
    }
    fclose(fp);
}

// Update Progress function
void updateProgress() {
    FILE *fp = fopen("progress.dat", "rb+");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    int student_id, session_id;
    float new_progress;
    printf("Enter Student ID: ");
    scanf("%d", &student_id);
    printf("Enter Session ID: ");
    scanf("%d", &session_id);
    printf("Enter new Progress (0.0 - 100.0): ");
    scanf("%f", &new_progress);

    Progress p;
    int found = 0;

    while (fread(&p, sizeof(Progress), 1, fp)) {
        if (p.student_id == student_id && p.session_id == session_id) {
            p.progress = new_progress;
            fseek(fp, -sizeof(Progress), SEEK_CUR);
            fwrite(&p, sizeof(Progress), 1, fp);
            found = 1;
            printf("Progress updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
    }

    fclose(fp);
}

// Display Progress function
void displayProgress() {
    FILE *fp = fopen("progress.dat", "rb");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    Progress p;
    while (fread(&p, sizeof(Progress), 1, fp)) {
        printf("Student ID: %d, Session ID: %d, Progress: %.2f\n", p.student_id, p.session_id, p.progress);
    }
    fclose(fp);
}

// Conduct Assessment function
void conductAssessment() {
    FILE *fp = fopen("assessments.dat", "ab");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    Assessment a;
    printf("Enter Student ID: ");
    scanf("%d", &a.student_id);
    printf("Enter Session ID: ");
    scanf("%d", &a.session_id);
    printf("Enter Assessment Score: ");
    scanf("%f", &a.score);

    fwrite(&a, sizeof(Assessment), 1, fp);
    fclose(fp);

    printf("Assessment recorded successfully!\n");
}

// Display Assessments function
void displayAssessments() {
    FILE *fp = fopen("assessments.dat", "rb");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    Assessment a;
    while (fread(&a, sizeof(Assessment), 1, fp)) {
        printf("Student ID: %d, Session ID: %d, Score: %.2f\n", a.student_id, a.session_id, a.score);
    }
    fclose(fp);
}

