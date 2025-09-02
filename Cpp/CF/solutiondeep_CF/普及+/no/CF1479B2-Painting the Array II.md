# 题目信息

# Painting the Array II

## 题目描述

### 题意

  **本题与 CF1480D1 的唯一区别是本题询问最小可能解.**

  给定一个数组 $a$, 你将将 $a_i$ 染为 $b_i$ 色, 其中 $b$ 是由你指定的一个 **01 数组**. 将 $a$ 数组中被染成 0 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(0)}$. 同理, 将 $a$ 数组中被染成 1 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(1)}$. 我们定义 $seg(c)$ 是一个正整数, 其中 $c$ 是一个数组, $seg(c)$ 的值为在我们将 $c$ 中相邻的所有相同元素合并后, $c$ 数组的大小. 例如, $seg([1, 1, 4, 5, 1, 4]) = |[1, 4, 5, 1, 4]|=5$. 最小化 $seg(a^{(0)})+seg(a^{(1)})$.

## 样例 #1

### 输入

```
6
1 2 3 1 2 2```

### 输出

```
4```

## 样例 #2

### 输入

```
7
1 2 1 2 1 2 1```

### 输出

```
2```

# AI分析结果

### 题目内容（已为中文，无需翻译）
【题目内容】
# Painting the Array II

## 题目描述

### 题意

  **本题与 CF1480D1 的唯一区别是本题询问最小可能解.**

  给定一个数组 $a$, 你将将 $a_i$ 染为 $b_i$ 色, 其中 $b$ 是由你指定的一个 **01 数组**. 将 $a$ 数组中被染成 0 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(0)}$. 同理, 将 $a$ 数组中被染成 1 色的数字取出来并依在 $a$ 中出现的顺序排列, 组成数组 $a^{(1)}$. 我们定义 $seg(c)$ 是一个正整数, 其中 $c$ 是一个数组, $seg(c)$ 的值为在我们将 $c$ 中相邻的所有相同元素合并后, $c$ 数组的大小. 例如, $seg([1, 1, 4, 5, 1, 4]) = |[1, 4, 5, 1, 4]|=5$. 最小化 $seg(a^{(0)})+seg(a^{(1)})$.

## 样例 #1

### 输入

```
6
1 2 3 1 2 2```

### 输出

```
4```

## 样例 #2

### 输入

```
7
1 2 1 2 1 2 1```

### 输出

```
2```

### 算法分类
本题相关的算法分类为贪心、动态规划

### 综合分析与结论
这些题解主要围绕如何将给定数组分成两个子数组，使得两个子数组合并相邻相同元素后的长度之和最小展开。题解思路主要分为贪心和动态规划两大类。

贪心思路的要点在于模拟将元素依次放入两个队列的过程，根据当前元素与两个队列队尾元素的关系以及队尾元素下一次出现的位置来决定元素放入哪个队列，以达到最小化 $seg(a^{(0)})+seg(a^{(1)})$ 的目的。

动态规划思路则是通过定义状态和状态转移方程来求解，通常会先对数组进行去重处理，然后根据不同的状态转移情况计算最小代价。

解决的难点在于如何合理地选择元素的分配方式，使得最终结果最小。不同的题解在处理细节上有所不同，但核心都是围绕如何利用元素的相邻关系和出现位置信息来优化分配策略。

### 所选题解
- **wsyhb（4星）**
    - **关键亮点**：思路清晰，分别给出了贪心和动态规划两种解法，并对动态规划的优化过程进行了详细说明，代码实现规范，有详细的注释。
    - **个人心得**：无
- **zjjws（4星）**
    - **关键亮点**：对动态规划的思路解释详细，通过具体的例子说明了转移关键点的选择原因，代码实现简洁明了。
    - **个人心得**：无
- **chlchl（4星）**
    - **关键亮点**：贪心思路的解释通俗易懂，通过具体例子说明了贪心策略的合理性，虽然没有给出代码，但思路清晰。
    - **个人心得**：无

### 重点代码及核心实现思想
#### wsyhb - 贪心解法
```cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
int a[max_n],id[max_n],Next[max_n];
typedef pair<int,int> P;//前一个是元素的值，后一个是元素的编号
vector<P> w,b;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",a+i);
        id[i]=n+1;//注意初始化
    }
    for(int i=n;i>=1;--i)
    {
        Next[i]=id[a[i]];
        id[a[i]]=i;
    }
    w.push_back(P(0,n+1));
    b.push_back(P(0,n+1));
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        if(a[i]==w.back().first)
            w.push_back(P(a[i],Next[i]));
        else if(a[i]==b.back().first)
            b.push_back(P(a[i],Next[i]));
        else
        {
            ++ans;
            if(w.back().second>b.back().second)
                w.push_back(P(a[i],Next[i]));
            else
                b.push_back(P(a[i],Next[i]));
        }
    }
    printf("%d\n",ans);
    return 0;
}
```
**核心实现思想**：先预处理每个元素下一次出现的位置，然后模拟将元素依次放入两个队列 $w$ 和 $b$ 的过程。如果当前元素与某个队列的队尾元素相等，则直接放入该队列；否则，比较两个队列队尾元素下一次出现的位置，将元素放入下一次出现位置更远的队列。

