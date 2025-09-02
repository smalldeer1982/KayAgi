# SUBST1 - New Distinct Substrings

## 题目描述

 Given a string, we need to find the total number of its distinct substrings.

## 样例 #1

### 输入

```
2
CCCCC
ABABA```

### 输出

```
5
9```

# 题解

## 作者：Mars_Dingdang (赞：4)

后缀数组模板应用，与 SP694 相同。

## 题目大意
给定一个长度为 $n \le 50000$ 的字符串，求字符串中本质不同的子串个数。

## 大体思路
考虑用后缀数组。由于每一个子串一定是一个后缀的前缀，因此本质不同的子串个数问题可以转化为所有后缀之间不同前缀的个数。

考虑排名为 $i$ 的后缀，其长度为 $n-sa_i+1$。由定义可知，$height_i$ 表示排名为 $i$ 与 $i-1$ 的后缀的最长公共前缀，即重复的前缀个数，所以该后缀的贡献为 $(n-sa_i+1)-height_i$。因为所有后缀按照字典序排序，不存在某一前缀 $S'$ 不为排名为 $i, i-1$ 的公共前缀，却为 $i, i-k(k>1)$ 的公共前缀，所以上述贡献不重不漏。

当然，也可以利用容斥原理，所有的子串个数为 $\dfrac{n(n+1)}2$，减去重复子串个数 $\sum height_i$ 即可。

