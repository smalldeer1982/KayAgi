# [ABC313F] Flip Machines

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc313/tasks/abc313_f

$ 1 $ から $ N $ までの番号が付けられた $ N $ 枚のカードがあります。 カードのそれぞれの面には整数が書かれており、カード $ i $ の表には $ A_i $ が、裏には $ B_i $ が書かれています。 最初、全てのカードは表を向いています。

今ここに $ M $ 台のマシーンがあり、$ 1 $ から $ M $ までの番号が付けられています。 マシーン $ j $ は（相異なるとは限らない）$ 2 $ つの $ 1 $ 以上 $ N $ 以下の整数 $ X_j,Y_j $ を持っており、マシーン $ j $ が起動されると、 $ \frac{1}{2} $ の確率でカード $ X_j $ を、残りの $ \frac{1}{2} $ の確率でカード $ Y_j $ を裏返します。 この確率は各起動ごとに独立です。

すぬけくんは今から以下の操作を順に行います。

1. $ 1 $ 以上 $ M $ 以下の整数からなる集合 $ S $ を選ぶ。
2. $ S $ に含まれる番号のマシーンを、番号が小さい順に $ 1 $ 度ずつ起動する。
 
すぬけくんがうまく $ S $ を選んだとき、「すべての操作が終了した後に各カードが向いている面に書かれた整数の合計」の期待値が最大でいくつになるか求めてください。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 40 $
- $ 1\leq\ M\ \leq\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ 10^4 $
- $ 1\leq\ X_j,Y_j\ \leq\ N $
- 入力は全て整数
 
### Sample Explanation 1

$ S $ として空集合を選んだ場合、どのマシーンも起動されないので、「すべての操作が終了した後に各カードが向いている面に書かれた整数の合計」の期待値は $ 3+10+5=18 $ です。 $ S $ として $ \lbrace\ 1\ \rbrace $ を選んだ場合、マシーン $ 1 $ が起動され、 - カード $ X_1\ =\ 1 $ が裏返された場合、「すべての操作が終了した後に各カードが向いている面に書かれた整数の合計」は $ 10+10+5=25 $ - カード $ Y_1\ =\ 2 $ が裏返された場合、「すべての操作が終了した後に各カードが向いている面に書かれた整数の合計」は $ 3+6+5=14 $ なので、その期待値は $ \frac{25+14}{2}\ =\ 19.5 $ です。 よって、「すべての操作が終了した後に各カードが向いている面に書かれた整数の合計」の期待値の最大値は $ 19.5 $ です。

### Sample Explanation 2

同じ $ (X_j,Y_j) $ を持つマシーンが複数存在することもあります。

## 样例 #1

### 输入

```
3 1
3 10
10 6
5 2
1 2```

### 输出

```
19.500000```

## 样例 #2

### 输入

```
1 3
5 100
1 1
1 1
1 1```

### 输出

```
100.000000```

## 样例 #3

### 输入

```
8 10
6918 9211
16 1868
3857 8537
3340 8506
6263 7940
1449 4593
5902 1932
310 6991
4 4
8 6
3 5
1 1
4 2
5 6
7 5
3 3
1 5
3 1```

### 输出

```
45945.000000```

# 题解

## 作者：Purslane (赞：4)

# Solution

看到 $n \le 40$，大概是 $O(n^5)$ 或者 $O(2^{\frac{n}{2}})$ 的。

首先分析一下，如果 $x_i=y_i$，那么这次是肯定翻转的。否则，一个卡只要被操作一次，其正反的概率都是 $\frac{1}{2}$，期望是 $\frac{a+b}{2}$。

对于所有的 $x_i=y_i$，如果 $a_i \le b_i$，我们一定翻转，这样不劣，然后就不用管这种操作了，因为叠加态翻转一次还是叠加态。

然后每个数都有一个值 $a$，翻转之后会得到 $\frac{a+b}{2}$，当 $b\ge a$ 时翻转更优，否则翻转更劣。

因此我们可以把每个数塞到两个集合中去：集合 $X$，表示翻转更优；集合 $Y$，表示翻转更劣。把每个操作当做节点的连边。

如果边的两端都在集合 $Y$ 中，那么一定没用；两端都在 $X$ 中，一定要翻转；比较难以处理的是跨两个集合的。

可以想到两种做法：

