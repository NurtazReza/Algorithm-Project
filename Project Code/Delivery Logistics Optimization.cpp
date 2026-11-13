#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

#define MAXN 20
#define MAXW 200
#define MAXVOL 200

// Data model (arrays only)
int idArr[MAXN];
int valueArr[MAXN];
int weightArr[MAXN];
int volumeArr[MAXN];
int deadlineArr[MAXN];
int zoneArr[MAXN];
double xArr[MAXN], yArr[MAXN];

int N = 0;                // number of packages active in dataset
int VAN_MAX_WEIGHT = 50;  // default capacities (can be overridden by dataset)
int VAN_MAX_VOLUME = 60;
double DEPOT_X = 0.0, DEPOT_Y = 0.0;

// -------------------------------
// Utility functions
// -------------------------------
double euclidean(double x1, double y1, double x2, double y2)
{
    double dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx*dx + dy*dy);
}

void printDatasetSummary()
{
    cout << "\nDataset summary: N = " << N
         << ", Van Max Weight = " << VAN_MAX_WEIGHT
         << ", Van Max Volume = " << VAN_MAX_VOLUME << "\n";
    cout << "id | value | weight | volume | deadline | zone | (x,y)\n";
    cout << "------------------------------------------------------\n";
    for (int i = 0; i < N; ++i)
    {
        cout << setw(2) << idArr[i] << " | "
             << setw(5) << valueArr[i] << " | "
             << setw(6) << weightArr[i] << " | "
             << setw(6) << volumeArr[i] << " | "
             << setw(8) << deadlineArr[i] << " | "
             << setw(4) << zoneArr[i] << " | "
             << "(" << xArr[i] << "," << yArr[i] << ")\n";
    }
    cout << "------------------------------------------------------\n";
}

// compute metrics for a chosen set (chosen[i] == 1 means selected)
struct Metrics
{
    int totalValue;
    int totalWeight;
    int totalVolume;
    int count;
    int deadlinesMet;
};

Metrics computeMetrics(const int chosen[])
{
    Metrics m;
    m.totalValue = m.totalWeight = m.totalVolume = m.count = m.deadlinesMet = 0;
    double curX = DEPOT_X, curY = DEPOT_Y;
    double time = 0.0;
    for (int i = 0; i < N; ++i)
    {
        if (chosen[i])
        {
            m.totalValue += valueArr[i];
            m.totalWeight += weightArr[i];
            m.totalVolume += volumeArr[i];
            m.count++;
            double d = euclidean(curX, curY, xArr[i], yArr[i]);
            time += d;
            if (time <= deadlineArr[i] + 1e-9) m.deadlinesMet++;
            curX = xArr[i]; curY = yArr[i];
        }
    }
    return m;
}

void printChosenItems(const int chosen[])
{
    cout << "Selected items (by id): ";
    for (int i = 0; i < N; ++i) if (chosen[i]) cout << idArr[i] << " ";
    cout << "\n";
}

// Datasets (multiple types)
void loadSmallDataset()
{
    N = 5;
    VAN_MAX_WEIGHT = 20;
    VAN_MAX_VOLUME = 20;
    int ids[5] = {1,2,3,4,5};
    int val[5] = {3,4,5,8,10};
    int wt[5]  = {2,3,4,5,9};
    int vol[5] = {3,4,5,7,9};
    int dl[5]  = {10,8,12,6,20};
    int zn[5]  = {1,1,2,2,3};
    double xs[5] = {1,2,3,4,0};
    double ys[5] = {0,1,2,1,3};
    for (int i = 0; i < N; ++i)
    {
        idArr[i] = ids[i]; valueArr[i] = val[i];
        weightArr[i] = wt[i]; volumeArr[i] = vol[i];
        deadlineArr[i] = dl[i]; zoneArr[i] = zn[i];
        xArr[i] = xs[i]; yArr[i] = ys[i];
    }
    cout << "\nSmall dataset loaded.\n\n";
}

