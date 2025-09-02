# [ABC201D] Game in Momotetsu World

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc201/tasks/abc201_d

$ H $ 行 $ W $ 列のマス目があり、各マスは青マスまたは赤マスのどちらかです。上から $ i $ 番目、左から $ j $ 番目のマスは、$ A_{i,\ j} $ が `+` なら青マスであり、`-` なら赤マスです。  
 最初、このマス目の一番左上のマスに一つ駒が置かれていて、高橋君と青木君はこの駒を使ってゲームをします。  
 $ 2 $ 人の得点は最初 $ 0 $ 点ずつです。$ 2 $ 人は、高橋君から始めて交互に次の操作をします。

- 駒を一つ右または一つ下のマスに動かす。ただし、駒がマス目の外に出るような動かし方はできない。動かした人は、駒の移動後のマスが青マスなら $ 1 $ 点を得て、赤マスなら $ 1 $ 点を失う。

どちらかが操作できなくなった時点でゲームは終了します。ゲームの結果は、終了時の $ 2 $ 人の得点が異なるならば得点の大きい方が勝ち、同じならば引き分けとなります。  
 両者とも自分の勝敗が最適になるように行動したとき、ゲームの結果を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ H,\ W\ \le\ 2000 $
- $ A_{i,\ j} $ は `+` または `-`

### Sample Explanation 1

高橋君は以下のような戦略で勝つことができます。 まず高橋君が最初に駒を右に動かします。移動先のマスは赤マスなので高橋君は $ 1 $ 点を失い、高橋君と青木君の得点はそれぞれ $ -1,\ 0 $ となります。 - 青木君が次に駒を右に動かしたなら、高橋君は駒を下に動かします - 青木君が次に駒を下に動かしたなら、高橋君は駒を右に動かします いずれの場合でも青木君は赤マスに駒を動かして $ 1 $ 点を失い、高橋君は青マスに駒を動かして $ 1 $ 点を得るため、両者の得点はそれぞれ $ 0,\ -1 $ となります。 現在駒はマス目の上から $ 2 $ 番目、左から $ 3 $ 番目のマスにあるので、次の移動では青木君は下に動かすほかなく、移動先が赤マスなので両者の得点はそれぞれ $ 0,\ -2 $ となります。 もう駒は右にも下にも動かせないのでゲームは終了し、得点の大きい高橋君が勝利します。

### Sample Explanation 2

青木君は、高橋君がどのように操作しても、上手く操作すれば勝つことができます。

### Sample Explanation 3

この場合ゲームは直ちに終了し、両者得点 $ 0 $ であるため結果は引き分けとなります。

## 样例 #1

### 输入

```
3 3
---
+-+
+--```

### 输出

```
Takahashi```

## 样例 #2

### 输入

```
2 4
+++-
-+-+```

### 输出

```
Aoki```

## 样例 #3

### 输入

```
1 1
-```

### 输出

```
Draw```

# 题解

## 作者：rickyxrc (赞：8)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

题目里写的比较显然，可以看出是一个博弈论问题。

（在模拟赛甚至想出来了是我没想到的）

## 解题思路

又是走棋盘又是博弈论，所以我们考虑博弈动态规划。

我们定义**先手**在走到 $(i,j)$ 时可以领先**对手**的分数。

注意我们提到的是先手不是对手。

我们这么考虑：在博弈 dp 中，先手和后手的角色在每次移动后都会互换。

所以我们领先的分数，等同于对手落后的分数。

所以我们要领先最多，不仅要得到最多分，还要让自己落后最少。

于是我们的转移方程应该是这样：

$$
f_{i-1,j} = \min\{-(f_{i,j}+map_{i,j})\}
$$
$$
f_{i,j-1} = \min\{-(f_{i,j}+map_{i,j})\}
$$

但是，我们应该倒序遍历地图，因为正序遍历会出现后效性，dp 无法处理此类问题，所以上面的的定义只能反过来。

语言表达可能不是很清楚，详见代码。

