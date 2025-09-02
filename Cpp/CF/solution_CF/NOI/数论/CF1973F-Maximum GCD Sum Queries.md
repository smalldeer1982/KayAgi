# Maximum GCD Sum Queries

## 题目描述

对于 $k$ 个正整数 $x_1, x_2, \ldots, x_k$，$\gcd(x_1, x_2, \ldots, x_k)$ 表示这些整数的最大公约数——即最大的整数 $z$，使得所有 $x_1, x_2, \ldots, x_k$ 都能被 $z$ 整除。

现在给定三个长度为 $n$ 的数组 $a_1, a_2, \ldots, a_n$，$b_1, b_2, \ldots, b_n$ 和 $c_1, c_2, \ldots, c_n$，其中每个元素都是正整数。

你有一台机器，可以对任意 $i$（$1 \leq i \leq n$）交换 $a_i$ 和 $b_i$，每次交换需要花费 $c_i$ 个金币。

请你在总花费不超过 $d$ 个金币的前提下，通过若干次交换，使得 $\gcd(a_1, a_2, \ldots, a_n) + \gcd(b_1, b_2, \ldots, b_n)$ 的值最大。金币数量会有多种情况，请你对于每个可能的金币数 $d_1, d_2, \ldots, d_q$，分别求出最大值。

## 说明/提示

在第一个样例的第一个询问中，不能进行任何交换，所以答案为 $\gcd(1, 2, 3) + \gcd(4, 5, 6) = 2$。在第二个询问中，可以交换 $a_2$ 和 $b_2$，此时答案为 $\gcd(1, 5, 3) + \gcd(4, 2, 6) = 3$。

