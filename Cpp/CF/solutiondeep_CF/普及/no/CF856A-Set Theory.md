# 题目信息

# Set Theory

## 题目描述

Masha and Grisha like studying sets of positive integers.

One day Grisha has written a set $ A $ containing $ n $ different integers $ a_{i} $ on a blackboard. Now he asks Masha to create a set $ B $ containing $ n $ different integers $ b_{j} $ such that all $ n^{2} $ integers that can be obtained by summing up $ a_{i} $ and $ b_{j} $ for all possible pairs of $ i $ and $ j $ are different.

Both Masha and Grisha don't like big numbers, so all numbers in $ A $ are from $ 1 $ to $ 10^{6} $ , and all numbers in $ B $ must also be in the same range.

Help Masha to create the set $ B $ that satisfies Grisha's requirement.

## 样例 #1

### 输入

```
3
3
1 10 100
1
1
2
2 4
```

### 输出

```
YES
1 2 3 
YES
1 
YES
1 2 
```

# AI分析结果



# Set Theory

## 题目描述

Masha 和 Grisha 喜欢研究正整数集合。

Grisha 在黑板上写了一个包含 $n$ 个不同整数 $a_i$ 的集合 $A$，要求 Masha 构造一个包含 $n$ 个不同整数 $b_j$ 的集合 $B$，使得所有由 $a_i + b_j$ 组成的 $n^2$ 个和都互不相同。所有数字必须在 $1$ 到 $10^6$ 范围内。

## 输入输出样例

### 样例输入
```
3
3
1 10 100
1
1
2
2 4
```

### 样例输出
```
YES
1 2 3 
YES
1 
YES
1 2 
```

---

**算法分类**：构造

---

## 题解分析与结论

### 题解对比

1. **暴力枚举法**（Bai_R_X、_Execution_ 等题解）
   - **关键思路**：从小到大枚举 $1 \sim 10^6$，检查候选数 $b$ 与所有 $a_i$ 的和是否已被标记。若未冲突，加入 $B$ 并标记所有新和。
   - **解决难点**：通过桶数组记录已存在的和，确保每次枚举的 $b$ 不会引入重复和。
   - **优化点**：找到 $n$ 个合法值后提前终止枚举，降低时间复杂度。

2. **差值转换法**（一叶知秋题解）
   - **关键思路**：将问题转换为确保 $B$ 的差值不与 $A$ 的差值相同。通过维护差值标记来构造 $B$。
   - **局限性**：实现复杂度较高且时间复杂度难以控制，未明确证明其正确性。

### 最优思路总结
暴力枚举法是最直接且正确性明确的解法。通过贪心策略选择最小的合法 $b$ 值，利用桶数组记录已生成的和，确保构造过程满足条件。

---

## 推荐题解代码

### 题解作者：Bai_R_X（评分：★★★★☆）
**关键亮点**：
- 清晰的初始化处理，确保多测试用例独立。
- 代码简洁，逻辑明确。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[105],b[105],cnt;
bool vis[2000005];

signed main() {
    cin>>T;
    while(T--) {
        memset(vis,0,sizeof(vis));
        cnt=0;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=1000000;i++) {
            bool f=0;
            for(int j=1;j<=n;j++)
                if(vis[a[j]+i]) {f=1; break;}
            if(f) continue;
            for(int j=1;j<=n;j++) vis[a[j]+i]=1;
            b[++cnt]=i;
            if(cnt==n) break;
        }
        if(cnt<n) cout<<"NO\n";
        else {
            cout<<"YES\n";
            for(int i=1;i<=n;i++) cout<<b[i]<<" \n"[i==n];
        }
    }
    return 0;
}
```

---

## 相似题目推荐

1. [CF1325D - Ehab the Xorcist](https://codeforces.com/problemset/problem/1325/D)（构造满足异或和与和的数组）
2. [CF1095F - Make It Connected](https://codeforces.com/problemset/problem/1095/F)（贪心构造最小生成树）
3. [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)（贪心策略的经典应用）

---
处理用时：158.62秒