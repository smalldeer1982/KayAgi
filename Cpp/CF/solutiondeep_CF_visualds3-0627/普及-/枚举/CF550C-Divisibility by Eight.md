# 题目信息

# Divisibility by Eight

## 题目描述

You are given a non-negative integer $ n $ , its decimal representation consists of at most $ 100 $ digits and doesn't contain leading zeroes.

Your task is to determine if it is possible in this case to remove some of the digits (possibly not remove any digit at all) so that the result contains at least one digit, forms a non-negative integer, doesn't have leading zeroes and is divisible by 8. After the removing, it is forbidden to rearrange the digits.

If a solution exists, you should print it.

## 样例 #1

### 输入

```
3454
```

### 输出

```
YES
344
```

## 样例 #2

### 输入

```
10
```

### 输出

```
YES
0
```

## 样例 #3

### 输入

```
111111
```

### 输出

```
NO
```

# AI分析结果



---

## 唯一算法分类  
**数学性质 + 暴力枚举**

---

## 综合分析与结论  

### 核心思路与难点  
**核心数学结论**：一个数能被 8 整除当且仅当其最后三位数能被 8 整除（对于长度 ≥3 的数）。  
**关键优化点**：优先处理特殊一位数（0 或 8）和两位数，再暴力枚举三位数组合。  

**解决难点**：  
1. **前导零问题**：需保证输出的数不以 `0` 开头（样例 #2 允许输出 `0`，但其他情况如 `012` 非法）。  
2. **暴力效率**：最坏情况需检查所有三位数组合，但题目限制数字长度 ≤100，时间复杂度为 O(100³) ≈ 1e6，可接受。  
3. **顺序限制**：数字顺序不可重排，需按原序依次检查每一位组合。  

### 算法流程  
1. **特判 0**：原数字含 `0` 直接输出 `0`。  
2. **枚举一位数**：检查是否存在 `8`。  
3. **枚举两位数**：检查所有连续两位组合是否能被 8 整除。  
4. **枚举三位数**：检查所有连续三位组合是否能被 8 整除。  

### 可视化设计思路  
**动画方案**：  
1. **像素高亮扫描**：用像素块表示数字序列，从左到右依次高亮当前检查的位数（红框表示一位、蓝框两位、绿框三位）。  
2. **动态数值计算**：右侧面板实时显示当前组合的值和模 8 结果。  
3. **解标记**：发现合法组合时，对应数字块闪烁黄光并播放「成功音效」。  

**复古游戏化设计**：  
- **8-bit 音效**：检查时播放短促「哔」声，成功时播放 FC 游戏通关音效。  
- **Canvas 像素网格**：数字以 16×16 像素块展示，扫描框用 8-bit 风格边框动画。  
- **自动演示模式**：AI 自动按序尝试所有组合，用户可暂停观察当前状态。  

---

## 题解清单（≥4星）  

### 灵光一闪（4.5★）  
**关键亮点**：  
1. **代码简洁性**：直接嵌套三重循环覆盖所有位数情况。  
2. **数学结论运用**：通过模 8 计算快速判断组合合法性。  
3. **注释指导性**：明确说明「末尾三位数」的数学依据。  

**核心代码**：  
```cpp
for(int i=0;i<s.size();i++){
    for(int j=i+1;j<s.size();j++){
        for(int k=j+1;k<s.size();k++){
            if((s[i]*100 + s[j]*10 + s[k])%8 ==0){
                cout<<s[i]<<s[j]<<s[k]; return;
            }
        }
        if((s[i]*10 + s[j])%8 ==0){...}
    }
    if(s[i]%8 ==0){...}
}
```

### FuriousC（4.0★）  
**关键亮点**：  
1. **变量命名清晰**：`a,b,c` 分别代表三位数各位。  
2. **逻辑分层明确**：依次处理一位、两位、三位情况。  
3. **代码可读性**：使用 `str.find('0')` 快速判断特例。  

**核心代码**：  
```cpp
a = str.find('0');
if(a < str.size()){
    cout<<"YES\n0"; return;
}
```

---

## 最优技巧提炼  

### 数学性质降维  
利用「末尾三位决定整除性」的数学结论，将问题从指数级枚举降为 O(n³)。  

### 贪心式优先检查  
按位数从小到大（1→2→3）检查，找到解立即返回，减少无效计算。  

### 特判加速  
优先处理 `0` 的存在性，避免进入复杂循环。  

---

## 类似题目推荐  
1. **P1217 [USACO1.5] 回文质数**：利用数学性质缩小搜索范围。  
2. **P1731 [NOI1999] 生日蛋糕**：暴力枚举+剪枝优化。  
3. **P1613 跑路**：利用数的二进制特性优化路径计算。  

---

## 个人心得摘录  
> 「灵光一闪」题解提到：  
> *“s[i] 绝对不是 0，所以可以放心输出”*  
> → 调试经验：特判 0 后，剩余数字首位非 0，避免前导零陷阱。  

> 「封禁用户」题解提到：  
> *“526 到底该输出 Yes/n56 还是 NO”*  
> → 思维顿悟：需按顺序组合而非任意位置取数，易漏判非连续情况。  

---

## 可视化代码片段（复古风格）  

```javascript
// Canvas 绘制数字块（8-bit 风格）
function drawPixelNumber(ctx, x, y, num, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x, y, 16, 16);
    ctx.fillStyle = "#FFFFFF";
    ctx.font = "12px 'Press Start 2P'";
    ctx.fillText(num, x+4, y+12);
}

// 扫描动画（自动模式）
function autoScan() {
    for(let i=0; i<s.length; i++){
        highlightBlock(i, "red"); // 一位数高亮
        if(s[i]%8 === 0) triggerWin(i);
        for(let j=i+1; j<s.length; j++){
            highlightBlock(j, "blue"); // 两位数高亮
            if((s[i]*10 + s[j])%8 ===0) triggerWin(i,j);
            for(let k=j+1; k<s.length; k++){
                highlightBlock(k, "green"); // 三位数高亮
                if((s[i]*100 + s[j]*10 + s[k])%8 ===0) triggerWin(i,j,k);
            }
        }
    }
}
```

**音效设计**：  
- 使用 Web Audio API 生成 8-bit 音效：  
  - 扫描时：方波短音（频率 440Hz，时长 0.1s）。  
  - 成功时：上升琶音（C4→E4→G4）。  
  - 失败时：低频噪声（200Hz，时长 0.5s）。  

---

**END** 此设计将算法过程转化为互动式学习体验，结合数学思维与游戏化元素，深化对暴力枚举优化的理解。

---
处理用时：80.86秒