总而言之，答案为
$$\sum_{i=1}^n (n-sa_i+1)-height_i=\dfrac{n(n+1)}2-\sum_{i=1}^n height_i$$

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 50000 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
int T, n, m;
char s[maxn];
int x[maxn], y[maxn], cnt[maxn], sa[maxn], rk[maxn], height[maxn];
inline void getSA() {
	rep(i, 1, n) cnt[x[i] = s[i]] ++;
	rep(i, 2, m) cnt[i] += cnt[i - 1];
	Rep(i, n, 1) sa[cnt[x[i]] --] = i;
	for(int k = 1; k <= n; k <<= 1) {
		int tot = 0;
		rep(i, n - k + 1, n) y[++tot] = i;
		rep(i, 1, n)
			if(sa[i] > k) y[++tot] = sa[i] - k;
		rep(i, 1, m) cnt[i] = 0;
		rep(i, 1, n) cnt[x[i]] ++;
		rep(i, 2, m) cnt[i] += cnt[i - 1];
		Rep(i, n, 1) sa[cnt[x[y[i]]] --] = y[i], y[i] = 0;
		swap(x, y);
		x[sa[1]] = 1, tot = 1;
		rep(i, 2, n)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++tot;
		if(tot == n) break;
		m = tot;
	}
}
inline void getH() {
	rep(i, 1, n) rk[sa[i]] = i;
	for(int i = 1, k = 0; i <= n; i ++) {
		if(rk[i] == 1) continue;
		if(k) k --;
		int j = sa[rk[i] - 1];
		while(j + k <= n && i + k <= n && s[i + k] == s[j + k]) k ++;
		height[rk[i]] = k;
	}
}
inline void solve() {
	memset(sa, 0, sizeof sa);
	memset(cnt, 0, sizeof cnt);
	memset(height, 0, sizeof height);
	memset(rk, 0, sizeof rk); // 多测清空
	scanf("%s", s + 1);
	n = strlen(s + 1), m = 128;
	getSA(); getH();
	ll ans = 0;
	rep(i, 1, n) 
		ans += (ll)(n - sa[i] + 1 - height[i]);
	writeln(ans);
}
int main () {
	scanf("%d", &T);
	while(T --) solve();	
	return 0;
}
```

---

## 作者：Polaris_Australis_ (赞：3)

[传送门](https://www.luogu.com.cn/problem/SP705)

来交一个广义后缀自动机的题解。

这题需要用到一个后缀自动机的性质：设 $minlen[i]$ 表示 $i$ 节点所表示的 $endpos$ 等价类中最短串的长度， $len[i]$ 表示 $i$ 节点所表示的 $endpos$ 等价类中最长串的长度， $fa[i]$ 表示 $i$ 节点在 parent tree 上的父亲，则：

$$
\begin{aligned}
minlen[i]=len[fa[i]]+1
\end{aligned}
$$

有了这个结论，这题就有解决方法了，一个 $endpos$ 等价类 $i$ 中本质不同的子串个数为 $len[i]-minlen[i]+1$ ，并且不同的 $endpos$ 等价类中所含子串一定不同，所以遍历所有 $endpos$ 等价类，统计答案即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Std
{
    int k,n,ans;
    char s[50010];
    int fa[100010],len[100010],tot=1,lst=1,son[100010][26];
    template<typename tp>void read(tp &x);
    template<typename tp>void write(tp x);
    void insert(int x);
    void add(int x,int y);
    void dfs(int x);
    template<typename tp>void read(tp &x)
    {
        x=0;
        tp nev=1;
        char c=getchar();
        while(c<'0'||c>'9')
        {
            if(c=='-')nev=-1;
            c=getchar();
        }
        while(c>='0'&&c<='9')
        {
            x=(x<<1)+(x<<3)+(c^48);
            c=getchar();
        }
        x*=nev;
    }
    template<typename tp>void write(tp x)
    {
        if(x<0)
        {
            putchar('-');
            write(-x);
            return;
        }
        if(x/10)write(x/10);
        putchar((x%10)^48);
    }
    void insert(int x)
    {
        int p=lst,np=lst=++tot;
        len[np]=len[p]+1;
        memset(son[np],0,sizeof(son[np]));
        while(p&&(!son[p][x]))
        {
            son[p][x]=np;
            p=fa[p];
        }
        if(!p)fa[np]=1;
        else
        {
            int q=son[p][x];
            if(len[q]==len[p]+1)fa[np]=q;
            else
            {
                int nq=++tot;
                memcpy(son[nq],son[q],sizeof(son[nq]));
                fa[nq]=fa[q];
                len[nq]=len[p]+1;
                fa[q]=fa[np]=nq;
                while(p&&son[p][x]==q)
                {
                    son[p][x]=nq;
                    p=fa[p];
                }
            }
        }
    }
    int main(void)
    {
        read(k);
        while(k--)
        {
            memset(son[1],0,sizeof(son[1]));
            scanf("%s",s+1);
            n=strlen(s+1);
            tot=lst=1;
            for(int i=1;i<=n;++i)insert(s[i]-'a');
            ans=0;
            for(int i=2;i<=tot;++i)
            {
                ans+=len[i]-len[fa[i]];
            }
            printf("%lld\n",ans);
        }
        return 0;
    }
}
#undef int
int main(int argc,char *argv[])
{
    return Std::main();
}

```


---

## 作者：Fading (赞：3)

这么模版的题目居然没有 SAM 题解？？？？？

那么我来水一发吧！

前置知识:后缀自动机 SAM

根据 parent 树的性质，我们知道根节点~$i$节点本质不同的串个数为$
\text{len}_i-\text{len}_{\text{parent}_i}$

然后我们一边插入字符一边添加答案就好了。

