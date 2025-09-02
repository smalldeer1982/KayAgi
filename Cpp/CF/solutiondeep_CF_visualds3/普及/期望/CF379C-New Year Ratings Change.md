# 题目信息

# New Year Ratings Change

## 题目描述

One very well-known internet resource site (let's call it X) has come up with a New Year adventure. Specifically, they decided to give ratings to all visitors.

There are $ n $ users on the site, for each user we know the rating value he wants to get as a New Year Present. We know that user $ i $ wants to get at least $ a_{i} $ rating units as a present.

The X site is administered by very creative and thrifty people. On the one hand, they want to give distinct ratings and on the other hand, the total sum of the ratings in the present must be as small as possible.

Help site X cope with the challenging task of rating distribution. Find the optimal distribution.

## 样例 #1

### 输入

```
3
5 1 1
```

### 输出

```
5 1 2
```

## 样例 #2

### 输入

```
1
1000000000
```

### 输出

```
1000000000
```

# AI分析结果


### 💡 Kay的C++算法解析：New Year Ratings Change 深入学习指南 💡

#### 题目解读与核心算法识别
✨ **本题主要考察**：贪心算法（排序+递推）  
🗣️ **初步分析**：  
> 这道题就像给朋友分发编号不同的礼物🎁——每个人有最低期望值，我们既要满足期望又要让总编号最小。贪心算法的核心是"当前最优选择"：先处理期望值小的用户，分配最小可用数字。  
> - **核心流程**：排序后遍历，若当前值≤前值则取`前值+1`，否则保留原值  
> - **可视化设计**：用像素方块表示用户期望值，排序后从左到右扫描。冲突时显示红色闪烁+音效，新分配值绿色高亮  
> - **复古元素**：FC红白机风格网格，分配成功时播放《超级玛丽》金币音效，自动演示模式像《贪吃蛇AI》逐步推进  

---

#### 精选优质题解参考
**题解一（fls233666）**  
* **点评**：思路清晰展现排序贪心本质，通过结构体巧妙保留原顺序。代码规范（`ans[p[i].b]`明确），递推逻辑直白易懂，边界处理严谨（首元素特判）。时间复杂度O(n log n)是本题最优解，竞赛可直接使用  

**题解二（zjc5）**  
* **点评**：创新性使用路径压缩（递归版并查集），`mp[x]=find(mp[x])`是亮点。代码极简但可读性稍弱，适合学习高级技巧。注意递归深度可能栈溢出，大数据需改迭代  

**题解三（drop）**  
* **点评**：珍贵展示调试过程（TLE→AC），结构体排序+原地修改的实践典范。`a[i].num=a[i-1].num+1`体现贪心本质，边界处理完整，适合初学者借鉴  

---

#### 核心难点辨析与解题策略
1.  **高效去重分配**  
    * **分析**：暴力检查重复O(n²)超时。贪心解法通过排序将相同值聚集，递推时只需比较前驱值  
    * 💡 **学习笔记**：排序是处理"去重最优化"问题的银弹  

2.  **保持原序输出**  
    * **分析**：需在排序前记录原始下标（如`struct`的`.b`或`pair`），处理结果按原索引存储  
    * 💡 **学习笔记**：涉及顺序保留时，预处理索引是通用技巧  

3.  **证明贪心正确性**  
    * **分析**：若最优解中存在逆序分配（大值用户得较小rating），交换后和更小，矛盾  
    * 💡 **学习笔记**：贪心正确性常通过"交换论证"证明  

### ✨ 解题技巧总结
- **排序预处理**：80%最值问题先排序  
- **结构体索引**：`struct{val, id}`处理需保留顺序的场景  
- **路径压缩**：递归式跳过已用值，空间换时间典范  

---

#### C++核心代码实现赏析
**通用核心实现（综合优化版）**  
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3e5+5;
pair<int, int> arr[MAXN]; // first:期望值, second:原下标
long long ans[MAXN]; // 防溢出

int main() {
    int n; cin >> n;
    for(int i=0; i<n; ++i) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    sort(arr, arr+n);
    
    long long cur = arr[0].first;
    ans[arr[0].second] = cur;
    
    for(int i=1; i<n; ++i) {
        cur = max(cur+1, (long long)arr[i].first);
        ans[arr[i].second] = cur;
    }
    
    for(int i=0; i<n; ++i) 
        cout << ans[i] << " ";
}
```
* **代码解读**：  
  > 1. `pair`同时存储值和原位置  
  > 2. 排序后首元素直接取期望值  
  > 3. 递推核心`cur = max(cur+1, arr[i].first)`保证严格递增  
  > 4. 结果按原下标`ans[second]`存储  

---

#### 算法可视化：像素动画演示
![](https://via.placeholder.com/400x200/000000/FFFFFF?text=贪心算法像素动画示意)  
* **主题**：像素风《贪吃蛇》式贪心分配  
* **关键帧**：  
  1. **初始化**：8-bit风格数字网格，用户期望值用黄色方块表示  
  2. **排序动画**：方块按冒泡排序从左到右重组，伴随"滴滴"音效  
  3. **分配阶段**：  
     - 绿色箭头扫描，当前用户方块闪烁蓝光  
     - 若值≥前值：方块变绿+金币音效  
     - 若冲突：红色闪烁+警报音，显示`cur+1`计算过程  
  4. **路径压缩演示**（可选）：紫色光束连接冲突值，展示跳跃分配  

---

#### 拓展练习与相似问题
1. **洛谷 P1094**：纪念品分组（贪心+双指针）  
   > 巩固"排序后贪心匹配"思想  
2. **洛谷 P1102**：A-B数对（哈希优化去重）  
   > 学习`unordered_map`处理大范围值域  
3. **洛谷 P1605**：迷宫（DFS路径记录）  
   > 训练索引保留技巧的变式应用  

---

#### 学习心得与经验分享
> **drop的调试经验**：  
> *"第一次用map直接查找超时，改用排序递推AC。教训：当n≤3e5时，O(n²)即使逻辑正确也必然TLE"*  
>   
> **Kay总结**：算法复杂度预判是竞赛核心能力，暴力解法后必须思考优化方向  

---

通过本指南，相信大家已掌握贪心算法的精髓。记住：排序预处理+索引保留是解决此类问题的黄金组合！🚀

---
处理用时：74.98秒