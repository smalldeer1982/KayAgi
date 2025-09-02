# [USACO10NOV] Cow Photographs G

## 题目描述

农夫约翰想要给他全部的 N (1 <= N <= 100,000) 头奶牛拍张照片，这些奶牛被方便地编号为 1 到 N，以便他能向朋友们炫耀。

在拍照日，奶牛们会跑到一起形成一条单行队列，位置 i 上是奶牛 c\_i (1 <= c\_i <= N)。农夫约翰有他自己关于奶牛应该如何排列的想法。

约翰认为奶牛 i 只能站在奶牛 i+1 的左边（对于所有 i，1 <= i <= N-1），并且奶牛 N 只能站在奶牛 1 的左边。当然，没有奶牛会站在队列中第一头（最左边的）奶牛的左边。

奶牛们渴望拍照后承诺的晚餐，因此农夫约翰想尽快拍完照片。奶牛们不太擅长遵循指示，所以他每分钟只能选择一对相邻的奶牛并让它们交换位置。农夫约翰能多快将它们排成某种合适的顺序？

考虑一组 5 头奶牛，其初始排列如下：

左           右

3  5  4  2  1

他可以先交换第二对奶牛：

3  4  5  2 1

然后交换最右边的一对：

3  4  5  1  2

这样就得到一个合适的排列，只需要两分钟的奶牛交换。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 
3 
5 
4 
2 
1 
```

### 输出

```
2 
```

# 题解

## 作者：zhiyangfan (赞：5)

## P2995 [USACO10NOV]Cow Photographs G
很有意思的一道题，正好初学群论，写一点从置换角度的理解。
### 题意
给出一个 $(1,2,\cdots,n)$ 的排列 $\mathrm{p}$，求出 $\mathrm{p}$ 最少交换多少次相邻元素能够与 $(1,2,\cdots,n)$ 循环同构。($1\le n\le 10^5$)
### 题解
首先要知道怎么求出两个排列 $\mathrm{p,q}$ 之间的最小交换次数。考虑一个置换：
$$p=\begin{pmatrix}\mathrm{p}\\1,2,\cdots,n\end{pmatrix}$$
即把排列 $\rm p$ 对应到“标准”排列的置换，则对排列 $\rm q$ 做置换 $p$ 会得到一个新的排列 $\rm q'$，而 $\rm p,q$ 之间的最小交换次数即 $\rm q'$ 中的逆序对个数。这个问题可以这么理解，我们把 $\rm p,q$ 都对应到了“标准”排列，每次交换相当于交换“标准”排列，而“标准”排列满足一开始没有逆序对，每次交换会增加一个逆序对，这样的话，$\rm q'$ 中的逆序对个数就是交换次数。

现在考虑这道题怎么做，考虑枚举最终要到达的排列，即所有 $n$ 个与 $(1,2,\cdots,n)$ 循环同构的排列。如果我们令最终排列 $\mathrm{p}_i$ 为：
$$\mathrm{p}_i=(2-i,3-i,\cdots,n+1-i)$$
其中定义 $1-1=n$。这样的话，$\mathrm{p}_i$ 对应的置换即：
$$p_i=\begin{pmatrix}2-i,3-i,\cdots,n-i+1\\1,2,\cdots,n\end{pmatrix}$$
考虑把这个置换施加到 $\rm q$ 上的效果，将 $p_i$ 施加到 $\rm q$ 身上，相当于将 $\rm q$ 上的所有元素循环减一：
$$\mathrm{q}\times p_i=(\mathrm{q}_1-i+1,\mathrm{q}_2-i+1,\cdots,\mathrm{q}_n-i+1)$$
减法定义同上。这样的话，如果能在合理时间内求出 $\rm q$ 每次置换后的逆序对，取个 $\min$ 即得答案。

注意到这个过程是依次相减的过程，所以我们考虑找出每次置换引起的逆序对变化。首先我们先求出 $\mathrm{q}\times p_1$，即原排列的逆序对，然后考虑将原排列循环减一后会发生什么。发现所有值会分为两种，一种是单纯的减一，另一种是在减到 $0$ 后又回到 $n$，而后者显然只有 $1$ 这个元素满足。对于前者，它们之间的逆序对是不会改变的，毕竟都减一了，相对大小是不改变的。对于后者，它和其他元素的大小关系会颠倒，即如果设它的位置为 $l$，则 $[1,l)$ 位置上的元素原来均和它形成逆序对，现在均不形成，需要减去，而 $(l,n]$ 位置上的元素原来均和它不形成逆序对，现在均形成，需要加上。也就是说，逆序对会增加 $n-l-(l-1)$ 个。

现在我们来考虑怎么求出 $l$。注意到一次置换会把所有数都循环减 $1$，所以 $\mathrm{q}\times p_i$ 后，那个出现循环的 $1$ 位置应在原排列的 $i-1$ 所在位置。所以我们记录下原排列中每个值对应的位置，求出 $\mathrm{q}\times p_1$ 的逆序对，然后枚举 $p_2\sim p_n$，分别处理逆序对的变化即可。时间复杂度 $\mathcal{O}(n\log n)$。
```cpp
#include <cstdio>
#include <algorithm>
const int N = 1e5 + 10; int a[N], p[N], pos[N]; typedef long long ll;
inline void read(int& x)
{
    x = 0; char ch; int f = 1;
    while ((ch = getchar()) < '0' || ch > '9') f = (ch ^ '-' ? 1 : -1);
    while (x = (x << 1) + (x << 3) + ch - '0', (ch = getchar()) >= '0' && ch <= '9') ;
    x *= f;
}
struct BIT
{
    ll c[N]; int len;
    int lowbit(int x) { return x & -x; }
    void add(int x, int v) { for (int i = x; i <= len; i += lowbit(i)) c[i] += v; }
    ll query(int x) { ll ans = 0; for (int i = x; i; i -= lowbit(i)) ans += c[i]; return ans; }
}bit;
int main()
{
    int n; read(n); bit.len = n; ll rev = 0, ans = 1e18;
    for (int i = 1; i <= n; ++i)
    {
        read(p[i]); rev += bit.query(bit.len) - bit.query(p[i]);
        bit.add(p[i], 1); pos[p[i]] = i;
    }
    ans = std::min(ans, rev);
    for (int i = 1; i < n; ++i) rev += 1 - pos[i] + n - pos[i], ans = std::min(ans, rev);
    printf("%lld\n", ans); return 0;
}
```

---

## 作者：王轩逸 (赞：3)

```cpp
#include<bits/stdc++.h>
using namespace std;
/*
示例：3 4 1 5 2 
所有满足条件的序列：
	2 3 4 5 1
	3 4 5 1 2
	4 5 1 2 3
	5 1 2 3 4
①分别求 3 4 1 5 2 经过多少次交换可以变成以上 4 种序列，选其中交换次数最少
到。
②要求 3 4 1 5 2 经过多少次交换可以变成 2 3 4 5 1，可以将 1 改为 6，然后求
逆序对数量。
③同理求：3 4 1 5 2 经过多少次交换可以变成 3 4 5 1 2，只需要将 1 改为 6，2
改为 7 求逆序对。
④归并求逆序对，需要求 N 次，时间复杂度 O(N^2 * log(N))，超时。
⑤考虑以下两个序列中的逆序对数的区别：
	3 4 1 5 2
	3 4 6 5 2
	a. 1 前面的所有数都和 1 形成逆序对。
	b. 6 后面的所有数都和 6 形成逆序对。
设值 i 所在位置为 p[i]，则：减少了 p[i]-1 个逆序对，增加了 n-p[i]个逆序
对。
⑥设当前序列逆序对数量为 cnt，当前最小值为 i，则将 i 修改为最大值后逆序对
数量变为：
cnt - (p[i] - 1) + (n - p[i]); 
⑦只需要做一次求逆序对即可，总时间复杂度降为 O(Nlog(N) + N); 
*/
const int N=100010;
int n,a[N],p[N],t[N];
long long js(int l,int r){
	long long s=0;
	if(l==r) return 0;//只有一个元素。
	int m=(l+r)/2;
	s+=js(l,m);s+=js(m+1,r);
	int i=l,j=m+1,k=l;
	while(i<=m&&j<=r){//左右数组都还有元素
		if(a[i]<=a[j]) t[k++]=a[i++];
		//a[i, mid]都 > a[j]，共产生 mid - i + 1 个逆序对
		else{
			t[k++]=a[j++];
			s+=m-i+1;
		}
	}
	while(i<=m)
		t[k++]=a[i++];//左边数组还有元素
	while(j<=r)//右边数组还有元素
		t[k++]=a[j++];
	//注意：需要用 t 数组覆盖原数组。
	for(int i=l;i<=r;i++)
		a[i]=t[i];
	return s;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[a[i]]=i;
	}
	long long x=js(1,n),y=(long long)N*N;
	//将 i 修改为 i+n, 减少了 p[i]-1 个逆序对，增加了 n-p[i]个逆序对。
	for(int i=1;i<=n;i++){
		x=x+n-p[i]-p[i]+1;
		y=min(x,y);
	}
	cout<<y;
	return 0;
}

