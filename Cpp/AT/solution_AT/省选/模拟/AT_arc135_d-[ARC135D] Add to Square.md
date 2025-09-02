# [ARC135D] Add to Square

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc135/tasks/arc135_d

$ H\times\ W $ のマス目があり、各マスに整数がひとつずつ書き込まれています。 $ 1\leq\ i\leq\ H $, $ 1\leq\ j\leq\ W $ に対して、$ i $ 行目・$ j $ 列目のマスに書き込まれている整数を $ A_{i,j} $ で表します。

あなたは次の操作を、何度でも行うことができます（一度も行わなくてもよいです）。

- $ 1\leq\ i\leq\ H\ -\ 1 $ かつ $ 1\leq\ j\leq\ W\ -\ 1 $ を満たす整数 $ i,\ j $ を選ぶ。
- 整数 $ x $ をひとつ選ぶ。
- $ A_{i,j} $, $ A_{i,j+1} $, $ A_{i+1,j} $, $ A_{i+1,j+1} $ に $ x $ を加える。

操作後の $ \sum_{i=1}^H\ \sum_{j=1}^W\ |A_{i,j}| $ が最小となるように操作を行うとき、操作後の $ \sum_{i=1}^H\ \sum_{j=1}^W\ |A_{i,j}| $ の値および、そのときのマス目の状態を出力してください。

## 说明/提示

### 制約

- $ 2\leq\ H,\ W\ \leq\ 500 $
- $ |A_{i,j}|\leq\ 10^9 $

### Sample Explanation 1

例えば次のように操作を行うと、出力例のマス目の状態になります。 - $ (i,\ j,\ x)\ =\ (1,\ 1,\ -1) $ として操作を行う。 - $ (i,\ j,\ x)\ =\ (1,\ 2,\ -4) $ として操作を行う。 このとき、$ \sum_{i=1}^H\ \sum_{j=1}^W\ |A_{i,j}|\ =\ 0\ +\ 3\ +\ 1\ +\ 3\ +\ 0\ +\ 2\ =\ 9 $ です。

### Sample Explanation 2

$ |A_{i,j}|\ >\ 10^9 $ となるような操作も認められています。

## 样例 #1

### 输入

```
2 3
1 2 3
4 5 6```

### 输出

```
9
0 -3 -1
3 0 2```

## 样例 #2

### 输入

```
2 2
1000000000 -1000000000
-1000000000 1000000000```

### 输出

```
4000000000
2000000000 0
0 2000000000```

## 样例 #3

### 输入

```
3 4
0 2 0 -2
-3 -1 2 0
-3 -3 2 2```

### 输出

```
0
0 0 0 0
0 0 0 0
0 0 0 0```

# 题解

## 作者：Math_rad_round (赞：9)

首先我们将棋盘黑白染色，将黑格上的数取反，把每次操作转化为左上右下 $+x$ 右上左下 $-x$。（以下部分的矩阵都是这样取反的）

这样我们可以发现，每次操作，每行每列的和都不会改变。（总是一个 $+x$ 一个 $-x$。）

同时，我们可以得到一个更强的结论：两个矩阵可以互相转化，当且仅当对应行相等，对应列也相同。

必要性已经说了，而充分性可以考虑先使左上 $(N-1)\times(M-1)$ 的矩阵相同，又因为对应行列相等，所以剩下的格子也一定相同。


------------

我们设转化后的矩阵为 $G$，原矩阵为 $F $，初始时 $G$ 为全 $0$。

再设 $x[i]$ 为 $F$ 的【第 $i$ 行和】减 $G$ 的【第 $i$ 行和】，同理设出 $y[i]$。

我们只需要调整使 $x[i],y[i]$ 均为 $0$ 即可。

我们现在证明 $G$ 的元素绝对值和最小为 $cnt=\max(\sum_{i=1}^n |x[i]|,\sum_{i=1}^m|y[i]|)$。

因为每次把一个格子加减 $a$，上式最多变化 $a$，而目标状态上式为 $0$ 所以答案至少为 $cnt$。

另一方面，考虑如此构造：

按下列优先顺序，重复操作：

```cpp
     if(存在 x[i]*y[j]>0){G[i][j]+=sign(x);}
else if(存在 x[i]*x[j]<0){G[x[i]][1]++;G[x[j]][1]--;}//设x[i]>0 
else if(存在 y[i]*y[j]<0){G[1][y[i]]++;G[1][y[j]]--;}//设y[i]>0 
```


