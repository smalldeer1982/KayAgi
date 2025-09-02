# Chip Game

## 题目描述

Burenka and Tonya are playing an old Buryat game with a chip on a board of $ n \times m $ cells.

At the beginning of the game, the chip is located in the lower left corner of the board. In one move, the player can move the chip to the right or up by any odd number of cells (but you cannot move the chip both to the right and up in one move). The one who cannot make a move loses.

Burenka makes the first move, the players take turns. Burenka really wants to win the game, but she is too lazy to come up with a strategy, so you are invited to solve the difficult task of finding it. Name the winner of the game (it is believed that Burenka and Tonya are masters of playing with chips, so they always move in the optimal way).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1719A/a6c823a6eb354fdb9ffdf07a308c103419371a6a.png)Chip's starting cell is green, the only cell from which chip can't move is red. if the chip is in the yellow cell, then blue cells are all options to move the chip in one move.

## 说明/提示

In the first case, Burenka has no move, so Tonya wins.

In the second case, Burenka can move $ 3 $ cells to the right, after which Tony will not be able to make a move, which means that Burenka wins.

In the third case, Burenka can move $ 5 $ squares to the right. Then we can say that we have a game on a board of $ 1 \times 5 $ cells, and Tonya is the first player. In such game the second player wins, so in the original one Burenka will win.

## 样例 #1

### 输入

```
6
1 1
1 4
5 6
2 2
6 3
999999999 1000000000```

### 输出

```
Tonya
Burenka
Burenka
Tonya
Burenka
Burenka```

# 题解

## 作者：D2T1 (赞：6)

## A. Chip Game

div2A 放这种题？

设先手一步、后手一步为一轮。那么每一轮，$x$ 坐标的增加值和 $y$ 坐标的增加值都是偶数（奇数 $+$ 奇数 $=$ 偶数）。而起点的坐标为 $(1,1)$，二数相加也是偶数。所以每一轮结束后的坐标 $x+y$ 必定为偶数。所以若 $n,m$ 奇偶不同，显然先手必胜。

否则后手有必胜策略，即使接下来的棋盘为正方形，然后仿照先手的走法换个方向走。

```cpp
#define multiple_test_cases
 
int n, m;
 
void solve(){
	n = rdi;
	m = rdi;
	if((n - m) & 1){
		puts("Burenka");
	} else {
		puts("Tonya");
	}
}
```

---

## 作者：zajasi (赞：5)

**题面传送门**

[题面](https://www.luogu.com.cn/problem/CF1719A)

**题意**

Burenka 和 Tonya 在做游戏。每一次一个人可以移动奇数步。 Burenka 先走，问谁能先从 $(1,1)$ 到 $(n,m)$ 。

**解题思路**

可以首先用 [曼哈顿距离](https://blog.csdn.net/qq_40723205/article/details/102669605) 算出 $(1,1)$ 到 $(n,m)$ 的距离。考虑到每个人每次只能走奇数步。也就是说 Burenka 走完后总步数是奇数，Tonya 走完后是偶数。所以我们只需要判断一下总步数的奇偶性就可以了。

**AC代码**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
int a,b;
main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>a>>b;
		int s=abs(a-1)+abs(b-1);
		if(s&1){
			cout<<"Burenka\n";
		}
		else{
			cout<<"Tonya\n";
		}
	}
	return 0;
}


```

---

## 作者：Epi4any (赞：4)

很好的一道博弈论题。
~~（但凡学过小奥应该都能秒）~~

思路如下：
1. 对矩阵进行**棋盘染色**：
2. 每一次一个人走一步都会让棋子走进与当前位置颜色不同的一个格子，没有例外。
3. 因为胜者是把棋子走入最后一个格子中的人，所以假如左下角的颜色和结尾相同，那么 Tony 赢，反之亦然。

具体实现见代码：
```cpp
#include <iostream>
#include <cstdio>
using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}

int n, m, t;

