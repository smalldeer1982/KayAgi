# Friends

## 题目描述

You have $ n $ friends and you want to take $ m $ pictures of them. Exactly two of your friends should appear in each picture and no two pictures should contain the same pair of your friends. So if you have $ n=3 $ friends you can take $ 3 $ different pictures, each containing a pair of your friends.

Each of your friends has an attractiveness level which is specified by the integer number $ a_{i} $ for the $ i $ -th friend. You know that the attractiveness of a picture containing the $ i $ -th and the $ j $ -th friends is equal to the exclusive-or ( $ xor $ operation) of integers $ a_{i} $ and $ a_{j} $ .

You want to take pictures in a way that the total sum of attractiveness of your pictures is maximized. You have to calculate this value. Since the result may not fit in a 32-bit integer number, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
3 1
1 2 3
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 2
1 2 3
```

### 输出

```
5
```

## 样例 #3

### 输入

```
3 3
1 2 3
```

### 输出

```
6
```

# 题解

## 作者：syzf2222 (赞：27)

[更好的阅读体验](https://www.cnblogs.com/syzf2222/p/14324732.html)

思路：先二分出$k$大值，在计算比$k$大值大的和。

$part 1:$二分求$k$大值

考虑建一棵$01trie$，每次二分值$mid$，枚举每个数，记异或值大于等于$mid$的数量。

二分一个$log$，枚举每个数是$\Theta(n)$，查询异或值大于等于$mid$的数量是一个$log$，故此部分复杂度$\Theta(n\log^2n)$。

```
inline long long check(int x){
	long long tot=0;
	for(int i=1;i<=n;i++){
		int u=0;
		for(int j=30;j>=0;j--){
			int t1=((1<<j)&a[i])!=0;
			int t2=((1<<j)&x)!=0;
			if(!t2)tot+=val[ch[u][t1^1]],u=ch[u][t1];
			else u=ch[u][t1^1];
			if(!u)break;
		}
		tot+=val[u];
	}
	return tot/2;
}
```
```
int l=0,r=1<<30,kth=0;
while(l<=r){
	int mid=(l+r)>>1;
	if(check(mid)>=k)kth=mid,l=mid+1;
	else r=mid-1;
}
```
$part 2:$计算异或值中大于等于$k$大值的和

预处理$tr$数组，$tr[x][y]$表示在$x$子树中的叶子节点上有多少个数的$2^y$上是$1$。

```
inline void pre(int x,int dep,int z){
	if(x==0)return;
	if(dep==0){
		for(int i=0;i<=30;i++)
			if((1<<i)&z)tr[x][i]=val[x];
		return;
	}
	pre(ch[x][0],dep-1,z);
	pre(ch[x][1],dep-1,z|(1<<dep-1));
	for(int i=0;i<=30;i++)
		tr[x][i]=tr[ch[x][0]][i]+tr[ch[x][1]][i];
}
```

$tr$数组使我们可以计算整棵子树异或一个数的和。

接着就可以在$01trie$上计算了。

枚举每一个数，走一遍$01trie$，遇见可以直接加的就枚举每一位，计算贡献。

这一部分的复杂度也是$\Theta(n\log^2n)$。

```
inline void solve(int kth){
	for(int i=1;i<=n;i++){
		int u=0;
		for(int j=30;j>=0;j--){
			int t1=((1<<j)&a[i])!=0;
			int t2=((1<<j)&kth)!=0;
			if(!t2){
				int t=ch[u][t1^1];
				for(int k=0;k<=30;k++){
					int t3=((1<<k)&a[i])!=0;
					if(t3)ans=(ans+1ll*(val[t]-tr[t][k])*(1ll<<k))%mod;
					else ans=(ans+1ll*tr[t][k]*(1ll<<k))%mod;
				}u=ch[u][t1];
			}else u=ch[u][t1^1];
			if(u==0)break;
		}
		ans=(ans+1ll*val[u]*kth)%mod;
	}
}
```

注意：

1.每一个值被计算了两次，故答案要除以$2$。
```
ans=ans*inv2%mod;
```
2.可能$k$大值与$k+1,k+2,k+3……$大值相等，注意最后要减掉这些“凑合的”。
```
ans=((ans-1ll*(check(kth)-k)*kth%mod)%mod+mod)%mod;
```

放上完整代码，以供参考：
```
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4+10;
const int mod=1e9+7;
const int inv2=5e8+4;
int n,a[maxn];
long long ans,k;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int ch[maxn*20][2],val[maxn*20],cnt;
inline void insert(int x){
	int u=0;
	for(int i=30;i>=0;i--){
		int t=((1<<i)&x)!=0;
		if(!ch[u][t])ch[u][t]=++cnt;
		u=ch[u][t];val[u]++;
	}
}
inline long long check(int x){
	long long tot=0;
	for(int i=1;i<=n;i++){
		int u=0;
		for(int j=30;j>=0;j--){
			int t1=((1<<j)&a[i])!=0;
			int t2=((1<<j)&x)!=0;
			if(!t2)tot+=val[ch[u][t1^1]],u=ch[u][t1];
			else u=ch[u][t1^1];
			if(!u)break;
		}
		tot+=val[u];
	}
	return tot/2;
}
int tr[maxn*20][35];
inline void pre(int x,int dep,int z){
	if(x==0)return;
	if(dep==0){
		for(int i=0;i<=30;i++)
			if((1<<i)&z)tr[x][i]=val[x];
		return;
	}
	pre(ch[x][0],dep-1,z);
	pre(ch[x][1],dep-1,z|(1<<dep-1));
	for(int i=0;i<=30;i++)
		tr[x][i]=tr[ch[x][0]][i]+tr[ch[x][1]][i];
}
inline void solve(int kth){
	for(int i=1;i<=n;i++){
		int u=0;
		for(int j=30;j>=0;j--){
			int t1=((1<<j)&a[i])!=0;
			int t2=((1<<j)&kth)!=0;
			if(!t2){
				int t=ch[u][t1^1];
				for(int k=0;k<=30;k++){
					int t3=((1<<k)&a[i])!=0;
					if(t3)ans=(ans+1ll*(val[t]-tr[t][k])*(1ll<<k))%mod;
					else ans=(ans+1ll*tr[t][k]*(1ll<<k))%mod;
				}u=ch[u][t1];
				//printf("%lld %lld %lld\n",i,j,ans);
			}else u=ch[u][t1^1];
			if(u==0)break;
		}
		ans=(ans+1ll*val[u]*kth)%mod;
		//printf("%lld %lld\n",i,ans);
	}
}
int main(){
	n=read();scanf("%lld",&k);
	if(!k)return puts("0"),0;
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		insert(a[i]);
	int l=0,r=1<<30,kth=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)>=k)kth=mid,l=mid+1;
		else r=mid-1;
	}
	pre(ch[0][0],30,0);
	pre(ch[0][1],30,1<<30);
	solve(kth);//printf("%lld\n",ans);
	ans=ans*inv2%mod;
	ans=((ans-1ll*(check(kth)-k)*kth%mod)%mod+mod)%mod;
	printf("%lld\n",ans);
	return 0;
}
```
深深地感到自己的弱小。

---

## 作者：tommymio (赞：25)

[$\texttt{可能更好的阅读体验}$](https://www.cnblogs.com/tommy0103/p/13050433.html)

## 链接

[CodeForces 241B](https://codeforces.com/problemset/problem/241/B)

## 题意

给定一个长度为 $N$ 的序列，求前 $k$ 大的 $a_i \operatorname{xor} a_j$ 之和，答案对 $10^9+7$ 取模。

其中 $a_i \operatorname{xor} a_j$ 与 $a_j \operatorname{xor} a_i$ 被看成是同一对。

$\texttt{Data Range:}1\leq n\leq 10^6,1\leq k\leq \frac{n(n-1)}{2}$。

## 约定

以下称 $a_i \operatorname{xor} a_j$ 的值为异或值。

$b_v[i..j]$ 为值 $v$ 在 **二进制意义** 下第 $i$ 位至第 $j$ 位的取值，如 $b_3[0..1]=11_2$，$b_5[1..2]=10_2$，$b_5[0,2]=101_2$（下标 $2$ 即表示二进制意义下）。

二进制意义下的最高位为 $mx$。  

## 题解

此题是 **[十二省联考2019]异或粽子** 的加强版，解法吊打 $\texttt{std}$。

提供了一种时间复杂度与 $k$ 无关的解法，时间复杂度为 $O(n\omega^2+n\log n)$，其中 $\omega$ 是一个常数，意义为在二进制意义下 $a_i$ 的最高位，在本题中 $\omega \approx 29$。

首先可以想到，要求出前 $k$ 大的异或和，必须先求出第 $k$ 大的异或和。

有一种很暴力的做法，枚举每个 $a_i,a_j$，求出第 $k$ 大的异或值。无疑可以优化，枚举每一个 $a_i$，将上述过程放至 $\texttt{trie}$ 上，从高位贪心，用类似权值线段树求第 $k$ 大的方式在 $\texttt{trie}$ 上二分即可。

更加具体地说，我们将一棵 $\texttt{trie}$ 分为 $n$ 层，第 $i$ 层的指针即 $a_i$ 所对应的 $a_j$ 的前缀。从最高位开始枚举第 $k$ 大的 $a_i \operatorname{xor} a_j$ 的每一位上取 $0/1$，在枚举到第 $x$ 位时，在每一层上计算 $a_i \operatorname{xor} a_j$ 的第 $x$ 位为 $1$ 的方案数，记这个数为 $cnt$。若 $cnt\geq k$，则说明这一位必须取 $1$，否则所求会小于第 $k$ 大。若 $cnt < k$，则说明这一位必须取 $0$ ，否则所求会大于第 $k$ 大。在 $n$ 层 $trie$ 上对应更新指针即可，并统计第 $x$ 位的取值，更新第 $k$ 大的异或值在 $x$ 上的取值即可。

求出第 $k$ 大的 $a_i \operatorname{xor} a_j$ 后，记其为 $val$。若 $val$ 第 $x$ 位上为 $0$，则若存在一个异或值 $t$，令$b_{val}[x+1..mx]=b_t[x+1..mx]$，仅在 $t$ 的第 $x$ 位上为 $1$，$t$ 一定大于 $val$ ，属于前 $k$ 大的取值。

考虑计算这部分值的贡献。仍然是从高位贪心，分成 $n$ 层。每层按照 $val$ 的值在 $\texttt{trie}$ 上递归，枚举值 $val$ 在二进制意义上为 $0$ 的那些位，统计仅在这一位上取 $1$ ，第 $x+1-mx$ 位上与 $val$ 在二进制意义下取值相同的那些异或值对答案造成的贡献。

由于即使确定了 $a_i$，$a_j$ 也是在一棵子树中，对一棵子树统计答案，不太好做。可以在初始时直接对 $a_i$ 排序，这样 **$\texttt{trie}$ 的一棵子树即对应了 $a$ 上一段连续的区间**。统计贡献时按位统计，对每一位上的 $0/1$ 分别维护一个前缀和，这样就可以了。

**Show the Code**
```cpp
#include<cstdio>
#include<algorithm>
typedef long long ll;
const ll mod=1e9+7;
int n,tot=0,rt=0;
int a[50005],tmp[50005];
int sum[35][50005][2];
int ch[1000005][2],size[1000005],l[1000005],r[1000005];
inline ll read() {
	register ll x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline ll Add(ll x,ll y) {return ((x+y)%mod+mod)%mod;}
inline ll pow(ll x,ll p) {
	ll res=1;
	for(;p;p>>=1) {if(p&1) res=res*x%mod;x=x*x%mod;}
	return res;
}
inline void insert(int val,int id) {
	if(!rt) rt=++tot,l[rt]=1,r[rt]=n;
	int p=rt;++size[rt];
	for(register int d=31;d>=0;--d) {
		int &nxt=ch[p][val>>d&1];
		if(!nxt) {nxt=++tot;l[nxt]=id;} 
		p=nxt;r[p]=id;++size[p];
	}
}
inline int getVal(ll &k) {
	int res=0;
	for(register int i=1;i<=n;++i) tmp[i]=rt;
	for(register int d=31;d>=0;--d) {//若当前取1的个数为cnt,cnt>k 
		int x=0;
		ll cnt=0;
		for(register int i=1;i<=n;++i) cnt+=size[ch[tmp[i]][(a[i]>>d&1)^1]];
		if(cnt>=k) res|=(1<<d),x=1;//cnt<k
		else k-=cnt,x=0;
		for(register int i=1;i<=n;++i) tmp[i]=ch[tmp[i]][(a[i]>>d&1)^x];
	}
	return res;
}
inline ll ask(int l,int r,int val) {
	if(!l||!r) return 0;
	ll res=0;
	for(register int d=31;d>=0;--d) res=Add(res,(ll)(sum[d][r][(val>>d&1)^1]-sum[d][l-1][(val>>d&1)^1])*((1ll<<d)%mod)%mod);
	return res;
}
inline ll getSum(ll k) {
	int val=getVal(k);
	ll res=val*k%mod;
	for(register int i=1;i<=n;++i) tmp[i]=rt;
	for(register int d=31;d>=0;--d) {
		int x=val>>d&1;
		if(!x) {for(register int i=1;i<=n;++i) res=Add(res,ask(l[ch[tmp[i]][(a[i]>>d&1)^1]],r[ch[tmp[i]][(a[i]>>d&1)^1]],a[i]));}
		for(register int i=1;i<=n;++i) tmp[i]=ch[tmp[i]][(a[i]>>d&1)^x];
	}
	return res;	
}
signed main() {
	n=read();
	ll k=read()*2ll;//25*1e8=2.5*1e9
	for(register int i=1;i<=n;++i) a[i]=read();
	std::sort(a+1,a+1+n);
	for(register int i=1;i<=n;++i) insert(a[i],i);
	for(register int i=1;i<=n;++i) {
		for(register int d=31;d>=0;--d) {
			sum[d][i][0]=sum[d][i-1][0];
			sum[d][i][1]=sum[d][i-1][1];
			++sum[d][i][a[i]>>d&1]; 
		}
	} 
	printf("%lld\n",getSum(k)*pow(2,mod-2)%mod);
	return 0;
}
```


---

## 作者：Alex_Wei (赞：4)

>  [CF241B Friends](https://www.luogu.com.cn/problem/CF241B)
>
>  题意简述：给出序列 $a_{[1,n]}$ 和 $m$，求出前 $m$ 大的 $a_i\oplus a_j\ (1\leq i<j\leq n)$ 的和。对 $10^9+7$ 取模。
>
>  $1\leq n\leq 5\times 10^4$，$0\leq m\leq \binom{n}{2}$，$0\leq a_i\leq 10^9$。

[P5283](https://www.luogu.com.cn/problem/P5283) 的加强版，不过复杂度稍劣了些。

具体来说，我们可以二分找到第 $k$ 大的异或和 $v$，再求出所有不小于 $v$ 的异或和的和。

首先，判断异或和 $\geq mid$ 的点对数量可以通过可持久化 Trie 来解决：Trie 上的每个节点维护落在该区间的数的个数。枚举 $i$，在 $T_n-T_i$ 这个 Trie 上查询。设 $a_i$ 和 $mid$ 当前位分别为 $c,t$，当前区间在 $T_i$ 和 $T_n$ 上的编号分别为 $x,y$。若 $t=0$ 表示当前位为 $c\oplus 1$ 的数都要被计算在内，则答案加上 $val_{son_{y,c\oplus 1}}-val_{son_{x,c\oplus 1}}$。然后向 $c\oplus t$ 儿子方向搜索即可。该部分时间复杂度 $n\log^2 w$，空间复杂度 $n\log w$，其中 $w$ 是值域。

所有不小于 $v$ 的异或和的和比较棘手。仍然枚举 $i$，因为 $(x+y)\oplus z$ 并不一定等于 $(x\oplus z)+(y\oplus z)$，所以不能单纯维护落在该区间的数的和。但是我们可以对每一位单独考虑：$s_{x,i}$ 表示值落在 $x$ 所表示区间的数有 $s_{x,i}$ 个第 $i$ 位为 $1$。查询时类似上面一部分，若 $t=0$ 则再枚举位数 $b$，若 $a_i$ 的第 $b$ 位为 $0$，则要记入第 $b$ 位为 $1$ 的数的个数，即为 $s_{y,b}-s_{x,b}$，反之亦然，个数为 $val_y-val_x-(s_{y,b}-s_{x,b})$。注意这里的 $x,y$ 其实应该是上一部分中的 $son_{x,c\oplus 1},son_{y,c\oplus 1}$。该部分时间复杂度 $n\log^2 w$，空间复杂度 $n\log^2 w$。

当然，这个解法仍有可以优化的地方：第一部分可以直接在 Trie 树上二分。设 $a_i$ 当前位为 $c_i$，判断 $\sum_{i=1}^{n-1}val_{son_{y,c_i\oplus 1}}-val_{son_{x,c_i\oplus 1}}$（记为 $cnt$）是否不小于 $m$，即 $a_i\oplus a_j$ 的当前位为 $1$ 的总方案数。若 $m\leq cnt$ 则表明第 $m$ 大的异或和当前位为 $1$，反之为 $0$ 且将 $m$ 减去 $cnt$，再向根据判断结果向对应方向继续查询即可。这样时间复杂度为 $n\log w$，可惜第二部分的时间复杂度无法优化。

空间复杂度的优化可以看其它题解。

注意开 long long，并且二分边界应该设为 $2^{30}$ 而不是单纯的 $10^9$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=5e4+5;
const int p=1e9+7;
const int B=30;

int n,m,a[N];
int node,R[N],ls[N<<5],rs[N<<5],val[N<<5],c[N<<5][B];
void modify(int pre,int &x,int p,int b){
	val[x=++node]=val[pre]+1,ls[x]=ls[pre],rs[x]=rs[pre];
	for(int i=0;i<B;i++)c[x][i]=c[pre][i]+(p>>i&1);
	if(b==0)return;
	if((p>>b-1)&1)modify(rs[pre],rs[x],p,b-1);
	else modify(ls[pre],ls[x],p,b-1);
}
ll query(int p,int k,int b,int x,int y){
	if(b==0)return val[y]-val[x];
	int bit=(p>>b-1)&1,t=(k>>b-1)&1;
	if(bit){
		if(t)return query(p,k,b-1,ls[x],ls[y]);
		else return val[ls[y]]-val[ls[x]]+query(p,k,b-1,rs[x],rs[y]);
	} 
	else{
		if(t)return query(p,k,b-1,rs[x],rs[y]);
		else return val[rs[y]]-val[rs[x]]+query(p,k,b-1,ls[x],ls[y]);
	}
}

ll cal(int x,int y,int p){
	ll ans=0;
	for(ll i=0;i<B;i++)
		if((p>>i)&1)ans+=(ll)(val[y]-val[x]-c[y][i]+c[x][i])<<i;
		else ans+=(ll)(c[y][i]-c[x][i])<<i;
	return ans;
}
ll sum(int p,int k,int b,int x,int y){
	if(b==0)return cal(x,y,p);
	int bt=(p>>b-1)&1,t=(k>>b-1)&1;
	if(bt){
		if(t)return sum(p,k,b-1,ls[x],ls[y]);
		else return cal(ls[x],ls[y],p)+sum(p,k,b-1,rs[x],rs[y]);
	}
	else{
		if(t)return sum(p,k,b-1,rs[x],rs[y]);
		else return cal(rs[x],rs[y],p)+sum(p,k,b-1,ls[x],ls[y]);
	}
}

int main(){
	cin>>n>>m;
	if(m==0)return cout<<0<<endl,0;
	for(int i=1;i<=n;i++)cin>>a[i],modify(R[i-1],R[i],a[i],B);
	ll l=0,r=1<<B,ans=0,cnt=0;
	while(l<r){
		ll mid=(l+r>>1)+1,cnt=0;
		for(int i=1;i<=n;i++)cnt=cnt+query(a[i],mid,B,R[i],R[n]);
		cnt>=m?l=mid:r=mid-1;
	}
	for(int i=1;i<n;i++)cnt=cnt+query(a[i],l,B,R[i],R[n]);
	for(int i=1;i<n;i++)ans+=sum(a[i],l,B,R[i],R[n]);
	cout<<(ans-(cnt-m)*l%p+p)%p<<endl;
	return 0;
}
```



---

## 作者：Limit (赞：4)

# 题目大意

给出一个序列 $a$,求 $a_i\oplus a_j$($i<j$)的前 $k$ 大值的和.

# 分析

~~本题是 [P5283](https://www.luogu.com.cn/problem/P5283) 升级版.~~

先消除 $i<j$ 的影响,只需要把 $k$ 乘二,最后答案除以二就可以了.

直接计算前 $k$ 大的和一看就很麻烦,如果知道了第 $k$ 大的值,那么就变成了计算小于等于这个值的所有方案的和,看起来就简单许多了.

计算 $k$ 大有一种非常 NB 的 $\mathcal{O}(n\log_2w)$($w$ 指值域)的做法,可惜的不会,所以来介绍一种更加简单粗暴的方法.

直接二分答案,在 `Check()` 的时候计算有多少对异或值大于等于 $middle$,这个可以直接在 01trie 上二分获得.总时间复杂度为 $\mathcal{O}(n\log_2^2w)$,因为计算所有和时的复杂度也是这个,所以对最终程序的效率影响并不是很大.

对于计算和的部分可以考虑先对 $a$ 数组排序,那么对于所有经过 trie 树上某个节点的数在 $a$ 中必定是一段区间,可以先将每个数拆成二进制,然后做一遍前缀和,那么对于一个数与一段区间上的数的异或和就可以 $\mathcal{O}(1)$ 计算了.具体做法和二分 $k$ 大值中的在 trie 上二分类似.

具体实现可能还有些许细节,这里就不展开了.

# 部分代码

```cpp
void Insert(int num,int id,int &now,int deep=LOG_NUM)//在 trie 中插入一个数
{
	if(!now)
	{
		trie[now=++trie_cnt].left=id;//计入这个节点的所对应的区间的左端点
	}
	trie[now].right=id;//每次都要更新右端点
	if(~deep)
	{
		bool p=num&(1<<deep);
		Insert(num,id,SON(p),deep-1);
		PushUp(now);
	}
	else
	{
		trie[now].size++;
	}
}
int QueryRank(int num,int top,int now,int deep=LOG_NUM)
{
	if(!now)
	{
		return 0;
	}
	if(~deep)
	{
		bool p=num&(1<<deep);
		if((1<<deep)<=top)//在 trie 上二分,建议自行理解意义
		{
			return QueryRank(num,top-(1<<deep),SON(p^1),deep-1);
		}
		else
		{
			return trie[SON(p^1)].size/*计算和的时候只要把这里改成对应节点的区间上的数与 num 的异或和的和*/+QueryRank(num,top,SON(p),deep-1);
		}
	}
	else
	{
		return trie[now].size;//对于叶节点直接返回所需要的信息
	}
}

...
    
//二分答案部分
bool Check(int middle)
{
	long long sum=0;
	REP(i,1,n)
	{
		sum+=QueryRank(arr[i],middle,root);//计算所有大于等于 middle 的数对的个数
	}
	return k<=sum;
}
int main()
{
	while(left<=right)//一个普通的二分答案
	{
		if(Check(middle=(left+right)>>1))
		{
			kth=middle;
			left=middle+1;
		}
		else
		{
			right=middle-1;
		}
	}
    ...
    //计算答案部分
	long long answer=0;
	REP(i,1,n)
	{
		answer+=QuerySum(arr[i],kth+1,root);//计算大于等于 kth+1 的所有数对的异或和的和
		k-=QueryRank(arr[i],kth+1,root);
	}
	answer+=k*kth;//对于第 k 大的异或值不能全部加上,只需要加上将其他数去掉之后剩下的个数个
	Writeln(answer/2);//最后答案除以二
}
```

[完整代码(提交记录)](https://codeforces.com/contest/241/submission/89996471)

---

## 作者：ExplodingKonjac (赞：3)

### [【原题链接】](https://www.luogu.com.cn/problem/CF241B)

介绍一下我在年级广播操练习的时候想到的 $O(n\log^2 V)$ 超慢解法（准最劣解）

貌似做法和题解区都不太一样，所以就来~~水~~题解了。

## 题目分析

按照套路，使用可持久化 $\text{01-Trie}$ 维护数对之间的异或。

首先一个很显然的东西，我们欲求前 $k$ 大和，必先求第 $k$ 大数。

## 求第 $k$ 大

我太菜了只会使用二分。。大概就是二分第 $k$ 大的值，然后 $O(n\log V)$ 地在每个版本的 $\text{01-Trie}$ 上二分，找到有多少个两两异或的数对比 $mid$ 小，$+1$ 后就是 $mid$ 的排名。如果这个排名 $>k$ 那么令 $l\gets mid+1$，否则 $r\gets mid$。

需要注意，**这里最终找到的 $l$ 是排名小于等于 $k$ 的最大的数**，所以统计答案时需要先统计 $>l$ 的答案，然后再加上 $l\times(l\text{ 被算了几次})$。

这部分复杂度 $O(n\log^2 V)$。

## 求前 $k$ 大和

首先考虑一下如何计算一个 $\text{01-Trie}$ 中大于某数的数的和。

为了方便起见，如果一个数 $x$ 在某个节点 $i$ 的子树中，我们称 $i$ 管辖了 $x$。

考虑拆位。每个节点开一个数组 `cnt[31]`。对于节点 $i$，$cnt_k$ 表示 $i$ 管辖的数中，有多少个数第 $k$ 位为 $1$（位从 $0$ 开始算）。可以得到，一个节点子树内所有的数的和就是 $\sum cnt_i\cdot 2^i$。

为什么要这么麻烦呢…因为统计答案时需要将整个 $\text{01-Trie}$ 异或一个值啊……如果需要异或的值某一位是 $1$，那么把 $cnt_i$ 变成 $siz-cnt_i$ 就行了。

可以计算子树的贡献，那么我们用 $\text{01-Trie}$ 上二分就可以找到答案了。

怎么维护 $cnt$？暴力加就行了。

这部分复杂度 $O(n\log^2 V)$。

## 关于空间

很遗憾，本做法的空间复杂度高达 $O(n\log^2 V)$，根本卡不过 $\text{256MB}$。

我们发现空间的瓶颈主要在 $cnt$ 数组。因为本题 $n\leq 5e4$，也就是说 $cnt$ 不会超过 $5e4$。可以用一个神奇的东西——`unsigned short` 储存。

然后就卡过去了。

## 代码实现

代码挺短的，就是跑得慢。

```cpp
#include <bits/stdc++.h>
using namespace std;

/*
省略100多行的快读快写模板
即下面的qin、qout
*/

typedef long long LL;
const int MOD=1e9+7;
int n,m,a[50005];
LL ans;
struct TrieNode
{
	unsigned short siz,cnt[31];
	int ch[2];
}t[2000005];
int cnt,rt[50005];
inline void update(int i,int v)
{
	for(int j=0;j<31;j++,v>>=1)
		if(v&1)	t[i].cnt[j]++;
}
inline int calc(int i,int v)
{
	LL res=0,bs=1;
	for(int j=0;j<31;j++,bs<<=1,v>>=1)
		if(v&1)	res=(res+(t[i].siz-t[i].cnt[j])*bs)%MOD;
		else	res=(res+t[i].cnt[j]*bs)%MOD;
	return res;
}
void insert(int &r,int v)
{
	t[++cnt]=t[r],r=cnt;
	int i=r;
	bool x;
	for(int j=30;j>=0;j--)
	{
		x=(v>>j)&1;
		t[++cnt]=t[t[i].ch[x]],t[i].ch[x]=cnt;
		t[i].siz++;
		update(i=t[i].ch[x],v);
	}
	t[i].siz++;
}
int getRank(int r,int v,int zt)
{
	int i=r,res=0;
	bool x,y;
	for(int j=30;j>=0;j--)
	{
		if(!i)	return res;
		x=(v>>j)&1,y=(zt>>j)&1;
		if(!x)	res+=t[t[i].ch[!y]].siz;
		i=t[i].ch[x^y];
	}
	return res;
}
int solve(int r,int v,int zt)
{
	int i=r,res=0;
	bool x,y;
	for(int j=30;j>=0;j--)
	{
		x=(v>>j)&1,y=(zt>>j)&1;
		if(!x)	res=(res+calc(t[i].ch[!y],zt))%MOD;
		i=t[i].ch[x^y];
	}
	return res;
}
int main()
{
	qin>>n>>m;
	for(int i=1;i<=n;i++)
		qin>>a[i],insert(rt[i]=rt[i-1],a[i]);
	int l=0,r=1<<30,mid,sum;
	while(l<r)
	{
		mid=(l+r)>>1,sum=1;
		for(int i=2;i<=n;i++)
			sum+=getRank(rt[i-1],mid,a[i]);
		if(sum>m)
			l=mid+1;
		else
			r=mid;
	}
	sum=0;
	for(int i=2;i<=n;i++)
	{
		sum+=getRank(rt[i-1],l,a[i]);
		ans=(ans+solve(rt[i-1],l,a[i]));
	}
	qout<<(ans+1ll*(m-sum)*l)%MOD;
//	return qout.flush(),0;
}
```


---

## 作者：Miko35 (赞：3)

题意简述：给定 $n$ 个整数 $a_{1\dots n}$，求两两异或前 $k$ 大的结果之和，其中$n \leq 5 \times 10^4 , 1 \leq a_i \leq 10^9$。

大体思路应该都差不多，这里写一种更加好写的想法以及一些细节的写法问题。

首先想到对于 $a$ 序列建出 01-trie，把这道题分为两个部分：

1. 找到第 $k$ 大的异或值 $R$。
2. 求前 $k$ 大的和。

由于 $a_i \operatorname{xor} a_j=a_j \operatorname{xor} a_i$ 会被算两次，考虑先将 $k$ 翻倍，最后答案除以 $2$。

第一部分我选择的是二分值域，然后枚举 $a_i$ 在 trie 上二分计算 $a_i \operatorname{xor} x > mid$ 的方案数。这里不取等号，可以少判一种相等的情况，写起来更加方便。具体而言，从高往低枚举二进制位：若 $mid$ 第 $d$ 位为 $1$，则 $a_i \operatorname{xor} x$ 这一位只能为 $1$，走这个儿子；反之若 $a_i \operatorname{xor} x$ 这一位为 $1$，则无论后面几位如何取都会比 $mid$ 大，故方案数加上 $a_i \operatorname{xor} x = 1$ 的 $size$，然后走 $a_i \operatorname{xor} x = 0$ 的儿子。

令 $> R$ 的方案数为 $res$，第二部分前 $k$ 大的和就是： $> R$ 的和 加上 $R \times ( k - res )$。$R \times ( k - res )$ 直接计算，对于 $> R$ 的和，我们可以先像第一部分那样在 trie 上二分，若 $R$ 某一位为 $1$ 只走儿子，为 $0$ 则更新答案后走儿子，更新答案也就是查询 trie 上某棵子树内所有数与 $x$ 的异或值之和。在节点 $i$ 维护一个 $s_{i,j}$ 表示 $i$ 子树内第 $j$ 位为 $1$ 的数的个数，然后计算时拆位处理即可。

个人认为将 trie 的操作写成递归的形式会大大减少思维难度和码量。在这里码量大约是其他题解的一半。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rgi register int
typedef long long ll;
const int N=50010,SZ=1500010,W=30;
#define g(x) ((x)>>d&1)
ll n,k,ans,res,M,L,R=(1<<W)-1;
int a[N],ch[SZ][2],siz[SZ],s[SZ][W+1],rt,tot;
void add(int x,int i){
	for(rgi d=W;~d;--d)ans+=(ll)(g(x)?siz[i]-s[i][d]:s[i][d])<<d;
}
void ins(int x,int& r=rt,int d=W){
	++siz[r?r:r=++tot];
	for(rgi D=W;~D;--D)s[r][D]+=(x>>D&1);
	if(~d)ins(x,ch[r][g(x)],d-1);
}
int qry(int x,int r=rt,int d=W){
	return r?!g(M)*siz[ch[r][!g(x)]]+qry(x,ch[r][g(x^M)],d-1):0;
}
void calc(int x,int r=rt,int d=W){
	if(r)calc(x,ch[r][g(x^R)],d-1);
	if(r&&!g(R))add(x,ch[r][!g(x)]);
}
signed main(){
	cin>>n>>k,k<<=1;
	for(rgi i=1;i<=n;++i)cin>>a[i],ins(a[i]);
	while(R>L+1){
		res=0,M=L+R>>1;
		for(rgi i=1;i<=n;++i)res+=qry(a[i]);
		if(res>=k)L=M;
		else R=M,ans=(k-res)*R;
	}
	for(rgi i=1;i<=n;++i)calc(a[i]);
	cout<<(ans/2)%1000000007;
	return 0;
}

```


---

## 作者：i207M (赞：3)

异或之，Tree and Xor，Friends...~~（禁赛.jpg~~

这个题和Tree and Xor 很像，我们可以先求出第K大，然后枚举其他异或值和第K大的LCP，进而算出前K大。但是过程中需要处理“一个数和Trie树上某个点的子树的所有数的异或和”...当时真是降智了，想到开$O(n\log ^2n)$的数组记录信息；或者dsu on tree，都太不优雅了，看了网上题解恍然大悟：

**Trie树上一个点的子树对应原序列的权值上的一段区间！** 所以在Trie树上每个点维护信息，不妨改为直接维护原序列的区间信息！

```cpp
#define N 50005
#define B 32 // INT -> 0-30
int n;
int tot=1,ch[N*B][2],sz[N*B];
void ins(int v)
{
	int x=1;
	for(ri i=30; i>=0; --i)
	{
		int w=(v>>i)&1;
		if(!ch[x][w]) ch[x][w]=++tot;
		x=ch[x][w];
		++sz[x];
	}
}
il int run(int v,int w)
{
	int x=1;
	for(ri i=30; i>=w; --i) x=ch[x][(v>>i)&1];
	return x;
}
uint K;
int a[N];
int bit[N][B];
int lim;
void getlim()
{
	uint rk=K;
	for(ri w=30; w>=0; --w)
	{
		// try 1 first
		uint nrk=0;
		for(ri i=1; i<=n; ++i) nrk+=sz[run(a[i]^lim^(1<<w),w)];
		nrk>>=1;
		if(rk<=nrk) lim|=1<<w;
		else rk-=nrk;
	}
}
uint cnt;
LL sum;
void getsum()
{
	// bigger than lim
	for(ri w=30; w>=0; --w)
	{
		if((lim>>w&1)==1) continue;
		int v=(lim>>w|1)<<w;
		for(ri i=1; i<=n; ++i)
		{
			int l=((a[i]^v)>>w)<<w,r=l|((1<<w)-1);
			l=lower_bound(a+1,a+1+n,l)-a;
			r=upper_bound(a+1,a+1+n,r)-a; // [ , )
			if(l==r) continue;
			sum+=(LL)v*(r-l);
			cnt+=r-l-(l<=i&&i<r);
			for(ri j=w-1; j>=0; --j)
			{
				int t=bit[l][j]-bit[r][j];
				if((a[i]>>j)&1) t=r-l-t;
				sum+=(LL)(1<<j)*t;
			}
		}
	}
	cnt>>=1,sum>>=1;
}
signed main()
{
#ifdef M207
	freopen("in.in","r",stdin);
	// freopen("ot.out","w",stdout);
#endif
	in(n,K);
	for(ri i=1; i<=n; ++i) in(a[i]);
	sort(a+1,a+1+n);
	for(ri i=n; i>=1; --i)
	{
		ins(a[i]);
		for(ri j=0; j<=30; ++j) bit[i][j]=bit[i+1][j]+((a[i]>>j)&1);
	}
	getlim();
	getsum();
	int ans=(sum+(LL)(K-cnt)*lim)%md;
	out(ans);
	return 0;
}
```


---

## 作者：Purslane (赞：2)

# Solution

考虑如果除序，那么相当于求前 $2m$ 大的两两异或值的和。

然后我们考虑在求第 $2m$ 大的过程中计算答案。你知道如何求一个数和其他数异或和前 $k$ 大的做法。相当于一个数二分答案。

因此就考虑一大堆数在二分答案。于是你想知道**舍弃一个区间**的时候产生的贡献。

然后你发现每次你关心 Trie 树上一个子树里点的信息。

如果你压成 DFS 序，你发现恰好是从小到大排序后的数列。

这样可以做到 $O(n \log^2 V)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50000+10,MAXM=30+2,MOD=1e9+7;
int n,m,tot=1,ans,kth,pos[MAXN],a[MAXN],cnt[MAXN][MAXM][2],sze[MAXN*MAXM],tr[MAXN*MAXM][2],l[MAXN*MAXM],r[MAXN*MAXM];
void insert(int v,int pos) {
	int rt=1; if(l[rt]==0) l[rt]=pos; r[rt]=pos; sze[rt]++;
	roff(i,29,0) {
		int op=!!(v&(1<<i));
		if(l[rt]==0) l[rt]=pos; r[rt]=pos;
		sze[rt]++;
		if(tr[rt][op]==0) tr[rt][op]=++tot;
		rt=tr[rt][op];
	}
	if(l[rt]==0) l[rt]=pos;
	r[rt]=pos;
	sze[rt]++;
	return ;
}
void add_ans(int l,int r,int v) {
	ffor(i,0,29) {
		int op=!!(v&(1<<i));
		ans=(ans+(cnt[r][i][op^1]-cnt[l-1][i][op^1])*(1<<i)%MOD)%MOD;
	}
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m,m*=2;
	ffor(i,1,n) cin>>a[i];
	sort(a+1,a+n+1);
	ffor(i,1,n) insert(a[i],i);
	ffor(i,1,n) {
		pos[i]=1;
		ffor(j,0,29) ffor(op,0,1) cnt[i][j][op]=cnt[i-1][j][op];
		ffor(j,0,29) cnt[i][j][!!(a[i]&(1<<j))]++;
	}
	roff(i,29,0) {
		int tot=0;
		ffor(j,1,n) if(pos[j]) {
			int op=!!(a[j]&(1<<i));
			tot+=sze[tr[pos[j]][op^1]];
		}
		if(tot<=m) {
			m-=tot;
			ffor(j,1,n) {
				int op=!!(a[j]&(1<<i));
				if(tr[pos[j]][op^1]) add_ans(l[tr[pos[j]][op^1]],r[tr[pos[j]][op^1]],a[j]);
				pos[j]=tr[pos[j]][op];
			}
		}
		else {
			kth+=(1<<i);
			ffor(j,1,n) {
				int op=!!(a[j]&(1<<i));
				pos[j]=tr[pos[j]][op^1];
			}
		}
	}
	ans+=kth*m%MOD;
	cout<<ans%MOD*(MOD+1)/2%MOD;
	return 0;
}
```

---

## 作者：UnyieldingTrilobite (赞：2)

首先题目就是让我们求前 $k$ 大异或值之和，肯定得把 $k$ 翻个倍方便计算。至于一个数异或自己怎么处理……这玩意难道不是 $0$ 吗为什么要处理。
 
然后按照传统套路把所有数丢进一个 Trie（记录子树大小的那种），然后我们就发现不会了……主要是前 $k$ 这玩意没法对每个数遍历一遍分开处理就很难受，考虑怎么让它舒服起来。直观的想法是，如果能对每个数找到在异或前 $k$ 内应该在 Trie 上走哪条路，那就能分开算了。而众所周知 Trie 可以处理对于一个数在异或大于某数的时候该怎么走，于是我们的当务之急就是把第 $k$ 大找出来。

然后这个东西可以直接二分，接下来判断大于它的数量是否足够少就可以了。这个时候我们可以顺便求出第 $k$ 大的出现次数，把它单独拎出来计算，不然计算正好第 $k$ 大的时候还是没法优秀地寻找路径。

接下来我们每个数在 Trie 上怎么走就很方便了，事实上和一层二分里的走法完全一致，复制一下就好了。所以我们相当于是要处理 Trie 一棵子树内所有数异或一个给定数的值的和。

这个东西显然要按位拆分（不然加和搞不了），然后对于 Trie 每个节点记录一下子树内的数给定位上有多少个 $1$ 就好了（由于记录了子树大小，不需要再记录有多少 $0$ 了）。

别忘了输出的时候答案还要再除以二，另外如果二分的时候答案没赋初值那么千万别忘了特判 $k$ 是否为零，不放心的把样例那组数据的 $k$ 调成零测一下就好了。

然后没了……哦还有代码。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 5e4 + 9, L = 31, mod = 1e9 + 7;
int n, k, kth, kcnt, a[N], ans;
signed tot = 1, sn[N * L][2], cnt[N * L][L], sz[N * L];
int calc_xor(int pos, int x) {
  int ret = 0;
  for (int i = 0, val = 1; i < L; ++i, (val <<= 1) %= mod) {
    int clc = ((x >> i) & 1) ? (sz[pos] - cnt[pos][i]) : cnt[pos][i];
    ret += clc * val % mod;
  }
  return ret;
}
signed main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);
  cin >> n >> k, k <<= 1;
  if (k) {
    for (int _ = 0; _ < n; ++_) {
      cin >> a[_];
      int pos = 1;
      for (int i = L - 1; i >= 0; --i) {
        signed& npos = sn[pos][(a[_] >> i) & 1];
        if (!npos) npos = ++tot;
        ++sz[pos = npos];
        for (int j = L - 1; j >= 0; --j)
          if ((a[_] >> j) & 1) ++cnt[pos][j];
      }
    }
    //以上为建树
    int l = 0, r = 2e9;
    while (l <= r) {
      int mid = (l + r) >> 1, dlt = 0;
      for (int i = 0; i < n; ++i) {
        int pos = 1;
        for (int j = L - 1; j >= 0; --j) {
          bool t1 = (a[i] >> j) & 1, t2 = (mid >> j) & 1;
          if (!t2)
            dlt += sz[sn[pos][!t1]], pos = sn[pos][t1];
          else
            pos = sn[pos][!t1];
        }
      }
      if (dlt < k)
        r = mid - 1, kth = mid, kcnt = k - dlt;
      else
        l = mid + 1;
    }
    //以上为找第 k 大
    for (int i = 0; i < n; ++i) {
      int pos = 1;
      for (int j = L - 1; j >= 0; --j) {
        bool t1 = (a[i] >> j) & 1, t2 = (kth >> j) & 1;
        if (!t2)
          ans += calc_xor(sn[pos][!t1], a[i]), pos = sn[pos][t1];
        else
          pos = sn[pos][!t1];
      }
    }
    //以上为计算答案，计算第 k 大的答案在下一行开始
    if (ans += kcnt * kth; ans & 1) ans += mod;
  }
  cout << (ans >> 1) % mod << endl;
  return 0;
}
```

Over.

---

## 作者：SunsetSamsara (赞：1)

## 题意

给定 $n$ 个整数 $a_1,a_2\cdots, a_n$，求两两异或值前 $k$ 大的和。 其中 $n \le 50000, a_i \le 10^9$。答案对 $10^9 + 7$ 取模。其中，$k \le \dfrac{n(n-1)}2$

## 分析

主要思路分为两步：求出第 $k$ 大的异或值 $x$，求出大于等于 $x$ 的两两异或值之和。

1. **求第 $k$ 大的异或值 $x$**

这一步直接二分。对于判断函数，考虑第 $i$ 个数的第 $t$ 位。

+ 如果 $x$ 的第 $t$ 位为 $0$，则比 $x$ 大的异或值有且只有可能是来自两棵不同子树的数。于是将排名加上 $a_i$ 所不在子树的子树的大小，并将当前节点向 $a_i$ 方向移动。

+ 如果 $x$ 的第 $t$ 位为 $1$，则只能考虑在另一子树中有没有比 $x$ 更大的，也就是说在当前这一层没有贡献。所以将当前节点向 $a_i$ 反方向移动。

到了（能走到的）最后一层时，加上这个节点的子树大小即可。

但是，这里的排名把 $a_i \oplus a_j$ 和 $a_j \oplus a_i$ 算成了两种不同的方法，所以排名要除以 $2$

```cpp
inline lld calc_rank(int x) {
	lld tot = 0;
	for (int i = 1; i <= n; ++ i) {
		int p = 0;
		for (int j = 30; ~j; -- j) {
			int t1 = (a[i] >> j) & 1, t2 = (x >> j) & 1;
			if (!t2) tot += tr[tr[p].ch[t1 ^ 1]].val, p = tr[p].ch[t1];
			else p = tr[p].ch[t1 ^ 1];
			if (!p) break;
		}
		tot += tr[p].val;
	}
	return tot >> 1;
}

```

2.**求大于 $x$ 的两两异或值之和**

这一步考虑对于每个结点维护 $\operatorname{ones}_ {u,i}$，表示节点 $u$ 的子树中所有插入的数中第 $i$ 位为 $1$ 的个数。$\operatorname{ones}_ {u,i}$ 可以使用一遍 `dfs` 来求。

```cpp
inline void dfs(int x, int dep, int t) {
	if (!x) return;
	if (!dep) {
		for (int i = 0; i <= 30; ++ i)
			if ((t >> i) & 1) tr[x].a[i] = tr[x].val;
		return;
	}
	dfs(tr[x].ch[0], dep - 1, t);
	dfs(tr[x].ch[1], dep - 1, t | (1 << (dep - 1)));
	for (int i = 0; i <= 30; ++ i)
		tr[x].a[i] = tr[tr[x].ch[0]].a[i] + tr[tr[x].ch[1]].a[i];
}
```

接下来就可以求出答案了。对于每一个 $a_i$，从每一位上考虑。

如果 $x$ 第 $j$ 位为 $0$，就可以出现比 $x$ 大的异或值。同样的，只有在不同的子树中，异或值才能大于 $x$。于是对于每一位 $k$，如果 $a_i$ 的第 $k$ 位为 $1$，就加上第 $k$ 位为 $0$ 的数的贡献 $2^k (\operatorname{size}_ u - \operatorname{ones} _ {u, k})$；否则就加上第 $k$ 位为 $1$ 的数的贡献$2^k \operatorname{ones} _ {u, k}$

```cpp
inline void solve(int kth) {
	for (int i = 1; i <= n; ++ i) {
		int u = 0;
		for (int j = 30; ~j; -- j) {
			int t1 = (a[i] >> j) & 1;
			int t2 = (kth >> j) & 1;
			if (!t2) {
				int t = tr[u].ch[t1 ^ 1];
				for (int k = 0; k <= 30; ++ k) {
					int t3 = (a[i] >> k) & 1;
					if (t3) ans = (ans + 1ll * (tr[t].val - tr[t].a[k]) * (1ll << k)) % mod;
					else ans = (ans + 1ll * tr[t].a[k] * (1ll << k)) % mod;
				}
				u = tr[u].ch[t1];
			} else u = tr[u].ch[t1 ^ 1];
			if (!u) break;
		}
		ans = (ans + 1ll * tr[u].val * kth) % mod;
	}
}
```

这里还要考虑判重，直接除以 $2$，还要加上与 $x$ 相同的异或值的贡献（因为求的是大于）。这样，就会有：

`ans = ((ans * inv2 % mod - 1ll * (calc_rank(kth) - k) * kth % mod) % mod + mod) % mod`

最后，把上面几步整合到一起，就能得到完整程序了。

## 代码

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define lld long long
using namespace std;
inline int min(const int &x, const int &y) { return x < y ? x : y; }
inline int max(const int &x, const int &y) { return x > y ? x : y; }
const int N = 50010;
const int mod = 1e9 + 7;
const int inv2 = (mod + 1) >> 1;
int n, a[N];
lld ans, k;
struct node {
	int ch[2];
	int val;
	int a[32];
} tr[N << 5];
int tcnt;
inline void insert(int x) {
	int p = 0;
	for (int i = 30; ~i; -- i) {
		int b = (x >> i) & 1;
		if (!tr[p].ch[b]) tr[p].ch[b] = ++ tcnt;
		p = tr[p].ch[b];
		++ tr[p].val;
	}
}
inline lld calc_rank(int x) {
	lld tot = 0;
	for (int i = 1; i <= n; ++ i) {
		int p = 0;
		for (int j = 30; ~j; -- j) {
			int t1 = (a[i] >> j) & 1, t2 = (x >> j) & 1;
			if (!t2) tot += tr[tr[p].ch[t1 ^ 1]].val, p = tr[p].ch[t1];
			else p = tr[p].ch[t1 ^ 1];
			if (!p) break;
		}
		tot += tr[p].val;
	}
	return tot >> 1;
}
inline void dfs(int x, int dep, int t) {
	if (!x) return;
	if (!dep) {
		for (int i = 0; i <= 30; ++ i)
			if ((t >> i) & 1) tr[x].a[i] = tr[x].val;
		return;
	}
	dfs(tr[x].ch[0], dep - 1, t);
	dfs(tr[x].ch[1], dep - 1, t | (1 << (dep - 1)));
	for (int i = 0; i <= 30; ++ i)
		tr[x].a[i] = tr[tr[x].ch[0]].a[i] + tr[tr[x].ch[1]].a[i];
}
inline void solve(int kth) {
	for (int i = 1; i <= n; ++ i) {
		int u = 0;
		for (int j = 30; ~j; -- j) {
			int t1 = (a[i] >> j) & 1;
			int t2 = (kth >> j) & 1;
			if (!t2) {
				int t = tr[u].ch[t1 ^ 1];
				for (int k = 0; k <= 30; ++ k) {
					int t3 = (a[i] >> k) & 1;
					if (t3) ans = (ans + 1ll * (tr[t].val - tr[t].a[k]) * (1ll << k)) % mod;
					else ans = (ans + 1ll * tr[t].a[k] * (1ll << k)) % mod;
				}
				u = tr[u].ch[t1];
			} else u = tr[u].ch[t1 ^ 1];
			if (!u) break;
		}
		ans = (ans + 1ll * tr[u].val * kth) % mod;
	}
}
int main() {
	scanf("%d%lld", &n, &k);
	for (int i = 1; i <= n; ++ i) scanf("%d", a + i);
	if (!k) {
		puts("0");
		return 0;
	}
	for (int i = 1; i <= n; ++ i) insert(a[i]);
	int l = 0, r = (1 << 30), mid, kth = 0;
	for (; mid = (l + r) >> 1, l <= r; ) {
		if (calc_rank(mid) >= k) kth = mid, l = mid + 1;
		else r = mid - 1;
	}
	dfs(tr[0].ch[0], 30, 0);
	dfs(tr[0].ch[1], 30, 1 << 30);
	solve(kth);
	ans = ((ans * inv2 % mod - 1ll * (calc_rank(kth) - k) * kth % mod) % mod + mod) % mod;
	printf("%lld\n", ans);
}
```


---

## 作者：juju (赞：1)

给定 $n$ 个整数 $a1,a2...an$ ，求两两异或值前 $k$ 大的和。

其中 $n\le 50000,ai\le 10^9$。

答案对 $1000000007$ 取模。

---

直接计算较为困难，考虑求第 $k$ 大的数并计算大于等于 $k$ 的数之和。

于是可以二分答案计算第 $k$ 大的数，具体实现可以通过讨论每一位上的数来计算。

可以用类似的步骤计算出大于等于 $k$ 的数之和。

```cpp
#include<bits/stdc++.h>
#define Mid (L+R>>1)
#define ll long long
#define int long long
using namespace std;
const int maxn=50010,mod=1e9+7;
int i,j,n,m,a[maxn];ll k;
int check(int L1,int R1,int L2,int R2,int b,int w,int last1,int last2){
	if(R1<L1 || R2<L2 || b<0)return 0;
	int d1=lower_bound(a+L1,a+R1+1,(1<<b)+last1)-a-1;
	int d2=lower_bound(a+L2,a+R2+1,(1<<b)+last2)-a-1;
	ll ans=0;
	if((1<<b)>=w){
		ans+=(d1-L1+1)*(R2-d2);
		if(L1!=L2)ans+=(d2-L2+1)*(R1-d1);
		ans+=check(L1,d1,L2,d2,b-1,w,last1,last2);
		ans+=check(d1+1,R1,d2+1,R2,b-1,w,last1+(1<<b),last2+(1<<b));
	}else{
		ans+=check(L1,d1,d2+1,R2,b-1,w-(1<<b),last1,last2+(1<<b));
		if(L1!=L2)ans+=check(d1+1,R1,L2,d2,b-1,w-(1<<b),last1+(1<<b),last2);
	}
//	cout<<"check "<<L1<<' '<<d1<<' '<<R1<<' '<<L2<<' '<<d2<<' '<<R2<<' '<<b<<' '<<w<<' '<<ans<<' '<<last1<<' '<<last2<<endl;
	return ans;
}
int Bit[maxn][35],bit[35][2];
ll sum(int L1,int R1,int L2,int R2){
	for(int i=0;i<=30;i++)bit[i][0]=Bit[R1][i]-Bit[L1-1][i];
	for(int i=0;i<=30;i++)bit[i][1]=Bit[R2][i]-Bit[L2-1][i];
	ll ans=0;
	for(int i=0;i<=30;i++)ans+=1ll*bit[i][0]*(R2-L2+1-bit[i][1])*(1<<i)%mod;
	for(int i=0;i<=30;i++)ans+=1ll*bit[i][1]*(R1-L1+1-bit[i][0])*(1<<i)%mod;
//	cout<<"sum "<<L1<<' '<<R1<<' '<<L2<<' '<<R2<<' '<<ans<<endl;
	return ans%mod;
}
ll getans(int L1,int R1,int L2,int R2,int b,int w,int last1,int last2){
	if(R1<L1 || R2<L2 || b<0)return 0;
	int d1=lower_bound(a+L1,a+R1+1,(1<<b)+last1)-a-1;
	int d2=lower_bound(a+L2,a+R2+1,(1<<b)+last2)-a-1;
	ll ans=0;
	if((1<<b)>=w){
		ans+=sum(L1,d1,d2+1,R2);
		if(L1!=L2)ans+=sum(d1+1,R1,L2,d2);
		ans+=getans(L1,d1,L2,d2,b-1,w,last1,last2);
		ans+=getans(d1+1,R1,d2+1,R2,b-1,w,last1+(1<<b),last2+(1<<b));
	}else{
		ans+=getans(L1,d1,d2+1,R2,b-1,w-(1<<b),last1,last2+(1<<b));
		if(L1!=L2)ans+=getans(d1+1,R1,L2,d2,b-1,w-(1<<b),last1+(1<<b),last2);
	}
//	cout<<"check "<<L1<<' '<<d1<<' '<<R1<<' '<<L2<<' '<<d2<<' '<<R2<<' '<<b<<' '<<w<<' '<<ans<<endl;
	return ans%mod;
}
signed main(){
	cin>>n>>k;
	if(!k)puts("0"),exit(0);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	sort(a+1,a+1+n);
	for(i=1;i<=n;i++)
		for(j=0;j<=30;j++)
			Bit[i][j]=Bit[i-1][j]+((a[i]&(1<<j))?1:0);
	ll L=0,R=2147483647;
	while(L<=R){
//		cout<<"try "<<Mid<<endl;
		if(check(1,n,1,n,30,Mid,0,0)>=k)L=Mid+1;
		else R=Mid-1;
	}
//	cout<<"ans="<<L-1<<endl;
//	cout<<getans(1,n,1,n,30,L,0,0)<<endl;
	cout<<(getans(1,n,1,n,30,L,0,0)+(L-1)*(k-check(1,n,1,n,30,L,0,0)))%mod<<endl;
	return 0;
}
/*
4 2
141 146 466 789 
*/
```

---

## 作者：bluewindde (赞：0)

是 [异或粽子](https://www.luogu.com.cn/problem/P5283) 的超级加强版，但是本题因为 $m$ 很大，不能套用那一题的解法。

---

换一种思路：考虑把 $a_i$ 从高位到低位插入 0-1 Trie 之后，二分第 $m$ 大，通过第 $m$ 大求答案。

对于二分的一个值 $x$，枚举每个位置 $i$，在 0-1 Trie 上找与 $a_i$ 异或值大于等于 $x$ 的值的个数。

类比求最大异或和的过程，考虑搜索到第 $j$ 位。如果 $x$ 的第 $j$ 位为 $1$，为了最终异或值大于等于 $x$，可能的数一定在与 $a_i$ 的第 $j$ 位相异的子树中，递归即可；反之，如果 $x$ 的第 $j$ 位为 $0$，与 $a_i$ 的第 $j$ 位相异的子树中的值一定全部满足条件，递归与 $a_i$ 的第 $j$ 位相同的子树即可。

于是可以在 $O(n \log^2 w)$ 的时间内找到第 $m$ 大的异或值（$w$ 为值域，后文同），设这个值为 $k$。

---

下一步是求前 $m$ 大两两异或值的和。

容易想到，类似前文所述，只需要处理被计算的完整的子树与 $a_i$ 的异或值的和。（即搜索时找到的 $k$ 的第 $j$ 位为 $0$，与 $a_i$ 的第 $j$ 位相异的子树）直接对这些子树的根节点打标记，整体遍历一次 0-1 Trie 时容易得到这棵子树内每一位上 $0$ 和 $1$ 的数量，答案也就容易统计了。

至多有 $n \log w$ 个标记，处理每个标记需要枚举 $\log w$ 位。同时，至多合并 $O(n \log w)$ 次，单次合并的时间为 $O(\log w)$。综上，时间复杂度 $O(n \log^2 w)$。

---

将两部分拼起来就得到了最终做法，时间复杂度 $O(n \log^2 w)$，可以通过。

```cpp
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

const ll mod = 1e9 + 7;

static inline ll qpow(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b & 1)
            ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
const ll _2 = qpow(2, mod - 2);

int n, m;
int a[50005];

int rt;
map<int, vector<int>> mp;
struct trie {
    int son[2];
    int val, cnt[32];
} tr[1600005];
int cnt;
static inline int insert(int x, int dep, int p) {
    if (!p)
        p = ++cnt;
    if (dep == -1) {
        ++tr[p].val;
        return p;
    }
    int tag = (x >> dep) & 1;
    tr[p].son[tag] = insert(x, dep - 1, tr[p].son[tag]);
    tr[p].val = tr[tr[p].son[0]].val + tr[tr[p].son[1]].val;
    return p;
}
static inline ll query(int x, int aim, int dep, int p) {
    if (!p)
        return 0;
    if (dep == -1)
        return tr[p].val;
    int tg = (x >> dep) & 1;
    int tg2 = (aim >> dep) & 1;
    if (tg2)
        return query(x, aim, dep - 1, tr[p].son[tg ^ 1]);
    return tr[tr[p].son[tg ^ 1]].val + query(x, aim, dep - 1, tr[p].son[tg]);
}

ll ans, sum;
static inline void query2(int x, int aim, int dep, int p) {
    if (!p)
        return;
    if (dep == -1)
        return;
    int tg = (x >> dep) & 1;
    int tg2 = (aim >> dep) & 1;
    if (tg2)
        return query2(x, aim, dep - 1, tr[p].son[tg ^ 1]);
    if (tr[p].son[tg ^ 1])
        mp[tr[p].son[tg ^ 1]].push_back(x);
    query2(x, aim, dep - 1, tr[p].son[tg]);
}
static inline void dfs(int dep, int p, int from, int val) {
    if (!p)
        return;
    if (dep == -1) {
        if (from)
            tr[p].cnt[dep + 1] += tr[p].val;
        if (mp.count(p))
            for (auto x : mp[p]) {
                sum += tr[p].val;
                ll tot = 0;
                for (int i = 0; i <= dep + 1; ++i) {
                    int tg = (x >> i) & 1;
                    if (tg)
                        tot += (ll)(tr[p].val - tr[p].cnt[i]) * (1ll << i) % mod;
                    else
                        tot += (ll)tr[p].cnt[i] * (1ll << i) % mod;
                }
                for (int i = dep + 2; i <= 30; ++i) {
                    int tg = (x >> i) & 1;
                    int tg2 = (val >> i) & 1;
                    if (tg ^ tg2)
                        tot += (ll)tr[p].val * (1ll << i) % mod;
                }
                ans = (ans + tot) % mod;
            }
        return;
    }
    if (tr[p].son[0]) {
        dfs(dep - 1, tr[p].son[0], 0, val);
        for (int i = 0; i <= 30; ++i)
            tr[p].cnt[i] += tr[tr[p].son[0]].cnt[i];
    }
    if (tr[p].son[1]) {
        dfs(dep - 1, tr[p].son[1], 1, val | (1 << dep));
        for (int i = 0; i <= 30; ++i)
            tr[p].cnt[i] += tr[tr[p].son[1]].cnt[i];
    }
    if (from)
        tr[p].cnt[dep + 1] += tr[p].val;
    if (mp.count(p))
        for (auto x : mp[p]) {
            sum += tr[p].val;
            ll tot = 0;
            for (int i = 0; i <= dep + 1; ++i) {
                int tg = (x >> i) & 1;
                if (tg)
                    tot += (ll)(tr[p].val - tr[p].cnt[i]) * (1ll << i) % mod;
                else
                    tot += (ll)tr[p].cnt[i] * (1ll << i) % mod;
            }
            for (int i = dep + 2; i <= 30; ++i) {
                int tg = (x >> i) & 1;
                int tg2 = (val >> i) & 1;
                if (tg ^ tg2)
                    tot += (ll)tr[p].val * (1ll << i) % mod;
            }
            ans = (ans + tot) % mod;
        }
}

static inline bool check(int x) {
    ll tot = 0;
    for (int i = 1; i <= n; ++i)
        tot += query(a[i], x, 30, rt);
    tot >>= 1;
    return tot >= m;
}

static inline void solve() {
    cin >> n >> m;
    if (m == 0) {
        cout << 0 << endl;
        return;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        rt = insert(a[i], 30, rt);
    }
    int l = 1;
    int r = 1ll << 30;
    int ret = -1;
    while (l <= r) {
        int mid = (int)((l + r) >> 1);
        if (check(mid)) {
            ret = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    for (int i = 1; i <= n; ++i)
        query2(a[i], ret, 30, rt);
    dfs(30, rt, 0, 0);
    sum >>= 1;
    ans = ans * _2 % mod;
    ans = (ans + (m - sum) * ret % mod) % mod;
    cout << ans << endl;
}

signed main() {
#ifndef ONLINE_JUDGE
    freopen("1.in", "r", stdin);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
```

---

## 作者：CC__DIAMOND (赞：0)

# CF241B Friends 题解
折腾好久终于把这一题过了。题解区第一篇的思路我是最喜欢的，但是它不说人话且马蜂比较精简。故本人改进了她的做法并且使用了更简单的解释与更易读的马蜂。希望能为同样被这题折磨的各位帮一点忙。
# 题意
翻译写得很明白了，略。
# 做法
我们先考虑怎么求出第 $m$ 大的异或值$mth$（先不要管是怎么想到这一步的）。  
方式和在 Trie 树上求前 $k$ 大值大体是相似的：  
从最高位按位枚举，对与第 $i$ 位，求出在前 $i-1$ 位与已求出的$mth$ 相同，第 $i$ 位取 $1$ 的异或值个数 $c$。  
将 $c$ 与 $m$ 比较，$c\le m$ 则这一位取 $1$，否则这一位取 $0$，并且取 $m^{\prime}=m-c$ 为新的 $m$。  
如果还不明白可以参考[这个](https://www.luogu.com.cn/article/m8o2nhmw)。  
可以发现最后 $m^{\prime}$ 会变成前 $m$ 大异或值中第 $m$ 大异或值的出现次数,$mth\cdot m^{\prime}$ 便是这一部分的贡献。  
在具体的代码实现中，我们维护一个节点数组 $\{p_n\}$ 并且让 $p_j$ 下面的任意数字和 $a_j$ 异或后的前 $i-1$ 位与 $mth$ 的前 $i-1$ 位相同。  
这样我们通过 Trie 上统计的 size 就可以得知每一个 $a_i$ 对于 $c$ 的贡献了。  
如果对于 $a_j$ 不存在 $a_k$ 使得 $a_j \ xor \ a_k$ 前 $i$ 位与 $mth$ 相同，我们直接让对应的 $p_j=0$ 即可（因为下标为 $0$ 的节点是空的）。  
接下来我们考虑大于 $mth$ 部分的贡献。对于每一个 $mth$ 取 $0$ 的二进制位 $i$，我们统计出前 $i-1$ 位相同，第 $i$ 位取 $1$ 的异或值之和。累加到 ans 里即可。  
具体该怎么实现呢？  
我们注意到（注意力惊人） Trie 树的一颗子树对应原序列排序后的一个子区间（类比平衡树），于是我们将原数列排序后，对每一位分别求出 $1$ 个数的前缀和。  
现在我们只要按位枚举就可以求出一个数 $a_i$ 和 $p_j$ 子树中所有元素的异或值之和了。  
同时异或 $a_j$ 后使得前 $i-1$ 位与 $mth$ 相同，第 $i$ 位取 $1$ 的所有元素显然也在一颗子树里，这样我们在每一个 $mth$ 取 $0$ 的位 $i$ 对于每个 $a_j$ 分别求和即可。  
记这一部分为 $s$，则 $s+mth \cdot m^{\prime}$ 显然就是答案。
# 代码
在实现中还要注意两点：  
1. $m=0$ 时上述方法会失效，此时直接输出 $0$ 即可。
2. 这么做 $a_i \ xor \ a_j$ 与 $a_j \ xor \ a_i$ 会被分别计算两次，将 $m$ 乘以 $2$ 再将答案除以 $2$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

// 个人习惯：把实际解题的代码放到一个命名空间里，避免冲突
namespace Solution {
    // 各种常量
    constexpr int N=5e4+10;
    constexpr int O=32; // 最大位数 Omega
    constexpr int mod=1e9+7;
    constexpr ll add(ll x,ll y) { return (x+y)%mod; }
    constexpr ll mul(ll x,ll y) { return (x*y)%mod; }
    constexpr ll pow(ll x,ll exp) {
        ll res=1;
        while(exp) {
            if(exp&1) res=mul(res,x);
            x=mul(x,x);
            exp>>=1;
        }
        return res;
    }
    int n;
    int a[N],cnt1sum[N][O]; // cnt1sum 是排序后的原数组在各个二进制位上 1 数量的前缀和
    // Trie
    int next[N*O][2],size[N*O],l[N*O],r[N*O],tot=1; // [l,r] 即为子树 p 对应的区间
    void prepare() { // 预处理出 Trie 和 cnt1sum
        sort(a+1,a+n+1);
        size[1]=n,l[1]=1,r[1]=n;
        for(int i=1;i<=n;++i) {
            int p=1;
            for(int j=O-1;j>=0;--j) {
                int c=a[i]>>j&1;
                if(!next[p][c]) {
                    next[p][c]=++tot;
                    l[next[p][c]]=i;
                }
                p=next[p][c];
                size[p]++;
                r[p]=i;
            }
        }
        for(int i=1;i<=n;++i) {
            for(int j=0;j<O;++j) {
                cnt1sum[i][j]=cnt1sum[i-1][j]+(a[i]>>j&1);
            }
        }
    }
    // 数字 v 和节点 p 子树中所有元素异或的和。
    ll getsum(int p,int v) {
        if(!p) return 0;
        ll res=0;
        for(int i=O-1;i>=0;--i) {
            res=mul(res,2);
            int c=v>>i&1;
            ll cnt1=cnt1sum[r[p]][i]-cnt1sum[l[p]-1][i];
            if(c) res=add(res,r[p]-l[p]+1-cnt1);
            else res=add(res,cnt1);
        }
        return res;
    }
    // 节点数组
    int p[N];
    ll solve(ll m) {
        for(int i=1;i<=n;++i) p[i]=1;
        ll ans=0,mth=0; // mth 表示第 m 大的异或值
        for(int i=O-1;i>=0;--i) {
            // 当前能对答案产生贡献的异或值中，这一位1的个数
            ll cnt1=0;
            int x; // x 表示 mth 这一位的取值
            for(int j=1;j<=n;++j) {
                int c=a[j]>>i&1;
                cnt1+=size[next[p[j]][!c]];
            }
            // 分类讨论
            if(cnt1<m) {
                x=0;
                m-=cnt1;
            } else {
                x=1;
                mth|=1<<i;
            }
            if(!x) {
                // 若这一位取 0，将所有目前能产生贡献的异或值中比 mth 大的加入到答案中
                for(int j=1;j<=n;++j) {
                    int c=a[j]>>i&1;
                    ans=add(ans,getsum(next[p[j]][!c],a[j])); // next[p[j]][!c] 便是元素异或 a[j] 后前 i-1 位相同，第 i 位取1的子树
                }
            }
            for(int j=1;j<=n;++j) {
                int c=a[j]>>i&1;
                p[j]=next[p[j]][c^x];
            }
        }
        ans=add(ans,mul(mth,m)); // 最后的 m 就是第 m 大异或值的个数，加入到答案中。
        return ans;
    }
    void solve() {
        ll m;
        cin>>n>>m;
        if(!m) { // 特判
            cout<<0<<'\n';
            return;
        }
        for(int i=1;i<=n;++i) cin>>a[i];
        prepare();
        // 我们的做法会把 a_i xor a_j 和 a_j xor a_i 都计入到答案中。所以 m 和答案要分别乘以/除以 2
        ll ans=solve(2*m);
        constexpr ll half=pow(2,mod-2);
        ans=mul(ans,half);
        cout<<ans<<'\n';
    }
}

// 并没有什么东西的 main 函数
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int T=1;
    // cin>>T;
    while(T--) {
        Solution::solve();
    }
    return 0;
}

```

---

## 作者：lg_zhou (赞：0)

**Trie 树小综合**

**CF241B Friends**

前置芝士：[Trie 2](https://www.luogu.com.cn/blog/lgzhou/solution-cf1055f)、[Trie 1](https://www.luogu.com.cn/blog/lgzhou/ke-chi-jiu-hua-trie)

这道题是异或粽子的加强版，由于 $k$ 值不受限制，我们复杂度就无法带 $k$，从而舍弃了那个堆的做法。

首先，如果不想可持久化，并解决 $a_i,a_j$ 无序的问题，我们将 $k$ 乘 $2$，最后答案除以 $2$。

我们通过 [Trie 2](https://www.luogu.com.cn/blog/lgzhou/solution-cf1055f) 这里的做法可以得出第 $k$ 大的异或和是多少，记为 $val$。我们只需要求出来所有异或和 $> val$ 的组累加即可，记为 $ans$。设 $>val$ 的有 $ctmore$ 组，那么最后答案就是 $ans+(k-ctmore)*val$。

具体的，我们对于每一个 $a[i]$（原数列）。分别求出和当前这个数异或和 $> val$ 的异或和的和。继续按位从高往低进行搜索，如果 $val$ 这一位为 $1$，那么指针直接往下跳，如果 $val$ 这一位为 $0$，那能使与 $a[i]$ 异或后这一位为 $1$ 的所有数与 $a[i]$ 异或肯定都满足大于等于 $val$ 的条件。我们就将答案累加，累加 $a[i]$ 分别异或上这个子树所有数的异或和之和。

怎么进行累加呢？直接枚举每个数时间复杂度显然不可行，我们可以预处理出来一个 $cnt[x][y]$ 数组，代表以 $x$ 为根的子树下面的所有数，第 $y$ 位为 $1$ 的有多少个。这样我们累加答案的时候就可以继续枚举每一位，累加上能使这一位为 $1$ 的数量乘上 $1<<i$ 的贡献即可，$i$ 为当前枚举的位数。

这一部分的代码：


```cpp
void getans(int p, int pos, int id){
	if (pos < 0){
		return;
	} 
	int c = (val>>pos&1);
	int to1 = trie[p][a[id]>>pos&1^1];
	int to0 = trie[p][a[id]>>pos&1];
	if (c) getans(to1,pos-1,id);//如果当前位为 1 了，直接走
	else{
		for (int i = 31; i >= 0; i--){
			if (a[id]>>i&1) (ans += 1ll*(sz[to1]-cnt[to1][i])*(1ll<<i))%=mod; //这位本来就是 1，要异或0才能累加贡献
			else (ans += 1ll*cnt[to1][i]*(1ll<<i))%=mod;//直接累加贡献
		}
		ctmore += sz[to1];//比它大的数多了这么多个
		getans(to0,pos-1,id);
	}
}
```
其他的代码和  [Trie 2](https://www.luogu.com.cn/blog/lgzhou/solution-cf1055f) 这里的几乎一样（不用滚存），只不过第 $k$ 小变成了第 $k$ 大，这里就不再浪费篇幅。

要注意的一点是，由于中间取过模，最后除以二要用逆元。

---

