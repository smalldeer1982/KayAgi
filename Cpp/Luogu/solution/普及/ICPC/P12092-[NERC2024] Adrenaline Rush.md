# [NERC2024] Adrenaline Rush

## 题目描述

Alice 的朋友是《Adrenaline Rush》赛车比赛的忠实粉丝，总是尽力参加每一场比赛。然而，这一次，比赛是 Alice 观看的。为了确保她的朋友不会错过任何重要细节，Alice 决定记录比赛中赛道上发生的所有事情。

比赛开始前，Alice 首先注意到车子的编号。所有车子按特定顺序排在起跑线上，距离起跑线最近的车编号为 $1$，第二辆车编号为 $2$，以此类推，直到最后一辆车，编号为 $n$。这太方便了！——Alice 想。

比赛开始时，倒计时开始：“三！二！一！开始！” Alice 观察到，车子按照最初的顺序起跑。然而，随着比赛的进行，车子的顺序发生了变化。她记录下每次当一辆车超越另一辆车时，基本上是在赛道上交换了位置。

在比赛过程中，Alice 注意到一件有趣的事情：没有任何一辆车超越另一辆车超过一次。换句话说，对于任何两辆车 $x$ 和 $y$，它们之间最多发生两次超车：$x$ 超越 $y$ 或者 $y$ 超越 $x$。

比赛结束后，Alice 仔细写下了车子的最终顺序 $c_1, c_2, \ldots, c_n$，其中 $c_1$ 代表比赛的冠军。

然而，Alice 的朋友只对最终排名感兴趣，除了最终的顺序，其他记录都被丢弃。由于 Alice 很好奇，她想知道：她在比赛中可能观察到的最长超车序列是什么？你的任务是帮助 Alice 解答这个问题。

## 样例 #1

### 输入

```
3
2 3 1```

### 输出

```
4
2 1
3 1
3 2
2 3```

## 样例 #2

### 输入

```
1
1```

### 输出

```
0```

## 样例 #3

### 输入

```
2
1 2```

### 输出

```
2
2 1
1 2```

# 题解

## 作者：Circle_Table (赞：3)

题目要求我们使超车次数最大，且任何车 $x$ 不应当超越另一辆车 $y$ 超过一次，并且要符合最终以输入的顺序抵达终点。

然后注意到第一组样例的后两行：为了使超车次数最大，这两辆车互相超了一次。再通过观察，可以得出两条结论。在 $i<j$ 的前提下：

- 当 $c_i>c_j$ 时，显然车 $i$ 被车 $j$ 超了一次。但如果车 $j$ 将车 $i$ 再超一次，由于车 $i$ 已经超过一次车 $j$ ，就超不回来了。因此这种情况下超车次数会增加一次。
- 当 $c_i<c_j$ 时，和样例一样，互相超一次。因此这种情况下超车次数会增加两次。

归纳一下：遇到逆序对，超车次数增加一次；遇到正序对，超车次数增加两次。到这里 $m$ 就已经可以求出来了。

至于后面的，由于最终情况下的最后一个车是不会再超了的，所以整个步骤就相当于从后向前进行冒泡排序，但是是从升序到要求的最终顺序。于是思路就出来了，从最后一个要被哪些车超过，慢慢往前排即可。

那么前面求出 $m$ 的过程也就为我们提供了思路，这里也就可以优化掉（事实上本质并没有改变）专门遍历求 $m$ 的过程。思路讲完了，代码如下。

```cpp
#include <bits/stdc++.h>
#define ios ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
int n,m;
int a[1145],p[1145],c[1145];//a指i上的数，p指数字i的位置，c指最终状态
int t,x;
vector<pair<int,int> >v;
//逆序对：超车一次
//正序对：超车了，但又被超回来了（使超车次数最大）
int main(){
	ios;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>c[i];
		a[i]=i;p[i]=i;
	}
//	for(int i=1;i<n;i++){ for(int j=i+1;j<=n;j++){
//			m++;if(c[i]<c[j])m++;
//	} }cout<<m;
//	这一段可直接求出m，但是做完后发现其实不必
	for(int qwq=n;qwq>=1;qwq--){
		t=c[qwq];x=p[t];
		for(int i=x-1;i>=1;i--){
			v.push_back({t,a[i]});
			p[t]=i;
			p[a[i]]=i+1;
			a[i+1]=a[i];
			a[i]=t;
		}
		for(int i=2;i<=qwq;i++){
			v.push_back({a[i],t});
			p[t]=i;
			p[a[i]]=i-1;
			a[i-1]=a[i];
			a[i]=t;
		}
	}m=v.size();
	cout<<m<<'\n';
	for(int i=0;i<m;i++)
		cout<<v[i].first<<' '<<v[i].second<<'\n';
	return 0;
}
```
感谢阅读！

---

## 作者：JIN_LONG (赞：2)

## 思路：
题目大意是给定赛车的最终排名，计算可能的最长超车序列，并输出这些超车事件。

以下是我的思路步骤。

- 首先先定义变量，我代码中的 $n$ 是赛车的数量，数组 $a$ 是用来存储最终排名，数组 $q$ 是用来记录哪些车已经被处理过，结构体数组 $b$ 用来存储超车事件。
- 输入后就是核心算法了，我们首先遍历最终排名数组 $a$ 中的每辆车。
- 在遍历的过程中，对于每辆车进行三个方向的检查，一是检查比 $a_i$ 大的未处理车辆，二是检查比 $a_i$ 大的未处理车辆，三是检查比 $a_i$ 小的未处理车辆，在这过程中记录可能的超车事件。
- 最后输出统计的超车事件数和超车事件即可。