```


---

## 作者：KSToki (赞：2)

不难看出，题目给出一个$n$的排列，要求将其相邻元素交换得到下列排列之一的最小交换次数：
```cpp
1 2 3 …… n
n 1 2 …… (n-1)
(n-1) n 1 …… (n-2)
…………………………………………
2 3 4 …… n 1
```
如果是求转化成$1…n$，那么我们就很容易的想到用**逆序对**来解决这个问题。但现在我们有多种选择，当然你可以选择跑$n$遍逆序对，时间复杂度$O(n^2logn)$，显然T到飞起。

考虑目标数列之间的联系。不难发现，每个目标数列是将前一个目标数列的最后一个数字移到最前面。针对移动数字$x$，会使原本与其不成逆序对关系的$1…(x-1)$与其成逆序对关系，而原本与其成逆序对关系的$(x+1)…n$与其不成逆序对关系。因此我们可以在$O(1)$的时间内实现一个目标数列答案向另一个目标数列答案的转移，这个环节的复杂度为$O(n)$，程序总复杂度为$O(nlogn)$，来源于第一次求逆序对。

代码使用树状数组求逆序对，记得开long long。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100001],r[100001],c[100001];
long long inv,ans;//inv表示当前逆序对数，ans表示答案
////
inline int lowbit(int x)
{
	return x&(-x);
}
void update(int x)
{
	for(;x<=n;x+=lowbit(x))
	    ++c[x];
}
int sum(int x)
{
	int res=0;
	for(;x;x-=lowbit(x))
	    res+=c[x];
	return res;
}
//树状数组模板
int main()
{
	scanf("%d",&n);
	for(register int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		update(a[i]);
		inv+=i-sum(a[i]);
		r[a[i]]=i;//开个映射数组，当然你用map也可以，只是会慢
	}
	ans=inv;
	for(register int i=n;i>0;--i)//转移
	{
		inv=inv+(r[i]-1)-(n-r[i]);//r[i]-1个比r[i]小的，n-r[i]个比r[i]大的
		ans=min(ans,inv);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：antiquality (赞：2)

最近在练树状数组呐，然后就找到了这题。

题面有些玄学的样子，不过仔细看看就不难发觉是和逆序对有关的东西。但是不是裸的板子题~~（这不是废话吗）~~

> “FJ是这么想的,标号为i(1<=i<=n-1)的奶牛只能站在标号为i+1的奶牛的左边,而标号为N的奶牛只能站在标号为1的奶牛的左边.当然,没有牛可以站在队列中最左边的奶牛的左边了.也就是说,最左边的奶牛编号是随意的. ”

这段话是本题题意的关键。讲的清楚明白一些，就是**最终排成的序列必须在首尾相接之后是递增的**。

例如：

1 2 3 4 5

5 1 2 3 4

4 5 1 2 3

想象有一个按照顺序排列的圆环，那么最终方案合法的充要条件就是它是圆环上截下的一段序列。（差不多就是[P1203BrokenNecklace](https://www.luogu.org/problemnew/show/P1203)这个意思）

那么怎么处理这个过程？可以每一次将最小数加上n，此时的逆序对数即此时情况的最优答案。

当然做n次求逆序对是要凉凉的。

首先假设最小数在第x数的位置。那么由于前x-1个数都比它大，肯定对答案有x-1的贡献。而最小数比之后的n-x个数都小，故没有贡献。

而将最小数（第x个数）加上n时就不一样了。它摇身一变成为最大数，于是前x-1的对答案的贡献全部作废，同时在它后面贡献了n-x的答案。

~~第x个数：今天你对我爱理不理，明天我让你高攀不起~~

大概就是这个意思。

不如贴一发code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	char ch = getchar();int num = 0;
	for (; !isdigit(ch); ch = getchar());
	for (; isdigit(ch); ch = getchar())
		num = (num<<3)+(num<<1)+ch-48;
	return num;
}
int f[100035],p[100035],a[100035],n,xx;
long long cnt,ans;
int lowbit(int x){return x&-x;}
void add(int x){for (; x<=n; x+=lowbit(x))f[x]++;}
int query(int x)
{
	int ret = 0;
	for (; x; x-=lowbit(x))
		ret += f[x];
	return ret;
}
int main()
{
	n = read();
	for (int i=1; i<=n; i++)
		xx = read(),p[xx] = i,a[i] = xx;
	for (int i=1; i<=n; i++)
	{
		add(a[i]);
		cnt += i-query(a[i]);
	}
	ans = cnt;
	for (int i=1; i<n; i++)
	{
		cnt += n-2*p[i]+1;
		ans = min(ans, cnt);
	}
	printf("%lld\n",ans);
	return 0;
}
```

