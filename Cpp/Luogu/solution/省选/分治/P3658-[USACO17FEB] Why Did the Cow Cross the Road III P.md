# [USACO17FEB] Why Did the Cow Cross the Road III P

## 题目描述

Farmer John 继续思考奶牛穿过他农场道路的问题，这个问题在前两个问题中已经介绍过。他现在意识到，友好度的阈值比他之前考虑的要微妙一些——现在，品种 $a$ 和 $b$ 是友好的当且仅当 $|a - b| \leq K$，否则就是不友好的。给定 FJ 农场道路两侧田地的品种顺序，请计算不友好的交叉品种对的数量，其中交叉品种对的定义与 [前两个问题](https://www.luogu.com.cn/problem/P3657) 相同。

## 说明/提示

在这个例子中，品种 1 和 4 是不友好的且交叉的，品种 1 和 3 也是不友好的且交叉的。

## 样例 #1

### 输入

```
4 1
4
3
2
1
1
4
2
3```

### 输出

```
2```

# 题解

## 作者：米奇奇米 (赞：11)

## 题解- P3658 Why Did the Cow Cross the Road III P

* **题目大意**

很小清新。就是给你两个排列$A,B$使得两个排列中相同的数字两边相连。最后问你存在多少对数对满足有交叉且$abs(Ai-Aj)>m$

* $Solution$

我们可以将题目转化的更加小清新。因为要有交显然满足$PA(Ai)<PB(Ai)$以及$PA(Aj)<PB(Aj)[PA,PB$为该元素在$A,B$排列中的位置$]$

这样我们就可以设一个三元组$(x,y,z)$满足

* $xi<xj$
* $yi>yj$
* $|zi-zj]>m$

