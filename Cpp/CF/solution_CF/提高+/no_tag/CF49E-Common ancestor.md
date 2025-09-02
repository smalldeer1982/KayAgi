# Common ancestor

## 题目描述

Berland的每一个生物的DNA序列可以被表示成一个由小写字母组成的非空字符串。Berland的科学家们发现所有生物都是一步一步进化来的。在其中的每一步，DNA序列的一个字符会被替换成另外的两个。总共有$n$种允许的变化。变化$a_i\rightarrow b_ic_i$表示一个字符$a_i$可以被替换成两个字符$b_ic_i$。每一种变化均可以无限次发生。
科学家们表示，如果一个DNA序列$s_3$在整个进化过程中可以最终变为$s_1$和$s_2$，或许是经过了不同的步骤数，那么DNA序列分别为$s_1$和$s_2$的两个生物就会有一个共同祖先。现在给出$s_1$和$s_2$，你的任务是弄清楚分别拥有这两种DNA序列的生物是否有共同祖先。如果存在，你需要找出所有共同祖先中长度最短的DNA序列。

## 样例 #1

### 输入

```
ababa
aba
2
c->ba
c->cc
```

### 输出

```
2
```

## 样例 #2

### 输入

```
ababa
aba
7
c->ba
c->cc
e->ab
z->ea
b->ba
d->dd
d->ab
```

### 输出

```
1
```

## 样例 #3

### 输入

```
ababa
aba
1
c->ba
```

### 输出

```
-1
```

# 题解

## 作者：mrsrz (赞：4)

DP。

设$ok1[i][j][ch]$表示第一个串中的第$i\sim j$个字符能否从字符$ch$扩展而来。

这个直接区间DP即可。即$ok1[i][j][ch]|=ok1[i][k][a]\&\&ok2[k+1][j][b]$（其中```ab```有一条规则直接从$ch$扩展而来）。

边界就是$ok1[i][i][s1[i]]=1$。

第二个串的状态$ok2$同理。

这部分时间复杂度$O(n^4)$。

再考虑$dp[i][j]$表示第一个串的前$i$个字符和第二个串的前$j$个字符最短能从多短的字符串扩展而来。

枚举两个串这次要匹配的区间，即$dp[i][j]=\min_{ii,jj,ch}\{dp[ii-1][jj-1]+1\}$（$ok1[ii][i][ch]$和$ok2[jj][j][ch]$均为真时转移）。

边界$dp[0][0]=0$。

时间复杂度$O(26n^4)$。

## Code：
```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#define rep(i,a,b)for(int i=(a);i<=(b);++i)
#define N 123
char s1[N],s2[N];
bool ok1[N][N][N],ok2[N][N][N];
int n,L1,L2,dp[N][N];
std::vector<std::pair<int,int>>vec[N];
void init(){
	rep(i,1,L1)ok1[i][i][s1[i]]=1;
	rep(L,2,L1)
	rep(i,1,L1){
		const int j=i+L-1;
		if(j>L1)break;
		rep(ch,'a','z')rep(k,i,j-1)
		for(auto ru:vec[ch])ok1[i][j][ch]|=ok1[i][k][ru.first]&&ok1[k+1][j][ru.second];
	}
	rep(i,1,L2)ok2[i][i][s2[i]]=1;
	rep(L,2,L2)
	rep(i,1,L2){
		const int j=i+L-1;
		if(j>L2)break;
		rep(ch,'a','z')rep(k,i,j-1)
		for(auto ru:vec[ch])ok2[i][j][ch]|=ok2[i][k][ru.first]&&ok2[k+1][j][ru.second];
	}
}
void solve(){
	memset(dp,0x3f,sizeof dp);
	**dp=0;
	rep(i,1,L1)rep(j,1,L2)rep(ii,1,i)rep(jj,1,j)rep(ch,'a','z')
	if(ok1[ii][i][ch]&&ok2[jj][j][ch])dp[i][j]=std::min(dp[i][j],dp[ii-1][jj-1]+1);
}
int main(){
	scanf("%s%s",s1+1,s2+1);
	L1=strlen(s1+1),L2=strlen(s2+1);
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		char c1,c2;
		while(!isalpha(c1=getchar()));
		while(!isalpha(c2=getchar()));
		vec[c1].emplace_back(c2,getchar());
	}
	init();
	solve();
	if(dp[L1][L2]<=1e9)printf("%d",dp[L1][L2]);else puts("-1");
	return 0;
}
```

