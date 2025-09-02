# 题目信息

# Big Brush

## 题目描述

You found a painting on a canvas of size $ n \times m $ . The canvas can be represented as a grid with $ n $ rows and $ m $ columns. Each cell has some color. Cell $ (i, j) $ has color $ c_{i,j} $ .

Near the painting you also found a brush in the shape of a $ 2 \times 2 $ square, so the canvas was surely painted in the following way: initially, no cell was painted. Then, the following painting operation has been performed some number of times:

- Choose two integers $ i $ and $ j $ ( $ 1 \le i < n $ , $ 1 \le j < m $ ) and some color $ k $ ( $ 1 \le k \le nm $ ).
- Paint cells $ (i, j) $ , $ (i + 1, j) $ , $ (i, j + 1) $ , $ (i + 1, j + 1) $ in color $ k $ .

All cells must be painted at least once. A cell can be painted multiple times. In this case, its final color will be the last one.

Find any sequence of at most $ nm $ operations that could have led to the painting you found or state that it's impossible.

## 说明/提示

In the first test case, the solution is not unique. Here's one of them:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638D/a19f3f2204a2363bab52391bc42a7f1ff29f94cb.png)In the second test case, there is no way one could obtain the given painting, thus the answer is $ -1 $ .

## 样例 #1

### 输入

```
4 4
5 5 3 3
1 1 5 3
2 2 5 4
2 2 4 4```

### 输出

```
6
1 3 3
3 3 4
2 2 5
1 1 5
2 1 1
3 1 2```

## 样例 #2

### 输入

```
3 4
1 1 1 1
2 2 3 1
2 2 1 1```

### 输出

```
-1```

# AI分析结果

### 题目翻译
## 大刷子

### 题目描述
你发现了一幅画在大小为 $n \times m$ 画布上的画。画布可以表示为一个有 $n$ 行和 $m$ 列的网格。每个单元格都有某种颜色。单元格 $(i, j)$ 的颜色为 $c_{i,j}$。

在画的附近，你还发现了一把形状为 $2 \times 2$ 正方形的刷子，所以这幅画肯定是按以下方式绘制的：最初，没有一个单元格被上色。然后，以下绘画操作被执行了若干次：
- 选择两个整数 $i$ 和 $j$（$1 \le i < n$，$1 \le j < m$）以及某种颜色 $k$（$1 \le k \le nm$）。
- 将单元格 $(i, j)$、$(i + 1, j)$、$(i, j + 1)$、$(i + 1, j + 1)$ 涂成颜色 $k$。

所有单元格必须至少被涂一次。一个单元格可以被多次涂色。在这种情况下，它的最终颜色将是最后一次涂的颜色。

找出任何一个最多包含 $nm$ 次操作的序列，该序列可能导致你所发现的这幅画，或者声明这是不可能的。

### 说明/提示
在第一个测试用例中，解决方案不是唯一的。以下是其中一种：
![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638D/a19f3f2204a2363bab52391bc42a7f1ff29f94cb.png)
在第二个测试用例中，没有办法可以得到给定的这幅画，因此答案是 $ -1 $。

### 样例 #1
#### 输入
```
4 4
5 5 3 3
1 1 5 3
2 2 5 4
2 2 4 4
```
#### 输出
```
6
1 3 3
3 3 4
2 2 5
1 1 5
2 1 1
3 1 2
```

### 样例 #2
#### 输入
```
3 4
1 1 1 1
2 2 3 1
2 2 1 1
```
#### 输出
```
-1
```

### 算法分类
构造

### 综合分析与结论
这些题解的核心思路都是采用逆向思维，从最终的画布状态倒推初始状态，通过不断找出 $2\times 2$ 且颜色相同（或满足特定条件）的方块，将其标记并记录操作，最后判断是否能将所有格子都处理完来确定是否有解。

不同题解的主要区别在于实现方式，有的使用 BFS，有的使用 DFS，还有的使用递归。但整体的算法要点都是先找出初始的可处理方块，然后根据其影响去寻找周围可能的方块，直到无法继续或所有格子都被处理。

解决的难点在于如何高效地判断一个 $2\times 2$ 的方块是否满足条件，以及处理已标记格子和未标记格子的关系。

### 所选题解
- **wumingwei（5星）**
    - **关键亮点**：思路清晰，使用 BFS 实现，代码结构良好，注释详细，易于理解。
    - **个人心得**：无
- **enucai（4星）**
    - **关键亮点**：反向思考的思路明确，代码简洁，对细节的处理较为巧妙。
    - **个人心得**：考场上这题没想出来，确实是想歪了，掉大分。
- **Milmon（4星）**
    - **关键亮点**：详细阐述了倒推的解题策略，时间复杂度分析清晰，代码实现规范。
    - **个人心得**：无

