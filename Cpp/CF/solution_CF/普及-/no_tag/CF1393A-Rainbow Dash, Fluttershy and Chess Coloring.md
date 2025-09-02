# Rainbow Dash, Fluttershy and Chess Coloring

## 题目描述

One evening Rainbow Dash and Fluttershy have come up with a game. Since the ponies are friends, they have decided not to compete in the game but to pursue a common goal.

The game starts on a square flat grid, which initially has the outline borders built up. Rainbow Dash and Fluttershy have flat square blocks with size $ 1\times1 $ , Rainbow Dash has an infinite amount of light blue blocks, Fluttershy has an infinite amount of yellow blocks.

The blocks are placed according to the following rule: each newly placed block must touch the built on the previous turns figure by a side (note that the outline borders of the grid are built initially). At each turn, one pony can place any number of blocks of her color according to the game rules.

Rainbow and Fluttershy have found out that they can build patterns on the grid of the game that way. They have decided to start with something simple, so they made up their mind to place the blocks to form a chess coloring. Rainbow Dash is well-known for her speed, so she is interested in the minimum number of turns she and Fluttershy need to do to get a chess coloring, covering the whole grid with blocks. Please help her find that number!

Since the ponies can play many times on different boards, Rainbow Dash asks you to find the minimum numbers of turns for several grids of the games.

The chess coloring in two colors is the one in which each square is neighbor by side only with squares of different colors.

## 说明/提示

For $ 3\times3 $ grid ponies can make two following moves: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1393A/e700c5c9ebb73cd50fb6689a87a04ee305695b19.png)

## 样例 #1

### 输入

```
2
3
4```

### 输出

```
2
3```

# 题解

## 作者：shabiisshabi (赞：2)

# 思路
根据题意不难看出，第一次填涂必须要涂最外围的格子，那么，要想填涂的格子最多，并且没有相邻同色，最优的方法就是外围格子隔一个涂一个涂，之后的每一圈都填上一圈的空再重复第一步。

所以，最优的方法就相当于第一次隔一个涂一个涂完之后，每次都涂没有涂的最外围一圈，也就是**一圈一圈的往里缩，求一共缩的圈数**。

接下来我们分类讨论：
1. $n$ 为偶数：每次往里缩一圈，所以一共缩了 $\lfloor\frac{n}{2}\rfloor$ 圈，但要注意最后还会漏下两个格子，所以次数还要加一,即为 $\lfloor\frac{n}{2}\rfloor+1$ 次。
2. $n$ 为奇数：同理，每次缩一圈，缩了 $\lfloor\frac{n}{2}\rfloor$ 圈后还会剩下中心及中心右上，右下左上，左下五个格子，所以次数仍然要加一，即为 $\lfloor\frac{n}{2}\rfloor+1$ 次。

现在，我们总结出来最终的公式，就是 $\lfloor\frac{n}{2}\rfloor+1$，每次输入 $n$ 之后调用此公式即可。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int x;
		scanf("%d",&x);
		printf("%d\n",x/2+1);
	} 
	return 0;
}
```

---

## 作者：saixingzhe (赞：2)

# 题意
每次填涂颜色必须在已经填涂颜色的方块旁边填涂。特别地，我们认为所有在矩阵边缘的方块是周围已经有被填涂的方块的。

对于第 $i$ 次填涂：$i$ 是奇数：填涂的颜色是亮蓝色。$i$ 是偶数：填涂的颜色是黄色。

给定 $n$，求最小的填涂次数，将空白的 $n×n$ 矩阵填涂成国际象棋棋盘状。

定义：国际象棋棋盘状是指所有方块都被填涂，并且没有两个有相邻边的方块颜色相同。

**一次可以涂很多个格子，只要这个格子周围有被填涂的格子即可。**
# 分析
一眼题，很明显最优解一定是从外边一圈一圈往里缩，可以证明因为每次只能从外往里涂，一次把所有目前能涂的格子涂满，一定比一次不涂满要优。

结论出来了，算式就好写了，因为我们是一圈一圈往里缩的，所以要缩 $n \div 2$ 次，但如果 $n$ 是偶数，就要多缩一次，所以最后的结果是 $n \div 2+1$。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        cout<<n/2+1<<endl;
    }
    return 0;
}
```

---

## 作者：45dinо (赞：2)

说句闲话：好像这不是CF第一次和动画片联动了，以前好像有一次小猪佩奇。（好奇有没有获得版权）

发现最优的情况如下：

1. A 把边上隔一个填一个。
1. B 把边上填满，便乘一个 $(n-2)\times (n-2)$ 的方格纸，把边上隔一个填一个。
1. A 把边上填满，便乘一个 $(n-4)\times (n-4)$ 的方格纸 $\cdots$

