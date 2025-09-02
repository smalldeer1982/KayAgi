# 题目信息

# [USACO19JAN] Redistricting P

## 题目背景

USACO 19 年一月月赛铂金组第一题。

## 题目描述

奶牛们的特大城市，牛都，要进行重新分区了！——这总是一个在居住在这里的两大主要种族（荷斯坦牛和更赛牛）之间富有争议的政治事件，因为两大种族都想要在牛都政府中保持足够的影响力。

牛都的大都市圈由一列 $n$ 块牧草地组成，每块里有一头奶牛，均为荷斯坦牛 (Holstein) 和更赛牛 (Guernsey) 之一。

牛都政府想要将大都市圈划分为若干个连续的区，使得每个区至少包含一块牧草地且至多包含 $k$ 块牧草地，并且每块牧草地恰好属于一个区。由于政府当前由荷斯坦牛控制，她们想要找到一种分区方式能够最小化更赛牛较多或者均势的区的数量（如果更赛牛的数量与荷斯坦牛的数量相等那么这个区就是均势的）。

有一个关心政治的更赛牛团体想要知道政府的分区计划可能会对她们造成多少损害。帮助她们求出最坏情况，也就是更赛牛较多或是均势的区的最小可能的数量。

## 说明/提示

### 样例解释

一种可能的划分方式是 $[1],~[2, 3],~[4, 5],~[6, 7]$。第二、四个区是均势的区，第三个区是更赛牛优势的区。

### 数据范围

对于 $100\%$ 的数据，保证 $1 \leq k \leq n \leq 3 \times 10^5$，$s$ 的长度为 $n$，且只含字符 `H` 和 `G`。

## 样例 #1

### 输入

```
7 2
HGHGGHG```

### 输出

```
3```

# AI分析结果

### 综合分析与结论
这些题解主要围绕动态规划（DP）展开，通过不同的数据结构进行优化以降低时间复杂度。大部分题解先推出朴素的 DP 方程，时间复杂度为 $O(nk)$，然后采用单调队列、优先队列、线段树等数据结构进行优化。其中，单调队列优化的时间复杂度可达 $O(n)$，优先队列和线段树优化的时间复杂度一般为 $O(n \log k)$ 或 $O(n \log n)$。

### 所选题解
- 梧桐灯（4星）
  - 关键亮点：思路清晰，使用单调队列优化 DP，时间复杂度为 $O(n)$，代码简洁且有详细注释。
  - 个人心得：提到单调队列好写、好记、好快，还调侃卡常和女装减小常数。
- lam_dyr（4星）
  - 关键亮点：详细阐述了单调队列优化的思路和步骤，代码规范，时间复杂度为 $O(n)$。
  - 个人心得：指出本题是数据结构优化 DP 的好题，强调单调队列在本题中的关键作用。
- ZeroF（4星）
  - 关键亮点：先给出朴素 DP 方程，再详细说明单调队列优化的过程，思路连贯，代码实现清晰。
  - 个人心得：明确指出朴素 DP 会 TLE，需要从状态转移处下手进行优化。

### 重点代码
#### 梧桐灯的题解
```cpp
#pragma GCC optimize ("Ofast")
#include <cstdio>
using namespace std;

inline void read (int& s) {
    s = 0;
    static char c = getchar ();
    while (c < '0' || c > '9') c = getchar ();
    while (c >= '0' && c <= '9') s = (s << 3) + (s << 1) + (c & 15), c = getchar ();
    return ;
}

const int N = 300007;
int n, k, f[N], sum[N];
int Q[N], H, T;

int main () {
    read (n), read (k);
    register int i; for (i = 1; i <= n; ++i) sum[i] = sum[i - 1] + (getchar () == 'H' ? 1 : -1);
    Q[T++] = 0; 
    for (i = 1; i <= n; ++i) {
        while (H < T && i - Q[H] > k) ++H; 
        f[i] = f[Q[H]] + (sum[i] - sum[Q[H]] <= 0);
        while (H < T) {
            if (f[i] < f[Q[T - 1]] || (f[i] == f[Q[T - 1]] && sum[i] < sum[Q[T - 1]])) --T;
            else break;
        } 
        Q[T++] = i;
    }
    printf ("%d\n", f[n]);
    return 0;
}
```
核心实现思想：先计算前缀和 `sum`，然后使用单调队列 `Q` 维护可能的转移点。在遍历过程中，先移除超出范围的队首元素，再根据队首元素更新当前状态 `f[i]`，最后将当前元素插入队列并维护队列的单调性。

