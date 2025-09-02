# 题目信息

# Jury Meeting

## 题目描述

$ n $ people gathered to hold a jury meeting of the upcoming competition, the $ i $ -th member of the jury came up with $ a_i $ tasks, which they want to share with each other.

First, the jury decides on the order which they will follow while describing the tasks. Let that be a permutation $ p $ of numbers from $ 1 $ to $ n $ (an array of size $ n $ where each integer from $ 1 $ to $ n $ occurs exactly once).

Then the discussion goes as follows:

- If a jury member $ p_1 $ has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
- If a jury member $ p_2 $ has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
- ...
- If a jury member $ p_n $ has some tasks left to tell, then they tell one task to others. Otherwise, they are skipped.
- If there are still members with tasks left, then the process repeats from the start. Otherwise, the discussion ends.

A permutation $ p $ is nice if none of the jury members tell two or more of their own tasks in a row.

Count the number of nice permutations. The answer may be really large, so print it modulo $ 998\,244\,353 $ .

## 说明/提示

Explanation of the first test case from the example:

There are two possible permutations, $ p = [1, 2] $ and $ p = [2, 1] $ . For $ p = [1, 2] $ , the process is the following:

1. the first jury member tells a task;
2. the second jury member tells a task;
3. the first jury member doesn't have any tasks left to tell, so they are skipped;
4. the second jury member tells a task.

So, the second jury member has told two tasks in a row (in succession), so the permutation is not nice.

For $ p = [2, 1] $ , the process is the following:

1. the second jury member tells a task;
2. the first jury member tells a task;
3. the second jury member tells a task.

So, this permutation is nice.

## 样例 #1

### 输入

```
4
2
1 2
3
5 5 5
4
1 3 3 7
6
3 4 2 1 3 3```

### 输出

```
1
6
0
540```

# AI分析结果

### 题目翻译
# 评审团会议

## 题目描述
有 $n$ 个人聚集在一起为即将到来的比赛召开评审团会议，第 $i$ 位评审团成员提出了 $a_i$ 个任务，他们想相互分享这些任务。

首先，评审团要决定描述任务的顺序。设这个顺序是一个从 $1$ 到 $n$ 的排列 $p$（一个大小为 $n$ 的数组，其中从 $1$ 到 $n$ 的每个整数恰好出现一次）。

然后讨论按以下方式进行：
- 如果评审团成员 $p_1$ 还有任务要讲，那么他们就给其他人讲一个任务。否则，跳过他们。
- 如果评审团成员 $p_2$ 还有任务要讲，那么他们就给其他人讲一个任务。否则，跳过他们。
- ...
- 如果评审团成员 $p_n$ 还有任务要讲，那么他们就给其他人讲一个任务。否则，跳过他们。
- 如果仍然有成员还有任务，那么这个过程从开始重复。否则，讨论结束。

如果没有一个评审团成员连续讲两个或更多自己的任务，那么排列 $p$ 就是好的。

计算好的排列的数量。答案可能非常大，所以请输出它对 $998244353$ 取模的结果。

## 说明/提示
示例中第一个测试用例的解释：

有两种可能的排列，$p = [1, 2]$ 和 $p = [2, 1]$。对于 $p = [1, 2]$，过程如下：
1. 第一位评审团成员讲一个任务；
2. 第二位评审团成员讲一个任务；
3. 第一位评审团成员没有任务可讲了，所以跳过他们；
4. 第二位评审团成员讲一个任务。

所以，第二位评审团成员连续讲了两个任务，所以这个排列不是好的。

对于 $p = [2, 1]$，过程如下：
1. 第二位评审团成员讲一个任务；
2. 第一位评审团成员讲一个任务；
3. 第二位评审团成员讲一个任务。

所以，这个排列是好的。

## 样例 #1
### 输入
```
4
2
1 2
3
5 5 5
4
1 3 3 7
6
3 4 2 1 3 3
```

### 输出
```
1
6
0
540
```

### 算法分类
组合数学

### 综合分析与结论
这些题解的核心思路都是先对题目进行分类讨论，根据最大值和次大值的关系来确定排列的合法性和计算方案数。主要分为三种情况：最大值有不止一个时，任意排列都合法，方案数为 $n!$；最大值比次大值大至少 $2$ 时，任意排列都不合法，方案数为 $0$；最大值只有一个且比次大值大 $1$ 时，需要计算满足条件的排列方案数。不同题解在计算最后一种情况的方案数时方法略有不同，有的从正面计算，有的通过总方案数减去不合法方案数来计算。

