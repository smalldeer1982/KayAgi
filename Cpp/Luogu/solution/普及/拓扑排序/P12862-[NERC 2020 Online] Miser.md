# [NERC 2020 Online] Miser

## 题目描述

在某所非传统大学中，食堂将在 $n$ 天后举行开业仪式。在尚未开放的食堂门前，有一块标牌显示着距离开业的天数。

对于这 $n$ 天中的每一天，食堂主管都知道当天会来学校并看到标牌的所有人员名单。主管需要每天选择一个标牌数字，并确保每个来校人员看到的数字是递减的。主管是个典型的**吝啬鬼**，希望尽可能少地订购不同数字的标牌。你的任务是帮助主管计算出最少需要订购多少种不同的标牌。

以第一个测试用例为例：人员 $1$ 在第 $1$、$2$ 和 $5$ 天来校，人员 $2$ 在第 $2$、$3$ 和 $4$ 天来校。主管可以仅订购四个标牌，数字分别为 $1$、$2$、$3$ 和 $4$：在第 $5$ 和 $4$ 天放置数字 $1$ 的标牌，第 $3$ 天放置数字 $2$，第 $2$ 天放置数字 $3$，第 $1$ 天放置数字 $4$。这样，人员 $1$ 将依次看到 $4$、$2$ 和 $1$，人员 $2$ 将依次看到 $3$、$2$ 和 $1$。


## 说明/提示

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1 1
2 1 2
1 2
1 2
1 1```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1 1
1 1
1 1
1 1
1 1```

### 输出

```
5```

# 题解

## 作者：MonKeySort_ZYczc (赞：5)

糖上加糖。本来本文第一段是这样的：
> 本来一眼差分约束，最长路打了个 SLF 优化 SPFA，2s 都 T 飞了，然后发现自己唐了。

其实本题如果差分约束做的话连完边是 DAG，拓扑排序就行，还吐槽 SPFA，唐。
## 思路一
### 思路流程  
本题答案显然具有单调性，因为如果 $k$ 块标牌是够的，再多几块吃灰一定没问题，只是牢主管不高兴而已。考虑二分答案。  

设此时二分的答案为 $k$，统计每天来的每个人之前看到过的数字的最小值，设其值为 $minn$，然后这一天就只能放出上面写着 $minn-1$ 的牌子。  
当然，如果 $minn=1$，也就是今天没办法在放出牌子时，该情况一定不行，直接返回。  
初始每个人看到过的数字的最小值设为 $k+1$ 即可。  
**注意**：这里每个人编号上界不一定为 $n$，要初始化到 $10^5$。  

时间复杂度为 $O(V\log n+\sum k\log n)$，其中 $V=10^5$，$V\log n$ 是二分 check 函数初始化的时间复杂度。  
### 代码实现
变量命名还是很丑的。  
有点慢，有几个点跑了十几毫秒。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,mx[N];
vector<int>v[N];
bool check(int k)
{
	for(int i=1;i<=100000;i++) mx[i]=k+1;
	for(int i=1;i<=n;i++)
	{
		int t=0x3f3f3f3f;
		for(int j=0;j<v[i].size();j++) t=min(t,mx[v[i][j]]);
		if(t==1) return 0;
		for(int j=0;j<v[i].size();j++) mx[v[i][j]]=t-1;
	}
	return 1; 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int m;cin>>m;
		for(int j=1;j<=m;j++)
		{
			int a;cin>>a;v[i].push_back(a);
		}
	}
	int l=1,r=n,mid;
	while(l<r)
	{
		mid=l+r>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l;
}

