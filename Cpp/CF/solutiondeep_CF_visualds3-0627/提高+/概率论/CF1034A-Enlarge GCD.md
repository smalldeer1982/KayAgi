# 题目信息

# Enlarge GCD

## 题目描述

Mr. F has $ n $ positive integers, $ a_1, a_2, \ldots, a_n $ .

He thinks the greatest common divisor of these integers is too small. So he wants to enlarge it by removing some of the integers.

But this problem is too simple for him, so he does not want to do it by himself. If you help him, he will give you some scores in reward.

Your task is to calculate the minimum number of integers you need to remove so that the greatest common divisor of the remaining integers is bigger than that of all integers.

## 说明/提示

In the first example, the greatest common divisor is $ 1 $ in the beginning. You can remove $ 1 $ so that the greatest common divisor is enlarged to $ 2 $ . The answer is $ 1 $ .

In the second example, the greatest common divisor is $ 3 $ in the beginning. You can remove $ 6 $ and $ 9 $ so that the greatest common divisor is enlarged to $ 15 $ . There is no solution which removes only one integer. So the answer is $ 2 $ .

In the third example, there is no solution to enlarge the greatest common divisor. So the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
1 2 4
```

### 输出

```
1```

## 样例 #2

### 输入

```
4
6 9 15 30
```

### 输出

```
2```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
-1```

# AI分析结果



---

## 算法分类
数论（质因数分解、筛法）

---

## 综合分析与结论

### 核心算法流程
1. **预处理阶段**：  
   - 计算所有数的初始 GCD `g`  
   - 将所有数除以 `g`，转化为求新数组 GCD > 1 的问题  
   - 统计处理后的数值分布（值域范围）  

2. **筛法优化**：  
   - 使用埃氏筛或线性筛预处理质数  
   - 对于每个质数 `p`，统计其在新数组中的倍数出现次数 `cnt`  
   - 最少删除数 `ans = min(ans, n - cnt)`  

3. **关键难点解决**：  
   - **大值域处理**：通过筛法将质数倍数统计复杂度优化至 O(m log log m)  
   - **重复质因子处理**：通过预处理最小质因子加速分解过程  

### 可视化设计思路
- **动画方案**：  
  - **质数高亮**：用红色标记当前处理的质数 `p`  
  - **倍数扫描**：蓝色闪烁显示当前质数 `p` 的倍数（如 `p, 2p, 3p...`）  
  - **计数器更新**：右侧面板实时显示每个质数的 `cnt` 值和对应的 `n - cnt`  
- **复古风格**：  
  - **8位像素网格**：数值用 16x16 像素块表示，质数显示为绿色，倍数扫描时闪烁黄色  
  - **音效设计**：  
    - 质数选中时播放 "beep" 音效  
    - 找到更优解时播放上升音阶  
- **交互控制**：  
  - 支持暂停/继续观察特定质数的统计过程  
  - 可切换自动演示模式（AI 按质数从小到大扫描）

---

## 题解清单（≥4星）

### 1. Siyuan（★★★★★）  
**亮点**：  
- 优化思路清晰，将问题转化为求新数组 GCD > 1  
- 使用埃氏筛统计质数倍数的设计简洁高效  
- 代码中 `a[i] /= d` 预处理巧妙消除原 GCD 影响  

**关键代码**：  
```cpp
for(int j=x;j<=mx;j+=x) num+=cnt[j];
ans = min(ans, n - num);
```

### 2. Acc_Robin（★★★★）  
**亮点**：  
- 补充严谨的复杂度分析（调和级数优化）  
- 线性筛预处理质数，避免重复标记  
- 代码中 `vis[j*i]=1` 同步完成筛和统计  

**核心片段**：  
```cpp
for(int j=1;p[i]*j<=mx;j++) res+=buc[p[i]*j];
ans = max(ans, res);
```

