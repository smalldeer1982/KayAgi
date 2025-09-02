# Sereja and Array

## 题目描述

Sereja has got an array, consisting of $ n $ integers, $ a_{1},a_{2},...,a_{n} $ . Sereja is an active boy, so he is now going to complete $ m $ operations. Each operation will have one of the three forms:

1. Make $ v_{i} $ -th array element equal to $ x_{i} $ . In other words, perform the assignment $ a_{vi}=x_{i} $ .
2. Increase each array element by $ y_{i} $ . In other words, perform $ n $ assignments $ a_{i}=a_{i}+y_{i} $ $ (1<=i<=n) $ .
3. Take a piece of paper and write out the $ q_{i} $ -th array element. That is, the element $ a_{qi} $ .

Help Sereja, complete all his operations.

## 样例 #1

### 输入

```
10 11
1 2 3 4 5 6 7 8 9 10
3 2
3 9
2 10
3 1
3 10
1 1 10
2 10
2 10
3 1
3 10
3 9
```

### 输出

```
2
9
11
20
30
40
39
```

# 题解

## 作者：幽界の冥神 (赞：3)

这题真的是紫题么？？？

看到的第一想法显然是线段树，可是我不会啊~~

再看一下，我们想到了——

# 暴力

就按题目说的做就行了，唯一的优化就是将每次累加的值累计在$pos$中，每次输出的时候加一下就行了。

还要注意 ：修改时，修改值要记得减去$pos$

代码很短 ： 

```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>

#define N 100005

using namespace std;

int n, m;
long long a[N], pos;

int main () {
	scanf ("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf ("%lld", a + i);
	for (int i = 1, opt, v, x; i <= m; ++i) {
		scanf ("%d", &opt);
		switch (opt) {
			case 1 : scanf ("%d%d", &v, &x); a[v] = x - pos; break;
			case 2 : scanf ("%d", &x); pos += x; break;
			case 3 : scanf ("%d", &x); printf ("%lld\n", a[x] + pos); break;
		}
	}
	return 0;
}
```

---

## 作者：Transparent (赞：1)

看见有人用
$\large\text{}$
$\large\text{暴力}$
做。

可是，像我这样不愿过多思考的蒟蒻，只想到了线段树。

还没有人发
$\large\text{线段树}$的题解，我就发一篇吧！

很裸的一个$\large\text{线段树}$。


