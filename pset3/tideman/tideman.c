#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair pairs_sorted[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    printf("[0][1]/[J][M]: %i\n",preferences[0][1]);////////////////////////////////////////////////////////////////////////////////////////////////
    printf("[0][2]/[J][P]: %i\n",preferences[0][2]);
    printf("[1][0]/[M][J]: %i\n",preferences[1][0]);

    printf("[1][2]/[M][P]: %i\n",preferences[1][2]);
    printf("[2][0]/[P][J]: %i\n",preferences[2][0]);
    printf("[2][1]/[P][M]: %i\n",preferences[2][1]);



    add_pairs();
    sort_pairs();
    // for (int i=0; i<pair_count; i++)
    //     printf("%i>%i (%li)\n",pairs_sorted[i].winner,pairs_sorted[i].loser,preferences[pairs_sorted[i].winner]-preferences[pairs_sorted[i].loser]);
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i=0; i<candidate_count; i++)
    {
        if (strcmp(candidates[i],name)==0)
        {
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i=0; i<candidate_count; i++)
    {
        for (int j=i+1; j<candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i=0; i<candidate_count; i++)
    {
        for (int j=i+1; j<candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i] || preferences[i][j] == preferences[j][i])
            {
                pairs[pair_count].winner=i;
                pairs[pair_count].loser=j;
                pair_count++;
            }
            else
            {
                pairs[pair_count].winner=j;
                pairs[pair_count].winner=i;
                pair_count++;
            }
        }
    }

    for (int i = 0; i<pair_count; i++)
    {
        printf("%s>%s\n",candidates[pairs[i].winner],candidates[pairs[i].loser]);///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int n=pair_count-1;
    for (int i=0; i<pair_count; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (preferences[pairs[j].winner]-preferences[pairs[j].loser]<preferences[pairs[j+1].winner]-preferences[pairs[j+1].loser])
                pairs_sorted[j]=pairs[j+1];
            else
                pairs_sorted[j]=pairs[j];
        }
        n=n-1;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int n=0; n<candidate_count; n++)
    {
        i=pairs_sorted.winner[n];
        j=pairs_sorted.loser[n];
        locked[i][j]=true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // for (int )
    return;
}

