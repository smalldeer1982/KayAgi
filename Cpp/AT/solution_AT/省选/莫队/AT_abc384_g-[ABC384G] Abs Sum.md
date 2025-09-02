# [ABC384G] Abs Sum

## 题目描述

给定长度为 $N$ 的整数序列 $A,B$ 和长度为 $K$ 的正整数序列 $X,Y$，对于 $k=1,2,3,...,K$，求 $\sum_{i = 1}^{X_k} \sum_{j = 1}^{Y_k} |A_i-B_j|$。

## 说明/提示

### 样例解释
#### 测试数据1
当 $k=1$ 时，答案为 $|A_1-B_1|=1$，因此第 $1$ 行输出一个整数 $1$。    
当 $k=2$ 时，答案为 $|A_1-B_1|+|A_1-B_2|=1+3=4$，因此第 $2$ 行输出一个整数 $4$。  
当 $k=3$ 时，答案为 $|A_1-B_1|+|A_2-B_1|=1+1=2$，因此第 $3$ 行输出一个整数 $2$。  
当 $k=4$ 时，答案为 $|A_1-B_1|+|A_1-B_2|+|A_2-B_1|+|A_2-B_2|=1+3+1+1=6$，因此第 $4$ 行输出一个整数 $6$。

### 数据范围
- $1 \leq N \leq 10^5$
- $0 \leq A_i,B_j \leq 2 \times 10^8$
- $1 \leq K \leq 10^4$
- $1 \leq X_k,Y_k \leq N$

## 样例 #1

### 输入

```
2
2 4
3 5
4
1 1
1 2
2 1
2 2```

### 输出

```
1
4
2
6```

## 样例 #2

### 输入

```
5
1163686 28892 1263085 2347878 520306
1332157 1202905 2437161 1291976 563395
5
5 3
1 5
2 3
1 2
5 5```

### 输出

```
13331322
2209746
6366712
207690
20241215```

# 题解

## 作者：Milthm (赞：15)

如你所见，这是一道 diff 为 $2343$ 的题目，看上去十分困难。

你十分惊慌，恐怕这道题你根本就无法做出来，马上就要面临着 rating $-114$ 的到来。

你冷静地思考了一会，发现这是你最擅长的莫队题目，你逐渐有了一些自信。

你发现如果运用莫队的技巧，那么问题就变成了：每次往 $a,b$ 中添加或删除一个值，然后维护 $\sum|a_i-b_j|$ 的值。这个问题当然是好做的，比如我们添加了一个 $a_i$，那么 $\sum\limits_j |a_i-b_j|$ 就是它产生的贡献，我们只需要分 $b_j\le a_i$ 和 $b_j>a_i$ 两种情况计算贡献即可。对于这一部分，可以把数组离散化之后将值放到树状数组上，解决这个偏序问题。

但是这个做法不会 TLE 吗？

在耀眼的光芒中，你看见了可爱的 lxy。她告诉你，你取块长为 $\frac{n}{\sqrt m}$，常数不要太大，就能稳过这题，时间复杂度是 $O(n\sqrt m \log n)$。

你非常高兴，很快就打出了一份代码，你调了二十分钟后，获得了一个绿色的 AC。


```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int n,m,a[N],b[N],vala[N],valb[N],ls[N],t,sum,siz=1e3,ans,rr[N];
struct yhb{
	int l,r,id;
}qwq[N];
int cmp(yhb x,yhb y){
	if(x.l/siz!=y.l/siz)return x.l<y.l;
	return (x.l/siz)&1?x.r<y.r:x.r>y.r;
}
struct BIT{
	int c[N];
	void add(int x,int k){
		while(x<=t)c[x]+=k,x+=x&-x;
	}
	int ask(int x){
		int ans=0;
		while(x)ans+=c[x],x-=x&-x;
		return ans;
	}
	int query(int l,int r){
		return ask(r)-ask(l-1);
	}
}A,Acnt,B,Bcnt;
void addx(int x,int k){
	//cout<<"a:"<<x<<" "<<k<<'\n';
	ans+=k*(Bcnt.query(1,a[x])*vala[x]-B.query(1,a[x]));
	ans+=k*(B.query(a[x]+1,t)-Bcnt.query(a[x]+1,t)*vala[x]);
	A.add(a[x],k*vala[x]);Acnt.add(a[x],k);
	//cout<<ans<<'\n';
}
void addy(int x,int k){
	//cout<<"b:"<<x<<" "<<k<<'\n';
	ans+=k*(Acnt.query(1,b[x])*valb[x]-A.query(1,b[x]));
	ans+=k*(A.query(b[x]+1,t)-Acnt.query(b[x]+1,t)*valb[x]);
	B.add(b[x],k*valb[x]);Bcnt.add(b[x],k);
	//cout<<ans<<'\n';
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i],vala[i]=a[i],ls[++t]=a[i];
	for(int i=1;i<=n;++i)cin>>b[i],valb[i]=b[i],ls[++t]=b[i]; 
	sort(ls+1,ls+t+1);
	for(int i=1;i<=n;++i)a[i]=lower_bound(ls+1,ls+t+1,a[i])-ls;
	for(int i=1;i<=n;++i)b[i]=lower_bound(ls+1,ls+t+1,b[i])-ls;
	cin>>m;
	for(int i=1;i<=m;++i)cin>>qwq[i].l>>qwq[i].r,qwq[i].id=i;
	sort(qwq+1,qwq+m+1,cmp);
	int l=0,r=0;
	for(int i=1;i<=m;++i){
		while(l>qwq[i].l)addx(l--,-1);
		while(r>qwq[i].r)addy(r--,-1);
		while(l<qwq[i].l)addx(++l,1);
		while(r<qwq[i].r)addy(++r,1);
		//cout<<l<<" "<<r<<'\n';
		rr[qwq[i].id]=ans;
	}
	for(int i=1;i<=m;++i)cout<<rr[i]<<'\n';
	return 0;
}
```

