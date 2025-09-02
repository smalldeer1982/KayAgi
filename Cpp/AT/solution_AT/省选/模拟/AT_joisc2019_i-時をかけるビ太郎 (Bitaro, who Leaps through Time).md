# 時をかけるビ太郎 (Bitaro, who Leaps through Time)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/joisc2019/tasks/joisc2019_i



# 题解

## 作者：InoueTakina (赞：3)

先把 $[L_i,R_i]$ 转化为 $[L_i-i,R_i-i]$，这样就抵消了时间的自然流逝，更方便下文的讨论。

很厉害的是我们可以构造如下半群信息 $\varepsilon$：

- 二元信息 $(L,R)$，表示目前存在一个点，他的时间可以从 $[L,R]$ 之间任选。
- 三元信息 $(u,v,c)$，表示目前存在一条路径，从时间 $u$ 开始，到时间 $v$ 结束，贡献是 $c$。

考虑信息的合并：

- 二元 $(L_1,R_1)$ / 二元 $(L_2,R_2)$：
  - $[L_1,R_1]\cap [L_2,R_2]\neq \emptyset$：$(L_1,R_1)+(L_2,R_2)\to (\max\{L_1,L_2\},\min\{R_1,R_2\})$。
  - $L_1>R_2$：$\to (L_1,R_2,L_1-R_2)$。
  - $L_2>R_1$：$\to (R_1,L_2,0)$。
- 二元 $(L,R)$ / 三元 $(u,v,c)$：
  - $u\in [L,R]$：$(L,R)+(u,v,c)\to (u,v,c)$。
  - $u>R$：$\to (R,v,c)$。
  - $u<L$：$\to (L,v,c+L-u)$。
- 三元 $(u,v,c)$ / 二元 $(L,R)$：
  - $v\in [L,R]$：$(u,v,c)+(L,R)\to (u,v,c)$。
  - $v>R$：$\to (u,R,c+v-R)$。
  - $v<L$：$\to (u,L,c)$。
- 三元 $(u_1,v_1,c_1)$ / 三元 $(u_2,v_2,c_2)$：$(u_1,v_1,c_1)+(u_2,v_2,c_2)\to (u_1,v_2,c_1+c_2+\max\{v_1-u_2,0\})$。

由于是半群信息，因此可以线段树维护这些信息。查询相当于取 $[B,B]+\varepsilon (l,r)+[D,D]$。

比较麻烦的是由于询问有两个方向，所以需要正反各做一次。

综合时间复杂度 $\mathcal{O}(n\log n)$。


---

## 作者：lfxxx (赞：0)

首先你的策略肯定是一直往前走，走到不能走就等或者时光倒流知道能走，能走的时候没必要等或者时光倒流，因为这样的操作可能会被后面的操作对冲，所以只在必要的时候去等或者时光倒流，现在考虑怎么维护答案。

下文只讨论 $a_i < c_i$ 也就是往后走的情况，另一种情况倒过来跑一遍即可。

首先这个走过一条边花费 $1$ 单位时间比较烦人，考虑由于时间是随着下标改变均匀增加，所以令点 $i$ 上的时间减去 $i$ 后即可认为走过一条边不需要花费时间。

然后考虑下你是在干嘛，你发现你是在一个每一列都有一个区间是可以走的网格图上走，询问往下走的次数，观察你的行动轨迹，你发现一个很牛的事，从一个点出发点轨迹，假若其没有拐弯（之前是向下走现在向上走或者反过来），那么说明走过的列满足相邻两列可以走的区间交非空，反过来，当你从任意位置出发走过一些满足这个条件的列时，最后会走到区间 $[l,r]$ 中，这个区间代表所有列可以走的区间的交，对于 $x < l$ 的位置，其会走到 $l$，对于 $x > r$ 的位置，其会走到 $r$，其余位置不变，并且由于路径没有拐弯，所以一个位置 $x$ 走到终点时向下走的步数刚好是 $\max(0,x-r)$。

那如果出现了路径拐弯的情况呢？

