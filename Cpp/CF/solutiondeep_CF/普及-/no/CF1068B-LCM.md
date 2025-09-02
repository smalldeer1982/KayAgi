# 题目信息

# LCM

## 题目描述

Ivan has number $ b $ . He is sorting through the numbers $ a $ from $ 1 $ to $ 10^{18} $ , and for every $ a $ writes $ \frac{[a, \,\, b]}{a} $ on blackboard. Here $ [a, \,\, b] $ stands for least common multiple of $ a $ and $ b $ . Ivan is very lazy, that's why this task bored him soon. But he is interested in how many different numbers he would write on the board if he would finish the task. Help him to find the quantity of different numbers he would write on the board.

## 说明/提示

In the first example $ [a, \,\, 1] = a $ , therefore $ \frac{[a, \,\, b]}{a} $ is always equal to $ 1 $ .

In the second example $ [a, \,\, 2] $ can be equal to $ a $ or $ 2 \cdot a $ depending on parity of $ a $ . $ \frac{[a, \,\, b]}{a} $ can be equal to $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
1```

## 样例 #2

### 输入

```
2
```

### 输出

```
2```

# AI分析结果



# LCM

## 题目描述

Ivan有一个数字$b$。他在遍历从$1$到$10^{18}$的所有数字$a$时，对每个$a$在黑板上写下$\frac{[a, \,\, b]}{a}$的值。这里的$[a, \,\, b]$表示$a$和$b$的最小公倍数。Ivan想知道他最终会在黑板上写下多少个不同的数字。请帮助他计算这个数量。

## 说明/提示

第一个样例中，$[a, \,\, 1] = a$，因此$\frac{[a, \,\, b]}{a}$总是等于$1$。

第二个样例中，$[a, \,\, 2]$可能等于$a$或$2 \cdot a$，这取决于$a$的奇偶性。$\frac{[a, \,\, b]}{a}$的取值可能为$1$和$2$。

## 样例 #1

### 输入
```
1
```

### 输出
```
1
```

## 样例 #2

### 输入
```
2
```

### 输出
```
2
```

---

**算法分类**: 数学（因数分解）

---

### 题解综合分析

所有题解均通过数学推导将问题转化为求$b$的因数个数，关键思路是利用公式$\frac{[a,b]}{a} = \frac{b}{\gcd(a,b)}$，进而证明不同的$\gcd(a,b)$取值等于$b$的因数数量。实现方式主要有两种：质因数分解后计算因数个数，或直接枚举因数。

---

### 优质题解推荐

#### 1. Dilute（5星）
**核心思路**：  
通过质因数分解计算因数个数，时间复杂度$O(\sqrt{n})$。  
**关键代码**：
```cpp
ll Ans = 1;
for(ll i = 2; i <= qn; i++){
    ll Cnt = 1;
    while(n % i == 0){
        n /= i;
        Cnt++;
    }
    Ans *= Cnt;
}
if(n > 1) Ans *= 2;
```

#### 2. lin000（4星）
**核心思路**：  
直接枚举因数对，处理平方数特殊情况。  
**关键代码**：
```cpp
for(long long i = 1 ; i <= sqrt(n); i++){
    if(n % i == 0) ans += 2;
    if(i * i == n) ans --;
}
```

#### 3. XL4453（4星）
**核心思路**：  
通过算术基本定理证明结论，代码简洁高效。  
**关键代码**：
```cpp
for(long long i=1;i*i<=n;i++){
    if(i*i==n) ans++;
    if(n%i==0) ans+=2;
}
```

---

### 关键技巧总结
1. **数学推导**：利用LCM公式转化为$\frac{b}{\gcd(a,b)}$，发现与因数的关系。  
2. **质因数分解**：通过分解质因数计算因数个数，复杂度更优。  
3. **边界处理**：遍历至$\sqrt{n}$时需处理平方数重复计数问题。  

---

### 相似题目推荐
1. [P1463 反素数](https://www.luogu.com.cn/problem/P1463)  
2. [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)  
3. [P2926 最大公约数](https://www.luogu.com.cn/problem/P2926)  

---

### 个人心得摘录
**两年打铁**提到未初始化变量导致WA的教训，强调变量初始化的必要性。  
**Arghariza**指出分解质因数后若剩余因子大于1需额外乘2的细节处理。  
**Z_M**强调当$a>b$时需特殊处理，但最终发现所有情况均可统一为因数计算。

---
处理用时：42.30秒