事实上一边插入一边添加得到的答案也是对的，具体证明可以考虑 SAM 建虚节点的过程。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int n;
long long ans;
char s[1000001];
struct Suffixautomaton{
    struct edge{
        int to,next;
    }e[3000001];
    int cnt=1,last=1,g[2000001][27],ANS,pa[2000001],len[2000001],tot;
    inline void insert(int ch){
        int pos=last,newp=++cnt;
        last=newp;len[newp]=len[pos]+1;
        for (;pos&&!g[pos][ch];pos=pa[pos]) g[pos][ch]=newp;
        if (!pos) pa[newp]=1;
        else{
            int posx=g[pos][ch];
            if (len[pos]+1==len[posx]) pa[newp]=posx;
            else{
                int vs=++cnt;
                len[vs]=len[pos]+1;
                for (int i=0;i<26;i++) g[vs][i]=g[posx][i];
                pa[vs]=pa[posx];pa[posx]=pa[newp]=vs;
                for (;g[pos][ch]==posx;pos=pa[pos]) g[pos][ch]=vs;
            }
        } 
        ANS+=len[newp]-len[pa[newp]];
    }
    inline void clear(){
        for (int i=1;i<=cnt;i++){
            pa[i]=len[i]=0;
            for (int j=0;j<26;j++){
                g[i][j]=0;
            }
        }
        cnt=1;last=1;ANS=0;
    }
}sam;
int main(){
    int T;cin>>T;
    while (T--){
        sam.clear();
        scanf("%s",s);
        int L=strlen(s);
        for (int i=0;i<L;i++) sam.insert(s[i]-'a');
        cout<<sam.ANS<<endl;
    }
}
```

---

## 作者：黑影洞人 (赞：1)

题意：

>给定字符串，求本质不同的子串的个数。

很显然，我们可以使用后缀自动机来解决。

根据后缀自动机的性质，从源点出发到终点的不同路径数，就是子串的个数，我们直接在 DAG 上 DP 即可。

通过简单的图论得出，当前节点出发的所有路径数就是所有子路径的和加上自己一个点。

得到 DP 方程：

$$dp_x=1+\sum_{y\in son(x)}dp_y$$

记忆化搜索算一遍即可。

```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#include<cstring>
#define N 114514
#define int long long
using namespace std;
int T,dp[N];
char s[N];
struct SAM{
	int last,len[N],link[N],tot;
	map<char,int>ch[N];
	int newnode(){len[++tot]=0,link[tot]=0,ch[tot].clear();return tot;}
	void csh(){tot=0,last=newnode();}
	void insert(char c){
		int y=last,x=newnode();
		len[last=x]=len[y]+1;
		while(y&&!ch[y].count(c))ch[y][c]=x,y=link[y];
		if(!y)return void(link[x]=1);
		int z=ch[y][c];
		if(len[z]==len[y]+1)return void(link[x]=z);
		int w=newnode();
		len[w]=len[y]+1;link[w]=link[z];ch[w]=ch[z];
		link[z]=link[x]=w;
		while(y&&ch[y][c]==z)ch[y][c]=w,y=link[y];
	}
	void build(char *s){while(*s)insert(*s++);}
}a;
int dfs(int x){
	if(dp[x])return dp[x];
	dp[x]=1;
	if(a.ch[x].size()==0)return 1;
	for(map<char,int>::iterator it=a.ch[x].begin();it!=a.ch[x].end();it++){
		int y=it->second;
		dp[x]+=dfs(y);
	}
	return dp[x];
}
signed main(){
	scanf("%lld",&T);
	while(T--){
		scanf("%s",s);
		memset(dp,0,sizeof(dp));
		a.csh();
		a.build(s);
		dfs(1);
		printf("%lld\n",dp[1]-1);
	}
	return 0;
}



```


---

## 作者：crashed (赞：1)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/problemnew/show/SP705)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;后缀数组基础应用题。   
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;很容易看出，对于每一个后缀，它对答案的贡献就是它的长度。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;可是这道题不是要求本质不同的子串个数吗？很简单，我们不是有$height$数组吗？$height_i$即为排名为$i$的后缀和$i-1$的后缀的最长公共前缀的长度，也就对应着这两个后缀的重复计算的子串个数。   
# 代码
```cpp
#include <cstdio>
#include <cstring>

typedef long long LL;

const int MAXLEN = 50005;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s < '0' || '9' < s ){ if( s == '-' ) f = -1; s = getchar(); }
	while( '0' <= s && s <= '9' ){ x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar(); }
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ x = -x, putchar( '-' ); }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

char str[MAXLEN];
int cnt[MAXLEN], rnk[4 * MAXLEN], tmp[4 * MAXLEN], sa[MAXLEN], height[MAXLEN];
int N;

bool equal( const int x, const int y, const int p )
{
	return rnk[x] == rnk[y] && rnk[x + p] == rnk[y + p];
}

