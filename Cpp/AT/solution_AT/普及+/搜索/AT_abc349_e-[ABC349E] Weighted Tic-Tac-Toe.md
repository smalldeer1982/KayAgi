# [ABC349E] Weighted Tic-Tac-Toe

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc349/tasks/abc349_e

$ 3\ \times\ 3 $ のマス目があります。上から $ i $ 行目、左から $ j $ 列目 $ (1\ \leq\ i,j\ \leq\ 3) $ のマスをマス $ (i,j) $ と表します。マス $ (i,j) $ には整数 $ A_{i,j} $ が書かれています。ここで、 $ \sum_{i=1}^3\ \sum_{j=1}^3\ A_{i,j} $ は奇数であることが保証されます。また、すべてのマスははじめ白で塗られています。

高橋君と青木君が、このマス目を使ってゲームを行います。ゲームでは、高橋君を先手として、二人が交互に以下の操作を行います。

- 白で塗られているマス $ (i,j)\,(1\leq\ i,j\ \leq\ 3) $ を選ぶ（操作が行われる時点で、そのようなマスは必ず存在することが示せる）。操作をしているプレイヤーが得点 $ A_{i,j} $ を得る。次に、操作をしているプレイヤーが高橋君ならば、マス $ (i,j) $ を赤で、青木君ならば青で塗る。
 
各操作のあと、次の判定を行います。

- 赤または青の同じ色で塗られたマスが縦・横・斜めのいずれかの方向に $ 3 $ つ連続する箇所があるか判定する。そのような箇所があれば、その時点でゲームを終了し、赤が $ 3 $ つ連続しているならば高橋君が、青が $ 3 $ つ連続しているならば青木君が勝利する。
- 白で塗られているマスが存在するか判定する。存在しなければ、その時点でゲームを終了し、その時点までに獲得した累計の得点が高い方のプレイヤーが勝利する。
 
ゲームは必ず有限回の操作で終了し、高橋君または青木君の一方が勝利することが示せます。両者が勝ちを目指して最適に行動するとき、どちらが勝つか判定してください。

## 说明/提示

### 制約

- $ |A_{i,j}|\ \leq\ 10^9 $
- $ \sum_{i=1}^3\ \sum_{j=1}^3\ A_{i,j} $ は奇数
- 入力はすべて整数
 
### Sample Explanation 1

高橋君が最初の手番で $ (2,2) $ を選択すると、その後どのように青木君が行動しても、高橋君が適切に行動することで、青で塗られたマスが $ 3 $ つ連続しないようにすることができます。赤で塗られたマスが $ 3 $ つ連続した場合は高橋君が勝ちます。赤で塗られたマスが $ 3 $ つ連続せずにゲームが終了した場合、その時点で高橋君は $ 1 $ 点、青木君は $ 0 $ 点を獲得しているため、どちらにせよ高橋君が勝ちます。

## 样例 #1

### 输入

```
0 0 0
0 1 0
0 0 0```

### 输出

```
Takahashi```

## 样例 #2

### 输入

```
-1 1 0
-4 -2 -5
-4 -1 -5```

### 输出

```
Aoki```

# 题解

## 作者：Drest (赞：4)

# [ABC349E] Weighted Tic-Tac-Toe 题解

