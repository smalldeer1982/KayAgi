# [IAMOI R1] 家庭矛盾

## 题目背景

小 L 和小 C 发生了一些家庭矛盾，小 C 和小 L 徘徊在分手的边缘。

## 题目描述

小 L 和小 C 在一起生活的的每一天都可以用一个二元组 $(a_i,c_i)$ 表示。$c_i$ 要么是 $0$ ，要么是 $1$，代表这天小 L 和小 C 有没有吵架。而 $a_i$ 则是一个整数，代表这一天小 C 的心情值。

小 L 和小 C 正在同时进行 $m$ 场家庭战争。第 $k$ 场战争从第 $l_k$ 天开始。

由于他们的战争非常激烈，你不知道他们在第几天会结束这场战争。但如果这场战争于第 $r$ 天结束，且从第 $l_k$ 天到第 $r$ 天吵架的天数恰好为 $d_k$，那么这场战争就会给小 C 带来一定的怨气值。怨气值为第 $l_k$ 天到第 $r$ 天小 C 心情值的逆序对个数。否则，小 C 的怨气值就为 $0$。

现在，小 L 把这 $n$ 天的 $(a_i,c_i)$ 和 $m$ 场战争的 $l_k$ 和 $d_k$ 告诉了你。对于每场战争，小 L 希望知道对于所有可能的结束时间，小 C 的怨气值之和，以便他挽回和小 L 的感情。他会非常感激你的帮助，并给你 $7420738134810 \bmod 12673$ 元作为感谢。

### 形式化题意

你有 $n$ 个二元组 $(a_{i},c_{i})$，其中满足 $c_{i} \in \{0,1\}$。

现在有 $m$ 个询问，每次询问给出两个整数 $l_{k},d_{k}$，求：

$$
\sum_{r=l_{k}}^{n} \left[\left(\sum_{i=l_{k}}^{r} c_{i}\right)=d_{k}\right] \sum_{i=l_{k}}^{r} \sum_{j=i+1}^{r} [a_{j}<a_{i}]
$$
其中中括号内的式子若为真，则其值为 $1$，否则为 $0$。

## 说明/提示

### 样例解释 $1$

对于询问 $1$，只有区间 $[3,4]$ 符合条件，所以答案为 $1$。

对于询问 $2$，只有区间 $[1,4]$ 符合条件，所以答案为 $5$。

### 数据范围

|测试点编号| $n,m\le$ | 特殊性质 |
| :-----------: | :-----------: | :-----------: |
| $1$ | $100$ | 无 | 
| $2,3$ | $10^3$ | 无 |
| $4,5$ | $10^5$ | A |
| $6\sim8$ | $10^5$ | B |
| $9,10$ | $10^5$ | CD |
| $11,12$ | $5\times10^4$ | C |
| $13,14$ | $10^5$ | C |
| $15\sim 17$ | $10^5$ | D |
| $18\sim20$ | $5\times10^4$ | 无 |
| $21\sim25$ | $10^5$ | 无 |

特殊性质 A：保证 $c_i=0$。

特殊性质 B：保证 $d_{k}=1$。

特殊性质 C：保证 $c_i=1$。

特殊性质 D：保证询问中 $\forall k<m,l_{k} \le l_{k+1},d_{k} \le d_{k+1}$。

对于 $100\%$ 的数据，$1\le n,m\le10^5$，$1\le l_k\le n$，$1\le a_i\le10^9$，$c_{i} \in \{0,1\}$，$0\le d_k\le 10^9$。

保证此题的时空限制是标程的 **2** 倍及以上。

## 样例 #1

### 输入

```
4
4 0
5 1
3 0
2 1
2
3 1
1 2```

### 输出

```
1
5```

# 题解

## 作者：wangshulin (赞：6)

## 暴力
- 合法区间的右端点是连续的，暴力树状数组递推求逆序对即可。
- 特殊性质 A：
	
   若存在合法区间，区间左端点固定为 $l_{k}$，区间右端点必定是 $[l_{k},n]$ 种任意一个数，所以从后往前递推树状数组求每种可能的 $l_{k}$ 对应的答案即可。