```
## 思路二
### 思路流程
类差分约束。  
先统计每个人都有哪几天来了，用 vector 数组存储。  
对于第 $i$ 个人，如果有存在 $j<k$，且这个入在第 $j$ 天来过之后下一次就是在第 $k$ 天来，从 $j$ 向 $k$ 连一条长度为 1 的有向边。  
容易发现由于 $j<k$，这个图中没有环，直接拓扑排序，从每个入度为 0 的点开始的最长路，再统计最长最长路即为答案。  
时间复杂度 $O(V+\sum k+n)$，$V$ 含义同上，是连边时的复杂度。
### 代码实现
和二分差不多是我没想到的，可能 stack 与 vector 两个 STL 常数太大。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,tot,head[N],to[N],nxt[N];
int dis[N],ind[N];
vector<int>v[N];
stack<int>st;
inline void add(int a,int b)
{
	tot++;ind[b]++;
	nxt[tot]=head[a];head[a]=tot;to[tot]=b;
}
inline void topo_sort_is_most_handsome()
{
	for(int i=1;i<=n;i++) if(ind[i]==0) st.push(i),dis[i]=1;
	while(!st.empty())
	{
		int a=st.top();st.pop();
		for(int i=head[a];i;i=nxt[i])
		{
			int t=to[i];
			ind[t]--;
			if(dis[t]<dis[a]+1) dis[t]=dis[a]+1;
			if(ind[t]==0) st.push(t);
		}
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int m;cin>>m;
		for(int j=1;j<=m;j++)
		{
			int a;cin>>a;v[a].push_back(i);
		}
	}
	for(int i=1;i<=1e5;i++) 
	{
		if(v[i].size()==0) continue;
		for(int j=0;j<v[i].size()-1;j++) 
		{
			add(v[i][j],v[i][j+1]);
		}
	}
	topo_sort_is_most_handsome(); 
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,dis[i]);
	cout<<ans;
}

```


实际上，以上两种做法如果离散化一下应该可以去掉 $V$ 的复杂度，降为 $n$，但实在没必要。

---

## 作者：LiHen_Yan (赞：3)

## P12862 [NERC 2020 Online] Miser 题解

### Problem

给定每天来校的人，一共 $k$ 块广告牌，求出最小的 $k$ 使得每个人每次来看到的广告牌是递减的。


### Solution
看到这种输入第一眼还以为是比较阴间的图论题，想了想发现可以差分约束，图建出来注意到是 DAG，直接 dp 就能跑最长路，但是太复杂了，有没有更简单一些的做法。

考虑如果告诉你有 $k$ 块让判断有没有解怎么做，直接暴力 $O(n)$ 扫一遍枚举天数然后求出当天参观看到牌子的最小值 $m$ 然后这天看到牌子的全更新为 $m-1$，如果有一天存在当前要更新为 $0$ 就无解，反之有解。

注意到如果 $k$ 有解，$k + 1$ 一定有解，具有单调性，要求最小值，考虑二分答案，然后直接做就完了。


```cpp
#include <bits/stdc++.h>
#define int long long
constexpr int maxn = 1e5 + 7;
std::vector<int> G[maxn];
int a[maxn], n, maxx;
bool check(int x){
	for(int i = 1; i <= maxx; i++){
		a[i] = x + 1;
	}
	int f = 1;
	for(int i = 1; i <= n; i++){
		int now = 1e18;
		for(int v : G[i]){
			now = std::min(now, a[v]);
		}
		if(!(now - 1)){
			f = 0;
			break;
		}
		for(int v : G[i]){
			a[v] = now - 1;
		}
	}
	return f;
}
int32_t main(){
	std::cin.tie(nullptr) -> std::ios::sync_with_stdio(false);
	std::cin >> n;
	for(int i = 1; i <= n; i++){
		int k;
		std::cin >> k;
		for(int j = 1; j <= k; j++){
			int v;
			std::cin >> v;
			G[i].push_back(v);
			maxx = std::max(maxx, v);
		}
	}
	int l = 1, r = 1e18, ans;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)){
			r = mid - 1;
			ans = mid;
		}
		else l = mid + 1;
	}
	std::cout << ans << '\n';
	return 0; 
}
```

---

## 作者：__sunhy2012__ (赞：2)

