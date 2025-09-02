# Sereja and Suffixes

## 题目描述

Sereja has an array $ a $ , consisting of $ n $ integers $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{n} $ . The boy cannot sit and do nothing, he decided to study an array. Sereja took a piece of paper and wrote out $ m $ integers $ l_{1},l_{2},...,l_{m} $ $ (1<=l_{i}<=n) $ . For each number $ l_{i} $ he wants to know how many distinct numbers are staying on the positions $ l_{i} $ , $ l_{i}+1 $ , ..., $ n $ . Formally, he want to find the number of distinct numbers among $ a_{li},a_{li}+1,...,a_{n} $ .?

Sereja wrote out the necessary array elements but the array was so large and the boy was so pressed for time. Help him, find the answer for the described question for each $ l_{i} $ .

## 样例 #1

### 输入

```
10 10
1 2 3 4 1 2 3 4 100000 99999
1
2
3
4
5
6
7
8
9
10
```

### 输出

```
6
6
6
6
6
5
4
3
2
1
```

# 题解

## 作者：Alex_Wei (赞：20)

题意：输入 $n,m$ 和 $n$ 个数 $a_i$，之后是 $m$ 次询问：输入一个数 $l$ ，输出 $a_l,a_{l+1},……a_n$ 之间有多少个不同的数

#### 思路：如果根据题意模拟，时间复杂度高可达到 $O(mn)$，所以需要优化

优化：

- #### 用一个 $map$ $k$（当然数组也可以，因为 $a_i$ 的范围比较小）判断一个值是否出现过

- 开一个数组 $s,s_i$ 记录 $a_i,a_{i+1},……a_n$ 之间不同的数的个数

预处理一下，**从后往前**枚举，对于第 $i$ 个数，如果 

$a_i$ 没有在 $a_{i+1},……a_n$ 中出现，即 $k[a_i]=0$，则 $s_i =s_{i+1}+1$，否则 $s_i=s_{i+1},$ **别忘了把 $k[a_i]$ 标记成 $1$**

对于每次询问 $l$，输出 $s_l$ 即可

- #### 加上优化时间复杂度为 $O(\max(m,n))$

#### 代码：
```
#include<bits/stdc++.h>
using namespace std;
map <int,bool> k;
int n,m,a[100100],s[100100],l;
int main()
{
	cin>>n>>m;
	for(int x=1;x<=n;x++)cin>>a[x];
	for(int x=n;x>0;x--){//从后向前枚举 
		if(!k[a[x]])s[x]=s[x+1]+1;//优化
		else s[x]=s[x+1];
		k[a[x]]=1;
	}
	for(int x=1;x<=m;x++)cin>>l,cout<<s[l]<<endl;
	return 0;
}
```
#### 珍爱账号，远离抄袭

如果有错误请私信我，我会及时改正！

求赞 $qwq$

$\small{\text{Upd 2019.8.17 : 添加Latex，之前的文章有点丑}}$

---

## 作者：Melon_Musk (赞：4)

