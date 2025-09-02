# Min Cost String

## 题目描述

Let's define the cost of a string $ s $ as the number of index pairs $ i $ and $ j $ ( $ 1 \le i < j < |s| $ ) such that $ s_i = s_j $ and $ s_{i+1} = s_{j+1} $ .

You are given two positive integers $ n $ and $ k $ . Among all strings with length $ n $ that contain only the first $ k $ characters of the Latin alphabet, find a string with minimum possible cost. If there are multiple such strings with minimum cost — find any of them.

## 样例 #1

### 输入

```
9 4```

### 输出

```
aabacadbb```

## 样例 #2

### 输入

```
5 1```

### 输出

```
aaaaa```

## 样例 #3

### 输入

```
10 26```

### 输出

```
codeforces```

# 题解

## 作者：Warriors_Cat (赞：10)

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1511D) & [CF 题面传送门](http://codeforces.com/problemset/problem/1511/D)。

题意：

* 定义一个字符串 $s$ 的可爱程度为满足 $1 \le i < j < |s|$ 且 $s_i = s_j$ 且 $s_{i+1}=s_{j+1}$ 的数对 $(i, j)$ 的个数。

* 给定 $n, k$，你要用小写字母表前 $k$ 个字母来组成一个长度为 $n$ 的字符串。由于你不希望这个字符串比你可爱，所以你要让这个字符串的可爱程度最小。请输出这个字符串，多解输出任一均可。

* $n \le 2\times 10^5$，$k \le 26$。

感觉是一个比较简单的构造？（

---

### Solution：

首先，考虑到本质不同的长度为 $2$ 的字符串最多有 $k^2$ 个，所以理论上当 $n \le k^2 + 1$ 的时候是可以做到没有重复的数对。

构造的话仔细想想也是很简单的，比如 $k=5$ 就可以如下构造：

$$\texttt{aabacadaebbcbdbeccdceddeea}$$

如果看不出来的话可以如下分段：

$$\texttt{[aabacadae][bbcbdbe][ccdce][dde][e]a}$$

这样就可以保证没有重复的数对。

那，$n \ge k^2 + 1$ 怎么办？

我们记这 $k^2$ 个本质不同的字符串的出现次数为 $a_1, a_2, a_3, ...a_{k^2}$。

很显然，可爱程度就为：

$$\begin{aligned}\sum_{i=1}^{k^2}\binom{a_i}{2}
&=\sum_{i=1}^{k^2}\dfrac{{a_i}^2-a_i}{2}
\\&=\sum_{i=1}^{k^2}\dfrac{{a_i}^2}{2}-\dfrac{n-1}{2}
\end{aligned}$$

而由均值不等式可知 $\sum\limits_{i=1}^{k^2}{a_i}^2\ge\dfrac{(\sum\limits_{i=1}^na_i)^2}{n}$。所以当 $a_1, a_2,a_3,...a_{k^2}$ 越接近时，可爱程度最小。

那我们直接将先前构造出的字符串给循环一下就行了，这样每次每种字符串个数只会循环地加 $1$。

over，时间复杂度为 $O(n+k^2)$。

---

### Code：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define fi first
#define se second
#define dingyi int mid = l + r >> 1, ls = p << 1, rs = p << 1 | 1
#define y0 y_csyakioi_0
#define y1 y_csyakioi_1
#define rep(i, x, y) for(int i = x; i <= y; ++i)
#define per(i, x, y) for(int i = y; i >= x; --i)
#define repg(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define mpr make_pair
inline int read(){
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ x = x * 10 + (ch ^ 48); ch = getchar(); }
	return x * f;
}
const int N = 200010, M = 30;
int n, k, len; char s[M * M];
inline int num(int x){
	return x % len == 0 ? len : x % len;
} 
inline void mian(){
	n = read(); k = read();
	len = 0;
	rep(j, 1, k){
		s[++len] = j + 'a' - 1;
		rep(i, 1, k - j){
		    s[++len] = j + 'a' - 1;
		    s[++len] = j + i + 'a' - 1;
		}
	}
	rep(i, 1, n) printf("%c", s[num(i)]);
}
int main(){ int qwq = 1; while(qwq--) mian(); return 0; }
/*
fa ff
aabacbdaeafbbcbdbebfccdcecfddedfeeffa
*/
```


---

## 作者：FutaRimeWoawaSete (赞：2)

一道比较送的 D（               

考虑在字符串长超过 $k ^ 2$ 后必然有 cost 产生，所以我们只要把每 $k ^ 2$ 种长为 $2$ 的字符串填满后循环构造就好了。               

简单证明一下为什么是对的：             

- 当 $n \leq k ^ 2$ 时显然是对的，毕竟没有任何 cost ；        

- 当 $k ^ 2 < n ^ 2$ 时，我们考虑每种长为 $2$ 的字符串的贡献。令 $x$ 为该种字符串的出现次数，那么一种长为 $2$ 的字符串的贡献就是 $\frac{x(x - 1)}{2}$ ，我们均匀填充必然会让所有长为 $2$ 的字符串种类的出现次数平均化，如果出现不平均的情况的话就肯定没有平均化得到的 cost 小，所以最后得到的肯定是最小的 cost。

```cpp
#include "bits/stdc++.h"
using namespace std;
int pos[31],n,m;
char c;
int main()
{
	scanf("%d %d",&n,&m);
	int cnt = 0 , pst = 0 , lst = 0;
	while(cnt < n)
	{
		for(int i = 0 ; i < m ; i ++) pos[i] = 0;
		pst = 0;
		lst = 0;
		while(cnt < n && pst < m * m)
		{
			c = lst + 'a';
			cout << c;
			int nums = lst;
			if(pos[pos[lst]] <= m - 1) lst = pos[lst];
			else lst = pos[lst] + 1;
			do 
			{
				pos[nums] ++;
			}while(pos[nums] < m && pos[pos[nums]] >= m - 1);
			cnt ++;
			pst ++;
		}
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[更好的阅读体验](https://www.doittomorrow.xyz/post/cf1511d-min-cost-string-de-ti-jie/)
## 题目大意
现在需要使用从小写字母 $a$ 开始的 $k$ 种字符，构造一个长度为 $n$ 的字符串 $s$，使满足 $i,j\in[1,n-1]，i\neq j$ 且 $a_i=a_j,a_{i+1}=a_{j+1}$ 的数对的数量最少。

其中 $1\le n \le 2\times 10^5,1\le k \le 26$。

## 思路
在使用 $k$ 总字符的情况下，可以构造长度为 $2$ 的字符串的种类为 $\operatorname{A}^2_k$。

但是因为在构造时上一队的字符会和这一对的字符组成以前出现过的字符。

为了避免这个情况，我们可以规定每一对里两个字母 $s_i$ 和 $s_{i+1}$ 满足 $s_i < s_{i+1}$，所以当与上一组组合时就一定会满足 $s_{i-1}>s_i$ 自然就不会出现重复的情况。

因为在如果所有的 $s_i$ 都小于 $s_{i+1}$ 时，我们就会漏掉一种 $s_i=s_{i+1}$ 的情况，所以就需要特别的在每一个 $s_i+1=s_{i+1}$ 的前面添加一个 $s_i$。

因为 $\sum_{i=1}^k 2\times(k-i) +1$

$=\sum_{i=1}^k 2\times k-2\times i+1$

$= 2\times k^2-2\times \frac{k\times (1+k)}{2}+k$

$=2\times k^2 -k-k^2+k$

$=k^2$

所以，使用以上方法构造的没有重复的序列最长为 $k^2$。 

假设第 $i$ 组字符串出现的次数为 $cnt_i$，那么一定满足 $\sum_{i=1}^{k^2} cnt_i$ 是一定的。

代价为 
$$cost=\sum _{i=1}^k \frac{cnt_i^2}{2}-\frac{n-1}{2}$$
要使 $cost$ 最小，那么所有的 $cnt_i$ 应该越相近越小，所以在 $n>k^2$ 的时候就应该将原来长度为 $k^2$ 的字符串在后面进行重复。

直接模拟上面的操作，时间复杂度为 $O(m)$。
## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int n,m,cnt,a[30][30];
void solve(){
	cin>>n>>m;
	while(cnt<n){
		for(int i=0;i<m;i++){
			if(cnt>=n) break;
			putchar('a'+i);
			cnt++;
			for(int j=i+1;j<m;j++){
				if(cnt>=n) break;
				putchar('a'+i);
				cnt++;
				if(cnt>=n) break;
				putchar('a'+j);
				cnt++;
				if(cnt>=n) break;
			}
		}
	}
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int T=1;
	while(T--) solve();
    return 0;
}
```

---

## 作者：zhongcy (赞：1)

[CF Problem](https://codeforces.com/problemset/problem/1511/D)

### Solution

------------

因为不同的长度为 $2$ 的字符串有 $k^2$ 个，所以可以做到当 $n\le k^2+1 $ 时 cost $=0$。

举个例子，当 $k=4$ 时，可以构造 $\texttt{abacada\ bbcbd\ ccd\ a}$ 满足 cost $=0$。

再考虑 $n>k^2+1$ 的情况。记这几个不同的字符串出现次数分别为   $a_1,a_2,\dots,a_{k^2}$。

所以 cost 的值为

$$  \sum\limits_{i=1}^{k^2}\binom{a_i}{2}=\sum\limits_{i=1}^{k^2}\dfrac{{a_i}^2}{2}-\dfrac{n-1}{2} $$

又由均值不等式可得，$a_1,a_2,\dots,a_{k^2}$ 越接近时，cost 越小。所以只用循环字符串即可。


### Code

------------

时间复杂度 $ \mathcal{O}(k^2+n) $。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int n,k,l=0;
	char s[901];
	cin>>n>>k;
	for(int i=1;i<=k;i++)
	{
		s[++l]=i+'a'-1;
		for(int j=i+1;j<=k;j++)
		{
			s[++l]=i+'a'-1;
			s[++l]=j+'a'-1;
		}
	}
	for(int i=1;i<=n;i++)
		cout<<s[i%l==0?l:i%l];
    return 0;
}
```


---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

定义字符串的费用是 $(i,j)$ 的个数满足 $1\leq i\lt j\leq n,s_i=s_j,s_{i+1}=s_{j+1}$。

给定 $n\leq 2\times 10^5$ 和字符集大小 $k(k\leq 26)$，用字母表前 $k$ 个小写字母组成的长度为 $n$ 的字符串中，找任意一种费用最小的字符串。

# 题目思路

字符集大小为 $k$ 的长度为 $2$ 的本质不同的字符串有 $k^2$ 个。对于 $n\leq k^2+1$，我们都可以构造费用为 $0$ 的解。

我们对于 $n\leq k^2+1$ 的，构造一组找一下规律：$\tt{[a,ab,ac,ad][b,bc,bd][c,cd]a}$。

我们不是所有 $k^2$ 个字符串都能放进去，因为可能会导致两个小字符串首尾相接出现重复。

这个例子启发我们，每一组都形如上面，先放自己，然后依次遍历字符集填充，可以构造费用为 $0$ 的解。感性理解一下，我们这里例子保证了单个 $k^2+1$ 长度的费用为 $0$，我们重复几次就很平均，所以看上去是对的。

严格证明一下，设这 $k^2$ 个字符串的出现次数分别为 $a_1,a_2,\cdots a_{k^2}$，那么我们的费用是 $\sum\limits_{i=1}^{k^2} \binom{a_i}{2}=\sum\frac{a_i(a_i-1)}{2}=\sum\frac{a_i^2-a_i}{2}=\frac{\sum a_i^2-a_i}{2}=\frac{\sum a_i^2}{2}-\frac{\sum a_i}{2}=\frac{\sum a_i^2}{2}-\frac{n-1}{2}$。

要是的上面这个式子最小，即最小化 $\sum a_i^2$。你贪心考虑，这个式子最小就是 $a_i$ 全部均摊的情况。那么我们上面给的这个费用为 $0$ 的构造就很平均。所以重复若干次即可。

# 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k;
string s;
int main()
{
    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        s += char(i + 'a');
        for (int j = i + 1; j < k; j++)
            s += char(i + 'a'), s += char(j + 'a');
    }
    for (int i = 0; i < n; i++)
        cout << s[i % s.size()];
    cout << endl;
    return 0;
}
```

---

