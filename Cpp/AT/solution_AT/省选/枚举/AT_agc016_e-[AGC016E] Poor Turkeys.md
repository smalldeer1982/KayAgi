# [AGC016E] Poor Turkeys

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc016/tasks/agc016_e

$ N $ 羽の鳥がいます。 鳥には $ 1 $ から $ N $ まで番号が振られています。

ここに $ M $ 人の男性が一人ずつ順番に訪れます。 $ i $ 番目に訪れる男性は次のような行動をします。

- 鳥 $ x_i $, $ y_i $ が両方とも生き残っている場合 : 鳥 $ x_i $, $ y_i $ の一方を等確率で選んで食べる。
- 鳥 $ x_i $, $ y_i $ の一方のみが生き残っている場合 : 生き残っている方の鳥を食べる。
- 鳥 $ x_i $, $ y_i $ がどちらも生き残っていない場合 : 何もしない。

次の条件を満たす $ (i,\ j) $ ($ 1\ <\ =\ i\ <\ j\ <\ =\ N $) の組の個数を求めてください。

- すべての男性が行動を終えた後、鳥 $ i $, $ j $ が両方とも生き残っている確率が $ 0 $ より大きい。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 400 $
- $ 1\ <\ =\ M\ <\ =\ 10^5 $
- $ 1\ <\ =\ x_i\ <\ y_i\ <\ =\ N $

### Sample Explanation 1

$ (i,\ j)\ =\ (1,\ 3),\ (2,\ 3) $ が条件を満たします。

### Sample Explanation 2

$ (i,\ j)\ =\ (1,\ 4) $ が条件を満たします。 鳥 $ 1 $, $ 4 $ が両方とも生き残るのは、次のような場合です。 - $ 1 $ 番目の男性が鳥 $ 2 $ を食べる。 - $ 2 $ 番目の男性が鳥 $ 3 $ を食べる。 - $ 3 $ 番目の男性が何もしない。

## 样例 #1

### 输入

```
3 1
1 2```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
1 2
3 4
2 3```

### 输出

```
1```

## 样例 #3

### 输入

```
3 2
1 2
1 2```

### 输出

```
0```

## 样例 #4

### 输入

```
10 10
8 9
2 8
4 6
4 9
7 8
2 8
1 8
3 4
3 4
2 7```

### 输出

```
5```

# 题解

## 作者：Ebola (赞：40)

# 【AGC016E】Poor Turkeys  题解

首先记住一句话：留着你是因为以后要炖了你。这句话非常重要，它的思想是题解的核心

我们设状态$f_{i,j}$表示：如果最后要留下$i$，那么是否要炖了$j$。初始值设$f_{i,i}=1$

如果我们从时间倒流的角度来考虑这个状态，那么当前$f$数组就表示：如果最后要留下$i$，那么之前是否要留下$j$（因为以后要炖了$j$）。如果我们遇到某个时刻需要在$i$和$j$中选择，那么为了留下$i$，必然要炖了$j$，那么在此之前就不能让$j$死了，于是在这之前的时间，$j$应该受到与$i$一样的保护，也就是如果某个时刻要在$j$和$k$中选择，那肯定炖了$k$。所以对于每一个$i$，我们都要从时间倒流的角度去传递这个状态，然后得到完整的状态，然后将满足$f_{i,j}=1$的点$j$放入集合$S_i$中，表示如果要留下$i$需要炖了哪些东西

考虑一只鸡$i$怎样才能被留下来。如果存在一个时刻，要在$x$和$y$中选择，而此时的状态是$f_{i,x}=f_{i,y}=1$（也就是说为了留下$i$，必须留下$x$和$y$来挡枪子），可是$x$和$y$只能留一个了，那么$i$就不能被保留下来了。**这是结论一**

那么我们把一对鸡$(i,j)$放到一起来考虑一下。假如有一个时刻需要在$i$和$x$中选择，接下来又有一个时刻需要在$j$和$x$中选择，那么根据上面的思想，之前那个时刻我们会把$x$炖了，可是为了留下$j$，我们又不能那么早炖了$x$，因此如果有那么两个时刻，我们就可以说这一对鸡$(i,j)$不可能同时留下来

将这个思路拓展一下，假如有一个时刻需要在$i$和$x$中选择，接下来又有一个时刻需要在$j$和$y$中选择，那么在此之前，$x$与$y$应该受到与$i$和$j$一样的保护，所以应该当做$i$和$j$来看待。假如在上述两个时刻之前，有一个时刻需要在$z$和$x$中选择，接下来又有一个时刻需要在$z$和$y$中选择，那么鸡$(i,j)$是不可能留下来的，因为$(x,y)$不能同时被保护，最后$i$和$j$就会有一个不能拉到挡枪的人。

再拓展一下，我们可以得到结论：$(i,j)$可以留下，当且仅当$S_i\cap S_j=\varnothing$。**这是结论二**

**按上面提到的两个结论去做就可以了，复杂度$O(nm+n^3)$，求交集的那个部分可以用bitset优化，但也没什么必要**

```cpp
#include<bits/stdc++.h>
using namespace std;