传送门：
[luogu](https://www.luogu.com.cn/problem/AT_abc349_e) | [atcoder](https://atcoder.jp/contests/abc349/tasks/abc349_e)

## 题目翻译

有一个 $3\times3$ 的网格。$(i,j)$ 表示从顶部数第 $i$ 行、从左数第 $j$ 列的单元格 $(1\le i,j\le 3)$。单元格 $(i,j)$ 包含一个整数 $A_{i,j}$。可以保证 $\sum_{i=1}^3 \sum_{j=1}^3 A_{i,j}$ 是奇数。此外，所有单元格最初都是白色的。

Takahashi 和 Aoki 将使用这个网格进行游戏。Takahashi 先走，他们轮流执行以下操作：

选择一个仍然为白色的单元格 $(i,j)(1\le i,j\le3)$（可以证明这样的单元格在操作时总是存在的）。执行操作的玩家获得 $A_{i,j}$ 分。然后，如果玩家是 Takahashi，他将单元格 $(i,j)$ 涂成红色；如果玩家是 Aoki，他将其涂成蓝色。

每次操作后，都会进行以下检查：

- 检测是否存在三个连续的单元格被涂成相同的颜色（红色或蓝色）在任何行、列或对角线上。如果存在这样的序列，游戏立即结束，并且其颜色形成该序列的玩家获胜。

- 检查是否有白色单元格剩余。如果没有白色单元格剩余，游戏结束，得分较高的玩家获胜。

可以证明游戏将在有限次数的操作后结束，并且 Takahashi 或 Aoki 将获胜。确定如果双方的操作都是最佳的，哪位玩家会获胜。

## 题意简述

其实就是井字棋+平局分高获胜的一个**博弈论问题**。

## 解题思路

很容易想到使用 DFS 解决此题。

根据博弈论：

- 当某一玩家行动时，如果**存在**一行动策略可以使得**这个玩家获胜**，那么这个玩家在此状态下**必胜**，否则必败（因为确保总分是奇数，所以不会出现平局的情况）。

其实题目中所给的 Takahashi 和 Aoki 分别对应的就是先后手的情况。那么以上就可以转换为：

- 当轮到 Takahashi 行动时，枚举所有的行动策略并 DFS，如果某一行动策略能使得 Takahashi 获胜，那么 Takahashi 必胜，否则必败。

- 当轮到 Aoki 行动时，枚举所有的行动策略并 DFS，如果某一行动策略能使得 Takahashi 必败，那么 Takahashi 必败，否则必胜。

注意：

1. 不开 `long long` 见祖宗。
2. 返回前记得重置状态。

~~别问我怎么知道的。~~

## AC 代码

其中，`end()` 函数是用于判定是否结束，返回 $0$ 未结束，返回 $1$ 是 Takahashi 胜利，返回 $2$ 是 Aoki 胜利，返回 $-1$ 表示需要计算分数。


```cpp
#define int long long
int a[4][4];
int vis[4][4];
int end() {
    // 已三连
    for (int i = 1; i <= 3; i++) {
        if (vis[i][1] != 0 && vis[i][1] == vis[i][2] && vis[i][2] == vis[i][3]) {
            return vis[i][1];
        }
    }
    for (int j = 1; j <= 3; j++) {
        if (vis[1][j] != 0 && vis[1][j] == vis[2][j] && vis[2][j] == vis[3][j]) {
            return vis[1][j];
        }
    }
    if (vis[1][1] != 0 && vis[1][1] == vis[2][2] && vis[2][2] == vis[3][3]) {
        return vis[1][1];
    }
    if (vis[1][3] != 0 && vis[1][3] == vis[2][2] && vis[2][2] == vis[3][1]) {
        return vis[1][3];
    }
    // 未填满
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            if (vis[i][j] == 0)
                return 0;
        }
    }
    // 填满了~~~
    return -1;
}

// (return) true : 先手必胜；false：后手必胜
// (args) num1：先手的分数；num2：后手的分数
bool dfs(bool now, int num1, int num2) {
    int endif = end();
    if (endif != 0) {
        if (endif == 1)  return true;           // 如果先手赢，返回 true
        if (endif == 2)  return false;          // 如果后手赢，返回 false
        if (endif == -1) return num1 > num2;    // 比较双方得分
    }
    if (now) { // 先手在走
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                if (vis[i][j] == 0) {
                    vis[i][j] = 1;
                    // 如果走这里必胜，那么先手必胜
                    if (dfs(false, num1 + a[i][j], num2)) {
                        vis[i][j] = 0; // 记得重置状态
                        return true;
                    }
                    vis[i][j] = 0;
                }
            }
        }
        return false; // 先手不必牲
    } else { // 后手在走
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                if (vis[i][j] == 0) {
                    vis[i][j] = 2;
                    // 如果走这里后手必胜，那么后手必胜
                    if (!dfs(true, num1, num2 + a[i][j])) {
                        vis[i][j] = 0;
                        return false;
                    }
                    vis[i][j] = 0;
                }
            }
        }
        return true; // 先手必胜
    }
    return true; // 防止 linux 系统下 RE
}
signed main() {
    for (int i = 1; i <= 3; i++) 
        for (int j = 1; j <= 3; j++) 
            cin >> a[i][j];
    bool win = dfs(true, 0, 0); // 先手是否必胜
    if (win) {
        cout << "Takahashi" << endl;
    } else {
        cout << "Aoki" << endl;
    }
    return 0;
}
``````

---

## 作者：KSCD_ (赞：2)

## 题意
有一个三行三列的网格，每格上有一个数，两人在上面玩井字棋，选到连续三个格子即获胜。若出现平局，则所选格子上的数字和较大者获胜，问谁有必胜策略。
## 思路
是一道博弈论题，但数据规模很小，一共只有 $9$ 个格子，可以dfs~~乱搞~~。

直接暴力dfs搜索两人的选择，分别标记为两人的序号，随时检查是否分出胜负即可。

要注意的是，只要在当前局面下有一种操作能使对方必败，则自己如此操作就必胜；若所有操作方式最终都让对方有必胜策略，则自己必败。

具体请看代码实现。
## 代码
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=3+10;
int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') { s=s*10+ch-'0'; ch=getchar();}
	return s*w;
}
int a[N][N],v[N][N];//输入的数和每个格子被选的情况 
bool dfs(int st,int x,int y)//已选了st个格子，初始先手的和为x，初始后手的和为y，此时操作是否有必胜策略 
{
	int now=st%2+1,la=(st+1)%2+1;//1为初始先手，2为初始后手；now为现在即将操作的人，la为上一个操作者 
	if(v[1][1]==la&&v[1][2]==la&&v[1][3]==la) return 0;
	if(v[2][1]==la&&v[2][2]==la&&v[2][3]==la) return 0;
	if(v[3][1]==la&&v[3][2]==la&&v[3][3]==la) return 0;
	if(v[1][1]==la&&v[2][2]==la&&v[3][3]==la) return 0;
	if(v[1][3]==la&&v[2][2]==la&&v[3][1]==la) return 0;
	if(v[1][1]==la&&v[2][1]==la&&v[3][1]==la) return 0;
	if(v[1][2]==la&&v[2][2]==la&&v[3][2]==la) return 0;
	if(v[1][3]==la&&v[2][3]==la&&v[3][3]==la) return 0;//判断上一个操作者是否连成三个 
	if(st==9)//若全部选完，则根据大小判断胜负 
	{
		if(x>y) return 0;
		else return 1;//要注意此处st=9，即初始后手即将操作，所以y较大时是必胜 
	}
	for(int i=1;i<=3;i++) for(int j=1;j<=3;j++)
	{
		if(v[i][j]) continue;
		v[i][j]=now;
		bool tf;
		if(now==1) tf=dfs(st+1,x+a[i][j],y);
		else tf=dfs(st+1,x,y+a[i][j]);//分初始先后手判断 
		v[i][j]=0;//注意回溯 
		if(!tf) return true;//对方必败则如此操作可必胜 
	}
	return false;
}
signed main()
{
	for(int i=1;i<=3;i++) for(int j=1;j<=3;j++) a[i][j]=read();
	if(dfs(0,0,0)) cout<<"Takahashi"; 
	else cout<<"Aoki";
	return 0;
}
```

---

## 作者：maokaiyu (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc349_e)
## 思路
既然两个人都很聪明，必然是不会出现连成三子的情况的。所以我们只需要递归求解所有平局的情况就好了。只要平局的答案中有至少一种高桥能赢，高桥就会赢，否则是输。
## 做法
递归时有两个参数为 $x$ 和 $sum$ 分别表示走的第几步和总分。当 $x$ 是偶数时，就表明到高桥了，当走这个位置必输时，就返回假，否则继续。到高桥走时，$sum$ 要加上对应权值，否则减去对应权值。到第九步时，如果 $sum$ 大于零返回真，否则是假。 
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be(x) x.begin()
#define en(x) x.end()
using namespace std;
typedef long long LL;
typedef int I;
I a[4][4],b[4][4];
bool check(){//判断
	for(I i = 1;i <= 3;i++){
		if(b[i][1] == b[i][2] && b[i][2] == b[i][3] && b[i][3]){
			return true;
		}
		if(b[1][i] == b[2][i] && b[2][i] == b[3][i] && b[3][i]){
			return true;
		}
	}
	if(b[1][1] == b[2][2] && b[2][2] == b[3][3] &&  b[3][3]){
		return true;
	}
	if(b[3][1] == b[2][2] && b[2][2] == b[1][3] && b[1][3]){
		return true;
	}
	return false;
}
bool dfs(I x,LL sum){
	if(x == 9){
		return !(sum > 0);
	}
	if(check()){
		return false;
	}
	bool t = false;
	for(I i = 1;i <= 3;i++){//搜索
		for(I j = 1;j <= 3;j++) if(!b[i][j]){
			b[i][j] = (x % 2) + 1;
			LL f = 1;
			if(x % 2){
				f = -1;
			}
			t |= 1 - dfs(x + 1,sum + a[i][j] * f);
			b[i][j] = 0;
		}
	}
	return t;
} 
I main(){
	for(I i = 1;i <= 3;i++){
		for(I j = 1;j <= 3;j++){
			scanf("%d",&a[i][j]);
		}
	}
	if(dfs(0,0)){//答案
		printf("Takahashi\n");
	}else{
		printf("Aoki\n");
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：1)

先给大家看个乐子，注意提交时间。

![](https://cdn.luogu.com.cn/upload/image_hosting/vrg3z5lt.png)

首先粗略估计一下状态数。每个格子只有可能填红色、蓝色或者白色。因此总状态最多只有 $3 ^ {9}$ 中，实际上会小得多。

将所有状态搜出来。对于一个状态，如果某个选手无法下棋了则定义当前状态为该选手对手的必胜态。一个状态是必胜态，当且仅当其后继状态其后继都是对手的必败态。反之则为必败态。

对问题构建博弈树，直接在博弈树上搜索即可。复杂度为状态数与判断复杂度的乘积，大概是 $O(n ^ 2 3 ^ {n ^ 2})$，其中 $n = 3$。[submission](https://atcoder.jp/contests/abc349/submissions/52355925)。

---

## 作者：haokee (赞：1)

需要一点细节的博弈论好题。

## 题目大意

有 $3\times 3$ 的棋盘，第 $i$ 行第 $j$ 列上面的数为 $a_{i,j}$。高桥和奥吉轮流下棋，如果在下棋的过程中其中一个人有三个子连成了一条长度为 $3$ 线，那么这个人就直接赢了。如果到最后都没分出胜负，那么就按照下的位置上面的数的和为标准来判断。两个人都会选择最优策略。

## 思路

首先是这道题的中心思想，非常重要，一定要默念三遍：如果对面有一种下棋方法必输，那么我就是必赢的；如果对面所有的下棋方法都必赢，那么我就必输。

接下来，我们可以采用 $\mathcal O(9!)$ 的大爆搜，这就代表着，只要我们细心地对着上面的结论进行模拟，那么就可以一遍过！

## 代码

```cpp
import java.util.*

val cin = Scanner(System.`in`)

const val n = 3
val a = Array(n + 1) { LongArray(n + 1) }  // 位置上面的数
val f = Array(n + 1) { LongArray(n + 1) }  // 每一个位置被谁给标记了
var s1 = 0L                                // 高桥的和
var s2 = 0L                                // 奥吉的和

fun check(): Long {                                                          // 判断那个人连成了一条线
  for (i in 1..n) {                                                          // 遍历每一行和每一列
    if (f[i][1] != 0L && f[i][1] == f[i][2] && f[i][2] == f[i][3]) {         // 当前行的赢了
      return f[i][1]                                                         // 返回赢了的人
    } else if (f[1][i] != 0L && f[1][i] == f[2][i] && f[2][i] == f[3][i]) {  // 当前列的赢了
      return f[1][i]                                                         // 返回赢了的人
    }
  }
  if (f[1][1] != 0L && f[1][1] == f[2][2] && f[2][2] == f[3][3]) {           // 右斜线
    return f[1][1]
  } else if (f[1][3] != 0L && f[1][3] == f[2][2] && f[2][2] == f[3][1]) {    // 左斜线
    return f[1][3]
  }
  return 0L                                                                  // 没有人赢
}

fun dfs(x: Long): Boolean {                               // 大爆搜环节
  if (check() != 0L) {                                     // 如果有人连成了一条线
    return check() - 1L != x % 2L                          // 判断当前人是否输了
                                                           // 这里可能比较抽象
                                                           // 因为当前人还没有下棋，因此需要判断的是当前人有没有输
                                                           // check() - 1L：高桥赢了为 0，奥吉赢了为 1
                                                           // x % 2L：当前为高桥为 1，当前为奥吉为 0
                                                           // 需要使用不等于号，因为假设当前为奥吉，刚才高桥赢了，
                                                           // 那么表达式就等同于 0 != 0，则 false
  }
  if (x > 9) {                                             // 没有决出胜负
    return s2 > s1                                         // 按照得分来判断
                                                           // 注意需要反过来，因为
                                                           // 刚才下的是高桥，我们需要
                                                           // 判断奥吉有没有赢
  }
  var b = false                                            // 判断对面有没有必输的可能
  for (i in 1..n) {                                        // 枚举行
    for (j in 1..n) {                                      // 枚举列
      if (f[i][j] == 0L) {                                 // 如果还没有被下
        if (x % 2 != 0L) s1 += a[i][j] else s2 += a[i][j]  // 累加到得分里面
        f[i][j] = if (x % 2 != 0L) 1 else 2                // 打上标记，高桥为 1，奥吉为 2
        b = b || !dfs(x + 1)                               // 继续搜索，看对面有没有必输的可能（这里可以剪枝）
        if (x % 2 != 0L) s1 -= a[i][j] else s2 -= a[i][j]  // 去掉加上的得分
        f[i][j] = 0L                                       // 清空标记
      }
    }
  }
  return b                                                 // 是否必赢
}

fun main() {
  for (i in 1..n) {
    for (j in 1..n) {
      a[i][j] = cin.nextLong()
    }
  }
  println(if (dfs(1)) "Takahashi" else "Aoki")
}
```

---

## 作者：CuteChat (赞：1)

## 题意

两个人下三子棋，但如果出现平局，哪一方下的棋子的位置的权值和大谁就赢，如果先手赢输出 `Takahashi`，否则输出 `Aoki`。

## 题解

这道题目和博弈论动态规划类似，只不过这个不用动态规划也可以，或者说更好，因为两个人的操作序列只有 $9!$ 种，暴力枚举全排列都可以做，省去了写哈希的麻烦。

定义一个递归函数，参数提供目前一共下了 $i$ 个棋，先手下的棋子的权值和为 $x$，后手下的棋子的权值和为 $y$，目前是 $k$ 这个人操作（$k=0$ 时为先手），返回值为 $k$ 这个人的胜负状态。

那么我们就有一下几种情况可以讨论：

- 如果场面已经形成了三同色棋子共线，显然 $k$ 这个人失败了，因为在上一个人落子的时候，转化到 $k$ 这个人的局面，他就已经输了。
- 如果棋子无处可落，根据 $x,y$ 的大小返回胜负状态即可。
- 否则，我们就看看这种局面可以达到哪些状态，暴搜加回溯，在递归的时候调用的参数，显然我们又落下了一个棋子，并且这时候由先（后）手转化到了后（先）手。如果在**那种**局面，返回的是失败状态，那么当前的局面就可以获胜。
- 否则当前局面就不可能获胜。

这是博弈论的简单套路，也就是说，如果先（后）手能将当前的局面转换成后（先）手必败的局面，那么先（后）手根据最优策略的说法，就一定能获胜，否则先（后）手在当前局面必败。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define Xuanxuan
#define int long long

#ifndef Xuanxuan
#define endl '\n'
#define debug(x, ...) printf(x, __VA_ARGS__)
#else
#define debug(x, ...)
#endif

int n, a[4][4], mp[4][4];

int check() {
	for (int i = 1; i <= 3; ++i) {
		if (mp[i][1] == mp[i][2] && mp[i][2] == mp[i][3]) {
			if (mp[i][1] == 1) return 1;
			else if (mp[i][1] == 2) return 2;
		}
	}
	for (int i = 1; i <= 3; ++i) {
		if (mp[1][i] == mp[2][i] && mp[2][i] == mp[3][i]) {
			if (mp[1][i] == 1) return 1;
			else if (mp[1][i] == 2) return 2;
		}
	}
	if (mp[1][1] == mp[2][2] && mp[2][2] == mp[3][3]) {
		if (mp[1][1] == 1) return 1;
		else if (mp[1][1] == 2) return 2;
	}
	if (mp[1][3] == mp[2][2] && mp[2][2] == mp[3][1]) {
		if (mp[1][3] == 1) return 1;
		else if (mp[1][3] == 2) return 2;
	}
	return 0;
}

bool dfs(int i, int tak, int aok, int who) { 
	int check_res = check();
	if (check_res) {
		return check_res == who;
	}
	if (i == 10) {
		if (who == 1) return tak > aok;
		else return tak <aok;
	}
	bool canwin = 0;
	for (int j = 1; j <= 3; ++j) {
		for (int k = 1; k <= 3; ++k) {
			if (!mp[j][k]) {
				mp[j][k] = who;
				if (who == 1)
					canwin |= !dfs(i + 1, tak + a[j][k], aok, 3 - who);
				else canwin |= !dfs(i + 1, tak, aok + a[j][k], 3 - who);
				mp[j][k] = 0;
			}
		}
	}
	return canwin;
}

signed main() {
	#ifdef Xuanxuan
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	#endif
	
	for (int i = 1; i <= 3; ++i) {
		for (int j = 1; j <= 3; ++j) {
			cin >> a[i][j];
		}
	}
	
	if (dfs(1, 0, 0, 1)) {
		cout << "Takahashi" << endl;
	} else {
		cout << "Aoki" << endl;
	}
	
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：0)

### 题目大意

#### 问题陈述

有一个 $3 \times 3$ 网格。让 $(i, j)$ 表示从顶端起第 $i$ 行和从左侧起第 $j$ 列的单元格 $(1 \leq i, j \leq 3)$ 。单元格 $(i, j)$ 包含一个整数 $A_{i,j}$ 。可以保证网格内所有数的和是奇数。此外，所有单元格最初都涂成白色。

高桥和青木将用这个网格下一盘棋。高桥先下，两人轮流进行以下操作：

- 选择一个仍被涂成白色的单元格 $(i, j)$ $(1\leq i, j \leq 3)$ (可以证明这样的单元格在操作时总是存在的)。执行操作的棋手会得到 $A_{i,j}$ 分。然后，如果棋手是高桥，他会将 $(i, j)$ 单元格涂成红色；如果棋手是青木，他会将其涂成蓝色。

每次操作之后，都要进行以下检查：

- 检查在任何一行、一列或对角线上是否有三个连续的单元格被涂上相同的颜色(红色或蓝色)。如果存在这样的序列，游戏立即结束，颜色构成序列的玩家获胜。
- 检查是否还有白色单元格。如果没有白色单元格，游戏结束，总分高的玩家获胜。

可以证明，对局总会在有限步数后结束，高桥或青木将获胜。如果两位棋手都以最佳方式下棋，那么哪位棋手会获胜？

如果是高桥赢了输出 `Takahashi`，否则输出 `Aoki`。

### 思路

我们考虑暴力搜索，每个格子是什么颜色，然后最后判断是否有三个连着的，如果有，那显然三个连着的胜利，否则就去看谁的分数大。

### 代码

~~~cpp
#include<bits/stdc++.h>
#define ll long long
#define mkp make_pair
#define pll pair<ll,ll>
#define prq priority_queue
using namespace std;
inline ll read() {
	ll x = 0, f = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9') {
		if (ch == '-') {
			f = -1;
		}
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
ll a[5][5], x[5][5];
inline ll chk() {
	for (int i = 1; i <= 3; i++) {
		if (x[i][1] == x[i][2] && x[i][2] == x[i][3]) {
			return x[i][1];
		}
	}
	for (int i = 1; i <= 3; i++) {
		if (x[1][i] == x[2][i] && x[2][i] == x[3][i]) {
			return x[1][i];
		}
	}
	if (x[1][1] == x[2][2] && x[2][2] == x[3][3]) {
		return x[1][1];
	}
	if (x[1][3] == x[2][2] && x[2][2] == x[3][1]) {
		return x[1][3];
	}
	ll cnt1 = 0, cnt2 = 0;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			if (!x[i][j]) {
				return 0;
			}
			if (x[i][j] == 1) {
				cnt1 += a[i][j];
			} else {
				cnt2 += a[i][j];
			}
		}
	}
	return (cnt1 > cnt2 ? 1 : 2);
}
inline ll dfs(ll p) {
	if (chk()) {
		return chk() == p ? 1 : 0;
	}
	ll ans = 0;
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			if (!x[i][j]) {
				x[i][j] = p;
				if (!dfs(p % 2 + 1)) {
					ans = 1;
				}
				x[i][j] = 0;
			}
		}
	}
	return ans;
}
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			a[i][j] = read();
		}
	}
	if (dfs(1)) {
		printf("Takahashi");
	} else {
		printf("Aoki");
	}
	return 0;
}
~~~

