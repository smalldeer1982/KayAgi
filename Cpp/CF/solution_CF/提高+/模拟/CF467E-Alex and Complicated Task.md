# Alex and Complicated Task

## 题目描述

After you have read all the problems, probably, you think Alex is genius person. That's true! One day he came up with the following task.

Given a sequence of integer numbers $ a_{1},a_{2},...,a_{n} $ . You are to find a longest sequence $ b_{1},b_{2},...,b_{4m} $ , that satisfies the following conditions:

- $ b_{4k+1}=b_{4k+3} $ for all valid integer $ k $ ;
- $ b_{4k+2}=b_{4k+4} $ for all valid integer $ k $ ;
- sequence $ b $ is subsequence of $ a $ (not necessarily contiguous subsequence).

And finally... Alex had given this complicated task to George, and George gave it to you. Help George to cope with the task.

## 样例 #1

### 输入

```
4
3 5 3 5
```

### 输出

```
4
3 5 3 5
```

## 样例 #2

### 输入

```
10
35 1 2 1 2 35 100 200 100 200
```

### 输出

```
8
1 2 1 2 100 200 100 200
```

# 题解

## 作者：_edge_ (赞：4)

没人写题解？

CF 官方题解好像是一个非常神仙的贪心，那我来说一下 DP 做法。

设 $f_i$ 表示前 $i$ 个能被拿出来多少个子序列，这时候不能直接转移。

必须枚举 $j$，然后判断 $(j,i]$ 里面是否存在一个长度为 $4$ 的合法子序列。

如何确定 $j$ 的范围就是最核心的问题了，如果能确定的话可以随手拿数据结构维护。

思考这么一个问题，我们假设 $nxt_i$ 表示 $i$ 后面第一个和他一样的点。

我们先处理掉 $x,x,x,x$ 的情况，直接找后面的四个相等的就可以了。

那么我们需要寻找的即为 $x,y,nxt_x,nxt_y$，那么这样的话就能从 $x$ 转移到 $nxt_y$ 了。

这一步有个贪心，有没有可能其他的决策更加优秀？

答案是否定的，因为如果出现了 $x,nxt_x,y,nxt_{nxt_x},nxt_y$ 的情况，然后 $x$ 和 $nxt_{nxt_x}$ 匹配，必然有 $nxt_x$ 和 $nxt_{nxt_x}$ 匹配更加优秀。

然后就很好做了，如果我们把 $i$ 视为左端点，$nxt_i$ 视为右端点，就是对每条线段找到和他有交，并且不包含，然后权值为 $i$，要求权值最大。

那么思考这个问题类似于二维数点，也就是说需要满足的条件是：

$[a,b]$ 和 $[c,d]$ 有交。

那么就是 $a \le c$ 并且 $c \le b \le d$。

前面那个可以直接排序消掉，后面那个可以上线段树维护区间最大值。

于是再 DP 一下记录方案即可。

