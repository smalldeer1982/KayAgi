# 题目信息

# [USACO21JAN] Dance Mooves S

## 题目描述

Farmer John 的奶牛们正在炫耀她们的最新舞步！

最初，所有的 $N$ 头奶牛（$2≤N≤10^5$）站成一行，奶牛 $i$ 排在其中第 $i$ 位。舞步序列给定为 $K$ （$1≤K≤2\times10^5$）个位置对 $(a_1,b_1),(a_2,b_2),…,(a_K,b_K)$。在舞蹈的第 $i=1…K$ 分钟，位置 $a_i$ 与 $b_i$ 上的奶牛交换位置。同样的 $K$ 次交换在第 $K+1…2K$ 分钟发生，在第 $2K+1…3K$ 分钟再次发生，以此类推，无限循环。换言之， 

 - 在第 $1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - ……
 - 在第 $K$ 分钟，位置 $a_K$ 与 $b_K$ 上的奶牛交换位置。
 - 在第 $K+1$ 分钟，位置 $a_1$ 与 $b_1$ 上的奶牛交换位置。
 - 在第 $K+2$ 分钟，位置 $a_2$ 与 $b_2$ 上的奶牛交换位置。
 - 以此类推……

对于每头奶牛，求她在队伍中会占据的不同的位置数量。

## 说明/提示

 - 奶牛 $1$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $2$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $3$ 可以到达位置 $\{1,2,3\}$。
 - 奶牛 $4$ 可以到达位置 $\{1,2,3,4\}$。
 - 奶牛 $5$ 从未移动，所以她没有离开过位置 $5$。

#### 测试点性质：

 - 测试点 1-5 满足 $N≤100,K≤200$。
 - 测试点 6-10 满足 $N≤2000,K≤4000$。
 - 测试点 11-20 没有额外限制。

供题：Chris Zhang 

## 样例 #1

### 输入

```
5 4
1 3
1 2
2 3
2 4```

### 输出

```
4
4
3
4
1```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是先模拟一轮 $k$ 次交换，找出其中的环，因为环内的奶牛运动轨迹相同，经过的位置也相同，所以可以统一处理环内奶牛经过的不同位置数量。大部分题解使用并查集来维护环，用 `vector` 记录每头奶牛经过的位置，用 `set` 统计不同位置的数量。部分题解还给出了从 50 分暴力解法到 100 分优化解法的思路。

### 所选题解
- **作者：Skies (赞：23)，4星**
  - **关键亮点**：思路讲解生动易懂，代码结构清晰，详细阐述了使用并查集维护环以及用 `vector` 和 `set` 统计不同位置数量的过程。
- **作者：Lonely_NewYear (赞：0)，4星**
  - **关键亮点**：将问题抽象为图论问题，每个点的出度和入度都为 1，说明图中每个点都在一个环上，通过 `dfs` 遍历环，并且使用 `cnt` 数组优化，避免每次都初始化数组，降低了时间复杂度。
- **作者：Aiopr_2378 (赞：5)，4星**
  - **关键亮点**：通过对样例的分析得出每经过 $n*k$ 次操作数组复原以及经过 $k$ 次操作后会出现环的结论，然后使用并查集、`vector` 和 `set` 解决问题，思路清晰。

### 重点代码
#### Skies 的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,k;
int a[N];
int fa[N],si[N];
// 初始化并查集和奶牛位置
void init()
{
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		a[i]=i;
	}
}
// 并查集查找操作
int get(int x)
{
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
vector<int >vc[N];
int cx[N],cy[N];
set<int> ans[N];

int main()
{
	cin>>n>>k;
	init();
	for(int i=1;i<=k;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		swap(a[x],a[y]);
		vc[a[x]].push_back(x);
		vc[a[y]].push_back(y);
	}
	for(int i=1;i<=n;i++)
	{
		vc[i].push_back(i);
	}
	for(int i=1;i<=n;i++)
	{
	    int x=get(i),y=get(a[i]);
	    fa[x]=y;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<vc[a[i]].size();j++)
		{
			ans[get(a[i])].insert(vc[a[i]][j]);
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[get(i)].size());
	}
	return 0;
}
```
**核心实现思想**：先模拟一轮 $k$ 次交换，记录每头奶牛经过的位置，然后使用并查集将有相同运动轨迹的奶牛合并到同一个集合中，最后用 `set` 统计每个集合中奶牛经过的不同位置数量。

#### Lonely_NewYear 的核心代码
```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
int now[100001],to[100001],cnt[100001],tot,ans[100001];
bool vis[100001];
vector<int> s[100001];
queue<int> q;