```cpp
#include<stdio.h>
#include<string.h>

#define maxn 2007

int map[maxn][maxn],dp[maxn][maxn],n,m;
char ch;

int max(int a,int b) {return a>b?a:b;}
int min(int a,int b) {return a<b?a:b;}

int main() {
	scanf("%d%d",&n,&m);

	for(int i=1; i<=n; i++)
		for(int j=1; j<=m; j++) {
			do {
				ch=getchar();
			} while(ch!='-'&&ch!='+');
			if(ch=='+')
				map[i][j] = 1;
			else
				map[i][j] = -1;
			dp[i][j] = 214748364;
		}
	dp[n][m] = 0;

	for(int i=n; i>=1; i--)
		for(int j=m; j>=1; j--)
			dp[i-1][j] = min(-(dp[i][j]+map[i][j]),dp[i-1][j]), 
			dp[i][j-1] = min(-(dp[i][j]+map[i][j]),dp[i][j-1]);

	if(dp[1][1] > 0)
		puts("Aoki");
	if(dp[1][1] < 0)
		puts("Takahashi");
	if(dp[1][1] == 0)
		puts("Draw");

	return 0;
}
```


---

## 作者：Jessica2333 (赞：6)

## 题意
给定一个 $H \times W$ 的棋盘，棋盘上的格子有两种颜色。有一颗棋子在棋盘左上角，也就是（$1,1$）。Takahashi 和 Aoki 要用这颗棋子对战。两人一开始都有 $0$ 分，他们要轮流执行如下操作，Takahashi 先走：

将棋子往右或下移动（不能移出棋盘）。如果移到的格子是蓝色的，对应的玩家得一分；否则，玩家扣一分。

当棋子走到（$H,W$）时，游戏结束。此时，如果两人得分相等，则视为平局；否则，得分多的人胜利。当两人都按最优操作进行游戏时，求最终的游戏结果。

## 思路
看到这句话：两人都按最优操作进行游戏，就想到了**博弈 dp**。题意简单来说就是求先手是否能领先后手（总得分比后手分多）。**我们设 $dp[i][j]$ 为如果先手从（$i,j$）开始走，两人都按照最优策略，到游戏结束先手最多能领先后手多少分**（这个值有可能是负数——先手会领先后手负多少多少分，也就是后手会领先先手正多少多少分）。

那么，游戏结果就是看 $dp[1][1]$ 的正负，如果是正的那么先手赢，是负数那么后手赢，如果是零，那么平局。

比较容易看出，状态的转移是由右到左，由下到上的，也就是从最右下角的格子向上向左推过来的。~~答案就是（$1,1$）怎么可能从左上角开始推嘛...~~ 因为我们如果先手从（$i,j$）走，根据题意，下一步只能走到（$i+1,j$）或（$i,j+1$），所以从（$i,j$）先手的这个状态需要由从（$i+1,j$）先手和从（$i,j+1$）先手的状态转移而来。

我们再想，假设我们从（$i,j$）先手，可以走到（$i+1,j$）或（$i,j+1$）；这时候该另一位玩家，那他就会从（$i+1,j$）或（$i,j+1$）先手；根据 $dp[i][j]$ 的定义，另一位玩家如果从（$i+1,j$）或（$i,j+1$）先手，他就会领先我们（也就是相对于他的后手）$dp[i+1][j]$ 或 $dp[i][j+1]$ 分，反过来那我们就会领先他 $-dp[i+1][j]$ 或 $-dp[i][j+1]$ 分；我们希望尽可能领先他多，所以我们要在 $-dp[i+1][j]$ 和 $-dp[i][j+1]$ 中取较大者；除了领先的分，我们还要考虑走到格子（$i+1,j$）或（$i,j+1$）直接得到的分数，综合起来状态转移方程就得到了：

$dp_{i,j}=\max(-dp_{i+1,j}+mmp_{i+1,j},-dp_{i,j+1}+mmp_{i,j+1})$

其中 $mmp$ 数组存的就是棋盘的某个格子的加分。
## 变量和初始化
### 变量 ~~（其实没啥）~~

$mmp[i][j]$：存棋盘。

$dp[i][j]$：先手从（$i,j$）开始走，两人都按照最优策略，到游戏结束先最多能领先后手多少分。

