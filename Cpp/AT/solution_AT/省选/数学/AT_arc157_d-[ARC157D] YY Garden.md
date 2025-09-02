# [ARC157D] YY Garden

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc157/tasks/arc157_d

$ H $ 行 $ W $ 列のマス目の各マスに `X`, `Y` のいずれかの文字が書かれています． 上から $ i $ 行目，左から $ j $ 列目のマスを $ (i,\ j) $ で表します． マス目に書かれている文字は $ H $ 個の文字列 $ S_1,\ S_2,\ \dots,\ S_H $ によって与えられ，$ S_i $ の $ j $ 文字目がマス $ (i,\ j) $ に書かれた文字を表します．

隣り合う各行および各列の間に，マス目全体を横断（縦断）するように柵を設置できます． 柵同士は交差しても構いません． 柵の設置後に，「あるマスから始めて上下左右に隣接するマスへの移動を繰り返すことで，柵を越えずに到達可能なマス全体」を**区画**と定義します． （出力例 1 の説明も参考にしてください．）

柵の設置方法は全部で $ 2^{H-1}\ \times\ 2^{W-1} $ 通りありますが，そのうち次の条件を満たすものの個数を $ 998244353 $ で割った余りを求めてください．

**条件:** 各区画には `Y` が書かれたマスがちょうど $ 2 $ 個含まれている．

## 说明/提示

### 制約

- $ 1\ \leq\ H\ \leq\ 2000 $
- $ 1\ \leq\ W\ \leq\ 2000 $
- $ S_i\ (1\ \leq\ i\ \leq\ H) $ は `X`, `Y` からなる長さ $ W $ の文字列である．
 
### Sample Explanation 1

柵の設置方法として，以下の $ 8 $ 通りがあります． ``` X Y Y X|Y Y X Y|Y X|Y|Y | | | | Y X Y Y|X Y Y X|Y Y|X|Y X Y Y X|Y Y X Y|Y X|Y|Y ----- -+--- ---+- -+-+- Y X Y Y|X Y Y X|Y Y|X|Y ``` たとえば，$ 2,\ 3 $ 列目の間に柵を設置した場合，区画は ``` XY YX ``` ``` Y Y ``` であり，それぞれにちょうど $ 2 $ 個の `Y` が含まれているので，条件を満たします． また，$ 1,\ 2 $ 行目の間と $ 1,\ 2 $ 列目の間に柵を設置した場合，区画は ``` X ``` ``` YY ``` ``` Y ``` ``` XY ``` となり，$ 2 $ つ目の区画以外にはちょうど $ 2 $ 個の `Y` が含まれていないので，条件を満たしません．

### Sample Explanation 2

どのように柵を設置しても条件を満たしません．

### Sample Explanation 3

条件を満たす柵の設置方法の総数を $ 998244353 $ で割った余りを出力してください．

## 样例 #1

### 输入

```
2 3
XYY
YXY```

### 输出

```
2```

## 样例 #2

### 输入

```
2 3
XYX
YYY```

### 输出

```
0```

## 样例 #3

### 输入

```
2 58
YXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXY
YXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXYXXY```

### 输出

```
164036797```

# 题解

## 作者：william555 (赞：8)

简要题意：给定一个大小为 $n\times m$ 的 `XY` 矩阵，然后你可以在矩阵的相邻两行/两列之间切一刀，问有多少种切法可以将矩阵分为若干块，且每一块都恰好包含两个 `Y`，对 $998244353$ 取模。$n,m\le 2000$。

如果一共有奇数个 `Y`，一定无解。

否则假设一共有 $S$ 个 `Y`，那么一共就要分为 $\frac S 2$ 块。然后我们枚举横竖各砍几刀，假设横着砍 $p$ 刀，竖着砍 $q$ 刀，接着我们要判断这样砍是否有解，以及如果有解，一共有多少砍法。

记 $S1_i$ 为前 $i$ 行一共有多少个 `Y`，$S2_i$ 为前 $i$ 列一共有多少个 `Y`。如果要有解，横着砍完以后每一段都要有恰好 $2q$ 个 `Y`，竖着每一段都要有恰好 $2p$ 个 `Y`。于是我们看一下 $S1$ 是否包含所有 $2q$ 的倍数，$S2$ 是否包含所有 $2p$ 的倍数。然后我们就可以得到一组解，然后我们用二维前缀和 check 一下是否每个块都是两个 `Y`。接着我们统计一下每个倍数有几个，然后乘起来就是答案。

