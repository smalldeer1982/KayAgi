# Train and Queries

## 题目描述

Along the railroad there are stations indexed from $ 1 $ to $ 10^9 $ . An express train always travels along a route consisting of $ n $ stations with indices $ u_1, u_2, \dots, u_n $ , where ( $ 1 \le u_i \le 10^9 $ ). The train travels along the route from left to right. It starts at station $ u_1 $ , then stops at station $ u_2 $ , then at $ u_3 $ , and so on. Station $ u_n $ — the terminus.

It is possible that the train will visit the same station more than once. That is, there may be duplicates among the values $ u_1, u_2, \dots, u_n $ .

You are given $ k $ queries, each containing two different integers $ a_j $ and $ b_j $ ( $ 1 \le a_j, b_j \le 10^9 $ ). For each query, determine whether it is possible to travel by train from the station with index $ a_j $ to the station with index $ b_j $ .

For example, let the train route consist of $ 6 $ of stations with indices \[ $ 3, 7, 1, 5, 1, 4 $ \] and give $ 3 $ of the following queries:

- $ a_1 = 3 $ , $ b_1 = 5 $ It is possible to travel from station $ 3 $ to station $ 5 $ by taking a section of the route consisting of stations \[ $ 3, 7, 1, 5 $ \]. Answer: YES.
- $ a_2 = 1 $ , $ b_2 = 7 $ You cannot travel from station $ 1 $ to station $ 7 $ because the train cannot travel in the opposite direction. Answer: NO.
- $ a_3 = 3 $ , $ b_3 = 10 $ It is not possible to travel from station $ 3 $ to station $ 10 $ because station $ 10 $ is not part of the train's route. Answer: NO.

## 说明/提示

The first test case is explained in the problem statement.

## 样例 #1

### 输入

```
3


6 3
3 7 1 5 1 4
3 5
1 7
3 10


3 3
1 2 1
2 1
1 2
4 5


7 5
2 1 1 1 2 4 4
1 3
1 4
2 1
4 1
1 2```

### 输出

```
YES
NO
NO
YES
YES
NO
NO
YES
YES
NO
YES```

# 题解

## 作者：Hisaishi_Kanade (赞：4)

### 一、思路

题意很清晰明了，不多赘述。

首先考虑 $O\left(t\cdot n^2\right)$ 的超时做法，这样显然是不行的，因为 $n\le2\cdot 10^5$，完全不能忍受。

那我们思考一个问题：

> 如果 $a_i$ 能到达 $b_i$ 说明什么？

答案：说明 $a_i$ 有一次出现比 $b_i$ 有一次出现早！

问题转换为记录出现的时间，这个很简单。

因为 $a_i$ 和 $b_i$ 值太大，开不了数组，那么只能使用容器映射。

### 二、代码

```cpp
#include <map>//映射要用
#include <stdio.h>
using std::map;
int t,n,k,x,a,b,i;
int main(){
	scanf("%d",&t);
	while(t--){
		map<int,int>l,r;//l表示最早一次，r表示最晚一次
						//不这样要clear()，反而麻烦，不如再申请一个
		scanf("%d %d",&n,&k);
		for(i=1;i<=n;++i){
			scanf("%d",&x);
			if(!l[x])//没见过
				l[x]=i;//记录
			r[x]=i;//不断更新
		}
		while(k--){
			scanf("%d %d",&a,&b);
			if(l[a]&&l[b]&&l[a]<=r[b])//都出现过且ai最早一次比bi最晚一次早，就可以
				puts("YES");
			else
				puts("NO");//反之，不行
		}
	}
	return 0;
}
```

复杂度 $O\left(t\cdot n\log n\right)$，可以忍受。

---

## 作者：yeshubo_qwq (赞：3)

## Description

给定一个序列 $a_1,a_2 \dots a_n$，问是否存在一个 $x$ 的位置不超过 $y$ 的位置。

## Solution

想要让 $x$ 的位置不超过 $y$ 的位置，最优的方案是尽可能让 $x$ 往前，$y$ 往后。

于是我们可以记录每一个数值最早和最晚出现的位置，每次判断 $x$ 最早的位置和 $y$ 最晚的位置即可。

数值最大会到 $10^9$，记录可以用 map。

除此之外，还要判断 $x,y$ 存在。

