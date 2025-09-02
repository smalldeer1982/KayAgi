# [BalticOI 2007] Ranklist Sorting (Day 1)

## 题目描述

在一场比赛中，你会得到几名选手的分数。你的任务是创建一个按分数递减排序的选手的排名表。  
不幸的是，用于选手排名表的数据结构仅支持一种操作，即在不改变其他玩家的相对顺序的情况下将玩家从位置 $i$ 移动到位置 $j$。如果 $i > j$，则 $j$ 和 $i-1$ 之间位置的玩家位置增加 $1$，否则如果 $i < j$，则 $i+1$ 和 $j$ 之间位置的玩家位置减少 $1$。  
这个操作需要 $i$ 步来定位要移动的玩家，$j$ 步来定位他或她移动到的位置，所以将一个玩家从位置 $i$ 移动到位置 $j$ 的总成本是 $i+j$。规定，位置从 $1$ 开始编号。  
确定一个步法序列来创建排名表，使步法的代价之和最小化。

## 说明/提示

#### 数据规模与约定  
对于 $30 \% $ 的数据，$n \le 10$，$0  \le s_i \le 10^6$。  
对于 $100 \%$ 的数据，$2 \le n \le 10^3$，$0  \le s_i \le 10^6$。
 #### 题目说明  
来源于 [Baltic Olympiad in Informatics 2007](https://www.boi2007.de/en/welcome) 的 [Day 1:sorting](https://www.boi2007.de/tasks/sorting.pdf)。  
由 @[求学的企鹅](/user/271784) 翻译整理。

## 样例 #1

### 输入

```
5
20
30
5
15
10```

### 输出

```
2
2 1
3 5```

# 题解

## 作者：yzy1 (赞：7)

## 题目大意

给你一个排列 $p_i$，每次可以将第 $i$ 个元素移到第 $j$ 个位置，花费 $i+j$ 的代价，问最少花费多少代价将这个排列变成 $1\sim n$ 的排列。

## 大体思路

对于一个数字 $i$，设它现在的下标为 $p_i$。它要移动到正确的位置（即数字 $i+1$ 的前面一个位置），有两种方式：用一次操作将它「主动」移过去，或者把 $[p_i+1\sim p_{i+1}-1]$ 之间的数字全部移走，让这个数「被动」跑到这个位置。如果 $p_i<p_{i+1}$，则用两种方式移动均可。否则，只能使用第一种方式。

我们可以用上面的方法，从 $n-1$ 至 $1$ 移动每个数。由于是「倒序」移动，所以当移动数 $i$ 时，$i+1\sim n$ 就已经排好序了，且 $1\sim i$ 的**相对**位置和未排序前一样。

我们设 $dp(i,j)$ 表示现在要排 $i$ 这个数，已经排好 $i+1\sim n$，且 $i$ 要放到**一开始的序列**的第 $j$ 号位置的最小代价。记 $now(x)$ 为数字 $x$ 现在的位置，$pos(x)$ 为数字 $x$ 一开始的位置。先来考虑第一种移动方式，我们可以枚举 $j$，即
$$
dp(i,j)=\min\{dp(i+1,j)+now(i)+now(j)\}.
$$
注意这里是 $now(j)$ 而不是 $j$，因为 $j$ 是**初始**序列的下标。

如果使用第二种移动方式，则需要麻烦一些了。根据[徐源盛大佬的论文《对一类动态规划问题的研究》](https://wenku.lingfengyun.com/view-2d83023e2de246c6bf6cf67626b153b7.html)，我们可以知道一个性质：当前决策对未来行动的费用影响只与当前决策有关。也就是说，如果 $i$ 这个数不动，那么可能对以后的决策花费产生影响，具体一点就是初始位置在 $[pos(i)+1, j-1]$ 之间的数在排序过程中都需要跨越一次 $i$。根据论文，我们知道对于整数 $x,x<i$，$x$ 跨越 $i$ 对答案所增加的代价是 $i-x$。由于「当前决策对未来行动的费用影响只与当前决策有关」，我们可以直接把这个 $i-x$ 加进当前决策的花费中。也就是说，对于移动方式二，我们有以下转移方程：
$$
dp(i,pos(i))=\min_{j=pos(i+1)}^n\{dp(i+1,j)+(\sum_{k=pos(i)+1}^{j-1}\max\{i-s_k,0\})\}
$$
转移方程里的那个求和可以在转移的过程中记录，所以该 DP 的时间复杂度为 $O(n^2)$。

## 核心代码

```cpp
memset(dp, 0x3F, sizeof dp);
dp[n][n] = 0;
per(i, n - 1, 1) {
  int posi = 1, posj = 1;
  re(j, pos[i] - 1) posi += (s[j] < i);
  // 移动方式 1
  re(j, n) {
    posj += (s[j] < i);
    if (dp[i + 1][j] != 0x3F3F3F3F) dp[i][j] = dp[i + 1][j] + posi + posj;
  }
  // 移动方式 2
  int sum = 0;
  rep(j, pos[i] + 1, n) {
    if (dp[i][pos[i]] > dp[i + 1][j] + sum) dp[i][pos[i]] = dp[i + 1][j] + sum, pre[i] = j;
    sum += max(0, i - s[j]);
  }
}
```



---

## 作者：myee (赞：2)

### Update
* 公式已修。

### 引言

参考资料：2009 年集训队论文，徐源盛，《对一类动态规划问题的研究》。

果然我看题解还是看不懂的吗，还是看原论文清楚。（虽然原论文格式排版很难受）

**为了方便起见，以下认为编号为 $x$ 的人应当放到第 $x$ 号位置，下标从 $0$ 到 $n-1$。**

**为了方便起见，我们再在第 $n$ 项放入一个 $n$，减少讨论。**

以下把重标号后的序列记为 $\{a\}$。

### 思路

#### 摆结论

$\textbf{Fact 1}$ 每个人最多被选择并移动一次。

$\textbf{Fact 2}$ 总存在按编号递减序移动取到最优解的方案；如果一个人被移动，总可令其移动到比其编号大 $1$ 的人之前，使得答案仍可取最优。

这两条结论的证明不是重点，此处从略。

由这两条结论，我们得到，按照如下做法进行操作是可获得最优解的：
* 按编号从大到小枚举每个人，考虑其是否主动移动。假设当前枚举到编号为 $x$ 的人。
* 如果其主动移动，其会移动到当前编号为 $x+1$ 的人前面。
* 否则，若其不主动移动，会导致对于编号更小的人，其移动方案的局面发生改变。
* 注意如果当前节点在 $x+1$ 右边，其必须主动移动。

然后我们得到一个推论，也即：

假设当前处理的是节点 $x$，则所有 $\le x$ 的数相对顺序不变，所有大于 $x+1$ 的数顺次排列在 $x+1$ 之后（但是不一定紧邻）。

#### 主动移动的贡献

**我们现在先只考虑每一步都仅仅只有主动移动的情况。**

假设原序列中 $x$ 在 $p$ 号位置，则现在其所在的位置为 $\sum_{i=0}^{p-1}[a_i<x]$，对答案有 $1+\sum_{i=0}^{p-1}[a_i<x]$ 的贡献。

问题是，现在 $x+1$ 在哪里是未知的，不妨假设现在其在 $t$ 号位置，显然 $t\le x$；因此容易发现，总存在一个位置 $q$，使得 $\sum_{i=0}^{q-1}[a_i<x+1]=t$。因此我们得到，现在的 $x+1$ 的位置就**等效**于原序列中的 $q$ 号位置，因为我们可以使用与 $x$ 相同形式的公式来从位置 $q$ 推算出 $x+1$ 现在所在位置 $t$。为了后面 dp 方便，我们这里采用 $q$ 来描述其目前位置。

这样，此次移动总贡献容易发现即为 $\sum_{i=0}^{p-1}[a_i<x]+\sum_{i=0}^{q-1}[a_i<x+1]+1$。

问题是，这个**等效坐标** $q$ 怎么选取呢？或者说，如果把 $q$ 记入状态，那么状态怎么转移呢？

答案是，直接用现在的 $q$ 做新的 $q$！

为什么？

考虑到移动相对位置不方便，我们考虑把问题转化为等效的**绝对坐标**，然后说明**绝对坐标**就是一个合法的**等效坐标**。

譬如，如果当前序列为

$$\begin{array}{|c|c|c|c|c|c|}2&1&4&0&3&5\end{array}$$

考虑保留格子，而仅修改每个元素的位置。

$$\begin{array}{|c|c|c|c|c|c|}2&1&\varnothing&0&3&4,5\end{array}$$

$$\begin{array}{|c|c|c|c|c|c|}2&1&\varnothing&0&\varnothing&3,4,5\end{array}$$

$$\begin{array}{|c|c|c|c|c|c|}\varnothing&1&\varnothing&0&\varnothing&2,3,4,5\end{array}$$

$$\begin{array}{|c|c|c|c|c|c|}\varnothing&\varnothing&\varnothing&0&\varnothing&1,2,3,4,5\end{array}$$

$$\begin{array}{|c|c|c|c|c|c|}\varnothing&\varnothing&\varnothing&\varnothing&\varnothing&0,1,2,3,4,5\end{array}$$

这是连续做了 $5$ 次后的结果。

容易观察发现，由于考虑到 $x$ 放到 $x+1$ 前一位后，$t$ 不改变，而 $q$ 和 $t$ 的关系式中 $x+1$ 变为 $x$ 答案不变，于是 $q$ 可以保持相同。

简单说来，记考虑了 $x\sim n$，并且 $x$ 的等效坐标为 $q$ 的最优解为 $f(x,q)$，则贡献转移方向为

$$f(x,q)\leftarrow f(x+1,q)+\sum_{i=0}^{p-1}[a_i<x]+\sum_{i=0}^{q-1}[a_i<x+1]+1$$

为了再考虑到 $x$ 在 $x+1$ 右侧的情况，应当调整为

$$f(x,q)\leftarrow f(x+1,q)+\sum_{i=0}^{p-1}[a_i<x]+\sum_{i=0}^{q-1}[a_i<x]+2$$

#### 不选择移动的贡献

显然得有 $p<q$。否则最后不能自然拼合。

结论是类似的。

但是贡献不能单独计算本次的（本次本身没有贡献）。

考虑到会有将来的费用，考虑如何计入这部分贡献。

哪部分贡献呢？

其实考虑一下，会发现就是说，考虑到，我们上面的 dp 是建立在**每一步都仅仅只有主动移动**的基础上的，我们要通过附加的贡献，使得后面计算 $\sum_{i=0}^{p-1}[a_i<x]$ 的部分是等效正确的。

显然，要计算的贡献，即是在 $p$ 右边、$q$ 左边并且比 $x$ 小的数的数目。

也即，

$$f(x,p)\leftarrow f(x+1,q)+\sum_{p<i<q}[a_i<x]\quad(p<q)$$

但是很不幸，这是假的。

因为 $a_i$ 穿过时，还会多穿过 $a_i+1\sim x-1$，而这部分贡献我们刚刚没有统计！

于是即为

$$f(x,p)\leftarrow f(x+1,q)+\sum_{p<i<q}[a_i<x](x-a_i)\quad(p<q)$$

然后就好了。

### Code

Luogu 上的版本要输出方案，随便写一下就好了。

总复杂度 $O(n^2)$。

bzoj 上这个输出格式好神秘……

```cpp
// 那就是希望。
// 即便需要取模，也是光明。

#include <algorithm>
#include <stdio.h>
#include <vector>
typedef long long llt;
typedef unsigned uint;typedef unsigned long long ullt;
typedef bool bol;typedef char chr;typedef void voi;
typedef double dbl;
template<typename T>bol _max(T&a,T b){return(a<b)?a=b,true:false;}
template<typename T>bol _min(T&a,T b){return(b<a)?a=b,true:false;}
template<typename T>T lowbit(T n){return n&-n;}
template<typename T>T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T>T lcm(T a,T b){return(a!=0||b!=0)?a/gcd(a,b)*b:(T)0;}
template<typename T>T exgcd(T a,T b,T&x,T&y){if(b!=0){T ans=exgcd(b,a%b,y,x);y-=a/b*x;return ans;}else return y=0,x=1,a;}
template<typename T>T power(T base,T index,T mod)
{
    T ans=1%mod;
    while(index)
    {
        if(index&1)ans=ans*base%mod;
        base=base*base%mod,index>>=1;
    }
    return ans;
}
uint F[1005][1005],From[1005][1005];
uint A[1005],At[1005],Cnt[1005][1005];
const ullt inf=1e9;
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    // freopen("QAQ.out","w",stdout);
#endif
    uint n;scanf("%u",&n);for(uint i=0;i<n;i++)scanf("%u",A+i),A[i]++,At[i]=i;
    At[n]=n,std::sort(At,At+n+1,[](uint a,uint b){return A[a]>A[b];});
    for(uint i=0;i<=n;i++)A[At[i]]=i;
    for(uint i=0;i<=n;i++)for(uint j=0;j<=n;j++)Cnt[i][j+1]=Cnt[i][j]+(A[j]<i);
    for(uint i=0;i<n;i++)F[n][i]=inf;
    for(uint i=n-1;~i;i--){
        for(uint j=0;j<=n;j++)
            F[i][j]=F[i+1][j]+Cnt[i][At[i]]+Cnt[i][j]+2,From[i][j]=j;
        for(uint j=At[i]+1,v=0;j<=n;j++){
            if(_min(F[i][At[i]],F[i+1][j]+v))
                From[i][At[i]]=j;
            if(A[j]<i)v+=i-A[j];
        }
    }
    uint p=std::min_element(F[0],F[0]+n+1)-F[0];
    std::vector<std::pair<uint,uint> >Ans;std::vector<uint>P;
    for(uint i=0;P.push_back(p),i<n;i++)p=From[i][p];
    for(uint i=0;i<n;i++)if(P[i]==P[i+1]){
        uint p1=Cnt[i][At[i]],p2=Cnt[i+1][P[i+1]];
        for(uint j=i+1;j<=n;j++)p1+=P[j]<At[i];
        for(uint j=i+2;j<=n;j++)p2+=P[j]<P[i+1];
        if(p1<p2)Ans.push_back({p1,p2-1});
        else Ans.push_back({p1,p2});
    }
    std::reverse(Ans.begin(),Ans.end());printf("%u\n",(uint)Ans.size());
    for(auto s:Ans)printf("%u %u\n",s.first+1,s.second+1);
    return 0;
}

// 那就是希望。
// 即便需要取模，也是光明。
```




---