- 暴力枚举 $Y$ 集合中的点哪些被选中了，和他们相连的 $X$ 集合的点一定可以选。这样的复杂度为 $O(n \times 2^{|Y|})$。
- 状压 DP 记录 $dp_{i,S}$ 为 $Y$ 集合前 $i$ 个数中，集合 $X$ 的子集 $S$ 被选中所带来的 $Y$ 集合的最大期望。最后统计时加上 $X$。这样复杂度为 $O(n \times 2^{|X|})$。（因为你转移的时候选了 $Y_i$ 在集合 $X$ 应当选所有与 $Y_i$ 相连的。）

容易发现，$\min \{|X|,|Y|\} \le \frac{n}{2}$。选择更优的那个能做到 $O(n \times 2^{\frac{n}{2}})$。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=40+5,MAXM=1e5+10;
int n,m,id[MAXN],flg[MAXN],a[MAXN],b[MAXN],x[MAXM],y[MAXM];
int dp[MAXN][1<<21]; 
vector<int> s1,s2; 
map<pair<int,int>,int> mp;
vector<int> G[MAXN];
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	ffor(i,1,n) cin>>a[i]>>b[i],a[i]*=2,b[i]*=2;
	ffor(i,1,m) cin>>x[i]>>y[i];
	ffor(i,1,m) if(x[i]==y[i]) {if(a[x[i]]<b[x[i]]) swap(a[x[i]],b[x[i]]);} 
	else if(!mp[{min(x[i],y[i]),max(x[i],y[i])}]) mp[{min(x[i],y[i]),max(x[i],y[i])}]=1,G[x[i]].push_back(y[i]),G[y[i]].push_back(x[i]);
	ffor(i,1,n) if(a[i]<b[i]) s1.push_back(i),id[i]=s1.size(); else s2.push_back(i),id[i]=-s2.size();
	ffor(i,1,m) if(x[i]!=y[i]) if(id[x[i]]>0&&id[y[i]]>0) flg[x[i]]=flg[y[i]]=1;
	if(s1.size()<=s2.size()) {
		memset(dp,-0x3f,sizeof(dp));
		dp[0][0]=0;
		int all=(1<<s1.size())-1;
		ffor(i,1,n) {
			if(id[i]>0) ffor(j,0,all) dp[i][j]=dp[i-1][j];
			else {
				int st=0;
				for(auto v:G[i]) if(id[v]>0) st|=(1<<(id[v]-1));
				ffor(j,0,all) dp[i][j]=max(dp[i][j],dp[i-1][j]+a[i]),dp[i][j|st]=max(dp[i][j|st],dp[i-1][j]+(a[i]+b[i])/2);
			}
		}
		int ans=0;
		ffor(i,0,all) {
			int tans=dp[n][i];
			ffor(j,1,s1.size()) if((i&(1<<j-1))||flg[s1[j-1]]) tans+=(a[s1[j-1]]+b[s1[j-1]])/2; else tans+=a[s1[j-1]];
			ans=max(ans,tans);	
		}
		cout<<fixed<<setprecision(10)<<ans/2.0;
	}
	else {
		int ans=0,all=(1<<s2.size())-1;
		ffor(i,0,all) {
			long long st=0;
			ffor(j,1,s2.size()) if(i&(1<<j-1)) {for(auto v:G[s2[j-1]]) if(id[v]>0) st|=(1ll<<id[v]-1);}
			int tans=0;
			ffor(j,1,n) if(id[j]>0) {if((st&(1ll<<id[j]-1))||flg[j]) tans+=(a[j]+b[j])/2; else tans+=a[j];}
			else {if(i&(1<<(-id[j]-1))) tans+=(a[j]+b[j])/2; else tans+=a[j];}
			ans=max(ans,tans);
		}
		cout<<fixed<<setprecision(10)<<ans/2.0;
	}
	return 0;
}
```

有一个坑点在于如果你用二进制压位，那么很有可能超过 $30$ 个元素，然后爆 long long 了。

---

## 作者：_jimmywang_ (赞：3)

一种很新的折半/根号分治。

~~手玩一下~~可以证明一个机器集合 $S$ 的期望，先把 $S$ 中 $x=y$ 的机器对应的卡片翻好面，对于剩下的机器，如果一张卡片被至少一个机器覆盖过（即 $x=i$ 或 $y=i$），那么它的期望是 $\dfrac{a+b}{2}$，否则就是 $a$。

首先把 $x_i=y_i$ 的机器处理掉，如果 $a_{x_i}<b_{x_i}$，那就直接交换。然后就可以不管这些东西了。毕竟再翻只会使期望变小。

现在只考虑 $x\not =y$ 的机器。

将 $a_i\ge b_i$ 的卡片记为集合 $P$，剩下的为 $Q$。覆盖一张卡的贡献是 $\dfrac{b_i-a_i}{2}$。

首先有一个观察：

- 覆盖 $Q$ 中点优于覆盖 $P$ 中点。

- 对于 $x_i\in P,y_i\in P$，这个机器永远不用。

- 对于 $x_i\in Q,y_i\in Q$，这个机器必然使用。（这里官方题解好像写错了）

下面将 $x\in Q,y\in P$ 的机器交换 $x,y$，变为 $x\in P,y\in Q$。

接下来介绍两种做法：

#### $1.$

暴力枚举 $P$ 中被覆盖的点的集合 $S$，因为覆盖 $Q$ 中的点优于覆盖 $P$ 中的点，所以所有 $x\in S,y\in Q$ 的机器必选。

复杂度 $O(m+2^{|P|}n)$。

#### $2.$

进行 $dp$，记 $dp[i][j]$ 为处理完 $P$ 中前 $i$ 个点，当前 $Q$ 中选的集合为 $j$ 时，**$P$ 中已选的点的最大值**。

同上，可以预处理 $P$ 中每个点作为机器的 $x$ 时对应的 $y$ 的集合，只要选了这个点，必然覆盖所有的 $y$。

然后 $dp$ 完以后加上 $j$ 中点的贡献就行了。

复杂度 $O(m+2^{|Q|}n)$。

我们发现 $|P|+|Q|=n$，因此 $\min(|P|,|Q|)\le \dfrac{n}{2}$，根据两个集合的大小选择做法就可以了。

---

## 作者：FatOldEight (赞：2)

稍微参考了官方题解。
### 题意
给定 $n$ 张牌，正面的数为 $a_i$，背面的数为 $b_i$。

现在有 $m$ 个机器，参数为 $(x_i,y_i)$，有二分之一的概率翻转第 $x_i$ 牌，剩下的二分之一翻转第 $y_i$ 牌。

求出所有对于选取机器的集合 $S$ 中，使得所有牌正面的数之和的期望值最大。
### 思路
令最优的机器集合为 $S$。

首先，定义集合 $I=\{i\mid \exists\ j\in S,x_j=i\lor y_j=i\}$。

说人话就是只要牌 $i$ 可能被翻转，它就在 $I$ 里面。

易证如果一张牌可能被翻转，无论多少次，最后的正面的期望一定是 $\frac{a+b}{2}$。

所以令翻转一张牌的变化量 $d_i=a_i-\frac{a_i+b_i}{2}=\frac{a_i-b_i}{2}$。

最后的答案就为 $\sum_{i=1}^n{a_i}+\sum_{i\in I}{d_i}$。

现在问题就变成了求 $\max{\sum_{i\in I}d_i}$。

首先把 $x_i=y_i$ 的机器处理掉，如果 $a_{x_i}<b_{b_i}$，那就直接交换。然后就可以不管这些东西了，再翻只会使期望变小。

先钦定 $P=\{1\le i\le n\mid d_i<0\},Q=\{1\le i \le n\mid d_i\ge0\}$。

现在考虑机器。

对于机器 $i$，有三种可能：

1. $x_i\in Q\land y_i\in Q$，此时肯定要选；

2. $x_i\in P \land y_i\in P$，此时肯定不选；

3. 对于剩余情况，钦定 $x_i\in P,y_i\in Q$，否则交换 $x_i,y_i$。此时如果 $x_i\in I\cap P$，这个机器就一定要选。

因为选 $Q$ 集合里面的牌都不劣，所以当 $x_i\in P$ 被选中时，所有的在 $Q$ 中能选的 $y_i$ 都一并要选，于是可以建立一个映射 $ls_i$，代表如果选了 $i\in P$ 有哪些在 $Q$ 中的元素能选。

根据上文，发现只需要依据 $I\cap P$ 即可判断 $S$ 的集合。

所以我们只需要找出最优的 $I\cap P$ 即可。 （其实就是在 $P$ 里面选出最优的集合。）

有两种方法：

1. 暴力枚举 $I\cap P$。时间复杂度 $O(2^{|P|}n+m)$。

2. 使用 DP。令 $f_{i,S}$ 为处理了 $P$ 中前 $i$ 个牌，选择的 $Q$ 的集合为 $S$，$P$ 中选的牌的最大值。如果没选 $i$，就不管；如果选了，加上 $d_i$，$S\gets S \cup ls_i$。最后加上 $S$ 中元素的 $d_i$ 即可。时间复杂度 $O(2^{|S|}n+m)$。

因为 $|Q|+|P|=n$，所以 $\min\{|Q|,|P|\}\le \frac{n}{2}$，所以根据 $P,Q$ 集合大小判断使用哪个即可。

最终时间复杂度 $O(2^{\frac{n}{2}}n+m)$。
### code

```cpp
#include<cstring>
#include<iostream>
#include<vector>
#define int long long
using namespace std;
int a[100005],s[100005],x[100005],y[100005],n,m,ans,id[100005],ls[100005],f[100][1148576];
vector<int>Q,P;
signed main()
{
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i],&s[i]);
    for(int i=1;i<=m;i++)
    {
        scanf("%lld%lld",&x[i],&y[i]);
        if(x[i]==y[i]&&a[x[i]]<s[x[i]])swap(a[x[i]],s[y[i]]);
    }
    for(int i=1;i<=n;i++)
    {
        ans+=a[i]*2;
        int d=a[i]-s[i];
        if(d>=0)
        {
            id[i]=P.size();
            P.push_back(d);
        }
        else
        {
            id[i]=Q.size();
            Q.push_back(-d);
        }
    }
    for(int i=1;i<=m;i++)
    {
        int hx=(a[x[i]]>=s[x[i]]);
        int hy=(a[y[i]]>=s[y[i]]);
        if(hx==hy)
        {
            if(!hx)
            {
                ans+=Q[id[x[i]]]+Q[id[y[i]]];
                Q[id[x[i]]]=Q[id[y[i]]]=0;
            }
        }
        else
        {
            if(!hx)swap(x[i],y[i]);
            ls[id[x[i]]]|=1ll<<id[y[i]];
        }
    }
    if(P.size()<=Q.size())
    {
        int mx=0;
        for(int bit=0;bit<1ll<<(int)P.size();bit++)
        {
            int an=0,q=0;
            for(int i=0;i<(int)P.size();i++)
            {
                if(bit>>i&1)
                {
                    an-=P[i];
                    q|=ls[i];
                }
            }
            for(int i=0;i<(int)Q.size();i++)if(q>>i&1)an+=Q[i];
            mx=max(mx,an);
        }
        ans+=mx;
    }
    else
    {
        memset(f,0xc0,sizeof(f));
        f[0][0]=0;
        int mx=0;
        for(int i=0;i<(int)P.size();i++)
        {
            for(int j=0;j<1ll<<(int)Q.size();j++)
            {
                f[i+1][j]=max(f[i+1][j],f[i][j]);
                f[i+1][j|ls[i]]=max(f[i][j]-P[i],f[i+1][j|ls[i]]);
            }
        }
        for(int bit=0;bit<1ll<<(int)Q.size();bit++)
        {
            int an=f[(int)P.size()][bit];
            for(int i=0;i<(int)Q.size();i++)if(bit>>i&1)an+=Q[i];
            mx=max(mx,an);
        }
        ans+=mx;
    }
    printf("%lf",ans/2.0);
}
```


---

## 作者：LJ07 (赞：1)

有意思但不多。下文概率翻转表示有 $\frac{1}{2}$ 的概率翻转。

+ 如果一次操作 $(u,v)$（$u\not=v$），则之后这一对的答案的贡献为 $\frac{a_u+b_u+a_v+b_v}{2}=(\frac{a_u+b_u}{2})+(\frac{a_v+b_v}{2})$。相当于两次独立的概率翻转。多次概率翻转等价于一次概率翻转。
+ 那么一次操作 $(u,v)$（$u\not=v$）等价于给 $u$，$v$ 进行 $a\leftarrow \frac{a+b}{2}$ 赋值，同时每个点这样的过程只能进行一次。同时操作顺序与答案无关。

+ 怎么折半？贪心的可取之处？令 $a_i<b_i$ 为白牌，否则为黑牌。我们想要在*尽量不翻黑牌时多翻白牌*。那么只有 $(u_i,v_i)$ 为一黑一白时需特殊考虑。全白一定选，全黑一定不选。

+ 现在能折半了：如果白牌比较多，可以直接暴力枚举黑点被赋值的集合；如果黑牌比较多，可以设计 dp：$f_{i,S}$ 表示前 $i$ 张黑牌白点被赋值的集合为 $S$，转移类似 $0/1$ 背包。

+ 如果存在 $u=v$？那就能稳定 $a_i\leftarrow b_i$。那么就可以给 $u$ 一次白变黑的机会。然后再进行上述过程。

复杂度为 $O(n2^{\frac{n}{2}})$。

```cpp
const int N = 40, HN = 20, M = 1e5;
int n, m, a[N + 5], b[N + 5], c[N + 5];
int u[M + 5], v[M + 5];
int d[N + 5], f[1 << HN], g[1 << HN], ans;
bool o[N + 5];
vector<int> vb, vs;
long long is, os[N + 5];

