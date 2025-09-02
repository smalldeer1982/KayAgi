# Levko and Permutation

## 题目描述

Levko loves permutations very much. A permutation of length $ n $ is a sequence of distinct positive integers, each is at most $ n $ .

Let’s assume that value $ gcd(a,b) $ shows the greatest common divisor of numbers $ a $ and $ b $ . Levko assumes that element $ p_{i} $ of permutation $ p_{1},p_{2},...\ ,p_{n} $ is good if $ gcd(i,p_{i})&gt;1 $ . Levko considers a permutation beautiful, if it has exactly $ k $ good elements. Unfortunately, he doesn’t know any beautiful permutation. Your task is to help him to find at least one of them.

## 说明/提示

In the first sample elements $ 4 $ and $ 3 $ are good because $ gcd(2,4)=2&gt;1 $ and $ gcd(3,3)=3&gt;1 $ . Elements $ 2 $ and $ 1 $ are not good because $ gcd(1,2)=1 $ and $ gcd(4,1)=1 $ . As there are exactly 2 good elements, the permutation is beautiful.

The second sample has no beautiful permutations.

## 样例 #1

### 输入

```
4 2
```

### 输出

```
2 4 3 1```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
-1
```

# 题解

## 作者：wind_whisper (赞：2)

## $\text{Description}$
给定 $n,k$，你需要构造一个序列，使得集合 $\{i|{1\le i \le n,\gcd(i,a_i)>1}\}$ 的元素个数恰好为 $k$.
## $\text{Solution}$
首先，由于 $1$ 必然不合法， $k=n$ 时必然无解.  

$k<n$时，对于 $2\le i\le k+1$ 我们让 $a_i=i$，从而使其全部合法.  
使 $a_{k+2}=1,a_1=n,a_i=i-1(k+3\le i\le n)$，从而使剩下的全部元素均不合法.  
注意特判 $m=n-1$ 的情况.  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=25;
#define r rand()
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}
int n,m;

int main(){
  #ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  if(n==m){
    printf("-1");return 0;
  }
  printf("%d ",m==n-1?1:n);
  for(int i=2;i<=m+1;i++) printf("%d ",i);
  if(m!=n-1) printf("1 ");
  for(int i=m+3;i<=n;i++) printf("%d ",i-1);
  return 0;
}

```


---

## 作者：流绪 (赞：2)

一个数组含 1 到 n，设 pi 是它下标，求一个排列，让这个数组中有 k 个数 gcd(i,pi)>1，其他的gcd(i,pi)=1.

这题要构造答案，首先我们发现两个相邻的数的最大公约数肯定是 1，然后除了1，其他数和自己的最大公约数肯定大于 1。所以我们让 k 个位置放它本身，另外的位置放与它相邻的数就好啦。

我的做法是最后面 k 个数放与它本身相等的数，然后前面 n-k 个数每个后移一位，然后第 n-k 位放到第一位。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#include<cstring>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
using namespace std;
int a[maxn];
int main()
{
	ios::sync_with_stdio(false);
	int n,k;
	cin >> n >> k;
	if(n==k)
	{
		cout << -1; 
		return 0;
	}
	cout << n-k<<" ";
	for(int i=2;i<=n;i++)
		if(i<=n-k)
			cout << i-1 << " ";
		else
			cout << i << " ";
	return 0; 
}  
```


---

## 作者：Yamchip (赞：1)

## 1.题意
求一个 $1$ 到 $n$ 的排列，其中有 $k$ 个数与下标不互质。
## 2.思路
构造题。
我们先拿一个 $a_{i}=i$ 的序列，然后把 $2$ 到 $n-k$ 的数向前挪一位，再把 $1$ 放到第 $n-k$ 位，剩下 $k$ 个数不动。

为什么这么做呢？
$2$ 到 $n-k$ 的数挪到自己的前一位，也就是第 $i-1$ 位，因为 $i$ 和 $i-1$ 互质，所以这 $n-k-1$ 个数与下标互质。由于 $1$ 与任何数互质，所以 $1$ 在第 $n-k$ 位也互质。我们都知道除了 $1$ 以外，其他数都不与自己互质，所以这 $k$ 个数满足题目中“其中有 $k$ 个数与下标不互质”的条件。

再看无解，由于 $1$ 与任何数互质，所以一个排列最多 $n-1$ 个数与下标不互质，因此 $n=k$ 时输出 $-1$。
## 3.Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k;
int main()
{
    cin >> n >> k;
    if(n == k)
    {
        cout << "-1";
        return 0;
    }
    for(int i = 1;i < n - k;i++)
        cout << i + 1 << " ";
    cout << "1 ";
    for(int i = n - k + 1;i <= n;i++)
        cout << i << " ";
    return 0;
}
```

