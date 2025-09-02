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



**唯一算法分类**: 数论-质数判断与因数分解

---

### 综合分析与结论

**核心思路**:  
题目要求通过最多 20 次询问判断隐藏数是否为质数。关键在于：  
1. **质数列表筛选**：所有 ≤50 的质数（如 2,3,5,...,47），确保覆盖所有可能的最小质因子。  
2. **平方数检测**：针对形如 \( p^2 \) 的合数（如 4,9,25,49），需额外检查质数的平方是否为因子。  

**难点与解决方案**:  
- **质数范围选择**：隐藏数 ≤100，其最小质因子必 ≤50（否则另一因子 ≥2，乘积超过 100），故质数列表仅需 2~47 的质数。  
- **平方数处理**：若隐藏数是 \( p^2 \)，询问 \( p \) 后需再问 \( p^2 \) 以确认是否合数。  

**可视化设计思路**:  
- **动画流程**：高亮当前询问的数，绿色标记 `yes`，红色标记 `no`。当检测到两次 `yes` 时，立即触发合数判定动画。  
- **复古风格**：8-bit 像素界面，质数列表以网格展示，音效配合每次询问和判定结果。  

---

### 题解清单（≥4星）

1. **lukelin（5星）**  
   - **亮点**：动态检查质数的平方，优化询问次数，提前终止逻辑。  
   - **代码**：清晰处理质数列表，实时计算平方数，避免冗余查询。  

2. **PC_DOS（4星）**  
   - **亮点**：合并质数与平方数到固定列表，代码简洁易懂。  
   - **实现**：19 次固定询问，覆盖所有可能因子。  

3. **stdout（4星）**  
   - **亮点**：显式列出质数与平方数，逻辑直白，适合快速理解。  

---

### 最优思路提炼

1. **质数列表**：所有 ≤50 的质数（共 15 个）。  
2. **平方数检测**：对每个质数 \( p \)，若 \( p \times p \leq 100 \)，则在 \( p \) 回答 `yes` 后询问 \( p^2 \)。  
3. **快速终止**：若累计 `yes` ≥2，立即输出 `composite`。  

**代码片段（lukelin 核心逻辑）**:
```cpp
for (int i = 0; i < p_num; ++i) {
    cout << prime[i] << endl; // 询问质数 prime[i]
    cin >> s;
    if (s[0] == 'y') {
        if (prime[i] * prime[i] <= 100) {
            cout << prime[i] * prime[i] << endl; // 询问平方数
            cin >> s;
            if (s[0] == 'y') {
                cout << "composite" << endl; // 二次 yes，直接判定
                return 0;
            }
        }
        ++cnt;
        if (cnt >= 2) { // 累计两次 yes
            cout << "composite" << endl;
            return 0;
        }
    }
}
```

---

### 类似题目推荐

1. **P3383** 【模板】线性筛素数  
2. **P1217** [USACO1.5] 回文质数  
3. **P1304** 哥德巴赫猜想  

---

### 个人心得摘录

- **踩坑记录**：多位作者提到首次未处理平方数导致 WA，如 49 需额外检测。  
- **优化顿悟**：动态询问平方数比固定列表更节省次数，适合尽早终止。  

---

### 可视化与游戏化设计

**像素动画方案**:  
1. **界面布局**：质数列表以 8x8 像素块排列，当前询问数闪烁。  
2. **音效设计**：  
   - 每次询问播放 "beep" 音效。  
   - 判定 `composite` 时播放低音效，`prime` 播放高音效。  
3. **自动演示模式**：AI 逐步询问质数，若模拟隐藏数为合数，随机触发平方数检测。  

**关键代码（伪）**:  
```javascript
// 模拟质数询问动画
function animateQuery(prime) {
    highlight(prime); // 高亮当前质数
    playSound('query'); // 播放询问音效
    if (isDivisor(prime)) {
        markYes(prime); // 标记为 yes
        if (prime * prime <= 100) {
            animateQuery(prime * prime); // 递归询问平方数
        }
    }
}
```

---

**总结**：通过质数筛选与平方数检测，结合动态优化策略，可在 20 次询问内高效判定质数。复古动画与音效增强学习趣味性。

---
处理用时：144.88秒