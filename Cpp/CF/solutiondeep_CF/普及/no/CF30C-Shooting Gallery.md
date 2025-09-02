# 题目信息

# Shooting Gallery

## 题目描述

One warm and sunny day king Copa decided to visit the shooting gallery, located at the Central Park, and try to win the main prize — big pink plush panda. The king is not good at shooting, so he invited you to help him.

The shooting gallery is an infinite vertical plane with Cartesian coordinate system on it. The targets are points on this plane. Each target is described by it's coordinates $ x_{i} $ , and $ y_{i} $ , by the time of it's appearance $ t_{i} $ and by the number $ p_{i} $ , which gives the probability that Copa hits this target if he aims at it.

A target appears and disappears instantly, so Copa can hit the target only if at the moment $ t_{i} $ his gun sight aimed at $ (x_{i},y_{i}) $ . Speed of movement of the gun sight on the plane is equal to 1. Copa knows all the information about the targets beforehand (remember, he is a king!). He wants to play in the optimal way, which maximizes the expected value of the amount of hit targets. He can aim at any target at the moment 0.

## 样例 #1

### 输入

```
1
0 0 0 0.5
```

### 输出

```
0.5000000000
```

## 样例 #2

### 输入

```
2
0 0 0 0.6
5 0 5 0.7
```

### 输出

```
1.3000000000
```

# AI分析结果



1. 【题目翻译】
# 射击场

## 题目描述

在一个温暖的晴天，Copa 国王决定去中央公园的射击场游玩，并试图赢得大奖——粉色毛绒熊猫玩偶。国王不擅长射击，因此邀请你协助他。

射击场是一个无限垂直平面，采用笛卡尔坐标系。目标以平面上的点形式存在。每个目标由其坐标 $(x_i, y_i)$、出现时间 $t_i$ 和概率值 $p_i$ 描述，其中 $p_i$ 表示当国王在时刻 $t_i$ 将准星对准该坐标时的命中概率。

目标会瞬间出现和消失，因此只有当准星在时刻 $t_i$ 对准 $(x_i, y_i)$ 时才能击中目标。准星在平面上的移动速度为 1 单位/秒。已知所有目标信息，国王希望以最优策略最大化命中目标的期望数量。国王可以在初始时刻 0 将准星对准任意目标。

## 样例 #1

### 输入
```
1
0 0 0 0.5
```

### 输出
```
0.5000000000
```

## 样例 #2

### 输入
```
2
0 0 0 0.6
5 0 5 0.7
```

### 输出
```
1.3000000000
```

---

2. 【算法分类】动态规划

---

3. 【题解对比分析】
各题解均采用以下核心思路：
1. 按时间排序目标，消除时序影响
2. 定义动态规划状态 f[i] 表示必选第 i 个目标时的最大期望
3. 转移时检查能否在时间差内完成位移（平方距离比较优化）
4. 最终取所有状态最大值

共同难点处理：
- 时间差与欧氏距离的比较采用平方运算避免浮点误差
- 状态定义强制包含当前目标，简化转移条件

差异点：
- jdsb 的题解完整说明排序必要性、状态转移逻辑，代码结构清晰
- wangyibo201026 的题解包含状态定义错误修正过程（从二维降为一维）

---

4. 【高星题解推荐】
### jdsb（★★★★☆）
**关键亮点**：
1. 明确说明排序必要性及转移条件数学依据
2. 使用结构体排序提升代码可读性
3. check 函数封装距离比较逻辑

**核心代码**：
```cpp
for(int i=1;i<=n;i++) {
    for(int j=1;j<i;j++) 
        if(check(i,j)) 
            f[i] = max(f[i], f[j]);
    f[i] += a[i].p;
    ans = max(ans, f[i]);
}
```

### XL4453（★★★★☆）
**关键亮点**：
1. 简洁的运算符重载实现排序
2. 数学推导部分简明扼要
3. 采用 long long 避免数值溢出

**代码亮点**：
```cpp
bool dis(int i,int j){
    return (num[i].x-num[j].x)*(num[i].x-num[j].x) 
         + (num[i].y-num[j].y)*(num[i].y-num[j].y)
         <= (num[i].t-num[j].t)*(num[i].t-num[j].t);
}
```

---

5. 【关键思路总结】
- **排序预处理**：按时间排序消除时序限制，转换为序列问题
- **状态压缩**：定义 f[i] 为必须选择第 i 个目标的最优解，通过强制包含当前元素简化转移
- **距离优化**：使用平方比较代替开根运算，避免浮点误差
- **滚动最值**：在状态转移过程中实时维护全局最大值

---

6. 【拓展套路】
类似时序+空间移动约束问题可参考：
1. 时间序列型动态规划（如 P2285 [HNOI2004] 打鼹鼠）
2. 带转移约束的最长序列问题（如 P1944 最长链）
3. 二维平面移动优化问题（如 P1233 木棍加工）

---

7. 【相似题目推荐】
1. P2285 [HNOI2004] 打鼹鼠 - 同类时序移动问题
2. P1944 最长链 - 带距离约束的序列DP 
3. P1233 木棍加工 - 二维排序与序列选择

---

8. 【个人心得摘录】
> "期望的可加性让问题简化为求最大概率和" —— tZEROちゃん  
> "用平方比较避免开根，这是处理几何距离的常用技巧" —— jdsb  
> "定义状态时必须包含当前元素，否则无法确定枪口位置" —— wangyibo201026

---
处理用时：55.05秒