这样算一组 $(p,q)$ 的时间是 $O(pq)=O(S)$ 的，然后可以发现 $(p,q)$ 的对数不会很多，好像最多的只有几十个，然后就过了。

```c++
#include<bits/stdc++.h>
using namespace std;
const int N=2005,mod=998244353;
inline int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
inline int mul(int a,int b){return 1ll*a*b%mod;}
int n,m,tot,ans;
char s[N][N];
int s1[N],s2[N];
int g[N],f1[N],f2[N];
int p1[N],p2[N];
int sum[N][N];
inline int S(int x1,int y1,int x2,int y2){
	return sum[x2][y2]-sum[x1][y2]-sum[x2][y1]+sum[x1][y1];
}
int cnt1[N],cnt2[N];
void solve(int k1){
	int k2=tot*2/k1,c1=0,c2=0;
	for(int i=1;i<=n;i++)if(s1[i]!=s1[i-1]&&s1[i]%k1==0)p1[++c1]=i;
	for(int i=1;i<=m;i++)if(s2[i]!=s2[i-1]&&s2[i]%k2==0)p2[++c2]=i;
	if(c1<<1!=k2||c2<<1!=k1)return;
	for(int i=1;i<=c1;i++)
		for(int j=1;j<=c2;j++)
			if(S(p1[i-1],p2[j-1],p1[i],p2[j])!=2)return;
	for(int i=1;i<=c1;i++)cnt1[i]=0;
	for(int i=1;i<=c2;i++)cnt2[i]=0;
	for(int i=1;i<=n;i++)if(s1[i]%k1==0)cnt1[s1[i]/k1]++;
	for(int i=1;i<=m;i++)if(s2[i]%k2==0)cnt2[s2[i]/k2]++;
	int res=1;
	for(int i=1;i<c1;i++)res=mul(res,cnt1[i]);
	for(int i=1;i<c2;i++)res=mul(res,cnt2[i]);
	ans=add(ans,res);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%s",s[i]+1);
		for(int j=1;j<=m;j++){
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
			if(s[i][j]=='Y')s1[i]++,s2[j]++,sum[i][j]++;
		}
	}
	for(int i=1;i<=n;i++)s1[i]+=s1[i-1];
	for(int i=1;i<=m;i++)s2[i]+=s2[i-1];
	tot=s1[n];
	if(tot&1)return cout<<0,0;
	for(int i=2;i<=n*m;i+=2)if(tot%i==0)solve(i);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

## 思路

考虑所有横着切的，不难发现分出来横每条的 `Y` 位置总数相等。记总 `Y` 位置数量为 $s$。

如果已经确定怎么横着切了，容易找到竖着切的分隔点。

容易发现空的行和空的列是无用的，先离散化，然后总的行前缀 `Y` 数量和总的列前缀 `Y` 数量均为递增的。枚举一个横条中的 `Y` 位置数量 $d$ 后即可 $O(n+\frac{ms}{d})$ 判断是否可行（横着切竖着切找分隔点）。不难发现 $d$ 是 $s$ 因数且 $\frac s d\leq n$，最大数量在 $100$ 左右。于是总复杂度大约为 $O(100mn)$，常数很小，可以通过。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#pragma GCC optimize(2,3,"Ofast","inline")
using namespace std;
const int mod=998244353;
int a[2005][2005],pre[2005][2005];
int rsum[2005],top,tot;
char c[2005];
pair<int,int> p[4000005];
int lx[4000005],ly[4000005],N,M;
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		for(int j=1;j<=m;j++){
			if(c[j]=='Y'){
				p[++top]=make_pair(i,j);
				lx[top]=i,ly[top]=j;
			}
		}
	}
	sort(lx+1,lx+top+1); N=unique(lx+1,lx+top+1)-lx-1;
	sort(ly+1,ly+top+1); M=unique(ly+1,ly+top+1)-ly-1;
	for(int i=1;i<=top;i++){
		p[i].first=lower_bound(lx+1,lx+N+1,p[i].first)-lx;
		p[i].second=lower_bound(ly+1,ly+M+1,p[i].second)-ly;
		a[p[i].first][p[i].second]=1,rsum[p[i].first]++,tot++;
	}
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			pre[i][j]=pre[i-1][j]+a[i][j];
		}
	}
	int ans=0;
	for(int k=1;k<=tot;k++){
		if((tot%k==0)&&(k%2==0)){
			int f1[tot/k+1],f2[k/2+1],p=0,p2=0,now=0; f1[0]=f2[0]=0;
			for(int i=1;i<=N;i++){
				now+=rsum[i];
				if(now==k) f1[++p]=i,now=0;
			}
			int csum[p+1]; for(int j=1;j<=p;j++) csum[j]=0;
			if(p==tot/k){
				for(int j=1;j<=M;j++){
					int ok=1;
					for(int i=1;i<=p;i++){
						csum[i]+=pre[f1[i]][j]-pre[f1[i-1]][j];
						if(csum[i]!=2) ok=0;
					}
					if(ok){
						f2[++p2]=j;
						for(int i=1;i<=p;i++) csum[i]=0;
					}
				}
				if(p2==k/2){
					int tmul=1;
					for(int i=1;i<p;i++){
						(tmul*=(lx[f1[i]+1]-lx[f1[i]]))%=mod;
					}
					for(int i=1;i<p2;i++){
						(tmul*=(ly[f2[i]+1]-ly[f2[i]]))%=mod;
					}
					(ans+=tmul)%=mod;
				}
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Ratio_Y (赞：2)

## 思路
感觉有点偏思维，不过推出几个重要性质后还是蛮简单的。

首先记 Y 的总数 $tot$，若为奇数一定无解。

已知两个 Y 分一组，那么一共有 $\frac{tot}{2}$ 组。我们将该矩阵分成若干个矩形，比较显然的是，知道了行被分成了几组，就能知道列被分成了几组。

我们可以枚举它，不过我枚举的是**行被分成若干组后，每一组含 Y 的个数 $hk$**，而我们知道两个 Y 一组，所以就能知道**列被分成了 $\frac{hk}{2}$ 部分**，根据矩形面积公式，我们就能得到**行应当被分成 $\frac{tot\times 2}{hk}$ 部分**；这里具体枚举那个都是无关紧要的，因为已知其中一个的值就能推导出剩下的值。

注意上面描述的时候用了**应当**，这是因为以上情况只是我们假设出来的理想情况，若与之不符则应当舍弃；此外，还有一个判断无解的标准，就是我们在按以上情况分出各部分后，需要判断每部分是否正好含两个 Y，具体实现我们可以借助二维前缀和维护。

之后方案若仍合法，则开始计数，此时我们划分部分就较为宽松了，在上面判断的时候，我们划分的标准是**该行 / 列有 Y 出现且能将行 / 列分成每部分含对应数量的一组**，而计数时只要不影响划分的状态都可以计入，最终利用乘法原理计算出该方案的所有方案数计入答案即可。

由于基础方案数比较少，所以原本 $\mathcal{O(S)}$ 的时间复杂度跑起来还是很快的。

## 实现

```cpp
#include<bits/stdc++.h>

