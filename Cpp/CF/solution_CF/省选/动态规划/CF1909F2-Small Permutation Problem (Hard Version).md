# Small Permutation Problem (Hard Version)

## 题目描述

[Andy Tunstall - MiniBoss](https://soundcloud.com/tunners/miniboss)

⠀



In the easy version, the $ a_i $ are in the range $ [0, n] $ ; in the hard version, the $ a_i $ are in the range $ [-1, n] $ and the definition of good permutation is slightly different. You can make hacks only if all versions of the problem are solved.

You are given an integer $ n $ and an array $ a_1, a_2, \dots, a_n $ of integers in the range $ [-1, n] $ .

A permutation $ p_1, p_2, \dots, p_n $ of $ [1, 2, \dots, n] $ is good if, for each $ i $ , the following condition is true:

- if $ a_i \neq -1 $ , the number of values $ \leq i $ in $ [p_1, p_2, \dots, p_i] $ is exactly $ a_i $ .

Count the good permutations of $ [1, 2, \dots, n] $ , modulo $ 998\,244\,353 $ .

## 说明/提示

In the first test case, all the permutations of length $ 5 $ are good, so there are $ 120 $ good permutations.

In the second test case, the only good permutation is $ [1, 2, 3, 4, 5] $ .

In the third test case, there are $ 4 $ good permutations: $ [2, 1, 5, 6, 3, 4] $ , $ [2, 1, 5, 6, 4, 3] $ , $ [2, 1, 6, 5, 3, 4] $ , $ [2, 1, 6, 5, 4, 3] $ . For example, $ [2, 1, 5, 6, 3, 4] $ is good because:

- $ a_1 = 0 $ , and there are $ 0 $ values $ \leq 1 $ in $ [p_1] = [2] $ ;
- $ a_2 = 2 $ , and there are $ 2 $ values $ \leq 2 $ in $ [p_1, p_2] = [2, 1] $ ;
- $ a_3 = 2 $ , and there are $ 2 $ values $ \leq 3 $ in $ [p_1, p_2, p_3] = [2, 1, 5] $ ;
- $ a_4 = 2 $ , and there are $ 2 $ values $ \leq 4 $ in $ [p_1, p_2, p_3, p_4] = [2, 1, 5, 6] $ ;
- $ a_5 = -1 $ , so there are no restrictions on $ [p_1, p_2, p_3, p_4, p_5] $ ;
- $ a_6 = -1 $ , so there are no restrictions on $ [p_1, p_2, p_3, p_4, p_5, p_6] $ .

## 样例 #1

### 输入

```
10
5
-1 -1 -1 -1 -1
5
1 2 3 4 5
6
0 2 2 2 -1 -1
6
-1 -1 -1 -1 -1 5
6
-1 -1 3 2 -1 -1
15
0 0 -1 -1 -1 2 2 -1 -1 -1 -1 9 11 13 15
6
0 2 2 2 4 6
6
0 1 3 4 5 5
6
1 2 3 2 4 6
15
0 0 1 1 1 2 3 4 5 6 7 9 11 13 15```

### 输出

```
120
1
4
0
0
494403526
4
0
0
532305727```

# 题解

## 作者：ForgotDream_CHN (赞：12)

 **UPD on 2024.01.04：换了个图床，望过审。**

[在我的博客园中查看](https://www.cnblogs.com/forgot-dream/p/17926481.html)

> 给定一个长度为 $n$ 的数组 $a$，其中 $a_i \in [-1, n]$，试计算满足以下条件的 $[1, n]$ 的排列 $p$ 的个数：
>
> + $\forall i \in [1, n], \text{有 }\sum_{1 \le j \le i} [p_j \le i] = a_i \text{ 或 } a_i = -1$
>
> $n \le 2 \times 10^5$。

[Easy Version 传送门](https://www.cnblogs.com/forgot-dream/p/17926475.html)

硬版本跟简单版本的区别就在于，存在 $a_i = -1$，也就是对正方形内数字个数不做要求的情况。因此我们仍然可以借用简单版本的思路，将其放到二维平面上思考。

注意到 $a_i = -1$ 的 $i$ 对其他数字的放置不构成任何影响，那么我们只需要考虑 $a_i \neq -1$ 的 $i$ 即可。对于某个 $i$，设 $j < i$ 为离 $i$ 最近的 $a_j \neq -1$ 的 $j$（若不存在就设为 $0$）。我们发现此时 $d = a_i - a_j$ 不再满足 $d \in \{0, 1, 2\}$ 的限制，且 L 形的宽度不再为 $1$，因此好像不能借用 Easy Version 的思路分类讨论了。

举个例子，假设 $a_4 = 2, a_5 = -1, a_6 = 5$，我们现在在填 $i = 6$ 的格子，则有：

![](https://www.z4请更换图床a.net/images/2024/01/04/imagee10c976c8735b543.png)

此时 L 形的宽度为 $2$，且需要在 $i, p_i \le 4$ 的区域放置两个点，那么我们很容易知道会有两行与两列的点受到影响。我们不关心具体是哪两行两列无法放置点，因此不失一般性的，我们假设是 $1, 2$ 这两行两列无法放置。那么就有：

![](https://www.z4请更换图床a.net/images/2024/01/04/image0101c6a8551f2413.png)

只有图中红色的部分是可用的。进一步的，我们将红色的部分划分为两个区域：

![](https://www.z4请更换图床a.net/images/2024/01/04/image3e303c1c9c9ea2a2.png)

考虑枚举左边的矩形内放了多少个点，不妨设为 $k$ 个，我们仍然不关心其被放置的具体位置，只需要知道，每放置一个点，右边部分的可用行，也就是纵坐标，就会减少 $1$，那么我们可以将原问题抽象为在两个矩形内部放置点，例如，假设 $k = 1$，那么左边的矩形长宽不变，而右边的矩形长度就会减一，那么也就是在一个长宽均为 $2$ 的矩形（也就是左边的矩形）内部放置一个点，再在一个长为 $3$，宽为 $2$ 的矩形（也就是右边的矩形减掉一行）内部放置剩下的一个点。那么我们只需要知道在确定长宽的矩形内放置点的方案数即可。

设矩形的长为 $h$，宽为 $w$，需要放置的点数为 $k$，为了保证没有同一行或者同一列上被放置了超过一个点，就需要先选出 $k$ 个互不相同的行，方案数为 $\binom{w}{k}$，再选出 $k$ 个互不相同的列，方案数为 $\binom{h}{k}$，最后再把这 $k$ 行与 $k$ 列两两配对，方案数为 $k!$。综上，选点的方案数就为 $\binom{h}{k}\binom{w}{k}k!$。

形式化的，对于某一对 $i, j$，可以得到，左边的矩形的长宽分别为 $i - j, j - a_j$，而右边的矩形长宽就分别为 $i - j, i - a_j$。设在左边的矩形内选 $k$ 个点，则右边的矩形的长宽就会变为 $i - j, i - a_j - k$。因此，其方案数为：

$$
\sum_{0 \le k \le d} \left(\binom{i - j}{k} \binom{j - a_j}{k} k!\right) \left(\binom{i - j}{d - k} \binom{i - a_j - k}{d - k} (d - k)!\right)
$$

那么只需要按顺序枚举 $i$ 将每个 $i$ 对应的答案垒乘起来即可。由于 $\sum d = a_n - a_1 = \mathcal{O}(n)$，因此该做法的复杂度也是线性的。

[代码](https://codeforces.com/contest/1909/submission/238672452)


---

## 作者：EuphoricStar (赞：9)

感觉这个题还是挺不错的。

考虑 F1。考察 $a_i$ 差分后的意义，发现 $a_i - a_{i - 1}$ 就是 $(\sum\limits_{j = 1}^{i - 1} [p_j = i]) + p_i \le i$。

考虑将其转化为棋盘问题。在 $(i, p_i)$ 放一个车，那么 $a_i - a_{i - 1}$ 就是 $(1, i) \sim (i, i)$ 和 $(i, 1) \sim (i, i - 1)$ 这些格子组成的“L”字形的车的数量。

一个放车的方案合法当且仅当所有车互不攻击。因此容易发现合法的 $a_i - a_{i - 1}$ 一定 $\in [0, 2]$。考虑从前往后扫，同时维护答案 $ans$ 和现在还没被占用的行（列）数量 $t$。

- 若 $a_i = a_{i - 1}$，无事发生，多了第 $i$ 行和列没被占用，因此 $t \gets t + 1$。
- 若 $a_i - a_{i - 1} = 1$，相当于可以在 $(1, i) \sim (i - 1, i)$ 和 $(i, 1) \sim (i, i - 1)$ 中还没被占用的格子放车，同时也可以在 $(i, i)$ 放车，那么 $ans \gets ans \times (2t + 1)$，$t$ 不变。
- 若 $a_i - a_{i - 1} = 2$，$(1, i) \sim (i - 1, i)$ 和 $(i, 1) \sim (i, i - 1)$ 中还没被占用的格子各放一个车，那么 $ans \gets ans \times t^2$，然后 $t \gets t - 1$。

如上讨论可以[通过 F1](https://codeforces.com/contest/1909/submission/238617437)。

F2 我们继续将其放到棋盘上考虑。考虑一个 $a_i \ne -1$ 的位置 $i$，设它上一个 $a_j \ne -1$ 的位置是 $j$。现在相当于求在 $y \times y$ 的左下角抠掉了 $x \times x$ 的一块的“L”字形棋盘放 $t$ 个互不攻击的车的方案数，其中 $x = j - a_j, y = i - a_j, t = a_i - a_j$。每个这样的“L”字形互相独立，所以可以直接把方案乘起来。

上面的问题可以考虑容斥（我现在还不会不容斥的做法？）。相当于在左下角 $x \times x$ 的区域不能放车，那么我钦定 $i$ 个车放在了左下角，设 $F(n, m)$ 为 $n \times n$ 的棋盘放 $m$ 个互不攻击的车的方案数，那么这部分的方案为 $F(x, i) \times F(y - i, t - i)$，容斥系数为 $(-1)^i$，因此结果为：

$$\sum\limits_{i = 0}^t (-1)^i F(x, i) F(y - i, t - i)$$

最后一个问题是求 $F(n, m)$。考虑先选 $m$ 行放车，有 $\frac{n!}{(n - m)!}$ 种选列的方案，那么 $F(n, m) = \binom{n}{m} \times \frac{n!}{(n - m)!}$。

容易发现 $\sum t = n$，所以时间复杂度为 $O(n)$。

[code](https://codeforces.com/contest/1909/submission/238616142)

---

## 作者：Unnamed114514 (赞：2)

[F1](https://www.luogu.com.cn/article/vbys8lu0)

考虑在 F1 上扩展。

先把 $a_n$ 判掉，即若 $a_n=-1$ 则 $a_n=n$。

对于每个 $a_i\ne -1$ 的 $i$，找到上一个 $lst$ 且 $a_{lst}\ne 0$。

延续刚才的思路，现在的问题是多了 $i-lst$ 行 $i-lst$ 列，然后放 $a_i-a_{lst}$ 颗棋子的方案数。

我们可以枚举左下角即 $(i-lst)\times lst$ 的矩阵中放了 $j$ 个，注意只有 $lst-a_{lst}$ 可以选，即 $A_{i-lst}^j\times C_{lst-a_{lst}}^j$。即先选 $j$ 列出来，然后 $i-lst$ 行每一列可以随便选。

右边就选 $a_i-a_{lst}-j$ 颗棋子，同理可以推出是 $C_{i-lst}^{a_i-a_{lst}-j}\times A_{i-j-a_{lst}}^{y-j}$。

直接枚举是 $O(\sum d)=O(n)$ 的。

---

## 作者：User_Unauthorized (赞：2)

若 $a_i \neq -1$，设 $j$ 是小于 $i$ 中最大的满足 $a_j \neq -1$ 的数。那么也就是在 $i$ 之前排列中需要多出 $d = a_i - a_j$ 个 $\le i$ 的数。

考虑将数进行分类，在 $\left[1, j\right]$ 中的数不能放在下标 $\left[1, j\right]$ 中，否则会导致 $a_j$ 改变，因此其只能放在 $\left(j, i\right]$ 中。而在 $\left(j, i\right]$ 中的数可以放在 $\left[1, i\right]$ 中的任意位置。

为了避免重复，我们可以先放 $\left[1, j\right]$ 中的数，再放 $\left(j, i\right]$ 中的数，这样就不会重复了。故枚举 $k$ 代表放了多少个 $\left[1, j\right]$ 中的数，这部分的方案数为

$$\dbinom{i - j}{k}\dbinom{j - a_j}{k} k!$$

接下来我们需要放 $d - k$ 个在 $\left(j, i\right]$ 中的数，这部分的方案数为

$$\dbinom{i - a_j - k}{d - k}\dbinom{i - j}{d - k}\left(d - k\right)!$$

$a_i$ 产生的贡献为

$$\sum\limits_{0 \le k \le d}\dbinom{i - j}{k}\dbinom{j - a_j}{k} k!\dbinom{i - a_j - k}{d - k}\dbinom{i - j}{d - k}\left(d - k\right)!$$

由于 $\sum d = n$，因此总复杂度为 $\mathcal{O}(n)$。

---

## 作者：xsap (赞：2)

好像赛时 F1 做麻烦了，不过这个 F1 的解法能比较轻松的推广到 F2。首先考虑 F1，首先 $a_n=n$，然后不妨让 $a_0=0$，合法的 $a$ 数组中，$a_i-a_{i-1}=0/1/2$。差分数组中第 $i$ 位一个位置的值对应了一个对原排列中出现在 $i$ 位的数的约束以及一个对原排列中 $i$ 出现的位置的约束。

具体的，假设原排列为 $p$，讨论三种情况：
- 如果 $a_i-a_{i-1}=0$，则 $p_i>i$，且 $i$ 在排列 $p$ 中出现位置是在第 $i$ 个位置后面。
- 如果 $a_i-a_{i-1}=2$，则 $p_i<i$，且 $i$ 在排列 $p$ 中出现位置是在第 $i$ 个位置前面。
- 如果 $a_i-a_{i-1}=1$，此时有三种可能。要么 $p_i>i$，且 $i$ 出现在第 $i$ 个位置前面，要么 $p_i=i$，要么 $p_i<i$，且 $i$ 出现在第 $i$ 个位置后面。

先只考虑前两种比较简单的情况，比如对于一个 $a_i-a_{i-1}=0$ 的 $i$，第 i 个位置如果填了 $j$，则 $j>i$ 且 $a_j-a_{j-1}=2$，且满足这个条件的 $j$ 一定能被填在 $i$ 位置。因此如果对每个 $i$ 维护一个合法的 $j$ 的集合，那么对于两个位置 $i_1<i_2$，$i_1$ 的集合一定包含了 $i_2$ 的集合。因此从右往左扫，扫到一个 $a_i-a_{i-1}=2$ 的位置就给计数器加一，然后扫到 $a_i-a_{i-1}=0$ 时，将答案乘上计数器，表示选这个 $i$ 的方案，然后要将计数器减一，因为这个位置选了的数不能再被后面的数选了。对于 $a_i-a_{i-1}=2$ 的就正着扫一遍，然后这个的计数器在 $a_i-a_{i-1}=2$ 的时候加一就可以了。

再考虑 $a_i-a_{i-1}=1$ 的 $i$，此时有三种可能的情况但是经过讨论不难发现这三种情况都不会对计数器的值发生改变，因此只需要乘上两次扫到 $i$ 时计数器的和加一就可以了。

----------------
对于 F2，考虑怎么解决 $a_i=-1$ 的情况。类似上面的讨论，我们还是尝试用正着扫一边反着扫一遍分别维护计数器来计算答案。

考虑相邻两个有约束的位置 $j<i$，$a_i$ 与 $a_j$ 的差是怎么产生的。一部分是 $(j,i]$ 的位置中填了 $[1,i]$ 的数，一部分是 $[1,j]$ 的位置中填了 $(j,i]$的数。设 $a_i-a_j=d$，$i-j=len$，假设第一种有 $x$ 个，则第二种应该有 $d-x$ 个。也就是说，$(j,i]$ 中填的数应该是 $x$ 个 $[1,i]$ 的数，$len-x$ 个 $(i,n]$ 的数。$(j,i]$ 中的数应该有 $d-x$ 个被填到了 $[1,j]$ 中，$len-d+x$ 个被填到了 $(j,n]$ 中。对于不同的 $x$，我们发现他们对于正反两个计数器的影响实际上是相同的，一个是加 $len-d$，一个是加 $d-len$。因此不管其他位置的 $x$ 是什么，每个位置两次扫到他时的计数器都是一定的，可以预处理出来。

对每个相邻的 $j<i$ 考虑计算他对答案的贡献，枚举 $x$，那首先决定填在 $(j,i]$ 中哪些位置填的数是 $[1,i]$ 的方案是 $len\choose{x}$，同样决定后面部分会带来贡献 $len\choose{d-x}$。此外还需要计算具体填 $(j,i]$ 之间的数的方案数，假设正着扫的计数器为 $cnt1$，反着扫的计数器为 $cnt2$，则这一部分的贡献为 $A_{cnt1+len-d+x}^{x}\times A_{cnt2}^{len-x}$。对每个 $x$ 计算这三个东西的乘积再求和就是 $(j,i]$ 的贡献，最终答案就是所有的贡献之积。

---

## 作者：_yi_ (赞：1)

# 题意简述

题目要求计算给定条件下的好排列的数量。好排列的定义是：对于序列 $a$ 中的每个元素 $a_i$，如果 $a_i \neq -1$，则排列 $p$ 中前 $i$ 个元素中小于等于 $i$ 的数的个数必须等于 $a_i$。

# 解题思路

由 Easy Version 的做法可以拓展而来，我们可以将 $p_i$ 转化为点对 $(i,p_i)$，则 $ a_i $ 描述的是横坐标小于 $i$，纵坐标小于 $ a_i $ 的点的个数。（详情可以看这篇[题解](https://www.luogu.com.cn/article/jaankt9d)）

考虑将连续的一段 $a_i=-1$ 一起统计，这是由于 $a_i=-1$ 没有意义，我们将其视为一个整体，这样我们就可以将问题由 $i$ 转移到 $i+1$ 转化为由 $i$ 转移到 $i+j+1$。（$j$ 为这一段连续的 $a_i=-1$ 的长度）

考虑转移，可以仿照一位位转移的方法，进行区间转移假设我们当前要从 $x_1$ 转移到 $x_2$，令 $y_1=a_{x_1},y_2=a_{x_2}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/iujngg5l.png)

~~笔者最开始考虑枚举图中红色部分有多少个点，但发现要推出转移式子还需要枚举绿色部分中有多少个点，这样时间复杂度不对。~~

可以枚举绿色部分中有 $i$ 个点。（$0\le i\le x_2-x_1$）

那么，红色部分和黄色部分就有 $y_2-y_1-i$ 个点。那么转移为：

$f(x_2)=f(x_1)\times \sum_{i=0}^{x_2-x_1}\binom{x_2-x_1}{i}\binom{x_1-y_1}{i}i!\binom{x_2-y_1-i}{y_2-y_1-i}\binom{x_2-x_1}{y_2-y_1-i}(y_2-y_1-i)!$

其中 $\binom{x_2-x_1}{i}\binom{x_1-y_1}{i}i!$ 的意思是在绿色的块内选取 $i$ 行和 $i$ 列，行和列之间的排列还需乘上 $i!$，剩下的 $\binom{x_2-y_1-i}{y_2-y_1-i}\binom{x_2-x_1}{y_2-y_1-i}(y_2-y_1-i)!$ 是指在红色和蓝色块中选取，意义和在绿色块中选取一样。

这样就可以 $O(n)$ 做完了。

**注意：$a_n=n$ 时或 $a_n=-1$ 本题才有解，注意特判一下并把 $a_n$ 赋值为 $n$。**

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5;
const ll mod=998'244'353;
ll pow(ll a,ll b,ll p){
    ll res=1;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }return res;
}
ll v[N+2],inv[N+2];
int a[N+2];
ll C(int n,int m){
    if(m>n||m<0||n<0){
        return 0;
    }
    return v[n]*inv[m]%mod*inv[n-m]%mod;
}
int main(){
    // freopen("data.in","r",stdin);
    cin.tie(0)->sync_with_stdio(0);
    v[0]=1;
    for(int i=1;i<=N;i++){
        v[i]=v[i-1]*i%mod;//组合数
    }
    inv[N]=pow(v[N],mod-2,mod);
    for(int i=N-1;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%mod;//逆元
    }
    int T;
    cin>>T;
    while(T--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        if(a[n]!=-1&&a[n]!=n){
            cout<<"0\n";
            continue;
        }
        a[n]=n;
        ll ans=1;
        for(int i=1;i<=n;i++){
            int t=i;
            while(i<n&&a[i]==-1){
                i++;
            }
            ll temp=0;
            ll x1=t-1,y1=a[t-1],x2=i,y2=a[i];
            for(int j=0;j<=x2-x1;j++){
                ll t1=C(x2-x1,j)*C(x1-y1,j)%mod*v[j]%mod,t2=C(x2-y1-j,y2-y1-j)*C(x2-x1,y2-y1-j)%mod*v[y2-y1-j]%mod;
                temp=(temp+t1*t2%mod)%mod;
            }
            ans=ans*temp%mod;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：Graphcity (赞：0)

首先考虑 Easy Version。我们在一个 $n\times n$ 的网格上考虑问题。一个排列相当于每行每列恰好放上一个棋子的方案，也可以看作行和列之间匹配的方案。

那么对于 $a_i$ 的限制，就相当于在前 $i$ 行，前 $i$ 列一共形成了 $a_i$ 对匹配。显然有 $a_i\le a_{i+1}$，$a_i\le i$ 以及 $a_n=n$。令 $a_i-a_{i-1}=d_i$，那么 $d_i$ 的意义就是第 $i$ 行和第 $i$ 列共有 $d_i$ 个棋子。考虑依次扫描 $i=1,2,\cdots n$ 并更新答案。

设 $k$ 表示当前暂未匹配的行 / 列数（注意未匹配的行和列数量肯定相等），扫描到 $i$ 时，如果 $d_i=0$，那么 $k\gets k+1$，答案不变；如果 $d_i=1$，那么当前这一列放置恰好一个棋子的方案有 $2k-1$ 种，同时 $k$ 不变；否则，放置恰好两个棋子的方案有 $k^2$ 种，同时 $k\gets k-1$。用乘法原理把这些数乘起来就可以得到答案，时间复杂度 $O(n)$。

然后是 Hard Version。首先注意到一点，那就是 $k=i-a_i$。我们对于两个相邻且已知的 $(a_{pre},a_i]$ 这段区间进行讨论。我们知道 $k$ 的变化量 $\Delta k$，新增的行 / 列数 $\Delta i$，以及新增的棋子数量 $\Delta d$。

我们需要做的，就是在一个 $(\Delta k+\Delta i)\times(\Delta k+\Delta i)$ 的棋盘上放置 $\Delta d$ 个棋子，且前面 $\Delta k$ 行 $\Delta k$ 列不能放置棋子。注意到这个限制，我们考虑进行容斥。钦定前面的部分有 $p$ 个棋子，那么容斥系数就是 $(-1)^{p-1}$，方案数就是 $\dbinom{\Delta k}{p}^2p!\times\dbinom{\Delta k+\Delta i-p}{\Delta d-p}^2(\Delta d-p)!$ 种。注意到 $\Delta d$ 的总和是 $O(n)$ 级别的，所以我们枚举 $p$ 的总时间复杂度仍然是 $O(n)$ 级别。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=4e5,Mod=998244353;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,a[Maxn+5],fac[Maxn+5],inv[Maxn+5];
inline int C(int x,int y) {return (x<y || y<0)?0:1ll*fac[x]*inv[x-y]%Mod*inv[y]%Mod;}
inline void Solve()
{
    cin>>n; For(i,1,n) cin>>a[i]; if(a[n]==-1) a[n]=n;
    if(a[n]!=n) {puts("0"); return;}
    For(i,1,n) if(a[i]>i) {puts("0"); return;}
    int ans=1,pr=0;
    For(i,1,n) if(a[i]!=-1)
    {
        if(a[i]<a[pr]) {puts("0"); return;}
        int k=pr-a[pr],w=i-pr,d=a[i]-a[pr],cur=0;
        For(j,0,d)
        {
            int s1=1ll*C(k,j)*C(k,j)%Mod*fac[j]%Mod;
            int s2=1ll*C(k+w-j,d-j)*C(k+w-j,d-j)%Mod*fac[d-j]%Mod;
            if(j&1) cur=(cur-1ll*s1*s2%Mod+Mod)%Mod;
            else cur=(cur+1ll*s1*s2)%Mod;
        } ans=1ll*ans*cur%Mod,pr=i;
    } cout<<ans<<endl;
}

int main()
{
    int T; cin>>T; fac[0]=inv[0]=1;
    For(i,1,Maxn) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[Maxn]=Pow(fac[Maxn],Mod-2);
    Rof(i,Maxn-1,1) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
    while(T--) Solve();    
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先考虑 easy version。考虑 $i\to i+1$ 时，$a_i\to a_{i+1}$ 会如何变化。

结论：变化量至多为 $2$。

证明：首先 $p_{i+1}$ 位置至多贡献一个。其次 $p_i\sim p_{i}$ 由于限制从 $i$ 变成了 $i+1$，也至多贡献一个。故变化量至多为 $2$。

考虑对于每种变化量分别考虑：

* 变化量为 $0$ 时，该位置选择了一个大于等于 $i+1$ 的数，我们放到后面考虑。
* 变化量为 $1$ 时，有三种情况：前面选择了 $i+1$，$i+1$ 位置选择一个小于 $i+1$ 的数，$i+1$ 位置选择了 $i+1$。于是转移系数是 $2(a_i-i)+1$。
* 变化量为 $2$ 时，一定是前面选择了 $i+1$ 且 $i+1$ 位置选择了小于 $i+1$ 的数。于是转移系数为 $(a_i-i)^2$。

考虑 hard version。忽略 $-1$。考虑跳了 $j_2$ 个位置，$a_i$ 增加量为 $k$ 的情况。枚举有多少前面的位置选了两个位置之间的量，可以计算出两个位置之间有多少位置选择了前面的值。设前面空位置为 $j_1$，前面选择了 $k_1$ 作为添加量，后面选了 $k_2$ 作为添加量，那么转移系数就是 $\binom{j_2}{k_1}\binom{j_1}{k_1}\binom{j_1+j_2-k_1}{k_2}\binom{j_2}{k_2}k_1!k_2!$。

总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
const int mod=998244353;
//Combinatorics
int qp(int a,int b){
	if(b<0){
		return qp(qp(a,mod-2),-b);
	}
	int ans=1;
	while(b){
		if(b&1) (ans*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return ans;
}
int fac[3000005],inv[3000005];
void init(){
	fac[0]=1; for(int i=1;i<=3000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[3000000]=qp(fac[3000000],mod-2); for(int i=2999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[j]%mod*inv[i-j]%mod;
}
//Fast input/output
int read(){
	char c; int ans=0; int z=1;
	while(!isdigit(c=getchar()))z-=2*(c=='-');
	do{ans=(ans*10+c-'0');}while(isdigit(c=getchar()));
	return ans*z;
}
void print(int x){
	if(x<0) putchar('-');
	if(llabs(x)>=10) print(llabs(x)/10);
	putchar((llabs(x)%10)+'0');
}
void endl(){
	putchar(10);
}
signed main(){
	init();
	int t; cin>>t;
	while(t--){
		int n; cin>>n; int a[n+1]; for(int i=1;i<=n;i++) cin>>a[i]; a[0]=0;
		if(a[n]!=n&&a[n]!=-1){
			cout<<0<<"\n";
			continue;
		}
		a[n]=n;
		int ans=1;
		for(int i=0;i<n;){
			int j=i+1;
			while(a[j]==-1) j++;
			//addpos=j-i, addval=a[j]-a[i]
			//choose k in i+1~j and put in 1~i
			int tmp=0;
			for(int k=0;k<=min(j-i,a[j]-a[i]);k++){
				int l=a[j]-a[i]-k;
				(tmp+=C(j-i,k)*C(i-a[i],k)%mod*C(j-a[i]-k,l)%mod*C(j-i,l)%mod*fac[k]%mod*fac[l]%mod)%=mod;
			}
			(ans*=tmp)%=mod;
			i=j;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

