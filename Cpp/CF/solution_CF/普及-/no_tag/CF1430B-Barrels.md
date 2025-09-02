# Barrels

## 题目描述

You have $ n $ barrels lined up in a row, numbered from left to right from one. Initially, the $ i $ -th barrel contains $ a_i $ liters of water.

You can pour water from one barrel to another. In one act of pouring, you can choose two different barrels $ x $ and $ y $ (the $ x $ -th barrel shouldn't be empty) and pour any possible amount of water from barrel $ x $ to barrel $ y $ (possibly, all water). You may assume that barrels have infinite capacity, so you can pour any amount of water in each of them.

Calculate the maximum possible difference between the maximum and the minimum amount of water in the barrels, if you can pour water at most $ k $ times.

Some examples:

- if you have four barrels, each containing $ 5 $ liters of water, and $ k = 1 $ , you may pour $ 5 $ liters from the second barrel into the fourth, so the amounts of water in the barrels are $ [5, 0, 5, 10] $ , and the difference between the maximum and the minimum is $ 10 $ ;
- if all barrels are empty, you can't make any operation, so the difference between the maximum and the minimum amount is still $ 0 $ .

## 样例 #1

### 输入

```
2
4 1
5 5 5 5
3 2
0 0 0```

### 输出

```
10
0```

# 题解

## 作者：vectorwyx (赞：2)

最直观的做法是令 $k$ 次操作后的最大值最大，最小值最小。由于只用一次操作就能使最小值变为 $0$，因此接下来我们只需要让最大值最大。贪心地选择前 $k$ 大的数将它们加到第 $k+1$ 大的数上即可。答案就是前 $k+1$ 大的数之和。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int maxn=2e5+5;
int a[maxn];

bool cmp(int x,int y){
	return x>y;
}

void work(){
	int n=read(),k=read();
	ll ans=0;
	fo(i,1,n) a[i]=read();
	sort(a+1,a+1+n,cmp);//从大到小排序 
	fo(i,1,k+1) ans+=a[i];
	printf("%lld\n",ans); 
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```


---

## 作者：Jay142753869 (赞：1)

题意：给你 $n$ 个桶，第 $i$ 桶里有 $a_i$ 升水，你可以选定把第 $i$ 桶的水倒到第 $j$ 桶中，可以倒 $k$ 次，求最后桶中水最大最小值的差。

那么我们可以发现，你如果把把第 $i$ 桶的水倒到第 $j$ 桶中，那么 $a_i$ 就变成了 $0$，所以最小值就是 $0$，那么我们只要使得最大值最大即可，所以答案就是前 $k+1$ 大的桶中水之和。

 _Code_ 
 ```cpp
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<cstdio>
#define int long long
using namespace std;
inline int read(){
	register int x=0,f=0,ch=getchar();
	while('0'>ch||ch>'9')f^=ch=='-',ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^'0'),ch=getchar();
	return f?-x:x;
}
int t,n,a[200010],k,anss;
signed main(){
	t=read();
	while(t--){
		n=read(),k=read();
		for(int i=1;i<=n;i++)
			a[i]=read();
		sort(a+1,a+n+1);
		for(int i=n;i>=n-k;i--)
			anss+=a[i];
		printf("%lld\n",anss);
		anss=0;
	}
	return 0;
}
```


---

## 作者：do_while_true (赞：0)

[$\text{更佳的阅读体验}$](https://www.cnblogs.com/do-while-true/p/13799080.html)

# B. Barrels

### Translate

$T$ 次询问，对于每一次询问：

有 $n$ 个水桶，第 $i$ 个水桶有 $a_i$ 单位的水，有 $k$ 次机会把一个桶里的水倒在另一个桶里（任意单位，可以不执行完），询问最后最大水桶水量和最小水桶水量的差的最大值。

$1\leq k < n\leq 2\cdot10^5,0\leq a_i \leq10^9$

### Solution

贪心：差值最大，则让最大数尽量大，最小数尽量小。用 $k$ 次机会把前 $(k+1)$ 大的水桶倒在一起，必剩有空桶（对应就是最小值为 $0$ ），则差的最大值就是前 $(k+1)$ 大的数的和。

### Code

```cpp
#define ll long long
const int N = 1e6 + 10;
int n, k;
ll a[N], sum, maxx, minn, b[N];
signed main() {
	int T = read();
	while(T--) {
		n = read();
		k = read();
		for(int i = 1; i <= n; ++i) a[i] = read();
		std::sort(a + 1, a + n + 1);
		sum = 0;
		++k;
		for(int i = n; i >= 1; --i) {
			sum += a[i];
			--k;
			if(!k) break;
		}
		printf("%lld\n", sum);
	}
	return 0;
}
```

---

## 作者：—维尼— (赞：0)

## 题目描述

给定$n$个桶和$k$次操作，每次操作你可以将任意一个桶中的任意数量的水转移到另一个桶，问$k$次操作后，所有桶中最多的水和最少的水的差值

## 题目思路
如何汇聚出最大值和最小值

我们发现在给定移动次数情况下**优先汇聚水最多的桶**就能得出最多的水，所以可以贪心求解，当然每次移动要将桶内的水**全部移走**，所以只要把前$k$个最多的水汇聚到$k+1$位置的水桶就行了，这就是最大值

而最小值因为每次我们移动的时候都不留任何水，所以最小值**就是0**，所以排序之后求前k大的数求和就行了

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
bool cmp(int a,int b){
	return a>b;
}
long long a[200005];
int main(){
	int t,n,k;
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		sort(a+1,a+1+n,cmp);
	//	for(int i=1;i<=n;i++)
	//	cout<<a[i]<<" ";
		for(int i=1;i<=k;i++){
			a[i+1]+=a[i];
			a[i]=0;
		}
		cout<<a[k+1]<<endl;
	}
	return 0;
}
```

---

## 作者：dbodb (赞：0)

#### 贪心题

#### 题意：

现在有n个桶，每个桶里面都有一定量的水，可以把桶中的水，倒入其他的桶里，最多可以倒k次。问桶中水的最大值与最小值的差。

#### 思路

让最大和最小的差值最小，那就让最小值为0，也就是一次全部拿完

先$sort$一遍

考虑怎么让最大值最大，将第2大，第3大，...第k大的全部放在第1大的上面，这样能做到最大

最后的答案就是$a[n]$

#### 注意

最后的答案可能爆$int$ 记得开$long long$

#### 代码

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2e6;
long long t;
long long a[N];
int main()
{
	cin>>t;
	for(long long i=1;i<=t;i++)
	{
		long long n;
		long long k;
		cin>>n >> k ;
	 	 for(long long i=1;i<=n;i++)
		cin>>a[i];	
		sort(a+1,a+1+n);
		for(long long i=n-1;i>=n-k;i--)
		{
			a[n]+=a[i];	
		}
		cout<<a[n]<<endl;
	}					
	return 0;				
} 
```



---

## 作者：星空舞涵 (赞：0)

~~趁着人不多，水发题解加点咕咕~~

### 题意

现在有$n$个桶，每个桶里面都有一定量的水，可以把桶中的水，倒入其他的桶里，最多可以倒$k$次。问桶中水的最大值与最小值的差。

### 分析

首先$k>0$的，这说明至少可以倒一次，也就是一定有一个桶里面的水可以被倒走，所以最小值一定是0。

然后考虑最大值，我首先想到的是背包，现在设每个桶的重量是$1$,价值就是水量，背包的容量是$k+1$。

但是因为每个桶的重量都是$1$,所以我们会发现背包选的是前$k+1$大的数，所以我们可以直接进行排序，选取值最大的$k+1$个数

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
long long ans;
int k,n;
int a[200001];
int main( )
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        ans=0;
        for(int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+n+1);
        for(int i=n;i>=n-k;i--)
        {
            ans=ans+a[i];
        }
        cout<<ans<<endl;
    }
}
```


---

## 作者：Konnyaku_LXZ (赞：0)

因为 $k>1$ ，所以你把一个桶里的水倒掉后这个桶里就没有水了，所以最小值为 $0$，让最大值最大只需要把桶按水量从大到小排序，将排名为前 $k+1$ 的桶里的水倒到一起即可。

Code：

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<cmath>
using namespace std;

typedef long long LL;
const int MAXN=2e5+50;

LL N,K,a[MAXN],Ans=0;

bool cmp(LL a,LL b){return a>b;}

void Init(){
	scanf("%lld%lld",&N,&K);
	for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
}

void Solve(){
	Ans=0;
	sort(a+1,a+1+N,cmp);
	for(int i=1;i<=K+1;++i) Ans+=a[i];
}

void Print(){
	printf("%lld\n",Ans);
}

int main()
{
	int T;
	cin>>T;
	while(T--){
		Init();
		Solve();
		Print();
	}
	return 0;
}
```

---