### 初始化
我们需要初始化的是最下面那一行和最右边那一列，因为状态转移是由右到左，由下到上的；这特殊的一行和一列的状态显然只能分别从它右边和下面转移 ~~（因为不能移出棋盘）~~。

最右下角的那个格子——也就是 $dp[H][W]$ 的值是 $0$，因为走到那个格子游戏就截至了，无法再得分；而特殊的一行和一列就从（$H,W$）分别向左和向上依次转移即可。

## HINTS
注意，如果从某个格子先手，那么这个格子的分是不加的，比如说开局先手从（$1,1$）开始走，（$1,1$）的分是不加的；而最后那个人走到（$H,W$）的分是要加的。

## 代码
```cpp
#include<iostream>
using namespace std;
int H,W,mmp[2008][2008],dp[2008][2008];
int main()
{
	int i,j,k;
	char opt;
	cin>>H>>W;
	for(i=1;i<=H;i++)
	{
		for(j=1;j<=W;j++)
		{
			cin>>opt;
			mmp[i][j]=(opt=='+'?1:-1);
		}
	}
	for(i=H-1;i>=1;i--)
		dp[i][W]=mmp[i-1][W]-dp[i+1][W];
	for(i=W-1;i>=1;i--)
		dp[H][i]=mmp[H][i-1]-dp[H][i+1];
	for(i=H-1;i>=1;i--)
		for(j=W-1;j>=1;j--)
			dp[i][j]=max(mmp[i+1][j]-dp[i+1][j],mmp[i][j+1]-dp[i][j+1]);
	if(dp[1][1]>0) cout<<"Takahashi";
	else if(dp[1][1]<0) cout<<"Aoki";
	else cout<<"Draw";
	return 0;
}
//2023.5.22 by Jessica2333
```


---

## 作者：_Ponder_ (赞：4)

