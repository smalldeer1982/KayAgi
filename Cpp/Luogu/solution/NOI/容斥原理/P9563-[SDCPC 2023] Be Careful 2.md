# [SDCPC 2023] Be Careful 2

## 题目描述

小青鱼有一个位于二维平面上的，大小为 $n \times m$ 的矩形。矩形的右上角位于 $(n, m)$，而左下角位于 $(0, 0)$。矩形内部有 $k$ 个禁止点，第 $i$ 个禁止点位于 $(x_i, y_i)$。

小青鱼想在矩形里画一个正方形。但由于小青鱼不喜欢禁止点，因此正方形的内部不能有任何禁止点。更正式地，小青鱼可以画一个左下角位于 $(x, y)$ 且边长为 $d$ 的正方形，当且仅当：

- $x$ 和 $y$ 都是非负整数，$d$ 是一个正整数。
- $0 \leq x < x+d \leq n$。
- $0 \leq y < y+d \leq m$。
- 每个 $1 \leq i \leq k$ 都 **不能** 满足以下条件：
  - $x < x_i < x+d$ 且 $y < y_i < y+d$。

请计算小青鱼可以画的正方形的总面积。由于答案可能很大，请将答案对 $998244353$ 取模后输出。

## 样例 #1

### 输入

```
3 3 1
2 2
```

### 输出

```
21
```

## 样例 #2

### 输入

```
5 5 2
2 1
2 4
```

### 输出

```
126
```

# 题解

## 作者：yllcm (赞：3)

考虑容斥，枚举 $S$，那么条件相当于包含矩形 $(\min x_{S_i},\max x_{S_i}\min y_{S_i},\max y_{S_i})$，可以做到 $\mathcal{O}(2^k)$。

发现完全在矩形内部的点不影响限制，假设 $T$ 在矩形内部，那么钦定边界上的点选择的集合之后，它的贡献是 $\sum_{T_0\subseteq T}(-1)^{|T_0|}=[T=\varnothing]$，说明只有 $T$ 是空集的矩形有贡献，我们只需要考虑这些矩形。

假设所有点的横纵坐标互不相同，那么可以证明合法的矩形是 $\mathcal{O}(k^2)$ 的，因为假如我们枚举横坐标最小 / 最大的点，假设为 $p,q(y_p<y_q)$，那么矩形的纵坐标的下边界只有可能是 $y_p$ 或者在 $p,q$ 横坐标之间的点集中 $y_p$ 的前驱，上边界同理。所以任意两个点最多有 $4$ 个不同的矩形。

考虑横纵坐标有相同的情况，我们不妨给点钦定互不相同的标号，使得按照标号横坐标 / 纵坐标的权值不降，那么将这些互不相同的标号看做互不相同的横纵坐标，跑上面的算法，仍然是正确的。

所以问题转化为如何 $\mathcal{O}(1)$ 求包含某个矩形的所有正方形的大小之和。假设矩形为 $[x,y,z,w]$（描述横坐标区间为 $[x,y]$，纵坐标区间为 $[z,w]$），那么考虑边长为 $d$ 时，左下角位置点 $(u,v)$ 的条件（以下只讨论 $u$，$v$ 是对称的）

* $u\in[y-d+1,x-1]$。
* $u\in [0,n-d]$。