---

## 作者：Rushroom (赞：3)

~~不是这道题真的有黑题难度吗~~

[传送门](https://www.luogu.com.cn/problem/CF49E)

## 思路

我们先考虑这样一种情况。

举个例子，祖先为字符 ```abc```, 转换规则有:
```
a->bc
b->bb
b->ba
```
一次繁殖后，变成 ```bc bb c```;

两次繁殖后，变成 ```bac baba c```;

（祖先是同一个字符的用空格隔开）

我们发现一个重要的性质：

同一个字符所繁殖出的后代，在最后一定形成一个**连续**的字串。

于是我们就很容易想到用 **DP** 解决。

## DP

设 $f_{i,j}$ 为考虑第一个字符串的前 $i$ 个字符，第二个字符串的前 $j$ 个字符，最短公共祖先的长度是多少。

转移时，我们枚举最后一个字符繁殖成的字串的位置，在第一个字符串中的位置为 $[x+1,i]$，在第二个字符串中的位置为 $[y+1,j]$，转移方程为：

$f_{x,y} \rightarrow f_{i,j}$ ($[x+1,i]$ 与 $[y+1,j]$ 有长度为 1 的公共祖先)

我们设 $g_{i,j,k}$ 表示 $[i,j]$ 是否可以由单独的一个字符 $k$ 繁殖出来，则上面的转移方程可以转变为：

$f_{x,y} \rightarrow f_{i,j}(\exists g_{x+1,i,k} \And g_{y+1,j,k})$

关于怎么求出 $g$ 数组，我们可以运用区间 DP 的思路，枚举 $k$ 繁殖成哪两个字符，和这两个字符的区间分界点，具体参见代码。

然后就可以愉快地写出程序了。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define forr(i, a, n) for (int i = a; i <= n; i++)
#define rep(i, n) forr(i, 0, n - 1)
#define repp(i, n) forr(i, 1, n)
#define pb push_back
#define mp make_pair
#define init(a, i) memset(a, i, sizeof(a))
#define fi first
#define se second
#define mod 1000000007
#define MOD 998244353
#define MAXN 0x3f3f3f3f
int T, case_;
int n;
char s[51], t[51], rubbish[51];
int dp[51][51];
bool can[2][51][51][26];
int r[51][3];
void solve()
{
    scanf("%s%s%d", s, t, &n);
    rep(i, n)
    {
        scanf("%s", rubbish);
        r[i][0] = rubbish[0] - 'a', r[i][1] = rubbish[3] - 'a', r[i][2] = rubbish[4] - 'a';
    }
    rep(i, strlen(s)) can[0][i][i][s[i] - 'a'] = 1;
    forr(len, 2, strlen(s))
    {
        rep(i, strlen(s) - len + 1)
        {
            int j = i + len - 1;
            forr(k, i, j - 1)
            {
                rep(c, n)
                {
                    can[0][i][j][r[c][0]] |= (can[0][i][k][r[c][1]] && can[0][k + 1][j][r[c][2]]);
                }
            }
        }
    }
    rep(i, strlen(t)) can[1][i][i][t[i] - 'a'] = 1;
    forr(len, 2, strlen(t))
    {
        rep(i, strlen(t) - len + 1)
        {
            int j = i + len - 1;
            forr(k, i, j - 1)
            {
                rep(c, n)
                {
                    can[1][i][j][r[c][0]] |= (can[1][i][k][r[c][1]] && can[1][k + 1][j][r[c][2]]);
                }
            }
        }
    }
    init(dp, 63);
    dp[0][0] = 0;
    rep(i, strlen(s))
    {
        rep(j, strlen(t))
        {
            rep(x, i + 1)
            {
                rep(y, j + 1)
                {
                    rep(c, 26)
                    {
                        if (can[0][x][i][c] && can[1][y][j][c])
                        {
                            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[x][y] + 1);
                        }
                    }
                }
            }
        }
    }
    if (dp[strlen(s)][strlen(t)] > 100)
        printf("-1");
    else
        printf("%d", dp[strlen(s)][strlen(t)]);
}
int main()
{
    T = 1;

    for (case_ = 1; case_ <= T; case_++)
        solve();
    return 0;
}
```


---

## 作者：lilong (赞：2)

记字符集大小 $A=26$。

我们并不关心一段字符串怎么变化，只关心变化之后能得到什么字母。设 $f1_{i,j,z}=0/1$ 表示字符串 $s_1$ 的 $[l,r]$ 子串不可以/可以变成字母 $z$。枚举合并点 $k$，则有

$$f1_{i,j,z} \leftarrow f1_{i,j,z} \operatorname{or} ( f1_{i,k,x} \operatorname{and} f1_{k+1,j,y} \operatorname{and} mp_{x,y,z}),i\le k <j$$

其中 $mp_{x,y,z}=0/1$ 表示两个字母 $x,y$ 不可以/可以合并为 $z$。同理对 $s_2$ 预处理出 $f2$。此部分时间复杂度 $O((n^3+m^3)A^3)$。

预处理完后，就可以开始比较 $s_1,s_2$ 了。设 $f_{i,j}$ 表示 $s_1,s_2$ 分别到第 $i,j$ 个位置的共同祖先的最短长度。枚举 $1\le k <i,1\le l <j$，若 $s_1$ 的 $[k+1,i]$ 子串与 $s_2$ 的 $[l+1,j]$ 子串可以得到相同的字符，则 $f_{i,j}\leftarrow \min(f_{i,j},f_{k,l}+1)$。初始化 $f$ 为 $+\infty$，$f_{0,0}=0$。若 $f_{n,m}$ 为 $+\infty$ 则无解。此部分时间复杂度 $O(n^2m^2A)$。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 0x3f3f3f3f
using namespace std;
char a[51],b[51];
int n,m,f[51][51];
bool mp[26][26][26],f1[51][51][26],f2[51][51][26];
int main(){
    cin>>a;
    cin>>b;
    n=strlen(a),m=strlen(b);
    for(int i=n;i>=1;i--)a[i]=a[i-1],a[i]-='a';
    for(int i=m;i>=1;i--)b[i]=b[i-1],b[i]-='a';
    int T;cin>>T;
    while(T--){
        char x,y,z,op1,op2;
        cin>>z>>op1>>op2>>x>>y;
        x-='a',y-='a',z-='a';
        // cout<<int(x)<<' '<<int(y)<<' '<<int(z)<<endl;
        mp[x][y][z]=1;
    }
    for(int i=1;i<=n;i++)
        f1[i][i][a[i]]=1;
    for(int i=1;i<=m;i++)
        f2[i][i][b[i]]=1;
    for(int L=2;L<=n;L++)
        for(int i=1;i+L-1<=n;i++){
            int j=i+L-1;
            for(int k=i;k<j;k++)
                for(int x=0;x<26;x++)
                    for(int y=0;y<26;y++)
                        for(int z=0;z<26;z++)
                            f1[i][j][z]|=f1[i][k][x]&f1[k+1][j][y]&mp[x][y][z];
        }
    // for(int i=1;i<=n;i++)
    //     for(int j=i;j<=n;j++)
    //         for(int z=0;z<26;z++)
    //         cout<<i<<' '<<j<<' '<<z<<' '<<f1[i][j][z]<<'\n';
    for(int L=2;L<=m;L++)
        for(int i=1;i+L-1<=m;i++){
            int j=i+L-1;
            for(int k=i;k<j;k++)
                for(int x=0;x<26;x++)
                    for(int y=0;y<26;y++)
                        for(int z=0;z<26;z++)
                            f2[i][j][z]|=f2[i][k][x]&f2[k+1][j][y]&mp[x][y][z];
        }
    for(int i=0;i<=n;i++)
        for(int j=0;j<=m;j++)
            f[i][j]=inf;
    f[0][0]=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<i;k++)
                for(int l=0;l<j;l++)
                    for(int z=0;z<26;z++)
                        if(f1[k+1][i][z]&&f2[l+1][j][z])
                            f[i][j]=min(f[i][j],f[k][l]+1);
    if(f[n][m]==inf)cout<<-1;
    else cout<<f[n][m];
    return 0;
}
```

