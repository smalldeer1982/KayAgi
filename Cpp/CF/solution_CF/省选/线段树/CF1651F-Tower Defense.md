# Tower Defense

## 题目描述

Monocarp is playing a tower defense game. A level in the game can be represented as an OX axis, where each lattice point from $ 1 $ to $ n $ contains a tower in it.

The tower in the $ i $ -th point has $ c_i $ mana capacity and $ r_i $ mana regeneration rate. In the beginning, before the $ 0 $ -th second, each tower has full mana. If, at the end of some second, the $ i $ -th tower has $ x $ mana, then it becomes $ \mathit{min}(x + r_i, c_i) $ mana for the next second.

There are $ q $ monsters spawning on a level. The $ j $ -th monster spawns at point $ 1 $ at the beginning of $ t_j $ -th second, and it has $ h_j $ health. Every monster is moving $ 1 $ point per second in the direction of increasing coordinate.

When a monster passes the tower, the tower deals $ \mathit{min}(H, M) $ damage to it, where $ H $ is the current health of the monster and $ M $ is the current mana amount of the tower. This amount gets subtracted from both monster's health and tower's mana.

Unfortunately, sometimes some monsters can pass all $ n $ towers and remain alive. Monocarp wants to know what will be the total health of the monsters after they pass all towers.

## 样例 #1

### 输入

```
3
5 1
7 4
4 2
4
0 14
1 10
3 16
10 16```

### 输出

```
4```

## 样例 #2

### 输入

```
5
2 1
4 1
5 4
7 5
8 3
9
1 21
2 18
3 14
4 24
5 8
6 25
7 19
8 24
9 24```

### 输出

```
40```

# 题解

## 作者：yzy1 (赞：12)

## 题目大意

- 数轴上有 $n$ 个塔，第 $i$ 个塔能量上限 $c_i$，每秒回复 $r_i$ 点能量，初始所有塔能量全是满的。
- 同时有 $m$ 个怪，第 $i$ 个会在 $t_i$ 秒刷出，血量 $h_i$。第 $i$ 个怪会在第 $t_i+j-1$ 秒被第 $j$ 个塔攻击。攻击时，塔的能量和怪的血量同时减去两者中的较小值。
- 输出所有怪全都走过一遍后所有怪血量之和。

## 简要做法

- 我们发现这个 $a_i \gets \min (a_i + T b_i,c_i)$ 的形式和 CF453E 有点像啊？

考虑对塔分块。我们发现一个怪经过一块内的塔只有两种情况：

1. 块内所有塔把怪打一遍后怪还有血，这时相当于块内塔的能量被清零了。
2. 怪被其中一个塔打成血量为零，此时这个怪就不会对后面的块造成贡献了。处理后面的块的时候直接把这个怪 continue 掉即可。

可以发现，由于一个怪最多只会被打成空血一次，所以第二种情况最多只会出现 $O(m)$ 次。

考虑对于每一块维护一个推平 tag 和这个块上次被操作的时间戳。预处理出每个块被清零后 $k$ 秒来了一个怪时能对怪打出多少伤害。对于每个怪依次处理每个块：

- 若这个怪能被块内的塔打成空血，直接暴力做，然后撤销块内的推平标记。
- 否则，若块内没有推平标记，同样暴力做，然后打上一个推平标记。
- 否则，直接把怪的血量减去预处理出来的值，推平标记保持不变。

预处理的方法可以参考我的[这篇题解](/blog/yzy1/solution-cf453e)。

但是我们发现，这道题的 $n \le 2\times 10^5$，而我们的空间复杂度是 $O(n\sqrt n)$，我们根本开不下这么大的数组！

考虑把所有询问离线，然后一块一块的做，每块统一处理所有的怪，这样的话就只需要保存当前的块的预处理值和标记即可。空间复杂度下降为 $O(n)$。

至此，我们以 $O(n\sqrt n)$ 的时间复杂度，$O(n)$ 的空间复杂度解决了此题。

