# 题目信息

# Unmerge

## 题目描述

Let $ a $ and $ b $ be two arrays of lengths $ n $ and $ m $ , respectively, with no elements in common. We can define a new array $ \mathrm{merge}(a,b) $ of length $ n+m $ recursively as follows:

- If one of the arrays is empty, the result is the other array. That is, $ \mathrm{merge}(\emptyset,b)=b $ and $ \mathrm{merge}(a,\emptyset)=a $ . In particular, $ \mathrm{merge}(\emptyset,\emptyset)=\emptyset $ .
- If both arrays are non-empty, and $ a_1<b_1 $ , then $ \mathrm{merge}(a,b)=[a_1]+\mathrm{merge}([a_2,\ldots,a_n],b) $ . That is, we delete the first element $ a_1 $ of $ a $ , merge the remaining arrays, then add $ a_1 $ to the beginning of the result.
- If both arrays are non-empty, and $ a_1>b_1 $ , then $ \mathrm{merge}(a,b)=[b_1]+\mathrm{merge}(a,[b_2,\ldots,b_m]) $ . That is, we delete the first element $ b_1 $ of $ b $ , merge the remaining arrays, then add $ b_1 $ to the beginning of the result.

This algorithm has the nice property that if $ a $ and $ b $ are sorted, then $ \mathrm{merge}(a,b) $ will also be sorted. For example, it is used as a subroutine in merge-sort. For this problem, however, we will consider the same procedure acting on non-sorted arrays as well. For example, if $ a=[3,1] $ and $ b=[2,4] $ , then $ \mathrm{merge}(a,b)=[2,3,1,4] $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

There is a permutation $ p $ of length $ 2n $ . Determine if there exist two arrays $ a $ and $ b $ , each of length $ n $ and with no elements in common, so that $ p=\mathrm{merge}(a,b) $ .

## 说明/提示

In the first test case, $ [2,3,1,4]=\mathrm{merge}([3,1],[2,4]) $ .

In the second test case, we can show that $ [3,1,2,4] $ is not the merge of two arrays of length $ 2 $ .

In the third test case, $ [3,2,6,1,5,7,8,4]=\mathrm{merge}([3,2,8,4],[6,1,5,7]) $ .

In the fourth test case, $ [1,2,3,4,5,6]=\mathrm{merge}([1,3,6],[2,4,5]) $ , for example.

## 样例 #1

### 输入

```
6
2
2 3 1 4
2
3 1 2 4
4
3 2 6 1 5 7 8 4
3
1 2 3 4 5 6
4
6 1 3 7 4 5 8 2
6
4 3 2 5 1 11 9 12 8 6 10 7```

### 输出

```
YES
NO
YES
YES
NO
NO```

# AI分析结果

### 题目翻译
## Unmerge

### 题目描述
设 $a$ 和 $b$ 分别是长度为 $n$ 和 $m$ 的两个数组，且它们没有共同元素。我们可以递归地定义一个长度为 $n + m$ 的新数组 $\mathrm{merge}(a, b)$ 如下：
- 如果其中一个数组为空，则结果为另一个数组。即 $\mathrm{merge}(\emptyset, b) = b$ 且 $\mathrm{merge}(a, \emptyset) = a$。特别地，$\mathrm{merge}(\emptyset, \emptyset) = \emptyset$。
- 如果两个数组都非空，且 $a_1 < b_1$，那么 $\mathrm{merge}(a, b) = [a_1] + \mathrm{merge}([a_2, \ldots, a_n], b)$。也就是说，我们删除 $a$ 的第一个元素 $a_1$，合并剩余的数组，然后将 $a_1$ 添加到结果的开头。
- 如果两个数组都非空，且 $a_1 > b_1$，那么 $\mathrm{merge}(a, b) = [b_1] + \mathrm{merge}(a, [b_2, \ldots, b_m])$。也就是说，我们删除 $b$ 的第一个元素 $b_1$，合并剩余的数组，然后将 $b_1$ 添加到结果的开头。

