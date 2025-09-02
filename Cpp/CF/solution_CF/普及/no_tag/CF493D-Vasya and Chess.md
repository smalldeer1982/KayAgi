# Vasya and Chess

## 题目描述

Vasya decided to learn to play chess. Classic chess doesn't seem interesting to him, so he plays his own sort of chess.

The queen is the piece that captures all squares on its vertical, horizontal and diagonal lines. If the cell is located on the same vertical, horizontal or diagonal line with queen, and the cell contains a piece of the enemy color, the queen is able to move to this square. After that the enemy's piece is removed from the board. The queen cannot move to a cell containing an enemy piece if there is some other piece between it and the queen.

There is an $ n×n $ chessboard. We'll denote a cell on the intersection of the $ r $ -th row and $ c $ -th column as $ (r,c) $ . The square $ (1,1) $ contains the white queen and the square $ (1,n) $ contains the black queen. All other squares contain green pawns that don't belong to anyone.

The players move in turns. The player that moves first plays for the white queen, his opponent plays for the black queen.

On each move the player has to capture some piece with his queen (that is, move to a square that contains either a green pawn or the enemy queen). The player loses if either he cannot capture any piece during his move or the opponent took his queen during the previous move.

Help Vasya determine who wins if both players play with an optimal strategy on the board $ n×n $ .

## 说明/提示

In the first sample test the white queen can capture the black queen at the first move, so the white player wins.

In the second test from the statement if the white queen captures the green pawn located on the central vertical line, then it will be captured by the black queen during the next move. So the only move for the white player is to capture the green pawn located at $ (2,1) $ .

Similarly, the black queen doesn't have any other options but to capture the green pawn located at $ (2,3) $ , otherwise if it goes to the middle vertical line, it will be captured by the white queen.

During the next move the same thing happens — neither the white, nor the black queen has other options rather than to capture green pawns situated above them. Thus, the white queen ends up on square $ (3,1) $ , and the black queen ends up on square $ (3,3) $ .

In this situation the white queen has to capture any of the green pawns located on the middle vertical line, after that it will be captured by the black queen. Thus, the player who plays for the black queen wins.

## 样例 #1

### 输入

```
2
```

### 输出

```
white
1 2
```

## 样例 #2

### 输入

```
3
```

### 输出

```
black
```

# 题解

## 作者：codeLJH114514 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/CF493D)

# 题目大意

在 $n \times n$ 的棋盘上，有白后和黑后（国际象棋）分别在 $(1, 1)$ 和 $(1, n)$，其余全是中立的兵，白方先手，问谁能必胜 ?

# 解题思路

## 结论

若 $n$ 为偶数，先手必胜。若 $n$ 为奇数，后手必胜。

## 证明

### case 1： $n$ 为奇数

|白|兵|兵|兵|黑|
|:-:|:-:|:-:|:-:|:-:|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|

无论白怎么走，黑都可以模仿白，比如白走到 $(1, 2)$，黑就走到 $(1, n - 1)$

||白|兵|兵|黑|
|:-:|:-:|:-:|:-:|:-:|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|

||白|兵|黑||
|:-:|:-:|:-:|:-:|:-:|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|
|兵|兵|兵|兵|兵|

如果白走到了最中间的那一列(即第 $\frac{n + 1}{2}$ 列)时，由于黑一直是白的镜像，所以黑一定在白的那一列，所以黑一定能吃掉白。

|||兵|||
|:-:|:-:|:-:|:-:|:-:|
|兵||兵||兵|
|兵||兵||兵|
||白|兵|黑||
|兵|兵|兵|兵|兵|

|||兵|||
|:-:|:-:|:-:|:-:|:-:|
|兵||兵||兵|
|兵||兵||兵|
|||白|黑||
|兵|兵|兵|兵|兵|

### case 2: $n$ 为偶数

这个很简单，只要白先走到 $(1, 2)$，然后就跟之前一模一样了，由于是镜像，所以白不会在走到第 $1$ 列了!（最后一行不影响）

||白|兵|兵|兵|黑|
|:-:|:-:|:-:|:-:|:-:|:-:|
|兵|兵|兵|兵|兵|兵
|兵|兵|兵|兵|兵|兵
|兵|兵|兵|兵|兵|兵
|兵|兵|兵|兵|兵|兵
|兵|兵|兵|兵|兵|兵

所以当 $n$ 为偶数的时候，白只要走到 $(1, 2)$ 就可以必胜，而且这样还满足题目中 "如果有多解，请输出 $r$ 最小的解，如果还有多解，请输出 $c$ 最小的解" 的要求。

# 代码

说了这么多了，其实核心代码就一行。

```cpp
cout << (n & 1 ? "black" : "white\n1 2");
```

AC 代码

```cpp
#include <iostream>
using namespace std;
int n;
int main() {
    cin >> n;
    cout << (n & 1 ? "black" : "white\n1 2"); // 核心判断
    return 0;
}
```

---

## 作者：issue_is_fw (赞：2)

$当n为奇数时,后手必胜$

