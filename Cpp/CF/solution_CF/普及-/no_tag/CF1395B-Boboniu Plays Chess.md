# Boboniu Plays Chess

## 题目描述

Boboniu likes playing chess with his employees. As we know, no employee can beat the boss in the chess game, so Boboniu has never lost in any round.

You are a new applicant for his company. Boboniu will test you with the following chess question:

Consider a $ n\times m $ grid (rows are numbered from $ 1 $ to $ n $ , and columns are numbered from $ 1 $ to $ m $ ). You have a chess piece, and it stands at some cell $ (S_x,S_y) $ which is not on the border (i.e. $ 2 \le S_x \le n-1 $ and $ 2       \le S_y \le m-1 $ ).

From the cell $ (x,y) $ , you can move your chess piece to $ (x,y') $ ( $ 1\le y'\le m, y' \neq y $ ) or $ (x',y) $ ( $ 1\le x'\le n, x'\neq x $ ). In other words, the chess piece moves as a rook. From the cell, you can move to any cell on the same row or column.

Your goal is to visit each cell exactly once. Can you find a solution?

Note that cells on the path between two adjacent cells in your route are not counted as visited, and it is not required to return to the starting point.

## 说明/提示

Possible routes for two examples:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1395B/c064004f0504fcb32a549da42e8ef5b0adb837cd.png)

## 样例 #1

### 输入

```
3 3 2 2```

### 输出

```
2 2
1 2
1 3
2 3
3 3
3 2
3 1
2 1
1 1```

## 样例 #2

### 输入

```
3 4 2 2```

### 输出

```
2 2
2 1
2 3
2 4
1 4
3 4
3 3
3 2
3 1
1 1
1 2
1 3```

# 题解

## 作者：—维尼— (赞：3)

## 题目描述
给定一个棋盘，和象棋的初始位置，问如何遍历整个棋盘（输出一种情况

## 求解方法
这题比第一题还简单（~~简单多了~~ ）

虽然题面不短，但仔细读就会发现条件不多

刚开始我误以为是一笔画的题，但题中的棋子不同，~~他是車~~ 

棋子可以直接跳过一个点，也就是上下左右随便走，那就简单了，遍历一遍从左往右，再从右往左就行啦，

注意奇数行从左往右走，偶数行从右到左

还有初始点读入的位置就不用再走了

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101][101];
int main(){
	int n,m;
	cin>>n>>m;
	int x1,y1;
	cin>>x1>>y1;
	for(int i=1;i<=n;i++)
	{
		if(i%2){
			for(int j=1;j<=m;j++)
			cout<<(i+x1-2)%n+1<<" "<<(j+y1-2)%m+1<<endl;
		}
		else{
			for(int j=m;j>=1;j--){
				cout<<(i+x1-2)%n+1<<" "<<(j+y1-2)%m+1<<endl;
				}
			}	
	}
	return 0; 
}
```



---

## 作者：_YyD_ (赞：2)

**题意：**

一张 $N \times M$ 的地图，你现在在 $(X,Y)$，你要给出一种走遍全图的方案。

**做法：**

DFS！

你只需要 dfs 向 $4$ 个方向去走，走过就标记掉，每次继续深搜前输出现在所在的 $X,Y$ 就好了。

**Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
bool mp[110][110];
int n,m;
void DFS(int x,int y){//x,y表示现在的位置
cout<<x<<" "<<y<<endl;//输出现在的位置
	mp[x][y]=true;//mp代表有没有走过现在来到了这里，就标记掉
	for(int i=1;i<=n;i++)//循环枚举横向移动，因为是车，所以1~n都可以到
		if(!mp[i][y])//判断位置是否没有越界并且没来过（这里不用考虑是否越界，因为每次的枚举都是合法的
        DFS(i,y);//现在的位置继续dfs
	for(int i=1;i<=m;i++)//同样的道理枚举竖着的位置
		if(!mp[x][i])//判断是否合法
        DFS(x,i);//继续dfs
}
int main(){
	int x,y;
	cin>>n>>m>>x>>y;
	DFS(x,y);
	return 0;
}
```


---

## 作者：⚡小林子⚡ (赞：2)

~~第一次打 CF 就遇到了这么水的 B 题，运气好啊~~

------------

