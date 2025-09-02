# [ABC381E] 11/22 Subsequence

## 题目描述

在本题中，11/22 字符串的定义与 A 问题和 C 问题相同。

当字符串 $T$ 满足以下所有条件时，称 $T$ 为 **11/22 字符串**。

- $|T|$ 是奇数。这里 $|T|$ 表示 $T$ 的长度。
- 第 $1$ 个字符到第 $\frac{|T|+1}{2}-1$ 个字符均为 `1`。
- 第 $\frac{|T|+1}{2}$ 个字符为 `/`。
- 第 $\frac{|T|+1}{2}+1$ 个字符到第 $|T|$ 个字符均为 `2`。

例如，`11/22`、`111/222`、`/` 是 11/22 字符串，而 `1122`、`1/22`、`11/2222`、`22/11`、`//2/2/211` 不是。

给定一个由 `1`、`2`、`/` 组成的长度为 $N$ 的字符串 $S$，请处理 $Q$ 个查询。

每个查询给出 $L$、$R$，请你求出 $S$ 的第 $L$ 个字符到第 $R$ 个字符组成的**连续**子串中，作为 $T$ 时，11/22 字符串的**（不要求连续的）**子序列的最大长度。若不存在这样的子序列，则输出 $0$。

## 说明/提示

### 约束

- $1 \leq N \leq 10^5$
- $1 \leq Q \leq 10^5$
- $S$ 是由 `1`、`2`、`/` 组成的长度为 $N$ 的字符串
- $1 \leq L \leq R \leq N$
- $N, Q, L, R$ 均为整数

### 样例解释 1

对于第 $1$ 个查询，$S$ 的第 $1$ 个字符到第 $7$ 个字符组成的子串为 `111/212`。该字符串包含 `11/22` 作为子序列，这是 11/22 字符串中长度最大的。因此答案为 $5$。对于第 $2$ 个查询，$S$ 的第 $9$ 个字符到第 $12$ 个字符组成的子串为 `1122`。该字符串不包含任何 11/22 字符串作为子序列，因此答案为 $0$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
12 5
111/212/1122
1 7
9 12
3 6
4 10
1 12```

### 输出

```
5
0
3
1
7```

# 题解

## 作者：Little_x_starTYJ (赞：16)

### 前言
2024/11/22 星期五是我的生日。

Atcoder 很良心地把 $A\sim F$ 的题目全都命名为 $11/22$ 或者 $1122$，[详见](https://atcoder.jp/contests/abc381/tasks)。

时隔几个月，又一次排名接近 $1000$（实际排名 $1006$，还吃了 $7$ 发罚时）。

### 题目大意
> 此问题中的 11/22 字符串的定义与题目 A 和 C 的定义相同。


如果字符串 $T$ 满足以下所有条件，那么称 $T$ 为 **11/22 字符串**：


- $|T|$ 是奇数。其中 $|T|$ 表示 $T$ 的长度。
- 第 $1$ 个字符到第 $\frac{|T| + 1}{2} - 1$ 个字符全都为 `1`。
- 第 $\frac{|T| + 1}{2}$ 个字符是 `/`。
- 第 $\frac{|T| + 1}{2} + 1$ 个字符到第 $|T|$ 个字符全都为 `2`。


例如 `11/22`， `111/222` 和 `/` 都是 11/22 字符串， 而 `1122`， `1/22`， `11/2222`， `22/11` 和 `//2/2/211` 都不是。


给你一个长度为 $N$ 且只包含 `1`， `2`， `/` 的字符串 $S$ 还有查询次数 $Q$。 


每次查询给出一组 $L$ 和 $R$。

请你找到从 $S$ 的第 $L$ 个字符到第 $R$ 个字符组成的 **（连续的）** 子串 $T$ 是 11/22 字符串的最大长度，如果不存在这样的子串，请输出 `0`。

### 赛时方法 1
这是我最开始尝试的方法，但是赛后 Atcoder 加了两组 Hack，把这个思路 Hack 掉了。

如果有解，那么 $a_l \sim a_r$ 之间一定包含至少一个 `/`。

那么我们可以先把 `/` 的位置存储起来，对于每次询问找到 $l\sim r$ 里面的所有 `/` 的位置，再看看 `/` 前面 $1$ 的少还是 `/` 后面的 $2$ 少，最后统计最大答案即可。

对于查询 `/` 前面的 $1$ 的数量，我第一反应是线段树，后来才发现可以直接前缀和。

最坏时间复杂度为 $\mathcal{O}(nq)$。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, q;
string a;
int seat[100010], id2;
int number1[100010], number2[100010];

signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q >> a;
	a = " " + a;  //询问是从 1 开始的
	for (int i = 1; i <= n; i++) {
		number1[i] = number1[i - 1];
		number2[i] = number2[i - 1];
		if (a[i] == '/') {
			seat[++id2] = i;
		} else if (a[i] == '1') {
			number1[i]++;
		} else {
			number2[i]++;
		}
	}
	seat[id2 + 1] = 1e18;
	while (q--) {
		int l, r;
		cin >> l >> r;
		int p = lower_bound(seat + 1, seat + 1 + id2, l) - seat;
		if (seat[p] < l || seat[p] > r) {
			cout << "0\n";
		} else {
			int ans = 0;
			for (; seat[p] <= r; p++) {
				int count1 = number1[seat[p]] - number1[l - 1];
				int count2 = number2[r] - number2[seat[p]];
				ans = max(min(count1, count2) * 2, ans);
			}
			cout << ans + 1 << "\n";
		}
	}
	return 0;
}
```
### 赛时方法 2
额，在用方法 $1$ 通过这道题 $5$ 分钟后，我又想到了正解，但是懒得打。直到今天早上发现 Atcoder 加了 Hack 数据才打。

我们先来看看方法 $1$ 的 Hack 数据应该是什么样子。

```
1e5 1e5
/////......////
1 1e5
2 1e5-1
3 1e5-2
...
```
因此我们就不能把这个区间里面的每个 `/` 都遍历一遍。

我们很容易发现只有 `/` 前面的 $1$ 的数量与 `/` 后面的 $2$ 的数量相差尽可能小，答案才会更大。

所以，我们可以二分 `/` 的位置，如果 $1$ 的数量比 $2$ 多，那么我们就向后推。反之亦然。

但是在最后的时候需要看看 `/` 取前面一个是否更优，因为存在取第 $i$ 个 `/` 时，满足 $number_2 > number_1$，取第 $i - 1$ 个 `/` 时，满足 $number_1 > number_2$，而取第 $i - 1$ 个更优。

最坏时间复杂度为 $\mathcal{O}(q \log n)$。

CODE：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, q;
string a;
int seat[100010], id2;
int number1[100010], number2[100010];

inline int ans(int l, int mid, int r) {
	return min(number2[r] - number2[mid], number1[mid] - number1[l - 1]) * 2 + 1;
}
signed main() {
	ios::sync_with_stdio(false);
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> q >> a;
	a = " " + a;
	for (int i = 1; i <= n; i++) {
		number1[i] = number1[i - 1];
		number2[i] = number2[i - 1];
		if (a[i] == '/') {
			seat[++id2] = i;
		} else if (a[i] == '1') {
			number1[i]++;
		} else {
			number2[i]++;
		}
	}
	seat[id2 + 1] = 1e18;
	while (q--) {
		int l, r;
		cin >> l >> r;
		int p = lower_bound(seat + 1, seat + 1 + id2, l) - seat;
		if (seat[p] < l || seat[p] > r) {
			cout << "0\n";
		} else {
			int k = upper_bound(seat + 1, seat + 1 + id2, r) - seat - 1;
			int ll = p, rr = k;
			while (ll < rr) {
				int mid = ll + rr >> 1;
				if (number1[seat[mid]] - number1[l - 1] < number2[r] - number2[seat[mid]]) {
					ll = mid + 1;
				} else {
					rr = mid;
				}
			}
			int res = ans(l, seat[ll], r);
			if (seat[ll - 1] >= l && seat[ll - 1] <= r)
				res = max(res, ans(l, seat[ll - 1], r));
			cout << res << "\n";
		}
	}
	return 0;
}
```

---

## 作者：zcz0263 (赞：9)

$O(n+q)$ 的做法，目前是最优解第一。

我们先进行如下定义：  
$pre_j$ 表示 $s_1\sim s_j$ 中 `1` 的数量  
$suf_j$ 表示 $s_j\sim s_n$ 中 `2` 的数量

然后我们发现第 $i$ 次询问时的结果就是

$$ans_i=1+2*\max_{s_j='/'}\left\{\min(pre_j-pre_{l_i-1},suf_j-suf_{r_i+1})\right\}$$

然后我们套路地考虑这个 $\min$ 会取到啥。  

- 取到 $pre_j-pre_{l_i-1}$ 时，即 $pre_j-pre_{l_i-1}\leq suf_j-suf_{r_i+1}$，变形为 $pre_j-suf_j\leq pre_{l_i-1}-suf_{r_i+1}$ 发现是一个前缀 $max$。
  
- 取到 $suf_j-suf_{r_i+1}$ 时，即 $pre_j-pre_{l_i-1}> suf_j-suf_{r_i+1}$，变形为 $pre_j-suf_j>pre_{l_i-1}-suf_{r_i+1}$ 发现是一个后缀 $max$。

因为可能是负数，所以要加偏移量。

