# [GCJ 2021 #1A] Append Sort

## 题目描述

我们有一个整数列表 $X_1, X_2, \ldots, X_N$。我们希望它们能按**严格递增**的顺序排列，但遗憾的是不能直接重新排序。这意味着常规的排序算法无法使用。

我们唯一的操作是在这些数字的右侧（十进制下）追加数字 $0$ 到 $9$。例如，若某数字是 $10$，通过一次追加操作可以变为 $100$ 或 $109$，通过两次操作可变为 $1034$（如下图所示）。

给定当前列表，至少需要进行多少次单数字追加操作才能使列表严格递增？

例如，对于列表 $100, 7, 10$，可通过 $4$ 次操作将其变为有序列表，如下图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/x5uxrlzd.png)

## 说明/提示

**样例解释**

在样例 #1 中，输入与题目描述中的示例相同。如图所示，需 $4$ 次操作使列表有序。注意最后两个数字最终至少需要 $3$ 位数字（共需至少 $3$ 次追加操作）。若所有数字最终均为 $3$ 位，由于第二个数字以 $7$ 开头而第三个以 $1$ 开头，第二个数字仍会大于第三个，因此无法用少于 $4$ 次操作完成。

在样例 #2 中，由于要求严格递增，必须至少进行 $1$ 次操作。此处对第二个数字追加任意有效数字均可。

在样例 #3 中，可通过 $2$ 次操作将列表变为 $4, 19, 193$。

在样例 #4 中，列表已严格递增，无需操作。

**数据范围**

- $1 \leq \mathbf{T} \leq 100$。

**测试集 1（12 分，可见判定）**

- $2 \leq \mathbf{N} \leq 3$。
- $1 \leq \mathbf{X}_i \leq 100$（对所有 $i$）。

**测试集 2（14 分，可见判定）**

- $2 \leq \mathbf{N} \leq 100$。
- $1 \leq \mathbf{X}_i \leq 10^9$（对所有 $i$）。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
3
100 7 10
2
10 10
3
4 19 1
3
1 2 3```

### 输出

```
Case #1: 4
Case #2: 1
Case #3: 2
Case #4: 0```

# 题解

## 作者：Zyh20101221 (赞：0)

## 题目分析
这题要求我们将给定的整数列表通过最少的追加数字操作变成严格递增序列。每次操作可以在数字的右侧追加一个数字。我们需要找到最优的追加策略，使得操作次数最少。

## 解题思路
从左到右处理：我们需要确保每个数字比前一个数字大，因此从左到右依次处理每个数字。

比较当前数字与前一个数字：如果当前数字已经大于前一个数字，无需处理。否则，需要在当前数字后追加若干数字，使其大于前一个数字。

追加策略：

1. 位数相同：直接比较数值，如果当前数字较小，则追加一个 $0$ 使其变大。

2. 当前数字位数较少：
如果当前数字是前一个数字的前缀且前一个数字剩余部分不全为 $9$，可以追加剩余部分 $+1$。否则，追加足够的 $0$ 使位数相同，再比较数值。

3. 特殊情况：如果前一个数字以当前数字为前缀且剩余部分全为 $9$，则必须增加一位。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n;

int main() {
    cin >> T;
    for(int t = 1; t <= T; t++){
        cin >> n;
        vector<string> nums(n);
        for (int i = 0; i < n; ++i) {
            cin >> nums[i];
        }
        int res = 0;
        for (int i = 1; i < n; ++i) {
            string prev = nums[i-1];
            string curr = nums[i];
            int added = 0;
            
            while (true) {
                if (curr.size() > prev.size()) {
                    break;
                } else if (curr.size() == prev.size()) {
                    if (curr > prev) {
                        break;
                    } else {
                        curr += '0';
                        added++;
                    }
                } else { // curr.size() < prev.size()
                    string prefix = prev.substr(0, curr.size());
                    if (prefix > curr) {
                        int need = prev.size() - curr.size();
                        curr += string(need, '0');
                        added += need;
                    } else if (prefix == curr) {
                        string rem = prev.substr(curr.size());
                        bool all9 = true;
                        for (char c : rem) {
                            if (c != '9') {
                                all9 = false;
                                break;
                            }
                        }
                        if (all9) {
                            int need = prev.size() - curr.size() + 1;
                            curr += string(need, '0');
                            added += need;
                        } else {
                            string temp = rem;
                            int k = temp.size() - 1;
                            while (k >= 0 && temp[k] == '9') {
                                temp[k] = '0';
                                k--;
                            }
                            if (k >= 0) {
                                temp[k]++;
                            }
                            curr += temp;
                            added += rem.size();
                        }
                    } else { // prefix < curr
                        int need = prev.size() - curr.size();
                        curr += string(need, '0');
                        added += need;
                    }
                }
            }
            nums[i] = curr;
            res += added;
        }
        cout << "Case #" << t << ": " << res << endl; //这需要注意
    }
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/226908030)

