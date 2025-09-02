# Game on Ranges

## 题目描述

Alice and Bob play the following game. Alice has a set $ S $ of disjoint ranges of integers, initially containing only one range $ [1, n] $ . In one turn, Alice picks a range $ [l, r] $ from the set $ S $ and asks Bob to pick a number in the range. Bob chooses a number $ d $ ( $ l \le d \le r $ ). Then Alice removes $ [l, r] $ from $ S $ and puts into the set $ S $ the range $ [l, d - 1] $ (if $ l \le d - 1 $ ) and the range $ [d + 1, r] $ (if $ d + 1 \le r $ ). The game ends when the set $ S $ is empty. We can show that the number of turns in each game is exactly $ n $ .

After playing the game, Alice remembers all the ranges $ [l, r] $ she picked from the set $ S $ , but Bob does not remember any of the numbers that he picked. But Bob is smart, and he knows he can find out his numbers $ d $ from Alice's ranges, and so he asks you for help with your programming skill.

Given the list of ranges that Alice has picked ( $ [l, r] $ ), for each range, help Bob find the number $ d $ that Bob has picked.

We can show that there is always a unique way for Bob to choose his number for a list of valid ranges picked by Alice.

## 说明/提示

In the first test case, there is only 1 range $ [1, 1] $ . There was only one range $ [1, 1] $ for Alice to pick, and there was only one number $ 1 $ for Bob to pick.

In the second test case, $ n = 3 $ . Initially, the set contains only one range $ [1, 3] $ .

- Alice picked the range $ [1, 3] $ . Bob picked the number $ 1 $ . Then Alice put the range $ [2, 3] $ back to the set, which after this turn is the only range in the set.
- Alice picked the range $ [2, 3] $ . Bob picked the number $ 3 $ . Then Alice put the range $ [2, 2] $ back to the set.
- Alice picked the range $ [2, 2] $ . Bob picked the number $ 2 $ . The game ended.

In the fourth test case, the game was played with $ n = 5 $ . Initially, the set contains only one range $ [1, 5] $ . The game's turn is described in the following table.

 Game turnAlice's picked rangeBob's picked numberThe range set afterBefore the game start $  \{ [1, 5] \}  $ 1 $ [1, 5] $  $ 3 $  $  \{ [1, 2], [4, 5] \} $ 2 $ [1, 2] $  $ 1 $  $  \{ [2, 2], [4, 5] \}  $ 3 $ [4, 5] $  $ 5 $  $  \{ [2, 2], [4, 4] \}  $ 4 $ [2, 2] $  $ 2 $  $  \{ [4, 4] \}  $ 5 $ [4, 4] $  $ 4 $  $  \{ \}  $ (empty set)

## 样例 #1

### 输入

```
4
1
1 1
3
1 3
2 3
2 2
6
1 1
3 5
4 4
3 6
4 5
1 6
5
1 5
1 2
4 5
2 2
4 4```

### 输出

```
1 1 1

1 3 1
2 2 2
2 3 3

1 1 1
3 5 3
4 4 4
3 6 6
4 5 5
1 6 2

1 5 3
1 2 1
4 5 5
2 2 2
4 4 4```

# 题解

## 作者：deviance (赞：4)

## 前言
修改了 $16$ 次，每个标点 $\LaTeX$ 都得到了处理，格式应该没问题。
### 本篇题解已解决以下问题：
1. 【中文】与【英文、数字或公式】之间未以半角空格隔开；
1. 【中文标点符号】与【英文、数字、公式或汉字】之间添加多余空格；
2. 数学公式外应使用中文全角标点；
1. 出现大量无关内容，应只包含题目相关内容；
1. $\LaTeX$ 使用不规范等问题；

蒟蒻第一次发题解，求过qwq。

[~~更优质的阅读环境~~](https://www.cnblogs.com/deviance/p/18102628)

------------

## 题意理解（建议先自己把原题描述看一遍再来看我的理解）

有一个集合，这个集合的元素是区间，一开始集合里只有一个元素就是 $[1,n]$ 的区间，对这个集合我们可以选择其中的一个元素（区间），然后在区间内选一个数 $d$，以  $[l,d-1]$  和 $[d+1,r]$ 这两个区间替换掉我们选择的这个区间（ $l$   和 $r$ 分别是我们从集合里面选择出来的这个元素的左端点和右端点)。当然这两个新区间必须存在才行，左端点小于等于右端点。如果不存在就不加入到集合中。我们选择 $n$ 个数后，集合内元素个数为 $0$，也就是区间个数为 $0$ 时结束。

