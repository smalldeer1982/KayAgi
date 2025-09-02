# 题目信息

# [USACO07NOV] Sunscreen G

## 题目描述

To avoid unsightly burns while tanning, each of the C (1 ≤ C ≤ 2500) cows must cover her hide with sunscreen when they're at the beach. Cow i has a minimum and maximum SPF rating (1 ≤ minSPFi ≤ 1,000; minSPFi ≤ maxSPFi ≤ 1,000) that will work. If the SPF rating is too low, the cow suffers sunburn; if the SPF rating is too high, the cow doesn't tan at all........

The cows have a picnic basket with L (1 ≤ L ≤ 2500) bottles of sunscreen lotion, each bottle i with an SPF rating SPFi (1 ≤ SPFi ≤ 1,000). Lotion bottle i can cover coveri cows with lotion. A cow may lotion from only one bottle.

What is the maximum number of cows that can protect themselves while tanning given the available lotions?

有C个奶牛去晒太阳 (1 <=C <= 2500)，每个奶牛各自能够忍受的阳光强度有一个最小值和一个最大值，太大就晒伤了，太小奶牛没感觉。

而刚开始的阳光的强度非常大，奶牛都承受不住，然后奶牛就得涂抹防晒霜，防晒霜的作用是让阳光照在身上的阳光强度固定为某个值。

那么为了不让奶牛烫伤，又不会没有效果。

给出了L种防晒霜。每种的数量和固定的阳光强度也给出来了

每个奶牛只能抹一瓶防晒霜，最后问能够享受晒太阳的奶牛有几个。


## 样例 #1

### 输入

```
3 2
3 10
2 5
1 5
6 2
4 1```

### 输出

```
2```

# AI分析结果



# 题解分析与总结

## 算法分类
**无算法分类**  
（核心解法为贪心算法）

---

## 题解思路、算法要点与解决难点

### 核心思路对比
1. **按右端点排序（翼德天尊）**  
   - 将奶牛按 `maxSPF` 升序排序，防晒霜按 `SPF` 升序排序。  
   - **贪心策略**：优先处理右端点小的奶牛，选择最小的可用防晒霜，为后续奶牛保留更大的选择空间。  
   - **正确性证明**：右端点小的奶牛选择范围有限，必须优先满足。

2. **按左端点排序（陷语）**  
   - 将奶牛按 `minSPF` 降序排序，防晒霜按 `SPF` 降序排序。  
   - **贪心策略**：优先处理左端点大的奶牛，选择最大的可用防晒霜，避免大值防晒霜浪费。  
   - **正确性证明**：大 `SPF` 的防晒霜更稀缺，优先满足需求高的奶牛。

3. **网络流（大菜鸡fks）**  
   - 构建源点→防晒霜→奶牛→汇点的网络流模型。  
   - **复杂度问题**：虽然正确但复杂度为 $O(n^2)$，数据规模大时效率低。

### 解决难点
- **贪心正确性证明**：需证明局部最优能推导全局最优。例如，按右端点排序时，若放弃当前奶牛，后续无法获得更优解。
- **排序策略选择**：右端点排序避免大范围奶牛占用小 `SPF`，左端点排序避免大 `SPF` 浪费。

---

## 题解评分（≥4星）

1. **翼德天尊（★★★★☆）**  
   - **亮点**：思路清晰，代码简洁，反例证明直观。  
   - **代码**：30行实现贪心，双重循环逻辑明确。

2. **陷语（★★★★☆）**  
   - **亮点**：详细数学证明，逻辑严谨。  
   - **代码**：结构清晰，变量命名规范。

3. **Kacho（★★★★☆）**  
   - **亮点**：代码可读性强，注释详细。  
   - **优化**：直接暴力枚举，适合小规模数据。

---

## 最优思路提炼

1. **贪心策略核心**  
   - **排序方向**：右端点升序或左端点降序，保证每一步最优选择。  
   - **匹配规则**：当前奶牛选择最小的可用防晒霜（右端点排序）或最大的可用防晒霜（左端点排序）。

2. **实现技巧**  
   - 双重循环暴力匹配，时间复杂度 $O(C \cdot L)$，数据规模 $2500 \times 2500$ 可接受。  
   - 预处理排序后，贪心选择可线性扫描。

---

## 同类型题与算法套路

- **区间覆盖问题**：如 [P1803 活动安排](https://www.luogu.com.cn/problem/P1803)。  
- **资源分配问题**：如 [P1230 智力大冲浪](https://www.luogu.com.cn/problem/P1230)。  
- **贪心排序策略**：如 [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)。

---

## 个人心得摘录

- **翼德天尊**：通过反例证明排序策略的正确性，强调右端点的关键性。  
- **Werner_Yin**：初始贪心策略错误，通过反例分析修正排序方向。  
- **大菜鸡fks**：尝试网络流但因内存限制放弃，体现算法选择的实际考量。

---

## 可视化与算法演示

### 动态规划可视化（贪心策略）
**动画设计**：  
1. **像素风格**：奶牛显示为绿色方块，防晒霜为蓝色圆点，匹配成功时变红。  
2. **Canvas 网格**：横向为 `SPF` 值，纵向为排序后的奶牛和防晒霜。  
3. **音效触发**：匹配成功时播放“叮”声，无可用防晒霜时播放“哔”声。  

**交互设计**：  
- **步进控制**：点击“Next”逐步展示匹配过程。  
- **速度调节**：滑动条控制动画速度（0.5x~3x）。  
- **自动演示**：AI 自动运行，高亮当前奶牛和候选防晒霜。

### 复古游戏化设计
- **8位音效**：背景音乐为 FC 风格循环曲，匹配成功音效为短促“叮咚”。  
- **积分系统**：每匹配一头牛得10分，连续匹配触发连击奖励。  
- **关卡模式**：分为“小规模测试→中等数据→极限数据”三关，逐步提升难度。

---

## 代码实现（贪心策略）

```cpp
// 翼德天尊题解代码（核心逻辑）
#include<bits/stdc++.h>
using namespace std;
int c,l,ans;
struct node{ int a,b; };
node cow[2501],fss[2501];

int cmp(node x,node y){ return x.b<y.b; } // 按右端点升序
int cmp1(node x,node y){ return x.a<y.a; } // 按SPF升序

int main(){
    scanf("%d%d",&c,&l);
    for(int i=1;i<=c;i++) scanf("%d%d",&cow[i].a,&cow[i].b);
    for(int i=1;i<=l;i++) scanf("%d%d",&fss[i].a,&fss[i].b);
    sort(cow+1,cow+c+1,cmp);
    sort(fss+1,fss+l+1,cmp1);
    
    for(int i=1;i<=c;i++){
        for(int j=1;j<=l;j++){
            if(fss[j].b>0 && fss[j].a>=cow[i].a && fss[j].a<=cow[i].b){
                fss[j].b--,ans++;
                break;
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 推荐题目
1. **P1803 活动安排**：区间不相交问题，贪心按结束时间排序。  
2. **P1230 智力大冲浪**：时间与收益的权衡，贪心+优先队列。  
3. **P1094 纪念品分组**：双指针贪心，固定分组策略。

---
处理用时：66.57秒