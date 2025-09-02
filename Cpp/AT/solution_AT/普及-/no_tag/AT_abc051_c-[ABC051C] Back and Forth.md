# [ABC051C] Back and Forth

## 题目描述

在平面直角坐标系中，有点 $A（sx,sy）$ 和 点 $B（tx,ty）$ 保证 $sx<tx$，$sy<ty$ 并且 $sx,sy,tx,ty$ 都为整数。

在 $A$ 点有一只海豚，它每次可以向上下左右其中一个方向移动一个单位长度。这只海豚想从 $A$ 点到 $B$ 点再回到 $A$ 点再到 $B$ 点再回到 $A$ 点。

要求：除了 $A,B$ 点以外，所有格点都不能走第二遍。海豚不能斜着走。

输出一个字符串 `S` 表示海豚的最短路径，
`S` 中只包括 $U,R,D,L$。
- $U$：向上走一个单位长度。 
- $R$：向右走一个单位长度。 
- $D$：向下走一个单位长度。 
- $L$：向左走一个单位长度。

## 样例 #1

### 输入

```
0 0 1 2```

### 输出

```
UURDDLLUUURRDRDDDLLU```

## 样例 #2

### 输入

```
-2 -2 1 1```

### 输出

```
UURRURRDDDLLDLLULUUURRURRDDDLLDL```

# 题解

## 作者：zct_sky (赞：6)

### Solution:
-----
既然要求最短路径，那么其中一种方法是：

先画一个以 $A_1(tx+1,sy-1)$ 为左上角，以 $B_1(sx,ty)$ 为右下角的矩形，然后从 $A(sx,sy)$ 点出发，沿着这个矩形顺时针走一圈（当然逆时针走也是可以的）。

再画一个以 $A_2(tx,sy)$ 为左上角，以 $B_2(sx-1,ty+1)$ 为右下角的矩形，然后同样从 $A(sx,sy)$ 点出发，沿着顺时针这个矩形走一圈。

也就是说：
1. 向右（$R$）走 $tx-sx$ 个单位长度。
1. 向上（$U$）走 $ty-sy+1$ 个单位长度。
1. 向左（$L$）走 $tx-sx+1$ 个单位长度。
1. 向下（$D$）走 $ty-sy+1$ 个单位长度。
1. 向右（$R$）走 $1$ 个单位长度。
1. 向上（$U$）走 $ty-sy$ 个单位长度。
1. 向右（$R$）走 $tx-sx+1$ 个单位长度。
1. 向下（$D$）走 $ty-sy+1$ 个单位长度。
1. 向左（$L$）走 $tx-sx+1$ 个单位长度。
1. 向上（$U$）走 $1$ 个单位长度。
### Code:
-----
```c++
#include<bits/stdc++.h>
#define ll long long
#define un unsigned
using namespace std;
int sx,sy,tx,ty;
int main(){
	cin>>sx>>sy>>tx>>ty;
	for(int i=sx;i<tx;i++) putchar('R');
	for(int i=sy;i<ty+1;i++) putchar('U');
	for(int i=sx;i<tx+1;i++) putchar('L');
	for(int i=sy;i<ty+1;i++) putchar('D');
	putchar('R');
	for(int i=sy;i<ty;i++) putchar('U');
	for(int i=sx;i<tx+1;i++) putchar('R');
	for(int i=sy;i<ty+1;i++) putchar('D');
	for(int i=sx;i<tx+1;i++) putchar('L');
	putchar('U');
	return 0;
} 
```

---

## 作者：Larryyu (赞：2)

## _Description_
在一个平面直角坐标系内，有一点 $A(x_1,y_1)$ 和点 $B(x_2,y_2)$ 你需要从 $A$ 点走到 $B$ 点，再走到 $A$ 点，再走到 $B$ 点，再回到 $A$ 点。期间，你只能沿网格线走，除 $A,B$ 点，其他任一格点都只能走一次，求最短路径(输出以 $\texttt U,\texttt R,\texttt D,\texttt L$ 组成的字符串)。


## _Solution_