### 3. kimi0705（★★★★）  
**亮点**：  
- 代码极简风格，将筛与统计合并到同一循环  
- 利用 `vis[j]` 标记质数的同时统计倍数  
- 值域处理时直接取 `maxx` 避免冗余计算  

**巧妙设计**：  
```cpp
if(!vis[i]) {
    for(int j=i; j<=maxx; j+=i) 
        vis[j] = 1, Cnt += cnt[j];
}
```

---

## 最优思路/技巧提炼

### 关键技巧
1. **GCD 预处理**：  
   - 将问题转化为求新数组的 GCD > 1，消除原 GCD 的干扰  

2. **筛法统计**：  
   - 对处理后的数值进行质数筛，在筛的过程中统计每个质数的倍数数量  

3. **最小质因子分解**：  
   - 预处理每个数的最小质因子，分解时复杂度降至 O(log a_i)  

### 思维突破点
- **逆向思维**：通过计算最少删除数等价于求最多保留数的质因子  
- **值域压缩**：通过除以 GCD 缩小数值范围，使筛法可行  

---

## 同类型题与算法套路

### 类似问题特征
- 需要处理大值域下的质数相关统计  
- 涉及通过删除/保留元素改变集合的数论性质  

### 推荐题目
1. [CF1047C] Enlarge GCD（本题的变式加强版）  
2. [洛谷 P1029] 最大公约数和最小公倍数问题  
3. [洛谷 P1072] Hankson 的趣味题  

---

## 可视化演示代码片段（复古风格）

```javascript
// Canvas 绘制质数网格
function drawGrid() {
    for (let i = 2; i <= maxx; i++) {
        const x = (i % 20) * 16;
        const y = Math.floor(i / 20) * 16;
        // 质数显示为绿色，非质数灰色
        ctx.fillStyle = isPrime[i] ? '#00ff00' : '#444444';
        ctx.fillRect(x, y, 16, 16);
    }
}

// 扫描质数倍数时的动画
function highlightMultiples(p) {
    for (let j = p; j <= maxx; j += p) {
        const x = (j % 20) * 16;
        const y = Math.floor(j / 20) * 16;
        ctx.fillStyle = '#ffff00'; // 黄色高亮
        ctx.fillRect(x, y, 16, 16);
        playSound('beep', 500 + j * 10); // 音调递增
    }
}
```

---

## 个人心得摘录

### Siyuan 的调试经验
> "在优化筛法时发现，若直接统计每个质数的倍数，需要处理的最大值域为 1.5e7，采用埃氏筛的调和级数优化是唯一可行方案"

### Acc_Robin 的顿悟
> "意识到初始 GCD 的预处理可以极大简化问题，这步转化是后续所有优化的基础"

---

## 核心算法代码实现

### Siyuan 优化思路完整代码
```cpp
#include <cstdio>
#include <algorithm>

const int N=3e5+5,M=1.5e7+5;
int n,a[N],cnt[M];
bool vis[M];

int gcd(int x,int y) {
    return y?gcd(y,x%y):x;
}

int main() {
    scanf("%d",&n);
    int d=0,mx=0;
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        d = gcd(d,a[i]);
    }
    for(int i=1;i<=n;i++) {
        a[i] /= d;
        mx = std::max(mx,a[i]);
        cnt[a[i]]++;
    }
    
    int ans=n;
    for(int i=2;i<=mx;i++) {
        if(!vis[i]) {
            int sum=0;
            for(int j=i;j<=mx;j+=i) {
                vis[j] = true;    // 标记非质数
                sum += cnt[j];   // 统计倍数
            }
            if(sum) ans = std::min(ans, n-sum);
        }
    }
    printf("%d\n",ans==n?-1:ans);
    return 0;
}
```

**核心思想**：  
- 通过埃氏筛的标记过程同步完成质数判断和倍数统计  
- `vis[j]` 双重功能：既标记非质数，又避免重复统计  
- 最终答案通过 `n - sum` 计算最少删除数

---
处理用时：86.03秒