于是这样就转换为一个三维偏序的简单问题，三维偏序见[戳这里](https://www.luogu.org/problem/P3810)

然后我们考虑单次计算的贡献显然为$[z-m,z+m]$这段区间里的答案，简单容斥即可


* $Code$

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for ( int i=(a);i<=(b);i++ )
#define Dow(i,a,b) for ( int i=(a);i>=(b);i-- )
#define FOR(i,t) for ( int i=head[t];i;i=e[i].nex )
#define int long long
#define db double
#define mem(x,s) memset(x,s,sizeof(x))
#define cpy(x,s) memcpy(x,s,sizeof(x))
#define lowbit(x) x&(-x)
using namespace std;

namespace IO {
	#define gc getchar
	#define pt putchar
	inline int read() {
		int sum=0,ff=1; char ch=gc();
		while(!isdigit(ch)) {
			if(ch=='-') ff=-1;
			ch=gc();
		}
		while(isdigit(ch))
			sum=sum*10+(ch^48),ch=gc();
		return sum*ff;
	}

	inline void write(int x) {
		if(x<0) pt('-'),x=-x;
		if(x>9) write(x/10);
		pt(x%10|48);
	}

	inline void wln(int x) {
		write(x); pt('\n');
	}

	inline void wrn(int x) {
		write(x); pt(' ');
	}
}

using namespace IO;

const int N=1000005;

int n,m,c[N*2],bo[N],ans;

struct number {
	int x,y,z;
};
number a[N],tmp[N];

inline bool cmpy(number a,number b) {
	if(a.y==b.y) return a.z<b.z;
	return a.y>b.y;
}

inline bool cmpx(number a,number b) {
	if(a.x==b.x) {
		if(a.y==b.y) return a.z<b.z;
		return a.y>b.y;
	}
	return a.x<b.x;
}
//三维排序

inline void add(int x,int val) {
	while(x<=n) {
		c[x]+=val;
		x+=lowbit(x);
	}
}

inline int query(int x) {
	int ret=0;
	x=min(x,n);
	x=max(x,0ll);
    //注意边界,被坑了好久
	while(x) {
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}

inline void cdq(int l,int r) {
//cdq模板
	if(l==r) return;
	int mid=(l+r)/2;
	cdq(l,mid);
	cdq(mid+1,r);
	sort(a+l,a+mid+1,cmpy);
	sort(a+mid+1,a+r+1,cmpy);
	int i=mid+1,j=l;
	for (;i<=r;i++) {
		while(j<=mid&&a[j].y>a[i].y) {
			add(a[j].z,1);
			j++;
		}
		ans+=query(a[i].z-m-1)+query(n)-query(a[i].z+m);
       //计算单次贡献
	}
	For(i,l,j-1) add(a[i].z,-1);//清空树状数组
}
	
signed main() {
	n=read();
	m=read();
	For(i,1,n) bo[read()]=i;
    //映射数组
	For(i,1,n) {
		int x=read();
		a[i]=(number){bo[x],i,x};
        //建立三元组
	}
	sort(a+1,a+n+1,cmpx);
	cdq(1,n);
	wln(ans);
	return 0;
}
```



---

## 作者：「QQ红包」 (赞：10)

比较简单的模型转换

记录两个序列每个元素出现的位置.

$c_i$ 表示为品种 $c_i$

$a_i$,$b_i$分别表示品种 $c_i$出现在两个序列的位置

有交叉点: $a_i<a_j$且 $b_i>b_j$

还有一个条件是 $abs(c_i-c_j)>k$

然后就是裸的了,而且没有什么特殊情况,比较好处理

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int qmax(int &x,int y) {if (x<y) x=y;}
inline int qmin(int &x,int y) {if (x>y) x=y;}
inline int read()
{
    char s;
    int k=0,base=1;
    while((s=getchar())!='-'&&s!=EOF&&!(s>='0'&&s<='9'));
    if(s=='-')base=-1,s=getchar();
    while(s>='0'&&s<='9')
    {
        k=k*10+(s^48);
        s=getchar();
    }
    return k*base;
}
void write(int x)
{
    if(x<0){putchar('-');write(-x);}
    else{if(x/10)write(x/10);putchar(x%10+'0');}
}
const int maxn=1e5+10;
int n,k,X;
int Map[maxn];
long long ans;
int t[maxn];
inline void xg(int x) {while (x<=n) t[x]+=1,x+=x&(-x);}
inline void xg1(int x) {while (x<=n) t[x]-=1,x+=x&(-x);}
inline int qh(int x) {x=x>n?n:x;if (x<=0) return 0;int s=0;while (x) s+=t[x],x^=x&(-x);return s;}
struct node
{
    int x,y,z;//x:p1,y:p2,z:权值
} a[maxn],b[maxn];
bool cmp(node aa,node bb) {return aa.x==bb.x?(aa.y==bb.y)?(aa.z<bb.z):aa.y>bb.y:aa.x<bb.x;}
inline void hb(int l,int r)
{
    if (l==r) return;
    int mid=(l+r)>>1;
    int i=l,j=mid+1,p=l-1;
    while (i<=mid&&j<=r) {if (a[i].y>a[j].y) b[++p]=a[i++]; else b[++p]=a[j++];}
    while (i<=mid) b[++p]=a[i++];
    while (j<=r) b[++p]=a[j++];
    for (int k=l;k<=r;k++) a[k]=b[k];
}
inline void ef(int l,int r)
{
    if (l==r) return;
    int mid=(l+r)>>1;
    ef(l,mid);ef(mid+1,r);hb(l,mid);hb(mid+1,r);
    int i=l,j=mid+1;
    while (j<=r)
    {
        while (i<=mid&&a[i].y>a[j].y) xg(a[i++].z);
        ans=ans+(long long)qh(a[j].z-k-1)+(long long)qh(n)-qh(a[j].z+k);
        ++j;
    }
    for (int k=l;k<i;k++) xg1(a[k].z);
}
int main()
{
    n=read();k=read();
    for (int i=1;i<=n;i++) Map[read()]=i;
    for (int i=1;i<=n;i++)
    {
        X=read();
        a[i].x=Map[X];a[i].y=i;a[i].z=X;
    }
    sort(a+1,a+n+1,cmp);
    ef(1,n);
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：bztMinamoto (赞：8)

题意

两列$n$的排列，相同的数连边，如果一对数有交叉且差的绝对值$>k$，则$++ans$，求$ans$

题解

可以把每一个数字看成一个三元组$(x,y,z)$，其中$x$表示在第一列的位置，$y$表示在第二列的位置，$z$表示权值

两条线交叉，就是$x<x'$且$y>y'$，又要满足差值的绝对值小于等于$k$，就是$|z-z'|<=k$

于是就转化为了一个三维偏序问题，直接上CDQ

具体细节请看代码
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
template<class T>inline bool cmin(T&a,const T&b){return a>b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=1e5+5;
int n,k,b[N];
ll ans;int c[N];
inline void add(int x){
    for(;x<=n;x+=x&-x) c[x]+=1;
}
inline void clear(int x){
    for(;x<=n;x+=x&-x)
    if(c[x]) c[x]=0;
    else break;
}
inline int query(int x){
    int res=0;x=x>n?n:x;if(x<=0) return 0;
    for(;x;x-=x&-x) res+=c[x];
    return res;
}
struct node{
    int x,y,z;
    node(){}
    node(int x,int y,int z):x(x),y(y),z(z){}
    inline bool operator <(const node &b)const
    {return x!=b.x?x<b.x:
            y!=b.y?y>b.y:
            z<b.z;}
}a[N],p[N];
void CDQ(int l,int r){
    if(l==r) return;
    int mid=l+r>>1;
    CDQ(l,mid),CDQ(mid+1,r);
    for(int j=mid+1,i=l;j<=r;++j){
        while(i<=mid&&a[i].y>a[j].y) add(a[i++].z);
        ans+=1ll*query(a[j].z-k-1)+query(n)-query(a[j].z+k);
    }
    for(int i=l;i<=mid;++i) clear(a[i].z);
    for(int i=l,j=l,k=mid+1;i<=r;){
        if(k>r||(j<=mid&&a[j].y>a[k].y)) p[i++]=a[j++];
        else p[i++]=a[k++];
    }
    for(int i=l;i<=r;++i) a[i]=p[i];
}
int main(){
    //freopen("testdata.in","r",stdin);
    n=read(),k=read();
    for(int i=1;i<=n;++i){
        int x=read();b[x]=i;
    }
    for(int i=1;i<=n;++i){
        int x=read();
        a[i]=node(b[x],i,x);
    }
    sort(a+1,a+1+n);
    CDQ(1,n);
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Ginger_he (赞：3)

# 题解
假设 $i$ 在排列 $A$ 中的位置为 $a_i$，在排列 $B$ 中的位置为 $b_i$。由于它们所在两个排列间对应的线交叉，不难得到 $a_i>a_j,b_i<b_j$ 或 $a_i<a_j,b_i>b_j$。通过样例发现，$(x,y)$ 和 $(y,x)$ 是同一种答案，所以我们钦定 $i>j+k$，做两次 cdq 分治即可。

分别以 $a_i,b_i,i$ 为第一、第二、第三关键字，先按第一维排序，在 cdq 分治的过程中，在保证第二关键字有序的同时，用树状数组维护第三关键字即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100005
struct node
{
	int x,y,z;
}a[N];
int n,k,t;
ll c[N<<1],ans;
bool cmp1(node u,node v)
{
	return u.x<v.x;
}
bool cmp2(node u,node v)
{
	return u.y>v.y;
}
bool cmp3(node u,node v)
{
	return u.x>v.x;
}
bool cmp4(node u,node v)
{
	return u.y<v.y;
}
int lowbit(int x)
{
	return x&(-x); 
}
void add(int x,int y)
{
	while(x<=n)
	{
		c[x]+=y;
		x+=lowbit(x);
	}
}
ll query(int x)
{
	ll res=0;
	while(x)
	{
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
void cdq1(int l,int r)
{
	if(l==r)
		return;
	int mid=l+r>>1,i,j=r;
	cdq1(l,mid);
	cdq1(mid+1,r);
	sort(a+l,a+mid+1,cmp2);
	sort(a+mid+1,a+r+1,cmp2);
	for(i=mid;i>=l;i--)
	{
		while(a[i].y>a[j].y&&j>mid)
		{
			add(a[j].z,1);
			j--;
		}
		if(a[i].z>k)
			ans+=query(a[i].z-k-1);
	}
	for(i=r;i>j;i--)
		add(a[i].z,-1);
}
void cdq2(int l,int r)
{
	if(l==r)
		return;
	int mid=l+r>>1,i,j=r;
	cdq2(l,mid);
	cdq2(mid+1,r);
	sort(a+l,a+mid+1,cmp4);
	sort(a+mid+1,a+r+1,cmp4);
	for(i=mid;i>=l;i--)
	{
		while(a[i].y<a[j].y&&j>mid)
		{
			add(a[j].z,1);
			j--;
		}
		if(a[i].z>k)
			ans+=query(a[i].z-k-1);
	}
	for(i=r;i>j;i--)
		add(a[i].z,-1);
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		a[t].x=i;
		a[i].z=i;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&t);
		a[t].y=i;
	}
	sort(a+1,a+n+1,cmp1);
	cdq1(1,n);
	sort(a+1,a+n+1,cmp3);
	cdq2(1,n);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

## 分析

对于这道题，我们不妨设 $\mathit{f}_{i},\mathit{s}_i$ 分别表示数字 $i$，在第一、二个排列中的下标位置（从 $1$ 到 $n$）。则我们的问题就转化成了求满足以下条件的二元组 $(i,j)$ 的数量：

1. $\mathit{f}_{i} < \mathit{f}_{j}$。

2. $\mathit{s}_{i} > \mathit{s}_{j}$。

3. $|i-j| > k$。

对于条件 $3$，我们有 $2$ 种情况：$i >j$，此时有 $i-k+1 \le j$；$i < j$，此时有 $i+k+1 \le j$。我们可以直接使用 CDQ 进行分治求值，每次的 $i$ 的贡献就使用 $2$ 棵树状数组。

## 代码

```cpp
//a.x<b.x,a.y>b.y,|a.s-b.s|>k
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
const int N=1e6+10;
int n,k,ans;
struct node{
	int x,y,s;
}a[N],b[N];
int tr1[N],tr2[N];
il bool cmp1(node a,node b){return a.x<b.x;}
il bool cmp2(node a,node b){return a.y>b.y;}
il void insert1(int x,int y){while(x<=n) tr1[x]+=y,x+=x&(-x);}
il void insert2(int x,int y){while(x>=1) tr2[x]+=y,x-=x&(-x);}
il int query1(int x){
	int ans=0;while(x>=1) ans+=tr1[x],x-=x&(-x);
	return ans;
}
il int query2(int x){
	int ans=0;while(x<=n) ans+=tr2[x],x+=x&(-x);
	return ans;
}
il void cdq(int l,int r){
	if(l>=r) return ;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp2),sort(a+mid+1,a+r+1,cmp2);
	int i=mid+1,j=l;
	for(;i<=r;++i){
		while(j<=mid&&a[j].y>a[i].y)
			insert1(a[j].s,1),insert2(a[j].s,1),++j;
		if(a[i].s-k-1>=0) ans+=query1(a[i].s-k-1);
		if(a[i].s-k+1<=n) ans+=query2(a[i].s+k+1);
	}
	for(re int k=l;k<j;++k)
		insert1(a[k].s,-1),insert2(a[k].s,-1);
	return ;
}
il void read(){
	scanf("%lld%lld",&n,&k);
	for(re int i=1;i<=n;++i){
		int x;scanf("%lld",&x);
		a[x]={i,0,x};
	}
	for(re int i=1;i<=n;++i){
		int y;scanf("%lld",&y);
		a[y]={a[y].x,i,y};
	}
	return ;
}
il void solve(){
	sort(a+1,a+n+1,cmp1);
	cdq(1,n);
	cout<<ans;return ;
}
signed main(){
	read(),solve();return 0;
}
```


---

## 作者：Jusc (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P3658)。

## 题目大意

两个排列 $A$，$B$，相同的数字连线，问有多少连线相交且满足 $ \left\vert  a - b \right\vert > k$ 的数对 $ (a,b) $。

## 正文

### 分析

令 $a_i$ 表示 $i$ 在排列 $A$ 中的位置，$b_i$ 同理。

容易看出，两个数 $i$，$j$ 的连线相交当且仅当满足下列一个条件：

* $a_i>a_j$ 且 $b_i<b_j$。

* $a_i<a_j$ 且 $b_i>b_j$。

不难看出 $(i,j)$ 和 $(j,i)$ 其实是同一种情况。接下来我们就默认使用第二种。

到这里，我们很容易看出使用三维偏序来处理。前两维存入 $x$ 在两个排列中的位置，我们按照正常cdq思路处理即可。

再来考虑 $ \left\vert a-b \right\vert > k$ 的情况。我们可以将 $x$ 的值存为第三维，将满足前两维条件的数用**树状数组**在 $x$ 的位置插入 $1$。因为 $ \left\vert a-b\right\vert > k$，所以对于 $x$ 来说，$\left[ x-k , x+k \right]$ 之间的数是没有贡献的。简单容斥可得，其真正有贡献的区间为 $\left[ 1 , x-k \right) \cup \left( x+k , m \right]$。对于这个区间前缀和处理。

所以就可以解决问题了，挺板的。

## Code:
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+100;
struct Yan
{
	int a,b,c;
}s[N];
int tr[N];
int n,m;
int ii[N];
long long ans;
bool cmp1(Yan &x,Yan &y)
{
	if(x.a==y.a)
	{
		if(x.b==y.b) return x.c<y.c;
		else return x.b>y.b;//别写反了
	} 
	else return x.a<y.a;
}
bool cmp2(Yan &x,Yan &y)
{
	if(x.b==y.b) return x.c<y.c;
	else return x.b>y.b;
}
int lowbit(int x) 
{
	return x&(-x);
}
void add(int x,int c)
{
	for(int i=x;i<=n;i+=lowbit(i)) tr[i]+=c;
}
int query(int x)
{
	int sum=0;
	x=min(x,n);
	x=max(0,x);
	for(int i=x;i;i-=lowbit(i)) sum+=tr[i];
	return sum;
}
void cdq(int l,int r)
{
	if(l==r) return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	sort(s+l,s+mid+1,cmp2),sort(s+mid+1,s+r+1,cmp2);
	
	int i,j=l;
	for(i=mid+1;i<=r;i++)
	{
		while(s[i].b<s[j].b&&j<=mid)
		{
			add(s[j].c,1);
			j++;
		}
		ans+=query(s[i].c-m-1)+query(n)-query(s[i].c+m);
	}
	for(i=l;i<j;i++)
	add(s[i].c,-1);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		ii[x]=i;
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		s[i]={ii[x],i,x};
	}
	sort(s+1,s+n+1,cmp1);
	cdq(1,n);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：xuzz (赞：2)

###### 个人写的第三道cdq分治，让我对cdq分治的理解又加深了。

题意已经够精简了，就不再赘述。

具体做法

$op_i$ 表示上面排列下标为 $i$ 的数在下面排列中对应数的下标。

只要找到所有 $i<j$ 且 $op_i>op_j$ 且 $|(a_i-a_j)>k|$ 的数对即可。

这样一转换就成了三维偏序的板子，可用cdq分治实现。

有一个小优化，一边处理贡献一边归并，省去了sort的时间。
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
const int N=100005;
struct obj{int y,z;}a[N],A[N];//A数组的作用是处理贡献时存归并后的数组
//本来开了x,y,z三个维度，后来发现我以下标为第一维，无需排序，所以x维度可以省略
int b[N],c[N],x,n,k;
long long ans;
void add(int x,int k){while(x<=n) c[x]+=k,x+=x&-x;}
int ask(int x){int s=0;while(x) s+=c[x],x-=x&-x;return s;}
void cdq(const int l,const int r)
{
	if(l==r) return;
	int mid=l+r>>1;
	cdq(l,mid),cdq(mid+1,r);
	int ll=l,cnt=ll;
	for(int rr=mid+1;rr<=r;rr++)
	{
		while(ll<=mid&&a[ll].y>a[rr].y) A[cnt++]=a[ll],add(a[ll].z,1),ll++;
		A[cnt++]=a[rr];
		int x1=a[rr].z-k,x2=a[rr].z+k;
		if(x1>1) ans+=ask(x1-1);//处理权值比当前数小至少k+1的贡献
		if(x2<n) ans+=ask(n)-ask(x2);//处理权值比当前数大至少k+1的贡献
	}
	for(int i=l;i<ll;i++) add(a[i].z,-1);
	while(ll<=mid) A[cnt++]=a[ll++];
	for(int i=l;i<=r;i++) a[i]=A[i];
	return;
}
int main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++) b[read()]=i;
	for(int i=1;i<=n;i++) a[i].z=read(),a[i].y=b[a[i].z];//我是以下面的排列为基准
	return cdq(1,n),printf("%lld\n",ans),0;//小小压行，无伤大雅
}
```

---

## 作者：moosssi (赞：2)

简单转化+cdq分治。

先简化题意：

给你两个序列，序列两边相同的数互相连线，若两两连线产生交点，且两条连线的数的绝对值差不超过k，则对答案的贡献加一。

设一个数为c，在两个序列分别出现的位置为a，b，那么对于两数 $c_i$ 和 $c_j$，
求满足：$a_i>a_j$，$b_i<b_j$， $|c_i-c_j|\le k$ 的情况。

这里很明显是道三维偏序的裸题，具体过程不再赘述，这里主要说一个地方。

双指针枚举时，我用的是树状数组维护前缀和，总的减去友好的数目即为所求数，注意范围不要越界,大概是这样： 

$query(N-1)-query(min(q[j].c+K,N-1))+query(max(q[j].c-K-1,0))$

最后，注意开long long。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
typedef long long ll;
struct nod{
	int a,b,c;
	ll res;
}q[N],w[N];
int tr[N],n,K;
ll ans;
bool cmp(nod x,nod y){
	return x.a>y.a;
}
int lowbit(int x){
	return x&-x;
}
void add(int x,int v){
	for(int i=x;i<N;i+=lowbit(i)){
		tr[i]+=v;
	}
}
int query(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i)){
		res+=tr[i];
	}
	return res;
}
void merg_sort(int l,int r){
	if(l>=r)return ;
	int mid=(l+r)/2;
	merg_sort(l,mid);
	merg_sort(mid+1,r);
	int i=l,j=mid+1,k=1;
	while(i<=mid&&j<=r){
		if(q[i].b<q[j].b)add(q[i].c,1),w[k++]=q[i++];
		else q[j].res+=query(N-1)-query(min(q[j].c+K,N-1))+query(max(q[j].c-K-1,0)),w[k++]=q[j++];
	}
	while(i<=mid)add(q[i].c,1),w[k++]=q[i++];
	while(j<=r)q[j].res+=query(N-1)-(query(min(q[j].c+K,N-1))-query(max(q[j].c-K-1,0))),w[k++]=q[j++];
	for(int i=l;i<=mid;i++){
		add(q[i].c,-1);
	}
	for(i=l,j=1;j<k;i++,j++){
		q[i]=w[j];
	}	
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++){
		int j;
		scanf("%d",&j);
		q[j].a=i;
		q[j].c=j;
	}
	for(int i=1;i<=n;i++){
		int j;
		scanf("%d",&j);
		q[j].b=i;
	}
	sort(q+1,q+n+1,cmp);
	merg_sort(1,n);
	for(int i=1;i<=n;i++){
		ans+=q[i].res;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：glorious_dream (赞：1)

[洛谷 P3658 [USACO17FEB]Why Did the Cow Cross the Road III P](https://www.luogu.com.cn/problem/P3658)

记录一下自己用了独特的两个树状数组解法。

我们开一个结构体，记录三个东西 $up,down,val$，分别表示这个数 $val$ 在 $A$ 排列中的位置，在 $B$ 排列中的位置，这个数的值$($也就是$val)$。然后我们发现，这道题就变成了一道三位偏序的问题。我们可以先按 $up$ 从小到大排序。如果要满足对应的线交叉，那么对于两个数 $x,y$，如果在 $A$ 中 $x$ 在 $y$ 前面，那么在 $B$ 中 $x$ 就必须在 $y$ 后面。那么由于第一维是从小到大排序的，第二维我们就要从大到小排序。还是分成两个区间 $[l,mid]$ 和 $[mid+1,r]$，分别从大到小排序。

考虑如何算贡献。我们记 $i$ 指向 $[mid+1,r]$，$j$ 指向 $[l,mid]$，那么当 $a[j].down > a[i].down$ 的时候，第二维的偏序也满足关系了。这时我们就要考虑怎么把式子给拆开。

$| i-j | > k \Rightarrow  i-j>k$ 或 $i-j<-k \Rightarrow i>j+k$ 或 $i<j-k$

那么我们开两个树状数组，一个往上维护，一个往下维护。在 $j$ 满足条件的时候，我们分别在两个树状数组中，$a[j].val$ 为下标的地方 $+1$。然后我们统计答案的时候，一个我们 $query1(a[i].val-k-1)$，一个 $query2(a[i].val+k+1)$，这两个的和就是答案。

注意，两个树状数组，由于维护的方向正好是相反的，所以我们要开两个数组。我一开始就开了一个数组，然后改了好长时间。

```cpp
#include <bits/stdc++.h>
#define re register
#define ll long long 
#define int long long 
#define rep(a,b,c)  for(re int a(b) ; a<=c ; ++a)
#define drep(a,b,c) for(re int a(b) ; a>=c ; --a)
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
const int M = 2e5+10;
int n,k,ans;
int c1[M],c2[M];
struct node{
    int up,down,val;
}a[M];
inline int lowbit(int x) { return x & -x; }
inline void update1(int x,int y){
    while(x <= n){
        c1[x] += y;
        x += lowbit(x);
    }
}
inline void update2(int x,int y){
    while(x){
        c2[x] += y;
        x -= lowbit(x);
    }
}
inline int query1(int x){
    if(x < 1) return 0;
    int res = 0;
    while(x){
        res += c1[x];
        x -= lowbit(x);
    }
    return res;
}
inline int query2(int x){
    if(x > n) return 0;
    int res = 0;
    while(x <= n){
        res += c2[x];
        x += lowbit(x);
    }
    return res;
}
inline bool cmp1(node a,node b) { return a.up < b.up; }
inline bool cmp2(node a,node b) { return a.down > b.down; }
inline void cdq(int l,int r){
    if(l == r) return;
    int mid = (l+r)>>1;
    cdq(l,mid),cdq(mid+1,r);
    sort(a+l,a+mid+1,cmp2),sort(a+mid+1,a+r+1,cmp2);
    int j = l;
    rep(i,mid+1,r){
        while(j <= mid && a[j].down > a[i].down){
            update1(a[j].val,1);
            update2(a[j].val,1);
            j++;
        }
        ans += query1(a[i].val-k-1) + query2(a[i].val+k+1);
    }
    rep(k,l,j-1) update1(a[k].val,-1),update2(a[k].val,-1);
}
signed main(){
    n = read(),k = read();
    rep(i,1,n){
        int x = read();
        a[x].up = i;
        a[x].val = x;
    }
    rep(i,1,n){
        int x = read();
        a[x].down = i;
    }
    sort(a+1,a+n+1,cmp1);
    cdq(1,n);
    printf("%lld\n",ans);
    return 0;   
}
```


---

## 作者：zhengrunzhe (赞：1)

a[x]是数字x在第一列的位置 b[]是第二列

不友好即：a[y]>a[x]&&b[y]<b[x]&&|x-y|>k

这是一个三维偏序问题 最后一层那个绝对值不好搞

我们把它转化成y<x-k||y>x+k

先排序掉一维然后用树套树(树状数组套Treap)解决
```cpp
#include<cstdio>
#include<algorithm>
#define reg register
using std::sort;
typedef long long ll;
const int N=1e5+10;
template<class type>inline const void read(reg type &in)
{
	in=0;reg char ch=getchar();reg bool fh=0;
	while (ch<48||ch>57)fh=ch=='-'?1:fh,ch=getchar();
	while (ch>47&&ch<58)in=(in<<3)+(in<<1)+(ch&15),ch=getchar();
	if (fh)in=-in;
}
template<class type>inline const void write(reg type out)
{
	if (out>9)write(out/10);
	putchar(out%10+48);
}
int n,k;
ll ans;
struct rapid
{
    int a,b,c;
    inline const bool operator<(reg const rapid &p)const
    {
        return a>p.a;
    }
}w[N];
//namespace Treap{
    struct tree
    {
        tree *son[2];
        int key,size,priority;
        inline const void pushup()
        {
            size=son[0]->size+1+son[1]->size;
        }
    }memory_pool[N<<5],*tail,*null;
    inline const void init()
    {
        tail=memory_pool;
        null=tail++;
        null->son[0]=null->son[1]=null;
        null->key=null->size=null->priority=0;
    }
    inline tree *spawn(reg int key)
    {
        tree *p=tail++;
        p->size=1;
        p->key=key;
        p->priority=rand();
        p->son[0]=p->son[1]=null;
        return p;
    }
    inline const void rotate(reg tree *&fa,reg bool f)
    {
        reg tree *p=fa->son[f];
        fa->son[f]=p->son[f^1];
        p->son[f^1]=fa;
        fa->pushup();(fa=p)->pushup();
    }
    inline const void insert(reg tree *&p,reg int key)
    {
        if (p==null)return (void)(p=spawn(key));
        reg bool f=p->key<key;
        insert(p->son[f],key);p->pushup();
        if (p->son[f]!=null&&p->son[f]->priority<p->priority)rotate(p,f);
    }
    inline const int less(reg tree *p,reg int key)
    {
        if (p==null)return 0;
        if (key<p->key)return less(p->son[0],key);
        if (p->key==key)return p->son[0]->size;
        return less(p->son[1],key)+p->son[0]->size+1;
    }
    inline const int greater(reg tree *p,reg int key)
    {
        if (p==null)return 0;
        if (key>p->key)return greater(p->son[1],key);
        if (p->key==key)return p->son[1]->size;
        return greater(p->son[0],key)+p->son[1]->size+1;
    }
//}using namespace Treap;
class Binary_Indexed_Tree
{
    private:
    	tree *root[N];
    	inline const int lowbit(reg int x)
    	{
			return x&-x;
		}
		inline const int prefix_query(reg int x,reg int y)
		{
			reg int sum=0;
			for (;x;x-=lowbit(x))sum+=less(root[x],y-k)+greater(root[x],y+k);
			return sum;
		}
	public:
		inline const void init()
		{
			for (reg int i=1;i<=n;i++)root[i]=null;
		}
		inline const void update(reg int x,reg int y)
		{
			for (;x<=n;x+=lowbit(x))insert(root[x],y);
		}
		inline const int query(reg int l,reg int r,reg int x)
		{
			if (l>r)return 0;
			return prefix_query(r,x)-prefix_query(l-1,x);
		}
}bit;
int main()
{
    read(n);read(k);
    //scanf("%d%d",&n,&k);
    for (reg int i=1;i<=n;i++)w[i].c=i;
    for (reg int x,i=1;i<=n;i++)//scanf("%d",&x),
	read(x),
	w[x].a=i;
    for (reg int x,i=1;i<=n;i++)//scanf("%d",&x),
	read(x),
	w[x].b=i;
    sort(w+1,w+n+1);init();bit.init();
    for (reg int i=1;i<=n;i++)
        ans+=bit.query(1,w[i].b-1,w[i].c),
        bit.update(w[i].b,w[i].c);
 //   printf("%lld\n",ans);
 	write(ans);
    return 0;
}
```

---

## 作者：苏联小渣 (赞：1)

观察样例发现，$(1,3),(1,4)$ 只会算一次，也就是说 $(3,1),(4,1)$ 不算入答案，所以我们不妨钦定 $i<j$。

由于是一个排列，所以令 $\forall i \in [1,n]$ 在 $A$ 出现的位置为 $a_i$，在 $B$ 中出现的位置为 $b_i$。画个图可以发现有交叉当且仅当 $a_i<a_j,b_i>b_j$ 或 $a_i>a_j,b_i<b_j$。由于我们钦定了 $i<j$，所以 $|i-j|>k$ 的条件就转化为了 $j-i>k,j>i+k$。令 $c_i=i,d_i=i+k$，则原问题转化为了：

$$\{(i,j)|a_i<a_j,b_i>b_j,d_i<c_j\} \cup \{(i,j)|a_i>a_j,b_i<b_j,d_i<c_j\}$$

这就是一个标准的三维偏序问题，用 cdq 分治 + 树状数组即可解决。

虽然两种情况都是 $d_i<c_j$，但是 $c,d$ 是两个数组。为了避免在排序上的瓶颈，这里进行了两次 cdq 分治。每次按 $a$ 排序，cdq 分治把 $b$ 合法的 $j$ 加入树状数组中，对于每一个 $i$，算出已经加入树状数组的使得 $c_j>d_i$ 的 $j$ 有多少个即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, m, k, ans, tmp;
struct node{
	int x, y, c, d, tot;
}a[100010];
int cmp1(node p, node q){
	return p.x < q.x;
}
int cmp2(node p, node q){
	return p.x > q.x;
}
int cmp3(node p, node q){
	return p.y < q.y;
}
int cmp4(node p, node q){
	return p.y > q.y;
}
struct BIT{
	int d[200010];
	void add(int p, int x){
		for (; p<=n+k; p+=p&-p) d[p] += x;
	}
	int query(int p){
		int ret = 0;
		for (; p; p-=p&-p) ret += d[p];
		return ret;
	}
}S, T;
void cdq1(int l, int r){
	if (l == r) return ;
	int mid = l + r >> 1;
	cdq1(l, mid); cdq1(mid+1, r);
	sort (a+l, a+mid+1, cmp3);
	sort (a+mid+1, a+r+1, cmp3);
	int i=l, j=mid+1;
	for (; i<=mid; i++){
		while (j <= r && a[i].y > a[j].y){
			S.add(a[j].c, 1);
			j ++;
		}
		a[i].tot += S.query(n+k) - S.query(a[i].d);
	}
	for (i=mid+1; i<j; i++){
		S.add(a[i].c, -1);
	}
}
void cdq2(int l, int r){
	if (l == r) return ;
	int mid = l + r >> 1;
	cdq2(l, mid); cdq2(mid+1, r);
	sort (a+l, a+mid+1, cmp4);
	sort (a+mid+1, a+r+1, cmp4);
	int i=l, j=mid+1;
	for (; i<=mid; i++){
		while (j <= r && a[i].y < a[j].y){
			T.add(a[j].c, 1);
			j ++;
		}
		a[i].tot += T.query(n+k) - T.query(a[i].d);
	}
	for (int i=mid+1; i<j; i++){
		T.add(a[i].c, -1);
	}
}
signed main(){
	scanf ("%lld%lld", &n, &k);
	for (int i=1; i<=n; i++){
		scanf ("%lld", &tmp);
		a[tmp].x = i;
		a[i].c = i, a[i].d = i + k;
	}
	for (int i=1; i<=n; i++){
		scanf ("%lld", &tmp);
		a[tmp].y = i;
	}
	sort (a+1, a+n+1, cmp1);
	cdq1(1, n);
	sort (a+1, a+n+1, cmp2);
	cdq2(1, n);
	for (int i=1; i<=n; i++){
		ans += a[i].tot;
	}
	printf ("%lld\n", ans);
	return 0;
}
```

---

## 作者：kczno1 (赞：1)

设两个序列为a,b。

b中位置i,j被计算

满足的条件就是

i<j
i对应的a中的位置>j对应的

|b[i]-b[j]|>k
这是一个三维偏序问题。

可以按顺序枚举一维，用kd-tree维护其他两维。

时间O(nlog^2)


因为kd-tree似乎会比cdq分治慢一些

所以这题会比较卡常(本机跑的1.1s)

所以我过不了。。

```cpp
# pragma opitimie "O2"
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i,n) for(int i=1;i<=n;++i)
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}

