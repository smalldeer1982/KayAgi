# [ICPC 2013 WF] Matryoshka

## 题目描述

套娃是俄罗斯传统木制玩具，由一组逐渐变小的娃娃组成，依次放置在另一个娃娃内部。一个套娃可以打开，露出一个更小的类似玩偶，而这个玩偶内部又有另一个玩偶，以此类推。

俄罗斯套娃博物馆最近展出了一系列设计相似的套娃，不同之处仅在于每套娃娃中嵌套的数量不同。不幸的是，一些过于热心（显然没有得到监督）的孩子把这些套娃拆散了，并将所有的单个娃娃排成一行。现在这一行中有 $n$ 个娃娃，每个都有一个整数大小。你需要重新组装这些套娃，既不知道套娃的数量，也不知道每套娃娃中娃娃的数量。你只知道每套完整的套娃由大小从 $1$ 到某个数字 $m$ 的连续大小的娃娃组成，而这个数字 $m$ 在不同的套娃中可能有所不同。

在重新组装套娃时，你必须遵循以下规则：
- 你只能将一个娃娃或一个嵌套的娃娃组放入一个更大的娃娃中。
- 你只能合并两个在行中相邻的娃娃组。
- 一旦一个娃娃成为一个组的成员，它不能被转移到另一个组或永久地从组中分离。它只能在合并两个组时暂时分离。

你的时间非常宝贵，你希望尽快完成这个重新组装过程。这个任务中唯一耗时的部分是打开和随后关闭一个娃娃，因此你希望尽量减少这样的操作次数。例如，当将组 $[1, 2, 6]$ 与组 $[4]$ 合并时，最少需要进行两次开关操作，因为你必须打开大小为 $6$ 和 $4$ 的娃娃。而当将组 $[1, 2, 5]$ 与组 $[3, 4]$ 合并时，需要进行三次开关操作。

编写一个程序计算重新组装所有拆散的套娃所需的最少开关次数。

## 样例 #1

### 输入

```
7
1 2 1 2 4 3 3```

### 输出

```
Impossible```

## 样例 #2

### 输入

```
7
1 2 3 2 4 1 3
```

### 输出

```
7```

# 题解

## 作者：mushezi (赞：2)

考虑 $f(l, r)$ 表示  $[l, r]$ 的最小花费。

然后因为不止一组套娃所以再设  $g(i)$ 表示前  $i$  个套娃拼成的最小花费。

考虑如何把两个区间拼起来，我们发现合并两组套娃的代价为它们大于对方最小套娃的套娃个数数量。

所以我们需要预处理一些东西。

 $minv[l][r]$  和  $maxv[l][r]$  就是区间最大/小值。

 $maxpos[l][r]$  表示区间最大值的位置。

 $sum[i][x]$  相当于二维前缀和，表示从 i 位置开始的小于等于 x 的数量。

```cpp
void Init(){
    memset(g, 0x3f, sizeof(g));
    memset(f, 0x3f, sizeof(f));
    g[0] = 0;

    for(int i = 1; i <= n + 1; i++){
        f[i][i] = 0;
        minv[i][i] = arr[i];
        maxv[i][i] = arr[i];
        maxpos[i][i] = temp[i];
        for(int j = i + 1; j <= n; j++){
            minv[i][j] = min(minv[i][j - 1], arr[j]);
            maxv[i][j] = max(maxv[i][j - 1], arr[j]);
            maxpos[i][j] = max(maxpos[i][j], temp[j]);
        }
        for(int j = 1; j < N; j++){
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
}
```
然后我们就可以实现  $cost(i, k, j)$ 表示 $[l, r]$  这个区间，中间点为  $k$  然后拼在一起的花费。

```cpp
int getsum(int a, int b, int c, int d){
    return (sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1]);
}

int cost(int i, int k, int j){
    return (getsum(i, minv[k + 1][j], k, N - 1) + getsum(k + 1, minv[i][k], j, N - 1));
}
```
转移方程很显然，然后注意判断区间合不合法即可。

全部代码如下。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int M = 0x3f3f3f3f;

int n;
int sum[N][N], minv[N][N], maxv[N][N], maxpos[N][N];
int temp[N], l1[N], arr[N];
int pos[N], top;
int f[N][N], g[N];

// f[l, r] 表示 [l, r] 区间拼套娃组的最小花费
// g[p] 表示前 p 个套娃已经装好的最小花费

void Init(){
    memset(g, 0x3f, sizeof(g));
    memset(f, 0x3f, sizeof(f));
    g[0] = 0;

    for(int i = 1; i <= n + 1; i++){
        f[i][i] = 0;
        minv[i][i] = arr[i];
        maxv[i][i] = arr[i];
        maxpos[i][i] = temp[i];
        for(int j = i + 1; j <= n; j++){
            minv[i][j] = min(minv[i][j - 1], arr[j]);
            maxv[i][j] = max(maxv[i][j - 1], arr[j]);
            maxpos[i][j] = max(maxpos[i][j], temp[j]);
        }
        for(int j = 1; j < N; j++){
            sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
}

int getsum(int a, int b, int c, int d){
    return (sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1]);
}

int cost(int i, int k, int j){
    return (getsum(i, minv[k + 1][j], k, N - 1) + getsum(k + 1, minv[i][k], j, N - 1));
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++){
        int x;
        cin >> x;

        sum[i][x]++;
        arr[i] = x;
        temp[i] = l1[x];
        l1[x] = i;
    }

    Init();

    for(int len = 1; len <= n; len++){
        for(int i = 1; i + len - 1 <= n; i++){
            int j = i + len - 1;

            if(maxpos[i][j] >= i) continue;

            for(int k = i; k < j; k++){
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j] + cost(i, k, j));
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= i; j++){
            // 符合条件的才能接上去
            if(maxpos[j][i] < j && minv[j][i] == 1 && maxv[j][i] == i - j + 1){
                g[i] = min(g[i], g[j - 1] + f[j][i]);
            }
        }
    }

    if(g[n] != M) cout << g[n];
    else cout << "Impossible";

    return 0;
}
```

---

