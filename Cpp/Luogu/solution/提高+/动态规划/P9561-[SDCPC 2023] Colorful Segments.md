# [SDCPC 2023] Colorful Segments

## 题目描述

考虑数轴上的 $n$ 条线段，其中第 $i$ 条线段的左端点为 $l_i$，右端点为 $r_i$。每一条线段都被涂上了颜色，其中第 $i$ 条线段的颜色为 $c_i$（$0 \le c_i \le 1$）。颜色共有两种，$c_i = 0$ 代表一条红色的线段，而 $c_i = 1$ 代表一条蓝色的线段。

您需要选择若干条线段（可以不选择任何线段）。如果您选择的任意两条线段有重合，则这两条线段的颜色必须相同。

求选择线段的不同方案数。

称第 $i$ 条线段和第 $j$ 条线段有重合，若存在一个实数 $x$ 同时满足 $l_i \le x \le r_i$ 且 $l_j \le x \le r_j$。

称两种选择线段的方案是不同的，若存在一个整数 $1 \le k \le n$，满足第 $k$ 条线段在其中一个方案中被选择，而在另一个方案中没有被选择。

## 样例 #1

### 输入

```
2
3
1 5 0
3 6 1
4 7 0
3
1 5 0
7 9 1
3 6 0```

### 输出

```
5
8```

# 题解

## 作者：czy0323 (赞：9)

赛时一眼秒（假）了，然后花了 5h 写假做法。

思路 5min，代码 2h，调试 2h，赛后才发现假了qwq

赛时唯一贡献是为队友贡献了 20min 的罚时。

## $\textbf{Solution}$

先讲一下我赛时的假思路（因为这对正解很有启发作用）：

统计方案数，考虑 dp。$n \le 10^5$，故 dp 应该是一维的。

令 $f(i)$ 表示选到第 $i$ 条线段为止，第 $i$ 条必选，后面的线段都不选的总方案数。注意到线段的顺序对答案没有影响，我们考虑对所有线段按右端点排序。

很自然的转移方程：

$$ f(0) = 1 $$

$$f(i) = f(0) + \sum\limits_{1\leq j\lt i,c_i=c_j}f(j) + \sum\limits_{1\leq j\lt i,c_i\neq c_j,r_j\lt l_i}f(j)$$

其中 $c$ 表示颜色数组。

下图是反例（有点丑）：

