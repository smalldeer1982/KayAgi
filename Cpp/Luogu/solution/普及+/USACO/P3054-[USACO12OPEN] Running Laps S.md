# [USACO12OPEN] Running Laps S

## 题目描述

农夫约翰让他的 n （1 <= n <= 100,000） 头牛在长度为 c 的跑道上进行跑 l 圈的比赛，所有牛从同一起点，以不同的速度开始跑。直到当跑得最快的那一头牛跑完 l 圈时，所有牛才同时停下。

  约翰发现在跑圈过程中发生了几次“超越事件”。其定义是：在比赛结束前某时刻，奶牛 x 已经超越了奶牛 y **整整一圈**，则称做一次“超越事件”。（注： **至少一圈** ，超越了1/2圈，或者超越了1/4圈等等都不算。且对于同一对奶牛（x，y）不会重复计算次数。）

 约翰想知道比赛过程中发生了多少次“超越事件”。

 （注：可能原文章表达有误或某些其他原因，各种翻译方式过来的题意都有问题，给人误导很大，这里是根据题目数据和样例解释写的正确的题意，而不是原文）

## 样例 #1

### 输入

```
4 2 100 
20 
100 
70 
1 
```

### 输出

```
4 
```

# 题解

## 作者：simonG (赞：16)

### 前言

由于蒟蒻不会线段树，或者是树状数组，  
暴力法可以得到12分（$O(n*n)$）。 

所以我们需要一种非常简单的算法，也就是归并，时间复杂度为$O(n*logn)$。而且易于理解  

### 详解  

  > * 1,
  我们知道，超越次数=（$int$）圈数之差  
  求出每一头牛在结束时跑了的圈数。我们假定，圈数在整数的情况下，例如  
  1,2,3  
  $2-1+3-2+3-1=4$  
  总共4次超越  
  但是，只是应用于**整数**的情况下

  > * 2,
  所以我们需要考虑**精度**的问题，然后标记。最后，剩下的整数部分就是求**逆序对**（求差）的过程。逆序对减去之前标记的就是答案。  
  1.3,2.8,3.2  
  在整数情况下还是4次，但是看下例  
  $int(2.8-1.3)+int(3.2-2.8)+int(3.2-1.3)=1+0+1=2$
  显然不一样了，只有2次。

  >* 3,
  我们一个一个枚举圈数之间的差，需要两层for遍历，时间复杂度为  $O(n*n)$。  
  所以，需要用**归并排序**，一种非常简便的方法，求出逆序对的个数。


------------
### 代码  
$O(n*logn)$算法，如下

