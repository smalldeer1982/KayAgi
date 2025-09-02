# Captains Mode

## 题目描述

Kostya is a progamer specializing in the discipline of Dota 2. Valve Corporation, the developer of this game, has recently released a new patch which turned the balance of the game upside down. Kostya, as the captain of the team, realizes that the greatest responsibility lies on him, so he wants to resort to the analysis of innovations patch from the mathematical point of view to choose the best heroes for his team in every game.

A Dota 2 match involves two teams, each of them must choose some heroes that the players of the team are going to play for, and it is forbidden to choose the same hero several times, even in different teams. In large electronic sports competitions where Kostya's team is going to participate, the matches are held in the Captains Mode. In this mode the captains select the heroes by making one of two possible actions in a certain, predetermined order: pick or ban.

- To pick a hero for the team. After the captain picks, the picked hero goes to his team (later one of a team members will play it) and can no longer be selected by any of the teams.
- To ban a hero. After the ban the hero is not sent to any of the teams, but it still can no longer be selected by any of the teams.

The team captain may miss a pick or a ban. If he misses a pick, a random hero is added to his team from those that were available at that moment, and if he misses a ban, no hero is banned, as if there was no ban.

Kostya has already identified the strength of all the heroes based on the new patch fixes. Of course, Kostya knows the order of picks and bans. The strength of a team is the sum of the strengths of the team's heroes and both teams that participate in the match seek to maximize the difference in strengths in their favor. Help Kostya determine what team, the first one or the second one, has advantage in the match, and how large the advantage is.

## 样例 #1

### 输入

```
2
2 1
2
p 1
p 2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
6
6 4 5 4 5 5
4
b 2
p 1
b 1
p 2
```

### 输出

```
0
```

## 样例 #3

### 输入

```
4
1 2 3 4
4
p 2
b 2
p 1
b 1
```

### 输出

```
-2
```

# 题解

## 作者：Ruan_ji (赞：5)

### 题目大意
总共有两种操作，一种是选一个人加入，一种是禁用。

加入的话很简单，贪心加入就行。但是禁用的操作就不能使用贪心了。本题就是用禁用操作卡掉了贪心的做法。

其他的题解都讲了，跳过禁用是没有影响的。如果跳过了选择英雄，就会随机选一个，根据贪心的思维，这个操作显然也没有用处。

最后，我们需要输出的是两个队伍的实力总和相减的绝对值，我们必须同时考虑两个队伍。

### 思路
我们先讲讲为什么贪心是一种不可行的思路。

这里举个例子。比方说我们有一个序列，供两个队伍来挑选。排好序之后是这样的 $[3, 3, 2, 2, 1]$。假如第一个队伍选择了禁用操作，按照贪心的思想，他一定会禁用第一个，也就是实力最强的一个英雄对吧。而不幸的是，这时候轮到对方来选择英雄。对方一定会直接选择剩下的实力最强的英雄。喔吼，你发现了吧，实力为 $3$ 的英雄都没了，轮到你的时候只剩下了一个 $2$ 的。这样，你还不如禁用一个实力最小的呢。所以贪心是不可行的。

这个时候我们来思考另一种可能的解法。我们现在就不引导大家往错误的方向去想了，直接开始正解的教学。

本题用到的算法有动态规划，这个是标签里就有的。但是最重要的算法其实是一个**简单博弈**。

回忆一下，在做博弈的题目，或者说看到博弈的文章的时候，有一句话至关重要。这句话就是：假设博弈双方都绝顶聪明。什么叫绝顶聪明？就是你预判了我的预判，我又预判了你预判了我的预判......这样无穷无尽地进行下去。

所以双方在做选择的时候，其实是可以直接看到最终的结果的。我们现在的选择英雄的双方其实就是在进行相互的博弈过程。博弈的大前提好模拟，但是我们怎么实现双方的”绝顶聪明“呢？似乎并不好实现。

我在这里卡了很久，但是老师点拨了出来。我们既然模拟不出”决定聪明“，为什么不直接从结果开始枚举，这样不久很方便了吗？

所以简单博弈的一句很重要的话是：**先手找剩下状态最优**。

ok，我们知道了要从后往前开始动态规划，现在就来看看如何动态规划吧。



------------


首先，读入 $n$ 个英雄力量，排序从大到小，取前 $m$ 个。因为我们只会有 $m$ 次操作，要多了没用。

