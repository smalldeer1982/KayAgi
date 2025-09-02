# [ARC172B] AtCoder Language

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc172/tasks/arc172_b

AtCoder 語には $ L $ 種類の文字があります。 AtCoder 語の文字からなる $ N $ 文字の文字列 $ s $ のうち、以下の条件を満たすものは何通りありますか。 答えを $ 998244353 $ で割った余りを求めてください。

- 文字列 $ s $ のどの「$ K $ 文字の部分列」も異なる。厳密には、文字列 $ s $ から $ K $ 文字を抜き出し、そのままの順序で連結して $ K $ 文字の文字列を得る方法は $ _N\mathrm{C}_K $ 通りあるが、それらすべてが異なる文字列を生成する。
 
 $ _N\mathrm{C}_K $ とは$ N $ 個のものの中から $ K $ 個を選ぶ方法の総数を指します。より厳密には、$ _N\mathrm{C}_K $ は $ N! $ を $ K!\ \times\ (N-K)! $ で割った値です。

## 说明/提示

### 制約

- $ 1\ \leq\ K\ <\ N\ \leq\ 500000 $
- $ 1\ \leq\ L\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

AtCoder 語の $ 1 $ 種類目の文字を `a`、$ 2 $ 種類目の文字を `b` と表すとき、条件を満たす文字列は `abab`、`baba` の $ 2 $ 通りとなります。

### Sample Explanation 2

条件を満たす文字列はおよそ $ 10^{86} $ 通りありますが、ここでは $ 998244353 $ で割った余りである $ 496798269 $ を出力します。

## 样例 #1

### 输入

```
4 3 2```

### 输出

```
2```

## 样例 #2

### 输入

```
100 80 26```

### 输出

```
496798269```

## 样例 #3

### 输入

```
100 1 26```

### 输出

```
0```

## 样例 #4

### 输入

```
500000 172172 503746693```

### 输出

```
869120```

# 题解

## 作者：小超手123 (赞：5)

##### 题意：

判断有多少个长度为 $n$，值域在 $[1,L]$ 的序列使得其任意取出两个长度为 $k$ 的子序列不同。

$n,k \le 5 \times 10^5,L \le 10 ^ 9$。

##### 分析：

**合法序列（命题1）的充要条件为任意两个相同字符的中间隔的字符数量至少为 $n-k$（命题2）**。

证明：

> ##### step 1：若命题二不成立，则命题一不成立
>
> 令 $s_{a}=s_{b}$。
>
> 容易构造 $s_{1},s_{2},\dots,s_{a},s_{b+1},s_{b+2},\dots,s_{n}$  和 $s_{1},s_{2},\dots,s_{a-1},s_{b},s_{b+1},\dots,s_{n}$，这两部分完全相等且当都大于等于 $k$。
>
> ##### step 2：若命题一不成立，则命题二不成立
>
> 记两次提取的子序列分别为 $s_{a_{1}},s_{a_{2}},\dots,s_{a_{k}}$ 和 $s_{b_{1}},s_{b_{2}},\dots,s_{b                                          _{k}}$。
>
> 显然有 $a_{i} \ge i, b_{i} \le n - k + i$。
>
> 所以 $|a_{i} - b_{i}| \le n - k$。

计算是简单的，前 $n-k+1$ 必须互不相同，剩下的位置能选的字符数是一样的。

因此当 $i \le n - k + 1$ 时，第 $i$ 个位置能选的字符数为 $\max(0,l -  i + 1)$。

当 $i > n - k + 1$，第 $i$ 个位置能选的字符数为 $l-(n-k+1)+1$，即 $l-(n-k)$.

时间复杂度为 $O(n)$。

---

## 作者：Register_int (赞：4)

子序列不好刻画，可以尝试转化为同等的充要条件。

考虑一对相同字符 $s_i,s_j$，则 $s_1,s_2,\cdots,s_i,s_{j+1},s_{j+2},\cdots,s_n$ 与 $s_1,s_2,\cdots,s_{i-1},s_j,s_{j+1},\cdots,s_n$ 是经过 $s_i,s_j$ 字符的最长的相等子序列。他们的长度为 $n-|i-j|$，当这个值 $\ge k$ 时就全部挂掉了。所以我们得到了一个等价条件：任意两个相同字符的间距 $|i-j|>n-k$。进一步地，任意 $n-k+1$ 个字符都要互不相同。充分性和必要性都是显然的。

