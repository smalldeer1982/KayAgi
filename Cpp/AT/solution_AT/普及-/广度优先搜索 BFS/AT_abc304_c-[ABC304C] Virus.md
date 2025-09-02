# [ABC304C] Virus

## 题目描述

编号为 $1\sim N$ 的人站在二维平面上，编号为 $i$ 的人在坐标 $(X_i,Y_i)$ 上。

现在编号为 $1$ 的人患上了一种病毒，并可以传染到与感染者距离 $D$ 以内的其它人身上。定义两个点的距离为其直线距离，即两个点 $(a_1,b_1)$ 与 $(a_2,b_2)$ 的距离为 $\sqrt{(a_1-a_2)^2+(b_1-b_2)^2}$。请你判断，在足够的时间之后，每个人是否会被感染。

## 说明/提示

- $1\le N,D\le2000$。
- $-1000\le X_i,Y_i\le 1000$
- 坐标互不相同。
- 输入的所有数据均为整数。

## 样例 #1

### 输入

```
4 5
2 -1
3 1
8 8
0 5```

### 输出

```
Yes
Yes
No
Yes```

## 样例 #2

### 输入

```
3 1
0 0
-1000 -1000
1000 1000```

### 输出

```
Yes
No
No```

## 样例 #3

### 输入

```
9 4
3 2
6 -1
1 6
6 5
-2 -3
5 3
2 -3
2 1
2 6```

### 输出

```
Yes
No
No
Yes
Yes
Yes
Yes
Yes
No```

# 题解

## 作者：Molina (赞：6)

# 题目大意：
在二维平面上有 $ N $ 个人，第 $ i $ 个人位于坐标 ( $ X_i $，$ Y_i $ ) 上。

现在第一个人感染了病毒，病毒会在传染给离他的距离（欧几里得距离）小于等于 $ D $ 的人。

依次判断最后每个人是否被感染。
# 本题思路：
看到这种题，第一时间可以想到用广搜去解，但看看本题数据范围 $ N $ 小于 $ 2000 $，就直接用递归解出来了。
### 步骤：
1. 输入，用 $ a $ 和 $ b $ 数组存坐标，$ c $ 数组存状态（见代码）。先给第一个人标记为 $ 1 $。

2. 开循环模拟，若还未被感染，就进行判断，判断后递归，找出所有被感染的人后，一一标记。

3. 最后判断输出结果。

详细讲解见代码。
# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d;
int a[2005],b[2005];//存每个人的坐标
bool c[2005];//存每个人的状态（是否被感染）
void cz(int x,int y){
	for(int i=2;i<=n;i++){
		if(c[i]==0){
			if(sqrt((x-a[i])*(x-a[i])+(y-b[i])*(y-b[i]))<=d){
				c[i]=1;	
				cz(a[i],b[i]);
			}
		}
	}
	return;
}//递归函数，如果符合情况就标记
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
	}
	c[1]=1;//先给第一个感染的人标记
	for(int i=2;i<=n;i++){//开始模拟
		if(c[i]==0){
			if(sqrt((a[1]-a[i])*(a[1]-a[i])+(b[1]-b[i])*(b[1]-b[i]))<=d){//欧几里得距离
				c[i]=1;//标记
				cz(a[i],b[i]);//递归
			}
		}
		
	}
	for(int i=1;i<=n;i++){
		if(c[i]==1)  cout<<"Yes"<<endl;
		else  cout<<"No"<<endl;
	}//判断后输出
	return 0;
}
```

---

## 作者：cjh20090318 (赞：5)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

有 $N$ 个人，他们分别在坐标为 $(X_i,Y_i)$ 的点上（$N$ 个人的坐标互不相同）。

第一个人被感染了病毒，他将会传染给道他欧几里得距离小于等于 $D$ 的人。

请你求出 $N$ 个人是否被感染。

## 分析

传播病毒这种题，其实第一眼就会想到广度优先搜索。

于是只需要把 $1$ 加入队列，每次取出队首，在对 $n$ 个人进行遍历，如果队首到第 $i$ 个人欧几里得距离小于等于 $D$，就加入队列中即可。

时间复杂度 $O(n^2)$。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#include<queue>
int n,d;
bool dis(int x,int y,int X,int Y){//判断 (x,y) 到 (X,Y) 的欧几里得距离是否小于等于 D。
	return (X-x)*(X-x)+(Y-y)*(Y-y)<=d*d;//直接拆开根号，就不需要进行开方运算了。
}
int xx[2002],yy[2002];
bool v[2002];//是否感染病毒。
int main(){
	scanf("%d%d",&n,&d);
	for(int i=1;i<=n;i++) scanf("%d%d",&xx[i],&yy[i]);
	std::queue<int> Q;
	Q.push(1);//第一个人感染病毒。
	for(int u;!Q.empty();){
		u=Q.front();Q.pop();
		if(v[u]) continue;//感染过则不再进行下一波传染。
		v[u]=1;//标记为感染。
		for(int j=1;j<=n;j++)
			if(j!=u && dis(xx[u],yy[u],xx[j],yy[j]) && !v[j])//注意：两个点不能是同一个点！
				Q.push(j);
	}
	for(int i=1;i<=n;i++) puts(v[i]?"Yes":"No");
	return 0;
}
```


