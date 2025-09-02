# Decorate Apple Tree

## 题目描述

### 题目大意

给你一个$n$个结点以$1$为根的树，给这$n$个结点任意染色，定义一个点为快乐结点当且仅当这个结点的子树上所有点颜色均不相同。求出对于$1\sim n$中的每一个$k$，快乐结点数大于等于$k$所需要的最少颜色数。

## 样例 #1

### 输入

```
3
1 1
```

### 输出

```
1 1 2 
```

## 样例 #2

### 输入

```
5
1 1 3 3
```

### 输出

```
1 1 1 2 3 
```

# 题解

## 作者：Suiseiseki (赞：5)

### 这一题我们可以在电脑上画一下
#### 便会发现一个很有趣的性质
**我们先倒着考虑**

- 如果是$n$个节点，很明显必须是所有叶子节点必须是不同的颜色
- 那么去掉根节点呢？就是左右两颗子树叶节点个数中的最大值了

接下来就可以很愉快地排序+求最大值啦！

那么就看代码吧：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
#define Maxn 100000
int head[Maxn+5],arrive[Maxn+5],nxt[Maxn+5],tot;
int f[Maxn+5];
void add_edge(int from,int to){
	arrive[++tot]=to;
	nxt[tot]=head[from];
	head[from]=tot;
}
void dfs(int root){
	f[root]=0;
	for(int i=head[root];i;i=nxt[i]){
		dfs(arrive[i]);
		f[root]+=f[arrive[i]];
	}
	if(f[root]==0){
		f[root]=1;//它本身是一个叶子节点
	}
}//O(n)计算节点中叶节点的个数
int main(){
	int n;
	scanf("%d",&n);
	int fa;
	for(int i=2;i<=n;i++){
		scanf("%d",&fa);
		add_edge(fa,i);
	}
	dfs(1);
	sort(f+1,f+1+n);//排序
	int ans=0;
	for(int i=1;i<=n;i++){
		if(f[i]>ans){
			ans=f[i];//求最大值
		}
		printf("%d ",ans);
	}
	puts("");
	return 0;
}

```

本人真蒟蒻一枚，代码可能不是最优。~~各位巨佬敬请喷~~

---

## 作者：VenusM1nT (赞：5)

$\text{Dfs}$。问题可以转换为以每个点为根的子树有多少叶子节点，因此跑一遍 $\text{Dfs}$ 后排序输出即可。

```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int cnt,fst[MAXN],nxt[MAXN],to[MAXN];
int n,sum[MAXN];
void AddEdge(int u,int v)
{
	to[++cnt]=v;
	nxt[cnt]=fst[u];
	fst[u]=cnt;
}
void Dfs(int u)
{
	bool fg=0;
	for(int i=fst[u];i;i=nxt[i])
	{
		fg=1;
		int v=to[i];
		Dfs(v);
		sum[u]+=sum[v];
	}
	if(!fg) sum[u]=1;
}
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		AddEdge(x,i);
	}
	Dfs(1);
	sort(sum+1,sum+n+1);
	for(int i=1;i<=n;i++) printf("%d ",sum[i]);
	return 0;
}
```

---

## 作者：JOE_ZengYuQiao_0928 (赞：3)

### 正常题意
求以点 $i$ 为根节点的子树有多少个叶子节点。
### 解题思路
考虑树形 DP。

状态为 $dp_i$ 表示以点 $i$ 为根节点的子树有多少个叶子节点。

答案为 $dp_i$。

状态转移方程为 $dp[x]+dp[nxt]$。

初始状态为本身是叶节点时 $dp_i$ 为 $1$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,dp[100005];
vector<int> nbr[100005];
void dfs(int x){
	for(auto nxt:nbr[x]){
		dfs(nxt);
		dp[x]+=dp[nxt]; 
	}
	if(dp[x]==0)dp[x]=1;//本身为叶节点时dp[i]为1 
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(),cout.tie();
	cin>>n;
	for(int i=2;i<=n;i++)cin>>a,nbr[a].push_back(i);
	dfs(1);
	sort(dp+1,dp+1+n);
	for(int i=1;i<=n;i++)cout<<dp[i]<<" ";
	return 0;
}

```

