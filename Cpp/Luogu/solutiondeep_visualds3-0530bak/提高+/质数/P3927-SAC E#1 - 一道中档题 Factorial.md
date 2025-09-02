# 题目信息

# SAC E#1 - 一道中档题 Factorial

## 题目背景

# 数据已修改

SOL君（炉石主播）和SOL菌（完美信息教室讲师）是好朋友。


## 题目描述

SOL君很喜欢阶乘。而SOL菌很喜欢研究进制。

这一天，SOL君跟SOL菌炫技，随口算出了n的阶乘。

SOL菌表示不服，立刻就要算这个数在k进制表示下末尾0的个数。

但是SOL菌太菜了于是请你帮忙。


## 说明/提示

对于20%的数据，n <= 1000000， k = 10

对于另外20%的数据，n <= 20， k <= 36

对于100%的数据，n <= 10^12，k <= 10^12

## update

1.一组数据

2.K不会==1

3.现在std没有爆long long

4.对数据有问题联系icy （建议大家不要面向数据编程）


## 样例 #1

### 输入

```
10 40```

### 输出

```
2```

# AI分析结果



# SAC E#1 - 一道中档题 Factorial 分析

## 唯一算法分类
数论（质因数分解与阶乘质因数计数）

---

## 题解思路与算法要点

### 核心思路
1. **问题转化**：末尾0的个数等价于 n! 能连续整除 k 的最大次数  
2. **质因数分解**：将 k 分解为质因数的幂次形式 $k = \prod p_i^{a_i}$  
3. **阶乘质因数计数**：计算 n! 中每个质因数 $p_i$ 的总次数 $c_i$  
4. **瓶颈分析**：最终答案为 $\min(\lfloor c_i/a_i \rfloor)$

### 解决难点
- **质因数分解优化**：当 k 达到 1e12 时，普通试除法需要遍历到 $\sqrt{k}$（约 1e6 次循环）  
- **大数阶乘处理**：使用 Legendre 公式 $c_i = \sum_{t=1}^\infty \lfloor n/p_i^t \rfloor$ 高效计算次数  
- **重复质因数合并**：需要将相同质因数的幂次累加（例如 k=8=2^3 需要合并统计）

---

## 题解评分（≥4星）

### 1. mrsrz 题解（★★★★★）
- **亮点**：  
  - 代码最简洁，仅 30 行实现核心逻辑  
  - 使用试除法直接分解质因数，对本题数据完全够用  
  - 使用 `now /= p[i]` 代替 `p[i]^t` 避免溢出  
- **个人心得**：在质因数分解时直接处理重复因子，避免后续合并

### 2. GoAway 题解（★★★★）
- **亮点**：  
  - 独立封装 `frequency` 函数提高可读性  
  - 特判 k=1 的情况（但题目已说明 k≠1）  
- **优化点**：质因数分解可合并重复因子

### 3. peterwuyihong 题解（★★★★）
- **亮点**：  
  - 使用 Pollard-Rho 算法处理极大质因数（虽然本题不需要）  
  - 通过质因数分解与阶乘计数分离，代码模块化清晰  
- **缺点**：代码复杂度较高，可读性略低

---

## 最优思路提炼
1. **质因数分解试除法**：遍历到 $\sqrt{k}$，每找到一个质因数就除尽  
   ```cpp
   for(long long i=2; i*i<=k; ++i)
     if(k%i==0) {
         p[++cnt] = i;
         while(k%i==0) ++c[cnt], k/=i;
     }
   if(k>1) p[++cnt] = k, c[cnt] = 1;
   ```
2. **Legendre 公式实现**：累加每层除法的结果  
   ```cpp
   long long t = 0, now = n;
   while(now) t += now /= p[i];
   ```
3. **结果取最小值**：每个质因数的可用次数除以其幂次  
   ```cpp
   t /= c[i];
   if(t < ans) ans = t;
   ```

---

## 同类型题与算法套路
- **通用解法**：  
  - 阶乘质因数计数 → 计算组合数因数个数  
  - 质因数分解 → 最大公约数/最小公倍数问题  
- **类似题目**：  
  1. **洛谷 P1739**（求 n! 末尾0的个数，k=10）  
  2. **CF1114C**（与本题完全相同）  
  3. **SP4941 FACT1**（大数质因数分解）

---

## 可视化与算法演示设计

### 核心动画流程
1. **质因数分解阶段**：  
   - **像素风格**：用不同颜色方块表示质因数，右侧显示当前分解进度  
   - **音效**：每次找到质因数时播放 "blip" 音效  
   ```javascript
   function playSound(type) {
     if(type === 'factor') new Audio('blip.wav').play();
     if(type === 'done') new Audio('success.wav').play();
   }
   ```
2. **阶乘计数阶段**：  
   - **网格动画**：展示 n 被连续除以 $p_i^t$ 的过程，高亮当前除数  
   - **动态计数器**：右侧显示累计的质因数次数  
3. **结果比较阶段**：  
   - **柱状图对比**：用不同高度柱子表示各质因数的 $\lfloor c_i/a_i \rfloor$  
   - **最小值闪烁**：最终答案柱子以红色闪烁，播放胜利音效

### 复古像素化实现
- **Canvas 绘制**：  
  ```javascript
  const ctx = canvas.getContext('2d');
  // 绘制质因数方块
  function drawFactor(x, y, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*16, y*16, 14, 14);
  }
  ```
- **自动演示模式**：  
  ```javascript
  let autoPlay = setInterval(() => {
    if(!nextStep()) clearInterval(autoPlay);
  }, 1000);
  ```

---

## 个人心得摘录
> "计算质因数次数时容易漏掉 $p^2, p^3$ 等高次项，必须用 while 循环累加除法的结果。" —— mrsrz  
> "特判 k=1 的情况虽然题目不存在，但能避免某些极端错误。" —— GoAway

---

## 核心代码片段
```cpp
#include<cstdio>
using namespace std;
long long n,k,p[200002],c[200002],ans;
int cnt;
int main(){
    scanf("%lld%lld",&n,&k);
    for(long long i=2; i*i<=k; ++i)
        if(k%i==0){
            p[++cnt] = i;
            while(k%i==0) ++c[cnt], k/=i;
        }
    if(k>1) p[++cnt]=k, c[cnt]=1;
    ans = 1e18;
    for(int i=1; i<=cnt; ++i){
        long long t=0, now=n;
        while(now) t += now /= p[i];
        t /= c[i];
        if(t < ans) ans = t;
    }
    printf("%lld\n",ans);
    return 0;
}
```

---
处理用时：89.61秒