这个算法有一个很好的性质，即如果 $a$ 和 $b$ 是有序的，那么 $\mathrm{merge}(a, b)$ 也将是有序的。例如，它被用作归并排序中的一个子过程。然而，对于这个问题，我们也会考虑同样的过程作用于无序数组的情况。例如，如果 $a = [3, 1]$ 且 $b = [2, 4]$，那么 $\mathrm{merge}(a, b) = [2, 3, 1, 4]$。

一个排列是一个由 $n$ 个从 $1$ 到 $n$ 的不同整数按任意顺序组成的数组。例如，$[2, 3, 1, 5, 4]$ 是一个排列，但 $[1, 2, 2]$ 不是一个排列（$2$ 在数组中出现了两次），$[1, 3, 4]$ 也不是一个排列（$n = 3$ 但数组中有 $4$）。

有一个长度为 $2n$ 的排列 $p$。判断是否存在两个长度均为 $n$ 且没有共同元素的数组 $a$ 和 $b$，使得 $p = \mathrm{merge}(a, b)$。

### 说明/提示
在第一个测试用例中，$[2, 3, 1, 4] = \mathrm{merge}([3, 1], [2, 4])$。

在第二个测试用例中，我们可以证明 $[3, 1, 2, 4]$ 不是两个长度为 $2$ 的数组的合并结果。

在第三个测试用例中，$[3, 2, 6, 1, 5, 7, 8, 4] = \mathrm{merge}([3, 2, 8, 4], [6, 1, 5, 7])$。

在第四个测试用例中，例如 $[1, 2, 3, 4, 5, 6] = \mathrm{merge}([1, 3, 6], [2, 4, 5])$。

### 样例 #1
#### 输入
```
6
2
2 3 1 4
2
3 1 2 4
4
3 2 6 1 5 7 8 4
3
1 2 3 4 5 6
4
6 1 3 7 4 5 8 2
6
4 3 2 5 1 11 9 12 8 6 10 7
```
#### 输出
```
YES
NO
YES
YES
NO
NO
```

### 算法分类
动态规划

### 综合分析与结论
这些题解的核心思路都是先通过分析合并操作的性质，将原排列 $p$ 划分为若干个“块”，每个块内的元素必须来自同一个数组，然后将问题转化为能否从这些块中选出一部分，使得它们的长度之和等于 $n$，这是一个典型的 0 - 1 背包问题，使用动态规划来解决。

不同题解在划分块的方式和动态规划的实现细节上有所不同。有的通过比较相邻元素大小来划分块，有的从大到小遍历元素并标记来划分块；在动态规划实现上，有的使用二维数组，有的使用一维数组，还有的使用 `bitset` 进行优化。

### 所选题解
- **Yaha（4星）**
  - **关键亮点**：思路清晰，详细推导了划分块的性质，使用 `bitset` 优化动态规划，代码简洁。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int siz[4100],t,n;
