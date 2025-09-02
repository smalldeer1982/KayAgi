# 题目信息

# Divisibility Rules

## 题目描述

Vasya studies divisibility rules at school. Here are some of them:

- Divisibility by $ 2 $ . A number is divisible by $ 2 $ if and only if its last digit is divisible by $ 2 $ or in other words, is even.
- Divisibility by $ 3 $ . A number is divisible by $ 3 $ if and only if the sum of its digits is divisible by $ 3 $ .
- Divisibility by $ 4 $ . A number is divisible by $ 4 $ if and only if its last two digits form a number that is divisible by $ 4 $ .
- Divisibility by $ 5 $ . A number is divisible by $ 5 $ if and only if its last digit equals $ 5 $ or $ 0 $ .
- Divisibility by $ 6 $ . A number is divisible by $ 6 $ if and only if it is divisible by $ 2 $ and $ 3 $ simultaneously (that is, if the last digit is even and the sum of all digits is divisible by $ 3 $ ).
- Divisibility by $ 7 $ . Vasya doesn't know such divisibility rule.
- Divisibility by $ 8 $ . A number is divisible by $ 8 $ if and only if its last three digits form a number that is divisible by $ 8 $ .
- Divisibility by $ 9 $ . A number is divisible by $ 9 $ if and only if the sum of its digits is divisible by $ 9 $ .
- Divisibility by $ 10 $ . A number is divisible by $ 10 $ if and only if its last digit is a zero.
- Divisibility by $ 11 $ . A number is divisible by $ 11 $ if and only if the sum of digits on its odd positions either equals to the sum of digits on the even positions, or they differ in a number that is divisible by $ 11 $ .

Vasya got interested by the fact that some divisibility rules resemble each other. In fact, to check a number's divisibility by $ 2 $ , $ 4 $ , $ 5 $ , $ 8 $ and $ 10 $ it is enough to check fulfiling some condition for one or several last digits. Vasya calls such rules the  $ 2 $ -type rules.

If checking divisibility means finding a sum of digits and checking whether the sum is divisible by the given number, then Vasya calls this rule the  $ 3 $ -type rule (because it works for numbers $ 3 $ and $ 9 $ ).

If we need to find the difference between the sum of digits on odd and even positions and check whether the difference is divisible by the given divisor, this rule is called the  $ 11 $ -type rule (it works for number $ 11 $ ).

In some cases we should divide the divisor into several factors and check whether rules of different types ( $ 2 $ -type, $ 3 $ -type or $ 11 $ -type) work there. For example, for number $ 6 $ we check $ 2 $ -type and $ 3 $ -type rules, for number $ 66 $ we check all three types. Such mixed divisibility rules are called  $ 6 $ -type rules.

And finally, there are some numbers for which no rule works: neither $ 2 $ -type, nor $ 3 $ -type, nor $ 11 $ -type, nor $ 6 $ -type. The least such number is number $ 7 $ , so we'll say that in such cases the mysterious  $ 7 $ -type rule works, the one that Vasya hasn't discovered yet.

Vasya's dream is finding divisibility rules for all possible numbers. He isn't going to stop on the decimal numbers only. As there are quite many numbers, ha can't do it all by himself. Vasya asked you to write a program that determines the divisibility rule type in the $ b $ -based notation for the given divisor $ d $ .

## 说明/提示

The divisibility rule for number $ 3 $ in binary notation looks as follows: "A number is divisible by $ 3 $ if and only if the sum of its digits that occupy the even places differs from the sum of digits that occupy the odd places, in a number that is divisible by $ 3 $ ". That's an $ 11 $ -type rule. For example, $ 21_{10}=10101_{2} $ . For it the sum of digits on odd positions equals $ 1+1+1=3 $ , an on even positions — $ 0+0=0 $ . The rule works and the number is divisible by $ 3 $ .

In some notations a number can fit into the $ 3 $ -type rule and the $ 11 $ -type rule. In this case the correct answer is "3-type".

## 样例 #1

### 输入

```
10 10
```

### 输出

```
2-type
1
```

## 样例 #2

### 输入

```
2 3
```

### 输出

```
11-type
```

# AI分析结果


### 💡 Kay的C++算法解析：Divisibility Rules 深入学习指南 💡

#### 题目解读与核心算法识别
✨ **本题主要考察**：`数学推导与数论应用`  
🗣️ **初步分析**：  
> 解决本题的关键在于**数学推导**，就像侦探通过线索推理案件真相。我们需要通过数论知识分析不同整除规则的本质特征：  
> - **2-type规则**：本质是检验除数d是否完全由进制b的质因数组成（通过反复除以gcd(b,d)实现）  
> - **3-type规则**：依赖(b-1)被d整除的特性（类比十进制中3的整除规则）  
> - **11-type规则**：依赖(b+1)被d整除的特性（类似二进制中3的规则）  
> - **6-type规则**：组合规则（需同时满足lcm(b-1,b+1)整除d）  
>  
> **可视化设计思路**：  
> 采用**像素化学因子分解动画**：  
> 1. 用不同颜色像素块表示b和d的质因数  
> 2. 2-type化简时，显示相同颜色块相消的动画  
> 3. 判断其他类型时，展示(b-1)/(b+1)像素块与剩余d的包含关系  
> 4. 音效设计：质因数相消时触发"叮"声，规则匹配时播放胜利音效  