---

## 作者：破壁人罗辑 (赞：0)

题目传送门：[洛谷](https://www.luogu.com.cn/problem/AT_abc349_e)/[Atcoder](https://atcoder.jp/contests/abc349/tasks/abc349_e)

## 解题思路

直接 dfs 深度优先搜索加点剪枝即可，相当于搜索所有的双方落子顺序，状态数严格小于 $A_9^9=9!=362880$，并且时间限制居然有两秒，乱搞都能过。

## AC 代码
### C++
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[3][3];int n[3][3];
bool dfs(long long x,long long y,int d,int k){
	if(d++==9)return x>y;
	bool t=1;
	for(int i=0;i<3&&t;i++)for(int j=0;j<3&&t;j++)if(!n[i][j]){
		n[i][j]=k;
		if(n[i][0]==k&&n[i][1]==k&&n[i][2]==k){
			n[i][j]=0;return 1;
		}
		if(n[0][j]==k&&n[1][j]==k&&n[2][j]==k){
			n[i][j]=0;return 1;
		}
		if(i==j&&n[0][0]==k&&n[1][1]==k&&n[2][2]==k){
			n[i][j]=0;return 1;
		}
		if(i+j==2&&n[0][2]==k&&n[1][1]==k&&n[2][0]==k){
			n[i][j]=0;return 1;
		}
		t=t&&dfs(y,x+a[i][j],d,-k);
		n[i][j]=0;
	}
	return !t;
}
int main(){
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)scanf("%lld",&a[i][j]);
	puts(dfs(0,0,0,1)?"Takahashi":"Aoki");
	return 0;
}
```

---

## 作者：DFbd (赞：0)

## 题意
两个人下井字棋，下到哪加哪个格子的分，连成三子获胜，若无人连成三子，则分高获胜，输出胜者。

## 思路
由于只有九个格子，所以可以直接暴搜每一步下在哪。

用一个 $x$ 表示当前是第几步，$y$ 表示下的人是谁，$1$ 表示高桥，$2$ 表示青木，还要两个计数变量 $s_1$ 和 $s_2$ 分别表示两人得了多少分。

`dfs(int x, int y, int s1, int s2)` 表示 $y$ 表示的选手能不能赢，$1$ 表示能赢，$0$ 表示不能赢。

另外需要一个数组 $p$ 表示每一格被谁下了。

先判断是否有三子连线，还要判断走完了没有，如果走完了就比较分数。

转移的时候，把 $p_{i,j}$ 改为 $y$，根据是谁下的来加得分，并且把 $y$ 改成另一个人，再用一个变量来判断这个人能不能赢。

如果有任何一种转移方式能使当前人赢，则当前步他也能赢。

转移完了要记得回溯。

更具体的请看代码。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[5][5], p[5][5];
bool dfs(int x, int y, int s1, int s2) {
  if (p[2][2] && (p[1][1] == p[2][2] && p[2][2] == p[3][3] || p[1][3] == p[2][2] && p[2][2] == p[3][1] || p[2][1] == p[2][2] && p[2][2] == p[2][3] || p[1][2] == p[2][2] && p[2][2] == p[3][2])) return p[2][2] == y;
  if (p[1][1] && (p[1][1] == p[1][2] && p[1][2] == p[1][3] || p[1][1] == p[2][1] && p[2][1] == p[3][1])) return p[1][1] == y;
  if (p[3][3] && (p[3][1] == p[3][2] && p[3][2] == p[3][3] || p[1][3] == p[2][3] && p[2][3] == p[3][3])) return p[3][3] == y; //这是判断是否三子连线，由于作者太蒟，写了好长
  if (x > 9) return s1 <= s2; //步数到了九步，比较分数
  bool f = 0; //判断当前人能不能赢
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) { //转移
      if (!p[i][j]) {
        p[i][j] = y;
        f |= !dfs(x + 1, 3 - y, s1 + (y == 1) * a[i][j], s2 + (y == 2) * a[i][j]); //3-y表示另一个人，如果这一种转移能赢，则这个人这一步就能赢
        p[i][j] = 0; //回溯
      }
    }
  }
  return f;
}
signed main() {
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      cin >> a[i][j];
    }
  }
  if (dfs(1, 1, 0, 0))
    cout << "Takahashi";
  else
    cout << "Aoki";
  return 0;
}
```

