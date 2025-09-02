# Bouncy Ball

## 题目描述

You are given a room that can be represented by a $ n \times m $ grid. There is a ball at position $ (i_1, j_1) $ (the intersection of row $ i_1 $ and column $ j_1 $ ), and it starts going diagonally in one of the four directions:

- The ball is going down and right, denoted by $ \texttt{DR} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i+1, j+1) $ .
- The ball is going down and left, denoted by $ \texttt{DL} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i+1, j-1) $ .
- The ball is going up and right, denoted by $ \texttt{UR} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i-1, j+1) $ .
- The ball is going up and left, denoted by $ \texttt{UL} $ ; it means that after a step, the ball's location goes from $ (i, j) $ to $ (i-1, j-1) $ .

After each step, the ball maintains its direction unless it hits a wall (that is, the direction takes it out of the room's bounds in the next step). In this case, the ball's direction gets flipped along the axis of the wall; if the ball hits a corner, both directions get flipped. Any instance of this is called a bounce. The ball never stops moving.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1807F/b981cd1b02284413957fa53dbf389556ca82be95.png)In the above example, the ball starts at $ (1, 7) $ and goes $ \texttt{DL} $ until it reaches the bottom wall, then it bounces and continues in the direction $ \texttt{UL} $ . After reaching the left wall, the ball bounces and continues to go in the direction $ \texttt{UR} $ . When the ball reaches the upper wall, it bounces and continues in the direction $ \texttt{DR} $ . After reaching the bottom-right corner, it bounces once and continues in direction $ \texttt{UL} $ , and so on.

Your task is to find how many bounces the ball will go through until it reaches cell $ (i_2, j_2) $ in the room, or report that it never reaches cell $ (i_2, j_2) $ by printing $ -1 $ .

Note that the ball first goes in a cell and only after that bounces if it needs to.

## 样例 #1

### 输入

```
6
5 7 1 7 2 4 DL
5 7 1 7 3 2 DL
3 3 1 3 2 2 UR
2 4 2 1 2 2 DR
4 3 1 1 1 3 UL
6 4 1 2 3 4 DR```

### 输出

```
3
-1
1
-1
4
0```

# 题解

## 作者：Larryyu (赞：16)

[题目链接](https://www.luogu.com.cn/problem/CF1807F)
## _Description_
在一个 $n\times m$ 的房间内有一个球，初始位置为 $(i_1,j_1)$，目标位置为 $(i_2,j_2)$，初始方向为字符串 $d$。

- $d=\texttt{UL}$，向左上移动
- $d=\texttt{DR}$，向右下移动
- $d=\texttt{DL}$，向左下移动
- $d=\texttt{UR}$，向右上移动

当小球碰到墙壁后会反弹，新的方向与旧方向以垂直与墙壁的一条线为轴对称。（见图）

当小球移到角落时会原地返回。

若小球会移到目标位置，问最少会反弹几次（碰到角落为一次），若无法移到，则输出 ```-1```。
## _Solution_
由于一共有 $n\times m$ 个点，有四种移动方向，所以在移动最多 $4\times n\times m$ 步后，每个点都会移到至少一遍。

然后模拟即可。

具体步骤见代码。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void solve(){
	int n=read(),m=read(),sx=read(),sy=read(),ex=read(),ey=read();
	int dx,dy,x=sx,y=sy,cnt=0;
	string s;
	cin>>s;
	if(s[0]=='D') dx=1;
	else dx=-1;
	if(s[1]=='L') dy=-1;
	else dy=1;
	ll lim=n*m*4;
	while(lim--){
		if(x==ex&&y==ey){ //移到目标点
			cout<<cnt<<endl;
			return ;
		}
		bool is=0;
		if(dx==1&&x==n){ //碰到下侧墙壁
			dx=-1;
			is=1;
		}
		if(dx==-1&&x==1){ //碰到上侧墙壁
			dx=1;
			is=1;
		}
		if(dy==1&&y==m){ //碰到右侧墙壁
			dy=-1;
			is=1;
		}
		if(dy==-1&&y==1){ //碰到左侧墙壁
			dy=1;
			is=1;
		}
		//碰到角落时，因为碰到两面墙壁，x和y都会取反
		if(is) cnt++; //有反弹
		x+=dx,y+=dy; //移动
	}
	cout<<-1<<endl;
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```

---

