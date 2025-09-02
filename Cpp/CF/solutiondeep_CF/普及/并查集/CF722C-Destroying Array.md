# 题目信息

# Destroying Array

## 题目描述

给你一个由 $n$ 个非负整数组成的数列 $a_1$，$a_2$，$\cdots$，$a_n$。

你将要一个一个摧毁这个数列中的数。并且，现在给你一个由 $1$ 到 $n$ 组成的序列来告诉你每个数被摧毁的时间顺序。

每当一个元素被摧毁时，你需要找到这个当前数列中的未被摧毁的数组成的和最大的连续子序列，另外，如果当前剩余的序列是空的的话，最大和就是 $0$。

## 说明/提示

第一个样例：

1.第三个数被删除了，现在的数列是 1 3 x 5 ，5由一个数5组成。

2.第四个数被删除了，现在的数列是 1 3 x x ，4由两个数1和3组成。

3.第一个数被删除了，现在的数列是 x 3 x x ，3由一个数3组成。

4.最后一个剩下的数被删除了，现在的数列中没有东西啦，所以答案是0呢！


感谢 @FangHaosb 提供的翻译

## 样例 #1

### 输入

```
4
1 3 2 5
3 4 1 2
```

### 输出

```
5
4
3
0
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
4 2 3 5 1
```

### 输出

```
6
5
5
1
0
```

## 样例 #3

### 输入

```
8
5 5 4 4 6 6 5 5
5 2 8 7 1 3 4 6
```

### 输出

```
18
16
11
8
8
6
6
0
```

# AI分析结果

### 题目内容（已为中文，无需翻译）
【题目内容】
# Destroying Array

## 题目描述

给你一个由 $n$ 个非负整数组成的数列 $a_1$，$a_2$，$\cdots$，$a_n$。

你将要一个一个摧毁这个数列中的数。并且，现在给你一个由 $1$ 到 $n$ 组成的序列来告诉你每个数被摧毁的时间顺序。

每当一个元素被摧毁时，你需要找到这个当前数列中的未被摧毁的数组成的和最大的连续子序列，另外，如果当前剩余的序列是空的的话，最大和就是 $0$。

## 说明/提示

第一个样例：

1. 第三个数被删除了，现在的数列是 1 3 x 5 ，5 由一个数 5 组成。

2. 第四个数被删除了，现在的数列是 1 3 x x ，4 由两个数 1 和 3 组成。

3. 第一个数被删除了，现在的数列是 x 3 x x ，3 由一个数 3 组成。

4. 最后一个剩下的数被删除了，现在的数列中没有东西啦，所以答案是 0 呢！


感谢 @FangHaosb 提供的翻译

## 样例 #1

### 输入

```
4
1 3 2 5
3 4 1 2
```

### 输出

```
5
4
3
0
```

## 样例 #2

### 输入

```
5
1 2 3 4 5
4 2 3 5 1
```

### 输出

```
6
5
5
1
0
```

## 样例 #3

### 输入

```
8
5 5 4 4 6 6 5 5
5 2 8 7 1 3 4 6
```

### 输出

```
18
16
11
8
8
6
6
0
```

### 综合分析与结论
这些题解主要围绕两种思路展开：线段树和并查集。

#### 线段树思路
- **算法要点**：通过线段树维护区间最大子段和、区间和、区间最大前缀和以及区间最大后缀和。删除操作将对应点的值赋为极小值，避免其被选入最大子段和。
- **解决难点**：处理删除操作时，将删除转化为赋值极小值，保证最大子段和计算不受影响。同时要注意多个极小值相加可能爆 `long long` 的问题。

#### 并查集思路
- **算法要点**：采用时光倒流法，将删除操作转化为从后往前的添加操作。用并查集维护相邻数的连通性，用数组记录每个连通分量的总和，每次添加数时更新总和并比较最大值。
- **解决难点**：并查集只能加边不能减边，通过逆向操作解决删除问题。利用数列元素非负的性质，每次添加数后最大值只会增大，简化最大值的更新过程。

### 所选题解
- **作者：shenmadongdong（4星）**
    - **关键亮点**：思路简洁，直接用 `multiset` 维护区间和，通过前缀和快速计算区间和，代码实现简单易懂。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,l,r,x,a[100010];
multiset<long long>s,res;
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],a[i]+=a[i-1];
    a[n+1]=a[n];
    res.insert(a[n]);
    s.insert(0),s.insert(n+1);
    for(int i=1;i<=n;i++)
    {
        cin>>x;
        auto it=s.lower_bound(x);
        r=*it;l=*--it;
        s.insert(x);
        res.erase(res.find(a[r-1]-a[l]));
        res.insert(a[x-1]-a[l]);
        res.insert(a[r-1]-a[x]);
        cout<<*--res.end()<<'\n';
    }
    return 0;
}
```
    - **核心实现思想**：先计算前缀和，将整个区间和插入 `res`，左右端点插入 `s`。每次删除一个点时，找到该点所在区间，将原区间和删除，插入左右子区间和，最后输出 `res` 中的最大值。

- **作者：QuAckB33（4星）**
    - **关键亮点**：清晰地阐述了并查集时光倒流法的思路，代码注释详细，易于理解。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int fa[100010];
int sum[100010];
int a[100010],b[100010];
int anss[100010];
int getfa(int x){
    if(fa[x]!=x){
        fa[x]=getfa(fa[x]);
        return getfa(fa[x]);
    }
    return x;
}
void merge(int x,int y){
    int a=getfa(x),b=getfa(y);
    if(a==b)return;
    fa[b]=a;
    sum[a]+=sum[b];
}
signed main(){
    int n;cin>>n;
    for(int i=1;i<=n;++i)cin>>a[i];
    for(int i=1;i<=n;++i)cin>>b[i];
    int ans=0;
    for(int i=n;i>=1;--i){
        fa[b[i]]=b[i];
        sum[b[i]]=a[b[i]];
        if(fa[b[i]-1])merge(b[i]-1,b[i]);
        if(fa[b[i]+1])merge(b[i]+1,b[i]);
        ans=max(ans,sum[getfa(b[i])]); 
        anss[i]=ans;
    }
    for(int i=2;i<=n;++i){
        cout<<anss[i]<<endl;
    }
    cout<<0<<endl;
}
```
    - **核心实现思想**：从后往前添加数，初始化并查集和每个数的总和。每次添加数时，将其与左右相邻且已添加的数合并，更新总和并比较最大值，最后逆序输出结果。

