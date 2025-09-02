# Koishi Loves Segments

## 题目描述

Koishi 喜欢线段。

她的 $n$ 条线段都能表示成数轴上的某个闭区间 $[l,r]$。Koishi 喜欢在把所有线段都放在数轴上，然后数出某些点被多少线段覆盖了。

Flandre 看她和线段玩得很起开心，就抛给她一个问题：

数轴上有 $m$ 个点突然兴奋，如果自己被身上覆盖了超过 $x$ 条线段，这个点就会浑身难受然后把 Koishi 批判一番。

Koishi 十分善良，为了不让数轴上的点浑身难受，也为了让自己开心，她想在数轴上放入尽量多的线段。

按照套路，Koishi 假装自己并不会做这道题，所以她就来求你帮忙。并承诺如果你解决了问题就给你打一通电话。

## 说明/提示

对于 $20\%$ 的数据，满足$1\leq n,m\leq 20$。

对于 $60\%$ 的数据，满足$1\leq n,m\leq 100$。

对于 $80\%$的数据，满足$1\leq n,m\leq 5000$。

对于 $100\%$ 的数据，满足$1\leq x\leq n\leq 2\times 10^5,1\leq m\leq 4\times 10^5,|l|,|r|,|p|\leq 10^7$

如果一个点兴奋了两次，那么 Koishi 应当满足它的**较严苛的要求**（也就是 $p$ 相同时 $x$ 取最小值啦）

请适当使用读入优化。

## 样例 #1

### 输入

```
4 3
1 3
2 4
5 7
6 8
2 5
3 1
6 2```

### 输出

```
3```

# 题解

## 作者：FlashHu (赞：11)

贪心小水题。

把线段按左端点从小到大排序，限制点也是从小到大排序，然后一起扫一遍。

对于每一个限制点实时维护覆盖它的所有线段，如果超过限制，则贪心地把右端点最大的线段永远删去，不计入答案。显然这样做对后面的决策更有利。

以右端点为键值，需要资瓷动态插入，删除最小值、最大值，multiset就行了。

代码很短，常数应该比较大，但不知为何暂时混了个rk1。

```cpp
#include<bits/stdc++.h>
#define R register int
#define G if(++ip==ie)if(fread(ip=buf,1,SZ,stdin))
using namespace std;
const int SZ=1<<19,N=4e5+9;
char buf[SZ],*ie=buf+SZ,*ip=ie-1;
inline int in(){
	G;while(*ip<'-')G;
	R f=*ip=='-';if(f)G;
	R x=*ip&15;G;
	while(*ip>'-'){x*=10;x+=*ip&15;G;}
	return f?-x:x;
}
struct Seg{
	int x,y;
	inline bool operator<(const Seg&a)const{
		return x<a.x;
	}
}a[N],b[N];
multiset<int>s;
int main(){
	R n=in(),m=in(),ans=n;
	for(R i=0;i<n;++i)a[i].x=in(),a[i].y=in();
	for(R i=0;i<m;++i)b[i].x=in(),b[i].y=in();
	sort(a,a+n);sort(b,b+m);
	for(R i=0,j=0;i<m;++i){
		while(j<n&&a[j].x<=b[i].x)s.insert(a[j++].y);
		while(s.size()&&*s.begin()<b[i].x)s.erase(s.begin());
		while(s.size()>b[i].y)s.erase(--s.end()),--ans;
	}
	return cout<<ans<<endl,0;
}
```

---

## 作者：SSerxhs (赞：4)

贪心水题。

