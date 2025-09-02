# 题目信息

# [USACO09OPEN] Cow Digit Game S

## 题目描述

Bessie is playing a number game against Farmer John, and she wants you to help her achieve victory.

Game i starts with an integer N\_i (1 <= N\_i <= 1,000,000). Bessie goes first, and then the two players alternate turns. On each turn, a player can subtract either the largest digit or the smallest non-zero digit from the current number to obtain a new number. For example, from 3014 we may subtract either 1 or 4 to obtain either 3013 or 3010, respectively. The game continues until the number becomes 0, at which point the last player to have taken a turn is the winner.

Bessie and FJ play G (1 <= G <= 100) games. Determine, for each game, whether Bessie or FJ will win, assuming that both play perfectly (that is, on each turn, if the current player has a move that will guarantee his or her win, he or she will take it).

Consider a sample game where N\_i = 13. Bessie goes first and takes 3, leaving 10. FJ is forced to take 1, leaving 9. Bessie takes the remainder and wins the game.

贝茜和约翰在玩一个数字游戏．贝茜需要你帮助她．

游戏一共进行了G(1≤G≤100)场．第i场游戏开始于一个正整数Ni(l≤Ni≤1,000,000)．游

戏规则是这样的：双方轮流操作，将当前的数字减去一个数，这个数可以是当前数字的最大数码，也可以是最小的非0数码．比如当前的数是3014，操作者可以减去1变成3013，也可以减去4变成3010．若干次操作之后，这个数字会变成0．这时候不能再操作的一方为输家．    贝茜总是先开始操作．如果贝茜和约翰都足够聪明，执行最好的策略．请你计算最后的赢家．

比如，一场游戏开始于13.贝茜将13减去3变成10．约翰只能将10减去1变成9．贝茜再将9减去9变成0．最后贝茜赢．


## 说明/提示

For the first game, Bessie simply takes the number 9 and wins. For the second game, Bessie must take 1 (since she cannot take 0), and then FJ can win by taking 9.


## 样例 #1

### 输入

```
2 
9 
10 
```

### 输出

```
YES 
NO 
```

# AI分析结果



---

## 唯一算法分类  
博弈论-必胜态/必败态分析  

---

## 综合分析与结论  
### 核心算法流程  
1. **状态定义**：`f[i]` 表示数字 `i` 是否为必胜态  
2. **初始状态**：1-9均为必胜态（可直接减到0）  
3. **状态转移**：  
   `f[i] = !(f[i-max_digit(i)] && f[i-min_digit(i)])`  
   （若所有后续状态均为必胜态，则当前为必败态）  
4. **高效求极值**：通过数位分解快速计算每个数的最大/最小非零数码  

### 可视化设计要点  
1. **动画流程**：  
   - **数位分解**：高亮当前处理的数字各数位  
   - **极值计算**：用不同颜色标记最大/最小数码  
   - **状态转移**：箭头连接 `i` → `i-max` 和 `i` → `i-min`，动态染色必胜态（绿色）和必败态（红色）  
2. **8-bit风格实现**：  
   - **Canvas网格**：每格表示一个数字，初始化时显示白色  
   - **状态染色**：预处理时用渐变色填充（绿→红表示必胜→必败）  
   - **音效触发**：状态更新时播放8-bit电子音（升调表必胜，降调表必败）  
3. **交互功能**：  
   - 速度滑块控制预处理速度（1-1000数字/秒）  
   - 暂停时点击任意数字，显示其max/min计算过程  

---

## 题解清单（≥4星）  
### 1. konjacq（⭐⭐⭐⭐⭐）  
**亮点**：  
- 预处理100万数据的标准模板  
- 提供离线生成数据的优化思路  
- 代码简洁高效（时间复杂度O(7*1e6)）  

### 2. Refined_heart（⭐⭐⭐⭐）  
**亮点**：  
- 使用SG函数理论清晰解释  
- 代码极简（仅25行含完整逻辑）  
- 预处理与查询分离，结构清晰  

### 3. qzhwlyn（⭐⭐⭐⭐）  
**亮点**：  
- 展示错误尝试与修正过程（40→100分）  
- 添加离线预处理优化说明  
- 注释详细，适合教学  

---

## 最优思路提炼  
### 关键技巧  
1. **必胜态推导公式**：  
   `当前必胜 ↔ 存在至少一个必败后继态`  
2. **极值快速计算**：  
   ```cpp  
   inline int fmax(int x) { // 计算最大数码  
       int m=0;  
       while(x) m=max(m,x%10), x/=10;  
       return m;  
   }  
   ```  
3. **预处理优化**：  
   按最大查询值动态计算，避免处理无用数据  

---

## 同类型题拓展  
### 通用解法  
博弈论问题中，若每次操作后的状态可穷举，均可采用「必胜态/必败态标记法」，典型特征：  
1. 状态转移可逆推（如石子游戏、取硬币）  
2. 存在明显的边界条件（如本题的1-9直接必胜）  

### 推荐题目  
1. [P2197] Nim游戏（基础博弈模板）  
2. [P1247] 取火柴游戏（Nim博弈变形）  
3. [P2575] 阶梯博弈（博弈论+数学分析）  

---

## 个人心得摘录  
> **qzhwlyn**：  
> "最初尝试枚举所有数位导致超时，意识到必须优化极值计算过程"  
> → **教训**：数位处理必须O(1)或O(digits)，避免线性扫描  

> **konjacq**：  
> "发现洛谷禁止提交预处理数据，改用内存压缩技巧"  
> → **技巧**：大规模预处理时考虑平台限制  

---

## 核心代码片段  
```cpp  
// 状态预处理核心逻辑  
for(int i=10; i<=1e6; ++i) {  
    int mx=0, mi=10, tmp=i;  
    while(tmp) {  
        int d=tmp%10;  
        mx = max(mx, d);  
        if(d>0) mi = min(mi, d);  
        tmp /= 10;  
    }  
    f[i] = !(f[i-mx] && f[i-mi]);  
}  
```

---

## 可视化示例（伪代码）  
```javascript  
// 8-bit风格状态染色  
const canvas = document.getElementById('grid');  
ctx.fillStyle = '#8B8B8B'; // 初始灰色  
// 预处理动画循环  
function animate(i) {  
    let mx = calcMaxDigit(i);  
    let mi = calcMinDigit(i);  
    // 高亮当前数位  
    drawDigits(i, {highlight: true});  
    // 计算后继状态  
    let s1 = i - mx, s2 = i - mi;  
    // 染色当前格子  
    ctx.fillStyle = f[i] ? '#00FF00' : '#FF0000';  
    ctx.fillRect((i%100)*8, Math.floor(i/100)*8, 7, 7);  
    // 播放音效  
    playSound(f[i] ? 'win' : 'lose');  
}  
```  
![可视化示意图](https://img-blog.csdnimg.cn/20210207153104504.gif#pic_center)  
（动态展示数字状态变化过程，绿色方块表示必胜态）

---
处理用时：73.19秒