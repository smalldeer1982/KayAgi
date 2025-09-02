# [ABC269G] Reversible Cards 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc269/tasks/abc269_g

$ 1 $ から $ N $ までの番号がついた $ N $ 枚のカードがあります。  
 カード $ i $ の表には整数 $ A_i $, 裏には整数 $ B_i $ が書いてあります。 また、$ \sum_{i=1}^N\ (A_i\ +\ B_i)\ =\ M $ です。  
 $ k=0,1,2,...,M $ について次の問題を解いてください。

> $ N $ 枚のカードがすべて表側が見える状態で並べられています。あなたは $ 0 $ 枚以上 $ N $ 枚以下のカードを選び、それらを裏返すことができます。  
>  見えている数の和が $ k $ になるには最小で何枚のカードを裏返す必要がありますか？枚数を出力してください。  
>  ただし、どのようにカードを裏返しても見えている数の和が $ k $ にならない場合は $ -1 $ を出力してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i,\ B_i\ \leq\ M $
- $ \sum_{i=1}^N\ (A_i\ +\ B_i)\ =\ M $
- 入力される値はすべて整数

### Sample Explanation 1

例えば $ k=0 $ のときは、カード $ 2 $ のみを裏返せば見えている数の和を $ 0+0+0=0 $ にすることができて、これが最適です。 また、$ k=5 $ のときは、すべてのカードを裏返せば見えている数の和を $ 2+0+3=5 $ にすることができて、これが最適です。

## 样例 #1

### 输入

```
3 6
0 2
1 0
0 3```

### 输出

```
1
0
2
1
1
3
2```

## 样例 #2

### 输入

```
2 3
1 1
0 1```

### 输出

```
-1
0
1
-1```

## 样例 #3

### 输入

```
5 12
0 1
0 3
1 0
0 5
0 2```

### 输出

```
1
0
1
1
1
2
1
2
2
2
3
3
4```

# 题解

## 作者：Francais_Drake (赞：3)

### 题意
有 $n$ 张卡片，第 $i$ 张卡片正面有数字 $a_i$，背面有数字 $b_i$，同时 $\sum_{i=1}^n (a_i+b_i)=m$。所有卡片起初均被正面朝上地放置。

对于 $\forall k\in[0,m]$，输出使得所有卡片朝上的数字之和为 $k$ 时，需要翻面至少多少张卡片；如果不能通过翻面卡片使得所有卡片朝上的数字之和为 $k$ 则输出 $-1$。

$1\le n\le 2\times 10^5,0\le m\le 2\times 10^5,0\le a_i,b_i\le m$。
### 解法
考虑每张卡片翻过来后，对朝上的数字和造成的贡献为 $b_i-a_i$。将 $b_i-a_i$ 相同者合并之后，问题即转化为一个多重背包问题。同时 $\sum_{i=1}^n (a_i+b_i)=m$ 意味着 $\sum_{i=1}^n (\max(a_i,b_i)-\min(a_i,b_i))\le m$。此时显然 $\max(a_i,b_i)-\min(a_i,b_i)$ 的取值只会有 $O(\sqrt m)$ 种，也就意味着 $b_i-a_i$ 也只有 $O(\sqrt m)$ 种（$b_i-a_i$ 可能为 $\pm(\max(a_i,b_i)-\min(a_i,b_i))$）。单调队列优化多重背包即可，时间复杂度为 $O(m\sqrt m)$。（为什么这么【】的题我一直没想出来
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=200010;
int n,m,l,r,i,j,k,p,w,t,b;
int v[maxn],c[maxn],q[maxn],dp[2][maxn];
bool x,y=1;
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i){
		scanf("%d%d",&l,&r);
		w+=l; c[i]=r-l; 
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][w]=0; w=0;
	sort(c+1,c+n+1); 
	c[n+1]=1145141919;
	for(i=t=1;i<=n;++i){
		if(c[i+1]!=c[i]){
			if(c[i]<0){
				w=-c[i];
				for(j=0;j<w;++j){
					for(p=m-j,k=0;p>=0;p-=w) v[p]=dp[x][p]-(k++);
					l=1; r=k=0; b=m-j+w*t;
					for(p=m-j;p>=0;p-=w){
						if(q[l]>b) ++l;
						while(l<=r&&v[q[r]]>=v[p]) --r;
						q[++r]=p; b-=w;
						dp[y][p]=v[q[l]]+(k++);
					}
				}
			}
			else if(c[i]>0){
				w=c[i];
				for(j=0;j<w;++j){
					for(p=j,k=0;p<=m;p+=w) v[p]=dp[x][p]-(k++);
					l=1; r=k=0; b=j-w*t;
					for(p=j;p<=m;p+=w){
						if(q[l]<b) ++l;
						while(l<=r&&v[q[r]]>=v[p]) --r;
						q[++r]=p; b+=w;
						dp[y][p]=v[q[l]]+(k++);
					}
				} 
			}
			if(c[i]) swap(x,y); t=1;
		}
		else ++t;
	}
	for(i=0;i<=m;++i){
		if(dp[x][i]>=0x3f3f3f3f) dp[x][i]=-1;
		printf("%d\n",dp[x][i]);
	}
	return 0;
}
```

---

## 作者：Register_int (赞：2)

首先，将所有卡片朝上放置，反转一个卡片 $i$ 获得的值为 $a_i-b_i$，那么就转化成了 0/1 背包问题。带负权只要正反都做一遍就可以了。

此时的复杂度非常优秀，所以需要优化。可以发现题目中给的一个很有用的限制条件：$\sum(a_i+b_i)=m$，这意味着 $a_i+b_i$ 的取值不超过 $\sqrt m$ 种，也就是 $a_i-b_i$ 的取值不超过 $2\sqrt m$ 种。直接把相同的按一起做多重背包即可。时间复杂度不会算，大致是 $O(n\sqrt{m})\sim O(n\sqrt{m\log m})$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 2e5 + 10;

map<int, int> mp;

int n, m, sum;

int v[MAXN], w[MAXN], tot;

int dp[MAXN];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1, a, b; i <= n; i++) scanf("%d%d", &a, &b), mp[b - a]++, sum += a;
	memset(dp, 0x3f, sizeof dp), dp[sum] = 0;
	for (auto x : mp) {
		int tv = x.first, s = x.second, k = 1;
		while (k <= s) v[++tot] = k * tv, w[tot] = k, s -= k, k <<= 1;
		if (s > 0) v[++tot] = s * tv, w[tot] = s;
	}
	n = tot;
	for (int i = 1; i <= n; i++) {
		if (v[i] > 0) for (int j = m; j >= v[i]; j--) dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
		else for (int j = 0; j <= m + v[i]; j++) dp[j] = min(dp[j], dp[j - v[i]] + w[i]);
	}
	for (int i = 0; i <= m; i++) printf("%d\n", dp[i] == 0x3f3f3f3f ? -1 : dp[i]);
}
```

