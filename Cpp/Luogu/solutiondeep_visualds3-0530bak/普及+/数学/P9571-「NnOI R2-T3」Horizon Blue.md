# 题目信息

# 「NnOI R2-T3」Horizon Blue

## 题目描述

小 C 喜欢在画板上画画。他进行了 $ n $ 次操作，每次操作有如下三种可能：

- ```1 k b``` 代表小 C 绘制了一条解析式为 $ y=kx+b $ 的直线。
- ```2 k b``` 代表小 C 询问你直线 $ y=kx+b $ 与多少条被绘制的直线有**恰好**一个公共点。
- ```3 k b``` 代表小 C 擦除所有与直线 $ y=kx+b $ 有**至少**一个公共点的直线。

**注意：两条重合的直线有无数个交点。**

**注意：询问时重合的直线应分别计算。**

## 说明/提示

**【样例 1 解释】**

第 1 次操作，绘制直线 $ y=x $。

第 2 次操作，绘制直线 $ y=-x $。

第 3 次操作，可以发现直线 $ y=2x+1 $ 与前两条线相交。

第 4 次操作，擦掉所有 $ y=x+3 $ 相交的线，直线 $ y=-x $ 被擦掉。

第 5 次操作，$ y=2x+1 $ 显然与 $ y=x $ 相交。

第 6 次操作，$ y=x+1 $ 与 $ y=x $ 斜率相等，是平行线，不相交。

**【数据范围】**

对于 $ 100\% $ 的数据，$ 1 \le n \le 10^5 $，$ 1 \le |k| \le 10^5 $，$ 0 \le |b| \le 10^5 $。

**提示：本题开启捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c}
\textbf{Subtask} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1& n \le 5000 & 27 \r
\textsf2& \vert k\vert,\vert b\vert \le 50 & 21 \r
\textsf3& 无第\ 3\ 类操作 & 13 \r
\textsf4& 第\ i\ 次操作满足\ k=i & 14 \r
\textsf5& 无特殊限制 & 25 \r
\end{array}
$$

在赛后新添加的 hack 测试点将放入 subtask 6。

### 题目来源

| 项目 | 人员 |
|:-:|:-:|
| idea | 船酱魔王 |
| data | 船酱魔王 |
| check | EstasTonne |
| solution | 船酱魔王 |

## 样例 #1

### 输入

```
6
1 1 0
1 -1 0
2 2 1
3 1 3
2 2 1
2 1 1```

### 输出

```
2
1
0```

## 样例 #2

### 输入

```
10
1 1 0
1 1 0
2 1 1
2 1 0
2 2 5
3 1 0
2 2 5
1 2 3
1 3 4
2 3 5```

### 输出

```
0
0
2
0
1```

# AI分析结果



**算法分类**：几何

---

### **题解思路与解决难点**

**核心思路**：  
- 两条直线相交当且仅当斜率不同，重合当且仅当斜率和截距均相同。  
- **操作1**：维护每个斜率 `k` 对应的截距集合 `b`，并统计总直线数。  
- **操作2**：答案为总直线数减去斜率为 `k` 的直线数（平行或重合的不计入）。  
- **操作3**：删除所有斜率不为 `k` 的直线，以及斜率为 `k` 但截距为 `b` 的直线。

**关键公式/推导**：  
- 若两条直线斜率不同，必有唯一交点；若斜率相同且截距不同则平行，截距相同则重合。  
- 操作2的答案公式：`总直线数 - 斜率为k的直线数`。  
- 操作3的删除条件：`k' ≠ k` 或 `k' = k 且 b' = b`。

**数据结构**：  
- 使用 `map<int, multiset<int>>` 维护每个斜率 `k` 的截距集合。  
- 总直线数 `tot` 和每个斜率对应的直线数 `cnt[k]` 用于快速查询。

---

### **题解评分（≥4星）**

1. **NaN_HQJ2007_NaN（5星）**  
   - **亮点**：使用 `set` 维护所有存在的斜率，每个斜率对应一个 `multiset` 存储截距。操作3通过遍历非目标斜率快速删除，时间复杂度严格为 $O(n \log n)$。  
   - **代码可读性**：简洁高效，利用 `set` 和 `multiset` 的自动排序特性。  
   - **优化**：负数处理通过偏移量转为正数，避免哈希冲突。