离散化，然后将线段按右端点升序，次要条件左端点降序排序，依次加入，能加就加，可以用线段树维护能否插入
```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N=4e5+2,M=1.6e6+2,O=1e7+2,inf=1e9;
int l[M],r[M],s[M],lz[M],fg[N][2],ys[O<<1],xz[N],a[N],b[N],lim[N],pos[N];
int n,m,i,j,c,fh,ds,y,z,ans;
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57))
	{
		if (c=='-') {fh=1;c=getchar();break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	if (fh) {x=-x;fh=0;}
}
void qs(int l,int r)
{
	int i=l,j=r,m=fg[l+r>>1][1],mm=fg[l+r>>1][0];
	while (i<=j)
	{
		while ((fg[i][1]<m)||(fg[i][1]==m)&&(fg[i][0]>mm)) ++i;
		while ((fg[j][1]>m)||(fg[j][1]==m)&&(fg[j][0]<mm)) --j;
		if (i<=j)
		{
			swap(fg[i][0],fg[j][0]);
			swap(fg[i++][1],fg[j--][1]);
		}
	}
	if (i<r) qs(i,r);
	if (l<j) qs(l,j);
}
void build(int x)
{
	if (l[x]==r[x]) {s[x]=lim[l[x]];return;}
	l[c=x<<1]=l[x];r[c]=l[x]+r[x]>>1;
	l[c|1]=r[c]+1;r[c|1]=r[x];
	build(c);build(x<<1|1);
	s[x]=min(s[x<<1],s[x<<1|1]);
}
inline void pushdown(register int x)
{
	if (lz[x])
	{
		lz[c=x<<1]+=lz[x];
		s[c]+=lz[x];
		lz[c=c|1]+=lz[x];
		s[c]+=lz[x];
		lz[x]=0;
	}
}
void rmq(int x)
{
	if ((z<=l[x])&&(r[x]<=y)) {ds=min(ds,s[x]);return;}
	pushdown(x);
	if (z<=r[x<<1]) rmq(x<<1);if (y>r[x<<1]) rmq(x<<1|1);
}
void mdf(int x)
{
	if ((z<=l[x])&&(r[x]<=y))
	{
		--lz[x];--s[x];return;
	}
	pushdown(x);
	if (z<=r[x<<1]) mdf(x<<1);
	if (y>r[x<<1]) mdf(x<<1|1);
	s[x]=min(s[x<<1],s[x<<1|1]);
}
int main()
{
	read(n);read(m);
	for (i=1;i<=n;i++)
	{
		read(fg[i][0]);read(fg[i][1]);
	}
	for (i=1;i<=m;i++)
	{
		read(z);read(y);
		if (ys[z+O])
		{
			xz[ys[z+O]]=min(xz[ys[z+O]],y);
		} else xz[ys[z+O]=++ds]=y,b[ds]=a[ds]=z;
	}
	sort(b+1,b+ds+1);m=ds;
	for (i=1;i<=m;i++) lim[lower_bound(b+1,b+m+1,a[i])-b]=xz[i];
	for (i=1;i<=n;i++)
	{
		fg[i][0]=lower_bound(b+1,b+m+1,fg[i][0])-b;
		fg[i][1]=upper_bound(b+1,b+m+1,fg[i][1])-b-1;
	}
	qs(1,n);r[l[1]=1]=m;build(1);
	for (i=1;i<=n;i++)
	{
		ds=inf;z=fg[i][0];y=fg[i][1];rmq(1);
		if (ds) {++ans;mdf(1);}
	}
	printf("%d",ans);
}
```


---

## 作者：IANYEYZ (赞：3)

事实上本题的思路各位大佬讲的已经是很清楚了。

美中不足的一点是 @FlashHu 大佬的题解中的贪心并没有证明为什么『贪心地把右端点最大的线段永远删去，不计入答案。显然这样做对后面的决策更有利。』，所以就有了这篇题解。

为方便讲解，先给出核心代码：

```cpp
for(int i = 1,j = 1;i <= m;i++) {
	while(j <= n && a[j].x <= b[i].x) s.insert(a[j++].y);
	while(s.size() && *s.begin() < b[i].x) s.erase(*s.begin());
	while(s.size() > b[i].y) s.erase(--s.end()),ans--;
}
```

`a` 数组和 `b` 数组分别是线段和点，都已经按左端点（线段）或按坐标（点）排好了序。

首先考虑在考虑第 $i$ 个点（换句话说正在跑第 4 行）时 `multiset` 内部到底存了什么。容易发现存了能够覆盖到该点的线段，而跑完第 5 行后，我们期望 `multiset` 中的线段**在只考虑前 $i$ 个点时**是合法的。

现在假设覆盖第 $i$ 个点的线段数量并不满足题目要求，那么需要删除一些线段，可以证明，删除最靠右的线段是最优的：

假设有两条线段 $a$，$b$ 并且 $b$ 的右端点在 $a$ 的右端点的右侧。

1. 如果 $a$，$b$ 都没有遮住额外的点，那么显然删哪个都一样。

2. 如果 $a$，$b$ 都遮住了额外的点，并且遮的数量一样，那么还是删哪个都一样

3. 否则，一定有 $b$ 遮住了更多的点，此时删除 $b$ 一定更优，因为这使得更多的线段可以填入。

综上，一定有删 $a$ 不优于删 $b$。

剩下的部分没什么好讲的（反正也不是这篇题解的重点），自行去看 @FlashHu 大佬的题解。

代码还是得给的：

