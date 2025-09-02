# 题目信息

# Chips

## 题目描述

Gerald plays the following game. He has a checkered field of size $ n×n $ cells, where $ m $ various cells are banned. Before the game, he has to put a few chips on some border (but not corner) board cells. Then for $ n-1 $ minutes, Gerald every minute moves each chip into an adjacent cell. He moves each chip from its original edge to the opposite edge. Gerald loses in this game in each of the three cases:

- At least one of the chips at least once fell to the banned cell.
- At least once two chips were on the same cell.
- At least once two chips swapped in a minute (for example, if you stand two chips on two opposite border cells of a row with even length, this situation happens in the middle of the row).

In that case he loses and earns $ 0 $ points. When nothing like that happened, he wins and earns the number of points equal to the number of chips he managed to put on the board. Help Gerald earn the most points.

## 说明/提示

In the first test the answer equals zero as we can't put chips into the corner cells.

In the second sample we can place one chip into either cell (1, 2), or cell (3, 2), or cell (2, 1), or cell (2, 3). We cannot place two chips.

In the third sample we can only place one chip into either cell (2, 1), or cell (2, 4).

## 样例 #1

### 输入

```
3 1
2 2
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4 3
3 1
3 2
3 3
```

### 输出

```
1
```

# AI分析结果

### 题目内容
# 筹码

## 题目描述
杰拉尔德玩以下游戏。他有一个 $n×n$ 大小的方格棋盘，其中有 $m$ 个不同的格子被禁止使用。在游戏开始前，他必须在棋盘的一些边界（但不是角落）格子上放置一些筹码。然后在 $n - 1$ 分钟内，杰拉尔德每分钟将每个筹码移动到相邻的格子。他将每个筹码从其初始的边缘移动到相对的边缘。在以下三种情况下，杰拉尔德会输掉这个游戏：
- 至少有一个筹码至少有一次落到了被禁止的格子上。
- 至少有一次两个筹码在同一个格子上。
- 至少有一次两个筹码在一分钟内交换了位置（例如，如果你在一行偶数长度的两个相对边界格子上放置两个筹码，这种情况会在该行的中间发生）。

在这种情况下，他会输掉游戏并获得 $0$ 分。当没有发生上述任何情况时，他会赢得游戏，并获得与他成功放置在棋盘上的筹码数量相等的分数。帮助杰拉尔德获得最多的分数。

## 说明/提示
在第一个测试用例中，答案为零，因为我们不能将筹码放入角落格子。

在第二个示例中，我们可以将一个筹码放入单元格 $(1, 2)$，或单元格 $(3, 2)$，或单元格 $(2, 1)$，或单元格 $(2, 3)$ 中。我们不能放置两个筹码。

在第三个示例中，我们只能将一个筹码放入单元格 $(2, 1)$ 或单元格 $(2, 4)$ 中。

## 样例 #1
### 输入
```
3 1
2 2
```
### 输出
```
0
```
## 样例 #2
### 输入
```
3 0
```
### 输出
```
1
```
## 样例 #3
### 输入
```
4 3
3 1
3 2
3 3
```
### 输出
```
1
```

### 算法分类
数学

### 题解综合分析与结论
这些题解思路基本一致，核心要点为：
1. **记录障碍**：通过数组记录每行每列是否存在禁止的格子。
2. **计算可放筹码数**：遍历非边界和角落的行与列，若该行或该列无禁止格子，则可放筹码数增加。
3. **处理相遇情况**：当棋盘边长 $n$ 为奇数且中间行和中间列都无禁止格子时，由于可能出现筹码在中间相遇的情况，可放筹码数减一。

各题解的区别主要在于代码实现细节和表述方式，整体思路和算法实现差异不大。

### 所选的题解
- **作者：miraculously（5星）**
  - **关键亮点**：思路清晰，代码简洁明了，直接用布尔数组记录行列阻碍情况，计算可放筹码数和处理相遇情况的代码逻辑清晰。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,n,m,ans;
