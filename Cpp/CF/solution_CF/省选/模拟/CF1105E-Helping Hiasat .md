# Helping Hiasat 

## 题目描述

你在某社交网站上面注册了一个新账号，这个账号有$n$($n\leq 10^5$)次记录。要么就是你更改过一次ID，要么就是一个ID为$s$($|s|\leq 40$)的朋友访问过你的空间。

你有$m$($m\leq 40$)个朋友。每一个朋友都会访问你的空间至少一次。如果这一个朋友每一次访问你的空间的时候，你的ID和它的ID一样，那么他就会高兴。
求你最多能让多少人高兴。

## 样例 #1

### 输入

```
5 3
1
2 motarack
2 mike
1
2 light
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 3
1
2 alice
2 bob
2 tanyaromanova
```

### 输出

```
1
```

# 题解

## 作者：hsfzLZH1 (赞：6)

## 题目大意

oql 有 $m$ 个好友，发生了 $n$ 个事件，每次事件都是如下的形式：

1. oql 可以改变他的用户名， oql 在同一时间内只能拥有一个用户名，在其余时间内 oql 不能改变他的用户名；

2. 一位好友 $s$ 访问了他的主页。

我们称一位好友 $s$ 是高兴的，当且仅当在 ** 每一次 ** 该好友访问 oql 的主页时，看到 oql 的用户名正好是 $s$ 。

现在给出 $n,m$ 和每一个事件，求 oql 最多能得到几个开心的好友。

$1\le n\le 10^5,1\le m,|s|\le 40$

## 解题思路

用户名是字符串，我们用 `map` 判断其是否原来存在，给其编号，将字符串转化为数字。

我们将每个好友访问 oql 主页的状况对每个好友表示成一个最多有 $10^5$ （位数等于事件中 1 的个数）位的二进制数，其中若这一位是 1 ，则表示这个好友在这个 1 事件后访问了 oql 的主页，否则表示没有访问。

由于 oql 在同一时间内只能拥有一个用户名，所以我们认为两位好友是不相冲突的当且仅当两位好友的二进制数按位与的值为 $0$ 。现在，我们的问题转化成，给出 $m$ 个 $n$ 位二进制数的集合，从其中取出最多的数，使得这些数两两互质。

我们将其中任意两个二进制数取出，单独考虑，若这两个数按位与的值不为 $0$ ，说明这两个人不能共存，将这两个人之间连一条边，问题就转化成了 ** 图上最大独立集 ** 的问题。这是 NP 完全的。

如果考察两个二进制数，若这两个数按位与的值为 $0$ ，说明这两个人能共存，将这两个人之间连一条边，问题就转化成了 ** 最大团 ** 问题，这也是 NP 完全的。

事实上，上面两个图互为补图，这题就是一道 ** 最大独立集做补集转求最大团 ** 的问题了。

对于求最大团，我们已经有现成解法，利用 Bron–Kerbosch 算法，可以在 $O(2^{\frac n 2})$ 的时间复杂度内解决这个问题。（ $n$ 为节点数）

