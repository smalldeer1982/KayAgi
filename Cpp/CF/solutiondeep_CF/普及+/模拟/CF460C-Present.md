# 题目信息

# Present

## 题目描述

Little beaver is a beginner programmer, so informatics is his favorite subject. Soon his informatics teacher is going to have a birthday and the beaver has decided to prepare a present for her. He planted $ n $ flowers in a row on his windowsill and started waiting for them to grow. However, after some time the beaver noticed that the flowers stopped growing. The beaver thinks it is bad manners to present little flowers. So he decided to come up with some solutions.

There are $ m $ days left to the birthday. The height of the $ i $ -th flower (assume that the flowers in the row are numbered from $ 1 $ to $ n $ from left to right) is equal to $ a_{i} $ at the moment. At each of the remaining $ m $ days the beaver can take a special watering and water $ w $ contiguous flowers (he can do that only once at a day). At that each watered flower grows by one height unit on that day. The beaver wants the height of the smallest flower be as large as possible in the end. What maximum height of the smallest flower can he get?

## 说明/提示

In the first sample beaver can water the last 3 flowers at the first day. On the next day he may not to water flowers at all. In the end he will get the following heights: \[2, 2, 2, 3, 2, 2\]. The smallest flower has height equal to 2. It's impossible to get height 3 in this test.

## 样例 #1

### 输入

```
6 2 3
2 2 2 2 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2 5 1
5 8
```

### 输出

```
9
```

# AI分析结果



### 题目内容重写

# 礼物

## 题目描述  
小海狸是一名编程新手，因此信息学是他最喜欢的科目。不久他的信息学老师将要过生日，小海狸决定为她准备一份礼物。他在窗台上种了一排 $n$ 朵花，等待它们生长。然而过了一段时间，他发现花朵停止生长了。小海狸认为送矮小的花不太礼貌，于是想出了一个解决方案。

距离生日还有 $m$ 天。当前第 $i$ 朵花（假设花从左到右编号为 $1$ 到 $n$）的高度为 $a_i$。在剩余的 $m$ 天里，小海狸每天可以使用特殊浇水方式，给连续的 $w$ 朵花浇水（每天只能操作一次）。被浇水的花朵当天高度会增加 $1$。小海狸希望最终最矮花朵的高度尽可能大。请问最终最矮花朵的最大可能高度是多少？

## 输入格式  
第一行三个整数 $n,m,w$  
第二行 $n$ 个整数表示初始高度 $a_i$  

## 输出格式  
一个整数表示答案  

## 样例  
### 样例1  
输入：  
6 2 3  
2 2 2 2 1 1  
输出：  
2  

### 样例2  
输入：  
2 5 1  
5 8  
输出：  
9  

---

### 题解综合分析

#### 核心算法共识  
所有题解均采用二分答案框架，验证最小高度可行性时主要分为两类优化方法：
1. **差分数组法**（4篇）：通过维护差分数组实现区间加减的O(1)操作，总体时间复杂度O(n logA)
2. **线段树/树状数组法**（3篇）：直接维护区间修改，时间复杂度O(n logn logA)或更高

#### 最优思路提炼  
**二分答案 + 差分数组** 是最优解：
1. 二分上下界设为 [min(a_i), min(a_i)+m]
2. 验证时从左到右扫描，对每个需要补足高度的位置，用差分数组记录区间浇水操作
3. 通过维护当前累计浇水量，保证每个位置的计算为O(1)

#### 关键实现技巧  
1. **差分边界处理**：当浇水区间超过n时只需修改左端点（右端点不处理）
2. **滚动累计值**：用变量跟踪当前位置的实际高度，避免重复计算前缀和
3. **早停机制**：当总操作天数超过m时立即返回失败

---

### 精选题解

#### 1. YuRuiH_（⭐⭐⭐⭐⭐）  
**核心亮点**：  
- 差分数组实现简洁高效，代码仅30行  
- 正确处理区间越界情况  
- 使用位运算加速二分过程  

**关键代码**：  
```cpp
bool can(int s){
    int a=0, b=m;
    memset(need,0,sizeof(need));
    for(int i=1;i<=n;i++){
        if(i>=w) a -= need[i-w]; // 移除过期区间的浇水量
        need[i] = max(0, s - a - f[i]); // 计算当前需要浇水的天数
        a += need[i];
        b -= need[i];
        if(b<0) return false;
    }
    return true;
}
```

#### 2. Sol1（⭐⭐⭐⭐）  
**独特贡献**：  
- 详细注释差分数组的维护逻辑  
- 强调重新初始化差分数组的重要性  
- 提供可视化调试的printf示例  

**调试心得**：  
> "每次二分后都要将差分数组重新赋值，因为上一次验证可能修改了数组"

#### 3. Karry5307（⭐⭐⭐⭐）  
**创新点**：  
- 将操作次数直接存储在差分数组  
- 使用min(n,i+w)处理边界更直观  
- 分离前缀和计算与浇水操作  

**核心片段**：  
```cpp
for(int i=1;i<=n-w+1;i++){
    c += diff[i];
    if(cur>0 && c<mid){
        int add = min(cur, mid-c);
        diff[i] += add;
        diff[i+w] -= add;
        cur -= add;
        c += add;
    }
}
```

---

### 拓展训练  
1. **P1873 砍树**：二分答案+区间和验证  
2. **P2884 [USACO07MAR]Monthly Expense**：最小化最大值问题  
3. **P2216 [HAOI2007] 理想的正方形**：二维区间最值优化  

---

### 关键代码总结  
**差分验证函数模板**：  
```cpp
bool check(int mid){
    int water = 0, cur_add = 0;
    memset(diff, 0, sizeof(diff));
    
    for(int i=1; i<=n; i++){
        cur_add += diff[i]; // 累计到当前点的浇水量
        int cur_h = a[i] + cur_add;
        
        if(cur_h < mid){
            int need = mid - cur_h;
            water += need;
            if(water > m) return false;
            
            diff[i] += need;        // 区间左端点
            if(i+w <=n) diff[i+w] -= need; // 区间右端点+1
            cur_add += need;        // 更新当前累计值
        }
    }
    return true;
}
```

---
处理用时：60.71秒