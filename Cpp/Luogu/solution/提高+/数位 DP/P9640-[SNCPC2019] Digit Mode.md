# [SNCPC2019] Digit Mode

## 题目描述

设 $m(x)$ 为正整数 $x$ 的十进制表示中数字的众数。众数是序列中出现频率最高的最大值。例如，$m(15532)=5$，$m(25252)=2$，$m(103000)=0$，$m(364364)=6$，$m(114514)=1$，$m(889464)=8$。

给定一个正整数 $n$，DreamGrid 想知道 $(\sum\limits_{x=1}^{n} m(x)) \bmod (10^9+7)$ 的值。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5
9
99
999
99999
999999```

### 输出

```
45
615
6570
597600
5689830```

# 题解

## 作者：OrezTsim (赞：7)

设 $d$ 为 $x$ 中出现次数最多的最大数。

记 $\text{cnt}_{i,x}$ 为 $x$ 中数位 $i$ 的出现次数，那么有：

- $\forall d'<d,\text{cnt}_{i,d'} \le \text{cnt}_{i,d}$。
- $\forall d'>d,\text{cnt}_{i,d'}<\text{cnt}_{i,d}$。

做法实际上就很简单了，依次枚举 $d$，$\text{LCP}$，$\text{LCP}$ 的后一位是多少，在剩余的未确定数位中有多少个 $d$。

剩下的部分可以通过背包来解决。

令 $f_{i}$ 表示在剩余的未确定的 $p$ 个数位中确定 $i$ 位的方案数。

因为此时已经可以随便选 $[0,9]$ 中除 $d$ 以外的数了，所以考虑枚举 $j \in [0,9]$，枚举选择的个数 $k$，那么有 $f_{i} \leftarrow f_{i}+\binom{p-(i-k)}{k} \times f_{i-k}$。

那么 $f_p$ 就是这部分的答案。

一个坑点就是前导零，也就是位数 $<\log_{10}n+1$ 的数可能会算错。

可以通过枚举位数从而规定它的上限是 $99 \dots 9$ 还是 $n$ 来解决。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=110,P=1e9+7;
int n,cnt[10],f[N],dig[N],C[N][N];
void md(int &x,int y) { ((x+=y)>=P)&&(x-=P); }

void solve(int res=0) {
    string str; cin>>str; int len=str.size();
    for(n=1;n<=len;++n) {
        if(n<len) fill(dig+1,dig+1+n,9);
        else for(int i=1;i<=n;++i) dig[i]=str[i-1]^48;
        for(int d=1;d<10;++d) {
            fill(cnt,cnt+10,0);
            for(int lcp=0;lcp<n;++lcp) {
                int sto=n-lcp-1;
                for(int nxt=!lcp;nxt<dig[lcp+1];++nxt) {
                    ++cnt[nxt];
                    for(int ext=0;ext<=sto;++ext) {
                        int all=cnt[d]+ext; bool ok=true;
                        for(int i=0;i<10;++i)
                            if((i<d&&cnt[i]>all)||(i>d&&cnt[i]>=all))
                                { ok=false; break; }
                        if(!ok) continue;
                        int lst=sto-ext; fill(f,f+lst+1,0),f[0]=1;
                        for(int i=0;i<10;++i) {
                            if(i==d) continue;
                            for(int j=lst;j;--j)
                                for(int k=1;k<=j&&k+cnt[i]<all+(i<d);++k)
                                    md(f[j],f[j-k]*C[lst-(j-k)][k]%P);
                        }
                        md(res,f[lst]*C[sto][ext]%P*d%P);
                    }
                    --cnt[nxt];
                }
                ++cnt[dig[lcp+1]];
            }
        }
        fill(cnt,cnt+10,0); int col=0;
        for(int i=1;i<=n;++i) ++cnt[dig[i]];
        for(int i=1;i<10;++i) if(cnt[i]>=cnt[col]) col=i;
        md(res,col);
    }
    cout<<res<<"\n";
}

auto main() -> signed {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    for(int i=0;i<=100;++i) C[i][0]=1;
    for(int i=1;i<=100;++i)
        for(int j=1;j<=i;++j)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
```

---

## 作者：FFTotoro (赞：6)

