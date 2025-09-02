# Flatland Fencing

## 题目描述

The King of Flatland will organize a knights' tournament! The winner will get half the kingdom and the favor of the princess of legendary beauty and wisdom. The final test of the applicants' courage and strength will be a fencing tournament. The tournament is held by the following rules: the participants fight one on one, the winner (or rather, the survivor) transfers to the next round.

Before the battle both participants stand at the specified points on the $ Ox $ axis with integer coordinates. Then they make moves in turn. The first participant moves first, naturally. During a move, the first participant can transfer from the point $ x $ to any integer point of the interval \[ $ x+a $ ; $ x+b $ \]. The second participant can transfer during a move to any integer point of the interval \[ $ x-b $ ; $ x-a $ \]. That is, the options for the players' moves are symmetric (note that the numbers $ a $ and $ b $ are not required to be positive, and if $ a<=0<=b $ , then staying in one place is a correct move). At any time the participants can be located arbitrarily relative to each other, that is, it is allowed to "jump" over the enemy in any direction. A participant wins if he uses his move to transfer to the point where his opponent is.

Of course, the princess has already chosen a husband and now she wants to make her sweetheart win the tournament. He has already reached the tournament finals and he is facing the last battle. The princess asks the tournament manager to arrange the tournament finalists in such a way that her sweetheart wins the tournament, considering that both players play optimally. However, the initial location of the participants has already been announced, and we can only pull some strings and determine which participant will be first and which one will be second. But how do we know which participant can secure the victory? Alas, the princess is not learned in the military affairs... Therefore, she asks you to determine how the battle will end considering that both opponents play optimally. Also, if the first player wins, your task is to determine his winning move.

## 说明/提示

In the first sample the first player can win in one move.

In the second sample the first participant must go to point $ 1 $ , where the second participant immediately goes and wins.

In the third sample changing the position isn't profitable to either participant, so nobody wins.

## 样例 #1

### 输入

```
0 2 0 4
```

### 输出

```
FIRST
2
```

## 样例 #2

### 输入

```
0 2 1 1
```

### 输出

```
SECOND
```

## 样例 #3

### 输入

```
0 2 0 1
```

### 输出

```
DRAW
```

# 题解

## 作者：first_fan (赞：1)

```cpp

题意翻译（略长，请耐心看完）

一个独木桥上甲乙二人在玩传送游戏，其规则如下：

1.开始时，甲乙二人分别位于x1,x2处，且甲先手。

2.根据给定的参数a,b，二人可以在桥上传送：每一回合中，假定甲乙现在坐标为x1,x2，那么甲可以传送到[x1+a,x1+b]这一区间内的任一点上，而乙则可以传送到[x2-b,x2-a]上的任一点上，传送时允许跨越对手所在点（毕竟是传送）。

3.胜利的条件：在本方传送后成功到达对手所在点(把对手挤下桥)。

现问：在双方都足够聪明的情况下，谁会胜利？

----

输出格式：

若甲胜利，输出“FIRST”，并在下一行指出此时甲第一步应该传送到的坐标。

若乙胜利，输出“SECOND”。

若比赛无法结束，输出“DRAW”。（注意：仅甲胜利时需要输出第二行。）

-----

数据：
输入仅一行四个整数：x1,x2,a,b。上述量均在[-1e9,1e9]范围内，且保证a≤b

* 特殊地，当a,b异号时，呆在原地不动也是合法操作。
```

题目描述在暗示a,b的符号性很重要，我们就以此分类：

### *此处设dis为二人初始位置差，即x2-x1

* a,b均正

1.甲乙只能背向前进，根本无法相遇，平局。(dis<0)

2.甲乙相向而行，判断甲能获胜的条件：dis%(a+b)∈[a,b]。

>这种情况下，最终一步始终由甲来完成。甲第一步要到`x2-(dis*(a+b))*(a+b)`处，乙就无法逃脱。

3.甲乙相向而行，乙能获胜的情况仅有一种：dis%(a+b)=0

>这种情况下，乙会恰好完成最后一步从而扼杀甲的下一步。

* a负b正

>这种条件下是可以呆在原地的，甲必须一发制敌，否则一定会陷入平局。

1.一发制敌，直接传送到x2处

2.无法到达x2，进入平局。

* a,b均负

>这种情况比较巧妙，我们考虑把桥倒过来，a,b再取绝对值并易位一下（因为-b≤-a），就可以调用第一种情况的结论了。