const int M=100010;
bool stu[410][410];
int n,m,a[M],b[M];
bool cant[410];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",a+i,b+i);
	for(int i=1;i<=n;i++)
	{
		stu[i][i]=1;
		for(int j=m;j>=1;j--)
		{
			bool x=stu[i][a[j]],y=stu[i][b[j]];
			if(x&&y){cant[i]=1;break;}
			else if(x) stu[i][b[j]]=1;
			else if(y) stu[i][a[j]]=1;
		}
	}
	int ans=0;
	for(int i=1;i<n;i++)
	{
		if(cant[i]) continue;
		for(int j=i+1;j<=n;j++)
		{
			if(cant[j]) continue;
			bool flag=1;
			for(int k=1;k<=n;k++)
				if(stu[i][k]&&stu[j][k]) flag=0;
			ans+=flag;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```



---

## 作者：Karry5307 (赞：17)

### 题意

有 $n$ 只鸡和 $m$ 个人，每个人会钦定两只鸡 $x,y$。接下来每个人轮流操作：

- 如果他所钦定的两只鸡都被吃掉了那么就什么也不做。

- 如果他所钦定的两只鸡中只有一只被吃掉那就吃掉剩下一只。

- 如果他所钦定的两只鸡中都没被吃掉那就等概率选择一只吃掉。

求有多少个二元组 $(i,j)$ 满足 $i<j$ 并且鸡 $i$ 和鸡 $j$ 都有可能存活。

$\texttt{Data Range:}1\leq n\leq 400,1\leq m\leq 2\times 10^5$

### 题解

这题很妙啊……

先考虑一只鸡 $i$ 能否存活下来。顺着做可能不是很好做，于是考虑时间倒流。

为了让 $i$ 活下来，如果有一个人钦定的两只鸡分别为 $i$ 和 $x$ 的话，那我必须在这次让 $x$ 来送命。于是 $x$ 这只鸡在这个人之前的所有人的操作中不能被拿去送命。

但是假设已经有 $i,x$ 和 $i,y$ 两个限制了，那么 $x,y$ 也是被保护的对象。如果前面再有一个 $x,y$ 的话，因为 $x$ 和 $y$ 中有一只鸡要在这里被吃掉，那么 $i$ 必死无疑。

于是就可以确定一只鸡是否存活了：对于鸡 $i$ 来说，设集合 $S_i$ 表示要想让这只鸡存活下来，当前需要保护的鸡有哪些。一开始 $S_i=\{i\}$，然后从后往前扫每一个人钦定的 $x,y$，如果 $x,y\in S$，那么鸡 $i$ 一定无法存活。否则如果只有一个属于 $S$，不妨设为 $x$，那么这一轮肯定是让 $y$ 送命，也即之前的轮次 $y$ 也必须被保护起来，于是将 $y$ 加入 $S_i$。

考虑两只鸡的情况。注意到如果 $i$ 能存活下来那么 $S_i$ 中除了 $i$ 的所有鸡都必须送命，同时注意到一只鸡只能被送命一次，所以枚举两只鸡 $i,j$ 然后判断 $S_i\cap S_j$ 是否为空即可。

有一个细节：枚举 $i,j$ 的时候一定要保证 $i,j$ 都不能是必死的。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef long long int li;
const ll MAXN=2e5+51;
ll n,m,res,u,v;
ll x[MAXN],y[MAXN],g[MAXN];
bitset<401>f[401];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
int main()
{
	n=read(),m=read();
	for(register int i=1;i<=m;i++)
	{
		x[i]=read(),y[i]=read();
	}
	for(register int i=1;i<=n;i++)
	{
		f[i][i]=1;
		for(register int j=m;j;j--)
		{
			u=f[i][x[j]],v=f[i][y[j]],u&&v?g[i]=1:1;
			u?f[i][y[j]]=1:(v?f[i][x[j]]=1:1);
		}
	}
	for(register int i=1;i<=n;i++)
	{
		if(g[i])
		{
			continue;
		}
		for(register int j=i+1;j<=n;j++)
		{
			!g[j]?res+=!((f[i]&f[j]).count()):1;
		}
	}
	printf("%d\n",res);
}
```

---

## 作者：小粉兔 (赞：16)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC016.html](https://www.cnblogs.com/PinkRabbit/p/AGC016.html)。

我的做法好复杂，但是却取得了更优的理论复杂度。

注意如果我们为每个时间点的每只火鸡都建立一个布尔变量表示它是否还活着。

则是可以根据操作建立一个 2-SAT 模型的，点数是 $\mathcal O (N M)$ 级别。

不过如果对同一只火鸡，把对它无操作的时刻前后的两个相邻布尔变量合成一个也无妨，所以点数可以是 $\mathcal O (N + M)$。

然后跑正常的 2-SAT 过程，缩点建出 DAG 并处理拓扑序。

两只火鸡最后都能活着，当且仅当它们俩首先最后都不是必死的，并且一只活着不会导致另一只死亡。

也就是最终时刻对应的两个布尔变量，一个为 $1$ 不能导出另一个为 $0$。

这也就是要求 DAG 上的可达性问题，因为询问是否能到达的点只有 $\mathcal O (N)$ 个所以直接 bitset 做就好。

这样复杂度是 $\displaystyle \mathcal O \!\left( \frac{(N + M) N}{w} \right)$，其中 $w$ 是字长。

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>

const int MN = 405, MM = 100005;
const int MC = (MM * 2 + MN) * 2;

int N, M, C;
std::vector<int> V[MN], G[MC], G2[MC];
inline int Alive(int x) { return 2 * x - 1; }
inline int Dead(int x) { return 2 * x; }
inline int T(int x) { return ((x - 1) ^ 1) + 1; }
inline void Insert(int x, int y) {
	G[x].push_back(y);
	G[T(y)].push_back(T(x));
}

int dfn[MC], low[MC], dfc;
int stk[MC], tp, instk[MC];
int bel[MC], scnt;
void Tarjan(int u) {
	dfn[u] = low[u] = ++dfc;
	instk[stk[++tp] = u] = 1;
	for (int v : G[u]) if (!dfn[v]) {
		Tarjan(v);
		low[u] = std::min(low[u], low[v]);
	} else if (instk[v]) low[u] = std::min(low[u], dfn[v]);
	if (low[u] == dfn[u]) {
		++scnt;
		for (int x = 0; x != u; --tp)
			bel[x = stk[tp]] = scnt, instk[x] = 0;
	}
}

int vis[MC], key[MC];
std::bitset<MN> bit[MC];
int bdfs[MN]; // be dead for sure

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; ++i) V[i].push_back(++C);
	for (int i = 1, x, y; i <= M; ++i) {
		scanf("%d%d", &x, &y);
		int u0 = V[x].back(), v0 = V[y].back(), u1, v1;
		V[x].push_back(u1 = ++C);
		V[y].push_back(v1 = ++C);
		Insert(Alive(u1), Alive(u0));
		Insert(Alive(v1), Alive(v0));
		Insert(Alive(u1), Dead(v1));
		Insert(Dead(u0), Dead(v1));
		Insert(Dead(v0), Dead(u1));
	}
	for (int i = 1; i <= 2 * C; ++i) if (!dfn[i]) Tarjan(i);
	for (int i = 1; i <= 2 * C; ++i) {
		for (int x : G[i]) if (bel[x] != bel[i] && !vis[bel[x]])
			G2[bel[i]].push_back(bel[x]), vis[bel[x]] = 1;
		for (int x : G[i]) vis[bel[x]] = 0;
	}
	for (int i = 1; i <= N; ++i) key[bel[Dead(V[i].back())]] = i;
	for (int i = 1; i <= scnt; ++i) {
		if (key[i]) bit[i][key[i]] = 1;
		for (int x : G2[i]) bit[i] |= bit[x];
	}
	int Ans = 0;
	for (int i = 1; i <= N; ++i) bdfs[i] = bit[bel[Alive(V[i].back())]][key[bel[Dead(V[i].back())]]];
	for (int j = 2; j <= N; ++j) if (!bdfs[j])
		for (int i = 1; i < j; ++i) if (!bdfs[i])
			if (!bit[bel[Alive(V[i].back())]][key[bel[Dead(V[j].back())]]]) ++Ans;
	printf("%d\n", Ans);
	return 0;
}
```

---

## 作者：critnos (赞：12)

新式~~最劣解~~ $O(\dfrac {n^2m} w)$ 暴力。

考虑枚举鸡 $(i,j)$ 是否能存活。

就是说我们要尽可能的保护 $i$ 和 $j$。

假设遇到了一个指令 $(p,i)$，

我们要杀的一定是 $p$。

当然 $p$ 必须存在，

换句话说就是要在这条指令前尽可能的保护 $p$。

solved.

倒着扫，同时维护一个数组 $al$，$al_i\in\{0,1\}$。

$al_i$ 表示当前鸡 $i$ 是否受到保护。

初值 $al_x=al_y=1$。

扫到一个指令 $(p,q)$ 的时候，

若 $p$ 受到保护，则这一步要杀的就是 $q$，进而 $q$ 在这一步前受到保护。$q$ 同理。

然而若 $p,q$ 均受到保护，则这一步必须要杀其一，进而鸡 $(i,j)$ 无法同时存活。

然而这样做是 $O(n^2m)$ 的。

令人震惊的是，这个暴力已经可以通过本题。

进一步的对着代码进行优化

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
pair<int,int> a[100005];
bool al[405];
int main() 
{
	int n,m,i,j,k,s=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
		{
			memset(al,0,sizeof(al));
			al[i]=al[j]=1;
			for(k=m;k>=1;k--)
			{
				if(al[a[k].x]&&al[a[k].y])
					goto bre;
				al[a[k].x]=al[a[k].y]=al[a[k].x]^al[a[k].y];
			}
			s++;
			bre:;	
		}
	cout<<s;
}
```