int main()
{
	int T;
	read( T );
	while( T -- )
	{
		scanf( "%s", str + 1 );
		N = strlen( str + 1 );
		for( int i = 1 ; i <= N ; i ++ )
		{
			cnt[str[i]] = 1;
		}
		for( int i = 1 ; i <= 127 ; i ++ )
		{
			cnt[i] += cnt[i - 1];
		}
		for( int i = 1 ; i <= N ; i ++ )
		{
			rnk[i] = cnt[str[i]];
		}
		int last = cnt[127], tot;
		for( int k = 1 ; tot ^ N ; k <<= 1, last = tot )
		{
			for( int i = 1 ; i <= last ; i ++ ) cnt[i] = 0;
			for( int i = 1 ; i <= N ; i ++ ) cnt[rnk[i + k]] ++;
			for( int i = 1 ; i <= last ; i ++ ) cnt[i] += cnt[i - 1];
			for( int i = N ; i >= 1 ; i -- ) tmp[cnt[rnk[i + k]] --] = i;
			for( int i = 1 ; i <= last ; i ++ ) cnt[i] = 0;
			for( int i = 1 ; i <= N ; i ++ ) cnt[rnk[tmp[i]]] ++;
			for( int i = 1 ; i <= last ; i ++ ) cnt[i] += cnt[i - 1];
			for( int i = N ; i >= 1 ; i -- ) sa[cnt[rnk[tmp[i]]] --] = tmp[i];
			tot = 0;
			for( int i = 1 ; i <= N ; i ++ )
			{
				if( ! equal( sa[i - 1], sa[i], k ) ) tot ++;
				tmp[sa[i]] = tot;
			}
			for( int i = 1 ; i <= N ; i ++ ) rnk[i] = tmp[i];
		}
		tot = 0;
		for( int i = 1, j ; i <= N ; i ++ )
		{
			if( rnk[i] == 1 ) continue;
			if( tot ) tot --;
			j = sa[rnk[i] - 1];
			while( i + tot <= N && j + tot <= N && str[i + tot] == str[j + tot] ) tot ++;
			height[rnk[i]] = tot;
		}
		LL res = N - sa[1] + 1;
		for( int i = 2 ; i <= N ; i ++ )
		{
			res += N - sa[i] + 1 - height[i];
		}
		write( res ), putchar( '\n' );
	}
	return 0;
}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~预处理辣摸长，计算答案辣摸短~~

---

## 作者：SkyRainWind (赞：1)

题目链接：https://www.spoj.com/problems/SUBST1/

题意：求一个字符串本质不同的子串个数

题解：

一个字符串的子串可以转化为后缀的前缀，发现后缀数组恰好可以适用这个问题

考虑根据$sa[]$数组的顺序从前往后加后缀，没加一个后缀排名为$i$，就会产生$n-sa[i]$个前缀，但是会有$h[sa[i]]$个与排名$i-1$的重复，需要减掉

为什么不需要考虑$i$和$i-2$的？因为已经被$i$和$i-1$、$i-1$和$i-2$ 包含了

PS：这题跟 SP694 是一道题

