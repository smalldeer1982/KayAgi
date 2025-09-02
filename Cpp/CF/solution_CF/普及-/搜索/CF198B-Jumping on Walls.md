# Jumping on Walls

## 题目描述

瓦西亚在和忍者玩电脑游戏。在这个关卡，瓦西亚需要操控忍者走出一个很深的峡谷。

峡谷由两面垂直于地面且互相平行的墙组成，它们的高度为$n$米。我们将这些墙分成许多$1$米长的区域，并从下到上用$1$到$n$的正整数对它们进行编号。有些地方是安全的，忍者可以爬上去。有些地方石头很尖锐，忍者不能待在那里。我们称这些地区为危险地区。

最初忍者在左墙的最下方。他每秒可以执行以下操作之一：

* 向上爬一个区域；
* 向下爬一个区域；
* 跳到对面的墙上。忍者会跳到比他当前所在高度高$k$米的地方。更准确地说，如果在跳跃之前忍者位于一面墙的区域$x$，那么在跳跃之后，他位于另一面墙的区域$x + k$。

如果在某个时间点忍者到达了一个高度大于$n$的区域，那么忍者就可以从峡谷中出来了。

但峡谷被水淹没了，每秒水位会上升一米。最初，水位达到区域$1$的下边界。忍者不能待在被水淹没的地方。忍者和水轮流移动——首先忍者行动，然后水上升一米，然后忍者再行动，以此类推。

如果忍者可以离开峡谷，那这个关卡就完成了。

在几次失败的尝试之后，瓦西亚开始怀疑是否有可能完成这一关卡。请回答他的问题。

## 说明/提示

在第一个样例中，忍者可以先跳到右边的墙，然后沿着右边的墙往下走一米，然后跳到左边的墙。再跳跃一次忍者就可以离开峡谷。

在第二个样例中，忍者是无法离开峡谷的。

## 样例 #1

### 输入

```
7 3
---X--X
-X--XX-
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
6 2
--X-X-
X--XX-
```

### 输出

```
NO
```

# 题解

## 作者：乐乐乐还在乐 (赞：6)

# CF198B 题解