![](https://cdn.luogu.com.cn/upload/image_hosting/69v33u72.png)

如图，方格内的任意一条路径都相等，即3条灰线长度相等，且为 $A,B$ 两点间最短路径。

但两红线在一来回后都有且仅有1次走过，所以，第二来回不能再走方格内的任一一条路径。

黄橙两线即为方格外最短路径，正确性显然。

输出四种方向即可。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
int sx,sy,tx,ty;
int cx,cy;
int main(){
    cin>>sx>>sy>>tx>>ty;
    cx=tx-sx;
    cy=ty-sy;
    for(int i=1;i<=cy;i++){
        cout<<"U";
    }
    for(int i=1;i<=cx;i++){
        cout<<"R";
    }
    for(int i=1;i<=cy;i++){
        cout<<"D";
    }
    for(int i=1;i<=cx;i++){
        cout<<"L";
    }
    cout<<"L";
    for(int i=1;i<=cy+1;i++){
        cout<<"U";
    }
    for(int i=1;i<=cx+1;i++){
        cout<<"R";
    }
    cout<<"DR";
    for(int i=1;i<=cy+1;i++){
        cout<<"D";
    }
    for(int i=1;i<=cx+1;i++){
        cout<<"L";
    }
    cout<<"U";
    return 0;
}
```

#### 完结撒花！！


---

## 作者：sqh_let_it_be (赞：1)

废话不多说，直接上思路。
# 思路：
既然不能重复的走，那么我就在外部绕圈子。

以样例 $1$ 为例：
![](https://cdn.luogu.com.cn/upload/image_hosting/j8gyuzl6.png)

绿色代表第一次从 $A$ 到 $B$ 再回来。蓝色代表第二次从 $A$ 到 $B$ 再回来。这时候走的路径就是最短的。

路径如下：
1. 向上走 $ty-sy$ 个单位长度。
2. 向右走 $tx-sx$ 个单位长度。
3. 向下走 $ty-sy$ 个单位长度。
4. 向左走 $tx-sx+1$ 个单位长度。
5. 向上走 $ty-sy+1$ 个单位长度。
6. 向右走 $tx-sx+1$ 个单位长度。
7. 向下走 $1$ 个单位长度。
8. 向右走 $1$ 个单位长度。
9. 向下走 $ty-sy+1$ 个单位长度。
10. 向左走 $tx-sx+1$ 个单位长度。
11. 向上走 $1$ 个单位长度。

### Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int sx,sy,tx,ty;
int main()
{
	cin>>sx>>sy>>tx>>ty;
	for(int i=1;i<=ty-sy;i++)
	  cout<<"U";
	for(int i=1;i<=tx-sx;i++)
	  cout<<"R";
	for(int i=1;i<=ty-sy;i++)
	  cout<<"D";
	for(int i=1;i<=tx-sx+1;i++)
	  cout<<"L";
	for(int i=1;i<=ty-sy+1;i++)
	  cout<<"U";
	for(int i=1;i<=tx-sx+1;i++)
	  cout<<"R";
	cout<<"DR";
	for(int i=1;i<=ty-sy+1;i++)
	  cout<<"D";
	for(int i=1;i<=tx-sx+1;i++)
	  cout<<"L";
	cout<<"U"<<endl;
	
}
```


---

## 作者：liuyifan (赞：1)

## 因为同样的格子不能走重复，所以最短路径一定是URDL轮换走最大矩形

这题还是比较简单的，具体就看代码了

这是核心走法部分的代码
```cpp
 for(reg int i=1;i<=(e2-e1);i++)printf("U");
 for(reg int i=1;i<=(s2-s1);i++)printf("R");
 for(reg int i=1;i<=(e2-e1);i++)printf("D");
 for(reg int i=1;i<=(s2-s1);i++)printf("L");
```
然后我们沿着外面再转一圈(紧贴这刚才的那一圈

```cpp
printf("L");
for(reg int i=1;i<=(e2-e1)+1;i++)printf("U");                  
for(reg int i=1;i<=(s2-s1)+1;i++)printf("R");
printf("D");
printf("R");
for(reg int i=1;i<=(e2-e1)+1;i++)printf("D");
for(reg int i=1;i<=(s2-s1)+1;i++)printf("L");
printf("U\n");//注意AT的题要换行
```
这里就不贴完整代码了(其实就是上面两段加起来）
### 拒绝抄袭,共建和谐洛谷

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT2282)

小学生又双叒叕来写题解啦！

这题就是个小模拟，只要你把路线图画好，再按照你的路线去模拟即可。

有多种方法，但必须是内圈加外圈的形式。

附上我的~~几何画板弄的~~路线图：

![AAA](https://cdn.luogu.com.cn/upload/image_hosting/jug5j1ty.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

箭头都标好方向了，自己走一遍。

手动模拟完了吗，那就写代码吧。

## 送上满分代码：


```cpp
#include <iostream>
#include <cstdio>
using namespace std;
void mp(int c, char x)   //多次输出函数。
//参数是重复输出的次数与输出的内容。 
{
	for (int i = 1; i <= c; i++) cout << x;
}
int main()
{
	int sx, sy, fx, fy;
	scanf("%d%d%d%d", &sx, &sy, &fx, &fy);
	mp(fx-sx, 'R');
	mp(fy-sy, 'U');
	mp(fx-sx, 'L');
	mp(fy-sy, 'D');
	cout << "D";
	mp(fx-sx+1, 'R');
	mp(fy-sy+1, 'U');
	cout << "LU";
	mp(fx-sx+1, 'L');
	mp(fy-sy+1, 'D');
	cout << "R";
	printf("\n");    //勿忘祖传换行。 
	return 0;
}
```


---

## 作者：wjk2020 (赞：0)

~~海豚疯了~~
### 这道题就是在两个点之间找到四条不重叠的连接路线。
注意“四条”这个字眼，意味着 A 点和 B 点的四个方向全要走过，否则会有重叠，不符合题意。

不难想到，前两条线 （ 一去一回 ） 就是最短路径 （ 组成一个正方形 ） ，后两条线就在周围紧贴着围一圈即可。

好，既然有了思路，就赶紧码代码吧！

首先，因为前两条线组成了一个正方形的图案，所以代码很好写，是这样的：

```cpp
for(int i = 1;i <= (t2-t1);i++)
	cout << 'D';
for(int i = 1;i <= (s2-s1);i++)
	cout << 'L';
for(int i = 1;i <= (t2-t1);i++)
	cout << 'U';
for(int i = 1;i <= (s2-s1);i++)
	cout << 'R';

```
接下来就是在外面围一圈了，代码稍微有点复杂，需要仔细想想。~~码风太丑，就不写出来了。~~

~~求过~~

---