现在题目给出的是每次操作时选择的那个区间，要你推出对应的d。比如现在有一个集合 $S$，里面有一个元素，区间 $[1,6]$。
 
 -  第一次操作，选 $[1,6]$，$d$ 取 $2$，对 $S$，删去 $[1,6]$，加入 $[1,1]$ 和 $[3,6] $，现 $S={[1,1],[3,6]}$。

   - 第二次操作，选 $[1,1]$ 进行操作，$d$ 取 $1$，对 $S$，删去 $[1,1]$，现 $S={[3,6]}$。

  - 第三次操作，选 $[3,6]$ 进行操作，$d$ 取 $6$，对 $S$，删去 $[3,6]$，加入 $[3,5]$，现 $S={[3,5]}$。

  - 第四次操作，选 $[3,5]$ 进行操作，$d$ 取 $3$，对 $S$，删去 $[3,5]$，加入 $[4,5]$，现 $S={[4,5]}$。

  - 第五次操作，选 $[4,5]$ 进行操作，$d$ 取 $5$，对 $S$，删去 $[4,5]$，加入 $[4,4]$，现 $S={[4,4]}$。

   - 第六次操作，选 $[4,4]$ 进行操作，$d$ 取 $4$，对 $S$，删去 $[4,4]$，现 $S$ 为空，游戏结束。


现题目打乱顺序的给出 $[1,6], [1,1], [3,6], [3,5],   [4,5], [4,4] $ 这六个区间，要求你推出每个区间对应的 $d$，并输出，可以不按照题目的顺序。

## 题解

看似很复杂的一道题，我们可以从简单的角度入手，对于左右端点相等的区间, $d$  只能选择端点值，所以我们先确定所有左右端点相等区间对应的 $d$ 值。其实我们可以简单的理解为每次操作删掉 $[1,n]$ 之间的一个数，所以删过的数就不可能再次出现，也就是每个区间对应的 $d$ 值都不相同。所以我们标记掉出现过的 $d$。于是我们有了这样一个思路，随着迭代的进行被标记的 $d$ 越来越多，对于区间越来越大，但是找到       $d$ 的难度相当，因为区间越大时被标记的   $d$ 就越多。我们将区间以从小到大的顺序排列，对于长度为 $1$ 的区间直接找到 $d$ 值，对于长度为 $2$ 的区间只有两个可能的 $d$ 值，但此前我们标记了一个 $d$ 值，所以对于长度为 $2$ 的区间也只有一个确定的 $d$ 值，以此类推。所有的区间我们都能找到一个 $d$ 值与之对应。

```

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define LM LLONG_MAX
#define IM INT_MAX
#define N 1001
struct pair1
{
	int l;
	int r;
	int len;
	int d=0;
};
bool cmp(pair1 a,pair1 b)
{
	return a.len<b.len;
}
 
int main()
{
	int t;
	
	cin>>t;
	while(t--)
    {
		bool vis1[N]={0};
		int n,ans[N];
		cin>>n;
		pair1 a[N];
		for(int i=1;i<=n;i++)
        {
			cin>>a[i].l>>a[i].r;
			a[i].len=a[i].r-a[i].l;
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)
        {
			if(a[i].l==a[i].r)
            {
				a[i].d=a[i].l;
				vis1[a[i].d]=true;
			}
			else 
            {
				for(int j=a[i].l;j<=a[i].r;j++)
                {
					if(!vis1[j])
                    {
						a[i].d=j;
						vis1[j]=true;
					}
				}
			}
		}
		for(int i=1;i<=n;i++) cout<<a[i].l<<" "<<a[i].r<<" "<<a[i].d<<endl;
	}
}
```

---

## 作者：Legitimity (赞：3)

赛场上没看见 $\sum n\leq1000$，于是就有个这个 $O(Tn\log n)$ 的做法。



------------
首先按照区间长度从大到小排序（相当于一次拓扑），然后考虑对于一个区间 $[l_i,r_i]$，在满足 $len_j<len_i $ 的所有区间中：

