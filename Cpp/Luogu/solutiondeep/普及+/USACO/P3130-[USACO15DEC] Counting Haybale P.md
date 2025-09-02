# 题目信息

# [USACO15DEC] Counting Haybale P

## 题目描述

Farmer John 正在尝试雇佣承包商来帮助他重新安排农场，但到目前为止，所有承包商在看到 FJ 希望他们遵循的复杂指令序列后都辞职了。FJ 不得不自己完成这个项目，他意识到自己可能把项目搞得比必要的还要复杂。请帮助他按照指令完成农场的升级。

FJ 的农场由一排 $N$ 个田地组成，编号为 $1 \ldots N$。每个田地里可以有任意数量的干草堆。Farmer John 的指令包含三种类型的条目：

1) 给定一个连续的田地区间，向每个田地添加一个新的干草堆。

2) 给定一个连续的田地区间，确定该区间内田地中干草堆的最小数量。

3) 给定一个连续的田地区间，计算该区间内干草堆的总数。

## 样例 #1

### 输入

```
4 5
3 1 2 4
M 3 4
S 1 3
P 2 3 1
M 3 4
S 1 3```

### 输出

```
2
6
3
8```

# AI分析结果

### 综合分析与结论
这些题解主要围绕农场田地干草堆操作问题展开，涉及区间修改、查询区间最小值和区间和的操作。大部分题解采用线段树实现，也有使用分块和 Splay 树的。线段树题解思路相似，通过维护节点的和、最小值以及懒标记，利用递归和标记下传实现高效操作；分块题解将序列分块，大块整体操作、小块暴力更改；Splay 树题解则用其维护序列，支持相关操作。

### 所选题解
- **作者：pipiispig (赞：10)，4星**
    - **关键亮点**：思路清晰，代码注释详细，对线段树各操作函数进行封装，方便调试和理解。
    - **个人心得**：作者认为线段树很可爱，且喜欢将操作封装成函数，方便调试。
- **作者：流逝丶 (赞：4)，4星**
    - **关键亮点**：使用宏定义简化代码，提高代码可读性，对线段树基本操作实现熟练。
    - **个人心得**：认为这是线段树裸题，注意开 long long 即可一遍过。
- **作者：Fheiwn (赞：1)，4星**
    - **关键亮点**：使用自定义的缩写宏，代码结构清晰，对线段树操作的实现逻辑明确。
    - **个人心得**：原本找并查集题目，遇到本题用线段树水过去，强调要开 long long。

### 重点代码
#### 作者：pipiispig
```cpp
// 向上传递信息
void pushup(int p)
{
    t[p].sum=t[p<<1].sum+t[p<<1|1].sum;
    t[p].min=min(t[p<<1].min,t[p<<1|1].min);
}
// 懒标记下传
void pushdown(int p)
{
    if(!t[p].add)return;
    t[p<<1|1].add+=t[p].add; 
    t[p<<1].add+=t[p].add;	
    t[p<<1].min+=t[p].add;
    t[p<<1|1].min+=t[p].add;
    t[p<<1|1].sum+=(t[p<<1|1].r-t[p<<1|1].l+1)*t[p].add;
    t[p<<1].sum+=(t[p<<1].r-t[p<<1].l+1)*t[p].add;
    t[p].add=0;
}
// 建树
void build(int p,int l,int r)
{
    t[p].l=l,t[p].r=r;
    if(l==r){t[p].min=t[p].sum=a[l];return;}
    int mid=l+r>>1;
    build(p<<1,l,mid);build(p<<1|1,mid+1,r);
    pushup(p);
}
// 区间修改
void change(int p,int l,int r,int z)
{
    if(l<=t[p].l&&r>=t[p].r){t[p].add+=z,t[p].min+=z,t[p].sum+=(t[p].r-t[p].l+1)*z;return;}
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    if(l<=mid)change(p<<1,l,r,z);
    if(r>mid)change(p<<1|1,l,r,z);
    pushup(p);
}
// 查询区间和
int querysum(int p,int l,int r)
{
    if(l<=t[p].l&&r>=t[p].r)return t[p].sum;
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    int ans=0;
    if(l<=mid)ans+=querysum(p<<1,l,r);
    if(r>mid)ans+=querysum(p<<1|1,l,r);
    return ans;
}
// 查询区间最小值
int querymin(int p,int l,int r)
{
    if(l<=t[p].l&&r>=t[p].r)return t[p].min;
    pushdown(p);
    int mid=t[p].l+t[p].r>>1;
    int ans=0x7f7f7f7f;
    if(l<=mid)ans=querymin(p<<1,l,r);
    if(r>mid)ans=min(ans,querymin(p<<1|1,l,r));
    return ans;
}
```
**核心实现思想**：通过 `pushup` 函数将子节点信息传递给父节点，`pushdown` 函数处理懒标记下传，`build` 函数递归建树，`change` 函数进行区间修改，`querysum` 和 `querymin` 函数分别查询区间和与区间最小值。

