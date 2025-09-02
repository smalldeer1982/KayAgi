# [COCI 2016/2017 #4] Osmosmjerka

## 题目描述

给定一个 $M \times N$ 的字母矩阵，以下面的为例：

```plain
honi
hsin
```

接着我们将其进行无限延伸，得到：

```plain
...honihonihonihoni...
...hsinhsinhsinhsin...
...honihonihonihoni...
...hsinhsinhsinhsin...
```

在无限延伸后得到的新矩阵后，我们随机选取其中一个区域的字母，然后再沿着一定的方向连续读取 $K$ 个字母。在独立完成上述操作两次之后，我们会得到两个长度为 $K$ 的字符串。求两个字符串相同的概率。

## 说明/提示

**【数据规模与约定】**

对于其中 $100$ 分的数据，$M=N$。

对于 $100\%$ 的数据，$1 \le M,N \le 500$，$2 \le K \le 10^9$。

**【提示与说明】**

**题目译自 [COCI 2016-2017](https://hsin.hr/coci/archive/2016_2017/) [CONTEST #4](https://hsin.hr/coci/archive/2016_2017/contest4_tasks.pdf) _T6 Osmosmjerka_。**

**本题分值按 COCI 原题设置，满分 $160$。**

## 样例 #1

### 输入

```
1 2 2
ab```

### 输出

```
5/16```

## 样例 #2

### 输入

```
2 4 3
honi
hsin```

### 输出

```
19/512```

## 样例 #3

### 输入

```
3 3 10
ban
ana
nab```

### 输出

```
2/27```

# 题解

## 作者：zhangshiyan (赞：1)

# P7538 [COCI2016-2017#4] Osmosmjerka
[R188752538 记录详情](https://www.luogu.com.cn/record/188752538)

## Main Idea
给定一个字符矩阵，我们将这个矩阵无限复制，形成一个无限大的矩阵。然后，从矩阵中的任意位置出发，可以沿着八个方向（上下左右以及四个斜对角方向）选取连续的 $K$ 个字符，形成一个字符串。题目要求计算，随机选择两个位置和两个方向，得到两个相同的字符串的概率。

## Solution
枚举起点 $i$ 和 $j$ 和八个方向 $d$，于是考虑计算哈希值，由于 $2 \leq K \leq 10^9$，数据太大了，于是可以考虑倍增计算哈希值。

我们发现对于每个点，只有八个方向，最终能得到 $8 \times n \times m$ 个字符串，不是很多，那我们可以考虑求出这些字符串的哈希值，相同的哈希值代表选到相同字符串的一种可能，直接统计即可。

但是，模数取 $998244353$ 时被卡掉一个点。

你可以选择：
1. 使用双哈希。
2. 使用一些不那么有名的模数。
3. 自然溢出

### 优化
当你做完后，开心地提交后，发现错了，为什么呢？由于空间复杂度是 $O(8 \times n ^ 2 \times \log_{2}{K})$ 内存超限了，怎么办呢？

肯定是用类似滚动数组的方式来优化空间复杂度，由于八个方向之间的计算互不影响，所以我们分开算八次，优化复杂度为 $O(n ^ 2 \times \log_{2}{K})$ 刚好可以过，具体实现见代码。

当你改完后，开心地提交后，发现还是错了，为什么呢？

注意，如果哈希的时候取模，是很慢。可以用自然溢出或不要再同一行代码取太多了模。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 0x7ffffff

inline int read()
{
	int x = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9')
	{
		if(c == '-')
		{
			f = -1;
		}
		c = getchar();
	}
	while(c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	return x * f;
}

const ll mod = 998244853;

char c[505][505];
int st[505][505][50];
ll poww[100];
ll pow2[100];
ll ans[20000010], top;

int dx[10] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[10] = {1, -1, 0, 0, 1, -1, 1, -1};

ll gcd(ll a, ll b)
{
	return !b ? a : gcd(b, a % b);
}

int main()
{
	poww[0] = 133;
	for(int i = 1; i <= 35; i++)
	{
		poww[i] = (poww[i - 1] * poww[i - 1]) % mod;
	}
	pow2[0] = 1;
	for(int i = 1; i <= 35; i++)
	{
		pow2[i] = pow2[i - 1] * 2;
	}
	int n = read(), m = read(), kkk = read();
	for(int i = 0; i < n; i++)
		scanf("%s", c[i]);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			st[i][j][0] = c[i][j] - 'a' + 1;
		}
	}
	for(int k = 0; k < 8; k++)//分开算八次
	{
		for(int l = 1; l <= 30; l++)
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < m; j++)
				{
					int x = (i + dx[k] * (pow2[l - 1])) % n;
					int y = (j + dy[k] * (pow2[l - 1])) % m;
					x = (x + n) % n;
					y = (y + m) % m;
					st[i][j][l] = (st[i][j][l - 1] * poww[l - 1] + st[x][y][l - 1]) % mod;
				}
			}
		}
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				ll Hash = 0;
				int x = i, y = j;
				for(int l = 30; l >= 0; l--)
				{
					if(kkk & (1 << l))
					{
						Hash = Hash * poww[l] + st[x][y][l];
						x = (x + pow2[l] * dx[k]) % n;
						y = (y + pow2[l] * dy[k]) % m;
						x = (x + n) % n;
						y = (y + m) % m;
					}
				}
				ans[++top] = Hash;
			}
		}
	}
	sort(ans + 1, ans + top + 1);
	ll cnt = 0;
	ll ans1 = 0;
	ll ans2 = top * top;
	for(int i = 1; i <= top; i++)
	{
		if(i > 1 && ans[i] == ans[i - 1])
		{
			cnt++;
		}
		else
		{
			ans1 += 1LL * cnt * cnt;
			cnt = 1;
		}
	}
	ans1 += cnt * cnt;
	printf("%lld/%lld", ans1 / gcd(ans1, ans2), ans2 / gcd(ans1, ans2));
	return 0;
}
```

---

## 作者：shuangmu (赞：1)

[广告](https://www.cnblogs.com/frostwood/p/17724628.html)

我们发现对于每个点，只有八个方向，也就是说，最终能得到的字符串只会有 $8nm$ 个，那我们可以考虑把这些字符串的哈希值求出来，相同的哈希值代表选到相同字符串的一种可能，直接统计即可。

现在的问题就在于，怎么快速地求出这 $8nm$ 个字符串的哈希值。因为 $k$ 很大，所以我们不能暴力求。发现我们只关心最后长度为 $k$ 的字符串的哈希值，所以我们可以考虑用倍增优化求哈希。令 $Hash_{i, j, k}$ 为在点 $(i, j)$ 处向一个方向延伸 $2^k$ 个字符后得到的字符串的哈希值，这样，把长度按二进制拆开后，逐个加上为 $1$ 的位上保存的哈希值就可以了（当然必须要乘上增加的底数）。

我们对每个延伸方向都这么做一遍就可以了。

需要注意的是，如果哈希的时候取模，可能会很慢。这里用的是自然溢出，当然评测机心情不好的时候还是要开 O2 才过（

代码：

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#define ULL unsigned long long
using namespace std;
const int N = 505;
const int pa = 13331;
const int mod = 998244853;
long long gcd(long long a, long long b) {
	return b == 0 ? a : gcd(b, a % b);
}
char mp[N][N];
ULL pwa[34];
ULL hasha[N][N][34];
int n, m, K;
int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[8] = {1, -1, 0, 0, 1, 1, -1, -1};

ULL vc[2000010];
int top;
int pw2[33];
void solve() {
	pw2[0] = 1;
	for(int i = 1; i<=30; ++i) {
		pw2[i] = pw2[i-1]<<1;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			hasha[i][j][0] = (mp[i][j] - 'a' + 1);
		}
	}
	for (int d = 0; d < 8; ++d) {
		
		int tx, ty;
		for (int k = 1; k <= 29; ++k) {
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {

					tx = (i + pw2[k-1] * dx[d] - 1) % n;
					ty = (j + pw2[k-1] * dy[d] - 1) % m;
					tx = (tx + n) % n + 1;
					ty = (ty + m) % m + 1;//求出延伸后的点的坐标
					hasha[i][j][k] = (hasha[i][j][k - 1] * pwa[k - 1] + hasha[tx][ty][k - 1]);
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {

				int nowx = i, nowy = j;
				ULL tmp = 0;
				for (int k = 0; k <= 29; ++k) {
					if ((K >> k) & 1) {
						tmp = tmp * pwa[k] + hasha[nowx][nowy][k];
						nowx = (nowx + pw2[k] * dx[d] - 1) % n;
						nowy = (nowy + pw2[k] * dy[d] - 1) % m;
						nowx = (nowx + n) % n + 1;
						nowy = (nowy + m) % m + 1;
					}
				}
				vc[++top] = tmp;
			}
		}
	}
	sort(vc+1, vc+top+1);
	long long U = 0;
	long long cnt = 0;
	for (int i = 1; i <= top; ++i) {
		if (i > 0 && vc[i] != vc[i - 1]) {
			U += (cnt * cnt);//两个人选出这个字符串都有 cnt 种方案，故共 cnt * cnt 种方案
			cnt = 1;
		} else {
			++cnt;
		}
	}
	U += (cnt * cnt);
	long long D = (1ll * top * top);//总方案数
	long long g = gcd(U, D);
	
	printf("%lld/%lld\n", U / g, D / g);
}
int main() {
	pwa[0] = pa;
	for (int i = 1; i <= 32; ++i) {
		pwa[i] = pwa[i - 1] * pwa[i - 1];
	}
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", mp[i] + 1);
	}
	solve();
	return 0;
}
```