最后特判一下区间内是否有 `/` 即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define max(...) max({__VA_ARGS__})
#define min(...) min({__VA_ARGS__})
#define tomx(x,...) ((x)=max((x),__VA_ARGS__))
#define tomn(x,...) ((x)=min((x),__VA_ARGS__))
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define N 200001
#define X 100000
struct askpre{
	vi c=vi(N);
	void add(int p,int x){
		p+=X;
		tomx(c[p],x);
	}
	void cl(){
		rep(i,1,N){
			tomx(c[i],c[i-1]);
		}
	}
	int ask(int p){
		p+=X;
		return c[p];
	}
}pr;
struct asksuf{
	vi c=vi(N);
	void add(int p,int x){
		p+=X;
		tomx(c[p],x);
	}
	void cl(){
		per(i,N-1,0){
			tomx(c[i],c[i+1]);
		}
	}
	int ask(int p){
		p+=X;
		return c[p];
	}
}su;
int n,q;
vi pre(N),suf(N),prx(N);
string s;
main(){
	ios::sync_with_stdio(0),cin.tie(nullptr);
	cin>>n>>q>>s;
	read(n);
	read(q);
	s.resize(n+1);
	s[0]=' ';
	rep(i,1,n) s[i]=IO::gc();
	rep(i,1,n){
		pre[i]=pre[i-1]+(s[i]=='1');
		prx[i]=prx[i-1]+(s[i]=='/');
	}
	per(i,n,1){
		suf[i]=suf[i+1]+(s[i]=='2');
	}
	rep(i,1,n){
		if(s[i]=='/'){
			pr.add(pre[i]-suf[i],pre[i]);
			su.add(pre[i]-suf[i],suf[i]);
		}
	}
	pr.cl();
	su.cl();
	rep(i,1,q){
		int l,r;
		cin>>l>>r;
		if(!(prx[r]-prx[l-1])){
			IO::pc('0');
			IO::pc('\n');
			continue;
		}
		write(1+2*max(pr.ask(pre[l-1]-suf[r+1])-pre[l-1],su.ask(pre[l-1]-suf[r+1])-suf[r+1]));
		wl;
	}
	flush();
}

```

---

## 作者：Yxy7952 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc381_e)

建议评黄。

## 题目大意

输入一个长度为 $n$ 的字符串 $s$（$1\le s_{i}\le  2$），从这个序列中寻找一个最长的子字符串（可以为空也可以不连续）满足下面 $2$ 个要求。

+ 子字符串长度为奇数。

+ 子字符串的格式为 ```11...11/22...22```，这里左边 $1$ 的个数和 $2$ 的个数相等。

## 思路（二分+前缀和）

这道题的定义和 $A$ 题是一样的，相信各位暴力都会写，但是时间复杂度将达到巨额的 $O(Qn^2)$，这个时间无法通过此题。

考虑二分优化：

因为所有的 ```11/22``` 字符串中间都必须有一个 ```/```，所以将所有 ```/``` 所在的下标存储下来，并进行二分。

这里根据代码进行讲解：
```cpp
while(Q--){
	cin>>L>>R;
	int l=1,r=m,ans=0;
	while(l<=r){
		int mid=l+(r-l)/2;
		if(a[mid]<L) l=mid+1;
		else if(a[mid]>R) r=mid-1;
		else{
			int c1=s1[a[mid]]-s1[L-1],c2=s2[R]-s2[a[mid]-1];
			ans=max(ans,min(c1,c2)*2+1);
			if(c1<=c2) l=mid+1;
			else r=mid-1;
		}
	}
	cout<<ans<<"\n";
}
```
在代码中 ```/``` 出现的次数存储为 $m$。

$a_{i}$ 表示第 $i$ 个 ```/``` 在原字符串中的位置。

$s1_{i}$ 表示 $1\sim i$ 中 $1$ 的个数。

$s2_{i}$ 表示 $1\sim i$ 中 $2$ 的个数。

---------

一共 $Q$ 次询问，每次询问进行二分查找。左端点设为 $1$，右端点设为 $m$。

首先进行两个判断，如果左端点的位置或右端点的位置超出边界，进行对应收缩。

然后利用前缀和优化，用 $O(1)$ 的时间复杂度求出 $L\sim a_{mid}$ 中 $1$ 的个数，和 $a_{mid}\sim R$ 中 $2$ 的个数。

再在 $c1$ 和 $c2$ 中取一个最小值，为什么这样做？举个例子：

$eg.$ ```111/212```。

在这个例子里，左边 $1$ 的个数为 $3$，右边 $2$ 的个数为 $2$，但是我们显然只能取少的数组成字符串（在此例中，为少的 $2$），否则数字会不够用。

最后，如果 $c1\le c2$，那显然，我们把 $mid$ 的位置往左移，可能会制造更多的 $1$。反之，也一样。
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,Q,L,R,m;
string s;
int a[100005],s1[100005],s2[100005];
using namespace std;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>Q>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='/') a[++m]=i;
		s1[i]=s1[i-1]+(s[i]=='1');
		s2[i]=s2[i-1]+(s[i]=='2');
	}
	while(Q--){
		cin>>L>>R;
		int l=1,r=m,ans=0;
		while(l<=r){
			int mid=l+(r-l)/2;
			if(a[mid]<L) l=mid+1;
			else if(a[mid]>R) r=mid-1;
			else{
				int c1=s1[a[mid]]-s1[L-1],c2=s2[R]-s2[a[mid]-1];
				ans=max(ans,min(c1,c2)*2+1);
				if(c1<=c2) l=mid+1;
				else r=mid-1;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：cjh20090318 (赞：4)

赛时竟然把好多暴力做法放过了，不能理解出题人的数据强度。

但是这里讲的是正确解法，不是暴力。

## 题意

当一个字符串 $T$ 满足以下所有条件时，它就是好的字符串：

- $\vert T \vert \bmod 2 = 1$。
- $T[1 : \frac{\vert T \vert +1}{2} - 1] = \texttt{1}$。
- $T[\frac{|T|+1}{2}] = \texttt{/}$。
- $T[\frac{|T|+1}{2} + 1 : \vert T \vert ] = \texttt{2}$。

给定长度为 $N$ 由`1`、`2`和`/`组成字符串 $S$，有 $Q$ 次询问 $L$ 和 $R$。假设 $T = S[L:R]$。求 $T$ 的好的子序列（不一定连续）的最大长度。如果不存在这样的则输出 $0$。

## 分析

以任意一个 `/` 作为中心点，分别不断向左边和右边扩展 `1` 和 `2`，最长的子串取决于 `1` 和 `2` 数量的最小值。

这个问题貌似并不是很好用数据结构维护，想到二分答案。

设当前二分的长度为 $x$，判定即找到 $L$ 的右边（包含 $L$）的第 $x$ 个 `1` 和 $R$ 的左边（包含 $R$）的第 $x$ 个 `2`，判断这两个位置中间是否有 `/`。

判断一个区间是否有 `/` 可以使用前缀和，于是现在的问题变成了如何能快速的找到第 $x$ 个，直接暴力跳肯定是不行的，可以使用倍增预处理。

接着就可以发现这个二分是不必要的，直接倍增求答案即可。

时间复杂度 $O(n \log n + Q \log n)$，空间复杂度 $O(n \log n)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#define MAXN 100005
using namespace std;
int n,q;
char s[MAXN];
int a[MAXN],nx[MAXN][18],pr[MAXN][18];//'/' 字符的前缀和，下一个 2，上一个 1。
int main(){
	scanf("%d%d %s",&n,&q,s+1);
	for(int i=1;i<=n;i++) a[i]=a[i-1]+(s[i]=='/');
	for(int i=1;i<=n+1;i++) pr[i][0]=i&&s[i-1]=='2'?i-1:pr[i-1][0];
	nx[n+1][0]=n+1;//注意边界情况。
	for(int i=n;i>=0;--i) nx[i][0]=i<n&&s[i+1]=='1'?i+1:nx[i+1][0];
	for(int k=1;k<18;k++)
		for(int i=0;i<=n+1;i++) pr[i][k]=pr[pr[i][k-1]][k-1],nx[i][k]=nx[nx[i][k-1]][k-1];//倍增预处理。
	for(int l,r;q--;){
		scanf("%d%d",&l,&r);
		bool fl=a[r]-a[l-1];//判断这段区间是否有 /，如果没有答案一定为 0。
		int ans=0;
		--l,++r;//因为包含，所以向两边多跳一个。
		for(int k=17,x,y;k>=0;--k){
			x=nx[l][k],y=pr[r][k];
			if(x<y&&a[y]-a[x-1]>0) ans|=1<<k,l=x,r=y;
		}
		printf("%d\n",ans?ans<<1|1:(int)fl);
	}
	return 0;
}
```

---

## 作者：hgcnxn (赞：3)

## AT_abc381_e [ABC381E] 11/22 Subsequence题解

### 思路
先考虑暴力。对于每一次询问，寻找区间内的“/”，每找到一个“/”就统计区间内它左边 $1$ 的个数 $x$ 与右边 $2$ 的个数 $y$（下文中的 $x$ 和 $y$ 均代表这个意思），则以该“/”为中心的“11/22”串的长度最长为 $2\times\min(x,y)+1$。该做法总时间复杂度为 $O(qn^2)$，寄了。

不难发现，我们可以将 $O(n)$ 统计 $1$ 和 $2$ 的个数改为用前缀和维护，将总时间复杂度降至 $O(qn)$，但这还不够。

