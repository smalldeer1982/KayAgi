# Quests

## 题目描述

Monocarp is playing a computer game. In order to level up his character, he can complete quests. There are $ n $ quests in the game, numbered from $ 1 $ to $ n $ .

Monocarp can complete quests according to the following rules:

- the $ 1 $ -st quest is always available for completion;
- the $ i $ -th quest is available for completion if all quests $ j < i $ have been completed at least once.

Note that Monocarp can complete the same quest multiple times.

For each completion, the character gets some amount of experience points:

- for the first completion of the $ i $ -th quest, he gets $ a_i $ experience points;
- for each subsequent completion of the $ i $ -th quest, he gets $ b_i $ experience points.

Monocarp is a very busy person, so he has free time to complete no more than $ k $ quests. Your task is to calculate the maximum possible total experience Monocarp can get if he can complete no more than $ k $ quests.

## 说明/提示

In the first test case, one of the possible quest completion sequences is as follows: $ 1, 1, 2, 3, 2, 4, 4 $ ; its total experience is equal to $ \underline{4} + 1 + \underline{3} + \underline{1} + 1 + \underline{2} + 1 = 13 $ (the underlined numbers correspond to the instances when we complete a quest for the first time).

In the second test case, one of the possible quest completion sequences is as follows: $ 1, 1 $ ; its total experience is equal to $ \underline{1} + 3 = 4 $ .

In the third test case, one of the possible quest completion sequences is as follows: $ 1, 2, 2, 2, 3 $ ; its total experience is equal to $ \underline{3} + \underline{2} + 3 + 3 + \underline{4} = 15 $ .

## 样例 #1

### 输入

```
4
4 7
4 3 1 2
1 1 1 1
3 2
1 2 5
3 1 8
5 5
3 2 4 1 4
2 3 1 4 7
6 4
1 4 5 4 5 10
1 5 1 2 5 1```

### 输出

```
13
4
15
15```

# 题解

## 作者：tbdsh (赞：1)

Updated on 2024/10/9：修正一处笔误，感谢 @[sapo1o](/user/997236) 的指出。

# 题意简述
[洛谷原题面](//www.luogu.com.cn/problem/cf1914c)

[CodeForces 原题面](//codeforces.com/problemset/problem/1914/c)

有 $n$ 个任务。第一个任务可以直接完成。后面的每个任务都需要前面的任务都至少完成一次才能完成。

一个任务第一次完成的奖励是 $a_i$，之后每次完成的奖励是 $b_i$。

你最多只能完成 $k$ 个任务。请最大化奖励。


# 分析

可以注意到，我们最多完成到第 $\min(n,k)$ 个任务。

并且，如果要完成任务 $i$，那么之前的所有任务都要完成。

而重复完成任务时，因为我们要使奖励最大化，所以当前 $i$ 个任务都完成时，肯定是选择奖励为 $\max\limits_{1\le j\le i}\{b_j\}$ 的任务进行完成，次数为 $k-i$。

那么我们就扫一遍数组，记录下 $b_i$ 的前缀最大值 $maxx$ 和 $a_i$ 的前缀和 $sum$，然后求 $\max\limits_{1\le i\le \min(n,k)}\{sum + maxx\times (k-i)\}$ 即可。

时间复杂度 $O(n)$。

空间复杂度：$O(n)$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MAXN = 2e5 + 5;
int n, k, a[MAXN], b[MAXN];
void Solve(){
  cin >> n >> k;
  for (int i = 1; i <= n; i++){
    cin >> a[i];
  }
  for (int i = 1; i <= n; i++){
    cin >> b[i];
  }
  int maxx = -1, ans = 0, sum = 0;
  for (int i = 1; i <= min(n, k); i++){
    maxx = max(maxx, b[i]);
    sum += a[i];
    ans = max(ans, sum + (k - i) * maxx);
  }
  cout << ans << '\n';
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--){
    Solve();
  }
  return 0;
}
```

---

## 作者：infinite2021 (赞：0)

### 题解

首先我们假设只做前 $i$ 个任务，这样的价值是 $\sum a_i$，然后如果 $k > i$，最优的策略是选 $[1,i]$ 中最大的 $b_i$，选 $k-i$ 次，然后把答案加起来。

然后 $i$ 的取值是 $[1,\min(n,k)]$，这个是显然的。

然后维护最大值和前缀和都是线性的。

放一下核心代码

```cpp
for(int i=1;i<=n;i++)
	maxn[i]=max(maxn[i-1],b[i]);
int res=0;
for(int i=1;i<=min(n,k);i++)
{
	int now=s[i]+max(k-i,0)*maxn[i];
	res=max(res,now);
}
cout<<res<<endl;
```

---

## 作者：myyyIisq2R (赞：0)

## [CF1914C Quests](https://www.luogu.com.cn/problem/CF1914C)
# 题意
有 $n$ 个任务和 $k$ 个次数。

- 第一个任务可以完成。
- 只有所有 $j < i$ 的任务都被完成时，$i$ 任务才可以被完成。

- 当第一次完成任务 $i$ 时，花费为 $a_i$。
- 当完成该任务的次数大于 $1$ 时，花费为 $b_i$。

求最大花费。

# 思路
当 $k$ 个次数全部用于前 $i$ 个任务时，当且仅当每个任务都至少做过一遍，且剩余的次数全部用于前 $i$ 个任务中 $b$ 花费最大的任务，取到当前情况的最大花费。

那么我们枚举每一个 $i$，预处理前 $i$ 位 $a_i$ 之和，和前 $i$ 位中 $b$ 的最大值，即可 $O(n)$ 处理出答案。

# 细节
```cpp
#include  <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2e5+5;
int a[N],b[N];
int qzh[N],maxb[N];
signed main()
{
	cin.tie(0);
	cout.tie(0); 
	int T;cin>>T;	
	while(T--)
	{
		//all once and pick max rest
		// (k<n)
	
		int n,k;
		cin>>n>>k;
		for(int i{1};i<=n;i++)
			cin>>a[i];
		for(int i{1};i<=n;i++)
			qzh[i] = qzh[i-1]+a[i];
		for(int i{1};i<=n;i++)
			cin>>b[i];
		//maxb
		maxb[0] = -INT_MAX;
		for(int i{1};i<=n;i++)
			maxb[i] = max(maxb[i-1],b[i]);
		
		int ans = -INT_MAX;
		
		for(int i{1};i<=n&&i<=k;i++)
		{
			
			int ansnow = qzh[i];
			ansnow += (k-i)*maxb[i];
			
			ans = max(ans,ansnow);
		}
		cout<<ans<<endl;
	}
 } 
```

---