模拟赛 T3，场切了。赛后得知原题后翻了一下题解区，发现居然没有和我一样的做法，于是写一篇题解造福后人。

下文记整数 $n$ 的“长度”（即十进制下的位数）为 $\mathrm{len}(n)$。

考虑数位 DP，从高位到低位枚举。记录三个信息，分别为当前处理到的位置 $x$（这里规定下标从 $0$ 开始，即最高位所对应的 $x=0$，次高位的 $x=1$，以此类推）、目前确定的所有位是不是**全部为** $0$（即处于“前导零”的阶段），以及后面的位是否可以随便取（例如上限为 $9999$，目前确定的最高的两位是 $98$，那么后面两位就可以取任意数）。使用 dfs 的写法，在 dfs 的同时动态维护一个数组 $c(|c|=10)$，表示每个数字在前面分别出现了多少次。

首先特判边界情况，对于已经确定所有位的情况（即当前的 $x=\mathrm{len}(n)$，前面的 $0\sim \mathrm{len}(n)-1$ 位全部确定完了），直接暴力算出当前的值并加上。

对于后面不能任意取的情况，直接按照常规数位 DP 方法继续递归下去就行了；对于后面可以可以任意取的情况，此时需要一点组合数学方面的知识。枚举最终出现次数最多的最大数 $i$ 以及其出现次数 $j(\max\{c_i,1\}\le j\le c_i+\mathrm{len}(n)-x)$，接着处理出其他所有数字 $d(d\ne i)$ 最多**新增的**出现次数（即不考虑之前确定的 $c_d$ 次）$r_d=j-c_d-[d>i]$，就变成了以下的问题：有若干种数字，数字 $d$ 最多取 $r_d$ 个，要求取**正好** $s$ 个数字（后面总共要填 $(\mathrm{len}(n)-x)$ 个数字，除去 $i$ 则总共要填 $(\mathrm{len}(n)-x-j+c_i)$ 个），问有多少种不同的数字排列（$\{1,1,2\}$ 和 $\{2,1,1\}$ 算不同的选法，即**可重集排列**）。

想要求解上面这个问题，首先在所有数字 $d$ 选的个数 $w_d$ 都确定的情况下，根据可重集排列数公式，答案就是 $\dfrac{(\mathrm{len}(n)-x)!}{\prod\limits_{d=0}^9w_d!}$（这里对于 $d=i$ 有 $w_d=j-c_i$，否则有 $0\le w_d\le r_d$）。回到原问题，在给定 $w_d(d\ne i)$ 取值范围的情况下，这个问题可以 DP 求解：设 $f_{d,p}$ 表示考虑了前 $d$ 种数字，已经选了 $p$ 个数字的答案（**这里先不乘上 $(\mathrm{len}(n)-x)!$**），有转移 $f_{d,p}\leftarrow f_{d-1,p-w_d}\cdot\frac{1}{w_d!}$，这里的 $w_d$ 需要你在可行的范围内**暴力枚举**。最后**记得将答案乘上 $(\mathrm{len}(n)-x)!$**；你也可以为了方便处理，把需要选 $(j-c_i)$ 个的数字 $i$ 单独处理（这样对于其他 $d\ne i$ 只需要存储一个 $w_d$ 的上界，即 $r_d$），即在 DP 过程中不考虑 $i$ 的情况，只是最后需要将答案乘上 $\dfrac{(\mathrm{len}(n)-x)!}{(j-c_i)!}$ 而不是 $(\mathrm{len}(n)-x)!$。

这道题似乎就做完了。但是有个很恶心的点，就是**前导 $0$**。上面的计算方法可能会导致把带有前导 $0$ 的数的答案算错（即可能把 $m(001)$ 算成 $0$，因为在考虑前导 $0$ 的情况下 $0$ 比 $1$ 多，然而事实上 $m(001)=m(1)=1$）。对于这种情况，只要考虑如果确定的所有位都是 $0$，即使当前这一位和后面的数字是任意取，也要枚举清楚这一位到底要取哪一个数字，然后再递归下去，用上面的方法求解即可。