在上文的暴力中可以发现，随着“/”的位置向右移，$x$ 的值单调不降，$y$ 的值单调不升。因此，对于某个“/”，如果当前 $y$ 的值小于 $x$ 时，将它向右移一定不优。同理，如果当前 $x$ 的值小于 $y$ 时，将它向左移一定不优。所以，我们可以对“/”的位置进行二分，进一步将总时间复杂度降为 $O(q\log n)$，可以通过本题。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+2;
int p1[N],p2[N],k[N],n,cnt,q,l,r,ll,rr,mid,x,y,ans;
char a[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p1[i]=p1[i-1];
		p2[i]=p2[i-1];
		if(a[i]=='1')p1[i]++;
		else if(a[i]=='2')p2[i]++;
		else k[cnt++]=i;
	}
	while(q--){
		cin>>ll>>rr;
		l=0,r=cnt-1,ans=0;
		while(l<=r){
			mid=(l+r)/2;
			if(k[mid]>rr)r=mid-1;
			else if(k[mid]<ll)l=mid+1;
			else{
				x=p1[k[mid]-1]-p1[ll-1];
				y=p2[rr]-p2[k[mid]];
				ans=max(ans,2*min(x,y)+1);
				if(x>y)r=mid-1;
				else if(x<y)l=mid+1;
				else break;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：zrl123456 (赞：3)

[[ABC381E] 11/22 Subsequence](https://www.luogu.com.cn/problem/AT_abc381_e)  

题目考察：二分，前缀和。  
题目简述：  
定义 11/22 序列为由 $k$ 个 `1`，$1$ 个 `/` 和 $k$ 个 `2` 拼接而成的字符串（$k$ 为 **非负整数**）。$q$ 次询问，每次询问求长度为 $n$ 的字符串 $s$ 的 $l$ 到 $r$ 位的最长的是 11/22 序列的子序列的长度。  
数据范围：
- $1\le l\le r\le n\le 10^5$。
- $1\le q\le 10^5$。
- 保证 $s$ 只有 `1`、`2` 和 `/` 组成。
---
贪心的想，对于每一个 `/`，他前面的所有 `1` （设有 $sum$ 个）和后面的所有 `2` （设有 $num$ 个）都可以放在他的前面（后面）形成一个子序列，但 `1` 和 `2` 的数量要相等，所以最长长度为 $2\min(sum,num)+1$。  
前面 `1` 的个数和后面 `2` 的个数均可用前（后）缀和预处理得到（设为 $sum_i$ 和 $num_i$）。  
但是我们截取 $[l,r]$ 区间后，$sum_i$ 要减去 $sum_{l-1}$，$num_i$ 要减去 $num_{r+1}$，我们就无法预处理每个 `/` 的最长长度了。  

我们发现，最后 $sum$ 和 $num$ 减完后应是这样的：  
![](https://cdn.luogu.com.cn/upload/image_hosting/5c6n4snc.png)  
$sum$ 是单调非递减的，$num$ 是单调非递增的。  
所以，当 $sum_i<num_i$ 时，$i$ 左边的 $j$ 一定会满足：
- $sum_j<num_j$。
- $sum_j\le sum_i$。

则最终最长长度一定更短，所以我们应该向右找。  
$sum_i>num_i$ 同理。  

那么现在我们就想到了二分，按照上述方法模拟即可。  

最终总体时间复杂度为 $\Theta(n+q\log n)$。  
[代码](https://www.luogu.com.cn/record/190515229)

---

## 作者：seika27 (赞：2)

### 思路
不难发现要想组成这个序列 ```/``` 是必要的。

所以我们可以把每个 ```/``` 的位置都记下来，我们把这个数组记作 $c$。

然后对于区间 $[l,r]$ 找到所有 $[i,j]$,对于任意 $k$ 属于 $[i,j]$ 都有 $l\leq c_k \leq r$。

接下来我们发现题目中说不要求连续并且要求最优，所以对于一个 $k$。我们可以把 $[l,k-1]$ 中的所有 ```1``` 都选上，我们把 ```1``` 的数量记作 $cnt1$。同理可得我们可以把 $[k+1,r]$ 中的所有 ```2``` 都选上，我们把 ```2``` 的数量记作 $cnt2$。

所以对于这个 $k$ 的答案就是 $\min(cnt1_k,cnt2_k)\times2+1$。

接下来我们考虑如何快速求解。

对于区间里每一个值的答案，都可以归为两类。

一种是 $cnt_k<cnt2_k$，一种是 $cnt1_k \geq cnt2_k$。

注意到 $cnt1$ 不降，$cnt2$ 不增。

所以答案肯定在最后一个 $cnt1_k<cnt2_k$ 的位置，或者在第一个 $cnt1_k\geq cnt2_k$ 的位置取到。使用二分即可。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
#define cin std::cin
#define cout std::cout
const int N=1e5+5;
int n,q;
std::string s;
int a[N],b[N],c[N];
int cl;
inline int calc(int x,int l,int r)
{
	return std::min(a[c[x]]-a[l-1],b[c[x]]-b[r+1])*2+1;
}
inline int thfind(int l,int r,int u,int v)
{
	while(l<=r)
	{
		int mid=l+r>>1;
		if(a[c[mid]]-a[u-1]>b[c[mid]]-b[v+1])r=mid-1;
		else l=mid+1;
	}
	return std::max(calc(l,u,v),calc(r,u,v));
}
signed main()
{
	std::ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>q>>s;
	s=' '+s;
	for(int i=1,j=n;i<=n;++i,--j)
	{
		a[i]=a[i-1]+(s[i]=='1');
		b[j]=b[j+1]+(s[j]=='2');
		if(s[i]=='/')c[++cl]=i;
	}
	while(q--)
	{
		int l,r;
		cin>>l>>r;
		int x=std::lower_bound(c+1,c+1+cl,l)-c;
		int y=std::upper_bound(c+1,c+1+cl,r)-c-1;
		if(!x||!y||y<x){cout<<0<<'\n';continue;}
		cout<<thfind(x,y,l,r)<<'\n';
	}
}
```

---

## 作者：whx2009 (赞：2)

## 本题思路：
这道题我们其实可以知道针对每一个 $/$ 的最大贡献就是左边一的个数和右边二的个数的最小值乘二加一，那么显然答案在一个前缀中。

考虑二分一和二的最小值，我们可以根据这个二分出来的最小值看看在当前区间中一达到数值的最左边与二达到数值的最右边（显然有单调性，出现一的数量与二的数量都是单调不降的），如果一的位置在二的位置的左边，且中间有 $\$ 就合法，往大的二分。否则往小了找。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct f{int l,id,r;}a[100005];
bool cmp(f x,f y){return x.r<y.r;}
int ans[100005],sum[100005],sum1[100005],sum2[100005];
signed main(){
	int n,q;cin>>n>>q;
	string s;cin>>s;s=' '+s;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1],sum1[i]=sum1[i-1];sum2[i]=sum2[i-1];
		if(s[i]=='1') sum[i]++;
		if(s[i]=='2') sum1[i]++;
		if(s[i]=='/') sum2[i]++;
	}
	for(int i=1;i<=q;i++){
		cin>>a[i].l>>a[i].r;
		int l=a[i].l,r=a[i].r;
		if(sum2[r]-sum2[l-1]==0){cout<<0<<'\n';continue;}
		int ls=0,rs=min(sum[r]-sum[l-1],sum1[r]-sum1[l-1]),summm=0;
		while(ls<=rs){
			int mid=(ls+rs)/2;
			int ll=l,rr=r,summ=r+1;
			while(ll<=rr){
				int midd=(ll+rr)/2;
				if(sum[midd]-sum[l-1]>=mid) summ=midd,rr=midd-1;
				else ll=midd+1;
			}
			ll=l,rr=r;int summ1=l-1;
			while(ll<=rr){
				int midd=(ll+rr)/2;
				if(sum1[r]-sum1[midd-1]>=mid) summ1=midd,ll=midd+1;
				else rr=midd-1;
			}
			if(summ>summ1||sum2[summ1]-sum2[summ]<=0) rs=mid-1;
			else summm=mid,ls=mid+1;
		}
		cout<<summm*2+1<<'\n';
	}
	return 0;
}
```

---

## 作者：Cute__yhb (赞：2)

## 前言

![](https://cdn.luogu.com.cn/upload/image_hosting/pmi90a42.png)

D 题 WA 了 $11$ 发，没时间做 E 了。但这个 E 真水。

## 思路

根据 C 题，我们可以知道，对于一个斜杠来说，它的答案就是 $1$ 加上它左边的 $1$ 的个数和右边 $2$ 的个数中的小的那个 $\times 2$。

所以，可以用前后缀和记录下前后缀 $1$ 和 $2$ 的个数。

由于是取 $\min$，肯定是左右两边越接近越好。

然后，前缀 $1$ 和后缀 $2$ 的个数肯定是递增的，允许二分。

二分时，二分每个斜杠的位置，求出左右两边 $1$ 和 $2$ 的个数，如果 $1$ 少，那么移动左端点，反之移动右端点。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define F(i,l,r) for(int i=l;i<=r;i++)
#define UF(i,r,l) for(int i=r;i>=l;i--)
#define p_q priority_queue
#define pb push_back
#define mk make_pair
#define pii pair<int,ll> 
#define ve vector
#define endl '\n'
#define fi first
#define se second
#define INF 0x3f3f3f3f
#define lowbit(x) (x&(-x))
int n,q,a1[200005],a2[200005],a[200005],cnt=0;
string s;
int main(){
	cin>>n>>q;
	cin>>s;
	s=" "+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='1') a1[i]=a1[i-1]+1;
		else a1[i]=a1[i-1];
		if(s[i]=='/') a[++cnt]=i;//每个斜杠的位置
	}
	for(int i=n;i;i--){
		if(s[i]=='2') a2[i]=a2[i+1]+1;
		else a2[i]=a2[i+1];
	}//前后缀和
//	for(int i=1;i<=n;i++) cout<<a1[i]<<" ";
//	cout<<endl;
//	for(int i=1;i<=n;i++) cout<<a2[i]<<' ';
//	cout<<endl;
	while(q--){
		int l,r;
		cin>>l>>r;
		int L=lower_bound(a+1,a+1+cnt,l)-a;
		int R=lower_bound(a+1,a+1+cnt,r)-a;
		if(a[R]!=r) R--;
		int ans=0;
		while(L<=R){
			int mid=(L+R)/2;
			int ans1=a1[a[mid]-1]-a1[l-1];
			int ans2=a2[a[mid]+1]-a2[r+1];
			ans=max(ans,1+2*min(ans1,ans2));//记录答案
			if(ans1<ans2){
				L=mid+1;
			}else R=mid-1;
		}
		cout<<ans<<endl;
	}
    return 0;
}
```

---

## 作者：wth2026 (赞：1)

p.s. 本题解的做法约等于 $n^2$。

# 题目思路
首先利用前缀和记录 $1$，后缀和记录 $2$，提前将所有斜杠字符存进一个 vector 里面。

然后对于每一个询问，先二分找到区间内的第一个斜杠，通过前/后缀和可以 $O(1)$ 得到答案。

遍历区间中的每一个斜杠，取最大值即可。

hack:
其实这个做法是 $n^2$，在字符串里全部是斜杠的时候会被卡。但是 AtCoder 的机子快，而且给的时间是 $3$ 秒，并且也跑不满，所以是可以过的。

[AC Code（赛时的，马蜂清奇）](https://atcoder.jp/contests/abc381/submissions/60069475)

---

## 作者：Emplace (赞：1)

## 思路
可以发现对于任意一条杠，要想使对于这条杠最大，是直接将左边的全部 $1$ 与右边全部的 $2$ 取最小 $\times2+1$。
那么我们可以对 $1$ 的个数与 $2$ 的个数求一个前缀和。然后用二分对每一次询问求最左边的杠与最右边的杠，然后再用二分求最大。再来说一下求值的二分的具体方法。可以发现，如果 $1$ 的个数少，肯定尽量往后靠，使得平均。$2$ 少时方法也一样，即往前靠，使得平均。我的写法是把三个二分和在一起，就不多介绍了。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,gang[1145140],sum1[1145140],sum2[1145140],id;
string s;
int main(){
	cin>>n>>m;
	cin>>s;
	s=' '+s;
	for(int i=1;i<=n;i++){
		if(s[i]=='/'){
			id++;
			gang[id]=i;
		}
		sum1[i]=sum1[i-1]+(s[i]=='1');
		sum2[i]=sum2[i-1]+(s[i]=='2');
	}
	while(m--){
		int l,r;
		cin>>l>>r;
		int li=1,ri=id,ans=0;
		while(li<=ri){
			int mid=(li+ri)/2;
			if(gang[mid]<l){
				li=mid+1;
				continue;
			}
			if(gang[mid]>r){
				ri=mid-1;
				continue;
			}
			int p1=sum1[gang[mid]]-sum1[l-1];
			int p2=sum2[r]-sum2[gang[mid]-1];
			if(p1<=p2){
				li=mid+1;
			}
			else{
				ri=mid-1;
			}
			ans=max(ans,2*min(p1,p2)+1);
		} 
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：GY程袁浩 (赞：1)

### 题意

因为没有翻译，提供题目翻译和概括理解。

#### 翻译

我们称一个长度为 $T$ 的字符串 $S$ 是好的，仅当它满足以下条件：

- T 是一个**奇数**。
- $S$ 中的任意 $i(1\le i\le \lfloor\frac{T}{2}\rfloor)$，都满足 $S_{i}=S_{i+\lfloor\frac{T}{2}\rfloor}$。
- $S_{\lfloor\frac{T}{2}\rfloor +1}=$`/`。

给出 $S$，每个询问给定 $l,r$，求 $S$ 的 $l$ 到 $r$ 里好的非连续字串的最大长度。

#### 概括理解

让我们规定 $t1_{l,r},t2_{l,r}$，为 $S$ 的 $l$ 到 $r$ 里字符 `1`、`2` 的数量。

让我们求对于 $S$ 里 $l$ 到 $r$ 的部分里每个 $i(S_{i}= $`/`$)$ 的 $\min(t1_{l,i-1},t2_{i+1,r})$ 的最大值。

### 解法

我们可以记录所有 $i(S_{i}= $`/`$)$ 的位置放在 $pl$ 中，查询时二分则可知道 $l$ 到 $r$ 内所有 $i$。

可是问题是我们不可能对于上文每个 $i$ 都更新一遍答案，所以考虑 $\min(t1_{l,i-1},t2_{i+1,r})$ 其实是一个对于 $i$ 的单峰函数，因为当 $i$ 增大 $t1_{l,i-1}$ 非单调递增，$t2_{i+1,r}$ 非单调递减，然后我们对这两个东西取 $\min$。所以考虑二分最后一个 $t1_{l,i-1}\ge t2_{i+1,r}$ 的在 $pl$ 中的位置 $p$，那么我们最大值取到的 $i$ 必然是 $pl_{p},pl_{p+1}$（前提是 $pl_{p+1}\le r$）。

至于 $t1,t2$ 的计算，很明显我们可以前缀和维护，具体的对于 $i$ 来说，如果 $S_{i}$ 为 `1` 或 `2`，那么我们就在 $t1_{i},t2_{i}$ 上加一，然后对于 $t1,t2$ 做一遍前缀和，即可查询。

代码里用了树状数组来做，属于是多此一举了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int t1[N],t2[N],n,m;
string a;
vector<int> b;
int lowbit(int x) {
	return x&-x;
}
void add(int x,int k,int t[]) {
	for(int i=x;i<=n;i+=lowbit(i)) t[i]+=k;
	return;
}
int qry(int x,int t[]) {
	int sum=0;
	for(int i=x;i;i-=lowbit(i)) sum+=t[i];
	return sum;
}
bool check(int x,int l,int r) {
	return (qry(b[x]-1,t1)-qry(l-1,t1)<=qry(r,t2)-qry(b[x],t2));
}
signed main() {
	cin>>n>>m;
	cin>>a;a=' '+a;
	for(int i=1;i<=n;i++) {
		if(a[i]=='1') add(i,1,t1);
		else if(a[i]=='2') add(i,1,t2);
		else b.push_back(i);
	}
	while(m--) {
		int ll,rr;cin>>ll>>rr;
		int r=upper_bound(b.begin(),b.end(),rr)-b.begin()-1,l=lower_bound(b.begin(),b.end(),ll)-b.begin();
		int ans=0;
		if(r==-1||l==b.size()||l>r) {
			cout<<ans<<endl;
			continue;
		}
		int tmpl=l,tmpr=r;
		while(l<r) {
			int mid=l+r+1>>1;
			if(mid==tmpl||check(mid,ll,rr)) l=mid;
			else r=mid-1;
		}
		ans=max(ans,min(qry(b[l],t1)-qry(ll-1,t1),qry(rr,t2)-qry(b[l],t2)));
		if(l+1<=tmpr) {
			l++;
			ans=max(ans,min(qry(b[l],t1)-qry(ll-1,t1),qry(rr,t2)-qry(b[l],t2)));
		}
		cout<<ans*2+1<<endl;
	}
	return 0;
}
```

---

## 作者：xixisuper (赞：1)

# AT_abc381_e [ABC381E] 11/22 Subsequence 题解

简单题。

## 思路

考虑二分。

我们可以把 11/22  串分成前面 $x$ 个 `1`，中间一个 `/`，后面 $x$ 个 `2` 的形式，然后我们只需要去二分那个 $x$ 的大小即可。

显然如果可以构成一个 11/22 串，那么串中每个元素的位置一定是越靠前越好，所以我们可以把 `1`、`2`、`/` 出现的位置丢进三个 `vector` 当中，这样二分就很容易了。

时间复杂度 $O(q\log n)$，可以通过此题。

[code.](https://atcoder.jp/contests/abc381/submissions/60101758)

---

## 作者：Xuan_qwq (赞：1)

### 题面大意
一个字符串 $T$ 为 11/22 字符串，当且仅当以下条件成立：
- $|T|$ 为奇数，此处 $|T|$ 是字符串 $T$ 的长度。
- 第 $1$ 到第 $\frac{|T|+1}{2}-1$ 个字符均为 `1`。
- 第 $\frac{|T|+1}{2}$ 个字符为 `/`。
- 第 $\frac{|T|+1}{2}+1$ 到第 $|T|$ 个字符均为 `2`。

给定一个长度为 $N$ 的字符串 $S$，保证 $S$ 只由 `1`，`2` 和 `/` 组成。

给出 $Q$ 个询问，每个询问给出两个正整数 $L$，$R$。对于每个询问输出 $S_L$ 至 $S_R$ 这一子串 $T$ 的最长子序列大小，且该子序列为 11/22 字符串。

### 思路

考虑对于每个询问二分答案。

由于直接考虑子序列长度太麻烦，还要判断奇偶性，所以我们考虑子序列的“半长”，即该 11/22 字符串中 `1` 的个数。并且由于考虑包含左端点比较麻烦，所以以下我们所有的左端点均不包含在询问字串与得到的子序列中。

我们发现对于一个给定的左端点 $l$ 和一个指定的半长 $x$，子序列的最小右端点 $r$ 是唯一的。也就是：
- 找到 $l$ 右侧第 $x$ 个 `1` 的位置 $a$。
- 找到 $a$ 右侧最近的 `/` 的位置 $b$。
- 找到 $b$ 右侧第 $x$ 个 `2` 的位置 $r$，得到答案。

我们发现第二步是可以直接对于每个 $a$ 预处理出来的，第一步和第三步都可以在预处理的基础上进行倍增，每次对于给定的 $l$ 和 $x$ 求得 $r$ 所需的时间复杂度是单 $\log$ 的。

于是这道题就做完了。对于每个询问二分答案并输出，总时间复杂度带两个 $\log$，可以通过本题。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
int r1[100005][18];//右侧的第 i 级别 1
int r2[100005][18];//右侧的第 i 级别 2
int rd[100005];//右侧的第一个 / 
int n,q;
char s[100005];
bool check(int l,int r,int x){//检测 l 右侧（不包含 l）符合要求的最短子序列是否在区间中
	int u=l;
	for(int k=17;k>=0;k--){
		if(x&(1<<k))u=r1[u][k];
	}
	u=rd[u];
	for(int k=17;k>=0;k--){
		if(x&(1<<k))u=r2[u][k];
	}
	if(u>r)return 0;
	return 1;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>s[i];
	//这里不能用 cin>>s+1 或者 scanf("%s",s+1)，不然会 CE 或 WA。
	//C++20 貌似不支持这个东西。
	int lst1=0,lst2=0,lstd=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			for(int j=lst1;j<i;j++)r1[j][0]=i;
			lst1=i;
		}
		else if(s[i]=='2'){
			for(int j=lst2;j<i;j++)r2[j][0]=i;
			lst2=i;
		}
		else{
			for(int j=lstd;j<i;j++)rd[j]=i;
			lstd=i;
		}//预处理
	}
	//边界条件
	for(int j=lst1;j<=n;j++)r1[j][0]=n+1;
	for(int j=lst2;j<=n;j++)r2[j][0]=n+1;
	for(int j=lstd;j<=n;j++)rd[j]=n+1;
	for(int i=0;i<18;i++)r1[n+1][i]=n+1,r2[n+1][i]=n+1;
	rd[n+1]=n+1;
	
	for(int j=1;j<18;j++)
		for(int i=0;i<=n;i++){
			r1[i][j]=r1[r1[i][j-1]][j-1];
			r2[i][j]=r2[r2[i][j-1]][j-1];
		}//预处理倍增数组
	while(q--){
		int L,R;cin>>L>>R;
		int ans=-1,l=0,r=(R-L)/2;//二分半长
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(L-1,R,mid))ans=mid,l=mid+1;//由于我们的 check 函数不包含左端点，所以把要包含的左端点想左移一位
			else r=mid-1;
		}//二分答案
		if(ans==-1)cout<<'0'<<endl;//特判无解
		else cout<<ans*2+1<<endl;//由半长还原至原长
	}
	return 0;
} 
```

---

## 作者：huangrenheluogu (赞：0)

把序列拿出来，假设 `/` 的位置是 $p$，则长度是 $[l,p-1]$ 的 `1` 的数量或者 $[p+1,r]$ 的 `2` 的数量的 min，记这个 min 是 $x$，则答案和 $2x+1$ 取 max。

考虑 $p$ 从 $l\to r$ 的过程 $[l,p-1]$ 中 `1` 的数量增加，$[p+1,r]$ 中 `2` 的数量减少，贪心考虑应当是 `1`、`2` 数量几乎一样的时候是最优的，二分即可。

```cpp
#include<bits/stdc++.h>
#define mid (l + r >> 1)
using namespace std;
const int N = 2e5 + 5;
int n, ans, cnt[N][2], q;
int L, R, pos, l, r, pl, pr;
int cnt0, cnt1;
string s;
vector<int> vec;
inline void solve(){
    for(int i = 0; i < n; i++){
        cnt[i + 1][0] = cnt[i][0];
        cnt[i + 1][1] = cnt[i][1];
        if(s[i] != '/') cnt[i + 1][s[i] - '1']++;
    }
    for(int i = 0; i < n; i++){
        if(s[i] == '/') vec.push_back(i + 1);
    }
    while(q--){
        cin >> L >> R;
        ans = 0;
        pl = lower_bound(vec.begin(), vec.end(), L) - vec.begin();
        pr = upper_bound(vec.begin(), vec.end(), R) - vec.begin() - 1;
        l = pl, r = pr;
        while(l <= r){
            cnt0 = cnt[vec[mid]][0] - cnt[L - 1][0];
            cnt1 = cnt[R][1] - cnt[vec[mid] - 1][1];
            ans = max(ans, min(cnt0, cnt1) << 1 | 1);
            if(cnt0 < cnt1) l = mid + 1;
            else r = mid - 1;
        }
        printf("%d\n", ans);
    }
}
int main(){
    // freopen("data.in", "r", stdin);
    // freopen("code.out", "w", stdout);
    cin >> n >> q >> s;
    solve();
    return 0;
}
```

---

## 作者：ran_qwq (赞：0)

不是单 log 写不起，而是双 log 好写好调，更有性价比。

一个 $\texttt{/}$ 的答案是前面 $\texttt{1}$ 个数和后面 $\texttt{2}$ 个数的最小值。

先二分答案 $x$，合法的充要条件是存在一个 $\texttt{/}$，它前面的 $\texttt{1}$ 和后面的 $\texttt{2}$ 个数均 $\ge x$。

满足前面的 $\texttt{1}$ 个数 $\ge x$ 的下标构成一段后缀；后面的 $\texttt{2}$ 个数 $\ge x$ 的下标构成一段前缀。二分出这段后缀的临界点 $p$，$l\sim p$ 合法；二分出这段前缀的临界点 $q$，$q\sim r$ 合法。$p\sim q$ 这段位置的 $\texttt{/}$ 是满足条件的。

求一段区间某个字符的个数可以用前缀和预处理。

```cpp
#include<bits/stdc++.h>
#define il inline
#define ui unsigned int
#define ll long long
#define ull unsigned ll
#define lll __int128
#define db double
#define ldb long double
#define pii pair<int,int>
#define vi vector<int>
#define vpii vector<pii>
#define fir first
#define sec second
#define gc getchar
#define pc putchar
#define mst(a,x) memset(a,x,sizeof a)
#define mcp(a,b) memcpy(a,b,sizeof b)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pct __builtin_popcount
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f,MOD=998244353;
const ll INFll=0x3f3f3f3f3f3f3f3f;
il int rd() {int x=0,f=1; char ch=gc(); while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=gc();} while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc(); return x*f;}
il ll rdll() {ll x=0; int f=1; char ch=gc(); while(ch<'0'||ch>'9') {if(ch=='-') f=-1; ch=gc();} while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=gc(); return x*f;}
il void wr(int x) {if(x==INT_MIN) return printf("-2147483648"),void(); if(x<0) return pc('-'),wr(-x); if(x<10) return pc(x+'0'),void(); wr(x/10),pc(x%10+'0');}
il void wrll(ll x) {if(x==LLONG_MIN) return printf("-9223372036854775808"),void(); if(x<0) return pc('-'),wrll(-x); if(x<10) return pc(x+'0'),void(); wrll(x/10),pc(x%10+'0');}
il void wr(int x,char *s) {wr(x),printf("%s",s);}
il void wrll(ll x,char *s) {wrll(x),printf("%s",s);}
il int vmod(int x) {return x>=MOD?x-MOD:x;}
il int vadd(int x,int y) {return vmod(x+y);}
il int vsub(int x,int y) {return vmod(x-y+MOD);}
il int vmul(int x,int y) {return 1ll*x*y%MOD;}
il int qpow(int x,int y) {int res=1; for(;y;y>>=1,x=vmul(x,x)) if(y&1) res=vmul(res,x); return res;}
il void cadd(int &x,int y) {x=vmod(x+y);}
il void csub(int &x,int y) {x=vmod(x-y+MOD);}
il void cmul(int &x,int y) {x=vmul(x,y);}
il void cmax(int &x,int y) {x<y&&(x=y);}
il void cmaxll(ll &x,ll y) {x<y&&(x=y);}
il void cmin(int &x,int y) {x>y&&(x=y);}
il void cminll(ll &x,ll y) {x>y&&(x=y);}
int n,m,sum[N][3]; string s;
void QwQ() {
	n=rd(),m=rd(),cin>>s,s=" "+s;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<2;j++) sum[i][j]=sum[i-1][j]+(s[i]==j+'1');
		sum[i][2]=sum[i-1][2]+(s[i]=='/');
	}
	for(int l,r,rs;m--;) {
		l=rd(),r=rd(),rs=0;
		auto chk=[&](int x) {
			int p=n+1,q=0;
			for(int L=l,R=r,md;L<=R;) sum[md=L+R>>1][0]-sum[l-1][0]>=x?R=(p=md)-1:L=md+1;
			for(int L=l,R=r,md;L<=R;) sum[r][1]-sum[md=L+R>>1][1]>=x?L=(q=md)+1:R=md-1;
			return p<=q&&sum[q][2]>sum[p-1][2];
		};
		for(int L=0,R=n,md;L<=R;) chk(md=L+R>>1)?(rs=md*2+1,L=md+1):R=md-1;
		wr(rs,"\n");
	}
}
signed main() {
//	freopen("in.in","r",stdin),freopen("out.out","w",stdout);
	int T=1; while(T--) QwQ();
}
```

---

## 作者：zhouruoheng (赞：0)

首先处理 `1`，`2`，`/` 的前缀数量，并记录所有 `/` 的位置，用 $p$ 记录。对于 $l$ 和 $r$，找到位于 $[l,r]$ 的所有 `/` 的位置。$l \le p_{L} \le p_{R} \le r$。对于所有 $i \in [L,R]$，设 $id=p_i$，计算 $[l,p_i-1]$ 中 `1` 的数量 $c1$，$[p_i+1,r]$ 中 $2$ 的数量 $c2$，通过前缀数组记录。显然贡献就是 $\min(c1,c2) \times 2 + 1$。但是直接枚举 $[L,R]$ 的话可能会超时，然而实际上这样就能过了 qwq。

记录：[https://atcoder.jp/contests/abc381/submissions/60088312](https://atcoder.jp/contests/abc381/submissions/60088312)

update：更新了两组 hack 数据，把暴力的卡掉了。

考虑优化，$i \in [L,R]$，$i$ 逐渐增大时，$c1$ 单调不减，$c2$ 单调不增。而答案是取决于 $c1$ 和 $c2$ 的最小值。可以用二分解决。

* 当 $c1=c2$ 时，说明答案最大，直接结束。
* 当 $c1<c2$ 时，说明 $i$ 增加时答案可能更大，$L=mid+1$。
* 当 $c1>c2$ 时，说明 $i$ 减小时才回使答案可能更大，$R=mid-1$。

对于每个 $mid$ 计算答案。

``` cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <map>

