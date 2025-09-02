# 题目信息

# Recommendations

## 题目描述

有 $n$ 个区间 $S_i=[l_i,r_i]$，对于每个区间求出 $|\bigcap\limits_{j} S_j|-|S_i|$，其中 $j\neq i$，且 $S_i\subseteq S_j$。即对于每个区间求出其包区间交集的大小，并减去自己的大小。

## 样例 #1

### 输入

```
4
3
3 8
2 5
4 5
2
42 42
1 1000000000
3
42 42
1 1000000000
42 42
6
1 10
3 10
3 7
5 7
4 4
1 2```

### 输出

```
0
0
1
999999999
0
0
0
0
0
2
3
2
4
8```

# AI分析结果



---

## **算法分类**
**二维排序与数据结构优化**

---

## **题解思路、算法要点与解决难点**

### **核心思路**
所有题解均围绕以下关键点展开：
1. **问题转化**：区间交的左右端点由所有包含当前区间的其他区间的最大左端点和最小右端点决定。
2. **排序优化**：通过两次排序（左端点升序、右端点降序）将二维区间包含问题转化为一维查询问题。
3. **数据结构加速**：使用 `multiset`、线段树或树状数组快速查询满足条件的最大左端点和最小右端点。

### **解决难点**
1. **高效查询**：如何在所有包含当前区间的区间中快速找到最大左端点 $L$ 和最小右端点 $R$。
2. **重复区间处理**：当多个区间完全相同时，需特判答案为零。
3. **离散化**：部分题解通过离散化处理大范围坐标，以适配线段树或树状数组的索引限制。

---

## **题解评分 (≥4星)**
| 作者 | 评分 | 亮点 |
|------|------|------|
| **Hide_In_The_Shadow** | ★★★★☆ | 简洁的双排序+`multiset`实现，代码逻辑清晰 |
| **Eddie08012025** | ★★★★☆ | 使用 `set` 和 `map` 处理排序，优化查询逻辑 |
| **SilverLi** | ★★★★☆ | 线段树维护极值，支持动态插入与查询 |

---

## **最优思路与技巧提炼**
### **关键步骤**
1. **左端点排序**：将所有区间按左端点升序排序，右端点降序排序（确保相同左端点时更大的右端点优先）。
2. **右端点查询**：用 `multiset` 维护已处理的右端点，通过 `lower_bound` 找到最小 $R$。
3. **右端点排序**：将所有区间按右端点降序排序，左端点升序排序。
4. **左端点查询**：用树状数组维护已处理的左端点的最大值。

### **核心代码片段**
```cpp
// 按左端点排序并处理右端点
sort(a+1, a+n+1, cmp0);
multiset<int> s;
for (int i=1; i<=n; ++i) {
    s.insert(a[i].r);
    auto it = s.lower_bound(a[j].r);
    if (it != s.end()) R = *it;
}

// 按右端点排序并处理左端点
sort(a+1, a+n+1, cmp1);
multiset<int> s_max_l;
for (int i=n; i>=1; --i) {
    s_max_l.insert(a[i].l);
    auto it = s_max_l.upper_bound(a[j].l);
    if (it != s_max_l.begin()) L = *(--it);
}
```

---

## **同类题目推荐**
1. **[P1908 逆序对](https://www.luogu.com.cn/problem/P1908)**：利用树状数组统计逆序对。
2. **[P1972 [SDOI2009] HH的项链](https://www.luogu.com.cn/problem/P1972)**：离线查询与树状数组结合。
3. **[P5490 矩形面积并](https://www.luogu.com.cn/problem/P5490)**：扫描线算法处理二维覆盖问题。

---

## **可视化与算法演示**
### **核心流程动画设计**
1. **排序过程**：以像素块表示区间，按左端点排序后，区间从左到右排列，右端点高度表示大小。
2. **右端点插入**：插入当前区间的右端点到 `multiset`，高亮当前操作的区间和已维护的右端点集合。
3. **查询最小R**：红色箭头动态指向 `lower_bound` 找到的最小右端点，并计算差值。
4. **左端点处理**：翻转坐标系后重复上述步骤，蓝色箭头标记最大左端点。

### **复古像素化效果**
- **颜色方案**：使用 8 位调色板（绿、红、蓝、黄）表示不同区间状态。
- **音效**：插入操作时播放短促“滴”声，查询成功时播放上升音调，失败时播放下降音调。
- **自动演示**：按空格键切换手动/自动模式，自动模式下算法逐步执行，速度可调。

---

## **代码实现（Hide_In_The_Shadow 题解）**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int t,n,l[N],r[N];
struct seg{ int l,r,id; }a[N];
bool cmp0(seg a,seg b){ return a.l<b.l; }
bool cmp1(seg a,seg b){ return a.r<b.r; }

int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--){
        cin>>n;
        for(int i=1;i<=n;++i) cin>>a[i].l>>a[i].r, a[i].id=i;
        
        // 处理右端点 R
        sort(a+1,a+n+1,cmp0);
        multiset<int> s;
        for(int i=1,pre=0; i<=n; pre=i){
            while(i<=n && a[i].l==a[pre].l) s.insert(a[i].r), i++;
            for(int j=pre; j<i; ++j){
                auto it = s.upper_bound(a[j].r);
                r[a[j].id] = (it!=s.end()) ? *it : -1;
            }
        }
        
        // 处理左端点 L
        sort(a+1,a+n+1,cmp1);
        multiset<int,greater<int>> s_max_l;
        for(int i=n,pre=n+1; i>=1; pre=i){
            while(i>=1 && a[i].r==a[pre].r) s_max_l.insert(a[i].l), i--;
            for(int j=i+1; j<pre; ++j){
                auto it = s_max_l.upper_bound(a[j].l);
                l[a[j].id] = (it!=s_max_l.end()) ? *it : -1;
            }
        }
        
        // 输出结果
        for(int i=1;i<=n;++i)
            cout<<( (l[i]==-1||r[i]==-1) ? 0 : r[i]-l[i]-(a[i].r-a[i].l) )<<'\n';
    }
    return 0;
}
```

---

**可视化代码片段（Canvas 动画骨架）**
```javascript
// 初始化 Canvas
const canvas = document.getElementById('animation');
const ctx = canvas.getContext('2d');
let intervals = []; // 存储区间数据

function drawInterval(interval, color) {
    ctx.fillStyle = color;
    ctx.fillRect(interval.x, 50, 10, 10); // 以方块表示区间端点
}

function animate() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    intervals.forEach(intv => drawInterval(intv, intv.active ? '#FF0000' : '#00FF00'));
    requestAnimationFrame(animate);
}
animate();
```

---

**总结**：本题解通过两次排序将二维问题降维，结合高效数据结构实现快速极值查询。可视化设计以像素风格和音效增强理解，同类题目可进一步巩固排序+数据结构的组合应用。

---
处理用时：92.34秒