因为 $\sum_{i=1}^n x[i]=\sum_{i=1}^my[i]$，第一步不能执行时，一定 $x$ 或 $y$ 均为 $0$，所以每次操作将数字变动 $a$ 时，$cnt$ 会减少 $a$。因此答案不会多于 $cnt$。


------------

具体实现时按照证明时的构造类似的写就行了，为了减省时间，可以让每一次操作都使一个 $x$ 或 $y$ 变为 $0$。

如果每一次暴力判断是否存在上面三条，时间复杂度是 $O((n+m)^2)$，不过严重跑不满而且常数小，可以通过。

细节见代码吧。

```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<map>
#include<algorithm>
#include<queue>
#include<set>
#define getmi int mi=(l+r)/2;
#define addm(a,b) {a+=b;if(a>=mu)a-=mu;}
#define decm(a,b) {a-=b;if(a<0)a+=mu;}
#define mtim(a,b) a=a*1LL*(b)%mu
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
inline long long read(){
    long long x=0,f=1;char a1=getchar();while(a1<'0'||a1>'9'){if(a1=='-')f=-f;a1=getchar();}
    while(a1>='0'&&a1<='9'){x=x*10+(a1^48);a1=getchar();}return x*f;}
inline void write(ll a,int ok=1){
    if(a<0){putchar('-');a=-a;}if(a==0)putchar('0');else
    {unsigned long long z=0,k=0;while(a){z=(z*10)+a%10;a/=10;k++;}while(k--){putchar('0'+(z%10));z/=10;}}if(ok==1)putchar('\n');else if(ok==2)putchar(' ');}
const int N=1000000;
ll x[N],y[N];
ll b[5100][5100];
void add(int i,int j,ll k){
	b[i][j]+=k;x[i]-=k;y[j]-=k;
}
int main(){
	ll n=read(),m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int e=read();
			if((i+j)&1)e=-e;
			x[i]+=e;y[j]+=e;
		}
	}
	ll ans=0;
	while(1){
		ll xmi=0,xma=0,ymi=0,yma=0;
		for(int i=1;i<=n;i++){
			if(x[i]<0)xmi=i;
			if(x[i]>0)xma=i;
		}
		for(int i=1;i<=m;i++){
			if(y[i]<0)ymi=i;
			if(y[i]>0)yma=i;
		}
		if(xma&&yma){
			add(xma,yma,min(x[xma],y[yma]));
		}else if(xmi&&ymi){
			add(xmi,ymi,max(x[xmi],y[ymi]));	
		}else if(xmi&&xma){
			ll s=min(x[xma],-x[xmi]);
			add(xmi,1,-s);add(xma,1,s);
		}else if(ymi&&yma){
			ll s=min(y[yma],-y[ymi]);
			add(1,ymi,-s);add(1,yma,s);
		}else break;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if((i+j)&1)b[i][j]=-b[i][j];
		ans+=abs(b[i][j]);
	}
	write(ans);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			write(b[i][j],2-(j==m));
		}
	}
	return 0;
}

```


---

## 作者：未来姚班zyl (赞：5)

## 题目大意

给定一个 $n\times m$ 的矩阵，你可以不断选择其中一个 $2\times 2$ 的子矩阵，为当中的每个数加上 $x$，最小化所有元素的绝对值之和。

## 题目分析

拿到这种对 $2\times 2$ 的矩阵做修改的题，首先要寻找矩阵中不变的量。比如这一题中，对于每一行，奇数列上的和与偶数列上的和的差不变，对于每一列，奇数行上的和与偶数行上的和的差不变，原因是每次操作是对相邻的数加同一个数。这题有一个很妙的方法是对这个矩阵黑白染色，并对白格上的数取反，则每行的和与每列的和不变，操作变为左上右下加，左下右上减同一个数，而对绝对值的影响与转化前一样。

然后，我们要找到等价的矩阵。

显然，左上的 $(n-1)\times (m-1)$ 的矩阵是可以全部置为 $0$ 的，这时候剩下的位置的值也就确定了。则如果两个矩阵的对应行、对应列对应的和都相等，则两个矩阵都可以通过这种方式转换成相同的矩阵，则两个矩阵可以互相转化。

所以，我们可以转化为往一个矩阵里填数，使得满足行/列和的前提下最小化绝对值之和。显然，答案的下界是行之和的绝对值之和与列之和的绝对值之和中的最大值，我们直接考虑构造出来。