## 后面所有讲解都要用的前置性质
设右端点的取值范围为 $[L,R]$，显然 $c_{L}=1$，$\forall i \in [L+1,R],c_{i}=0$，又显然 $[L,R]$ 的取值最多只有 $n$ 种，因为整个 $[1,n]$ 的区间是由若干个不重合的 $[L,R]$ 区间拼成的，所以我们将询问按其对应的 $[L,R]$ 分类。

设 $f(l,r)$ 为区间 $[l,r]$ 的逆序对个数，贡献可以分为了三部分：
- 左部分区间：$f(l,L-1)$。
- 右部分区间：$\sum_{i=L}^{R} f(L,i)$。
- 两区间之间：$\sum_{i=L}^{R} \sum_{j=l}^{L-1} \sum_{k=L}^{i}[a_{j}>a_{k}]$。
## 两区间之间的贡献的求法
- 对序列进行分块，对于每一个块用树状数组预处理其和每个区间 $[L,R]$ 之间的贡献，是 $O(n \sqrt n \log n)$ 的，查询时先遍历整块求所有整块的贡献和，剩下残块的贡献用类似的方法用树状数组求，是 $O(n \sqrt n \log n)$ 的。

- 特殊性质 C：
	
   每个区间 $[L,R]$ 的长度都为 $1$，所以直接比较，不需要树状数组维护。

- 发现如上算法中，一共有 $O(n)$ 次加入，和 $O(n \sqrt n)$ 次查询，这显然可以用根号平衡——使用 $O(\sqrt n)$ 加入，$O(1)$ 查询的分块数据结构即可。
## 左区间贡献的求法
- 特殊性质 B：

	左区间的 $c_{i}$ 是全 $0$ 段，且右端点为 $n$ 或右边一位的 $c_{i}$ 为 $1$，性质和右区间的出现相似，所以可以参考下文右区间贡献的求法。


- 左区间是固定区间，相当于求区间逆序对，可以用莫队暴力 $O(n\sqrt m \log n)$ 做，可跑过 $n \le 5 \times 10^{4}$ 的点。

- 特殊性质 D：
	
   这个特殊性质下的左区间的左端点和右端点都是递增的，意味着不需要做 $O(n \sqrt m)$ 次莫队更新，只需要 $O(m)$ 递推，时间复杂度降到 $O(n \log n)$。

- $O(n \sqrt m)$ 的正解做法参考 P5047。
## 右区间贡献的求法
- 特殊性质 C:
	
   右区间长度为 $1$，不需要处理其贡献。
- 所有右区间拥有共同的左端点，参考性质 A 的方法。

最终时间复杂度即优化为 $O(n\sqrt m+n\sqrt n)$。

