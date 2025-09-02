# Decreasing Debts

## 题目描述

There are $ n $ people in this world, conveniently numbered $ 1 $ through $ n $ . They are using burles to buy goods and services. Occasionally, a person might not have enough currency to buy what he wants or needs, so he borrows money from someone else, with the idea that he will repay the loan later with interest. Let $ d(a,b) $ denote the debt of $ a $ towards $ b $ , or $ 0 $ if there is no such debt.

Sometimes, this becomes very complex, as the person lending money can run into financial troubles before his debtor is able to repay his debt, and finds himself in the need of borrowing money.

When this process runs for a long enough time, it might happen that there are so many debts that they can be consolidated. There are two ways this can be done:

1. Let $ d(a,b) > 0 $ and $ d(c,d) > 0 $ such that $ a \neq c $ or $ b \neq d $ . We can decrease the $ d(a,b) $ and $ d(c,d) $ by $ z $ and increase $ d(c,b) $ and $ d(a,d) $ by $ z $ , where $ 0 < z \leq \min(d(a,b),d(c,d)) $ .
2. Let $ d(a,a) > 0 $ . We can set $ d(a,a) $ to $ 0 $ .

The total debt is defined as the sum of all debts:

 $ $$$\Sigma_d = \sum_{a,b} d(a,b) $ $$$

Your goal is to use the above rules in any order any number of times, to make the total debt as small as possible. Note that you don't have to minimise the number of non-zero debts, only the total debt.

## 说明/提示

In the first example the optimal sequence of operations can be the following:

1. Perform an operation of the first type with $ a = 1 $ , $ b = 2 $ , $ c = 2 $ , $ d = 3 $ and $ z = 5 $ . The resulting debts are: $ d(1, 2) = 5 $ , $ d(2, 2) = 5 $ , $ d(1, 3) = 5 $ , all other debts are $ 0 $ ;
2. Perform an operation of the second type with $ a = 2 $ . The resulting debts are: $ d(1, 2) = 5 $ , $ d(1, 3) = 5 $ , all other debts are $ 0 $ .

In the second example the optimal sequence of operations can be the following:

1. Perform an operation of the first type with $ a = 1 $ , $ b = 2 $ , $ c = 3 $ , $ d = 1 $ and $ z = 10 $ . The resulting debts are: $ d(3, 2) = 10 $ , $ d(2, 3) = 15 $ , $ d(1, 1) = 10 $ , all other debts are $ 0 $ ;
2. Perform an operation of the first type with $ a = 2 $ , $ b = 3 $ , $ c = 3 $ , $ d = 2 $ and $ z = 10 $ . The resulting debts are: $ d(2, 2) = 10 $ , $ d(3, 3) = 10 $ , $ d(2, 3) = 5 $ , $ d(1, 1) = 10 $ , all other debts are $ 0 $ ;
3. Perform an operation of the second type with $ a = 2 $ . The resulting debts are: $ d(3, 3) = 10 $ , $ d(2, 3) = 5 $ , $ d(1, 1) = 10 $ , all other debts are $ 0 $ ;
4. Perform an operation of the second type with $ a = 3 $ . The resulting debts are: $ d(2, 3) = 5 $ , $ d(1, 1) = 10 $ , all other debts are $ 0 $ ;
5. Perform an operation of the second type with $ a = 1 $ . The resulting debts are: $ d(2, 3) = 5 $ , all other debts are $ 0 $ .

## 样例 #1

### 输入

```
3 2
1 2 10
2 3 5
```

### 输出

```
2
1 2 5
1 3 5
```

## 样例 #2

### 输入

```
3 3
1 2 10
2 3 15
3 1 10
```

### 输出

```
1
2 3 5
```

## 样例 #3

### 输入

```
4 2
1 2 12
3 4 8
```

### 输出

```
2
1 2 12
3 4 8
```

## 样例 #4

### 输入