---

## 作者：mark0575 (赞：1)

[更好的阅读体验](https://www.cnblogs.com/mark0575-qwq/articles/17458343.html)



### [题目传送门](https://www.luogu.com.cn/problem/AT_abc304_c)


------------
## 题意:
有 $n$ 个人，其中第一个人生了病，每个生了病的人都会传给与他欧几里得距离不大于 $D$ 的人。请问最后每个人的生病情况。



## 题解：
我们可以借用最小生成树的思想，把每个距离不大于 $D$ 的边都存下来，然后用最小生成树的方法把他们连成几个连通块。如果这个人和第一个人在一个连通块里，这个人就生病了。

时间复杂度：$O(N^2)$

## AC code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2000+10;
int n,d;
int x[N],y[N];
struct node{//存图
	int x,y;
}r[N*N];
int len;
int f[N];
int find(int x)
{
	if(x==f[x])
	{
		return x;
	}
	return f[x]=find(f[x]);
 } 
bool check(int x1,int x2,int y1,int y2)//判断距离是否大于D
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)<=d*d; 
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
		{
			if(i==j)
			{
				continue;
			}
			if(check(x[i],x[j],y[i],y[j]))
			{
				r[++len].x=i;
				r[len].y=j;
			}
		}
	}
	for(int i=0;i<=n+1;i++)
	{
		f[i]=i;
	}
	for(int i=1;i<=len;i++)//最小生成树
	{
		int xx=find(r[i].x);
		int yy=find(r[i].y);
		if(xx==yy)
		{
			continue;
		}
		f[xx]=yy;
	}
	for(int i=1;i<=n;i++)
	{
		int xx=find(1);
		int yy=find(i);
		if(xx==yy)
		{
			cout<<"Yes\n";
		}
		else
		{
			cout<<"No\n";
		}
	}
	return 0;
 }

