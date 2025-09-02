# [PA 2025] 乘数 / Mnożenie cyfr

## 题目背景

PA 2025 R3B.


## 题目描述



对于非负整数 $n$，定义函数 $f(n)$：

- 令 $n$ 的十进制表示为 $\overline{a_1a_2\ldots a_k}$。
- 则 $f(n)=a_1a_2\cdots a_k$。

换言之，$f(n)$ 就是将 $n$ 十进制表示下的数位相乘得到的结果。

对于非负整数 $x$，按如下程序执行操作：

1. 若 $x\le 9$，终止操作；
2. 否则令 $x\gets f(x)$，回到 1。

> **举例**
>
> 1. $57\to 5\times 7=35\to 3\times 5=15\to 1\times 5=5$。
> 2. $255\to 2\times 5\times 5=50\to 5\times 0=0$。

可以证明，对于任意非负整数 $x$，这个操作都一定会终止。

$T$ 组数据，每组数据给定 $n$，对于 $i=0,1,\ldots,9$，求出：

- 有多少个 $1\le j\le n$ 满足将 $j$ 操作后最终会得到 $i$。

## 说明/提示

- $1\le T\le 10^3$；
- $1\le n\le 10^{18}$。

## 样例 #1

### 输入

```
5
10 56 57 123 1```

### 输出

```
1 1 1 1 1 1 1 1 1 1
11 2 7 3 6 5 8 2 9 3
11 2 7 3 6 6 8 2 9 3
36 3 11 4 12 8 16 4 24 5
0 1 0 0 0 0 0 0 0 0```

# 题解

## 作者：FFTotoro (赞：3)

对于这种题目，考虑函数 $f(x)$ 的性质：

- 乘法具有交换律，将 $x$ 的所有数位重排得到 $y$，则 $f(x)=f(y)$；
- $x$ 的数位中若出现 $0$ 则答案必然为 $0$。

前一条性质是解决本题的关键，后一条性质可以简化做法：接下来的讨论中**不考虑** $f(x)=0$ 的情况，最后用 $n$ 减去其他情况的数量即可得到 $f(x)=0$ 的答案。

考虑针对前一条性质我们能做什么：定义两个数“处于同一个等价类”，当且仅当其中一个可以通过数位重排得到另一个数；则只需对于每一个等价类找一个代表元，这里选择其中字典序最小的：事实上等价类的个数并不多（经过测试，在题目给定的数据范围下共有 $48367$ 个），可以考虑使用拆分数相关知识进行证明（因为字典序最小，所以数位上的值是递增的），或直接打个表也可以得出该性质。

预处理出所有的代表元：只需在原有代表元的基础上，对于某个代表元，在末尾添加一个比原来的末尾更大的数位，即可生成一个新的代表元。

---