---

## 作者：yihang2011 (赞：0)

### [P13026 [GCJ 2021 #1A] Append Sort](https://www.luogu.com.cn/problem/P13026)

贪心题。~~调了我一个半小时。~~

题意：给出 $N$ 个正整数 $X_1, X_2,\cdots, X_n$，要求通过在这些数后面添加若干数字（可以不加），使得序列 $X$ 单调递增。求添加数字个数最小值。

首先，为了使后面增加的个数变少，每次增加需要增加到满足条件的最小的正整数。序列中的每个数都可以看成一个字符串。

记 $\text{len}(x)$ 为 $x$ 的位数。

对于 $X_i$，当 $i = 1$ 时，不用添加任何数字。当 $i = 2$ 时，分类讨论：

- 当 $X_{i - 1} < X_i$ 时，不用添加任何数字；

- 否则，可以考虑两种添加方式：$X_i \gets X_{i - 1} + 1$ 或 $X_i \gets X_i \times 10^k$，即 $X_i$ 为 $X_{i - 1} + 1$ 或往 $X_i$ 的后面添 $0$ 直到大于 $X_{i - 1}$。

  显然，前者更优，但前者有前提条件，即 $X_i$ 是 $X_{i - 1} + 1$ 的前缀且 $\text{len}(X_i) < \text{len}(X_{i - 1})$，这种方案需要添加 $\text{len}(X_{i - 1}) - \text{len}(X_i)$ 个数字。而若不满足条件，只能取后者，添加 $0$ 直至 $X_i > X_{i - 1}$，这可能需要添加 $\text{len}(X_{i - 1}) - \text{len}(X_i)$ 或 $\text{len}(X_{i - 1}) - \text{len}(X_i)$ 个数字。

照思路模拟即可。时间复杂度 $O(TN)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define mt make_tuple
#define pqueue priority_queue
#define umap unordered_map
#define set(f, x) memset(f, x, sizeof f)
using ll = long long;
ll read() {
    int x = 0, f = 1; char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0', ch = getchar();
    }
    return x * f;
}
#define rd read()
void write(ll x) {
    if (x < 0) {
        putchar('-'), x = -x;
    } 
    if (x > 9) {
        write(x / 10);
    }
    putchar(x % 10 + '0');
}
#define wln(x) write(x); putchar('\n');
#define wt(x) write(x); putchar(' ');
#define db(x) printf(#x); putchar(':'); wln(x);

const int N = 110;
int n, ans;
string x;

bool compare(string x, string y) {
    // x > y return true, x <= y return false;
    if (x.size() != y.size()) {
        return x.size() > y.size();
    }
    for (int i = 0; i < x.size(); i++) {
        if (x[i] < y[i]) {
            return false;
        } 
        if (x[i] > y[i]) {
            return true;
        }
    }
    return false;
}

string plusone(string x) { // 加一
    for (int i = x.size() - 1; i >= 0; i--) {
        if (x[i] != '9') {
            x[i]++;
            return x;
        }
        x[i] = '0';
    }
    if (x[0] == '0') {
        return ("1" + x);
    }
    return x;
}

int solve() {
    ans = 0;
    n = rd;
    string last;
    cin >> last;
    for (int i = 2; i <= n; i++) {
        cin >> x;
        if (compare(x, last)) { // 本来就递增
            last = x;
            continue ;
        }
        if (x.size() < last.size() && last.substr(0, x.size()) == x && plusone(last).substr(0, x.size()) == last.substr(0, x.size())) { // 如果这个数是前一个的前缀
            /*
             是前缀的同时还需要满足两个条件：
             一是这个数位数比前一个数少，因为加一后位数不变，但题目中只能添加数字不能修改数字；
             二是前一个数加一后的前缀还有这个数，因为如果加一产生的进位影响到了高位导致前缀部分变化，那么就没法直接加一了。
             其实可以花间一下，不用这个数是不是前一个的前缀，只用判这个数是不是前一个数加一的前缀就行了（理论上）。
            */
            ans += last.size() - x.size();
            last = plusone(last);
        } else {
            // 不是前缀，往这个数后面添0，先添到与前一个数位数相同
            ans += last.size() - x.size();
            x += string(last.size() - x.size(), '0');
            if (!compare(x, last)) { // 如果位数相同但还是比前一个数小或等于前一个数
                // 那么还需要添一个0
                ans++;
                x += "0";
            } 
            last = x;
        }
    }
    return ans;
}

int main() {
    int T = rd;
    for (int i = 1; i <= T; i++) {
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
```

[AC Record](https://www.luogu.com.cn/record/224766532)

---

