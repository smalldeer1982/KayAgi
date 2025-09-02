# Treasure Hunt

## 题目描述

Bill船长收到一个有趣的挑战，有一些陌生人给了他一张地图和一些能够远程传送的药水…………

简单而言，给你移动方式，让你判断能否从(x1,y1)的位置移动到(x2,y2)的位置

而移动方式如下：输入x,y，你一共有四种移动方式可选择
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817A/5f61670d9b3608116440491f8884c7a41d992eb9.png)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817A/fdee4e4bb66766e4b40f483072f3c9b0b1880af7.png)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817A/7517913342c0c19a2f0627ccf2eab647a7b547bf.png)
![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817A/324d1b3af2d1a5e602e1cfc99403662780a262b3.png)

## 样例 #1

### 输入

```
0 0 0 6
2 3
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
1 1 3 6
1 5
```

### 输出

```
NO
```

# 题解

## 作者：xxxalq (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/CF817A) & [CF链接](http://codeforces.com/problemset/problem/817/A)

## 思路分析：

其实这道题并没有想象的那么难，只需要 $2$ 个 $O(1)$ 的判断即可。

首先一个大家都很容易想到的，那就是两个 $x$ 坐标的差值的绝对值必须是 $a$ 的倍数，同理两个 $y$ 坐标的差值的绝对值也必须是 $B$ 的倍数。要不然无论如何都跳不到重点。

但是如果只判断这一个是不行的，可以参考样例 $2$：

输入:

```
1 1 3 6
1 5
```

输出:


```
NO
```

这个样例满足第一个判断条件，但是他仍然是不合法的，因为我们忽略了一个重要的问题，每一次操作 $x$ 和 $y$ 坐标都会发生变化，显然我们的第一个判断只是分别考虑了 $x$ 和 $y$ 坐标。那如何同时考虑 $2$ 个坐标呢？只需要判断 $\frac{|x1-x2|}{a}$ 和 $\frac{|y1-y2|}{b}$ 的奇偶性是否相同即可。