### 上述题解中存在两种贡献的求解需要从带 $\log$ 优化到不带 $\log$，但是根据测试数据的强度看选手只需要会其中一个就足以通过了（我们又不是 Ynoi，真的卡不掉啊！）
## code

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=200010,B=500,CB=(N+B-1)/B;
int n,m,cq,clis,a[N],c[N],sc[N],lis[N],bel[N],lef[CB],rig[CB];
ll g[N],ans[N],fl[N],fr[N],sfl[N],sfr[N],Id[N<<2],cnt[CB][N];
vector<int> gId[N];
vector<ll> ansl[N],ansr[N];
vector<pair<int,int>> gl[N],gr[N];
int qbel(int x){
	return (x+B-1)/B;
}
int qlef(int x){
	return max(0,B*(x-1)+1);
}
int qrig(int x){
	return min(n,B*x);
}
namespace DS{
	struct BIT{
		ll t[N];
		void clear(){
			memset(t,0,sizeof(t));
		}
		int lowbit(int x){
			return x&-x;
		}
		void add(int k,ll x){
			for(int i=k;i<=n;i+=lowbit(i)) t[i]+=x;
		}
		ll query(int k){
			ll s=0;
			for(int i=k;i;i-=lowbit(i)) s+=t[i];
			return s;
		}
		ll query(int l,int r){
			if(l>r) return 0;
			else return query(r)-query(l-1);
		}
	}tr;
	struct BLC{
		ll val[N],tag[CB];
		void clear(){
			memset(val,0,sizeof(val));
			memset(tag,0,sizeof(tag));
		}
		void add(int k,ll x){//单点加——O(\sqrt n)
			for(int i=k;i<=rig[bel[k]];i++) val[i]+=x;
			for(int i=bel[k]+1;i<=bel[n];i++) tag[i]+=x;
		}
		ll query(int l){//前缀查询——O(1)
			return val[l]+tag[bel[l]];
		}
		ll query(int l,int r){
			if(l>r) return 0;
			else return query(r)-query(l-1);
		}
	}blc;
};
struct query{
	int x,d,l,r;
}p[N];
struct MO_query{
	int l,r,Id;
	bool operator<(const MO_query &o)const{
		if(bel[l]!=bel[o.l]) return bel[l]<bel[o.l];
		else{
			if(bel[l]&1) return r<o.r;
			else return r>o.r;
		}
	}
}q[N];
void PART_1(){
	DS::tr.clear();
	DS::blc.clear();
	int L,R,cnt;
	ll res;
	sort(q+1,q+cq+1);
	L=1,R=0,cnt=0;
	for(int i=1;i<=cq;i++){
		if(R<q[i].r) gr[L-1].push_back({R+1,q[i].r}),ansr[L-1].push_back(0),Id[++cnt]=ansr[L-1].size()-1,R=q[i].r;
		if(L>q[i].l) gl[R].push_back({q[i].l,L-1}),ansl[R].push_back(0),Id[++cnt]=ansl[R].size()-1,L=q[i].l;
		if(R>q[i].r) gr[L-1].push_back({q[i].r+1,R}),ansr[L-1].push_back(0),Id[++cnt]=ansr[L-1].size()-1,R=q[i].r;
		if(L<q[i].l) gl[R].push_back({L,q[i].l-1}),ansl[R].push_back(0),Id[++cnt]=ansl[R].size()-1,L=q[i].l;
	}
	for(int i=0;i<=n;i++){
		if(i){
			fr[i]=DS::blc.query(a[i]+1,n);
			DS::blc.add(a[i],1);
			fl[i]=DS::blc.query(a[i]-1);
			sfl[i]=sfl[i-1]+fl[i];
			sfr[i]=sfr[i-1]+fr[i];
		}
		for(int j=0;j<gl[i].size();j++){
			for(int k=gl[i][j].first;k<=gl[i][j].second;k++) ansl[i][j]+=DS::blc.query(a[k]-1);
		}
		for(int j=0;j<gr[i].size();j++){
			for(int k=gr[i][j].first;k<=gr[i][j].second;k++) ansr[i][j]+=DS::blc.query(a[k]+1,n);
		}
	}
	L=1,R=0,cnt=0,res=0;
	for(int i=1;i<=cq;i++){
		if(R<q[i].r) res+=(sfr[q[i].r]-sfr[R])-ansr[L-1][Id[++cnt]],R=q[i].r;
		if(L>q[i].l) res+=ansl[R][Id[++cnt]]-(sfl[L-1]-sfl[q[i].l-1]),L=q[i].l;
		if(R>q[i].r) res-=(sfr[R]-sfr[q[i].r])-ansr[L-1][Id[++cnt]],R=q[i].r;
		if(L<q[i].l) res-=ansl[R][Id[++cnt]]-(sfl[q[i].l-1]-sfl[L-1]),L=q[i].l;
		ans[q[i].Id]+=res*(p[q[i].Id].r-p[q[i].Id].l+1);
	}
}
void PART_2(){
	DS::tr.clear();
	DS::blc.clear();
	for(int l=1,r;l<=n;l=r+1){//预处理计算块完整/不完整时的贡献——O(n\log n)
		for(r=l;r<=n&&sc[r]==sc[l];r++) ;
		r--;
		ll t=0;
		for(int j=r;j>=l;j--){
			t+=DS::tr.query(a[j]-1);
			DS::tr.add(a[j],r-j+1);
		}
		g[l]=t;
		for(int j=l;j<=r;j++){//从 l 到 r 删除
			t-=DS::tr.query(a[j]-1);//去除 a_{j} 往后贡献的逆序对
			if(j<r) g[j+1]=t;
			DS::tr.add(a[j],-(r-j+1));
		}
	}
	for(int i=1;i<=bel[n];i++){//开始计算 [1,l-1] 和 [l,r] 之间的贡
		for(int j=lef[i];j<=rig[i];j++) DS::blc.add(a[j],1);
		for(int l=1,r;l<=n;l=r+1){
			for(r=l;r<=n&&sc[r]==sc[l];r++) ;
			r--;
			if(rig[i]>=l) continue;
			for(int j=l;j<=r;j++) cnt[i][l]+=DS::blc.query(a[j]+1,n)*(r-j+1);
		}
		for(int j=lef[i];j<=rig[i];j++) DS::blc.add(a[j],-1);
	}
	for(int l=1,r;l<=n;l=r+1){//开始计算 [1,l-1] 和 [l,r] 之间的贡献
		for(r=l;r<=n&&sc[r]==sc[l];r++) ;
		r--;
		for(int i=l;i<=r;i++) DS::blc.add(a[i],r-i+1);
		for(auto i:gId[l]){
			if(p[i].x>=p[i].l){
				ans[i]=g[p[i].x];
				continue;
			}
			ans[i]+=g[p[i].l];
			if(bel[p[i].x]==bel[p[i].l-1]){
				for(int j=p[i].x;j<=p[i].l-1;j++) ans[i]+=DS::blc.query(a[j]-1);
			}else{
				for(int j=p[i].x;j<=rig[bel[p[i].x]];j++) ans[i]+=DS::blc.query(a[j]-1);
				for(int j=bel[p[i].x]+1;j<bel[p[i].l-1];j++) ans[i]+=cnt[j][l];
				for(int j=lef[bel[p[i].l-1]];j<=p[i].l-1;j++) ans[i]+=DS::blc.query(a[j]-1);
			}
		}
		for(int i=l;i<=r;i++) DS::blc.add(a[i],-(r-i+1));
	}
}
int main(){
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++) bel[i]=qbel(i);
	for(int i=1;i<=bel[n];i++) lef[i]=qlef(i),rig[i]=qrig(i); 
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&c[i]);
		lis[i]=a[i];
		sc[i]=sc[i-1]+c[i];
	}
	sort(lis+1,lis+n+1);
	clis=unique(lis+1,lis+n+1)-lis-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(lis+1,lis+clis+1,a[i])-lis;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&p[i].x,&p[i].d);
		p[i].l=lower_bound(sc+1,sc+n+1,sc[p[i].x-1]+p[i].d)-sc;
		p[i].r=upper_bound(sc+1,sc+n+1,sc[p[i].x-1]+p[i].d)-sc-1;