void loadMediumDataset()
{
    N = 10;
    VAN_MAX_WEIGHT = 40;
    VAN_MAX_VOLUME = 50;
    int ids[10] = {1,2,3,4,5,6,7,8,9,10};
    int val[10] = {8,11,14,7,6,9,4,5,13,15};
    int wt[10] = {5,7,8,9,4,6,3,2,10,12};
    int vol[10] = {6,10,9,8,4,7,5,3,11,13};
    int dl[10] = {20,10,30,8,12,15,40,25,18,22};
    int zn[10] = {1,2,1,3,2,1,3,2,1,2};
    double xs[10] = { 3,1,-2,5,-3,2,0,4,-4,1};
    double ys[10] = { 4,1,2,-1,-3,-2,4,4,1,-2};
    for (int i = 0; i < N; ++i)
    {
        idArr[i] = ids[i]; valueArr[i] = val[i];
        weightArr[i] = wt[i]; volumeArr[i] = vol[i];
        deadlineArr[i] = dl[i]; zoneArr[i] = zn[i];
        xArr[i] = xs[i]; yArr[i] = ys[i];
    }
    cout << "\nMedium dataset loaded.\n\n";
}

void loadLargeDataset()
{
    N = 15;
    VAN_MAX_WEIGHT = 70;
    VAN_MAX_VOLUME = 80;
    int ids[15] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int val[15] = {10,13,17,9,11,14,15,6,7,18,20,5,4,19,12};
    int wt[15] =  {5,9,12,7,8,10,11,4,6,13,15,3,2,14,9};
    int vol[15] = {6,10,13,8,9,11,12,5,7,14,16,4,3,15,10};
    int dl[15] =  {30,12,40,8,15,18,25,22,20,35,45,10,6,28,16};
    int zn[15] =  {1,2,1,3,2,1,3,2,1,2,3,1,2,3,2};
    double xs[15] = {3,1,-2,5,-3,2,0,4,-4,1,2,-1,-2,5,-3};
    double ys[15] = {4,1,2,-1,-3,-2,4,4,1,-2,3,-2,2,0,1};
    for (int i = 0; i < N; ++i)
    {
        idArr[i] = ids[i]; valueArr[i] = val[i];
        weightArr[i] = wt[i]; volumeArr[i] = vol[i];
        deadlineArr[i] = dl[i]; zoneArr[i] = zn[i];
        xArr[i] = xs[i]; yArr[i] = ys[i];
    }
    cout << "\nLarge dataset loaded.\n\n";
}

