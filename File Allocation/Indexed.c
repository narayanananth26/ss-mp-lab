/*

File Allocation Methods: Indexed Allocation

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct file
{
    char name[20];
    int no_of_blocks;
    int index;
    int blocks[20];
} files[20];

// Stores number of total blocks
int total_blocks;
// Stores number of remaining blocks as they are allocated to files
int remaining_blocks;
// Stores the file count
int file_count = 0;
// Generating block numbers which are used for random selection (1 - block available, 0 - unavailable)
int avail_blcks[100];

void create()
{
    int count, rand_block;

    printf("Enter file name: ");
    scanf("%s", files[file_count].name);

    printf("Enter no. of blocks: ");
    scanf("%d", &files[file_count].no_of_blocks);

    // If nob > remaining blocks available
    if (files[file_count].no_of_blocks > remaining_blocks)
    {
        printf("Not enough blocks available.\n");
        return;
    }
    else
    {
        count = 0;

        do
        {
            // Generate a random block
            rand_block = rand() % total_blocks;

            // If block status is set as available
            if (avail_blcks[rand_block] != 0)
            {
                // If index block is not allocated
                if (files[file_count].index == -1)
                {
                    files[file_count].index = rand_block;
                    avail_blcks[rand_block] = 0;
                    remaining_blocks--;
                    continue;
                }

                files[file_count].blocks[count] = rand_block;
                count++;
                avail_blcks[rand_block] = 0;
                remaining_blocks--;
            }
        } while (count < files[file_count].no_of_blocks);
    }
}

void display()
{
    printf("-------------------------------------------------------\n");
    printf("File Details:\n");
    printf("%-20s%-15s%-20s%-20s\n", "Name of File", "No. of Blocks", "Index Block No.", "Blocks Allocated");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < file_count; i++) {
        printf("%-20s%-15d", files[i].name, files[i].no_of_blocks);

        if (files[i].index == -1) {
            printf("%-20s%-20s\n", "Not Allocated", "Not Allocated");
        } else {
            printf("%-20d", files[i].index);

            if (files[i].no_of_blocks > 0) {
                printf("%d", files[i].blocks[0]);
                for (int j = 1; j < files[i].no_of_blocks; j++) {
                    printf(", %d", files[i].blocks[j]);
                }
            }

            printf("\n");
        }
    }

    printf("-------------------------------------------------------\n");
    printf("Remaining blocks: %d\n", remaining_blocks);
}

int main()
{
    int choice;

    srand(time(NULL));
    printf("Enter total no. of blocks: ");
    scanf("%d", &total_blocks);

    remaining_blocks = total_blocks;

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            files[i].blocks[j] = -1;
            files[i].index = -1;
        }
    }

    // Generating block numbers which are used for random selection (1 - block available, 0 - unavailable)
    for (int i = 0; i < total_blocks; i++)
        avail_blcks[i] = 1;

    do
    {
        printf("\tMENU\n");
        printf("1. Create file\n2. Display files\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (remaining_blocks == 0)
            {
                printf("All blocks are allocated.\n");
                break;
            }
            create();
            file_count++;
            display();
            break;
        case 2:
            display();
            break;
        }
    } while (choice >= 1 && choice <= 2);

    return 0;
}