设 $dp_i$ 为前 $i$ 位填的方案数，有转移：

$$dp_i=\max(l-i+1,l-k+1)dp_{i-1}$$

复杂度 $O(n)$。

# Ac 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 10;
const int mod = 998244353;

int n, m, l; ll dp[MAXN];

int main() {
	scanf("%d%d%d", &n, &m, &l), *dp = 1, m = n - m + 1;
	for (int i = 1; i <= n; i++) {
		if (i <= m) dp[i] = dp[i - 1] * (l - i + 1) % mod;
		else dp[i] = dp[i - 1] * (l - m + 1) % mod; 
	}
	printf("%lld", dp[n]);
}
```

---

## 作者：elbissoPtImaerD (赞：3)

换一种形式刻画合法条件。

考虑一个同色点对 $(c_i,c_j)$。

其不会有重复串等价于 $i+n-j<k-1$。

也就是 $j-i>n-k+1$。

也就是任意连续 $n-k+1$ 个不能有同色的。

那答案就是 $\prod\limits_{i=0}^n (i+1-\min(i+1,n-k+1))$。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/arc172/submissions/51437021)

---

## 作者：CYZZ (赞：2)

# [ARC172B](https://www.luogu.com.cn/problem/solution/AT_arc172_b)
第一次做 arc，连 A 都不会，高兴了。
### 思路
观察一下子序列需满足的条件，很强。对于长度为 $K$ 的子序列，可以先固定其中的 $K-1$ 个字符，剩下一个当作限制来用。

例如：先把前 $K-1$ 个固定在最左边，这样 $[K,N]$ 区间内的就不能有重复的数了。或者把 $K-2$ 个固定在最左边，剩下一个放在最右边，这样 $[K-1,N-1]$ 也被限制了。

发现每一个长为 $N-K+1$ 的子区间里都不能有重复的数。最后，类似滑动窗口逐位计算方案即可
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,m,l,mod=998244353;
int main()
{
    scanf("%d%d%d",&n,&k,&l);
    long long ans=1;m=n-k+1;
    for(int i=1;i<=n;i++)
    {
        if(i<=m) ans=ans*max(0,l-i+1)%mod;
        else ans=ans*max(0,l-m+1)%mod;
    }
    printf("%lld",ans);
}
```

---

## 作者：Miss_SGT (赞：2)

一般遇到计数题我都不太会，这次做出来了，写个题解纪念下。

### 题意：
给定 $n,k,L$，求长度为 $n$ 的序列 $a$，满足 $a_i \in [1,L]$ 且任意两个长度为 $k$ 的子序列本质不同（长得不一样）的数量。
### 转化：
对于每一个下标点对 $(i,j)$ 如果 $i<j,a_i = a_j$ 则需满足
$(i-1)+(n-j)+1 < k$。

显然，这是充要的，因为任意一种不合法的情况，总能找到一对 $i,j$ 使得前面和后面公共用一段，中间分别选 $i,j$，构成本质相同的两个子序列。

### 实现：
用小学数学学的方法，先给所有位置定个计算先后顺序，每个位置的方案数就是 $L$ 减去和它不能一样的数量，最后答案为方案数相乘，即

$\displaystyle\prod_{i=1}^{n} (L-min(i-1,n-k))$

代码就几行就不给了。

---

## 作者：XYQ_102 (赞：1)

## B - AtCoder Language

> The AtCoder language has $L$ different characters. How many $N$-character strings $s$ consisting of characters in the AtCoder language satisfy the following condition? Find the count modulo $998244353$.
> 
> +   All $K$-character subsequences of the string $s$ are different. More precisely, there are $_N\mathrm{C}_K$ ways to obtain a $K$-character string by extracting $K$ characters from the string $s$ and concatenating them without changing the order, and all of these ways must generate different strings.
> 
> What is $_N\mathrm{C}_K$?$_N\mathrm{C}_K$ refers to the total number of ways to choose $K$ from $N$ items. More precisely, $_N\mathrm{C}_K$ is the value of $N!$ divided by $K! \times (N-K)!$.
> 
> $1 \le K \lt N \le 500000,1 \le L \le 10^9$

场上小丑一样把自己绕到死胡同里面去了。

首先容易发现对于同一个字母，两次相邻的位置中间至少有 $n-k$ 个字符。于是我们做完了。

现在有两种思路：对于每一个位置的字符，考虑它下一个的位置/考虑转移到它有多少种方案。

