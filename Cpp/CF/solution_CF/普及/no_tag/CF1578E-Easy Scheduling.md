# Easy Scheduling

## 题目描述

Eonathan Eostar decided to learn the magic of multiprocessor systems. He has a full binary tree of tasks with height $ h $ . In the beginning, there is only one ready task in the tree — the task in the root. At each moment of time, $ p $ processes choose at most $ p $ ready tasks and perform them. After that, tasks whose parents were performed become ready for the next moment of time. Once the task becomes ready, it stays ready until it is performed.

You shall calculate the smallest number of time moments the system needs to perform all the tasks.

## 说明/提示

Let us consider the second test from the sample input. There is a full binary tree of height $ 3 $ and there are two processes. At the first moment of time, there is only one ready task, $ 1 $ , and $ p_1 $ performs it. At the second moment of time, there are two ready tasks, $ 2 $ and $ 3 $ , and the processes perform them. At the third moment of time, there are four ready tasks, $ 4 $ , $ 5 $ , $ 6 $ , and $ 7 $ , and $ p_1 $ performs $ 6 $ and $ p_2 $ performs $ 5 $ . At the fourth moment of time, there are two ready tasks, $ 4 $ and $ 7 $ , and the processes perform them. Thus, the system spends $ 4 $ moments of time to perform all the tasks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1578E/98a14360f938976e2072b80e9c0ef58237d08d77.png)

## 样例 #1

### 输入

```
3
3 1
3 2
10 6```

### 输出

```
7
4
173```

# 题解

## 作者：DarkShadow (赞：4)

# CF1578E（模拟）

## 题目大意：

给出一个 $h$ 层的满二叉树，每次可以消去最多 $q$ 个暴露的节点（上方无节点的节点），求最少要消几次才能消完整棵树。

## 思路分析：

我们可以分情况讨论，如果当前暴露的节点少于 $q$ 个，那么可以把这些节点全部消去；如果当前暴露的节点多于 $q$ 个，那么我们就每次消 $q$ 个，同时把新产生的暴露的节点加进去。

注意：由于本题 $h \le 50$，所以需要开 long long。

