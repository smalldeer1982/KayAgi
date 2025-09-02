# 题目信息

# [USACO09DEC] Selfish Grazing S

## 题目描述

Each of Farmer John's N (1 <= N <= 50,000) cows likes to graze in a certain part of the pasture, which can be thought of as a large one-dimeensional number line. Cow i's favorite grazing range starts at location S\_i and ends at location E\_i (1 <= S\_i < E\_i; S\_i < E\_i <= 100,000,000).

Most folks know the cows are quite selfish; no cow wants to share any of its grazing area with another. Thus, two cows i and j can only graze at the same time if either S\_i >= E\_j or E\_i <= S\_j. FJ would like to know the maximum number of cows that can graze at the same time for a given set of cows and their preferences.

Consider a set of 5 cows with ranges shown below:

```cpp
  ... 1    2    3    4    5    6    7    8    9   10   11   12   13 ...
  ... |----|----|----|----|----|----|----|----|----|----|----|----|----
Cow 1:      <===:===>          :              :              :
Cow 2: <========:==============:==============:=============>:
Cow 3:          :     <====>   :              :              :
Cow 4:          :              :     <========:===>          :
Cow 5:          :              :     <==>     :              :
```
These ranges represent (2, 4), (1, 12), (4, 5), (7, 10), and (7, 8), respectively.

For a solution, the first, third, and fourth (or fifth) cows can all graze at the same time. If the second cow grazed, no other cows could graze. Also, the fourth and fifth cows cannot graze together, so it is impossible for four or more cows to graze.

约翰有N(1≤N≤50000)头牛，约翰的草地可以认为是一条直线．每只牛只喜欢在某个特定的范围内吃草．第i头牛喜欢在区间(Si，Ei)吃草，1≤Si<Ei≤1,000,000,00.

奶牛们都很自私，他们不喜欢和其他奶牛共享自己喜欢吃草的领域，因此约翰要保证任意

两头牛都不会共享他们喜欢吃草昀领域．如果奶牛i和奶牛J想要同时吃草，那么要满足：Si>=Ej或者Ei≤Sj．约翰想知道在同一时刻，最多可以有多少头奶牛同时吃草？


## 样例 #1

### 输入

```
5 
2 4 
1 12 
4 5 
7 10 
7 8 
```

### 输出

```
3 
```

# AI分析结果



# 算法分类  
贪心算法  

---

# 题解思路与算法要点  
## 核心思路  
所有题解均采用**按右端点排序+贪心选择**的算法框架，核心步骤：  
1. 将区间按右端点升序排序  
2. 维护当前已选区间的最右端点值，依次遍历排序后的区间  
3. 若当前区间的左端点 >= 已选区间的右端点，则选择该区间并更新右端点  

## 解决难点  
1. **排序依据的推导**：正确性证明需说明为什么按右端点排序能保证最优解  
   - 正确性核心：每次选择结束最早的区间，能为后续保留最多选择空间  
2. **贪心策略验证**：通过反例（如按左端点排序的失败案例）验证策略正确性  
3. **初始值处理**：第一个区间必选，ans初始值为1  

---

# 题解评分（≥4星）  
1. **微香玉烛暗（5星）**  
   完整样例推演 + 代码注释清晰 + 正确性说明  

2. **user48442（4.5星）**  
   详细反例验证排序策略 + 工作类比喻帮助理解  

3. **CloudStroll（4星）**  
   明确对比贪心与DP适用场景 + 推荐同类练习  

---

# 最优思路与技巧提炼  
## 关键技巧  
```cpp
// 结构体排序函数（核心逻辑）
struct Node { int l, r; };
bool cmp(Node a, Node b) { return a.r < b.r; }

// 贪心选择过程
int ans = 1, last = a[1].r;
for(int i=2; i<=n; ++i) {
    if(a[i].l >= last) {
        ans++;
        last = a[i].r;
    }
}
```  
## 思维要点  
1. **区间问题的终局思维**：以结束时间作为决策核心，确保后续选择空间最大化  
2. **贪心策略验证**：通过构造极端样例（如长区间与多个短区间）验证策略正确性  

---

# 同类题型推荐  
1. P1803 凌乱的yyy（同款区间调度模板题）  
2. P2285 打鼹鼠（时间轴上的区间选择）  
3. P2240 部分背包问题（不同形式的贪心策略）  

---

# 可视化算法演示  
## 动画设计方案  
1. **像素风格时间轴**  
   - 使用16色调色板，棕色表示已选区间，绿色表示候选区间  
   - 每个区间显示为水平色块，右端点标注数字  

2. **关键步骤高亮**  
   ![算法演示](https://cdn.luogu.com.cn/upload/image_hosting/4q4kz3e1.gif)  
   - 红色边框标记当前比较的区间  
   - 黄色箭头展示`last`指针移动轨迹  

3. 音效设计  
   - 选择区间时播放"ding"音效（8-bit合成器）  
   - 错误重叠时播放低音警报  

4. 交互功能  
   ```javascript
   // 伪代码示例
   class Animation {
     constructor() {
       this.speed = 1000; // 1秒/步
       this.playMode = 'auto'; // auto|manual
     }
     
     highlightCompare(i, last) {
       // 高亮当前区间与last的比较
     }
   }
   ```

---

# 核心代码实现  
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 50005;
struct Node { int l, r; } a[MAXN];

bool cmp(Node x, Node y) { 
    return x.r < y.r; 
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%d%d", &a[i].l, &a[i].r);
    
    sort(a, a+n, cmp);
    
    int ans = 1, last = a[0].r;
    for(int i=1; i<n; ++i) {
        if(a[i].l >= last) {
            ans++;
            last = a[i].r;
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

# 心得摘录  
> "考试时第一反应是DP，但N=5e4的数据量暗示了贪心的存在" —— user48442  
> "重载运算符时把`<`写成`>`，debug两小时才找到问题" —— 星尘_星辰（典型编码陷阱案例）  

---

# 扩展思考  
当区间带权重时（如选区间可得不同分数），需转化为动态规划问题（如P1944）。此时贪心失效，需使用右端点排序+二分查找优化DP。

---
处理用时：57.14秒