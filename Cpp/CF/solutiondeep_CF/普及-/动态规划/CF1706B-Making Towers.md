# 题目信息

# Making Towers

## 题目描述

You have a sequence of $ n $ colored blocks. The color of the $ i $ -th block is $ c_i $ , an integer between $ 1 $ and $ n $ .

You will place the blocks down in sequence on an infinite coordinate grid in the following way.

1. Initially, you place block $ 1 $ at $ (0, 0) $ .
2. For $ 2 \le i \le n $ , if the $ (i - 1) $ -th block is placed at position $ (x, y) $ , then the $ i $ -th block can be placed at one of positions $ (x + 1, y) $ , $ (x - 1, y) $ , $ (x, y + 1) $ (but not at position $ (x, y - 1) $ ), as long no previous block was placed at that position.

A tower is formed by $ s $ blocks such that they are placed at positions $ (x, y), (x, y + 1), \ldots, (x, y + s - 1) $ for some position $ (x, y) $ and integer $ s $ . The size of the tower is $ s $ , the number of blocks in it. A tower of color $ r $  is a tower such that all blocks in it have the color $ r $ .

For each color $ r $ from $ 1 $ to $ n $ , solve the following problem independently:

- Find the maximum size of a tower of color $ r $ that you can form by placing down the blocks according to the rules.

## 说明/提示

In the first test case, one of the possible ways to form a tower of color $ 1 $ and size $ 3 $ is:

- place block $ 1 $ at position $ (0, 0) $ ;
- place block $ 2 $ to the right of block $ 1 $ , at position $ (1, 0) $ ;
- place block $ 3 $ above block $ 2 $ , at position $ (1, 1) $ ;
- place block $ 4 $ to the left of block $ 3 $ , at position $ (0, 1) $ ;
- place block $ 5 $ to the left of block $ 4 $ , at position $ (-1, 1) $ ;
- place block $ 6 $ above block $ 5 $ , at position $ (-1, 2) $ ;
- place block $ 7 $ to the right of block $ 6 $ , at position $ (0, 2) $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/ec98c0f164311a4ec7c2c7d82fee7c9f6eae74e7.png)The blocks at positions $ (0, 0) $ , $ (0, 1) $ , and $ (0, 2) $ all have color $ 1 $ , forming an tower of size $ 3 $ .

In the second test case, note that the following placement is not valid, since you are not allowed to place block $ 6 $ under block $ 5 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1706B/39b20d638e1634a0778efb064f52a1e1cffbd150.png)It can be shown that it is impossible to form a tower of color $ 4 $ and size $ 3 $ .

## 样例 #1

### 输入

```
6
7
1 2 3 1 2 3 1
6
4 2 2 2 4 4
1
1
5
5 4 5 3 5
6
3 3 3 1 3 3
8
1 2 3 4 4 3 2 1```

### 输出

```
3 2 2 0 0 0 0 
0 3 0 2 0 0 
1 
0 0 1 1 1 
1 0 4 0 0 0 
2 2 2 2 0 0 0 0```

# AI分析结果



# Making Towers 建塔问题

## 题目描述

给定一个长度为 $n$ 的彩色方块序列，第 $i$ 个方块颜色为 $c_i$。按以下规则在无限网格中放置方块：

1. 初始方块 1 放在 $(0, 0)$。
2. 第 $i$ 个方块（$i \ge 2$）必须放在前一个方块的左、右或上方（不能下方），且位置未被占用。

定义颜色 $r$ 的塔为同一列上连续的同色方块序列。求每个颜色 $r$ 能形成的最大塔高。

---

## 题解分析与结论

### 核心思路总结
所有题解均基于以下关键观察：**同色方块的位置差为奇数时才能形成更高塔**。因为：
- 若两同色块间隔 $k$ 个方块，需要绕 $k$ 步形成垂直叠加，此时总步数 $2k+1$ 必为奇数。
- 等价于判断两个同色块的下标差是否为奇数。

### 最优解法
#### 动态规划（奇偶状态）
维护两个状态数组 `dp[color][0/1]` 分别记录当前颜色在奇/偶位置的最大高度。遍历时根据当前块的奇偶性更新状态：
```cpp
for(int i=1; i<=n; i++) {
    f[a[i]][i&1] = max(f[a[i]][i&1], f[a[i]][!(i&1)] + 1);
}
ans = max(dp[color][0], dp[color][1]);
```
**优势**：时间复杂度 $O(n)$，空间高效。

#### 奇偶差值统计
记录每个颜色上次出现的位置 `last[color]`，若当前下标差为奇数则更新答案：
```cpp
if (las[c]==0 || (i-las[c])%2==1) {
    ans[c]++;
    las[c] = i;
}
```
**优势**：实现简洁，常数更小。

---

## 高分题解推荐

### 题解1：cachejtt（⭐️⭐️⭐️⭐️⭐️）
**亮点**：代码简洁高效，直接判断奇偶差，时间复杂度 $O(n)$。
```cpp
memset(las,0,sizeof(las));
for(int i=1; i<=n; i++){
    cin >> c;
    if(las[c]==0 || (i-las[c])%2==1){
        ans[c]++;
        las[c] = i;
    }
}
```

### 题解2：ExplodingKonjac（⭐️⭐️⭐️⭐️⭐️）
**亮点**：动态规划分奇偶状态，清晰展示转移逻辑。
```cpp
for(int i=1; i<=n; i++) 
    f[a[i]][i&1] = max(f[a[i]][i&1], f[a[i]][!(i&1)] + 1);
```

### 题解3：Jeremiahy（⭐️⭐️⭐️⭐️）
**亮点**：详细推导位置差条件，代码包含优化注释。
```cpp
if (!last[c] || (i - last[c] - 1) % 2 == 0)
    ans[c]++;
last[c] = i;
```

---

## 同类题目推荐
1. **CF1352G** - 构造奇偶交替排列（奇偶位置分析）
2. **P1896** - 互不侵犯（状态压缩 DP）
3. **P1433** - 吃奶酪（状态压缩与路径规划）

---
处理用时：42.12秒