void load2DFriendlyDataset()
{
    N = 12;
    VAN_MAX_WEIGHT = 60;
    VAN_MAX_VOLUME = 35;
    int ids[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int val[12] = {20,18,25,15,12,30,22,10,8,27,14,16};
    int wt[12] =  {6,5,10,4,3,12,7,2,1,9,4,5};
    int vol[12] = {8,7,12,6,5,15,9,3,2,11,4,6};
    int dl[12] =  {20,18,30,12,10,40,25,8,6,32,14,15};
    int zn[12] =  {1,1,2,2,3,1,2,3,1,2,3,1};
    double xs[12] = {1,2,3,4,0,-2,2,-1,0,3,-2,1};
    double ys[12] = {0,1,2,-1,3,2,0,4,1,-3,2,0};
    for (int i = 0; i < N; ++i)
    {
        idArr[i] = ids[i]; valueArr[i] = val[i];
        weightArr[i] = wt[i]; volumeArr[i] = vol[i];
        deadlineArr[i] = dl[i]; zoneArr[i] = zn[i];
        xArr[i] = xs[i]; yArr[i] = ys[i];
    }
    cout << "\n2D-friendly dataset loaded.\n\n";
}

void loadAdversarialDataset()
{
    // Designed to show greedy pitfalls
    N = 8;
    VAN_MAX_WEIGHT = 20;
    VAN_MAX_VOLUME = 25;
    // A mix: one heavy-high-value, many medium small with better ratio
    int ids[8] = {1,2,3,4,5,6,7,8};
    int val[8] = {100,18,18,18,18,18,18,18};
    int wt[8] =  {18,3,3,3,3,3,3,3};
    int vol[8] = {18,3,3,3,3,3,3,3};
    int dl[8] =  {50,20,20,20,20,20,20,20};
    int zn[8] =  {1,1,1,1,1,1,1,1};
    double xs[8] = {0,1,1,1,1,1,1,1};
    double ys[8] = {0,1,2,3,4,5,6,7};
    for (int i = 0; i < N; ++i)
    {
        idArr[i] = ids[i]; valueArr[i] = val[i];
        weightArr[i] = wt[i]; volumeArr[i] = vol[i];
        deadlineArr[i] = dl[i]; zoneArr[i] = zn[i];
        xArr[i] = xs[i]; yArr[i] = ys[i];
    }
    cout << "\nAdversarial dataset loaded.\n\n";
}

// -------------------------------
// Algorithm functions (each separate)
// -------------------------------

// 1) Brute Force (exhaustive). N must be <= MAXN (we keep N <= 20 in datasets)
void bruteForce(int chosenOut[])
{
    int bestChosen[MAXN] = {0};
    int bestVal = -1;
    long long total = 1LL << N; // N <= 20 OK
    for (long long mask = 0; mask < total; ++mask)
    {
        int sumW = 0, sumV = 0, sumVal = 0;
        bool ok = true;
        for (int i = 0; i < N; ++i)
        {
            if (mask & (1LL << i))
            {
                sumW += weightArr[i];
                sumV += volumeArr[i];
                if (sumW > VAN_MAX_WEIGHT || sumV > VAN_MAX_VOLUME) { ok = false; break; }
                sumVal += valueArr[i];
            }
        }
        if (!ok) continue;
        if (sumVal > bestVal)
        {
            bestVal = sumVal;
            for (int i = 0; i < N; ++i) bestChosen[i] = (mask & (1LL << i)) ? 1 : 0;
        }
    }
    for (int i = 0; i < N; ++i) chosenOut[i] = bestChosen[i];
}

// 2) 0/1 Knapsack DP (weight only)
void knap01DP(int chosenOut[])
{
    static int dp[MAXN+1][MAXW+1];
    static char take[MAXN+1][MAXW+1];
    int W = VAN_MAX_WEIGHT;
    for (int i = 0; i <= N; ++i)
        for (int w = 0; w <= W; ++w) { dp[i][w] = 0; take[i][w] = 0; }
    for (int i = 1; i <= N; ++i)
    {
        int wt = weightArr[i-1];
        int val = valueArr[i-1];
        for (int w = 0; w <= W; ++w)
        {
            dp[i][w] = dp[i-1][w];
            take[i][w] = 0;
            if (w >= wt)
            {
                int cand = dp[i-1][w-wt] + val;
                if (cand > dp[i][w]) { dp[i][w] = cand; take[i][w] = 1; }
            }
        }
    }
    // backtrack
    int w = W;
    for (int i = N; i >= 1; --i)
    {
        if (take[i][w])
        {
            chosenOut[i-1] = 1;
            w -= weightArr[i-1];
        } else chosenOut[i-1] = 0;
    }
}

// 3) 2D Knapsack DP (weight + volume)
void knap2DDP(int chosenOut[])
{
    static int dp[MAXN+1][MAXW+1][MAXVOL+1];
    static char take[MAXN+1][MAXW+1][MAXVOL+1];
    int W = VAN_MAX_WEIGHT, V = VAN_MAX_VOLUME;
    // init
    for (int i = 0; i <= N; ++i)
        for (int w = 0; w <= W; ++w)
            for (int v = 0; v <= V; ++v) { dp[i][w][v] = 0; take[i][w][v] = 0; }
    for (int i = 1; i <= N; ++i)
    {
        int wt = weightArr[i-1], vol = volumeArr[i-1], val = valueArr[i-1];
        for (int w = 0; w <= W; ++w)
        {
            for (int v = 0; v <= V; ++v)
            {
                dp[i][w][v] = dp[i-1][w][v];
                take[i][w][v] = 0;
                if (w >= wt && v >= vol)
                {
                    int cand = dp[i-1][w-wt][v-vol] + val;
                    if (cand > dp[i][w][v]) { dp[i][w][v] = cand; take[i][w][v] = 1; }
                }
            }
        }
    }
    // backtrack
    int w = W, v = V;
    for (int i = N; i >= 1; --i)
    {
        if (take[i][w][v])
        {
            chosenOut[i-1] = 1;
            w -= weightArr[i-1];
            v -= volumeArr[i-1];
        } else chosenOut[i-1] = 0;
    }
}

// 4) Fractional Knapsack (greedy by value/weight ratio)
// returns fractional array (0..1) in fracOut; for comparison we also produce chosenOut for full items only
void fractionalKnapsack(double fracOut[], int chosenOut[])
{
    int idx[MAXN];
    double ratio[MAXN];
    for (int i = 0; i < N; ++i)
    {
        idx[i] = i;
        ratio[i] = double(valueArr[i]) / double(max(1, weightArr[i]));
        fracOut[i] = 0.0;
        chosenOut[i] = 0;
    }
    // bubble sort by ratio desc
    for (int a = 0; a < N-1; ++a)
        for (int b = 0; b < N-1-a; ++b)
            if (ratio[idx[b]] < ratio[idx[b+1]]) swap(idx[b], idx[b+1]);

    int remW = VAN_MAX_WEIGHT;
    for (int k = 0; k < N && remW > 0; ++k)
    {
        int i = idx[k];
        if (weightArr[i] <= remW)
        {
            fracOut[i] = 1.0;
            chosenOut[i] = 1;
            remW -= weightArr[i];
        }
        else
        {
            fracOut[i] = double(remW) / double(weightArr[i]);
            // fractional; chosenOut remains 0 (we don't mark partial as full)
            remW = 0;
        }
    }
}

// Helper: zero an integer array
void zeroIntArray(int a[]) { for (int i = 0; i < MAXN; ++i) a[i] = 0; }

// 5) Greedy by Value
void greedyByValue(int chosenOut[])
{
    int idx[MAXN];
    for (int i = 0; i < N; ++i) idx[i] = i;
    // sort idx by value desc (bubble)
    for (int a = 0; a < N-1; ++a)
        for (int b = 0; b < N-1-a; ++b)
            if (valueArr[idx[b]] < valueArr[idx[b+1]]) swap(idx[b], idx[b+1]);
    int curW = 0, curV = 0;
    zeroIntArray(chosenOut);
    for (int k = 0; k < N; ++k)
    {
        int i = idx[k];
        if (curW + weightArr[i] <= VAN_MAX_WEIGHT && curV + volumeArr[i] <= VAN_MAX_VOLUME)
        {
            chosenOut[i] = 1;
            curW += weightArr[i];
            curV += volumeArr[i];
        }
    }
}

// 6) Greedy by Weight (light-first)
void greedyByWeight(int chosenOut[])
{
    int idx[MAXN];
    for (int i = 0; i < N; ++i) idx[i] = i;
    for (int a = 0; a < N-1; ++a)
        for (int b = 0; b < N-1-a; ++b)
            if (weightArr[idx[b]] > weightArr[idx[b+1]]) swap(idx[b], idx[b+1]);
    int curW = 0, curV = 0;
    zeroIntArray(chosenOut);
    for (int k = 0; k < N; ++k)
    {
        int i = idx[k];
        if (curW + weightArr[i] <= VAN_MAX_WEIGHT && curV + volumeArr[i] <= VAN_MAX_VOLUME)
        {
            chosenOut[i] = 1;
            curW += weightArr[i];
            curV += volumeArr[i];
        }
    }
}

// 7) Greedy by Value/Weight ratio
void greedyByRatio(int chosenOut[])
{
    int idx[MAXN];
    double ratio[MAXN];
    for (int i = 0; i < N; ++i) { idx[i] = i; ratio[i] = double(valueArr[i]) / double(max(1, weightArr[i])); }
    for (int a = 0; a < N-1; ++a)
        for (int b = 0; b < N-1-a; ++b)
            if (ratio[idx[b]] < ratio[idx[b+1]]) swap(idx[b], idx[b+1]);
    int curW = 0, curV = 0;
    zeroIntArray(chosenOut);
    for (int k = 0; k < N; ++k)
    {
        int i = idx[k];
        if (curW + weightArr[i] <= VAN_MAX_WEIGHT && curV + volumeArr[i] <= VAN_MAX_VOLUME)
        {
            chosenOut[i] = 1; curW += weightArr[i]; curV += volumeArr[i];
        }
    }
}

// 8) Greedy by Earliest Deadline (EDF)
void greedyByDeadline(int chosenOut[])
{
    int idx[MAXN];
    for (int i = 0; i < N; ++i) idx[i] = i;
    for (int a = 0; a < N-1; ++a)
        for (int b = 0; b < N-1-a; ++b)
            if (deadlineArr[idx[b]] > deadlineArr[idx[b+1]]) swap(idx[b], idx[b+1]);
    int curW = 0, curV = 0;
    zeroIntArray(chosenOut);
    for (int k = 0; k < N; ++k)
    {
        int i = idx[k];
        if (curW + weightArr[i] <= VAN_MAX_WEIGHT && curV + volumeArr[i] <= VAN_MAX_VOLUME)
        {
            chosenOut[i] = 1; curW += weightArr[i]; curV += volumeArr[i];
        }
    }
}

// 9) Greedy by Zone (ascending zone id)
void greedyByZone(int chosenOut[])
{
    int idx[MAXN];
    for (int i = 0; i < N; ++i) idx[i] = i;
    for (int a = 0; a < N-1; ++a)
        for (int b = 0; b < N-1-a; ++b)
            if (zoneArr[idx[b]] > zoneArr[idx[b+1]]) swap(idx[b], idx[b+1]);
    int curW = 0, curV = 0;
    zeroIntArray(chosenOut);
    for (int k = 0; k < N; ++k)
    {
        int i = idx[k];
        if (curW + weightArr[i] <= VAN_MAX_WEIGHT && curV + volumeArr[i] <= VAN_MAX_VOLUME)
        {
            chosenOut[i] = 1; curW += weightArr[i]; curV += volumeArr[i];
        }
    }
}

// -------------------------------
// Comparison table runner
// -------------------------------
void runComparisonAndPrint()
{
    cout << "\nRunning all algorithms on current dataset...\n";
    int chosen[MAXN];
    double frac[MAXN];

    // Brute Force
    zeroIntArray(chosen);
    bruteForce(chosen);
    Metrics mBrute = computeMetrics(chosen);

    // 0/1 DP
    int chosen01[MAXN]; zeroIntArray(chosen01);
    knap01DP(chosen01);
    Metrics m01 = computeMetrics(chosen01);

    // 2D DP
    int chosen2D[MAXN]; zeroIntArray(chosen2D);
    knap2DDP(chosen2D);
    Metrics m2D = computeMetrics(chosen2D);

    // Fractional
    int chosenFrFull[MAXN]; zeroIntArray(chosenFrFull);
    fractionalKnapsack(frac, chosenFrFull);
    Metrics mFracFull = computeMetrics(chosenFrFull);
    // compute fractional total value explicitly
    double fracTotalValue = 0.0;
    for (int i = 0; i < N; ++i) fracTotalValue += frac[i] * double(valueArr[i]);

    // Greedy variants
    int gVal[MAXN]; zeroIntArray(gVal); greedyByValue(gVal); Metrics mgVal = computeMetrics(gVal);
    int gWt[MAXN]; zeroIntArray(gWt); greedyByWeight(gWt); Metrics mgWt = computeMetrics(gWt);
    int gRatio[MAXN]; zeroIntArray(gRatio); greedyByRatio(gRatio); Metrics mgRatio = computeMetrics(gRatio);
    int gDead[MAXN]; zeroIntArray(gDead); greedyByDeadline(gDead); Metrics mgDead = computeMetrics(gDead);
    int gZone[MAXN]; zeroIntArray(gZone); greedyByZone(gZone); Metrics mgZone = computeMetrics(gZone);

        // Print table header
    cout << "\n-------------------------------------------------------------------------------\n";
    cout << left << setw(24) << "Algorithm"
         << setw(8) << "Value"
         << setw(10) << "Weight"
         << setw(10) << "Volume"
         << setw(8)  << "#Items"
         << setw(12) << "DeadlinesMet"
         << "\n";
    cout << "-------------------------------------------------------------------------------\n";

    cout << left << setw(24) << "Brute Force (optimal)"
         << setw(8) << mBrute.totalValue
         << setw(10) << mBrute.totalWeight
         << setw(10) << mBrute.totalVolume
         << setw(8)  << mBrute.count
         << setw(12) << mBrute.deadlinesMet << "\n";

    cout << left << setw(24) << "0/1 Knapsack (DP)"
         << setw(8) << m01.totalValue
         << setw(10) << m01.totalWeight
         << setw(10) << m01.totalVolume
         << setw(8)  << m01.count
         << setw(12) << m01.deadlinesMet << "\n";

    cout << left << setw(24) << "2D Knapsack (DP)"
         << setw(8) << m2D.totalValue
         << setw(10) << m2D.totalWeight
         << setw(10) << m2D.totalVolume
         << setw(8)  << m2D.count
         << setw(12) << m2D.deadlinesMet << "\n";

    cout << left << setw(24) << "Fractional (upper bound)"
         << setw(8) << fixed << setprecision(2) << fracTotalValue
         << setw(10) << mFracFull.totalWeight
         << setw(10) << mFracFull.totalVolume
         << setw(8)  << mFracFull.count
         << setw(12) << mFracFull.deadlinesMet << "\n";
    cout << fixed; // reset

    cout << left << setw(24) << "Greedy - Value"
         << setw(8) << mgVal.totalValue
         << setw(10) << mgVal.totalWeight
         << setw(10) << mgVal.totalVolume
         << setw(8)  << mgVal.count
         << setw(12) << mgVal.deadlinesMet << "\n";

    cout << left << setw(24) << "Greedy - Weight"
         << setw(8) << mgWt.totalValue
         << setw(10) << mgWt.totalWeight
         << setw(10) << mgWt.totalVolume
         << setw(8)  << mgWt.count
         << setw(12) << mgWt.deadlinesMet << "\n";

    cout << left << setw(24) << "Greedy - Value/Weight"
         << setw(8) << mgRatio.totalValue
         << setw(10) << mgRatio.totalWeight
         << setw(10) << mgRatio.totalVolume
         << setw(8)  << mgRatio.count
         << setw(12) << mgRatio.deadlinesMet << "\n";

    cout << left << setw(24) << "Greedy - Deadline"
         << setw(8) << mgDead.totalValue
         << setw(10) << mgDead.totalWeight
         << setw(10) << mgDead.totalVolume
         << setw(8)  << mgDead.count
         << setw(12) << mgDead.deadlinesMet << "\n";

    cout << left << setw(24) << "Greedy - Zone"
         << setw(8) << mgZone.totalValue
         << setw(10) << mgZone.totalWeight
         << setw(10) << mgZone.totalVolume
         << setw(8)  << mgZone.count
         << setw(12) << mgZone.deadlinesMet << "\n";

    cout << "-------------------------------------------------------------------------------\n\n";

    // Optionally: display which items each algorithm selected (short)
    cout << "Selected item lists (id):\n";
    cout << "Brute   : "; printChosenItems(chosen);
    // To show lists properly, recompute arrays and print each
    int tmp[MAXN];
    bruteForce(tmp); cout << "Brute   : "; printChosenItems(tmp);
    knap01DP(tmp); cout << "DP01    : "; printChosenItems(tmp);
    knap2DDP(tmp); cout << "DP2D    : "; printChosenItems(tmp);
    fractionalKnapsack(frac, tmp); cout << "Fractional (full items only): "; printChosenItems(tmp);
    greedyByValue(tmp); cout << "GreedyV : "; printChosenItems(tmp);
    greedyByWeight(tmp); cout << "GreedyW : "; printChosenItems(tmp);
    greedyByRatio(tmp); cout << "GreedyR : "; printChosenItems(tmp);
    greedyByDeadline(tmp); cout << "GreedyD : "; printChosenItems(tmp);
    greedyByZone(tmp); cout << "GreedyZ : "; printChosenItems(tmp);

    cout << "\nComparison run complete.\n";
}

// Menu and main

void showMainMenu()
{
    cout << "\n====== Delivery Loading Optimization ======\n";
    cout << "\nDataset & Algorithms Menu:\n";
    cout << "1. Load Small Dataset\n";
    cout << "2. Load Medium Dataset\n";
    cout << "3. Load Large Dataset\n";
    cout << "4. Load 2D-friendly Dataset\n";
    cout << "5. Load Adversarial Dataset\n";
    cout << "6. Show Current Dataset Summary\n";
    cout << "7. Run Brute Force\n";
    cout << "8. Run 0/1 Knapsack (DP)\n";
    cout << "9. Run 2D Knapsack (DP)\n";
    cout << "10. Run Fractional Knapsack\n";
    cout << "11. Run Greedy (Value)\n";
    cout << "12. Run Greedy (Weight)\n";
    cout << "13. Run Greedy (Value/Weight)\n";
    cout << "14. Run Greedy (Deadline)\n";
    cout << "15. Run Greedy (Zone)\n";
    cout << "16. Run Full Comparison Table\n";
    cout << "17. Exit\n";
    cout << "\nEnter an option: ";
}

int main()
{
    cout << fixed << setprecision(4);
    int option;

    while (true)
    {
        showMainMenu();
        if (!(cin >> option)) { cin.clear(); cin.ignore(1000,'\n'); cout << "Invalid input\n"; continue; }
        if (option == 1) loadSmallDataset();
        else if (option == 2) loadMediumDataset();
        else if (option == 3) loadLargeDataset();
        else if (option == 4) load2DFriendlyDataset();
        else if (option == 5) loadAdversarialDataset();
        else if (option == 6) printDatasetSummary();
        else if (option == 7)
        {
            int chosen[MAXN]; zeroIntArray(chosen); bruteForce(chosen);
            cout << "\nBrute Force selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 8)
        {
            int chosen[MAXN]; zeroIntArray(chosen); knap01DP(chosen);
            cout << "\n0/1 Knapsack (DP) selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 9)
        {
            int chosen[MAXN]; zeroIntArray(chosen); knap2DDP(chosen);
            cout << "\n2D Knapsack (DP) selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 10)
        {
            double frac[MAXN]; int chosen[MAXN]; zeroIntArray(chosen); fractionalKnapsack(frac, chosen);
            cout << "\nFractional knapsack fractions (index: fraction):\n";
            double totVal = 0.0; int totW = 0, totV = 0, cntFull = 0;
            for (int i = 0; i < N; ++i)
            {
                if (frac[i] > 0.0)
                {
                    cout << idArr[i] << ":" << frac[i] << " ";
                    totVal += frac[i] * double(valueArr[i]);
                    if (frac[i] >= 1.0 - 1e-9) { totW += weightArr[i]; totV += volumeArr[i]; cntFull++; }
                }
            }
            cout << "\nFractional total value (upper bound) = " << totVal << "\n";
            cout << "Full items selected = " << cntFull << ", WeightUsed=" << totW << ", VolumeUsed=" << totV << "\n";
        }
        else if (option == 11)
        {
            int chosen[MAXN]; zeroIntArray(chosen); greedyByValue(chosen);
            cout << "\nGreedy by Value selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 12)
        {
            int chosen[MAXN]; zeroIntArray(chosen); greedyByWeight(chosen);
            cout << "\nGreedy by Weight selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 13)
        {
            int chosen[MAXN]; zeroIntArray(chosen); greedyByRatio(chosen);
            cout << "\nGreedy by Value/Weight selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 14)
        {
            int chosen[MAXN]; zeroIntArray(chosen); greedyByDeadline(chosen);
            cout << "\nGreedy by Deadline selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 15)
        {
            int chosen[MAXN]; zeroIntArray(chosen); greedyByZone(chosen);
            cout << "\nGreedy by Zone selection:\n"; printChosenItems(chosen);
            Metrics m = computeMetrics(chosen);
            cout << "Value=" << m.totalValue << ", Weight=" << m.totalWeight << ", Volume=" << m.totalVolume << ", Items=" << m.count << ", DeadlinesMet=" << m.deadlinesMet << "\n";
        }
        else if (option == 16)
        {
            runComparisonAndPrint();
        }
        else if (option == 17)
        {
            cout << "Exiting the system. Thank you for using our optimization tool.\n";
            break;
        }
        else
        {
            cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
