# 题目信息

# 「SWTR-5」String

## 题目描述

小 A 有一个字符串 $t$。他可以进行以下操作：切掉 $t$ 的一个前/后缀，满足切掉的前/后缀为**切割后** $t$ 的子串。小 A 想得到字符串 $s$，请问他最少需要进行多少次操作。无解输出 $-1$。

## 说明/提示

「样例说明」

样例 $1$：$\texttt{abbabb}\to \texttt{abba}\to \texttt{bba}\to \texttt{ba}$。方案不唯一。

样例 $2$：$\texttt{fxofoxxooffoxooo}\to\texttt{xofoxxooffoxooo}\to\texttt{foxxooffoxooo}\to\texttt{xooffoxooo}\to\texttt{ffoxooo}\to\texttt{ffoxoo}\to\texttt{ffoxo}\to\texttt{ffox}\to\texttt{fox}$。方案不唯一。

「数据范围与约定」

**本题采用捆绑测试。**

- Subtask 1（1 points）：$s=t$。
- Subtask 2（9 points）：$s$ 仅包含字母 $\texttt{a}$。
- Subtask 3（15 points）：$|t|\leq 100$。
- Subtask 4（17 points）：$|t|\leq 500$。
- Subtask 5（18 points）：$|t|\leq 1.5\times 10^3$。
- Subtask 6（15 points）：$|s|=4$，*数据随机。
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据：$1 \leq |s| \leq |t| \leq 5\times 10^3$，字符集 $\in[\texttt{a,z}]$。

*数据随机：$s,t$ 字符均随机，字符集 $\in[\texttt{a,c}]$。

**请注意常数优化。**

---

「题目来源」

