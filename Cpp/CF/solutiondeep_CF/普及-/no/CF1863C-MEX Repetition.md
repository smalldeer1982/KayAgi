# 题目信息

# MEX Repetition

## 题目描述

You are given an array $ a_1,a_2,\ldots, a_n $ of pairwise distinct integers from $ 0 $ to $ n $ . Consider the following operation:

- consecutively for each $ i $ from $ 1 $ to $ n $ in this order, replace $ a_i $ with $ \operatorname{MEX}(a_1, a_2, \ldots, a_n) $ .

Here $ \operatorname{MEX} $ of a collection of integers $ c_1, c_2, \ldots, c_m $ is defined as the smallest non-negative integer $ x $ which does not occur in the collection $ c $ . For example, $ \operatorname{MEX}(0, 2, 2, 1, 4) = 3 $ and $ \operatorname{MEX}(1, 2) = 0 $ .

Print the array after applying $ k $ such operations.

## 说明/提示

In the first test case, here is the entire process:

1. On the first operation, the array changes from $ [1] $ to $ [0] $ , since $ \operatorname{MEX}(1) = 0 $ .
2. On the second operation, the array changes from $ [0] $ to $ [1] $ , since $ \operatorname{MEX}(0) = 1 $ .

Thus, the array becomes $ [1] $ after two operations.

In the second test case, the array changes as follows during one operation: $ [{\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}, 1, 3] \rightarrow [2, {\mkern3mu\underline{\mkern-3mu {\bf 1}\mkern-3mu}\mkern3mu}, 3] \rightarrow [2, 0, {\mkern3mu\underline{\mkern-3mu {\bf 3}\mkern-3mu}\mkern3mu}] \rightarrow [2, 0, 1] $ .

In the third test case, the array changes as follows during one operation: $ [{\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}, 2] \rightarrow [1, {\mkern3mu\underline{\mkern-3mu {\bf 2}\mkern-3mu}\mkern3mu}] \rightarrow [1, 0] $ . And during the second operation: $ [{\mkern3mu\underline{\mkern-3mu {\bf 1}\mkern-3mu}\mkern3mu}, 0] \rightarrow [2, {\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}] \rightarrow [2, 1] $ .

## 样例 #1

### 输入

```
5
1 2
1
3 1
0 1 3
2 2
0 2
5 5
1 2 3 4 5
10 100
5 3 0 4 2 1 6 9 10 8```

### 输出

```
1
2 0 1
2 1
2 3 4 5 0
7 5 3 0 4 2 1 6 9 10```

# AI分析结果

### 题目内容（中文重写）
# MEX 重复

## 题目描述
给定一个由 $0$ 到 $n$ 之间两两不同的整数组成的数组 $a_1, a_2, \ldots, a_n$。考虑以下操作：
- 按顺序从 $1$ 到 $n$ 对每个 $i$，将 $a_i$ 替换为 $\operatorname{MEX}(a_1, a_2, \ldots, a_n)$。

这里，整数集合 $c_1, c_2, \ldots, c_m$ 的 $\operatorname{MEX}$ 定义为不在该集合中出现的最小非负整数。例如，$\operatorname{MEX}(0, 2, 2, 1, 4) = 3$，$\operatorname{MEX}(1, 2) = 0$。

输出进行 $k$ 次这样的操作后的数组。

## 说明/提示
在第一个测试用例中，整个过程如下：
1. 在第一次操作中，数组从 $[1]$ 变为 $[0]$，因为 $\operatorname{MEX}(1) = 0$。
2. 在第二次操作中，数组从 $[0]$ 变为 $[1]$，因为 $\operatorname{MEX}(0) = 1$。

因此，经过两次操作后，数组变为 $[1]$。

在第二个测试用例中，数组在一次操作中的变化如下：$ [{\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}, 1, 3] \rightarrow [2, {\mkern3mu\underline{\mkern-3mu {\bf 1}\mkern-3mu}\mkern3mu}, 3] \rightarrow [2, 0, {\mkern3mu\underline{\mkern-3mu {\bf 3}\mkern-3mu}\mkern3mu}] \rightarrow [2, 0, 1] $。

在第三个测试用例中，数组在一次操作中的变化如下：$ [{\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}, 2] \rightarrow [1, {\mkern3mu\underline{\mkern-3mu {\bf 2}\mkern-3mu}\mkern3mu}] \rightarrow [1, 0] $。在第二次操作中：$ [{\mkern3mu\underline{\mkern-3mu {\bf 1}\mkern-3mu}\mkern3mu}, 0] \rightarrow [2, {\mkern3mu\underline{\mkern-3mu {\bf 0}\mkern-3mu}\mkern3mu}] \rightarrow [2, 1] $。

## 样例 #1
### 输入
```
5
1 2
1
3 1
0 1 3
2 2
0 2
5 5
1 2 3 4 5
10 100
5 3 0 4 2 1 6 9 10 8
```

