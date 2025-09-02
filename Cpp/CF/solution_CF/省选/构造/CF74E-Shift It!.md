# Shift It!

## 题目描述

There is a square box $ 6×6 $ in size. It contains $ 36 $ chips $ 1×1 $ in size. Those chips contain 36 different characters — "0"-"9" and "A"-"Z". There is exactly one chip with each character.

You are allowed to make the following operations: you may choose one of $ 6 $ rows or one of $ 6 $ columns and cyclically shift the chips there to one position to the left or to the right (for the row) or upwards or downwards (for the column). Those operations are allowed to perform several times.

To solve the puzzle is to shift the chips using the above described operations so that they were written in the increasing order (exactly equal to the right picture). An example of solving the puzzle is shown on a picture below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF74E/0a3a314e2a091acebeaa1e063e0064f39d2f8755.png)Write a program that finds the sequence of operations that solves the puzzle. That sequence should not necessarily be shortest, but you should not exceed the limit of $ 10000 $ operations. It is guaranteed that the solution always exists.

## 样例 #1

### 输入

```
01W345
729AB6
CD8FGH
IJELMN
OPKRST
UVQXYZ
```

### 输出

```
2
R2
U3
```

# 题解

## 作者：NobodyThere (赞：6)

萌萌构造题。

来一个操作次数比较优秀的做法。

这里设 $n=6$ 为正方形的边长，$m\leq10^4$ 为操作次数。**注意以下的讨论是基于 $n=6$ 进行的。**

一个简单的想法是先复原左上角 $(n-1)\times(n-1)$ 的元素，这个复原是简单的：

1. 如果这个元素在复原后所在的那一行，则将其移到最后一列，然后将其移出。
1. 此时元素不在复原后所在的那一行，那么可以将那一行已复原的元素「对齐」最后一列，然后将元素拼回去。

这个过程可以类比魔方。

那么就只剩最后一行和最后一列的元素了。

容易发现，除去最后两个元素外，也一样可以简单地复原：

1. 首先先复原最后一列的前 $n-2$ 个元素，过程与上述类似。
1. 然后复原最后一行的前 $n-1$ 个元素，利用上先前在最后一列留出的两个空位，也可以同样进行上述的复原方式。

最后的问题就是复原 $(n-1,n)$ 和 $(n,n)$ 两个元素了。

通过包括但不限于打表、手玩、发挥人类智慧推导、类比魔方复原等方式，可以发现交换这两个元素是容易的，只需对最后一行（列）进行：

$\begin{matrix}\underbrace{\texttt{URUL}\cdots\texttt{URUL}}&\texttt{URUUL}\\\text{重复 }\frac{n}{2}-1\text{ 次}\end{matrix}$

或者

$\begin{matrix}\texttt{RDDLD}&\underbrace{\texttt{RDLD}\cdots\texttt{RDLD}}\\&\text{重复 }\frac{n}{2}-1\text{ 次}\end{matrix}$

这样的操作就可以了。（以上两种操作本质上没有区别，一个是将另一个反着做的结果）

由于前 $(n-1)\times(n-1)$ 个元素的复原操作数不会超过 $\frac{3}{2}n$ 次，剩余的除最后两个数之外的元素的复原操作数不超过 $n+2$ 次，最后交换两个数需要 $2n+1$ 次操作，由此可以粗略估计 $m<\frac{3}{2}n^3$，精细一点的分析可以得到 $n=6$ 时有 $m<300$；而且这个估计是跑不满的。CF 上甚至只用了不到 $200$ 次操作。

代码及提交记录：<https://codeforces.com/contest/74/submission/236595301>。

这题还能拓展到任意的 $n$：

当 $n$ 是偶数时，与上面的分析是一致的。

当 $n$ 是奇数时，可能无解，充要条件可以类比排列的奇偶性，当且仅当给定的矩阵是「偶」的时候有解。考虑以上过程，那么最后两个数要么无法被复原，要么已经被复原。

一个思考题：如果每次循环位移不限制位移距离，那么你能找到更优秀的解法吗？

结语：魔方题。

嘛，虽然我对魔方不甚熟悉就是了。

---

## 作者：zac2010 (赞：3)

### 题目类型

很妙的构造题，要写出较优的解也会考验一些码量。

### 解法

对于下文中的坐标 $(i,j)$，$i$ 表示行，$j$ 表示列。

我们考虑对一个固定的位置 $(i,j)$ 进行如下操作：上右下左上。

会发现 $(i,j)$ 位置上的字符和 $(i,j+1)$ 上的交换了，同时 $j$ 这一列的其它字符也进行了向上的循环位移。