```
3 4
2 3 1
2 3 2
2 3 4
2 3 8
```

### 输出

```
1
2 3 15
```

# 题解

## 作者：Error_Eric (赞：6)

### 题意

前面那篇题解说这个东西很神奇，但是也没有给出解释或者证明。其实吧，是翻译把原来简单的东西复杂了。

题意是有若干个三元组，$(x,y,z)$ 表示 $x$ 欠 $y$ 一共 $z$ 块钱。

然后试重新整理这些欠债关系使得金钱交易量最小。

### Sol

（冷知识，其实 alipay 之类的软件就是干这个的）。

现实中，我们只关心自己借出去了多少钱，拿回来了多少钱，至于这些钱是谁给的，其实并不重要，在这道题里面也一样。

具体地，给每个人一个余额 $a$，表示**借出去了多少钱**，也就是**最终应该得到多少钱**，初值为 $0$。

向别人借钱则余额减去 $z$，借给别人前则余额加上 $z$。

最后，如果余额大于 $0$ 随便找一个余额小于 $0$ 的要钱，这样一定是不劣的。

为什么呢？因为每个借给别人钱的人不管是分成多次，还是一次拿完，至少都会对交易量造成 $a$ 的贡献。因此不存在更优的解法。

此外，这种方式一定是合法的。一个人借出去了 $a$ 块钱，拿回来了 $a$ 块钱，相当于债务清零。

### Code

