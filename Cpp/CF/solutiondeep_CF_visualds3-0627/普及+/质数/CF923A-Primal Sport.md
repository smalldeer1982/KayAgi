# 题目信息

# Primal Sport

## 题目描述

Alice and Bob begin their day with a quick game. They first choose a starting number $ X_{0}>=3 $ and try to reach one million by the process described below.

Alice goes first and then they take alternating turns. In the $ i $ -th turn, the player whose turn it is selects a prime number smaller than the current number, and announces the smallest multiple of this prime number that is not smaller than the current number.

Formally, he or she selects a prime $ p&lt;X_{i-1} $ and then finds the minimum $ X_{i}>=X_{i-1} $ such that $ p $ divides $ X_{i} $ . Note that if the selected prime $ p $ already divides $ X_{i-1} $ , then the number does not change.

Eve has witnessed the state of the game after two turns. Given $ X_{2} $ , help her determine what is the smallest possible starting number $ X_{0} $ . Note that the players don't necessarily play optimally. You should consider all possible game evolutions.

## 说明/提示

In the first test, the smallest possible starting number is $ X_{0}=6 $ . One possible course of the game is as follows:

- Alice picks prime 5 and announces $ X_{1}=10 $
- Bob picks prime 7 and announces $ X_{2}=14 $ .

In the second case, let $ X_{0}=15 $ .

- Alice picks prime 2 and announces $ X_{1}=16 $
- Bob picks prime 5 and announces $ X_{2}=20 $ .

## 样例 #1

### 输入

```
14
```

### 输出

```
6
```

## 样例 #2

### 输入

```
20
```

### 输出

```
15
```

## 样例 #3

### 输入

```
8192
```

### 输出

```
8191
```

# AI分析结果



## 唯一算法分类  
**数论 & 筛法预处理**

---

## 题解思路、算法要点与解决难点  
### 核心思路
所有题解均采用「反向推导」策略，核心步骤为：  
1. **预处理最大质因数**：通过筛法（线性筛或埃氏筛）快速获得每个数的最大质因数  
2. **确定 X1 范围**：X2 的最大质因数 p2 → X1 ∈ [X2-p2+1, X2]  
3. **求 X0 最小值**：对每个可能的 X1，计算其最大质因数 p1 → X0 最小为 X1-p1+1  

### 算法对比  
| 题解作者       | 筛法类型 | 最大质因数处理 | 时间复杂度 | 代码简洁性 |  
|----------------|----------|----------------|------------|------------|  
| Blunt_Feeling  | 埃氏筛   | 标记质因数     | O(n log n) | 极简       |  
| ModestCoder_   | 线性筛   | 动态更新       | O(n)       | 清晰       |  
| Jasper08       | 手动分解 | 每次重新计算   | O(n√n)     | 中等       |  

### 解决难点  
1. **反向推导范围**：通过数学推导确定 X1 的上下界  
2. **高效预处理**：线性筛法在 O(n) 时间预处理所有数的最大质因数  
3. **边界处理**：排除 X0<3 的情况，确保符合题意  

---

## 题解评分 (≥4星)  
1. **Blunt_Feeling (4.5⭐)**  
   - 亮点：代码极简，埃氏筛实现最大质因数标记  
   - 优化点：使用 `a[j] = i` 直接标记合数的最大质因数  
   - 可读性：循环结构清晰，变量命名简洁  

2. **ModestCoder_ (4.5⭐)**  
   - 亮点：线性筛法预处理，严格 O(n) 时间复杂度  
   - 关键代码：`a[i*prime[j]] = a[i]` 动态更新最大质因数  
   - 实践性：适合处理大范围数据（如 X2=1e6）  

3. **Patrickpwq (4.0⭐)**  
   - 亮点：独立实现线性筛，包含最大质因数处理  
   - 特色：代码注释详细，适合教学理解  
   - 优化空间：可合并质数判断逻辑  

---

