# Divisors

## 题目描述

Bizon the Champion isn't just friendly, he also is a rigorous coder.

Let's define function $ f(a) $ , where $ a $ is a sequence of integers. Function $ f(a) $ returns the following sequence: first all divisors of $ a_{1} $ go in the increasing order, then all divisors of $ a_{2} $ go in the increasing order, and so on till the last element of sequence $ a $ . For example, $ f([2,9,1])=[1,2,1,3,9,1] $ .

Let's determine the sequence $ X_{i} $ , for integer $ i $ $ (i>=0) $ : $ X_{0}=[X] $ ( $ [X] $ is a sequence consisting of a single number $ X $ ), $ X_{i}=f(X_{i-1}) $ $ (i&gt;0) $ . For example, at $ X=6 $ we get $ X_{0}=[6] $ , $ X_{1}=[1,2,3,6] $ , $ X_{2}=[1,1,2,1,3,1,2,3,6] $ .

Given the numbers $ X $ and $ k $ , find the sequence $ X_{k} $ . As the answer can be rather large, find only the first $ 10^{5} $ elements of this sequence.

## 样例 #1

### 输入

```
6 1
```

### 输出

```
1 2 3 6 
```

## 样例 #2

### 输入

```
4 2
```

### 输出

```
1 1 2 1 2 4 
```

## 样例 #3

### 输入

```
10 3
```

### 输出

```
1 1 1 2 1 1 5 1 1 2 1 5 1 2 5 10 
```

# 题解

## 作者：A_zjzj (赞：6)

### 一道函数递归题

记录一下当前的是第几层和现在要分的数是几（分别用 $x$ 和 $y$ 表示）

然后，每一次从小到大枚举因子，继续递归直到输出的总数到达 $10^5$。

```cpp
#include<cstdio>
#include<cmath>
#define ll long long
using namespace std;
ll a,b,tot;
void dfs(ll x,ll y){
	if(tot>=100000)return;
	if(!x){
		printf("%lld ",y);
		tot++;
		return;
	}
	for(ll i=1;i*i<=y;i++){
		if(y%i)continue;
		dfs(x-1,i);
		if(tot>=100000)return;
	}
	ll k=(ll)(sqrt(y));
	for(ll i=(k*k==y?k-1:k);i>=1;i--){//注意如果这个数是个完全平方数，那么就不能让 sqrt(y) 搜索两次
		if(y%i)continue;
		dfs(x-1,y/i);
		if(tot>=100000)return;
	}
}
int main(){
	scanf("%lld%lld",&a,&b);
	dfs(b,a);
	return 0;
}
```

然后，你就会发现你稳稳地 $T$ 了。

我们考虑优化：

- 如果当前的数 $y$ 是 $1$，那么就不用搜索下去了，直接输出 $1$

- 可以先预处理出 $X$ 的所有因数存在数组 $p$ 中，那么 $X$ 的因数的因数 $\cdots$ 的因数一定是在 $p$ 中

- 枚举每一个 $X$ 的因数的时候，如果这个因数已经大于 $y$ 了，就不用再枚举了（后面的一定比前面的大啊）

### 最终 AC 代码

```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
ll a,b,tot,p[100001];
void dfs(ll x,ll y){
	if(tot>=100000)return;
	if(!x||y==1){
		printf("%lld ",y);
		tot++;
		return;
	}
	for(ll i=1;i<=p[0]&&p[i]<=y;i++){
		if(y%p[i])continue;
		dfs(x-1,p[i]);
		if(tot>=100000)return;
	}
}
int main(){
	scanf("%lld%lld",&a,&b);
	for(ll i=1;i*i<=a;i++){
		if(a%i==0){
			p[++p[0]]=i;
			if(i*i!=a)p[++p[0]]=a/i;
		}
	}
	sort(p+1,p+1+p[0]);
	dfs(b,a);
	return 0;
}
```

---

## 作者：XL4453 (赞：2)

### 解题思路：

感觉没什么硬核的性质，而且题目也有只输出 $10^5$ 这种限制，所以考虑直接搜索。

由于这题是个 E 题，猜想直接搜肯定过不了（实际上也过不了）。考虑对其进行剪纸。

首先发现，当当前搜索的数为 $1$ 时，最终的结果一定是 $1$，这个可以用第一数学归纳法来证明，~~或者用易证~~。 
这样，没当搜索到数字为 $1$ 时，无论目前的操作数是多少，直接输出 $1$ 并退出。

但是这样还是不能满足时间限制，发现每一次都是在因数中再次选取因数，也就是说这个数的因数一定还是原数因数。所以考虑先预处理出最初的数的因数，然后直接从这些因数中找。

