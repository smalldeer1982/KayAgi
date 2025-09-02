# Playing with String

## 题目描述

Two people play the following string game. Initially the players have got some string $ s $ . The players move in turns, the player who cannot make a move loses.

Before the game began, the string is written on a piece of paper, one letter per cell.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305E/e3dc20c8c09e1180ec4786b230762f8e7c79cfda.png)An example of the initial situation at $ s $ = "abacaba"A player's move is the sequence of actions:

1. The player chooses one of the available pieces of paper with some string written on it. Let's denote it is $ t $ . Note that initially, only one piece of paper is available.
2. The player chooses in the string $ t=t_{1}t_{2}...\ t_{|t|} $ character in position $ i $ $ (1<=i<=|t|) $ such that for some positive integer $ l $ $ (0&lt;i-l; i+l<=|t|) $ the following equations hold: $ t_{i-1}=t_{i+1} $ , $ t_{i-2}=t_{i+2} $ , ..., $ t_{i-l}=t_{i+l} $ .
3. Player cuts the cell with the chosen character. As a result of the operation, he gets three new pieces of paper, the first one will contain string $ t_{1}t_{2}...\ t_{i-1} $ , the second one will contain a string consisting of a single character $ t_{i} $ , the third one contains string $ t_{i+1}t_{i+2}...\ t_{|t|} $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF305E/4da2b2c4651d8ec70c1d3e569c51588926a9324c.png)An example of making action $ (i=4) $ with string $ s $ = «abacaba»Your task is to determine the winner provided that both players play optimally well. If the first player wins, find the position of character that is optimal to cut in his first move. If there are multiple positions, print the minimal possible one.

## 说明/提示

In the first sample the first player has multiple winning moves. But the minimum one is to cut the character in position $ 2 $ .

In the second sample the first player has no available moves.

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
First
2
```

## 样例 #2

### 输入

```
abcde
```

### 输出

```
Second
```

# 题解

## 作者：Vsinger_洛天依 (赞：0)

这题题解写了两三遍全死机了。。。一次都没存。

首先刚看到题面我们就有一个很简单的 $O(n^3)$ 的 dp 计算区间 SG 函数的做法，但是哇塞，我们的 $|S|$ 足足有 $5000$，所以 $O(n^3)$ 做法是过不去的说，那就只能优化一下了，只要优化到 $O(n^2)$ 就能做了。

我们发现 $s_{i-1}=s_{i+1}$ 的点比较特殊，两个相邻的这种点删掉一个就会导致另一个也被删除，那么我们只需要提取出所有连续的特殊的点一段一段做即可，容易发现不被特殊点连接的特殊点不会相互影响，此时我们求 SG 函数的 dp 就被转化为了一维的 dp，复杂度 $O(n^2)$ 可以通过。

---

## 作者：MyukiyoMekya (赞：0)

学过 `multi-SG` 的同学应该读完题就会有一个 $\mathcal O(n^3)$ 的大力 dp 算区间 $SG$ 函数的做法，但是 $n$ 挺大，过不去。

仔细分析一下，我们把 $s_{i-1}=s_{i+1}$ 的 $i$ 成为特殊点，如果两个特殊点相邻，那么删掉一个就会使另一个特殊点消失。

如果两个特殊点不相邻且它们之间没有任何特殊点，那它们不会互相影响。

所以在一开始就把每一段连续的特殊点提出来，一段一段做就好了，$SG$ 函数变成 $1$ 维的了，$\mathcal O(n^2)$

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
const int MaxN=5050;
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
int f[MaxN],n;
char s[MaxN];
inline int dfs(int n)
{
	if(n<=0)return 0;
	if(~f[n])return f[n];
	bool vis[MaxN];std::mem(vis,0);
	for(int k=1;k<=n;++k)vis[dfs(k-2)^dfs(n-k-1)]=1;
	f[n]=0;
	while(vis[f[n]])++f[n];
	return f[n];
}
inline int calc(int l,int r)
{
	if(l>r)return 0;
	std::vector<int> dr;
	reg int cnt=0;
	for(int i=l+1;i<r;++i)
		if(s[i-1]==s[i+1])
			++cnt;
		else if(cnt)dr.pb(cnt),cnt=0;
	if(cnt)dr.pb(cnt);
	reg int ans=0;
	for(auto i:dr)ans^=dfs(i);
	return ans;
}
signed main(void)
{
	std::mem(f,-1);
	std::scanf("%s",s+1);
	n=std::strlen(s+1);
	if(!calc(1,n))return std::puts("Second"),0;
	std::puts("First");
	for(int i=1;i<=n;++i)
		if(s[i-1]==s[i+1]&&!(calc(1,i-1)^calc(i+1,n)))
			return write(i),ln,0;
	return 0;
}
```



---

