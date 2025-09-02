# 题目信息

# Integers Have Friends

## 题目描述

British mathematician John Littlewood once said about Indian mathematician Srinivasa Ramanujan that "every positive integer was one of his personal friends."

It turns out that positive integers can also be friends with each other! You are given an array $ a $ of distinct positive integers.

Define a subarray $ a_i, a_{i+1}, \ldots, a_j $ to be a friend group if and only if there exists an integer $ m \ge 2 $ such that $ a_i \bmod m = a_{i+1} \bmod m = \ldots = a_j \bmod m $ , where $ x \bmod y $ denotes the remainder when $ x $ is divided by $ y $ .

Your friend Gregor wants to know the size of the largest friend group in $ a $ .

## 说明/提示

In the first test case, the array is $ [1,5,2,4,6] $ . The largest friend group is $ [2,4,6] $ , since all those numbers are congruent to $ 0 $ modulo $ 2 $ , so $ m=2 $ .

In the second test case, the array is $ [8,2,5,10] $ . The largest friend group is $ [8,2,5] $ , since all those numbers are congruent to $ 2 $ modulo $ 3 $ , so $ m=3 $ .

In the third case, the largest friend group is $ [1000,2000] $ . There are clearly many possible values of $ m $ that work.

## 样例 #1

### 输入

```
4
5
1 5 2 4 6
4
8 2 5 10
2
1000 2000
8
465 55 3 54 234 12 45 78```

### 输出

```
3
3
2
6```

# AI分析结果

### 题目中文重写
# 整数也有朋友

## 题目描述
英国数学家约翰·利特尔伍德（John Littlewood）曾经这样评价印度数学家斯里尼瓦瑟·拉马努金（Srinivasa Ramanujan）：“每一个正整数都是他的挚友。”

事实证明，正整数之间也能成为朋友！给定一个由不同正整数组成的数组 $a$。

若存在一个整数 $m \ge 2$，使得 $a_i \bmod m = a_{i + 1} \bmod m = \ldots = a_j \bmod m$（其中 $x \bmod y$ 表示 $x$ 除以 $y$ 的余数），则称子数组 $a_i, a_{i + 1}, \ldots, a_j$ 为一个朋友组。

你的朋友格雷戈尔（Gregor）想知道数组 $a$ 中最大朋友组的大小。

## 说明/提示
在第一个测试用例中，数组为 $[1, 5, 2, 4, 6]$。最大的朋友组是 $[2, 4, 6]$，因为所有这些数对 $2$ 取模的余数都为 $0$，所以 $m = 2$。

在第二个测试用例中，数组为 $[8, 2, 5, 10]$。最大的朋友组是 $[8, 2, 5]$，因为所有这些数对 $3$ 取模的余数都为 $2$，所以 $m = 3$。

在第三个测试用例中，最大的朋友组是 $[1000, 2000]$。显然有许多可能的 $m$ 值都满足条件。

## 样例 #1
### 输入
```
4
5
1 5 2 4 6
4
8 2 5 10
2
1000 2000
8
465 55 3 54 234 12 45 78
```

### 输出
```
3
3
2
6
```

### 算法分类
差分

### 综合分析与结论
这些题解的核心思路都是将原问题转化为差分数组的问题。由于若 $a_i \equiv a_{i + 1} \pmod{m}$，则 $m$ 是 $|a_{i + 1} - a_i|$ 的因数，所以原问题可转化为在差分数组中找到最长的子区间，使得该区间的 $\gcd$ 大于 $1$。

各题解的主要区别在于实现方法，主要有双指针、二分查找结合 ST 表或线段树来维护区间 $\gcd$ 等。双指针法通过枚举右端点并动态调整左端点来找到最长区间；二分法通过二分答案区间长度，再枚举左端点判断是否存在满足条件的区间。

### 所选题解
- **作者：Prean (赞：19)，4星**
    - **关键亮点**：使用双指针结合两个栈维护区间，复杂度为 $O(n\log V)$，代码实现较为巧妙。
    - **个人心得**：提到在日报上看到该题，且发现 NOIP 模拟赛考过相关技巧。
- **作者：HoshizoraZ (赞：18)，4星**
    - **关键亮点**：思路清晰，详细说明了转化过程和易错点，使用 ST 表 + 二分/双指针求解。
    - **个人心得**：指出做过相关题目并熟悉思路的话能迅速做完本题。
- **作者：rouxQ (赞：7)，4星**
    - **关键亮点**：对问题的分析和转化过程讲解详细，使用二分答案结合 ST 表判断区间是否可行。
    - **个人心得**：提到看上去时间复杂度是 $O(N\log N\log \text{值域})$，但 cf 官方题解貌似给出了复杂度更低的证明。