熟悉我的朋友们可能发现了，这篇文章和我的 [abc380g](https://www.luogu.com.cn/article/e2plnt1n) 题解有什么太大区别？

其实是有的，就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/21dunfwl.png
)

这次我成功了。

---

## 作者：lzyqwq (赞：14)

锐评一下带 $\log n$ 的官解有没有素质啊。

> - 给出长度为 $n$ 的序列 $a,b$，$q$ 次询问 $x,y$，求 $\sum\limits_{i=1}^x\sum\limits_{j=1}^y|a_i-b_j|$。
>
> - $n,q\le 10^5$。

考虑以 $B=\mathcal{O}(\sqrt n)$ 为块长分块。

预处理 $F_{i,j}$ 表示 $a$ 的前 $i$ 块与 $b$ 的前 $j$ 块的答案。可以枚举 $j$，记块 $j$ 的右端点为 $r$，然后指针 $p$ 从 $1$ 扫到 $n$，先维护好 $b_1\sim b_j$ 的信息，$p$ 每扫到一个新的值就查询 $p$ 与 $b_1\sim b_j$ 的贡献并统计。每扫到一个块的右端点就记录一下答案。

一共 $\mathcal{O}(n)$ 次修改和 $\mathcal{O}(n\sqrt n)$ 次查询，容易使用 $\mathcal{O}(\sqrt n)-\mathcal{O}(1)$ 的分块维护。

剩余的贡献形如散块对一段前缀。注意到散块元素只有 $\mathcal{O}(\sqrt n)$ 个，可以暴力累加所有元素的贡献。考虑把散块挂在前缀的右端点，扫描线维护前缀信息，然后遍历散块内的元素查询。同样使用 $\mathcal{O}(\sqrt n)-\mathcal{O}(1)$ 的分块维护。注意到散块形如一个区间，因此直接在前缀右端点上挂一个区间即可。这样空间线性。

时间复杂度为 $\mathcal{O}(n\sqrt n)$，空间复杂度为 $\mathcal{O}(n)$。

