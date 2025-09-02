# 题目信息

# Mishka and Interesting sum

## 题目描述

Little Mishka enjoys programming. Since her birthday has just passed, her friends decided to present her with array of non-negative integers $ a_{1},a_{2},...,a_{n} $ of $ n $ elements!

Mishka loved the array and she instantly decided to determine its beauty value, but she is too little and can't process large arrays. Right because of that she invited you to visit her and asked you to process $ m $ queries.

Each query is processed in the following way:

1. Two integers $ l $ and $ r $ ( $ 1<=l<=r<=n $ ) are specified — bounds of query segment.
2. Integers, presented in array segment $ [l,r] $ (in sequence of integers $ a_{l},a_{l+1},...,a_{r} $ ) even number of times, are written down.
3. XOR-sum of written down integers is calculated, and this value is the answer for a query. Formally, if integers written down in point 2 are $ x_{1},x_{2},...,x_{k} $ , then Mishka wants to know the value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7210428d91e1c7505cfe57a2df3abdc28a7ac76c.png), where ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/4298d47c0191af3c0a3103f431751061bc7e2362.png) — operator of exclusive bitwise OR.

Since only the little bears know the definition of array beauty, all you are to do is to answer each of queries presented.

## 说明/提示

In the second sample:

There is no integers in the segment of the first query, presented even number of times in the segment — the answer is $ 0 $ .

In the second query there is only integer $ 3 $ is presented even number of times — the answer is $ 3 $ .

In the third query only integer $ 1 $ is written down — the answer is $ 1 $ .

In the fourth query all array elements are considered. Only $ 1 $ and $ 2 $ are presented there even number of times. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/1f43581f72fc5ce3c0b862a8034cb76a29952125.png).

In the fifth query $ 1 $ and $ 3 $ are written down. The answer is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF703D/7a7518e2f6c019be104f1f3114e7d17043192b15.png).

## 样例 #1

### 输入

```
3
3 7 8
1
1 3
```

### 输出

```
0
```

## 样例 #2

### 输入

```
7
1 2 1 3 3 2 3
5
4 7
4 5
1 3
1 7
1 5
```

### 输出

```
0
3
1
3
2
```

# AI分析结果



# 算法分类  
**离线处理 + 树状数组/线段树**

---

## 综合分析与结论  

### 核心思路  
**关键推导**：  
出现偶数次的数的异或和 = 区间异或和 ^ 区间不同数的异或和  
- **区间异或和**：通过前缀异或和快速计算  
- **区间不同数的异或和**：用树状数组/线段树维护每个数最后一次出现的位置，离线处理查询  

### 解决难点  
1. **高效维护不同数的异或和**：  
   - 离散化处理大范围数值  
   - 对查询按右端点排序，保证处理顺序  
   - 当遇到重复数时，删除其上一次出现的位置的贡献  

2. **异或性质的应用**：  
   - 利用异或自反性（x^x=0）消去奇数次出现的数  
   - 不同数异或和与区间异或和的结合实现偶数次筛选  

---

## 题解清单 (≥4星)  

### 1. 顾z (5星)  
**亮点**：  
- 核心推导简洁，代码结构清晰  
- 树状数组实现高效维护不同数的异或和  
- 离散化处理大范围数值  
**代码片段**：  
```cpp  
while(now<=r) {  
    if(pre[now]) add(pre[now],b[a[now]]);  
    add(now,b[a[now]]);  
    now++;  
}  
ans[que[i].idx] = (query(r)^query(l-1)) ^ (sum[r]^sum[l-1]);  
```

### 2. Little09 (4星)  
**亮点**：  
- 类似HH的项链的离线处理思路  
- 树状数组维护动态异或和  
**核心代码**：  
```cpp  
while(tot<q[i].r) {  
    tot++;  
    add(tot,col[tot]), add(pre[tot],col[pre[tot]]);  
}  
```