讨论完了，上代码：

```cpp
#include <bits/stdc++.h>
#define ri register int
#define ll long long
using namespace std;

int read()
{
	int num=0;
	int flg=1;
	char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
		{
			flg=-1;
		}
		c=getchar();
	}
	while(isdigit(c))
	{
		num=(num<<1)+(num<<3)+(c^48);
		c=getchar();
	}
	return num*flg;
}

int dire=1;//记录桥方向是否倒转
int main()
{
	int x1=read();
	int x2=read();
	int dis=x2-x1;
	int a=read();
	int b=read();
	if(a<=0&&b<=0)//均负
	{
		swap(a,b);
		a=-a;
		b=-b;
		dis=-dis;
		dire=-dire;//反向
	}
	if(a<=0)//异号
	{
		if(a<=dis&&dis<=b)
		{
			puts("FIRST");
			return 0&printf("%d",x2);
		}
		else//甲不能一发制敌
		{
			return 0&(int)puts("DRAW");
		}
	}
	//两种情况：
	//1.本来就均正
	//2.翻转后均正
	if(dis<0)//南辕北辙
	{
		return 0&(int)puts("DRAW");
	}
	else if(dis%(a+b)==0)
	{
		return 0&(int)puts("SECOND");
	}
	else if(a<=dis%(a+b)&&dis%(a+b)<=b)//甲胜
	{
		puts("FIRST");
		return 0&printf("%d",x2-dire*(dis/(a+b))*(a+b));//方向得用上。
	}
	else//平局
	{
		return 0&(int)puts("DRAW");
	}
}
```

规律其实可以由搜索得到，感兴趣的读者可以亲手试试找规律的过程。

---

## 作者：MadokaKaname (赞：0)

不用 SG 函数的博弈论，你值得拥有。

似乎题解都写的很粗略，我来篇详细点的。

### 前置芝士：[Bash博弈](https://baike.baidu.com/item/%E5%B7%B4%E4%BB%80%E5%8D%9A%E5%BC%88/1819345)

我们先观察题目所给的条件，为两个点和转移区间。

注意到 $x$ 并不严格小于 $y$，在这种情况下将 $x$ 和 $y$ 交换一下，$a$ 和 $b$ 交换后取反即可。

现在 $x$ 严格小于 $y$ 了，发现可以划分成以下三种情况：

- $a$ 和 $b$ 都是负数

显然是平局，原因不用我多说了吧。

- $a$ 和 $b$ 都是正数

此时这个问题可转化为有一堆个数为 $y-x$ 个的石子，双方轮流取，至少取 $a$ 个，至多取 $b$ 个，先取完者胜。

显然是 Bash 博弈的变种。

我们用 Bash 博弈的套路去思考：

下面用 $n$ 替代 $y-x$，用 $m$ 替代 $a+b$。

如果 $n \bmod m \equiv0 $，则后手必胜；

否则分成两种情况：

1. $x \le n \bmod m \le y$，显然先手取 $n \bmod m$ 必胜；


