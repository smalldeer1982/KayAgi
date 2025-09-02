# 题目信息

# Three Base Stations

## 题目描述

The New Vasjuki village is stretched along the motorway and that's why every house on it is characterized by its shift relative to some fixed point — the $ x_{i} $ coordinate. The village consists of $ n $ houses, the $ i $ -th house is located in the point with coordinates of $ x_{i} $ .

TELE3, a cellular communication provider planned to locate three base stations so as to provide every house in the village with cellular communication. The base station having power $ d $ located in the point $ t $ provides with communication all the houses on the segment $ [t-d,t+d] $ (including boundaries).

To simplify the integration (and simply not to mix anything up) all the three stations are planned to possess the equal power of $ d $ . Which minimal value of $ d $ is enough to provide all the houses in the village with cellular communication.

## 样例 #1

### 输入

```
4
1 2 3 4
```

### 输出

```
0.500000
1.500000 2.500000 3.500000
```

## 样例 #2

### 输入

```
3
10 20 30
```

### 输出

```
0
10.000000 20.000000 30.000000
```

## 样例 #3

### 输入

```
5
10003 10004 10001 10002 1
```

### 输出

```
0.500000
1.000000 10001.500000 10003.500000
```

# AI分析结果



# Three Base Stations

## 题目描述

New Vasjuki 村庄沿高速公路延伸，因此每个房屋的位置由其相对于某个固定点的偏移量坐标 $x_i$ 表示。村庄共有 $n$ 座房屋，第 $i$ 座房屋位于坐标 $x_i$ 处。

通信公司 TELE3 计划建造三个基站，每个基站的功率相同为 $d$。位于位置 $t$ 的基站能覆盖区间 $[t-d, t+d]$（含边界）。求能覆盖所有房屋的最小 $d$，并输出对应的三个基站中心坐标。

## 输入输出样例

### 样例 #1
输入：
```
4
1 2 3 4
```
输出：
```
0.500000
1.500000 2.500000 3.500000
```

### 样例 #2
输入：
```
3
10 20 30
```
输出：
```
0
10.000000 20.000000 30.000000
```

---

## 算法分类
**二分**

---

## 题解分析与结论

### 核心思路
1. **二分答案**：通过二分法确定最小半径 $d$。
2. **贪心验证**：每次检查当前 $d$ 是否可行时，采用贪心策略：将每个基站尽可能设置在能覆盖最左侧未覆盖点的最右位置，以最大化覆盖范围。若最终使用不超过三个基站即可覆盖所有点，则 $d$ 可行。

### 解决难点
- **浮点精度处理**：二分时需设置足够小的精度（如 $10^{-7}$），避免精度误差。
- **基站位置保存**：在验证过程中需记录每个基站的位置，确保输出正确。

---

## 精选题解

### 题解1：TheSky233（⭐⭐⭐⭐⭐）
**关键亮点**：
- 代码结构清晰，正确处理浮点精度和答案保存。
- 贪心策略简洁高效，每次检查时间复杂度为 $O(n)$。
- 通过全局变量保存最优基站位置，确保输出正确。

**核心代码**：
```cpp
bool check(double k) {
    int cnt = 1;
    tmp[1] = a[1] + k;
    for (int i = 2; i <= n; i++) {
        if (a[i] > tmp[cnt] + k) {
            if (cnt == 3) return false;
            tmp[++cnt] = a[i] + k;
        }
    }
    return true;
}

int main() {
    // 初始化与排序
    while (r - l >= eps) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            ans = mid;
            for (int i = 1; i <= 3; i++) pos[i] = tmp[i];
            r = mid - eps;
        } else l = mid + eps;
    }
    // 输出答案
}
```

---

### 题解2：皮卡丘最萌（⭐⭐⭐⭐）
**关键亮点**：
- 思路清晰的二分框架，通过逐步放置基站验证覆盖。
- 处理了基站位置可能未完全使用的情况，确保覆盖正确。

**核心代码**：
```pascal
function pd(x: real): boolean;
begin
  bao1 := a[1] + x;
  // 放置三个基站...
  exit((i = n) and (a[i] <= bao3 + x));
end;
```

---

## 关键思路总结
- **二分答案**是解决此类覆盖问题的通用方法。
- **贪心放置策略**（每次尽可能覆盖更右侧的点）能高效验证答案。
- **浮点精度处理**需设置合理的 $eps$，并在循环条件中避免死循环。

---

## 拓展与练习
1. **类似题目**：
   - [P4343 [SHOI2015] 自动刷题机](https://www.luogu.com.cn/problem/P4343)
   - [P2216 [HAOI2007] 理想的正方形](https://www.luogu.com.cn/problem/P2216)
   - [P3745 [六省联考 2017] 期末考试](https://www.luogu.com.cn/problem/P3745)

2. **调试技巧**：
   - 验证贪心策略时，可手动模拟极端情况（如所有点需三个基站或仅需一个基站）。
   - 注意全局变量在不同二分迭代中的状态重置。

---
处理用时：299.93秒