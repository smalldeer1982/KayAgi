# 题目信息

# 「TERRA-OI R1」别得意，小子

## 题目背景

战至中途，蓝紫色天空瞬间变为黑压压一片，噬神者身上一些紫色外壳开始脱落，化为更小的蟒蛇，这些小家伙从出现开始便不要命的向你冲过来，刚清理掉这些小家伙，迷雾中忽然涌现出一张血盆大口，噬神者正向你冲击而来......

## 题目描述

现给定一个有 $n$ 段的分段函数，每一段可能是一个一次函数或者一个二次函数，并有 $q$ 次询问，每次询问 $x=k$ 时 $y$ 的取值或是 $y=k$ 与函数有多少个交点。



## 说明/提示

#### 【样例解释 #1】

三段函数分别为 $y=x+2$，$y=x^2-2x+1$，$y=x$。

对于当 $x=4$ 时套入第二段函数可以得到结果为 $9$。

而直线 $y=5$ 只与第一段与第二段函数相交，并且各只有一个交点，所以结果为 $2$。

显而易见，第三个询问对应的直线不与函数相交。

第四个询问虽然与第一段函数交于 $x=0$ 的位置，但 $0$ 不在该函数区间内，故舍去。

------------

#### 【数据范围】

**本题采用捆绑测试。**

| Subtask | Score | $n,q\le$ | limit |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10$ | $100$ | 无 |
| $2$ | $15$ | $10^3$ | $r_n\le 5\times 10^3$ |
| $3$ | $20$ | $2\times 10^5$ | 不存在询问 $2$ |
| $4$ | $25$ | $2\times 10^5$ | 不存在二次函数 |
| $5$ | $30$ | $2\times 10^5$ | 无 |

对于 $100\%$ 的数据，$1\le n,q\le 2\times 10^5$，$0\le l_i,r_i\le10^9$，$\forall i\in [1,n],r_i>l_i$ 。

所有的函数系数均在 **$64$ 位有符号整型变量**存储范围内，并且运算结果与每个函数式中任何一项的最大值与最小值不会超过 **$64$ 位有符号整型变量**存储范围。所有询问参数均在 **$32$ 位有符号整型变量**范围内。

（即 $-4\times 10^{18}\le k,a,b,c\le 4\times 10^{18}$，$-10^9\le x\le 10^9$）

------------
#### 【提示】

采用浮点数据时建议使用 long double，避免产生精度问题。

upd：添加一组 hack 数据，未通过会显示为“Unaccepted 100pts”。

## 样例 #1

### 输入

```
3 4
0 3 1 1 2
3 6 2 1 -2 1
6 10 1 1 0
1 4
2 5
2 114514
2 2```

### 输出

```
9
2
0
0```

## 样例 #2

### 输入

```
6 8
0 4 2 1 -4 0 
4 6 1 2 -10 
6 11 1 1 -19 
11 19 2 -1 -30 559 
19 29 1 1 -58 
29 38 1 1 -68 
1 11
2 4
2 -1
1 21
2 -5
2 2
1 34
2 1
```

### 输出

```
-8
1
4
-37
1
2
-34
2
```

# AI分析结果

### 综合分析与结论

本题的核心在于处理分段函数的查询，尤其是对于二次函数的处理较为复杂。各题解的思路主要集中在二分查找、差分、离散化、动态开点线段树等算法上。其中，MCRS_lizi和kbtyyds的题解较为全面，分别通过`map`和离散化处理二次函数的复杂情况，而聊机的题解则通过动态开点线段树实现了较为简洁的解决方案。jifbt的题解则通过将二次函数分段处理，简化了讨论。

### 所选高星题解

#### 1. MCRS_lizi (5星)
**关键亮点**：
- 使用`map`进行差分，避免了大规模数组的内存问题。
- 详细讨论了二次函数的对称轴和顶点处理，特别是浮点数精度的控制。
- 代码结构清晰，注释详细，易于理解。

**个人心得**：
- 作者提到二次函数的顶点处理困扰了三四天，最终通过浮点数精度控制和分类讨论解决了问题。