[Game in Momotetsu World](https://www.luogu.com.cn/problem/AT_abc201_d)

### 题目大意

在一个 $n\times m$ 的网格中，存在红色和蓝色两种格子，红色格子用 `-` 表示，蓝色格子用 `+` 表示。

现在 Takahashi 和 Aoki 要在这个网格中进行游戏，游戏的规则如下：

- 初始时，有一枚棋子摆放在左上角，即 $(1,1)$ 的位置。两名玩家的分数均为 $0$。
- 双方轮流行动，Takahashi 先行动。
- 在每次行动中，行动者可以选择将棋子向下或向右移动一格，但移动后不能超出网格。移动后如果棋子位于红色格子，那么行动者的分数 $-1$，否则 $+1$。
- 当棋子无法行动时，即位于 $(n,m)$ 时，游戏结束，得分高者为胜者。

现在告诉你网格的颜色情况，请你判断谁将会获胜。你可以认为这两名玩家都绝顶聪明。

~~好吧，其实我是全部粘过来的，但翻译也是我写的不是吗~~

### 思路分析

~~在打 AT 时，一个重要的原则是遇事不决就 DP。~~

考虑 DP，设 $f_{i,j}$ 表示棋子位于 $(i,j)$ 时，Takahashi 的得分与 Aoki 的得分的差。

那么 Takahashi 的目标是最大化这个值，而 Aoki 则想要最小化这个值。

因为棋子只能向右或向下走，所以此时的回合数就是 $i+j-1$（回合从 $1$ 开始）。那么容易写出状态转移方程：

$$f_{i,j}=\begin{cases}\max(f_{i+1,j}+a_{i+1,j},f_{i,j+1}+a_{i,j+1})&i+j-1\equiv 1\pmod2\\\min(f_{i+1,j}-a_{i+1,j},f_{i,j+1}-a_{i,j+1})&i+j-1\equiv 0\pmod2\end{cases}$$

（$a_{i,j}$ 表示这一位的符号，即若 $(i,j)$ 为 `+`，那么 $a_{i,j}$ 为 $1$，否则为 $-1$。）

因为转移比较奇怪，所以考虑用记搜实现。

### 代码

```
#include <bits/stdc++.h>
using namespace std;
const int N=2020;
#define inf 0x3f3f3f3f

int a[N][N],dp[N][N];
int n,m;
char ch[N];

int dfs(int x,int y){
    if(x==n&&y==m) return 0;//到达边界
    if(dp[x][y]) return dp[x][y];
    if((x+y-1)%2==1){
        dp[x][y]=-inf;//记得赋初值和特判边界！
        if(x!=n) dp[x][y]=max(dp[x][y],dfs(x+1,y)+a[x+1][y]);
        if(y!=m) dp[x][y]=max(dp[x][y],dfs(x,y+1)+a[x][y+1]);
        return dp[x][y];
    }
    else{
        dp[x][y]=inf;
        if(x!=n) dp[x][y]=min(dp[x][y],dfs(x+1,y)-a[x+1][y]);
        if(y!=m) dp[x][y]=min(dp[x][y],dfs(x,y+1)-a[x][y+1]);
        return dp[x][y];
    }
}

int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%s",ch+1);
        for(int j=1;j<=m;j++)
            a[i][j]=(ch[j]=='+')?1:-1;
    }
    int ans=dfs(1,1);//1 1 即为答案
    if(ans>0) cout<<"Takahashi\n";
    if(ans==0) cout<<"Draw\n";
    if(ans<0) cout<<"Aoki\n";
    return 0;
}
```

---

## 作者：VitrelosTia (赞：1)

看到这个数据范围可以考虑 dp。下记 Alice 为先手，Bob 为后手。

思考如何设计状态，考虑最后答案需要判断的是 Alice 和 Bob 的数的关系，那就可以设状态 $f_{i, j}$ 为 Alice 的数减去 Bob 的数在 $(i, j)$ 位置的值。这里 Alice 想要这个东西大，Bob 想让这个东西小，那我们记一下当前是到谁走就可以暴力转移了。

由于转移顺序应该是从后往前推的，含义是从结果反推，并且边界处理起来有点麻烦，所以可以使用记搜实现。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2005, inf = 0x3f3f3f3f;
int n, m; int mp[N][N];

int f[N][N];
int dfs(int x, int y, int now) {
	if (x == n && y == m) return 0;
	if (f[x][y] != inf) return f[x][y];
	int f1 = inf, f2 = inf;
	if (x != n) f1 = dfs(x + 1, y, now ^ 1) + (now ? mp[x + 1][y] : -mp[x + 1][y]);
	if (y != m) f2 = dfs(x, y + 1, now ^ 1) + (now ? mp[x][y + 1] : -mp[x][y + 1]);
	if (f1 == inf) return f2; if (f2 == inf) return f1;
	return f[x][y] = (now ? max(f1, f2) : min(f1, f2));
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++)
		{ char ch; cin >> ch; mp[i][j] = (ch == '+' ? 1 : -1); }
	memset(f, inf, sizeof f); int ans = dfs(1, 1, 1);
	if (ans == 0) cout << "Draw";
	else cout << (ans > 0 ? "Takahashi" : "Aoki");
	return 0;
}
```

---

## 作者：dingshengyang (赞：0)

简单的 minmax 对抗搜索（但是因为没有后效性可以 dp）。

如果当前横纵坐标之和为偶数说明轮到 Takahashi 走，否则轮到 Aoki 走。设 $f_{i,j}$ 为从 $(i,j)$ 走到 $(n,m)$，双方都采用最优策略，所得到的 Takahashi 的分值减去 Aoki 的分值所得到的值。显然 Takahashi 希望这个数尽量大，而 Aoki 希望这个数尽量小。因此 Takahashi 走时会在右边和下边选取一个较大的 $f + w$，其中 $w$ 表示走到这个格子付出的代价。Aoki 同理。

对了，注意越界，然后因为边界在 $f_{n,m} = 0$，所以记得倒着推。

代码就这样，挺容易理解的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2005;
char a[N][N];
int n,m;
int f[N][N],vis[N][N];
// let f[i][j] = Takahashi's score - Aoki's score
// so that Takahashi will try to make it bigger
// and Aoki will try to make it smaller
// for (i + j) is even , the current move will be moved by Takanashi
// otherwise the current move will be moved by Aoki
int main(){
    cin >> n >> m;
    for(int i = 1;i <= n;i ++)for(int j = 1;j <= m;j ++)cin >> a[i][j];
    // f[n][m] = (((n + m) & 1) ? 1 : -1) * (a[n][m] == '+' ? 1 : -1);
    for(int i = n;i >= 1;i --){
        for(int j = m;j >= 1;j --){
            if(i == n && j == m)continue;
            if((i + j) % 2 == 0){ // Takanashi's move
                f[i][j] = -0x3f3f3f3f;
                if(i + 1 <= n){
                    f[i][j] = max(f[i][j],f[i + 1][j] + ((a[i + 1][j] == '+') ? 1 : -1));
                }
                if(j + 1 <= m){
                    f[i][j] = max(f[i][j],f[i][j + 1] + ((a[i][j + 1] == '+') ? 1 : -1));
                }
            }else{ //Aoki's move
                f[i][j] = 0x3f3f3f3f;
                if(i + 1 <= n){
                    f[i][j] = min(f[i][j],f[i + 1][j] - ((a[i + 1][j] == '+') ? 1 : -1));
                }
                if(j + 1 <= m){
                    f[i][j] = min(f[i][j],f[i][j + 1] - ((a[i][j + 1] == '+') ? 1 : -1));
                }
            }
        }
    }
    // f[1][1] -= (((1 + 1) & 1) ? 1 : -1) * (a[1][1] == '+' ? 1 : -1);
    // for(int i = 1;i <= n;i ++){
    //     for(int j = 1;j <= m;j ++){
    //         cout << f[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    if(f[1][1] > 0)cout << "Takahashi" << endl;
    else if(f[1][1] == 0)cout << "Draw" << endl;
    else cout << "Aoki" << endl;
    return 0;
}
```