接下来的部分需要一个前置知识：[多重集排列数](https://oiwiki.org/math/combinatorics/combination/#%E5%A4%9A%E9%87%8D%E9%9B%86%E7%9A%84%E6%8E%92%E5%88%97%E6%95%B0--%E5%A4%9A%E9%87%8D%E7%BB%84%E5%90%88%E6%95%B0)。设多重集中每种元素的出现次数为 $n_1,n_2,\ldots,n_k$，集合大小为 $n$（满足 $n=\sum\limits_{i=1}^kn_i$），那么其全排列个数为 $\dfrac{n!}{\prod_{i=1}^kn_i!}$。

暴力枚举每个等价类，现在只需对于一个 $n$，求出某个等价类里面有多少个数 $\le n$。

记一个数的位数为 $\mathrm{len}(n)$。显然一个等价类内所有元素位数相等，于是对于代表元 $x$ 分情况讨论：

- $\mathrm{len}(x)>\mathrm{len}(n)$：答案为 $0$；
- $\mathrm{len}(x)<\mathrm{len}(n)$：$x$ 的所有数位重排方案均 $\le n$，答案为 $x$ 的数位构成的多重集排列数；
- $\mathrm{len}(x)=\mathrm{len}(n)$：进行数位 DP，从高位到低位考虑，每次取出 $x$ 中的一个数位填写：
  - 当前位上填的数字小于 $n$ 该位的数字：后面的数可以随便填，答案为余下的数位构成的多重集排列数；
  - 当前位上填的数字等于 $n$ 该位的数字：将该位忽略，递归对于更低的位解决原问题。

注意特判 $x=n$ 的情况。实现时为了提升效率，可以直接针对每一个代表元，支持加入 / 删除一个数位时快速计算排列数。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
static int fac[19];
inline int f(int x){
  while(x>9){
    int y=1;
    while(x)y*=x%10,x/=10;
    x=y;
  }
  return x;
} // 题目所述的 f(x)
struct number{
  int d,l,r; vector<int> c;
  number(int x):l(0),d(f(x)),c(10){
    while(x)l++,c[x%10]++,x/=10;
    r=fac[l]; for(int i:c)r/=fac[i];
  }
  inline void add(int x){r*=++l,r/=++c[x];}
  inline void del(int x){r*=c[x]--,r/=l--;}
};
// 结构体，维护一个等价类
// c 表示每个数字的出现次数
// l 表示元素的位数
// r 表示实时维护的当前数位构成的多重集排列数
main(){
  ios::sync_with_stdio(false);
  for(int i=fac[0]=1;i<=18;i++)
    fac[i]=fac[i-1]*i;
  vector<pair<int,int> > c;
  vector<number> s;
  for(int i=1;i<10;i++)
    c.emplace_back(i,i),s.emplace_back(i);
  for(int l=2;l<=18;l++){
    vector<pair<int,int> > d;
    for(auto [n,p]:c)
      for(int j=n%10;j<10;j++){
        int m=n*10+j;
        d.emplace_back(m,p*j);
        if(f(m))s.emplace_back(m);
      }
    c=d;
  } // 预处理所有代表元
  int t; cin>>t;
  while(t--){
    int n; cin>>n;
    string N=to_string(n);
    vector<int> c(10);
    for(number d:s){
      if(d.l>N.length())break;
      if(d.l<N.length()){c[d.d]+=d.r; continue;}
      bool f=true; // 是否可能出现 x=n
      for(int i=0;i<N.length();i++){
        if(N[i]==48){f=false; break;}
        for(int j=1;j<N[i]-48;j++)
          if(d.c[j])d.del(j),c[d.d]+=d.r,d.add(j);
        if(d.c[N[i]-48])d.del(N[i]-48);
        else{f=false; break;}
      } // 数位 DP 过程
      if(f)c[d.d]++;
    }
    c[0]=n-accumulate(c.begin(),c.end(),0ll);
    // 对于 0 的答案单独处理
    for(int i:c)cout<<i<<' ';
    cout<<'\n';
  }
  return 0;
}
```

---

## 作者：shinzanmono (赞：1)

显然可以发现，对于 $x=10,\ldots,n$，如果从 $f(x)$ 向 $x$ 连边的话，会得到一个外向森林，$ans_x$ 即为 $x$ 的子树大小。

显然叶子结点的个数比较多，那么我们不妨对每个非叶子结点的子节点计数，显然，除了 $1\sim 9$ 都可以被找到，那么我们额外将其加进去即可。而非叶子结点的质因数一定仅存在 $2,3,5,7$ 作为其质因子，可以预处理处所有可能的非叶子节点，接下来的计数是简单的，可以进行数位 dp。假设可能作为非叶子结点的结点有 $K\approx6.6\times 10^4$ 个，数位 dp 求解复杂度太大了，很难通过。

接下来我们要考虑如何优化。考虑 $f(x)=0$ 的条件限制比较宽松，猜测以 $0$ 为根的子树的大小很大，那我们可以不对 $0$ 的子树计数，使用 $n-ans_{1\sim 9}$ 直接计算即可。此时的 $K\approx 200$，比较容易通过。

```cpp
#include<iostream>
#include<algorithm>
#include<map>
using ll=long long;
#define lg(x) (__builtin_log(x)/__builtin_log(10))
ll pow(ll base,ll exp){
  ll ans=1;
  while(exp!=0){
    if(exp&1)ans*=base;
    base*=base,exp>>=1;
  }
  return ans;
}
ll f(ll x){
  ll res=1;
  while(x!=0)res*=x%10,x/=10;
  return res;
}
int calc(ll x){
  while(x>9)x=f(x);
  return x;
}
std::map<ll,ll>dp[19][10];
std::map<ll,int>term;
ll ans[10];
int num[19];
ll dfs(int p,int dig,bool lim,ll mul){
  if(p==0)return mul==1;
  if(!lim&&dp[p][dig].find(mul)!=dp[p][dig].end())return dp[p][dig][mul];
  ll res=0;
  int bound=lim?num[p]:9;
  for(int i=1;i<=bound;i++)
    if(mul%i==0)res+=dfs(p-1,i,lim&&i==bound,mul/i);
  if(!lim)dp[p][dig][mul]=res;
  return res;
}
std::basic_string<ll>V;
void solve(ll x){
  std::fill(ans,ans+10,0);
  int len=0;
  while(x!=0)num[++len]=x%10,x/=10;
  for(int l=1;l<=len;l++)
    for(ll x:V)ans[term[x]]+=dfs(l,0,l==len,x);
}
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  for(int i=0;i<=60;i++){
    for(int j=0;j<=38;j++){
      for(int k=0;k<=26;k++){
          for(int l=0;l<=22;l++){
          if(i*lg(2)+j*lg(3)+k*lg(5)+l*lg(7)<=18){
            V+=pow(2,i)*pow(3,j)*pow(5,k)*pow(7,l);
            if(calc(V.back())==0)V.pop_back();
            else term[V.back()]=calc(V.back());
          }
        }
      }
    }
  }
  std::sort(V.begin(),V.end());
  int t;
  std::cin>>t;
  while(t--){
    ll n;
    std::cin>>n;
    solve(n);
    ans[0]=n;
    for(int i=1;i<=9;i++)ans[0]-=ans[i];
    for(int i=0;i<10;i++)std::cout<<ans[i]<<" ";
    std::cout<<"\n";
  }
  return 0;
}
```

---

## 作者：diqiuyi (赞：1)

显然我们不能对所有数都算一遍。注意到对于一个 $k$，若存在 $f(x)=k$，则 $k$ 的质因数必然是 $\{2,3,5,7\}$ 的子集。爆搜一下发现满足条件的 $k$ 只有约 $60000$ 个，且若 $x$ 和 $f(x)$ 连边，所有满足条件的数会构成一棵树。

我们对每个 $k$，算出满足 $f(x)=k$ 的数，这个东西可以数位 dp 解决。然后每个点的最终答案就是它的子树的答案和。

但是这样复杂度过高，无法通过。

发现很多数最后会变成 $0$，考虑只算非 $0$ 的子树的答案，发现剩余的点只有 $193$ 个，再做数位 dp 即可通过。$0$ 的答案拿 $n$ 减去剩下的即可。
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n,a[60000],val[60000],ord[60005],f[20][60005],s[20][60005],ret[15];
unordered_map<ll,int> id;
int p[4]={2,3,5,7},d[20],tot,t,pa[60000];
vector<int> son[60000],ok;
void dfs(int x,ll now){
	if(x==4){
		a[++tot]=now,id[now]=tot;
		return ;
	}
	for(;;){
		dfs(x+1,now);
		if(now<=150094635296999121ll/p[x])
			now*=p[x];
		else break;
	}
}
ll F(ll x){
	ll res=1;
	while(x) res*=x%10,x/=10;
	return res;
}
void dfs(int x){
	for(int y:son[x]) 
		dfs(y),val[x]+=val[y];
}
void col(int x){
	ok.push_back(x);
	for(int y:son[x])
		col(y);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	dfs(0,1);
	for(int i=1;i<=tot;i++)
		if(a[i]>9)
			pa[i]=id[F(a[i])],son[pa[i]].push_back(i);
	for(int i=1;i<=9;i++) col(id[i]);
	f[0][1]=1;
	for(int i=1;i<=18;i++)
		for(int j=1;j<=tot;j++){
			for(int k=1;k<=9;k++)
				if(!(a[j]%k))
					f[i][j]+=f[i-1][id[a[j]/k]];
			s[i][j]=s[i-1][j]+f[i][j];	
		}
	cin>>t;
	while(t--){
		cin>>n;
		for(int x:ok) val[x]=0;
		int len=0;ret[0]=n;ll nn=n;
		while(n) d[++len]=n%10,n/=10;
		ll now=1;
		for(int i=len;i;i--){
			if(i==len)
				for(int j:ok) 
					val[j]+=s[i-1][j];
			if(!d[i]) break;
			for(int j=1;j<d[i];j++){
				ll nv=now*j;
				for(int k:ok)
					if(!(a[k]%nv))
						val[k]+=f[i-1][id[a[k]/nv]];
			}
			now*=d[i];
			if(i==1) val[id[now]]++;	
		}
		for(int i=1;i<=9;i++) dfs(id[i]);
		for(int i=1;i<10;i++) ret[i]=val[id[i]],ret[0]-=ret[i];
		for(int i=0;i<10;i++) cout<<ret[i]<<' ';
		cout<<'\n';
	}
	return 0;
} 
```