#### lam_dyr 的题解
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=300005;
const int INF=1e9;
int sum[N],dp[N];
int q[N];
int head,tail;
int n,k;
string s;
int main() {
    cin>>n>>k;
    cin>>s;
    for(int i=1;i<=n;++i) 
        sum[i]=sum[i-1]+(s[i-1]=='H'?1:-1);
    for(int i=0;i<= n;++i) 
        dp[i]=INF;
    dp[0]=0;
    q[tail++]=0;
    for(int i=1;i<=n;++i){
        while(head<tail && q[head]<i-k){
            head++;
        }
        dp[i]=dp[q[head]]+(sum[i]-sum[q[head]]<=0);
        while(head<tail){
            int j=q[tail-1];
            if (dp[j]>dp[i] || (dp[j]==dp[i] && sum[j]>=sum[i])) 
                tail--;
            else 
                break;
        }
        q[tail++] = i;
    }
    cout<<dp[n];
    return 0;
}
```
核心实现思想：同样先计算前缀和 `sum`，并初始化 `dp` 数组。使用单调队列 `q` 维护转移点，在遍历过程中，移除超出范围的队首元素，更新 `dp[i]`，再从队尾移除不优的元素，最后将当前元素插入队列。

#### ZeroF 的题解
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[3*114514];
int cnt[3*114514],dp[3*114514];
deque<int>q;
int main(){
    int n,k;
    cin>>n>>k;
    scanf("%s",s+1);
    q.push_back(0);
    for(int i=1;i<=n;i++){
        if(s[i]=='G')cnt[i]=cnt[i-1]+1;
        else cnt[i]=cnt[i-1]-1;
        while(!q.empty()&&i-q.front()>k)q.pop_front();
        int j=q.front();
        if(cnt[i]-cnt[j]>=0)dp[i]=dp[j]+1;
        else dp[i]=dp[j];
        while(!q.empty()&&(dp[q.back()]>dp[i]||(dp[q.back()]==dp[i]&&cnt[i]-cnt[q.back()]>=0)))q.pop_back();
        q.push_back(i);
    }
    cout<<dp[n]<<endl;
    return 0;
}
```
核心实现思想：计算前缀和 `cnt`，使用双端队列 `q` 维护转移点。在遍历过程中，移除超出范围的队首元素，根据队首元素更新 `dp[i]`，再从队尾移除不优的元素，最后将当前元素插入队列。

### 最优关键思路或技巧
- **动态规划**：定义状态表示前 $i$ 个元素的最优解，通过枚举转移点得到朴素的 DP 方程。
- **前缀和**：用于快速计算任意区间内两种牛的数量差，判断该区间是否为更赛牛较多或均势区。
- **单调队列优化**：在满足转移条件的区间内，维护一个单调队列，队列中的元素按一定规则排序，保证队首元素为最优转移点，从而将时间复杂度从 $O(nk)$ 降低到 $O(n)$。

### 可拓展之处
同类型题：涉及区间划分和求最优解的动态规划问题，且转移区间长度有限制。
类似算法套路：对于一些动态规划问题，当转移区间固定时，可以考虑使用单调队列优化；对于需要维护区间最值的问题，可以使用线段树、优先队列等数据结构进行优化。

### 推荐题目
- P1886 滑动窗口 /【模板】单调队列
- P1714 切蛋糕
- P2627 [USACO11OPEN]Mowing the Lawn G

### 个人心得总结
- 梧桐灯：强调单调队列的优势，如好写、好记、好快，还提到卡常技巧。
- lam_dyr：指出本题是数据结构优化 DP 的好题，突出单调队列在本题中的关键作用。
- ZeroF：明确朴素 DP 会超时，需要从状态转移处下手进行优化。

---
处理用时：53.40秒