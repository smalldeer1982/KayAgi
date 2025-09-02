# Script Generation

## 题目描述

编剧们打算组一些 $\mathtt{CP}$ 来满足观众的喜好！

总共有 $n$ 个男角色与 $n$ 个女角色，且最多只能组成 $k$ 对 $\mathtt{CP}$ ，每对 $\mathtt{CP}$ 都可以给观众带来 $r$ 的幸福值。

总幸福值的定义即为所有 $\mathtt{CP}$ 给观众带来的幸福值之和且一个角色不能和多人组 $\mathtt{CP}$ ！

由于编剧认为让观众获得最大幸福值会导致剧本可预测，所以他们想要选取总幸福值为第 $t$ 小的 $\mathtt{CP}$ 组合方案。

由于编剧们去玩了，所以他们把这个问题交给了你，请你求出第 $t$ 小的总幸福值。

数据保证有解。

## 样例 #1

### 输入

```
2 4 3
1 1 1
1 2 2
2 1 3
2 2 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 4 7
1 1 1
1 2 2
2 1 3
2 2 7
```

### 输出

```
8
```

# 题解

## 作者：wkjwkj (赞：0)

这道题目，我们首先需要进行模型转化。

直接求第 $t$ 小的幸福值，明显很难求，所以我们可以直接采用二分答案！

每次限定了一个范围上限 $limit$ ，只需统计在 $0 \le x \le limit$ 范围内满足条件的 $\mathtt{CP}$ 对数，我们在二分这个 $limit$ 的时候，满足条件的 $\mathtt{CP}$ 对数肯定是单调变化的，即答案具有单调性，所以最终答案是正确的。

现在本题的瓶颈就是在 $check$ 函数的设计上。

我们可以直接采用 $dfs$ ，对于每对 $\mathtt{CP}$ 关系都可以取或不取，对于角色使用关系可以用 $vis$ 数组来保存。

还要注意的一点是，本题时限较紧，注意在 $dfs$ 过程加上剪枝。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t;
int a[25][25];
int head[45],Next[405],ver[405],edge[405];
int tot=0;
int vis[45];
void add(int x,int y,int z)
{
	Next[++tot]=head[x],ver[tot]=y,edge[tot]=z;
	head[x]=tot;
}
int dfs(int x,int sum,int limit)
{
	if(sum>limit)return 0;
	if(x==n+1)return 1;
	int ans=dfs(x+1,sum,limit);
	for(int i=head[x];i;i=Next[i])
	{
		int y=ver[i],z=edge[i];
		if(ans>=t)continue;
		if(vis[y])continue;
		vis[y]=1;
		ans+=dfs(x+1,sum+z,limit);
		vis[y]=0;
	}
	return ans;
}
int check(int x)
{
	return dfs(1,0,x)>=t;
}
int main()
{
	scanf("%d%d%d",&n,&k,&t);
	for(int i=1;i<=k;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		y+=n;
		add(x,y,z);
	}
	int l=0,r=2e5;
	int ans=-1;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```





---