const int Ratio=0;
const int N=2005;
const int mod=998244353;
int n,m,tot;
int sum[N][N],hsum[N],lsum[N],hang[N],lie[N];
int hzc[N],lzc[N],cnth[N],cntl[N];
int ans;
namespace Wisadel
{
    void Wsol(int hk)
    {
        int lk=tot*2/hk,ch=0,cl=0,res=1;
        for(int i=1;i<=n;i++) if(hang[i]&&hsum[i]%hk==0) hzc[++ch]=i;
        for(int i=1;i<=m;i++) if(lie[i]&&lsum[i]%lk==0) lzc[++cl]=i;
        if(2*ch!=lk||2*cl!=hk) return;
        for(int i=1;i<=ch;i++) for(int j=1;j<=cl;j++)
        {
            int ck=sum[hzc[i]][lzc[j]]-sum[hzc[i-1]][lzc[j]]-sum[hzc[i]][lzc[j-1]]+sum[hzc[i-1]][lzc[j-1]];
            if(ck!=2) return;
        }
        std::fill(cnth+1,cnth+1+ch,0),std::fill(cntl,cntl+1+cl,0);
        for(int i=1;i<=n;i++) if(hsum[i]%hk==0) cnth[hsum[i]/hk]++;
        for(int i=1;i<=m;i++) if(lsum[i]%lk==0) cntl[lsum[i]/lk]++;
        for(int i=1;i<ch;i++) res=1ll*res*cnth[i]%mod;
        for(int i=1;i<cl;i++) res=1ll*res*cntl[i]%mod;
        ans=(ans+res)%mod;
    }
    short main()
    {
        scanf("%d%d",&n,&m);getchar();
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
            {
                char ch=getchar();
                sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1];
                if(ch=='Y') hang[i]++,lie[j]++,hsum[i]++,lsum[j]++,sum[i][j]++;
            }
            getchar();
            hsum[i]+=hsum[i-1];
        }
        for(int i=1;i<=m;i++) lsum[i]+=lsum[i-1];
        tot=hsum[n];
        if(tot&1){printf("0\n");return Ratio;}
        for(int i=2;i<=n*m;i+=2)
        {
            if(tot%i==0) Wsol(i);
            if(i>tot) break;
        }
	    printf("%d\n",ans%mod);
        return Ratio;
    }
}
int main(){return Wisadel::main();}
```


---

完结撒花~

[$\mathcal{Welcome\;to\;my\;blogs}$](https://www.cnblogs.com/Ratio-Yinyue1007)

---

## 作者：Kketchup (赞：1)

### [[ARC157D] YY Garden](https://atcoder.jp/contests/arc157/tasks/arc157_d)

- 组合数学

**Sol:** 首先判断 $X$ 的个数（设为 $cnt$），是奇数直接无解。我们假设横着设置了 $h-1$ 道栅栏，竖着设置了 $w-1$ 道栅栏，那么整个矩阵被划分成了 $h\times w$ 块，且 $2\times h\times w=cnt$，所以 $h$ 与 $w$ 一定是 $cnt$ 的因数。我们考虑直接枚举 $h$，那么可以计算出 $w=\large\frac{cnt}{2h}$。

观察这时候合法的矩阵划分形态，发现相邻两个横着的栅栏之间 $X$ 的个数恰巧是 $2w$ 个，相邻两个竖着的栅栏之间 $X$ 有 $2h$ 个。我们发现，在 $h$ 固定的情况下，所有横着栅栏的范围是不交的，因为每个栅栏的范围都是块内有了 $2w$ 个 $X$ 以后的空行，这样不会影响答案。所以我们可以直接模拟划分过程，记录栅栏位置，并把栅栏的划分区间相乘算出一种 $h$ 的答案，再通过预处理的二维前缀和检查每个块内 $X$ 是否都是 $2$ 个判断是否合法。

时间复杂度 $O(HWd(HW))$，$d(x)$ 表示 $x$ 的约数个数，查表得到 $10^7$ 以内 $d(x)$ 最大值是 $448$，可以通过本题。关于约数个数，[这篇文章](https://wenku.baidu.com/view/9e336795bb4cf7ec4afed057.html)证明了约数个数上界是 $\sqrt{3n}$ 的，感兴趣可以自行阅读。

**Trick:** 因为题目限制看起来非常强，所以直接从限制入手。观察到只要确定一个维度的划分，就能计算出另一个维度的划分，而且贡献区间不交，从而得到解法。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl '\n'
#define F(i,x,y) for(int i=(x);i<=(y);++i)
#define Fo(i,x,y) for(int i=(x);i>=(y);--i)
const int N=2005,mod=998244353;
int n,m,cnt;
int a[N][N],s[N][N],sx[N],sy[N];
ll ans=0;
char ch[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    for(int i=1;i<=n;++i){
        cin>>ch;
        for(int j=1;j<=m;++j){
            a[i][j]=(ch[j-1]=='Y');
            (s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j])%=mod;
            sx[i]+=a[i][j];
            sy[j]+=a[i][j];
            cnt+=a[i][j];
        }
    }
    auto ask=[=](int A,int B,int C,int D){return s[A][B]-s[C-1][B]-s[A][D-1]+s[C-1][D-1];};
    if(cnt==0||cnt&1) return cout<<0<<endl,0;
    cnt>>=1;
    for(int p=1,q;p<=cnt;++p){
        if(cnt%p) continue;
        q=cnt/p;
        if(q>m) continue;
        vector<int> r,c;
        r.emplace_back(1);
        c.emplace_back(1);
        ll res1=1,res2=1;
        for(int i=1,j=1;i<=n;i=j){
            int tmp=0,tot=1;
            while(tmp<2*q&&j<=n) tmp+=sx[j],j++;
            while(sx[j]==0&&j<=n) tot++,j++;
            r.emplace_back(j);
            if(j<=n) (res1*=tot)%=mod;
        }
        for(int i=1,j=1;i<=m;i=j){
            int tmp=0,tot=1;
            while(tmp<2*p&&j<=m) tmp+=sy[j],j++;
            while(sy[j]==0&&j<=m) tot++,j++;
            c.emplace_back(j);
            if(j<=m) (res2*=tot)%=mod;
        }
        for(int i=0;i<p;++i) for(int j=0;j<q;++j) if(ask(r[i+1]-1,c[j+1]-1,r[i],c[j])!=2) goto con;
        (ans+=res1*res2%mod)%=mod;
        con:;
    }    
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：EXODUS (赞：1)

# Part 1：前言
比较简单的一道题，但还是有一定思维难度。

# Part 2：正文

注意到每个块要求恰好有两个 $\texttt{Y}$，不妨考虑从这一点入手。

首先记录 $\texttt{Y}$ 的个数为 $x$，那么要求 $x$ 为二的倍数。又因为设置 $h-1$ 个横向栅栏，$w-1$ 个纵向栅栏后，总的块数为 $hw$，所以 $h$ 和 $w$ 必定为 $x$ 的因数。

首先判掉 $x$ 为奇数的情况。我们枚举 $h$，则 $w$ 固定且为 $\dfrac{x}{2h}$。考虑对于一个这种状态我们如何计算方案。再次观察，由于 $h$ 和 $w$ 固定，则若我们只观察横向划分，每一块里恰好要有 $2w$ 个 $\texttt{Y}$。纵向划分同理。下面只讨论横向的情况。注意到此时一个栅栏的位置会被固定在一个全部由 $\texttt{X}$ 构成的行，否则均会导致这一块中的 $1$ 的个数不为 $2w$。注意到每一个栅栏被固定的范围不交，因此如果确定了 $h$ 和 $w$ 以后，方案数的计算可以直接通过乘法原理将每个栅栏可能存在的位置个数相乘得到方案数。然后模拟任意一种划分，二维前缀和判断是否合法。最后将所有合法的 $h$ 取值所导出的方案数相加即可。

时间复杂度 $O(HWd(HW))$，其中 $d$ 为约数个数函数。常数不大，因此可以通过。

# Part 3：代码

```cpp
#include<bits/stdc++.h>
#include<atcoder/modint>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef atcoder::modint998244353 mint;