### 3. 傅天宇666 (4星)  
**亮点**：  
- 树状数组动态更新异或和的实现  
- 离散化与预处理巧妙结合  
**代码片段**：  
```cpp  
for(int i=1;i<=m;i++) {  
    while(r<q[i].r) add(++r);  
    ans[q[i].id] = query(q[i].r)^query(q[i].l-1)^sum[r]^sum[l-1];  
}  
```

---

## 最优思路或技巧提炼  

### 关键技巧  
1. **异或性质转换**：  
   ```  
   偶数次异或和 = 区间异或和 ^ 不同数异或和  
   ```  
2. **离线处理 + 右端点排序**：  
   - 保证每个数只保留最后一次出现的贡献  
3. **树状数组动态维护**：  
   - 插入新数时，删除其上一次出现的贡献  

---

## 同类型题与算法套路  

### 通用解法  
- **离线处理区间不同元素问题**：  
  1. 按右端点排序查询  
  2. 维护每个元素最后一次出现的位置  
  3. 动态更新数据结构（树状数组/线段树）  

### 推荐题目  
1. [P1972 HH的项链](https://www.luogu.com.cn/problem/P1972)（区间不同元素数量）  
2. [CF1000F One Occurrence](https://codeforces.com/problemset/problem/1000/F)（区间中仅出现一次的数）  
3. [SP3267 DQUERY](https://www.luogu.com.cn/problem/SP3267)（区间不同元素个数）  

---

## 可视化与算法演示  

### 核心动画设计  
**树状数组维护不同数异或和**  
1. **颜色标记**：  
   - **红色**：当前处理的元素  
   - **绿色**：树状数组中更新的位置  
2. **步进控制**：  
   - 展示右端点逐步右移，插入新数并删除旧位置  
3. **像素风格演示**：  
   - 使用8-bit风格网格表示数组，树状数组节点以方块显示  
   - 插入/删除操作时播放“哔”音效，完成查询时播放“叮”音效  

### 复古游戏化设计  
- **Canvas动画**：  
  - 数组元素显示为像素方块，数值用颜色编码  
  - 树状数组节点动态高亮更新路径  
- **音效触发**：  
  - 插入元素：短促“哔”声  
  - 完成查询：上扬“成功”音效  
- **自动演示模式**：  
  - 右端点自动右移，展示算法处理流程  

---

## 代码实现（树状数组版）  

```cpp  
#include <bits/stdc++.h>  
using namespace std;  
const int N=1e6+5;  
int n,m,a[N],b[N],sum[N],pre[N],last[N],ans[N],tree[N];  
struct Query { int l,r,id; } q[N];  

void update(int x,int val) {  
    for(;x<=n;x+=x&-x) tree[x]^=val;  
}  
int query(int x) {  
    int res=0;  
    for(;x;x-=x&-x) res^=tree[x];  
    return res;  
}  

int main() {  
    // 输入与离散化  
    scanf("%d",&n);  
    for(int i=1;i<=n;i++) {  
        scanf("%d",&a[i]);  
        b[i]=a[i]; sum[i]=sum[i-1]^a[i];  
    }  
    sort(b+1,b+n+1);  
    int cnt=unique(b+1,b+n+1)-b-1;  
    for(int i=1;i<=n;i++) {  
        a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;  
        pre[i]=last[a[i]];  
        last[a[i]]=i;  
    }  
    // 处理查询  
    scanf("%d",&m);  
    for(int i=1;i<=m;i++) {  
        scanf("%d%d",&q[i].l,&q[i].r);  
        q[i].id=i;  
    }  
    sort(q+1,q+m+1,[](auto& x,auto& y){return x.r<y.r;});  
    // 离线处理  
    int cur=1;  
    for(int i=1;i<=m;i++) {  
        while(cur<=q[i].r) {  
            if(pre[cur]) update(pre[cur],b[a[cur]]);  
            update(cur,b[a[cur]]);  
            cur++;  
        }  
        ans[q[i].id]=query(q[i].r)^query(q[i].l-1)^sum[q[i].r]^sum[q[i].l-1];  
    }  
    // 输出结果  
    for(int i=1;i<=m;i++) printf("%d\n",ans[i]);  
    return 0;  
}  
```

---
处理用时：88.70秒