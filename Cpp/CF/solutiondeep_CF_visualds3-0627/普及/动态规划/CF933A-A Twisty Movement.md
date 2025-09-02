# 题目信息

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出

```
9
```

# AI分析结果



# 题目重写

## 题目描述

龙象征着智慧、力量和财富。在农历新年，人们用竹条和布料制作龙形道具，用长杆高低起伏地挥舞，模仿飞龙在天的姿态。

将低举杆子的表演者记为 $1$，高举的记为 $2$。因此，表演队列可以用序列 $a_{1},a_{2},...,a_{n}$ 表示。

Tommy 也在队列中。他想选择一个区间 $[l,r]$（$1 \leq l \leq r \leq n$），反转其中的元素 $a_{l},a_{l+1},...,a_{r}$，使得新序列的最长非递减子序列长度最大化。

非递减子序列定义为下标序列 $p_{1},p_{2},...,p_{k}$，满足 $p_{1}<p_{2}<...<p_{k}$ 且 $a_{p1} \leq a_{p2} \leq ... \leq a_{pk}$。子序列长度即为 $k$。

## 说明/提示

第一个样例中，反转区间 $[2,3]$ 得到 $[1,1,2,2]$，最长非递减子序列长度为 $4$。

第二个样例中，反转区间 $[3,7]$ 得到 $[1,1,1,1,2,2,2,2,2,1]$，最长非递减子序列长度为 $9$。

## 样例 #1

### 输入
```
4
1 2 1 2
```

### 输出
```
4
```

## 样例 #2

### 输入
```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出
```
9
```

---

# 算法分类
**线性DP**

---

# 综合分析与结论

## 核心思路与难点
题目本质是寻找最优翻转区间，使得最长非递减子序列最大化。关键突破点在于发现最终序列可分解为四段结构：
```
[1...1][2...2][1...1][2...2]
```
通过翻转中间两段即可形成连续递增序列。动态规划维护四个状态，分别表示前i个元素中：
1. 仅包含第一段（全1）
2. 包含前两段（1+2）
3. 包含前三段（1+2+1）
4. 包含全部四段（1+2+1+2）

## 状态转移方程
```python
f1 = f1 + (a[i] == 1)
f2 = max(f1, f2 + (a[i] == 2))
f3 = max(f2, f3 + (a[i] == 1))
f4 = max(f3, f4 + (a[i] == 2))
```

## 可视化设计
采用网格动画展示四状态动态变化：
![状态转移示意图](https://cdn.luogu.com.cn/upload/image_hosting/1jz0x3l4.gif)
- **颜色编码**：黄色表示1触发的更新，蓝色表示2触发的更新
- **步进控制**：可调节速度观察每个元素的处理过程
- **音效提示**：状态提升时播放8-bit上升音效，保持状态时播放短促提示音

---

# 题解清单 (≥4星)

1. **浅色调（解法二）★★★★★**  
   核心亮点：四状态线性DP，时空复杂度O(n)，代码极简  
   ```cpp
   f[1]+=(x==1);
   f[2]=max(f[1],f[2]+(x==2));
   f[3]=max(f[2],f[3]+(x==1));
   f[4]=max(f[3],f[4]+(x==2));
   ```

2. **蒟蒻丁 ★★★★☆**  
   亮点：通过分四组理论推导状态转移，代码与注释结合清晰  
   ```cpp
   // 状态转移体现分组逻辑
   f[3]=max(f[2],f[3]+(x==1));
   ```

3. **Karry5307 ★★★★**  
   特色：前后缀分解思路，使用双向DP预处理  
   ```cpp
   // 预处理前后缀最大值
   for(int i=n;i;i--) 
       x[i]==2?g[i][2]++:g[i][1]=max(g[i+1][1],g[i+1][2])+1;
   ```

---

# 核心代码实现

**最优解代码（浅色调解法二）**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,f[5];

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&x);
        f[1]+=(x==1);
        f[2]=max(f[1],f[2]+(x==2));
        f[3]=max(f[2],f[3]+(x==1));
        f[4]=max(f[3],f[4]+(x==2));
    }
    cout<<f[4];
}
```

**代码要点**
- 仅用四个变量维护状态，空间复杂度O(1)
- 每步转移仅需O(1)时间，总时间复杂度O(n)
- 巧妙利用max函数自动处理状态继承

---

# 同类型题目推荐
1. P1091 合唱队形（双向LIS）
2. P1280 尼克的任务（线性DP状态设计）
3. P1140 相似基因（二维线性DP）

---

# 可视化代码片段（Canvas动画）

```javascript
// 初始化四状态展示
const states = [0, 0, 0, 0]; 
const colors = ['#FFD700', '#87CEEB', '#FF69B4', '#32CD32'];

function drawDPFrame(ctx, step) {
    ctx.clearRect(0, 0, 400, 200);
    states.forEach((val, idx) => {
        ctx.fillStyle = colors[idx];
        ctx.fillRect(100*idx, 100-val*5, 80, val*5); // 高度映射数值
        ctx.fillText(`F${idx+1}=${val}`, 100*idx+10, 180);
    });
}

// 音效触发
function playSound(pitch) {
    const osc = audioCtx.createOscillator();
    osc.frequency.value = pitch;
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(audioCtx.currentTime + 0.1);
}
```

---

# 个人心得摘录
> "考试时先想到线段树解法，后来发现元素只有1和2的特性，突然意识到可以拆分为四段结构，这种降维思考是关键突破" —— 浅色调  
> "调试时发现第三个状态总是不更新，后来才明白转移条件写反了1和2的判断，这种细节决定成败" —— gesong

---

**通过本案例可以深刻理解：当题目存在特殊限制（如元素取值有限）时，通过结构分解往往能大幅简化问题，而动态规划的状态设计需要紧扣问题本质特征。**

---
处理用时：82.88秒