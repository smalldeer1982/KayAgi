# [ONTAK2015] Bajtocja

## 题目描述

给定 $d$ 张无向图，每张图都有 $n$ 个点。一开始，在任何一张图中都没有任何边。接下来有 $m$ 次操作，每次操作会给出 $a, b, k$，意为在第 $k$ 张图中的点 $a$ 和点 $b$ 之间添加一条无向边。你需要在每次操作之后输出有序数对 $(a, b)$ 的个数，使得 $1 \leq a, b \leq n$，且 $a$ 点和 $b$ 点在 $d$ 张图中都连通。

## 说明/提示

对于 $100\%$ 的数据，$1 \leq d \leq 200$，$1 \leq n \leq5 \times 10^3$，$1\leq m \leq 10^6$，$1 \leq a, b \leq n$，$1 \leq k \leq d$。

## 样例 #1

### 输入

```
3 4 10
1 2 1
2 1 2
1 2 3
3 4 1
1 3 2
2 3 3
2 4 2
3 4 3
3 4 2
1 3 1```

### 输出

```
4
4
6
6
6
6
6
8
8
16```

# 题解

## 作者：dbxxx (赞：44)

[欢迎您到我的博客查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/luogu-p8026.html)

题目只考察连通性，不考察图更具体的结构，所以可以用 $d$ 个并查集维护。

两个点 $u$ 和 $v$ 在图 $i$ 上连通，当且仅当图 $i$ 上 $u$ 和 $v$ 的并查集祖先相同。

因此，两个点 $u$ 和 $v$ 在 $d$ 张图上都连通，等价于对于任意 $i$，$u$ 和 $v$ 在第 $i$ 张图的并查集祖先相同。

所以考虑对每个点 $u$ 维护一个长度为 $d$ 的字符串 $s_u$，$s_u(i)$ 表示第 $i$ 张图上 $u$ 的并查集祖先。

于是 $u$ 和 $v$ 在 $d$ 张图上连通等价于 $s_u = s_v$。

我们动态地维护这 $n$ 个字符串的哈希值，对于哈希值相同的 $k$ 个字符串，可以给答案贡献 $k^2$。开桶记录即可。

因为桶的下标是字符串哈希值域量级，桶用 unordered_map（如果会哈希表用哈希表也行）。

现在考虑动态维护 $n$ 个字符串哈希值的复杂度。很明显，每次我们更改的字符串不能太多。

对于一次在第 $k$ 张图连接 $a$ 和 $b$ 的操作，我们会修改 $s_u$ 的第 $k$ 个字符，其中 $u$ 是所有这次连边中在并查集上被更改祖先的点。我们要控制这个点数的量级。

所以不路径压缩，考虑按并查集树的大小启发式合并。这样以来，一个点在第 $d$ 张图中，被更改祖先的次数不会超过 $\log n$ 次（因为被更改一次祖先，它所在的并查集树的大小就会翻倍），每个字符串被修改的数量不超过 $d\log n$，所有字符串被修改的总次数为 $dn\log n$ 量级。

时间复杂度 $\Theta(dn\log n)$，常数略大。

另外这里所有字符串长度都是 $d$，所以可以不用写普通的字符串哈希，直接给每个位置随机一个权值 $w(i)$，记 $S(i)$ 为字符串 $S$ 的第 $i$ 个字符，我们令 $S$ 的哈希值为 $\sum w(i) \times S(i)$ 即可。这样代码会更好写，而且规避了可能的卡哈希问题（本题好像把基数为 131 的自然溢出哈希卡了）。


```cpp
typedef unsigned long long ull;

const int D = 205;
const int N = (int)5e3 + 5;

int rt[D][N];
std :: vector <int> t[D][N]; // t[k][u] 表示第 k 层图中以 u 为根的并查集树
ull ha[N], val[D];
int ans;
std :: unordered_map <ull, int> cnt;

inline void add(ull ha) {
	int x = cnt[ha];
	ans += 2 * x + 1;
	++cnt[ha];
}

inline void del(ull ha) {
	int x = cnt[ha];
	ans -= 2 * x - 1;
	if (--cnt[ha] == 0)
    	cnt.erase(ha); // 本题一个哈希值消失就很难再现，直接 erase 掉能显著减小常数。不 erase 也没什么问题。
}

int main() {
	int d = read(), n = read(), m = read();
	std :: mt19937_64 rng(std :: random_device{}());
	for (int i = 1; i <= d; ++i)
		val[i] = rng();
	for (int i = 1; i <= d; ++i) {
		for (int u = 1; u <= n; ++u) {
			rt[i][u] = u;
			ha[u] += u * val[i];
			t[i][u].push_back(u);
		}
	}

	for (int u = 1; u <= n; ++u)
		add(ha[u]);
	
	while (m--) {
		int u = read(), v = read(), k = read();
		u = rt[k][u]; v = rt[k][v];
		if (u == v) {
			printf("%d\n", ans);
			continue;
		}
		if (t[k][v].size() > t[k][u].size())
			std :: swap(u, v);
		for (int x : t[k][v]) {
			t[k][u].push_back(x);
			rt[k][x] = u;
			del(ha[x]);
			ha[x] += (u - v) * val[k];
			add(ha[x]);
		}
		t[k][v].clear();
		printf("%d\n", ans);
	}
	return 0;
}
```

如果您觉得我的题解写的不错，解决了您的疑惑的话，请给我题解点个赞，谢谢！

---

## 作者：Masterwei (赞：9)

#### 前言

昨天 ACM 的 $1012$，赛时对内没人会，我写了个假算洛谷上跑了 $60$ 分。

#### 思路

考虑用并查集，发现我们要统计在 $d$ 张图上父亲都相同的点对个数即可。具体的，我们可以将每个点在各个图上的父亲 `hash` 保存起来。设一种 `hash` 值的个数为 $cnt$，显然，同种 `hash` 值对答案的贡献为 $cnt^2$。对于每个加边操作，我们维护联通快，然后启发式合并，对于我们修改的每个点，显然它只会被改变一个父亲，这样我们就可以直接改变 `hash` 值，算答案了。

代码不难写。


```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=5005,base=1313131;
int d,n,q;
int f[Maxn][205];
int ha[Maxn],a[205];
vector<int>s[Maxn][205];
unordered_map<int,int>sum;
int ans=0;
inline void change(int Ha,int p){
//	if(p>0)printf("vv:%llu\n",sum[Ha]);
	ans-=sum[Ha]*sum[Ha];
	sum[Ha]+=p;
	ans+=sum[Ha]*sum[Ha];
}
int pw[205];
signed main(){srand(time(0));
	d=read();n=read();q=read();pw[0]=1;
	for(int i=1;i<=d;i++)a[i]=rand();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d;j++)f[i][j]=i,s[i][j].push_back(i),ha[i]=ha[i]+a[j]*i;
		change(ha[i],1);
	}
	while(q--){
		int u=read(),v=read(),w=read();
		if(f[u][w]==f[v][w]){
			printf("%llu\n",ans);
			continue;
		}u=f[u][w];v=f[v][w];
		if(s[u][w].size()<s[v][w].size())swap(u,v);
//		printf("dd:%llu %llu\n",u,v);
		for(int p:s[v][w]){
			change(ha[p],-1);
			ha[p]-=a[w]*(v-u);
			change(ha[p],1);
			f[p][w]=u;
			s[u][w].push_back(p);
//			printf("fa[%llu][%llu]=%llu\n",p,w,f[p][w]);
		}s[v][w].clear();
		printf("%llu\n",ans);
	}
	return 0;
}
```

---

## 作者：larsr (赞：8)

校测搬了这题。看了题解区发现都是哈希？

这道题难点在于合并，而且有多个图。考虑倒着进行这些操作，每次操作就是分裂操作，并且直接分裂即可，不用考虑那么多。

两个点在一个集合的前提是两个点在每个图都连通。

对于分裂，可以使用启发式分裂（~~合并~~）的思想，只处理被分裂的两部分中小的那部分。具体实现可以维护两个值 $id_i$ 和 $siz_i$，分别代表第 $i$ 个点所在的集合，第 $i$ 个集合的大小。然后对于小的部分所在的集合的大小减少并维护答案，然后再新建一些集合，如果两个在小的部分的点原来在同一个集合，那么现在也放在一个集合。

