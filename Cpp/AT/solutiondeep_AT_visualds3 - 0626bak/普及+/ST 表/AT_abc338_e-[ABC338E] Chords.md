# 题目信息

# [ABC338E] Chords

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc338/tasks/abc338_e

円周上に $ 2N $ 個の点が等間隔に並んでおり、ある点から始めて時計回りに $ 1 $ から $ 2N $ までの番号が付けられています。

円周上にはさらに $ N $ 個の弦があり、$ i $ 個目の弦は点 $ A_i $ と点 $ B_i $ を結んでいます。 ここで、$ A_1,\dots,A_N,B_1,\dots,B_N $ は全て相異なることが保証されます。

弦どうしの交点が存在するかどうか判定してください。

## 说明/提示

### 制約

- $ 2\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i,B_i\ \leq\ 2N $
- $ A_1,\dots,A_N,B_1,\dots,B_N $ は全て相異なる
- 入力は全て整数

### Sample Explanation 1

!\[\](https://img.atcoder.jp/abc338/de1d9dd6cf38caec1c69fe035bdba545.png) 図のように、弦 $ 1 $（点 $ 1 $ と点 $ 3 $ を結ぶ線分）と弦 $ 2 $（点 $ 4 $ と点 $ 2 $ を結ぶ線分）が交点を持つので、`Yes` を出力します。

### Sample Explanation 2

!\[\](https://img.atcoder.jp/abc338/1b3b982c8d6ca59f00ca0edd218fb9c4.png) 図のように、弦どうしの交点は存在しないので、`No` を出力します。

## 样例 #1

### 输入

```
3
1 3
4 2
5 6```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3
6 1
4 3
2 5```

### 输出

```
No```

## 样例 #3

### 输入

```
4
2 4
3 7
8 6
5 1```

### 输出

```
Yes```

# AI分析结果



### 唯一算法分类  
栈的应用（括号匹配）

---

### 综合分析与结论  
**核心思路**：将弦视为括号对，通过栈检查括号匹配情况。若遍历过程中出现不匹配的右括号，则存在交点。  
**难点**：将几何问题转化为序列匹配问题，需理解弦相交的充要条件（区间交错但不包含）。  
**算法流程**：  
1. 预处理每个点的配对点。  
2. 遍历所有点，左端点入栈，右端点检查栈顶是否匹配。  
3. 若发现不匹配，立即输出存在交点。  

**可视化设计**：  
- **动画流程**：Canvas 绘制圆上点，动态标记当前处理点（红色高亮），栈状态以列表展示。匹配成功时弹出栈顶（绿色闪烁），失败时红色警示。  
- **复古风格**：16色像素调色板，音效采用 8-bit 风格，匹配成功时播放清脆音效，失败时低沉提示音。  
- **交互控制**：支持步进执行，速度可调，自动演示模式模拟 AI 决策过程。  

---

### 题解清单（≥4星）  
1. **spfa_（5星）**  
   - 亮点：代码极简，核心逻辑仅10行，完美体现栈的应用。  
   - 代码片段：  
     ```cpp  
     for (int i = 1; i <= n<<1; ++i) {  
         if (v[i].fi) stk[++top] = v[i].se;  
         else if (stk[top--] != v[i].se) puts("Yes"), exit(0);  
     }  
     ```  

2. **CheZiHe929（4星）**  
   - 亮点：注释清晰，变量命名规范，适合新手理解。  
   - 个人心得：调试中发现栈顶匹配判断是关键，漏判会导致错误。  

3. **tanzicheng（4星）**  
   - 亮点：代码简短，直接映射括号匹配逻辑，易移植到其他语言。  

---

### 核心代码实现  
```cpp  
#include <iostream>  
#include <stack>  
using namespace std;  

int main() {  
    int n;  
    cin >> n;  
    int to[400005] = {0};  
    for (int i = 0; i < n; ++i) {  
        int a, b;  
        cin >> a >> b;  
        to[a] = b;  
        to[b] = a;  
    }  
    stack<int> stk;  
    for (int i = 1; i <= 2*n; ++i) {  
        if (stk.empty() || stk.top() != to[i])  
            stk.push(i);  
        else  
            stk.pop();  
    }  
    cout << (stk.empty() ? "No" : "Yes");  
    return 0;  
}  
```  

---

### 同类型题推荐  
1. **P1241 括号序列**：基础括号匹配，练习栈的经典应用。  
2. **P1972 [SDOI2009] HH的项链**：区间覆盖问题，可用类似区间标记法。  
3. **CF1023C Bracket Subsequence**：最短合法括号子序列，需动态维护栈。  

---

### 可视化关键代码（JS片段）  
```javascript  
// 初始化 Canvas  
const canvas = document.getElementById('canvas');  
const ctx = canvas.getContext('2d');  
const points = Array.from({length: 2*N}, (_,i) => ({  
    x: Math.cos(i*Math.PI/N),   
    y: Math.sin(i*Math.PI/N)  
}));  

// 动画步进  
function step() {  
    let current = pointsOrder[idx];  
    ctx.fillStyle = current.isLeft ? '#FF0000' : '#00FF00';  
    drawPoint(current);  
    if (current.isLeft) {  
        stack.push(current.pair);  
    } else {  
        if (stack.pop() !== current.id) {  
            playSound('error');  
            highlightConflict();  
        }  
    }  
    idx++;  
}  
```  

---

### 复古风格设计  
- **调色板**：16色，使用 NES 经典配色（#6D6D6D, #000000, #7C3800...）。  
- **音效**：Web Audio 生成方波音效，匹配时频率 880Hz，错误时 220Hz。  
- **AI 模式**：自动以每步 500ms 执行，模拟解题过程。

---
处理用时：82.55秒