---

## 作者：BDFCL (赞：2)

**Solution**

*洛谷题目难度虚高了不少啊，CF评分才2300*

一开始的想法是由于将两个串变成一样的比较烦，所以考虑能不能只在一个串上操作，但是发现如果建反向边（即$ai \to b_ic_i$的）话会出现一些问题（比如说先由一变二再由二变一再由一变二），所以只能放弃这个想法

观察操作的性质，发现最终变成的串中每个字符均为原有串中一段连续的字串，所以考虑先将每段是否能够变为某一个字符处理出来在考虑如何分段使得最后的串长变小

基于这个想法，我们考虑分步$dp$

首先设$f1(l, r, c)$表示将$s1[l .. r]$变为$c$是否可行，$dp$转移方程十分好写：（其中$c1c2\to c$表示$c1c2$能够变成$c$
$$
f1(l, r, c) |= f(l, mid, c1) \&\& f(mid+1, r, c2) \quad(c1c2\to c)
$$
注意这里枚举的时候不是分别枚举$c1,c2,c$而是枚举$c$然后枚举有多少种方式能够组成$c$，这样枚举$c$总的复杂度是$O(N)$的

对于$s2$用同样的方法处理出$f2(l, r, c)$

然后我们设$g(i, j)$表示$s1$看到$i$，$s2$看到$j$时候的所能变成的最小串长，转移方程也十分显然：
$$
g(i, j) = \min \{g(x, y) + 1 | f1(x+1, i, c) \&\&f2(y+1, j, c) \}
$$
然后答案为$g(len(s1), len(s2))$