------------
![](https://gss1.bdstatic.com/-vo3dSag_xI4khGkpoWK1HF6hhy/baike/c0%3Dbaike92%2C5%2C5%2C92%2C30/sign=0622b6a868600c33e474d69a7b253a6a/bd3eb13533fa828bcb5fe85ffe1f4134970a5a09.jpg)

大概长这样（图选自[百度百科](https://baike.baidu.com/item/%E7%BA%BF%E6%AE%B5%E6%A0%91/10983506?fr=aladdin)）

每一个节点维护一段区间的信息（如：和，最值）。

普通线段树可以处理区间询问，单点修改，单次询问时间复杂度$O(log n)$。

通过Lazy-Tag+标记下传可以在$O(log n)$的时间内完成区间修改。


------------

本题需要维护区间的和。

**操作1**：单点修改。

**操作2**：区间修改。

**操作3**：单点询问。（不就是区间询问吗？？？）



------------
完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll sum[400004],num[100001],add[400004],n,m;
void build(ll k,ll l,ll r)
{
	if(l==r)
	{
		sum[k]=num[l];
		return;
	}
	ll mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
inline void Add(ll k,ll l,ll r,ll v)
{
	add[k]+=v;
	sum[k]+=v*(r-l+1);
}
inline void pushdown(ll k,ll l,ll r,ll mid)
{
	if(add[k]==0)
	return;
	Add(k<<1,l,mid,add[k]);
	Add(k<<1|1,mid+1,r,add[k]);
	add[k]=0;
}
ll query(ll k,ll l,ll r,ll x,ll y)
{
	if(l>=x&&r<=y)
	return sum[k];
	ll mid=(l+r)>>1;
	ll res=0;
	pushdown(k,l,r,mid);
	if(x<=mid)res+=query(k<<1,l,mid,x,y);
	if(mid<y)res+=query(k<<1|1,mid+1,r,x,y);
	return res;
}
void change(ll k,ll l,ll r,ll x,ll v)
{
	if(r<x||l>x)
		return;
	if(l==r&&l==x)
	{
		sum[k]=v;
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(k,l,r,mid);
	change(k<<1,l,mid,x,v);
	change(k<<1|1,mid+1,r,x,v);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
void modify(ll k,ll l,ll r,ll x,ll y,ll v)
{
	if(l>=x&&r<=y)
	{
		Add(k,l,r,v);
		return;
	}
	ll mid=(l+r)>>1;
	pushdown(k,l,r,mid);
	if(x<=mid)modify(k<<1,l,mid,x,y,v);
	if(mid<y)modify(k<<1|1,mid+1,r,x,y,v);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
int main()
{
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=n;i++)
	scanf("%lld",num+i);
	build(1,1,n);
	while(m--)
	{
		ll s,i,x;
		scanf("%lld",&s);
		if(s==1)
		{
			scanf("%lld%lld",&i,&x);
			change(1,1,n,i,x);
		}
		if(s==2)
		{
			scanf("%lld",&x);
			modify(1,1,n,1,n,x);
		}
		if(s==3)
		{
			scanf("%lld",&x);
			printf("%lld\n",query(1,1,n,x,x));
		}
	}
	return 0;
}
```
最后吐槽一下：这种题能被评上$\color{#9d3dd2}\text{省选/NOI-}$？？？？？

---

## 作者：Sternenlicht (赞：0)

题目大意：

给定一个长度为 $n$ 的 $a$ 数组，有 $m$ 次操作。

操作 1：输入 $x$ 和 $y$，将 $a_x$ 赋为 $y$。

操作 2：输入 $x$，将 $a$ 数组中的每个数都加上 $x$。

操作 3：输入 $x$，输出 $a_x$ 的值。

思路：

依题意模拟即可。

因 $n \le 10^5$，$O(n^2)$ 的算法会超时，所以要考虑优化。

将操作 2 中输入的值都加入 $sum$ 变量中，操作 1 修改时将 $y$ 减去 $sum$，操作 3 将输出的值加上 $sum$ 即可。

```cpp
#include <bits/stdc++.h>
//包装好的快读快写
#define LL long long
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
}
using namespace IO;
using namespace std;

const int N = 1e5+10;
int a[N],n,m,sum;
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++)a[i]=read();
	for (int i=1;i<=m;i++){
		int opt=read(),x=read(),y;
		if (opt==1)y=read(),a[x]=y-sum;
		if (opt==2)sum+=x;
		if (opt==3)write(a[x]+sum);
	}
	return 0;
}

---

## 作者：PeterBei (赞：0)

这题看起来很像线段树，但仔细读一下题就会发现里面根本不是区间加减，而是要整体进行加减……

那只需要一个 $cnt$ 记录一下每次给整体加上的值就行了。

需要注意要给每一次修改的值减去当前的 $cnt$，因为改过的数应该不会被前面的加减所影响，即使有可能出现负数也是正常情况，反正最后加 $cnt$ 的时候会补齐成正数。

建议结合代码来看分析，原代码：

```
#include<iostream>
#include<cstring>
using namespace std;

int a[100100];
long long cnt = 0;

int mian()
{
    int n = 0, m = 0;

    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}
	
	int x = 0, y = 0, z = 0;
	for(int i = 1; i <= m; i++)
	{
		scanf("%d%d", &x, &y);
		if(x == 1)
		{
			scanf("%d", &z);
			a[y] = z - cnt;
		}
		else if(x == 2)
		{
			cnt += y;
		}
		else if(x == 3)
		{
			printf("%d\n", a[y] + cnt);
		}
	}

    return 0;
}
```

---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF315B)

又是一道暴力枚举题。


------------
### 分析

做题先要看数据，这样可以判定用线段树还是暴力。很显然，数据这么大，如果第二种操作暴力用双重循环肯定 ```TLE``` 。所以如果我们用暴力的话，必须想办法优化。


------------
### 优化与步骤

经过一段时间的发现，我们做第二种操作时并不需要每次循环去改变数组里面的值，可以用一个变量 ```pos``` 去记录每次调整的值，也就是说 ```pos``` 里面存储着每次累加的值，最后输出的时候需加上 ```pos``` 就行了。

我们一步步来实现。

1. 把 ```a[i]``` 赋值为 ```x``` 。

这一步没什么好说的，只需要注意修改时得减去 ```pos``` 。

```
if(choose==1){
    long long sub,x;
    scanf("%lld%lld",&sub,&x);
    a[sub]=x-pos;
}
```

2. 把数组 ```a``` 里面每个数加 ```x``` 。

按照上面说的，累加需要修改的值。

```
else if(choose==2){
    long long x;
    scanf("%lld",&x);
    pos+=x;
}
```

3. 查询数组中的某个元素。

这也很简单，不过输出时记得的加上 ```pos``` 。
```
else if(choose==3){
    long long x;
    scanf("%lld",&x);
    printf("%lld\n",a[x]+pos);
}
```



------------
### 完整 ```AC``` 代码

```
#include<iostream>
#include<cstdio>
using namespace std;
long long n,m,a[100010],pos;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(long long i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(long long i=1;i<=m;i++){
        long long choose;
        scanf("%lld",&choose);
        if(choose==1){
            long long sub,x;
            scanf("%lld%lld",&sub,&x);
            a[sub]=x-pos;
        }else if(choose==2){
            long long x;
            scanf("%lld",&x);
            pos+=x;
        }else if(choose==3){
            long long x;
            scanf("%lld",&x);
            printf("%lld\n",a[x]+pos);
        }
    }
    return 0;
}
```


---

## 作者：fjy666 (赞：0)

### 0x01 思路
考虑 **树状数组**。  
这题和 [【模板】树状数组2](https://www.luogu.com.cn/problem/P3368) 很像，都是 **区间加法** 和 **单点查询**。  

对于操作 $2$ ，给整个序列加上 $x$ 即可。  
对于操作 $3$ ，单点查询 $x$ 即可。  

操作 $1$ 最复杂。  
考虑怎么将 单点赋值 转化成 区间加法呢？  
首先，把 区间加法 转化成 单点加法。  
这很容易，因为我们知道 单点加法 就是加一个长度为 $1$ 的区间。  
然后，把 单点赋值 转化成 单点加法。  
设原来的值为 $p$ ，新的值为 $p$  
则我们要把 $p \gets q$  
转化成 $p \gets p + x$。  
显然， $x \gets q - p$。  
这样，我们就成功把 单点赋值 转化为 区间加法 了！

有一个坑点：**要开long long**！  
时间复杂度：$\Theta(m\times\log n)$，常数极小。

------------
### 0x02 代码
```cpp
#include <cstdio>
#include <cstdlib>
#define fo(i_,j_,k_) for(int i_=j_;i_<=k_;++i_)
#define fr(i_,j_,k_) for(int i_=j_;i_>=k_;--i_)
#define It(type_) type_::iterator
#define rg register
#define rtn return
#define il inline

typedef long long ll;
const int kMaxn = 100005;
ll arr[kMaxn];
int n,m,ID,IsHaveTypeI,IsHaveTypeII;
struct query
{
	int id;
	ll a,b;
	void Scan(void)
	{
		scanf("%d",&id);
		if(id==1)scanf("%lld%lld",&a,&b);
		else scanf("%lld",&a);
	}
}q[kMaxn];

void Init(void)
{
	scanf("%d%d",&n,&m);
	fo(i,1,n)
		scanf("%lld",arr+i);
	fo(i,1,m)
	{
		q[i].Scan();
		if(q[i].id==1)
			IsHaveTypeI = 1;
		if(q[i].id==2)
			IsHaveTypeII = 1;
	}
}

namespace SubtaskI
{
	void Solve(void)
	{
		fo(i,1,m)
		{
			if(q[i].id==1)arr[q[i].a]=q[i].b;
			if(q[i].id==2)fo(j,1,n)arr[j]+=q[i].a;
			if(q[i].id==3)printf("%lld\n",arr[q[i].a]);
		}
		exit(0);
	}
}
namespace SubtaskII
{
	void Solve(void)
	{
		ll add=0;
		fo(i,1,m)
		{
			if(q[i].id==2)add+=q[i].a;
			if(q[i].id==3)printf("%lld\n",arr[q[i].a]+add);
		}
		exit(0);
	}
}

namespace SubtaskIII
{
#define lowbit(x) (x&-x)
	ll c[kMaxn];
	void Add(int ind,ll add)
	{
		for(;ind<=n;ind+=lowbit(ind))
			c[ind]+=add;
	}
	ll Query(int x)
	{
		ll sum=0;
		for(;x;x-=lowbit(x))
			sum+=c[x];
		rtn sum;
	}
	void Solve(void)
	{
		fo(i,1,n)
			Add(i,arr[i]-arr[i-1]);
		fo(i,1,m)
		{
			if(q[i].id==1)
			{
				ll T = q[i].b - Query(q[i].a);
				Add(q[i].a,T);
				Add(q[i].a+1,-T);
			}
			if(q[i].id==2)Add(1,q[i].a);
			if(q[i].id==3)printf("%lld\n",Query(q[i].a));
		}
	}
		
}

int main()
{
// 	freopen("array.in","r",stdin);
// 	freopen("array.out","w",stdout);
	Init();
	if((n<=1000&&m<=1000) || (IsHaveTypeII == 0))
		SubtaskI::Solve();
	else if(IsHaveTypeI == 0)
		SubtaskII::Solve(); 
	else
		SubtaskIII::Solve();
    rtn 0;
}
```
请自行忽略 $\texttt {SubtastI}\ \&\ \texttt{SubtastII}$。

---

## 作者：YUYGFGG (赞：0)

看到第一眼——线段树？？？

~~出于pj-~~ 我不会，只好直接打暴力
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a;
void pls(int x){
    for(int i=0;i<a.size();i++){
        a[i]+=x;
    }
}
int main(){
    int n,m,x,op,k;
    cin>>n>>m;
    for (int i=0;i<n;i++){
        cin>>x;
        a.push_back(x);
    }
    for (int i=0;i<m;i++){
        cin>>op;
        if(op==3){
            cin>>x;
            cout<<a[x-1]<<endl;
        }
        if(op==2){
            cin>>x;
            pls(x);
        }
        if(op==1){
            cin>>x>>k;
            a[x-1]=k;
        }
    }
}
```
恭喜：![](https://tva1.sinaimg.cn/large/007S8ZIlgy1genlcefdyyj312i0a6wex.jpg)

于是肯定要加一点优化，但我不会线段树，于是：

- 经过简单观察，发现操作2号耗时最大，就想办法优化

基本思路：由于是全数组而非部分+，可以用```pos```	变量记录“调整量”，使得不需要每一次操作2都遍历一遍数组
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> a;
int main(){
    int n,m,x,op,k,pos=0;
    cin>>n>>m;
    for (int i=0;i<n;i++){
        cin>>x;
        a.push_back(x);
    }
    for (int i=0;i<m;i++){
        cin>>op;
        if(op==3){
            cin>>x;
            cout<<a[x-1]+pos<<endl;//输出时加上“调整量”
        }
        if(op==2){
            cin>>x;
            pos+=x;//调整量增加
        }
        if(op==1){
            cin>>x>>k;
            a[x-1]=k-pos;//直接赋值，要取消调整量的影响，需要减去调整量，否则后面如果要输出是会多“当前的pos”
        }
    }
}

```


---

