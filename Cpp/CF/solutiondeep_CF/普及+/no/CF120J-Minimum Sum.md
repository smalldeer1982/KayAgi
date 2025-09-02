# 题目信息

# Minimum Sum

## 题目描述

You are given a set of $ n $ vectors on a plane. For each vector you are allowed to multiply any of its coordinates by -1. Thus, each vector $ v_{i}=(x_{i},y_{i}) $ can be transformed into one of the following four vectors:

- $ v_{i}^{1}=(x_{i},y_{i}) $ ,
- $ v_{i}^{2}=(-x_{i},y_{i}) $ ,
- $ v_{i}^{3}=(x_{i},-y_{i}) $ ,
- $ v_{i}^{4}=(-x_{i},-y_{i}) $ .

You should find two vectors from the set and determine which of their coordinates should be multiplied by -1 so that the absolute value of the sum of the resulting vectors was minimally possible. More formally, you should choose two vectors $ v_{i} $ , $ v_{j} $ ( $ 1<=i,j<=n,i≠j $ ) and two numbers $ k_{1} $ , $ k_{2} $ ( $ 1<=k_{1},k_{2}<=4 $ ), so that the value of the expression $ |v_{i}^{k_{1}}+v_{j}^{k_{2}}| $ were minimum.

## 说明/提示

A sum of two vectors $ v=(x_{v},y_{v}) $ and $ u=(x_{u},y_{u}) $ is vector $ s=v+u=(x_{v}+x_{u},y_{v}+y_{u}) $ .

An absolute value of vector $ v=(x,y) $ is number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF120J/f38b71729f5e7990a499daa93821211f59c1e021.png).

In the second sample there are several valid answers, such as:

(3 1 4 2), (3 1 4 4), (3 4 4 1), (3 4 4 3), (4 1 3 2), (4 1 3 4), (4 2 3 1).

## 样例 #1

### 输入

```
5
-7 -3
9 0
-8 6
7 -8
4 -5
```

### 输出

```
3 2 4 2
```

## 样例 #2

### 输入

```
5
3 2
-4 7
-6 0
-8 4
5 1
```

### 输出

```
3 4 5 4
```

# AI分析结果

### 题目内容
# 最小和

## 题目描述
给定平面上的一组 $n$ 个向量。对于每个向量，你可以将其任意一个坐标乘以 -1。因此，每个向量 $v_{i}=(x_{i},y_{i})$ 可以转换为以下四个向量之一：
- $v_{i}^{1}=(x_{i},y_{i})$ 
- $v_{i}^{2}=(-x_{i},y_{i})$ 
- $v_{i}^{3}=(x_{i},-y_{i})$ 
- $v_{i}^{4}=(-x_{i},-y_{i})$ 

你需要从该集合中找出两个向量，并确定应该将它们的哪些坐标乘以 -1，以使所得向量之和的绝对值尽可能小。更正式地说，你应该选择两个向量 $v_{i}$，$v_{j}$（$1\leq i,j\leq n,i\neq j$）以及两个数字 $k_{1}$，$k_{2}$（$1\leq k_{1},k_{2}\leq 4$），使得表达式 $|v_{i}^{k_{1}}+v_{j}^{k_{2}}|$ 的值最小。

## 说明/提示
两个向量 $v=(x_{v},y_{v})$ 和 $u=(x_{u},y_{u})$ 的和是向量 $s=v + u=(x_{v}+x_{u},y_{v}+y_{u})$。
向量 $v=(x,y)$ 的绝对值是数 $\sqrt{x^{2}+y^{2}}$。
在第二个样例中有几个正确答案，例如：
(3 1 4 2), (3 1 4 4), (3 4 4 1), (3 4 4 3), (4 1 3 2), (4 1 3 4), (4 2 3 1)。

## 样例 #1
### 输入
```
5
-7 -3
9 0
-8 6
7 -8
4 -5
```
### 输出
```
3 2 4 2
```

## 样例 #2
### 输入
```
5
3 2
-4 7
-6 0
-8 4
5 1
```
### 输出
```
3 4 5 4
```

### 算法分类
分治

### 综合分析与结论
这三道题解思路相似，均是将向量和的模长问题转化为平面最近点对问题求解。具体要点如下：
 - **思路**：通过将向量加法转化为减法，即把其中一个向量的 $x$，$y$ 都取负再与另一向量相减，使向量模长变为两点间的距离，从而利用平面最近点对算法解决。
 - **算法要点**：对每个向量生成四种可能的向量（通过对坐标取正负），将这些向量视为平面上的点，然后用分治算法求解平面最近点对。分治过程中，先分别处理左右区间得到最小距离 $d$，再考虑经过左右两边的贡献，只留下距离中间分割点横、纵坐标之差不超 $d$ 的点，利用右侧点间距特性减少判断次数。
 - **解决难点**：核心在于理解并实现平面最近点对算法中处理跨左右区间点对的方式，通过限制横纵坐标差值范围及利用右侧点的分布特性优化枚举过程。

