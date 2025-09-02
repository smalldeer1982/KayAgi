# [ABC325G] offence

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc325/tasks/abc325_g

文字列 $ S $ が与えられます。文字列 $ S $ に対して以下の操作を $ 0 $ 回以上繰り返し行うことで得られる文字列の長さの最小値を求めてください。

- 文字列の中で `of` が連続する箇所および $ 0 $ 以上 $ K $ 以下の整数 $ i $ を $ 1 $ つ選ぶ。その後、`of` およびその後ろに連続する $ i $ 文字を文字列から取り除く。

## 说明/提示

### 制約

- $ 0\ \leq\ K\ <\ |S|\ \leq\ 300 $
- $ K $ は整数
- $ S $ は英小文字からなる文字列
 
### Sample Explanation 1

$ 4,\ 5 $ 文字目に連続する `of` を選び、$ i\ =\ 3 $ とすることで `keyofscience` から `ofsci` を取り除き、 `keyence` を得ます。 操作の繰り返しにより文字列の長さを $ 6 $ 以下にすることはできないため、$ 7 $ が答えとなります。

## 样例 #1

### 输入

```
keyofscience
3```

### 输出

```
7```

## 样例 #2

### 输入

```
oofsifffence
3```

### 输出

```
2```

## 样例 #3

### 输入

```
ooofff
5```

### 输出

```
0```

## 样例 #4

### 输入

```
okeyencef
4```

### 输出

```
9```

# 题解

## 作者：CultReborn (赞：12)