实测极限数据不超过 $0.4s$，可以通过此题。还是没搞清楚上面是怎么做的，可以参考代码注释。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=1e9+7;
static int f[52],d[52];
int n,r,c[10]; string s;
inline void chadd(int &x,int y){
  if((x+=y)>=p)x-=p;
}
inline int qpow(int a,int b){
  int r=1;
  while(b){
    if(b&1)(r*=a)%=p;
    (a*=a)%=p,b>>=1;
  }
  return r;
}
inline int bf(){
  int x=0,d=0;
  for(int i=0;i<10;i++)
    if(c[i]>=x)x=c[i],d=i;
  return d;
} // 暴力求当前的值
inline int get(vector<int> &c,int s){
  if(s<0)return 0;
  vector<int> f(s+1); f[0]=1;
  for(int i:c)if(i){
    vector<int> g(s+1);
    for(int j=0;j<=s;j++)
      if(f[j])for(int k=0;k<=i&&j+k<=s;k++)
        chadd(g[j+k],f[j]*d[k]%p);
    f=g;
  } // 进行上述的 DP 转移，c[i] 是数字 i 取的个数上限
  return f[s];
}
void dfs(int x,bool l,bool b){
// 分别表示：当前位置，目前确定的是否全是 0，从这一位开始能不能随便取
  if(x==n)return chadd(r,l?0:bf()); // 暴力求
  if(!b){
    if(l){
      for(int i=0;i<10;i++){
        if(i)c[i]++;
        dfs(x+1,!i,false);
        if(i)c[i]--;
      } // 有前导 0，继续递归下去
    }
    else{
      for(int i=1;i<10;i++)
        for(int j=max(c[i],1ll);j<=c[i]+n-x;j++){
          vector<int> w;
          for(int k=0;k<i;k++)
            w.emplace_back(j-c[k]);
          for(int k=i+1;k<10;k++)
            w.emplace_back(j-c[k]-1);
          // 求每个数字取的个数的上限
          bool b=true;
          for(int i:w)if(i<0){b=false; break;}
          if(b)chadd(r,f[n-x]*d[j-c[i]]%p*get(w,n-x-j+c[i])%p*i%p);
        } // 枚举 i,j 进行求解 
    }
    return;
  }
  for(int i=s[x]-48;~i;i--){
    if(i||!l)c[i]++;
    dfs(x+1,l&&!i,i==s[x]-48);
    if(i||!l)c[i]--;
  } // 常规的数位 DP
}
main(){
  ios::sync_with_stdio(false);
  for(int i=f[0]=d[0]=1;i<=51;i++)
    d[i]=qpow(f[i]=f[i-1]*i%p,p-2);
    // 预处理阶乘及其逆元
  int t; cin>>t;
  while(t--){
    cin>>s,n=s.length(),r=0;
    memset(c,0,sizeof(c));
    dfs(0,true,true),cout<<r<<'\n';
  }
  return 0;
}
```

---

## 作者：SDLTF_凌亭风 (赞：5)


来自某不愿意透露姓名的队友。

---
很好的数位 DP 题，非常适合拿来复健。

按照类似数位 DP 的思想，假设数有 $L$ 位，那么考虑 $1\sim L-1$ 位的数，然后 $L$ 位的话考虑一位一位去重合。同时由于讨论 $1\sim L-1$ 位数的时候，首位不能填 $0$，所以枚举首位。这时，我们把 $1\sim n$ 的数划分成了一些区间，这些区间的前缀是给定的，后面的数可以随便乱填，然后逐一对这些区间计算就会方便许多。

然后由于对每个数直接计算众数不可行，所以可以反过来枚举众数和众数的出现次数，然后考虑其他数字出现多少次，再利用排列组合就好了。

假设当前考虑的是已经填写了 $1\sim l-1$ 位，$l\sim r$ 位随便填，在前 $l-1$ 位中数字 $i$ 出现 $o_i$ 次，众数 $i$ 在整个数中出现 $j$ 次。那么在随便填的位置中要填写 $j-o_i$ 个 $i$，剩余位置给别的数字。

同时，$0\sim i-1$ 在整个数中出现次数最多为 $j$，$i+1\sim 9$ 在整个数出现次数最多为 $j-1$。所以如果前 $l-1$ 位直接超了就寄了。否则我们设 $f_j$ 表示还有 $j$ 个能填的位置时候的方案数，然后发现这个东西是一个多重背包，直接枚举填写的个数然后拆成 01 背包，转移如下：
$$
f_j=\sum \binom{j}{k}f_{j-k}
$$
很明显是类似于二项卷积的形式，所以可以拆一下组合数然后重新整理：
$$
\dfrac{f_j}{j!}=\sum \dfrac{1}{k!}\dfrac{f_{j-k}}{(j-k)!}
$$
对这个进行转移很明显相比之前的式子更好写，常数也更小。

最后来考虑合并答案。假设还有 $m$ 个剩余位置（也即求出了 $\dfrac{f_m}{m!}$），由于众数 $i$ 与其他数字在随便填的位数中相互独立，所以答案为
$$
f_m\binom{r-l+1}{m}=\frac{f_m}{m!}\cdot\frac{(r-l+1)!}{(r-l+1-m)!}=\frac{f_m}{m!}\cdot\frac{(r-l+1)!}{(j-o_i)!}
$$
这样就做完了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll MAXN=151,MOD=1e9+7;
ll test,len,res,rem,mx,cur;
ll dg[MAXN],fact[MAXN],finv[MAXN],occ[MAXN],f[MAXN];
char c[MAXN];
inline ll read()
{
	register ll num=0,neg=1;
	register char ch=getchar();
	while(!isdigit(ch)&&ch!='-')
	{
		ch=getchar();
	}
	if(ch=='-')
	{
		neg=-1;
		ch=getchar();
	}
	while(isdigit(ch))
	{
		num=(num<<3)+(num<<1)+(ch-'0');
		ch=getchar();		
	}
	return num*neg;
}
inline ll qpow(ll base,ll exponent)
{
    ll res=1;
    while(exponent)
    {
        if(exponent&1)
        {
            res=res*base%MOD;
        }
        base=base*base%MOD,exponent>>=1;
    }
    return res;
}
inline void setup(ll cnt)
{
	fact[0]=fact[1]=finv[0]=1;
	for(register int i=2;i<=cnt;i++)
	{
		fact[i]=fact[i-1]*i%MOD;
	}
	finv[cnt]=qpow(fact[cnt],MOD-2);
	for(register int i=cnt-1;i;i--)
	{
		finv[i]=finv[i+1]*(i+1)%MOD;
	}
}
inline ll dp(ll rem,ll oc,ll mo)
{
	memset(f,0,sizeof(f)),f[0]=1;
	for(register int i=0;i<=9;i++)
	{
		if(i==mo)
		{
			continue;
		}
		if((mx=oc-(i>mo)-occ[i])<0)
		{
			return 0;
		}
		for(register int j=rem;j;j--)
		{
			for(register int k=1;k<=mx&&k<=j;k++)
			{
				f[j]=(f[j]+f[j-k]*finv[k])%MOD;
			}
		}
	}
	return f[rem];
}
inline ll calc(ll l,ll r)
{
	ll res=0;
	for(register int i=0;i<10;i++)
	{
		occ[i]=0;
	}
	for(register int i=1;i<=l-1;i++)
	{
		occ[dg[i]]++;
	}
	for(register int i=1;i<=9;i++)
	{
		for(register int j=occ[i];j<=occ[i]+r-l+1;j++)
		{
			rem=r-l+1-(j-occ[i]);
			cur=dp(rem,j,i)*fact[r-l+1]%MOD*finv[j-occ[i]]%MOD;
			res=(res+i*cur)%MOD;
		} 
	}
	return res;
}
inline void solve()
{
	scanf("%s",c+1),len=strlen(c+1),res=0;
	for(register int i=1;i<len;i++)
	{
		for(register int j=1;j<=9;j++)
		{
			dg[1]=j,res=(res+calc(2,i))%MOD;
		}
	}
	for(register int i=1;i<=len;i++)
	{
		dg[i]=0;
		for(register int j=(i==1);j<=c[i]-'1';j++)
		{
			dg[i]=j,res=(res+calc(i+1,len))%MOD;
		}
		dg[i]=c[i]-'0';
	}
	res=(res+calc(len+1,len))%MOD,printf("%lld\n",res);
}
int main()
{
	setup(100),test=read();
	for(register int i=1;i<=test;i++)
	{
		solve();
	}
}
```

