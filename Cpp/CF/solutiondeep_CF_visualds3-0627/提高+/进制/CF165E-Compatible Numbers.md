# 题目信息

# Compatible Numbers

## 题目描述

Two integers $ x $ and $ y $ are compatible, if the result of their bitwise "AND" equals zero, that is, $ a $ $ & $ $ b=0 $ . For example, numbers $ 90 $ $ (1011010_{2}) $ and $ 36 $ $ (100100_{2}) $ are compatible, as $ 1011010_{2} $ $ & $ $ 100100_{2}=0_{2} $ , and numbers $ 3 $ $ (11_{2}) $ and $ 6 $ $ (110_{2}) $ are not compatible, as $ 11_{2} $ $ & $ $ 110_{2}=10_{2} $ .

You are given an array of integers $ a_{1},a_{2},...,a_{n} $ . Your task is to find the following for each array element: is this element compatible with some other element from the given array? If the answer to this question is positive, then you also should find any suitable element.

## 样例 #1

### 输入

```
2
90 36
```

### 输出

```
36 90```

## 样例 #2

### 输入

```
4
3 6 3 6
```

### 输出

```
-1 -1 -1 -1```

## 样例 #3

### 输入

```
5
10 6 9 8 2
```

### 输出

```
-1 8 2 2 8```

# AI分析结果



**唯一算法分类**  
高维前缀和/状压DP

---

**综合分析与结论**  
本题核心在于快速判断每个数补集的子集中是否存在数组元素。各题解核心思路一致：预处理补集子集信息，利用位运算特性优化查询。  
**关键算法流程**：  
1. **预处理补集**：对每个a_i，计算其补集mask = (1<<22)-1 ^ a_i。  
2. **高维前缀和预处理**：从低位到高位，将每个数的解传播到包含它的更大数（即逐步添加1的位）。  
3. **查询阶段**：直接查询补集mask对应的预处理结果。  

**可视化设计**：  
- **动画方案**：以网格展示0~(1<<22)-1的所有数，用颜色区分已标记/未标记状态。  
- **步进操作**：逐位处理时高亮当前位，展示被更新的数如何继承子集解。  
- **像素风格**：每个数用8x8像素块表示，标记时播放8-bit音效，成功匹配时触发胜利音效。  

---

**题解清单 (≥4星)**  
1. **__Watcher (5星)**：代码简洁高效，高维前缀和模板直接应用，时间复杂度O(M log M)。  
2. **Mooncrying (4星)**：详解高维前缀和原理，适合新手理解，代码结构清晰。  
3. **ZillionX (4星)**：FWT实现思路新颖，提供不同视角的位运算解法。  

---

**核心代码实现**  
```cpp
// 高维前缀和核心片段
const int MAXN = (1<<22)-1;
int f[MAXN+1];

// 预处理阶段
for(int i=1;i<=n;i++) f[a[i]] = a[i];
for(int bit=0;bit<22;bit++)
    for(int j=0;j<=MAXN;j++)
        if(j & (1<<bit) && f[j^(1<<bit)])
            f[j] = f[j^(1<<bit)];

// 查询阶段
int mask = MAXN ^ a[i];
int ans = f[mask] ? f[mask] : -1;
```

---

**同类型题推荐**  
1. [CF449D - Jzzhu and Apples](https://codeforces.com/problemset/problem/449/D)  
2. [LOJ#152 子集卷积](https://loj.ac/p/152)  
3. [P5495 子集和问题](https://www.luogu.com.cn/problem/P5495)

---

**个人心得摘录**  
> "注意位运算优先级！不确定时加括号保平安" —— Prurite  
> "补集计算时要用异或掩码防止符号位干扰" —— 白鲟  
> "从大往小枚举保证状态正确传递" —— zyc____  

---

**复古可视化方案**  
```javascript
// 伪代码展示Canvas绘制逻辑
const canvas = document.getElementById("bit-grid");
const ctx = canvas.getContext("2d");

function drawNumberGrid() {
    for(let i=0; i<MAXN; i++) {
        const x = (i % 128) * 8; // 128列网格
        const y = Math.floor(i/128) * 8;
        ctx.fillStyle = f[i] ? "#00FF00" : "#333333"; 
        ctx.fillRect(x, y, 6, 6); // 绘制像素块
    }
}

// 音效触发
function playUpdateSound() {
    const synth = new Tone.Synth().toDestination();
    synth.triggerAttackRelease("C4", "8n"); // 8分音符C调
}
```

**交互设计**：  
- 按空格键单步执行位处理  
- 方向键控制动画速度  
- 成功匹配时像素块闪烁金色，播放《超级马里奥》金币音效  
- 失败时显示红色闪烁，播放《魂斗罗》中弹音效  

---

**关键优化点**  
预处理时采用高位优先的更新顺序，确保每个数继承最具体子集的解。查询时直接O(1)访问，整体复杂度完美适配4e6量级数据。

---
处理用时：65.89秒