1. 若不存在 $l_j=l_i$，则当前取了 $l_j$  这个数，分成 $[l_i+1,r_i]$ 一个区间。
2. 若不存在 $r_j=r_i$，则当前取了 $r_j$  这个数，分成 $[l_i,r_i-1]$ 一个区间。
3. 若同时存在 $l_j=l_i$ 和 $r_{j^{\prime}}=r_i$，则当前取了 $r_j+1$ 这个数，分成 $[l_j,r_j]$ 和 $[l_{j^{\prime}},r_{j^{\prime}}]$ 两个区间。

因为拓扑排序过，可以用 bfs 进行这个过程，然后每次进行上述 $3$ 个判断，这些判断可以开两个 vector 维护，初始时将所有区间都塞进去，每次懒惰删除即可。

复杂度瓶颈在排序，不过换成基排之后就能线性。

[code](https://www.luogu.com.cn/paste/83thr75h)

---

## 作者：Storm_Lightning (赞：2)

# 题解：CF1623B Game on Ranges

## 题目大意

在区间 $[1,n]$ 中删一个数，分成两个区间再放入，重复 $n$ 次直到删完。给出选出的区间，输出给出的区间和在此区间删除的数。

## 思路分析

- 算法：结构体排序和贪心

- 贪心策略：因为每次只能删一个数，所以把大区间排在前面。然后对比下一个小区间找出删除的数，如果两个区间相等，那就选最小的区间，当然也可以删除自己本身。

## 核心代码

```cpp
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++)
{
	if(a[i].l==a[i+1].l&&i!=n) wzh[a[i].num]=a[i+1].r+1;
	else if(a[i].r==a[i+1].r&&i!=n) wzh[a[i].num]=a[i+1].l-1;
	else if(a[i].l==a[i].r) wzh[a[i].num]=a[i].l;
}
```

---

## 作者：封禁用户 (赞：1)

思路：排序（结构体排序）和贪心。

不会结构体排序？[戳我](https://www.luogu.com.cn/paste/qqrdsu1b)！

先结构体排序，删过的数就不可能再次出现，也就是每个区间 $[1,r]$ 对应的 $d$ 值都不相同，时间复杂度一眼便知 $\mathcal O(n^2)$。

核心代码（仅供参考）：
```
struct Node
{
	int l,r,len,d=0;
};
Node a[maxn];
bool cmp(Node a,Node b)
{
	return a.len<b.len;
}
for(int i=1;i<=n;i++)
        {
			cin>>a[i].l>>a[i].r;
			a[i].len=a[i].r-a[i].l;
		}
		sort(a+1,a+1+n,cmp);
```

---

## 作者：Haoyue_06432 (赞：1)

~~太久没写题解了掉橙了水一篇~~

主要是翻译题目很奇怪很绕口一开始没看懂，大意是在区间 $[1,n]$ 中一个删数，分成两个区间（也有可能删了头或尾分成一个）再放入，重复 $n$ 次直至删完。然后给出选出的区间（不一定按顺序），输出给出的区间和在此区间删除的数。

一看到就知道排序，按头尾排出区间，大区间在前面，因为每次只能删一个数，因此对比下一个小区间找出删除的数，如果区间左右相等，即为最小区间，就能删除本身。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define maxn 1000005
#define inf 1e18
using namespace std;
struct interval
{
	ll l,r,num;
}a[maxn],b[maxn];
ll t,n,ans[maxn];
bool cmp(interval a,interval b)
{
	if(a.l!=b.l)return a.l<b.l;
	else return a.r>b.r;
}
int main()
{
	cin>>t;
	while(t)
	{
		t--;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].l>>a[i].r; 
			a[i].num=i;
			b[i]=a[i];
		}
		sort(a+1,a+1+n,cmp);
		cout<<endl;
		for(int i=1;i<=n;i++)
		{
			if(a[i].l==a[i+1].l&&i!=n)ans[a[i].num]=a[i+1].r+1;
			else if(a[i].r==a[i+1].r&&i!=n)ans[a[i].num]=a[i+1].l-1;
			else if(a[i].l==a[i].r)ans[a[i].num]=a[i].l;
		}
		for(int i=1;i<=n;i++)cout<<b[i].l<<" "<<b[i].r<<" "<<ans[i]<<endl;
	}
	return 0;
}