---

## 作者：_Kenma_ (赞：0)

# AT_abc201_d 解题报告

## 前言

minmax 对抗搜索只能放 D，实在是给我吓到了。

可能是因为做法很像 DP，好理解？

## 思路分析

为了方便描述，我们把先手称为 $A$，后手称为 $B$。$A$ 的收益为 $val_a$，$B$ 的收益为 $val_b$。

首先因为不能走回头路，所以每个状态之间转移构成一颗树。

然后发现是一个双方拿金币的模型。

可以设 $f_{i,j}$ 表示走到 $(i,j)$，在双方都使用最优策略的情况下，$val_a-val_b$ 的值。

然后根据定义修改地图的值。

具体地，当 $i+j$ 为偶数时，这个位置的收益是加在 $val_b$ 上的，所以此时要把地图的加减号翻转。

然后在搜索树上从下往上（其实就是在网格图上从下往上，从右往左）转移：

$$f_{i,j}=
    \begin{cases}
      \min(f_{i+1,j},f_{i,j+1})+a_{i,j} & & ((i+j)\bmod 2=0)\\ 
      \max(f_{i+1,j},f_{i,j+1})+a_{i,j} & & ((i+j)\bmod 2=1)\\
    \end{cases}
$$

- 如果 $f_{1,1}>0$，先手胜；

- 如果 $f_{1,1}=0$，平局胜；

- 如果 $f_{1,1}<0$，后手胜；

然后就做完了。复杂度为 $O(nm)$。

## 代码实现

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,a[2005][2005],f[2005][2005];
char ch;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>ch;
			if(ch=='+') a[i][j]=1;
			else a[i][j]=0;
			if((i+j)%2==0) a[i][j]^=1;
		} 
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(!a[i][j]) a[i][j]=-1;
		}
	}
	a[1][1]=0;
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(i==n && j==m) f[i][j]=a[i][j];
			else if(i==n) f[i][j]=f[i][j+1]+a[i][j];
			else if(j==m) f[i][j]=f[i+1][j]+a[i][j];
			else if((i+j)%2==0) f[i][j]=max(f[i+1][j],f[i][j+1])+a[i][j];
			else f[i][j]=min(f[i+1][j],f[i][j+1])+a[i][j]; 
		}
	}
	if(f[1][1]>0) cout<<"Takahashi";
	else if(f[1][1]==0) cout<<"Draw";
	else cout<<"Aoki";
	return 0;
}

