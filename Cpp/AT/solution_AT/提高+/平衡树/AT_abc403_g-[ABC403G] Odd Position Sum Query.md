# [ABC403G] Odd Position Sum Query

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc403/tasks/abc403_g

初始有一个空数列 $A$。

需要依次处理 $Q$ 个查询。第 $i$ 个查询的描述如下：

> 给定整数 $y_i$。定义 $z$ 为：当 $i=1$ 时 $z=0$，否则 $z$ 为第 $i-1$ 个查询的答案。然后定义 $x_i=((y_i+z)\bmod 10^9)+1$。将 $x_i$ 添加到 $A$ 的末尾。
> 
> 接着，将 $A$ 升序排列得到序列 $B=(B_1,B_2,\ldots,B_i)$，求 $B$ 中奇数位置元素的总和。即若 $m$ 为不超过 $i$ 的最大奇数，则求 $B_1+B_3+B_5+\ldots+B_m$。

## 说明/提示

### 约束条件

- $1 \leq Q \leq 3 \times 10^5$
- $0 \leq y_i < 10^9$
- $1 \leq x_i \leq 10^9$
- 输入均为整数

### 样例解释 #1

- 第 1 个查询：$y_1=1,z=0$，故 $x_1=((1+0)\bmod 10^9)+1=2$。$A$ 变为 $(2)$，排序后 $B=(2)$，答案为 $B_1=2$。
- 第 2 个查询：$y_2=3,z=2$，故 $x_2=((3+2)\bmod 10^9)+1=6$。$A$ 变为 $(2,6)$，排序后 $B=(2,6)$，答案为 $B_1=2$。
- 第 3 个查询：$y_3=1,z=2$，故 $x_3=((1+2)\bmod 10^9)+1=4$。$A$ 变为 $(2,6,4)$，排序后 $B=(2,4,6)$，答案为 $B_1+B_3=8$。
- 第 4 个查询：$y_4=999999994,z=8$，故 $x_4=((999999994+8)\bmod 10^9)+1=3$。$A$ 变为 $(2,6,4,3)$，排序后 $B=(2,3,4,6)$，答案为 $B_1+B_3=6$。
- 第 5 个查询：$y_5=999999993,z=6$，故 $x_5=((999999993+6)\bmod 10^9)+1=1000000000$。$A$ 变为 $(2,6,4,3,1000000000)$，排序后 $B=(2,3,4,6,1000000000)$，答案为 $B_1+B_3+B_5=1000000006$。

### 样例解释 #2

$x_1,x_2,\ldots,x_8$ 的值依次为：

- 105282054
- 800516877
- 573289179
- 26509423
- 168629803
- 696409999
- 656737335
- 915059758

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
5
1
3
1
999999994
999999993```

### 输出

```
2
2
8
6
1000000006```

## 样例 #2

### 输入

```
8
105282053
695234822
468007124
120710491
568831200
700753895
765188109
262666319```

### 输出

```
105282054
105282054
905798931
599798602
995656103
891549225
1652393438
1652393438```

# 题解

## 作者：Dtw_ (赞：6)

## 题意
有 $q$ 次询问，每次询问给你一个数 $x$，你需要把 $x$ 插入到初始为空的序列 $A$，然后对 $A$ 排序，求 $A$ 奇数位置上的数的和。

强制在线。
## Solution
因为我们不关心这个序列到底是啥，我们只关心和，所以我们放到值域上去做。

考虑假设你有 $c$ 个 $x$，那么奇数位置上的数的和是 $\left \lceil \frac{c}{2}  \right \rceil \times x$，同样的，偶数位置上的和也是好求的。

那么这个东西肯定可以合并，所以我们就考虑线段树。

对于每个点我都记 $c,odd,even$ 分别表示区间内点的个数，奇数位置上的和以及偶数位置上的和。

那合并的时候我们只需要看左子树的数量是奇数还是偶数就行，然后我们算出当前点的 $c,odd,even$ 即可。

答案就是根节点的 $odd$。但是值域很大，所以动态开点线段树即可。
## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define ll long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int N = 3e5 + 10, P = 1e9;

int q, cnt, rt;

struct node {
    int l, r, c;
    ll odd, even;
} tr[N * 30];

#define l(rt) tr[rt].l
#define r(rt) tr[rt].r
#define mid (l + r) / 2

void push_up(node &a, node b, node c)
{
    a.c = b.c + c.c;
    a.odd = b.odd + (b.c & 1 ? c.even : c.odd);
    a.even = b.even + (b.c & 1 ? c.odd : c.even);
}

void update(int &rt, int l, int r, int p)
{
    if (!rt) rt = ++cnt;
    if (l == r) {
        tr[rt].c++;
        tr[rt].even = 1ll * tr[rt].c / 2 * l;
        tr[rt].odd = 1ll * (tr[rt].c + 1) / 2 * l;
        return;
    }
    if (p <= mid) update(l(rt), l, mid, p);
    else update(r(rt), mid + 1, r, p);
    push_up(tr[rt], tr[l(rt)], tr[r(rt)]);
}

int main()
{
    fst
    cin >> q;
    ll la = 0;
    for (int i = 1; i <= q; i++) {
        int x; cin >> x; x = (x + la) % P + 1;
        update(rt, 1, P, x);
        cout << (la = tr[rt].odd) << "\n";
    }
    return 0;
}
```

