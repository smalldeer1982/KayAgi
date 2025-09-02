# Help Shrek and Donkey 2

## 题目描述

Having learned (not without some help from the Codeforces participants) to play the card game from the previous round optimally, Shrek and Donkey (as you may remember, they too live now in the Kingdom of Far Far Away) have decided to quit the boring card games and play with toy soldiers.

The rules of the game are as follows: there is a battlefield, its size equals $ n×m $ squares, some squares contain the toy soldiers (the green ones belong to Shrek and the red ones belong to Donkey). Besides, each of the $ n $ lines of the area contains not more than two soldiers. During a move a players should select not less than $ 1 $ and not more than $ k $ soldiers belonging to him and make them either attack or retreat.

An attack is moving all of the selected soldiers along the lines on which they stand in the direction of an enemy soldier, if he is in this line. If this line doesn't have an enemy soldier, then the selected soldier on this line can move in any direction during the player's move. Each selected soldier has to move at least by one cell. Different soldiers can move by a different number of cells. During the attack the soldiers are not allowed to cross the cells where other soldiers stand (or stood immediately before the attack). It is also not allowed to go beyond the battlefield or finish the attack in the cells, where other soldiers stand (or stood immediately before attack).

A retreat is moving all of the selected soldiers along the lines on which they stand in the direction from an enemy soldier, if he is in this line. The other rules repeat the rules of the attack.

For example, let's suppose that the original battlefield had the form (here symbols "G" mark Shrek's green soldiers and symbols "R" mark Donkey's red ones):

  `-G-R-<br></br>-R-G-<br></br>` Let's suppose that $ k=2 $ and Shrek moves first. If he decides to attack, then after his move the battlefield can look like that:

  `--GR-     --GR-     -G-R-<br></br>-RG--     -R-G-     -RG--<br></br>` If in the previous example Shrek decides to retreat, then after his move the battlefield can look like that:

  `G--R-     G--R-     -G-R-<br></br>-R--G     -R-G-     -R--G<br></br>` On the other hand, the followings fields cannot result from Shrek's correct move:

  `G--R-     ---RG     --GR-<br></br>-RG--     -R-G-     GR---<br></br>` Shrek starts the game. To make a move means to attack or to retreat by the rules. A player who cannot make a move loses and his opponent is the winner. Determine the winner of the given toy soldier game if Shrek and Donkey continue to be under the yellow pills from the last rounds' problem. Thus, they always play optimally (that is, they try to win if it is possible, or finish the game in a draw, by ensuring that it lasts forever, if they cannot win).

## 样例 #1

### 输入

```
2 3 1
R-G
RG-
```

### 输出

```
First
```

## 样例 #2

### 输入

```
3 3 2
G-R
R-G
G-R
```

### 输出

```
Second
```

## 样例 #3

### 输入

```
2 3 1
-R-
-G-
```

### 输出

```
Draw
```

## 样例 #4

### 输入

```
2 5 2
-G-R-
-R-G-
```

### 输出

```
First
```

# 题解

## 作者：VenusM1nT (赞：3)

## 题意

 - 给定一个 $n\times m$ 的棋盘。棋盘中 `-` 代表空格，`G` 代表绿色棋子，`R` 代表红色棋子。每行至多有两个士兵。
 - 先手执绿棋。
 - 每个回合玩家可以选择 $1$ 到 $k$ 个棋子在当前行内向左或向右任意移动一次，但不能越过另一个棋子，也不能在不同行之间移动。
 - 若一方在移动后能使另一方无法移动，则获胜。  
 - 求最后谁获胜或平局。
 - $1\leq n,m,k\leq 100$。
 
