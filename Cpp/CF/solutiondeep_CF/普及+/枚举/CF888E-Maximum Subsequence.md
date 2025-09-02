# 题目信息

# Maximum Subsequence

## 题目描述

You are given an array $ a $ consisting of $ n $ integers, and additionally an integer $ m $ . You have to choose some sequence of indices $ b_{1},b_{2},...,b_{k} $ ( $ 1<=b_{1}&lt;b_{2}&lt;...&lt;b_{k}<=n $ ) in such a way that the value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png) is maximized. Chosen sequence can be empty.

Print the maximum possible value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/3a3d2e76b5bca3303d7d35912be232a5cadb1203.png).

## 说明/提示

In the first example you can choose a sequence $ b={1,2} $ , so the sum ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF888E/08d6750b1b23699a8b513ddd01c316f10e6a789c.png) is equal to $ 7 $ (and that's $ 3 $ after taking it modulo $ 4 $ ).

In the second example you can choose a sequence $ b={3} $ .

## 样例 #1

### 输入

```
4 4
5 2 4 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 20
199 41 299
```

### 输出

```
19
```

# AI分析结果

### 题目内容
# 最大子序列

## 题目描述
给定一个由 $n$ 个整数组成的数组 $a$ ，以及一个整数 $m$ 。你必须选择一些索引序列 $b_{1},b_{2},\cdots,b_{k}$ （$1\leq b_{1}<b_{2}<\cdots <b_{k}\leq n$ ），使得 $\sum_{i = 1}^{k}a_{b_{i}}\bmod m$ 的值最大化。所选序列可以为空。
输出 $\sum_{i = 1}^{k}a_{b_{i}}\bmod m$ 的最大可能值。

## 说明/提示
在第一个示例中，你可以选择序列 $b = \{1,2\}$ ，因此和 $\sum_{i = 1}^{2}a_{b_{i}} = 5 + 2 = 7$ （对 $4$ 取模后为 $3$ ）。
在第二个示例中，你可以选择序列 $b = \{3\}$ 。

## 样例 #1
### 输入
```
4 4
5 2 4 1
```
### 输出
```
3
```

## 样例 #2
### 输入
```
3 20
199 41 299
```
### 输出
```
19
```

### 综合分析与结论
所有题解都基于数据范围 $n\leq35$ ，发现朴素 $O(2^n)$ 枚举不可行，从而采用折半搜索的策略。将原序列分成两半，分别暴力搜索两半序列所有元素组合的和并取模，得到两个数组。之后针对如何从这两个数组中选取元素组合使得和取模后最大，采用了不同的优化策略：
 - **双指针法**：对两个数组排序后，用两个指针分别指向一个数组的开头和另一个数组的末尾，根据两指针指向元素和与 $m$ 的大小关系移动指针，找到最优解。同时考虑两数组最大值之和取模的情况更新答案。
 - **二分查找法**：对其中一个数组排序，对于另一个数组中的每个元素，通过二分查找在排序数组中找到满足条件（小于等于 $m - 1 - x$ ）的最大元素，同时考虑与排序数组最大值组合的情况更新答案。

### 所选的题解
- **作者：newbiechd (赞：19)  星级：5星**
    - **关键亮点**：思路清晰，从暴力枚举的不可行性出发，逐步引入折半搜索和双指针优化。代码实现完整且注释详细，还特别提到了对 $n = 1$ 情况的特判。
    - **个人心得**：作者提到切这道题用了较长时间，发题解作为纪念。
```cpp
void dfs1(int i,int sum){
    if(i==b){p[++k]=sum,p[++k]=(sum+a[b])%m; return ;}
    dfs1(i+1,sum),dfs1(i+1,(sum+a[i])%m);
}
void dfs2(int i,int sum){
    if(i==n){q[++t]=sum,q[++t]=(sum+a[n])%m; return ;}
    dfs2(i+1,sum),dfs2(i+1,(sum+a[i])%m);
}
int main(){
    R int i,j,ans=0;
    n=read(),m=read(),b=n>>1;
    for(i=1;i<=n;++i) a[i]=read();
    if(n==1) printf("%d",a[1]%m),exit(0);
    dfs1(1,0),dfs2(b+1,0),i=0,j=t;
    sort(p+1,p+k+1),sort(q+1,q+t+1);
    while(i<=k){
        while(p[i]+q[j]>=m) --j;
        ans=max(ans,p[i]+q[j]),++i;
    }
    ans=max(ans,p[k]+q[t]-m);
    printf("%d",ans);
    return 0;
}
```
核心实现思想：`dfs1` 和 `dfs2` 分别对序列的两半进行搜索，记录所有可能的和（取模后）。主函数中对搜索结果数组排序，通过双指针移动找到最优解。
- **作者：Youngore (赞：9)  星级：4星**
    - **关键亮点**：对排序后数组匹配过程的分析较为详细，从 $p + q$ 与 $m$ 的大小关系出发，分情况讨论并给出优化策略，逻辑严谨。
```cpp
sort(sum1 + 1, sum1 + cnt1 + 1), sort(sum2 + 1, sum2 + cnt2 + 1);
l = cnt1, r = 1;
for (r = 1; r <= cnt2; ++ r)
{
    while (sum1[l] + sum2[r] >= mod) -- l;
    res = max(res, sum1[l] + sum2[r]);
}
```
核心实现思想：对两半搜索得到的数组 `sum1` 和 `sum2` 排序，初始化指针 `l` 指向 `sum1` 末尾，`r` 指向 `sum2` 开头，遍历 `sum2` ，根据两数和与 `mod` 的关系移动 `l` 找到最优解。
- **作者：fls233666 (赞：4)  星级：4星**
    - **关键亮点**：详细阐述折半搜索思路，对搜索结果的处理采用排序加二分查找的方式，代码简洁明了，对边界情况处理得当。
```cpp
void dfs1(int x,ll s){
    if(x==n/2){
        pans.push_back(s);
        return;
    }
    dfs1(x+1,s);
    dfs1(x+1,(s+a[x])%m);
}
void dfs2(int x,ll s){
    if(x>n){
        int tp=lower_bound(pans.begin(),pans.end(),m-s)-1-pans.begin();
        ans=qmx(ans,pans[tp]+s);
        ans=qmx(ans,(pans[pans.size()-1]+s)%m);
        return;
    }
    dfs2(x+1,s);
    dfs2(x+1,(s+a[x])%m);
}
int main(){
    scanf("%d%lld",&n,&m);
    for(rgt i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    if(n==1){
        printf("%lld",a[1]%m);
        return 0;
    }
    dfs1(1,0);
    sort(pans.begin(),pans.end());
    dfs2(n/2,0);
    printf("%lld",ans);
    return 0;
}
```
核心实现思想：`dfs1` 搜索前半部分序列，`dfs2` 搜索后半部分序列。在 `dfs2` 中，通过二分查找找到合适元素与当前和匹配，同时考虑与数组最大值组合的情况更新答案。

### 最优关键思路或技巧
折半搜索将原问题的指数级时间复杂度降低，通过对两半搜索结果数组的排序，利用双指针法或二分查找法快速找到最优组合，优化了从两个数组中选取元素使和取模最大的过程。同时，利用取模后两数和小于 $2m$ 的性质，简化了问题的讨论。

### 可拓展之处
同类型题或类似算法套路：适用于数据规模不大，直接暴力枚举复杂度太高，但问题具有可拆分合并性质的情况。可以将原问题分成两部分分别求解，再合并结果。例如一些子集和问题、背包问题的变体等。

### 洛谷相似题目推荐
 - **P4799 [CEOI2008] 疗养**：同样是通过折半搜索来解决子集和相关问题，与本题思路相似。
 - **P1433 吃奶酪**：在搜索过程中可以利用折半思想优化枚举，与本题优化思路类似。
 - **P2661 信息传递**：虽然主要考察的是图论中的环相关知识，但在数据规模较小时，也可以考虑折半搜索等优化手段来枚举。 

---
处理用时：35.22秒