在第二个样例的第二个询问中，最优做法是在第 $1$ 和第 $3$ 个位置进行交换，此时答案为 $\gcd(3, 3, 6, 9, 3) + \gcd(8, 4, 4, 8, 4) = 7$，总共需要花费 $40$ 个金币。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 4
1 2 3
4 5 6
1 1 1
0 1 2 3```

### 输出

```
2 3 3 3```

## 样例 #2

### 输入

```
5 5
3 4 6 8 4
8 3 4 9 3
10 20 30 40 50
5 55 13 1000 113```

### 输出

```
2 7 3 7 7```

## 样例 #3

### 输入

```
1 1
3
4
5
0```

### 输出

```
7```

# 题解

## 作者：Purslane (赞：0)

# Solution

注意最终可能的序列 $\rm gcd$ 对只有 $O(d(a_1)d(b_1))$ 种（这一步非常关键，否则会毫无头绪），因此尝试把所有的 $\rm gcd$ 对所需最小翻转代价求出来，这样 $d$ 就不是限制而只是简单的询问。

PS：$10^8$ 以内 $d(n)$ 的最大值为 $768$。

考虑直接计算 $f_{i,j}$。（这样就从最优化问题变成确定性的判定问题）

考虑给定 $(a,b,d)$，$f$ 如何变化。

1. 如果 $i \mid a$ 且 $j \mid b$，不变；
2. 否则，如果 $i \mid b$ 且 $j \mid a$，加 $d$；
3. 否则，加 $+ \infty$。

也就是，所有整数对 $+ \infty$，$(a,b)$ 的前缀加 $- \infty$，$(b,a)$ 的前缀加 $d - \infty$，$(\gcd(a,b),\gcd(a,b))$ 的前缀加 $-d + \infty$，其中 $\infty$ 是一个充分大的常数，比如 $10^{15}$。（这是为了超过所有的询问。这时候就得开 `__int128` 了）

直接上高维前缀和即可。

注：确定 $a$ 和 $b$ 之后，就可以将 $f$ 的二维进行离散化（甚至不需要真的离散化，可以通过一些手段去 $\log$）

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=5e5+10,MAXM=1000+10,INF=1e15+1,LIM=1e18;
int n,q,a[MAXN],b[MAXN],c[MAXN],dp[MAXM][MAXM];
int tot,lsh[MAXN*4],mx[MAXN*4];
vector<pair<int,int>> vc;
int is_prime(int x) {
	if(x==1) return 0;
	if(x==2) return 1;
	if(x%2==0) return 0;
	for(int i=3;i<=x/i;i+=2) if(x%i==0) return 0;
	return 1;
}
vector<int> get(int n) {
	vector<int> ans;
	ffor(i,1,n/i) if(n%i==0) {
		ans.push_back(i);
		if(n/i!=i) ans.push_back(n/i);	
	}
	return ans;
}
const int MAXK=5e4+10;	
struct HSH {
	int f,a1[MAXK],a2[MAXK];
	void update(int n,int v) {
		if(n<=10000) return a1[n]=v,void();
		return a2[f/n]=v,void();
	}
	int query(int n) {
		if(n<=10000) return a1[n];
		return a2[f/n];	
	}
	void init(int n) {
		return f=n,void();	
	}
}H1,H2;
__int128 f[MAXM][MAXM];
vector<int> f1,f2;
void UPDATE(int a,int b,int add) {return f[H1.query(a)][H2.query(b)]+=add,void();}
void solve(int a0,int b0,int c0) {
	H1.init(a0),H2.init(b0);
	f1=get(a0),f2=get(b0);
	sort(f1.begin(),f1.end()),sort(f2.begin(),f2.end());
	ffor(i,0,f1.size()-1) H1.update(f1[i],i+1);
	ffor(i,0,f2.size()-1) H2.update(f2[i],i+1);
	memset(f,0,sizeof(f));
	ffor(i,2,n) {
		UPDATE(a0,b0,INF);
		UPDATE(__gcd(a0,a[i]),__gcd(b0,b[i]),-INF);
		UPDATE(__gcd(a0,b[i]),__gcd(b0,a[i]),c[i]-INF);
		UPDATE(__gcd(a0,__gcd(a[i],b[i])),__gcd(b0,__gcd(a[i],b[i])),INF-c[i]);
	}
	set<int> prime1,prime2;
	reverse(f1.begin(),f1.end()),reverse(f2.begin(),f2.end());
	for(auto id:f1) if(is_prime(id)) for(auto i:f1) if(i%id==0) for(auto j:f2) f[H1.query(i/id)][H2.query(j)]+=f[H1.query(i)][H2.query(j)];
	for(auto id:f2) if(is_prime(id)) for(auto j:f2) if(j%id==0) for(auto i:f1) f[H1.query(i)][H2.query(j/id)]+=f[H1.query(i)][H2.query(j)];
	for(auto i:f1) for(auto j:f2) vc.push_back({min((__int128)LIM,f[H1.query(i)][H2.query(j)]+c0),i+j});
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n) cin>>b[i];
	ffor(i,1,n) cin>>c[i];
	solve(a[1],b[1],0),solve(b[1],a[1],c[1]);
	sort(vc.begin(),vc.end());
	tot=vc.size();
	ffor(i,1,tot) lsh[i]=vc[i-1].first,mx[i]=vc[i-1].second;
	ffor(i,2,tot) mx[i]=max(mx[i],mx[i-1]);
	ffor(i,1,q) {
		int d;
		cin>>d;
		int id=upper_bound(lsh+1,lsh+tot+1,d)-lsh-1;
		cout<<mx[id]<<' ';	
	}
	return 0;
}
```

---

## 作者：liaoz123 (赞：0)

狄利克雷前/后缀和的经典应用。

考虑第一对数 $(a_1,b_1)$，则 $ans\in\{x+y\}$，其中有 $x|a_1,y|b_1$。那么我们可以拆解 $a_1,b_1$，验证每一对 $(x,y)$ 的合法性及其代价。总共 $O(\text{d}(n)^2)$ 对这样的数，可以接受。

由于固定了 $a_1,b_1$，为了考虑到所有的情况，我们需要做两次。其中第二次需要交换 $a_1,b_1$，并增加 $c_1$ 的基础代价。

现在考虑怎么计算这样的代价，并判断合法性。一对 $(x,y)$ 合法等价于满足 $x|\gcd(a_1,a_i)$ 且 $y|\gcd(b_1,b_i)$，或者 $x|\gcd(a_1,b_i)$ 且 $y|\gcd(b_1,a_i)$ 的位置 $i$ 的个数等于 $n$。考虑从遍历所有的 $a_i,b_i$，计算 $A=\gcd(a_1,a_i),B=\gcd(b_1,b_i),C=\gcd(a_1,b_i),D=gcd(b_1,a_i)$，那么 $(A,B)$ 会对所有的 $(p,q)$ 满足 $p|A,q|B$ 都造成 $1$ 的贡献，$(C,D)$ 同理。交换 $a_i,b_i$ 的代价也是同样的形式。

