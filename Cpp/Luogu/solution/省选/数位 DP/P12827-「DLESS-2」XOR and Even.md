# 「DLESS-2」XOR and Even

## 题目描述

给定一个长度为 $n$ 的非负整数序列 $a$，$q$ 次询问，每次询问形如以下两种中的一种：

- ```0 l r x```: 在区间 $[l,r]$ 中选出**偶数**个数（可以是 $0$ 个，此时异或和为 $0$，下同），使得这些数的异或和小于等于 $x$，求方案数，答案对 $10^9+7$ 取模。
- ```1 l r x```: 在区间 $[l,r]$ 中选出**偶数**个数，使得这些数的异或和异或上 $x$ 最大，求这个最大值。

## 说明/提示

对于所有数据，保证：

- $1\le T\le 10^4$
- $1\le n,\sum n\le 5\times10^5$
- $1\le q,\sum q\le 5\times10^5$
- $1\le l<r\le n$
- $0\le a_i,x<2^{30}$

**本题采用捆绑测试**，各子任务描述如下：

| Subtask | $\sum n\le$ | $\sum q\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $10$ | $1000$ | 无 | $10$ |
| $2$ | $1000$ | $1000$ | A | $15$ |
| $3$ | $1000$ | $1000$ | B | $15$ |
| $4$ | $1000$ | $1000$ | 无 | $10$ |
| $5$ | $5\times10^4$ | $5\times10^4$ | 无 | $10$ |
| $6$ | $5\times10^5$ | $5\times10^5$ | A | $15$ |
| $7$ | $5\times10^5$ | $5\times10^5$ | B | $15$ |
| $8$ | $5\times10^5$ | $5\times10^5$ | 无 | $10$ |

特殊性质 A：操作类型一定为 $0$。

特殊性质 B：操作类型一定为 $1$。

## 样例 #1

### 输入

```
2
5 6
1 2 4 8 16
0 1 3 3
0 1 4 3
1 2 4 0
1 2 4 1
0 1 5 114514
0 1 4 5
6 7
1 1 4 5 1 4
0 1 3 0
1 2 4 0
1 1 2 1
1 2 6 0
1 1 4 5
0 2 4 4
1 1 2 0```

### 输出

```
2
2
12
13
16
3
2
5
1
5
5
3
0```

# 题解

## 作者：luanyanjia (赞：11)

AI 做不出这种题吗，挺有道理的。

