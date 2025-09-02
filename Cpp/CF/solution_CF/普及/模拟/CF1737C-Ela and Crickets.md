# Ela and Crickets

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/f0f8b416d84260abf4a5738763b563a4a29739c9.png)Ela likes Chess a lot. During breaks, she usually challenges her co-worker in DTL to some chess games. She's not an expert at classic chess, but she's very interested in Chess variants, where she has to adapt to new rules and test her tactical mindset to win the game.The problem, which involves a non-standard chess pieces type that is described below, reads: given $ 3 $ white crickets on a $ n \cdot n $ board, arranged in an "L" shape next to each other, there are no other pieces on the board. Ela wants to know with a finite number of moves, can she put any white cricket on the square on row $ x $ , column $ y $ ?

An "L"-shape piece arrangement can only be one of the below:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/514135a9cb3021fdd11c6f5877903e61238e21da.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/e135bddf869fc3c4e5900f14eaae8062e1263b64.png) ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/b79b64cfe0ed70ae5dd5a6ed54ba57554fdeec32.png)![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/07b44b1ac7a379c6fed131cb7e0805a4ed084742.png)For simplicity, we describe the rules for crickets on the board where only three white crickets are. It can move horizontally, vertically, or diagonally, but only to a square in some direction that is immediately after another cricket piece (so that it must jump over it). If the square immediately behind the piece is unoccupied, the cricket will occupy the square. Otherwise (when the square is occupied by another cricket, or does not exist), the cricket isn't allowed to make such a move.

See an example of valid crickets' moves on the pictures in the Note section.

## 说明/提示

Here's the solution for the first test case. The red square denotes where the crickets need to reach. Note that in chess horizontals are counted from bottom to top, as well as on this picture.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/5d188af801d8843cba510dd4aca2e2621bb3a163.png)

## 样例 #1

### 输入

```
6
8
7 2 8 2 7 1
5 1
8
2 2 1 2 2 1
5 5
8
2 2 1 2 2 1
6 6
8
1 1 1 2 2 1
5 5
8
2 2 1 2 2 1
8 8
8
8 8 8 7 7 8
4 8```

### 输出

```
YES
NO
YES
NO
YES
YES```

# 题解

## 作者：Binary_Lee (赞：10)

## [题面传送门](https://www.luogu.com.cn/problem/CF1737C)

### 题目翻译

给定一个 $n\times n$ 的棋盘，棋盘上有且仅有三颗排成 $\text{L}$ 形的棋子。

对于 $\text{L}$ 形的定义，有且仅有以下四种情况：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/514135a9cb3021fdd11c6f5877903e61238e21da.png)，
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/e135bddf869fc3c4e5900f14eaae8062e1263b64.png)，
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/b79b64cfe0ed70ae5dd5a6ed54ba57554fdeec32.png)，
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1737C/07b44b1ac7a379c6fed131cb7e0805a4ed084742.png)

棋子的移动规则和跳棋相同。它可以水平、垂直或斜向移动。当且仅当一个棋子的某个方向紧随另一个棋子时，它能跳到另一个棋子之后的一个方格上。棋子不能跳出棋盘。详见样例解释。

现在有 $T$ 组询问，每组给出棋盘大小 $n(n\le 10^5)$，三颗棋子各自的位置 $r_1,c_1,r_2,c_2,r_3,c_3(1\le r_1,c_1,r_2,c_2,r_3,c_3 \le n)$，以及目标点 $x,y(1 \le x,y \le n)$，询问是否能使其中的一颗棋子跳到目标点。输出 `YES` 或 `NO`。

### 解决思路

当没有什么思路的时候可以先模拟一下棋子的跳跃过程。