时间复杂度$O(N^4\times26)$

**Code**

（由于$g$方程初始化的需要，这里将$g$中的下标全部$+1$）

```c++
#include <bits/stdc++.h>

#define N (int) 55
#define INF 0x3f3f3f3f

using namespace std;
int n;
string s1, s2;
vector <pair <int, int> > v[N];

int f1[N][N][N], f2[N][N][N];
int g[N][N];

int main () {
    cin >> s1 >> s2;
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        char c = getchar ();
        while (c < 'a' || c > 'z') c = getchar ();
        getchar ();
        getchar ();
        char c1 = getchar (), c2 = getchar ();
        v[c-'a'].push_back (make_pair (c1-'a', c2-'a'));
        // cout << c << " " << c1 << " " << c2 << endl;
    }

    for (int i = 0; i < s1.size (); i ++) f1[i][i][s1[i]-'a'] = 1;
    for (int len = 2; len <= s1.size (); len ++) {
        for (int l = 0; l+len-1 < s1.size (); l ++) {
            int r = len + l - 1;
            for (int x = 0; x < 26; x ++) {
                for (int mid = l; mid < r; mid ++) {
                    for (int i = 0; i < v[x].size (); i ++) {
                        int c1 = v[x][i].first, c2 = v[x][i].second;
                        f1[l][r][x] |= f1[l][mid][c1] && f1[mid+1][r][c2];
                    }
                }
                // cout << l << " " << r << " " << x << " " << f1[l][r][x] << endl;
            }
        }
    }

    for (int i = 0; i < s2.size (); i ++) f2[i][i][s2[i]-'a'] =1;
    for (int len = 1; len <= s2.size (); len ++) {
        for (int l = 0; l < s2.size (); l ++) {
            int r = len + l - 1;
            for (int mid = l; mid < r; mid ++) {
                for (int x = 0; x < 26; x ++) {
                    for (int i = 0; i < v[x].size (); i ++) {
                        int c1 = v[x][i].first, c2 = v[x][i].second;
                        f2[l][r][x] |= f2[l][mid][c1] && f2[mid+1][r][c2];
                    }
                }
            }
        }
    }

    memset (g, INF, sizeof (g));
    g[0][0] = 0;
    for (int i = 1; i <= s1.size (); i ++) {
        for (int j = 1; j <= s2.size (); j ++) {
            for (int x = 0; x < i; x ++) {
                for (int y = 0; y < j; y ++) {
                    for (int c = 0; c < 26; c ++) {
                        if (f1[x][i-1][c] && f2[y][j-1][c]) g[i][j] = min (g[i][j], g[x][y] + 1);
                    }
                }
            }
            // cout << g[i][j] << " ";
        }
        // cout << endl;
    }

    cout << (g[s1.size ()][s2.size ()] < INF ? g[s1.size ()][s2.size ()] : -1) << endl;

    return 0;
}

```

**Conclusion**

* 找性质
* 如果一个$dp$不行就使用两个



---

## 作者：MyukiyoMekya (赞：1)

这题的 $n$ 很小，所以可以考虑怎么暴力怎么来。

设 $h_{i,j}$ 表示 $s1$ 的前 $i$ 位和 $s2$ 的前 $j$ 位的最短公共祖先长度，大力枚举转移点 $k<i,l<j$ ，

当 $s1(k+1,i)$ 和 $s2(l+1,j)$ 都可以由一个字符 $o$ 造出来的时候转移 $h_{i,j}=\min \{h_{k,l}+1\}$

这部分 $\mathcal O(26n^4)$

