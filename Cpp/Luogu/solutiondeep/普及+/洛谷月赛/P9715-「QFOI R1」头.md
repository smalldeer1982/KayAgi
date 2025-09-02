# 题目信息

# 「QFOI R1」头

## 题目背景

可以看看这个讨论：<https://www.luogu.com.cn/discuss/703835>。

## 题目描述

小 R 是一个可爱的女孩子。有一天，她在被摸头时，突然灵光乍现，便随手加强了一道题给你做。

这道题的名字叫涂色游戏。初始时你有一个 $n$ 行 $m$ 列的网格，所有格子上都没有颜色。有 $k$ 种颜色的刷子，颜色编号为 $1\sim k$。然后给出 $q$ 次操作，每次操作给出 $op,l,r,c,t$ 五个参数：

- 如果 $op=1$，表示将第 $l\sim r$ 行的所有格子涂成颜色 $c$。
- 如果 $op=2$，表示将第 $l\sim r$ 列的所有格子涂成颜色 $c$。
- 如果 $t=0$，意味着如果涂色时遇到已经被染色的格子，就不再进行染色。
- 如果 $t=1$，意味着如果涂色时遇到已经被染色的格子，就用新的颜色覆盖它。

在所有涂色操作结束以后，对于每种颜色，求出有多少个格子被染成了这种颜色。

## 说明/提示

**样例 $1$ 解释**

用浅灰色表示颜色 $1$，灰色表示颜色 $2$。

涂色过程如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/gl7dmh5b.png)

共有 $17$ 个区域被染成颜色 $1$，$7$ 个区域被染成颜色 $2$。

---

**数据范围**

本题共 $20$ 个测试点，每个测试点 $5$ 分。

对于全部数据，保证 $1\le n,m,q\le 2\times 10^6$，$1\le k\le 5\times 10^5$，$op\in\{1,2\}$，若 $op=1$ 则 $1\le l\le r\le n$，若 $op=2$ 则 $1\le l\le r\le m$，$1\le c\le k$，$t\in\{0,1\}$。

- 对于测试点 $1\sim 3$：保证 $n,m,k,q\le 200$。
- 对于测试点 $4\sim 6$：保证 $n,m,k,q\le 2\times 10^3$。
- 对于测试点 $7\sim 9$：保证 $n,m,k,q\le 10^5$，$op=1$。
- 对于测试点 $10\sim 12$：保证 $n,m,k,q\le 10^5$，$t=1$。
- 对于测试点 $13\sim 18$：保证 $n,m,k,q\le 10^5$。
- 对于测试点 $19\sim 20$：无特殊限制。

## 样例 #1

### 输入

```
5 5 2 4
1 2 4 1 0
2 4 5 1 1
2 2 4 2 0
1 1 1 2 1```

### 输出

```
17 7```

## 样例 #2

### 输入

```
5 5 3 6
2 1 3 3 1
2 2 4 1 0
1 4 4 2 0
2 1 1 1 0
1 2 5 2 0
1 1 5 3 0```

### 输出

```
5 4 16```

# AI分析结果

• 综合分析与结论：
    - 本题主要难点在于处理不同覆盖规则（t = 0和t = 1）的染色操作，以及高效统计每种颜色的格子数。众多题解的核心思路是通过调整操作顺序，将t = 1的操作转化为类似t = 0的操作，再进行处理。
    - 算法要点包括使用并查集、线段树、链表等数据结构来维护行和列的染色状态，以优化时间复杂度。
    - 从质量上看，部分题解思路清晰、代码可读性较好且有一定优化，但整体达到4星及以上的较少。

所选的题解：
  - **作者：registerGen（5星）**
    - **关键亮点**：提供官方题解，详细阐述多种算法。算法一为暴力染色统计，算法二针对t = 1时倒序操作并利用线段树维护行列染色状态，算法三优化算法二，使用单向链表替代线段树，均摊时间复杂度至线性，算法四提出合理安排操作顺序，先执行t = 1的操作再执行t = 0的操作，时间复杂度为O(n + m + q)。
    - **重点代码**：
```cpp
struct Solver {
  int sum, a[N + 10], nxt[N + 10];

  inline void modify(int ql, int qr) {
    int lst = 0;
    for (int i = ql; i <= qr; i = nxt[i]) {
      if (a[i] == 0) sum++;
      a[i] = 1;
      if (lst) nxt[lst] = nxt[qr];
      lst = i;
    }
  }

  inline int query(int ql, int qr) {
    int res = 0;
    for (int i = ql; i <= qr; i = nxt[i]) {
      res +=!a[i];
    }
    return qr - ql + 1 - res;
  }
} tr, tc;

void modify(int id) {
  int opt = qry[id].opt, l = qry[id].l, r = qry[id].r, c = qry[id].c;
  if (opt == 1) {
    int cntr = tr.query(l, r), cntc = tc.sum;
    ans[c] += 1LL * (r - l + 1 - cntr) * (m - cntc);
    tr.modify(l, r);
  } else {
    int cntr = tr.sum, cntc = tc.query(l, r);
    ans[c] += 1LL * (n - cntr) * (r - l + 1 - cntc);
    tc.modify(l, r);
  }
}
```
    - **核心实现思想**：通过单向链表nxt维护每行/列中未染色的下一个位置，modify函数用于更新染色状态，query函数用于查询指定区间内未染色的数量，modify函数根据操作类型计算每种颜色的贡献。

  - **作者：SamHJD（4星）**
    - **关键亮点**：先对操作按t值和时间顺序排序，使得操作变为每次都为覆盖染色的形式。逆序处理操作，利用链表处理行和列的染色情况，计算每次操作对颜色的贡献，时间复杂度为O(n + m + q)。
    - **重点代码**：