### 输出
```
1
2 0 1
2 1
2 3 4 5 0
7 5 3 0 4 2 1 6 9 10
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过模拟操作找规律，发现对长度为 $n$ 的数组进行操作的循环节长度为 $n + 1$，从而将操作次数 $k$ 对 $n + 1$ 取模来减少计算量。各题解的主要步骤包括：
1. 输入数组并找出 $\operatorname{MEX}$ 值。
2. 计算 $k$ 对 $n + 1$ 取模的结果。
3. 根据规律计算并输出操作 $k$ 次后的数组。

不同题解在找规律的方式和代码实现细节上有所不同，但整体思路一致。

### 所选题解
- **作者：Aisaka_Taiga（4星）**
  - **关键亮点**：思路清晰，通过手模样例发现规律，代码简洁明了。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
#define N 1000100
using namespace std;
int t, n, m, a[N], ans[N], vis[N];
signed main()
{
    cin >> t;
    while(t --)
    {
        cin >> n >> m;
        m %= n + 1;
        int cao = -1;
        for(int i = 0; i <= n; i ++) vis[i] = 0;
        for(int i = 1; i <= n; i ++) cin >> a[i], vis[a[i]] ++;
        for(int i = 0; i <= n; i ++) if(!vis[i]) cao = i;
        a[n + 1] = cao;
        for(int i = 1; i <= n + 1; i ++) ans[(m + i) % (n + 1)] = a[i];
        for(int i = 1; i <= n ; i ++) cout << ans[i] << " ";
        cout << endl;
    }
    return 0;
}
```
**核心实现思想**：先找出数组中未出现的最小非负整数 `cao`，将其放在数组末尾。然后根据循环节规律，将原数组元素按偏移量 `m` 重新排列到 `ans` 数组中，最后输出 `ans` 数组的前 $n$ 个元素。

- **作者：One_JuRuo（4星）**
  - **关键亮点**：详细解释了周期为 $n + 1$ 的原因，代码逻辑清晰。
  - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,k,a[100005];
set<int>s;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k),k%=n+1;
        for(int i=0;i<=n;++i) s.insert(i);
        for(int i=1;i<=n;++i) scanf("%d",&a[i]),s.erase(a[i]);
        auto i=s.begin();int p=*i;
        if(!k){for(int i=1;i<=n;++i) printf("%d ",a[i]);puts("");}
        else
        {
            for(int i=1;i<=n;++i)
            {
                if(i<k) printf("%d ",a[n-k+i+1]);
                else if(i==k) printf("%d ",p);
                else printf("%d ",a[i-k]);
            }
            puts("");
        }
        s.erase(p);
    }
    return 0;
}
```
**核心实现思想**：使用 `set` 找出数组中未出现的最小非负整数 `p`。根据 $k$ 的值分情况输出结果，当 $k = 0$ 时直接输出原数组，否则根据规律计算并输出对应位置的元素。

- **作者：___nyLittleT___（4星）**
  - **关键亮点**：给出了周期为 $n + 1$ 的证明，代码简洁高效。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 1000005
using namespace std;
ll t,n,m;
ll a[N],ans[N],cnt[N];
int main() {
    scanf("%lld",&t);
    while(t--) {
        scanf("%lld%lld",&n,&m);
        m%=n+1;
        int pos=-1;
        for(int i=0; i<=n; i++) cnt[i]=0;
        for(int i=1; i<=n; i++) scanf("%lld",&a[i]),cnt[a[i]]++;
        for(int i=0; i<=n; i++) if(!cnt[i]) pos=i;
        a[n+1]=pos;
        for(int i=1; i<=n+1; i++) ans[(m+i)%(n+1)]=a[i];
        for(int i=1; i<=n; i++) printf("%lld ",ans[i]);
        puts("");
    }
    return 0;
}
```
**核心实现思想**：通过计数数组 `cnt` 找出数组中未出现的最小非负整数 `pos`，将其放在数组末尾。然后根据循环节规律，将原数组元素按偏移量 `m` 重新排列到 `ans` 数组中，最后输出 `ans` 数组的前 $n$ 个元素。

### 最优关键思路或技巧
- **找规律**：通过手动模拟操作过程，发现操作的循环节长度为 $n + 1$，从而将操作次数 $k$ 对 $n + 1$ 取模，避免了大量不必要的计算。
- **利用 $\operatorname{MEX}$ 的性质**：由于数组元素是 $0$ 到 $n$ 之间两两不同的整数，所以可以快速找出未出现的最小非负整数，简化计算。

### 拓展思路
同类型题目可能会改变操作规则或数组元素的范围，但核心思路仍然是通过找规律来减少计算量。类似的算法套路包括：
- 对于有规律的操作，先通过模拟小数据找出循环节。
- 利用数据的特殊性质（如元素范围、唯一性等）简化计算。

### 推荐题目
1. [P1046 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)
2. [P1420 最长连号](https://www.luogu.com.cn/problem/P1420)
3. [P1980 计数问题](https://www.luogu.com.cn/problem/P1980)

### 个人心得摘录与总结
部分题解作者提到通过手模样例来找规律，这是一种很有效的解题方法。当面对复杂的题目没有思路时，可以从简单的情况入手，通过列举小数据来发现规律，从而找到解题的突破口。同时，在代码实现过程中要注意细节，避免出现 TLE 等问题，如避免使用可能导致超时的 `memset` 函数等。 

---
处理用时：55.56秒