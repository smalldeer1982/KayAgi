# Vladik and Favorite Game

## 题目描述

这是一个交互式的问题。

Vladik 在空闲时间最喜欢玩一个游戏。

游戏的场地用一个 $n \times m$ 的矩阵显示，每个格子分为三种类型：

- 「.」—— 普通格子，玩家可以踩上去。
- 「F」—— 终点格子，玩家需要到达这里才能赢得游戏。这里只有一个这样的格子。
- 「*」—— 危险格子，踩到这里会导致游戏失败。

游戏一开始，玩家位于左上角格子 $(1,1)$。

玩家可以通过四个按钮「U」、「D」、「L」、「R」来分别向上、下、左、右移动。

然而并没有那么简单！有时玩家的朋友会调换按钮的功能。「L」和「R」可能会互换，同样的，「U」和「D」也可能会互换。需注意，按钮功能的改变只能在游戏开始时进行。

请帮助 Vladik 赢得这场游戏吧！

## 说明/提示

在第一个测试案例中，所有四个方向都换成了它们的反方向。交互协议的说明如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF811D/950006bce8e634504ab933f77783747c37b83110.png)

这次测试的黑客攻击可以如下描述：

```
4 3 1 1
...
**.
F*.
...
```

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 3
...
**.
F*.
...
1 1
1 2
1 3
1 3
2 3
3 3
4 3
4 2
4 1
3 1
```

### 输出

```
R
L
L
D
U
U
U
R
R
D
```

# 题解

## 作者：hwk0518 (赞：2)

拿到图后首先$BFS$出一条合法路径。沿着合法路径走。一旦要上下走且没弄清楚$U$和$D$是否颠倒，就强制向下走，并弄清$U$和$D$的关系；要左右走同理。

有同学会有疑问：万一强制向下走到$*$，游戏不就结束了吗？

这是不可能的。首先如果我们还没弄清是否颠倒，在之前一定没有任何$U$和$D$操作。所以现在我们一定在第一行。而且我们很明确地知道往上走一定会撞墙，所以我们一定想要往下走。

我们分两种情况讨论：

(1)颠倒了。这样我们就会撞到边界上的墙，没有任何关系。

(2)没有颠倒。正好遂了我们的心愿。

所以强制向下走没有任何关系。左右走时同理。

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
#include<queue>
#include<vector>
using namespace std;

const int N=205;
const int T=1e6+5;
int n,m,dis[N][N],vis[N][N],Tx,Ty;
int hd,tl,top;
int dx[5]={0,0,1,-1};
int dy[5]={1,-1,0,0};
char s[N][N];
int oppolr,oppoud,totfl;
pair<int,int> q[T];
pair<int,int> v[T];

void init()
{
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		scanf("%s",s[i]+1);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			if(s[i][j]=='F')
				Tx=i,Ty=j;
}

bool ok(int x,int y)
{
	if(x<1||x>n||y<1||y>m) return false;
	if(s[x][y]=='*') return false;
	return true;
}

void BFS()
{
	int i;
	hd=1,tl=0;
	q[++tl]=make_pair(1,1);vis[1][1]=1;
	while(hd<=tl)
	{
		pair<int,int> fr=q[hd];++hd;
		pair<int,int> nowT;
		for(i=0;i<4;++i)
		{
			nowT=make_pair(fr.first+dx[i],fr.second+dy[i]);
			if(!ok(nowT.first,nowT.second)) continue;
			if(vis[nowT.first][nowT.second]) continue;
			vis[nowT.first][nowT.second]=1;
			q[++tl]=nowT;dis[nowT.first][nowT.second]=dis[fr.first][fr.second]+1;
		}
		if(vis[Tx][Ty]) break;
	}
	
	if(!vis[Tx][Ty])
	{
		printf("Chen Jiabo tql! Too Difficult!\n");
		totfl=1;
		return;
	}
	
	int nowx=Tx,nowy=Ty;
	while(nowx!=1||nowy!=1)
	{
		v[++top]=make_pair(nowx,nowy);
		pair<int,int> nowT;
		for(i=0;i<4;++i)
		{
			nowT=make_pair(nowx+dx[i],nowy+dy[i]);
			if(dis[nowT.first][nowT.second]==dis[nowx][nowy]-1&&vis[nowT.first][nowT.second]&&
			ok(nowT.first,nowT.second)) break;
		}
		nowx+=dx[i],nowy+=dy[i];
	}
	v[++top]=make_pair(nowx,nowy);
}

int to(pair<int,int> v,pair<int,int> u)
{
	if(u.first==v.first&&u.second==v.second+1) return 2;
	if(u.first==v.first&&u.second==v.second-1) return 1;
	if(u.first==v.first+1&&u.second==v.second) return 4;
	if(u.first==v.first-1&&u.second==v.second) return 3; 
}

void print()
{
	int i=top,j,k;
	for(i;i>1;--i)
	{
		int dir=to(v[i],v[i-1]);
		if(dir<3)
		{
			bool fl=0;
			if(oppolr==dir) printf("%c\n",'L');
			else if(oppolr) printf("%c\n",'R');
			else fl=1,printf("%c\n",'R');
			fflush(stdout);
			
			scanf("%d%d",&j,&k);
			if(make_pair(j,k)==v[i])
			{
				oppolr=2,printf("%c\n",'L'),fflush(stdout);
				scanf("%d%d",&j,&k);
				if(make_pair(j,k)!=v[i-1])
				{
					printf("Huang Zhigang AK IOI!\n");
					return;
				}
			}
			
			if(!oppolr) oppolr=1;
		}
		else
		{
			bool fl=0;
			if(oppoud==dir) printf("%c\n",'U');
			else if(oppoud) printf("%c\n",'D');
			else fl=1,printf("%c\n",'D');
			fflush(stdout);
			
			scanf("%d%d",&j,&k);
			if(make_pair(j,k)==v[i])
			{
				oppoud=4,printf("%c\n",'U'),fflush(stdout);
				scanf("%d%d",&j,&k);
				if(make_pair(j,k)!=v[i-1])
				{
					printf("Yan Shuyi AK IOI!\n");
					return;
				}
			}
			
			if(!oppoud) oppoud=3;
		}
	}
}

int main()
{
	init();
	BFS();if(totfl) return 0;
	print();
	return 0;
}

```

---