```cpp
bool cmp(nodeq a,nodeq b){
    if(a.t!=b.t) return a.t<b.t;
    else if(a.t==1) return a.id<b.id;
    else return a.id>b.id;
}
signed main(){
    scanf("%lld%lld%lld%lld",&n,&m,&k,&Q);
    for(int i=1;i<=Q;++i){
        scanf("%lld%lld%lld%lld%lld",&q[i].op,&q[i].l,&q[i].r,&q[i].c,&q[i].t);
        q[i].id=i;
    }
    sort(q+1,q+Q+1,cmp);
    for(int i=1;i<=n+1;++i) nxt[i][1]=i;
    for(int i=1;i<=m+1;++i) nxt[i][2]=i;
    last[1]=n;
    last[2]=m;
    for(int i=Q;i>=1;--i){
        int cnt=0,x;
        for(int j=q[i].l;j<=q[i].r;j=nxt[j+1][q[i].op]){
            if(!mp[j][q[i].op]) cnt++,last[q[i].op]--;
            mp[j][q[i].op]=1;
            if(x<=q[i].r) nxt[j][q[i].op]=nxt[q[i].r+1][q[i].op];
        }
        sum[q[i].c]+=cnt*last[3-q[i].op];
    }
```
    - **核心实现思想**：cmp函数定义操作的排序规则，main函数中先读入操作并排序，初始化链表nxt和记录剩余未染色行/列数的last数组。逆序遍历操作，通过链表计算每次操作中未染色的行/列数，进而计算对颜色的贡献。

  - **作者：262620zzj（4星）**
    - **关键亮点**：根据数据范围想到分别处理行和列信息，离线处理操作，先倒序进行t = 1的操作，再正着进行t = 0的操作，统一操作特性。使用线段树分别维护行和列的涂色情况，计算每次操作对颜色的贡献，同时提出一些优化和注意点。
    - **重点代码**：
```cpp
void build(int p,int l,int r){
    int ls=p<<1,rs=p<<1|1,mid=l+r>>1;
    if(l==r){
        tr[c][p].l=tr[c][p].r=l;
        tr[c][p].v=1;
        return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
    tr[c][p].l=tr[c][ls].l;
    tr[c][p].r=tr[c][rs].r;
    tr[c][p].v=r-l+1;
}
void add(int p,int L,int R){
    int ls=p<<1,rs=p<<1|1,l=tr[c][p].l,r=tr[c][p].r;
    if(r<L||R<l)return;
    if(tr[c][p].v==0)return;
    if(L<=l&&r<=R){
        tr[c][p].v=0;
        return;
    }
    add(ls,L,R);
    add(rs,L,R);
    tr[c][p].v=tr[c][ls].v+tr[c][rs].v;
}
int query(int p,int L,int R){
    int ls=p<<1,rs=p<<1|1,l=tr[c][p].l,r=tr[c][p].r;
    if(r<L||R<l||tr[c][p].v==0)return 0;
    if(L<=l&&r<=R)return tr[c][p].v;
    return query(ls,L,R)+query(rs,L,R);
}
int main(){
    read(n,m,k,q);
    for(int i=1,tt,l,r,c,t;i<=q;i++){
        read(tt,l,r,c,t);
        if(t==1)op1.push_back((operation){tt,l,r,c});
        else op0.push_back((operation){tt,l,r,c});
    }
    for(int i=0;i<op1.size();i++)op[op1.size()-i]=op1[i];
    for(int i=0;i<op0.size();i++)op[op1.size()+i+1]=op0[i];
    c=1;
    build(1,1,n);
    c=0;
    build(1,1,m);
    for(int i=1;i<=q;i++){
        int l=op[i].l,r=op[i].r,w=op[i].c;
        if(op[i].dir==1){
            c=1;
            int tmp=query(1,l,r);
            c=0;
            ans[w]+=1ll*tmp*query(1,1,m);
            c=1;
            add(1,l,r);
        }
        else{
            c=0;
            int tmp=query(1,l,r);
            c=1;
            ans[w]+=1ll*tmp*query(1,1,n);
            c=0;
            add(1,l,r);
        }
    }
```
    - **核心实现思想**：build函数构建线段树，add函数用于区间修改，query函数用于区间查询。main函数中先读入操作并按t值分类存储，调整操作顺序后，利用线段树分别维护行和列的涂色情况，计算每次操作对颜色的贡献。

**最优关键思路或技巧**：
    - **操作顺序调整**：将t = 1的操作倒序执行，t = 0的操作顺序执行，使得所有操作统一为类似t = 0的形式，避免复杂的覆盖关系处理。
    - **数据结构选择**：使用并查集、链表或线段树维护行和列的染色状态，优化时间复杂度。如并查集和链表能达到线性时间复杂度，线段树通过优化也能接近线性时间复杂度。

**可拓展之处**：
    - 同类型题常涉及区间操作和状态维护，类似算法套路包括离线处理、合理安排操作顺序以及选择合适的数据结构。例如在处理区间覆盖、区间查询等问题时，可借鉴本题调整操作顺序和使用数据结构优化的思路。

**推荐题目**：
    - [P2391 白雪皑皑](https://www.luogu.com.cn/problem/P2391)：与本题类似，涉及区间染色和统计，可练习使用并查集维护染色状态。
    - [P1501 积木城堡](https://www.luogu.com.cn/problem/P1501)：同样是区间操作问题，可锻炼对区间处理和数据结构应用的能力。
    - [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)：经典的线段树模板题，有助于巩固线段树的基本操作和应用，为解决本题这类结合区间操作与统计的问题打下基础。

**个人心得摘录**：无。 

---
处理用时：126.03秒