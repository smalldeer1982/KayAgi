# 题目信息

# Lara Croft and the New Game

## 题目描述

You might have heard about the next game in Lara Croft series coming out this year. You also might have watched its trailer. Though you definitely missed the main idea about its plot, so let me lift the veil of secrecy.

Lara is going to explore yet another dangerous dungeon. Game designers decided to use good old 2D environment. The dungeon can be represented as a rectangle matrix of $ n $ rows and $ m $ columns. Cell $ (x,y) $ is the cell in the $ x $ -th row in the $ y $ -th column. Lara can move between the neighbouring by side cells in all four directions.

Moreover, she has even chosen the path for herself to avoid all the traps. She enters the dungeon in cell $ (1,1) $ , that is top left corner of the matrix. Then she goes down all the way to cell $ (n,1) $ — the bottom left corner. Then she starts moving in the snake fashion — all the way to the right, one cell up, then to the left to the cell in $ 2 $ -nd column, one cell up. She moves until she runs out of non-visited cells. $ n $ and $ m $ given are such that she always end up in cell $ (1,2) $ .

Lara has already moved to a neighbouring cell $ k $ times. Can you determine her current position?

## 说明/提示

Here is her path on matrix $ 4 $ by $ 3 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1

### 输入

```
4 3 0
```

### 输出

```
1 1
```

## 样例 #2

### 输入

```
4 3 11
```

### 输出

```
1 2
```

## 样例 #3

### 输入

```
4 3 7
```

### 输出

```
3 2
```

# AI分析结果

### 题目中文重写
# 劳拉·克劳馥与新游戏

## 题目描述
你可能听说过今年即将推出的劳拉·克劳馥系列的下一款游戏。你可能也看过它的预告片。不过你肯定错过了关于其剧情的主要内容，所以让我来揭开神秘的面纱。

劳拉即将探索另一个危险的地下城。游戏设计师决定采用经典的 2D 环境。地下城可以用一个 $n$ 行 $m$ 列的矩形矩阵来表示。单元格 $(x,y)$ 是第 $x$ 行第 $y$ 列的单元格。劳拉可以在相邻的单元格之间向四个方向移动。

此外，她甚至已经为自己选择了一条避开所有陷阱的路径。她从单元格 $(1,1)$（即矩阵的左上角）进入地下城。然后她一直向下走到单元格 $(n,1)$（即矩阵的左下角）。接着她开始以蛇形方式移动——一直向右，向上移动一格，然后向左移动到第 2 列的单元格，再向上移动一格。她一直移动，直到没有未访问过的单元格为止。给定的 $n$ 和 $m$ 保证她最终会到达单元格 $(1,2)$。

劳拉已经移动了 $k$ 次到相邻的单元格。你能确定她当前的位置吗？

## 说明/提示
以下是她在 4 行 3 列矩阵上的路径：

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF976B/1b2df8f31f927201c078b0cd1ef3dccbc8991311.png)

## 样例 #1
### 输入
```
4 3 0
```
### 输出
```
1 1
```

## 样例 #2
### 输入
```
4 3 11
```
### 输出
```
1 2
```

## 样例 #3
### 输入
```
4 3 7
```
### 输出
```
3 2
```

### 综合分析与结论
- **思路对比**：所有题解均将劳拉的移动路径分为从左上角到左下角和从左下角到终点两部分。先特判第一步分，再处理第二部分，根据第二部分步数的奇偶性判断移动方向（从左到右或从右到左），进而确定坐标。
- **算法要点**：通过数学计算直接得出第 $k$ 步的坐标，避免模拟移动过程，时间复杂度为 $O(1)$。关键在于根据步数计算出行数和列数，利用取整和取余运算。
- **解决难点**：主要难点在于找出第二部分移动的规律，即根据步数判断当前行的移动方向，并正确计算列坐标。不同题解在计算步数和坐标时的细节略有不同，但核心思路一致。

### 所选题解
- **作者：wwwidk1234（5星）**
    - **关键亮点**：思路清晰，对每一部分的分析详细，代码简洁，注释明确，对数据范围的提醒很重要。
- **作者：GordonLu（4星）**
    - **关键亮点**：代码简洁，直接给出核心代码，对思路的概括准确。
- **作者：___cjy__（4星）**
    - **关键亮点**：代码规范，使用宏定义简化代码，对思路的阐述清晰。

### 重点代码
```cpp
// wwwidk1234的核心代码
if(k<n) cout<<k+1<<" "<<1<<endl;
else
{
    long long k1=k-n;
    if((k1/(m-1))%2==1) cout<<n-k1/(m-1)<<" "<<m-k1%(m-1)<<endl;
    else cout<<n-k1/(m-1)<<" "<<k1%(m-1)+2<<endl;
}

// GordonLu的核心代码
if(k<n)printf("%lld %d",k+1,1);
else {
    k-=n;printf("%lld ",n-k/(m-1));
    if(k/(m-1)&1)printf("%lld",m-k%(m-1));else printf("%lld",k%(m-1)+2);
}

// ___cjy__的核心代码
if(k < n) cout << k + 1 << " 1\n";
else{
    k -= n;
    int line = k / (m - 1);
    int t = k % (m - 1);//[0, m - 2]
    if(line & 1){
        line = n - line;
        t = m - t;
    }else{
        line = n - line;
        t = t + 2;
    }
    cout << line << ' ' << t << endl;
} 
```
**核心实现思想**：先判断 $k$ 是否小于 $n$，若小于则直接得出坐标 $(k + 1, 1)$；否则计算第二部分的步数，根据步数的奇偶性判断移动方向，进而计算出坐标。

### 最优关键思路或技巧
- **分阶段处理**：将移动路径分为两个阶段，分别处理，简化问题。
- **数学计算**：利用取整和取余运算，直接计算出第 $k$ 步的坐标，避免模拟移动过程，降低时间复杂度。
- **奇偶判断**：通过判断步数的奇偶性确定移动方向，从而正确计算列坐标。

### 可拓展之处
同类型题可能会改变移动规则，如改变起点、终点或移动方向，或者增加矩阵的维度。类似算法套路是将复杂的移动过程分解为多个简单的阶段，找出每个阶段的规律，通过数学计算直接得出结果。

### 推荐洛谷题目
- P1003 铺地毯
- P1047 校门外的树
- P1091 合唱队形

### 个人心得摘录与总结
- **EternalAlexander**：提到一开始用 `%d` 读 `long long` 调了几十分钟，提醒我们要注意输入输出格式与数据类型的匹配。

---
处理用时：30.98秒