---

#### 精选优质题解参考
**题解（作者：MyukiyoMekya）**  
* **点评**：  
  思路清晰揭示数学本质：  
  - **逻辑推导**：将抽象规则转化为gcd/lcm运算（如2-type化简的循环设计）  
  - **代码规范**：变量名`p`(base), `d`(divisor) 含义明确，边界处理严谨（y!=1时分类判断）  
  - **算法优化**：利用`__gcd`内置函数实现O(log n)高效化简  
  - **实践价值**：完整覆盖所有规则类型，可直接用于竞赛  

---

#### 核心难点辨析与解题策略
1. **难点：数学条件推导**  
   * **分析**：需发现3-type依赖(b-1)整除d，11-type依赖(b+1)整除d。优质题解通过多项式分解（如∑aᵢ(bⁱ-1)≡0 mod d）揭示本质  
   * 💡 **学习笔记**：整除规则本质是进制b在模d下的同余性质  

2. **难点：混合规则处理**  
   * **分析**：6-type要求组合验证（lcm(b-1,b+1)整除d）。题解用`lcm(p+1,p-1)%y==0`统一判断，避免冗余计算  
   * 💡 **学习笔记**：lcm(a,b) = ab/gcd(a,b) 是处理混合条件的关键工具  

3. **难点：规则互斥性处理**  
   * **分析**：2-type化简优先于其他规则（cnt>0时跳过3/11-type）。需注意判断顺序：先2-type→再3/11-type→最后6-type  
   * 💡 **学习笔记**：算法流程设计需考虑条件优先级  

**✨ 解题技巧总结**  
- **质因数分解思维**：将整除问题转化为质因子包含关系（2-type核心）  
- **同余定理应用**：利用 (bᵏ ≡ 1 mod d) 推导3-type条件  
- **LCM整合判断**：用lcm处理多条件复合场景（6-type）  

---

#### C++核心代码实现赏析
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int p, d, y; // p:进制, d:除数, y:中间变量
    cin >> p >> d; 
    y = d;
    int cnt = 0; // 记录2-type需要的位数

    // 2-type化简：不断消去b和d的公因子
    while (__gcd(p, y) > 1) {
        cnt++;
        y /= __gcd(p, y);
    }

    if (y == 1) { // 2-type成立
        cout << "2-type\n" << cnt; 
    } else if (lcm(p+1, p-1) % y == 0) { // 6-type大条件
        if (cnt == 0 && (p-1) % y == 0) cout << "3-type"; 
        else if (cnt == 0 && (p+1) % y == 0) cout << "11-type";
        else cout << "6-type"; // 混合类型
    } else {
        cout << "7-type"; // 无规则
    }
    return 0;
}
```

**代码解读概要**：  
1. **2-type化简循环**：通过`y /= gcd(p,y)`逐步消除d中与b相同的质因子  
2. **规则优先级判断**：先检查2-type → 再通过lcm判断6-type → 最后细化3/11-type  
3. **LCM自定义实现**：`lcm(a,b) = a*b/gcd(a,b)` 确保高效计算  

---

#### 算法可视化：像素动画演示
**主题**：质因数消消乐（8-bit像素风格）  

**动画流程**：  
1. **初始化**：  
   - 顶部显示b和d的像素化质因数分解（不同颜色方块）  
   - 控制面板含速度滑块/单步执行按钮  
   - 背景播放8-bit轻快BGM  

2. **2-type化简演示**：  
   ```mermaid
   graph LR
   A[原d: ▮▮▮▮] --> B{计算gcd(b,d)}
   B -->|消去相同方块| C[新d: ▮▮]
   C --> D{继续化简?}
   D -->|Yes| B
   D -->|No| E[显示cnt计数]
   ```

3. **规则匹配判定**：  
   - 3-type：显示(b-1)方块覆盖剩余d方块（成功时闪烁绿光+胜利音效）  
   - 11-type：(b+1)方块覆盖d（蓝光+不同音效）  
   - 7-type：d方块抖动+红色警告光效  

4. **交互设计**：  
   - 点击质因数显示其数值  
   - "AI演示"模式自动完成全过程  

---

#### 拓展练习与相似问题
1. **洛谷 P1082**：同余方程（练习gcd推导）  
   *→ 掌握扩展欧几里得在规则推导中的应用*  
2. **洛谷 P1069**：细胞分裂（质因数分解进阶）  
   *→ 强化2-type的质因子包含思维*  
3. **洛谷 P4549**：裴蜀定理（数论基础）  
   *→ 理解同余式推导的数学基础*  

---

#### 学习心得与经验分享
本次题解未包含作者个人心得，但实践中需注意：  
> **调试技巧**：当d=1边界条件失效时，打印while循环中gcd值和y值可快速定位逻辑错误  

---
通过本指南，相信大家已掌握整除规则背后的数论本质。记住：编程中的数学就像魔法——理解原理才能创造奇迹！✨

---
处理用时：97.22秒