$因为后手可以一直模仿先手走$

$比如白字从(1,1)走到(1,2),那么黑子就从(1,n)走到(1,n-1)$

$这样一直模仿先手走,知道先手走到第n/2+1列$

$由于之前后手都是对称走的,所以这一步可以直接吃掉它$

<br/>

$}当n是偶数时,先手必胜$

$因为先手第一步可以走到(2,1)位置$

$此时不论后手怎么走,先手都可以模仿后手走,就是上面的情况$

$注意到之后的步骤先手怎样都不会走到第一列去了,因为是对称走$

$所以减去这列,回到了n是奇数的情况,先手必胜$

```
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;  cin >> n;
	cout << (n%2==0?"white\n1 2":"black");
}
```

---

## 作者：时间次元 (赞：1)

这是一道比较毒瘤的题

可以注意到，n的范围极大，基本确定算法复杂度O(1)或O(n)

只要想到一个点，黑方可以模仿白方行动

若n为偶数，则最后一定是白方动不了

若n为奇数，白方只需走到（2,1），就可以让黑方落入前文中白方的境地，于是就解决了

### 代码
```cpp
#include <cstdio>

using namespace std;

int main(){
    int n; scanf("%d", &n);
    if (n & 1) printf("black\n");
    else printf("white\n1 2\n");
    return 0;
}
```

第一次发题解求过~

---

## 作者：I_have_been_here (赞：0)

# 题目分析

一眼博弈论问题。对于这种简单博弈论，我们可以直接针对问题本身入手想结论，这题也不例外，重要的参数仅仅是 $n$ 一个，针对 $n$ 即可。

# 思路解析

现在我们拿到了一个长度为 $n$ 的棋盘，我们现在考虑如果白皇后能赢的情况：

- 如果 $n$ 为偶数：

我们可以将这个棋盘砍成两半，每一边的长度为 $2$ 分之 $n$, 那么决出胜负的时候是什么时候呢，无疑是白皇后和黑皇后挨着的时候，如果双方都按最优策略，当双方在砍成砍成两半的分界线上时，因为是白色先手，所以它可以一步吃掉黑皇后。

- 如果 $n$ 为奇数：

现在我们可以知道分界线仅仅只有一条，而且都按最优策略，谁站在这上面谁就没了，因为我们可以看作它俩在镜像移动，而白色是先手，所以说无论如何，在它吃完自己这一半的棋子之前，它会先走上这条分界线，这时黑色就赢了。

# AC CODE

```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int n;
int main() {
	cin >> n;
	if (n % 2 == 0) {
		puts("white");
		puts("1 2");
	}
	else {
		puts("black");
	}
}
```


---

## 作者：Fearliciz (赞：0)

又是一道小奥题。

#### 题目大意：

翻译很良心了，点赞。

有一个 $n \times n$ 的国际象棋棋盘。将白后放在 $(1,1)$，黑后放在 $(1,n)$，其余位置全都是中立的卒。
双方交替移动。白方先手。
每次移动，后可以朝八个方向（上下左右对角线）之一移动任意格，直到碰到另外一个棋子，然后吃掉这个棋子。注意，在本题中，每次移动必须吃掉一个棋子。
当你的皇后被吃了或者你没有棋子可以吃了，就输了。
给出棋盘大小，请问哪方会赢。

+ 如果黑方会赢，请输出 `black`。

+ 如果白方会赢，请输出 `white`，并在下一行输出两个整数 $r,c$，表示白方第一步应该移动到哪里才能保证胜利。如果有多解，请输出 $r$ 最小的解，如果还有多解，请输出 $c$ 最小的解。

#### 解题思路：

这种必胜策略的题，就一定要考虑到一点：模仿。

不难看出：

由于白先手，所以

- 当走的步数为奇数的时候，即 $n$ 为奇的时候，黑方有必胜策略。

只要黑方不断模仿白方，所以最后就可以吃掉白后。

- 当走的步数为偶数的时候，即 $n$ 为偶的时候，白方有必胜策略。

同理，只要不断模仿黑方，由于白方先手，就可以最后吃掉黑后。

想到这里，核心部分就过去了，只剩下一些简单的分析。

由于题目中说：

	
如果白方会赢，请输出 `white`，并在下一行输出两个整数 $r,c$，表示白方第一步应该移动到哪里才能保证胜利。如果有多解，请输出 $r$ 最小的解，如果还有多解，请输出 $c$ 最小的解。

因为原本白方在 $(1,1)$ 的位置，所以可移动的位置有 $(1,2)$、$(2,2)$、$(2,1)$，所以为了使 $r$ 最小，白方第一步走到 $(1,2)$ 的位置上。

#### 代码：

```cpp
#include<stdio.h>
int main()
{
	int n;
	scanf("%d",&n);
	if(n%2==0) printf("white\n1 2");
	else printf("black");
	return 0; //好习惯
}
```

总结：遇到必胜策略的题目，先考虑模仿。


---

## 作者：BotDand (赞：0)