---

## 作者：JoyLosingK (赞：1)

# 题意 

给定 $n,k$,要求你构造出一个序列 $A$，使得在 $1\le i\le n$ 内，恰好有 $k$ 个 $i$ 满足 $\gcd(i,A_i)>1$。

# 解法

首先你想啊，我们构造的序列的相邻的两个数一定是互质的。

为啥？因为 $\gcd(i,i+1)=1$ 啊！

继续想，$\gcd(1,A_1)$ 一定等于 $1$，所以当 $k=n$ 时必定无解，直接输出 ```-1``` 即可。

对于其他数，可以让最后的 $k$ 个数造与它相等的数，这样对于每一个数，都有 $\gcd(i,A_i)>1$。

前面 $n-k$ 个数的话，我们把它们每个往后移 $1$ 位，这样，都有 $\gcd(i,A_i)＝1$。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[100002],n,k;
int main()
{   cin>>n>>k;
    if(n==k){cout<<-1;return 0;}
	else{ cout<<n-k<<" ";
	    for(int i=2;i<=n;i++)
		    if(i<=n-k) cout<<i-1<<" ";
		        else cout<<i<<" ";
	} return 0; 
}  
```
建议再做 P9632，和本题思路非常相似。

---

## 作者：L_shadow (赞：1)

## 思路：
以下的 $i$ 都为整数。

显然，有一下三点性质：

1. $1$和任何数的最小公约数为 $1$。
2. $\gcd(i,i+1)=1$。
3. $\gcd(i,i)=i$。

因此，由于第一条性质，如果 $n=k$，就会出现为无解的情况。

对于 $a_1$，无论我们放任何数，都是不可能合法的，所以最后再决定放啥。

对于 $a_2$ 到 $a_{k+1}$，这部分我们搞成合法的，而且这部分个数恰好为 $k$，由于第三条性质，我们直接放它们的下标就行。

对于 $a_{k+2}$ 到 $a_n$，这部分我们搞成不合法的，由于第二条性质，我们直接放它们的下标 $+1$ 的值，特别的，我们在 $a_n$ 的位置放上 $1$。

构造完了，发现 $k+2$ 没有被用到，于是在 $a_1$ 的位置上放 $k+2$。

当然，在 $n=k+1$ 时，我们在每一个位置放上它们的下标即可。

## AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int main() {
	scanf("%d%d",&n,&k);
	if(n==k) {
		printf("-1");
		return 0;
	}
	if(n==k+1) {
		for(int i=1; i<=n; i++) printf("%d ",i);
		return 0;
	}
	printf("%d ",n);
	for(int i=2; i<=k+1; i++) printf("%d ",i);
	for(int i=k+2; i<n; i++) printf("%d ",i+1);
	printf("1");
}
```

---

## 作者：_shine_ (赞：0)

因为是看 $i,a_i$ 的最大公约数，而因为当序列为 $1,2,3,\dots,n$ 的形式时，可以发现的是除了 $1$ 以外的所有 $a_i$ 均满足条件。

