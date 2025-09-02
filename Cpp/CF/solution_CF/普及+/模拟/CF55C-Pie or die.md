# Pie or die

## 题目描述

Volodya and Vlad play the following game. There are $ k $ pies at the cells of $ n×m $ board. Each turn Volodya moves one pie to the neighbouring (by side) cell. If the pie lies at the border of the board then Volodya can move it outside the board, get the pie and win. After Volodya's move, Vlad bans some edge at the border of the board of length 1 (between two knots of the board) so that Volodya is not able to move the pie outside the board through this edge anymore. The question is: will Volodya win this game? We suppose both players follow the optimal strategy.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF55C/31b302de1bb09a87c0444ab4f4b5165ba7e60f5d.png)

## 样例 #1

### 输入

```
2 2 1
1 2
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 4 0
```

### 输出

```
NO```

## 样例 #3

### 输入

```
100 50 2
50 25
50 25
```

### 输出

```
NO```

# 题解

## 作者：WinterRain208 (赞：7)

CF55C 【Pie or die】

博弈论好题

### 题目让窝们干什么

模拟两个人对弈的过程，并判断先手 是否有必胜策略。

题目有几个重点。

开始时有$n*n$的棋盘 和$k$个棋子（派）在上面，玩家是一个先手一个后手 。

先手每步移动一个棋子（任意），四联通移动。就是：

| N | Y | N |
| -----------: | -----------: | -----------: |
| Y | * | Y |
| N | Y | N |

后手选择棋盘边缘一个方块的一条边堵住，先手不能从这里通过。

如果先手能将任意一个棋子移动到棋盘之外，先手胜，反之后手胜利。

他们都绝顶聪明。

### 首先理解几个事实：

如果一个派已经在边缘上，如果它出去的那格没有挡住，那么一定要挡住。

如果一个派已经在角落里，且两个出口未被挡住，那么就赢了。

### 接下来模拟对弈的过程：

先手会选择一个离边界最近的派往边界移动。

这期间如果派还没到边缘，那后手会填补角落方块的两个出口之一，直到派到达边界。

一旦到达边界，后手会填补对应的出口，然后先手沿着边界移动到还没有被填补的角落。

这期间后手必须跟着先手的步伐填补当前先手所在位置的出口。

这个时候，如果先手能找到一个还没有填补的角落位置，先手必胜。

### 继续考虑：

每个边缘位置只需要填补两个出口之一即可，这样可以将其转化为普通边缘格子。

后手在先手到达边缘之前可以填补多少角落格子？是先手的派到边缘的距离。

众所周知，一个长方形棋盘最多只有四个角落，也就是长方形的四个角。

所以如果后手有足够的时间填补这四个角落后手就能赢。

即，先手离边缘最近的派与边界的距离大于4。反过来可以得到先手的胜利条件。

### 分析完毕，来考虑怎么做。

这很简单，读入一个派的坐标，计算它到边缘的距离，如果小于等于4就判胜利，如果一直没有判胜利就判失败。

这题解决了，代码也写出来了，放一下（即使楼上楼下苣佬已经放过了

### 代码

```cpp
#include<bits/stdc++.h>
#define F(i,j,r) for(int i=j;i<=r;++i)

using namespace std;

int n,m,k;
int x,y,flag=1;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	F(i,1,k){
		scanf("%d%d",&x,&y);
		if(x-1<=4||y-1<=4||4>=n-x||4>=m-y)
			flag=0;
	}
	puts(flag?"NO":"YES");
    return 0;
}

```

遇到这种题，可以拿样例自己试试找规律或者纸笔分析一波。其实很简单就出来了。

~~最喜欢这种紫题~~

注释就不写了，解释过了，如果有漏洞欢迎指出。

$wtrl$

---

## 作者：abensyl (赞：4)