```

注意将 $a_{1,1}$ 赋为 $0$。

## 后记

不多见的 minmax 搜索的偏板子题。

不认为是 DP 的原因是转移函数一直在变化，也没有主观决策的过程。

---

## 作者：Claire0918 (赞：0)

注意到每一个操作的人是确定的。设 $f_{x, y}$ 表示在 $(x, y)$ 位置当前操作者希望得到的先手和后手的分数差。其中先手希望使其尽量大，后手希望使其尽量小。答案即判断 $f_{1, 1}$ 的符号。

我们尝试用 DFS 处理每一个 $f_{x, y}$。注意到可以使用记忆化保证复杂度为 $\mathcal{O}(WH)$。

每一次转移查看向下和向右的两个点的值，按照操作者的希望取值。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxn = 2000 + 10, INF = numeric_limits<int>::max();
const int dx[] = {0, 1}, dy[] = {1, 0};

int n, m;
int a[maxn][maxn], f[maxn][maxn];

inline int dfs(int x, int y, int person){
    if (f[x][y] != INF){
        return f[x][y];
    }
    int res = person ? numeric_limits<int>::max() : numeric_limits<int>::min();
    for (int i = 0; i < 2; i++){
        const int gx = x + dx[i], gy = y + dy[i];
        if (gx <= n && gy <= m){
            const int value = dfs(gx, gy, person ^ 1) + (a[gx][gy] ^ person ? 1 : -1);
            if (person){
                res = min(res, value);
            }else{
                res = max(res, value);
            }
        }
    }
    return f[x][y] = res;
}

int main(){
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++){
        getchar();
        for (int j = 1; j <= m; j++){
            a[i][j] = getchar() == '+';
            f[i][j] = INF;
        }
    }
    f[n][m] = 0;
    dfs(1, 1, 0);
    printf(f[1][1] > 0 ? "Takahashi" : !f[1][1] ? "Draw" : "Aoki");

return 0;
}
```

---

## 作者：cosf (赞：0)

这题和 [AT_dp_l](https://www.luogu.com.cn/problem/AT_dp_l) 很像，只不过是二维的。

考虑倒推 dp。我们令 $f_{i, j}$ 表示从 $(i, j)$ 出发，先手得分减去后手得分的最大值是多少。

递推式可以很容易地写出：

$$
f_{i, j} = \max\{a_{i, j + 1} - f_{i, j + 1}, a_{i + 1, j} - f_{i + 1, j}\}
$$

其中，如果 $(i, j)$ 是 `+`，那么 $a_{i, j} = 1$，否则 $a_{i, j} = -1$。

我们只需要算出 $f_{1, 1}$ 的值即可。注意判边界。

## 代码

```cpp
#include <iostream>
using namespace std;

using ll = long long;

#define MAXN 2005
#define get(x) ((x) == '+' ? 1 : -1)

int n, m;

string mp[MAXN];

ll dp[MAXN][MAXN];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> mp[i];
        mp[i] = " " + mp[i];
    }
    for (int i = n; i; i--)
    {
        for (int j = m; j; j--)
        {
            if (i == n && j == m)
            {
                continue;
            }
            else if (i == n)
            {
                dp[i][j] = get(mp[i][j + 1]) - dp[i][j + 1];
            }
            else if (j == m)
            {
                dp[i][j] = get(mp[i + 1][j]) - dp[i + 1][j];
            }
            else
            {
                dp[i][j] = max(get(mp[i][j + 1]) - dp[i][j + 1], get(mp[i + 1][j]) - dp[i + 1][j]);
            }
        }
    }
    if (dp[1][1] > 0)
    {
        cout << "Takahashi" << endl;
    }
    else if (dp[1][1] == 0)
    {
        cout << "Draw" << endl;
    }
    else
    {
        cout << "Aoki" << endl;
    }
    return 0;
}
```

---

