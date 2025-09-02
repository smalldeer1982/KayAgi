# 题目信息

# Two Movies

## 题目描述

一个公司发行了两部电影。现在有 $n$ 位观众，每个人都会看一部这个公司的电影。

每位观众都会对其看的电影进行评分，分数 $a_i,b_i\in\{-1，0，1\}$。电影的总评分是看了此电影的观众对此电影的评分总和。公司的最终得分是这两部电影的总评分的较小值。

已知这些观众对两部电影的评价，你需要给每个人推荐一部电影，使公司的最终得分最大。求这个最大值。

## 样例 #1

### 输入

```
4
2
-1 1
-1 -1
1
-1
-1
5
0 -1 1 0 1
-1 1 0 0 1
4
-1 -1 -1 1
-1 1 1 1```

### 输出

```
0
-1
1
1```

# AI分析结果



## 算法分类
**贪心算法**

---

## 题解思路与解决难点

### 核心思路
1. **差异评分优先处理**  
   当观众对两部电影评分不同时，推荐其评分较高的电影，直接获得最大收益。
   
2. **相同评分动态平衡**  
   若评分相同（1或-1），在完成差异评分处理后，根据当前总评分动态分配：
   - 若评分为1，优先给当前较小的总评分加1，提高短板
   - 若评分为-1，优先从当前较大的总评分减1，削弱长板

### 关键难点与解决方案
- **动态平衡的实时判断**  
  需要在每次处理相同评分时实时比较两部电影当前总评分，动态决定如何分配。例如，Vct14题解通过循环中判断 `suma >= sumb` 决定操作方向。

- **相同评分的分类处理**  
  部分题解（如HuangBarry）将相同评分进一步分为1和-1两类，分别统计数量后批量处理，降低时间复杂度。

---

## 题解评分（≥4星）

### 1. Vct14（⭐⭐⭐⭐⭐）
- **亮点**  
  代码简洁，逻辑清晰，通过 `c[]` 数组缓存相同评分，逐个处理时动态判断当前总分差。
- **代码片段**  
  ```cpp
  for(int i=1; i<=s; i++){
      if(suma>=sumb){
          if(c[i]==1) sumb++;
          else suma--;
      }else{
          if(c[i]==1) suma++;
          else sumb--;
      }
  }
  ```

### 2. chatoudp（⭐⭐⭐⭐）
- **亮点**  
  使用 `vector` 动态存储相同评分，处理时通过 `f1 < f2` 判断方向，逻辑与Vct14类似但实现方式不同。
- **关键逻辑**  
  ```cpp
  if(a[p]<0) f1 += a[p];
  else f2 += b[p];
  ```

### 3. HuangBarry（⭐⭐⭐⭐）
- **亮点**  
  显式分离1和-1的计数，通过 `while` 循环批量处理，更直观体现贪心策略。
- **核心代码**  
  ```cpp
  while(sum1--) // 处理所有1的情况
      if(movie1 <= movie2) movie1++;
  while(sumfu1--) // 处理所有-1的情况
      if(movie1 >= movie2) movie1--;
  ```

---

## 最优思路提炼
### 关键技巧
1. **两阶段贪心**  
   - **阶段一**：无脑选择差异评分中的较高者
   - **阶段二**：用相同评分动态平衡总分差

2. **平衡操作可视化**  
   ```python
   # 伪代码示例
   for same_score in same_scores:
       if current_score_A >= current_score_B:
           if same_score == 1: B += 1  # 提升短板
           else: A -= 1               # 削弱长板
       else:
           if same_score == 1: A += 1
           else: B -= 1
   ```

---

## 类似题目推荐
1. [CF1029C Maximal Intersection](https://www.luogu.com.cn/problem/CF1029C)  
   **共同点**：通过贪心策略移除一个元素求最大剩余交集

2. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)  
   **相似点**：动态选择最优操作（删除数字）以最大化/最小化结果

3. [CF1760E Binary Inversions](https://www.luogu.com.cn/problem/CF1760E)  
   **关联点**：通过局部修改（翻转0/1）最大化全局指标（逆序对）

---

## 可视化设计

### 核心算法演示
**动画方案**：
1. **初始状态**  
   - 左右两栏分别显示 `SumA` 和 `SumB`，背景色区分
   - 观众列表以图标排列，颜色表示评分（绿=1，灰=0，红=-1）

2. **处理差异评分**  
   - 高亮当前观众图标，箭头指向选择的电影栏
   - 对应总评分数值闪烁更新

3. **处理相同评分**  
   - 动态显示当前 `SumA` 与 `SumB` 比较结果
   - 平衡操作时显示上升/下降动画（↑+1 或 ↓-1）

### 复古像素风格实现
```javascript
// 伪代码示例：Canvas绘制观众图标
function drawViewer(ctx, x, y, score) {
    const colors = {1: '#00FF00', 0: '#808080', '-1': '#FF0000'};
    ctx.fillStyle = colors[score];
    ctx.fillRect(x, y, 16, 16); // 16x16像素方块
}

// 音效触发
function playSound(effect) {
    const sounds = {
        add: new Audio('data:audio/wav;base64,UklGRl9...'), // +1音效
        sub: new Audio('data:audio/wav;base64,UklGRl9...')  // -1音效
    };
    sounds[effect].play();
}
```

---

## 完整代码（Vct14实现）
```cpp
#include<bits/stdc++.h>
using namespace std;

int a[200002], b[200002], c[200002];

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        for(int i=1; i<=n; i++) cin>>a[i]; 
        for(int i=1; i<=n; i++) cin>>b[i];
        int suma=0, sumb=0, s=0;
        
        // 阶段一：处理差异评分
        for(int i=1; i<=n; i++){
            if(a[i]>b[i]) suma += a[i];
            else if(a[i]<b[i]) sumb += b[i];
            else if(a[i]!=0) c[++s] = a[i];
        }
        
        // 阶段二：平衡相同评分
        for(int i=1; i<=s; i++){
            if(suma >= sumb){
                if(c[i]==1) sumb++;
                else suma--;
            } else {
                if(c[i]==1) suma++;
                else sumb--;
            }
        }
        
        cout << min(suma, sumb) << "\n";
    }
    return 0;
}
```

---
处理用时：74.26秒