#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define File(filename) freopen(filename ".in","r",stdin),freopen(filename ".out","w",stdout)

#ifdef EXODUS
	#define Debug(...) fprintf(stderr,__VA_ARGS__)
#else
	#define Debug(...) 0
#endif

//=========================================================================================================
// Something about IO

template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}

//=========================================================================================================
// Define the global variables here.

bool membg=0;


constexpr int N=2e3+7;

int n,m;
char s[N][N];
int yr[N],yl[N],sum[N][N],all;

bool memed=0;

//=========================================================================================================
// Code here.

void solve(){
	read(n,m);
	rep(i,1,n)scanf("%s",s[i]+1);
	rep(i,1,n)rep(j,1,m)
		if(s[i][j]=='Y')sum[i][j]++,yr[i]++,yl[j]++,all++;
	rep(i,1,n)rep(j,1,m)sum[i][j]+=sum[i][j-1];
	rep(j,1,m)rep(i,1,n)sum[i][j]+=sum[i-1][j];
	auto ask=[&](int u,int d,int l,int r){return sum[d][r]-sum[u-1][r]-sum[d][l-1]+sum[u-1][l-1];};
	if(!all||(all&1))return printf("0\n"),void();
	all>>=1;mint ans=0;
	for(int a=1,b;a<=n;a++){
		if(all%a)continue;b=all/a;
		if(b>m)continue;
		// printf("===%d %d===\n",a,b);
		basic_string<int>row{1},line{1};
		mint cR=1,cL=1;
		for(int i=1,j=1;i<=n;i=j){
			int cur=0;
			while(j<=n&&cur<2*b)cur+=yr[j],j++;
			int free=1;
			while(j<=n&&yr[j]==0)free++,j++;
			row+=j;if(j<=n)cR*=free;
		}
		for(int i=1,j=1;i<=m;i=j){
			int cur=0;
			while(j<=m&&cur<2*a)cur+=yl[j],j++;
			int free=1;
			while(j<=m&&yl[j]==0)free++,j++;
			line+=j;if(j<=m)cL*=free;
		}
		// for(auto x:row)printf("%d ",x);printf("\n");
		// for(auto x:line)printf("%d ",x);printf("\n");
		for(int i=0;i<a;i++)
			for(int j=0;j<b;j++)
				if(ask(row[i],row[i+1]-1,line[j],line[j+1]-1)!=2)
					goto there;
		ans+=cR*cL;
		there:;
	}
	printf("%d\n",ans.val());
	
	return;
}