---

## 作者：incra (赞：0)

### Sol
细节有点多的爆搜题。

设 `DFS(u,wa,wb)` 表示当前要放棋的人是 $u\bmod 2$（是 $0$ 就是第一个人，是 $1$ 就是第二个人），之前先手和后手的权值和分别是 $wa,wb$，返回先手会不会必胜（不必胜则必败）。

若棋盘下满了还没有三颗连续的棋子，那么就返回 $[wa>wb]$。

否则，在下棋前判断是否有了连续的棋子，若有，返回连续的人是谁。

接着开始枚举当前执棋的人下在哪里，此时返回值分类讨论：

- 若当前执棋的是先手，那么只要有**一个**必胜的下法，那么先手必胜，否则必败。
- 若当前执棋的是后手，那么只有后手不论怎么下，后手必败，先手才必胜，否则必败。

### Code
[Link](https://atcoder.jp/contests/abc349/submissions/52338393)。

---

## 作者：wenlebo (赞：0)

我们要考虑什么情况一定能赢。

如果你是正在下棋的某一个人（两个人都很聪明，所以哪一个无所谓），下一步棋有三种情况取得胜利：

1. 这步棋下完可以连成三线

1. 这步棋下完产生平局，并且你的分高

1. 这步棋下完给对方下时，对方无法找到必胜下棋位置（必败）。

如果某个位置不能取胜，那就换另一个没下过的。

如果你无法找到一个能满足这三种胜利方法的下棋位置，你必败！

所以我们利用上面的规则，每次判断此时下的人（“先手”）在当前情况是否必胜，让后交换双方，让后者下。

不用担心平局，因为题目告诉你分数的和是奇数。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[4][4];
int p[4][4];
int des=0;
int jg;
/*
a 代表格中分数
p 代表棋局状态 1 是 Takahashi 的 2 反之
des 是我瞎起的名字，指填好的格子
jg 结果，用于 ch() 
*/
void ch(){
//判断结果 
	jg=0;
	for(int i=1;i<=3;i++){
		if(p[i][1]==p[i][2]&&p[i][2]==p[i][3]&&p[i][1]){
			jg=p[i][1];
			return;
		}
	}
	for(int i=1;i<=3;i++){
		if(p[1][i]==p[2][i]&&p[2][i]==p[3][i]&&p[1][i]){
			jg=p[1][i];
			return;
		}
	}
	if(p[1][1]==p[2][2]&&p[2][2]==p[3][3]&&p[1][1]){
		jg=p[1][1];
		return;
	}
	if(p[1][3]==p[2][2]&&p[2][2]==p[3][1]&&p[1][3]){
		jg=p[1][3];
		return;
	}
	return;
}
bool wi(int xs,int hs,long long pa,long long pb){
	//xs 是当前下的 hs 反之 pa 是 xs 得分 pb 反之 
	//意思是当前下者能否在当前局面中获胜 
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			if(p[i][j]==0){//是空的 
				p[i][j]=xs;
				jg=0;
				des++;
				ch();
				if(jg==xs){//一情况 
					p[i][j]=0;
					des--;
					return 1;
				}
				if(jg==hs){//没用 
					p[i][j]=0;
					des--;
					continue;
				}
				if(des==9){
					if(pa+a[i][j]>pb){//二情况 
						p[i][j]=0;
						des--;
						return 1;
					}else{    //分没比过 
						p[i][j]=0;
						des--;
						continue;
					}
				}
				if(wi(hs,xs,pb,pa+a[i][j])==1){
								//对手没输 
					p[i][j]=0;
					des--;
					continue;
				}else{			//三情况，让对手输就是我赢了
					p[i][j]=0;
					des--;
					return 1;
				}
			}
		}
	}
	return 0;
}
int main(){
	for(int i=1;i<=3;i++){
		for(int j=1;j<=3;j++){
			cin>>a[i][j];
		}
	}
	if(wi(1,2,0,0)){
		cout<<"Takahashi";
	}else{
		cout<<"Aoki";
	}
	return 0;
}

```

---

