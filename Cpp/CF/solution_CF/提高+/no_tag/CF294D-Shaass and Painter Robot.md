# Shaass and Painter Robot

## 题目描述

Shaass thinks a kitchen with all white floor tiles is so boring. His kitchen floor is made of $ n·m $ square tiles forming a $ n×m $ rectangle. Therefore he's decided to color some of the tiles in black so that the floor looks like a checkerboard, which is no two side-adjacent tiles should have the same color.

Shaass wants to use a painter robot to color the tiles. In the beginning the robot is standing in a border tile $ (x_{s},y_{s}) $ facing a diagonal direction (i.e. upper-left, upper-right, down-left or down-right). As the robot walks in the kitchen he paints every tile he passes even if it's painted before. Painting each tile consumes one unit of black paint. If at any moment the robot hits a wall of the kitchen he changes his direction according the reflection rules. Note that a tile gets painted when the robot enters the tile from another tile, in other words changing direction in the same tile doesn't lead to any painting. The first tile the robot is standing on, is also painted.

The robot stops painting the first moment the floor is checkered. Given the dimensions of the kitchen and the position of the robot, find out the amount of paint the robot consumes before it stops painting the floor.

Let's consider an examples depicted below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF294D/9a76f461f123d79b09ad121ee5e2505584689476.png)If the robot starts at tile number 1 (the tile $ (1,1) $ ) of the left grid heading to down-right it'll pass tiles 1354236 and consumes 7 units of black paint on his way until he stops at tile number 6. But if it starts at tile number 1 in the right grid heading to down-right it will get stuck in a loop painting tiles 1, 2, and 3.

## 样例 #1

### 输入

```
3 4
1 1 DR
```

### 输出

```
7
```

## 样例 #2

### 输入

```
3 4
3 3 DR
```

### 输出

```
11
```

## 样例 #3

### 输入

```
3 3
1 1 DR
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
3 3
1 2 DL
```

### 输出

```
4
```

# 题解

## 作者：skyskyCCC (赞：1)

## 前言。
先澄清一下，光的反射指的是面朝某个斜 $45$ 度的方向进行返回弹射操作。这道题就是一个妥妥的思维题和模拟题。
## 分析。
首先在最开始我们提出一个结论：当且仅当整张网格已按要求染成黑白相间，边缘上所有该染黑的格子才被都染黑。

这里给出可能是比较正确的证法：归纳。假设第一行应该染黑的格子都已经染黑，那么就会得到第二行该染黑的格子都已染黑。原因如下：第一行某个染黑的格子必定从它的斜边进去然后反射出来，即这个第一行的黑格子的左下和右下的两格都染黑了，不管是从右下还是左下进去这个格子。当然对于角上的情况要特殊考虑要原路返回。同时对于第一行该染黑的所有格子的最后一个格子的情况要特别考虑。因为这时由于它两旁相间的格子都已染黑，所以左下和右下的两格必定也染黑，所以可以概括为“只进不出”。这样我们每一行就可以证明出来，所以可证。

那么这个问题就转换成了模拟这个网格的边缘染色情况。我们让这个数组储存所有已经过（染色）的边缘的格子，然后模拟机器人的行走，最后看看有没有解即可。这个有没有解就是看它是不是进入了死循环或者超出一些限制。那么我们就要考虑可能有几个边缘的格子被染成黑色。我们画一张图：

