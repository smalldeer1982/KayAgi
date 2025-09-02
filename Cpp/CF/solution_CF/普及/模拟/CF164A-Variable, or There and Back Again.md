# Variable, or There and Back Again

## 题目描述

给你一个n个点，m条边的有向图（不一定连通），每个点都被标上了0、1或2。如果有一条路径是从一个标为1的点开始，途径若干个标为0或2的点，最后到达一个标为2的点，那么这条路径上的所有点都算作被访问过。请问最后有多少点被访问过？

## 说明/提示

对于样例1，唯一的合法路径1->2->3->4包含了全部的点。

对于样例2，唯一的一条合法路径3->1包含了1和3两个点，点2没有在路径中。

对于样例3，没有一条路径是合法的。

## 样例 #1

### 输入

```
4 3
1 0 0 2
1 2
2 3
3 4
```

### 输出

```
1
1
1
1
```

## 样例 #2

### 输入

```
3 1
1 0 2
1 3
```

### 输出

```
1
0
1
```

## 样例 #3

### 输入

```
3 1
2 0 1
1 3
```

### 输出

```
0
0
0
```

# 题解

## 作者：icefake (赞：3)

# CF164A Variable, or There and Back Again

首先我们来翻译一下题意

这道题的题意其实很简单

### 题意
> 输入 $n$ 和 $m$ ，表示有 $n$ 个点和 $m$ 条边（单向）
> 若一条路径从 $1$ 开始，到 $2$ 结束，并且中间没有 $1$ ，那么这条路径就是“有趣路径”
> 询问：哪些是“有趣路径”哪些不是

说实话。。。

这道题有亿点点水/xk

至于思路——

两次BFS直接暴搜就完事了

第一次从 $1$ 开始搜，第二次 $2$ 开始搜

关于判定——

若两次都搜到了，那么就是“有趣路径”

代码也没啥好讲的，就把核心的BFS放出来一下

### 核心代码（部分——仅有一次BFS）
```cpp
while(!q.empty()) {
	int now = q.front();
	q.pop();
	for(register int i = 0; i < edge[now].size(); i ++) {
		int x = edge[now][i];
		if (a[x] != 1 && !vis1[v]) {
            vis1[x] = 1;
		    q.push(x);
        }
	}
}
```

完结撒花！！！

啦啦啦






---

## 作者：luoyicen (赞：2)

# CF164A 题解

[题目传送门](https://www.luogu.com.cn/problem/CF164A)

蒟蒻的第一篇题解，求过！！！

## 题目大意
说实话，其实下面两位大佬写的题目大意已经够详细了。不过要注意的是，可能存在**多个**标记为 $1$ 和 $2$ 的点，从标号为 $1$ 到标号 $2$ 的路径可能**不止一条**，并且题目要求的是**所有**可以从标号为 $1$ 到标号 $2$ 的路径所经过的点有哪些。

## 暴力做法

### 思路
暴力的算法应该不难想出来，只需要遍历所有标记为 $1$ 的点，然后一个一个点往后找，找到标记为 $2$ 点就更新一下被标记过的点。

### 代码
~~这个代码还可以优化。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[100010],r[100010],maxn=0,ansr[100010];
vector<int> ve[100010];
void get_ans(){//标记 
	for(int i=1;i<=n;i++){
		ansr[i]=max(r[i],ansr[i]);
	}
}
void dfs(int d,int maxl){//深度优先搜索 
	if(r[d]==1) return; //已经被遍历过了 
	r[d]=1;//标记走过 
	if(f[d]==2){
		get_ans();
	}
	for(int i=0;i<ve[d].size();i++){
		dfs(ve[d][i],maxl+1);
	}
	r[d]=0;//回溯 
}
void add(int x,int y){//存边，注意是有向图 
	ve[x].push_back(y);
	//ve[y].push_back(x);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i]);
	}
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i=1;i<=n;i++){
		if(f[i]==1){
			dfs(i,1);
		}
	}
	for(int i=1;i<=n;i++){
		printf("%d\n",ansr[i]);
	}
	return 0;
}
```

## 满分做法

## 思路
其实我们只需要换一个思路。可以从所有标记为 $1$ 的点开始遍历存下可以达到的点有哪些，从标记为 $2$ 的点开始遍历也存下可以达到的点有哪些，如果一个点同时被标记了两次，那么说明这个点可以被访问过。

这里也有一个注意点，就是应该注意在第二次遍历的时候，碰到标记为 $1$ 的点就应该标记后并**结束**，而不是继续遍历下去（~~因为这个我 WA 了两次~~）。

## 代码
代码我是使用 DFS 实现的，楼下两个大佬都是 BFS。

~~我才不会告诉你我是因为 BFS 不会才用 DFS 的。~~


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,f[100010],r[100010],maxn=0,k1[100010],k2[100010];
vector<int> ve1[100010],ve2[100010];
void add(int x,int y){
	ve1[x].push_back(y);
	ve2[y].push_back(x);
}
void dfs1(int d){//标记为1的遍历 
	if(k1[d]) return;
	k1[d]=1;
	for(int i=0;i<ve1[d].size();i++){
		dfs1(ve1[d][i]);
	}
}
void dfs2(int d){//标记为2的遍历 
	if(k2[d]) return;
	k2[d]=1;
    if(f[d]==1) return;//遇到标记为1的就应该标记后就停止遍历 
	for(int i=0;i<ve2[d].size();i++){
		dfs2(ve2[d][i]);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&f[i]);
	}
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
	}
	for(int i=1;i<=n;i++){
		if(f[i]==1){//遇到标记为1的 
			dfs1(i);
		}else if(f[i]==2){//遇到标记为2的 
			dfs2(i);
		}
	}
	for(int i=1;i<=n;i++){
		if(k1[i]+k2[i]==2) printf("1\n");
		else printf("0\n");
    }
	return 0;
}
```

