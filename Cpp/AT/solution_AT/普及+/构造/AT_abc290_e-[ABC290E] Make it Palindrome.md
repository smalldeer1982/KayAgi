# [ABC290E] Make it Palindrome

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc290/tasks/abc290_e

数列 $ X $ に対し、 $ f(X)\ = $ ( $ X $ を回文にするために変更する必要のある要素の個数の最小値 ) とします。

与えられた長さ $ N $ の数列 $ A $ の全ての **連続** 部分列 $ X $ に対する $ f(X) $ の総和を求めてください。

但し、長さ $ m $ の数列 $ X $ が回文であるとは、全ての $ 1\ \le\ i\ \le\ m $ を満たす整数 $ i $ について、 $ X $ の $ i $ 項目と $ m+1-i $ 項目が等しいことを指します。

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ N $
 
### Sample Explanation 1

\- $ f(5)\ =\ 0 $ - $ f(2)\ =\ 0 $ - $ f(1)\ =\ 0 $ - $ f(2)\ =\ 0 $ - $ f(2)\ =\ 0 $ - $ f(5,2)\ =\ 1 $ - $ f(2,1)\ =\ 1 $ - $ f(1,2)\ =\ 1 $ - $ f(2,2)\ =\ 0 $ - $ f(5,2,1)\ =\ 1 $ - $ f(2,1,2)\ =\ 0 $ - $ f(1,2,2)\ =\ 1 $ - $ f(5,2,1,2)\ =\ 2 $ - $ f(2,1,2,2)\ =\ 1 $ - $ f(5,2,1,2,2)\ =\ 1 $ 以上より、求める答えは $ 9 $ です。

## 样例 #1

### 输入

```
5
5 2 1 2 2```

### 输出

```
9```

# 题解

## 作者：_JellyFish_ (赞：8)

#  1. 题意
 
一个长度为 $N$ 的序列 $X$，求将 $X$ 的每个连续子序列分别变成回文串所需要的最小操作次数。
 
#  2. 分析
将每一对点 $l$ 和 $r$ 进行连线：如果相等，称作它们的连线为好线，如果不等，称作坏线。

为什么要这样做呢？我们发现，对于每一对坏线，他都会在一定的区间内，产生答案的贡献。举例：$A={1,2,4,2,3}$，对于 $a_2$ 和 $a_3$，它们之间连了一条坏线，会使 $[2,3]$ 和 $[1,4]$ 两个区间的答案增加，从而对总答案产生贡献。

不难发现，只有坏线会对总答案产生贡献，而坏线其实不好直接计算，我们考虑用总线的数量减去好线的数量。发现数据范围：所有的 $a_i \le n$，开一个数组，记录某个数出现的所有位置，从而计算好线的对答案的贡献。好线的贡献，也可以理解为这对线能让最终答案减少多少。如果 $a_i=a_j$，那么他们对答案的贡献就是 $min(l,n-r+1)$。

接下来，假设 $P_x$ 数组存储了 $x$ 这个数在序列中所有出现的位置，比如 $A={1,2,4,2,3}$，则 $P_2={2,4}$。

设 $l=0$，$r=size(P_x)-1$，可以发现，如果 $P_{x,l}<n+1-P_{x,r}$，那么对于 $P_{x,l}<n+1-P_{x,r-1}$，$P_{x,l}<n+1-P_{x,r-2}$，...，$P_{x,l}<n+1-P_{x,l+1}$，它们都是成立的，所以它们的贡献都是 $P_{x,l}$。总共献即 $(r-l) \times P_{x,l}$。同时，以 $l$ 为左端点的所有区间都处理完了，所以 $l+1$，另外一种情况同理。