$dp[sta]$ 表示剩下 $sta$ 的英雄，按照题意后 $k$ 次操作。初始化 $dp[0] = 0$。遍历状态 $sta = 1 - 2^m$，从 $sta$ 中 $1$ 的个数推出当前的操作编号 $now$。枚举 $now$ 操作的目标英雄为 $i = 0 ~ m - 1$ 且 $i$ 出现在 $sta$ 中。

$dp[sta] = max(dp[sta | 2^i] + val[i])$ 如果当前是 $b$，$val[i] = 0$。如果当前是 $p1$，$val[i] = s[i]$。若 $p2$，$val[i] = -s[i]$。

最后，$answer = dp[2^m  - 1]$。

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>

#define MAXN 1000005
#define INF 1000000000

using namespace std;

int n, m, s[MAXN];
int answer;
int team[MAXN], mp[21][1<<21];
char op[MAXN][2];
bool vis[30],v[21][1<<21];

bool cmp(int x, int y) {return x > y;}

int solve(int x,int p) {
	if(x>m)return 0;
	if(v[x][p])return mp[x][p];
	v[x][p]=1;
	int res;
	if(team[x]==1)
	{
		res=-INF;
		for(int i=1;i<=min(n,20);i++)
		{
			if(!vis[i])
			{
				vis[i]=1;
				res=max(solve(x+1,p+(op[x][1]=='b')*(1<<(i-1)))+(op[x][1]=='p'?s[i]:0),res);
				vis[i]=0;
				if(op[x][1]=='p')
					break;
			}
		}
	}
	else
	{
		res=INF;
		for(int i=1;i<=min(n,20);i++)
		{
			if(!vis[i])
			{
				vis[i]=1;
				res=min(solve(x+1,p+(op[x][1]=='b')*(1<<(i-1)))-(op[x][1]=='p'?s[i]:0),res);
				vis[i]=0;
				if(op[x][1]=='p')
					break;
			}
		}
	}
	mp[x][p]=res;
	return res;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> s[i];
	
	sort (s + 1, s + n + 1, cmp); //从大到小排序,因为两个队伍总是选最优解
	
	cin >> m;
	for (int i = 1; i <= m; ++i)
		scanf("%s%d",op[i]+1,&team[i]);
	answer=solve(1,0);
	printf("%d",answer);
	return 0;
}
```


---

## 作者：是个汉子 (赞：5)

[洛谷传送门](https://www.luogu.com.cn/problem/CF377C)	[CF传送门](http://codeforces.com/problemset/problem/377/C)

### Solution

很显然的，两个队列肯定选择最强的，即使 $m$ 个操作均为‘b’操作，这些操作也只和最强的 $m$ 个英雄有关。

发现题目中 $m\leq \min(n,20)$ ，所以可以考虑状压DP。

在DP之前，还有一点问题——跳过‘p’和'b'怎么办？

对于跳过‘p’，因为两边都是最优策略，所以自己选择一定比随机优；对于跳过‘b’，就相当于禁了最弱的那个，没有影响。

那么现在操作只有‘p’和'b'，设 $dp_{st,pos}$ 表示当前状态是 $st$ ，现在是第 $pos$ 个操作，（一队减二队）最大的得分。对于操作 $i$ ，如果 $i$ 和 $i-1$ 是一个队的操作，最优一定是相加；如果不是，最优一定是做差。

![](https://cdn.luogu.com.cn/upload/image_hosting/82qaq21v.png)
(关于我的博客 $\LaTeX$ 又锅了这件事)

其中 $op_{pos}$ 表示是哪个队操作的， $type_{pos}$ 表示是哪种操作。

肉眼可见，这个转移方程分类讨论了许多，所以选择拿记忆化搜索来转移。(￣▽￣)"

注意：因为刚开始的 $dp_{0,m-1}$ 我们是默认 $op_{m-1}=1$ 来做的，所以如果 $op_{m-1}=2$ ，在求完 $dp_{0,m-1}$ 后要取反。

### Code

```c++
#include<bits/stdc++.h>

using namespace std;
const int N=1<<20,INF=0x3f3f3f3f;
int dp[N][20],n,m,a[110],type[50],op[50];
bool vis[N][20];
char s[5];

int  dfs(int st,int pos){
    if(vis[st][pos]) return dp[st][pos];
    vis[st][pos]=true;
    int & ans=dp[st][pos];
    ans=-INF;
    if(type[pos]){
        for(int i=0;i<m;i++){
            if((1<<i)&st) continue;
            if(pos==0) ans=max(ans,a[i]);
            else if(op[pos]==op[pos-1])
                      ans=max(ans,a[i]+dfs(st|(1<<i),pos-1));
                 else ans=max(ans,a[i]-dfs(st|(1<<i),pos-1));
        }
    }
    else{
        for(int i=0;i<m;i++){
            if((1<<i)&st) continue; 
            if(pos==0) ans=max(ans,0);
            else if(op[pos]==op[pos-1])
                      ans=max(ans,dfs(st|(1<<i),pos-1));
                 else ans=max(ans,-dfs(st|(1<<i),pos-1));
        }
    }
    return ans;
}

