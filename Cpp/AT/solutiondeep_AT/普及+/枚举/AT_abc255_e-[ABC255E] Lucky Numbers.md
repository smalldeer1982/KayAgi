# 题目信息

# [ABC255E] Lucky Numbers

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc255/tasks/abc255_e

長さ $ N-1 $ の整数列 $ S\ =\ (S_1,\ S_2,\ \ldots,\ S_{N-1}) $ および、「ラッキーナンバー」として $ M $ 個の相異なる整数 $ X_1,\ X_2,\ \ldots,\ X_M $ が与えられます。

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \ldots,\ A_N) $ であって、次の条件を満たすものを「良い数列」と呼びます。

> すべての $ i\ =\ 1,\ 2,\ \ldots,\ N-1 $ について、$ A_i\ +\ A_{i+1}\ =\ S_i $ が成り立つ。

良い数列 $ A $ を $ 1 $ つ選ぶときの、$ A $ の要素のうちラッキーナンバーであるものの個数（すなわち、$ A_i\ \in\ \lbrace\ X_1,\ X_2,\ \ldots,\ X_M\ \rbrace $ となる $ 1 $ 以上 $ N $ 以下の整数 $ i $ の個数）としてあり得る最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10 $
- $ -10^9\ \leq\ S_i\ \leq\ 10^9 $
- $ -10^9\ \leq\ X_i\ \leq\ 10^9 $
- $ X_1\ \lt\ X_2\ \lt\ \cdots\ \lt\ X_M $
- 入力はすべて整数

### Sample Explanation 1

良い数列 $ A $ として $ A\ =\ (3,\ -1,\ 4,\ -1,\ 5,\ -9,\ 2,\ -6,\ 5) $ を選ぶと、$ A $ の要素のうちラッキーナンバーであるものは $ A_2,\ A_4,\ A_5,\ A_9 $ の $ 4 $ 個となり、これが考えられる中で最大です。

## 样例 #1

### 输入

```
9 2

2 3 3 4 -4 -7 -4 -1

-1 5```

### 输出

```
4```

## 样例 #2

### 输入

```
20 10

-183260318 206417795 409343217 238245886 138964265 -415224774 -499400499 -313180261 283784093 498751662 668946791 965735441 382033304 177367159 31017484 27914238 757966050 878978971 73210901

-470019195 -379631053 -287722161 -231146414 -84796739 328710269 355719851 416979387 431167199 498905398```

### 输出

```
8```

# AI分析结果

### 题目翻译
给定长度为 $N - 1$ 的整数序列 $S = (S_1, S_2, \ldots, S_{N - 1})$ 以及 $M$ 个不同的整数 $X_1, X_2, \ldots, X_M$ 作为 “幸运数”。

长度为 $N$ 的整数序列 $A = (A_1, A_2, \ldots, A_N)$ 若满足以下条件，则被称为 “好序列”：

对于所有的 $i = 1, 2, \ldots, N - 1$，都有 $A_i + A_{i + 1} = S_i$ 成立。

当选择一个好序列 $A$ 时，求 $A$ 的元素中为幸运数的个数（即满足 $A_i \in \{X_1, X_2, \ldots, X_M\}$ 的 $1$ 到 $N$ 之间的整数 $i$ 的个数）的最大值。

### 综合分析与结论
这些题解的核心思路都是基于确定序列 $A$ 中的一个数就能确定整个序列 $A$ 这一特性。通过枚举 $A_i = X_j$，计算出对应的 $A_1$，利用哈希表（如 `map`）统计 $A_1$ 的出现次数，出现次数的最大值即为答案。

- **算法要点**：
    1. 枚举每个可能的幸运数 $X_j$ 作为序列 $A$ 中的某一项 $A_i$。
    2. 推导出由 $A_i$ 计算 $A_1$ 的公式。
    3. 预处理公式中与 $S$ 序列相关的部分，实现 $O(1)$ 计算 $A_1$。
    4. 使用哈希表统计 $A_1$ 的出现次数。
    5. 找出哈希表中出现次数的最大值。
- **解决难点**：
    - 原暴力枚举生成序列 $A$ 并统计幸运数个数的方法时间复杂度为 $O(N^2M)$，无法通过本题。题解通过推导 $A_i$ 与 $A_1$ 的关系，将问题转化为统计 $A_1$ 的出现次数，结合预处理优化，将时间复杂度降低到 $O(NM \log(NM))$。

