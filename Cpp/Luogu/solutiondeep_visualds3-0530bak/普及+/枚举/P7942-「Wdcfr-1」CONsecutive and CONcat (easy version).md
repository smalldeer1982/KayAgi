# 题目信息

# 「Wdcfr-1」CONsecutive and CONcat (easy version)

## 题目描述

**In easy version, It is guaranteed that any string in array $\mathbf a$ contains at least two different letters.**

Lily White is playing with strings. Being a yousei, she is not capable of complex speech. Thus, she likes strings that only contain one kind of letter, she calls such strings of length $x$ a "$x$-CON string". For example, `qqqq` is a "$4$-CON string", while `aaab` is not any type of "CON string".

Lily White composed an array $a$. It contains $n$ strings of length $m$ that she will use to herald spring. For each permutation of $1,2,\ldots, n$, let us denote current permutation as $p=\{p_1,p_2,\cdots,p_n\}$. Lily White concatenates all the string in array $a$ in the order of $a_{p_1},a_{p_2},\cdots,a_{p_n}$ into a string $s$ of length $nm$ . 

As she likes $k$-CON strings, she wants to know the sum of the number of "$k$-CON string" in all non-empty substrings of $s$ composed by all $n!$ permutations. Since the answer may be enormous, just print the answer taken modulo $998,244,353$ (a large prime).


## 说明/提示

### Explanation

#### Sample \#1

- For permutation $1,2,3$, the formed $s$ is `aabbaabaa`, none on the non-empty substring in this string are "$4$-CON string".
- For permutation $1,3,2$, the formed $s$ is `aabbaabaa`, none on the non-empty substring in this string are "$4$-CON string".
- For permutation $2,1,3$, the formed $s$ is `baaaabbaa`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $2,3,1$, the formed $s$ is `baabaaaab`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $3,1,2$, the formed $s$ is `baaaabbaa`, this string has one substring `aaaa` which is a "$4$-CON string".
- For permutation $3,2,1$, the formed $s$ is `baabaaaab`, this string has one substring `aaaa` which is a "$4$-CON string".

In summary, the answer is $0+0+1+1+1+1=4$.

#### Sample \#2

In all of the full permutation of length $3$, there will be six different $s$: `xyzqaqaba`, `xyzabaqaq`, `qaqxyzaba`, `qaqabaxyz`, `abaqaqxyz`, and `abaxyzqaq`. None of these has a non-empty substrings which is a "$2$-CON string". So the answer is $0$.

### Constraints

$2\le k \le n\cdot m\le 10^6;\ 1\le m \le 100$. $a_i$ contains only lowercase English letters.

**In easy version, we ensure that any string in array $\mathbf a$ contains at least two different letters.**

## 样例 #1

### 输入

```
3 3 4
aab
baa
baa```

### 输出

```
4```

## 样例 #2

### 输入

```
3 3 2
xyz
qaq
aba
```

### 输出

```
0```

# AI分析结果



**唯一算法分类**  
组合数学与贡献分析法

---

**综合分析与结论**  
题目核心在于高效计算所有排列下拼接字符串中 k-CON 子串的总贡献。通过拆分贡献为**单字符串内部贡献**和**跨字符串拼接贡献**两部分，结合组合数学统计各情况出现次数。  
**核心难点**在于跨字符串贡献的精确计算，需避免重复计数并处理同一字符串自拼接的特殊情况。FFTotoro 题解通过预处理前后缀极长连续段长度，并引入修正项 `e[j][i][c]` 剔除自拼接干扰，是正确解法。

**可视化设计思路**  
1. **动画流程**：  
   - **分屏显示**：左半展示字符串内部连续段统计（红色高亮 k-CON 段），右半演示不同排列中前后缀拼接过程（蓝绿标记前后缀）。  
   - **步进操作**：每步展示一个排列的拼接结果，动态绘制可能的跨段 k-CON 子串（黄色覆盖）。  
   - **统计面板**：实时更新单段贡献（红色计数）与跨段贡献（蓝色计数），突出公式 `min-max` 计算过程。  
2. **复古像素风格**：  
   - **8位字符块**：用不同颜色像素块表示字符（如 'a'=浅蓝，'b'=粉色），拼接时像素块横向滚动合并。  
   - **音效触发**：单段贡献时播放短促“哔”声，跨段成功时播放上升音阶，错误重叠时低频提示音。  

---

**题解清单 (≥4星)**  
1. **FFTotoro（5星）**  
   - **关键亮点**：正确拆分贡献，引入修正项避免重复；预处理极长前后缀，O(m²) 枚举高效计算。  
   - **个人心得**：指出官方题解公式错误，强调边界条件处理（如 `f(i,j,k)` 函数设计）。  

---

**核心代码逻辑**  
```cpp
// 预处理前后缀极长连续段
for (auto &i : a) {
    int l = 0, t = 0;
    // 计算极长前缀长度 l 和极长后缀长度 t
    for (int j = 0; j < m; j++) {
        if (j == 0 || i[j] == i[j - 1]) t++;
        else { /* 处理内部贡献 */ }
    }
    // 更新 b, s, e 数组统计出现次数
    b[l][c]++; s[t][c]++;
    if (i[0] == i.back()) e[l][t][c]++;
}

// 跨字符串贡献计算
for (int c = 0; c < 26; c++)
    for (int i = 1; i < m; i++)
        for (int j = max(k - i, 1); j < m; j++)
            res += (b[j][c] * s[i][c] - e[j][i][c]) * f(i, j, k) * F2;
```

---

**同类型题与套路**  
1. **贡献拆分**：如 [CF1391D] 需统计二进制矩阵中边贡献。  
2. **排列组合统计**：如 [洛谷P3773] 中全排列逆序对期望。  
3. **前后缀极值预处理**：如 [LeetCode 152] 乘积最大子数组。  

**推荐题目**  
1. [CF1189B] 环形数组构造（前后缀极值）  
2. [洛谷P2679] 子串统计（跨段DP）  
3. [LeetCode 828] 唯一字符子串贡献  

---

**复古游戏化演示代码片段**  
```javascript
// 伪代码：Canvas 绘制拼接过程
function drawConcat(s1, s2, overlapLen) {
    ctx.fillStyle = '#8B00FF'; // 紫色背景
    ctx.fillRect(0, 0, CANVAS_W, CANVAS_H);
    // 绘制 s1 后缀与 s2 前缀的像素块
    drawString(s1, 50, 100, {suffix: true});
    drawString(s2, 50 + s1.length * 8, 100, {prefix: true});
    // 高亮重叠部分
    if (overlapLen >= k) {
        ctx.fillStyle = 'rgba(255,255,0,0.3)';
        ctx.fillRect(50 + (s1.length - s) * 8, 100, (s + p) * 8, 16);
    }
}
```

---
处理用时：77.26秒