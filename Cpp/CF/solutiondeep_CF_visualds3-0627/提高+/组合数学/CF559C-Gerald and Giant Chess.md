# 题目信息

# Gerald and Giant Chess

## 题目描述

Giant chess is quite common in Geraldion. We will not delve into the rules of the game, we'll just say that the game takes place on an $ h×w $ field, and it is painted in two colors, but not like in chess. Almost all cells of the field are white and only some of them are black. Currently Gerald is finishing a game of giant chess against his friend Pollard. Gerald has almost won, and the only thing he needs to win is to bring the pawn from the upper left corner of the board, where it is now standing, to the lower right corner. Gerald is so confident of victory that he became interested, in how many ways can he win?

The pawn, which Gerald has got left can go in two ways: one cell down or one cell to the right. In addition, it can not go to the black cells, otherwise the Gerald still loses. There are no other pawns or pieces left on the field, so that, according to the rules of giant chess Gerald moves his pawn until the game is over, and Pollard is just watching this process.

## 样例 #1

### 输入

```
3 4 2
2 2
2 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
100 100 3
15 16
16 15
99 88
```

### 输出

```
545732279
```

# AI分析结果



# Gerald and Giant Chess 题解分析

## 唯一算法分类
动态规划（DP）与组合数学

---

## 题解思路与核心难点

### 核心算法流程
1. **组合数预处理**：通过阶乘与逆元预处理快速计算组合数。
2. **黑点排序**：按坐标 $(x, y)$ 升序排序，确保 DP 转移时仅依赖已处理的前序黑点。
3. **动态规划状态转移**：
   - 定义 $f[i]$ 为从起点到第 $i$ 个黑点且不经过其他黑点的路径数。
   - 初始值 $f[i] = C(x_i + y_i - 2, x_i - 1)$（不考虑其他黑点的总路径）。
   - 转移时减去所有 $j < i$ 的黑点贡献：$f[i] -= f[j] \cdot C(x_i - x_j + y_i - y_j, x_i - x_j)$。

### 解决难点
- **组合数优化**：模数 $10^9+7$ 下需高效计算逆元。
- **黑点依赖顺序**：排序确保转移顺序正确，避免重复或遗漏。
- **容斥原理应用**：通过减法原理排除经过前序黑点的非法路径。

---

## 题解评分（≥4星）

### 1. 作者：smilke（⭐⭐⭐⭐⭐）
- **亮点**：代码简洁，预处理阶乘与逆元高效；状态转移逻辑清晰，直接排序后动态规划。
- **核心代码**：
  ```cpp
  rep(i,1,n+1) f[i] = C(a[i].x-1, a[i].x+a[i].y-2);
  rep(i,1,n+1) rep(j,1,i-1) {
      if (a[i].x >= a[j].x && a[i].y >= a[j].y) {
          f[i] -= f[j] * C(a[i].x - a[j].x, a[i].x + a[i].y - a[j].x - a[j].y);
      }
  }
  ```

### 2. 作者：Gorenstein（⭐⭐⭐⭐）
- **亮点**：详细推导 DP 状态转移方程，将终点视为黑点巧妙统一逻辑。
- **核心代码**：
  ```cpp
  for (int i=1; i<=n+1; i++) {
      f[i] = C(a[i].x + a[i].y - 2, a[i].x - 1);
      for (int j=1; j<i; j++) {
          f[i] = (f[i] - f[j] * C(a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x)) % mod;
      }
  }
  ```

### 3. 作者：crashed（⭐⭐⭐⭐）
- **亮点**：结合容斥思想，代码模块化，排序后直接处理。
- **核心代码**：
  ```cpp
  for (int i=1; i<=N; i++) {
      DP[i] = C(a[i].x + a[i].y - 2, a[i].y - 1);
      for (int j=1; j<i; j++) {
          DP[i] = (DP[i] - 1LL * DP[j] * C(a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x)) % mod;
      }
  }
  ```

---

## 最优思路提炼
- **组合数预处理**：阶乘与逆元预处理实现 $O(1)$ 组合数查询。
- **排序与 DP 转移**：按坐标排序后，逐个计算每个黑点的合法路径数，确保前序结果已计算。
- **终点处理技巧**：将终点视为黑点，统一状态转移逻辑。

---

## 同类型题与相似套路
- **类似题目**：
  - [BZOJ4767 两双手](http://www.lydsy.com/JudgeOnline/problem.php?id=4767)：同样需要处理路径中的障碍点，但移动方式不同。
  - [LeetCode 62. 不同路径](https://leetcode.cn/problems/unique-paths/)：基础版，无障碍情况。
  - [LeetCode 63. 不同路径 II](https://leetcode.cn/problems/unique-paths-ii/)：含障碍的网格 DP。

---

## 推荐题目
1. **洛谷 P2567 障碍路线**（动态规划与组合数结合）
2. **洛谷 P3958 奶酪**（三维空间路径规划与容斥）
3. **洛谷 P5020 货币系统**（动态规划与集合覆盖问题）

---

## 可视化与算法演示设计
### 动画方案
- **8位像素风格**：棋盘用网格表示，起点绿色，终点红色，黑点灰色。
- **关键步骤高亮**：
  - **当前处理黑点**：闪烁显示。
  - **路径计算**：用箭头动态绘制当前黑点到终点的路径。
- **音效设计**：
  - **路径更新**：触发短促“滴”声。
  - **错误路径**：播放低沉音效。

### 交互功能
- **步进控制**：允许单步执行 DP 转移，观察每个黑点的计算过程。
- **自动模式**：按排序顺序自动展示每个黑点的处理流程。

---

## 个人心得摘录
- **排序重要性**：未正确排序会导致转移顺序错误，需严格按 $(x, y)$ 升序排列。
- **模运算处理**：减法后需加模再取模，避免负数结果（如 `f[i] = (f[i] + mod) % mod`）。

---

## 核心代码实现（以 smilke 为例）
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
const int N=3e5+50, mod=1e9+7;
int h,w,n,p[N],inv[N],f[N];
struct node{ int x,y; }a[N];
bool cmp(node a,node b){ return a.x<b.x || (a.x==b.x && a.y<b.y); }
int C(int m,int n){ return m>n ? 0 : p[n]*inv[n-m]%mod*inv[m]%mod; }
int pow_mod(int a,int b){
    int res=1;
    while(b){ if(b&1) res=res*a%mod; a=a*a%mod; b>>=1; }
    return res;
}
int main(){
    scanf("%d%d%d",&h,&w,&n);
    rep(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
    a[n+1] = {h, w};
    sort(a+1, a+n+2, cmp);
    rep(i,0,N-10) p[i] = i?p[i-1]*i%mod : 1, inv[i] = pow_mod(p[i], mod-2);
    rep(i,1,n+1){
        f[i] = C(a[i].x-1, a[i].x+a[i].y-2);
        rep(j,1,i-1){
            if(a[i].x >= a[j].x && a[i].y >= a[j].y){
                int dx = a[i].x - a[j].x, dy = a[i].y - a[j].y;
                f[i] = (f[i] - f[j] * C(dx, dx+dy) % mod + mod) % mod;
            }
        }
    }
    printf("%d\n", f[n+1]);
    return 0;
}
```

---
处理用时：90.17秒