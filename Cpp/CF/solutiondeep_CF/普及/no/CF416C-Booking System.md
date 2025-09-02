# 题目信息

# Booking System

## 题目描述

Innovation technologies are on a victorious march around the planet. They integrate into all spheres of human activity!

A restaurant called "Dijkstra's Place" has started thinking about optimizing the booking system.

There are $ n $ booking requests received by now. Each request is characterized by two numbers: $ c_{i} $ and $ p_{i} $ — the size of the group of visitors who will come via this request and the total sum of money they will spend in the restaurant, correspondingly.

We know that for each request, all $ c_{i} $ people want to sit at the same table and are going to spend the whole evening in the restaurant, from the opening moment at 18:00 to the closing moment.

Unfortunately, there only are $ k $ tables in the restaurant. For each table, we know $ r_{i} $ — the maximum number of people who can sit at it. A table can have only people from the same group sitting at it. If you cannot find a large enough table for the whole group, then all visitors leave and naturally, pay nothing.

Your task is: given the tables and the requests, decide which requests to accept and which requests to decline so that the money paid by the happy and full visitors was maximum.

## 样例 #1

### 输入

```
3
10 50
2 100
5 30
3
4 6 9
```

### 输出

```
2 130
2 1
3 2
```

# AI分析结果



# 题目内容重写（中文）
## 题目名称：订餐系统

### 题目描述
创新技术正在席卷全球，渗透到人类活动的各个领域！  
名为"Dijkstra's Place"的餐厅开始考虑优化订餐系统。  

现有 $n$ 个订餐请求，每个请求有两个参数：$c_i$（顾客人数）和 $p_i$（消费总金额）。所有顾客必须坐在同一张桌子且从18:00待到闭店。  

餐厅共有 $k$ 张桌子，每张桌子有容量 $r_i$。若无法提供足够大的桌子，该请求将被拒绝且无收益。  

任务：选择接受的请求，使总收益最大化。

### 输入样例
```
3
10 50
2 100
5 30
3
4 6 9
```

### 输出样例
```
2 130
2 1
3 2
```

---

**算法分类**：贪心

---

### 题解综合分析
#### 核心思路
所有题解均采用贪心策略：
1. **双重排序**：将订餐请求按金额降序（同金额时人数升序）排序，桌子按容量升序排序
2. **贪心匹配**：为每个请求分配最小的可用桌子，确保高收益请求优先占用最小必要资源

#### 难点对比
- **正确性证明**：需理解局部最优（优先处理高金额请求）能推导出全局最优
- **数据结构选择**：部分题解使用`multiset`优化查找（如Ryder00的题解），但多数采用双重循环暴力匹配（数据规模较小时可行）

---

### 精选题解（评分≥4星）
#### 1. 作者：skyskyCCC（★★★★☆）
**亮点**：
- 结构体设计清晰，包含原始序号标记
- 注释明确解释排序逻辑和标记逻辑
```cpp
// 请求排序：金额降序，同金额时人数升序
bool cmp1(node x,node y){
    return (x.p==y.p)?x.c<y.c:x.p>y.p;
}
// 桌子排序：容量升序
bool cmp2(node2 x,node2 y){
    return x.lag<y.lag;
}
// 核心匹配逻辑（双重循环）
for(int i=1;i<=n;i++){
    for(int j=1;j<=k;j++){
        if(桌子未使用 && 容量足够){
            标记占用并累加收益
            break; // 关键：分配后立即跳出
        }
    }
}
```

#### 2. 作者：feiji_code（★★★★☆）
**亮点**：
- 变量命名直观（如`b`表示桌子占用标记）
- 输出处理时直接遍历原数组，保持原始顺序
```cpp
// 输出时按原请求顺序遍历
for(int i=1;i<=n;i++){
    if(a[i].b==1){
        cout<<a[i].id<<" "<<a[i].num<<endl;
    }
}
```

---

### 最优技巧总结
**关键实现技巧**：
1. **复合排序**：`sort(a+1,a+1+n, [](...){ return p降序 || (p等 && c升序); })`
2. **最小资源占用**：对排序后的桌子使用线性扫描找首个可用
3. **原位标记**：直接在结构体中标记桌子和请求的占用状态

---

### 拓展思考
**同类问题**：
- 区间调度问题（选择不重叠区间使数量最多）
- 资源分配问题（如P1209 [USACO1.3]修理牛棚）

**推荐练习**：
1. P1209 [USACO1.3]修理牛棚（贪心+区间处理）
2. P1230 智力大冲浪（带截止时间的任务调度）
3. P2240 【深基12.例1】部分背包问题（分数背包贪心）

---

### 题解心得摘录
- **feiji_code**："刚开始我看成 DP 了" → 强调审题时明确问题类型的重要性
- **Ryder00**：使用`multiset`优化查找，体现数据结构选择对效率的影响
- **Ag2WO4**（Python解）：通过预分组桌子减少重复计算，展示预处理思路

---
处理用时：43.83秒