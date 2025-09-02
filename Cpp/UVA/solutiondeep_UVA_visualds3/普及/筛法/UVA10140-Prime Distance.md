# 题目信息

# Prime Distance

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=13&page=show_problem&problem=1081

[PDF](https://uva.onlinejudge.org/external/101/p10140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA10140/7fac8d7bdf18ec6e0fd2914c1623eee77be89ef3.png)

## 样例 #1

### 输入

```
2 17
14 17```

### 输出

```
2,3 are closest, 7,11 are most distant.
There are no adjacent primes.```

# AI分析结果



## 算法分类
筛法

## 综合分析与结论

### 核心思路与难点
题目要求在极大区间 [L,R] (R-L ≤1e6) 内寻找相邻质数的最小/最大间距。关键难点在于：
1. 区间端点可达 2^31，无法直接存储整个区间质数表
2. 需要高效筛选区间内质数

所有优质题解均采用**二次筛法**：
1. 预处理 2~√R 的质数集合（线性筛/埃筛）
2. 对每个预处理的质数 p，标记区间内所有 p 的倍数
3. 未被标记的即为区间质数，遍历比较相邻间距

### 题解评分（≥4星）

#### 1. Siyuan（⭐⭐⭐⭐⭐）
- 思路清晰：线性筛预处理 + 二次筛法
- 代码规范：正确处理 L=1 的特殊情况
- 高效优化：j 从 l/p 开始，避免重复计算

#### 2. 冒泡ioa（⭐⭐⭐⭐）
- 理论完整：引用《算法进阶指南》复杂度分析
- 边界处理：增加 `p*i - l < 0` 判断避免越界
- 可读性强：变量命名规范，逻辑分层清晰

#### 3. WLR__jr（⭐⭐⭐⭐）
- 代码简洁：仅使用埃筛预处理
- 高效实现：通过 `j = l/p[i]` 快速定位标记起点
- 内存优化：用 `b[i-L]` 偏移存储区间状态

### 最优思路提炼
1. **质数倍数标记法**  
   对每个质数 p，计算区间内第一个 ≥L 的倍数 `start = max(p*2, ⌈L/p⌉*p)`，标记所有 `start, start+p...` 为合数

2. **偏移存储技巧**  
   用 `vis[x-L]` 表示区间数 x 的状态，将任意区间映射到 [0, R-L] 的数组下标

3. **线性筛预处理**  
   预处理 √(2^31) ≈ 46340 内的质数，保证二次筛法的正确性

```cpp
// 核心代码片段（Siyuan 版）
void init() { // 线性筛预处理小质数
    for(int i=2;i<N;++i) {
        if(!flg[i]) p[++tot]=i;
        for(int j=1;j<=tot&&i*p[j]<N;++j) {
            flg[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
void solve() {
    for(int i=1;i<=tot;++i) { // 二次筛法标记区间
        for(long long j=l/p[i];j*p[i]<=r;++j) {
            long long x = p[i]*j;
            if(j>1 && x>=l) vis[x-l] = 0; // 偏移标记
        }
    }
}
```

### 可视化设计
1. **像素动画演示**  
   ![筛法可视化](https://i.imgur.com/9bGjK8m.gif)  
   - 黄色方块：当前处理的预处理质数 p  
   - 红色闪烁：正在标记的 p 的倍数  
   - 绿色高亮：剩余未被标记的质数

2. **8-bit 音效设计**  
   ```javascript
   // 伪代码示例
   function playSound(type) {
     const ctx = new AudioContext();
     const osc = ctx.createOscillator();
     osc.frequency.value = type === 'mark' ? 440 : 880; // 标记/成功不同音高
     osc.connect(ctx.destination);
     osc.start(); osc.stop(ctx.currentTime + 0.1);
   }
   ```

### 相似题目
1. P1835 素数密度（区间筛法模板）
2. P1217 [USACO1.5]回文质数（区间筛法+回文判断）
3. P3383 【模板】线性筛素数（预处理练习）

---

## 完整题解代码（Siyuan 版）
```cpp
#include <cstdio>
#include <cstring>

const int N=1e6+5;
int tot,p[N];
bool flg[N],vis[N];

void init() {
    for(int i=2;i<N;++i) {
        if(!flg[i]) p[++tot]=i;
        for(int j=1;j<=tot&&i*p[j]<N;++j) {
            flg[i*p[j]]=1;
            if(i%p[j]==0) break;
        }
    }
}
void chkmin(long long &x,long long a,long long b,long long &p1,long long &p2) {
    if(x>b-a) x=b-a,p1=a,p2=b;
}
void chkmax(long long &x,long long a,long long b,long long &p1,long long &p2) {
    if(x<b-a) x=b-a,p1=a,p2=b;
}
int main() {
    init();
    long long l,r;
    while(~scanf("%lld%lld",&l,&r)) {
        memset(vis,1,sizeof(vis));
        if(l==1) vis[0]=0;
        for(int i=1;i<=tot;++i) {
            for(long long j=l/p[i];j*p[i]<=r;++j) {
                long long x=p[i]*j;
                if(j>1&&x>=l) vis[x-l]=0;
            }
        }
        long long p=0,p1,p2,p3,p4,mn=1LL<<60,mx=0;
        for(long long i=l;i<=r;++i) {
            if(!vis[i-l]) continue;
            if(p) chkmin(mn,p,i,p1,p2),chkmax(mx,p,i,p3,p4);
            p=i;
        }
        if(!mx) puts("There are no adjacent primes.");
        else printf("%lld,%lld are closest, %lld,%lld are most distant.\n",p1,p2,p3,p4);
    }
    return 0;
}
```

---
处理用时：82.50秒