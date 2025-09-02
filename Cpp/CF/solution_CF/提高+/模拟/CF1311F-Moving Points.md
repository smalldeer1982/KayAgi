# Moving Points

## 题目描述

在数轴 $OX$ 上有 $n$ 个点。第 $i$ 个点最初在坐标 $x_i$， 并且有一个速度 $v_i$。没有两个点的坐标是相同的。所有的的都安装不变的速度移动，第 $i$ 个点在 $t$ 时刻的坐标为 $x_i + t \cdot v_i$ （$t$ 可能不是整数）。

对于两个点 $i$ 和 $j$，设 $d(i,j)$ 为 $i$ 和 $j$ 在任意时刻下的可能的最小距离（时刻可能不是整数）。如果 $i$ 和 $j$ 在某一时刻重合，那么 $d(i,j)=0$。

你的任务是计算出下面这个式子的值（对于任意两个点的最小距离之和）：
$$
\sum_{1\leq i < j \leq n}d(i,j)
$$

## 样例 #1

### 输入

```
3
1 3 2
-100 2 3```

### 输出

```
3```

## 样例 #2

### 输入

```
5
2 1 4 3 5
2 2 2 3 4```

### 输出

```
19```

## 样例 #3

### 输入

```
2
2 1
-3 0```

### 输出

```
0```

# 题解

## 作者：Zvelig1205 (赞：15)

# 树状数组求二维偏序

