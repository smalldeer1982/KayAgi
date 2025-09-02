# 题目信息

# Messages

## 题目描述

Monocarp 是 $n$ 个学生的导师。现在有很多条消息，Monocarp 希望第 $i$ 个学生阅读编号为 $m_i$ 的消息。他需要把一些消息置顶，因为学生只会阅读置顶的消息。

学生 $i$ 有一个属性 $k_i$。如果你置顶了 $t$ 条消息，若 $t\le k_i$，该学生会阅读所有置顶消息；否则，该学生会从置顶的 $t$ 条消息中随机选 $k_i$ 条阅读。

你需要求出在使得第 $i$ 名学生阅读到第 $m_i$ 条消息的 $i$ 的数量的期望值最大时，你应该置顶哪些消息。如果有多个答案，输出任意一种。

## 样例 #1

### 输入

```
3
10 1
10 2
5 2```

### 输出

```
2
5 10```

## 样例 #2

### 输入

```
3
10 1
5 2
10 1```

### 输出

```
1
10```

## 样例 #3

### 输入

```
4
1 1
2 2
3 3
4 4```

### 输出

```
3
2 3 4```

## 样例 #4

### 输入

```
3
13 2
42 2
37 2```

### 输出

```
3
42 13 37```

# AI分析结果

### 题目分类
贪心、概率论

### 综合分析与结论
各题解核心思路相近，均是先分析出最优解中置顶消息数量 $t$ 的范围（由于 $k_i \leq 20$，$t$ 最大为 20），然后枚举 $t$，对于每个 $t$ 值，计算每条消息的贡献，选取贡献最大的 $t$ 条消息，最后比较不同 $t$ 值下的期望，取期望最大的方案。不同题解的主要差异在于实现细节和优化方式。

### 所选题解
- **DaiRuiChen007（5星）**
    - **关键亮点**：思路清晰，证明了最优解中 $t$ 的范围，代码可读性高，注释详细。
    - **核心实现思想**：使用桶记录每个 $m_i$ 对应的 $k_i$ 之和，枚举 $t$ 从 1 到 20，每次对桶按 $k_i$ 之和降序排序，选取前 $t$ 个，计算期望并更新答案。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+1;
int k[MAXN],m[MAXN];
struct BucketNode {
    int val,id;
    inline friend bool operator <(const BucketNode &x,const BucketNode &y) {
        return x.val>y.val;
    }
} b[MAXN];
inline BucketNode mp(int val,int id) {
    BucketNode ans;
    ans.val=val,ans.id=id;
    return ans;
}
struct DataNode {
    vector <int> vec; 
    double val; 
    inline void clear() {
        val=0;vec.clear();
    }
} ans,tmp; 
signed main() {
    int n;
    scanf("%d",&n);
    for(register int i=1;i<=n;++i) scanf("%d%d",&m[i],&k[i]);
    for(register int t=1;t<=20;++t) {
        for(register int i=0;i<MAXN;++i) b[i]=mp(0,i); 
        for(register int i=1;i<=n;++i) b[m[i]].val+=min(t,k[i]); 
        sort(b+1,b+MAXN+1); 
        tmp.clear();
        for(register int i=1;i<=t;++i) {
            tmp.val+=b[i].val;
            tmp.vec.push_back(b[i].id);
        }
        tmp.val/=t;
        if(tmp.val>ans.val) ans=tmp; 
    }
    printf("%d\n",ans.vec.size());
    for(register int i:ans.vec) printf("%d ",i);
    putchar('\n');
    return 0;
}
```
- **401rk8（4星）**
    - **关键亮点**：指出找出前 $t$ 大的数不需要 `sort`，使用 `nth_element` 优化，时间复杂度为 $O(20n)$。
    - **核心实现思想**：同样枚举 $t$，用桶统计每个数的贡献，使用 `nth_element` 选取前 $t$ 大的数。
    - **核心代码（思路示意，原代码为链接）**：
```cpp
// 伪代码，仅示意思路
for (int t = 1; t <= 20; ++t) {
    // 统计每个数的贡献
    vector<pair<int, int>> contributions; // 贡献和编号
    for (int i = 1; i <= n; ++i) {
        // 更新贡献
    }
    nth_element(contributions.begin(), contributions.begin() + t, contributions.end(), greater<pair<int, int>>());
    // 计算期望并更新答案
}
```
- **_RainCappuccino_（4星）**
    - **关键亮点**：思路简洁，对答案范围进行了贪心分析，代码实现清晰。
    - **核心实现思想**：枚举 $t$ 从 1 到 20，计算每条消息的代价，取前 $t$ 大的消息，更新期望最大的方案。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
const int N = 2e5 + 10;
int n;
vector<int> num[N];
int m[N], k[N];
pi sum[N];
signed main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> m[i] >> k[i];
        num[m[i]].push_back(k[i]);
    }
    double ans = 0;
    vector<int> res;
    for (int kk = 1; kk <= 20; kk ++) {
        for (int i = 1; i <= 2e5; i ++) {
            sum[i].first = 0, sum[i].second = i;
            for (auto x : num[i]) sum[i].first += min(kk, x);
        }
        sort(sum + 1, sum + 1 + 200000, greater<pi>());
        int cnt = 0;
        for (int i = 1; i <= kk; i ++) {
            cnt += sum[i].first;
        }
        double p = cnt / (kk * 1.0);
        if(p > ans) {
            ans = p;
            res.clear();
            for (int i = 1; i <= kk; i ++) {
                res.push_back(sum[i].second);
            }
        }
    }
    cout << res.size() << endl;
    for (auto x : res) cout << x << ' ';
    return 0;
}
```

### 关键思路与技巧
- **贪心思想**：在 $t$ 确定的情况下，选取 $k_i$ 之和最大的前 $t$ 个消息，使得期望最大。
- **范围分析**：通过分析 $k_i$ 的范围，得出最优解中 $t$ 的范围最大为 20，减少枚举量。
- **桶的使用**：使用桶记录每个 $m_i$ 对应的 $k_i$ 之和，方便统计和排序。

### 拓展思路
同类型题可能会改变学生的阅读规则或消息的限制条件，但核心思路可能还是通过贪心和枚举来求解最优方案。类似算法套路包括先分析问题的范围，减少不必要的计算，再通过枚举和贪心选取最优解。

### 推荐洛谷题目
- P1223 排队接水：贪心算法的经典题目，通过排序来优化总等待时间。
- P1090 合并果子：贪心算法，每次选取最小的两个果子合并。
- P2240 部分背包问题：贪心算法，根据单位价值排序选取物品。

---
处理用时：56.28秒