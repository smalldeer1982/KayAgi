# [JRKSJ R2] 你的名字。

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/73iq08qk.png)

## 题目描述

给你一个长为 $n$ 的序列 $a$，有 $m$ 次查询，每次查询区间 $[l,r]$ 模 $k$ 意义下的最小值。

## 说明/提示

Idea：mcyl35，Solution：mcyl35，Code：mcyl35，Data：cyffff&mcyl35

本题采用捆绑测试。

| $\text{Subtask}$ | $n,m\le$ | $k,a_i\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $\text{1}$ | $10^4$ | $10^5$ | 无 | $3$ | $1$ |
| $\text{2}$ | $10^5$ | $300$ | 无 | $6$ | $1$ |
| $\text{3}$ | $10^5$ | $10^5$ | $k\ge 10^3$ | $10$ | $1\to2$ |
| $\text{4}$ | $10^5$ | $10^5$ | 无 | $19$ |$2\to4$ |
| $\text{5}$ | $3\times10^5$ | $10^5$ | 数据随机 | $14$ |$1$ |
| $\text{6}$ | $3\times10^5$ | $10^5$ | $k\ge 10^3$ | $2$ |$2\to3$ |
| $\text{7}$ | $3\times10^5$ | $10^5$ | 无 | $46$ |$2\to5$ |

对于 $100\%$ 的数据，$1\le n,m\le3\times10^5$，$1\le a_i,k\le 10^5$。

前 $6$ 个 $\text{Subtask}$ 的空间限制为 $256\text{MB}$，第 $7$ 个 $\text{Subtask}$ 的空间限制为 $128\text{MB}$。

## 样例 #1

### 输入

```
10 10
15 14 14 4 8 10 18 14 10 9 
2 10 8
2 4 7
3 9 6
1 7 5
3 4 6
6 6 12
4 8 20
1 6 18
7 8 8
2 6 6```

### 输出

```
0
0
0
0
2
10
4
4
2
2```

## 样例 #2

### 输入

```
5 5
77 24 80 90 92 
2 3 84
4 5 37
1 1 4
3 5 85
1 4 46```

### 输出

```
24
16
1
5
24```

# 题解

## 作者：critnos (赞：20)

我们认为 $n,m$ 同级，下面一律写为 $n$；令 $v=\max\{a_i\}$。

sol：$O(n(\sqrt v+\sqrt n))$ 时间，$O(v+n)$ 空间。

code：$O(n(\sqrt v+\sqrt n))$ 时间，$O(v\log v+n)$ 空间（为了卡常数，有人用线性空间过题了请通知我，谢谢！）。

根号分治。

我们令分治界为 $\Theta(\sqrt v)$。

当 $k\le \sqrt v$ 时，将所有 $k$ 相同的询问同时处理。此时使用 $O(n)-O(\sqrt v)$（注意 $O(\sqrt v)$ 是个上界） 的 RMQ 数据结构即可。因为询问是 $O(n)$ 级别，序列长度总和为 $O(n\sqrt v)$ 级别的。

当 $k> \sqrt v$ 时，枚举 $p=ck$，$p\le v$，$c$ 为自然数。求所有的 $\min\{a_x-p|l\le x\le r\land a_x\ge p\}$ 的 $\min$ 即 $\min\{a_x|l\le x\le r\land a_x\ge p\}-p$，即 $p$ 的区间不严格后继（再减去 $p$）。这个问题可以这样转化是因为本质上 $a\bmod b=a-cb,cb\le a<(c+1)b$，然后虽然这样做每个数进行了大量非取模操作，但是唯一的一次取模操作一定小于其他的非取模操作。

关于区间不严格后继问题，可以通过序列和询问同步排序扫描的方式转化为单点修改区间 $\min$ 的问题。具体的，询问按 $p$ 排序，序列也需排序。枚举询问。维护一个单调递减的在序列上的指针，对于每个 $p$，通过指针单调移动将序列中的大于等于 $p$ 的数加入数据结构中。那么此时数据结构中维护的数就是所有大于等于 $p$ 的数，区间 $\min$ 即为 $p$ 的区间后继。

注意到修改 $\Theta(n)$ 次而查询 $O(n\sqrt v)$ 次，所以允许修改时间复杂度升高。可以通过分块降低猫树（二区间合并）更新复杂度的方式做到。即维护每块的前缀后缀 $\min$，和整块的 $\min$ 组成的长度为 $\Theta(\sqrt n)$ 的序列的猫树。

查询的时候，若 $l,r$ 在同一个块中，则直接暴力（这实质上是第二个根号分治，不是“区间不严格后继”暴力，而是直接按题暴力，即不进入 $k>\sqrt v$ 的根号分治），复杂度为 $O(\sqrt n)$；否则由左块的后缀，右块的前缀和猫树维护的中间块组成。更新前缀后缀复杂度为 $O(\sqrt n)$，更新猫树的复杂度仍为 $\Theta(\sqrt n)$。所以此时做到了 $O(n(\sqrt v+\sqrt n))$ 的复杂度。

另外枚举 $p$ 时不能把每个询问都存下来，否则空间复杂度会退化。

卡常数大家就各显神通吧（流汗黄豆

代码不放了，需要者私信。

