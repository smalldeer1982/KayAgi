# Omkar and Akmar

## 题目描述

Omkar and Akmar are playing a game on a circular board with $ n $ ( $ 2 \leq n \leq 10^6 $ ) cells. The cells are numbered from $ 1 $ to $ n $ so that for each $ i $ ( $ 1 \leq i \leq n-1 $ ) cell $ i $ is adjacent to cell $ i+1 $ and cell $ 1 $ is adjacent to cell $ n $ . Initially, each cell is empty.

Omkar and Akmar take turns placing either an A or a B on the board, with Akmar going first. The letter must be placed on an empty cell. In addition, the letter cannot be placed adjacent to a cell containing the same letter.

A player loses when it is their turn and there are no more valid moves.

Output the number of possible distinct games where both players play optimally modulo $ 10^9+7 $ . Note that we only consider games where some player has lost and there are no more valid moves.

Two games are considered distinct if the number of turns is different or for some turn, the letter or cell number that the letter is placed on were different.

A move is considered optimal if the move maximizes the player's chance of winning, assuming the other player plays optimally as well. More formally, if the player who has to move has a winning strategy, they have to make a move after which they will still have a winning strategy. If they do not, they can make any move.

## 说明/提示

For the first sample case, the first player has $ 4 $ possible moves. No matter what the first player plays, the second player only has $ 1 $ possible move, so there are $ 4 $ possible games.

## 样例 #1

### 输入

```
2```

### 输出

```
4```

## 样例 #2

### 输入

```
69420```

### 输出

```
629909355```

## 样例 #3

### 输入

```
42069```

### 输出

```
675837193```

# 题解

## 作者：一之濑帆波 (赞：12)

