# [SDOI2009] Bill的挑战

## 题目描述

Sheng_bill 不仅有惊人的心算能力，还可以轻松地完成各种统计。在昨天的比赛中，你凭借优秀的程序与他打成了平局，这导致 Sheng_bill  极度的不满。于是他再次挑战你。这次你可不能输。

这次，比赛规则是这样的：

给出 $N$ 个长度相同的字符串（由小写英文字母和 `?` 组成），$S_1,S_2,\dots,S_N$，求与这 $N$ 个串中的刚好 $K$ 个串匹配的字符串 $T$ 的个数，答案对 $1000003$ 取模。

若字符串 $S_x(1\le x\le N)$ 和 $T$ 匹配，满足以下条件：
1. $|S_x|=|T|$。
2. 对于任意的 $1\le i\le|S_x|$，满足 $S_x[i]= \texttt{?}$ 或者 $S_x[i]=T[i]$。

其中 $T$ 只包含小写英文字母。

## 说明/提示

### 数据规模与约定
- 对于 $30\%$ 的数据，$N\le5$，$|S_i|\le20$；
- 对于 $70\%$ 的数据，$N\le13$，$|S_i|\le30$；
- 对于 $100\%$ 的数据，$1\le T\le 5$，$1\le N \le15$，$1\le|S_i|\le50$。

## 样例 #1

### 输入

```
5

3 3

???r???

???????

???????

3 4

???????

?????a?

???????

3 3

???????

?a??j??

????aa?

3 2

a??????

???????

???????

3 2

???????

???a???

????a??```

### 输出

```
914852

0

0

871234

67018```

# 题解

## 作者：远航之曲 (赞：46)