### 重点代码
#### wumingwei 的核心代码
```c++
bool check(int x,int y)//判断是否可以染色 
{
    if(x>=1&&x<n&&y>=1&&y<m)//是否在范围内 
    {
        s=-1;
        for(int i=x;i<=x+1;i++)
        {
            for(int j=y;j<=y+1;j++)
            {
                if(a[i][j]!=-1&&s==-1)
                    s=a[i][j];
                else if(a[i][j]!=-1&&a[i][j]!=s)
                    return 0;
            }
        }
        return 1;
    }
    return 0;
}

void change(int x,int y)
{
    a[x][y]=a[x+1][y]=a[x][y+1]=a[x+1][y+1]=-1;//-1为无色 
}

//主函数部分
while(!q.empty())//dddd
{
    S now=q.front();
    q.pop();
    for(int i=0;i<8;i++)//枚举8个方向 
    {
        int nx=now.x+f[i][0];
        int ny=now.y+f[i][1];
        if(check(nx,ny)&&s!=-1&&!book[nx][ny])//s=-1就是4个皆空,无需染色,已经染色的也不需要 
        {
            book[nx][ny]=1;
            change(nx,ny);//改变 
            w.x=nx;
            w.y=ny;
            w.z=s;
            q.push(w);
            v.push_back(w);
        }
    }
}
```
**核心实现思想**：`check` 函数用于判断一个 $2\times 2$ 的方块是否可以染色，即方块内的非空格子颜色是否相同。`change` 函数将方块内的格子标记为无色。在主函数的 BFS 过程中，不断从队列中取出元素，检查其周围 8 个方向的方块，若满足条件则加入队列和答案数组。

#### enucai 的核心代码
```cpp
void paint(int x,int y){
    if(x==0||x==n||y==0||y==m) return;//越界判断
    int val[]={a[x][y],a[x+1][y],a[x][y+1],a[x+1][y+1]};
    sort(val,val+4);
    if(val[3]==0) return;//格子全部被处理则返回
    bool flag=true;
    For(i,0,2) if(val[i]!=0&&val[i]!=val[3]) flag=false;
    if(!flag) return;//有未被处理的格子颜色不相等，不能处理改2*2块
    ans.pb((node){x,y,val[3]});//对这个2*2的块进行染色
    For(i,x,x+1) For(j,y,y+1) a[i][j]=0;//标记处理
    For(i,x-1,x+1) For(j,y-1,y+1) paint(i,j);//周围8个块都可能可以染色
}
```
**核心实现思想**：`paint` 函数用于处理一个 $2\times 2$ 的方块，先判断是否越界和是否已全部处理，再判断方块内非空格子颜色是否相同，若满足条件则记录操作并标记处理，然后递归处理周围 8 个方块。

#### Milmon 的核心代码
```
inline void work(int x,int y){
    if(x<1||x>n-1||y<1||y>m-1||p[x][y])return;
    bool flag=true; int col=-1;
    for(int i=0;i<=1;i++)
        for(int j=0;j<=1;j++){
            if(a[x+i][y+j]==-1)continue;
            if(col==-1)col=a[x+i][y+j];
            flag&=a[x+i][y+j]==col;
        }
    if(col==-1)return;
    if(flag)ans[++anslen]={x,y,col},p[x][y]=true;
}

//主函数部分
for(int i=1;i<=anslen;i++){
    for(int j=0;j<=1;j++)
        for(int jj=0;jj<=1;jj++)
            a[ans[i].x+j][ans[i].y+jj]=-1;//标记
    for(int j=-1;j<=1;j++)
        for(int jj=-1;jj<=1;jj++)
            work(ans[i].x+j,ans[i].y+jj);
}
```
**核心实现思想**：`work` 函数用于判断一个 $2\times 2$ 的方块是否满足条件，若满足则记录答案并标记。在主函数中，对已记录的方块进行标记，并检查其周围的方块。

### 最优关键思路或技巧
- **逆向思维**：正向构造比较困难，通过反向思考，从最终状态倒推初始状态，简化了问题。
- **标记处理**：使用特殊标记（如 -1 或 0）来表示已处理的格子，方便判断和处理。
- **BFS 或 DFS**：利用搜索算法（BFS 或 DFS）来遍历可能的方块，确保不会遗漏。

### 拓展思路
同类型题或类似算法套路通常涉及构造方案，可通过逆向思维将问题简化。例如，一些拼图还原、状态转换的题目，都可以尝试从最终状态倒推初始状态，找出可行的操作序列。

### 推荐题目
1. [CF37E Trial for Chief](https://www.luogu.com.cn/problem/CF37E)
2. [P1242 新汉诺塔](https://www.luogu.com.cn/problem/P1242)
3. [P1097 统计数字](https://www.luogu.com.cn/problem/P1097)

### 个人心得总结
- enucai 提到考场上这题想歪了，导致掉大分，提醒我们在考试中要保持清晰的思路，避免陷入错误的方向。

---
处理用时：67.42秒