```

---

## 作者：Elairin176 (赞：1)

[CODE](https://www.luogu.com.cn/problem/AT_abc304_c)        
简单 dfs。          
## 题意
有 $n$ 个人，第 $i$ 个人的坐标为 $(x_i,y_i)$。     
现在有病毒，只有第 $1$ 个人被感染，被感染的人会传染给和他欧几里得距离不超过 $d$ 的所有人，求最后所有人是否被感染。
## 解法
我们从第 $1$ 个人开始 dfs，每次 dfs 扫一遍所有人，判断距离，之后进行继续 dfs 即可。注意感染的人要打上标记并且再次扫到时不能继续 dfs。    
[CODE](https://www.luogu.com.cn/paste/63l2599j)

---

## 作者：FreedomKing (赞：1)

### 思路

搜索板子题，通过 $O(n^2)$ 复杂度预处理出 $a_i$ 与 $a_j$ 的欧几里得距离，如果距离长度 $\le D$ 就在 $a_i$ 和 $a_j$ 间加一条边，每遍历一个就标记为已被传染，最后遍历这 $n$ 个元素，记录被标记的数量。

### AC Code
```
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5;
int a[N][N],n,m,t,k;
struct node{
	int x,y;
}f[N];
map<int,int>mp;
vector<int>G[N];
void dfs(int x){
	int len=G[x].size();
	for(int j=0;j<len;j++){
		if(!mp[G[x][j]]){
			mp[G[x][j]]=true;
			dfs(G[x][j]);
		}
	}
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>f[i].x>>f[i].y;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(sqrt((f[i].x-f[j].x)*(f[i].x-f[j].x)+(f[i].y-f[j].y)*(f[i].y-f[j].y))<=m){
				G[i].push_back(j);
				G[j].push_back(i);
			}
		}
	}
	mp[1]=true;
	dfs(1);
	for(int i=1;i<=n;i++){
		if(mp[i]) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：DengDuck (赞：1)

直接利用 BFS 求解即可。

首先将第一个人加入队列。

接下来，对于队列的每个人，我们都看看其是否可以感染一个人，也就是看距离，并将此人打上感染标记加入队列。

最后输出即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,d,vis[2005],x[2005],y[2005];
queue<LL>q;
LL cal(LL i,LL j)
{
	return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i]>>y[i];
	}
	vis[1]=1;
	q.push(1);
	while(!q.empty())
	{
		LL t=q.front();
		q.pop();
		for(int i=1;i<=n;i++)
		{
			if(!vis[i]/*不要重复添加*/&&cal(t,i)<=d*d/*判断距离*/)
			{
				vis[i]=1;//标记感染
				q.push(i);
			}
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i])
		{
			puts("Yes");
		}
		else
		{
			puts("No");
		}
	}
}
```

---

## 作者：PineappleSummer (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc304_c)

一眼深搜。

### 1.欧几里得距离
已知点 $A(a_1,a_2),B(b_1,b_2)$，则点 $A$ 与 点 $B$ 之间的欧几里得距离为 $\sqrt{(a_1-b_1)^2 +(a_2-b_2)^2}$。

于是就很轻易地得出求欧几里得距离的函数。
```cpp
double odis(int x,int y,int x2,int y2)
{
	return sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
}
```
### 2.深搜
用 $f$ 数组标记该人是否被感染。

主函数调用 `dfs(1)`。
```cpp
void dfs(int i)
{
	f[i]=1;//标记该人被感染
	for(int j=1;j<=n;j++)//判断每个人与第i个人的距离
		if(!f[j]&&odis(x[i],y[i],x[j],y[j])<=d) dfs(j);//距离不超过d，则第j个人会被感染，从j开始搜索
}
```
注意：判断第 $j$ 个人与第 $i$ 个人的距离是否不超过 $d$ 时，要注意 $j$ 不能等于 $i$。
### 3.输出
如果 $f_i$ 为 $1$，则说明被感染，输出 `Yes`，否则输出 `No`。
```cpp
for(int i=1;i<=n;i++)
{
	if(f[i]) printf("Yes\n");
	else printf("No\n");
}
```

[完整代码](https://atcoder.jp/contests/abc304/submissions/42017529)

---

## 作者：qwertim (赞：0)

# 题意
有 $n$ 个人，第 $i$ 个人在坐标为 $(X_i,Y_i)$ 的点上，而第一个人感染了病毒，病毒会传播到与他的欧几里得距离小于 $D$ 的人，请求出这 $N$ 人里哪些人被感染了。
# 思路
我们把这道题转化一下：有 $n$ 个点，如第 $i$ 个人与第 $j$ 个人的欧几里得距离小于 $D$，就称第 $i$ 个点与第 $j$ 个点有一条边，问第一个点共能到达几个点。

这么想就很简单了。

我们定义一个布尔类型的二位数组，其中 $b_{i,j}$ 表示第 $i$ 个人与第 $j$ 个人的欧几里得距离是否小于 $D$，或者第 $i$ 个点与第 $j$ 个点是否有边。

最后再用 dfs 搜索第一个点可以到达的所有点即可。

时间复杂度 $O(n^2)$。
# 代码
```cpp
#include<bits/stdc++.h>
#define fo(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
int n,d,x[2005],y[2005];
bool b[2005][2005],vis[2005];
void dfs(int x){
	vis[x]=1;
	fo(i,1,n)
		if(b[x][i]&&!vis[i])dfs(i);//如有边且没被访问过则搜索
}
int main(){
	cin>>n>>d;
	fo(i,1,n)cin>>x[i]>>y[i];
	fo(i,1,n)	
		fo(j,1,n){
			double a=(x[i]-x[j])*(x[i]-x[j]),bb=(y[i]-y[j])*(y[i]-y[j]);
			double tmp=sqrt(a+bb);//算出第i人与第j人的欧几里得距离
			if(tmp<=d)b[i][j]=1;//是否有边
		}
	dfs(1);
	fo(i,1,n){
		if(vis[i])cout<<"Yes"<<endl;//如有病毒，Yes
		else cout<<"No"<<endl;//否则No
	}
	return 0;
}
```
AC记录：[link](https://atcoder.jp/contests/abc304/submissions/41944596)

---

## 作者：Crazyouth (赞：0)

**翻译**

有 $n$ 个人，第 $i$ 个人站在坐标 $(x_i,y_i)$。现在第 $1$ 个人感染了病毒，只要与任意被感染的人距离小于等于 $D$，就会被感染，问最后所有的人哪些感染了。（点 $(x_1,y_1),(x_2,y_2)$ 间的距离为 $\sqrt{(x_1-x_2)^2+(y_1-y_2)^2}$）。

**分析**

一看数据范围，$n\le 2000$，一种大概是 $O(n^2)$ （如有错误，欢迎大佬指正）的递归做法浮现脑海。

我们可以以第 $k$ 个人为病原体，把这个人周围与他距离小于等于 $D$ 的都感染了，然后再以他们为病原体，继续感染，不就做完了吗？

**AC Code**

```
#include <bits/stdc++.h>
using namespace std;
double x[2001],y[2001],g[2001],n,d;//x,y数组存位置，g数组表示是否感染
double dist(double ax,double ay,double bx,double by)//计算距离
{
	return sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by));
}
void spread(int s)//以第s人为病原体传播
{
	if(!g[s]) return;//假如他没感染，跳过
	for(int i=1;i<=n;i++)//对n个人感染
	{
		if(i==s) continue;//如果是他自己，跳过
		if(g[i]) continue;//如果这个人感染过了，跳过
		if(dist(x[s],y[s],x[i],y[i])<=d)//感染
		{
			g[i]=1;
			spread(i);//传播
		}
	}
} 
int main()
{
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>x[i]>>y[i];
	g[1]=1;//1号感染了
	spread(1);//开始传播
	for(int i=1;i<=n;i++)
	{
		if(g[i]) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

这题，可以用一种类似于 BFS 的方法。

一开始，先把 $1$ 号点放入队列。

用 $head$ 和 $tail$ 记录当前未处理的头和尾。

对于每一个点，查找符合的点，放入队列。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d,x[2001],y[2001],a[20001];
bool vis[2001];
int js(int p,int q){
	return (x[p]-x[q])*(x[p]-x[q])+(y[p]-y[q])*(y[p]-y[q]);
}
int main(){
	int head=0,tail=1;
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
	vis[1]=1;
	a[1]=1;
	while(head<tail){
		head++;
		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			if(js(i,a[head])<=d*d){
				vis[i]=1;
				a[++tail]=i;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(vis[i])cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：CheZiHe929 (赞：0)

# AT_abc304_c 题解
## 原题链接
[**洛谷**](https://www.luogu.com.cn/problem/AT_abc304_c)

[**Atcoder**](https://atcoder.jp/contests/abc304/tasks/abc304_c)

## 题目大意
在二维平面上有 $ 1,\ 2,\ \ldots,\ n $ 个人，第 $ i $ 个人位于 $ (X_i,Y_i) $。

已知第 $ 1 $ 个人已经感染病毒，只要与感染者的欧几里得距离小于 $ d $ 的人都会被感染。

**欧几里得距离**：有 $ 2 $ 点分别为 $ (a_1,\ a_2) $ 和 $ (b_1,\ b_2) $，其欧几里得距离就为 $ \sqrt {(a_1-b_1)^2\ +\ (a_2-b_2)^2} $。

经过足够长的时间后，问着 $ n $ 个人是否被感染病毒。

## 思路分析
既然是经过足够多的时间后再进行判断，我们肯定就不能用 $ 1 $ 次循环判断了，这时我们就要用到**深搜**或者**广搜**了。

如果对深搜或广搜不是很了解的大佬可以看[**这里**](https://www.luogu.com.cn/paste/gnqlhlxq)。

### 深搜
首先让第 $ 1 $ 个人入栈，只要栈不为空就从栈顶元素向下遍历，遍历时要满足 $ 3 $ 个条件：
1. 不为同一个点。
2. 遍历的点 $ i $ 未被感染。
3. 两点的欧几里得距离小于 $ d $。

如果满足以上三个条件，就记录被感染并入栈。

最后遍历结束后将栈顶元素出栈。

### 广搜
广搜的做法和深搜没什么两样，只是把栈改成了队列而已。

## 代码

### 深搜
```cpp
#include<bits/stdc++.h>
using namespace std;
stack<int>s;//定义一个栈s
int x[2005],y[2005];//存横纵坐标 
bool vis[2005];//标记是否被感染病毒
signed main(){
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	s.push(1);//第一个人为传染源，已经被感染，入栈 
	vis[1]=1;//标记已被感染 
	while(!s.empty()){//只要栈不为空 
		int now=s.top();//now为目前栈顶元素
		bool f=0;//记录本次深入遍历有无点可以输出 
		for(int i=1;i<=n;i++){
			double distance=sqrt(pow(x[now]-x[i],2)+pow(y[now]-y[i],2));//根据欧几里得公式算出两点距离 
			if(i!=now&&!vis[i]&&distance<=d){//两点不为同一点且遍历的点i未被感染且两点距离<d 
				vis[i]=1;//标记已被感染 
				s.push(i);//入栈 
				f=1;//本次有可以遍历的点
				break;//深搜的特征——break 
			}
		}
		if(f==0)s.pop();//如果本次没有可遍历的点就出栈（回到上一个岔路口）
	}
	for(int i=1;i<=n;i++){
		if(vis[i])cout<<"Yes"<<endl;//已被感染 
		else cout<<"No"<<endl;//未被感染 
	}
	return 0;
} 
```


### 广搜
```cpp
#include<bits/stdc++.h>
using namespace std;
queue<int>s;//定义一个队列s 
int x[2005],y[2005];//存横纵坐标 
bool vis[2005];//标记是否被感染病毒 
signed main(){
	int n,d;
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i];
	s.push(1);//第一个人为传染源，已经被感染，入队 
	vis[1]=1;//标记已被感染 
	while(!s.empty()){//只要队列不为空 
		int now=s.front();//now为目前队首元素 
		for(int i=1;i<=n;i++){
			double distance=sqrt(pow(x[now]-x[i],2)+pow(y[now]-y[i],2));//根据欧几里得公式算出两点距离 
			if(i!=now&&!vis[i]&&distance<=d){//两点不为同一点且遍历的点i未被感染且两点距离<d 
				vis[i]=1;//标记已被感染 
				s.push(i);//入队 
			}
		}
		s.pop();//出队 
	}
	for(int i=1;i<=n;i++){
		if(vis[i])cout<<"Yes"<<endl;//已被感染 
		else cout<<"No"<<endl;//未被感染 
	}
	return 0;
}
```


## AC 记录
[**洛谷深搜**](https://www.luogu.com.cn/record/112110841)

[**洛谷广搜**](https://www.luogu.com.cn/record/112110929)

[**Atcoder 深搜**](https://atcoder.jp/contests/abc304/submissions/42021756)

[**Atcoder 广搜**](https://atcoder.jp/contests/abc304/submissions/42021780)

**THE END.**

**THANK YOU.**

---