![](https://cdn.luogu.com.cn/upload/image_hosting/73iq08qk.png)

---

## 作者：CXY07 (赞：16)

> 题目链接：[P7811 [JRKSJ R2] 你的名字。](https://www.luogu.com.cn/problem/P7811)

> **本题解同步发布于 [My Blog](http://www.cxy07.blog/index.php/archives/123/)**

题意：

> 给定长度为 $n$ 的序列 $\{a_n\}$，共 $m$ 组询问，每次询问一个区间 $[l,r]$ 中，在 $\bmod\  k$ 意义下的最小值。

> $1\le n,m\le 3\times 10^5, 1\le a_i\le 10^5$。

~~受不了了根本卡不动~~

这题我曾经自己编出来过，但只会 $\mathcal{O}(n\sqrt{n\log n})$。/kk

考虑根号分治。设一个阈值 $V$，分别考虑 $k>V$ 和 $k\le V$ 的询问。

对于 $k\le V$ 的询问，本质不同的 $k$ 只有 $V$ 种。因此可以将其中 $k$ 相同的拿出来一起做。对于一个固定的 $k$，设 $b_i=a_i\bmod k$，使用分块或线段树等 $\mathcal{O}(n)$ 预处理的数据结构进行维护即可。这里的复杂度是 $\mathcal{O}(nV+m\log n)$ 或 $\mathcal{O}(nV+m\sqrt{n})$。

对于 $k>V$ 的询问，考虑到 $a\bmod k=a-ck$，所以考虑枚举 $k$ 的倍数 $ck$，然后寻找一个 $a_i$ 使得 $a_i\ge ck$ 且 $a_i - ck$ 最小。不难发现一个询问会变成 $\mathcal{O}(\dfrac{10^5}{V})$ 个上述问题。这里需要注意一下空间。

考虑将序列中的元素降序排序，所有询问也降序排序，双指针维护，依次将 $\ge k$ 的元素插入序列，然后询问区间最小值即可完成上述问题。

上述问题中，插入只有 $\mathcal{O}(n)$ 次，而询问有 $\mathcal{O}(\dfrac{10^5m}{V})$ 次，因此考虑把插入的复杂度变高些以平衡查询的复杂度。

考虑使用猫树的思想，做到 $\mathcal{O}(1)$ 的查询。但猫树的插入是 $\mathcal{O}(n)$ 的，无法接受。因此先分块，在分块的结构上套一个猫树，每次插入一个元素后更新整块的值，再记录每个块的前缀、后缀 $\min$，就可以做到 $\mathcal{O}(\sqrt{n})$ 的插入，$\mathcal{O}(1)$ 的查询。

因此此部分是 $\mathcal{O}(n\sqrt{n}+\dfrac{10^5m}{V})$。

发现 $V$ 取 $\sqrt{10^5}$ 复杂度达到最优，最后时间复杂度是 $\mathcal{O}((n+m)\sqrt{n}+m\sqrt{10^5})$。~~代码先不放了 因为本人还没卡过~~

---

## 作者：meyi (赞：8)

[dX 的题解](https://www.luogu.com.cn/blog/_post/401942) 目前已经不能通过本题，但是加上一个又合理又奇怪（？）的特判，便可通过本题。

令阈值为 $B$，考虑 $k\le B$ 的情况，我们需要 $O(n)$ 计算出 $a_i \bmod k$ 的值，但如果当前的 $k$ 的询问数很少，其实不如将这些询问与 $k\ge B$ 的询问一起处理，这样做可以省下计算 $a$ 数组取模后的值的开销。

由此可以很自然地想到一个特判：如果 $\min(\frac{a}{i},\frac{a}{w})\times|q|\le \alpha n$，那么就将当前的询问放在最后处理。
其中，$\min(\frac{a}{i},\frac{a}{w})$ 表示通过 bitset 计算一个答案的花费，$|q|$ 表示询问数量，$\alpha$ 是~~可以通过手动二分得到的~~平衡因子。

不难发现，由于 $\frac{a}{i}$ 随 $i$ 增大而减小，所以我们可以不设置阈值，让它完全自适应测试数据。

实际测试中，这个特判表现得相当优秀，我在多次调整阈值后仍TLE的点，在加上这个特判后只跑了 0.2s，~~当然也不排除出题人还能造出来卡掉这个特判的数据~~。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int maxa=1e5+1,maxn=3e5+1;
template<class T>inline bool ckmin(T &x,const T &y){return x>y?x=y,1:0;}
template<class T>inline bool ckmax(T &x,const T &y){return x<y?x=y,1:0;}
template<class T>inline void clear(T *arr,int siz,int val=0){memset(arr,val,sizeof(T)*(siz+1));}
static char pbuf[1000000],*p1=pbuf,*p2=pbuf,obuf[1000000],*o=obuf;
#define getchar() p1==p2&&(p2=(p1=pbuf)+fread(pbuf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define putchar(x) (o-obuf<1000000)?(*o++=(x)):(fwrite(obuf,o-obuf,1,stdout),o=obuf,*o++=(x))
inline int qr(){
	ri in=0;register char ch;
	while(!isdigit(ch=getchar()));
	do in=(in<<1)+(in<<3)+(ch^48);while(isdigit(ch=getchar()));
	return in;
}
template<class T>
void qw(T out){
	if(out>9)qw(out/10);
	putchar(out%10|48);
}
struct flusher{~flusher(){fwrite(obuf,o-obuf,1,stdout);}}autoflush;
int a[maxn],_a[maxn],BB,m,n;
struct qry{
	int l,r,k,id,bel;
	inline qry(int l_=0,int r_=0,int k_=0,int id_=0):l(l_),r(r_),k(k_),id(id_){}
	inline bool operator<(const qry &rhs)const{return bel!=rhs.bel?l<rhs.l:(bel&1)?r<rhs.r:r>rhs.r;}
};
vector<qry>bq,sq[maxa];
typedef unsigned long long ull;
template<int siz>
struct bset{
	ull b[((siz+63)>>6)+1];int len;
	inline bset(){len=(siz+63)>>6;}
	inline void set0(int p){b[p>>6]&=~(1llu<<p);}
	inline void set1(int p){b[p>>6]|=(1llu<<p);}
	inline int find_first(){for(ri i=0;i<len;++i)if(b[i])return (i<<6)|__builtin_ctzll(b[i]);return siz;}
	inline int find_next(int p){
		if(++p>=siz)return siz;
		ri hi=p>>6,lo=p&63;
		if(b[hi]>>lo)return p+__builtin_ctzll(b[hi]>>lo);
		for(ri i=hi+1;i<len;++i)if(b[i])return (i<<6)|__builtin_ctzll(b[i]);
		return siz;
	}
};
bset<maxa>b;
int ans[maxn],cnt[maxn];
int main(){
	n=qr(),m=qr();
	for(ri i=1;i<=n;++i)a[i]=qr();
	for(ri i=1;i<=m;++i){
		ri x=qr(),y=qr(),z=qr();
		sq[z].emplace_back(x,y,z,i);
	}
	for(ri i=2;i<maxa;++i)
		if(sq[i].size()){
			if(min(maxa/i,maxa>>6)*sq[i].size()<(n<<2)){
				bq.insert(bq.end(),sq[i].begin(),sq[i].end());
				continue;
			}
			BB=n/sqrt(sq[i].size())+1;
			for(qry &j:sq[i])j.bel=j.l/BB;
			sort(sq[i].begin(),sq[i].end());
			for(ri j=1;j<=n;++j)_a[j]=a[j]%i;
			ri pl=1,pr=0;
			for(const qry &j:sq[i]){
				while(pl>j.l)if(!cnt[_a[--pl]]++)b.set1(_a[pl]);
				while(pr<j.r)if(!cnt[_a[++pr]]++)b.set1(_a[pr]);
				while(pl<j.l)if(!--cnt[_a[pl++]])b.set0(_a[pl-1]);
				while(pr>j.r)if(!--cnt[_a[pr--]])b.set0(_a[pr+1]);
				ans[j.id]=b.find_first();
			}
			while(pr>=pl)b.set0(_a[pr]),--cnt[_a[pr--]];
		}
	if(bq.size()){
		BB=n/sqrt(bq.size())+1;
		for(qry &i:bq)i.bel=i.l/BB;
		sort(bq.begin(),bq.end());
		ri pl=1,pr=0;
		for(const qry &i:bq){
			while(pl>i.l)if(!cnt[a[--pl]]++)b.set1(a[pl]);
			while(pr<i.r)if(!cnt[a[++pr]]++)b.set1(a[pr]);
			while(pl<i.l)if(!--cnt[a[pl++]])b.set0(a[pl-1]);
			while(pr>i.r)if(!--cnt[a[pr--]])b.set0(a[pr+1]);
			ans[i.id]=i.k;
			for(ri j=b.find_first();ans[i.id]&&j<maxa;j=b.find_next((j/i.k+1)*i.k-1))if(j<maxa)ckmin(ans[i.id],j%i.k);
		}
	}
	for(ri i=1;i<=m;++i)qw(ans[i]),putchar(10);
	return 0;
}
```


---

## 作者：dead_X (赞：8)

## 前言
暴力日过去了。
## 正片
一看到静态区间查询一个莫队一下子拍上去了啊？

看到一个 $k>10^3$ 的包，我们考虑 $k$ 很大的时候有没有特殊性质。

注意到值域只有 $10^5$，那么这个包的意义就是维护一个 ``bitset`` 然后每次直接暴力找最接近的数，时间复杂度 $O(n\sqrt m+\frac{ma}{w}+\frac{ma}{k})$，实现的时候可以用 ``_Find_first`` 和 ``_Find_next`` 来偷懒。

那 $k$ 比较小的时候咋做呢？~~直接阈值分治跑 ``bitset``，时间复杂度 $O(n\sqrt{km}+mk)$~~ 但是其实这就是个 RMQ 啊？我们直接上四毛子就是 $O(nk+m)$ 的了。注意这里一定不能用传统的倍增 ST 表因为复杂度会多个 $\log$。

然后我们惊奇地发现这玩意好像能过，设阈值为 $B$，时间复杂度 $O(nB+\frac{ma}{w}+n\sqrt m+\frac{ma}{B}+mB)$，$B$ 取 $\sqrt a$ 是最优的，总复杂度为 $O(n\sqrt a+m\sqrt a+n\sqrt m+\frac{na}{w})$，是不是看起来就很奇怪，小编也非常惊讶。
## 代码
~~顶碗人代写~~ 原来我就是顶碗人呀！

被卡常了，加了个特判才过去。

值得一提的是我 $k$ 很小的时候真的跑了阈值分治 ``bitset``，居然没被卡！

十几分钟写的，代码有点丑见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int S=256;
struct query
{
	int l,r,b,id,pos;
	bool operator<(const query &lxl)const
	{return (pos<lxl.pos)||(pos==lxl.pos&&((pos&1)?r<lxl.r:r>lxl.r));}
};
vector<query> v[256];
int a[300003],cnt[100003],A[300003],ans[300003];
bitset<100003> f;
int main()
{
    int n=read(),m=read();
    for(int i=1; i<=n; i++) a[i]=read();
    for(int l,r,b,i=1; i<=m; ++i)
    {
    	l=read(),r=read(),b=read();
    	if(b<S) v[b].push_back((query){l,r,0,i,0});
		else v[0].push_back((query){l,r,b,i,0});
	}
	for(int i=2; i<S; i++)
	{
		if(!v[i].size()) continue;
		int bl=n/sqrt((int)v[i].size()+1)+1;
		for(int j=1; j<=n; ++j) A[j]=a[j]%i;
		for(int j=0; j<v[i].size(); ++j) v[i][j].pos=v[i][j].l/bl;
		sort(v[i].begin(),v[i].end());
		for(int j=0,l=1,r=0; j<v[i].size(); ++j)
		{
			while(l>v[i][j].l) (!cnt[A[--l]]++)&&(f[A[l]]=1);
			while(r<v[i][j].r) (!cnt[A[++r]]++)&&(f[A[r]]=1);
			while(l<v[i][j].l) (!--cnt[A[l]])&&(f[A[l]]=0),++l;
			while(r>v[i][j].r) (!--cnt[A[r]])&&(f[A[r]]=0),--r;
			for(int k=0; k<i; ++k) if(f[k]) {ans[v[i][j].id]=k;break;}
		}
		f.reset(),memset(cnt,0,sizeof(cnt));
	}
	if(v[0].size())
	{
		int bl=n/sqrt((int)v[0].size()+1)+1;
		for(int j=0; j<v[0].size(); ++j) v[0][j].pos=v[0][j].l/bl;
		sort(v[0].begin(),v[0].end());
		for(int j=0,l=1,r=0; j<v[0].size(); ++j)
		{
			while(l>v[0][j].l) (!cnt[a[--l]]++)&&(f[a[l]]=1);
			while(r<v[0][j].r) (!cnt[a[++r]]++)&&(f[a[r]]=1);
			while(l<v[0][j].l) (!--cnt[a[l]])&&(f[a[l]]=0),++l;
			while(r>v[0][j].r) (!--cnt[a[r]])&&(f[a[r]]=0),--r;
			ans[v[0][j].id]=0x3f3f3f3f;
			for(int k=f._Find_first(); ans[v[0][j].id]&&k!=f.size(); k=(k/v[0][j].b+1)*v[0][j].b-1>=f.size()?f.size():f._Find_next((k/v[0][j].b+1)*v[0][j].b-1)) 
				(ans[v[0][j].id]>k%v[0][j].b)&&(ans[v[0][j].id]=k%v[0][j].b);
		}
	}	
	for(int i=1; i<=m; i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：违规用户名76G!ihcm (赞：7)

不会猫树。

根号分治，$k\leq B$ 在模完的序列上分块维护块内 $\min$。

$k > B$ 把询问拆成区间 $\geq ik$ 的 $\min$，按 $ik$ 排序离线变成了 $O(n)$ 次插入全局 $\min$ 和 $O(n\sqrt k)$ 次查区间 $\min$。

空间对每个 $k$ 枚举因数做到线性。

序列分块，维护块内前后缀 $\min$，块间 st 表。

修改只影响 st 表根号（$1+2+4+8\cdots +\sqrt n$）个位置。

$l,r$ 同块不用根号分治直接暴力。

总复杂度 $O(n\sqrt n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[300005],n,m,out[300005],L[100005],R[100005],solved[100005],ans[300005],ANS[300005];
struct query
{
	int l,r,k,id;
}b[300005];
inline bool cmp(query x,query y)
{
	return x.k<y.k;
}
namespace small//这里所有unsigned short不必要，其实不很卡常
{
	const int B=567,N=300005,M=100005;
	unsigned short A[N],C[M],mn[N/B+2];
	inline unsigned short query(int l,int r)//分块区间min
	{
		unsigned short rtn=-1;
		if(l/B==r/B)
		{
			for(int i=l;i<=r;i++) rtn=min(rtn,A[i]);
			return rtn; 
		}
		int L=l/B*B+B-1,R=r/B*B;
		for(int i=l;i<=L;i++) rtn=min(rtn,A[i]);
		for(int i=R;i<=r;i++) rtn=min(rtn,A[i]);
		for(int i=l/B+1;i<r/B;i++) rtn=min(rtn,mn[i]);
		return rtn;
	}
	inline void solvek(int x)
	{
		for(int i=0;i<x;i++) C[i]=i;
		for(int i=x;i<=100000;i++) C[i]=C[i-x];//C[i]=i%x
		for(int i=0;i<=n/B;i++) mn[i]=-1;
		for(int i=1;i<=n;i++) A[i]=C[a[i]];//A[i]=a[i]%x
		for(int i=0;i<=n/B;i++)
		{
			int l=max(1,i*B),r=min(n,i*B+B-1);
			for(int j=l;j<=r;j++) mn[i]=min(mn[i],A[j]);//mn[i]块内min
		}
		for(int i=L[x];i<=R[x];i++)
			if(out[b[i].id]==200002) out[b[i].id]=query(b[i].l,b[i].r);
	}
}
namespace large
{
	const int B=3000,N=300005,LG=7;
	int st[LG][N/B+2],qz[N],hz[N],lg[N/B+2];//st表，前后缀min
	inline void change(int p,int x)//改前后缀
	{
		int bel=p/B,L=max(1,bel*B),R=min(n,bel*B+B-1);
		for(int i=p;i<=R;i++) qz[i]=x;
		for(int i=L;i<=p;i++) hz[i]=x;
		st[0][bel]=x,qwqa[p]=x;
	}
	inline void changest(int p,int x)//改st表
	{
		int bel=p/B;
		st[0][bel]=x;
		for(int i=1;i<LG;i++)
		{
			int L=max(0,bel-(1<<i)+1),R=min(bel,n/B-(1<<i)+1);
			for(int j=L;j<=R;j++) st[i][j]=x;
		}
	}
	inline int query(int l,int r)
	{
		int L=l/B+1,R=r/B-1,X=lg[R-L+1];
		return min(hz[l],min(qz[r],R>=L?min(st[X][L],st[X][R-(1<<X)+1]):200002));
	}
	vector <int> v[100005];
	inline void solve()
	{
		for(int i=1;i<=100000;i++) v[i].clear();
		for(int i=1;i<=n;i++) v[a[i]].push_back(i);
		for(int i=2;i<=n/B;i++) lg[i]=lg[i>>1]+1;
		for(int i=1;i<=n;i++) qwqa[i]=qz[i]=hz[i]=200002;
		for(int i=0;i<LG;i++) for(int j=0;j<=n/B;j++) st[i][j]=200002;
		for(int i=100000;i>=1;i--)
		{
			for(auto t:v[i]) change(t,i),changest(t,i);
			for(int j=1;j*j<=i;j++)
			{
				if(i%j==0)
				{
					if(!solved[j]) for(int k=L[j];k<=R[j];k++) ans[k]=min(ans[k],query(b[k].l,b[k].r)-i);
					if(j*j!=i) if(!solved[i/j]) for(int k=L[i/j];k<=R[i/j];k++) ans[k]=min(ans[k],query(b[k].l,b[k].r)-i);
				}
			}
		}
		for(int i=1;i<=m;i++)
			ans[i]=min(ans[i],query(b[i].l,b[i].r));
	}
}
int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for(int i=1;i<=n;i++) cin >> a[i];
	for(int i=1;i<=m;i++)
	{
		cin >> b[i].l >> b[i].r >> b[i].k;
		b[i].id=i,out[i]=200002;
	}
	sort(b+1,b+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		ANS[i]=200002;
		if(b[i].r-b[i].l<=large::B)//同块暴力
		{
			int rtn=200002;
			for(int j=b[i].l;j<=b[i].r;j++) rtn=min(rtn,a[j]%b[i].k);
			ANS[i]=rtn;
		}
		if(!L[b[i].k]) L[b[i].k]=i;
		R[b[i].k]=i,ans[i]=200002;
	}
	for(int i=1;i<=100000;i++) L[i]=max(L[i],1);
	for(int i=1;i<=100000;i++)
	{
		int w1=n;
		long long w2=100000/i*(double)(R[i]-L[i]+1)*3;//对每个k算放到小的和大的的代价
		if(w1<w2) small::solvek(i),solved[i]=1;
	}
	large::solve();
	for(int i=1;i<=m;i++)
	{
		if(ANS[i]<=100000) out[b[i].id]=ANS[i];
		else out[b[i].id]=min(out[b[i].id],ans[i]);
	}
	for(int i=1;i<=m;i++)
		cout << out[i] << "\n";
	return 0;
}
```

---

## 作者：xfrvq (赞：6)

$v=10^5$ 级别的取模。考虑根号分治。

$k\le\sqrt v$：分别处理每个 $k$，问题变成取模后数列的 RMQ。线段树。复杂度 $O(n\sqrt v+m\log n)$。

$k\gt\sqrt v$：莫队时维护每个数是否出现的 `bitset`，`_Find_next()` 找每个循环节的最小答案。复杂度 $O\left(n\sqrt m+m\sqrt v\times\dfrac nw\right)$。

然后过不了。

快读。有些没意义的函数拆掉。手写数组代替 `vector`。没有询问时的特判。莫队块长 $\dfrac n{\sqrt m}$。

然后每个点都能过。只是因为分治界原因不能同时过。

于是我们写个函数，对于一个分治界，尝试估价算法的总计算量。于是可以对数据找到最合适的分治边界。

乱调估价。过了。但是我说的很抽象。看代码吧。

```cpp
#include<bits/stdc++.h>
using namespace std;

// IO

const int N = 3e5 + 5,M = 1e5 + 5;

int n,m,a[N],c[N],ans[N];
bitset<M> b;
int L[N],R[N],K[N];
struct Qry{ int l,r,k,i,b; } Q[N];
int sz[N],cur[N];

namespace sgt{
	int T[N << 2];
	
	#define lc (i << 1)
	#define rc (lc | 1)
	#define mid ((L + R) >> 1)
	#define ls lc,L,mid
	#define rs rc,mid + 1,R
	#define _ int i = 1,int L = 1,int R = n
	
	void build(int k,_){
		if(L == R) return void(T[i] = a[L] % k);
		build(k,ls); build(k,rs); T[i] = min(T[lc],T[rc]);
	}
	
	int qry(int l,int r,_,int s = 2e9){
		if(l <= L && R <= r) return T[i];
		if(l <= mid) s = qry(l,r,ls);
		if(r > mid) s = min(s,qry(l,r,rs));
		return s;
	}
}

int calc(int Bl){
	int tot = 0,cnt = 0;
	static bool vis[N];
	int x = *max_element(a + 1,a + n + 1);
	for(int i = 1;i <= m;++i){
		if(K[i] < Bl){
			if(!vis[i]) vis[i] = 1,tot += n * 4;
			tot += __lg(n) * 3;
		} else ++cnt,tot += x / K[i] * 5;
	}
	tot += n * sqrt(cnt + 1) * 5;
	return tot;
}

int main(){
	n = read(),m = read();
	for(int i = 1;i <= n;++i) a[i] = read();
	for(int i = 1;i <= m;++i)
		L[i] = read(),R[i] = read(),K[i] = read();
	int S = 256,cS = calc(S);
	for(int i = 200,cT;i <= 480;i += 18)
		if((cT = calc(i)) < cS) cS = cT,S = i;
	for(int i = 1;i <= m;++i) ++sz[min(K[i],S)];
	for(int i = 1;i <= S;++i) sz[i] += (cur[i] = sz[i - 1]);
	for(int i = 1;i <= m;++i) Q[cur[min(K[i],S)]++] = {L[i],R[i],K[i],i,0};
	for(int i = 2;i < S;++i) if(sz[i] - sz[i - 1]){
		sgt::build(i);
		for(int j = sz[i - 1];j < sz[i];++j)
			ans[Q[j].i] = sgt::qry(Q[j].l,Q[j].r);
	}
	if(sz[S] - sz[S - 1]){
		int bl = n / sqrt(sz[S] - sz[S - 1] + 1) + 1;
		for(int i = sz[S - 1];i < sz[S];++i) Q[i].b = Q[i].l / bl;
		sort(Q + sz[S - 1],Q + sz[S],[](Qry a,Qry b){
			return a.b ^ b.b ? a.l < b.l : a.b & 1 ? a.r < b.r : a.r > b.r;
		});
		for(int i = sz[S - 1],l = 1,r = 0;i < sz[S];++i){
			while(r < Q[i].r) !c[a[++r]]++ && (b[a[r]] = 1);
			while(l > Q[i].l) !c[a[--l]]++ && (b[a[l]] = 1);
			while(r > Q[i].r) !--c[a[r]] && (b[a[r]] = 0),--r;
			while(l < Q[i].l) !--c[a[l]] && (b[a[l]] = 0),++l;
			ans[Q[i].i] = 2e9;
			for(int j = b._Find_first();ans[Q[i].i] && j < b.size();j = b._Find_next((j / Q[i].k + 1) * Q[i].k - 1))
				if(j < b.size()) ans[Q[i].i] = min(ans[Q[i].i],j % Q[i].k);
		}
	}
	for(int i = 1;i <= m;++i) print(ans[i]),putchar('\n');
	return fwrite(obuf,C-obuf,1,stdout),0;
}
```

---

## 作者：zesqwq (赞：4)

感恩出题人自己卡自己，让抽象复杂度飘过去了。

下面认为 $n,q,V$ 同阶。

一看题解区全都是一些各种套娃做法，这里提供一种思考起来清新，跑起来截止到现在是最优解的做法。

看到取模，根号分治大概逃不掉的，对于 $k<v$ 的数，我们考虑建立线段树来做 $\text{rmq}$ 问题，时间复杂度 $O(nv+q \log n)$；

对于 $k \ge v$ 的数，因为取模就相当于是减去 $xk$，因此 $x \le \dfrac n v$，然后每次查询就可以枚举 $x$，变成了 $\dfrac n v$ 次查询区间非严格后继。

这个问题可以先二区间并（俗称猫树），变成了 $O(n \log n)$ 次的加一个数和 $q \dfrac n v$ 次查询后继，可以自由选择数据结构（压位 $\text{Trie}$，多层分块 **可能** 都可以接受），我选择的的是压位 $\text{Trie}$，此时时间复杂度是 $O(nv + q\log n + q\dfrac n v \dfrac {\log n} {\log w})$，此时取 $v = \sqrt {n \dfrac{\log n}{\log w}}$，时间复杂度为 $O(n \sqrt{n \dfrac{\log n} {\log w}})$。

---

## 作者：ez_lcw (赞：4)

一种较为简单的思路？虽然复杂度稍劣。

考虑以 $B$ 分块，每个询问对于散块我们暴力处理。

对于每个整块，考虑预处理出每个 $k$ 的答案。

设该整块中的数集为 $S$。容易 $O(V)$ 预处理出 $dis_x=\min\{y\in S:y\geq x\}-x$。

那么某个 $k$ 的答案即为 $ans_k=\min\{dis_x:k|x\}$。使用高维后缀和即可在 $O(V\log\log V)$ 的时间内预处理出所有 $ans_k$。

视 $n,m$ 同阶，那么总时间复杂度为 $O(nB+\frac {n^2}B+\frac nBV\log\log V)$。

取 $B=\sqrt{n+V\log\log V}$ 得到 $O(n\sqrt{n+V\log\log V})$。

[需要、卡常。](https://paste.ubuntu.com/p/tSPQKXNDdy/)

---

## 作者：Vidoliga (赞：3)

題解

前言：卡了 $7$ 頁

感觉没什么直接做法，考虑根号分治。

取模区间 min，显然有 $O(n^2)$ 的两种暴力，一直是对于每个查询扫一遍，另一种是枚举模数 $k$ 然后预处理元素后区间查 min。

显然后者拼更有前途，考虑拼 $k \in [1,\sqrt{a}]$ 的后部分暴力。

那如何处理 $k > \sqrt{a}$ 的部分，考虑取模的另类形式 $a \%k=a-\lfloor\dfrac{a}{k}\rfloor k$。

一个显然的事实是 $\forall j \in [0,\lfloor\dfrac{a}{k}\rfloor]$，有 $ a-jk>a-\lfloor\dfrac{a}{k}\rfloor k$

而 $\because k > \sqrt{a}, \therefore \lfloor\dfrac{a}{k}\rfloor \leq \sqrt{a}$。

那么我们就有一个想法了，一次查询相当于对于 $\forall j \in [0,\lfloor\dfrac{a}{k}\rfloor]$，找到区间 $\geq jk$ 的最小值。

$\geq p$ 的限制很烦，值域大到小扫描线，具体的，若当前扫到 $p$ ，已经将 $>p$ 的数更新，加入值为 $p$ 的位置，而此时相当于枚举 $p$ 的因子 $k$，更新所有查询模数为 $k$ 的 min。

但是用什么数据结构维护？

你仔细想想，如果修改复杂度 $O(S_1)$，查询复杂度 $O(S_2)$，不难发现一个位置恰好会被加入一次，固修改复杂度为 $O(S_1 n)$，而一个询问会贡献 $O(\sqrt{a})$ 次查询，复杂度为 $O(S_2 q\sqrt{a})$。

显然修改和查询复杂度不是很平衡，考虑用 $S_1,S_2$ 平衡一下，一个比较显然的 ds 是用 sqrttree 维护一下，单点修改可以做到 $O( \sqrt{n})$，查询可做 $O(\log \log \log n)$ 或者 $O(1)$。

但是常數大，會被卡。

好，那换个小常数的？区间最小值？ $O(S_2q\sqrt{a})$ 显然不能再加 $\text{polylog}$ 的东西，那要 $O(1)$ 的话只有 RMQ，用 st 表维护一下，不需要预处理，动态修改 st 表怎么搞？考虑分块，对每个块维护一个 st 表，块与块之间维护 st 表。

我们搞搞修改，先考虑块内 st 表 的修改，显然的事实是只有一个值被更改了，考虑一下 st 表跳 $2^i$ 的数时，跨过当前被修改的点的区间个数是多少，不难发现是形如 $\sum\limits_{i\geq 0} 2^{i}$ ，而 $i$ 的上界为 $\lfloor \log_{2}{\sqrt{n}} \rfloor$，根据等比数列求和公式不难得出，被影响的区间数为 $O(\sqrt{n})$ 的，而块与块之间的，因为只有一个块被修改，所以可以类似做 $O(\sqrt{n})$。

其实这种操作类似 sqrttree 的修改，但是 sqrttree 如果这样修改由于递归层数为 $O(\log \log n)$ 的，所以复杂度会退化到 $O(\sqrt n \log \log n)$。

那，查询就正常散块并整块查就好了。

时间复杂度 $O(n \sqrt{a} +q \sqrt{a})$，空间复杂度 $O(n)$。

warning，卡常题，建议自行思考实现细节以及自身对代码常数的理解和优化。


---

## 作者：Sakura_xyz (赞：3)

### 题解

完全过不去做法。

设 $n,m$ 同阶，值域为 $w$，考虑对 $k$ 根号分治。

对于小于阈值 $B$ 的 $k$，考虑分块，枚举每一个作为模数的 $i$，处理出块内 $\bmod i$ 的最小值，查询时遍历每个整块，枚举散块中每一个数，设块长为 $\sqrt n$，预处理是 $O(nB)$ 的，查询是 $O(\sqrt n)$ 的，

对于大于阈值的 $k$，考虑最终答案是将询问区间中的所有元素 $a_i$ 写成 $kx + b$ 的形式后，$b$ 的最小值，方便起见，这里的 $x$ 可以取任意小于 $\lfloor \frac{a_i}{k} \rfloor$ 的值，显然，$x \not = \lfloor \frac{a_i}{k} \rfloor$ 一定是不优的，由于 $k > B$ ，则 $x$ 有 $O(\frac{w}{B})$ 种取值。

我们暴力枚举 $kx$ ，此时得到的最小的 $b$ 一定是大于 $kx$ 的所有元素中最小的值减去 $kx$ 。将询问离线下来，从大到小动态地依次将每个数插入到序列中，再维护区间最小值就可以解决问题。

有一个属于我这种普及组选手的解法，用线段树进行 $O(n)$ 次修改和 $O(\frac{nw}{B})$ 次查询，时间复杂度分别为 $O(n\log n)$ 和 $O(\frac{nw}{B}\log n)$，取 $B = \sqrt {w\log n}$，就有一个复杂度为 $n \sqrt {w \log n}$ 的显然做法。

然而这非常不根号平衡，因此这肯定是不优的。考虑修改的复杂度很低，而查询的复杂度很高，那考虑使用一个修改可以带根号而查询是 $O(1)$ 的算法来解决带修 RMQ 问题，事实上这是可行的。

我们再次考虑分块，设块长为 $\sqrt n$，则我们有每次修改 $O(\sqrt n)$，查询 $O(1)$ 的带修 RMQ。观察到我们可以离线处理，对于每个块而言，维护其前后缀最小值，可以做到 $O(\sqrt n)$。对 $O(\sqrt n)$ 个块间建立一棵笛卡尔树，每次修改时更新块内最小值，将笛卡尔树暴力重构。相信没有人不知道，查询时两点间的 LCA 的块内最小值就是答案，使用 tarjan 算法离线查询 LCA 可以做到 $O(1)$ 的复杂度查询。

观察到，对于我们枚举 $i = kx$ 时，由于有其约数个数的限制，所涉及到的询问至多有 $O(n\log n)$ 个，因此离线询问是可以接受的。

然而理论上来讲这个做法可以做到线性空间，观察到很明显唯一空间复杂度带 $\log$ 的地方是离线询问，把笛卡尔树换成在线的 Method of Four Russians 来在线处理 RMQ 就行了。

此时修改复杂度为 $n \sqrt n$，查询复杂度为 $O(\frac{nw}{B})$，取 $B = \sqrt w$，时间复杂度为 $O(n \sqrt n + n \sqrt w)$。

### 代码

由于这种离谱做法的常数非常大，代码不能通过本题，仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
#define MAXN 300005
#define re register

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

const int SZ1=300000000,SZ2=100000000;
char ibuf[SZ1],*p1;
char obuf[SZ2],*p2;
inline void putc(const char x){*p2++=x;}

template <typename T>

inline void read(T & s){
	s=0; char ch=*p1++;
	while(!std :: isdigit(ch)) ch=*p1++;
	while(std :: isdigit(ch)) s=(s<<3)+(s<<1)+(ch^48),ch=*p1++;
}

template <typename T>

inline void WT(T x){
	if(x>9) WT(x/10);
	putc(x%10+48);
}

template <typename T>

inline void write(const T & x){
	WT(x);
	putc('\n');
}

using namespace std;

const int S1=505,S2=567,S3=1090;

int n,m,a[MAXN],L[MAXN],R[MAXN],ans[MAXN];

struct node{
	int l,r,k,id;
	bool operator < (const node & b) const { return k<b.k; }
}q[MAXN];

struct seg{
	int l,r,mn;
}tree[MAXN<<2];

namespace Solve1{
	
	int blk[MAXN],bl[MAXN/S2+2],br[MAXN/S2+2],blkcnt;
	
	int mn[MAXN/S2+2][S1+2];
	
	inline void Init(int N){
		for(re int i=1;i<=n;i++)
			blk[i]=(i-1)/S2+1;
		blkcnt=blk[n];
		for(re int i=1;i<=blkcnt;i++)
			bl[i]=(i-1)*S2+1,br[i]=i*S2;
		br[blkcnt]=n;
		memset(mn,0x3f,sizeof(mn));
		for(re int i=1;i<=blkcnt;i++){
			for(re int k=1;k<=N;k++){
				for(re int j=bl[i];j<=br[i];j++){
					mn[i][k]=min(mn[i][k],a[j]%k);
				}
			}
		}
	}
	
	inline int query(int idx){
		int ret=INT_MAX,l=q[idx].l,r=q[idx].r,k=q[idx].k;
		if(blk[l]==blk[r]){
			for(int i=l;i<=r;i++) ret=min(ret,a[i]%k);
			return ret;
		}
		for(re int i=l;i<=br[blk[l]];i++) ret=min(ret,a[i]%k);
		for(re int i=bl[blk[r]];i<=r;i++) ret=min(ret,a[i]%k);
		for(re int i=blk[l]+1;i<blk[r];i++) ret=min(ret,mn[i][k]);
		return ret;
	}
	
}

namespace Solve2{
	
	int blk[MAXN],bl[MAXN/S3+2],br[MAXN/S3+2],blkcnt;
	
	int lc[MAXN/S3+2],rc[MAXN/S3+2],fa[MAXN/S3+2],val[MAXN/S3+2];

	int pr[MAXN],suf[MAXN];

	int stk[MAXN/S3+2],top=0;
	
	vector <int> v[MAXN];
	
	struct lk{
		int nxt,to,idx;
	}link[MAXN*25];

	int head[MAXN/S3+2],rt,dfn[MAXN/S3+2],dfncnt=0,nodecnt=0,Now;
	
	int Find(int x) { return x==fa[x]?x:fa[x]=Find(fa[x]); }
	
	inline void Init(){
		for(re int i=1;i<=n;i++)
			blk[i]=(i-1)/S3+1;
		blkcnt=blk[n];
		for(re int i=1;i<=blkcnt;i++)
			bl[i]=(i-1)*S3+1,br[i]=i*S3;
		br[blkcnt]=n;
	}
	
	inline void modify(int pos,int vl){
		for(re int i=pos;i<=br[blk[pos]];i++) pr[i]=vl;
		for(re int i=bl[blk[pos]];i<=pos;i++) suf[i]=vl;
		val[blk[pos]]=vl;
	}
	
	inline void Add_query(int x,int y,int id){
		link[++nodecnt].to=y;
		link[nodecnt].nxt=head[x];
		link[nodecnt].idx=id;
		head[x]=nodecnt;
	}
	
	void dfs1(int x){
		if(!x) return;
		dfn[x]=++dfncnt;
		dfs1(lc[x]); dfs1(rc[x]);
	}
	
	void dfs2(int x){
		fa[x]=x;
		if(lc[x]) dfs2(lc[x]),fa[lc[x]]=x;
		if(rc[x]) dfs2(rc[x]),fa[rc[x]]=x;
		for(int i=head[x];i;i=link[i].nxt)
			ans[link[i].idx]=min(ans[link[i].idx],val[Find(link[i].to)]-Now);
	}
	
	inline void build(){
		top=0;
		for(re int i=1,pos;i<=blkcnt;i++){
			pos=top;
			while(pos&&val[stk[pos]]>val[i]) pos--;
			if(pos) rc[stk[pos]]=i;
			if(pos!=top) lc[i]=stk[pos+1];
			stk[top=++pos]=i;
		}
		rt=stk[1];
	}
	
	inline void query(){
		memset(pr,0x3f,sizeof(pr));
		memset(suf,0x3f,sizeof(suf));
		memset(val,0x3f,sizeof(val));
		for(re int i=1;i<=n;i++) v[a[i]].push_back(i);
		for(re int i=1;i<=m;i++){
			if(blk[q[i].l]==blk[q[i].r]){
				for(re int j=q[i].l;j<=q[i].r;j++)
					ans[q[i].id]=min(ans[q[i].id],a[j]%q[i].k);
			}
		}
		bool flag=true;
		for(re int i=100000;i;i--){
			Now=i;
			if(i!=100000) flag=false;
			for(int j : v[i]) modify(j,i),flag=true;
			if(flag){
				memset(lc,0,sizeof(lc));
				memset(rc,0,sizeof(rc));
				build();
			}
			memset(dfn,0,sizeof(dfn));
			memset(fa,0,sizeof(fa));
			memset(head,0,sizeof(head));
			nodecnt=dfncnt=0;
			dfs1(rt);
			for(re int j=1;j*j<=i;j++){
				if(i%j) continue;
				if(j>S1){
					for(re int k=L[j];k<=R[j];k++){
						if(blk[q[k].l]==blk[q[k].r]) continue;
						ans[q[k].id]=min(ans[q[k].id],suf[q[k].l]-i);
						ans[q[k].id]=min(ans[q[k].id],pr[q[k].r]-i);
						if(blk[q[k].l]+1==blk[q[k].r]) continue;
						if(dfn[blk[q[k].l]+1]>dfn[blk[q[k].r]-1])
							Add_query(blk[q[k].l]+1,blk[q[k].r]-1,q[k].id);
						else Add_query(blk[q[k].r]-1,blk[q[k].l]+1,q[k].id);
					}
				}
				if(j*j!=i&&i/j>S1){
					for(re int k=L[i/j];k<=R[i/j];k++){
						if(blk[q[k].l]==blk[q[k].r]) continue;
						ans[q[k].id]=min(ans[q[k].id],suf[q[k].l]-i);
						ans[q[k].id]=min(ans[q[k].id],pr[q[k].r]-i);
						if(blk[q[k].l]+1==blk[q[k].r]) continue;
						if(dfn[blk[q[k].l]+1]>dfn[blk[q[k].r]-1])
							Add_query(blk[q[k].l]+1,blk[q[k].r]-1,q[k].id);
						else Add_query(blk[q[k].r]-1,blk[q[k].l]+1,q[k].id);
					}
				}
			}
			dfs2(rt);
		}
	}
	
}

void buildtree(int p,int l,int r){
	tree[p].l=l,tree[p].r=r;
	if(l==r) return (void) (tree[p].mn=a[l]);
	int mid=l+r>>1;
	buildtree(p<<1,l,mid); buildtree(p<<1|1,mid+1,r);
	tree[p].mn=min(tree[p<<1].mn,tree[p<<1|1].mn);
}

int qry(int p,int l,int r){
	if(tree[p].l>=l&&tree[p].r<=r) return tree[p].mn;
	int mid=tree[p].l+tree[p].r>>1,ret=INT_MAX;
	if(mid>=l) ret=min(ret,qry(p<<1,l,r));
	if(mid<r) ret=min(ret,qry(p<<1|1,l,r));
	return ret;
}

int main(){
	p1=ibuf,fread(ibuf,1,SZ1,stdin),p2=obuf;
	memset(ans,0x3f,sizeof(ans));
	read(n); read(m);
	for(int i=1;i<=n;i++)
		read(a[i]);
	for(int i=1;i<=m;i++){
		read(q[i].l); read(q[i].r); read(q[i].k);
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	Solve1 :: Init(S1);
	int i;
	for(i=1;i<=m&&q[i].k<=S1;i++)
		ans[q[i].id]=Solve1 :: query(i);
	for(;i<=m;i++){
		if(!L[q[i].k]) L[q[i].k]=i;
		R[q[i].k]=i;
	}
	Solve2 :: Init();
	Solve2 :: query();
	buildtree(1,1,n);
	for(i=1;i<=m;i++)
		ans[q[i].id]=min(ans[q[i].id],qry(1,q[i].l,q[i].r));
	for(i=1;i<=m;i++) write(ans[i]);
	fwrite(obuf,1,p2-obuf,stdout);
	return 0;
}
```

---