[AC Link & Code](https://atcoder.jp/contests/abc384/submissions/60897506)

---

## 作者：FiraCode (赞：9)

我们发现，这就是给你一个矩阵，第 $i$ 行第 $j$ 列的权值是 $\left | A_i - B_j \right |$，有 $k$ 个询问，每次问你矩阵里 $(1,1)$ 到 $(x,y)$ 的和。

然后我么发现每个矩阵都有一个 $(1, 1)$ 固定，只有 $(x,y)$ 在变，所以就直接类似一维莫队，然后维护两个权值线段树，一个维护当前扫到的所有 $B_j$，另一个维护当前扫到的所有 $A_i$。

然后考虑新加一个 $x + 1$，那么就是说多了 $\sum \left | A_{x + 1} - B_j \right |$，那么就把绝对值拆开，然后就是在维护 $B$ 的权值线段树上，查 $\le A_{x + 1}$ 的 $B_j$ 的和以及数量，以及 $> A_{x + 1}$ 的 $B_j$ 的和以及数量，然后删除和关于 $y$ 的类似，然后就做完了。

---

## 作者：q1uple (赞：4)

赛时秒了但没时间写了/ll，~~写一篇题解纪念一下~~。\
注意到问题中没有修改,又因为 $ 1\le\ N\le\ 10^5 $，考虑一下莫队。\
绝对值是很好拆开的，比如对于 $ \displaystyle\ \sum_{j=1}^{K}\ \left|X-B_j\ \right| $ 这样的式子，可以先对于 $X < B_j$ 的部分进行处理，再对 $X \ge B_j$ 进行处理，只需要维护区间和即可。\
注意到 $1\le\ K\le\ 10^4$，我们在莫队过程中顺便用 $2$ 个树状数组分别维护 $A$，$B$ 两个序列，用莫队跑一遍就做完了。\
时间复杂度是 $O(n \sqrt{k} \log k)$ 的。可以通过。\
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=4e5+6,mod=1e9+7,INF=2e9;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
#define qmi(a,b) a=min(a,b)
#define qma(a,b) a=max(a,b)
#define rep(i,l,r) for(int i=(l);i<=(r);i++)
#define atrep(i,l,r) for(int i=(r);i>=(l);i--)
#define vec vector<int>
#define pb push_back
namespace fast_IO {
#define IOSIZE 100000
	char ibuf[IOSIZE], obuf[IOSIZE], *p1 = ibuf, *p2 = ibuf, *p3 = obuf;
#define getchar() ((p1==p2)and(p2=(p1=ibuf)+fread(ibuf,1,IOSIZE,stdin),p1==p2)?(EOF):(*p1++))
#define putchar(x) ((p3==obuf+IOSIZE)&&(fwrite(obuf,p3-obuf,1,stdout),p3=obuf),*p3++=x)
#define isdigit(ch) (ch>47&&ch<58)
#define isspace(ch) (ch<33)
	template<typename T> inline T read() { T s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s * w; }
	template<typename T> inline bool read(T &s) { s = 0; int w = 1; char ch; while (ch = getchar(), !isdigit(ch) and (ch != EOF)) if (ch == '-') w = -1; if (ch == EOF) return false; while (isdigit(ch)) s = s * 10 + ch - 48, ch = getchar(); return s *= w, true; }
	template<typename T> inline void print(T x) { if (x < 0) putchar('-'), x = -x; if (x > 9) print(x / 10); putchar(x % 10 + 48); }
	inline bool read(char &s) { while (s = getchar(), isspace(s)); return true; }
	inline bool read(char *s) { char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) *s++ = ch, ch = getchar(); *s = '\000'; return true; }
	inline void print(char x) { putchar(x); }
	inline void print(char *x) { while (*x) putchar(*x++); }
	inline void print(const char *x) { for (int i = 0; x[i]; i++) putchar(x[i]); }
	inline bool read(std::string& s) { s = ""; char ch; while (ch = getchar(), isspace(ch)); if (ch == EOF) return false; while (!isspace(ch)) s += ch, ch = getchar(); return true; }
	inline void print(std::string x) { for (int i = 0, n = x.size(); i < n; i++) putchar(x[i]); }
	inline bool read(bool &b) { char ch; while(ch=getchar(), isspace(ch)); b=ch^48; return true; }
	inline void print(bool b) { putchar(b+48); }
	template<typename T, typename... T1> inline int read(T& a, T1&... other) { return read(a) + read(other...); }
	template<typename T, typename... T1> inline void print(T a, T1... other) { print(a), print(other...); }
	struct Fast_IO { ~Fast_IO() { fwrite(obuf, p3 - obuf, 1, stdout); } } io;
	template<typename T> Fast_IO& operator >> (Fast_IO &io, T &b) { return read(b), io; }
	template<typename T> Fast_IO& operator << (Fast_IO &io, T b) { return print(b), io; }
#define cout io
#define cin io
#define endl '\n'
} using namespace fast_IO;
int bl[N],S,n;
struct que{
	int l,r,id;
	bool operator <(const que &x) const{
		if(bl[l]!=bl[x.l])	return bl[l]<bl[x.l];
		if(bl[l]&1)	return r<x.r;return r>x.r;
	}
}g[N]; 
int a[N],b[N];
int lsha[N],lshb[N];
vec lsh;
int ans[N];
const int SZ=N-5;
struct BIT{
	#define lowbit(x)  ((x)&(-x))
	pii t[N];
	void add(int x,int l,int p){
		while(x<=SZ){t[x].first+=l,t[x].second+=p;x+=lowbit(x);}
	}
	pii query(int x){
		int res=0,ans=0;
		while(x){
			res+=t[x].first;
			ans+=t[x].second;
			x-=lowbit(x);
		}
		return {res,ans};
	}	
}T[2];
int ANS=0; 
pii operator -(pii x,pii y){
	return {x.first-y.first,x.second-y.second};
}
void add(int x,int id){
	if(id==0){
		pii l=T[1].query(lsha[x]);	
		pii r=T[1].query(SZ)-T[1].query(lsha[x]);
		ANS+=(l.second*a[x]-l.first);
		ANS+=(r.first-(r.second)*a[x]);
		T[0].add(lsha[x],a[x],1);
	}else{
		pii l=T[0].query(lshb[x]);	
		pii r=T[0].query(SZ)-T[0].query(lshb[x]);
		ANS+=(l.second*b[x]-l.first);
		ANS+=(r.first-r.second*b[x]);
		T[1].add(lshb[x],b[x],1);
	}
}
void del(int x,int id){
	if(id==0){
		pii l=T[1].query(lsha[x]);	
		pii r=T[1].query(SZ)-T[1].query(lsha[x]);
		ANS-=(l.second*a[x]-l.first);
		ANS-=(r.first-r.second*a[x]);
		T[0].add(lsha[x],-a[x],-1);
	}else{
		pii l=T[0].query(lshb[x]);	
		pii r=T[0].query(SZ)-T[0].query(lshb[x]);
		ANS-=(l.second*b[x]-l.first);
		ANS-=(r.first-r.second*b[x]);
		T[1].add(lshb[x],-b[x],-1);
	}
}
signed main(){
	cin>>n;
	S=sqrt(n);
	rep(i,1,n)	bl[i]=(i-1)/S+1;
	rep(i,1,n)	cin>>a[i];
	rep(i,1,n)	cin>>b[i];
	rep(i,1,n)	lsh.pb(a[i]);
	rep(i,1,n)	lsh.pb(b[i]);
	sort(lsh.begin(),lsh.end());
	rep(i,1,n)	lsha[i]=lower_bound(lsh.begin(),lsh.end(),a[i])-lsh.begin()+1;
	rep(i,1,n)	lshb[i]=lower_bound(lsh.begin(),lsh.end(),b[i])-lsh.begin()+1;	
	int q;
	cin>>q;
	rep(i,1,q){
		cin>>g[i].l>>g[i].r;g[i].id=i;
	}
	sort(g+1,g+q+1);
	int L=0,R=0;
	rep(i,1,q){
		while(g[i].l<L)	del(L--,0);
		while(g[i].r>R)	add(++R,1);
		while(g[i].l>L)	add(++L,0);
		while(R>g[i].r)	del(R--,1);
		ans[g[i].id]=ANS;
	}
	rep(i,1,q)	cout<<ans[i]<<endl;
}
```

---

## 作者：HasNoName (赞：3)

### 思路
考虑莫队。

将每对询问的 $X_i$ 和 $Y_i$ 分别看成一维。

对于一个 $|A_i-B_j|$ 的询问，考虑将 $A_i\ge B_j$ 和 $A_i<B_j$ 的情况分类讨论。

用树状数组维护即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
unordered_map<int,int>mxmn;
struct Q
{
	int x,y,w;
}q[N];
int a[N],b[N],tmp[N],p[N],c[3][N],n,mnmx[N];//不要把mnmx开成unordered_map
ll s[3][N],sum,ans[N];
bool cmp(Q a,Q b)//莫队
{
	if(p[a.x]!=p[b.x])return a.x<b.x;
	if(p[a.x]&1)return a.y<b.y;
	return a.y>b.y;
}
void tradd(int x,int t,int f)//树状数组
{
	int u=x;
	for(;x<=n+n;x+=x&(-x))
	{
		c[t][x]+=f;
		s[t][x]+=f*mnmx[u];
	}
}
ll getcnt(int x,int t)
{
	ll sum=0;
	for(;x;x-=x&(-x))
		sum+=c[t][x];
	return sum;
}
ll getsum(int x,int t)
{
	ll sum=0;
	for(;x;x-=x&(-x))
		sum+=s[t][x];
	return sum;
}
void add(int x,int t,int f)//莫队移动下标是的增与减。x：数字，t：那个数组，f：增还是减
{
	if(t==1)//分A和B数组讨论
	{
		sum+=f*(mnmx[x]*getcnt(x,2)-getsum(x,2)+getsum(n+n,2)-
			getsum(x,2)-mnmx[x]*(getcnt(n+n,2)-getcnt(x,2)));//分类讨论（大小）
		tradd(x,t,f);
	}
	else
	{
		sum+=f*(mnmx[x]*getcnt(x,1)-getsum(x,1)+getsum(n+n,1)-
			getsum(x,1)-mnmx[x]*(getcnt(n+n,1)-getcnt(x,1)));
		tradd(x,t,f);
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T,t;
	cin>>n;
	t=sqrt(n);
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		p[i]=(i-1)/t+1;//分块
		tmp[i]=a[i];
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		tmp[i+n]=b[i];
	}
	sort(tmp+1,tmp+n+n+1);
	int k=0;
	tmp[0]=-1;
	for(int i=1;i<=n+n;i++)
		if(tmp[i]!=tmp[i-1])
		{
			mxmn[tmp[i]]=++k;
			mnmx[k]=tmp[i];
		}
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		cin>>q[i].x>>q[i].y;
		q[i].w=i;//离线
	}
	sort(q+1,q+T+1,cmp);
	for(int i=1;i<=n;i++)
	{
		a[i]=mxmn[a[i]];
		b[i]=mxmn[b[i]];
	}
	ll l=0,r=0;
	for(int i=1;i<=T;i++)//莫队
	{
		while(l<q[i].x)add(a[++l],1,1);//下标移动
		while(l>q[i].x)add(a[l--],1,-1);
		while(r<q[i].y)add(b[++r],2,1);
		while(r>q[i].y)add(b[r--],2,-1);
		ans[q[i].w]=sum;//得到答案
	}
	for(int i=1;i<=T;i++)cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：huangjinxiu (赞：3)

定义 $f(x,y)={\sum_{i=1}^{x}\sum_{j=1}^{y}}\left\vert A_i-B_j\right\vert$ 即询问 $(x,y)$ 的答案。
 
发现 $f(x,y)$ 转移到 $f(x,y+1)$，$f(x+1,y)$，$ f(x-1,y)$，$f(x,y-1)$ 可以快速处理。并且观察到询问总数很小，于是自然地想到莫队。

以 $f(x,y)\rightarrow f(x+1,y)$ 为例（其余的同理）：

$f(x+1,y)=f(x,y)+(f(x+1,y)-f(x,y))$

$f(x+1,y)=f(x,y)+\sum_{j=1}^{y}\left\vert A_{x+1}-B_j\right\vert$ 

我们考虑把绝对值拆开分别算 ，只需要获取数组 $B$ 的前 $y$ 个元素中的所有小于等于 $A_{x+1}$ 的值的个数 $siz$ 与和总和 $val$。这部分的贡献为 $siz\times A_{x+1}-val$。剩下部分都是大于 $A_{x+1}$ 的数，贡献为 $\sum_{j=1}^{y}B_j -val-(y-siz)\times A_{x+1}$，第一项求和可以简单前缀和直接做。

上述操作中求(前缀)区间小于等于某个数的所有数的和与个数可以用主席树轻松完成。单次复杂度为 $O(\log{V})$( $V$ 表示未离散化的值域，懒得写离散化了)。~~写完发现其实可以直接用值域树状数组维护~~

还要注意 $n,q$ 不同阶，块长取 $\frac {n} {\sqrt{q}}$ 效率最高。复杂度为 $O(n\sqrt{q}\log{V})$，常数可能比较大。

代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long //坏习惯  
#define pii pair<int,int>
#define fi first
#define se second
#define pb emplace_back
#define ld long double
using namespace std;
namespace IO{
	const int maxn=(1<<20);char *p1,*p2,buf[maxn];
	#define gc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,maxn,stdin),p1==p2)?EOF:*p1++)
	int read(){
		int f=1,k=0;char c;
		while(!isdigit(c=gc()))if(c=='-')f=-1;
		while(isdigit(c))k=k*10+c-48,c=gc();
		return f*k;
	}
	void write(int k,char c){
		if(k<0){putchar('-');k=-k;}
		char st[21];int top=0;
		do{st[++top]=(k%10)|48,k/=10;}while(k);
		while(top)putchar(st[top--]);
		putchar(c);
	}
}using namespace IO;
const int N=1e5+10,MN=0,MX=2e8;
int a[N],b[N],suma[N],sumb[N],n,m,val,l,r,B;
struct Q{int l,r,id,ans;}q[N];
pii operator +(pii x,pii y){
	return {x.fi+y.fi,x.se+y.se};
}
bool cmp(Q x,Q y){
	if(x.l/B==y.l/B){
		if((x.l/B)&1)return x.r>y.r;
		else return x.r<y.r;
	}
	return x.l<y.l;
}
struct HJT_SGT{
	struct Tree{int ls,rs,val,siz;}tr[N*32];
	int cnt=0,root[N],ql,qr,pos;//pos是在值域上的位置，其实就是值  
	#define mid ((l+r)>>1) 
	#define ls(u) tr[u].ls 
	#define rs(u) tr[u].rs 
	#define siz(u) tr[u].siz 
	#define val(u) tr[u].val
	void update(int &u,int v,int l,int r){
		tr[u=++cnt]=tr[v];tr[u].val+=pos;++siz(u);
		if(l==r)return ;
		if(pos<=mid)update(ls(u),ls(v),l,mid);
		else update(rs(u),rs(v),mid+1,r);
	}
	void upd(int id,int v){
		pos=v;update(root[id],root[id-1],MN,MX);
	}
	pii query(int u,int l,int r){
		if(!u)return {0,0};
		pii res={0,0};
		if(ql<=l&&r<=qr)return {siz(u),val(u)};
		if(ql<=mid)res=res+query(ls(u),l,mid);
		if(mid<qr)res=res+query(rs(u),mid+1,r);
		return res;
	}
	pii qry(int id,int kl,int kr){
		ql=kl,qr=kr;
		return query(root[id],MN,MX);
	}
}SGT[2];
//这里主席树为了卡常把每次操作的ql,qr,pos都提前改好，不用每次update,query都把其传进去 
//实在卡不过可以考虑离散化，把单次操作的复杂度从(log值域)降为(logn) 
void add_l(int pos){pii res=SGT[1].qry(r,0,a[pos]);val+=(a[pos]*res.fi-res.se)+(sumb[r]-res.se-a[pos]*(r-res.fi));}
void del_l(int pos){pii res=SGT[1].qry(r,0,a[pos]);val-=(a[pos]*res.fi-res.se)+(sumb[r]-res.se-a[pos]*(r-res.fi));}
void add_r(int pos){pii res=SGT[0].qry(l,0,b[pos]);val+=(b[pos]*res.fi-res.se)+(suma[l]-res.se-b[pos]*(l-res.fi));}
void del_r(int pos){pii res=SGT[0].qry(l,0,b[pos]);val-=(b[pos]*res.fi-res.se)+(suma[l]-res.se-b[pos]*(l-res.fi));}
signed main(){  
	n=read();
	for(int i=1;i<=n;++i)SGT[0].upd(i,a[i]=read());
	for(int i=1;i<=n;++i)SGT[1].upd(i,b[i]=read());
	for(int i=1;i<=n;++i)suma[i]=suma[i-1]+a[i];
	for(int i=1;i<=n;++i)sumb[i]=sumb[i-1]+b[i];	
	m=read();B=ceil(1.0*n/sqrt(m));
	for(int i=1;i<=m;++i) q[i]={read(),read(),i};
	sort(q+1,q+1+m,cmp);
	for(int i=1;i<=m;++i){
		int pl=q[i].l,pr=q[i].r;
		//这里的l,r表示当前坐标为(l,r) 实际上并不是区间[l,r]
		//(pl,pr)表示目标位置  
		while(l<pl)add_l(++l);
		while(r<pr)add_r(++r);
		while(l>pl)del_l(l--);
		while(r>pr)del_r(r--);		
		q[i].ans=val;
	}
	sort(q+1,q+1+m,[&](Q x,Q y){
		return x.id<y.id;	
	});
	for(int i=1;i<=m;++i)write(q[i].ans,'\n');
	return 0;
}
```

