# 题目信息

# Marathon

## 题目描述

Valera takes part in the Berland Marathon. The marathon race starts at the stadium that can be represented on the plane as a square whose lower left corner is located at point with coordinates $ (0,0) $ and the length of the side equals $ a $ meters. The sides of the square are parallel to coordinate axes.

As the length of the marathon race is very long, Valera needs to have extra drink during the race. The coach gives Valera a bottle of drink each $ d $ meters of the path. We know that Valera starts at the point with coordinates $ (0,0) $ and runs counter-clockwise. That is, when Valera covers $ a $ meters, he reaches the point with coordinates $ (a,0) $ . We also know that the length of the marathon race equals $ nd+0.5 $ meters.

Help Valera's coach determine where he should be located to help Valera. Specifically, determine the coordinates of Valera's positions when he covers $ d,2·d,...,n·d $ meters.

## 样例 #1

### 输入

```
2 5
2
```

### 输出

```
1.0000000000 2.0000000000
2.0000000000 0.0000000000
```

## 样例 #2

### 输入

```
4.147 2.8819
6
```

### 输出

```
2.8819000000 0.0000000000
4.1470000000 1.6168000000
3.7953000000 4.1470000000
0.9134000000 4.1470000000
0.0000000000 2.1785000000
0.7034000000 0.0000000000
```

# AI分析结果



# Marathon (马拉松)

## 题目描述

Valera 参加伯兰马拉松。马拉松赛道在平面上表示为一个边长为 $a$ 米的正方形，左下角坐标为 $(0,0)$，各边平行于坐标轴。Valera 从 $(0,0)$ 出发逆时针绕行。每当 Valera 跑完 $d$ 米时，教练需要给他送饮料。已知总赛程为 $nd+0.5$ 米，求每次跑完 $d, 2d,..., nd$ 米时的坐标。

## 样例 #1

### 输入
```
2 5
2
```

### 输出
```
1.0000000000 2.0000000000
2.0000000000 0.0000000000
```

## 样例 #2

### 输入
```
4.147 2.8819
6
```

### 输出
```
2.8819000000 0.0000000000
4.1470000000 1.6168000000
3.7953000000 4.1470000000
0.9134000000 4.1470000000
0.0000000000 2.1785000000
0.7034000000 0.0000000000
```

---

**算法分类**：模拟

---

### 题解分析与结论

题目核心是模拟逆时针绕行的路径，计算每次跑完 $d$ 米的坐标。关键点在于处理绕圈时的方向切换和剩余距离计算。

---

#### 题解评分与亮点（4星）

**题解作者**：aeiouaoeiu  
**关键思路**：  
1. 用 `pos` 表示当前所处的边（0-3对应四条边），`l` 表示当前边上累计的距离。  
2. 每次增加距离 $d$ 后，若 `l > a`，计算跨越边的次数，更新 `pos` 并计算剩余距离。  
3. 根据最终 `pos` 和剩余距离，按边计算坐标。

**代码亮点**：  
- 通过整数除法和取模快速计算方向切换次数。  
- 坐标计算公式简洁，直接对应各边情况。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    l += d;
    if(l>a) {
        ll steps = (ll)(l/a);
        pos = (pos + steps) % 4;
        l -= steps * a;
    }
    // 根据 pos 计算坐标
}
```

---

### 最优思路总结

**关键技巧**：  
1. **方向切换计算**：利用 `l/a` 的整数部分确定跨边次数，通过取模4实现循环方向。  
2. **余数处理**：将累计距离转化为当前边的剩余距离，避免复杂路径计算。  
3. **坐标映射**：根据方向 `pos` 直接推导坐标，无需维护全局位置。

**同类问题拓展**：  
- 环形路径问题（如蚂蚁离开网格后的坐标计算）。  
- 周期运动中的位置推算（如钟表指针位置）。

---

### 推荐习题
1. [P1510 方格取数](https://www.luogu.com.cn/problem/P1510)  
   - 涉及路径模拟与动态规划结合。
2. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)  
   - 坐标覆盖问题，逆向模拟判断。
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)  
   - 路径统计与贪心选择，需要处理坐标轴上的移动。

---
处理用时：193.39秒