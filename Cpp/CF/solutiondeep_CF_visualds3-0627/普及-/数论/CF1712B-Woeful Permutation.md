# 题目信息

# Woeful Permutation

## 题目描述

I wonder, does the falling rain



Forever yearn for it's disdain?

Effluvium of the Mind



You are given a positive integer $ n $ .

Find any permutation $ p $ of length $ n $ such that the sum $ \operatorname{lcm}(1,p_1) + \operatorname{lcm}(2, p_2) + \ldots + \operatorname{lcm}(n, p_n) $ is as large as possible.

Here $ \operatorname{lcm}(x, y) $ denotes the [least common multiple (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple) of integers $ x $ and $ y $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

For $ n = 1 $ , there is only one permutation, so the answer is $ [1] $ .

For $ n = 2 $ , there are two permutations:

- $ [1, 2] $ — the sum is $ \operatorname{lcm}(1,1) + \operatorname{lcm}(2, 2) = 1 + 2 = 3 $ .
- $ [2, 1] $ — the sum is $ \operatorname{lcm}(1,2) + \operatorname{lcm}(2, 1) = 2 + 2 = 4 $ .

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
1 
2 1```

# AI分析结果



## 唯一算法分类
构造

---

## 题解思路与算法要点

### 核心思路
所有题解均围绕「相邻数交换保证互质」这一核心策略：
1. **数学基础**：相邻自然数互质（gcd=1），此时 lcm(a,b)=a*b，为最大值
2. **贪心策略**：将最大的相邻数对尽可能多地配对以最大化乘积之和
3. **奇偶处理**：
   - **偶数n**：直接两两交换（2↔1,4↔3...）
   - **奇数n**：首项固定为1，剩余部分两两交换（3↔2,5↔4...）

### 关键实现步骤
```cpp
// 偶数n的处理
for(int i=1; i<=n; i+=2) 
    cout << i+1 << " " << i << " ";

// 奇数n的处理
cout << "1 ";
for(int i=2; i<=n; i+=2)
    cout << i+1 << " " << i << " ";
```

### 解决难点
1. **排列构造证明**：需证明这种构造方式确实能产生最大和，通过数学归纳法可验证小规模样例，大规模则依赖相邻数乘积最优性
2. **边界处理**：奇数情况下首项的固定与后续交换的起始位置调整

---

## 题解评分（≥4星）

| 题解作者       | 星级 | 亮点                                 |
|----------------|------|--------------------------------------|
| Dregen_Yor     | ★★★★★| 思路清晰，代码简洁，数学推导完整     |
| YYHDoggy       | ★★★★☆| 从互质与乘积角度详细分析，代码规范   |
| zfx_VeXl6      | ★★★★☆| 使用位运算简化代码，思路新颖易理解   |

---

## 最优思路提炼
**相邻对调法**：
1. **互质最大化**：通过相邻数交换确保每对数的gcd=1
2. **乘积最大化**：让大数尽可能早参与计算，如将n与n-1配对
3. **奇偶分治**：通过奇偶性处理首项问题，保证构造逻辑统一

---

## 类似算法套路
1. **构造型贪心**：如构造最大回文数、最优排列等问题
2. **互质应用**：如CF1542B Plus and Multiply 的互质性质应用
3. **相邻优化**：如滑动窗口问题中利用相邻状态优化

---

## 推荐练习题
1. [P1896 SCOI2005 互不侵犯](https://www.luogu.com.cn/problem/P1896)（相邻状态处理）
2. [P2119 魔法阵](https://www.luogu.com.cn/problem/P2119)（构造特定排列）
3. [CF1542B Plus and Multiply](https://codeforces.com/problemset/problem/1542/B)（互质性质应用）

---

## 代码实现（核心逻辑）
```cpp
#include <iostream>
using namespace std;

void solve(int n) {
    if(n & 1) {
        cout << "1 ";
        for(int i=2; i<=n; i+=2) 
            cout << i+1 << " " << i << " ";
    } else {
        for(int i=1; i<=n; i+=2)
            cout << i+1 << " " << i << " ";
    }
    cout << endl;
}

int main() {
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        solve(n);
    }
    return 0;
}
```

---

## 可视化设计
**像素动画方案**：
1. **网格布局**：用16x16像素块表示数字，按初始顺序排列
2. **交换动画**：
   - **高亮标记**：当前交换对用闪烁黄框表示
   - **滑动效果**：数字块水平滑动交换位置，伴随8-bit音效
3. **数值展示**：
   - 右侧面板实时显示当前lcm值与累加和
   - 每完成一对交换，对应位置显示爆炸粒子特效

**音效设计**：
- `swap_sound.wav`：交换时播放（8-bit电子音）
- `complete_jingle.wav`：全部完成时播放胜利旋律

**交互功能**：
- 速度滑块：调节动画速度（0.5x~3x）
- 单步执行：按空格暂停/继续，方向键步进
- 自动模式：AI自动运行，展示构造全过程

---

## 知识拓展
**互质性质证明**：
```math
\forall n \in \mathbb{N}^+, \gcd(n, n+1) = 1
```
**证明**：设d为n和n+1的公因数，则d整除(n+1)-n=1 ⇒ d=1

---
处理用时：90.01秒