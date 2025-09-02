# 题目信息

# Make It Equal

## 题目描述

There is a toy building consisting of $ n $ towers. Each tower consists of several cubes standing on each other. The $ i $ -th tower consists of $ h_i $ cubes, so it has height $ h_i $ .

Let's define operation slice on some height $ H $ as following: for each tower $ i $ , if its height is greater than $ H $ , then remove some top cubes to make tower's height equal to $ H $ . Cost of one "slice" equals to the total number of removed cubes from all towers.

Let's name slice as good one if its cost is lower or equal to $ k $ ( $ k \ge n $ ).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1065C/658a593f32bf5073d4f1a1a7bd7987feaeb4f838.png)Calculate the minimum number of good slices you have to do to make all towers have the same height. Of course, it is always possible to make it so.

## 说明/提示

In the first example it's optimal to make $ 2 $ slices. The first slice is on height $ 2 $ (its cost is $ 3 $ ), and the second one is on height $ 1 $ (its cost is $ 4 $ ).

## 样例 #1

### 输入

```
5 5
3 1 2 2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4 5
2 3 4 5
```

### 输出

```
2
```

# AI分析结果



### 综合分析与结论

#### 题目核心与贪心策略
**问题核心**：通过最少的切割次数将所有塔的高度统一，每次切割的总方块数不超过 k。  
**贪心策略**：  
1. **分层计算**：将问题转化为按高度分层处理，统计每一层需要切割的方块总数。
2. **前缀和优化**：利用差分或桶排序预处理每个高度对应的方块数，再通过前缀和快速累加。
3. **累加切割**：从最高层向下遍历，累加每层的方块数，当总和超过 k 时触发一次切割，重置累加器。
4. **剩余处理**：最后若剩余方块数不为零，需额外一次切割。

**解决难点**：  
- **分层计算的高效性**：需避免暴力枚举所有可能的切割高度，通过预处理将复杂度降至 O(max_h)。  
- **边界处理**：如所有塔高度相同时的特判、最后剩余方块的切割判断。  

#### 可视化设计思路
- **像素动画**：用不同颜色的像素块表示各塔高度，切割时高亮当前处理层，显示累计方块数。  
- **贪心过程演示**：逐层下降高度，实时更新累加值和切割次数，超限时触发切割动画。  
- **音效与交互**：切割时播放音效，支持步进/暂停，展示当前切割高度和剩余方块数。  
- **复古风格**：采用 8-bit 像素风格，背景音乐循环播放，切割时显示得分增加。

---

### 题解评分（≥4星）

1. **Blunt_Feeling（★★★★☆）**  
   - **亮点**：前缀和+桶排序预处理，代码简洁高效，处理了最终剩余值的边界情况。  
   - **代码可读性**：变量命名清晰，逻辑直接。  
   - **个人心得**：提到第六个测试点的边界错误，强调最后剩余值的处理。  

2. **MY_Lee（★★★★☆）**  
   - **亮点**：差分优化预处理，贪心累加逻辑清晰，复杂度 O(n + h) 最优。  
   - **代码可读性**：注释详细，分步骤拆解。  
   - **实践性**：直接通过差分统计高度层，避免复杂数据结构。  

3. **Fan_Tuan（★★★★☆）**  
   - **亮点**：桶排序后贪心遍历，代码简洁，处理了高度相同的特判。  
   - **优化点**：通过排序预处理高度，逻辑直观。  

---

### 最优思路与代码实现

#### 核心贪心逻辑
```cpp
// 预处理差分数组（MY_Lee 方法）
for (int i = 1; i <= n; i++) {
    scanf("%d", &x);
    tong[1]++;          // 差分起点+1
    tong[x + 1]--;      // 差分终点-1
}
// 计算前缀和得到每层方块数
for (int i = 1; i <= mx; i++) {
    tong[i] += tong[i - 1];
}

// 贪心累加切割
int ans = 0, cnt = 0;
for (int i = max_h; i > min_h; i--) {
    if (cnt + tong[i] > k) {
        ans++;
        cnt = tong[i];  // 重置累加器
    } else {
        cnt += tong[i];
    }
}
if (cnt > 0) ans++;     // 处理剩余方块
```

#### 完整代码（Blunt_Feeling）
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=200050;
int n,k,h[maxn],sum[maxn],Min=0x3f3f3f3f,Max=0,tot[maxn],ans=0;

int main() {
    cin>>n>>k;
    for(int i=1; i<=n; i++) {
        int a; cin>>a;
        h[a]++;
        Min=min(Min,a); 
        Max=max(Max,a);
    }
    for(int i=Max; i>=Min; i--) sum[i]=sum[i+1]+h[i];
    int tot=0;
    for(int i=Max; i>=Min; i--) {
        if(tot+sum[i]>k) ans++, tot=0;
        tot += sum[i];
    }
    if(tot>0) ans++;
    cout<<ans<<endl;
    return 0;
}
```

---

### 同类题目与推荐

1. **P1090 合并果子**（贪心+优先队列，每次合并最小两堆）  
2. **P5019 铺设道路**（分层贪心，计算填平次数）  
3. **P1223 排队接水**（排序贪心，最小化总等待时间）  

---

### 可视化与游戏化设计

1. **贪心动画**：  
   - **Canvas 绘制**：塔的像素高度随切割动态下降，当前处理层高亮。  
   - **步进控制**：按钮控制切割步骤，显示当前累加值和切割次数。  
   - **音效触发**：切割时播放 "8-bit 刀切" 音效，背景音乐循环。  

2. **复古游戏要素**：  
   - **积分系统**：每次切割得分=当前层数，连击加分。  
   - **AI 演示**：自动播放模式展示最优切割路径。  

---

### 个人心得摘录

- **Blunt_Feeling**：在第六个测试点因未处理剩余方块导致 WA，强调边界检查的重要性。  
- **MY_Lee**：通过差分将暴力 O(nh) 优化至线性，验证了“暴力碾标算”的可能性。  
- **Z_drj**：尝试线段树+二分但复杂度较高，最终回归分层贪心的简洁性。  

---

**总结**：本题核心在于将问题转化为分层累加，通过预处理优化计算，贪心策略的关键是及时切割并处理剩余值。

---
处理用时：88.01秒