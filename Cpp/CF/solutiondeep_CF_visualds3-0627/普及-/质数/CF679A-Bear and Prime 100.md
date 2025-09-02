# 题目信息

# Bear and Prime 100

## 题目描述

This is an interactive problem. In the output section below you will see the information about flushing the output.

Bear Limak thinks of some hidden number — an integer from interval $ [2,100] $ . Your task is to say if the hidden number is prime or composite.

Integer $ x>1 $ is called prime if it has exactly two distinct divisors, $ 1 $ and $ x $ . If integer $ x>1 $ is not prime, it's called composite.

You can ask up to $ 20 $ queries about divisors of the hidden number. In each query you should print an integer from interval $ [2,100] $ . The system will answer "yes" if your integer is a divisor of the hidden number. Otherwise, the answer will be "no".

For example, if the hidden number is $ 14 $ then the system will answer "yes" only if you print $ 2 $ , $ 7 $ or $ 14 $ .

When you are done asking queries, print "prime" or "composite" and terminate your program.

You will get the Wrong Answer verdict if you ask more than $ 20 $ queries, or if you print an integer not from the range $ [2,100] $ . Also, you will get the Wrong Answer verdict if the printed answer isn't correct.

You will get the Idleness Limit Exceeded verdict if you don't print anything (but you should) or if you forget about flushing the output (more info below).

## 说明/提示

The hidden number in the first query is $ 30 $ . In a table below you can see a better form of the provided example of the communication process.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/b5d048578748c4adde3d49c36a749660a61701b4.png)

The hidden number is divisible by both $ 2 $ and $ 5 $ . Thus, it must be composite. Note that it isn't necessary to know the exact value of the hidden number. In this test, the hidden number is $ 30 $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF679A/f54f8d5adb5e9403a147185e0d841ee7fbfd7d7b.png)

 $ 59 $ is a divisor of the hidden number. In the interval $ [2,100] $ there is only one number with this divisor. The hidden number must be $ 59 $ , which is prime. Note that the answer is known even after the second query and you could print it then and terminate. Though, it isn't forbidden to ask unnecessary queries (unless you exceed the limit of $ 20 $ queries).

## 样例 #1

### 输入

```
yes
no
yes
```

### 输出

```
2
80
5
composite
```

## 样例 #2

### 输入

```
no
yes
no
no
no
```

### 输出

```
58
59
78
78
2
prime
```

# AI分析结果



## 唯一算法分类
数论与质数判断

---

## 综合分析与结论

### 核心思路
1. **质数与平方数检测**：所有 ≤50 的质数（共 15 个）必须被检测。若隐藏数为合数，则至少能被其中两个质数整除，或能被一个质数的平方整除。
2. **优化询问策略**：对于每个质数 `p`，若 `p` 是因子，进一步检测 `p²`（若 `p² ≤ 100`）。若 `p²` 也是因子，直接判定为合数。
3. **提前终止**：一旦检测到两次 "yes" 回答或平方数的存在，立即终止并返回结果。

### 解决难点
- **平方数的特殊处理**：如 4、9、25、49 等由单个质数平方构成的合数需额外检测。
- **询问次数优化**：通过动态检测质数的平方，减少不必要的总询问次数，确保不超过 20 次限制。

---

## 题解清单（评分 ≥4 星）

### 1. lukelin 的题解（5 星）
- **亮点**：动态检测质数的平方，代码高效且逻辑清晰。
- **核心代码**：
  ```cpp
  if (s[0] == 'y') {
    if ((prime[i] * prime[i]) <= 100) {
      cout << (prime[i] * prime[i]) << endl;
      cin >> s;
      if (s[0] == 'y') return 0; // 直接判定合数
    }
    ++cnt;
  }
  ```

### 2. PC_DOS 的题解（4 星）
- **亮点**：合并质数和平方数列表，代码简洁易懂。
- **核心代码**：
  ```cpp
  int arrAsk[19] = {2,3,4,5,9,7,11,...,49};
  if (nCount >= 2) goto endapp; // 立即终止
  ```

### 3. N_z_ 的题解（5 星）
- **亮点**：紧凑的代码结构，同时处理质数和平方数检测。
- **核心代码**：
  ```cpp
  if (s[0] == 'y') {
    cnt++;
    if (a[x] * a[x] <= 100) {
      cout << a[x] * a[x] << endl;
      if (s[0] == 'y') cnt++;
    }
  }
  ```

---

## 最优思路与技巧提炼
1. **质数范围选择**：仅需检测 ≤50 的质数，因任何合数必有一个因子 ≤50。
2. **平方数检测**：若 `p` 是因子且 `p² ≤ 100`，必须检测 `p²` 以避免漏判。
3. **提前终止机制**：一旦确定结果，立即退出以减少不必要的询问。

---

## 类似题目推荐
1. **CF679C**：基于质因数分解的网格搜索。
2. **洛谷 P3383**：线性筛质数的扩展应用。
3. **LeetCode 204**：统计质数数量（埃氏筛法的变种）。

---

## 可视化设计（复古像素风格）

### 算法演示
1. **像素动画**：在 Canvas 上绘制质数列表，逐步高亮当前询问的数。
   - **质数**显示为绿色方块，**平方数**显示为黄色方块。
   - 当回答为 "yes" 时，方块变为红色，并触发音效。
2. **音效设计**：
   - **询问**：8-bit 短音效。
   - **判定成功**：上扬音调。
3. **交互控制**：允许调整动画速度，单步执行或自动播放。

### 代码片段（JavaScript）
```javascript
// 初始化 Canvas 和音效
const primes = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47];
const squares = [4,9,25,49];
let step = 0;

function drawStep() {
  // 绘制当前询问的数（像素风格）
  ctx.fillStyle = "#00FF00"; // 绿色质数
  ctx.fillRect(x, y, 16, 16);
  if (response === "yes") {
    playSound("yes_sound");
    ctx.fillStyle = "#FF0000"; // 红色高亮
  }
}
```

---

## 个人心得摘录
- **调试教训**：初始未处理平方数导致多次 WA，需仔细验证边界条件。
- **优化感悟**：动态检测平方数显著减少询问次数，优于固定列表。

---
处理用时：218.70秒