原题：[CF55C Pie or die](https://www.luogu.com.cn/problem/CF55C)

## 思路

简要地说题意就是如果派被 Volodya 推下桌边并没有被 Vlad 挡住，则 Volodya 胜利。

由于两人都是是绝顶聪明的，所以如果派被推到桌子边， Vlad 一定会把桌子的边上的那一格挡住，这样 Volodya 就不能把派推出去。

也就是说，只有在派被推到了桌子的角落上并且两个临边都没有被 Vlad 提前挡住时 Vlad 是挡不住的。

![](https://cdn.luogu.com.cn/upload/image_hosting/pqao1mg0.png)

（此时，Vlad不论堵哪里，都会被推下桌）

我们定义有威胁为派被推到桌边，不得不被封堵时。

如图所示，而当派在角里时，是最有威胁的如图所示。

Volodya 为了赢，会尽可能的给 Vlad 制造威胁，所以他会尽可能地把派往角上推。

所以，只要有一个派到达桌子的一条边上，Volodya 就会一直把派沿着桌子边推，让 Vlad 忙于堵截，没有空余的步数来堵截桌子的四个角落，这样当 Volodya 将派推到一个两条临边都没有被堵上的角落里， Volodya 就赢了。

因此只要派到达桌子的一条边上， Volodya 就会一直把派沿着桌子边推，就可以给 Vlad 造成威胁。

所以他一开始就会尽可能将距离桌子最近的那个派推到桌边。

但是 Vlad 会选择在一开始就堵住桌子的四个角，所以Volodya 只有 $4$ 步机会将派推到桌子边上。

所以我们只需要比较一下离桌子的边最近的一个派与桌边间的距离（设为 $S$ ）和 $4$ 的大小就行了，如果 $S \leq 4$，那么 Volodya 获胜，否则 Vlad 获胜。

则判断条件为：

```
(x-1<=4||y-1<=4||4>=n-x||4>=m-y)
```

## 代码（本人蒟蒻）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,y;
bool flag;
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        scanf("%d%d",&x,&y);
        if(x-1<=4||y-1<=4||4>=n-x||4>=m-y){
            flag=0;// Volodya 获胜
            puts("YES");
            return 0;// 直接结束，不再进行判断，省时间
        }
    }
    puts("NO");// Vlad 获胜
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/83238092)

---

## 作者：COsm0s (赞：2)

## 题目大意

有 $k$ 个棋子，在 $n×m$ 的棋盘上，每次先手可以移动棋子（四联通）。一个棋子移到边界，且这条边界没有被设上挡板时，先手就获得胜利，否则每次先手移动完，后手都可以在边界任意位置放上挡板。

## 思路

博弈论。

从题目可提取一条关键信息：**如果一个棋子已经在角落里，且两个出口未被挡住，则先手胜。**

根据这条信息，我们可以将题目转化：

+ 满足某个条件，使棋子走到边界前，**四个角落都有至少一块挡板**。

当每个角落都至少有一块挡板时，角落就变成了普通边界（只有一个出口），那在棋子来到边界时，只需要将当前边界的唯一出口堵死，那棋子就永远无法出去。

那让后手堵住四个角落的条件是什么呢？

注意，后手放一块挡板所用一个单位时间，而先手走一步也需要一个单位时间。因为总共有四个角落，所以后手要花四个单位时间。

所以，只要先手在四个单位时间内无法到边界（即离边界超过四格），即判负。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}	
signed main(){
	int n = read(), m = read(), k = read();
	while(k --) {
		int x = read(), y = read();
		if(x < 6 || y < 6 || n - x < 5 || m - y < 5) 
			puts("YES"), exit(0);
	}
	puts("NO");
	return 0;
}

```


---

## 作者：喵仔牛奶 (赞：1)

## $\mathcal{S}olution$

题意：让你向四周移动一个棋子，每次你移动都会有人把一个边界封掉，超越边界就赢了。求是否有必胜策略。

显然，你如果到达了非边角的边上，它可以一直堵你：

[![zx3kPf.md.png](https://s1.ax1x.com/2022/12/26/zx3kPf.md.png)](https://imgse.com/i/zx3kPf)

（如图，黄色的是角落）

你就只能一直走，走到角落。角落你可以往两个方向走，他就不能堵死你了。

[![zx3Vxg.md.png](https://s1.ax1x.com/2022/12/26/zx3Vxg.md.png)](https://imgse.com/i/zx3Vxg)

可是对方不傻，在你没有到边界的时候会偷偷把角落堵上。如果四个角落都堵上了，你就输了。

但是如果你在他把四个角落都堵上前到达边界，他就不能继续堵角落，你可以沿边界到没有被堵角落，就赢了。

[![zx3ERS.png](https://s1.ax1x.com/2022/12/26/zx3ERS.png)](https://imgse.com/i/zx3ERS)

所以，判断能否在四次操作内到达边界即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, x, y;
int main() {
	cin >> n >> m >> k;
	while (k --) {
		cin >> x >> y;
		if (x <= 5 || y <= 5 || n - x <= 4 || m - y <= 4)
			puts("YES"), exit(0);
	}
	puts("NO");
	return 0;
}

```


---

## 作者：activeO (赞：1)

## 题目大意

就是有 $ k $ 个棋子，在 $ n \times m $ 的棋盘上，每次先手可以移动棋子上下左右，当有一个棋子移到边界时，并且这条边界没有被设上挡板，先手就可以把它移除边界，并获得胜利，否则每次先手移动完，后手都可以在任意位置放上挡板。

## 思路

