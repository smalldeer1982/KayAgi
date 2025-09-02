# Court Blue (Easy Version)

## 题目描述

This is the easy version of the problem. In this version, $ n=m $ and the time limit is lower. You can make hacks only if both versions of the problem are solved.

In the court of the Blue King, Lelle and Flamm are having a performance match. The match consists of several rounds. In each round, either Lelle or Flamm wins.

Let $ W_L $ and $ W_F $ denote the number of wins of Lelle and Flamm, respectively. The Blue King considers a match to be successful if and only if:

- after every round, $ \gcd(W_L,W_F)\le 1 $ ;
- at the end of the match, $ W_L\le n, W_F\le m $ .

Note that $ \gcd(0,x)=\gcd(x,0)=x $ for every non-negative integer $ x $ .

Lelle and Flamm can decide to stop the match whenever they want, and the final score of the performance is $ l \cdot W_L + f \cdot W_F $ .

Please help Lelle and Flamm coordinate their wins and losses such that the performance is successful, and the total score of the performance is maximized.

## 说明/提示

In the first test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Flamm wins, $ \gcd(1,2)=1 $ .
- Flamm wins, $ \gcd(1,3)=1 $ .
- Lelle wins, $ \gcd(2,3)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 2\cdot2+3\cdot5=19 $ .

In the third test case, a possible performance is as follows:

- Flamm wins, $ \gcd(0,1)=1 $ .
- Lelle wins, $ \gcd(1,1)=1 $ .
- Lelle wins, $ \gcd(2,1)=1 $ .
- Lelle wins, $ \gcd(3,1)=1 $ .
- Lelle wins, $ \gcd(4,1)=1 $ .
- Lelle wins, $ \gcd(5,1)=1 $ .
- Flamm wins, $ \gcd(5,2)=1 $ .
- Flamm wins, $ \gcd(5,3)=1 $ .
- Flamm wins, $ \gcd(5,4)=1 $ .
- Lelle and Flamm agree to stop the match.

The final score is $ 5\cdot2+4\cdot2=18 $ . Note that Lelle and Flamm can stop the match even if neither of them has $ n $ wins.

## 样例 #1

### 输入

```
8
3 3 2 5
4 4 1 4
6 6 2 2
7 7 2 3
9 9 9 1
2 2 1 4
5 5 1 4
8 8 6 7```

### 输出

```
19
17
18
33
86
9
24
86```

## 样例 #2

### 输入

```
1
20000000 20000000 1341 331```

### 输出

```
33439999007```

## 样例 #3

### 输入

```
2
1984 1984 19 84
9982 9982 44 35```

### 输出

```
204143
788403```

# 题解

## 作者：COsm0s (赞：1)

结论题。

手模一下很容易想到先跳到 $(a,b)$ 位置，$a,b$ 是最大和第二大的小于 $n$ 的质数。

我们知道，在 $10^7$ 范围内，相邻素数之差很小，所以在跳到 $(a,b)$ 之后，我们在 $(a,b)$ 到 $(n,n)$ 之间暴力枚举判断即可。


```cpp
bool vis[M], q[N][N];
vector<int> p;
void Prime() {
	vis[1] = 1;
	for(int i = 2; i < M; i ++) {
		if(!vis[i]) p.pb(i);
		for(int j = 0; i * p[j] < M && j < p.size(); j ++) {
			vis[i * p[j]] = 1;
			if(i % p[j] == 0) break;
		}
	}
}
void Solve() {
	int n, m, l, f;
	cin >> n >> m >> l >> f;
	int u = *(--upper_bound(p.begin(), p.end(), n));
	int v = *(--lower_bound(p.begin(), p.end(), u));
	int ans = 0;
	if(n <= 16) u = v = 1;
	REP(i, u, n) REP(j, v, i) {	
		q[i - u + 1][j - v + 1] = ((__gcd(i, j) != 1) || (q[i - u][j - v + 1] && q[i - u + 1][j - v]));
		if(!q[i - u + 1][j - v + 1])
			ans = max(ans, max(l * i + f * j, l * j + f * i));
 	}
 	cout << ans << '\n';
}
signed main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	Prime();
	int T = 1;
	cin >> T;
	while (T --) {
		Solve();
	}
	return 0;
}
```

---

## 作者：int08 (赞：0)

## 前言
（表达搞不出 D 错失上分机会的懊悔之情）

幸好搞出了 F1 也上了一些。

## 题意
考虑一个初始为 $(0,0)$ 的点对，每次可以选择一个数加 $1$，但是点对全程要满足：

1. $\gcd(x,y)=1$（我们认为 $gcd(0,x)=x$）

2. $x\le n,y\le m$

现在给定 $l,f$，请合法操作以最大化 $xl+yf$，输出最大值即可。

$n,m\le 2\times 10^7,l,f\le 10^9$，**简单版 $n=m$**。
# Solution

现在我们先打个表，我们发现，比较优的策略是先把数对调到 $(1,p)$（小于等于 $n$ 最大的质数），此时另一个数可以随意到达 $1$ 到 $p-1$。

发现任何路径都肯定要经过这两条线。另外又发现当我到达 $(q,p)$（$q$ 为小于等于 $n$ 次大的质数）的时候，由于一般来说 $2q>n$（较小时候不一定，所以 $n\le 20$ 时候可以直接暴力 BFS）所以顺着走到 $(q,n)$ 都可以。

画个图：

![](https://cdn.luogu.com.cn/upload/image_hosting/0nyvuvxw.png)

那么，答案显然会在蓝色阴影区域内。

实际上呢，你发现蓝色根本不大，直接暴力建一下图跑个 BFS 就行了，通过了 F1。

~~我会说我因为 BFS 写挂了吃了两发吗~~

## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,l,f,T,i,j;
vector<int> prime;
bool np[20080506];
bool vis[2085][2085];
signed main()
{
  	for(i=2;i<=20000000;i++)
	{
    	if(!np[i]) prime.push_back(i);
    	for(int pj:prime)
		{
      		if(i*pj>20000000) break;
      		np[i*pj]=true;
      		if(i%pj==0) break;
    	}
  	}
	cin>>T;
	while(T--)
	{
		cin>>n>>m>>l>>f;
		if(l<f) swap(l,f);
		if(!np[n])
		{
			cout<<n*l+(n-1)*f<<endl;
			continue;
		}
		int fp=*(--lower_bound(prime.begin(),prime.end(),n)),sp=*(--lower_bound(prime.begin(),prime.end(),fp));
		if(n<=16) fp=sp=1;
		int x=n-fp+1,y=n-sp+1;
		cerr<<x<<" "<<y<<" "<<endl;
		for(i=0;i<=x+1;i++)
		{
			for(j=0;j<=y+1;j++)
			{
				if(i==0||i==x+1||j==0||j==y+1||__gcd(fp-1+i,sp-1+j)!=1) vis[i][j]=0;
				else vis[i][j]=1;
			}
		}
		queue<pair<int,int> > q;
		q.push({1,1});
		int ans=0;
		while(!q.empty())
		{
			i=q.front().first,j=q.front().second;q.pop();
			ans=max(ans,(fp-1+i)*l+(sp-1+j)*f);
			if(vis[i+1][j]) vis[i+1][j]=0,q.push({i+1,j});
			if(vis[i][j+1]) vis[i][j+1]=0,q.push({i,j+1});
		}
		cout<<ans<<endl;
	}
}
```
# The End.

---