[CF368B Sereja and Suffixes题面](https://www.luogu.com.cn/problem/CF368B)

[安利一下我的博客](https://www.melonmusk.cn/index.php/2021/02/01/cf368b-sereja-and-suffixes-%e9%a2%98%e8%a7%a3/)

## 题面描述

给出一个长度为 $n$ 的序列 $a$，有 $m$ 个查询,对于每个查询，给出一个数 $l$ ,输出 $[l,n]$ 的区间内不同的数的个数。

## 分析

我们发现题目需要求的答案是从 $l$ 到 $n$ 的，很自然的想到我们从后往前维护一个数组 $sum$ , $sum[i]$ 表示从 $i$ 到 $n$ 区间中不同的数的个数。

①如果当前位置的 $a[i]$ 在 $[i+1,n]$ 中出现过了，那么 $sum[i]=sum[i+1]$ 。

②如果在后面都没有出现此数，那么 $sum[i]=sum[i+1]+1$。

于是，现在我们考虑如何判断在 $[i+1,n]$ 中是否出现过此数，因为 $1<=a[i]<=10 
^5$ ,所以我们可以直接用一个桶来维护。
但是出于某些原因，我的代码中使用了 $map$ ,来储存（简单对不懂 $map$ 的同学们解释一下，我们可以将 $map$ 当成一个下表可以是任意数的数组，是我们编写 $c++$ 程序的有利助手（没学过的同学们可以去其他渠道学习一下））。

[AC记录](https://www.luogu.com.cn/record/45942637)

## 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+7;
ll read() 
{
	ll res=0,f=1;
	char c=getchar();
	while(!isdigit(c) && c!='-') c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(isdigit(c)) res=(res<<1)+(res<<3)+c-48,c=getchar();
	return res*f;
}
int n,m;
int a[maxn],sum[maxn];
map<int,int> mp;
int main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=n;i;i--) 
		if(!mp[a[i]]) 
		{
			mp[a[i]]=1;
			sum[i]=sum[i+1]+1;
		}
		else 
			sum[i]=sum[i+1];
	for(int i=1;i<=m;i++)
	{
		int l=read();
		printf("%d\n",sum[l]);
	}
	return 0;
}
```

有问题欢迎在评论区提出，卑微求赞awa


---

## 作者：Eason_AC (赞：2)

## Content
有 $n$ 个数 $a_1,a_2,a_3,...,a_n$。有 $m$ 次询问，每次给定一个数 $l$，查询在区间 $[l,n]$ 内不同的数一共有多少个。

**数据范围：$1\leqslant n,m\leqslant 10^5,1\leqslant a_i\leqslant 10^5$。**
## Solution
鉴于 $\mathcal{O}(nm)$ 的暴力模拟显然不能够通过此题，我们需要一种更高效的算法，以卡过这样的数据。

那么，我们自然而然就会想到 $\texttt{dp}$ 的算法了。

既然是要求 $[l,n]$ 里面的不同的数的个数，那么我们不妨就设 $dp_i$ 为 $[i,n]$ 里面不同的数的个数。那么，我们显然可以先推出这样一个式子：

$$dp_n=1$$

很显然，$[n,n]$ 里面不同的数只有 $a_n$ 一个，对吧？那么我们就从这个临界点开始从右往左进行 $\texttt{dp}$。

为了统计这个数字是否出现，我们需要开一个 $vis$ 数组（这里 $a_i$ 的值不算太大，如果很大的时候就需要用到 $\texttt{map}$ 来实现了）。那么，这个题目的转化方程就很容易想到了：**如果在 $i$ 之后出现了一个数 $j$，使得 $a_j=a_i$，那么 $dp_i$ 就保持和 $dp_{i+1}$ 不变，否则，又出现了一个不同的数，那么 $dp_i$ 相比较于 $dp_{i+1}$ 就会多 $1$。**

这样，转移方程就列完了：

$$dp_i=\begin{cases}1&i=n\\dp_{i+1}+1&vis_{a_i}=0,1\leqslant i<n\\dp_{i+1}&vis_{a_i}=1,1\leqslant i<n\end{cases}$$

我们拿样例 $1$ 做个例子：

```
1 2 3 4 1 2 3 4 100000 99999
```

显然，$dp_{10}=1$。

更新 $vis_{99999}=1$，从 $10$ 这个位置开始从右往左扫。

1. 扫到 $9$ 这个位置，显然，后面并没有出现 $100000$ 这个数，所以 $dp_9=dp_{10}+1=2$，并更新 $vis_{100000}=1$。

2. 扫到 $8$ 这个位置，显然，后面并没有出现 $4$ 这个数，所以 $dp_8=dp_9+1=3$，并更新 $vis_4=1$。

3. 扫到 $7$ 这个位置，显然，后面并没有出现 $3$ 这个数，所以 $dp_7=dp_8+1=4$，并更新 $vis_3=1$。

4. 扫到 $6$ 这个位置，显然，后面并没有出现 $2$ 这个数，所以 $dp_6=dp_7+1=5$，并更新 $vis_2=1$。

5. 扫到 $5$ 这个位置，显然，后面并没有出现 $1$ 这个数，所以 $dp_5=dp_6+1=6$，并更新 $vis_1=1$。

6. 扫到 $4$ 这个位置，显然，位置 $8$ 出现了 $4$ 这个数，有 $vis_4=1$，所以 $dp_4=dp_5=6$。无须再更新 $vis_4$ 了，下同。

7. 扫到 $3$ 这个位置，显然，位置 $7$ 出现了 $3$ 这个数，有 $vis_3=1$，所以 $dp_3=dp_4=6$。

8. 扫到 $2$ 这个位置，显然，位置 $6$ 出现了 $2$ 这个数，有 $vis_2=1$，所以 $dp_2=dp_3=6$。

9. 扫到 $1$ 这个位置，显然，位置 $5$ 出现了 $1$ 这个数，有 $vis_1=1$，所以 $dp_1=dp_2=6$。

这样，所有的 $dp$  数组全部更新完了：

$$\begin{cases}dp_1=6\\dp_2=6\\dp_3=6\\dp_4=6\\dp_5=6\\dp_6=5\\dp_7=4\\dp_8=3\\dp_9=2\\dp_{10}=1\end{cases}$$

显然，这和样例所给出的答案完全相符。相信对这个 $\texttt{dp}$ 的过程有了一定的加深理解。

那么，既然$\mathcal{O}(n)$ 的 $\texttt{dp}$ 预处理完了，剩下的询问就可以直接 $\mathcal{O}(1)$ 轻松搞定了，这下就可以轻松通过此题了。

## Code
本题只放 $\texttt{dp}$ 过程的核心代码部分，其中：

- $dp_i$ 表示 $[i,n]$ 内不同的数的个数。
- $vis_i$ 表示 $i$ 是否出现过，是的话 $vis_i=1$，否则 $vis_i=0$。

```cpp
f[n] = 1;
vis[a[n]] = 1;
for(int i = n - 1; i >= 1; --i) {
	if(!vis[a[i]]) {
		f[i] = f[i + 1] + 1;
		vis[a[i]] = 1;
	} else	f[i] = f[i + 1];
}
```

---

## 作者：李至擎 (赞：1)

法一：暴力模拟。

复杂度：$O(nm)$。

再看看题目范围： $(1<=n,m<=10^5)$ 。嗯，肯定会超时。

既然法一不行，那我们想想还有没有更好的方法呢？答案是有的。

我们可以运用预处理的方法，先 $O(n)$ 的存储好每种情况的答案，然后m次提问每次只用 $O(1)$ 的输出就行了，肯定不会超时。

因此，为了实现我们的想法，我们可以用上dp与前缀和的思想：定义一个num数组， $num[i]$ 表示 $[i,n]$ 这个区间中不同数的个数。因为 $dp[n]$ 一定为1（只有第n个数），我们就可以根据这一点来递推了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100005],sum[100005],n,m,vis[100005],x;//定义
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sum[n]=1;//赋值
	vis[a[n]]++;//用vis数组判断是否重复
	for(int i=n-1;i>=1;i--)//倒着枚举
	{
		if(vis[a[i]]==0)//之前没出现过
		{
			sum[i]=sum[i+1]+1;
		}
		else//之前出现过
		{
			sum[i]=sum[i+1];
		}
		vis[a[i]]++;
	}
	for(int i=1;i<=m;i++)//m次询问
	{
		cin>>x;
		cout<<sum[x]<<endl;
	}
	return 0;
}
```
### 完结撒花！！！

---

## 作者：xgwpp6710 (赞：1)

像往常一样，分析一下题目。

这题数据比较大，用暴力搜的复杂度是 $mn$ ，显然会`TLE`。

因此我们需要使用优化的方法。

那么到底用什么方法呢？

有了！因为 $\{l,n\}$ 中不同的数的数量和 $\{l+1,n\}$ 中不同的数的数量有关，只相差一个 $a[i]$ ，因此可以用动态规划（dp）通过此题。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[100009];//标记一个值是否出现过
int a[100009],l,n,m,dp[100009];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	dp[n]=1;//注意这里必须赋值，否则会数组越界
	vis[a[n]]=1;//标记此数出现过
	for(int i=n-1;i>=1;i--)//注意倒序枚举
	{
		dp[i]=dp[i+1];//{i+1,n}中的所有数，一定在{i,n}中
		if(!vis[a[i]])//判断当前的数是否出现过
		{
			vis[a[i]]=1;
			dp[i]++;
		}
	}
	for(int i=1;i<=m;i++)
	{
		cin>>l;
		cout<<dp[l]<<endl;//直接输出，简单无比！
	}
	return 0;
}
```

---

## 作者：nofall (赞：1)

看到好像没人发树状数组的题解，于是就发一篇

### 题目大意

给出一个长度为$n$的序列$a$,给出$m$个查询$l$,对于每个查询输出$[l,n]$的区间内不同数的个数。

分析：

将查询按照$l$的大小排序，从大到小的遍历，每次将$>=$当前$l$的位置的$a[i]$全部加入树状数组，让树状数组记录每个数是否出现过，每次的答案就是查询树状数组的总和。

代码：

```cpp
#include <cstdio>
#include <algorithm>
const int MAX = 100010;
#define lowbit(x) x & -x
using namespace std;
typedef pair<int, int> pa;
int n, m, ans[MAX], a[MAX], c[MAX];
pa l[MAX];
const int lim = 1e5 + 1;
//template
template<class type>type _max(type _, type __) { return _ > __ ? _ : __; }
template<class type>type _min(type _, type __) { return _ < __ ? _ : __; }
template<class type>type _abs(type __) { return __ < 0 ? -__ : __; }
template<class type>type _gcd(type __, type ___) { return (!___) ? __ : gcd(___, __ % ___); }
template<class type>type _mod(type __, type ____) { if (__ >= 0 && __ < ____)return __; __ %= ____; if (__ < 0)__ += ____; return __; }
template<class type>type _qpow(type __, type ___, type ____) { type ans = 1; for (; ___; ___ >>= 1, __ = _mod(__ * __, ____))if (___ & 1)ans = _mod(ans * __, ____); return ans; }
//char buf[1 << 21], *p1 = buf, *p2 = buf;
//inline int getc() {
//	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++;
//}
inline int r() {
	register int x = 0; register char ch = getchar();
	for (; ch < '0' || ch > '9'; ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
	return x;
}
inline double r_db() {
	double s = 0.0; int f = 1; char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
	while (c >= '0' && c <= '9') { s = s * 10 + (c ^ 48); c = getchar(); }
	if (c == '.') { int k = 10; c = getchar(); while (c >= '0' && c <= '9') { s += (double)(c ^ 48) / k; k *= 10; c = getchar(); } }
	return s;
}
//以上的template可以忽略
void add(int x) {
	while (x <= lim) {
		c[x]++;
		x += lowbit(x);
	}
}
int sum(int x) {
	int ret = 0;
	while (x) {
		ret += c[x];
		x -= lowbit(x);
	}
	return ret;
}
int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++)
			a[i] = r();
		for (int i = 0; i < m; i++) {
			l[i].first = r();
			l[i].first--;
			l[i].second = i;
		}
		sort(l, l + m);
		int j = n - 1;
		for (int i = m - 1; i >= 0; i--) {
			while (j >= l[i].first) {
				if (sum(a[j]) - sum(a[j] - 1) == 0)
					add(a[j]);
				j--;
			}
			ans[l[i].second] = sum(1e5);
		}
		for (int i = 0; i < m; i++)
			printf("%d\n", ans[i]);
	}
}
```

希望你们不要$ctrl+c$     $ctrl+v$

---

## 作者：OnlyExtreme (赞：1)

这是一道多么好的~~暴力~~树状数组题目啊。

首先考虑这样一个结论：

对于若干个右端点相同的询问，区间里出现的相同数字一定只需要考虑最后出现的那一次，例如：

`1   3   5   4   1`


这组数中，最左端的 $1$ 完全可以被最右端的 $1$ 代替，因为右端的 $1$ 一定会出现在查询的区间中，就算第一个 $1$ 计算过，在最后也会被重复计算，因此这个结论成立。

那么，我们可以建立一个数组 $ans$ 用于存储答案，$ans[i]$ 用于存储以 $i$ 为左端点的区间询问的答案，同时使用一个 $pre$ 数组储存当前数字上一次出现的位置 $pre[a[i]]$ 存储的是 $a[i]$ 对应的数上一次出现的位置下标。遍历数组，扫描到一个数字时，我们需要考虑这个数的贡献以及区间。

1. 如果这个数没有出现过，即 $pre[i]$ 为空，那么其影响区间为 $[1,i]$
2. 如果这个数出现过，即 $pre[i]$ 已经存储着这个数上次出现的位置，那么其影响区间为 $[pre[i]+1,i]$

相当于是每个数字只影响从当前位置到上一次出现的位置的区间，那么我们就将这个问题转化为了**区间修改**，**单点查询**的问题，但是直接暴力复杂度过高，因此可以使用数据结构进行优化，树状数组和线段树都可以实现，这里使用树状数组会更简单一些。

关于树状数组这里就不再赘述，[OI-WIKI](http://next.oi-wiki.org/ds/fenwick) 这里有详细的讲解，不会使用的可以去学习。

AC 代码如下。
```cpp
#include <bits/stdc++.h>
#define low(i) ((i) & (-(i)))
using namespace std;

