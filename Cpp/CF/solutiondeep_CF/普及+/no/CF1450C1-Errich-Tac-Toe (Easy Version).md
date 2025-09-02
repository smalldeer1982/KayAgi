# 题目信息

# Errich-Tac-Toe (Easy Version)

## 题目描述

The only difference between the easy and hard versions is that tokens of type O do not appear in the input of the easy version.

Errichto gave Monogon the following challenge in order to intimidate him from taking his top contributor spot on Codeforces.

In a Tic-Tac-Toe grid, there are $ n $ rows and $ n $ columns. Each cell of the grid is either empty or contains a token. There are two types of tokens: X and O. If there exist three tokens of the same type consecutive in a row or column, it is a winning configuration. Otherwise, it is a draw configuration.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450C1/39afc6239351b009b5f556b0fc6f685f7842a873.png) The patterns in the first row are winning configurations. The patterns in the second row are draw configurations. In an operation, you can change an X to an O, or an O to an X. Let $ k $ denote the total number of tokens in the grid. Your task is to make the grid a draw in at most $ \lfloor \frac{k}{3}\rfloor $ (rounding down) operations.

You are not required to minimize the number of operations.

## 说明/提示

In the first test case, there are initially three 'X' consecutive in the second row and the second column. By changing the middle token to 'O' we make the grid a draw, and we only changed $ 1\le \lfloor 5/3\rfloor $ token.

In the second test case, we change only $ 9\le \lfloor 32/3\rfloor $ tokens, and there does not exist any three 'X' or 'O' consecutive in a row or column, so it is a draw.

In the third test case, we change only $ 3\le \lfloor 12/3\rfloor $ tokens, and the resulting grid is a draw.

## 样例 #1

### 输入

```
3
3
.X.
XXX
.X.
6
XX.XXX
XXXXXX
XXX.XX
XXXXXX
XX.X.X
XXXXXX
5
XXX.X
.X..X
XXX.X
..X..
..X..```

### 输出

```
.X.
XOX
.X.
XX.XXO
XOXXOX
OXX.XX
XOOXXO
XX.X.X
OXXOXX
XOX.X
.X..X
XXO.O
..X..
..X..```

# AI分析结果

### 题目内容中文重写
# Errich-Tac-Toe（简单版本）

## 题目描述
简单版本和困难版本的唯一区别在于，简单版本的输入中不会出现类型为 O 的棋子。

Errichto 为了吓唬 Monogon，不让他夺走自己在 Codeforces 上的顶级贡献者位置，给了他以下挑战。

在一个井字棋网格中，有 $n$ 行和 $n$ 列。网格的每个单元格要么为空，要么包含一个棋子。棋子有两种类型：X 和 O。如果存在三个相同类型的棋子在一行或一列中连续出现，那么这就是一个获胜的局面。否则，就是一个平局局面。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450C1/39afc6239351b009b5f556b0fc6f685f7842a873.png) 第一行的图案是获胜局面。第二行的图案是平局局面。在一次操作中，你可以将一个 X 变成一个 O，或者将一个 O 变成一个 X。设 $k$ 表示网格中棋子的总数。你的任务是在最多 $\lfloor \frac{k}{3}\rfloor$（向下取整）次操作内使网格变成平局。

你不需要最小化操作次数。

## 说明/提示
在第一个测试用例中，最初第二行和第二列有三个连续的 'X'。通过将中间的棋子改为 'O'，我们使网格变成了平局，并且我们只改变了 $1\le \lfloor 5/3\rfloor$ 个棋子。

在第二个测试用例中，我们只改变了 $9\le \lfloor 32/3\rfloor$ 个棋子，并且不存在任何三个 'X' 或 'O' 在一行或一列中连续出现，所以这是一个平局。

在第三个测试用例中，我们只改变了 $3\le \lfloor 12/3\rfloor$ 个棋子，并且得到的网格是一个平局。

## 样例 #1
### 输入
```
3
3
.X.
XXX
.X.
6
XX.XXX
XXXXXX
XXX.XX
XXXXXX
XX.X.X
XXXXXX
5
XXX.X
.X..X
XXX.X
..X..
..X..
```

### 输出
```
.X.
XOX
.X.
XX.XXO
XOXXOX
OXX.XX
XOOXXO
XX.X.X
OXXOXX
XOX.X
.X..X
XXO.O
..X..
..X..
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是通过对矩阵进行染色，将 $(i, j)$ 染成 $(i + j) \bmod 3$，这样每行、每列的任意连续 3 个格子的颜色都不同。然后统计三种颜色中 X 的数量，选择数量最少的那种颜色，将该颜色对应的 X 全部改为 O，就可以保证在不超过 $\lfloor \frac{k}{3}\rfloor$ 次操作的情况下使网格变成平局。

### 所选题解
- **作者：Rainy7（5星）**
    - **关键亮点**：思路清晰，详细解释了染色的原理和选择最小次数颜色的原因，代码可读性高，注释详细。
    - **个人心得**：“多测不清空，爆零两行泪”，提醒了多组测试数据时清空变量的重要性。
- **作者：2huk（4星）**
    - **关键亮点**：思路简洁明了，通过图片直观展示了染色的结果，易于理解。
- **作者：nztyz（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，直接实现了核心思路。

### 重点代码
#### Rainy7 的代码
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
using namespace std;
int T,n;
char s[305][305],s2[305][305],s3[305][305];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s[i]+1);
            for(int j=1;j<=n;j++)
                s2[i][j]=s3[i][j]=s[i][j];
        }
        int m=0,cnt=0,cnt2=0,cnt3=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(s[i][j]!='X')continue;
                m++;
                if((i+j)%3==0)cnt++;
                if((i+j)%3==1)cnt2++;
                if((i+j)%3==2)cnt3++;
            }
        int x=min(cnt,min(cnt2,cnt3));
        if(x==cnt)
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    if(s[i][j]!='X')printf(".");
                    else if((i+j)%3==0)printf("O");
                    else printf("X");
                }
                printf("\n");
            } 
        }
        else if(x==cnt2){
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    if(s[i][j]!='X')printf(".");
                    else if((i+j)%3==1)printf("O");
                    else printf("X");
                }
                printf("\n");
            } 
        }
        else if(x==cnt3){
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=n;j++)
                {
                    if(s[i][j]!='X')printf(".");
                    else if((i+j)%3==2)printf("O");
                    else printf("X");
                }
                printf("\n");
            } 
        }
    }
    return 0;
}
```
**核心实现思想**：先读取输入的矩阵，然后统计三种颜色中 X 的数量，选择数量最少的颜色，将该颜色对应的 X 改为 O 并输出结果。

### 最优关键思路或技巧
- **染色思想**：通过对矩阵进行 $(i + j) \bmod 3$ 染色，保证每行、每列的任意连续 3 个格子的颜色都不同，从而避免出现连续 3 个相同类型的棋子。
- **贪心选择**：选择三种颜色中 X 数量最少的那种颜色进行修改，保证操作次数不超过 $\lfloor \frac{k}{3}\rfloor$。

### 可拓展之处
同类型题可能会增加棋子的类型、改变获胜条件或操作限制等。类似的算法套路可以应用于其他需要构造满足特定条件的矩阵或网格的问题。

### 洛谷题目推荐
- P1003 铺地毯
- P1012 拼数
- P1047 校门外的树

---
处理用时：47.43秒