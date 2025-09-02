# 题目信息

# Split Sort

## 题目描述

You are given a permutation $ ^{\dagger} $ $ p_1, p_2, \ldots, p_n $ of integers $ 1 $ to $ n $ .

You can change the current permutation by applying the following operation several (possibly, zero) times:

- choose some $ x $ ( $ 2 \le x \le n $ );
- create a new permutation by: 
  - first, writing down all elements of $ p $ that are less than $ x $ , without changing their order;
  - second, writing down all elements of $ p $ that are greater than or equal to $ x $ , without changing their order;
- replace $ p $ with the newly created permutation.

For example, if the permutation used to be $ [6, 4, 3, 5, 2, 1] $ and you choose $ x = 4 $ , then you will first write down $ [3, 2, 1] $ , then append this with $ [6, 4, 5] $ . So the initial permutation will be replaced by $ [3, 2, 1, 6, 4, 5] $ .

Find the minimum number of operations you need to achieve $ p_i = i $ for $ i = 1, 2, \ldots, n $ . We can show that it is always possible to do so.

 $ ^{\dagger} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, $ n = 1 $ and $ p_1 = 1 $ , so there is nothing left to do.

In the second test case, we can choose $ x = 2 $ and we immediately obtain $ p_1 = 1 $ , $ p_2 = 2 $ .

In the third test case, we can achieve the minimum number of operations in the following way:

1. $ x = 4 $ : $ [6, 4, 3, 5, 2, 1] \rightarrow [3, 2, 1, 6, 4, 5] $ ;
2. $ x = 6 $ : $ [3, 2, 1, 6, 4, 5] \rightarrow [3, 2, 1, 4, 5, 6] $ ;
3. $ x = 3 $ : $ [3, 2, 1, 4, 5, 6] \rightarrow [2, 1, 3, 4, 5, 6] $ ;
4. $ x = 2 $ : $ [2, 1, 3, 4, 5, 6] \rightarrow [1, 2, 3, 4, 5, 6] $ .

## 样例 #1

### 输入

```
5
1
1
2
2 1
6
6 4 3 5 2 1
3
3 1 2
19
10 19 7 1 17 11 8 5 12 9 4 18 14 2 6 15 3 16 13```

### 输出

```
0
1
4
1
7```

# AI分析结果

### 题目内容（中文重写）
# 分割排序

## 题目描述
给定一个整数 $1$ 到 $n$ 的排列 $p_1, p_2, \ldots, p_n$。

你可以通过多次（可能为零次）执行以下操作来改变当前排列：
- 选择某个 $x$（$2 \leq x \leq n$）；
- 创建一个新排列，方法如下：
  - 首先，按顺序写下 $p$ 中所有小于 $x$ 的元素；
  - 其次，按顺序写下 $p$ 中所有大于或等于 $x$ 的元素；
- 用新创建的排列替换 $p$。

例如，如果排列原来是 $[6, 4, 3, 5, 2, 1]$，你选择 $x = 4$，那么你将先写下 $[3, 2, 1]$，然后接上 $[6, 4, 5]$。所以初始排列将被替换为 $[3, 2, 1, 6, 4, 5]$。

找到使 $i = 1, 2, \ldots, n$ 时 $p_i = i$ 所需的最少操作次数。我们可以证明这总是可以做到的。

注：长度为 $n$ 的排列是一个由 $n$ 个从 $1$ 到 $n$ 的不同整数按任意顺序组成的数组。例如，$[2,3,1,5,4]$ 是一个排列，但 $[1,2,2]$ 不是一个排列（$2$ 在数组中出现了两次），$[1,3,4]$ 也不是一个排列（$n = 3$ 但数组中有 $4$）。

## 说明/提示
在第一个测试用例中，$n = 1$ 且 $p_1 = 1$，所以无需进行任何操作。

在第二个测试用例中，我们可以选择 $x = 2$，这样就可以立即得到 $p_1 = 1$，$p_2 = 2$。

在第三个测试用例中，我们可以按以下方式实现最少操作次数：
1. $x = 4$：$[6, 4, 3, 5, 2, 1] \rightarrow [3, 2, 1, 6, 4, 5]$；
2. $x = 6$：$[3, 2, 1, 6, 4, 5] \rightarrow [3, 2, 1, 4, 5, 6]$；
3. $x = 3$：$[3, 2, 1, 4, 5, 6] \rightarrow [2, 1, 3, 4, 5, 6]$；
4. $x = 2$：$[2, 1, 3, 4, 5, 6] \rightarrow [1, 2, 3, 4, 5, 6]$。

