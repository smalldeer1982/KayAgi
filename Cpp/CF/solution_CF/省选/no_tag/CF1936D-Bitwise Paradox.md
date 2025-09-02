# Bitwise Paradox

## 题目描述

You are given two arrays $ a $ and $ b $ of size $ n $ along with a fixed integer $ v $ .

An interval $ [l, r] $ is called a good interval if $ (b_l \mid b_{l+1} \mid \ldots \mid b_r) \ge v $ , where $ | $ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). The beauty of a good interval is defined as $ \max(a_l, a_{l+1}, \ldots, a_r) $ .

You are given $ q $ queries of two types:

- "1 i x": assign $ b_i := x $ ;
- "2 l r": find the minimum beauty among all good intervals $ [l_0,r_0] $ satisfying $ l \le l_0 \le r_0 \le r $ . If there is no suitable good interval, output $ -1 $ instead.

Please process all queries.

## 说明/提示

In the first test case, $ a = [2, 1, 3] $ , $ b = [2, 2, 3] $ , and $ v = 7 $ .

The first query is of the second type and has $ l = 1 $ and $ r = 3 $ . The largest interval available is $ [1, 3] $ , and its bitwise OR is $ b_1 \mid b_2 \mid b_3 = 3 $ which is less than $ v $ . Thus, no good interval exists.

The second query asks to change $ b_2 $ to $ 5 $ , so $ b $ becomes $ [2, 5, 3] $ .

The third query is of the second type and has $ l = 2 $ and $ r = 3 $ . There are three possible intervals: $ [2, 2] $ , $ [3, 3] $ , and $ [2, 3] $ . However, $ b_2 = 5 < v $ , $ b_3 = 3 < v $ . So only the last interval is good: it has $ b_2 \mid b_3 = 7 $ . The answer is thus $ \max(a_2, a_3) = 3 $ .

The fourth query is of the second type and has $ l = 1 $ and $ r = 3 $ . There are three good intervals: $ [1, 2] $ , $ [2, 3] $ , and $ [1, 3] $ . Their beauty is $ 2 $ , $ 3 $ , $ 3 $ correspondingly. The answer is thus $ 2 $ .

In the second test case, $ a = [5, 1, 2, 4] $ , $ b = [4, 2, 3, 3] $ , and $ v = 5 $ .

The first query has $ l = 1 $ and $ r = 4 $ . The only good intervals are: $ [1, 2] $ , $ [1, 3] $ , $ [1, 4] $ . Their beauty is $ 5 $ , $ 5 $ , $ 5 $ correspondingly. The answer is thus $ 5 $ .

## 样例 #1

### 输入

```
3
3 7
2 1 3
2 2 3
4
2 1 3
1 2 5
2 2 3
2 1 3
4 5
5 1 2 4
4 2 3 3
6
2 1 4
1 3 15
2 3 4
2 2 4
1 2 13
2 1 4
1 5
6
4
1
2 1 1```

### 输出

```
-1 3 2 
5 2 2 1 
-1```

# 题解

## 作者：EnofTaiPeople (赞：9)

省选前写题解 rp++！

首先发现 $v$ 是全局给定的，不然会很复杂，这里 $v$ 全局给定相当于将本题变成了一种类最大子段和问题。

最大子段和问题的常用解决方案就是在线段树上维护前缀最大值，后缀最大值，在上传时合并左边的后缀和右边的前缀。

这里相当于将前后缀形如一个二元组 $(a,b)$ 表示 $a_i$ 的最大值和 $b_i$ 的或和。

所谓或运算单调性有两个方面：

1. 或的越多，数字越大，所以前后缀的或和单调。

2. 每次增大或和时二进制下为 $1$ 的位数一定会**增大**，所以前后缀或和只有本质不同 $O(\log V)$ 种。

用处就是暴力存下所有本质不同 $b$ 所对应最小（最靠前）的 $a$ 是可以接受的。

上传是先将自己的前缀数据记为左儿子的，然后枚举右儿子的前缀和左儿子的 $(a,b)$ 的和合并之后插入，当然如果这里的 $b$ 没有增大就不插入，后缀数据同理。

这里需要枚举左儿子后缀和右儿子前缀来统计答案，如果这里直接枚举是 $O((n+q)\log n\log^2V)$ 可能过不了，但因为这里的单调性太强了，所以可以双指针。

查询时直接将线段树对应节点的 $O(\log n)$ 个数据合并起来，总时间复杂度 $O((n+q)\log n\log V)$，空间 $O(n\log V)$：

```cpp
int T,n,m,a[N],t1,b[N];
pair<int,int>b1[N];
struct dat{
    vector<pair<int,int> >d;
    int operator*(const dat &z)const{
        int z1=d.size(),z2=z.d.size(),res=M,l,r;
        for(l=0,r=z2;l<z1;++l){
            while(r&&(z.d[r-1].second|d[l].second)>=m)--r;
            if(r<z2)res=min(res,max(d[l].first,z.d[r].first));
        }return res;
    }
    void upc(pair<int,int> &p){
        if(d.empty()||d.back().second<p.second)d.push_back(p);
    }
    void upd(int A,int B,dat &z){
        for(auto &p:z.d){
            A=max(A,p.first),B|=p.second;
            if(d.empty()||d.back().second<B)d.emplace_back(A,B);
        }
    }
};
struct dc{
    dat pr,to;int v,s,x;
    void mg(dc &p,dc &q){
        v=min({p.v,q.v,p.to*q.pr});
        s=p.s|q.s,x=max(p.x,q.x);
        pr=p.pr,pr.upd(p.x,p.s,q.pr);
        to=q.to,to.upd(q.x,q.s,p.to);
    }
    void mgg(dc p,dc &q){
        v=min({p.v,q.v,p.to*q.pr});
        s=p.s|q.s,x=max(p.x,q.x);
        pr=p.pr,pr.upd(p.x,p.s,q.pr);
        to=q.to,to.upd(q.x,q.s,p.to);
    }
    void init(int l){
        v=b[l]>=m?a[l]:M;
        s=b[l],x=a[l];
        pr.d=to.d={{0,0},{a[l],b[l]}};
    }
    void init(){pr=to={},v=M,s=x=0;}
}ac[N],sum;
int T1;
#define ls x<<1
#define rs x<<1|1
void pp(int x){ac[x].mg(ac[ls],ac[rs]);}
void build(int x,int l,int r){
    if(l==r)ac[x].init(l);
    else{
        int md=l+r>>1;
        build(ls,l,md);
        build(rs,md+1,r),pp(x);
    }
}
void cg(int x,int l,int r,int p){
    if(l==r)ac[x].init(l);
    else{
        int md=l+r>>1;
        if(p>md)cg(rs,md+1,r,p);
        else cg(ls,l,md,p);pp(x);
    }
}
void ask(int x,int l,int r,int L,int R){
    if(l>=L&&r<=R)sum.mgg(sum,ac[x]);
    else{
        int md=l+r>>1;
        if(L<=md)ask(ls,l,md,L,R);
        if(md<R)ask(rs,md+1,r,L,R);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int i,j,k,l,r,x,y,z,_l,_r;
    for(cin>>T;T--;){
        cin>>n>>m;
        for(i=1;i<=n;++i)cin>>a[i];
        for(i=1;i<=n;++i)cin>>b[i];
        build(1,1,n);
        for(cin>>T1;T1--;){
            cin>>k;
            if(k==1){
                cin>>x,cin>>b[x];
                cg(1,1,n,x);
            }else{
                sum.init(),cin>>l>>r;
                ask(1,1,n,l,r);
                printf("%d ",sum.v==M?-1:sum.v);
            }
        }puts("");
    }
    return 0;
}
```

---

## 作者：EuphoricStar (赞：4)