最开始做[这个题](https://www.luogu.com.cn/problem/P11620)的时候，我就想过如果区间异或上一个数时，如果简单地将线性基内的元素全部异或，那么只有偶数个元素的集合搞出来是正确的，所以直接做是不可行的，但在这个题上却刚刚好。

先用带时间戳的线性基把询问区间的线性基搞出来（要离线扫描线）。

对于第二种询问，我们将线性基中每一个数都异或 $2^{30}$，$x$ 也异或上 $2^{30}$，这样因为要贪心取最大值，所以最后的方案一定是取了偶数个数。否则答案不带 $2^{30}$ 一定更小。

对于第一种询问，我们同样地做，这样奇数个数的方案异或出来的值带有 $2^{30} > x$，所以一定不合法，求答案只需按位贪心，假设前面几位都顶到了上界，此时异或出来的值是确定的，然后分讨计算即可。最后答案要乘上 $2^{r-l+1-cnt}$（$cnt$ 是线性基的元素个数）。

分讨的部分可以看看代码。

```cpp
const int V=60;
struct Linear_Basis{
	int b[V+5],tm[V+5];
	inline void Insert(int x,int t,int st){
		for(int i=st;i>=0;i--){
			if((x>>i)&1){
				if(b[i]){
					if(tm[i]<t){
						Insert(x^b[i],tm[i],i-1);
						b[i]=x;tm[i]=t;
						break;
					}
					else x^=b[i];
				}else{
					b[i]=x;tm[i]=t;
					break;
				}
			}
		}
	}
	inline int Query(int x,int v){
		int now=v;
		for(int i=30;i>=0;i--)
			if(tm[i]>=x&&!(now>>i&1))
				now^=b[i];
		return now;
	}
    int c[60];
    inline int Get(int l,int r,int x){
        int cnt=0,ans=0,now=0;
        c[0]=(b[0]!=0)&&tm[0]>=l;
        for(int i=1;i<=30;i++)c[i]=c[i-1]+((b[i]!=0)&&tm[i]>=l);
        for(int i=30;i>=0;i--)if(tm[i]>=l&&b[i])++cnt;
        for(int i=30;;i--){
            if(i==-1){
                if(now<=x)Add(ans,1);
                break;
            }
            if(x>>i&1){
                if((now>>i&1)&&(b[i]&&tm[i]>=l))Add(ans,i?m2[c[i-1]]:1);
                if(!(now>>i&1)){
                    if(b[i]&&tm[i]>=l){
                        now^=b[i];
                        if(i)Add(ans,m2[c[i-1]]);
                        else Add(ans,1);
                    }else{
                        if(i)Add(ans,m2[c[i-1]]);
                        else Add(ans,1);
                        break;
                    }
                }
            }else{
                if(now>>i&1){
                    if(!b[i]||tm[i]<l)break;
                    else if(tm[i]>=l)now^=b[i];
                }
            }
        }
        ans=1ll*ans*m2[r-l+1-cnt]%mod;
        return ans;
    }
    inline void Clear(){
        memset(b,0,sizeof b);
        memset(tm,0,sizeof tm);
    }
}LB;
inline void Solve(){
    rd(n,q);
    for(int i=1;i<=n;i++)rd(a[i]);
    for(int i=1;i<=q;i++){
        int op,l,r,x;rd(op,l,r,x);
        vec[r].emplace_back(op,l,x,i);
    }
    LB.Clear();
    for(int i=1;i<=n;i++){
        LB.Insert(a[i]^(1<<30),i,30);
        for(auto[op,l,x,id]:vec[i]){
            if(op==1){
                ans[id]=LB.Query(l,x^(1<<30))^(1<<30);
            }else{
                ans[id]=LB.Get(l,i,x);
            }
        }
    }
    for(int i=1;i<=n;i++)vec[i].clear();
    for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
}
signed main(){
    m2[0]=1;
    for(int i=1;i<=500000;i++)m2[i]=m2[i-1]*2%mod;
    rd(T);
    while(T--)Solve();
    return 0;
}
```

---

## 作者：Gold14526 (赞：9)

### 做法一

考虑在 $a_l,a_{l+1},a_{l+2},\dots,a_{r}$ 中选出偶数个数等价于在 $a_l\oplus a_{l+1},a_{l+1}\oplus a_{l+2},\dots,a_{r-1}\oplus a_r$ 中选出若干个数。

所以我们直接建出异或差分后的线性基，然后直接就能解决询问类型 $1$，对于另一种询问，我们可以从高到低类似数位 dp 处理，时间复杂度 $O((n+q)\log V)$。

---

### 做法二

考虑询问 $0$：

把每个数加上 $2^{31}$，如果异或和要小于等于 $x$ 必须选偶数个数，于是直接建出线性基后数位 dp 即可。

考虑询问 $1$：

把每个数和 $x$ 都加上 $2^{31}$，如果异或和要最大必须选偶数个数，直接建出线性基贪心即可。

---

## 作者：Masterwei (赞：3)

线性基板子。

两个询问都是要选出偶数个数。考虑转化形式，最平常的就是直接进行差分，设 $b_i=a_i \oplus a_{i+1}$，那么原本在 $a$ 的区间 $[l,r]$ 内选偶数个数就转化为在 $b$ 的区间 $[l,r-1]$ 内选任意个数。

那么现在这个问题就被简化为线性基最普通的形式了。

类型 $1$ 的询问比较简单，直接求最大值。

对于类型 $0$ 的询问，我们考虑一位一位去考虑。

具体的，我们从高位到低位扫线性基，设当前扫到第 $i$ 位，那么如果 $x$ 的第 $i$ 位是 $1$，我们可以计算这一位为 $0$ 的时候的答案，然后继续扫，以计算这一位为 $1$ 的答案。设线性基后面的位中有 $cnt$ 个数，根据线性基构造的唯一性，这一位为 $0$ 对答案的贡献就是 $2^{cnt}$。

但这只是线性基内对答案的贡献，我们还要考虑线性基之外的。设有 $tot$ 个数不在线性基中，那么将答案乘上 $2^{tot}$ 即可。

区间询问，写个猫树分治即可。

时间复杂度 $O(n\log n\log V)$，时间戳线性基能单 $\log$。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=5e5+5,mod=1e9+7;
int n,q;
int a[Maxn];
int ans[Maxn];
struct Query{
	int op,l,r,x,id;
};
int pw[Maxn];
struct XOR{
	int f[31]={0},cnt=0;
	inline void clear(){
		cnt=0;
		for(int i=0;i<=30;i++)f[i]=0;
	}
	inline void insert(int x){
		for(int i=29;~i;i--)
			if((x>>i)&1){
				if(!f[i]){f[i]=x;cnt++;return;}
				x^=f[i];
			}
	}
	inline int query(int x){
		for(int i=29;~i;i--)x=max(x,x^f[i]);
		return x;
	}
	inline int sol(int len,int x){
		int now=0,del=0,ans=0;
		for(int i=29;~i;i--){
			del+=(f[i]>0);
			if((x>>i)&1){
				if(((now>>i)&1)&&f[i]){
					ans=(ans+pw[cnt-del])%mod;
				}
				if(!((now>>i)&1)){
					ans=(ans+pw[cnt-del])%mod;
					if(!f[i])break;
					now^=f[i];
				}
			}else{
				if((now>>i)&1){
					if(!f[i])break;
					now^=f[i];
				}
			}
			if(i==0)ans=(ans+1)%mod;
		}
		return 1ll*ans*pw[len-cnt]%mod;
	}
}pre[Maxn],suf[Maxn];
inline XOR merge(XOR a,XOR b){
	for(int i=0;i<30;i++)if(b.f[i])a.insert(b.f[i]);
	return a;
}

void solve(int l,int r,vector<Query>Q){
	if(Q.empty())return;
	if(l==r){
		XOR h;h.clear();h.insert(a[l]);
		for(Query it:Q){
			if(it.op==0)ans[it.id]=h.sol(1,it.x);
			else ans[it.id]=h.query(it.x);
		}
		return;
	}
	int mid=l+r>>1;
	vector<Query>Ql,Qr;pre[mid+1].clear();
	for(int i=mid;i>=l;i--)pre[i].clear(),pre[i]=pre[i+1],pre[i].insert(a[i]);
	suf[mid].clear();
	for(int i=mid+1;i<=r;i++)suf[i].clear(),suf[i]=suf[i-1],suf[i].insert(a[i]);
	XOR h;
	for(Query it:Q){
		if(it.r<=mid)Ql.push_back(it);
		else if(it.l>mid)Qr.push_back(it);
		else{
			h.clear();h=merge(pre[it.l],suf[it.r]);
			if(it.op==0)ans[it.id]=h.sol(it.r-it.l+1,it.x);
			else ans[it.id]=h.query(it.x);
		}
	}
	
	solve(l,mid,Ql);solve(mid+1,r,Qr);
}

inline void Main(){
	n=read();q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++)a[i]=(a[i]^a[i+1]);
	vector<Query>b;
	for(int i=1;i<=q;i++){
		b.push_back({read(),read(),read()-1,read(),i});
	}
	solve(1,n-1,b);
	for(int i=1;i<=q;i++)printf("%d\n",ans[i]);
}
signed main(){
	int T=read();
	pw[0]=1;for(int i=1;i<=5e5;i++)pw[i]=(pw[i-1]+pw[i-1])%mod;
	while(T--)Main();
	return 0;
}