## 样例 #1
### 输入
```
5
1
1
2
2 1
6
6 4 3 5 2 1
3
3 1 2
19
10 19 7 1 17 11 8 5 12 9 4 18 14 2 6 15 3 16 13
```
### 输出
```
0
1
4
1
7
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路大多围绕着通过分析数字之间的位置关系来确定最少操作次数。多数题解发现，当一个数的位置在比它大 $1$ 的数的后面时，就需要进行一次操作，因此问题可以转化为求相邻逆序对的数量。

各题解的算法要点主要是先记录每个数字在原排列中的位置，然后遍历这些位置信息，统计相邻逆序对的数量。解决的难点在于理解操作的本质以及如何通过位置关系来确定最少操作次数。

### 所选题解
- **One_JuRuo（4星）**
  - **关键亮点**：思路清晰，代码简洁，直接阐述了每次只排一个数字的贪心策略，通过记录数字位置并比较相邻数字位置关系来统计操作次数。
  - **个人心得**：无
- **Ericby666（4星）**
  - **关键亮点**：先给出暴力解法，再通过研究样例发现规律，将问题转化为求相邻逆序对数量，具有一定的思考过程展示。
  - **个人心得**：比赛时没做出来，写暴力解法前两个点没超时很意外，研究样例后找到正确思路，感叹这么简单的题比赛时爆零。
- **guozhe6241（4星）**
  - **关键亮点**：思路明确，直接指出题目本质类似快排，通过比较相邻数字位置关系统计操作次数，代码简洁。
  - **个人心得**：赛时手打快排超时只拿了40分。

### 重点代码
#### One_JuRuo 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,a,ans;
map<int,int>m;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n),ans=0;
        for(int i=1;i<=n;++i) scanf("%d",&a),m[a]=i;
        for(int i=1;i<n;++i) if(m[i+1]<m[i]) ++ans;
        printf("%d\n",ans);
    }
    return 0;
}
```
**核心实现思想**：使用 `map` 记录每个数字的位置，然后遍历从 $1$ 到 $n - 1$ 的数字，若 $i + 1$ 的位置在 $i$ 的位置之前，则操作次数加 $1$。

#### Ericby666 的 AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[100005],b[100005],ans;
//b数组用于存储a数组中元素的位置
int main(){
    scanf("%d",&t);
    for(int tt=1;tt<=t;tt++){
        scanf("%d",&n);
        ans=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            b[a[i]]=i;
        }
        for(int i=1;i<n;i++)
            if(b[i]>b[i+1])
                ans++;
        printf("%d\n",ans); 
    }
}
```
**核心实现思想**：用数组 `b` 记录每个数字的位置，遍历从 $1$ 到 $n - 1$ 的数字，若 $i$ 的位置在 $i + 1$ 的位置之后，则操作次数加 $1$。

#### guozhe6241 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5; 
int t,n,a[maxn],ans,x[maxn];
int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            x[a[i]]=i;
        }
        for(int i=1;i<n;++i){
            ans+=(x[i]>x[i+1]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
**核心实现思想**：用数组 `x` 记录每个数字的位置，遍历从 $1$ 到 $n - 1$ 的数字，若 $i$ 的位置在 $i + 1$ 的位置之后，则操作次数加 $1$。

### 最优关键思路或技巧
- **位置记录**：使用数组或 `map` 记录每个数字在原排列中的位置，方便后续比较数字之间的位置关系。
- **贪心策略**：每次只考虑排一个数字，通过比较相邻数字的位置关系来确定是否需要操作，从而统计最少操作次数。

### 可拓展之处
同类型题可能会改变操作规则或排列的条件，但核心思路可能仍然是通过分析元素之间的位置关系或顺序关系来确定最少操作次数。类似的算法套路包括分析操作对元素顺序的影响，将问题转化为某种计数问题。

### 推荐题目
- [P1116 车厢重组](https://www.luogu.com.cn/problem/P1116)：通过交换相邻元素使序列有序，可求逆序对数量。
- [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)：直接求逆序对数量的经典题目。
- [P2234 [HNOI2002]营业额统计](https://www.luogu.com.cn/problem/P2234)：涉及到元素顺序和位置关系的维护。

### 个人心得总结
- Ericby666 比赛时写暴力解法没考虑复杂度，前两个点没超时很意外，后来通过研究样例找到正确思路，意识到简单题也可能在比赛时做不出来。
- guozhe6241 赛时直接用快排导致超时，只拿了部分分数，说明要根据题目特点选择合适的算法。 

---
处理用时：49.56秒