//=========================================================================================================

int main(){
	Debug("%.3lfMB\n",fabs(&memed-&membg)/1024.0/1024.0);
	int timbg=clock();
	int T=1;
	while(T--)solve();
	int timed=clock();
	Debug("%.3lfs\n",1.0*(timed-timbg)/CLOCKS_PER_SEC);
	fflush(stdout);
	return 0;
}
```

---

## 作者：Dovish (赞：0)

## 分析

首先，我们可以观察到，我们知道 ```Y``` 的总出现次数，那么显然就可以枚举至多 $O(d(nm))$ 种将矩阵分为 $a\times b$ 个小矩阵的方法。

继续观察，当纵方向上切的总刀数一定时，我们发现每个 ```Y``` 所属的纵方向上的块都是一定的。即：不同的对纵方向的切割方案可以简单地用乘法原理将几个间隔的长度乘起来。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/hq3g7tjt.png)

我们继续考虑横方向上可以类似地做。

枚举每一行，看切下去是否能使得每一个竖带内都可以恰好分割出**相同的** $2x$ 个 ```Y```。同样的乘法原理把间隔乘起来。

时间复杂度是 $O(d(nm)\sum_{k|nm,k\le n}km)$，但是 $O(d(nm)nm)$ 也能过就是了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,a,b) for(register int i=(a);i>=(b);--i)
#define edge(i,u) for(int i=head[u];i;i=e[i].next)
#define lc(u) (ch[u][0])
#define rc(u) (ch[u][1])
#define pii pair<int,int>
#define pdd pair<double,double>
#define mp make_pair
#define pb push_back
#define fst first
#define sed second
using namespace std;
const int N=2e3+10,M=4e6+10,inf=1e9,mod=998244353;
bool MS;int used;
int qpow(int a,int b){int res=1;while(b){if(b&1)res=1ll*res*a%mod;a=1ll*a*a%mod;b>>=1;}return res;}
int inv(int a){return qpow(a,mod-2);}
void Mul(int&a,int b){a=1ll*a*b%mod;}
void Add(int&a,int b){a+=b;if(a>=mod)a-=mod;}
void Dec(int&a,int b){a-=b;if(a<0)a+=mod;}
int mul(int a,int b){return 1ll*a*b%mod;}
int add(int a,int b){return a+b>=mod?a+b-mod:a+b;}
int dec(int a,int b){return a-b<0?a-b+mod:a-b;}
char s[N][N];
int sum[N][N];
int sumx[N],cntx[M];
int cnty[M];
int last[M];
int cnt; 
int n,m;
int check_x(int k)//分成k份,每份lim个 
{
	if(k>n)return 0;
	int lim=cnt/k;
	int res=1;
	rep(i,1,k)
	Mul(res,cntx[i*lim]);
	if(!res)return 0;
	rep(i,1,k)
	{		
		int l=last[(i-1)*lim]+1,r=last[i*lim];
		rep(j,1,m)
		{
			sum[i][j]=sum[i][j-1];
			rep(k,l,r)
			sum[i][j]+=(s[k][j]=='Y');
		}
	}
	rep(j,1,m)
	{
		int base=sum[1][j];
		rep(i,1,k)
		if(sum[i][j]!=base)goto end;
		cnty[base]++;
		end:;
	}
	cnty[lim]=1;
	rep(i,1,lim/2)
	Mul(res,cnty[i*2]);
	rep(j,1,m)
	cnty[sum[1][j]]=0;
	return res;
}
bool MT;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	rep(i,1,n)
	rep(j,1,m)
	{
		cin>>s[i][j];
		cnt+=(s[i][j]=='Y');
		sumx[i]+=(s[i][j]=='Y');
	}
	if(cnt&1)return cout<<0,0;
	rep(i,1,n)
	{
		sumx[i]+=sumx[i-1];
		cntx[sumx[i]]++;
		last[sumx[i]]=i; 
	}
	cntx[cnt]=1;
	int ans=0;
	rep(i,1,cnt/2)
	if(cnt/2%i==0)
	Add(ans,check_x(i));
	cout<<ans<<'\n';
	cerr<<"Memory:"<<(&MS-&MT)/1048576.0<<"MB Time:"<<clock()/1000.0<<"s\n";
}
```

