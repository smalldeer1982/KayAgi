# 题目信息

# [JRKSJ R1] JFCA

## 题目描述

给出一个环，上面有 $n$ 个点，每个相邻的点对之间的距离为 $1$。

每个点有两个属性 $a_i$ 和 $b_i$，对于点 $i$，定义 $f_i$ 为它与满足 $a_j\ge b_i$ 的最近的点 $j$ 与 $i$ 在环上距离较短一边的长度，其中 $i\ne j$。如果没有满足条件的 $j$，其 $f_i=-1$。

## 说明/提示

对于 $20\%$ 的数据，$1\le n \le 10^3$；\
对于 $100\%$ 的数据，$1\le n \le 10^5$，$1\le a_i,b_i\le 10^9$。

我们对于测试点 $4$ 至 $11$ 采用捆绑测试。

#### 样例 1 解释
对于 $i=1$，$a_3=3= b_1=3$, $1$ 和 $3$ 的距离是 $1$，所以 $f_1=1$。\
对于 $i=2$，$a_3=3> b_2=2$, $2$ 和 $3$ 的距离是 $1$，所以 $f_2=1$。\
对于 $i=3$，$a_2=2> b_3=1$, $2$ 和 $3$ 的距离是 $1$，所以 $f_3=1$。

$\text{upd2021.3.30}$：增加一组 hack 数据，卡掉了@[wu0615](https://www.luogu.com.cn/user/133037) 的提交。



## 样例 #1

### 输入

```
3
1 2 3
3 2 1```

### 输出

```
1 1 1```

## 样例 #2

### 输入

```
5
5 4 3 5 6
7 6 5 4 3```

### 输出

```
-1 2 1 1 1```

## 样例 #3

### 输入

```
5
1 1 2 1 1
2 2 2 2 2```

### 输出

```
2 1 -1 1 2```

# AI分析结果



**唯一算法分类**  
二分

---

### 题解思路、算法要点与解决难点

**核心思路**  
1. **断环为链**：将数组复制三倍（原环展开为链，避免越界）  
2. **ST表预处理**：O(n log n) 预处理区间最大值，支持 O(1) 查询  
3. **二分查找**：对每个点 i，二分距离 mid，检查左右区间是否存在满足条件的最大值  

**算法要点**  
- 搜索区间初始化为 [1, n-1]（环上最长劣弧为 ⌊n/2⌋）  
- 二分条件：左右区间 [i-mid, i-1] 和 [i+1, i+mid] 的最大值 ≥ b_i  
- 区间收缩：若存在满足条件的最大值，则尝试更小距离（r=mid-1），否则扩大（l=mid+1）  

**解决难点**  
1. **环结构处理**：通过三倍数组模拟环的展开，中间段（n+1~2n）作为基准点  
2. **排除当前点**：区间查询需严格排除 i 点自身（i≠j）  
3. **边界条件**：当二分结果 mid=n 时，说明绕环一周无解，返回 -1  

---

### 题解评分 (≥4星)

1. **cyffff (5星)**  
   - 亮点：代码简洁，三倍数组处理巧妙，ST表与二分逻辑清晰  
   - 关键代码：  
     ```cpp
     int ef(int x, int i) {
         int l=1, r=n;
         while (l<r) {
             int mid = l+r>>1;
             if (max(query(i-mid,i-1), query(i+1,i+mid)) >=x) r=mid;
             else l=mid+1;
         }
         return l==n ? -1 : l;
     }
     ```

2. **Scorilon (4星)**  
   - 亮点：代码规范，注释清晰，逻辑完整  
   - 关键优化：直接处理中间段 i+n，避免复杂边界判断  

3. **HPXXZYY (4星)**  
   - 亮点：模块化设计，check 函数分离，代码可读性强  
   - 关键逻辑：  
     ```cpp
     bool check(int t, int i, int x) {
         return max(query(i-t,i-1), query(i+1,i+t)) >=x;
     }
     ```

---

### 最优思路或技巧提炼

1. **三倍数组断环**：复制数组为三倍长度，中间段作为基准点，避免越界  
2. **二分条件优化**：同时检查左右区间，取最大值判断，减少二分次数  
3. **ST表区间查询**：O(1) 时间获取任意区间最大值，支撑二分的高效性  
4. **边界处理**：通过 l==n 判断无解，避免无效绕环  

---

### 同类型题或类似算法套路

- **二分答案**：当问题可转化为“判断是否存在满足条件的最小值”时适用  
- **区间极值预处理**：静态数组多次查询极值，优先用 ST 表  
- **环形转链**：通过复制数组展开环，适用于旋转、循环问题  

**推荐题目**  
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)（区间极值）  
2. [P3382 三分法](https://www.luogu.com.cn/problem/P3382)（单峰函数极值）  
3. [P4344 环形均分纸牌](https://www.luogu.com.cn/problem/P4344)（环形结构处理）  

---

### 可视化与算法演示

**动画方案**  
1. **像素风格 Canvas**：  
   - 环形数组用三个色块（红、绿、蓝）表示三倍复制  
   - 当前基准点 i+n 高亮为黄色  
   - 左右区间用动态扩展的矩形框表示，颜色随 mid 变化  

2. **二分过程演示**：  
   - **初始状态**：left=1（蓝色），right=n-1（红色），mid 标记为紫色  
   - **收缩逻辑**：若满足条件，right 左移；否则 left 右移  
   - **结果高亮**：找到的 mid 用绿色闪烁，无解时显示红色 X  

3. **音效设计**：  
   - 移动 mid：8-bit 电子音  
   - 找到解：胜利音效（高音阶）  
   - 无解：低沉错误音  

**交互控制**  
- 速度滑块：调节动画步进速度（0.5x~4x）  
- 单步执行：按空格键逐步执行二分步骤  
- 自动播放：AI 自动完成全过程，类似贪吃蛇自动寻路  

---

### 代码核心实现（cyffff 题解）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10;
int n, st[N][30], lg[N];

int query(int l, int r) {
    int q=lg[r-l+1];
    return max(st[l][q], st[r-(1<<q)+1][q]);
}

int ef(int x, int i) { // 二分核心逻辑
    int l=1, r=n;
    while(l<r) {
        int mid=l+r>>1;
        if (max(query(i-mid,i-1), query(i+1,i+mid)) >=x) r=mid;
        else l=mid+1;
    }
    return l==n ? -1 : l;
}

int main() {
    n=read();
    for(int i=1; i<=n; i++) {
        st[i][0] = st[i+n][0] = st[i+n+n][0] = read();
    }
    // ST表预处理
    for(int i=2; i<=3*n; i++) lg[i]=lg[i>>1]+1;
    for(int j=1; j<=20; j++) {
        for(int i=1; i+(1<<j)-1<=3*n; i++) {
            st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
        }
    }
    // 处理每个点
    for(int i=1; i<=n; i++) {
        int b=read();
        write(ef(b, i+n));
    }
}
```

---

### 个人心得摘录

- **调试教训**：初始未处理三倍数组导致越界，需严格验证区间范围  
- **顿悟点**：发现二分时只需检查左右区间而非整个环，极大简化逻辑  
- **优化技巧**：预处理 lg 数组代替 log2 计算，加速 ST 表查询  

--- 

**可视化代码片段（伪代码）**  
```javascript
// Canvas绘制环形数组
function drawRing() {
  ctx.fillStyle = "#FF0000"; // 红色段
  ctx.fillRect(0, 0, width/3, height);
  ctx.fillStyle = "#00FF00"; // 绿色段（基准段）
  ctx.fillRect(width/3, 0, width/3, height);
  ctx.fillStyle = "#0000FF"; // 蓝色段
  ctx.fillRect(2*width/3, 0, width/3, height);
}

// 更新二分动画
function updateBinaryStep() {
  let mid = Math.floor((left + right) / 2);
  drawMidMarker(mid); // 绘制紫色mid标记
  if (checkCondition(mid)) {
    right = mid - 1;
    playSound("success");
  } else {
    left = mid + 1;
    playSound("move");
  }
}
```

---
处理用时：85.57秒