# P12862 Miser 题解
## 题目大意：
一共有 $n$ 天，每天有 $k$ 个学生路过食堂窗口，求至少购买多少个数字牌才能使来过校的每名同学分别看到的数字是严格递减的。
## 算法思路
这道题可以用拓扑加贪心实现，用邻接表建图，然后每一次输入都标记这个节点存在，如果这个数字第一次出现，就记录最后一次出现是 $i$  如果这个数之前出现过，那就建边，之前的这个节点入度加一并更新这个数最后一次出现。然后进行拓扑排序的初始化：循环判断，如果这个节点 $i$ 存在且入度为零,初始化深度为一然后进队列。拓扑排序部分就比较简单了，取队头，然后更新最大深度，遍历当前节点所有邻接点，临节点入度减一并更新邻接点的深度，如果深度为零，那就继续入队列。
## AC代码
```
#include<bits/stdc++.h>
using namespace std;
const int N =1e4+5;
int n,in[N],d[N],nex[N],ans;
// n：节点数。
// in：入度。
// d：深度。
// nex：每个数字最后出现的节点。
bool v[N];// 用来标记节点是否存在。
vector<int>p[N];
queue<int>q;
int main(){
	int k;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>k;
		int x;
		for(int j=1;j<=k;j++){
			cin>>x;
			v[i]=1;// 标记节点 i 存在。	
			if(nex[x]==0){// 如果 x 第一次出现。
				nex[x]=i;// 记录最后一次出现是。
				continue;
			}
			// 如果 x 之前出现过，建边。
			p[i].push_back(nex[x]);// 从当前节点i向之前最后一次出现 x 的节点建立边
			in[nex[x]]++;// 之前的这个节点入度加一。
			nex[x]=i;// 更新 x 最后一次出现。
		}
	}
	for(int i=1;i<=100000;i++){//拓扑初始化，节点数最多不超过十万。
		if(v[i]&&in[i]==0){// 如果这个节点 i 存在且入度为零.
			d[i]=1;// 初始化深度为一。
			q.push(i);// 进队列。
		}
	}
	while(!q.empty()){// 拓扑排序部分
		int x=q.front();// 取出队头
		q.pop();
		ans=max(ans,d[x]);// 更新最大深度
		for(size_t i=0;i<p[x].size();i++){// 遍历当前节点所有邻接点
			int y=p[x][i];
			in[y]--;// 临节点入度减一。
			d[y]=max(d[y],d[x]+1);// 更新邻接点的深度
			if(in[y]==0) q.push(y);// 如果深度为零，进队列
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Charged_Charge (赞：2)

# 洛谷 P12862
## 前言：
这貌似是一道十分冷门的题，提交次数与通过次数都少得可怜。
## 题目大意：
$n$ 天，每天 $k$ 名学生，求至少购买多少个数字牌才能使来过校的每名同学分别看到的数字是单调递减的。
## 解题思路：
这个题目是可以用二分解决的。首先，我们分析一下，为什么这题用二分。当我们发现，使用 $x$ 个数字牌可以满足要求，如果再多买数字牌显然是可以的，但是，吝啬的主管十分的吝啬，他不想花更多的钱，所以当我们发现使用 $x$ 个数字牌可以时，再多买，一定是不符合要求的。在判断函数里，我们把之前来的学生看到数字的最小值设为 $num$，则当天的数字则应该为 $num-1$，如果之前看到的数字的数字变为 $1$ 了，则 $num-1$ 就是 $0$ 了，今天就无法放数字牌了，则返回当前二分的数字牌数量不行。注意：$n$ 已经大到了 $10^5$，需要采用链式前向星的思想，用向量存储。
## AC 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+20;
int n, k;
vector<int> a[N];
int b[N];
int l, r, mid;
bool check(int x) {
	for (int i = 1; i <= N; i++) {
		b[i] = x + 1;
	}

	for (int i = 1; i <= n; i++) {
		int num = INT_MAX;

		for (int j = 0; j < a[i].size(); j++) {
			num = min(num, b[a[i][j]]);
		}

		if (num == 1) {
			return false;
		}

		for (int j = 0; j < a[i].size(); j++) {
			b[a[i][j]] = num - 1;
		}
	}

	return true;
}

int main() {
	cin >> n;

	for (int i = 1; i <= n; i++) {
		cin >> k;

		for (int j = 1; j <= k; j++) {
			int x;
			cin >> x;
			a[i].push_back(x);
		}
	}

	l = 1, r = n;

	while (l <= r) {
		mid = (l + r) >> 1;

		if (check(mid)) {
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}

	cout << l;
	return 0;
}
```

---