---

## 作者：small_john (赞：2)

## 思路

定义 $a_i$ 为 $n$ 在十进制中从高到低的第 $i$ 位，$n$ 一共有 $cnt$ 位，$b_i$ 为最终数在十进制中从高到低的第 $i$ 位。

首先类似数位 DP，枚举有 $x$ 位是填满的（对于每个 $i\in[1,x]$，满足 $b_i=a_i$），然后第 $x+1$ 位满足 $b_i<a_i$，那么 $x+2\sim cnt$ 位是可以随便填的。对于有前导零的情况，枚举前 $x$ 位是 $0$，第 $x+1$ 位必须填一个正整数，$x+2\sim cnt$ 位也是可以随便填的。我们设已经确定下来的有效数位中 $i$ 的出现次数为 $add_i$，可以随便填的数位个数为 $len$。

这时我们枚举出现次数最多的数是 $m$，其出现次数位 $c$，不难发现，对于 $x\neq m$，在随便填的位置中最多出现 $lim_x=c-add_x-[x>c]$ 次，其实这很像多重背包。设 $f_{i,j}$ 表示前 $i$ 个数（不包括 $m$），一共用了 $j$ 个数的方案数，则有转移：

$$f_{i,j}=\sum\limits_{k=0}^{k\le lim_i} f_{i-1,j-k}\times \binom{j}{k}$$

