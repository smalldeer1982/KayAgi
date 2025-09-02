# 题目信息

# 「TOCO Round 1」自适应 PVZ

## 题目背景

爆切今天的毒瘤三维计算几何后，$\color{black}\texttt{Q}\color{red}\texttt{wQcOrZ}$ 打开了某个有趣的 exe 文件。

## 题目描述

可怜的 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 在草坪上遇到了 $n$ 只僵尸，第 $i$ 只僵尸在 $l_i$ 时刻出现，会在 $r_i$ 时刻走进房子。

$\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 手头有 $m$ 个豌豆射手。若一个豌豆射手在 $l_i$ 至 $r_i$ 时刻（不包括两个端点）持续攻击 $i$ 僵尸则可以杀死 $i$ 僵尸，但在攻击过程中不能攻击另外两只僵尸且攻击的僵尸不能更换。

现在 $\color{black}\texttt Q\color{red}\texttt{wQcOrZ}$ 想知道在合理的安排下，最少有几只僵尸会进入他的房子。

## 说明/提示

对于 $30\%$ 的数据，$n,m\leq 6$。  
对于 $60\%$ 的数据，$n,m\leq 10^3$。  
对于另外 $20\%$ 的数据，$m\geq n$。  
对于 $100\%$ 的数据，$1\leq n,m\leq 2\times 10^5$，$1\leq l_i<r_i\leq 10^9$。

## 样例 #1

### 输入

```
2 1
1 2
3 4```

### 输出

```
0```

## 样例 #2

### 输入

```
3 2
1 3
1 3
2 4```

### 输出

```
1```

## 样例 #3

### 输入

```
2 1
1 3
3 5```

### 输出

```
0```

# AI分析结果



## 唯一算法分类
**贪心算法（区间调度）**

---

## 综合分析与结论

### 核心算法流程
1. **排序策略**：将僵尸按右端点升序排序，优先处理结束时间早的僵尸，以最大化后续调度空间。
2. **数据结构**：使用 `multiset` 维护豌豆射手的最近可用时间，每次通过二分查找（`upper_bound`）快速定位可用射手。
3. **调度逻辑**：对于每个僵尸，找到第一个可用时间 ≤ 当前僵尸左端点的射手，更新其可用时间；若无可用且射手数未满则新增，否则无法消灭该僵尸。

### 可视化设计思路
1. **动画方案**：
   - **僵尸队列**：左侧显示按右端点排序的僵尸，当前处理僵尸高亮为红色。
   - **豌豆射手池**：右侧用绿色方块表示 `multiset` 中的可用时间，选中时变为黄色。
   - **操作演示**：当前僵尸被处理时，从 `multiset` 中弹出匹配的绿色方块，插入新的蓝色方块（新可用时间）。
2. **复古风格**：
   - **8位像素UI**：僵尸显示为像素骷髅头，射手时间用不同颜色方块表示。
   - **音效设计**：消灭成功时播放短促“叮”声，失败时播放低沉“噗”声，背景为8位芯片音乐。
3. **交互功能**：支持暂停/继续、步进执行、调节动画速度，并显示当前消灭数和剩余僵尸数。

---

## 题解清单（4星及以上）

### 1. 吴思诚（5星）
- **亮点**：代码简洁，利用 `multiset` 的自动排序和二分特性高效处理调度，时间复杂度 O(n log n)。
- **关键代码**：
  ```cpp
  multiset<int> s;
  sort(z+1, z+n+1, cmp); // 按右端点排序
  for (每个僵尸) {
      auto it = s.upper_bound(l_i);
      if (it != s.begin()) s.erase(--it), s.insert(r_i);
      else if (s.size() < m) s.insert(r_i);
      else ans++;
  }
  ```

### 2. liaoxingrui（4星）
- **亮点**：与吴思诚思路一致，代码更易读，适合初学者理解。
- **个人心得**：明确注释了边界条件（`l_i+1` 开始攻击），避免区间端点误解。

### 3. _zhx（4星）
- **亮点**：提供完整 Splay 树实现，展示底层数据结构操作，适合进阶学习。
- **关键片段**：
  ```cpp
  Splay<ll> splay; // 自定义平衡树
  splay.insert(0); // 初始射手时间为0
  for (僵尸) {
      int pre = splay.get_pre(l_i);
      if (pre有效) splay删除pre并插入r_i;
      else 处理新增或失败;
  }
  ```

---

## 核心代码实现（吴思诚版）

```cpp
#include<bits/stdc++.h>
using namespace std;
struct zombie { int l, r; } z[200005];
multiset<int> s;
int main() {
    int n, m, ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        cin >> z[i].l >> z[i].r;
    sort(z+1, z+n+1, [](auto a, auto b) { 
        return a.r < b.r; 
    });
    for (int i = 1; i <= n; i++) {
        auto it = s.upper_bound(z[i].l);
        if (it != s.begin()) 
            s.erase(--it), s.insert(z[i].r);
        else if (s.size() < m) 
            s.insert(z[i].r);
        else ans++;
    }
    cout << ans;
}
```

---

## 类似题目推荐
1. **P1803 线段覆盖**：基础贪心，按右端点排序选择不重叠线段。
2. **P4059 找爸爸**：时间调度中的动态规划优化。
3. **CF732E 插座匹配**：贪心+优先队列处理资源分配。

---

## 个人心得摘录
- **sunrise1024**：调试时发现需处理三种情况，平衡树的复杂操作容易出错，最终通过分步验证解决。
- **ForgotMe**：最初错误地按左端点排序，WA后对比样例才意识到右端点排序的关键性。

---

## 复古游戏化动画代码片段（JS）

```javascript
// 初始化 Canvas
const canvas = document.getElementById('game');
const ctx = canvas.getContext('2d');
let zombies = [...]; // 排序后的僵尸数据
let shooters = new SortedSet(); // 模拟 multiset

function draw() {
    ctx.fillStyle = '#2d2d2d'; // 复古背景色
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    // 绘制僵尸队列
    zombies.forEach((z, i) => {
        ctx.fillStyle = i === currentZombie ? '#ff0000' : '#ffffff';
        drawPixelArt(zombieSprite, z.l * 10, 50 + i * 20);
    });
    // 绘制射手池
    shooters.values().forEach((t, i) => {
        ctx.fillStyle = t === selectedTime ? '#ffff00' : '#00ff00';
        drawPixelArt(shooterSprite, t * 10, 200 + i * 20);
    });
}

function gameStep() {
    if (currentZombie >= zombies.length) return;
    let z = zombies[currentZombie];
    let it = shooters.upperBound(z.l);
    // 播放音效
    if (it !== shooters.begin()) {
        playSound('attack');
        shooters.delete(--it);
        shooters.add(z.r);
    } else if (shooters.size < m) {
        playSound('new');
        shooters.add(z.r);
    } else {
        playSound('fail');
        ans++;
    }
    currentZombie++;
    requestAnimationFrame(draw);
}
```

---
处理用时：84.95秒