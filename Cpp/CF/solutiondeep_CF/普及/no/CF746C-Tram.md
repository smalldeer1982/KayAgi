# 题目信息

# Tram

## 题目描述

The tram in Berland goes along a straight line from the point $ 0 $ to the point $ s $ and back, passing $ 1 $ meter per $ t_{1} $ seconds in both directions. It means that the tram is always in the state of uniform rectilinear motion, instantly turning around at points $ x=0 $ and $ x=s $ .

Igor is at the point $ x_{1} $ . He should reach the point $ x_{2} $ . Igor passes $ 1 $ meter per $ t_{2} $ seconds.

Your task is to determine the minimum time Igor needs to get from the point $ x_{1} $ to the point $ x_{2} $ , if it is known where the tram is and in what direction it goes at the moment Igor comes to the point $ x_{1} $ .

Igor can enter the tram unlimited number of times at any moment when his and the tram's positions coincide. It is not obligatory that points in which Igor enter and exit the tram are integers. Assume that any boarding and unboarding happens instantly. Igor can move arbitrary along the line (but not faster than $ 1 $ meter per $ t_{2} $ seconds). He can also stand at some point for some time.

## 说明/提示

In the first example it is profitable for Igor to go by foot and not to wait the tram. Thus, he has to pass $ 2 $ meters and it takes $ 8 $ seconds in total, because he passes $ 1 $ meter per $ 4 $ seconds.

In the second example Igor can, for example, go towards the point $ x_{2} $ and get to the point $ 1 $ in $ 6 $ seconds (because he has to pass $ 3 $ meters, but he passes $ 1 $ meters per $ 2 $ seconds). At that moment the tram will be at the point $ 1 $ , so Igor can enter the tram and pass $ 1 $ meter in $ 1 $ second. Thus, Igor will reach the point $ x_{2} $ in $ 7 $ seconds in total.

## 样例 #1

### 输入

```
4 2 4
3 4
1 1
```

### 输出

```
8
```

## 样例 #2

### 输入

```
5 4 0
1 2
3 1
```

### 输出

```
7
```

# AI分析结果



# Tram

## 题目描述

在伯兰的直线轨道上，电车在点 $0$ 到点 $s$ 之间往返运行，每移动 1 米耗时 $t_1$ 秒。伊戈尔需要从点 $x_1$ 到达点 $x_2$，步行速度为每米 $t_2$ 秒。已知电车初始位置为 $p$，方向为 $d$（$d=1$ 表示向右，$d=-1$ 向左），求伊戈尔到达终点的最短时间。他可以在任何与电车位置重合时上下车，上下车时间不计。

## 输入输出样例

### 样例 #1
输入：
```
4 2 4
3 4
1 1
```
输出：
```
8
```

### 样例 #2
输入：
```
5 4 0
1 2
3 1
```
输出：
```
7
```

---

**算法分类**  
模拟

---

## 题解分析与结论

### 题解综合对比
1. **封禁用户题解（4星）**  
   - **关键思路**：分两种情况比较：直接步行时间 vs 电车到达终点时间（覆盖起点的情况）。  
   - **亮点**：通过方向判断和分段计算，精准处理电车往返路径。  
   - **代码实现**：分方向讨论电车运动轨迹，计算首次覆盖起点时的终点到达时间。  

### 最优思路提炼
1. **直接步行**：时间计算为 $|x_2 - x_1| \cdot t_2$。
2. **电车方案**：计算电车到达终点的时间，确保路径覆盖起点 $x_1$。根据电车初始方向和位置，分以下情况：
   - 电车方向与目标终点方向一致时直接计算。
   - 方向相反时需计算掉头后的总时间。
3. **取最小值**：比较两种方案时间，取较小值。

### 核心代码实现
```cpp
int main(){
    int s, x1, x2, t1, t2, p, d;
    cin >> s >> x1 >> x2 >> t1 >> t2 >> p >> d;
    int ans = abs(x1 - x2) * t2; // 直接步行时间
    int t = 0, ok = 0;
    
    if (p != x2) { // 电车未在终点时计算
        if (p < x2) {
            t = (x2 - p) * t1;
            if (d == -1) { // 电车需先掉头
                t += p * 2 * t1;
                d = 1;
                if (x1 <= x2) ok = 1;
            } else {
                if (x1 <= x2 && p <= x1) ok = 1;
            }
        } else {
            t = (p - x2) * t1;
            if (d == 1) { // 电车需先掉头
                t += (s - p) * 2 * t1;
                d = -1;
                if (x1 >= x2) ok = 1;
            } else {
                if (x1 >= x2 && x1 <= p) ok = 1;
            }
        }
    }
    
    if (ok) ans = min(ans, t);
    else { // 需要额外往返的情况
        if ((x2 - x1) * d > 0) t += 2 * s * t1;
        else t += (x2 < x1) ? (s - x2) * 2 : x2 * 2;
        ans = min(ans, t);
    }
    cout << ans;
}
```

### 拓展与相似题目
1. **CF746B**（模拟运动路径）  
2. **洛谷P1515**（时间最优决策）  
3. **CF723A**（坐标点选择与运动模拟）

---
处理用时：277.47秒