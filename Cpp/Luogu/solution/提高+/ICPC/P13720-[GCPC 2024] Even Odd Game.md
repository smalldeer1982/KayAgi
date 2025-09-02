# [GCPC 2024] Even Odd Game

## 题目描述

像往常的每个星期六一样，Eve 去她本地的游戏俱乐部玩耍。  
今天，Bob 带来了一款他自己设计的新游戏。  
经过仔细研究，你声称这个游戏存在一个必胜策略，因此某一方总能获胜。  
Bob 对你说他设计的游戏很无聊这件事半信半疑，于是他邀请你来玩一局！  
既然你声称存在必胜策略，你可以决定谁先开始游戏。

![](https://cdn.luogu.com.cn/upload/image_hosting/119eym2b.png)

:::align{center}
图 E.1：两组样例对局中的卡牌。
:::

游戏规则如下：  
桌上有 $n$ 张卡牌，每张卡牌上都有一个数学运算符（$\texttt{+}$ 或 $\texttt{*}$）和一个整数，如图 E.1 所示。  
Eve 和 Bob 轮流选择卡牌，用选中的卡牌对一个公共数字进行操作。  
例如，如果当前数字为 $5$，而卡牌为 $+3$，则数字会变为 $8$。  
每张卡牌只能使用一次，所有卡牌用完后游戏结束。  
如果最终数字是奇数，则先手获胜；如果是偶数，则后手获胜。  
给定卡牌列表和初始值，请帮助 Eve 赢得这场游戏。

## 说明/提示

（无）

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
+ 7
* 4
+ 2
1


* 4```

### 输出

```





me
+ 2

+ 7```

## 样例 #2

### 输入

```
2
+ 8
* 5
10

+ 8```

### 输出

```




you

* 5```

# 题解

## 作者：Crazyouth (赞：0)

## 分析

根据样例的启发，牌分为三类：

- 加偶数或乘奇数，这种牌不改变当前的奇偶性。
- 加奇数，这种牌使当前奇偶性取反。
- 乘偶数，这种牌使当前数变为偶数。

观察题目数据范围，会发现 $O(n^3)$ 的复杂度是可以通过的，又因为这题是博弈，不难发现我们以每一种牌的数量加上当前数奇偶性为一个状态，只会有至多 $O(n^3)$ 种状态，在这些状态上跑有向图博弈就做完了（不用真的建图）。

具体地，枚举每次在三种牌中打哪一种，如果三种方法都会输，那么这个状态就是必胜的，否则它是必败的。边界条件是如果 $n$ 为奇数，那么所有牌打完后如果是偶数，那么当前的人（即后手）会获胜，否则当前的人就失败了。$n$ 为偶数时相反。在交互的时候你只要让交互库一直位于必败态就可以了。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt1,cnt2,cnt3,x;
int sta[310][310][310][2];
multiset<pair<char,int>> st1,st2,st3;
int dfs(int i,int j,int k,int b)
{
	if(~sta[i][j][k][b]) return sta[i][j][k][b];
	int f=0;
	if(i) f|=!dfs(i-1,j,k,b);
	if(j) f|=!dfs(i,j-1,k,!b);
	if(k) f|=!dfs(i,j,k-1,0);
	sta[i][j][k][b]=f;
	return f;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		char opt;
		int k;
		cin>>opt>>k;
		if(opt=='+')
		{
			if(k%2==0) cnt1++,st1.insert({opt,k});
			else cnt2++,st2.insert({opt,k});
		}
		else
		{
			if(k%2==0) cnt3++,st3.insert({opt,k});
			else cnt1++,st1.insert({opt,k});
		}
	}
	cin>>x;
	memset(sta,-1,sizeof sta);
	sta[0][0][0][0]=n%2;
	sta[0][0][0][1]=1-n%2;
	dfs(cnt1,cnt2,cnt3,x%2);
	cout<<(sta[cnt1][cnt2][cnt3][x%2]?"me":"you")<<endl;
	if(sta[cnt1][cnt2][cnt3][x%2])
	{
		int i=cnt1,j=cnt2,k=cnt3,b=x%2;
		while(1)
		{
			if(!n) break;
			n--;
			if(i&&!sta[i-1][j][k][b]&&st1.size())
			{
				i--;
				cout<<st1.begin()->first<<' '<<st1.begin()->second<<'\n';
				st1.erase(st1.begin());
			}
			else if(j&&!sta[i][j-1][k][!b]&&st2.size())
			{
				j--;
				cout<<st2.begin()->first<<' '<<st2.begin()->second<<'\n';
				st2.erase(st2.begin());
				b=!b;
			}
			else
			{
				k--;
				cout<<st3.begin()->first<<' '<<st3.begin()->second<<'\n';
				st3.erase(st3.begin());
				b=0;
			}
			cout.flush();
			if(!n) break;
			n--;
			char opt;
			int t;
			cin>>opt>>t;
			if(st1.count({opt,t}))
			{
				st1.erase(st1.find({opt,t}));
				i--;
			}
			else if(st2.count({opt,t}))
			{
				st2.erase(st2.find({opt,t}));
				j--;
				b=!b;
			}
			else
			{
				st3.erase(st3.find({opt,t}));
				k--;
				b=0;
			}
		}
	}
	else
	{
		int i=cnt1,j=cnt2,k=cnt3,b=x%2;
		while(1)
		{
			if(!n) break;
			n--;
			char opt;
			int t;
			cin>>opt>>t;
			if(st1.count({opt,t}))
			{
				st1.erase(st1.find({opt,t}));
				i--;
			}
			else if(st2.count({opt,t}))
			{
				st2.erase(st2.find({opt,t}));
				j--;
				b=!b;
			}
			else
			{
				st3.erase(st3.find({opt,t}));
				k--;
				b=0;
			}
			if(!n) break;
			n--;
			if(i&&!sta[i-1][j][k][b]&&st1.size())
			{
				i--;
				cout<<st1.begin()->first<<' '<<st1.begin()->second<<'\n';
				st1.erase(st1.begin());
			}
			else if(j&&!sta[i][j-1][k][!b]&&st2.size())
			{
				j--;
				cout<<st2.begin()->first<<' '<<st2.begin()->second<<'\n';
				st2.erase(st2.begin());
				b=!b;
			}
			else
			{
				k--;
				cout<<st3.begin()->first<<' '<<st3.begin()->second<<'\n';
				st3.erase(st3.begin());
				b=0;
			}
			cout.flush();
		}
	}
}

---