[link](https://codeforces.com/contest/1536/problem/F)

最后停止的局面，连续的空格长度一定不超过 $1$，且去掉空格后的环一定满足相邻两点颜色不同。

由于这是个环，所以可以确定最后的 $A,B$ 数量是相等的，步数是偶数，所以后手必胜。

每个人每时刻任何合法的选择都是最优策略。

考虑枚举最后空格的个数、空格的位置、放置顺序的圆排列数，答案为
$$
n\sum_{i=n\bmod 2}^{\lfloor n/2\rfloor} 2\cdot{n-i\choose i}\cdot(n-i-1)!
$$
注意其中系数 $n$ 是环旋转的方案数，系数 $2$ 是 $A,B$ 交错有两种的可能的排列。

**code**

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

const int P = 1e9 + 7;

int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = (i64) res * a % P;
        a = (i64) a * a % P;
        b >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> fac(n + 1), ifac(n + 1);
    fac[0] = ifac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = (i64) fac[i - 1] * i % P;
    ifac[n] = power(fac[n], P - 2);
    for (int i = n; i > 1; --i)
        ifac[i - 1] = (i64) ifac[i] * i % P;

    auto choose = [&](int x, int y) -> int {
        return (i64) fac[x] * ifac[y] % P * ifac[x - y] % P;
    };

    int ans = 0;
    for (int i = n % 2; i <= n / 2; i += 2)
        ans = (ans + (i64) choose(n - i, i) * 2 * fac[n - i - 1]) % P;
    ans = (i64) ans * n % P;
    std::cout << ans << '\n';
    
    return 0;
}
```

---

## 作者：dead_X (赞：7)

## 前言
哇我 vp 的时候场切了！
## 题意
两个人在一个长度为 $n$ 的环上放黑白棋，每个人在一个空格子里放一个颜色不能与相邻棋子相同的棋子，问如果两人都采用最优策略，可能的游戏过程有多少种。
## $sg$ 函数
我从 $sg$ 函数的角度思考这个问题从而得出第一部分结论。如果您不想看这个又臭又长的过程，请移步“更好的证明”部分。

首先，我们发现，从第一次放棋子开始，棋盘上的状态一定是一段空格接一段字母接一段空格。

然后我们对于每段空格，根据其两段的棋子分为相同和不同两类。

记一个两端棋子相同的 $x$ 个连续空格局面为 $f(x)$，两端棋子不同的 $x$ 个连续空格局面为 $g(x)$，我们的目标即为计算 $sg(f(n-1))$。

由于所有环独立，因此整个局面的 $sg$ 函数即为所有段的 $sg$ 函数的异或和。

于是我们直接暴力计算 $sg$ 值，可以写出如下代码：
## 暴力代码
```cpp
signed main()
{
	for(int i=1; i<=10; ++i)
	{
		set<int> s;
		for(int j=0; j<i; ++j) s.insert(g[j]^g[i-1-j]);
		for(int j=1; j<i-1; ++j) s.insert(f[j]^f[i-1-j]);
		while(s.find(f[i])!=s.end()) ++f[i];
		s.clear();
		for(int j=0; j<i-1; ++j) s.insert(g[j]^f[i-1-j]);
		while(s.find(g[i])!=s.end()) ++g[i];
		printf("%d %d\n",f[i],g[i]);
	}
	return 0;
}
```

这个代码可以在 $O(n^2)$ 的时间复杂度内计算 $sg(f(n))$。
## 结论
我们发现，输出全是 $1,0$！

因此得到一个结论：后手无论怎么走，只要他在能走的时候走一步，他就能赢。

根据输出的规律去证明就不难了，请读者自行证明这个结论。
## 更好的证明
这部分是从官方题解搬的！

考虑最后游戏不能再进行的终止状态，必然是在黑白交替中穿插着几个不连续的空格，那么放的棋子数量一定是偶数，因此后手必胜。
## 简单组合数学
知道这个结论之后我们就可以发现，题目就是叫你算本质不同的游戏过程数量。

不难发现，对于每个终止状态，设它放了 $n$ 个棋子，则有 $n!\times f(n)$ 种本质不同的游戏过程，其中 $f(n)$ 为 $n$ 个棋子的终止状态数。

对于 $f(n)$，我们只要计算中间的空格有多少种放法。这部分可以用插板法解决，最终给出答案式：

$$\sum_{2|i}i!(\binom{i}{n-i}+\binom{i-1}{n-i-1})$$
## 代码
```cpp
//And in that light,I find deliverance.
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=1e9+7;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=t*t%p) if(y&1) res=res*t%p;
	return res;
}
int fac[2000003];
int ifac[2000003];
int C(int n,int m)
{
	if(n<m) return 0;
	return fac[n]*ifac[m]%p*ifac[n-m]%p;
}
int f(int n,int m)
{
	return (C(n,m)+C(n-1,m-1))%p;
}
signed main()
{
	int n=read();
	fac[0]=1,ifac[0]=1;
	for(int i=1; i<=n+5; ++i) 
	fac[i]=fac[i-1]*i%p,ifac[i]=qp(fac[i],p-2);
	int ans=0;
	for(int i=2; i<=n; i+=2)
	{
		ans=(ans+fac[i]*f(i,n-i)%p)%p;
	}
	printf("%lld\n",ans*2%p);
	return 0;
}
```

---

## 作者：SunsetLake (赞：3)

## 思路

首先最后的局面在两两字母间一定不会多于 $1$ 个空格。考虑反证，假设有两个空格，那么有以下两种情况：$\text{A}\_\_ \text{B}$，$\text{A}\_\_ \text{A}$，也就是两边的字母不同，相同。对于第一种，在任意一个空格都可以填一个与他相邻字符不同的字符，对于第二种，填 $\text{B}$ 即可。因此，最后两字母之间一定只有一个空格，并且空格隔开的两字符不同。那么把空格去掉之后，一定是形如 $\text{ABAB\dots B}$ 这样 $\text{A,B}$ 相间的一个排列，并且最后一个字符与第一个不同。那么这个序列长一定为偶数，也就是说最后一步一直都是由后手走，故后手必胜。因此每时每刻，任何人的任何操作都是最优策略。

那么我们就只需要考虑计数了。设最后局面有 $i$ 个空格，满足 $2 \mid n-i$，考虑第 $1$ 格的放置情况：

- 放空格，那么在后面 $n-1$ 个位置中放 $i-1$ 个空格，且两空格不相邻，首尾不能放（相当于只有 $n-3$ 个空格），共 $C_{n-i-1}^{i-1}$ 种放法。
- 不放空格，那么在 $n-1$ 个位置中放 $i$ 个空格，只需满足两两不相邻即可，共 $C_{n-i}^{i}$ 种放法。

对于字符来说，顺序是任意的，并且 $\text {A,B}$ 可以交换，那么这部分答案就是 $2 \times (n-i)!$。

因此，总答案为 $\displaystyle\sum_{i=0,2 \mid n-i}^{n}2\times (n-i)! \times (C_{n-i-1}^{i-1}+C_{n-i}^{i})$。

这里说一下 $n$ 个球取 $m$ 个不相邻的球的方案数怎么算。可以先在 $n-m+1$ 个球中任取 $m$ 个球，就有 $C_{n-m+1}^{m}$ 种选法，然后再另外拿 $m-1$ 个球插到那 $m$ 个球的 $m-1$ 个空位中，这样使得我们原本取出的 $m$ 个球都互不相邻，并且最后总球数为 $n$ 个。不难验证逆向思维得出的情况与正常考虑的情况是一一对应的，故我们可以得到上面的结论。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,k,cnt;
const int mod=1e9+7;
ll fac[1000005],ans,inv[1000005]; 
ll qpow(ll a,ll b){
	ll res=1;
	while(b){
		if(b&1)res=(res*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return res;
}
ll C(int x,int y){
	if(x<y||x<0||y<0)return 0;
	return fac[x]*inv[x-y]%mod*inv[y]%mod;
}
int main(){
	cin>>n;
	fac[0]=1;
	for(ll i=1;i<=n;++i)fac[i]=(fac[i-1]*i)%mod;
	inv[n]=qpow(fac[n],mod-2);
	inv[0]=1;
	for(int i=n-1;i>=1;--i)inv[i]=(inv[i+1]*(ll)(i+1))%mod;
	for(int i=0;i<=n;++i){
		if((n-i)&1)continue;
		ans=(ans+2*fac[n-i]%mod*((C(n-i-1,i-1)+C(n-i,i))%mod))%mod;
	}
	cout<<ans;
	return 0;                      
}
```


