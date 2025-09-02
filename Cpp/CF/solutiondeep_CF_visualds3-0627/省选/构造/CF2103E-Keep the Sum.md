# 题目信息

# Keep the Sum

## 题目描述

You are given an integer $ k $ and an array $ a $ of length $ n $ , where each element satisfies $ 0 \le a_i \le k $ for all $ 1 \le i \le n $ . You can perform the following operation on the array:

- Choose two distinct indices $ i $ and $ j $ ( $ 1 \le i,j \le n $ and $ i \neq j $ ) such that $ a_i + a_j = k $ .
- Select an integer $ x $ satisfying $ -a_j \le x \le a_i $ .
- Decrease $ a_i $ by $ x $ and increase $ a_j $ by $ x $ . In other words, update $ a_i := a_i - x $ and $ a_j := a_j + x $ .

Note that the constraints on $ x $ ensure that all elements of array $ a $ remain between $ 0 $ and $ k $ throughout the operations.

Your task is to determine whether it is possible to make the array $ a $ non-decreasing $ ^{\text{∗}} $ using the above operation. If it is possible, find a sequence of at most $ 3n $ operations that transforms the array into a non-decreasing one.

It can be proven that if it is possible to make the array non-decreasing using the above operation, there exists a solution that uses at most $ 3n $ operations.

 $ ^{\text{∗}} $ An array $ a_1, a_2, \ldots, a_n $ is said to be non-decreasing if for all $ 1 \le i \le n - 1 $ , it holds that $ a_i \le a_{i+1} $ .

## 说明/提示

In the first test case, the array is already non-decreasing, so we do not need to perform any operations.

In the second test case, we can perform an operation with $ i=4 $ , $ j=1 $ , and $ x=1 $ . $ a_4 $ decreases by $ 1 $ to become $ 5 - 1 = 4 $ while $ a_1 $ increases by $ 1 $ to become $ 1 + 1 = 2 $ . After the operation, the array becomes $ [2, 2, 3, 4, 4] $ , which is non-decreasing.

Note that there are other ways to make the array non-decreasing, all of which would be considered correct as long as they do not use more than $ 3 \cdot n = 15 $ operations.

In the third test case, it is not possible to make the array non-decreasing. This is because there are no distinct pairs of indices $ i $ and $ j $ where $ a_i + a_j = 7 $ , so no operation can be done on the array.

In the fourth test case, the array is transformed as follows:

1. $ [\textbf{0}, 5, 3, 2, 7, 3, 1, \textbf{10}, 4, 0] $
2. $ [0, 5, \textbf{1}, 2, \textbf{9}, 3, 1, 10, 4, 0] $
3. $ [0, 5, 1, 2, \textbf{6}, 3, \textbf{4}, 10, 4, 0] $
4. $ [0, 5, 1, 2, \textbf{3}, 3, 4, 10, \textbf{7}, 0] $
5. $ [0, 5, 1, 2, 3, 3, 4, \textbf{5}, 7, \textbf{5}] $
6. $ [0, \textbf{1}, 1, 2, 3, 3, 4, 5, 7, \textbf{9}] $

## 样例 #1

### 输入

```
4
5 100
1 2 3 4 5
5 6
1 2 3 5 4
5 7
7 1 5 3 1
10 10
2 5 3 2 7 3 1 8 4 0```

### 输出

```
0
1
4 1 1
-1
6
1 8 2
3 5 2
5 7 3
5 9 3
8 10 5
2 10 4```

# AI分析结果



## 唯一算法分类  
构造法/贪心策略  

## 综合分析与结论  
### 核心思路与难点  
**核心思路**：  
1. **必须存在至少一对匹配数**（和为K），否则无法操作。  
2. 将匹配数移动至数组两端（如a1和an），作为“枢纽”调整其他元素。  
3. 通过递进式调整（0与K、1与K-1等）逐步构建有序序列。  

**解决难点**：  
- 如何在没有直接交换能力时，借助枢纽数对实现间接交换。  
- 确保每次操作后数组仍满足0≤a_i≤K的条件。  
- 在O(n)时间复杂度内完成操作步骤。  

