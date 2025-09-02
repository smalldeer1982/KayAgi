# Quarrel

## 题目描述

Friends Alex and Bob live in Bertown. In this town there are $ n $ crossroads, some of them are connected by bidirectional roads of equal length. Bob lives in a house at the crossroads number $ 1 $ , Alex — in a house at the crossroads number $ n $ .

One day Alex and Bob had a big quarrel, and they refused to see each other. It occurred that today Bob needs to get from his house to the crossroads $ n $ and Alex needs to get from his house to the crossroads $ 1 $ . And they don't want to meet at any of the crossroads, but they can meet in the middle of the street, when passing it in opposite directions. Alex and Bob asked you, as their mutual friend, to help them with this difficult task.

Find for Alex and Bob such routes with equal number of streets that the guys can follow these routes and never appear at the same crossroads at the same time. They are allowed to meet in the middle of the street when moving toward each other (see Sample 1). Among all possible routes, select such that the number of streets in it is the least possible. Until both guys reach their destinations, none of them can stay without moving.

The guys are moving simultaneously with equal speeds, i.e. it is possible that when one of them reaches some of the crossroads, the other one leaves it. For example, Alex can move from crossroad $ 1 $ to crossroad $ 2 $ , while Bob moves from crossroad $ 2 $ to crossroad $ 3 $ .

If the required routes don't exist, your program should output -1.

## 样例 #1

### 输入

```
2 1
1 2
```

### 输出

```
1
1 2 
2 1 
```

## 样例 #2

### 输入

```
7 5
1 2
2 7
7 6
2 3
3 4
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7 6
1 2
2 7
7 6
2 3
3 4
1 5
```

### 输出

```
6
1 2 3 4 3 2 7 
7 6 7 2 1 5 1 
```

# 题解

## 作者：xh39 (赞：7)

前置算法:bfs

注:不可以不看暴力。

## 暴力$O(n^{4})$
设$f[i][j]$为Alice在$i$点,Bob在$j$点时**最小移动次数**。

$f[i][j]=min\{f[i.v][j.v]\}(i.v!=j.v)+1$($i.v$表示与$i$相邻的点)。

实现方法:将$f[i][j]$想象成一个**结点**,每一个转移$f[i.v][j.v]\text{与}f[i][j]$连一条权值为$1$的边。

由于边权为$1$,所以**bfs**跑最短路就可以了。

至于bfs记录路径,记录下转移过来的结点fa就可以了。具体见正解代码,与暴力的记录路径是一样的。

## 正解$O(n^{3})$

将两人同时走一步想象成Alice**先**走一步,Bob**再**走一步。

设$fa[i][j]$为Alice先走时的最小移动次数,$fb[i][j]$为Bob先走时最小移动次数。

$fa[i][j]=min\{f[i.v][j]\}+1$

$fb[i][j]=min\{fa[i][j.v]\}(i!=j.v)+1$

注:只有Bob先走时有两点不相同时的才有该限制,因为题目中有两句话:

> They are allowed to meet in the middle of the street when moving toward each other (see Sample 1).

> The guys are moving simultaneously with equal speeds, i.e. it is possible that when one of them reaches some of the crossroads, the other one leaves it. For example, Alex can move from crossroad 1 to crossroad 2 , while Bob moves from crossroad 2 to crossroad 3 .

翻译过来就是

> 可以在边的中间见面(见样例1)

> 其中一个到达某些十字路口时,另一个可能离开。比如Alice在1,Bob在2,那么Alice可以移动到2,Bob移动到3。

所以Alice可以先走到Bob所在的点。然后Bob再走到其它点。