首先可以很轻松可以发现：**如果一个棋子在别的棋子移动后可以取得胜利，那么这个棋子刚开局时就能取胜**，因为有别的棋子在这枚棋子之前动，边界就会多挡板，然而这时这枚棋子还能赢，在开局没挡板的时候也能赢。所以实际上我们只用考虑每个棋子能不能开局获胜就行了。

接着考虑一个棋子能获胜的条件是什么，首先发现：每次棋子移动后，后手都可以在这枚棋子的移动方向上放上挡板，所以**唯独棋子到达没有挡板的角落上可以获胜**。如果在棋子到达边界之前 $ 4 $ 个角落没有被当上一条边，棋子就可以在边界迫使后手在他所在的边界上放挡板，然后一路沿着边界到达那个没有放挡板的角落然后取胜。所以结论：**棋子到达边界之前每角落必须被挡上一条边**，后手才能取胜。

~~而就是这么道题，我交了 $ 3 $ 遍~~

## 代码

这就很简单了，照着意思来。

```cpp
#include <bits/stdc++.h>

using namespace std;

int main(){
	
	int n,m,k;
	
	scanf("%d %d %d",&n,&m,&k);
	
	for(int i=1;i<=k;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		if(x==n||x==1||y==m||y==1){
			puts("YES");
			return 0;
		}
		if((n-x+1<=5||m-y+1<=5)||(x<=5||y<=5)){
			puts("YES");
			return 0;
		}
	}
	
	puts("NO");
	
	return 0;
}
/*
........
........
........
........
........
....#...
........
........
........
........

*/
```

update:当时打的代码有点凌乱

---

## 作者：ADivT (赞：1)

这是一道有意思的题，可以看得出来是博弈，代码实现很简单，主要是思路：

首先，(我理解的）Volodya移动肯定是先到达离他最近的边，然后再向角落里逃逸，当到达角落时，**可以有两个方向出去**，但是对手只能挡住一边，这样不就赢了吗？

由此，易得AC代码：
```cpp
#include <bits/stdc++.h>

#define rep(i,o,p) for(register int i=o;i<=p;++i)

int n,m,k,x,y,ans=0;

int main() {

	scanf("%d%d%d",&n,&m,&k);
	rep(i,1,k) {
		scanf("%d%d",&x,&y);
		ans=(x>=n-4||x<=5||y>=m-4 ||y<=5)?1:ans
	}
	printf(ans?"YES":"NO");
	return 0;
}
```

---

## 作者：Mint_Flipped (赞：0)

感觉这道题不应该是紫题，思路就是乱搞，没人证明，我来证明一下。

假设我们有一个棋盘，点在中心，离四个边界的位置都是N。

我们走出第一步，对面为了不让我们赢，必拦我们走的那个方向，为了赢，我们可以再走一步，对面会拦上面或者下面的一个点。（拦上面的点，走下面，反之，即可）

距离为4是一个分界点，我们往右使用上面的这个操作，然后再走一步，我们离边界距离只有2步，但挡板比我们领先一个身位，再往下走，一直走到底下，这时如果我们再往右走，路被封死了，往左走必赢。

距离为5这个点，我们继续上面那个过程，我们离边界距离有3步，但挡板比我们领先一个身位，再走，就是两个身位，无论我们怎么走，必输，往下走也是这个情况。

代码如下：
```c
#include <map>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
#define mem(a,b) memset(a,b,sizeof(a))
#define fo1(a,b) for(int a=0;a<b;++a)
#define fo2(a,b) for(int a=1;a<=b;++a)
#define lowbit(a) (a&(-a))
#define fir(a) a->first 
#define sec(a) a->second 
const int inf=0x3f3f3f3f;
const int maxn=1e6+5;
const int mod=2008;
const double eps=1e-6;
int main()
{
    int n,m,k,x,y;
    bool flag=0;
    scanf("%d%d%d",&n,&m,&k);
    fo2(i,k){
        scanf("%d%d",&x,&y);
        if(x<=5||y<=5||n-x<=4||m-y<=4)
        flag=1;
    }
    flag==1?puts("YES"):puts("NO");
    return 0;
}
```


---

## 作者：OHYEP (赞：0)

这题仔细想想，看看规律

当棋子走到角落的时候，有两个出口，这就可以出去了

所以另一个人一开始就要给每个角落封上一个，

所以就是一个棋子到棋盘边缘的距离小于5时，那就没办法封完

那就获胜了

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int n,m,q,xx=99999,yy=99999;
	cin>>n>>m>>q;
	for(int i=1;i<=q;i++)
	{
		int x,y;
		cin>>x>>y;
		xx=min(xx,min(x-1,n-x));
		yy=min(yy,min(y-1,m-y));
	}
	if(min(xx,yy)<=4) printf("YES");
	else printf("NO");
	return 0;
}
```


---

