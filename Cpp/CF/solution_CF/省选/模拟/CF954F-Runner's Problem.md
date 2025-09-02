# Runner's Problem

## 题目描述

You are running through a rectangular field. This field can be represented as a matrix with $ 3 $ rows and $ m $ columns. $ (i,j) $ denotes a cell belonging to $ i $ -th row and $ j $ -th column.

You start in $ (2,1) $ and have to end your path in $ (2,m) $ . From the cell $ (i,j) $ you may advance to:

- $ (i-1,j+1) $ — only if $ i&gt;1 $ ,
- $ (i,j+1) $ , or
- $ (i+1,j+1) $ — only if $ i&lt;3 $ .

However, there are $ n $ obstacles blocking your path. $ k $ -th obstacle is denoted by three integers $ a_{k} $ , $ l_{k} $ and $ r_{k} $ , and it forbids entering any cell $ (a_{k},j) $ such that $ l_{k}<=j<=r_{k} $ .

You have to calculate the number of different paths from $ (2,1) $ to $ (2,m) $ , and print it modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
2 5
1 3 4
2 2 3
```

### 输出

```
2
```

# 题解

## 作者：hfctf0210 (赞：3)

这题是一年前某场我参加过的Education Round codeforces的F题，当时我显然是不会的。

现在看看感觉应该是能做出的。

不扯了写题解：

考虑朴素的DP，在不存在障碍的情况下：f[i][0]=f[i-1][0]+f[i-1][1],f[i][1]=f[i-1][0]+f[i-1][1]+f[i-1][2],f[i][2]=f[i-1][1]+f[i-1][2]。

然后由于N范围不太大而M有1e18，一脸矩乘的样子。

没有障碍物显然可以构造如下矩阵：

0  1  1

1  1  1

1  1  0

然后直接快速幂就行了。

考虑某一行出现障碍物，实际上是将该列的矩阵的值全部变为0

然后可以把每一段离散化建立矩阵，分段矩阵乘法就行了

notice：注意若从前向后计算出每一段的最后矩阵t后，一定是ans=t×ans而不是ans=ans×t！！

时间复杂度：O(nlogn+27nlogM)

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e4+7,mod=1e9+7;
struct mat{
	int a[3][3];
	void clear(){memset(a,0,sizeof a);}
	void init(){clear();a[0][0]=a[1][1]=a[2][2]=1;}
	void zero(){init();a[0][1]=a[1][0]=a[1][2]=a[2][1]=1;}
};
struct node{ll l,r;int a;}a[N];
int n,num;
ll m,b[N<<1],c[3][N<<1],sc[3];
mat operator*(mat a,mat b)
{
	mat c;c.clear();
	for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
	for(int k=0;k<3;k++)
	c.a[i][j]=(c.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%mod;
	return c;
}
mat qpow(mat a,ll b)
{
	mat ret;ret.init();
	while(b){if(b&1)ret=ret*a;a=a*a,b>>=1;}
	return ret;
}
int main()
{
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%lld%lld",&a[i].a,&a[i].l,&a[i].r),a[i].a--;
		b[++num]=a[i].l-1,b[++num]=a[i].r;
	}
	b[++num]=1,b[++num]=m;
	sort(b+1,b+num+1),num=unique(b+1,b+num+1)-b-1;
	for(int i=1;i<=n;++i)
	{
		int L=lower_bound(b+1,b+num+1,a[i].l)-b,R=lower_bound(b+1,b+num+1,a[i].r)-b;
		c[a[i].a][L]++,c[a[i].a][R+1]--;
	}
	mat ans;ans.clear();
	ans.a[1][0]=1;
	for(int i=2;i<=num;i++)
	{
		mat t;t.zero();
		for(int j=0;j<3;j++)
		{
			sc[j]+=c[j][i];
			if(sc[j])t.a[j][0]=t.a[j][1]=t.a[j][2]=0;
		}
		t=qpow(t,b[i]-b[i-1]);
		ans=t*ans;
	}
	printf("%d",ans.a[1][0]);
}
```