比较简单，放个链接：[Link](https://codeforc.es/contest/1266/submission/180273671)

---

## 作者：_Wind_Leaves_ShaDow_ (赞：2)

用一种自认为很巧妙的思路秒了，激动地打开题解区准备交题解，结果发现有这种做法了。

没关系我还是要发题解！

---

中文题面过于形式化题意，看不懂，于是去看了英文题面。

就是说有 $m$ 个形如 $(x,y,z)$ 的欠债关系，代表 $x$ 欠 $y$ $z$ 元。然后你可以找两个 $(a,b,x)$ 和 $(c,d,y)$ 的欠债关系，让 $a$ 欠 $b$ 的钱减少 $z\le\min(x,y)$，让 $c$ 欠 $d$ 的钱减少 $z$，然后让 $a$ 多欠 $d$ $z$ 元，$c$ 多欠 $b$ $z$ 元钱。

现在要你进行这种操作若干次，使得欠条上面数字总和最小。

---

手玩一下这个看起来抽象的操作，我们发现结果是所有欠债的人欠的钱没有变，所有要债的人要的债没有变。所以我们的所有操作最后只能把形如 $(a,a,x)$，即我欠我自己 $x$ 元钱的情况去掉。

玩数据的过程中因为看不懂操作带入了生活情境，发现 $(a,b,x)$ 和 $(c,d,y)$ 中 $a,d$ 和 $c,b$ 不认识也没有关系。所以说每个人都是一样的，没有说一定要找谁要钱。

那么我们考虑建立一个债务处理所，每个人的欠钱和要债都转移到处理所里面进行，即每个人把自己欠的钱给债务处理所，债务处理所把每个人要的钱给他们，那么每个人最后要么只欠钱，要么只要债，要么没有债务。

所以把人分为要债的和欠钱的两类，要债的随便找欠钱的人把自己的钱补齐就可以了，因为每个人都是一样的所以找谁都无所谓。

```cpp
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pb push_back
#define vec vector
#define Il inline
#define Rg register
#define Ri Rg int
#define p_que priority_queue
#define IT ::iterator

using namespace std;
//typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
const int N=2e5,Inf=1e18;
const db eps=1e-9,pi=acos(-1.0);

int n,m,nd[N+5],ans=0;
p_que<pii,vector<pii>,greater<pii>>pq;
vec<pair<pii,int>>v;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for(Ri i=1;i<=m;i++){
		int x,y,z;cin>>x>>y>>z;
		nd[y]+=z,nd[x]-=z;
	}
	for(Ri i=1;i<=n;i++)if(nd[i]<0)pq.push({nd[i],i});
	for(Ri i=1;i<=n;i++){
		if(nd[i]<=0)continue;
		while(nd[i]){
			int fq=pq.top().se;pq.pop();
			if(-nd[fq]>nd[i]){
				v.pb({{fq,i},nd[i]});
				nd[fq]+=nd[i],nd[i]=0;pq.push({nd[fq],fq});
			}else{
				v.pb({{fq,i},-nd[fq]});
				nd[i]+=nd[fq],nd[fq]=0;
			}
		}
	}
	cout<<v.size()<<'\n';for(Rg pair<pii,int> i:v)cout<<i.fi.fi<<' '<<i.fi.se<<' '<<i.se<<'\n';
	return 0;
}
```

---

## 作者：Nemlit (赞：2)

想了好久奇怪的东西……

实际上我们只需要记录每个人的出边之和以及入边之和，然后任意匹配即可。

证明：首先，每个点出边之和-入边之和是不会发生改变的，所以这个答案一定是我们的下界。其次，对于每个点，他不可能同时存在入边和出边，所以每个点最后的形态一定是连出去或者连进来总和为$|in_i-out_i|$的边。

所以我们现在可以知道每个点的最终连边量，考虑怎么构造一张图可以被题目的操作方式构造。不难发现，对于任意两张都满足上一段的那个条件的图，他们是可以互相转化的。所以我们只需要任意连一张符合条件的图即可。
### $\rm Code : $
```cpp
/* This code is written by Nemlit */
#include<bits/stdc++.h>
using namespace std;
#define il inline
#define int long long
#define re register
#define rep(i, a, b) for(re int i = (a); i <= (b); ++ i)
il int read() {
    re int x = 0, f = 1; re char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - 48, c = getchar();
    return x * f;
}
#define maxn 600005
int n, m, in[maxn], u[maxn], v[maxn], w[maxn], a[maxn], out[maxn], b1, c1, b[maxn], c[maxn], cnt;
il bool cmp(int x, int y) {
	return a[x] > a[y];
}
signed main() {
	n = read(), m = read();
	rep(i, 1, m) {
		int u = read(), v = read(), w = read();
		in[v] += w, out[u] += w;
	}
	rep(i, 1, n) a[i] = in[i] - out[i];
	rep(i, 1, n) if(a[i] < 0) b[++ b1] = i;
	rep(i, 1, n) if(a[i] > 0) c[++ c1] = i;
	sort(b + 1, b + b1 + 1, cmp), sort(c + 1, c + c1 + 1, cmp);
	int now = 1;
	rep(i, 1, b1) {
		while(now <= n && a[b[i]] < 0) {
			int t = min(-a[b[i]], a[c[now]]);
			a[b[i]] += t, a[c[now]] -= t;
			u[++ cnt] = b[i], v[cnt] = c[now], w[cnt] = t;
			if(a[c[now]] == 0) ++ now;
		}
	}
	cout << cnt << endl;
	rep(i, 1, cnt) printf("%lld %lld %lld\n", u[i], v[i], w[i]);
	return 0;
}

```

---

## 作者：wangyibo201026 (赞：0)

## description

原题意是债务处理器，可能更有感觉一些。

对于点 $i$，令其出边权值和为 $in_i$，入边权值和为 $out_i$，那么进行若干次操作后 $in_i - out_i$ 是肯定不会变的。比较好的理解方式是，生活中处理债务，我不可能凭空少欠别人钱，也不可能多欠别人钱。

还注意到一个事情就是所有 $in_i - out_i$ 相同的状态图都能被构造出来。比较感性的理解是因为在债务中我只关心我应该获得多少钱（也可以是负的），题目操作也明示我们债务对象会发生改变，所以和债务对象没有关系。

那么现在就是需要构造一张图，使得其 $in_i - out_i$ 与原图一样，很容易用两个栈或者是队列解决。

## code

code：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 3e5 + 5;

int n, m;
int a[N];

stack < int > stk1, stk2;
vector < pair < pii, int > > e;

void Solve () {
  cin >> n >> m;
  for ( int i = 1; i <= m; i ++ ) {
    int u, v, w;
    cin >> u >> v >> w;
    a[v] -= w, a[u] += w;
  }
  for ( int i = 1; i <= n; i ++ ) {
    if ( a[i] > 0 ) {
      stk1.push ( i );
    }
    else if ( a[i] < 0 ) {
      stk2.push ( i );
    }
  }
  while ( !stk1.empty () ) {
    if ( a[stk1.top ()] < -a[stk2.top ()] ) {
      e.push_back ( { { stk1.top (), stk2.top () }, a[stk1.top ()] } );
      a[stk2.top ()] += a[stk1.top ()];
      a[stk1.top ()] = 0;
      stk1.pop ();
    }
    else if ( a[stk1.top ()] == -a[stk2.top ()] ) {
      e.push_back ( { { stk1.top (), stk2.top () }, a[stk1.top ()] } );
      a[stk1.top ()] = a[stk2.top ()] = 0;
      stk1.pop (), stk2.pop ();
    }
    else {
      e.push_back ( { { stk1.top (), stk2.top () }, -a[stk2.top ()] } );
      a[stk1.top ()] += a[stk2.top ()];
      a[stk2.top ()] = 0;
      stk2.pop ();
    }
  }
  cout << e.size () << '\n';
  for ( pair < pii, int > x : e ) {
    cout << x.first.first << " " << x.first.second << " " << x.second << '\n';
  }
}

signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
  Solve ();
  return 0;
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

**题目大意**

给定一张有向图，共 $n$ 个点，令 $d(a,b)$ 表示 $a\to b$ 的有向边的边权，您有两种操作：

1. 选择四个点对 $(a,b,c,d)$（$a\ne c,b\ne d$，且 $d(a,b)>0,d(c,d)>0$），则您选择一个整数 $z$ 满足 $0 < z\le \min(d(a,b),d(c,d))$，则 $d(a,b)$ 和 $d(c,d)$ 减少 $z$，同时生成/如果存在则增加边 $d(c,b),d(a,d)$ 的边权 $z$ 点；
2. 选择一个点 $x$，令 $d(x,x)=0$。

问通过上述两种操作能使得此图的边权和最小为多少？输出最后的图。

**一些显然的事情**

首先如果 $c=b$ 那么 $d(c,b)$ 就不生成，不用增加 $z$。$a=d$ 同理。

这也就意味着只有下面这两种情况可以减少边权和：

第一种：

$$
\begin{aligned}
d(a,b) = w_1,d(b,c)=w_2
\rArr
\left\{\begin{matrix}
 d(a,b)=w_1-\min(w_1,w_2)\\
d(b,c)=w_2 - \min(w_1,w_2)\\
 d(a,c)=\min(w_1,w_2)
\end{matrix}\right.
\end{aligned}
$$
此时总值 $tot$ 会减少 $\min(w1,w2)$。还会删除一条边。


第二种：

$$
\begin{aligned}
d(a,b) = w_1,d(b,a)=w_2
\rArr
\left\{\begin{matrix}
 d(a,b)=w_1-\min(w_1,w_2)\\
d(b,a)=w_2 - \min(w_1,w_2)
\end{matrix}\right.
\end{aligned}
$$

此时总值 $tot$ 会减少 $\min(w1,w2)$。会删除一条边。

如果有重边可以直接合并。

**这之后的性质**

我们重点关注情况 $1$ 的点 $b$，发现在简化之后，它要么只有入度不为 $0$ 要么只有出度不为 $0$。

也就是说简化之后与一个点有关的资金流量只有一个，那就是总出权值与总入权值的差。设点 $i$ 的资金流量为 $W_i$。

事实上，结合题意理解。在不增加债务的情况下，资金流转情况和每个用户关系不大，每个用户只要关心自己收了多少债与自己欠了多少债。

所以我们直接进行端到端的短平快式处理。把
$W_i>0$ 的放一组，把 $W_i<0$ 的放一组。让大于 $0$ 的往小于 $0$ 的补流量即可。

正确性证明：

你一次性把流量全给了和分期付款对于总边权贡献相同。这样做也没有创造新的债务。而且资金流量的和就是 $0$。

所以我们找两个双指针遍历当前的正点和负点，让出的多的点往入的多的点里面补充流量即可。这个点的流量变成 $0$（平账了）就换下一个。

---

## 作者：eb0ycn (赞：0)

传送门：[CF1266D](https://www.luogu.com.cn/problem/CF1266D)。

不得不说这个翻译有点过于形式化，甚至我一开始还以为这是一道图论题……

## 题意

有 $n$ 个人，他们之间打了 $m$ 个欠条，每个欠条表示 $a$ 欠了 $b$ 的钱为 $d(a,b)$。现在你可以重新安排这些欠条，在不改变每个人外债的基础上，让欠条上的钱之和最小。输出任意一种方案。

如 $a$ 欠 $b$ 两块钱，$b$ 欠 $c$ 两块钱，可以等效为 $a$ 欠 $c$ 两块钱。$a$ 欠 $b$ 两块钱，$b$ 欠 $a$ 三块钱，可以等效为 $b$ 欠 $a$ 一块钱。

显然，自己不可能欠自己的钱。

## 思路

我们只关心每个人的外债是多少。所以欠别人和别人欠自己可以抵消。先算出每个人需要还或需要得到多少元。

先是否欠钱分组，由于要让欠条上的钱之和最小，所以肯定要让每个负债的人向债主打欠条。至于找谁打，随便。那打的欠条是多少呢？

假设 $a$ 需要还 $x$ 元，$b$ 需要得到 $y$ 元。那欠条上的钱 $z$ 肯定不能超过 $\min(x,y)$。如果超过 $x$，那 $a$ 还要在别人那里得到 $z-x$ 元；超过 $y$，那 $b$ 就负债了。我们维护两个指针 $l,r$，分别表示负债的人和债主。对于每一个 $l$，当前欠条就是 $(a,r,\min(x,y))$。打完欠条以后让 $l$ 的负债减少 $z$，$r$ 的外债减少 $z$。此时，一定有至少一个人外债为 $0$，就跳过这个人。这样 $l,r$ 单调不降，就是尺取。

由于每个人的外债加起来一定是 $0$，所以尺取的细节就少了很多，具体看代码。

时间复杂度：严格 $O(n+m)$。

## AC代码

甚至不用建图。

```cpp
#include <cstdio>
using namespace std;
int n,m,u[100001],v[100001],a,b,cnt1,cnt2,d1[100001],d2[100001],l=1,r=1,cnt3;
#define ll long long
ll zw[100001],w[100001],ret,c;
ll min(ll a,ll b){return a>b?b:a;}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)scanf("%d%d%lld",&a,&b,&c),zw[a]+=c,zw[b]-=c;
	for(int i=1;i<=n;++i){
		if(zw[i]>0)d1[++cnt1]=i;
		if(zw[i]<0)d2[++cnt2]=i;
	}
	while(l<=cnt1){
		ret=min(zw[d1[l]],-zw[d2[r]]);
		zw[d1[l]]-=ret,zw[d2[r]]+=ret,u[++cnt3]=d1[l],v[cnt3]=d2[r],w[cnt3]=ret;
		if(!zw[d1[l]])++l;
		if(!zw[d2[r]])++r;
	}printf("%d\n",cnt3);
	for(int i=1;i<=cnt3;++i)printf("%d %d %lld\n",u[i],v[i],w[i]);
	return 0;
}
```


---

