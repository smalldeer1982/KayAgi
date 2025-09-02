# Minimum Ties

## 题目描述

A big football championship will occur soon! $ n $ teams will compete in it, and each pair of teams will play exactly one game against each other.

There are two possible outcomes of a game:

- the game may result in a tie, then both teams get $ 1 $ point;
- one team might win in a game, then the winning team gets $ 3 $ points and the losing team gets $ 0 $ points.

The score of a team is the number of points it gained during all games that it played.

You are interested in a hypothetical situation when all teams get the same score at the end of the championship. A simple example of that situation is when all games result in ties, but you want to minimize the number of ties as well.

Your task is to describe a situation (choose the result of each game) so that all teams get the same score, and the number of ties is the minimum possible.

## 说明/提示

In the first test case of the example, both teams get $ 1 $ point since the game between them is a tie.

In the second test case of the example, team $ 1 $ defeats team $ 2 $ (team $ 1 $ gets $ 3 $ points), team $ 1 $ loses to team $ 3 $ (team $ 3 $ gets $ 3 $ points), and team $ 2 $ wins against team $ 3 $ (team $ 2 $ gets $ 3 $ points).

## 样例 #1

### 输入

```
2
2
3```

### 输出

```
0 
1 -1 1```

# 题解

## 作者：meyi (赞：14)

令 $x$ 为有胜负的局数， $y$ 为平局局数，易得下列方程组：

