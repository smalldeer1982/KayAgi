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



# 算法分类
计算几何、极角排序、容斥原理

---

## 题解思路与核心难点

### 核心思路对比
**容斥派**（yzhang/partychicken等）：
1. 总三角形数 C(n,3) - 不包含原点的三角形数
2. 极角排序后，每个点统计其所在半平面内的点对组合数
3. 通过双指针/二分查找确定半平面边界

**直接计算派**（xtx1092515503）：
1. 极角排序后，每个点作为第一个顶点时，确定第二、第三顶点的合法区间
2. 预处理每个点的最大扩展点 far[i]
3. 使用前缀和快速计算三元组数量

### 解决难点
- **极角排序**：将二维平面点转化为角度排序，便于线性处理
- **半平面判定**：利用双指针维护动态范围，O(n) 时间找到每个点对应的半平面边界
- **去重处理**：容斥法中通过固定统计方向（如只算左侧），避免重复计算

---

## 高星题解推荐（≥4⭐）

1. **xtx1092515503（5⭐）**
   - 亮点：创新性数学推导，完全避免容斥，直接计算三元组
   - 核心：极角排序+双指针预处理 far[i]，前缀和优化累加

2. **yzhang（4⭐）**
   - 亮点：经典容斥思路，代码简洁易懂
   - 核心：双指针维护半平面范围，处理两倍角度应对循环

3. **juju527（4⭐）**
   - 亮点：清晰的容斥实现，极角排序后动态维护指针
   - 核心：通过旋转卡壳式指针移动统计贡献

---

## 最优思路提炼
**容斥法关键步骤**：
1. 极角排序所有点
2. 对每个点 i，找到其对面半平面起始点 j（角度差 ≥π）
3. 累加 [i+1, j-1] 区间的组合数 C(k,2)，其中 k 为区间长度
4. 最终答案 = C(n,3) - 总非法组合数

**核心代码片段**（yzhang）：
```cpp
sort(p+1,p+1+n); // 极角排序
for(int i=n+1;i<=n<<1;++i) p[i]=p[i-n], p[i].k+=2*Pi; // 处理循环
int l=0,r=0;
for(int i=1;i<=n;++i){
    while(p[r+1].k+eps < p[i].k+Pi) ++r;
    ans -= 1ll*(r-l+1)*(r-l)/2; // 减去半平面内的组合数
}
```

---

## 相似题目推荐
1. **P1663 山**（极角排序+半平面交）
2. **P2289 星际导航**（极角序处理环形问题）
3. **CF598C Nearest vectors**（极角差最小问题）

---

## 可视化设计
**复古像素化演示**：
1. **极角排序动画**：点以旋转方式排列在圆形轨道上，角度值用8-bit字体显示
2. **双指针扫描**：用红色/蓝色像素块表示左右指针，移动时播放"beep"音效
3. **贡献计算**：每次统计区间时，对应区域闪烁绿色，统计值以16进制显示

**交互功能**：
- 方向键控制扫描速度，空格暂停
- 失败音效：当三点不满足条件时播放短促"error.wav"
- 自动模式：AI按最优路径扫描，类似吃豆人移动

---

## 核心算法演示（容斥法）
```javascript
// 伪代码示例：极角排序与双指针扫描
let points = sortByAngle(points); // 极角排序
let doublePoints = [...points, ...points.map(p => ({...p, angle: p.angle + 2*PI}))];

let total = combination(n, 3);
let invalid = 0;
let l = 0, r = 0;

for (let i = 0; i < n; i++) {
    // 更新右边界
    while (doublePoints[r].angle < points[i].angle + PI) r++;
    // 计算区间长度
    let k = r - l - 1;
    invalid += k * (k - 1) / 2;
    l++; // 左指针跟随i移动
}

// 最终结果
let golden = total - invalid;
```

---

## 实现要点
1. **极角处理**：使用`atan2(y,x)`计算角度，注意处理负角度
2. **循环数组**：将角度复制并+2π，避免模运算带来的边界问题
3. **组合数优化**：使用公式 C(k,2) = k*(k-1)/2 避免重复计算

**调试心得**（来自题解）：
> "WA了三次才发现没处理两倍数组，极角差可能跨越360度" —— yzhang  
> "long long没开全，结果n=1e5时溢出" —— juju527

---
处理用时：76.16秒