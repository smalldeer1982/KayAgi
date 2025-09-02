# 题目信息

# [ABC336D] Pyramid

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc336/tasks/abc336_d

正の整数 $ k $ について、サイズ $ k $ の **ピラミッド数列** とは、長さ $ (2k-1) $ の数列であって各項の値が順に $ 1,2,\ldots,k-1,k,k-1,\ldots,2,1 $ であるようなものをさします。

長さ $ N $ の数列 $ A=(A_1,A_2,\ldots,A_N) $ が与えられます。  
 $ A $ に対して、次の操作のうち一方を選んで行うことを繰り返して ($ 0 $ 回でも良い) 得ることのできるピラミッド数列のサイズの最大値を求めてください。

- 数列の項を $ 1 $ つ選び、その項の値を $ 1 $ 減少させる。
- 先頭または末尾の項を削除する。
 
なお、問題の制約のもとで、操作を繰り返すことで必ず $ 1 $ 種類以上のピラミッド数列を得ることができることが証明できます。

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

$ A=(2,2,3,1,1) $ から始めて、 次のようにして数列 $ A $ からサイズ $ 2 $ のピラミッド数列を作る事ができます。 - 第 $ 3 $ 項を選び、$ 1 $ 減少させる。数列は $ A=(2,2,2,1,1) $ となる。 - 先頭を削除する。数列は $ A=(2,2,1,1) $ となる。 - 末尾を削除する。数列は $ A=(2,2,1) $ となる。 - 第 $ 1 $ 項を選び、$ 1 $ 減少させる。数列は $ A=(1,2,1) $ となる。 $ (1,2,1) $ はサイズ $ 2 $ のピラミッド数列です。 一方、どのように操作を行ってもサイズ $ 3 $ 以上のピラミッド数列を作ることはできないため $ 2 $ を出力します。

## 样例 #1

### 输入

```
5

2 2 3 1 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5

1 2 3 4 5```

### 输出

```
3```

## 样例 #3

### 输入

```
1

1000000000```

### 输出

```
1```

# AI分析结果



# 【题目翻译】

## [ABC336D] Pyramid

### 题目描述

给定一个正整数 $k$，称大小为 $k$ 的**金字塔数列**是长度为 $(2k-1)$ 的数列，其各项值依次为 $1,2,\ldots,k-1,k,k-1,\ldots,2,1$。

现给定长度为 $N$ 的数列 $A=(A_1,A_2,\ldots,A_N)$，可以通过以下两种操作（可执行任意次，包括零次）将其转换为金字塔数列，求能得到的最大的金字塔数列的大小：
- 选择数列中的某一项，将其值减 1
- 删除数列的首项或末项

### 输入格式
第一行输入整数 $N$  
第二行输入数列 $A$

### 输出格式
输出最大金字塔数列的大小

### 样例解释 #1
输入：  
5  
2 2 3 1 1  

输出：  
2  
（通过操作得到序列 [1,2,1]，对应大小为 2 的金字塔数列）

---

# 1. 算法分类
**线性DP**

# 2. 综合分析与结论

## 核心思路
通过预处理左右两个方向的最长递增序列，最终取最小值得到最大金字塔大小：
1. **左金字塔数组** `f[i]`：以 $A_i$ 结尾的最长递增序列长度
2. **右金字塔数组** `g[i]`：以 $A_i$ 开头的最长递减序列长度
3. **状态转移方程**：
   - `f[i] = min(f[i-1]+1, A[i])`
   - `g[i] = min(g[i+1]+1, A[i])`
4. **最终答案**：所有位置 `min(f[i], g[i])` 的最大值

## 解决难点
- **操作转化**：将复杂的删除操作转化为对数列长度的限制
- **对称结构**：利用金字塔的对称性拆分左右两半处理
- **线性复杂度**：通过递推式实现 O(n) 时间预处理

## 可视化设计
**动态规划矩阵更新动画**：
1. 用双色网格表示 `f` 和 `g` 数组的更新过程
2. 高亮当前更新的位置，显示转移来源（前一个位置的值+1 或当前值）
3. 最终用第三色标记每个位置的瓶颈值 `min(f[i], g[i])`