const int N=1e5+5;
int n,dya[N]; 
struct node
{
    int b,dy;//dy=b中位置i对应的a中位置
    node *f,*cl,*cr;
    int mndy,mxdy,mxb,mnb,s;bool live;
}T[N];
node *q[N],*now,*rt;

const int L=2000;
int nl,nr,ndy;ll ans;
#define ok(mndy,mxb,mnb) (mndy>ndy&&(mxb<nl||mnb>nr))
void qiu()
{
    static node *q[L];
    q[1]=rt;
    int tail=1;
    for(int head=1;head<=tail;++head)
    {
     node *x=q[head];
     if(!x->s)continue;
     if(x->mxdy<ndy)continue;
     if(x->mnb>=nl&&x->mxb<=nr)continue;
     if(ok(x->mndy,x->mxb,x->mnb)){ans+=x->s;continue;}
     if(x->live)
     {
        if(ok(x->dy,x->b,x->b)) ++ans;
     }
     if(x->cl)q[++tail]=x->cl;
     if(x->cr)q[++tail]=x->cr;
    }
}
void modify()
{
    int nb=now->b;
    now->live=1;
    for(node *x=now;x;x=x->f)
    {
        if(++x->s==1) {x->mndy=x->mxdy=ndy;x->mnb=x->mxb=nb;}
        else 
        {
            if(x->mndy>ndy)x->mndy=ndy; else
            if(x->mxdy<ndy)x->mxdy=ndy;
            if(x->mnb>nb)x->mnb=nb; else
            if(x->mxb<nb)x->mxb=nb;
        }
    }
}