```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long//不开longlong见祖宗
using namespace std;//命名空间
#define maxn 100003//数据范围 
ll n,l,c;
ll V[maxn];//速度 
ll d[maxn],a[maxn],f[maxn],s[maxn];

inline ll read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
} //快-读

ll Msort(ll l,ll r) { //归并排序
	if(l>=r)return 0;//递归边界 
	ll ans=0;
	int mid=(l+r)>>1;//(l+r)/2
	ans+=Msort(l,mid);
	ans+=Msort(mid+1,r);
	for(int i=l; i<=mid; i++)
		a[i]=d[i];
	for(int i=mid+1,j=r; j>=mid+1; i++,j--)
		a[i]=d[j];
	int i=l;
	int j=r;//左右边界 
	for(int k=l; k<=r; k++)
		if(a[i]<=a[j])
			d[k]=a[i++];
		else {
			ans+=mid-i+1;//求逆序对
			d[k]=a[j--];
		}
	return ans;//逆序对个数
} 

int main(){ 
	n=read(),l=read(),c=read();//读入
	for(int i=1; i<=n; i++)
		V[i]=read();//读入
	sort(V+1,V+n+1);//有序性
	ll ans=0,t=0;
	for(int i=1; i<=n; i++) {
		f[i]=l*V[i]/V[n];
		d[i]=l*V[i]%V[n];
	}//圈数，个数
	for(int i=1; i<=n; i++) {
		ans+=(i-1)*f[i]-t;
		t=t+f[i];
	} //枚举
	ans-=Msort(1,n);//减去逆序对个数
	printf("%lld",ans);//输出 
	return 0;
}
``` 
### 后记
[记录](https://www.luogu.com.cn/record/43805109)  

遇到难题时，不一定要考虑非常高级的算法，从最简单的开始，逐步往上推，直至最优解。

---

## 作者：Danny_SCQ (赞：6)

此题总体思路为逆序对，可以使用归并排序，树状数组和线段树等算法。

**本文使用[归并排序](https://oi-wiki.org/basic/merge-sort/)的思路来解决逆序对。**

暴力算法时间复杂度为 $O(n^2)$。

期望得分 $48$ 分。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 100001
int a[N];
int n,l,c;
int main(){
	scanf("%d %d %d",&n,&l,&c);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	sort(a+1,a+n+1);
	long long ans=0;
	for(int i=n;i>1;i--){
		for(int j=i-1;j>=1;j--){
			ans+=((a[i]-a[j])*l)/a[n]; 
		}
	}
	printf("%lld",ans);
	
}
```
首先我们考虑每头牛跑的圈数，则先需要求出所有牛可以跑步的最大时间 $t$。


> 某头牛跑完时，所有的牛都停下来。

因此只要速度最快的牛完成了赛段，则所有的牛都需要停下，用快速排序求出速度最大值 $V_{max}$。

不难求出 $t=\frac{l \times c}{V_{max}}$。

设第 $i$ 头奶牛跑了 $a_i$ 圈， $a_i =v_i\times (l\div V_{max})$ （数学公式可由上式推出）
。

我们对圈数进行排序，则绕圈数量为 


>$n=a_i -a_j=(v_i-v_j)\times l \div V_{max}$ $(1\leq i<j\leq n)$。


但注意一个**魔鬼细节**。

如果圈数为小数时则会多算一圈，举个例子如果 $a_i=3.6,a_j=2.9$ 时，这个式子就会多算一个 $1$，我们可以对 $a_i$ 的余数部分求出逆序对，可以将所有多算出来的部分求出。

**Q**：

为什么要求出余数部分，而不求小数部分？

**A**：

因为小数部分精度问题复杂，余数方便处理。


代码如下。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,c;
int v[114514];
int cpy[114514];
int guich[114514];
inline int read(){//快读
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-'){
			f=-1;
			c=getchar();
		}
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+(c^48),c=getchar();
	}
	return x*f;
}
int tmp[114514];
int ans=0,t=0,gary=0;
inline void merge(int l,int mid,int r){//归并板子
	int i=l,j=mid+1,t=l;
	while(i<=mid&&j<=r){
		if(cpy[i]>cpy[j]){
			ans+=mid-i+1;
			tmp[t++]=cpy[j++];
		}
		else tmp[t++]=cpy[i++];
	}
	while(i<=mid) tmp[t++]=cpy[i++];
	while(j<=r) tmp[t++]=cpy[j++];
	for(int i=l;i<=r;i++) cpy[i]=tmp[i];
}
inline void mergesort(int l,int r){
	if(l>=r) return ;
	int mid=l+(r-l)/2;
	mergesort(l,mid);
	mergesort(mid+1,r);
	merge(l,mid,r);
//	return ans;
}
int v_max;
signed main(){//使用了#define int long long 所以将int修改为signed
	n=read();
	l=read();
	c=read();
	for(register int i=1;i<=n;i++){
		v[i]=read();
		v_max=max(v_max,v[i]);
	}
	sort(v+1,v+1+n);
	for(register int i=1;i<=n;i++){
		cpy[i]=(l*v[i])%v_max;//余数部分
		guich[i]=(l*v[i])/v_max;//整数部分
	}
	for(register int i=1; i<=n; i++) {
		gary+=(i-1)*guich[i]-t;//计算未处理前的值
		t=t+guich[i];//计算所有多加的值
	} 
	mergesort(1,n);
	gary-=ans;
	printf("%lld\n",gary);
	return 0;
}
```





---

## 作者：1124828077ccj (赞：6)

首先，求出每只奶牛跑的圈数，q[i]表示第i只奶牛的速度，Max表示速度最快的奶牛的速度

得出式子：q[i]\*(l\*c/Max)/c，约分得q[i]\*l/Max，存下它们的下取整数（p[i].s）和余数(p[i].t)

判断i和j两只奶牛超越了几次方法如下（j跑的圈数比较多）

如果p[j].t>=p[i].t，则答案为p[j].s-p[i].s否则答案为p[j].s-p[i].s-1

那么方法很明显了，我们只需要知道在这只奶牛之前有多少只奶牛的余数比它大就行了，可以树状数组维护，至于p[j].s-p[i].s这个如何算就非常容易了，请自己思考。

附代码

```cpp
#include<cstdio>
#include<algorithm>
#include<cstdlib>
using namespace std;
long long n,m,l,c,q[100002],Max,h,ans,sz[1000002];
typedef struct{
    long long s,t;
}P;
bool cmp(P aa,P bb){
    if (aa.s!=bb.s)return aa.s<bb.s;
    return aa.t<bb.t;
}
P p[100002];
long long chaxun(long long x){
    int ans=0;
    for (;x>=1;x-=x&-x)
    ans+=sz[x];
    return ans;
}
void gengxin(long long x){
    for (;x<=m;x+=x&-x)
    sz[x]++;
}
int main()
{
    scanf("%lld%lld%lld",&n,&l,&c);m=1e6;
    for (int i=0;i<n;i++)
    {
        scanf("%lld",&q[i]);Max=max(Max,q[i]);
    }
    for (int i=0;i<n;i++)
    {
        p[i].s=q[i]*l/Max;
        p[i].t=q[i]*l%Max;
    }
    sort(p,p+n,cmp);
    for (int i=0;i<n;i++)
    {
        ans+=i*p[i].s-h-(chaxun(m)-chaxun(p[i].t));
        h+=p[i].s;if (p[i].t)gengxin(p[i].t);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：Drinkkk (赞：4)

## 题目描述

Farmer John决定调查开展“奶牛赛跑运动”的可能性。 

他将 $N$ 头奶牛 $(1 \leq N \leq 100,000)$，放在一个长度为 $C$ 的圆形跑道上。奶牛们沿圆形跑道，跑 $L$ 圈。 

所有奶牛起点都相同，跑步的速度不同。 

当最快的奶牛跑完距离 $L \times C$ 的时候，比赛结束。 

FJ 注意到，有些时候一头奶牛会超过另一个奶牛。 

他在思考，整个比赛中，这类“超车事件”会发生多少次。 

更具体的说，一个“超车事件”指的是： 

一对奶牛 $(x,y)$ 和一个时间 $t$ （小于等于比赛结束时间），在时间 $t$ 奶牛 $x$ 超过前面的奶牛 $y$ 。

请帮 FJ 计算整个比赛过程中，“超车事件”发生的次数。

## 题解

我们设第 $i$ 头牛在比赛期间跑了 $l_i$ 圈，显然这是一个小数。那么我们先按牛的速度排序，然后对于两头牛 $i$ 和 $j$ ，如果 $i>j$ ，那么 $l_i>l_j$ 。

然后 $i$ 和 $j$ 两头牛对答案的贡献肯定就是 $\lfloor l_i-l_j \rfloor$ 。

但是这样是 $O(n^2)$ 的，考虑怎么优化它。

如果我们把贡献改为 $\lfloor l_i \rfloor - \lfloor l_j \rfloor$ ，那么答案会多算。例如 $l_i=2.7,l_j=1.8$ ，贡献应该是 $0$ 而不是 $1$ 。

我们不难发现对于 $i$ 和 $j$ ，它们产生的贡献如果用 $\lfloor l_i \rfloor - \lfloor l_j \rfloor$ 最多只会多算 $1$ ，而且不会少算。并且如果多算了 $1$ ，那么 $l_i$ 的小数部分一定会小于 $l_j$ 的小数部分。

那么我们对小数部分做一遍逆序对，逆序对数就是多算的答案了。

但是对小数做逆序对有点麻烦，而且容易被卡精度。于是我们考虑设 $v_i$ 为第 $i$ 头牛的速度，而且已经是按升序排好了的。那么我们不难得出 $l_i=[ v_i \times (L \times C) \div v_n ] \div C$ 。然后把乘 $C$ 和除 $C$ 抵消掉，得 $l_i=v_i \times L \div v_n $ 。那么我们设 $d_i=(v_i \times L) \; \mod \; v_n +1$ ，然后对 $d$ 数组做一遍逆序对就可以了。加 $1$ 是为了防止出现 $0$ 。这里求逆序对我是用线段树来实现的，时间复杂度为 $O(n\;\log\;n)$ 。

## 参考代码

```cpp
#include <cstdio>
struct node{ int l,r,lc,rc,c; } tree[2100001];
long long a[1000001],b[1000001],d[1000001];
int len=0;
void px(long long l,long long r)
{
	long long x=l,y=r,mid=a[(l+r)/2];
	while(x<=y)
	{
		while(a[x]<mid)
		{
			x++;
		}
		while(a[y]>mid)
		{
			y--;
		}
		if(x<=y)
		{
			long long t=a[x];
			a[x]=a[y];
			a[y]=t;
			x++;
			y--;
		}
	}
	if(l<y)
	{
		px(l,y);
	}
	if(x<r)
	{
		px(x,r);
	}
}
void bt(int l,int r)
{
	len++;
	tree[len].l=l;
	tree[len].r=r;
	tree[len].lc=0;
	tree[len].rc=0;
	tree[len].c=0;
	int now=len;
	if(l<r)
	{
		int mid=(l+r)/2;
		tree[len].lc=len+1;
		bt(l,mid);
		tree[now].rc=len+1;
		bt(mid+1,r);
	}
}
void change(int now,int x,int t)
{
	if(tree[now].l==tree[now].r)
	{
		tree[now].c+=t;
		return ;
	}
	int mid=(tree[now].l+tree[now].r)/2;
	if(x<=mid)
	{
		change(tree[now].lc,x,t);
	}
	else
	{
		change(tree[now].rc,x,t);
	}
	tree[now].c=tree[tree[now].lc].c+tree[tree[now].rc].c;
}
int findsum(int now,int l,int r)
{
//	printf("findsum(%d,%d,%d):%d,%d\n",now,l,r,tree[now].l,tree[now].r);
	if(tree[now].l==l && tree[now].r==r)
	{
		return tree[now].c;
	}
	int mid=(tree[now].l+tree[now].r)/2;
	if(r<=mid)
	{
		return findsum(tree[now].lc,l,r);
	}
	else if(mid+1<=l)
	{
		return findsum(tree[now].rc,l,r);
	}
	else
	{
		return findsum(tree[now].lc,l,mid)+findsum(tree[now].rc,mid+1,r);
	}
}
int main()
{
	long long n=0,l=0,ma=0;
	double c=0.0;
	scanf("%lld %lld %lf",&n,&l,&c);
	for(long long i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	px(1,n);
	for(long long i=1;i<=n;i++)
	{
		b[i]=(long long)(a[i]*1.0*l/a[n]);
		d[i]=(a[i]*l)%a[n]+1;
		if(d[i]>ma)
		{
			ma=d[i];
		}
	}
	long long ans=0,su=b[1];
	for(long long i=2;i<=n;i++)
	{
		su+=b[i];
		ans+=b[i]*i-su;
	}
	bt(1,ma+1);
	change(1,d[1],1);
	for(long long i=2;i<=n;i++)
	{
		ans-=findsum(1,d[i]+1,ma+1);
		change(1,d[i],1);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：wly09 (赞：3)

# 题意简述

求
$$\sum_{v_i>v_j}\big\lfloor\dfrac{l(v_i-v_j)}{v_{\max}}\big\rfloor.$$

传送门：[洛谷](https://www.luogu.com.cn/problem/P3054)

# 思路

由于一共跑 $l$ 圈，每圈路程为 $C$，故总路程 $S=lC$。设最快的奶牛速度为 $v_{max}$，则总时间为 $T=\dfrac{S}{v_{max}}=\dfrac{lC}{v_{max}}$。此时每头奶牛跑的路程为 $s_i=v_iT$，即 $\dfrac{s_i}{C}=\dfrac{v_i\cdot\frac{lC}{v_{max}}}{C}=\dfrac{lv_i}{v_{max}}$ 圈。显然奶牛被“套圈”的总次数为 $\sum_{v_i>v_j}\big\lfloor\dfrac{l(v_i-v_j)}{v_{\max}}\big\rfloor.$

## $O(n^2)$ 做法

不难想到暴力枚举，但考虑到 $n$ 最大 $10^5$ 显然无法 AC ，洛谷上可以拿约 80 分（[记录](https://www.luogu.com.cn/record/147704094)）：

```c++
#include <algorithm>
#include <iostream>
using namespace std;

long long n, c, k;
double v[100010];

int main() {
	register long long res = 0;
	ios::sync_with_stdio(false);
	cin >> n >> k >> c;
	for (register int i = 0; i < n; ++i) cin >> v[i];
	sort(v, v + n);
	double v_max = v[n - 1];
	for (register int i = 1; i < n; ++i)
		for (register int j = 0; i > j; ++j)
			res += __builtin_floor(k * (v[i] - v[j]) / v_max);
	cout << res << endl;
	return 0;
}
```

## $O(n\log n)$ 正解

注意到：
$$\begin{aligned}\sum_{v_i>v_j}\big\lfloor\dfrac{l(v_i-v_j)}{v_{\max}}\big\rfloor&=\sum_{v_i>v_j}\big\lfloor\dfrac{lv_i}{v_{\max}}-\dfrac{lv_j}{v_{\max}}\big\rfloor\\&=\sum_{v_i>v_j}\bigg\lfloor\Big(\big\lfloor\dfrac{lv_i}{v_{max}}\big\rfloor+\dfrac{(lv_i)\mod{v_{max}}}{v_{max}}\Big)-\Big(\big\lfloor\dfrac{lv_j}{v_{max}}\big\rfloor+\dfrac{(lv_j)\mod{v_{max}}}{v_{max}}\Big)\bigg\rfloor\\&=\sum_{v_i>v_j}\bigg\lfloor\big\lfloor\dfrac{lv_i}{v_{max}}\big\rfloor-\big\lfloor\dfrac{lv_j}{v_{max}}\big\rfloor+\dfrac{(lv_i)\mod{v_{max}}-(lv_j)\mod{v_{max}}}{v_{max}}\bigg\rfloor.\end{aligned}$$

其中，对于每一对 $v_i>v_j$，不难发现 $0\leq(lv_i)\mod v_{max},(lv_j)\mod v_{max}< v_{max}$，故 $-v_{max}<(lv_i)\mod{v_{max}}-(lv_j)\mod{v_{max}}<v_{max}$，即 $-1<\dfrac{(lv_i)\mod{v_{max}}-(lv_j)\mod{v_{max}}}{v_{max}}<1$，于是显然有：
$$\bigg\lfloor\big\lfloor\dfrac{lv_i}{v_{max}}\big\rfloor-\big\lfloor\dfrac{lv_j}{v_{max}}\big\rfloor+\dfrac{(lv_i)\mod{v_{max}}-(lv_j)\mod{v_{max}}}{v_{max}}\bigg\rfloor=\begin{cases}\big\lfloor\dfrac{lv_i}{v_{max}}\big\rfloor-\big\lfloor\dfrac{lv_j}{v_{max}}\big\rfloor,&(lv_i)\mod{v_{max}}\geq(lv_j)\mod{v_{max}}, \\ \big\lfloor\dfrac{lv_i}{v_{max}}\big\rfloor-\big\lfloor\dfrac{lv_j}{v_{max}}\big\rfloor-1,&\text{otherwise}.\end{cases}$$

为了方便计算，我们可以先将序列 $\{v_i\}$ 排序，即可在 $O(n)$ 计算 $\sum_{v_i>v_j}\Big(\big\lfloor\dfrac{lv_i}{v_{max}}\big\rfloor-\big\lfloor\dfrac{lv_j}{v_{max}}\big\rfloor\Big)$（记为 $res$），然后统计序列 $\big\{(lv_i)\mod{v_{max}}\big\}$ 中逆序对的个数（即式中 $\text{otherwise}$ 情况出现的数量，记为 $cnt$）。$res-cnt$ 即为所求。

排序和求逆序对均可以在 $O(n\log n)$ 内完成，故总时间复杂度为 $O(n \log n)$。

```c++
#include <algorithm>
#include <iostream>
using namespace std;

long long n, c, k;
long long v[100010], r[100010], tmp[100010], cnt = 0;

void merge_sort(long long *arr, int l, int r) {
	if (r - l <= 1) return ;
	int mid = l + ((r - l) >> 1);
	merge_sort(arr, l, mid), merge_sort(arr, mid, r);
	register int pt1 = l, pt2 = mid, pt = l;
	for (; pt1 < mid && pt2 < r; ++pt) {
		if (arr[pt1] <= arr[pt2])  tmp[pt] = arr[pt1++];
		else tmp[pt] = arr[pt2++], cnt += mid - pt1;
	}
	for (; pt1 < mid; ++pt1) tmp[pt++] = arr[pt1];
	for (; pt2 < r; ++pt2) tmp[pt++] = arr[pt2];
	for (register int i = l; i < r; ++i) arr[i] = tmp[i];
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k >> c;
	for (register long long i = 0; i < n; ++i) cin >> v[i];
	sort(v, v + n);
	long long v_max = v[n - 1];
	for (register long long i = 0; i < n; ++i) {
		r[i] = k * v[i] % v_max;
		v[i] = k * v[i] / v_max;
	}
	register long long lsum = 0, res = 0;
	for (register long long i = 0; i < n; ++i) {
		res += v[i] * i - lsum;
		lsum += v[i];
	}
	merge_sort(r, 0, n);
	cout << res - cnt << endl;
	return 0;
}
```

[记录](https://www.luogu.com.cn/record/147704250)

---

## 作者：Addicted_Game (赞：2)

# [传送门](https://www.luogu.com.cn/problem/P3054)

### 题目大意
给定跑道的长度 $c$ 和要跑的圈数 $l$ 和每只奶牛的速度 $s_i$，每只奶牛要在第一只奶牛跑完后停止，求出现了多少次超越。

### 思路
我们可以直接求出每只牛跑的圈数和剩下的米数，可以直接算出整数圈的超越次数。但是可能会出现一只圈数更多的奶牛多的米数比另一只少，这种就会减少超越。而这种情况就是圈数多（位置靠前），而米数少（数值小），那不就是逆序对吗！所以说结果就是整数圈超越减去米数逆序对的个数。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,c;
long long v[100005],r[100005],a[100005];
long long t;
void m_sort(long long L,long long R){
	if(L==R)  return ;
    long long mid=L+R>>1,i=L,j=mid+1,k=L;
    m_sort(L,mid);
	m_sort(mid+1,R);
    while(i<=mid&&j<=R){
    	if(r[i]<=r[j]){
    		a[k++]=r[i++];
		}else{
			a[k++]=r[j++];
			t+=mid-i+1;//求逆序对
		}
	}
    while(i<=mid) a[k++]=r[i++];
    while(j<=R) a[k++]=r[j++];
    for(long long i=L;i<=R;i++) r[i]=a[i];
}
int main(){
	scanf("%lld%lld%lld",&n,&l,&c);
	for(long long i=1;i<=n;i++){
		scanf("%lld",&v[i]);
	}
	sort(v+1,v+n+1);//排序其实是为累加整数圈与逆序对的初始化
	for(long long i=1;i<=n;i++){
		r[i]=l*v[i]%v[n];//整数圈
		v[i]=l*v[i]/v[n];//剩余的米数
	}
	long long ans=0,sum=0;
	for(long long i=1;i<=n;i++){
		ans+=v[i]*(i-1)-sum;//很巧妙，通过累加原本的超越数优化时间
		sum+=v[i];
	}
	m_sort(1,n);
	printf("%lld",ans-t);//整数圈-小数圈
	return 0;
}
```

---

## 作者：Loser_Syx (赞：2)

考虑到不同速度的每个人在有限的时间 $t$ 内跑的圈数都是不一样的，于是可以先算出每个人 $i$ 跑了几圈，多多少圈（不满一圈），然后进行分组别处理。

- 对于整数部分，直接用 $speed \times (i-1) - sum$ 得出多跑的圈子。

但是发现小数部分会存在，$a$ 的小数部分比 $b$ 大，但是直接用 $b$ 的整数部分减去了 $a$ 的，存在 $1$ 圈的错误计算。

于是可以使用 `__gnu_pbds::tree` 来实现存储小数部分，每次进行查询小数部分比当前大的即可。

注意考虑到 `double` 类型所存在的精度误差，故参与计算时应加上误差（此处我取了 $10^{-10}$）。

显然所有操作基于排序后再搞。

```cpp
typedef pair<double, int> pdi;
tree<pdi, null_type, greater<pdi>, rb_tree_tag, tree_order_statistics_node_update> tr;
const int N = 1e5 + 19;
const double eps = 1e-10; 
int v[N];
signed main() {
	int n, l, c, ans = 0;
	read(n, l, c);
	for (int i = 1; i <= n; ++i) {
		read(v[i]);
	}
	sort(v + 1, v + 1 + n);
	double t = 1.0 * l * c / v[n];
	int sum = 0;
	for (int i = 1; i <= n; ++i) {
		double speed = v[i] * t / c;
		int speed1 = (int)speed;
		double speed2 = speed - speed1;
		ans += speed1 * (i-1) - sum;
		sum += speed1;
		ans -= tr.order_of_key({speed2+eps, 1e9});
		tr.insert({speed2, -i});
	}
	write(ans, '\n');
	return 0;
}
```

---

## 作者：wangping (赞：2)

**思路**

由于题目里面说只要有一头跑完 $1$ 圈那么所有的牛都会停下来，

所以我们可以想给 `v数组` 排序（方便后面处理），并算出每头奶牛跑了多少圈（`cycle数组`）。

显然第 `i` 头奶牛和第 `j` 头奶牛 `cycle` 之差下取整。

那么题目就简化为给 $n$ 个实数求每个数与它之前所有数之差下取整的和（$n\leq10^5$，显然 $n^2$ 做法是不可行的，从取值范围可以看出应该是 $n\log n$ 的）。

先举个例子 `(cycle[i], cycle[j]) = (4.8, 5.7)` 差的下取整是 $0$ ,但 `(cycle[i], cycle[j]) = (4.2, 5.7)` 差的下取整是 $1$，

所以我们可以把 `cycle` 分成整数部分 `cycle`，以及小数部分 `last` 。

若 `last[i]>last[j]`，则 `ans=cycle[j]-cycle[i]-1`；若 `last[i]<=last[j]`，则 `ans=cycle[j]-cycle[i]`。

所以我们可以在 `ans` 里面存下 `cycle` 之差然后再在 `last` 数组里找逆序对，逆序对有几个 `ans` 就得减多少。

至于逆序对，我使用归并排序实现（`merge` 为归并排序过程），也可以用树状数组等数据结构（还没写 QwQ），

详见代码（注意 `double` 判断大小的时候用相减判断，不然会出现精度问题）。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long i,j,l,m,n,v[100005],ans,c,cycle[100005];
double t,k,last[100005],b[100005];
void merge(int lef,int rig)
{
	if (lef==rig) return;
	if (lef==rig-1)
	{
		if (last[lef]-last[rig]>1e-7) ans--,swap(last[lef],last[rig]);
		return;
	}
	int mid=(lef+rig)/2;
	merge(lef,mid);
	merge(mid+1,rig);
	int i,j,l;
	for (l=i=lef,j=mid+1; i<=mid&&j<=rig;)
	{
		if (last[i]-last[j]>1e-7)
		{
			ans-=(mid-i+1);
			b[l++]=last[j++];
		}
		else b[l++]=last[i++];
	}
	for (; i<=mid;) b[l++]=last[i++];
	for (; j<=rig;) b[l++]=last[j++];
	for (i=lef; i<=rig; i++) last[i]=b[i];
}
int main()
{
	scanf("%lld%lld%lld",&n,&l,&c);
	for (i=1; i<=n; i++) scanf("%lld",&v[i]);
	sort(v+1,v+n+1);
	t=l*c*1.0/v[n];
	m=0;
	for (i=1; i<=n; i++)
	{
		cycle[i]=(long long)(t*v[i]/c);
		ans+=(i-1)*cycle[i]-m;
		m+=cycle[i];
		last[i]=t*v[i]-cycle[i]*c;
	}
	merge(1,n);
	printf("%lld",ans);
}
```

---

## 作者：rainbow_cat (赞：1)

#### 注：
这道题考试的时候看错了数据范围，喜提及格分（无语）。
### 思路
首先，我们思考暴力做法。先按 $v$ 从小到大排序，设第 $i$ 头牛在最快的牛跑完比赛之前可以跑 $b_i$ 圈，则化简后 $b_i=\frac{l \times v_i}{v_n}$。则第 $i$ 头牛超越第 $j$ 头牛的次数为 $\lfloor b_i-b_j \rfloor$，接下来暴力循环累加即可，时间复杂度为平方级别。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,k,ans,a[100010];
int main()
{
	ios::sync_with_stdio(0);	
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	double t=m*k/a[n];
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
		{
			if(a[i]==a[j])break;
			int tmp=m*(a[i]-a[j])/a[n];
			//m/a[n]*(a[i]-a[j])
			if(!tmp)break;
			ans+=tmp;			
		}		
	}
	cout<<ans;
	return 0;
}
```
接下来，我们考虑优化。很明显，我们希望将 $\lfloor b_i-b_j \rfloor$ 拆分为 $\lfloor b_i \rfloor-\lfloor b_j \rfloor$ 以线性处理。可是我们会发现一个问题，对与 $b_i=2.2$ 和 $b_j=1.3$ 或 $b_i=11.4$ 和 $b_j=7.434$ 之类 $b_i$ 整数位比 $b_j$ 大，但小数位比 $b_j$ 小的情况，$\lfloor b_i \rfloor-\lfloor b_j \rfloor$ 会多算一次。由于我们按 $v$ 从小到大排序，所以只需要减去对小数位的逆序对个数即可。   
与此同时，我们发现使用小数可能产生精度误差，于是我们将小数改为余数的形式即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,ans,a[100010],bit[1000010],b[100010];
int lowbit(int x){return x&-x;}
void add(int x,int y){for(;x;x-=lowbit(x))bit[x]+=y;}
int query(int x)
{
	int res=0;
	for(;x<=a[n];x+=lowbit(x))res+=bit[x];
	return res;
}
signed main()
{
	ios::sync_with_stdio(0);	
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)
	{
		int tmp=m*a[i]/a[n];
		b[i]=m*a[i]%a[n]+1;//本人太蒟了，使用树状数组求逆序对，故余数要加一
		ans+=tmp*(i-1-n+i);
	}
	for(int i=1;i<=n;i++)ans-=query(b[i]+1),add(b[i],1);
	cout<<ans;
	return 0;
}
```

---

## 作者：kfhkx (赞：1)

看到没有pascal的题解，就来一波吧~

思路：

1. 把所有速度从大到小排序 
2. 预处理出最快的速度来求出比赛的时间t 
3. 把每一只奶牛在t时间内能跑多少圈求出来，然后分别存整数部分跟小数部分。 
4. 用归并排序求出小数部分的逆序对数量
5. 要进行下取整，因为有小数是因为没够一圈，所以舍去
6. 注意精度问题

### p3054.pas
------------


```pascal
var
        a,zheng:array[0..100000] of int64;
        xiao,b:array[0..100000] of real;
        ans,bns,sum:int64;
        n,l,c,i:longint;
        t:real;
procedure kp(x,y:longint);//从大到小做快速排序
var
        l,r,m:longint;
begin
        l:=x;
        r:=y;
        m:=a[(l+r)>>1];//位运算更快哦~
        repeat
                while a[l]>m do inc(l);
                while a[r]<m do dec(r);
                if l<=r then begin
                        a[0]:=a[l];
                        a[l]:=a[r];
                        a[r]:=a[0];
                        inc(l);
                        dec(r);
                end;
        until l>r;
        if x<r then kp(x,r);
        if l<y then kp(l,y);
end;
procedure gb(x,y:longint);//归并找逆序对
var
        l,r,h,m,i:longint;
begin
        if x=y then exit;
        m:=(x+y)>>1;//位运算更快哦~
        gb(x,m);
        gb(m+1,y);
        l:=x;
        r:=m+1;
        h:=x;
        while (l<=m) and (r<=y) do begin
                if xiao[l]-xiao[r]>-0.000001 then begin//注意精度
                        b[h]:=xiao[l];
                        inc(l);
                        inc(h);
                end else begin
                        b[h]:=xiao[r];
                        inc(h);
                        inc(r);
                        bns:=bns+m-l+1;
                end;
        end;
        while l<=m do begin
                b[h]:=xiao[l];
                inc(l);
                inc(h);
        end;
        while r<=y do begin
                b[h]:=xiao[r];
                inc(r);
                inc(h);
        end;
        for i:=x to y do xiao[i]:=b[i];
end;
begin
        read(n,l,c);
        for i:=1 to n do readln(a[i]);
        kp(1,n);
        t:=l*c/a[1];
        for i:=1 to n do begin
                zheng[i]:=trunc(a[i]*t/c);//整数部分
                l:=zheng[i]*c;
                xiao[i]:=a[i]*t-l;//小数部分
        end;
        for i:=n downto 1 do begin
                sum:=sum+(n-i)*(zheng[i]-zheng[i+1]);
                ans:=ans+sum;
        end;
        gb(1,n);
        writeln(ans-bns);
end.
```

---

## 作者：cghAndy (赞：1)

这道题不难发现是 (跑的快的圈数-跑的少的圈数)向下取整的总和

那么N^2算法是很显然的 怎样快点呢？

我们可以分离一下整数和小数  整数部分直接减（随便搞） 那么如果有什么 2.4-1.5 其实向下取整是一圈都没有的

所以我们对于小数部分求出逆序对再减掉就好了~

欢迎来刷访问量 <http://blog.csdn.net/cgh\_andy/article/details/52992952> 代码若丑 别介意。。。


---

## 作者：LZYAC (赞：0)

## 思路
通过题意我们先对 $v_i$ 进行排序，可以直接算出每头奶牛在 $t$ 时间内跑了多少圈，设圈数为 $x$，最快的奶牛速度为 $y$，则有 $x=\frac l y \times v_i $。两头奶牛的超越次数就是相减之后向下取整。$O(n^2)$ 的时间复杂度显然是不可接受的。

考虑优化，明显可以将形如 $\lfloor a-b \rfloor$ 的式子拆分成 $\lfloor a \rfloor$ $-$ $\lfloor b \rfloor$ 。但这样可能会错误计算，因为小数部分向下取整了（比如 $3.6$ 和 $2.9$ 就可能存在多算了一圈）。故可以使用逆序对求出多算的圈数。

小数可能会产生精度误差，改为余数即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,c,ans,tmp,v[200010],a[200010],b[200010],tot;
void merge(int l,int mid,int r){
	int blen=l,i=l,j=mid+1;
	while(i<=mid&&j<=r){
		if(a[i]<=a[j]){
			b[blen++]=a[i++];
		}
		else{
			b[blen++]=a[j++];
			tot+=(mid-i+1);
		}
	}
	while(i<=mid){
		b[blen++]=a[i++];
	}
	while(j<=r){
		b[blen++]=a[j++];
	}
	for(int k=l;k<=r;k++){
		a[k]=b[k];
	}
}
void mergesort(int l,int r){
	if(l<r){
		int mid=(l+r)/2;
		mergesort(mid+1,r);
		mergesort(l,mid);
		merge(l,mid,r);
	}
}
signed main(){
	scanf("%lld%lld%lld",&n,&l,&c);
	for(int i=1;i<=n;i++) scanf("%lld",&v[i]);
	sort(v+1,v+1+n);
	for(int i=1;i<=n;i++){
		tmp=v[i]*l/v[n];
		ans=ans+tmp*(2*i-1-n);
	}
	for(int i=1;i<=n;i++) a[i]=(v[i]*l)%v[n]+1;
	mergesort(1,n);
	printf("%lld",ans-tot);
	return 0;
}
```

---

## 作者：SSqwq_ (赞：0)

## sub1 86pts

一个 trival 的暴力：对于每只奶牛，求出其跑的总圈数。

先对 $v$ 数组从小到大排序，则显然整场比赛的总用时 $t=\frac{l\times c}{v_n}$。

记第 $i$ 只奶牛跑了 $k_i$ 圈，则显然有：

$$k_i=\frac{t\times v_i}{c}=\frac{\frac{l\times c}{v_n}\times v_i}{c}=\frac{l\times v_i}{v_n}$$

由于总共超越次数即为每对奶牛间超越次数之和，可以发现答案等于：

$$\sum^{n}_{i=1} \sum^{n}_{j=i+1}{k_j-k_i}$$

注意精度问题即可。时间复杂度 $O(n^2)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const double eps=0.00000001;
int n,ans;
double v[100001];
double l,c,t,k[100001];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>l>>c;
	for(int i=1;i<=n;++i){
		cin>>v[i];
	}
	sort(v+1,v+1+n);
	for(int i=1;i<=n;++i){
		k[i]=(v[i]*l)/v[n];
	}
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			ans+=(int)(k[j]-k[i]+eps);
		}
	}
	cout<<ans<<"\n"; 
	return 0;
} 
```

## sub2 100pts

考虑优化求和部分。

显然整数部分的优化是 trival 的，前缀和即可。

小数部分则不然。由于精度误差，前缀和会出现重复计算或漏加的可能。

观察到一个性质：答案具有共同的分母 $v_n$。因此考虑完全剩余系，以除以 $v_n$ 得到的余数代替原来小数部分。

至此，我们摆脱了小数的困扰。之后可以发现多算的部分其实就是余数部分的逆序对数量，使用你喜欢的求逆序对算法即可。这里代码实现使用树状数组。

时间复杂度 $O(n\log n)$。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans,tr[1000005];
int v[100001],now,pos;
int l,c,t,k[100001];
int lowbit(int x){
	return x&-x;
}
int ask(int x){
	int res=0;
	x++;
	for(;x;x-=lowbit(x)){
		res+=tr[x];
	}
	return res;
}
void add(int x,int y){
	x++;
	for(;x<=1000000;x+=lowbit(x)){
		tr[x]+=y;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>l>>c;
	for(int i=1;i<=n;++i){
		cin>>v[i];
	}
	sort(v+1,v+1+n);
	for(int i=1;i<=n;++i){
		int op=l*(v[i]-v[i-1]);
		now+=(i-1)*(op/v[n]);
		op%=v[n];
		if(op>0){
			int l=pos-op,r=pos-1;
			if(l<0){
				l+=v[n];
			}
			if(r<0){
				r+=v[n];
			}
			if(l<=r){
				now+=ask(r)-ask(l-1);
			}
			else{
				now+=ask(1000000)+ask(r)-ask(l-1);
			}
			if(pos<op){
				pos+=v[n];
			}
			pos-=op;
		}
		add(pos,1);
		ans+=now;
	}
	cout<<ans<<"\n"; 
	return 0;
} 
```


---

## 作者：Geoyster (赞：0)


标签：树状数组

首先考虑暴力：先排序 $\left\{v_i\right\}$，则答案 $\sum_{i<j}{\lfloor\frac{(v_j-v_i)l}{v_n}\rfloor}$。复杂度 $\mathcal{O(n^2)}$。

然后考虑优化，想到扫描线，枚举 $j$，推出此时的子答案 $f_j$，总答案为 $\sum f_j$。

$f_j=\sum{\lfloor\frac{(v_j-v_i)l}{v_n}\rfloor}=\sum{\lfloor\frac{(v_j-v_{j-1})l}{v_n}+\frac{(v_{j-1}-v_i)l}{v_n}\rfloor}$ 

观察式子，整除分母固定为 $v_n$，不难想到构造 $v_n$ 的剩余系，$j$ 的子答案与 $j-1$ 的子答案的各项的余数有关。

设 $g(x,y)=(v_x-v_y)l$。当 $g(j,j-i)<v_n\;\&\;g(j-1,i)<v_n$ 时，若 $g(j,j-1)+g(j-1,i)\geq v_n$，则子答案变化量加一。那么，此时对于全集

$f_j=f_{j-1}+\sum{[g(j-1,i)\geq v_n-g(j,j-1)]}$ 

而可以直接算出 $g(j,j-1)$，所以可以区间求和，使用树状数组。若 $g(j,j-1)\geq v_n$，那么 $f_j\gets(j-1)\lfloor\frac{g(j,j-1)}{v_n}\rfloor$，然后取余继续求。若 $g(j-1,i)\geq v_n$，此时即包含之前子答案，符合推理。

那么问题的关键是实现维护 $v_n$ 的剩余系的余数。其本质是权值线段树，区间查询容易实现，但是整体平移不容易直接实现，不妨转化为改变 0 点。其他还要注意当 $g(j,j-1)=0$ 时要特判。

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1e5 + 2;
const int M = 1e6 + 2;

int n,l,c,v[N];
int fw[M];
ll ans,res,p;

void add(int x,int v){
	for(int i=x+1;i<=M-2;i+=i&-i) fw[i]+=v; 
}

ll get(int x){
	ll res=0;
	for(int i=x+1;i>0;i-=i&-i) res+=fw[i];
	return res;
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>l>>c;
	for(int i=1;i<=n;i++) cin>>v[i];
	sort(v+1,v+1+n);
	for(int j=1;j<=n;j++){
		ll delta=1ll*l*(v[j]-v[j-1]);
		res+=(j-1)*(delta/v[n]);
		delta%=v[n];
		if(delta){
			int r=p-1,l=p-delta;
			if(r<0) r+=v[n];
			if(l<0) l+=v[n]; 
			if(l<=r) res+=get(r)-get(l-1);
			else res+=get(M-2)+get(r)-get(l-1);
			p-=delta;
			if(p<0) p+=v[n];
		} 
		
		add(p,1);
		ans+=res;
	}
	cout<<ans;
	return 0;
}
```

---