int main() {
	t = read();
	while (t--) {
		n = read(), m = read();
		if ((n & 1) && (m & 1) || !(n & 1) && !(m & 1)) cout << "Tonya" << endl;
		else cout << "Burenka" << endl;
	}
	return 0;
}
//皆为警告：理解思路 杜绝抄袭
```

---

## 作者：Jeremiahy (赞：4)

## 分析

在二维网格上判断是否必胜要分 $n,m$ 是奇偶数的情况，太复杂了。我们把它做一个转化，转化为一维的。长度为 $n+m$。

这样做正确的原因是在二维网格上只能向上或向右走，一次走一格一共能走 $n+m-2$ 次，由于它与 $n+m$ 的奇偶性是相同的，所以可以转化为一维。

当 $n+m$ 为奇数时， ```Burenka``` 可以一步走完，他胜；当 $n+m$ 为偶数时，```Burenka``` 无法一次走完，而下一次 ```Tonya``` 可以一次走完，故 ```Tonya``` 胜。

#### 代码

```cpp
#include<cstdio>
int n, m, t;
signed main() {
	scanf("%d", &t);
	while (t--)
		scanf("%d%d", &n, &m), puts(((n + m) % 2) ? "Burenka" : "Tonya");
    return 0;
}
```


---

## 作者：_FJX_ (赞：3)

这是一道数学规律题:

我们要想明白每一轮，$x$ 坐标的增加值和 $y$ 坐标的增加值都是偶数（奇数 $+$ 奇数 $=$ 偶数）。

所以我们在分两种情况讨论：若 $n,m$ 奇偶不同，显然先手必胜 ; 不然就是后手胜。

_AC code:_

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void work()
{
    int n, m;
    cin >> n >> m;
    if((n - m) & 1)
    {
		cout << "Burenka\n";
	}
    else 
    {
		cout << "Tonya\n";
	}
}
int main(){
    ios_base::sync_with_stdio(false);
	cin.tie (0);
	cout.tie (0);
    int T;
    cin >> T;
    while (T --)
    {
        work();
    }
	return 0;
}
```


---

## 作者：Dry_ice (赞：3)