bool dy_xiao(node *x,node *y)
{
    return x->dy<y->dy;
}
bool b_xiao(node *x,node *y)
{
    return x->b<y->b;
}
node* build(int l,int r,bool d)
{
    int mid=l+r>>1;
    nth_element(q+l,q+mid,q+r+1,!d?dy_xiao:b_xiao);
    node *rt=q[mid];
    if(l!=mid)(rt->cl=build(l,mid-1,!d))->f=rt;
    if(r!=mid)(rt->cr=build(mid+1,r,!d))->f=rt;
    return rt;
}

int main()
{
    n=read();int k=read();
    rep(i,n)dya[read()]=i;
    rep(i,n)T[i].dy=dya[T[i].b=read()];
    
    rep(i,n)q[i]=T+i;
    rt=build(1,n,0);
    
    rep(i,n)
    {
        now=T+i;
        nl=now->b-k;nr=now->b+k;ndy=now->dy;
        qiu();
        modify();
    }
    printf("%lld\n",ans);
}
```

---

## 作者：CQ_Bab (赞：0)

# 主要思路
`cdq` 分治。
# 思路
我们可以从某些不知名渠道中得知这道题是 `cdq` 分治，那么我们就可以来想一下三个条件了。

- 因为那两条线一定要相交，所以我们就要让 $p1_x<p2_x$ 并且 $p1_y>p2_y$ 而 $p1_i$ 和 $p2_i$ 数组表示 $i$ 在第一个数组和第二个数组中的位置。
- $|x-y|>k$ 这个其实就那树状数组枚举就好了。

所以这道题我们就可以化简成一个[三维偏序](https://www.luogu.com.cn/problem/P3810)那道题了，我们只需要现将 $p1$ 和 $p2$ 从排序来处理然后再用一个树状数组来处理后面那个了，我们可以发现对于答案要分两种情况讨论因为可以 $x$ 大或者 $y$ 大。
# 代码
```
#include <bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rep1(i,x,y) for(int i=x;i>=y;--i)
#define int long long
#define gh int
#define ru(x) cin>>x
using namespace std ;
const int N=2e6+10;
int tr[N],n,k,res;
struct node {
	int x,y;
	int val;
} s[N];
int lowbit(int x) {
	return x&-x;
}
int Ans(int x) {
	x=max(x,0ll);
	x=min(x,n);
	int res=0;
	while(x) {
		res+=tr[x];
		x-=lowbit(x);
	}
	return res;
}
void add(int x,int k) {
	while(x<=n) {
		tr[x]+=k;
		x+=lowbit(x);
	}
}
bool cmp(node a,node b) {
	return a.x<b.x;
}
bool cmp1(node a,node b) {
	return a.y>b.y;
}
void cdq(int l,int r) {//模板
	if(l==r) return ;
	int mid=l+r>>1;
	cdq(l,mid);
	cdq(mid+1,r);
	sort(s+l,s+1+mid,cmp1);
	sort(s+1+mid,s+1+r,cmp1);
	int j=l;
	rep(i,mid+1,r) {
		while(j<=mid&&s[j].y>s[i].y) {
			add(s[j].val,1);
			j++;
		}
		res+=Ans(s[i].val-k-1)+Ans(n)-Ans(s[i].val+k); //分两种情况讨论
	}
	rep(i,l,j-1) add(s[i].val,-1); //为了不改变清零
}
signed main() {
	ru(n),ru(k);
	rep(i,1,n) {
		gh x;
		ru(x);
		s[x].val=x;
		s[x].x=i;
	}
	rep(i,1,n) {
		gh x;
		ru(x);
		s[x].y=i;
	}
	sort(s+1,s+1+n,cmp); //先按第一维排序
	cdq(1,n);
	cout<<res<<endl;
	return false;
}

