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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cycle(int winner, int loser); // add my self

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {

        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            for (int j = 0; j < pair_count - i - 1; j++)
            {
                if (preferences[pairs[j].winner][pairs[j].loser] <
                    preferences[pairs[j + 1].winner][pairs[j + 1].loser])
                {
                    pair temp = pairs[j];
                    pairs[j] = pairs[j + 1];
                    pairs[j + 1] = temp;
                }
            }
        }
    }
}

bool check_cycle(int winner, int loser)
{
    if (loser == winner)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (check_cycle(winner, i))
            {
                return true;
            }
        }
    }
    return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!check_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = false;
                break;
            }
        }
        if (is_source)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}


// #define	candidate{A ,B, C}  Voters = 3

// rank[]=vote()

// preference[]=record_preferences()

// pairs[]=add_pairs()


// Voter1 =    R1 =A	rank[]=0 1 2
// 	        R2 =B 	preference = [0][1]+1  [0][2]+1 [1][2]+1
// 	        R3 =C

// Voter2 =    R1 =B	rank[]=1 2 0
// 	        R2 =C 	preference = [1][2]+1  [1][0]+1 [2][0]+1
// 	        R3 =A

// Voter3 =    R1 =C	rank[]=2 0 1
//        	    R2 =A	preference = [2][0]+1  [2][1]+1 [0][1]+1
// 	        R3 =B

// preferences = [ //[↓][→]
//   [0, 2, 1],
//   [1, 0, 2],
//   [2, 1, 0]
// ]

// pairs[]->{{0,1},{1,2},{2,1}}
// sort_pairs()
// pairs[]->{{0,1},{1,2},{2,1}}

// locked = {
//   [false, false, false], // A>B
//   [false, false, false], // B>C
//   [false, false, false]  // C>A
// }

// locked()
//     Before locking the pair, check if adding this pair would create a cycle using the check_cycle function.
//     If adding the pair does not create a cycle, lock the pair by setting locked[winner][loser] to true.

// check_cycle()
//     Base Case: If the loser is the same as the winner, it means there is a cycle, so return true.
//     Recursively check all the successors of the loser. If any of these paths leads back to the winner, a cycle is detected, and true is returned.
//     If no path from the loser leads back to the winner, return false.

// locked = {
//   [false, true, false], // A>B
//   [false, false, true], // B>C
//   [false, false, false]  // C>A
// }

// print_winner()
//     Check all other candidates to see if there is any locked pair pointing to the current candidate.
//     If no locked pair points to the current candidate, they are the source, and thus the winner. Print their name and return.
