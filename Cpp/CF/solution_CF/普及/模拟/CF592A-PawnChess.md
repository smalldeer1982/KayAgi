# PawnChess

## 题目描述

Galois is one of the strongest chess players of Byteforces. He has even invented a new variant of chess, which he named «PawnChess».

This new game is played on a board consisting of 8 rows and 8 columns. At the beginning of every game some black and white pawns are placed on the board. The number of black pawns placed is not necessarily equal to the number of white pawns placed.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592A/9900e176569f519565c0c8328f093726ce1eb9d2.png)Lets enumerate rows and columns with integers from 1 to 8. Rows are numbered from top to bottom, while columns are numbered from left to right. Now we denote as $ (r,c) $ the cell located at the row $ r $ and at the column $ c $ .

There are always two players A and B playing the game. Player A plays with white pawns, while player B plays with black ones. The goal of player A is to put any of his pawns to the row $ 1 $ , while player B tries to put any of his pawns to the row $ 8 $ . As soon as any of the players completes his goal the game finishes immediately and the succeeded player is declared a winner.

Player A moves first and then they alternate turns. On his move player A must choose exactly one white pawn and move it one step upward and player B (at his turn) must choose exactly one black pawn and move it one step down. Any move is possible only if the targeted cell is empty. It's guaranteed that for any scenario of the game there will always be at least one move available for any of the players.

Moving upward means that the pawn located in $ (r,c) $ will go to the cell $ (r-1,c) $ , while moving down means the pawn located in $ (r,c) $ will go to the cell $ (r+1,c) $ . Again, the corresponding cell must be empty, i.e. not occupied by any other pawn of any color.

Given the initial disposition of the board, determine who wins the game if both players play optimally. Note that there will always be a winner due to the restriction that for any game scenario both players will have some moves available.

## 说明/提示

In the first sample player A is able to complete his goal in 3 steps by always moving a pawn initially located at $ (4,5) $ . Player B needs at least 5 steps for any of his pawns to reach the row $ 8 $ . Hence, player A will be the winner.

## 样例 #1

### 输入

```
........
........
.B....B.
....W...
........
..W.....
........
........
```

### 输出

```
A
```

## 样例 #2

### 输入

```
..B.....
..W.....
......B.
........
.....W..
......B.
........
........
```

### 输出

```
B
```

# 题解

## 作者：RE_Prince (赞：2)

# PawnChess 


模拟题。


