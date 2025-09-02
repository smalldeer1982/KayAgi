# 题目信息

# Chemistry Experiment

## 题目描述

One day two students, Grisha and Diana, found themselves in the university chemistry lab. In the lab the students found $ n $ test tubes with mercury numbered from $ 1 $ to $ n $ and decided to conduct an experiment.

The experiment consists of $ q $ steps. On each step, one of the following actions occurs:

1. Diana pours all the contents from tube number $ p_{i} $ and then pours there exactly $ x_{i} $ liters of mercury.
2. Let's consider all the ways to add $ v_{i} $ liters of water into the tubes; for each way let's count the volume of liquid (water and mercury) in the tube with water with maximum amount of liquid; finally let's find the minimum among counted maximums. That is the number the students want to count. At that, the students don't actually pour the mercury. They perform calculations without changing the contents of the tubes.

Unfortunately, the calculations proved to be too complex and the students asked you to help them. Help them conduct the described experiment.

## 样例 #1

### 输入

```
3 3
1 2 0
2 2
1 2 1
2 3
```

### 输出

```
1.50000
1.66667
```

## 样例 #2

### 输入

```
4 5
1 3 0 1
2 3
2 1
1 3 2
2 3
2 4
```

### 输出

```
1.66667
1.00000
2.33333
2.66667
```

# AI分析结果

### 题目内容
# 化学实验

## 题目描述
一天，两位学生Grisha和Diana来到大学化学实验室。在实验室里，学生们发现了$n$个标有从$1$到$n$编号的装有汞的试管，并决定进行一项实验。

该实验由$q$个步骤组成。在每一步中，会发生以下操作之一：
1. Diana倒空编号为$p_{i}$的试管中的所有物质，然后向其中倒入恰好$x_{i}$升汞。
2. 考虑将$v_{i}$升水添加到试管中的所有方式；对于每种方式，计算装有最多液体（水和汞）的试管中的液体体积；最后找出这些计算出的最大值中的最小值。这就是学生们想要计算的数字。需要注意的是，学生们实际上并不会倒水。他们在不改变试管中物质的情况下进行计算。

不幸的是，计算结果证明过于复杂，学生们请求你帮助他们。帮助他们进行上述实验。

## 样例 #1
### 输入
```
3 3
1 2 0
2 2
1 2 1
2 3
```
### 输出
```
1.50000
1.66667
```

## 样例 #2
### 输入
```
4 5
1 3 0 1
2 3
2 1
1 3 2
2 3
2 4
```
### 输出
```
1.66667
1.00000
2.33333
2.66667
```

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是基于二分答案来解决问题，因为要找“最大值最小”的情况，二分答案具有单调性，满足条件。主要难点在于如何高效地判断二分出来的答案是否可行，不同题解采用了不同的数据结构来辅助判断。有的使用权值线段树（动态开点），有的使用平衡树（Treap），权值线段树可以快速统计满足一定值域范围的元素个数和总和，平衡树则可以在维护有序性的同时，快速获取子树的相关信息。

### 所选的题解
- **作者：GuuGuu (5星)**
    - **关键亮点**：采用线段树上二分，通过调整二分对象为调整到的高度，规避了实数的线段树上二分，时间复杂度$O(n\log n)$，代码实现较为简洁高效。
    - **重点代码核心思想**：`Query`函数实现线段树上二分，通过比较当前区间内可容纳的水的体积与目标体积，决定向左或向右子树搜索。`Modify`函数用于单点修改，更新线段树节点信息。
    - **核心代码片段**：
```cpp
ll SIZE,SUM;
ll Query(int x,int l,int r,ll lim){
    if(!x) return l;
    if(l==r) return SIZE+=siz(x),SUM+=sum(x),l;
    int mid=l+r>>1,MID=mid+1;
    ll res=1ll*(siz(ls(x))+SIZE)*MID-(sum(ls(x))+SUM);
    if(res>=lim) return Query(ls(x),l,mid,lim);
    else return SIZE+=siz(ls(x)),SUM+=sum(ls(x)),Query(rs(x),mid+1,r,lim); 
}
void Modify(int &x,int l,int r,int pos,int v){
    if(!x) x=++cur;
    siz(x)+=v,sum(x)+=v*pos;
    if(l==r) return ;
    int mid=l+r>>1;
    if(pos<=mid) Modify(ls(x),l,mid,pos,v);
    else Modify(rs(x),mid+1,r,pos,v);
    return ;
}
```
- **作者：Mobius127 (4星)**
    - **关键亮点**：思路简单易懂，明确指出最后有水的试管水面高度相同且答案具有单调性，采用二分答案结合权值线段树（动态开点）的方法，代码逻辑清晰。
    - **重点代码核心思想**：`add`函数用于向权值线段树中添加或删除元素，更新节点的数量和总和信息。`query`函数用于查询一定值域范围内的元素数量和总和。`check`函数根据查询结果判断二分的答案是否可行。
    - **核心代码片段**：