- **作者：让风忽悠你（4星）**
    - **关键亮点**：详细解释了线段树维护最大子段和的原理，代码结构清晰。
    - **核心代码**：
```cpp
#include<cstdio>
#include<algorithm>
#define N 400005 
#define ll long long 
#define inf -9e13 

using namespace std;

struct node{
    int l,r;
    ll ls,rs,ms,w;
};
node tree[N];

inline void pushup(int k){
    tree[k].w=tree[k*2].w+tree[k*2+1].w;
    tree[k].ls=max(tree[k*2].ls,tree[k*2].w+tree[k*2+1].ls);
    tree[k].rs=max(tree[k*2+1].rs,tree[k*2+1].w+tree[k*2].rs);
    tree[k].ms=max(max(tree[k*2].ms,tree[k*2+1].ms),tree[k*2].rs+tree[k*2+1].ls);
} 
void build(int k,int l,int r){
    tree[k].l=l; tree[k].r=r;
    if(l==r){
        scanf("%lld",&tree[k].w);
        tree[k].ls=tree[k].rs=tree[k].ms=tree[k].w;
        return;
    }
    int mid=(l+r)>>1;
    build(k*2,l,mid);
    build(k*2+1,mid+1,r);
    pushup(k);
} 
void change(int k){
    if(tree[k].l==tree[k].r){
        tree[k].w=tree[k].ms=tree[k].ls=tree[k].rs=y; 
        return;
    }
    int mid=(tree[k].l+tree[k].r)>>1;
    if(x<=mid) change(k*2);
    else change(k*2+1);
    pushup(k);
}
node query(int k,int x,int y){
    if(x<=tree[k].l && y>=tree[k].r) return tree[k];
    int mid=(tree[k].l+tree[k].r)>>1;
    if(x>mid) return query(k*2+1,x,y);
    if(y<=mid) return query(k*2,x,y);
    else{
        node T,ansl,ansr;
        ansl=query(k*2,x,y); ansr=query(k*2+1,x,y);
        T.w=ansl.w+ansr.w;
        T.ms=max(max(ansl.ms,ansr.ms),ansl.rs+ansr.ls);
        T.ls=max(ansl.ls,ansl.w+ansr.ls);
        T.rs=max(ansr.rs,ansr.w+ansl.rs);
        return T;
    }
} 
int main(){
    scanf("%d",&n);
    build(1,1,n);
    for(int i=1;i<n;i++){
        scanf("%d",&x);
        change(1);
        printf("%lld\n",query(1,1,n).ms);
    }
    printf("0"); 
    return 0;
}
```
    - **核心实现思想**：通过线段树的 `build` 函数建树，`pushup` 函数合并区间信息，`change` 函数修改节点值，`query` 函数查询区间最大子段和。每次删除一个数时，将其值改为极小值，更新线段树并输出最大子段和。

### 最优关键思路或技巧
- **逆向思维**：将删除操作转化为添加操作，解决了并查集只能加边不能减边的问题，简化了问题的处理。
- **数据结构的运用**：线段树可以灵活维护区间信息，适用于各种复杂的区间查询和修改操作；并查集能高效处理连通性问题，在本题中用于维护相邻数的连通分量。

### 可拓展之处
- **同类型题**：涉及动态维护区间信息或连通性的问题，如动态最大子矩阵和、动态连通块问题等。
- **类似算法套路**：逆向思维在很多问题中都有应用，如逆序处理操作、倒推求解等；线段树和并查集是处理区间和连通性问题的常用数据结构，可以结合其他算法进行拓展，如线段树与二分查找结合、并查集与路径压缩优化等。

### 推荐题目
- [P1197 星球大战](https://www.luogu.com.cn/problem/P1197)：同样采用逆向思维，将删除操作转化为添加操作，用并查集维护连通性。
- [P2024 [NOI2001] 食物链](https://www.luogu.com.cn/problem/P2024)：并查集的经典应用，需要维护多种关系的连通性。
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：线段树的基础模板题，可用于练习线段树的基本操作。

### 个人心得摘录与总结
- **作者：shenmadongdong**：提到用 `set` 虽然能通过此题，但时间复杂度不如并查集，喜提本题最劣解，提醒我们在选择数据结构时要考虑其性能。
- **作者：AC自动机**：指出要注意两个负无穷的数相加时可能爆 `long long` 的问题，在处理极小值时需要特别小心。

---
处理用时：66.78秒