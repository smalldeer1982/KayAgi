# Typewriter

## 题目描述

# 打字机


最近，Polycarp收到了一台特殊的打字机作为礼物！不幸的是，这台打字机有一个相当奇怪的设计。

这台打字机由 $n$ 个单元组成，从左到右编号为 $1$ 到 $n$ ，还有一个移动的小车。打字机的每个单元包含 $n$ 个不同的整数，从 $1$ 到 $n$ ，每个单元 $i$ 最初包含整数 $p_i$ 。在所有操作之前，小车位于第一个单元上，它的缓冲区没有任何内容。当前小车所在的单元称为当前单元。

小车可以执行以下五种操作：

- 如果当前单元不为空，就将其中的整数放入小车的缓冲区（缓冲区最多只能容纳一个整数）。
- 如果小车的缓冲区不为空，就将其中的整数放入当前单元（如果当前单元为空）。
- 如果小车的缓冲区和当前单元都含有整数，就交换缓冲区中的整数和当前单元中的整数。
- 将小车从当前单元 $i$ 移动到下一个单元 $i+1$ （如果 $i<n$ ），缓冲区中的整数保持不变。
- 将小车重置，即将其移动到第一个单元，缓冲区中的整数保持不变。

Polycarp对这个打字机非常感兴趣，所以他请你帮助他理解它，并回答他 $q$ 个问题：

1. 执行一个循环左移 $k_j$ 的操作。
2. 执行一个循环右移 $k_j$ 的操作。
3. 反转序列。

在每个查询之前和之后，Polycarp想要知道为了将数字分配到它们的单元（使数字 $i$ 最终位于第 $i$ 个单元），需要多少次小车重置的最小次数。

注意，Polycarp只想知道需要多少次小车重置来整理数字的位置，但实际上并不进行分配。

帮助Polycarp找到每个查询的答案！

## 说明/提示

在第一个示例中，答案为 $1$ 。你可以通过这个示例了解小车的工作方式。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1834F/01d1261e4504263d10e986c4b6ba55c7ce30a3cc.png)在第二个示例中，需要计算答案的序列如下：

1. 所有查询之前：$1\ 2\ 3$ —— 答案为 $0$ 。
2. 右移 $1$ 位之后：$3\ 1\ 2$ —— 答案为 $2$ 。
3. 反转序列之后：$2\ 1\ 3$ —— 答案为 $1$ 。

在第三个示例中，每个查询之前和之后的序列如下：

1. $3\ 1\ 2\ 5\ 4$ —— 答案为 $3$ 。
2. $5\ 4\ 3\ 1\ 2$ —— 答案为 $2$ 。
3. $2\ 1\ 3\ 4\ 5$ —— 答案为 $1$ 。
4. $3\ 4\ 5\ 2\ 1$ —— 答案为 $2$ 。
5. $1\ 3\ 4\ 5\ 2$ —— 答案为 $1$ 。
6. $2\ 5\ 4\ 3\ 1$ —— 答案为 $2$ 。

## 样例 #1

### 输入

```
3
2 3 1
0```

### 输出

```
1```

## 样例 #2

### 输入

```
3
1 2 3
2
2 1
3```

### 输出

```
0
2
1```

## 样例 #3

### 输入

```
5
3 1 2 5 4
5
1 3
3
2 3
1 4
3```

### 输出

```
3
2
1
2
1
2```

# 题解

## 作者：Lynkcat (赞：5)

首先观察到答案下界为 $\sum_i p_i<i$，因为如果一个位置的 $p_i$ 小于他那么必须重置才能放回去。

接下来我们尝试把答案构造到这个：

考虑每个大小大于 $1$ 的置换环，按其最小值从小到大排序；然后我们逐一进行操作，每次从这个置换环的最小点开始做，然后最后回到最小点，这样就能讲一个置换环调整完毕。并且因为最小值单调所以从当前环的最小点能直接走到下一个环的最小点不需要额外的重置。

接下来问题就变成支持区间旋转、整体翻转，查询 $\sum_i p_i<i$。

区间旋转，那考虑对于一个 $i$，对答案有贡献的旋转的偏移量是一个或两个区间，差分搭配前缀和即可。

整体翻转就没啥意思了，维护一下翻转后的序列即可。

时间复杂度 $O(n+q)$。