---

## 作者：xxr___ (赞：6)

前情提要：超级好写的题。

知识：值域线段树。

对每个值域线段树的节点维护三个信息 $len,even,odd$ 分别表示这个区间的长度（注意不能直接 $r - l + 1$ 了，因为可能会有元素重复），区间内奇数位置的和，偶数位置的和。

我们发现，这种线段树是不用下传标记的，考虑上传的时候如果处理。

设 $ls(u)$ 表示值域线段树上 $u$ 的左儿子，$rs(u)$ 表示值域线段树上 $u$ 的右儿子。

1. $len(u) = len(ls(u)) + len(rs(u))$ 不用解释吧。
2. $even(u) = even(ls(u)) + $ 如果 $len(ls(u))$ 是奇数，那么就相当于是拼接上右儿子的偶数位置的值，否则就是奇数位置。
3. $odd(u)$ 和 $even(u)$ 一样计算。

然后就做完了，代码 27 行。

代码：
```cpp
#include<iostream>
#define int long long
const int N = 2e5 + 5;
struct node{
	int len,even,odd;//区间长度，奇数位置的和，偶数位置的和 
}tr[N << 5];
int n,q,lst = 0,rt = 0,ls[N << 5],rs[N << 5],idx = 0,vl;
inline node operator + (const node & x,const node & y){
	return (node){x.len + y.len,x.even + ((x.len & 1) ? y.odd : y.even),x.odd + ((x.len & 1) ? y.even : y.odd)};
}
inline void ins(int &u,int l,int r,int x){
	if(!u) u = ++ idx;
	if(l == r) return (tr[u] = tr[u] + (node){1,l,0}),void();
	int mid = (l + r) >> 1;
	(x <= mid ? ins(ls[u],l,mid,x) : ins(rs[u],mid + 1,r,x));
	tr[u] = tr[ls[u]] + tr[rs[u]];
}
int32_t main(){
	std::cin >> q;
	for(int i = 1;i <= q; ++ i){
		std::cin >> vl;
		vl = (vl + lst) % 1000000000 + 1;
		ins(rt,1,1e9,vl);
		std::cout << (lst = tr[rt].even) << '\n';
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：4)

# 题目链接

[[ABC403G] Odd Position Sum Query](https://www.luogu.com.cn/problem/AT_abc403_g)

# 解题思路

介绍一个根号做法。

考虑根号重构，设一个阀值 $B$，将询问分成 $\displaystyle \lfloor \frac{n}{B} \rfloor$ 块，每 $B$ 次询问重构一次，前 $B$ 次操作暴力做。

这样在第 $i$ 次询问就会有 $\max(\displaystyle\lfloor\frac{i}{B}\rfloor , 1)$ 块，只需要支持块内插入一个数字即可，这里可以使用 vector 维护，那么插入一个数复杂度为 $O(B + \displaystyle\lfloor\frac{n}{B}\rfloor)$ 总时间复杂度为 $O(nB + n \lfloor\displaystyle\frac{n}{B}\rfloor)$，$B$ 取 $\sqrt{n}$ 即可。

# 参考代码

```cpp
ll n;
ll sq,x;
ll a[1000010];
ll last;
ll f(ll x){
    return ((x+last)%(ll)1e9)+1;
}
struct bl{
    ll l,r;
    vector<pii>v;
    ll s0,s1;
    ll S;
    ll maxn;
    void clear()
    {
        maxn=0;
        l=0,r=0;
        v.clear();
        s0=s1=0;
    }
    void add(ll x)
    {
        if(Max(maxn,x))
        {
            v.pb({x,1});
            return ;
        }
        bool P=0;
        vector<pii>v2;
        for(auto i:v)
        {
            if(x<i.x)
            {
                if(!P)
                    v2.pb({x,1}),
                    P=1;
                v2.pb(i);
            }
            else if(x==i.x)
                P=1,
                v2.pb({x,i.y+1});
            else
                v2.pb(i);
        }
        if(!P)
            v2.pb({x,1});
        v=v2;
        // for(auto j:v)
            // cout<<",,"<<j.x<<" "<<j.y<<endl;
    }
    void query()
    {
        s1=s0=0;
        S=0;
        ll now=1;
        for(auto i:v)
        {
            if(now)
            {
                s1+=(i.y+1)/2*i.x;
                s0+=i.y/2*i.x;
                now^=i.y&1;
            }
            else
            {
                s0+=(i.y+1)/2*i.x;
                s1+=i.y/2*i.x;
                now^=i.y&1;
            }
            S+=i.y;
        }
    }
}B[300010];
/*
2 6 4 3 1000000000
*/
void build(ll x)
{
    forl(i,1,x)
        B[i].clear();
    sort(a+1,a+1+x*sq);
    forl(i,1,x)
    {
        B[i].l=B[i-1].r+1;
        B[i].r=i*sq;
        forl(j,B[i].l,B[i].r)
        {
            ll R=j,S=1;
            while(R<B[i].r && a[R+1]==a[j])
                R++,
                S++;
            B[i].v.pb({a[j],S});
            j=R;
        }
        B[i].maxn=a[B[i].r];
        B[i].query();
        // cout<<i<<":"<<B[i].s0<<' '<<B[i].s1<<endl;
    }
}
void _clear(){}
void solve()
{
    _clear();
    cin>>n;
    sq=sqrt(n);
    forl(i,1,min(n,sq))
    {
        cin>>x;
        x=f(x);
        a[i]=x;
        sort(a+1,a+1+i);
        ll S=0;
        forll(j,1,i,2)
            S+=a[j];
        cout<<S<<endl;
        last=S;
    }
    forl(i,sq+1,n)
    {
        if(i%sq==1)
            build(i/sq);
        cin>>x;
        x=f(x);
        a[i]=x;
        ll P=0;
        forl(j,1,i/sq)
            if(x<=B[j].maxn)
            {
                // cout<<i<<" add "<<j<<endl;
                P=1;
                B[j].add(x);
                B[j].query();
                break;
            }
        if(!P)
            B[i/sq].add(x),
            B[i/sq].query();
        ll now=0;
        ll ans=0;
        forl(j,1,i/sq)
        {
            if(now==0)
            {    
                ans+=B[j].s1;
                now^=B[j].S&1;
            }
            else
            {
                ans+=B[j].s0;
                now^=B[j].S&1;
            }
        }
        cout<<ans<<endl;
        last=ans;
    }
}
```

---

## 作者：gcx114514 (赞：3)

我们注意到是对其升序排列后的奇数位，而且动态加点，我们考虑有平衡树维护升序后的序列（这里使用 FHQ）。

我们在平衡树上维护 $val_0$ 和 $val_1$ 分别表示偶数位和奇数位的权值和，同时维护一个 $num$ 表示当前点是奇数位还是偶数位，维护 $tag$ 表示是否有 $num$ 取反的 $tag$ 。

因为我们发现，当我们插入一个数时，其后面的数的位置奇偶性就会发生改变，直接区间操作即可，剩下的就是板子了，这样的复杂度是 $O(n\log n)$ 的，可以通过。

### Code

```cpp
#include <bits/stdc++.h>
#define pii pair<int,int>
#define pb emplace_back
#define int long long
#define mk make_pair
#define se second
#define fi first
using namespace std;
bool Mst;
const int Max=2e5+10;
const int mod=1e9;
const int inf=1e9+10; 