## Code

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
int n,m,i,x,y;
void solve(){
	cin>>n>>m;
	map <int,int> a,b;
	for (i=1;i<=n;i++){
		cin>>x;
		if (a[x]==0) a[x]=i;
		b[x]=i;
	}
	for (i=1;i<=m;i++){
		cin>>x>>y;
		if (a[x]!=0 && b[y]!=0 && a[x]<=b[y]) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int tests=1;
	cin>>tests;
	while (tests--)
		solve();
	return 0;
}

```


---

## 作者：NATO (赞：1)

### 题目翻译：
沿铁路有站点，编号从 $1$ 到 $10^9$。快车总是沿着由 $n$（$1≤n≤2⋅10^5$）个站点组成的路线行驶，索引为 $u_1$，$u_2$，…，$u_n$，其中（$1≤u_i≤10^9$）。火车从左向右行驶。它从 $u_n$ 站开始，然后停在 $u_2$ 站，然后停在 $u_3$ 这里，以此类推。$u_n$ 是终点站。这列火车可能会多次停靠同一个车站。也就是说，值 $u_1$，$u_2$，…，可能存在重复。给你 $k$（$1≤k≤2⋅10^5$）个查询，每个包含两个不同的整数 $a_j$ 和 $b_j$（$1≤a_j,b_j≤10^9$）。对于每个查询，确定是否可以乘坐火车从索引为 $a_j$ 的站点到达索引为 $b_j$ 的站点。

### 题目分析：

首先，因为数据范围达到了 $10^9$，同时，$n$ 与 $k$ 均达到了 $2⋅10^5$，因此考虑每一次查询时间复杂度控制在 $O(logn)$ 级别，因为数据范围太大，必须因此我们想到了使用映射来存储。

映射键名即是经过站点索引，键值存储该站点在路线中的出现位置最大值与最小值。设 $\max(id)$ 表示该线路中索引为 $id$ 的车站出现位置最大值，$\min(d)$ 表示该线路中索引为 $id$ 的车站出现位置最小值，查询时，即可如下：

1.若 $\max(a_j)$ 或 $\max(b_j)$ 为 $0$ 则说明至少有一个索引不在经过站点中，输出 ```NO```。

2.若 $\min(a_j)>\max(b_j)$ 说明最早经过的 $a_j$ 站点都比最晚经过的 $b_j$ 晚，就不可能从索引为 $a_j$ 的站点到达索引为 $b_j$ 的站点，输出 ```NO```。

3.若以上两点均未满足，输出 ```YES```。

#### 参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#pragma GCC optimize(2)
using namespace std;
ll t;
ll n,k;
ll cnt;
struct px
{
	ll minn=2147483647,maxn;
};
map<ll,px>a;
ll u,v,op;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t; 
	while(t--)
	{
		a.clear();
		cnt=0;
		cin>>n>>k;
		for(ll i=1;i<=n;++i)
		{
			cin>>op;
			a[op].minn=min(a[op].minn,i);
			a[op].maxn=max(a[op].maxn,i);
		}
		for(ll i=1;i<=k;++i)
		{
			cin>>u>>v;
			if(!a[u].maxn||!a[v].maxn)
				cout<<"NO\n";
			else
			{
				if(a[u].minn>a[v].maxn)
				cout<<"NO\n";
				else 
				cout<<"YES\n";
			}
		}
	}
}
```


---

## 作者：Halberd_Cease (赞：0)

## 题意简述
给你一个序列，给定 $a,b$ 让你求 $a$ 是否在 $b$ 前面（$a$ 和 $b$ 可以出现多次，只要存在一对即可）。

考虑 $ 1 \le a_j, b_j \le 10^9 $ 显然不能直接开数组，因此需要使用离散化或者映射。这里选择相对码量较少的映射。

一个下标携带 $2$ 个数据：该数最早出现和最晚出现的位置。

对于每一个询问：

1. 如果任意一个没有出现过就输出 ```NO```；

2. 如果 $a$ 的最早出现位置比 $b$ 的最晚出现位置还要晚，那么 $a$ 不可能在$b$ 前面，故输出 ```NO```；

3. 如果以上都不成立，输出 ```YES```。

如何判断有没有出现过？

其实很简单，给每一个赋上初值，只要没有改变就没有出现。

## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct Node{
    int maxx=0,minx=2147483647;
};
map<int,Node>mapp;
main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        mapp.clear();
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
        {
            int x;
            cin>>x;
            mapp[x].maxx=max(mapp[x].maxx,i);
            mapp[x].minx=min(mapp[x].minx,i);
        }
        for(int i=1;i<=m;i++)
		{
			int x,y;
			cin>>x>>y;
			if(mapp[x].maxx==0||mapp[y].maxx==0)
			{
				cout<<"NO\n";
				continue;
			}
			if(mapp[x].minx>mapp[y].maxx)
			{
				cout<<"NO\n";
				continue;
			}
			cout<<"YES\n";
		 } 
    }
}
```

---

## 作者：HarunluoON (赞：0)

## 题意简述

共有 $t$ 个测试用例，每个测试用例中有一列**单方向行驶的**火车依次停靠编号为 $u_1,u_2,\dots,u_n$ 的 $n$ 个车站，$u_1,u_2,\dots,u_n$ 之间可以有重复。有 $k$ 次询问，每次询问给出两个车站编号 $a$、$b$，你需要回答能否乘坐这列火车从编号为 $a$ 的车站到达编号为 $b$ 的车站。

## 方法 1

对于每次询问，在 $u_1,u_2,\dots,u_n$ 中找出 $a$ ，然后试图向右继续找出 $b$。时间复杂度 $O(tkn)$。

$t$ 的最大值为 $10^4$，$n$ 和 $k$ 的最大值为 $2\cdot 10^5$，妥妥的超时。

## 方法 2

显然，如果 $a$ 在 $u_1,u_2,\dots,u_n$ 中第一次出现的下标大于（当然不可能等于啦）$b$ 在 $u_1,u_2,\dots,u_n$ 中最后一次出现的下标，那么不能乘坐这列火车从编号为 $a$ 的车站到达编号为 $b$ 的车站。

举个例子，当 $n=5,u_1=1,u_2=1,u_3=2,u_4=3,u_5=5$ 时，显然不可能乘坐这列火车从编号为 $3$ 的车站到达编号为 $1$ 的车站。

对每一个测试用例，在输入 $u_1,u_2,\dots,u_n$ 时记录下每一个编号在 $u_1,u_2,\dots,u_n$ 中第一次和最后一次出现时的下标。之后进行 $k$ 次询问时便可以做到 $O(1)$ 给出答案。

时间复杂度为 $O(tn)$，看似 $tn$ 达到了 $2\cdot 10^9$，会超时，但是~~由于未知原因~~不会。

完整代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
map<int,int> first,last;//分别存储每个编号在车站序列中第一次和最后一次出现位置的下标
void work()
{
	int n,k,u,a,b;
	first.clear();last.clear();
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&u);
		if(first[u]==0)//记录
		first[u]=i;
		last[u]=i;
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d%d",&a,&b);
		if(first[a]!=0&&first[b]!=0)//这里 first[x] 为 0 说明车站序列里没有编号为 x 的车站，应该输出"NO"
		{
			if(first[a]<last[b])
			printf("YES");
			else
			printf("NO");
		}
		else
		printf("NO");
		printf("\n");
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	work();
	return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定 $n$ 个数 $a_1, a_2, \cdots, a_n$，$m$ 次询问，每次询问给定 $x, y$，问这 $n$ 个数里是否有两个数 $i, j$，满足 $1 \leq i \leq j \leq n$，$a_i = x$，$a_j = y$。多组数据。

## 做法

显然每次暴力枚举是 $O(n^2 mt)$ 的复杂度，其中 $t$ 是数据组数。

考虑预处理。

对于询问 $x, y$，显然如果存在 $i, j$，满足 $1 \leq i \leq j \leq n$，$a_i = x$，$a_j = y$，那么所有 $i^{\prime}, j^{\prime}$ 满足 $i^{\prime} < i$ ，$j^{\prime} > j$，$a_{i^{\prime}} = x$，$a_{j^{\prime}} = y$ 也一定满足原有性质，即 $i^{\prime} \leq j^{\prime}$。

设 $f_i$ 表示 $i$ 在 $n$ 个数中第一次出现的位置，$l_i$ 表示 $i$ 在 $n$ 个数中最后一次出现的位置，若 $f_x \leq l_y$，则存在 $i, j$，否则不存在。

使用 `map` 每组数据预处理，复杂度 $O(\sum (n \log n) + \sum m)$。

---

## 作者：qwq___qaq (赞：0)

因为要从 $a$ 到 $b$，所以只需判断 $a$ 在序列中的最左边是否在 $b$ 在序列中的最右边的左边即可。

注意 $a$、$b$ 有可能不在序列中，并且值域比较大，所以使用 `map` 存储。

---

## 作者：SUNCHAOYI (赞：0)

若干个车站被停靠若干次，第 $i$ 次停靠的站点为 $j$，设 $\forall j \in n$，站点 $j$ 被停靠所对应的集合为 $ {C_i}$。则容易想到，对于每组询问的 $x,y$，若成立则一定满足 $\min \{C_x\} < \max \{C_y\}$。

发现数据范围中 $u_i$ 较大，但是 $n$ 较小，考虑使用 `map <int,int> p1,p2` 来存储每个站点的最小，最大停靠编号。值得注意的是，因为 `unodered_map` 的不稳定性，不要去使用它，可能会导致超时。（好像很多人因为这个，赛后被 hack 疯了）

于是，在询问的时候，只要这两个站点被停靠过并且满足 $\min \{C_x\} < \max \{C_y\}$，就输出 `YES`，否则为 `NO`。上代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map> 
#include <cstring>
#define init(x) memset (x,0,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 2e5 + 5;
const int MOD = 1e9 + 7;
inline int read ();
int t,n,k,a[MAX];
map <int,int> p1,p2;
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	t = read ();
	while (t--)
	{
		n = read ();k = read ();
		p1.clear ();p2.clear ();//多测一定要记得清空！！！
		for (int i = 1;i <= n;++i)
		{
			a[i] = read ();
			p1[a[i]] = (!p1[a[i]]) ? i : min (p1[a[i]],i);
			p2[a[i]] = (!p2[a[i]]) ? i : max (p2[a[i]],i);//一个存最大值，另一个存最小值	
		}
		for (int i = 1;i <= k;++i)
		{
			int x = read (),y = read ();
			if (p1[x] != 0 && p1[y] != 0 && p1[x] < p2[y]) printf ("YES\n");//有解的两个情况都要符合
			else printf ("NO\n");
		} 
	}
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

## 作者：tzyt (赞：0)

题目链接[（CF](https://codeforces.com/problemset/problem/1702/C)，[洛谷）](https://www.luogu.com.cn/problem/CF1702C) | 强烈推荐[博客](https://ttzytt.com/2022/07/CF1702/)中观看。

## 题意：
给你一个长度为 $n (1\le n \le 2 \cdot 10 ^ 5)$ 的数组 $u$。代表所有的火车站。火车只能从左边的站台开到右边的站台。也就是从 $u_1$ 开始，再到 $u_2, \ u_3$，最后到 $u_n$。

现在给你 $k (1\le k \le 2 \cdot 10 ^ 5)$ 个询问，每个包含两个整数 $a_i$ 和 $b_i$，问你是否可以从 $a_i$ 这个站台开始，坐火车到 $b_i$。

比如：$u$ 数组为 $[3,7,1,5,1,4]$，有以下三个询问：
- $a_1 = 3, b_1 = 5$。
  从 $3$ 号站台坐车到 $5$ 号站台是可能的，有以下路径：$[3,7,1,5]$。
- $a_2 = 1, b_2 = 7$
  没有路径可以从 $1$ 号站坐车做到 $7$ 号站台。
- $a_3 = 3, b_3 = 10$
  没有路径可以从 $3$ 号站台坐车到 $10$ 号站台（$10$ 号根本不存在）。 

## 思路：
我们只需要知道某个站台第一次出现的位置和最后一次出现的位置就行了。假设站台 $i$ 第一次出现的位置为 $f_i$，最后一次出现的位置为 $l_i$。并且这时有询问 $a, b$。

那么只要 $f_a < l_b$ 就一定可以从站台 $a$ 坐车到站台 $b$ 了。因为我们知道第一个 $a$ 号站台在最后一个 $b$ 号站台的左边，而火车只能从左向右开，所以可以到达 $b$。

因为要形成一个站台编号到位置的映射，并且站台的编号比较大（$1e9$），站台编号的数量相对较少（$2e5$）。用平常的数组肯定不行，因为需要的空间过大 （$1e9$）。所以有两种办法，离散化（用排序离散化）和使用 `map`。

这里我开了两个 `map`，其中一个是站台编号到第一次出现位置的映射，还有一个，和前面讲的一样，是编号到最后一次出现位置的映射。

然后我们就可以得到如下代码：
## 代码：
因为使用的是 `cin` 和 `cout`，所以可能会因为输入速度比较慢造成 TLE，所以可以取消一下同步。
```cpp
// author: ttzytt (ttzytt.com)
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int a[n + 1];
        map<int, int> v2pos_frt, v2pos_bk;
        //编号->第一次出现， 编号->第二次出现
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            
            if (!v2pos_frt[a[i]]) 
                v2pos_frt[a[i]] = i;
            // 只有第一次才会赋值

            v2pos_bk[a[i]] = i;
        }
        while (k--) {
            int l, r;
            cin >> l >> r;
            int lp = v2pos_frt[l];
            int rp = v2pos_bk[r];
            if (lp <= rp && lp != 0 && rp != 0) {
                // 如果根本没有这个站台，那 lp 或 rp 就会为 0
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}
```
最后，希望这篇题解对你有帮助，如果有问题可以通过评论区或者私信联系我。

---