但是最终状态计算起来比较麻烦，可以直接让每个图的联通块之间连边，也就是让它们在同一个集合，然后再分裂即可。总时间复杂度 $O(dn\log n)$。

Code:
```cpp
#include<cstdio>
#include<algorithm>
#include<vector>
#pragma GCC optimize(3, "Ofast", "inline")
#define N 2000010
#define M 10000010
#define p(a,b) ((a - 1) * n + b)
using namespace std;
int d, n, m;
int f[N], siz[N];
int sta[N], top, ans, res[N];
int id[N], tot = 0, si[M], num[M], las[M];
vector<int>ch[N], w[N];
int getfa(int x)
{
	if(f[x] == x)return x;
	return f[x] = getfa(f[x]);
}
void dfs(int now, int c, int k)
{
	w[c].push_back(now - (k - 1) * n);
	for(int &to : ch[now])
		dfs(to, c, k);
}
int main()
{
	scanf("%d%d%d", &d, &n, &m);
	for(int i = 1; i <= n * d; i++)f[i] = i, siz[i] = 1;
	for(int i = 1; i <= m; i++)
	{
		int u, v, k;
		scanf("%d%d%d", &u, &v, &k);
		u = getfa(p(k, u));
		v = getfa(p(k, v));
		if(u == v)continue;
		if(siz[u] < siz[v])swap(u, v);
		f[v] = u;
		siz[u] += siz[v];
		ch[u].push_back(v);
		dfs(v, i, k);
	}
	int tm = m;
	for(int i = 1; i <= d; i++)
	{
		top = 0;
		for(int j = 1; j <= n; j++)
			if(f[p(i, j)] == p(i, j))
			{
				sta[++top] = p(i, j);
			}
		for(int j = 1; j < top; j++)
		{
			tm++;
			int u = sta[j], v = sta[j + 1];
			u = getfa(u);
			v = getfa(v);
			if(siz[u] < siz[v])swap(u, v);
			f[v] = u;
			siz[u] += siz[v];
			ch[u].push_back(v);
			dfs(v, tm, i);
		}
	}
	for(int i = 1; i <= n; i++)id[i] = 1;
	ans = n * n;
	si[1] = n;
	tot = 1;
	for(int i = tm; i; i--)
	{
		res[i] = ans;
		top = 0;
		for(int &to : w[i])
		{
			ans -= si[id[to]] * 2 - 1;
			si[id[to]]--;
			num[id[to]]++;
		}
		for(int &to : w[i])
		{
			if(!num[id[to]])
			{
				id[to] = las[id[to]];
				continue;
			}
			tot++;
			las[id[to]] = tot;
			si[tot] = num[id[to]];
			ans += si[tot] * si[tot];
			num[id[to]] = 0;
			id[to] = tot;
		}
	}
	for(int i = 1; i <= m; i++)printf("%d\n", res[i]);
	return 0;
}
```

---

## 作者：Xy_top (赞：8)

一道好题，本来是做几道启发式合并玩玩，没想到是个哈希。

这一道题需要维护连通性，显然想到使用并查集。

如果两个点在某个图内的父亲相同，显然这两个点就连通了。

但是如果每链接一对点我们就遍历所有点对然后判断父亲，显然爆炸。

于是考虑借鉴一下 CSP 2022 T3 的思路，对于每个点处理一个值 $weight$。

我们再对每张图中的每个点搞一个随机值 $w$，如果 $i$ 的祖先是 $j$，那么给 $weight_i$ 加上 $w_j$ 即可。

这样我们就把每个点的 $weight$ 设成了它在所有的图中祖先节点的权值之和，然后维护有多少对 $weight$ 相等就行了。

这样错误的可能性很小，因为你很难构造出随机的方程，使得 $a_1+a_2+a_3+\cdots +a_d=b_1+b_2+b_3+\cdots b_d$，并且还有一大堆连通性的要求。

但我第一发的模数是 $998244353$，WA 掉一个点，所以模数尽量开大点。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 300005, mod = 998244353;
#define For(i, a, b) for (int i = (a); i <= (b); ++ i)
inline void r (int &x) {
	int s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') w = -1;
		ch = getchar ();
	}
	while (ch >= '0' && ch <= '9') {
		s = s * 10 + ch - 48;
		ch = getchar ();
	}
	x = s * w;
}
int d, n, m;
int w[201][5001], fa[201][5001], sz[201][5001];
int weight[5001];
unordered_map <int, int> b;
vector <int> v[201][5001];
int find (int k, int x) {
	if (fa[k][x] != x) {
		fa[k][x] = find (k, fa[k][x]);
		return fa[k][x];
	} else return x;
}
signed main () {
	srand (time (0) );
	r (d); r (n); r (m);
	For (i, 1, d) {
		For (j ,1, n) {
			w[i][j] = (long long) rand () * (long long) rand () % 129319283324;
			weight[j] += w[i][j];
			v[i][j].push_back (j);
			fa[i][j] = j;
			sz[i][j] = 1;
		}
	}
	For (i, 1, n) b[weight[i] ] ++;
	int ans = n;
	For (i, 1, m) {
		int x, y, k;
		r (x); r (y); r (k);
		int fx = find (k, x), fy = find (k, y);
		if (fx == fy) {
			cout << ans << "\n";
			continue;
		}
		if (sz[k][fx] > sz[k][fy]) swap (fx, fy);
		fa[k][fx] = fy;
		sz[k][fy] += sz[k][fx];
		for (int i : v[k][fx]) {
			ans -= (-- b[weight[i] ]) * 2;
			weight[i] -= w[k][fx];
			weight[i] += w[k][fy];
			ans += b[weight[i] ] * 2;
			b[weight[i] ] ++;
			v[k][fy].push_back (i);
		}
		v[k][fx].clear ();
		cout << ans << "\n";
	}
	return 0;
}
```


---

## 作者：Zhangikun (赞：7)

## 思路：
1. 此题我们需要找在 $d$ 个图中两点都联通的有序点对的数量。若把每个图之间的关系逐个用并查集维护，则问题转换为：需要找满足点对中的点由 $d$ 个并查集中根节点组成的序列一样的有序点对。

什么意思？举个例子：

若 $d=2$，$x$ 在第一个图中所在并查集根节点为 $1$，第二个图中所在并查集根节点为 $2$，则它会组成一个序列：$1,2$（我们把这样组成的序列称为 $v_x$），若点 $y$ 这样计算下序列也是 $1,2$，说明它们在 $
d$ 张图中都连通，$(x,y)$ 和 $(y,x)$ 就是我们要找的有序点对。

2. 假如有 $k$ 种 $v_i$，第 $j$ 种 $v_i$ 有 $a_j$，那么总方案数是：
$$ans=\sum^k_{j=1}{a_j}^2$$

3. 暴力做法：维护 $d$ 个并查集和下标为 $v_i$ 的桶（map），对于每次第 $c$ 张图连边操作，把两点第 $c$ 个并查集合并，把两个并查集中一个并查集里的点 $v_{ic}$（$v_{xy}$ 表示 $v_x$ 的第 $y$ 项）全部改成另一个并查集的根节点（要遍历全树就要存边，故不可使用路径压缩），改完之后改桶，每次查询就算一遍贡献（不必考虑实现，考虑的东西都在后面的优化中可以解决）。

显然，时间是炸了的。

4. 优化点一：并查集合并时，把点少的合并进点多的，这样对于每个集合，自己只需合并 $\log n$ 次，把每个**被合并**的并查集暴力修改。

5. 优化点二：我们可以再减些时间，把 $v_i$ 给它哈希了，这样用桶会快很多。但是变了哈希怎么修改呢（$v_i$ 哈希后用数字 $hash_i$ 表示，哈希的进制数用 $base$ 表示）？

假如要把 $v_{ij}$ 改为 $x$，那么把 $hash_i$ 改成 $hash_i-v_{ij}\times base^{d-j}+x\times base^{d-j}$ 即可。

6. 优化点三：每次连完边再算一遍显然是不现实的，我们可以直接用上一次询问的答案拓展得到：

设 $mp_i$ 表示能使 $hash_j=i$ 成立的 $j$ 的个数。若一个点 $x$ 连边前 $hash_x=\alpha$，连边后 $hash_x=\beta$，那么 $mp_\alpha$ 要减去 $1$，$mp_\beta$ 要加上 $1$。根据完全平方公式：$(a+b)^2=a^2+b^2+2ab,(a-b)^2=a^2+b^2-2ab$，得：$mp_\alpha$ 减去 $1$ 会使得 $ans$ 加上 $1$ 并且减去 $2\times mp_\alpha$，$mp_\beta$ 加上 $1$ 会使得 $ans$ 加上 $1+2\times mp_\beta$。

## 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const int cxk=5e3+5,cln=205,base=13331;
int fa[cln][cxk],sz[cln][cxk],d,n,m,ans;
vector<int>nbr[cln][cxk],v[cxk];
ull has[cxk],pw[cln];
unordered_map<ull,int>mp;
int find(int k,int x)
{
	return fa[k][x]==x?x:find(k,fa[k][x]);
}
void update(int cur,int k,int x)
{
	ans+=1-2*mp[has[cur]];//减去贡献
	mp[has[cur]]--;//桶-1
	has[cur]-=v[cur][k]*pw[d-k];//改hash
	v[cur][k]=x;//改v[cur]
	has[cur]+=v[cur][k]*pw[d-k];//改hash
	ans+=1+2*mp[has[cur]];//加上贡献
	mp[has[cur]]++;//桶+1
}
void dfs(int cur,int k,int x)
{
	update(cur,k,x);//对cur修改
	for(int nxt:nbr[k][cur])
		dfs(nxt,k,x);
}
void unio(int k,int x,int y)
{
	x=find(k,x),y=find(k,y);
	if(sz[k][x]>sz[k][y])//小的合并大的
		swap(x,y);
	dfs(x,k,y);//遍历+修改
	fa[k][x]=y;
	sz[k][y]+=sz[k][x];
	nbr[k][y].push_back(x);//连边
}
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>d>>n>>m;
	pw[0]=1;
	for(int i=1;i<=n;i++)
	{
		v[i].push_back(0);
		for(int j=1;j<=d;j++)
		{
			v[i].push_back(i);
			pw[j]=pw[j-1]*base;//base的j次方=pw[j]
			has[i]=has[i]*base+i;
			fa[j][i]=i;
			sz[j][i]=1;
		}
		mp[has[i]]++;
	}
	ans=n;//初始为n
	for(int x,y,k;m--;)
	{
		cin>>x>>y>>k;
		if(find(k,x)!=find(k,y))//不连通才合并
			unio(k,x,y);//合并
		cout<<ans<<"\n";
	}
}
```

