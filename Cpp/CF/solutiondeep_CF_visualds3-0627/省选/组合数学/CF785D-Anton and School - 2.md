# 题目信息

# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()
```

### 输出

```
6
```

## 样例 #2

### 输入

```
()()()
```

### 输出

```
7
```

## 样例 #3

### 输入

```
)))
```

### 输出

```
0
```

# AI分析结果



## 算法分类
组合数学、范德蒙德卷积

---

## 综合分析与结论

### 核心算法流程
1. **前缀/后缀预处理**：  
   - 预处理每个位置左侧的`(`数量（含当前位）和右侧的`)`数量
2. **组合数优化**：  
   - 对每个`(`位置i，贡献为组合数C(l[i]+r[i]-1, l[i])
   - 应用范德蒙德卷积公式将原始O(n²)求和转化为O(1)计算
3. **阶乘逆元优化**：  
   - 预处理阶乘数组和逆元数组实现O(1)组合数查询

### 可视化设计要点
1. **像素风格展示**：  
   - 使用16色调色板，`(`用绿色方块表示，`)`用红色方块表示
   - 当前遍历的`(`位置用黄色边框高亮，对应贡献值以浮动数字显示
2. **动态数据标注**：  
   - 在Canvas顶部显示当前处理的`(`位置的前缀数(l[i])和后缀数(r[i])
   - 用蓝色进度条展示组合数C(l[i]+r[i]-1, l[i])的计算过程
3. **音效交互**：  
   - 遍历每个`(`时播放"滴"声，成功计算贡献时播放上升音阶
   - 最终答案显示时播放8-bit胜利音乐

---

## 题解评分（≥4星）

### 1. 作者：_Life_（⭐️⭐️⭐️⭐️⭐️）
- **亮点**：  
  - 精确推导范德蒙德卷积转换过程  
  - 代码采用线性逆元预处理，效率最优
- **核心代码片段**：
```cpp
for(int i=1;i<=n;i++)
    if(str[i]=='(')
        ans=(ans+C(x[i]+y[i]-1,x[i]))%mod;
```

### 2. 作者：YuntianZhao（⭐️⭐️⭐️⭐️）
- **亮点**：  
  - 详细说明组合数模运算原理  
  - 变量命名清晰易懂
- **关键推导**：
``` 
∑C(a-1,i-1)*C(b,i) = C(a+b-1, a)
```

### 3. 作者：wcyQwQ（⭐️⭐️⭐️⭐️）
- **亮点**：  
  - 给出完整数学证明过程  
  - 代码模块化程度高

---

## 最优思路提炼

### 关键技巧
1. **强制选取最后一个`(`**：  
   通过枚举最后一个左括号的位置，避免重复计数
2. **范德蒙德卷积应用**：  
   将原始双重求和转化为单组合数计算
3. **线性逆元预处理**：  
   通过递推计算阶乘逆元，实现O(1)组合数查询

### 思维突破点
- 发现贡献式与范德蒙德卷积的形态匹配
- 通过组合意义（选择物品的两种方式）理解公式转换

---

## 相似题目推荐
1. [CF1342E - Placing Rooks](https://www.luogu.com.cn/problem/CF1342E)  
   （组合数学+容斥原理）
2. [ABC202E - Count Descendants](https://www.luogu.com.cn/problem/ABC202E)  
   （DFS序+组合计数）
3. [P6672 - 你的生命已如风中残烛](https://www.luogu.com.cn/problem/P6672)  
   （卡特兰数变形）

---

## 核心代码实现

```cpp
const int maxn = 2e5+5, mod = 1e9+7;
int fac[maxn], inv[maxn], l[maxn], r[maxn];

void init() {
    fac[0] = 1;
    for(int i=1;i<maxn;i++) fac[i] = fac[i-1] * i % mod;
    inv[maxn-1] = power(fac[maxn-1], mod-2);
    for(int i=maxn-2;i>=0;i--) 
        inv[i] = inv[i+1] * (i+1) % mod;
}

int C(int n, int m) {
    return n < m ? 0 : fac[n] * inv[m] % mod * inv[n-m] % mod;
}

int main() {
    init();
    string s; cin >> s;
    for(int i=0; i<s.size(); i++)
        l[i+1] = l[i] + (s[i] == '(');
    for(int i=s.size()-1; i>=0; i--)
        r[i+1] = r[i+2] + (s[i] == ')');
    
    int ans = 0;
    for(int i=1; i<=s.size(); i++)
        if(s[i-1] == '(')
            ans = (ans + C(l[i]+r[i]-1, l[i])) % mod;
    cout << ans;
}
```

---

## 可视化方案设计

### 动画演示逻辑
1. **初始化阶段**：  
   ![像素风格括号序列]  
   用绿/红方块构建原始括号序列，底部显示前缀/后缀计数器

2. **遍历过程**：  
   ▶️ 黄色光标从左向右扫描，遇到`(`时触发以下动作：  
   - 弹出当前`(`的l[i]和r[i]数值  
   - 显示C(l[i]+r[i]-1, l[i])的组合数计算式  
   - 播放"blip"音效

3. **贡献累计**：  
   🔢 右侧面板实时显示当前总和，每次更新时数字跳动+音效

### 交互功能
- **速度调节**：滑块控制扫描速度（1x-10x）
- **单步模式**：空格键逐帧执行
- **历史回看**：左/右键回溯贡献计算过程

---

通过这种设计，学习者可直观理解每个`(`位置的贡献计算过程，以及范德蒙德卷积的优化效果。复古像素风格与游戏化交互能显著提升算法学习的趣味性。

---
处理用时：63.67秒