inline int read(){
	int res=0,v=1;
	char c=getchar();
	while(c<'0'||c>'9'){v=(c=='-'?-1:1);c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<3)+(res<<1)+(c^48);c=getchar();}
	return res*v;
}

struct FHQ{
	
	int tag,val[2],sum,key,ch[2],num,siz;
	#define val(x,i) tr[x].val[i]
	#define ch(x,i) tr[x].ch[i]
	#define tag(x) tr[x].tag
	#define sum(x) tr[x].sum
	#define num(x) tr[x].num
	#define key(x) tr[x].key
	#define siz(x) tr[x].siz
	
}tr[Max<<2];
int root;
void pushup(int now){
	val(now,0)=val(ch(now,0),0)+val(ch(now,1),0)+(num(now)?0:sum(now));
	val(now,1)=val(ch(now,1),1)+val(ch(now,0),1)+(num(now)?sum(now):0);
	siz(now)=siz(ch(now,0))+siz(ch(now,1))+1;
}

void work(int now){
	tag(now)^=1;num(now)^=1;swap(val(now,0),val(now,1)); 
}

void pushdown(int now){
	if(tag(now)){
		work(ch(now,0));
		work(ch(now,1));
		tag(now)=0;
	}
}

void Split(int now,int val,int &x,int &y){
	if(!now){x=y=0;return;}pushdown(now);
	if(sum(now)<=val){
		x=now;Split(ch(now,1),val,ch(x,1),y);
	}else{
		y=now;Split(ch(now,0),val,x,ch(y,0));
	}
	pushup(now);
}

