# Chino的试卷

## 题目背景

orz trz

Chino参加了萌妹子期末考试，又到了发试卷的时候了，但是，老师 $ygg$ 与 老师 $ggy$ 就怎样发试卷才最省力这一事发生了一些争论。现在，为了解决这一矛盾，你决定帮Chino用数据说话。

下面是 $ygg$ 老师的发试卷策略，请你帮他计算发完试卷要走的总路程。

## 题目描述

为了简化问题，我们规定Chino的同学们(妹子们)都参加了考试，且坐在一排，顺次位置的编号为 $1\sim n$，不妨规定位置 $i$, $j$ 之间的路程为 $|i - j|$。每张试卷上都有一个编号，代表要发给坐在这个编号的妹子。

$ygg$ 老师正在分发试卷。我们定义这个分发试卷的老师有两只手。刚开始，所有的试卷都在 $ygg$ 老师的左手，老师位于位置 $s$ 处。发试卷时，$ygg$ 老师会用右手拿起左手顶部的一张试卷。如果这是最后一张需要发的试卷，显然他别无选择，只能走到这张试卷主人的位置上去发这张试卷。如果他的左手还有试卷，那么他会进行一次比较，比较发左手顶部的那张试卷走的路程短，还是发右手那张试卷走的路程短。如果左手那张试卷走的路程短，他会把右手的试卷放到左手试卷的最下面，不然的话，他会直接发掉右手的试卷，并停留在刚发完这张试卷的位置。无论如何，他都会从左手再拿一张试卷，来进行下一步的决策，直到所有卷子都被发完。

现在，给定试卷的初始顺序序列$p$，以及老师的初始位置 $s$，问他要发完所有试卷走过的总路程是多少。

Chino想快速的知道答案，所以你要在$+4s$内完成这道题哦qwq

Orz yky,dyh,wjk,jjy,cxr,gsy,cpy,zcy,tyz,yy,hz,zhr,ygg

## 说明/提示

| 测试点 |     $n= $     | 测试点 |     $n =$     |
| :----: | :-----------: | :----: | :-----------: |
|   1    | $3\times10^1$ |   11   | $3\times10^5$ |
|   2    | $3\times10^2$ |   12   | $3\times10^5$ |
|   3    | $3\times10^2$ |   13   | $3\times10^5$ |
|   4    | $3\times10^3$ |   14   | $3\times10^5$ |
|   5    | $3\times10^3$ |   15   | $3\times10^5$ |
|   6    | $3\times10^3$ |   16   | $3\times10^6$ |
|   7    | $3\times10^4$ |   17   | $3\times10^6$ |
|   8    | $3\times10^4$ |   18   | $3\times10^6$ |
|   9    | $3\times10^4$ |   19   | $3\times10^6$ |
|   10   | $3\times10^4$ |   20   | $3\times10^6$ |

对于前$15$个测试点，时限$1s$

对于后$5$个测试点，时限$4s$

## 样例 #1

### 输入

```
5 1
2 3 1 4 5```

### 输出

```
8```

# 题解

## 作者：decoqwq (赞：4)

~~比赛结束这么久一直忘了把官方题解放上来~~

题目归纳为，给定一个循环队列，每次比较队头的两个元素 $p1,p2$，距离当前指针的位置，如果 $p1$ 不比 $p2$ 远，令指针指向 $p1$, 并弹出队列，否则将 $p1$ 放回队尾
统计指针移动距离

模拟可以获得$30$分

因为每个元素只会出队一次，所以我们考虑优化寻找下一个出队元素的过程

考虑二分，但是这没有单调性啊，比如我可能在第 $i$ 个位置停下，却不一定
能在第 $i + 1$ 个位置停下啊。
换一种判断方式，如果我们会在区间 $[1, i]$ 中的某个位置停下，
就一定会在区间 $[1, i + 1]$ 的某个位置停下
所以如何判断对于当前指针 $s$，我们是否会在区间 $[1, i]$ 停下呢？

我们可以发现，对于相邻的两个元素 $pi, pi+1$，是可以找到一条，分界线的，其中分界线的一侧都会被拦下来，而另一侧都可以通过

我可以维护区间中分界线的交集！线段树即可

所以思路就是先二分，然后判断区间的交集是否能拦下从$ s$ 处出发的老师

最终复杂度$O(nlog^2n)$

