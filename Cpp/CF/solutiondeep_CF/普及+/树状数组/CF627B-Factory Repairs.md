# 题目信息

# Factory Repairs

## 题目描述

A factory produces thimbles in bulk. Typically, it can produce up to $ a $ thimbles a day. However, some of the machinery is defective, so it can currently only produce $ b $ thimbles each day. The factory intends to choose a $ k $ -day period to do maintenance and construction; it cannot produce any thimbles during this time, but will be restored to its full production of $ a $ thimbles per day after the $ k $ days are complete.

Initially, no orders are pending. The factory receives updates of the form $ d_{i} $ , $ a_{i} $ , indicating that $ a_{i} $ new orders have been placed for the $ d_{i} $ -th day. Each order requires a single thimble to be produced on precisely the specified day. The factory may opt to fill as many or as few of the orders in a single batch as it likes.

As orders come in, the factory owner would like to know the maximum number of orders he will be able to fill if he starts repairs on a given day $ p_{i} $ . Help the owner answer his questions.

## 说明/提示

Consider the first sample.

We produce up to $ 1 $ thimble a day currently and will produce up to $ 2 $ thimbles a day after repairs. Repairs take $ 2 $ days.

For the first question, we are able to fill $ 1 $ order on day $ 1 $ , no orders on days $ 2 $ and $ 3 $ since we are repairing, no orders on day $ 4 $ since no thimbles have been ordered for that day, and $ 2 $ orders for day $ 5 $ since we are limited to our production capacity, for a total of $ 3 $ orders filled.

For the third question, we are able to fill $ 1 $ order on day $ 1 $ , $ 1 $ order on day $ 2 $ , and $ 2 $ orders on day $ 5 $ , for a total of $ 4 $ orders.

## 样例 #1

### 输入

```
5 2 2 1 8
1 1 2
1 5 3
1 2 1
2 2
1 4 2
1 3 2
2 1
2 3
```

### 输出

```
3
6
4
```

## 样例 #2

### 输入

```
5 4 10 1 6
1 1 5
1 5 5
1 3 2
1 5 2
2 1
2 2
```

### 输出

```
7
1
```

# AI分析结果

### 题目翻译
# 工厂维修

## 题目描述
一家工厂批量生产顶针。通常情况下，它一天最多能生产 $a$ 个顶针。然而，部分机器出现了故障，目前每天只能生产 $b$ 个顶针。工厂打算选择一个为期 $k$ 天的时间段进行维护和建设；在此期间，工厂无法生产任何顶针，但 $k$ 天结束后，工厂将恢复到每天生产 $a$ 个顶针的满负荷生产状态。

最初，没有待处理的订单。工厂会收到形式为 $d_{i}$、$a_{i}$ 的更新信息，表明在第 $d_{i}$ 天有 $a_{i}$ 个新订单。每个订单都要求在指定的那天恰好生产一个顶针。工厂可以选择在一批中尽可能多地或尽可能少地完成订单。

随着订单的到来，工厂老板想知道如果他在给定的第 $p_{i}$ 天开始维修，他最多能完成多少订单。请帮助老板回答他的问题。

## 说明/提示
考虑第一个样例。

目前我们每天最多生产 $1$ 个顶针，维修后每天最多生产 $2$ 个顶针。维修需要 $2$ 天。

对于第一个问题，我们可以在第 $1$ 天完成 $1$ 个订单，在第 $2$ 天和第 $3$ 天不完成任何订单，因为我们正在维修，在第 $4$ 天不完成任何订单，因为那天没有顶针订单，在第 $5$ 天完成 $2$ 个订单，因为我们受到生产能力的限制，总共完成 $3$ 个订单。

对于第三个问题，我们可以在第 $1$ 天完成 $1$ 个订单，在第 $2$ 天完成 $1$ 个订单，在第 $5$ 天完成 $2$ 个订单，总共完成 $4$ 个订单。

## 样例 #1
### 输入
```
5 2 2 1 8
1 1 2
1 5 3
1 2 1
2 2
1 4 2
1 3 2
2 1
2 3
```
### 输出
```
3
6
4
```

## 样例 #2
### 输入
```
5 4 10 1 6
1 1 5
1 5 5
1 3 2
1 5 2
2 1
2 2
```
### 输出
```
7
1
```

