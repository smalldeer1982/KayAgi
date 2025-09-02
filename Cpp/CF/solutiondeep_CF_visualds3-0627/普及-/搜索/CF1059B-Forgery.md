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



# 题解分析

## 一、算法分类  
**其他搜索**（核心为枚举所有可能的操作中心点）

---

## 二、题解思路与解决难点  
**核心思路**：  
1. **逆向模拟**：从目标矩阵出发，枚举所有可能的 3x3 操作中心点，检查其周围 8 格是否全为 `#`。若满足条件，则在模拟矩阵中染色这 8 格。
2. **比对验证**：最终将模拟矩阵与目标矩阵比对，完全一致则输出 `YES`，否则 `NO`。

**难点与解决**：  
- **边界处理**：操作中心点必须确保 3x3 区域不越界，需限定遍历范围（如 `2 ≤ i ≤ n-1`）。
- **染色覆盖**：多次染色允许覆盖，无需考虑顺序，只需确保所有可能的操作都被执行。
- **时间复杂度**：O(nm) 的枚举策略可处理最大 1000x1000 的数据规模。

---

## 三、题解评分 (≥4星)  
1. **Abyss_Bright (5星)**  
   - **亮点**：代码结构清晰，利用方向数组简化周围格子遍历，通过标记 `biao` 快速判断是否可染色。
   - **代码可读性**：变量命名明确，注释详细，适合初学者理解。

2. 「已注销」 (4星)  
   - **亮点**：直接枚举所有可能的操作中心，使用预定义的 `dx, dy` 数组表示 3x3 区域偏移，代码简洁。
   - **优化点**：合并输入与模拟矩阵初始化，减少内存访问次数。

3. 氢氧化铯CsOH (4星)  
   - **亮点**：通过 `vis` 数组记录染色区域，最终检查未染色的 `#` 是否存在，逻辑严谨。
   - **代码风格**：使用 `const` 和函数封装提高可维护性。

---

## 四、最优思路提炼  
1. **关键技巧**：  
   - **方向数组**：预定义 8 个方向的偏移量，简化周围格子遍历。
   - **模拟染色**：通过二维数组记录染色结果，避免原地修改导致干扰。
   - **逆向验证**：从目标出发推断可能的操作，而非正向模拟所有步骤。

2. **思维角度**：  
   - 将问题转化为“覆盖问题”——所有 `#` 必须被至少一次染色操作覆盖，且染色操作必须符合目标结构。

---

## 五、同类型题与算法套路  
- **类似题目**：  
  - **覆盖问题**：如用特定形状的瓦片铺满网格（[洛谷 P1219](https://www.luogu.com.cn/problem/P1219)）。  
  - **逆向构造**：如给定最终状态，判断是否可通过特定操作生成（[CF 1059B](https://codeforces.com/contest/1059/problem/B)）。  

- **通用解法**：  
  - 枚举所有可能的操作，模拟其影响，最后验证结果是否匹配目标。

---

## 六、推荐相似题目  
1. [P1219 八皇后](https://www.luogu.com.cn/problem/P1219) - 回溯枚举合法位置。  
2. [CF 1059B](https://codeforces.com/contest/1059/problem/B) - 同题，可对比不同解法效率。  
3. [P1583 魔法照片](https://www.luogu.com.cn/problem/P1583) - 通过规则逆向推导初始状态。  

---

## 七、个人心得摘录  
- **Abyss_Bright**：强调方向数组的灵活使用，指出“多次染色无需考虑顺序”是解题关键。  
- **Forever1507**：提到深搜在本题中效率劣于枚举，提醒优先选择时间复杂度更优的方法。  

---

## 八、可视化与算法演示  
**动画方案设计**：  
1. **网格绘制**：  
   - 使用 Canvas 绘制 n×m 网格，初始全灰（代表 `.`）。  
   - 目标矩阵中的 `#` 显示为红色，模拟染色区域显示为蓝色。  

2. **染色过程**：  
   - **步进染色**：高亮当前操作中心（黄色），显示其 3x3 区域，若满足条件则染色周围 8 格为蓝色。  
   - **音效触发**：每次成功染色播放短促“滴”声，失败（越界或格子不为 `#`）播放低沉“嘟”声。  

3. **最终比对**：  
   - 正确时全屏绿色闪烁 + 胜利音效；错误时红色闪烁 + 失败音效。  

**复古像素风格**：  
- **调色板**：8 位风格，使用有限颜色（红、蓝、黄、绿）。  
- **音效**：芯片音乐风格，使用 Web Audio API 生成方波音效。  

**自动演示模式**：  
- **AI 控制**：自动遍历所有可能的中心点，按行优先顺序执行染色操作。  
- **速度调节**：滑动条控制每步间隔（100ms~2s），支持暂停/继续。  

---

## 九、核心代码实现  
```cpp
// 方向数组定义
int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

// 枚举所有可能的操作中心
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
        bool can_paint = true;
        // 检查周围8格是否全为'#'
        for (int k = 0; k < 8; ++k) {
            int ni = i + dx[k], nj = j + dy[k];
            if (ni < 1 || ni > n || nj < 1 || nj > m || target[ni][nj] != '#') {
                can_paint = false;
                break;
            }
        }
        if (!can_paint) continue;
        // 在模拟矩阵中染色
        for (int k = 0; k < 8; ++k) {
            int ni = i + dx[k], nj = j + dy[k];
            sim[ni][nj] = '#';
        }
    }
}
// 比对结果
bool ok = true;
for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
        if (target[i][j] != sim[i][j]) ok = false;
cout << (ok ? "YES" : "NO");
```

---
处理用时：80.35秒