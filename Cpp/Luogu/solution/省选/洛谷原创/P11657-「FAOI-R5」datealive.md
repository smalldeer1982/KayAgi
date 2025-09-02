# 「FAOI-R5」datealive

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/kidxx2qe.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/is31j7j7.png)

## 题目描述

给定长度为 $n$ 的序列 $c_1,c_2,\cdots,c_n$，$c_i\in\{0,1\}$。序列中每个元素都对应一个括号，若 $c_i=0$ 则该位置上的括号是左括号，若 $c_i=1$ 则该位置上的括号是右括号。

我们用 $f(l,r)$ 表示区间 $[l,r]$ 内的括号序列是否合法。若 $c_l,c_{l+1},\cdots,c_r$ 组成的括号序列合法则为 $f(l,r)=1$，否则则为 $f(l,r)=0$。

合法括号序列的定义：
- 空串是合法括号序列；
- 若 `A` 是合法括号序列，`(A)` 是合法括号序列；
- 若 `A` 和 `B` 是合法括号序列，`AB` 是合法括号序列。

你需要**在线地**执行 $q$ 次操作，分为两种：
- `1 l r`，查询 $\max\limits_{[l',r']\in[l,r]}\{(r'-l'+1)\cdot f(l',r')\}$，即查询 $[l,r]$ 间的最长合法括号子串的长度。
- `2 l r`，对于 $i\in[l,r]$，将 $c_i$ 修改为 $(1-c_i)$，即将 $[l,r]$ 间的括号逐个调转方向。

## 说明/提示

### 样例 1 解释

解密后的结果如下：

```
10 10
0 1 1 0 0 1 0 0 1 1 
2 8 9
2 1 6
2 2 6
2 7 8
2 2 8
2 5 6
2 4 5
1 3 6
1 6 9
1 10 10
```

$7$ 次修改后的括号串为 $)((())()()$。

- 对于第一组询问，截取子串 $[3,6]$ 得 $(())$。整个子串是合法的括号序列，故答案为 $6-3+1=4$。
- 对于第二组询问，截取子串 $[6,9]$ 得 $)()($。子串 $[7,8]$ 是其中最长的合法括号子串，故答案为 $8-7+1=2$。
- 对于第三组询问，截取子串 $[10,10]$ 得 $)$。该子串中合法括号子串为空串，故答案为 $0$。

### 数据规模与约定

**本题采用捆绑测试。**

| Subtask 编号 | $n \le$ | $q \le$ | 分值 | 特殊性质 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $100$ | $100$ | $10$ | × |
| $2$ | $2 \times 10^4$ | $2 \times 10^4$ | $10$ | × |
| $3$ | $4 \times 10^6$ | $10^5$ | $20$ | $\checkmark$ |
| $4$ | $10^5$ | $10^5$ | $30$ | × |
| $5$ | $4 \times 10^6$ | $10^5$ | $30$ | × |

特殊性质：保证没有修改操作。

对于所有数据，$1 \le n\le 4 \times 10^6$，$1\le q \le 10^{5}$，$1 \le l',r' \le n$，$op\in\{1,2\}$，$c_i\in\{0,1\}$。

本题除 Subtask #3 外保证操作类型随机生成，即每次选择一个 $\{1,2\}$ 中的随机数（选到 $1$ 和 $2$ 的概率均为 $50\%$）作为 $op$。

本题题目附件附有大样例。

## 样例 #1

### 输入

```
10 10
0 1 1 0 0 1 0 0 1 1 
2 7 8
2 10 5
2 5 1
2 7 6
2 7 1
2 4 5
2 3 4
1 5 2
1 4 1
1 7 7```

### 输出

```
4
2
0```

## 样例 #2

### 输入