```

---

## 作者：XZhuRen (赞：3)

为运算用 $\oplus,\And,|$ 表示。

$\mathcal{O}(q\log^2n)$ 能冲过 qwq。

对于序列中的数 $a_i\to a_i\oplus 2^{30}$，一类询问 $x\to x\oplus 2^{30}$。

直接对原序列猫树分治，则我们做一个前缀线性基，另一边扫描，扫到的时候合并。

零类询问合并后暴力做求 $x$ 的 $rank$，注意要 $rank+1$ 后乘上 $0$ 个数。

一类询问合并后暴力求 $\max$。

没了，两个 $\log$ 即可冲过，注意零询问别写二分。

```cpp

#include<bits/stdc++.h>
using namespace std;
typedef long long ll1;
const int N=5e5+5;
const int M=1e6+5;
const int KK=30;
const ll1 mod=1e9+7;
const int SB=1<<30;
const int inf=INT_MAX;
int d[KK+1],cnt=0;
ll1 pow2[N];
struct xorbase{
	int b[KK+1],cnt0=0;
	void ins(int x){
		for(int k=KK;k>=0;k--){
			if(((x>>k)&1)){
				if(b[k])x^=b[k];
				else{b[k]=x;return;}
			}
		}
		cnt0++;
		return;
	}
	void rebuild(){
		cnt=0;
		for(int i=0;i<=KK;i++){
			for(int j=i-1;j>=0;j--)
				if(b[i]&(1ll<<j))b[i]^=b[j];
			if(b[i])d[cnt++]=b[i];
		}
	}
	int qk(int k){
		int ans=0;
		for(int i=0;i<cnt;i++)
			if((k>>i)&1)ans^=d[i];
		return ans;
	}
	int qrank(int x){
		rebuild();
		ll1 lt=1,rt=1ll<<cnt,md=0,ans=0;
		// while(lt<=rt){
		// 	md=(lt+rt)>>1;
		// 	if(qk(md)<=x)ans=md,lt=md+1;
		// 	else rt=md-1;
		// }
		int nw=0;
		for(int i=cnt-1;i>=0;i--){
			if((nw^(d[i]))<=x){
				nw^=d[i],ans|=(1ll<<i);
			}
			// if((k>>i)&1)ans^=d[i];
		}
		ans++;
		ans=ans%mod*pow2[cnt0]%mod;
		return ans;
	}
	int qmx(int x){
		int ans=x;
		for(int k=KK;k>=0;k--)
			if((ans^b[k])>ans)ans^=b[k];
		return ans;
	}
	void clear(){cnt0=0;memset(b,0,sizeof b);}
	void operator +=(const xorbase &o){
		cnt0+=o.cnt0;
		for(int k=KK;k>=0;k--)if(o.b[k])ins(o.b[k]);
	}
}bs[N],tbs,bs1;
int n,q,Ans[N],a[N];
struct qrys{
	int l,r,val,id;
	bool operator<(const qrys &o)const{return l>o.l;}
};vector<qrys>qs[M];
#define ls (o<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
void ins(int o,int l,int r,int lt,int rt,int x,int id){
	if(lt<=mid&&rt>mid||rt==mid||lt==mid+1){qs[o].emplace_back((qrys){lt,rt,x,id});return;}
	if(l!=r-1)
	rt<=mid?ins(ls,l,mid,lt,rt,x,id):ins(rs,mid,r,lt,rt,x,id);
}
void solve(int o,int l,int r){
	tbs.clear(),bs[mid].clear();
	for(int i=mid+1;i<=r;i++){
		bs[i]=bs[i-1],bs[i].ins(a[i]);
	}
	sort(qs[o].begin(),qs[o].end());
	int nw=0;
	for(int i=mid+1;i>=l;i--){
		if(i<=mid)tbs.ins(a[i]);
		while(nw<int(qs[o].size())){
			auto cq=qs[o][nw];
			if(cq.l==i){
				bs1=tbs;
				bs1+=bs[cq.r];
				if(cq.id<0){
					Ans[-cq.id]=bs1.qrank(cq.val);
				}else Ans[cq.id]=bs1.qmx(cq.val)^SB;
				nw++;
			}else break;
		}
	}
	if(l!=r-1)solve(ls,l,mid),solve(rs,mid,r);
}
#undef ls
#undef rs
#undef mid
void init(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=(n<<2);i++)qs[i].clear();
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]),a[i]^=SB;
	for(int t=1,l,r,x,op;t<=q;t++){
		scanf("%d%d%d%d",&op,&l,&r,&x);
		ins(1,1,n,l,r,op?x^SB:x,op?t:-t);
	}
}
void work(){
	solve(1,1,n);
	for(int i=1;i<=q;i++)printf("%d\n",Ans[i]);
}
int main(){
	pow2[0]=1;
	for(int i=1;i<=500000;i++)pow2[i]=pow2[i-1]*2%mod;
	int T;
	scanf("%d",&T);
	while(T--){
		init();
		work();
	}
	return 0;
}