## 代码：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int stx,sty,enx,eny,a,b;
int main(){
	cin>>stx>>sty>>enx>>eny;
	cin>>a>>b;
	if(abs(enx-stx)%a==0&&abs(eny-sty)%b==0&&(abs(enx-stx)/a)%2==(abs(eny-sty)/b)%2){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	return 0;
}
```

[**AC记录**](https://www.luogu.com.cn/record/117872345)

---

## 作者：清清老大 (赞：1)

## 题意

从 $(x_1,y_1)$ 出发，每次可以用下面的四种移动方式，问能否到达 $(x_2,y_2)$。

方式一. $(x_1,y_1) \to (x_1+x,y_1+y)$

方式二. $(x_1,y_1) \to (x_1+x,y_1-y)$

方式三. $(x_1,y_1) \to (x_1-x,y_1+y)$

方式四. $(x_1,y_1) \to (x_1-x,y_1-y)$

## 思路

首先，无论怎么移动，横纵坐标变换量都分别是 $x$ 和 $y$ 的倍数。

但是还不够，再观察四种方式，可以发现横向或纵向移动的方法

上移 $2y$ (方式一 $+$ 方式三)： $(x_1,y_1) \to (x_1,y_1+2y)$

下移 $2y$ (方式二 $+$ 方式四)： $(x_1,y_1) \to (x_1,y_1-2y)$

右移 $2x$ (方式一 $+$ 方式二)： $(x_1,y_1) \to (x_1+2x,y_1)$

左移 $2x$ (方式三 $+$ 方式四)： $(x_1,y_1) \to (x_1-2x,y_1)$

设出发点是 $(x_1,y_1)$ 最终到达的点是 $(x_1+ax,y_1+by)$ ，分四种情况讨论：

### 1. $a,b$ 都是偶数

由于 $a$ 是偶数，所以通过左移或右移的方法，可以 $(x_1,y_1) \to (x_1+ax,y_1)$。

由于 $b$ 是偶数，所以通过上移或下移的方法，可以 $(x_1+ax,y_1) \to (x_1+ax,y_1+by)$。

所以，当 $a,b$ 都是偶数时，可以到达。

### 2. $a,b$ 都是奇数

由于 $a$ 是奇数，所以通过左移或右移的方法，可以 $(x_1,y_1) \to (x_1+(a-1)x,y_1)$。

由于 $b$ 是奇数，所以通过上移或下移的方法，可以 $(x_1+(a-1)x,y_1) \to (x_1+(a-1)x,y_1+(b-1)y)$。

最后，用题目中给出的方式一， $(x_1+(a-1)x,y_1+(b-1)y) \to (x_1+ax,y_1+ay)$。

所以，当 $a,b$ 都是奇数时，可以到达。

### 3. $a$ 是偶数， $b$ 是奇数

由于 $a$ 是偶数，所以通过左移或右移的方法，可以 $(x_1,y_1) \to (x_1+ax,y_1)$。

由于 $b$ 是奇数，所以通过上移或下移的方法，可以 $(x_1+ax,y_1) \to (x_1+ax,y_1+(b-1)y)$。

此时，横坐标离终点还差 $y$ ，但是不管怎么走，都不能把横坐标加上 $y$ ，所以，当 $a$ 是偶数， $b$ 是奇数时，不可以到达。

### 4. $a$ 是奇数， $b$ 是偶数

证明同第三种情况，当 $a$ 是奇数， $b$ 是偶数时，纵坐标离终点还差 $x$ 不可以到达。

综上所述，当 $a,b$ 同为偶数或同为奇数时才能到达。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int x,x1,x2,y,y1,y2;
    cin >> x1 >> y1 >> x2 >> y2 >> x >> y;
    int dx = abs(x1 - x2),dy = abs(y1 - y2);
    if(dx % x || dy % y || (dx / x) % 2 != (dy / y) % 2)
    {
        puts("NO");
    }
    else
    {
        puts("YES");
    }
}
```

---

## 作者：zk_y (赞：0)

这道题目我们可以看出有 $4$ 类操作，题目都给出了，这里就不一一赘述了。

我们可以很轻松地看出来，如果 $x_1 \equiv x_2 \pmod x$ 或者 $y_1 \equiv y_2 \pmod x$。那么一定是需要输出 ``NO``。但是，这题就这么简单吗？

我们知道就算是两个数的差可以整除，也不一定是可以做成的，因为我们每次对于 $x$，$y$ 的数值差改变要么是 $0$（同加同减），要么是 $2$（一加一减）。所以我们需要判断每次改变的次数，如果它们模 $2$ 的余数相等并且满足上面的性质，那么就是可以的，反之亦然。

这里可以通过加和或者是作差来判断奇偶性。

---
# AC 代码

```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int t_x,t_y,x_1,y_1,x_2,y_2,x,y;
int main(){
	scanf("%d%d%d%d%d%d",&x_1,&y_1,&x_2,&y_2,&x,&y);
	t_x=(x_1-x_2)/x;//判断每次改变的次数
	t_y=(y_1-y_2)/y;
	if((x_1-x_2)%x==0&&(y_1-y_2)%y==0){
		if((t_x+t_y)%2==0){
			printf("YES");
			return 0;
		}
	}
	printf("NO");
	return 0;
}
```


---

## 作者：Sternenlicht (赞：0)

思路：

对于每次走到的点 $(nx,ny)$，一定是 $(x+k_1x_1,y+k_2y_1)$ 的形式，其中 $(x,y)$ 为初始坐标，$k_1,k_2\in Z$。若 $k_1$ 和 $k_2$ 中有一个不为整数，则无解，输出 NO。

还有一种情况。$x_1$ 移动偶数次，$y_1$ 也要移动偶数次；$x_1$ 移动奇数次，$y_1$ 也要移动奇数次。即 $x_1$ 与 $y_1$ 同奇偶。

通过上面的推论，就可以写出代码。

```cpp
#include <bits/stdc++.h>
#define LL long long
#define endl '\n'
#define lowbit(x) (x&-x)
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define INF 0x3f3f3f3f
namespace IO{
	inline LL read(){
	    LL x=0,f=1;char ch=getchar();
	    for (;!isdigit(ch);ch=getchar())if (ch=='-')f=-1;
	    for (;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
	    return x*f;
	}
	inline void write(LL x,char c='\n'){
	    if (x){
	    	if (x<0)x=-x,putchar('-');
	    	char a[30];short l;
	    	for (l=0;x;x/=10)a[l++]=x%10^48;
	    	for (l--;l>=0;l--)putchar(a[l]);
		}
		else putchar('0');putchar(c);
	}
	inline char getc(){
		char ch=getchar();
		while (isspace(ch))ch=getchar();
		return ch;
	}
}
using namespace IO;
using namespace std;

int main(){
	int x1=read(),y1=read(),x2=read(),y2=read(),x=read(),y=read();
	int kx=abs(x1-x2),ky=abs(y1-y2);
	if (kx%x!=0||ky%y!=0||((kx/x)&1)!=((ky/y)&1))puts("NO");//&1=%2 
	else puts("YES");
	return 0;
}
```

---

## 作者：Supor__Shoep (赞：0)

这是一道比较坑人的题目。

刚刚看到题的我天真地以为这是一道深搜的题目，便自信满满地打起了代码，结果总是出了各种大问题。

然后我顿时反应过来：对于每次移动的坐标 $nx$ 一定是 $sx+k\times x$，其中 $nx$ 为当前 $x$ 坐标，$sx$ 为初始坐标，$k$ 为整数。同理得到 $ny=sy+k\times y$。如果要到达终点，那么也一定会满足上面的结论。如果逆推算出来的 $k_1$ 和 $k_2$ 有一个不为整数，那么就一定无法达到终点。

当然除了这些情况，还有一些也会导致答案错误。

对于只移动 $x$ 的情况，可以用偶数次使得 $y$ 的值先加后减。即 $x$ 移动偶数次，相应的 $y$ 也必须移动偶数次，同理 $x$ 移动奇数次，相应的 $y$ 也需要移动奇数次。通过这个规律，如果一定能够到达终点，那么 $ex/x$ 以及 $ey/y$ 必须满足同偶或者同奇。

所以结果就自然而然地出来了。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int sx,sy,ex,ey;
    cin>>sx>>sy>>ex>>ey;
    int x,y;
    cin>>x>>y;
    int p=abs(sx-ex);
    int q=abs(sy-ey);
    if(p%x!=0||q%y!=0||(p/x)%2!=(q/y)%2)
    {
        cout<<"NO";
    }
    else
    {
        cout<<"YES";
    }
    return 0;
}
```

---

## 作者：HuZHUNZHUN (赞：0)

### 本蒟蒻的第二篇题解QAQ

本题思路：

1) 不难发现，从 $(x1,x2)$ 能到达的位置都形如 $(x1+k1x,y1+k2y)$ 的点，这里 $k1,k2$ 都是整数。

2) 因此，想要到达终点 $(x2,y2)$，必须满足 $x\mid x2-x1$ 且 $y\mid y2-y1$。

3) 结束了？当然没有。如果我们将起点和终点都放到一个单位长度分别为 $x,y$ 的平面直角坐标系中，由于只能斜着走，所以从某个点永远到不了它相邻的点，因此，一旦出现了这种情况，也就是 $\dfrac{x2-x1}{x}$ 和 $\dfrac{y2-y1}{y}$ 奇偶互异，就到不了。

总结一下：一个点能到达当且仅当 $x\mid x2-x1$，$y\mid y2-y1$ 和 $2\mid \dfrac{x2-x1}{x}+\dfrac{y2-y1}{y}$ 同时成立。

无注释代码奉上：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x1,y1,x2,y2,x,y;
	ios::sync_with_stdio(false);
	cin>>x1>>y1>>x2>>y2>>x>>y;
	int d1=abs(x1-x2),d2=abs(y1-y2);
	if((d1%x==0) && (d2%y==0) && ((d1/x)%2==(d2/y)%2)) cout<<"YES";
	else cout<<"NO";
	return 0;
}


---

## 作者：SalomeJLQ (赞：0)

**2021.5.8 Update：把非公式 LaTeX删了**

------------


这种题我们拿到操作方式，发现每次对横纵坐标的改变都是a和 $b$。因此比较显然的是无论怎么移动，横纵坐标的变化量都分别是x和y的倍数。

------------
然而这还不够。设变化量为 $\left|\Delta x\right|,\left|\Delta y\right|$，仔细分析第二个样例发现，我们还需要满足 $\left|\frac{\left|\Delta x\right|}{x}-\frac{\left|\Delta y\right|}{y}\right|$ 是偶数。

为什么呢？

设 $d=\left|\frac{\left|\Delta x\right|}{x}-\frac{\left|\Delta y\right|}{y}\right|$，观察四个操作

- $(a+x,b+y)$
- $(a+x,b-y)$
- $(a-x,b+y)$
- $(a-x,b-y)$

其中第一个操作对于d的贡献是0，第二个操作的贡献是 $1-(-1)=2$；同理第三个是2，第四个是0。而d最初为0，都是偶数的贡献。所以我们如论怎样去操作，最终d都是偶数。

------------


因此我们定义一个bool变量ck，为真表示可以，在程序中只需这两个 if：

```cpp
if(abs(x_1-x_2)%x||abs(y_1-y_2)%y)ck=false;
if(abs(x_1-x_2)/x%2!=abs(y_1-y_2)/y%2)ck=false;
```

然后这题就做完了。

---

## 作者：sandwich (赞：0)

咳咳咳，这一道题的话，看到第一眼，我就觉得，这是一道dfs，但是呢，这看起来又不太像，因为可以四面八方移动，所以感觉巨难，但是后来，我才发现，这题正如楼下讲的，非常简单。

还有，为什么要%2呢？因为它每一次横坐标必须改变x，纵坐标必须改变y，如果这两个数%2不相等的话，就绝对不可能达到，所以，就这样喽

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x1,x2,y1,y2,x,y;
    cin>>x1>>y1>>x2>>y2;
	x1=abs(x2-x1);y1=abs(y2-y1);
	cin>>x>>y;
    if(x1%x!=0||y1%y!=0||(x1/x)%2!=(y1/y)%2)
    cout<<"NO";
    else
    cout<<"YES";
    return 0;
}
```


---