```

---

## 作者：hgzxwzf (赞：0)

## 解题思路：
题目要求满足三个条件的点对 $(i,j)$ 数：

$\begin{cases}a_i>b_i\\a_j<b_j\\|i-j|>k\end{cases}$

$a_i$ 和 $b_i$ 分别表示 $i$ 排列 $A$ 和排列 $B$ 中的位置，因为把相同的数连起来，两条连线相交，所以要满足前两个式子。

这是一个关于数对 $(x,y,z)$ 的三维偏序，所以我们可以用 cdq 分治（[模板题](https://www.luogu.com.cn/problem/P3810)）解决。

$x$ 为某个数字在 $A$ 中的位置，$y$ 为这个数字在 $B$ 中的位置，$z$ 为这个数字。

首先通过第一关键字和第二关键字的处理方法和模板一样，对于第三维，用树状数组维护：
```cpp
ans+=query(n)-(query(no[i].c+k)-query(no[i].c-k-1));
```
运用了查分前缀和的思想，$sum[1,c-k-1]+sum[c+k+1,n]=sum[1,n]-(sum[1,c+k]-sum[1,c-k-1])$。

最后注意两个点：

1、注意树状数组查询时的定义域要控制在 $[0,n]$。

2、记得 $ans$ 开 long long，不然 wa 第 $2$ 个点。

```cpp
#include<cstdio>
#include<algorithm>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=z;x>=y;x--)
using namespace std;
const int N=1e5+10;
struct node
{
	int a,b,c;
}no[N];
int MAP[N];
long long ans;
int t[N],n,k;
inline void add(int i,int x) {while(i<=n) t[i]+=x,i+=i&-i;}
inline int query(int i) {i=min(i,n);i=max(i,0);int sum=0;while(i) sum+=t[i],i-=i&-i;return sum;}
bool comp(const node &P,const node &Q) {return P.a!=Q.a?(P.a<Q.a):(P.b!=Q.b?P.b>Q.b:P.c<Q.c);}
bool comp2(const node &P,const node &Q) {return P.b!=Q.b?P.b>Q.b:P.c<Q.c;}
void CDQ(int l,int r)
{
	if(l==r) return ;
	int mid=l+r>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	sort(no+l,no+mid+1,comp2);//[l,mid]
	sort(no+mid+1,no+r+1,comp2);//[mid+1,r]
	int j=l;
	rep(i,mid+1,r)
	{
		while(j<=mid&&no[j].b>no[i].b) add(no[j].c,1),j++;
		ans+=query(n)-(query(no[i].c+k)-query(no[i].c-k-1));//[1,no[i].c-k],[no[i].c+k,n]
	}
	rep(i,l,j-1) add(no[i].c,-1);
}
int main()
{
	scanf("%d%d",&n,&k);
	rep(i,1,n) {int x;scanf("%d",&x);MAP[x]=i;}
	rep(i,1,n)
	{
		int x;
		scanf("%d",&x);
		no[i]=(node) {MAP[x],i,x};
	}
	sort(no+1,no+1+n,comp);
	CDQ(1,n);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：AlicX (赞：0)

### Solution

先讲暴力。在第一个数列中枚举位置，同时在第二个数列中枚举位置，用一个数组表示这个数在下一个序列中出现的位置，最后判断是不是交叉相等就可以了。

正解也很明显，观察到决定答案的因素有以下三个东西：

1. 数 $i$ 在第一个数列中出现的位置小于 $j$ 在第一个数列中出现的位置。

2. 数 $i$ 在第一个数列中出现的位置大于 $j$ 在第一个数列中出现的位置。

3. $i$ 和 $j$ 的绝对值大于 $k$。

我们发现前两点可以判断他们是否交叉相等，而第三个要求显然可以用树状数组或者线段树求。

注意：求的时候有可能越界，注意判断。

##  Code


```cpp
#include<bits/stdc++.h>
#define int long long 
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=1e5+10;
int n,k;
int f[N]; 
int ans=0;
int tr1[N],tr2[N];
int read(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9') f=(ch=='-')?-1:1,ch=getchar();
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
struct Node{ 
	int w; 
	int x,y; 
}a[N]; 
inline int lowbit(int x){ return x&-x; }
inline bool cmp1(Node a,Node b){
	return a.x<b.x;
}
inline bool cmp2(Node a,Node b){
	return a.y>b.y;
} 
inline void add1(int x,int val){
	for(int i=x;i<=n;i+=lowbit(i)) tr1[i]+=val;  
}
inline int query1(int x){
	if(x<1) return 0; int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=tr1[i];
	return res;
}
inline void add2(int x,int val){
	for(int i=x;i;i-=lowbit(i)) tr2[i]+=val;
}
inline int query2(int x){
	if(x>n) return 0; int res=0;
	for(int i=x;i<=n;i+=lowbit(i)) res+=tr2[i];
	return res;
}
inline void CDQ(int l,int r){
	if(l==r) return ;
	int mid=l+r>>1,j=l;
	CDQ(l,mid),CDQ(mid+1,r); 
	sort(a+l,a+mid+1,cmp2); 
	sort(a+mid+1,a+r+1,cmp2);
	for(int i=mid+1;i<=r;i++){ 
		while(j<=mid&&a[j].y>a[i].y) add1(a[j].w,1),add2(a[j].w,1),j++; 
		ans+=query1(a[i].w-k-1)+query2(a[i].w+k+1); 
	} for(int i=l;i<j;i++) add1(a[i].w,-1),add2(a[i].w,-1); 
}
signed main(){
	n=read(),k=read(); 
	for(int i=1,x;i<=n;i++) x=read(),a[x].x=i,a[x].w=x;
	for(int i=1,x;i<=n;i++) x=read(),a[x].y=i;
	sort(a+1,a+n+1,cmp1); CDQ(1,n); printf("%lld\n",ans);
	return 0; 
}/*
4 1
4 3 2 1 
1 4 2 3  



*/
```


---