---

## 作者：gcx12012 (赞：0)

### 前言
这篇题解介绍的是 $K=66061$ 的解法。

做这题的时候没注意到更优的解法，对着 $O(TK\lg V)$ 还有大常数的代码卡了一上午。
### Solution
首先考虑计数 $x\to f(x)$，但是直接对着 $x$ 做数位 dp 比较困难。

我们发现 $f(x)$ 的形式为 $2^x3^y5^z7^w$，其中 $x,y,z,w$ 均为非负整数。然后写个暴力发现 $f(x)$ 的取值只有 $K=66061$ 种，于是考虑对以上形式进行 dp。

不难设 $f_{i,x,y,z,w,0/1}$ 表示当前考虑到前 $i$ 位，$f(x)=2^x3^y5^z7^w$，$x$ 的前 $i$ 位是否等于 $n$ 的前 $i$ 位来进行 dp，一次转移大概是 10 倍常数。

但是讨论该位是否填 0 比较麻烦，此时我们发现：$ans_0=n-\sum_{i=1}^9 ans_i$，于是只需要枚举 1 到 9 即可。

但是还是过不去，此时发现当 $i$ 固定且最后一维为 1 时，只有一组 $(x,y,z,w)$ 对应值不为 0 的 $f$，于是我们把最后一维为 1 的转移单独拿出来做即可。