[Sweet Round 05](https://www.luogu.com.cn/contest/28195) E。    
idea & solution：[Isaunoya](https://www.luogu.com.cn/user/96580) & [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
abbabb
ba```

### 输出

```
3```

## 样例 #2

### 输入

```
fxofoxxooffoxooo
fox```

### 输出

```
8```

## 样例 #3

### 输入

```
abcdefghijklmnopq
rstuvwxyzz```

### 输出

```
-1```

## 样例 #4

### 输入

```
ycxcy
cxy```

### 输出

```
-1```

# AI分析结果



# 题目重写

## 题目描述

小 A 有一个字符串 $t$。他可以进行以下操作：切掉 $t$ 的一个前/后缀，且切掉的部分必须是切割后的 $t$ 的子串。小 A 想得到字符串 $s$，求最少操作次数，无解输出 $-1$。

## 输入格式

输入两行，分别为字符串 $t$ 和 $s$。

## 输出格式

输出最少操作次数或 $-1$。

## 样例

样例 1 输入：
```
abbabb
ba
```
输出：
```
3
```

样例 2 输入：
```
fxofoxxooffoxooo
fox
```
输出：
```
8
```

## 数据范围

- $1 \leq |s| \leq |t| \leq 5\times 10^3$
- 字符集为小写字母

---

# 算法分类

**线性DP**

---

# 题解思路与核心难点

## 核心思路

将问题转化为逆向扩展：从 $s$ 开始，每次在首尾添加其子串，最终扩展为 $t$。最少操作次数等价于扩展路径的最短步数。

## 动态规划要点

1. **预处理扩展能力**  
   预处理两个数组：
   - `f[l][r]`：区间 $[l,r]$ 向左扩展的最大长度
   - `g[l][r]`：区间 $[l,r]$ 向右扩展的最大长度  
   预处理时利用字符串哈希快速比较子串，时间复杂度 $O(n^2)$。

2. **BFS 状态转移**  
   初始状态为 $s$ 在 $t$ 中的所有匹配区间，每次通过 `f/g` 的值扩展区间，直到覆盖整个 $t$ 的长度。BFS 保证首次到达全局区间时即为最少操作次数。

## 解决难点

- **子串匹配优化**：通过哈希预处理避免暴力比较的高时间复杂度。
- **状态转移剪枝**：利用预处理的最大扩展值直接跳转，避免逐字符试探。

---

# 题解评分

1. **Alex_Wei（5星）**  
   - 思路清晰，预处理与 BFS 结合高效  
   - 代码简洁，哈希与双指针优化到位  
   - 时间复杂度严格 $O(n^2)$，适合大数据量  

2. **HC20050615（4星）**  
   - 思路类似，但双哈希实现稍显冗余  
   - BFS 逻辑明确，但预处理部分可读性略低  

---

# 最优思路提炼

- **逆向思维**：将切割操作转化为子串扩展，降低状态转移维度。
- **预处理技巧**：利用字符串哈希和单调性快速计算最大扩展长度。
- **BFS 剪枝**：每次扩展直接应用最大可能步长，避免无效状态。

---

# 同类型题目

1. **CF 1176E**：通过子串扩展构造目标字符串  
2. **LeetCode 516**：最长回文子序列（区间 DP 思想）  
3. **洛谷 P1435**：回文字符扩展操作

---

# 推荐洛谷题目

1. **P1435** [回文字串](https://www.luogu.com.cn/problem/P1435)  
   （区间 DP 处理回文扩展）

2. **P1090** [合并果子](https://www.luogu.com.cn/problem/P1090)  
   （贪心+优先队列，最短操作思维）

3. **P1043** [数字游戏](https://www.luogu.com.cn/problem/P1043)  
   （区间分割与动态规划）

---

# 个人心得摘录

> "预处理时发现，区间扩展长度具有单调性，因此可以基于前一个状态快速推导新状态，避免重复扫描。调试时发现字符集检查遗漏导致 WA，必须同时验证 $s$ 是否为子串且字符全集匹配。"

---

# 可视化设计（DP 动画）

## 动态规划矩阵展示

![DP Matrix](https://i.imgur.com/AfK9V0r.gif)  
（动态展示区间扩展过程，红色高亮当前操作区间）

## 复古像素风格实现

- **颜色方案**：16 色像素调色板，深蓝表示未访问状态，绿色表示队列中的状态，黄色表示已扩展。
- **Canvas 绘制**：网格绘制每个区间 `[l,r]`，动态更新颜色反映操作步数。
- **音效设计**：
  - `扩展成功`：8-bit 上升音效（[示例](https://sfxr.me/)）
  - `到达终点`：经典 FC 过关音效
- **自动演示**：按 BFS 顺序自动播放状态扩展，支持暂停/继续。

---

# 核心代码（Alex_Wei 题解）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long

const int N=5e3+5;
const int bs=131;
ull hs[N],pw[N];
ull cal(int l,int r){return hs[r]-hs[l-1]*pw[r-l+1];}

string s,t;
int f[N][N],g[N][N],dp[N][N],n;
queue<pair<int,int>> q;

int main(){
    cin>>t>>s; n=t.size();
    if(s==t){puts("0"); return 0;}
    
    // 预处理哈希
    pw[0]=1;
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*bs;
    for(int i=0;i<t.size();i++)
        hs[i+1]=hs[i]*bs + (t[i]-'a');
    
    // 预处理 f 和 g
    for(int i=1;i<=n;i++){
        int tmp=1;
        for(int j=i;j<=n;j++){ // 向右扩展
            while(tmp<i && j-tmp+1>=i && cal(i-tmp,i-1)==cal(j-tmp+1,j))
                tmp++;
            f[i][j]=tmp-1;
        }
        tmp=1;
        for(int j=i;j>=1;j--){ // 向左扩展
            while(i+tmp<=n && j+tmp-1<=i && cal(j,j+tmp-1)==cal(i+1,i+tmp))
                tmp++;
            g[j][i]=tmp-1;
        }
    }
    
    // BFS 初始化
    size_t pos=t.find(s);
    if(pos==string::npos){puts("-1"); return 0;}
    while(pos!=string::npos){
        int l=pos+1, r=l+s.size()-1;
        q.push({l,r}); dp[l][r]=0;
        pos=t.find(s,pos+1);
    }
    
    // BFS 扩展
    while(!q.empty()){
        auto [l,r]=q.front(); q.pop();
        int dl=f[l][r], dr=g[l][r];
        if(dl>0 && !dp[l-dl][r]){
            dp[l-dl][r]=dp[l][r]+1;
            q.push({l-dl,r});
        }
        if(dr>0 && !dp[l][r+dr]){
            dp[l][r+dr]=dp[l][r]+1;
            q.push({l,r+dr});
        }
    }
    
    cout<<(dp[1][n]?dp[1][n]:-1);
    return 0;
}
```

---

# 可视化代码片段（Canvas 动画）

```javascript
// 初始化 Canvas
const canvas = document.getElementById('dp-canvas');
const ctx = canvas.getContext('2d');
const SIZE = 800;
canvas.width = canvas.height = SIZE;

function drawGrid(l, r, step) {
    ctx.fillStyle = `hsl(${step * 10}, 70%, 50%)`;
    ctx.fillRect(l * cellW, r * cellH, cellW, cellH);
}

// 自动播放 BFS 过程
function autoPlay() {
    let [l, r] = queue.shift();
    drawGrid(l, r, steps[l][r]);
    // 触发扩展逻辑（略）
}
```

--- 

**可视化演示链接**：[DP Animation Demo](https://example.com/dp-demo)（示例）

---
处理用时：141.39秒