---

## 作者：2huk (赞：2)


## 题目描述

有一个 $3 \times m$ 的田野，一开始你在 $(2, 1)$ 位置。

如果你在 $(i,j)$ 位置，在不出界的前提下，可以走到 $(i+1,j),(i+1,j\pm 1)$。

有 $n$ 段障碍，障碍不能走。每段障碍都有 $3$ 个参数 $a_i,l_i,r_i$，表示这段障碍在第 $a_i$ 行，且左右端点分别为 $l_i$ 和 $r_i$。具体地，对于所有的 $l_i \le j \le r_i$，田野的 $(a_i, j)$ 上有障碍。

询问从 $(2, 1)$ 到达 $(2, m)$ 的方案数，答案对 $10^9 + 7$ 取模。

$1 \le n \le 10^4,\ 3 \le m \le 10^{18}$

## 分析

首先考虑没有障碍的情况。易得递推式：$f_{1, i} = f_{1, i - 1} + f_{2, i - 1},\ f_{2, i} = f_{1, i - 1} + f_{2, i - 1} + f_{3, i - 1},\ f_{3, i} = f_{2, i - 1} + f_{3, i - 1}$。

由于 $m$ 过大，所以可以矩阵加速。两个矩阵分别是这个样子：
$$
A = \begin{bmatrix} f_{1, i} & f_{2, i} & f_{3, i}\end{bmatrix},\ B = \begin{bmatrix} 1 & 1 & 0\\ 1 & 1 & 1\\ 0 & 1 & 1\end{bmatrix}
$$
所以没有障碍的答案应该为 $\begin{bmatrix} 0 & 1 & 0\end{bmatrix} \times \begin{bmatrix} 1 & 1 & 0\\ 1 & 1 & 1\\ 0 & 1 & 1\end{bmatrix} ^ {m - 1}$ 这个矩阵的 $(1, 2)$ 项。

但是有了障碍题目就变得复杂了。由于数据范围过大，所以首先将障碍物的位置离散化。 然后统计出差分数组。

接下来对于每一段连续的障碍物状态相同的列分别计算。如果在这些连续的列中的第 $x$ 行上有障碍物，那么就把 $B$ 矩阵的第 $x$ 行全部变成 $0$。这样处理完后再进行矩阵快速幂就没有问题了。

剩下的是一些代码细节：离散化的过程为 `sort` + `unique` + `lower_bound`，差分后需要统计一个前缀和数组，矩阵乘法和快速幂可以写成函数方便代码。