所以说当 $n=k$ 时显然无解。

那么如果并不是 $k=n-1$ 的情况，就意味着必须要使得一些的值与编号互质，则很简单的是只要让序列的值为 $\left(i,i-1\right),\left(1,i\right)$（先后可调换）的形式就必然有不合法的。

所以只需要分两半输出，一半使其无法满足条件，一半满足条件即可。

注意先前的特判。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define pii pair<int,int>
#define lx first
#define ly second
int n,k;
signed main(){
	cin >> n >> k;
	if(n==k){puts("-1");return 0;}
	for(int i=1;i<n-k;++i)cout << i+1 << " ";cout << 1 << " ";
	for(int i=n-k+1;i<=n;++i)cout << i << " ";
	return 0;
}
```

---

## 作者：wwxxbb (赞：0)

### 题意

> 给定 $n,k$，你需要构造一个**排列**，使得集合 $\{i|{1\le i \le n,\gcd(i,a_i)>1}\}$ 的元素个数恰好为 $k$。

### 思路

考虑以下性质：

- $\gcd(1,i)=1$
- $\gcd(i,i)=i$
- $\gcd(i,i+1)=1$

证明略。

由第 $1$ 条，由于 $i=1$ 时 $\gcd(i,a_i)=1$，如果 $k=n$，则 $i=1$ 时不满足条件，无解。

无解的条件判了，下面考虑构造策略。因为构造策略很多，下面只讲 $1$ 种。

由第 $3$ 条，我们可以使 $a_i\leftarrow i+1,i\in[1,n-k-1]$；再由 $2$ 条，$a_i\leftarrow i,i\in[n-k+1,n]$，最后使 $a_{n-k}=1$。

- 为什么 $1$ 要赋给 $a_{n-k}$？

- 因为我们这个序列是一个**排列**，所以各个元素互不相同，且值域为 $[1,n]$，如果我们 $a_i\leftarrow i+1,i\in[1,n-k]$，或者 $a_i\leftarrow i,i\in[n-k,n]$，就会发现有 $1$ 个数用了 $2$ 次，且 $1$ 没用过。

这样构造的一个好处是可以避免分类讨论，思维量较少。、

附上代码：

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    if (k == n) return cout << -1, 0;
    for (int i = 1; i < n - k; i ++) cout << i + 1 << ' ';
    cout << 1 << ' ';
    for (int i = n - k + 1; i <= n; i ++) cout << i << ' ';
    return 0;
}
```