```


---

## 作者：ArrogHie (赞：1)

## 题意

对于一个区间 $[l,r]$，你可以选择其中一个数 $k$，然后删除 $[l,r]$ 这个区间。若 $l\leq k-1$ 则建立 $[l,k-1]$ 区间，若 $k+1\leq r$ 则建立 $[k+1,r]$ 区间。

初始有一个 $[1,n]$ 的区间，它将不断执行上述操作直到区间全部删除，给出过程中出现的所有区间，问出现的所有区间中选择的 $k$ 分别是哪些。

## 题解

递归。

因为每个区间只会被分一次，所以对于一个区间 $[l,r]$，枚举 $i$ ，若 $[l,i-1],[i+1,r]$ 都出现过（如果能建立的话），那么这个区间选择的数就是 $i$，之后递归解决 $[l,i-1],[i+1,r]$ 即可。

---

## 作者：King_duck (赞：0)

题目大意是在区间 $[1,n]$ 中删一个数，分成两个区间再放入，重复 $n$ 次直到删完。给出选出的区间，输出给出的区间和在此区间删除的数。

一眼排序和贪心，首先按头尾排出区间，因为每次只能删一个数，所以把大区间排在前面，然后对比下一个小区间找出删除的数，如果两个区间相等，那就是最小区间，可以删除本身。

上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
struct node{
	int l,r,num;
}a[N],b[N];
bool cmp(node a,node b)
{
	if(a.l!=b.l)
	{
		return a.l<b.l;
	}
	else 
	{
		return a.r>b.r;
	}
}
int t,n,ans[N];
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].l>>a[i].r; 
			a[i].num=i;
			b[i]=a[i];
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			if(a[i].l==a[i+1].l&&i!=n)
			{
				ans[a[i].num]=a[i+1].r+1;
			}
			else if(a[i].r==a[i+1].r&&i!=n)
			{
				ans[a[i].num]=a[i+1].l-1;
			}
			else if(a[i].l==a[i].r)
			{
				ans[a[i].num]=a[i].l;
			}
		}
		for(int i=1;i<=n;i++)
		{
			cout<<b[i].l<<" "<<b[i].r<<" "<<ans[i]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：_little_Cabbage_ (赞：0)

# CF1623B Game on Ranges 题解
~~[博客食用体验更佳](https://www.luogu.com.cn/blog/958804/solution-cf1623b)~~

这是一道排序、贪心题。

我们记 $a_{il}$ 为 $a_i$ 的左端点，$a_{ir}$ 为 $a_i$ 的右端点。

我们可以发现，对于两个区间，如果左端点 $l$ 不同，就对 $l$ 进行从小到大排序，否则就对 $r$ 进行从大到小排序。

这样对于左端点相同的所有区间，区间长度更长的会排在更前面了。

由于区间长度更长的会排在更前面，所以对于区间 $i$，与他左端点相同的区间一定都是由它分裂出来的，也就是 $[a_{il},a_{ir}-x]$，即 $l$ 相同，$r$ $\le a_{ir}-1$。

对于所有左端点相同的区间组的最后一个，直接输出 $a_{il},a_{ir},a_{il}$ 就行了，对于其他的，我们可以发现，新的分裂点就是 $a_{i+1r}+1$，所以我们直接输出 $a_{il},a_{ir},a_{i+1r}+1$ 就行了。

AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int l,r;
}a[1000100];
bool cmp(node a,node b)
{
	if(a.l!=b.l)
	{
		return a.l<b.l;
	}
	else
	{
		return a.r>b.r;
	}
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			a[i].l=l;
			a[i].r=r;
		}
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			int l=a[i].l,r=a[i].r,ans;
			if(i<n&&a[i].l==a[i+1].l)
			{
				ans=a[i+1].r+1;
			}
			else
			{
				ans=a[i].l;
			}
			printf("%d %d %d\n",l,r,ans);
		}
	}
}
```
[AC 记录](https://www.luogu.com.cn/record/142062724)

---

## 作者：liuyuanpei (赞：0)

本题考查结构体排序和贪心。

$O(n^2)$ 方法比较好想，先结构体排序，删过的数就不可能再次出现，也就是每个区间对应的 $d$ 值都不相同。记得要保存数据，还原答案。

### 主要代码:
```cpp
struct node{//结构体
	int l,r;
	int cnt,ans;
}a[100000];

for(int i=1;i<=n;i++){
	if(a[i].l==a[i].r){//已经确定的数
		a[i].ans=a[i].l;
		tt[a[i].ans]=1; 
	}
	else{
		for(int j=a[i].l;j<=a[i].r;j++)//找第一个没选的数
			if(tt[j]==0){
				a[i].ans=j;
				tt[j]=1;
			}
	}
}
for(int i=1;i<=n;i++){//还原 
	for (int j=1;j<=n;j++){
		if (a[i].l==pp[j][1]&&a[i].r==pp[j][2]) {
			pp[j][3]=a[i].ans;
			break;
		}
	}
}
```
但还原答案花了太长时间，那么可以看看这个方法：

首先，数据给出的是 Alice 取出的区间，问取出的区间中那个数被拿走了。

可以对所有区间排个序，排序的规则为：

1. 当左端点不同时，按左端点从小到大排序。
2. 当左端点相同时，按右端点从大到小排序。

排序之后我们就可以发现一个规律：对于左端点相同的所有区间，区间长度更长的会排在更前面。

这样一来，我们直接遍历一遍排序后的数组。

如果下一条区间的左端点和当前区间左端点相同，因为越长的区间会排在越前面，下一条区间一定是由当前区间分割出来的。

并且选取的分割点，刚好就是下一条区间的右端点 $+1$。

这种情况下直接输出当前区间的左右端点、以及得到的分割点即可。

而当下一条区间的左端点和当前区间左端点不同时，当前区间就一定是这个左端点能够分割出的最后一个区间了。

此时一定可以直接在当前区间的左端点做一次分割。

因此输出当前区间的左右端点，然后再输出一遍当前区间左端点即可。

### 代码:
```cpp
# include <iostream>
# include <cmath>
# include <cstring>
# include <string>
# include <algorithm>
# include <stack>
# include <queue>
# include <set>
# include <map>
using namespace std;
struct node{//结构体
	int l,r;
	int id,ans;
}a[100005],b[100005];
bool tt[100005];
bool cmp(node a,node b){//排序
	if((a.r-a.l)!=(b.r-b.l)) return (a.r-a.l)<(b.r-b.l);
	return a.l<b.l;
}
int main(){
	int t;
	cin >>t;
	while(t--){
		memset(tt,0,sizeof(tt));//清空桶 
		int n;
		cin >>n;
		for(int i=1;i<=n;i++) {//读入 
			cin >>a[i].l>>a[i].r;
			a[i].id=i;
		}
		sort(a+1,a+n+1,cmp);//排序 
		for(int i=1;i<=n;i++) {
			for(int j=a[i].l,k=a[i].r;j<=k;j++,k--) {
				if(!tt[j]) {//从两头向中间找区间内第一个没取的 
					tt[j]=1;
					a[i].ans=j;
					continue;
				}
				if(!tt[k]) {
					tt[k]=1;
					a[i].ans=k;
					continue;
				}
			}
			b[a[i].id].l=a[i].l;
			b[a[i].id].r=a[i].r;
			b[a[i].id].ans=a[i].ans;//优化，直接赋值 
		}
		for(int i=1;i<=n;i++) 
			cout <<b[i].l<<" "<<b[i].r<<" "<<b[i].ans<<endl;
		cout <<endl;
	}
	return 0;
}
```


---

## 作者：GaoKui (赞：0)

首先对所有区间排个序，排序的规则为：

1. 当左端点不同时，按左端点从小到大排序。
1. 当左端点相同时，按右端点从大到小排序。

------------

排序之后我们就可以发现一个规律：
对于左端点相同的所有区间，区间长度更长的会排在更前面。

这样一来，我们直接遍历一遍排序后的数组。

如果下一条区间的左端点和当前区间左端点相同，因为越长的区间会排在越前面，下一条区间一定是由当前区间分割出来的。

并且选取的分割点，刚好就是下一条区间的右端点 $+1$。

这种情况下直接输出当前区间的左右端点、以及得到的分割点即可。


------------


而当下一条区间的左端点和当前区间左端点不同时，当前区间就一定是这个左端点能够分割出的最后一个区间了。

此时一定可以直接在当前区间的左端点做一次分割。

因此输出当前区间的左右端点，然后再输出一遍当前区间左端点即可。


------------



```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAX = 1020;

typedef struct Range // 把范围封装成一个结构体
{
    int l, r;

    bool operator<(const Range &rhs) const
    {
        if (l != rhs.l) // 排序时的标准：首先左端点越小的越在前
        {
            return l < rhs.l;
        }
        else // 齐次右端点越大的越在前，也可以理解为长度大的范围在前
        {
            return r > rhs.r;
        }
    }
}Range;


int n;
Range arr[MAX];

void Solve(void)
{
    cin >> n;
    for (int i = 0; i < n; i++) // 输入
    {
        cin >> arr[i].l >> arr[i].r;
    }

    sort(arr, arr + n); // 按照给定规则排序

    for (int i = 0; i < n; i++)
    {
        // 如果下一个和当前的左端点相同，说明下一个是由当前的分割出来的
        if (i < n - 1 && arr[i + 1].l == arr[i].l)
        cout << arr[i].l << ' ' << arr[i].r << ' ' << arr[i + 1].r + 1 << '\n';
        // 否则的话，当前已经是之前一堆所分割出来的最后一个范围，直接在左端点切割
        else
        cout << arr[i].l << ' ' << arr[i].r << ' ' << arr[i].l << '\n';
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        Solve();
    }

    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

虽然题目描述挺复杂的，但是我们可以从简单的角度入手。

可以简单的理解为每次操作删掉 $[1,n]$ 之间的一个数，所以删过的数就不可能再次出现，也就是每个区间对应的 $d$ 值都不相同。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1400;
int T,n,ans[maxn];
struct Node
{
	int l,r,len,num=0;
};
Node a[maxn];
bool cmp(Node a,Node b)
{
	return a.len<b.len;
}
int main()
{
	cin>>T;
	while(T--)
	{
		bool p[maxn]={0};
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i].l>>a[i].r;
			a[i].len=a[i].r-a[i].l;
		}
		sort(a+1,a+1+n,cmp);
		for(int i=1;i<=n;i++)
		{
			if(a[i].l==a[i].r)
			{
				a[i].num=a[i].l;
				p[a[i].num]=true;
			}
			else
			{
				for(int j=a[i].l;j<=a[i].r;j++)
				{
					if(!p[j])
					{
						a[i].num=j;
						p[j]=true;
					}
				}
			}
		}
		for(int i=1;i<=n;i++)
		{
			cout<<a[i].l<<" "<<a[i].r<<" "<<a[i].num<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：PosVII (赞：0)

[CF1623系列](https://www.luogu.com.cn/blog/271260/cf1623-bi-sai-ji-lu)

可以发现每个区间有且仅有一个分割方式。

发现 $n \leq 1000$，又已知最开始的区间一定是 $[1,n]$，直接对于每个区间暴力查找分割的点即可。

时间复杂度 $\mathbin{\mathrm{O(n^2)}}$。

[Code](https://codeforces.com/contest/1623/submission/146893531)

---

## 作者：RicardoLu (赞：0)

# CF1623B

## 思路

提示1：考虑 Bob 选取的每个数字是在哪个 Alice 选择过的区间中被选择的。

提示2：数字 $i$ 一定是在包含数字 $i$ 的**最小区间**被选取的。

## 证明（反证法）：

* 假设在包含数字 $i$ 的最小区间为 $[l, r]$，选取的不是数字 $i$。
* 分裂出的区间包含数字 $i$，分裂前的区间 $[l, r]$ 不是最小区间，矛盾。
* 因此必须在包含数字 $i$ 的最小区间为 $[l, r]$ 选取数字 $i$。

## 算法思路

* 枚举 Bob 要选择的数字 $i$
  * 枚举 Alice 选择的所有区间
    * 找到包含数字 $i$ 的最小的区间 $[l, r]$，输出 $l, r, i$

## 代码
```
const int N = 1000;
 
int n;
int l[N], r[N];
 
void Solve() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> r[i];
  }
  for (int i = 1; i <= n; i++) {  // 枚举 Bob 要选择的每个数字
    int len = n + 1, pos;  // len 表示最小区间长度，pos 表示最小区间下表
    for (int j = 0; j < n; j++) {  // 枚举 Alice 选择的每个区间
      if (l[j] <= i && i <= r[j] && r[j] - l[j] + 1 < len) {  // 如果区间包含数字 i并且区间更小
        len = r[j] - l[j] + 1;
        pos = j;
      }
    }
    cout << l[pos] << ' ' << r[pos] << ' ' << i << endl;
  }
}
```


---