$\left\{
    \begin{array}{l}
            x+y=\frac{n(n-1)}{2} \\  3x+2y=kn (k \in N^*)
        \end{array}
\right.$

对第二个方程的解释：有胜负的局数会为所有队的总分的和贡献 $3$ 分，平局会贡献 $2$ 分，而题目要求 $n$ 支所有球队的积分完全相同，故总分为 $n$ 的倍数。

解得
$\left\{
	\begin{array}{l}
    	x=(k-n+1)n \\ y=(\frac{3n-3}{2}-k)n (k\in N^*)
    \end{array}
\right.$

- 若 $n$ 为奇数，则 $k$ 显然取 $\frac{3n-3}{2}$，此时
$\left\{
	\begin{array}{l}
    	x=\frac{n(n-1)}{2} \\ y=0
    \end{array}
\right.$

只需让每只队伍都赢 $\frac{n-1}{2}$ 次即可。

- 若 $n$ 为偶数，则 $k$ 显然取 $\frac{3n-4}{2}$，此时
$\left\{
	\begin{array}{l}
    	x=\frac{n(n-2)}{2} \\ y=\frac{n}{2}
    \end{array}
\right.$

只需让每只队伍都赢 $\frac{n-2}{2}$ 次，平局 $1$ 次即可。

时间复杂度 $O(tn^2)$。

代码：

```cpp
#include<cstdio>
#define ri register int
int n,t;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(ri i=1;i<n;++i){
			ri j=i+1;
			if(!(n&1)&&(i&1))++j,printf("0 ");
			for(;j<=n;++j)
				printf("%d ",(j-i)&1?-1:1);
		}	
		putchar(10);
	}
	return 0;
}
```

---

## 作者：7KByte (赞：5)

转换为图论模型，就是给定一个完全图，每个队伍就是一个点，每场比赛就是一条无向边。现在每次可以消掉一个环，使得剩下的边最少。

转换后的模型就很清晰了，由于$N\le 100$很小，所以我们可以先枚举起点 $S$，再枚举步长 $L$，然后判断 $S\to S+L\to S+2L \to \cdots\to S$是否成环，成环消掉即可。

时间复杂度$\rm O(TN^3)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define N 105
using namespace std;
int v[N][N],d[N],r[N][N],c[N];
void solve(){
	memset(v,0,sizeof(v));
	memset(r,0,sizeof(r));
	int n;scanf("%d",&n);
	rep(i,1,n)rep(l,1,n-1)
		{
			int k=i;bool flag=false;
			memset(c,0,sizeof(c));
			while(!c[k]){
				int p=k;c[p]=1;k=(k-1+l)%n+1;
				if(v[p][k]||v[k][p]||r[p][k]||r[k][p]){flag=true;break;}
				r[p][k]=r[k][p]=1;
			}
			k=i;
			memset(c,0,sizeof(c));
			while(!c[k]){
				int p=k;c[p]=1;k=(k-1+l)%n+1;
				r[p][k]=r[k][p]=0;
			}
			if(!flag){
				k=i;memset(c,0,sizeof(c));
				while(!c[k]){
					int p=k;c[p]=1;k=(k-1+l)%n+1;
					v[p][k]=1;v[k][p]=-1;
				}
			}
		}
	rep(i,1,n)rep(j,i+1,n)printf("%d ",v[i][j]);
	putchar('\n');
}
int main(){
	int T;scanf("%d",&T);
	while(T--)solve();
	return 0;
}
```

---

## 作者：LeavingZzz (赞：2)

# $\mathsf{Solution\space To\space CF1487C}$  
提供一种时间复杂度为 $O(Tn^2)$ 的做法  
## $\mathsf{Description}$  
有 $n$ 支球队要互相比赛，每两支球队之间都进行且只进行一场比赛（一共进行 $\frac{n\times(n-1)}{2}$ 场），每一场比赛胜方得 $3$ 分，败方得 $0$ 分，平局两方各得 $1$ 分。  

现在请你安排这 $\frac{n\times(n-1)}{2}$ 场比赛的 胜/负/平局 情况，请输出任意一种使得所有队伍总得分相同且平局数最少的方案  

多组测试数据，$1\le T\le 100,2\le n\le 100$  
## $\mathsf{Analysis}$  
要求平局数量最少，可以从没有平局入手，因为一共有 $\frac{n\times (n-1)}{2}$ 场，又要每一支队伍分数相同，如果没有平局的话，就相当于每一支队伍获胜次数相同，所以每支队伍获胜 $\frac{n-1}{2}$ 次，所以当 $n$ 是奇数的时候可以直接对一个 $n\times n$ 的矩形染色  
染色代码如下  
```cpp
const int maxn=107;
int ans[maxn][maxn];
int N;
void calc()
{
    int cnt;
    for(int i=1;i<=N;i++)
    {
        cnt=0;
        for(int j=1;j<=N;j++)
        {
            if(i==j) continue;
            if(ans[i][j]==0)
            {
                ans[i][j]=1;ans[j][i]=-1;
                ++cnt;
            }
        }
    }
}

```  
然后考虑 $n$ 是偶数的情况  
假设我们会有 $x$ 场非平局，$y$ 场平局，那么总共产生的分数为 $(3+0)x+(1+1)y=3x+2y$  
我们要让所有队伍分数相同，那么总共产生的分数就要能被 $n$ 整除  
所以有  
$$\begin{cases}2x+2y=n\times (n-1)\\3x+2y=kn\end{cases}$$  
可以解得 $x=n\times(k-n+1)$  
有 $x\le \frac{n\times(n-1)}{2}$  

得到 $k\le \frac{n-1}{2}+n-1$  

让平局数 $y$ 最小，所以 $k$ 取最大，又因为 $n$ 是偶数  

所以 $k=\frac{n-2}{2}+n-1$  

此时 $x=\frac{n\times (n-2)}{2},y=\frac{n}{2}$  

所以每一支队伍胜利 $\frac{n-2}{2}$ 次，失败 $\frac{n-2}{2}$ 次，平局一次  

所以修改一下上面染色的代码，考虑失败的次数限制和平局有且仅有一次即可  
## $\mathsf{Code}$  
```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cctype>
#include<cstdlib>
#include<ctime>
using namespace std;
const int maxn=107;
int ans[maxn][maxn];
int T,N;
int stk[maxn],top;
int r[maxn];
bool book[maxn];
void calc(int w,int te)//w 表示胜利次数限制,te 表示是否有平局
{
    memset(ans,0,sizeof(ans));
    memset(book,0,sizeof(book));
    for(int i=1;i<=N;i++)
        r[i]=N-1-(w+te);//失败次数限制
    if(!w) return ;
    for(int i=1;i<=N;i++)
    {
        top=0;
        for(int j=1;j<=N;j++)
        {
            if(i==j) continue;//不可以自己和自己对战
            if(te&&!book[i]&&!book[j]&&ans[i][j]==0)
            //需要填充平局,i j 都没有过平局并且 i j 间没有对局
            {
                ans[i][j]=ans[j][i]=-2;
                book[i]=book[j]=true;//标记为填充过平局
            }
            if(ans[i][j]==0&&top<w)
            //i j 间没有过对局并且 i 的胜利次数和 j 的失败次数未满
            {
                if(r[j])
                stk[++top]=j,--r[j];
            }
        }
        for(int j=1;j<=top;j++)
            ans[i][stk[j]]=1,ans[stk[j]][i]=-1;
    }
    return ;
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    #endif
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        if(N&1) calc(N-1>>1,0);
        else calc(N-2>>1,1);
        
        for(int i=1;i<=N;i++)
            for(int j=i+1;j<=N;j++)
                printf("%d ",ans[i][j]==-2?0:ans[i][j]);
        puts("");
    }
    return 0;
}
```

---

## 作者：John_Smith (赞：1)

[点击以获得更差的体验](https://www.cnblogs.com/megatrio/p/14430983.html)

为什么题解里面都写得这么简单啊……

提供一种极其复杂的做法。

设非平局的场数为 $a$，平局场数为 $b$。显然，所有人的得分和为 $3a+2b=3(a+b)-b$。

由题得 $\dfrac{n(n+1)}2=a+b$（即总场数为非平局场数加上平局场数），所以我们可以 $O(1)$ 得出使得总得分能被 $n$ 整除的 $b$。

既然得到了平局场数，随即得到每个人的分数。然后呢？只要分数大于等于 $3$，就让他赢，否则：若分数大于 $0$ 则本场平局，否则输。

具体看代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(register int i=(a);i>=(b);--i)
#define read() Read<int>()
#define write Write<int>
#define writesp Writesp<int>
#define writeln Writeln<int>
template<typename T>
inline T Read()
{
	bool f=0;T x=0;char ch;
	do{ch=getchar();f|=(ch=='-');}while(!isdigit(ch));
	do{x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}while(isdigit(ch));
	return f?-x:x;
}
template<typename T>
inline void Write(T x)
{
	if(x<0){putchar('-');write(-x);return;}
	if(x>9)write(x/10);
	putchar(x%10+48);
}
template<typename T> inline void Writeln(T x){Write(x);puts("");}
template<typename T> inline void Writesp(T x){Write(x);putchar(' ');}
int a[105];//记录每个人之前比赛的总得分
int main()
{
	int t=read();
	while(t--)
	{
		memset(a,0,sizeof a);
		int n=read();
		int tot=n*(n-1)/2;//比赛总场数
		int tie=tot*3%n;//平局数量
		int pts=tot*3/n;//每个人的分数
		rep(i,1,n)
		{
			int q=pts-a[i];//当前剩余的得分
			int cur=i+1;//当前对战的球队
			while(q>=3)//赢
			{
				a[i]+=3;
				writesp(1);
				++cur;
				q-=3;
			}
			while(q)//平
			{
				a[i]+=1;
				a[cur]+=1;
				--q;++cur;
				writesp(0);
			}
			while(cur<=n)//输
			{
				a[cur]+=3;
				writesp(-1);
				++cur;
			}
		}
		puts("");
	}
	return 0;
}
```


---

## 作者：一扶苏一 (赞：1)

## CF1487C

### Description

There are $n$ soccer teams. In a season, each team will play exactly one game with all the other teams. There are two outcomes of a game:

- If a team is winner, then it gets 3 points. Yet the lost team won't get point.
- If the result of a game is tie, then both of two teams will get 1 point.

You should construct results of each game to get the aims:

- Eventually all the teams have the same points.
- The number of results which is tie should be as small as possible.

### Limitations

$100$ test cases; $1 \leq n \leq 100$.

### Ayalysis

Consider that if $n$ is odd, then the number of games each team will play $(n -1)$ is even. Let $m$ be $\frac {n - 1}{2}$. If each team wins $m$ games and loses $m$ games, then they will gain the same points and the number of result "tie" is zero, which is minimum.

If $n$ is even, then the number of games each team will play is odd. Obviously, if there is no tie, not all the teams will get the same points(if some team wins more than half games it will play, then there must be other team that loses more than half games, then their points will be distinct). Let $x$ be the number of result of "tie". Then the number of result "one winner" is $\frac {n(n-1)}{2} - x$. The total points of the season is $3(\frac{n(n-1)}{2}-x) + 2x = \frac{3(n-1)}{2}n + \frac x 2$, which must be divisible by $n$. Then $\frac x 2$ must be divisibly by $n$. We have proven that $x$ can't be $0$. Then $x$ is at least $\frac n 2$. There is no harm to assume that the game between $1$ and $2$, $3$ and $4$, ..., $(n-1)$ and $n$ are draws. Then we will get a same problem with case $n$ is odd: For each team, the number of result to be determined is even.

Let's make a dynamic maintenance for the number of games a team have won and lost, and determine the result of team $1, 2, 3, \dots n$ one by one. For each team (which still needs $k$ games to win), we just need to find the team that has lost the minimum team which hasn't played game with the current team. Continue to do this until $k$ is zero. Then we can construct an answer.

To find the teams of which the number of result "lose" is little, we can use priority_queue or sort for each team.

The time complexity is $O(Tn^2 \log n)$.

### Code

```java
import java.io.*;
import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;

public class Main {
  public static void main(String[] argc) {
    Scanner cin = new Scanner(System.in);
    OutputWriter out = new OutputWriter(System.out);
    for (int T = cin.nextInt(); T != 0; --T) {
      int intN = cin.nextInt(), intHalf = (intN - 1) >> 1;
      int[][] intArrWinner = new int[intN][intN];
      for (int i = 0; i < intN; ++i) {
        for (int j = i + 1; j < intN; ++j) intArrWinner[i][j] = -2;
      }
      int[] intArrWins = new int[intN], intArrLost = new int[intN];
      for (int i = 0; i < intN; ++i) intArrWins[i] = intArrLost[i] = 0;
      for (int i = 0; i < intN; ++i) {
        Queue<Pair> Q = new PriorityQueue<>(Comparator.comparingInt(o -> o.intLost));
        int intDraw = -1;
        if ((intN & 1) == 0) {
          intDraw = ((i & 1) == 1) ? i - 1 : i + 1;
          if (intDraw > i) intArrWinner[i][intDraw] = 0;
        }
        for (int j = 0; j < intN; ++j)
          if ((i != j) && (i != intDraw) && (intArrLost[j] < intHalf)
                  && (intArrWinner[Math.min(i, j)][Math.max(i, j)] == -2)) {
            Q.offer(new Pair(j, intArrLost[j]));
          }
        while (intArrWins[i]++ != intHalf) {
          int j = Q.poll().intId;
          if (i < j) intArrWinner[i][j] = 1;
          else intArrWinner[j][i] = -1;
          ++intArrLost[j];
        }
        Q = new PriorityQueue<>(Comparator.comparingInt(o -> -o.intLost));
        for (int j = 0; j < intN; ++j)
          if ((i != j) && (i != intDraw) && (intArrWins[j] < intHalf)
                  && (intArrWinner[Math.min(i, j)][Math.max(i, j)] == -2)) {
            Q.offer(new Pair(j, intArrLost[j]));
          }
        while (intArrLost[i]++ != intHalf) {
          int j = Q.poll().intId;
          if (i < j) intArrWinner[i][j] = -1;
          else intArrWinner[j][i] = 1;
          ++intArrWins[j];
        }
      }
      for (int i = 0; i < intN; ++i) {
        for (int j = i + 1; j < intN; ++j) {
          out.print(intArrWinner[i][j] + " ");
        }
      }
      out.println();
    }
    out.close();
  }
}

class Pair {
  int intId, intLost;

  Pair(int x, int y) {
    intId = x; intLost = y;
  }
}

class OutputWriter {
  private final PrintWriter writer;

  public OutputWriter(OutputStream outputStream) {
    writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(outputStream)));
  }

  public OutputWriter(Writer writer) {
    this.writer = new PrintWriter(writer);
  }

  public void print(Object...objects) {
    for (int i = 0; i < objects.length; i++) {
      if (i != 0)
        writer.print(' ');
      writer.print(objects[i]);
    }
  }

  public void println(Object...objects) {
    print(objects);
    writer.println();
  }

  public void close() {
    writer.close();
  }

}
```

---