# Problems
有一个  $n\times n$  的国际象棋棋盘。将白后放在  $(1,1)$ ，黑后放在  $(1,n)$  ，其余位置全都是中立的卒。  
双方交替移动。白方先手。  
每次移动，后（Queen）可以朝八个方向（上下左右对角线）之一移动任意格，直到碰到另外一个棋子，然后吃掉这个棋子。注意，在本题中，每次移动必须吃掉一个棋子。  
当你的皇后被吃了或者你没有棋子可以吃了，就输了。  
给出棋盘大小，请问哪方会赢。
- 如果黑方会赢，请输出 `black`。
- 如果白方会赢，请输出 `white`，并在下一行输出两个整数  $r,c$ ，表示白方第一步应该移动到哪里才能保证胜利。如果有多解，请输出  $r$  最小的解，如果还有多解，请输出  $c$  最小的解。

# Answer
观察$n$的数据范围：$2 \le n \le 10^9$，不难想到是要找规律的。

于是分两种情况：

1. $n$为奇数，则白棋最后一定是走不了了，黑棋赢；

1. $n$为偶数，则黑棋最后一定是走不了了，白棋赢，白棋只需要走到$(1,2)$将黑卒吃掉一个即可。

# Code
```pascal
var
  n:int64;
begin
  readln(n);//读入n
  if odd(n) then writeln('black')//如果n是奇数，则输出black
    else begin writeln('white');writeln('1 2');end;//反正输出white和1 2
end.
```

---

## 作者：LRL65 (赞：0)

思路：

当 $n$ 为偶数的时候，$n^2$ 也为偶数，这时因为白先手，所以白黑白黑……，**最后刚好为：……白黑**。**这时下一个为白，白就可以吃掉黑了**，所以输出white。第一步因为得选行小的，其次列小的，那就是（1，2）。

当 $n$ 为奇数的时候，$n^2$ 也为奇数，这时因为白先手，所以白黑白黑……，**最后为：……白黑白**。**这时下一个为黑，黑就可以吃掉白了**，所以输出black。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n; 
int main() {
	cin>>n;
	if(n%2==0)cout<<"white"<<endl<<1<<" "<<2<<endl;
	else cout<<"black"<<endl;
	return 0;
}
```


---

## 作者：zhuchengyang (赞：0)

1. 假如你是先手，且棋盘边长为奇数，那么你先往右走一步，然后一直模仿对方走，然后你就赢了。
2. 假如你是后手，且棋盘边长为奇数，那么对手就会先往右走一步，然后一直模仿你走，然后你就输了。
3. 假如你是先手，且棋盘边长为偶数，对方一直模仿你走，然后你就输了。
4. 假如你是后手，且棋盘边长为偶数，你一直模仿对方走，然后你就赢了。

附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<((n%2==1)?"black\n":"white\n1 2\n");
    return 0;
}
```

---

## 作者：skywang (赞：0)

## 题意
```txt
	有一个n×n棋盘。(1,1)包含白皇后, (1,n)包含黑皇后。其他每一个格子都包含一个小兵。
	两个皇后依次移动（白皇后先）。
	每次移动时，皇后必须吃掉一个妻子（就是移动到有小兵或敌方皇后的方块中)。
	如果玩家在移动过程中无法吃掉任何棋子，或者在之前的移动中王后被对方王后吃掉，那么他就会输。
	问谁必胜？
```
## 题解
```txt
	很明显，当n为偶数时，白胜，n为奇数时，黑胜。
	n为偶数时，白可以先走到（1，n/2）,而黑不能走到（1，n/2+1）（会被吃）然后白一路往下走，一定战胜黑
	n为奇数时，白和黑都按最优策略走时，中间一列会被空出，(谁走到谁就会被吃掉）。而白先走，所以白先会被困死，故黑赢
```
## 调试记录
### 水，一遍A
```cpp
#include <iostream>
using namespace std;
int main(){
	int n;
	cin>>n;
	if (n%2==0) {
		cout<<"white"<<endl;
		cout<<"1 2"<<endl; 
	}else{
		cout<<"black"<<endl;
	}
}
```

---

## 作者：情非昔比 (赞：0)

## 题目大意：
		n*n的棋盘中，有一个白皇后在（1,1）位置。有一个黑皇后在（1，n）位置。其余位置全都是中立的小兵。每次必须吃一个小兵或者皇后。当你的皇后被吃了或者你没有棋子可以吃了，你就输了。问白赢还是黑赢。
## 解题思路：
		这道题可以按照对称的思想。
    	- 当n为偶数时，你走一步到（1,2），对方最优可以对称着你走。那当你走到第n/2列时，对方就在n/2+1列。此时此刻你就可以直接把对方吃了。
    	- 当n为奇数时，你先走到（1,2）的位置上。此时就相当于变成了对方先手，n为偶数的情况。那么你就输了。
## 调试记录：这题肯定一次AC的啦
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
	scanf("%d",&n);
	if(n%2==1) printf("black\n");
	else printf("white\n1 2\n");
	return 0;
}
```

---