---

## 作者：lqsy002 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P4472)。

## 解题思路

哈希，倍增。

注意到 $k \in[2,10^9]$。

暴力复杂度 $O(mnk)$ 显然超时，考虑用 $\log k$ 的时间处理。

类似 ST 表的做法，因为 $k$ 步同方向，倍增处理后合并。

合并后遍历 hash 数组，将答案加上所有相同的字符串数量，因为所有字符串均可以由原字符串向 $8$ 个方向扩张后平移得到。

所以实际只需得出 $8 \times m \times n$ 个字符串的哈希值即可。

$n \times m$ 的矩阵 $8$ 个方向，总方案数 $(8 \times m \times n)^2$。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define int long long
#define siz 2000000//8mn 
#define maxn 205
using namespace std;
int n,m,k,logk,pm,pn,ans1,ans2,pow1[50],cnt[siz+10];
int dic[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
ull pow2[50],hash1[siz+10],hash2[siz+10],f[5][10][maxn][maxn];
//f_{i,j,k,l}表示从(i,j)开始像k方向走2^l步得到的hash 
//pow1倍增 pow2作为hash的base 
string s;
int Hash(ull x,ull y){
    int p=x%siz; 
    while(hash1[p]&&((hash1[p]!=x)||(hash2[p]!=y)))
        if(++p==siz)
            p=0;
    return p;
}
signed main(){
    freopen("genius.in","r",stdin);
    freopen("genius.out","w",stdout);
	ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr);
    cin>>m>>n>>k;
    logk=log(k)/log(2);//倍增的边界 
    for(int i=1;i<=m;++i){
        cin>>s;
        s=" "+s;
        for(int j=1;j<=n;++j)
            for(int l=0;l<8;++l)
                f[0][l][i][j]=s[j]-('a'-1);
    }
    pow1[0]=1;
    pow2[0]=31;
    for(int i=1,p;i<=logk;++i){
        pow1[i]=(pow1[i-1]<<1);
        pow2[i]=pow2[i-1]*pow2[i-1];
        for(int j=0;j<8;++j)
            for(int l=1;l<=m;++l)
                for(int o=1;o<=n;++o){
                    p=i&1;
                    pm=((l+dic[j][0]*pow1[i-1]-1)%m+m)%m+1;
                    pn=((o+dic[j][1]*pow1[i-1]-1)%n+n)%n+1;
                    f[p][j][l][o]=f[p^1][j][l][o]+f[p^1][j][pm][pn]*pow2[i-1];
                }
    }
    for(int i=0,p,logkk=logk&1;i<8;++i)
        for(int j=1;j<=m;++j)
            for(int l=1;l<=n;++l){
                pm=((j+dic[i][0]*(k-pow1[logk])-1)%m+m)%m+1;
                pn=((l+dic[i][1]*(k-pow1[logk])-1)%n+n)%n+1;
                p=Hash(f[logkk][i][j][l],f[logkk][i][pm][pn]);//找到插入hash的位置 
                hash1[p]=f[logkk][i][j][l];
                hash2[p]=f[logkk][i][pm][pn];
                ++cnt[p];//计数相同哈希值 
            }
    for(int i=0;i<siz;++i)
        if(cnt[i])
            ans1+=cnt[i]*cnt[i];
    ans2=n*n*m*m*64;
    k=__gcd(ans1,ans2);
    cout<<ans1/k<<'/'<<ans2/k;
    return 0;
}
//双倍经验 P7635
```

---

## 作者：Union_of_Britain (赞：0)

对于一个方向，我们可以把这些格子划分为若干等价类，每个等价类中的格子有循环同构的循环节。这些等价类的循环节长的和为 $nm$。对于一个等价类的格子，我们容易求出其循环节的哈希值。

其重复 $k$ 次的哈希（设循环节长 $L$，原哈希值为 $H$）为

$$(1+x^L+\dots+x^{(k-1)L})H $$

$$=\frac{x^{kL}-1}{x^L-1}H$$

如果我们的哈希 $base-1$ 存在关于 $mod$ 的逆元，那么我们就可以快速求出其长度为 $K$ 的哈希值。

最后的答案：设 $8nm$ 的哈希值中相同的有 $H_1,H_2\dots,H_K(\sum H_i=8nm)$ 个，答案就是

$$\frac{\sum H_i^2}{(8nm)^2}$$

赛时代码，唐完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,K,cnt=0,qsy1=1e9+97,qsy2=1e9+7;
int dx[8]={1,0,-1,0,1,-1,1,-1};
int dy[8]={0,1,0,-1,-1,1,1,-1};
int bse[3]={233,791,229};
int mod[3]={998244853,qsy1,qsy2};
int pw[3][250005],ipw[3][250005],Ipw[3][250005];
int res[3][250005];
struct hsh{
	int a[3];
	hsh(){
		for(int i=0;i<3;i++)a[i]=0;
	}
	bool operator <(const hsh &b)const{
		for(int i=0;i<3;i++){
			if(a[i]!=b.a[i])return a[i]<b.a[i];
		}
		return 0;
	}
	bool operator ==(const hsh &b)const{
		for(int i=0;i<3;i++)if(a[i]!=b.a[i])return 0;
		return 1;
	}
};
int qp(int a,int b,int c){
	if(b==0)return 1;
	int ans=1,tmp=a;
	for(int i=0;(1ll<<i)<=b;i++){
		if(b&(1ll<<i))ans=ans*tmp%c;
		tmp=tmp*tmp%c;
	}
	return ans;
}
char s[505][505];
vector<char> A[2000005];
int dir[8][505][505];
bool vis[8][505][505];
map<hsh,int> mp;
inline int tx(int x){
	return 1+(x-1+n)%n;
}
inline int ty(int y){
	return 1+(y-1+m)%m;
}
vector<pair<int,int> > bin;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>m>>K;
	for(int i=1;i<=n;i++)cin>>(s[i]+1);
	for(int i=0;i<3;i++){
		pw[i][0]=ipw[i][0]=1;
		for(int j=1;j<=80000;j++){
			pw[i][j]=pw[i][j-1]*bse[i]%mod[i];
			ipw[i][j]=qp(pw[i][j],mod[i]-2,mod[i]);
			Ipw[i][j]=qp(pw[i][j]-1,mod[i]-2,mod[i]);
		}
	}
	for(int t=0;t<8;t++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(!vis[t][i][j]){
					int ct=0;bin.clear();
					int nx=i,ny=j;++cnt;
					A[cnt].push_back('?');
					while(!vis[t][nx][ny]){
						vis[t][nx][ny]=1;++ct;
						dir[t][nx][ny]=ct;
						A[cnt].push_back(s[nx][ny]);
						bin.push_back({nx,ny});
						nx=tx(nx+dx[t]),ny=ty(ny+dy[t]);
					}
					int L=A[cnt].size()-1;
					for(int k=1;k<=L;k++)A[cnt].push_back(A[cnt][k]);
					for(int tp=0;tp<3;tp++){
						res[tp][0]=0;
						for(int k=1;k<A[cnt].size();k++){
							res[tp][k]=(res[tp][k-1]+pw[tp][k]*A[cnt][k]%mod[tp])%mod[tp];
						}
					}
					int zfy[3];
					for(int tp=0;tp<3;tp++){
						int rd=K/L,rl=K%L,nch123=qp(bse[tp],rd*L,mod[tp]);
						zfy[tp]=nch123;
					}
					for(auto pt:bin){
						int x=pt.first,y=pt.second;
						int l=dir[t][x][y],r=l+L-1;hsh cur;
						for(int tp=0;tp<3;tp++){
							int T=(ipw[tp][l]*(res[tp][r]-res[tp][l-1])%mod[tp]+mod[tp])%mod[tp],QSY=0;
							int rd=K/L,rl=K%L;
							(QSY+=T*(zfy[tp]-1)%mod[tp]*Ipw[tp][L]%mod[tp]+mod[tp])%=mod[tp];
							(QSY+=zfy[tp]*ipw[tp][l]%mod[tp]*(res[tp][l+rl-1]-res[tp][l-1])%mod[tp]+mod[tp])%=mod[tp];
							cur.a[tp]=QSY;
						}
						mp[cur]++;
					}
				}
			}
		}
	}
	int fz=0,fm=(8*n*m)*(8*n*m);
	for(auto P:mp){
		fz+=P.second*P.second;
	}
	int G=__gcd(fz,fm);fz/=G,fm/=G;
	cout<<fz<<"/"<<fm<<endl;
	return 0;
}
```

---