int n, a[100010], b[100010];	// a 为原数组, b 为树状数组（差分）
int ans[100010];	// ans[i] 存储以 i 为左端点的区间答案
int m;
int q[100010];	// q 存储询问
int pre[100010];	// pre[a[i]] 存储 a[i] 这个数上次出现的位置

// 树状数组
void add(int p, int val){
	for(; p<=n; p+=low(p)){
		b[p] += val;
	}
}

int query(int p){
	int ans = 0;
	for(; p; p-=low(p)){
		ans += b[p];
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++){
		scanf("%d", &a[i]);
	}
	for(int i=1; i<=m; i++){
		scanf("%d", &q[i]);
	}
	for(int i=1; i<=n; i++){
		// 如果当前数字没有出现过
		if(!pre[a[i]]){
			pre[a[i]] = i;
			add(1, 1);
			add(i+1, -1);
		}
		// 如果当前数字出现过
		else{
			add(pre[a[i]]+1, 1);
			add(i+1, -1);
			pre[a[i]] = i;
		}
		if(i == n){
			// 遍历到右端点，准备查询答案
			for(int j=1; j<=m; j++){
				printf("%d\n", query(q[i]));
				// 查询以 q[i] 为左端点的区间答案
			}
		}
	}
	return 0;
}
```
完结撒花！

PS: [P1972 [SDOI2009]HH的项链](https://www.luogu.com.cn/problem/P1972) 思路与这一题基本相同，多了排序处理离线询问的技巧，大家可以进行练习。

---

## 作者：Terraria (赞：0)

## $Part$ $1:$ 题目大意：

有 $n$ 个数和 $m$ 个询问，每次询问给出 $l$ 求出区间 $\left[ l,n \right]$ 中不同数的个数。

数据范围： $1 \leq n,m,a_i \leq 10^5,1 \leq l \leq n$。

## $Part$ $2:$ 思路：

看到 $1 \leq n,m,a_i \leq 10^5$，就应该知道如果依照提议暴力枚举时间复杂度为 $O(nm)$，明显过不去。注意到 $a_i \leq 10^5$，于是乎想到用**桶**。

~~于是就没有难点了。~~

## $Part$ $3:$ 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt=0,l;
int a[100009];
int ans[1000009];//ans[i]表示区间[i,n]不同数的个数
int bucket[100009];//记录不同数出现的个数
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=n;i>=1;i--){//因为要求的区间是[l,n]，因此我们要从后往前枚举。
		if(!bucket[a[i]]){//如过没有出现这个数
			bucket[a[i]]++;
			cnt++;//cnt记录的是从后到i这个位置不同数的个数，正好满足题意需要
		}
		ans[i]=cnt;
	}
	while(m--){
		cin>>l;
		cout<<ans[l]<<endl;
	}
	return 0;
}
```