using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,q;
string s;
int a[N],b[N],c[N];
int p[N],tot;
void solve()
{
    cin>>n>>q;
    cin>>s;
    s="0"+s;
    for(int i=1;i<=n;i++) 
    {
        if(s[i]=='1') a[i]=1;
        else if(s[i]=='2') b[i]=1;
        else 
        {
            c[i]=1;
            p[++tot]=i;
        }
        a[i]+=a[i-1];
        b[i]+=b[i-1];
        c[i]+=c[i-1];
    }
    while(q--)
    {
        int l,r;
        cin>>l>>r;
        int L=lower_bound(p+1,p+tot+1,l)-p;
        int R=upper_bound(p+1,p+tot+1,r)-p-1;
        int ans=0;
        int mid,c1,c2,id;
        while(L<=R)
        {
            mid=L+R>>1;
            id=p[mid];
            c1=a[id-1]-a[l-1];
            c2=b[r]-b[id];
            ans=max(ans,2*min(c1,c2)+1);
            if(c1<c2) L=mid+1;
            else if(c1>c2) R=mid-1;
            else break;
        }
        cout<<ans<<'\n';
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif 
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}

```

---

## 作者：Redamancy_Lydic (赞：0)

首先能够想到枚举所有的 `/`，对于每个 `/` 计算以它为中间字符时能够产生的最大答案。对于当前询问的区间 $(l,r)$，设 $pos$ 表示当前这个 `/` 的位置。如果令 $s1$ 表示区间 $[l,pos]$ 里 `1` 的数量，$s2$ 表示区间 $[pos,r]$ 里 `2` 的数量，那么此时的答案显然就是 $\min(s1,s2)+1$。其中 $s1$ 和 $s2$ 可以用前缀和维护。

但是直接枚举肯定是不行的。我们不妨感性理解一下，作为断点字符的 `/` 一定要尽可能靠近中间，于是不难想到二分。

具体的，我们预处理所有 `/` 的位置，每次先二分找到所有在当前询问范围内的 `/` 位置区间，设这个区间为 $[L,R]$。然后在这个集合内二分找到最优的 `/` 的位置。

在 $check$ 的时候，我们对于当前的 $mid$，找到区间 $[L,mid]$ 中 `1` 的数量 $sum1$，区间 $[mid,R]$ 中 `2` 的数量 $sum2$，那么如果 $sum1\le sum2$，就收缩左端点，否则收缩右端点。

二分的收缩，边界等细节其实不用过多考虑。对于我来说，最后可以把最优位置所在的区间收缩到一个大概不超过 $10$ 的范围，在这个范围里全部重新计算贡献，就可以不用考虑边界问题，足以通过本题。

[提交记录](https://atcoder.jp/contests/abc381/submissions/60070696)

---

## 作者：liuziqin (赞：0)

## 思路

核心思想：倍增。

显然，如果 $[l,r]$ 中有 `/` 答案一定不为 0。

对每一个 `/`，设它的位置为 $p$，那么它的贡献为 
$$
\min(\sum_{i=l}^{p-1}(S_i=1),\sum_{i=p+1}^{r}(S_i=2))*2+1
$$
观察式子可以看书出，左边 `1` 的数量随着 $p$ 的增大而增大，右边 `2` 的数量随着 $p$ 的增大而减小，由于是取最小值，因此当 `2` 的数量和 `1` 的数量尽量接近时最优，因此考虑二分 $p$。

## Code
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int cnt1[N],cnt2[N],dl[N],tot,n,q;
char s[N];
int check(int l,int r,int ql,int qr){
	int ls=l,rs=r,ans=0;
	while(ls<=rs){
		int mid=(ls+rs)>>1;
		int sum1=cnt1[dl[mid]]-cnt1[ql-1];
		int sum2=cnt2[qr]-cnt2[dl[mid]-1];
		ans=max(ans,min(sum1,sum2)*2+1);
		if(sum1<=sum2)ls=mid+1;
		else rs=mid-1;
	}//二分
	return ans;
}
void sol(int l,int r){
	int ql=lower_bound(dl+1,dl+tot+1,l)-dl;
	if(ql>tot||dl[ql]>r){
		cout<<"0\n";//没有/答案自然为0
		return ;
	}
	int qr=upper_bound(dl+1,dl+tot+1,r)-dl-1;
	cout<<check(ql,qr,l,r)<<"\n";
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		cnt1[i]=cnt1[i-1];
		cnt2[i]=cnt2[i-1];
		if(s[i]=='/')dl[++tot]=i;
		if(s[i]=='1')cnt1[i]++;
		if(s[i]=='2')cnt2[i]++;
	}//前缀和快速求出1的数量和2的数量
	while(q--){
		int l,r;
		cin>>l>>r;
		sol(l,r);
	}
}
```

---

## 作者：Liyunze123 (赞：0)

# 一个很明显的性质
对于每个询问，答案必然是满足从起点开始数 $k$ 个 $1$，接着数下一个 `/`，接着再数 $k$ 个 $2$，第 $k$ 个 $2$ 不超过 $r$ 的最大 $2i+1$。
# 求答案
二分求即可。
## 如何维护从某点开始数的第 $k$ 个 $1$ 或 $2$
可以倍增。

设 $f_{i,j}$ 为从 $i$ 点开始数，不包括 $i$ 的第 $2^j$ 个 $1$，$g_{i,j}$ 同理，但是是第 $2^j$ 个 $2$。没有 $2^j$ 个时，等于 $n+1$ 即可。$h_i$ 为包括 $i$ 的下一个 `/` 的位置。从后到前扫，求出 $f_{i,0},g_{i,0},h_i$。然后，对于大于等于 $1$ 的 $j$，仍然从后到前扫，$f_{i,j}$ 是 $f_{f_{i,j-1},j-1}$，$g_{i,j}$ 是 $g_{g_{i,j-1},j-1}$。

## 二分时如何判断是否可行
根据性质和 $f,g,h$ 的定义，从 $l-1$ 开始倍增 $mid$ 个 $1$，设数到 $k$，接着数一个`/`，即 $h_k$，之后再倍增 $mid$ 个 $2$，如果最后的 $k$ 是小于等于 $r$ 的，那么这个 $mid$ 是可行的。

时间复杂度是 $O(n \log(n) \log(n))$ 的。

[代码链接](https://atcoder.jp/contests/abc381/submissions/60105751)

---

## 作者：kkxacj (赞：0)

#### 思路

容易发现，随着 $i$ 增加，左边 $1$ 的个数是单调递增的，而右边 $2$ 是单调递减的，直接二分，先将字符为 `/` 的取出来，考虑 $l,r$ 里的 `/` 是哪一段，然后二分时求值就行了。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],to,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++to]=48+x%10;while(to) pc(stk[to--]);}
}
using namespace IO;
const int N = 2e5+10; 
int n,a[N],b[N],ans,q,sum[N],sum1[N],cnt1,c[N],d[N],st[N],x,y,o,o1,L,R,l,r,sum2,mid; 
string s;
signed main()
{
	cin >> n >> q >> s; s = ' '+s;
	for(int i = 1;i <= n;i++)
	{
		if(s[i] == '1') a[i] = a[i-1]+1;
		else a[i] = 0;
	}
	for(int i = 1;i <= n;i++) sum[i] = sum[i-1]+(s[i] == '1');
	for(int i = n;i >= 1;i--) sum1[i] = sum1[i+1]+(s[i] == '2');
	for(int i = n;i >= 1;i--)
	{
		if(s[i] == '2') b[i] = b[i+1]+1;
		else b[i] = 0;
	}
	for(int i = 1;i <= n;i++) if(s[i] == '/') st[++cnt1] = i;
	for(int i = 1;i <= n;i++)
		if(s[i] == '/') c[i] = i;
		else c[i] = c[i-1];
	d[n+1] = n+1;
	for(int i = n;i >= 1;i--)
		if(s[i] == '/') d[i] = i;
		else d[i] = d[i+1];
	while(q--)
	{
		read(L),read(R); 
		x = d[L],y = c[R];
		if(R < x || y < L)
		{
			print(0),pc('\n');
			continue;
		}
		ans = 0;
		o = lower_bound(st+1,st+1+cnt1,x)-st;
		o1 = lower_bound(st+1,st+1+cnt1,y)-st;
		l = o,r = o1; ans = 0;
		while(l <= r)
		{
			mid = ((l+r)>>1);
			ans = max(ans,min(sum[st[mid]]-sum[L-1],sum1[st[mid]]-sum1[R+1])*2+1);
			if(sum[st[mid]]-sum[L-1] < sum1[st[mid]]-sum1[R+1]) l = mid+1;
			else r = mid-1;
		}
		print(ans),pc('\n');
	}
	flush();
	return 0;
}