所以就看 n 的奇偶性，如果 n 是偶数，最后就是一个 $2\times 2$ 的方格纸，就是 $\frac n 2+1$ 。如果 n 是奇数，就是 $\frac {n+1} 2$ 。

所以答案可以写成 $\frac n 2+1$ （找规律比推公式快多了系列）

---

## 作者：159号程序员 (赞：2)

$update$ 20200810 证明部分增加更详细的解释。

作为一名忠实的马迷，这道题也不能错过了。

简单模拟，也可以打表。

首先我们来研究样例：

$$n = 3, ans = 2$$
$$n = 4, ans = 3$$

然后继续构造数据：

$$n = 5, ans = 3$$
$$n = 6, ans = 4$$
$$n = 7, ans = 4$$
$$n = 8, ans = 5$$
$$n = 9, ans = 5$$
$$n = 10, ans = 6$$
$$\dots\dots$$

可以轻松地找出规律：$ans = n \div 2 + 1$。

但是别急，证明一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/sge4y35p.png)
可以看出，不管 $n$ 是奇是偶，填色时都是一圈一圈往里缩的，所以要缩 $\left\lceil\dfrac{n}{2}\right\rceil$ 次，但当 $n$ 是偶数，就会多缩一次（如上图），证明我们的公式是对的。

这样就可以简单地切这道题了：

_AC Code_ 

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T, n;
    cin >> T;
    while(T--)
    {
        cin >> n;
        cout << n / 2 + 1 << endl; //利用公式，注意换行
    }
    return 0;
}
```
${\color{white}\text{连云宝和柔柔都会的数学题，你还不会吗？}}$

---

## 作者：__Dist__ (赞：1)

### 题目描述

给定 $ T $ 组测试数据，对于每组数据，给定一个 $ n $，要你填涂一个 $ n \times n $ 的矩阵。对于第 $ i $ 次填涂，若 $ i $ 是奇数，则填涂亮蓝色；否则填涂黄色。问最少多少次填涂后矩阵变成国际象棋棋盘的样子（任意一个格子与上、下、左、右的格子的颜色都不同，而它上、下、左、右的格子颜色均相同）。

### 思路讲解
~~dfs？~~

~~看错了。~~

其实这是一道规律题，画画图，推一下。

下面是我的思考过程：

 $ n=1 $ 时，需要 $ 1 $ 次；
 
 $ n=2 $ 时，需要 $ 2 $ 次；
  
 $ n=3 $ 时，需要 $ 2 $ 次；
   
 $ n=4 $ 时，需要 $ 3 $ 次；
   
 $ n=5 $ 时，需要 $ 3 $ 次；
  
  规律已经显而易见了。矩阵边长是 $ n $ 时，共需要 $ \frac {n}{2}+1 $ 次。
  
### 代码环节

```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<iomanip>
#include<cstdio>
#include<stack>
#include<queue>
#include<map>
#include<vector>
using namespace std;
int T;
int n;
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		cout<<n/2+1<<endl;
	}
	return 0;
}
```


---

## 作者：KSToki (赞：1)

~~这道题作为 CF 的 A 题是不是难了点。~~

首先明确，什么颜色先涂是无所谓的。我们不妨先推一下 $n=1$、$2$、$3$ 时的，显然答案为 $1$、$2$、$2$。这个时候我们来看一看 $n=4$（你可以试着画个图）我们发现，当 $n=4$ 走了两步后，相当于 $n=2$ 时走了一步。你可以试着再推一下 $n=5$ 时，你会发现 $n=5$ 时走两步相当于 $n=3$ 时走一步。

到这里代码就很简单了，大可以忽略这个快读：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		    flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		cout<<n/2+1<<endl;
	}
	return 0;
}
```


---

## 作者：luosw (赞：1)

### 题意简述

- 给定一个 $n\times n$ 的棋盘；

- 两个玩家依次放置棋子：

	- 对于每一次放置，必须要有棋子（或者墙壁）挨着；
    
    - 最后需要得到国际象棋的摆法。
    
- 求摆完棋盘的最小回合数。

> The chess coloring in two colors is the one in which each square is neighbor by side only with squares of different colors.

翻译过来就是：

> 两种颜色的国际象棋着色是其中每个正方形仅与不同颜色的正方形并排相邻的颜色。

好了，现在已经明确题意了，我们来看数据范围。

> $1≤n≤10^9$

这样算下来，如果说按照二维数组用贪心算法来做，那么这种算法的时间复杂度为 $O(n^2)$ ，还需要加各种特判，况且有多组数据输入输出，这样会超时。

怎么样能不超时呢？