[$\text{Code}$](https://codeforces.com/contest/954/submission/207296442)

---

## 作者：jucason_xu (赞：1)


首先看到 $10^{18}$ 的范围，就能想到矩阵优化。

然后对于作用于区间的限制，我们可以对每一行开一个 `set` 维护区间上的所有限制（类似珂朵莉树），然后把所有区间端点离散化，对于所有限制条件相同的区间我们分段处理即可。

考虑如何构造矩阵。我们发现，从 $i$ 能转移到 $j$，一定是 $i$ 能到达且 $j$ 能到达。但是，这样就很难在相邻的两个区间 $[l,d]$ 和 $[d+1,r]$ 之间转移。也就是我们需要单独处理 $d\rightarrow d+1$ 的这一次转移。这样不好，考虑更好的写法。

那么，我们就令：$i$ 能转移到 $j$，只要 $i$ 上没有障碍即可。下一次转移是否采用 $j$ 是视下一次的障碍而定的。

为什么这样做是对的呢？因为如果下一次转移时，$j$ 被禁用了，那么即使 $j$ 被转移到了也不会对后面的结果造成影响。而如果 $j$ 在后一行的限制中没有被限制，就可以从 $j$ 往后转移。

这样，我们一次转移就可以直接从 $[l,r]$ 的 $l$ 直接转移到 $r+1$。

然后就可以分段快速幂求出 $f_{2,m}$。

```cpp
#define rd(i,n) for(int i=0;i<n;i++)
#define rp(i,n) for(int i=1;i<=n;i++)
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=b;i>=a;i--)
#define st string
#define vt vector
#define pb push_back
#define int long long
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const ll P=1000000007;
map<int,int>bid[3];
int n,m,a,l,r;
ll f[3];
vt<int>vg;
struct matrix{
	vt<vt<ll> >a;
	matrix operator *(const matrix b)const{
		matrix p(0,0);
		vt<vt<ll> >res(a.size(),vt<ll>(b.a[0].size(),0ll));
		rd(i,a.size()){
			rd(j,b.a[0].size()){
				rd(k,b.a.size()){
					res[i][j]=(res[i][j]+a[i][k]*b.a[k][j]%P)%P;
				}
			}
		}
		p.a=res;
		return p;
	}
	matrix(int n,int m){
		vt<vt<ll> >v(n,vt<ll>(m,0ll));
		a=v;
	}
};
inline matrix mpow(matrix a,ll p){
	if(p==1)return a;
	matrix res=mpow(a,p>>1);
	if(p&1)return res*res*a;
	return res*res;
}
bool f_(int a,int x){
	auto k=bid[a].upper_bound(x);
	if(k!=bid[a].begin()){
		k--;
		if(k->first<=x&&k->second>=x)return 1;
	}
	return 0;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m;
	vg.pb(1);
	vg.pb(m-1);
	vg.pb(m);
	rp(i,n){
		cin>>a>>l>>r;
		vg.pb(l);
		if(r<m-1)vg.pb(r+1);
		a--;
		auto k=bid[a].upper_bound(l);
		if(k!=bid[a].begin()){
			k--;
			if(k->second>=l){
				l=min(l,k->first),r=max(r,k->second);
				bid[a].erase(k);
			}
		}
		vt<int>v;
		auto d=bid[a].lower_bound(l);
		while(d!=bid[a].end()&&d->first<=r){
			l=min(l,d->first),r=max(r,d->second);
			v.pb(d->first);
			d++;
		}
		for(auto i:v)bid[a].erase(i);
		bid[a][l]=r;
	}
	sort(vg.begin(),vg.end());
	vg.erase(unique(vg.begin(),vg.end()),vg.end());
	matrix f(3,1);
	f.a[0][0]=0,f.a[1][0]=1,f.a[2][0]=0;
	rd(d,vg.size()-1){
		int pp[3];
		rd(i,3)pp[i]=f_(i,vg[d]);
		matrix mx(3,3),k(3,3);
		rd(i,3)rd(j,3)if(!pp[i]&&!pp[j]&&abs(i-j)<2)mx.a[i][j]=1;
		rd(i,3)rd(j,3)if(!pp[i]&&abs(i-j)<2)k.a[j][i]=1;
		if(vg[d+1]-vg[d]>1)f=mpow(mx,vg[d+1]-vg[d]-1)*f;
		f=k*f;
	}
	if(!f_(1,m))cout<<f.a[1][0]<<endl;
	else cout<<0<<endl;
	return 0;
}
//Crayan_r
```

---

## 作者：Adove (赞：1)

离散化+矩阵快速幂

首先看数据范围可以确定该题的算法为矩阵快速幂

然后易得转移矩阵

$$\begin{bmatrix} 1 & 1 & 0 \\ 1 & 1 & 1 \\ 0 & 1 & 1 \end{bmatrix}$$

然后把障碍离散下来重构，获取每段区间内障碍的情况（共$2^3=8$种）

重构的时候用辅助变量$pre$表示上一段区间对应的情况，易得重构部分的算法

若某一列有障碍，则将转移矩阵中的这一列全置0即可

为了减小代码复杂度，我们将每种情况与预处理后的转移矩阵一一对应，即可快速选择需要的转移矩阵

代码中用对应$.kd$二进制位为1表示该列有障碍

初始矩阵显然是

$$\begin{bmatrix} 0 \\ 1 \\ 0 \end{bmatrix}$$

分段求矩阵快速幂即可

时间复杂度$\Theta(n \log n + siz^3n \log m)$

```cpp
#include"cstdio"
#include"cstring"
#include"iostream"
#include"algorithm"
using namespace std;

const int siz=8;
const int MAXN=1e4+5;
const int MOD=1e9+7;

int n,pre,np;
long long m;
int cnt[siz];
struct Matrix{
	int v[siz][siz];
	int x,y;

	void clear(){memset(v,0,sizeof(v));x=y=0;}
	void Mmul(Matrix a,Matrix b)
	{
		clear();x=a.x,y=b.y;int c=a.y;
		for(int i=1;i<=x;++i){
			for(int j=1;j<=y;++j){
				for(int k=1;k<=c;++k){
					v[i][j]+=(long long)a.v[i][k]*b.v[k][j]%MOD;
					v[i][j]%=MOD;
				}
			}
		}return;
	}

	Matrix Mpw(Matrix a,long long b)
	{
		Matrix x;x.clear();x.x=x.y=a.x;
		for(int i=1;i<=x.x;++i) x.v[i][i]=1;
		while(b){
			if(b&1) x.Mmul(x,a);
			b>>=1;a.Mmul(a,a);
		}return x;
	}

	void write()
	{
		for(int i=1;i<=x;++i){
			for(int j=1;j<=y;++j){
				printf("%d ",v[i][j]);
			}puts("");
		}puts("");
		return;
	}
}A[siz],B;
struct rpg{
	long long x;
	int h;
	bool kd;
}a[MAXN<<1];
struct lint{
	long long siz;
	int kd;
}line[MAXN<<1];

bool cmp(rpg a,rpg b){return a.x<b.x;}
void build()
{
	for(int i=0;i<siz;++i) A[i].x=A[i].y=3;
	for(int i=0;i<siz;++i){
		for(int j=1;j<=2;++j){
			for(int k=1;k<=2;++k){
				A[i].v[j][k]=A[i].v[4-j][4-k]=1;
			}
		}for(int j=0;j<3;++j){
			if(i&(1<<j)){
				for(int k=1;k<=3;++k){
					A[i].v[k][j+1]=0;
				}
			}
		}
	}B.x=3,B.y=B.v[2][1]=1;
	return;
}

void init()
{
	build();
	scanf("%d%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d%lld%lld",&a[i].h,&a[i].x,&a[i+n].x),a[i+n].kd=1,a[i+n].h=a[i].h,++a[i+n].x;
	sort(a+1,a+(n<<1)+1,cmp);np=line[1].siz=1;
	for(int i=1;i<=n<<1;++i){
		if(a[i].kd) --cnt[a[i].h];
		else ++cnt[a[i].h];
		if(a[i+1].x!=a[i].x){
			int nw=0;
			for(int j=1;j<=3;++j) if(cnt[j]) nw|=1<<j-1;
			if(nw!=pre){
				line[np].siz=a[i].x-line[np].siz;
				pre=nw;
				line[++np]=(lint){a[i].x,pre};
			}
		}
	}line[np].siz=m-line[np].siz;
	return;
}

void solve()
{
	for(int i=1;i<=np;++i) B.Mmul(A[line[i].kd].Mpw(A[line[i].kd],line[i].siz),B);
	printf("%d\n",B.v[2][1]);
	return;
}

int main()
{
	init();
	solve();
	return 0;
}
```



---

## 作者：zdd6310 (赞：0)

# CF954F Runner's Problem
先讨论两个简单情况。

### $m$ 的数据范围很小

可以直接递推。

具体的，设 $f_{i,j}$ 表示从 $(2,1)$ 走到 $(i,j)$ 的方案数。

递推式子：
$$
f_{1,i}=f_{1,i-1}+f_{2,i-1}\\
f_{2,i}=f_{1,i-1}+f_{2,i-1}+f_{3,i-1}\\
f_{3,i}=f_{2,i-1}+f_{3,i-1}\\
$$

### 没有障碍

发现上面的转移的系数不受函数值影响。

也就是可以矩阵快速幂。
$$
\begin{bmatrix}
 f_{1,i-1} & f_{2,i-1} & f_{3,i-1}
\end{bmatrix}
\begin{bmatrix}
 1 & 1 & 0\\
 1 & 1 & 1\\
 0 & 1 & 1
\end{bmatrix}
=
\begin{bmatrix}
 f_{1,i} & f_{2,i} & f_{3,i}
\end{bmatrix}
$$

## 最终做法

首先，把每一行的障碍区间能够合并的都合并，保证每一行的障碍不交。这个是简单的。

然后，把每一段都离散化。

也就是，对于一个区间 $[l,r]$，把 $l-1,l,r,r+1$ 全部放进数组离散化。

然后，对于离散化的一段区间，它们的障碍位置都是相同的，就有矩阵快速幂的条件了。

但是转移矩阵的系数不一样。不一样在哪里？

区别就是障碍位置的 $f$ 数组的值是 $0$。

相当于转移矩阵的那一列是 $0$。

然后就可以矩阵快速幂了。

复杂度 $O(n\log n +T^3n\log m)$。

其中 $T$ 是矩阵大小，这里取 $3$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define Pair pair<int,int>
#define F(i,a,b) for(int i=a;i<=(b);i++)
#define dF(i,a,b) for(int i=a;i>=(b);i--)
using namespace std;
const int MAXN=1e4+5;
const int inf=1e9;
const int mod=1e9+7;
int n,m;
vector<Pair>G[4],Q[4];
int lin[MAXN*30],tmp;
int siz[MAXN*30],tim[4][MAXN*30];
struct matrix{
    int z[4][4];
    int* operator [](int x){return z[x];}
    inline void clear(){F(i,1,3)F(j,1,3)z[i][j]=0;}
    inline friend matrix operator *(matrix a,matrix b){
        matrix c;c.clear();
        F(k,1,3)F(i,1,3)F(j,1,3){
            (c[i][j]+=(a[i][k]*b[k][j]%mod))%=mod;
        }
        return c;
    }
}all;
inline void ksm_add(matrix& fir,matrix a,int b){
    while(b){
        if(b&1)fir=fir*a;
        a=a*a;b>>=1;
    }
}
signed main(){
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int col,l,r;cin>>col>>l>>r;
        G[col].push_back(Pair(l,r));
    }
    for(int col=1;col<=3;col++){
        sort(G[col].begin(),G[col].end());
        for(int i=0;i<G[col].size();i++){
            int lst=G[col][i].second,now=i;
            while((now+1)<G[col].size()&&G[col][now+1].first<=lst){
                lst=max(lst,G[col][now+1].second);now++;
            }
            Q[col].push_back(Pair(G[col][i].first,lst));
            i=now;
        }
    }
    for(int col=1;col<=3;col++){
        for(auto [l,r]:Q[col]){
            lin[++tmp]=l-1,lin[++tmp]=l;
            lin[++tmp]=r,lin[++tmp]=r+1;
        }
    }
    lin[++tmp]=m-1;
    sort(lin+1,lin+tmp+1);tmp=unique(lin+1,lin+tmp+1)-(lin+1);
    #define Find(x) (lower_bound(lin+1,lin+tmp+1,x)-lin)
    tmp=Find(m-1);
    for(int col=1;col<=3;col++){
        for(auto [l,r]:Q[col]){
            l=Find(l),r=Find(r);
            tim[col][l]++,tim[col][r+1]--;
        }
    }
    for(int col=1;col<=3;col++)
        for(int i=1;i<=tmp;i++)tim[col][i]+=tim[col][i-1];
    matrix all;all.clear();
    all[1][1]=1,all[1][2]=1,all[1][3]=0;
    all[2][1]=1,all[2][2]=1,all[2][3]=1;
    all[3][1]=0,all[3][2]=1,all[3][3]=1;
    matrix st;st.clear();
    st[1][2]=1;
    for(int i=1;i<=tmp;i++){
        lin[i-1]=max(lin[i-1],1ll);
        lin[i]=max(lin[i],1ll);
        int len=lin[i]-lin[i-1];
        matrix del=all;
        if(tim[1][i])del[1][1]=del[2][1]=del[3][1]=0;
        if(tim[2][i])del[1][2]=del[2][2]=del[3][2]=0;
        if(tim[3][i])del[1][3]=del[2][3]=del[3][3]=0;
        ksm_add(st,del,len);
    }
    int ans=(st[1][1]+st[1][2]+st[1][3])%mod;
    cout<<ans<<"\n";
}
```

---

## 作者：Fimlty (赞：0)

# CF954F 题解

- **题意**

  ​	有一个 $3 \times m$ 的田野，一开始你在 $(2, 1)$ 位置。

  ​	如果你在 $(i,j)$ 位置，在不出界的前提下，可以走到 $(i,j+1),(i\pm 1,j+1)$。
  
  ​	有 $n$ 段障碍，障碍不能走。每段障碍都有 $3$ 个参数 $a_i,l_i,r_i$，表示这段障碍在第 $a_i$ 行，且左右端点分别为 	$l_i$ 和 $r_i$。具体地，对于所有的 $l_i \le j \le r_i$，田野的 $(a_i, j)$ 上有障碍。
  
  ​	询问从 $(2, 1)$ 到达 $(2, m)$ 的方案数，答案对 $10^9 + 7$ 取模。

- **Pre**

    ​	对于没有障碍限制的情况，设 $dp_{i,0/1/2}$ 到达 $(i,0/1/2)$ 的方案数。
    
    ​	有转移如下：
    
    ​	$dp_{i,0} = dp_{i-1,0} + dp_{i-1,1}$
    
    ​	$dp_{i,1} = dp_{i-1,0} + dp_{i-1,1} + dp_{i-1,2}$
    
    ​	$dp_{i,2} = dp_{i-1,1} + dp_{i-1,2}$
    
    ​	若设矩阵 $$A = \left[\begin{array}{ll}dp_{i,0}\\dp_{i,1}\\dp_{i,2}\end{array}\right]$$ ，则有转移矩阵 $K = \left[\begin{array}{ll}1 & 1 & 0\\1 &1&1\\0&1&1\end{array}\right]$ ，从而 $A_n = K^{n-1}A_1$ ，显然 $$A_1 = \left[\begin{array}{ll}1\\0\\0\end{array}\right]$$ 。
    
    ​	矩阵快速幂可以解决上面的问题。
    
- **Solution**
    
    ​	但是我们的问题在于障碍怎么办。
    
    ​	障碍的本质是将转移矩阵中的某一列置 0 ，意义是障碍所处的行不参与转移。
    
    ​	由此，不妨分段设置转移矩阵，我们记录一个 0 / 1 数组 $A_{i,0/1/2}$ 表示 $(i,0/1/2)$ 是否存在障碍。
    
    ​	数据范围太大，但是我们只关心某一段的转移矩阵是什么，所以可以离散化障碍的左右端点。
    
    ​	最后在离散化后的端点数组上 dp ，具体地，我们称 $(lsh_i, lsh_{i-1}]$ 为一个段，对每个段求出对应的 $K$ ，然后让 $A \leftarrow K^{lsh_i-lsh_{i-1}}  A$ 即可。

 - **Code**

  
    ```cpp
    #include<bits/stdc++.h>
    using namespace std;
    typedef long long i64;
    const int N = 1e4 + 5, mod = 1e9 + 7;
    struct mat {
    	int a[3][3];
    	void clear() { memset(a, 0, sizeof a); }
    	void init() { clear(); a[0][0] = a[1][1] = a[2][2] = 1; }
    	void zero() { init(); a[0][1] = a[1][0] = a[1][2] = a[2][1] = 1; }
    	mat() { clear(); }
    };
    struct node { i64 l, r; int a; }a[N];
    int n, num;
    i64 m, b[N << 1], c[3][N << 1], sc[3];
    mat operator*(mat a, mat b) {
    	mat c;
    	for (int i = 0; i < 3; i++)
    		for (int j = 0; j < 3; j++)
    			for (int k = 0; k < 3; k++)
    				c.a[i][j] = (c.a[i][j] + 1ll * a.a[i][k] * b.a[k][j]) % mod;
    	return c;
    }
    mat qpow(mat a, i64 b) {
    	mat ret; ret.init();
    	while (b) { if (b & 1)ret = ret * a; a = a * a, b >>= 1; }
    	return ret;
    }
    int main() {
    	cin >> n >> m;
    	for (int i = 1; i <= n; i++) {
    		cin >> a[i].a >> a[i].l >> a[i].r, a[i].a--;
    		b[++num] = a[i].l - 1, b[++num] = a[i].r;
    	}
    	b[++num] = 1, b[++num] = m;
    	sort(b + 1, b + num + 1), num = unique(b + 1, b + num + 1) - b - 1;
    	for (int i = 1; i <= n; ++i) {
    		int L = lower_bound(b + 1, b + num + 1, a[i].l) - b, 
    			R = lower_bound(b + 1, b + num + 1, a[i].r) - b;
    		c[a[i].a][L]++, c[a[i].a][R + 1]--;
    	}
    	mat ans;
    	ans.a[1][0] = 1;
    	for (int i = 2; i <= num; i++) {
    		mat t; t.zero();
    		for (int j = 0; j < 3; j++) {
    			sc[j] += c[j][i];
    			if (sc[j])t.a[j][0] = t.a[j][1] = t.a[j][2] = 0;
    		}
    		t = qpow(t, b[i] - b[i - 1]);
    		ans = t * ans;
    	}
    	cout << ans.a[1][0];
    }
    ```

---

## 作者：mango2011 (赞：0)

这题算是近期做的题目中最复杂的一题了，感觉评紫有理有据啊。

设走到第 $i$ 列的一、二、三行的方案数量分别为 $a_i,b_i,c_i$。如果没有障碍，那么转移就是：

$\textstyle\begin{bmatrix}a_i&b_i&c_i\end{bmatrix}\begin{bmatrix}1&1&0\\ 1&1&1\\ 0&1&1\end{bmatrix}=\begin{bmatrix}a_{i+1}&b_{i+1}&c_{i+1}\end{bmatrix}$。

如果 $(1,2)$ 处没有障碍（否则答案为 $0$），那么 $\begin{bmatrix}a_1&b_1&c_1\end{bmatrix}=\begin{bmatrix}0&1&0\end{bmatrix}$。

对于读入的障碍，我们可以先离散化掉，通过差分进行维护，然后从左到右拆成若干个连续的相同的列（两列相同即它们障碍情况相同）。我们考虑一列障碍对转移矩阵的影响：

对于一列 $i$，若其第 $j$ 
行有障碍，那么其转移矩阵中的第 $j$ 列一定全为 $0$。

举个例子：

一个 $3\times2$ 的网格，其中只有 $(1,2)$ 处有障碍，那么：

$\textstyle\begin{bmatrix}a_1&b_1&c_1\end{bmatrix}=\begin{bmatrix}0&1&0\end{bmatrix}$，$\begin{bmatrix}a_2&b_2&c_2\end{bmatrix}=\begin{bmatrix}0&1&0\end{bmatrix}\begin{bmatrix}0&1&0\\0&1&1\\0&1&1\end{bmatrix}=\begin{bmatrix}0&1&1\end{bmatrix}$。

上面的例子还是比较直观的，可以说明这种转移的正确性。

当连续两列相同的时候，则它们的转移矩阵也相同，可以用矩阵快速幂进行优化。

注意本题离散化的时候不能仅仅是加入 $l_i,r_i$ 还要加入与它们相邻的点以及 $n$，否则就会出现漏掉转移的情形（参见测试点 #3）。

综上，我们就做完了~~麻烦的~~这一题。

[评测记录](https://codeforces.com/problemset/submission/954/271101011)

---

## 作者：DegChuZm (赞：0)

### 鲜花
CF2100* 但是是紫。

其实可以只评个蓝的。

### sol
首先考虑不长脑子的 $O(M)$ 做法。

设 $dp_{i,j}$ 表示第 $i$ 行在 $j$ 位置的方案数。

$c_{i,j}$ 表示第 $i$ 行 $j$ 位置的障碍状态。

然后易得转移方程：
$
\begin{cases}
  dp_{1,i} = dp_{1,i-1}(!c_{1,i-1})\ +\ dp_{2,i-1}(!c_{2,i-1})\\
   dp_{2,i} = dp_{1,i-1}(!c_{1,i-1})\ +\ dp_{2,i-1}(!c_{2,i-1})\ +\ dp_{3,i-1}(!c_{3,i-1})\\
  dp_{3,i} = dp_{2,i-1}(!c_{2,i-1})\ +\ dp_{3,i-1}(!c_{3,i-1})
\end{cases}
$

然后因为 $M$ 巨大，而列又非常小，非常自然地就过渡到矩乘加速。

矩阵，启动！

然后画出不考虑 $c$ 的矩阵：

$
\begin{bmatrix} 1 & 1 & 0\\ 1 & 1 & 1 \\ 0 & 1 & 1 \end{bmatrix}
$

然后搞搞离散化，加速一下就行了。

~~才不会告诉你没想到离散化实现上卡了很久~~

### code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n,m,cnt;
int c[4][100001];
struct dcz{
	int mt[5][5];
};
dcz muilt(dcz x,dcz y){
	dcz z;
	memset(z.mt,0,sizeof z.mt);
	for(int i=1;i<=3;i++){
		for(int k=1;k<=3;k++){
			for(int j=1;j<=3;j++){
				z.mt[i][j]=(z.mt[i][j]+x.mt[i][k]*y.mt[k][j]%mod)%mod;
			}
		}
	}
	return z;
}
struct sbdcz{
	int z,x,y;
}a[100001];
int b[100001];
dcz ksm(dcz a,int b){
	dcz ans;
	memset(ans.mt,0,sizeof ans.mt);
	for(int i=1;i<=3;i++) ans.mt[i][i]=1;
	while(b){
		if(b&1) ans=muilt(ans,a);
		a=muilt(a,a);
		b>>=1;
	}
	return ans;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].z>>a[i].x>>a[i].y;
		b[++cnt]=a[i].x-1,b[++cnt]=a[i].y;
	}
	b[++cnt]=1;
	b[++cnt]=m;
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i].x=lower_bound(b+1,b+cnt+1,a[i].x)-b;
		a[i].y=lower_bound(b+1,b+cnt+1,a[i].y)-b;
		c[a[i].z][a[i].x]++,c[a[i].z][a[i].y+1]--;//答辩离散化
	}
	for(int i=1;i<=cnt;i++){
		c[1][i]+=c[1][i-1];
		c[2][i]+=c[2][i-1];
		c[3][i]+=c[3][i-1];//差分记录障碍物状态
	}
	dcz ans;
	memset(ans.mt,0,sizeof ans);
	ans.mt[1][2]=1;
	for(int i=2;i<=cnt;i++){
		dcz sb;
		memset(sb.mt,0,sizeof sb.mt);
		sb.mt[1][1]=sb.mt[2][2]=sb.mt[3][3]=sb.mt[2][1]=sb.mt[1][2]=sb.mt[2][3]=sb.mt[3][2]=1;
		for(int k=1;k<=3;k++){
			if(c[k][i]) sb.mt[1][k]=sb.mt[2][k]=sb.mt[3][k]=0;
		}
		ans=muilt(ans,ksm(sb,b[i]-b[i-1]));
	}
	cout<<ans.mt[1][2];
	return 0;
}
```

---

