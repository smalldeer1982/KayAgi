# 题目信息

# [USACO10OPEN] Triangle Counting G

## 题目描述

Bessie is standing guard duty after

the big bad wolf was spotted stalking

```cpp
cows over at Farmer Don's spread. 
Looking down from her guard tower in 
utter boredom, she's decided to 
perform intellectual exercises in 
```
order to keep awake.
After imagining the field as an X,Y

grid, she recorded the coordinates of

the N (1 <= N <= 100,000) 

conveniently numbered 1..N cows as

```cpp
X_i,Y_i (-100,000 <= X_i <= 100,000; 
-100,000 <= Y_i <= 100,000; 1 <= i <= 
N). She then mentally formed all possible triangles that could be made from subsets of the entire set of cow coordinates. She counts a triangle as 'golden' if it wholly contains the origin (0,0). The origin does not fall on the line between any pair of cows. Additionally, no cow is standing exactly on the origin. 
Given the list of cow locations, calculate the number of 'golden' triangles that contain the origin so Bessie will know if she's doing a good job. 
```
By way of example, consider 5 cows at these locations:
-5,0   0,2   11,2   -11,-6   11,-5

Below is a schematic layout of the field from Betsy's point of view:

```cpp
............|............ 
............*..........*. 
............|............ 
-------*----+------------ 
............|............ 
............|............ 
............|............ 
............|............ 
............|..........*. 
.*..........|............ 
............|............ 
```
All ten triangles below can be formed from the five points above:

By inspection, 5 of them contain the origin and hence are 'golden'.

在一只大灰狼偷偷潜入Farmer Don的牛群被群牛发现后，贝西现在不得不履行着她站岗的职责。从她的守卫塔向下瞭望简直就是一件烦透了的事情。她决定做一些开发智力的小练习，防止她睡着了。



想象牧场是一个X，Y平面的网格。她将N只奶牛标记为1…N (1 <= N <= 100,000)，每只奶牛的坐标为X\_i,Y\_i (-100,000 <= X\_i <= 100,000;-100,000 <= Y\_i <= 100,000; 1 <= i <=N)。然后她脑海里想象着所有可能由奶牛构成的三角形。如果一个三角形完全包含了原点(0,0)，那么她称这个三角形为“黄金三角形”。原点不会落在任何一对奶牛的连线上。另外，不会有奶牛在原点。

给出奶牛的坐标，计算出有多少个“黄金三角形”。


## 样例 #1

### 输入

```
5 
-5 0 
0 2 
11 2 
-11 -6 
11 -5 
```

### 输出

```
5 
```

# AI分析结果



**唯一算法分类**  
计算几何（极角排序与容斥原理）

---

**综合分析与结论**  
题目要求统计包含原点的三角形数量。直接枚举所有三角形不可行，需高效算法。核心思路：

1. **容斥原理**：总三角形数减去不包含原点的三角形数。
2. **极角排序**：将点按极角排序后，对每个点统计其半平面内的点数，计算组合数。
3. **循环处理**：通过扩展数组为两倍长度，处理极角环绕问题，便于二分查找。

**核心难点**：正确统计不包含原点的三角形，避免重复计算。  
**解决方案**：利用极角排序后的单调性，对每个点找到其半平面内的点数量，使用组合数公式累加。扩展数组处理极角环绕，确保二分查找正确性。

**可视化设计思路**：  
- **极角环状图**：将极角排序后的点绘制在圆环上，动态高亮当前点及其半平面范围。  
- **双指针动画**：展示如何移动指针找到半平面边界点。  
- **像素风格**：使用8位色块表示点，颜色区分不同半平面区域。  
- **音效提示**：每次找到边界时播放音效，成功统计时触发得分音效。

---

**题解清单 (≥4星)**  
1. **作者：xtx1092515503 (4星)**  
   - 直接计算合法三角形，利用极角排序与双指针预处理，前缀和优化求和。  
   - 代码清晰但逻辑较复杂，适合理解极角分治。

2. **作者：yzhang (5星)**  
   - 容斥思路简洁，极角排序后扩展数组处理循环，二分查找快速统计。  
   - 代码高效易懂，处理边界完整，适合快速实现。

3. **作者：Graphcity (4星)**  
   - 分上下半平面统计贡献，极角排序结合二分查找。  
   - 思路独特，适合理解几何分治。

---

**最优思路提炼**  
1. **容斥原理**：总数为C(n,3)，减去每个点半平面内选两点的组合数。
2. **极角扩展数组**：复制点并加2π，避免极角环绕问题。
3. **二分查找**：快速定位半平面边界点，统计区间长度。

---

**同类型题与算法套路**  
- **极角排序应用**：如[CF598C Nearest vectors](https://www.luogu.com.cn/problem/CF598C)。
- **容斥计数**：如[P3197 越狱](https://www.luogu.com.cn/problem/P3197)。
- **几何分治**：如[P7405 能量获取](https://www.luogu.com.cn/problem/P7405)。

---

**推荐题目**  
1. [P1355 神秘大三角](https://www.luogu.com.cn/problem/P1355)  
2. [CF598C Nearest vectors](https://www.luogu.com.cn/problem/CF598C)  
3. [P2992 [USACO10OPEN] Triangle Counting G](https://www.luogu.com.cn/problem/P2992)

---

**个人心得摘录**  
- **极角精度**：注意atan2的精度问题，避免排序错误。  
- **循环处理**：扩展数组巧妙解决极角环绕，避免复杂边界判断。

---

**代码核心片段**  
```cpp
// 容斥方法核心代码（yzhang题解）
sort(p + 1, p + 1 + n);
for (int i = 1; i <= n; i++) p[i + n] = p[i], p[i + n].k += 2 * Pi;

ll ans = 1LL * n * (n - 1) * (n - 2) / 6;
for (int i = 1, r = 1; i <= n; i++) {
    while (p[r + 1].k < p[i].k + Pi + eps) r++;
    int cnt = r - i;
    ans -= 1LL * cnt * (cnt - 1) / 2;
}
printf("%lld\n", ans);
```

---

**可视化与复古动画实现**  
- **Canvas绘制极角环**：圆心为原点，点按极角分布，半平面高亮为扇形。  
- **像素动画**：点用8位色块，移动指针时高亮当前半平面范围。  
- **音效触发**：指针移动时播放“滴”声，统计贡献时播放“叮”声。  
- **自动演示**：按排序顺序逐个处理点，自动展示查找过程。

---
处理用时：112.11秒