稍微卡卡常就可以过了，码量有点大，看看就行。
### Code
```
#include<bits/stdc++.h>
#include<cmath>
#define ll long long
#define ld long double
#define ull unsigned long long
#define lll __int128
#define N 1000010
#define ls x<<1
#define rs x<<1|1
#define lson ls,l,mid
#define rson rs,mid+1,r
#define For(i,a,b) for(short i=a;i<=b;++i)
#define Rof(i,a,b) for(short i=a;i>=b;--i)
#define mk make_pair
#define pb emplace_back
#define pii pair<ll,ll>
#define pque priority_queue
#define fi first
#define se second

using namespace std;
ll f[2][64][40][28][25][2];//cnt2 cnt3 cnt5 cnt7 islim
ll T,n;

ll read(){
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
ll mul[64][40][28][25];
short g[64][40][28][25];
ll ans[10];
ll shi[20],pre[21][4];
short add[10][4]={{0,0,0,0},{0,0,0,0},{1,0,0,0},{0,1,0,0},{2,0,0,0},{0,0,1,0},{1,1,0,0},{0,0,0,1},{3,0,0,0},{0,2,0,0}};
int w[21],pcnt=0;
void sol(){
	int op=0;
	For(p2,0,63){
		if(mul[p2][0][0][0]>n) break;
		For(p3,0,39){
			if(mul[p2][p3][0][0]>n) break;
			For(p5,0,27){
				if(mul[p2][p3][p5][0]>n) break;
				For(p7,0,24){
					if(mul[p2][p3][p5][p7]>n) break;
					f[0][p2][p3][p5][p7][0]=f[0][p2][p3][p5][p7][1]=f[1][p2][p3][p5][p7][0]=f[1][p2][p3][p5][p7][1]=0;
				}
			}
		}
	}
	int is=1;
	For(i,1,w[1]-1) f[0][add[i][0]][add[i][1]][add[i][2]][add[i][3]][0]++;
	if(w[1]) For(i,w[1],w[1]) f[0][add[i][0]][add[i][1]][add[i][2]][add[i][3]][1]++;
	For(S,1,pcnt-1){
		if(!w[S+1]) is=0; 
		//cout<<pre[S]<<endl;
		For(p2,0,63){
			if(mul[p2][0][0][0]>shi[S]) break;
			For(p3,0,39){
				if(mul[p2][p3][0][0]>shi[S]) break;
				For(p5,0,27){
					if(mul[p2][p3][p5][0]>shi[S]) break;
					For(p7,0,24){
						if(mul[p2][p3][p5][p7]>shi[S]) break;
						if(f[op][p2][p3][p5][p7][0]) For(i,1,9) f[op^1][p2+add[i][0]][p3+add[i][1]][p5+add[i][2]][p7+add[i][3]][0]+=f[op][p2][p3][p5][p7][0];
						f[op][p2][p3][p5][p7][0]=0;
					}
				}
			}
		}
		if(is) For(i,1,w[S+1]-1) f[op^1][pre[S][0]+add[i][0]][pre[S][1]+add[i][1]][pre[S][2]+add[i][2]][pre[S][3]+add[i][3]][0]+=f[op][pre[S][0]][pre[S][1]][pre[S][2]][pre[S][3]][1];
		if(is) For(i,w[S+1],w[S+1]) f[op^1][pre[S][0]+add[i][0]][pre[S][1]+add[i][1]][pre[S][2]+add[i][2]][pre[S][3]+add[i][3]][1]+=f[op][pre[S][0]][pre[S][1]][pre[S][2]][pre[S][3]][1];
		For(i,1,9) f[op^1][add[i][0]][add[i][1]][add[i][2]][add[i][3]][0]++;
		f[op][pre[S][0]][pre[S][1]][pre[S][2]][pre[S][3]][1]=0;
		op^=1;
	}
	fill(ans,ans+10,0);
	For(p2,0,63){
		if(mul[p2][0][0][0]>n) break;
		For(p3,0,39){
			if(mul[p2][p3][0][0]>n) break;
			For(p5,0,27){
				if(mul[p2][p3][p5][0]>n) break;
				For(p7,0,24){
					if(mul[p2][p3][p5][p7]>n) break;
					ans[g[p2][p3][p5][p7]]+=f[op][p2][p3][p5][p7][0]+f[op][p2][p3][p5][p7][1];
				}
			}
		}
	}
	ans[0]=n;
	For(i,1,9) ans[0]-=ans[i];
	For(i,0,9) cout<<ans[i]<<' ';
	cout<<endl;
}
short calc(ll x){
	if(x<10) return x;
	ll now=x,prod=1;
	while(now){
		prod*=(now%10);
		now/=10;
	}
	return calc(prod);
}

int main()
{
    //freopen("game.in","r",stdin);
    //freopen("game.out","w",stdout);
    For(p1,0,63){
    	For(p2,0,39){
    		For(p3,0,27){
    			For(p4,0,24){
    				mul[p1][p2][p3][p4]=2e18;
				}
			}
		}
	}
    shi[0]=1;
    For(i,1,18) shi[i]=shi[i-1]*10;
    ll now1=1;
	For(p2,0,63){
		if(now1>shi[18]) break;
		ll now2=now1;
		For(p3,0,39){
			if(now2>shi[18]) break;
			ll now3=now2;
			For(p5,0,27){
				if(now3>shi[18]) break;
				ll now4=now3;
				For(p7,0,24){
					if(now4>shi[18]) break;
					g[p2][p3][p5][p7]=calc(now4);
					mul[p2][p3][p5][p7]=now4;
					now4*=7;
				}
				now3*=5;
			}
			now2*=3;
		}
		now1*=2;
	}
    T=read();
    ll in[1010];
    For(i,1,T) in[i]=read();
    For(i,1,T){
    	n=in[i];
    	ll now=n;
    	pcnt=0;
    	while(now){
    		w[++pcnt]=now%10;
    		now/=10;
		}
		reverse(w+1,w+pcnt+1);
		For(j,1,pcnt){
			For(k,0,3){
				pre[j][k]=pre[j-1][k]+add[w[j]][k];
			}
		}
    	sol();
	}
   	return 0;
}
/*

*/
```

---