我们自然不可能每次暴力去给每个 $(p,q)$ 修改，但是发现这是狄利克雷后缀和的形式，我们可以把贡献先保留在 $(A,B)$ 上，在遍历完之后进行一次狄利克雷后缀和，便可以得到每对 $(x,y)$ 的代价及其合法性。

对于查询，只需要把答案存入一个 set 中，查询时二分一下就可以了。复杂度 $O(\text{d}(n)^2+q\log{n})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
int a[N],b[N],p[N],q,cnt;
bool vis[N];
ll c[N],la;int n;
map<ll,int> ans;
set<pair<ll,int> > s;
ll m[2005][2005];
int cc[2005][2005];
void pre(){
	for(int i=2;i<N;i++){
		if(!vis[i])p[++cnt]=i;
		for(int j=1;j<=cnt&&p[j]*i<N;j++){
			vis[p[j]*i]=true;
			if(i%p[j]==0)break;
		} 
	}
}
void solve(ll w){
	vector<int> pa,pb,da,db;
	map<int,int> ida,idb;
	memset(m,0,sizeof(m));
	memset(cc,0,sizeof(cc));
	for(int i=1;i*i<=a[1];i++){
		if(a[1]%i!=0)continue;
		da.push_back(i);
		if(i*i!=a[1])da.push_back(a[1]/i);
	}
	for(int i=1;i*i<=b[1];i++){
		if(b[1]%i!=0)continue;
		db.push_back(i);
		if(i*i!=b[1])db.push_back(b[1]/i);
	}
	sort(da.begin(),da.end());
	sort(db.begin(),db.end());
	for(int i=0;i<da.size();i++)ida[da[i]]=i;
	for(int i=0;i<db.size();i++)idb[db[i]]=i;
	int now=a[1];
	for(int i=1;i<=cnt&&p[i]*p[i]<=now;i++){
		if(a[1]%p[i]!=0)continue;
		pa.push_back(p[i]);
		while(now%p[i]==0)now/=p[i];
	}
	if(now!=1)pa.push_back(now);
	now=b[1];
	for(int i=1;i<=cnt&&p[i]*p[i]<=now;i++){
		if(b[1]%p[i]!=0)continue;
		pb.push_back(p[i]);
		while(now%p[i]==0)now/=p[i];
	}
	if(now!=1)pb.push_back(now);
	for(int i=1;i<=n;i++){
		int x=__gcd(a[1],a[i]),y=__gcd(b[1],b[i]);
		int p=__gcd(a[1],b[i]),q=__gcd(b[1],a[i]);
		m[ida[p]][idb[q]]+=c[i];
		m[ida[__gcd(x,p)]][idb[__gcd(y,q)]]-=c[i];
		cc[ida[p]][idb[q]]++;cc[ida[x]][idb[y]]++;
		cc[ida[__gcd(x,p)]][idb[__gcd(y,q)]]--;
	}
	for(int i=0;i<pa.size();i++){
		int p=pa[i];
		for(int j=da.size()-1;j>=0;j--){
			if(da[j]%p!=0)continue;
			int pos=ida[da[j]/p];
			for(int z=0;z<db.size();z++)
			m[pos][z]+=m[j][z],cc[pos][z]+=cc[j][z];
		}
	}
	for(int i=0;i<pb.size();i++){
		int p=pb[i];
		for(int j=db.size()-1;j>=0;j--){
			if(db[j]%p!=0)continue;
			int pos=idb[db[j]/p];
			for(int z=0;z<da.size();z++)
			m[z][pos]+=m[z][j],cc[z][pos]+=cc[z][j];
		}
	}
	for(int i=0;i<da.size();i++)
	for(int j=0;j<db.size();j++){
		m[i][j]+=w;
		if(cc[i][j]!=n)continue;
		if(ans.count(m[i][j]))
		ans[m[i][j]]=max(ans[m[i][j]],da[i]+db[j]);
		else ans[m[i][j]]=da[i]+db[j];
	}
}
int main(){
	cin>>n>>q;pre();
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)scanf("%d",&b[i]);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]);
	solve(0);swap(a[1],b[1]);solve(c[1]);
	map<ll,int>::iterator it=ans.begin();
	for(;it!=ans.end();it++)
	if(!la||(*it).second>la)
	la=(*it).second,s.insert({(*it).first,(*it).second});
	while(q--){
		ll d;scanf("%lld",&d);
		set<pair<ll,int> >::iterator it;
		it=s.lower_bound({d,(int)1e9});
		it--;printf("%lld ",(*it).second);
	}
	return 0;
}
```

---

## 作者：Otomachi_Una_ (赞：0)

**【题目简述】**

你有两个序列 $a,b$。你可以用 $c_i$ 的代价交换 $a_i,b_i$。在不超过 $d$ 的代价下最大化 $\gcd(a)+\gcd(b)$。

对 $d$ 多测。

$n,q\leq 5\times 10^5$，$a_i,b_i\leq 10^8$。

**【解题思路】**

考虑枚举 $a_1,b_1$ 是否交换。不难发现这样的 $(\gcd(a),\gcd(b))$ 的二元对不超过 $\mathcal O(d(a_1)d(b_1))$ 对。

考虑对每个这样的二元对算最小的代价，考虑钦定 $x=\gcd(a),y=\gcd(b)$，我们只需要满足 $x|a_i,y|b_i$ 即可（因为如果 $x<\gcd(a)$ 必然不优）。

这个与高维前缀和十分类似，我们只需要搞一种统一变换计算满足给定 $f_i$（$i$ 是 $a_1$ 的所有因子） 计算 $g_i=\sum_{i|j} f_j$ 这种东西即可。

时间复杂度：$\mathcal O(n\log V+d(V)^2\omega(V))$。

**【参考代码】**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MP make_pair
mt19937 rnd(time(0));
const int MAXN=5e5+5;
int n,q,a[MAXN],b[MAXN],c[MAXN];
map<ll,int> mp;
set<pair<ll,int> > se;
ll co[2005][2005];int cnt[2005][2005];
bool is_prime(int x){
	if(x==1) return false;
	for(int i=2;i*i<=x;i++) if(x%i==0) return false;
	return true;
}
void solve(int o){
	vector<int> da,db,pa,pb;
	map<int,int> ma,mb;int ta=0,tb=0;
	memset(co,0,sizeof(co));memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=a[1];i++) if(a[1]%i==0){
		da.push_back(i);ma[i]=(ta++);
		if(is_prime(i)) pa.push_back(i);
	}
	for(int i=1;i<=b[1];i++) if(b[1]%i==0){
		db.push_back(i);mb[i]=(tb++);
		if(is_prime(i)) pb.push_back(i);
	}
	for(int i=1;i<=n;i++){
		int x=__gcd(a[1],a[i]),y=__gcd(b[1],b[i]);
		int p=__gcd(a[1],b[i]),q=__gcd(b[1],a[i]);
		co[ma[p]][mb[q]]+=c[i];
		co[ma[__gcd(x,p)]][mb[__gcd(y,q)]]-=c[i];
		cnt[ma[x]][mb[y]]++;
		cnt[ma[p]][mb[q]]++;
		cnt[ma[__gcd(x,p)]][mb[__gcd(y,q)]]--;
	}
	for(int i:pa){
		for(int j=ta-1;j>=0;j--) if(da[j]%i==0){
			int f=ma[da[j]/i];
			for(int k=0;k<tb;k++) co[f][k]+=co[j][k],cnt[f][k]+=cnt[j][k];
		}
	}
	for(int i:pb){
		for(int k=tb-1;k>=0;k--) if(db[k]%i==0){
			int f=mb[db[k]/i];
			for(int j=0;j<ta;j++) co[j][f]+=co[j][k],cnt[j][f]+=cnt[j][k];
		}
	}
	for(int i=0;i<ta;i++) for(int j=0;j<tb;j++) co[i][j]+=o;
	for(int i=0;i<ta;i++) for(int j=0;j<tb;j++) if(cnt[i][j]==n){
		if(mp.count(co[i][j])) mp[co[i][j]]=max(mp[co[i][j]],da[i]+db[j]);
		else mp[co[i][j]]=da[i]+db[j];
	}
}
int main(){
	ios::sync_with_stdio(false);
	// freopen("Otomachi_Una.in","r",stdin);
	// freopen("Otomachi_Una.out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) cin>>b[i];
	for(int i=1;i<=n;i++) cin>>c[i];
	solve(0);swap(a[1],b[1]);
	solve(c[1]);
	int lst=0;
	for(auto i:mp) if(i.second>lst){
		se.insert({i.first,i.second}),lst=i.second;
	}
	while(q--){
		ll x;cin>>x;
		cout<<((--se.lower_bound({x+1,-1}))->second)<<' ';
	}
	return 0;
}
```

---