总的时间复杂度为 $O(n\times m^2+2^{\frac m 2})$ 。空间复杂度为 $O(nm)$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<string>
#include<map>
using namespace std;
const int maxn=50;
bool mp[maxn][maxn];
int some[maxn][maxn],none[maxn][maxn],all[maxn][maxn];
int n,m,ans,op,id,cnt,cur;
bool tf[maxn][100010];
string nm;
map<string,int>st;
void dfs(int d,int an,int sn,int nn)
{
	if(!sn&&!nn)ans=max(ans,an);
	int u=some[d][0];
	for(int i=0;i<sn;i++)
	{
		int v=some[d][i];
		if(mp[u][v])continue;
		for(int j=0;j<an;j++)all[d+1][j]=all[d][j];
		all[d+1][an]=v;
		int tsn=0,tnn=0;
		for(int j=0;j<sn;j++)if(mp[v][some[d][j]])some[d+1][tsn++]=some[d][j];
		for(int j=0;j<nn;j++)if(mp[v][none[d][j]])none[d+1][tnn++]=none[d][j];
		dfs(d+1,an+1,tsn,tnn);
		some[d][i]=0,none[d][nn++]=v;
	}
}
int work()
{
	ans=0;
	for(int i=0;i<n;i++)some[1][i]=i+1;
	dfs(1,0,n,0);
	return ans;
}
int main()
{
	scanf("%d%d",&m,&n);
	while(m--)
	{
		scanf("%d",&op);
		if(op==1)cur++;
		else
		{
			cin>>nm;
			if(st[nm])id=st[nm];
			else id=++cnt,st[nm]=id;
			tf[id][cur]=true;
		}
	}
	for(int i=1;i<=n;i++)for(int j=1;j<i;j++)
	{
		bool jd=true;
		for(int k=1;k<=cur;k++)if(tf[i][k]&&tf[j][k]){jd=false;break;}
		if(jd)mp[i][j]=mp[j][i]=true;
	}
	printf("%d\n",work());
	return 0;
}
```

---

## 作者：CYJian (赞：5)

当时我是写对了这道题的。。最后还剩大概一分钟的时间$Debug$对了，然后正要交的时候。。

# 网炸了。。

~~什么时候打CF也变成了网速大赛啊。。~~

----

首先可以想到的是，如果一个朋友$A$高兴了，那么在相邻两次修改ID的记录中，如果有$A$的访问记录，那么同样在这两次修改记录中访问过的其他朋友是不可能高兴的。

然后。。我们就可以把相邻两次修改ID中访问过的人互相连边，然后答案就是最大独立集的大小了。

这样的话。。

去吧，模拟退火！！！

思路非常简单，代码也很~~简单~~丑陋

```
#include <bits/stdc++.h>

using namespace std;

#define reg register
#define db double
#define bit bitset<MAXN + 1>
#define MAXN 40

const db deltaT = 0.998;//玄学调参
const db eps = 1e-15;

struct Node {
	int a[MAXN + 1];
}res;

int n;
int Ans;
bit f[MAXN + 1];

inline int Checker(reg Node);
inline void Simulate_Anneal();

map<string,int>mp;
int opt[200000];
int s[200000];
bool in[44];

int main() {
	reg int m, cnt = 0;
	cin >> m >> n;
	for(reg int i = 1; i <= m; i++) {
		cin >> opt[i];
		if(opt[i] % 2 == 0) { //这里先用map hash一下
			string S; 
			cin >> S;
			if(!mp[S]) {
				mp[S] = ++cnt;
			}
			s[i] = mp[S];
		}
	}
	for(reg int i = m; i >= 1; i--) { //连边
		if(opt[i] & 1) {
			for(reg int j = 1; j <= n; j++) {
				if(in[j])
				for(reg int k = j + 1; k <= n; k++) {
					if(in[k]) f[j][k] = f[k][j] = 1;
				}
			}
			memset(in, 0, sizeof(in)); //别忘了清空
		}
		else in[s[i]] = 1; //在两次修改ID中访问过
	}

	srand(time(NULL));
	for(reg int i = 1; i <= 5; i++) //玄学srand
		srand(1LL * rand() * rand() % 19260817 * rand() % 998244353 * rand() % 19491001 * rand() % 998244853 * rand() % 23333333333);
	for(reg int i = 1; i <= n; i++) res.a[i] = i; Ans = Checker(res); //先预处理一下一个答案
	while(clock() <= CLOCKS_PER_SEC * 1.7) Simulate_Anneal(); //时限两秒，不T就好了
	printf("%d\n", Ans);
}

inline int Checker(reg Node a) { //看看能选出多少个点来。
	reg bit S; S.reset();
	for(reg int i = 1; i <= n; i++)
		if(!(S & f[a.a[i]]).count())
			S[a.a[i]] = 1;
	return S.count();
}

