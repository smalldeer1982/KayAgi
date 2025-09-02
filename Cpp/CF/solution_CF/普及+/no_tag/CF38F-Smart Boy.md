# Smart Boy

## 题目描述

Petya和Vasya发明了一种新的游戏，并把它叫做 "聪明小子"。他们为这个游戏规定了一组单词——字典。字典中可以包含类似的单词。

游戏规则如下：首先，第一个玩家从字典中的任意一个单词中选择任意一个字母,得到一个长度为 $1$ 的单词，并将其写在一张纸上。第二位玩家在这个字母的开头或结尾位置加上其他字母，这样就形成了一个长度为 $2$ 的单词，然后又轮到第一位玩家，他在目前单词的开头或结尾加上一个字母，这样就形成了一个长度为 $3$ 的单词，以此类推。但玩家的操作必须满足一个条件：新造的单词必须是字典中的一个单词的子串。如果玩家不能在不违反条件的情况下给当前的单词添加一个字母，那么他就输了。

另外，如果在一个回合结束时，某个字符串 $s$ 被写在纸上，那么刚刚完成操作的玩家，就会根据公式得到一定的分数:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/0581ff8dd9c5f97bc34f4839b9be626798958173.png)

其中:


- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/e4be189456c3857fdc2ca591471080a7e0553024.png)是拉丁字母（即英文字母）中符号 $c$ 的序列号，从 $1$ 开始编号。例如![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/a709cc8eab21d8d610387ef6b07c36d3277a654a.png)，和![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/72027ed786a5fe069852a41dd736894e110bbaab.png) 。
- ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF38F/a15427ebfe6c6b2fd1a1aca564e59cc85cdf2fd3.png)是字典中含有 $s$ 的单词数量。（若字符串 $s$ 作为子串在单词 $x$ 中出现至少一次，我们称 $x$ 是一个含有 $s$ 的单词）

你的任务是计算出谁将赢得游戏以及最后的分数是多少。每个玩家都会以最佳的方式进行游戏，并且试图赢得比赛，即使自己的分数最大化，使对手的分数最小化。

## 样例 #1

### 输入

```
2
aba
abac
```

### 输出

```
Second
29 35
```

## 样例 #2

### 输入

```
3
artem
nik
max
```

### 输出

```
First
2403 1882
```

# 题解

## 作者：liangbowen (赞：0)

[blog](https://www.cnblogs.com/liangbowen/p/17737676.html)。严重怀疑这题放到 2023 年至少 \*2000，评绿合情合理。

---

首先是博弈论。然后数据范围很小。直接暴力 DP 啪的一下上去了，很快啊！

这就抽象起来了。另一篇题解说不能暴力转移，但是你先预处理出来 $num(s)$，然后直接记忆化搜索，暴力枚举每一次操作的字符，这不就做完了吗。

具体一点的话，直接模拟下面过程就可以过题了。

+ `dfs()` 传参就把题目里面有用的东西全传进去，$s$，$\sum\limits_{i=1}^{|s|} \operatorname{value}(s_i)$ 与 $\max\limits_{1\le i\le |s|}\{\operatorname{value}(s_i)\}$。
+ 你每次返回三个数，一个记录是谁的必胜态，另外两个记录先后手的分数。
+ 最后 naive 地转移：能赢最重要，其次是先手的分数越大越好，然后是后手的分数越小越好。

[code](https://codeforces.com/contest/38/submission/225843774)，时间复杂度 $O(\text{能过})$。


---

## 作者：EgLund (赞：0)

思路 部分来自 [官方题解（俄语）](https://codeforces.com/blog/entry/816)。

严重怀疑这题放到 2022 年至少 *2600，洛谷建议评紫。不知道为什么 2010 年的外国小哥水平这么强。

这种题没有什么好的贪心解法，想 DP。

博弈论的常见解法是存储一个游戏状态和当前操作的玩家，然后结果是当前玩家是否有必胜策略。

所以我们考虑用一个 `dp[str]` 数组存储三元组 $(result,a,b)$，其中 $result$ 表示当前玩家是否可以获胜，$a$ 和 $b$ 表示当前玩家采取最优策略时当前玩家和对手的分数。

有两个问题：第一个是数组的存储，我们总不能把字符串当下标吧。所以我们用 `std::unordered_map` 存储字符串对应的序数，然后没了。

第二个是转移。考虑 trival 的博弈论 DP，先手必败态转移到的一定是必胜态。

但是发现这个东西没法转移。

我们倒推，对于一个能转移到必败态的节点，一定是必胜态。我们枚举放上去的字母，然后去更新答案。

代码中采用 `std::set` 预处理状态转移，使用记忆化搜索进行转移。

```
#include<bits/stdc++.h>
using namespace std;
using Status=pair<bool,pair<int,int> >;
int n,a[14000],b[14000],vis[14000];
string s[31];
map<string,int> mp;
#define get_id(str) ((mp.count(str))?(mp[str]):(mp[str]=mp.size()-1))
set<int> g[14000];
Status dp[14000];
Status dfs(int u)
{
	if(!vis[u])
	{
		vis[u]=1;
		if(g[u].empty())return make_pair(0,make_pair(0,0));
		else
		{
			Status res=make_pair(0,make_pair(0,0));
			for(int v:g[u])
			{
				Status p=dfs(v);
				res=max(res,make_pair(!p.first,make_pair(a[v]-p.second.second,-p.second.first)));
			}
			dp[u]=res;
		}
	}
	return dp[u];
}
int main()
{
	cin>>n;
	mp[""]=0;
	for(int i=1;i<=n;i++)
	{
		memset(b,0,sizeof b);
		cin>>s[i];
		for(int j=0;j<(int)s[i].size();j++)
		{
			for(int k=1;k+j<=(int)s[i].size();k++)
			{
				b[get_id(s[i].substr(j,k))]=1;
			}
		}
		for(int j=0;j<14000;j++)a[j]+=b[j];
	}
	for(pair<string,int> i:mp)
	{
		int mx=0,sm=0;
		for(int j=0;j<(int)i.first.size();j++)
		{
			mx=max(mx,i.first[j]-'a'+1);
			sm+=i.first[j]-'a'+1;
		}
		a[i.second]+=mx*sm;
		if(i.first!="")
		{
			if(mp.count(i.first.substr(1,i.first.size()-1)))g[mp[i.first.substr(1,i.first.size()-1)]].insert(i.second);
			if(mp.count(i.first.substr(0,i.first.size()-1)))g[mp[i.first.substr(0,i.first.size()-1)]].insert(i.second);
		}
	}
	Status p=dfs(0);
	cout<<((p.first)?"First":"Second")<<endl<<p.second.first<<' '<<-p.second.second;
}
```

---