我们来**找规律**。

### 题目分析

首先，从最简单的开始，$1\times1$ 的棋盘，非常明显，$1$ 次即可完成。

然后是 $2\times 2$：

![a4hV7q.png](https://s1.ax1x.com/2020/08/08/a4hV7q.png)

$2$ 次完成。

从题目给出的两个样例可以知道，$3\times3$ 需要 $2$ 次完成，$4\times4$ 需要 $3$ 次完成。

已经列举了 $4$ 个了，我们至少要发现针对每一个 $n\times n$ 棋盘要是其最小填充的规律。

我们发现，$n$ 的奇偶性决定了我们的第一次填充。

不妨进行分类讨论：

$n ≡ 0 (\bmod{2}) $ 时，第一次填充时，应该在四个面每一个面填充 $\dfrac{n}{2}$ 个面，加上重复，第一次就应该填涂 $4\times \dfrac{n}{2}-2=2n-2$ 个面,然后我们依次遍历每一个已经填涂的小正方形，依次在它的上下左右填涂上另一种颜色的颜料。如果它挨着墙壁，那么忽略掉墙壁面，想它有的周围的其它面依次填充即可。

在讨论 $n$ 是偶数的过程中，我们知道了最优解的规则：

> 依次遍历每一个已经填涂的小正方形，依次在它的上下左右填涂上另一种颜色的颜料。如果它挨着墙壁，那么忽略掉墙壁面，想它有的周围的其它面依次填充即可。

同理，当 $n$ 是奇数的时候，先进行第一次填充，这个时候应该优先填充中间的面才能使最终更多。然后按照上面的规则填充即可。

这样的话，我们依次枚举，就会得到一个表格：

|$n$|次数|
|:----:|:----:|
|$1$|$1$|
|$2$|$2$|
|$3$|$2$|
|$4$|$3$|
|$5$|$3$|
|$6$|$4$|
|$7$|$4$|
|$8$|$5$|
|$9$|$5$|
|$...$|$...$|

发现除了 $n=1$ 需要特判外，其他的:

$$\texttt{次数}=\lfloor{\dfrac{n}{2}}\rfloor+1$$

我们已经得到公式了！

下面就是代码环节：

### 代码

```cpp
#include<bits/stdc++.h>
int t,tmp;
using namespace std;
int main(){
	cin>>t;
	for(int i=0;i<t;i++){
		cin>>tmp;
		if(tmp==1)	cout<<"1\n";
		else{
        	cout<<floor(n/2)+1<<endl;
        }
	}
    return 0;
} 

---

## 作者：Yizhixiaoyun (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1393A)

## 题目分析

本题我们可以先推一下规律。

$$n=3 , ans=2$$ 

$$n=4 , ans=3$$

$$n=5 , ans=3$$

$$n=5 , ans=3$$

$$n=6 , ans=4$$

$$...$$

我们便可以推出公式： $ans = n ÷ 2 + 1$

我们画个图就会发现，当 $n = 4$ 时走两步，相当于 $n = 2$ 时走一步，而当 $n = 5$ 时走两步，相当于 $n = 3$ 时走一步，以此类推，我们推出的公式正确。

## 贴上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		n=n/2+1;
		cout<<n<<endl;
	}
}
```

---

## 作者：Steve_xh (赞：0)

# 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1393A)

**题目大意：**

给定一个 $n\times n$ 的棋盘对于第 $i$ 次填涂，规定：

- 如果 $i$ 是奇数就填蓝色，偶数则填黄色。

- 不能有同个颜色是相邻的。

- 每次填必须在一个已有格子的旁边。

- 每次可以有多个且相同颜色的格子被填涂。

- 棋盘最边上的格子可以填。

问最少用多少次填涂就能将这个棋盘填满。

# 思路

我们先来看一下最优解法。先也只能先填最外圈，每相邻一个格子填一个，这时我们可以说我们已经把最外层给“缩”掉了，如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/d9an5w74.png)
接着我们只能换一种颜色，把剩下边上的格子填完，顺便将再里面一圈的位置隔一个放一个，如下图。
![](https://cdn.luogu.com.cn/upload/image_hosting/0sb5num1.png)
以此类推，我们就能把所有的格子“缩”掉而填满棋盘。

那么具体要多少次呢？当然就是缩的圈数啦！当 $n$ 是奇数时，答案是从最中间开始往一边一直往外延申再加上最中间的那块，也就是 $(n+1)\div 2$。当 $n$ 是偶数时，最后一定会剩下一个 $2\times2$ 的方格，而这种情况下无论怎样都要填 $2$ 次，所以还要将圈数加一，就是 $n\div2+1$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    scanf("%d",&n);
    for(int i=1,t;i<=n;i++){
        scanf("%d",&t);
        printf("%d",(t&1)?(t+1)/2:t/2+1);//套公式
    }
    return 0;
}
```

---

## 作者：_VEGETABLE_OIer_xlc (赞：0)

画图找规律：

$n=1$，$ans=1$。

$n=2$，$ans=2$。

$n=3$，$ans=2$。

$n=4$，$ans=3$。

$n=5$，$ans=3$。

不难发现，$ans=\frac{n}{2}+1$。

为什么呢？

如果边长是奇数，那么最优方案是两圈两圈整体往里缩，满足上面结论。

如果边长是偶数，那么最优方案是从右上角两圈两圈缩，也满足上面结论。

这样我们就证明上面的公式是对的。

记得要换行。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	cin>>t;
	while(t--)
	{
		cin>>n;
		cout<<n/2+1<<endl;
	}
	return 0;
}


```