## 代码：

```cpp
#include <bits/stdc++.h>
#define PII pair<int, int>
using namespace std;
PII pp(int x, int y){
	PII p;
	p.first=x,p.second=y; 
	return p;
}
int a[1001],q[1001];
struct jl{
	int x,y;
}b[1000001];
int main(){
	int n,sum=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		for(int j=a[i]+1;j<=n;j++){
			if(!q[j]){
				sum++;
				b[sum].x=j;
				b[sum].y=a[i];
			}
		}
		for(int j=n;j>=a[i]+1;j--){
			if(!q[j]){
				sum++;
				b[sum].x=a[i];
				b[sum].y=j;
			}
		}
		for(int j=a[i]-1;j>=1;j--){
			if(!q[j]){
				sum++;
				b[sum].x=a[i];
				b[sum].y=j;
			}
		}
		q[a[i]]=1;
	}
	cout<<sum<<endl;
	for(int i=1;i<=sum;i++){
		cout<<b[i].x<<' '<<b[i].y<<endl;
	}
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P12092)

题意：有一场赛车比赛，初始排名是 $1$ 到 $n$。每两辆车 $x$ 和 $y$ 之间最多只能有 $x$ 超过 $y$ 和 $y$ 超过 $x$ 两次超车，给定最后排名 $c$，问最多可以有多少次超车。

如果有两辆车的初始相对位置和最终相同（即初始时 $x$ 在 $y$ 前面，最后 $x$ 还是在 $y$ 前面），那么显然它们可以互相超过一次。而如果初始和最终相对位置不同，只能由后面的超过前面的一次。

我们容易想到一种构造方法：每次找到 $c_i$，让 $c_i$ 后面的所有车都超过它一次，再让 $c_i$ 一直往前到第 $i$ 名。可以用一个 $vis$ 数组记录一辆车是否已经到对应位置。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
pii mkp(int x, int y){pii p; p.first = x, p.second = y; return p;}
int n, a[1001], u[1000001], v[1000001], cnt, vis[1001];
signed main(){
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = 1; i <= n; i++){
		for (int j = a[i] + 1; j <= n; j++) if (!vis[j]) u[++cnt] = j, v[cnt] = a[i];//先到最后
		for (int j = n; j >= a[i] + 1; j--) if (!vis[j]) u[++cnt] = a[i], v[cnt] = j;
		for (int j = a[i] - 1; j >= 1; j--) if (!vis[j]) u[++cnt] = a[i], v[cnt] = j;//再到前面
		vis[a[i]] = 1;//已到达，更新vis
	}
	printf("%lld\n", cnt);
	for (int i = 1; i <= cnt; i++) printf("%lld %lld\n", u[i], v[i]);
	return 0;
}
```

---

## 作者：DecemberFox (赞：0)

# P12092 [NERC2024] Adrenaline Rush 题解

## 题目分析

题目要求我们给出一个超车的方案，使得最终到达终点的车辆序列为 $c$，且对于任意一辆车都不能超过任何一辆车两次及以上，求最大的超越次数。

## 解法分析

想要超车的次数最大化，对于每一辆车都要就要尽可能多地超越其余的车。进行一次超车，就相当于调换了两车的相对顺序，那么我们可以比较初始和结束的序列判断途中的超车情况。

对于两辆车 $x,y(x<y)$，若最终仍然是 $x$ 在 $y$ 之前，那么就应该是辆车互相超过对方一次。这样才能使超车次数更大。

若最终 $y$ 在 $x$ 前面，则 $y$ 一定超过了 $x$，且由于 $y$ 只能超过 $x$ 一次，因此 $x$ 一定不会超过 $y$。

此外，题目要求构造一组超车的序列。为保证不重不漏，我们从结果中最后一名开始，它一定可以超过原来在它前面的车，且其余所有车都超过它一次。

对于序列中，就相当于将该车移动到序列的第一位，然后再移动至最后面，移动的过程就是超车的过程。

处理完最后一辆车后，依次向前遍历，同样是超越了它前面的车一次，然后又被剩余的车超过（正好排除了最后一名的车）。

依次类推，最终可以处理完整个序列。代码如下。

```cpp
#include<iostream>
#include<utility>
#include<cstdio>
#include<queue>
namespace SOLVE
{
	typedef long long ll;
	typedef unsigned long long ull;
	typedef __int128 lll;
	typedef unsigned __int128 ulll;
	const int const1=1e3+10;
	int t[const1],rank[const1],now[const1],pos[const1];
	std::queue<std::pair<int,int> > ans;
	void solve()
	{
		int n,i,j,k;
		read(n);
		for(i=1;i<=n;++i)
		{
			read(t[i]);
			rank[t[i]]=now[i]=pos[i]=i;
		}
		for(i=n;i>=1;--i)
		{
			for(j=pos[t[i]];j>1;--j)
			{
				ans.push(std::make_pair(now[j],now[j-1]));
				std::swap(pos[now[j]],pos[now[j-1]]);
				std::swap(now[j],now[j-1]);
			}
			for(j=1;j<rank[t[i]];++j)
			{
				ans.push(std::make_pair(now[j+1],now[j]));
				std::swap(pos[now[j+1]],pos[now[j]]);
				std::swap(now[j+1],now[j]);
			}
		}
		write(ans.size());
		while(!ans.empty())
		{
			write(ans.front().first,' ',ans.front().second);
			ans.pop();
		}
	}
}
int main()
{
	SOLVE::solve();
	return 0;
}
```

---