![](https://cdn.luogu.com.cn/upload/image_hosting/3htzi85j.png)

按照我们有的转移方程，$f(3) = 3$，而由定义可知 $f(3)= 2$。

为什么会错呢？因为 $f(3)$ 通过 $f(2)$ 转移过来，$f(2)$ 从 $f(1)$ 转移过来，但其实 $1$ 号线段和 $3$ 号线段不能相容，也就是出现了dp不能转移的情况，所以这种做法就错了。

那怎么做才对呢？

既然由同色线段转移会出现错误，那只由异色线段转移不就行了？

对于 $(i, j) \text{ s.t. }i \lt j , c_i \neq c_j$，我们定义 $cnt(i, j)$：

$$ cnt(i, j) = \sum\limits_{i\lt k\lt j,c_j=c_k}[r_i\lt l_k]$$

那么转移方程就是：

$$f(i)=\sum\limits_{1\leq j\lt i,c_i\neq c_j}f(j)\times\sum_{k=0}^{cnt(i,j)}\binom{cnt(i,j)}{k}$$

二项式定理化一下：

$$f(i)=\sum\limits_{1\leq j\lt i,c_i\neq c_j}f(j)\times 2^{cnt(i,j)}$$

时间复杂度 $\mathcal O(n ^ 2) $。

考虑如何优化。

对于一条线段 $i$，由于两种颜色等价，不妨设 $c_i = 0$ 的。

我们需要找到 $\lt l_i$ 的最大 $r_j (\text{s.t. } c_j = 1 )$，即下标 $\le j(\text{s.t. } c_j = 1 )$ 的 $f_j$ 都对 $f_i$ 有贡献。

如果我知道 $\sum\limits_{k\le j, c_k  = 1}f(k)\times 2^{cnt(k, i)}$ 就好了。

令 $g_j= \sum\limits_{k\le j, c_k  = 1}f(k)\times 2^{cnt(k, i)}$。那 $f_i$ 可以直接由 $g_j$ 转移而来。

那么怎么维护 $g$ 呢？对于当前的 $i, \forall j \text{ s.t. }r_j \lt l_i$ 的 $g_j$ 其实都要被 $\times 2$。由于线段是有序（以右端点为关键字）的，故所有需要更新的 $g_j$ 都在一个连续的区间内。也就是对 $g$ 序列区间乘 $2$。

考虑用一个数据结构维护 $g$。要求：快速查询前缀和、区间乘 $2$ 和单点修改。

显然线段树。由于是单点修改，可以单 Tag。

## $\textbf{AC Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5, mod = 998244353;
int n, pow2[N], f[N];
int tr[2][4 * N], mark[2][4 * N];	//0红 1蓝 
int ql, qr, d;

struct seg{
	int l, r;
	bool operator <(const seg &b) const{
		return r < b.r;
	}
	bool operator <(const int &d) const{
		return r < d;
	}
};
vector<seg> red, blue;

inline int get(int d, int op){
	if( !op )
		return lower_bound(red.begin(), red.end(), d) - red.begin();
	return lower_bound(blue.begin(), blue.end(), d) - blue.begin();
}

inline int MOD(int a, int b){
	if( a + b >= mod )
		return a + b - mod;
	return a + b;
}

inline void pushdown(int l, int r, int p, int op){
	if( l != r && mark[op][p] ){
		tr[op][p << 1] = tr[op][p << 1] * pow2[mark[op][p]] % mod;
		tr[op][p << 1 | 1] = tr[op][p << 1 | 1] * pow2[mark[op][p]] % mod;
		mark[op][p << 1] += mark[op][p];
		mark[op][p << 1 | 1] += mark[op][p];
		mark[op][p] = 0;
	}
	return;
}

inline void modify(int l, int r, int p, int op, int ope){		//ope0是单点加，ope1是区间乘 
	if( ql <= l && r <= qr ){
		if( !ope )
			tr[op][p] = d;
		else{
			tr[op][p] = MOD(tr[op][p], tr[op][p]);
			mark[op][p]++;
		}
		return;
	}
	pushdown(l, r, p, op);
	int mid = (l + r) >> 1;
	if( ql <= mid )
		modify(l, mid, p << 1, op, ope);
	if( mid < qr )
		modify(mid + 1, r, p << 1 | 1, op, ope);
	tr[op][p] = MOD(tr[op][p << 1], tr[op][p << 1 | 1]);
	return;
}

inline int query(int l, int r, int p, int op){
	if( ql <= l && r <= qr )
		return tr[op][p];
	pushdown(l, r, p, op);
	int mid = (l + r) >> 1, ans = 0;
	if( ql <= mid )
		ans = MOD(ans, query(l, mid, p << 1, op));
	if( mid < qr )
		ans = MOD(ans, query(mid + 1, r, p << 1 | 1, op));
	tr[op][p] = MOD(tr[op][p << 1], tr[op][p << 1 | 1]);
	return ans;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	pow2[0] = 1;
	for(int i = 1; i < N; i++){
		pow2[i] = pow2[i - 1] + pow2[i - 1];
		if( pow2[i] >= mod )	pow2[i] -= mod;
	}
	int T;
	cin >> T;
	while( T-- ){
		for(int i = 1; i <= n; i++)
			f[i] = 0;
		for(int i = 1; i <= 4 * n; i++)
			tr[0][i] = tr[1][i] = mark[0][i] = mark[1][i] = 0;
		red.clear();	blue.clear();
		
		cin >> n;
		for(int i = 1; i <= n; i++){
			seg now;
			int c;
			cin >> now.l >> now.r >> c;
			if( !c )	red.push_back(now);
			else	blue.push_back(now);
		}
		sort(red.begin(), red.end());
		sort(blue.begin(), blue.end());
		
		d = f[0] = 1;
		ql = 0, qr = 0;
		modify(0, red.size(), 1, 0, 0);
		modify(0, blue.size(), 1, 1, 0);
		int p1 = 0, p2 = 0, cnt = 0;
		while( p1 < red.size() || p2 < blue.size() ){
			++cnt;
			if( p1 !=red.size() && (p2 == blue.size() || red[p1].r < blue[p2].r) ){		//选红色线段
				ql = 0, qr = get(red[p1].l, 1);
				d = f[cnt] = query(0, blue.size(), 1, 1);
				modify(0, blue.size(), 1, 1, 1);
				ql = qr = p1 + 1;
				modify(0, red.size(), 1, 0, 0);
				p1++;
			}
			else{
				ql = 0, qr = get(blue[p2].l, 0);
				d = f[cnt] = query(0, red.size(), 1, 0);
				modify(0, red.size(), 1, 0, 1);
				ql = qr = p2 + 1;
				modify(0, blue.size(), 1, 1, 0);
				p2++;
			}
		}
		
		int ans = 0;
		for(int i = 0; i <= n; i++)
			ans = MOD(ans, f[i]); 
		cout << ans << "\n";
	}
	return 0;
}
```

LaTeX：@Matrix_mlt

---

## 作者：ykzzldz (赞：4)

上课讲到这题，来写个题解。

所有线段先按照右端点排序，这样我们就只需要考虑左端点的位置即可。考虑暴力 dp，设 $f_i$ 表示选到第 $i$ 条线段的方案数。枚举最后一条不同颜色的线段 $j$，那么在 $(j,i]$ 中的线段是可以任意选或不选的。具体地，令 $num(j,i)=\sum_{k=j+1}^i[c_k=c_i\land r_j<l_k]$。那么转移方程即为 $f_i=\sum_{j=1}^{i-1}[c_j\ne c_i]\times f_j\times 2^{num(j,i)}$。

对于一种颜色，由于我们只会从另外一种颜色转移而来，所以可以分开考虑。这里，我们使用线段树来优化转移。每次转移完成后，我们只需要对于线段树中单点加，区间乘 $2$ 即可，代码比较简单，就不放了。

---

## 作者：critnos (赞：2)

非常难写的 dp 题。

容易想到这个思路：离散化，$dp_{i,0/1}$ 表示对于前 $i$ 个位置最后一个选的是红/蓝色。为了不重不漏地转移，枚举的是最后一段连续的同色段所包含的区间。即在 $i$ 处枚举区间 $[l,i]$，$l$ 和 $i$ 处必须有线段覆盖，且所有线段都在 $[l,i]$ 区间中。

考虑 $i$ 处的转移（不妨考虑在转移 $dp_{i,0}$），即考虑所有 $r=i$ 的线段。钦定某条线段是选的线段中左端点最小的，设其为 $l$。那么对于 $[l,i]$ 这个区间，已经满足 $l,i$ 被覆盖了。这里的贡献就是 $dp_{l-1,1}\times 2^{cnt-1}$（钦定选择了这条线段），$cnt$ 是 $[l,i]$ 区间中线段的数量。对于 $l_0<l$ 的区间 $[l_0,i]$，左右端点处的选择是无关的，贡献是 $dp_{l_0-1,1}\times 2^{cnt}\times (2^{cnt_0}-1)\times (2^{cnt_1}-1)$。$cnt$ 是 $[l_0+1,i-1]$ 区间中线段的数量，$cnt_0$ 是右端点为 $i$ 可选可不选的线段数量，$cnt_1$ 是左端点位于 $l$ 的线段数量。

发现上面的 $2^{cnt_1}-1$ 不是很能维护，所以拆开维护即可，这样共要用三个线段树。

最后十五分钟过了两个题，总算还是切了十二个。这是两者之一。

```cpp
#include<bits/stdc++.h>
#define Yukinoshita namespace
#define Yukino std
using Yukinoshita Yukino;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') w=ch=='-'?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
const int mxn=5e5+5;
const int mod=998244353;
int qpow(int a,int p)
{
	int mul=1;
	for(;p;p>>=1)
	{
		if(p&1) mul=1ll*mul*a%mod;
		a=1ll*a*a%mod;
	}
	return mul;
}
inline void getmod(int &x)
{
	x-=(x>=mod)*mod;
}
int h[mxn];
int pw2[mxn];
struct segment_tree
{
	struct seg
	{
		int l,r,tag,sum;
	}t[mxn*4];
	#define ls w<<1
	#define rs ls|1
	void pushup(int w)
	{
		getmod(t[w].sum=t[ls].sum+t[rs].sum);
	}
	void ad(int w,int v)
	{
		t[w].tag=1ll*t[w].tag*v%mod;
		t[w].sum=1ll*t[w].sum*v%mod;
	}
	void pushdown(int w)
	{
		if(t[w].tag!=1)
			ad(ls,t[w].tag),ad(rs,t[w].tag),t[w].tag=1;
	}
	void build(int w,int l,int r)
	{
		t[w].l=l,t[w].r=r,t[w].sum=0,t[w].tag=1;
		if(l<r)
		{
			int mid=l+r>>1;
			build(ls,l,mid);
			build(rs,mid+1,r);
		}
	}
	void add(int w,int l,int r,int v)
	{
		if(l>r) return;
		if(t[w].l>=l&&t[w].r<=r)
		{
			ad(w,v);
			return;
		}
		pushdown(w);
		if(t[ls].r>=l) add(ls,l,r,v);
		if(t[rs].l<=r) add(rs,l,r,v);
		pushup(w);
	}
	void add(int w,int x,int v)
	{
		if(t[w].l>=x&&t[w].r<=x)
		{
			t[w].sum=v;
			return;
		}
		pushdown(w);
		if(t[ls].r>=x) add(ls,x,v);
		if(t[rs].l<=x) add(rs,x,v);
		pushup(w);
	}
	int ask(int w,int l,int r)
	{
		if(l>r) return 0;
		if(t[w].l>=l&&t[w].r<=r) return t[w].sum;
		int s=0;
		pushdown(w);
		if(t[ls].r>=l) s=ask(ls,l,r);
		if(t[rs].l<=r) getmod(s+=ask(rs,l,r));
		return s;
	}
}T[2],T2[2],T3[2];
/*
1
7
1 9 1
3 10 1
0 8 0
6 7 0
8 9 1
3 4 1
6 7 1

38
*/
int sum[mxn][2],sum2[mxn];
int dp[mxn][2];
vector<int> pos[mxn][2];
struct node
{
	int l,r,c;
}a[mxn];
int main()
{
//	system("fc out out2");
//	freopen("in","r",stdin);
//	freopen("out2","w",stdout);
	int Ti=read();
	while(Ti--)
	{
		int n=read(),i,j,k,cnt=0;
		pw2[0]=1;
		for(i=1;i<=n;i++)
			getmod(pw2[i]=pw2[i-1]*2);
		for(i=1;i<=n;i++)
			a[i].l=read(),a[i].r=read(),a[i].c=read(),h[++cnt]=a[i].l,h[++cnt]=a[i].r;
		sort(h+1,h+1+cnt);
		cnt=unique(h+1,h+1+cnt)-h-1;
		for(i=1;i<=n;i++)
			a[i].l=lower_bound(h+1,h+1+cnt,a[i].l)-h,
			a[i].r=lower_bound(h+1,h+1+cnt,a[i].r)-h;	
		for(i=1;i<=cnt;i++)
			pos[i][0].clear(),pos[i][1].clear(),sum2[i]=0;
		for(i=1;i<=n;i++)
			pos[a[i].r][a[i].c].push_back(a[i].l);
		dp[0][0]=dp[0][1]=1;
		T[0].build(1,0,cnt+1);
		T[1].build(1,0,cnt+1);
		T2[0].build(1,0,cnt+1);
		T2[1].build(1,0,cnt+1);
		T3[0].build(1,0,cnt+1);
		T3[1].build(1,0,cnt+1);
		T[0].add(1,1,1);
		T[1].add(1,1,1);
		T2[0].add(1,1,1);
		T2[1].add(1,1,1);
		T3[0].add(1,1,1);
		T3[1].add(1,1,1);
		for(i=1;i<=cnt;i++)
		{
			for(j=0;j<2;j++)
			{
				dp[i][j]=dp[i-1][j];
				sort(pos[i][j].begin(),pos[i][j].end());
				for(k=0;k<pos[i][j].size();k++)
				{
					int w=pos[i][j][k];
					
					dp[i][j]=(dp[i][j]+1ll*T3[!j].ask(1,w,w)*pw2[pos[i][j].size()-k-1])%mod;
					dp[i][j]=(dp[i][j]+1ll*(T[!j].ask(1,1,w-1)-T2[!j].ask(1,1,w-1)+mod)*pw2[pos[i][j].size()-k-1])%mod;
//					cout<<i<<' '<<w<<','<<!j<<':'<<1ll*(T[!j].ask(1,1,w-1)-T2[!j].ask(1,1,w-1)+mod)*pw2[pos[i][j].size()-k-1]%mod<<' '<<1ll*T2[!j].ask(1,w,w)*pw2[pos[i][j].size()-k-1]<<endl;
				}
			}
			for(j=0;j<2;j++)
			{
				for(k=0;k<pos[i][j].size();k++)
				{
					int w=pos[i][j][k];
//					cout<<"add "<<!j<<' '<<w-1<<endl;
					T[!j].add(1,1,w-1,2);
					T2[!j].add(1,1,w-1,2);
					T[!j].add(1,w,w,2);
					T3[!j].add(1,1,w,2);
//					sum2[w]++;
				}	
				T[j].add(1,i+1,dp[i][j]);
				T2[j].add(1,i+1,dp[i][j]);
				T3[j].add(1,i+1,dp[i][j]);
			}
//			cout<<i<<':'<<dp[i][0]<<' '<<dp[i][1]<<endl;
		}	
		printf("%d\n",(dp[cnt][0]+dp[cnt][1]-1ll+mod)%mod);
	}
}
/*
2
3
1 5 0
2 5 0
1 2 0
*/
```

---

## 作者：Unnamed114514 (赞：1)

按照左端点排序，这一步是为了让所有区间左边的和它不交的区间对它造成贡献，同时我们取的时候也可以按照左端点从小到大取。

定义 $f_{i,r,0/1}$ 表示当前处理的是第 $i$ 个区间，最大的右端点为 $r$，颜色为 $0/1$ 的方案数，注意开始时先把 $l,r$ 离散化，$m$ 为离散化后值的上界。

考虑 $(l,r,c)$ 的贡献：

- 不取，有：$f_{i,\_,\_}\gets f_{i-1,\_,\_}$。

- 上一个最大的右端点的区间和它颜色不同，那么它们一定不交：$f_{i,r,c}\gets f_{i,r,c}+\sum\limits_{k=1}^{l-1}f_{i-1,k,1-c}$。

- 上一个最大的右端点的区间和它颜色不同，那么我们就要考虑这两个 $r$ 的大小关系，若原来的 $R<r$，那么此时贡献的右端点就是 $r$，即：$f_{i,r,c}\gets f_{i,r,c}+\sum\limits_{k=1}^{r-1} f_{i-1,k,c}$。

- 否则 $R\ge r$，那么贡献的是原来的 $R$，因此有 $\forall r'\in[r,m],f_{i,r',m}\gets f_{i,r',m}+f_{i-1,r,m}$，即 $f_{i,r',m}\gets 2f_{i,r',m}$。

注意到第一个直接继承即可，然后第二三个是单点加，第四个是区间乘，直接线段树维护即可。

THUWC Day1 T1 也可以用同样的方法解决。

```cpp
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
#define int long long
#define endl '\n'
using namespace std;
const int N=1e5+5,mod=998244353;
int T,n,m,lsh[N<<1],t[N<<3][2],tag[N<<3][2];
struct node{
	int l,r,c;
	bool operator <(const node &o) const{ return l<o.l; }
}f[N];
void build(int p,int l,int r){
	t[p][0]=t[p][1]=0,tag[p][0]=tag[p][1]=1;
	if(l==r) return;
	int mid=l+r>>1;
	build(ls,l,mid),build(rs,mid+1,r);
}
void pushdown(int p){
	t[ls][0]=t[ls][0]*tag[p][0]%mod,tag[ls][0]=tag[ls][0]*tag[p][0]%mod;
	t[rs][0]=t[rs][0]*tag[p][0]%mod,tag[rs][0]=tag[rs][0]*tag[p][0]%mod;
	t[ls][1]=t[ls][1]*tag[p][1]%mod,tag[ls][1]=tag[ls][1]*tag[p][1]%mod;
	t[rs][1]=t[rs][1]*tag[p][1]%mod,tag[rs][1]=tag[rs][1]*tag[p][1]%mod;
	tag[p][0]=tag[p][1]=1;
}
void add(int p,int l,int r,int c,int pos,int val){
	if(l==r){
		t[p][c]=(t[p][c]+val)%mod;
		return;
	}
	pushdown(p);
	int mid=l+r>>1;
	if(pos<=mid) add(ls,l,mid,c,pos,val);
	else add(rs,mid+1,r,c,pos,val);
	t[p][0]=(t[ls][0]+t[rs][0])%mod;
	t[p][1]=(t[ls][1]+t[rs][1])%mod;
}
void mul(int p,int l,int r,int c,int ql,int qr){
	if(ql<=l&&r<=qr){
		tag[p][c]=tag[p][c]*2%mod;
		t[p][c]=t[p][c]*2%mod;
		return;
	}
	pushdown(p);
	int mid=l+r>>1;
	if(ql<=mid) mul(ls,l,mid,c,ql,qr);
	if(mid<qr) mul(rs,mid+1,r,c,ql,qr);
	t[p][0]=(t[ls][0]+t[rs][0])%mod;
	t[p][1]=(t[ls][1]+t[rs][1])%mod;
}
int qsum(int p,int l,int r,int c,int ql,int qr){
	if(ql>qr) return 0;
	if(ql<=l&&r<=qr) return t[p][c];
	pushdown(p);
	int mid=l+r>>1,res=0;
	if(ql<=mid) res=(res+qsum(ls,l,mid,c,ql,qr))%mod;
	if(mid<qr) res=(res+qsum(rs,mid+1,r,c,ql,qr))%mod;
	return res;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;++i) cin>>f[i].l>>f[i].r>>f[i].c,lsh[i]=f[i].l,lsh[i+n]=f[i].r;
		sort(lsh+1,lsh+2*n+1);
		m=unique(lsh+1,lsh+2*n+1)-lsh-1;
		for(int i=1;i<=n;++i) f[i].l=lower_bound(lsh+1,lsh+m+1,f[i].l)-lsh,f[i].r=lower_bound(lsh+1,lsh+m+1,f[i].r)-lsh;
		sort(f+1,f+n+1);
		build(1,1,m);
		for(int i=1;i<=n;++i){
			mul(1,1,m,f[i].c,f[i].r,m);
			add(1,1,m,f[i].c,f[i].r,(qsum(1,1,m,f[i].c^1,1,f[i].l-1)+qsum(1,1,m,f[i].c,1,f[i].r-1)+1)%mod);
		}
		cout<<(qsum(1,1,m,0,1,m)+qsum(1,1,m,1,1,m)+1)%mod<<endl;
	}
	return 0;
}
```

---

## 作者：yuyc (赞：1)

提供一种不一样的状态设计。

将所有区间按右端点排序后，设 $dp_{i,j,k}$ 表示前 $i$ 个区间中，选出的右端点最靠右的颜色为 $k$ 的区间，其右端点位于 $j$ 的方案数。

如果不选第 $i$ 个区间，$dp_{i-1,j,k}$ 对 $dp_{i,j,k}$ 作贡献。

如果选第 $i$ 个区间：

对于 $k \not= c_i,j<l_i$，也就是不与任何异色区间相交的情况，$dp_{i-1,j,k}$ 同样对 $dp_{i,j,k}$ 作贡献。


对于 $k = c_i$，右端点最靠右的颜色为 $k$ 的区间必定为区间 $i$，故对于任意 $j<l_i$，$dp_{i-1,j,k \operatorname{xor}1}$ 对 $dp_{i,r_i,k}$ 作贡献。

整理可得： 

$$dp_{i,j,k}=dp_{i-1,j,k} + dp_{i-1 ,j,k}[j<l_i,k\not= c_i]$$

特别地，

$$dp_{i,r_i,c_i}=dp_{i-1,r_i,c_i}+\sum_{j<l_i}dp_{i - 1,j,c_i \operatorname{xor}1}$$

滚动数组后，操作就变为了区间乘 $2$，单点加，区间求和，两种颜色分别建一棵线段树来维护即可。

[代码](https://www.luogu.com.cn/paste/d6eo1zk8)

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/P9561)

# 思路：

按线段的 $r$ 端点排序，对两种颜色建两颗不同的线段树，枚举当前线段，设当前线段颜色是 $A$，当前线段如果不选的话，当前线段的 $l$ 左边的颜色 $B$ 的线段全部都能转移到当前的 $r$ 端点处，如果选择选当前的线段的话，当前线段的 $l$  左边的颜色 $B$ 的线段全部 $\times 2$，因为颜色 $B$ 可以选或者不选。

最后答案即为某一种颜色全部加起来，注意最开始从 $0$ 开始往右边转移。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
const int mod=998244353;
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
int T,n,q,m,a[N],bn,b[N<<1],cnt;
struct node{
    int s,m,f;
}tr1[N<<2],tr2[N<<2];
struct node1{
    int l,r;
    bool c;
}sm[N<<1];
int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1){
            res=res*a%mod;
        }
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
void pu1(int p){
    tr1[p].s=tr1[p<<1].s+tr1[p<<1|1].s;
}
void pd1(int p,int pl,int pr){
    int mid=(pl+pr)>>1;
    tr1[p<<1].s=(tr1[p<<1].s*tr1[p].m+tr1[p].f*(mid-pl+1))%mod;
    tr1[p<<1|1].s=(tr1[p<<1|1].s*tr1[p].m+tr1[p].f*(pr-mid))%mod;
    tr1[p<<1].m=(tr1[p<<1].m*tr1[p].m)%mod;
    tr1[p<<1|1].m=(tr1[p<<1|1].m*tr1[p].m)%mod;
    tr1[p<<1].f=(tr1[p<<1].f*tr1[p].m+tr1[p].f)%mod;
    tr1[p<<1|1].f=(tr1[p<<1|1].f*tr1[p].m+tr1[p].f)%mod;
    tr1[p].m=1;
    tr1[p].f=0;
}
void ua1(int p,int pl,int pr,int l,int r,int z){
    z%=mod;
    if(l<=pl&&r>=pr){
        tr1[p].f=(tr1[p].f+z)%mod;
        tr1[p].s=(tr1[p].s+(pr-pl+1)*z)%mod;
        return;
    }
    pd1(p,pl,pr);
    int mid=(pl+pr)>>1;
    if(l<=mid){
        ua1(p<<1,pl,mid,l,r,z);
    }
    if(r>mid){
        ua1(p<<1|1,mid+1,pr,l,r,z);
    }
    pu1(p);
}
void um1(int p,int pl,int pr,int l,int r,int z){
    z%=mod;
    if(l<=pl&&r>=pr){
        tr1[p].m=(tr1[p].m*z)%mod;
        tr1[p].f=(tr1[p].f*z)%mod;
        tr1[p].s=(tr1[p].s*z)%mod;
        return;
    }
    pd1(p,pl,pr);
    int mid=(pl+pr)>>1;
    if(l<=mid){
        um1(p<<1,pl,mid,l,r,z);
    }
    if(r>mid){
        um1(p<<1|1,mid+1,pr,l,r,z);
    }
    pu1(p);
}
int q1(int p,int pl,int pr,int l,int r){
    if(l<=pl&&r>=pr){
        return tr1[p].s;
    }
    pd1(p,pl,pr);
    int mid=(pl+pr)>>1,res=0;
    if(l<=mid){
        res+=q1(p<<1,pl,mid,l,r);
    }
    if(r>mid){
        res+=q1(p<<1|1,mid+1,pr,l,r);
    }
    return res;
}
void b1(int p,int pl,int pr){
    tr1[p].m=1;
    tr1[p].f=0;
    if(pl==pr){
        tr1[p].s=0;
        return;
    }
    int mid=(pl+pr)>>1;
    b1(p<<1,pl,mid);
    b1(p<<1|1,mid+1,pr);
    pu1(p);
}
void pu2(int p){
    tr2[p].s=tr2[p<<1].s+tr2[p<<1|1].s;
}
void pd2(int p,int pl,int pr){
    int mid=(pl+pr)>>1;
    tr2[p<<1].s=(tr2[p<<1].s*tr2[p].m+tr2[p].f*(mid-pl+1))%mod;
    tr2[p<<1|1].s=(tr2[p<<1|1].s*tr2[p].m+tr2[p].f*(pr-mid))%mod;
    tr2[p<<1].m=(tr2[p<<1].m*tr2[p].m)%mod;
    tr2[p<<1|1].m=(tr2[p<<1|1].m*tr2[p].m)%mod;
    tr2[p<<1].f=(tr2[p<<1].f*tr2[p].m+tr2[p].f)%mod;
    tr2[p<<1|1].f=(tr2[p<<1|1].f*tr2[p].m+tr2[p].f)%mod;
    tr2[p].m=1;
    tr2[p].f=0;
}
void ua2(int p,int pl,int pr,int l,int r,int z){
    z%=mod;
    if(l<=pl&&r>=pr){
        tr2[p].f=(tr2[p].f+z)%mod;
        tr2[p].s=(tr2[p].s+(pr-pl+1)*z)%mod;
        return;
    }
    pd2(p,pl,pr);
    int mid=(pl+pr)>>1;
    if(l<=mid){
        ua2(p<<1,pl,mid,l,r,z);
    }
    if(r>mid){
        ua2(p<<1|1,mid+1,pr,l,r,z);
    }
    pu2(p);
}
void um2(int p,int pl,int pr,int l,int r,int z){
    z%=mod;
    if(l<=pl&&r>=pr){
        tr2[p].m=(tr2[p].m*z)%mod;
        tr2[p].f=(tr2[p].f*z)%mod;
        tr2[p].s=(tr2[p].s*z)%mod;
        return;
    }
    pd2(p,pl,pr);
    int mid=(pl+pr)>>1;
    if(l<=mid){
        um2(p<<1,pl,mid,l,r,z);
    }
    if(r>mid){
        um2(p<<1|1,mid+1,pr,l,r,z);
    }
    pu2(p);
}
int q2(int p,int pl,int pr,int l,int r){
    if(l<=pl&&r>=pr){
        return tr2[p].s;
    }
    pd2(p,pl,pr);
    int mid=(pl+pr)>>1,res=0;
    if(l<=mid){
        res+=q2(p<<1,pl,mid,l,r);
    }
    if(r>mid){
        res+=q2(p<<1|1,mid+1,pr,l,r);
    }
    return res;
}
void b2(int p,int pl,int pr){
    tr2[p].m=1;
    tr2[p].f=0;
    if(pl==pr){
        tr2[p].s=0;
        return;
    }
    int mid=(pl+pr)>>1;
    b2(p<<1,pl,mid);
    b2(p<<1|1,mid+1,pr);
    pu2(p);
}
signed main(){
    T=read();
    while(T--){
        n=read();
        cnt=0;
        for(int i=1,l,r;i<=n;i++){
            bool c;
            l=read();
            r=read();
            cin>>c;
            sm[i]={l,r,c};
            b[++cnt]=l;
            b[++cnt]=r;
        }
        sort(b+1,b+1+cnt);
        m=unique(b+1,b+1+cnt)-b-1;
        for(int i=1;i<=n;i++){
            auto[l,r,x]=sm[i];
            sm[i].l=lower_bound(b+1,b+1+m,l)-b;
            sm[i].r=lower_bound(b+1,b+1+m,r)-b;
        }
        sort(sm+1,sm+1+n,[&](node1 a,node1 b){return a.r==b.r?a.l<b.l:a.r<b.r;});
        b1(1,0,m);
        b2(1,0,m);
        ua1(1,0,m,0,0,1);
        ua2(1,0,m,0,0,1);
        for(int i=1;i<=n;i++){
            auto[l,r,x]=sm[i];
            if(x==0){
                int s=q1(1,0,m,0,l-1);
                ua2(1,0,m,r,r,s);
                um1(1,0,m,0,l-1,2);
            }else{
                int s=q2(1,0,m,0,l-1);
                ua1(1,0,m,r,r,s);
                um2(1,0,m,0,l-1,2);
            }
        }
        cout<<q1(1,0,m,0,m)%mod<<endl;
    }
    return 0;
}
```

完结撒花~

---

