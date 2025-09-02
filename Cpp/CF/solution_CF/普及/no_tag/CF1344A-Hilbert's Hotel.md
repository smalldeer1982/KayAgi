# Hilbert's Hotel

## 题目描述

Hilbert's Hotel is a very unusual hotel since the number of rooms is infinite! In fact, there is exactly one room for every integer, including zero and negative integers. Even stranger, the hotel is currently at full capacity, meaning there is exactly one guest in every room. The hotel's manager, David Hilbert himself, decides he wants to shuffle the guests around because he thinks this will create a vacancy (a room without a guest).

For any integer $ k $ and positive integer $ n $ , let $ k\bmod n $ denote the remainder when $ k $ is divided by $ n $ . More formally, $ r=k\bmod n $ is the smallest non-negative integer such that $ k-r $ is divisible by $ n $ . It always holds that $ 0\le k\bmod n\le n-1 $ . For example, $ 100\bmod 12=4 $ and $ (-1337)\bmod 3=1 $ .

Then the shuffling works as follows. There is an array of $ n $ integers $ a_0,a_1,\ldots,a_{n-1} $ . Then for each integer $ k $ , the guest in room $ k $ is moved to room number $ k+a_{k\bmod n} $ .

After this shuffling process, determine if there is still exactly one guest assigned to each room. That is, there are no vacancies or rooms with multiple guests.

## 说明/提示

In the first test case, every guest is shifted by $ 14 $ rooms, so the assignment is still unique.

In the second test case, even guests move to the right by $ 1 $ room, and odd guests move to the left by $ 1 $ room. We can show that the assignment is still unique.

In the third test case, every fourth guest moves to the right by $ 1 $ room, and the other guests move to the right by $ 5 $ rooms. We can show that the assignment is still unique.

In the fourth test case, guests $ 0 $ and $ 1 $ are both assigned to room $ 3 $ .

In the fifth test case, guests $ 1 $ and $ 2 $ are both assigned to room $ 2 $ .

## 样例 #1

### 输入

```
6
1
14
2
1 -1
4
5 5 5 1
3
3 2 1
2
0 1
5
-239 -2 -100 -3 -11```

### 输出

```
YES
YES
YES
NO
NO
YES```

# 题解

## 作者：tommymio (赞：13)

感觉楼下的题解讲的都不是特别清楚，推出了结论但是过程非常的混乱，这里提供一种比较清晰的解法.

题目讲的很清楚，一个无限长的数轴，很容易可以想到数论.

当一次移动后存在两个数的位置相同，则必有不定方程 $x+a_{x \bmod n}=y+a_{y \bmod n}$ 存在 **至少一个整数解**.

对上式进行如下变形

$x-y=a_{y \bmod n}-a_{x \bmod n}$

设 $x=k_1n+i,y=k_2n+j$，则上式可写作 $\ k_1n+i-k_2n-j=a_j-a_i$

$\Rightarrow (k_1-k_2)n=a_j-a_i+j-i=(a_j+j)-(a_i+i)$。

设 $c_i=a_i+i$，则上式可变为 $(k_1-k_2)n=c_j-c_i$。

$(k_1-k_2)$ 显然为整数，于是改为求解是否存在 $c_j,c_i$，令 $(c_j-c_i) | n$，利用整除的性质可以得到当 $(c_j-c_i)|n$ 时，$c_j,c_i$ 在模 $n$ 意义下有相同的余数。

此题就变为判断是否存在 **两个或两个以上** 的 $a_i+i$ 在 模 $n$ 意义下有相同余数，**如果存在则输出 "NO"，不存在则输出 "YES"**，用桶记录一下即可求解.