inline void Simulate_Anneal() { //模拟退火
	reg db T = 192608;
	reg Node Test = res;
	while(T >= eps) {
		reg int x = rand() % n + 1;
		reg int y = rand() % n + 1;
		Test = res; swap(Test.a[x], Test.a[y]);
		reg int rt = Checker(Test);
		reg int delta = rt - Ans;
		if(delta > 0) Ans = rt, res = Test;
		else if(exp(delta / T) * RAND_MAX > rand()) res = Test;
		T *= deltaT;
	}
}
```

---

## 作者：litble (赞：4)

首先，连续的一段1相当于只有一个，所以我们可以将本题看做有若干段时间，每段时间有若干个朋友有要求，一段时间内只能满足一位朋友的要求，一个朋友的要求全被满足权值+1，问最大权值。

接着我们可以得到若干两个朋友不能被同时满足的信息，原题就转化为了最大独立集问题。

由于朋友的个数是40，我们可以对于前20个朋友，算出每一个集合是否是一个独立集，对于后20个，也算出是否是独立集。

对后20个朋友做一次高维前缀和，求出每一个集合及其子集中最大的权值，权值定义为：若这个集合是独立集，权值为这个集合包含的点数，否则为0。

然后对于前20个朋友组成的独立集，求出这个集合在被保证选出的情况下，后20个朋友有哪些朋友是能被选的。那么这些能被选的朋友组成的集合，以及它的子集，都是可能被选的，用我们预处理的高维前缀和就能获得答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
typedef long long LL;
const int N=100005,LIM=1048580;
int n,m,cnt,js,ans;LL k1,k2;
int op[N],p[N],yes[LIM],orz[LIM];
LL bin[42],a[N],no[42];
map<string,int> mp;

int getid(string s) {
	if(!mp[s]) mp[s]=++cnt;
	return mp[s];
}
void prework() {
	for(RI i=1;i<=js;++i)
		for(RI j=1;j<=m;++j)
			if(bin[j-1]&a[i]) no[j]|=a[i];
	for(RI i=1;i<=m;++i) no[i]^=bin[i-1];
	
	k1=m/2,k2=m-k1;//预处理前一半朋友和后一半朋友的独立集
	for(LL zt=0;zt<bin[k1];++zt) {
		yes[zt]=1;
		for(RI i=1;i<=k1;++i)
			if(zt&bin[i-1]) {if(no[i]&zt) {yes[zt]=0;break;}}
	}
	for(LL zt=0;zt<bin[k2];++zt) {
		orz[zt]=0;
		for(RI i=1;i<=k2;++i)
			if(zt&bin[i-1]) {
				if(no[i+k1]&(zt<<k1)) {orz[zt]=0;break;}
				else ++orz[zt];
			}
	}
}
void work() {
	for(RI i=0;i<k2;++i)//高维前缀和
		for(LL zt=0;zt<bin[k2];++zt)
			if(zt&bin[i]) orz[zt]=max(orz[zt],orz[zt^bin[i]]);
	for(LL zt=0;zt<bin[k1];++zt) {//枚举前一半朋友的独立集
		if(!yes[zt]) continue;
		int js=0;LL nono=0;
		for(RI i=1;i<=k1;++i)
			if(zt&bin[i-1]) nono|=no[i],++js;
		js+=orz[((bin[m]-1)^nono)>>k1];
		if(js>ans) ans=js;
	}
}
int main()
{
	string s;
	scanf("%d%d",&n,&m);
	for(RI i=1;i<=n;++i) {
		scanf("%d",&op[i]);
		if(op[i]==2) cin>>s,p[i]=getid(s);
	}
	bin[0]=1;for(RI i=1;i<=m;++i) bin[i]=bin[i-1]<<1LL;
	for(RI i=1;i<=n;++i)
		if(op[i]==2) {//每一段时间有哪些朋友有要求
			if(op[i-1]==2) a[js]|=bin[p[i]-1];
			else ++js,a[js]=bin[p[i]-1];
		}
	prework(),work();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Katsura_Hinagiku (赞：2)

思路和其他几位差不多，这里就讲一讲最大独立集的求法吧。

原图的最大独立集=补图的最大团

用dfs+剪枝求出

详见代码注释（注:此为图中最大团求法，注释中“最大独立集”与“补图中的最大团”是等价的说法）

```cpp
#include<bits/stdc++.h>
using namespace std;
int vis[45],group[45],n,m,num[45];//vis:当前独立集,group:以求出的独立集中最大的一个,num[i]:从i及i以后的节点中选出的最大独立集的大小
bool mp[45][45];//邻接矩阵
map<string,int>t;//将名字映射为点的编号
string ss;
int tmp[100005],k=0,kk=0,ans=0,cnt=0;//ans:最大独立集大小
bool dfs(int u,int pos)
{
	for(int i=u+1;i<=m;++i)
	{
		if(num[i]+pos<=ans)return 0;//剪枝:num[i]表示i及i以后节点中选出最大独立集大小的话，num为一个非递减的数组,若当前最理想的情况都比ans小的话，直接剪枝
		if(!mp[u][i])//补图中两点间有连边
		{
			bool p=0;
			for(int j=0;j<pos;++j)
			{
				if(mp[vis[j]][i])
				{
					p=1;
					break;
				}
			}
			if(!p)//i点符合条件，可加入当前独立集
			{
				vis[pos]=i;
				if(dfs(i,pos+1))return 1;
			}
		}
	}
	if(pos>ans)//更新ans
	{
		for(int i=0;i<pos;++i)group[i]=vis[i];
		ans=pos;
		return 1;
	}
	return 0;
}
void maxclique()
{
	ans=-1;
	for(int i=m;i>0;--i)
	{
		vis[0]=i;
		dfs(i,1);
		num[i]=ans;
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i)
	{
		int opt;
		scanf("%d",&opt);
		if(i==1&&opt==1)continue;
		if(opt==2)
		{
			cin>>ss;
			if(!t[ss])t[ss]=++kk;
			tmp[++k]=t[ss];
		}
		else
		{
			for(int i=1;i<=k;++i)
			{
				for(int j=1;j<=k;++j)
				{
					if(tmp[i]==tmp[j])continue;
					mp[tmp[i]][tmp[j]]=1;
					mp[tmp[j]][tmp[i]]=1;	
				}
			}
			k=0;
		}
	}
	for(int i=1;i<=k;++i)
	{
		for(int j=1;j<=k;++j)
		{
			if(tmp[i]==tmp[j])continue;
			mp[tmp[i]][tmp[j]]=1;
			mp[tmp[j]][tmp[i]]=1;	
		}
	}
	maxclique();
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Nelofus (赞：1)

真是折折又半半啊。早知道去网上抄个 $2^{n/2}$ 的最大独立集了。

题目即，有若干个颜色集合，你可以从每个集合中取出恰好一个颜色，如果对于某种颜色，剩余的集合中不存在这个颜色，你的权值 $+1$，问最大权值。

对于每种颜色 $x$，如果你想取得其贡献，那么就必须在所有包含 $x$ 的集合里都取 $x$，那就意味着这个集合里的其他元素都不会带来贡献了。也就是，对于每个集合 $S$ 的任意一对 $x,y\in S$ 且 $x\neq y$，都有选了 $x$ 就不能选择 $y$ 的限制。现在你要最大化选择的数的个数，在每对 $x,y$ 之间连一条边，答案就是最大独立集。

考虑折半状压，对每种颜色 $x$ 维护取了 $x$ 之后就不能取的颜色集合，称为冲突集合。两边转移的时候是一样的，枚举一个新加入的颜色，如果当前的颜色和新加入的颜色的冲突集合有交，那么就不能加入。

然后是把两边的答案拼起来，枚举一边的集合，记为 $S$，若另一侧的集合 $T$ 与 $S$ 中颜色冲突集合的并集**无交**，那么两边的答案就可以拼起来。

设 $U$ 为全集，对于每个 $S$，答案是

$$
f_S+\max_{T\subseteq \complement_US}g_T
$$

枚举子集的复杂度是 $3^{n/2}$ 的，显然爆了，但是这个可以 FMT 算一下子集 $\max$，如果不会 FMT 那现场发明一下也不难。

最终时间复杂度 $\mathcal O(n + m2^{m/2})$。

```cpp
// Code by Heratino & Nelofus
// 彗星になれなかった姿を
// 笑い飛ばしてほしかった

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;

//{{{
template<typename Ta, typename Tb>
inline void chkmax(Ta &a, const Tb &b) {if (a < b)	a = b;}
template<typename Ta, typename Tb>
inline void chkmin(Ta &a, const Tb &b) {if (a > b)	a = b;}
//}}}

constexpr int N = 1e5 + 10;
std::unordered_map<std::string, int> mp;
std::pair<int, std::string> qry[N];
int tot;
int n, m;
u64 ban[40];
u64 suf[1 << 20];
u64 f[1 << 20], g[1 << 20];
u64 preg[1 << 20];
bool a1[1 << 20], a2[1 << 20];
int main() {
#ifdef HeratinoNelofus
	freopen("input.txt", "r", stdin);
#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		auto &[op, s] = qry[i];
		std::cin >> op;
		if (op == 2) {
			std::cin >> s;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (qry[i].first == 2) {
			int j = i;
			while (j <= n && qry[j].first == 2)
				j++;
			j--;
			u64 s = 0;
			// s 中的元素两两不能共存
			for (int k = i; k <= j; k++) {
				if (!mp.count(qry[k].second))
					mp[qry[k].second] = tot++;
				s |= (1ull << mp[qry[k].second]);	
			}
			for (int k = i; k <= j; k++) {
				ban[mp[qry[k].second]] |= s;
			}
			i = j;
		}
	}
	// 显然不能共存的元素里没有自己
	for (int i = 0; i < m; i++)
		ban[i] ^= (1ull << i);

	int f1 = m / 2, f2 = m - f1;
	a1[0] = true;
	int ans = 0;
	for (u64 s = 0; s < (1 << f1); s++) {
		if (!a1[s])
			continue;
		chkmax(ans, f[s]);
		// 还没有被加入 & 没有和当前冲突
		for (int i = 0; i < f1; i++) {
			if (s & (1 << i))
				continue;
			if (!(s & ban[i]))
				f[s | (1 << i)] = f[s] + 1, a1[s | (1 << i)] = true;
		}
	}
	a2[0] = true;
	for (u64 s = 0; s < (1 << f2); s++) {
		if (!a2[s])
			continue;
		chkmax(ans, g[s]);
		// 同理，但注意属于第二半的部分在后 f2 位
		for (int i = 0; i < f2; i++) {
			if (s & (1 << i))
				continue;
			if (!((s << f1) & ban[i + f1]))
				g[s | (1 << i)] = g[s] + 1, a2[s | (1 << i)] = true;
		}
	}

	// FMT
	for (int s = 0; s < (1 << f2); s++) {
		preg[s] = g[s];
		for (int i = 0; i < f2; i++) {
			if (s & (1 << i))
				chkmax(preg[s], preg[s ^ (1 << i)]);
		}
	}

	for (u64 s = 0; s < (1 << f1); s++) {
		u64 t = 0;
		// 取出小的那一半的冲突集合，取并
		// 不需要考虑存在子集中某个 t 与当前的 s 冲突的问题，因为关系是双向的，这种情况下 t 必然与 s 冲突从而不会被枚举到。
		for (int i = 0; i < f1; i++)
			if (s & (1 << i))
				t |= ban[i];
		t ^= (1ull << m) - 1;
		t >>= f1;
		chkmax(ans, f[s] + preg[t]);
	}
	std::cout << ans << '\n';
	return 0;
}
```

---

## 作者：1saunoya (赞：1)

最大独立集的 $2^{\frac{n}{2}}$  做法。

先考虑前半部分的最大独立集 $state$ 状态是否冲突。
（如果 $state$ 所代表的集合可选，那么这个 $state$ 合法。）

然后考虑后半部分不冲突的情况下，能选最多几个。

然后我们令后半部分为 $Count_{state}$。

考虑将这个玩意变成高维前缀和。


然后 $Count_S$ 就变成了 $S$ 状态下的子集的 $\max$ 值。

于是随便合并就做完了。

---

## 作者：太阳起晚了呢 (赞：0)

### 解

观察可以发现，在更改一次 ID 之前到上一次更改 ID 之间来过的所有朋友最多只能满足一个。

那么他们之间满意这个事件是互斥的，如果对其建边，那么原题变成一个求最大独立集的问题，可以使用随机化算法模拟退火求解。

细节上，我们没有必要真正建图出来，只需要看看当前这个点和已经选中的点是否冲突，观察到好友数量很少，我们也可以状压解决。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=45;
const int N=1e5+101;
struct node
{
    int v,next;
}e[maxn*maxn*2];
int head[maxn],cnt,top,tot;
bitset<N> b[maxn];
bitset<maxn> f[maxn];
int a[maxn];
int n,m;
int calc()
{
    bitset<maxn> s;s.reset();
    int res=0;
    for(int i=1;i<=m;i++)
    {
        int u=a[i];
        if(!(s & f[u]).count()) s[u]=1,res++;
    }
    return res;
}
int ans;
void SA()
{
    for(double T=5000;T>=1e-14;T*=0.96)
    {
        int x=rand()%m+1,y=rand()%m+1;
        swap(a[x],a[y]);
        int res=calc();
        int delta=res-ans;
        swap(a[x],a[y]);
        if(delta>0)
        {
            ans=res;
            swap(a[x],a[y]);
        }
        else if(exp(-delta/T)*RAND_MAX<=rand()) swap(a[x],a[y]);
    }
}
map<string,int > mp;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int x;scanf("%d",&x);
        if(x==1) top++;
        else
        {
            string s;cin>>s;
            if(mp.find(s)==mp.end()) mp[s]=++tot;
            b[mp[s]][top]=1;
        }
    }
    for(int i=1;i<=top;i++)
        for(int j=1;j<tot;j++)
            for(int k=j+1;k<=tot;k++)
                if(b[j][i] && b[k][i]) f[j][k]=f[k][j]=1;
    for(int i=1;i<=m;i++) a[i]=i;
    while((double)clock()/CLOCKS_PER_SEC<=1.95) SA();
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：Erusel (赞：0)

