# Game with Points

## 题目描述

You are playing the following game. There are $ n $ points on a plane. They are the vertices of a regular $ n $ -polygon. Points are labeled with integer numbers from $ 1 $ to $ n $ . Each pair of distinct points is connected by a diagonal, which is colored in one of 26 colors. Points are denoted by lowercase English letters. There are three stones positioned on three distinct vertices. All stones are the same. With one move you can move the stone to another free vertex along some diagonal. The color of this diagonal must be the same as the color of the diagonal, connecting another two stones.

Your goal is to move stones in such way that the only vertices occupied by stones are $ 1 $ , $ 2 $ and $ 3 $ . You must achieve such position using minimal number of moves. Write a program which plays this game in an optimal way.

## 说明/提示

In the first example we can move stone from point $ 4 $ to point $ 1 $ because this points are connected by the diagonal of color 'a' and the diagonal connection point $ 2 $ and $ 3 $ , where the other stones are located, are connected by the diagonal of the same color. After that stones will be on the points $ 1 $ , $ 2 $ and $ 3 $ .

## 样例 #1

### 输入

```
4
2 3 4
*aba
a*ab
ba*b
abb*
```

### 输出

```
1
4 1
```

## 样例 #2

### 输入

```
4
2 3 4
*abc
a*ab
ba*b
cbb*
```

### 输出

```
-1
```

# 题解

## 作者：minecraft_herobrine (赞：1)

注意到 $n\le70$ ，所以你可以直接 $n^3$ 保存路径

设 $p[p_1][p_2][p_3].num$ 表示发生发生变动的是哪个石头

$p[p_1][p_2][p_3].from$ 发生变动的石头原来的位置

$p[p_1][p_2][p_3].res$ 表示要达到这个状态的步数

最短路径用bfs查找，每次分别尝试扩展三个石头。若当前准备扩展的石头和目标的边的颜色和另外两个石头之间边的颜色不同就不进行扩展，如果这个状态已经有答案了也不进行扩展。