观察第一次拐弯的位置 $i$，其一定满足第 $i$ 列可以走的区间与第 $i+1$ 列可以走的区间交为空，此时你发现任意位置出发最终都会走到第 $i+1$ 列可以走的区间的一个端点，因此我们不妨视作此时会先不拐弯的走到第 $i$ 列可以走的区间的一个端点，此后所有位置出发的点的运动路径全部相同。

至此可以非常好的刻画对于一个区间的列，假若从位置 $x$ 出发，抵达位置与向下走的步数，分为两种情况，一种情况可以记作 $l,r$，表示上面路径没有拐弯的情况，第二种情况可以记作 $c,cend,cst$，表示会先没有拐弯地走到 $cend$ 的位置，在拐弯后走的花费时 $cst$，走到的位置是 $c$，而一个位置 $x$ 的花费自然就是 $\max(0,x-cend)+cst$。

接下来考虑怎么快速的合并两个相邻区间的列的答案以快速回答区间询问与单点修改，大部分情况是简单的，这里挑我个人在此处思考了一会的情况展开讲讲。

对于前面的区间的路径没有拐弯，后面的区间出现拐弯的情况，可能出现下面的情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/8xb8z9c0.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

假若前面的区间的 $R$ 小于后面的区间的 $cend$，此时你不知道合并后第一次拐弯的位置了，怎么办？

其实你不需要知道第一次拐弯的位置，你只在乎第一次拐弯前的区间的左端点或者右端点，在这种情况中这个端点一定是 $R$，因为假若后面的区间存在更小的 $R'$，就不会到 $cend$ 处了，另一种对称的 $L > cend$ 的情况同理。

