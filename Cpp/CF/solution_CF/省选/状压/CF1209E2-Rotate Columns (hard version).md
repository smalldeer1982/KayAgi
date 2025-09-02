# Rotate Columns (hard version)

## 题目描述

这是该问题的更难版本，区别仅在于约束条件不同。

给定一个 $n \times m$ 的矩阵 $a$。每次操作，你可以选择任意一列，并将该列的元素循环移动（即将该列的元素向下移动一格，最底部的元素移动到最顶部）。你可以对任意一列进行任意次数（包括零次）这样的操作，也可以对同一列多次操作。

完成所有循环移动后，对于每一行，计算该行中的最大值。设第 $i$ 行的最大值为 $r_i$。请问 $r_1 + r_2 + \ldots + r_n$ 的最大可能值是多少？

## 说明/提示

在第一个测试用例中，你可以将第三列向下循环移动一次，这样可以得到 $r_1 = 5$，$r_2 = 7$。

在第二个测试用例中，你可以不进行任何旋转，此时 $r_1 = r_2 = 10$，$r_3 = 9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
2 3
2 5 7
4 2 4
3 6
4 1 5 2 10 4
8 6 6 4 9 10
5 4 9 5 8 7
3 3
9 9 9
1 1 1
1 1 1
```

### 输出

```
12
29
27
```

# 题解

## 作者：Foofish (赞：21)

相信题意大家已经都了解了，我们思考一下如何解决这道题目。

首先数据范围是 $n\leq12$，在这个范围内能做的估计是指数级的复杂度。

因为 $m$ 很大，我们要尝试能不能把他弄掉。

> 我们只可能用到**列里最大值最大**的前 $n$ 个列

证明：

假设我们用到了最大值最第 $n+1$ 大的那个列。假如说他用到了这个列里的某些值，那么这些值肯定没有那些 $i,i\leq n$ 列的最大值大，那么我们大可以用那些前 $n$ 列的最大值替换现在这个列里用到的那些值，这样只会使答案更优。

我们已经将 $m$ 也降到了 $n$ 的级别了。

思考一下如何暴力。这就是 E1。直接令 $dp_{i,j}$ 表示现在选到了第 $i$ 行，已经确定选那些行的状态是 $j$ 的最大值。转移就枚举 $j$ 的子集 $k$ 表示上一行中已经确定的状态。那么就有状态转移方程 $dp_{i,j}=dp_{i,k}+w_{k\ xor \ j}$ 其中 $w_k$ 表示现在这一行中我已经确定的状态经过移位后的最大值。

有聪明的彦祖就会问了，如果我这一位最后明明不是行里的最大值，但是还是把他当做了最大值，这不是错误的么？

当然不是，因为就算这种选法是错误的，正是因为他不是行里的最大值，所以取最大的时候他肯定没正确的选法更大，所以不会对答案造成影响。

------------

然后我们计算一下时间复杂度。

枚举子集的复杂度是 $\mathcal{O}(3^n)$ 这里也稍微证明一下

令二元组 $(S,T),T\subseteq S$ 这就表示我们枚举的集合 $S$ 和子集 $T$ 。我们思考一下每一个元素可能的情况

1. $k\in S,k\notin T$
2. $k\in S,k\in T$
3. $k\notin S,k\notin T$

所以对于每一种元素有 $3$ 种情况，那么总时间复杂度就是 $\mathcal{O}(3^n)$

话说上文，枚举了子集之后，我们还要计算 $w_{k\ xor\ j}$ 的值，因为还要移位所以计算 $w_{k\ xor\ j}$ 的复杂度是 $\mathcal{O}(n^2)$ 总时间复杂度就是 $\mathcal{O}(n^33^n)$ 这肯定是过不了的。

我们注意到 $w_{l}$ 的值是不会变的，我们枚举所有集合预处理出 $w$ 数组。

总时间复杂度即为 $\mathcal{O}(n(2^nn^2+3^n))=\mathcal{O}(n^32^n+n3^n)$

主要难度都在代码上了。

```cpp
#include <bits/stdc++.h>
#define debug puts("I love Newhanser forever!!!!!");
#define pb push_back
using namespace std;
template <typename T>inline void read(T& t){
    t=0; register char ch=getchar(); register int fflag=1;
    while(!('0'<=ch&&ch<='9')){if(ch=='-') fflag=-1;ch=getchar();}
    while(('0'<=ch&&ch<='9')){t=t*10+ch-'0'; ch=getchar();} t*=fflag;
}
template <typename T,typename... Args> inline void read(T& t, Args&... args){read(t);read(args...);}
const int MAXN=13;
int T,n,m;
struct Col{
    int a[MAXN],maxx;
    void Clear(){maxx=0;}
    void Intt(){for(int i=0;i<n;++i) maxx=max(maxx,a[i]);}
    bool operator < (const Col &col) const{
        return maxx>col.maxx;
    }
}c[5145];
int w[1<<MAXN],dp[MAXN][1<<MAXN];
int main(){
    read(T);
    while(T--){
        read(n,m);
        memset(dp,0,sizeof(dp));
        for(int i=0;i<m;++i) c[i].Clear();
        for(int i=0;i<n;++i){
            for(int j=0;j<m;++j)
                read(c[j].a[i]);
        }
        for(int j=0;j<m;++j) c[j].Intt();
        sort(c,c+m);
        /*for(int i=0;i<min(n,m);++i)
            for(int j=0;j<n;++j)
                cout<<c[i].a[j]<<endl;*/
        for(int i=0;i<min(n,m);++i){
            //现在是第 i 列
            for(int j=0;j<(1<<n);++j){
                //现在选的状态是 j
                w[j]=0;
                for(int k=0;k<n;++k){
                    //进行了 k 次循环移位.
                    int res=0;
                    for(int l=0;l<n;++l)
                    if((1<<l)&j) res+=c[i].a[(l+k)%n];
                    w[j]=max(w[j],res);
                }
            }
            for(int j=0;j<(1<<n);++j){
                //现在选择的状态是 j.
                if(i==0){
                    dp[i][j]=w[j];
                    continue;
                }
                dp[i][j]=dp[i-1][j];
                for(int k=j;k;k=(k-1)&j) dp[i][j]=max(dp[i][j],dp[i-1][k]+w[k^j]);
            }
        }
        cout<<dp[min(n,m)-1][(1<<n)-1]<<endl;
    }
    return 0;
}
//Welcome back,Newhanser.
```

---

## 作者：Pelom (赞：15)

[更好的阅读体验](https://pelom.top/archives/13/)

### 题意

给出一个矩阵，可以选择一个列循环移位，求每一行的最大值的最大和

**数据范围：**$1 \le n \le 12,1 \le m \le 2000$

### 题解

我们可以记录每一列的选择情况，容易想到这是状压$dp$

用$dp[i][j]$表示前$i$列的选择情况为$j$的和，其中$j$的第$k$位表示选择第$k$行

但是由于$m$较大，这样会太慢

我们可以按每一列的最大值对列从大到小排序，容易证明，只会选择前$n$大的列，而剩下的列显然不会对答案造成影响

```cpp
for(int j=0;j<m;j++){
    for(int i=0;i<n;i++)
        v[j]=Max(v[j],a[i][j]);
    c[j]=(node){v[j],j};
}
sort(c,c+m);
m=Min(n,m);
```

我们可以进行预处理，用$f[i][j]$表示第$i$列的选择情况为$j$的和，$j$的第$k$位表示选择第$i$列的第$k$行，即$a[k][i]$

```cpp
tot=1<<n;
for(int i=0;i<m;i++)
    for(int j=0;j<tot;j++)
        for(int k=0;k<n;k++)
            if((j>>k)&1)
                f[i][j]+=a[k][c[i].id];