---

## 作者：cwfxlh (赞：0)

# [AT_arc157_d](https://www.luogu.com.cn/problem/AT_arc157_d)      

横着的栅栏与竖着的栅栏将其分成若干个格子，其中每个横条的 Y 数量必定相同，于是枚举横条的 Y 数量，总共有 $O(h)$ 种。接下来，考虑竖着放栅栏，因为每个格子的 Y 数量固定为 $2$，所以找到竖着切开后，每个横条的前缀 Y 个数相等且为偶数的位置，然后将空列合在一起算，最后乘起来累加即可。        

思路是简单暴力的，分析一下复杂度，复杂度瓶颈在于，找到从某个地方竖着切开后，每个横条的前缀 Y 个数，这部分是 $O(w\times B)$ 的，$B$ 是横条数量，因为有整除的限制，以及 $B\le h$，所以合法的 $B$ 的个数是很少的，足以通过此题，一点不卡常。代码有点难写。    

代码：    


```cpp
#include<bits/stdc++.h>
#define int long long
#define MOD 998244353
using namespace std;
int h,w,a[2003][2003],preh[2003],k1,k2,k3,k4,k5,k6,k7,k8,k9,ans;
int stk[5003],tot,v[5003],mk[5003];
int pre[2003][2003],num[5003];
string s;
int calc(){
	if(mk[w]==-1)return 0;
	if(mk[w]%2!=0)return 0;
	int ret=1;
	if(mk[w]/2>w)return 0;
	for(int i=1;i<=mk[w];i++)num[i]=0;
	for(int i=1;i<=w;i++)if(mk[i]!=-1)num[mk[i]]++;
	for(int i=2;i<mk[w];i+=2)ret=ret*num[i]%MOD;
	return ret;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>h>>w;
	for(int i=1;i<=h;i++){
		cin>>s;
		for(int j=1;j<=w;j++)a[i][j]=(s[j-1]=='Y');
		preh[i]=preh[i-1];
		for(int j=1;j<=w;j++)preh[i]+=a[i][j];
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<=w;j++)pre[i][j]=pre[i-1][j]+a[i][j];
	}
	for(int i=1;i<=h;i++){
		if(preh[i]==0)continue;
		if(preh[i]%2!=0)continue;
		if(preh[h]%preh[i]!=0)continue;
		if((preh[h]/preh[i])>h)continue;
		if(preh[i]==preh[i-1])continue;
		k1=1;
		tot=0;
		for(int j=preh[i],u=i;j<preh[h];j+=preh[i]){
			while(u<h&&preh[u]<j)u++;
			if(u>h||preh[u]!=j){
				k1=0;
				break;
			}
			k2=0;
			stk[++tot]=u;
			while(preh[u]==j){
				u++;
				k2++;
			}
			k1=k1*k2%MOD;
		}
		if(k1==0)continue;
		stk[0]=0;
		stk[tot+1]=h;
		for(int j=1;j<=tot+1;j++)v[j]=0;
		for(int j=1;j<=w;j++){
			for(int u=1;u<=tot+1;u++){
				v[u]+=pre[stk[u]][j]-pre[stk[u-1]][j];
			}
			k3=1;
			for(int u=2;u<=tot+1;u++)if(v[u]!=v[u-1])k3=0;
			if(v[1]==0||v[1]%2!=0)k3=0;
			if(k3==0)mk[j]=-1;
			else mk[j]=v[1];
		}
		if(k1!=0)ans=(ans+k1*calc())%MOD;
	}
	ans%=MOD;
	ans+=MOD;
	ans%=MOD;
	cout<<ans;
	return 0;
}
```

