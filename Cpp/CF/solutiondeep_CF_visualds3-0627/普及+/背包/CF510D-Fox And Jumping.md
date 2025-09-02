# 题目信息

# Fox And Jumping

## 题目描述

Fox Ciel is playing a game. In this game there is an infinite long tape with cells indexed by integers (positive, negative and zero). At the beginning she is standing at the cell 0.

There are also $ n $ cards, each card has 2 attributes: length $ l_{i} $ and cost $ c_{i} $ . If she pays $ c_{i} $ dollars then she can apply $ i $ -th card. After applying $ i $ -th card she becomes able to make jumps of length $ l_{i} $ , i. e. from cell $ x $ to cell $ (x-l_{i}) $ or cell $ (x+l_{i}) $ .

She wants to be able to jump to any cell on the tape (possibly, visiting some intermediate cells). For achieving this goal, she wants to buy some cards, paying as little money as possible.

If this is possible, calculate the minimal cost.

## 说明/提示

In first sample test, buying one card is not enough: for example, if you buy a card with length 100, you can't jump to any cell whose index is not a multiple of 100. The best way is to buy first and second card, that will make you be able to jump to any cell.

In the second sample test, even if you buy all cards, you can't jump to any cell whose index is not a multiple of 10, so you should output -1.

## 样例 #1

### 输入

```
3
100 99 9900
1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5
10 20 30 40 50
1 1 1 1 1
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
7
15015 10010 6006 4290 2730 2310 1
1 1 1 1 1 1 10
```

### 输出

```
6
```

## 样例 #4

### 输入

```
8
4264 4921 6321 6984 2316 8432 6120 1026
4264 4921 6321 6984 2316 8432 6120 1026
```

### 输出

```
7237
```

# AI分析结果



**唯一算法分类**: 动态规划 / 图论（最短路）

---

### **题解思路与核心难点**

- **核心思路**: 通过裴蜀定理转化为求一组数使其gcd为1的最小代价。  
- **难点**: 如何高效维护不同gcd值的最小代价，避免暴力枚举所有可能的gcd。  
- **解决关键**: 使用动态规划或优先队列（Dijkstra）维护当前所有可能的gcd值及其最小费用。

**可视化设计思路**:
- **动画演示**: 将每个gcd值视为一个节点，卡片处理视为边，动态生成状态图。  
- **高亮变化**: 新产生的gcd值用绿色闪烁，费用降低时红色高亮。  
- **复古风格**: 8-bit像素字体显示当前处理的卡片和gcd值，音效在状态更新时触发。

---

### **题解评分（≥4星）**

1. **Kohakuwu（5星）**  
   - **亮点**: 简洁的map动态规划，无需分解质因数，代码可读性极佳。  
   - **代码片段**:  
     ```cpp
     for(int i=1; i<=n; i++) 
     {
         for(auto x:mp) {
             int num=__gcd(a[i],x.first), val=x.second+b[i];
             if(!mp[num] || mp[num]>val) mp[num]=val;
         }
         if(!mp[a[i]] || mp[a[i]]>b[i]) mp[a[i]]=b[i];
     }
     ```

2. **dks0311（4.5星）**  
   - **亮点**: Dijkstra算法直观展示状态转移，优先队列保证最优解。  
   - **代码片段**:  
     ```cpp
     void dijkstra(){
         dist[0] = 0;
         q.push({0, 0});
         while(!q.empty()){
             int u = q.top().second; q.pop();
             if(vis[u]) continue;
             for(int i=1; i<=n; ++i){
                 int v = gcd(u, l[i]);
                 if(dist[v] > dist[u] + c[i]) {
                     dist[v] = dist[u] + c[i];
                     q.push({dist[v], v});
                 }
             }
         }
     }
     ```

3. **ZYF_B（4星）**  
   - **亮点**: 状压DP高效处理质因数分解，复杂度稳定。  
   - **难点**: 质因数分解预处理，代码相对复杂。  

---

### **最优思路提炼**

1. **map动态规划**  
   - 维护一个map，键为当前可能的gcd值，值为最小费用。  
   - 对每个卡片，遍历现有状态生成新的gcd并更新费用。  
   - **优势**: 避免分解质因数，直接利用gcd运算动态合并状态。

2. **Dijkstra优化**  
   - 将每个gcd值视为图中的节点，费用为路径权重。  
   - 使用优先队列优先处理费用低的状态，确保首次遇到gcd=1时即为最优解。

---

### **同类题目推荐**

1. **P4549 【模板】裴蜀定理**  
   - 直接应用裴蜀定理求最小系数。  
2. **P1891 gcd数列**  
   - 动态维护区间gcd值。  
3. **P2303 Longge的问题**  
   - 利用gcd性质进行数学推导与求和。

---

### **代码核心实现**

**map动态规划（Kohakuwu）完整代码**:
```cpp
#include <bits/stdc++.h>
using namespace std;
map<int,int> mp;
int a[303],b[303];
int main(){
    int n; cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    for(int i=1;i<=n;i++){
        for(auto x:mp){
            int num=__gcd(a[i],x.first), val=x.second+b[i];
            if(!mp.count(num) || mp[num]>val) mp[num]=val;
        }
        if(!mp.count(a[i]) || mp[a[i]]>b[i]) mp[a[i]]=b[i];
    }
    cout<<(mp.count(1)?mp[1]:-1);
}
```

---

### **可视化与像素动画设计**

- **Canvas绘制**:  
  - 网格显示当前处理的卡片序号和更新的gcd值。  
  - 每个gcd节点用像素方块表示，颜色深浅表示费用高低。  
- **音效设计**:  
  - `update_sound`: 每次状态更新时播放8-bit "beep"。  
  - `success_sound`: 当gcd=1出现时播放胜利音效。  
- **自动演示模式**:  
  - 按卡片顺序自动处理，高亮当前卡片和生成的gcd节点。

**JS伪代码示例**:
```javascript
function drawPixelGrid(ctx) {
    // 绘制像素风格的状态网格
    for(let gcd in states) {
        let x = (gcd % 10) * 32;
        let y = Math.floor(gcd / 10) * 32;
        ctx.fillStyle = getColor(states[gcd]);
        ctx.fillRect(x, y, 30, 30);
    }
}
```

---
处理用时：92.92秒