代码：
```cpp
// by Balloons
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define mpr make_pair
#define debug() puts("okkkkkkkk")
#define rep(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)

using namespace std;

typedef long long LL;

const int inf = 1 << 30;

const int maxn=1e5+5;

int bin[maxn],sa[maxn],rk[maxn],tmp[maxn];
char s[maxn];
int n,sz;

void getsa(){
	sz=max(n,128);
	
	for(int i=0;i<n;i++)rk[i]=s[i];
	for(int i=0;i<sz;i++)bin[i]=0;
	for(int i=0;i<n;i++)++bin[rk[i]];
	for(int i=1;i<sz;i++)bin[i]+=bin[i-1]; 
	for(int i=n-1;i>=0;i--)sa[--bin[rk[i]]]=i;
	
	for(int j=1;j<=n;j<<=1){
		int p=0;
		for(int i=n-j;i<n;i++)tmp[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]-j>=0)tmp[p++]=sa[i]-j;
		
		for(int i=0;i<sz;i++)bin[i]=0;
		for(int i=0;i<n;i++)++bin[rk[i]];
		for(int i=1;i<sz;i++)bin[i]+=bin[i-1]; 
		for(int i=n-1;i>=0;i--)sa[--bin[rk[tmp[i]]]]=tmp[i];
		
		p=0;
		tmp[sa[0]]=0;
		for(int i=1;i<n;i++){
			int v0=sa[i-1],v1=sa[i],v00,v01;
			if(v0+j<n)v00=rk[v0+j];else v00=-1;
			if(v1+j<n)v01=rk[v1+j];else v01=-1;
			
			if(rk[sa[i-1]]==rk[sa[i]]&&v00==v01)tmp[sa[i]]=p;
			else tmp[sa[i]]=++p;
		}
		
		for(int i=0;i<n;i++)rk[i]=tmp[i];
	}
}

int h[maxn];

int calc(int x,int y,int res){
	for(;s[x+res]==s[y+res];)++res;
	return res;
}

void geth(){
	if(rk[0]==0)h[0]=0;
	else h[0]=calc(0,sa[rk[0]-1],0);
	
	for(int i=1;i<n;i++){
		if(rk[i]==0)h[i]=0;
		else h[i]=calc(i,sa[rk[i]-1],max(h[i-1]-1,0));
	}
}

void solve(){
	scanf("%s",s);
	n=strlen(s);
	
	getsa();
	geth();
	
	int ans=0;
	for(int i=0;i<n;i++){
		int curh=n-sa[i];
		ans+=curh-h[sa[i]];
	}
	printf("%d\n",ans);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--)solve();

	return 0;
}

```

---

## 作者：朝夕晨曦_L (赞：0)

传送门：[SP705 SUBST1 - New Distinct Substrings](https://www.luogu.com.cn/problem/SP705) 

来一发 SA 做法。

考虑一共会产生多少的子串？以第一个字符为起点，有 $n$ 个串推理得到以第 $n$ 个字符为起点，有 $1$ 个。

根据等差数列求和公式得到：
$$\frac{n\times(n + 1)}{2}$$

那么接下来怎样删去重复的子串，就用 height！删去所有 height 即可！

$$\frac{n\times(n + 1)}{2}-{\sum\limits_{i = 1}^{n}{height[i]}}$$
见代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define M 1000050
using namespace std;
int n,m,l;
string s,ss;
int y[M],x[M],c[M],sa[M],rk[M],height[M],numm[M],maxn=0;
void get_sa(){
    for(int i=1;i<=n;++i) ++c[x[i]=s[i]];
    for(int i=2;i<=m;++i) c[i]+=c[i-1];
    for(int i=n;i>=1;--i) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1){

        int num=0;
        for(int i=n-k+1;i<=n;++i) y[++num]=i;
        for(int i=1;i<=n;++i) if(sa[i]>k) y[++num]=sa[i]-k;
        for(int i=1;i<=m;++i) c[i]=0;
        for(int i=1;i<=n;++i) maxn=max(maxn,++c[x[i]]);
        for(int i=2;i<=m;++i) c[i]+=c[i-1];
        for(int i=n;i>=1;--i) sa[c[x[y[i]]]--]=y[i],y[i]=0;
        swap(x,y);
        x[sa[1]]=1;
        num=1;
        for(int i=2;i<=n;++i){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]) {
                x[sa[i]]=num;
            }
            else {
                x[sa[i]]=++num;
            }
        }
        if(num==n)break;
        m=num;
    }
}
long long solve (){
    long long ans=((long long)n*(long long)(n+1))/2;
    for(int i=1;i<=n;++i)ans-=height[rk[i]];
    return ans;
}
void get_lcp(){
    int k=0;
    for(int i=1;i<=n;++i)rk[sa[i]]=i;
    for(int i=1;i<=n;++i){
        if(rk[i]==1)continue;
        if(k)--k;
        int j=sa[rk[i]-1];
        while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k])++k;
        height[rk[i]]=k;
    }
}
int main(){
    int nn;
    cin>>nn;
    for(int j=1;j<=nn;j++){
        cin>>ss;
        memset(sa,0,sizeof(sa));
        memset(rk,0,sizeof(rk));
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
        memset(height,0,sizeof(height));
        memset(c,0,sizeof(c));
        s='0';
        for(int i=0;i<ss.size();i++){
            s+=ss[i];
        }
        m=122;
        n=s.size()-1;
        get_sa();
        get_lcp();
        cout<<solve()<<endl; 
    }
    return 0;
}
```

---

## 作者：凤年 (赞：0)

>求本质不同子串个数。

SAM 经典应用，利用母树的树形结构，$\text{len}(i) - \text{len}(\text{fa}(i))$ 即为 $i$ 节点的子串个数，在建自动机的时候动态更新 $ans$ 即可。

多测记得清空。

```cpp
#include <bits/stdc++.h>
#define N 50010
using namespace std;