注意如下分析中，始终有所有行之和的和等于所有列之和的和。

思考在一个位置填 $k$，相当于将对应的行和列还需要填的值同时减去 $k$。

考虑按照如下策略：

 1. 找到同号的一行和一列，通过修改它们公共的位置，将绝对值小的削成 $0$，直到所有的行或所有的列都不需填数。
 
这时候要么只有列还需填数，要么只有行还需填数，我们拿行举例。此时还需填的行对应的正数和负数的绝对值之和相等。
 
 2. 找到异号的行，通过修改两同列个数（值相反），将绝对值小的削成 $0$，直到所有行都不需填数。
 
显然，在过程中，我们的修改量正好是答案的下界，故构造成功。
 
由于每次都削掉一行或一列，所以复杂度应为 $O(n+m+nm)$，瓶颈在于输入输出与求行列之和。
 
```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R L|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define OK Ll<=l&&r<=Rr
#define Root 1,1,n
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define repn(x) rep(x,1,n)
#define repm(x) rep(x,1,m)
#define pb push_back
#define e(x) for (int i = h[x], y = to[i]; i; i = nxt[i], y = to[i])
#define E(x) for (auto y : p[x])
#define Pi pair<int, int>
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =5e2+5,M=1e6+5,inf=(1LL<<31)-1,mod=998244353;
const ll llf=1e18;
using namespace std;
int n=read(),m=read();
ll a[N][N],sx[N],sy[N];
int sxz[N],sxf[N],syz[N],syf[N],txz,txf,tyz,tyf;
signed main(){
	repn(i)repm(j)a[i][j]=read();
	repn(i)repm(j)if(i+j&1)a[i][j]*=-1;
	repn(i)repm(j)sx[i]+=a[i][j],sy[j]+=a[i][j];
	memset(a,0,sizeof(a));
	repn(i)if(sx[i]>0)sxz[++txz]=i;
	else if(sx[i]<0)sxf[++txf]=i;
	repm(i)if(sy[i]>0)syz[++tyz]=i;
	else if(sy[i]<0)syf[++tyf]=i;
	while(txz&&tyz){
		int i=sxz[txz--],j=syz[tyz--];
		ll k=min(sx[i],sy[j]);
		a[i][j]+=k,sx[i]-=k,sy[j]-=k;
		if(sx[i])sxz[++txz]=i;
		if(sy[j])syz[++tyz]=j;
	}
	while(txf&&tyf){
		int i=sxf[txf--],j=syf[tyf--];
		ll k=min(-sx[i],-sy[j]);
		a[i][j]-=k,sx[i]+=k,sy[j]+=k;
		if(sx[i])sxf[++txf]=i;
		if(sy[j])syf[++tyf]=j;
	}
	while(txz&&txf){
		int l=sxz[txz--],r=sxf[txf--];
		ll k=min(sx[l],-sx[r]);
		a[l][1]+=k,a[r][1]-=k,sx[l]-=k,sx[r]+=k;
		if(sx[l])sxz[++txz]=l;
		if(sx[r])sxf[++txf]=r;
	}
	while(tyz&&tyf){
		int l=syz[tyz--],r=syf[tyf--];
		ll k=min(sy[l],-sy[r]);
		a[1][l]+=k,a[1][r]-=k,sy[l]-=k,sy[r]+=k;
		if(sy[l])syz[++tyz]=l;
		if(sy[r])syf[++tyf]=r;
	}
	ll ans=0;
	repn(i)repm(j)if(i+j&1)a[i][j]*=-1;
	repn(i)repm(j)ans+=abs(a[i][j]);
	pf(ans),putchar('\n');
	repn(i){
		repm(j)pf(a[i][j]),putchar(' ');
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：masonpop (赞：2)

**出于个人习惯，以下将矩阵行列数 $H,W$ 改为 $n,m$**。

首先有一个关键变换：给原图黑白染色，把黑点权值取反，这样每次操作转化为给两黑点 $-x$，两白点 $+x$。

性质出现了：每行每列的和都不变！设每行每列的和为 $x_i,y_i$，那么有一个更强的结论，就是两个矩阵可达当且仅当所有 $x,y$ 对应相等。证明也很简单，数归即可。

设最终矩阵为 $G$，现在问题变为：已知 $G$ 的所有 $x_i,y_i$，求其元素绝对值之和的最小值。显然有一个理论下界

$\text{Ans}=\max(\sum\limits_{i=1}^n|x_i|,\sum\limits_{i=1}^m|y_i|)$。

接下来证明其可以取到并给出构造。

为了减少绝对值造成的损耗，我们当然希望所有位置 $(i,j)$ 的值与其对应的 $x_i,y_j$ 同号。如果每次给 $G_{i,j}$ 加上 $d$，相当于 $x_i,y_j$ 均减去 $d$（可以理解为差距的减小）。可以按照如下步骤构造：

① 选择两个同号的 $x_i,y_j$，将绝对值较小者变为 $0$。

此时由于 $\sum x_i=\sum y_j$，故要么 $x$ 全为 $0$，要么 $y$ 全为 $0$。接下来进入下一步。

② 选择两个异号的 $x_i,x_j$ 或 $y_i,y_j$，将绝对值较小者变为 $0$。此时符号就正确了。

别忘了我们刚开始是染色后翻转，因此还得翻回来。复杂度理论 $O((n+m)^3)$，但是显然跑不满所以过了。[代码](https://www.luogu.com.cn/record/139712810)。

---

## 作者：freoepn (赞：1)

先考虑 $2 \times 2$ 矩形加有什么性质，将矩阵黑白染色，将黑格子里的数取相反数，这样改变不会影响绝对值的和，操作后 $2 \times 2$ 矩形加对于每一行每一列来说都是加一次减一次，行或列上数的总和不变，归纳法可知保持原来行列总和不变的矩阵都可以变化得到，问题转化为行和列总合确定求如何分配使得绝对值之和最小。

设 $x_i$ 为第 $i$ 行之和，$y_i$ 为第 $j$ 行之和，答案最小为 $\min(\sum_{i=1}^n |x_i|,\sum_{i=1}^m |y_i|)$，可以构造证明这个解始终存在，首先找到所有 $(i,j)$ 使得 $x_i$ 和 $y_j$  同号，将其中绝对值较小的填入 $(i,j)$ 使得 $x_i$ 和 $y_j$ 中较小的变为 $0$，直到不能操作为止，这时 $x$ 和 $y$ 中一定有一个全是 $0$ ,因为此时 $x$ 和 $y$ 要么一个全是非正数一个全是非负数，要么其中一个全为 $0$，第一种情况明显不满足 $x$ 之和与 $y$ 之和相等的条件，可知 $x$ 和 $y$ 中一定一个全为 $0$。

接下来考虑如何对 $x$ 和 $y$ 中不全是 $0$ 的那个进行消除，不妨设为 $x$，$x$ 中一定有正有负且总和为 $0$，每次选一行总和为正的和一行总和为负的，设其中较小的绝对值为 $p$，随便选一列将正的那一行减去 $p$ 负的哪一行加上 $p$，就可以在不改变列的情况下改变行，一直操作直到匹配完成为止，注意答案矩阵要还原为没取相反数的状态。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int kMaxN = 505;
int a[kMaxN][kMaxN], b[kMaxN][kMaxN];
int sum[kMaxN], summ[kMaxN];
signed main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
      if ((i + j) % 2 == 0) {
        a[i][j] = -a[i][j];
      }
      sum[i] += a[i][j], summ[j] += a[i][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (sum[i] > 0 && summ[j] > 0) {
        b[i][j] = min(sum[i], summ[j]);
        sum[i] -= b[i][j], summ[j] -= b[i][j];
      } else if (sum[i] < 0 && summ[j] < 0) {
        b[i][j] = max(sum[i], summ[j]);
        sum[i] -= b[i][j], summ[j] -= b[i][j];
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (sum[i] > 0 && sum[j] < 0) {
        int e = min(abs(sum[i]), abs(sum[j]));
        sum[i] -= e, sum[j] += e;
        b[i][1] += e, b[j][1] -= e;
      } else if (sum[i] < 0 && sum[j] > 0) {
        int e = min(abs(sum[i]), abs(sum[j]));
        sum[i] += e, sum[j] -= e;
        b[i][1] -= e, b[j][1] += e;
      }
    }
  }
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= m; j++) {
      if (summ[i] > 0 && summ[j] < 0) {
        int e = min(abs(summ[i]), abs(summ[j]));
        summ[i] -= e, summ[j] += e;
        b[1][i] += e, b[1][j] -= e;
      } else if (summ[i] < 0 && summ[j] > 0) {
        int e = min(abs(summ[i]), abs(summ[j]));
        summ[i] += e, summ[j] -= e;
        b[1][i] -= e, b[1][j] += e;
      }
    }
  }
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    for(int j = 1;j <= m;j++){
      sum += abs(b[i][j]);
    }
  }
  cout << sum << '\n';
  for (int i = 1; i <= n; i++) {
    for(int j = 1;j <= m;j++){
      cout << b[i][j]<< " ";
    }
    cout << '\n';
  }
}
```

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc135_d)