int calc(long long s) {
  int res = 0;
  for (int i = 0; i < vs.size(); ++i) {
    res += (s >> i & 1) ? c[vs[i]] : a[vs[i]];
  }
  return res;
}

int main() {
//  freopen("input.in", "r", stdin);
  rd(n), rd(m);
  U(i, 1, n) {
    rd(a[i]), rd(b[i]);
    o[i] = b[i] > a[i];
  }
  U(i, 1, m) {
    rd(u[i]), rd(v[i]);
    if (u[i] == v[i]) {
      if (o[u[i]]) {
        o[u[i]] ^= 1;
        swap(a[u[i]], b[u[i]]);
      }
    }
  }
  U(i, 1, n) {
    c[i] = a[i] + b[i];
    a[i] <<= 1, b[i] <<= 1;
    auto &v = o[i] ? vs : vb;
    d[i] = v.size();
    v.emplace_back(i);
  }
  U(i, 1, m) {
    if (u[i] != v[i]) {
      if (o[u[i]] < o[v[i]]) {
        swap(u[i], v[i]);
      }
      if (o[v[i]]) {
        is |= (1ll << d[u[i]]) | (1ll << d[v[i]]);
      }else if (o[u[i]]) {
        os[d[v[i]]] |= 1ll << d[u[i]];
      }
    }
  }
  const int SM = vs.size(), BG = vb.size();
  if (SM < BG) {
    memset(f, -0x3f, sizeof f);
    f[is] = 0;
    U(i, 0, BG - 1) {
      swap(f, g);
      memset(f, -0x3f, sizeof f);
      for (int j = (1 << SM) - 1; ~j; --j) {
        f[j | os[i]] = max(f[j | os[i]], g[j] + c[vb[i]]);
        f[j] = max(f[j], g[j] + a[vb[i]]);
      }
    }
    U(i, 0, (1 << SM) - 1) {
      ans = max(ans, f[i] + calc(i));
    }
  } else {
    U(i, 0, (1 << BG) - 1) {
      long long s = is;
      int res = 0;
      U(j, 0, BG - 1) {
        if (i >> j & 1) {
          s |= os[j];
          res += c[vb[j]];
        }else {
          res += a[vb[j]];
        }
      }
      ans = max(ans, calc(s) + res);
    }
  }
  printf("%.12lf", ans / 2.);
  return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_abc313_f)

