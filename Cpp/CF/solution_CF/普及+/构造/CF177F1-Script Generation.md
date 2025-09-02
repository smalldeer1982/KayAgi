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

## 作者：wkjwkj (赞：2)

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

## 作者：4041nofoundGeoge (赞：1)

觉得楼下的题解讲得不太详细，所以写了此篇题解！

## 题目翻译

[翻译](https://www.luogu.com.cn/paste/q1b0f5p5)

## 解题思路

应该非常好理解，就是一道关于图的模拟题（也可以理解成链表），可以用结构体模拟。

> 1. `next`：代表一个结点的下一个结点。
> 2. `head`：头结点。
> 3. `ver`：代表一个结点的上一个结点。
> 4. `edge`：代表边权。

题目大概思路是用二分查找第 $k$ 幸福值，但所有值都查找一遍会喜提 TLE，**所以一定要用二分**。二分中查找的每个值 $mid$ 都要深度优先搜索。

为了让时间复杂度卡在 $2$ 秒之内，需要在 DFS 中剪枝。

### 前置小知识

二分模板：

```cpp
int l = 1, r = 10000000, mid;
while (l < r) {
    mid = (l + r) / 2 // 或者mid=(l+r)>>1
        if (check(mid)) l
        = mid; // check函数自由发挥
    else r = mid;
}
```

链式前向星法模（mú）板：

```cpp
void add_edge(int x, int y, int z)
{
    a[++tot].next = a[x].head, a[tot].ver = y, a[tot].edge = z;
    a[x].head = tot;
}
```

## 接下来我们来看一下代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, k, t;
struct Node {
    int head, next, ver, edge;
} a[1005];
int tot = 0;
bool vis[105];
void add_edge(int x, int y, int z)
{
    a[++tot].next = a[x].head, a[tot].ver = y, a[tot].edge = z;
    a[x].head = tot;
}
int dfs(int x, int sum, int limits)
{
    if (sum > limits)
        return false;
    if (x == n + 1)
        return true;
    int ans = dfs(x + 1, sum, limits);
    for (int i = a[x].head; i; i = a[i].next) {
        int summ = a[i].ver, z = a[i].edge;
        if (ans >= t)
            continue;
        if (vis[i])
            continue;
        vis[summ] = true;
        ans += dfs(x + 1, sum + z, limits);
        vis[summ] = false;
    }
    return ans;
}
bool check(int x)
{
    return dfs(1, 0, x) >= t;
}
int main()
{
    cin >> n >> k >> t;
    for (int i = 1; i <= k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        y += n;
        add_edge(x, y, z);
    }
    int l = 0, r = 2e5;
    int ans = -114514;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (check(mid))
            r = mid - 1, ans = mid;
        else
            l = mid + 1;
    }
    cout << ans << endl;
    return 0;
}

```

---

## 作者：Jin_Yichen (赞：1)

本蒟蒻又来写题解了！

## 思路
和第一篇题解的思路大致相同，就是使用二分找到幸福值第 $t$ 小的一组 CP，然后输出即可。

对于 $check$ 函数，可以使用 dfs 对其进行搜索，判断其幸福值是否满足要求，如果是，那么上边界更新到 $mid$，并保存答案，否则就将下边界更新到 $mid$。有一点要注意，每遍历一组 CP，都要打一个标记，保证不会出现死循环。

这道题的时限比较小，而且我们使用了 dfs，所以必须要在 dfs 里做剪枝，包括：

1. 当这一组 CP 已经遍历过时，跳过，遍历下一组；

2. 当当前答案已经大于之前的答案时，即此答案没有意义时，停止遍历。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,cnt;
int hd[405],nt[405],ve[405],ed[405],vs[405];
void addedge(int u,int v,int c){
	nt[++cnt]=hd[u];
	ve[cnt]=v,ed[cnt]=c;
	hd[u]=cnt;
}
int Dfs(int dep,int sum,int lit){
	if(sum>lit)return 0;
	if(dep==n+1)return 1;
	int ans=Dfs(dep+1,sum,lit);
	for(int i=hd[dep];i;i=nt[i]){
		int x=ve[i],y=ed[i];
		if(ans>=t)continue;
		if(vs[x])continue;
		vs[x]=true;
		ans+=Dfs(dep+1,sum+y,lit);
		vs[x]=false;
	} 
	return ans;
}
bool check(int x){
	if(Dfs(1,0,x)>=t)return true;
	else return false;
}
int main(){
	scanf("%d%d%d",&n,&k,&t);
	for(int i=1;i<=k;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		addedge(x,y+n,z);
	}
	int l=0,r=20005,ans=-1;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid))r=mid-1,ans=mid;
		else l=mid+1;
	}
	printf("%d",ans);
	return 0;
}
```

---

