# World of Darkraft

## 题目描述

两个玩家在一个 $n$ 行 $m$ 列的网格上玩游戏，网格上的字母有 `L`、`R`、`X` 三种，一开始全部是白色的，两个玩家轮流操作，操作为选择一个白色的格子变成黑色，然后会根据格子上的字母触发一些效果：

- `L`：这个格子向左下和右上方向 直到另一个黑色的格子（或到边界） 路径上的所有格子都变成黑色的。
- `R`：效果与 `L` 相同，但方向是向左上和右下。
- `X`：效果相当于这个格子上同时有 `L` 和 `R`。

无法操作了的人输，问先手是必胜还是必败。

## 说明/提示

在第一个样例中，每操作一次都会使网格的一条对角线变为黑色，因此先手在总共操作两次后必败。

在第二个样例中，有三种不同的操作方式：操作主对角线或剩下的任意方格。这意味着在总共三次操作后，游戏结束，先手必胜。

## 样例 #1

### 输入

```
2 2
RL
LR
```

### 输出

```
LOSE
```

## 样例 #2

### 输入

```
2 2
RR
RR
```

### 输出

```
WIN
```

# 题解

## 作者：C20203030 (赞：4)

## 一、题目
[点此看题](https://www.luogu.com.cn/problem/CF138D)
## 二、解法
看到``n,m<=20``就能确定这是$sg$函数的题了吧，只不过我们要用一些奇技淫巧。

可以把原图翻转$45$度，这样右上左下就变成了横切，右下左下就变成了纵切，但这里我们不需要把新的图建出来，只需要表示出一个映射关系，具体方法为：对于点$(i,j)$，翻转后的坐标为$(i+j,i-j+m)$

设$sg[x_1][x_2][y_1][y_2]$，为新图上这个矩形的$sg$函数，转移就枚举选取的点，看它的功能（是``L,R,X``的哪一种），然后拆成若干个图，标记一下它们的异或和就可以了。

有一个小优化，就是可以对原图黑白染色，每次只考虑黑点或白点，因为黑点和白点的博弈是无关的，这样应该可以优化一下时间复杂度，本算法的上界是$O(40^4\times 20^2)$，但是怎么可能达得到呢？贴个代码$qwq$

```cpp
#include <cstdio>
#include <cstring>
const int M = 45;
int read()
{
    int x=0,flag=1;char c;
    while((c=getchar())<'0' || c>'9') if(c=='-') flag=-1;
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return x*flag;
}
int n,m,sg[M][M][M][M][2];char s[M][M];
int get(int x1,int x2,int y1,int y2,int f)
{
    if(x1>x2 || y1>y2) return 0;
    if(sg[x1][x2][y1][y2][f]!=-1) return sg[x1][x2][y1][y2][f];
    bool vis[205]={};
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(((i+j)&1)==f)
            {
                int x=i+j,y=i-j+m;
                if(x1<=x && x<=x2 && y1<=y && y<=y2)
                {
                    if(s[i][j]=='L') vis[get(x1,x-1,y1,y2,f)^get(x+1,x2,y1,y2,f)]=1;
                    if(s[i][j]=='R') vis[get(x1,x2,y1,y-1,f)^get(x1,x2,y+1,y2,f)]=1;
                    if(s[i][j]=='X')
                        vis[get(x1,x-1,y1,y-1,f)^get(x+1,x2,y1,y-1,f)^get(x1,x-1,y+1,y2,f)^get(x+1,x2,y+1,y2,f)]=1;
                }
            }
    for(int i=0;;i++)
        if(!vis[i])
            return sg[x1][x2][y1][y2][f]=i;
}
int main()
{
    memset(sg,-1,sizeof sg);
    n=read();m=read();
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    if(get(1,n+m,1,n+m,0)^get(1,n+m,1,n+m,1))
        puts("WIN");
    else
        puts("LOSE");
}

```



---

## 作者：chenzida (赞：1)

### 题意简述：
[（题目本来的的描述就够简单的了）](https://www.luogu.com.cn/problem/CF138D)

### 解析：

这道题先考虑算法，根据数据范围以及两人博弈的性质可以得出这道题是一道博弈论 $SG$ 的题。

对于这类题先考虑 $sg$ 数组表示的状态。可以看出这道题如果在这种状态下并不是十分好记录状态，因为它影响的是一个对角线，所以我们要把对角线变成横行纵列，所以我们将这个图进行旋转，使得原先的对角线变成横的行或者纵列。

那这样的话原先的 $a_{i,j}$ 就会变成 $a_{i+j,i-j+m}$。然后现在我们就能考虑状态了，那就是 $sg[x1][y1][x2][y2]$ 表示这个矩阵左上顶点是 $(x1,y1)$，右下顶点是 $(x2,y2)$，时的 $SG$ 值。

所以就有这些转移方程：

![](https://cdn.luogu.com.cn/upload/image_hosting/vv0hc72g.png)

这些转移方程的原因就是：

当 $a[i][j]=L$ 时，那么就在中间将这个矩阵断开，并将这两块的值取 $xor$ （这是最基本的 $SG$）

当 $a[i][j]=R$ 时跟上面的很像。

当 $a[i][j]=X$ 时就是把这个矩形断成4部分，其他的也同上。

所以有这个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=55;
int n,m;
int sg[NR][NR][NR][NR][2];
char a[NR][NR];
int mex(bool vis[])
{
	for(int i=0;~i;i++)
		if(!vis[i]) return i;
	return 0;
}
int get_sg(int x1,int y1,int x2,int y2,bool flag)
{
    if(x1>x2||y1>y2) return 0;
    if(sg[x1][y1][x2][y2][flag]!=-1) return sg[x1][y1][x2][y2][flag];
    bool vis[210];
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
        {
            int x=i+j,y=i-j+m;
            if(!((i+j&1)-flag)||x<x1||x>x2||y<y1||y>y2) continue;
            if(a[i][j]=='L')
            {
            	int a=get_sg(x+1,y1,x2,y2,flag)^get_sg(x1,y1,x-1,y2,flag);
            	vis[a]=1;
			}
            else if(a[i][j]=='R')
            {
            	int a=get_sg(x1,y+1,x2,y2,flag)^get_sg(x1,y1,x2,y-1,flag);
            	vis[a]=1;
			}
            else
            {
            	int a=get_sg(x+1,y+1,x2,y2,flag)^get_sg(x1,y1,x-1,y-1,flag);
            	int b=get_sg(x+1,y1,x2,y-1,flag)^get_sg(x1,y+1,x-1,y2,flag);
            	vis[a^b]=1;
			}
        }
	}
    return sg[x1][y1][x2][y2][flag]=mex(vis);
}
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch<='9'&&ch>='0'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int main()
{
    memset(sg,-1,sizeof(sg));
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=m;j++)
    	{
    		scanf(" %c",&a[i][j]);
		}
	}
	int x=get_sg(1,1,n+m,n+m,0)^get_sg(1,1,n+m,n+m,1);
	if(x) puts("WIN");
	else puts("LOSE");
    return 0;
}
```


---