**题目大意**

> 给定 $n$ 个卡片，正面 $a_i$ 反面 $b_i$，第 $i$ 个操作以平均的概率反转 $u_i/v_i$，操作 $1\sim m$ 个中的若干个使得最终所有向上卡面的数之和期望最大。
>
> 数据范围：$n\le 40,m\le 10^5$。

**思路分析**

注意到每个被操作至少一次的卡最终期望总是 $\dfrac{a_i+b_i}2$。

特判 $u_i=v_i$ 的情况，如果 $a_i<b_i$ 加入集合 $S$，否则加入 $T$。

显然一个操作两端都在 $S$ 必操作，都在 $T$ 必不操作。

剩下的操作看成连接 $S,T$ 的边，然后讨论 $|S|$ 和 $|T|$ 大小关系：

- 如果 $|S|>|T|$，那么枚举 $|T|$ 中哪些数被操作了，那么所有与这些数相连的 $|S|$ 中的元素必被选，直接求和。
- 否则可以 dp，$f_{i,S}$ 表示 $T_1\sim T_i$ 选若干个使得邻域覆盖 $S$ 的最小代价，转移很简单。

时间复杂度 $\mathcal O(n2^{n/2})$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int inf=1e9;
int n,m,a[45],b[45],w[45],id[45],f[1<<20],g[1<<20];
ll adj[45];
bool e[45][45],del[45];
signed main() {
	scanf("%d%d",&n,&m);
	vector <int> U,V;
	for(int i=1;i<=n;++i) scanf("%d%d",&a[i],&b[i]);
	for(int i=1,x,y;i<=m;++i) {
		scanf("%d%d",&x,&y);
		if(x^y) e[x][y]=e[y][x]=true;
		else if(a[x]<=b[x]) swap(a[x],b[x]);
	}
	for(int i=1;i<=n;++i) {
		w[i]=b[i]-a[i];
		if(w[i]>=0) id[i]=U.size(),U.push_back(i);
		else id[i]=V.size(),V.push_back(i);
	}
	for(int x=1;x<=n;++x) for(int y=x+1;y<=n;++y) if(e[x][y]) {
		if(w[x]>=0&&w[y]>=0) del[x]=del[y]=true;
		else if(w[x]>=0) adj[y]|=1ll<<id[x];
		else if(w[y]>=0) adj[x]|=1ll<<id[y];
	}
	int vc=V.size(),uc=U.size(),ans=-inf;
	if(vc<uc) {
		for(int s=0;s<(1<<vc);++s) {
			int tmp=0; ll t=0;
			for(int i=1;i<=n;++i) if(w[i]<0&&(s&(1ll<<id[i]))) {
				tmp+=w[i],t|=adj[i];
			}
			for(int i=1;i<=n;++i) if(w[i]>=0&&((t&(1ll<<id[i]))||del[i])) tmp+=w[i];
			ans=max(ans,tmp);
		}
	} else {
		memset(f,-0x3f,sizeof(f));
		f[0]=0;
		for(int i=1;i<=n;++i) if(w[i]<0) {
			memcpy(g,f,sizeof(g));
			for(int s=0;s<(1<<uc);++s) g[s|adj[i]]=max(g[s|adj[i]],f[s]+w[i]);
			memcpy(f,g,sizeof(f));
		}
		for(int s=0;s<(1<<uc);++s) {
			int tmp=f[s];
			for(int i=1;i<=n;++i) if(w[i]>=0&&((s&(1ll<<id[i]))||del[i])) tmp+=w[i];
			ans=max(ans,tmp);
		}
	}
	for(int i=1;i<=n;++i) ans+=2*a[i];
	if(ans&1) printf("%d.5\n",ans/2);
	else printf("%d\n",ans/2);
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

我们将操作 $(x,y)$ 比作连接 $x,y$ 的无向边。

对于 $x=y$ 的边，它必然会翻转卡牌 $x$，那我们可以通过操作使得卡牌 $x$ 的最大值朝上。

接下来仅考虑 $x\not = y$ 的边。有一个重要观察：**若一个点 $i$ 有连边，则它的期望值必然为 $\dfrac{A_i+B_i}{2}$**。证明则考虑连接它的第一条边，翻转与不翻转的概率相等，且结果对称。

我们把点划分成两类：最小值朝上，此时连边更优，组成的集合为 $s_1$；最大值朝上，此时连边更劣，组成的集合为 $s_2$。

$s_1$ 内部的边必然相连，$s_2$ 内部的边必然不连，可以预处理。接下来仅考虑 $s_1,s_2$ 之间的边。若 $s_2$ 中的一个点有连边，则与它相连的所有边肯定全都被选。看到 $n=40=20\times 2$，不妨考虑折半搜索。

- $|s_1|\le |s_2|$

此时 $|s_1|\le 20$。我们设 $s_2$ 中的点 $i$ 有边连接到 $s_1$ 的点集为 $f_i$。我们需要找到 $s_2$ 中的一个子集 $t$，设 $r=\cup_{i\in t}f_i$，也就是 $t$ 的邻居集合，并最大化 $\sum_{i\in t}\Delta i+\sum_{i\in r}\Delta i$（此处 $\Delta i$ 为翻转 $i$ 后期望值的变化量）。这个可以通过状压 DP 解决。

- $|s_1|>|s_2|$

此时 $|s_2|< 20$。考虑直接 dfs $s_2$ 中被选的点，然后暴力计算即可。

```cpp
#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=40,Maxk=(1<<20);
const double inf=1e18;

int n,m,lim,g[Maxn+5][Maxn+5],col[Maxn+5],vis[Maxn+5];
double a[Maxn+5],b[Maxn+5],c[Maxn+5];
double dx[Maxn+5],f[Maxk+5],h[Maxk+5],ans,all;
vector<int> v1,v2;

inline void Solve1()
{
    int sz=v1.size(),p=0; lim=(1<<sz)-1;
    For(i,0,lim) f[i]=-inf;
    For(i,0,sz-1) if(vis[v1[i]]) p|=(1<<i); f[p]=0;
    For(i,0,sz-1) h[1<<i]=dx[v1[i]];
    For(i,1,lim) {int x=lowbit(i),y=(x^i); if(y) h[i]=h[x]+h[y];}
    for(auto i:v2)
    {
        int k=0; For(j,0,sz-1) if(g[i][v1[j]]) k|=(1<<j);
        For(j,0,lim-1) f[j|k]=max(f[j|k],f[j]+dx[i]);
    }
    For(i,0,lim) all=max(all,f[i]+h[i]);
    ans+=all;
}
inline double Count2(double res)
{for(auto i:v1) if(vis[i]) res+=dx[i]; return res;}
inline void dfs2(int x,double y)
{
    if(x==v2.size()) {all=max(all,Count2(y)); return;}
    for(auto i:v1) if(g[v2[x]][i]) vis[i]++;
    dfs2(x+1,y+dx[v2[x]]);
    for(auto i:v1) if(g[v2[x]][i]) vis[i]--;
    dfs2(x+1,y);
}
inline void Solve2() {dfs2(0,0),ans+=all;}

int main()
{
    scanf("%d%d",&n,&m);
    For(i,1,n) cin>>a[i]>>b[i],c[i]=(a[i]+b[i])/2.0;
    For(i,1,m)
    {
        int x,y; scanf("%d%d",&x,&y);
        if(x==y && a[x]<b[x]) swap(a[x],b[x]);
        if(x!=y) g[x][y]=g[y][x]=1;
    }
    For(i,1,n) if(a[i]<c[i]) v1.push_back(i);
               else v2.push_back(i),col[i]=1;
    For(i,1,n) ans+=a[i],dx[i]=c[i]-a[i];
    For(i,1,n) if(!col[i]) For(j,i+1,n) if(!col[j] && g[i][j]) vis[i]=vis[j]=1;
    if(v1.size()<=v2.size()) Solve1(); else Solve2();
    printf("%.10lf\n",ans);
    return 0;
}
```



---

## 作者：User_Unauthorized (赞：0)

## 题意

有 $N$ 张卡片，第 $i$ 张卡片正面印着一个数 $A_i$，反面印着一个数 $B_i$。一开始所有数正面朝上。

有 $M$ 种操作，第 $i$ 种操作表示为：

- $50\%$ 的概率将卡片 $X_i$ 翻转，否则将 $Y_i$ 翻转。

求一个集合 $S\subseteq \mathbb{N} \bigcap \left[1,M\right]$，使得进行了集合中所有的编号的操作之后正面朝上的所有数的和的期望最大。输出这个最大值。

（$1 \le N \le 40, 1 \le M \le 10^5$）。

## 题解

[$\tt{cnblogs}$](https://www.cnblogs.com/User-Unauthorized/p/solution-ABC313F.html)

首先可以发现若对于卡片 $i$，若有操作 $k$ 满足 $X_k = i$ 或 $Y_k = i$，那么其最终状态正反面概率相等，无论之前的状态如何。所以我们可以发现每个卡片只有被选择和不被选择两种可能，而每次操作为选择两个卡片，故我们可以尝试转化为图论问题，将操作视为边，将卡片视为节点。

现在我们的问题转化为了：给定一个无向图，每个点有点权，选择若干条边，使得覆盖的点权和最大。但是发现这样还不够，我们继续挖掘题目性质。可以发现

- 若有一条边连接了两个非负权的点，那么这条边一定入选；
- 如果一条边连接了两个负权的点，那么这条边一定不入选。

所以我们要处理的边还剩下两种情况：

- 连接了一个非负权和一个负权的点的边；
- 自环。

后者是好处理的，发现若一个节点被选择，那么其贡献期望为 $\dfrac{A_i + B_i}{2}$，若其不被选择，那么其贡献为 $A_i$，而形如自环的边可以让我们以百分百的概率翻转一条边，可以发现，若 $A_i < B_i$，那么翻转该卡片一定不劣，否则翻转一定不优。

现在我们只需要处理连接了一个非负权和一个负权的点的边，发现其形如二分图的形式，而两个部分的节点数之和一定不超过 $N$，设 $P$ 表示非负权点数量，$Q$ 表示负权点数量，那么我们可以得出 $\min\left\{P, Q\right\} \le \dfrac{N}{2} \le 20$，这启发我们去枚举较小的点集来解决问题。

### $P \ge Q$

我们考虑枚举负权点数量，由于在删点和删边操作后，图中只剩下了连接负权点和非负权点的边，也就是说与负权点相连的一定为非负权点，所以若有一个负权点被覆盖，覆盖所有与它相连的非负权点一定更优。得到负权点的策略后，通过枚举每个负权点是否被覆盖，我们可以得到最优解。

### $P < Q$

考虑状压，设 $f_S$ 代表覆盖点集 $S$ 的最优解，既然我们得到了负权点的策略，那么我们就可以快速的进行转移了。

两种算法的复杂度均为 $\mathcal{O}(2^{\frac{N}{2}} + N + M)$，可以通过本题。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef long double realType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;
typedef std::pair<valueType, valueType> ValuePair;
typedef std::vector<ValuePair> PairVector;
typedef std::vector<bool> bitset;

ValueVector count;

valueType dfs(valueType x, ValueVector const &C, ValueVector const &set, ValueMatrix const &G) {
    if (x == set.size())
        return 0;

    valueType ans = dfs(x + 1, C, set, G);

    valueType sum = C[set[x]];

    for (auto const &iter: G[set[x]]) {
        if (count[iter] == 0)
            sum += C[iter];

        ++count[iter];
    }

    sum += dfs(x + 1, C, set, G);

    for (auto const &iter: G[set[x]])
        --count[iter];

    return std::max(ans, sum);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N, M;

    std::cin >> N >> M;

    PairVector edge;

    ValueVector A(N), B(N);

    for (valueType i = 0; i < N; ++i)
        std::cin >> A[i] >> B[i];

    for (valueType i = 0; i < M; ++i) {
        valueType X, Y;

        std::cin >> X >> Y;

        --X;
        --Y;

        if (X == Y) {
            if (A[X] < B[X])
                std::swap(A[X], B[X]);

            continue;
        }

        edge.emplace_back(X, Y);
    }

    valueType const base = std::accumulate(A.begin(), A.end(), (valueType) 0);

    ValueVector C(N);

    for (valueType i = 0; i < N; ++i)
        C[i] = B[i] - A[i];

    bitset exist(N, true);
    ValueMatrix G(N);

    for (auto const &iter: edge) {
        if (C[iter.first] < 0 && C[iter.second] < 0)
            continue;

        if (C[iter.first] >= 0 && C[iter.second] >= 0) {
            exist[iter.first] = false;
            exist[iter.second] = false;

            continue;
        }

        if (!exist[iter.first] || !exist[iter.second])
            continue;

        if (C[iter.first] < 0)
            G[iter.first].push_back(iter.second);
        else
            G[iter.second].push_back(iter.first);
    }

    valueType ans = 0;
    valueType leftCount = 0, rightCount = 0;
    ValueVector rightSet, id(N), node(N);

    for (valueType i = 0; i < N; ++i) {
        if (!exist[i]) {
            ans += C[i];

            continue;
        }

        if (C[i] >= 0) {
            id[i] = leftCount;
            node[leftCount] = i;

            ++leftCount;
        } else {
            for (auto iter = G[i].begin(); iter != G[i].end();)
                if (!exist[*iter])
                    iter = G[i].erase(iter);
                else
                    ++iter;

            if (G[i].empty())
                continue;

            ++rightCount;

            rightSet.push_back(i);
        }
    }

    if (leftCount <= rightCount) {
        valueType const S = 1 << leftCount;

        ValueVector V(S, 0);

        for (valueType j = 0; j < S; ++j)
            for (valueType i = 0; i < leftCount; ++i)
                if (j & (1 << i))
                    V[j] += C[node[i]];

        ValueVector F(S, std::numeric_limits<valueType>::min() >> 1);

        F[0] = 0;

        for (auto const i: rightSet) {
            valueType bit = 0;

            for (auto const &iter: G[i])
                bit |= 1 << id[iter];

            for (valueType j = 0; j < S; ++j)
                F[j | bit] = std::max(F[j | bit], F[j] + C[i]);
        }

        valueType max = std::numeric_limits<valueType>::min();

        for (valueType i = 0; i < S; ++i)
            max = std::max(max, V[i] + F[i]);

        std::cout << std::fixed << std::setprecision(10) << (realType) (2 * base + ans + max) / 2.0 << std::endl;
    } else {
        count.resize(N, 0);

        std::cout << std::fixed << std::setprecision(10) << (realType) (2 * base + ans + dfs(0, C, rightSet, G)) / 2.0 << std::endl;
    }
}
```

---

