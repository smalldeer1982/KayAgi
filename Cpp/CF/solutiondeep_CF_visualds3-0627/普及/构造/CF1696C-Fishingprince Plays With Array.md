# 题目信息

# Fishingprince Plays With Array

## 题目描述

Fishingprince is playing with an array $ [a_1,a_2,\dots,a_n] $ . He also has a magic number $ m $ .

He can do the following two operations on it:

- Select $ 1\le i\le n $ such that $ a_i $ is divisible by $ m $ (that is, there exists an integer $ t $ such that $ m \cdot t = a_i $ ). Replace $ a_i $ with  $ m $ copies of $ \frac{a_i}{m} $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[2,3] $ and $ i=1 $ , $ a $ changes into $ [1,1,3] $ .
- Select $ 1\le i\le n-m+1 $ such that $ a_i=a_{i+1}=\dots=a_{i+m-1} $ . Replace these $ m $ elements with a single $ m \cdot a_i $ . The order of the other elements doesn't change. For example, when $ m=2 $ and $ a=[3,2,2,3] $ and $ i=2 $ , $ a $ changes into $ [3,4,3] $ .

Note that the array length might change during the process. The value of $ n $ above is defined as the current length of the array (might differ from the $ n $ in the input).

Fishingprince has another array $ [b_1,b_2,\dots,b_k] $ . Please determine if he can turn $ a $ into $ b $ using any number (possibly zero) of operations.

## 说明/提示

In the first test case of the sample, we can do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},4,2]\to [1,\color{red}{4},4,2] $ .

In the second testcase of the sample, we can:

- do the second operation with $ i=2 $ : $ [1,\color{red}{2,2},8,2,2]\to [1,\color{red}{4},8,2,2] $ .
- do the second operation with $ i=4 $ : $ [1,4,8,\color{red}{2,2}]\to [1,4,8,\color{red}{4}] $ .
- do the first operation with $ i=3 $ : $ [1,4,\color{red}{8},4]\to [1,4,\color{red}{4,4},4] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{4,4},4,4]\to [1,\color{red}{8},4,4] $ .
- do the second operation with $ i=3 $ : $ [1,8,\color{red}{4,4}]\to [1,8,\color{red}{8}] $ .
- do the second operation with $ i=2 $ : $ [1,\color{red}{8,8}]\to [1,\color{red}{16}] $ .

## 样例 #1

### 输入

```
5
5 2
1 2 2 4 2
4
1 4 4 2
6 2
1 2 2 8 2 2
2
1 16
8 3
3 3 3 3 3 3 3 3
4
6 6 6 6
8 3
3 9 6 3 12 12 36 12
16
9 3 2 2 2 3 4 12 4 12 4 12 4 12 4 4
8 3
3 9 6 3 12 12 36 12
7
12 2 4 3 4 12 56```

### 输出

```
Yes
Yes
No
Yes
No```

# AI分析结果



**唯一算法分类**  
构造

---

### 综合分析与结论  
**题目核心思路**  
通过两种互逆操作（拆分与合并），判断数组能否相互转换。核心在于将两数组分解为无法再拆分的基本形式（数值不可被 m 整除），并比较其顺序、数值和出现次数是否一致。  

**解决难点**  
1. **高效表示分解后的元素**：通过结构体记录数值及其出现次数（m 的幂次），避免直接展开元素导致的指数级爆炸。  
2. **顺序敏感匹配**：分解后的结构体顺序必须与原数组操作后的顺序一致，确保合并操作的合法性。  

**可视化设计思路**  
- **动画方案**：  
  1. **双端队列操作**：用队列动态展示数组 a 的结构体被逐个匹配的过程。  
  2. **颜色标记**：高亮当前处理的元素（如红色表示正在匹配的结构体），灰色表示已处理或未处理的部分。  
  3. **步进控制**：允许单步执行，观察每一步如何消耗结构体次数。  

**复古游戏化设计**  
- **像素风格**：用 8-bit 风格绘制队列和结构体，数值显示为像素块，次数用数字叠加。  
- **音效触发**：每次结构体匹配成功时播放清脆音效，失败时播放低沉音效。  
- **自动演示模式**：算法自动运行，动态展示队列匹配过程。  

---

### 题解清单 (≥4星)  
1. **作者：lenlen（⭐️⭐️⭐️⭐️⭐️）**  
   - **关键亮点**：使用双端队列动态匹配结构体，确保顺序严格一致，代码高效且逻辑清晰。  
   - **实现技巧**：逐个消耗结构体次数，避免合并相邻元素，保证正确性。  
   ```cpp  
   deque <hl> q;  
   for (处理数组a的每个元素) {  
      分解为结构体并存入队列;  
   }  
   for (处理数组b的每个元素) {  
      分解为结构体并逐个匹配队列头部;  
   }  
   ```

---

### 最优思路或技巧提炼  
1. **结构体分解法**：将元素分解为不可拆分的数值和出现次数，避免数据爆炸。  
2. **顺序严格匹配**：通过队列维护顺序，确保合并操作只能在原顺序基础上进行。  
3. **动态消耗次数**：逐个处理数组 b 的结构体，灵活处理跨结构体的次数匹配。  

---

### 同类型题或类似算法套路  
- **操作互逆性问题**：如括号匹配、字符串变换（如 Codeforces 1110D）。  
- **结构体压缩表示**：如区间合并（LeetCode 56）、游程编码。  

---

### 推荐相似题目  
1. **CF1695C**：通过操作转换数组，需构造最小操作次数。  
2. **LeetCode 726**：化学式解析，需处理括号和数字后缀的结构体表示。  
3. **Luogu P1496**：区间覆盖问题，需合并相邻区间。  

---

### 个人心得摘录  
> "分解后的结构体顺序必须与原始数组操作后的顺序一致，否则无法通过合并操作转换。" —— lenlen  
> "合并相邻结构体会导致顺序错乱，必须避免。" —— jiangtaizhe001 调试总结  

---

### 代码核心片段  
```cpp  
// lenlen 的核心匹配逻辑  
for (int i = 1; i <= nn && !flag; i++) {  
    int k = 1;  
    while (b[i] % m == 0) b[i] /= m, k *= m;  
    while (k) {  
        if (q.empty()) { flag = 1; break; }  
        tmp = q.front(); q.pop_front();  
        if (tmp.d != b[i]) { flag = 1; break; }  
        if (tmp.sum <= k) k -= tmp.sum;  
        else {  
            q.push_front({tmp.d, tmp.sum - k});  
            k = 0;  
        }  
    }  
}  
```  

---

### 可视化实现要点  
1. **Canvas 绘制**：队列用横向像素块表示，数值为颜色块，次数为数字标签。  
2. **自动演示**：用 `setInterval` 控制匹配速度，高亮当前操作的 b 元素和队列头部。  
3. **音效设计**：使用 Web Audio API 播放 8-bit 音效，匹配成功时播放高音，失败时低音。

---
处理用时：346.68秒