int merge(int x,int y){
	if(!x||!y){return x|y;}
	if(key(x)<key(y)){
		pushdown(x);
		ch(x,1)=merge(ch(x,1),y);
		pushup(x);return x;
	}else{
		pushdown(y);
		ch(y,0)=merge(x,ch(y,0));
		pushup(y);return y;
	}
}

int tot=0;

int Build(int val,int num){
	int now=++tot;
	sum(now)=val;num(now)=num;
	key(now)=rand();siz(now)=1;
	val(now,num(now))=val;
	return now;
}

void Insert(int val){
	int x,y;
	Split(root,val,x,y);
	work(y);root=merge(merge(x,Build(val,(siz(x)+1)&1)),y);
}



bool Med;
signed main(){
	int n=read();
	int las=0;
	for(int i=1;i<=n;++i){
		int x=(read()+las)%mod+1;
		Insert(x);las=val(root,1);
		cout << las << "\n";
	}


	cerr<< "Time: "<<clock()/1000.0 << "s\n";
	cerr<< "Memory: " << (&Mst-&Med)/1000000.0 << "MB\n";
	return 0;
}

```

---

## 作者：FFTotoro (赞：3)

*本篇题解参考了 [__gnu_pbds 中 tree 的扩展应用](https://www.cnblogs.com/redacted-area/p/18063265#join-%E5%92%8C-split)，在此表示对作者的感谢。*

> 你说得对，但是 `__gnu_pbds::tree` 是可以支持自定义 `pushup` 的。

前置知识：[__gnu_pbds::tree 的基本使用方法](https://oi-wiki.org/lang/pb-ds/tree/)

考虑如何设计信息：需要维护的是，对于两个区间 $[l_1,r_1],[l_2,r_2]$，将 $[l_2,r_2]$ 接在 $[l_1,r_1]$ 之后所有奇数位置的和。维护信息 $(s,o,e)$ 分别表示当前区间大小、奇数下标和与偶数下标和；合并 $(s_1,o_1,e_1)$ 与 $(s_2,o_2,e_2)$ 时分类讨论：

- 若 $s_1$ 为奇数，那么合并结果为 $(s_1+s_2,o_1+e_2,e_1+o_2)$；
- 否则，合并结果为 $(s_1+s_2,o_1+o_2,e_1+e_2)$。

使用一个 `tuple<int,long long,long long>` 来存储信息。以下是一个信息合并的函数的例子：

```cpp
typedef long long ll;
typedef tuple<int,ll,ll> tpi;
inline tpi operator +(const tpi &x,const tpi &y){
  return make_tuple(get<0>(x)+get<0>(y),
    get<1>(x)+(get<0>(x)&1?get<2>(y):get<1>(y)),
    get<2>(x)+(get<0>(x)&1?get<1>(y):get<2>(y)));
}
```

先定义一个结构体表示 `tree` 存储的类型（其中包含 `key`，即比较的关键字，以及其他你想维护的信息）。以下是一个本题中可以使用的结构体的例子：

```cpp
struct S{
  int key; mutable tpi c;
  // 使用 mutable 是因为需要修改
  S(int key=0,int x=0,ll y=0,ll z=0):key(key),c(x,y,z){}
  bool operator <(const S &b)const{return key<b.key;}
  // 按照 key 排序
};
```

接下来自定义平衡树中的信息合并：即在 `tree` 中 `Node_Update` 的位置放上一个自己定义的更新。

```cpp
template<class Node_CItr,class Node_Itr,class Cmp_Fn,class _Alloc> struct op{
  typedef tpi metadata_type;
  // 维护的额外信息
  void operator()(Node_Itr it,Node_CItr end_it){
    Node_Itr itl=it.get_l_child();
    Node_Itr itr=it.get_r_child();
    tpi l,r;
    if(itl!=end_it)l=itl.get_metadata();
    if(itr!=end_it)r=itr.get_metadata();
    const_cast<tpi&>(it.get_metadata())=l+(*it)->c+r;
    // 信息合并，注意顺序
  }
  virtual Node_CItr node_begin()const=0;
  virtual Node_CItr node_end()const=0;
};
```

为了方便操作，从 `__gnu_pbds::tree` 继承过来一个结构体，直接在里面定义操作：

```cpp
struct rbt:tree<S,null_type,less<S>,rb_tree_tag,op>{
  inline void update(iterator x){
    update_to_top(x.m_p_nd,(node_update*)this);
  }
  // 修改一个结点的信息不会自动更新可能被影响到的结点
  // 需要一路手动更新上去
  inline void ist(int x){
    auto it=lower_bound(S(x,0,0,0));
    if(it==end()||it->key!=x)insert(S(x,1,x,0));
    else{
      get<0>(it->c)++;
      if(get<1>(it->c)>get<2>(it->c))get<2>(it->c)+=x;
      else get<1>(it->c)+=x;
      // 插入了多个 x
      update(it);
    }
  }
  inline ll all_prod(){
    return get<1>(node_begin().get_metadata());
    // 查询全局的答案
  }
}t;
```

以下给出完整代码供参考。

参考代码（GNU C++ 17）：

```cpp
#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef tuple<int,ll,ll> tpi;
const int M=1e9;
struct S{
  int key; mutable tpi c;
  S(int key=0,int x=0,ll y=0,ll z=0):key(key),c(x,y,z){}
  bool operator <(const S &b)const{return key<b.key;}
};
inline tpi operator +(const tpi &x,const tpi &y){
  return make_tuple(get<0>(x)+get<0>(y),
    get<1>(x)+(get<0>(x)&1?get<2>(y):get<1>(y)),
    get<2>(x)+(get<0>(x)&1?get<1>(y):get<2>(y)));
}
template<class Node_CItr,class Node_Itr,class Cmp_Fn,class _Alloc> struct op{
  typedef tpi metadata_type;
  void operator()(Node_Itr it,Node_CItr end_it){
    Node_Itr itl=it.get_l_child();
    Node_Itr itr=it.get_r_child();
    tpi l,r;
    if(itl!=end_it)l=itl.get_metadata();
    if(itr!=end_it)r=itr.get_metadata();
    const_cast<tpi&>(it.get_metadata())=l+(*it)->c+r;
  }
  virtual Node_CItr node_begin()const=0;
  virtual Node_CItr node_end()const=0;
};
struct rbt:tree<S,null_type,less<S>,rb_tree_tag,op>{
  inline void update(iterator x){
    update_to_top(x.m_p_nd,(node_update*)this);
  }
  inline void ist(int x){
    auto it=lower_bound(S(x,0,0,0));
    if(it==end()||it->key!=x)insert(S(x,1,x,0));
    else{
      get<0>(it->c)++;
      if(get<1>(it->c)>get<2>(it->c))get<2>(it->c)+=x;
      else get<1>(it->c)+=x;
      update(it);
    }
  }
  inline ll all_prod(){
    return get<1>(node_begin().get_metadata());
  }
}t;
int main(){
  ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int q; ll l=0; cin>>q;
  for(int i=0;i<q;i++){
    ll y; cin>>y;
    (y+=l)%=M,y++,t.ist(y);
    cout<<(l=t.all_prod())<<'\n';
  }
  return 0;
}
```

---

## 作者：zhangjiting (赞：2)

## 题意

插入一个数，查询从小到大排名为奇数的数的和，强制在线。

## 思路

建立两棵平衡树 $T_1,T_0$，分别记录排名为奇数的数和排名为偶数的数。

插入 $x$ 时，两棵树分别按 $x$ 分裂，得到 $T_{1,0},T_{1,1}$ 和 $T_{0,0},T_{0,1}$ 四棵树。

如果 $x$ 当前排名为偶数，就合并 $T_{0,0},x,T_{1,1}$ 为 $T_0$，然后合并 $T_{1,0},T_{0,1}$ 为 $T_1$，很好理解。

奇数时类似。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cerr<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=3e5+5;
int q;
mt19937_64 rnd(time(0));
struct node{
    int ch[2];
    int key,siz;
    int sum,val;
}tree[N];
#define ls(x) tree[x].ch[0]
#define rs(x) tree[x].ch[1]
int tot,root1,root0;
void pushup(int x){
    tree[x].siz=tree[ls(x)].siz+tree[rs(x)].siz+1;
    tree[x].sum=tree[ls(x)].sum+tree[rs(x)].sum+tree[x].val; 
}
int new_node(int x){
    ++tot;
    tree[tot].key=rnd();
    tree[tot].val=x;
    tree[tot].siz=1;
    tree[tot].sum=x;
    ls(tot)=rs(tot)=0;
    return tot;
}
void split(int p,int k,int &x,int &y){
    if(!p) return x=y=0,void();
    if(tree[p].val<=k) x=p,split(rs(p),k,rs(x),y);
    else y=p,split(ls(p),k,x,ls(y));
    pushup(p);
}
int merge(int x,int y){
    if(!x||!y) return x|y;
    if(tree[x].key>tree[y].key){
        rs(x)=merge(rs(x),y);
        return pushup(x),x;
    }
    else{
        ls(y)=merge(x,ls(y));
        return pushup(y),y;
    } 
}
signed main(){
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    IOS;
    cin>>q;
    for(int _=1,lastans=0,x;_<=q;_++){
        cin>>x;
        x=(x+lastans)%1000000000+1;
        int a1,b1,a0,b0;
        split(root1,x,a1,b1);
        split(root0,x,a0,b0);
        if((tree[a1].siz+tree[a0].siz)&1){
            root0=merge(a0,merge(new_node(x),b1));
            root1=merge(a1,b0);
        }
        else{
            root1=merge(a1,merge(new_node(x),b0));
            root0=merge(a0,b1);
        }
        lastans=tree[root1].sum;
        cout<<lastans<<endl;
    }
    return 0;
}
```