### 综合分析与结论
这些题解主要围绕工厂维修问题，通过不同的数据结构和算法来解决单点修改和区间查询问题。大部分题解采用线段树或树状数组，核心思路是维护 $\sum\limits_{i=1}^{x - 1} \min(b, t_i)$ 和 $\sum\limits_{i=x + k}^{n} \min(a, t_i)$ 两个式子。
- **思路对比**：多数题解思路一致，使用线段树或树状数组进行单点修改和区间查询，部分题解采用两颗线段树分别维护两个式子，也有使用树状数组维护前缀和、超过特定值的数的和与个数。
- **算法要点**：线段树题解主要涉及建树、单点修改、区间查询操作，树状数组题解则是单点修改和区间查询。
- **解决难点**：主要难点在于处理 $\min(a, t_i)$ 和 $\min(b, t_i)$，多数题解在单点修改时进行比较和更新，部分题解还需处理区间不合法的特判情况。

### 高评分题解
1. **RedStoneShark（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用一颗线段树存储 $\min(b, t_i)$、$\min(a, t_i)$ 和 $t_i$，避免使用 `Lazy_tag`，降低复杂度。
    - **核心代码**：
```cpp
void pushup(int u){
    xds[u].amin=xds[xds[u].zrz].amin+xds[xds[u].yrz].amin;
    xds[u].bmin=xds[xds[u].zrz].bmin+xds[xds[u].yrz].bmin;
}
void update(int u,int l,int r,int x,int val){
    if(l==r){
        xds[u].num+=val;
        xds[u].amin = min(a,xds[u].num);
        xds[u].bmin = min(b,xds[u].num);
        return;
    }
    int mid = (l+r)>>1;
    if(x<=mid){
        update(xds[u].zrz,l,mid,x,val);
    }else{
        update(xds[u].yrz,mid+1,r,x,val);
    }
    pushup(u);
}
```
2. **yingjingxu_NaS2O3（4星）**
    - **关键亮点**：详细阐述思路，对不合法区间进行特判，代码结构清晰。
    - **核心代码**：
```cpp
void Update(int l,int r,int x,int y,int iid)
{
    if(l==r)
    {
        tr[iid]=min(b,tr[iid]+y);
        return;
    }
    int mid=l+r>>1;
    if(x<=mid)
        Update(l,mid,x,y,iid<<1);
    else
        Update(mid+1,r,x,y,iid<<1|1);
    tr[iid]=tr[iid<<1]+tr[iid<<1|1];
    return;
}
```
3. **QCurium（4星）**
    - **关键亮点**：提供原题链接和视频讲解，代码注释详细，使用一颗线段树维护相关值。
    - **核心代码**：
```cpp
void modify(int aa,int lr,int z){
    if(a[aa].l==a[aa].r&&a[aa].l==lr){
        a[aa].vala+=z;
        a[aa].valb+=z;
        a[aa].suma=min(a[aa].vala,aaa);
        a[aa].sumb=min(a[aa].valb,bbb);
        return ;
    }
    int mid=(a[aa].l+a[aa].r)>>1;
    if(lr<=mid)
        modify(aa*2,lr,z);
    else
        modify(aa*2+1,lr,z);
    pushup(aa);
    return ;
}
```

### 最优关键思路与技巧
- **数据结构**：使用线段树或树状数组进行单点修改和区间查询，提高效率。
- **思维方式**：将问题拆分为两个式子分别维护，在单点修改时处理 $\min$ 操作。
- **代码实现**：部分题解使用 `pushup` 函数更新区间和，减少代码冗余。

### 拓展思路
同类型题目可能涉及更多复杂的区间操作，如区间修改、区间最值查询等，可使用线段树的 `Lazy_tag` 或树状数组的扩展来解决。类似算法套路包括使用数据结构维护前缀和、后缀和等。

### 推荐题目
1. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3368 【模板】树状数组 2](https://www.luogu.com.cn/problem/P3368)

### 个人心得摘录与总结
- **charleshe**：翻译题目时出现错误，提醒做题要注意输入顺序，避免对题意产生疑惑。
- **VitrelosTia**：自己写出数据结构题感到开心，强调要维护查询所需信息，利用 `pushup` 合并左右子树信息。 

---
处理用时：44.52秒