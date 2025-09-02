# [PA 2020] Liczba Potyczkowa

## 题目描述

**题目译自 [PA 2020](https://sio2.mimuw.edu.pl/c/pa-2020-1/dashboard/) Runda próbna [Liczba Potyczkowa](https://sio2.mimuw.edu.pl/c/pa-2020-1/p/lic/)。**

Bajtek 在数学史课上了到解了一位俄罗斯数学家弗拉基米尔·波季奇科夫（Vladimir Potyczkow）。这位科学家以对数字的研究而闻名，为了纪念他，今天我们将这些数称为 **Potyczkow 数**：是一个正整数，并且可以用其十进制表示中出现过的每个数字整除。特别地，这意味着十进制表示中不能有零。例如 $48$、$1$ 和 $112$ 是 Potyczkow 数，而 $23$、$10$ 和 $121$ 不是。Bajtek 想知道在 $[l, r]$ 范围内有多少这样的数，请帮助他数一数！

## 说明/提示

#### 样例 1 解释

不超过 $100$ 的 Potyczkow 数有 $1, 2, 3, 4, 5, 6, 7, 8, 9,11,12, 15, 22, 24, 33, 36, 44, 48, 55, 66, 77, 88$ 和 $99$。

------------

#### 数据范围

**本题采用捆绑测试**

对于部分子任务，满足 $r-l\le 10^6$。

对于 $100\%$ 的数据，保证 $1\le l\le r\le 10^{18}$。

## 样例 #1

### 输入

```
1 100```

### 输出

```
23```

# 题解

## 作者：L_zaa_L (赞：3)

数位 DP 题。

数位 DP 感觉都是一个样子的，然后我最喜欢用的是记忆化搜索（写得方便）。

我们需要记录的东西是他所有出现数字的最小公倍数，然后以及这个数的值，和有没有顶到上界。但是由于要有原数要整除最小公倍数，所以我们不能出现除前导 $0$ 以外的 $0$。而且我们发现我们记录的这个数是不好记忆化搜索的（会超时），由于有个东西就是 $x\bmod y=x\bmod y\bmod z(y\mid z)$，所以我们取模所有非零阿拉伯数字的最小公倍数 $2520$，然后再判断能不能整除，这样子就可以记忆化搜索了。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ls(x) ((x)*2)
#define rs(x) ((x)*2+1)
#define Debug(...) fprintf(stderr, __VA_ARGS__)
#define For(i,a,b) for(int i=a,i##end=b;i<=i##end;i++)
#define Rof(i,a,b) for(int i=a,i##end=b;i>=i##end;i--)
#define rep(i,  b) for(int i=1,i##end=b;i<=i##end;i++)
using namespace std;
const int N=1e6+5,base=999983,Mod=998244353;
//char buf[(1<<21)+5],*p1,*p2;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline void chmx(int &x,int y){(x<y)&&(x=y);}
inline void chmn(int &x,int y){(x>y)&&(x=y);}
inline void Add(int &x,int y){(x=x+y+Mod)%=Mod;}
inline int read(){
	int f=0,x=0;
	char ch=getchar();
	while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return f?-x:x;
}
void print(int n){
    if(n<0){
        putchar('-');
        n*=-1;
    }
    if(n>9) print(n/10);
    putchar(n%10+'0');
}
int a[N],tot;
map<tuple<int,int,int>,int>mp;
int  Gcd[3005];
int dfs(int x,int op,bool flag,int lcm,int yu){
	if(!op&&!flag&&mp.count(make_tuple(x,Gcd[lcm],yu))) return mp[make_tuple(x,Gcd[lcm],yu)];
	if(x==0){
//		if(yu%Gcd[lcm]==0) cout<<yu<<endl;
		return (yu%Gcd[lcm]==0);
	}
	int res=0;
	For(j,0,9){
		if(op&&j>a[x]) continue;
		if(!flag&&j==0) continue;
		res+=dfs(x-1,op&(j==a[x]),flag&(j==0),(j==0)?0:lcm|(1<<(j-1)),(yu*10+j)%2520);
	}
	if(!op&&!flag)mp[make_tuple(x,Gcd[lcm],yu)]=res;
	return res;
}
inline int calc(int x){
	int p=x;
	tot=0;
	mp.clear();
	while(p){
		a[++tot]=p%10;
		p/=10;
	}
	return dfs(tot,1,1,0,0);
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	// ios::sync_with_stdio(false);
	// cin.tie(0); cout.tie(0);
	int l=read(),r=read();
	For(i,0,1023){
		Gcd[i]=1;
		For(j,1,9){
			if(i&(1<<(j-1))) Gcd[i]=Gcd[i]*j/__gcd(Gcd[i],j);
		}
	}
	printf("%lld\n",calc(r)-calc(l-1));
#ifdef LOCAL
    Debug("\nMy Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
	return 0;
}
```

---

## 作者：Elairin176 (赞：3)

[传送门](https://www.luogu.com.cn/problem/P9092)   
在未 AC 记录里找到的，甚至还是多倍经验。    
## 解法
一眼数位 dp。   
首先，如果说这个数字满足的题面给出的条件，那么它一定是 $2$ 到 $9$ 的最小公倍数的因数或倍数。所以，我们可以得出以下一个结论：    
- 如果 $x$ 是一个满足要求的数字，那么 $x\bmod p$ 也是。$p$ 为 $2$ 到 $9$ 的最小公倍数，为 $2520$。   

故我们可以在 dfs 过程中记录以下几个值：   
- 原数模 $p$ 的值。   
- 所有出现过的数字的最小公倍数。   
- 是否在前导 $0$ 部分。   

之后套上板子就可以了。   
CODE:   
```cpp
//Code by __dest__ruct__or__(uid=592238)
#include <iostream>
#include <cstring>
using namespace std;
#define ll long long
int t,k,a[25],b[114514],tot;
ll l,r,dp[25][2525][514];
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a*b/gcd(a,b);}
const int p=2520;
ll dfs(int pos,int x,int l,bool f,bool f2){
	if(pos==0)return x%l==0;
	if(f==0&&f2==0&&dp[pos][x][b[l]]!=-1)return dp[pos][x][b[l]];
	int mx=(f?a[pos]:9);
	ll ans=0;
	for(int i=(f2?0:1);i<=mx;i++)ans+=dfs(pos-1,((x<<3)+(x<<1)+i)%p,(i==0?l:(lcm(l,i))),f&(i==a[pos]),f2&(i==0));
	if(f||f2)return ans;
	return dp[pos][x][b[l]]=ans;
}
ll solve(ll x){
	k=0;
	while(x)a[++k]=x%10,x/=10;
	return dfs(k,0,1,1,1);
}
int main(void){
	memset(dp,-1,sizeof(dp));
	for(int i=1;i<=p;i++){
		if(p%i!=0){
			continue;
		}
		b[i]=++tot;
	}
	t=1;
	while(t--){
		scanf("%lld%lld",&l,&r);
		printf("%lld\n",solve(r)-solve(l-1));
	}
}
```
说句闲话：这题代码我是从一道类似的 SPOJ 题改过来的。那道题甚至卡码量，所以我把我缺省源给删了。

---

## 作者：Echoternity (赞：2)

显然的数位 $\mathrm{dp}$。

对于每一位，肯定都是 $1\sim 9$，所以一定只有 $9$ 种除数，可以考虑一个状态压缩的过程，记录当前状态下某一个数是否存在过，然后在最后进行判定，但是这样下来的空间复杂度为 $\mathcal O(9!2^{10}\ln n)$，显然是过不了的，所以考虑一点优化。

如果对于每一个除数都记录一个其模数显然是赘余的，因为如果我们已经知道的 $\bmod 9$ 下的余数，那么 $\bmod 3$ 的余数显然是也知道了的，同理，$2,4,8$ 也存在这样的关系。所以，实际上我们可以仅仅通过记录 $\bmod \operatorname{lcm}(1\sim 9)=2520$ 的余数即可知道所有的模数。这样下来，空间复杂度可以优化到 $\mathcal O(2520\times 2^8\ln n)$，因为 $1$ 是没有必要状压的。

当然，因为 $0$ 只能出现在前导部分，所以还需要加上 $limit$ 和判 $0$ 的 $\mathcal O(4)$ 部分。（常数好像不能写进时间复杂度分析里，但我也不知道怎么写了啊QAQ）

唯一那篇题解的方法好冗长啊，这里给出简短的记忆化搜索写法：

``` c++
const int MAXN=19,MAXS=1<<8|10,MAXNUM=2520;
const int Mod=2520;
ll Dp[MAXN][MAXS][MAXNUM][2][2];
int Nums[20],Len;
ll ql,qr;
//pos,state(2~9),mod 7,8,9
int gcd(int a,int b)
{ return !b?a:gcd(b,a%b); }
inline int lcm(int a,int b)
{ return a*b/gcd(a,b); }
ll dfs(int pos,int state,int mod,bool limit,bool _0)
{
	if(!~pos)
	{
		int _lc=1;
		for(int i=2;i<=9;++i) if(state>>(i-2)&1) _lc=lcm(_lc,i);
		return mod%_lc==0;
	}
	if(~Dp[pos][state][mod][limit][_0]) return Dp[pos][state][mod][limit][_0];
	ll ret=0;int st=_0?1:0,num=limit?Nums[pos]:9;
	for(int i=st;i<=num;++i)
	{
		int nxd=(mod*10+i)%Mod,_st=state;
		if(i>1) _st|=1<<(i-2);
		ret+=dfs(pos-1,_st,nxd,limit&(i==num),_0|(i>0));
	}
	return Dp[pos][state][mod][limit][_0]=ret;
}
inline ll solve(ll x)
{
	if(!x) return 0;
	std::memset(Dp,-1,sizeof(Dp));
	ll ret=0;
	for(Len=0;x;x/=10) Nums[Len++]=x%10;
	ret=dfs(Len-1,0,0,1,0);
	return ret;
}
int main()
{
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	read(ql,qr);
	int delta=(ql==1);
	write(solve(qr)-solve(ql-1)-delta);
	return 0;
}
```

---

## 作者：ForgotMe (赞：2)

显然有一个复杂度的数位 dp 暴力，直接 $2^9$ 保存每个数字是否出现过，然后保存数 $x \bmod i(2\le i\le 9)$ 的值，不仅时间爆炸，空间也爆炸。

考虑如何压缩状态，只要状态压下去了，那么这个题也就做完了。

首先考虑如何压缩保存取模后的信息。思考一下，如果知道 $x\bmod 4$ 的值，那是不是就知道了 $x\bmod 2$ 的值，同理，如果知道了 $x\bmod 8$ 的值，就可以知道 $x\bmod 4$ 或者 $x\bmod 2$ 的值，于是判断 $2|x,4|x,8|x$ 只需要保存 $x\bmod 8$ 的值就行。那么按照上面这个想法，把 $3,9$ 分成一组，只保存 $x\bmod 9$ 的信息。那么剩下的暴力保存即可？其实还可以优化一下，$6=2\times 3$，判断一个数是否满足 $6|x$，只需要判断 $2|x$，$3|x$ 即可，于是不需要保存 $x\bmod 6$ 的值。$5|x$ 就只需要判断最低位是不是 $5$ 就行，不需保存 $x\bmod 5$ 的值。那么至此只需要保存 $x\bmod 7$，$x\bmod 8$，$x\bmod 9$ 的值。

然后来考虑如何压缩每个数字是否出现过的信息，模仿上面的想法，把 $2,4,8$ 分成一组，$3,9$ 分成一组，$5,6,7$ 各自分成一组，为什么这么分呢？因为如果 $4$ 出现了，那么 $2$ 就算出现了也就没用了，因为 $4|x$ 这个条件满足了那么显然满足 $2|x$，于是这里就被压缩到了 $4\times 3\times 2^3=96$。

那么接下来就很简单了，从高位到低位或者从低位到高位做数位 dp 就行。

作者实现的是从低到高的写法，复杂度 $\mathcal{O}(L\times 96\times 7\times 8\times 9\times 9)=\mathcal{O}(435456L)$。看上去很大，实际上根本跑不满。

极限数据 120ms，去 LOJ 看了看，发现 std 跑得非常慢，总用时 33000ms，这个做法总用时只有 5300ms。

```cpp
#include <cstdio>
#include <map>
#include <iostream>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#include <queue>
#include <stack>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
using namespace std;
#define LL long long
#define pp pair<int,int>
#define mp make_pair 
#define ull unsigned long long
namespace IO{
    const int sz=1<<22;
    char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
    inline char gc(){
		return getchar();
   //     return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
    }
    template<class T> void gi(T& x){
        x=0; int f=1;char c=gc();
        if(c=='-')f=-1;
        for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
        for(;c>='0'&&c<='9';c=gc())
            x=x*10+(c-'0');
        x=x*f;
    }
    inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
    inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
    template<class T> void pi(T x,char c='\n'){
        if(x<0)pc('-'),x=-x;
        if(x==0) pc('0'); int t=0;
        for(;x;x/=10) p[++t]=x%10+'0';
        for(;t;--t) pc(p[t]); pc(c);
    }
    struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
using IO::gc;
const int mod=998244353;
const int inv2=(mod+1)>>1;
inline int add(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
	return x-y<0?x-y+mod:x-y;
}
inline int qkpow(int a,int b){
	int ans=1,base=a;
	while(b){
		if(b&1)ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int fac[1000005],inv[1000005],Invn[1000005];
inline int binom(int n,LL m){
	if(n<m||m<0)return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int N){
	fac[0]=1;
	for(int i=1;i<=N;i++)fac[i]=1ll*fac[i-1]*i%mod; 
	inv[0]=1;
	inv[N]=qkpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
	Invn[0]=Invn[1]=1;
	for(int i=2;i<=N;i++)Invn[i]=1ll*inv[i]*fac[i-1]%mod;
}      
int trans[100][10],a[19];
LL l,r,dp[2][19][100][7][8][9][2];
map<string,int>H;
string sta[100];
int cnt;
inline int getid(string S){
	if(!H[S]){
		H[S]=++cnt;
		sta[cnt]=S;
	}
	return H[S];
}
inline void dfs(int x){
	if(x==6){
		string S;
		for(int i=1;i<=5;i++)S+=(a[i]+'0');
		trans[getid(S)][1]=getid(S);
		for(int x=2;x<=9;x++){
			int num=0,pos=0;
			if(x==2)num=1,pos=1;
			else if(x==4)num=2,pos=1;
			else if(x==8)num=3,pos=1;
			else if(x==3)num=1,pos=2;
			else if(x==9)num=2,pos=2;
			else num=1,pos=x-2;
			string S2;
			for(int j=1;j<=5;j++){
				if(j==pos)S2+=(max(a[j],num)+'0');
				else S2+=(a[j]+'0');
			}
			trans[getid(S)][x]=getid(S2);
		}
		return ;
	}
	if(x==1){
		for(int i=0;i<=3;i++){
			a[x]=i;
			dfs(x+1);
		}
	}else if(x==2){
		for(int i=0;i<=2;i++){
			a[x]=i;
			dfs(x+1);
		}
	}else{
		for(int i=0;i<=1;i++){
			a[x]=i;
			dfs(x+1);
		}
	}
}
inline LL solve(LL n){
	if(!n)return 0;
	LL x=n;
	int len=0;
	while(x){
		a[++len]=x%10;
		x/=10;
	}
	memset(dp,0,sizeof dp);
	for(int x=1;x<=9;x++)
		dp[(x==5)][1][trans[1][x]][x%7][x%8][x%9][(x<=a[1])]=1;
	LL pw=10;
	for(int i=1;i<len;i++){
		for(int l1=0;l1<2;l1++){
			for(int j=1;j<=96;j++){
				for(int p1=0;p1<7;p1++){
					for(int p2=0;p2<8;p2++){
						for(int p3=0;p3<9;p3++){
							for(int t=0;t<2;t++){
								if(dp[l1][i][j][p1][p2][p3][t]){
									LL v=dp[l1][i][j][p1][p2][p3][t];
									for(int p=1;p<=9;p++){
										int nt=(p<a[i+1]||(t&&p==a[i+1]));
										int np1=((pw*p)%7+p1)%7,np2=((pw*p)%8+p2)%8,np3=((pw*p)%9+p3)%9;
										dp[l1][i+1][trans[j][p]][np1][np2][np3][nt]+=v;
									}
								}
							}
						}
					}
				}
			}
		}
		pw*=10ll;
	}
	LL ans=0;
	for(int l1=0;l1<2;l1++){
		for(int p1=0;p1<7;p1++){
			for(int p2=0;p2<8;p2++){
				for(int p3=0;p3<9;p3++){
					for(int j=1;j<=96;j++){
						LL v=0;
						for(int i=1;i<=len;i++){
							v+=dp[l1][i][j][p1][p2][p3][1];
							if(i!=len)v+=dp[l1][i][j][p1][p2][p3][0];
						}
						if(v){
							bool f=1;
							for(int p=0;p<5;p++){
								int num=sta[j][p]-'0';
								if(!num)continue;
								if(p==0){
									if(num==1&&p2%2!=0){
										f=0;
										break;
									}
									if(num==2&&p2%4!=0){
										f=0;
										break;
									}
									if(num==3&&p2%8!=0){
										f=0;
										break;
									}
								}
								if(p==1){
									if(num==1&&p3%3!=0){
										f=0;
										break;
									}
									if(num==2&&p3%9!=0){
										f=0;
										break;
									}
								}
								if(p==2&&!l1){
									f=0;
									break;
								}
								if(p==3&&((p2%2!=0)||(p3%3!=0))){
									f=0;
									break;
								}
								if(p==4&&p1){
									f=0;
									break;
								}
							}
							if(f)ans+=v;
						}
					}
				}
			}
		}
	}
	return ans;
}
signed main(){
	gi(l),gi(r);
	dfs(1);
	pi(solve(r)-solve(l-1),'\n');
	return 0;
}
```

---

## 作者：__O_v_O__ (赞：1)

数位 dp。

显然有一个数位 dp 暴力，直接 $2^9$ 保存每个数字是否出现过，然后保存 $x$ 模 $i(2\le i\le 9)$ 的值。不仅时间爆炸，空间也爆炸。

考虑这个状态能不能压缩的更简洁一些。注意到 $2∼9$ 中所有数的最小公倍数是 $2520$，那么我们不需要分别保存 $x$ 模 $i(2\le i\le 9)$ 的值，直接保存这个数模 $2520$ 的值、以及所有出现过的数字的最小公倍数 $p$ 即可。

故我们可以在 dfs 过程中记录以下几个值：

- 当前填的位置。

- 现在填了的这些位置模 $2520$ 的值。

- 现在填了的这些数字的最小公倍数。

- 是否存在前导 $0$。

- 是否顶上界。

记忆化搜索即可。

常数优化方面，可以用一个数组给 $2520$ 的 $48$ 个因数编一个号，dfs 时存储编号，可以节省空间。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mo=2520;
int t,l,r,id[5001],to;
int f[21][2601][51],a[51];
int lc(int x,int y){
	return x*y/__gcd(x,y);
}
int dfs(int po,int nu,int p,int li,int z){
	if(!po)return (nu%p==0);
	if(!li&&!z&&f[po][nu][id[p]]!=-1)
		return f[po][nu][id[p]];
	int mx=li?a[po]:9,an=0;
	for(int i=(z?0:1);i<=mx;i++)
		an+=dfs(po-1,(nu*10+i)%mo,i?lc(p
			,i):p,li&&(i==a[po]),z&&(i==0));
	if(!li&&!z)f[po][nu][id[p]]=an;
	return an;
}
int sl(int x){
	int t=0;
	while(x)a[++t]=x%10,x/=10;
	return dfs(t,0,1,1,1);
}
signed main(){
	ios::sync_with_stdio(0);
	memset(f,-1,sizeof f);
	for(int i=1;i<=mo;i++)
		if(!(mo%i))id[i]=(++to);
	cin>>l>>r;
	cout<<sl(r)-sl(l-1);
	return 0;
}
```

---

