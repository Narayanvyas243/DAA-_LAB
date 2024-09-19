#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    int deadline;
    int profit;
} Job;

void swap(Job *a, Job *b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void sortJobsByProfit(Job jobs[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (jobs[i].profit < jobs[j].profit) {
                swap(&jobs[i], &jobs[j]);
            }
        }
    }
}

int findMaxDeadline(Job jobs[], int n) {
    int maxDeadline = jobs[0].deadline;
    for (int i = 1; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }
    return maxDeadline;
}

void jobScheduling(Job jobs[], int n) {
    sortJobsByProfit(jobs, n);
    
    int maxDeadline = findMaxDeadline(jobs, n);
    int slot[maxDeadline + 1];
    bool slotFilled[maxDeadline + 1];

    for (int i = 0; i <= maxDeadline; i++) {
        slotFilled[i] = false;
    }

    int totalProfit = 0;
    int countJobs = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (!slotFilled[j]) {
                slotFilled[j] = true;
                slot[j] = i;
                totalProfit += jobs[i].profit;
                countJobs++;
                break;
            }
        }
    }

    printf("Selected Jobs:\n");
    for (int i = 1; i <= maxDeadline; i++) {
        if (slotFilled[i]) {
            printf("Job %d (Profit: %d, Deadline: %d)\n", jobs[slot[i]].id, jobs[slot[i]].profit, jobs[slot[i]].deadline);
        }
    }
    printf("\nTotal Profit: %d\n", totalProfit);
}

int main() {
    Job jobs[] = {
        {1, 2, 100},
        {2, 1, 19},
        {3, 2, 27},
        {4, 1, 25},
        {5, 3, 15}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);

    jobScheduling(jobs, n);

    return 0;
}