```
20 20
0 0 0 1 1 1 1 0 0 1 0 0 0 1 0 0 0 0 1 1 
2 16 7
2 12 10
1 4 5
1 14 7
1 16 7
2 15 12
1 12 2
1 3 4
1 1 10
2 14 3
2 19 1
1 20 9
2 14 16
1 10 13
1 6 8
2 1 2
1 8 16
1 9 15
1 17 12
2 15 14```

### 输出

```
0
2
8
2
0
2
6
4
0
2
0
0```

# 题解

## 作者：immix (赞：6)

[更好的体验](https://linlexiao.com/posts/a60cdb098078/)

类似题目：
- [P10513 括号](https://www.luogu.com.cn/problem/P10513)
- [P8765 [蓝桥杯 2021 国 AB] 翻转括号序列](https://www.luogu.com.cn/problem/P8765)




## 区间翻转，区间最长合法括号子串

[P11657 「FAOI-R5」datealive](https://www.luogu.com.cn/problem/P11657)

给定一个长度为 $n$ 的括号序列，支持 $m$ 次操作：
1. 翻转 $[l,r]$ 中的括号，即 ```(``` 变 ```)```，```)``` 变 ```(```。
2. 查询子串 $[l,r]$ 最长合法括号子串的长度。

$n\le 4\times 10^6,m\le 1\times 10^5$，保证操作类型随机。


对于翻转来说。我们只用额外维护一个节点保存取反之后的结果，然后翻转操作交换两个节点的内容，不是本题的难点，我们考虑如何求出一个区间的最长合法括号子串。

利用线段树的分治结构，我们能求出了只在左右区间内的结果，考虑如何处理横跨区间两边的子串。

我们知道：一个括号序列能匹配都匹配完之后剩下一定是一段前缀 `)` 和后缀 `(`。（要不然就还有能匹配的部分）

比如序列 `(())))()(()` 最后留下的就是 `))(`。

不失一般性，假设左区间在右边剩下的 `(` 个数更多。

假设匹配了 $k$ 个，我们只需要找到左区间简化后的第 $k+1$ 个 `(`（从右边数）和右边的第一个 `(`（从左边数）。

![](https://cdn.luogu.com.cn/upload/image_hosting/4jju3wn8.png)


我们讨论实现找到这些括号位置的细节。

我们发现，对于一个固定起点来说，开头剩余的 `)` 个数单调不下降。（因为再也没有字符能和它匹配了）

同样地，对于一个固定终点来说，结尾剩余的 `(` 个数也单调不下降。


基于这个单调性，我们可以用线段树二分，花费 $O(\log n)$ 的代价找到这些括号的位置。

对于 `)` 来说，因为是固定起点单调不降，所以只能左往右找到第 $k$ 个 `)`（如果反过来，`)` 就有可能被前面的 `(` 闭合，难以找到实际的位置） ，而对于 `(` 就只能从右往左找了。

直接线段树二分也是可行的，这里提供一种更简单的二分。

对于区间 $[l,r]$ 和一个完全包含它的节点 $o$：


先花 $O(\log n)$ 把 $[l,r]$ 拆分成 $O(\log n)$ 个区间。

```cpp
struct Node{
    int o,l,r;  // 包含 [l,r] 的线段树节点编号和该节点维护区间
    int cntL,cntR,ans; // 左边剩下的)，右边剩下的(，答案
};
Node stk[10000];int tp;
void find_nodes(int o,int ql,int qr,int op){
    if(ql<=t[o][op].l&&t[o][op].r<=qr){stk[++tp]=t[o][op];return;}
    int lch=o<<1,rch=o<<1|1;
    int mid=(t[o][op].l+t[o][op].r)>>1;
    pushdown(o);
    if(ql<=mid)find_nodes(lch,ql,qr,op);
    if(qr> mid)find_nodes(rch,ql,qr,op);
}
```
然后以找到从左边数第 $k$ 个 `)` 为例：
找到 $O(\log n)$ 段中第一个达到 $k$ 个 `)` 的，然后在这一段里面进行二分找到真正的分界点，这样二分就保证了时刻处理的都一定是完整的节点，直接用一个 `while` 循环就足够解决问题。

复杂度仍然是 $O(\log n)$。

```cpp
struct Node{
    int o,l,r;  // 包含 [l,r] 的线段树节点编号和该节点维护区间
    int cntL,cntR,ans; // 左边剩下的)，右边剩下的(，答案
};

// 找到 [ql,qr] 中第 k 个剩的右括号所在的位置（最靠左的那个）
int getkth_L(int o,int ql,int qr,int op,int k){
    tp=0; find_nodes(o,ql,qr,op);
    for(int i=1;i<=tp;i++){
        if(stk[i].cntL >= k){ // 在 i 处二分即可。
            int l = stk[i].l, r = stk[i].r;
            o = stk[i].o;
            while(l<r){
                pushdown(o); // 记得 pushdown
                int mid=(l+r)>>1;
                int lch=o<<1,rch=o<<1|1;
                if(t[lch][op].cntL >= k)r=mid,o=lch;
                else k=k-t[lch][op].cntL+t[lch][op].cntR,l=mid+1,o=rch;
            }
            return l;
        }
        k = k - stk[i].cntL + stk[i].cntR;
    }
    assert(0); // 我们保证一定存在这样的位置
    return -1;
}
```

有了这个，我们就可以开始写 `merge` 函数，用于合并两个节点了。
```cpp
Node merge(const Node& p,const Node& q,int op){
    int elim = min(p.cntR, q.cntL);
    Node ret{min(p.o,q.o)>>1,p.l,q.r,p.cntL+q.cntL-elim,p.cntR+q.cntR-elim,max(p.ans,q.ans)};
    int newans;
    
    if(p.cntR == q.cntL){
        newans =    (q.cntR ? getkth_R(q.o,q.l,q.r,op,q.cntR)-1 : q.r) 
                  - (p.cntL ? getkth_L(p.o,p.l,p.r,op,p.cntL)+1 : p.l) + 1;
    }
    else if(p.cntR >= q.cntL){ 
        // q 的被消耗完了
        newans =    (q.cntR ? getkth_R(q.o,q.l,q.r,op,q.cntR)-1 : q.r) 
                  - (getkth_R(p.o,p.l,p.r,op,q.cntL+1)+1) + 1;
    }
    else{
        // p 的被消耗完了
        newans =    (getkth_L(q.o,q.l,q.r,op,p.cntR+1)-1) 
                  - (p.cntL ? getkth_L(p.o,p.l,p.r,op,p.cntL)+1 : p.l) + 1;
    }
    ret.ans = max(ret.ans, newans);
    return ret;
}
```

分类讨论哪边的括号被消耗完，找到对应的位置，算出横跨的长度更新答案就好了。

建树复杂度 $T(n)=2T(n/2)+O(\log n) = O(n)$，查询复杂度 $O(\log^2 n)$。
总复杂度 $O(n+q\log^2 n)$。

这道题空间卡的也比较紧（主要是 $n$ 太大了）。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 4e6+6;
int a[N];
struct Node{
    int o,l,r;  // 包含 [l,r] 的线段树节点编号和该节点维护区间
    int cntL,cntR,ans; // 左边剩下的)，右边剩下的(，答案
};

Node t[N*4][2];bool tag[N*4];

void inv(int o){
    swap(t[o][0],t[o][1]);
    tag[o] = !tag[o];
}
void pushdown(int o){
    if(tag[o]){
        int lch=o<<1,rch=o<<1|1;
        inv(lch);inv(rch);
        tag[o]=0;
    }
}


Node stk[10000];int tp;
void find_nodes(int o,int ql,int qr,int op){
    if(ql<=t[o][op].l&&t[o][op].r<=qr){stk[++tp]=t[o][op];return;}
    int lch=o<<1,rch=o<<1|1;
    int mid=(t[o][op].l+t[o][op].r)>>1;
    pushdown(o);
    if(ql<=mid)find_nodes(lch,ql,qr,op);
    if(qr> mid)find_nodes(rch,ql,qr,op);
}

// 找到 [ql,qr] 中第 k 个剩的右括号所在的位置（最靠左的那个）
int getkth_L(int o,int ql,int qr,int op,int k){
    tp=0; find_nodes(o,ql,qr,op);
    for(int i=1;i<=tp;i++){
        if(stk[i].cntL >= k){ // 在 i 处二分即可。
            int l = stk[i].l, r = stk[i].r;
            o = stk[i].o;
            while(l<r){
                pushdown(o);
                int mid=(l+r)>>1;
                int lch=o<<1,rch=o<<1|1;
                if(t[lch][op].cntL >= k)r=mid,o=lch;
                else k=k-t[lch][op].cntL+t[lch][op].cntR,l=mid+1,o=rch;
            }
            return l;
        }
        k = k - stk[i].cntL + stk[i].cntR;
    }
    assert(0);
    return -1;
}

// 找到 [ql,qr] 中从右边看，第k个右边剩下的左括号所在的位置（最靠右的那个）
int getkth_R(int o,int ql,int qr,int op,int k){
    tp=0; find_nodes(o,ql,qr,op);
    for(int i=tp;i>=1;i--){
        if(stk[i].cntR >= k){ // 在 i 处二分即可。
            int l = stk[i].l, r = stk[i].r;
            o = stk[i].o;
            while(l<r){
                pushdown(o);
                int mid=(l+r)>>1;
                int lch=o<<1,rch=o<<1|1;
                if(t[rch][op].cntR >= k)l=mid+1,o=rch;
                else k=k-t[rch][op].cntR+t[rch][op].cntL,r=mid,o=lch;
            }
            return l;
        }
        k = k - stk[i].cntR + stk[i].cntL;
    }
    assert(0);
    return -1;
}


Node merge(const Node& p,const Node& q,int op){
    int elim = min(p.cntR, q.cntL);
    Node ret{min(p.o,q.o)>>1,p.l,q.r,p.cntL+q.cntL-elim,p.cntR+q.cntR-elim,max(p.ans,q.ans)};
    int newans;
    
    if(p.cntR == q.cntL){
        newans =    (q.cntR ? getkth_R(q.o,q.l,q.r,op,q.cntR)-1 : q.r) 
                  - (p.cntL ? getkth_L(p.o,p.l,p.r,op,p.cntL)+1 : p.l) + 1;
    }
    else if(p.cntR >= q.cntL){ 
        // q 的被消耗完了
        newans =    (q.cntR ? getkth_R(q.o,q.l,q.r,op,q.cntR)-1 : q.r) 
                  - (getkth_R(p.o,p.l,p.r,op,q.cntL+1)+1) + 1;
    }
    else{
        // p 的被消耗完了
        newans =    (getkth_L(q.o,q.l,q.r,op,p.cntR+1)-1) 
                  - (p.cntL ? getkth_L(p.o,p.l,p.r,op,p.cntL)+1 : p.l) + 1;
    }
    ret.ans = max(ret.ans, newans);
    return ret;
}

void build(int o,int l,int r){
    if(l==r){
        t[o][0] = {o,l,r, a[l]==1,a[l]==0,0};
        t[o][1] = {o,l,r, a[l]==0,a[l]==1,0};
        return;
    }
    int lch=o<<1,rch=o<<1|1;
    int mid=(l+r)>>1;
    build(lch,l,mid);build(rch,mid+1,r);
    t[o][0] = merge(t[lch][0],t[rch][0],0);
    t[o][1] = merge(t[lch][1],t[rch][1],1);
}
void modify(int o,int l,int r,int ql,int qr){
    if(ql <=l && r<=qr){
        inv(o);return;
    }
    pushdown(o);
    int lch=o<<1,rch=o<<1|1;
    int mid=(l+r)>>1;
    if(ql<=mid)modify(lch,l,mid,ql,qr);
    if(qr>mid) modify(rch,mid+1,r,ql,qr);
    t[o][0] = merge(t[lch][0],t[rch][0],0);
    t[o][1] = merge(t[lch][1],t[rch][1],1);
}

Node query(int o,int l,int r,int ql,int qr){
    if(ql<=l && r<=qr)return t[o][0];
    pushdown(o);
    int lch=o<<1,rch=o<<1|1;
    int mid=(l+r)>>1;
    if(qr<=mid)return query(lch,l,mid,ql,qr);
    if(ql>mid)return query(rch,mid+1,r,ql,qr);
    return merge(query(lch,l,mid,ql,qr),query(rch,mid+1,r,ql,qr),0);
}
    

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];

    build(1,1,n);
    int lastans = 0;
    while(m--){
        int op,l,r;cin>>op>>l>>r;
        l=(l+lastans)%n+1,r=(r+lastans)%n+1;
        if(l>r)swap(l,r);
        if(op==1){
            lastans = query(1,1,n,l,r).ans;
            cout << lastans << '\n';
        }
        else modify(1,1,n,l,r);
    }
    return 0;
}
```

---

## 作者：喵仔牛奶 (赞：5)

# Solution

使用线段树，考虑合并时如何计算跨过中点的答案。

观察到一段括号序列能匹配的都匹配后会剩下前面一段右括号和后面一段左括号，合并两区间时实际上是将左区间剩下的左括号和右区间剩下的右括号进行匹配。

这两种括号肯定有一种匹配完，否则能继续匹配得到更优的答案。我们分讨匹配完的是哪种。

如果是左区间剩下的左括号匹配完，设 $k$ 是原来左区间剩下的左括号数，线段树上二分出左区间**最后一个**剩的右括号的位置 $L$ 与右区间第 $k+1$ 个**剩下的括号**的位置 $R$，最大长度即为 $R-L-1$。右区间剩下的右括号匹配的情况是类似的，不再讨论。

关于线段树二分，我采用的方法是先将二分的区间拆分成线段树上的 $\log n$ 段，然后求出第一个满足条件的段，再以那段为根向下二分。

因为有区间取反，还需要再维护一个区间括号取反后的答案，然后修改时直接打 tag 即可。建树的时候直接 pushup，可以推导得出建树的复杂度 $\sum_{i=0}^{\log n}i\cdot2^{\log n-i}=\mathcal{O}(n)$。

合并一次复杂度 $\mathcal{O}(\log n)$，总复杂度 $\mathcal{O}(n+q\log^2 n)$。

---

## 作者：Thomas0702 (赞：1)

我是一个毒瘤呀，我用分块水过了这道题。

~~赛时分析复杂度分析错了，把正解扔了，写分块没写出来。~~

考虑将一个区间中能匹配的括号都匹配完后，肯定会剩下左边的若干个右括号和右边的若干个左括号。对每个块处理这样的结构，并记录两个未匹配的括号之间有多少已匹配的括号。具体见下图，其中“箭头”指向的地方可能有已经匹配的括号，注意中间还有个 $mid$。

![块](https://cdn.luogu.com.cn/upload/image_hosting/sk54wc1h.png)

修改时容易的，散块直接重构，整块打 tag。注意要维护一个块反转前和反转后的两种状态。

查询的时候，如果两个端点在一个块内，直接暴力。

考虑端点不在一个块内的情况，不妨将两边的散块当做整块处理。统计块内的最长合法串是容易的。对于跨过块的合法串，考虑维护下图的一个结构。

![栈](https://cdn.luogu.com.cn/upload/image_hosting/9yakbqvl.png)

其中，``(......(`` 表示来自同一个块内的**连续的左括号**，每个左括号的右边都有一些它所在的块内的已经匹配的括号（即第一张图中的“箭头”），注意这一段左括号可以为空。中间的”方框“表示左右两个块之间**已经匹配的括号**，以及若干个块的 $mid$。特别地，最左边的方框代表最左边的块的 $mid$。

从左到右合并整块。每加入一个新块，不断取出上面的结构的最右边的一个连续段，与新块的右括号匹配，直到新块的右括号用完或者上面的结构中的左括号用完。记 $sum$ 当前的（跨过新块的左端点的）合法串的长度（包括刚刚匹配的、块内本来就匹配的、上面结构中的”方框“）。将 $sum+ex$ 贡献到 $ans$，$ex$ 的取值分下面两种情况。

如果新块的右括号匹配完，$ex$ 为最左边的没匹配的右括号的左边的“箭头”。这时前面的合法串不可能再扩展了，这时将新块的 $mid$ 和右边连续的左括号扔到我们要维护的结构里。

如果新块的右括号用完了，如果还有没匹配的左括号，则 $ex$ 为最右边的没匹配的左括号的右边的“箭头”，否则为 $0$。这时前面的合法串还可以再扩展，将 $sum$ 和新块右边连续的左括号扔到我们要维护的结构里。

用栈维护上面的结构即可。

取块长 $B=\sqrt{N}$，总时间复杂度 $O(Q\sqrt{N})$，实际上我的块长是 $B=1500$。需要卡常。

```cpp
#include<bits/stdc++.h>
using namespace std;
void rd(){}
template<typename T,typename... U> void rd(T &x,U&... arg){
	x=0;int f=1,c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9') x=x*10+c-48,c=getchar();
	x*=f;rd(arg...);
}
const int maxn=4e6+5,B=1500;
int N,Q,a[maxn],b[maxn],tg[maxn];
struct block{
	int mid,Max,L,R,vl[B+5],vr[B+5],sl[B+5],sr[B+5],nl,nr;
	bool tag;
	void build(int l=-1,int r=0,bool tg=0){
		if(~l) L=l,R=r,tag=tg;
		mid=Max=nl=nr=0;
		int lstl=L-1,lstr=R+1;
		for(int i=L,now=0,sum=0;i<=R;i++)
			if(a[i]^tag^1) now++;
			else if(now) now--,sum+=2;
			else lstl=i,vl[++nl]=sum,sum=0;
		for(int i=R,now=0,sum=0;i>=L;i--)
			if(a[i]^tag) now++;
			else if(now) now--,sum+=2;
			else lstr=i,vr[++nr]=sum,sum=0;
		reverse(vr+1,vr+nr+1);
		for(int i=1;i<=nl;i++) sl[i]=sl[i-1]+vl[i],Max=max(Max,vl[i]);
		for(int i=1;i<=nr;i++) sr[i]=sr[i-1]+vr[i],Max=max(Max,vr[i]);
		Max=max(Max,mid=lstr-lstl-1);
	}
}x[maxn/B+5][2];
struct info{int bi,l,r;}stk[maxn];
int mid[maxn],tp1,tp2,ans;
void ins(int i){
	ans=max(ans,x[i][tg[i]].Max);
	int sum=0,l=1,r=x[i][tg[i]].nl;
	while(l<=r&&tp1){
		info t=stk[tp1--];
		int len=min(t.r-t.l+1,r-l+1);
		sum+=2*len;
		if(len==t.r-t.l+1) sum+=mid[tp2--];
		if(!len) continue;
		sum+=x[t.bi][tg[t.bi]].sr[t.r]-x[t.bi][tg[t.bi]].sr[t.r-len];
		sum+=x[i][tg[i]].sl[l+len-1]-x[i][tg[i]].sl[l-1];
		t.r-=len,l+=len;
		if(t.r>=t.l) stk[++tp1]=t;
	}
	if(l>r){
		sum+=x[i][tg[i]].mid;
		while(tp1&&stk[tp1].l>stk[tp1].r)
			sum+=mid[tp2--],tp1--;
		int ex=0;
		if(tp1){
			info t=stk[tp1];
			ex=x[t.bi][tg[t.bi]].vr[t.r];
		}
		ans=max(ans,sum+ex);
		mid[++tp2]=sum;
	}else{
		ans=max(ans,sum+x[i][tg[i]].vl[l]);
		mid[++tp2]=x[i][tg[i]].mid;
	}
	stk[++tp1]={i,1,x[i][tg[i]].nr};
}
int main(){
	rd(N,Q);
	for(int i=1;i<=N;i++) rd(a[i]);
	for(int i=1;i<=N;i++) b[i]=(i+B-1)/B;
	for(int i=1;i<=b[N];i++)
		x[i][0].build((i-1)*B+1,min(N,i*B),0),
		x[i][1].build((i-1)*B+1,min(N,i*B),1);
	while(Q--){
		int op,l,r;rd(op,l,r);
		l=(l+ans)%N+1,r=(r+ans)%N+1;
		if(l>r) swap(l,r);
		if(op==1){
			ans=0;
			if(b[l]==b[r]){
				tp1=0;
				for(int i=l,lst=l-1;i<=r;i++)
					if(a[i]^tg[b[l]]^1) mid[++tp1]=i;
					else if(tp1){
						if(--tp1) ans=max(ans,i-mid[tp1]);
						else ans=max(ans,i-lst);
					}else lst=i;
			}else{
				int L=0,R=b[N]+1;
				tg[L]=tg[b[l]];
				x[L][tg[L]].build(l,b[l]*B,tg[b[l]]);
				tg[R]=tg[b[r]];
				x[R][tg[R]].build((b[r]-1)*B+1,r,tg[b[r]]);
				tp1=0,tp2=0;
				ins(L);
				for(int i=b[l]+1;i<b[r];i++) ins(i);
				ins(R);
			}
			printf("%d\n",ans);
		}else{
			if(b[l]==b[r]){
				for(int i=l;i<=r;i++) a[i]^=1;
				x[b[l]][0].build();
				x[b[l]][1].build();
				continue;
			}
			for(int i=l;i<=b[l]*B;i++) a[i]^=1;
			for(int i=(b[r]-1)*B+1;i<=r;i++) a[i]^=1;
			x[b[l]][0].build();
			x[b[l]][1].build();
			x[b[r]][0].build();
			x[b[r]][1].build();
			for(int i=b[l]+1;i<b[r];i++) tg[i]^=1;
		}
	}
	return 0;
}
```

---

## 作者：xxxxxzy (赞：1)

出题人题解，还是决定来交一篇，虽然题不怎么样。

## 前言
![](https://cdn.luogu.com.cn/upload/image_hosting/mygrxv2s.png)

## Solution

考虑线段树，计算跨过中点的贡献，每次只需要合并两个区间 $[l,mid]$ 和 $[mid+1,r]$。

下文设左括号为 (，右括号为 )。

考虑如何快速合并，我们发现一个区间匹配后一定是若干个右括号加上若干个左括号，我们先维护信息匹配后剩下的左右括号对数。

求出来这个信息之后，发现最长的跨过中点的括号串，实际是等于将左区间的左括号和右区间的右括号进行匹配。

这两种括号一定有一种会匹配完，所以先求出两个值的 $\min$，然后以这个值往中点左右线段树二分。

值得注意的是，这个并不需要拆成 $O(\log n)$ 个区间，直接在当前左节点和右节点二分即可。

这样就做到了 $O(\log n)$ 合并线段树上信息，区间取反操作，直接维护取反后的信息就好。

## 后记

 这类问题好像叫做单侧递归线段树？这个题是 23.12 左右出出来的，现在看起来，确实是有点标准了。
 
搞不懂为什么有人会被卡常。

std 最大点 1.2s，空间 11MB，加了底层分块，本来想卡空间的但是没卡成。

验题人最大点 3.5s，所以真的不卡常。

---