[cnblogs浏览](https://www.cnblogs.com/dry-ice/p/cf1719a.html)

> 代码短吧。

## Description
一个大小 $n \times m$ 的棋盘，你要从左下角走到右上角。

每步可以选择向上或向右走任意奇数步，不可走出棋盘，问 $\text{Burenka}$ 先走，能否获胜。

## Analysis
> 博弈类游戏题。作为 A 题，可以找规律。

### Easy version
先不考虑二维，只考虑**一维问题**，走一条长度为 $n$ 的**线段**谁能获胜。

既然提到了**奇数**，显然会想到通过奇偶性去解决问题：两人共需走的长度为 $n$。 $\text{Burenka}$ 每次移动后，二人移动总长度为奇数；$\text{Tonya}$ 每次移动后，二人移动总长度为偶数。获胜条件是某人**走最后一步**到达 $n$。

故若 $n$ 为奇数，则 $\text{Burenka}$ 会走最后一步并获胜；反之，若 $n$ 为偶数，则必然是 $\text{Tonya}$ 走最后一步并获胜。

### Hard version
一维问题考虑清楚后，现在再考虑二维。

如何解决二维问题？由于只能向右或向上移动，所以可以进行**降维**：不考虑何时转弯，二人需要移动的总长度总为 $n + m$，因为**不能走回头路**。

即转化为线性（一维）问题：走一条长度为 $n + m$ 的线段谁能获胜。

## Code
思路想通，代码极其简短。

```cpp
#include <stdio.h>
int n, m;
int main(void) {
    int t; for (scanf("%d", &t); t--; ) {
        scanf("%d %d", &n, &m);
        if (n + m & 1) puts("Burenka"); //判奇偶
        else puts("Tonya");
    }
    return 0;
}
```

## The end. Thanks.

~~（一键三连~~

---

## 作者：RE_Prince (赞：2)

# CF1719A Chip Game

[link](https://www.luogu.com.cn/problem/CF1719A)

题意：两个人在一个 $n\times m$ 的棋盘上玩游戏，石子初始在 $(1,1)$，每次可以把石子向下或向右移动奇数个格子，问谁能把棋子移到终点。

其实 @_zyINF 已经把思路说的比较清楚了，就是判断 $n$ 和 $m$ 是否奇偶性相同。

原因就是每次的增量是奇数，而两人移动过一轮棋子后增量的和就变成了偶数。因此移动过一轮的棋子的坐标相加也是偶数。

所以问题就变为了判断给出的两个数奇偶性相不相同。

完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define rg register int
using namespace std;
int n, m;
signed main()
{
	int T;
	cin >> T;
	while (T--)
	{
		cin >> n >> m;
		if ((n & 1) != (m & 1)) cout << "Burenka\n";
		else cout << "Tonya\n";
	}
	return 0;
}
```

## 加强

这里给出一个加强版：

两个人挪石子，给出一个起点，每次能向下或向右移动奇数格棋子，最终到达 $(n,m)$ 的人获胜。请编写程序来判断先手胜还是后手胜。

输入：

四个数，$n,m,x,y$，分别表示终点坐标和起点坐标。

输出：

如果先手胜，输出 $1$，否则输出 $2$。

## Sol


我们在上一道题中之所以只用判断 $n,m$ 奇偶性相同，就是因为起点的 $(1,1)$ 的和就是偶数。现在题目要求输入起点了，我们就要对起点做出奇偶性的判断了。剩下的和上一道题一样。

代码不放了，有兴趣的同学可以自己试试写一写。

---

## 作者：Fly_AFO (赞：2)

如果两个数中一个为奇数，另一个为偶数，则先手必胜，因为先手会先向一边走到顶，然后后手只能走奇数个格子，而先手则可以直接到达终点。

如果两个数都为奇数或偶数，则上述结论正好颠倒。

所以，只要两个数都是奇数或偶数，后手胜；反之，先手胜。

主要代码如下：
```cpp
if(a%2==b%2)
	cout<<"Tonya"<<endl;
else
	cout<<"Burenka"<<endl;
```

---

## 作者：Dregen_Yor (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1719A)。

# 思路

当其中一个人不能动的时候，这个人一定位于点 $(n,m)$ 上。令点 $(n,m)$ 为终点。

当 $n$ 和 $m$ 都是奇数或当 $n$ 和 $m$ 都是偶数时，赢的人一定会是 Tonya。

原因很简单。当 $n$ 和 $m$ 都是偶数时，因为 Burenka 先手，奇数 $+$ 奇数 $=$ 偶数。所以最早抵达终点的人一定是 Tonya。当 Tonya 抵达终点后 Burenka 就无法移动了，故 Tonya 胜。

当 $n$ 和 $m$ 都是奇数时，假设他们的路线为先一直向右再一直向上，类比都是偶数的情况，第一个到达最右边的一定是 Burenka，到达右边界之后 Tonya 先走，这时最先到达上边界的人就变成了 Tonya，也就是终点，这时 Burenka 无法移动，故 Tonya 胜。

当 $n$ 和 $m$ 中只有一个数是奇数的时候，类比上面的两种走法，不同的是此时最先到达终点的人变成了 Burenka，这时 Burenka 获胜。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, m;

int main() {
	scanf("%d", &t);

	while (t--) {
		scanf("%d%d", &n, &m);
		int p = 0;

		if (n & 1) {
			p++;
		}

		if (m & 1) {
			p++;
		}

		if (p == 1) {
			puts("Burenka");
		} else {
			puts("Tonya");
		}
	}

	return 0;
}

```


---

## 作者：Moyyer_suiy (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1719A)

## 题意概况
极其水的一道数学题哈。

一个行为 $n$ 列为 $m$ 的方格矩阵，从左下角开始，每次可以**往上或往右走奇数格**。Burenka 先开始走格子。最后无法移动格子的人失败。
## 解决思路
由于每次只可以往上或往右走，那么题目中所说的**最后无法移动格子**，可以理解为**另一方已经到达了矩阵的右上角**，此时就不能够向上或向右移动了。

由此，我们可以将题意简化为，Burenka 先从点 $(1,1)$ 出发，每次可以向上或向右走奇数格，先到达点 $(n,m)$ 者胜利。

考虑情况 $n\bmod2=1$ 且 $m\bmod2=1$ 或 $n\bmod2=0$ 且 $m\bmod2=0$。此时横纵坐标都是奇数，或都是偶数。

因为奇数 $+$ 奇数 $=$ 偶数，奇数 $+$ 偶数 $=$ 奇数，所以此时 Tonya 后一步出发，一定能先到达点 $(n,m)$。此时 Tonya 胜利。反之同理。

## 贴代码

```cpp
#include<iostream>
using namespace std;
int t,a,b;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		if(a%2==0&&b%2==0||a%2==1&&b%2==1) puts("Tonya");
		else puts("Burenka");
	}
}
```

---

## 作者：zhicheng (赞：0)

### 思路

我们注意到，假设一个人走了 $a (a \ge 3)$ 步，那么其实就相当于这个人走了 $1$ 步后，另一个人走了 $a-2$ 步，这个人再走了 $1$ 步。以此类推，所有的走步都可以分成一步一步走，那么再来考虑，当 $m+n$ 是偶数时，一定是后手（Tonya）赢，否则就是先手（Burenka）赢。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,a,b;
	scanf("%lld",&n);
	while(n--){
		scanf("%lld%lld",&a,&b);
		if((a+b)%2){  
			printf("Burenka\n");
		}
		else{
			printf("Tonya\n");
		}
	}
}
```

---

## 作者：ttq012 (赞：0)

A:

任何的一个奇数长度的距离都需要走奇数次，任何一个偶数长度的距离都需要走偶数次。

只需要判断横坐标的值和纵坐标的值是否都是奇数或者都是偶数即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

signed main() {
  int T;
  cin >> T;
  while (T --) {
    int a, b;
    cin >> a >> b;
    if (a % 2 == b % 2)
      cout << "Tonya\n";
    else
      cout << "Burenka\n";
  }
  return 0;
}

```

---

## 作者：Scorilon (赞：0)

因为每次只能向上或向右走奇数步，所以若 $n$ 或 $m$ 里面只有一个是偶数，即一奇一偶，那么是 $\text{Burenka}$ 胜，反之，均奇或均偶则 $\text{Tonya}$ 胜。

因为棋盘是一奇一偶，所以 $\text{Burenka}$ 第一步先往格子数为偶数的那个方向走格子数减一格，接下来 $\text{Tonya}$ 就只可以走一格，那么 $\text{Burenka}$ 再走奇数格即可胜。

举个例子，若 $n=3,m=4$，那么 $\text{Burenka}$ 先向右走 $m-1=3$ 格，接下来 $\text{Tonya}$ 就只可以走 $1$ 格，$\text{Burenka}$ 再走 $n=3$ 格，$\text{Burenka}$ 胜。

反之，若均偶或均奇，则在最后一步时 $Bureanka$ 无法走 $n$ 格，那么 $Tonya$ 胜。

```cpp
#include <cstdio>
#include <iostream>

using namespace std;

int t,n,m;

int main() {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		if(n%2==0) {
			if(m%2==1) puts("Burenka");
			else puts("Tonya");
		}
		else {
			if(m%2==0) puts("Burenka");
			else puts("Tonya");
		}
	}
	return 0;
} 
```


---

## 作者：うっせぇわ (赞：0)

### 解法

这道题其实跟矩阵没什么关系，我们可以直接把这个矩阵转化成一个 $m+n-1$ 长度的序列，可以将在 $1$ 处的棋子向前移动奇数格，谁先到达 $m+n-1$ 的格子谁赢。

这样问题就得到了转化：将整数 $m+n-1$ 分成若干个奇数相加。

我们知道，偶数个奇数相加一定是偶数，奇数个奇数相加一定是奇数，所以，当 $m+n-1$ 可以被 $2$ 整除时，先手 `Burenka` 胜利；反之亦然。

```
#include <iostream>
using namespace std;
int m,n;
int t;
int main(){
	cin>>t;
	while(t--){
		cin>>m>>n;
		if((m+n-1)%2==0)cout<<"Burenka\n";
		else cout<<"Tonya\n";
	}
	return 0;
}
```

---

## 作者：IYSY2009I (赞：0)

一个很显然的点是，一定存在一种方案，使一方恰好走到右上角。我们可以构造出一种每次只走一步的方案。

我们知道，从 $(1,1)$ 走到 $(n,m)$，需要向上走 $n-1$ 步，向右走 $m-1$ 步，所以总共需要走 $n+m-2$ 步，因为每次走奇数步，所以每次走一段路，走的总路程的奇偶性就会改变。由此我们可以得出结论：如果 $n+m-2$ 为偶数，则 $\texttt{Tonya}$ 走到右上角，$\texttt{Burenka}$ 无处可走，反之 $\texttt{Burenka}$ 走到右上角，$\texttt{Tonya}$ 无处可走。

代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<1)+(x<<3)+c-'0';
		c=getchar();
	}
	return x*f;
}
void cf(){
	int n=read(),m=read();
	if((n+m-2)&1) printf("Burenka\n");
	else printf("Tonya\n");
	return;
}
int main(){
    int t=read();
    for(int i=1;i<=t;i++)
		cf();
	return 0;
}
```
讲个笑话：这道题我一开始以为套 $\texttt{Nim}$ 取石子问题就可以了，卡了 $20min$……

---

## 作者：Hiro_Akiba (赞：0)

其实题意就是让你输出第一个到右上角的人的名字。

我就直接分析吧。

~~这道题好像和另一个oj的比赛题重了？~~

## 分析

只能走奇数格，所以当棋盘边长的格子数都是奇数时，后走的人先赢。

这是图示：
![](https://cdn.luogu.com.cn/upload/image_hosting/iym0qh9l.png)

其中，蓝色表示先手，红色为后手。

当棋盘边长为一奇一偶时，我们可以割掉一列格子，使其边长格子数都为奇数，所以此时先走的人赢。

这是图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ezrgbywq.png)

无论怎样的一奇一偶，我们直接把它放躺算就行了。


当棋盘边长都是偶数时，割掉一行，形成一奇一偶的形式，再用一奇一偶的结论，但由于割掉了一横行，我们就加在最上面，所以在一奇一偶的结论上多了一格，所以另一个人赢。

这是图示：

![](https://cdn.luogu.com.cn/upload/image_hosting/itll8k8e.png)

所以我们就能把代码轻松写出来了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    while(n--){
    	int x,y;
    	cin>>x>>y;
    	if(x%2&&y%2){
    		cout<<"Tonya"<<endl;
		}
		else if(!x%2&&!y%2){
			cout<<"Tonya"<<endl;
		}
		else cout<<"Burenka"<<endl;
	}
	return 0;
}

```