### 重点代码
#### Prean 的代码
```cpp
#include<cstdio>
typedef unsigned ui;
typedef unsigned long long ull;
const ui M=2e5+5;
ui T,n;ull a[M],f[M];
inline ull gcd(const ull&a,const ull&b){
    return b?gcd(b,a%b):a;
}
signed main(){
    ui i,j,l,mid,ans;scanf("%u",&T);
    while(T--){
        scanf("%u",&n);l=mid=1;ans=0;
        for(i=1;i<=n;++i)scanf("%llu",a+i),a[i-1]=a[i-1]>a[i]?a[i-1]-a[i]:a[i]-a[i-1];
        for(i=1;i<n;++i){
            f[i]=i==1||i-1==mid?a[i]:gcd(f[i-1],a[i]);
            while(l<=mid&&gcd(f[l],f[i])==1)++l;
            if(l>mid){
                f[i]=a[mid=i];
                for(j=i-1;j>=l;--j)f[j]=gcd(a[j],f[j+1]);
                while(l<=i&&f[l]==1)++l;
            }
            if(i-l+1>ans)ans=i-l+1;
        }
        printf("%u\n",++ans);
    }
}
```
**核心实现思想**：先计算差分数组，然后使用双指针枚举右端点 $i$，通过栈 $f$ 维护区间 $\gcd$，动态调整左端点 $l$ 以保证区间 $\gcd$ 大于 $1$，当 $l > mid$ 时重构栈。

#### HoshizoraZ 的代码
```cpp
#include <bits/stdc++.h>
#define INF 1e9
#define eps 1e-6
typedef long long ll;
using namespace std;

int t, n, ans;
ll a[200010], sub[200010], st[200010][20];

ll gcd(ll x, ll y){
    if(!y) return x;
    return gcd(y, x % y);
}
 
ll query(int i, int j){
    int k = log2(j - i + 1);
    return gcd(st[i][k], st[j - (1 << k) + 1][k]);
}

inline int max(int a, int b){
    return a > b ? a : b;
}

int main(){
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%lld", &a[i]);
        if(n == 1){
            puts("1");
            continue;
        }
        for(int i = 1; i < n; i++){
            sub[i] = a[i] - a[i + 1];
            if(sub[i] < 0) sub[i] = -sub[i];
        }
        n--;
        for(int i = 1; i <= n; i++)
            st[i][0] = sub[i];
        for(int j = 1; (1 << j) <= n; j++) 
            for(int i = 1; i + (1 << j) - 1 <= n; i++)
                st[i][j] = gcd(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        ans = 0;
        for(int i = 1, l, r; i <= n; i++){
            l = i, r = n;
            while(l < r){
                int mid = (l + r + 1) >> 1;
                if(query(i, mid) == 1) r = mid - 1;
                else l = mid;
            }
            if(sub[i] != 1) ans = max(ans, l - i + 1);
        }
        printf("%d\n", ans + 1);
    }
    return 0;
}
```
**核心实现思想**：先计算差分数组，然后使用 ST 表预处理区间 $\gcd$，枚举右端点 $i$，二分查找满足条件的最右左端点 $l$，更新答案。

#### rouxQ 的代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 5, LogN = 19;
ll st[20][N], Log[N], a[N];int n, m;
ll gcd(ll x, ll y){return y == 0 ? x : gcd(y, x % y);}
bool work(int len){
    for (int i = 1; i <= m - len + 1; i++){
        int l = i, r = i + len - 1;
        int s = Log[len];
        if (gcd(st[s][l], st[s][r - (1 << s) + 1]) > 1)return 1;
    }
    return 0;
}
int main (){
    int T;
    ios::sync_with_stdio(false);
    cin >> T;
    for (int i = 2; i <= 2e5; i++)
        Log[i] = Log[i / 2] + 1;
    while(T--){
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        if (n == 2 && abs(a[1] - a[2]) == 1){
            cout << 1 << endl;
            continue;
        }
        m = n - 1;
        for (int i = 1; i < n; i++) 
            st[0][i] = abs(a[i] - a[i + 1]);
        st[0][n] = 1;
        for (int i = 1; i <= LogN; i++)
            for (int j = 1; j + (1 << i) - 1 <= m; j++)
                st[i][j] = gcd(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        int l = 1, r = m, mid;
        while(l <= r){
            mid = l + r >> 1;
            if (work(mid))l = mid + 1;
            else r = mid - 1;
        }
        cout << l << endl;
    }
    return 0;
}
```
**核心实现思想**：先计算差分数组，使用 ST 表预处理区间 $\gcd$，二分答案区间长度，通过 `work` 函数判断是否存在满足条件的区间。

### 最优关键思路或技巧
- **差分转化**：将同余问题转化为差分数组的 $\gcd$ 问题，简化了问题的求解。
- **ST 表或线段树维护区间 $\gcd$**：可以在 $O(1)$ 或 $O(\log n)$ 的时间复杂度内查询区间 $\gcd$，提高了算法效率。
- **双指针或二分查找**：通过双指针动态调整区间或二分答案区间长度，找到最长的满足条件的区间。

### 拓展思路
同类型题目通常涉及同余问题或区间性质问题，可采用差分转化、维护区间信息（如 $\gcd$、和等）的方法求解。类似算法套路包括：
- 对于同余问题，可考虑作差转化为整除问题。
- 对于区间查询问题，可使用 ST 表、线段树等数据结构维护区间信息。

### 推荐题目
- [P1816 忠诚](https://www.luogu.com.cn/problem/P1816)：ST 表的基础应用，用于查询区间最小值。
- [P3865 【模板】ST 表](https://www.luogu.com.cn/problem/P3865)：ST 表的模板题，可加深对 ST 表的理解。
- [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)：涉及数论和区间 $\gcd$ 的问题，与本题思路有一定关联。

---
处理用时：81.84秒