如果你选择第二种，你就赢了。

容易发现，对于第一个字符，它有 $L$ 种选法；

而对于第二个，它有 $L-1$ 种选法（因为不能选第一个）；

$\dots $

发现对于第 $i$ 个字符，它不能选的只是在它前面 $n-k$ 个中出现的，而这显然是不重的，

所以第 $i$ 个字符的选法是 $L-\min(i-1,n-k)$。

于是就做完了。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

const int N=1e6+5;
int n,H,W,c[30];
ll S=0;

void calc(int x,ll Sum){
  if(!n) return ;
  for(int i=x;i>=0;i--){
    ll nw=(1ll<<i)*(1ll<<i);
    ll tmp=min(1ll*c[i],Sum/nw);
    Sum-=1ll*nw*tmp,c[i]-=tmp,n-=tmp;
    if(!Sum) break;
  }
}

void sol(){
  cin>>H>>W>>n;
  for(int i=1,x;i<=n;i++) cin>>x,c[x]++,S+=1ll*(1ll<<x)*(1ll<<x);
  if(H>W) swap(H,W);
  for(int i=29;i>=0;i--){
    int len=(1ll<<i),w=W;
    if(len<=H){
      calc(i,1ll*len*len*(w/len));
      w-=1ll*(w/len)*len;
      for(int j=i;j>=0;j--)
        if(w>=(1ll<<j)) calc(j,1ll*len*(1ll<<j)),w-=(1ll<<j);
      H-=len;
    }
  }
  if(!n) cout<<"Yes\n";
  else cout<<"No\n";
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  sol();
  return 0;
}
```

---

## 作者：封禁用户 (赞：1)

## 前言：
竟然有如此水的绿题。

## 思路：

这是一道非常经典的子序列问题。

通过观察子序列所需满足的条件，我们可以发现非常强。当我们对于长度为 $K$ 的子序列，可以先固定其中的 $K−1$ 个字符，剩下的一个当作限制来用。

比如说我们可以把前 $K−1$ 个固定在最左边，这样 $[K,N]$ 区间内的就不会有重复的数。或者说我们可以把 $K-2$ 个固定在最左边，剩下的一个放在最右边，这样 $[K-1,N-1]$ 也会被限制。

这样我们就可以发现每一个长为 $N-K+1$ 的子区间里都不会有重复的数。

最后，输出 $sum$ 即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,m,l,mod=998244353;

int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n >> k >> l;
	long long sum=1;m=n-k+1;
	for(int i=1;i<=n;i++)
	{
		if(i<=m)
		{
			sum=sum*max(0,l-i+1)%mod;
		}
		else
		{
			sum=sum*max(0,l-m+1)%mod;
		}
	}
	cout << sum << endl;
	return 0;
}
``````

---

## 作者：ast123 (赞：1)

~~模拟赛打挂了，写一发题解补偿一下~~

### [洛谷](https://www.luogu.com.cn/problem/AT_arc172_b)
### [Atcoder](https://atcoder.jp/contests/arc172/tasks/arc172_b)
### Part 1 找规律
先考虑一些简单一些的情况，找找规律。

+ $K=1$ 时，这代表满足条件的字符串中每个字符都不同，此时若 $N \leq L$，则答案为 $A_{L}^{N}$，否则为 $0$。
+ $K=2$ 时，可以发现满足条件的字符串中相同的字符只能一首一尾，否则都会有重复的可能，则答案为 $A_{L}^{N-1} \times L$。(确定了前 $N-1$ 个数后，最后一个数随便选。)
+ $K=3$ 时，考虑满足条件的字符串中相等字符的位置。此时设一堆相等字符的位置从小到大分别为 $a,b$。可以发现 $a \geq 3$ 时，前两个数和 $a,b$ 可以构成一组相同的子序列，不满足条件。同理 $b \leq N-2$ 时也不满足条件。

由上面的讨论我们可以发现，$K=1$ 时，两个相等字符之间至少有 $N-1$ 个字符（相当于没有相等字符）；$K=2$ 时，两个相等字符之间只能相隔 $N-2$ 个字符（一头一尾）；$K=3$ 时，两个相等字符之间至少相隔 $N-3$ 个字符。于是可以得出结论，如果满足条件，两个相等字符之间至少相隔 $N-K$ 个字符。因为由 $K=3$ 时的思路，$a,b$ 必须满足 $a < K$，$b > N-K$，当 $a=1,b=N-K+1$ 时，两者正好相隔 $N-K$ 个字符。
### Part 2 考虑实现
接着考虑如何实现。

+ 对于 $i \leq N-K$ 的情况，必须满足之前的字符都不与该位置的字符相同，有 $\max(0,L-(i-1))$ 种方案。
+ 对于 $i > N-K$ 的情况，只需考虑它之前 $N-K$ 个字符的情况，有 $\max(0,L-(N-K))$ 种方案。

可以直接枚举 $[1,N]$，累积结果即可。记得开 long long、取模。
[代码Link](https://www.luogu.com.cn/record/148286759)

---

## 作者：Night_sea_64 (赞：1)

题目中说需要让 $s$ 所有长度为 $k$ 的子序列都不相同。

不难看出，如果两个相同的字符下标分别为 $i,j(1\le i<j\le n)$。那么如果 $j-i\le n-k$ 就不符合要求了。

因为显然可以取出两个子序列，一个是 $s_1\sim s_i,s_{j+1}\sim s_n$ 两个子串组成的，另一个是 $s_1\sim s_{i-1},s_j\sim s_n$ 两个子串组成的。

这两个子序列显然相同，且长度均为 $n+i-j$。所以如果这个长度 $n+i-j\ge k$，即 $j-i\le n-k$ 就不符合要求了。

于是这个条件就转化为一个字符不能和它前面的 $n-k$ 个字符相同。这就非常简单。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,k,l;
long long ans=1;
const int mod=998244353;
int main()
{
  cin>>n>>k>>l;
  if(n-k>l)
  {
    cout<<0<<endl;
    return 0;
  }
  for(int i=1;i<=n;i++)
    ans=ans*(l-min(i-1,n-k))%mod;
  cout<<ans<<endl;
  return 0;
}
```

