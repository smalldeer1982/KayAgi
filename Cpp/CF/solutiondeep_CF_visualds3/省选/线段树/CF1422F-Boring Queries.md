# 题目信息

# Boring Queries

## 题目描述

Yura owns a quite ordinary and boring array $ a $ of length $ n $ . You think there is nothing more boring than that, but Vladik doesn't agree!

In order to make Yura's array even more boring, Vladik makes $ q $ boring queries. Each query consists of two integers $ x $ and $ y $ . Before answering a query, the bounds $ l $ and $ r $ for this query are calculated: $ l = (last + x) \bmod n + 1 $ , $ r = (last + y) \bmod n + 1 $ , where $ last $ is the answer on the previous query (zero initially), and $ \bmod $ is the remainder operation. Whenever $ l > r $ , they are swapped.

After Vladik computes $ l $ and $ r $ for a query, he is to compute the least common multiple (LCM) on the segment $ [l; r] $ of the initial array $ a $ modulo $ 10^9 + 7 $ . LCM of a multiset of integers is the smallest positive integer that is divisible by all the elements of the multiset. The obtained LCM is the answer for this query.

Help Vladik and compute the answer for each query!

## 说明/提示

Consider the example:

- boundaries for first query are $ (0 + 1) \bmod 3 + 1 = 2 $ and $ (0 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 2] $ is equal to $ 6 $ ;
- boundaries for second query are $ (6 + 3) \bmod 3 + 1 = 1 $ and $ (6 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 1] $ is equal to $ 2 $ ;
- boundaries for third query are $ (2 + 2) \bmod 3 + 1 = 2 $ and $ (2 + 3) \bmod 3 + 1 = 3 $ . LCM for segment $ [2, 3] $ is equal to $ 15 $ ;
- boundaries for fourth query are $ (15 + 2) \bmod 3 + 1 = 3 $ and $ (15 + 3) \bmod 3 + 1 = 1 $ . LCM for segment $ [1, 3] $ is equal to $ 30 $ .

## 样例 #1

### 输入

```
3
2 3 5
4
1 3
3 3
2 3
2 3```

### 输出

```
6
2
15
30```

# AI分析结果


### 💡 Kay的C++算法解析：Boring Queries 深入学习指南 💡

**题目解读与核心算法识别**  
✨ **本题主要考察**：`根号分治 + 主席树 + ST表`  
🗣️ **初步分析**：  
> 解决"Boring Queries"的关键是将质因数按值域分为两类：  
> - **小质数（≤447）**：仅有87个，用ST表高效查询区间最大指数（类似多个小雷达同时扫描区间峰值）。  
> - **大质数（>447）**：每个数至多含一个，转化为区间不同值的乘积问题（类似收集彩色宝石，重复的只算一次）。  
>  
> **核心难点**在于：  
> 1. 小质数需87个ST表，空间优化至关重要（指数用char存储）  
> 2. 大质数需主席树动态去重（时光倒流式消除旧贡献）  
>  
> **可视化设计思路**：  
> - 像素风格网格代表序列，质因数用不同颜色方块  
> - ST表构建：自底向上合并时显示像素块叠加动画  
> - 主席树修改：显示质因数"宝石"移动路径，旧位置打叉（逆元消除），新位置高亮  
> - 音效：质因数出现（叮）、消除（咔）、查询成功（胜利旋律）

---

### 2. 精选优质题解参考
**题解一（louhao088）**  
* **亮点**：  
  - 统一用主席树处理所有质因数，逻辑简洁  
  - 巧妙利用逆元动态消除重复贡献  
  - 质因子分解与维护高度模块化  
* **代码片段**：  
  ```cpp
  while(f[x]) { // 动态分解质因数
      int k=f[x],t=1;
      while(x%k==0) {
          t*=k; x/=k;
          if(s[t]) Rt[i]=merge(Rt[i],1,n,s[t],inv[k]); // 消除旧贡献
          s[t]=i; // 记录新位置
      }
      Rt[i]=merge(Rt[i],1,n,i,t); // 添加新贡献
  }
  ```

**题解二（IntrepidStrayer）**  
* **亮点**：  
  - 经典根号分治，效率平衡  
  - ST表用char存储指数，极大节省空间  
  - 主席树去重逻辑清晰（类似HH的项链）  
* **代码片段**：  
  ```cpp
  // 大质数处理
  if(a[i]>1) {
      if(pre[a[i]]) modify(rt[i],1,n,pre[a[i]],inv[a[i]]); // 逆元消除
      modify(rt[i],1,n,i,a[i]); // 当前添加
      pre[a[i]]=i;
  }
  ```

---

### 3. 核心难点辨析与解题策略
1. **小质数空间优化**  
   * **分析**：87个ST表若用int导致MLE → char存指数  
   * 💡学习笔记：值域小时，类型降维是空间优化利器  

2. **大质数去重时机**  
   * **分析**：主席树修改需同步移除旧贡献 → 逆元抵消  
   * 💡学习笔记：乘法逆元是模下去重的数学基础  