而最终对答案的贡献为 $f_{9,len-(c-add_m)}\times\binom{len}{c-add_m}\times c$。按上述方法转移即可。

最终复杂度为 $O(cnt^4V^3)$，其中 $V$ 为数码的个数，看似很大，但是常数极小，可以通过。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9+7,N = 100;
int a[N],C[N][N],f[N],cnt,add[N],ans;
string s;
inline void work(int len)
{
	for(int c = 0;c<=9;c++) for(int m = add[c];m<=add[c]+len;m++)
	{
		int tot = len-(m-add[c]);
		for(int i = 0;i<=tot;i++) f[i] = 0;
		f[0] = 1;
		bool fl = 1;
		for(int i = 0;i<=9;i++)
		{
			if(i==c) continue;
			int lim = m-add[i];
			if(i>c) lim--;
			if(lim<0)
			{
				fl = 0;
				break;
			}
			for(int j = tot;j;j--)
				for(int k = 1;k<=min(lim,k);k++)
					(f[j]+=f[j-k]*C[j][k])%=mod;
		}
		if(fl) (ans+=f[tot]*c*C[len][m-add[c]])%=mod;
	}
}
inline void solve()
{
	cin>>s,cnt = s.size();
	for(int i = 1;i<=cnt;i++)
		a[i] = s[i-1]-'0';
	for(int i = 0;i<=9;i++) add[i] = 0;
	for(int i = 1;i<=cnt;i++)
		add[a[i]]++;
	ans = 9;
	for(int i = 8;~i;i--)
		if(add[i]>add[ans]) ans = i;
	for(int i = 0;i<=9;i++) add[i] = 0;
	for(int i = 1;i<cnt;i++)
	{
		for(int j = 1;j<=9;j++)
			add[j]++,work(i-1),add[j]--;
	}
	for(int i = 1;i<=cnt;i++)
	{
		int mn = 1;
		if(i!=1) mn = 0; 
		for(int j = mn;j<a[i];j++)
			add[j]++,work(cnt-i),add[j]--;
		add[a[i]]++;
	}
	cout<<ans<<'\n';
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	C[0][0] = 1;
	for(int i = 1;i<N;i++)
	{
		C[i][0] = 1;
		for(int j = 1;j<=i;j++)
			C[i][j] = (C[i-1][j]+C[i-1][j-1])%mod;
	}
	int T;cin>>T;
	while(T--) solve(); 
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18375518)

### 思路：

定义 $F(l,r)$ 表示若已经确定了 $[1,l-1]$ 的数，且 $[l,r]$ 没有限制的贡献数。

设 $n$ 的长度为 $len$，考虑先求出 $[1,i](i \le len-1)$ 的贡献（是没有限制的），那么每次枚举第 $1$ 位数字 $a_1 \in [1,9]$，算上 $F(2,i)$ 的贡献即可。

则该情况贡献和为：