### 所选的题解
 - **作者：lottle1212__ (3星)**
    - **关键亮点**：详细阐述平面最近点对算法分治过程的精髓，即处理跨左右区间点对时通过限制横纵坐标差值筛选点，且指出右侧特定矩阵内点的分布特性可减少判断次数。代码实现完整，包含输入输出及详细注释。
    - **重点代码 - 核心实现思想**：`divide` 函数实现分治，递归处理左右区间，筛选可能产生更优解的点并判断更新答案，最后合并排序。
```cpp
int divide(int l, int r) {
    if (l==r) return inf;
    int mid=l+r>>1; node pmid=a[mid];
    int d=min(divide(l, mid), divide(mid+1, r));
    int cntl=0, cntr=0;
    L(i, l, mid) if (sq(a[i].x-pmid.x)<=d) pl[++cntl]=a[i];
    L(i, mid+1, r) if (sq(a[i].x-pmid.x)<=d) pr[++cntr]=a[i];
    int cur=1;
    L(i, 1, cntl) {
        while (cur<=cntr&&sq(pl[i].y-pr[cur].y)>d&&pl[i].y>pr[cur].y) ++cur;
        int ccur=cur;
        while (ccur<=cntr&&sq(pl[i].y-pr[ccur].y)<=d) {
            if (pl[i].id%n!=pr[ccur].id%n) minimize(d, pl[i], pr[ccur]);
            ++ccur;
        }
    }
    int curl=l, curr=mid+1; cur=l-1;
    while (curl<=mid&&curr<=r)
        if (a[curl].y<a[curr].y) b[++cur]=a[curl++];
        else b[++cur]=a[curr++];
    while (curl<=mid) b[++cur]=a[curl++];
    while (curr<=r) b[++cur]=a[curr++];
    L(i, l, r) a[i]=b[i];
    return d;
}
```
 - **作者：juju527 (2星)**
    - **关键亮点**：思路清晰，简洁说明将向量和模长转化为平面距离问题，利用平面最近点对模板求解，代码实现完整且有注释。
    - **重点代码 - 核心实现思想**：`dfs` 函数实现分治查找最近点对，递归处理左右区间，筛选横纵坐标差值符合条件的点并判断更新答案。
```cpp
double dfs(int l, int r){
    if(l==r)return inf;
    if(r-l==1){
        if(a[l].id==a[r].id)return inf;
        if(dis-dist(a[l],a[r])>eps){
            dis=dist(a[l],a[r]);
            p=a[l].id;u=a[l].flag;
            q=a[r].id;v=a[r].flag;
        }
        return dist(a[l],a[r]);
    }
    int mid=l+((r-l)>>1);
    double d1=dfs(l,mid),d2=dfs(mid+1,r);
    double d=min(d1,d2);
    int cnt=0;
    for(int i=l;i<=r;i++)
        if(fabs(a[i].x-a[mid].x)-d<eps)
            t[++cnt]=a[i];
    sort(t+1,t+cnt+1,cmp);
    for(int i=1;i<=cnt;i++){
        for(int j=i+1;j<=cnt;j++){
            if(fabs(t[i].y-t[j].y)-d>eps)break;
            if(t[i].id==t[j].id)continue;
            if(d-dist(t[i],t[j])>=eps){
                d=dist(t[i],t[j]);
                if(dis-d>eps){
                    dis=d;
                    p=t[i].id;u=t[i].flag;
                    q=t[j].id;v=t[j].flag;
                }
            }
        }
    }
    return d;
}
```
 - **作者：Elairin176 (0星)**
    - **关键亮点**：代码实现了将向量和问题转化为平面最近点对问题求解，但代码可读性较差，变量命名不直观，缺少注释，思路阐述简略。

### 最优关键思路或技巧
将向量和的模长问题转化为平面最近点对问题，利用分治算法解决平面最近点对问题时，通过巧妙筛选横纵坐标差值范围内的点，并利用点的分布特性减少枚举次数，优化算法时间复杂度至 $O(n \log n)$。

### 可拓展思路
此类问题可拓展到更高维度向量和模长最小化问题，或在向量变换规则更复杂的情况下，同样尝试转化为几何距离问题，利用类似分治思想求解。

### 洛谷相似题目推荐
 - [P1429 平面最近点对（加强版）](https://www.luogu.com.cn/problem/P1429)
 - [P7883 [COCI2012-2013#5] KOŠARE](https://www.luogu.com.cn/problem/P7883)
 - [P2056 [ZJOI2007]捉迷藏](https://www.luogu.com.cn/problem/P2056) （虽不是严格平面最近点对，但涉及分治思想及距离相关计算）

### 个人心得总结
三道题解均未提及个人心得。 

---
处理用时：72.00秒