```

操作中$j$循环移位$k$次后的状态$t$可以表示为

```cpp
int t=((j>>k)|(j<<(n-k)))&(tot-1);
```

$j$共有$n$种变化；因为可以任意进行操作，所以
$$f[i][j]=max(f[i][t])$$
接下来进行$dp$

如果不在当前列选择，直接从之前继承

```cpp
dp[i+1][j]=dp[i][j];
```

否则，对于一个状态$j$，从低位到高位枚举前$i$列选择的行，而第$i+1$列选择的自然就是剩下的行，我们将其状态记为$t$，那么前$i$列的状态就是$j \oplus t$

```cpp
for(int t=j;t;t=(t-1)&j)
    dp[i+1][j]=Max(dp[i+1][j],dp[i][j^t]+f[i][t]);
```

**代码：**

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=12+1;
const int M=2000+10;
int t,n,m;
int a[N][M];
int tot;
int v[M],f[N][1<<N],dp[N][1<<N];
template <typename T>
inline T Max(T a,T b){
    return a>b?a:b;
}
template <typename T>
inline T Min(T a,T b){
    return a<b?a:b;
}
struct node{
    int v,id;
    inline bool operator < (const node& x) const{
        return v>x.v;
    }
} c[M];
int main(){
    scanf("%d",&t);
    for(;t--;){
        memset(v,0,sizeof(v));
        memset(f,0,sizeof(f));
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                scanf("%d",&a[i][j]);
        for(int j=0;j<m;j++){
            for(int i=0;i<n;i++)
                v[j]=Max(v[j],a[i][j]);
            c[j]=(node){v[j],j};
        }
        sort(c,c+m);
        m=Min(n,m);
        tot=1<<n;
        for(int i=0;i<m;i++){
            for(int j=0;j<tot;j++)
                for(int k=0;k<n;k++)
                    if((j>>k)&1)
                        f[i][j]+=a[k][c[i].id];
            for(int j=0;j<tot;j++)
                for(int k=0;k<n;k++){
                    int t=((j>>k)|(j<<(n-k)))&(tot-1);
                    f[i][j]=Max(f[i][j],f[i][t]);
                }
        }
        for(int i=0;i<m;i++)
            for(int j=0;j<tot;j++){
                dp[i+1][j]=dp[i][j];
                for(int t=j;t;t=(t-1)&j)
                    dp[i+1][j]=Max(dp[i+1][j],dp[i][j^t]+f[i][t]);
            }
        printf("%d\n",dp[m][tot-1]);
    }
    return 0;
}
```