**题目大意**

> 给定 $n\times m$ 矩阵，每次操作可以把 $2\times 2$ 子矩形中的每个元素 $\pm 1$，若干次操作后最小化所有元素的绝对值和，给出构造。
>
> 数据范围：$n,m\le 500$。

**思路分析**

给矩阵黑白间隔染色，并把白格取反，这样不改变答案。

此时所有的操作都不改变每行每列的元素和，因此答案的下界是每行元素和的绝对值之和以及每列元素和的绝对值之和。

不难发现这个下界是可以取到的，下给出构造性证明：

- 不妨设每行元素的绝对值之和大于每列元素的绝对值之和，那么一组解取到下界当且仅当每个元素的符号和其行和符号相等。
- 如果有一行一列同为正，那么在交点处填行和与列和的较小值（同为负同理）。
- 由于行和列和总和相等，因此该过程停止时所有列和一定为 $0$。
- 此时找到一正一负的两行，任取一列填绝对值较小值。

每次填数至少使得一行或一列和为 $0$，操作次数 $\mathcal O(n+m)$。

时间复杂度 $\mathcal O((n+m)^2)$。

**思路分析**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=505;
int n,m;
ll a[MAXN][MAXN],R[MAXN],C[MAXN],ans=0;
void add(int i,int j,ll x) { a[i][j]+=x,R[i]-=x,C[j]-=x; }
signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1,w;i<=n;++i) for(int j=1;j<=m;++j) {
		scanf("%d",&w),w*=(i+j)&1?-1:1,R[i]+=w,C[j]+=w;
	}
	while(true) {
		int ip=0,in=0,jp=0,jn=0;
		for(int i=1;i<=n;++i) ip=(R[i]>0?i:ip),in=(R[i]<0?i:in);
		for(int j=1;j<=m;++j) jp=(C[j]>0?j:jp),jn=(C[j]<0?j:jn);
		if(ip&&jp) add(ip,jp,min(R[ip],C[jp]));
		else if(in&&jn) add(in,jn,max(R[in],C[jn]));
		else if(ip&&in) {
			ll z=min(R[ip],-R[in]);
			add(ip,1,z),add(in,1,-z);
		} else if(jp&&jn)  {
			ll z=min(C[jp],-C[jn]);
			add(1,jp,z),add(1,jn,-z);
		} else break;
	}
	for(int i=1;i<=n;++i) for(int j=1;j<=m;++j) ans+=abs(a[i][j]);
	printf("%lld\n",ans);
	for(int i=1;i<=n;++i,puts("")) for(int j=1;j<=m;++j) printf("%lld ",a[i][j]*((i+j)&1?-1:1));
	return 0;
}
```

---

## 作者：Feyn (赞：0)

首先需要做一个转化。把原来的表格黑白染色，并把黑色的格子取反。这样做有两个好处：一个是新表格的答案和原表格的答案是一样的，因为一个数取反之后绝对值不变；另一个是说这样一来每次操作中每一行每一列都恰好涉及一个白格子和一个黑格子，也就是说这一排的数的和是不变的。

于是答案就很显然了，即每行绝对值之和和每列绝对值之和的较大值。当然可以尝试着去大概证明一下。

首先有一个结论是任意满足行和列和和原表格相同的数都可以由原表格通过一系列操作得到，大概就是可以从一个角落向其它角落操作，最后只有一行一列没被确定，由于和是相同的，所以最后的那一行一列和原表应该也是相同的，这是必要性。

充分性可以通过构造过程来证明，此时问题就变成了希望找到一个表使得其行列和合法并且元素绝对值之和等于我们的答案。思考一下什么时候前者满足而后者不满足，肯定是存在一行中存在两个数一正一负，加起来抵消了，绝对值就产生了浪费。避免这种浪费的方法就是让元素和所在行列和的符号保持一致，于是每次暴力找到一对行和列符号相同就能避免这种浪费。如果找不到了，那么说明有一方已经全零了，剩下的就填充相反数即可，容易发现这样构造出来的表格元素绝对值之和就是前文的答案。

---