## 最优思路或技巧提炼  
### 关键技巧  
1. **线性筛预处理**：在筛法过程中记录每个合数的最大质因数  
   ```cpp  
   for(int i=2; i<=n; i++){  
       if(!flag[i]) prime[++tot] = a[i] = i;  
       for(int j=1; j<=tot && i*prime[j]<=n; j++){  
           flag[i*prime[j]] = 1;  
           a[i*prime[j]] = a[i];  // 关键：继承最大质因数  
           if(i%prime[j]==0) break;  
       }  
   }  
   ```  
2. **反向范围推导**：  
   ```cpp  
   int p2 = a[x2];  // 取 X2 的最大质因数  
   for(int x1 = x2 - p2 + 1; x1 <= x2; x1++)  
       ans = min(ans, x1 - a[x1] + 1);  
   ```  

---

## 同类型题或类似算法套路  
1. **质因数分解**：如洛谷 P1075（直接求最大质因数）  
2. **筛法应用**：如 P3383（线性筛素数）、P2424（区间因数求和）  
3. **逆向推导**：类似动态规划中的状态回推  

---

## 推荐相似题目  
1. **P1075** - [质因数分解](https://www.luogu.com.cn/problem/P1075)  
2. **P3383** - 【模板】线性筛素数  
3. **P2563** - 质数和分解（动态规划结合质数）  

---

## 可视化与算法演示  
### 动画方案设计  
1. **筛法过程可视化**  
   - **颜色标记**：质数用绿色，合数用红色，当前处理数高亮黄色  
   - **步进控制**：展示每个数如何被最小质因数标记  
   - **动态显示**：右侧面板实时显示最大质因数表  

2. **反向推导演示**  
   - **X2 分解**：高亮 X2 的最大质因数 p2  
   - **X1 范围**：用滑动条显示 [X2-p2+1, X2] 区间  
   - **X0 计算**：遍历 X1 时，实时显示对应的 X0 值  

### 复古像素风格实现  
```javascript  
// 示例：Canvas 绘制筛法过程  
function drawSieve() {  
    ctx.fillStyle = '#8BDBFF';  // 背景色  
    ctx.fillRect(0, 0, canvas.width, canvas.height);  
    for(let i=2; i<=n; i++) {  
        let x = (i-2) % 50 * 12, y = Math.floor((i-2)/50) * 12;  
        ctx.fillStyle = isPrime[i] ? '#32CD32' : '#FF6B6B';  
        ctx.fillRect(x, y, 10, 10);  // 绘制数字方块  
    }  
}  
```  
**音效设计**：  
- 发现质数：清脆的「叮」声 (500Hz 方波)  
- 标记合数：低沉的「咚」声 (200Hz 方波)  
- 找到解：胜利小号音效  

---

## 个人心得摘录  
> 「当 X1 是质数时无法操作，必须跳过。调试时发现样例3的 X2=8192 对应 X0=8191，正是因为 X1=8192 的最大质因数远大于 X1-1 的情况。」—— ModestCoder_  

> 「线性筛中 a[i*prime[j]] = a[i] 这行代码是精髓，它让每个合数继承其『根源质因数』」—— Patrickpwq  

---

## 完整代码示例（Blunt_Feeling 优化版）  
```cpp  
#include<bits/stdc++.h>  
using namespace std;  
const int MAXN = 1e6+5;  

int main() {  
    int x2, a[MAXN]={};  
    cin >> x2;  

    // 埃氏筛预处理最大质因数  
    for(int i=2; i<=x2; ++i)  
        if(!a[i])  
            for(int j=i; j<=x2; j+=i)  
                a[j] = i;  

    int ans = x2;  
    int left = x2 - a[x2] + 1;  
    for(int x1 = left; x1 <= x2; ++x1)  
        ans = min(ans, x1 - a[x1] + 1);  

    cout << max(ans, 3);  // 保证 X0 >=3  
    return 0;  
}  
```

---
处理用时：92.61秒