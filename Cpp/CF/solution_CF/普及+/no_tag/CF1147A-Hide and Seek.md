# Hide and Seek

## 题目描述

Alice and Bob are playing a game on a line with $ n $ cells. There are $ n $ cells labeled from $ 1 $ through $ n $ . For each $ i $ from $ 1 $ to $ n-1 $ , cells $ i $ and $ i+1 $ are adjacent.

Alice initially has a token on some cell on the line, and Bob tries to guess where it is.

Bob guesses a sequence of line cell numbers $ x_1, x_2, \ldots, x_k $ in order. In the $ i $ -th question, Bob asks Alice if her token is currently on cell $ x_i $ . That is, Alice can answer either "YES" or "NO" to each Bob's question.

At most one time in this process, before or after answering a question, Alice is allowed to move her token from her current cell to some adjacent cell. Alice acted in such a way that she was able to answer "NO" to all of Bob's questions.

Note that Alice can even move her token before answering the first question or after answering the last question. Alice can also choose to not move at all.

You are given $ n $ and Bob's questions $ x_1, \ldots, x_k $ . You would like to count the number of scenarios that let Alice answer "NO" to all of Bob's questions.

Let $ (a,b) $ denote a scenario where Alice starts at cell $ a $ and ends at cell $ b $ . Two scenarios $ (a_i, b_i) $ and $ (a_j, b_j) $ are different if $ a_i \neq a_j $ or $ b_i \neq b_j $ .

## 说明/提示

The notation $ (i,j) $ denotes a scenario where Alice starts at cell $ i $ and ends at cell $ j $ .

In the first example, the valid scenarios are $ (1, 2), (2, 1), (2, 2), (2, 3), (3, 2), (3, 3), (3, 4), (4, 3), (4, 5) $ . For example, $ (3,4) $ is valid since Alice can start at cell $ 3 $ , stay there for the first three questions, then move to cell $ 4 $ after the last question.

 $ (4,5) $ is valid since Alice can start at cell $ 4 $ , stay there for the first question, the move to cell $ 5 $ for the next two questions. Note that $ (4,5) $ is only counted once, even though there are different questions that Alice can choose to do the move, but remember, we only count each pair of starting and ending positions once.

In the second example, Alice has no valid scenarios.

In the last example, all $ (i,j) $ where $ |i-j| \leq 1 $ except for $ (42, 42) $ are valid scenarios.

## 样例 #1

### 输入

```
5 3
5 1 4
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4 8
1 2 3 4 4 3 2 1
```

### 输出

```
0
```

## 样例 #3

### 输入

```
100000 1
42
```

### 输出

```
299997
```

# 题解

## 作者：流绪 (赞：2)

对于一个代币 他有三种选择:往左移,不动,往右移
那我们枚举每一个单元格,设代币放里面,然后看看三种操作哪几种能够使代币不被发现,就让答案 +1

怎么判断会不会被发现呢,只要移动过去的那一格在询问中最后一次出现早于原本那一格第一次出现就可以了,所以我们只要在枚举前预处理 minn 数组存第一次出现的时间,maxn 数组存最后一次出现的时间,然后就能在接下来的枚举中 O(1) 地判断会不会被发现啦