如果写了正解还是 $TLE$ 可能只是常数过大(，$std$ 没有加快读仍然只在 $2s$ 内完成了

---

## 作者：redegg (赞：0)

写太多了，总体而言是下面这句话。

```
一句话题解：相邻两张试卷的中点与s的关系，决定了前一张试卷是否能发放。
用线段树等数据结构维护中点即可。
剩下的就是模拟了。
```

这题最重要的部分是这个性质：

我们现在没发的试卷序列是 $p$ 。

对于 $p[1],p[2]$ ，求出两数连线中点 $mid=\frac{(p[1]+p[2])}{2}$ 。 如果 $p[1]<p[2]$ ，则当且仅当 $s\le mid$ 时，会发掉 $p[1]$ ，同理 ，若 $p[1]>p[2]$ 时，$s\ge mid$ 才会选择发掉 $p[1]$ 。

那么创建两个中点序列 $a,b$ ，一个序列的中点表示当 $s\le a[i]$ 时，可以发掉 $a[i]$ 所对应的两张卷子的第一份卷子。另一个同理，在 $s\ge b[i]$ 时，可以发掉对应两张中的前一张。

可以明确的是，对于相邻两张卷子来说，就会有一个中点仅存在于 $a$ 或者是 $b$ 中。

那么我们现在要找到的是，当前两个序列中，第一个可以发掉卷子的对应中点的位置。这一部分可以用两 线段树/平衡树 维护，然后 线段树/平衡树 二分 找到。对于这个点 $x$ ，在这个点前面点会被集体移动到序列末端（因为前面的卷子被放到了卷子堆的末端，对应的中点也会被提到末端），并且因为这个点的对应的第一份卷子被发掉了，那么这个点也就不存在了，而且这个点的上一个点也因为第二份卷子被发掉也不存在了，但是同时又会创造一个新的点，也就是新的相邻两张卷子又会产生新的中点。

那么现在最困难的是如何把一段序列整体移动到末尾，对于平衡树(splay)来说很好办直接把前面接到后面就行了，但是这里选择用线段树也很简单，可以直接先查询后区间，再查询前面的区间，就等同与把前面区间接到后面了，给后区间的查询到的答案附上更高的优先级即可。

代码很长，可以尝试把两棵线段树合并，但是冬天了脑子不灵通，就暴力无脑了。复杂度 $O(nlogn)$ 。

```
#include <bits/stdc++.h>
using namespace std;

void read(int &an){
    char ch=getchar();an=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')an=(an<<3)+(an<<1)+ch-'0',ch=getchar();
}

const int inf=1e7;
const int MAXN=1e6+2;
int n;
int maxn[12*MAXN],minn[12*MAXN];
int p=1,s;
int a[3*MAXN];

void updatemax(int l,int r,int x,int v,int id){
    if(l==r){
        maxn[id]=v;return ;
    }
    int mid=(l+r)/2;
    if(mid>=x)updatemax(l,mid,x,v,id*2);
    else updatemax(mid+1,r,x,v,id*2+1);
    maxn[id]=min(maxn[id*2],maxn[id*2+1]);
}

void updatemin(int l,int r,int x,int v,int id){
    if(l==r){
        minn[id]=v;return ;
    }
    int mid=(l+r)/2;
    if(mid>=x)updatemin(l,mid,x,v,id*2);
    else updatemin(mid+1,r,x,v,id*2+1);
    minn[id]=max(minn[id*2],minn[id*2+1]);
}

int querymax(int l,int r,int v,int id){
    if(l==r){
        if(maxn[id]>v)return -1;
        return l;
    }
    int mid=(l+r)/2;
    if(maxn[id*2]<=v)return querymax(l,mid,v,id*2);
    else{
        if(maxn[id*2+1]>v)return -1;
        return querymax(mid+1,r,v,id*2+1);
    }
}

int querymin(int l,int r,int v,int id){
    if(l==r){
        if(minn[id]<v)return -1;
        return l;
    }
    int mid=(l+r)/2;
    if(minn[id*2]>=v)return querymin(l,mid,v,id*2);
    else {
        if(minn[id*2+1]<v)return -1;
        return querymin(mid+1,r,v,id*2+1);
    }
}

int querymax(int l,int r,int z,int y,int v,int id){
    if(l==z&&r==y){
        int an=querymax(l,r,v,id);
        return an;
    }
    int mid=(l+r)/2;
    if(mid>=y)return querymax(l,mid,z,y,v,id*2);
    else if(mid<z)return querymax(mid+1,r,z,y,v,id*2+1);
    else{
        int an=querymax(l,mid,z,mid,v,id*2);
        if(an!=-1)return an;
        return querymax(mid+1,r,mid+1,y,v,id*2+1);
    }
}
int querymin(int l,int r,int z,int y,int v,int id){
    if(l==z&&r==y){
        int an=querymin(l,r,v,id);
        return an;
    }
    int mid=(l+r)/2;
    if(mid>=y)return querymin(l,mid,z,y,v,id*2);
    else if(mid<z)return querymin(mid+1,r,z,y,v,id*2+1);
    else{
        int an=querymin(l,mid,z,mid,v,id*2);
        if(an!=-1)return an;
        return querymin(mid+1,r,mid+1,y,v,id*2+1);
    }
}

void up(int l,int r,int x){
    if(a[l]>a[r]){
        int v=(a[l]+a[r]+1)/2;
        updatemax(1,n,x,v,1);
        updatemin(1,n,x,-inf,1);
    }
    else{
        int v=(a[l]+a[r])/2;
        updatemin(1,n,x,v,1);
        updatemax(1,n,x,inf,1);
    }
}

int nxt[3*MAXN],last[3*MAXN];

long long ans;

int main(){

    read(n),read(s);
    for(int i=1;i<=n;i++)read(a[i]);
    if(n==1){
        printf("%d\n",abs(s-a[1]));
        return 0;
    }

    for(register int i=1;i<=n;i++){
        int ni=i+1;if(ni>n)ni=1;
        nxt[i]=ni;
        last[ni]=i;
        up(i,ni,i);
    }

    for(register int i=1;i<=n;i++){
        int mx,mi;
        mx=querymax(1,n,p,n,s,1);
        mi=querymin(1,n,p,n,s,1);
        if(mx==-1&&mi==-1){
            mx=querymax(1,n,1,p-1,s,1);
            mi=querymin(1,n,1,p-1,s,1);
        }
        int an=0;
        if(mx==-1&&mi>0)an=mi;
        else if(mi==-1&&mx>0)an=mx;
        else{an=min(mx,mi);}
        
        ans+=abs(a[an]-s);
        s=a[an],p=an;
        int nl=last[an],nr=nxt[an];

        if(nr==nl){
            ans+=abs(s-a[nl]);
            break;
        }

        updatemax(1,n,an,inf,1);
        updatemin(1,n,an,-inf,1);

        up(nl,nr,nl);
        nxt[nl]=nr;
        last[nr]=nl;
    }

    printf("%lld\n",ans);
    return 0;
}

```


---

