# 题目信息

# Rectangle Filling

## 题目描述

There is an $ n \times m $ grid of white and black squares. In one operation, you can select any two squares of the same color, and color all squares in the subrectangle between them that color.

Formally, if you select positions $ (x_1, y_1) $ and $ (x_2, y_2) $ , both of which are currently the same color $ c $ , set the color of all $ (x, y) $ where $ \min(x_1, x_2) \le x \le \max(x_1, x_2) $ and $ \min(y_1, y_2) \le y \le \max(y_1, y_2) $ to $ c $ .

This diagram shows a sequence of two possible operations on a grid:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1966B/d8e91236088d989799638772d594a0a137d702f1.png)Is it possible for all squares in the grid to be the same color, after performing any number of operations (possibly zero)?

## 说明/提示

In the first example, it is impossible to ever change the color of any square with an operation, so we output NO.

The second example is the case pictured above. As shown in that diagram, it is possible for all squares to be white after two operations, so we output YES.

In the third and fourth examples, all squares are already the same color, so we output YES.

In the fifth example we can do everything in two operations. First, select positions $ (2, 1) $ and $ (1, 4) $ and color all squares with $ 1 \le x \le 2 $ and $ 1 \le y \le 4 $ to white. Then, select positions $ (2, 1) $ and $ (3, 4) $ and color all squares with $ 2 \le x \le 3 $ and $ 1 \le y \le 4 $ to white. After these two operations all squares are white.

## 样例 #1

### 输入

```
8
2 1
W
B
6 6
WWWWBW
WBWWWW
BBBWWW
BWWWBB
WWBWBB
BBBWBW
1 1
W
2 2
BB
BB
3 4
BWBW
WBWB
BWBW
4 2
BB
BB
WW
WW
4 4
WWBW
BBWB
WWBB
BBBB
1 5
WBBWB```

### 输出

```
NO
YES
YES
YES
YES
NO
YES
NO```

# AI分析结果

### 题目中文重写
# 矩形填充

## 题目描述
有一个由白色和黑色方块组成的 $n \times m$ 网格。在一次操作中，你可以选择任意两个颜色相同的方块，然后将它们之间的子矩形中的所有方块都染成该颜色。

形式上，如果你选择位置 $(x_1, y_1)$ 和 $(x_2, y_2)$，它们当前的颜色均为 $c$，则将所有满足 $\min(x_1, x_2) \le x \le \max(x_1, x_2)$ 且 $\min(y_1, y_2) \le y \le \max(y_1, y_2)$ 的 $(x, y)$ 位置的方块颜色设置为 $c$。

此图展示了网格上可能的两次操作序列：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1966B/d8e91236088d989799638772d594a0a137d702f1.png)

在执行任意次数（可能为零）的操作后，网格中的所有方块是否可以变成相同的颜色？

## 说明/提示
在第一个样例中，不可能通过任何操作改变任何方块的颜色，因此我们输出 `NO`。

第二个样例是上图所示的情况。如图所示，经过两次操作后所有方块都可以变成白色，因此我们输出 `YES`。

在第三和第四个样例中，所有方块已经是相同的颜色，因此我们输出 `YES`。

在第五个样例中，我们可以通过两次操作完成。首先，选择位置 $(2, 1)$ 和 $(1, 4)$，将所有满足 $1 \le x \le 2$ 且 $1 \le y \le 4$ 的方块染成白色。然后，选择位置 $(2, 1)$ 和 $(3, 4)$，将所有满足 $2 \le x \le 3$ 且 $1 \le y \le 4$ 的方块染成白色。经过这两次操作后，所有方块都变成了白色。

## 样例 #1
### 输入
```
8
2 1
W
B
6 6
WWWWBW
WBWWWW
BBBWWW
BWWWBB
WWBWBB
BBBWBW
1 1
W
2 2
BB
BB
3 4
BWBW
WBWB
BWBW
4 2
BB
BB
WW
WW
4 4
WWBW
BBWB
WWBB
BBBB
1 5
WBBWB
```

### 输出
```
NO
YES
YES
YES
YES
NO
YES
NO
```

### 综合分析与结论
这些题解主要围绕判断给定的黑白方阵能否通过特定染色操作变成同色方阵展开。思路大致可分为两类：
1. **对角判断法**：先判断是否有对角顶点颜色相同，若有则有解；若无，则判断能否改变角上颜色使其出现对角同色。
2. **边界判断法**：判断矩阵的上下左右四条边上是否都有白色或黑色，若有则有解，否则无解。

### 所选题解
- **huhaoming2011（4星）**
    - **关键亮点**：思路清晰，先判断对角颜色是否相同，再判断角上颜色是否可变，代码实现逻辑完整。
    - **核心代码**：