---

## 作者：hehezhou (赞：9)

[题面(洛谷)](https://www.luogu.org/problemnew/solution/CF1209E2)  
[题面(CF)](http://codeforces.com/contest/1209/problem/E2)

题意

给定一个 $n \times m$ 的矩阵，你可以对每一列进行任意次循环移位

求最大的 每一行的最大值之和

$n\leq 12,m\leq 2000,t\leq 40$

首先有一个很自然的状压dp想法(也就是只能过E1的)  
令$dp[s][i]$表示已经处理好了前$i$列，集合$s$中的位置已经确定最大值  
这样$dp$可能会有不合法的情况  
但是这些情况显然不优  
所以不会有问题  
转移直接枚举子集  
$O(tm3^n)$  

这里有一个性质  
就是按照每列的最大值从大到小排序  
只取前$n$个做  
结果也是正确的  
比较显然  
然后就$O(tn3^n+tmlogm)$  
```cpp
#include <bits/stdc++.h>
using namespace std;
int dp[2100][4100];
int n, m, t;
struct node {
    int a[20], c;
    inline int init(int *x) {
        c = 0;
        for(int i = 1; i <= n; i++) a[i] = x[i], c = max(c, a[i]);
    }
    inline int operator < (const node &b) const {
        return c > b.c;
    }
    inline void out(int *x) {
        for(int i = 1; i <= n; i++) x[i] = a[i];
    }
} nd[2100];
int tmp[4100];
int lg2[4100];
int a[2100][2100];
int now[20];
int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++) scanf("%d", a[j] + i);
        for(int i = 1; i <= m; i++) nd[i].init(a[i]);
        sort(nd + 1, nd + 1 + m);
        for(int i = 0; i < n; i++) lg2[1 << i] = i;
        int all = (1 << n) - 1;
        for(int i = 1; i <= min(n, m); i++) {
            nd[i].out(now - 1);
            for(int s = 0; s <= all; s++) {
                tmp[s] = 0;
                for(int d = 0; d < n; d++) {
                    int sum = 0, tt = s;
                    while(tt) {
                        sum += now[(d + lg2[tt & -tt]) % n];
                        tt -= tt & -tt;
                    }
                    tmp[s] = max(tmp[s], sum);
                }
            }
            for(int S = 0; S <= all; S++) {
                dp[i][S] = 0;
                for(int s = S; ; s = (s - 1) & S) {
                    dp[i][S] = max(dp[i][S], dp[i - 1][s] + tmp[S ^ s]);
                    if(s == 0) break;
                }
            }
        }
        printf("%d\n", dp[min(n, m)][all]);
    }
}
```

---

## 作者：kradcigam (赞：3)

行很少，列很多。

最终的答案只跟每一行有关，所以有些列是没用的。

或者换个角度理解，我们**按一列上的最大数将这 $m$ 列排序**，把第一列上的最大数放在第 1 行，第二列上的最大数房子第 2 行，……，把第 $n$ 列上的最大数放在第 $n$ 行。于是我们发现第 $n+1\sim m$ 列甚至连最大数都是没用的，况且前 $n$ 列不仅会用到最大数，其它数也都有用到的可能，所以可能有用的列数只有 $\min(n,m)$ 条。

接下来就考虑状压 DP，考虑状态 $f_{i,j}$ 表示处理到排序后的第 $i$ 列，行上的状态为 $j$（1 表示已经确定了最大数，0 表示没有确定最大数）中已经确定最大数的最大和。

考虑转移，枚举子集，并计算子集的最大贡献，复杂度为 $O(3^nn^3)$ 但这是无法接受的。

我们发现瓶颈在于计算子集的最大贡献需要 $O(n^2)$ 的复杂度，而一个子集可能会被计算多次，于是考虑提前预处理，得到复杂度为 $O(3^n n+2^nn^3)$。

代码：
```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
template<typename T>inline void write(T x){
    unsigned long long y=0;T l=0;
    if(x<0)x=-x,putchar(45);
    if(!x){putchar(48);return;}
    while(x){y=y*10+x%10;x/=10;l++;}
    while(l){putchar(y%10+48);y/=10;l--;}
}
template<typename T>inline void writeln(T x){write(x);puts("");}
template<typename T>inline void writes(T x){write(x);putchar(32);}
const int N=13,M=2010,K=(1<<N)+10;
int f[N][K],a[N][M],t[K];
struct Column{
	int maxn,id;
	inline bool operator<(const Column&t)const{
		return maxn>t.maxn;
	}
}c[M];
signed main(){
	int _=read();while(_--){
		int n=read(),m=read();
		F(i,1,m)c[i].id=i,c[i].maxn=0;
		F(i,1,n)
			F(j,1,m){
				a[i][j]=read();
				c[j].maxn=max(c[j].maxn,a[i][j]);
			}
		sort(c+1,c+m+1);
		F(i,1,min(n,m)){
			F(j,0,(1<<n)-1){
				t[j]=0;
				F(k,0,n-1){
					int sum=0;
					F(l,0,n-1)
						if((j>>l)&1)sum+=a[(l+k)%n+1][c[i].id];
					t[j]=max(t[j],sum);
				}
			}
			F(j,0,(1<<n)-1){
				f[i][j]=f[i-1][j];
				for(int k=j;k;k=(k-1)&j)
					f[i][j]=max(f[i][j],f[i-1][j^k]+t[k]);
			}
		}writeln(f[min(n,m)][(1<<n)-1]);
	}
	return 0;
}
```

---

## 作者：Qiiiiiii_ (赞：3)

题意描述：$T$ 次询问，每次给定一个 $n*m$ 的矩阵，每次可以将一列循环任意次。设 $r_i$ 表示第 $i$ 行的最大值，求所有可能的操作下 $\sum r_i$ 最大值。 $(T\le40,n\le12,m\le2e3)$

考虑到 $n$ 很小，显然就是状态压缩，但是 $m$ 很大，而且乘 $2^n$ 完全不能过，所以就思考这 $m$ 个必是唬人的。先猜一个结论，我们只用取每列最大值排名前 $n$ 的。考虑为什么。当我们取第 $n+1$ 大的那一列的时候，我们选前 $n$ 名取满一定不会更劣，而第 $n+1$ 大的那一列中不存在比那个列的最大值排名第 $n+1$ 的值更大的值了，所以必然不劣。然后就是对 $n*n$ 的矩阵求原值，这个用状态压缩 $dp$ 可以轻易通过。 设 $dp[i][j]$ 表示选到第 $i$ 列，强制选了状态为 $j$ 的行的最大值。时间复杂度$O(n3^n)$。  

```
#include<bits/stdc++.h>
#define re register
#define ll long long
#define LL inline ll
#define I inline int
#define V inline void
#define B inline bool 
#define FOR(i,a,b) for(re int i=(a),i##i=(b);i<=i##i;++i)
#define ROF(i,a,b) for(re int i=(a),i##i=(b);i>=i##i;--i)
//#define gc getchar()
#define gc (fs==ft&&(ft=(fs=buf)+fread(buf,1,1<<18,stdin),ft==fs))?0:*fs++
using namespace std;
char *fs,*ft,buf[1<<18];
const int N=1e4+10;
LL read(){
	ll p=0; bool w=0; char ch=gc;
	while(!isdigit(ch)) w=ch=='-'?1:0,ch=gc;
	while(isdigit(ch)) p=p*10+ch-'0',ch=gc;
	return w?-p:p;
}
int T,n,m,a[30][N],mx[N],ans;
int dp[2][N],f[20][N],sck[20],fl;
I get(int x,int zt){
	int res=0,as=0,tmp=zt;
	FOR(i,1,n){
		tmp=zt,as=0;
		FOR(j,i,i+n-1) (as+=(tmp&1)?a[j][x]:0),tmp>>=1;
		res=max(res,as);
	}
	return res;
}
V sol(){
	int tot=(1<<n)-1,tmp=0,bj=0;
	FOR(k,1,n) { 
		tmp=0,bj=0; 
		FOR(i,1,m) if(mx[i]>tmp) tmp=mx[i],bj=i;
		sck[k]=bj,mx[bj]=0;
	}
	FOR(k,1,n) FOR(j,0,tot) f[k][j]=get(sck[k],j);
	FOR(i,1,n){
		FOR(j,0,tot){
			int w=tot^j;
			dp[fl][j]=max(dp[fl][j],dp[fl^1][j]);
			for(re int k=w;k;k=(k-1)&w) 
				dp[fl][j|k]=max(dp[fl][j|k],dp[fl^1][j]+f[i][k]);
		}
		fl^=1;
		memset(dp[fl],0,sizeof(dp[fl]));
	}
	fl^=1;
	ans=dp[fl][tot];
	printf("%d\n",ans);
	return ;
}
V init(){
	memset(mx,0,sizeof(mx));
	memset(dp,0,sizeof(dp));
	return ;
}
int main(){
	T=read();
	while(T--){
		n=read(),m=read(),ans=0;
		init();
		FOR(i,1,n) FOR(j,1,m) a[i][j]=read(),mx[j]=max(mx[j],a[i][j]);
		FOR(i,n+1,2*n) FOR(j,1,m) a[i][j]=a[i-n][j];
		sol();
	}
	return 0;
}
```


---

## 作者：FjswYuzu (赞：2)

注意到整个 $n \times m$ 的矩阵中实际只有 $n^2$ 数是有用的，因为我们最坏的情况下，我们会选择 $n$ 列中的最大值对应我们的每一行。

在 Easy Version 中，矩阵于是被我们缩小到了 $4 \times 4$ 的范围，直接搜就行了。时间复杂度是 $O(n^{m-1})$。

但是在 Hard Version 中，$n \leq 12$ 不足以让我们接受。注意到 $12$ 是一个极小的数，不难与之和状压状物产生联系。

状态设置中，首先列的编号必不可少。然而我们的 dp 状态设置中，重要的表达状态的第二维需要表示当前的最优状态，但是其会与最大值挂钩。还是一样的，因为最大值和我们的状态没有直接联系，我们没必要更不能将其加入状态。但是如果我们将状态设置为 $dp_{i,S}$ 为，前 $i$ 列中确定了状态为 $S$ 的行的最大值，如果出现有更大的数覆盖了之前的最大值怎么办？

注意到，假设这个被覆盖的值的位置为 $p$，我们在 $S\backslash p$ 中会得到更优的值。即，即使这个玩意儿不合法，我们也有更优秀的状态去更新。

于是直接 dp 即可。预处理循环唯一每列选择的状态可以选取的数的最大值。过程中有一个致命的小细节需要注意，在代码中将标出。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct infm{
	int v,i;
	infm(){}
	infm(int V,int I){v=V,i=I;}
	bool operator < (infm ano) const {return v>ano.v;}
}st[2005];
int n,m,a[15][2005],mat[15][2005],sts[(1<<12)+5],dp[14][(1<<12)+5];
int trans(int S){return (S>>1)|((S&1)*(1<<(n-1)));}
int main(){
	int C;
	scanf("%d",&C);
	while(C-->0)
	{
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;++i)	for(int j=1;j<=m;++j)	scanf("%d",&a[i][j]);
		for(int j=1;j<=m;++j)
		{
			int maxn=0;
			for(int i=1;i<=n;++i)	maxn=max(maxn,a[i][j]);
			st[j]=infm(maxn,j);
		}
		sort(st+1,st+1+m);
		m=min(m,n);
		for(int i=1;i<=m;++i)
		{
			int id=st[i].i;
			for(int j=1;j<=n;++j)	mat[j][i]=a[j][id];
		}
		dp[0][0]=0;
		for(int i=1;i<=m;++i)
		{
			for(int S=0;S<(1<<n);++S)
			{
				dp[i][S]=0;
				sts[S]=0;
				int org=S;
				do{
					int sum=0;
					for(int j=0;j<n;++j)	if((S>>j)&1)	sum+=mat[j+1][i];
					sts[org]=max(sts[org],sum);
					S=trans(S);
				}while(org!=S);
			}
			for(int S=0;S<(1<<n);++S)
			{
				for(int T=S;;T=S&(T-1))
				{
					dp[i][S]=max(dp[i][S],dp[i-1][T]+sts[S^T]);
					if(T==0)	break;//!!!!!!!!!!!
				}
			}
		}
		printf("%d\n",dp[m][(1<<n)-1]);
	}
	return 0;
}
```

---

## 作者：kouylan (赞：1)

## 题解 CF1209E2 【Rotate Columns (hard version)】

[洛谷题面传送门](https://www.luogu.com.cn/problem/CF1209E2)

[CF题面传送门](https://codeforces.ml/contest/1209/problem/E2)

首先一开始，我们能想到一个朴素的 dp。

设 $f_{i,s}$ 表示考虑到第 $i$ 列，已经有 $s$ 状态的列中选择了数的最大值。因为 $s$ 中的 $1$ 肯定是只会多不会少的。所以转移就是

$$f_{i,s}=f_{i-1,t}+work(i,s-t)$$

其中 $t$ 表示 $i-1$ 列的状态，是 $s$ 的子集，函数 $work(i,s)$ 表示在第 $i$ 列选择 $s$ 状态下的数的最大值。

但我们发现每一次询问的复杂度是 $O(2^n\times m\times n\times log_n)$ 的，（其中的 $log$ 是枚举子集）需要优化。

我们首先能发现其实没必要考虑那么多列。那些数比较小的列最后肯定不会被算进答案中。所以我们可以给列按最大值由高到低排序，取前 $n$ 列进行计算即可。

接下来我们发现，对于每一列计算时，我们可以先把 $work(i,s)$ 的 $2^n$ 个值预处理出来，然后枚举子集计算时 $O(1)$ 调用即可。

总时间复杂度 $O(2^n\times n^2+2^n\times n\times log_n)$ 就能稳稳的过了。

下面是 AC 代码
```cpp
/*
Codeforces 1209E2
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int q,n,m;
struct col{
	int a[15],mx;
	bool operator < (const col b) const
	{
		return mx>b.mx;
	}
}c[2005];
int f[1<<13],mx[1<<13],ff[1<<13];

int work(int x,int s)
{
	int res=0;
	for(int k=0;k<n;k++)
	{
		int sum=0;
		for(int i=1;i<=n;i++)
			if(s&1<<i-1)
				sum += c[x].a[i];
		res = max(res,sum);
		int tmp=c[x].a[n];
		for(int i=n-1;i>=1;i--)
			c[x].a[i+1] = c[x].a[i];
		c[x].a[1] = tmp;
	}
	return res;
}

signed main()
{
	cin>>q;
	while(q--)
	{
		memset(f,0,sizeof(f));
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=max(n,m);i++)
			c[i].mx = -1, memset(c[i].a,0,sizeof(c[i].a));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				scanf("%lld",&c[j].a[i]);
				c[j].mx = max(c[j].mx,c[j].a[i]);
			}
		sort(c+1,c+1+m);
		m = min(m,n);
		for(int i=1;i<=m;i++)
		{
			for(int s=0;s<=(1<<n)-1;s++)
				mx[s] = work(i,s);
			memcpy(ff,f,sizeof(ff)); 
			for(int s=0;s<=(1<<n)-1;s++)
				for(int k=s;k<=(1<<n)-1;k=k+1|s)
					f[k] = max(f[k],ff[s^k]+mx[s]);
		}
		printf("%lld\n",f[(1<<n)-1]);
	}
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：DarkMoon_Dragon (赞：1)

## $Solution~II$
### 何必二维$dp$
+ 首先只用最大的$n$列是显然的，因为题意可以转换为每行取一个数，使得最后和最大
+ 考虑状压$dp$
+ 设$dp[state]$表示$state$状态下的最优答案
+ 枚举子集更新即可
   
```cpp
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define rr int
using namespace std;
typedef long long ll;
inline ll read() {
    char i = getchar();
    ll f = 1, res = 0;
    while (i < '0' || i > '9') {
        if (i == '-') f = -1;
        i = getchar();
    }
    while (i >= '0' && i <= '9') {
        res = res * 10 + i - '0';
        i = getchar();
    }
    return res * f;
}
int n, m;
const int N = 1e5 + 50;
struct zk {
    int a[25], maxn;
    inline void init(int* x) {
        memset(a, 0, sizeof a);
        maxn = 0;
        for (rr i = 0; i < n; ++i) {
            a[i] = x[i];
            maxn = max(maxn, x[i]);
        }
    }
    bool operator<(const zk& A) const { return maxn > A.maxn; }
} line[N];
int rd[N][25];
ll dp[5000];  // dp[st] 表示当前状态最大值
ll tmp[5000], odp[5000];
int main() {
    int T = read();
    while (T--) {
        memset(dp, 0, sizeof dp);
        n = read(), m = read();
        for (rr i = 0; i < n; ++i)
            for (rr j = 0; j < m; ++j) rd[j][i] = read();
        for (rr i = 0; i < m; ++i) {
            line[i].init(rd[i]);
            // cout << line[i].maxn <<endl;
        }
        sort(line, line + m);
        m = min(n, m);
        int sz = (1 << n);
        for (rr i = 0; i < m; ++i) {
            memset(tmp, 0, sizeof tmp);
            for (rr st = 0; st < sz; ++st) {
                for (rr k = 0; k < n; ++k) {  // 转k次
                    ll res = 0;
                    for (rr now = 0; now < n; ++now) {
                        if (st & (1 << now)) {
                            res += line[i].a[(now + k) % n];
                        }
                        tmp[st] = max(tmp[st], res);
                    }
                }
            }
            memcpy(odp, dp, sizeof dp);
            for (rr st = 0; st < sz; ++st) {
                // for (rr k = st; k > 0; k = (k - 1) & st) {
                for (rr k = st; k < sz; k = (k + 1) | st) {
                    dp[k] = max(dp[k], odp[st ^ k] + tmp[st]);
                }
            }
        }
        printf("%lld\n", dp[sz - 1]);
    }
}
````

---

## 作者：D_14134 (赞：0)

### 题意

给定一个n×m的矩阵，你可以对每一列进行若干次循环移位。

求操作完成后每一行的最大值之和。

### 范围
n<=12,m<=2000
### 题解
我们可以很简单的吧题目变换一下——把最大值的和最大修改成：每行选一个数使得和最大。

所以朴素的状压就出来了：用dp[i][j] 表示前i列的选择情况为j的和，其中j的第k位表示选择第k行。

复杂的为O(3^n*m)。明显不行。

优化1：把每一列按照最大值排序，则只需要考虑前n个，否则一定可以替换某一位使它变得更优.O(3^n * m)——>O(3^n*n)

就可以过这道题n<=12的数据了。

但其实这道题的n还可以做到20;

优化2：循环移位的dp值相等，O(3^n * n)——>O(2^n * n^2)

### code
```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define maxn 2010
using namespace std;

struct M{
	int id,Max;
	bool operator<(const M &z)const{return z.Max<Max;}
}kp[maxn];

int lp[20][1<<14],f[20][20],T,dp[1<<14],n,m;

void work(){
	int S;
	scanf("%d%d",&n,&m),S=1<<n;
	for(int i=1;i<=m;i++) kp[i].Max=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&lp[i][j]),kp[j].Max=max(kp[j].Max,lp[i][j]);
	for(int i=1;i<=m;i++) kp[i].id=i;
	sort(kp+1,kp+1+m);
	m=min(m,n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			f[i][j]=lp[i][kp[j].id];
	for(int j=1;j<=m;j++){
		for(int k=0;k<S;k++){
			lp[j][k]=0;
			for(int i=1;i<=n;i++)
				if((1<<(i-1))&k) lp[j][k]+=f[i][j];
		}
		for(int i=1;i<S;i++)
			for(int k=0;k<n;k++)
				lp[j][i]=max(lp[j][i],lp[j][((i>>k)|(i<<(n-k)))&(S-1)]);
	}
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=m;i++){
		for(int j=S-1;j;j--){
			for(int k=j;k;k=(k-1)&j){
				dp[j]=max(dp[j],dp[j^k]+lp[i][k]);
			}
		}
	}
	printf("%d\n",dp[S-1]);
}

int main(){
	scanf("%d",&T);
	while(T--) work();
	return 0;
}
```







---

## 作者：Lates (赞：0)

首先可以加强一下，变成每行随便取一个数，要求和最大。

然后有个 $f_{i,S}$ 表示前 $i$ 列，已经确定 $S$ 中选啥的答案。

这时可以过 E1

然后一个观察是，最大值前 $n$ 大的列可以是答案。因为这个与其他方式相比肯定不劣。于是只要让这几列拿去 dp。

然后复杂度变成 $\mathcal{O}(n(3^n+n^2))$。

[link](https://codeforces.com/contest/1209/submission/182351981)

---

