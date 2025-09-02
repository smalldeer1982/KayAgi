# Party

## 题目描述

A company has $ n $ employees numbered from $ 1 $ to $ n $ . Each employee either has no immediate manager or exactly one immediate manager, who is another employee with a different number. An employee $ A $ is said to be the superior of another employee $ B $ if at least one of the following is true:

- Employee $ A $ is the immediate manager of employee $ B $
- Employee $ B $ has an immediate manager employee $ C $ such that employee $ A $ is the superior of employee $ C $ .

The company will not have a managerial cycle. That is, there will not exist an employee who is the superior of his/her own immediate manager.

Today the company is going to arrange a party. This involves dividing all $ n $ employees into several groups: every employee must belong to exactly one group. Furthermore, within any single group, there must not be two employees $ A $ and $ B $ such that $ A $ is the superior of $ B $ .

What is the minimum number of groups that must be formed?

## 说明/提示

For the first example, three groups are sufficient, for example:

- Employee 1
- Employees 2 and 4
- Employees 3 and 5

## 样例 #1

### 输入

```
5
-1
1
2
1
-1
```

### 输出

```
3
```

# 题解

## 作者：StudyingFather (赞：13)

这道题中的所有上下级关系事实上构成了一棵树（可以虚构一个节点作为没有直接上司的人的上司）。

那么，我们就可以将深度相同的人分配到同一组。所以本题的答案就是该树的最大深度。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int fa[2005];
int find(int x)
{
 int cnt=0;
 while(x!=-1)
  x=fa[x],cnt++;
 return cnt;
}
int main()
{
 int n,ans=0;
 scanf("%d",&n);
 for(int i=1;i<=n;i++)
  scanf("%d",&fa[i]);
 for(int i=1;i<=n;i++)//因为n<=2000，所以这里直接暴力寻找每个节点的深度了，复杂度为O(n^2)
  ans=max(ans,find(i));
 printf("%d\n",ans);
 return 0;
}
```

---

## 作者：xiaomuyun (赞：4)

# CF115A Party 题解
这是一道树的好题。

[题目传送门](https://www.luogu.com.cn/problem/CF115A)

（话说 CF 可真厉害，一百个测试点不是事……）
## 解法：~~伟大的~~邻接表
我们在输入的同时，用 vector 存树，然后 dfs 并求出最大深度即可。
## 需要注意的几个地方
1. 如果当前员工没有上级（即输入的时候为 $-1$），就不需要加边，直接输入下一个即可；
2. 求**最大深度**：在 dfs 的时候，将当前节点的所有儿子的深度设为当前节点的深度 $+1$，并取最大值（~~千万不能白白 dfs 了一遍，什么也没做……~~）。

## 代码
```cpp
#include<cstdio>
#include<vector>
#define max(a,b) ((a>b)?a:b)

using namespace std;

int n,mx=1,dep[2001],f[2001];
vector<int> g[2001];

void dfs(int u){
	for(int i=0;i<g[u].size();++i){
		int v=g[u][i];
		dep[v]=dep[u]+1;//求深度
		mx=max(dep[v],mx);//取max
		dfs(v);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&f[i]);
		if(f[i]==-1) continue;
		g[f[i]].push_back(i);//存边
	}
	for(int i=1;i<=n;++i){
		if(f[i]==-1){//一定要从每棵树的根开始dfs
			dep[i]=1;
			dfs(i);
		}
	}
	printf("%d\n",mx);
	return 0;
}
```
## 总结
点个赞吧，制作不易！

---

## 作者：Mysterious_Cat (赞：3)

### 题目大意：
这里补一下输入格式

第一行，一个正整数$n$，表示有$n$个雇员。  
接下来$n$行，每行一个正整数，表示第$i$个职员的直接上司，没有上司则为$-1$。

### 题目思路：
最小值问题，二分有不可解，贪心无疑。  

对于每一条路径，组数必须大于路径长，否则路径上必有两点在同一组。

于是变成了求最长路径。

### Code：
```cpp
\\数据2e3，O(n^2)暴力递归能过
#include<bits/stdc++.h>
using namespace std;

const int NR = 2e3 + 5;

int ans = 0, father[NR];

int find(int x, int len)
{
    if(father[x] == -1) return len;
    return find(father[x], len + 1);
}

int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &father[i]);
    for(int i = 1; i <= n; i++)
        ans = max(ans, find(i, 1));
    cout << ans;
    
    return 0;
}
```


---

## 作者：WinterRain208 (赞：1)

仔细看了一下，这题不就是一棵树吗？

而且数据还很小。

那我们直接用父亲表示法，再递归记录最大深度。

编号也不大，代码中可以全部使用$int$。

至于父亲表示法，就不多介绍了，开一个数组，下标表示儿子，具体的值表示他的父亲。

```cpp
tree[son]=father;
```

就像这样。

这题就解决了。

时间复杂度为$O(n^2)$。

## 丑陋的代码

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;
const int N=1e4+5;

int n,tree[N],x,M=-1;

int find(int s,int step){
	if(tree[s]==-1)return step+1;
	return find(tree[s],step+1);
}
int main(){
	scanf("%d",&n);
	F(i,1,n){
		scanf("%d",&x);
		tree[i]=x;
	}
	F(i,1,n)
		M=max(M,find(i,0));
	printf("%d",M);
    return 0;
}

```