~~抄袭了 xht 神仙的风格。~~  
![杏树表情3.png](https://i.loli.net/2020/10/26/uEirCVGf6WwOPdA.png)

---
## 解法

恶心的细节题。  
![卡维表情3.png](https://i.loli.net/2020/10/26/I1XHu47GQ5LvlWF.png)  
首先考虑特殊情况。可以发现当某一行内只有同色棋子，则持有这枚棋子的玩家处于不败态，因为在任何情况下这枚棋子都是可以移动的（除非这些棋子将整行塞满了）。当两名玩家均处于不败态时则平局，否则处于不败态的那个玩家必胜。  
然后考虑一般情况，对每行分别考虑，可以视作该行内有 **两棋子间空格数** 的棋子，共有 $n$ 堆石子，最终谁把石子取完谁获胜。  
先来考虑这个模型的正确性，当 A 取完之后，B 只能将棋子朝一个方向移动，此时 A 只需要穷追不舍，将棋子怼到 B 移动的棋子的脸上，则最终必然是 B 不能移动。  
然后就是怎么解决这个问题。这是一个经典的 $\textbf{Nim - K}$ 问题。结论是每一堆的同一位二进制加起来 $\bmod\ (k+1)$ **均**为 0，则先手必败，否则先手必胜。  
下面给出~~口胡~~证明。

---
### $\text{Proof}$

※ 下以“条件”代指“每一堆的同一位二进制加起来 $\bmod\ (k+1)$ 均为 0”。  
首先明确必败态。终态每堆都是 $0$，显然满足条件。  
若此时为先手必败态，先手可以对至多 $k$ 堆进行操作，使若干个位置不满足条件，此时后手可以通过一次操作改变先手改变的若干二进制位使其再次满足条件，因为不论先后手最多都是操作 $k$ 堆石子，所以这显然是可以做到的。  
若此时不是先手必败态，因为 $x \bmod\ (k+1)\leq k$，所以先手最多只需将 $k$ 个二进制位 $-1$ 就可以满足条件，最坏情况下这 $k$ 个位置分散于 $k$ 堆中，而先手最多操作 $k$ 堆，因此先手必然可以将当前状态操作为先手必败态，自己变为后手，因此不满足条件的必然是后手必败态。  

确实有点口胡，感性理解吧各位。  
![舞契约表情02.png](https://i.loli.net/2020/10/26/lXLU6GrKi4VO8QE.png)  
```cpp
#include<bits/stdc++.h>
#define N 100
#define reg register
#define inl inline
using namespace std;
int n,m,k,a[N+5];
char ch[N+5][N+5];
inl string Solve()
{
	for(reg int i=0;i<=8;i++)
	{
		reg int res=0;
		for(reg int j=1;j<=n;j++) res+=(a[j]>>i)&1;
		if(res%(k+1)) return "First";
	}
	return "Second";
}
int main()
{
	reg int Fg=0,Fr=0;
	scanf("%d %d %d",&n,&m,&k);
	for(reg int i=1;i<=n;i++)
	{
		scanf("%s",ch[i]+1);
		reg int G=0,R=0,sG=0,sR=0;
		for(reg int j=1;j<=m;j++)
		{
			if(ch[i][j]=='G') G=j,sG++;
			if(ch[i][j]=='R') R=j,sR++;
		}
		if(G && R) a[i]=abs(G-R)-1;
		Fg+=((!sR)&&sG&&(sG<m));
		Fr+=((!sG)&&sR&&(sR<m));
	}
	if(Fg && !Fr) return puts("First"),0;
	if(!Fg && Fr) return puts("Second"),0;
	if(Fg && Fr) return puts("Draw"),0;
	puts(&Solve()[0]);
	return 0;
}
```

---

## 作者：VinstaG173 (赞：1)

k-Nim 模板题（细节怪

首先我们发现对于一行，如果里面同时有红色和绿色棋子，那么根据规则，相当于两颗棋子之间的空格数为一堆石子，每次取出任意多颗。

然而还有可能在同一行里只有一种颜色甚至没有。

我们发现如果有空格，那么相当于这颗棋子的主人可以随意移动，当其他的他都不想移的时候，他可以在这里面为所欲为。

如果没空格，那么这行相当于是废的。

如果全是空的，没棋子，相当于也是废的。

于是把上面几个给处理一下，一堆特判后再上 k-Nim 就完了。

Code:
```cpp
#include<cstdio>
int n,m,k;
int ans[13];
char ch[107];
int tmp,vf,vs,vv,vt,flag=0;//vv 为一行对应的一堆的石子数，vt 为一行中的棋子数。
//tmp 表示目前的状态，体现当前格处于的位置是否在红绿之间，同时作判断棋子种类数用。
//vf 表示先手能移动的行数，vs 表示后手能移动的行数。
//flag 表示是否有同时有红有绿的行
int main()
{
	scanf(" %d %d %d",&n,&m,&k);++k;
	for(int i=0;i<n;++i)
	{
		scanf(" %s",ch);vv=vt=tmp=0;
		for(int i=0;i<m;++i)
		{
			if(ch[i]=='-')
			{
				if(tmp)++vv;
			}
			if(ch[i]=='G')++tmp,++vt;
			if(ch[i]=='R')--tmp,++vt;
		}
		if(tmp)//只有一种颜色
		{
			if(vt==m)continue;
			else if(tmp>0)++vf;
			else ++vs;
		}
		else
		{
			flag=1;
			if(vv)++vf,++vs;
			for(int i=0,j=1;vv;++i,j<<=1)
			{
				if(vv&j)
				{
					vv^=j,ans[i]=(ans[i]+1)%k;
				}
			}
		}
	}
	if(!vf)printf("Second\n");//先手不能动
	else if(!vs)printf("First\n");//后手不能动
	else if(!flag)printf("Draw\n");//两人能动的行都是自由移动的，平局
	else
	{
		flag=0;
		for(int i=0;i<13;++i)
		{
			if(ans[i])
			{
				flag=1;break;
			}
		}
		printf("%s\n",flag?"First":"Second");
	}
	return 0;
}
```

---

## 作者：rizynvu (赞：0)

[我的博客](https://www.cnblogs.com/rizynvu/p/18042829)。

提供一个严谨的 *Nim-K* 证明。

首先如果有一行只有 $\texttt{G}$ 或 $\texttt{R}$ 且其是可以移动的，那么这个对应的一方肯定不输。  
需要先把这个情况判掉。

那么剩下的行要么是不合法的（不可能在这一行进行操作的）要么就是有 $\texttt{RG}$ 的。  
不合法的显然不会影响博弈，可以去掉。  
对于合法的行，显然如果 $\texttt{RG}$ 相邻了，那么一方就只能向一边移动，另一方可以跟上继续堵，直到堵到了边界，另一方获胜。  

于是就转化为了 $n$ 堆石子，每堆石子的初始个数为这一行 $\texttt{RG}$ 中空格的数量，每次可以选取 $k$ 堆石子取出任意个，取不了的人失败。  
这是 *Nim-K* 问题，结论为拆出二进制位，对于每一位所有堆这一位为 $1$ 的个数总和都 $\bmod (k + 1) = 0$ 则后手胜，否则先手胜。

证明：  
> 首先定义 $\text{P}$ 态 $\text{N}$ 态为先手必胜 / 输的状态。  
> 显然全 $0$ 为 $\text{N}$ 态。  
> 对于 $\text{N}$ 态，不管怎么操作都会变为 $\text{P}$ 态是显然的，因为最多只能选 $k$ 堆到不了 $k + 1$。  
> 对于 $\text{P}$ 态，存在操作变为 $\text{N}$ 态。  
> 从高位到低位考虑，如果选了一个数，就先让其变为 $0$。  
> 假设当前在第 $i$ 位，且 $> i$ 位选了 $c_1$ 个数，第 $i$ 位为 $1$ 的个数 $\bmod (k + 1)$ 为 $c_2$。     
> 如果说 $c_1 + c_2\ge k + 1$，因为 $c_1$ 个数最高位 $> i$ 所以第 $i$ 位是能变为 $1$ 的，直接让 $k + 1 - c_2$ 个 $c_1$ 中的数的第 $i$ 位变为 $1$ 即可。  
> 否则有 $c_1 + c_2 < k + 1$，即 $c_1 + c_2\le k$，直接选上这 $c_2$ 个数即可。  
> 所以最后选的堆数肯定能不超过 $k$。

时间复杂度 $\mathcal{O}(nm)$。

```cpp
#include<bits/stdc++.h>
const int maxn = 100 + 10;
int a[maxn];
int main() {
    int n, m, k; std::cin >> n >> m >> k;
    bool fR = 0, fG = 0;
    for (int i = 1; i <= n; i++) {
        std::string s; std::cin >> s;
        int wR, cntR = 0, wG, cntG = 0;
        for (int j = 0; j < m; j++) s[j] == 'R' && (wR = j, cntR++), s[j] == 'G' && (wG = j, cntG++);
        if (cntR == 0 && cntG && cntG < m) fG = 1;
        else if (cntR && cntR < m && cntG == 0) fR = 1;
        else if (cntR && cntG) a[i] = abs(wR - wG) - 1;
    }
    if (fR && fG) return puts("Draw"), 0;
    else if (fR) return puts("Second"), 0;
    else if (fG) return puts("First"), 0;
    bool f = 1;
    for (int i = 0; i < 7; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) cnt += a[j] >> i & 1;
        f &= cnt % (k + 1) == 0;
    }
    puts(f ? "Second" : "First");
    return 0;
}
```

---

## 作者：shao0320 (赞：0)

#### 题目大意

- 给定一个 $n\times m$ 的棋盘。棋盘中 `-` 代表空格，`G` 代表绿色棋子，`R` 代表红色棋子。每行至多有两个士兵。
- 先手执绿棋。
- 每个回合玩家可以选择 $1$ 到 $k$个棋子在当前行内向左或向右任意移动一次，但不能越过另一个棋子，也不能在不同行之间移动。
- 若一方在移动后能使另一方无法移动，则获胜。
- 求最后谁获胜或平局。
- $1\leq n,m,k\leq 100$

分析：
考虑单独的一行，当他只有一个颜色的棋子时，可以无限移，对于有两个颜色不一样的棋子时，注意到如果这个人把棋子往另一个的棋子的另一边移是没有用的（因为另一个人可以用一次机会让局面变成相同的），因此这问题等价于必须往中间走。

这个游戏可以抽象成有$m$个石子（$m$是这两个棋子间的空格数量），每次每个人取其中任意多个石子，取走最后一个的胜利。

而同时这里有$m$堆石子你每次只能从其中挑出$1-k$堆进行操作，这就是经典的$Nim-K$问题，这个问题的结论是当且仅当每堆石子的二进制相同位加起来$mod (k+1)=0$。

代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define N 200005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,k,cnt,a[N],Of,Os;
char ch[N];
int abs(int x,int y)
{
	if(x>y)return x-y;
	else return y-x;
}
int main()
{
	n=read();m=read();k=read();;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",(ch+1));
		int	f=0,s=0,ff=0,ss=0;
		for(int j=1;j<=m;j++)
		{
			if(ch[j]=='G')f=j,ff++;
			if(ch[j]=='R')s=j,ss++;
		}
		if(f==0&&s!=0&&ss!=m)Os=1;
		if(f!=0&&s==0&&ff!=m)Of=1;
		if(f&&s)a[++cnt]=abs(s-f)-1;
	}
	if(Os==1&&Of==1)puts("Draw");
	else if(Os==1&&Of==0)puts("Second");
	else if(Of==1&&Os==0)puts("First");
	else
	{
		for(int i=0;i<=8;i++)
		{
			int ff=0;
			for(int j=1;j<=cnt;j++)ff+=((a[j]>>i)&1);
			if(ff%(k+1))
			{
				puts("First");
				return 0;
			}
		}
		puts("Second");
	}
}
```



---