和 [CF1004F Sonya and Bitwise OR](https://www.luogu.com.cn/problem/CF1004F) 很像。

考虑一次询问怎么做。考虑分治，每次只计算左端点在 $[l, mid]$，右端点在 $[mid + 1, r]$ 的区间的贡献。对于每个 $i \in [l, mid]$，维护最小的 $j \in [mid + 1, r]$ 使得 $[i, j]$ 的或 $\ge v$，那么 $\max\limits_{k = i}^j a_k$ 对答案有贡献。

考虑带修怎么做。考虑套上线段树，利用线段树的分治结构，问题变成了如何合并两个区间的答案。

按位或有个很好的性质，就是前（或后）缀的或只会变化 $O(\log V)$ 次。所以我们对于线段树上每个结点，维护前缀和后缀的或第一次变化的位置。

计算左端点在左结点，右端点在右结点的区间贡献，就枚举左结点所有后缀或第一次变化的位置作为左端点，双指针维护使得区间或 $\ge v$ 的最靠左的右端点即可。

注意到 $a$ 不变，可以使用 ST 表单次 $O(1)$ 计算 $a$ 的区间最大值。合并两个区间的复杂度为 $O(\log V)$。所以总时间复杂度为 $O((n + q) \log n \log V)$。

[code](https://codeforces.com/problemset/submission/1936/249076401)

---

## 作者：Alex_Wei (赞：4)

### [CF1936D Bitwise Paradox](https://www.luogu.com.cn/problem/CF1936D)

设 $f(l, r)$ 表示 $b_{l\sim r}$ 的按位或。

因为 $f$ 具有包含单调性，即 $f(l, r)\geq f(l + 1, r)$ 且 $f(l, r)\geq f(l, r - 1)$，所以称一个好区间 $[l, r]$ 是极小的，若 $[l + 1, r]$ 和 $[l, r - 1]$ 都不是好区间，则以 $i$ 为左端点的好区间唯一，以 $i$ 为右端点的好区间唯一，且将所有极小好区间按左端点递增排序后右端点也递增。

设一个好区间的权值为 $a_{l\sim r}$ 的最大值。考虑直接维护所有极小好区间，则 $2$ 操作相当于查询极小好区间的一段区间的最小权值。用线段树维护左端点落在当前区间的极小好区间的右端点最大值，查询时线段树二分即可。

对于修改，注意到固定 $l$，随着 $r$ 增大，$f(l, r)$ 只会改变 $\mathcal{O}(\log V)$ 次。很明显的一点是如果 $l_1 < l_2$ 都是覆盖 $i$ 的极小好区间的左端点，则 $f(l_1, i)\neq f(l_2, i)$，否则 $[l_2, r_1]$ 是一个更小的好区间。于是覆盖每个点的极小好区间数量为 $\mathcal{O}(\log V)$。可以用 set 显式维护所有极小好区间，以支持删除覆盖 $i$ 的所有极小好区间。

对于修改时可能产生的新的极小好区间，显然会覆盖 $i$。因为 $l$ 可能作为这样的区间的左端点的必要条件是 $f(l, i) > f(l + 1, i)$（否则 $v\leq f(l, r) = f(l + 1, r)$，不满足极小的限制），于是可以用另一颗线段树维护 $b$ 的区间按位或，并使用向左的线段树二分求出总共 $\mathcal{O}(\log V)$ 个可能的左端点。对 $l$ 求最小的 $r$ 则是在该线段树上向右二分。

时间复杂度 $\mathcal{O}(n\log n\log V)$，其中查询操作为 $\mathcal{O}(\log n)$。空间复杂度 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1936/submission/248955075)。

---

## 作者：H_W_Y (赞：2)

读完题目，发现这是一个与二进制相关的问题，
而容易发现，每组数据中 $v,a_i$ 都是不变的，且涉及到 $b_l|b_{l+1}|\dots |b_r \ge v$ 的计算，
我们不难想到拆位，也就是对每一个二进制位分开来讨论。



现在再来看数据范围，直觉是可以去尝试 Poly log 的做法，
而用最普通的线段树来维护，问题就在于我们如何去 **合并两个区间**。


发现这是好做的，我们同样按照二进制位从高到低考虑，合并区间 $[l,mid]$ 和 $[mid+1,r]$，得到最优的满足条件区间 $[L,R]$。

设当前枚举到第 $i$ 位，假设 $v$ 的这一位要求是 $1$，那么这个 $1$ 一定来源于左区间或者右区间（根据或运算）。

假设左区间从右往左第一个 $i$ 位为 $1$ 的位置是 $P$，右区间从左往右第一个 $i$ 位为 $1$ 的位置是 $Q$，则：

- 如果 $\max_{i=P}^{mid} a_i \le \max_{i=mid+1}^{Q} a_i$，那么我们选择把 $L$ 扩展到 $P$。

- 反之我们选择把 $R$ 拓展到 $Q$。

这样贪心地选择一定是不劣的，因为你总需要拓展一个，我们希望答案尽可能优。


而 $v$ 的这一位不要求为 $1$ 的情况也是简单的，我们枚举选还是不选：

- 如果把这一位选成 $1$，操作与上面相同，而后面的位我们都不用选了，这样直接算上此时区间最大值与答案取 $\min$。

- 不选则继续往下枚举。

这样我们就可以做到两个区间的合并了，实现中只需要维护一个区间每一位的 $P,Q$，容易发现这也是好维护的，下面是区间合并的代码：

```cpp
  //S(l,r) 算区间 [l,r] 中 a_i 的最大值
  sgt operator +(sgt Lp,sgt Rp){//合并区间 Lp 和 Rp
  	sgt res;
  	res.v=min(Lp.v,Rp.v),res.l=Lp.l,res.r=Rp.r;
    //v 是当前区间的答案，l,r 是当前区间的左右界
  	int L=Lp.r,R=Rp.l,tmp=inf,_L,_R;bool fl=1;
  	for(int i=30;i>=0;i--){
  	  res.pre[i]=Lp.pre[i]?Lp.pre[i]:Rp.pre[i];//更新当前区间第 i 位的 P，不存在为 0
  	  res.suf[i]=Rp.suf[i]?Rp.suf[i]:Lp.suf[i];//更新当前区间第 i 位的 Q，不存在为 0
  	  if(!fl) continue;//高位无法满足条件直接跳过
  	  if(!Lp.suf[i]&&!Rp.pre[i]){fl=!lim[i];continue;}//这一位无法为 1 满足条件
  	  if(!lim[i]) _L=L,_R=R;
  	  if(!Lp.suf[i]) R=max(R,Rp.pre[i]);
  	  else if(!Rp.pre[i]) L=min(L,Lp.suf[i]);
  	  else{
  	  	if(S(Lp.suf[i],Lp.r)<=S(Rp.l,Rp.pre[i])) L=min(L,Lp.suf[i]);
  	  	else R=max(R,Rp.pre[i]);
  	  }
  	  if(!lim[i]) tmp=min(tmp,S(L,R)),L=_L,R=_R;//在不要求选 1 时选了 1，可以直接更新答案
  	}
  	if(fl) res.v=min(res.v,S(L,R));
  	res.v=min(res.v,tmp);
  	return res;
  }
```


完成了区间合并，那么这道题就做完了。其实只要想到拆位，也就不难了。

实现中 $a$ 的区间最大值可以用 ST 表维护做到 $\mathcal O(1)$，那么总时间复杂度是 $\mathcal O(q \log n \log V + n \log V)$，后者是预处理的复杂度。

```cpp
const int N=2e5+5,inf=2e9;
int n,T,m,V,a[N],st[30][N],b[N],lg[N],lim[31];

void init(){
  lg[1]=0;
  for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
  for(int i=1;i<=lg[n]+1;i++)
    for(int j=1;j+(1<<i)-1<=n;j++)
      st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}

int S(int l,int r){
  int tmp=lg[r-l+1];
  return max(st[tmp][l],st[tmp][r-(1<<tmp)+1]);
}

namespace SGT{
  struct sgt{
    int v,pre[31],suf[31],l,r;
  }tr[N<<2];
  #define mid ((l+r)>>1)
  #define lc p<<1
  #define rc p<<1|1
  #define lson l,mid,lc
  #define rson mid+1,r,rc
  sgt operator +(sgt Lp,sgt Rp){
  	sgt res;
  	res.v=min(Lp.v,Rp.v),res.l=Lp.l,res.r=Rp.r;
  	int L=Lp.r,R=Rp.l,tmp=inf,_L,_R;bool fl=1;
  	for(int i=30;i>=0;i--){
  	  res.pre[i]=Lp.pre[i]?Lp.pre[i]:Rp.pre[i];
  	  res.suf[i]=Rp.suf[i]?Rp.suf[i]:Lp.suf[i];
  	  if(!fl) continue;
  	  if(!Lp.suf[i]&&!Rp.pre[i]){fl=!lim[i];continue;}
  	  if(!lim[i]) _L=L,_R=R;
  	  if(!Lp.suf[i]) R=max(R,Rp.pre[i]);
  	  else if(!Rp.pre[i]) L=min(L,Lp.suf[i]);
  	  else{
  	  	if(S(Lp.suf[i],Lp.r)<=S(Rp.l,Rp.pre[i])) L=min(L,Lp.suf[i]);
  	  	else R=max(R,Rp.pre[i]);
  	  }
  	  if(!lim[i]) tmp=min(tmp,S(L,R)),L=_L,R=_R;
  	}
  	if(fl) res.v=min(res.v,S(L,R));
  	res.v=min(res.v,tmp);
  	return res;
  }
  void pu(int p){tr[p]=tr[lc]+tr[rc];}
  void Up(int p,int l){
    tr[p].l=tr[p].r=l,tr[p].v=(b[l]>=V)?a[l]:inf;
    for(int i=0;i<31;i++) tr[p].pre[i]=tr[p].suf[i]=((b[l]>>i)&1)?l:0;
  }
  void build(int l,int r,int p){
    if(l==r) return Up(p,l);
    build(lson),build(rson),pu(p);
  }
  void upd(int l,int r,int p,int x){
  	if(l==r) return Up(p,l);
  	x<=mid?upd(lson,x):upd(rson,x);pu(p);
  }
  sgt qry(int l,int r,int p,int x,int y){
  	if(x<=l&&y>=r) return tr[p];
  	if(y<=mid) return qry(lson,x,y);
  	if(x>mid) return qry(rson,x,y);
  	return qry(lson,x,y)+qry(rson,x,y);
  }
}
using namespace SGT;

void sol(){
  cin>>n>>V;
  for(int i=0;i<31;i++) lim[i]=((V>>i)&1);
  for(int i=1;i<=n;i++) cin>>a[i],st[0][i]=a[i];
  for(int i=1;i<=n;i++) cin>>b[i];
  init();build(1,n,1);
  cin>>m;
  while(m--){
  	int op,l,r;cin>>op>>l>>r;
  	if(op==1) b[l]=r,upd(1,n,1,l);
  	else{
  	  sgt res=qry(1,n,1,l,r);
  	  if(res.v==inf) cout<<"-1 ";
  	  else cout<<res.v<<' ';
  	}
  }
  cout<<'\n';
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>T;
  while(T--) sol();
  return 0;
}
```

---

## 作者：forest114514 (赞：2)

鉴定为有一点套路的DS题。

首先不带修改容易想到分治：

首先计算 $[l,mid]$ 和 $[mid+1,r]$ 的答案，然后考虑如何合并两个区间计算跨越 $mid$ 的区间的答案。

位运算考虑拆位，因为区间前后缀 $max$ 具有单调性，我们考虑让满足条件的区间尽量小一点。

我们对每一个位数分别记录区间两端第一个出现的位置，倒着考虑每一位的取值，类似数位 DP，然后分类讨论：

1. $v$ 的第 $i$ 位为 1：

   首先我们前面所有 $>i$ 的位我们都钦定现在都与 $v$ 那位相等，我们考虑此时选择左区间最右边的点/右区间最左边的点，记两个值为 $cl/cr$，讨论大小即可，注意两个值相等的时候两个点都要选，因为这样对于小于 $i$ 的位，这样可以包括更多的位。

2. $v$ 的第 $i$ 位为 $0$：

   首先贪心地想，我们不取这一位；如果我们取这一位，此时不用管后面的位，此时或的值已经 $>v$ 了，我们可以直接把此时得到的区间和区间的答案取 $\min$ 即可。

至于查询 $a$ 的区间最大值，因为 $a$ 是静态的，可以考虑 ST 表做到 $O(n\log n)-O(1)$。

然后考虑单点修改，我们类比最大子段和，直接线段树维护即可。

时间复杂度为 $O((n+q)\log n\log V)$，空间复杂度为 $O(n(\log n+\log V))$。

代码：

```cpp
const int N=2e5+100;
int n,q,v,a[N],b[N];
struct RMQ{
	int mx[20][N],lg[N];
	void init(){
		rep(i,2,2e5)lg[i]=lg[i>>1]+1;
	}
	void resize(){
		rep(i,1,n) mx[0][i]=a[i];
		rep(t,1,lg[n]) rep(i,1,n-(1<<t)+1) mx[t][i]=max(mx[t-1][i],mx[t-1][i+(1<<t-1)]);
	}
	int query(int l,int r){
		if(l>r) return inf;
		int k=lg[r-l+1];
		return max(mx[k][l],mx[k][r-(1<<k)+1]);
	}
}ST;
struct SGT{
	int mn,l,r;
	int ml[30],mr[30];
}tr[N<<2];
SGT operator +(SGT LS,SGT RS){
	SGT RES;
	RES.mn=min(LS.mn,RS.mn);
	rep(i,0,29) RES.ml[i]=(LS.ml[i])?LS.ml[i]:RS.ml[i],RES.mr[i]=(RS.mr[i])?RS.mr[i]:LS.mr[i];
	//注意特判左/右区间没有该位的数的情况 
	RES.l=LS.l,RES.r=RS.r;	
	int mid=LS.r;
	auto qry=[&](int l,int r){
		return ST.query(l,r);
	};
	int nl=mid+1,nr=mid;
	bool fl=1;
	per(i,29,0){
		int op=(v&(1<<i));
		if(op){//必须选第i位，且没有额外的答案 
			int cl=(LS.mr[i])?qry(min(nl,LS.mr[i]),nr):inf,cr=(RS.ml[i])?qry(nl,max(nr,RS.ml[i])):inf;
			if((!LS.mr[i])&&(!RS.ml[i])){fl=0; break;}//不合法 
			if(cl==cr){//相等就尽量扩大区间 
				nl=min(nl,LS.mr[i]),nr=max(nr,RS.ml[i]);
			}
			else{
				(cl<cr)?(nl=min(nl,LS.mr[i])):(nr=max(nr,RS.ml[i]));
			}
		}
		else{//不必须选第i位，可以有额外的答案 
			if(LS.mr[i]) RES.mn=min(RES.mn,qry(min(nl,LS.mr[i]),nr));
			if(RS.ml[i]) RES.mn=min(RES.mn,qry(nl,max(nr,RS.ml[i])));
		}
	}
	if(fl) RES.mn=min(RES.mn,qry(nl,nr)); //刚好是v 
	return RES;
}
void build(int x,int l,int r){
	if(l==r){
		tr[x].l=tr[x].r=l;
		tr[x].mn=(b[l]>=v)?a[l]:inf;
		rep(i,0,29) tr[x].ml[i]=(b[l]&(1<<i))?l:0,tr[x].mr[i]=(b[l]&(1<<i))?l:0;
		return;
	}
	int mid=l+r>>1;
	build(ls(x),l,mid);
	build(rs(x),mid+1,r);
	tr[x]=tr[ls(x)]+tr[rs(x)];
}
void update(int x,int l,int r,int u){
	if(l==r){
		tr[x].mn=(b[l]>=v)?a[l]:inf;
		rep(i,0,29) tr[x].ml[i]=(b[l]&(1<<i))?l:0,tr[x].mr[i]=(b[l]&(1<<i))?l:0;
		return;
	}
	int mid=l+r>>1;
	(mid>=u)?update(ls(x),l,mid,u):update(rs(x),mid+1,r,u);
	tr[x]=tr[ls(x)]+tr[rs(x)];
}
SGT query(int x,int l,int r,int L,int R){
	if(L<=l&&r<=R) return tr[x];
	int mid=l+r>>1;
	if(L<=mid&&mid<R) return query(ls(x),l,mid,L,R)+query(rs(x),mid+1,r,L,R);
	return (mid>=L)?query(ls(x),l,mid,L,R):query(rs(x),mid+1,r,L,R);
}
void solve(){
	read(n,v);
	rep(i,1,n) read(a[i]);
	ST.resize();
	rep(i,1,n) read(b[i]);
	build(1,1,n);
	read(q);
	while(q--){
		int op,l,r;
		read(op,l,r);
		if(op==1){
			b[l]=r;
			update(1,1,n,l);
		}
		else{
			SGT res=query(1,1,n,l,r);
			write((res.mn==inf)?-1:res.mn,' ');
		}
	}
	putchar('\n');
}
```

---

## 作者：__ycx2010__ (赞：1)

### 思路

直接维护不好做，考虑先套上一层分治，$f(l,r)=\min\{f(l,mid),f(mid+1,r),\operatorname{merge}(left,right)\}$。

这个分治需要线段树来维护，若要询问 $f(l,r)$，则先拆成 $O(\log n)$ 个线段，再两两合并。

分别对线段树上的每一段维护 $pre$，和 $suf$，表示不同的 $b$ 的前缀或，由于每次二进制位至少增加 $1$，所以 $pre$，$suf$ 的大小都是 $O(\log V)$ 级别，然后就可以用双指针做了，复杂度 $O(n\log n\log V)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

const int N = 2e5 + 10, inf = 0x3f3f3f3f;
int n, v;
int a[N], b[N], c[N][22], lgn[N];

int max(int x, int y) {
	return (x > y) ? x : y;
}

int Amax(int l, int r) {
	int k = lgn[r - l + 1];
	return max(c[r][k], c[l + (1 << k) - 1][k]);
}

struct node {
	int ans;
	vector<pair<int, int>> pre, suf;
} tr[N << 2];

int merge(int u, int s, int t) {
	int j = (int)tr[u << 1].suf.size() - 1;
	while (tr[u << 1].suf[j].second < s) j -- ;
	int ans = inf;
	for (int i = 0; i < tr[u << 1 | 1].pre.size(); i ++ ) {
		if (tr[u << 1 | 1].pre[i].second > t) break;
		while (j > 0 && (tr[u << 1 | 1].pre[i].first | tr[u << 1].suf[j - 1].first) >= v) j -- ;
		if ((tr[u << 1 | 1].pre[i].first | tr[u << 1].suf[j].first) >= v) ans = min(ans, Amax(tr[u << 1].suf[j].second, tr[u << 1 | 1].pre[i].second));
	}
	return ans;
}

void build(int u, int l, int r) {
	if (l == r) {
		if (b[l] >= v) tr[u].ans = a[l];
		else tr[u].ans = inf;
		tr[u].pre.clear();
		tr[u].suf.clear();
		tr[u].pre.pb({0, l - 1});
		tr[u].pre.pb({b[l], l});
		tr[u].suf.pb({0, l + 1});
		tr[u].suf.pb({b[l], l});
		return;
	}
	int mid = l + r >> 1;
	build(u << 1, l, mid);
	build(u << 1 | 1, mid + 1, r);
	tr[u].ans = min(min(tr[u << 1].ans, tr[u << 1 | 1].ans), merge(u, l, r));
	tr[u].pre = tr[u << 1].pre;
	for (auto i : tr[u << 1 | 1].pre) {
		if ((i.first | tr[u].pre.back().first) ^ tr[u].pre.back().first)
			tr[u].pre.pb({(i.first | tr[u].pre.back().first), i.second});
	}
	tr[u].suf = tr[u << 1 | 1].suf;
	for (auto i : tr[u << 1].suf) {
		if ((i.first | tr[u].suf.back().first) ^ tr[u].suf.back().first)
			tr[u].suf.pb({(i.first | tr[u].suf.back().first), i.second});
	}
}

void modify(int u, int l, int r, int x) {
	if (l == r) {
		tr[u].ans = (b[l] >= v) ? a[l] : inf;
		tr[u].pre.clear();
		tr[u].suf.clear();
		tr[u].pre.pb({0, l - 1});
		tr[u].pre.pb({b[l], l});
		tr[u].suf.pb({0, l + 1});
		tr[u].suf.pb({b[l], l});		
		return;
	}
	int mid = l + r >> 1;
	if (x <= mid) modify(u << 1, l, mid, x);
	else modify(u << 1 | 1, mid + 1, r, x);
	tr[u].ans = min(min(tr[u << 1].ans, tr[u << 1 | 1].ans), merge(u, l, r));
	tr[u].pre = tr[u << 1].pre;
	for (auto i : tr[u << 1 | 1].pre) {
		if ((i.first | tr[u].pre.back().first) ^ tr[u].pre.back().first)
			tr[u].pre.pb({(i.first | tr[u].pre.back().first), i.second});
	}
	tr[u].suf = tr[u << 1 | 1].suf;
	for (auto i : tr[u << 1].suf) {
		if ((i.first | tr[u].suf.back().first) ^ tr[u].suf.back().first)
			tr[u].suf.pb({(i.first | tr[u].suf.back().first), i.second});
	}	
}

int ask(int u, int l, int r, int s, int t) {
	if (s <= l && r <= t) {
		return tr[u].ans;
	}
	int mid = l + r >> 1;
	if (s > mid) return ask(u << 1 | 1, mid + 1, r, s, t);
	if (t <= mid) return ask(u << 1, l, mid, s, t);
	return min(min(ask(u << 1, l, mid, s, t), ask(u << 1 | 1, mid + 1, r, s, t)), merge(u, s, t));
}

void solve() {
	scanf("%d%d", &n, &v);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i ++ ) scanf("%d", &b[i]);
	for (int i = 1; i <= n; i ++ ) {
		c[i][0] = a[i];
		for (int j = 1; j < 20; j ++ )
			if (i - (1 << j) >= 0)
				c[i][j] = max(c[i][j - 1], c[i - (1 << j - 1)][j - 1]);
	}
	build(1, 1, n);
	int q; scanf("%d", &q);
	while (q -- ) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1) {
			b[x] = y;
			modify(1, 1, n, x);
		} else {
			int res = ask(1, 1, n, x, y);
			printf("%d\n", (res == inf) ? -1 : res);
		}
	}
}