---

## 作者：strlen_s_ (赞：6)

WC 第二课堂的题目选讲讲了这题，感觉非常妙，特写一篇题解总结。

## 分析

题目要求每张图都联通，观察 $m$ 发现很大，所以枚举每张图不显示，于是可以参考 CSP-S T3 的思路，给每张图的每个点随机赋一个点权，然后哈希。

现在考虑如何哈希。

我们发现题目要求我们维护一个连边的操作，自然而然想到用并查集维护，那么每个点有一个指向的父亲。对于这种唯一确定的关系，我们就可以在这个方面设计哈希值。

设 $sum_i$ 表示 $i$ 在每张图中父亲的点权之和。倘若 $a$ 与 $b$ 的 $sum_i$ 相同，那么它们大概率在每张图中都有相同的父亲，所以它们在每张图中联通，对答案有贡献。

然后开一个桶用来跟新答案，然后再写一个启发式合拼。

复杂度 $O(m \log dn)$，但常数巨大，要吸氧。

```
#include<bits/stdc++.h>
#define in inline
#define re register
#define int long long
using namespace std;
in int read(){
	int x=0,f=1;
	char c;
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const int N=5e3+10,D=205,mod=2e9;
int w[D][N];
vector<int>st[D][N];
int f[D][N],sum[N];
int d,n,m;
unordered_map<int,int>mp;
int ans;
int add(int sum,int x,int z){
	sum-=mp[x]*mp[x];
	mp[x]+=z;
	sum+=mp[x]*mp[x];
	return sum;
}
signed main(){
	srand(time(0));
	d=read(),n=read(),m=read();
	for(int i=1;i<=d;i++)for(int j=1;j<=n;j++)w[i][j]=rand()*rand()%mod;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d;j++)
			st[j][i].push_back(i),f[j][i]=i,sum[i]+=w[j][i];
		ans=add(ans,sum[i],1);
	}
	while(m--){
		int x=read(),y=read(),p=read();
		x=f[p][x],y=f[p][y];
		if(x==y){
			printf("%lld\n",ans);
			continue;
		}
		if(st[p][x].size()<st[p][y].size())swap(x,y);
		for(auto i:st[p][y]){
			st[p][f[p][x]].push_back(i);
			ans=add(ans,sum[i],-1);
			sum[i]=sum[i]-w[p][f[p][i]]+w[p][f[p][x]];
			ans=add(ans,sum[i],1);
			f[p][i]=f[p][x];
		}
		st[p][y].clear();
		printf("%lld\n",ans);
	}
	return 0;
}

```

---

## 作者：WeLikeStudying (赞：5)

这个做法真的好妙，发篇题解记录下。
### [题意](https://www.luogu.com.cn/problem/P8026)
给定 $d$ 张 $n$ 个点的图和 $m$ 次加边操作（每次只在某个图上加边），求每次操作后在 $d$ 张图上都连通的点对个数，$d\le 200,n\le 5\times 10^3,m\le 10^6$ 。

### 分析
如果只有一张图，使用并查集，每个节点都有自己的祖先，如果最后第 $i$ 个节点有 $a_i$ 个节点做它的祖先，那么答案就是：
$$\sum_{i=1}^na_i^2$$
如果更改一个节点的祖先，我们可以 $O(1)$ 更新这个数值。

那么连边会改变一些节点的祖先情况，但是，只要我们连两个集合的时候，始终只更新小的那个集合，而不变动大的集合，这就是启发式合并，时间复杂度为 $O(m\log n)$。

那么考虑在 $d$ 张图上一起的情况，还是一样的操作，问题变成了维护一个长度为 $d$ 的数列的相等情况，但是，直接这样做时间复杂度至少是 $\Omega(dm\log n)$（因为更新是 $O(d)$），过不了。