代码写的比较冗余，实际上没那么长，个人认为这种思路更好想。

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int INF=1e6+5;
int n,nxt[INF],a[INF],id[INF],pre4[INF];
map <int,int> la,la1;
struct Segment{
    #define ll tl[id]
    #define rr tr[id]
    #define ls(x) x<<1
    #define rs(x) x<<1|1
    int tl[INF<<2],tr[INF<<2],sum[INF<<2];
    void push_up(int id) {
        sum[id]=max(sum[ls(id)],sum[rs(id)]);
    }
    void build(int l,int r,int id) {
        ll=l;rr=r;
        if (ll==rr) {sum[id]=0;return ;}
        int Mid=(ll+rr)>>1;
        build(l,Mid,ls(id));
        build(Mid+1,r,rs(id));
        push_up(id);
    }
    void add(int l,int x,int id) {
        if (ll==rr) {
            sum[id]=x;
            return ;
        }
        int Mid=(ll+rr)>>1;
        if (l<=Mid) add(l,x,ls(id));
        else add(l,x,rs(id));
        push_up(id);
    }
    int query(int l,int r,int id) {
        if (l<=ll && rr<=r) return sum[id];
        int Mid=(ll+rr)>>1;
        if (l>Mid) return query(l,r,rs(id));
        else if (r<=Mid) return query(l,r,ls(id));
        else return max(query(l,r,ls(id)),query(l,r,rs(id)));
    }
}T1;
struct _node_edge{
    int to_,next_,disv_;
}edge[INF<<1];
int tot,head[INF],pre[INF],pre1[INF],pre2[INF],pre3[INF];
void add_edge(int x,int y,int z) {
    edge[++tot]={y,head[x],z};
    head[x]=tot;
}
namespace Sub {
    void print(int x) {
        if (x==0) return ;
        print(pre3[x]);
        if (pre1[x])
            cout<<a[pre2[x]]<<" "<<a[pre1[x]]<<" "<<a[pre4[x]]<<" "<<a[x]<<" ";
    }
    int f[INF];
    void main() {
        f[0]=0;
        for (int x=1;x<=n;x++) {
            f[x]=f[x-1];pre3[x]=x-1;
            for (int i=head[x];i;i=edge[i].next_) {
                int v=edge[i].to_,d=edge[i].disv_;
                if (f[v-1]+4<=f[x]) continue;
                // cout<<v<<" -> "<<x<<" "<<id[i]<<" yiw?\n";
                pre[x]=nxt[v];pre1[x]=d;pre2[x]=v;pre3[x]=v-1;
                pre4[x]=nxt[pre2[x]];
                if (id[i]) pre4[x]=nxt[nxt[pre2[x]]];
                f[x]=f[v-1]+4;
            }
        }

        cout<<f[n]<<"\n";
        print(n);
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for (int i=1;i<=n;i++) cin>>a[i];
    for (int i=n;i;i--) {
        if (la[a[i]]) nxt[i]=la[a[i]];
        else nxt[i]=n+1;
        la[a[i]]=i;
    }

    // for (int i=1;i<=n;i++) f[i][0]=nxt[i],f1[i][0]=i;
    // for (int i=1;i<=25;i++) {
    //     if ((1ll<<i)>n) break;
    //     for (int j=1;j+(1<<i)-1<=n;j++) {
    //         if (f[j][i-1]>f[j+(1<<(i-1))][i-1]) 
    //             f[j][i]=f[j+(1<<(i-1))][i-1],f1[j][i]=f1[j+(1<<(i-1))][i-1];
    //         else f[j][i]=f[j][i-1],f1[j][i]=f1[j][i-1];
    //     }
    // }
    // for (int i=1;i<=n;i++)
    //     cout<<nxt[i]<<" ";
    // cout<<" endl\n";
    T1.build(1,n,1);
    for (int i=1;i<=n;i++) {

        int R=i;
        for (int j=1;j<=3;j++) R=nxt[R];
        if (R<=n) add_edge(R,i,nxt[i]),id[tot]=1;
    }

    //     if (nxt[i]==n+1) continue;
    //     if (i==nxt[i]-1) continue;
    //     pii k1=T1.query(i+1,nxt[i]-1,nxt[i],1);
    //     int kk=k1.se;

    //     // cout<<kk<<" kekkqwe\n";
    //     // i->kk->nxt[i]->nxt[kk]
    //     if (i<kk && kk<nxt[i] && nxt[i]<nxt[kk]) add_edge(nxt[kk],i,kk);
    // }
    
    for (int i=1;i<=n;i++) {
        if (nxt[i]==n+1) continue;
        if (i==nxt[i]-1) continue;
        int kk=T1.query(i+1,nxt[i]-1,1);
        // cout<<kk<<" "<<nxt[i]<<" yiwiyw\n";
        if (kk<i && i<nxt[kk] && nxt[kk]<nxt[i]) add_edge(nxt[i],kk,i);
        T1.add(nxt[i],i,1);
    }
    Sub::main();
    return 0;
}
```


---

