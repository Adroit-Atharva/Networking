#include <stdio.h>
#include <string.h>
#define MAX 1024

int main() {
    int systemid, choice = 0;
    char message[MAX];
    char lines[MAX];
    FILE *fp;

    while (1) {
        printf("\nSelect Service :\n1) Send Message\n2) View Message\n3) Exit\n> ");
        scanf("%d", &choice);
        getchar(); // Consume leftover newline

        if (choice == 1) {
            // Reset buffers
            memset(lines, 0, sizeof(lines));

            printf("Whom to send: ");
            scanf("%d", &systemid);
            getchar();  // consume newline left by scanf

            printf("What to send (end with an empty line):\n");
            while (1) {
                fgets(message, sizeof(message), stdin);
                // Stop if user enters a blank line
                if (message[0] == '\n') {
                    break;
                }
                strcat(lines, message);
            }

            printf("\nSending to : %d\n", systemid);
            printf("Message:\n%s", lines);

            fp = fopen("b_ui.txt", "w");
            if (fp == NULL) {
                perror("Error opening file");
                continue;
            }
	    fwrite(&systemid,1,sizeof(int),fp);
            fwrite(lines, sizeof(char), strlen(lines), fp);
            fclose(fp);
            printf("\nSent!!!\n");
        }

        else if (choice == 2) {
	    systemid = 0;
            printf("\nDisplaying Message:\n");
            fp = fopen("b_ui.txt", "r");
            if (fp == NULL) {
                perror("Error opening file");
                continue;
            }
	    //fread(&systemid,1,4,fp);
            //printf("%d\n",systemid);
	    fseek(fp,4,SEEK_SET);
            while (fgets(message, sizeof(message), fp) != NULL) {
                printf("%s", message);
            }

            fclose(fp);
            printf("\n--- End of Message ---\n");
        }

        else if (choice == 3) {
            printf("Exiting...\n");
            break;
        }

        else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