但是虽然数列长度为 $d$，但是更新只是更新一张图，采用哈希算法维护数列的相等关系，关于哈希函数，我这里采用随机赋权重异或的方法，毕竟只是维护数列相等，这样错误率低（因为可以开 long long），更新也是 $O(1)$，时间复杂度 $O((dn+m)\log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define up(a,b,c) for(int a=b;a<=c;++a)
const int D=201,N=5001;
using ll=unsigned long long;
using namespace std;
int d,n,m,k,f[D][N],sz[D][N],ans;
mt19937_64 rnd;
ll h[N],w[D][N];
unordered_map<ll,int>gg;
vector<int>to[D][N];
void add(ll u,int w)
{
	ans+=(2ll*gg[u]+w)*w,gg[u]+=w;
}
void cfa(int u,int v)
{
	add(h[v],-1),h[v]^=w[k][f[k][v]]^w[k][u],
	f[k][v]=u,to[k][u].push_back(v),add(h[v],1);
}
void tog(int u,int v)
{
	u=f[k][u],v=f[k][v];
	if(u==v)return;
	if(sz[k][u]<sz[k][v])swap(u,v);
	sz[k][u]+=sz[k][v];
	for(int z:to[k][v])cfa(u,z);
	to[k][v].clear();
}
int main()
{
	scanf("%d%d%d",&d,&n,&m);
	up(i,1,d)up(j,1,n)
		h[j]^=w[i][j]=rnd(),f[i][j]=j,sz[i][j]=1,to[i][j].push_back(j);
	up(i,1,n)add(h[i],1);
	while(m--)
	{
		int u,v;scanf("%d%d%d",&u,&v,&k),tog(u,v),printf("%d\n",ans);
	}
	return 0;
}
```
### 易错点
唯一易错的就是这题卡常。

先开 O2 优化。

当你大数据还是都不过的时候，你大概率在程序中使用了 `cin` 或 `cout`，你可以采取如下方法。
- 用 `fread`，`fwrite`快读快输：最快速的通过方法，[代码](https://www.luogu.com.cn/paste/5tlvjtbf)。
- 用 `getchar`，`putchar`快读快输：第二快速的通过方法，[代码](https://www.luogu.com.cn/paste/5xrapazd)。
- 坚持用 `cin` 和 `cout`：别用 `endl` 和 `fflush`，在主函数开头加上 `ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);`，第三快速，[代码](https://www.luogu.com.cn/paste/5n3qikoj)。
- 用`scanf` 和 `printf`：也能过，[代码](https://www.luogu.com.cn/paste/95twnf3f)。

---

## 作者：keep_silence (赞：4)

首先，看到题目之后，我们就可以首先意识到，在无向图里只看连通性，就要用并查集，所以转换一下，两个点在每个图都联通，就等于说两个点在每个点的祖先都相同，但是暴力查找一定会超时，仔细分析，我们发现，如果我们把一个点所对应的祖先序列用某个简单的方式无重复的表示出来，然后把相同的值的数量记录一下，不就可以线性计算了吗？

那怎么表示呢？相信大家已经想到答案了，没错，就是哈希。

我们使用哈希来表示不同的序列，由于每个图都不一样，所以不同的图要赋不同的哈希值，用随机数就好了，由于这题过于~~毒瘤~~优秀，会卡常，把值域小的哈希卡出冲突，所以要用大值域的随机数生成器。

但是还有一个问题，怎么快速更新每个点的祖先，并把更改了祖先的点对应的值给修改了呢？并查集不优化肯定不行，也不能路径压缩，因为压缩之后，每次被修改了祖先的点就特别多了，所以要用启发式合并，关于启发式合并具体内容详见[这里](https://oi-wiki.org/ds/dsu/#%E5%90%AF%E5%8F%91%E5%BC%8F%E5%90%88%E5%B9%B6)。

那这道题就做完了，如果还有不懂得，可以看看代码。作为一个好人，提醒一个坑点，虽然应该没有人会踩这个坑，在判断两棵树大小时，要注意判断两个节点祖先是否已经相同，不然会挂在第一个点上，死活调不出来。

```cpp
#include<bits/stdc++.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
namespace IN
{
#define getc() (p1 == p2 && (p2 = (p1 = buf) + inbuf->sgetn(buf, MANPUT), p1 == p2) ? EOF : *p1++)
    const int MANPUT = 1000000;
    char *p1, *p2, buf[MANPUT];
    template <typename T>
    inline void read(T &x)
    {
        static std::streambuf *inbuf = cin.rdbuf();
        x = 0;
        register char c = getc();
        register bool f = 0;
        while (!isdigit(c))
        {
        	if(c == '-')f = 1;
        	c = getc();
		}
            
        x = c ^ 48;
        c = getc();
        while (isdigit(c))
            x = (x << 3) + (x << 1) + (c ^ 48), c = getc();
        if(f)
        	x = -x;
    }
    template <typename T, typename... Args>
    inline void read(T &x, Args &...args)
    {
        read(x);
        read(args...);
    }
}
using namespace IN;
int d,n,m,f[5005][205];
unsigned long long h[5005][205],b[5005];
int an;
unordered_map<unsigned long long,int>mp;
vector<int>a[5005][205];
int find(int x,int k){
	if(x==f[x][k])return x;
	return find(f[x][k],k);
}
int main(){
	std::mt19937_64 rng(std::random_device{}());
	for(int i=1;i<=5000;i++)for(int j=1;j<=200;j++)h[i][j]=rng();
	read(d,n,m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d;j++){
			a[i][j].push_back(i);
			f[i][j]=i;
			b[i]+=h[i][j];
		}
		mp[b[i]]++;
	}
	an=n;
	for(int i=1;i<=m;i++){
		int x,y,k;
		read(x,y,k);
		int fx=find(x,k),fy=find(y,k);
		int l=min(a[fx][k].size(),a[fy][k].size());
		if(a[fx][k].size()>a[fy][k].size()){
			f[fy][k]=fx;
			while(l--){
				int ff=a[fy][k].back();
				a[fx][k].push_back(ff);
				an-=2*mp[b[ff]]-1;
				mp[b[ff]]--;
				b[ff]-=h[fy][k]-h[fx][k];
				an+=2*mp[b[ff]]+1;
				mp[b[ff]]++;
				a[fy][k].pop_back();
			}
		}else if(fx!=fy){
			swap(fx,fy);
			f[fy][k]=fx;
			while(l--){
				int ff=a[fy][k].back();
				a[fx][k].push_back(ff);
				an-=2*mp[b[ff]]-1;
				mp[b[ff]]--;
				b[ff]-=h[fy][k]-h[fx][k];
				an+=2*mp[b[ff]]+1;
				mp[b[ff]]++;
				a[fy][k].pop_back();
			}
		}
		printf("%d\n",an);
	}
}
```

---

## 作者：tanghg (赞：4)

对于本题，发现只要一个点对 $(u,v)$ 在每一个图中都被加入到了同一个集合里即为合法。则直接考虑维护 $d$ 个并查集。所以设 $f_{u,i}$ 表示 $u$ 在第 $i$ 个图中所属的集合，则只要所有的 $f_{u,i},i\in[1,d]$ 全部相等即可。所以我们维护一个哈希表示 $u$ 的所有图的所属集合，之后查询这个哈希有多少个，则就是满足条件，若大小为 $s$ 则可以为最终答案贡献 $s^2$。

之后维护并查集需要更改哈希，如果是路径压缩不好处理，考虑启发式合并即可。

发现边数虽然看起来很大但是能更改的边数只有最多 $nd$ 条，所以如果操作的 $(a,b)$ 在第 $k$ 张图上已经在同一个集合内答案不会改变。

最终时间复杂度 $O(nd\log n)$。
```cpp
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
const ll MAXN=5e3+5;
const ll MAXD=200+5;
ll n,d,q;
ll fa[MAXN][MAXD];
vector<ll>se[MAXN][MAXD];
ll ans;
ll ha[MAXN],base[MAXN];
unordered_map<ll,ll>val;
void change(ll x,ll op){
    ll mx=val[ha[x]];
    ans-=mx*mx;
    val[ha[x]]+=op;
    mx=val[ha[x]];
    ans+=mx*mx;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>d>>n>>q;
    for(int i=1;i<=d;++i){
        base[i]=rand();
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=d;++j){
            fa[i][j]=i;
            se[i][j].push_back(i);
            ha[i]+=base[j]*i;
        }
        change(i,1);
    }
    while(q--){
        ll u,v,k;
        cin>>u>>v>>k;
        u=fa[u][k],v=fa[v][k];
        if(u==v){
            cout<<ans<<endl;
            continue;
        }
        if(se[u][k].size()>se[v][k].size()){
            swap(u,v);
        }
        for(auto x:se[u][k]){
            fa[x][k]=v;
            se[v][k].push_back(x);
            change(x,-1);
            ha[x]-=base[k]*u;
            ha[x]+=base[k]*v;
            change(x,1);
        }
        se[u][k].clear();
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：dengjunhaodejia09 (赞：4)

首先看到这道题，他只有连通这一个要求，那就可以想到并查集，并查集又是怎么判断连通的呢，那就是代表元相同对吧，所以我们把每个点的代表元存下来。若两个点在所有图中的代表元均相同，那么他们就是可以组成满足要求数对。

在并查集中，两个集合并起来，我们要改点的代表元，此时我们启发式合并，改小的那个集合的代表元，这便是达到了我们的要求。但是该如何快速判断呢，我们发现每次修改一个点，只会改他一个图中的代表元，此时便能用字符串哈希的方法快速单点修改哈希值，两个点分别对他们的所有图中的代表元哈希的值相同，我们便能认为他们在所有图中连通，然后用哈希表判断即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
unordered_map<unsigned long long,int> ma;
long long ans=0,f[205][6005],siz[205][6005];
unsigned long long Hash[1919810];
vector<int> g[205][6005];
unsigned long long sum[1919810],base=1299709;
int find(int id,int x){
	if(f[id][x]==x){
		return x;
	}
	return find(id,f[id][x]);
}
void merge(int x,int y,int z){
	x=find(z,x);
	y=find(z,y);
	if(x==y){
		return;
	}
	if(siz[z][x]<siz[z][y]){
		swap(x,y);
	}
	for(int id:g[z][y]){
		ans-=ma[Hash[id]]*2-1;
		ma[Hash[id]]--;
		Hash[id]-=sum[z-1]*f[z][id];
		Hash[id]+=sum[z-1]*x;
		ma[Hash[id]]++;
		ans+=ma[Hash[id]]*2-1;
		f[z][id]=x;
		g[z][x].push_back(id);
	}
	siz[z][x]+=siz[z][y];
	siz[z][y]=0;
	g[z][y].clear();
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int d,n,m;
	cin>>d>>n>>m;
	sum[0]=1;
	for(int i=1;i<=300;i++){
		sum[i]=sum[i-1]*base;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d;j++){
			Hash[i]+=sum[j-1]*i;
			f[j][i]=i;
			siz[j][i]=1;
			g[j][i].push_back(i);
		}
		ma[Hash[i]]++;
		ans++;
	}
	for(int i=1;i<=m;i++){
		int a,b,k;
		cin>>a>>b>>k;
		merge(a,b,k);
		cout<<ans<<"\n";
	}
	return 0;
} 
```

---

## 作者：Leasier (赞：4)

看到连通性相关，考虑对每张图用一个并查集维护连通性，答案即为在 $d$ 张图中连通性信息相同的点的个数的平方和之和。

连通性看上去不好上数据结构维护，考虑对每个点在每张图内的所属集合编号哈希，每次启发式合并修改哈希值即可。

开 `unordered_map` 或手写哈希即可。时间复杂度为 $O(dn \log n + m \log n)$。

代码：
```cpp
#include <unordered_map>
#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int seed = 998244353;
ll ans = 0;
ull power[207], hash_val[5007];
unordered_map<ull, int> mp;

