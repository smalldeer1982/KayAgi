# 题目信息

# Mystic Carvings

## 题目描述

The polar bears have discovered a gigantic circular piece of floating ice with some mystic carvings on it. There are $ n $ lines carved on the ice. Each line connects two points on the boundary of the ice (we call these points endpoints). The endpoints are numbered $ 1,2,...,2n $ counter-clockwise along the circumference. No two lines share an endpoint.

Now a group of 6 polar bears (Alice, Bob, Carol, Dave, Eve, Frank) are going to build caves on the endpoints. Each polar bear would build a cave and live in it. No two polar bears can build a cave on the same endpoints. Alice and Bob is a pair of superstitious lovers. They believe the lines are carved by aliens (or humans, which are pretty much the same thing to polar bears), and have certain spiritual power. Therefore they want to build their caves on two endpoints which are connected by a line. The same for Carol and Dave, Eve and Frank.

The distance between two caves X and Y is defined as one plus minimum number of other caves one need to pass through in order to travel from X to Y along the boundary of the ice (endpoints without caves are not counted).

To ensure fairness, the distances between the three pairs of lovers have to be the same (that is, the distance between Alice and Bob, the distance between Carol and Dave, and the distance between Eve and Frank are the same).

The figures below show two different configurations, where the dots on the circle are the endpoints. The configuration on the left is not valid. Although each pair of lovers (A and B, C and D, E and F) is connected a line, the distance requirement is not satisfied. The distance between A and B is 2 (one can go from A to B in the clockwise direction passing through F). The distance between E and F is also 2. However, the distance between C and D is 1 (one can go from C to D in the counter-clockwise direction without passing through any other caves). The configuration on the right is valid. All three pairs have the same distance 1.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF297E/d4294009e1edf87a8acd5f07b8b6190c53a3334c.png)Count the number of ways to build the caves under the requirements. Two configurations are considered the same if the same set of 6 endpoints are used.

## 说明/提示

The second sample corresponds to the figure in the problem statement.

## 样例 #1

### 输入

```
4
5 4
1 2
6 7
8 3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
1 7
2 4
3 9
5 11
6 8
10 16
13 15
14 12
```

### 输出

```
6
```

# AI分析结果



---

## 算法分类
**组合数学 + 二维偏序 + 树状数组**

---

## 综合分析与结论

### 核心问题与难点
- **目标**：统计圆上选3对端点满足每对距离相同的方案数  
- **关键难点**：  
  1. 环形结构难以直接处理，转化为线性区间问题  
  2. 合法情况（三种特殊弦结构）难以直接计数  
  3. 非法情况需分类讨论（相交、包含等）  
- **解决思路**：  
  1. **容斥法**：总方案数 $C(n,3)$ 减去非法方案  
  2. **二维偏序**：利用树状数组高效统计每条弦的左右不相交弦数 $l[i], r[i]$  
  3. **分类计算**：将非法情况分解为图1、图3/4两种类型分别处理  

### 可视化设计要点
1. **环形弦结构展示**：  
   - 用Canvas绘制圆和所有弦，合法弦对用不同颜色高亮  
   - 单步演示：选中某条弦时，用红色标记当前弦，蓝色标记其左右不相交弦  
2. **树状数组操作动画**：  
   - 动态显示插入和查询操作，如插入弦的右端点时，对应位置亮起绿色光点  
   - 查询区间时，用黄色覆盖被统计的区间  
3. **复古像素风格**：  
   - 8位色块表示端点，弦用像素线条连接  
   - 音效：插入树状数组时播放“哔”声，非法情况统计时播放“噔”声  

---

## 题解评分（≥4星）

### 1. stoorz（⭐⭐⭐⭐⭐）
- **关键亮点**：  
  - 清晰拆解非法情况为两类，公式推导严谨  
  - 利用二维偏序和树状数组高效计算 $l[i], r[i]$  
  - 代码简洁，时间复杂度 $O(n \log n)$  
- **代码片段**：  
  ```cpp
  // 计算 l[i] 的二维偏序部分
  sort(a+1,a+1+n,cmp1);
  for (int i=1;i<=n;i++) {
      l[a[i].id] += bit.ask(a[i].x) + (bit.ask(n*2) - bit.ask(a[i].y));
      bit.add(a[i].y, 1);
  }
  ```

---

## 最优思路提炼

### 核心技巧
1. **容斥与分类讨论**：  
   - 总方案减去非法情况，避免直接统计复杂合法结构  
2. **二维偏序建模**：  
   - 将弦的左右不相交条件转化为二维区间查询问题  
3. **树状数组高效统计**：  
   - 通过排序和树状数组的插入/查询操作，快速计算 $l[i]$ 和 $r[i]$  

### 通用性思路
- **环形问题线性化**：将环形端点展开为线性序列处理  
- **组合计数中的容斥**：当合法情况复杂时，优先考虑反向计算非法情况  

---

## 类似题目推荐
1. **P1972 [SDOI2009]HH的项链**：二维偏序与树状数组应用  
2. **P3810 【模板】三维偏序（陌上花开）**：扩展偏序问题  
3. **P2163 [SHOI2007]园丁的烦恼**：二维区间查询与离散化  

---

## 核心代码实现（stoorz解法）

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N=300010;
int n,l[N],r[N];
ll ans1,ans2;

struct node { int x,y,id; } a[N];
struct BIT {
    int c[N];
    void add(int x,int val) {
        for (;x<=n*2;x+=x&-x) c[x]+=val;
    }
    int ask(int x) {
        int sum=0;
        for (;x;x-=x&-x) sum+=c[x];
        return sum;
    }
} bit;

bool cmp1(node x,node y) { return x.x<y.x; }
bool cmp2(node x,node y) { return x.y>y.y; }

int main() {
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d%d",&a[i].x,&a[i].y);
        if (a[i].x>a[i].y) swap(a[i].x,a[i].y);
        a[i].id=i;
    }
    // 计算 l[i]
    sort(a+1,a+1+n,cmp1);
    for (int i=1;i<=n;i++) {
        l[a[i].id] += bit.ask(a[i].x) + (bit.ask(n*2)-bit.ask(a[i].y));
        bit.add(a[i].y,1);
    }
    memset(bit.c,0,sizeof(bit.c));
    // 计算 r[i]
    for (int i=n;i>=1;i--) {
        r[a[i].id] += bit.ask(a[i].y) - bit.ask(a[i].x);
        bit.add(a[i].y,1);
    }
    // 最终统计与输出
    ans1 = 1LL*n*(n-1)*(n-2)/6;
    for (int i=1;i<=n;i++) {
        ans1 -= 1LL*l[i]*r[i];
        ans2 += 1LL*(l[i]+r[i])*(n-l[i]-r[i]-1);
    }
    printf("%lld", ans1 - ans2/2);
    return 0;
}
```

---
处理用时：85.68秒