[题目传送门](https://www.luogu.com.cn/problem/CF1311F)。

首先了解一下什么叫二维偏序。

二维偏序是这样一类问题：已知点对的序列 $(x_1,y_1),(x_2,y_2),\cdots,(x_n,y_n)$，在其上定义某种偏序关系 $\prec $，对于点 $(x_i,y_i)$，求满足 $(x_j,y_j)\prec(x_i,y_i)$ 的 $(x_j,y_j)$ 的数量。

是不是感觉很抽象？

举个例子：

平面上有 $n$ 个点，对于点 $(x_i,y_i)$，求满足 $x_i\le x_j\ \text{and}\ y_j\le y_i$ 的 $(x_j,y_j)$ 的数量。

试着看一下这个题：

数轴上有 $n$ 个数，对于数 $x_i$，求满足 $i< j\ \text{and}\ x_j\le x_i$ 的 $x_j$ 的数量。

这不就是逆序对吗？

而它和上边题目的区别，~~好像没什么区别~~。

所以二维偏序就可以用树状数组求逆序对的思路来解决。

那么这个题如何转化成二维偏序问题呢？

试着看样例（第二组），可以画出这样一个图：

![](https://pic.imgdb.cn/item/633141f916f2c2beb186b4ca.png)

图丑勿喷。

不妨假设 $x_i\le x_j$（题干保证 $x_i$ 互不相同，所以等号并不影响），可以发现，若 $v_i\le v_j$，则两点的最短距离为初始距离，之后越来越远；反之，最短距离为 0，即两点可以相遇。

那么问题也就转化成了：

求满足 $x_i\le x_j\ \text{and}\ v_i\le v_j$ 的点对的 $x_j-x_i$ 之和。

那么我们按照 $v$ 单调递减排序，$v$ 相同按 $x$ 单调递减排序，然后用两个树状数组分别维护点的个数和坐标之和。

查询时，先求出满足条件的点的个数 $cnt$ 和坐标之和 $sum$，那么当前点的贡献就是 $sum-cnt\times x_i$。

然后将当前点也插入到两棵树状数组中。

最后，值域为 $10^8$，建议离散化。

代码（为确保可读，我把所有压行都去了）：

```cpp
const int inf=2e5+7;
int n,ans,bok[inf];
struct node{
	int v,x;
	bool operator <(const node &b)const
	{
		return (v^b.v)?(v>b.v):(x>b.x);
	}
}a[inf];
int s[2][inf];
int lowbit(int i)
{
	return i&(-i);
}
void add(int op,int i,int k)
{
	while(i<=n)
	{
		s[op][i]+=k;
		i+=lowbit(i);
	}
}
int ask(int op,int i)
{
	int ret=0;
	while(i)
	{
		ret+=s[op][i];
		i-=lowbit(i);
	}
	return ret;
}
signed main()
{
	freopen("data.in","r",stdin);
	n=re();
	for(int i=1;i<=n;i++)
		bok[i]=a[i].x=re();
	for(int i=1;i<=n;i++)
		a[i].v=re();
	sort(bok+1,bok+n+1);
	for(int i=1;i<=n;i++)
		a[i].x=lower_bound(bok+1,bok+n+1,a[i].x)-bok;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		int sum=ask(1,n)-ask(1,a[i].x-1),
			cnt=ask(0,n)-ask(0,a[i].x-1);
		ans+=sum-cnt*bok[a[i].x];
		add(0,a[i].x,1);
		add(1,a[i].x,bok[a[i].x]);
	}
	wr(ans);
	return 0;
}
```

听说二维偏序有个大哥，叫[三维偏序](https://www.luogu.com.cn/problem/P3810)，~~不知道会不会出现四维偏序（树套树套树？）。~~

就酱紫，掰掰 (*^▽^*)。



---

## 作者：Scintilla (赞：6)

~~为何个人感觉最近的比赛最后一题都比倒数第二题简单...~~

比赛时把大于号和小于号搞反了，没调出来... 第二天早上瞬间AC，我太蒻了QAQ

好了，看题。
### **题意简述**
给定坐标轴上 $n$ 个点的初始坐标 $\{x_n\}$ 及运动速度 $\{v_n\}$ （为负数就是向左运动），令 $d(i,j)$ 表示第 $i$ 个点和第 $j$ 个点在运动过程中的距离最小值，求 $\sum_{1 \leq i < j \leq n}d(i,j)$。

### **思路**

不难发现，若 $i,j$ 在运动过程中有交点，则 $d(i,j)=0$ ；否则， $d(i,j)=|x_i - x_j|$ ，因为如果两个点开始运动时不是逐渐靠近的话，它们间的距离就不会再减少了。所以只有满足 $x_i>x_j$ 且 $v_i < v_j$ 的点对 $(i,j)$ 才对答案有贡献。

考虑把数组按 $v$ 降序排序，这样的话任意一对 $1 \leq i < j \leq n$ ，若 $x_i \geq x_j$ （这意味着 $i$ 在 $j$ 的正方向，且 $i$ 不慢 $j$ ，所以 $i$ 和 $j$ 不会相互靠近）对答案的贡献为 $x_i-x_j$，否则贡献为 $0$ 。

想到了什么？归并排序，因为这类似于求逆序对的思想。

需要特别注意的是，当 $v_i=v_j$ 时， $d(i,j)=|x_i - x_j|$ 。所以速度相等的每一对点都对答案有贡献。当 $v$ 相等时将 $x$ 降序排列，这样我们就可以没有遗漏地统计了。

总的时间复杂度是 $O(nlogn)$ 。

### **$Code:$**

（我为了~~懒~~方便，在排序后用 $sx[i]$ 代替了 $pt[i].x$ ）
```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define Rep(i, s, e) for (re int i = s; i <= e; ++i)
#define Dep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

typedef long long ll;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') f = false; c = getchar();}
    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

int n, sx[200010];
struct node {
    int x, v;
    il bool operator < (const node &tp) const  {
        return v == tp.v ? x > tp.x : v > tp.v; //之前说的排序方法以及需要注意的地方
    }
} pt[200010];

ll ans;
int tp[200010];

il void msort(int l, int r) { //归并排序
    if (l == r) return;
    int mid = (l + r) >> 1;
    msort(l, mid), msort(mid + 1, r);
    int i = l, j = mid + 1, k = l; ll sum = 0;
    Rep(ee, l, mid) sum += sx[ee]; //这里的sum是前半段的和
    while (i <= mid && j <= r) {
        if (sx[i] <= sx[j]) tp[k++] = sx[i], sum -= sx[i++]; //i往后跳一个，sum相应减少
        else tp[k++] = sx[j], ans += sum - 1ll * sx[j++] * (mid - i + 1); //即统计贡献 (sx[i] - sx[j]) + (sx[i + 1] - sx[j]) + ... + (sx[mid] - sx[j])。
    }                                                                     //把每个括号的第一项合起来就是sum，后一项合起来就是sx[j] * (mid - i + 1)。 要开long long，不然会炸。
    while (i <= mid) tp[k++] = sx[i++];
    while (j <= r) tp[k++] = sx[j++];
    Rep(i, l, r) sx[i] = tp[i];
}

int main() {
    n = read();
    Rep(i, 1, n) pt[i].x = read();
    Rep(i, 1, n) pt[i].v = read();
    std::sort(pt + 1, pt + n + 1);
    Rep(i, 1, n) sx[i] = pt[i].x;
    msort(1, n);
    printf("%lld\n", ans);
    return 0;
}
```
实在不懂的可以好好看看[这题](https://www.luogu.com.cn/problem/P1908)的题解，方法是差不多的。

祝大家早日上 $LGM!$

---

## 作者：NinT_W (赞：4)

# CF1311F Moving Points

最近在做一些真题，然后就发现 NOI Online 2022 的提高 T3 是二维偏序，然后我不会二维偏序，来学习一下。

## 题目分析

我们可以把题目分为三种情况。

1. $ x_i < x_j $ 且 $ v_i \leq v_j $，那目前的距离就是最近的距离。

2. $ x_i < x_j $ 且 $ v_i >v_j $，两者会相遇，最近距离为 0。

3. $ x_j < x_j $ 且 $ v_i > 0,v_j<0 $，二者会相遇，最近距离为 0。

不难看出只有第一种情况会产生贡献。

我们用树状数组进行二维偏序。

设小于当前 $ v $ 的节点个数为 $ A $，原点到前 $ i $ 个点的距离之和为 $ B $，不难推出 $ ans=\sum x_i \times A-B $。

用两个树状数组维护即可。

AC code

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#define int long long

using namespace std;

const int maxn=2e5+5;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9')
	{
		if(ch=='-')
		{
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
	{
		w=(w<<3)+(w<<1)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

int n,ans;

int b[maxn];

int t[3][maxn];

struct node
{
	int x,v;
}nod[maxn];

bool cmp(node a,node b)
{
	if(a.x!=b.x)
	{
		return a.x<b.x;
	}
	return a.v<b.v;
}

int lowbit(int x)
{
	return x&-x;
}

void update(int x,int y,int t[])
{
	for(;x<maxn;x+=lowbit(x))
	{
		t[x]+=y;
	}
}

int query(int x,int t[])
{
	int ans=0;
	for(;x;x-=lowbit(x))
	{
		ans+=t[x];
	}
	return ans;
}

signed main()
{
	n=read();
	
	for(int i=1;i<=n;i++)
	{
		nod[i].x=read();
	}
	
	for(int i=1;i<=n;i++)
	{
		nod[i].v=read();
		b[i]=nod[i].v;
	}
	
	sort(nod+1,nod+n+1,cmp);
	
	sort(b+1,b+n+1);
	
	int num=unique(b+1,b+n+1)-b-1;
	
	for(int i=1;i<=n;i++)
	{
		nod[i].v=lower_bound(b+1,b+num+1,nod[i].v)-b;
	}
	
	for(int i=1;i<=n;i++)
	{
		update(nod[i].v,nod[i].x,t[1]);
		update(nod[i].v,1,t[2]);
		ans+=nod[i].x*query(nod[i].v,t[2])-query(nod[i].v,t[1]);
	}
	
	cout<<ans;
	
	return 0;
}
```


---

## 作者：gyh20 (赞：2)

最开始看成了时间必定为整数，以为是不可做题。

结果突然发现很多 dalao 都切了 F,只有一个 dalao 切了 E，于是再去看了看题。发现时间可以是实数。

回归正题，可以发现，当 $x_i>x_j$ 且 $v_i>v_j$ 时，$d(i,j)=x_i-x_j$，因为总距离会一直增加，否则 $i,j$ 两点必定相遇。

将 $v_i$ 离散化，并按 $x$ 从小到大排序。并用两个树状数组分别维护速度为 $k$ 的 $\sum x_i^0[v_i==k]$ 和 $\sum x_i^1[v_i==k]$，每次询问得到的答案分别为 sum0,sum1。则对答案的贡献为 $sum0\times x_i-sum1$。

记得开 long long。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0,f=0;
	re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return f?-t:t;
}
struct node{
	int x,y;
}p[200002];
int r[200002],c[200002],d[200002];int n,ans;
inline bool cmp(re node x,re node y){
	return x.x<y.x;
}
inline void add(re int x,re int y){
	for(x;x<=n;x+=x&(-x))c[x]+=y;
}
inline void add1(re int x,re int y){
	for(x;x<=n;x+=x&(-x))d[x]+=y;
}
inline int ask(re int x){
	int sum=0;
	for(x;x;x-=x&(-x))sum+=c[x];
	return sum;
}
inline int ask1(re int x){
	int sum=0;
	for(x;x;x-=x&(-x))sum+=d[x];
	return sum;
}

signed main(){
	n=read();
	for(re int i=1;i<=n;++i){
		p[i].x=read();
	}
	for(re int i=1;i<=n;++i)r[i]=p[i].y=read();
	sort(r+1,r+n+1);
	int m=unique(r+1,r+n+1)-r-1;
	for(re int i=1;i<=n;++i){
		p[i].y=lower_bound(r+1,r+m+1,p[i].y)-r;
	}
	sort(p+1,p+n+1,cmp);
	for(re int i=1;i<=n;++i){
		int tmp=ask(p[i].y),tmp1=ask1(p[i].y);
		ans+=tmp1*p[i].x-tmp;
		add(p[i].y,p[i].x),add1(p[i].y,1);
	}
	printf("%lld",ans);
}
```


---

## 作者：JRzyh (赞：2)

$$Part~1\text{说句闲话}$$

我是在逛某大佬blog时，发现了这题的题解，当时正在找一些有难度的BIT题目，于是就来做了做（结果还因为离散化板子错了调了一天qwq)。又因为想涨社区贡献所以打了这么一篇题解（不过话说这题蓝是不是过了）。

$$Part~2\text{前置知识}$$


[不会追及问题的~~建议跳楼~~](http://baidu.apphb.com/?q=%E8%BF%BD%E5%8F%8A%E9%97%AE%E9%A2%98)

[不会树状数组的](http://baidu.apphb.com/?q=%E6%A0%91%E7%8A%B6%E6%95%B0%E7%BB%84)

[不会离散化的](http://baidu.apphb.com/?q=%E7%A6%BB%E6%95%A3%E5%8C%96)

$$Part~3\text{做法讲解}$$


现有两点 $i,j$ 且$x_i<x_j$ , $v$ 的关系可能有如下情况：

1. $v_i\le v_j$  
 这种情况他们的距离肯定越来越大（等于时不变），所以$d(i,j)=x_j-x_i$

2. $v_i> v_j$  
	这种情况一定会追上，$d(i,j)=0$
    
所以最后答案为$\large\sum_{x_i<x_j\&v_i\le v_j}(x_i-x_j)$

首先按 $x$ 排序，能保证 $x_i<x_j$

将 $v$ 离散化，建立两个BIT（线段树常数大空间大还难写不建议用）一个维护速度为 $i$ 的坐标和，一个维护速度为 $i$ 的数量。设BIT1从 $1$ 到 $v_i$ 的和是$ans1$,BIT2从 $1$ 到 $v_i$ 的和是$ans2$。最后的答案就是 $ans1\times x_i-ans2$

$$Part~4\text{代码}$$

~~我知道你们就看这~~

```
#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))//个人习惯，喜欢宏定义。 
using namespace std;
//存点
struct node
{
	int x,v;
}p[200008];
// 
bool cmp(node a,node b)
{
	return a.x<b.x;
}
long long t1[200008],t2[200008],r[200008];
int n;
//树状数组1
void add(int wh,int v)
{
    for(;wh<=n;wh+=lowbit(wh)) t1[wh]+=v;
}
long long getsum(int wh)
{
    long long ans=0;
    for(;wh;wh-=lowbit(wh)) ans+=t1[wh];
    return ans;
}
//树状数组2 
void add2(int wh,int v)
{
    for(;wh<=n;wh+=lowbit(wh)) t2[wh]+=v;
}
long long getsum2(int wh)
{
    long long ans=0;
    for(;wh;wh-=lowbit(wh)) ans+=t2[wh];
    return ans;
}
//main 
long long ans;
int main()
{
	//读入
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>p[i].x;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>r[i];
		p[i].v=r[i];
	}
	//离散化 
	sort(r+1,r+n+1);
	int m=unique(r+1,r+n+1)-r-1;
	for(int i=1;i<=n;i++)
	{
		p[i].v=lower_bound(r+1,r+m+1,p[i].v)-r;
	}
	//解题 
	sort(p+1,p+n+1,cmp);
	for(int i=1;i<=n;i++)
	{
		long long tmp=getsum(p[i].v),tmp2=getsum2(p[i].v);
		ans+=tmp2*p[i].x-tmp;
		add(p[i].v,p[i].x);
		add2(p[i].v,1);
	}
	//输出
	cout<<ans;
	return 0;
} 
```
$$Part~5\text{结尾}$$

求赞OvO

![13_56b585b1a88b91c7abca426d0bc5e287.gif](https://i.loli.net/2020/03/26/qzryOs1JNB28uPh.gif)

$$Thanks~for~watching$$



---

## 作者：Erica_N_Contina (赞：1)

## 思路
本题要求任意两点中间的最小距离之和，并且没有说要在同一时间取到。所以我们可以想到，这两个点的最小距离要么是 $0$，要么是初始距离。

那么什么时候是 $0$ 呢？很容易可以知道，设这两个点为 $i,j$，如果 $x_i<x_j$ 且 $v_i>v_j$，那么 $d(i,j)=0$。就是常说的追及问题。

那么什么时候是初始距离呢？当然就是追不上的情况，即 $x_i<x_j$ 且 $v_i<v_j$。

所以本题就变成了：求所有 $i,j$ 使得 $x_i<x_j$ 且 $v_i≤v_j$，求 $x_j-x_i$。

乍一看前面的条件，那不就是二维偏序嘛（类似逆序对，只不过是顺序对）。那么我们就往二维偏序上去想。

二维偏序最常用的是什么？树状数组。回顾一下逆序对的树状数组做法是怎么样的。我们维护值域树状数组，从左往右逐渐加入 $a_i$（即在 $a_i$ 处 $+1$），并且求出树状数组中值域在 $1\sim a_i$ 的前缀和 $q_i$ 即可（树状数组维护前缀和），然后用 $i-q_i$ 就求出了下标在 $i$ 之前且值比 $a_i$ 大的数的个数。

那么本题要求的是值，而不是个数，我们就可以考虑维护两个树状数组，一个记录 $x_i$ 的大小关系，为权值树状数组，我们称之为 $A$；一个记录 $x_i$ 的值，我们称之为 $B$。

按照 $v_i$ 从小到大排序，我们遍历 $i$。当我们遍历到一个 $x_i$，我们就在 $A$ 中查询满足 $x_j<x_i$ 的 $x_j$ 的个数，记为 $cnt_i$，然后在 $B$ 中求出这些 $x_j$ 的和，我们记为 $sum_i$。那么很显然，答案应该加上 $x_i\times cnt_i-sum_i$。

最后我们将 $x_i$ 分别插入 $A,B$ 中。注意，$x_i$ 在 $B$ 中插入的相对位置应该和 $A$ 中的一样。
## 代码

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . FancyKnowledge .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//
#include<bits/stdc++.h>

//
#define int long long
#define ull unsigned long long
#define db double
#define endl '\n'
#define err(fmt, ...) fprintf(stderr, "[%d] : " fmt "\n", __LINE__, ##__VA_ARGS__)
///*
#define pr pair<double,int>
#define pf first
#define ps second
#define pb push_back
//*/

//
using namespace std;
//
const int N=2e5+5;
const int M=1e3;
const int MOD=1e9+7;
const int MMOD=903250223;
const int INF=1e9;
const int IINF=1e18;
const db eps=1e-9;
//
int n,m,x,y;

int to[N],ans;
int c[2][N<<2];//两棵树状数组

struct node{
	int x,v;
}a[N];


int lowbit(int x) {
	return x&-x;
}


void add(int f,int i,int x) {//在位置i加上x
	while(i<=n) {
		c[f][i]+=x;
		i+=lowbit(i);
	}
}


int query(int f,int x) {
	int res=0;
	while(x) {
		res+=c[f][x];
		x-=lowbit(x);
	}
	return res;
}

bool cmp(node a,node b){
	if(a.v==b.v)return a.x<b.x;//v相同时也追不上
	return a.v<b.v;
}

signed main() {
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].x;
		to[i]=a[i].x;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i].v;
	}
	sort(to+1,to+n+1);
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(to+1,to+n+1,a[i].x)-to;//离散化，将值a_i离散为第x大
	}
	
	sort(a+1,a+n+1,cmp);
	
	for(int i=1;i<=n;i++){
		int sum=query(1,a[i].x-1);
		add(1,a[i].x,to[a[i].x]);
		int cnt=query(0,a[i].x-1);
		add(0,a[i].x,1);
		ans+=cnt*to[a[i].x]-sum;
		
		
	}
	
	cout<<ans<<endl;
	return 0;
}
```


注意本题需要离散化。



注意树状数组空间大小不能只开 $n$。



---

## 作者：Jayun (赞：1)

# 链接：

[洛谷](https://www.luogu.com.cn/problem/CF1311F)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/14450368)

# 题目大意：

一条数轴上有 $n$ 个动点，每个动点的初始坐标是 $x_i$，它们每秒会向右移 $v_i$。求出所有点对最短距离之和。

# 正文：

假设我们当前正在处理点对 $(i,j)$。如果 $v_i<v_j$：

![](https://img2020.cnblogs.com/blog/1748322/202102/1748322-20210226083449098-89346816.png)

那么它们的距离会越来越远，所以初始距离则是最短距离。

---

如果 $v_i=v_j$：

![](https://img2020.cnblogs.com/blog/1748322/202102/1748322-20210226083650639-1785583060.png)

那么它们的距离不会改变，初始距离还是最短距离。

---

如果 $v_i>v_j$：

![](https://img2020.cnblogs.com/blog/1748322/202102/1748322-20210226083856297-1570371353.png)

因为时间不一定是整数，所以它们必然会走到一个点，即距离为 $0$。

那么现在可以把题目转换成：$x_i<x_j$ 且 $v_i\leq v_j$ 的点对距离和。显然是二维偏序。维护两个树状数组 $A,B$，分别维护的是已经维护了点的数量、已维护点到原点距离之和。那么答案是 $\sum A\cdot x_i-B$。

# 代码：

```cpp
const int N = 2e5 + 10;

ll t[2][N], b[N];
int n, m;
ll ans;

void modify(int x, ll val, ll t[]){for (; x <= N - 10; x += x & -x) t[x] += val;}
ll query (int x, ll t[])
{
	ll ans = 0;
	for (; x; x -= x & -x) ans += t[x];
	return ans;
}

struct node
{
	int x, v;
}a[N];

bool cmp (node a, node b) {return a.x < b.x || (a.x == b.x && a.v < b.v);}

int main ()
{
	scanf ("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf ("%d", &a[i].x);
	for (int i = 1; i <= n; i++)
		scanf ("%d", &a[i].v), b[i] = a[i].v;
	sort (a + 1, a + 1 + n, cmp);
	sort (b + 1, b + 1 + n);
	int k = unique(b + 1, b + 1 + n) - b;
	for (int i = 1; i <= n; i++)
		a[i].v = lower_bound(b + 1, b + 1 + k, a[i].v) - b;
	for (int i = 1; i <= n; i++)
	{
		modify(a[i].v, a[i].x, t[0]);
		modify(a[i].v, 1, t[1]);
		ans += query(a[i].v, t[1]) * a[i].x - query(a[i].v, t[0]);
	}
	printf ("%lld\n", ans);
	
	return 0;
}

```

---

## 作者：快斗游鹿 (赞：0)

## 思路

先来分类讨论一下，假设现在在考虑第 $i$ 个点和第 $j$ 个点，其中 $i,j$ 满足 $x_i<x_j$。

如果 $v_i\le v_j$，就意味着 $i$ 永远追不上 $j$，此时 $d(i,j)$ 为最初的 $x_j-x_i$。

否则，$i$ 一定可以追上 $j$，此时 $d(i,j)$ 为 $0$。

所以题目可以转化为，求所有满足 $x_i<x_j$ 且 $vi\le v_j$ 的 $x_j-x_i$ 的和，这是一个二维偏序问题，使用树状数组解决即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
struct Node{
	int x,v;
}e[N];
int n,a[N];
long long ans,c[N],d[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
bool cmp(Node xxx,Node yyy){
	return xxx.x<yyy.x;
}
int lowbit(int x){
	return x&-x;
}
void adda(int x,int w){
	for(x;x<=n;x+=lowbit(x))c[x]+=w;
}
void addb(int x,int w){
	for(x;x<=n;x+=lowbit(x))d[x]+=w;
}
long long aska(int x){
	long long aaa=0;
	for(x;x>0;x-=lowbit(x))aaa+=c[x];
	return aaa;
}
long long askb(int x){
	long long aaa=0;
	for(x;x>0;x-=lowbit(x))aaa+=d[x];
	return aaa;
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)e[i].x=read();
	for(int i=1;i<=n;i++)e[i].v=read(),a[i]=e[i].v;
	sort(e+1,e+1+n,cmp);
	sort(a+1,a+1+n);
	int s=unique(a+1,a+1+n)-a-1;
	for(int i=1;i<=n;i++){
		e[i].v=lower_bound(a+1,a+1+s,e[i].v)-a;
		//cout<<e[i].v<<endl;
	}
	for(int i=1;i<=n;i++){
		ans=ans+askb(e[i].v)*e[i].x-aska(e[i].v);
		adda(e[i].v,e[i].x);
		addb(e[i].v,1);
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Uuuuuur_ (赞：0)

看大家都在讨论二维偏序，树状数组。作为一个超级蒟蒻，我什么都不会，所以只能提供一种**归并排序**方法。

首先分析，如果有两个点 $A$，$B$，且 $A_x < B_x$，那么凭借我们的~~小学数学~~初中物理知识，就可以知道，当 $A_v \le B_v$ 时，$A$是追不上 $B$ 的，$AB_{min}=B_x-A_x$；反之 $A$ 就可以追上 $B$，$AB_{min}=0$（速度是负数也是满足的，可以自行验证）。

好了，那就先把所有的点**按照坐标**排个序，从左到右，对于每个点，往后面找出速度**大于等于**它的点，并且加上它们之间的距离，时间复杂度 $O(n^2)$。

或许此时，大家已经想到了一个叫**逆序对**的东西，而这里，就是求所有“顺序对”。处理逆序对有一个很有力的算法——归并排序。

现在，我们在坐标有序的前提下，对**速度**进行归并排序。

对于当前两个已排序好的数组 $M$，$N$，我们要进行合并，可以发现，与归并排序求逆序对类似，如果当前将 $M_{now}$ 并入数组，那么它就与 $N$ 中剩下的元素构成了“顺序对”，把距离算出来就好了。而算距离，我们可以利用前缀和，快速算出 $N$ 中剩下元素坐标之和，再减去元素个数乘以 $M_{now}$ 的坐标。

时间复杂度就是 $O (n\log n)$。

代码很简单。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;
int n;
ll ans;
struct node 
{
   int x;
   int v;
   bool operator < (const node &b) const {
    return x < b.x;
   } 
   bool operator <= (const node &b) const {
    return v <= b.v;
   }
};
node p[200005];
ll pre[200005];
inline ll f(int l, int r) {
    return pre[r] - pre[l - 1];
}
void merge(int l1, int r1, int l2, int r2) {
    node tmp[200005];
    int cnt = l1;
    int st = l1;
    while (l1 <= r1 && l2 <= r2) {
        if (p[l1] <= p[l2]) {
            tmp[cnt++] = p[l1];
            ans += f(l2, r2) - ll(r2 - l2 + 1) * ll(p[l1].x);
            l1++;
        } else {
            tmp[cnt++] = p[l2];
            l2++;
        }
    }
    while (l1 <= r1) {
        tmp[cnt++] = p[l1++];
    }
    while (l2 <= r2) {
        tmp[cnt++] = p[l2++];
    }
    for (int i = st; i <= r2; i++) {
        pre[i] = pre[i - 1] + tmp[i].x;
        p[i] = tmp[i];
    }
}
void merge_sort(int l, int r) {
    if (l >= r) {
        pre[l] = pre[l - 1] + p[l].x;
        return ;
    }
    int mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);
    merge(l, mid, mid + 1, r);
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i].x);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &p[i].v);
    }
    sort(p + 1, p + 1 + n);
    merge_sort(1, n);
    cout << ans;
    return 0;
} 
```


---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16810144.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1311F)
## 思路
给出一种不需要脑子的四颗树状数组解法。

这四颗树状数组分别为：一颗维护负数，一颗维护负数个数，一颗维护正数，一颗维护正数个数。

首先考虑没有速度该怎么求。

不妨先按 $x_i$ 从小到大排序，答案为 $\sum x_i \times (i-1)-sum_i$，其中 $sum_i$ 表示 $\sum_{j=1}^i x_j$。所以我们不妨先把 $ans$ 赋值为这个值。

接下来考虑加入速度。

我们只需考虑两种情况：相遇和相离，由于时间无限，所以相遇的情况 $d_{i,j}$ 一定是 $0$，而相离后的距离一定大于 $0$ 时刻的距离，所以 $d_{i,j}$ 实际只有两种情况：$0$，$|x_i-x_j|$。

我们已经把所有的 $|x_i-x_j|$ 累加入答案，接下来只需要消去 $0$ 的贡献即可。

设当前扫到的位置为 $i$：

+ 若 $v_i>0$，则此时能与 $i$ 距离为 $0$ 的点 $j$ 必定满足 $v_j>v_i$，这是简单的追及问题。
+ 若 $v_i<0$，则此时能与 $i$ 距离为 $0$ 的点 $j$ 必定满足 $v_j>0$ 或 $v_j<v_i$，$v_j>0$ 是相遇问题，$v_j<v_i$ 是追及问题。

接下来就可以简单地二维数点了，或者也可以像我一样暴力开四颗树状数组维护。
## 代码
```cpp
//A tree without skin will surely die. 
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int n,b[N],sum[N],hsum[N];
struct node{int x,v;}a[N];
struct Tree_Array{
    int c[N];
    #define lowbit(x) (x&-x)
    inline void update(int x,int v){while (x<=n) c[x]+=v,x+=lowbit(x);}
    inline int query(int x){int res=0;while (x) res+=c[x],x-=lowbit(x);return res;}
}T[5];
inline bool cmp(node a,node b){return a.x<b.x;}
signed main(){
    //读入
    sort(b+1,b+n+1);int l=unique(b+1,b+n+1)-b-1;//离散化
    for (int i=1;i<=n;++i) a[i].v=lower_bound(b+1,b+l+1,a[i].v)-b;
    sort(a+1,a+n+1,cmp);int ans=0;
    for (int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i].x;
    for (int i=n;i>=1;--i) hsum[i]=hsum[i+1]+a[i].x;
    for (int i=1;i<=n;++i) ans+=a[i].x*(i-1)-sum[i-1];
    int sum0=0,sum=0;
    for (int i=1;i<=n;i=i){
        int j=i;while (a[j+1].x==a[i].x) ++j;
        for (int k=i;k<=j;++k){
            if (!b[a[k].v]){
                ans-=a[k].x*T[3].query(n)-T[0].query(n);
                continue;
            }
            if (b[a[k].v]>0) ans-=a[k].x*(T[3].query(n)-T[3].query(a[k].v))-(T[0].query(n)-T[0].query(a[k].v));
            else ans-=a[k].x*sum0-sum+a[k].x*(T[3].query(n)+(T[4].query(n)-T[4].query(a[k].v)))-(T[0].query(n)+(T[1].query(n)-T[1].query(a[k].v)));
        }
        for (int k=i;k<=j;++k){
            if (!b[a[k].v]){
                ++sum0;
                sum+=a[k].x;
                continue;
            }
            if (b[a[k].v]>0) T[0].update(a[k].v,a[k].x),T[3].update(a[k].v,1);
            else T[1].update(a[k].v,a[k].x),T[4].update(a[k].v,1);
        }
        i=j+1;
    }
    //输出
    return 0;
}
```


---

## 作者：osfly (赞：0)

前置芝士：二维偏序。

二维偏序的板子题。

怎么看出是二维偏序的呢？

考虑点对 $(i,j)$，令 $x_i<x_j$。

若 $v_i>v_j$，则两点会越来越近，易知最短距离为 $0$，所以我们不需要考虑这种情况。

所以问题转化成：$x_i<x_j$ 且 $v_i\le v_j$ 的点对的距离和。

很明显，二维偏序，套板子就行啦。

设已维护点的数量为 $a$，距离和为 $b$，则这个点的贡献为 $x_i\times a-b$。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define int long long
struct BIT
{
	int tree[200010];
	int lowbit(int x)
	{
		return x&(-x);
	}
	void update(int x,int num)
	{
		for(int i=x;i<=200000;i+=lowbit(i)) tree[i]+=num;
	}
	int query(int x)
	{
		int res=0;
		for(int i=x;i;i-=lowbit(i)) res+=tree[i];
		return res;
	}
}t[2];
int n;
struct point
{
	int x;
	int v;
}p[200010];
int lsh[200010];
int ans;
bool cmp(point a,point b)
{
	if(a.x==b.x) return a.v<b.v;
	return a.x<b.x;
}
void init()
{
	sort(lsh+1,lsh+1+n);
	int m=unique(lsh+1,lsh+1+n)-lsh-1;
	for(int i=1;i<=n;i++) p[i].v=lower_bound(lsh+1,lsh+1+m,p[i].v)-lsh;
	sort(p+1,p+1+n,cmp);
}
signed main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&p[i].x);
	for(int i=1;i<=n;i++) scanf("%lld",&p[i].v),lsh[i]=p[i].v;
	init();
	for(int i=1;i<=n;i++)
	{
		int qwq=t[0].query(p[i].v),ry=t[1].query(p[i].v);
		ans+=ry*p[i].x-qwq;
		t[0].update(p[i].v,p[i].x),t[1].update(p[i].v,1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Mars_Dingdang (赞：0)

生日祭，一道二维偏序好题。

## 题目大意
在数轴上给定 $n$ 个点的坐标 $x_i$，以及向右移动的速度 $v_i\in [-10^8, 10^8]$，设 $d(i,j)$ 表示第 $i,j$ 个点在任意时刻的最近距离，求
$$\sum_{1\le i<j\le n}d(i,j)$$

## 大体思路
首先，对于两个点 $i,j$，不妨设 $x_i<x_j$。此时，如果 $v_i>v_j$，则 $i$ 可以在 $t=\dfrac{x_j-x_i}{v_i-v_j}$ 时间追上 $j$，因此两者最近距离 $d(i,j)=0$；如果 $v_i\le v_j$ 才会形成贡献 $d(i,j)=x_j-x_i$。

所以，本题实际上是一个二维偏序问题，对于二元组 $(x,v)$，当且仅当 $x_i<x_j$ 且 $v_i\le v_j$ 时产生贡献。

由于贡献于 $x$ 有关，一种做法是按照 $v$ 从大到小排序，当 $v$ 相等时按 $x$ 从大到小排序，这样排序后 $x_i>x_j$ 就会产生贡献。

然后，类似归并排序，假设待合并的区间为 $A=[l,mid],B=(mid,r]$，对于 $i\in A,j\in B$，若 $x_i>x_j$，则表示 $x_i\sim x_{mid}$ 均大于 $x_j$，因此贡献增加 $\sum_{k=i}^{mid}x_k-x_j$。如果用 $sum$ 累计当前 $A$ 区间中 $x$ 的后缀和，上述贡献可以写成 $sum-(mid-i+1)\cdot x_j$（当然也可以使用前缀和做差）。这样，合并时单点贡献计算的复杂度为 $O(1)$，总复杂度为 $O(n\log n)$。

注意开 `long long`。

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 2e5 + 5;
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
ll n, ans, tmp[maxn], tot;
struct node {
	ll x, v;
	bool operator <(const node &X)const{
		return v > X.v || (v == X.v && x > X.x);
	}
} p[maxn];
#define x(i) p[i].x
inline void merge(ll l, ll r) {
	if(l == r) return;
	ll mid = (l + r) >> 1;
	merge(l, mid), merge(mid + 1, r);
	ll i = l, j = mid + 1, tot = l - 1;
	ll sum = 0;
	rep(k, l, mid) sum += x(k);
	while(i <= mid && j <= r) {
		if(x(i) <= x(j)) {
			tmp[++tot] = x(i);
			sum -= x(i);
			i ++;
		} else {
			tmp[++tot] = x(j);
			ans += sum - x(j) * (mid - i + 1);
			j ++;
		}
	}
	while(i <= mid) tmp[++tot] = x(i ++);
	while(j <= r) tmp[++tot] = x(j ++);
	rep(k, l, r) x(k) = tmp[k];
}
int main () {
	read(n);
	rep(i, 1, n) read(p[i].x);
	rep(i, 1, n) read(p[i].v);
	sort(p + 1, p + n + 1);
	merge(1, n);
	writeln(ans);
		
	return 0;
}
```

---

## 作者：极寒神冰 (赞：0)

将每一个点的速度和位置组成一个二元组$(v,x)$，升序排序后

假设一个点的位置为$i$,第一个大于等于这个坐标为$pos$那么这个点的贡献为

$$ (pos-n+i-1)\times pos$$

加起来即为答案

```
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb push_back
#define pii pair<int,int> 
#define mkp make_pair
#define Max(a,b) ((a>b)?a:b)
#define us unsigned 
#define int long long
using namespace std;
const int inf=1e18;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=2e5+10;
int n,a[N],res;
pii v[N];
signed main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) v[i]=mkp(read(),a[i]);
	sort(a+1,a+n+1);
	sort(v+1,v+n+1);
	for(int i=1;i<=n;i++)
		res+=(lower_bound(a+1,a+n+1,v[i].second)-a-n+i-1)*v[i].second;
	printf("%lld\n",res);
}
```




---

## 作者：章烨凯 (赞：0)

### 分析

可以发现， $t$ 时刻两个点 $i$ 和 $j(x_i<x_j)$ 的距离

$=abs((x_i+t\cdot v_i)-(x_j+t\cdot v_j))=abs((x_i-x_j)+t\cdot (v_i-v_j))$

令 $y=(x_i-x_j)+t*(v_i-v_j)$ ，那么可以得到：

当 $v_i>v_j$ 时 $y$ 单调递增，存在一个 $t=\dfrac{(x_j-x_i)}{(v_i-v_j)}$ 使得 $y=0$ ，即 $abs(y)=0$ 。

当 $v_i=v_j$ 时 $y$ 为常数，即 $y=x_i-x_j,abs(y)=x_j-x_i$ 。

当 $v_i<v_j$ 时 y单调递减，$y\le x_i-x_j,abs(y)\ge x_j-x_i$ 。

综上所述，当 $v_i>v_j$ 时 $d(i,j)=0$ ,否则 $d(i,j)=x_j-x_i$ 。

所以当且仅当 $x_i<x_j$ 且 $v_i\le v_j$ 才要累加 $d(i,j)$ 。

### 暴力

对于每个点 $i$ ，枚举所有点 $j$ ，如果满足 $x_j<x_i$ 且 $v_j\le v_i$ ，
则令答案增加 $x_i-x_j$ 。

时间复杂度 $\Theta(n^2)$ 。

### 优化

对于每个点 $i$ ，因为点 $j$ 要满足 $x_j<x_i$ ，所以不需要枚举所有点 $j$ 。

可以对数组根据 $x$ 从小到大排序。

那么只要在 $1$ ~ $i-1$ 中寻找所有满足 $v_j\le v_i$ 的 $j$ ，然后累加 $x_i-x_j$ 。

设满足的 $j$ 有 $k$ 个 ，分别表示为 $j_1$ ~ $j_k$ ，那么答案增加

$(x_i-x_{j_{1}})+(x_i-x_{j_{2}})+...+(x_i-x_{j_{k}})=x_i\cdot k-(x_{j_{1}}+x_{j_{2}}+...+x_{j_{k}})$

可以用线段树或树状数组维护 $k$ 和 $(x_{j_{1}}+x_{j_{2}}+...+x_{j_{k}})$ ，具体见代码。

每次累加完只要更新点 $i$ 的信息即可。

因为 $-10^8\le vi\le 10^8$ 所以需要离散化。

时间复杂度 $\Theta(nlogn)$ 。

### 树状数组代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int b[200005],m;
ll c[200005][2];//第二维为0表示当前扫描到的点中，v值在区间内的点的个数，为1表示v值在区间内的点的x值和
struct node
{
   	int x,v;
    bool operator < (const node t) const
   	{
   		return x<t.x;
   	}
}a[200005];
int lsh(ll x)
{
   	return lower_bound(b+1,b+1+m,x)-b;
}
ll query(int x,int k)//返回1~x区间内的点数或点的坐标和 
{
    ll ret=0;
	for (int i=x;i>=1;i-=i&-i)
    	ret+=c[i][k];
	return ret;	
}
void update(int x,int y)//更新点x 
{
   	for (int i=x;i<=m;i+=i&-i)
   	{
   		c[i][0]++;
   		c[i][1]+=y;
	}
}
int main()
{
   	int n;
   	scanf("%d",&n);
   	for (int i=1;i<=n;i++)
    	scanf("%d",&a[i].x);
    for (int i=1;i<=n;i++)
   	{
   		scanf("%d",&a[i].v);
   		b[i]=a[i].v;
   	}
   	sort(b+1,b+1+n);
   	m=unique(b+1,b+1+n)-b-1;
   	sort(a+1,a+1+n);//根据x排序 
   	ll ans=0;
   	for (int i=1;i<=n;i++)
   	{
    	int t=lsh(a[i].v);//离散化 
    	ans+=query(t,0)*a[i].x-query(t,1);//计算距离和 
    	update(t,a[i].x);
   	}
   	printf("%lld",ans);
   	return 0;
}
```
### 线段树代码
```cpp
#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;
typedef long long ll;
int b[200005],m;
ll tr[800005][2];
struct node
{
   	int x,v;
    bool operator < (const node t) const
   	{
   		return x<t.x;
   	}
}a[200005];
int lsh(ll x)
{
   	return lower_bound(b+1,b+1+m,x)-b;
}
ll query(int l,int r,int x,int y,int k,int p)
{
    if (l==x && r==y)
      	return tr[p][k];
    int mid=l+r>>1;
    if (y<=mid)
      	return query(l,mid,x,y,k,ls);
    else if (x>mid)
      	return query(mid+1,r,x,y,k,rs);
    else
      	return query(l,mid,x,mid,k,ls)+query(mid+1,r,mid+1,y,k,rs);
}
void update(int l,int r,int x,int y,int p)
{
   	if (l==r)
    {
    	tr[p][0]++;
    	tr[p][1]+=y;
    	return;
    }
    int mid=l+r>>1;
    if (x<=mid)
    	update(l,mid,x,y,ls);
    else
    	update(mid+1,r,x,y,rs);
    tr[p][0]=tr[ls][0]+tr[rs][0];
    tr[p][1]=tr[ls][1]+tr[rs][1];
}
int main()
{
   	int n;
   	scanf("%d",&n);
   	for (int i=1;i<=n;i++)
    	scanf("%d",&a[i].x);
    for (int i=1;i<=n;i++)
   	{
   		scanf("%d",&a[i].v);
   		b[i]=a[i].v;
   	}
   	sort(b+1,b+1+n);
   	m=unique(b+1,b+1+n)-b-1;
   	sort(a+1,a+1+n);
   	ll ans=0;
   	for (int i=1;i<=n;i++)
   	{
    	int t=lsh(a[i].v);
    	ans+=query(1,m,1,t,0,1)*a[i].x-query(1,m,1,t,1,1);
    	update(1,m,t,a[i].x,1);
   	}
   	printf("%lld",ans);
   	return 0;
}
```

---

## 作者：zhmshitiancai (赞：0)

题意；数轴上有$n$个点，每个点的坐标和速度给出。(保证每个点开始时在不同位置)定义$d(i,j)$为两个点运动过程中最短距离。求
$$\sum_{1\leq i <j\leq n}d(i,j)$$

对于两个点$i$和$j$，不妨设$x_i>x_j$

如果$v_i \geq v_j$ 

那么$d(i,j)=x_i-x_j$

否则$d(i,j)=0$

发现这很像逆序对。

我们模仿树状数组求逆序对的方式。

先对$v_i$离散化

用树状数组维护$s1,s2$

$s1_i$表示速度为$i$的坐标和。

$s2_i$则统计速度为$i$的数量

我们按照坐标排升序，倒序扫描。

扫到$i$时，我们要统计在$i$之后，且速度大于$i$的点，到$x_i$的距离和。

速度大于$i$的点，就是$s1$在$v_i$之后的，我们已经统计了他们的$x_i$之和，只要加起来就行，但这不是到$i$的距离和，所以我们还维护了$s2$是数量，只要减去数量和$\times x_i$即可

**code**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int INF=0x3f3f3f3f,N=2e5+5;
int n;
struct node{
	ll x,v,id;
}a[N];
ll tr[2][N*4];
ll b[N];
ll lowbit(ll x)
{
	return x&-x;
}
void add(ll x,ll y,int cur)
{
	while(x<=n)
	{
		tr[cur][x]+=y;
		x+=lowbit(x);
	}
}
ll sum(ll x,int cur)
{
	ll s=0;
	while(x)
	{
		s+=tr[cur][x];
		x-=lowbit(x);
	}
	return s;
}
bool cmp1(node x,node y)
{
	return x.v<y.v;
}
bool cmp2(node x,node y)
{
	return x.x<y.x;
}
void print()
{
	for(int i=1;i<=n;i++)
		printf("%d ",sum(i,1)-sum(i-1,1));
	cout<<endl;
	for(int i=1;i<=n;i++)
		printf("%d ",sum(i,0)-sum(i-1,0));
	cout<<endl;
	cout<<endl;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i;
	cin>>n;
	
	for(i=1;i<=n;i++)
		scanf("%lld",&a[i].x);
	for(i=1;i<=n;i++)
		scanf("%lld",&a[i].v);
	sort(a+1,a+n+1,cmp1);
	int tot=0;
	for(i=1;i<=n;i++)
	{
		if(i==1||a[i].v!=a[i-1].v)
		{
			tot++;
			b[i]=tot;
		}
		else 
			b[i]=b[i-1];
	}
	for(i=1;i<=n;i++)
		a[i].v=b[i];
	sort(a+1,a+n+1,cmp2);
	
//	for(i=1;i<=n;i++)
//		cout<<a[i].v<<" ";
//	cout<<endl;
	ll ans=0;
	for(i=n;i;i--)
	{
		ll num=sum(n,0)-sum(a[i].v-1,0);
		ans+=sum(n,1)-sum(a[i].v-1,1)-num*a[i].x;
		add(a[i].v,a[i].x,1);
		add(a[i].v,1,0);
		//print();
	}
	cout<<ans<<endl;
}
```

---

## 作者：Lily_White (赞：0)

TLDR: 稍稍修改的二维偏序模板

事实上，如果 $x_i < x_j$，则在 $v_i>v_j$ 时二者必定相遇。$v_i \le v_j $ 时距离的最小值就是初始值， $x_i \ge x_j$ 同理。

维护两个树状数组，一个记录目前为止满足 $x_i < x_j, v_i \le v_j $的点的数量 $c$ ，另一个记录所有点到原点距离的和 $L$。

查询时，设当前点到原点距离 $x$，则答案为 $xc-L$。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define y1 y114514
#define elif else if
#define VPII vector <PII>
#define y2 y1919810
typedef pair <int, int> PII;
typedef vector <int> VI;
#define int long long
#define all(x) x.begin(),  x.end()
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int i = 1; i <= (int)n; i++)
#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define range(i, s, t)  for (int i = s; i <= (int)t; i++)
#define il inline
#define RESET(x) memset((x), 0, sizeof(x))


const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
LL qread() {
    char c = getchar();
    int neg = 1;
    LL val = 0;
    while (c != '-' && !isdigit(c)) c = getchar();
    if (c == '-') {
        c = getchar(); 
        neg = -1;
    }
    while (isdigit(c)) {
        val = (val << 3) + (val << 1) + c - '0';
        c = getchar();
    }
    return neg * val;
}
const int N = 200000;
struct node {
    int x, v;
    node(int x = 0, int v = 0): x(x), v(v) {}
    bool operator < (const node& b) const {
        if (x != b.x) return x < b.x;
        return v < b.v;
    }
};
struct BIT {
    int tr[N + 15];
    void add(int x, int v = 1) {
        for (; x <= N; x += x & -x) {
            tr[x] += v;
        }
    }
    int que(int x) {
        int ret = 0;
        for (; x; x -= x & -x) {
            ret += tr[x];
        }
        return ret;
    }
}cnt, dist;
vector <node> p;
vector <int> D;
int n;
void solve() {
    n = qread();
    p.resize(n);
    rep(i, n) p[i].x = qread(); rep(i, n) p[i].v = qread();
    sort(all(p));
    vector <int> d;
    rep(i, n) d.pb(p[i].v);
    sort(all(d)); d.erase(unique(all(d)), d.end());
    D.resize(n);
    rep(i, n) D[i] = lower_bound(all(d), p[i].v) - d.begin() + 1;
    int ans = 0;
    rep(i, n) {
        dist.add(D[i], p[i].x);
        cnt.add(D[i]);
        int c = cnt.que(D[i]), L = dist.que(D[i]);
        ans += c * p[i].x - L;
    }
    printf("%lld\n", ans);
}
signed main() {
    int T = 1;
    //T = qread();
    while (T--) 
        solve();
    return 0;
}
```

---