[link](https://www.luogu.com.cn/problem/CF592A)
## Sol

先考虑一个简化版的题目：如果保证没有两个兵在同一列上，题目是不是就好做了？不停地枚举每一列，判断列上的兵是白是黑。如果是白，那就取答案和 $j-1$ 的 $\min$，如果是黑，那就取答案和 $9-j$ 的 $\min$。


好了，回到原题上，怎么处理两个或多个兵在同一列的情况呢？

很简单，根据颜色来决定内层枚举的顺序。如果计算黑兵时（反向枚举）遇到了一个白，直接结束，因为那个白色棋子怎么也躲不开上面的黑色棋子，就会撞上。白色也是同理。在遇到这种情况之前，统计答案。


具体见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,k;
char a[109][109];
signed main()
{
	for(i=1;i<9;i++)
		for(j=1;j<9;j++) cin>>a[i][j];
	int mp1=1e9,mp2=1e9;//赋一个极大的值
	for(j=1;j<9;j++)
		for(i=8;i>=1;i--)//注意，反向枚举，因为白兵是往上走的
			if(a[i][j]=='W') break;
			else if(a[i][j]=='B') mp1=min(mp1,9-i);//统计黑兵最小步数
	for(j=1;j<9;j++)
		for(i=1;i<9;i++)
			if(a[i][j]=='B') break;
			else if(a[i][j]=='W') mp2=min(mp2,i-1);//白兵最小步数
	if(mp2<mp1) cout<<"A";//判断谁赢
	else cout<<"B";
	return 0;
}
```

---

## 作者：_Execution_ (赞：1)

## 思路
枚举每一列，如果堵死了就不考虑，否则由外至内计算最小的步数，较小的一方获胜。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define INF 0x7fffffff
using namespace std;
int n,m,i,j,k;
int min1=INF,min2=INF ;
char maps[109][109];
signed main(){
	for(i=1;i<9;i++){
		for(j=1;j<9;j++){
			cin>>maps[i][j];
		}
	}
	for(j=1;j<9;j++){
		for(i=8;i>=1;i--){
			if(maps[i][j]=='W'){
				break;
			}
			else if(maps[i][j]=='B'){
				min1=min(min1,9-i);
			}
		}
	}
	for(j=1;j<9;j++){
		for(i=1;i<9;i++){
			if(maps[i][j]=='B'){
				break;
			}
			else if(maps[i][j]=='W'){
				min2=min(min2,i-1);
			}
		}
	}
	if(min2<min1){
		cout<<"A";
	}
	else{
		cout<<"B";
	}
	return 0;
}
```

---

## 作者：Terry2011 (赞：0)

# 题目分析

1. 本题需要输入一个 $8$ 行 $8$ 列的棋盘，我们可以通过一个二维的字符数组来存储。
1. 因为数据保证不会出现堵死的情况，所以，我们可以放心地去通过循环分别遍历两遍棋盘：一次是以白棋的角度，另一次是黑棋。
1. 在这里，我们可以分别声明两个变量，分别统计白兵和黑兵最小步数。最后比较大小即可。

# code
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[10][10];
int main(){
	for(int i=1;i<=8;i++){
        for(int j=1;j<=8;j++){
            cin>>a[i][j];//输入
		 }
    }
	int min1=2e9,min2=2e9;//定义最值（打擂台）
	for(int j=1;j<=8;j++){
        for(int i=8;i>=1;i--){//白棋要倒着走
            if(a[i][j]=='W') break;//一定要写！
			else if(a[i][j]=='B') min1=min(min1,9-i);//更新
        }
    }
	for(int j=1;j<=8;j++){
        for(int i=1;i<=8;i++){
		    if(a[i][j]=='B') break;
			else if(a[i][j]=='W') min2=min(min2,i-1);
		}
    }
    char a=min1>min2?'A':'B';
    cout<<a;	
	return 0;
}
```

---

## 作者：LazYQwQ (赞：0)

## 题意简述
- 输入一个 $8 \times 8$ 的棋盘，代表棋盘的布局。

- 选手 $A$ 执白棋，选手 $B$ 执黑棋，且白棋先手。黑方向棋盘下方(第八行) 行棋，白方向棋盘上方(第一行)行棋，先行棋至自己目标行的一方胜利
- 约定以 `W` 代表白棋，以 `B` 代表黑棋，只有当自己棋子向目标方向的前一格位置上没有棋子时才能行棋。
- 若选手 $A$ 胜利则输出 $A$，反之则输出 $B$。
- 数据保证不会出现堵死的情况。

## 解题思路
1. 首先按规则读入并预处理，若一个点为黑棋，则其下方的白棋将无法到达其上方，若一个点为白棋，则其上方的黑棋将无法到达其下方。

2. 再进行一次遍历，若一点为黑棋，其前方无白棋阻挡，则黑方获胜的最少步数为当前节点所需步数与之前记录的最小步数间的最小值，白棋也做类似的判断。
3. 若黑棋所需步数最少，则黑方胜，由于白方先手的规则，若白方最小步数小于或等于黑方步数，则白方胜利。

## 参考代码如下
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	char c[10][10];
	int w[10][10],b[10][10];
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			cin>>c[i][j];
			if(c[i][j]=='W'){
				for(int k=1;k<=i;k++)
				w[k][j]=1;
		    }
			else if(c[i][j]=='B'){
				for(int k=8;k>=i;k--)
				b[k][j]=1;
		    }
		} 
	}
	int minw=10,minb=10;
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			if(b[i][j]!=1 and c[i][j]=='W')minw=min(minw,i);
			if(w[i][j]!=1 and c[i][j]=='B')minb=min(minb,8-i+1);
		} 
	}
	if(minw<=minb)cout<<"A";
	else cout<<"B";
	return 0;
}
```


---