```

---

## 作者：Colinxu2020 (赞：0)

定义一个 11/22 序列的中心点为这个序列中 `/` 所在的下标，容易发现无解当且仅当 $S_{l \cdots r}$ 之间不存在 `/` 直接特判即可。考虑枚举中心点 $p$，若 $s_{l \cdots p}$ 中有 $a$ 个 $1$，$s_{p \cdots r}$ 中共有 $b$ 个 $2$，则以 $p$ 为中心的极长的 11/22 序列长度为 $\min(a,b) \times 2 + 1$。考虑运用前缀和优化，令 $one_i$ 为 $s_{1 \cdots i}$ 中 $1$ 的数量，$two_i$ 为 $s_{1 \cdots i}$ 中 $2$ 的数量，则长度可化为 $\min(one_p-one_{l-1}, two_r-two_p) \times 2 + 1$。

朴素实现会超时，但我们可以观察到大部分的转移点 $p$ 都是没有意义的。又因为 $one_{i} \geq one_{i-1},two_i \leq two_{i+1}$，可以发现 $one_p-one_{l-1}$ 随 $p$ 单调增，$two_r-two_p$ 随 $p$ 单调减。$\min$ 看起来很不优雅，不便于优化，考虑拆开，令 $p$ 为 $\max p$ 使得 $one_p-one_{l-1}\lt two_{r}-two_p$ 且 $p$ 可作为中心点，基于前面的结论有 $\forall l \leq i \leq p$ 有 $one_p-one_{l-1} \lt two_r-two_p$，反之亦然，而 $\forall j \lt i,one_i-one_{l-1} \geq one_j-one_j$，因此用 $p$ 转移一定较 $j$ 更优，只需要考虑 $p$ 即可；再考虑 $one_p-one_{l-1} \geq two_r-two_p$ 的情况，有 $\forall j \gt i,two_r-two_j \leq two_r-two_i$，因此用 $p$ 之后的第一个中心点转移即可。

考虑优化找 $p$，可以发现在只考虑中心点的意义下 $p$ 的条件是有单调性的，不妨二分找到最大的 $p$ 即可，若不存在这样的 $p$ 则应用 $l$ 转移。注意边界情况，若 $p$ 之后第一个中心点在 $r$ 之后则不能用则这个点转移。

时间复杂度为 $\theta(N \log N)$，空间复杂度为 $\theta(N)$。

参考代码：

```cpp
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn=1e5+10;
int n,q,nxt[maxn],one[maxn],two[maxn]; string s;
vector<int> splits;