改变循环顺序，即只枚举 $i$，在枚举指令时同步的维护所有的 $j$ 的 $al$ 数组。

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
pair<int,int> a[100005];
bool al[405][405];
bool fl[405];
int main() 
{
	int n,m,i,j,k,s=0,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(i=1;i<=n;i++)
	{
		memset(al,0,sizeof(al));
		memset(fl,0,sizeof(fl));
		for(j=i+1;j<=n;j++)
			al[j][j]=al[i][j]=1;
		for(j=m;j>=1;j--)
		{
			x=a[j].x,y=a[j].y;
			for(k=1;k<=n;k++)
				if(al[x][k]&&al[y][k])
					fl[k]=1;
				else
					al[x][k]=al[y][k]=al[x][k]^al[y][k];
		}
		for(j=i+1;j<=n;j++)
			s+=!fl[j];
	}
	cout<<s;
}
```

发现 $al$ 数组可用 bitset 优化，做完了。

```cpp
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;
pair<int,int> a[100005];
bitset<405> al[405],fl;
int main() 
{
	int n,m,i,j,k,s=0,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			al[j].reset();
		fl.reset();
		for(j=i+1;j<=n;j++)
			al[j][j]=al[i][j]=1;
		for(j=m;j>=1;j--)
		{
			x=a[j].x,y=a[j].y;
			fl|=al[x]&al[y];
			al[x]=al[y]=al[x]^al[y];
		}
		for(j=i+1;j<=n;j++)
			s+=!fl[j];
	}
	cout<<s;
}
```


---

## 作者：whiteqwq (赞：5)

[AT2389 [AGC016E] Poor Turkeys](https://www.luogu.com.cn/problem/AT2389)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1758804)

## 题意
- 给定$n$只火鸡，$m$个操作，每次操作会选择两只火鸡$a,b$；
- 如果两只都活着，那么任意吃一只；如果只活了一只，那么吃剩下一只；如果两只都死了，那么不吃；
- 求数对$(i,j)$满足$i<j$且存在一种情况$i$和$j$同时活着的数量。
- 数据范围：$1\leqslant n\leqslant 400,1\leqslant m\leqslant 10^5$。

## 分析
神仙题。

我们设$f_{i,j}=1$（$i\ne j$）表示：**如果$i$要活着，那么以后$j$一定要为$i$“抵命”**。

可以用一个倒推的dp来$O(n^2)$求出$f$数组，具体地说：

- 枚举以后要存活的火鸡$i$，首先设边界$f_{i,i}=1$（很显然）。
- 然后，我们倒序枚举每一个操作$(a,b)$：
- - 如果$f_{i,a}=1$且$f_{i,b}=1$，那么意味着$a$和$b$以后一定要为$i$“抵命”，**在这里不能死去**，而这里有一次$(a,b)$操作，因此$a$和$b$**一定不能两个同时存活**，那么$i$以后一定活不了。
- - 如果$f_{i,a}=1$或$f_{i,b}=1$，那么不妨设$f_{i,a}=1$（如果$f_{i,b}=1$那么交换$a,b$），因为$a$以后要为$i$抵命，所以$b$一定得现在死来保护$a$。
- - 如果$f_{i,a}=0$且$f_{i,b}=0$，那么操作$(a,b)$与$i$无关，不需要考虑。

设$S(i)$为必须死去来抵$i$一命的集合。

然后，我们枚举点对$(i,j)$（$i<j$），首先判断$i,j$是不是一定得死去，如果不是，那么很显然只有$S(i)\cap S(j)=\varnothing$才能让$i$和$j$同时存活（**一只火鸡不能同时给$i$和$j$抵命**）。

## 题解
```
#include<stdio.h>
#include<bitset>
using namespace std;
const int maxn=405,maxm=100005;
int n,m,ans;
int a[maxm],b[maxm],no[maxn];
bitset<maxn>keep[maxn];
int main(){
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++){
		keep[i][i]=1;
		for(int j=m;j>=1;j--){
			if(keep[i][a[j]]&&keep[i][b[j]]){
				no[i]=1;
				break;
			}
			if(keep[i][a[j]])
				keep[i][b[j]]=1;
			else if(keep[i][b[j]])
				keep[i][a[j]]=1;
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(no[i]==0&&no[j]==0&&(keep[i]&keep[j]).count()==0)
				ans++;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Soulist (赞：5)

~~感觉 D 比 E 难...?~~

对于每个人，当作一条边连接 $(u,v)$，标记时间为 $t$

如果一个人吃了鸡 $v$，那么保留这条边，同时进行定向，为 $u\to v$

于是最后会得到一个基环树森林，因为生效的吃次数为 $n$

我们发现如果 $(i,j)$ 合法那么必然以 $i$ 为根和以 $j$ 为根的结果是两棵互不相交的树。

考虑什么时候 $i$ 能活下来，$i$ 能活下来当且仅当在考虑 $i$ 的出边的时候连向的点没有被删除，否则 $i$ 无法活下来。

反过来，在考虑完这条边之后那个点必然被删除，所以对于那个点，如果有时间在连向他的那条边之前的点，那么这些点也不能被删除，直到这个点被删除。

类似的递归下去是可以的，我们发现 $i$ 能存活当且仅当这样递归生成了一棵树。

于是 $O(nm)$ 对每个点 $i$ dfs 一下这棵树，枚举 $(i,j)$ 判一下树的交是不是空即可。

复杂度 $O(n^3+nm)$

$Code:$

```cpp
#include<bits/stdc++.h>
using namespace std ;
#define Next( i, x ) for( register int i = head[x]; i; i = e[i].next )
#define rep( i, s, t ) for( register int i = (s); i <= (t); ++ i )
#define drep( i, s, t ) for( register int i = (t); i >= (s); -- i )
#define re register
int gi() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N = 400 + 5 ; 
const int M = 1e5 + 5 ; 
int n, m, R, cnt, head[N], S[N][N], flag[N], vis[N] ; 
struct E {
	int to, next, w ; 
} e[M << 1] ;
void add( int x, int y, int z ) {
	e[++ cnt] = (E){ y, head[x], z }, head[x] = cnt,
	e[++ cnt] = (E){ x, head[y], z }, head[y] = cnt ; 
}
void dfs( int x, int t ) {
	if( vis[x] ) { flag[R] = 1 ; return ; }
	vis[x] = 1 ; 
	Next( i, x ) if( e[i].w < t ) dfs( e[i].to, e[i].w ) ;
}
signed main()
{
	n = gi(), m = gi() ; int x, y ; 
	rep( i, 1, m ) x = gi(), y = gi(), add( x, y, i ) ;
	rep( i, 1, n ) {
		R = i, memset( vis, 0, sizeof(vis) ) ; 
		dfs( i, m + 1 ) ; 
		rep( j, 1, n ) S[i][j] = vis[j] ; 
	}
	int Ans = 0 ;
	rep( i, 1, n ) rep( j, 1, n ) {
		if( flag[i] || flag[j] ) continue ; 
		++ Ans ; 
		rep( k, 1, n ) if( S[i][k] && S[j][k] ) { -- Ans ; break ; } 
	}
	printf("%lld\n", Ans / 2 ) ;
	return 0 ;
}
```

---

## 作者：strlen_s_ (赞：4)

我们不妨枚举每个 $(i,j)$，判断是否可行。

如果从 $1$ 到 $M$ 正向枚举，判断 $i$ 或 $j$ 是否会被杀掉，发现很难维护和判断，所以不妨反向枚举。

倘若 $i$ 是最终存活的那个幸运鸡，它要满足当前它所在的这个指定的火鸡对里的另一个火鸡 $x$ 一定在这是被杀死，为 $i$ 挡枪。

那么 $x$ 一定不能提前死去，否则就没有鸡为 $i$ 挡枪了。

所以 $x$ 是一定要保护的，那么与 $x$ 在同一火鸡对里的鸡也是要被保护的，否则 $x$ 也会提前死去。

于是对于 $i$ 可以构建一个标记数组 `protect`  ,表示 $i$ 要存活，必须保护哪些鸡。

同理，对 $j$ 也可以构建这个 `protect` 数组。

再来讨论 $(i,j)$ 不满足条件的情况。

很明显，在一对指定的火鸡 $ (u,v) $ 中，当 `protect[u]=1` 而且   `protect[v]=1` 时，$ (i,j) $不满足条件。

因为必须受保护的 $(u,v)$  中必有一个要死，那么 $ (i,j) $ 中也必有一个要死，所以无法满足条件。

至此，一个大致的暴力已经可以写出，时间复杂度 $ O(n^2m) $。


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e2+10,M=2e5+100;
int protect[N];
struct turkey{
	int x,y;
}a[M];
int n,m,ans;
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&a[i].x,&a[i].y);
	}
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){              		//枚举每个 i 与 j 
			memset(protect,0,sizeof(protect));		//将记录保护鸡的数组清零 
			protect[i]=protect[j]=1;		 		//将 i 与 j 记录为保护对象 
			bool isok=1; 
			for(int k=m;k>=1;k--){                  //从 m 到 1 循环，求需要保护的对象 
				if(protect[a[k].x]&&protect[a[k].y]){ //若在同一对火鸡中两个都需保护 
					isok=0;break;					//记录一下，退出 
				}
				if(protect[a[k].x])protect[a[k].y]=1;  //若x为需保护的对象，那么y也是要保护的对象，标记为1 
				else if(protect[a[k].y])protect[a[k].x]=1;// 同理 
			}
			ans+=isok;  							//统计答案 
		}
	}
	printf("%lld",ans);
	return 0;
}
```

竟然过了……

https://www.luogu.com.cn/record/82430526

尝试优化。

我们可以先处理出最后要有 $i$ ,需要保护哪些鸡，用一个二维标记数组   `protect[i][j]`  表示。

再枚举 $ (i,j) $,检查有没有一对火鸡两个都需要保护，并统计答案。

复杂度 $ O(nm+n^3) $。

```
#include<bits/stdc++.h>
#define int long long
#define re register
using namespace std;
int rd() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N=4e2+10,M=2e5+100;
bool protect[N][N];
bool mustdie[N];
struct turkey{
	int x,y;
}a[M];
int n,m,ans;
signed main(){
	n=rd(),m=rd();
	for(re int i=1;i<=m;i++){
		a[i].x=rd(),a[i].y=rd();
	}
	for(re int i=1;i<=n;i++){                       //预处理 
		protect[i][i]=1;
		for(re int j=m;j>=1;j--){
			if(protect[i][a[j].x]&&protect[i][a[j].y]){
				mustdie[i]=1;                          //如果当前这个鸡无论如何都会死，给他打上标记 
				break;
			}
			if(protect[i][a[j].x])protect[i][a[j].y]=1;
			else if(protect[i][a[j].y])protect[i][a[j].x]=1;
		}
	}
	for(re int i=1;i<=n;i++){
		if(!mustdie[i]){							//若当前鸡非必死 
			for(int j=i+1;j<=n;j++){
				if(!mustdie[j]){                    //同理 
					bool isok=1;
					for(int k=1;k<=n;k++)
						if(protect[i][k]&&protect[j][k]){ //如暴力 ，一一枚举判断 
							isok=0;break;
					}
					ans+=isok;
				}
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

https://www.luogu.com.cn/record/82472950

这个过程还可以进一步优化，用 `bitset` 维护它们 `protect[i][j]` 的交。

时间复杂度还可以进一步优化。

```
#include<bits/stdc++.h>
#define int long long
#define re register
using namespace std;
int rd() {
	char cc = getchar() ; int cn = 0, flus = 1 ;
	while( cc < '0' || cc > '9' ) {  if( cc == '-' ) flus = - flus ; cc = getchar() ; }
	while( cc >= '0' && cc <= '9' )  cn = cn * 10 + cc - '0', cc = getchar() ;
	return cn * flus ;
}
const int N=4e2+10,M=2e5+100;
bitset<N>protect[N];  
bool mustdie[N];
struct turkey{
	int x,y;
}a[M];
int n,m,ans;
signed main(){
	n=rd(),m=rd();
	for(re int i=1;i<=m;i++){
		a[i].x=rd(),a[i].y=rd();
	}
	for(re int i=1;i<=n;i++){
		protect[i][i]=1;
		for(re int j=m;j>=1;j--){
			if(protect[i][a[j].x]&&protect[i][a[j].y]){
				mustdie[i]=1;
				break;
			}
			if(protect[i][a[j].x])protect[i][a[j].y]=1;
			else if(protect[i][a[j].y])protect[i][a[j].x]=1;
		}
	}
	for(re int i=1;i<=n;i++){
		if(!mustdie[i]){
			for(int j=i+1;j<=n;j++){
				if(!mustdie[j]){
					if((protect[i]&protect[j]).count()==0)ans++;   //bitset 求交 
				}
			}
		}
	}
	printf("%lld",ans);
	return 0;
}
```

https://www.luogu.com.cn/record/82474444

至此，我们做完了这一道题，方法还是很巧妙的。

---

## 作者：PosVII (赞：4)

**前言**

------------

评分虚高，此题解只是提供这种数据过小导致一道题方法大幅度改变的暴力方法。

**分析**

------------

首先我们对于此题进行最朴素的暴力，得到思路如下：

首先枚举第 $i$ 和第 $j$ 只火鸡，那么从头到尾进行选择，当遇到 $i,j$ 和其它的火鸡进行选择的时候，我们就去掉那只火鸡。如果此时那只火鸡已经被吃，就往前寻找有没有方法能使这只应当被杀的火鸡存活。

这里不分类细讲，因为这种方法很明显是严重超时的，并且难以实现。

仔细思考，删除问题的解决方法都有倒着枚举命令，这样我们就能免去拯救已经被吃的火鸡的时间了。留给我们倒着枚举的时间复杂度是 $O(m)$ 的，也就是说我们需要线性解决每对火鸡是否可行。

继续沿用删除问题的思路，我们在最后一定保留第 $i$ 和第 $j$ 只火鸡，那么每次于与它们进行选择的火鸡一定要活到那时候，我们就记录这只火鸡，让它享受和第 $i$ 和第 $j$ 只火鸡相同的待遇。如果出现两只火鸡都不能被吃的情况，那么就不计入最终答案。

那么代码就确定了，虽然在此时还可以继续优化，但是因为出题人的失误，导致我们的暴力做法也能通过此题，那么我们可以直接暴力跑路，为后面的题目留更多时间。

**code**

------------

```
#include<bits/stdc++.h>
using namespace std;
const int MAXN=4e2+5,N=1e5+5;
int n,m,x[N],y[N],ans;
bool h[MAXN];
int main() {
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;++i) scanf("%d %d",&x[i],&y[i]);
	for(int i=1;i<=n;++i) {
		for(int j=i+1;j<=n;++j) {
			memset(h,0,sizeof(h));
			h[i]=h[j]=1;
			for(int k=m;k>=1;--k) {
				if(h[x[k]]&&h[y[k]]) {
					--ans;
					break;
				}
				if(h[x[k]]) h[y[k]]=1;
				if(h[y[k]]) h[x[k]]=1;
			}
			++ans;
		}
	}
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：luoguliujiaxin (赞：3)

有 $2$ 个显而易见的性质：
1. 一只火鸡只会死一次。
2. 火鸡死后不会复生。

因此，对于第 $i$ 个行动 $(x_i,y_i)$，若 $x_i$ 必须存活，则 $y_i$ **必须**满足以下条件：
- 在第 $1\sim i-1$ 个行动**后**，$y_i$ 必须存活（依据性质1）。
- 在第 $i+1\sim n$ 个行动**前**，$y_i$ 已经死去（依据性质2）。

我们钦定火鸡 $i$ 在 $M$ 个人行动后仍然存活。

定义 $dead_j$ 表示第 $j$ 只火鸡此时是否被吃，$choose_t$ 表示第 $t$ 轮吃哪只火鸡（$choose_t=0$ 表示吃哪只均可），$s_{i,j}$ 表示 $i$ 存活是否不会导致 $j$ 死亡。由于 $i$ 不能被吃，我们初始化 $dead_i=1$。

先倒序遍历所有操作，处理出所有的 $choose_t$。此时，若有操作 $(x,y)$ 满足 $dead_x\land dead_y$，则本轮无论吃哪只火鸡均会导致 $i$ 死亡，即 $i$  不可能存活。

再正序遍历所有操作，处理出**最终**会死亡的火鸡（即 $s_{i,j}$）。此时，对于每次操作 $(x,y)$，仅有以下 $3$ 种情况：
1. 必须吃掉火鸡 $x$。
2. 必须吃掉火鸡 $y$。
3. 吃掉火鸡 $x$ 和 火鸡 $y$ 均可。

对于第 $3$ 种情况，若操作前它们均存活，则操作后它们均可能存活（在对方被吃的情况下），否则它们均不可能存活。

遍历完成后，当且仅当 $s_{i,j}$ 和 $s_{j,i}$ 均成立时，$(i,j)$ 能同时存活。

最后给出正确性的感性理解：

若一对 $(i,j)$ 不能同时存活，则必须**满足以下条件之一**：
- **$j$ 永远无法存活**或 $i$ 存活会导致 $j$ 死亡。
- **$i$ 永远无法存活**或 $j$ 存活会导致 $i$ 死亡。

这些都被判断过了。因此，对于任意一对满足条件的 $(i,j)$，根据上述操作，它一定会被计入答案。

时间复杂度 $O(nm+n^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=405;
const int maxm=100005;
int read(){//快读
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while( isdigit(ch)){ret=(ret<<3)+(ret<<1)+(ch&15);ch=getchar();}
	return ret*f;
}
int n,m,cnt;
struct operate{//操作
	int x,y;
	int chs;//chs表示选择吃哪只火鸡
}opt[maxm];
bool s[maxn][maxn],dead[maxn];
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		opt[i].x=read();
		opt[i].y=read();
	}
	for(int i=1;i<=n;++i){
		memset(dead,0,sizeof dead);
		bool alive=true;dead[i]=1;
		for(int j=m;j;--j){
			if(dead[opt[j].x]&&dead[opt[j].y]){//两只都不能吃
				alive=false;
				break;
			}else if(dead[opt[j].x]){//火鸡x不能吃，吃火鸡y
				opt[j].chs=opt[j].y;
				dead[opt[j].y]=1;
			}else if(dead[opt[j].y]){//火鸡y不能吃，吃火鸡x
				opt[j].chs=opt[j].x;
				dead[opt[j].x]=1;
			}else opt[j].chs=0;//随便吃
		}
		if(!alive)//火鸡i无法存活
			continue;
		for(int j=1;j<=m;++j){//判断其他火鸡能否存活
			if(!opt[j].chs){
				dead[opt[j].x]|=dead[opt[j].y];
				dead[opt[j].y]|=dead[opt[j].x];
			}
		}
		for(int t=1;t<=n;++t) s[i][t]=!dead[t];
	}
	for(int i=1;i<=n;++i)
	for(int j=i+1;j<=n;++j)
	if(s[i][j]&&s[j][i]) cnt++;
	printf("%d",cnt);
	return 0;
}
```


---

## 作者：二叉苹果树 (赞：2)

## 题意

共有 $n$ 只火鸡，并给出了 $m$ 对火鸡，每对火鸡中都会选择其中一只吃掉，问最终还有多少对 $(i,j)$ 火鸡活着。

需要注意的是，本题并不是求整体的最优解，对于每组的询问都是独立的，我们可以任意地改变对于每一对被吃的火鸡中的选择。

## 步骤

对于第 $i$ 只火鸡，我们考虑如果想让其在 $m$ 次吃的过程后仍然存活，需要做出怎样的决策。

对于 $m$ 对火鸡中存在第 $i$ 只火鸡的 $k$ 对， 我们需要满足在这 $k$ 对吃的指令中始终不选择第  $i$ 只火鸡，也就是始终选择除了第 $i$ 只火鸡的另一只。

预处理时，我们依次枚举每只火鸡，并对于每只火鸡枚举每队吃的指令，将为了保护第 $i$ 只火鸡需要「献祭」出的火鸡存入第 $i$ 个集合。若第 $i$ 只火鸡在某次吃的指令中，另一只火鸡已经存在于它的集合中，也就说明另一只火鸡在先前的指令中已经被吃，这次指令中，只能吃第 $i$ 只火鸡。也就是说，在出现了这种情况下，第 $i$ 只火鸡是必死的。

最后考虑枚举 $(i,j)$ 时如何判断第 $i$ 只火鸡和第 $j$ 只火鸡能够同时存活下来。很显然，首先第 $i$ 只火鸡和第 $j$ 只火鸡不能是必死的。其次，第 $i$ 只火鸡不能存在于为第 $j$ 只火鸡献祭的集合中，第 $j$ 只火鸡不能存在于为第 $i$ 只火鸡献祭的集合中。如此保证了第 $i$ 只火鸡和第 $j$ 只火鸡不会出现互相保护从而献祭其中之一的情况。

## 实现

注意，$(i,j)$ 是任意的数对，而不是题目中给出的 $m$ 对指令。

枚举 $m$ 条指令时，需要按照从后往前的顺序，否则可能会出现神奇的 $\rm{RE}$ 现象，~~想一想，为什么~~。

剩下的代码实现中可以使用 $\rm{map}$ 或 $\rm{bitset}$ 轻松实现，$\rm{STL}$ 中的函数对本题提供了很大的便利。


```cpp
	for(int i=1;i<=n;i++)
	{
		f[i][i]=1;
		for(int j=m;j>=1;j--)
		{
			if(f[i][x[j]]&&f[i][y[j]])
			    g[i]=1；
			else if(f[i][x[j]])
			    f[i][y[j]]=1;
			else if(f[i][y[j]])
			    f[i][x[j]]=1;
		}
	}
```
这里我们用 $f[i][j]$ 来记录对于第 $i$ 只火鸡，是否需要献祭第 $j$ 只火鸡，$g[i]$ 记录第 $i$ 只火鸡是否是必死的。

对于每一对火鸡，将其中之一加入献祭队列，若两只火鸡都已经死亡，说明此时保护第 $i$ 只火鸡的情况是不存在的，第 $i$ 只火鸡是必死的。

最后枚举数对 $(i,j)$ ，其中 $1\le i\le n , i+1\le j \le n $ 即可。这里的 $f[i][j]$ 使用 $\rm{map}$ 定义，可以使用 $\rm{bitset}$ 中的 $\rm{count}$ 快速判断两者是否在对方的集合之中。

```cpp
	for(int i=1;i<=n;i++)
		if(!g[i])
		    for(int j=i+1;j<=n;j++)
			    if(!g[j])
			    	res+=!((f[i]&f[j]).count());
```


---

## 作者：_XHY20180718_ (赞：2)

## [更好的阅读体验。](https://www.luogu.com.cn/blog/399475/at2389-ti-xie)

## 题目大意： 
有 $N$ 只火鸡，编号为 $1$ 到 $N$，有 $M$ 个人，每人依次准备来吃指定的两只火鸡 $x$ 和 $y$。

1. 若 $x$ 和 $y$ 都活着，那么这个人将会等概率地随机吃掉一只。  
2. 若 $x$ 和 $y$ 恰好活着一只，那么这个人将会吃掉活着的这只。  
3. 若 $x$ 和 $y$ 都已经死亡，那么只好什么都不做。

求有多少对火鸡**可能**都还活着。

## 题目分析：
由于这道题只有四百只鸡，我们可以先考虑枚举暴力每对鸡是否能活着：

如果我们要保护一只鸡，那么想吃这个鸡的人必须得吃他想吃的另一只鸡。

所以我们又要在这个人吃鸡之前保护好这另一只鸡，否则无法保护我们要保护的鸡。

如何保护好这只鸡呢，你可以把上面那两句话重新读一遍。

总而言之，就是要在杀这只鸡或结束流程之前保护好这只鸡。

另外，保护鸡时顺着做不是很好做，我们可以倒着推。

时间复杂度：$O(n^2m)$。

## [AC code1](https://www.luogu.com.cn/paste/4h8m93ys)

然而，这道题似乎~~神奇的在某OJ上加强了数据~~。

## 需要用到的用的东西： [Bitset](https://oi-wiki.org/lang/csl/bitset/)。

考虑优化，我们可以预处理出要留下一个鸡，必须要保护哪些鸡。

然后我们就只用枚举不必须保护的鸡了，即只需枚举一次 $n$。

然后再用 Bitset 容器优化一下，之后就完全可以过了。

时间复杂度：$O(\dfrac{n^3+nm}{w})$。

## AC code2
```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
const int N=410,M=2e5+10;
int n,m,a[M][2],ans;
bitset<N> p[N],f;
void write(re int x){
	if(x>=10)write(x/10);
	putchar(x%10+48);
	return;
}
inline int read(){
	re int x=0;
	re char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();
	return x;
}
signed main()
{
	n=read(),m=read();
	re int x,y,i,j,k;re bool flag;
	for(i=1; i<=m; i++)
		a[i][0]=read(),a[i][1]=read();
	for(i=1; i<=n; i++)
	{
		for(j=1;j<=n;j++)
			p[j].reset();
		f.reset();
		for(j=i+1;j<=n;j++)
			p[j][j]=p[i][j]=1;
		for(j=m; j>=1; j--)
		{
			x=a[j][0],y=a[j][1];
			f|=p[x]&p[y];
			p[x]=p[y]=(p[x] xor p[y]);
		}
		for(j=i+1;j<=n;j++)
			ans+=!f[j];
	}
	write(ans);
	return 0;
}
```

---

## 作者：Rye_Catcher (赞：2)

### 题目链接

https://www.luogu.org/problemnew/show/AT2389


### 闲扯

考场20分爆搜走人 \cy

话说这几天T3都很考验思维啊



### 分析

我们先钦定一只鸡先必须活着,所以呢我们需要逆着倒推每一组关系,然后把为了保证我们钦定的鸡活着必须杀的鸡放进一个集合,为了方便表示用$f[now][i]=1/0$表示钦定第now只鸡活着第$i$只鸡最终有没有加入集合;

对于一对关系$(a,b)$,如果$f[now][a]=1$,那么$f[now][b]$显然必须置为1加入集合,因为a这只鸡为了保证now不被杀掉已经在一条边中被杀掉,为了保证当前这条边合法则必须杀掉b(注意关系是倒着枚举的)

但这是有个问题,就是如果$f[now][a]$&$f[now][b]=1$说明关系矛盾,$now$必须死,为啥?

![i8WxW6.png](https://s1.ax1x.com/2018/10/05/i8WxW6.png)

我们考虑没有这种情况,将鸡视为点,关系视为边,显然我们的集合实际上是一个以now为根节点的树,而且满足$x$到$fa[x]$的关系比$fa[x]$到$fa[fa[x]]$的边次序要早(但是在枚举时因为是倒着枚举是先构成前者)

如果这时候加入一条边连接两个已经在集合中的点$(a,b)$,由于1号边次序要比2,3边早,所以先必须在a,b中选一个杀死满足1号边的关系.但是我们为了让now不死,我们必须要让a点因为2号边死去,b因为3号边死去.出现了这种情况显然就不可能了,所以需要记录一下$now$存活是不可行的



最后假设已经遍历完,获得钦定每个点活着的时候要杀掉的鸡的集合(虽然不一定合法)

然后对于每一只鸡判断是否能与编号靠后的另一只鸡一起存活,怎么判断呢?

首先如果如果其中有只鸡本身无法存活则特判continue,但是还有种非法的情况,就是存在一只鸡为了满足$a$活必须死,又同时满足$b$活下来也必须死.这样的话$a,b$无法同时存活

这其实很显然的,边有先后顺序,你为了满足其中一只鸡另一只鸡就一定不可行,所以这种情况我们可以把两个鸡的集合并起来看看有没有1存在



### 代码

```c++
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <bitset>
#define ll long long 
#define ri register int 
using std::min;
using std::bitset;
using std::max;
template <class T>inline void read(T &x){
    x=0;int ne=0;char c;
    while(!isdigit(c=getchar()))ne=c=='-';
    x=c-48;
    while(isdigit(c=getchar()))x=(x<<3)+(x<<1)+c-48;
    x=ne?-x:x;return ;
}
const int maxn=405;
const int inf=0x7fffffff;
bitset <maxn> o[maxn];
bool ok[maxn];
int a[100005],b[100005],m,n;
int main(){
    int x,y;
    bool flag=0;
    read(n),read(m);
    for(ri i=1;i<=m;i++)read(a[i]),read(b[i]);
    for(ri i=1;i<=n;i++){
        o[i][i]=1;flag=0;
        for(ri j=m;j>=1&&!flag;j--){
            x=o[i][a[j]],y=o[i][b[j]];
            if(x&y){
                ok[i]=1;
                flag=1;continue;
            }
            if(x){o[i][b[j]]=1;}
            if(y){o[i][a[j]]=1;}
        }
    }
    ll ans=0;
    for(ri i=1;i<=n;i++){
        if(ok[i])continue;
        for(ri j=i+1;j<=n;j++){
            if(ok[j])continue;
            if(!((o[i]&o[j]).any()))ans++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：GIFBMP (赞：1)

神仙题。

我们发现直接算概率的话是不可做的，但是题目只要求所有可能共同存活的火鸡对数，那么我们可以把等概率选择一只火鸡变成选择一种选择火鸡的方案。那么题目就转化为：是否存在一种方案，使得两只火鸡最后能够共同存活。

正着推不太好做，考虑倒推。定义 $f_{i,j}$ 表示为了使 $i$ 存活，是否一定要保留 $j$，也就是说，当面临在 $(i,j)$ 中二选一的情况时，$j$ 必须在此时是活着的。当然情况不止这么一种，我们发现，如果 $f_{i,j}=1$ 时面临着在 $(j,k)$ 中二选一的情况，那么也必须保留 $k$，即 $f_{i,k}=1$。因为这种链状结构是前面依赖后面，所以我们要倒序枚举所有的操作。初值显然，为 $f_{i,i}=1$。

那么我们处理出这个 $f$ 数组有什么用呢？考虑在转移的过程中，此时枚举到一对操作 $(j,k)$，此时 $f_{i,j}=f_{i,k}=1$，我们发现，此时根据上面的推导，必须同时保留 $j,k$，而 $j,k$ 又必须被吃掉一个，因此 $i$ 在最后不可能存活。

我们再推导一下，对于一对 $(i,j)$，如果存在一个 $x$ 使得 $f_{i,x}=f_{j,x}=1$，不妨设为了保留 $i$，$x$ 必须被吃掉的操作编号为 $a$，为了保留 $j$，$x$ 必须被吃掉的操作编号为 $b$，假设 $a<b$，因为 $x$ 在 $a$ 操作时就被吃掉，在操作 $b$ 时，$x$ 就不能被选，因此最后 $j$ 不能存活；对于 $a>b$ 的情况同理，因此我们得出了一个结论：

对于一对 $(i,j)$，它们能共同存活，当且仅当 $\forall k\in [1,n]\cap\mathbb{N}^{*}$，$[f_{i,k}=0]\lor [f_{j,k}=0]$

然后就做完了，时间复杂度 $\Theta(nm+n^3)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 1e5 + 10 ;
int n , m , ans , f[410][410] , a[MAXN] , b[MAXN] , vis[410] ;
int main () {
	scanf ("%d%d" , &n , &m) ;
	for (int i = 1 ; i <= n ; i++) f[i][i] = 1 ;
	for (int i = 1 ; i <= m ; i++) scanf ("%d%d" , &a[i] , &b[i]) ;
	for (int i = 1 ; i <= n ; i++)
		for (int j = m ; j ; j--) {
			int x = f[i][a[j]] , y = f[i][b[j]] ;
			if (x && y) {vis[i] = 1 ; break ;}
			if (x) f[i][b[j]] = 1 ; 
			if (y) f[i][a[j]] = 1 ;
		}
	for (int i = 1 ; i <= n ; i++) {
		if (vis[i]) continue ;
		for (int j = i + 1 ; j <= n ; j++) {
			if (vis[j]) continue ;
			bool flag = 1 ;
			for (int k = 1 ; k <= n ; k++)
				if (f[i][k] && f[j][k]) {flag = 0 ; break ;}
			ans += flag ;
		}
	}
	printf ("%d\n" , ans) ;
	return 0 ;
}
```

---

## 作者：Violet___Evergarden (赞：1)

假设我们现在要尽力保留第 $i$ 只鸡，那么我们倒着考虑每一个选择，当遇到 $ (x,i)$ 时，此时肯定要干掉 $x$，那么在这个选择之前一定不能干掉 $x$，所以当遇到 $(x,y)$ 时，肯定要干掉 $y$，那么在这个选择之前一定不能干掉 $y$......

所以可以设一个数组 $need_{i,j}$ 表示要保留 $i$ 时是否需要保留 $j$，首先初始化 $need_{i,i} \gets 1$，倒序枚举选择 $(a,b)$，若选择中其中一个数需要保留（假设是 $a$），此时若 $b$ 也需要保留，那么 $i$ 就一定不可能活着，否则 $ need_{i,b} \gets 1$。

枚举两只可能活着鸡 $(i,j)$，若存在 $k$ 使 $need_{i,k}=need_{j,k}=1$，那么这两只鸡就不可能同时活着，因为此时两只鸡都需要干掉 $k$，但每只鸡只能被干掉一次。
```cpp
#include <iostream>
#include <bitset>
using namespace std;
const int kMaxN=401;
const int kMaxM=1e5+1;
int n,m,ans;
int a[kMaxM],b[kMaxM];
bitset<kMaxN>need[kMaxN],bs;
int main()
{
//freopen("c.in","r",stdin);
//freopen("c.out","w",stdout);
cin>>n>>m;
for(int i=1;i<=m;i++)
{
  cin>>a[i]>>b[i];
}
for(int i=1;i<=n;i++)//枚举要保留的鸡
{
  need[i][i]=true;
  //cout<<i<<" "<<i<<"\n";
  for(int j=m;j>=1;j--)//倒序枚举选择
  {
    //cout<<j<<" "<<a[j]<<" "<<b[j]<<" "<<need[i][a[j]]<<" "<<need[i][b[j]]<<"\n";
    if(need[i][a[j]]&&need[i][b[j]])//若两只鸡都要保护
    {
      bs[i]=true;//那么i必死
      break;
    }
    else if(!need[i][a[j]]&&!need[i][b[j]])continue;
    else//只有其中一只要保护，就把另一只也打上要保护的标记
    {
      if(need[i][a[j]])
      {
        need[i][b[j]]=true;
      }
      else
      {
        need[i][a[j]]=true;
      }
    }
  }
}
for(int i=1;i<=n;i++)
{
  if(bs[i])continue;//过滤掉必死的鸡
  for(int j=i+1;j<=n;j++)
  {
    if(bs[j])continue;
    bool flag=true;
    for(int k=1;k<=n;k++)
    {
      if(need[i][k]&&need[j][k])//若(i,j)都需要干掉k
      {
        flag=false;
        break;
      }
    }
    if(flag)
    {
      ans++;
    }
  }
}
cout<<ans;
return 0;
}
```

---

## 作者：Demoe (赞：1)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/AT2389)

## $\text{Description}$

- 有 $n$ 个东西和 $m$ 个人，每人依次过来，且每人有一对数 $(x,y)(x<y)$。
- 对于每个人有如下操作：
   - 若此时 $x$ 和 $y$ 都还在，随便扔掉一个。
    - 若此时 $x$ 和 $y$ 只有一个在，扔掉它。
    - 若此时 $x$ 和 $y$ 都扔掉了，不做操作。
- 求最后 $(i,j)$ 有概率都没被扔掉的东西对数。

## $\text{Solution}$

考虑倒推，即从最后一个人开始向前进行。

我们考虑 $(i,j)$ 最后都没被扔掉，则在前面某人为 $(x,i)$ 时，我们扔掉的一定是 $x$。

那么此时我们就需要保证再往前 $x$ 不能被扔掉。

若前面出现 $(x,y)$ 且都不能被扔掉，那么 $(i,j)$ 一定不是一组解。

注意到这里每次拓展实际是一个的拓展，而非一对的拓展。

我们可以将枚举 $(i,j)$ 换成枚举 $i$，记录下如果要留下 $i$ 前面一定不能被扔掉的数集 $S_i$。

此时若 $S_i \cap S_j=\varnothing$，则 $(i,j)$ 满足题意。模型意义下即表示 $i$ 和 $j$ 前面不能被扔掉的东西不重复，因为在 $S_i$ 中所有除 $i$ 的东西都会被扔掉，而东西不能重复扔掉。

考虑到 $S_i$ 和 $S_j$ 实际上只要对位完成与运算，用 bitset 存储即可。

时间复杂度 $O(nm+\dfrac{n^3}{\omega})$。

关于倒流的话，如果想再练练这东西的话，可以做一做这题 [[JOI 2016 Final]断层](https://www.luogu.com.cn/problem/P5103)。

## $\text{Code}$

```cpp
const int N=405,M=1e5+5;
int n,m,a[M],b[M],ans;
bool tag[N];
bitset<N> s[N];

// ----------  ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);rd(m);
	for(re i=1;i<=m;++i) rd(a[i]),rd(b[i]);
	for(re i=1;i<=n;++i) s[i][i]=1;
	for(re i=1;i<=n;++i)
		for(re j=m;j>0;--j){
			if(s[i][a[j]]&&s[i][b[j]]){tag[i]=1;break;}
			if(s[i][a[j]]) s[i][b[j]]=1;
			if(s[i][b[j]]) s[i][a[j]]=1;
		}
	for(re i=1;i<=n;++i)
		if(!tag[i]){
			for(re j=i+1;j<=n;++j)
				if(!tag[j]){
					if((s[i]&s[j]).count()==0) ++ans;
				}
		}
	wr(ans);puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：cosf (赞：0)

# [AT_agc016_e](https://atcoder.jp/contests/agc016/tasks/agc016_e) [Poor Turkeys](https://www.luogu.com.cn/problem/AT_agc016_e)

题意
---
不需要解释了吧，直接跳过

---

思路
---

我提供一个很神奇的做法，时间复杂度为 $O(N^2M)$，看样子超时，但是常数特别的小，在随机数据下常数几乎为 $0$，然后我就过了这道题。

我们可以枚举每一对 $(i, j)$，看看能不能全部活下来，然后记录一下对数就可以了。

怎么判断能不能都活下来呢？我们可以用**倒推法**。

我们从最后一个人开始判断。一开始，我们选中的 $(i, j)$ 两只鸡都是要**被保护的**~~，因为死了就结束了~~，如果这个人选的那两只鸡就是被保护的，那么他就算 S 哪一只都会导致后面一定会 S 掉 $(i, j)$，这时直接结束判断。如果这个人选的只有一只是被保护的，那么他只能 S 另外一只，也就是前面的人都不能 S 这只鸡，即我们可以把另一只也设成要被保护的。如果把每个人都判断一遍，都可以不把被保护的鸡 S 掉，那么 $(i, j)$ 就能都活下来。

那么接下来就是实现部分了。

大家可以参考一下代码。

[AC Code](https://www.luogu.com.cn/record/92729866)
---

```cpp
#include <iostream>
using namespace std;

int v[405]; // 保护数组
int a[100005]; // 那个人选的第一只鸡
int b[100005]; // 第二只“只因”

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i] >> b[i];
	}
	int cnt = 0;
	int add;
	for (int i = 1; i < n; i++)
	{
		for (int j = i + 1; j <= n; j++) // 强行枚举
		{
			add = 1;
			for (int k = 1; k <= n; k++) // 清零
			{
				v[k] = 0;
			}
			v[i] = v[j] = 1; // 被保护
			for (int k = m; k >= 1; k--)
			{
				if (v[a[k]] && v[b[k]]) // 都被保护了
				{
					add = 0; // 那就活不下来
					break;
				}
				if (v[a[k]]) // 保护另一只
				{
					v[b[k]] = 1;
				}
				else if (v[b[k]])
				{
					v[a[k]] = 1;
				}
			}
			cnt += add; // 如果循环正常退出，证明可以都活下来，加1，否则活不下来，加0。
		}
	}
	cout << cnt << endl; // 结果
	return 0;
}
```

写在最后：测试点最长时间为 $1.17s$，远远没有限制的 $2s$。这个方法是可以过的。


---