---

## 作者：bmatrix (赞：1)

[题面](https://www.luogu.com.cn/problem/AT_arc172_b)。

题意：

> 在用一个大小为 $L$ 的字符集构成的所有长为 $N$ 字符串中，有多少个满足所有长为 $K$ 的子序列两两不同。
>
> $1\le K<N\le 5\times 10^5,1\le L\le 10^9$

~~水一发题解~~

注意到，所有长为 $K$ 的子序列两两不同 $\iff$ 所有长为 $N-K+1$ 的子区间均不存在相同字符。因为如果存在一个长为 $N-K+1$ 的子区间存在相同字符，则用剩下的 $K-1$ 个字符和这对相同字符即可构成相同的子序列。

设 $f(i)$ 为 $N=i$ 时的答案，$f(0)=1$。

由于第 $i$ 位不能与前 $\min(i-1,N-K)$ 位相同，因此只有 $L-\min(i-1,N-K)$ 种字符可用，$\Theta(n)$ 递推即可。

---

## 作者：WhileTrueRP (赞：0)

### ARC172B

结论：满足题干条件的序列的充要条件为 $\forall s_i=s_j(j>i),j-i\geq n+1-k$。

证明：

必要性：

可以采用反证法，若 $\exists i,j$ 使得 $s_i=s_j,j-i<n+1-k$，则这两个字符与 $[1,i)\cup(j,n]$ 中的字符所构成的两个字符串显然相等。

充分性：

若 $\forall s_i=s_j(j>i),j-i\geq n+1-k$，则任意的字符均不可与其他字符形成相等的字符串，得证。

所以只需要求解符合该要求的字符串个数即可，考虑 $O(N)$  的 DP。对于每一位置 $i$,可以放置的字符种数为 $\max(l-i+1,l-n+k)$，可以 $O(N)$ 求解。关键代码如下：

```cpp
for(int i=1;i<=n;i++){
	ans = 1ll* ans * max(l-i+1,l-(n-k)) % MOD;
}
```

[代码实现](https://atcoder.jp/contests/arc172/submissions/55657944)

---

## 作者：XYQ_102 (赞：0)

## 思路
首先容易发现对于同一个字母，两次相邻的位置中间至少有 $n-k$ 个字符。~~于是我们做完了。~~

现在有两种思路：对于每一个位置的字符，考虑它下一个的位置/考虑转移到它有多少种方案。

容易发现，对于第一个字符，它有 $L$ 种选法；

而对于第二个，它有 $L-1$ 种选法（因为不能选第一个）；

$\cdots$

发现对于第 $i$ 个字符，是在它前面 $n-k$ 个中出现的，所以第 $i$ 个字符的选法是 $L-\min(i-1,n-k)$。

于是就做完了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back

const int N=1e6+5,mod=998244353;
int n,k,l,ans=1;

void sol(){
  cin>>n>>k>>l;
  if(l<n-k) return cout<<"0",void();
  for(int i=1;i<=n;i++){
    if(i<=n-k) ans=1ll*ans*(l-i+1)%mod;
    else ans=1ll*ans*(l-n+k)%mod;
  }
  cout<<ans;
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  sol();
  return 0;
}
```

---

## 作者：incra (赞：0)

### Solution
本题解参考官解，但会更加简洁一点。

模拟样例 $n=4,k=2,l=3$，你会发现字符串 $\texttt{abca}$ 是满足条件的，所以结果字符串中可以存在相同的字符。

设字符串为 $s$，然后随便设两个相同的字符的位置为 $a,b(a<b)$，考虑以下情况：

- $a\ge k$，显然可以构造 $s_1,s_2,\cdots s_{k-1},s_a$ 和 $s_1,s_2,\cdots s_{k-1},s_b$ 相同，不满足条件。

- $a\ge k-1,b\le n - 1$，同理可以构造 $s_1,s_2,\cdots s_{k-2},s_a,s_n$ 和 $s_1,s_2,\cdots s_{k-2},s_b,s_n$ 相同，不满足条件。

- $a\ge k-2,b\le n - 2$，同理可以构造 $s_1,s_2,\cdots s_{k-3},s_a,s_{n-1},s_n$ 和 $s_1,s_2,\cdots s_{k-3},s_b,s_{n-1},s_n$ 相同，不满足条件。

- $\vdots$

- $a\ge k-t,b\le n-t$，可以构造 $s_1,s_2,\cdots,s_{k -t-1},s_a,s_{n-t+1},s_{n-t+2},\cdots,s_n$ 和 $s_1,s_2,\cdots,s_{k -t-1},s_b,s_{n-t+1},s_{n-t+2},\cdots,s_n$ 相同，也不满足条件。

综上，我们可以发现，当 $b-a\le n-k$ 时，一定不满足条件，所以 $b-a>n-k$，所以 $b-a-1\ge n-k$，所以任意两个相邻的字符中间都应有不少于 $n-k$ 的字符。

这样思路就很明确了，我们从头开始往后构造，这里模拟一组样例方便大家思考：（同 AT 官解，这里仅作翻译）

考虑样例 $n=5,k=3,l=26$。

对于第 $1$ 个字符，显然填什么都可以，有 $26$ 种情况。

对于第 $2$ 个字符，显然填的数不能和第 $1$ 个相同，有 $25$ 种情况。

对于第 $3$ 个字符，显然填的数不能和第 $1,2$ 个相同，有 $24$ 种情况。

对于第 $4$ 个字符，显然填的数不能和第 $2,3$ 个相同，有 $24$ 种情况。

对于第 $5$ 个字符，显然填的数不能和第 $3,4$ 个相同，有 $24$ 种情况。

所以有 $26\times 25 \times 24 \times 24 \times 24=8985600$ 种。

对于上面样例，我们可以推出广义的答案计算方法：

对于 $i\le n-k$，第 $i$ 个字符不能和 $s_1,s_2,\cdots,s_{i-1}$ 相同，所以有 $l+1-i$ 种。

对于 $i>n-k$，第 $i$ 个字符不能和 $s_{i-(n-k)},s_{i-k+1},s_{i-1}$ 相同，所以有 $l-(n-k)$ 种。

注意这里下标从 $1$ 开始，简单说一下为什么要加一（蒟蒻很菜，只会很麻烦的方法）：

设第一种情况答案为 $l+x-i$，显然第 $1$ 个位置答案为 $l$，所以 $l+x-1=l$，所以 $x=1$。

注意特判 $l+1-i$ 和 $l-(n-k)$ 不为正整数的情况，此时答案为 $0$。

然后就是我们简单的代码了！
### Code
```
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = in.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = in.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = in.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
const int MOD = 998244353;
LL n,k,l;
int main () {
	cin >> n >> k >> l;
	LL ans = 1;
	for (int i = 1;i <= n;i++) {
		if (i <= n - k) ans *= max (l + 1 - i,0ll);
		else ans *= max (l - (n - k),0ll);
		ans %= MOD;
	}
	cout << ans << endl;
	return 0;
}
```

---