---

## 作者：sandwave114514 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1719A)

题目大意

有一个 $n$ 行 $m$ 列的方格矩阵，左下角的方格有一个棋子，这个棋子每次移动**只能向上或向右移动奇数格**。`Burenka` 和 `Tonya` 用这个棋子玩一个游戏：两人依次移动一次棋子，最后没法移动棋子的人就输了。`Burenka`先手，给你 $n$ 和 $m$，问你谁最后会赢。他们每一步走棋方式都是最优的。

解题思路

通过看样例，我们可以发现 $n+m$ 是偶数，赢家是 `Tonya` ，$n+m$ 是奇数，赢家是 `Burenka` 。所以我们就判断 $n+m$ 的奇偶性就可以了

代码如下

```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0' || ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0' && ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
void write(long long n,bool p){
	if(n<0){putchar('-');n=-n;}
	if(n==0){if(p)putchar('0');return;}
	write(n/10,0);putchar(n%10+'0');
}//快输 
long long t,n,m,ans;
int main(){
    t=read();
    while(t--){
    	n=read();m=read();
    	ans=n+m;
    	if(ans%2==0)cout<<"Tonya"<<endl;//判断奇偶性 
    	else cout<<"Burenka"<<endl;
	}
	return 0;
}
```


---

## 作者：滑_稽 (赞：0)