细节见代码。
# 3.代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[200005],ans;
vector<vector<int> >V(200005);//V[i]存储数i的所有出现位置 
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],V[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		ans+=(n-i+1)*(i/2);//计算所有线的数量 
		int l=0,r=V[i].size()-1;
		while(l<r){
			ans-=(r-l)*min(V[i][l],n+1-V[i][r]);//ans减去"好线"的数量就是坏线的数量 
			(V[i][l]<(n+1-V[i][r]))?l++:r--;//类似双指针写法 
		}
	}
	cout<<ans;
	return 0;
}
}
```

---

## 作者：zhaoyp (赞：4)

考虑有多少个相等的数对不会对答案产生贡献。

记一个相等的数对的下标为 $(x,y)$，则他会在 $\min\{x,n - y + 1\}$ 个子串里成为对应位置。

对于每个数值 $x$，记他所有出现的位置构成的序列为 $b$。

在 $b$ 中枚举左端点 $i$，在剩下部分里进行二分，二分一个点 $mid$，在他左边的右端点贡献为 $i$，右边的用一个类似前缀的东西预处理一下就行了。

然后在加回所有对应位的数量即可。

```cpp
/*
看到你时总是感觉清风徐徐
本以为和你相识不会是偶遇
奈何你犹如过客、化作秋雨
只是经过我生命的一瓢柳絮
从不会真正有童话似的结局
我静静地写尽这些躁言丑句
本以为可以稍稍地缓解抑郁
却是徒增一场悲伤的脑补剧
你问我为什么说这么多?
因为这题是 ABC290E
*/
#include<bits/stdc++.h>
using namespace std;
#define pb	push_back
const int maxn = 2e5 + 5;
long long ans,n,a[maxn],tot,b[maxn],sum[maxn];
vector <int> d[maxn];
inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
  	return f * x;
}
int main()
{
	n = read();
	for(int i = 1;i <= n;i++)	d[read()].pb(i);
	for(int i = 1;i <= n;i++)	if(d[i].size())
	{
		tot = 0;
		for(int j = 0;j < (int) d[i].size();j++)	b[++tot] = d[i][j];
		for(int j = 1;j <= tot;j++)	sum[j] = sum[j - 1] + b[j];
		for(int j = 2;j <= tot;j++)
		{
			int tmp = upper_bound(b + 1,b + 1 + tot,n + 1 - b[j]) - b - 1;
			tmp = min(tmp,j - 1);
			ans -= sum[tmp];
			if(tmp < j)	ans -= 1ll * (j - tmp - 1) * (n - b[j] + 1);
		}
		for(int j = 1;j <= tot;j++)	sum[j] = 0;
	}
	for(int i = 1;i <= n;i++)	ans += 1ll * (i / 2) * (n - i + 1);
	cout << ans;
	return 0 ;
}
/*
NOIP 2023 RP++
*/
```

---

## 作者：ダ月 (赞：4)

### 题意概要：

给定长度为 $n$ 的序列 $a_i$，定义 $f(B)$ 为 $a_i$ 子区间 $B$ 中，修改最少的次数让 $B$ 成为一个回文序列。求所有 $f(B)$ 的和。

### 题目分析：

对于一个子区间 $B$，第 $i$ 个数需要匹配的位置如果与 $i$ 能够成功匹配，那么第 $i$ 个数与其对应匹配位置连一条线，叫这条线为**好线**。如果不能匹配，也连一条线，我们称呼其为**坏线**。定义**线**为好线与坏线的总和。显然题目让我们统计所有的坏线之和。

若 $B$ 区间长度为 $l$，显然区间内有 $\left\lfloor\frac{l}{2}\right\rfloor$ 条线。那么序列 $a_i$ 一共有 $\begin{aligned}\sum_{i=1}^n(n-i+1)\times\left\lfloor\frac{i}{2}\right\rfloor\end{aligned}$ 条线。

我们考虑容斥，即坏线的数目等于线数目减去好线数目。

我们取其中两个相同的数，位置分别在 $x,y(x<y)$，显然产生的贡献为 $\min(n-y+1,x)$。这样可以暴力统计答案。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
const int N=2e5+10;
ll a[N];
ll sum=0,ans=0;
vector<ll> b[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) sum+=(n-i+1)*(i>>1);
	for(int i=1;i<=n;i++) b[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		for(int j=0;j<b[i].size();j++){
			for(int k=j+1;k<b[i].size();k++)
				ans+=min(b[i][j],n-b[i][k]+1);
		}
	}printf("%lld\n",sum-ans);
	return 0;
}
```


时间复杂度：最坏 $O(n^2)$。

显然无法通过此题。我们考虑优化。

我们可以考虑双指针，如果右指针 $j$ 的数产生的贡献（即 $n-j+1$）大于左指针 $i$ 的数产生的贡献（即 $i$），那么产生的总贡献为 $i$ 指针的贡献乘上 $j-i$。相反同理。

代码如下：

```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n;
const int N=2e5+10;
ll a[N];
ll sum=0,ans=0;
vector<ll> b[N];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++) sum+=(n-i+1)*(i>>1);
	for(int i=1;i<=n;i++) b[a[i]].push_back(i);
	for(int i=1;i<=n;i++){
		int l=0,r=b[i].size()-1;
		while(l<r){
			if(b[i][l]<n+1-b[i][r]) ans+=(r-l)*b[i][l],l++;
			else ans+=(r-l)*(n+1-b[i][r]),r--;
		}
	}printf("%lld\n",sum-ans);
	return 0;
}
```

时间复杂度：$O(n)$。

---

## 作者：2huk (赞：2)

## 题目描述

对于一个序列 $X$，我们设函数 $f(X)$ 表示将 $X$ 修改为回文串需要修改的数的数量。

现在，给定一个长度为 $N$ 的序列 $A$，问 $A$ 的所有连续的子序列（也就是子串）的 $f(X)$ 的值的和。

## 样例输入输出

```
5
5 2 1 2 2
```

```
9
```

## 数据范围

$1 \le A_i \le N \le 2 \times 10^5$

## 思路

对于一对数，如果两个数不相同，则称这个对是“坏对”，否则这个对是“好对”。

如果要求所有的 $f(X)$ 的值的和，就相当于要求所有的坏对会影响到的区间的总数。

什么叫做影响到的区间呢？