bool a[1001],b[1001];//a，b分别记录行列是否有阻碍
int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>x>>y;
        a[x]=1;
        b[y]=1;
    }
    for(int i=2;i<n;i++)
        ans+=(!a[i])+(!b[i]);//如果行没阻碍，那答案+1，列同理
    if((n&1)&&(!a[(n>>1)+1])&&(!b[(n>>1)+1]))//处理相遇的
        ans--;
    cout<<ans;
}
```
  - **核心实现思想**：先读入禁止格子的行列并标记，然后遍历非边界和角落的行与列，统计无障碍的行和列数量作为可放筹码数，最后根据棋盘边长和中间行列的阻碍情况调整可放筹码数。

- **作者：zhangqiuyanAFOon2024（4星）**
  - **关键亮点**：思路阐述较详细，从简单思路引入到考虑相遇情况，代码中使用数组记录障碍情况，逻辑较清晰。
  - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int x[N],y[N],sx[N],sy[N];
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
        cin>>x[i]>>y[i],sx[x[i]]++,sy[y[i]]++;//记录
    int cnt=0;
    for(int i=2;i<n;i++)
        if(sx[i]==0) cnt++;
    for(int i=2;i<n;i++)
        if(sy[i]==0) cnt++;//全都放
    if((n&1)&&!sx[n/2+1]&&!sy[n/2+1]) cnt--;//相遇减一
    cout<<cnt;
}
```
  - **核心实现思想**：读入禁止格子坐标并记录每行每列禁止格子数量，遍历非边界和角落的行与列，统计无障碍的行和列数量作为可放筹码数，根据棋盘边长和中间行列禁止格子数量调整可放筹码数。

- **作者：wuyixiang（4星）**
  - **关键亮点**：对题目理解和思路分析详细，先指出常见错误点，再阐述正确思路，代码实现清晰。
  - **重点代码**：
```cpp
#include <iostream>
using namespace std;
int n,m,c[1005],d[1005],r,w,q;
int main()
{
    cin >> n >> m;
    w = n / 2 + 1;
    for(int i = 1,x,y;i <= m;i ++)cin >> x >> y,c[x] = d[y] = 1;//标记：这一行和这一列不能有芯片
    for(int i = 2;i < n;i ++)if(!c[i])r ++;//算芯片可以放置的个数
    for(int i = 2;i < n;i ++)if(!d[i])r ++;
    if(n % 2 &&!c[w] &&!d[w])q = 1;//q判断芯片在正中间相撞的情况
    cout << r - q;//输出
}
```
  - **核心实现思想**：读入禁止格子坐标并标记所在行和列，遍历非边界和角落的行与列，统计无障碍的行和列数量作为可放筹码数，根据棋盘边长和中间行列的标记情况判断是否有芯片在中间相撞，调整可放筹码数。

### 最优关键思路或技巧
使用数组记录每行每列的禁止格子情况，通过简单遍历统计可放置筹码的行列数量，同时针对棋盘边长为奇数时中间行列可能出现的筹码相遇情况进行特殊处理。

### 拓展思路
同类型题通常围绕在有约束条件的棋盘移动问题，类似算法套路是先分析移动规则和限制条件，利用数组等数据结构记录关键信息，通过遍历和条件判断得出结果。

### 洛谷相似题目推荐
1. **P1031 均分纸牌**：通过计算平均数，移动纸牌使每行纸牌数量相等，考察对规则的理解和简单数学计算。
2. **P1192 台阶问题**：涉及到台阶上的物品移动，有一定的限制条件，与本题类似需分析移动规则并统计结果。
3. **P1439 【模板】最长公共子序列**：虽然是字符串相关，但在分析子序列匹配规则和统计结果上与本题分析放置筹码规则和统计数量有相似思维方式。 

---
处理用时：70.58秒