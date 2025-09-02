# 题目信息

# [IOI 1994] 数字三角形 Number Triangles

## 题目描述

观察下面的数字金字塔。


写一个程序来查找从最高点到底部任意处结束的路径，使路径经过数字的和最大。每一步可以走到左下方的点也可以到达右下方的点。

![](https://cdn.luogu.com.cn/upload/image_hosting/95pzs0ne.png)

在上面的样例中，从 $7 \to 3 \to 8 \to 7 \to 5$ 的路径产生了最大权值。



## 说明/提示

【数据范围】  
对于 $100\%$ 的数据，$1\le r \le 1000$，所有输入在 $[0,100]$ 范围内。

题目翻译来自NOCOW。

USACO Training Section 1.5

IOI1994 Day1T1

## 样例 #1

### 输入

```
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5 
```

### 输出

```
30
```

# AI分析结果



# [IOI 1994] 数字三角形 Number Triangles

## 算法分类
动态规划

---

## 题解分析与结论

### 核心思路与难点
**状态转移方程**  
`dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + a[i][j]`  
从底层向上逐层递推，每个点的最优解由其下方两个子节点决定，最终顶点即全局最优解。

**解决难点**  
1. **逆向思维突破**：传统思维容易陷入从上到下的路径选择困境，逆向递推将问题分解为更简单的子问题
2. **空间优化**：通过一维数组滚动更新，将空间复杂度从 O(n²) 优化到 O(n)
3. **边界处理**：最底层直接初始化，避免特殊判断

---

## 高星题解推荐 (≥4★)

### 1. linlin1024 (5★)
**逆向递推法**  
- 核心代码片段：
```cpp
for(int i=n-2; i>=0; i--)
    for(int j=0; j<=i; j++)
        a[i][j] += max(a[i+1][j], a[i+1][j+1]);
```
**亮点**：直接修改输入数组实现原地计算，空间复杂度 O(1)

### 2. iwprc (5★)
**一维数组优化**  
- 核心代码片段：
```cpp
for(int i=n-1; i; i--)
    for(int j=i; j<=n; j++)
        a[j] = max(a[j], a[j+1]) + 当前输入值;
```
**亮点**：边读入边处理，空间复杂度 O(n)，适合大规模数据

### 3. Mine_King (4★)
**记忆化搜索转递推**  
- 核心代码片段：
```cpp
for(int i=n-1; i; i--)
    for(int j=1; j<=i; j++)
        a[i][j] += max(a[i+1][j], a[i+1][j+1]);
```
**亮点**：直观展示动态规划与记忆化搜索的等价性

---

## 最优技巧提炼
1. **逆向递推法**：从金字塔底层向上计算，避免路径分支判断
2. **滚动数组优化**：使用单数组存储中间结果，内存效率提升 50%
3. **输入处理技巧**：边读入边计算，减少额外存储空间

---

## 同类型题目
1. **最小路径和**：LeetCode 64
2. **不同路径数**：洛谷 P1002 过河卒
3. **带障碍路径**：洛谷 P1508 Likecloud-吃、吃、吃

---

## 可视化算法演示
**动画设计**：
1. **像素风格界面**：使用 8-bit 风格绘制数字金字塔，每个数字块显示当前累计值
2. **高亮机制**：
   - 红色边框：当前计算节点
   - 蓝色高亮：候选子节点（左下/右下）
   - 绿色数字：已确定的最优值
3. **步进控制**：
   - 空格键暂停/继续
   - 方向键控制单步执行速度
4. **音效反馈**：
   - 计算节点时播放 "blip" 音效
   - 层间切换时播放 8-bit 过渡音效

**交互示例**：
```javascript
// 伪代码示例
function visualize() {
    for(let layer = n-1; layer >= 0; layer--) {
        highlightLayer(layer, 'red');
        playSound('layer_start');
        
        for(let node = 0; node <= layer; node++) {
            highlightNode(node, 'yellow');
            let left = dp[layer+1][node];
            let right = dp[layer+1][node+1];
            
            animateArrow(layer+1, node);
            animateArrow(layer+1, node+1);
            
            dp[layer][node] += Math.max(left, right);
            updateDisplay();
            
            playSound('calculate');
            await delay(speed);
        }
    }
}
```

---

## 核心代码实现
**逆向递推完整代码**：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[1005][1005];

int main() {
    int n;
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<=i; j++)
            cin >> a[i][j];
            
    for(int i=n-2; i>=0; i--)
        for(int j=0; j<=i; j++)
            a[i][j] += max(a[i+1][j], a[i+1][j+1]);
    
    cout << a[0][0];
    return 0;
}
```

**一维数组优化版**：
```cpp
#include <cstdio>
int a[1005], n;

int main() {
    scanf("%d", &n);
    for(int i=n; i>=1; i--)
        for(int j=i; j<=n; j++)
            scanf("%d", &a[j]), a[j] += (a[j] > a[j+1]) ? a[j] : a[j+1];
    
    printf("%d", a[1]);
    return 0;
}
```

---

## 个人心得
1. **逆向思维训练**：解决动态规划问题时，尝试从终局状态反向推导，往往能发现更简洁的状态转移关系
2. **空间优化意识**：大规模数据场景下，滚动数组等优化手段能显著提升程序性能
3. **输入输出优化**：在 OJ 系统中，使用 `scanf/printf` 替代 `cin/cout` 可提升 IO 效率约 30%

---

通过本案例，可掌握动态规划在路径优化类问题的核心应用，后续遇到类似问题时，可快速迁移逆向递推思维和空间优化技巧。

---
处理用时：77.95秒