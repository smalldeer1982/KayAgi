# Duff in Beach

## 题目描述

### 题目翻译

给出一个长度为$n$的序列$a_0,a_1,...,a_{n-1}$，通过它构造出一个长度为$l$的序列$b_0,b_1,...,b_{l-1}$满足$b_i = a_{i \mod n}$。

现求满足如下条件的$b$的子序列$b_{q_0} , b_{q_1},...,b_{q_{x-1}}$的数量：

1、$1 \leq x \leq k$

2、$\forall i \in [0,x-2] , \lfloor\frac{q_i}{n} \rfloor = \lfloor \frac{q_{i+1}}{n} \rfloor -1$

3、$\forall i \in [0,x-2] , b_{q_i} \leq b_{q_{i+1}}$

## 样例 #1

### 输入

```
3 5 3
5 9 1
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 10 3
1 2 3 4 5
```

### 输出

```
25
```

# 题解

## 作者：Wisdom (赞：0)

$b$ 数组可以看成很多段 $a$ 数组组成。从 $b$ 数组中选择的子序列需要满足的第二条件的意思是选择的子序列相邻两个元素在相邻的 $a$ 数组中。  
根据 $nk \le 10^6$ 这个条件，我们很容易想到可以设计一个状态数为 $10^6$ 的动态规划算法来解决这道题目，但是 $b$ 数组的长度最大有 $10^{18}$，这就需要一些转换了。对于任意一个满足条件的子序列方案，我们都可以把他平移成第一个元素在第一个 $a$ 数组中的方案。这样我们只需要关心前 $nk$ 个元素组成的方案，后面的元素构成的方案都可以由这些方案往后平移形成。  
状态定义：$dp_{i,j}$ 表示以 $b_{(i-1)\times n+j}$ 为结尾构成长度为 $i$ 的子序列的方案数。  
初始状态：$dp_{1,j} \gets 1$  
状态转移：$\begin{aligned}dp_{i,j} \gets \sum_{b_{(i-2)\times n+k} \le b_{(i-1)\times n+j}}{dp_{i-1,k}}\end{aligned}$  
可以看到状态转移是分层的，我们可以对 $a$ 数组进行排序，这样转移时当前层的某个状态的值就等于上一层的某个前缀和。

代码：  
```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
#define y1 y11
#define fi first 
#define se second
#define pi acos(-1)
#define LL long long
#define ULL unsigned LL
#define pb push_back
#define pll pair<LL, LL>
#define pii pair<int, int>
#define tiii tuple<int, int, int>
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

const int N = 1e6 + 100;
const int MOD = 1e9 + 7;
int n, k, a[N], b[N], id[N], le[N];
LL l;
int main() {
    scanf("%d %lld %d", &n, &l, &k);
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]), b[i] = a[i], id[i] = i;
    sort(b, b+n);
    sort(id, id+n, [&](int x, int y){
        return a[x] < a[y];
    });
    vector<vector<int>> dp(k+1, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        le[id[i]] = id[upper_bound(b, b+n, b[i]) - b - 1];
    }
    LL ans = 0;
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < n; ++j) {
            if(i == 1) dp[i][j] = 1;
            else {
                dp[i][j] = dp[i-1][le[j]];
            }
            if(l >= n*1LL*(i-1)+j+1)
                ans = (ans + (1+(l-n*1LL*(i-1)-j-1)/n) % MOD * 1LL * dp[i][j] % MOD) % MOD;
        }
        for (int j = 1; j < n; ++j) dp[i][id[j]] = (dp[i][id[j]] + dp[i][id[j-1]]) % MOD;
        
    }
    printf("%lld\n", ans);
    return 0;
}
```


---