int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=m-1;i>=0;i--){
        scanf("%s%d",s,&op[i]);
        type[i]=(s[0]=='p');
    }
    sort(a,a+n);
    for(int i=0;i<m;i++)
        swap(a[i],a[n-i-1]);
    int ans=dfs(0,m-1);
    if(op[m-1]==2) ans=-ans;//取反
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：Mihari (赞：4)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF377C)

# 题解

刚开始我以为这是个贪心，然后打了这样一个代码

``` cpp
inline void Solve(){
    int pts=1,ans=0;
    char opt[5];int team;
    while(m--){
        scanf("%s %d",opt,&team);
        if(opt[0]=='p')ans+=(team==1?1:-1)*val[pts];
        ++pts;
    }writc(ans,'\n');
}
```

然后 $WA$ 穿了......

显然贪心是不对的，因为如果一个人有很多个操作，他在 $ban$ 的回合，不一定会 $ban$ 掉战力最高的英雄

如何解决这个问题？

由于每个队长执行的操作是保证最优的，我们可以定义 `dfs(now,s)` 为执行到操作 $now$，剩下的英雄状态为 $s$ 时，当前操作的队伍能让差变得多大（返回值），那么，对于一个操作 $i$，如果操作 $i$ 和 $i+1$ 是同一队执行，那么差值显然是叠加，否则，最大差值肯定是作差。

为什么这样设计？因为我们要保证每一队都进行最优选择。

**在很多类似的题目中，都保证双方执行最优解时，我们都可以这样进行处理，这是一个很好的方法——线交替先后手地位，用作和或作差对解进行叠加。**

对于每一个操作，我们可以暴力枚举我们应该 $pick/ban$ 掉哪个英雄，为降低复杂度，我们可以定义 $f[i][j]$ 为 `dfs(i,j)` 的返回值。

而我们有四个操作，$pick,ban,miss\space pick,miss\space ban$，但是对于 $pick$ 的回合，选择一定比不选择更优，对于 $ban$，如果是 $miss\space ban$ 也相当于 $ban$ 掉一个最差的英雄，对结果不影响，也就是说，我们只需要考虑 $pick$ 和 $ban$ 两种操作即可。

对于时间复杂度的分析，因为两队都进行最优选择，那么一定不会选择差的英雄，也相当于，只有前 $m$ 个战力最大的英雄有用，那么时间复杂度为 $\mathcal O(20\times 20\times 2^{20})=\mathcal O(419430400)$？（为什么还可以过）

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13442574.html
```



---

## 作者：wenge (赞：2)

正解：状压dp

由于双方都是最优策略，显然选择只会在前$m$大的英雄里进行。

看上去一共4种情况：$pick,ban,misspick,missban$，实际上只需要考虑2种情况$pick,ban$。

因为如果$misspick$的话，选当前剩下最大的总比在剩下的所有英雄里挑选不劣。

由于$2<=m<=min(n,20)$，所以$missban$等价于$ban$了前$m$大的英雄里最小的一个。

所以对于每个状态$dp[i]$都有与其唯一对应的操作轮数。可以根据 每个英雄是否能选择 进行状压dp。

状态转移方程见代码。

```cpp
#pragma GCC optimize(2)
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <iomanip>
using namespace std;
int dp[2100000];
int t[2100000];
int a[105];
char c[30];
int d[30];
int n,m;
int main(){
	for(int i=0;i<=1<<19;i++){
		t[i*2]=t[i];
		t[i*2+1]=t[i]+1;
	}
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1,greater<int>());
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>c[i]>>d[i];
	}
	for(int i=1;i<=(1<<m)-1;i++){
		int j=m-t[i]+1;
		if(d[j]==1)dp[i]=-0x7fffffff;
		else dp[i]=0x7fffffff;
		for(int k=1;k<=m;k++){
			if(i&(1<<(k-1))){
				int l=(c[j]=='p'?a[k]:0);
				if(d[j]==1)dp[i]=max(dp[i], dp[i^(1<<(k-1))] +l);
				else dp[i]=min(dp[i], dp[i^(1<<(k-1))] -l);
			}
		}
	}
	cout<<dp[(1<<m)-1];
    return 0;
}
```


---