#### wsyhb - 动态规划解法
```cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=1e5+5;
int a[max_n],id[max_n],f[max_n];//id 就是上述提到的桶
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",a+i);
        if(a[i]==a[i-1])
            --i,--n;//去掉相同的相邻元素
    }
    for(int i=1;i<=n;++i)
    {
        id[a[i-1]]=i;
        f[i]=f[i-1]-(i-1)+1;
        int j=id[a[i]];
        if(j)
            f[i]=min(f[i],f[j]-j);
        f[i]+=i-1;
    }
    int ans=n;
    for(int i=1;i<=n;++i)
        ans=min(ans,f[i]+(n-i));
    printf("%d\n",ans);
    return 0;
}
```
**核心实现思想**：先对数组进行去重处理，然后定义 $f(i)$ 表示当前已加入前 $i$ 个元素，且 $b_i \neq b_{i-1}$ 时，$seg(a^{(0)})+seg(a^{(1)})$ 的最小值。通过状态转移方程 $f(i)=(i-1)+\min\begin{cases}f(i-1)-(i-1)+1\\f(j)-j &(j=\max\{j:a_{j-1}=a_i\})\end{cases}$ 计算 $f(i)$ 的值，最后取 $\min_{i=1}^{n}\{f(i)+(n-i)\}$ 作为最终答案。

#### zjjws - 动态规划解法
```cpp
#include <queue>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#define LL long long
using namespace std;
const int N=3e5+3;
inline LL rin()
{
    LL s=0;
    bool bj=false;
    char c=getchar();
    for(;(c>'9'||c<'0')&&c!='-';c=getchar());
    if(c=='-')bj=true,c=getchar();
    for(;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+(c^'0');
    if(bj)return -s;
    return s;
}
inline void jh(int &x,int &y){if(x!=y)x^=y^=x^=y;}
inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
inline LL min(LL x,LL y){return x<y?x:y;}
inline LL max(LL x,LL y){return x>y?x:y;}

int n;
int a[N];
int f[N];
int lst[N];
inline void work()
{
    n=rin();
    for(int i=1;i<=n;i++)a[i]=rin();
    int nam=0;
    for(int i=1,j;i<=n;i=j){for(j=i+1;j<=n&&a[j]==a[i];j++);a[++nam]=a[i];}
    n=nam;
    for(int i=1;i<=n;i++)f[i]=i;
    for(int i=1,j;i<=n;i++)
    {
        f[i]=min(f[i],f[i-1]+1);
        if(lst[a[i]])j=lst[a[i]],f[i]=min(f[i],f[j+1]+(i-j-2));
        lst[a[i]]=i;
    }
    printf("%d\n",f[n]);
    return;
}
int main()
{
    work();
    return 0;
}
```
**核心实现思想**：先对数组进行去重处理，然后定义 $f_x$ 表示下标 $1$ 到 $x$ 的所有元素已经分完组的最小代价。状态转移时，考虑不将最后一个元素与其他元素组合的情况 $f_x\le f_{x-1}+1$，以及强制将最后一个元素与前面相同元素组合的情况 $f_x=f_{y+1}+(x-(y+2)+1)-1$，其中 $y$ 是最大的满足 $p_x=p_y$ 且 $y<x$ 的下标。

### 最优关键思路或技巧
- **预处理下一次出现位置**：通过预处理每个元素下一次出现的位置，可以在贪心选择时更方便地判断元素应该放入哪个队列。
- **去重处理**：将相邻相同的元素合并，不影响最终结果，同时可以减少状态转移的复杂度。
- **状态转移优化**：在动态规划中，通过分析状态转移方程，找到关键的转移点，减少不必要的计算，将时间复杂度从 $O(n^2)$ 优化到 $O(n)$。

### 可拓展之处
同类型题或类似算法套路：
- 其他数组划分问题，如将数组划分为多个子数组，使得某些指标（如子数组的和、长度等）达到最优。
- 区间合并问题，根据元素的相邻关系和出现位置信息，对区间进行合并和优化。

### 推荐洛谷题目
- [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)
- [P2672 [NOIP2015 普及组] 推销员](https://www.luogu.com.cn/problem/P2672)
- [P1880 [NOI1995] 石子合并](https://www.luogu.com.cn/problem/P1880)

---
处理用时：76.90秒