---

## 作者：LSG_waterf (赞：0)

## 直接摆思路：

$~~~~~~~~~$ 我们看到 $n$ 的范围到了 $10^5$ 级别，很明显，最暴力的方法明显是过不了的，这里给大家介绍一种最简单的DP思想:

$~~~~~~~~~$ 我们从后往前枚举，如果我们当前枚举到的数是第 $i$，即 $a[i]$ 个，就是说：如果 $a[i+1] 到  a[n]$中间出现过与 $a[i]$ 相等的数，那么我们就不用加一，直接枚举下一个数 $a[i-1]$ .

$~~~~~~~~~~$ 如果我们枚举到 $a[i]$ 并且之前没有出现过与 $a[i]$ 相同的数，就标记 $a[i]$ 已经出现过了．

```cpp
#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
int n,m,s[M],v[M],a[M],k[M];
// s[i] 记录的就是 i~n 之间有多少不同的数
// v[i] 记录的就是 i 这个数有没有出现，v[i]=1 就是出现了　，v[i]=0 就是没出现．
// a[i] 就是题目里的 a[i].
// k[i] 就是题目里的 l[i].
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) scanf("%d",&k[i]);
	for(int i=n;i>=1;i--)
	{
		if(!v[a[i]]) {s[i]=s[i+1]+1;v[a[i]]=1;}
        //如果 a[i] 这个数没有出现过,那么就是我们又找到了一个新的没有出现过的数．标记为出现过，更新答案．
		else s[i]=s[i+1];//否则，答案等于 i+1 项
	}
	for(int i=1;i<=m;i++) printf("%d\n",s[k[i]]);//注意输出的不是s[i]，是s[k[i]];
	return 0;
}
```
## 完结


