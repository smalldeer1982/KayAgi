# Ann and Books

## 题目描述

In Ann's favorite book shop are as many as $ n $ books on math and economics. Books are numbered from $ 1 $ to $ n $ . Each of them contains non-negative number of problems.

Today there is a sale: any subsegment of a segment from $ l $ to $ r $ can be bought at a fixed price.

Ann decided that she wants to buy such non-empty subsegment that the sale operates on it and the number of math problems is greater than the number of economics problems exactly by $ k $ . Note that $ k $ may be positive, negative or zero.

Unfortunately, Ann is not sure on which segment the sale operates, but she has $ q $ assumptions. For each of them she wants to know the number of options to buy a subsegment satisfying the condition (because the time she spends on choosing depends on that).

Currently Ann is too busy solving other problems, she asks you for help. For each her assumption determine the number of subsegments of the given segment such that the number of math problems is greaten than the number of economics problems on that subsegment exactly by $ k $ .

## 说明/提示

In the first sample Ann can buy subsegments $ [1;1],[2;2],[3;3],[2;4] $ if they fall into the sales segment, because the number of math problems is greater by $ 1 $ on them that the number of economics problems. So we should count for each assumption the number of these subsegments that are subsegments of the given segment.

Segments $ [1;1] $ and $ [2;2] $ are subsegments of $ [1;2] $ .

Segments $ [1;1],[2;2] $ and $ [3;3] $ are subsegments of $ [1;3] $ .

Segments $ [1;1],[2;2],[3;3],[2;4] $ are subsegments of $ [1;4] $ .

Segment $ [3;3] $ is subsegment of $ [3;4] $ .

## 样例 #1

### 输入

```
4 1
1 1 1 2
1 1 1 1
4
1 2
1 3
1 4
3 4
```

### 输出

```
2
3
4
1
```

## 样例 #2

### 输入

```
4 0
1 2 1 2
0 0 0 0
1
1 4
```

### 输出

```
10
```

# 题解

## 作者：Prean (赞：16)

# 题目大意

有一个序列，每个位置上有 1 或 2 两种元素若干，每次询问一个区间，求这个区间有多少个子区间满足 1 类元素恰好比 2 类元素多 $ k $ 个。
# 莫队
要是看到很难维护的东西，又允许离线，多半就是莫队。（雾）

来看看一个区间在满足条件的情况有啥可以用到的东西：
$$ s1[R] - s1[L-1] = s2[R] - S2[L-1] + k$$
$ s1[i] $ 表示从 $ 1 $ 到 $ i $ 有多少个一类元素，$ s2 $ 同理。

移项：
$$ (s1[R]-s2[R])=(s1[L-1]-s2[L-1])+k $$
转化成了这样一个问题：
$$ \sum_{i=L-1}^{R-1}\sum_{j=i+1}^R[val[j]=val[i]+k] $$
其中 $ val[i] $ 表示 $ s1[i] - s2[i] $。

首先我们在莫队的过程中维护一个桶，表示目前区间中有多少个 $ val[i] $。

在莫队的转移过程中，我们得考虑新加入的元素是在左侧还是在右侧。

如果在左侧，$ ans+=Bucket[val[i]+k] $（因为区间的右侧要比自己大）；如果在右侧，则 $ ans+=Bucket[val[i]-k] $。

关于如何维护桶，离散化就行了。

记得离散化的数组不仅要加入 $ val[i],val[i]+k $ 和 $ val[i]-k $，还要加入 $ 0,k $ 和 $ -k $。（因为 $ val[0]=0 $)

code:
```cpp
#include<algorithm>
#include<cstdio>
#include<cmath>
const int M=1e5+5;
typedef long long ll;
int len;ll lsh[M*3];
int n,m,k,p,t[M],v[M],nxt[M],pre[M];ll CB[M*3];ll now,val[M],ans[M];
struct Query{
	int L,R,p,id;
	inline bool operator<(const Query&it)const{
		return p==it.p?p&1?R<it.R:R>it.R:L<it.L;
	}
}q[M];
inline void Add(const int&id,const int&to){
	now+=CB[to];++CB[v[id]];
}
inline void Del(const int&id,const int&to){
	--CB[v[id]];now-=CB[to];
}
signed main(){
	register int i,L=1,R=0;
	scanf("%d%d",&n,&k);lsh[++len]=0;lsh[++len]=k;lsh[++len]=-k;
	for(i=1;i<=n;++i)scanf("%d",t+i);
	for(i=1;i<=n;++i){
		scanf("%lld",val+i);
		if(t[i]==1)val[i]=val[i-1]+val[i];
		else val[i]=val[i-1]-val[i];
		lsh[++len]=val[i];lsh[++len]=val[i]-k;lsh[++len]=val[i]+k;
	}
	std::sort(lsh+1,lsh+len+1);len=std::unique(lsh+1,lsh+len+1)-lsh-1;
	for(i=0;i<=n;++i){
		v[i]=std::lower_bound(lsh+1,lsh+len+1,val[i])-lsh;
		pre[i]=std::lower_bound(lsh+1,lsh+len+1,val[i]-k)-lsh;
		nxt[i]=std::lower_bound(lsh+1,lsh+len+1,val[i]+k)-lsh;
	}
	scanf("%d",&m);p=ceil(n/sqrt(m*2.0/3));
	for(i=1;i<=m;++i){
		scanf("%d%d",&q[i].L,&q[i].R);--q[i].L;
		q[i].id=i;q[i].p=q[i].L/p;
	}
	std::sort(q+1,q+m+1);
	for(i=1;i<=m;++i){
		const int&QL=q[i].L,&QR=q[i].R;
		while(R<QR)++R,Add(R,pre[R]);
		while(L>QL)--L,Add(L,nxt[L]);
		while(L<QL)Del(L,nxt[L]),++L;
		while(R>QR)Del(R,pre[R]),--R;
		ans[q[i].id]=now;
	}
	for(i=1;i<=m;++i)printf("%lld\n",ans[i]);
}
```

---

## 作者：dead_X (赞：8)

## 思路
显然我们可以记录前缀和，即前 $i$ 本书中 $1$ 问题的数量减 $2$ 问题的数量。

于是找区间被我们转化成找两个**相差为 $k$，顺序指定**的数点对问题。

一看到这个模型可以莫队就直接上莫队。

考虑一个区间最后的数的贡献，设这个数为 $s$，则它的贡献就是其余数中 $s-k$ 出现的次数，第一个数同理，于是我们可以直接暴力用 ``unordered_map`` 维护出现次数。

时间复杂度 $O(n\sqrt n\times\text{A\ large number})$，原因是 ``unordered_map`` 的常数太大了……

于是它 $\color{blue}\mathsf{TL\ on\ 11}$ 了。
## 优化 $1$
显然不同的前缀和只有 $n$ 个，因此我们要统计的出现次数 $s\pm k$ 只有 $2n$ 个，于是只统计这些出现次数即可。
## 优化 $2$
优化 $1$ 有亿点麻烦，我们考虑卡常。

1. 快速输入输出，``fread``：由于输入达到 $3\times 10^5$，已经可以使用 ``fread`` 优化。
2. 高级吸氧：玄学，但是莫队吸氧能更快是事实。
3. 奇偶排序：减少移动次数，但是不知道为什么我的代码用了就 WA 了……
4. 更换哈希表：``gp_hash_table`` 更快。
5. 使用 C++17(64)：寻址更快。

