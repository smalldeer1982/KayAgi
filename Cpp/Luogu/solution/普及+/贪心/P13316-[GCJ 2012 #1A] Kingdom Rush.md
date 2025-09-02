# [GCJ 2012 #1A] Kingdom Rush

## 题目背景

Kingdom Rush 由 Ironhide Game Studio 开发。Ironhide Game Studio 未参与本题，也未对 Google Code Jam 进行任何背书。


## 题目描述

Ryan 正在玩 Kingdom Rush，这是一款由 Ironhide Game Studio 开发的单人塔防游戏。在 Kingdom Rush 中，玩家通过完成关卡获得星星，具体规则如下。星星越多，玩家就越强大；因此，Ryan 也许暂时无法完成第 2 关，但他可以先通过第 1 关获得星星后再挑战第 2 关。

真实的 Kingdom Rush 游戏机制与本题略有不同。你不需要玩过这款游戏也能解题。

在本题描述的 Kingdom Rush 里，当玩家完成某一关时，可以获得 1 星或 2 星的评价。获得星星的具体规则如下：

* 如果玩家从未通关该关卡，并以 1 星评价通关，则获得 1 颗星。
* 如果玩家从未通关该关卡，并以 2 星评价通关，则获得 2 颗星。
* 如果玩家之前以 1 星评价通关过该关卡，现在以 2 星评价再次通关，则再获得 1 颗星。

除此之外，玩家无法再通过该关卡获得星星。

Ryan 可能并不能立刻完成所有关卡。对于每一关，在以 1 星评价完成前，需要至少获得 $a_i$ 颗星；而以 2 星评价完成前，需要至少获得 $b_i$ 颗星，且 $b_i \geq a_i$。

例如，假设有两关：

* 第 1 关：以 1 星评价完成需要 0 颗星，以 2 星评价完成需要 1 颗星。
* 第 2 关：以 1 星评价完成需要 0 颗星，以 2 星评价完成需要 2 颗星。

Ryan 可能的通关流程如下：

1. Ryan 初始有 0 颗星。他可以选择以 1 星评价完成第 1 关或第 2 关。他选择以 1 星评价通关第 1 关，此时有 1 颗星。
2. 现在，Ryan 可以选择以 1 星评价通关第 2 关，或以 2 星评价再次通关第 1 关。他选择以 2 星评价通关第 1 关，此时有 2 颗星。
3. 现在，Ryan 可以以 2 星评价通关第 2 关。他完成后共有 4 颗星。
4. 此时他已完成所有关卡的 2 星评价，累计获得 4 颗星（每关 2 颗）。他一共通关了 3 次：第 1 关两次，第 2 关一次。

Ryan 很擅长塔防游戏，但他需要你的帮助来尽快通关。你的任务是计算，为了让每一关都获得 2 星评价，Ryan 至少需要通关多少次。


## 说明/提示

**限制条件**

- $1 \leq T \leq 100$
- $0 \leq a_i \leq b_i \leq 2001$

**测试集 1（15 分，结果可见）**

- $1 \leq N \leq 10$

**测试集 2（18 分，结果隐藏）**

- $1 \leq N \leq 1000$

翻译由 ChatGPT-4.1 完成。

## 样例 #1

### 输入

```
4
2
0 1
0 2
3
2 2
0 0
4 4
1
1 1
5
0 5
0 1
1 1
4 7
5 6```

### 输出

```
Case #1: 3
Case #2: 3
Case #3: Too Bad
Case #4: 6```

# 题解

## 作者：kill_wcz (赞：2)

果然，人都是喜新厌旧的吗…
### 题解：P13316 [GCJ 2012 #1A] Kingdom Rush
---
题目大意：

[题目](https://www.luogu.com.cn/problem/P13316)

#### 思路：

这道题目的背景就像皇室战争，推荐大家玩！  

这是一道标准的贪心题目。  
贪心的点就是直接二星肯定比一星好（条件通过的话）。  
我们先把一星和二星分别输入，再按升序排序。  
再开始判断：

当看到一关可以二星通过时，直接通关。  
再通一星的关卡。  
如果连一星的题目都通过不了，那就输出 Too Bad 。

所以我们得出代码。  
注：这段代码的思路和代码原型来自于[@wuhaolinwhl](https://www.luogu.com.cn/user/1187802)。  
他本人也同意了，这段代码是作者的改进版。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,t,sum=0,ans=0,x[10005];
struct node1 {
	int one,id,two;
	bool operator<(node1 z)const{
		if(sum>=one&&sum>=z.one)return two>z.two;
		return one<z.one;
	}
} p1[10005];
struct node2 {
	int two,id;
	bool operator<(node2 z)const{
		return two<z.two;
	}
} p2[10005];
signed main() {
	cin>>t;
	for(int j=1; j<=t; j++) {
		//初始化 
		ans=sum=0;
		for(int i=1; i<=1000; i++)x[i]=0;
		cin>>n;
		for(int i=1; i<=n; i++) {
			cin>>p1[i].one>>p2[i].two;
			p1[i].two=p2[i].two;
			p1[i].id=i;
			p2[i].id=i;
		}
		sort(p1+1,p1+n+1);
		sort(p2+1,p2+n+1);
		int c1=1,c2=1,op=0;
		while(c2<=n) {
			int k=0;
			if(sum>=p2[c2].two) {
				sum+=(2-x[p2[c2].id]);
				x[p2[c2].id]=2;
				c2++;
				k=1;
				ans++;
			}
			else {
				if(sum>=p1[c1].one&&c1<=n) {
					if(x[p1[c1].id]==0) {
						sum++;
						x[p1[c1].id]=1;
						ans++;
					}
					c1++;
					k=1;
				}
			}
			sort(p1+c1,p1+n+1);
			if(k==0){
				cout<<"Case #"<<j<<": "<<"Too Bad"<<endl;
				op=1;
				break;
			}
		}
		if(op==1) continue;
		cout<<"Case #"<<j<<": "<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：wuhaolinwhl (赞：0)

# [P13316](https://www.luogu.com.cn/problem/P13316)

祝贺自己切掉一道绿题

## 题目大纲  
这道题是一道贪心加排序的题（个人认为贪心思路好想，排序思路较难）。  
## 思路讲解  
这题的贪心思路是要将一颗星与两颗星分开计算并记录他们的 $id$ 利用 $sort$ 函数进行排序，然后先看当前是否能通当前未通关中两颗星要求最小的关卡，有就通，没有就看能否通一颗星的。每次通关后都要进行重新排序。若都无法通关就输出 Too Bad。

两颗星的排序思路是从小到大排，而一颗星的排序思路不是从小到大排，而是在你能通关且未通关的关卡中按它们关卡的两颗星通关要求星数从大到小排，剩下的按一颗星的要求从小到大排。  
代码如下
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int t,x[10005],sum;
struct ON
{
	int on,id,tw;
}pl1[10005];
struct TW
{
	int tw,id;
}pl2[10005];
bool cmp1(ON x,ON y)
{
	if(sum>=x.on&&sum>=y.on) return x.tw>y.tw;
	return x.on<y.on;
}
bool cmp2(TW x,TW y)
{
	return x.tw<y.tw;
}
int main()
{
	cin>>t;
	for(int j=1;j<=t;j++)
	{
		int n,ans=0;
		sum=0;
		for(int i=1;i<=1000;i++)
		{
			x[i]=0;
		}
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>pl1[i].on>>pl2[i].tw;
			pl1[i].tw=pl2[i].tw;
			pl1[i].id=i;
			pl2[i].id=i;
		}
		sort(pl1+1,pl1+n+1,cmp1);
		sort(pl2+1,pl2+n+1,cmp2);
		int cnt2=1,cnt1=1,op=0;
		while(cnt2<=n)
		{
			int k=0;
			if(sum>=pl2[cnt2].tw)
			{
				sum+=(2-x[pl2[cnt2].id]);
				x[pl2[cnt2].id]=2;
				cnt2++;
				k=1;
				ans++;
			}
			else
			{
				if(sum>=pl1[cnt1].on&&cnt1<=n)
				{
					if(x[pl1[cnt1].id]==0)
					{
						sum++;
						x[pl1[cnt1].id]=1;
						cnt1++;
						k=1;
						ans++;
					}
					else
					{
						cnt1++;
						k=1;
					}
				}
			}
			sort(pl1+cnt1,pl1+n+1,cmp1);
			if(k==0)
			{
				cout<<"Case #"<<j<<": "<<"Too Bad"<<endl;
				op=1;
				break;
			}
		}
		if(op==1) continue;
		cout<<"Case #"<<j<<": "<<ans<<endl;
	}
	return 0;
}
```

---