```c++
// Problem: F. Typewriter
// Contest: Codeforces - Codeforces Round 879 (Div. 2)
// URL: https://codeforc.es/contest/1834/problem/F
// Memory Limit: 256 MB
// Time Limit: 3000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 400005
using namespace std;
int n,p[N],ip[N],cnt[N],q;
int p1[N],ip1[N],cnt1[N];
int sum[N],sum1[N];
void BellaKira()
{
	cin>>n;
	for (int i=1;i<=n;i++)
		cin>>p[i];
		
	for (int i=1;i<=n;i++)
	{
		ip[p[i]]=i;
		if (p[i]>=i)
		{
			int l=p[i]-i+1;
			int r=n-i;
			if (l<=r) sum[l]++,sum[r+1]--;
		} else
		{
			{
				int l=0;
				int r=n-i;
				if (l<=r) sum[l]++,sum[r+1]--;
			}
			{
				int l=n+p[i]-i+1;
				int r=n-1;
				if (l<=r) sum[l]++,sum[r+1]--;
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		cnt[(ip[i]-i+n)%n]++;
	}

	for (int i=1;i<=n;i++) p1[i]=p[n-i+1];
	for (int i=1;i<=n;i++)
	{
		ip1[p1[i]]=i;
		if (p1[i]>=i)
		{
			int l=p1[i]-i+1;
			int r=n-i;
			if (l<=r) sum1[l]++,sum1[r+1]--;
		} else
		{
			{
				int l=0;
				int r=n-i;
				if (l<=r) sum1[l]++,sum1[r+1]--;
			}
			{
				int l=n+p1[i]-i+1;
				int r=n-1;
				if (l<=r) sum1[l]++,sum1[r+1]--;
			}
		}
	}
	for (int i=1;i<=n;i++)
	{
		cnt1[(ip1[i]-i+n)%n]++;
		sum[i]+=sum[i-1];
		sum1[i]+=sum1[i-1];
	}
	
	int x=0,y=0,zt=0;
	if (zt==1)
	{
		cout<<sum1[y]<<'\n';
	} else
	{
		cout<<sum[x]<<'\n';
	}
	cin>>q;
	while (q--)
	{
		int o,p;
		cin>>o;
		if (o==3)
		{
			zt^=1;
		} else
		{
			cin>>p;
			o--;
			if ((zt^o)==0)
			{
				x=(x-p+n)%n;
				y=(y+p)%n;
			} else
			{
				x=(x+p)%n;
				y=(y-p+n)%n;
			}
		}
		if (zt==1)
		{
			cout<<sum1[y]<<'\n';
		} else
		{
			cout<<sum[x]<<'\n';
		}
	}
		
}
signed main()
{
	IOS;
	cin.tie(0);
	int T=1;
	while (T--)
	{
		BellaKira();
	}
}
```

---

## 作者：Locix_Elaina_Celome (赞：1)

# [CF1834F Typewriter](https://www.luogu.com.cn/problem/CF1834F) 题解

## 题意

> 给定一个 $n\in [1,4\times 10^5]$ 的排列。你有一个指针和一片只能放一个整数缓冲区。
>
> 每次可以执行如下操作：
>
> 1. 若指针指向的位置不为空，缓存区为空，将其中的整数放入缓冲区。
> 2. 若指针指向的位置为空吗，缓冲区不为空，将缓冲区中的数放入指向的位置。
> 3. 两个都不为空，交换两个数。
> 4. 将指针从 $i$ 移到 $i+1$。（$i < n$）
> 5. 将指针移动到 $1$。
>
> 初始指针在 $1$，缓冲区为空。
>
> 还有 $q\in [1,4\times 10^5]$ 次修改：
>
> 1. 将整个排列循环左移 $k$。
> 2. 将整个排列循环右移 $k$。
> 3. 反转序列。
>
> 对于最初局面以及每次修改后，求将整个排列排序至少需要多少次操作五。

## 题解

瞪一下样例再瞎猜，答案就是 $\sum [a_i < i]$。

感性理解就是说如果想往回就必须重置，否则直接往后推就行了。

那么考虑一下怎么维护操作。

循环位移只需要处理一个方向就行了，毕竟左移 $k$ 相当于右移 $n-k$。

设 $b_i=a_i-i$，那么问题就变成了询问整体 $b_i<0$ 的位置个数。

位移视为给每个被扔到前面的位置 $i-=n-k$，也就是 $b_i+=n-k$，其余位置 $b_i-=k$。

反转直接维护两个，一正一反同时维护。

于是就可以使用树套树了。

---

但是树套树太丑陋了，而且 $4\times 10^5$ 不太能过。

因为树套树的功能很多都没用上，所以很明显能感觉出有简单很多的方法。

首先我们会发现对于初始状态，每个数能对答案产生贡献的位移次数是一个区间。把这些区间扔到数轴上，每次相当于查询一个位移次数被多少个区间覆盖了。