inline void erase(ull x){
	int &y = mp[x];
	ans -= y * 2 - 1;
	if (--y == 0) mp.erase(x);
}

inline void insert(ull x){
	ans += ++mp[x] * 2 - 1;
}

typedef struct {
	int id;
	int root[5007];
	int size[5007];
	vector<int> v[5007];
	
	inline void init(int n){
		for (register int i = 1; i <= n; i++){
			root[i] = i;
			size[i] = 1;
			hash_val[i] += i * power[id];
			v[i].push_back(i);
		}
	}
	
	int get_root(int x){
		if (root[x] == x) return x;
		return root[x] = get_root(root[x]);
	}
	
	inline void merge(int x, int y){
		int x_root = get_root(x), y_root = get_root(y);
		if (x_root != y_root){
			if (size[x_root] > size[y_root]) swap(x_root, y_root);
			root[x_root] = y_root;
			size[y_root] += size[x_root];
			for (register int i = 0; i < size[x_root]; i++){
				int z = v[x_root][i];
				erase(hash_val[z]);
				v[y_root].push_back(z);
				hash_val[z] += power[id] * (y_root - x_root);
				insert(hash_val[z]);
			}
			v[x_root].clear();
		}
	}
} DSU;

DSU dsu[207];

inline void init(int n){
	power[0] = 1;
	for (register int i = 1; i <= n; i++){
		power[i] = power[i - 1] * seed;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

void write(ll n){
	if (n >= 10) write(n / 10);
	putchar(n % 10 + '0');
}

int main(){
	int d = read(), n = read(), m = read();
	init(d);
	for (register int i = 1; i <= d; i++){
		dsu[i].id = i;
		dsu[i].init(n);
	}
	for (register int i = 1; i <= n; i++){
		insert(hash_val[i]);
	}
	for (register int i = 1; i <= m; i++){
		int a = read(), b = read(), k = read();
		dsu[k].merge(a, b);
		write(ans);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Union_Find (赞：1)

首先注意到的是，这题考查的是无向图连通性，考虑并查集。

我们知道，若 $(u,v)$ 满足在每一张图中都联通当且仅当 $\forall k \in [1,d],find(u,k)=find(v,k)$，这里的 $find(u,k)$ 表示在第 $k$ 张图中 $u$ 的并查集的根，和下面的代码一样。

但是这样子的问题就在于我们如何判断呢？考虑到判断每一位都相同，可以 hash。类似于字符串 hash，我们进行加边操作的时候，相当于修改了若干个点的根。我们可以直接修改这些点的祖先，然后 hash 配合 STL 的 map 解决问题（代码中因为 map 常数过大而换成了 unordered_map）。

但是这样子被修改的点就会很多。我们会有两种想法。第一种，使用数据结构维护，但是这题里面因为用的是并查集，我们不好进行推平等操作，所以放弃。

第二种就是启发式合并。因为我们需要涉及的点数最少，所以我们可以启发式合并。

> 并查集的启发式合并虽然与按秩合并类似，但是用的是两种东西。因为并查集需要的是最大深度最小，按秩合并的**秩**一般是最大深度。而这题我们需要点数最少，我们启发式合并用的就应该是子树大小。

这样子单次修改涉及的点数大约只有 $O(\log n)$ 级别。

然后，你写完代码交上去，全 T 了。

为什么呢？我们考虑如何卡掉上述做法。我们可以先用 $O(n)$ 次把一张图中所有点连起来，然后疯狂连一些已经在同一个连通块的点。这样子我们单次修改虽然没有实际意义，但是每次都是 $O(n)$ 的，轻松 T 飞。

我们加上特判，如果连接的两个点在同一个连通块内就直接输出，不修改。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define il inline
#define N 5005
#define D 205
#define calc(x) ((x) * (x))
il ll rd(){
	ll s = 0, w = 1;
	char ch = getchar();
	for (;ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') w = -1;
	for (;ch >= '0' && ch <= '9'; ch = getchar()) s = ((s << 1) + (s << 3) + ch - '0');
	return s * w;
}
ll d = rd(), n = rd(), m = rd(), u, v, k, fa[N][D], sz[N][D], w[D], ans;
ull hsh[N];
unordered_map <ull, ll> tp;
char s[N][D];
vector <ll> e[N][D];
il ll find(ll x, ll k){return fa[x][k] == x ? x : find(fa[x][k], k);}
void ch(ll u, ll k, ll p, ll s){
	ans -= calc(tp[hsh[u]]), tp[hsh[u]]--, ans += calc(tp[hsh[u]]);
	hsh[u] -= w[k] * s, hsh[u] += w[k] * p;
	ans -= calc(tp[hsh[u]]), tp[hsh[u]]++, ans += calc(tp[hsh[u]]);
	for (int v : e[u][k]) ch(v, k, p, s);
}
int main(){
	srand(time(0));
	for (int i = 1; i <= n; i++) for (int j = 1; j <= d; j++) fa[i][j] = i, sz[i][j] = 1;
	for (int i = 1; i <= d; i++) w[i] = rand();
	for (int i = 1; i <= n; i++) for (int j = 1; j <= d; j++) hsh[i] += w[j] * i;
	for (int i = 1; i <= n; i++) tp[hsh[i]]++, ans++;
	while (m--){
		u = rd(), v = rd(), k = rd();
		u = find(u, k), v = find(v, k);
		if (u == v){
			printf ("%lld\n", ans);
			continue;
		}
		if (sz[u][k] > sz[v][k]) swap(u, v);
		ch(u, k, v, u), fa[u][k] = v, sz[v][k] += sz[u][k], e[v][k].push_back(u);
		printf ("%lld\n", ans);
	}
	return 0;
}

```

---

## 作者：Hell0_W0rld (赞：1)

注意到本题只考虑连通性，我们可以维护 $d$ 个并查集。

对于每一个点，将它在 $d$ 张图中 $fa_u$ 的哈希值维护在一张表里。给所有点在所有图中都随机一个权值。则哈希值即为所有图中 $fa_u$ 的权值和。

每次更新的时候，用树上启发式合并的想法，把 $u$ 所在的并查集大小和 $v$ 所在并查集大小较小的那一堆合并到较大的那一堆里面。

每次更新的时候动态修改表格（表格维护哈希值及其出现次数），交叉算一下动态更新答案即可。

时间复杂度 $O(n\log n+nd)$。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define rep(i,l,r) for(register ll i=(l);i<=(r);++i)
#define Rep(i,l,r) for(register ll i=(r);i>=(l);--i)
#define all(x) x.begin(),x.end()
#define Set(x,y) memset(x,y,sizeof(x))
#define Cpy(x,y) memcpy(x,y,sizeof(x))
#define cll const long long
using namespace std;
template<class T>
void death(T s){cout<<s<<endl;exit(0);} 
cll N=5009,D=209;
ull hsh[N],val[D][N];
ll n,m,d,k;
ll sz[D][N],fa[D][N];
vector<ll> nodes[D][N];
ll root(ll x,ll y){
	return fa[x][y]==y?y:fa[x][y]=root(x,fa[x][y]);
}
int main(){
	scanf("%lld%lld%lld",&d,&n,&k), d--;
	ll ans=0;
	random_device rd;
	mt19937 gen(rd());
	rep(iG,1,d+1)rep(u,1,n)val[iG][u]=gen();
	rep(iG,1,d+1)rep(u,1,n){
		fa[iG][u]=u;
		sz[iG][u]=1;
		hsh[u]+=val[iG][u];
		nodes[iG][u].push_back(u);
	}
	unordered_map<ull,ll> cntH;
	rep(u,1,n)cntH[hsh[u]]++;
	rep(i,1,k){
		ll u,v,iG;scanf("%lld%lld%lld",&u,&v,&iG);
		ll ru=root(iG,u);
		ll rv=root(iG,v);
		if(ru==rv){
		    printf("%lld\n",ans*2+n);
			continue;
		}
		if(sz[iG][ru]<sz[iG][rv])swap(ru,rv);
		unordered_map<ull,ll> new_cntH;
		for(auto x:nodes[iG][rv]){
			nodes[iG][ru].push_back(x);
			cntH[hsh[x]]--;
			hsh[x]-=val[iG][rv];
			hsh[x]+=val[iG][ru];
			new_cntH[hsh[x]]++;
		}
		sz[iG][ru]+=sz[iG][rv];
		fa[iG][rv]=ru;
		nodes[iG][rv].clear();
		nodes[iG][rv].shrink_to_fit();
		for(auto info:new_cntH){
			ull h=info.first; ll c=info.second;
			ans+=c*cntH[h];
			cntH[h]+=c;
		}
		printf("%lld\n",ans*2+n);
	}
	return 0;
}
```

---

## 作者：cike_bilibili (赞：1)

题意很简单，就是在 $d$ 张图中动态加边，求所有二元组 $(i,j)$ 中满足 $i,j$ 在每一张图中都联通的二元组数量。

首先看到只有动态加边，考虑用并查集维护连通性，那么两个点在一张图中联通当且仅当它们在对应的并查集中根相同，因此，我们只需要将所有图中的根 hash 下来，用 map 维护就行了。

具体合并时，我们使用启发式合并，那么每个点被合并的次数就在 $\log$ 级别，一边合并一边处理变化量即可。

注意二元组是有序的，答案要乘二。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
inline int read(){
    int ans=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
       if(ch=='-')w=-1;
       ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
       ans=(ans<<1)+(ans<<3)+ch-'0';
       ch=getchar();
    }
    return w*ans;
}
int D,n,m;
int fa[205][5005];
int sz[205][5005];
ull p[5005];
ull base=1145141;
ull h[5005];
int zx[205][5005];
vector<int>e[205][5005];
void init(){
    for(int i=1;i<=D;i++){
        for(int j=1;j<=n;j++){
            fa[i][j]=j;
            zx[i][j]=j;
            sz[i][j]=1;
        }
    }
}
int find(int d,int x){
    if(fa[d][x]!=x)return find(d,fa[d][x]);
    return x;
}
unordered_map<ull,int>t;
ll ans=0;
void change(int d,int x,int y){//将以x为根的并查集修改为y
    t[h[x]]--;
    ans-=t[h[x]];
    h[x]-=p[d]*zx[d][x];
    zx[d][x]=y;
    h[x]+=p[d]*zx[d][x];
    ans+=t[h[x]];
    t[h[x]]++;
    
    for(int i:e[d][x])change(d,i,y);
}
void Union(int d,int x,int y){
    int rt_x=find(d,x),rt_y=find(d,y);
    if(rt_x==rt_y)return;
    if(sz[d][rt_x]>sz[d][rt_y]){
        fa[d][rt_y]=rt_x;
        e[d][rt_x].push_back(rt_y);
        sz[d][rt_x]+=sz[d][rt_y];
        change(d,rt_y,rt_x);
    }else{
        fa[d][rt_x]=rt_y;
        e[d][rt_y].push_back(rt_x);
        sz[d][rt_y]+=sz[d][rt_x];
        change(d,rt_x,rt_y);
    }
}
int main(){
    D=read(),n=read(),m=read();
    p[0]=1;
    for(int i=1;i<=5000;i++)p[i]=p[i-1]*base;
    init();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=D;j++)h[i]+=p[j]*zx[j][i];
        t[h[i]]++;
    }
    
    while(m--){
        int x=read(),y=read(),d=read();
        Union(d,x,y);
        cout<<2*ans+n<<'\n';
    }
}
/*
就是把每张图的并查集祖先当做序列hash起来，联通等价于hash值等
*/
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P8026)

# 思路：

考虑给每个图开一个并查集。设 $f_{i,k}$ 表示第 $i$ 个点在第 $k$ 张图中并查集的根。然后我们对于每个点 $i$，我们将 $d$ 张图中的 $f_i$ 当成一个字符串并算出 ```hash``` 值。如果两个点 $i,j$ 的 ```hash``` 值相同，则他们在每一张图中都连通。

具体操作可以开一个 ```hash``` 表。然后并查集启发式合并。记得要开 ```long long``` 哦。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e3+10;
const int INF=0x3f3f3f3f;
const int MOD=10000007;
const int p=2337;
int d,n,m,ans,pw[N],g[N];
struct node{
    int to,next;
};
struct node1{
	int h[MOD],cnt,size[N*N/5],nxt[N*N/5],val[N*N/5];
	void ins(int x){
		int v=x%MOD;
		for(int i=h[v];i;i=nxt[i]){
			if(val[i]==x){
				size[i]++;
				ans+=2*size[i]-1;
				return;
			}
		}
		val[++cnt]=x;
		nxt[cnt]=h[v];
		size[cnt]=1;
		h[v]=cnt;
		ans++;
	}
	void del(int x){
		int v=x%MOD;
		for(int i=h[v];i;i=nxt[i]){
			if(val[i]==x){
				ans-=2*size[i]-1;
				size[i]--;
				return;
			}
		}
	}
}ha;
struct node2{
	int id,f[N],size[N],h[N],cnt;
	void init(){
        for(int i=1;i<=n;i++){
            f[i]=i;
            size[i]=1;
        }
    }
	int gf(int v){
        return v==f[v]?v:f[v]=gf(f[v]);
    }
	node s[N<<1];
	void add(int i,int j){
        s[++cnt]=(node){j,h[i]};
        h[i]=cnt;
    }
	void dfs(int v,int fa){
		ha.del(g[v]);
		g[v]-=f[v]*pw[id-1];
		f[v]=fa;
		g[v]+=f[v]*pw[id-1];
		ha.ins(g[v]);
		for(int i=h[v];i;i=s[i].next){
			int to=s[i].to;
			dfs(to,fa);
		}
	}
	void Merge(int a,int b){
		a=gf(a);
        b=gf(b);
		if(a==b){
            return;
        }
		if(size[a]>size[b]){
            swap(a,b);
        }
		add(b,a);
		size[b]+=size[a];
		dfs(a,b);
	}
}T[N];
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
signed main(){
	d=read();
    n=read();
    m=read();
	pw[0]=1;
	for(int i=1;i<=d;i++){
        T[i].init();
        pw[i]=pw[i-1]*p;
        T[i].id=i;
    }
	for(int i=1;i<=n;i++){
		for(int j=1;j<=d;j++){
            g[i]=g[i]*p+i;
        }
		ha.ins(g[i]);
	}
	for(int i=1,x,y,z;i<=m;i++){
		x=read();
        y=read();
        z=read();
		T[z].Merge(x,y);
		cout<<ans<<endl;
	}
	return 0;
}
```

完结撒花~

---

## 作者：Populus_euphratica (赞：0)

只用考虑连通性问题，自然而然就想到了并查集，但是还需要考虑如何判断是否在 $d$ 张图里面都联通。

可以考虑对于每个点建立一个哈希，哈希表示在第 $i$ 张图中，这个点的在并查集里面的父亲是谁。

如果两个点在 $d$ 张图中都是联通的，那么这两个点的哈希值就应该相同。

是否相同用一个 $map$ 就可以维护，具体维护可以见代码，还需要考虑的是并查集的合并问题。

路径压缩显然不行，这会导致我们的哈希错误，那么考虑启发式合并，将并查集以启发式合并的方法合并。

这里并不卡哈希，带权和哈希也可通过。

时间复杂度为 $O(nd \log n)$。

```
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int d, n, m;
int ans;
const int Maxn = 210, Maxm = 5010, mod = 998244353;
vector<int> son[Maxn][Maxm];
int fa[Maxn][Maxm];
int Hash[Maxm], sum[Maxm];
unordered_map<int, int> mp;
void add(int x){
	int s = mp[x];
	// cout << x << " " << s << '\n';
	ans += 2 * s + 1;
	mp[x]++;
}
void del(int x){
	int s = mp[x];
	ans -= 2 * s - 1;
	mp[x]--;
}
signed main(){
	mt19937_64 rng(std :: random_device{}());
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> d >> n >> m;
	for(int i = 1 ; i <= d ; i++) Hash[i] = rng() % mod;
	for(int i = 1 ; i <= d ; i++){
		for(int j = 1 ; j <= n ; j++){
			fa[i][j] = j;
			son[i][j].push_back(j);
			sum[j] += j * Hash[i];
		}
	}
	for(int i = 1 ; i <= n ; i++) add(sum[i]);
	while(m--){
		int x, y, k;
		cin >> x >> y >> k;
		x = fa[k][x], y = fa[k][y];
		if(x == y){
			cout << ans << '\n';
			continue;
		}
		if(son[k][x].size() < son[k][y].size()) swap(x, y);
		for(auto to : son[k][y]){
			del(sum[to]);
			sum[to] += (x - y) * Hash[k];
			son[k][x].push_back(to);
			fa[k][to] = x;
			add(sum[to]);
		}
		son[k][y].clear();
		cout << ans << '\n';
	}
	return 0;
}
```

---

## 作者：XiangyuHu (赞：0)

考虑使用 $d$ 个并查集维护点之间的联通关系

那么两个点在所有图都联通的充要条件即为在所有并查集中的根节点都相等

把每一个点的根节点数组哈希下来加进 `map` 里面动态维护答案即可

具体实现可以使用启发式合并维护点的根节点变化，详见代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int bs = 5003;
int fa[210][5050];
vector<int> p[210][5050];
ull hs[5050];
ull pw[210];
unordered_map<ull, int> cnt;
int ans = 0;
int getfa(int k, int x) {
    if (fa[k][x] == x) return x;
    return fa[k][x] = getfa(k, fa[k][x]);
}
void merge(int k, int x, int y) {
    x = getfa(k, x), y = getfa(k, y);
    if (x == y) return;
    if (p[k][x].size() < p[k][y].size()) swap(x, y); // 启发式合并
    // printf("%d %d %d\n", k, x, y);
    for (int h : p[k][y]) {
        p[k][x].push_back(h); 
        fa[k][h] = x;
        ans -= (--cnt[hs[h]]) * 2; // 删掉之前的点对
        hs[h] += (x - y) * pw[k - 1];
        ans += (cnt[hs[h]]++) * 2; // 加进新的点对
    }
}
int n, m, d;
int main() {
    scanf("%d%d%d", &d, &n, &m);
    ull sm = 0;
    pw[0] = 1;
    ans = n;
    for (int i = d; i >= 1; i--) {
        sm = sm * bs + 1;
        pw[d - i + 1] = pw[d - i] * bs;
    }
    for (int i = 1; i <= n; i++) {
        hs[i] = sm * i;
        cnt[hs[i]]++;
        for (int k = 1; k <= d; k++) {
            fa[k][i] = i;
            p[k][i].push_back(i);
        }
    }
    for (int i = 1; i <= m; i++) {
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        merge(k, a, b);
        // for (auto x : cnt) if (x.second) printf("%llu %d\n", x.first, x.second);
        printf("%d\n", ans);
    }
}
```

---

## 作者：Jerrywang09 (赞：0)

考虑给每层的每个连通块都赋予随机权值 $key$。记 $val(i)$ 表示点 $i$ 在每一层中所在连通块的权值 $key$ 的异或和。

转化一下条件：如果 $u,v$ 在每一层中都连通，说明每一层中 $u,v$ 都处在相同的连通块内。

有了随机权值这一工具，上述条件可以进一步转化为 $val(u)=val(v)$。可以使用系统自带的哈希表维护 $val$。

如果需要合并两个集合，则启发式合并，维护并查集的同时维护以 $u$ 为首的连通块内具体有哪些点，用 vector 存储。并入的结点更换了连通块，需要同时修改 $val$ 和哈希表。

如何统计答案呢？考虑在哈希表插入或删除时同步维护，注意点对是有序的。

```cpp
// Title:  Bajtocja
// Source: BZOJ4298
// Author: Jerrywang
#include <bits/stdc++.h>
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=5005, M=205;
using namespace std;

mt19937 rnd(time(0));
int d, n, T, ans; ll val[N];
unordered_map<ll, int> mp;

struct layer
{
    int f[N]; ll key[N];
    vector<int> a[N];
    void init()
    {
        rep(i, 1, n) f[i]=i, key[i]=rnd()*rnd(), a[i].push_back(i);
    }
    int fa(int u)
    {
        if(u==f[u]) return u;
        return f[u]=fa(f[u]);
    }
    void merge(int u, int v)
    {
        u=fa(u), v=fa(v);
        if(u==v) return;
        if(a[u].size()<a[v].size()) swap(u, v);
        f[v]=u;
        for(int x:a[v])
        {
            a[u].push_back(x);
            ll &t=val[x];
            ans-=(--mp[t])*2;
            val[x]=val[x]^key[x]^key[u];
            ans+=(mp[t]++)*2;
            key[x]=key[u];
        }
        a[v].clear();
    }
} a[M];

int main()
{
    scanf("%d%d%d", &d, &n, &T); ans=n;
    rep(i, 1, d) a[i].init();
    rep(i, 1, n)
    {
        rep(j, 1, d) val[i]^=a[j].key[i];
        mp[val[i]]++;
    }
    while(T--)
    {
        int u, v, k; scanf("%d%d%d", &u, &v, &k);
        a[k].merge(u, v);
        printf("%d\n", ans);
    }

    return 0;
}
```

---

## 作者：hlsnqdmz (赞：0)

一道将启发式合并和哈希结合的好题，不过由于自己写的太差，提交了十多发才过（手写哈希表真的比 `unordered_map` 快好多）。

看到题目，我们发现，如果 $a,b$ 两点要成为点对，那么它们在所有图上都连通，而图的连通性问题我们能想到用并查集来解决。那么这个描述就可以改进为两点的并查集祖先相同。我们知道，如果每次修改暴力枚举所有点，寻找它们每个图并查集祖先都相同那肯定会 T 飞，但是每次修改的答案可以基于上一次的答案做修改——对于每个修改的点，减去原来和它是点对的点的个数乘二（因为是点对），加上现在和它是点对的点的个数乘二就是答案。现在的问题是如何快速找到所有和它是点对的点，我们想到 hash，这里有个巧妙的做法，我们给每个图每个点都随机一个点权，每个点在每个图的所有祖先的点权加到一起，就是它判断与其他点是否是点对的条件。但是这个方法还是有些坑的，`rand()` 生成的随机数质量不足，总是会有几个点 WA 掉，所以这里我们使用 `mt19937` 生成质量高的随机数（甚至比 `rand()` 还快），具体的使用方法可以看[ OI Wiki ](https://oi-wiki.org/misc/random/#mt19937)，这里不多讲述（~~其实是不会~~）。当然坑点不止一个，取模的数最好不要太小，范围比 `int` 大也是可以的；一次随机可能不够保险，你可以随机两次再相乘。  
我们把一个点在每个图的祖先（最开始是它自己）的点权加在一起，存在 `unordered_map` 或者哈希表里（前者写得少，后者跑得快），使其初始值为 1,（因为图最开始都没连通），答案初值设为点数，然后就可以开始执行操作。

将读入的两个点（$x,y$）的父亲作比较，这里不用调用函数而是直接用父亲的原因是之后点的修改都会让它的父亲直接指向它并查集深度最小的祖先，相当于已经路径压缩好了，它的父亲就是并查集的祖先。相等直接输出答案跳到下一个，否则就让 $y$ 的点集（这里用 `vector` 存储）的所有点修改贡献之后将父亲改为 $x$ 的父亲（其实这里的“父亲”指的是并查集的数组 `fa`，它的值就是这个点的“祖先”），然后加入 $x$ 的点集，最后清空 $y$ 的点集防止 MLE。  
我们先不提如何修改贡献，而是观察一下，这个方法是会超时的，原因是你可能将一个很大的点集全部修改了而不去修改较小的点集。这个问题我们可以使用启发式合并来解决，这样可以保证时间复杂度是 $O(n\log{n})$ 的。原因是你这个点每次被枚举后所在的点集至少会增大一倍，点集大小：$1\to 2\to 4\to 8\to 16……$，所以是 $\log{n}$ 的。所以我们在修改点集之前让被修改的点集大小更小就可以了。

最后谈一谈怎么修改贡献，其实这个很简单。原来的哈希值对应的点的个数先减一，再让答案减去其的两倍，修改哈希值后，让答案加上新的哈希值对应的点的个数的两倍，在让个数加一就完成了。

这里的数组除了哈希值和 `unordered_map` 或者哈希标的下标，其他都可以开 `int`，不然可能爆空间。

最后给出代码：  
使用了 `unordered_map` 的代码：
```
//Just Sayori
#pragma GCC diagnostic ignored "-Wnarrowing"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
#include <vector>
#include <unordered_map>
#define ll long long
#define ull unsigned long long
#define rnt register int
#define gr getchar
#define pr putchar
#define N 500005
#define M 1000000007
using namespace std;
inline ll read()
{
	ll x = 0, f = 1;
	char ch = gr();
	while (ch < '0' || ch > '9') ch == '-' ? f = -1, ch = gr() : ch = gr();
	while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = gr();
	return x * f;
}
inline void write(ll x)
{
	static int top = 0, sta[39];
	if (x < 0) pr('-'), x = -x;
	do sta[++top] = x % 10, x /= 10;
	while (x);
	while (top) pr(sta[top--] ^ 48);
}
int d, n, m, a, b, k, ans;
ll g[5005];
int w[5005][205], fa[5005][205], sz[5005][205];
vector<int> v[5005][205];
unordered_map<ll, int> mp;
int main()
{
	mt19937 myrand(time(0));
	d = read(), n = read(), m = read(), ans = n;
	for (rnt i = 1; i <= n; mp[g[i]]++, i++)
		for (rnt j = 1; j <= d; j++)
		{
			w[i][j] = (ll)myrand() * (ll) myrand() % 1145141919810;
			fa[i][j] = i;
			sz[i][j] = 1;
			v[i][j].push_back(i);
			g[i] += w[i][j];
		}
	for (rnt i = 1; i <= m; i++)
	{
		a = read(), b = read(), k = read();
		int fx = fa[a][k], fy = fa[b][k];
		if (fx == fy)
		{
			write(ans), pr(10);
			continue;
		}
		if (sz[fx][k] < sz[fy][k]) swap(fx, fy);
		fa[fy][k] = fx;
		sz[fx][k] += sz[fy][k];
		for (rnt j : v[fy][k])
		{
			ans -= (--mp[g[j]]) * 2;
			g[j] -= w[fy][k];
			g[j] += w[fx][k];
			fa[j][k] = fx;
			ans += (mp[g[j]]++) * 2;
			v[fx][k].push_back(j);
		}
		v[fy][k].clear();
		write(ans), pr(10);
	}
	return 0;
}
```
使用了丑陋写法的哈希表的代码：
```
//Just Sayori
#pragma GCC diagnostic ignored "-Wnarrowing"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <random>
#include <vector>
#include <unordered_map>
#define ll long long
#define ull unsigned long long
#define rnt register int
#define gr getchar
#define pr putchar
#define N 500005
#define M 10000005
using namespace std;
inline ll read()
{
	ll x = 0, f = 1;
	char ch = gr();
	while (ch < '0' || ch > '9') ch == '-' ? f = -1, ch = gr() : ch = gr();
	while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + (ch ^ 48), ch = gr();
	return x * f;
}
inline void write(ll x)
{
	static int top = 0, sta[39];
	if (x < 0) pr('-'), x = -x;
	do sta[++top] = x % 10, x /= 10;
	while (x);
	while (top) pr(sta[top--] ^ 48);
}
struct edge
{
	ll x;
	int y, next;
} e[M << 1];
int head[M], cnt;
int d, n, m, a, b, k, ans;
ll g[5005];
int w[5005][205], fa[5005][205], sz[5005][205];
vector<int> v[5005][205];
inline ll get_map(ll x)
{
	if (x < 0) x = -x;//原来的负数太大，这里随便写了一句就 A 了，所以没有修改。
	return (x + M) % M;
}
int query(ll x)
{
	for (rnt i = head[get_map(x)]; i; i = e[i].next)
		if (e[i].x == x)
			return e[i].y;
	return 0;
}
void modify(ll x, int w)
{
	for (rnt i = head[get_map(x)]; i; i = e[i].next)
		if (e[i].x == x)
			return e[i].y += w, void();
	e[++cnt] = {x, w, head[get_map(x)]}, head[get_map(x)] = cnt;
}
int main()
{
	mt19937 myrand(time(0));
	d = read(), n = read(), m = read(), ans = n;
	for (rnt i = 1; i <= n; modify(g[i], 1), i++)
		for (rnt j = 1; j <= d; j++)
		{
			w[i][j] = (ull)myrand() * (ull) myrand() % 1145141919810;
			fa[i][j] = i;
			sz[i][j] = 1;
			v[i][j].push_back(i);
			g[i] += w[i][j];
		}
	for (rnt i = 1; i <= m; i++)
	{
		a = read(), b = read(), k = read();
		int fx = fa[a][k], fy = fa[b][k];
		if (fx == fy)
		{
			write(ans), pr(10);
			continue;
		}
		if (sz[fx][k] < sz[fy][k]) swap(fx, fy);
		fa[fy][k] = fx;
		sz[fx][k] += sz[fy][k];
		for (rnt j : v[fy][k])
		{
			modify(g[j], -1);
			ans -= query(g[j]) * 2;
			g[j] -= w[fy][k];
			g[j] += w[fx][k];
			fa[j][k] = fx;
			ans += query(g[j]) * 2;
			modify(g[j], 1);
			v[fx][k].push_back(j);
		} 
		v[fy][k].clear();
		write(ans), pr(10);
	}
	return 0;
}
```

---