### 所选题解
- **XL4453（4星）**
    - **关键亮点**：思路清晰，代码简洁，直接考虑最大和次大的两种数，通过分析最大数的位置来确定合法方案数。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
long long T,n,a[200005],cnt;
long long ans,MOD=998244353;
void work(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    sort(a+1,a+n+1);
    ans=1;
    if(a[n]==a[n-1]){
        for(long long i=1;i<=n;i++)ans=ans*i%MOD;
        printf("%lld\n",ans);
        return;
    }
    if(a[n]-a[n-1]>1){
        printf("0\n");
        return;
    }
    cnt=1;
    for(int i=n-2;i>=1;i--){
        if(a[i]!=a[i+1])break;
        cnt++;
    }
    for(long long i=1;i<=n;i++)
        if(i!=cnt+1)ans=ans*i%MOD;
        else ans=ans*(i-1)%MOD;
    printf("%lld\n",ans);
}
int main(){
    scanf("%d",&T);
    while(T--){
        work();
    }
    return 0;
}
```
    - **核心实现思想**：先对数组排序，判断最大值和次大值的关系。如果最大值等于次大值，直接计算 $n!$；如果最大值比次大值大至少 $2$，输出 $0$；否则，统计次大值的数量 $cnt$，计算 $\frac{n!\times cnt}{cnt + 1}$。

- **SSerxhs（4星）**
    - **关键亮点**：从概率角度考虑问题，思路新颖，简洁明了。
    - **核心思路**：设最大为 $a$，出现了 $A$ 次；次大为 $b$，出现了 $B$ 次。当 $a\ge b + 2$ 时，无解；当 $A\ge 2$ 时，任意排列都合法；当 $a = b + 1$ 时，$A = 1$，从概率角度可得答案为 $n!\frac{B}{B + 1}$。

- **Maysoul（4星）**
    - **关键亮点**：思路清晰，代码实现简单易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MAXN=1e6+10;
const int MOD=998244353;
int num,ans=1;
int mx,mcnt,a[MAXN];
int jie(int n)
{
    int res=1;
    for (int i=1;i<=n;i++) res=(res*i)%MOD;
    return res;
}
signed main()
{
    int t,n;
    cin>>t;
    while(t--){
        int res=0,ans=1;
        cin>>n;
        for (int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        if(a[n]==a[n-1]){
            cout<<jie(n)<<endl;
            continue;
        }
        if(a[n]-a[n-1]>=2){
            cout<<"0"<<endl;
            continue;
        }
        int goal=a[n-1];
        for (int i=n-1;i>=1;i--){
            if(a[i]==goal) res++;
        }
        for (int i=1;i<=n;i++){
            if(i!=res+1) ans=(ans*i)%MOD;
            else ans=(ans*(i-1))%MOD; 
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：先对数组排序，判断最大值和次大值的关系。如果最大值等于次大值，计算 $n!$；如果最大值比次大值大至少 $2$，输出 $0$；否则，统计次大值的数量 $res$，计算 $\frac{n!\times res}{res + 1}$。

### 最优关键思路或技巧
- **分类讨论**：根据最大值和次大值的关系进行分类讨论，将复杂问题简化。
- **从特殊情况入手**：先考虑最大值有多个和最大值与次大值差距较大的特殊情况，再处理一般情况。
- **逆向思维**：在计算最大值只有一个且比次大值大 $1$ 的情况时，通过总方案数减去不合法方案数来计算合法方案数。

### 拓展思路
同类型题或类似算法套路通常涉及组合数学和分类讨论的思想。例如，在一些排列组合问题中，需要根据不同的条件对排列进行分类，然后分别计算方案数。在处理复杂的组合问题时，可以先考虑特殊情况，再逐步推广到一般情况。

### 推荐洛谷题目
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：涉及数论和组合数学的知识。
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)：考察组合数的计算和取模运算。
- [P2671 [NOIP2015 普及组] 求和](https://www.luogu.com.cn/problem/P2671)：需要运用组合数学和前缀和的思想。

### 个人心得
题解中未包含个人心得。

---
处理用时：96.60秒