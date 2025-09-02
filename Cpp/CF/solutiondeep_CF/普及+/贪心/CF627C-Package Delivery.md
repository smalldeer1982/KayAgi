# 题目信息

# Package Delivery

## 题目描述

Johnny drives a truck and must deliver a package from his hometown to the district center. His hometown is located at point $ 0 $ on a number line, and the district center is located at the point $ d $ .

Johnny's truck has a gas tank that holds exactly $ n $ liters, and his tank is initially full. As he drives, the truck consumes exactly one liter per unit distance traveled. Moreover, there are $ m $ gas stations located at various points along the way to the district center. The $ i $ -th station is located at the point $ x_{i} $ on the number line and sells an unlimited amount of fuel at a price of $ p_{i} $ dollars per liter. Find the minimum cost Johnny must pay for fuel to successfully complete the delivery.

## 说明/提示

In the first sample, Johnny's truck holds $ 4 $ liters. He can drive $ 3 $ units to the first gas station, buy $ 2 $ liters of gas there (bringing the tank to $ 3 $ liters total), drive $ 3 $ more units to the third gas station, buy $ 4 $ liters there to fill up his tank, and then drive straight to the district center. His total cost is $ 2·5+4·3=22 $ dollars.

In the second sample, there is no way for Johnny to make it to the district center, as his tank cannot hold enough gas to take him from the latest gas station to the district center.

## 样例 #1

### 输入

```
10 4 4
3 5
5 8
6 3
8 4
```

### 输出

```
22
```

## 样例 #2

### 输入

```
16 5 2
8 2
5 1
```

### 输出

```
-1
```

# AI分析结果



# Package Delivery

## 题目描述

Johnny 驾驶一辆卡车，需要从家乡（数轴上的点 $0$）运送包裹到地区中心（数轴上的点 $d$）。卡车的油箱容量为 $n$ 升，初始时油箱是满的。每行驶一单位距离消耗一升油。途中有 $m$ 个加油站，第 $i$ 个加油站位于点 $x_i$，油价为每升 $p_i$ 美元。求完成运送的最小油费，若无法到达输出 $-1$。

## 样例 #1

### 输入
```
10 4 4
3 5
5 8
6 3
8 4
```

### 输出
```
22
```

## 样例 #2

### 输入
```
16 5 2
8 2
5 1
```

### 输出
```
-1
```

---

### 综合分析与结论

**核心思路**：贪心策略结合单调栈预处理。对每个加油站，预处理找到后续第一个油价更低的加油站，并在当前加油站选择最优加油量（刚好到达目标站或加满）。时间复杂度 $O(m \log m)$，适用于大数据范围。

---

### 精选题解分析

#### 题解 1：jdsb（★★★★★）
**关键亮点**：
1. **单调栈预处理** $O(m)$ 时间找到每个加油站的下一个低价站。
2. **全局变量隐式初始化**原点为虚拟加油站（$x=0,p=0$），简化边界处理。
3. **终点虚拟化**将终点视为价格为负的加油站，统一处理逻辑。

**代码核心**：
```cpp
// 预处理单调栈找后续最低价站
a[m+1] = {d, -1}; // 终点虚拟化
st[++top] = m+1;
for (int i=m; i>=0; i--) {
    while (top && a[st[top]].p > a[i].p) top--;
    nxt[i] = st[top];
    st[++top] = i;
}

// 贪心计算油量
int res = n; // 当前剩余油量
for (int i=0; i<=m; i++) {
    int dis = max(0, min(a[nxt[i]].x - a[i].x, n) - res);
    ans += 1ll * dis * a[i].p;
    res -= a[i+1].x - a[i].x - dis; // 更新剩余油量
    if (res < 0) return puts("-1"),0;
}
```

#### 题解 2：wuyixiang（★★★★）
**关键亮点**：
1. **优先队列动态维护**当前可达范围内的最低油价。
2. **分段处理区间**，将长距离拆分为多个最优覆盖区间。

**代码核心**：
```cpp
priority_queue<node> q;
q.push({0,0}); // 初始原点
for (int i=1; i<=m+1; i++) {
    int maxx = a[i-1].x;
    // 处理队列中无法覆盖当前区间的加油站
    while (!q.empty() && a[i].x - q.top().x > n) {
        ans += max(q.top().x + n - maxx, 0LL) * q.top().p;
        maxx = max(maxx, q.top().x + n);
        q.pop();
    }
    if (q.empty()) { /* 无解处理 */ }
    ans += (a[i].x - maxx) * q.top().p; // 计算剩余区间
    q.push({a[i].x, a[i].p});
}
```

#### 题解 3：run_away（★★★★）
**关键亮点**：
1. **代码简洁**，逻辑与题解1一致。
2. **结构体排序**与题解1相同，但代码更紧凑。

---

### 关键技巧总结
1. **虚拟终点**：将终点视为特殊加油站，统一处理逻辑。
2. **隐式原点处理**：利用全局变量初始化为原点（$x=0,p=0$）。
3. **单调栈预处理**：快速找到后续最优加油点。
4. **贪心决策**：在低价站尽可能多加油，高价站仅补充必要量。

---

### 拓展练习
1. [P1016 旅行家的预算](https://www.luogu.com.cn/problem/P1016)  
2. [CF767E Change-Free](https://codeforces.com/problemset/problem/767/E)  
3. [P3488 [POI2009]LYZ-Ice Skates](https://www.luogu.com.cn/problem/P3488)

---
处理用时：256.04秒