#### 作者：流逝丶
```cpp
// 更新节点信息
inline void update(int k){
    tr[k]=tr[ls]+tr[rs];
    mi[k]=min(mi[ls],mi[rs]);
}
// 懒标记下传
inline void down(int k,int l,int r){
    laz[ls]+=laz[k];laz[rs]+=laz[k];
    tr[ls]+=laz[k]*(mid-l+1);mi[ls]+=laz[k];
    tr[rs]+=laz[k]*(r-mid);mi[rs]+=laz[k];
    laz[k]=0;
}
// 建树
void build(int k,int l,int r){
    if(l==r){
        tr[k]=mi[k]=read();
        return ;
    }
    build(lson);build(rson);
    update(k);
}
// 区间修改
void change(int k,int l,int r,int x,int y,int z){
    if(l==x&&y==r){
        tr[k]+=(LL)z*(r-l+1);
        mi[k]+=z;
        laz[k]+=z;
        return ;
    }
    if(laz[k])down(k,l,r);
    if(y<=mid)change(lson,x,y,z);
    else if(x>mid)change(rson,x,y,z);
    else change(lson,x,mid,z),change(rson,mid+1,y,z);
    update(k);
}
// 查询区间和
LL ask(int k,int l,int r,int x,int y){
    if(l==x&&y==r){
        return tr[k];
    }
    if(laz[k])down(k,l,r);
    if(y<=mid)return ask(lson,x,y);
    else if(x>mid)return ask(rson,x,y);
    else return ask(lson,x,mid)+ask(rson,mid+1,y);
}
// 查询区间最小值
LL query(int k,int l,int r,int x,int y){
    if(l==x&&y==r){
        return mi[k];
    }
    if(laz[k])down(k,l,r);
    if(y<=mid)return query(lson,x,y);
    else if(x>mid)return query(rson,x,y);
    else return min(query(lson,x,mid),query(rson,mid+1,y));
}
```
**核心实现思想**：使用宏定义简化代码，`update` 函数更新节点信息，`down` 函数处理懒标记下传，`build` 函数建树，`change` 函数进行区间修改，`ask` 和 `query` 函数分别查询区间和与区间最小值。

#### 作者：Fheiwn
```cpp
// 向上传递信息
void push_up(QAQ o){
    tree[o].sum=tree[o<<1].sum+tree[o<<1|1].sum;
    tree[o].Min=min(tree[o<<1].Min,tree[o<<1|1].Min);
}
// 懒标记下传
void push_down(QAQ o,TAT l){
    if(tree[o].lazy!=0){
        tree[o<<1].lazy+=tree[o].lazy;
        tree[o<<1].Min+=tree[o].lazy;
        tree[o<<1].sum+=tree[o].lazy*(l-(l>>1));
        tree[o<<1|1].lazy+=tree[o].lazy;
        tree[o<<1|1].Min+=tree[o].lazy;
        tree[o<<1|1].sum+=tree[o].lazy*(l>>1);
        tree[o].lazy=0;
    }
}
// 建树
void build(QAQ l,QAQ r,QAQ o){
    if(l==r){
        scanf("%lld",&tree[o].sum);
        tree[o].Min=tree[o].sum;
        return ;
    }
    build(LS);build(RS);
    push_up(o);
}
// 区间修改
void add(QAQ l,QAQ r,QAQ o,QAQ a,QAQ b,TAT c){
    if(l>=a&&r<=b){
        tree[o].sum+=c*(r-l+1);
        tree[o].Min+=c;
        tree[o].lazy+=c;
        return ;
    }
    push_down(o,(TAT)r-l+1);
    if(a<=mid) add(LS,a,b,c);
    if(b>mid) add(RS,a,b,c);
    push_up(o);
}
// 查询区间最小值
TAT Qmin(QAQ l,QAQ r,QAQ o,QAQ a,QAQ b){
    if(l>=a&&r<=b) return tree[o].Min;
    push_down(o,(TAT)r-l+1);
    TAT Min=1e18;
    if(a<=mid) Min=min(Min,Qmin(LS,a,b));
    if(b>mid) Min=min(Min,Qmin(RS,a,b));
    return Min;
}
// 查询区间和
TAT Qsum(QAQ l,QAQ r,QAQ o,QAQ a,QAQ b){
    if(l>=a&&r<=b) {
        return tree[o].sum;
    }
    push_down(o,(TAT)r-l+1);
    TAT ans=0;
    if(a<=mid) ans+=Qsum(LS,a,b);
    if(b>mid) ans+=Qsum(RS,a,b);
    return ans;
}
```
**核心实现思想**：使用自定义缩写宏，`push_up` 函数向上传递信息，`push_down` 函数处理懒标记下传，`build` 函数建树，`add` 函数进行区间修改，`Qmin` 和 `Qsum` 函数分别查询区间最小值与区间和。

### 最优关键思路或技巧
- **线段树**：通过维护节点的和、最小值以及懒标记，利用递归和标记下传，实现高效的区间修改和查询操作。
- **分块思想**：将原序列划分成若干块，大块整体操作，小块暴力更改，在一定程度上简化实现。
- **Splay 树**：用 Splay 树维护序列，支持区间加、区间最小值、区间和等操作。

### 可拓展之处
同类型题或类似算法套路：
- 区间修改、查询区间最大值、区间乘积等问题，可在现有线段树或分块的基础上进行扩展。
- 多维线段树，处理二维或更高维的区间操作问题。

### 推荐题目
- [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
- [P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)
- [P2574 XOR的艺术](https://www.luogu.com.cn/problem/P2574)

---
处理用时：75.87秒