2. $0<n \bmod m < x$ 或 $y < n \bmod m $，可以发现一定可以不移到第一种区间内。先手一定不必胜，因为无论先手怎么走，后手都可以粘着先手将 $m$ 补满以形成平局；后手也一定不必胜，反证法，假设后手必胜，则先手必败，根据[策梅洛定理](https://baike.baidu.com/item/%E7%AD%96%E6%A2%85%E6%B4%9B%E5%AE%9A%E7%90%86/10511540)，先手转移的所有状态都必定是必胜态，而显然不转移到第二种区间内时并不转移到必胜态，矛盾。则在此情况下只能是平局。

- $a$ 是负数，$b$ 是非负数

如果一步能挤掉就直接一步挤掉。

否则显然必定是和局。证明就不贴了。

~~为什么不加多测呢~~

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,i,j,k,m;
int a,b,x,y;
int main() {
    scanf("%d%d%d%d",&x,&y,&a,&b);
    
	bool flag=false;
	if(x>y){
		swap(x,y);
		swap(a,b);
		a=-a;
		b=-b;
		flag=true;
	}
	if(a<=0){
		if(x+b>=y){
		    printf("FIRST\n");
			if(flag==false) printf("%d",y);
			else printf("%d",x);
		}
    	else printf("DRAW");
    	return 0;
	}
	int sum=y-x;
	if((sum%(a+b))==0){
		printf("SECOND");
	}
	else if(sum%(a+b)>=a && sum%(a+b)<=b){
		printf("FIRST\n");
		if(flag==true){
			printf("%d",y-sum%(a+b));
		}
		else{
			printf("%d",x+sum%(a+b));
		}
	}
	else printf("DRAW");
	return 0;
}

```


---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
尝试用 $\text{SG}$ 函数硬推，感觉有点玄乎，有问题还请指出。

---
### 解题思路：

首先转化问题。其实 $x_1$ 和 $x_2$ 到底是多少并不重要，真正重要的是 $x_2-x_1$，也就是两者之间的位移，注意这是有符号的，不妨设 $d=x_2-x_1$。

每一次操作，无论是先手玩家还是后手玩家，都是从 $d$ 中减去任意一个 $x\in[a,b]$。

那么就根据这个构建一个 $\text{SG}$ 函数，不妨设这个函数为 $g_i$，表示 $d=i$ 的时候的情况。显然有：$g_0=0$。但如果只是这样似乎不太好设计平局的情况，尝试做出一点改动：令$g_x=-1$ 其中 $x<0$，定义 $-1$ 出现且仅出现在 $\text{MEX}(a)$，$a$ 是一个集合，且这个集合中存在 $-1$ 且不存在 $0$，可以这样理解，如果 $0$ 会尽量取 $0$，让自己得到胜利，否则只能退而求其次，也就是找平局。

然后每一个人能取到的范围是 $[i-a,i-b]$，也就是说 $g_i=\text{MEX}(g_{x})$，其中 $x\in[i-a,i-b]$。

---
此时发现，如果 $a$ 和 $b$ 异号，会出现环，似乎不太好处理，不妨直接特殊地考虑一下。

在这种情况下每一个人都是可以选择停留在原地的，那么如果某一个距离 $d$ 在一个玩家看来能够获胜，在另一个玩家看了也一定能够获胜，只是取决于谁先手。

所以要不然就是玩家一一开始就能获胜，要不然就是平局。

---
然后就能正常地推导下去了，最后可以得到：

$\begin{matrix}\underbrace{-1,\cdots,-1}\\<0\end{matrix}\ 0 \ \begin{matrix}\underbrace{-1,\cdots,-1}\\(0,a-1]\end{matrix}\  \begin{matrix}\underbrace{1,\cdots,1}\\ [a,b] \end{matrix}  \ \begin{matrix}\underbrace{-1,\cdots,-1}\\ (b,a+b) \end{matrix} \ 0 \cdots$

接下来又是这样的循环（注意上面范围的开闭），每一个循环节的长度为 $a+b$，所以直接取模然后对应位置即可，当为 $0$ 的时候即为后手必胜，$-1$ 平局，$1$ 先手必胜。

如果 $a$ 和 $b$ 都是负的，同样满足以上的规律，不过循环的方向是向左，不太好理解。

但是可以发现，如果将两者的符号都取反，并将两者的位置交换，也就得到了和之前类似的结果，可能会简单一点。

---
最后还要求输出第一步的移动情况，如果是 $a,b$ 异号的情况，那么直接移动到对应的位置就好了，否则的话需要移动到上面对应 $0$ 的位置就行了。

注意符号取反的时候移动的位位移也要取反，而且输出的是坐标。

---
### 代码：

```cpp
#include<cstdio>
using namespace std;
int x,y,a,b,d,swap=1;
int main(){
	scanf("%d%d%d%d",&x,&y,&a,&b);
	d=y-x;
	if(a<0&&b<0){a=-a;b=-b;d=-d;swap=-1;}
	if((a<=d&&d<=b)||(b<=d&&d<=a)){
		printf("FIRST\n");
		printf("%d\n",x+swap*d);
		return 0;
	}
	if((a<=0&&b>=0)||(a>=0&&b<=0)){
		printf("DRAW\n");
		return 0;
	}
	if(d<0){
		printf("DRAW\n");
		return 0;
	}
	d%=(a+b);
	if((a<=d&&d<=b)||(b<=d&&d<=a)){
		printf("FIRST\n");
		printf("%d\n",x+swap*d);
		return 0;
	}
	if(d==0){
		printf("SECOND\n");
		return 0;
	}
	printf("DRAW\n");
	return 0;
}
```




---