[题目传送门](/problem/CF1719A)

因为游戏的最终目标是要让某一人无路可走，那么走到最后一步棋子（也就是那个chip）显然一定是在右上角那个格子的。下文将这个格子称为终点。

我们考虑任意一种从左下角走到右上角的路线，它一定是一个楼梯形的朝右上的折线，因为不可能往左或往下走。那么我们将这条折线分成若干条线段，一定可以将这些线段向下或向右平移到矩阵边界，使得平移后的路线呈一个“$\lrcorner$”的形状。也就是说，对于每一个给定的情况，我们都可以选择先向右走若干步到右下角，再向上走若干步到右上角。先水平走，再竖直走。这种走法与任意一种走法都是等价的，而且它形式最简单，所以我们就来研究这种走法。

题目中其实有提示（“Then we can say that we have a game on a board of $1\times5$ cells, and Tonya is the first player.”），这种走法实际上可以分解成两个子问题分别研究，一部分是水平的路，一部分是竖直的路。这样我们只需研究当行数为 $1$ 时二人的胜负情况就行了。

1. 行数为 $1$，列数为偶数时，先手一定赢，因为他可以一步走到终点。

2. 行数为 $1$，列数为奇数时，后手一定赢，因为先手不能一步到位，只能先走奇数步，之后问题就转化为列数为偶数时的情况，本来的后手现在变成了先手，所以后手赢。