**算法流程**：  
1. 离散化处理所有a_i和K-a_i的值，便于快速匹配。  
2. 查找初始匹配对，将其移动至数组两端。  
3. 维护前缀指针px和后缀指针py，按值从小到大将元素交换至正确位置。  
4. 每轮处理一对互补值（v和K-v），通过三次交换完成元素归位。  

### 可视化设计  
- **动画方案**：  
  1. 初始匹配对用红色高亮，移动至首尾时触发黄色闪光。  
  2. 每次交换操作时，源元素（蓝色）和目标位置（绿色）闪烁，数值变化以箭头动画表示。  
  3. 当前处理的互补值对（如0/K）用不同底色区分，已排序部分渐变灰色。  

- **复古像素风格**：  
  - 16色调色板（深蓝=未处理，亮绿=当前操作，红=枢纽）。  
  - 音效：交换时播放8-bit点击音，完成排序播放NES过关音效。  

## 题解清单 (≥4星)  
1. **wanggk（4星）**  
   - 亮点：离散化处理+集合维护，代码简洁高效。  
   - 关键代码：  
     ```cpp  
     void Swap(int x,int to,int y){
         if(x==to) return;
         Print(x,y,h[a[x]]-h[a[to]]);
         Print(to,y,h[a[to]]-h[a[x]]);
         Erase(x),Erase(to),swap(a[x],a[to]);
         Insert(x),Insert(to);
     }
     ```  

2. **liangbob（4星）**  
   - 亮点：详细推导交换步骤，三次操作实现任意交换。  
   - 心得：“必须借助中间匹配对，类似寄存器暂存数据”  

## 最优思路提炼  
1. **枢纽构造**：将任意匹配对移动至首尾，建立全局交换基础。  
2. **分层处理**：按互补值从小到大处理（0/K→1/K-1→...），避免冲突。  
3. **离散化加速**：将原始值映射为连续编号，用set维护位置集合。  

## 同类型题  
- CF489A SwapSort（直接交换排序）  
- P1969 积木大赛（递推构造）  
- P2894 [USACO08FEB]Hotel G（区间维护）  

## 推荐洛谷题  
1. P1969（构造性调整）  
2. P1970（贪心策略）  
3. P1908（逆序对与交换）  

## 核心代码实现  
```cpp  
// 离散化与初始化  
For(i,1,n) h[i-1]=a[i],h[i+n-1]=K-a[i];  
sort(h,h+n+n);  
K=unique(h,h+n+n)-h-1;  

// 查找初始匹配对  
For(i,1,n){  
    a[i]=lower_bound(h,h+K+1,a[i])-h;  
    if(st[K-a[i]].size()) px=*st[K-a[i]].begin(),py=i;  
    Insert(i);  
}  

// 移动匹配对至首尾  
Swap(px,1,py); px=1;  
Swap(py,n,px); py=n;  

// 分层处理互补值  
for(int v=0;v<K-v;v++){  
    Print(px,py,h[a[px]]-h[v]);  
    a[px]=v,a[py]=K-v;  
    while(!st[v].empty())  
        Swap(*st[v].begin(),++px,py),Erase(px);  
    while(!st[K-v].empty())  
        Swap(*st[K-v].begin(),--py,px),Erase(py);  
}  
```  

## 个人心得  
- **离散化技巧**：需同时离散原值和互补值，保证配对关系不变。  
- **集合维护**：用set快速查找同类元素位置，避免线性扫描。  
- **操作次数控制**：每元素最多3次操作（移动至枢纽+两次交换），严格满足3n限制。  

## 复古游戏化动画（伪代码）  
```javascript  
// Canvas绘制函数  
function drawArray(ctx, arr, px, py) {  
    arr.forEach((val, i) => {  
        ctx.fillStyle = i===0||i===arr.length-1 ? '#FF0000' :   
                        (i<=px||i>=py) ? '#00FF00' : '#0000FF';  
        ctx.fillRect(i*20, 100-val*5, 18, val*5);  
    });  
}  

// 音效触发  
function playSwapSound() {  
    const osc = audioCtx.createOscillator();  
    osc.frequency.setValueAtTime(440, audioCtx.currentTime);  
    osc.connect(audioCtx.destination);  
    osc.start(); osc.stop(audioCtx.currentTime + 0.1);  
}  
```

---
处理用时：79.24秒