[代码参考](https://codeforces.com/contest/1651/submission/149206879)

---

## 作者：panyf (赞：10)

容易发现每个怪物一定是让一段前缀的炮塔弹药变为 $0$，让下一个炮塔的弹药减少到某个值，其余炮塔弹药不变。

也就是说，每个怪物只会让炮塔增加常数段。这里的“段”有两种，一种是 $[l,r]$ 内的炮塔在某一个怪物经过后弹药全部变为 $0$，另一种是 $l=r$ 并且炮塔 $l$ 在某一个怪物经过后弹药变为某个值。

从前到后枚举怪物。考虑用一个栈存下每一段的端点和对应的怪物。新增一个怪物时，只需要从前到后暴力枚举每一段，判断怪物是否会在这一段死亡。如果是，那么二分死亡的位置；否则继续考虑下一段。然后将枚举的这些段合并成一段。因为每次只会增加常数段，所以总段数是 $n+q$ 级别的，复杂度均摊下来就是对的。

$l=r$ 的部分很好处理。考虑 $l<r$ 的部分。需要支持：给定 $x$（即当前怪物和这一段对应怪物的出生时间的差），给定 $l$（即这一段的左端点），给定 $w$（剩余血量），求一个最大的位置 $p$，满足 $sum=\sum_{l\leq i\leq p}\min(c_i,r_ix),sum\leq w$，并求出 $sum$ 的值。

发现转化后的问题和[CF837G Functions On The Segments](https://www.luogu.com.cn/problem/CF837G)差不多，考虑用同样的做法。首先 $\min(c_i,r_ix)$ 可以视为分段一次函数，$x\leq \lfloor c_i/r_i\rfloor$ 的时候是 $r_ix+0$，$x>\lfloor c_i/r_i\rfloor$ 的时候是 $0x+c_i$。注意到 $\max x\leq 2\times 10^5$，考虑建 $\max x$ 棵可持久化线段树，以炮塔编号为下标维护一次项和常数项的区间和，每个炮塔对应线段树上的至多两次单点修改。

求位置 $p$ 可以二分，容易发现可以线段树上二分，这样单次复杂度就是 $\log n$。总复杂度 $O((n+q)\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
enum{N=200009};
struct T{
	int l,r;
	ll a,b;
}s[N*24];
int c[N],r[N],rt[N],id,u,v,x,st[N],tim[N],nc[N],p;
ll now,h,ans;
basic_string<int>bs[N];
void bd(int&k,int l,int r){//建树
	if(k=++id,l==r){s[k].a=::r[l];return;}
	int m=l+r>>1;
	bd(s[k].l,l,m),bd(s[k].r,m+1,r),s[k].a=s[s[k].l].a+s[s[k].r].a;
}
void upd(int&k,int l,int r){//单点修改
	if(s[++id]=s[k],k=id,l==r){s[k].a=0,s[k].b=c[l];return;}
	int m=l+r>>1;
	u>m?upd(s[k].r,m+1,r):upd(s[k].l,l,m),s[k].a=s[s[k].l].a+s[s[k].r].a,s[k].b=s[s[k].l].b+s[s[k].r].b;
}
void qry(int k,int l,int r){//区间和
	if(u<=l&&r<=v){now+=s[k].a*x+s[k].b;return;}
	int m=l+r>>1;
	if(u<=m)qry(s[k].l,l,m);
	if(m<v)qry(s[k].r,m+1,r);
}
void erf(int k,int l,int r){//二分
	ll w=s[k].a*x+s[k].b;
	int m=l+r>>1;
	if(l>=u){
		if(now+w<=h)now+=w,p=r;
		else if(l<r){
			if(w=s[s[k].l].a*x+s[s[k].l].b,now+w<=h)now+=w,p=m,erf(s[k].r,m+1,r);else erf(s[k].l,l,m);
		}
	}else if(m<u)erf(s[k].r,m+1,r);else if(erf(s[k].l,l,m),p==m)erf(s[k].r,m+1,r);
}
int main(){ios::sync_with_stdio(0),cin.tie(0);
	int n,m,i,j,t,o=0;
	for(cin>>n,i=1;i<=n;++i)if(cin>>c[i]>>r[i],j=c[i]/r[i]+1,j<N)bs[j]+=i;
	for(bd(rt[0],1,n),i=1;i<N;++i){
		rt[i]=rt[i-1];
		for(int o:bs[i])u=o,upd(rt[i],1,n);
	}
	for(st[0]=n+1,i=n;i;--i)st[++o]=i,nc[o]=c[i];
	for(cin>>m;m--;){
		cin>>t>>h;
		while(o){
			if(st[o-1]-(i=st[o])==1){//l=r的段
				j=min((ll)c[i],r[i]*1ll*(t-tim[o])+nc[o]);
				if(j>h){
					nc[o]=j-h,tim[o]=t;
					break;
				}
				h-=j,--o;
				continue;
			}
			x=t-tim[o],u=i,v=st[o-1]-1;//l<r的段
			now=0,qry(rt[x],1,n);
			if(now>h){
				now=0,p=u-1,erf(rt[x],1,n),++p;
				if(p==v)--o;else st[o]=p+1;
				st[++o]=p,j=min((ll)c[p],r[p]*1ll*x),h-=now,j-=h,nc[o]=j,tim[o]=t;
				break;
			}
			h-=now,--o;
		}
		if(!o)ans+=h;
		if(st[o]!=1)st[++o]=1,tim[o]=t,nc[o]=0;
	}
	cout<<ans;
}
```

---

## 作者：Cry_For_theMoon (赞：6)

自己花了近两个小时独立想到了这题的完整解法，很有成就感。

------------

把一个连续的，经过 $n$ 座塔的过程，视作非连续的，每座塔独立的过程。比如说如果时刻 $1$ 加入了一只怪物，时刻 $10$ 加入了第二只。当怪物 $1$ 从塔 $1$ 走到塔 $2$ 的时候，塔 $1$ 不会回复法力值，而是等到怪物 $2$ 到达塔 $1$ 的时候，一口气回复 $9$ 秒法力值。

换言之，在攻击完当前怪物后，所有的塔并不回复法力值。设下一只怪物 $t$ 秒后出现，那么处理下一只怪物之前，让所有的塔回复 $t$ 秒的法力值即可。

如果怪物没有死，那么说它死在第 $n+1$ 座塔。如果怪物死在第 $i$ 座塔，那么攻击完毕后，塔 $1\sim i-1$ 的剩余法力值都为 $0$，塔 $i$ 的法力值会被消耗掉一部分，而塔 $i+1\sim n$ 的法力值没有变化。

处理任意怪物之前，塔可以被分为若干个单点和若干条线段。单点的法力值是任意的，而一条线段里的每座塔的法力值可以视作从 $0$ 法力值开始，回复一个相同的秒数 $t$ 而得到。

给定线段 $[l,r]$ 和一个时间 $t$，代表其中的每座塔，初始法力都为空，然后都回复了 $t$ 秒。能否快速求出回复结束后的法力值之和？

如果塔没有法力值上限 $c_i$，那么我们求出区间的每秒回复量 $r_i$ 之和 $s$。$s\times t$ 就是所求。考虑对于每座塔，有一个分界时刻 $lim$：当 $t\le lim$ 的时候，它的贡献是 $t\times r_i$，否则，它的贡献是 $c_i$。

考虑把 $n$ 个 $lim$ 离散化，然后用可持久化线段树维护前缀和。这样可以 $O(\log n)$ 地得到答案。

现在可以快速计算线段的和了，而单点的信息也是很好维护的。

一个怪物被攻击的时候，是从最前面的部分开始推平的（“推平”指法力值清空重新开始回复）。我们可以用栈来维护所有的单点和线段。

那么考虑到一种情况，就是怪物最后倒在了一条线段的某个点上，这个时候，我们不能简单地处理了，需要在线段上用二分算出这个死亡的位置。这样，单次处理怪物的时间复杂度是 $O(\log^2 n)$ 的。当然是可以优化到 $O(\log n)$ 的，我们把这个二分过程改成主席树上二分即可。

现在我们完成了攻击怪物的过程，但是攻击当前怪物前，全局的所有塔都要回复一个 $t$ 秒，这个怎么维护呢。

对每条线段/点记录它被加入的时刻，然后维护一个全局时间 $sum$，加入一个线段/点的时候，它的时刻就是 $sum$。而当我们想让所有塔回复 $t$ 秒的时候，直接 $sum\leftarrow sum+t$ 即可。这样，用当前的 $sum$ 和线段/点的加入时刻作差，就可以得出这个部分到底回复了几秒，就可以利用主席树快速算答案了。

时间复杂度视实现在 $O(q\log n)\sim O(q\log^2 n)$ 吧。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
#define int ll
const ll MAXN=2e5+10,MAXM=MAXN*30,INF=1.5e12;
int n,q,c[MAXN],r[MAXN],pre;
int d[MAXN];
ll sum;
stack<array<ll,4> >st;
ll ans;
struct Node{int lc,rc;ll tag;};
struct Seg{
    int rt[MAXN],tot;
    Node tree[MAXM];
    ll a[MAXN];
    void copy(int from,int to){tree[to]=tree[from];}
    void build(ll* a){rep(i,1,n)(*this).a[i]=a[i];}
    int update(int x,int l,int r,int ql,int qr,ll val){
        int p=++tot;copy(x,p);
        if(ql<=l&&qr>=r){
            tree[p].tag+=val;
            return p;
        }
        int mid=(l+r)>>1;
        if(ql<=mid)tree[p].lc=update(tree[p].lc,l,mid,ql,qr,val);
        if(qr>mid)tree[p].rc=update(tree[p].rc,mid+1,r,ql,qr,val);
        return p;
    }
    ll qry(int x,int l,int r,int pos,ll sum){
        sum+=tree[x].tag;
        if(l==r)return sum+a[l];
        int mid=(l+r)>>1;
        if(pos<=mid)return qry(tree[x].lc,l,mid,pos,sum);
        else return qry(tree[x].rc,mid+1,r,pos,sum);
    }
}s1,s2;
bool cmp(int x,int y){return d[x]<d[y];}
void Pre(){
    static ll sum[MAXN],idx[MAXN];
    memset(sum,0,sizeof sum);
    s2.build(sum);
    rep(i,1,n)sum[i]=sum[i-1]+r[i];
    s1.build(sum);
    rep(i,1,n)d[i]=c[i]/r[i]+1,idx[i]=i;
    sort(idx+1,idx+1+n,cmp);sort(d+1,d+1+n);
    rep(i,1,n){
        s1.rt[i]=s1.update(s1.rt[i-1],1,n,idx[i],n,-r[idx[i]]);
        s2.rt[i]=s2.update(s2.rt[i-1],1,n,idx[i],n,c[idx[i]]);
    }
}
ll qry(ll t,int l){
    if(l==0)return 0;
    int idx=upper_bound(d+1,d+1+n,t)-d-1;
    return s2.qry(s2.rt[idx],1,n,l,0)+t*s1.qry(s1.rt[idx],1,n,l,0);
}
ll qry(ll t,int l,int r){return qry(t,r)-qry(t,l-1);}
void solve(int t,int h){
    sum+=t;
    while(st.size()){
        array<ll,4>tmp=st.top();st.pop();
        if(tmp[0]==tmp[1]){
            tmp[2]=min(tmp[2]+(sum-tmp[3])*r[tmp[0]],(ll)c[tmp[0]]);
            tmp[3]=sum;
            if(tmp[2]<h){
                h-=tmp[2];
                continue;
            }else{
                tmp[2]-=h;st.push(tmp);
                if(tmp[0]>1){
                    if(tmp[0]>2)st.push({1,tmp[0]-1,sum,0});
                    else st.push({1,1,0,sum}); 
                }
                return;
            }
        }else{
            ll val=qry(sum-tmp[2],tmp[0],tmp[1]);
            if(val<h){h-=val;continue;}
            int L=tmp[0],R=tmp[1],ret=L-1;
            while(L<=R){
                int mid=(L+R)>>1;
                if(qry(sum-tmp[2],tmp[0],mid)<h){
                    ret=mid;L=mid+1;
                }else R=mid-1;
            }
            ll pre=0;if(ret>=tmp[0])pre=qry(sum-tmp[2],tmp[0],ret);
            h-=pre;val=qry(sum-tmp[2],ret+1,ret+1);
            if(ret+1!=tmp[1]){
                if(ret+2!=tmp[1])st.push({ret+2,tmp[1],tmp[2],0});
                else st.push({ret+2,ret+2,qry(sum-tmp[2],ret+2,ret+2),sum});
            }
            st.push({ret+1,ret+1,val-h,sum});
            if(ret){
                if(ret>1)st.push({1,ret,sum,0});
                else st.push({1,1,0,sum});
            }
            return;
        }
    }
    if(n==1)st.push({1,1,0,sum});
    else st.push({1,n,sum,0});
    ans+=h;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n;
    rep(i,1,n)cin>>c[i]>>r[i];
    Pre();
    sum=INF;
    if(n>1)st.push({1,n,0,0});
    else st.push({1,n,c[1],sum});
    cin>>q;
    rep(i,1,q){
        int t,h;cin>>t>>h;
        int delta=t-pre;
        solve(delta,h);
        pre=t;
    }
    cout<<ans<<endl;

    return 0;
}
```

---

## 作者：Lynkcat (赞：3)

在 CF 上出 Dirty Work 题，出题人耗子尾汁。

我们对于每个塔求出填满所需要的时间 $f_i$，当前已经正常填了 $\min(g_i\times r_i,c_i)$，发现每次相当于重置一个前缀的 $g_i$ 为 0，然后一个位置特殊处理。于是可以直接考虑颜色段均摊，然后段内用主席树查询填满和未满的两部分值就行了。思维难度 *800。

代码我写的比较冗长，但很出人意料地调的时间花费的很少。

```c++
//我耳朵瞎掉拉~~
#define setI(x) freopen(x,"r",stdin)
#define setO(x) freopen(x,"w",stdout)
#include<bits/stdc++.h>
#define poly vector<int>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define mt make_tuple
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 200005
#define B 300005ll
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int rt[N];
int rt1[N];
int tp;
int sta[N];
int n,r[N],c[N],fl[N],nowfl[N];
int s[N];
int res[N];

int q,ans;
namespace sg1
{
    int cnt;
    int tr[10000005];
    int rson[10000005];
    int lson[10000005];
    void pushup(int k)
    {
        tr[k]=tr[lson[k]]+tr[rson[k]];
    }
    void update(int &k,int lst,int l,int r,int L,int x)
    {
        k=++cnt;
        tr[k]=tr[lst];
        lson[k]=lson[lst];
        rson[k]=rson[lst];
        if (l==r)
        {
            tr[k]=tr[k]+x;
            return;
        }
        int mid=l+(r-l)/2;
        if (L<=mid) update(lson[k],lson[lst],l,mid,L,x);
        else update(rson[k],rson[lst],mid+1,r,L,x);
        pushup(k);
    }
    int query(int lk,int rk,int l,int r,int L)
    {
        if (lk==rk) return 0;
        if (!rk) return 0;
        if (r<=L)
        {
            return tr[rk]-tr[lk];
        }
        int mid=l+(r-l)/2;
        int res=query(lson[lk],lson[rk],l,mid,L);
        if (mid<L)  
            res+=query(rson[lk],rson[rk],mid+1,r,L);
        return res;
    }
};
namespace sg2
{
    int cnt;
    int tr[10000005];
    int rson[10000005];
    int lson[10000005];
    void pushup(int k)
    {
        tr[k]=tr[lson[k]]+tr[rson[k]];
    }
    void update(int &k,int lst,int l,int r,int L,int x)
    {
        k=++cnt;
        tr[k]=tr[lst];
        lson[k]=lson[lst];
        rson[k]=rson[lst];
        if (l==r)
        {
            tr[k]=tr[k]+x;
            return;
        }
        int mid=l+(r-l)/2;
        if (L<=mid) update(lson[k],lson[lst],l,mid,L,x);
        else update(rson[k],rson[lst],mid+1,r,L,x);
        pushup(k);
    }
    int query(int lk,int rk,int l,int r,int L)
    {
        if (r<L) return 0;
        if (lk==rk) return 0;
        if (!rk) return 0;
        if (L<=l)
        {
            return tr[rk]-tr[lk];
        }
        int mid=l+(r-l)/2;
        int res=query(rson[lk],rson[rk],mid+1,r,L);
        if (L<=mid) 
            res+=query(lson[lk],lson[rk],l,mid,L);
        return res;
    }
};
void BellaKira()
{
    n=read();
    for (int i=1;i<=n;i++) 
    {
        c[i]=read(),r[i]=read();
        fl[i]=(c[i]-1)/r[i]+1;
        fl[i]=min(fl[i],B);
        s[i]=s[i-1]+c[i];
    }
    for (int i=1;i<=n;i++)
    {
        sg1::update(rt[i],rt[i-1],0,B,fl[i],c[i]);
        sg2::update(rt1[i],rt1[i-1],0,B,fl[i],r[i]);
    }
    q=read();
    sta[++tp]=n;
    nowfl[n]=inf;
    int lstt=0;
    for (int i=1;i<=q;i++)
    {
        int t=read(),h=read();
        int lstl=0;
        while (tp)
        {
            if (nowfl[sta[tp]]==inf)
            {
                int l=lstl+1,r=sta[tp];
                int now=r+1;
                while (l<=r)
                {
                    int mid=l+(r-l)/2;
                    if (s[mid]-s[lstl]>=h)
                    {
                        now=mid;
                        r=mid-1;
                    } else l=mid+1;
                }
                if (now==sta[tp]+1)
                {
                    h-=s[n]-s[lstl];
                    nowfl[n]=t;res[n]=0;
                } else
                {
                    if (now!=sta[tp]) sta[++tp]=now;
                    res[sta[tp]]=s[now]-s[lstl]-h;
                    nowfl[sta[tp]]=t;
                    if (now>1)
                    {
                        sta[++tp]=now-1;
                        nowfl[sta[tp]]=t;
                        res[sta[tp]]=0;
                    }
                    h=0;
                }
                break;
            } else
            if (!res[sta[tp]])
            {
                int nowt=t-nowfl[sta[tp]];
                int nowtt=sg1::query(rt[lstl],rt[sta[tp]],0,B,nowt)+
                            sg2::query(rt1[lstl],rt1[sta[tp]],0,B,nowt+1)*nowt;
                if (h>=nowtt)
                {
                    h-=nowtt;
                    nowfl[sta[tp]]=0;
                    res[sta[tp]]=0;
                    lstl=sta[tp];
                    tp--;
                    continue;
                } else
                {
                    int l=lstl+1,r=sta[tp];
                    int now=r+1;
                    while (l<=r)
                    {
                        int mid=l+(r-l)/2;
                        if (sg1::query(rt[lstl],rt[mid],0,B,nowt)+sg2::query(rt1[lstl],rt1[mid],0,B,nowt+1)*nowt>=h)
                        {
                            now=mid;
                            r=mid-1;
                        } else l=mid+1;
                    }
                    if (now!=sta[tp]) sta[++tp]=now;
                    res[sta[tp]]=sg1::query(rt[lstl],rt[now],0,B,nowt)+sg2::query(rt1[lstl],rt1[now],0,B,nowt+1)*nowt-h;
                    nowfl[sta[tp]]=t;
                    if (now>1)
                    {
                        sta[++tp]=now-1;
                        nowfl[sta[tp]]=t;
                        res[sta[tp]]=0;
                    }
                    h=0;
                    break;
                }
            } else
            {
                res[sta[tp]]+=(t-nowfl[sta[tp]])*r[sta[tp]];
                res[sta[tp]]=min(res[sta[tp]],c[sta[tp]]);
                if (res[sta[tp]]<=h)
                {
                    h-=res[sta[tp]];
                    res[sta[tp]]=0;
                    nowfl[sta[tp]]=0;
                    lstl=sta[tp];
                    tp--;
                    continue;
                } else
                {
                    res[sta[tp]]=res[sta[tp]]-h;
                    h=0;
                    nowfl[sta[tp]]=t;
                    break;
                }
            }   
        }
        if (!tp) sta[++tp]=n,nowfl[n]=t,res[n]=0;
        else
        {
            if (sta[tp]!=1)
            {
                int lst=sta[tp];
                sta[++tp]=lst-1;
                nowfl[lst-1]=t;
                res[lst-1]=0;
            }
        }
        ans+=h;
    }
    writeln(ans);
}
signed main()
{
    int T=1;
    while (T--)
    {
        BellaKira();
    }
}
/*
3
5 1
7 4
4 2
4
0 14
1 10
3 16
10 16
*/
```

---

## 作者：lingfunny (赞：3)

## Solution

记 $X_k$ 为 $\sum_{i=1}^kx_i$，即序列 $x$ 的前缀和。

对于每座塔都有满魔力时，可以通过二分 $C$ 来得到会推平哪个前缀。

对于每座塔在前一秒都没有魔力时，可以通过二分 $R$ 来得到会推平哪个前缀。

对于每座塔在前 $k$ 秒都没有魔力，且 $r_ik\le c_i$ 时，可以也通过二分 $R$ 来得到会推平哪个前缀。记 $p=\lceil\frac{h}{k}\rceil$，对 $p$ 二分即可。

记 $f_i=\lceil\frac{c_i}{r_i}\rceil$。对于经过时间 $t$，一座塔 $i$ 满魔力当且仅当 $t\ge f_i$。

如果不考虑 $r_ik\le c_i$ 的限制：

可以尝试实现一个数据结构，能够支持查询的 $t\ge f_i$ 塔的魔力总和与 $t<f_i$ 的塔的恢复速率总和，就可以得到经过时间 $t$ 后的魔力和。

考虑**线段树**。

在下标 $f_i$ 插入每个塔的 $c_i$ 和 $r_i$ 并维护 $c$ 和 $r$ 的区间和。查询时只需要查询前缀 $[1,t]$ 的容量和 和 区间 $[t+1, \texttt{inf}]$ 的速率和。

问题是现在只支持维护魔力和，并不能算出要推平到哪个前缀。

考虑**倍增**。

每次判断 $[1, v]$ 的塔的前缀魔力和是否大于 $h$，大于就不跳，小于等于就跳。倍增要注意可能 $[1,1]$ 就大于 $h$，不过这些都是基本的实现细节。

问题是线段树一下就插入了 $n$ 个塔的信息，区分不了前 $v$ 座塔魔力和 和 后 $n-v$ 座塔的魔力和。

考虑**主席树**。

按 $1\sim n$ 的顺序依次在下标 $f_i$ 插入 $c_i,r_i$，对于查询区间 $[l,r]$，直接用版本 $r$ 减去版本 $l-1$。注意到我们维护的信息是 $c$ 和 $r$ 的区间和，具有**可减性**，可以直接维护。

通过主席树和倍增，我们可以做到在 $\mathcal O(\log^2 n)$ 的时间复杂度内查询推平哪个前缀。

仍有一个问题，实现上述做法后，我们能回答的问题都有一个限制：每座塔需要都在**同一秒**没有魔力。

显然实际上很难出现这样的情况。

不过刚才反复出现了**推平**二字……

考虑**珂朵莉树**。

我们用珂朵莉树维护若干个区间 $[l,r,t]$，表示区间 $[l,r]$ 的每座塔都在 $t$ 时刻被榨干。对于在 $t$ 时刻没有完全榨干的塔，给它打个标记，分配一个 $[i,i,-t]$ 的线段（显然正常的 $t$ 不会是负数，标记不会混淆）。

不过珂朵莉树的最大问题在于时间复杂度。

发现每次操作，我们会抹平一段前缀，并新建两个线段 $[1, p, t]$ 和 $[p,p,-t]$，总线段数是 $\mathcal O(q)$ 的。而每个线段最多被插入一次，删除一次，对时间复杂度的总贡献是 $\mathcal O(1)$ 的，珂朵莉树的总时间复杂度是 $\mathcal O(q\log q)$ 的（用 `map` 或 `set` 实现自带 $\log$，当然你会发现每次只会对前缀动手脚，所以**直接用链表维护也可以**）。而先前使用的主席树也可以支持查询的任意一个线段 $[l,r]$ 内的塔。

总时间复杂度 $\mathcal O(q(\log^2 n+\log q))$ 或 $\mathcal O(q\log^2 n)$（链表）。

## Code

```cpp
// Problem: F. Tower Defense
// From: Codeforces - Educational Codeforces Round 124 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1651/problem/F
// Time: 2022-03-15 16:54
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
const int mxn = 2e5+10, mxd = 1e7;

int n, c[mxn], r[mxn], tt, root[mxn], lst[mxn], lg[mxn];
LL ans;
struct node {
	LL sc, sr; inline node operator + (const node& rhs) const { return {sc + rhs.sc, sr + rhs.sr}; }
} nd[mxd];
int lc[mxd], rc[mxd], tot;
#define mid ((L+R)>>1)
inline void psup(int o) { nd[o] = nd[lc[o]] + nd[rc[o]]; }
void insert(int& o, int rt, int p, node x, int L = 1, int R = mxn) {
	if(!o) o = ++tot; if(L == R) return nd[o] = nd[rt] + x, void();
	if(p <= mid) insert(lc[o], lc[rt], p, x, L, mid), rc[o] = rc[rt];
	else insert(rc[o], rc[rt], p, x, mid+1, R), lc[o] = lc[rt];
	psup(o);
}
node query(int r, int l, int p, int L = 1, int R = mxn) {
	// 计算版本r-l的小于等于 p 的 sc 和大于 p 的sr
	if(R <= p) return {nd[r].sc-nd[l].sc, 0}; if(L > p) return {0, nd[r].sr-nd[l].sr};
	return query(lc[r], lc[l], p, L, mid) + query(rc[r], rc[l], p, mid+1, R);
}
map <int, int> mp;
inline void cut(int p) {
	if(mp.find(p) == mp.end()) mp[p] = prev(mp.lower_bound(p))->second;
}
inline LL get(int l, int r, int dt) {
	node s = query(root[r], root[l-1], dt);
	return s.sc + (s.sr*dt);
}
// node[P] 时间为 P 的时候满魔力的塔的信息

signed main() {
	scanf("%d", &n); lg[0] = -1;
	for(int i = 1; i <= n; ++i) scanf("%d%d", c+i, r+i), lg[i] = lg[i>>1] + 1;
	for(int i = 1; i <= n; ++i) insert(root[i], root[i-1], min((c[i]+r[i]-1)/r[i], mxn), {c[i], r[i]});
	mp[n+1] = 114514; mp[1] = -1919810;
	scanf("%d", &tt);
	while(tt--) {
		int t, L, R, dt, pos; LL h, dec; scanf("%d%lld", &t, &h);
		++t;	// 存在 t = 0, 建议先 +1 以保证特殊标记可以区分开
		auto it = mp.begin();
		while(it->first != n+1) {
			if(it -> second < 0 && it -> second != -1919810) {
				// 这个点删了，但没完全删
				dt = t + it->second, pos = it -> first;
				dec = min((LL)c[pos], lst[pos] + (LL)r[pos] * dt);
				if(h >= dec) { h -= dec; it = mp.erase(it); }
				else { lst[pos] = dec - h; it -> second = -t; h = 0; break; }
			} else {
				L = it->first, R = next(it)->first - 1, dt = t - it->second;
				dec = get(L, R, dt);
				if(h >= dec) { h -= dec; it = mp.erase(it); }
				else {
					for(int d = lg[R-L+1], v; v = L + (1<<d), ~d; --d) if(v <= R) {
						// 判断 [L, v] 的和是否比 h 大，大了不跳，小了就跳
						dec = get(L, v, dt);
						if(h >= dec) h -= dec, L = v + 1;
					}
					if((dec = get(L, L, dt)) <= h) h -= dec, ++L;
					// 此时 get(L, L, dt) > h
					dec = min((LL)c[L], (LL)r[L] * dt);
					dec -= h; lst[L] = dec; h = 0; cut(L), cut(L+1);
					mp.erase(it); mp[L] = -t; break;
				}
			}
		}
		if(mp.find(1) == mp.end()) mp[1] = t; ans += h;
	}
	printf("%lld\n", ans);
	return 0;
}
```



---

## 作者：GaryH (赞：3)

## CF1651F 题解


**题意**：

数轴上有 $n$ 个塔，其中塔 $i$ 的坐标是 $i$，魔力值上限是 $lim_i$，每秒末可以回复 $re_i$ 点魔力。

还有 $q$ 个怪物，第 $i$ 个怪物出现时间为第 $t_i$ 秒初，血量为 $h_i$，初始坐标为 $1$ 并以 $1m/s$ 速度向右走。

第 $0$ 秒初时，所有塔的魔力值为 $lim_i$，怪物经过某塔的瞬间，该塔会耗费魔力值给怪物造成同等伤害，

形式化的，若此时怪物血量为 $H$，塔此时魔力值为 $W$，则 $H$ 和 $W$ 同时减去 $\min(H,W)$。

你要求出，所有经过了最后一个塔的怪物，在经过了最后一个塔后的剩余血量之和。

> $n,q,t_i\le2\times10^5,h_i\le10^{12},\forall i<q,t_i<t_{i+1},$ 其余所有数都在 `int` 范围内。

**做法**：

我们注意到，每个怪物的速度都是一样的，由此我们可以得到，数轴上所有怪物的位置顺序永远不变，

即不存在任何两塔 $i,j$ 以及两怪物 $x,y$，使得：$x$ 比 $y$ 先经过 $i$，而 $y$ 比 $x$ 先经过 $j$，

故一个自然的想法是，按出现时间的先后枚举每个怪物，并快速维护当前怪物给所有塔带来的影响。

我们发现，怪物给所有塔的魔力值带来的影响，永远是以下形式：

从点 $1$ 出发，将经过的所有塔的魔力值清零，最后到达杀死该怪物的塔或所有塔的后面。

注意到，在这段路径上，只有最多一个塔的魔力值损耗，与怪物本身的血量有关，

其他的塔的魔力值都会被清零，并按照其自身的永远不变的魔力值恢复速度来恢复魔力值。

我们称那个与怪物血量有关的点为关键点，则其他点就是非关键点。

此时，我们将数轴上的所有塔，用若干个关键点划分成了一些连续段，而任意一连续段，

其对应的区间 $[l,r]$ 中的所有塔，必定被同一怪物 $c$ 依次清零过，此时我们称该连续段颜色为 $c$。

那我们考虑能否快速维护一个连续段的信息。形式化的，若有个怪物 $i$ 站在了点 $l$，血量为 $H$，

且存在点 $r$ 使区间 $[l,r]$ 是颜色为 $c$ 的连续段，此时我们能否快速维护，

怪物 $i$ 最后会在区间 $[l,r]$ 中的哪个位置被杀死，或到达 $r$ 的右边。

考虑这个问题，我们可以先二分 $mid$ 并将问题转化为，判定怪物 $i$ 能否活着经过点 $mid$。

而怪物 $i$ 能活着经过点 $mid$，等价于区间 $[l,mid]$ 里所有塔对怪物造成的伤害值小于 $H$，

故我们需要求出区间 $[l,mid]$ 中塔对怪物造成的伤害值总和。

注意到 $[l,mid]$ 是 $[l,r]$ 的子区间，故对 $\forall j\in[l,mid]$，塔 $j$ 在第 $t_c+j-1$ 秒初的魔力值为 $0$，

原因是 $[l,r]$ 中所有塔的魔力值，都被怪物 $c$ 清零过，而怪物 $c$ 在 $t_c$ 秒初时，坐标为 $1$，

所以怪物 $c$ 到达点 $j$ 的时刻，就是第 $t_c+j-1$ 秒初。

同理，我们也可以算出，怪物 $i$ 到达塔 $j$ 时是第 $t_i+j-1$ 秒初，

这与怪物 $c$ 的到达时间相差 $t_i-t_c$ 秒，即塔 $j$ 有 $t_i-t_c$ 秒的时间，从 $0$ 开始恢复魔力值，

故我们可以算出，塔 $j$ 在怪物 $i$ 到达时的魔力值是：$\min((t_i-t_c)\times re_j,lim_j)$。

也就是说，区间 $[l,mid]$ 对怪物 $i$ 造成了总伤害是：$\sum\limits_{l\le j\le mid}\min((t_i-t_c)\times re_j,lim_j)$，

而我们需要的，就是快速的算出这个值。

看到式子里的 $\min$ 是不好维护的，我们考虑能否将 $\min$ 拆开，

即设 $X_j=\min((t_i-t_c)\times re_j,lim_j)$，我们分类讨论 $X_j$ 的值究竟等于哪一项。

若 $X_j=(t_i-t_c)\times re_j$，则说明了 $(t_i-t_c)\times re_j\le lim_j$，即 $t_i-t_c\le\lceil\frac{lim_j}{re_j}\rceil$，

而若 $X_j=lim_j$，也就说明了 $(t_i-t_c)\times re_j>lim_j$，即 $t_i-t_c>\lceil\frac{lim_j}{re_j}\rceil$。

我们记 $val_j=\lceil\frac{lim_j}{re_j}\rceil$，那么对于所有满足 $t_i-t_c\le val_j$ 的 $j$，$X_j$ 值都为 $(t_i-t_c)\times re_j$，

相反的，对于所有满足 $t_i-t_c>val_j$ 的 $j$，$X_j$ 值都为 $lim_j$，

所以，我们可以将我们要求的式子改写，即：

$\sum\limits_{l\le j\le mid}X_j=(\sum\limits_{l\le j\le mid,val_j\ge t_i-t_c}(t_i-t_c)\times re_j)+(\sum\limits_{l\le j\le mid,val_j<t_i-t_c}lim_j)$。

注意到后面两项都是典型的二位偏序的形式，故我们可以用主席树做到单次 $O(\log n)$，

再乘上二分的复杂度，即我们可以用 $O(\log^2n)$ 的复杂度来维护一个连续段的信息。

那我们继续考虑，当有若干个连续段时的维护方法。

其实，这时我们可以暴力处理每个关键点，并暴力枚举每个连续段，单个连续段内用上面的方法维护，

而这样的时间复杂度也是对的，原因可以用均摊复杂度的思想证明。

我们可以注意到，在这种做法中，枚举的连续段数与怪物实际经过的关键点数同级，

而怪物每经过一个关键点，都会使这个关键点的魔力值清零，即变成非关键点，

而每个怪物只会在其被某个塔杀死时，使这个塔变成一个新的关键点，

也就是说，关键点的总增量是 $O(q)$ 的，故我们枚举连续段的总次数也就是 $O(q)$ 的，

那么总复杂度也就是 $O(n+q\log^2n)$ 的。

当然，如果代码~~像我一样~~实现的不是很好，那复杂度可能会变成 $O((n+q)\log^2n)$ 且常数巨大，

就需要卡一下常数才能过。

当然，上面的时间复杂度还可以优化，就是把二分拿到主席树里面去，就可以做到单 $\log$。

[代码链接](https://codeforces.com/contest/1651/submission/149531334)

---

## 作者：DengDuck (赞：1)

感觉比较巧妙，而且是我的 $100$ 紫，所以写个题解纪念一下。

首先考虑分块解决问题。

注意到一个块可能会被多次归零，所以我们预处理每个块清空后经过 $i$ 秒增加的量 $f_i$，可以先写一个差分，再求个前缀和。

之后我们比较暴力地做，来了一个怪兽，如果块是整体清空过的，而且还没有对其中的部分单独修改过，那么预处理显然可以派上用场，整体值可以求出，然后讨论一下：

- 怪兽过得去就是清空，时间复杂度为 $\mathcal O(1)$。
- 怪兽过不去就暴力修改块，时间复杂度为 $\mathcal O(\sqrt n)$，显然这种修改每个怪兽只有一次。

否则对于不符合条件的块，就得暴力做，不过之后就清空喽。

时间复杂度为 $\mathcal O(n\sqrt n)$。

空间限制比较严，应该离线一块一块处理，空间复杂度 $\mathcal O(n)$

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=4e5+5;
const LL B=400;
const LL T=4e5;
LL n,q,c[N],b[N],r[N],t[N],h[N],L[N],R[N],ans,a[N],f[N],vis;
void work(LL x,LL y,LL now,LL lst)
{
	vis=0;
	for(int i=L[x];i<=R[x];i++)
	{
		a[i]=min(c[i],a[i]+(now-lst)*r[i]);
		if(a[i]<=h[y])
		{
			h[y]-=a[i];
			a[i]=0;
		}
		else
		{
			a[i]-=h[y];
			h[y]=0,vis=1;
		}
	}
}
void solve(LL x)
{
	vis=1;
	LL tim=0;
	memset(f,0,sizeof(f));
	for(int i=L[x];i<=R[x];i++)
	{
		f[1]+=r[i];
		f[c[i]/r[i]+1]-=r[i];
	}
	for(int i=1;i<=T;i++)f[i]+=f[i-1];
	for(int i=L[x];i<=R[x];i++)
	{
		f[c[i]/r[i]+1]+=c[i]%r[i];
	}
	for(int i=1;i<=T;i++)f[i]+=f[i-1];
	for(int i=1;i<=q;i++)
	{
		if(h[i]==0)continue;
		LL now=t[i]+L[x]-1;
		if(vis)work(x,i,now,tim);
		else 
		{
			if(h[i]<f[now-tim])work(x,i,now,tim);
			else h[i]-=min(f[now-tim],h[i]);
		}
		tim=now;
	}
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&c[i],&r[i]);
		a[i]=c[i];
	}
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%lld%lld",&t[i],&h[i]);
	}
	LL num=(n+B-1)/B;
	for(LL i=1;i<=num;i++)
	{
		L[i]=R[i-1]+1,R[i]=min(B*i,n);
		for(int j=L[i];j<=R[i];j++)b[j]=i;
	}
	for(int i=1;i<=n;i++)a[i]=c[i];
	for(int i=1;i<=num;i++)solve(i);
	for(int i=1;i<=q;i++)ans+=h[i];
	printf("%lld",ans);
}
```

---

## 作者：xfrvq (赞：0)

设 $a_{i,j}$ 为 $i$ 时刻塔 $j$ 魔力值。一次操作 $(t,h)$ 等价于：

+ 找到最小 $j$ 使 $a_{t,1}+\cdots+a_{t+j-1,j}-h\ge0$，设其值 $x$。$a_{t,1}\cdots\gets 0,a_{t+j-1,j}\gets x$。
+ 期间不断发生转移 $a_{i+1,j}=\min(a_{i,j}+r_j,c_j)$。

维护 $b_{i,j}=a_{i+j-1,j}$，转化为维护序列 $b_j$：

+ 操作 1：找到最小 $j$ 使 $b_1+\cdots+b_j-h\ge0$，设其值 $x$。$b_1\cdots b_{j-1}\gets 0,b_j\gets x$。
+ 操作 2：对于所有位置，$b_j\gets\min(b_j+r_j,c_j)$。

考虑分块。给每个块标记状态：$1$ 代表已被清空，$2$ 代表被清空到一半，即操作 1 中 $j$ 所在块状态。以下认为 $n,q$ 以及时间维同阶。

对于每个块，预处理 $S_i$：清空该块后 $i$ 时刻块和。于是对 $1$ 类块，记录上次清空时间，询问块和时直接查表。

操作 1 直接从前往后依次询问块和，超过 $h$ 停止。然后依次查询该块每个位置的值。注意到**当需要询问一个块的块和时，该块最后一定会被清空或标注为 $2$ 类块**。于是一次操作 1 会清空访问到所有的 $2$ 类块，并新产生一个 $2$ 类块，所有操作 1 总共会影响到 $O(n)$ 个 $2$ 类块。所以对 $2$ 类块直接暴力求和。

实现时注意到存在 $0$ 类块代表初始满血状态。于是对每个 $0/2$ 类块位置维护函数 $(k,x)$，代表 $b_{t,j}=\min(k_jt+x_j,c_j)$，$t$ 为当前时间。

对每个块处理清空后 $2\times10^5$ 个时刻的块和，$O(n\sqrt n)$ 空间开不下，考虑仅处理到 $\sqrt n$，对于 $\gt\sqrt n$ 的部分暴力。因为触发 $\gt\sqrt n$ 的询问，必定会消耗 $\sqrt n$ 个时刻，故对每个块最多有根号个此类询问。

总复杂度 $O(n\sqrt n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i = (a);i <= (b);++i)

using ll = long long;

const int N = 2e5 + 5,SQ = 455;

int n,q,T,B,C,bl[N],st[SQ],ed[SQ],vis[SQ];
ll h,a[N],b[N],c[N],sc[SQ],S[SQ][SQ],tim[SQ],sum;

ll qry0(int i){
	if(!vis[bl[i]]) return c[i];
	return min(c[i],vis[bl[i]] == 1 ? b[i] * (T - tim[bl[i]]) : b[i] * T + a[i]);
}

ll qry(int i,ll s = 0){
	if(!vis[i]) return sc[i];
	if(vis[i] == 1 && T - tim[i] <= 450) return S[i][T - tim[i]];
	rep(j,st[i],ed[i]) s += qry0(j);
	return s;
}

int main(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d%d",c + i,b + i);
	B = sqrt(n),C = (n - 1) / B + 1;
	rep(i,1,C){
		st[i] = ed[i - 1] + 1,ed[i] = i == C ? n : st[i] + B - 1;
		rep(j,st[i],ed[i]){
			bl[j] = i,S[i][1] += b[j],sc[i] += c[j];
			if(c[j] / b[j] <= 450) S[i][c[j] / b[j] + 1] += c[j] % b[j] - b[j],S[i][c[j] / b[j] + 2] -= c[j] % b[j];
		}
		rep(j,1,450) S[i][j] += S[i][j - 1];
		rep(j,1,450) S[i][j] += S[i][j - 1];
//		rep(j,0,10) printf("%d,",S[i][j]);puts("");
	}
	for(scanf("%d",&q);q--;sum += h){
		scanf("%d%lld",&T,&h);
		rep(i,1,C){
			ll x = qry(i);
			if(h > x){ h -= x,vis[i] = 1,tim[i] = T; continue; }
			rep(j,st[i],ed[i]){
				x = qry0(j);
				if(h > x){ h -= x,a[j] = -T * b[j]; continue; }
				a[j] = -T * b[j] + x - h,h = 0;
				rep(k,j + 1,ed[i]) a[k] = -T * b[k] + qry0(k);
				break;
			}
			vis[i] = 2; break;
		}
	}
	printf("%lld\n",sum);
	return 0;
}
```

---

## 作者：analysis (赞：0)

首先是数学表达这道题

考虑第 $i$ 个怪物。

它跑完自己的全程扣得血是：

$$
\sum\min\{c_j,m_{j,lst} + \Delta t \times r_j\}
$$

$\min$ 有点难搞，没啥好性质。

考虑拆开为两个部分：

$$
\sum c_j + \sum (m_{j,lst} + \Delta t \times r_j) = \sum c_j + \sum m_{j,lst} + \sum \Delta t \times r_j
$$

且取用的部分都与 $\Delta t$ 有关，当 $\Delta t \geq \frac{c_j}{r_j}$ 时取用 $c_j$，反之亦然。

有上式可以想到二分，若前缀关于上式的值小于 $h$ 则可取，反之亦然。

这样维护前缀的上式即可。

不想打主席树怎么办？分块处理。

维护块中上式，对于三种情况：

- 非全零块暴力

- 全零块 $O(1)$ 计算。

- 未能抹平块暴力。

均摊 $O(n\sqrt{n})$

```cpp
#include <bits/stdc++.h>
#define int long long
const int maxn = 4e5;
using namespace std;
int s, n, q;
#define getbl(x) (x - 1) / s + 1
#define getbll(x) (x - 1) * s + 1
#define getblr(x) x *s
#define forbl(i, bl) for (int i = getbll(bl); i <= min(n, getblr(bl)); i++)
int c[maxn + 5], r[maxn + 5], m[maxn + 5];
int t[maxn + 5], h[maxn + 5];
int mxt;
int d[maxn + 5];
signed main() {
    freopen("dinosaurs.in", "r", stdin);
    freopen("dinosaurs.out", "w", stdout);
    scanf("%lld", &n);
    s = sqrt(n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld", &c[i], &r[i]);
        m[i] = c[i];
    }
    scanf("%lld", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%lld%lld", &t[i], &h[i]);
    }
    t[0] = 0;
    int ed = getbl(n);
    mxt = t[q];
    for (int i = 1; i <= ed; i++) {
        memset(d, 0, sizeof d);
        int j, k;
        forbl(j, i) {
            d[1] += r[j];
            if(c[j] / r[j] > maxn)continue;
            d[c[j] / r[j] + 1] -= r[j];
            if (c[j] % r[j]) {
                d[c[j] / r[j] + 1] += c[j] % r[j];
                d[c[j] / r[j] + 2] -= c[j] % r[j];
            }
        }
        for (j = 1; j <= maxn; j++) {
            d[j] += d[j - 1];
        }
        for (j = 1; j <= maxn; j++) {
            d[j] += d[j - 1];
        }
        int lst = 0;
        bool tag = 0;
        for (j = 1; j <= q; j++) {
            if (!h[j])
                continue;
            if (!tag) {
                forbl(k, i) { m[k] = min(m[k] + (t[j] - t[lst]) * r[k], c[k]); }
                bool clr = true;
                forbl(k, i) {
                    int ct = min(h[j], m[k]);
                    h[j] -= ct;
                    m[k] -= ct;
                    if (m[k])
                        clr = false;
                }
                if (clr)
                    tag = 1;
            } else {
                int dt = t[j] - t[lst];
                if (h[j] >= d[dt]) {
                    h[j] -= d[dt];
                } else {
                    forbl(k, i) { m[k] = min(m[k] + dt * r[k], c[k]); }
                    bool clr = true;
                    forbl(k, i) {
                        int ct = min(h[j], m[k]);
                        h[j] -= ct;
                        m[k] -= ct;
                    }
                    tag = 0;
                }
            }
            lst = j;
        }
    }
    int ans = 0;
    for (int i = 1; i <= q; i++) {
        ans += h[i];
    }
    printf("%lld", ans);
}
```

---

