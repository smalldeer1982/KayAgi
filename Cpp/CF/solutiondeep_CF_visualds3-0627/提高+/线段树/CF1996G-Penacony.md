# 题目信息

# Penacony

## 题目描述

在梦乡 $\text{Penacony}$ ，有 $n$ 栋房子和 $n$ 条双向的路。第 $i$ 栋和第 $i+1$ 栋房子（包括第 $n$ 和第 $1$ 栋之间）有双向的路连接。然而，由于梦乡的危机，领主陷入债务，难以维护所有的路。

梦乡的居民之中，有 $m$ 对好朋友。如果住在 $a$ 栋的居民和住在 $b$ 栋的居民是好朋友，那么他们必须能够通过受到维护的道路相互来往，即要求维护 $a$ 栋和 $b$ 栋之间那些的路。

请求出梦乡的领主最少需要维护多少条路。

## 样例 #1

### 输入

```
7
8 3
1 8
2 7
4 5
13 4
1 13
2 12
3 11
4 10
10 2
2 3
3 4
10 4
3 8
5 10
2 10
4 10
4 1
1 3
5 2
3 5
1 4
5 2
2 5
1 3```

### 输出

```
4
7
2
7
2
3
3```

# AI分析结果



---

## 唯一算法分类  
**哈希 + 前缀和统计**

---

## 综合分析与结论  
### 核心思路  
所有题解均围绕「环上两点路径选择」这一核心矛盾展开。异或哈希法（int08、LETTTER、Priestess_SLG）通过以下步骤实现突破：  
1. **路径影响哈希化**：为每对朋友随机生成哈希值，异或到两个端点  
2. **前缀和特征提取**：通过异或前缀和将环转化为链式特征值  
3. **众数统计优化**：出现次数最多的前缀和对应最大可删除边集合  

### 解决难点  
- **环的双向路径选择**：通过哈希值的奇偶性隐式表示路径方向选择  
- **动态维护复杂度**：线段树需 O(n log n)，哈希法通过差分前缀和实现 O(n)  

### 可视化设计要点  
1. **像素动画**：将环展开为直线网格，每格代表一条边  
   - 初始状态：所有边为灰色  
   - 添加朋友对时：在对应端点位置播放像素爆炸特效（红/蓝粒子）  
   - 异或过程：用闪烁的黄色方块表示异或操作  
2. **哈希值流动**：  
   - 前缀和计算时，用流动光效从左到右传递异或值  
   - 相同哈希值用统一颜色标记（如彩虹色谱映射哈希值）  
3. **音效设计**：  
   - 异或操作：8-bit "哔"声（类似红白机射击音效）  
   - 众数统计完成：播放经典过关音效  

---

## 题解清单 (≥4星)  
### 1. int08（⭐️⭐️⭐️⭐️⭐️）  
**亮点**：首创Xor-Hash思想，随机数处理环路径方向，代码仅20行  
**核心代码**：  
```cpp
ll r=Rand();
p[a]^=r, p[b]^=r;  // 异或端点
for(i=1;i<=n;i++) p[i]^=p[i-1];  // 前缀和
ans = max出现次数(p[1..n]);
cout << n-ans;
```

### 2. LETTTER（⭐️⭐️⭐️⭐️）  
**亮点**：清晰解释哈希值对应几何意义（优弧/劣弧选择）  
**优化点**：使用mt19937_64替代自定义随机函数  

### 3. Priestess_SLG（⭐️⭐️⭐️⭐️）  
**亮点**：双哈希增强正确性，代码注释详细  
**心得摘录**："保险起见，再加上双哈希" —— 处理大数冲突的实用技巧  

---

## 最优思路代码实现  
```cpp
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

void solve() {
    int n, m; cin >> n >> m;
    vector<ull> hash(n+1);
    mt19937_64 rng(random_device{}());
    
    while(m--) {
        int a, b; cin >> a >> b;
        ull val = rng();
        hash[a] ^= val;  // 关键点1：异或到端点
        hash[b] ^= val;
    }
    
    // 关键点2：前缀和化环为链
    for(int i=1; i<=n; i++) hash[i] ^= hash[i-1];
    
    // 关键点3：统计最大相同值
    unordered_map<ull, int> cnt;
    int max_cnt = 0;
    for(int i=1; i<=n; i++) 
        max_cnt = max(max_cnt, ++cnt[hash[i]]);
    
    cout << n - max_cnt << "\n";
}
```

---

## 相似题目推荐  
1. **P3538 [POI2012]OKR-A Horrible Poem**  
   - 哈希应用：循环节判断  
2. **CF1016E Rest In The Shades**  
   - 几何问题前缀和化  
3. **P3185 [HNOI2007]分裂游戏**  
   - 异或哈希在博弈论中的应用  

---

## 复古像素动画实现要点  
```javascript
// Canvas初始化
const canvas = document.getElementById('pixel-canvas');
const ctx = canvas.getContext('2d');
const GRID_SIZE = 20; // 像素块大小

function drawEdge(edgeIdx, color) {
    const x = edgeIdx * GRID_SIZE;
    ctx.fillStyle = color;
    ctx.fillRect(x, 50, GRID_SIZE, GRID_SIZE); // 在y=50位置绘制边
}

// 异或动画示例
function playXorAnim(a, b, hashVal) {
    // 端点闪烁特效
    [a, b].forEach(i => {
        drawEdge(i, '#FF00FF');
        setTimeout(() => drawEdge(i, getHashColor(hashVal)), 200);
    });
    // 播放音效
    new Audio('sfx/xor.ogg').play(); 
}

// 哈希值颜色映射
const hashColors = {}; 
function getHashColor(hash) {
    if(!hashColors[hash]) 
        hashColors[hash] = `hsl(${Math.abs(hash)%360}, 70%, 60%)`;
    return hashColors[hash];
}
```

---

## 思维拓展  
当问题扩展到**三维环面**时，可将哈希维度提升至三维坐标哈希。例如对立方体的每条棱进行独立哈希编码，通过三维前缀和统计最大公共子空间。此时需注意环面在三个维度的循环特性，可采用模运算处理哈希值的空间传递。

---
处理用时：68.04秒