int find(int x, int y){
    int l=lower_bound(splits.begin(), splits.end(), x)-splits.begin();
    int r=upper_bound(splits.begin(), splits.end(), y)-splits.begin()-1;
    if(one[splits[l]]-one[x-1]>=two[y]-two[splits[l]])return splits[l];
    while(l<=r){
        int mid=(l+r)/2;
        if(one[splits[mid]]-one[x-1]<two[y]-two[splits[mid]])l=mid+1;
        else r=mid-1;
    }
    return splits[l-1];
}
int solve(int x, int l, int r){
    return min(one[x]-one[l-1], two[r]-two[x]);
}
int main(){
    cin>>n>>q>>s; s=" "+s;
    for(int i=n;i>=0;i--){
        if(i==n||s[i+1]=='/')nxt[i]=i+1;
        else nxt[i]=nxt[i+1];
    }
    for(int i=1;i<=n;i++)one[i]=one[i-1]+(s[i]=='1'),two[i]=two[i-1]+(s[i]=='2');
    for(int i=1;i<=n;i++)if(s[i]=='/')splits.push_back(i);
    while(q--){
        int l,r; cin>>l>>r;
        if(nxt[l-1]>r){
            cout<<"0\n";
            continue;
        }
        int pos=find(l,r),ans=solve(pos, l, r);
        //cout<<pos<<endl;
        if(nxt[pos]<=r)ans=max(ans, solve(nxt[pos], l, r));
        cout<<ans*2+1<<endl;
    }
}
```

---

## 作者：Shunpower (赞：0)

当你开始整数三分，注定会拥有一个失败的人生。

-------------

考虑我们容易写出一个暴力：枚举区间中的每一个 `/`，计算在区间中它左侧的 $1$ 的数量 $lef$，区间中它右侧的 $2$ 的数量 $rig$，那么它对答案的贡献就是 $2\min(lef,rig)+1$。我们只需求它对所有区间中的 `/` 的 $\max$。

然后我们立即想歪了！我们抛弃 $\min$ 的 $\max$ 启动二分的想法，发现 $lef$ 是从左向右单调递增的，$rig$ 是从右向左单调递减的，那么它们的 $\min$ 就是凸的。

然而直接做整数三分是没有正确性的。注意到时限三秒，我们直接开始爬山！

我们把所有 `/` 的位置存下来，只考虑区间内的 `/`，这样我们就确定了爬山的边界。然后直接架爬山板子，我们在区间内随机挪移小于等于温度的长度，如果答案更好则挪移，挪移不满一步时（即温度小于 $1$ 时）退出。

初始设置温度 $T$ 为区间内 `/` 的个数，$eps=1$，降温系数 $t=0.992$，最后用答案的左右 $500$ 个 `/` 进行调整，即可通过。

听说三分调整也过了。

---------------

```cpp
int n,q;
char c[N];
vector <int> g;
int pre1[N],suf2[N];
int le,re;
il int calc(int idx){
    int lef=pre1[idx]-pre1[le-1];
    int rig=suf2[idx]-suf2[re+1];
    return min(lef,rig)*2+1;
}
il double rd(){
    return (double)rand()/RAND_MAX;
}
int main(){
#ifdef Shun
    freopen(".in","r",stdin);
    freopen(".out","w",stdout);
#endif 
    srand(time(0));
    ios::sync_with_stdio(false);
    cin>>n>>q;
    fr1(i,1,n) cin>>c[i];
    fr1(i,1,n) pre1[i]=pre1[i-1]+(c[i]=='1');
    fr2(i,n,1) suf2[i]=suf2[i+1]+(c[i]=='2');
    fr1(i,1,n) if(c[i]=='/') g.pb(i);
    while(q--){
        cin>>le>>re;
        if(g.empty()){
            cout<<"0\n";
            continue;
        }
        int l=lower_bound(g.begin(),g.end(),le)-g.begin();
        int r=upper_bound(g.begin(),g.end(),re)-g.begin();
        r--;
        if(r<l){
            cout<<"0\n";
            continue;
        }
        int ans=0;
        double T=r-l+1,eps=1,t=0.992;
        int x=l+r>>1;
        while(T>=eps){
            int del=T*(rd()*2-1);
            int nx=x+del;
            nx=min(nx,r);
            nx=max(nx,l);
            ans=max(ans,calc(g[x]));
            double delta=calc(g[nx])-calc(g[x]);
            if(delta>0) x=nx;
            T*=t;
        }
        fr1(i,max(l,x-500),min(x+500,r)) ans=max(ans,calc(g[i]));
        cout<<ans<<'\n';
    }
    
    ET;
}
//ALL FOR Zhang Junhao.
```

![](https://cdn.luogu.com.cn/upload/image_hosting/litlgg7x.png)

三发三分，三发爬山，最后还下了三分。

---

## 作者：无名之雾 (赞：0)

赛时气血上涌做 $15$ min，个人感觉难度不大。

## 思路

首先根据 [C](https://www.luogu.com.cn/article/wqhgis1f) 题的启发。

我们不难想到本题也应该从 `/` 入手开始分析。

考虑一个 `11/22` 序列的长度其实就是 `/` 的左右两端连续的 $1$ 与 $2$ 中取较小值。

所以不难想到先前缀和记录 $1$ 和 $2$ 的前缀与后缀长度。

不难发现这个东西是有单调性的可以二分。

具体的：

- 我们设 $S_1$ 是`/`左边 $1$ 的个数， $S_2$ 是右边 $2$ 的个数。
- 如果是 $S_1 >S_2$ ，那么应该二分它左边的 `/`。
- 反之则应二分右边的 `/`。


时间复杂度 $O(Q \log n)$。

[submission](https://atcoder.jp/contests/abc381/submissions/60068526)

---

## 作者：Ericzc (赞：0)

## 题目分析

题目要求在给定的字符串 $S$ 中找到满足 `11/22` 规则的最大长度子序列。每个查询需要指定一个子字符串，要求我们从中找到 `11/22` 规则的最大子序列长度。

满足是 `11/22` 规则:

* 长度必须是奇数。

* 前一半字符（不包括中间字符）全是 `1`，中间字符是 `/`，后一半字符（不包括中间字符）全是 `2`。

## 核心思路

我们需要预处理字符串来加速每个查询的处理：

使用前缀和数组分别统计每个位置之前的 `1` 和 `2` 的个数。

使用一个数组记录所有 `/` 的位置。

对每个查询，通过二分查找快速定位查询子串中可能的 `/` 位置，然后根据左右 `1` 和 `2` 的数量确定最大符合规则的子序列长度。

## Code：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n, q, k;
int qzh1[100005], qzh2[100005], did[100005];
char a[100005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == '/') did[++k] = i;
        if (a[i] == '1') qzh1[i] = qzh1[i - 1] + 1;
        else qzh1[i] = qzh1[i - 1];
        if (a[i] == '2') qzh2[i] = qzh2[i - 1] + 1;
        else qzh2[i] = qzh2[i - 1];
    }
    while (q--) {
        int L, R;
        cin >> L >> R;
        int l = 1, r = k, ma = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int x = qzh1[did[mid] - 1] - qzh1[L - 1], y = qzh2[R] - qzh2[did[mid]];
            if (did[mid] < L) l = mid + 1; 
            else if (did[mid] > R) r = mid - 1;
            else if (x <= y) {
                ma = max(ma, min(x, y) * 2 + 1);
                l = mid + 1;
            } else {
                ma = max(ma, min(x, y) * 2 + 1);
                r = mid - 1;
            }
        }
        cout << ma << endl;
    }
    return 0;
}
```