```cpp
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
struct node{
	int x,y;
	bool operator<(node o) {
		return x < o.x;
	}
}a[400010],b[400010];
int n,m,ans;
multiset<int> s;
int main()
{
	cin >> n >> m;
	ans = n;
	for(int i = 1;i <= n;i++) {
		cin >> a[i].x >> a[i].y;
	}
	for(int i = 1;i <= m;i++) {
		cin >> b[i].x >> b[i].y;
	}
	sort(a + 1,a + n + 1);
	sort(b + 1,b + n + 1);
	for(int i = 1,j = 1;i <= m;i++) {
		while(j <= n && a[j].x <= b[i].x) s.insert(a[j++].y);
		while(s.size() && *s.begin() < b[i].x) s.erase(*s.begin());
		while(s.size() > b[i].y) s.erase(--s.end()),ans--;
	}
	cout << ans << "\n";
}
```

---

## 作者：w (赞：2)

官方题解： https://www.luogu.org/discuss/show?postid=7867


---

## 作者：FreedomKing (赞：1)

妙妙贪心题，但我太菜了模拟赛出类似题没切出来。

### 思路

直接按照题意增加线段是不好做的，考虑正难则反，把所有边先加入到数轴中枚举每一个限制然后删除线段。

删除线段有点 dp 的感觉但是实际上是一个很简单的贪心。先把线段按照左端点升序其次右端点升序排序，限制条件也升序排序并从左往右扫，显然在把题目转换后尽量多加入线段变成了尽量少删除线段，对于数轴上一个有超出限制数量的线段的点，删除右端点最靠右的覆盖这个点的线段更有可能对后面数轴上的点产生贡献，直接使用 set 维护即可。

### AC Code

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize("Ofast")
bool M1;
#define look_memory cerr<<abs(&M2-&M1)/1024.0/1024<<" MB\n"
#define look_time cerr<<(clock()-Time)*1.0/CLOCKS_PER_SEC<<'\n'
#define File(_) freopen(_".in","r",stdin);freopen(_".out","w",stdout)
#define int long long
using namespace std;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
const int N=1e6+5,mN=3e4+5,mod=9999991;
namespace FreedomKing_qwq{
#define Time 0
#define lowbit(_) (_&-_) 
	struct Tree{
		int tree[N];
		inline void add(int x,int j){
			for(int i=1;i<=x;i+=lowbit(i)) tree[i]+=j;
			return;
		}
		inline int query(int x){
			int ans=0;
			for(int i=x;i>1;i-=lowbit(i)) ans+=tree[i];
			return ans;
		}
	};
	struct Dset{
		int fa[N];
		inline void init(int x){
			for(int i=1;i<=x;i++) fa[i]=i;
			return;
		}
		inline int find(int x){
			return (fa[x]==x?x:fa[x]=find(fa[x]));
		}
		inline void update(int x,int y){
			x=find(x);y=find(y);
			fa[y]=x;
			return;
		}
	};
#define lc (p<<1)
#define rc (p<<1|1)
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}	
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (x%y==0?y:gcd(y,x%y));}
	inline int lcm(int x,int y){return (x/gcd(x,y)*y);}
#define pf(_) ((_)*(_))
}
pair<int,int>a[N],f[N];
multiset<int>st;
bool M2;signed main(){
	int n=qr,m=qr;
	for(int i=1;i<=n;i++) a[i]={qr,qr};
	for(int i=1;i<=m;i++) f[i]={qr,qr};
	sort(a+1,a+n+1);
	sort(f+1,f+m+1);
	int ans=n;
	for(int i=1,pos=1;i<=m;i++){
		while(a[pos].first<=f[i].first&&pos<=n){
			st.insert(a[pos].second);
			pos++;
		}
		while((!st.empty())&&(*st.begin())<f[i].first) st.erase(*st.begin());
		while(st.size()>f[i].second){
			st.erase(--st.end());
			ans--;
		}
	}
	qw(ans);
	return 0;
}
```

---

## 作者：Caicz (赞：1)

#### 前言

~~我已经收到 koishi 打来的电话了~~

#### 题意

在一个数轴上，给你 n 条线段，同时有 m 个点它突然兴奋(题面这么说的qwq)，认为它只能被覆盖 x 次，求最多能放在数轴上的线段数量

#### 题解

看到这题我也是突然兴奋qwq，然后开始分析
我们需要判断只有 m 个点，显然的我们先对所有的坐标离散化，给每个点赋上权值 -x ，我们将所有的线段都放在数轴上，所有覆盖的位置权值 +1，可以各种方法维护

此时很显然权值为正的点是不合法的，此时转化一下题意，就成了：

+ 使用最少的线段覆盖数轴上的点，第 x 个点要求至少覆盖 y 次

贪心选取对于能选择的能达到最远的线段即可，可以用 堆/平衡树/优先队列 等数据结构简单维护
$$
\large\color{grey}{\text{Talk is cheap , show you the code}}
$$


#### 代码

```cpp
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=400005;
const int inf=0x3f3f3f3f;
int n,m,b[maxn],sum[maxn],ans;
int vis[maxn];
struct node
{
	int pos,val;
}p[maxn];
struct seg
{
	int l,r;
}s[maxn];
vector<int>c[maxn];
priority_queue<int>q;