## 代码
1918ms。
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
void print(long long x) {
    if(x>9) print(x/10);
    *O++=x%10+'0';
}
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
//unordered_map<long long,int> mp;
//unordered map is rubbish!
gp_hash_table<long long,int> mp; 
long long sum[100003],ans[100003];
int t[100003];
struct node
{
	int l,r,bl,id;
	bool operator<(const node&t)const{return bl<t.bl||(bl==t.bl&&r<t.r);}
}q[100003];
int n=read();
long long k=read();
signed main()
{	
	for(int i=1; i<=n; ++i) t[i]=read();
	for(int i=1; i<=n; ++i) sum[i]=sum[i-1]+read()*(t[i]==1?1:-1);
	int m=read(),B=400;
	for(int i=1; i<=m; ++i) q[i].l=read()-1,q[i].r=read(),q[i].bl=q[i].l/B,q[i].id=i;
	sort(q+1,q+m+1);
	long long cur=0;	
	for(int i=1,l=1,r=0; i<=m; ++i)
	{
		while(r<q[i].r) cur+=mp[sum[++r]-k],++mp[sum[r]];
		while(l>q[i].l) cur+=mp[sum[--l]+k],++mp[sum[l]];
		while(r>q[i].r) --mp[sum[r]],cur-=mp[sum[r--]-k];
		while(l<q[i].l) --mp[sum[l]],cur-=mp[sum[l++]+k];
		ans[q[i].id]=cur;
	}
	for(int i=1; i<=m; ++i) print(ans[i]),*O++='\n';
	fwrite(obuf,O-obuf,1,stdout);
	return 0;
}
```

---

## 作者：b6e0_ (赞：6)

[题目在这](https://www.luogu.com.cn/problem/CF877F)

**至少我发这篇题解时，第一次运行时间 rank1！**

为什么没人用离散化啊。

首先，我们对序列做 $1$ 类问题个数减 $2$ 类问题的前缀和，将子区间问题个数转化成前缀和相减。记 $i$ 的前缀和为 $s_i$。

然后就是莫队了。在将右端点 $R$ 增加一时，在区间 $[L-1,R]$ 中查询有多少个前缀和为 $s_R-k$，其他同理。

在处理排序过的询问前，对 $s_i$ 做离散化，并预处理 $s_i\pm k$ 离散化后的数是多少。时间复杂度 $\mathcal O(n\sqrt n)$，具体细节看代码：
```cpp
#include<bits/stdc++.h>
using namepace std;
const int bs=316;
struct query
{
	int l,r,id;
}q[100010];
bool a[100010];
long long b[100010],s[100010],c[100010],buc[100010],out[100010];//s为前缀和，c为离散化数组，buc为桶，out为答案，记得开long long
int uk[100010],dk[100010];//s[i]+k和s[i]-k离散化后的数
inline int read()//快读
{
	char c=getchar();
	int x=0,y=1;
	while(c<'0'||c>'9')
	{
		if(c=='-')
			y=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return x*y;
}
inline void write(long long x)//快写
{
	if(!x)
	{
		putchar('0');
		putchar('\n');
		return;
	}
	int sta[20],tp=0;
	while(x)
	{
		sta[++tp]=x%10;
		x/=10;
	}
	while(tp)
		putchar(sta[tp--]+'0');
	putchar('\n');
}
bool cmp(query x,query y)
{
	if(x.l/bs!=y.l/bs)
		return x.l<y.l;
	if((x.l/bs)&1)
		return x.r<y.r;
	return x.r>y.r;
}
int main()
{
	int n=read(),k=read(),Q,m=0,i,L=1,R=0;
	long long ans=0;
	for(i=1;i<=n;i++)
		a[i]=read()-1;//-1，转成bool
	for(i=1;i<=n;i++)
	{
		b[i]=read();
		if(a[i])
			s[i]=s[i-1]-b[i];
		else
			s[i]=s[i-1]+b[i];
		c[i]=s[i];
	}
	Q=read();
	for(i=1;i<=Q;i++)
	{
		q[i].l=read();
		q[i].r=read();
		q[i].id=i;
	}
	sort(q+1,q+Q+1,cmp);
	sort(c,c+n+1);//这里要把c[0]也离散化进去
	m=unique(c,c+n+1)-c;
	for(i=0;i<=n;i++)
	{
		uk[i]=lower_bound(c,c+m,s[i]+k)-c;
		if(uk[i]<=n&&c[uk[i]]!=s[i]+k)
			uk[i]=-1;
		dk[i]=lower_bound(c,c+m,s[i]-k)-c;
		if(c[dk[i]]!=s[i]-k)
			dk[i]=-1;
		s[i]=lower_bound(c,c+m,s[i])-c;//一定要先找s[i]+k和s[i]-k再找s[i]
	}
	for(i=1;i<=Q;i++)
	{
		while(R<q[i].r)
		{
			R++;
			buc[s[L-1]]++;//避免特判，先将s[L-1]加进桶，一会后再删去
			if(dk[R]!=-1)
				ans+=buc[dk[R]];
			buc[s[L-1]]--;
			buc[s[R]]++;
		}
		while(R>q[i].r)
		{
			buc[s[R]]--;
			buc[s[L-1]]++;
			if(dk[R]!=-1)
				ans-=buc[dk[R]];
			buc[s[L-1]]--;
			R--;
		}
		while(L>q[i].l)
		{
			L--;
			buc[s[L]]++;
			if(uk[L-1]!=-1)
				ans+=buc[uk[L-1]];
		}
		while(L<q[i].l)
		{
			if(uk[L-1]!=-1)
				ans-=buc[uk[L-1]];
			buc[s[L]]--;
			L++;
		}
		out[q[i].id]=ans;
	}
	for(i=1;i<=Q;i++)
		write(out[i]);
	return 0;
}
```

---

## 作者：Mars_Dingdang (赞：5)

一道莫队+离散化+前缀和维护的好题，是一类题目的模板。

## 题目大意
商店里有 $n$ 本书，每本书中有 $a_i$ 个 $t_i=\{1,2\}$ 类问题。

有 $q$ 次询问，每次询问给出一个区间，求有多少个符合下列条件的区间:

- 这个区间是给出区间的子区间;

- 这个区间的所有书中第 $1$ 类问题比第 $2$ 类问题多 $k$ 个，其中 $k$ 在所有询问中相同。

## 大体思路
看到区间和，考虑将区间和转换为前缀和。由于题目求满足“第 $1$ 类问题比第 $2$ 类问题多 $k$ 个”，所以记 $sum_i$ 表示前 $i$ 本书第 $1$ 类问题比第 $2$ 类问题多的个数。

其计算公式如下：

$$sum_i=\begin{cases}sum_{i-1}+a_i,\ t_i=1\\sum_{i-1}-a_i,\ t_i=2\end{cases}$$

然后考虑莫队。令左右指针为 $L,R$。

1. 当 $L-1$，即向左插入时，答案新增的是 $[L,i\in (L,R]]$ 部分的贡献，因此求 $sum_i-sum_{L-1}=k(i\in [L,R])$ 的数量，即区间中 $sum_{L-1}+k$ 的数量（这可以用 $cnt$ 数组维护，即莫队基本思想）。删除同理。

2. 当 $R+1$，即向右插入时，答案新增的是 $[i\in [L,R),R]$ 的贡献，求 $sum_R-sum_i=k(i\in [L-1,R-1])$ 的数量，即区间 $[L-1,R-1]$ 中 $sum_R-k$ 的数量。所以先加入 $L-1$ 的贡献，再计算，再撤销 $L-1$ 的贡献，最后加上 $R$ 的贡献。删除同理。

由此可见，我们需要维护三个值 $sum,sum+k,sum-k$，而值域为 $10^9$，所以对上述三个值进行离散化。注意：若 $sum+k,sum-k$ 不存在，令其等于 $-1$，并在莫队更新区间时特判。

$n,m$ 同阶，总复杂度仍然为 $O(n\sqrt n)$ 级别。

## 完整代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5, B = 224;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
ll n, k, m, len, L, R;
ll a[maxn], sum[maxn], c[maxn], cnt[maxn], Ans[maxn], ans, id[maxn];
ll ak[maxn], mk[maxn];//addk, minus k
bool t[maxn];
struct node{
	int l, r, pos;
	bool operator <(const node &x)const{
		if(id[l] != id[x.l]) return l < x.l;
		if(id[l] & 1) return r < x.r;
		return r > x.r;
	}
} q[maxn];
int main () {
	read(n); read(k);
	rep(i, 1, n) {
		int x; read(x);
		t[i] = (x == 2);
		id[i] = (i - 1) / B + 1;
	}
	rep(i, 1, n) {
		read(a[i]);// 输入 
		if(t[i]) sum[i] = sum[i - 1] - a[i];
		else sum[i] = sum[i - 1] + a[i];
		c[i] = sum[i];//预处理前缀和 
	}
	c[n+1] = k, c[n+2] = -k; n += 2;
	sort(c, c + n + 1);
	len = unique(c, c + n + 1) - c;
	rep(i, 0, n) {
		ak[i] = lower_bound(c, c + len, sum[i] + k) - c;
		if(ak[i] <= n && c[ak[i]] != sum[i] + k) ak[i] = -1;
		mk[i] = lower_bound(c, c + len, sum[i] - k) - c;
		if(c[mk[i]] != sum[i] - k) mk[i] = -1;
		sum[i] = lower_bound(c, c + len, sum[i]) - c;
	}//离散化
	
	read(m);
	rep(i, 1, m) {
		read(q[i].l); read(q[i].r);
		q[i].pos = i;
	} 
	sort(q + 1, q + m + 1);
	L = 1, R = 0;
	rep(i, 1, m) {
		while(L < q[i].l) {
			if(ak[L - 1] != -1) ans -= cnt[ak[L - 1]];
			cnt[sum[L]]--; L++;
 		} while(R > q[i].r) {
			cnt[sum[R]]--; cnt[sum[L - 1]]++;
			if(mk[R] != -1) ans -= cnt[mk[R]];
			cnt[sum[L - 1]]--;
			R--;
		} while(L > q[i].l) {
			L--; cnt[sum[L]]++;
			if(ak[L - 1] != -1) ans += cnt[ak[L - 1]];
		} while(R < q[i].r) {
			R++; cnt[sum[L - 1]]++;
			if(mk[R] != -1) ans += cnt[mk[R]];
			cnt[sum[L - 1]]--;
			cnt[sum[R]]++;
		}
 		Ans[q[i].pos] = ans;
	}
	rep(i, 1, m) writeln(Ans[i]);
	return 0;
}
```

## 后记
关于莫队块长选择，假设块长为 $B$，共有 $\dfrac n B$ 块。由于同一个块一起处理，左端点移动距离单次 $\le B$，总距离 $\le m\cdot B$。

关于右端点移动距离，以询问 $[x, y]$ 时 $x$ 为横轴，$y$ 为纵轴建立坐标系，发现所有询问对应的点都在 $y=x$ 上方，因此右端点移动距离是 $n+(n-B)+(n-2B)+\cdots=\dfrac{n^2}{2B}$。

总移动距离为 $mB+\dfrac{n^2}{2B}$，由基本不等式解得 $mB=\dfrac{n^2}{2B}$，$B=\dfrac{n}{\sqrt{2m}}$ 时最小。

所以，莫队最优块长是 $\dfrac{n}{\sqrt{2m}}$ 而非 $\sqrt n$。

---

## 作者：Eon_Sky (赞：4)

## 莫队做法。

顺便推荐一个很好的题单，目前正在刷：[$\texttt{Link}$](https://www.luogu.com.cn/training/38213)

------------

看完题首先考虑用前缀和简化问题，$pre_i$ 表示前 $i$ 个书中问题 $1$ 减问题 $2$ 的个数，这样我们只要找在区间内且相差为 $k$ 的两点的对数即可。

我们接着考虑区间中一个数 $x$ 的贡献，显然是 $x-k$ 或 $x+k$（如果 $x$ 以右端点出现就是 $x-k$ ，左端点就是 $x+k$）。于是我们只要维护 $x-k$ 或 $x+k$ 出现次数即可，离散化方法可以直接用 map。

莫队的两个操作就不说了，上面解释的应该够了，可以看代码。

[结果在 $\#11$ T掉了](https://www.luogu.com.cn/record/46873024)

为了卡常我进行了以下优化：
1. 快读
2. map 换成 gp_hash_table
3. 火车头
4. 奇偶排序

于是过了，AC 代码：

```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

const int N=1e5+1;

struct Que//询问
{
	int id;
	int l,r;
}que[N];
int n,q,k;
int a[N],t[N];

int len;//分块长度
int p[N];//分块，每个位置都在哪个块

gp_hash_table<long long,int>mp;//map
int l=1,r; 
long long pre[N];//前缀和
long long ans[N];//答案
long long res;//维护的

inline int read()//快读
{
	int X=0; bool flag=1; char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') flag=0; ch=getchar();}
	while(ch>='0'&&ch<='9') {X=(X<<1)+(X<<3)+ch-'0'; ch=getchar();}
	if(flag) return X;
	return ~(X-1);
}

bool cmp(Que x,Que y)//奇偶排序
{
	return (p[x.l]^p[y.l])?p[x.l]<p[y.l]:((p[x.l]&1)? x.r<y.r:x.r>y.r);
}

inline void add(int x,bool t)
{
	int y=k;
	if(t)
		y=-y;//左端点和右端点区别对待（
	res+=mp[pre[x]+y];//加答案
	++mp[pre[x]];//更新
	return;
}

inline void del(int x,bool t)
{
	int y=k;
	if(t)
		y=-y;//同上
	--mp[pre[x]];//更新
	res-=mp[pre[x]+y];//减去
	return;
}

int main()
{
	n=read();//读入
	k=read();
	len=sqrt(n);
	for(int i=1;i<=n;++i)
	{
		t[i]=read();
		p[i]=(i-1)/len+1;
	}
	for(int i=1;i<=n;++i)
	{
		a[i]=read();
		pre[i]=pre[i-1]+a[i]*(t[i]==1?1:-1);//前缀和
	}
	q=read();
	for(int i=1;i<=q;++i)
	{
		que[i].l=read(),que[i].r=read();
		que[i].l--;
		que[i].id=i;
	}
	sort(que+1,que+1+q,cmp);

	for(int i=1;i<=q;++i)//主要部分
	{
		while(que[i].l<l)
			add(--l,false);//注意区分左右端点
		while(que[i].r>r)
			add(++r,true);
		while(que[i].l>l)
			del(l++,false);
		while(que[i].r<r)
			del(r--,true);
		ans[que[i].id]=res;
	}
	
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);//输出
	return 0;
}
```


---

## 作者：SilverLi (赞：2)

> [Ann and Books の 传送门](https://www.luogu.com.cn/problem/CF877F)

> [戳一戳](https://www.cnblogs.com/Silver-Wolf/p/18701810/CF877F)

$s_i=\sum_{j=1}^i a_j \left [ t_j=1 \right ], t_i=\sum_{j=1}^i a_j \left [ t_j=2 \right ]$。

满足条件的区间可以表示为 $\left [ l, r \right ]$，满足 $s_r-s_{l-1}>t_r-t_{l-1}+k$。

移一移项，$s_r-t_r>s_{l-1}-t_{l-1}+k$。

令 $val_i=s_i-t_i$，化简为 $val_r>val_{l-1}+k$。

然后用**莫队**~~就做完了~~。

具体一点，存下当前区间所有的 $val_i$。

1. 在右侧插入，答案加上 $val_{now}-k$ 的出现次数，再**特判它本身**。

2. 在左侧插入，答案加上 $val_{now}+k$ 的出现次数，再**特判它本身**。

~~删除就是把插入的代码倒着写一遍。~~


```cpp
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define int long long
using namespace std;
inline int read()
{
    int f = 0, ans = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        ans = (ans << 3) + (ans << 1) + c - 48, c = getchar();
    return f ? -ans : ans;
}
void write(int x)
{
    if (x < 0)
        putchar('-'), x = -x;
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
const int N = 2e5 + 5, M = N * 3;
int n, k, m, t[N], a[N];
int cnt, s1[N], s2[N], val[N];
int sq, mp[M], b[M], id[N][3];
int ans, res[N];
struct que
{
    int l, r, id;
    bool operator<(const que &x) const
    {
        if (l / sq != x.l / sq)
            return l < x.l;
        return l / sq & 1 ? r < x.r : r > x.r;
    }
} q[N];
inline int get(int x) { return lower_bound(b + 1, b + cnt + 1, x) - b; }
inline void ins_l(int i) { ++mp[id[i][0]], ans += mp[id[i - 1][2]]; }
inline void ins_r(int i, int l) { ans += mp[id[i][1]] + (val[i] == val[l - 1] + k), ++mp[id[i][0]]; }
inline void del_l(int i) { ans -= mp[id[i - 1][2]], --mp[id[i][0]]; }
inline void del_r(int i, int l) { --mp[id[i][0]], ans -= mp[id[i][1]] + (val[i] == val[l - 1] + k); }
signed main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    n = read(), k = read();
    sq = sqrt(n);
    for (int i = 1; i <= n; ++i)
        t[i] = read();
    b[++cnt] = val[0];
    b[++cnt] = val[0] - k;
    b[++cnt] = val[0] + k;
    for (int i = 1; i <= n; ++i)
    {
        a[i] = read();
        s1[i] = s1[i - 1] + a[i] * (t[i] == 1);
        s2[i] = s2[i - 1] + a[i] * (t[i] == 2);
        val[i] = s1[i] - s2[i];
        b[++cnt] = val[i];
        b[++cnt] = val[i] - k;
        b[++cnt] = val[i] + k;
    }
    sort(b + 1, b + cnt + 1);
    cnt = unique(b + 1, b + cnt + 1) - b - 1;
    for (int i = 0; i <= n; ++i)
        id[i][0] = get(val[i]), id[i][1] = get(val[i] - k), id[i][2] = get(val[i] + k);
    m = read();
    for (int i = 1; i <= m; ++i)
        q[i].l = read(), q[i].r = read(), q[i].id = i;
    sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i)
    {
        while (l > q[i].l)
            ins_l(--l);
        while (r < q[i].r)
            ins_r(++r, l);
        while (l < q[i].l)
            del_l(l++);
        while (r > q[i].r)
            del_r(r--, l);
        res[q[i].id] = ans;
    }
    for (int i = 1; i <= m; ++i)
        write(res[i]), putchar('\n');
    return 0;
}
```

---

## 作者：_anll_ (赞：2)

## 大体思路
对于这种离线的区间询问，很显然可以联想到莫队。而在莫队中问你大区间内有多少个子区间满足条件的题一般都会用前缀数组进行维护，把枚举区间转换为枚举点（类似的题目：[P4462](https://www.luogu.com.cn/problem/P4462)），然后再拿莫队板子去套就可以解决了。

下文中的某些数组可能会出现与代码中的数组不同名的情况。

我们拿前缀和数组进行维护，令 $qzh1$ 维护 $1$ 的出现次数，$qzh2$ 维护 $2$ 的出现次数。于是对于区间 $\{l,r\}$ 而言，出现过的 $1$ 为 $qzh1_r-qzh1_{l-1}$，出现过的 $2$ 为 $qzh2_r-qzh2_{l-1}$。对于 $r$ 而言，$l$ 符合条件当且仅当 
$$
(qzh1_r-qzh_{l-1})-(qzh2_r-qzh2_{l-1})=k
$$
发现 $qzh1_i-qzh2_i$ 出现过两次，引导我们可以再开一个数组 $qzh$，对于 $i$，可以再拿一个数组 $qzh_i=qzh1_i-qzh2_i$。于是条件就变成了
$$
qzh_r-qzh_{l-1}=k
$$
移项整理为
$$
qzh_r-k=qzh_{l-1}
$$
因为我们要转换为枚举点的问题，以右端点为例，我们希望枚举它时可以得到对应的左端点的次数。很容易想到再拿一个数组 $cnt$ 记录每个数出现的次数，每次枚举右端点时让 $ans = ans\pm cnt_{qzh_r-k}$，同理，对于每个左端点，我们让 $ans= ans \pm cnt_{qzh{l-1}+k}$ 就好了。

由于 $k$ 达到了惊人的 $10^9$，我们需要使用 `unordered_map`。~~于是你就会发现 TL on 11 了。~~ 这个时候有两种选择：

- 进行离散化
- 进行卡常

我比较菜，学离散化的时候学的不是很好，所以这里用的是我们的卡常大法。卡常的地方和一些需要注意的细节一并在代码中写了注释，在这里就不赘述了。

然后这道题就可以通过了。

## 代码演示
大体思路就是这样，如果有不清晰的地方可以结合代码和注释理解。
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
//卡常火车头 
#define int long long
using namespace __gnu_pbds;
using namespace std;
struct Que{
    int l,r,id;
}que[100005];
int n,k,q,bl,ans,qzhh[100005][3],qzh[100005],anu[100005];
int tt[100005],aa[100005];
gp_hash_table<int,int> cnt; //更换hash表为gp_hash_table
inline int read(){//快读 
   	int s=0,w=1;
   	char ch=getchar();
   	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   	return s*w;
}
bool cmp(Que a,Que b){
    if(a.l/bl!=b.l/bl) return a.l<b.l;
    if(a.l/bl&1) return a.r<b.r;
    return a.r>b.r;
}
void add(int x,int awa){
    if(awa) ans+=cnt[qzh[x]-k];
    if(!awa) ans+=cnt[qzh[x]+k];
    cnt[qzh[x]]+=1;//要先改后加 否则当k=0的时候会多算 
}
void del(int x,int awa){
	cnt[qzh[x]]-=1;//要先加后改 否则当k=0的时候会多算 
    if(!awa) ans-=cnt[qzh[x]+k];
    if(awa) ans-=cnt[qzh[x]-k];
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    n=read();k=read();
    for(int i=1;i<=n;i++) tt[i]=read();
    for(int i=1;i<=n;i++) aa[i]=read();
    q=read();
    for(int i=1;i<=q;i++){que[i].l=read();que[i].r=read();que[i].id=i;}
    bl=sqrt(n);
    sort(que+1,que+1+q,cmp);
    for(int i=1;i<=n;i++){
        qzhh[i][1]=qzhh[i-1][1],qzhh[i][2]=qzhh[i-1][2];
        qzhh[i][tt[i]]+=aa[i];
    }
    for(int i=1;i<=n;i++) qzh[i]=qzhh[i][1]-qzhh[i][2];
    
    int l=1,r=0;
    for(int i=1;i<=q;i++){
        int ql=que[i].l,qr=que[i].r,id=que[i].id;
        while(l>ql-1) add(--l,0);
        while(l<ql-1) del(l++,0);
        while(r<qr) add(++r,1);
        while(r>qr) del(r--,1);
        anu[id]=ans;
    }
    for(int i=1;i<=q;i++) cout<<anu[i]<<endl;
    return 0;
}
```



---

## 作者：CQ_Bab (赞：2)

# 思路
我们可以用一个数组存下前 $i$ 个数中 $1$ 的次数比 $2$ 的次数多多少，然后我们就可以用前缀和相减的方式来表示出 $k$ 了，那么我们这里需要进行分类讨论。

- 如果是右端点，那么我们就可以对于 $cnt_{sum_{i}-k}$ 进行加减，毕竟这里一定是要他减去前面的某个数等于 $k$ 时才能行，毕竟当自己为减数时会被用后面的数相加上。
- 如果是左端点，我们就可以对于 $cnt_{sum_{i}+k}$ 进行加减即可，这里也和上面同理。

但是，由于这道题 $0\leq a_i\leq 10^9$ 那么我们可以进行离散化或者直接用 map 来存储，但是由于 map 的常数过大，所以我们可以进行卡常即可，否则会被第十一个点卡掉。
# 代码
```cpp
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <bits/stdc++.h>
#define ri int
#define il inline
#define pai(a,x,y) sort(a+x,a+y+1)
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std ;
inline void read(int &x) {
	x=false;
	ri f=1;
	char c=getchar();
	while(c>'9'||c<'0') {
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c-'0'<=9&&c>='0') {
		x=x*10+c-'0';
		c=getchar();
	}
	x*=f;
}
int n,k;
const int N=1e5+4;
int t[N],a;
long long sum[N];
int q,len;
struct node {
	int l,r,id;
} s[N];
gp_hash_table<long long,int>mp;
int p[N];
inline bool cmp(node x,node y) {
	return (p[x.l]^p[y.l])?p[x.l]<p[y.l]:((p[x.l]&1)? x.r<y.r:x.r>y.r);
}
long long res;
il void pplus(int i,int f) {
	res+=mp[sum[i]+k*f];//分类讨论
	mp[sum[i]]++;
}
il void del(int i,int ff) {
	mp[sum[i]]--;
	res-=mp[sum[i]+k*ff]; //分类讨论
}
long long ans[N];
int main() {
	read(n);
	read(k);
	len=sqrt(n);
	for(ri i=1; i<=n; i++) read(t[i]);
	for(ri i=1; i<=n; i++) {
		read(a);
		p[i]=(i-1)/len+1;
		if(t[i]==1) sum[i]=sum[i-1]+a; //前缀和
		else sum[i]=sum[i-1]-a;
	}
	read(q);
	for(ri i=1; i<=q; ++i) {
		read(s[i].l);
		s[i].l--;
		read(s[i].r);
		s[i].id=i;
	}
	sort(s+1,s+1+q,cmp);
	int l=1,r=false;
	for(ri i=1; i<=q; ++i) {
		while(l>s[i].l) pplus(--l,1); //模板
		while(r<s[i].r) pplus(++r,-1);
		while(l<s[i].l) del(l++,1);
		while(r>s[i].r) del(r--,-1);
		ans[s[i].id]=res;
	}
	for(ri i=1; i<=q; i++) printf("%lld\n",ans[i]);
	return false;
}
```

---

## 作者：EC75 (赞：1)

### 难度

话说这道题是省选难度。

### 思路

如果第 $i$ 本书是经济学的，$a_i=-a_i$。现在的问题是计算 $\sum k$ 的结果。

首先，我们计算前缀总和：算式为 $p_j=\sum _{i=1}^{j}$，又有 $\sum _{i=l}^{r}=p_i-p_{l-1}$。

现在我们就可以在 $O(n×q×\log(n))$ 的时间复杂度中解决掉它了。我们将沿着分段计算 $cnt_i-i$ 在分段中出现的次数。然后我们将添加 $cnt_{p_{i}-k}$ 来回答。$p_i$ 可能足够大，我们应当使用类似于 map 的东西。

我们可以轻松地将两个边框向左和向右移动。然后我们可以在 $O\left( q\times \sqrt{n}\times \log n\right)$ 中解决问题。不幸的是，它仍然太慢了。

我们必须压缩。计算 $v_i-p_i$ 的压缩值、$l_i-p_i-k$ 的压缩值，以及，$r_i-p_i+k$ 的压缩值即可得出中正确答案。

### 代码

~~我知道你就是来看这个的……~~

```python
import os
import sys
from io import BytesIO, IOBase
BUFSIZE = 8192
class FastIO(IOBase):
    newlines = 0
    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None
    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()
    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()
    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)
class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")
sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")
from math import ceil
def prod(a, mod=10 ** 9 + 7):
    ans = 1
    for each in a:
        ans = (ans * each) % mod
    return ans
def gcd(x, y):
    while y:
        x, y = y, x % y
    return x
def lcm(a, b): return a * b // gcd(a, b)
def binary(x, length=16):
    y = bin(x)[2:]
    return y if len(y) >= length else "0" * (length - len(y)) + y
for _ in range(int(input()) if not True else 1):
    n, k = map(int, input().split())
    t = list(map(int, input().split()))
    a = list(map(int, input().split()))
    for i in range(n):
        # math = eco + k
        # math - eco = k
        if t[i] == 2:
            a[i] *= -1
    count = [0] * (n + 1)
    pre = [0]
    for i in a:
        pre += [pre[-1] + i]
    index = {}
    cc = list(set(pre))
    for i in range(len(cc)):
        index[cc[i]] = i
    minusK = [-1]*(n + 1)
    plusK = [-1] * (n + 1)
    zero = [-1] * (n + 1)
    for i in range(n + 1):
        if pre[i] - k in index:
            minusK[i] = index[pre[i] - k]
        if pre[i] + k in index:
            plusK[i] = index[pre[i] + k]
        zero[i] = index[pre[i]]
    BLOCK_SIZE = 320
    blocks = [[] for i in range(BLOCK_SIZE)]
    q = int(input())
    ans = [0]*q
    for i in range(q):
        l, r = map(int, input().split())
        blocks[l // BLOCK_SIZE] += [[l-1, r, i]]
    for i in range(len(blocks)):
        if not blocks[i]: continue
        blocks[i] = sorted(blocks[i], key=lambda x: x[1])
        left = right = BLOCK_SIZE * i
        res = 0
        count[zero[left]] += 1
        for l, r, ind in blocks[i]:
            while right < r:
                right += 1
                if minusK[right] != -1:
                    res += count[minusK[right]]
                count[zero[right]] += 1
            while left < l:
                count[zero[left]] -= 1
                if plusK[left] != -1:
                    res -= count[plusK[left]]
                left += 1
            while left > l:
                left -= 1
                if plusK[left] != -1:
                    res += count[plusK[left]]
                count[zero[left]] += 1
            ans[ind] = res
        while left <= right:
            count[zero[left]] -= 1
            if plusK[left] != -1:
                res -= count[plusK[left]]
            left += 1
        assert res == 0
    for i in ans:
        print(i)
```

---

## 作者：RainFestival (赞：1)

注意到询问可以离线。

假设我们知道 $(l,r)$ 的答案，计算 $(l+1,r)$, $(l,r+1)$，$(l,r-1)$，$(l-1,r)$ 的答案都可以时间复杂度 $O(1)$ 内完成。

于是我们可以使用**莫队**。时间复杂度 $O(n\sqrt n)。$

注意在最开始的时候要离散化一下。时间复杂度 $O(n\log n)$。

总时间复杂度 $O(n\log n)+O(n\sqrt n)=O(n\sqrt n)$。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
struct query
{
	int l,r,id;
};
std::map<long long,int> mp;
int n,q,t[100005],b[100005],g[100005],nxt[100005],pre[100005];
long long k,ss[100005],d[100005],f[100005],ans[100005],s=0;
query a[100005];
int cmp(query x,query y){return b[x.l]!=b[y.l]?b[x.l]<b[y.l]:x.r<y.r;}
void delfst(int x){int p=ss[x],tmp;--g[p];tmp=nxt[p];if (tmp!=-1) s=s-g[tmp];}
void dellst(int x){int p=ss[x],tmp;--g[p];tmp=pre[p];if (tmp!=-1) s=s-g[tmp];}
void addfst(int x){int p=ss[x],tmp;tmp=nxt[p];if (tmp!=-1) s=s+g[tmp];++g[p];}
void addlst(int x){int p=ss[x],tmp;tmp=pre[p];if (tmp!=-1) s=s+g[tmp];++g[p];}
int main()
{
	scanf("%d%lld",&n,&k);
	for (int i=1;i<=n;i++) scanf("%d",&t[i]);
	for (int i=1;i<=n;i++) scanf("%lld",&f[i]);
	for (int i=1;i<=n;i++) if (t[i]==1) ss[i]=ss[i-1]+f[i];else ss[i]=ss[i-1]-f[i];
	for (int i=1;i<=n;i++) d[i]=ss[i];
	std::stable_sort(d+1,d+n+1);
	long long lst=-1;int cnt=0;
	for (int i=0;i<=n;i++) if (d[i]!=lst) mp[d[i]]=++cnt,lst=d[i];
	for (int i=0;i<=n;i++)
	{
		long long x=ss[i];
		int tmp=mp[x];
		pre[tmp]=(mp[x-k]?mp[x-k]:-1);
		nxt[tmp]=(mp[x+k]?mp[x+k]:-1);
		ss[i]=tmp;
    }
	for (int i=0;i<=n;i++) b[i]=i/100;
	scanf("%d",&q);
	for (int i=1;i<=q;i++) scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i,--a[i].l;
	std::stable_sort(a+1,a+q+1,cmp);
	int l=0,r=-1;
	for (int i=1;i<=q;i++)
	{
		int ll=a[i].l,rr=a[i].r,id=a[i].id;
		while (r<rr) addlst(++r);
		while (ll<l) addfst(--l);
		while (l<ll) delfst(l++);
		while (rr<r) dellst(r--);
		ans[id]=s;
	}
	for (int i=1;i<=q;i++) printf("%lld\n",ans[i]);
	return 0;
}
```

总用时 $20.70s$ 在 $13$ 人中排名为 $6$。

---

## 作者：MonKeySort_ZYczc (赞：0)

## 思路流程
可以先去看看 [P4662](https://www.luogu.com.cn/problem/P4462) 与 [P3604](https://www.luogu.com.cn/problem/P3604)，食用效果更佳哦。  
可离线区间询问？那么我猜这题想考察莫队不过分吧。  

我们利用前缀和的思想，设 $a_i$ 为前 $i$ 本书第一种问题比第二种问题多多少。  
注意到区间 $[l,r]$ 两种问题数量之差可表示为 $a_r-a_{l-1}$，这题思路一下明了了：用 $cnt_i$ 存储所有使 $a_k=i$ 的 $k$ 的数量，我们每次右端点变化为 $p$ 时应当加上（或减去）$cnt_{a_p-k}$ 的值，左端点变化为 $p$ 时应当加上（或减去）$cnt_{k-a_p}$ 的值。   
（仔细想想为什么？）  

可是若直接莫队，显然 $10^9$ 数量级就让我们的 $cnt$ 数组十分为难。  
容易想到离散化。  
接下来便是核心了：在离散化的同时，找到 $a_p-k$ 与 $k-a_p$ 在离散化后的实际值，若在序列中就设为 $0$（假设离散化编号从 $1$ 开始，比较方便）。  
[P3604](https://www.luogu.com.cn/problem/P3604) 这题也用到类似的思想，离散化时记录转移需要的数离散化后的值。   

到此，问题应当差不多解决了。  
当然请注意：
- 不知道什么原因，不开那啥竟然会见祖宗。
- 据说不加快读有点难卡过诶！尊嘟假嘟？
- 由于前缀和的原因，询问的区间左端点应当减 $1$ 或采取其他方法避免漏算。这与开头推荐的两道题“一脉相承”。

总时间复杂度：$O(n\sqrt n)$。  
[AC record](https://codeforces.com/problemset/submission/877/315809061) 在这里哦。  
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int n,m,ans[N],q[N],op[N],tot=1,sol[N][2],k;
int l=1,r,now,cnt[N],blo;
map<int,int>mp;
struct que
{
	int l,r,id;
}qe[N];
inline int read()
{
	char c=getchar();int sign=1,a;
	while(c>'9'||c<'0')
	{
		if(c=='-') sign=-1;
		c=getchar();
	}
	a=c-'0';
	while((c=getchar())<='9'&&c>='0') a=(a<<3)+(a<<1)+c-'0';
	return a*sign;
}
bool cmp(que a,que b)
{
	int x=a.l/blo,y=b.l/blo;
	if(x^y) return x<y;
	else
	{
		if(x&1) return a.r<b.r;
		else return a.r>b.r;
	}
}
inline void add(int p,int pd)
{
	now+=cnt[sol[p][pd]],cnt[q[p]]++;
}
inline void del(int p,int pd)
{
	cnt[q[p]]--,now-=cnt[sol[p][pd]];
}
signed main()
{
	n=read();k=read();mp[0]=1;blo=sqrt(n);
	for(int i=1;i<=n;i++) op[i]=read();
	for(int i=1;i<=n;i++)
	{
		q[i]=read();
		q[i]=q[i-1]+q[i]*(op[i]==1?1:-1);
		if(mp.find(q[i])==mp.end()) mp[q[i]]=++tot;
	}
	for(int i=0;i<=n;i++)
	{
		if(mp.find(q[i]-k)!=mp.end()) sol[i][0]=mp[q[i]-k];
		if(mp.find(q[i]+k)!=mp.end()) sol[i][1]=mp[q[i]+k];
		q[i]=mp[q[i]];
	}
	m=read();
	for(int i=1;i<=m;i++)
	{
		qe[i].l=read();qe[i].r=read();qe[i].l--;qe[i].id=i;
	}
	sort(qe+1,qe+m+1,cmp);
	for(int i=1;i<=m;i++)
	{
		while(l>qe[i].l) add(--l,1);
		while(r<qe[i].r) add(++r,0);
		while(l<qe[i].l) del(l++,1);
		while(r>qe[i].r) del(r--,0);
		ans[qe[i].id]=now; 
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<'\n';
 } 
```

---

## 作者：TruchyR (赞：0)

不好维护，且范围允许 $O(n\sqrt{n})$，所以考虑莫队。  

考虑转化问题，设立 $A'$ 数组：  

- 若 $t_i=1$，则 $A'_i=a_i$。  

- 若 $t_i=2$，则 $A'_i=-a_i$。   

问题转化为 $\sum_{i=l}^{r}\sum_{j=i}^{r}[k=\sum_{p=i}^{j} A'_p]$。  

发现 $A'$ 可以前缀和：设 $A_1=A'_1$，$A_i=A_{i+1}+A'_i$。  

问题再次转化为 $\sum_{i=l-1}^{r-1}\sum_{j=i+1}^{r}[k=A_j-A_i]$。  

于是可以上莫队了：

```c++
//此部分代码不能通过本题，仅作为中间过程展示
for(int i=1;i<=m;i++){
	int L=q[i].L,R=q[i].R;
	while(l>L){ans+=cnt[a[--l]+k];cnt[a[l]]++;}
	while(r<R){ans+=cnt[a[++r]-k];cnt[a[r]]++;}
	while(l<L){cnt[a[l]]--;ans-=cnt[a[l++]+k];}
	while(r>R){cnt[a[r]]--;ans-=cnt[a[r--]-k];}
	//调整左端点时，需要寻找右侧的值，所以 +k
	//调整右端点时，需要寻找左侧的值，所以 -k
	res[q[i].id]=ans;
}
```

但是再看一眼数据范围，发现 $-10^9\leq k\leq 10^9$，$0\leq a_i\leq 10^9$。  

考虑将 $A$ 离散化，然后记录上面代码向左向右跳的下标。  

循环以 $0$ 为开始，所以注意要将 $0$ 加入离散化数组。  

代码如下，其中代码中的 $a$ 等价于上文的 $A$：  

```c++
#include<bits/stdc++.h>
#define MX 200005
#define int long long
using namespace std;
int read();
int P,n,m,k,a[MX],b[MX],ans,res[MX],cnt[MX],jmpL[MX],jmpR[MX],l=0,r=-1;
struct eg{int L,R,K,id;}q[MX];
bool cmp(eg X,eg Y){return (X.K^Y.K)?(X.K<Y.K):(X.R<Y.R);}
signed main(){
	n=read();k=read();P=sqrt(n);
	//读入 & 前缀和
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++){m=read();a[i]=(a[i]==1?m:-m);}
	for(int i=1;i<=n;i++){a[i]+=a[i-1];b[i]=a[i];}
	//离散化
	sort(b+1,b+2+n);m=unique(b+1,b+2+n)-b-1;
	for(int i=0;i<=n;i++) a[i]=lower_bound(b+1,b+1+m,a[i])-b;
	//初始化
	for(int i=1;i<=m;i++) jmpL[i]=jmpR[i]=n+2; 
	//记录向左向右跳的下标
	for(int i=1;i<=m;i++){
		int r=lower_bound(b+1,b+1+m,b[i]+k)-b;
		if(b[r]==b[i]+k) jmpR[i]=r,jmpL[r]=i;
	}
	//离线询问
	m=read();for(int i=1;i<=m;i++){
		q[i].L=read()-1;
		q[i].R=read();
		q[i].K=q[i].L/P;
		q[i].id=i;
	}sort(q+1,q+1+m,cmp);
	//处理询问
	for(int i=1;i<=m;i++){
		int L=q[i].L,R=q[i].R;
		while(l>L){ans+=cnt[jmpR[a[--l]]];cnt[a[l]]++;}
		while(r<R){ans+=cnt[jmpL[a[++r]]];cnt[a[r]]++;}
		while(l<L){cnt[a[l]]--;ans-=cnt[jmpR[a[l++]]];}
		while(r>R){cnt[a[r]]--;ans-=cnt[jmpL[a[r--]]];}
		res[q[i].id]=ans;
	}
	for(int i=1;i<=m;i++){printf("%lld\n",res[i]);}
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}
```

---

## 作者：Xttttr (赞：0)

## CF877F 题解

[更好的阅读体验](https://www.cnblogs.com/Xttttr/p/17725161.html)

提供一个扫描线 + 根号分治做法。

首先，可以把题目的条件转化成求 $sum_r-sum_{l-1}=k$ 的区间数。

考虑扫描线，当区间的右端点从 $r-1$ 移动到 $r$ 时，新增的区间的左端点就是所有满足 $sum_{l-1}=sum_r-k,l\le r$ 的 $l$。这时我们对 $sum_{l-1}$ 的出现次数按 $B$ 进行分治。

具体的，如果出现次数 $\le B$ ，那么我们这一次至多会修改 $B$ 个位置，而查询只有一次，于是可以采用 $O(1)-O(\sqrt{n})$ 的分块来维护；如果出现次数 $>B$，这样的数至多有 $\dfrac{n}{B}$ 个，我们可以对每个数都维护一个数据结构，要求支持区间加以及区间和，而每次加的操作只有 $O(1)$ 次，但是每个询问都要对每个数进行查询，共 $\dfrac{n}{B}$ 次，于是可以采用 $O(\sqrt{n})-O(1)$ 的分块（具体可见 [LOJ#6280. 数列分块入门 4](https://loj.ac/p/6280)）。

总复杂度 $O(n\sqrt{n}+q\sqrt{n}+nB+q\dfrac{n}{B})$，$B$ 取 $\sqrt{n}$ 时就可以在 $O(n\sqrt{n}+q\sqrt{n})$ 的复杂度内解决这道题。

```
const int N=100501,B=1000;
int n,k,Q;
int t[N],a[N],tot,bl[N],L[N],R[N];
ll pre[N],ans[N],st[N];
vector<pair<int,int> >qu[N];
map<ll,int>mp;
struct Brick{
    ll sum[N],sumb[N];
    inline void modify(int x){sum[x]++,sumb[bl[x]]++;}
    inline ll query(int l,int r){
        if(bl[l]==bl[r]){
            ll ans=0;
            for(int i=l;i<=r;i++)ans+=sum[i];
            return ans;
        }
        ll ans=0;
        for(int i=l;i<=R[bl[l]];i++)ans+=sum[i];
        for(int i=bl[l]+1;i<bl[r];i++)ans+=sumb[i];
        for(int i=L[bl[r]];i<=r;i++)ans+=sum[i];
        return ans;
    }
}T;
vector<int>hav[N],big;
int id[N],cnt;
struct Bri{
    vector<ll>pre,sum,tag;
    int n;
    inline void init(int m){n=m;pre.resize(n+1),sum.resize(n+1),tag.resize(n+1);}
    inline void add(int x,int k){
        for(int i=x;i<=R[bl[x]];i++)pre[i]+=1ll*k*(i-x+1);
        for(int i=bl[x]+1;i<=bl[n];i++)sum[i]+=1ll*k*(1-x),tag[i]+=k;
    }
    inline void add(int l,int r,int k){add(l,k);if(r<n)add(r+1,-k);}
    inline ll query(int x){return pre[x]+sum[bl[x]]+1ll*tag[bl[x]]*x;}
    inline ll query(int l,int r){return query(r)-query(l-1);}
}b[N/B+50];
int low[N/B+50][N],upp[N/B+50][N];
int main(){
    n=read(),k=read();
    for(int i=1;i<=n;i++)t[i]=read();
    for(int i=1;i<=n;i++)a[i]=read(),pre[i]=pre[i-1]+(t[i]==1?a[i]:-a[i]);
    for(int i=0;i<n;i++)st[++tot]=pre[i];
    sort(st+1,st+tot+1);
    tot=unique(st+1,st+tot+1)-st-1;
    for(int i=1;i<=tot;i++)mp[st[i]]=i;
    for(int i=0;i<n;i++)hav[mp[pre[i]]].push_back(i);
    for(int i=1;i<=n;i++){
        bl[i]=(i-1)/B+1;
        if(bl[i]^bl[i-1])L[bl[i]]=i;
        R[bl[i]]=i;
    }
    for(int i=1;i<=tot;i++)if((int)hav[i].size()>B)big.push_back(i),id[i]=++cnt;
    for(int i=0;i<n;i++)if(id[mp[pre[i]]]){
        int x=id[mp[pre[i]]];
        low[x][i+1]++;
        upp[x][i+2]++;
    }
    for(int i=1;i<=cnt;i++){
        upp[i][0]=1;
        for(int j=1;j<=n;j++)low[i][j]+=low[i][j-1],upp[i][j]+=upp[i][j-1];
        b[i].init(low[i][n]);
    }
    Q=read();
    for(int t=1;t<=Q;t++){
        int l=read(),r=read();
        qu[r].push_back({l,t});
    }
    for(int i=1;i<=n;i++){
        ll cur=pre[i]-k;
        if(mp[cur]){
            int x=mp[cur];
            int len=hav[x].size();
            if(len<=B){
                for(auto j:hav[x]){
                    if(j>=i)break;
                    T.modify(j+1);
                }
            }
            else{
                int y=id[x];
                b[y].add(1,low[y][i],1);
            }
        }
        for(auto j:qu[i]){
            int l=j.first,id=j.second;
            ans[id]+=T.query(l,i);
            for(int k=1;k<=cnt;k++)ans[id]+=b[k].query(upp[k][l],low[k][i]);
        }
    }
    for(int i=1;i<=Q;i++)write(ans[i]),putchar('\n');
    return 0;
}
```

---

## 作者：Pwtking (赞：0)

本题的难点在于如何快速判断符合题意的答案。因为题目让我们统计是两种书的和的差，看到这种情况首先想到记录两本书之和差的前缀和 $sum_{1-n}$。

每次我们将 $l$ 移至 $l-1$ 时，新增加的答案情况便是 $[l,k],k\in [l+1,r]$ 这种情况的答案，也即是 $sum_k-sum_{l-1}=k$ 的情况，移项得 $sum_k=k+sum_{l-1}$。即是求有多少个 $sum_k$ 等于 $k+sum_{l-1}$。$k$ 和 $sum_{l-1}$ 是我们在维护时的已知量，那么我们只需处理 $sum_k$ 的次数即可。

每次我们将 $r$ 移至 $r+1$ 时，答案的增加量即是 $[l,k],k \in [l,r)$ 的情况。与刚才 $l$ 转移时的情况同理，即是求 $sum_r-k$ 的数量。

综上，我们需要预处理 $sum$，$sum-k$，$sum+k$，同时判断是否有 $sum-k=sum_i$ 或 $sum+k=sum_i$ 即可。

因为值域过大，所以接下来有两种方式进行实现：

- 离散化。

- 用哈希去重。

第二种常数较大，需大力卡常，推荐使用第一种。

---

## 作者：Daidly (赞：0)

$10^5$ 可以莫队。先求前缀和，对 $t_i=1$ 加上 $a_i$，$t_i=2$ 减去 $a_i$，求出 $sum_i$。

我们考虑如何 `add` 和 `del`，若询问区间为 $[L,R]$，则答案为：

$$
\sum_{l=L}^{R}\sum_{r=l}^{R}[sum_r-sum_{l-1}=k]
$$

发现虽然询问的是 $[L,R]$，但是我们维护 $sum_i$ 的区间为 $[L-1,R]$，下文所以的 $l$ 自动减 $1$。不妨先离散化，开桶来统计。

对于区间左端点右移，即删去左端点，则不能使 $l$ 为左端点，也就是不能对 $sum_{j}-sum_{l}=k,j\in[l+1,r]$ 计数，再 `l=l+1`，注意 $j$ 的范围。

其余三个为：

区间左端点左移，先 `l=l-1`，加上 $sum_j-sum_{l}=k,j\in[l+1,r]$ 的个数。

区间右端点右移，先 `r=r+1`，加上 $sum_{r}-sum_{i}=k,i\in[l,r-1]$ 的个数， 。

区间右端点左移，删去 $sum_r-sum_{i}=k,i\in[l,r-1]$ 的个数，再 `r=r-1`。

如此一来，我们需要开两个桶，分别维护 $sum_i,sum_i+k$ 即可，顺序一定要搞清楚。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long  

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int N=1e5+10;
int n,k,sum[N],sumk[N],a[N],t[N],q,S;
int l=1,r=0,nans=0,ans[N];
struct node{
	int L,R,id;
	bool operator<(const node &p)const{
		if(L/S==p.L/S)return R<p.R;
		return L/S<p.L/S;
	}
}que[N];

int tmp[N<<1],num,tong[N<<1],tongk[N<<1];

void lsh(){
	for(int i=0;i<=n;++i){
		tmp[++num]=sum[i];
		tmp[++num]=sumk[i];
	}
	sort(tmp+1,tmp+num+1);
	num=unique(tmp+1,tmp+num+1)-tmp-1;
	for(int i=0;i<=n;++i){
		sum[i]=lower_bound(tmp+1,tmp+num+1,sum[i])-tmp;
		sumk[i]=lower_bound(tmp+1,tmp+num+1,sumk[i])-tmp;
	}
}

void dell(int pos){
	tong[sum[pos]]--,tongk[sumk[pos]]--;
	nans-=tong[sumk[pos]];
}

void delr(int pos){
	tong[sum[pos]]--,tongk[sumk[pos]]--;
	nans-=tongk[sum[pos]];
}

void addl(int pos){
	nans+=tong[sumk[pos]];
	tong[sum[pos]]++,tongk[sumk[pos]]++;
}

void addr(int pos){
	nans+=tongk[sum[pos]];
	tong[sum[pos]]++,tongk[sumk[pos]]++;
}

signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i)t[i]=read();
	for(int i=1;i<=n;++i)a[i]=read();
	q=read();
	for(int i=1;i<=q;++i)que[i].L=(read()-1),que[i].R=read(),que[i].id=i;
	S=n/(int)sqrt(q);
	sort(que+1,que+q+1);
	for(int i=1;i<=n;++i){
		if(t[i]==1)sum[i]=sum[i-1]+a[i];
		else sum[i]=sum[i-1]-a[i];
	}
	for(int i=0;i<=n;++i)sumk[i]=sum[i]+k;
	lsh();
	for(int i=1;i<=q;++i){
		while(l>que[i].L)addl(--l);
		while(r<que[i].R)addr(++r);
		while(l<que[i].L)dell(l++);
		while(r>que[i].R)delr(r--);
		ans[que[i].id]=nans;
	}
	for(int i=1;i<=q;++i)print(ans[i]),puts("");
	return 0;
}
```

---

## 作者：JWRuixi (赞：0)

~~细节！细节！细节！~~

- 题意

商店里有 $n$ 本书，每本书中有 $a_i$ 个 $t_i=1/2$ 类问题。

有 $q$ 次询问，每次询问给出一个区间求有多少个这个区间的子区间满足：所有书中第 $1$ 类问题比第 $2$ 类问题多 $k$ 个，其中 $k$ 在所有询问中相同。

- 分析

发现数据范围仅有 $10^5$，非常想要莫队，怎么做呢？

考虑一下如果设种类 $1$ 权值为 $1$，种类 $2$ 权值为 $-1$，如果一个区间满足条件即 $pre_r-pre_{l-1}=k$，那就非常好做了！

由于数据范围比较大，所以开个 ```__gnu_pbds::gp_hash_table``` 统计一下每种数出现的次数，对于 $l$ 段点，查询有多少 $cnt_{pre_{l-1}+k}$，对于 $r$ 段点，查询有多少 $cnt_{pre_{r}-k}$，下面代码的实现中，我用 ```q[i].l--``` 的方式转化为开区间，于是就变成查询 $cnt_{pre_l+k}$ 了！

- code

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define ll long long
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(1e5 + 50);
int n, m, k, sqn, a[maxn];
ll pre[maxn], ans[maxn], sum;
__gnu_pbds::gp_hash_table <ll, int> cnt;

struct qNode {
	int l, r, id;
	inline bool operator < (const qNode &rhs) const {
		if (l / sqn == rhs.l / sqn) return (l / sqn) & 1 ? r < rhs.r : r > rhs.r;
		return l < rhs.l;
	}
} q[maxn];

int main () {
	n = read(), k = read(), sqn = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = (read() & 1) ? 1 : -1;
	for (int i = 1; i <= n; i++) a[i] *= read();
	for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i];
	m = read();
	for (int i = 1; i <= m; i++) q[i] = {read() - 1, read(), i};
	sort(q + 1, q + m + 1);
	for (int i = 1, l = 1, r = 0; i <= m; i++) {
		while (l > q[i].l) {
			--l;
			sum += cnt[pre[l] + k];
			cnt[pre[l]]++;
		}
		while (r < q[i].r) {
			++r;
			sum += cnt[pre[r] - k];
			cnt[pre[r]]++;
		}
		while (l < q[i].l) {
			cnt[pre[l]]--;
			sum -= cnt[pre[l] + k];
			++l;
		}
		while (r > q[i].r) {
			cnt[pre[r]]--;
			sum -= cnt[pre[r] - k];
			--r;
		}
		ans[q[i].id] = sum;
	}
	for (int i = 1; i <= m; i++) write(ans[i]), puts("");
}
```

---

## 作者：ningago (赞：0)

对于每个位置，设置权值 $val_i$，$t_i=1$ 的权值 $val_i$ 设为 $a_i$，$t_i=2$ 设为 $-a_i$，那么题意转化为：

每次询问给出 $l_i,r_i$，求 $l_i \leq L \leq R\leq r_i$ 且 $\sum_{x=L}^R val_x=k$ 的 $L,R$ 点对个数。

考虑将区间和转化为点对：

记 $pre_i$ 为 $\sum_{x=1}^i val_x$，则有 $\sum_{x=L}^R val_x=pre_R - pre_{L-1}$。

转化为求 $l_i-1 \leq L \leq R\leq r_i$，$pre_R = k+ pre_{L}$ 的 $L,R$ 点对个数。

考虑莫队维护。

从已知序列 $i\in [L,R]$ 右边加入/删除点 $x$，贡献是 $[L,R]$ 中 $pre_i=pre_x-k$ 的 $i$ 的个数。

从已知序列 $i\in [L,R]$ 左边加入/删除点 $x$，贡献是 $[L,R]$ 中 $pre_i=pre_x+k$ 的 $i$ 的个数。

如果暴力维护 `cnt` 数组，下标最大是 $[-10^{14},10^{14}]$。

一种做法是直接开 `map` 存，复杂度是 $n\sqrt n \log A$ 的（$A$ 为 $pre$ 值域）。

可以在读入时提前离散化，存下 $pre_i$，$pre_i+k$，$pre_i-k$ 离散化后的下标，即可 $O(1)$ 转移。

```Code:
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>

#define int long long
#define N 200010

int n,m,k;
int t[N],a[N];
int belong[N],L[N],R[N];
int len,idx;
int pre[N];

void init()
{
	len = sqrt(n + 1);
	for(int i = 1;i <= n + 1;i++)
		belong[i] = (i - 1) / len + 1,idx = belong[i];
	for(int i = 1;i <= idx;i++)
	{
		L[i] = (i - 1) * len + 1;
		R[i] = i * len;
	}
	R[idx] = n + 1;
}

struct Query
{
	int l,r,id;
}q[N];

bool cmp(Query x,Query y)
{
	return (belong[x.l] ^ belong[y.l]) ? belong[x.l] < belong[y.l] : ((belong[x.l] & 1) ? x.r < y.r : x.r > y.r);
}

int cnt[N << 2];
int leftcp[N << 2],rightcp[N << 2];
std::map <int,int> mp;
int mpcnt;
int ans[N];

signed main()
{
	scanf("%lld%lld",&n,&k);
	for(int i = 1;i <= n;i++)
		scanf("%lld",&t[i]);
	for(int i = 1;i <= n;i++)
	{
		scanf("%lld",&a[i]);
		if(t[i] == 2)
			a[i] = -a[i];
		pre[i + 1] = pre[i] + a[i];
	}
	for(int i = 1;i <= n + 1;i++)
	{
		if(!mp[pre[i]])
			mp[pre[i]] = ++mpcnt;
		if(!mp[pre[i] + k])
			mp[pre[i] + k] = ++mpcnt;
		if(!mp[pre[i] - k])
			mp[pre[i] - k] = ++mpcnt;
		leftcp[i] = mp[pre[i] + k];
		rightcp[i] = mp[pre[i] - k];
		pre[i] = mp[pre[i]];
	}
	scanf("%lld",&m);
	for(int i = 1;i <= m;i++)
		scanf("%lld%lld",&q[(q[i].id = i)].l,&q[i].r),q[i].r++;
	init();
	std::sort(q + 1,q + 1 + m,cmp);
	int l = 1,r = 0,now = 0;
	for(int i = 1;i <= m;i++)
	{
		int ql = q[i].l,qr = q[i].r;
		while(ql < l)
		{
			l--;
			now += cnt[leftcp[l]];
			cnt[pre[l]]++;
		}
		while(r < qr)
		{
			r++;
			now += cnt[rightcp[r]];
			cnt[pre[r]]++;
		}
		while(l < ql)
		{
			cnt[pre[l]]--;
			now -= cnt[leftcp[l]];
			l++;
		}//
		while(qr < r)
		{
			cnt[pre[r]]--;
			now -= cnt[rightcp[r]];
			r--;
		}
		ans[q[i].id] = now;
	}
	for(int i = 1;i <= m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
```

---

## 作者：NusGhy (赞：0)

  说一个在线的分块做法。  
  
  首先把前缀和离散化。
  
  然后枚举每个块，把块内前缀和开一个桶记下来，再枚举每个元素，每个位置的前缀和减 $k$ 之后在桶里查一下，就可以搞出一个数组 $f_{i,j}$ 表示 $i$ 这个元素作为一个端点，另一个端点在块 $j$ 内部的满足条件的区间数量。
  
  然后前缀和一下搞出 $g_{i,j}$ ，当 $i$ 元素在 $j$ 块左边的时候表示左端点是 $i$，右端点从 （$i+1$） 到（$j$ 块右端点） 的答案数量。右边时同理
  
  然后块内枚举一下元素，再枚举一下另一个块，搞出 $b_{i,j}$ 表示左端点在 $i$ 块内，右端点在（左端点 $+1$ ）到（$j$ 块右端点）的答案数量。
  
  然后回答询问的时候枚举整块用 $b$ 算（两个端点都在整块内的），再枚举不在整块内的点用 $g$ 算（一个端点在整块内，一个端点不在）或者（两个端点在同一边的散点）的，然后（端点在不同侧散点的）显然可以开个桶扫一遍搞完。
  
  时间和空间复杂度都是 $O(n \sqrt{n})$。
  
  注意因为卡空间，所以实现的时候 $g$ 不能另外开，要覆盖掉 $f$ 。
  
  code & data ：[https://codeforces.com/contest/877/submission/157862937](https://codeforces.com/contest/877/submission/157862937)

---