简单分析可以得到

在两次操作1之间，**我们最多只能满足一个人的要求**

我们把两次操作之间的字符串两两连边

那么这样就构成了一张图

因为在两次操作1之间，我们只能取一个，

所以问题转化成了求在图中最多的点，使得这些点互相不连接

这就是图的**最大独立集**

---

让我们敲锣打鼓

鼓掌欢迎解决方案

。。。

方案是，暴力dfs

因为图的最大独立集是NPC问题，可以理解为不能在多项式时间复杂度内进行求解

树的**最大独立集**和二分图的**最大独立集**可以求解因为它们具有一些性质

dfs也要有技巧啊

我们把互相不连接转化成互相连接

**求解图的最大独立集就是求解在完全图中的补图的最大团（最大完全子图）**

有了这个性质之后，我们就可以进行dfs了

code：

```
#pragma GCC optimize(2) 
#include<bits/stdc++.h>

#define rd(x) x=read()

#define N 55

using namespace std;

int n,m;

vector<int>v;
//vector<int>e[N];
map<string,int>p;
int f[N][N];
int rmatch[N];
int ans;
int t[N];

void addEdge(int u,int v){f[u][v]=1;}

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int dfs(int u,int depth)
{
//	for(int i=0;i<e[u].size();i++)
//	{
//		int v=e[u][i];
//	}
	for(int v=u+1;v<=m;v++)
	{
		if(t[v]+depth<=ans)return 0;//如果上一次的答案+深度还是小于ans剪枝
		if(f[u][v]==0)
		{
			int i;
			for(i=0;i<depth;i++)if(f[v][rmatch[i]])break;//如果有连边
			if(i==depth)//如果全部符合{rmatch[depth]=v;if(dfs(v,depth+1))return 1;}
		}
	}
	if(depth>ans)return (ans=depth)|1;
	return 0;
}

int main()
{
	rd(n),rd(m);int cnt=0;
	while(n--)
	{
		int opt;string s;rd(opt);
		if(opt==1)v.clear();
		else 
		{
			cin>>s;if(!p[s])p[s]=++cnt;
			for(int i=0;i<v.size();i++)addEdge(p[s],v[i]),addEdge(v[i],p[s]);
			v.push_back(p[s]);
		}//连边
	}
	for(int i=m;i>0;i--)t[i+1]=ans,rmatch[0]=i,dfs(i,1);
	cout<<ans<<endl;

    return 0;
}


```

---