**Show the Code**
```cpp
#include<cstdio>
int t[1000005];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
int main() {
	int T=read();
	while(T--) {
		int n=read(),flag=1;
		for(register int i=0;i<n;++i) ++t[((read()+i)%n+n)%n];//-(n-1)+n~(n-1)+n
		for(register int i=0;i<2*n;++i) if(t[i]>1) {flag=0;break;}  
		for(register int i=0;i<2*n;++i) t[i]=0;
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：MY_Lee (赞：3)

观察一下，是个数论题。

发现有一个取模运算非常讨厌，考虑想办法去掉模运算，怎么去呢？

很显然，要么转化掉，然鹅这里似乎不太可能 ~~（是我孤陋寡闻了？）~~，要么，可以来一把同余，把他消掉。

这个同余看起来很有希望，我们做一下。

令数轴上的两个数 $x=pn+r,y=qn+r$。

根据题中信息，在变换之后，
$$
\left\{
\begin{aligned}
x'&=x+a_{x\bmod n}=pn+r+a_r\\
y'&=y+a_{y\bmod b}=qn+r+a_r
\end{aligned}
\right.
$$
假设 $x'=y'$，则

$$
\begin{aligned}
pn+r+a_r&=qn+r+a_r\\
pn&=qn\\
\because n&\ne0\\
\therefore p&=q
\end{aligned}
$$

什么东西？$p=q$ 代表的是 $x=y$ 啊！

于是我们得到了一个重要结论：
> 变换之后，所有对模 $n$ 同余的整数的变换值均互不相同。

那好办了，只需要对 $1\rightarrow n$ 的数做一下变换就过啦。

不过注意：$a_i$ 的范围很大，普通的数组下标存不下，记得开 `map`。

复杂度：$O(tn\log w)$，$t$ 是组数，$n$ 是枚举每个数，$\log$ 是 `map` 的复杂度。

$\rm{Code:}$

```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
map<int,bool>mp;
int t,n,a[200005],tmp;
inline int mod(int x,int m){
	return (x+(1000000000/m*m))%m;
}
inline void answer(){
	for(register int i=1;i<=n;i++){
		tmp=mod(i+a[i],n);
		if(mp[tmp]==true){
			printf("NO\n");return ;
		}
		mp[tmp]=true;
	}
	printf("YES\n");return ;
}
int main(){
	scanf("%d",&t);
	for(register int c=1;c<=t;c++){
		scanf("%d",&n);mp.clear();
		for(register int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		answer();
	}
	return 0;
}
```
---

**写在最后** 

[我](https://moon-snow.blog.luogu.org/)也不晓得 $10^4\times(2\times10^5)\times30$ 怎么就水过去了。而且跑的还不慢啊(最慢的点 $187\ ms$)。

---

## 作者：Priori_Incantatem (赞：3)

[题目链接](https://www.luogu.com.cn/problem/CF1344A)

### 题目大意
有一条数轴，在它的每个整数位置上有一个人  
现在对于所有整数 $k$，位置 $k$ 上的人会移动到位置 $k+a_{k \mod n}$  
问在所有人移动一次后，是否每个位置上都恰好有一个人

### 解题思路
我们可以把这题当成图论来做  
对于每一个人的移动操作，我们把它视为一条有向边 $[k,k+a_{k \mod n}]$
注意，我么需要把每条边的起点与终点 $\mod n$，使得 $a$ 中的每一个元素恰好对应一个位置

在加完边后，每一条以点 $x$ 为终点的边表示有一个人在移动后停留在了点 $x$。而又因为每个点 $x$ 恰好是一条有向边的起点（有一个人离开了点 $x$），所以我们计算答案是只需判断每个点的入度是否为 $1$ 就可以了。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int Maxn=200000+10,inf=0x3f3f3f3f;
int a[Maxn];
int ind[Maxn],n;
int main()
{
//	freopen("in.txt","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;++i)
		{
			scanf("%d",a+i);
			if(a[i]>=0)a[i]%=n;
			else a[i]=-((-a[i])%n);
			if(i+a[i]<0)a[i]+=n;
			if(i+a[i]>=n)a[i]-=n;
			++ind[i+a[i]];
		}
		for(int i=0;i<n;++i)
		if(ind[i]>1){puts("NO");goto GG;}
		puts("YES");
		GG:;
		memset(ind,0,sizeof(ind));
	}
	return 0;
}
```

---

## 作者：hujiasheng1234 (赞：2)

结论：所有的 $a_i + i \text{ }(0 \le i < n)$ 模 $n$ 的余数若两两不同则为	`YES`,否则为 `NO`。

给出一种简单的证明：

若有 $(a_i+i) \bmod n = (a_j+j) \bmod n$，则 $n \mid a_i+i-a_j-j$，而 $(i + x \times n) \bmod n = i \bmod n = i$，则必有 $a_i+x \times n + i = a_j + j$，所以会有两个整数的位置相同

可以用 `map` 判断重复,记得负数取模要在取模前加上模数。

```
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;
const int mx=2e5+5;
int T,n,a[mx];
map<int,int> mp;
void solve(){
	mp.clear();
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++){
	    if(mp[((a[i]+i)%n+n)%n]){
	    	cout<<"NO"<<endl;
	    	return ;
		}
		mp[((a[i]+i)%n+n)%n]=1;
	}
	cout<<"YES"<<endl;
}
signed main(){
	ios::sync_with_stdio(0);cout.tie(0);cin.tie(0);
    cin>>T;
    while(T--) solve(); 
    return 0;
}

---

## 作者：killer_queen4804 (赞：2)

这个题只要读懂题意就不难了，哎，这题意看了半小时才看懂，是 $k+a\left[ k\% n \right]$， 丫的这样写不就行了吗，非得写成数学公式混淆题意，题目就是问会不会有两个数移动完之后会重合，我们可以看一下最后一组样例，$0 \sim 4$ 移动完之后分别是 $-234,4,-93,5,-2$,先只考虑 $k$ 为正数时，那么接下来的 $5\sim 9$ 也就是分别在 $-234,4,-93,5,2$ 上分别加 $5$，也就是加 $n$，所以我们可以思考一下，什么时候会不重复呢，答案是这 $5$ 个数取余 $5$ 各不相同时就不会重复，这应该挺显而易见吧，所以只要给 $0\sim n-1$ 移动完一次看看取余是否各不相同就可以了，各不相同也就是 $0\sim n-1$ 每个数都出现且仅出现一次；
```cpp
#include<bits/stdc++.h>
#define ll long long
#define lowbit(i) ((-i)&(i))
using namespace std;
const ll inf=1e18;
const ll mod=10000;
ll n,a[200005],t;
int main(){
	//freopen("in.txt","r",stdin);
	scanf("%lld",&t);
	while(t--){
        scanf("%lld",&n);
        for(int i=0;i<n;i++){
            scanf("%lld",&a[i]);
            a[i]=((a[i]+i)%n+n)%n;
        }
        sort(a,a+n);
        ll flag=1;
        for(int i=0;i<n;i++)
        if(a[i]!=i){flag=0;break;}
        if(flag) printf("YES\n");
        else printf("NO\n");
	}
	return 0;
}

```


---

## 作者：jimmy2021 (赞：0)

题目要求找到两个数 $x$ 和 $y$ 满足：

$x + a_{x \bmod n} = y + a_{y \bmod n}$

将上式做一个简单移项：

$x - y = a_{y \bmod n} - a_{x \bmod n}$

假设 $x = k_1 \times n + i, y = k_2 \times n + j$，那么变化上式得：

$(k_1 \times n + i) - (k_2 \times n + j) = a_j - a_i$

拆括号：

$k_1 \times n + i - k_2 \times n - j = a_j - a_i$

简单移项：

$(k_1 - k_2) \times n = a_j + j - a_i - i$

加括号：

$(k_1 - k_2) \times n = (a_j + j) - (a_i + i)$

假设 $c_i = a_i + i$，那么上式变化为：

$(k_1 - k_2) \times n = c_j - c_i$

由于 $(k_1 - k_2)$ 为整数，那么题目要求变化为：**是否可以找到两个或以上的 $c_i$ 使得他们模 $n$ 的余数一样，如果有，输出`NO`，否则输出`YES`**（`YES`代表没有两个移动后的下标相同，反之亦然）

于是，我们用一个桶记录即可。

代码：
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <limits.h>
#include <cstring>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int INF = 0x3f3f3f3f, INF_BIT = 0x3f;

const int N = 2e5 + 10;

int t;
int n;
int x;

#define getmod(x, p) (((x) % p + p) % p)
bool f[N];

int main(){
    scanf("%d", &t);
    while(t--){
        memset(f, false, sizeof(f));
        bool flag = false;
        
        scanf("%d", &n);
        for(int i = 0;i < n;i++){
            scanf("%d", &x);
            
            int val = getmod(x + i, n);
            if(f[val]) flag = true;
            else f[val] = true;
        }
        
        if(flag) puts("NO");
        else puts("YES");
    }
    return 0;
}
```

---

## 作者：0x3F (赞：0)

考虑对所有的（无穷多个）$k$ 按模 $n$ （不模 $n$ 模什么呢？）的余数进行分类。

如果原先的 $k$ 为 $pn+i$，则 $k \bmod n = i$， 需要右移 $a_i$，右移后变成了 $pn + (i+a_i)$。

由于 $p$ 为任意整数，它必定包含了所有模 $n$ 同余 $(i + a_i)$ 的整数。

所以易证如果存在 $0 \leqslant i \lt j \lt n$ 使得 $i + a_i \equiv j + a_j \pmod n$ 则答案为 `NO`，否则答案为 `YES`。

用 $n$ 个桶存储即可，如果一个桶装了超过 $1$ 个数即为 `NO`，否则为 `YES`。

注意三点：

1. $i$ 从 $0$ 开始取！

1. 负数要转正！（正负通用万能公式：$(a \bmod p + p) \bmod p$）

1. `memset` 会爆掉！

上代码：（使用 `goto` 不是好习惯，小盆友们不要跟我学）

```cpp
#include <bits/stdc++.h>
using namespace std;
int T, n, a[200010];
bool vis[200010];
int main() {
	cin >> T;
	while (T--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> a[i];
			a[i] = ((a[i] + i) % n + n) % n;
			vis[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			if (vis[a[i]]) {
				cout << "NO" << endl;
				goto fail;
			}
			vis[a[i]] = 1;
		}
		cout << "YES" << endl;
		fail:;
	}
	return 0;
}
```


---

## 作者：流绪 (赞：0)

$k$ 房间的人移动到 $k+a_{k modn}$ 房间，由此可以看出以 $n$ 个房间为一个循环节，每两个循环节的移动方式是一样的。那么怎么判断有没有两个人移到同一个房间了呢？

暴力方法：定义一个标记数组，把移动后的房间记录一下，看看有没相同的。

考虑优化这个方法，同一个循环节内的移动显然可以用上述方法在 $O(n)$ 下解决；不同循环节的只有在两个人移动方向不同时才会进入同一个房间，例如，我移动到了我这一组的第k个房间，下一组的某个人移动到了我这一组的第 $k$ 个房间。由此我们可以将移动到的房间模 $n$，这样就可以用一组来替代所有组，从而 $O(n)$ 得解。注意可能是负数要 %$n+n$。

下面是$AC$代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f7f7f7f7f 
#define maxn 1000010
#define ri register int
#define il inline
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define mod 998244353
#define db(x) cout << x << endl; 
#define eps 0.0001
using namespace std;
int a[maxn],b[maxn];
int s[maxn]; 
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--)
	{
		int n;
		cin >> n;
		for(int i=0;i<n;i++)
			b[i] = 0;//初始化标记数组 
		for(int i=0;i<n;i++)
			cin >> a[i],((a[i]%=n)+=n)%=n;
		int flag = 1;
		for(int i=0;i<n;i++)
			b[(i+a[i])%n]++;
		for(int i=0;i<n;i++)
			if(b[i]!=1)
				flag = 0;
		if(flag)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	return 0;
}
```


---

