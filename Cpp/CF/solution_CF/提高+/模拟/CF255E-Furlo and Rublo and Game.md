# Furlo and Rublo and Game

## 题目描述

Furlo and Rublo play a game. The table has $ n $ piles of coins lying on it, the $ i $ -th pile has $ a_{i} $ coins. Furlo and Rublo move in turns, Furlo moves first. In one move you are allowed to:

- choose some pile, let's denote the current number of coins in it as $ x $ ;
- choose some integer $ y $ $ (0<=y&lt;x; x^{1/4}<=y<=x^{1/2}) $ and decrease the number of coins in this pile to $ y $ . In other words, after the described move the pile will have $ y $ coins left.

The player who can't make a move, loses.

Your task is to find out, who wins in the given game if both Furlo and Rublo play optimally well.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
Rublo
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
Rublo
```

## 样例 #3

### 输入

```
10
1 2 3 4 5 6 7 8 9 10
```

### 输出

```
Furlo
```

# 题解

## 作者：__stick (赞：0)

## 题意

给出 n 个数，每次可以将一个数减去 $y,y\in[\sqrt[4]x,\sqrt{x}]$  ，两个人依次取数，不能取则失败，先手是否必胜？

## 思路

简单博弈题，发现每个数是独立的，满足 nim 游戏每个数 SG 函数异或起来是整个游戏 SG 函数值的性质，所以问题就变成了求每个数的 SG 函数。

发现数值很大，大概是 $10^{12}$ 左右，明显不能直接算，但是会发现我们在计算一个数的 SG 函数时只会用到 $\sqrt{x}$ 以下的函数值，所以我们可以预处理出来 $10^6$ 以内的 SG 函数值，超过的就现场计算，但是单次计算每个数 SG 函数的时候复杂度是 $\sqrt{x}$ 的，加一起就炸了，所以考虑优化，具体方法是将输入的数排序，每次从小的算到大的，减去小于 $\sqrt[4]{x}$ 的SG 函数对答案的贡献，加上不大于 $\sqrt{x}$ 但还没有加入计算的贡献，最后求出 mex 即可。

这样最多扫描 $\sqrt{x}+\sqrt[4]{x}$ 次，复杂度就正确了。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
inline bool cmax(T& a,const T& b){return a<b?a=b,1:0;}
template<typename T>
inline bool cmin(T& a,const T& b){return b<a?a=b,1:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define X first
#define Y second
const int MAXN=2e6+10;
const int mod=1e9+7;
int SG[MAXN];
int cnt[20];
void init()
{
	ll a=0,b=0;
	for(int i=1;i<MAXN;i++)
	{
		while(a*a<=i&&a<i)cnt[SG[a++]]++;
		while(b*b*b*b<i)cnt[SG[b++]]--;
		while(cnt[SG[i]])SG[i]++;
	}
}
ll x[MAXN];
int main()
{
	ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int n;cin>>n;
	int ans=0;
	init();
	
	for(int i=1;i<=n;i++)cin>>x[i];
	sort(x+1,x+n+1);
	ll a=0,b=0;
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)
	{
		if(x[i]<MAXN)ans^=SG[x[i]];
		else
		{
			int u=0;
			while(a*a<=x[i]&&a<=x[i])cnt[SG[a++]]++;
			while(b*b*b*b<x[i])cnt[SG[b++]]--;
			while(cnt[u])u++;
			ans^=u;
		}
	}
	if(!ans)cout<<"Rublo";
	else cout<<"Furlo";
	return 0;
}
```


---

