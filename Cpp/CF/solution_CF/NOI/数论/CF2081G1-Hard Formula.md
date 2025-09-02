# Hard Formula

## 题目描述

这是本题的简单版本。两个版本的区别在于此版本对 $n$ 的限制和时间限制更小。只有当您解决了该问题的所有版本时才能进行 hack。

给定一个整数 $n$，你需要计算 $(\sum_{k=1}^n k \bmod \varphi(k)) \bmod 2^{32}$，其中 $\varphi(k)$ 表示不大于 $k$ 且与 $k$ 互质的正整数的数量。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
5```

### 输出

```
2```

## 样例 #2

### 输入

```
10000000```

### 输出

```
2316623097```

## 样例 #3

### 输入

```
10000000000```

### 输出

```
282084447```

# 题解

## 作者：diqiuyi (赞：0)

注意到 $\dfrac{n}{\varphi(n)}$ 在数据范围内不超过 $6$。

显然答案为：

$\begin{aligned}\sum_{i=1}^n i-\lfloor{\dfrac{i}{\varphi(i)}}\rfloor\varphi(i)&=i(i+1)/2-\sum_{j=1}^6 \sum_{i=1}^n[\lfloor{\dfrac{i}{\varphi(i)}}\rfloor\ge j]\varphi(i)\end{aligned}$

我们考虑枚举 $j$，再爆搜 $i$ 的较小的质因子，当 $\dfrac{i}{\varphi(i)}\ge j$ 或把往后连续尽可能多的质数都选上也无法使 $\dfrac{i}{\varphi(i)}\ge j$ 时就退出。假设我们爆搜得到的数是 $s$，它对答案的贡献即为 $-\sum_{xs\le n}[\operatorname{minp}(x)>\operatorname{maxp}(s)]\varphi(x)\varphi(s)$。

当 $n\le 10^{10}$ 时，这样的 $s$ 只有一百多万个，而 $\sum_{xs\le n}[\operatorname{minp}(x)>\operatorname{maxp}(s)]\varphi(x)\varphi(s)$ 可以先把询问存在 $\operatorname{maxp}(s)$ 处，在 min_25 的时候计算即可。

注意 $\varphi(x)$ 并非完全积性函数，所以设 $g(x,j)=\sum_{i=1}^x [\operatorname{minp}(i)>j \lor i\in \mathbb P]\varphi(i)$，$p_i$ 表示第 $i$ 个质数，$sp_i$ 表示前 $i$ 个质数的 $\varphi$ 的和，则转移的式子是 $g(x,j)=g(x,j-1)-\sum_{p_j^i\le x}p_j^{i-1}(p_j-1)\max(g(\dfrac{x}{p_j^i},j)-sp_i-[i=1],1)(p_j^2\le x)$，$g(x,0)$ 的值似乎需要杜教。

时间复杂度为 $O(\dfrac{n^{3/4}}{\log n}+n^{2/3})$，可以跑 $n\le 10^{10}$。
```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define uint unsigned int
#define pii pair<int,int>
#define io ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
inline int read(){
	int x=0;bool f=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=0;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f?x:-x;
}
const int B=5e6;
ll n,val[200005];
int tot,sq,p[B>>3],cnt,all,num,id1[100005],id2[100005],mp[1000000];
uint g[200005],phi[B+5],ans,res[200005],sphi[30005],sum[200005];
bitset<B+5> vis; 
vector<pair<uint,uint> > vc[30000];
int id(ll x){
	if(x<=sq) return id1[x];
	return id2[n/x];
}
void dfs(int x,ll now,ll s,int mb,int maxp){
	if(s>n) return ;
	if(s>=mb*now){
		all=max(all,maxp);
		vc[maxp].push_back({id(n/s),(uint)now});
		return ;
	}
	if(x>cnt){
		cout<<"!\n";
		return ;
	}
	ll ns=s,nn=now;
	for(int i=x;i<=cnt&&ns*p[i]<=n;i++)
		nn*=(p[i]-1),ns*=p[i];
	if(ns<mb*nn) return ;
	bool flg=0;
	do{
		dfs(x+1,now,s,mb,flg?x:maxp);
		if(!flg) now*=(p[x]-1);
		else now*=p[x];
		s*=p[x];
		flg=1;
	}while(s<=n);
}
uint getphi(ll x){
	if(x<=B) return phi[x];
	if(res[id(x)]) return res[id(x)];
	uint re=(__int128)x*(x+1)/2;
	for(ll l=2,r;l<=x;l=r+1)
		r=x/(x/l),re-=(r-l+1)*getphi(x/l);
	return res[id(x)]=re;
}
int main(){
	cin>>n,sq=sqrt(n);
	double c=clock(); 
	ans=(__int128)n*(n+1)/2;
	phi[1]=1;
	for(int i=2;i<=B;i++){
		if(!vis[i]) p[++cnt]=i,phi[i]=i-1;
		for(int j=1;p[j]*i<=B;j++){
			vis[i*p[j]]=1;
			if(!(i%p[j])){
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	for(int i=1;i<=B;i++) phi[i]+=phi[i-1];
	for(int i=1;p[i]<=sq;i++) sum[i]=sum[i-1]+p[i];
	for(ll l=1,r;l<=n;l=r+1){
		r=n/(n/l),val[++tot]=r;
		if(r<=sq) id1[r]=tot; 
		else id2[n/r]=tot;
	}
	for(int i=1;i<=tot;i++) g[i]=getphi(val[i]);
	ans-=g[tot];
	for(int i=2;i<=6;i++)
		dfs(1,1,1,i,0);
	for(int i=1;i<=all;i++){
		sphi[i]=sphi[i-1]+p[i]-1;
		for(int j=p[i];j<p[i+1];j++) mp[j]=i;
	}
	for(int i=1;i<=all;i++){
		for(int j=lower_bound(val+1,val+tot+1,1ll*p[i]*p[i])-val;j<=tot;j++)
			for(ll pw=1;pw*p[i]<=val[j];pw*=p[i])
				g[j]-=(uint)pw*(p[i]-1)*(val[j]/pw/p[i]>=p[i]?g[id(val[j]/pw/p[i])]-sphi[i]-(pw==1):1);
		for(auto x:vc[i])
			ans-=(uint)x.second*(val[x.first]<p[i]?1:g[x.first]-sphi[i]);
	}
	cout<<ans<<'\n';
    return 0;
}
```

---