双倍经验 [P9632](https://www.luogu.com.cn/problem/P9632)。

这题条件反了，所以只需要将 $n-k$ 改为 $k$ 即可，且特判条件要换成 $k=0$。

```c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, k;
    cin >> n >> k;
    if (!k) return cout << -1, 0;
    for (int i = 1; i < k; i ++) cout << i + 1 << ' ';
    cout << 1 << ' ';
    for (int i = k + 1; i <= n; i ++) cout << i << ' ';
    return 0;
}
```

---

## 作者：Flaw_Owl (赞：0)

# CF361B Levko and Permutation 题解

原题链接：[Levko and Permutation](https://www.luogu.com.cn/problem/CF361B)

双倍经验：[P9632 [ICPC2020 Nanjing R] K Co-prime Permutation](https://www.luogu.com.cn/problem/P9632)

## 题目分析

乍一看好像是复杂的数学问题，实际上朴素地思考之后就可以得到三个结论：

1. $\gcd(a,a) = a$，也就是任何大于 $1$ 的数和自己的最大公约数都大于 $1$（即满足条件）
2. $\gcd(a,a+1) = 1$，也就是任何数和自己的邻居的最大公约数都为 $1$（即互质）
3. $\gcd(1,a) = 1$，也就是任何数和 $1$ 的最大公约数都是 $1$。

所以就可以很简单地这样考虑：题目要求这个序列中 $\gcd(i,a_i) > 1$ 的元素个数恰好有 $k$ 个，换句话说也就是 $\gcd(i,a_i) = 1$ 的元素个数恰好有 $n-k$ 个。考虑到 $1$ 的特殊性，不妨恰好将第 $n-k$ 位放上 $1$，而其他的位上都放它们的邻居；第 $n-k+1$ ~ $n$ 位都填自身。这样就可以保证满足题目的条件。

接下来是思考特殊情况：即什么时候无法构造出这个序列，需要输出 $-1$？根据上面的思路，考虑到 $\gcd(1,a) = 1$，这个序列中至少有一个 $\gcd(a,b) = 1$ 的情况。因此当 $n = k$ 时不可能成立，因为根据上面的推断，此时 $\gcd(i,a_i) = 1$ 的元素个数有 $0$ 个。

## AC 代码

```cpp
#include <iostream>
#include <cctype>

using namespace std;

int read()
{
    int x = 0, f = 1;
    char ch = 0;
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int maxN = 1e5 + 5;

int n, k;

int ans[maxN];

int main()
{
    n = read();
    k = read();
    if (k == n)
    {
        printf("-1");
        return 0;
    }
    for (int i = 1; i < n - k; i++)
        ans[i] = i + 1;
    ans[n - k] = 1;
    for (int i = n - k + 1; i <= n; i++)
        ans[i] = i;
    for (int i = 1; i <= n; i++)
    {
        printf("%d", ans[i]);
        if (i != n)
            printf(" ");
    }
    return 0;
}
```

---

## 作者：zhaohanwen (赞：0)

### 题意简述

填一个 $1-n$ 的排列使得恰好有 $k$ 个数和其下标互质。

### 题目分析

我们都知道，$\gcd(a,a+1)=1$，也就是两个相邻的数一定互质。我们还知道 $\gcd(a,a)>1(a\not= 1)$，所以，我们让 $k$ 个位置的数和它的下标相等，另外的位置就放和它相邻的数。这样就可以保证刚好有 $k$ 个数和其下标互质。

一种可行的解法是最后 $k$ 个数和下标相等，之前的数 $a_i$ 都变成 $i-1$，同时第一个数变成 $n-k$。最后注意 $n=k$ 时无解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int num[N];
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,k;
	cin>>n>>k;
	if(n==k)
	{
		cout<<-1<<endl;
	}
	else
	{
		num[1]=(n-k);
		for(int i=2;i<=(n-k);i++)
		{
			num[i]=i-1;
		}
		for(int i=(n-k+1);i<=n;i++)
		{
			num[i]=i;
		}
		for(int i=1;i<=n;i++)
		{
			cout<<num[i]<<' ';
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：_QWQ__QWQ_ (赞：0)

前置芝士——[最大公约数 - OI Wiki](https://oi-wiki.org/math/number-theory/gcd/)

题目其实很简单，我们可以知道一些最大公约数的性质：

有一个数 $x$，则：

$$
\gcd(x,x-1)=1 \\ \gcd(1,x)=1
$$

那么其实只要将前 $k$ 个数都往后移一位，第 $k$ 位用 $1$ 即可，后面的全是原数。

注意特判 $k=n$ 和 $n=1,k\ne0$ 的情况，$k=n$ 是因为第一个需要是 $1$，$n=1,k\ne0$ 是因为只有一个的时候一定是 $0$ 个。

CFAC 记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/6kxltz8t.png)

AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl "\n"
using namespace std;
const int maxn=1e6+5;
int n,k;
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>k;
	if(k==n||n==1&&k!=0){
		cout<<"-1"<<endl;
		return 0;
	}
	for(int i=1;i<n-k;i++){
		cout<<i+1<<' ';
	}
	cout<<1<<' ';
	for(int i=n-k+1;i<=n;i++){
		cout<<i<<' ';
	}
	return 0;
}
```

---