![金字塔DP示意图](https://cdn.luogu.com.cn/upload/image_hosting/8q6y1qj6.png)

# 3. 题解清单（评分≥4星）

## 作者：BIG_CUTE_BUG（★★★★★）
**亮点**：
- 最简洁的递推实现
- 完整注释说明状态转移逻辑
```cpp
for(int i=1; i<=n; i++)
    q[i] = min(q[i-1]+1, a[i]);
for(int i=n; i>=1; i--)
    p[i] = min(p[i+1]+1, a[i]);
```

## 作者：Saka_Noa（★★★★☆）
**亮点**：
- 引入左右金字塔的直观解释
- 代码包含边界初始化
```cpp
lef[1] = 1, rit[n] = 1;
for(int i=2; i<=n; i++)
    lef[i] = min(lef[i-1]+1, a[i]);
```

## 作者：xz001（★★★★☆）
**亮点**：
- 使用二维数组统一处理左右方向
- 完整变量命名增强可读性
```cpp
f[i][0] = min(f[i-1][0]+1, a[i]);
f[i][1] = min(f[i+1][1]+1, a[i]);
```

# 4. 核心代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5+5;
int n, a[N], f[N], g[N];

int main() {
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d", a+i);
    
    // 左金字塔递推
    for(int i=1; i<=n; ++i) 
        f[i] = min(f[i-1]+1, a[i]);
    
    // 右金字塔递推 
    for(int i=n; i>=1; --i)
        g[i] = min(g[i+1]+1, a[i]);
    
    int ans = 0;
    for(int i=1; i<=n; ++i)
        ans = max(ans, min(f[i], g[i]));
    
    printf("%d", ans);
    return 0;
}
```

# 5. 同类型题目
1. **接雨水**（LeetCode 42）：预处理左右最大值
2. **最大矩形面积**（LeetCode 84）：单调栈处理左右边界
3. **最长山脉数组**（LeetCode 845）：结合递增递减序列

# 6. 推荐练习题
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1508 Likecloud-吃、吃、吃](https://www.luogu.com.cn/problem/P1508)
3. [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)

# 7. 个人心得摘录
> "原本尝试二分答案，但发现构造验证条件需要 O(n^2) 时间。突然意识到金字塔的对称性可以拆分为左右两半独立处理，这成为解题的关键转折点。" —— 作者：Elysian_Realme

# 8. 可视化设计要点

## 复古像素风格实现
```javascript
// 初始化 Canvas
const canvas = document.getElementById('dp-canvas');
const ctx = canvas.getContext('2d');
const TILE_SIZE = 16; // 16x16像素块

// 绘制DP矩阵
function drawDP(arr, color) {
    arr.forEach((val, i) => {
        ctx.fillStyle = color;
        ctx.fillRect(i*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
        ctx.fillStyle = 'white';
        ctx.fillText(val, i*TILE_SIZE+2, TILE_SIZE-2);
    });
}

// 音效系统
const sfx = {
    update: new Audio('blip.wav'),    // 状态更新音效
    bottleneck: new Audio('ping.wav') // 瓶颈值发现音效
};

// 自动演示
let step = 0;
function autoPlay() {
    if(step > n) return;
    
    // 更新左金字塔数组
    if(step <= n) {
        f[step] = Math.min(f[step-1]+1, a[step]);
        drawDP(f, '#FF5555'); 
        sfx.update.play();
    }
    
    // 更新右金字塔数组
    if(step >= n) {
        g[n-step] = Math.min(g[n-step+1]+1, a[n-step]);
        drawDP(g, '#5555FF');
        sfx.update.play();
    }
    
    step++;
    requestAnimationFrame(autoPlay);
}
```

## 交互功能
- **WASD控制**：手动步进查看状态转移
- **空格键**：切换自动/手动模式
- **数字键1-3**：切换不同题解的可视化对比

## 像素风格特征
- 使用NES经典16色调色板
- 状态更新时像素块抖动特效
- 背景播放《俄罗斯方块》风格BGM

---
处理用时：89.47秒