int T;
char s[N];
long long ans;

struct SAM {
    int fa, len, nex[26];
}sam[N << 1];

int tot = 1, last = 1;
void add(int x) {
    
    int now = ++tot, p = last;
    sam[now].len = sam[p].len + 1;
    for(; p && !sam[p].nex[x]; p = sam[p].fa) sam[p].nex[x] = now;
    if(!p) sam[now].fa = 1;
    else {
        int q = sam[p].nex[x];
        if(sam[q].len == sam[p].len + 1) sam[now].fa = q;
        else {
            int tmp = ++tot;
            sam[tmp] = sam[q];
            sam[now].fa = sam[q].fa = tmp;
            sam[tmp].len = sam[p].len + 1;
            for(; p && sam[p].nex[x] == q; p = sam[p].fa) sam[p].nex[x] = tmp;
        }
    }
    last = now;
    ans += sam[now].len - sam[sam[now].fa].len;
}

void clear() {
    ans = 0;
    tot = last = 1;
    memset(sam, 0, sizeof(sam));
}

int main() {
    scanf("%d", &T);
    while(T--) {
        clear();
        scanf("%s", s);
        // printf("%s ", s);
        for(int i = 0, n = strlen(s);i < n; ++i) add(s[i] - 'a'); 
        printf("%lld\n", ans);
    }    
    return 0;
}
```


---

## 作者：Emp7iness (赞：0)

这题可以用后缀数组来解。

设字符串长度为 $n$，那么所有子串的总数就是 $\dfrac{n(n+1)}{2}$，我们的目标就转化为了求相同子串的个数。

回想一下 `height` 数组的定义：$height[i]=\operatorname{lcp}(sa[i],sa[i-1])$

由于所有子串都可以看成后缀的前缀，所以相同子串的个数就是不同后缀的最长公共前缀之和，也就是 `height` 数组之和。

所以只需要从总数中减去这部分即可。

不要忘了多测清空，以及不开 `long long` 见祖宗。

代码：

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int N=50005;
int T,n,d[N],sa[N],rk[N],h[N];
long long ans;
char c[N];
struct str
{
	int a,b,i;
}s[N],p[N];
void rsort()
{
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++)	d[s[i].b]++;
	for(int i=1;i<N;i++)	d[i]+=d[i-1];
	for(int i=1;i<=n;i++)	p[d[s[i].b-1]+1]=s[i],d[s[i].b-1]++;
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++)	d[p[i].a]++;
	for(int i=1;i<N;i++)	d[i]+=d[i-1];
	for(int i=1;i<=n;i++)	s[d[p[i].a-1]+1]=p[i],d[p[i].a-1]++;
}
signed main()
{
	cin>>T;
	while(T--)
	{
		memset(rk,0,sizeof(rk));
		scanf("%s",c+1);
		n=strlen(c+1);
		for(int i=1;i<=n;i++)	rk[i]=c[i];
		for(int l=1;l<n;l<<=1)
		{
			for(int i=1;i<=n;i++)
			{
				s[i].a=rk[i];
				s[i].b=rk[i+l]+1;
				s[i].i=i;
			}
			rsort();
			int k=0;
			for(int i=1;i<=n;i++)
			{
				if(s[i].a!=s[i-1].a||s[i].b!=s[i-1].b)	k++;
				rk[s[i].i]=k;
			}
		}
		for(int i=1;i<=n;i++)	sa[rk[i]]=i;
		int j=0;
		for(int i=1;i<=n;i++)
		{
			j=max(0ll,j-1);
			if(rk[i]==1)	continue;
			int k=sa[rk[i]-1];
			while(i+j<=n&&j+k<=n&&c[i+j]==c[j+k])	j++;
			h[rk[i]]=j;
		}
		ans=n*(n+1)/2;
		for(int i=1;i<=n;i++)	ans-=h[i];
		cout<<ans<<endl;
	}
	return 0;
}
```