//		printf("%lld %lld\n",p[i].l,p[i].r);
		if(p[i].r<=p[i].x) continue;
		if(p[i].x<=p[i].l-1&&p[i].l<=p[i].r) q[++cq].l=p[i].x,q[cq].r=p[i].l-1,q[cq].Id=i;
		if(p[i].l<=p[i].r) gId[p[i].l].push_back(i);
	}
	PART_1();
	PART_2();
	for(int i=1;i<=m;i++){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：_abcd_ (赞：2)

## [[IAMOI R1] 家庭矛盾](https://www.luogu.com.cn/problem/P11763)

由于 $ c_i \ge 0 $，因此所有可能的 $ r $ 肯定构成了一个连续的区间。设这个区间是 $ (L,R] $，并设 $ f(l,R) = \sum\limits_{r=l}^R \sum\limits_{l \le i < j \le r} [a_i > a_j] $，那么答案就是 $ f(l,R) - f(l,L) $，因此可以拆成两个询问。

考虑如何处理 $ f(l,R) $。显然
$$ f(l,R) = \sum\limits_{l \le i < j \le R} [a_i > a_j] (R-j+1) $$
$$ = (R+1) \sum\limits_{l \le i < j \le R} [a_i > a_j] - \sum\limits_{l \le i < j \le R} [a_i > a_j] j $$

前半部分直接上 [Yuno loves sqrt technology II](https://www.luogu.com.cn/problem/P5047) 就行了。对于后半部分做法类似，只需要当莫队往右扩展时，将逆序对数乘上 $ r $。而当莫队往左扩展时，只需要新开一个 $ \rm BIT $ 和分块前缀和，其中每个数的权值是他的下标。

视 $ n,m $ 同阶，则复杂度为 $ O(n \sqrt{n}) $。

---

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pn putchar('\n')
#define mset(a,x) memset(a,x,sizeof a)
#define mcpy(a,b) memcpy(a,b,sizeof a)
#define all(a) a.begin(),a.end()
#define fls() fflush(stdout)
#define int ll
using namespace std;
int re()
{
    int x=0;
    bool t=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
        t=ch=='-'?0:t,ch=getchar();
    while(ch>='0'&&ch<='9')
        x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return t?x:-x;
}
const int maxn=1e5+5;
struct Qry
{
    int l,r,i,ad;
};
int n,Q,m,B;
int a[maxn],b[maxn];
int pf[maxn],pf2[maxn],sf[maxn];
int ans[maxn],ans1[maxn*4],ans2[maxn*4];
vector<Qry>qry;
vector<tuple<int,int,int>>qry1[maxn],qry2[maxn];
struct BIT
{
    int tree[maxn];
    void add(int x,int ad)
    {
        for(int i=x;i<=n;i+=i&-i)
            tree[i]+=ad;
    }
    int qry(int x)
    {
        int ret=0;
        for(int i=x;i;i-=i&-i)
            ret+=tree[i];
        return ret;
    }
}bit,bit2;
struct Block
{
    int n,B;
    int a[maxn],b[maxn];
    void clr()
    {
        mset(a,0);
        mset(b,0);
    }
    void add(int x,int ad)
    {
        int k=x/B;
        for(int i=x;i<k*B+B&&i<=n;i++)
            a[i]+=ad;
        for(int i=k+1;i*B<=n;i++)
            b[i]+=ad;
    }
    int qry(int x)
    {
        return a[x]+b[x/B];
    }
}blk,blk2;
void lsh()
{
    vector<int>b;
    for(int i=1;i<=n;i++)
        b.push_back(a[i]);
    sort(all(b));
    b.erase(unique(all(b)),b.end());
    for(int i=1;i<=n;i++)
        a[i]=lower_bound(all(b),a[i])-b.begin()+1;
    blk.n=blk2.n=b.size();
    blk.B=blk2.B=sqrt(b.size());
}
signed main()
{
    n=re();
    for(int i=1;i<=n;i++)
    {
        a[i]=re();
        b[i]=b[i-1]+re();
    }
    lsh();
    Q=re();
    for(int i=1;i<=Q;i++)
    {
        int l=re();
        int k=b[l-1]+re();
        int r=lower_bound(b+1,b+1+n,k)-b-1;
        if(r>=l)
            qry.push_back({l,r,i,-1});
        r=upper_bound(b+1,b+1+n,k)-b-1;
        if(r>=l)
            qry.push_back({l,r,i,1});
    }
    B=sqrt((double)n*n/Q)+1;
    sort(all(qry),[](Qry x,Qry y){return x.l/B==y.l/B?x.r<y.r:x.l<y.l;});
    int L=1,R=0;
    for(auto [l,r,i,ad]:qry)
    {
        if(l<L)
        {
            m++;
            qry1[R].push_back({l,L-1,m});
            L=l;
        }
        if(R<r)
        {
            m++;
            qry2[L].push_back({R+1,r,m});
            R=r;
        }
        if(L<l)
        {
            m++;
            qry1[R].push_back({L,l-1,m});
            L=l;
        }
        if(r<R)
        {
            m++;
            qry2[L].push_back({r+1,R,m});
            R=r;
        }
    }
    for(int i=1;i<=n;i++)
    {
        bit.add(a[i]+1,1);
        bit2.add(a[i]+1,i);
        pf[i]=bit.qry(a[i]);
        pf2[i]=bit2.qry(a[i]);
    }
    for(int i=1;i<=n;i++)
    {
        blk.add(a[i],1);
        blk2.add(a[i],i);
        for(auto [l,r,j]:qry1[i])
        {
            for(int k=l;k<=r;k++)
            {
                ans1[j]+=blk.qry(a[k]-1)-pf[k];
                ans2[j]+=blk2.qry(a[k]-1)-pf2[k];
            }
        }
    }
    mset(bit.tree,0);
    blk.clr();
    for(int i=n;i;i--)
    {
        bit.add(a[i],1);
        sf[i]=n-i+1-bit.qry(a[i]);
    }
    for(int i=n;i;i--)
    {
        blk.add(a[i],1);
        for(auto [l,r,j]:qry2[i])
        {
            for(int k=l;k<=r;k++)
            {
                int t=n-i+1-blk.qry(a[k])-sf[k];
                ans1[j]+=t;
                ans2[j]+=t*k;
            }
        }
    }
    L=1,R=0;
    m=0;
    int c1=0,c2=0;
    for(auto [l,r,i,ad]:qry)
    {
        if(l<L)
        {
            m++;
            c1+=ans1[m];
            c2+=ans2[m];
            L=l;
        }
        if(R<r)
        {
            m++;
            c1+=ans1[m];
            c2+=ans2[m];
            R=r;
        }
        if(L<l)
        {
            m++;
            c1-=ans1[m];
            c2-=ans2[m];
            L=l;
        }
        if(r<R)
        {
            m++;
            c1-=ans1[m];
            c2-=ans2[m];
            R=r;
        }
        ans[i]+=((r+1)*c1-c2)*ad;
    }
    for(int i=1;i<=Q;i++)
        printf("%lld\n",ans[i]);
    return 0;
}
```

---

## 作者：lzyqwq (赞：2)

思路一眼秒了，然后写挂调了一万年，最后少了标题的特判没能赛时战胜此题。玉玉了。

问题不弱于区间逆序对，考虑根号做法。

容易二分把那个 $\sum c_i=d$ 的条件转化成 $r$ 在一个区间内，那么问题变成：

> 给出 $l,L,R$，求区间 $[l,L],\dots,[l,R]$ 的逆序对个数和。

考虑答案等于 $[l,L-1]$ 内部的贡献乘以 $R-L+1$ 和 $[L,R]$ 内每个 $i$ 与 $[l,i-1]$ 的贡献之和。前者是莫队二次离线板子。

后者，考虑以 $B=\mathcal{O}(\sqrt n)$ 为块长分块。考虑整块和散块内的 $i$ 的贡献。

离线逐块处理。记当前块的端点为 $bl,br$。记 $p_i$ 表示 $i$ 作为逆序对右边那个数的贡献，则一个块对一个询问的贡献中，$p_i$ 的系数构成公差为 $-1$ 的等差数列。把系数平移一下使得右端点贡献系数为 $1$。这样还要再加上整个块的贡献乘上一个常数。

对于 $p_i$，容易将其差分成 $[1,i-1]$ 和 $[1,l-1]$ 两部分贡献之差。对于 $[1,i-1]$ 的部分，又可以表示成 $[1,bl-1]$ 和 $[bl,i-1]$ 两部分贡献的和。

于是记 $P_i$ 表示当前块和前 $i$ 个数的贡献，扫描 $i$，每次考虑这个 $i$ 可以和块中的哪些元素贡献，则需要支持单点修改区间查询。使用 $\mathcal{O}(\sqrt n)-\mathcal{O}(1)$ 的分块即可。

对于剩下的贡献，形如块中每个位置到块左端点的这一段前缀。由于块中每一个元素对应的前缀都被整块包含，因此只需要知道所有前缀贡献的和而不需要知道每一个位置的贡献。考虑每个位置会贡献给哪些前缀，于是可以从块左端点扫描，每次先把自己删除，再查询。

其实这里只有 $\mathcal{O}(n)$ 次查询和修改，可以提前 BIT 预处理。

至于散块，一共只有 $\mathcal{O}(m\sqrt n)$ 次查询单点的贡献。考虑暴力累加。将单点的贡献差分为 $[1,i-1]$ 和 $[1,l-1]$，将整个散块挂在 $l-1$ 上，然后扫描线。这样对于一个位置 $k$ 上的所有询问，其散块贡献的 $[1,l-1]$ 这部分就可以在扫到 $k$ 时依次查询累加。至于 $[1,i-1]$ 的贡献，已经在莫二离的时候预处理好了，顺带加上即可。

认为 $n,m$ 同阶，时间复杂度 $\mathcal{O}(n\sqrt n)$，空间复杂度 $\mathcal{O}(n)$。

代码不算很好写。


```cpp
#include <bits/stdc++.h>
//#define int long long
#define ll long long
using namespace std; const int N = 100005;
int n, a[N], c[N], b[N], q, tot, cq, B;
ll pre[N], pre2[N], p1[N], p2[N], d[N], ans[N], val[N];
int ql[N], qr[N], lft[N];
struct BLK {
	int B, bl[N], br[N], be[N]; ll a[N], t[N];
	void I(int n) {
		B = sqrt(n); for (int i = 1; i <= n; ++i) be[i] = (i - 1) / B + 1;
		for (int i = 1; i <= be[n]; ++i)
			bl[i] = br[i - 1] + 1, br[i] = min(n, i * B);
	}
	void C() { memset(a, 0, sizeof a); memset(t, 0, sizeof t); }
	void S(int l, int r, int v) { for (int i = l; i <= r; ++i) a[i] += v; }
	void U(int l, int r, int v) {
		if (be[l] == be[r]) return S(l, r, v); S(l, br[be[l]], v);
		S(bl[be[r]], r, v); for (int i = be[l] + 1; i < be[r]; ++i) t[i] += v;
	}
	int Q(int x) { return a[x] + t[be[x]]; }
	int Q(int l, int r) { return l > r ? 0 : Q(r) - Q(l - 1); }
} ds, ds2;
struct queries { int l, r, v, id; } Qr[N]; vector<queries> g[N], h[N], G[N];
signed main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0); cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i] >> c[i], c[i] += c[i - 1], b[i] = a[i];
	stable_sort(b + 1, b + n + 1); tot = unique(b + 1, b + n + 1) - b - 1;
	ds.I(tot); ds2.I(tot);
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b,
		p1[i] = ds.Q(a[i] + 1, tot), ds.U(a[i], tot, 1), p2[i] = ds.Q(a[i] - 1);
	cin >> q; B = sqrt(n);// B = 1;
	//B = 1;
	//B = 400;
	for (int i = 1, l, d; i <= q; ++i) {
		cin >> l >> d; lft[i] = l;
		int fl = l, fr = n, f = 0, g = 0;
		while (fl <= fr) {
			int m = fl + fr >> 1;
			if (c[m] - c[l - 1] >= d) f = m, fr = m - 1;
			else fl = m + 1;
		}
		if (!f || c[f] - c[l - 1] > d) continue;
		fl = f, fr = n;
		while (fl <= fr) {
			int m = fl + fr >> 1;
			if (c[m] - c[l - 1] <= d) g = m, fl = m + 1;
			else fr = m - 1;
		}
		if (f > l) {
			Qr[++cq] = {l, f - 1, l / B, i};
			val[i] = g - f + 1;
		}
		ql[i] = f; qr[i] = g;
		//cout << f << ' ' << g << '\n';
	}
	stable_sort(Qr + 1, Qr + cq + 1, [&](queries x, queries y) {
		return x.v != y.v ? x.v < y.v : x.v & 1 ? x.r < y.r : x.r > y.r;
	});
	for (int i = 1, l = 1, r = 0; i <= cq; ++i) {
		if (l > Qr[i].l) {
			g[r].emplace_back(queries{Qr[i].l, l - 1, 1, i});
			for (; l > Qr[i].l; --l) d[i] -= p2[l - 1];
		}
		if (r < Qr[i].r) {
			h[l - 1].emplace_back(queries{r + 1, Qr[i].r, -1, i});
			for (; r < Qr[i].r; ++r) d[i] += p1[r + 1];
		}
		if (l < Qr[i].l) {
			g[r].emplace_back(queries{l, Qr[i].l - 1, -1, i});
			for (; l < Qr[i].l; ++l) d[i] += p2[l];
		}
		if (r > Qr[i].r) {
			h[l - 1].emplace_back(queries{Qr[i].r + 1, r, 1, i});
			for (; r > Qr[i].r; --r) d[i] -= p1[r];
		}
	}
	ds.C();
	for (int i = 1; i <= n; ++i) {
		ds.U(a[i], tot, 1);
		for (auto [l, r, v, id] : g[i])
			for (int j = l; j <= r; ++j) d[id] += 1ll * v * ds.Q(a[j] - 1);
		for (auto [l, r, v, id] : h[i])
			for (int j = l; j <= r; ++j) d[id] += 1ll * v * ds.Q(a[j] + 1, tot);
	}
	for (int i = 1; i <= cq; ++i) ans[Qr[i].id] = ans[Qr[i - 1].id] + d[i];
	for (int i = 1; i <= cq; ++i) ans[Qr[i].id] *= val[Qr[i].id];
	ds.C();
	int ccnt = 0;
	for (int i = 1; i <= (n - 1) / B + 1; ++i) {
		int l = (i - 1) * B + 1, r = min(i * B, n);
		for (int j = l; j <= r; ++j) {
			ds.U(a[j], tot, r - j + 1);
			ds2.U(a[j], tot, 1);
		}
		for (int j = 1; j < l; ++j) {
			pre[j] = pre[j - 1] + ds.Q(1, a[j] - 1);
			pre2[j] = pre2[j - 1] + ds2.Q(1, a[j] - 1);
		}
		ll tmp = 0, tmp2 = 0;
		for (int j = l; j <= r; ++j) {
			ds.U(a[j], tot, j - r - 1);
			ds2.U(a[j], tot, -1);
			tmp += ds.Q(1, a[j] - 1);
			tmp2 += ds2.Q(1, a[j] - 1);
		}
		//cout << tmp << '\n';
		for (int j = 1; j <= q; ++j) {
			if (qr[j] < l || ql[j] > r) continue;
			if (!ql[j]) continue;
			if (ql[j] <= l && r <= qr[j]) {
				ans[j] += pre[l - 1] - pre[lft[j] - 1] + tmp;
				ans[j] += 1ll * (pre2[l - 1] - pre2[lft[j] - 1] + tmp2) * (qr[j] - r);
			} else {
				++ccnt;
				int lo = max(l, ql[j]), rr = min(r, qr[j]);
				if (lft[j] == 1) {
					for (int k = lo; k <= rr; ++k) ans[j] += 1ll * p1[k] * (qr[j] - k + 1);
				} else G[lft[j] - 1].emplace_back(queries{lo, rr, -1, j});
			}
		}
	}
	ds.C();
	assert(ccnt <= 10 * N);
	for (int i = 1; i <= n; ++i) {
		ds.U(a[i], tot, 1);
		for (auto [l, r, v, id] : G[i]) {
			for (int j = l; j <= r; ++j) {
				ans[id] += 1ll * (qr[id] - j + 1) * (p1[j] - ds.Q(a[j] + 1, tot));
			}
		}
	}
	for (int i = 1; i <= q; ++i) cout << ans[i] << '\n';
	return 0;
}
/*
6
5 0
1 0
4 0
1 0
1 0
4 0
1
1 1
*/
```

---