顺便做一波硬广[我的博客](http://www.cnblogs.com/antiquality/)

---

## 作者：zundamon (赞：1)

[luogu](https://www.luogu.com.cn/problem/P2995)

------------------------

现在假设 $n=5$ ，这是我们的初始目标序列：

```cpp
1 2 3 4 5

逆序对数量：0
```
将它进行一次循环，我们得到了：

```cpp
2 3 4 5 1

逆序对数量：4
```

每一次循环，逆序对的数量发生了什么变化？我们不必每次都暴力求出

我们发现，此次移动的数字 $1$ ，在原序列中是小于其他数的元素，但却在其他数的前方，所以不构成任何一个逆序对

但当它走到序列最后时，依然小于其他数，却在其他数的后方了。所以与其他所有数都构成了逆序对

循环多次，我们不难得到一个结论：

对于数 $x$ ，在它循环到序列末端时，先前**不与它构成逆序对**的所有数，现在**都与它构成逆序对**。

反之，先前**所有与它构成逆序对**的数，现在都**不与它构成逆序对**。

-------------

要让给出的序列变成**初始**目标序列，对它求逆序对即可，这是初始的交换次数

我们记录下所有数所在的位置，对于每个数，计算它在序列末端做出的贡献，得到新的交换次数


```cpp
int cowat[N];
int endans;
signed main(){
	n=read();
	int ans=0;
	loop(i,1,n){
		nun[i]=read();
		cowat[nun[i]]=i;
	}
	loop(i,1,n){
    	//初始序列逆序对
		add(nun[i],1);
		ans+=(i-query(nun[i]));
	}
	endans=ans;
	loop(i,1,n){
		ans=ans+(n-cowat[i])-(cowat[i]-1);
		endans=Min(endans,ans);
	}
	cout<<endans;
	return 0;
}
```


---

## 作者：wangjinbo (赞：1)

这道题其实是个逆序对水题。。。

### 暴力
对于把 $i (1 \le i \le n)$ 放在最左边的情况，大小关系为 $i<i+1<i+2<……<n<1<2<……<i-1$，计算逆序对即可

时间复杂度 $O(n^2 log n)$，实际得分 $70$ 分

### 正解
经过分析，我们可以发现，最左边的数字增加1，就是把 $2-n$ 这 $n$ 个数字都减 $1$，然后把原来的 $1$ 变成 $n$.

例：原序列为 $3$ $5$ $4$ $2$ $1$

最左边为 $1$ 时，序列为 $3$ $5$ $4$ $2$ $1$，逆序对数为 $8$个

最左边的数 $+1$ 变成 $2$ 时，序列变成 $2$ $4$ $3$ $1$ $5$,逆序对数为 $4$ 个

后面依此类推

这也就是说最左边的数从 $i$ 变成 $i+1$ 时,产生和消除的逆序对都和 $i$ 这个数有关。又因为当最左边的数为 $i$ 时， $i$为最小数，与前面的数均构成逆序对，最左边的数变为 $i+1$ 时，$i$ 变为最大数，与后面的数均构成逆序对。

因此我们可以得到这样一个结论：**设原序列中 $i$ 的位置为 $b[i]$,最左边的数由 $i$ 变成 $i+1$ 时，答案增加 $(n-b[i])-(b[i]-1)$**，算出初始的逆序对数，递推即可

时间复杂度 $O(n log n)$，瓶颈在于计算逆序对数，得分 $100$

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn],n,b[maxn];
long long sum[maxn<<1];
int lowbit(int x){return x&(-x);}
void add(int x,int k){for(;x<=n;x+=lowbit(x))sum[x]+=k;}
long long query(int x){
	long long res=0;
	for(;x>0;x-=lowbit(x))res+=sum[x];
	return res;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[a[i]]=i;
	}
	long long ans=0,now=0;
	for(int i=n;i>=1;i--){
		now+=query(a[i]);
		add(a[i],1);
	}
	ans=now;
	for(int i=1;i<=n;i++)
	{
		now+=(n-b[i])-(b[i]-1);
		ans=min(ans,now);
	} 
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Istruggle (赞：0)

如果要求第一头奶牛必须站在第一个位置，那么答案就是逆序对个数，然后我们发现，所有可能的答案序列就是顺序序列的循环，因此如果我们能快速求出每循环一次的答案就能将问题解决。

我们考虑每次将最后一个数移到最前面，如果是第一次移动，那么这个数一定是最大的，所以如果这个数在原始序列中的位置为 $p$，那么则在新产生了 $p-1$ 个逆序对的同时减少了 $n-p$ 个逆序对。那么当我们再将倒数第二大的数移动到前面的时候该如何计算呢？可以发现，这一操作就相当于将最小的数变为最大的数，例如原序列为 $1,2,3,4,5$，变换后的序列为 $6,2,3,4,5$，由于相对大小没变，所以第二个序列就相当于将第一个序列中的 $5$ 移到前面，这样就简单了，我们每次将最小的数变为最大的数，其实就是按从小到大的顺序考虑将每个数变为最大，然后按照前面的方法计算新的答案即可。

---

## 作者：xixisuper (赞：0)

# P2995 [USACO10NOV] Cow Photographs G 题解

首先是一个常见题意转化，**交换相邻元素使序列变有序的最小次数**等价于数这个序列的**逆序对个数**。

但是这题让求变成循环同构序列的的最小交换次数，怎么做呢？

考虑一种映射，假设我们的目标序列是 $a=\{x,x+1,\cdots,n,1,2\cdots x-1\}$，那么我们把 $a_i\to i$ 上，就又变成了求逆序对个数了。

最后考虑如何实现这种映射，不难想到的是先令让值域变成 $0\sim n-1$，然后映射就相当于是把 $a_i\to (a_i+k)\bmod n$ 上。

最后我们对于 $k\in[0,n-1]$ 中的每一个 $k$ 求出对应的操次数，然后输出最小值就是答案。

而转化后的题目实际上就是[ABC396F](https://www.luogu.com.cn/problem/AT_abc396_f)，。

转化后怎么做呢？考虑任意两位之间的贡献，用树状数组计算贡献，然后改变差分数组即可，时间复杂度 $O(n\log n)$。

```cpp
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const ll N=4e5+10;
inline ll lowbit(ll x){return x&(-x);}
ll sum[N];
void add(ll x){for(ll i=x;i<N;i+=lowbit(i)) sum[i]+=1;}
ll query(ll x){
	ll ret=0;
	for(ll i=x;i;i-=lowbit(i)){ret+=sum[i];}
	return ret;
}
void init(){for(ll i=0;i<N;i++) sum[i]=0;}
ll n,m,a[N],cha[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;m=n;
	for(ll i=1;i<=n;i++){cin>>a[i];a[i]--;}
	for(ll i=n;i>=1;i--){
		add(a[i]+1);
		ll dt=query(a[i]);
		cha[0]+=dt;
		cha[m-a[i]]-=dt;
		dt=query(m+1)-query(a[i]+1);
		cha[m-a[i]]-=dt;
	}
	init();
	for(ll i=1;i<=n;i++){
		add(a[i]+1);
		ll dt=query(m+1)-query(a[i]+1);
		cha[m-a[i]]+=dt;
		dt=query(a[i]);
		cha[m-a[i]]+=dt;
	}
	ll ans=cha[0];
	for(ll i=1;i<m;i++){
		cha[i]+=cha[i-1];
		ans=min(ans,cha[i]);
	}
	cout<<ans;
	return 0;
}
```

---