2. **DengDuck（4.5星）**  
   - **亮点**：通过 `map<int, map<int, int>>` 维护斜率和截距的计数，操作3时直接清空无关键值。  
   - **优化**：利用 `set` 记录未被清空的斜率，避免重复遍历。

3. **Special_Tony（4星）**  
   - **亮点**：使用数组偏移处理负数，`multiset` 存储截距，操作3通过 `count` 快速统计重合直线数。  
   - **创新**：利用 `vector` 记录当前存在的斜率，动态维护删除后的状态。

---

### **最优思路与技巧**

1. **斜率分类统计**：  
   将直线按斜率分组，总直线数减去同斜率数量即为相交直线数。这是所有题解的核心优化点。

2. **负数处理技巧**：  
   将斜率 `k` 加上固定偏移量（如 $10^5$）转为非负数，避免哈希表无法处理负数键。

3. **高效删除策略**：  
   - 操作3中，直接清空所有非目标斜率的存储结构（如 `multiset::clear`），复杂度为 $O(1)$ 到 $O(m)$，但均摊后总复杂度仍为 $O(n \log n)$。  
   - 用 `vector` 或 `set` 维护当前存在的斜率，避免遍历所有可能的斜率值。

---

### **类似题目推荐**

1. **P2785 直线交点数**：计算多条直线的交点数量。  
2. **P1972 [SDOI2009] HH的项链**：区间不同元素统计，类似斜率分组思想。  
3. **P1904 天际线**：几何扫描线问题，需处理线段相交。

---

### **可视化与算法演示**

**核心动画设计**：  
- **像素风格界面**：用不同颜色线条表示不同斜率，重合直线高亮为红色。  
- **操作演示**：  
  1. **添加直线**：动态绘制新直线，更新右侧统计面板的斜率分布直方图。  
  2. **查询操作**：高亮所有斜率不同的直线，显示相交点。  
  3. **删除操作**：触发“爆炸”动画清除目标直线，更新剩余直线分布。  

**交互功能**：  
- **步进控制**：允许单步执行，观察每条直线如何被添加或删除。  
- **音效**：添加时播放“滴”声，删除时播放“碎裂”声，查询时播放“叮”声。  

**Canvas 实现片段**：  
```javascript
// 绘制直线 y = kx + b
function drawLine(k, b, color) {
    ctx.beginPath();
    ctx.moveTo(0, b);
    ctx.lineTo(canvas.width, k * canvas.width + b);
    ctx.strokeStyle = color;
    ctx.stroke();
}

// 删除动画：渐变缩小直线
function animateDeletion(line) {
    let scale = 1;
    const animate = () => {
        scale *= 0.9;
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        drawLine(line.k, line.b, `rgba(255,0,0,${scale})`);
        if (scale > 0.1) requestAnimationFrame(animate);
    };
    animate();
}
```

---

### **代码实现（核心片段）**

**NaN_HQJ2007_NaN 的题解代码**：  
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5,nn=1e5;
multiset<int>st[N];
set<int>s;
vector<int>t;
int n;
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>n;
    int tot=0;
    for(int i=1;i<=n;++i){
        int op,k,b;cin>>op>>k>>b;
        if(op==1)st[k+nn].insert(b),s.insert(k+nn),++tot;
        else if(op==2)cout<<tot-st[k+nn].size()<<endl;
        else{
            set<int>::iterator it;t.clear();
            for(it=s.begin();it!=s.end();++it){
                int w=(*it);if(w==k+nn)continue;
                tot-=st[w].size();st[w].clear();t.push_back(w);
            }
            for(int i=0;i<t.size();++i)s.erase(t[i]);
            tot-=st[k+nn].count(b);st[k+nn].erase(b);
        }
    }
    return 0;
}
```

**关键思想**：  
- 使用 `st[k+nn]` 处理负数斜率，`s` 维护所有存在的斜率。  
- 操作3遍历并清空非目标斜率的 `multiset`，再删除重合直线。

---

### **个人心得**

- **调试教训**：直接遍历所有斜率会导致超时，必须维护动态存在的斜率集合。  
- **顿悟点**：操作3只需保留目标斜率的直线，其他全部清除，无需逐个判断相交。

---
处理用时：84.20秒