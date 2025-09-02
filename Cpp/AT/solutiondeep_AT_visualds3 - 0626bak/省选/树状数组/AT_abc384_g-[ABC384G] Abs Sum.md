# 题目信息

# [ABC384G] Abs Sum

## 题目描述

给定长度为$N$的整数序列$A,B$和长度为$K$的正整数序列$X,Y$，对于$k=1,2,3,...,K$，求$\sum_{i = 1}^{X_k} \sum_{j = 1}^{Y_k} |A_i-B_j|$。

## 样例 #1

### 输入

```
2
2 4
3 5
4
1 1
1 2
2 1
2 2```

### 输出

```
1
4
2
6```

## 样例 #2

### 输入

```
5
1163686 28892 1263085 2347878 520306
1332157 1202905 2437161 1291976 563395
5
5 3
1 5
2 3
1 2
5 5```

### 输出

```
13331322
2209746
6366712
207690
20241215```

# AI分析结果



---

## 算法分类
**莫队算法（Mo's Algorithm）**

---

## 题解思路与核心难点

### 核心思路
1. **莫队算法框架**：  
   将每个查询视为二维平面上的点 $(X_k, Y_k)$，通过调整查询顺序，以块为单位排序，减少指针移动次数。
2. **绝对值拆分与统计**：  
   对于每个新增元素 $A_i$ 或 $B_j$，拆分为两部分贡献：小于等于当前值的元素和与数量，以及大于当前值的元素和与数量。例如：
   $$
   \sum |A_i - B_j| = \sum_{B_j \le A_i} (A_i - B_j) + \sum_{B_j > A_i} (B_j - A_i)
   $$
3. **树状数组维护**：  
   使用树状数组动态维护离散化后的元素出现次数与总和，实现 $O(\log N)$ 的查询和更新。

### 解决难点
- **离散化处理**：将 $A$ 和 $B$ 的值域压缩到 $O(N)$ 范围，避免内存爆炸。
- **双指针同步移动**：维护当前区间 $[1, x]$ 和 $[1, y]$ 的状态，确保每次移动时正确更新总答案。
- **块长优化**：通过调整块长为 $\frac{N}{\sqrt{Q}}$ 或 $\sqrt{N \log N}$，平衡时间与空间复杂度。

---

## 题解评分 (≥4星)

### 1. 作者：Milthm（⭐⭐⭐⭐⭐）
- **亮点**：  
  - 代码结构清晰，使用双树状数组分别维护 $A$ 和 $B$ 的统计信息。  
  - 离散化处理简洁，分块策略合理。  
  - 调试心得提到“常数不要太大”，提醒关注实际运行效率。
```cpp
// 核心代码：添加元素时更新树状数组和总答案
void addx(int x,int k) {
    ans += k*(Bcnt.query(1,a[x])*vala[x] - B.query(1,a[x]));
    ans += k*(B.query(a[x]+1,t) - Bcnt.query(a[x]+1,t)*vala[x]);
    A.add(a[x],k*vala[x]); Acnt.add(a[x],k);
}
```

### 2. 作者：Conan15（⭐⭐⭐⭐）
- **亮点**：  
  - 使用统一离散化数组，减少代码冗余。  
  - 通过 `change` 函数封装树状数组的更新逻辑，增强可读性。  
```cpp
inline void change(int val, bool xy, int opt) {
    // 计算贡献并更新树状数组
    sum[xy].add(val, c[val] * opt), cnt[xy].add(val, opt);
}
```

### 3. 作者：q1uple（⭐⭐⭐⭐）
- **亮点**：  
  - 块长设为 $\sqrt{N}$，适合小规模数据。  
  - 使用 `pair` 封装树状数组的查询结果，简化逻辑。  
```cpp
pii query(int x) {
    int s = 0; ll sum = 0;
    for (; x; x -= x&-x) s += c[x], sum += t[x];
    return {s, sum};
}
```

---

## 最优思路与技巧提炼

### 关键步骤
1. **离散化**：合并 $A$ 和 $B$ 的值域，映射到 $[1, 2N]$。
2. **莫队排序**：按块排序查询，奇偶块交替处理右端点，减少移动次数。
3. **树状数组维护**：  
   - 维护两个树状数组：一个记录元素个数，一个记录元素和。
   - 新增元素时，计算其对另一数组中所有元素的贡献。

### 代码实现片段
```cpp
// 离散化处理
vector<int> lsh;
for (int i=1; i<=n; i++) lsh.push_back(a[i]);
for (int i=1; i<=n; i++) lsh.push_back(b[i]);
sort(lsh.begin(), lsh.end());
lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());

// 莫队移动指针
while (l < q[i].l) addA(++l);
while (r < q[i].r) addB(++r);
while (l > q[i].l) delA(l--);
while (r > q[i].r) delB(r--);
```