## 复杂度分析

预处理部分（前缀和及记录 / 位置）：时间复杂度 $O(N)$。

查询部分：二分查找每个查询的 / 位置，时间复杂度 $O(\log k)$，总体为 $O(Q \log k)$。

综合复杂度：$O(N + Q \log k)$。

## 总结

该算法通过预处理字符串中的 `1`、`2`、`/` 数量和位置，使用二分查找有效处理每个查询，使得整体算法在大数据量情况下依然高效运行。

---

## 作者：Luxe877 (赞：0)

赛时胡搞结果过了，意外之喜。

## 题意
**11/22 串**（以下定义其为 $T$ 串）的定义如下：

- $|T|$ 为奇数，即 $T$ 的长度为奇数。
- 对于任意的 $i \in [1,\frac{|T|+1}{2}-1]$，满足 $T_i$ 都为 `1`。
- $i=\frac{|T|+1}{2}$ 时，$T_i$ 为 `/`。
- 对于任意的 $i \in [\frac{|T|+1}{2}+1,|T|]$，满足 $T_i$ 都为 `2`。

现在给定一个长度为 $N$ 且只包含 `1`、`2`、`/` 的字符串 $S$，给出 $Q$ 次询问。每次询问输入两个数 $L,R$，需要求出 $[L,R]$ 之间最长的 11/22 串的长度。

## 正解做法
二分和前缀和。

用前缀和 $f_{i,1}$ 和 $f_{i,2}$ 记录第 $i$ 个位置前有多少个 `1` 和 `2`，这样可以减少计算长度的统计次数。然后，对于所有的 `/` 的位置，也用一个数组存起来。

每次询问，先二分求出 $[L,R]$ 区间中最左边的 `/` 和 最右边的 `/`，记为 $l$ 与 $r$，如果二分后发现 $l>r$，则直接输出 `0`。因为当 $l>r$ 时，表明区间 $[L,R]$ 中没有 `/` 字符，显然不存在 11/22 串，故长度为 $0$。

然后，不难发现每个 `/` 左右的最长 11/22 串长度为 $\min(f_{i-1,1}-f_{l-1,1},f_{r,2}-f_{i,2}) \times 2+1$，$i$ 表示 `/` 的位置。因此两个二分分别求出 $[L,R]$ 中 `1` 的个数和 `2` 的个数的最大最小值，然后就可以得出答案了。