安利一下[博客](http://www.yhzq-blog.cc/luogu-2167-sdoi2009bill的挑战/)


一眼数据范围：你好状压


因为每个字符串都是相同长度的，我们可以先预处理一个$match[1 \cdots len][a \cdots z]$，里面用二进制表示$1 \cdots n$位的字符串的第$i$位是否可以匹配上$a \cdots z$。


然后转移就非常好想了，$f[i][j]$表示第i位的匹配上了j这个状态的方案数，然后随便瞎搞统计结果就行了。。。


```cpp
#include <cstdio>
#include <cstring>
using namespace std;
char s[100][100];
int f[55][1<<15];
int n,k,len,tot,mod=1000003;
int match[50][50];
void check(int x,int y)
{
    for (int i=0;i<=len;i++)
        if (!(s[x][i]=='?'||s[y][i]=='?'||s[x][i]==s[y][i]))
            return;
    match[x][y]=match[y][x]=1;
}
main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        memset(f,0,sizeof f);
        memset(match,0,sizeof match);
        tot=0;
        scanf("%d%d",&n,&k);
        for (int i=1;i<=n;i++)
            scanf("%s",s[i]);
        len=strlen(s[1]);
        
        for (int i=0;i<len;i++)
            for (char ch='a';ch<='z';ch++)
                for (int j=1;j<=n;j++)
                    if (s[j][i]=='?'||s[j][i]==ch)
                        match[i][ch-'a']|=(1<<j-1);
        int cnt=(1<<n)-1;
        f[0][cnt]=1;
        for (int i=0;i<len;i++)
            for (int j=0;j<=cnt;j++)
                if (f[i][j])
                    for (char ch='a';ch<='z';ch++)
                        f[i+1][match[i][ch-'a']&j]+=f[i][j],
                        f[i+1][match[i][ch-'a']&j]%=mod;
        for (int i=0;i<=cnt;i++)
        {
            int ans=0;
            for (int j=1;j<=cnt;j<<=1) ans+=(bool)(i&j);
            if (ans==k) tot=(tot+f[len][i])%mod;
        }
        printf("%d\n",tot);
    }
}
```

---

## 作者：枫林晚 (赞：39)

# 全网唯一一篇容斥题解
安利博客 ：[[SDOI2009]Bill的挑战——大力容斥](https://www.cnblogs.com/Miracevin/p/9585609.html)

看到这个题，大部分人想的是状压dp

但是我是个蒟蒻没想到，就用容斥切掉了。

并且复杂度比一般状压低，

目前是luogu rank1 （虽然开了O2，但是大家都开了啊）

（其实这个容斥的算法，提出来源于ywy_c_asm）

（然而我知道了这个算法，竟然和他写的不一样，而且比他跑的快）

进入正题：

我们需要统计恰好满足匹配k个的情况。

那么，我们可以先找出来，恰好满足n个，n-1，n-2。。。k个的情况。

分别记为ans[i]

ans[i]怎么算呢？

先给出公式：

### ans[i]=cal(i)-∑C(j,i)×ans[j] 其中，i+1<=j<=n

cal(i)表示，从n个中任意选择i个，对于所有选择的情况，的方案数的和。

cal(i)可以dfs暴力C(n,i)枚举，每次统计答案。计入tot

```cpp
void dfs(int x,int has){
	if(x==n+1){
		if(has!=up) return;
		ll lp=1;
		for(int j=1;j<=len;j++){
			las=-1;
			for(int i=1;i<=up;i++){
				if(a[mem[i]][j]!='?'){
					if(las==-1){
						las=a[mem[i]][j]-'a';
					}
					else if(las!=a[mem[i]][j]-'a') return;
				}
			}
			if(las==-1)lp=(lp*26)%mod;
		}
		(tot+=lp)%=mod;
		return;
	}
	if(has<up) {
		mem[++cnt]=x;
		dfs(x+1,has+1);
		mem[cnt--]=0;
	}
	if(n-x>=up-has) dfs(x+1,has);
}
```

至于后面减去的部分。就是容斥的内容了。

大家可以自己画一个韦恩图理解一下。

![](https://cdn.luogu.com.cn/upload/pic/31926.png )

这里有一个例子：n=4

现在我们要算ans[2],也就是恰好匹配2个的T的方案数

就是黄色的部分。

红色的数字是这个区域被算cal(i)的次数。

可见，三个点的重复区域，由于有C(3,2)种方法选到，所以会被算C(3,2)次。

所以减去所有的ans[3]即可。

其他情况同理。

最后输出ans[1]

组合数打表。

理论复杂度：

O(n×len×2^15)

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=20;
const int M=52;
const int mod=1000003;
char a[N][M];
int len;
int n,t,k;
int mem[N],cnt;
ll ans[N];
ll c[N][N];
ll sum;
ll tot;//tot measures
int up;//choose 
int las;
void dfs(int x,int has){//dfs计算tot 
	if(x==n+1){
		if(has!=up) return;
		ll lp=1;
		for(int j=1;j<=len;j++){
			las=-1;
			for(int i=1;i<=up;i++){
				if(a[mem[i]][j]!='?'){
					if(las==-1){
						las=a[mem[i]][j]-'a';
					}
					else if(las!=a[mem[i]][j]-'a') return;//两个字符不一样，无合法方案 
				}
			}
			if(las==-1)lp=(lp*26)%mod;//如果都是‘？’可以随便填，否则只有一种 
		}
		(tot+=lp)%=mod;
		return;
	}
	if(has<up) {
		mem[++cnt]=x;
		dfs(x+1,has+1);
		mem[cnt--]=0;
	}
	if(n-x>=up-has) dfs(x+1,has);
}

void clear(){
	memset(ans,0,sizeof ans);
	sum=0;
	len=0;
}
int main()
{
	for(int i=0;i<=N-1;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
		}
	}
	scanf("%d",&t);
	while(t--){
		clear();//清空数组，其实没有必要 
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%s",a[i]+1);
		}
		len=strlen(a[1]+1);//长度 
		
		for(int i=n;i>=k;i--){//ans[i]计算 
			tot=0;up=i;
			dfs(1,0);
			sum=0;
			for(int j=i+1;j<=n;j++){//容斥的处理 
				(sum+=c[j][i]*ans[j])%=mod;
			}
			ans[i]=(tot-sum+mod)%mod;
		}
		printf("%lld\n",ans[k]);
	}
	return 0;
}
```

---

## 作者：sodak (赞：14)

## 思路

* 这道题是真的难想，一开始我觉得应该从行数开始枚举进行装压DP，但是看到字符串长度最大为$50$，还是算了（汗），容易爆掉，所以转换思想，枚举位数，维护数组$g[i][j]$表示第$i$个位数下放$j$的情况下该列的匹配情况，预处理好像就这些（汗）;

* 接下来就是紧张刺激的DP环节了，我们定义$f[i][j]$为$T$串已经匹配了$i$位，且与$n$个字符串是否匹配的集合为$j$，状态边界为$lim$，$f[0][lim-1]=1$,首先枚举位数，然后枚举状态，如果$f[i][j]==0$不需要进行操作，可以剪枝，然后枚举字符，在下一状态下添加字符的种类数为本状态加上下一状态的原种类数

* 最后枚举不同状态，记录该状态与原数组的匹配情况，判断该状态是否包括某一行的位数（即该行匹配），如果是则$tot++$，如果$tot=m$，叠加$f[len][当前状态]$，求解$ans$。

## 如果还不明白的话，请看代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e6+3;
const int maxn=100010;
int f[50+5][1<<15],g[50+5][30];
char s[16][50+5];
int T,n,m;
int main(){
	scanf("%d",&T);
	while(T--){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)scanf("%s",s[i]);
		int len=strlen(s[0]);
		for(int i=0;i<len;i++){//枚举位数
			for(int j=0;j<26;j++){//枚举字符
				for(int k=0;k<n;k++){//枚举行数
					if(s[k][i]=='?' || s[k][i]==j+'a')g[i][j]|=(1<<k);//位数为i时j字符的匹配情况
				}
			}
		}
		int lim=(1<<n);
		f[0][lim-1]=1;
		for(int i=0;i<len;i++){//枚举位数
			for(int j=0;j<lim;j++){//枚举状态
				if(f[i][j])//剪枝
					for(int k=0;k<26;k++){//枚举字符
						f[i+1][j&g[i][k]]=(f[i+1][j&g[i][k]]+f[i][j])%mod;
					}
			}
		}
		int ans=0;
		for(int i=0;i<lim;i++){//枚举状态
			int tot=0;
			for(int j=0;j<n;j++){
				if(i & (1<<j))tot++;
			}
			if(tot==m)ans=(ans+f[len][i])%mod;
		}
		printf("%d\n",ans);
		
	}
}
```


---

## 作者：nekko (赞：12)

一般化的题目描述：

> 有$n$个属性，求恰好满足$k$个属性的物品个数
>
> 你有一个函数$q(S)$，可以快速算出至少满足属性集合$S$的物品个数（保证每个物品最多只会被统计一次）

设$f(S)$表示只满足属性集合$S$中的物品的个数，那么答案就是$\sum_{S \subseteq U \wedge |S| = k}f(S)$

设$f(S)=\sum\limits_{S \subseteq P}q(P)g(|P|)$，其中$|S|=k$，显然有$g(x)=(-1)^{x-k}$

证明：

>对于一个物品$t$，假设它的属性集合为$Q$，且$S \subseteq Q$，且$|Q|=k+u$
>
>那么它对$f(S)$的贡献是
>$$\sum_{i=0}^{u}{u \choose i}(-1)^{i}=(-1+1)^{u}=[u=0]$$
>

也就是说$f(S)=\sum\limits_{S \subseteq P}q(P)(-1)^{|P|-k}$

也就是说
$$\begin{aligned}T&=\sum\limits_{S \subseteq U \wedge |S| = k}f(S) \\&=\sum\limits_{S \subseteq U \wedge |S| = k} \sum_{S \subseteq P}q(P)(-1)^{|P|-k} \\&=\sum\limits_{P \subseteq U \wedge |P| \ge k} q(P)(-1)^{|P|-k}{|P| \choose k}\end{aligned}$$

于是就做完了……

由于这道题的$q(S)$求法十分简单，在此就不赘述了

---

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e6 + 3;
char s[20][55];
int n, k, vis[55], len;
ll pw(ll a, ll b) {
    ll r = 1;
    for( ; b ; b >>= 1, a = a * a % mod) if(b & 1) r = r * a % mod;
    return r;
}
ll calc(int s) {
    for(int i = 1 ; i <= len ; ++ i) {
        vis[i] = 0;
    }
    for(int i = 1 ; i <= n ; ++ i) {
        if((s >> (i - 1)) & 1) {
            for(int j = 1 ; j <= len ; ++ j) {
                char c = :: s[i][j];
                if(c == '?') continue;
                if(vis[j] && vis[j] != c) {
                    return 0;
                }
                vis[j] = c;
            }
        }
    }
    
    ll res = 1;
    for(int i = 1 ; i <= len ; ++ i) {
        if(vis[i]) continue;
        res = res * 26 % mod;
    }
    
    return res;
}

int C[20][20];

void sol() {
    scanf("%d%d", &n, &k);
    for(int i = 1 ; i <= n ; ++ i) {
        scanf("%s", s[i] + 1);
    }
    len = strlen(s[1] + 1);
    int ans = 0;
    for(int s = 0 ; s < (1 << n) ; ++ s) {
        int cnt = 0;
        for(int i = 1 ; i <= n ; ++ i) {
            if((s >> (i - 1)) & 1) {
                ++ cnt;
            }
        }
        if(cnt >= k) {
            ll sig = ((cnt - k) & 1) ? -1 : 1;
            ans = (ans + sig * C[cnt][k] * calc(s)) % mod;
        }
    }
    ans = (ans % mod + mod) % mod;
    printf("%d\n", ans);
}

int main() {
    C[0][0] = 1;
    for(int i = 1 ; i < 20 ; ++ i) {
        C[i][0] = 1;
        for(int j = 1 ; j < 20 ; ++ j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    int T; scanf("%d", &T);
    while(T --) sol(); 
}
```



---

## 作者：Fading (赞：10)

这是一个非常无脑的，本菜鸡~~上文化课时~~自己想到的弱智状压，结果是对的~~只是非常慢~~，看没有人用这种写法于是我就决定发一篇qwq

### 非常无脑！

设$f[i][j]$表示有多少个串满足条件。

$j$是状态，表示答案与哪些$S$串匹配

$i$表示现在匹配到了第$i$位

比如：
$S1=a?,S2=ab,f[1][3(11)]=f[2][3(11)]=1,f[2][1(01)]=26$

然后假设我们有了$f[i][j],$如何转移到$f[i+1][???]\ \ ??????$

我们先开一个数组$hash[][]$记录每一种字符出现的位置，把$?$字符转化成$a$~$z$

比如

$S1=a$

$S2=?$

$S2=z$

那么$hash[\text{a}]=${$1,2$}，$1$来源于$S1$，$2$来源于$S2$

$hash[\text{b}]=hash[\text{c}]=...=hash[\text{y}]=${$2$}，$2$来源于$S2$

$hash[\text{z}]=${$2,3$}，$2$来源于$S2$,$3$来源于$S3$

发现，如果我们枚举$i+1$位的字符$ch$，选择$ch$之后匹配的$S$串，就是$hash[ch]!!!$ 

然后我们就可以快乐的转移了~

设$hash[ch]$有$size$个数:

$f[i+1][\sum_{i\le size}(1<<(has[ch][i]))]+=f[i][j]$

代码如下:

```
#include<bits/stdc++.h>
#define ljc 1000003
using namespace std;
inline int getit(){
	//转化 a->1,b->2,...,z->26,?->27
    char ch=getchar();
    while (!isalpha(ch)&&(ch!='?')) ch=getchar();
    if (isalpha(ch)) return ch-'a'+1;
    else return 27;
}
inline int read(){
    int x=0,f=1;char ch=getchar();
    while (!isdigit(ch)){if (ch=='-') f=-1;ch=getchar();}
    while (isdigit(ch)){x=(x<<1)+(x<<3)+ch-48;ch=getchar();}
    return x*f;
}
char s[10000];
int a[1600][5100],has[280][5100],len,T,n,m,f[51][33333];
inline int countbit(int x){
    //返回二进制数x中有多少为1
    int ans=0;
    while (x){
        if (x&1) ans++;
        x>>=1;
    }
    return ans;
}
int main(){
    T=read();
    while (T--){
        memset(f,-1,sizeof(f));
        memset(has,0,sizeof(has));
        n=read(),m=read();int ans=0;
        scanf("%s",s);len=strlen(s);
        for (int i=0;i<len;i++){
            if (isalpha(s[i])) a[1][i+1]=s[i]-'a'+1;
            else a[1][i+1]=27;
        }
        for (int i=2;i<=n;i++){
            for (int j=1;j<=len;j++){
                a[i][j]=getit();
            }
        }
		f[0][(1<<n)-1]=1;
        for (int i=0;i<len;i++){
            for (int P=0;P<(1<<n);P++){//P就是上述的j状态qwq
                if (f[i][P]==-1) continue;
                for (int k=1;k<=26;k++) has[k][0]=0;//has[i][0]表示上述的size qwq
                for (int j=1;j<=n;j++){
                	if ((P&(1<<j-1))==0) continue;
                    if (a[j][i+1]<=26) has[a[j][i+1]][++has[a[j][i+1]][0]]=j;
                    else{
                    	for (int k=1;k<=26;k++) has[k][++has[k][0]]=j;
                    }	
                }
                for (int j=1;j<=26;j++){
                    if (has[j][0]){
       		     		int rev=0;
                        for (int k=1;k<=has[j][0];k++) rev+=(1<<has[j][k]-1);
                        if (f[i+1][rev]==-1) f[i+1][rev]=0;
                        f[i+1][rev]=(f[i+1][rev]+f[i][P])%ljc;//转移
                    }
                }
            }
        }
        for (int P=0;P<(1<<n);P++){
            if (f[len][P]==-1) continue;
            if (countbit(P)==m) ans=(ans+f[len][P])%ljc;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：yuzhechuan (赞：8)

延续枫林晚大佬的容斥思想，用简单的**二项式反演**来个小小的常数优化，目前最优解rk2

---

### 题解：

二反经典套路：设 $f(i)$ 表示钦定能够匹配的是某 $i$ 个串的方案数， $g(i)$ 表示能匹配的串恰好为 $i$ 个的方案数

$f(i)$我们可以用dfs暴力搞出，而$g(k)$就是我们的答案

然后根据定义以及二项式反演转化：

$$f(n)=\sum\limits_{i=n}^m{i\choose n}g(i)\Leftrightarrow g(n)=\sum\limits_{i=n}^m(-1)^{i-n}{i\choose n}f(i)$$

于是：

$$ans=g(k)=\sum\limits_{i=k}^n(-1)^{i-k}{i\choose k}f(i)$$


---

### 代码：

```cpp
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;return x;
}
template<class t> inline void write(t x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}

const int mod=1e6+3,N=55,M=16;
char s[M][N],ch[N];
int pw[N],pn,n,m,k,f[M],c[N][N],p[N];

void dfs(int x,int cnt){ //暴力搞出f(i)
	if(n-x+1+cnt<k) return ; //范围剪枝
	if(x==n+1){
		f[cnt]+=pw[m-pn]; //累加
		if(f[cnt]>mod) f[cnt]-=mod;
		return ;
	}
	dfs(x+1,cnt);
	for(int i=0;i<m;i++) if(ch[i]&&s[x][i]>='a'&&ch[i]!=s[x][i]) return ; //ch[i]表示第i个位置上应该是哪个字母
	int now=pn;
	for(int i=0;i<m;i++) if(!ch[i]&&s[x][i]!='?') ch[i]=s[x][i],p[++pn]=i;
	dfs(x+1,cnt+1);
	while(pn>now) ch[p[pn--]]=0; //修改回去
}

void doit(){
	read(n);read(k);
	for(int i=1;i<=n;i++) scanf("%s",s[i]);
	m=strlen(s[1]);
	for(int i=k;i<=n;i++) f[i]=0;
	dfs(1,0);
	int ans=0;
	for(int i=k;i<=n;i++){
		if(i-k&1) ans+=mod-1ll*c[i][k]*f[i]%mod; //二项式反演
		else ans+=1ll*c[i][k]*f[i]%mod;
		if(ans>=mod) ans-=mod;
	}
	write(ans);puts("");
}

signed main(){
	for(int i=0;i<=15;i++){
		c[i][0]=1;
		for(int j=1;j<=i;j++){
			c[i][j]=c[i-1][j-1]+c[i-1][j];
			if(c[i][j]>mod) c[i][j]-=mod;
		}
	}
	for(int i=0;i<=50;i++) pw[i]=i?pw[i-1]*26%mod:1;
	int t;
	read(t);
	while(t--) doit();
}
```

---

## 作者：Coros_Trusds (赞：5)

[更好的阅读体验](https://www.cnblogs.com/Coros-Trusds/p/16293123.html)

状压 $\rm Dp$ 小清新题。

# 题目大意

$\rm Sheng\_bill$ 不仅有惊人的心算能力，还可以轻松地完成各种统计。在昨天的比赛中，你凭借优秀的程序与他打成了平局，这导致 $\rm Sheng\_bill$  极度的不满。于是他再次挑战你。这次你可不能输。

这次，比赛规则是这样的：

给出 $N$ 个长度相同的字符串（由小写英文字母和 `?` 组成），$S_1,S_2,\dots,S_N$，求与这 $N$ 个串中的刚好 $K$ 个串匹配的字符串 $T$ 的个数，答案对 $1000003$ 取模。

若字符串 $S_x(1\le x\le N)$ 和 $T$ 匹配，满足以下条件：

1. $|S_x|=|T|$。

2. 对于任意的 $1\le i\le|S_x|$，满足 $S_x[i]= \texttt{?}$ 或者 $S_x[i]=T[i]$。

其中 $T$ 只包含小写英文字母。

# 题目分析

令 $dp[i][s]$ 表示所有字符串匹配到第 $i$ 个字符，选择的字符串集合为 $s$ 时匹配的方案数，$g[i][ch]$ 表示在所有字符串的第 $i$ 个字符中字符 $ch$ 出现的状态集合。

初始化 $dp[0][2^n-1]=1$。

那么我们不难求出转移式：$dp[i+1][s\operatorname{and}g[i+1][ch]]\gets dp[i+1][s\operatorname{and}g[i+1][ch]]+dp[i][s]$。

注意 `?` 可以认为是任意一种字符，所以会出现在任意属于字符 $ch$ 的集合内。

# 代码

```cpp
//2022/5/20
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() std::ios::sync_with_stdio(false),std::cin.tie(0),std::cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define stop return(0)
const int mod = 1e6 + 3;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 55,M = 16;
int g[N][N],dp[N][1 << M];
//dp[i][s]:选择的字符串集合为 s,匹配到第 i 个字符时匹配的方案数
char s[M][N];
int T,n,m;
inline void init() {
	mst(dp,0),mst(g,0);
}
inline int getid(char ch) {
	return ch - 'a';
}
inline int popcount(int x) {
	int res = 0;
	while (x) {
		if (x & 1) res ++;
		x >>= 1;
	}
	return res;
}
inline void solve() {
	scanf("%d%d",&n,&m);
	for (register int i = 1;i <= n; ++ i) scanf("%s",s[i] + 1);
	int len = strlen(s[1] + 1);
	for (register int i = 1;i <= len; ++ i) {
		for (register char ch = 'a';ch <= 'z'; ++ ch) {
			for (register int j = 1;j <= n; ++ j) {
				if (s[j][i] == '?' || s[j][i] == ch) {
					g[i][getid(ch)] |= (1 << (j - 1));
				}
			}
		}
	}
	dp[0][(1 << n) - 1] = 1;
	for (register int i = 0;i < len; ++ i) {
		for (register int j = 0;j < (1 << n); ++ j) {
			if (dp[i][j] == 0) continue;
			for (register char ch = 'a';ch <= 'z'; ++ ch) {
				dp[i + 1][j & g[i + 1][getid(ch)]] = MOD(dp[i + 1][j & g[i + 1][getid(ch)]] + dp[i][j]);
			}
		}
	}
	int ans = 0;
	for (register int i = 0;i < (1 << n); ++ i) {
		if (popcount(i) == m) {
			ans = MOD(ans + dp[len][i]);
		}
	}
	printf("%d\n",ans);
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	scanf("%d",&T);
	while (T --) {
		init();
		solve();
	}

	return 0;
}
```

---

## 作者：communist (赞：5)

### 一看题解好像全是状压$DP$，那么我就来补充一个容斥写法吧

### 乍一看，好像是水题，枚举选哪$k$个串，然后判断

$\text{1，如果这k个串中\red{至少两个}串某位置确定且不相同，答案显然为0}$

$\text{2，如果这个位置只被\red{有且仅有一个}串确定，这个位置就唯一确定了}$

$\text{3，否则这个位置有26种不同填数情况，统计答案时只要用乘法原理搞一下就行}$

### 但是容易想到，这样做是有问题的，以样例的第一组数据为例

$\text{我们选定串1，2，然后发现第四个位置确定是r，其他位置任选，}$
$\text{但是无论我们构造出怎样的串，T总是可以同时匹配串3的}$

### 考虑容斥掉这些匹配到更多串的方案

#### 首先，我们可以用上述方法求出匹配至少$i$个串的方案数，记为$num[i]$

#### 我们需要统计恰好满足匹配$i$个的情况，记为$ans[i]$

#### 现在问题来了，怎么容斥

$\text{考虑ans[i]与ans[j]的联系（i>j），定义保证ans[j]是恰好匹配j个串}$

$\text{如果再匹配到i-j个串，就是ans[j]}$

$\text{在i个串中，这i-j个串的选择当然就有C(i,i-j)种方案}$

$\text{我们有num[j]，得出公式}ans[j]=num[j]-\sum{C(i,i-j)*ans[i]}$

$\text{倒序处理ans数组即可}$

### 上代码：
```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long ll;
const int mod=1000003;
int t,n,k,num[20],len,c[20][20],ans[20];
char s[20][60];
int ksm(int x,int t)
{
    int ret=1;
    while(t)
    {
        if(t&1)
            ret=(ll)ret*x%mod;
        x=(ll)x*x%mod,t>>=1;
    }
    return ret%mod;
}
int check(int x)
{
    char tmp[60];
    for(int i=0;i<len;i++)
        tmp[i]='?';
    int rest=len;
    for(int i=0;i<n;i++)
    {
        if(x&(1<<i))
            for(int j=0;j<len;j++)
                if(!isalpha(tmp[j])&&isalpha(s[i+1][j]))
                {
                    tmp[j]=s[i+1][j];
                    rest--;
                }
                else if(isalpha(tmp[j])&&isalpha(s[i+1][j])&&tmp[j]!=s[i+1][j])
                    return 0;
    }
    return ksm(26,rest);
}
int main()
{
    for(int i=0;i<20;i++){
        c[i][0]=1;
        for(int j=1;j<=i;j++){
            c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
        }
    }
    scanf("%d",&t);
    while(t--)
    {
        memset(num,0,sizeof(num));
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++)
            scanf("%s",s[i]);
        len=strlen(s[1]);
        int mul=1;
        if(k>n)
        {
            printf("0\n");
            continue;
        }
        for(int i=1;i<(1<<n);i++)
        {
            int cnt=0;
            for(int j=0;j<n;j++)
                if(i&(1<<j))
                    cnt++;
            if(cnt<k)
                continue;
            (num[cnt]+=check(i))%=mod;
        }
        for(int i=n;i>=k;i--)
        {
            int sum=0;
            for(int j=i+1;j<=n;j++)
                (sum+=(ll)c[j][i]*ans[j]%mod)%=mod;
            ans[i]=((num[i]-sum)%mod+mod)%mod;
        }
        printf("%d\n",(ans[k]%mod+mod)%mod);
    }
    return 0;
}
```

---

## 作者：zimujun (赞：4)

群友把这题当了胡策的签到题，脑洞不够大没把大家都在说的直接容斥的正确性想出来，所以我写了个高维后缀差分，它也是对的。

----

先考虑求出对于每个字符串的集合 $T$ 求出**至少**满足这个集合中字符串的限制的答案总数 $f(T)$，这个好做，直接看看哪些位上被确定必须选某个字符即可。另外设一个**恰好**满足 $S$ 中限制的答案总数为 $g(S)$，则 $f(T) = \displaystyle\sum_{T \subset S}g(S)$ 即为所有 $T$ 的超集 $S$ 的恰好的答案之和，其实就是说 $f$ 是 $g$ 的子集后缀和，本质上是个高维后缀和，做一下它的逆运算即可得到 $g$ 数组，具体实现就是做一遍 $\operatorname{and}$ 卷积的 idmt。

最后答案即为 $\displaystyle\sum_{\operatorname{popcount(S)} = k}g(S)$。

---

## 作者：凑个热闹吖 (赞：1)

### [[SDOI2009]Bill的挑战](https://www.luogu.com.cn/problem/solution/P2167)

这道题可以运用容斥原理解决。

这里尝试对第一篇题解的那条公式作出更容易理解的解释。

# solution

我们设 $Ans_i$ 表示**恰好**与 $i$ 个字符串匹配的字符串 $T$ 的个数。

从 $n$ 个字符串里选出 $i$ 个字符串为一组，记与这一组所有字符串匹配的字符串个数为 $cnt$，用 $calc_i$ 记所有组的 $cnt$ 总和。

用暴力可以在 $O(2^nlen \times i)$ 的时间复杂度内求出 $calc_i$，代码如下。

```cpp
int cnt;
int Solve(string state){
	int x = 1;
	rep(i , 0 , len - 1)
		(x *= (state[i] == '?') ? 26 : 1) %= MOD;
	return x;
}
void dfs(int adr , int num , string state , int lim){
	if(num == lim){
		(cnt += Solve(state)) %= MOD;
		return;
	}
	if(adr > n)return;
	dfs(adr + 1 , num , state , lim);
	bool flag = true;
	rep(i , 0 , len - 1){
		if(state[i] != '?' && s[adr][i] != '?' && s[adr][i] != state[i])flag = false;
		if(s[adr][i] != '?')state[i] = s[adr][i];
	}
	if(!flag)return;
	dfs(adr + 1 , num + 1 , state , lim);
}
int calc(int num){
	string state = "";
	cnt = 0;
	rep(i , 0 , len - 1)state += '?';
	dfs(1 , 0 , state , num);
	return cnt;
}
```

现在考虑 $Ans_i$ 的求法。

举个例子便于理解。

```
4 2
a????
?b???
??c??
???d?
```
假设现在 $Ans_3$，$Ans_4$ 均已求出。

我们一开始令 $Ans_2=calc_2$。

在 $calc_2$ 中，`abcdd` 这个字符串一共被累计了 $6$ 次（`{a????,?b???}`、`{a????,??c??}`、`{a????,???d?}`、`{?b???,??c??}`、`{?b???,???d?}`、`{??c??,???d?}` 这 $6$ 组字符串中都累计了一次），但显然 `abcdd` 这个字符串不应该统计在 $Ans_2$ 里面，因为它恰好可以与 $4$ 个字符串进行匹配，而不是恰好可以和 $2$ 个字符串匹配。

所以对于 `abcdd` 这个字符串，我们应该用 $Ans_2$ 减去 $C_{4}^{2}$。

那有多少个类似于 `abcdd` 这样可以与 $4$ 个字符串进行匹配的字符串呢？显然有 $Ans_4$ 个。

同样的，对于例如 `abccd` 这种可以和 $3$ 个字符串匹配的字符串，我们应该用 $Ans_2$ 减去 $C_{3}^{2}Ans_3$。

于是我们最终可以得到下面这条公式：

$$Ans_i=calc_i - \sum_{i < j \leqslant n}Ans_j$$

最后输出 $Ans_k$ 即可。

# code

```cpp
#include<bits/stdc++.h>
#define rep(i , m , n) for(register int i = m; i <= n; i++)
#define drp(i , m , n) for(register int i = n; i >= m; i--)

using namespace std;
const int MOD = 1000003;
int G;
int n , k;
int c[20][20];
int len;
int ans[20];
string s[20];
void YHSJ(){
	c[1][0] = c[1][1] = 1;
	rep(i , 2 , 15)
		rep(j , 0 , i)
			c[i][j] = (j == '0') ? 1 : (c[i - 1][j - 1] + c[i - 1][j]);
}
int cnt;
int Solve(string state){
	int x = 1;
	rep(i , 0 , len - 1)
		(x *= (state[i] == '?') ? 26 : 1) %= MOD;
	return x;
}
void dfs(int adr , int num , string state , int lim){
	if(num == lim){
		(cnt += Solve(state)) %= MOD;
		return;
	}
	if(adr > n)return;
	dfs(adr + 1 , num , state , lim);
	bool flag = true;
	rep(i , 0 , len - 1){
		if(state[i] != '?' && s[adr][i] != '?' && s[adr][i] != state[i])flag = false;
		if(s[adr][i] != '?')state[i] = s[adr][i];
	}
	if(!flag)return;
	dfs(adr + 1 , num + 1 , state , lim);
}
int calc(int num){
	string state = "";
	cnt = 0;
	rep(i , 0 , len - 1)state += '?';
	dfs(1 , 0 , state , num);
	return cnt;
}
int main(){
	cin >> G;
	YHSJ();
	while(G--){
		memset(ans , 0 , sizeof ans);
		cin >> n >> k;
		rep(i , 1 , n)cin >> s[i];
		len = s[1].size();
		drp(i , k , n){
			int tot = 0;
			rep(j , i + 1 , n)
				(tot += c[j][i] * ans[j]) %= MOD;
			ans[i] = (calc(i) - tot + MOD) % MOD;
		}
		cout << ans[k] << '\n';	
	}
	return 0;
}
```


---

## 作者：OIer_ACMer (赞：0)

~~Hello 状压！~~

------------
## 警钟敲烂：
1. 给那些想要压维度的人提个醒：不要吝啬自己的空间，放开去开~~不然就会像我一样改了将近 $30$ 分钟~~。

2. 一定要记得取模~~在这地方我又卡了 $20$ 分钟~~。

------------
## 大致思路：
本题一开始我想用 $dp[sta]$ 表示此时到了 $sta$ 状态时有多重可以匹配的字符串 $T$，那个状态就是我们常说的二进制序列（这个要是不知道建议参看[状压 DP 详解](https://oi-wiki.org/dp/state/)），但很显然，这是个错的想法，因此，我~~改头换面~~重新思考，决定新开一个维度，因此，我们的旅程正式开始！

我们定义 $dp[i][sta]$ 为考虑到了字符串的第 $i$ 位，当前选的状态是 $sta$ 时，方案数是多少。这样才满足了写转移方程的条件。

接着，我们开是考虑如何转移。首先我们的状态肯定是要转移到某个 $dp[i + 1][nxt]$ 上去，那么这个 $nxt$ 又是个什么东东呢？这时，我们就需要我们的辅助数组——$f$ 数组登场了！我们设 $f[i][j]$ 表示在当前字符串的第 $i$ 位上，这一位可以与 $j$ 字符对应的字符有哪些。我们考虑每个 $j$，这一位啥时候可以与别的匹配，比较显然，要么这一位是问号要么这一位是和 $j$ 一样的字符。有了这些我们就可以直接双层循环枚举每一个字符串的第 $i$ 位是否与字符 $j$ 符合，预处理即可。

有了 $f$ 数组的与处理结果，我们就可以轻松写出转移方程了：

$dp[i + 1][sta \operatorname{and} f[i +1][ch]] = dp[i + 1][sta \operatorname{and} f[i +1][ch]] + dp[i][sta]$。

至于那个 $ch$ 的意思是 $26$ 个字母一一遍历得到的结果，因为你要组合来得到 $T$ 字符串嘛。

那么最后的答案就是对于每一个状态 $sta$ 二进制下 $1$ 的个数恰好为 $k$ 的所有的 $dp[len][sta]$ 之和。其中 $len$ 表示每一个字符串的长度。

------------
## 代码如下：

```c++
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    register int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int mod = 1000003;
const int maxn = 16;
const int maxm = 51;
string s[maxn];
int f[maxm][maxm], dp[maxm][1 << maxn], val[1 << maxn];
int main()
{
    int t;
    t = read();
    while (t--)
    {
        int n, k;
        n = read();
        k = read();
        memset(dp, 0, sizeof(dp));
        memset(f, 0, sizeof(f));
        memset(val, 0, sizeof(val));
        for (int i = 0; i < n; i++)
        {
            cin >> s[i], s[i] = '%' + s[i];
        }
        int len = s[0].size() - 1;
        for (int sta = 0; sta < (1 << n); sta++)
        {
            for (int i = 0; i < n; i++)
            {
                if (sta & (1 << i))
                {
                    val[sta]++;
                }
            }
        }
        for (int i = 1; i <= len; i++)
        {
            for (char ch = 'a'; ch <= 'z'; ch++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (s[j][i] == '?' || s[j][i] == ch)
                    {
                        f[i][ch - 'a'] |= (1 << j);
                    }
                }
            }
        }
        dp[0][(1 << n) - 1] = 1;
        for (int i = 0; i < len; i++)
        {
            for (int sta = 0; sta < (1 << n); sta++)
            {
                if (!dp[i][sta])
                {
                    continue;
                }
                for (char ch = 'a'; ch <= 'z'; ch++)
                {
                    (dp[i + 1][sta & f[i + 1][ch - 'a']] += dp[i][sta]) %= mod;
                }
            }
        }
        int ans = 0;
        for (int sta = 0; sta < (1 << n); sta++)
        {
            if (val[sta] == k)
            {
                (ans += dp[len][sta]) %= mod;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/122250293)

---

## 作者：ktq_cpp (赞：0)

这道题我们可以令 dp[i][j] 为在状态j下第i位可以选的方案数

但仔细想一想会发现这样没有考虑到当问号串中有明确字母的情况。一开始我的思路是容斥，但我数学太菜了，不会搞。所以后来可以预处理出在第 i 位时，字母是 j 的情况一共有哪些字符串，然后根据这个存在数组 g[i][j] 里。

然后我们便可以推出公式

```latex
dp[i][j&g[i][k]]=(dp[i][j&g[i][k]]+dp[i-1][j])
```


代码如下

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T;
int g[55][31];
int dp[55][40001];
const int mod=1e6+3;
char s[16][52];
int solve(){
    int n,k;
    scanf("%lld %lld",&n,&k);
    
    int ans=0;
    scanf("%lld %lld",&n,&k);
    //cout<<n<<k<<endl;
    memset(dp,0,sizeof(dp));
    memset(g,0,sizeof(g));
    //cout<<1<<endl;
    for(int i=1;i<=n;i++)
        scanf("%s",s[i]+1);
    int len=strlen(s[1]+1);
    for(int i=1;i<=len;i++){
        for(int j=0;j<26;j++){
            for(int k=1;k<=n;k++){
                //cout<<1<<endl;
                if(s[k][i]=='?'||s[k][i]==j+'a')g[i][j]|=(1<<k-1);
            }
        }
    }
    int sum=1<<n;
    sum--;
    dp[0][sum]=1;
    //cout<<len<<endl;
    for(int i=1;i<=len;i++){
        for(int j=0;j<=sum;j++){
            if(dp[i-1][j]){
                for(int k=0;k<26;k++){
                    dp[i][j&g[i][k]]=(dp[i][j&g[i][k]]+dp[i-1][j])%mod;
                }
            }
        }
    }
    for(int i=0;i<=sum;i++){
        int x=i,chk=0;
        while(x){
            if(x&1)chk++;
            x=x>>1;
        }
        if(chk==k)ans=(ans+dp[len][i])%mod;
        //cout<<dp[len][i]<<endl;
    }
    printf("%lld\n",ans);
    return 0;
}
signed main(){
    scanf("%lld",&T);
    //cout<<1<<endl;
    while(T--){
        //cout<<1<<endl;
        solve();
    }
    return 0;
}
```


---

## 作者：fanypcd (赞：0)

数据规模与约定:

对于 $100\%$ 的数据，$1\le T\le 5,1\le N \le15$

一眼状压无疑了。

然后就比较自然地想到将能够匹配的压到一个集合 $S$ 中。

状态设计：$f_{i,S}$ 表示当前匹配到第 $i$ 个字符，能够匹配的字符串集合为 $S$ 的字串个数。

转移就比较显然了：$f_{i+1,S \cap S'}=\sum \limits_{ch=\texttt{a}} ^{\texttt{z}}f_{i,S}$ （其中 $S'$ 表示只考虑第 $i + 1$ 位取 $ch$ 能匹配的字符串集，与原有的能匹配的字符串集 $S$ 求交就是当前这位取 $ch$ 时前 $i + 1$ 位都能匹配的字符串集）。

然后考虑将所有的 $S'$ 预处理出来，记 $g_{i,ch}$ 表示第 $i$ 位取字符 $ch$ 时当前这位能匹配的字符串集。

然后转移方程就是： 

$$f_{i+1,S \cap {g_{i+1,ch}}}= \sum \limits_{ch=\texttt{a}} ^{\texttt{z}} f_{i,S}$$

显然 $O(26\times2^n\times m)$，能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline void read(int &x)
{
	x = 0;
	int f = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9')
	{
		f |= ch == '-';
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9')
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	x = f ? -x : x;
	return;
}
const int mod = 1000003;
#define N 16
#define M 55
int n, m, k;
char s[N][M];
int f[M][1 << N], g[M][26];
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		read(n), read(k);
		for(int i = 1; i <= n; i++)
		{
			scanf("%s", s[i] + 1);
		}
		m = strlen(s[1] + 1);
		memset(f, 0, sizeof(f)), memset(g, 0, sizeof(g));
		for(int i = 1; i <= m; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				for(int ch = 0; ch < 26; ch++)
				{
					if(s[j][i] - 'a' == ch || s[j][i] == '?')
					{
						g[i][ch] |= (1 << (j - 1));
					}
				}
			}
		}
		f[0][(1 << n) - 1] = 1;
		for(int i = 0; i < m; i++)
		{
			for(int state = 0; state < (1 << n); state++)
			{
				if(!f[i][state])
				{
					continue;
				}
				for(int ch = 0; ch < 26; ch++)
				{
					f[i + 1][state & g[i + 1][ch]] = (f[i + 1][state & g[i + 1][ch]] + f[i][state]) % mod;
				}
			}
		}
		int ans = 0;
		for(int state = 0; state < (1 << n); state++)
		{
			int tot = 0;
			for(int i = 0; i < n; i++)
			{
				if(state & (1 << i))
				{
					tot++;
				}
			}
			if(tot == k)
			{
				ans = (ans + f[m][state]) % mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：摸鱼酱 (赞：0)

[更好的阅读体验](https://www.moyujiang.com/969.html)

题意：

给定 $n$ 个长度为 $l$ 的字符串 $s_{1...n}$，串由小写字母和字符 `?` 构成，定义串 $s_x$ 和串 $t$ 匹配，当且仅当满足：

 - $|t|=l$
 - $\forall i\in[1,l],t[i]=s_x[i]\text或s_x[i]= ?$

求有多少个串 $t$ 恰好匹配 $k$ 个 $s_x$。

$1\leq n\leq15,1\leq l\leq50,k≥1$。

这数据范围爆搜就好了。

枚举选 $k$ 个串匹配，每个位置要么有固定的字母，要不就全是 `?`，统计一下即可。这一步是爆搜，时间复杂度 $O(2^n*n*l)$

但是发现它可能不一定只匹配了枚举的这 $k$ 个串，比如 $5$ 个串的所有元素都是 `?`， $k=1$，答案就是 $0$。

于是我们发现，刚刚枚举的是**至少**匹配我们选择的 $k$ 个串的串数，而题目要求的是**恰好**匹配 $k$ 个串的串数，所以套个二项式反演就好了。

[二项式反演基础](https://www.moyujiang.com/968.html)

[完整代码Link](https://www.luogu.com.cn/paste/yo3j3wo9)
 
还是蛮快的，我这样的大常数选手都能不开 O2 卡进最优解第一页。

---

## 作者：Stinger (赞：0)

# [某客食用体验更佳](

[某送门](https://www.luogu.com.cn/problem/P2167)

~~看数据范围是一种优良的传统~~，本题 $N\leq 15$，状压无疑了QAQ。

然后我们看到：**刚好与 $K$ 个串匹配的个数**，就想到了容斥。

~~感觉自己思维好跳跃啊不过似乎也是正常思路？~~

由于是与 $K$ 个串匹配，不能单纯的“奇加偶减”，我们用 $f[i]$ 表示恰好与 $K$ 个串匹配的串的个数，$Cnt[i]$ 表示与**至少** $K$ 个串匹配的串的个数。

画几个韦恩图（~~不过挺难画的~~），可以发现对于每个表示与至少 $K$ 个串匹配的个数的“圆圈”都有交集，所以我们依次减去这些交集：

$f[i]=Cnt[i]-\sum\limits^N_{i+1} C[j][i] * f[j]$

对于 $Cnt$ 数组的计算，要根据每个字符串的集合算出它们的交集，然后根据这些集合表示的字符串的个数来判断应该把它加到哪个 $Cnt$ 中，这个过程很简单，详见代码（话说这个部分我开始以为自己的思路有问题，又是debug又是在草稿纸上画来画去，最后看了题解一怒之下删了 $^{tm}$ 一大段代码直接 $A$ 了。（~~枯了~~）

码风贼丑，见谅。

# $Code:$

```cpp
#include <cstdio>
#include <cstring>
#define MOD 1000003
#define MAXS 1 << 16
#define lowbit(x) (x & ~x + 1)
#define max(x, y) (x > y ? x : y)

char S[16][51], Union[MAXS][51];
int Pow[51] = {1}, Log[MAXS], bitlen[MAXS], C[16][16], f[16], Cnt[20];
bool vis[MAXS];

int main() {
	for (int i(1); i <= 50; ++ i) Pow[i] = Pow[i - 1] * 26 % MOD;
	for (int i(0); i < 16; ++ i) Log[1 << i] = i;
	for (register int i(1); i < MAXS; ++ i) bitlen[i] = bitlen[i ^ lowbit(i)] + 1;
	for (int i(0); i <= 15; ++ i) {
		C[i][0] = 1;
		for (int j(1); j <= i; ++ j) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}
	int T;
	scanf("%d", &T);
	while (T --) {
		int N, K, len;
		scanf("%d%d", &N, &K);
		memset(vis, 0, sizeof(vis)), memset(Cnt, 0, sizeof(Cnt));
		for (register int i(0); i < N; ++ i) scanf("%s", S[i]);
		len = strlen(S[0]);
		memset(Union, '\0', sizeof(Union));
		for (register int i(0); i < 50; ++ i) Union[0][i] = '?';
		
		for (register int i(1); i < 1 << N; ++ i) {
			if (!vis[i ^ lowbit(i)]) strcpy(Union[i], Union[i ^ lowbit(i)]);
			else {vis[i] = true; continue;}
			
			register char * s(S[Log[lowbit(i)]]), * Uni(Union[i]);
			for (register int j(0); j < len; ++ j)
			if (Uni[j] != '?' && s[j] != '?' && Uni[j] != s[j]) {vis[i] = true; break;}
			else if (s[j] != '?') Uni[j] = s[j];
		}
		
		for (register int i(1); i < 1 << N; ++ i) if (!vis[i] && bitlen[i] >= K) {
			int cnt(0);
			for (register int j(0); j < len; ++ j) if (Union[i][j] == '?') ++ cnt;
			(Cnt[bitlen[i]] += Pow[cnt]) %= MOD;
		}
		
		for (int i(N); i >= K; -- i) {
			f[i] = Cnt[i];
			int sum(0);
			for (int j(i + 1); j <= N; ++ j)
			sum += C[j][i] * f[j], sum = (sum + MOD) % MOD;
			f[i] = ((f[i] - sum) % MOD + MOD) % MOD;
		}
	 	printf("%d\n", f[K]);
	}
}
````

---

## 作者：tzc_wk (赞：0)

> 洛谷 P2167

> 题意：给出 $n$ 个含问号，并且长度相等的字符串，求有多少个长度与它们相等的字符串，能够与这 $n$ 个字符串中恰好 $k$ 个匹配。答案对 $10^6+3$ 取模。

> $1 \leq n \leq 15$，字符串长度不超过 $50$。

为什么大佬都喜欢用容斥啊 /yiw，一个用状压 dp 的小蒟蒻瑟瑟发抖 /fad

看到 $1 \leq n \leq 15$ 自然可以想到状压。我们考虑一位一位地填充。$dp[i][j]$ 表示填充到第 $i$ 位，可以匹配的字符串集合为 $j$ 的方案数。

那么我们枚举第 $i$ 位填的什么字符，然后再枚举每个字符串看看哪些字符串是否能够与它匹配，假设表示为二进制集合为 $t$，那么可以从 $dp[i-1][j]$ 转移到 $dp[i][j\&t]$，其中 $\&$ 为按位与。

边界 $dp[0][2^n-1]=1$

最终要求的答案就是 $\sum dp[k][s]$ 其中 $k$ 为字符串长度，$s$ 的二进制中 $1$ 的个数刚好为 $m$。

不过这样是 $\mathcal O(26 \times 2^n \times n \times m)$ 的，还是没法过去。但是发现转移到时候的状态集合 $t$ 与当前的状态无关。因此只要预处理出状态集合 $t$ 就可以省去一个 $n$ 了。

~~又水了一片题解。~~

```cpp
//Coded by tzc_wk
/*
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n,m,k,dp[55][32768],msk[55][26];
char s[17][55];
const int MOD=1e6+3;
inline void solve(){
	n=read(),k=read();
	fz(i,1,n)	scanf("%s",s[i]+1);
	m=strlen(s[1]+1);
	fill0(dp);fill0(msk);
	int whole=(1<<n)-1;
	dp[0][whole]=1;
	fz(i,1,m){
		for(int j=0;j<26;j++){
			for(int o=1;o<=n;o++){
				if(s[o][i]=='?'||s[o][i]-'a'==j){
					msk[i][j]|=(1<<(o-1));
				}
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<(1<<n);j++){
			for(int l=0;l<26;l++){
				int nt=j&msk[i+1][l];
				dp[i+1][nt]+=dp[i][j];
				if(dp[i+1][nt]>=MOD)	dp[i+1][nt]-=MOD;
			}
		}
	}
	int ans=0;
	for(int i=0;i<(1<<n);i++){
		if(__builtin_popcount(i)==k){
			ans=(ans+dp[m][i])%MOD;
		}
	}
	cout<<ans<<endl;
}
signed main(){
	int T=read();
	while(T--)	solve();
	return 0;
}
```

---

## 作者：_louhc (赞：0)

# 思路

$f[i][j]$表示第$i$位匹配$j$(二进制表示的)字符串。  
然后预处理一下每一位的每一个字符能匹配哪些字符串(还是二进制表示),下面代码中即为$mc$。  
状态转移方程即为
$$f[i][j]=\sum_{k \& mc[i]['a'...'z'] = j}f[i - 1][k]$$
也许一般DP的写法并不是很好写,具体参考代码的写法好了。  
滚动数组速度会变快是什么鬼)  
我的代码目前大概是全谷写状压DP里面跑得最快的了,抢到rk2,rk1的巨佬看起来是写容斥的)  

# 代码

```cpp
#include<cstdio>
#include<cctype>
#include<ctime>
#include<cmath>
#include<cstring>
#define u32 unsigned
#define i64 long long
#define u64 unsigned long long
#define f80 long double
#define rgt register
using namespace std;
#define mod 1000003

template<typename T>
inline void read( rgt T &x ){ x = 0; rgt char t, flg(0);
    for ( t = getchar(); !isdigit(t); t = getchar() ) flg = t == '-';
    for ( ; isdigit(t); t = getchar() ) x = x * 10 + ( t & 15 ); x = flg ? -x : x;
}

clock_t __t_bg, __t_ed;

int T, N, L, K, M;
char s[17][55];
int mc[55][30], f[2][1<<15], cr, nx, cnt[1<<15];
inline void dec( rgt int &x ){ x = x >= mod ? x - mod : x; }

signed main(){
    __t_bg = clock();
    read(T), M = 1 << 15;
    for ( rgt int i = 1; i < M; ++i ) cnt[i] = cnt[i >> 1] + ( i & 1 );
    while( T-- ){
        read(N), read(K), memset( mc, 0, sizeof mc );
        for ( rgt int i = 0; i < N; ++i )
            scanf( "%s", s[i] + 1 );
        L = strlen(s[0] + 1);
        for ( rgt int i = 0; i < N; ++i )
            for ( rgt int w = 1; w <= L; ++w )
                for ( rgt char j = 'a'; j <= 'z'; ++j )
                    if ( s[i][w] == '?' || s[i][w] == j )
                        mc[w][j & 31] |= 1 << i;
        M = 1 << N, memset( f[0], 0, M << 2 ), f[0][M - 1] = 1, cr = 0, nx = 1;
        for ( rgt int l = 0; l < L; ++l, cr = !cr, nx = !nx ){
            memset( f[nx], 0, M << 2 );
            for ( rgt int i = 0; i < M; ++i ) if ( f[cr][i] && cnt[i] >= K ){
                for ( rgt char j = 'a'; j <= 'z'; ++j )
                    dec( f[nx][i & mc[l + 1][j & 31]] += f[cr][i] );
            }
        } rgt int ans(0);
        for ( rgt int i = 0; i < M; ++i ) if ( cnt[i] == K ) dec( ans += f[cr][i] );
        printf( "%d\n", ans );
    }
    __t_ed = clock(), fprintf( stderr, "time: %.5lfs\n", double( __t_ed - __t_bg ) / CLOCKS_PER_SEC );
    return 0;
}
```

---

## 作者：wsy_jim (赞：0)

P2167 Bill的挑战

题意：给定 $n$ 个长度相同的只含小写字母和 `?` 的字符串，求与这 $n$ 个字符串中的恰好 $k$ 个字符串匹配的字符串的个数，匹配指的是每一个位置的字母都相同 ，`?` 可以代替所有小写字母，数据范围：$1\leq T\leq 5,1\leq n\leq 15,1\leq |S_i|\leq 50$ 

首先我们假设求出了可以快速得到至少与集合 $S$ 内的字符串匹配的字符串个数的函数 $q(S)$，接下来就是猜容斥系数环节，先列出式子

设 $f(S)$ 为恰好只与集合内的字符串匹配的字符串个数，那么答案就是 $\sum_{S\subseteq U\land |S|=k} f(S)$ 

$f(S)=\sum_{S\subseteq P\subseteq U}q(P)g(|P|)$ 其中 $|S|=k$，有 $g(x)=(-1)^{x-k}$，为啥呢？

对于一个答案字符串，假设它可以和 $Q$ 集合内的字符串匹配，且 $S\subseteq Q$，$|Q|=k+u$，那么它对 $f(S)$ 的贡献是 $\sum_{i=0}^u\binom ui(-1)^i=(-1+1)^u=[u=0]$，里面的 $(-1)^i$ 就可以充当容斥系数啦

于是 $f(S)=\sum_{S\subseteq P\subseteq U} q(P)(-1)^{|P|-k}$，于是：

$$
\begin{aligned}
ans=&\sum_{S\subseteq U\land |S|=k} f(S)\\
=&\sum_{S\subseteq U\land |S|=k} \sum_{S\subseteq P\subseteq U} q(P)(-1)^{|P|-k}\\
=&\sum_{P\subseteq U\land |P|\geq k} q(P)(-1)^{|P|-k}\binom {|P|}k
\end{aligned}
$$

大力容斥

$q(S)$ 直接看看 $S$ 里面的字符串匹配情况，如果不能匹配就是 $0$，有多少个全是 `?`，就是 $26$ 的多少次方

码：
```cpp

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#define N 100010
#define int long long
#define re register
using namespace std;
template<typename T>
inline void read(T &x){
    x=0;bool flg=0;char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') flg=1;
    for(;isdigit(c);c=getchar()) x=x*10+(c^48);
    if(flg) x=-x; 
}
const int Mod=1000003;

int T,n,m,k,all=0,ans=0;
int jc[N],bit[N];
char str[30][60];

int fpow(int a,int b){
    int res=1%Mod;a%=Mod;
    for(;b;b>>=1,a=a*a%Mod) if(b&1) res=res*a%Mod;
    return res%Mod;
}

int calc(int S){
    int res,sum=m;
    int s[60];
    memset(s,0,sizeof s);
    res=jc[bit[S]]*fpow(jc[k],Mod-2)%Mod*fpow(jc[bit[S]-k],Mod-2)%Mod;
    for(int i=1;i<=n;i++){
        if(S&(1<<(i-1))){
            for(int j=1;j<=m;j++){
                if(str[i][j]=='?'||str[i][j]==s[j]) continue;
                if(!s[j]){s[j]=str[i][j];sum--;continue;}
                return 0;
            }
        }
    }
    (res*=fpow(26,sum))%=Mod;
    if((bit[S]-k)%2) return (-res+Mod)%Mod;
    else return (res+Mod)%Mod;
}

signed main(){

    jc[0]=1;
    for(int i=1;i<=15;i++) jc[i]=jc[i-1]*i%Mod;
    for(int i=0;i<(1<<15);i++) bit[i]=bit[i>>1]+(i&1);

    read(T);
    while(T--){
        ans=0;
        read(n);read(k);
        all=(1<<n);
        for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
        m=strlen(str[1]+1);
        for(int i=0;i<all;i++){
            if(bit[i]<k) continue;
            (ans+=calc(i)+Mod)%=Mod;
        }
        printf("%lld\n",ans);
    }

    

    return 0;
}

```

---