**核心代码**：
```cpp
inline void tag(register int x) {
    register int aa=a[x].a,bb=a[x].b,cc=a[x].c;
    if(a[x].op==1) {
        line(a[x].l,a[x].r,x);
    } else {
        long double mid=-1.0*bb/(2*aa);
        register int top=ceil(a[x].a*mid*mid+a[x].b*mid+a[x].c);
        if(mid<=a[x].l||mid-e>a[x].r||bb%(2*aa)==0&&-bb/(2*aa)==a[x].l) {
            line(a[x].l,a[x].r,x);
        } else if(top<=f(x,a[x].l)&&aa<0||top>=f(x,a[x].l)&&aa>0) {
            if(aa<0) {
                upd(f(x,a[x].r),1),upd(top,-1);
            } else {
                upd(f(x,a[x].r)+1,-1),upd(top,1);
            }
        } else {
            if(aa<0) {
                int tp=-2;
                if(fabs(a[x].a*mid*mid+a[x].b*mid+a[x].c-(long double)top)<=e) {
                    upd(top+1,-1);
                    tp++;
                }
                upd(top,tp),upd(f(x,a[x].l)+1,1),upd(f(x,a[x].r),1);
            } else {
                int tp=2;
                if(fabs(a[x].a*mid*mid+a[x].b*mid+a[x].c-(long double)top)<=e) {
                    upd(top+1,1);
                    tp--;
                }
                upd(top,tp),upd(f(x,a[x].l),-1),upd(f(x,a[x].r)+1,-1);
            }
        }
    }
}
```

#### 2. kbtyyds (4.5星)
**关键亮点**：
- 通过离散化处理一次函数和二次函数的值域，简化了差分操作。
- 详细讨论了二次函数的对称轴和顶点处理，特别是对顶点是否为整点的处理。

**核心代码**：
```cpp
struct func {
    int l,r,ty,a,b,c,k;
    inline void solve() {
        if(ty==1) {
            int tl,tr;
            if(k>0) tl=calc(l)+1,tr=calc(r);
            else tl=calc(r),tr=calc(l)-1;
            len++,p[len].l=tl,p[len].r=tr;
        } else {
            long double tmp=-b/2.0l/a;
            if(tmp>l&&tmp<=r) {
                int tl1,tr1,tl2,tr2;
                long double top=(4.0l*a*c-b*b)/4.0l/a;
                if(a>0) {
                    tl1=ceil(top),tr1=calc(l)-1;
                    tl2=ceil(top),tr2=calc(r);
                    if(ceil(top)==top) tl2++;
                } else {
                    tl1=calc(l)+1,tr1=floor(top);
                    tl2=calc(r),tr2=floor(top);
                    if(floor(top)==top) tr2--;
                }
                len++,p[len].l=tl1,p[len].r=tr1;
                len++,p[len].l=tl2,p[len].r=tr2;
            } else {
                int tl,tr;
                if((a>0&&tmp<=l)||(a<0&&tmp>r)) tl=calc(l)+1,tr=calc(r);
                else tl=calc(r),tr=calc(l)-1;
                len++,p[len].l=tl,p[len].r=tr;
            }
        }
    }
}f[S];
```

#### 3. 聊机 (4星)
**关键亮点**：
- 使用动态开点线段树处理大规模值域问题，避免了离散化的复杂性。
- 代码简洁，易于实现。

**核心代码**：
```cpp
void update(int p,ll l,ll r,ll L,ll R,int x) {
    if(l>=L&&r<=R) {
        lz[p]+=x;
        return ;
    }
    pushdown(p);
    ll mid=(l+r)>>1;
    if(mid>=L) update(ls[p],l,mid,L,R,x);
    if(mid<R) update(rs[p],mid+1,r,L,R,x);
    return ;
}
```

### 最优关键思路与技巧
1. **二分查找**：用于快速定位查询点所在的函数区间。
2. **差分与离散化**：处理大规模值域问题，避免内存和时间开销。
3. **动态开点线段树**：适用于大规模值域且需要动态更新的场景。
4. **二次函数的对称轴与顶点处理**：通过分段处理简化讨论，特别是浮点数精度的控制。

### 可拓展之处
- 类似问题可以扩展到更高次函数的分段处理，或者多维度函数的查询。
- 动态开点线段树可以用于其他需要处理大规模值域的问题，如区间修改、单点查询等。

### 推荐题目
1. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
2. [P3373 【模板】线段树 2](https://www.luogu.com.cn/problem/P3373)
3. [P5490 【模板】扫描线](https://www.luogu.com.cn/problem/P5490)

---
处理用时：50.77秒