赛后 AC 记录： https://atcoder.jp/contests/abc381/submissions/60104521

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
char s[100002];
int qzh[100002][3];
vector<int> rec;
int efl(int l,int r,int pos)
{
//	cout<<"L"<<" "<<l<<" "<<r<<" "<<pos<<"\n";
	if(l>=r)
	{
		return l;
	}
	int mid=(l+r)/2;
	if(rec[mid]>=pos)
	{
		return efl(l,mid,pos);
	}else{
		return efl(mid+1,r,pos);
	}
}
int efr(int l,int r,int pos)
{
//	cout<<"R"<<" "<<l<<" "<<r<<" "<<pos<<"\n";
	if(l>=r)
	{
		return l;
	}
	int mid=(l+r)/2;
	if(rec[mid]<=pos)
	{
		return efr(mid+1,r,pos);
	}else{
		return efr(l,mid,pos);
	}
}
bool ch1(int l,int r,int pos)
{
	return (qzh[r][2]-qzh[pos][2]<=qzh[pos-1][1]-qzh[l-1][1]);
}
bool ch2(int l,int r,int pos)
{
	return (qzh[r][2]-qzh[pos][2]>=qzh[pos-1][1]-qzh[l-1][1]);
}
int main()
{
	cin>>n>>q;
	rec.push_back(0);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		qzh[i][1]=qzh[i-1][1]+(s[i]=='1');
		qzh[i][2]=qzh[i-1][2]+(s[i]=='2');
		if(s[i]=='/')
		{
			rec.push_back(i);
		}
	}
	int l,r,L,R,m=rec.size()-1;
	while(q--)
	{
		scanf("%d %d",&l,&r);
		L=efl(1,m,l);
		if(rec[L]<l)
		{
			L++;
		}
		R=efr(1,m,r);
		if(rec[R]>r)
		{
			R--;
		}
//		cout<<L<<" "<<R<<"\n";
		if(L>R)
		{
			printf("0\n");
			continue;
		}
		int ll=L,rr=R,okl=L,okr=R,ans=1,mid;
		while(ll<=rr)
		{
			mid=(ll+rr)/2;
			if(ch1(l,r,rec[mid]))
			{
				rr=mid-1;
				okr=mid;
			}else{
				ll=mid+1;
			}
		}
		ans=max(ans,min(qzh[r][2]-qzh[rec[okr]][2],qzh[rec[okr]-1][1]-qzh[l-1][1])*2+1);
		ll=L,rr=R,okl=L;
		while(ll<=rr)
		{
			mid=(ll+rr)/2;
			if(ch2(l,r,rec[mid]))
			{
				ll=mid+1;
				okl=mid;
			}else{
				rr=mid-1;
			}
		}
		ans=max(ans,min(qzh[r][2]-qzh[rec[okl]][2],qzh[rec[okl]-1][1]-qzh[l-1][1])*2+1);
		printf("%d\n",ans);
	}
	return 0;
}
```

## 暴力做法
我的赛时做法，二分 $[L,R]$ 区间中最左边的 `/` 和最右边的 `/` 位置不变，但是直接枚举 $[l,r]$ 的所有 `/`，暴力算出答案并输出，2600ms 极限通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
char s[100002];
int qzh[100002][3];
vector<int> rec;
int efl(int l,int r,int pos)
{
//	cout<<"L"<<" "<<l<<" "<<r<<" "<<pos<<"\n";
	if(l>=r)
	{
		return l;
	}
	int mid=(l+r)/2;
	if(rec[mid]>=pos)
	{
		return efl(l,mid,pos);
	}else{
		return efl(mid+1,r,pos);
	}
}
int efr(int l,int r,int pos)
{
//	cout<<"R"<<" "<<l<<" "<<r<<" "<<pos<<"\n";
	if(l>=r)
	{
		return l;
	}
	int mid=(l+r)/2;
	if(rec[mid]<=pos)
	{
		return efr(mid+1,r,pos);
	}else{
		return efr(l,mid,pos);
	}
}
int main()
{
	cin>>n>>q;
	rec.push_back(0);
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		qzh[i][1]=qzh[i-1][1]+(s[i]=='1');
		qzh[i][2]=qzh[i-1][2]+(s[i]=='2');
		if(s[i]=='/')
		{
			rec.push_back(i);
		}
	}
	int l,r,L,R,m=rec.size()-1;
	while(q--)
	{
		scanf("%d %d",&l,&r);
		L=efl(1,m,l);
		if(rec[L]<l)
		{
			L++;
		}
		R=efr(1,m,r);
		if(rec[R]>r)
		{
			R--;
		}
//		cout<<L<<" "<<R<<"\n";
		int ans=0;
		for(int i=L;i<=R;i++)
		{
			ans=max(ans,1+2*min(qzh[rec[i]][1]-qzh[l-1][1],qzh[r][2]-qzh[rec[i]-1][2]));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：csgpx (赞：0)

洛谷题目链接：[AT_abc381_e](https://www.luogu.com.cn/problem/AT_abc381_e)。

## 思路

主要用到了前缀和以及二分的知识（可能还带点贪心）。

这道题的切入点在 $\texttt{/}$ 上。对于 $\texttt{1}$ 和 $\texttt{2}$，出现位置和次数不定，只有 $\texttt{/}$ 是只能取一次的，所以我们可以找到区间中的 $\texttt{/}$，并看左右的 $\texttt{1}$ 和 $\texttt{2}$ 的个数，取最小值 $\times 2+1$，因为左右数字个数需要一样，同时加上中间的 $\texttt{/}$。

可以预处理出 $\texttt{1}$ 和 $\texttt{2}$ 的前缀和，那么对于区间的个数就很容易得出，用右端点的前缀和减去左端点减一的前缀和即可。

问题只剩如何快速找到 $\texttt{/}$ 的区间位置和最优的情况了。这里可以采用二分，记录每个 $\texttt{/}$ 所在的位置，每次询问时设 $lt$ 和 $rt$ 为二分左右端点，$lt$ 为 $1$，$rt$ 为 $\texttt{/}$ 的个数，当 $mid$ 不在询问区间时直接缩小二分范围，反之按上述方法取答案最大值，这时的二分区间需要特殊讨论：当 $\texttt{1}$ 的个数小于 $\texttt{2}$ 的个数时，可以发现只有 $\texttt{/}$ 的位置向右才有可能取到更大的答案，相反，当 $\texttt{1}$ 的个数大于 $\texttt{2}$ 的个数时，只有当 $\texttt{/}$ 的位置向左时才有可能取到更大的答案，因为答案取决于较小值，只有较小值更大时答案才会变大。本题思路大概就这样，记得多测清空。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,q,f[100010],e[100010],g[100010],d,ans;
char s[100010];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>s[i];
		f[i]=f[i-1];
		e[i]=e[i-1];
		if(s[i]=='1') f[i]++;
		else if(s[i]=='2') e[i]++;
		else g[++d]=i;//记录'/'的位置
	}
	while(q--){
		int l,r;
		cin>>l>>r;
		ans=0;
		int lt=1,rt=d;
		while(lt<=rt){//二分
			int mid=(lt+rt)/2;
			if(g[mid]<l){//不在区间内，位置小于区间左端点
				lt=mid+1;//缩小二分左端点
			}
			else if(g[mid]>r){//不在区间内，位置大于区间右端点
				rt=mid-1;//缩小二分右端点
			}
			else{
				ans=max(ans,min(e[r]-e[g[mid]],f[g[mid]-1]-f[l-1])*2+1);//计算答案取最大值
				if(e[r]-e[g[mid]]>f[g[mid]-1]-f[l-1]){
					lt=mid+1;
				}
				else rt=mid-1;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：0)

我们设 $sum1_{l,r}$ 表示在 $s_{l,r}$ 中 $1$ 出现的次数，$sum2_{l,r}$ 表示 $2$ 出现个次数。

接着会想到一个做法：以每一个 `/` 为中心，向两边选择，设 `/` 的位置为 $x$，询问的端点为 $l,r$，则答案就是 $\min(sum1_{l,x-1},sum2_{x+1,r})$，也就是 $1$ 和 $2$ 个数的最小值。

但是枚举区间每一个 `/` 是很浪费时间的，这里可以利用贪心思想，我们要尽可能让 $1$ 和 $2$ 的个数接近。若当前 $1$ 的个数小于 $2$ 的个数，那么 $x$ 肯定是需要增加，这样 $1$ 的个数就不增，$2$ 的个数不降，就可以让他们尽可能接近。那么最优情况就是 $1$ 的个数大于 $2$ 的个数，且最接近，和 $2$ 的个数大于 $1$ 的个数，且最接近。这两种情况的 $x$ 可以通过二分求出，于是预处理出每个 `/` 的位置和 $sum1,sum2$，然后就做完了。

```cpp
#include<bits/stdc++.h>
#define N 100005
#pragma GCC optimize("O3")
using namespace std;
int n,q,len,a[N],cnt[3][N];
char c[N];
int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++)//预处理sum1,sum2和'/'出现的位置
	{
		cin>>c[i];
		if(c[i]=='/') cnt[0][i]++;
		if(c[i]=='1') cnt[1][i]++;
		if(c[i]=='2') cnt[2][i]++;
		cnt[0][i]+=cnt[0][i-1];
		cnt[1][i]+=cnt[1][i-1];
		cnt[2][i]+=cnt[2][i-1];
		if(c[i]=='/') a[++len]=i;
	}
	while(q--)
	{
		int l,r,x,y,ans=0;
		cin>>l>>r;
		x=lower_bound(a+1,a+len+1,l)-a;
		y=upper_bound(a+1,a+len+1,r)-a-1;
  //二分得出'/'位置的最小值和最大值
		if(x>y)//这个区间没有'/'
		{
			cout<<0<<"\n";
			continue;
		}
		int L=x,R=y+1,mid,pos1=-1,pos2=-1;
		while(L<R)
		{
			mid=L+R>>1;
			if(cnt[1][a[mid]-1]-cnt[1][l-1]>=cnt[2][r]-cnt[2][a[mid]]) R=pos1=mid;
			else L=mid+1;
		}
		L=x-1,R=y;
		while(L<R)
		{
			mid=L+R+1>>1;
			if(cnt[1][a[mid]-1]-cnt[1][l-1]<=cnt[2][r]-cnt[2][a[mid]]) L=pos2=mid;
			else R=mid-1;
		}
		if(pos1!=-1) ans=max(ans,(cnt[2][r]-cnt[2][a[pos1]])*2+1);
		if(pos2!=-1) ans=max(ans,(cnt[1][a[pos2]-1]-cnt[1][l-1])*2+1);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Liuhy2996 (赞：0)

## 题意
给定一个长度为 $n$ 的字符串 $s$，有 $q$ 次询问，每次问你在 $\left [ l,r \right ]$ 中的最长 “11/22” 字串（不一定连续）的长度。
## 思路
处理出所有 “/” 的位置，记第 $i$ 个位置为 $p_i$。若已确定选择 $p_i$ 作为答案中的 “/”，设 $\left [ l,p_i-1 \right ]$ 中的 “1” 的数量为 $cnt_1$，$\left [ p_i+1,r \right ]$ 中的 “2” 的数量为 $cnt_2$，则答案为 $\min(cnt_1,cnt_2)\times 2+1$。

考虑二分。若 $cnt_1<cnt_2$，则将 $p_i$ 换成 $p_{i+1}$ 后答案可能更优。二分 $i$ 即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,inf=1e15;
int n,q,ans,t,x,y,s[N][100],p[N]; //s为前缀和数组
char c;
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;++i){
		cin>>c,s[i]['1']=s[i-1]['1'],s[i]['2']=s[i-1]['2'],++s[i][c];
		if(c=='/') p[++t]=i;
	}
	while(q--){
		cin>>x>>y;
		int l=lower_bound(p+1,p+t+1,x)-p,r=upper_bound(p+1,p+t+1,y)-p-1;
		if(l>r) puts("0"); //[l,r] 中没有“/”
		else{
			ans=0;
			while(l<=r){
				int mid=(l+r+1)>>1,cnt1=s[p[mid]-1]['1']-s[x-1]['1'],cnt2=s[y]['2']-s[p[mid]]['2'];
				ans=max(ans,min(cnt1,cnt2));
				if(cnt1>cnt2) r=mid-1;
				else l=mid+1;
			}
			cout<<ans*2+1<<endl;
		}
	}
	return 0;
}
```

---