inline int read(void)
{
	int num,sign=1;char c;
	while(!isdigit(c=getchar()))if(c=='-')sign=0;num=c-'0';
	while(isdigit(c=getchar()))num=(num<<1)+(num<<3)+c-'0';
	return sign?num:-num;
}

signed main(void)
{
	n=read(),m=read();
	for(register int i=1;i<=n;++i)s[i].l=read(),s[i].r=read();
	for(register int i=1;i<=m;++i)b[i]=p[i].pos=read(),p[i].val=read();
	sort(b+1,b+1+m);
	int M=unique(b+1,b+1+m)-b-1;
	for(register int i=1;i<=m;++i)
	{
		p[i].pos=lower_bound(b+1,b+1+M,p[i].pos)-b;
		if(vis[p[i].pos])
		{
			int t=vis[p[i].pos];
			sum[p[i].pos]+=p[t].val,sum[p[i].pos+1]-=p[t].val;
			p[i].val=min(p[i].val,p[t].val);
		}
		vis[p[i].pos]=i;
		sum[p[i].pos]-=p[i].val,sum[p[i].pos+1]+=p[i].val;
	}
	for(register int i=1;i<=n;++i)
	{
		s[i].l=lower_bound(b+1,b+1+M,s[i].l)-b;
		s[i].r=upper_bound(b+1,b+1+M,s[i].r)-b-1;
		++sum[s[i].l],--sum[s[i].r+1];
		c[s[i].l].push_back(s[i].r);
	}
	for(register int i=1;i<=M;++i)
	{
		sum[i]+=sum[i-1];
		int si=c[i].size();
		for(register int j=0;j<si;++j)q.push(c[i][j]);
		while(sum[i]>0)
		{
			int t=q.top();
			--sum[i],++sum[t+1],--ans;
		}
	}
	cout<<ans+n<<endl;
	return 0;
}

```



---

## 作者：dlzlj_2010 (赞：0)

本来以为是 DP 什么的，结果~~看标签~~发现是贪心（可能是我太蒻了）。  
首先将线段按**左端点**升序排序，兴奋的点也**按坐标升序排序**，方便处理。我们可以发现，这么排序后，在覆盖于点上的线段**超过 $x$ 条**时，右端点更大的**可能会覆盖较多的点**，所以右端点更大的线段**一定不优**。  
有注意到 $\lvert l\rvert,\lvert r\rvert,\lvert p\rvert \le 10^7$，**需要离散化**，这里因为线段端点可能重复，所以使用 multiset。

## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,M=4e5+5;
struct seg{//线段
	int l,r;
}a[N];
struct point{//兴奋点
	int p,x;
}b[M];
bool cmp1(seg a,seg b){//按照线段的左端点排序
	return a.l<b.l;
}
bool cmp2(point a,point b){//按坐标排序
	return a.p<b.p;
}
int n,m,ans;
multiset<int>s;//默认按升序排序
int main(){
	int n,m;
	cin>>n>>m;
	ans=n;
	for(int i=1;i<=n;i++){
		cin>>a[i].l>>a[i].r;
	}
	for(int i=1;i<=m;i++){
		cin>>b[i].p>>b[i].x;
	}
	sort(a+1,a+1+n,cmp1);
	sort(b+1,b+1+m,cmp2);
	int idx=1;//在a数组中的下标
	for(int i=1;i<=m;i++){//维护每一个兴奋点
		while(idx<=n&&a[idx].l<=b[i].p){//加入所有可能覆盖当前点的线段
			s.insert(a[idx++].r);
		}
		while(s.size()&&*s.begin()<b[i].p){//删去未覆盖当前点的线段
			s.erase(s.begin());
		}
		while(s.size()>b[i].x){//多于x个且右端点最大的一定不优，删除
			s.erase(--s.end()),ans--;
		}
	}
	cout<<ans;
    return 0;
}
```

---