由于本题数据范围较大，需要用长整型存储数据。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
long long n,k,p[100005],cnt,tot;
void dfs(long long num,long long k){
	if(tot>=100000)return;
	if(k==0||num==1){
		printf("%I64d ",num);
		tot++;
		return;
	}
	for(int i=1;i<=cnt;i++){
		if(num%p[i]==0)dfs(p[i],k-1);
		if(num<p[i]||tot>100000)return;
	}
}
int main(){
	scanf("%I64d%I64d",&n,&k);
	for(long long i=1;i*i<=n;i++)
	if(n%i==0)p[++cnt]=i;
	for(int i=cnt;i>=1;i--)
	if(p[i]*p[i]!=n)p[++cnt]=n/p[i];
	dfs(n,k);
	return 0;
}
```


---

## 作者：C_Pos_Princess (赞：1)

## 题意

定义函数 $f(a)$ （ $a$ 是一个不定长度的整数集合，这里用 $n$ 表示它的长度）的返回值为如下的另一集合 $b$ ，它包含 $a$ 中的第一个数 $a_1$ 的所有约数，第二个数 $a_2$ 的所有约数，……，一直到第 $n$ 个数 $a_n$ 的所有约数（每一个数的约数要求从小到大排序）。

例如：$f[2,9,1]=[1,2,1,3,9,1]$，$f[1,2,4,8]=[1,1,2,1,2,4,1,2,4,8]$。
考虑到结果可能很大，只要输出这个集合的前    $10^5$个数即可（如果有的话）。

##### 一句话描述
求一个数 $x$ 的 $k$ 次约数展开序列。


## 题解

我们注意到，每次约数展开都是利用的上一个数展开的剩下的。

所以总共涉及到的数字不会很多，我们考虑直接搜索怎么做。

然而爆搜肯定不可以，我们来剪枝一下。

首先，如果搜到了 1，那么直接输出，因为 1 的约数只有 1，再搜下去无意义。

同样的，输出到达了限制就可以直接退出了。


我们考虑一下**时间复杂度**。

一看这个 $1\le k \le 10^{18}$，这怎么能爆搜呢？但别忘了，我们有 1 的优化，一旦 $k$ 到了 $10^5$ 的时候就会全被 1 优化掉，这样一来复杂度上限就会到 $10^5$，仔细分析完全可以。


### 代码
```cpp
const int N = 1e6+10;
const int INF = 0x3f3f3f3f;
using namespace std;
#define int long long
int x,k,m;
int cnt,ans;
int p[10055];
int tot; 

void dfs(int c,int x){
	
	if(cnt>=m) return;
	if(x == 1 || c == k){
		cnt++;
		write(x);
		SP;
		return; 
	}
	for(int i = 1;i<=tot && p[i]<=x;i++){
		if(x%p[i] == 0){
			dfs(c+1,p[i]);
		}
		if(cnt>=m) return;
	}
	
}

signed main(){	
	read(x,k);
	m = 1e5;
	for(int i = 1;i*i<=x;i++){
		if(x%i == 0){
			p[++tot] = i;
			if(x/i!=i) p[++tot] = x/i;
		}
	}
	sort(p+1,p+1+tot);
	dfs(0,x);

	return 0;
}

```

---

## 作者：Dtw_ (赞：1)

# 前言
爆搜加剪枝。本篇大体注重复杂度分析，因为做法其他题解写的挺详细的。
# 思路
首先还是说一下做法：先对 $x$ 的约数进行预处理，然后跑 DFS。DFS 主要维护两个参数，$a,b$，这里 $a$ 指当前要分解的数，$b$ 指分解次数，每次可以枚举 $a$ 的约数，然后 `dfs(a/p, b-1)`。

然后就要优化了，首先发现如果 $k \ge 10^5$ 那判断一下如果 $x = 1$ 就只输出 $1$ 个 $1$，否则输出 $10^5$ 个 $1$。因为 $k$ 足够大，每次分解一个大于 $1$ 的数都会新增一个 $1$，所以这样直接输出就行。

在分解的过程如果遇到 $1$ 直接输出就行，然后统计输出几个数字了，如果 $\ge 10^5$ 直接返回。

最后在枚举因数的时候如果因数已经大于这个数那就不用枚举了。

复杂度分析：

首先我们可以对于每一个数，把他的分解过程想象成一颗树：

![](https://cdn.luogu.com.cn/upload/image_hosting/57mfjo8j.png)

我们会发现，我们只考虑前 $m$ 个数（这里 $m = 10^5$）然后对于 $1$，无论怎么分解还是那个 $1$，所以分解的时候我们遇到 $1$ 就直接输出，这样就避免了一直递归下去的情况，这样对于 $1$ 就可以优化掉 $O(m)$。然后现在我们只考虑了前 $m$ 个所以 DFS 的复杂度大概是 $O(m)$ 的，考虑前面枚举 $x$ 的因数以及排序复杂度为 $O(\sqrt{x}\log \sqrt{x})$ 的。所以这个爆搜是对的。

# Code

```cpp
#include<bits/stdc++.h>

using namespace std;

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 1e6 + 10, M = 1e5;

int x, k, cnt, tot;

int p[N];