然后就是快速预处理一个串的 $[l,r]$ 能否被单个字符 $o$ 生成，记为 $f_{l,r,o}$，边界 $f_{i,i,o}=[s(i)=o]$

然后就是区间 dp 的转移 $f_{l,r,o} \leftarrow f_{l,r,o} \operatorname{or} (f_{l,k,a} \operatorname{and} f_{k+1,r,b})$ ，当 $o$ 能变成 $ab$ 的时候。

这部分是 $\mathcal O(26^2n^3)$ 的，跑不满，能过。

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
#define mem(x,y) memset(x,y,sizeof x)
#define ln std::puts("")
#define lsp std::putchar(32)
#define pb push_back
#define MP std::make_pair
template <class t> inline void read(t &s){s=0;
reg int f=1;reg char c=getchar();while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
while(isdigit(c))s=(s<<3)+(s<<1)+(c^48),c=getchar();s*=f;return;}
template<class t,class ...A> inline void read(t &x,A &...a){read(x);read(a...);}
template <class t> inline void write(t x){if(x<0)putchar('-'),x=-x;
int buf[21],top=0;while(x)buf[++top]=x%10,x/=10;if(!top)buf[++top]=0;
while(top)putchar(buf[top--]^'0');return;}
inline int lowbit(int x){return x&(-x);}
template <class t> inline void Read(t &s){
reg char c=getchar();while(!isalpha(c))c=getchar();s=c;}
#define fi first
#define se second
char a[55],b[55];
std::vector<std::pair<int,int> > nxt[26];
int f[55][55][26],g[55][55][26],h[55][55];
int n,m,q;
inline int dfs(int f[55][55][26],char *a,int l,int r,int o)
{
	if(~f[l][r][o])
		return f[l][r][o];
	if(l==r)
		return ((a[l]-'a')==o)?1:0;
	f[l][r][o]=0;
	for(auto i:nxt[o])
		for(int k=l;!f[l][r][o]&&k<r;++k)
			f[l][r][o]|=dfs(f,a,l,k,i.fi)&dfs(f,a,k+1,r,i.se);
	return f[l][r][o];
}
signed main(void)
{
	std::mem(f,-1),std::mem(g,-1);
	std::scanf("%s%s",a+1,b+1);
	n=std::strlen(a+1),m=std::strlen(b+1);
	read(q);
	while(q--)
	{
		reg char c,u,v;Read(c),Read(u),Read(v);
		nxt[c-'a'].pb(MP(u-'a',v-'a'));
	}
	std::mem(h,0x3f);
	h[0][0]=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			for(int k=0;k<i;++k)
				for(int l=0;l<j;++l)
					for(int o=0;o<26;++o)
						if(dfs(f,a,k+1,i,o)&&dfs(g,b,l+1,j,o))
							h[i][j]=std::min(h[i][j],h[k][l]+1);
    if(h[n][m]>1e9)
        std::puts("-1");
    else
	    write(h[n][m]),ln;
	return 0;
}
```



---

## 作者：liangbowen (赞：0)

[problem](https://www.luogu.com.cn/problem/P1001) & [blog](https://www.cnblogs.com/liangbowen/p/17722775.html)。

提供一个逻辑顺畅的思路（然而做法相同的）。

---

手玩样例，Sample1 是 $\texttt{ac}\to[\texttt{a}][\texttt{baba}]$ 与 $[\texttt{a}][\texttt{ba}]$。很显然样例有分段性质，所以 DP，$dp_{i,j}$ 表示 $s_{1,2,\cdots,i}$ 与 $t_{1,2,\cdots,j}$ 的最短祖先长度。

很 naive 地，$dp_{i,j}=\min\{dp_{i_0,j_0}+1\}(\#)$，$\#$ 满足 $(i_0,i-1)$ 与 $(j_0,j-1)$ 可以由同一个字符转换到。于是处理一下 $\#$ 即可。

发现这件事情是 $[i,j]$ 能否由 $C$ 得到，所以区间 DP，转移是平凡的。预处理后就做完了。

[code](https://codeforces.com/contest/49/submission/224577290)，时间复杂度 $O(n^4A)$，$A=26$，常数很小。


---

## 作者：王熙文 (赞：0)

## 思路

首先，看到公共的部分，自然可以想到类似 LCS 的状态设计：$dp_{i,j}$ 表示 $s$ 串的前 $i$ 个字符与 $t$ 串的前 $j$ 个字符最终能变成的最短长度（要满足相等）。

那么很容易想到，$dp_{i,j}$ 需要将 $s$ 串的某个位置（设其为 $k_1$）到 $i$ 与 $t$ 串的某个位置（设其为 $k_2$）到 $j$ 替换成同一个字符，并从 $dp_{k_1-1,k_2-1}$ 转移过来，那么转移方程就是 $dp_{i,j}=dp_{k_1-1,k_2-1}+1$。

但是，我们如何知道某个区间能不能替换成一个字符呢？对于这种数据范围较小的题，并且是对于区间操作，一眼就可以看出是区间 dp。

设 $f_{l,r,c}$ 表示某个字符串的区间 $[l,r]$ 是否能转移成一个字符 $c$。考虑如何转移，字符 $c$ 的诞生是因为 $c$ 要从两个字符转移，所以我们枚举能转移成 $c$ 的两个字符（设其为 $a$ 和 $b$），然后判断是否存在一个分割点 $k$ 使得 $f_{l,k,a}=1$ 且 $f_{k+1,r,b}=1$，如果存在那么字符 $c$ 就可以通过这两部分转移出来了。 

## 启发

对于公共的子串一类问题，首先想到前 $i$ 个字符对前 $j$ 个字符这种线性 dp 的设计。

对于区间问题且数据范围可接受，首先想到区间 dp。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

string a,b;

vector<pair<int,int> > vec[30]; 

bool f1[55][55][30],f2[55][55][30]; // ok1[i][j][c] 表示第一个字符串中的 [i,j] 是否可以转移成字符 c

int dp[55][55];

int main()
{
    memset(dp,0x3f,sizeof(dp)); dp[0][0]=0;
    cin>>a>>b;
    int la=a.size(),lb=b.size();
    a=" "+a,b=" "+b;
    int q;
    char c,tmp,tmp2,d,e;
    cin>>q;
    for(int i=1; i<=q; ++i)
    {
        cin>>c>>tmp>>tmp2>>d>>e;
        vec[c-'a'].push_back(make_pair(d-'a',e-'a'));
    }
    for(int i=1; i<=la; ++i) f1[i][i][a[i]-'a']=1;
    for(int i=1; i<=lb; ++i) f2[i][i][b[i]-'a']=1;
    for(int d=2; d<=la; ++d)
    {
        for(int i=1; i<=la-d+1; ++i)
        {
            int j=i+d-1;
            for(int c=0; c<26; ++c)
            {
                bool flag=0;
                int len=vec[c].size();
                for(int k=0; k<len; ++k)
                {
                    for(int zzd=i; zzd<=j-1; ++zzd)
                    {
                        if(f1[i][zzd][vec[c][k].first] && f1[zzd+1][j][vec[c][k].second])
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag) break;
                }
                f1[i][j][c]=flag;
            }
        }
    }
    for(int d=2; d<=lb; ++d)
    {
        for(int i=1; i<=lb-d+1; ++i)
        {
            int j=i+d-1;
            for(int c=0; c<26; ++c)
            {
                bool flag=0;
                int len=vec[c].size();
                for(int k=0; k<len; ++k)
                {
                    for(int zzd=i; zzd<=j-1; ++zzd)
                    {
                        if(f2[i][zzd][vec[c][k].first] && f2[zzd+1][j][vec[c][k].second])
                        {
                            flag=1;
                            break;
                        }
                    }
                    if(flag) break;
                }
                f2[i][j][c]=flag;
            }
        }
    }
    for(int j=1; j<=lb; ++j)
    {
        for(int c=0; c<26; ++c)
        {
            if(f2[1][j][c])
            {
                dp[0][j]=1;
                break;
            }
        }
    }
    for(int i=1; i<=la; ++i)
    {
        for(int c=0; c<26; ++c)
        {
            if(f1[1][i][c])
            {
                dp[0][i]=1;
                break;
            }
        }
    }
    for(int i=1; i<=la; ++i)
    {
        for(int j=1; j<=lb; ++j)
        {
            for(int ii=0; ii<i; ++ii)
            {
                for(int jj=0; jj<j; ++jj)
                {
                    for(int c=0; c<26; ++c)
                    {
                        if(f1[ii+1][i][c] && f2[jj+1][j][c])
                        {
                            dp[i][j]=min(dp[i][j],dp[ii][jj]+1);
                        }
                    }
                }
            }
        }
    }
    cout<<(dp[la][lb]==0x3f3f3f3f?-1:dp[la][lb]);
    return 0;
}
```



---

