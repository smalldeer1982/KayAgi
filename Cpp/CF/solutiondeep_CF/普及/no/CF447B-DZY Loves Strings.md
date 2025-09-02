# 题目信息

# DZY Loves Strings

## 题目描述

DZY loves collecting special strings which only contain lowercase letters. For each lowercase letter $ c $ DZY knows its value $ w_{c} $ . For each special string $ s=s_{1}s_{2}...\ s_{|s|} $ ( $ |s| $ is the length of the string) he represents its value with a function $ f(s) $ , where

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF447B/47a1fab5618b8aab7370048ef8382ed56e397765.png)Now DZY has a string $ s $ . He wants to insert $ k $ lowercase letters into this string in order to get the largest possible value of the resulting string. Can you help him calculate the largest possible value he could get?

## 说明/提示

In the test sample DZY can obtain "abcbbc", $ value=1·1+2·2+3·2+4·2+5·2+6·2=41 $ .

## 样例 #1

### 输入

```
abc
3
1 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

### 输出

```
41
```

# AI分析结果



### 中文重写题目
**DZY 爱字符串**

#### 题目描述  
DZY 喜欢收集仅包含小写字母的特殊字符串。每个小写字母 $c$ 都有一个权值 $w_c$。对于特殊字符串 $s=s_1s_2...s_{|s|}$，其价值由函数 $f(s)$ 表示：  
$$f(s) = \sum_{i=1}^{|s|} i \times w_{s_i}$$  
DZY 有一个字符串 $s$，他可以在其中插入 $k$ 个小写字母，使得新字符串的价值最大。求这个最大可能的价值。

#### 输入输出样例  
**输入**  
```
abc
3
1 2 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```  
**输出**  
```
41
```

---

### 算法分类  
**贪心**

---

### 题解分析与结论  
**核心逻辑**：插入 $k$ 个权值最大的字符到原字符串末尾，利用等差数列求和公式快速计算插入部分的总价值。  

**关键思路对比**：  
1. **插入位置**：所有题解均指出，插入到末尾能使新增字符的权重因子 $i$ 最大化。  
2. **公式优化**：多数题解使用等差数列公式 $\frac{(a_1+a_n) \cdot n}{2}$ 直接计算插入部分的总和，避免逐项累加的低效操作。  
3. **实现差异**：部分题解直接在原字符串后追加字符再计算总值（$O(n+k)$），而更优解法通过数学公式计算（$O(1)$）。  

**最优策略**：  
- 先计算原字符串的价值。  
- 找到权值最大的字符，计算其插入 $k$ 次后的总价值（利用等差数列公式）。  

---

### 高分题解精选（≥4星）  

#### 题解1：Alex_Wei（⭐⭐⭐⭐⭐）  
**亮点**：  
- 直接数学公式计算，时间复杂度最优（$O(n)$ 预处理 + $O(1)$ 插入计算）。  
- 代码简洁，仅需 12 行。  

**核心代码**：  
```cpp
int main() {
    cin >> s >> k;
    for (int x = 0; x < 26; x++) cin >> w[x], m = max(m, w[x]);
    for (int x = 0; x < s.size(); x++) n += w[s[x]-'a'] * (x+1);
    cout << n + m * (2*s.size() + k + 1) * k / 2;
}
```

#### 题解2：Morax2022（⭐⭐⭐⭐）  
**亮点**：  
- 明确公式推导过程，强调等差数列的应用。  
- 变量命名清晰，适合教学。  

**代码片段**：  
```cpp
cout << ans + mx * (s.size() + 1 + s.size() + k) * k / 2;
```

#### 题解3：Luo_gu_ykc（⭐⭐⭐⭐）  
**亮点**：  
- 使用 `map` 存储字符权值，代码可读性高。  
- 包含详细注释，适合新手理解。  

**关键实现**：  
```cpp
for(int i = s.size() + 1; i <= s.size() + k; i++)
    ans += maxi * i;
```

---

### 关键技巧总结  
1. **贪心选择**：插入权值最大的字符。  
2. **数学优化**：用等差数列公式替代循环计算，将时间复杂度从 $O(k)$ 优化到 $O(1)$。  
3. **边界处理**：注意原字符串长度为 $l$ 时，插入的第一个字符的位置是 $l+1$。  

---

### 类似题目推荐  
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)（贪心排序）  
2. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)（贪心选择区间）  
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)（贪心+优先队列）  

---

### 题解个人心得摘录  
- **初始化技巧**：`maxn` 应初始化为负数，避免权值全为 0 时出错。（Wy_x 题解）  
- **调试教训**：插入字符的位置计算需与原字符串长度关联，避免索引错误。（JacoAquamarine 题解）  
- **公式推导**：通过样例验证等差数列的正确性，避免手算错误。（Alex_Wei 题解）

---
处理用时：55.44秒