$$\sum_{i=1}^{len-1} \sum_{j=1}^9 F(2,i)$$ 

现在来考虑长度为 $len$ 的数的贡献的和，也考虑枚举第 $i$ 位的数字 $j$，那么若想要使得 $[i+1,len]$ 没有限制，则至少要满足 $i \in [0,n_i-1]$，为了使得后面不算重，故我们要每次算完 $[i+1,len]$ 的贡献和后，需要令 $a_i = n_i$。

则该情况贡献和为：

$$\sum_{i=1}^{len} \sum_{j=[i=1]}^{n_i-1} F(i+1,len)$$

注意最后要单独计算 $n$ 本身的贡献。

现在我们来考虑确定 $a_{1,\cdots,l-1}$ 的情况下如何计算 $F(l,r)$。

考虑枚举众数最大值 $i$ 和众数的出现次数 $j$，设 $p_i$ 表示 $i$ 的出现次数，那么在后面 $[l,r]$ 内 $i$ 至少还需要出现 $j-p_i$ 次；同时为了确保 $i$ 是众数，需要满足 $[0,i-1]$ 的出现次数 $\le j$，且 $[i+1,9]$ 的出现次数 $\le j-1$；即现在我们要求将 $r-l+1-(j-p_i)$ 个位置分配给除了 $i$ 以外的 $9$ 个数的且满足限制的方案数。

设我们枚举的众数为 $k$，众数出现次数为 $mx$，使用动态规划算法，定义 $f_i$ 表示可以分配 $i$ 个位置的方案数，考虑枚举选的数 $j$ 和分配给 $j$ 的数量 $k$，背包形转移：

$$f_i = \sum_{j=0}^9 [j \ne k] \sum_{k=0}^{\min(mx,p_j-[i>k])} \binom{i}{k} f_{i-k}$$

可以先预处理阶乘和逆元来计算组合数。

**注意要先枚举 $j$。**

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=55,mod=1e9+7;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,t,g,ans,sum;
ll a[N],h[N],p[N],f[N],fac[N],inv[N];
char s[N];
ll qpow(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1ll)
          ans=(ans*a)%mod;
        a=(a*a)%mod;
        b>>=1ll;
    }
    return ans;
}
void init(){
    fac[0]=fac[1]=1;
    For(i,2,N-1)
      fac[i]=(fac[i-1]*i)%mod;
    inv[N-1]=qpow(fac[N-1],mod-2);
    _For(i,0,N-2)
      inv[i]=inv[i+1]*(i+1)%mod;
}
ll C(ll n,ll m){
    if(m>n||m<0)
      return 0;
    if(!m||n==m)
      return 1;
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
ll get(ll n,ll k,ll mx){
	memset(f,0,sizeof(f));
    f[0]=1;
	For(i,0,9){
		if(i==k)
		  continue;
        t=mx-(i>k)-p[i];
		if(t<0)
		  return 0;
        _For(j,1,n)
          For(k,1,min((int)t,j))
			f[j]=(f[j]+f[j-k]*C(j,k)%mod)%mod;
	}
	return f[n];
}
ll get(ll l,ll r){
    sum=0;
    For(i,0,9)
      p[i]=0;
    For(i,1,l-1)
      p[a[i]]++;
    For(i,1,9)
      For(j,p[i],p[i]+r-l+1)
        sum=(sum+get(r-l+1-j+p[i],i,j)*C(r-l+1,r-l+1-j+p[i])%mod*i%mod)%mod;
    return sum;
}
void solve(){
    ans=0;
    scanf("%s",s+1);
    n=strlen(s+1);
    For(i,1,n)
      h[i]=s[i]-'0';
    For(i,1,n-1){
        For(j,1,9){
            a[1]=j;
            ans=(ans+get(2,i))%mod;
        }
    }
    For(i,1,n){
        For(j,(i==1),h[i]-1){
            a[i]=j;
            ans=(ans+get(i+1,n));
        }
        a[i]=h[i];
    }
    write((ans+get(n+1,n))%mod);
    putchar('\n');
}
bool End;
int main(){
    init();
    T=read();
    while(T--)
      solve();
	//cerr<<'\n'<<abs(&Begin-&End)/1048576<<"MB";
	return 0;
}
```

---

