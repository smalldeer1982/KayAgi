# 题目信息

# Fox and Cross

## 题目描述

Fox Ciel has a board with $ n $ rows and $ n $ columns. So, the board consists of $ n×n $ cells. Each cell contains either a symbol '.', or a symbol '\#'.

A cross on the board is a connected set of exactly five cells of the board that looks like a cross. The picture below shows how it looks.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF389B/5ccac31668e0d529fa8a5f9e69b4dcfcf1f3b650.png)Ciel wants to draw several (may be zero) crosses on the board. Each cross must cover exactly five cells with symbols '\#', and any cell with symbol '\#' must belong to some cross. No two crosses can share a cell.

Please, tell Ciel if she can draw the crosses in the described way.

## 说明/提示

In example 1, you can draw two crosses. The picture below shows what they look like.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF389B/2961c8465879f5caacf5ebd47c02d06b75cd444e.png)In example 2, the board contains 16 cells with '\#', but each cross contains 5. Since 16 is not a multiple of 5, so it's impossible to cover all.

## 样例 #1

### 输入

```
5
.#...
####.
.####
...#.
.....
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4
####
####
####
####
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
6
.#....
####..
.####.
.#.##.
######
.#..#.
```

### 输出

```
YES
```

## 样例 #4

### 输入

```
6
.#..#.
######
.####.
.####.
######
.#..#.
```

### 输出

```
NO
```

## 样例 #5

### 输入

```
3
...
...
...
```

### 输出

```
YES
```

# AI分析结果

### 题目内容
# Fox and Cross

## 题目描述
Fox Ciel有一块$n$行$n$列的棋盘。所以，棋盘由$n×n$个格子组成。每个格子里要么是符号'.'，要么是符号'#'。

棋盘上的一个十字是由恰好五个格子组成的连通集合，形状像一个十字。下图展示了它的样子。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF389B/5ccac31668e0d529fa8a5f9e69b4dcfcf1f3b650.png)Ciel想在棋盘上画几个（可能是零个）十字。每个十字必须恰好覆盖五个标有'#'的格子，并且任何标有'#'的格子都必须属于某个十字。任意两个十字不能共用一个格子。

请告诉Ciel她是否能按照要求画出十字。

## 说明/提示
在示例1中，你可以画两个十字。下图展示了它们的样子。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF389B/2961c8465879f5caacf5ebd47c02d06b75cd444e.png)在示例2中，棋盘上有16个标有'#'的格子，但每个十字包含5个。由于16不是5的倍数，所以不可能覆盖所有格子。

## 样例 #1
### 输入
```
5
.#...
####.
.####
...#.
.....
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
4
####
####
####
####
```
### 输出
```
NO
```

## 样例 #3
### 输入
```
6
.#....
####..
.####.
.#.##.
######
.#..#.
```
### 输出
```
YES
```

## 样例 #4
### 输入
```
6
.#..#.
######
.####.
.####.
######
.#..#.
```
### 输出
```
NO
```

## 样例 #5
### 输入
```
3
...
...
...
```
### 输出
```
YES
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路均为模拟，通过遍历矩阵判断是否存在十字形状的'#'组合，并进行相应处理，最后判断所有'#'是否都能组成十字。各题解的主要区别在于判断十字的方式、处理已识别十字的方法以及最终判断剩余'#'的方式。有的题解直接在原矩阵上修改，有的使用标记数组；有的先统计'#'数量并判断其是否为5的倍数以提前排除不可能的情况，有的则直接遍历判断。

### 所选的题解
- **作者：xtr169 (5星)**
    - **关键亮点**：思路清晰直接，代码简洁明了，纯字符串操作，双重循环遍历矩阵，遇到十字就将其覆盖的'#'替换为'.'，最后判断矩阵中是否还有剩余的'#'。
    - **重点代码**：
```cpp
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        if(s[i][j]=='#'&&s[i][j-1]=='#'&&s[i][j+1]=='#'
        &&s[i-1][j]=='#'&&s[i+1][j]=='#')//判断是否有十字
        {
            s[i][j]='.';
            s[i][j-1]='.';
            s[i][j+1]='.';
            s[i-1][j]='.';
            s[i+1][j]='.';
            //有的话全换成'.'
        }
    }
}
for(int i=0;i<n;i++)
{
    for(int j=0;j<n;j++)
    {
        if(s[i][j]=='#')//只要有#说明没有全部被替换。输出NO
        {
            cout<<"NO";
            return 0;
        }
    }
}
cout<<"YES";
```
- **作者：guozhetao (4星)**
    - **关键亮点**：在模拟的基础上进行了小优化，先统计'#'的数量，若其不是5的倍数则直接输出NO，减少不必要的遍历。之后遍历矩阵寻找十字，找到后更新'#'数量，最后根据剩余'#'数量判断结果。
    - **重点代码**：
```cpp
if(ans % 5!= 0) {
    printf("NO\n");
    return 0;
}
for(int i = 2;i < n;i++) {
    for(int j = 2;j < n;j++) {
        if(p[i][j] && p[i - 1][j] && p[i + 1][j] && p[i][j + 1] && p[i][j - 1]) {
            p[i][j] = 0;
            p[i - 1][j] = 0;
            p[i + 1][j] = 0;
            p[i][j + 1] = 0;
            p[i][j - 1] = 0;
            ans -= 5;
        }
    }
}
if(ans) {
    printf("NO\n");
    return 0;
}
printf("YES\n");
```
- **作者：_lzy_ (4星)**
    - **关键亮点**：将判断十字、清除十字和判断是否清空分别封装成函数，代码结构清晰，易于理解和维护。
    - **重点代码**：
```cpp
bool check(){//判断是否清空的函数
    for(int i=1;i<=n;i++)    
        for(int k=1;k<=n;k++)    
            if(f[i][k]==1)
                return false;
    return true;
}
bool checkf(int x,int y){//判断是否构成十字架
    if(f[x][y]&&f[x+1][y])
        if(f[x-1][y]&&f[x][y+1])
            if(f[x][y-1])
                return true;
    return false;
}
void cleaning(int x,int y){//清空十字架
    f[x][y]=0;
    f[x-1][y]=0;
    f[x+1][y]=0;
    f[x][y-1]=0;
    f[x][y+1]=0;
}
```

### 最优关键思路或技巧
1. **提前判断**：如guozhetao的题解，先统计'#'的数量并判断是否为5的倍数，可提前排除不可能的情况，减少计算量。
2. **函数封装**：像_lzy_的题解，将不同功能封装成函数，使代码结构更清晰，提高可读性和维护性。

### 拓展
同类型题通常围绕图形匹配、矩阵元素组合判断等展开，类似套路为通过遍历矩阵元素，依据给定的图形或组合规则进行判断和处理。例如，判断矩阵中能否组成特定形状的连通块等。

### 洛谷相似题目推荐
1. **P1036 [NOIP2002 普及组] 选数**：涉及组合和简单的数学判断，与本题遍历判断元素组合有相似之处。
2. **P1161 开灯**：通过模拟开关灯的过程，考察对逻辑判断和循环遍历的运用，和本题模拟十字判断过程类似。
3. **P1423 小玉在游泳**：模拟小玉游泳的过程，根据给定条件判断状态变化，与本题按规则处理矩阵元素思路相近。 

---
处理用时：75.57秒