---

## 作者：7KByte (赞：2)

结论：无论怎么走后手一定赢。

这应该是这道题中最难想到的。

这里的一定赢是指不用考虑任何策略，都能躺赢（

反证法，假定先手赢了，此时场上有奇数个位置被填了，那么一定存在去掉空格后相邻的两个格子颜色相同，它们之间还能再填至少一个，所以后手必胜。

然后就非常简单了，我们计算最终状态，如果最终状态有 $k$ 个位置被填了，那么有 $k!$ 种方案达到这个状态。

$k$ 一定是偶数，我们枚举 $k$ ，计算有多少种最终状态。

最终状态去掉空格后一定是形如 $AB\cdots AB$ 或者 $BA\cdots BA$ 的长度为 $k$ 的串，一个 $AB$ 中最多只能插入一个空格。

由于是环，讨论一下第一个位置是否为空格。

如果第一个位置不是空格，方案数为 $2\binom{k}{n-k}$ 。

如果第一个位置为空格，方案数为 $2\binom{k-1}{n-k-1}$ 。

这样我们就得到了答案。

$$Ans=2\sum\limits_{1\le i\le \left\lfloor\frac{n}{2}\right\rfloor}(2i)!\binom{2i}{n-2i}+(2i)!\binom{2i-1}{n-2i-1}$$

时间复杂度 $\mathcal{O}(n+\log P)$ 。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 1000005
#define P 1000000007
using namespace std;
int n,fac[N],inv[N];
int Pow(int x,int y){
	int now=1;
	for(;y;y>>=1,x=1LL*x*x%P)if(y&1)now=1LL*now*x%P;
	return now;
}
int C(int x,int y){
	if(x<0||y<0||x<y)return 0;
	return 1LL*fac[x]*inv[y]%P*inv[x-y]%P;
}
// Sharpness V
int main(){
	scanf("%d",&n);fac[0]=1;
	rep(i,1,n)fac[i]=1LL*i*fac[i-1]%P;
	inv[n]=Pow(fac[n],P-2);
	pre(i,n-1,0)inv[i]=1LL*inv[i+1]*(i+1)%P;
	int ans=0;
	rep(i,1,n/2){
		int cur=i*2;
		ans=(ans+2LL*fac[cur]*(C(cur,n-cur)+C(cur-1,n-cur-1)))%P;
	}
	printf("%d\n",ans);
	return 0;
} 
```

---