---

## 作者：InfiniteRobin (赞：1)

## 题目大意
[**CF 题目传送门**](https://codeforces.com/contest/164/problem/A)   

给你一个 $n$ 个点，$m$ 条边的图，每个节点有一个标记，若有一条路径，从编号为 $1$ 的点出发，最终到达编号为 $2$ 的点，且途中不经过编号为 $1$ 的点，则该路径上的所有点都算作被访问过。问最后有哪些点被访问过。

---

## 分析

我们第一时间可以想到从编号为 $1$ 的点出发做深搜，按照规定，不经过其他编号为 $1$ 的点，并对遍历到的点做标记。

那么我们怎么截取其中结尾为 $2$ 的路径部分呢？

我们可以把所有边反过来，从所有编号为 $2$ 的点出发，进行深搜，并再打另一个标记。

最后，若是一个点被打上两个标记，则说明该点可以被访问到。输出 $1$ 即可。

注意：在第一个深搜中，可以经过多个编号为 $2$ 的点。而第二个深搜中，若是碰到编号为 $1$ 的点，就要停止深搜。

---

## Code


```cpp
#include<bits/stdc++.h>
using namespace std;
 
vector <int> mp[100005],mp2[100005];
int f[100005]; //编号 
//两个标记 
bool a[100005],b[100005];
int n,m;

void dfs1(int x){ //从编号为 1 的点出发 
	a[x]=1; //打标记 
	for(auto i: mp[x]){	
		if(!a[i]&&f[i]!=1){  //不能经过号为 1 的点
			dfs1(i);
		}
	}
}

void dfs2(int x){ //从号为 2 的点出发 
	b[x]=1;	
	if(f[x]==1){ //遇到号为 1 的点就 return 
		return;
	}
	for(auto i: mp2[x]){
		if(!b[i]){
			dfs2(i);
		}
	}
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>f[i];
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		mp[u].push_back(v);
		mp2[v].push_back(u); //把边反过来 
	}
	for(int i=1;i<=n;i++){
		if(f[i]==1){ 
			dfs1(i);
		}
		if(f[i]==2){
			dfs2(i);
		}
	} 
	for(int i=1;i<=n;i++){
		if(a[i]&&b[i]){ //如果被打上 2 个标记，那么可以被遍历到 
			cout<<"1\n";
		}
		else{
			cout<<"0\n";
		}
		//cout<<a[i]<<" "<<b[i]<<"\n";
	}
	return 0;
}
```
---

[Codeforces RemoteJudge 暂不可用，详见置顶帖。](https://codeforces.com/contest/164/submission/291732605)

---

## 作者：_zhaosihan_qwq_ (赞：0)

# 题解：CF164A Variable, or There and Back Again
**[题目传送门](https://www.luogu.com.cn/problem/CF164A)**
## 题目大意：
给你一个 $n$ 个点， $m$ 条边的有向图（不一定连通），每个点都被标上了$0$、$1$ 或 $2$。如果有一条路径是从一个标为 $1$ 的点开始，途径若干个标为 $0$ 或 $2$ 的点，最后到达一个标为 $2$ 的点，那么这条路径上的所有点都算作被访问过。请问最后有多少点被访问过。
## 思路：
其实这道黄题较水，两个 BFS 暴力搜索擦边过，判断这个点后面的点 1，点 2。注意回溯。
## 注意：
- long long 判断是否要加上。
- 回溯注意要回溯到 $0$，不是 $1$。
- 数组要用 vector。
### 此题较水，代码就不放送了。

---