---

## 作者：Lightwhite (赞：2)

考虑一次询问类似一个矩形，分别将 $a,b$ 分块后可以将其分割为整块散块四个部分。对于带有整块的部分，可以预处理一下每个整块对另一个序列每个前缀的答案。

具体来说，对于一个整块，可以对于值域上所有预处理出比 $x$ 更小的数个数及其总和。然后直接枚举另一个序列计算贡献。当然，值域很大，要离散化。复杂度 $O(\frac{n^2}{B})$。

于是询问只剩下了散块和散块。如果直接拿下来树状数组或者排序或者二分又是带 $\log$ 的，这很不好。发现可以提前对于每个块进行排序，记一下排序前的位置。枚举散块所在整块，把在散块里的拿下来就好了。两个排序后的数组求答案可以直接双指针。复杂度 $O(mB)$。

平衡一下复杂度，取 $B=\frac{n}{\sqrt q}$，可以做到 $O(n\sqrt q)$ 的时间复杂度。

跑的比我写的莫队树状数组只快了三分之一，可见莫队树状数组常数之优秀。

代码很丑。

[Submission.](https://atcoder.jp/contests/abc384/submissions/65737010)

---

## 作者：Conan15 (赞：2)

2024.12.15：修改对于 $x,y$ 指针的歧义表述。

感觉在线不太好写，所以往离线方面想了。\
离线的话需要维护双指针（当前的 $x$ 和 $y$，表示现在的答案是 $\sum\limits_{i=1}^{x} \sum\limits_{j=1}^{y} \left| A_i - B_j \right|$）并支持移动这两个指针，所以容易想到**莫队**。\
之后需要支持统计答案，显然需要数据结构维护拆掉绝对值之后的东西，赛时有想过树状数组但是没写出来，还是我太菜了。

首先将 $a,b$ 离散化，然后以 $a$ 为例进行统计。\
即分别计算 $b_j \gt a_i$ 和 $b_j \lt a_i$ 的数字总和、数量，就可以直接计算出绝对值。\
$b$ 同理，于是套个莫队就做完了。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 15, Q = 1e4 + 15;
int n, q, B;
int m, a[N], b[N], c[N];

struct Queries {
    int x, y, id;
} qry[Q];
inline bool cmp(Queries a, Queries b) {
    if (a.x / B  != b.x / B) return a.x < b.x;
    return a.y < b.y;
}

struct BIT {
    long long tr[N];
    inline void add(int x, int d) { for ( ; x <= m; x += x & -x) tr[x] += d; }
    inline long long query(int x) {
        long long res = 0;
        for ( ; x ; x -= x & -x) res += tr[x];
        return res;
    }
} sum[2], cnt[2];
//0 x - 1 y

long long ans[Q], Ans = 0;
inline void change(int val, bool xy, int opt) {
    long long res = 0;
    val = (xy == 0) ? a[val] : b[val];
    //right
    res += (sum[xy ^ 1].query(m) - sum[xy ^ 1].query(val)) - (cnt[xy ^ 1].query(m) - cnt[xy ^ 1].query(val)) * 1ll * c[val];
    //left
    res += (cnt[xy ^ 1].query(val) * 1ll * c[val]) - sum[xy ^ 1].query(val);
    Ans += res * opt;
    sum[xy].add(val, c[val] * opt), cnt[xy].add(val, opt);
}
inline void add(int x, bool opt) { change(x, opt, 1); }
inline void del(int x, bool opt) { change(x, opt, -1); }

int main() {
    scanf("%d", &n), B = sqrt(n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]), c[++m] = a[i];
    for (int i = 1; i <= n; i++) scanf("%d", &b[i]), c[++m] = b[i];
    sort(c + 1, c + 1 + m);
    m = unique(c + 1, c + 1 + m) - c - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(c + 1, c + 1 + m, a[i]) - c;
    for (int i = 1; i <= n; i++) b[i] = lower_bound(c + 1, c + 1 + m, b[i]) - c;

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) scanf("%d%d", &qry[i].x, &qry[i].y), qry[i].id = i;
    sort(qry + 1, qry + 1 + q, cmp);
    int x = 0, y = 0;
    for (int i = 1; i <= q; i++) {
        int xx = qry[i].x, yy = qry[i].y;
        while (x < xx) add(++x, 0);
        while (y < yy) add(++y, 1);
        while (x > xx) del(x--, 0);
        while (y > yy) del(y--, 1);
        ans[qry[i].id] = Ans;
    }
    for (int i = 1; i <= q; i++) printf("%lld\n", ans[i]);
    return 0;
}
```

---

## 作者：NTT__int128 (赞：2)

# AT_abc384_g [ABC384G] Abs Sum题解
~~题外话：论我考场上想到了莫队，却一直在想怎么插入，没有意识到可以预先确定每个元素插在哪里……~~

显然的莫队。考虑怎么快速转移。

我用 $l,r$ 表示现在求出了 $\sum\limits_{i=1}^{l}\sum\limits_{j=1}^{r}|A_i-B_j|$。

假设我们现在要求 $\sum\limits_{i=1}^{l+1}\sum\limits_{j=1}^{r}|A_i-B_j|$：

不难发现，此时的答案为 $\sum\limits_{i=1}^{l}\sum\limits_{j=1}^{r}|A_i-B_j|+\sum\limits_{j=1}^{r}|A_{l+1}-B_j|$。把后边那一堆东西去一下绝对值。假设有 $C$ 个 $B_j\le A_{l+1}(1\le j\le r)$，它们的和为 $S$，则 $\sum\limits_{j=1}^{r}|A_{l+1}-B_j|=C\cdot A_{l+1}-S-(r-C)\cdot A_{l+1}+(\sum\limits_{j=1}^{r}B_j-S)$。其中，$C,S$ 可以用树状数组或线段树维护。

求 $[l-1,r],[l,r+1],[l,r-1]$ 时的答案同理。

时间复杂度：$\Theta(K\cdot\sqrt N\cdot\log N)$。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,m,a[N],b[N],c[N],d[N],t,ans[N],cnt,g[N<<1],l;
struct ask{
	int l,r,id;
	bool operator<(const ask&_)const{return (l/t==_.l/t?r<_.r:l<_.l);}
}q[N];
struct binary_tree{
	int t[N<<1];
	binary_tree(){memset(t,0,sizeof t);}
	int low(int x){return (x&-x);}
	void up(int x,int v){while(x<=l)t[x]+=v,x+=low(x);}
	int qy(int x){int s=0;while(x)s+=t[x],x-=low(x);return s;}
}tac,tas,tbc,tbs;
void add_a(int x){
	cnt+=a[x]*tbc.qy(c[x])-tbs.qy(c[x])-a[x]*(tbc.qy(l)-tbc.qy(c[x]))+(tbs.qy(l)-tbs.qy(c[x]));
	tac.up(c[x],1);
	tas.up(c[x],a[x]);
}
void add_b(int x){
	cnt+=b[x]*tac.qy(d[x])-tas.qy(d[x])-b[x]*(tac.qy(l)-tac.qy(d[x]))+(tas.qy(l)-tas.qy(d[x]));
	tbc.up(d[x],1);
	tbs.up(d[x],b[x]);
}
void del_a(int x){
	cnt-=a[x]*tbc.qy(c[x])-tbs.qy(c[x])-a[x]*(tbc.qy(l)-tbc.qy(c[x]))+(tbs.qy(l)-tbs.qy(c[x]));
	tac.up(c[x],-1);
	tas.up(c[x],-a[x]);
}
void del_b(int x){
	cnt-=b[x]*tac.qy(d[x])-tas.qy(d[x])-b[x]*(tac.qy(l)-tac.qy(d[x]))+(tas.qy(l)-tas.qy(d[x]));
	tbc.up(d[x],-1);
	tbs.up(d[x],-b[x]);
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],g[++l]=a[i];
	for(int i=1;i<=n;i++)cin>>b[i],g[++l]=b[i];
	sort(g+1,g+l+1);
	l=unique(g+1,g+l+1)-g-1;
	for(int i=1;i<=n;i++)c[i]=lower_bound(g+1,g+l+1,a[i])-g;
	for(int i=1;i<=n;i++)d[i]=lower_bound(g+1,g+l+1,b[i])-g;
	t=sqrt(n);
	cin>>m;
	for(int i=1;i<=m;i++)cin>>q[i].l>>q[i].r,q[i].id=i;
	sort(q+1,q+m+1);
	int l=0,r=0;
	for(int i=1;i<=m;i++){
		while(l<q[i].l)add_a(++l);
		while(r<q[i].r)add_b(++r);
		while(r>q[i].r)del_b(r--);
		while(l>q[i].l)del_a(l--);
		ans[q[i].id]=cnt; 
	}
	for(int i=1;i<=m;i++)cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：_determination_ (赞：2)

场了，感谢这题送了我人生中第一个 2400 并带我上蓝。

拆式子，绝对值题考虑分讨。

$$\sum_{i=1}^{n}\sum_{j=1}^{m}\left | a_i-b_j \right|$$

$$(\sum_{i=1}^{n}\sum_{j=1}^{m}a_i-b_j) - 2(\sum_{i=1}^{n}\sum_{j=1}^{m}(a_i-b_j)[a_i<b_j] )$$

左侧部分是唐，不管。考虑右侧。右侧显然也可以做到单组询问 $O(n\log n)$ 的速度做到，类似逆序对的拉个树状数组维护一下即可。

发现将 $n$ 与 $m$ 增加 $1$ 或减少 $1$ 并统计贡献是简单的，直接考虑莫队。复杂度 $O(n\sqrt{q}\log n)$。小小 $2\times 10^8$ 随便过。

[code](https://atcoder.jp/contests/abc384/submissions/60758203) 还是比较简单的，算上调试信息才写 3k，记得离散化。当时离散化害得我场上多调 20min。

---

## 作者：KazamaRuri (赞：1)

## 题意

给定长度为 $N$ 的整数序列 $A=(A_1,A_2,\ldots,A_N)$ 和 $B=(B_1,B_2,\ldots,B_N)$，以及长度为 $K$ 的整数序列 $X=(X_1,X_2,\ldots,X_K)$ 和 $Y=(Y_1,Y_2,\ldots,Y_K)$。

对于每个 $k= 1,2,\ldots,K $，求出 $\displaystyle \sum_{i=1}^{X_k} \sum_{j=1}^{Y_k}| A_i-B_j| $。

AI 翻译。

## 分析

发现知道 $(x,y)$ 求 $(x+1,y)$，$(x,y-1)$ 的答案是 ez 的，具体的讲是一次类似查比 $A_x$ 小的数的和或者数量。那么就可以得到一个 $O(n\sqrt n \log n)$ 的莫队加权值数据结构的做法，注意到询问很少，把块长从 $\sqrt n$ 改到 $\sqrt {n\log n}$ 就不会 TLE 了。最优块长我懒得算了，可以发在评论里。

## 代码

我用的的 BIT。


```cpp
#include <bits/stdc++.h>
#define lc(x) (x<<1)
#define rc(x) (x<<1|1)
#define lb(x) (x&-x)
using namespace std;
using ll=long long;
using pii=pair<ll,int>;
const int N=1e5+5;
int n,m,a[N],b[N],cnt,h[N<<1],len,bl[N],l,r; ll sa[N],sb[N],ans[N],sum;
struct BIT{
	int n,c[N<<1]; ll t[N<<1];
	void init(int n){ this->n=n; for(int i=0;i<=n;i++) t[i]=c[i]=0; }
	void upd(int x,int k,int p){ k*=p; for(;x<=n;x+=lb(x)) t[x]+=k,c[x]+=p; }
	int askc(int x){ int s=0; for(;x;x-=lb(x)) s+=c[x]; return s; }
	ll asks(int x){ ll s=0; for(;x;x-=lb(x)) s+=t[x]; return s; }
}t0,t1;
struct node{
	int l,r,id;
	bool operator<(const node &o)const{
		return bl[l]==bl[o.l]?bl[l]&1?r<o.r:r>o.r:l<o.l;
	}
}t[N]; unordered_map<int,int>mp;
inline void addA(int x){ sum+=1ll*x*(2*t1.askc(mp[x])-r)+(sb[r]-2*t1.asks(mp[x])),t0.upd(mp[x],x,1); }
inline void delA(int x){ sum-=1ll*x*(2*t1.askc(mp[x])-r)+(sb[r]-2*t1.asks(mp[x])),t0.upd(mp[x],x,-1); }
inline void addB(int x){ sum+=1ll*x*(2*t0.askc(mp[x])-l)+(sa[l]-2*t0.asks(mp[x])),t1.upd(mp[x],x,1); }
inline void delB(int x){ sum-=1ll*x*(2*t0.askc(mp[x])-l)+(sa[l]-2*t0.asks(mp[x])),t1.upd(mp[x],x,-1); }
int main(){
	scanf("%d",&n),len=sqrt(n*log2(n))+1;
	for(int i=1;i<=n;i++)
		scanf("%d",a+i),h[i]=a[i],sa[i]=sa[i-1]+a[i];
	for(int i=1;i<=n;i++)
		scanf("%d",b+i),h[i+n]=b[i],sb[i]=sb[i-1]+b[i];
	for(int i=1;i<=n;i++) bl[i]=(i-1)/len+1;
	sort(h+1,h+1+2*n),cnt=unique(h+1,h+1+2*n)-h-1;
	for(int i=1;i<=cnt;i++) mp[h[i]]=i; t0.init(cnt),t1.init(cnt);
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&t[i].l,&t[i].r),t[i].id=i;
	sort(t+1,t+1+m);
	for(int i=1;i<=m;i++){
		int u=t[i].l,v=t[i].r;
		while(l<u) addA(a[++l]);
		while(r<v) addB(b[++r]);
		while(l>u) delA(a[l--]);
		while(r>v) delB(b[r--]);
		ans[t[i].id]=sum;
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：Down_syndrome (赞：1)

## 前言

你怎么知道我赛时贺平衡树板子来代替树状数组结果发现平衡树有空间问题错失 AK。

大失败啊。

## 题意

给定 $N,K$，长度为 $N$ 的数组 $A,B$，长度为 $K$ 的数组 $X,Y$，对于每个 $k\in[1,K]$，求解 $\sum\limits_{i=1}^{X_k}\sum\limits_{j=1}^{Y_k}|A_i-B_j|$。

## 思路

这里我们引入[莫队](https://oi-wiki.org/misc/mo-algo-intro/)算法，来求解这个问题。

那么如何判定一个莫队问题呢？？

1. 奇怪的区间询问。

2. 单次添加/删除一个元素的复杂度不高。

3. 可以离线。

这样你就可以考虑使用莫队来做了。

或许有人会问，这也不是区间询问啊？

诶，在这道题中，我们可以拓宽一下这条限制，改为：与左右端点有关并且相对独立的询问。

诶，这句话是什么意思呢？？

这我们就要讲到莫队的原理了！

### 普通莫队算法

假设我们在探讨一个区间询问的问题。现在我们有如下的一些询问：

![](https://cdn.luogu.com.cn/upload/image_hosting/s41vlwrz.png)

询问按照紫、红、蓝的顺序。

我们考虑暴力一点的做法。

我们钦定两个指针 $l$ 和 $r$，一开始，$l=1,r=0$。

我们统一维护区间 $[l,r]$ 的答案。对于一个询问区间 $[ql,qr]$，如果指针 $l>ql$，就加上第 $l-1$ 个数的贡献，并令 $l\gets l-1$；如果指针 $l<ql$，就减去第 $l$ 个数的贡献，并令 $l\gets l+1$。右端点亦然。

就像这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/0tqj9tv8.png)

很显然这样的复杂度是错的。假设加入和删除的复杂度是 $O(1)$，这样的做法非常容易会被卡到 $O(nm)$。于是普通莫队算法应运而生。

莫队算法的核心就是把询问离线下来，排序，然后跑暴力算法。其中最重要的就是排序这部分了，这是保证复杂度的关键。

我们考虑将原序列分块，块长为 $B$，**按照左端点所在块为第一关键字，右端点为第二关键字**排序，跑暴力算法，总体复杂度则为 $O(\frac{n^2}{B}+mB)$。

我知道你很急，但你先别急，我们来分析一下复杂度。

我们分别考虑两个端点的移动数量。

先考虑左端点。

假设现在有两个询问 $[ql_i,qr_i]$ 和 $[ql_{i+1},qr_{i+1}]$，令 $bel_x$ 表示 $x$ 所在的块。这两个询问之间有两种可能：

1. $bel_{ql_i}=bel_{ql_{i+1}}$，这种情况下，左端点最多移动 $B$ 步，总共最多移 $mB$ 步。

2. $bel_{ql_i}\ne bel_{ql_{i+1}}$，因为最多只有 $\frac{n}{B}$ 个块，所以最多只有 $\frac{n}{B}$ 个这种情况，总共最多移 $\frac{n^2}{B}$ 步。

再考虑右端点。

1. $bel_{ql_i}=bel_{ql_{i+1}}$，这种情况下，右端点只会往右移，所以对于每个块，右端点最多移 $n$ 步，总共最多移 $\frac{n^2}{B}$ 步。

2. $bel_{ql_i}\ne bel_{ql_{i+1}}$，因为最多只有 $\frac{n}{B}$ 个块，所以最多只有 $\frac{n}{B}$ 个这种情况，总共最多移 $\frac{n^2}{B}$ 步。

因为加入和删除的复杂度是 $O(1)$，所以总复杂度就是 $O(\frac{n^2}{B}+mB)$。取块长为 $\frac{n}{\sqrt m}$ 可以得到较优复杂度 $O(n\sqrt m)$。

### 回归原题

学习了普通莫队算法的你，可以聪明的发现，普通莫队算法其实不一定要求询问的是一个“区间”，只要其有两个端点（其实多个也可以，只不过复杂度会更劣一点），拓展端点时能够加入删除，并且两端点之间相对独立，也就是说可以单独更改一个端点而不会影响另一个端点，就能够使用莫队。

对于这道题目，我们把 $X_k,Y_k$ 看做 $ql$ 和 $qr$，就能够实施莫队算法了！

现在唯一的问题是如何高效地加入和删除一个数。

考虑拆掉绝对值。

具体的，我们可以离散化后维护 $4$ 个权值树状数组，分别维护：当前加入的 $A$ 数组中小于等于 $x$ 的数的个数、当前加入 $A$ 数组中小于等于 $x$ 的数的和、当前加入的 $B$ 数组中小于等于 $x$ 的数的个数、当前加入 $B$ 数组中小于等于 $x$ 的数的和。

以在 $A$ 中加入一个数 $v$ 为例，令当前加入的 $B$ 数组中小于等于 $x$ 的数的个数为 $query1(x)$、当前加入 $B$ 数组中小于等于 $x$ 的数的和为 $query2(x)$，则 $v$ 的贡献为 $query1(v)\times v-query2(v)+query2(\infty)-query2(v)-(query1(\infty)-query1(v))\times v$。

取块长为 $\frac{n\sqrt{m\log n}}{m}$，总复杂度做到 $O(n\sqrt{m\log n})$。

然后这道题就做完了。

加上奇偶排序等优化，加上 AT 神机，成功拯救了这道题的高复杂度，每个点都在一秒以内跑完。

[code](https://atcoder.jp/contests/abc384/submissions/60791230)

AT 上有 $O(n\sqrt m)$ 的做法，有点强，各位感兴趣的可以[去学](https://atcoder.jp/contests/abc384/editorial/11618)。

---