容易发现两个区间均非空时（$d\in [y-x+2,n]$）时刻有交，所以 $u$ 的取值个数是 $\min(x-1,n-d)-\max(y-d+1,0)+1$。所以列出式子：
$$
\sum_{d}d^2(\min(x-1,n-d)-\max(y-d+1,0)+1)(\min(z-1,m-d)-\max(w-d+1,0)+1)
$$
这是一个不超过 $4$ 次 / $5$ 段的分段函数，分段后直接求出前缀和即可。[code](https://qoj.ac/submission/201046)

---

## 作者：cmk666 (赞：1)

神 @[ftt2333](/user/34225) 好强，膜拜。

考虑容斥，记 $g_S$ 表示覆盖了点集 $S$ 的正方形的面积之和，则答案显然为 $\sum\limits_S(-1)^{|S|}g_S$。但点集有高达 $2^k$ 个，无法直接枚举。

容易发现，覆盖一个点集 $S$，等价于包含最小的覆盖点集 $S$ 的矩形，可能的最小矩形只有 $O(k^4)$ 个。转为枚举矩形，记包含矩形 $A$ 的正方形面积之和为 $f_A$，答案为 $\sum\limits_Af_A(\sum\limits_{S}(-1)^{|S|})$。

我们发现，一个不在最小矩形的边界上的点，它选或不选，对系数分别有 $1$ 和 $-1$ 的贡献，总贡献为 $0$。因此只有所有点在边界上的矩形才有用。

枚举左右的点 $(x_1,y_1),(x_2,y_2)$，那么上下的边界必然是 $y_1,y_2$ 或者 $x\in(x_1,x_2)$ 的某个前驱后继，不然矩形内会包含额外的点。这个可以排序后 $O(1)$ 维护。

于是我们在 $O(k^2)$ 的时间内找出了所有的最小矩形，并且容斥系数 $\sum\limits_{S}(-1)^{|S|}$ 实际上就是 $-1^{\text{边界上点的个数}}$。

接下来考虑 $O(1)$ 计算 $f_A$。这是经典小学奥数题，容易发现这是一个 $\le5$ 段的不超过 $4$ 次的分段多项式的和，把每段拿出来做前缀和就行了。

大常数 $O(k^2)$。

---

## 作者：_LiWenX_ (赞：0)

正方形直接做这个限制感觉不方便扫描线，所以考虑容斥，考虑一个暴力做法，枚举一个限制点集 $S$，然后求出包含这个点集的最小矩形 $T$，求出所有包含 $T$ 的正方形面积和，容斥系数是 $(-1)^{|S|}$，这些步骤是简单的。

交换求和顺序，考虑矩形 $T$ 的贡献。

矩形包含的性质非常好，发现如果 $T$ 的内部有一个限制点，那么必然所有以 $T$ 为最小包含矩形的集合 $S$，可以让它们可以依据是否包含 $x$ 而两两配对，于是这个矩形的贡献是 $0$。

所以只用考虑边界上有点的矩形 $T$。进一步的，直接枚举横坐标最大最小的两个点，然后求出这两个点的矩形，这个矩形按照上述规则只能向上或向下拓展，触及一个前驱或后继点。

但是边界上的点稍微有点问题，可以把每一个点开一个二元的权值，就可以比较与判断是否合法了，具体实现可以参考代码。

现在考虑包含一个矩形的所有正方形面积和，假如这个矩形覆盖横坐标范围 $[x,y]$，覆盖纵坐标范围 $[l,r]$，可以枚举一下正方形的边长 $d$，然后考虑每一维的取值范围再全部乘到一起去就好了，不过这么计算是 $O(V)$ 的。

如何继续优化，发现式子里面有一些 $\min,\max$，所以这个东西是个分 $O(1)$ 段的多项式，直接使用拉格朗日插值计算多项式区间和。

但是这个做法要轻微卡常的，拉插还是太慢了一些，注意一下这个插值对象是一个 $4$ 次多项式，前缀和就是 $5$ 次的，然后需要 $6$ 项才能计算。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
using namespace std;
int quickpow(int a,int b){
	int ret=1;
	while(b){
		if(b&1) ret=1ll*ret*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}return ret;
}
int inv[4587];
int s1[1000005],s2[1000005];
int askinv(int x){
	if(x<0) return mod-inv[-x];
	return inv[x];
}
void init(int n=4000){
	for(int i=1;i<=n;i++) inv[i]=quickpow(i,mod-2);
	s1[0]=s2[0]=1;
	for(int j=1;j<=n;j++){
		s1[j]=1ll*s1[j-1]*askinv(j)%mod;
		s2[j]=1ll*s2[j-1]*askinv(-j)%mod;
	}
}
int pre[1000005],suf[1000005];
int vec[1000005];
int lag(int k){
	if(k<6) return vec[k];
	for(int j=0;j<6;j++){
		pre[j]=k-j;
		if(j) pre[j]=1ll*pre[j-1]*pre[j]%mod;
	}
	suf[6]=1;
	for(int j=6-1;~j;j--){
		suf[j]=k-j;
		if(j+1!=6) suf[j]=1ll*suf[j]*suf[j+1]%mod;
	}
	ll ret=0;
	for(int i=0;i<6;i++){
		int fz=suf[i+1]%mod;
		if(i) fz=1ll*fz*pre[i-1]%mod;
		int fm=s2[6-i-1];
		fm=1ll*fm*s1[i]%mod;
		ret+=1ll*vec[i]*fz%mod*fm%mod;
	}
	ret%=mod;
	return ret;
}
int all(int n,int m){
	for(int d=1;d<=6;d++){
		int y=1ll*d*d%mod*(n-d+1)%mod*(m-d+1)%mod; 
		if(d==1) vec[d-1]=y;
		else vec[d-1]=(vec[d-2]+y)%mod;
	}
	return lag(min(n,m)-1);
}
int n,m,k;
int in(int x,int y,int l,int r){
	if(l>r) swap(l,r);
	ll ret=0;
	int L=max(y-x+2,r-l+2),R=min(n,m);
	vector<int> p={L,R+1,n-x+1,y+1,m-l+1,r+1};
	sort(p.begin(),p.end());
	auto ask=[&](int d){
		int ret=1ll*d*d%mod*(min(x-1,n-d)-max(y-d+1,0)+1)%mod*(min(l-1,m-d)-max(r-d+1,0)+1)%mod;
		if(d<l||d>r) ret=0;
		return ret; 
	};
	for(int i=0;i+1<(int)p.size();i++){
		int a=p[i],b=p[i+1]-1;
		if(a<L||a>R) continue;
		if(b-a+1<=6){
			for(int d=a;d<=b;d++) ret+=ask(d);
		}
		else{
			for(int d=a;d<a+6;d++){
				if(d==a) vec[d-a]=ask(d);
				else{
					vec[d-a]=(ask(d)+vec[d-a-1])%mod;
				}
			}
			ret+=lag(b-a);
		}
	}
	ret%=mod;
	return ret;
}
struct node{
	pair<int,int> x,y;
}a[5005];
pair<int,int> x[5005],y[5005];
int Pre[5005][5005],Suf[5005][5005];
map<int,int> ma[5005];
int inf=1e9+4587;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	init();
	cin>>n>>m>>k;
	ll ans=all(n,m);
	for(int i=1;i<=k;i++){
		cin>>a[i].x.first>>a[i].y.first;
		a[i].x.second=a[i].y.second=i;
	}
	sort(a+1,a+1+k,[](node x,node y){
		return x.x<y.x;
	});
	for(int i=1;i<=k;i++){
		x[i]=a[i].x,y[i]=a[i].y;
	}
	
	vector<pair<int,int> > vec;
	for(int i=1;i<=k;i++){
		ans-=in(x[i].first,x[i].first,y[i].first,y[i].first);
		int pre=0,suf=0;
		for(int j=i+1;j<=k;j++){
			if((!pre||y[pre]>max(y[j],y[i]))&&(!suf||y[suf]<min(y[i],y[j]))){
				ans+=in(x[i].first,x[j].first,y[i].first,y[j].first);
				if(pre) ans-=in(x[i].first,x[j].first,y[pre].first,min(y[i],y[j]).first);
				if(suf) ans-=in(x[i].first,x[j].first,y[suf].first,max(y[i],y[j]).first);
				if(pre&&suf) ans+=in(x[i].first,x[j].first,y[pre].first,y[suf].first);
			}
			if(y[i]<y[j]&&(!pre||y[pre]>y[j])) pre=j;
			if(y[i]>y[j]&&(!suf||y[suf]<y[j])) suf=j;
		}
	}
	ans=(ans%mod+mod)%mod;
	cout<<ans<<'\n';
}
```

---

## 作者：ljw0102 (赞：0)

不考虑容斥，从上往下扫描线。

将所有点按照横坐标排序，从大到小加入每个点，每次只统计下边界横坐标在 $[x_{i-1},x_i)$ 的所有正方形，考虑其上边界所在的位置。

先将加入的所有点按 $y$ 排序（可以插入排序）。画图发现有两种情况：

1. 对一个点 $(x_i,y_i)$，单调栈求出每个点左边第一个 $x<x_i$ 的点（设为 $(x_j,y_j)$）、右边第一个 $x<x_i$ 的点（设为 $(x_k,y_k)$），上边界在 $\max(x_j,x_k)+1\le x\le x_i,y_j\le y\le y_k$ 这样一个矩形中（注意不要算重）；

2. 考虑相邻两个点 $(x_i,y_i),(x_{i+1},y_{i+1})$，若 $y_i<y_{i+1}$，则上边界在 $\max(x_i,x_{i+1})+1\le x\le n,y_i\le y\le y_{i+1}$ 这样一个矩形中。 

转化为求解 $f(n,m,d,u)$：$n\times m$ 的矩形内，上边界横坐标在 $[u,m]$，下边界横坐标在 $[0,d]$ 的正方形个数。

简单容斥一下：设 $g(n,m)$ 表示 $n\times m$ 的矩形内的正方形个数，$f(n,m,d,u)=g(n,m)-g(u-1,m)-g(n-d-1,m)+g(u-d-2,m)$。而 $g(n,m)$ 是好求的：

$$g(n,m)=\sum_{d=1}^{\min(n,m)}(n-d+1)(m-d+1)d^2$$

是一个四次多项式前缀和的形式，拆成平方和、三次方和、四次方和即可。放一下比较冷门的四次方和公式：

$$\sum_{i=1}^ni^4=\dfrac{n^5}5+\dfrac{n^4}2+\dfrac{n^3}3-\dfrac{n}{30}$$

复杂度 $O(k^2)$。代码实现略有不同。


```cpp
#include<bits/stdc++.h>
#define N 5005
#define ll long long
#define mod 998244353
#define inv2 499122177
#define inv3 332748118
#define inv5 598946612
#define inv6 166374059
using namespace std;
int n,m,k;
struct point{
	int x,y;
}a[N];
bool cmpx(point a,point b){
	return a.x<b.x;
}
bool cmpy(point a,point b){
	return a.y<b.y||a.y==b.y&&a.x<b.x;
}
ll qmi(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%mod) if(b&1) ans=ans*a%mod;
	return ans;
}
ll S1(ll n){
	return n*(n+1)%mod*inv2%mod;
}
ll S2(ll n){
	return n*(n+1)%mod*(n*2+1)%mod*inv6%mod;
}
ll S3(ll n){
	return S1(n)*S1(n)%mod;
}
ll S4(ll n){
	return (qmi(n,5)*inv5%mod+qmi(n,4)*inv2%mod+qmi(n,3)*inv3%mod-n*inv6%mod*inv5%mod+mod)%mod;
}
ll calc0(ll a2,ll a3,ll a4,ll n){
	return (a2*S2(n)+a3*S3(n)+a4*S4(n))%mod;
}
ll calc1(int n,int m){
	if(n<=0||m<=0) return 0;
	return calc0((ll)(n+1)*(m+1)%mod,(mod-(n+m+2)%mod)%mod,1,min(n,m));
}
ll calc2(int n,int m,int d,int u){
	if(n<=0||m<=0||u-d>m||u>n) return 0;
	return ((calc1(n,m)-calc1(u-1,m)-calc1(n-d-1,m)+calc1(u-d-2,m))%mod+mod)%mod;
}
ll ans;
int st[N],top;
int pl[N],pr[N],d[N],tag[N];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=k;i++) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+k+1,cmpx);
	ans=calc1(n-a[k].x,m);
	for(int i=k;i>=1;i--){
		if(a[i].x==a[i-1].x) continue;
		int d1=a[i-1].x,d2=a[i].x-1-a[i-1].x;
		sort(a+i,a+k+1,cmpy);
		top=0;
		for(int j=i;j<=k;j++){
			tag[j]=0,d[j]=d1;
			while(top&&a[st[top]].x>a[j].x) top--;
			if(top&&a[st[top]].x==a[j].x) tag[j]=1,top--;
			if(top) pl[j]=a[st[top]].y,d[j]=max(d[j],a[st[top]].x);
			else pl[j]=0;
			st[++top]=j;
		}
		top=0;
		for(int j=k;j>=i;j--){
			while(top&&a[st[top]].x>=a[j].x) top--;
			if(top) pr[j]=a[st[top]].y,d[j]=max(d[j],a[st[top]].x);
			else pr[j]=m;
			st[++top]=j;	
		}
		for(int j=i;j<=k;j++){
			if(tag[j]) continue;
			ans=(ans+calc2(a[j].x-d1,pr[j]-pl[j],d2,d[j]+1-d1));
		}
		ans=(ans+calc2(n-d1,a[i].y,d2,a[i].x+1-d1))%mod;
		ans=(ans+calc2(n-d1,m-a[k].y,d2,a[k].x+1-d1))%mod;
		for(int j=i;j<k;j++) ans=(ans+calc2(n-d1,a[j+1].y-a[j].y,d2,max(a[j+1].x,a[j].x)+1-d1))%mod;
	}
	printf("%lld\n",ans);
	return 0;
}


```

---