---

## 作者：TernaryTree (赞：0)

萌萌 2435，顿悟一下就会了。

记矩阵中 $\tt Y$ 个数为 $sum$。

首先去枚举一下横着切了几次，这一定是 $\dfrac{sum}2$ 的因数；然后竖着切了几次我们也知道了。

然后去嗯跑一下横着切的行，先处理出每一行的总和，然后就可以先跑出一个每条线都尽可能往上的切分；注意到如果一刀底下是空行，那么这一刀往下跑也行；而且每一刀互不影响，所以一行的答案应该是所有这样最上边的刀，往下跑能跑到多少个，的乘积。

我们又有：这样随便跑，对列的纵切是没有任何影响的，因为只是空行反复被上下两组踢皮球。再来考虑列。列的纵切从左到右，找有多少个纵的位置，对于每一个行组中的每一行算出这一行到这个位置的前缀和，要求所有行组的每一行的这个和都是一样的，即 $2,4,6,8,\dots$。方案数同样是对于 $2,4,6,8,\dots$ 中每个数满足条件的纵切个数的乘积。

然后一个枚举的答案就是上面两个乘积的乘积。对所有枚举求和即可。

分析一下复杂度：假设某一次枚举切了 $h-1$ 次，因为我们每一次有 $h$ 行被跑 $m$ 次来解决，所以这样跑一次的复杂度是 $hm$。

