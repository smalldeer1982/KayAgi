# 题目信息

# Bessie and MEX

## 题目描述

[MOOO! - Doja Cat](https://soundcloud.com/amalaofficial/mooo)

⠀



Farmer John has a permutation $ p_1, p_2, \ldots, p_n $ , where every integer from $ 0 $ to $ n-1 $ occurs exactly once. He gives Bessie an array $ a $ of length $ n $ and challenges her to construct $ p $ based on $ a $ .

The array $ a $ is constructed so that $ a_i $ = $ \texttt{MEX}(p_1, p_2, \ldots, p_i) - p_i $ , where the $ \texttt{MEX} $ of an array is the minimum non-negative integer that does not appear in that array. For example, $ \texttt{MEX}(1, 2, 3) = 0 $ and $ \texttt{MEX}(3, 1, 0) = 2 $ .

Help Bessie construct any valid permutation $ p $ that satisfies $ a $ . The input is given in such a way that at least one valid $ p $ exists. If there are multiple possible $ p $ , it is enough to print one of them.

## 说明/提示

In the first case, $ p = [0, 1, 4, 2, 3] $ is one possible output.

 $ a $ will then be calculated as $ a_1 = \texttt{MEX}(0) - 0 = 1 $ , $ a_2 = \texttt{MEX}(0, 1) - 1 = 1 $ , $ a_3 = \texttt{MEX}(0, 1, 4) - 4 = -2 $ , $ a_4 = \texttt{MEX}(0, 1, 4, 2) - 2 = 1 $ , $ a_5 = \texttt{MEX}(0, 1, 4, 2, 3) - 3 = 2 $ .

So, as required, $ a $ will be $ [1, 1, -2, 1, 2] $ .

## 样例 #1

### 输入

```
3
5
1 1 -2 1 2
5
1 1 1 1 1
3
-2 1 2```

### 输出

```
0 1 4 2 3 
0 1 2 3 4 
2 0 1```

# AI分析结果



**唯一算法分类**  
组合数学

---

### 题解思路与算法分析  
**核心难点**：如何根据逆向推导性质，通过维护当前 mex 值线性构造排列。  
**关键推导**：  
1. 整个排列的 MEX 必为 `n`，因此末位 `p_n = n - a_n`  
2. 从后往前处理时，当前 mex 表示前 i 项的 MEX。通过 `p_i = mex - a_i` 计算当前值，并维护 mex 为历史最小值（确保后续步骤中 MEX 的正确性）  

**数学证明思路**：  
- 归纳法证明 mex 维护的正确性：假设处理到 i+1 时 mex 正确，则 i 的 mex 应为前 i 项的 MEX，而 `min(mex, p_{i+1})` 保证未被后续元素干扰  
- 正确性验证：计算每个 `p_i` 时，其值必在 `0~n-1` 且不重复  

**可视化设计**：  
- **动画流程**：从右向左逐步计算 p_i，高亮当前计算位置，显示 `mex` 值和计算式 `p_i = mex - a_i`  
- **颜色标记**：当前处理位用红色框，`mex` 值用绿色显示，已确定部分用灰色  
- **像素风格**：8-bit 风格界面，步进时播放 "beep" 音效，完成时播放胜利音效  

---

### 题解评分（≥4星）  
1. **luobotianle（5星）**  
   - 思路清晰，代码简洁，线性时间复杂度  
   - 关键代码：逆向遍历维护 mex，`min` 操作保证正确性  
   ```cpp
   int mex = n;
   for(int i=n;i>=1;i--){
       p[i]=mex - a[i];
       mex = min(mex, p[i]);
   }
   ```

2. **Zhuluoan（4星）**  
   - 详细推导前因后果，补充数学证明  
   - 代码与最优解一致，注释清晰  

3. **王逸辰（4星）**  
   - 代码精简，直接体现核心逻辑  
   - 适合快速理解逆向思维  

---

### 最优思路提炼  
**逆向维护 mex 法**：  
1. **末位定锚**：利用全排列性质确定 `p_n = n - a_n`  
2. **逆向迭代**：从 `n-1` 到 `1`，计算 `p_i = mex - a_i`  
3. **最小值维护**：`mex = min(mex, p_i)` 保证前 i 项的 MEX 正确性  

**思维突破点**：  
- 全排列的 MEX 必为 n，此性质为逆向推导提供锚点  
- mex 的维护本质是排除已处理的较大值，确保前 i 项的最小未出现数  

---

### 同类题型推荐  
1. [CF1433E - Two Round Dances](https://codeforces.com/problemset/problem/1433/E)（排列组合计数）  
2. [LC 645. Set Mismatch](https://leetcode.com/problems/set-mismatch/)（寻找重复与缺失数）  
3. [洛谷 P1494 - 小明的游戏](https://www.luogu.com.cn/problem/P1494)（MEX 性质应用）  

---

### 核心代码实现  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N],p[N]; 
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        int mex=n;
        for(int i=n;i>=1;i--){
            p[i]=mex - a[i];
            mex = min(mex, p[i]);
        }
        for(int i=1;i<=n;i++) cout<<p[i]<<" \n"[i==n];
    }
    return 0;
}
```

---

### 可视化算法演示（伪代码）  
```javascript
// 初始化 Canvas
const canvas = initCanvas();
let step = n, mex = n;
const p = new Array(n+1);

function drawFrame() {
    highlight(step); // 高亮当前处理位置
    displayFormula(`p_${step} = ${mex} - ${a[step]} = ${mex - a[step]}`);
    p[step] = mex - a[step];
    mex = Math.min(mex, p[step]);
    step--;
    if(step >=1) requestAnimationFrame(drawFrame);
    else playVictorySound();
}
drawFrame();
```

---

### 复古游戏化设计  
- **像素风格**：16色调色板，网格布局显示数组  
- **音效设计**：  
  - 计算步：8-bit "beep" 短音  
  - 完成：FC 风格胜利音乐  
- **自动演示模式**：按帧步进，速度可调  
- **积分系统**：每正确一步+10分，连续正确触发连击  

---

### 个人心得摘录  
> "逆向思维是本题关键——全排列的 MEX 性质提供了天然的递归锚点，而维护最小值取代复杂数据结构是线性时间的关键。" —— Zhuluoan 题解

---
处理用时：129.20秒