---

## 作者：zplqwq (赞：0)

后缀数组练手好题。


$sa_i$ 表示的是后缀排序后第 $i$ 小的后缀编号，因此 $n-sa_i$ 就是这个后缀的长度。（下标从 $1$ 开始的话就是 $n-sa_i-1$）。

$height_i$ 表示的是最长第 $i$ 个后缀和第 $i-1$ 个后缀的最长公共前缀的长度。

有了这两个定义之后，我们发现，我们对该字符串进行后缀排序后，第一个子串肯定全部都可以选，那么第二个子串能选的部分其实就是它的长度减去它与第一个子串的最长公共前缀的长度。可能有点绕，画个图理解一下会好很多。

所以实际上代码就这么多：

```cpp
	ans+=n-sa[1]+1;//第一个子串全部都可以选
		
	for(int i=2;i<=n;i++)
	{
		ans+=n-sa[i]+1/*当前子串的长度*/-height[i]/*与前面那个子串的最长公共前缀*/;
	}
       
```

具体求 $sa_i$ 和 $height_i$ 的部分就是后缀数组基本操作了。

---

## 作者：lgswdn_SA (赞：0)

这么模板的题目竟然没有后缀树题解？？？？？

那么我来水一发吧！

前置知识：后缀树。

考虑到后缀树是所有后缀形成的 trie，在原 trie （未压缩的）中的每一个非根节点代表一个本质不同的子串（因为 trie 的特性是不会有重复的）。那么在后缀树中，这个即 $\sum len$，因为每个非根节点的 $len$ 代表了自己到父亲节点之间的节点数。注意由于要去掉终止符的贡献，要减去原串长度+1。

```cpp
int T,n,s[N];
long long ans;
char str[N];

int sz,cnt,now,rem,ch[N<<1][27],link[N<<1],st[N<<1],len[N<<1];
int newn(int s,int l) {return link[++cnt]=1,st[cnt]=s,len[cnt]=l,cnt;}
void extend(int x) {
	int last=1; sz++, rem++;
	while(rem) {
		while(rem>len[ch[now][s[sz-rem+1]]])
			rem-=len[now=ch[now][s[sz-rem+1]]];
		int &v=ch[now][s[sz-rem+1]], c=s[st[v]+rem-1];
		if(x==c||!v) {
			link[last]=now, last=now;
			if(!v) v=newn(sz-rem+1,inf);
			else break;
		} else {
			int u=newn(st[v],rem-1);
			ch[u][x]=newn(sz,inf), ch[u][c]=v;
			st[v]+=rem-1, len[v]-=rem-1;
			link[last]=v=u, last=u;
		}
		(now==1)?rem--:now=link[now];
	}
}

int main() {
	T=read();
	while(T--) {
		cnt=1,now=1,sz=0,rem=0,ans=0,len[0]=inf;
		scanf("%s",str+1); n=strlen(str+1);
		rep(i,1,n) s[i]=str[i]-'a'+1; s[++n]=0;
		rep(i,1,n) extend(s[i]);
		rep(i,1,cnt) if(len[i]>n) len[i]=n-st[i]+1;
		rep(i,1,cnt) ans+=len[i]; ans-=n;
		printf("%lld\n",ans);
		rep(i,0,cnt) {
			link[i]=st[i]=len[i]=0;
			rep(j,0,26) ch[i][j]=0;
		}
	}
	return 0;
}
```

---