有两个条件限制 $h$：

- $h\le n$
- $h \mid \dfrac{sum}2$

显然如果要让 $\sum h$ 最大，$n$ 要最大，取 $2000$；然后我们就可以写个筛子，跑出 $\dfrac{sum}2\in [0,2\times 10^6]$ 范围内每个数 $\le 2000$ 因数的和，可以得到其最大值为 $78241$。而乘上 $m=2000$ 也就 $1.5\times 10^8$，~~而且应该构造不出能完全卡满这个上界的数据~~，况且这个题给了 $3s$，那就随便跑了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn = 2e3 + 10;
const int mod = 998244353;

int n, m, sum, ans = 0;
int a[maxn][maxn];
int b[maxn][maxn], c[maxn], d[maxn], cnt;
int buc[maxn * maxn];
char ch;

int solve(int h) {
	if (h > n) return 0;
	for (int j = 1; j <= m; j++) d[j] = 0;
	cnt = 0;
	int w = sum / h;
	int s = 1, lst = 0, mul = 1;
	for (int i = 1; i <= n; i++) {
		if (c[i] != c[i - 1]) lst = i;
		if ((i == n || c[i] != c[i + 1]) && c[i] == c[s - 1] + w) {
			int t = i;
			++cnt;
			if (cnt != h) mul = mul * (i - lst + 1) % mod;
			if (cnt == 1) {
				for (int j = 1; j <= m; j++) d[j] = d[j - 1] + b[i][j] - b[s - 1][j];
			} else {
				int cur = 0;
				for (int j = 1; j <= m; j++) {
					cur += b[i][j] - b[s - 1][j];
					if (cur != d[j]) d[j] = 0;
				}
			}
			s = t + 1;
		}
	}
	if (cnt != h) return 0;
	int tot = 0, pos = 0;
	for (int j = 1; j <= m; j++) if (d[j]) buc[d[j]]++;
	for (int i = 2; i < w; i += 2) mul = mul * buc[i] % mod;
	for (int j = 1; j <= m; j++) if (d[j]) buc[d[j]]--;
	return mul;
}

signed main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		c[i] = c[i - 1];
		for (int j = 1; j <= m; j++) {
			cin >> ch;
			a[i][j] = (ch == 'Y');
			sum += a[i][j];
			c[i] += a[i][j];
			b[i][j] = b[i - 1][j] + a[i][j];
		}
	} 
	if (sum & 1) {
		cout << 0 << endl;
		return 0;
	}
	for (int i = 1; i * i <= sum / 2; i++) {
		if (sum / 2 % i == 0) {
			(ans += solve(i)) %= mod;
			if (i * i != sum / 2) (ans += solve(sum / 2 / i)) %= mod;
		}
	}
	cout << ans << endl;
	return 0;
}

```

---

## 作者：_lbw_ (赞：0)

我们发现题目的限制看起来非常强，先考虑一些必要条件。

首先设 `Y` 的个数为 $k_1$，容易得到 $2AB=k_1$，$A$ 表示行割了几刀，$B$ 同理。

第二个必要条件是只考虑行的刀，分成的每一块 `Y` 的个数都是 $2B$，列同理。

然后我们会对每一刀确定一个范围，但我们还有一个条件是每一块恰好 $2$ 个 `Y`。

不过我们又发现无论刀在哪里割，每一小块 `Y` 的个数都是固定的。

判断，然后乘法原理计数即可。

---

