# 题目信息

# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 3
###
###
###
```

### 输出

```
NO```

## 样例 #3

### 输入

```
4 3
###
###
###
###
```

### 输出

```
YES```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......
```

### 输出

```
YES```

# AI分析结果

### 题目重写
**伪造签名**

#### 题目描述
学生Andrey整个学期都在逃体育课，现在他必须想办法通过这门课。显然，通过合法手段是不可能的，但Andrey并没有放弃。他从当地医院获得了一张空白的证明，并打算利用他对当地医生笔迹的了解来伪造一张病假证明。然而，在写完大部分证明后，Andrey突然发现医生的签名无法伪造。或者真的无法伪造吗？

为了简化问题，签名被表示为一个$n \times m$的网格，每个单元格要么被墨水填充，要么为空。Andrey的笔可以填充一个$3 \times 3$的正方形，但不包括其中心单元格，前提是该正方形完全包含在网格内，如下图所示。

```
xxx
x.x
xxx
```

请确定是否可以在一个空的$n \times m$网格上伪造签名。

#### 说明/提示
在第一个样例中，Andrey可以以$(2, 2)$为中心的正方形的边框进行染色。

在第二个样例中，签名无法伪造。

在第三个样例中，Andrey可以以$(2, 2)$和$(3, 2)$为中心的正方形的边框进行染色：

1. 初始空白纸张：
```
...
...
...
...
```
2. 使用以$(2, 2)$为中心的笔：
```
###
#.#
###
...
```
3. 使用以$(3, 2)$为中心的笔：
```
###
###
###
###
```

在第四个样例中，Andrey可以以$(3, 3)$和$(3, 5)$为中心的正方形的边框进行染色。

#### 样例 #1
**输入**
```
3 3
###
#.#
###
```
**输出**
```
YES
```

#### 样例 #2
**输入**
```
3 3
###
###
###
```
**输出**
```
NO
```

#### 样例 #3
**输入**
```
4 3
###
###
###
###
```
**输出**
```
YES
```

#### 样例 #4
**输入**
```
5 7
.......
.#####.
.#.#.#.
.#####.
.......
```
**输出**
```
YES
```

---

### 题解分析与结论

#### 综合分析
该题的核心问题是通过给定的染色规则，判断是否可以将一个空网格染成目标网格。所有题解都采用了类似的思路：遍历网格中的每个点，判断是否可以进行染色操作，最后比对染色后的网格与目标网格是否一致。

#### 最优关键思路
1. **遍历与染色**：遍历网格中的每个点，判断其周围的8个点是否都为目标网格中的`#`，如果是，则进行染色操作。
2. **边界检查**：在染色操作前，确保染色范围不会越界。
3. **比对结果**：染色完成后，比对染色后的网格与目标网格是否一致。

#### 推荐题解
1. **Abyss_Bright (5星)**
   - **关键亮点**：代码清晰，逻辑简洁，通过移动数组简化了染色操作，边界检查和处理非常到位。
   - **核心代码**：
     ```cpp
     for(int x=1;x<=n;x++)
         for(int y=1;y<=m;y++)
         {
             int biao=1;
             for(int z=0;z<8;z++)
             {
                 int mx=x+dx[z];
                 int my=y+dy[z];
                 if(mx>n||mx<=0||my>m||my<=0)
                 {
                     biao=0;
                     break;
                 }
                 else if(mubiao[mx][my]!='#')
                 {
                     biao=0;
                     break;
                 }
             }
             if(biao==0) continue;
             for(int z=0;z<8;z++)
             {
                 int mx=x+dx[z];
                 int my=y+dy[z];
                 bian[mx][my]='#';
             }
         }
     ```

2. **Forever1507 (4星)**
   - **关键亮点**：提供了枚举和深搜两种解法，代码结构清晰，适合不同学习阶段的读者。
   - **核心代码**：
     ```cpp
     for(int i=1;i<=n;i++)
         for(int j=1;j<=m;j++)
         {
             bool flag=0;
             for(int k=0;k<=7;k++)
             {
                 int mx=i+dx[k];
                 int my=j+dy[k];
                 if(mx<=0||mx>n||my<=0||my>m||want[mx][my]=='.')
                 {
                     flag=1;
                     break;
                 }
             }
             if(flag) continue;
             for(int k=0;k<=7;k++)
             {
                 int mx=i+dx[k];
                 int my=j+dy[k];
                 now[mx][my]='#';
             }
         }
     ```

3. **氢氧化铯CsOH (4星)**
   - **关键亮点**：代码简洁，逻辑清晰，通过方向数组简化了染色操作，边界检查和处理非常到位。
   - **核心代码**：
     ```cpp
     for(int i=0;i+2<n;i++) for(int j=0;j+2<m;j++) 
         if(all(i,j)) set(i,j);
     ```

#### 可拓展之处
该题的思路可以拓展到其他类似的网格染色问题，如通过不同的染色规则或不同的网格形状进行染色。类似的题目可以通过遍历网格、判断染色条件、进行染色操作并比对结果来解决。

#### 推荐题目
1. [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)
2. [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
3. [P1131 最小生成树](https://www.luogu.com.cn/problem/P1131)

#### 个人心得摘录
- **Forever1507**：深搜虽然在时间和空间上劣于枚举，但提供了另一种解题思路，适合不同学习阶段的读者。
- **Abyss_Bright**：通过移动数组简化了染色操作，边界检查和处理非常到位，代码清晰易读。

---
处理用时：45.39秒