```cpp
#include<iostream>
using namespace std;
struct NOI2020_chaoxianshishu{
	int v,next;
}_[1000005];
int head[1000005],tot=1;
void add(int u,int v){
	_[tot].v=v;
	_[tot].next=head[u];
	head[u]=tot;
	tot++;
}
struct IOI2020_lianjieqingtianshu{
	int va,vb,dis,fa; //a表示alex,b表示bob,dis表示距离,fa表示转移过来的状态。 
	bool firsta; //alex是否先走。 
}list[1000005];
int l=0,r=1;
bool markb[1005][1005],marka[1005][1005];
int kkksc03a[1005],kkksc03b[1005];
int main(){
	int n,m,i,j,k,A,B;
	cin>>n>>m;
	list[0].va=1;
	list[0].vb=n;
	list[0].dis=0;
	list[0].firsta=1;
	list[0].fa=-1; //没有转移边。
	marka[1][n]=1;
	for(i=0;i<m;i++){
		scanf("%d %d",&A,&B);
		add(A,B);
		add(B,A);
	}
	tot=0;
	while(l<r){
		if(list[l].firsta&&(list[l].va==n)&&(list[l].vb==1)){
			cout<<(list[l].dis>>1)<<endl; //由于是Alice先走Bob再走,所以边权变成了2。就要除以2。
			for(i=l;i>=0;i=list[i].fa){
				if(list[i].firsta){ //注意:Bob先走转移过来的结点才会是Alice先走,这时才是最终状态。
					kkksc03a[tot]=list[i].va;
					kkksc03b[tot]=list[i].vb;
					tot++;
				}
			}
			for(i=tot-1;i>=0;i--){ //由于我们是从终点记录到起点,有2种解决方案:①倒序输出。②先输出Bob再输出Alice。这里用的是①。
				cout<<kkksc03a[i]<<" ";
			}
			cout<<endl;
			for(i=tot-1;i>=0;i--){
				cout<<kkksc03b[i]<<" ";
			}
			cout<<endl;
			return 0;
		}
		if(list[l].firsta){
			for(i=head[list[l].va];i;i=_[i].next){
				if(!marka[_[i].v][list[l].vb]){
					marka[_[i].v][list[l].vb]=1;
					list[r].dis=list[l].dis+1;
					list[r].va=_[i].v;
					list[r].vb=list[l].vb;
					list[r].firsta=0; //下一个就该Alice走了。
					list[r].fa=l;
					r++;
				}
			}
		}else{
			for(i=head[list[l].vb];i;i=_[i].next){
				if(!markb[list[l].va][_[i].v]&&_[i].v!=list[l].va){
					markb[list[l].va][_[i].v]=1;
					list[r].dis=list[l].dis+1;
					list[r].va=list[l].va;
					list[r].vb=_[i].v;
					list[r].firsta=1;
					list[r].fa=l;
					r++;
				}
			}
		}
		l++;
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：C6H14 (赞：0)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF29E)

[My blog](https://www.luogu.com.cn/blog/128433/#)

看到最短路标签自信写了个Dijkstra，写到一半发现假掉了……

~~针不戳~~

## 思路

**前置知识：BFS求最短路。**

### 假掉的最短路算法

按照题意，假如从 $1$ 号十字路口到 $n$ 号十字路口的最短路长度为奇数，那么就是答案，因为此时两人相遇时必定在街道中央相遇。

~~这两人什么神奇的视力。~~

但是当最短路长度为偶数时就暴毙了……因为可以让一个人在某两个位置消磨时光，等另一个人走过去后才出来（如样例3），这就不是从 $1$ 号十字路口到 $n$ 号十字路口的最短路了。

### 正解

> 首先，我们打个暴力；加点剪枝；加个记忆化，A了！——[crxis](https://www.luogu.com.cn/user/14512)

辺权为 $1$，可以考虑用BFS求最短路。

但是直接搜时间复杂度太高，所以剪一下枝：

用 $f[x][y][0/1]$ 记录Alice在 $x$，Bob在 $y$，当前轮到Alice/Bob走的状态是否搜索过，假如 $f[x][y][0/1]$ 不为 $0$，就不用搜了。

显然 $1 \leqslant x,y \leqslant n$，每个 $(x,y)$ 最多遍历一次，每次遍历到搜边时又最多遍历n条边（去重边的话），那么时间复杂度最大是 $O(n^3)$。

再看一眼题目，发现要输出路径……

可以直接拿 $f[x][y][0/1]$ 记录是从哪一个状态搜索过来的，节省空间。

## 代码

```cpp
struct edge
{
	int u,v,n;
} e[20005];
int n,m,h[505],l,st[100005],f[505][505][2];//f用于记录从哪个状态过来
queue<int> qx,qy,q;//qx记录Alice的位置，qy记录Bob的位置，q同时记录步数和轮到谁走了
inline void add(int u,int v)//链式前向星加边
{
	e[++l].u=u,e[l].v=v;
	e[l].n=h[u],h[u]=l;
}
int main()
{
	n=read(),m=read();
	for (int i=1;i<=m;++i)
	{
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	qx.push(1);
	qy.push(n);
	q.push(1);
	f[1][n][1]=-1;
	while (!q.empty())//t存储当前轮到谁走了，s存储步数
	{
		int x=qx.front(),y=qy.front(),t=q.front()&1,s=q.front()>>1,v;
		if (x==n && y==1 && t==1)
		{
			write(s,'\n');
			int tx=n,ty=1,i=1;
			write(1,' ');
			while (tx>0 && ty>0)
			{
				if (i)
					st[++st[0]]=tx,ty=f[tx][ty][i];//st存储Bob的路径
				else
					write(ty,' '),tx=f[tx][ty][i];
				i^=1;
			}
			putchar('\n');
			for (int i=1;i<=st[0];++i)
				write(st[i],' ');
			return 0;
		}
		qx.pop(),qy.pop(),q.pop();
		if (t)
		{
			for (int b=h[x];b;b=e[b].n)//Alice走
			{
				v=e[b].v;
				if (f[v][y][t^1])
					continue;
				qx.push(v);
				qy.push(y);
				q.push(s<<1|(t^1));
				f[v][y][0]=x;
			}
		}
		else
		{
			for (int b=h[y];b;b=e[b].n)//Bob走
			{
				v=e[b].v;
				if (f[x][v][t^1] || x==v)
					continue;
				qx.push(x);
				qy.push(v);
				q.push((s+1)<<1|(t^1));
				f[x][v][1]=y;
			}
		}
	}
	write(-1);
	return 0;
}
}
```


---