![](https://cdn.luogu.com.cn/upload/image_hosting/yxp81j47.png)

例如上图粉色的 $\text{L}$ 形，经过一次跳跃，其折点可以跳到 $1,2$ 处，非折点可以跳到 $3,4,5,6$。

我们进行分类讨论：

1. 跳折点（$1,2$）

![](https://cdn.luogu.com.cn/upload/image_hosting/2nenn96u.png)

此后原先折点可以和另一点在一列上不断跳，原先两个非折点可以不断斜向跳，但图中如果左下的跳到右上则又变成了 $\text{L}$ 形，原先折点还是折点。

同时发现，可以跳到的任意点，其横纵坐标，一定有一个和原先折点奇偶性相同。就算重新变 $\text{L}$ 形，新折点的横纵坐标一定有一个和原先折点奇偶性相同，所以结论仍成立。

2. 斜跳非折点（$3,4$）

![](https://cdn.luogu.com.cn/upload/image_hosting/4x8oujf3.png)

发现就是情况 $1$ 镜像翻转了一下。

3. 直跳非折点（$5,6$）

![](https://cdn.luogu.com.cn/upload/image_hosting/wcf57k2e.png)

发现又变成了 $\text{L}$ 形（情况 $1$ 已讲）。

由此，可以得出，若目标横纵坐标有一个和原先折点奇偶性相同，则可以到达。

然而发现样例都过不了。

考虑后可以发现有特殊情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/g9drvndy.png)

当原先折点在棋盘角落时，只能到达两条边上的点（因为跳不出去）。

所以特判一下就好。

至于如何判断那个是折点，输入每一个 $x,y$ 后排序，$x_2,y_2$ 就是 。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
int T,n,x[4],y[4],tx,ty;
bool check(){
	bool _1=0,_2=0;
	if((x[2]==1||x[2]==n)&&tx!=x[2]) _1=1;
	if((y[2]==1||y[2]==n)&&ty!=y[2]) _2=1;
	if(_1&&_2) return 0;
	if(((x[2]+tx)&1)&&((y[2]+ty)&1)) return 0;
	return 1;
}
void solve(){
	cin>>n;
	for(int i=1;i<=3;i++) cin>>x[i]>>y[i];
	cin>>tx>>ty;
	sort(x+1,x+4),sort(y+1,y+4);
	if(check()) cout<<"YES"<<endl;
	else cout<<"NO"<<endl; 
} 
signed main(){
	IOS;TIE;
	cin>>T;
	while(T--) solve();
	return 0;
}
```




---

## 作者：Withershine (赞：6)

原先大佬的题解写的很好，但这里想讲一下不同做法。

## 思路
题目中说的 $L$ 型有四种情况，很容易就可以想到特殊情况，那就是 $L$ 型恰好贴在棋盘的四个角上，这时我们发现，这样子棋子只能在棋盘的其中两条边上移动。对于四个角我们进行四次特判。

看普通情况，在手动模拟完样例后发现，棋盘上到不了的点是有一定的规律，换个想法理解，棋盘上能够到达的所有点都可看做是原 $L$ 型的三个点沿着 $r$ 或 $c$ 平移 $2k$ 个单位长度，其中 $k$ 为整数。这个时候我们不用理会部分出界的情况，只要有一部分仍在棋盘内，原来的 $L$ 型就可以移动到那里。

看回 $L$ 型，把它补成一个 $2 \times 2$ 的正方形，再结合上面的话，就会发现，那些永远达不到的点，就是那个被补上去的点。这时只要看目标点是否在这些点之间就行了。

## 代码实现
思路好想，但是代码还是有很多小细节。

首先是对最开始三个棋子位置的记录及特判，如果一个一个判断，将要花费巨大的时间与精力。所以最好的方法是运用数组。

一开始我想开一个 $10^5 \times 10^5$ 的二维数组，但感觉会空超，于是就变成了这样：
```cpp
struct edge
{
    bitset<100005> r;
}c[100005];
```
可实际上，该超还是超，直到我看见了这样的一个东西：`map`。我只需要记录四个角是否有对应的棋子，并不需要知道具体是哪个棋子，`map` 正好满足我的需要。只要在用完后将用的位置清零就解决了。

其次是如何判断目标点是否在 $L$ 型永远到不了的点上。直接分四种情况讨论太复杂了，所以需要找到一点规律。设三个棋子分别为 $chess_1$，$chess_2$，$chess_3$，$L$ 型的拐角点为 $chess_2$。发现，其中一个到不了的点一定在 $L$ 型拐角点左下角 $(r_2 - 1,c_2 - 1)$ 的位置上。那么如何表示出这个点呢？

### 结论
设这个点的位置为 $(r_a,c_a)$，则满足 $r_a=r_1+r_2+r_3-2 \times \max(r_1,r_2,r_3)$，$c_a=c_c+c_2+c_3-2 \times \max(c_1,c_2,c_3)$。

### 证明
这两个结论的证明类似，所以这里给出 $r_a$ 的证明过程。

设 $r_x=\max(r_1,r_2,r_3)$，$r_n=\min(r_1,r_2,r_3)$。由于 $L$ 型是三个相连的棋子，所以满足 $r_x-r_n=1$。对于四种 $L$ 型可以进行归类。

#### 两个棋子在上，一个棋子在下
包括

| $chess_1$ | $chess_2$ |
| :----------: | :----------: |
|  | $chess_3$ |

以及

| $chess_2$ | $chess_1$ |
| :----------: | :----------: |
| $chess_3$ |  |

两种情况。

此时可以发现 $r_1=r_2=r_x$，$r_3=r_n$。而 $r_a=r_x-1$。
我们对 $r_a=r_x-1$ 进行变形。

$r_a=r_x-1$，

将 $1$ 用 $r_x-r_n$ 代替，

$r_a=r_x-(r_x-r_n)$，

去括号，

$r_a=r_x-r_x+r_n$，

在后面加上 $r_x$ 然后再减去，这一步其实非常玄乎，一开始我并没有想到这么写，直到将另外一种情况讨论完后才悟到可以这么写，可以看做纯数字做法。

$r_a=r_x-r_x+r_n+r_x-r_x$，

移项，部分合并，

$r_a=r_x+r_x+r_n-2 \times r_x$，

而前面已知 $r_1=r_2=r_x$，$r_3=r_n$，$r_x=\max(r_1,r_2,r_3)$，所以 $r_a=r_1+r_2+r_3-2 \times \max(r_1,r_2,r_3)$。

#### 两个棋子在下，一个棋子在上
包括

| $chess_1$ |  |
| :----------: | :----------: |
| $chess_2$ | $chess_3$ |

以及

|  | $chess_1$ |
| :----------: | :----------: |
| $chess_3$ | $chess_2$ |

两种情况。

此时可以发现 $r_1=r_x$，$r_2=r_3=r_n$。而 $r_a=r_x-2$。
我们对 $r_a=r_x-2$ 进行变形。

$r_a=r_x-2$，

将 $2$ 用 $r_x-r_n$ 代替，

$r_a=r_x-2 \times (r_x-r_n)$，

去括号，

$r_a=r_x-2 \times r_x+2\times r_n$，

拆项，

$r_a=r_x-r_x-r_x+r_n+r_n$，

移项，部分合并，

$r_a=r_x+r_n+r_n-2 \times r_x$，

而前面已知 $r_1=r_x$，$r_2=r_3=r_n$，$r_x=\max(r_1,r_2,r_3)$，所以 $r_a=r_1+r_2+r_3-2 \times \max(r_1,r_2,r_3)$。

------------
化简完后发现四种情况的 $r_a$ 都可以用同一个式子表示出来。

那又该如何判断题目给出的目标点是否在不可到达的点上呢？

由于不可到达的点也是由 $(r_a,c_a)$ 沿着 $r$ 或 $c$ 移动 $2k$ 个单位得到的，其中 $k$ 为整数，所以只需要像下面的代码一样判断是否横纵坐标之和或差是否是二的倍数就好了。
```cpp
			ll mid_r = p1.r + p2.r + p3.r - 2 * max(p1.r , max(p2.r , p3.r));
            ll mid_c = p1.c + p2.c + p3.c - 2 * max(p1.c , max(p2.c , p3.c));
            if((mid_r + target.r) % 2 == 0 && (mid_c + target.c) % 2 == 0)
            {
                printf("NO\n");
                continue;
            }
            else
            {
                printf("YES\n");
                continue;
            }
```
其中 `mid_r` 便是刚才的 $r_a$，`mid_c` 就是 $c_a$。$target$ 是用结构体定义的，表示目标点及其横纵坐标。

## 代码
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define ld double
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll t , n;
struct node
{
    ll r , c;
}p1 , p2 , p3 , target;
signed main()
{
    t = read();
    while(t--)
    {
        map<pair<ll , ll> , ll> cr;
        n = read();
        cr[{p1.c , p1.r}] = 0;
        cr[{p2.c , p2.r}] = 0;
        cr[{p3.c , p3.r}] = 0;
        p1.r = read();
        p1.c = read();
        cr[{p1.c , p1.r}] = 1;
        p2.r = read();
        p2.c = read();
        cr[{p2.c , p2.r}] = 1;
        p3.r = read();
        p3.c = read();
        cr[{p3.c , p3.r}] = 1;
        target.r = read();
        target.c = read();
        if(cr[{1 , 1}] && cr[{1 , 2}] && cr[{2 , 1}])//左下角特判
        {
            if(target.c == 1 || target.r == 1)
            {
                printf("YES\n");
                continue;
            }
            else
            {
                printf("NO\n");
                continue;
            }
        }
        else if(cr[{1 , n}] && cr[{1 , n - 1}] && cr[{2 , n}])//左上角
        {
            if(target.c == 1 || target.r == n)
            {
                printf("YES\n");
                continue;
            }
            else
            {
                printf("NO\n");
                continue;
            }
        }
        else if(cr[{n , 1}] && cr[{n - 1 , 1}] && cr[{n , 2}])//右下角
        {
            if(target.c == n || target.r == 1)
            {
                printf("YES\n");
                continue;
            }
            else
            {
                printf("NO\n");
                continue;
            }
        }
        else if(cr[{n , n}] && cr[{n - 1 , n}] && cr[{n , n - 1}])//右上角
        {
            if(target.c == n || target.r == n)
            {
                printf("YES\n");
                continue;
            }
            else
            {
                printf("NO\n");
                continue;
            }
        }
        else
        {
            ll mid_r = p1.r + p2.r + p3.r - 2 * max(p1.r , max(p2.r , p3.r));
            ll mid_c = p1.c + p2.c + p3.c - 2 * max(p1.c , max(p2.c , p3.c));
            if((mid_r + target.r) % 2 == 0 && (mid_c + target.c) % 2 == 0)
            {
                printf("NO\n");
                continue;
            }
            else
            {
                printf("YES\n");
                continue;
            }
        }
    }
    system("pause");
    return 0;
}
```

---