```

---

## 作者：masterhuang (赞：2)

区间选偶数个数异或：相当于你 $a'_{i}\gets a_{i}\bigoplus a_{i+1}$，然后条件等价于 $[l,r-1]$ 中选任意数异或。

同理：选奇数个数我们直接强制钦定选 $a_l$，然后再在 $a'$ 的 $[l,r-1]$​ 中选任意数异或即可。

---

有另一个很巧妙的思想：由于都是要求**值不超过某个数**，你可以给所有数的最高位更高的地方都填上 $1$，这样必须选偶数个数才能达到不超过的条件。

奇数和上面同理，钦定 $a_l$ 必选。

---

然后异或最大值是好求的，$\le x$ 方案数那个**考虑单侧递归**，本来是 $2^{\text{线性基大小}}$ 的枚举，但是注意到每层只有一个有效值（二进制前缀与 $x$ 相等），否则恒 $<x$ 或 $>x$​，直接计算答案即可。于是单侧递归，单次复杂度仍然为线性基大小。

---

这两种做法是等价的。本质上是在干什么呢？是给原来二进制数加上一个 $01$ 占位符，表示选不选，然后最后偶数奇数就看占位符。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define fi first
#define se second
#define fr(x) freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);
using namespace std;
namespace IO
{
	const int _Pu=2e7+5,_d=32;
	char buf[_Pu],obuf[_Pu],*p1=buf+_Pu,*p2=buf+_Pu,*p3=obuf,*p4=obuf+_Pu-_d;
	inline void fin()
	{
		memmove(buf,p1,p2-p1);
		int rlen=fread(buf+(p2-p1),1,p1-buf,stdin);
		if(p1-rlen>buf) buf[p2-p1+rlen]=EOF;p1=buf;
	}
	inline void fout(){fwrite(obuf,p3-obuf,1,stdout),p3=obuf;}
	inline int rd()
	{
		if(p1+_d>p2) fin();int isne=0,x=0;
		for(;!isdigit(*p1);++p1) isne=(*p1=='-');x=(*p1++-'0');
	    for(;isdigit(*p1);++p1) x=x*10+(*p1-'0');
		if(isne) x=-x;return x;
	}
	inline void wr(int x,char end='\n')
	{
		if(!x) return *p3++='0',*p3++=end,void();
		if(x<0) *p3++='-',x=-x;
		char sta[20],*top=sta;
		do{*top++=(x%10)+'0';x/=10;}while(x);
		do{*p3++=*--top;}while(top!=sta);(*p3++)=end;
	}
}using IO::rd;using IO::wr;
const int N=5e5+5,mod=1e9+7,U=2147483647;
int T,n,m,a[N],p2[N],s,lim,B[N][31],p[N][31];
vector<pair<int,int>>b;
inline int md(int x){return x>=mod?x-mod:x;}
inline void ins(int w,int x)
{
	for(int i=29;~i;i--) B[w][i]=B[w-1][i],p[w][i]=p[w-1][i];
	for(int i=29,nw=w;~i&&x;i--) if(x>>i&1)
	{
		if(B[w][i])
		{
			if(nw>p[w][i]) swap(p[w][i],nw),swap(B[w][i],x);
			x^=B[w][i];	
		}
		else{p[w][i]=nw,B[w][i]=x;break;}
	}
	
}
inline void get(int l,int r){
	for(int i=29;~i;i--) if(p[r][i]>=l) b.push_back({B[r][i],i});
}
void dfs(int w,int x)
{
	if(w==n) return s+=(x<=lim),void();
	int t=U^((1<<(b[w].se+1))-1),y=x&t,z=lim&t;
	if(y>z) return;
	if(y<z) s=md(s+p2[n-w]);
	else dfs(w+1,x),dfs(w+1,x^b[w].fi);
}
int main()
{
	T=rd();
	for(int i=*p2=1;i<=5e5;i++) p2[i]=md(p2[i-1]<<1);
	while(T--)
	{
		n=rd(),m=rd();
		for(int i=1;i<=n;i++) a[i]=rd();
		for(int i=1;i<n;i++) ins(i,a[i]^=a[i+1]);
		for(int o,l,r,x;m--;)
		{
			o=rd(),l=rd(),r=rd(),x=rd();
			if(l==r){wr(o?x:1);continue;}
			b.clear();get(l,r-1);
			if(o){for(auto i:b) x=max(x^i.fi,x);wr(x);}
			else
			{
				n=b.size();s=0;lim=x;
				dfs(0,0);wr(1ll*s*p2[r-l-n]%mod);
			}
		}
	}
	return IO::fout(),0;
}
```

---