---

## 相似题目与推荐

1. **P1972 [SDOI2009]HH的项链**  
   - 莫队算法经典应用，统计区间内不同数字个数。
2. **P1903 [国家集训队]数颜色 / 维护队列**  
   - 带修改的莫队，拓展到三维查询。
3. **P4113 [HEOI2012]采花**  
   - 结合莫队与树状数组，统计区间内出现次数超过阈值的元素。

---

## 可视化与算法演示设计

### 动画方案
- **像素风格界面**：  
  - 用 8-bit 色块表示 $A$ 和 $B$ 数组元素，不同颜色区分已处理和未处理部分。
- **高亮操作**：  
  - 红色框标记当前移动的指针（$x$ 或 $y$）。
  - 绿色闪烁显示树状数组的更新位置。
- **音效提示**：  
  - 指针移动时播放“滴”声，树状数组更新时播放“嗒”声。
  - 背景音乐使用 8-bit 风格的循环旋律。

### 交互设计
- **控制面板**：  
  - 滑动条调节动画速度（1x~5x）。  
  - 按钮切换自动演示/手动步进。  
- **算法比较模式**：  
  - 并行显示分块法与莫队的指针移动路径，对比时间复杂度差异。

---

## 个人心得摘录

- **调试经验**：  
  > “离散化时忘记去重，导致树状数组越界，调了 20 分钟才找到问题。”（作者：Milthm）  
  > “块长设置不当导致 TLE，改为 $\sqrt{N \log N}$ 后 AC。”（作者：KazamaRuri）

- **优化技巧**：  
  > “预处理前缀和，避免每次重新计算总和。”（作者：huangjinxiu）  
  > “奇偶块交替排序减少右端点抖动，实测节省 30% 时间。”（作者：FiraCode）

---

## 核心代码实现（完整）

```cpp
#include<bits/stdc++.h>
#define N 200005
#define int long long
using namespace std;
int n,m,a[N],b[N],vala[N],valb[N],ls[N],t,sum,siz=1e3,ans,rr[N];
struct yhb{int l,r,id;}qwq[N];
int cmp(yhb x,yhb y){
    if(x.l/siz!=y.l/siz)return x.l<y.l;
    return (x.l/siz)&1?x.r<y.r:x.r>y.r;
}
struct BIT{
    int c[N];
    void add(int x,int k){while(x<=t)c[x]+=k,x+=x&-x;}
    int ask(int x){int ans=0; while(x)ans+=c[x],x-=x&-x; return ans;}
    int query(int l,int r){return ask(r)-ask(l-1);}
}A,Acnt,B,Bcnt;
void addx(int x,int k){
    ans += k*(Bcnt.query(1,a[x])*vala[x] - B.query(1,a[x]));
    ans += k*(B.query(a[x]+1,t) - Bcnt.query(a[x]+1,t)*vala[x]);
    A.add(a[x],k*vala[x]); Acnt.add(a[x],k);
}
void addy(int x,int k){
    ans += k*(Acnt.query(1,b[x])*valb[x] - A.query(1,b[x]));
    ans += k*(A.query(b[x]+1,t) - Acnt.query(b[x]+1,t)*valb[x]);
    B.add(b[x],k*valb[x]); Bcnt.add(b[x],k);
}
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i], vala[i]=a[i], ls[++t]=a[i];
    for(int i=1;i<=n;i++) cin>>b[i], valb[i]=b[i], ls[++t]=b[i];
    sort(ls+1,ls+t+1);
    for(int i=1;i<=n;i++) a[i]=lower_bound(ls+1,ls+t+1,a[i])-ls;
    for(int i=1;i<=n;i++) b[i]=lower_bound(ls+1,ls+t+1,b[i])-ls;
    cin>>m;
    for(int i=1;i<=m;i++) cin>>qwq[i].l>>qwq[i].r,qwq[i].id=i;
    sort(qwq+1,qwq+m+1,cmp);
    int l=0,r=0;
    for(int i=1;i<=m;i++){
        while(l>qwq[i].l)addx(l--,-1);
        while(r>qwq[i].r)addy(r--,-1);
        while(l<qwq[i].l)addx(++l,1);
        while(r<qwq[i].r)addy(++r,1);
        rr[qwq[i].id]=ans;
    }
    for(int i=1;i<=m;i++)cout<<rr[i]<<'\n';
    return 0;
}
```

---
处理用时：119.59秒