考虑对 $n$ 和 $m$ 的奇偶性讨论，假设机器人从 $\left(1,1\right)$ 开始，向右下方前进，如下：
- 如果 $n$ 奇 $m$ 偶的话：  
举出一个例子：  
![](https://cdn.luogu.com.cn/upload/image_hosting/s4y9670u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
此时边缘的黑格子有 $3$ 个。如果画更多的网格，我们就不妨将那些都看做这个的叠加。
- 如果 $n$ 偶 $m$ 奇的话：  
再举出一个例子：  
![](https://cdn.luogu.com.cn/upload/image_hosting/ynt1jmgn.png?x-oss-process=image/resize,m_lfit,h_170,w_225)  
显然有 $5$ 个黑格子在边缘上。那么我们也可以去掉一个 $m$ 使得去掉一列，但是仍然有 $4$ 个在边缘上，而这个去掉一列的图形就可以看做更复杂的网格的叠加的基本图形。

- 都是偶或者都是奇：  
显然走的就是对角线，所以特殊考虑一下即可。

总而言之，上述的三个情况所组成的网格我们都可以看做是一个基本的最简单的图形经过平移、重叠后得到的，除了进行严谨的证明，也可以通过举例子或者看“叠加态”得出一个结论：边缘上该染黑的格子永远有 $n+m-2$ 个。

代码如下，仅供参考：
```
#include<iostream>
#include<map>
#include<algorithm>
#include<cmath>
using namespace std;
long long n,m,x,y;
char s[5];
map<int,int> ma[100005];
long long dx,dy;
long long sum,cishu,ans=1,way=0x3f3f3f3f;
int main(){
	cin>>n>>m>>x>>y>>s+1;
	sum=n+m-2;
	(s[1]=='U')?dx=-1:dx=1;
	(s[2]=='L')?dy=-1:dy=1;
	if(x==1||x==n||y==1||y==m){
		ma[x][y]=1;
		sum--;
	}
	while(true){
		cishu++;
		way=0x3f3f3f3f;
		if(cishu>=500000){
			cout<<"-1\n";
			return 0;
		}
		if(dx==1){
		    way=min(way,n-x);
		}
		else{
		    way=min(way,x-1);
		}
		if(dy==1){
		    way=min(way,m-y);
		}
		else{
		    way=min(way,y-1);
		}
		x+=dx*way;
		y+=dy*way;
		ans+=way;
		if(x==1){
		    dx=x;
		}
		else if(x==n){
		    dx=-1;
		}
		if(y==1){
		    dy=y;
		}
		else if(y==m){
		    dy=-1;
		}
		if(ma[x][y]==0){
			ma[x][y]=1;
			sum--;
		}
		if(!sum){
			cout<<ans<<"\n";
			return 0;
		}
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：_Felix (赞：1)

### 题意简述

给厨房的n行m列瓷砖上色。初始时在$(X_s,Y_s)$上。$Shaass$希望厨房瓷砖最后像棋盘一样黑白相间。即：没有两块相邻瓷砖颜色相同。

机器人有"UL"左上，"UR"右上，"DL"左下，"DR"右下四种移动方式，
当它撞墙时会遵循【光的反射】原则反弹。

每当机器人移动到一块瓷砖上，它就给这块瓷砖上色（所以可能重复多次上色）

输出机器人的步数，当机器人不能完成任务，输出-1.

### 分析

很有趣的题目 ~~由此推出我不会做~~

显然，对于第二行，如果第一行已经黑白间隔地填好，则第二行一定已经填好。原因是穿进穿出时，第一行的黑格的左下格和右下格已经涂黑。

由此推出，如果边界全部黑白相间的填好，则一定已经填完。

那么要涂多少边界呢？

~~举几个例子~~ 按照奇偶性分类看一下，是 $n+m-2$

接着，我们只需要暴力计算每次到边缘格的时候在那块瓷砖就行了。

这个不用多说。~~快 乐 的 思 维 题~~

### code

```
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define rd(x) scanf("%d",&x);
typedef long long LL;
int n,m,x,y,cnt;
long long ans;
string str;
map<pair<int,int>,int>vis;
int main(){
	rd(n);rd(m);rd(x);rd(y);
	cin>>str;
	int dx,dy;
	(str[0]=='U')?dx=-1:dx=1;
	(str[1]=='L')?dy=-1:dy=1;
	cnt=0;int tim=0;
	if(x==1||x==n||y==1||y==m) cnt++,vis[make_pair(x,y)]=1;
	while(cnt!=n+m-2){
		if(++tim>=500000)  {puts("-1");return 0;}
		int tx,ty;
		if(dx==1) tx=abs(n-x);else tx=abs(1-x);
		if(dy==1) ty=abs(m-y);else ty=abs(1-y);
		int tmp=min(tx,ty);
		x+=dx*tmp;y+=dy*tmp;ans+=tmp;
		if(x==1) dx=1;if(x==n) dx=-1;
		if(y==1) dy=1;if(y==m) dy=-1;
		if(!vis[make_pair(x,y)]) cnt++,vis[make_pair(x,y)]=1;
	}
	cout<<ans+1<<endl;
	return 0;
}
```

### 注意点

1.本题那个边缘那个好难想到qaq

2.不可以边界重复走就输出-1！会过不去样例的！

3.当心int溢出

---

## 作者：liujiaxi123456 (赞：0)

## 关键词：模拟，思维。
### 思路：
观察性质：当一条边界填好，则这条边界隔一的那一行/列必然已经填好，因为为了斜着填边界必然会把隔的那一行/列填好。

所以，我们只需要填好边界即可。
### 实现：
从当前点一直跳到边界，把答案加上这一次的步数，并标记这个边界，当所有边界都被标记后，就算跳完了。

因为显然一共有 $N+M-2$ 个边界，所以当模拟 $500000$ 以上时，就一定无解了。
### Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int Maxn = 1e5+5;

namespace Josh_zmf {
	
	int N, M, x, y, dx, dy; string opt;
	map <int, bool> vis[Maxn];

	inline int main() {
		cin>> N>> M>> x>> y>> opt;
		dx = (opt[0] == 'U' ?-1 :1);
		dy = (opt[1] == 'L' ?-1 :1);
		int cnt = 0;
		if(x==1 || y==1 || x==N || y==M)	cnt++, vis[x][y] = 1;
		ll ans = 1;
		for(int tim=1; cnt!=(N+M-2); tim++) {
			if(tim >= 500000)	return cout<< "-1", 0;
			int xx = (dx==1 ?N-x :x-1), yy = (dy==1 ?M-y :y-1);
			int tmp = min(xx, yy);
			x += dx*tmp, y += dy*tmp, ans += tmp;
			if(x == 1)	dx = 1; 
			if(x == N)	dx = -1;
			if(y == 1)	dy = 1; 
			if(y == M)	dy = -1;
			if(!vis[x][y])	cnt++, vis[x][y] = 1;
		} 
		cout<< ans;
		return 0;
	}

}

int main() {
	Josh_zmf::main();
	return 0;
}
```
### 结语：
都看到这里了，点个赞再走吧。: )

---

