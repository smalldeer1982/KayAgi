# Resort

## 题目描述

Valera 终于决定要去滑雪胜地了！

Valera 意识到自己可能会在新地方迷路，但是有位好心人告诉他胜地有 $n$ 个目的地（每个目的地的编号从 $1$ 到 $n$ ），目的地只会是酒店或雪山。

Valera 又发现胜地有多条雪道，并且对于每个目的地 $v$ 只可能存在一个出发点 $u$ （每个目的地只可能从另外**一个**目的地滑过来）。我们也知道没有雪道会以酒店作为出发点。

Valera 怕他会在胜地迷路，所以他想让你告诉他一条他可以滑行的路径。这条路径包含目的地 $v_1, v_2, ... , v_k (k>=1 )$ 并需要符合以下要求：

1. 目的地 $v_1, v_2, ... , v_{k-1}$ 都是雪山，只有 $v_k$ 是酒店。

2. 对于每个整数 $i (1 <= i <= k)$ ，只有一条以 $v_i$ 为出发点的雪道，也就是说目的地 $v_i$ 只对应**一个**目的地。

3. 这条路径经过尽可能多的目的地（ $k$ 为最大值）。

帮助 Valera，找到一条符合所有要求的路径吧！

## 样例 #1

### 输入

```
5
0 0 0 0 1
0 1 2 3 4
```

### 输出

```
5
1 2 3 4 5
```

## 样例 #2

### 输入

```
5
0 0 1 0 1
0 1 2 2 4
```

### 输出

```
2
4 5
```

## 样例 #3

### 输入

```
4
1 0 0 0
2 3 4 2
```

### 输出

```
1
1
```

# 题解

## 作者：Camaro (赞：3)

本题最容易出错的地方就是没注意题目的条件，比如：只有最后一个点为酒店（条件 $1$ ），以及：滑行的路径中不能碰到分叉（条件 $2$ ）

还有一点就是虽然是从雪山滑到酒店，但为了在大多数数据中降低运行时间，我们可以在输入时直接标记酒店，之后 DFS 就以这些点为起点了。也就是反向走，走到不能再走了。

在注意到这些之后，这道题就不算太难了。

```c
 for(int i=1;i<=n;i++)
    {
        cin>>ob[i];
        if(ob[i]==1)
            vis[i]=true;
    }
    
```
第一行输入：标记所有为 $1$ 的点（酒店） 

```c
for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        t[x]++;
        des[i]=x;
    }
```
第二行输入：由于我们是从酒店开始走，所以第二行输入的数据就变成了每个 $i$ 点对应的终点，所以将 Destination 数组设置为 $Des[i]=$ 输入

同时记录每个 $x$ 被输入的次数，如果超过 $1$ 了就不符合第二个条件了（根据题意的逻辑，这个点 $x$ 同时通往 $i_1$ 和 $i_2$ ），所以到时候在 DFS 的时候直接跳过这些点。

```c
 for(int i=1;i<=n;i++)
    {
        if(vis[i]==true)
        {
            path.push_back(i);
            dfs(i,1);
            path.pop_back();
        }
    }
```

DFS 入口，如果为酒店则进入 DFS 函数，进入之前将该点推入 vector 数组，以记录路径，同时在退出函数的时候进行回溯。

DFS 函数有两个变量，点和深度，深度是用来比较最优解的。

```c
void dfs(int x, int dep)
{
    if(dep>ans)
    {
        ans=dep;
        anspath=path;
    }
    int now=des[x];
    if(now!=0&&vis[now]==false&&t[now]==1)
    {
        vis[now]=true;
        path.push_back(now);
        dfs(now,dep+1);
        path.pop_back();
        vis[now]=false;
    }
}

```

将 $now$ 设置为当前点的下一个点（ $Des$ ），判定进入DFS 的条件如下：

1. $now$ 不等于 $0$（ $0$ 的话就意味着没有点可以到达该点）

2. $now$ 未被访问过，这样不会陷入循环也可以避开其他酒店

3. $now$ 被输入的次数等于等于 $1$ ，如果大于 $1$ ，根据题目条件 $2$ ，该点为死路，不能经过这个点

在写完这些后，只需要将 $vis$ 数组标记为 $true$ ，推入 vector 数组，并在退出的时候全部回溯

并且在进入函数的时候要判断当前深度是否大于最优解，如果大于则替换最优解，并且将 $path$ vector 数组直接赋值 $anspath$ vector 数组


在写完这些后把 $anspath$ vector 数组倒着输出出来就可以了，毕竟我们是从酒店出发的。

```c
cout<<anspath.size()<<endl;
    for(int i=anspath.size()-1;i>=0;i--)
    {
        cout<<anspath[i]<<" ";
    }
```


---

## 作者：Fuxh_18 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF350B)
## 思路
**本题用 dfs。**

路径给出了两个条件：

1. 起点只能为雪山。
2. 只有终点为酒店。
3. 路途中没有分岔。

如果直接搜索，能到达的点很多，很麻烦。我们可以考虑倒着搜，即只能从从酒店出发，往回搜索，只能到达雪山。需要记录：一个点的分岔，一个点是雪山还是酒店，最长路径的长度和经过的点。

注：因为是倒着搜，所以存边要倒过来，输出要倒过来。

## [AC](https://www.luogu.com.cn/record/168557341) Code


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+1;
bool a[N],vis[N];
int n,num[N],mp[N],ansl;
vector<int>q; //搜索时用的 
vector<int>ans; //记录最长路径用的 
void dfs(int len,int u){
	if(len>ansl){
		ansl=len;
		ans=q;
	}
	int v=mp[u];
	if(num[v]==1&&v&&!vis[v]&&!a[v]){ //判断下一个点能不能走 
		vis[v]=1;
		q.push_back(v);
		dfs(len+1,v);
		vis[v]=0;
		q.pop_back(); //回溯 
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		int x;
		cin>>x;
		num[x]++; //记录分岔 
		mp[i]=x; //倒着存 
	}
	for(int i=1;i<=n;i++){
		if(a[i]){ //只从酒店出发 
			q.push_back(i);
			dfs(1,i);
			q.pop_back();
		}
	}
	cout<<ansl<<endl;
	while(ansl--){ //倒着搜要倒着存 
		cout<<ans[ansl]<<' ';
	}
	return 0;
}
```
完结撒花。

---