---

## 作者：引领天下 (赞：0)

题意实际上就是要求你将一个 $n\times n$ 的方格图全部填成交替的 $0,1$ ，问最少需要多少次，但每次填的数都必须与之前的已经填上的数至少有一条公共边。

咋一看似乎不太好做，但仔细一想这个填数的过程实际上就是**一圈一圈**地从外向内填数。

具体过程如下：

填好最外面半圈→换一种颜色填好靠内一圈，同时补上刚才一圈空下的空→……→填好最靠内的半圈。

经过对较小的几个数据的观察，可以发现规律如下：

- 当 $n$ 为偶数的时候，填好之前的所有圈共需要 $\frac{n}{2}$ 次，再加上最后一圈一次，共计 $\frac{n}{2}+1$ 次。

- 当 $n$ 为奇数的时候，最后一圈实际上就是最中间的一个点，故答案就是填好之前的圈所需要的次数，即 $\frac{n+1}{2}$ 次。

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
    int t,n;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        printf("%d\n",n&1?(n+1)>>1:(n>>1)+1);
    }
    return 0;
}
```

---

## 作者：loceaner (赞：0)

## 思路

> 给定一个$n\times n$的方阵，每个格子上可以放两种颜色，每次只能在已经填好色的方格的四周（上下左右）填色，求使这个方阵变成颜色相间的棋盘的最小操作数。

一道结论题。

手推一下可以发现:

1. 当$n$为奇数时，$n+2$的情况是$n$的情况的次数加$1$
2. $n+1$的情况不会超过$n+2$的情况

又因为:

- $n=1$时摆放的次数为$1$，
- $n=2,3$时摆放的次数为$2$，
- $n=4,5$时摆放的次数为$3$……

由此可以大胆的猜测答案就是$\dfrac{\lfloor n+2\rfloor}{2}$，交上去测一发，发现的确是对的，在代码里即为$n/2+1$

那么我们就要想了，**为什么是这样的呢？**

其实就是因为在$n$的状态下进行一次摆放，尽可能摆放最多棋子的情况下，得到的就是$n-2$的情况下未摆放时的状态

以此类推，一直到$n=1,2$的情况，就可以一步步再倒着推回去了，这样的话这道题就做完了，最后给出代码。

## 代码

```cpp
/*
Author:loceaner
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

inline int read() {
  char c = getchar();
  int x = 0, f = 1;
  for ( ; !isdigit(c); c = getchar()) if (c == '-') f = -1;
  for ( ; isdigit(c); c = getchar()) x = x * 10 + (c ^ 48);
  return x * f;
}

int main() {
  int T = read();
  while (T--) {
    int n = read();
    cout << n / 2 + 1 << '\n';
  }
}
```

---

## 作者：huayucaiji (赞：0)

这个题很简单，我们可以画几张图，发现每一次我们染色的最佳方法就是每次往里面多填一圈，并把上一圈给填满。

![](https://espresso.codeforces.com/d847e618f3087a23400280c5f2bee399134a4718.png)

比如上图就很好地说明了这个过程，大家可以用画一下 $n=4,n=5,n=6,n=7$，就能验证这个命题了，所以一个 $n\times n$ 的矩阵有 $\lfloor\frac{n}{2}\rfloor+1$ 圈，所以直接输出即可。

```cpp
//Don't act like a loser.
//You can only use the code for studying or finding mistakes
//Or,you'll be punished by Sakyamuni!!!
//#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
//#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
#include<bits/stdc++.h>
#define int long long
using namespace std;

int read() {
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9') {
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return f*x;
}

int n;

signed main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	
	int t=read();
	while(t--) {
		n=read();
		
		cout<<n/2+1<<endl;
	}

	//fclose(stdin);
	//fclose(stdout);
	return 0;
}


```

---