就直接差分+前缀和就行了。

时间复杂度 $O(n+q)$。

```cpp
using namespace std;
#include<bits/stdc++.h>
//#include<cstdio>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 1000005
#define LL long long
#define LD long double
//#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define Rand() ((rand()<<16)|rand())
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define Rand() ((rand()<<16)|rand())
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define Rand() (rand())
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-6);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);}
int n,q;
int s[2][N];
int a[N];
#undef aint
int main(){
//#define int LL
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int i=1;i<=n;i++){
		s[0][Max(a[i]-i+1,(int)0)]++;
		s[0][n-i+1]--;
		if(a[i]-i+1<0)s[0][n+a[i]-i+1]++;
	}
	reverse(a+1,a+n+1); 
	for(int i=1;i<=n;i++){
		s[1][Max(a[i]-i+1,(int)0)]++;
		s[1][n-i+1]--;
		if(a[i]-i+1<0)s[1][n+a[i]-i+1]++;
	}
	int nw=0;
	for(int i=1;i<=n;i++){
		s[0][i]+=s[0][i-1];
		s[1][i]+=s[1][i-1];
	}
	write(s[0][nw]);
	puts("");
	int rev=0;
	int n1=0,n2=0;
	read(q);
	for(int i=1;i<=q;i++){
		int op,k;
		read(op);
		if(op==3)rev^=1;
		else{
			read(k);
			if((op==2)^rev){
				n1=(n1+k>=n?n1+k-n:n1+k);
				n2=(n2-k<0?n2-k+n:n2-k);
			}
			else{
				n2=(n2+k>=n?n2+k-n:n2+k);
				n1=(n1-k<0?n1-k+n:n1-k);
			}
		}
		if(!rev)write(s[0][n1]);
		else write(s[1][n2]);
		puts("");
	}
	return 0;
#undef int
}
```

---

## 作者：Prophesy_One (赞：1)

### 题意：

我认为以我的语言表达能力不足以讲明题意。

https://codeforces.com/contest/1834/problem/F

### 思路：

找规律题？？？盯着样例看了一会发现结论是 $\sum {p_i < i}$。

$p_i$ 除了是第 $i$ 项，也是最终的目标位置。感性理解，$p_i>i$ 意味着目标位置在当前位置之后，在操作过程中会被带过去，不计入答案。

而 $p_i<i$ 意味着目标位置在当前位置之前，需要一次操作带回去，对答案产生贡献。

具体地，可以用线段树维护：下标 $i$ 表示当前整个排列整体右移了 $i$ 步，维护每个元素产生贡献的时刻即可。

预处理出正向和反向排列右移 $i$ 步的贡献，预处理 $\text{O}(n \log n)$，查询 $\text{O}(1)$，但是我懒得再开个数组了，就直接 $\text{O}(\log n)$ 查了。

### 代码：
```cpp
#include<cstdio>
using namespace std;
const int N=4e5+5;
int n,q,p[N],rev[N];
struct SGT
{
	int sum[N<<2],tag[N<<2];
	void pushup(int k)
	{
		sum[k]=sum[k<<1]+sum[k<<1|1];
	}
	void pushdown(int k,int l,int r)
	{
		if(!tag[k])
		return;
		int mid=(l+r)>>1;
		tag[k<<1]+=tag[k];tag[k<<1|1]+=tag[k];
		sum[k<<1]+=tag[k]*(mid-l+1);
		sum[k<<1|1]+=tag[k]*(r-mid);
		tag[k]=0;
	}
	void update(int k,int l,int r,int x,int y,int v)
	{
		if(x>y)
		return;
		if(l>=x&&r<=y)
		{
			sum[k]+=(r-l+1)*v;tag[k]+=v;
			return;
		}
		int mid=(l+r)>>1;
		pushdown(k,l,r);
		if(x<=mid)
		update(k<<1,l,mid,x,y,v);
		if(mid<y)
		update(k<<1|1,mid+1,r,x,y,v);
		pushup(k);
	}
	int query(int k,int l,int r,int x,int y)
	{
		if(l>=x&&r<=y)
		return sum[k];
		int mid=(l+r)>>1,ans=0;
		pushdown(k,l,r);
		if(x<=mid)
		ans=query(k<<1,l,mid,x,y);
		if(mid<y)
		ans+=query(k<<1|1,mid+1,r,x,y);
		return ans; 
	}
}t1,t2;
int read()
{
	int res,f=1;
	char ch;
	while((ch=getchar())<'0'||ch>'9')
	if(ch=='-')
	f=-1;
	res=ch-48;
	while((ch=getchar())>='0'&&ch<='9')
	res=res*10+ch-48;
	return res*f;
}
int main()
{
	int i,op,x,stp=0;
	bool bz=0;
	n=read();
	for(i=1;i<=n;i++)
	p[i]=read();
	for(i=1;i<=n;i++)
	rev[i]=p[n-i+1];
	for(i=1;i<=n;i++)
	{
		if(i<=p[i])
		t1.update(1,1,n,p[i]-i+1,n-i,1);
		else
		{
			t1.update(1,1,n,1,n-i,1);
			t1.update(1,1,n,n-i+p[i]+1,n,1);
		}
	}
	for(i=1;i<=n;i++)
	{
		if(i<=rev[i])
		t2.update(1,1,n,rev[i]-i+1,n-i,1);
		else
		{
			t2.update(1,1,n,1,n-i,1);
			t2.update(1,1,n,n-i+rev[i]+1,n,1);
		}
	}
	printf("%d\n",t1.query(1,1,n,n,n));
	q=read();
	for(i=1;i<=q;i++)
	{
		op=read();
		if(op==1)
		{
			x=read();stp=(stp-x+n)%n;
		}
		if(op==2)
		{
			x=read();stp=(stp+x)%n;
		}
		if(op==3)
		{
			bz^=1;stp=n-stp; 
		}
		stp=!stp?n:stp;
		if(bz)
		printf("%d\n",t2.query(1,1,n,stp,stp));
		else
		printf("%d\n",t1.query(1,1,n,stp,stp));
	}
	return 0;
}
```

