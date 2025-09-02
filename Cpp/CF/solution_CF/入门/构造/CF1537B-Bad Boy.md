# Bad Boy

## 题目描述

Riley is a very bad boy, but at the same time, he is a yo-yo master. So, he decided to use his yo-yo skills to annoy his friend Anton.

Anton's room can be represented as a grid with $ n $ rows and $ m $ columns. Let $ (i, j) $ denote the cell in row $ i $ and column $ j $ . Anton is currently standing at position $ (i, j) $ in his room. To annoy Anton, Riley decided to throw exactly two yo-yos in cells of the room (they can be in the same cell).

Because Anton doesn't like yo-yos thrown on the floor, he has to pick up both of them and return back to the initial position. The distance travelled by Anton is the shortest path that goes through the positions of both yo-yos and returns back to $ (i, j) $ by travelling only to adjacent by side cells. That is, if he is in cell $ (x, y) $ then he can travel to the cells $ (x + 1, y) $ , $ (x - 1, y) $ , $ (x, y + 1) $ and $ (x, y - 1) $ in one step (if a cell with those coordinates exists).

Riley is wondering where he should throw these two yo-yos so that the distance travelled by Anton is maximized. But because he is very busy, he asked you to tell him.

## 说明/提示

Here is a visualization of the first test case.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1537B/55dd7a7a8828547b72bc3be325a8a8e51cf757fa.png)

## 样例 #1

### 输入

```
7
2 3 1 1
4 4 1 2
3 5 2 2
5 1 2 1
3 1 3 1
1 1 1 1
1000000000 1000000000 1000000000 50```

### 输出

```
1 2 2 3
4 1 4 4
3 1 1 5
5 1 1 1
1 1 2 1
1 1 1 1
50 1 1 1000000000```

# 题解

## 作者：BurningEnderDragon (赞：20)