将这两条规律连起来运用到上文中的“$\lrcorner$”形走法，我们可以发现，**当 $n$ 与 $m$ 奇偶性相同时，总是后手赢；而当 $n$ 与 $m$ 奇偶性不同时，总是先手赢。** 这个结论不难想，那个水平的子问题里谁是赢家，谁在竖直的子问题里就是后手。水平的子问题里的终点就是竖直的子问题里的起点。

代码就不放了，相信有了结论写出来不算难事。

---

## 作者：cachejtt (赞：0)

## 题意
有一个 $n$ 行 $m$ 列的矩阵，初始左下角有一个棋子。小 B 和小 T 在做游戏。两个人交替移动棋子，小 B 先手。移动棋子的规则是，只能向右或向上移动奇数格。谁先无法移动就输了，请输出胜者。假设两人都很聪明，都是按最优方式去移动。

## 思路
考虑 $n$ 与 $m$ 的奇偶关系。

![图示](https://cdn.luogu.com.cn/upload/image_hosting/vtzul084.png)

若 $n\bmod 2=0$，则在横向上，一共需要走奇数步，也就是说，需要移动奇数次。若 $n\bmod 2=1$，则一共需要走偶数步，也就是说，需要移动偶数次。

若 $m\bmod 2=0$，则在纵向上，一共需要走奇数步，也就是说，需要移动奇数次。若 $m\bmod 2=1$，则一共需要走偶数步，也就是说，需要移动偶数次。

因此，若 $n$ 与 $m$ 同奇偶，则一共需要走偶数步。为什么是偶数呢？因为**奇加奇等于偶**（当 $n,m$ 均为偶数），或**偶加偶等于偶**（当 $n,m$ 均为奇数）。

同样，若 $n$ 与 $m$ 异奇偶，则一共需要走奇步。为什么是奇数呢？因为**奇加偶等于奇**。

## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define nrep(i, a, b) for (int i = (a); i >= (b); --i)
#define endl "\n"
using namespace std;
int t=1,n,m,k;
signed main(){
  ios::sync_with_stdio(0);
  cin>>t;
  rep(kk,1,t){
    cin>>n>>m;
    if(n%2==m%2)cout<<"Tonya"<<endl;
    else cout<<"Burenka"<<endl;
  }
  return 0;
}
```

---

## 作者：sw2022 (赞：0)

## 题意简析

给定一个 $n\times m$ 的矩形网格，棋子一开始在左下角格，每次只能往右或者往上移动奇数个格子，问按最优策略谁最后一定会获胜。

因为题目中说棋子只有在右上角格时才不能移动，所以棋子移动的路径一定是从左下角到右上角的曼哈顿距离，即 $n+m-1$。又因为奇数 $\times$ 奇数 $=$ 奇数，奇数 $\times$ 偶数 $=$ 偶数，而移动距离是由移动步数个奇数组成，所以我们只要判断 $n+m-1$ 的奇偶性就可以得到步数的奇偶性。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        printf((n+m)%2?"Burenka\n":"Tonya\n");//直接判断奇偶性
    }
    return 0;
}
```

---

## 作者：wzmzmhk (赞：0)

题目大意：给定一个 $n\times m$ 的棋盘，一个棋子，起点在左下角，每次可以向上或向右走一格，要求走到右上角。两个人轮流移动这颗棋子，谁走到终点谁就输，求出胜者。

小学的平移知识告诉我们：棋子移动路径的总长一定是 $n + m$，那么棋子就要移动 $n + m - 2$ 次。由于是两人轮流移动，因此，若 $n + m - 2$ 是奇数，那么先移动的人胜利，否则后移动的人胜利。

```cpp
if ((a + b) % 2) cout << "Burenka\n";
else cout << "Tonya\n";
```

---

## 作者：sgl654321 (赞：0)

### 题目大意
有两个人 A，B 在一个 $n\times m$ 的棋盘上玩游戏，每次只能向上或向右走奇数格。要从左下角走到右上角，请问谁有必胜策略。
### 解题思路
每次都只能向上或向右走，要从左下角走到右上角，可见两人走的总步数一定是 $n+m$。

因为都只能走奇数格，所以有如下的结论：

- 当 $n$ 为奇数， $m$ 为偶数时，第一个人可以先从左下角走到左上角，然后第二个人不论怎么走都走不到终点，而偶数 $-$ 奇数 $=$ 奇数，因此第一个人能赢。
- 当 $n,m$ 均为奇数时，第一个人不论怎么走都走不到左上角，然后第二个人可以**用第一种情况第一个人的策略**，赢得这个比赛。
- 当 $n$ 为偶数，$m$ 为奇数时，相当于把第一种情况**转一个方向**，所以第一个人能赢。
- 当 $n,m$ 均为偶数时，第二个人可以 **用第一个人第三种情况的策略**，赢得这个比赛。

所以总结后我们发现：

- 当 $n,m$ 奇偶不同时，即相加为一个奇数时，A 赢。
- 当 $n,m$ 奇偶相同时，即相加为一个偶数时，B 赢。

### 参考代码
注意本题有多组数据。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m;
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		if((n+m)%2==1)cout<<"Burenka"<<endl;
		else cout<<"Tonya"<<endl;
	}
	return 0;
}
 
```

---

## 作者：RoyWu1207 (赞：0)

题目说有一个 $n \times m$ 的矩阵，只能向上或向右移动？？？
 
一个 ~~**显然**~~ 的办法：直接把行进的路线看成一个 $n + m$ 长度的一行不就好了吗？？？

**思路：**

- 当 $n + m$ 为奇数，不管怎么走，先手方都会留给后手方一个奇数，先手方，卒！

- 当 $n + m$ 为偶数，~~如果 Burenka 有点脑子的话~~，她必定会留给后手方一个偶数，后手方怎么走都会给先手方留下一个奇数，于是……后手方，卒！

就这么简单~~~

#### **AC Code：**

```cpp
#include <iostream>

using namespace std;

int main() {
	int t; cin >> t;
	while (t--) {
		int a, b; cin >> a >> b;
		if ((a + b) % 2 == 0)
			cout << "Tonya" << endl;
		else
			cout << "Burenka" << endl;
	} return 0;
}
```


---

