# 题目信息

# Parking Lot

## 题目描述

Nowadays it is becoming increasingly difficult to park a car in cities successfully. Let's imagine a segment of a street as long as $ L $ meters along which a parking lot is located. Drivers should park their cars strictly parallel to the pavement on the right side of the street (remember that in the country the authors of the tasks come from the driving is right side!). Every driver when parking wants to leave for themselves some extra space to move their car freely, that's why a driver is looking for a place where the distance between his car and the one behind his will be no less than $ b $ meters and the distance between his car and the one in front of his will be no less than $ f $ meters (if there's no car behind then the car can be parked at the parking lot segment edge; the same is true for the case when there're no cars parked in front of the car). Let's introduce an axis of coordinates along the pavement. Let the parking lot begin at point 0 and end at point $ L $ . The drivers drive in the direction of the coordinates' increasing and look for the earliest place (with the smallest possible coordinate) where they can park the car. In case there's no such place, the driver drives on searching for his perfect peaceful haven. Sometimes some cars leave the street and free some space for parking. Considering that there never are two moving cars on a street at a time write a program that can use the data on the drivers, entering the street hoping to park there and the drivers leaving it, to model the process and determine a parking lot space for each car.

## 样例 #1

### 输入

```
30 1 2
6
1 5
1 4
1 5
2 2
1 5
1 4
```

### 输出

```
0
6
11
17
23
```

## 样例 #2

### 输入

```
30 1 1
6
1 5
1 4
1 5
2 2
1 5
1 4
```

### 输出

```
0
6
11
17
6
```

## 样例 #3

### 输入

```
10 1 1
1
1 12
```

### 输出

```
-1
```

# AI分析结果



### 题目重写
# 停车场

## 题目描述

现代城市停车难度日益增加。假设某街道有长度为 $ L $ 米的停车带，车辆必须严格平行于道路右侧停放。每辆车停车时需要满足：与前车保持至少 $ f $ 米间距，与后车保持至少 $ b $ 米间距（若无前车/后车则允许贴边停放）。车辆按坐标递增方向行驶，选择满足条件且坐标最小的位置停放。若无法停放则离开。车辆可能随时离开，同一时刻仅有一辆移动车辆。要求模拟停车过程并输出每辆车的停放位置。

## 样例 #1

### 输入
（同原题）

## 样例 #2

### 输入
（同原题）

## 样例 #3

### 输入
（同原题）

---

### 算法分类
模拟

---

### 题解对比与结论

#### 核心思路对比
1. **暴力扫描**：直接维护占用标记数组，每次线性扫描所有可能位置。时间复杂度 $O(nL)$，适合小数据。
2. **有序映射（map）**：用有序结构维护已停车辆的区间边界，通过遍历相邻区间寻找可用空间。时间复杂度 $O(n^2)$，但实际效率较高。
3. **线段树**：维护最大连续空区间长度，支持快速查询和更新。时间复杂度 $O(n \log L)$，适合大数据量。

#### 最优思路
使用有序映射（map）维护车辆区间，通过插入虚拟边界点简化计算，遍历相邻区间检查可用空间。该方法在代码简洁度与时间复杂度之间取得最佳平衡。

---

### 精选题解

#### 1. 作者：May_Cry_（⭐⭐⭐⭐⭐）
**关键亮点**：  
- 利用 map 的有序特性快速维护车辆区间
- 插入虚拟边界点 (-b, -b) 和 (L+f, L+f) 简化边界判断
- 遍历相邻区间检查间距，逻辑清晰简洁

**核心代码**：
```cpp
map<int, int> mp;
int a[100000]; // 记录每辆车的起点

// 停车逻辑核心部分
for (auto last = mp.begin(), t = ++mp.begin(); t != mp.end(); ++t, ++last) {
    if (t->first - last->second >= x + b + f) {
        a[cnt] = last->second + b;
        mp[a[cnt]] = a[cnt] + x; // 记录终点
        break;
    }
}
```

#### 2. 作者：Last_kiss_Snow_Dog6（⭐⭐⭐⭐）
**关键亮点**：  
- 线段树维护最大可用区间长度
- 通过扩展区间 (L+b+f) 处理边界条件
- 分情况处理靠边停车和中间停车

**核心代码**：
```cpp
// 线段树节点定义
struct _Tree {
    int len, lmax, rmax, amax, lazy;
};

// 查询可用区间
int query(int tn, int l, int r, int len) {
    if (tree[tn].amax < len) return -1;
    if (l == r) return l;
    // ... 递归查询左右子树
}

// 更新停车状态
void update(int tn, int l, int r, int x, int y, int flg) {
    if (x <= l && r <= y) {
        tree[tn].lazy = flg; // 标记为占用/释放
        // ... 更新区间信息
    }
    // ... 递归更新子树
}
```

---

### 关键思路总结
1. **边界处理技巧**：插入虚拟车辆 (-b, -b) 和 (L+f, L+f) 消除边界特判。
2. **区间合并思想**：通过维护有序区间集合，快速判断相邻区间的可用空间。
3. **操作时间复杂度控制**：根据数据规模选择暴力（小数据）或线段树（大数据）。

---

### 拓展思考
类似问题可抽象为区间动态维护问题，常见变式包括：
1. 支持区间合并/分裂的数据结构（如并查集）
2. 带权区间的资源分配（如会议室预定）

---

### 推荐习题
1. [P2161 会场预约](https://www.luogu.com.cn/problem/P2161)  
   （区间维护与合并）
2. [P1904 天际线问题](https://www.luogu.com.cn/problem/P1904)  
   （区间扫描与状态维护）
3. [P2894 酒店](https://www.luogu.com.cn/problem/P2894)  
   （线段树维护最大连续区间）

---
处理用时：145.71秒