```cpp
void add(int &k, int l, int r, int x, int v){
    if(!k) k=++cnt, V[k]=null;
    if(l==r){
        V[k].num+=v;V[k].sum=V[k].num*x;
        return ;
    }
    if(x<=mid) add(V[k].lc, l, mid, x, v);
    else add(V[k].rc, mid+1, r, x, v);
    return pushup(k);
}
node query(int &k, int l, int r, int x, int y){
    if(!k) return null;
    if(x<=l&&r<=y) return V[k];
    node ret=null;
    if(x<=mid) ret=ret+query(V[k].lc, l, mid, x, y);
    if(mid<y) ret=ret+query(V[k].rc, mid+1, r, x, y);
    return ret;
}
bool check(ld mid, ld sum){
    node ans=chtholly.query(root, 0, INF, 0, turn((ll)mid));
    ld gt=(ld)1ll*ans.num*mid-(ld)ans.sum;
    if(gt>=sum) return 1;
    return 0;
}
```
- **作者：Alex_Eon (4星)**
    - **关键亮点**：详细阐述了思路，指出将倒水分为两部分，通过排序后暴力枚举不支持修改，所以采用权值线段树维护，并在权值线段树上二分选择前多少个试管为更优策略。
    - **重点代码核心思想**：`change`函数用于修改权值线段树节点信息，`query`函数查询前$rk$个元素的总和，`queryrk`函数查询第$rk$个元素的高度，`mim`函数通过二分找到最优的试管选择数量并计算答案。
    - **核心代码片段**：
```cpp
void change(int &rt,int L,int R,int pos,int val)
{
    if(!rt)
        rt=++tot;
    if(L==R)
    {
        t[rt].cnt+=val;
        t[rt].val+=1LL*val*L;
        return;
    }
    int mid=L+R>>1;
    if(pos<=mid)
        change(t[rt].ls,L,mid,pos,val);
    else
        change(t[rt].rs,mid+1,R,pos,val);
    push_up(rt);
    return;
}
LL query(int &rt,int L,int R,int rk)
{
    if(!rt)
        return 0;
    if(rk==t[rt].cnt)
        return t[rt].val;
    if(L==R)
        return L*rk;
    int mid=L+R>>1;
    LL res=0;
    res=query(t[rt].ls,L,mid,min(rk,t[t[rt].ls].cnt));
    if(rk>t[t[rt].ls].cnt)
        res+=query(t[rt].rs,mid+1,R,rk-t[t[rt].ls].cnt);
    return res;
}
int queryrk(int &rt,int L,int R,int rk)
{
    if(!rt)
        return 0;
    if(L==R)
        return L;
    int mid=L+R>>1;
    if(t[t[rt].ls].cnt>=rk)
        return queryrk(t[rt].ls,L,mid,rk);
    return queryrk(t[rt].rs,mid+1,R,rk-t[t[rt].ls].cnt);
}
double mim(LL x)
{
    int l=1,r=n,res=0;
    while(l<=r)
    {
        int mid=l+r>>1,pos=T.queryrk(T.root,0,1e9,mid);
        LL q=T.query(T.root,0,1e9,mid);
        if(1LL*pos*mid-q>x)
            r=mid-1;
        else
            l=mid+1,res=mid;
    }
    if(!res)
        res=1;
    LL q=T.query(T.root,0,1e9,res);
    return 1.0*(q+x)/res;
}
```

### 最优关键思路或技巧
利用二分答案的单调性，将“最大值最小”问题转化为可行性判断问题。同时，巧妙运用权值线段树（动态开点）或平衡树等数据结构，高效统计满足一定条件（如小于等于某个值）的元素信息，从而快速判断二分的答案是否可行。

### 可拓展之处
同类型题通常围绕二分答案结合数据结构维护来考察，类似套路是先分析出答案的单调性，然后通过合适的数据结构来加速判断过程。例如，在一些资源分配、最优值求解等场景下，都可能用到类似思路。

### 洛谷推荐题目
- [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)：通过二分答案来确定满足条件的最小跳跃距离，结合简单的模拟判断可行性。
- [P3853 [TJOI2007]路标设置](https://www.luogu.com.cn/problem/P3853)：同样是二分答案，判断在给定路标数量限制下，相邻路标间的最小距离。
- [P1824 进击的奶牛](https://www.luogu.com.cn/problem/P1824)：二分奶牛之间的最小距离，利用排序和简单遍历判断是否能放置所有奶牛。 

---
处理用时：92.89秒