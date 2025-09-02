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



# Forgery 题解分析

**唯一算法分类**: 其他搜索（枚举模拟）

## 题解思路与核心难点

### 核心思路
题目要求判断是否能通过多次特定涂色操作生成目标网格。每个涂色操作以某个点为中心，将其周围8个格子涂色（3x3边框）。核心思路为：
1. **反向模拟**：遍历所有可能的中心点，检查其周围是否满足条件（均为`#`且不越界），若满足则进行涂色。
2. **对比验证**：将模拟涂色后的结果与目标网格比对，完全一致则可行。

### 解决难点
1. **边界处理**：中心点必须位于内部区域（行2~n-1，列2~m-1），否则涂色会越界。
2. **覆盖逻辑**：多次涂色不影响结果，只需确保所有可能操作被执行。
3. **正确性验证**：最终比对必须严格一致，任何差异均判定为不可行。

## 题解评分（≥4星）

1. **Abyss_Bright (5星)**
   - **亮点**：代码清晰，严格检查每个点是否可涂色，通过双向数组处理偏移。
   - **代码可读性**：结构明确，变量命名合理，注释详细。
   - **优化点**：遍历所有点但通过条件过滤，不影响正确性。

2. **「已注销」 (5星)**
   - **亮点**：高效枚举可能的中心区域，直接处理8个偏移，减少无效遍历。
   - **代码简洁性**：利用位移数组简化逻辑，对比过程高效。

3. **氢氧化铯CsOH (4星)**
   - **亮点**：代码简洁，使用预计算位移数组，逻辑紧凑。
   - **优化点**：通过`vis`数组记录实际涂色位置，避免重复操作。

## 最优思路与技巧提炼

1. **反向模拟法**：从目标网格出发，枚举所有可能的涂色操作，避免正向搜索的复杂性。
2. **位移数组优化**：使用预定义的偏移数组（如`dx[8]`和`dy[8]`）简化周围格子的遍历。
3. **中心点范围优化**：仅遍历内部区域（行2~n-1，列2~m-1），减少无效检查。

## 同类型题与算法套路

- **类似问题**：网格覆盖、图案生成、操作模拟。
- **通用解法**：枚举所有可能的操作，模拟执行后验证结果。
- **拓展思路**：若操作顺序影响结果，需结合BFS/DFS遍历状态空间。

## 推荐题目

1. **洛谷P1078** - 文化之旅（路径枚举与条件判断）
2. **Codeforces 1059B** - 类似网格操作问题
3. **洛谷P1443** - 马的遍历（BFS应用）

## 可视化与算法演示

### 动画设计
1. **像素网格展示**：以8位风格绘制网格，初始为全白（`.`），目标图案用不同颜色标记。
2. **涂色过程**：
   - 高亮当前中心点（黄色），检查周围8格是否为`#`（红色表示符合条件）。
   - 符合条件时，涂色区域变为绿色，播放“滴答”音效。
3. **结果比对**：所有操作完成后，错误格子闪烁红色，正确则显示“胜利”动画与音效。

### 交互功能
- **步进控制**：允许单步执行或自动播放（速度可调）。
- **音效提示**：涂色成功时播放8位音效，错误时播放低沉音效。

### 复古风格实现
- **Canvas绘制**：采用16色调色板，网格线为深灰色，节点用方块表示。
- **音效设计**：使用Web Audio API生成短促方波音效，背景音乐为循环芯片音乐。

---

**核心代码片段（Abyss_Bright 题解）**
```cpp
for(int x=1;x<=n;x++)
    for(int y=1;y<=m;y++) {
        bool valid = true;
        // 检查周围8格是否均为#且不越界
        for(int z=0;z<8;z++) {
            int mx = x+dx[z], my = y+dy[z];
            if(mx<1 || mx>n || my<1 || my>m || mubiao[mx][my]!='#') {
                valid = false; break;
            }
        }
        if(valid) // 涂色操作
            for(int z=0;z<8;z++)
                bian[x+dx[z]][y+dy[z]] = '#';
    }
```

**关键逻辑**：遍历每个可能中心点，检查并涂色，最终比对结果。

---
处理用时：69.75秒