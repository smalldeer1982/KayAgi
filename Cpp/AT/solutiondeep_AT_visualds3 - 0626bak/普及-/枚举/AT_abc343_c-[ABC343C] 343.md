# 题目信息

# [ABC343C] 343

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc343/tasks/abc343_c

正整数 $ N $ が与えられます。

$ N $ 以下の正整数であって回文立方数であるものの最大値を求めてください。

ただし、正整数 $ K $ は以下の $ 2 $ つの条件を満たすとき、またそのときに限り回文立方数であると定義します。

- ある正整数 $ x $ が存在し、$ x^3\ =\ K $ を満たす。
- $ K $ を先頭に $ 0 $ をつけずに $ 10 $ 進表記した文字列が回文となる。より厳密には、$ 0 $ 以上 $ 9 $ 以下の整数 $ A_0,\ A_1,\ \ldots,\ A_{L-2} $ および $ 1 $ 以上 $ 9 $ 以下の整数 $ A_{L-1} $ を用いて $ K\ =\ \sum_{i\ =\ 0}^{L-1}\ A_i10^i $ と表記したときに $ i\ =\ 0,\ 1,\ \ldots,\ L-1 $ に対して $ A_i\ =\ A_{L-1-i} $ を満たす。

## 说明/提示

### 制約

- $ N $ は $ 10^{18} $ 以下の正整数

### Sample Explanation 1

$ 343 $ は回文立方数であり、$ 344,\ 345 $ は回文立方数ではありません。したがって、$ 343 $ が答えとなります。

## 样例 #1

### 输入

```
345```

### 输出

```
343```

## 样例 #2

### 输入

```
6```

### 输出

```
1```

## 样例 #3

### 输入

```
123456789012345```

### 输出

```
1334996994331```

# AI分析结果



## 唯一算法分类
无算法分类（暴力枚举 + 回文判断）

---

## 综合分析与结论

### 核心算法流程
1. **立方根倒序枚举**：计算 N 的立方根 x_max，从 x_max 向下枚举 x
2. **回文判断**：将 x³ 转字符串后比对首尾字符
3. **提前终止**：找到第一个满足条件的立方数立即输出

### 解决难点
- **数值范围**：当 N=1e18 时，x_max=1e6，暴力枚举可行
- **回文判断优化**：字符串反转比对效率优于逐位判断
- **数据类型**：需使用 unsigned long long 或 __int128 避免溢出

### 关键可视化设计
- **像素风格显示**：用 16 色像素块表示 x 值和 x³ 值
- **回文检查高亮**：用红色闪烁标识正在比对的字符对
- **音效反馈**：
  - 立方数超限时播放低沉音效（频率 200Hz，持续 50ms）
  - 发现回文时播放胜利音效（三音阶上升旋律）
- **自动演示模式**：以 10 步/秒速度自动执行，按空格键暂停

---

## 题解清单（≥4星）

### 1. Little_x_starTYJ（5星）
- **亮点**：倒序枚举 + 提前终止
- **代码亮点**：`cbrt(n)+1` 起始点优化
```cpp
for (unsigned long long i = cbrt(n) + 1; ; i--) {
    if (i*i*i > n) continue;
    // 回文判断后直接 return
}
```

### 2. OIerWu_829（4星）
- **亮点**：正序枚举记录最大值
- **优化点**：循环边界明确 `i*i*i <= n`
```cpp
for (int i = 1; i*i*i <= n; i++)
    if (check(i*i*i)) ans = i*i*i;
```

### 3. Albatross_LC（4星）
- **亮点**：二分法求立方根
- **特殊处理**：使用 __int128 防溢出
```cpp
while (l < r) {
    int mid = ((__int128)l + r + 1) >> 1;
    // 二分查找立方根
}
```

---

## 最优思路与技巧

### 核心实现思想
```cpp
unsigned long long x_max = cbrt(n); // 确定枚举上界
for (x = x_max; x >= 1; x--) {      // 倒序枚举
    cube = x*x*x;
    if (cube > n) continue;          // 提前跳过超限值
    if (is_palindrome(cube)) {       // 字符串回文判断
        cout << cube;
        return 0;                    // 找到即终止
    }
}
```

### 关键优化技巧
- **倒序枚举**：第一个满足条件的解即为最大值
- **立方根计算**：将枚举次数从 1e6 降为最多 1e6 次
- **字符串比对**：时间复杂度 O(1)（因数字长度最多 18 位）

---

## 类似题目推荐
1. [P1217 [USACO1.5] 回文质数](https://www.luogu.com.cn/problem/P1217)
   - 回文数 + 质数判断
2. [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
   - 数学枚举 + 边界优化
3. [P2415 集合求和](https://www.luogu.com.cn/problem/P2415)
   - 数学性质分析 + 暴力枚举

---

## 个人心得摘录
> **littlebug 的调试经验**：  
> “要正确理解题意，不要像我似的以为是 k 要回文而不是 k³”  
> **启示**：仔细阅读题目条件，明确回文判断对象是立方数本身而非底数

---

## 可视化算法演示

### 复古像素风格设计
```javascript
// Canvas 初始化（伪代码）
const canvas = initCanvas(640, 480);
const palette = ["#000","#F00","#0F0","#00F","#FF0"]; // 复古 16 色

// 绘制当前状态
function drawState(x, cube, isPalindrome) {
    drawText(`x=${x}`, 10, 20, palette[2]);         // 绿色显示当前 x
    drawText(`x³=${cube}`, 10, 40, palette[1]);     // 红色显示立方数
    if (isPalindrome) {
        drawRect(50, 100, 100, 20, palette[3]);     // 蓝色矩形框标识回文
    }
}

// 音效触发
function playSound(freq) {
    const osc = new OscillatorNode(ctx, {frequency: freq});
    osc.connect(ctx.destination);
    osc.start(); osc.stop(0.05);
}
```

### 动画流程示例
1. **初始化**：显示 x_max=1e6 和立方数 1e18
2. **步进枚举**：x 递减，立方数显示红色闪烁边框
3. **回文检查**：比对字符时高亮对应数字位
4. **找到解**：播放胜利音效，立方数变为绿色锁定

---

## 代码实现（核心逻辑）

### 最优题解完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    unsigned long long n;
    cin >> n;
    for (unsigned long long x = cbrt(n) + 1; ; x--) {
        unsigned long long cube = x * x * x;
        if (cube > n) continue;
        string s = to_string(cube);
        if (s == string(s.rbegin(), s.rend())) {
            cout << cube;
            return 0;
        }
    }
    cout << 1; // 处理 x=0 的边界情况
    return 0;
}
```

### 音效触发代码示例
```javascript
// Web Audio API 音效
function playTone(freq, duration = 100) {
    const ctx = new AudioContext();
    const osc = ctx.createOscillator();
    osc.type = 'square'; // 8-bit 方波音色
    osc.frequency.value = freq;
    osc.connect(ctx.destination);
    osc.start(); osc.stop(ctx.currentTime + duration/1000);
}
// 触发示例：发现回文时
if (is_palindrome) playTone(880, 200); // 高音 La
```

---
处理用时：72.37秒