至此可以使用线段树在 $((n+q) \log n)$ 的时间复杂度内解决这个问题。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 2e18;
const int maxn = 3e5+114;
int l[maxn],r[maxn];
int a[maxn],b[maxn],c[maxn],d[maxn],opt[maxn],pos[maxn],x[maxn],y[maxn];
int ans[maxn];
int n,q;
struct node{
    int ty,l,r,c,cend,cst;
    node(int Ty=0,int L=0,int R=0,int C=0,int Cend=0,int Cst=0){
        ty=Ty,l=L,r=R,c=C,cend=Cend,cst=Cst;
    }
    node operator+(const node &x)const{
        node res=node();
        if(ty==0){
            if(x.ty==0){
                if(max(l,x.l)<=min(r,x.r)){
                    res.ty=0;
                    res.l=max(l,x.l);
                    res.r=min(r,x.r);
                }else{
                    if(x.l>r){
                        res.ty=1;
                        res.c=x.l;
                        res.cend=r;
                        res.cst=0;
                    }else{
                        res.ty=1;
                        res.c=x.r;
                        res.cend=l;
                        res.cst=l-x.r;
                    }
                }
            }else{
                res.ty=1;
                res.c=x.c;
                if(x.cend<l){
                    res.cend=l;
                    res.cst=x.cst+(l-x.cend);
                }else if(x.cend>r){
                    res.cend=r;
                    res.cst=x.cst;
                }else{
                    res.cend=x.cend;
                    res.cst=x.cst;
                }
            }
        }else{
            if(x.ty==0){
                res.ty=1;
                res.c=min(x.r,max(x.l,c));
                res.cend=cend;
                res.cst=cst+max(0*1ll,c-x.r);
            }else{
                res.ty=1;
                res.c=x.c;
                res.cend=cend;
                res.cst=cst+max(0*1ll,c-x.cend)+x.cst;
            }
        }
        return res;
    }   
}tr[maxn<<2];
void build(int cur,int lt,int rt){
    if(lt==rt){
        tr[cur].ty=0;
        tr[cur].l=l[lt],tr[cur].r=r[lt];
        return ;
    }
    int mid=(lt+rt)>>1;
    build(cur<<1,lt,mid);
    build(cur<<1|1,mid+1,rt);
    tr[cur]=tr[cur<<1]+tr[cur<<1|1];
}
void change(int cur,int lt,int rt,int pos,int L,int R){
    if(lt==rt){
        tr[cur].ty=0;
        tr[cur].l=L,tr[cur].r=R;
        return ;
    }
    int mid=(lt+rt)>>1;
    if(pos<=mid) change(cur<<1,lt,mid,pos,L,R);
    else change(cur<<1|1,mid+1,rt,pos,L,R);
    tr[cur]=tr[cur<<1]+tr[cur<<1|1];
}
node ask(int cur,int lt,int rt,int l,int r){
    if(rt<l||r<lt) return node(0,-inf,inf,0,0,0);
    if(l<=lt&&rt<=r) return tr[cur];
    int mid=(lt+rt)>>1;
    return ask(cur<<1,lt,mid,l,r)+ask(cur<<1|1,mid+1,rt,l,r);
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n>>q;
    for(int i=1;i<n;i++){
        cin>>l[i]>>r[i];
        r[i]--;
    }
    if(n==1){
        while(q--){
            int opt;
            cin>>opt;
            if(opt==2){
                int A,B,C,D;
                cin>>A>>B>>C>>D;
                cout<<max(0*1ll,B-D)<<'\n';
            }            
        }
        return 0;
    }
    for(int i=1;i<=q;i++){
        cin>>opt[i];
        if(opt[i]==1) cin>>pos[i]>>x[i]>>y[i],y[i]--;
        else cin>>a[i]>>b[i]>>c[i]>>d[i];
    }
    //solve 1
    for(int i=1;i<n;i++) l[i]-=i,r[i]-=i;
    for(int i=1;i<=q;i++){
        if(opt[i]==1) x[i]-=pos[i],y[i]-=pos[i];
        else b[i]-=a[i],d[i]-=c[i];
    }
    build(1,1,n-1);
    for(int i=1;i<=q;i++){
        if(opt[i]==1){
            change(1,1,n-1,pos[i],x[i],y[i]);
        }else{
            if(a[i]<c[i]){
                node f=ask(1,1,n-1,a[i],c[i]-1)+node(0,d[i],d[i],0,0,0);
                if(f.ty==0) ans[i]=max(0*1ll,b[i]-f.r);
                else ans[i]=f.cst+max(0*1ll,b[i]-f.cend);
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(opt[i]==1) x[i]+=pos[i],y[i]+=pos[i];
        else b[i]+=a[i],d[i]+=c[i];
    }
    for(int i=1;i<n;i++) l[i]+=i,r[i]+=i;
    //wait
    reverse(l+1,l+n);
    reverse(r+1,r+n);
    for(int i=1;i<=q;i++){
        if(opt[i]==1) pos[i]=n-pos[i];
        else a[i]=n-a[i]+1,c[i]=n-c[i]+1;
    }
    //solve 2
    for(int i=1;i<n;i++) l[i]-=i,r[i]-=i;
    for(int i=1;i<=q;i++){
        if(opt[i]==1) x[i]-=pos[i],y[i]-=pos[i];
        else b[i]-=a[i],d[i]-=c[i];
    }
    build(1,1,n-1);
    for(int i=1;i<=q;i++){
        if(opt[i]==1){
            change(1,1,n-1,pos[i],x[i],y[i]);
        }else{
            if(a[i]<c[i]){
                node f=ask(1,1,n-1,a[i],c[i]-1)+node(0,d[i],d[i],0,0,0);
                if(f.ty==0) ans[i]=max(0*1ll,b[i]-f.r);
                else ans[i]=f.cst+max(0*1ll,b[i]-f.cend);
            }
        }
    }
    for(int i=1;i<=q;i++){
        if(opt[i]==1) x[i]+=pos[i],y[i]+=pos[i];
        else b[i]+=a[i],d[i]+=c[i];
    }
    for(int i=1;i<n;i++) l[i]+=i,r[i]+=i;
    for(int i=1;i<=q;i++){
        if(a[i]==c[i]){
            ans[i]=max(0*1ll,b[i]-d[i]);
        }
    }
    for(int i=1;i<=q;i++){
        if(opt[i]==2) cout<<ans[i]<<'\n';
    }
    return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2019I 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2019_i)

**题目大意**

> 数轴上有 $n$ 个城市，其中 $i,i+1$ 之间有双向路径，想要通过必须在 $x\in[l_i,r_i-1]$ 时刻出发，在 $x+1$ 到达另一侧，你可以在原地让时刻 $+1$ 或发动时光倒流使时刻 $-1$。
>
> $q$ 次操作，修改 $l_i,r_i$ 或询问 $b$ 时刻在 $a$ 至少要几次时光倒流才是在时刻 $d$ 到 $c$。
>
> 数据范围：$n,q\le 3\times 10^5$。

**思路分析**

可以看成在网格图中向右下、下或上移动，考虑把右下操作变成右，即令 $[l_i,r_i-1]\gets [l_i-i,r_i-i-1]$。

然后这个问题就可以直接贪心，每次移动尽可能少，那么一个区间的限制有两种：

- $[l,r]$ 表示在 $[l,r]$ 之内可以向另一侧移动。
- $x\to y$ 表示从 $x$ 时刻进入 $y$ 时刻输出，花费的代价为 $w$。

分类讨论合并信息即可，线段树维护。

时间复杂度 $\mathcal O((n+q)\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=3e5+5;
struct Info {
	int x,y; ll p; //p=-1: interval[x,y], p>=0: path x->y, cost = p
	inline friend Info operator +(const Info &u,const Info &v) {
		if(~u.p&&~v.p) return {u.x,v.y,u.p+max(0,u.y-v.x)+v.p};
		if(~u.p) return {u.x,max(min(u.y,v.y),v.x),u.p+max(0,u.y-v.y)};
		if(~v.p) return {min(max(u.x,v.x),u.y),v.y,v.p+max(0,u.x-v.x)};
		if(u.y<v.x) return {u.y,v.x,0};
		if(u.x>v.y) return {u.x,v.y,u.x-v.y};
		return {max(u.x,v.x),min(u.y,v.y),-1};
	}
};
int n,q;
struct SegmentTree {
	Info tr[MAXN<<2];
	inline void psu(int p) { tr[p]=tr[p<<1]+tr[p<<1|1]; }
	inline void upd(int u,Info I,int l=1,int r=n,int p=1) {
		if(l==r) return tr[p]=I,void();
		int mid=(l+r)>>1;
		if(u<=mid) upd(u,I,l,mid,p<<1);
		else upd(u,I,mid+1,r,p<<1|1);
		psu(p);
	}
	inline Info qry(int ul,int ur,int l=1,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return tr[p];
		int mid=(l+r)>>1;
		if(ur<=mid) return qry(ul,ur,l,mid,p<<1);
		if(mid<ul) return qry(ul,ur,mid+1,r,p<<1|1);
		return qry(ul,ur,l,mid,p<<1)+qry(ul,ur,mid+1,r,p<<1|1);
	}
};
struct sol {
	SegmentTree T;
	inline void set(int i,int x,int y) { T.upd(i,{x-i,y-i-1,-1}); }
	inline ll qry(int u,int s,int v,int t) {
		return max(((Info){s-u,s-u,-1}+T.qry(u,v-1)+(Info){t-v,t-v,-1}).p,0ll);
	}
}	T1,T2;
int l[MAXN],r[MAXN];
signed main() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<n;++i) {
		scanf("%d%d",&l[i],&r[i]);
		T1.set(i,l[i],r[i]),T2.set(n-i,l[i],r[i]);
	}
	for(int op,u,v,s,t;q--;) {
		scanf("%d",&op);
		if(op==1) {
			scanf("%d%d%d",&u,&s,&t);
			T1.set(u,s,t),T2.set(n-u,s,t);
		} else {
			scanf("%d%d%d%d",&u,&s,&v,&t);
			if(u==v) printf("%d\n",max(0,s-t));
			if(u<v) printf("%lld\n",T1.qry(u,s,v,t));
			if(u>v) printf("%lld\n",T2.qry(n-u+1,s,n-v+1,t));
		}
	}
	return 0;
}
```



---

## 作者：james1BadCreeper (赞：0)

显然走的方式很呆板：能走就走，不能走就等或时间旅行。现在假设 $A<C$。

设 $y$ 时刻的 $x$ 城市代表 $(x,y)$，套路地，为了避免行走时时间流逝的自然影响，将其改成 $(x,y-x)$。

用 $(a,b,c)$ 表示行动，$a$ 为开始时刻，$b$ 为结束时刻，$c$ 为时间倒流次数。$(L,R)$ 代表这条道路只能在 $[L,R]$ 时通过。现在考虑如何合并：

- 两个二元：如果有交集则取交集，否则可以转化为三元组。
- 一二一三：观察二元组和 $a$ 的关系即可算出。
- 两个三元：计算中间时间穿越的次数即可。

最终答案用起终点的两个三元组加上中间路径的三元组即可得到。具有结合律，可以使用线段树维护。$A>C$ 的情况是对称的。时间复杂度 $O((n+q)\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
typedef long long i64; 
const int INF = 1e9; 

int n, q; 
int l[300005], r[300005]; 

struct Node {
    int l, r; i64 val; 
    Node(int l = -INF, int r = INF, i64 val = -1) : l(l), r(r), val(val) {}
    friend Node operator+ (const Node &a, const Node &b) {
        if (a.val == -1 && b.val == -1) {
            if (a.l > b.r) return Node(a.l, b.r, a.l - b.r); 
            if (a.r < b.l) return Node(a.r, b.l, 0); 
            return Node(max(a.l, b.l), min(a.r, b.r)); 
        }
        if (a.val == -1) {
            if (b.l < a.l) return Node(a.l, b.r, b.val + a.l - b.l); 
            if (b.l > a.r) return Node(a.r, b.r, b.val); 
            return b; 
        }
        if (b.val == -1) {
            if (a.r < b.l) return Node(a.l, b.l, a.val); 
            if (a.r > b.r) return Node(a.l, b.r, a.val + a.r - b.r); 
            return a; 
        }
        return Node(a.l, b.r, a.val + b.val + max(0, a.r - b.l)); 
    }
}; 
struct Segment_Tree {
    Node T[1200005]; 
    void update(int o, int l, int r, int p, int x, int y) {
        if (l == r) return T[o] = Node(x, y, -1), void(); 
        int mid = l + r >> 1; 
        if (p <= mid) update(o << 1, l, mid, p, x, y); 
        else update(o << 1 | 1, mid + 1, r, p, x, y); 
        T[o] = T[o << 1] + T[o << 1 | 1]; 
    }
    void update(int p, int x, int y) { update(1, 1, n - 1, p, x, y); }
    Node query(int o, int l, int r, int x, int y) {
        if (x <= l && r <= y) return T[o]; 
        int mid = l + r >> 1; 
        if (y <= mid) return query(o << 1, l, mid, x, y); 
        if (mid < x) return query(o << 1 | 1, mid + 1, r, x, y); 
        return query(o << 1, l, mid, x, y) + query(o << 1 | 1, mid + 1, r, x, y); 
    }
    Node query(int x, int y) { return query(1, 1, n - 1, x, y); }
} tL, tR; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> q; 
    for (int i = 1; i < n; ++i) {
        cin >> l[i] >> r[i]; 
        tL.update(i, l[i] - i, r[i] - 1 - i); 
    }
    reverse(l + 1, l + n); reverse(r + 1, r + n); 
    for (int i = 1; i < n; ++i) tR.update(i, l[i] - i, r[i] - 1 - i); 
    while (q--) {
        int op; cin >> op; 
        if (op == 1) {
            int p, l, r; cin >> p >> l >> r; 
            tL.update(p, l - p, r - 1 - p); 
            p = n - p; tR.update(p, l - p, r - 1 - p); 
        } else {
            int a, b, c, d; cin >> a >> b >> c >> d; 
            if (a < c) cout << max(0ll, (Node(b - a, b - a) + tL.query(a, c - 1) + Node(d - c, d - c)).val) << "\n"; 
            else if (a == c) cout << max(0, b - d) << "\n";  
            else {
                a = n - a + 1; c = n - c + 1; 
                cout << max(0ll, (Node(b - a, b - a) + tR.query(a, c - 1) + Node(d - c, d - c)).val) << "\n"; 
            }
        }
    }
    return 0; 
}
```

---