int main(){
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        int cnt=0,Max=0,a;
        for(int i=1;i<=2*n;i++)
        {
            scanf("%d",&a);
            if(a<Max) siz[cnt]++;//加入块
            else siz[++cnt]=1,Max=a;//新建块
        }
        bitset<10000> B;
        B[0]=1;//可以凑成0！
        for(int i=1;i<=cnt;i++)
            B|=B<<siz[i];
        if(B[n]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```
  - **核心实现思想**：先遍历排列 $p$，根据元素与当前块头的大小关系划分块，记录每个块的大小。然后使用 `bitset` 进行动态规划，`B[i] = 1` 表示可以凑成长度 $i$，通过左移取或操作更新 `B`，最后判断 `B[n]` 是否为 1。

- **Scintilla（4星）**
  - **关键亮点**：通过具体样例展示划分块的过程，将问题转化为 0 - 1 背包问题，思路直观，代码实现简洁。
  - **核心代码**：
```cpp
int tc;
int n, p[N << 1];
int tot, sz[N << 1];
bool vis[N << 1];
bool f[N];
int main() {
    tc = read(), f[0] = true;
    while (tc--) {
        n = read() << 1;
        Rep(i, 1, n) p[i] = read();
        int now = n, lst = n;
        Dep(i, n, 1) {
            vis[p[i]] = true;
            if (p[i] == now) {
                while (now && vis[now]) --now;
                sz[++tot] = lst - i + 1, lst = i - 1;
            }
        }
        Rep(i, 1, tot) {
            Dep(j, n >> 1, sz[i]) f[j] |= f[j - sz[i]];
        }
        puts(f[n >> 1] ? "YES" : "NO");
        tot = 0;
        Rep(i, 1, n) f[i] = false, vis[i] = false;
    }
    return 0;
}
```
  - **核心实现思想**：从后往前遍历排列 $p$，标记已访问元素，当遇到当前最大值时，记录当前块的长度，划分出块。然后使用一维数组 `f` 进行 0 - 1 背包动态规划，判断是否能凑出长度 $n$。

- **RedLycoris（4星）**
  - **关键亮点**：详细解释了划分块的过程，使用二维数组进行 0 - 1 背包动态规划，代码结构清晰。
  - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mxn=4002;
vector<int>g[mxn];
int n,m;
int a[mxn],pos[mxn];
bool ban[mxn];
vector<int>v;
int dp[mxn][mxn];
inline void solve(){
    cin>>n;for(int i=1;i<=n*2;++i)pos[i]=0;
    for(int i=1;i<=n*2;++i)ban[i]=0;
    v.clear();
    for(int i=1;i<=n*2;++i)cin>>a[i],pos[a[i]]=i;
    for(int i=n*2;i;--i){              //分割
        int cnt=0;
        for(int j=pos[i];j<=n*2 and !ban[j];)++cnt,ban[j]=1,++j;
        if(cnt)v.push_back(cnt);
    }
    for(int i=0;i<=v.size();++i)for(int j=0;j<=n;++j)dp[i][j]=0;
    dp[0][0]=1;
    sort(v.begin(),v.end());
    for(int i=0;i<v.size();++i){       //背包
        for(int j=0;j<=n;++j){
            if(dp[i][j]==1){
                dp[i+1][j]=1;
                if(j+v[i]<=n){
                    dp[i+1][j+v[i]]=1;
                }
            }
        }
    }
    if(dp[(int)(v.size())][n])cout<<"YES\n";
    else cout<<"NO\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int T=1;cin>>T;
    for(;T--;)solve();
}
```
  - **核心实现思想**：从大到小遍历排列 $p$，标记已访问元素，统计每个块的长度，将其存入 `v` 中。然后使用二维数组 `dp` 进行 0 - 1 背包动态规划，判断是否能凑出长度 $n$。

### 最优关键思路或技巧
- **性质推导**：通过分析合并操作的性质，得出连续递减子序列或一个数到其后第一个比它大的数之间的元素必须来自同一个数组，从而将原排列划分为若干个块。
- **动态规划优化**：使用 `bitset` 可以在常数时间内完成状态转移，优化动态规划的时间复杂度。

### 可拓展之处
同类型题或类似算法套路：
- 其他涉及序列划分和组合的问题，如将一个序列划分为若干个子序列，使得子序列满足某些条件，然后判断是否能组合出特定的结果。
- 0 - 1 背包问题的变种，如多重背包、完全背包等，可通过改变状态转移方程来解决。

### 推荐洛谷题目
- P1048 [NOIP2005 普及组] 采药
- P1616 疯狂的采药
- P2871 [USACO07DEC]Charm Bracelet S

### 个人心得摘录与总结
- **傅思维666**：一开始狂开三个 `memset` 导致 TLE，后来发现保存原数列的数组和每段的长度数组不需要清空，对于 `dp` 数组可以边转移边清空，避免了超时问题。总结：在处理多组数据时，要注意数组清空的必要性，避免不必要的操作导致超时。

---
处理用时：72.50秒