void dfs(int a, int b)
{
	if(tot >= M) return;
	if(a == 1 || b == 0)
	{
		cout << a << " ";
		tot++;
		return;
	}
	for(int i=1; i<=cnt && p[i] <= b; i++)
	{
		if(a % p[i] == 0)
		{
			dfs(p[i], b-1);
			if(tot >= M) return;
		}
	}
}

signed main()
{
	fst
    cin >> x >> k;
    if(k >= M)
    {
    	if(x == 1) cout << "1";
    	else for(int i=1; i<=M; i++) cout << "1 ";
    	return 0;
	}
    for(int i=1; i*i<=x; i++)
    {
    	if(x % i == 0)
    	{
    		p[++cnt] = i;
    		if(x / i != i) p[++cnt] = x / i;
		}
	}
	sort(p+1, p+cnt+1);
//	for(int i=1; i<=cnt; i++) cout << p[i] << " ";
//	cout << endl;
	dfs(x, k);
	return 0;
}




```

---

## 作者：laoliu12345 (赞：1)

## CF448E
### 解法说明
暴力肯定过不了

那我们来想一想如何~~优化~~优雅的暴力。

一、首先，$x$ 的因数就是 $x$ 的因数的因数，也就是说后来出现的每个因数都是之前出现过的。

二、对于 $10^5$ 之后的数，我们就没有必要再算了，因为就算算出来了也不作为答案输出，所以只要算出 $10^5$  个数后就可以停止。

三、对于产生出的 $1$，我们就没必要继续递归了。

那就可以愉快的写代码了。
### 题目代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int x,k,m;
int cnt,ans;
int p[10055],cn;
void dfs(int c,int x)
{
	//cout<<c<<" "<<x<<endl;
	if(cnt>=m) return ;
	if(x==1||c==k)
	{
		cnt++;
		printf("%lld ",x);
		return ;
	}
	for(int i=1;i<=cn&&p[i]<=x;i++)
	{
		if(x%p[i]==0)
			dfs(c+1,p[i]);//cout<<p[i]<<" ";
		if(cnt>=m) return ;
	}
}
signed main()
{
	//freopen("trans.in","r",stdin);
	//freopen("trans.out","w",stdout);
	scanf("%lld%lld",&x,&k);
	m=1e5;
	for(int i=1;i*i<=x;i++)
		if(x%i==0)
		{
			p[++cn]=i;
			if(x/i!=i)
			    p[++cn]=x/i;
		}
	sort(p+1,p+cn+1);
	dfs(0,x);
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

首先思路是暴力+模拟，但是肯定会 TLE，于是我们考虑优化。

拿样例来说：

```plain
x0:4
x1:1 2 4
x2:1 1 2 1 2 4
```

我们发现，所有的数都是 $x$ 的因数，这些数被重复计算，所以可以提前预处理出 $x$ 的所有因数，计算的时候再一步一步计算就好了。

然后我们非常容易有一份仍然是 TLE 的代码，我们继续考虑优化：

1. 因为 $x$ 约数的约数必定是 $x$ 的约数，所以查找正在讨论的约数的位置，再在这个位置以前查找 $x$ 这个约数的约数，找到后继这个找到的约数继续 DFS。

2. 如果 $x > 1$ 并且 $k > 10^5$ 时，我们可以直接输出 $10^5$ 个 $1$，然后结束程序。

```cpp
//2021/7/24

#include <cstdio>

#include <algorithm>

#define int long long

using namespace std;

const int ma=1e5+5;

int divi[ma],ans[ma];

int index,nf;

inline bool cmp(int x,int y)
{
	return x<y;
}

namespace sol
{
	inline int init(int n)//预处理因数 
	{
	    int idx=0;
	    
	    for(register int i=1;i*i<=n;i++)
	    {
	        if(n%i==0)
	        {
	            divi[idx++]=i;
	            
	            if(n/i!=i)
	            {
	            	divi[idx++]=n/i;
				}
        	}
    	}
    	
    	sort(divi,divi+idx,cmp);
    	
    	return idx;
	}
	
	inline void dfs(int x,int k)
	{
		if(index>=100000)
		{
			return;
		}
		 
		if(x==1 || k==0)
		{
			ans[index++]=x;
			
			return;
		}
		
		for(register int i=0;i<nf;i++)
		{
			if(divi[i]>x)//优化1 
			{
				break;
			}
			
			if(index>=ma)//超了100000就返回 
			{
				return;
			}
			
			if(x%divi[i]==0)
			{
				dfs(divi[i],k-1);//继续遍历 
			}
		}
	}
}

#undef int

int main(void)
{
	#define int long long
	
	int x,k;
	
	scanf("%lld%lld",&x,&k);
	
	if(x>1 && k>100000)//优化2
	{
		for(register int i=1;i<=100000;i++)
		{
			printf("1 ");
		}
		
		return 0;
	} 
	
	nf=sol::init(x);
	
	sol::dfs(x,k);
	
	for(register int i=0;i<index;i++)
	{
		printf("%lld ",ans[i]);
	}
	
	return 0;
}
```

---

