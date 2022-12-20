#include <bits/stdc++.h>

using namespace std;

class Elements {
public:
    double w, p, ratio, index;
    void makeRatio() {
        ratio = p / w;
    }
};

class Output {
public:
    int index;
    double profit;
    double quantity;
};

void Result(Elements products[], int n, double w, int s, int e) {
    vector<Output> res;
    int cur_w = w, i = s;
    while (cur_w && i != e) {
        Output r;
        r.index = products[i].index;
        if (products[i].w <= cur_w) {
            r.quantity = products[i].w;
            r.profit = products[i].p;
            cur_w -= products[i].w;
        }
        else if (products[i].w >= cur_w) {
            r.quantity = cur_w;
            r.profit = products[i].ratio * cur_w;
            cur_w = 0;
        }
        if (s < e) i++;
        else i--;
        res.push_back(r);
    }
    cout << "Number of object\t Profit\t Value of x\n";
    double total_profit = 0.0, total_weight = 0.0;
    for (i = 0; i < res.size(); i++) {
        cout << res[i].index << "\t\t\t " << res[i].profit << "\t " << res[i].quantity << endl;
        total_profit += res[i].profit;
        total_weight += res[i].quantity;
    }
    cout << "\n";
    cout << "Total Profit: " << total_profit << "\n";
    cout << "Total Weight: " << total_weight << "\n";
}

void knapSack() {
    int n, i;
    double w;
    ifstream in("knapsack.txt");
    if (in.is_open()) {
        while (in >> n) {
            in >> w;
            Elements products[n];
            for (int i = 0; i < n; i++) {
                in >> products[i].w;
                products[i].index = i + 1;
            }
            for (int i = 0; i < n; i++) {
                in >> products[i].p;
                products[i].makeRatio();
            }
            cout << "Feasible Solution 01 #####----->\n\n";
            Result(products, n, w, 0, n - 1);
            cout << "\nFeasible Solution 02 #####----->\n\n";
            Result(products, n, w, n - 1, 0);
            cout << "\nOptimal Solution #####----->\n\n";
            sort(products, products + n, [](Elements &a, Elements &b)
                 { return a.ratio >= b.ratio; });
            Result(products, n, w, 0, n - 1);
        }
        in.close();
    }
}

class JobData {
public:
    int profit, index, deadline;
};

void jobSequencing() {
    int i, n;
    ifstream in("job.txt");
    if (in.is_open()) {
        in >> n;
        JobData Jobs[n];
        for (int i = 0; i < n; i++) {
            in >> Jobs[i].profit;
            Jobs[i].index = i + 1;
        }
        for (int i = 0; i < n; i++) {
            in >> Jobs[i].deadline;
        }
        sort(Jobs, Jobs + n, [](JobData &a, JobData &b)
             {if(a.deadline == b.deadline) return a.profit > b.profit;
                 else return a.deadline < b.deadline; });

        vector<int> Index;
        int total_profit = Jobs[0].profit;
        Index.push_back(Jobs[0].index);
        for (i = 1; i < n; i++) {
            while (i < n && Jobs[i].deadline == Jobs[i - 1].deadline) i++;
            if (i < n) {
                Index.push_back(Jobs[i].index);
                total_profit += Jobs[i].profit;
            }
        }
        cout << "Optimal Job Sequence to obtain maximum profit #####----->\n\n";
        for (auto x : Index) cout << x << ' ';
        cout << "\n";
        cout << "\nTotal Profit: " << total_profit << "\n\n";
    }
    in.close();
}

int main() {
    
    cout << "\n\n####################---------->     Knapsack     <----------####################\n\n";
    knapSack();
    cout << "\n\n####################---------->  Job Scheduling  <----------####################\n\n";
    jobSequencing();
}