---

## 作者：金银花露 (赞：0)

[CF368B Sereja and Suffixes](https://www.luogu.com.cn/problem/CF368B)

## 知识

1. 预处理

1. 题目的小变化应对

1. 前缀和（拓展）

## 1.审题

### 1.1关键点

1. 注意是从 $l$ 到 $n$。

1. 找的是不同数的个数。

### 1.2思路的开始

1. ~~暴力好，暴力秒！~~

直接暴力枚举区间里的数，用一个数组统计，每次询问输出。

## 2.暴力实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int A[100005];
int H[100005];
int f[100005];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	while(m--)
	{
		int x,ans=0;
		scanf("%d",&x);
		memset(H,0,sizeof(H));
		for(int i=x;i<=n;i++)//暴力统计
		{
			if(H[A[i]]==0)
			{
				ans++;
				H[A[i]]++;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```
## 3.优化

### 3.1预处理

刚刚的暴力肯定是不能通过这道题的。

于是在之前代码的基础上，我们先将每一个都算出来，询问时输出。

所以，我们用 $f_i$ 表示 $i$ 到 $n$ 的不同数种类。

其中，$f_i=f_{i+1}+1$ 的（如果 $i$ 是一个新数）。

如果不是新数，则是 $f_i=f_{i+1}$。

为了避免被更新错误，所以我们从后往前遍历。

### 3.2优化代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int A[100005];
int H[100005];
int f[100005];
int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	f[n]=1;
	H[A[n]]=1;
	for(int i=n-1;i>=1;i--)
	{
		if(H[A[i]]==0)
		{
		f[i]=f[i+1]+1;	
		H[A[i]]++;
		}
		else f[i]=f[i+1];
	}
	while(m--)
	{
		int x;
		scanf("%d",&x);
		cout<<f[x]<<"\n";
	}
	return 0;
}
```
## 4.变式

### 4.1变式

Q：若将问题改为从 $1$ 到 $l$ 呢？

A：在遍历时，从前往后遍历即可。

Q：若要求的是当中的最大值呢？

A：将 $f_i$ 的设为 $i$ 到 $n$ 里的最大值，则有 $f_i=\max(f_{i+1},A_i)$。

### 4.2前缀和

给定一个序列，求任意一段连续的数的和。

解法：

令 $f_i$ 为从 $1$ 到 $i$ 的和。

则有 $f_i=f_{i-1}+A_i$ 。

那么 $i$ 到 $j$ 的和为 $f_j-f_j$。

---

## 作者：一滴小水滴 (赞：0)

## 我认为这道题不应该是红题的，应该是一个黄题的水平，~~可能是恶意评分的~~

先跟大家说明一下，本蒟蒻的代码可能不想楼上那几位红名大佬的代码那样高大上，但是也能AC。

首先，看到这题的数据范围是十的五次方，我就有点心慌。如果用双层循环，那么时间复杂度就会变成O(n,m)~~（好像是这么写的吧？）~~，而时间限制只有一秒种，悲剧（TLE）一定会发生。所以我们可以从n~1一个个判断这个数有没有出现过。先给大家看一看代码
```cpp
bool t[100005];  //t用来记录这个数字有没有出现过。
int g[100005];   //g用来记录a[1]~a[n]每个数字开始的不同数字的数量。
memset(t,0,sizeof(t));
memset(g,0,sizeof(g));  
	//一定要记得初始化（本人闲着没事干用局部变量memset）
for(int i=n;i>=1;i--)  //一定要从后往前，不然会错。
{
	if(!t[a[i]])
    {
    	g[i]=g[i+1]+1; 
        t[a[i]]=1;
    }    //如果这个数字没有出现过，
         //那么g[i]就是在他之后的数字不同数量的个数+1。
	else g[i]=g[i+1];
            //不然这个g[i]就是他之后的数字的不同数量的个数。
}
```

既然这篇题解的重点已经讲完了，那么完整的代码就很好写了。
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int X=0,w=0;
	char ch=0;
	while(!isdigit(ch))
	{
		w|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		X=(X<<3)+(X<<1)+(ch^48);
		ch=getchar();
	}
	return w?-X:X;
}   //本人看数据大闲着没事写快读，但是完全可以用cin。
int main()
{
	int n,m,a[100005],l,g[100005],ans[100005];
                           //ans数组是用来记录每个数字的答案的。
	bool t[100005];
	memset(t,0,sizeof(t));
	memset(g,0,sizeof(g));
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=n;i>=1;i--)
	{
		if(!t[a[i]])g[i]=g[i+1]+1;
		else g[i]=g[i+1];
		t[a[i]]=1;
	}
	for(int i=1;i<=m;i++)
	{
		l=read();
		ans[i]=g[l];
	}    //每次输入l[i]，就把ans的值改为g[l]。
	for(int i=1;i<=m;i++)
		cout<<ans[i]<<endl;  //最后输出答案就可以啦。
	return 0;
}
```
大家最好不要用上那三个键，可以自己多想想再写啊。

---