### 所选题解
- **HyB_Capricornus（5星）**
    - **关键亮点**：思路清晰，详细推导了由 $A_i$ 计算 $A_1$ 的公式，并对预处理部分进行了详细说明，代码注释清晰。
    - **核心代码**：
```c++
#include <iostream>
#include <map>
#define MAXN 100010
#define MAXM 15
#define ll long long
using namespace std;
ll n,m;
ll s[MAXN],luky[MAXM];
ll a[MAXN],b[MAXN];
map<ll,ll> mp;
ll k;
int main(void) {
    cin>>n>>m;
    for (ll i=1;i<n;i++)
        cin>>s[i];
    for (ll i=1;i<=m;i++)
        cin>>luky[i];
    for (ll i=2;i<=n;i++)
        b[i]=s[i-1]-b[i-1]; //递推公式，上文已做推导
    for (ll i=1;i<=n;i++)
        for (ll j=1;j<=m;j++)
            mp[(b[i]-luky[j])*(i%2?-1:1)]++; //luky[i] 对应文中 a[n]
    for (map<ll,ll>::iterator it=mp.begin();it!=mp.end();it++)
        k=max(k,it->second); //查找最多相同的 a[1]
    cout<<k;
    return 0;
}
```
- **Ryan_Adam（4星）**
    - **关键亮点**：思路简洁明了，代码实现规范，对公式的推导和复杂度分析较为清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int s[N],x[N],ss[N];
int n,m;
vector<vector<int> > v;
map<int,int> mp;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n-1;i++)
        cin>>s[i];
    for(int i=1;i<=m;i++)
        cin>>x[i];
    ss[1]=s[1];
    for(int i=2;i<=n;i++)
        ss[i]=ss[i-1]+(i&1?1:-1)*s[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            mp[ss[i-1]+(i&1?1:-1)*x[j]]++;
    int ans=-1;
    for(auto it:mp)
        ans=max(ans,it.second);
    cout<<ans<<endl;
    return 0;
}
```
- **__YSC__（4星）**
    - **关键亮点**：思路清晰，对公式的推导和优化过程有详细说明，代码简洁易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

const long long MAXN = 100001;

long long n, m, s[MAXN], x[MAXN], sum[MAXN], ans;
map<long long, long long> mp;

int main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(long long i = 1; i < n; ++i) {
    cin >> s[i];
  }
  for(long long i = 1; i <= m; ++i) {
    cin >> x[i];
  }
  for(long long i = 1; i < n; ++i) {
    sum[i] = sum[i - 1] + (i % 2 ? 1ll : -1ll) * s[i];
  }
  for(long long i = 1; i <= n; ++i) {
    for(long long j = 1; j <= m; ++j) {
      mp[sum[i - 1] + (i % 2 ? 1ll : -1ll) * x[j]]++;
    }
  }
  for(pair<long long, long long> p : mp) {
    ans = max(ans, p.second);
  }
  cout << ans;
  return 0;
}
```

### 最优关键思路或技巧
- **思维方式**：利用确定序列中的一个数就能确定整个序列的特性，将问题转化为统计某个固定位置（如 $A_1$）的出现次数。
- **算法优化**：通过预处理 $S$ 序列相关部分，实现 $O(1)$ 计算 $A_1$，降低时间复杂度。
- **数据结构**：使用哈希表（如 `map`）统计 $A_1$ 的出现次数，方便查找最大值。

### 可拓展之处
同类型题目可能会有不同的序列约束条件或统计要求，但核心思路都是通过确定部分元素来推导整个序列，再根据特定条件进行统计。类似算法套路包括利用递推关系推导序列元素，通过预处理优化计算过程，使用合适的数据结构进行统计和查找。

### 洛谷相似题目推荐
1. [P5847 【模板】线性筛素数](https://www.luogu.com.cn/problem/P5847)
2. [P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
3. [P1064 [NOIP2006 提高组] 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

### 个人心得摘录与总结
- **HyB_Capricornus**：提到修改汉字与数学公式空格错误并重新提交审核，强调了细节的重要性。总结为在编写题解时要注意格式规范，确保内容准确清晰。
- **xuan_gong_dong**：一开始以为 $n$ 和 $m$ 同阶，觉得题目很难，后来发现 $m \le 10$ 才找到思路。总结为在解题时要仔细分析数据范围，数据范围往往是解题的关键线索。 

---
处理用时：47.80秒