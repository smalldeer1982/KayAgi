# Medium Demon Problem (hard version)

## 题目描述

这是该问题的困难版本。两个版本之间的关键区别已用粗体强调。

有一群 $n$ 只蜘蛛聚在一起交换毛绒玩具。一开始，每只蜘蛛手里都有一个毛绒玩具。每年，如果第 $i$ 只蜘蛛至少有一个毛绒玩具，它会把自己的一个毛绒玩具送给第 $r_i$ 只蜘蛛。否则，它会选择不做任何事情。注意，所有毛绒玩具的转移同时进行。在这个版本中，每只蜘蛛在任何时候都可以拥有多个毛绒玩具。

如果今年（在进行交换之前）每只蜘蛛拥有的毛绒玩具数量与去年（交换之前）相同，那么这一年就是稳定的。需要注意的是，第一年不可能是稳定的。

请找出施行直到稳定的第一个年份。

## 说明/提示

对于第二个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 1, 1, 1, 1]$。由于这个数组与去年相同，所以第二年是稳定的。

对于第三个测试用例：

- 第一年，每只蜘蛛拥有的毛绒玩具数量为：$[1, 1, 1, 1, 1]$。接下来进行第一次交换。
- 第二年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 2, 1, 1, 0]$。随后进行第二次交换。
- 第三年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 3, 0, 1, 0]$。随后进行第三次交换。
- 第四年，每只蜘蛛拥有的毛绒玩具数量变为：$[1, 4, 0, 0, 0]$。随后进行第四次交换。
- 第五年，每只蜘蛛拥有的毛绒玩具数量仍为：$[1, 4, 0, 0, 0]$。由于这个阵列与上一年相同，第五年是稳定的。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
5
2
2 1
5
2 3 4 5 1
5
2 1 4 2 3
5
4 1 1 5 4
10
4 3 9 1 6 7 9 10 10 3```

### 输出

```
2
2
5
5
5```

# 题解

## 作者：FishPressedCoins (赞：2)

**拓扑排序加一点点树结构。**

首先是思路。

事实上，无论这个环到底是什么样子、到底有几个，想要有解，环上所有结点的玩具数就必须相等。也就是说，从出题数据确定的那一刻开始，环的结局就已经确定了。所以我们只需要考虑环外的结点即可。

可以通过拓扑排序找到所有的环外结点。可以确定的是，因为它们在环外，它们肯定会呈现出一个或多个树形图结构。我们要做的，就是将这些树的根结点找出来一一比较，玩具最多的那个根结点，就是我们需要的答案。

请注意，根结点的玩具数等于所有子树的和加上本身初始状态的一，也就是这棵树的玩具总数。

```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
//对应数组分别为：路径、入度、礼物个数
int T, N, arr[200010], f[200010], sum[200010], S, n, temp, ans;
vector<int>V;//存储非环结点
queue<int>Q;//筛选非环结点
//4 1 1 5 4
int main()
{
	std::ios::sync_with_stdio(false);
	cin >> T;
	while (T--) {
		cin >> N;
		ans = 0; 
		for (int i = 1; i <= N; i++) {
			cin >> arr[i];
			f[arr[i]]++, sum[i] = 1;//入度、玩具初始化
		}
		
		for (int i = 1; i <= N; i++) {
			if (f[i] == 0)Q.push(i),V.push_back(i);//第一批入度为零的结点入队，同时也是非环结点
		}
		while (!Q.empty()) {//拓扑排序，挑选所有非环结点
			temp = Q.front();
			Q.pop();
			f[arr[temp]]--;
			if (f[arr[temp]] == 0)Q.push(arr[temp]),V.push_back(arr[temp]);
		}

		for (auto t : V) {//将所有非环结点的玩具数分发下去
			sum[arr[t]] += sum[t];
		}
		for (auto t : V) {//统计拥有最多玩具的结点
			ans=max(ans,sum[t]);
		}
		
		//善后工作
		V.clear();
		for (int i = 1; i <= N; i++) {
			arr[i] = 0, f[i] = 0, sum[i] = 0;
		}
		cout << ans+2 << '\n';//从第二年开始，记得加2
	}
	return 0;
}
```

---

## 作者：Peaky (赞：1)

**本片题解将同时阐述 Easy version 与 hard version 的区别。**
### 思路
考虑拓扑。  
容易发现本题的图为**基环森林**，对于两题而言，**若图中只剩下了环，再如何传递，都不会发生变化了。** 
显然，两题只剩环的时间是不同的。  
以下，将环视为树根而言。  
- 对于第一题，由于每一个节点只会保留一个信息，那么，每个节点最后一个收到的信息一定是**最长链给到的信息**，那么，问题就转换成的找环上最长链。  
- 对于第二题，收到的信息是不限的，那么，他将收到**来自每一颗子树的大小的信息**。又由于他每次只会传递一个信息，那么他将信息传递完的时间是**各子树大小加它本身**。

如果使用数学语言会更为直观。  
对于第一题，一个结点的贡献为：
$$
dp_u=\max(dp_v)+1
$$
对于第二题，一个结点的贡献为：
$$
dp_u=\sum{dp_v}+1
$$
其中，$v$ 为能够一步到达 $u$ 的节点。  
仅仅是一个符号的区别。  
如果一个点的答案更新完了，那么他也就可以更新其他节点。显而易见，本题应使用拓扑。
### AC code
**[CF2044G1](https://www.luogu.com.cn/problem/CF2044G1)：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int t,n,r[N],d[N],cnt[N],inq[N],ans;
void Solve(){
	cin>>n; ans=0;
	for(int i=1;i<=n;i++) inq[i]=0,d[i]=0,cnt[i]=0;
	for(int i=1;i<=n;i++) cin>>r[i],inq[r[i]]++;
	queue<int> q;
	for(int i=1;i<=n;i++) if(!inq[i]) q.push(i);
	while(!q.empty()){
		int u=q.front(),v=r[u]; q.pop();
		ans=max(ans,++d[u]);
		inq[v]--; d[v]=d[u];
		if(!inq[v]) q.push(v);
	}
	cout<<ans+2<<"\n";
}
signed main(){
	cin>>t;
	while(t--) Solve();
	return 0;
}
```
**[CF2044G2](https://www.luogu.com.cn/problem/CF2044G2)：**
```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N=2e5+10,inf=0x3f3f3f3f,mod=1e9+7;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef long long ll;
/*

*/
int t,n,r[N],d[N],cnt[N],inq[N],ans;
void Solve(){
	cin>>n; ans=0;
	for(int i=1;i<=n;i++) inq[i]=0,d[i]=0,cnt[i]=0;
	for(int i=1;i<=n;i++) cin>>r[i],inq[r[i]]++;
	queue<int> q;
	for(int i=1;i<=n;i++) if(!inq[i]) q.push(i);
	while(!q.empty()){
		int u=q.front(),v=r[u]; q.pop();
		ans=max(ans,++d[u]);
		inq[v]--; d[v]+=d[u];
		if(!inq[v]) q.push(v);
	}
	cout<<ans+2<<"\n";
}
signed main(){
	cin>>t;
	while(t--) Solve();
	return 0;
}
```

---

## 作者：Kexi_ (赞：0)

本题解默认已经通过了简单版。

## 题意简述

有 $n$ 个蜘蛛，初始时每只有一个玩具。每个蜘蛛有一个传递目标，每单位时间传递一次，求什么时候蜘蛛的玩具数量与上一单位时间的全部一样。

## 思路

这题与简单版的区别很小，由于这题蜘蛛拿到多的玩具不会扔，然而一次只能给一个玩具，那么它要把所有玩具给自己唯一的传递目标就需要传子树大小和次。

所以在拓扑找无入度点时推一下每个点的子树和就好啦，其他与简单版无区别。


```cpp
	#include <bits/stdc++.h>
	#define N 200005
	#define ri register int
	using namespace std;
	int t,n,ans;
	int in[N],siz[N];
	vector<int> son[N];
	namespace G
	{
		using namespace std;
		inline int topsort()
		{	
			queue<int> q;
			for(ri i=1;i<=n;i++) {if(!in[i]){q.push(i);}}
			while(!q.empty())
			{	
				int now=q.front(); q.pop();
				for(ri i=0;i<son[now].size();i++)
				{	int to=son[now][i];
					siz[to]+=siz[now];
					ans=max(ans,siz[now]);
					if(!--in[to]) q.push(to);
				}
			}
			return ans+2;
		}
		void main()
		{	ans=0;
			cin>>n;
			for(ri i=1;i<=n;i++)
			{
				siz[i]=1; in[i]=0;
			 } 
			for(ri i=1;i<=n;i++)
				son[i].clear();
			for(ri i=1;i<=n;i++){int a; cin>>a; son[i].push_back(a); in[a]++;}
			cout<<topsort()<<'\n';
		}
	}
	int main()
	{
		cin>>t;
		while(t--){G::main();}
		return 0;
	}
```

---

## 作者：wflhx2011 (赞：0)

这篇题解将同时说明两个版本的解法。

要让一次变化后状态与上一次一样，也就是形成一个环，且只有环内的点有玩具。

因为是第 $i$ 人给第 $r_i$ 人，考虑从 $i$ 向 $r_i$ 连边建图，之后用拓扑排序或搜索找环。

找完环后，需要找出除环上的点都没有玩具的经过时间，这也是两个题的不同之处：

- 对于简单版本，因为每个点最多一个玩具，考虑 dp 求出，设 $v$ 表示连向了 $u$ 的点，状态转移应为 $dp_u=\max\{dp_v\}+1$，也就是环外的最长链。

- 对于困难版本，每个点可以有多个玩具，每次仍只能传递一个，仍用 dp，但每个点的值应是连向它的点的值的和，即 $dp_u=\sum dp_v+1$。

这个 dp 在拓扑排序时顺便就可以处理。

G1 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[200005];
int in[200005],f[200005],n,ans;
queue<int> q;
void topo()
{
	ans=0;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			in[v]--;
			ans=max(ans,++f[u]);
			f[v]=max(f[u],f[v]);
			if(!in[v])
				q.push(v); 
		}
	}
	cout<<ans+2<<"\n";
	return ; 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		while(!q.empty())
			q.pop();
		cin>>n;
		for(int i=1;i<=n;i++)
			in[i]=0,f[i]=0,g[i].clear();
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			g[i].push_back(x);
			in[x]++;
		}
		topo();
	}
 	return 0;
}
```

G2 代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> g[200005];
int in[200005],f[200005],n,ans;
queue<int> q;
void topo()
{
	ans=0;
	for(int i=1;i<=n;i++)
		if(!in[i])
			q.push(i);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=0;i<g[u].size();i++)
		{
			int v=g[u][i];
			in[v]--;
			ans=max(ans,++f[u]);
			f[v]+=f[u];  
			if(!in[v])
				q.push(v); 
		}
	}
	cout<<ans+2<<"\n";
	return ; 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		while(!q.empty())
			q.pop();
		cin>>n;
		for(int i=1;i<=n;i++)
			in[i]=0,f[i]=0,g[i].clear();
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			g[i].push_back(x);
			in[x]++;
		}
		topo();
	}
 	return 0;
}
```

---