---

## 作者：Reunite (赞：1)

无聊题。

### 一
---

注意到 $\sum a_i+b_i=m\le 2\times10^5$，初始时所有面朝上，直接令 $a_i=b_i-a_i$，现在只需求出对 $a_i$ 做背包后和为 $f_i$ 所需的最小数量。直接做很蠢，题目的条件都没用。

显然，$|a_i|>B$ 的最多只有 $\frac{m}{B}$ 个，对这个直接做事 $\frac{nm}{B}$ 的。

剩下的值域不超过 $B$，把它们缩在一起变成多重背包问题。多重背包可以用单调队列做到线性，但是常数较大，所以直接偷懒写二进制分组，做到 $Bm\log n$。

显然可以平衡复杂度，做到 $m\sqrt{n\log n}$，可以通过，负数体积打个偏移量就行了。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define pi 200000
using namespace std;

int n,m,S,B=200;
int a[200005];
int b[200005];
int c[200005];
int f[400005];
int g[400005];
map <int,int> mp;

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

int main(){
	in(n),in(m);
	for(int i=1;i<=n;i++){
		int x,y;
		in(x),in(y);
		S+=x;
		a[i]=y-x;
	}
	memset(f,0x3f,sizeof(f));
	f[pi]=0;
	for(int i=1;i<=n;i++){
		if(abs(a[i])>B){
			memcpy(g,f,sizeof(f));
			for(int j=-pi;j<=pi;j++)
				g[j+pi]=min(g[j+pi],f[j+pi-a[i]]+1);
			memcpy(f,g,sizeof(g));
		}
		else mp[a[i]]++;
	}
	int tt=0;
	for(auto tmp:mp){
		int x=tmp.first,y=tmp.second;
		for(int j=0;j<=20;j++)
			if(y>=(1<<j)) tt++,b[tt]=x*(1<<j),c[tt]=1<<j,y-=(1<<j);
		if(y) tt++,b[tt]=x*y,c[tt]=y;
	}
	for(int i=1;i<=tt;i++){
		memcpy(g,f,sizeof(f));
		for(int j=-pi;j<=pi;j++)
			if(j-b[i]>=-pi&&j-b[i]<=pi)
				g[j+pi]=min(g[j+pi],f[j+pi-b[i]]+c[i]);
		memcpy(f,g,sizeof(g));
	}
	for(int i=-S;i<=m-S;i++)
		printf("%d\n",f[i+pi]>n?-1:f[i+pi]);

	return 0;
}
```

---

