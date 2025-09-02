# 题目信息

# たのしいたのしい家庭菜園

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2015/tasks/joisc2015_c

# AI分析结果



## 唯一算法分类
动态规划 + 线段树优化

---

## 综合分析与结论
### 题目核心思路
最终保留的草需构成单峰序列（先增后减）。通过动态规划分别计算每个点作为峰顶时，左侧递增和右侧递减的最大收益，合并后取最大值。

### 核心算法流程
1. **离散化**：将高度值映射到连续区间，便于线段树操作。
2. **动态规划**：
   - `f[i]`：保留第 i 棵草时左侧的最大收益。
   - `g[i]`：保留第 i 棵草时右侧的最大收益。
3. **线段树维护**：
   - 查询区间 `[0, h[i]]` 最大值，加上当前收益 `p[i]`。
   - 插入当前值到线段树的 `h[i]` 位置。
   - 对 `[0, h[i]-1]` 区间减去 `c[i]`，表示后续更高草需要被拔除的代价。

### 解决难点
- **转移方程优化**：将 O(n²) 的暴力 DP 优化为 O(n log n)，通过线段树维护区间最大值及批量减操作。
- **离散化处理**：解决高度值范围过大的问题。
- **双向处理**：反转数组计算右侧收益，保证对称性。

---

## 题解评分（≥4星）
1. **题解作者：是个汉子（★★★★★）**
   - **亮点**：详细推导转移方程，明确线段树优化逻辑，代码注释清晰。
   - **关键代码**：离散化与线段树操作分离，逻辑模块化。
2. **题解作者：Otue（★★★★）**
   - **亮点**：代码结构简洁，突出线段树操作的核心逻辑。
   - **改进点**：缺少对离散化的详细说明。
3. **题解作者：Red_river（★★★★）**
   - **亮点**：提供部分分代码与正解对比，适合不同层次读者。
   - **改进点**：正解代码较长，可读性略低。

---

## 最优思路与技巧提炼
### 关键思路
1. **离散化预处理**：将原始高度映射为连续整数，便于线段树操作。
2. **双向动态规划**：分别计算左右两侧的收益，通过反转数组复用同一逻辑。
3. **线段树区间操作**：
   - **查询**：快速获取满足高度约束的最大历史收益。
   - **批量减法**：动态维护后续草被拔除的代价。

### 代码实现片段
```cpp
// 离散化处理
sort(buk + 1, buk + lsh + 1);
lsh = unique(buk + 1, buk + lsh + 1) - buk - 1;
for (int i = 1; i <= n; i++)
    h[i] = lower_bound(buk + 1, buk + lsh + 1, h[i]) - buk;

// 线段树更新与查询
void work(ll *f) {
    build(1, 0, lsh);
    insert(1, 0, lsh, 0, 0);
    for (int i = 1; i <= n; i++) {
        f[i] = query(1, 0, lsh, 0, h[i]) + p[i];
        insert(1, 0, lsh, h[i], f[i]);
        update(1, 0, lsh, 0, h[i] - 1, -c[i]);
    }
}
```

---

## 同类题目与推荐
1. **P1908 逆序对**（线段树统计逆序对）
2. **P3580 [POI2014]LAM**（动态规划 + 数据结构优化）
3. **P4097 [HEOI2013]Segment**（线段树维护凸包）

---

## 可视化与算法演示
### 动画方案设计
1. **像素风格展示**：
   - **草的高度**：用不同颜色的像素块表示，高度越高颜色越亮。
   - **线段树节点**：以网格形式展示，每个节点显示当前区间最大值。
2. **关键操作高亮**：
   - **查询操作**：高亮线段树中被访问的节点。
   - **区间减法**：用闪烁效果表示区间更新。
   - **插入操作**：在当前高度位置显示插入动画。
3. **音效设计**：
   - **查询/插入**：短促“滴”声。
   - **区间减法**：低沉“嗡”声。
   - **合并答案**：欢快音效。

### 交互控制
- **步进控制**：允许单步执行，观察每棵草的处理流程。
- **速度调节**：滑动条控制动画播放速度。
- **自动演示**：AI 自动运行，展示最优解生成过程。

---

## 个人心得摘录
> **调试经验**：初始线段树未正确初始化最大值导致负收益计算错误。  
> **关键顿悟**：线段树中的区间减法实际上预计算了后续所有更高草的代价，使得查询时直接获得有效最大值。  
> **代码技巧**：反转数组复用同一函数处理右侧，减少代码冗余。

---

## 完整代码
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ls rt<<1
#define rs rt<<1|1

using namespace std;
const int N=1e5+10;
const ll INF=1e18;
int n,h[N],p[N],c[N],buk[N],lsh;
ll f[N],g[N],mx[N<<2],lz[N<<2],ans;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

void build(int rt,int l,int r){
    mx[rt]=-INF; lz[rt]=0;
    if(l==r) return ;
    int mid=(l+r)>>1;
    build(ls,l,mid); build(rs,mid+1,r);
}

inline void pushdown(int rt){
    if(!lz[rt]) return ;
    mx[ls]+=lz[rt]; lz[ls]+=lz[rt];
    mx[rs]+=lz[rt]; lz[rs]+=lz[rt];
    lz[rt]=0;
}

void update(int rt,int l,int r,int L,int R,ll v){
    if(L<=l&&r<=R){
        mx[rt]+=v; lz[rt]+=v;
        return ;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(L<=mid) update(ls,l,mid,L,R,v);
    if(R>mid) update(rs,mid+1,r,L,R,v);
    mx[rt]=max(mx[ls],mx[rs]);
}

ll query(int rt,int l,int r,int L,int R){
    if(L<=l&&r<=R) return mx[rt];
    pushdown(rt);
    int mid=(l+r)>>1;
    ll res=-INF;
    if(L<=mid) res=max(res,query(ls,l,mid,L,R));
    if(R>mid) res=max(res,query(rs,mid+1,r,L,R));
    return res;
}

void insert(int rt,int l,int r,int p,ll v){
    if(l==r){
        mx[rt]=max(v,mx[rt]);
        return ;
    }
    pushdown(rt);
    int mid=(l+r)>>1;
    if(p<=mid) insert(ls,l,mid,p,v);
    else insert(rs,mid+1,r,p,v);
    mx[rt]=max(mx[ls],mx[rs]);
}

inline void work(ll *f){
    build(1,0,lsh); insert(1,0,lsh,0,0);
    for(int i=1;i<=n;i++){
        f[i]=query(1,0,lsh,0,h[i])+p[i];
        insert(1,0,lsh,h[i],f[i]);
        update(1,0,lsh,0,h[i]-1,-c[i]);
    }
}

int main(){
    n=read();
    for(int i=1;i<=n;i++)
        h[i]=read(),p[i]=read(),c[i]=read(),buk[++lsh]=h[i];
    sort(buk+1,buk+lsh+1);
    lsh=unique(buk+1,buk+lsh+1)-buk-1;
    for(int i=1;i<=n;i++)
        h[i]=lower_bound(buk+1,buk+lsh+1,h[i])-buk;
    work(f);
    reverse(h+1,h+n+1); reverse(p+1,p+n+1); reverse(c+1,c+n+1);
    work(g);
    reverse(g+1,g+n+1); reverse(p+1,p+n+1);
    for(int i=1;i<=n;i++)
        ans=max(ans,f[i]+g[i]-p[i]);
    printf("%lld\n",ans);
    return 0;
}
```

---
处理用时：105.69秒