在输出路径的时候从 $1,2,3$ 三个点中答案最大的开始沿着 $p[p_1][p_2][p_3].from$ 往回递归，直到递归回初始状态后再输出，具体细节就看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Stone_Pos
{
	int p1,p2,p3,res;
};
struct Path
{
	int res,num,from;
}p[80][80][80];
queue<Stone_Pos> q;
int mp[80][80],n;
void bfs()
{
	int i;
	while(!q.empty())
	{
		Stone_Pos u=q.front();q.pop();
		int u1=u.p1,u2=u.p2,u3=u.p3;
//		printf("%d %d %d\n",u1,u2,u3);
		for(i=1;i<=n;i++)
		{
			if(i==u1 || i==u2 || i==u3) continue;
			//~x表示将x的二进制全部取反，~x=0表示x=-1
			if(mp[u1][i]==mp[u2][u3] && !(~p[i][u2][u3].res))
			{
				p[i][u2][u3].res=u.res+1;//步数+1
				p[i][u2][u3].from=u1;//第一个石头是从u1走到i的
				p[i][u2][u3].num=1;//发生变动的石头是第一个
				//下面两个同理
				q.push((Stone_Pos){i,u2,u3,u.res+1});
			}
			if(mp[u2][i]==mp[u1][u3] && !(~p[u1][i][u3].res))
			{
				p[u1][i][u3].res=u.res+1;
				p[u1][i][u3].from=u2;
				p[u1][i][u3].num=2;
				q.push((Stone_Pos){u1,i,u3,u.res+1});
			}
			if(mp[u3][i]==mp[u1][u2] && !(~p[u1][u2][i].res))
			{
				p[u1][u2][i].res=u.res+1;
				p[u1][u2][i].from=u3;
				p[u1][u2][i].num=3;
				q.push((Stone_Pos){u1,u2,i,u.res+1});
			}
		}
	}
	return;
}
void Print(int p1,int p2,int p3)
{
	if(!p[p1][p2][p3].res) return;//走到初始情况了
	switch(p[p1][p2][p3].num)//来看这个点是改变哪个石头得到的
	{
		case 1:
		{
			Print(p[p1][p2][p3].from,p2,p3);
			printf("%d %d\n",p[p1][p2][p3].from,p1);
			break;
		}
		case 2:
		{
			Print(p1,p[p1][p2][p3].from,p3);
			printf("%d %d\n",p[p1][p2][p3].from,p2);
			break;
		}
		case 3:
		{
			Print(p1,p2,p[p1][p2][p3].from);
			printf("%d %d\n",p[p1][p2][p3].from,p3);
			break;
		}
	}
	return;
}
int main()
{
	int i,j,s1,s2,s3;
	char c;
	scanf("%d",&n);
	scanf("%d %d %d",&s1,&s2,&s3);
	memset(p,-1,sizeof(p));
	p[s1][s2][s3].res=0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			cin>>c;
			if(c=='*') mp[i][j]=0;
			else mp[i][j]=c-'a'+1;
		}
	}
	q.push((Stone_Pos){s1,s2,s3,0});//初始状态入队
	bfs();
	int res=1145141919+810*24,e1,e2,e3;
	//找一下步数最小的那个状态，并作为递归输出的起点
	if(~p[1][2][3].res && p[1][2][3].res<res)
	{
		res=p[1][2][3].res;
		e1=1;e2=2;e3=3;
	}
	if(~p[1][3][2].res && p[1][3][2].res<res)
	{
		res=p[1][3][2].res;
		e1=1;e2=3;e3=2;
	}
	if(~p[2][1][3].res && p[2][1][3].res<res)
	{
		res=p[2][1][3].res;
		e1=2;e2=1;e3=3;
	}
	if(~p[2][3][1].res && p[2][3][1].res<res)
	{
		res=p[2][3][1].res;
		e1=2;e2=3;e3=1;
	}
	if(~p[3][1][2].res && p[3][1][2].res<res)
	{
		res=p[3][1][2].res;
		e1=3;e2=1;e3=2;
	}
	if(~p[3][2][1].res && p[3][2][1].res<res)
	{
		res=p[3][2][1].res;
		e1=3;e2=2;e3=1;
	}
	if(res>1919810)//无法走到任何一种可能的结束状态
	{
		printf("-1");
		return 0;
	}
	printf("%d\n",res);
	Print(e1,e2,e3);//递归输出路径
	return 0;
}
```


---

## 作者：_edge_ (赞：0)

我们先来分析一下题目的条件，发现这个操作并不好搞，再看一眼数据范围 $n \le 70$，那显然是要依赖于 $O(n^3)$ 或者 $O(n^4)$ 的。

我们发现这个石头的位置如果固定，那答案也是固定的。

所以可以尝试将石头的位置都压进状态里面，值得一提的是，这个看起来是 DP 实际上会产生后效性。

可以把状态看成几个点，然后如果能转移就看成一条边，很容易发现它是一个边权为 $1$ 的最短路问题。

边权为 $1$ 的最短路问题可以用 BFS 快速解决。

那么如何确定源点以及汇点呢？相信很多人都会拿起点作为源点，但是那样的话就不太符合 BFS 的形式，所以就要拿最终状态作为源点。

复杂度 $O(n^4)$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int INF=75;
struct _node_data{
	int a,b,c;
};
queue <_node_data> q;
int n,f[INF][INF][INF],f1[INF][INF][INF][5];
char Map[INF][INF];
void print(int a,int b,int c) {
	if (f1[a][b][c][0]==0 || f1[a][b][c][1]==0 || f1[a][b][c][2]==0) return ;
	if (f1[a][b][c][0]!=a) cout<<a<<" "<<f1[a][b][c][0]<<"\n";
	if (f1[a][b][c][1]!=b) cout<<b<<" "<<f1[a][b][c][1]<<"\n";
	if (f1[a][b][c][2]!=c) cout<<c<<" "<<f1[a][b][c][2]<<"\n";
	print(f1[a][b][c][0],f1[a][b][c][1],f1[a][b][c][2]);
}
signed main()
{
	memset(f,63,sizeof f);
	ios::sync_with_stdio(false);
	cin>>n;int a=0,b=0,c=0;
	cin>>a>>b>>c;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			cin>>Map[i][j];
	f[1][2][3]=f[1][3][2]=f[2][1][3]=f[2][3][1]=f[3][1][2]=f[3][2][1]=0;
	q.push((_node_data){1,2,3});
	q.push((_node_data){1,3,2});
	q.push((_node_data){2,1,3});
	q.push((_node_data){2,3,1});
	q.push((_node_data){3,1,2});
	q.push((_node_data){3,2,1});
	while (q.size()) {
		_node_data xx=q.front();q.pop();
//		cout<<xx.a<<" "<<xx.b<<" "<<xx.c<<" "<<f[xx.a][xx.b][xx.c]<<" ???????\n"; 
		for (int i=1;i<=n;i++) {
			if (i==xx.a || i==xx.b || i==xx.c) continue;
			if (Map[xx.b][xx.c]==Map[xx.a][i]) {
				if (!(f[i][xx.b][xx.c]<f[xx.a][xx.b][xx.c]+1)) {
					f[i][xx.b][xx.c]=f[xx.a][xx.b][xx.c]+1;
					f1[i][xx.b][xx.c][0]=xx.a;
					f1[i][xx.b][xx.c][1]=xx.b;
					f1[i][xx.b][xx.c][2]=xx.c;
					q.push((_node_data){i,xx.b,xx.c});
				}
			}
			if (Map[xx.b][xx.a]==Map[xx.c][i]) {
				if (!(f[xx.a][xx.b][i]<f[xx.a][xx.b][xx.c]+1)) {
					f[xx.a][xx.b][i]=f[xx.a][xx.b][xx.c]+1;
					f1[xx.a][xx.b][i][0]=xx.a;
					f1[xx.a][xx.b][i][1]=xx.b;
					f1[xx.a][xx.b][i][2]=xx.c;
					q.push((_node_data){xx.a,xx.b,i});
				}
			}
//			if (i==3) cout<<xx.a<<" "<<xx.b<<" "<<xx.c<<" "<<Map[xx.a][xx.c]<<" "<<Map[xx.b][i]<<" endl\n";
			if (Map[xx.a][xx.c]==Map[xx.b][i]) {
				if (f[xx.a][i][xx.c]<f[xx.a][xx.b][xx.c]+1) continue;
				f[xx.a][i][xx.c]=f[xx.a][xx.b][xx.c]+1;
				f1[xx.a][i][xx.c][0]=xx.a;
				f1[xx.a][i][xx.c][1]=xx.b;
				f1[xx.a][i][xx.c][2]=xx.c;
				q.push((_node_data){xx.a,i,xx.c});
			}
		}
	}
//	cout<<f[6][3][2]<<" ???\n";
	int xx=f[a][b][c];
	if (xx<1e9) cout<<xx<<"\n";
	else {cout<<"-1\n";return 0;}
	print(a,b,c);
	return 0;
}
```


---