## 完整代码：

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int T,h,q;
ll Pow[55],cnt1,cnt2,ans,t;//cnt1表示当前还剩下多少节点，cnt2表示当前暴露的节点个数
int main(){
	Pow[0]=1ll;
	for(int i=1;i<=51;i++)
		Pow[i]=Pow[i-1]*2ll;//预处理2的多少次幂
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&h,&q);
		cnt1=Pow[h]-1ll,cnt2=1ll,ans=0ll;
		while(cnt1){
			if(cnt2<=q){//如果暴露的节点少于q个
				cnt1-=cnt2,cnt2*=2ll,ans++;
				continue;
			}
			t=cnt2/(ll)(q),ans+=t,cnt1-=t*(ll)(q),cnt2-=t*(ll)(q),cnt2+=t*(ll)(q)*2ll,cnt2=min(cnt2,cnt1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Goodrage (赞：2)

**题目大意**

我有一棵 $h$ 层满二叉树，想要消去它。只有暴露的节点可以被消去，而且一次最多消去 $q$ 个暴露的节点。

最开始只有根节点是暴露的节点。但是，如果消去了一个节点，它的子节点就会暴露出来。那么最少几次消去整棵树？

**思路分析**

我们在消去节点时，无疑会遇到两种情况：

1. 这一层的节点数目 $\le$ $q$

那么这一次只能消掉这一层所有的节点，进入下一层。

2. 这一层的节点数目 $>$ $q$

那么就可以放飞自我，随便消！反正如果不是最后一层，消完还有新露出来的，不用管顺序。就算是最后一层也没事。直接用剩余节点数除以 $q$ 即可。

**重点**

一棵 $h$ 层满二叉树的节点数：
$2^{h}-1$

一棵满二叉树第 $i$ 层的的节点数：
$2^{i-1}$

**代码**

```cpp
#include<cstdio>
#include<iostream>
#include<cmath> 
#define int long long //会爆int
using namespace std;
int rdcnt[60];
signed main()
{
	int T;
	scanf("%lld",&T);
	for(int asdf=1;asdf<=T;asdf++)
	{
		int steps=0;
		int n,m;
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++)
		{
			rdcnt[i]=pow(2.0,i-1); //计算每层节点个数
		}
		int nodenum=pow(2.0,n)-1; //整棵树节点个数
		if(m==1) //特判。第一个样例就是这样的
		{
			printf("%lld\n",nodenum);
			continue;
		}
		int i=1; //现在层数
		while(i<=n)
		{
			if(rdcnt[i]<=m) //第一种情况，只能消一层
			{
				steps++;
				i++;
			}
			else //第二种情况，随便消
			{
				int gone=pow(2.0,i-1)-1;
 ```
这里注意一下。

前面 $i-1$ 层已经消干净了，等于去掉了一个 $i-1$ 层的满二叉树。现在需要求得还剩下的点的个数，就用总数减去消掉的数目。所以这样计算已被消去的点的个数。
 ```cpp
				int newnum=nodenum-gone;//还剩多少
				steps+=newnum/m; //放飞自我！反正一次消q个就行
				if(newnum%m!=0) steps++;//判整除！如果没整除，剩下的还需要再消一次
				break;
			}
		}
		printf("%lld\n",steps);
	}
	return 0;
}
```

**结果**

![](https://cdn.luogu.com.cn/upload/image_hosting/kehc2vr3.png)

鸣谢：

思路 - [洛浔](https://www.luogu.com.cn/user/151947)

代码 - [我](https://www.luogu.com.cn/user/283215)

陪着开黑 - [2019tyk61](https://www.luogu.com.cn/user/398434)

---

## 作者：__int127 (赞：0)

**[洛谷 link](https://www.luogu.com.cn/problem/CF1578E)，[Codeforces link](https://codeforces.com/problemset/problem/1578/E)**

## 题目大意

此题包含 $t$ 组测试用例。

一颗高度为 $h$ 的满二叉树，每次最多消除 $q$ 个“暴露的节点”，问消除几次可以消除所有节点。

定义节点是“暴露的”：

1. 根节点为“暴露的节点”。

1. 被消除的“暴露的节点”的子节点为“暴露的节点”。

## 思路

首先我们要知道：

1. 一颗高度为 $h$ 的满二叉树的节点数为 $2^h-1$。

1. 一棵满二叉树的第 $i$ 层有 $2^{i-1}$ 个节点。

接下来就会有两种情况：

### 第 $i$ 层节点数（$2^{i-1}$）$<q$

因为每一次消不够 $q$ 个节点，所以可以从第 $1$ 层开始遍历，最多遍历至 $n$ 层，每层让计数变量增加 $2^{i-1}$（由于我的代码中 $i$ 初始为 $0$，所以让 `gs += pow(2, i);`，`gs` 为计数变量，文章中 $i$ 初始均为 $1$，请自行转换），当 $i>n$ 或 $2^{i-1} \ge q$ 时停止，代码：

```cpp
for (long long i = 0; i < n; i++){
	if (pow(2, i) <= q){
		ans++;
		gs += pow(2, i);
	} else {
		break;
	}
}
```

### 第 $i$ 层节点数（$2^{i-1}$）$\ge q$

这种情况就不用循环了，因为每一次消完 $q$ 个节点后还有剩余，而且还会出现新的节点（叶子节点除外），但是最后可能还会消不够，所以向上取整一下就好了，次数为 $\lceil\frac{num-gs}{q}\rceil$，$num$ 为高度为 $h$ 的满二叉树的节点数，$ans$ 为消除次数，代码：

```cpp
ans += ceil(((double)num - gs) / q);
```

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, q;
int main(){
	ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
	cin >> t;
	while (t--){
		cin >> n >> q;
		long long num = pow(2, n) - 1, gs = 0, ans = 0;
		for (long long i = 0; i < n; i++){
			if (pow(2, i) <= q){
				ans++;
				gs += pow(2, i);
			} else {
				break;
			}
		}
		ans += ceil(((double)num - gs) / q);
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Fu_Da_Ying (赞：0)

## [原题链接](https://www.luogu.com.cn/problem/CF1578E)
## 题意：
一棵 $h$ 层满二叉树，想要消去它。只有暴露的节点可以被消去，而且一次最多消去 $q$ 个暴露的节点。

最开始只有根节点是暴露的节点。但是，如果消去了一个节点，它的子节点就会暴露出来。那么最少几次消去整棵树？
## 思路：
我们在消去节点时，无疑会遇到两种情况：

1. 这一层的节点数目 $\le q$

那么这一次只能消掉这一层所有的节点，进入下一层。

2. 这一层的节点数目 $> q$

那么随便消就行。次层的节点数目已经 $> q$，则下面露出的节点一定 $>q$。直接用剩余节点数 $\div q$ 即可。

一棵 $h$ 层满二叉树的节点数：$2^{h}-1$

在代码中出现了 ```?:``` 东西，ta 是三目运算符，基本格式是 ```a?b:c```，即 ```a``` 为真，则返回 ```b```，否则返回 ```c```。
## Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,h,q,storey_nodes,steps,full_nodes;
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld%lld",&h,&q);
		storey_nodes=1,steps=0,full_nodes=pow(2,h)-1;//初始化
		for(int i=1;i<=h;i++){
			if(storey_nodes<=q){
				steps++;//次数增加 
				full_nodes-=storey_nodes;//此棵满二叉树减掉此层的节点 
				storey_nodes*=2;//下一层的节点是上一层的两倍 
			}else{
			    steps+=full_nodes/q+(full_nodes%q==0?0:1/*三目运算符*/);
				break;
			}
		}
		printf("%lld\n",steps);
	}
	return 0;
}
```

---

