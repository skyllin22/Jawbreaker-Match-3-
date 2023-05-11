#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 5
#define NUM_COLORS 6
#define REQUIRED_MATCH 3
#define INDEX_OUT_OF_BOUNDS(idx, size) (((idx) < (0)) || ((idx) >= (size)))

void initialize_grid(int grid[GRID_SIZE][GRID_SIZE]);
void print_grid(int grid[GRID_SIZE][GRID_SIZE]);
int check_match(int grid[GRID_SIZE][GRID_SIZE]);
void swap_elements(int grid[GRID_SIZE][GRID_SIZE], int x1, int y1, int x2, int y2);
void apply_gravity(int grid[GRID_SIZE][GRID_SIZE]);
void fill_with_new_elements(int grid[GRID_SIZE][GRID_SIZE]);

int main(void)
{
    srand((unsigned)time(NULL));
    int grid[GRID_SIZE][GRID_SIZE];
    int x1, y1, x2, y2;

    int points = 0;
    initialize_grid(grid);

    while (1)
    {
        print_grid(grid);
        do
        {
            printf("Enter coordinates of elements to swap (x1 y1 x2 y2): ");
            scanf_s("%d %d %d %d", &x1, &y1, &x2, &y2);
            if (INDEX_OUT_OF_BOUNDS(x1, GRID_SIZE) || INDEX_OUT_OF_BOUNDS(y1, GRID_SIZE)
                || INDEX_OUT_OF_BOUNDS(x2, GRID_SIZE) || INDEX_OUT_OF_BOUNDS(y2, GRID_SIZE)) {
                printf("The provided coordinates are invalid.\n");
                continue;
            }
            swap_elements(grid, x1, y1, x2, y2);
            points = check_match(grid);
            if (points == 0)
            {
                printf("No match found. Try again.\n");
                swap_elements(grid, x1, y1, x2, y2);
            }
        } while (points == 0);

        printf("Match found! %d points gained.New elemnts have been added\n", points);

        apply_gravity(grid);
        fill_with_new_elements(grid);
    }

    return 0;
}

void initialize_grid(int grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            grid[i][j] = rand() % NUM_COLORS + 1;
        }
    }
}

void print_grid(int grid[GRID_SIZE][GRID_SIZE])
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

int check_match(int grid[GRID_SIZE][GRID_SIZE])
{
    int total_matches = 0;
    int matched[GRID_SIZE][GRID_SIZE] = { 0 };
    for (int i = 0; i < GRID_SIZE; i++)
    {
        int match_count = 1;
        int prev_color = grid[i][0];
        for (int j = 1; j < GRID_SIZE; j++)
        {
            if (grid[i][j] == prev_color)
            {
                match_count++;
            }
            else {
                if (match_count >= REQUIRED_MATCH)
                {
                    total_matches += match_count;
                    for (int k = j - match_count; k < j; k++)
                    {
                        matched[i][k] = 1;
                    }
                }
                match_count = 1;
            }
            prev_color = grid[i][j];
        }
        if (match_count >= REQUIRED_MATCH)
        {
            total_matches += match_count;
            for (int k = GRID_SIZE - match_count; k < GRID_SIZE; k++)
            {
                matched[i][k] = 1;
            }
        }
    }

    for (int j = 0; j < GRID_SIZE; j++)
    {
        int match_count = 1;
        int prev_color = grid[0][j];
        for (int i = 1; i < GRID_SIZE; i++)
        {
            if (grid[i][j] == prev_color)
            {
                match_count++;
            }
            else {
                if (match_count >= REQUIRED_MATCH)
                {
                    total_matches += match_count;
                    for (int k = i - match_count; k < i; k++)
                    {
                        matched[k][j] = 1;
                    }
                }
                match_count = 1;
            }
            prev_color = grid[i][j];
        }
        if (match_count >= REQUIRED_MATCH)
        {
            total_matches += match_count;
            for (int k = GRID_SIZE - match_count; k < GRID_SIZE; k++)
            {
                matched[k][j] = 1;
            }
        }
    }

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            if (matched[i][j] == 1)
            {
                grid[i][j] = 0;
            }
        }
    }

    return total_matches;
}
void swap_elements(int grid[GRID_SIZE][GRID_SIZE], int x1, int y1, int x2, int y2)
{
    int temp = grid[x1][y1];
    grid[x1][y1] = grid[x2][y2];
    grid[x2][y2] = temp;
}

void apply_gravity(int grid[GRID_SIZE][GRID_SIZE])
{
    for (int col = 0; col < GRID_SIZE; col++)
    {
        int row_to_fill = GRID_SIZE - 1;

        for (int row = GRID_SIZE - 1; row >= 0; row--)
        {

            if (grid[row][col] != 0)
            {
                grid[row_to_fill][col] = grid[row][col];

                if (row != row_to_fill)
                {
                    grid[row][col] = 0;
                }
                row_to_fill--;
            }
        }
    }
}

void fill_with_new_elements(int grid[GRID_SIZE][GRID_SIZE])
{

    for (int col = 0; col < GRID_SIZE; col++)
    {
        int row_to_fill = GRID_SIZE - 1;


        for (int row = GRID_SIZE - 1; row >= 0; row--)
        {

            if (grid[row][col] == 0)
            {
                int new_color = rand() % NUM_COLORS + 1;
                grid[row][col] = new_color;
            }

            else
            {
                grid[row_to_fill][col] = grid[row][col];
                row_to_fill--;
            }
        }
    }
}