[题目传送门](https://www.luogu.com.cn/problem/CF1395B)

这题实在是一道比 A 还水的题（只要你题目大意看得懂）

题意简述：

- 有一颗棋子在 $n\times m$ 的矩阵内，起始坐标为 $(S_x,S_y)$。

- 每次棋子能移动到同一行或同一列仍未访问过的位置。

- 请你输出一种可能的移动顺序。

具体输入输出格式可以参照样例，这里就不细说了。

这题有 Special Judge，所以任意输出一种顺序就行了。

然后...这题就是一道大水题了啊！

打一个暴搜模板（注意移动时是同一行和列），加上 vis 和边界的判断，结 束 了 ！

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy;
bool vis[101][101];
inline bool judge(int x,int y){  //边界和 vis 的判断
	return x>=1&&x<=n&&y>=1&&y<=m&&!vis[x][y];
}
void dfs(int x,int y){
	vis[x][y]=1;  //标记已访问
	printf("%d %d\n",x,y);  //输出当前坐标
	for(int i=1;i<=n;i++)  //下一步移动的位置
		if(judge(i,y)) dfs(i,y);
	for(int i=1;i<=m;i++)
		if(judge(x,i)) dfs(x,i);
}
int main(){
	cin>>n>>m>>sx>>sy;
	dfs(sx,sy);
	return 0;
}
```

[AC！](https://www.luogu.com.cn/record/36948553)

------------

这一轮的 A 和 B 可能顺序颠倒了吧（A 至少还有一点思维，但是 B 就是一个无脑题），也没啥好说的了。

# $\sf{The\,End.}$

---

## 作者：luosw (赞：0)

因为不能重复，考虑如下构造：

设 $(a,b)$ 是首先染色的点。将 $(1,b),\cdots,(a,b)$ 全部染色，然后将 $(1,b-1),\cdots,(1,1)$ 全部染色，然后蛇形从第一行染色到第 $n$ 行。

这就是一种构造。代码略。

---

## 作者：Ryo_Yamada (赞：0)

这题看到神仙们都是用 S型走位 或者其它规律走法做的，来一发爆搜题解。

这题简直比 A 简单不少。

考场上看懂题目之后一看数据范围， $n, m \leq 100$ ，这不是直接爆搜就可以了吗？于是直接写了一发 dfs。

直接上 $\text{Code}$：

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

int n, m, x, y, k;
bool vis[105][105];
int xi[10005], yi[10005];//记录路线

void print() {
	for(int i = 1; i <= k; i++) {
		printf("%d %d\n", xi[i], yi[i]);
	}	
}

void dfs(int a, int b, int st) {
	if(st > k) {
		print();
		exit(0);//这里直接exit(0)退出程序
	}
	for(int i = 1; i <= n; i++) {
		if(!vis[i][b]) {
			vis[i][b] = true;
			xi[st] = i, yi[st] = b;
			dfs(i, b, st + 1);
			vis[i][b] = false;
		}
	}//在这一列走
	for(int i = 1; i <= m; i++) {
		if(!vis[a][i]) {
			vis[a][i] = true;
			xi[st] = a, yi[st] = i;
			dfs(a, i, st + 1);
			vis[a][i] = false;
		}
	}//在这一行走
}

int main() {
	cin >> n >> m >> x >> y;
	k = n * m;
	vis[x][y] = true;
	xi[1] = x, yi[1] = y; 
	dfs(x, y, 2);
	return 0;
}
```


---

## 作者：Demoe (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1395B)

## 题意

- 给定一个方格图的长宽及所在初始点位置。

- 每次你可以到你当前所在位置同行或列的任意位置。

- 输出一种方案遍历全图，并使得每个位置只到达一次。

## Sol

~~CF 前 $50$ 个 $A$ 的，祭之。~~

我们有一个很简单的想法，每一行先走完再换行。

这样就可以了。

你可以蛇形走位。（（（

像这么写。

```cpp
/*
***
还要继续努力
成为一名烤咕学家哦
***
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,a,b,cnt;
template <typename T> void rd(T &x){
	ll fl=1;x=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') fl=-fl;
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	x*=fl;
}
void wr(ll x){
	if(x<0) x=-x,putchar('-');
	if(x<10) putchar(x+'0');
	if(x>9) wr(x/10),putchar(x%10+'0');
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	rd(n);rd(m);rd(a);rd(b);
	wr(a);putchar(' ');wr(b);puts("");
	for(ll i=1;i<=m;i++)
		if(i!=b) wr(a),putchar(' '),wr(i),puts("");
	for(ll i=1;i<=n;i++)
		if(i!=a){
			cnt++;
			if(cnt&1){
				for(ll j=m;j>0;j--) wr(i),putchar(' '),wr(j),puts("");
			}
			else{
				for(ll j=1;j<=m;j++) wr(i),putchar(' '),wr(j),puts("");
			}
		}
	return 0;
}
```

但数据比较弱，我写的其实可以 Hack 掉。（

比如这组数据

```
3 3 2 3
```

这种写法需要特判掉初始位置在最右边的情况。

可以通过改变 $cnt$ 来操作。

代码修改留给读者自写。

---

## 作者：引领天下 (赞：0)

考虑构造。

首先可以先把 $sx$ 行处理掉。

然后对于 $sx$ 下面的行，可以考虑这样跑：$1->2->3->...->m->$ 下一行 $->m-1->...->1$ ，即：**蛇形走位**。

上面同理。

```cpp
#include <bits/stdc++.h>
using namespace std;
bool last;
int main(){
    register int n,m,sx,sy;
    scanf("%d%d%d%d",&n,&m,&sx,&sy);
    printf("%d %d\n",sx,sy);
    for(register int i=sx;i<=n;i++)if(!last){
        for(register int j=1;j<=m;j++)if(i!=sx||j!=sy)printf("%d %d\n",i,j),last=1;
    }else for(register int j=m;j>=1;j--)if(i!=sx||j!=sy)printf("%d %d\n",i,j),last=0;
    for(int i=1;i<sx;i++){
        if(!last)for(register int j=1;j<=m;j++)printf("%d %d\n",i,j),last=1;else for(register int j=m;j>=1;j--)printf("%d %d\n",i,j),last=0;
    }
    return 0;
}
```

---

## 作者：KSToki (赞：0)

这道题甚至比 A 题还水。基本策略是先把第 $x$ 行走完，然后再依次走 $1$ 到 $n$ 行（除第 $x$ 行）即可。用一个变量记录当前该从最左端走还是从最右端走即可。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>x>>y;
	cout<<x<<" "<<y<<endl;
	for(register int i=1;i<=m;++i)
	    if(i!=y)
	        cout<<x<<" "<<i<<endl;
	int op=1;
	for(register int i=1;i<x;++i,op^=1)
	{
		if(op)
		    for(register int j=m;j>0;--j)
		        cout<<i<<" "<<j<<endl;
		else
		    for(register int j=1;j<=m;++j)
		        cout<<i<<" "<<j<<endl;
	}
	for(register int i=x+1;i<=n;++i,op^=1)
	{
		if(op)
		    for(register int j=m;j>0;--j)
		        cout<<i<<" "<<j<<endl;
		else
		    for(register int j=1;j<=m;++j)
		        cout<<i<<" "<<j<<endl;
	}
	return 0;
}
```


---

## 作者：猪龙骨丶丶 (赞：0)

**题意**

**1**题意为给一个n*m的矩阵，以及xi，yi为起点，要求从起点出发，找到一条路径可以将整个矩阵走完一遍，且不能重复走一个点。

**2**运动时可以走到同一行或同一列的任何一个点，与象棋中车的走法类似。且一次跳跃出发点到到达点之间的点不算被访问。

**3**最后不需要回到起点

**思路**

边走边输出到达点
从出发点开始先将出发点左端所有点依次输出，再跳到右端依次输出。
再分别遍历xi行上方矩阵和下方矩阵。用s型路线即可.上端s型走完跳至下端走s型，即可无重复走完该矩形!

![](https://cdn.luogu.com.cn/upload/image_hosting/yhbnkusx.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

s型遍历时，起点行为x，abs(x-xi)为奇数行起点为m，偶数行起点为1。

**S型路线走法代码**
****
//TMP记录为abs(x-xi)奇偶

```
int tmp=1;
for(int i=x-1;i>=1;i--)
	{
		if(tmp==1)
		{
			for(int j=m;j>=1;j--)
			printf("%d% d\n",i,j);
		}
		else
		{
			for(int j=1;j<=m;j++)
			printf("%d% d\n",i,j);
		}
		tmp+=1;	tmp%=2;
	}
    
	for(int i=x+1;i<=n;i++)
	{
		if(tmp==1)
		for(int j=m;j>=1;j--)
		printf("%d% d\n",i,j);
		else
		for(int j=1;j<=m;j++)
		printf("%d% d\n",i,j);
		tmp+=1;
		tmp%=2;
	}

```


---

