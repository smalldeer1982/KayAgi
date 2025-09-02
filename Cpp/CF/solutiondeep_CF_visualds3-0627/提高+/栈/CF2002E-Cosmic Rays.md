# 题目信息

# Cosmic Rays

## 题目描述

Given an array of integers $ s_1, s_2, \ldots, s_l $ , every second, cosmic rays will cause all $ s_i $ such that $ i=1 $ or $ s_i\neq s_{i-1} $ to be deleted simultaneously, and the remaining parts will be concatenated together in order to form the new array $ s_1, s_2, \ldots, s_{l'} $ .

Define the strength of an array as the number of seconds it takes to become empty.

You are given an array of integers compressed in the form of $ n $ pairs that describe the array left to right. Each pair $ (a_i,b_i) $ represents $ a_i $ copies of $ b_i $ , i.e. $ \underbrace{b_i,b_i,\cdots,b_i}_{a_i\textrm{ times}} $ .

For each $ i=1,2,\dots,n $ , please find the strength of the sequence described by the first $ i $ pairs.

## 说明/提示

In the first test case, for the prefix of length $ 4 $ , the changes will be $ [0,0,1,0,0,0,1,1,1,1,1]\rightarrow[0,0,0,1,1,1,1]\rightarrow[0,0,1,1,1]\rightarrow[0,1,1]\rightarrow[1]\rightarrow[] $ , so the array becomes empty after $ 5 $ seconds.

In the second test case, for the prefix of length $ 4 $ , the changes will be $ [6,6,6,6,3,6,6,6,6,0,0,0,0]\rightarrow[6,6,6,6,6,6,0,0,0]\rightarrow[6,6,6,6,6,0,0]\rightarrow[6,6,6,6,0]\rightarrow[6,6,6]\rightarrow[6,6]\rightarrow[6]\rightarrow[] $ , so the array becomes empty after $ 7 $ seconds.

## 样例 #1

### 输入

```
4
4
2 0
1 1
3 0
5 1
6
4 6
1 3
4 6
4 0
7 6
6 3
7
9 0
7 1
5 0
7 1
9 0
1 1
2 0
10
10 7
4 9
2 2
7 9
2 8
8 5
11 7
15 5
12 7
4 0```

### 输出

```
2 2 4 5 
4 4 7 7 10 10 
9 9 9 9 9 9 10 
10 10 10 10 10 10 12 15 15 15```

# AI分析结果



1. **算法分类**  
   单调栈

---

### 题解思路与核心分析

**题目核心**：每次操作删除所有极长连续段的第一个元素，求每个前缀数组被删空的秒数。  
**关键观察**：相邻同色段合并后存活时间可能超过原最大值，合并条件为中间段均小于二者。  
**算法核心**：维护单调递减栈，保证栈中元素为可能影响最终时间的段，合并同色段。  

**实现要点**：  
- **单调递减栈**：保证栈中元素 `a` 值严格递减  
- **同色合并**：当栈顶与前驱段颜色相同时，合并并调整 `a` 值  
- **答案推导**：栈底元素的 `a` 值为当前前缀的强度  

**难点对比**：  
- int08 的代码实现更简洁，合并条件处理清晰  
- chlchl 的代码结构更模块化，函数封装明确  

**结论**：栈底元素的 `a` 值即为答案，单调栈维护合并逻辑确保正确性。

---

### 题解评分 ≥4星

1. **int08（5星）**  
   - 思路清晰，代码简洁高效  
   - 合并逻辑处理精妙，直接操作栈结构  

2. **chlchl（4星）**  
   - 模块化设计增强可读性  
   - 注释与变量命名规范  

---

### 最优思路提炼

**核心技巧**：  
- **单调栈维护递减段**：确保栈中每个段的 `a` 值比后续大  
- **同色合并调整**：合并时累加前驱段与当前段的差值  
- **动态更新答案**：栈底元素始终为最大存活时间  

**代码关键段**：  
```cpp
while (pt > 0 && sta[pt].first <= a[i]) {
    if (sta[pt - 1].second == b[i]) 
        a[i] += sta[pt - 1].first - sta[pt].first, pt--;
    pt--;
}
sta[++pt] = {a[i], b[i]};
cout << sta[1].first << " ";
```

---

### 相似题目推荐

1. **P5788 单调栈模板**（基础单调栈应用）  
2. **P1901 发射站**（递减栈处理相邻影响）  
3. **P2866 Bad Hair Day**（单调栈统计可见性）  

---

### 可视化与算法演示

**动画设计**：  
- **像素风格栈结构**：用不同颜色方块表示段，高度为 `a` 值  
- **合并特效**：同色段合并时播放闪烁动画，数值更新  
- **音效触发**：弹出段时低音，合并时高音，答案更新时特殊音效  

**交互控制**：  
- **步进播放**：观察栈变化与合并过程  
- **自动模式**：AI 按逻辑自动处理添加与合并  

**Canvas 示例**：  
```javascript
// 伪代码：绘制栈元素
function drawStack() {
    ctx.clearRect(0, 0, width, height);
    for (let i = 0; i < stack.length; i++) {
        drawRect(i * 50, 100 - stack[i].a * 5, 40, stack[i].a * 5, stack[i].color);
    }
}
```

---

### 代码实现（核心逻辑）

**int08 的完整代码**：  
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 333664
pair<int,int> sta[N];
int pt,n,i,j,a[N],b[N],T;
signed main() {
    cin>>T;
    while(T--) {
        cin>>n;
        for(i=1;i<=n;i++) {
            cin>>a[i]>>b[i];b[i]++;
            while(pt>0&&sta[pt].first<=a[i]) {
                if(sta[pt-1].second==b[i]) a[i]+=sta[pt-1].first-sta[pt].first,pt--;
                pt--;
            }
            sta[++pt]={a[i],b[i]};
            cout<<sta[1].first<<" ";
        }
        cout<<endl;
        pt=0;
    }
    return 0;
}
```

---

**总结**：通过单调栈维护递减段结构，合并同色段动态调整存活时间，最终栈底元素决定答案。

---
处理用时：151.09秒