---

## 作者：Helenty (赞：0)

需要注意到答案的下界为 $\sum [a_i>i]$。

考虑怎么取到，我们第一轮直接把 $a_i<i$ 的全部解决掉，此时如果有则一定可以顺便拿到一个 $a_i>i$ 的，一轮一轮解决即可。

我们对 $a_i$ 算出来有贡献的循环位移区间 $[l,r]$，翻转就是多算一种。

这样就可以做到线性的。

---

## 作者：daniEl_lElE (赞：0)

先考虑单词询问怎么做。对于每一个 $p_i<i$，我们需要一次操作将他移到前面，设共有 $k$ 个，则我们至少要 $k$ 次操作。同时，我们观察到对于任意一个置换环，均可以将其分为若干段，使得最后一段 $i\to j$ 满足 $j<i$，于是对着置换环构造即可说明存在一种方案只用 $k$ 次回去的操作。于是答案就是 $p_i<i$ 的位置个数。

观察到本质不同的询问只有 $O(n)$ 种（左右移动可以对 $n$ 取模），我们考虑预处理出来。容易发现，$i$ 位置产生贡献的一定是一个对 $n$ 取模的区间。把所有区间算出来，差分即可。总复杂度 $O(n+q)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[500005],b[500005],prea[500005],preb[500005];
signed main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	reverse(b+1,b+n+1);
	for(int i=1;i<=n;i++){
		if(a[i]<i){
			prea[0]++,prea[i-a[i]]--;
			prea[i]++;
		}
		else{
			prea[i]++,prea[i+n-a[i]]--;
		}
		if(b[i]<i){
			preb[0]++,preb[i-b[i]]--;
			preb[i]++;
		}
		else{
			preb[i]++,preb[i+n-b[i]]--;
		}
	}
	for(int i=1;i<=n;i++) prea[i]+=prea[i-1],preb[i]+=preb[i-1];
//	for(int i=0;i<n;i++) cout<<prea[i]<<" "; cout<<"\n";
//	for(int i=0;i<n;i++) cout<<preb[i]<<" "; cout<<"\n";
	cout<<prea[0]<<"\n";
	int q; cin>>q;
	int sta=0,posa=0,posb=0;
	while(q--){
		int opt; cin>>opt;
		if(opt==1){
			int num;
			cin>>num;
			if(sta==0){
				(posa+=num)%=n;
				(posb+=n-num%n)%=n;
			}
			else{
				(posa+=n-num%n)%=n;
				(posb+=num)%=n;
			}
		}
		if(opt==2){
			int num;
			cin>>num;
			if(sta==0){
				(posa+=n-num%n)%=n;
				(posb+=num)%=n;
			}
			else{
				(posa+=num)%=n;
				(posb+=n-num%n)%=n;
			}
		}
		if(opt==3){
			sta^=1;
		}
		if(sta==0) cout<<prea[posa];
		else cout<<preb[posb];
		cout<<"\n";
	}
	return 0;
}
```

---

