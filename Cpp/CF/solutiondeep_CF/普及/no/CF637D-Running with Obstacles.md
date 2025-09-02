# 题目信息

# Running with Obstacles

## 题目描述

A sportsman starts from point $ x_{start}=0 $ and runs to point with coordinate $ x_{finish}=m $ (on a straight line). Also, the sportsman can jump — to jump, he should first take a run of length of not less than $ s $ meters (in this case for these $ s $ meters his path should have no obstacles), and after that he can jump over a length of not more than $ d $ meters. Running and jumping is permitted only in the direction from left to right. He can start andfinish a jump only at the points with integer coordinates in which there are no obstacles. To overcome some obstacle, it is necessary to land at a point which is strictly to the right of this obstacle.

On the way of an athlete are $ n $ obstacles at coordinates $ x_{1},x_{2},...,x_{n} $ . He cannot go over the obstacles, he can only jump over them. Your task is to determine whether the athlete will be able to get to the finish point.

## 样例 #1

### 输入

```
3 10 1 3
3 4 7
```

### 输出

```
RUN 2
JUMP 3
RUN 1
JUMP 2
RUN 2
```

## 样例 #2

### 输入

```
2 9 2 3
6 4
```

### 输出

```
IMPOSSIBLE
```

# AI分析结果



# 题目重写  
## 题目名称：奔跑中的障碍  

## 题目描述  
运动员从起点 $x_{start}=0$ 出发，沿直线跑向终点 $x_{finish}=m$。运动员可以进行跳跃，但需要满足以下条件：  
1. 跳跃前必须进行至少 $s$ 米的助跑（助跑路径上不能有障碍）  
2. 跳跃距离不超过 $d$ 米  
3. 起跳和落地必须在无障碍的整数坐标点  
4. 每个障碍必须被跳跃跨越，且落地点严格在障碍右侧  

给定 $n$ 个障碍的坐标 $x_1,x_2,...,x_n$，判断运动员能否到达终点。若能，输出动作序列；否则输出"IMPOSSIBLE"。  

## 输入输出样例  
样例 #1  
输入：  
3 10 1 3  
3 4 7  
输出：  
RUN 2  
JUMP 3  
RUN 1  
JUMP 2  
RUN 2  

样例 #2  
输入：  
2 9 2 3  
6 4  
输出：  
IMPOSSIBLE  

---

### 算法分类  
贪心  

---

### 题解综合分析  
核心思路是通过贪心策略处理障碍区间：  
1. **排序预处理**：将障碍坐标排序后合并连续不可分割的障碍区间  
2. **区间验证**：每个合并后的障碍区间长度必须满足 $R_i-L_i+2 \leq d$  
3. **助跑验证**：相邻区间间距需满足助跑距离要求 $s$  
4. **动作生成**：在满足条件的区间间交替进行助跑和跳跃  

关键难点在于正确合并障碍区间，需确保：  
- 第一个障碍前的初始助跑距离足够  
- 合并后的障碍区间长度不超过跳跃能力  
- 区间间距满足后续助跑需求  

---

### 精选题解（评分≥4星）  

#### 题解作者：water_tomato（⭐⭐⭐⭐⭐）  
**亮点**：  
1. 详细阐述了预处理中的三个关键细节：  
   - 初始助跑距离验证  
   - 设置虚拟点 $a_0=-∞$ 避免首障碍合并错误  
   - 排序必要性说明  
2. 代码中明确处理了区间长度等于 $d$ 的非法情况  
3. 输出了完整的动作序列生成逻辑  

**关键代码**：  
```cpp  
// 预处理合并障碍区间  
a[0] = -(1e9+7);  
for(int i=1;i<=n;i++){  
    if(a[i]-a[i-1]-1 > s)  
        e[++cnt].l = a[i], e[cnt].r = a[i];  
    else  
        e[cnt].r = a[i];  
}  

// 验证跳跃可行性  
for(int i=1;i<=cnt;i++)  
    if(e[i].r - e[i].l +1 >= d){  
        printf("IMPOSSIBLE\n");  
        return 0;  
    }  
```

---

### 最优思路提炼  
1. **区间合并策略**：将间距不足 $s$ 的障碍合并为连续区间  
2. **跳跃可行性检验**：验证每个合并区间长度 $\leq d$  
3. **动作序列生成**：  
   - 在区间左侧进行最大可能助跑  
   - 跳跃到区间右侧+1位置  
   - 最后处理终点剩余距离  

---

### 同类题目推荐  
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 贪心策略  
2. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019) - 区间处理  
3. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803) - 贪心区间选择

---
处理用时：51.32秒