![image](https://img1.imgtp.com/2023/04/08/4oyJjmLe.png)

上图中，如果 $3$ 与 $5$ 是不同的，那么如果要求 $f(3, 4, 5)$ 或 $f(2, 3, 4, 5,6)$ 时，由 $3$ 和 $5$ 所构成的影响数就各多了 $1$。因此我们就称 $3$ 和 $5$ 这个坏对所造成的影响为 $2$。

## 暴力

如果找到一个坏对，那么它就会造成若干各不好的影响。形象到的区间的总数为 $\min(l, n-r+1)$。

如果存在一个坏对，那么他会影响到它左右两边的区间，并且这个区间两个端点距离当前这个坏对的端点的距离是一样的。那么，只需要求出左右两边各存在多少个点，并取最小值即可。

```cpp
for(int i=1; i<=n; i++){
	for(int j=i; j<=n; j++){
		if(a[i] != a[j]){
			res += min(i, n-j+1);
		}
	}
}
```

暴力时间复杂度是 $\Theta(n^2)$，显然不可取。

## 优化

如果要求坏对影响的数量，那么可以求出所有对影响区间的数量，再减去所有对影响区间的数量。

求解这两个值我们使用双指针算法。

### 所有对影响区间的数量

令 $l$ 指向第 $1$ 项，$r$ 指向最后 $1$ 项。

首先分别统计出当前 $l$ 即 $l$ 左边元素的数量为 $x$，$r$ 即 $r$ 右边元素的数量为 $y$。那么就有 $x = l, y = n - r + 1$。

如果左边的数量小于右边的数量，那么产生的影响为 $(r - l) \times x$。此时我们认为与 $l$ 构成的对已经算完了，那么将 $l$ 向右移动。

否则，如果左边的数量大于右边的数量，那么产生的影响为 $(r - l) \times y$。此时我们认为与 $r$ 构成的对已经算完了，那么将 $r$ 向左移动。

```cpp
l = 1, r = n;
while(l < r){
	int x = l;
	int y = n - r + 1;
	if(x < y){
		res += (r-l) * x;
		l++;
	}
	else{
		res += (r-l) * y;
		r--;
	}
}
```

### 好对影响区间的数量

首先统计出所有数字出现的位置存于 `vector<int> v[N]` 。

统计出来后，我们每个数字的看，这样就保证目前统计的数都是相同的。

再令 $l$ 指向当前数字位置的第 $0$ 项，$r$ 指向最后 $1$ 项。（`vector` 是从 $0$ 开始）

对于每一次计算得到的 $l, r$ 对，首先找到两个值再原数组中的实际位置，即 `int ll = v[e][l], rr = v[e][r];`。

与上面类似，分别统计出当前 $ll$ 即 $ll$ 左边元素的数量为 $x$，$rr$ 即 $rr$ 右边元素的数量为 $y$。那么就有 $x = ll, y = n - rr + 1$。

如果左边的数量小于右边的数量，那么产生的影响为 $(r - l) \times x$。此时我们认为与 $l$ 构成的对已经算完了，那么将 $l$ 向右移动。

否则，如果左边的数量大于右边的数量，那么产生的影响为 $(r - l) \times y$。此时我们认为与 $r$ 构成的对已经算完了，那么将 $r$ 向左移动。

```cpp
for(auto e : s){		// 枚举所有出现过的元素，s 表示出现过的元素所构成的集合 
	int l = 0, r = v[e].size() - 1;
	
	if(v[e].size() >= 2){		// 必须能构成对 
		while(l < r){
			int ll = v[e][l], rr = v[e][r];
			int x = ll, y = n - rr + 1;
			
			if(x < y){
				res -= (r - l) * x;
				l++;
			}
			else{
				res -= (r - l) * y;
				r--;
			}
		}
	}
}
```

## 代码

```cpp
AC 代码
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int N = 2e5 + 10;

int n, x, res;
vector<int> v[N];
int l, r;
set<int> s;		// 出现过的元素构成的集合 
int a, b;

signed main(){
	// 读入 
	scanf("%lld", &n);
	
	for(int i=1; i<=n; i++){
		scanf("%lld", &x);
		v[x].push_back(i);		// x 元素在 i 上出现了一次 
		s.insert(x);
	}
	
	// 所有对影响区间的数量
	l = 1, r = n;
	
	while(l < r){
		if(l < n - r + 1){
			res += (r - l) * l;
			l++;
		} 
		else{
			res += (r - l) * (n - r + 1);
			r--;
		}
	}
	
	// 好对影响区间的数量
	for(auto e : s){
		l = 0, r = v[e].size() - 1;
		while(l < r){
			a = v[e][l], b = v[e][r];
			if(a < n - b + 1){
				res -= (r - l) * a;
				l++;
			}
			else{
				res -= (r - l) * (n - b + 1);
				r--;
			}
		}
	}
	
	// 输出 
	printf("%lld", res);
	
	return 0;
}
```


---

## 作者：lzc0115 (赞：1)

## ABC290E
### 题目大意
**对于一个序列 $X$ 记 $F(X)$ 为使它成为回文序列的最小修改次数。给定长度为 $n$ 的序列 $A$，$X$ 为 $A$ 的任意连续子序列，求 $\sum F(X)$**

------------

### 分析
易知 $F(X)$ 为对应位置不相等的数量，考虑 $(i, j)$ 对答案的供献。

$\sum F(X) = \sum\limits_{1\, \le \, i \,< \, j\, \le \, n }[a_i \ne a_j] \cdot \min(i, n - j + 1)$

时间复杂度 $O(n^2)$。

------------

### 优化
考虑优化，从中间开始枚举 $i, j(i < j)$， 则 $i = n-j+1$，记每个数出现的次数为 $s_x$， 则 $i$ 对答案的贡献为 $(j - i + 1 - s_{a_i}) \times i$，$j$ 对答案的贡献为 $(j - i + 1 - s_{a_j}) \times i$， 再减去 $(i, j)$ 对答案的贡献 $[a_i \ne a_j] \cdot i$ 即可。

- 一个小细节，当 $n$ 为奇数时， 要加上含 $a_n$ 的连续子序列的贡献。

时间复杂度 $O(n)$。

------------

### 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

long long n, a[200010], s[200010], s2[200010], ans;

int main(){
  cin >> n;
  for(int i = 1; i <= n; i++){
    cin >> a[i];
  }
  for(int i = n / 2, j = i + 1; i && j <= n; j++, i--){
    s[a[j]]++, s[a[i]]++;
    ans += (j - i + 1 - s[a[i]]) * i + (j - i + 1 - s[a[j]]) * i 
        + (n % 2) * (j - i - s[a[j]] + (a[i] == a[j])) - (a[i] != a[j]) * i;
    					\\特判n为奇数
  }
  if(n % 2) ans += (n - s[a[n]] - 1); \\特判n为奇数
  cout << ans;
  return 0;
}

```

------------



---

## 作者：3580_YY (赞：1)

### 算法分析
数学 + 双指针。

如果一个数对 $(nums_1, nums_r)$  是不相同的，那它们中心对称的子数组有   $\min (l, n-r+1)$  个，也是这 个数对所造成的影响（对答案的贡献）

解释:
```
1 2 3 4 5 6
```
如上述数组 $3$ 和 $5$ 是不同的，它们两个中心对称的最大子数组就是
```
1 (2 3 4 5 6)
```

最小子数组是
```
1 2 (3 4 5) 6
```
理论上我们找到所有这样的数对就可以求出答案，但是找到这些数对需要双重循环遍历，时间复杂度是  $O\left(n^{2}\right)$  的，会超时。

因此可以求出补集，用总数对的贡献减去好数对的贡献，就能得到坏数对的贡献。假设 $nums_1$  包括自己， 左边一共有  $x=l$  个元素， $nums_r$ 包括自己，右边一共有  $y=n-r+1$  个元素。

1. 在  $x<y$  的情况下，此时  $r$  往左移动到  $l+1$  都能满足  $x<y$   (一共有  $r-l$  个位置满足条件)，这也就意味着  $l$  产生的 贡献为  $x \times(r-l)$。

2. 在  $x \geq y$  的情况下，此时  $l$  往右移动到  $r-1$  也都能满足  $x \geq y$，这也意味着 $r$  产生的贡献为  $y \times(r-l)$。

接下来用一个哈希表存储每个数值的位置，遍历每个数值的位置数组，用上述同样的双指针算法计算好数对 的贡献即可。

### 复杂度分析
计算总数对数量时，对整个数组使用一次相对双指针算法，时间复杂度为   $O(n)$；在计算好数对数量时，遍历数组中的所有相同数字，每种数字都是用一次相对双指针算法，总体的时间复杂度也是  $O(n)$，因此算法的时间复杂度就是  $O(n)$。

开辟了一个哈寿表存储每种数值的索引位置，每个数字都有一个位置，因此额外空间复杂度为  $O(n)$。

---

## 作者：VitrelosTia (赞：0)

看不太懂大家写的代码啊。

首先正难则反，先钦定每个子串都要暴力变，这样答案是 $\sum_{i=1}^{n} (n-i+1) \times \lfloor \dfrac n 2 \rfloor$，含义是对于长度为 $i$ 的 $n - i + 1$ 个串，暴力变一半。然后我们看什么情况下可以使这个东西不需要变这么多，是有相同数字的情况。考虑对于两个相同数字**在原数组中的位置** $(x, y)$，假设 $x < y$，那么答案可以减去 $\min(x, n - y + 1)$，含义是这个数对被包含的时候到左右端点距离得相等，应该比较显然。那么我们可以考虑枚举对于一种数字的两个位置 $x', y'$，（后面带 $'$ 的指的是在一个**颜色中的下标**，映射原数组中的位置）就有一个暴力。

```cpp
cin >> n;
for (int i = 1; i <= n; i++) cin >> a[i], v[a[i]].push_back(i);
int ans = 0; for (int i = 1; i <= n; i++) ans += (n - i + 1) * (i / 2);
for (int i = 1, m; m = v[i].size(), i <= n; i++) if (m > 1) for (int x = 0; x < m - 1; x++)
	for (int y = x + 1; y < m; y++) ans -= min(v[i][x], n - v[i][y] + 1);
cout << ans;
```

但是这样太慢了，得优化。发现 $\min$ 里面的两个东西单调性明显，$x$ 是单增的，$n - y + 1$ 是单减的，那你就容易想到维护一个 $y'$ 的指针往左移动，每次移动到当前的最右边的使得 $x < n - y + 1$ 的位置，假设是 $q$，那么在区间 $[x' + 1, m]$ 中，$[x' + 1, y']$ 每个位置对答案贡献是 $x$，总和是 $(y' - x') \times x$；$[y' + 1, m]$ 每个位置对答案贡献是 $n - y + 1$，总和是 $\sum_{y'+1}^{m}n-y+1$，这个可以后缀和算出来。这样由于你的指针一直往左移动，那么复杂度就可以均摊到 $O(n)$。大家可以仔细思考一下 $y’$ 指针的移动，非常有启发性。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define test cerr << "test\n"
#define print(x) cerr << #x << " = " << x << '\n'

const int N = 2e5 + 5;
int n, a[N]; 
vector <int> v[N], sum[N];

signed main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], v[a[i]].push_back(i);
	for (int i = 1, m; m = v[i].size(), i <= n; i++) if (m > 1) {
		sum[i].resize(m + 1); sum[i][m] = 0;
		for (int j = m - 1; j >= 0; j--) sum[i][j] = sum[i][j + 1] + n - v[i][j] + 1;
	}
	int ans = 0; for (int i = 1; i <= n; i++) ans += (n - i + 1) * (i / 2);
	for (int i = 1, m; m = v[i].size(), i <= n; i++) if (m > 1) for (int x = 0, y = m - 1; x < m - 1; x++) {
		while (v[i][x] >= n - v[i][y] + 1 && y >= 0) y--;
		ans -= max(y - x, 0ll) * v[i][x]; if (y + 1 != m) ans -= sum[i][max(y + 1, x + 1)];
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Claire0918 (赞：0)

先对于一个 $\{a_i\}$，考虑 $f(a_i)$ 的值。

不难发现 $\displaystyle f(a_i) = \sum_{i = 1}^{\lfloor \frac{|\{a_i\}|}{2} \rfloor} [a_i \neq a_{n - i + 1}]$，最优性和可行性是容易证明的。

回到题目，我们对于一个确定的点 $i$，找到满足 $j > i, a_i \neq a_j$ 的 $j$，则 $(i, j)$ 对答案的贡献为 $i$ 到子串左端点距离等于 $j$ 到子串右端点距离相等的子串数量，这容易转化为 $\min\{i, n - j + 1\}$。我们于是得到答案的表示
$$
\sum_{i = 1}^{n} \sum_{j = i + 1}^{n} [a_i \neq a_j] \times \min\{i, n - j + 1\}
$$
直接求值是 $\mathcal{O}(n^2)$ 的。我们考虑转化。

我们注意到 $[p] = 1 - [\neg p]$，所以 $[a_i \neq a_j] = 1 - [a_i = a_j]$，从而
$$
\begin{aligned}
\sum_{i = 1}^{n} \sum_{j = i + 1}^{n} [a_i \neq a_j] \times \min\{i, n - j + 1\}
&= \sum_{i = 1}^{n} \sum_{j = i + 1}^{n} (1 - [a_i = a_j]) \times \min\{i, n - j + 1\}\\
&= \sum_{i = 1}^{n} \sum_{j = i + 1}^{n} \min\{i, n - j + 1\} - \sum_{i = 1}^{n} \sum_{j = i + 1}^{n} [a_i = a_j] \times \min\{i, n - j + 1\}
\end{aligned}
$$
我们回顾一个重要的事实
$$
\min\{a, b\} = 
\begin{cases}
a & a < b\\
b & \text{otherwise}\\
\end{cases}
$$
考虑求式子第一项，我们有
$$
\sum_{i = 1}^{n} \sum_{j = i + 1}^{n} \min\{i, n - j + 1\} = \sum_{i = 1}^{n} \sum_{j = i + 1}^{n}
\begin{cases}
i & i < n - j + 1\\
n - j + 1 & \text{otherwise}
\end{cases}
$$

大括号的值取 $n - j + 1$ 的条件是 $i \geq n - j + 1$，即 $j \geq n - i + 1$。从而
$$
\begin{aligned}\sum_{i = 1}^{n} \sum_{j = i + 1}^{n} \begin{cases}
i & i < n - j + 1\\
n - j + 1 & \text{otherwise}
\end{cases}
&= \sum_{i = 1}^{n} (\sum_{j = i + 1}^{n - i} i + \sum_{j = \max\{i + 1, n - i + 1\}}^{n} n - j + 1)\\
&= \sum_{i = 1}^{n} (\max\{0, n - 2i\} \times i + \sum_{j = 1}^{\min\{n - i, i\}} j)\\
&= \sum_{i = 1}^{n} (\max\{0, n - 2i\} \times i + \frac{\min\{n - i, i\}(\min\{n - i, i\} + 1)}{2})\\
\end{aligned}
$$
这是可以 $\mathcal{O}(n)$ 求得的。

再计算式子的第二项。这项是和 $\{a_i\}$ 有关的，故不能直接数学推导。我们考虑对于一个 $j$，计算所有 $i < j, a_i = a_j$ 的 $i$ 的贡献。

分类讨论 $i < n - j + 1$ 和 $i \geq n - j + 1$。

我们对于每一个 $a_i$ 的值维护一个栈，表示对答案作其自身贡献的 $i$（换而言之，即是对于当前的 $j$，有 $\min\{i, n - j + 1\} = i$ 的 $i$）。显然一个栈中是单调递增的。

如果对于当前 $j$，栈顶的 $i$ 已经使得 $i \geq n - j + 1$，那么 $i$ 不再能作其自身的贡献，而将在后面作 $n - j + 1$ 的贡献。这是因为 $n - j + 1$ 随 $j$ 的增大而越来越小，从而 $i$ 一直不能作自身的贡献。因此，我们将 $i$ 从栈中弹出。

我们分别维护当前确定作 $n - j + 1$ 贡献的位置的数量 $c$ 和栈中数的总和 $s$。每次到达 $j$ 位置时，第二项的值加上 $c \times (n - j + 1) + s$，并且将 $j$ 压入 $a_j$ 对应的栈中，该栈的总和加上 $a_j$。

每个位置会且仅会入栈一次，故这一段的复杂度仍然是 $\mathcal{O}(n)$。

总的复杂是 $\mathcal{O}(n)$，注意第二项前是负号。

在实现中，我们使用较为安全的 `vector` 而不是 `stack` 实现栈。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxa = 2e5 + 10;

int n;
long long res = 0;
long long sum[maxa], cnt[maxa];
vector<int> pos[maxa];

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        const long long sup = min(i, n - i);
        res += max(0, n - (i << 1)) * (long long)i + (sup * (sup + 1) >> 1);
    }
    for (int i = 1; i <= n; i++){
        int a;
        scanf("%d", &a);
        while (!pos[a].empty() && pos[a][pos[a].size() - 1] >= n - i + 1){
            sum[a] -= pos[a][pos[a].size() - 1];
            pos[a].pop_back();
            cnt[a]++;
        }
        res -= cnt[a] * (n - i + 1) + sum[a];
        pos[a].push_back(i);
        sum[a] += i;
    }
    printf("%lld", res);

return 0;
}
```

---

## 作者：N_Position (赞：0)

# AT_abc290_e
## 分析
我们先假设对于 $A$ 的所有的字序列 $B$ 都不是回文序列，再减去 $B_i=B_{n-i+1}$ 的数量，其中 $n$ 是 $B$ 的长度。

### 步骤一

如果所有的子序列都不是回文串，那么，答案显然为 $\sum_{i=1}^N\sum_{j=i+1}^N\lfloor \frac{j-i+1}{2}\rfloor$。

考虑如何 $O(N)$ 求解这个式子。

发现若 $i$ 已经确定，那么 $\sum_{j=i+1}^N\lfloor \frac{j-i+1}{2}\rfloor$ 其实就是两个首项为 $1$，公差为 $1$ 的等差数列之和。

其中这两个等差数列的长度分别为 $\lceil\frac{N-i}{2}\rceil$ 和 $\lfloor\frac{N-i}{2}\rfloor$。

根据求和公式，容易求得两个等差数列的和，我们将其记作 $s_{i,1}$ 和 $s_{i,2}$。计算每一个 $s_{i,j}$ 的时间复杂度为 $O(1)$。

所以答案就是 $\sum_{i=1}^{N}(s_{i_1}+s_{i,2})$，可以在 $O(N)$ 的时间内求得。

### 步骤二
当所有 $A_i$ 都相等时，求相同部分暴力的复杂度是 $O(N^2)$ 的，不能接受。

考虑双指针。

设 $v_{i,j}$ 表示数列 $A$ 中第 $j$ 个 $i$ 的位置，其中 $j\in[l,r]$。

若 $v_{i,l} < n-v_{i,r}+1$，我们可以发现，对于 $\forall j\in(l,r)$，$(l,j)$ 影响到的区间数量与 $(l,r)$ 影响到的区间数量相等。一并计算即可，此时所有的 $(l,i)$ 都已经计算完毕，所以令 $l$ 变为 $l+1$ 即可。

$v_{i,l} \geq n-v_{i,r}+1$ 的情况同理。

## 代码实现
关键代码（步骤二）如下：
```cpp
for(int i=1;i<=n;i++){
	if(v[i].size() < 2){
		continue;
	}
	int l = 0,r = v[i].size()-1;
	while(l < r){
		int a = v[i][l];
		int b = v[i][r];
		if(a < n-b+1){
			ans -= 1ll * (r-l) * a;
			l ++;
		}else{
			ans -= 1ll * (r-l) * (n-b+1);
			r --;
		}
	}
}
```
[完整代码](https://atcoder.jp/contests/abc290/submissions/52379922)

---

## 作者：郑朝曦zzx (赞：0)

## 题目讲解

观察数据特征 $1 \le A_i \le N$，这种套路见多了，很容易想到开桶。

由于直接统计不好统计，我们考虑能节省多少操作。

- 操作总数：区间长度的一半除以二向下取整的总和。

```cpp
F(i, 1, n) ans += (LL)(n + 1ll - i) * (LL)(i >> 1);
```
- 节省的操作数

考虑某一个区间从 $l$ 到 $r$ 能节省多少操作，答案应该是这个区间能像两边“延长”的距离，即 $\min(l, n + 1 - r)$。

还有一个问题需要考虑，就是有多个相同的数怎么办，例如：

```latex
1 2 1 3 1
```

处理第一个和第三个 $1$ 的时候，我们发现由于它们中间还有 $1$，我们能节省超过 $1$ 个，而是两个即 $p_r - p_l$ 其中 $p_x$ 表示这是第几个重复的数，但是如何保证计算不重复呢？

- 循环顺序

由于可能出现多个相同的数，我们不能重复计算，这里采用双指针即可解决问题。

这里我们有必要进一步解释 $p_r - p_l$，其中包括 $p_l$ 和 $p_r$ 匹配的一个，和 $p_l$ 或 $p_r$ （取决于指针更新的方向）和中间匹配的 $p_r - p_l - 1$ 个。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define F(i, a, b) for (int i = (a); i <= (b); ++i)
typedef long long LL;
const int mxn = 200010;
vector <int> pos[mxn];
inline int rd()
{
    char c=getchar(); int x=0, s=1;
    while(c<'0'||c>'9') { if(c=='-')s=-1;c=getchar();}
    while(c>='0'&&c<='9') { x=(x<<3)+(x<<1)+c-'0';c=getchar();}
    return x*s;
}
LL ans;
int n;
int main()
{
	n = rd();
	F(i, 1, n) pos[rd()].push_back(i);
	F(i, 1, n) ans += (LL)(n + 1ll - i) * (LL)(i >> 1);
	F(i, 1, n)
	{
		int l = 0, r = pos[i].size() - 1;
		while (l < r)
		{
			if (pos[i][l] < (n + 1 - pos[i][r]))
				ans -= (LL)(r - l) * (LL)pos[i][l++];
			else ans -= (LL)(r - l) * (n + 1 - pos[i][r--]);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```


---

## 作者：FReQuenter (赞：0)

考虑每一对不相同的字符会使每个包含它们的原字符串连续子序列的贡献加 $1$。

所以，可以对每一对不相同的字符对答案的贡献进行统计从而解题。

但是，不相同的字符对数很多，不好统计。

想到“正难则反”，可以先统计一共有多少对字符串（假设它们都不相同）对答案有多少贡献减去所有相同字符对的贡献就能获得答案。

那么如何统计？不难发现，设一对字符的下标位置为 $(x,y)$，则贡献为包含它们的所有回文串：$\min(x,n+1-y)$。

那么对于所有 $A_i$ 的值，我们把它们的位置记录下来，然后对于每一个值对应的位置（存入数组 $B$）$\sum_{i=1}^{|B|-1}\sum_{j=i+1}^{|B|}\min(B_i,n+1-B_j)$ 求和即为所有两两相同字符对的贡献之和。

然后发现当当前计算区间 $[l,r]$ 在 $B_l<n+1-B_r$ 时，对于所有位置对 $(x,y)=(l,l+1),(l,l+2),\cdots,(l,r)$ 贡献为 $(r-l)\times B_i$，并使得 $l=l+1$。反之，对于所有位置对 $(x,y)=(l,r),(l+1,r),\cdots,(r-1,r)$ 贡献为 $(r-l)\times (N+1-B_r)$，并使得 $r=r-1$。

然后就做完了。$\color{white}{\text{膜拜YZB巨佬！TA吊打我！TQL！}}$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<int> gv[200005];
int n,ans,sum,a[200005];
signed main(){
  cin>>n;
  for(int i=1;i<=n;i++) cin>>a[i],gv[a[i]].push_back(i);
  for(int i=1;i<=n;i++){
    sum+=(n+1-i)*(i/2);
    int l=0,r=(int)gv[i].size()-1;
    while(l<r){
      if(gv[i][l]<(n+1-gv[i][r])) ans+=(r-l)*gv[i][l],l++;
      else ans+=(r-l)*(n+1-gv[i][r]),r--;
    }
  }
  cout<<sum-ans;
}
```

---

## 作者：lsj2009 (赞：0)

## Solution

先考虑暴力。考虑对于一个字符串他需要修改几个字符才能使得其回文，那么显然，每个字符都是开头结尾一一对应的，如果这两个字符不同，那就需要改其中一个，贡献加一；如果相同，则不需要。

那么我们自然地想到，可以计算每一个字符对于全局的贡献，即确定一个 $i$，去考虑一个 $j$ 可以和他配对且 $s_i\neq s_j$，设有 $a_{i,j}$ 个字符串可以让他们配对，则答案即为 $\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [s_i\neq s_j]\times a_{i,j}$。接下来考虑计算 $a_{i,j}$，我们不妨以他们两个先为一个字符串的开头和结尾，显然他们两个配对，然后接下来分别向左向右扩展，显然依旧配对，而且有且仅有这种情况配对，则得到共可以拓展 $\min\{i,n-j+1\}$ 个，所以答案 $=\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n [s_i\neq s_j]\times \min\{i,n-j+1\}$。

最后的问题就是如何 $\Theta(n)$ 或 $\Theta(n\log n)$ 去计算他。

首先我们把他拆成 $(\sum\limits_{i}\sum\limits_j [s_i\neq s_j]\times i)+(\sum\limits_{i}\sum\limits_j [s_i\neq s_j]\times (n-j+1))$，然后去解不等式计算前后 $i,j$ 的取值范围，可以得到：前者为 $i<j<n+1-i$，后者为 $\max\{i,n-i\}<j$，然后；类似地把后者再拆一下。接下来我们就可以用常用的类似于换根 dp 的方法开个桶（下标为值域）计算偏差（再挪动时加减），设 $t_i$ 为所有 $s_j=i$ 的贡献，则通过容斥原理可计算，最后求和。

然后就做完了。

## Code

正解：<https://atcoder.jp/contests/abc290/submissions/39037891>。

---

## 作者：lingfunny (赞：0)

感觉做复杂了，但不会更简单的做法。

显然对于两个下标 $i, j~(i<j)$，如果 $a_i\neq a_j$，则会对所有 $(i, j)$ 形成匹配的回文串造成 $1$ 的贡献。总共就是 $\min(i, n - j + 1)$ 的贡献。

但是 $a_i\neq a_j$ 要枚举 $O(n^2)$ 种下标，于是考虑枚举 $a_i = a_j$，然后扣掉贡献。

于是对于一个 $A_v = \{i\mid a_i = v\}$，集合内部排序后，考虑一个下标 $i$ 的贡献：对于 $n-j+1\ge i$，贡献为 $i$，对于 $n-j+1<i$，贡献为 $n-j+1$。

前面的比较平凡，count 一下就好了，后面的不平凡。但会发现，随着 $i$ 往右移动，$n - j + 1 < i$ 会更宽松，则 $j$ 会往左移。

于是拿双指针维护，记 $c[i]$ 为序列中第 $i$ 个 $v$ 出现的位置，$m=\vert A_v\vert$：

```cpp
int r = m;
LL sum = 0;	// 维护合法 j 的 n - j + 1 的和
for (i = 1; i <= r; ++i) {
	while (r > i && n - c[r] + 1 < c[i]) sum += n - c[r--] + 1;
	ans -= sum + (LL)(r - i) * c[i];	// r - i 即为 n - j + 1 >= i 的 j 的数量
}
```

到 $i > r$ 还没结束，只是后面的 $i$ 一定满足 $n - j + 1 < i$ 了，少了前半部分贡献。还要继续计算下去：

```cpp
for (; i <= m; ++i) {
	while (r + 1 <= i) sum -= n - c[++r] + 1;
	ans -= sum;
}
```

目前扣掉了不合法的，另一个问题是所有的贡献怎么算：

$$
\sum_{i=1}^n\sum_{j=i + 1}^n \min(i, n - j+1)
$$

朴素算是 $O(n^2)$ 的，寄了。

对 $\min$ 的取值分类讨论，会得到 $j$ 的取值范围，乘一下就好了。

总时间复杂度 $O(n)$。
```cpp
// Problem: E - Make it Palindrome
// URL: https://atcoder.jp/contests/abc290/tasks/abc290_e
// Group: AtCoder - Toyota Programming Contest 2023 Spring Qual B（AtCoder Beginner Contest 290）
// Time: 2023-02-19 21:24
// Author: lingfunny

#include <bits/stdc++.h>
using LL = long long;
using uint = unsigned;
using namespace std;
const int mxn = 2e5 + 10;

int n, a[mxn], c[mxn], m;
vector<int> all[mxn];
LL ans;
LL S(LL n) { return n * (n + 1) >> 1; }

signed main() {
	scanf("%d", &n);
	for (int i = 1, x; i <= n; ++i) scanf("%d", &x), all[x].push_back(i);
	for (int i = 1; i <= n; ++i)
		if ((int)all[i].size() > 1) {
			for (m = 0; int x : all[i]) c[++m] = x;
			int r = m, i;
			LL sum = 0;
			for (i = 1; i <= r; ++i) {
				while (r > i && n - c[r] + 1 < c[i]) sum += n - c[r--] + 1;
				ans -= sum + (LL)(r - i) * c[i];
			}
			for (; i <= m; ++i) {
				while (r + 1 <= i) sum -= n - c[++r] + 1;
				ans -= sum;
			}
		}
	for (int i = 1; i <= n; ++i) {
		int l = i + 1, r = n - i + 1;
		if (l <= r) ans += 1ll * i * (r - l + 1);
		l = max(n - i + 1, i) + 1, r = n;
		if (l <= r) ans += 1ll * (n + 1) * (r - l + 1), ans -= S(r) - S(l - 1);
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：honglan0301 (赞：0)

## 题意简述
定义一个字符串的权值为使其变为回文串的最小修改次数。给出长为 $n\ (n\leq2\times 10^5)$ 的字符串 $s_i$, 求其所有连续子串的权值和。

## 题目分析
根据定义得出一个串 $s_1,\cdots,s_n$ 的权值为 $\sum_{i=1}^{i\leq \lfloor{n\over 2}\rfloor} {[s_i ≠s_{n+1-i}]}$。那么对于一对 $s_i,s_j\ (i<j)$, 它们所贡献的次数即为使它们配对的串的个数，容易发现这样的串形如 $s_{i-k},\cdots,s_{j+k}\ (k∈N)$, 故串的个数为 $\min(i,n+1-j)$, 答案 $ans=\sum_{i,j=1}^n [s_i≠s_j]\times\min(i,n+1-j)$。

这样做是 $O(n^2)$ 的，我们考虑优化。从反面考虑，我们只需要算出并减去 $\sum_{i,j=1}^n [s_i=s_j]\times\min(i,n+1-j)$ 的结果就行。于是我们使用权值线段树，对于每个数 $x$, 找出所有满足 $s_i=x$ 的 $i$, 从左至右依次计算每个 $s_i$ 与左边数造成的贡献，并将 $i$ 加入权值线段树中即可。具体地，记 $c(l,r)$ 表示线段树中区间 $(l,r)$ 数的个数， $s(l,r)$ 表示区间 $(l,r)$ 的数之和，每个 $s_i$ 造成的贡献即为 $c(n+1-i,n)\times(n+1-i)+s(1,n-i)$, 原因可根据前面的 $\min$ 自己想。

时间复杂度取决于线段树的插入与查询次数，为 $O(n\log n)$, 可以通过本题。

## 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
#define int long long

int n,a[200005],ans;
vector <int> v[200005];

struct tree
{
	int num,sum;
}tree[800005];

#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define n(x) tree[x].num
#define m(x) tree[x].sum
#define md(x,y) ((x+y)>>1)
#define push_up(x) {n(x)=n(ls(x))+n(rs(x));m(x)=m(ls(x))+m(rs(x));}

void add(int l,int r,int x,int k,int p)
{
	if(l==r) {n(p)+=k; m(p)+=l*k; return;}
	int mid=md(l,r);
	if(mid>=x) add(l,mid,x,k,ls(p)); else add(mid+1,r,x,k,rs(p));
	push_up(p);
}

int aska(int l,int r,int x,int y,int p)
{
	if(x>y) return 0;
	if(l>=x&&r<=y) {return n(p);}
	int mid=md(l,r),nans=0;
	if(mid>=x) nans+=aska(l,mid,x,y,ls(p));
	if(mid<y) nans+=aska(mid+1,r,x,y,rs(p));
	return nans;
}
int askb(int l,int r,int x,int y,int p)
{
	if(x>y) return 0;
	if(l>=x&&r<=y) {return m(p);}
	int mid=md(l,r),nans=0;
	if(mid>=x) nans+=askb(l,mid,x,y,ls(p));
	if(mid<y) nans+=askb(mid+1,r,x,y,rs(p));
	return nans;
}

signed main()
{
	cin>>n; for(int i=1;i<=n;i++) {cin>>a[i]; v[a[i]].push_back(i);}
	for(int i=1;i<=n;i++)
	{
		ans+=aska(1,n,n-i+1,n,1)*(n-i+1)+askb(1,n,1,n-i,1);
		add(1,n,i,1,1);
	}
	for(int i=1;i<=n;i++) add(1,n,i,-1,1);
	for(int i=1;i<=n;i++)
	{
		for(auto j:v[i])
		{
			ans-=aska(1,n,n-j+1,n,1)*(n-j+1)+askb(1,n,1,n-j,1);
			add(1,n,j,1,1);
		}
		for(auto j:v[i]) add(1,n,j,-1,1);
	}
	cout<<ans<<endl;
}
```
感觉赛时码风还不错（

---