int main() {
	lgn[0] = -1;
	for (int i = 1; i < N; i ++ ) lgn[i] = lgn[i >> 1] + 1;
	int T;
	scanf("%d", &T);
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：zzafanti (赞：1)

## D1D

### description

给定两个长度为 $n$ 的序列 $a,b$，以及一个正整数 $v$。一个区间 $[l,r]$ 的权值为 $\max(a_l,a_{l+1},\dots,a_{r-1},a_{r})$。一个区间好当且仅当 $(b_{l}~\texttt{or}~b_{l+1}~\texttt{or}~\dots ~\texttt{or}~ b_{r})\ge v$。其中 $\texttt{or}$ 是按位或。

有 $Q$ 次操作。操作有两类：

1. 给出 $i,x$，给 $b_i$ 改成 $x$。
2. 给出 $l,r(1\leq l\leq r\leq n)$，求出 $[l,r]$ 的所有好的子区间中权值最小的子区间的权值大小。或报告不存在好的子区间。

- $n\leq 2\cdot 10^5$
- 5.0s 1024MB

### solution

观察到一个关键性质是一个序列只有不超过 $\log_2V$ 个前缀按位或取值，其中 $V$ 是值域。

于是我们可以在线段树上对每个区间维护前缀按位或的取值以及第一次的出现位置，并维护这个区间的答案。

后缀按位或也是同理。

合并两个区间时，两个区间答案取 $\min$，然后双指针枚举左边区间的后缀和右边区间的前缀，更新答案，至多枚举 $O(\log V)$ 次。然后把前后缀的按位或取值和出现位置合并即可。

$a$ 数组是一直不变的，所以可以 ST 表 $O(n\log n)$ 预处理，$O(1)$ 回答一个区间的权值。

时间复杂度 $O(n\log V+Q\log n\log V)$，空间复杂度 $O(n(\log V+\log n))$。

### code

[Submission #249093781 - Codeforces](https://codeforces.com/contest/1936/submission/249093781)

---

## 作者：不知名用户 (赞：1)

题意：给定两个数列 $a,b$ 和一个固定的整数 $v$，支持动态修改 $b$，询问给定 $L,R$ 求 $\min\limits_{L\le l\le r\le R\atop(b_l|b_{l+1}|\cdots|b_r)\ge v}\{\max\limits_{l\le i\le r}a_i\}$。数据范围：下标 $n=2\times10^5$，值域 $V=10^9$。

线段树维护，类似最大子段和（具体怎么维护下面会写到），需要维护前缀、后缀的信息，更新是把跨过端点和原来两边答案取 $\min$。

发现每个区间从左往右的前缀最大值最多变化 $\log V$ 次，把每次变化的端点记录下来。合并：把另一个变化的端点和当前最右边的做位运算或，如果不同则更新右端点。有个[坑](https://www.luogu.com.cn/discuss/794096)！维护的时候可能最后有冗余，但是不能不取 $\max$。

更新答案像最大子段和是两边的最小值，及跨过边界拼起来。直接合并 $O(\log^2V)$ 太慢，需要配合 `two-pointers` 实现 $O(\log V)$。

复杂度瓶颈在于合并是 $O(\log V)$ 的，所以初始化 $O(n\log V)$，修改和查询都是 $O(\log n\log V)$ 的。

[AC code.](https://codeforces.com/contest/1936/submission/252079871)
```cpp
#include<bits/stdc++.h>
#define inf 1000000001
using namespace std;

const int N = 2e5 + 10;

int v;

struct arr
{
	int x[32], mx[32], len, m;
};
int a[N], b[N];
arr itoa(int x, int y){arr a;a.len = 1, a.mx[1] = a.m = x, a.x[1] = y;return a;}
arr operator + (arr a, const arr &b)
{
	int i, m = a.m;
	a.m = max(a.m,b.m);
	for(i=1;i<=b.len;i++) if((a.x[a.len]|b.x[i])!=a.x[a.len])
	{
		a.len++;
		a.x[a.len] = a.x[a.len-1] | b.x[i];
		m = a.mx[a.len] = max(m,b.mx[i]);
	}
	return a;
}
struct node
{
	arr l, r;
	int ans;
}st[N*4];
node iton(int x, int y){node a;a.l = a.r = itoa(x,y);a.ans = (y >= v) ? x : inf;return a;}
node operator + (const node &x, const node &y)
{
	node z;
	z.l = x.l + y.l;
	z.r = y.r + x.r;
	z.ans = min(x.ans,y.ans);
	int i, j;
	for(i=1,j=y.l.len;i<=x.r.len;i++)
	{
		if((x.r.x[i]|y.l.x[j])<v) continue;
		while(j>=1&&(x.r.x[i]|y.l.x[j])>=v) j--;
		j++;
		z.ans = min(z.ans,max(x.r.mx[i],y.l.mx[j]));
	}
	return z;
}
inline void upd(int p){st[p] = st[p*2] + st[p*2+1];}
void build(int p, int L, int R)
{
	if(L==R) return st[p] = iton(a[L],b[L]), void();
	int mid = L + R >> 1;
	build(p*2,L,mid), build(p*2+1,mid+1,R);
	upd(p);
}
void ch(int p, int L, int R, int x, int y)
{
	if(L==R) return st[p] = iton(a[L],y), void();
	int mid = L + R >> 1;
	if(x<=mid) ch(p*2,L,mid,x,y);
	else ch(p*2+1,mid+1,R,x,y);
	upd(p);
}
node ask(int p, int l, int r, int L, int R)
{
	if(l<=L&&R<=r) return st[p];
	int mid = L + R >> 1;
	if(l>mid) return ask(p*2+1,l,r,mid+1,R);
	if(mid>=r) return ask(p*2,l,r,L,mid);
	return ask(p*2,l,r,L,mid) + ask(p*2+1,l,r,mid+1,R);
}

int Main()
{
	int n, q, i;
	scanf("%d%d", &n, &v);
	for(i=1;i<=n;i++) scanf("%d", &a[i]);
	for(i=1;i<=n;i++) scanf("%d", &b[i]);
	build(1,1,n);
	scanf("%d", &q);
	while(q--)
	{
		int op, l, r;
		scanf("%d%d%d", &op, &l, &r);
		if(op==1) ch(1,1,n,l,r);
		else
		{
			int ans = ask(1,l,r,1,n).ans;
			if(ans==inf) ans = -1;
			printf("%d ", ans);
		}
	}
	printf("\n");
	return 0;
}
int main(){int t;scanf("%d", &t);while(t--)Main();return 0;}
```

---

## 作者：XYQ_102 (赞：0)

# F. Bitwise Paradox

> You are given two arrays $a$ and $b$ of size $n$ along with a fixed integer $v$.
> 
> An interval $[l, r]$ is called a **good** interval if $(b_l \mid b_{l+1} \mid \ldots \mid b_r) \ge v$, where $|$ denotes the [bitwise OR operation](https://en.wikipedia.org/wiki/Bitwise_operation#OR). The **beauty** of a good interval is defined as $\max(a_l, a_{l+1}, \ldots, a_r)$.
> 
> You are given $q$ queries of two types:
> 
> +   "1 i x": assign $b_i := x$;
> +   "2 l r": find the **minimum** beauty among all **good** intervals $[l_0,r_0]$ satisfying $l \le l_0 \le r_0 \le r$. If there is no suitable good interval, output $-1$ instead.
> 
> Please process all queries.
> 
> $1 \le n,q \le 2 \times 10^5,1 \le a_i,b_i \le 10^9$。

DS 好题。一篇认认真真的题解。

  

读完题目，发现这是一个与二进制相关的问题，

而容易发现，每组数据中 $v,a_i$ 都是不变的，且涉及到 $b_l|b_{l+1}|\dots |b_r \ge v$ 的计算，

我们不难想到拆位，也就是对每一个二进制位分开来讨论。

  

现在再来看数据范围，直觉是可以去尝试 Poly log 的做法，

而用最普通的线段树来维护，问题就在于我们如何去 **合并两个区间**。

  

发现这是好做的，我们同样按照二进制位从高到低考虑，合并区间 $[l,mid]$ 和 $[mid+1,r]$，得到最优的满足条件区间 $[L,R]$。

设当前枚举到第 $i$ 位，假设 $v$ 的这一位要求是 $1$，那么这个 $1$ 一定来源于左区间或者右区间（根据或运算）。

假设左区间从右往左第一个 $i$ 位为 $1$ 的位置是 $P$，右区间从左往右第一个 $i$ 位为 $1$ 的位置是 $Q$，则：

+   如果 $\max_{i=P}^{mid} a_i \le \max_{i=mid+1}^{Q} a_i$，那么我们选择把 $L$ 扩展到 $P$ 。
    
+   反之我们选择把 $R$ 拓展到 $Q$。
    

这样贪心地选择一定是不劣的，因为你总需要拓展一个，我们希望答案尽可能优。

  

而 $v$ 的这一位不要求为 $1$ 的情况也是简单的，我们枚举选还是不选：

+   如果把这一位选成 $1$，操作与上面相同，而后面的位我们都不用选了，这样直接算上此时区间最大值与答案取 $\min$。
    
+   不选则继续往下枚举。
    

这样我们就可以做到两个区间的合并了，

实现中只需要维护一个区间每一位的 $P,Q$，容易发现这也是好维护的，下面是区间合并的代码：

```cpp
  //S(l,r) 算区间 [l,r] 中 a_i 的最大值
  sgt operator +(sgt Lp,sgt Rp){//合并区间 Lp 和 Rp
  	sgt res;
  	res.v=min(Lp.v,Rp.v),res.l=Lp.l,res.r=Rp.r;
    //v 是当前区间的答案，l,r 是当前区间的左右界
  	int L=Lp.r,R=Rp.l,tmp=inf,_L,_R;bool fl=1;
  	for(int i=30;i>=0;i--){
  	  res.pre[i]=Lp.pre[i]?Lp.pre[i]:Rp.pre[i];//更新当前区间第 i 位的 P，不存在为 0
  	  res.suf[i]=Rp.suf[i]?Rp.suf[i]:Lp.suf[i];//更新当前区间第 i 位的 Q，不存在为 0
  	  if(!fl) continue;//高位无法满足条件直接跳过
  	  if(!Lp.suf[i]&&!Rp.pre[i]){fl=!lim[i];continue;}//这一位无法为 1 满足条件
  	  if(!lim[i]) _L=L,_R=R;
  	  if(!Lp.suf[i]) R=max(R,Rp.pre[i]);
  	  else if(!Rp.pre[i]) L=min(L,Lp.suf[i]);
  	  else{
  	  	if(S(Lp.suf[i],Lp.r)<=S(Rp.l,Rp.pre[i])) L=min(L,Lp.suf[i]);
  	  	else R=max(R,Rp.pre[i]);
  	  }
  	  if(!lim[i]) tmp=min(tmp,S(L,R)),L=_L,R=_R;//在不要求选 1 时选了 1，可以直接更新答案
  	}
  	if(fl) res.v=min(res.v,S(L,R));
  	res.v=min(res.v,tmp);
  	return res;
  }
```

  

完成了区间合并，那么这道题就做完了。其实只要想到拆位，也就不难了。

实现中 $a$ 的区间最大值可以用 ST 表维护做到 $\mathcal O(1)$，那么总时间复杂度是 $\mathcal O(q \log n \log V + n \log V)$，后者是预处理的复杂度。

```cpp
const int N=2e5+5,inf=2e9;
int n,T,m,V,a[N],st[30][N],b[N],lg[N],lim[31];

void init(){
  lg[1]=0;
  for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
  for(int i=1;i<=lg[n]+1;i++)
    for(int j=1;j+(1<<i)-1<=n;j++)
      st[i][j]=max(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}

int S(int l,int r){
  int tmp=lg[r-l+1];
  return max(st[tmp][l],st[tmp][r-(1<<tmp)+1]);
}

namespace SGT{
  struct sgt{
    int v,pre[31],suf[31],l,r;
  }tr[N<<2];
  #define mid ((l+r)>>1)
  #define lc p<<1
  #define rc p<<1|1
  #define lson l,mid,lc
  #define rson mid+1,r,rc
  sgt operator +(sgt Lp,sgt Rp){
  	sgt res;
  	res.v=min(Lp.v,Rp.v),res.l=Lp.l,res.r=Rp.r;
  	int L=Lp.r,R=Rp.l,tmp=inf,_L,_R;bool fl=1;
  	for(int i=30;i>=0;i--){
  	  res.pre[i]=Lp.pre[i]?Lp.pre[i]:Rp.pre[i];
  	  res.suf[i]=Rp.suf[i]?Rp.suf[i]:Lp.suf[i];
  	  if(!fl) continue;
  	  if(!Lp.suf[i]&&!Rp.pre[i]){fl=!lim[i];continue;}
  	  if(!lim[i]) _L=L,_R=R;
  	  if(!Lp.suf[i]) R=max(R,Rp.pre[i]);
  	  else if(!Rp.pre[i]) L=min(L,Lp.suf[i]);
  	  else{
  	  	if(S(Lp.suf[i],Lp.r)<=S(Rp.l,Rp.pre[i])) L=min(L,Lp.suf[i]);
  	  	else R=max(R,Rp.pre[i]);
  	  }
  	  if(!lim[i]) tmp=min(tmp,S(L,R)),L=_L,R=_R;
  	}
  	if(fl) res.v=min(res.v,S(L,R));
  	res.v=min(res.v,tmp);
  	return res;
  }
  void pu(int p){tr[p]=tr[lc]+tr[rc];}
  void Up(int p,int l){
    tr[p].l=tr[p].r=l,tr[p].v=(b[l]>=V)?a[l]:inf;
    for(int i=0;i<31;i++) tr[p].pre[i]=tr[p].suf[i]=((b[l]>>i)&1)?l:0;
  }
  void build(int l,int r,int p){
    if(l==r) return Up(p,l);
    build(lson),build(rson),pu(p);
  }
  void upd(int l,int r,int p,int x){
  	if(l==r) return Up(p,l);
  	x<=mid?upd(lson,x):upd(rson,x);pu(p);
  }
  sgt qry(int l,int r,int p,int x,int y){
  	if(x<=l&&y>=r) return tr[p];
  	if(y<=mid) return qry(lson,x,y);
  	if(x>mid) return qry(rson,x,y);
  	return qry(lson,x,y)+qry(rson,x,y);
  }
}
using namespace SGT;

void sol(){
  cin>>n>>V;
  for(int i=0;i<31;i++) lim[i]=((V>>i)&1);
  for(int i=1;i<=n;i++) cin>>a[i],st[0][i]=a[i];
  for(int i=1;i<=n;i++) cin>>b[i];
  init();build(1,n,1);
  cin>>m;
  while(m--){
  	int op,l,r;cin>>op>>l>>r;
  	if(op==1) b[l]=r,upd(1,n,1,l);
  	else{
  	  sgt res=qry(1,n,1,l,r);
  	  if(res.v==inf) cout<<"-1 ";
  	  else cout<<res.v<<' ';
  	}
  }
  cout<<'\n';
}

int main(){
  ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
  cin>>T;
  while(T--) sol();
  return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/CF1936D)

**题目大意**

> 给定 $n,k,a_1\sim a_n,b_1\sim b_n$，定义一个区间 $[l,r]$ 是好的当且仅当 $\mathrm{OR}_{i=l}^r b_i\ge k$，记该区间权值为 $\max_{i=l}^r a_i$。
>
> $q$ 次操作单点修改 $b_i$，或询问 $[l,r]$ 所有子区间中权值最小的好区间。
>
> 数据范围：$n,q\le 2\times 10^5$。

**思路分析**

考虑线段树维护区间答案，每次合并 $[l,mid],[mid+1,r]$ 时，只需考虑跨越 $mid$ 的所有区间。

容易发现这些区间都是 $[l,mid]$ 的后缀拼上 $[mid+1,r]$ 的前缀。

根据经典结论，一个区间本质不同的前后缀 $\mathrm{OR}$ 只有 $\mathcal O(\log V)$ 个，因为每个位只有一次从 $0$ 变成 $1$ 的机会。

对于 $[l,mid]$ 所有 $\mathrm{OR}$ 相同的后缀，只有最小的一个有意义，同理 $[mid+1,r]$ 中所有 $\mathrm{OR}$ 相同的后缀，只有最大的一个有意义。

注意到所有的前后缀 $\mathrm{OR}$  都具有单调性，因此可以合并时用双指针求有意义的区间，用 ST 表快速计算区间权值。

那么一个区间的信息只有区间答案，以及区间本质不同极小前后缀，合并容易做到 $\mathcal O(\log V)$。

时间复杂度 $\mathcal O((n+q)\log n\log V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5,inf=2e9;
typedef vector<array<int,2>> vi;
int n,k,q,a[MAXN],b[MAXN],st[MAXN][20];
int bit(int x) { return 1<<x; }
int qmax(int l,int r) {
	int z=__lg(r-l+1);
	return max(st[l][z],st[r-bit(z)+1][z]);
}
struct info {
	int v; vi pre,suf;
	friend info operator +(const info &l,const info &r) {
		int x; info w; w.v=min(l.v,r.v);
		const vi &t=r.pre; auto it=t.rbegin();
		for(auto i:l.suf) {
			while(it!=t.rend()&&(i[0]|(*it)[0])>=k) ++it;
			if(it!=t.rbegin()) {
				--it,w.v=min(w.v,qmax(i[1],(*it)[1]));
			}
		}
		x=l.pre.back()[0],w.pre=l.pre;
		for(auto i:r.pre) if((i[0]|x)>x) w.pre.push_back({x|=i[0],i[1]});
		x=r.suf.back()[0],w.suf=r.suf;
		for(auto i:l.suf) if((i[0]|x)>x) w.suf.push_back({x|=i[0],i[1]});
		return w;
	}
};
struct SegmentTree {
	info tr[MAXN<<2];
	void psu(int p) { tr[p]=tr[p<<1]+tr[p<<1|1]; }
	void init(int l=1,int r=n,int p=1) {
		if(l==r) {
			tr[p].v=(b[l]>=k?a[l]:inf);
			tr[p].pre=tr[p].suf=vi(1,{b[l],l});
			return ;
		}
		int mid=(l+r)>>1;
		init(l,mid,p<<1),init(mid+1,r,p<<1|1);
		psu(p);
	}
	void set(int u,int l=1,int r=n,int p=1) {
		if(l==r) {
			tr[p].v=(b[l]>=k?a[l]:inf);
			tr[p].pre=tr[p].suf=vi(1,{b[l],l});
			return ;
		}
		int mid=(l+r)>>1;
		u<=mid?set(u,l,mid,p<<1):set(u,mid+1,r,p<<1|1);
		psu(p);
	}
	info qry(int ul,int ur,int l=1,int r=n,int p=1) {
		if(ul<=l&&r<=ur) return tr[p];
		int mid=(l+r)>>1;
		if(ur<=mid) return qry(ul,ur,l,mid,p<<1);
		if(mid<ul) return qry(ul,ur,mid+1,r,p<<1|1);
		return qry(ul,ur,l,mid,p<<1)+qry(ul,ur,mid+1,r,p<<1|1);
	}
}	T;
void solve() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]),st[i][0]=a[i];
	for(int z=1;z<20;++z) for(int i=1;i+bit(z)-1<=n;++i) {
		st[i][z]=max(st[i][z-1],st[i+bit(z-1)][z-1]);
	}
	for(int i=1;i<=n;++i) scanf("%d",&b[i]);
	T.init();
	scanf("%d",&q);
	for(int op,x,y;q--;) {
		scanf("%d%d%d",&op,&x,&y);
		if(op==1) b[x]=y,T.set(x);
		else {
			auto z=T.qry(x,y);
			printf("%d ",z.v<inf?z.v:-1);
		}
	}
	puts("");
}
signed main() {
	int cas; scanf("%d",&cas);
	while(cas--) solve();
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

首先有个很简单的结论，就是不同的 $b_i\operatorname{or}b_{i+1}\operatorname{or}\dots\operatorname{or}b_r$ 最多有 $\log V$ 种。这也是很容易解释的，因为有 $\log V$ 的二进制位，每 $\operatorname{or}$ 一次要么不变，要么加上若干个二进制位。

考虑线段树维护一个区间使 $b_x\operatorname{or}b_{x+1}\operatorname{or}\dots\operatorname{or}b_y\geq v$ 的 $\max(a_x,a_{x+1},\dots,a_y)$ 的最小值，以及前缀和后缀的所有不同 $\operatorname{or}$ 的首次出现的值与对应段 $a_i$ 的最大值。合并时使用双指针对跨区间的统计一下即可。一次 $\operatorname{pushup}$ 是 $O(\log V)$ 的（具体见代码 $\operatorname{merge}$ 部分），故总复杂度 $O(q\log n\log V)$。

```cpp
#include <bits/stdc++.h>
//#define int long long
#define mid ((l+r)>>1)
using namespace std;
struct node{
	int preval[35],premax[35],pretot;
	int sufval[35],sufmax[35],suftot;
	int minv,maxv;
};
int v,a[200005],b[200005];
node merge(node x,node y){
	node ans;
	ans.preval[0]=ans.sufval[0]=ans.premax[0]=ans.sufmax[0]=0;
	ans.minv=min(x.minv,y.minv); ans.maxv=max(x.maxv,y.maxv);
	{
		int j=0;
		for(int i=x.suftot;i>=1;i--){
			while((x.sufval[i]|y.preval[j])<v&&j!=y.pretot) j++;
			if((x.sufval[i]|y.preval[j])>=v){
				ans.minv=min(ans.minv,max(x.sufmax[i],y.premax[j]));
			}
		}
	}
	{
		for(int i=1;i<=x.pretot;i++) ans.preval[i]=x.preval[i],ans.premax[i]=x.premax[i];
		int now=x.preval[x.pretot],pmax=x.maxv;
		ans.pretot=x.pretot;
		for(int i=1;i<=y.pretot;i++) if((now|y.preval[i])!=now) now=now|y.preval[i],ans.pretot++,ans.preval[ans.pretot]=now,ans.premax[ans.pretot]=max(pmax,y.premax[i]);
	}
	{
		for(int i=1;i<=y.suftot;i++) ans.sufval[i]=y.sufval[i],ans.sufmax[i]=y.sufmax[i];
		int now=y.sufval[y.suftot],pmax=y.maxv;
		ans.suftot=y.suftot;
		for(int i=1;i<=x.suftot;i++) if((now|x.sufval[i])!=now) now=now|x.sufval[i],ans.suftot++,ans.sufval[ans.suftot]=now,ans.sufmax[ans.suftot]=max(pmax,x.sufmax[i]);
	}
	return ans;
}
node makenode(int x,int y){
	node ans;
	ans.preval[0]=ans.sufval[0]=ans.premax[0]=ans.sufmax[0]=0;
	ans.pretot=ans.suftot=1;
	ans.preval[1]=ans.sufval[1]=y;
	ans.premax[1]=ans.sufmax[1]=x;
	if(y>=v) ans.minv=x;
	else ans.minv=2e9;
	ans.maxv=x;
	return ans;
}
struct sgt{
	node f[1000005];
	void build(int i,int l,int r){
		if(l==r){
			f[i]=makenode(a[l],b[l]);
			return ;
		}
		build(i*2,l,mid),build(i*2+1,mid+1,r);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void change(int i,int l,int r,int pos,node cg){
		if(l==r){
			f[i]=cg;
			return ;
		}
		if(pos<=mid) change(i*2,l,mid,pos,cg);
		else change(i*2+1,mid+1,r,pos,cg);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	node qry(int i,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return f[i];
		if(qr<=mid) return qry(i*2,l,mid,ql,qr);
		if(ql>mid) return qry(i*2+1,mid+1,r,ql,qr);
		return merge(qry(i*2,l,mid,ql,qr),qry(i*2+1,mid+1,r,ql,qr));
	}
}tree;
void solve(){
	int n; cin>>n>>v;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	tree.build(1,1,n);
	int q; cin>>q;
	while(q--){
		int opt; cin>>opt;
		if(opt==1){
			int i,x; cin>>i>>x;
			tree.change(1,1,n,i,makenode(a[i],x));
		}
		else{
			int l,r; cin>>l>>r;
			node tmp=tree.qry(1,1,n,l,r);
			if(tmp.minv>1e9) cout<<-1;
			else cout<<tmp.minv;
			cout<<" ";
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t; cin>>t; while(t--) solve(),cout<<"\n";
	return 0;
}
```

---

## 作者：Albert_van (赞：0)

[题](https://www.luogu.com.cn/problem/CF1936D)。带修考虑线树。一开始想维护每个点向右前缀 $\text{OR}$ 的 $\log V$ 段，发现修改量不可接受。注意到 $\max$ 可**重复贡献**，考虑按位考虑。

每个结点维护本区间的答案，并对每一个二进制位 $i$，维护其在区间内最左/最右的出现位置 $l_i,r_i$。类似于分治，合并区间 $[x,y]$ 和 $[y+1,z]$ 时，考虑计算跨过中点 $(y,y+1)$ 的答案。

此时考虑，若钦定 $[l_0,r_0]$ 的 $\text{OR}$ 结果在 $s$ 第 $i$ 位为 $1$，$l_0,r_0$ 会受到什么限制。显然是 $(l_0\le L_i\text{或}r_0\ge R_i)$，$L_i$ 为左区间的 $r_i$，$R_i$ 为右区间的 $l_i$。

以此为基础，考虑从高到低枚举 $i$，满足 $v$ 在第 $i$ 位为 $0$，并认为 $i$ 是 $s$ 与 $v$ **最高的不同位**（$i$ 为 $v$ 的 $\operatorname{lowbit}$ 也需纳入考虑，此时 $s=v$。所有操作前令 $v\gets v-1$ 然后当 $s>v$ 来做也可）。这对 $l_0,r_0$ 的限制是：

- $\forall j\ge i$ 满足 $j=i$、或 $v$ 在第 $j$ 位为 $1$，均有 $(l_0\le L_j\text{或}r_0\ge R_j)$。

看上去难做，但是注意到 $\max$ 可重复贡献。这意味着，对于每一条 $j$ 的限制，我们可以**分别贪心**。具体地，取 $x_j=\max\{a_{L_j},\cdots,a_{y+1}\},y_j=\max\{a_{y},\cdots,a_{R_j}\}$†，那么最终有 $s=\max_j\{\min(x_j,y_j)\}$。感性理解，无论选择左还是右，都不影响后续 $j$ 对最优性的判断。对所有 $i$ 的答案取 $\min$ 即可。

区间 $\max$ 以 ST 表实现。单次合并 $\mathcal O(\log V)$，整体 $\mathcal O(n\log n\log V)$。实际上这题把区间 $\max$ 换成区间和一类也能做，扫 $l_0$ 维护 $r_0$ 最小值，复杂度不变。

† CF 的 std 在这里令 $x_j$ 取区间右端点为 $a_y$，$y_j$ 取左端点为 $a_{y+1}$。这并不影响答案：若最终方案中 $x$ 与 $y$ 均有选择，那么两个下标的值都作出了贡献；反之，该答案不跨过 $(y,y+1)$，在子区间中已被计算。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=231231,lb=30,inf=0x3f3f3f3f;

int a[N],v;

namespace ST{
	int s[N][18];
	void build(int n){
		for(int i=1;i<=n;++i) s[i][0]=a[i];
		for(int l=1;(1<<l)<=n;++l) for(int i=1;i+(1<<l)-1<=n;++i)
			s[i][l]=max(s[i][l-1],s[i+(1<<l-1)][l-1]);
	}
	int mx(int l,int r){
		int g=__lg(r-l+1);
		return max(s[l][g],s[r-(1<<g)+1][g]);
	}
}

namespace sgt{
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	struct node{
		int l[lb],r[lb],res;
		#define l(x) x.l
		#define r(x) x.r
		#define res(x) x.res
	}t[N<<2],S;
	node mrg(node L,node R,int m){
		res(S)=min(res(L),res(R));
		int cr=0;for(int i=lb-1,nw;~i;--i){
			int r=l(R)[i]<inf?ST::mx(m+1,l(R)[i]):inf,
				l=r(L)[i]?ST::mx(r(L)[i],m):inf;
			nw=max(min(l,r),cr);
			if(v&(1<<i)){
				cr=nw;if((1<<i)==(v&-v)) res(S)=min(res(S),nw);
			}else res(S)=min(res(S),nw);
		}
		for(int i=0;i<lb;++i)
			l(S)[i]=min(l(L)[i],l(R)[i]),r(S)[i]=max(r(L)[i],r(R)[i]);
		return S;
	}
	void set(int u,int p,int x){
		for(int i=0;i<lb;++i) x&(1<<i)?l(t[u])[i]=r(t[u])[i]=p:
			(l(t[u])[i]=inf,r(t[u])[i]=0);
		res(t[u])=x>=v?ST::mx(p,p):inf;
	}
	void build(int now,int ln,int rn){
		if(ln==rn) return set(now,ln,a[ln]);
		int mid=ln+rn>>1;
		build(ls(now),ln,mid);
		build(rs(now),mid+1,rn);
		t[now]=mrg(t[ls(now)],t[rs(now)],mid);
	}
	void upd(int now,int ln,int rn,int p,int x){
		if(ln==rn) return set(now,p,x);
		int mid=ln+rn>>1;
		if(p<=mid) upd(ls(now),ln,mid,p,x);
		else upd(rs(now),mid+1,rn,p,x);
		t[now]=mrg(t[ls(now)],t[rs(now)],mid);
	}
	node qry(int now,int ln,int rn,int l,int r){
		if(l<=ln&&rn<=r) return t[now];
		int mid=ln+rn>>1;bool flg=0;node res;
		if(l<=mid) res=qry(ls(now),ln,mid,l,r),flg=1;
		if(r>mid) S=qry(rs(now),mid+1,rn,l,r),flg?res=mrg(res,S,mid):res=S;
		return res;
	}
}

int main()
{
	int T;scanf("%d",&T);while(T--){
		int n;scanf("%d%d",&n,&v);
		for(int i=1;i<=n;++i) scanf("%d",a+i);
		ST::build(n);
		for(int i=1;i<=n;++i) scanf("%d",a+i);
		sgt::build(1,1,n);
		int q,f,x,y;scanf("%d",&q);while(q--){scanf("%d%d%d",&f,&x,&y);switch(f){
			case 1:sgt::upd(1,1,n,x,y);break;
			case 2:int r=sgt::qry(1,1,n,x,y).res;printf("%d ",r<inf?r:-1);
		}}puts("");
	}
}
```

---