---

## 作者：zyn0309 (赞：2)

# [ABC403G] Odd Position Sum Query
[题目传送门](https://atcoder.jp/contests/abc403/tasks/abc403_g)

## 思路
用一棵平衡树维护当前已经插入的数的有序序列，平衡树上的每个结点都要维护所在的平衡树子树的奇数位置和偶数位置的权值和。

对于一个结点 $u$，其左右儿子分别为 $ls$ 和 $rs$。可以根据左儿子子树大小的奇偶性来分类讨论维护奇数位置和偶数位置的权值和。

下图中黄色代表属于奇数位置，紫色代表属于偶数位置。
![](https://cdn.luogu.com.cn/upload/image_hosting/ly1fx0ji.png)
所以此时 $u$ 的奇数和等于左儿子奇数和加右儿子奇数和，偶数和等于左儿子偶数和加右儿子偶数和加 $u$ 自身的权值。

![](https://cdn.luogu.com.cn/upload/image_hosting/hruuyxz3.png)
所以此时 $u$ 的奇数和等于左儿子奇数和加右儿子偶数和加 $u$ 自身的权值，偶数和等于左儿子偶数和加右儿子奇数和。

最后在每次插入后输出平衡树根结点的奇数和即可。
## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
struct tree{
	int lson,rson,siz,val,pri,ji,ou;
}t[N];
int tot,n,root;
mt19937 rnd(time(0));
inline int New(int x){
	++tot;
	t[tot].siz=1;
	t[tot].val=t[tot].ji=x;
	t[tot].pri=rnd();
	return tot;
}
inline void push_up(int u){
	t[u].siz=t[t[u].lson].siz+t[t[u].rson].siz+1;
	if(t[t[u].lson].siz&1){
	  t[u].ji=t[t[u].lson].ji+t[t[u].rson].ji;
	  t[u].ou=t[t[u].lson].ou+t[u].val+t[t[u].rson].ou;
	}
	else{
	  t[u].ji=t[t[u].lson].ji+t[u].val+t[t[u].rson].ou;
	  t[u].ou=t[t[u].lson].ou+t[t[u].rson].ji;
	}
} 
inline void split(int u,int x,int &l,int &r){
	if(!u){
	  l=r=0;
	  return;
	}
	if(t[u].val<=x){
	  l=u;
	  split(t[u].rson,x,t[u].rson,r);
	  push_up(u);
	}
	else{
	  r=u;
	  split(t[u].lson,x,l,t[u].lson);
	  push_up(u);
	}
}
inline int merge(int l,int r){
	if(!l||!r)return l+r;
	if(t[l].pri>t[r].pri){
	  t[l].rson=merge(t[l].rson,r);
	  push_up(l);
	  return l;
	}
	else{
	  t[r].lson=merge(l,t[r].lson);
	  push_up(r);
	  return r;
	}
}
inline int insert(int x){
	int L,R;
	split(root,x,L,R);
	return merge(merge(L,New(x)),R);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int x,last=0;
	cin>>n;
	for(int i=1;i<=n;++i){
	  cin>>x;
	  x=(x+last)%((int)1e9)+1;
	  root=insert(x);
	  cout<<(last=t[root].ji)<<"\n";
	}
	return 0;
}
```

---

## 作者：yhy2024 (赞：1)

题意：给你一个可重集，支持插入，查询所以排名为奇数的数的和。强制在线。

考虑在值域上开线段树。每个节点维护 $ou_k$ 节点 $k$ 所有排名为偶数的数的和，$ji_k$ 节点 $k$ 所有排名为奇数的数的和，$siz_k$ 节点 $k$ 有多少个数。

考虑区间如何合并。显然的，根据左儿子的 $siz$ 的奇偶性分类讨论。

当 $siz$ 为奇数时，右儿子的 $ou$，$ji$ 交换。

当 $siz$ 为偶数时，右儿子的 $ou$，$ji$ 不变。

注意到值域非常大，动态开点即可。


```cpp
#include<bits/stdc++.h>
#define N 2000005
#define rd read()
#define int long long
using namespace std;
int n,m,x,las,rt,tot,q;
const int V=1e9;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9')
		x=x*10+ch-'0',ch=getchar();
	return x*f;
}
struct Node{
	int ou,ji,siz;
	Node operator + (const Node &o) const{
		Node res;
		res.siz=siz+o.siz;
		if(siz&1) res.ou=ou+o.ji,res.ji=ji+o.ou;
		else res.ou=ou+o.ou,res.ji=ji+o.ji;
		return res;
	}
};
struct{
	Node v;
	int ls,rs;
}tr[N<<2];
inline void pushup(int k){tr[k].v=tr[tr[k].ls].v+tr[tr[k].rs].v;}
inline void ins(int &k,int l,int r,int v){
	if(!k) k=++tot;
	if(l==r){
		tr[k].v.siz++;	
		if(tr[k].v.siz&1) tr[k].v.ji+=v;
		else tr[k].v.ou+=v;
		return;
	}
	int mid=l+r>>1;
	if(v<=mid) ins(tr[k].ls,l,mid,v);
	else ins(tr[k].rs,mid+1,r,v);
	pushup(k);
}
signed main(){
	cout.tie(0);
	q=rd;
	for(int i=1;i<=q;i++){
		x=(rd+las)%V+1;
		ins(rt,1,V,x);
		cout<<(las=tr[rt].v.ji)<<'\n';
	}
	return 0;
} 
```

---

## 作者：CJ_Fu (赞：1)

考虑对下标分奇偶建两棵平衡树 $T_1,T_2$（就是当前操作前奇数下标的放在第一棵树，偶数在第二棵），然后对于插入一个 $x$，在两棵树上查 $x$ 的排名 $rnk_1(x),rnk_2(x)$，可以得到 $x$ 在所有数中的排名 $rk=rnk_1(x)+rnk_2(x)-1$，根据 $rk$ 的奇偶性即可确定 $x$ 应该放到哪棵树上。插入 $x$ 只会对下标比它大的数产生影响，也就是比它大的那些数的下标集体加一（也就是奇偶性互换）。

所以按值 $x$ 分裂两棵树为四棵树 $T_1\to a,b,T_2\to c,d$，然后把 $d$ 接到 $a$ 上，$b$ 接到 $c$ 上即可完成互换（$T_1\leftarrow a+d,T_2\leftarrow c+b$）。最后把 $x$ 插到对应的树上去即可，查询的答案即为 $T_1$ 的所有元素的和。用 FHQ 实现，非常直观好写，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e6+7;
int n;
#define ls tree[now].l
#define rs tree[now].r
int root[2],cnt;
struct node{
    int val,sum;
    int l,r,siz,wei;
}tree[maxn];
void pushup(int now){
    tree[now].siz=tree[ls].siz+tree[rs].siz+1;
    tree[now].sum=tree[ls].sum+tree[rs].sum+tree[now].val;
    // 维护子树和
}
int create(int val){
    tree[++cnt]={val,val,0,0,1,rand()};
    return cnt;
}
void split(int now,int val,int &rt1,int &rt2){
    if(!now){ rt1=rt2=0; return; }
    if(tree[now].val<=val){
        rt1=now;
        split(rs,val,rs,rt2);
    }else{
        rt2=now;
        split(ls,val,rt1,ls);
    }
    pushup(now);
}
int merge(int rt1,int rt2){
    if(!rt1||!rt2) return rt1+rt2;
    if(tree[rt1].wei>tree[rt2].wei){
        tree[rt1].r=merge(tree[rt1].r,rt2);
        pushup(rt1);
        return rt1;
    }else{
        tree[rt2].l=merge(rt1,tree[rt2].l);
        pushup(rt2);
        return rt2;
    }
}
void ins(int val,int wt){
    int x,y;
    split(root[wt],val-1,x,y);
    root[wt]=merge(merge(x,create(val)),y);
}
int rnk(int val,int wt){
    int x,y,rks;
    split(root[wt],val-1,x,y);
    rks=tree[x].siz+1;
    root[wt]=merge(x,y);
    return rks;
} // 板子
void swp(int x){ // 交换
    int a,b,c,d;
    split(root[0],x-1,a,b);
    split(root[1],x-1,c,d);
    root[0]=merge(a,d);
    root[1]=merge(c,b);
}
signed main(){
    cin>>n;
    int z=0; 
    for(int i=1,y,x;i<=n;i++){
        cin>>y; x=(y+z)%1000000000+1;
        int pos=rnk(x,0)+rnk(x,1)-1;
        swp(x); ins(x,pos&1);
        cout<<tree[root[1]].sum<<'\n';
        z=tree[root[1]].sum;
    }
    return 0;
}
```

---

## 作者：incra (赞：1)

### Sol
平衡树做法，代码很好写。

考虑给每个节点维护字数大小，下标为奇数的和，下标为偶数的和，分别记作 $s,odd,even$。

考虑如何再平衡树上维护信息，记左节点为 $ls$，记右节点为 $rs$，记当前的点为 $u$ 且权值为 $key_u$。
1. 如果 $s_{ls}$ 是奇数，那么 $odd_u\gets odd_l+even_r,even_u\gets even_l+key_u+odd_r$。

1. 如果 $s_{ls}$ 是奇数，那么 $odd_u\gets odd_l+key_u+even_r,even_u\gets even_l+odd_r$。

然后就做完了。
### Code
代码中除了 `push_up` 都是贺的。/mgx

[Link](https://atcoder.jp/contests/abc403/submissions/65286179)。

---

## 作者：Eterna (赞：1)

赛时看到已经没有时间写了。

题意大概就是每次插入一个数，然后查询排名是奇数的数的和。

有两种做法。

第一种是我赛时的想法。我们直接维护有序的 $a$，及其奇数下标和偶数下标的数的和。块状链表，插入一个数直接单块重构一下，其他块不用管。然后查询的话，就是一边算前面的数的数量的奇偶性，就可以考虑当前块查奇数还是查偶数了。

但是 $O(n \sqrt{n})$ 不一定能过。可以换成平衡树，每次插入按值分裂，然后 pushup 一下，pushup 讨论左边的区间长度奇偶性即可。所以可以 $O(n \log n)$。[提交记录](https://atcoder.jp/contests/abc403/submissions/65306889)。

第二种是官方题解的想法。对值域开线段树，然后直接就可以和平衡树做法一样合并区间。但是值域太大，直接开是不行的，于是动态开点卡空间。然后 $O(n \log m)$ 跑得没有平衡树快。[提交记录](https://atcoder.jp/contests/abc403/submissions/65306342)。

---

## 作者：ty_mxzhn (赞：0)

嘟嘟嘟。

考虑权值线段树，修改直接修，查询的时候考虑如何合并二区间答案。

不难发现右半区间的答案只和左半区间出现次数的奇偶性有关，记录 $r_{i}$ 表示这个区间左边出现次数对 $2$ 取模为 $i$，这个区间的贡献。pushup 是简单的。

好写。

---