所以我们只要做 $n-1$ 次，就可以把这一列的其它元素归回原位，并且 $(i,j)$ 上的字符还和 $(i,j+1)$ 上的交换了位置（$n-1$ 是奇数）。这需要花费 $5n-5$ 次循环位移。

这是左右交换的，上下交换也类似。故而我们得到了交换任意相邻元素的方案。

这时只需要像冒泡排序一样，通过交换相邻的使得最终元素一个个去到该去的位置。

我的代码采用的是逐行还原，能通过。[code](https://codeforces.com/contest/74/submission/211708776)。

### 优化解法 $1$

我们没有必要进行 $n-1$ 次，因为我们进行移位的时候可能会破坏其他行已经归位的元素的位置，所以我们每移动一次，就把破坏掉的那个再进行循环移位复原一下即可。

### 优化解法 $2$

让前 $n-1$ 行的先去到最终位置（交换元素过程中的“上右下左上”只进行 $1$ 次，不是 $n-1$ 次），最后一行通过上述解法中的方法交换得到最终棋盘。

实现相对复杂。

---

## 作者：Expert_Dreamer (赞：0)

一道很好的构造题。有点像魔方，又有点像数字华容道。可以说是[这道题](https://www.acwing.com/problem/content/183/)的加强版。

### 题目大意
一个 $6 \times 6$ 的矩阵。通过多次操作使矩阵变成
```
012345
6789AB
CDEFGH
IJKlMN
OPQRST
UVWXYZ
```
### 思路
有一个魔方公式：上右下左上，能将魔方左右相邻的两个块互换，考虑本题的性质可以用这种方法做。我们以 $map_{4,3}$ 为例，如图：
```cpp
交换前
  a   
  b   
  c   
defghi
  j
  k
```
```cpp
上
  b   
  c   
  f   
dejghi
  k
  a
```
```cpp
右
  b   
  c   
  f   
idejgh
  k
  a
```
```cpp 
下
  a   
  b   
  c   
idfjgh
  e
  k
```
```cpp
左
  a   
  b   
  c   
dfjghi
  e
  k
```
```  cpp
上
  b   
  c   
  j   
dfeghi
  k
  a
```
这样 $f,e$ 就互换了。

但是有一个问题，如果 $map_{x,y}$ 通过这种方法和 $map_{x,y+1}$ 互换，那么第 $y$ 列整列都会向上移动。解决方法就是移动 $5$ 次，这样 $map_{x,y}$ 和 $map_{x,y+1}$ 互换就不会有任何影响（比其他做法花的步骤多很多，但是题目要求的 $10000$ 次绰绰有余）。

左右能交换，第二个问题就是上下交换，我们只要像左右交换一样，做 $5$ 次右下左上右。

左右交换，上下交换，那不就是一开始的数字华容道吗？于是我们用华容道的思想，一层一层还原就行了。

ACcode:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n=6;
char a[7][7],target[7][7]={
{' ',' ',' ',' ',' ',' ',' '},
{' ','0','1','2','3','4','5'},
{' ','6','7','8','9','A','B'},
{' ','C','D','E','F','G','H'},
{' ','I','J','K','L','M','N'},
{' ','O','P','Q','R','S','T'},
{' ','U','V','W','X','Y','Z'}
};
vector<pair<char,int>>ans;
void R(int &x){//右移
    for(int i=n+1;i>=2;i--) a[x][i]=a[x][i - 1];
    a[x][1]=a[x][n+1],ans.push_back({'R',x});
}
void L(int &x){//左移
    for(int i=0;i<n;i++) a[x][i]=a[x][i + 1];
    a[x][n]=a[x][0],ans.push_back({'L',x});
}
void U(int &x){//上移
    for(int i=0;i<n;i++) a[i][x]=a[i + 1][x];
    a[n][x]=a[0][x],ans.push_back({'U',x});
}
void D(int &x){//下移
    for(int i=n+1;i>=2;i--) a[i][x]=a[i-1][x];
    a[1][x]=a[n+1][x],ans.push_back({'D',x});
}
int main(){
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cin>>a[i][j];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int x,y,flag=0;
            for(int k=1;k<=n;k++){
                if(flag) break;
                for(int t=1;t<=n;t++){
                    if(a[k][t]==target[i][j]){
                        flag=1,x=k,y=t;
                        break;
                    }
                }
            }
            while(y<j){
                for(int i=2;i<=n;i++) U(y),L(x),D(y),R(x),U(y);//做左右交换的公式
                y++;
            }
            while(y>j){
                y--;
                for(int i=2;i<=n;i++) U(y),L(x),D(y),R(x),U(y);
            }
            while(x>i) R(x),D(y),L(x),U(y),R(x),x--;//做上下交换的公式
        }
    }
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++) cout<<ans[i].first<<ans[i].second<<endl;
}
```

---