[原题链接](https://atcoder.jp/contests/abc325/tasks/abc325_g)、[洛谷题面](https://www.luogu.com.cn/problem/AT_abc325_g)


[更好的阅读体验](https://www.cnblogs.com/CultReborn/articles/ABC325G-offence-qujian-dp-tijie.html)

# 题意
给你一个字符串 $S$ 和一个自然数 $K$。请找出对字符串 $S$ 执行下列操作 $0$ 次或 $0$ 次以上所得到的字符串的最小长度：

+ 在字符串中选择一个连续出现的 `of`；
+ 选择一个介于 $0$ 和 $K$ 之间的整数 $i$；
+ 从字符串中删除选中的 `of` 和其后面的 $i$ 个字符。

# 思路
看到这种区间合并的最优解问题我们就想到区间 dp。

### 解法一
规定 $dp(l,r)$ 为区间 $[l,r]$ 经过若干次操作后可以得到的最小长度，其中 $0<l\leq r\leq |S|$。

对于区间 $[l,r]$，规定其最小长度最劣的转移方程为 $dp(l,r)=1+dp(l+1,r)$，（这么做是为了和接下来更新答案的方式对应）紧接着继续考虑删除操作。

规定 $[l,r]$ 之间的某个字符下标为 $x(l<x<r)$，当且仅当：

+ $S[l]$ 为字符 `o`；
+ $S[x]$ 为字符 `f`；
+ $dp(l+1,x-1) = 0$，即 $[l+1,x-1]$ 可以完全被删除。


这样，$[l,x]$ 就可以被完全删除。在这种情况下，转移方程就是：

$$
\min \{ 1+dp(l+1,r),\max[dp(x + 1,r) - p,0]\}
$$

如何理解 $\max[dp(x + 1,r) - p,0]$？

$[l,x]$ 已经被清空了，剩下 $[l+1,r]$ 的最短长度就是 $dp(l+1,r)$，而题目规定可以在 `of` 后再删除 $K$ 个字符，那么能删则删，删得越多越好，一直删到 $0$ 为止。

### 解法二

还有另外一种设计状态转移的方法，第三重循环枚举中间分界的时候，里面套有三次循环：

1. 第一次循环：先规定 $dp(l,r)$ 最劣的答案为当前选择的区间长度 $r-l+1$，然后枚举中间分解点 $x$，更新一波答案：$dp(l,r)=\min[dp(l,r),dp(l,x) + dp(x + 1,r)]$。
2. 第二次循环：如果 $s[l]=o$，那么再枚举一波中间分界点 $x$，找到 $s[x] = f$。然后 $dp(l,r) = \min\{dp(l,r),\max[dp(x + 1,r) - p,0]\}$。
3. 第三次循环：如果 $s[r]=f$，那么再枚举一波中间分界点 $x$，找到 $s[x] = o$。然后 $dp(l,r) = \min[dp(l,r),dp(l,x-1)]$。

不难证明这样转移不重不漏。尽管这样写常数大，但是是区间 dp 更一般的思路，所以推荐大家也看一看。

我只给出解法一的代码：

# 代码
[AC 记录](https://atcoder.jp/contests/abc325/submissions/46941293)
      
算法的时间复杂度为 $O(|S|^3)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1003;
string s; 
int n,p,dp[maxn][maxn];
int main(){
	cin >> s >> p;
	n = s.size(); s = " " + s;
	for(int i = 1;i <= n;++i) dp[i][i] = 1;
	for(int len = 2;len <= n;++len){
		for(int i = 1;i <= n + len - 1;++i){
			int j = i + len - 1;
			dp[i][j] = 1 + dp[i + 1][j];
			if(s[i] != 'o') continue;
			for(int k = i + 1;k <= j;++k)
				if(s[k] == 'f' && dp[i + 1][k - 1] == 0)
					dp[i][j] = min(dp[i][j],
					max(dp[k + 1][j] - p,0));
		}
	}
	cout << dp[1][n] << endl;
	return 0;
}
```
[![Page Views Count](https://badges.toozhao.com/badges/01HDNH2TZ1J1K0SQ70GRM76M2X/orange.svg)](https://badges.toozhao.com/stats/01HDNH2TZ1J1K0SQ70GRM76M2X "Get your own page views count badge on badges.toozhao.com")

这题的 $|S|$ 真的小于 $300$ 吗？我开到了 $1000$ 才没有 RE。。。

---

## 作者：Creeper_l (赞：2)

## 题意

给定一个长度为 $n$ 字符串以及一个数 $f$，你可以执行以下操作任意次，求最终字符串长度的最小值。

- 在字符串中选择一个连续的 ```of```，删掉它以及它后面的 $i$ 个字符，$0 \le i \le f$。

数据范围：$n \le 300$。

## 思路

看到数据范围以及字符串中间的删除可以想到区间 dp。

设 $dp_{i,j}$ 表示 $i$ 到 $j$ 这一段字符串最少能被删到几个。那么我们可以枚举左右端点 $i,j$ 以及中间点 $k$，如果满足 $s_{i}=o$，$s_{k}=f$ 并且 $i+1$ 到 $k-1$ 这一段可以被删完的话，那么就有转移 $dp_{i,j}=\max(0,dp_{k+1,j}-f)$。最终的答案就是 $dp_{1,n}$。

要初始化。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f
const int MAXN = 1e3 + 10;
int f,n,dp[MAXN][MAXN];
char s[MAXN];
signed main()
{
	memset(dp,inf,sizeof dp);
	cin >> (s + 1) >> f;
	int n = strlen(s + 1);
	for(int i = 1;i <= n + 1;i++) dp[i][i] = 1,dp[i][i - 1] = 0;
	for(int i = 1;i < n;i++) 
	{
		if(s[i] == 'o' && s[i + 1] == 'f') dp[i][i + 1] = 0;
		else dp[i][i + 1] = 2; 
	}
	for(int len = 3;len <= n;len++)
		for(int i = 1;i <= n - len + 1;i++)
		{
			int j = i + len - 1;
			dp[i][j] = min(dp[i + 1][j],dp[i][j - 1]) + 1;
			if(s[i] != 'o') continue;
			for(int k = i + 1;k <= j;k++) 
			{
				if(s[k] == 'f' && dp[i + 1][k - 1] == 0) 
					dp[i][j] = min(dp[i][j],max(0ll,dp[k + 1][j] - f));
			}
		}
	cout << dp[1][n];
	return 0;
} 
```


---

## 作者：Zwb0106 (赞：1)

[**原题链接**](https://atcoder.jp/contests/abc325/tasks/abc325_g)

------------

给一个神秘抽象做法。

------------
## 思路

结合删除子串的操作和较小的数据范围，推测区间 DP。

我最初的想法是设 $f_{l,r}$ 表示区间 $[l,r]$ 是否能被完全删除，但是显然不够，因为一个串删除后可以选择多删后面的字符。然后状态含义改成 $0$ 不能删除，若删除的话，$s_l$ 与 $s_r$ 是否能构成一对匹配的 $\texttt{of}$，$1$ 表示不能，$2$ 表示能。

对于所有能删除的区间（后两类），最小化原串长度等价于任意选若干不交区间使得长度和最大。

关于 $f$ 的转移，大概有以下几种情况：

1. 若 $s_l \ne \texttt{o}$ 则 $f_{l,r}$ 必为 $0$；
2. 若存在 $k$ 使得 $f_{l,k} = 2$ 且 $k+K \ge r$，则 $f_{l,r} \leftarrow 1$；
3. 若存在 $k$ 使得 $f_{l,k} \ne 0$ 且 $f_{k+1,r} \ne 0$，则 $f_{l,r} \leftarrow \max\{ f_{l,k},f_{k+1,r} \}$；
4. 若 $s_r = \texttt{f}$ 且 $f_{l,r} \ne 0$，则 $f_{l,r} \leftarrow 2$。

然而这是错误的。对拍找到这样一组数据：$s = \texttt{ffffofoofoooofo}$，$K=2$。答案为 $4$，除了前缀 $\texttt{ffff}$ 都可以删除。发现上述做法问题在于，两个可删除的串拼接后，前面的串仍然能够继续删除字符。

信息记录过少，现在修改状态，$-1$ 表示不能被删除，否则 $f_{l,r}$ 为删除 $[l,r]$ 后至多再删除多少字符。

转移如下：

1. 若 $s_l \ne \texttt{o}$ 则 $f_{l,r}$ 必为 $-1$；
2. 若存在 $k$ 使得 $f_{l,k} \ge r-k$，则 $f_{l,r} \leftarrow f_{l,k} - (r-k)$；
3. 若存在 $k$ 使得 $f_{l,k} \ne -1$ 且 $f_{k+1,r} \ne -1$，则 $f_{l,r} \leftarrow \max\{ f_{l,k}+f_{k+1,r} \}$；
4. 若 $s_r = \texttt{f}$ 且 $f_{l,r} \ne -1$，则 $f_{l,r} \leftarrow K$。

选线段的部分是平凡的，此处略去。

时间复杂度 $O(n^3)$。

------------
## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define gc getchar
#define pc putchar
#define fs first
#define sc second
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define lowbit(x) (x&(-x))
using namespace std;

ll read()
{
	ll x=0,f=1;
	char ch=gc();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc();
	}
	while(ch>='0'&&ch<='9')
		x=x*10+(ch^48),ch=gc();
	return x*f;
}
void print(ll x)
{
	if(x<0)pc('-'),x=-x;
	if(x>9)print(x/10);
	pc(x%10+48);
}

const int N=305;
int n,K,f[N][N],g[N];
char s[N];
vector<int>p[N];

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
	scanf("%s",s+1),n=strlen(s+1),K=read();
	
	memset(f,-1,sizeof(f));
	
	for(int i=1;i<n;i++)
		if(s[i]=='o'&&s[i+1]=='f')
			f[i][i+1]=K;
	
	for(int len=3;len<=n;len++)
		for(int l=1,r=len;r<=n;l++,r++)
		{
			if(s[l]!='o')continue;
			
			for(int k=l+1;k<r;k++)
				if(f[l][k]>=r-k)
					f[l][r]=max(f[l][r],f[l][k]-(r-k));
			
			for(int k=l+1;k+1<r;k++)
				if(f[l][k]!=-1&&f[k+1][r]!=-1)
					f[l][r]=max(f[l][r],f[l][k]+f[k+1][r]);
			
			if(s[r]=='f'&&f[l+1][r-1]!=-1)
				f[l][r]=K;
		}
	
	for(int l=1;l<n;l++)
		for(int r=l+1;r<=n;r++)
			if(f[l][r]!=-1)p[r].push_back(l);
	
	for(int r=1;r<=n;r++)
	{
		g[r]=g[r-1];
		for(int l:p[r])
			g[r]=max(g[r],g[l-1]+(r-l+1));
	}
	
	print(n-g[n]);
	
	return 0;
}
```

---

## 作者：FReQuenter (赞：1)

考虑区间 dp。

设 $f_{i,j}$ 表示当前区间为 $[i,j]$，删除完之后剩下的最少字符数。

考虑如何转移。

分两种情况考虑：

- 由两个子区间合并而来。那么直接枚举中点 $i\le m<j$，取 $f_{i,j}\leftarrow\text{min}\{f_{l,m}+f_{m+1,r}\}$

- 区间左端点为 `o`，再找一个为 `f` 的位置合并。那么只需要枚举这样一个 $s_m$ 的值为 `o` 且 $i\le m<j$ 就可以转移 $f_{i,j}\leftarrow\text{min}\{\text{max}\{0,f_{m+1,r}-k\}\}$ 需要满足 $f_{l+1,m-1}=0$。即这一对 of 发生的合并。

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[305][305];
signed main(){
  int n,k;
  string s;
  cin>>s>>k;
  n=s.length();
  s='#'+s;
  for(int r=1;r<=n;r++){
    for(int l=r;l>=0;l--){
      f[l][r]=r-l+1;
      for(int m=l;m<r;m++){
        f[l][r]=min(f[l][r],f[l][m]+f[m+1][r]);
      }
      if(s[l]=='o'){
        for(int m=l+1;m<=r;m++){
          if(s[m]=='f'&&f[l+1][m-1]==0) f[l][r]=min(f[l][r],max(0,f[m+1][r]-k));
        }
      }
    }
  }
  cout<<f[1][n];
}
```

---

## 作者：forever_nope (赞：1)

一道不难但是需要想一想的区间 DP。

有一个比较复杂的例子：`ooofofxxx`，简单的分析可知，一个 `of` 后面删除多少，与其前、后都有关，于是考虑区间 DP。

想到这里，其实问题已经解决一半了。

### 状态设计

设 $f(l,r)$ 为闭区间 $[l,r]$ 经过操作之后的最小长度。

注意：我的状态设计与 [官方题解](https://atcoder.jp/contests/abc325/editorial/7487) 的区别在于，我设计的是闭区间，而官方题解是左闭右开。

考虑转移，我们分类讨论第一个字符是否删除。

### 删除

#### 条件：

- $S_l=\texttt{o}$；
- 找到一个 $(l,r]$ 内的 $k$，满足 $S_k=\texttt{f}$；
- $(l,k)$ 内的所有字符能删除，即 $f(l+1,k-1)=0$。

#### 转移：

- 那么可以转移 $f(l,r)=\max\{f(k+1,r)-K,0\}$；
- 表示：先删除 $(l,k)$，然后删除 $l$ 和 $k$ 及后面的 $K$ 的字符，但是不能删到负数。

### 不删除

#### 条件：

- 无，任何情况均可转移.

#### 转移：

- 因为第一个字符不删除，所以 $l$ 和 $(l,r]$ 是独立的；
- 所以有 $f(l,r)=f(l+1,r)+1$；
- 表示：$l$ 后面的，最少可以剩下多少个字符，在加上 $l$ 这个字符。

### 代码

于是，时间复杂度为 $\mathcal{O}(n^3)$，可过。

代码见：<https://atcoder.jp/contests/abc325/submissions/46904975>


---

## 作者：Sevendays_Coder (赞：1)

捡到一个比较简单的 G，切了水篇题解

##  _Description_

>- 给定一个字符串 $S$，一个**非负**整数 $K$。

>- 你可以进行若干次操作，每次操做选择一个非负整数 $i(0\le i\le K)$，在选择一个子段```of```，再删去```of```和紧跟的 $i$ 个字符。

>- 求操作后的最小长度。

>- $0\le K<|S|\le300$。

## _Solution_
 $300$ 的数据范围，一眼区间 DP。
 
 设 $f_{i,j}$ 表示区间 $[i,j]$ 的最小剩余长度。
 
 第一种转移 ：当且仅当左端点为```o```： 
 
 设 $E$ 为满足 $S_k=$ ```f```， $0\le k<|S|$，
 的 $k$ 的集合。
 
 $~~~~~~~\forall k\in E,(k=i+1)\lor(i\le k\le j\land f_{i+1,k-1}=0),$

 $~~~~~~~~f_{i,j}=\min(f_{i,j},\max(f_{k+1,r}-K,0))$
 
 第二种转移：
 	
 $~~~~~~~\forall k,i\le k<j,$

$~~~~~~~~~f_{i,j}=\min(f_{i,j},f_{i,k}+f_{k+1,j})$
 
 输出 $f_{0,|S|}$ 就做完了。
 
 时间复杂度 $O(n^3)$。
 
 代码如下：
 
 ```cpp
#include<bits/stdc++.h>

using namespace std;
int f[305][305];
int main()
{
	string c;
	cin>>c;
	int n=c.size(),kk;
	cin>>kk;
	int ans=0;
	for(int i=0;i<n;i++)
		f[i][i]=1;
	for(int len=2;len<=n;++len)
	{
		for(int l=0;l+len-1<n;++l)
		{
			int r=l+len-1;
			if(len==2)
			{
				f[l][r]=(c[l]=='o'&&c[r]=='f')?0:2;
				continue;
			}
            f[l][r]=r-l+1;
			if(c[l]=='o')
				for(int k=l+1;k<=r;k++)
				{
					if(c[k]!='f')
						continue;
					if(k!=l+1&&f[l+1][k-1]!=0)
						continue;
					f[l][r]=min(f[l][r],max(f[k+1][r]-kk,0));
				}
			for(int k=l;k+1<=r;k++)
				f[l][r]=min(f[l][r],f[l][k]+f[k+1][r]);
		}
	}
	printf("%d\n",f[0][n-1]);
 	return 0;
}

```


---

## 作者：WaterSun (赞：0)

# 思路

看到消除区间，并且 $|S| \leq 300$ 果断选择区间 DP。

定义 $dp_{i,j}$ 表示操作 $i \sim j$ 区间能剩下最少数量。

首先枚举 $i,j$，然后枚举一个分解点 $k$，那么显然有 $dp_{i,j} = \min_{i \leq k < j}\{dp_{i,k} + dp_{k + 1,j}\}$。

如果 $s_i$ 是 `o`，需要单独考虑一下。

依旧在 $k \in (i,j]$ 寻找 $s_k$ 为 `f` 的 $k$，如果 $dp_{i + 1,k - 1}$ 不为 $0$，表明 $(i + 1) \sim (k - 1)$ 不能完全操作掉，因此无法使得 $i,k$ 挨在一起，形成 `of`。

所以当我们找到满足 $dp_{i + 1,k - 1} = 0$ 的 $k$ 时，$i \sim k$ 中的所有元素都能被消除，并且可以在 $k$ 之后顺手消除 $K$ 个，所以直接将 $dp_{i,j}$ 设为 $\min(dp_{i,j},\max(dp_{k + 1,j} - K,0))$ 即可。

# code

```cpp
#include <bits/stdc++.h>
#define re register

using namespace std;

const int N = 310;
int n,m;
int dp[N][N];
string s;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> s >> m;
	n = s.size();
	s = ' ' + s;
	for (re int i = 1;i <= n;i++){
		for (re int j = i;j <= n;j++) dp[i][j] = j - i + 1;
	}
	for (re int l = 2;l <= n;l++){
		for (re int i = 1;i + l - 1 <= n;i++){
			int j = i + l - 1;
			if (l == 2){
				if (s[i] == 'o' && s[j] == 'f') dp[i][j] = 0;
			}
			else{
				for (re int k = i;k < j;k++) dp[i][j] = min(dp[i][j],dp[i][k] + dp[k + 1][j]);
				if (s[i] == 'o'){
					for (re int k = i + 1;k <= j;k++){
						if (s[k] == 'f' && !dp[i + 1][k - 1]) dp[i][j] = min(dp[i][j],max(dp[k + 1][j] - m,0));
					}
				}
			}
		}
	}
	cout << dp[1][n];
	return 0;
}
```

---

