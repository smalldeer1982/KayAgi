# Quantity of Strings

## 题目描述

Just in case somebody missed it: this winter is totally cold in Nvodsk! It is so cold that one gets funny thoughts. For example, let's say there are strings with the length exactly $ n $ , based on the alphabet of size $ m $ . Any its substring with length equal to $ k $ is a palindrome. How many such strings exist? Your task is to find their quantity modulo $ 1000000007 $ ( $ 10^{9}+7 $ ). Be careful and don't miss a string or two!

Let us remind you that a string is a palindrome if it can be read the same way in either direction, from the left to the right and from the right to the left.

## 说明/提示

In the first sample only one string is valid: "a" (let's denote the only letter of our alphabet as "a").

In the second sample (if we denote the alphabet letters as "a" and "b") the following strings are valid: "aaaaa" and "bbbbb".

## 样例 #1

### 输入

```
1 1 1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 2 4
```

### 输出

```
2
```

# 题解

## 作者：kevin1616 (赞：7)

### 审题
用 $m$ 中不同的字符填入 $n$ 个位置，使得长度为 $k$ 的子串都是回文串。求方案数对 $10^9+7$ 取模的结果。
***
### 思路
首先考虑极端情况。

+ 当 $k=1$ 时，每个字符都可以任填。所以方案数为 $m^n$。
+ 当 $k=n$ 时，整个字符串为一个回文串。回文串需要两两配对，如果 $n$ 是奇数，那么中心位也可以自由选择。所以可自由选择位数为 $\displaystyle\lceil\frac{n}{2}\rceil$，于是方案数即为 $m^{\displaystyle\lceil\frac{n}{2}\rceil}$。
+ 当 $k>n$ 时，不需要考虑回文，所以方案数为 $m^n$。

现在来考虑一般情况。

首先，只要 $1<k<n$，那么在字串可以在字符串中一位一位向右移动。如果 $k$ 是奇数，有以下例子：

当 $n=7,k=5$，假设字符串的每个位置分别为 `abcdefg`，那么：

+ 当子串为 `abcde` 时，易知 $a=e$，$b=d$。
+ 当子串为 `bcdef` 时，易知 $b=f$，$c=e$。
+ 当子串为 `cdefg` 时，易知 $c=g$，$d=f$。

最终得到：$a=c=e=g$，$b=d=f$。

推广到 $k$ 为奇数，那么总共只可以有 $2$ 种字符。方案数为 $m^2$。

按照同样的方法，推广到 $k$ 为偶数，那么总共只可以有 $1$ 种字符。方案数为 $m$。这里就不举例论述了，方法是相同的。

最后，发现 $m^n$ 和 $m^{\displaystyle\lceil\frac{n}{2}\rceil}$ 过大，需要使用快速幂。记得取模。
***
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 1e9 + 7;
int n,m,k;
int fpow(int x,int y,int z){ //快速幂
    int res = 1;
    while(y){
        if(y & 1) res = res * x % z;
        x = x * x % z;
        y >>= 1;
    }
    return res;
}
signed main(){
    cin >> n >> m >> k;
    if(k == 1) cout << fpow(m,n,MOD); //k=1的情况
    else if(k == n) cout << fpow(m,(n + 1) / 2,MOD); //k=n的情况
    else if(k > n) cout << fpow(m,n,MOD); //k>n的情况
    else if(k % 2 == 1) cout << fpow(m,2,MOD); //k为奇数的情况
    else if(k % 2 == 0) cout << m; //k为偶数的情况
    return 0;
}

```
![通过记录](https://cdn.luogu.com.cn/upload/image_hosting/jnqqpakx.png)

不抄题解，从我做起！

---

## 作者：Running_a_way (赞：3)

绝世唐题。和别人 duel 的时候死活调不出来发现还有 $k > n$ 的情况 /xk

---

注意到当 $k$ 为奇数时，字符串只能为形如 `ABAB...BABA` 的形式，此时答案为 $m^2$；$k$ 为偶数时，字符串只能为形如 `AAA...AAA` 的形式，此时答案为 $m$。

但是还没做完。我们发现 $k$ 可以为 $1$。此时字符串随便填就好了，答案 $m^n$。同理，$k=n$ 时答案为 $m^{\left \lceil n/2 \right \rceil}$。

但是还没做完。我们发现 $k$ 可以 $> n$。此时因为不存在长度为 $k$ 的回文串，所以字符串可以随便填，答案为 $m^n$。

upd on 2024.10.23: 修改了一处笔误。

---

## 作者：Lily_White (赞：3)

并查集。

对于一个回文串$S_{1\dots n}$，一定有$S_i=S_{n-i+1}$对于所有$1 \le i \le n$成立。因此，如果两个字符一定相等，我们就把它们合并入一个集合。最后我们数一下集合的总数$c$，因为这些位置每一个都可以从字母表中任意选择一个填上。所以答案是$m^c$。

Code:
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define pb push_back
#define mp make_pair
#define lsh(i) (1 << (i))
#define lshll(i) (1LL << (i))
#define repn(i, n) for (int (i) = 1; (i) <= n; (i)++)
#define rep(i, n) for (int (i) = 0; (i) < n; (i)++)
const int INF = 0x3f3f3f3f;
const long double EPS = 1e-6;
const int MOD = 1e9 + 7;
const int N = 2019;
struct dsu {
	int fa[N];
	void makeSet(int n) {repn(i, n) fa[i] = i;}
	int find(int x) {
		return x == fa[x] ? x: fa[x] = find(fa[x]);
	}
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx != fy) fa[fx] = fy;
	}
	int count(int n) {
		int ans = 0;
		for (int i = 1; i <= n; i++) if (fa[i] == i) ans++;
		return ans;	
	}
}s;
int n, m, k;
LL qpow(LL a, LL b, LL p) {
	LL ans = 1;
	for (; b; b >>= 1) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
	}
	return ans;
}
int main() {
	scanf("%d%d%d", &n, &m, &k);
	s.makeSet(n);
	for (int i = 1; i + k - 1 <= n; i++)
		for (int j = i, p = i + k - 1; j <= p; j++, p--) 
			s.merge(j, p);
	printf("%d", (int)qpow(m, s.count(n), MOD));
	return 0;
}
``

---

## 作者：YFF1 (赞：2)

## 思路：
不难发现，如果把题目中要求的那些字符之间必须相等的关系抽象成图上的边，每个连通块内部都两两相等，就可以把这道题转化为一道基础图论题。注意到数据范围很小，所以我们可以把每个回文子串当中的每个下标枚举一遍，对应的字符看作给它们两个建了一条边，然后用并查集求解。不过答案可能很大，所以还要再加一个快速幂。

答案是什么呢？假设并查集求出来 $p$ 个连通块，那么答案就是 $m^p$。


## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,k,mod=1e9+7,sum,fa[200005];
map<int,int>mp;
int find(int x){//并查集
	if(fa[x]==x)return x;
	return fa[x]=find(fa[x]);
}
int qpow(int a,int b){//快速幂
	int ans=1,cnt=a;
	while(b>0){
		if(b&1==1)ans=ans*cnt%mod;
		cnt=cnt*cnt%mod;
		b>>=1;
	}
	return ans;
}
signed main () {
	cin>>n>>m>>k;
	if(k>n){//注意这个情况，容易漏掉
		cout<<qpow(m,n)%mod;
		return 0;
	}
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n-k+1;i++){
		for(int l=i,r=i+k-1;l<=r;l++,r--)fa[find(l)]=find(r);//建图
	} 
	for(int i=1;i<=n;i++)mp[find(i)]=1;//求连通块个数
	sum=qpow(m,mp.size());
	cout<<sum%mod;
	return 0;
}
```

---

## 作者：gxp123 (赞：1)

# CF150 B - Quantity of Strings

## 题意

现在有一个长度为 $N$ 的字符串，它的字典集为 $M$。也就是说每一位有 $M$ 种不同的字母可以选。

对于这个字符串所有连续的长度为 $K$ 的子串都必须是回文串，请问有多少种不同的方案。

由于答案可能很大，请将答案对 $10^9+7$ 取模。

- $1 \leq N,M,K \leq 2000$

## 题解

分类讨论一下即可。

- $K = 1$ 或 $N < K$，我们每个位置上可以随便填字符，答案就是 $N^M$。

- $N = K$，就直接枚举可能的回文串数量，答案时 $(\lceil \frac{N}{2} \rceil)^M$。
- $N > K$ 且 $N$ 是奇数，那只能 $\text{abab...}$ 式（$a,b$ 可以相同）的填，答案是 $M^2$。
- $N > K$ 且 $N$ 是偶数，那只能 $\text{aaa...}$ 式的填，答案是 $M$。

## code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;
const int mod = 1e9 + 7;
const int maxN = 2000 + 10;
ll qpow(ll a,int k){
    ll res = 1;
    while (k){
        if(k & 1)   res = res * a % mod;
        a = a * a % mod;
        k = k >> 1;
    }
    return res;
}
int n,m,k;

int main(){
    scanf("%d%d%d",&n,&m,&k);
    if(k == 1 || n < k){
        cout << qpow(m,n) << endl;
        return 0;
    }else if(n == k){
        cout << qpow(m,(n + 1) >> 1) << endl;
    }else if((k & 1)){
        cout << 1ll * m * m % mod << endl;
    }else
        cout << m << endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

递推：
首先建图：
~~和楼上的很像，具体不多说了~~。然后跑板子DFS，算出联通分量。

下面递推：

我飞快地敲出了递推式：(伪~~biao~~代~~cheng~~码)

```
for(i -> cnt)
ans *= 26,ans %= 1e9 + 7      cnt为连通分量的个数
```
一运行连样例都没过
再看题目：

```
based on the alphabet of size m
```
原来是乘M     ~~我说输入为什么有个多余的呢？一定是我太弱了~~

废话不多说，上代码，记得开long long

[标程(建议先AC再食用)](https://codeforces.ml/contest/150/submission/78646966)

---

## 作者：QWQ_123 (赞：0)

模拟小数据：

当 $k=1$ 或 $n<k$，此时随便填方案为 $m^n$。

考虑两个例子：  
> 当 $k=4$，$a_1,a_2,a_3,a_4,a_5,a_6$。  
>	那么对于第一个长度为 $k$ 的字串 $a_1=a_4,a_2=a_3$。
>	第二个：$a_1=a_2=a_3=a_4=a_5$。  
> 第三个：$a_1=a_2=a_3=a_4=a_5=a_6$。  
> 我们发现对于一个 $k$ 是偶数的字符串，除了 $n=k$ 的情况，其他都是这个串所有字母都相等。

> 当 $k=5$，$a_1,a_2,a_3,a_4,a_5,a_6$。  
>	那么对于第一个长度为 $k$ 的字串 $a_1=a_5,a_2=a_4$。
>	第二个：$a_1=a_3=a_5,a_2=a_4=a_6$。
> 我们发现对于一个 $k$ 是奇数的字符串，除了 $n=k$ 的情况，其他都是编号为奇数的位上的字母都相同，编号为偶数的位字母都相同。

然后分讨输出即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const long long mod = 1e9 + 7;

int n, m, k;

long long power(long long a, long long b) {
	long long res = 1;
	for (; b; b >>= 1, a = a * a % mod)
		if (b & 1) res = res * a % mod;
	return res;
}

int main() {
	scanf("%d%d%d", &n, &m, &k);

	if (k == 1 || n < k) printf("%lld\n", power(m, n));
	else if (n == k) printf("%lld\n", 1ll * power(m, (n + 1) / 2));
	else if (k & 1) printf("%lld\n", 1ll * m * m % mod);
	else printf("%lld\n", 1ll * m % mod);

	return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：0)

##  题目翻译
现在有一个长度为 $N$ 的字符串，它的字典集为 $M$。也就是说每一位有 $M$ 种不同的字母可以选。对于这个字符串所有连续的长度为 $K$ 的子串都必须是回文串，请问有多少种不同的方案。$(1 \leq N,M,K \leq 2000)$ 由于答案可能很大，请将答案对 $10^9+7$ 取模。
## 代码（有注释，且含思路，请勿抄袭）
```cpp
#include<iostream>
#define mod 10000000007
long long int n,m,k,m2=1;
using namespace std;
int main()
{
	cin>>n>>m>>k;
	if(k>n||k==1)//第一种情况，每一位直接有M种情况，乘法原理，算好了
		while(n--)
			m2=(m2*m)%mod;
	else if(k==n)//如果长度相同，根据回文截断，再去做乘法
	{
		n=(n+1)/2;
		while(n--)
			m2=(m2*m)%mod;
	}
	else if(k%2)//只有两位
		m2=m*m;
	else//就一位
		m2=m;
	cout<<m2<<endl；//输出
}
```

---

## 作者：YangHHao (赞：0)

### 题意简述

求出长度为 $n$，字典大小为 $m$ 的字符串的数量，满足其每个长度为 $k$ 的字串都是回文串。


范围： $n,m,k \le 2000$

### 题解

这里，我们根据回文串对称中心的位置（体现为 $k$ 的奇偶性），进行分类讨论。（以下内容在默认 $n>k$ 情况下进行）

1. $k$ 为奇数

此时对称中心在点上，如图（两色箭头表示根据一种颜色的对称得两字符相等）

![k为奇数](https://cdn.luogu.com.cn/upload/image_hosting/41gwauon.png)

由于对称前后位置奇偶性不变，且归纳可得所有同奇偶位置的字符处处相等，故共有两个等价类，此时答案为 $m^2$。

2. $k$ 为偶数

此时对称中心在两点之间，如图

![k为偶数](https://cdn.luogu.com.cn/upload/image_hosting/pg7aluhs.png)

可得所有字符相等，共一个等价类，此时答案为 $m$。

在推出这个答案时，我兴冲冲地跑去交了代码，然后，“Wrong answer on test 3”。

特判！！

具体就是两点：一个是 $k$ 与 $n$ 的大小关系，一点是 $k$ 与 $n$ 的边界数值。

当 $k > n$，无回文串，答案为 $m^n$。

当 $k = n$，仅一个回文串，答案为 $m ^ {\left \lceil \frac{n}{2} \right \rceil}$。

当 $k = 1$，相当于无回文串，答案为 $m^n$。

当 $n = 1$，也是相当于无回文串，答案为 $m$。（其实这种情况已经被包含于 $k > n$ 或 $k = 1$ 中了）

### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(int x=0,int f=1){
    char ch=getchar();
    while(ch<'0'||ch>'9')f=(ch=='-'?-1:1),ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x*f;
}
inline void write(int x){
    char F[200];
    int tmp=x>0?x:-x;
    if(x<0)putchar('-');
    if(x==0)putchar('0');
    int cnt=0;
    while(tmp>0){
	    F[cnt++]=tmp%10+'0';
        tmp/=10;
    }
    while(cnt>0)putchar(F[--cnt]);
    putchar('\n');
}
const int mod=1e9+7;
int n,m,k;
inline int qp(int a,int b){
	int res=1;
	while(b){
		if(b&1)res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
signed main(){
	n=read(),m=read(),k=read();
	if(k>n)write(qp(m,n));
	else if(k==n)write(qp(m,(n+1)/2));
	else if(k==1)write(qp(m,n));
	else if(n==1)write(m);
	else if(k&1)write(qp(m,2));
	else write(m);
}


```


---