下面是 AC 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define inf 0x7f7f7f7f
using namespace std;
ll maxn[1000010],minn[1000010];
ll a[1000010];
int main()
{
	ios::sync_with_stdio(false);
	ll n,k;
	cin >> n >> k;
	memset(maxn,-1,sizeof(maxn));
	memset(minn,inf,sizeof(minn));
	for(ll i=1;i<=k;i++)
	{
		cin >> a[i];
		maxn[a[i]] = max(maxn[a[i]],i);
		minn[a[i]] = min(minn[a[i]],i);//记录a[i]号最早被问和最晚被问的时间 
	}	
	ll ans = 0;
	for(int i=1;i<=n;i++)
	{
		if(i<1||i>n)
			continue;
		if(minn[i] > maxn[i-1]&&i>1)
			ans++;
		if(minn[i] > maxn[i+1]&&i<n)
			ans++;
		if(minn[i] > maxn[i])
			ans++;
	}
	cout << ans;
} 
```


---

## 作者：729hao (赞：0)

[**luogu** 传送门](https://www.luogu.com.cn/problem/CF1147A) [**codeforces** 传送门](http://codeforces.com/problemset/problem/1147/A)


---

## 思路
将所有情况分成 $3$ 类：

### 1. 代币自始至终没有动过
显然，只要这个位置没有被问过，放这里一定没有问题。

### 2. 从 $i$ 移到 $i-1$
既然这个操作要保证不被发现，那么这个操作一定要在最后一次询问 $i-1$ 之后，第一次询问 $i$ 之前。

于是记录每一个格子 $i$ 第一次被询问的时间及最后一次被询问的时间。枚举 $i$ ，看 $i$ 与 $i-1$ 是否满足条件。


### 3. 从 $i$ 移到 $i+1$
与第 $2$ 种情况类似，这时操作必须在最后一次询问 $i+1$ 之后，第一次询问 $i$ 之前。

## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace cs{
	#define LL long long
	#define ULL unsigned long long
	#define fir first
	#define sec second
	typedef pair<int,int> PII;
	const int N=1e5;
	const LL INF=LLONG_MAX/3;
	const LL Mod=998244353;
	int n,k,fpos[N+5],lpos[N+5],ans;
	bool Find(int x,int y){
		if(fpos[x]==0||fpos[y]==0)return 1;
		return lpos[y]<=fpos[x];
	}
	int main(){
		ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
		cin>>n>>k;
		int x;
		for(int i=1;i<=k;i++){
			cin>>x;
			if(!fpos[x])fpos[x]=i;
			lpos[x]=i;
		}
		for(int i=1;i<=n;i++){
			if(i!=1){
				if(Find(i,i-1))ans++;
			}
			if(i!=n){
				if(Find(i,i+1))ans++;
			}
			if(fpos[i]==0)ans++;
		}
		cout<<ans;
		return 0;
	}
}
int main(){
	cs::main();
	return 0;
}
```

---

## 作者：Nuclear_Fish_cyq (赞：0)

## 题意简述

你可以在 $n$ 个格子里放一个东西，抓的检查 $k$ 次，每次都看一个格子里有没有这个东西。你有一次操作的机会，可以移动这个东西或者保持位置不变。问有多少种可能使抓的没发现这个东西。

## 思路

注意到 $n\leq10^5$，操作顶多三种，可以直接考虑每种操作可不可行。因为只能操作一次，所以最好的方法就是在要被查到的时候转移到一个已经查完了的地方。所以我们可以维护每个格子什么时候第一次查，什么时候最后一次查。然后我们暴力每一个格子，看往下走（这里要查的时候下面已经查完了），不动（这里就没被查），往上走（这里要查时上面已经查完了）可不可行，最后就能算出答案了。

上代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
//#define mod
//#define range
using namespace std;
int n, k, a, fir[100000], las[100000], ans;

//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> k;
	fill(fir, fir + n, 1000000);//初始化 
	fill(las, las + n, -1);//初始化 
	for(int i = 0; i < k; i++){
		cin >> a;
		a--;//迷惑码风导致的迷惑行为 
		fir[a] = min(fir[a], i);//统计第一次出现 
		las[a] = max(las[a], i);//统计最后一次出现 
	}
	for(int i = 0; i < n; i++){
		if(i != 0 && fir[i] > las[i - 1]){//可以从i逃向i-1 
			ans++;
		}
		if(las[i] == -1){//不用逃 
			ans++; 
		}
		if(i != n - 1 && fir[i] > las[i + 1]){//可以从i逃向i+1 
			ans++;
		}
	} 
	cout << ans << endl;
	return 0;
}

```

---

