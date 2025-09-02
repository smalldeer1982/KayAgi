# [SDCPC 2023] Puzzle: Sashigane

## 题目描述

给定一个 $n$ 行 $n$ 列的网格，网格中包含恰好一个黑色方格，其余方格均为白色。令 $(i, j)$ 表示位于第 $i$ 行第 $j$ 列的格子，这个黑色方格位于 $(b_i, b_j)$。

您需要用若干 L 形覆盖所有白色格子，使得每个白色格子都恰好被一个 L 形所覆盖，同时唯一的黑色方格不能被任何 L 形覆盖。L 形不能超过网格的边界。

更正式地，网格中的一个 L 形由四个整数 $(r, c, h, w)$ 唯一确定，其中 $(r, c)$ 确定了 L 形的转折点，$h$ 和 $w$ 确定了 L 形两臂的方向和长度。四个整数满足 $1 \le r, c \le n$，$1 \le r + h \le n$，$1 \le c + w \le n$，$h \ne 0$，$w \ne 0$。

- 若 $h < 0$，则所有满足 $r + h \le i \le r$ 的格子 $(i, c)$ 均属于该 L 形；否则若 $h > 0$，则所有满足 $r \le i \le r + h$ 的格子 $(i, c)$ 均属于该 L 形。
- 若 $w < 0$，则所有满足 $c + w \le j \le c$ 的格子 $(r, j)$ 均属于该 L 形；否则若 $w > 0$，则所有满足 $c \le j \le c + w$ 的格子 $(r, j)$ 均属于该 L 形。

下图展示了几种 L 形。

