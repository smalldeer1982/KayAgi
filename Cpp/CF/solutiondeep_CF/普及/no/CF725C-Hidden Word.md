# 题目信息

# Hidden Word

## 题目描述

Let’s define a grid to be a set of tiles with $ 2 $ rows and $ 13 $ columns. Each tile has an English letter written in it. The letters don't have to be unique: there might be two or more tiles with the same letter written on them. Here is an example of a grid:

 `ABCDEFGHIJKLM<br></br>NOPQRSTUVWXYZ`We say that two tiles are adjacent if they share a side or a corner. In the example grid above, the tile with the letter 'A' is adjacent only to the tiles with letters 'B', 'N', and 'O'. A tile is not adjacent to itself.

A sequence of tiles is called a path if each tile in the sequence is adjacent to the tile which follows it (except for the last tile in the sequence, which of course has no successor). In this example, "ABC" is a path, and so is "KXWIHIJK". "MAB" is not a path because 'M' is not adjacent to 'A'. A single tile can be used more than once by a path (though the tile cannot occupy two consecutive places in the path because no tile is adjacent to itself).

You’re given a string $ s $ which consists of $ 27 $ upper-case English letters. Each English letter occurs at least once in $ s $ . Find a grid that contains a path whose tiles, viewed in the order that the path visits them, form the string $ s $ . If there’s no solution, print "Impossible" (without the quotes).

## 样例 #1

### 输入

```
ABCDEFGHIJKLMNOPQRSGTUVWXYZ
```

### 输出

```
YXWVUTGHIJKLM
ZABCDEFSRQPON
```

## 样例 #2

### 输入

```
BUVTYZFQSNRIWOXXGJLKACPEMDH
```

### 输出

```
Impossible
```

# AI分析结果



# 中文题目重写

## 题目描述

我们定义一个网格为2行13列的瓷砖矩阵，每个瓷砖上写有一个大写英文字母（允许重复）。相邻定义为共享边或角的瓷砖。例如示例网格：

`ABCDEFGHIJKLM`  
`NOPQRSTUVWXYZ`  

其中'A'的相邻瓷砖为'B'、'N'、'O'。路径定义为相邻瓷砖的序列，允许重复使用瓷砖但不能连续重复。

给定一个长度为27的字符串s，每个字母至少出现一次。要求构造一个包含能形成该字符串路径的网格，若无法构造则输出"Impossible"。

## 样例 #1

### 输入
`ABCDEFGHIJKLMNOPQRSGTUVWXYZ`

### 输出
`YXWVUTGHIJKLM`  
`ZABCDEFSRQPON`

## 样例 #2

### 输入
`BUVTYZFQSNRIWOXXGJLKACPEMDH`

### 输出
`Impossible`

# 算法分类
构造

# 题解分析与结论

**核心思路**：由于字符串长度为27且每个字母至少出现一次，必有一个字母重复。找到重复字母的位置：  
1. 若两重复字母相邻则无解（无法形成路径）
2. 将两重复字母间的字符平分到两行构造网格

**关键难点**：如何将中间字符合理分配到两行，确保路径连续。通过逆序填充第二行实现相邻性。

# 精选题解

## igAC的题解（★★★★☆）
**亮点**：  
- 直接定位重复字母位置，计算中间段长度
- 将中间段平分到两行，逆序填充第二行  
**核心代码**：
```cpp
ans[0][13-space+1] = wish; // 重复字母放置位置
for (int i=13-space+2; i<=13; ++i) ans[0][i] = s[++cnt]; // 第一行后半填充
for (int i=13; i>=1; --i) { // 第二行逆序填充
    ++cnt;
    if (cnt == p2) ++cnt; // 跳过重复字母
    ans[1][i] = s[cnt];
}
```

## JLGxy的题解（★★★★☆）
**亮点**：  
- 通过旋转字符串调整字符分布  
- 处理边界条件避免重复冲突  
**核心代码**：
```cpp
// 调整字符串使中间段可平分
while (a > 26 - b) s += *s.begin(), s.erase(s.begin()), a--, b--; 
// 填充第二行时跳过重复
if (ans[i][1] == s[j] || ans[i+1][1] == s[j]) j++; 
ans[i][0] = s[j];
```

# 最优技巧总结
1. **重复字母定位**：利用哈希表快速找到重复位置
2. **中间段平分策略**：将中间段长度除2，分别填充到两行的对应区域
3. **逆序构造**：第二行逆序填充以保持相邻性

# 拓展与同类题
- **类似构造思路**：棋盘覆盖、回文路径构造
- **推荐题目**：  
  1. [CF3D Least Cost Bracket Sequence](https://www.luogu.com.cn/problem/CF3D)（贪心构造）  
  2. [P1058 棋盘覆盖](https://www.luogu.com.cn/problem/P1058)（分治构造）  
  3. [CF1365D Solve The Maze](https://www.luogu.com.cn/problem/CF1365D)（路径构造验证）

---
处理用时：91.15秒