---

## 作者：GSE_ (赞：1)

## 人话翻译

一棵以 $1$ 为根的有 $n$ 个节点的树，将该树中若干个节点的值置为 $1$，使得这棵树中有 $k$ 个节点满足以该节点为根节点的子树的叶子结点的值全为 $1$，对于从 $1$ 到 $n$ 的每个 $k$ 值，输出最少要将多少个节点置为 $1$。

## 实现思路

~~树上 dp 模板题，还是非常简单的。~~

- 对于树的每个节点，使用一个数组 $f$ 存储节点满足条件的最小值。

- 对于任意一个有儿子的节点 $i$（不是叶子结点，则令 $f_i = 0$， 否则 $f_i = 1$。

- 对于任意一个节点，该节点的值等于该节点本身的值加上该节点所有儿子的值。

这样就获取到了每个节点的值，实现如下：

dp 函数：

```cpp
void dp(int now)
{
	//son
	for(auto i : tree[now])
	{
		dp(i);
		f[now] += f[i];
	}
	
	return;
}
```

题目要求输出 $k$ 个节点满足条件时的最小值，可以对 $f$ 数组进行升序排序，排序后的 $f_i$ 就是 $i$ 个节点满足条件时的最小值。

完整代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int f[100001];
vector<int> tree[100001];

void dp(int now)
{
	//son
	for(auto i : tree[now])
	{
		dp(i);
		f[now] += f[i];
	}
	
	return;
}

signed main()
{	
	cin >> n;
	for(int i=2; i<=n; i++)
	{
		int tmp;
		scanf("%d", &tmp);
		//make tree
		tree[tmp].push_back(i);
	}
	//init f
	for(int i=1; i<=n; i++)
	{
		//no son
		if(tree[i].size() == 0)
		{
			f[i] = 1;
		}
	}
	//dp
	dp(1);
	//sort
	sort(f+1, f+n+1);
	//output
	for(int i=1; i<=n; i++)
	{
		cout << f[i] << ' ';
	}
	
	return 0;
}
```

---

## 作者：Bai_R_X (赞：0)

## 思路
问题等价于以每个点为根的子树有多少叶子节点，所以搜索一遍再排序即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p,i,tot,head[100005],sz[100005];
struct Edge
{
	int v,nxt;
}e[100005];
void add(int u,int v)
{
	e[++tot].v=v;
	e[tot].nxt=head[u];
	head[u]=tot;
}
void dfs(int u)
{
	if(head[u]==0)sz[u]=1;
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		dfs(v);
		sz[u]+=sz[v];
	}
}
signed main()
{
	cin>>n;
	for(i=2;i<=n;i++)
	{
		cin>>p;
		add(p,i);
	}
	dfs(1);
	sort(sz+1,sz+n+1);
	for(i=1;i<=n;i++)cout<<sz[i]<<" ";
	return 0;
}
```

---

## 作者：liuyi0905 (赞：0)

题意很简单，读完题可得知问题是求以每个点为根节点有多少个叶节点。

跑一遍树形 $dp$ 后排序即可求出答案。

注意：当结点本身就是叶节点时要将 $dp_i$ 设为 $1$。

具体代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int n,cnt,head[N],dp[N];
struct edge{int to,from,nxt;}e[N];
void add(int x,int y){e[++cnt]={y,x,head[x]},head[x]=cnt;}
void dfs(int u){
	for(int i=head[u];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v);
		dp[u]+=dp[v];
	}
	if(!dp[u])dp[u]=1;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=2,x;i<=n;i++)cin>>x,add(x,i);
    dfs(1);
    sort(dp+1,dp+n+1);
    for(int i=1;i<=n;i++)cout<<dp[i]<<" ";
    return 0;
}
```

---

