# [HBCPC2024] Enchanted

## 题目描述

在《Minecraft》中，变得更强的一种方式是让盔甲和武器附魔。附魔书在其中扮演了重要角色。

![](https://cdn.luogu.com.cn/upload/image_hosting/pc5cf4e8.png)

附魔书最重要的属性是其等级。等级越高，书越好。我们可以将两本相同等级 $l$ 的书合并成一本新书（原来的两本书将消失）。新书的等级为 $l+1$，合并的费用为 $2^{l+1}$。

现在，Steve 有 $n$ 本编号从 $1$ 到 $n$ 的附魔书。最初，第 $i$ 本书的等级为 $a_i$。Steve 请你帮助他完成以下四种操作。

1. 给定两个整数 $l,r(1 \le l \le r \le n)$，计算通过合并编号从 $l$ 到 $r$ 的书能达到的最大等级。
2. 给定三个整数 $l,r(1 \le l \le r \le n)$ 和 $k$，然后按照以下步骤操作：
步骤 $1$：Steve 合并编号从 $l$ 到 $r$ 的所有书，直到不存在两本等级相同的书。
步骤 $2$：Steve 将一个新书等级为 $k$ 的书加入步骤 $1$ 中得到的书中。
步骤 $3$：Steve 需要合并步骤 $2$ 中得到的书，并希望最大化合并次数。
请计算并输出步骤 $3$ 中的总费用对 $10^9+7$ 取模的结果。
\textbf{注意，计算后，序列会恢复。也就是说，此操作实际上不会改变序列。}

3. 给定两个整数 $pos,k$，Steve 将编号为 $pos$ 的书的等级改为 $k$。

4. 给定一个整数 $t$，Steve 将序列恢复到第 $t$ 次操作后的状态。如果 $t=0$，则 Steve 将序列恢复到初始状态。

## 说明/提示

函数 `max` 表示参数中的最大值。函数 `min` 表示参数中的最小值。

在例子 1 中，初始书为 $[1,2,3,1,2,3]$。三个操作的范围分别是 $[4,4]$，$[1,3]$ 和 $[4,5]$。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
6 3 2 1 3```

### 输出

```
1
3
2```

## 样例 #2

### 输入

```
10 15 5 4 7```

### 输出

```
0
9
9
0
64
0
0```

# 题解

## 作者：Akiyama_mzk (赞：5)

[戳](https://www.luogu.com.cn/article/kudyreke)

# 题意

给定一个值域为 $[1,30]$ 的序列，合并操作定义是使用两个相同的元素（设为 $x$）合并出一个值为 $x+1$ 的元素，代价为 $2^{x+1}$，维护以下四种操作。

- 操作 $1$：求出区间 $[l,r]$ 内的元素通过合并能得到的最大元素。

- 操作 $2$：将区间 $[l,r]$ 之间的元素合并，直至任意元素互不相同，然后再加入一个值为 $k$ 的元素，继续合并直至任意元素互不相同，求出加新元素后所有合并的代价之和。

- 操作 $3$：将第 $x$ 个数的值改为 $val$。

- 操作 $4$：回到第 $t$ 次操作。

# 算法

注意到 $[1,30]$ 的值域，想到使用二进制维护合并，合并操作就像二进制加法内的进位，少了两个相同的元素，多出另一个元素。

因此，区间合并后的最大的元素就是区间和的最大二进制位，其他操作也可以照样用二进制维护。

对于操作 $4$ 的回退和操作 $3$ 的修改操作，我们使用可持久化线段树来维护。

但什么是可持久化？

**下面内容请会可持久化线段树的大佬跳过**。

我们需要先了解 [P3919 【模板】可持久化线段树 1（可持久化数组）](https://www.luogu.com.cn/problem/P3919)。

题面为在某个历史版本上修改某一个位置上的值，并访问某个历史版本上的某一位置的值。

可持久化线段树的基本思想就是只对进行修改的结点进行复制，以减少空间的消耗，让我们不必复制每个版本所有节点。

![](https://cdn.luogu.com.cn/upload/image_hosting/3s9xk202.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

易得，每次添加的节点数为 $\log(n)$ 个，可持久化线段树有很多根，对于每一个根都可以构成一棵完整的线段树。

所以我们知道，可持久化线段树只会对部分节点进行复制，我们每一次想询问一个版本的线段树，就可以在那个版本的根构成的线段树中询问。

我们直接开一块内存池存新节点。编号为此时总节点数个数 $+1$。开结构体存节点编号。根要另外开个数组存。

注意，可持久化线段树不能用 $x\times 2$，$x\times 2+1$ 来表示左右儿子，而是应该动态开点，并保存每个节点的左右儿子编号。

代码如下。

```cpp
int n,m,dfn;
int root[1000001],a[1000001];
struct president_tree{
	struct node{
		int lson,rson,val;
	}t[25000001];
	void build(int &x,int l,int r){
		x=++dfn;
		if(l==r){
			t[x].val=a[l];
			return;
		}
		int mid=(l+r)>>1;
		build(t[x].lson,l,mid);
		build(t[x].rson,mid+1,r);
	}
	void update(int idx,int &id,int l,int r,int x,int d){
		id=++dfn;
		t[id]=t[idx];
		if(l==r){
			t[id].val=d;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			update(t[idx].lson,t[id].lson,l,mid,x,d);	
		}
		else{
			update(t[idx].rson,t[id].rson,mid+1,r,x,d);
		}
	}
	int query(int x,int l,int r,int pos){
		if(l==r){
			return t[x].val;
		}
		int mid=(l+r)>>1;
		if(pos<=mid){
			return query(t[x].lson,l,mid,pos);
		}
		else{
			return query(t[x].rson,mid+1,r,pos);
		}
	}
}tree;
```

# 代码与评测记录

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
inline long long read(){
	long long x=0;
	short f=1;
	char c=getchar();
	while(c>57||c<48){
		if(c==45) f=-1;
		c=getchar();
	}
	while(c<58&&c>47){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline void write(long long x){
	if(x<0ll) putchar(45),x=~x+1;
	if(x>9ll) write(x/10);
	putchar(x%10|48);
}
int n,m,dfn,a,p,q;
int root[4000001],cost[4000001];
struct president_tree{
	struct node{
		int lson,rson,val;
	}t[64000001];
	#define lson(x) t[x].lson
	#define rson(x) t[x].rson
	void push_up(int x){
		t[x].val=t[lson(x)].val+t[rson(x)].val;
	} 
	void build(int &x,int l,int r){
		x=++dfn;
		if(l==r){
			t[x].val=cost[l];
			return;
		}
		int mid=(l+r)>>1;
		build(t[x].lson,l,mid);
		build(t[x].rson,mid+1,r);
		push_up(x);
		return;
	}
	void update(int idx,int &id,int l,int r,int x,int d){
		id=++dfn;
		t[id]=t[idx];
		if(l==r){
			t[id].val=d;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid){
			update(t[idx].lson,t[id].lson,l,mid,x,d);	
		}
		else{
			update(t[idx].rson,t[id].rson,mid+1,r,x,d);
		}
		push_up(id);
	}
	int query(int x,int l,int r,int ll,int rr){
		if(ll<=l&&r<=rr){
			return t[x].val;
		}
		int mid=(l+r)>>1;
		int res=0;
		if(ll<=mid){
			res+=query(t[x].lson,l,mid,ll,rr);
		}
		if(rr>=mid+1){
			res+=query(t[x].rson,mid+1,r,ll,rr);
		}
		return res;
	}
}tree;
const int mod=1e9+7;
int cal(){
	a=(7ll*a+13)%19260817;
	return (a+19260817)%19260817;
}
signed main(){
	n=read();
	m=read();
	a=read();
	p=read();
	q=read();
	for(int i=1;i<=n;i++){
		cost[i]=cal()%q+1;
		cost[i]=(1ll<<cost[i]);
	}
	tree.build(root[0],1,n);
	for(int i=1;i<=m;i++){
		root[i]=root[i-1];
		int op=cal()%p+1;
		if(op==1){
			int l=cal()%n+1;
			int r=cal()%n+1;
			if(r<l){
				swap(l,r);
			}
			long long ans=tree.query(root[i],1,n,l,r);
			write(__lg(ans));
			printf("\n");
		}
		if(op==2){
			int l=cal()%n+1;
			int r=cal()%n+1;
			if(r<l){
				swap(l,r);
			}
			int k=cal()%q+1;
			int res=tree.query(root[i],1,n,l,r);
			int ans=0;
			for(int j=0;res;j++){
				if(j>=k){
					if(res&1){
						ans+=(1ll<<(j+1))%mod;
						ans%=mod;
					}
					else{
						break;
					}
				}
				res>>=1;
			}
			write(ans);
			printf("\n");
		}
		if(op==3){
			int pos=cal()%n+1;
			int k=cal()%q+1;
			k=1ll<<k;
			tree.update(root[i-1],root[i],1,n,pos,k);
		}
		if(op==4){
			int loc=cal()%i;
			root[i]=root[loc];
		}
	}
	return 0;
}
```

[record](https://www.luogu.com.cn/record/172189867)

---

## 作者：封禁用户 (赞：0)

![](https://cdn.luogu.com.cn/upload/image_hosting/pc5cf4e8.png)

### 题意
- 给你一个附魔书序列 $a$，支持以下操作：
- 求合并 $[l,r]$ 所有附魔书可以得到的最高等级(实际上不做任何修改)；
- 合并 $[l,r]$ 所有附魔书，再与等级为 $k$ 的附魔书合并，求附魔花费（实际上不做任何修改）；
- 将 $a_x$ 的等级修改为 $k$；
- 返回第 $t$ 次操作之后。

范围：$a[i] \le30,n,m \le10^6$。

附魔书的合并很像二进制相加，不妨设附魔书 $i$ 的权值为 $a^{a[i]-1}$，则合并相当于加法。则原操作为：

- 求区间和的二进制最高位。直接维护区间和即可；
- 求区间和加上 $k$ 与原来相比的二进制变化位数和。设区间和为 $t$，则答案为 $2 \times((t+k) \oplus t  \oplus k)$。
- 其余操作可持久化即可。

时间复杂度 $O(n \log n)$。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define lc tree[pos].ls
#define rc tree[pos].rs
using namespace std;
const int maxn=1e6+3;
const int mod1=19260817;
const int mod2=1e9+7;
struct T{
	int sum,ls,rs;
}tree[maxn<<5];
int tim,cnt;
int n,m,a[maxn],A,P,Q;
int root[maxn];
int rnd(){
    return A=(7*A+13)%mod1;
}
void pushup(int pos){
    tree[pos].sum=tree[lc].sum+tree[rc].sum;
}
void update(int &pos,int l,int r){
	if(!pos) pos=++cnt;
	if(l==r){
		tree[pos].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	update(lc,l,mid);
	update(rc,mid+1,r);
    pushup(pos);
}
void modify(int rt,int &pos,int l,int r,int x,int v){
    if(!pos) pos=++cnt;      // 新建节点，加 & 保证不会访问到空节点并直接存在儿子中
    if(l==r){
        tree[pos].sum=v;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid){
        tree[pos].ls=++cnt;    // 新建左儿子
        tree[pos].rs=tree[rt].rs;
        tree[lc]=tree[tree[rt].ls];// 继承右儿子的所有信息
        modify(tree[rt].ls,lc,l,mid,x,v);
    }else{
        tree[pos].rs=++cnt;    // 同理
        tree[pos].ls=tree[rt].ls;
        tree[rc]=tree[tree[rt].rs];
        modify(tree[rt].rs,rc,mid+1,r,x,v);
    }
    pushup(pos);
}
int query(int pos,int l,int r,int L,int R){
	if(L<=l&&r<=R) return tree[pos].sum;
	int mid=(l+r)>>1,sum=0;
	if(L<=mid) sum+=query(lc,l,mid,L,R);
	if(mid+1<=R) sum+=query(rc,mid+1,r,L,R);
    return sum;
}
int highbit(int x){
    int top=0;
    while(x){
        x/=2;
        top++;
    }
    return top;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>m>>A>>P>>Q; 
	for(int i=1;i<=n;i++){
		a[i]=1<<(rnd()%Q);
	}
	update(root[0],1,n);
	for(int i=1,op,l,r,L,R,k;i<=m;i++){
		op=rnd()%P+1;
		if(op==1){
			L=rnd()%n+1;
            R=rnd()%n+1;
            l=min(L,R);
            r=max(L,R);
            root[i]=root[i-1];
            int t=query(root[i],1,n,l,r);
            cout<<highbit(t)%mod2<<'\n';
		}else if(op==2){
			L=rnd()%n+1;
            R=rnd()%n+1;
            l=min(L,R);
            r=max(L,R);
            k=1<<(rnd()%Q);
            root[i]=root[i-1];
			int t=query(root[i],1,n,l,r);
            cout<<((t+k)^t^k)*2%mod2<<'\n';
		}else if(op==3){
			L=rnd()%n+1;
            k=1<<(rnd()%Q);
            modify(root[i-1],root[i],1,n,L,k);
        }else{
            k=rnd()%i;
            root[i]=root[k];
        }
	}
	return 0;
}
```

---

## 作者：是青白呀 (赞：0)

首先合并书本的过程等价于一个二进制加法，一本权值为 $k$ 的书的权值是 $2^k$，最终合并的书的等级就是所有权值加和后值为 $1$ 位置的位数。由这个过程不难发现，合并的结果是唯一确定的。

因此，操作 $1$ 就是区间求和后找和值的最高位；操作 $2$ 就是区间求和后找和值中第 $k$ 位往上数的连续位数。都只需要求得区间和，即可轻松解决。

对于回退到某个操作之后的操作，我们考虑离线所有操作，建立操作树，每个版本对应一个节点，其父亲就是其来源的版本。我们 dfs 整棵树，使用树状数组维护区间和，仅需在进行了操作 $3$ 的节点做修改，回溯时回退即可。

时间复杂度 $O(m\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define repp(i,j,k) for(int i=j;i>=k;i--)
#define ls(x) (x<<1)
#define rs(x) ((x<<1)|1)
#define mp make_pair
#define sec second
#define fir first
#define pii pair<int,int>
#define lowbit(i) i&-i
#define int long long
#define qingbai 666
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N=1e6+5,M=6,S=(1<<20)+5,inf=(ll)8e18+7,mo=1e9+7;
const double eps=1e-8;
void read(int &p){
	int x=0,w=1;
	char ch=0;
	while(!isdigit(ch)){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	p=x*w;
}
int n,m,tmp,p,q;
int rnd(){
    tmp=(7*tmp+13)%19260817;
    return tmp;
}
int a[N];
struct BIT{
    int t[4*N];
    void add(int x,int v){
        for(int i=x;i<=n;i+=lowbit(i))
            t[i]+=v;
    }
    int query(int x){
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res+=t[i];
        return res;
    }
}T;
struct oper{
    int op,l,r,k;//pos/t:l
}t[N];
int fa[N];
vector<int>e[N];
int ans[N];
//离线操作树+树状数组
void dfs(int x){
    int prev;
    if(t[x].op==0){
        rep(i,1,n)
            T.add(i,1<<(a[i]-1));
    }
    if(t[x].op==1){
        int le=t[x].l,ri=t[x].r;
        int res=T.query(ri)-T.query(le-1);
        ans[x]=floor(log2(res))+1;
    }
    if(t[x].op==2){
        int le=t[x].l,ri=t[x].r,k=t[x].k;
        int res=T.query(ri)-T.query(le-1);
        res>>=k-1;
        ans[x]=0;
        int nwv=1ll<<(k+1);
        while((res&1))
            ans[x]+=nwv,nwv<<=1,res>>=1,ans[x]%=mo;
    }
    if(t[x].op==3){
        int npos=t[x].l,nwv=(1<<(t[x].k-1));
        prev=a[npos];
        T.add(npos,nwv-(1<<(a[npos]-1)));
        a[npos]=t[x].k;
    }
    for(auto j:e[x])
        dfs(j);
    if(t[x].op==3){
        int npos=t[x].l;
        T.add(npos,(1<<(prev-1))-(1<<(a[npos]-1)));
        a[npos]=prev;
    }
}
signed main(){
    read(n),read(m),read(tmp),read(p),read(q);
    rep(i,1,n)
        a[i]=rnd()%q+1;
    rep(i,1,m){
        ans[i]=-1;
        int op=rnd()%p+1;
        if(op==1){
            int l=rnd()%n+1,r=rnd()%n+1;
            if(l>r)swap(l,r);
            t[i]=(oper){op,l,r,0};
        }
        if(op==2){
            int l=rnd()%n+1,r=rnd()%n+1;
            if(l>r)swap(l,r);
            int k=rnd()%q+1;
            t[i]=(oper){op,l,r,k};
        }
        if(op==3){
            int pos=rnd()%n+1,k=rnd()%q+1;
            t[i]=(oper){op,pos,pos,k};
        }
        if(op==4){
            int ver=rnd()%i;
            t[i]=(oper){op,ver,ver,0};
        }
    }
    rep(i,1,m){
        if(t[i].op==4)fa[i]=t[i].l;
        else fa[i]=i-1;
    }
    rep(i,1,m)
        e[fa[i]].push_back(i);
    dfs(0);
    rep(i,1,m)
        if(ans[i]!=-1)printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：_jimmywang_ (赞：0)

### P10863 [HBCPC2024] Enchanted

考虑储存 对一个区间使劲合成完后 的状态。

观察到 $q$ 非常小，同时你就算使劲合成最终等级也就最多提升 $O(\log n)$ 次，最终态每个等级的书最多一本。因此我们使用状压来储存一个区间的最终状态。

数量级大概在 $2^{50}$ 左右，存的下。

接下来考虑合并两个区间的状态（记作 $x,y$）。先用二进制写出，~~适当手模~~后发现合成操作等价于加法中的进位。

因此最终态就是 $x+y$。真神奇！

现在抛开操作 4 不谈，我们来看看前面的操作怎么解决。

- 操作 1：

  trival。因为我们已经能处理区间状态合并，~~理所当然~~可以上线段树。那么直接查询该区间最终态，并枚举判断最高位即可。复杂度 $O(\log n +q)$（或者是不是有什么 `__builtin` 的操作？）

- 操作 2：

  同理，先查询该区间的最终态并暴力合并新书 $k$。复杂度 $O(\log n +q)$

- 操作 3：

  这不直接单点修改。复杂度 $O(\log n)$。

现在来考虑操作 4。

数据结构大师一定会大喊可持久化即可，这是因为你主席树学傻了。

我们直接离线建出操作树，不同节点表示不同状态（因此操作 4 时会回退到树上一个已有的节点上）。父亲到儿子连边相当于单点修改，询问挂在点上。

接下来对这棵树进行一次 dfs，递归时修改，回溯时撤销即可。

---

