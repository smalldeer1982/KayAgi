# Cookie Clicker

## 题目描述

Kostya is playing the computer game Cookie Clicker. The goal of this game is to gather cookies. You can get cookies using different buildings: you can just click a special field on the screen and get the cookies for the clicks, you can buy a cookie factory, an alchemy lab, a time machine and it all will bring lots and lots of cookies.

At the beginning of the game (time 0), Kostya has 0 cookies and no buildings. He has $ n $ available buildings to choose from: the $ i $ -th building is worth $ c_{i} $ cookies and when it's built it brings $ v_{i} $ cookies at the end of each second. Also, to make the game more interesting to play, Kostya decided to add a limit: at each moment of time, he can use only one building. Of course, he can change the active building each second at his discretion.

It's important that Kostya is playing a version of the game where he can buy new buildings and change active building only at time moments that are multiples of one second. Kostya can buy new building and use it at the same time. If Kostya starts to use a building at the time moment $ t $ , he can get the first profit from it only at the time moment $ t+1 $ .

Kostya wants to earn at least $ s $ cookies as quickly as possible. Determine the number of seconds he needs to do that.

## 样例 #1

### 输入

```
3 9
1 0
2 3
5 4
```

### 输出

```
6
```

## 样例 #2

### 输入

```
3 6
1 0
2 2
5 4
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 13
1 0
2 2
6 5
```

### 输出

```
7
```

## 样例 #4

### 输入

```
1 10000000000000000
1 0
```

### 输出

```
10000000000000000
```

# 题解

## 作者：loveJY (赞：6)

建议标签:凸包

思路:

看到最少秒数,我们能想到满足二分性质,因为如果一个时间点之前的可以那么之后的也一定可以

发现我们check函数有一个$n^2$的做法:$dp_{i,j}$表示记录第i秒我们当且在使用j工厂,能有的最大金币数,这样肯定TLE...

但是看到这个动态规划的形式,其实很容易发现是维护了许多直线,但是只有他们构成的凸包有用处

于是想:我们把$time$(每一秒)当做$x$轴,$value$(手上的钱)当做$y$轴的话,连续选择一个工厂生产就相当于**在某个点开始的一条射线**,而且那个点的$y>C_i$而且射线斜率是$V_i$

然后会发现我们要确定那个点,其实就是在确定最优决策下**达到$C_i$的最短时间!**

所以我们就是要对这些个直线按照$C_i$ 递增的顺序依次进行处理,计算他们的最优代价,因为我们一定先解锁代价小的再解锁代价大的

做法:

开一个栈维护我们最优决策构成的凸包

对于一条新的要加入的直线,从栈底开始向上扫,找到第一条包括大于他的纵坐标的点的直线,即下图中的红点即其所在直线,注意可能红点的纵坐标**不是$C_i$**,但一定大于$C_i$:

![](https://cdn.luogu.com.cn/upload/image_hosting/o4c106sv.png)

然后我们可以根据那个点,相应的计算出蓝线的表达式

我们再把蓝线插入凸包即可qwq

由于我们其中$C_i$是递增的,每次只用在栈顶栈底操作,所以维护凸包的复杂度是$O(n)$的

瓶颈在于排序$O(nlogn)$

```cpp

//From Dawn light
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1e18;
const int MAXN = 3e5 + 7;
int n, ans;
int S, head, tail;
int f[MAXN], que[MAXN];
struct Mac {
	int V, C;
	bool operator<(const Mac &x)const {
		return C == x.C ? V < x.V : C < x.C;
	}
} a[MAXN];

int calc(int x, int o) {
	return max(0ll, (x - f[o] + a[o].V - 1) / a[o].V);
}

bool chk(int i, int j, int V) {
	int Xi = calc(V, i);
	int Xj = calc(V, j);
	if(Xi != Xj)return Xi > Xj;
	return f[i] + Xi * a[i].V <= f[j] + Xj * a[j].V;
}

int getslope(int i, int j) {
	return (f[i] - f[j]) / (a[j].V - a[i].V);
}

signed main() {
	// freopen("test.in", "r", stdin);
	scanf("%lld%lld", &n, &S);
	for(int i = 1; i <= n; ++i)scanf("%lld%lld", &a[i].V, &a[i].C);
	sort(a + 1, a + n + 1);
	int h = 1, t = 0, V = 0;
	ans = inf;
	for(int i = 1; i <= n; ++i) {
		if(a[i].V <= V)continue;
		V = a[i].V;
		while(h < t && chk(que[h], que[h + 1], a[i].C))++h;
		if(i > 1) {
			int j = que[h];
			f[i] = f[j] - a[i].C - calc(a[i].C, j) * (a[i].V - a[j].V);
		}
		ans = min(ans, calc(S, i));
		while(h < t && getslope(que[t - 1], que[t]) >= getslope(que[t], i))
			--t;
		que[++t] = i;
	}
	printf("%lld\n", ans);
	return 0;
}



```

---

## 作者：XZhuRen (赞：2)

除排序外线性做法。

参考了 ${l\color{Red} oveJY}$ 大神的题解：[文章链接](https://www.luogu.com.cn/article/0wexvqh0)。

我们发现，有一些工厂一定是不优的：按照 $c_{i}$ 升序（$c_{i}$ 相同按照 $v_{i}$ 降序）排序后，$v_{i}<=premax(v)$ 的一定是可以删除的。

之后我们就得到了一个 $c_{i}$ 和 $v_{i}$ 都严格上升的序列。

现在设函数：

${\Large F(t)}$。

横坐标为**时间** $t$，纵坐标是**金币数** $sum$。

容易发现，我们的操作顺序总是**先取 $\mathbf{c_{i}}$ 小的**，直到钱够了再取大的。

又有**贪心结论**：一个工厂**如果被购买**，则一定在能取用的第一时间（即当前总金币数 $sum \ge c_{i}$ 时）购买启动。

易知 $F(t)$ 是单调递增，且下凸的。

初始时 $F(t)$ 为一条直线 $sum=0$。

有了这个这两个结论，我们可以考虑增量构造函数 $F(t)$。

首先我们从工厂 $1$ 开始，顺序构造（大的一定在后面，以这个基础确定第一次出现的位置）。

每次对于当前的工厂，找到最早的时间 $t$ 使得 $F(t) \ge c_{i}$，这就是本工厂的启动时间，根据贪心结论，这个时间的**固定的**。

再确定这个工厂能影响的区间：

[![pEFVDwn.png](https://s21.ax1x.com/2025/01/15/pEFVDwn.png)](https://imgse.com/i/pEFVDwn)

把这个区间全部变为这条直线就可以了。

由于整个函数是由很多直线（射线）构成的，使用单调栈维护就行，每次从栈底向顶找 $F(t)\ge c_{i}$，再把栈顶不优的全部弹掉，由于 $c_{i}\uparrow $，所以栈底指针也是单调增的（注意边界情况，实际写的时候最好找到了之后 `bottom--`）。

复杂度线性对数，瓶颈在于排序，实测跑得比二分快 $500ms$。

最后扫一遍函数找到第一个 $F(t)\ge S$ 的位置就好了。

**P.S.** 实际上本题对于下凸性质并没有利用，而是利用了单调性。

[Code](https://codeforces.com/contest/377/submission/301075114)。

---

## 作者：Purslane (赞：0)

# Solution

这个算 slope trick 吗。

如果 $v_i \ge v_j$ 且 $c_i \le c_j$，那么 $i$ 严格优于 $j$，因此假定 $c$ 两两不同。

显然，我们会买 $v$ 比较小的一家工厂——因为手头资金缺乏。等攒够了一定资本，就可以买 $v$ 比较大的工厂了。并且，我们只会在用之前买工厂，不会提前购买。

设 $dp_{i,j}$ 为，考虑了 $v$ 前 $i$ 小的工厂，用了 $j$ 的时间，最多能获得多少的钱。

归纳的证明：$(x,dp_{i,x})$ 对每个 $i$ 都形成一个下凸壳。这个只需要在我们的 DP 中体现就行。

考虑加入 $(c,v)$，我们显然会从**第一个满足 $dp_{i,x} \ge c$ 的位置 $x$ 开始买这个工厂，且对于足够大的 $t$，一定是买这个 $v$ 更大的工厂更优**。

因此相当于将 $dp_{i,*}$ 和斜率更大的直线取 $\max$。显然这样操作之后还是一个凸包。

直接模拟维护线段斜率即可做到 $O(n \log n)$，瓶颈在排序和二分。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,INF=1e17;
int n,s,hd=1,tl;
struct SEG {__int128 st,ed,k,b;__int128 f(__int128 x) {return k*x+b;}}t[MAXN];
map<int,int> mp;
pair<int,__int128> bfind(int v) {
	if(v==0) return {0,0};
	int ans=-1,l=hd,r=tl;
	__int128 pt;
	while(l<=r) {
		int mid=(l+r>>1);
		if(t[mid].f(t[mid].ed)<v) l=mid+1;
		else {
			int pos=(v-t[mid].b+t[mid].k-1)/t[mid].k;
			pos=max(pos,(int)t[mid].st);
			if(pos>=t[mid].st&&pos<=t[mid].ed) if(ans==-1||pos<ans) ans=pos,pt=t[mid].f(pos);
			r=mid-1;
		}
	}
	return {ans,pt};
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>s;
	ffor(i,1,n) {
		int v,c;
		cin>>v>>c;
		if(mp.count(v)) mp[v]=min(mp[v],c);
		else mp[v]=c;	
	}
	t[++tl]={0,10000000000000001,0,0};
	for(auto pr:mp) {
		int v=pr.first,c=pr.second;
		auto Pr=bfind(c);
		int pos=Pr.first;
		__int128 val=Pr.second;
		if(pos==-1) continue ;
		SEG seg={pos+1,10000000000000001,v,val-c-v*pos};
		if(seg.f(10000000000000001)<=t[tl].f(10000000000000001)) continue ;
		while(hd<=tl) {
			int Lim=max(seg.st,t[tl].st);
			if(Lim>t[tl].ed||seg.f(t[tl].ed)<=t[tl].f(t[tl].ed)) {seg.st=t[tl].ed+1;break ;}
			int lst=max(Lim,(int)((t[tl].b-seg.b+seg.k-t[tl].k-1)/(seg.k-t[tl].k)));
			if(lst>Lim||Lim!=t[tl].st) {
				seg.st=lst,t[tl].ed=lst-1;
				break ;	
			}
			--tl;
		}
		t[++tl]=seg;
	}
	cout<<bfind(s).first;
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：0)

若 $c_i\ge c_j$ 且 $v_i\lt v_j$ 则 $i$ 永远不会用到，去掉这样的 $i$ 以后按照 $c$ 排序，我们肯定是按照这个顺序去用一些人，最后激活某个人然后一直用它。

由于 $c,v$ 都是递增的，所以如果有两种方案：第一种花了 $x$ 秒激活了 $i$，第二种花了 $y$ 秒：假设 $x\lt y$ 则第二种方案不管此时有多少金币一定没有第一种方案优：因为差的这 $(y-x)$ 秒，第一种方案用工厂 $i$ 转；第二个人用 $v_j\lt v_i$ 的一些工厂 $j$ 转，显然没有第一种方案优秀。所以我们的第一关键字是激活时间，第二关键字是激活时剩下的金币数，这样直接暴力转移就可以设计出一个 $n^2$ 的 dp。这个 trick 在 CF1801D 里也出现了。

由于转移是双关键字比较的所以一些拆贡献之类的优化方法就不太行得通，但是注意到有决策单调性在：考虑两个状态 $i\lt j$，若 $j$ 在 $k$ 处比 $i$ 优秀，则对于更大的 $k'$ 一定是 $j$ 比 $i$ 来的优秀。

然后就可以二分队列进行优化，但是第一次写二分队列炸了半天心态没了，有几个注意点：

- 若 $i\ge j$ 则认为 $i\rightarrow j$ 的转移代价是 $\infty$。

- 若 $i$ 在 $n$ 处都不比队尾优就不要加了，我的实现里把他的边界设成了 $n+1$，然后任何一个人转移到 $n+1$ 的结果都是一样的所以这样这个人就永远赖在队列里，前面弹不掉他后面人也干不掉他......然后会 WA 116.

时间复杂度 $O(n\log n)$。

[代码](https://codeforces.com/contest/377/submission/207935628)

---