void dfs(int u)
{
	vis[u]=1;
	q.push(u);
	int len=s[u].size();
	for(int i=0;i<len;i++)
	{
		if(++cnt[s[u][i]]==1)
		{
			tot++;
		}
	}
	if(!vis[to[u]])
	{
		dfs(to[u]);
	}
}

int main()
{
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		now[i]=i;
		s[i].push_back(i);
	}
	for(int i=1;i<=k;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		s[now[a]].push_back(b);
		s[now[b]].push_back(a);
		swap(now[a],now[b]);
	}
	for(int i=1;i<=n;i++)
	{
		to[now[i]]=i;
	}
	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			dfs(i);
			int res=tot;
			while(!q.empty())
			{
				int u=q.front();
				q.pop();
				ans[u]=res;
				int len=s[u].size();
				for(int j=0;j<len;j++)
				{
					if(--cnt[s[u][j]]==0)
					{
						tot--;
					}
				}
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		printf("%d\n",ans[i]);
	}
	return 0;
}
```
**核心实现思想**：先模拟一轮 $k$ 次交换，记录每头奶牛经过的位置，将问题抽象为图论问题，每个点的出度和入度都为 1，说明图中每个点都在一个环上，通过 `dfs` 遍历环，使用 `cnt` 数组统计不同位置的数量，避免每次都初始化数组。

#### Aiopr_2378 的核心代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005],fa[100005];
vector <int> v[100005];
set <int> ans[100005];

int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}

int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		fa[i]=i;
		a[i]=i;
	}
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y;
		swap(a[x],a[y]);
		v[a[x]].push_back(y);
		v[a[y]].push_back(x);
	}
	for(int i=1;i<=n;i++) v[a[i]].push_back(i);
	for(int i=1;i<=n;i++) fa[find(i)]=find(a[i]);
	for(int i=1;i<=n;i++){
		for(int j=0;j<v[a[i]].size();j++){
			ans[find(a[i])].insert(v[a[i]][j]);
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[find(i)].size()<<endl;
	return 0;
}
```
**核心实现思想**：先模拟一轮 $k$ 次交换，记录每头奶牛经过的位置，使用并查集将有相同运动轨迹的奶牛合并到同一个集合中，最后用 `set` 统计每个集合中奶牛经过的不同位置数量。

### 最优关键思路或技巧
- **并查集维护环**：将有相同运动轨迹的奶牛合并到同一个集合中，方便统一处理环内奶牛经过的位置。
- **使用 `vector` 记录经过位置**：动态记录每头奶牛经过的位置，避免使用二维数组造成空间浪费。
- **使用 `set` 统计不同位置数量**：`set` 会自动去重，方便统计不同位置的数量。
- **图论抽象**：将问题抽象为图论问题，每个点的出度和入度都为 1，说明图中每个点都在一个环上，通过 `dfs` 遍历环。
- **数组优化**：使用 `cnt` 数组统计不同位置的数量，避免每次都初始化数组，降低时间复杂度。

### 可拓展之处
同类型题或类似算法套路：
- 循环节问题：当问题中存在循环操作时，可以先找出循环节，然后根据循环节的特点进行优化。
- 图论中的环问题：可以使用并查集、`dfs` 等方法来处理图中的环。

### 推荐题目
- P1196 [NOI2002] 银河英雄传说：并查集的应用，涉及到集合的合并和元素之间的距离计算。
- P1892 [BOI2003]团伙：并查集的应用，需要处理朋友和敌人的关系。
- P2024 [NOI2001] 食物链：并查集的拓展应用，需要处理三种不同的关系。

### 个人心得
- **Lonely_NewYear**：赛时这题没弄出来，认为最重要的优化是使用 `cnt` 数组统计不同位置的数量，避免每次都初始化数组，否则时间复杂度会提高为 $O(n^2)$，只能拿到 50 分。总结：在处理需要多次初始化数组的问题时，要考虑使用数组优化，避免时间复杂度的增加。

---
处理用时：55.29秒