**[题目传送门](https://www.luogu.com.cn/problem/CF198B)**

### 题目大意

- 忍者想从逃出峡谷。

- 每次行动可以向上爬、向下爬或跳到另一面墙上。

- 问忍者是否能逃出峡谷。

### 分析题目

这道题是一道 dfs。

只需要注意一下剪枝即可通过。

### 思考算法

dfs 五步骤：状态、转移、初始状态、出口、剪枝。

**状态：**

我们需记录一个时刻的水的深度、忍者在哪面墙和忍者的高度，即：

```cpp
water,where,height
```

**转移：**

可由：
```cpp
dfs(water,where,height)

```
继续搜索以下几个状态：
```cpp
dfs(water+1,where,height+1)
```
```cpp
dfs(water+1,where,height-1)
```
```cpp
dfs(water+1,where^1,height+k)
```

**初始状态：**

一开始，忍者从左边的第 $1$ 号墙开始走，水位为 $0$，即：

```cpp
water=1,where=0,height=1
```

**出口：**

当忍者遇到以下几种情况时，均为出口：

1.忍者逃出来了；

2.忍者被淹死了；

3.忍者到了危险地带。

**剪枝：**

_划重点！！！划重点！！！_

让我们想想，有哪些地方能剪枝呢？

乍一看，似乎没什么可以剪的地方，所以我就直接提交了。

~~喜提 TLE~~

于是，我仔细想了亿想，发现如果忍者已经来过一个地方了，就不需要再来了。

（因为按顺序搜索时，一个总是先搜到水位低的，再搜到水位高的）

加上这个剪枝后，就万事大吉啦！！！

## 附上AC代码


```cpp
#include<bits/stdc++.h>
#define ll long long;
using namespace std;

int n,k;
int a[2][100005];//a[0][i]表示左边的第i号墙是否安全
//a[1][i]表示右边的第i号墙是否安全
int rmb[2][100005];//rmb用来记录忍者是否来过这个地方
//bool ans=false;

bool dfs(int water,int where,int height){
	if(height>n)return true;//忍者逃出来啦！！！ 
	if(rmb[where][height]==1)return false;//来过这个地方啦，剪！！！ 
	if(a[where][height]==0)return false;//忍者跳到危险地区，剪！！！
	if(water>height)return false;//忍者淹死啦，剪！！！
	
	rmb[where][height]=1;//标记这个地方来过了 
	return dfs(water+1,where^1,height+k)||//跳跃
	dfs(water+1,where,height+1)||//往上走
	dfs(water+1,where,height-1);//往下走
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<=1;i++){
		for(int j=1;j<=n;j++){
			char c;
			scanf(" %c",&c);
			if(c=='X')a[i][j]=0;
			else a[i][j]=1;
		}
	}
	
	//忍者从左边的第1号墙开始走 
	if(dfs(1,0,1)==true)printf("YES\n");
	else printf("NO\n");
	return 0;
}


```

---

## 作者：Alex_Wei (赞：3)

### $BFS$ 基础练习题

因为不会记搜，所以就打了一个 $BFS$

这道题目很适合练习 $BFS$ 的基础能力

如果你还不会 $BFS$ 可以看 [$\color{#00bfff}\text{我的这篇博客}$](https://www.luogu.org/blog/wjz060130/sou-suo-1-kuan-du-you-xian-sou-suo-bfs-yang-xie)

对于给定的两个字符串，先处理掉，$BFS$ 的时候就不用判断了

具体实现细节见代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct pos{
	int h,id,t;//h是当前高度，id是当前在哪一个墙上（0为左，1为右），t是当前水位
};
queue <pos> q;
int n,k,pd[100005][2];
string l,r;
int main()
{
	cin>>n>>k>>l>>r;
	for(int i=1;i<=n;i++){
		if(l[i-1]=='X')pd[i][0]=1;//先处理掉左边的墙
		if(r[i-1]=='X')pd[i][1]=1;//同上
	}
	q.push((pos){1,0,0}),pd[1][0]=1;//将初始值压进队列
	while(!q.empty()){
		pos t=q.front(),nw;q.pop();
		nw=t;nw.h--;nw.t++;//往下爬一格
		if(nw.h>0&&!pd[nw.h][nw.id]&&nw.h>nw.t)//判断是否合法（高度，是否已经走过，还有水位） 
			pd[nw.h][nw.id]=1,q.push(nw);//合法就标记走过，压进队列
		nw=t;nw.h++;nw.t++;//往上爬一格
		if(nw.h>n)cout<<"YES",exit(0);//是否已经完成关卡
		if(!pd[nw.h][nw.id]&&nw.h>nw.t)//判断是否合法
			pd[nw.h][nw.id]=1,q.push(nw); 
		nw=t;nw.h+=k;nw.id=!nw.id;nw.t++;//往对面的墙上跳
		if(nw.h>n)cout<<"YES",exit(0);//同上
		if(!pd[nw.h][nw.id]&&nw.h>nw.t)//判断是否合法
			pd[nw.h][nw.id]=1,q.push(nw);
	}
	cout<<"NO";//搜索完毕不能逃出关卡
	return 0;
}
```


---

## 作者：Juanzhang (赞：2)

~~hack数据真是恶心~~

**进入正题**

~~裸的~~**搜索**

~~不加剪枝会挂的。。~~

我们发现，已经搜过的地方并不需要重复搜索，此外，搜索的顺序也十分重要，于是。。

**代码**

``` cpp
#include <bits/stdc++.h>
using namespace std;

#define nc() getchar()

const int maxn = 1e5 + 10;
int n, k;
bool a[2][maxn], vis[2][maxn];

bool dfs(bool chk, int h, int t) {
	if (h > n) return 1;
	if (vis[chk][h] || a[chk][h] || h < t) return 0;
	return vis[chk][h] = 1, dfs(chk ^ 1, h + k, t + 1) || dfs(chk, h + 1, t + 1) || dfs(chk, h - 1, t + 1);
}

int main() {
	scanf("%d %d", &n, &k);
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = nc() == 'X';
		}
		for (; nc() ^ '\n'; );
	}
	puts(dfs(0, 1, 1) ? "YES" : "NO");
	return 0;
}
```

---

## 作者：_segmenttree (赞：1)

### 思路

这道题非常适合初学宽度优先搜索的人拿来练手。我们只要根据题意模拟即可。

### 注意

每次记得先判断是否越界再去判断是否走过，否则会数组越界。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,vis[100010][2];
char a[2][100010]; 
queue<int>q,p,t;//位置，哪面墙，时间 
int main() {
	cin>>n>>k;
	scanf("%s%s",a[0],a[1]);
	for(int i=1;i<=n;i++){
		if(a[0][i-1]=='X') vis[i][0]=1;
		if(a[1][i-1]=='X') vis[i][1]=1;
	}
	q.push(1),p.push(0),t.push(0);
	while(!t.empty()) {
		int nx=q.front(),f=p.front(),te=t.front();
		q.pop(),p.pop(),t.pop();
		if(nx>n) {//已经离开 
			cout<<"YES";
			return 0;
		}
		if(nx<=te||vis[nx][f]==1) continue ;//已经被水淹或是障碍物或已经走过 
		vis[nx][f]=1;
		q.push(nx-1);
		p.push(f);
		t.push(te+1);//向下 
		q.push(nx+1);
		p.push(f);
		t.push(te+1);//向上 
		q.push(nx+k);
		p.push(1-f);
		t.push(te+1);//往另一面墙跳 
	}
	cout<<"NO";//全部状况搜索完还没方案，不能通过 
	return 0;
}
```

---

## 作者：Allanljx (赞：1)

## 思路
通过 $DFS$ 搜索，但是要用 $book$ 数组记录他有没有走过这个地方。但是并不用考虑水位，因为他并没有让你求步数。

### 注意：
忍者只能从左面的墙（上面的一行）开始走，我被这个问题卡了半个小时。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[1000001],b[1000001];
int book[2][1000001],f=0,n,k;//book[0][i]是左面的墙，book[1][i]是右面的墙 
void dfs(bool w,int x,int s)//w记录哪个是墙，x记录忍者的位置，s记录水的位置 
{
	if(book[w][x]==1) return;//走过了 
	book[w][x]=1;
	if(w==0)//左面的墙 
	{
		if(a[x]=='X') return;//危险区域 
	}
	if(w==1)//右面的墙 
	{
		if(b[x]=='X') return;//危险区域 
	}
	if(f==1) return;//可以走出去 
	if(s>=x) return;//被水淹了
	if(x<1) return;//越界 
	if(x>n)//出去了 
	{
		puts("YES");
		f=1;
	}
	if(w==0)//在左面的墙 
	{
		dfs(1,x+k,s+1);//跳到对面 
		dfs(0,x+1,s+1);//往上 
		dfs(0,x-1,s+1);//往下 
	}
	if(w==1)//在右面的墙 
	{
		dfs(0,x+k,s+1);//跳到对面 
		dfs(1,x+1,s+1);//往上 
		dfs(1,x-1,s+1);//往下 
	}
	return;
}
int main()
{
	cin>>n>>k;
	cin>>(a+1);//从1开始存 
	cin>>(b+1);//从1开始存 
	dfs(0,1,0);
	if(f==0) puts("NO");
	return 0;
}
```


---

## 作者：Federico2903 (赞：0)

## 题意  
这是一道练习 BFS 的好题。  
设忍者的位置为 $n$ ，则忍者可以走到 $n + 1$ ， $n - 1$ ， 或者对面的 $n + k$ 位置。  
最初忍者在左墙的最下方，当忍者到达了一个**高度大于 $n$ 的区域**，那么忍者就可以从峡谷中出来了。  
但峡谷被水淹没了，每秒水位会上升一米。我们设忍者已经爬了 $t$ 次，也就是说水位已经达到了 $t$ ，如果 $n \leq t$ 那么这种情况是不可取的。  
如果忍者曾经到达过一个区域，我们就不必再前往那个区域，否则会出现重复的情况。  
我们用一个二维数组来表示两堵墙， $wall[x][0]$ 表示左边那堵墙的第 $x$ 个位置，反之同理。  
如果一个地方是危险的，我们亦可将其看作是曾经走过（都属于不可取的情况），所以当 $wall[x][0]$ 的值为 $1$ 时，表示此地已经走过或者是障碍，反之则是未走过的安全地带。  
然后用 BFS 广搜，从左下角开始，每次扩展三个节点（上，下，异侧跳）。  
更多细节见代码注释。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
int wall[100005][2];//标记数组
string leftw,rightw;
struct pos{//用来表示忍者的位置
	int h,t;//h为忍者的高度，t为忍者用了的时间
	int way;//忍者在哪堵墙 0为左 1为右
	pos(){}
	pos(int h,int t,int way){//构造函数
		this->h=h;
		this->t=t;
		this->way=way;
	}
};
queue<pos> q;
void bfs(pos start){
	q.push(start);
	wall[1][0]=1;//标记左下角走过了
	while(!q.empty()){
		pos t=q.front();
		q.pop();
		if(t.h-1>0&&!wall[t.h-1][t.way]&&t.h-1>t.t+1){//向下走
			wall[t.h-1][t.way]=1;//打标记
			q.push(pos(t.h-1,t.t+1,t.way));//扩展
		}
		if(t.h+1>n){//向上走可以直接走出
			cout << "YES";
			return;//离开了峡谷
		}
		if(!wall[t.h+1][t.way]&&t.h+1>t.t+1){//向上走无法直接走出
			wall[t.h+1][t.way]=1;
			q.push(pos(t.h+1,t.t+1,t.way));//扩展
		}
		if(t.h+k>n){//向另一边跳直接离开峡谷
			cout << "YES";//离开了峡谷
			return;
		}
		if(!wall[t.h+k][!t.way]&&t.h+k>t.t+1){//扩展异侧跳
			wall[t.h+k][!t.way]=1;
			q.push(pos(t.h+k,t.t+1,!t.way));
		}
	}
	cout<<"NO";//所有可能性都无法逃出峡谷，输出NO
	return;
}
int main(){
	cin >> n >> k;
	cin >> leftw >> rightw;
	for(int i=1;i<=n;i++){
		if(leftw[i-1]=='X'){
			wall[i][0]=1;
		}
		if(rightw[i-1]=='X'){
			wall[i][1]=1;
		}//处理字符串
	}
	bfs(pos(1,0,0));//从左下角开始搜索
	return 0;
}
```

---