[题目链接：CF1537B Bad Boy](https://www.luogu.com.cn/problem/CF1537B)

## 题意解释

Riley 有一个 $n$ 行 $m$ 列的房间，他初始在房间内 $(i,j)$ 的位置，他要把两个悠悠球扔到房间的任意两个位置（两个位置可以相同），并且从初始位置出发捡回两个悠悠球后回到初始位置。

Riley 每次只会移动到相邻（有公共边）的格子，且整个过程中只会沿着当前状态的最短路径移动。求把悠悠球扔在哪两个位置可以使 Riley 需要移动的总距离最长。

## 结论

容易验证，将两个悠悠球扔在房间**对角线的两个角落**，Riley 需要移动的总距离一定最长。

以样例中的第 $3$ 组数据（$n=3$，$m=5$，$i=2$，$j=2$）为例：

其中蓝色点表示 Riley 的初始位置，两个红色点表示悠悠球的位置，绿色箭头表示 Riley 的一种移动的路线。

当把两个悠悠球分别扔在房间的左上角和右下角时，Riley 移动的路线长度**相当于在房间的外围走一圈**，此时路线最长：

![](https://cdn.luogu.com.cn/upload/image_hosting/f1piz3nx.png)

当把两个悠悠球分别扔在房间的左上角和右上角时，Riley 移动的路线长度显然小于上一种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/4ka3qhj3.png)

上述结论成立。

可以发现对于初始位置在房间外围的情况，会有其他的最优解，但此时将悠悠球扔在房间对角线的两个角落亦是一种最优解。

所以，你可以输出以下两种答案中的任意一种：

- 左上角和右下角，即 $(1,1)$ 和 $(n,m)$；
- 右上角和左下角，即 $(1,m)$ 和 $(n,1)$。

## 代码

```cpp
#include <cstdio>
int t,n,m,i,j,x1,y1,x2,y2,ans;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%d",&n,&m,&i,&j);
		printf("%d %d %d %d\n",1,1,n,m);
	}
	return 0;
}
```



---

## 作者：FjswYuzu (赞：2)

注意到原问题目标是，设当前点为 $X$，即 $(i,j)$，选择两个点 $A,B$ 使 $\operatorname{Dis}(A,X)+\operatorname{Dis}(A,B)+\operatorname{Dis}(B,X)$ 最大。其中 $\operatorname{Dis}(P,Q)$ 为 $P,Q$ 之间的曼哈顿距离。

比较显然的是，如果我们将 $A,B$ 同时放在 $X$ 的左边或右边，一定不优；同理也不可能同时放在上面和下面（随便证证.jpg）。那么上面的式子我们可以简单的写成 $2\operatorname{Dis}(A,B)$。那么答案很显然，就是选择这个矩形的两个边角即可。即，无论 $X$ 是什么点，总有一个合法解 $(1,1),(n,m)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int Abs(int x){return x<0?-x:x;}
int getDis(int a,int b,int c,int d){return Abs(a-c)+Abs(b-d);}
int main(){
	int T;
	scanf("%d",&T);
	while(T-->0)
	{
		int n,m,i,j;
		scanf("%d %d %d %d",&n,&m,&i,&j);
		printf("%d %d %d %d\n",1,1,n,m);
	}
	return 0;
}
```

---

## 作者：miraculously (赞：1)

题目大意：

在房间里放两个溜溜球，使它们在不同的位置。

分析：

本题有spj，只要在范围内输出两个位置就可以了。

代码如下（只是其中一种情况）：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,x,y;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%d",&n,&m,&x,&y);
		printf("1 1 %d %d\n",n,m);//为了方便，我随机找的点
	}
}
```


---

## 作者：ʕ•ﻌ•ʔ (赞：1)

传送门：[CF1537B](https://www.luogu.com.cn/problem/CF1537B)。

CF题面：[CF1537B](https://codeforces.com/contest/1537/problem/B)。

---


### 题目大意：

Anton 有一个房间，共有 $n$ 行 $m$ 列，也就是一共 $n \times m $ 个格子。他一开始站在编号为 $(i,j)$ 的格子里。给出 $t$ 组测试数据，对于每一组测试数据，将分别给出 $n\ m\ i\  j$ 四个整数。

你需要在 $(x_1,y_1)$ 和 $(x_2,y_2)$ 处放两个悠悠球。Anton 会从初始位置出发，他每次只能向上，向下，向左或者向右移动一个格子（前提是存在这样的格子，没有超出边界），Anton 需要将两个悠悠球都捡起来（也就是要到达这两个悠悠球的位置），然后再返回自己的初始位置。

你需要选择放置这两个悠悠球的位置，使得 Anton 走过的路径最长。

输出$x_1\ y_1\  x_2\  y_2$。（如果有多组解输出**任意一组**即可）。

---

### 题目分析：

通过分析几组样例不难发现，对于一个普通的房间（先不管特殊的）和普通的出发位置（即不在四个角中的任意一个），我们只要选择**任意一组对角**，那 Anton 走过的路径显然最长。

如果房间是特殊的情况（$1\times1$,$1\times 2$,$2\times 1$）,那我们只要特判一下即可，这一步可以自己画图试试，答案也比较明显。

而如果出发位置是一个角落，那我们只需要去**对角**和**剩下两个角中任意一个**即可。

以上结论的正确性证明：

要想使 Anton 经过的路径最长，那显然离初始位置越远越好。可以考虑反证，**即如果选择的位置比角落更接近初始位置，那走的距离明显变短了。**

## AC CODE:

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,x,y,t;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>x>>y;
		if(n==m&&x==y&&n==1&&x==1){
			cout<<"1 1 1 1"<<endl;
			continue ;
		}
		if(n==1&&m==2){
			if(x==1&&y==2) cout<<"1 1 1 1"<<endl;
			else cout<<"1 2 1 2"<<endl;
			continue;
		} 
		if(n==2&&m==1){
			if(x==1&&y==1) cout<<"2 1 2 1"<<endl;
			else cout<<"1 1 1 1"<<endl;
			continue ;
		}
		//以上为特判 1*1 1*2 2*1的部分 
		if(x==1&&y==1){
			cout<<n<<" "<<m<<" "<<n<<" "<<"1"<<endl;
			continue;
		}
		if(x==1&&y==m){
			cout<<n<<" "<<"1 "<<n<<" "<<m<<endl;	
			continue ;
		}
		if(x==n&&y==1){
			cout<<"1 "<<m<<" "<<n<<" "<<m<<endl;
			continue ;
		}
		if(x==n&&y==m){
			cout<<"1 1 "<<n<<" 1"<<endl;	
			continue ;
		}
		//以上为特判初始位置在角上的情况 
		cout<<"1 1 "<<n<<" "<<m<<endl; //普通情况，任选一组对角就可以 
	}
	return 0;
} 
```








---

## 作者：int32 (赞：0)

### 思路分析

要想走的路程最多，则最好就是走一遍外围的长度。

所以你只需要把球放在房间的对角就行了。

通解为 $(1,1),(n,m)$ 与 $(1,m),(n,1)$。

### 代码展示

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, x, y, t;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>k>>x>>y;
        printf("1 1 %d %d\n",n,k);
        //printf("1 %d %d 1",k,n);
    }
    return 0;
}
```

---

## 作者：Cripple_Abyss (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1537B)

## Description 
- 给定房间的大小和起始位置。

- 在房间的任意两个位置上放上溜溜球（可重复），使得从起点出发，走不重复的路径且经过这两个位置，最终回到起点的距离最大。

## Solution
- 既然要求走的距离最大，安排的两个位置的距离一定要尽可能大。

- 对于每次询问，我们都在 $(1,1)$ 和 $(n,m)$ 的位置上放置溜溜球。

## Code 
```cpp
#include <cstdio>
typedef long long ll;
inline void in(ll &x) {
	x=0;
	ll f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	x*=f;
}
ll T,n,m,a,b;
int main() {
	in(T);
	while (T--) {
		in(n),in(m),in(a),in(b);
		printf("1 1 %lld %lld\n",n,m);
	}
	return 0;
}


```

---

