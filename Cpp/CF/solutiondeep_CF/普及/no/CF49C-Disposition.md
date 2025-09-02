# 题目信息

# Disposition

## 题目描述

Vasya bought the collected works of a well-known Berland poet Petya in $ n $ volumes. The volumes are numbered from $ 1 $ to $ n $ . He thinks that it does not do to arrange the book simply according to their order. Vasya wants to minimize the number of the disposition’s divisors — the positive integers $ i $ such that for at least one $ j $ ( $ 1<=j<=n $ ) is true both: $ j $ $ mod $ $ i=0 $ and at the same time $ p(j) $ $ mod $ $ i=0 $ , where $ p(j) $ is the number of the tome that stands on the $ j $ -th place and $ mod $ is the operation of taking the division remainder. Naturally, one volume can occupy exactly one place and in one place can stand exactly one volume.

Help Vasya — find the volume disposition with the minimum number of divisors.

## 样例 #1

### 输入

```
2
```

### 输出

```
2 1 
```

## 样例 #2

### 输入

```
3
```

### 输出

```
1 3 2 
```

# AI分析结果



### 中文题目重写
**题目名称：排列**

**题目描述**  
Vasya购买了著名Berland诗人Petya的n卷诗集，编号1到n。他认为简单的顺序排列不够有趣，想要构造一种排列方式，使得满足以下条件的正整数i的数量最少：存在至少一个位置j（1≤j≤n），使得j mod i=0且p(j) mod i=0，其中p(j)表示第j个位置的卷号。

**输入样例 #1**  
```
2
```

**输出样例 #1**  
```
2 1 
```

**输入样例 #2**  
```
3
```

**输出样例 #2**  
```
1 3 2 
```

---

### 算法分类  
**构造**

---

### 题解分析与结论  
**核心思路**：构造排列使得所有i≥2的除数条件均不成立，仅保留i=1作为唯一除数。通过将2~n顺序排列后接1，确保对任意i≥2，当j是i的倍数时，对应位置的数p(j)=j+1 ≡1 mod i，从而不满足条件。

**最优解法**：将2~n顺序放置，最后一个位置放1。此排列下，所有i≥2均无法找到满足条件的j，最终仅i=1满足条件，达到最优。

**关键证明**：  
- 对于任意i≥2，假设存在j=k*i（k≥1），此时p(j)=k*i+1  
- 有j mod i=0，但p(j) mod i=1 ≠0  
- 因此所有i≥2均不满足条件，仅i=1必然满足

---

### 高星题解推荐  
1. **Buried_Dream（4星）**  
   **亮点**：代码简洁高效，直接输出2~n后接1  
   **代码核心**：  
   ```cpp
   for(int i=2; i<=n; i++) cout << i << " ";
   cout << "1";
   ```

2. **Terraria（4星）**  
   **亮点**：明确构造思路，代码直观  
   **代码核心**：  
   ```cpp
   for(int i=2; i<=n; i++) cout<<i<<" ";
   cout<<1;
   ```

3. **Morax2022（4星）**  
   **亮点**：数学解释清晰，强调1的特殊性  
   **代码核心**：  
   ```cpp
   for (int i=2; i<=n; i++) cout << i << " ";
   cout << 1;
   ```

---

### 关键实现代码  
```cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    for(int i=2; i<=n; ++i) cout << i << " ";
    cout << "1";
    return 0;
}
```
**实现思想**：顺序输出2至n后追加1，确保每个位置i的值为i+1（末位特殊处理），使得所有i≥2不满足除数条件。

---

### 拓展与相似题目  
1. **CF1433E**（排列构造，数学性质）  
2. **CF1352G**（特殊排列构造）  
3. **AT_abc326_e**（数学构造与模运算）  

**解题套路**：当问题要求构造满足特定数学条件的排列时，优先考虑：  
- 特殊元素（如0/1）的边界处理  
- 相邻元素差值或模数关系  
- 循环位移或逆序排列等简单变换  

---

### 题解心得摘录  
- **xiaozeyu**："这道题AC的人少是因为题意理解困难，构造核心是打破i≥2的模条件"  
- **Fearliciz**的反例教训：错误地将原排列输出，导致所有i都满足条件，说明验证构造正确性的重要性

---
处理用时：160.14秒