### 蒟蒻结尾

---

## 作者：fengxiaoyi (赞：0)

### 修改日志

- 2022.8.6 21:55 ：去处了普通英文的 $\LaTeX$，对算法进一步描述。

------------

### 题意简化
给你一个森林（注意有可能有多个 $p_i$ 为 $-1$。所以是森林，但下文会做处理），求森林里每棵树的最大深度的最大值

### 思路
不难想到用广搜。

因为可能会有多个没有直接总经理的节点（既没有上级），那为了方便广搜，我们可以建立一个虚拟 $0$ 号节点，来充当 $p_i$ 为 $-1$ 的节点的上级。

对于每个节点，设其深度为 $dep$，遍历一遍他的儿子节点。因为这是一棵树，所以不用判断这个节点是否被访问过。对于每个儿子节点的深度，就是其父亲的深度 $dep+1$，接着将得到的深度 $dep_2$ 对 $ans$ 取个 $\max$。

队列我习惯用 queue 容器维护。

### 代码（简单明了的广搜）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,dep[2010],ans=-1,f[2010],nxt[2010],to[2010],num;
struct e{
	int u,d;
};
queue<e>q;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int p;
		cin>>p;
		p=max(0,p);
		to[++num]=i;
		nxt[num]=f[p];
		f[p]=num;
	}
	q.push({0,0});
	while(!q.empty()){
		int v=q.front().u,dep=q.front().d;
		ans=max(ans,dep);
		q.pop();
		for(int i=f[v];i;i=nxt[i]){
			q.push({to[i],dep+1});
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Daidly (赞：0)

给定每个人的上司，求最少分成几个集合使得每个集合中任意两个元素没有上下属关系。

考虑把每个人的上司和他连边，这样便形成了一棵树，这棵树的每一层都没有上下属关系，答案就是树的深度。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e3+5;
int n,f[MAXN],maxdep;
int dep(int x,int len){
	if(f[x]==-1)return len;
	return dep(f[x],len+1);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>f[i];
	}
	for(int i=1;i<=n;++i){
		maxdep=max(maxdep,dep(i,1));
	}
	cout<<maxdep;
	return 0;
}
```

---

## 作者：Nozebry (赞：0)

## $Problems$
给出每个员工的直属上级， $-1$ 说明没有直属上级。

如果 $A$ 是 $B$ 的上级，$B$ 是 $C$ 的上级，那么 $A$ 也是 $C$ 的上级。

现在公司里有 $N$ 个人要开 $party$，要求上级和下属不能坐在同一张桌子上，问至少需要几张桌子。
## $Answer$
我们可以把题目变形成：给出每个叶子结点的父亲节点， $-1$ 说明没有父亲节点。如果 $A$ 是 $B$ 的父亲节点，$B$ 是 $C$ 的父亲节点，那么 $A$ 也是 $C$ 的父亲节点。

这样一改就不难发现这道题是道并查集，我们只需再读入时不断地利用 $p$ 来构建一颗树，并在最后枚举每个节点来找最大深度就可以了。。。
## $Code$
```cpp
#include<bits/stdc++.h>
int f[2010];
int find(int x)
{
    int k=0;
    while(f[x]!=x)x=f[x],k++;
    return k;
}//查找每个节点可以延伸出去的深度
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
	int k;
        scanf("%d",&k);
        if(k==-1)f[i]=i;
        else f[i]=k;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
	if(find(i)>ans)ans=find(i);查找每个节点可以延伸出去的深度，以此来找最大的深度
    printf("%d",ans+1);
}
```

---

## 作者：动态WA (赞：0)

根据管理员大佬的题解，本题是求树的最大深度，于是我选择了~~已经死掉的~~spfa

建图（本题解所有边都是单向边，且边权为-1）：建立一个超级源点连向所有点，
如果a[i]不为-1，那么建立一条边由i连向a[i]。

跑出结果后找d[i]最小的，再输出相反数，就是答案了

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
int n,h;
int d[2010],head[2010],to[6010],nt[6010];
bool c[2010];
queue<int> q;
void add(int u,int v){
	to[++h]=v;
	nt[h]=head[u];
	head[u]=h;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int d;
		scanf("%d",&d);
		if (d>0)
			add(i,d);
		add(0,i);
	}
	memset(d,0x3f,sizeof(d));
	d[0]=0;
	c[0]=1;
	q.push(0);
	while (!q.empty()){
		int g=q.front();
		q.pop();
		c[g]=0;
		for (int i=head[g];i;i=nt[i]){
			int j=to[i];
			if (d[j]>d[g]-1){
				d[j]=d[g]-1;
				if (!c[j]){
					c[j]=1;
					q.push(j);
				}
			}
		}
	}
	int ans=-1;
	for (int i=1;i<=n;i++)
		ans=min(ans,d[i]);
	cout<<-ans;
	return 0;
}
```


---