![](https://cdn.luogu.com.cn/upload/image_hosting/s4jgji61.png)

## 样例 #1

### 输入

```
5 3 4
```

### 输出

```
Yes
6
5 1 -1 3
1 2 1 3
3 1 -2 1
4 3 -1 -1
4 5 1 -1
2 5 1 -2
```

## 样例 #2

### 输入

```
1 1 1
```

### 输出

```
Yes
0
```

# 题解

## 作者：One_JuRuo (赞：5)

## 思路

刚看到还被吓了一跳，以为又是什么神仙题目，细想了一下觉得有做头。

### Step1.不算很好的解法

首先想到左下一个右上一个，就可以套一圈，然后就可以先套一个正方形出来，这个正方形可以尽可能的大，如下图的红色框。

![](https://cdn.luogu.com.cn/upload/image_hosting/pxru6gpw.png)

然后就剩下三种情况：

1. 刚好覆盖完（即黑色方格恰好在正中间），输出就完事儿。
2. 留下两边，直接对角输出就完事儿，剩多少就输出多少。
3. 留下三边，这样就剩下两个对角，先从一个对角输出，然后从另一个对角输出。

![](https://cdn.luogu.com.cn/upload/image_hosting/ncfa68ft.png)

如上图，红色方格代表套出的正方形，左侧为第二种情况，右侧为第三种情况。

想法很不错（至少当时我是这么觉得的），然后实现了很久，居然 WA 了。

对了，顺带一提，设套出的正方形边长为 $k$，再令 $sum=\frac{k-1}{2}$，那么套出的正方形有 $2\times sum$ 个 L 形，还剩下 $n-2\times sum-1$ 个空行或者空列，也就是还剩下 $n-2\times sum-1$ 个 L 形。

所以一共会放 $n-1$ 个 L 形。

如果想看这个做法的代码，很抱歉，我实在不想去调了，想看可以看这个[屎山代码](https://www.luogu.com.cn/paste/0jbra28g)。

### Step2.逐步扩展的正方形

抛弃了上面的做法后，我就跑去看其他题了，然后突然就想到了一个很不错的方法。

![](https://cdn.luogu.com.cn/upload/image_hosting/3a23p2tm.png)

倒过来想，我们如何把一个完整的正方形通过切割 L 形，变成只有 $1\times 1$ 的黑色方格呢？

可以每次从边角切一个 L 形，就变成了一个边长小 $1$ 的小正方形，然后逐步朝黑色方格切割，最后就可以边长黑色方格。

我们再反过来，每次从当前正方形的四个角添一个正方形就可以了，直到添成 $n\times n$ 的大正方形。

每次边长大 $1$，所以需要 $n-1$ 次，这个方法的总次数比上一个方法好理解一些。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,xx,xxx,yy,yyy;
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	printf("Yes\n%d\n",n-1);//直接得出答案
	xx=xxx=x,yy=yyy=y;//记录边界，用xx，xxx之类的绝对不是因为x1,x2,y1,y2是关键字CE了qwq
	for(int i=1;i<n;++i)
	{
		if(xx>1&&yy>1) printf("%d %d %d %d\n",--xx,--yy,i,i);//如果可以从这个方向添L形，下面同理
		else if(xx>1&&yyy<n) printf("%d %d %d %d\n",--xx,++yyy,i,-i);
		else if(xxx<n&&yy>1) printf("%d %d %d %d\n",++xxx,--yy,-i,i);
		else printf("%d %d %d %d\n",++xxx,++yyy,-i,-i);
	}
}
```

---

## 作者：Halberd_Cease (赞：2)

赛时没写出来，赛后口胡一篇题解。

首先要被填充的矩形是正方形，其中不能被填充的黑色方块只有一个，显然也可以看做正方形。

我们要做的，就是添加 L 形，让整个大正方形被填满。

一个正方形，可以通过在外围添加一个 L 形，变成一个更大（边长$+1$）的正方形。

然后我们的思路就是往 $4$ 个方向加 L 形，先往左上方加，加不动了往左下方，然后右下方，最后右上方。

此处加不动的定义就是在这个方向上有任意一边到达了边界。

![](https://cdn.luogu.com.cn/upload/image_hosting/fn6o2kqs.png)

像这个图，染色顺序：红橙黄绿。

像这样子添加，原来正方形的边长每次都会 $+1$，添加 $n-1$ 个 L 形之后，就可以填满整个正方形。

为什么一定可以填满？

填完一个方向过后，会出现 $2$ 种情况，一种就是有一条边触到外围，这时候转向第二个方向，在第二个方向上也让一条边触到外围，然后就变成了下面的第二种情况。

第二种，有 $2$ 条边触碰到外围，因为我们扩展的形状和外围的形状都是正方形，所以只需要向那两条边扩展就好了。

代码就不放了，因为没写。

---

## 作者：zzbzwjx (赞：1)

## 题意
[~~自己看题~~](https://www.luogu.com.cn/problem/P9567)

## 思路
1. 我们先找到一黑方块为中心的最小正方形，我们可以直接将这个正方形表达出来。

![](https://cdn.luogu.com.cn/upload/image_hosting/zuyik4qy.png)

2. 然后我们就一上下分别扩展就行

![](https://cdn.luogu.com.cn/upload/image_hosting/hcjrrxt9.png)

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,xx,yy;
int main() {
	cin>>n>>xx>>yy;
	int r=min(min(min(xx-1,yy-1),n-xx),n-yy);
	puts("Yes\n");
	int res=r*2+(n-r*2-1);
	cout<<res<<'\n';
	int h=1,w=2,x,y;
	x=xx,y=yy;
	for (int i=1;i<=r;i++){
		cout<<x+i<<' '<<y+i<<" -"<<h<<" -"<<w<<'\n';
		cout<<x-i<<' '<<y-i<<' '<<h<<' '<<w<<'\n';
		h+=2,w+=2;
	}
	res-=r*2;
	int t=0;
	if (xx-r==1) {
		x=x+r+1,y=yy-r-1;
		while (x<=n&&y>=1) {
			t++;
			cout<<x<<' '<<y<<" -"<<x-1<<' '<<x-1<<'\n';
			x++,y--;
		}
		x=y=n;
		while (t<res) {
			cout<<x<<' '<<y<<" -"<<x-1<<" -"<<x-1<<'\n';
			x--,y--,t++;
		}
	} else if(yy+r==n) {
		x=x-r-1,y=yy-r-1;
		while (x>=1&&y>=1) {
			t++;
			cout<<x<<' '<<y<<' '<<n-y<<' '<<n-y<<'\n';
			x--,y--;
		}
		x=n,y=1;
		while (t<res) {
			cout<<x<<' '<<y<<" -"<<x-1<<' '<<x-1<<'\n';
			x--,y++,t++;
		}
	} else if(xx+r==n) {
		x=x-r-1,y=yy-r-1;
		while (x>=1&&y>=1){
			t++;
			cout<<x<<' '<<y<<' '<<n-x<<' '<<n-x<<'\n';
			x--,y--;
		}
		x=1,y=n;
		while (t<res) {
			cout<<x<<' '<<y<<' '<<y-1<<" -"<<y-1<<'\n';
			x++,y--,t++;
		}
	}else{
		x=x-r-1,y=yy+r+1;
		while (x>=1&&y<=n){
			t++;
			cout<<x<<' '<<y<<' '<<y-1<<" -"<<y-1<<'\n';
			x--,y++;
		}
		x=y=n;
		while (t<res){
			cout<<x<<' '<<y<<" -"<<y-1<<" -"<<y-1<<'\n';
			x--,y--,t++;
		}
	}
	return 0;
}
```

---

## 作者：yxy666 (赞：1)

题意：有一个 $n \times n$ 的白色矩阵，中间有一个黑色方块，我们要用 $L$ 型的长条将矩阵填满且不能覆盖到黑色方块。

![](https://cdn.luogu.com.cn/upload/image_hosting/vlhy380k.png)

以样例为例，不要管他给我们的方法，那是故意恶心你的。每种颜色表示一个 $L$ 型长条，显而易见，每一次补全的图形都是正方形且边长在上一次的基础上长度增加了 $1$，而且补的 $L$ 型长条都是长款相等的。因为最终补全的图形是正方形，这样子补肯定是有可行解的。那就排除了不存在可行方案的可能。

但是个人感觉每次补全的代码写起来有点怪怪的，所以就倒着推，每次切割，从$n \times n$ 的矩阵推到 $(n-1) \times (n-1)$ 的矩阵，用 dfs 分治就可以轻松解决啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sx,sy;
struct yxy{
	int r,c,h,w;
}Ans[1000005];
int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
void dfs(int Ux,int Dx,int Ly,int Ry,int Z){
	if(Z==1)return;
	if(Ux<sx&&Ly<sy){
		Ans[++m]=(yxy){Ux,Ly,Z-1,Z-1};
		dfs(Ux+1,Dx,Ly+1,Ry,Z-1);
	}
	else if(Dx>sx&&Ly<sy){
		Ans[++m]=(yxy){Dx,Ly,1-Z,Z-1};
		dfs(Ux,Dx-1,Ly+1,Ry,Z-1);
	}
	else if(Ux<sx&&Ry>sy){
		Ans[++m]=(yxy){Ux,Ry,Z-1,1-Z};
		dfs(Ux+1,Dx,Ly,Ry-1,Z-1);
	}
	else if(Dx>sx&&Ry>sy){
		Ans[++m]=(yxy){Dx,Ry,1-Z,1-Z};
		dfs(Ux,Dx-1,Ly,Ry-1,Z-1);
	}
}//一共有四种切割矩阵的方式，只要不切到黑色格子就是合法的
int main(){
	n=read();sx=read();sy=read();
	if(n==1)puts("Yes"),putchar('0'),exit(0);
	dfs(1,n,1,n,n);
	printf("Yes\n");
	printf("%d\n",m);
	for(int i=1;i<=m;i++)printf("%d %d %d %d\n",Ans[i].r,Ans[i].c,Ans[i].h,Ans[i].w);
	return 0;
}
```


---

## 作者：__zfy__ (赞：0)

### 题意

一个空白矩形，中间有一格黑色，不能覆盖到黑色的情况下，要求用 $L$ 形覆盖满整个矩形，求一些乱七八糟的值。

### 思路

首先看如何覆盖更优，拿出纸笔写写，想到了这样一种方法（有点潦草）。

![](https://cdn.luogu.com.cn/upload/image_hosting/5amc90pf.png)

这样就可以覆盖了，但是如果你看样例，会发现：妈妈！这题太难了！不要惊慌，那是骗你的，实际上都可以搞成这样，而且根本不存在不可行解。数量直接算就可以了。至于每个 $L$ 形的坐标，我们来继续看图。

![](https://cdn.luogu.com.cn/upload/image_hosting/vjwicese.png)

有图有真相，不难看出，每次的搜索的条件和下一步做什么。

```cpp
	if(x1<tx&&ly<ty){
                 ……
		dfs(x1+1,x2,ly+1,ry,z-1);
	}
	else if(x2>tx&&ly<ty){
                 ……
		dfs(x1,x2-1,ly+1,ry,z-1);
	}
	else if(x1<tx&&ry>ty){
                 ……
		dfs(x1+1,x2,ly,ry-1,z-1);
	}
	else if(x2>tx&&ry>ty){
                 ……
		dfs(x1,x2-1,ly,ry-1,z-1);
	}
```

---

## 作者：寄风 (赞：0)

其实简单。

首先找到一个以黑色格子为中心的最小正方形（也就是黑色格子），然后分类讨论上下左右四种情况，发现刚好对应四种题目给的 L 型。

然后就做完了。

## 代码如下：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
int p1 = 1 , p2 = 2 , x , y , n , tmpx , tmpy , tmp , cnt , now;
inline void Up(){
    x += tmp + 1;
    y = tmpy;
    y -= tmp + 1;
    while(x <= n && y){
        now++;
        printf("%lld %lld -%lld %lld\n" , x , y , x - 1 , x - 1);
        x++;
        y--;
    }
    x = n;
    y = n;
    while(now < cnt){
        printf("%lld %lld -%lld -%lld\n" , x , y , x - 1 , x - 1);
        x--;
        y--;
        now++;
    }
}
inline void Down(){
	x -= tmp + 1;
    y = tmpy;
    y -= tmp + 1;
    while(x && y){
        now++;
        printf("%lld %lld %lld %lld\n" , x , y , n - x , n - x);
        x --;
        y --;
    }
    x = 1;
    y = n;
    while(now < cnt){
        printf("%lld %lld %lld -%lld\n" , x , y , y - 1 , y - 1);
        x++;
        y--;
        now++;
    }
}
inline void Left(){
    x -= tmp + 1;
    y = tmpy;
    y += tmp + 1;
    while(x && y <= n){
        now++;
        printf("%lld %lld %lld -%lld\n" , x , y , y - 1 , y - 1);
        x--;
        y++;
    }
    x = n;
    y = n;
    while(now < cnt){
        printf("%lld %lld -%lld -%lld\n" , x , y , y - 1 , y - 1);
        x--;
        y--;
        now++;
    }
}
inline void Right(){
    x -= tmp + 1;
    y = tmpy;
    y -= tmp + 1;
    while(x && y){
        now++;
        printf("%lld %lld %lld %lld\n" , x , y , n - y , n - y);
        x--;
        y--;
    }
    x = n;
    y = 1;
    while(now < cnt){
        printf("%lld %lld -%lld %lld\n" , x , y , x - 1 , x - 1);
        x--;
        y++;
        now++;
    }
}
signed main(){
	cin >> n >> tmpx >> tmpy;
	tmp = min(min(tmpx - 1 , tmpy - 1) , min(n - tmpx , n - tmpy));
    puts("Yes");
	cnt = n - 1;
	cout << cnt << endl;
    x = tmpx;
    y = tmpy;
	for(int i = 1;i <= tmp;i++){
        printf("%lld %lld -%lld -%lld\n" , x + i , y + i , p1 , p2);
        printf("%lld %lld %lld %lld\n" , x - i , y - i , p1 , p2);
		p1 += 2;
		p2 += 2;
	}
	cnt -= tmp * 2;
	if(tmpx - tmp == 1){ 
		Up();
	}
	else if(tmpy + tmp == n){
		Right();
	}
	else if(tmpx + tmp == n){
        Down();
	}
	else{
		Left();
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

这题放在倒数第二题偏易了。

我们可以画图理解：

![](https://cdn.luogu.com.cn/upload/image_hosting/vwt3vgjf.png)

我们可以发现，我们每次操作就相当于在给黑色格子外一直添加 L 形的物体，然后，它不管怎么加这个 L，它有且一定有解是可以变成正方形的。

知道了这个，我们下面就很好实现了。

我们可以创建 $4$ 个边界 $s$、$x$、$z$、$y$，然后进行分类讨论。

如果 $s$ 大于 $1$ 并且 $z$ 小于 $1$，说明我们是可以形成一个反过来的 L 的。

如果 $s$ 大于 $1$ 并且 $y$ 小于 $n$，说明我们是可以形成一个正过来的 L 的。

如果 $z$ 大于 $1$ 并且 $x$ 小于 $n$，说明我们是可以形成一个倒过来并且是反着的 L 的。

如果 $z$ 大于 $1$ 并且 $y$ 小于 $n$，说明我们是可以形成一个倒过来的 L 的。

那么按照题意模拟就行了。

代码也十分简单，就不放出来了。

---

## 作者：SakurajiamaMai (赞：0)

## **思路:**
从黑色格子开始，每次循环都向外包一层，如果其四面边界有一面是空的，那么就在那个方向包一层 L，同时更新边界范围。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
int n,i,j;
signed main() {
    std::cin>>n>>i>>j;
    int u=i,d=i,l=j,r=j;//分别为上下左右
    std::cout<<"Yes"<<endl;
    std::cout<<n-1<<endl;
    for (int k = 1; k < n; k++) {
        if (u>1&&l>1){
            u--; l--;
            printf("%d %d %d %d\n",u,l,d-u,r-l);
        }
        else if(u>1&&r<n){
            u--; r++;
            printf("%d %d %d %d\n",u,r,d-u,l-r);
        } 
        else if(d<n&&l>1){
           d++; l--;
            printf("%d %d %d %d\n",d,l,u-d,r-l);
        } 
        else{
            d++; r++;
            printf("%d %d %d %d\n",d,r,u-d,l-r);
        }
    }
    return 0;
}
```


---

## 作者：Milthm (赞：0)

## P9567 题解

~~刚开始被吓到了，想了个三十多种情况的分类讨论，后来发现根本没必要。~~

### 前置知识

- 模拟

### 题目解法

首先，你会发现这题解法十分开放，没有太多的要求。所以我们想到了一种情况没有那么多的简单方法：

![](https://cdn.luogu.com.cn/upload/image_hosting/g7nm2u8d.png)

（图画的不太好，见谅）

就像这样，我们螺旋的把黑格子包围起来，如果碰到边缘就不放这个方向的。很容易发现，因为格子是正方形，这么放不可能放不下（要空着也是还有一边空着，所以还可以放），也是一定可以放满的。

所以维护四个变量，对应上、下、左、右的位置，循环判断即可。

至于操作次数吗，因为每次操作行会增加一个，列也会增加一个，又因为有一个黑格子，所以是 $n-1$ 次。

### AC 代码

```cpp
#include<iostream> 
using namespace std;
int n,sx,sy;
int main(){
	cin>>n>>sx>>sy;
	int u=sx,l=sy,d=sx,r=sy;//上下左右
	cout<<"Yes\n"<<n-1<<'\n';//记得输出 Yes
	for(int i=1;i<n;++i){
		if(u>1&&r<n){
			--u;++r;
			cout<<u<<" "<<r<<" "<<d-u<<" "<<l-r<<'\n';//按照题意输出 L 形的坐标，下面同理
		}
		else if(u>1&&l>1){
			--u;--l;
			cout<<u<<" "<<l<<" "<<d-u<<" "<<r-l<<'\n';
		}
		else if(d<n&&l>1){
			++d;--l;
			cout<<d<<" "<<l<<" "<<u-d<<" "<<r-l<<'\n';
		}
		else{
			++d;++r;
			cout<<d<<" "<<r<<" "<<u-d<<" "<<l-r<<'\n';
		}
	}
    return 0;
}

```


---