```cpp
if(g[n][1]==g[1][m]||g[1][1]==g[n][m])
{
    printf("YES\n");
}
else
{
    int ff=0;
    for(int i=1;i<=n;i++)
    {
        if(g[i][1]!=g[1][1]&&bz[1]==0)
        {
            bz[1]++;
        }
        if(g[i][m]!=g[1][m]&&bz[2]==0)
        {
            bz[2]++;
        }
        if(g[i][1]!=g[n][1]&&bz[3]==0)
        {
            bz[3]++;
        }
        if(g[i][m]!=g[n][m]&&bz[4]==0)
        {
            bz[4]++;
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(g[1][i]!=g[1][1]&&bz[1]==1)
        {
            ff=1;
            printf("YES\n");
            break;
        }
        if(g[1][i]!=g[1][m]&&bz[2]==1)
        {
            ff=1;
            printf("YES\n");
            break;
        }
        if(g[n][i]!=g[n][1]&&bz[3]==1)
        {
            ff=1;
            printf("YES\n");
            break;
        }
        if(g[n][i]!=g[n][m]&&bz[4]==1)
        {
            ff=1;
            printf("YES\n");
            break;
        }
    }
    if(ff==0) printf("NO\n");
}
```
- **Lame_Joke（4星）**
    - **关键亮点**：采用边界判断法，思路简洁，代码实现简单明了。
    - **核心代码**：
```cpp
for(int i=1;i<=n;i++)
{
    if(a[i][1]==1) cnt1[0]=1;
    if(a[i][m]==1) cnt1[1]=1;
    if(a[i][1]==0) cnt2[0]=1;
    if(a[i][m]==0) cnt2[1]=1;
}
for(int i=1;i<=m;i++)
{
    if(a[1][i]==1) cnt1[2]=1;
    if(a[n][i]==1) cnt1[3]=1;
    if(a[1][i]==0) cnt2[2]=1;
    if(a[n][i]==0) cnt2[3]=1;
}
if((cnt2[0]==1&&cnt2[1]==1&&cnt2[2]==1&&cnt2[3]==1)||(cnt1[0]==1&&cnt1[1]==1&&cnt1[2]==1&&cnt1[3]==1)) printf("YES\n");
else printf("NO\n");
```
- **junee（4星）**
    - **关键亮点**：思路全面，先处理特殊情况，再判断对角颜色，最后判断能否通过找对边点覆盖，逻辑严谨。
    - **核心代码**：
```cpp
if(n==1){
    if(a[1][1]!=a[1][m])cout<<"NO"<<'\n';
    else cout<<"YES"<<'\n';
    continue;
}
if(m==1){
    if(a[1][1]!=a[n][1])cout<<"NO"<<'\n';
    else cout<<"YES"<<'\n';
    continue;
}
if(a[1][1]==a[n][m]||a[n][1]==a[1][m]){
    cout<<"YES"<<'\n';
    continue;
}
if(a[1][1]==a[n][1]){
    int f=1;
    for(int i=1;i<=n;i++){
        if(a[i][m]==a[1][1]){
            cout<<"YES"<<'\n';
            f=0;
            break;
        }
    }
    if(!f)continue;
    for(int i=1;i<=n;i++){
        if(a[i][1]==a[n][m]){
            cout<<"YES"<<'\n';
            f=0;
            break;
        }
    }
    if(!f)continue;
}
if(a[1][1]==a[1][m]){
    int f=1;
    for(int i=1;i<=m;i++){
        if(a[1][1]==a[n][i]){
            cout<<"YES"<<'\n';
            f=0;
            break;
        }
    }
    if(!f)continue;
    for(int i=1;i<=m;i++){
        if(a[n][m]==a[1][i]){
            cout<<"YES"<<'\n';
            f=0;
            break;
        }
    }
    if(!f)continue;
}
cout<<"NO"<<'\n';
```

### 最优关键思路或技巧
- **边界判断法**：通过枚举四条边，标记是否存在白色或黑色，判断四条边上是否都有同一种颜色，若有则可将矩阵染成纯色，这种方法代码实现简单，时间复杂度低。
- **对角判断法**：先判断对角顶点颜色是否相同，若不同再判断能否改变角上颜色使其出现对角同色，逻辑清晰，能全面考虑各种情况。

### 可拓展之处
同类型题目可能会改变操作规则或矩阵元素，例如改变染色规则、增加颜色种类等。类似算法套路可用于解决一些图形变换、状态判断的问题，关键在于找出图形的特征和变化规律，通过判断某些条件是否满足来得出结论。

### 推荐洛谷题目
1. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
2. [P1506 拯救oibh总部](https://www.luogu.com.cn/problem/P1506)
3. [P2002 消息扩散](https://www.luogu.com.cn/problem/P2002)

### 个人心得摘录与总结
部分题解未提及个人心得。在解决此类问题时，应仔细观察题目特征，找出关键规律，如本题中的对角颜色和边界颜色情况，同时注意代码实现的逻辑完整性和简洁性。 

---
处理用时：43.52秒