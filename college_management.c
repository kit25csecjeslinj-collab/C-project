#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Structures =====
struct Student {
    int id;
    char name[50];
    char department[30];
    int attendance;
    int marks;
};

struct Staff {
    int id;
    char name[50];
    char designation[30];
};

// ===== Student Functions =====
void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    scanf("%s", s.name);
    printf("Enter Department: ");
    scanf("%s", s.department);
    printf("Enter Attendance Percentage: ");
    scanf("%d", &s.attendance);
    printf("Enter Marks: ");
    scanf("%d", &s.marks);
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Student added successfully!\n");
}

void viewStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        printf("No student records found!\n");
        return;
    }
    printf("\nID\tName\tDept\tAttendance\tMarks\n");
    printf("----------------------------------------------\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%s\t%s\t%d\t\t%d\n", s.id, s.name, s.department, s.attendance, s.marks);
    }
    fclose(fp);
}

void updateStudent() {
    struct Student s;
    int id, found = 0;
    FILE *fp = fopen("students.dat", "rb+");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter New Attendance: ");
            scanf("%d", &s.attendance);
            printf("Enter New Marks: ");
            scanf("%d", &s.marks);
            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    if (found)
        printf("Student record updated!\n");
    else
        printf("Student not found!\n");
}

void deleteStudent() {
    struct Student s;
    int id;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);
    remove("students.dat");
    rename("temp.dat", "students.dat");
    printf("Student record deleted!\n");
}

// ===== Staff Functions =====
void addStaff() {
    struct Staff t;
    FILE *fp = fopen("staff.dat", "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter Staff ID: ");
    scanf("%d", &t.id);
    printf("Enter Staff Name: ");
    scanf("%s", t.name);
    printf("Enter Designation: ");
    scanf("%s", t.designation);
    fwrite(&t, sizeof(t), 1, fp);
    fclose(fp);
    printf("Staff added successfully!\n");
}

void viewStaff() {
    struct Staff t;
    FILE *fp = fopen("staff.dat", "rb");
    if (fp == NULL) {
        printf("No staff records found!\n");
        return;
    }
    printf("\nID\tName\tDesignation\n");
    printf("------------------------------\n");
    while (fread(&t, sizeof(t), 1, fp)) {
        printf("%d\t%s\t%s\n", t.id, t.name, t.designation);
    }
    fclose(fp);
}

// ===== Main Menu =====
int main() {
    int choice;
    do {
        printf("\n==== College Management System ====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Update Student (Attendance & Marks)\n");
        printf("4. Delete Student\n");
        printf("5. Add Staff\n");
        printf("6. View Staff\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: addStaff(); break;
            case 6: viewStaff(); break;
            case 7: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 7);
    return 0;
}
