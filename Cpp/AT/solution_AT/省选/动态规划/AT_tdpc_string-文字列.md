# 文字列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_string

入力は以下の形式で標準入力から与えられる。

> $ freq_1 $ $ ... $ $ freq_{26} $

 答えを一行に出力せよ。 ```

1 0 2 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

```

6
```

```

1 1 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```

```

3628800
```

## 说明/提示

### Constraints

 以下の条件を満たす文字列の個数を mod 1,000,000,007 で求めよ。

- a を $ freq_1 $ 個、b を $ freq_2 $ 個、... z を $ freq_{26} $ 個含む (他の文字は含まない)。
- 同じ文字が隣り合うことはない。

- - - - - -

- $ 0\ <\ =\ freq_i\ <\ =\ 10 $
- At least one of $ freq_i $ will be nonzero.

# 题解

## 作者：EricQian (赞：4)

[AT_tdpc_string 文字列](https://www.luogu.com.cn/problem/AT_tdpc_string)

> 构造一个小写字母构成的字符串，使小写字母 $i$ 出现了 $h_i$ 次，且相同字母不能相邻，求方案数并对 $10^9 + 7$ 取模。 
> 
> $0 \leq h_i \leq10$。

PS：目前已知最优解

首先有一个最暴力的搜索，考虑一个一个加入字母，记下每个字母都还剩下多少个，上一次加了什么字母。。复杂度 $\mathcal{O(sum!)}$。

在这个暴力中，容易发现其中很多过程都是不需要的，正所谓“言简意赅”，我们要用更少的状态代替上面的累赘。

同样的字母没有任何区别，那么不能够将他们分开处理，考虑**一种一种字母加入**。那么在加入一种新的字母时，可以将他们放到串的各个位置。由于题目要求相邻字符不能相同，影响了每次加入位置的限制，不妨记下当前**有多少相邻字符是相同的**。

设 $f_{i,k}$ 表示加完前 $i$ 个字符后，字符串中有 $k(k\le sum_{i-1})$ 个相邻的位置字符相同的方案数。

考虑转移，新的字符可以做三件事情：

+ 将原来相邻相同的“好基友”拆散，设有 $p$ 个这样的字符，方案数
    $$
    \dbinom{k}{p}
    $$

+ 自己组成一对“好基友”，设组成了 $q$ 对，方案数（隔板法，原本有 $f_i-1$ 块板，去掉一块增加一对基友）
    $$
    \dbinom{f_i-1}{q}
    $$

+ 什么事也不干，有 $o$ 个这样的字符，方案数（隔板法，原本有 $sum_{i-1}+1$ 个空隙，去掉 $k$ 个是相邻相同的）
    $$
    \dbinom{sum_{i-1}+1-k}{o}
    $$

上面 $p,q,o$ 必须保证 $p\le k,q\le \max(f_i-1,0),f_i-q=p+o$，结合其意义显然。

那么枚举 $i,k,p,q,o$ 转移即可，复杂度 $\mathcal{O(n\times sum\times f^2)}$，大约 $10^5$ 级别。

```cpp
// Author:A weak man named EricQian
// Attention:Check your code while coding!
#include<bits/stdc++.h>
using namespace std;
#define infll 0x3f3f3f3f3f3f3f3f
#define inf 0x3f3f3f3f
#define pb push_back
#define eb emplace_back
#define pa pair<int,int>
#define fi first
#define se second
typedef long long ll;
#define Maxc 30
#define Maxsumn 305
#define mod 1000000007
inline int rd()
{
	int x=0;
	char ch,t=0;
	while(!isdigit(ch = getchar())) t|=ch=='-';
	while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
	return x=t?-x:x;
}
int st;
int hav[Maxc],sum[Maxc];
int C[Maxsumn][Maxsumn],dp[Maxc][Maxsumn];
int main()
{
	//ios::sync_with_stdio(false); cin.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	C[0][0]=1;
	for(int i=1;i<=26;i++)
	{
		hav[i]=rd();
		if(!st && hav[i]) st=i;
		sum[i]=sum[i-1]+hav[i];
	}
	if(sum[26]==0) { printf("0\n"); return 0; }
	for(int i=1;i<=300;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	dp[st][hav[st]-1]=1;
	for(int i=st+1;i<=26;i++) for(int k=0;k<sum[i-1];k++)
		for(int q=0;q<max(hav[i],1);q++) for(int p=0;p<=k && p+q<=hav[i];p++)
		{
			int o=hav[i]-p-q;
			dp[i][k-p+q]=(dp[i][k-p+q]+1ll*dp[i-1][k]*
				C[max(hav[i]-1,0)][q]%mod*C[k][p]%mod*C[sum[i-1]+1-k][o]%mod)%mod;
		}
	printf("%d\n",dp[26][0]);
	//fclose(stdin);
	//fclose(stdout);
	return 0;
}
```

---

## 作者：include_BM (赞：4)

设 $s_i=\sum_{j=1}^ifreq_j$，$f_{i,j,k,l}$ 表示已经放完了 $i-1$ 种字母，第 $i$ 种字母已经放了 $j$ 个，前 $i-1$ 种字母共有 $k$ 对相邻，第 $i$ 种字母有 $l$ 对相邻的情况数。

初始时 $f_{1,0,0,0}=1$，考虑如何从 $f_{i,j,k,l}$ 转移。

1. $j<freq_i$，那么下一位放的还是当前字母：

> 1. 新放的字母减少了前 $i-1$ 种字母的相邻对数，即转移到 $f_{i,j+1,k-1,l}$，放在任意一对相邻字母之间即可，共有 $k$ 种放法。
> 
> 2. 新放的字母新增了第 $i$ 种字母的相邻对数，即转移到 $f_{i,j+1,k,l+1}$，放在任意一个同种字母旁边即可，由于每对相邻字母公用一个位置，故共有 $2\times j-l$ 种放法。
>
>3. 新放的字母没有改变相邻对数，即转移到 $f_{i,j+1,k,l}$，此时放在除上述以外的任何位置即可，共有 $s_{i-1}+j+1-k-(2\times j-l)=s_{i-1}-j-k+l+1$ 种放法。

2. $j=freq_i$，转移到 $f_{i+1,0,k+l,0}$，在 $i+1$ 处进行处理。

但是同种字母间是无序的，这种做法考虑了相对顺序，需要最后除以 $\prod freq_i!$。

```cpp
const int N=30,P=1e9+7;
ll a[N],s[N],f[N][12][N*12][N],inv[N],d=1;

inline void Add(ll &x,ll y){x=(x+y)%P;}

signed main(){
    for(int i=1;i<=26;++i) s[i]=s[i-1]+(a[i]=read());
    f[1][0][0][0]=1;
    for(int i=1;i<=26;++i){
        for(int j=0;j<=a[i];++j)
            for(int k=0;k<=(i-1)*10;++k)
                for(int l=0;l<10;++l){
                    if(j<a[i]){
                        if(k) Add(f[i][j+1][k-1][l],f[i][j][k][l]*k);
                        Add(f[i][j+1][k][l+1],f[i][j][k][l]*(2*j-l));
                        Add(f[i][j+1][k][l],f[i][j][k][l]*(s[i-1]-k-j+l+1));
                    }
                    else Add(f[i+1][0][k+l][0],f[i][j][k][l]);
                }
    }
    inv[0]=inv[1]=1;
    for(int i=2;i<=10;++i) inv[i]=(P-P/i)*inv[P%i]%P;
    for(int i=2;i<=10;++i) inv[i]=inv[i-1]*inv[i]%P;
    for(int i=1;i<=26;++i) d=d*inv[a[i]]%P;
    printf("%lld\n",f[27][0][0][0]*d%P);
    return 0;
}
```

---

## 作者：Bitaro (赞：3)

汗流浃背了兄弟，近两个月做过的纯度最高的动态规划。

看到不相邻，想到插板法。我们设每个字母的个数分别为 $a_{[1,26]}$。

尝试一个一个填字母，首先填第一个。填完之后，发现中间有 $a_1-1$ 个空格不满足条件。想要满足题目条件，我们需要用后面的字母将这 $a_1-1$ 个空格填满。

于是我们可以得知：对于每个相邻的字母，后来的字母至少有一个要填充进去。于是记录 $f_{i,j}$ 表示当前填到字母 $i$，当前有 $j$ 个相同字母相邻。转移枚举新减少的相邻字母，与当前字母分为几段即可。

注意以下细节：

1. 字母一共有 $26$ 个。

2. 字符串总长最大可达 $260$。

3. 这是 AT 早期题目，请在行末输出换行符。

具体枚举细节可以看代码，由于调了很久注释很详细：

```cpp
/*
slow is fast
*/
#include<bits/stdc++.h>
#define pre(i,a,b) for(int i=a;i<=b;++i)
#define suf(i,a,b) for(int i=a;i>=b;--i)
#define ll long long
#define pii pair<int,int>
using namespace std;
char *p1,*p2,buf[100000];
#define nc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
template<typename T> T read(T &x) {
  int f=1;
  char ch=nc();
  while(ch<48||ch>57) {
    if(ch=='-') f=-1;
    ch=nc();
  }
  while(ch>=48&&ch<=57) x=x*10+ch-48,ch=nc();
  return x*f;
}
const int N=26,p=1e9+7;
namespace Y {
int plu(int a,int b) { return a+b>=p?a+b-p:a+b; }
int mul(int a,int b) { return (1ll*a*b)%p; }
int qpow(int u,int v,int ans=1) { for(;v;v>>=1,u=mul(u,u)) if(v&1) ans=mul(ans,u); return ans; }
int n,a[27];
int f[N][266],tot,fac[266],inv[266];
void init(int n) {
  fac[0]=inv[0]=1;
  pre(i,1,n) fac[i]=mul(fac[i-1],i);
  inv[n]=qpow(fac[n],p-2);
  suf(i,n-1,1) inv[i]=mul(inv[i+1],i+1);
}
int C(int n,int m) { return mul(fac[n],mul(inv[m],inv[n-m])); }
void MAIN() {
  n=26;
  init(260);
  pre(i,1,n) read(a[i]);
  sort(a+1,a+n+1,[](int a,int b) { return a>b; });
  tot=a[1];
  if(a[1]==0) {
    cout<<1<<endl;
    return ;
  }
  f[1][a[1]-1]=1;
  int fin=27;
  pre(i,2,26) {
    int sum=tot+1;//当前可以放置字母的空格数
    if(a[i]==0) { fin=i;break; }//为 0 则字符串已确定
    pre(j,0,tot-1) { // 当前不合法总数
      int z=sum-j;//当前合法空格数，用总空格数减不合法空格数
      pre(k,0,min(a[i],j)) { // 去除的不合法数
        pre(w,max(1,k),min({z+k,sum,a[i]})) { //划分的段数
        // max 原因是：每个减去的不合法空格都需要一段
        // min 中三个数依次为：允许放置的段数（k个被删除不合法空格之外的不合法空格不允许被放置），总段数，最多划分段数
          int ne=a[i]-w;//新增不合法数
          int cnt=mul(C(z,w-k),C(j,k));//选择插入段方案数
          f[i][j-k+ne]=plu(f[i][j-k+ne],mul(f[i-1][j],mul(cnt,C(a[i]-1,w-1))));
          //选择完插入段后还要选择每个段几个字母
        }
      }
    }
    tot+=a[i];
  }
  cout<<f[fin-1][0]<<endl;
}
};//namespace Y
signed main() {
  auto I=freopen("text.in","r",stdin);
  auto O=freopen("text.out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0);cout.tie(0);
	int T=1;
	while(T--) Y::MAIN();
	return 0;
}
```



---

## 作者：OIerAlbedo (赞：3)

## Solution

我们可以利用隔板法的思想，假设 $ f[i][j] $ 表示截止到前 $ i $ 个不同的数，有 $ j $ 个不合法的空位，最终答案为 $ f[len][0] $，其中 $ len $ 为不同的数的个数。

然后我们可以发现，新加进来 $ fre $ 个相同的数，前面总共有 $ sum $ 个数，那么总共有 $ sum+1 $ 个空位，我们需要知道的有：

$ lst1 $ 表示前面不合法的空位的数量。

$ now $ 表示当前这 $ fre $ 个数会抵消多少个不合法的空位。

$ add $ 表示当前这 $ fre $ 个数会增加几个不合法的空位。

现在我们还要考虑的是如果增加了 $ add $ 个不合法的空位会对这新加进来的 $ fre $ 的数产生什么影响，我们假设会分成 $ x $ 段，那么 $ \sum_{i=1}^x len[x]-1=add $，就是 $ fre-x=add $，就是 $ x=fre-add $,就是如果我们要增加 $ add $ 个空位势必要分成 $ fre-add $ 段，而我们发现如果枚举有多少个空位不好做，我们考虑枚举分成几段。

那么有如下转移：
$$
f[i][lst1-now+fre-x]+=f[i-1][lst]\times C(fre-1,fre-x)\times C(lst1,now)\times C(sum+1-lst1,x-now)
$$
理论上会 $ \text{T} $，但实际不知道，待我写完再说。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;
long long len,MOD,lsh[1001010],fac[1001010],sum,dif,lst1,x,c[1010][1010],up,fre[100101],f[1010][1010],a[100100],n,i,j,now,ans;
int main() {
    ios::sync_with_stdio(0);cin.tie();cout.tie();
    cin>>n;MOD=1e9+7;
    for (i=1;i<=n;i++) 
         {
         	cin>>a[i];
         	for (j=2,up=sqrt(a[i]);j<=up;j++)
         	     while (a[i] % (j*j)==0) 
         	          a[i]/=(j*j);
         	lsh[i]=a[i];
		 }
	c[0][0]=1;fac[0]=1;
	for (i=1;i<=500;i++)
	    {
	    	c[i][0]=1;c[i][i]=1;
	    	for (j=1;j<i;j++)
	    	   c[i][j]=(c[i-1][j-1]+c[i-1][j]) % MOD;
	    	fac[i]=fac[i-1]*i % MOD;
		}
	sort(lsh+1,lsh+n+1);len=unique(lsh+1,lsh+n+1)-lsh-1;
	for (i=1;i<=n;i++) a[i]=lower_bound(lsh+1,lsh+len+1,a[i])-lsh,fre[a[i]]++;
	f[1][fre[1]-1]=1;sum=fre[1];
	for (i=1,dif=1;i<=len;i++) dif=dif*fac[fre[i]] % MOD;
	for (i=2;i<=len;sum+=fre[i],i++)
	   for (lst1=0;lst1<=sum+1;lst1++)
	        if (f[i-1][lst1]!=0)
	            for (x=1;x<=fre[i];x++)
	                for (now=0;now<=min(lst1,x);now++)
	                    { 
	                    f[i][lst1-now+fre[i]-x]+=f[i-1][lst1]*c[fre[i]-1][fre[i]-x] % MOD*c[lst1][now] % MOD*c[sum+1-lst1][x-now] % MOD;
	                    f[i][lst1-now+fre[i]-x]%=MOD;
						}
    cout<<f[len][0]*dif % MOD<<endl;
	return 0;
}

```



---

## 作者：jijidawang (赞：3)

这下这下了，首先二项式反演，令 $f_n$ 为钦定 $n$ 个位置的方案数，那么考虑依次加入每个字母。

那么整个字符串就被分成 $\sum w_c-n$ 个连续段，枚举钦定位置数后分成若干连续段，分割方案数可以用组合数描述，那么可以得到转移：
$$f'_n=\sum_{i=1}^n\dbinom ni\dbinom{w_c-1}{w_c-i}f_{n-i}$$
那么答案即为：
$$\mathrm{ans}=\sum_{i\ge1}(-1)^if_i$$

时间复杂度 $O((\sum w_c)^2S)$，其中 $S$ 是字符集大小。应该可以类似分治 FFT 分析的更小点（我没试过）。

[Submission](https://atcoder.jp/contests/tdpc/submissions/41667602)。

---

## 作者：yllcm (赞：2)

来一发二项式反演做法。

假设我们已经在原序列中钦定 $t$ 个位置 $i$ 满足 $s_i=s_{i+1}$，那么可以把这些相等的段合并成一个二元组 $(c,x)$，表示这里有 $x$ 个字符 $c$。容易发现此时的字符串变成了由 $\sum \text{freq}_i-t$ 个二元组组成的序列，考虑如何确定这个序列。

我们的构造分为两步：对于每个字符 $c$，将其拆成若干个二元组 $(c,x_i)$ 满足 $\sum x_i=\text{freq}_c$；将得到的二元组集合组成一个序列。对于第一步，可以枚举 $\text{freq}_c$ 的分拆数。对于第二步，将相同的二元组合并成一个多重集后，容易使用多重集组合数得到答案。

为了整合这些信息，我们在外层记录一个 DP 数组 $f_{i,j}$ 表示考虑前 $i$ 个字符，已经钦定了 $j$ 个位置的方案数。考虑转移到 $i+1$，我们枚举在这个位置的钦定位置数 $t$，将其拆成 $\text{freq}_{i+1}-t$ 个二元组，并乘上多重集组合数中的阶乘逆元。将这个状态和 $f_{i,j}$ 合并之后便可得到状态 $f_{i+1,j+t}$。

根据二项式反演相关知识，最后的答案就是 $\sum\limits_i f_{26,i}(-1)^i$。不难发现上述构造可以唯一对应到一个原序列上的钦定方案。 

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define FR first
#define SE second
using namespace std;
inline int read() {
    int x = 0; bool op = 0;
    char c = getchar();
    while(!isdigit(c))op |= (c == '-'), c = getchar();
    while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return op ? -x : x;
}
const int N = 2e3 + 10;
const int P = 1e9 + 7;
void add(int &a, int b) {a = (a + b) % P;}
void sub(int &a, int b) {a = (a - b + P) % P;}
int ksm(int x, int k) {
    int res = 1;
    for(int pw = x; k; (k & 1) ? res = 1ll * res * pw % P : 0, pw = 1ll * pw * pw % P, k >>= 1);
    return res;
}
int f[N], g[N], fac[N], ifac[N];
void init() {
    fac[0] = ifac[0] = 1;
    for(int i = 1; i < N; i++)fac[i] = 1ll * fac[i - 1] * i % P;
    ifac[N - 1] = ksm(fac[N - 1], P - 2);
    for(int i = N - 2; i; i--)ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;
    return ;
}
int dfs(int x, int y, int lst, int cnt) {
    if(y == 0)return (x == 0) * ifac[cnt];
    int res = 0;
    for(int i = lst; i <= x; i++) {
        if(lst == i)add(res, dfs(x - i, y - 1, i, cnt + 1));
        else add(res, 1ll * ifac[cnt] * dfs(x - i, y - 1, i, 1) % P);
    }
    return res;
}
int main() { 
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    init();
    int sum = 0;
    f[0] = 1;
    for(int i = 0; i < 26; i++) {
        int x = read(); sum += x;
        if(x == 0)continue;
        swap(f, g);
        memset(f, 0, sizeof(f));
        for(int i = 0; i <= sum; i++) {
            for(int j = 0; j < x; j++) {
                add(f[i + j], 1ll * g[i] * dfs(x, x - j, 1, 0) % P);
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < N; i++) {
        int w = 1ll * f[i] * fac[sum - i] % P;
        ((i & 1) ? sub(ans, w) : add(ans, w));
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：ylxmf2005 (赞：2)

### Description

构造一个小写字母构成的字符串，使小写字母 $i$ 出现了 $freq_i$ 次，且相同字母不能相邻，求方案数并对 $10^9 + 7$ 取模。 

$1 \leq freq_i \leq10$。

### Solution

计数 dp，先找出所有 $freq_i > 0$ 的小写字母，一个个插入字符串中。因为答案与插入顺序无关，所以我们按 `aabbbccddddeeefgg` 这样的顺序插入。在插入的过程中，难免会出现不合法的情况。举个栗子，如 `*a a*c*b*d d d*b b*`，不合法的位置有 $4$ 个，即为空格。合法位置有 $6$ 个，即为 `*`。可以发现三个性质：

1. $S$ 的合法位置数与不和法位置数之和为 $|S| + 1$
2. 没有两个合法位置或不合法位置是相邻的。
3. 每一个合法位置可以插入任意个字母，也可以不插。

可以想到状态，令 $f_{i,j}$ 为插入了所有的小写字母 $i$ 后，有 $j$ 个不合法位置的方案数。赋初值，将第一段 $freq_i > 0$ 的小写字母全部插入后的 $f_{i,j} = 1$。如 `bbbccddddeeefgg` 中 `bbb` 是第一段，于是 $f_{b - a = 1, 2} = 1$。


枚举 $i$，和 $f_{i-1,k}$ 中的 $k$，意味着 $f_{i,j}$ 会从 $f_{i-1,k}$ 转移。考虑将所有的小写字母 $i$ 插入到字符串中，无非是插入到合法的位置或不合法的位置。所以再枚举一个 $good$ 和 $bad$，如字面意思，$good$ 为插入到合法位置的**段数**，$bad$ 为插入到不合法位置的段数。在枚举的过程中，同时维护一个在加入字母前的字符串长度 $sum$，用于确定枚举范围。 


考虑一个问题：将所有小写字母 $i$ 加入字符串，有 $good$ 段字母插入了合法位置，有 $bad$ 段字母插入了不合法位置。那么新产生了多少不合法的位置，又减少了多少不合法的位置？

减少的就是 $good$ 个。因为插入的字母分成了 $good + bad$ 段，那么新产生了 $good + bad - 1$ 个间隔。如果 $good+bad=1$，那么成为不合法位置的位置一共有 $freq_i - 1$ 个，所以增加了 $freq_i - 1 - good - bad + 1 = freq_i - good - bad$ 个不合法位置。

所以，$j = k - bad + freq_i - good - bad$。

转移方程如下，其中 $sum + 1 - k$ 为根据性质一求出的合法位置个数，$n \choose m$ 为组合数可以预处理。可以发现，转移方程是根据乘法原理将每一部分相乘，其中的 ${freq_i - good - bad} \choose {f_i - 1}$ 是什么呢？因为我们是把一段段相同的字母插入合法的位置或不合法的位置，不仅要乘上几段字母插入到哪几个位置的方案数，还要乘上所有的字母 $i$ 是如何分成了几段字母的方案数。把一段字母看成一个盒子，每个字母看成一个球，一共 $good + bad$ 个盒子，$freq_i$ 个球，问题转换成求每个盒子至少一个球的方案数。套上[插板法](http://baidu.apphb.com/?q=%E6%8F%92%E6%9D%BF%E6%B3%95)公式即可。

$$f_{i,j} = f_{i,j} + f_{i - 1,k} \times {{bad}\choose{k}} \times {{good}\choose{sum + 1 - k}}  \times  {{good + bad -1} \choose{freq_i - 1}} $$
$$ans = f_{n-1,0}$$

时间复杂度 $O(n^3)$，其中 $n  = \sum_{i=0}^{25} freq_i$。


### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 500 + 5, p = 1e9 + 7;
inline int read() {
    int X = 0,w = 0; char ch = 0;
    while(!isdigit(ch)) {w |= ch == '-';ch = getchar();}
    while(isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48),ch = getchar();
    return w ? -X : X;
}
int f[26][N], C[N][N], freq[N], sum, fir, n;
signed main() {
	for (int i = 0; i < 26; i++) {
		freq[n] = read();
		if (freq[n]) n++;
	}
	for (int i = 0; i <= 300; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % p;
	}
    f[0][freq[0] - 1] = 1, sum = freq[0];
    for (int i = 1; i < n; i++) {
    	for (int k = 0; k <= sum; k++) 
			for (int bad = 0; bad <= min(freq[i], k); bad++)
				for (int good = 0; good + bad <= freq[i] && good <= sum + 1 - k; good++) {
					int j = k - bad + freq[i] - good - bad;
					f[i][j] = (f[i][j] + f[i - 1][k] * C[k][bad] % p * C[sum + 1 - k][good] % p 
					* C[freq[i] - 1][good + bad - 1] % p) % p;
				}
		sum += freq[i]; 
    }	
	printf("%lld\n", f[n - 1][0]);
	return 0;
}  
```

---

## 作者：_jimmywang_ (赞：1)

做傻了，纯 dp 不会了。

当然，本题存在使用多项式科技的做法，左转加强版 [ABC260H](https://www.luogu.com.cn/problem/AT_abc260_h)。

-------

设第 $i$ 种字符出现次数为 $a_i$。

不好直接做，我们考虑从 a 到 z 添加字符，并设状态为 $dp_{i,j}$，表示前 $i$ 种字符填完后，字符串中有 $j$ 个相邻的相同字母对。

考虑如何转移。设当前考虑字符 $i$，我们想从 $dp_{i-1,j}$ 转移到 $dp_{i,*}$。我们可以枚举 $a_i$ 在填进去以后被,切成了几段，并依据这个来转移。

设切成 $x$ 段，那么由插板法，切的方案数是 $\binom{a_i-1}{x-1}$。这样会产生额外的 $a_i-x$ 对相邻字母对。接下来考虑把这 $x$ **段**插入原串中。

我们再枚举这 $x$ 段把多少个原来的相邻字母对分开了。设他把 $y$ 个原有的相邻字母对分开了，你怎么选择这 $y$ 个位置的方案数是 $\binom{j}{y}$。把一对分开需要用一段，那么剩下的 $x-y$ 需要填到原来不是相同字母相邻的位置里去，选择这些位置的方案数是 $\binom{(\sum_{t=1}^{i-1}a_t)+1}{y-x}$ 种。

选择定了插入的位置后，将这 $x$ 段依次填入就是一种合法方案。因此，把所有方案数乘起来我们得到：

$$dp_{i,j+(a_i-x)-y} \leftarrow \sum_{x=1}^{a_i}\sum_{y=x}^{j}dp_{i-1,j}\binom{a_i-1}{x-1}\binom{j}{y}\binom{(\sum_{t=1}^{i-1}a_t)+1}{y-x}$$

时间复杂度 $O(\Omega\times (\sum a_i)^2\times \max(a_i))$，随便跑（$\Omega$ 是字符集大小，即 26）。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
const ll N=300010;
struct edge{ll v,w,nx;}e[N<<1];
ll hd[N],cnt;
void add(ll u,ll v,ll w){e[++cnt]=(edge){v,w,hd[u]};hd[u]=cnt;}
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m;
ll a[26];
ll dp[26][300];
ll C[310][310];
const ll mod=1e9+7;
int main(){
    f(i,0,25)a[i]=d;
    C[0][0]=1;
    f(i,1,300){
        C[i][0]=1;
        f(j,1,i)C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
    dp[0][max(0ll,a[0]-1)]=1;
    ll s=a[0];
    f(i,1,25){
        if(!a[i]){f(j,0,270)dp[i][j]=dp[i-1][j];continue;}
        f(j,0,270)if(dp[i-1][j]){
            f(x,1,a[i])f(y,0,j)if(x>=y){
                dp[i][j+(a[i]-x)-y]=(dp[i][j+(a[i]-x)-y]+dp[i-1][j]*C[a[i]-1][x-1]%mod*C[j][y]%mod*C[s+1-j][x-y])%mod;
                // cout<<i<<" "<<j+(a[i]-x)-y<<endl;
            }
        }s+=a[i];
    }cout<<dp[25][0]<<endl;
	return 0;
}
```

---

## 作者：Graphcity (赞：0)

先来考虑 “相同字母不能相邻” 这个条件。有一个经典的问题：

- 从 $1\sim n$ 中选出 $k$ 个数，并且 $k$ 个数不相邻的方案数。

这个问题的解法就是在 $k$ 个数的空隙中插入 $n-k$ 个数，且每个空隙至少插入一个数。利用插板法可知答案为 $\dbinom{n-k+1}{k}$。

借用这道题目的思路，我们可以这样想：一个字母一个字母地考虑，每次考虑到一个新字母时就让它插进前面字母的空隙中。显然这样的插入方式和最终形成的字符串是一一对应的。

设 $f_{i,j}$ 表示已经考虑完前 $i$ 种字母，且有 $j$ 个相同字母是相邻的。发现 $freq_i$ 不大，考虑暴力枚举第 $i$ 种字母的插入方式。这可以用一个 $freq_i-1$ 位的二进制数来表示，其中第 $k$ 位表示要分开第 $k$ 个和第 $k+1$ 个字母。

再设 $pop(k)$ 表示 $k$ 的二进制中 $1$ 的个数。那么划分方式为 $k$ 就对应要分成 $pop(k)+1$ 段，且新增了 $freq_i-1-pop(k)$ 对相同相邻字母。设这 $k+1$ 段共要填补 $l$ 个相同字母间的空隙，那么就有：

$$
f_{i-1,j}\times\binom{j}{l}\times\binom{sum_{i-1}+1-j}{pop(k)+1-l} \to f_{i,j-l+freq_i-1-pop(k)}
$$

其中 $sum_i=\sum_{j=1}^i freq_j$。

总时间复杂度 $O(nsum_nk2^k)$，其中 $k=\max_{i=1}^n freq_i$。注意特判 $freq_i=0$ 的情况，此时转移数组不变。

```cpp
#include<bits/stdc++.h>
#define pop(x) __builtin_popcount(x)
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=26,Maxm=260,Mod=1e9+7;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int val[Maxn+5],sum,f[Maxn+5][Maxm+5];
int fac[Maxm+5],inv[Maxm+5];
inline int C(int x,int y) {return 1ll*fac[x]*inv[x-y]%Mod*inv[y]%Mod;}

int main()
{
    fac[0]=inv[0]=1;
    For(i,1,Maxm) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[Maxm]=Pow(fac[Maxm],Mod-2);
    Rof(i,Maxm-1,1) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
    For(i,1,26) cin>>val[i];
    f[1][max(0,val[1]-1)]=1,sum=val[1];
    For(i,2,26)
    {
        if(!val[i])
        {
            For(j,0,sum) f[i][j]=f[i-1][j];
            continue;
        }
        int lim=(1<<val[i]-1)-1;
        For(j,0,lim)
        {
            int res=val[i]-1-pop(j);
            int cnt=pop(j)+1;
            For(k,0,sum) if(f[i-1][k])
            {
                int now=f[i-1][k];
                For(l,0,min(k,cnt)) if(sum+1-k>=cnt-l)
                    f[i][k-l+res]=(f[i][k-l+res]+1ll*now*C(k,l)%Mod*C(sum+1-k,cnt-l)%Mod)%Mod;
            }
        }
        sum+=val[i];
    }
    printf("%d\n",f[26][0]);
    return 0;
}
```

---