3. **强制在线处理**  
   * **分析**：无法离线排序 → 主席树"时光回溯"特性支持在线  
   * 💡学习笔记：可持久化结构是强制在线的标准武器  

**✨ 解题技巧总结**  
- **根号分治**：按质因数大小分类击破  
- **ST表峰值压缩**：小质数指数用char，空间降75%  
- **主席树时光机**：当前版本消除过去版本的贡献  

---

### 4. C++核心代码实现赏析
**通用核心实现（综合优化版）**  
```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;
const int N=1e5+5, M=2e5+5, S=450, P=87, mod=1e9+7;

char st[P][N][18]; // 小质数ST表（char存储）
int rt[N], pre[M], inv[M], lg[N], n, q, last;

struct Node { int l,r,val=1; } T[N*20]; // 主席树动态开点
int build(int l,int r) { /* 初始化 */ }
int update(int pre,int l,int r,int p,int v) {
    int now = ++tot; T[now]=T[pre];
    T[now].val = 1LL*T[now].val*v%mod; // 实时更新乘积
    if(l == r) return now;
    int mid=(l+r)>>1;
    if(p<=mid) T[now].l=update(T[pre].l,l,mid,p,v);
    else T[now].r=update(T[pre].r,mid+1,r,p,v);
    return now;
}
int query(int u,int l,int r,int L,int R) { /* 区间乘积查询 */ }

int main() {
    // 初始化逆元 & 质数表
    for(int i=1; i<M; ++i) inv[i]=(i==1)?1:1LL*inv[mod%i]*(mod-mod/i)%mod;
    
    // 小质数指数分解
    for(int i=1,x; i<=n; ++i) {
        x=a[i];
        for(int j=0; j<P; ++j) while(x%pr[j]==0) 
            st[j][i][0]++, x/=pr[j];
    }
    
    // 主席树处理大质数
    for(int i=1; i<=n; ++i) {
        rt[i]=rt[i-1];
        if(a[i]>S) {
            if(pre[a[i]]) rt[i]=update(rt[i],1,n,pre[a[i]],inv[a[i]]); // 去重
            rt[i]=update(rt[i],1,n,i,a[i]); // 新增
            pre[a[i]]=i;
        }
    }
    
    // 查询处理
    while(q--) {
        int l=(last+read())%n+1, r=(last+read())%n+1;
        if(l>r) swap(l,r);
        last = 1;
        for(int j=0; j<P; ++j) // 小质数贡献
            last = 1LL*last*ksm(pr[j], st_query(j,l,r))%mod;
        last = 1LL*last*query(rt[r],1,n,l,r)%mod; // 大质数贡献
    }
}
```

---

### 5. 算法可视化：像素动画演示
**主题**：8位像素风"质因数大冒险"  
**核心流程**：  
1. **网格场景**：  
   - 横向像素网格（每个格子代表数组位置）
   - 顶部HUD显示当前质因数类型（小质数红/大质数蓝）

2. **ST表构建动画**：  
   ```mermaid
   sequenceDiagram
     小质数 p->>+位置i: 扫描指数
     位置i-->>ST表: 闪烁黄光
     loop 自底向上合并
        ST表层1->>ST表层2: 相邻块合并（像素方块碰撞特效+8bit音效）
     end
   ```

3. **主席树修改演示**：  
   - 新大质数出现：当前位置冒出蓝色宝石💎 + "叮"声  
   - 重复出现：旧位置宝石变灰💣 + 爆炸音效，新位置蓝光亮起✨  

4. **查询过程**：  
   - 小质数：ST表区间覆盖半透明绿色图层  
   - 大质数：从主席树根部发射金色光线，穿透[l,r]区间叶子节点  

**控制面板**：  
- 步进/暂停/速度滑块  
- 质因数类型开关（单独查看小/大质数效果）  
- "AI演示"模式：自动播放解题全流程（像素小人沿路径移动）  

---

### 6. 拓展练习与相似问题
**通用技巧迁移**：  
> 根号分治思想还可用于：  
> 1. 区间众数查询（分出现频率）  
> 2. 带修改莫队（分块大小平衡）  
> 3. 大数因子求和（分大小因子）  

**洛谷推荐**：  
1. [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)  
   → **练习主席树去重核心思想**  
2. [P3865 ST表](https://www.luogu.com.cn/problem/P3865)  
   → **巩固ST表空间优化技巧**  
3. [P1890 gcd区间](https://www.luogu.com.cn/problem/P1890)  
   → **对比LCM与GCD的查询差异**  

---

### 7. 学习心得与经验分享
> **来自IntrepidStrayer的调试经验**：  
> “ST表用int提交MLE后，发现指数≤5 → 改用char存储，空间直降75%”  
>   
> **Kay总结**：值域分析是空间优化的关键突破口！遇到大数据结构时：  
> 1. 算清理论空间需求  
> 2. 观察数据值域特征  
> 3. 尝试类型降维（int→char/short）  

---

通过这份指南，希望大家能掌握根号分治的精髓，理解主席树"时光回溯"的妙用，并在像素化演示中感受算法之美。下次遇到复杂问题时，记得像拆分质因数一样将它分解击破！🚀

---
处理用时：134.91秒