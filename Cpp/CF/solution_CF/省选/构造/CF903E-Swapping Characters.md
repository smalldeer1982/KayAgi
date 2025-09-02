# Swapping Characters

## 题目描述

给你 $k$ 个串，每个串长度都是 $n$，现在问你是否可能这些串是同一个串交换两个位置的字符所产生的，输出这个原串。

## 样例 #1

### 输入

```
3 4
abac
caab
acba
```

### 输出

```
acab
```

## 样例 #2

### 输入

```
3 4
kbbu
kbub
ubkb
```

### 输出

```
kbub
```

## 样例 #3

### 输入

```
5 4
abcd
dcba
acbd
dbca
zzzz
```

### 输出

```
-1
```

# 题解

## 作者：hanzizhou (赞：6)

第一次交题解，如有不好处请指正。~~好像是第一篇耶~~

## 题意
给你 $k$ 个串，每个串长度都是 $n$，现在问你是否可能这些串是同一个串交换两个位置的字符所产生的。

## 思路
首先 $k$ 个串中,统计一下任意两个串的每个字符出现次数，任意两个串的每个字符出现次数都要相同，否则就无解。
```
    cj=1;
    for(int i=1;i<=k;++i){
        for(int j=0;j<n;++j)t[i][s[i][j]-'a']++;
        for(int j=0;j<26;++j)if(t[i][j]!=t[1][j])cj=0;
    }
    if(cj==0)return printf("-1\n"),0;
```
### ①

这题看上去没有好的办法，本来想 $k$ 个串，全部两两交换，然后存在 $map$ 里面，看看有哪一个串出现了$k$ 次，就是可以的了。

可是但是复杂度是$O(k \times n^2 \times \log {n^2} )$的，所以就不行了。

### ②

只要对第一个串进行 $n^2$ 交换，但是交换以后对每个串又要用 $O(n)$ 时间计算差别。复杂度是 $O(k \times n^3)$ 的，所以也就不行了。

### ③

然后优化计算差别，其实可以用 $O(1)$ 时间.

预处理一下所有字符串 $s_1$ 的差别即可，所以复杂度是 $O(k \times n^2)$

PS：
$s_1$ 交换两字符后，如果其是原串，那么后面的字符串与其的差别要么是 $2$ 个字符，要么是 $0$ 个字符(条件是原串存在 $2$个 相同字符)。


## 代码
鄙人码风不好，请谅解。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
char s[5001][5001];
int k,n,sa,cj,t[5001][26],b[5001],bb[5001];
signed main(){
    scanf("%lld%lld",&k,&n);
    for(int i=1;i<=k;++i)scanf("%s",s[i]);
    cj=1;
    for(int i=1;i<=k;++i){
        for(int j=0;j<n;++j)t[i][s[i][j]-'a']++;
        for(int j=0;j<26;++j)if(t[i][j]!=t[1][j])cj=0;
    }
    if(cj==0)return printf("-1\n"),0;
    for(int i=0;i<=26;++i)if(t[1][i]>=2)sa=1;
    for(int i=2;i<=k;++i)for(int j=0;j<=n;++j)
    if(s[i][j]!=s[1][j])++b[i];
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            int flag=1;
            for(int l=2;l<=k;++l)bb[l]=b[l];
            for(int l=2;l<=k;++l){
                if(s[1][i]!=s[l][i])bb[l]--;
                if(s[1][j]!=s[l][i])bb[l]++;
                if(s[1][j]!=s[l][j])bb[l]--;
                if(s[1][i]!=s[l][j])bb[l]++;
                if(bb[l]!=2){if(!sa||bb[l]!=0)flag=0;}
            }
            if(flag==1){
                swap(s[1][i],s[1][j]);
                return printf("%s\n",s[1]),0;
            }
        }
    }
    printf("-1\n");
    return 0;
}
```


---

## 作者：Hoks (赞：2)

## 前言
duel 发生意外后来提款的时候跳到的题，感觉挺水的。

只不过没看懂为什么需要用 hash。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842#information)。
## 思路分析
大致看一遍题意，找到重点突破口应该是 $n\times k\le5\times10^3$。

接着思考下一种暴力的做法，因为我们的答案肯定可以通过交换两个位置的字符的方式得到 $s_1$，逆转这个过程，也就是 $s_1$ 可以通过交换两个字符的方式得到答案。

通过 $n^2$ 枚举交换的两个字符的位置。

接着枚举剩下的字符串，对于每个字符串，$O(n)$ 找出其与答案是差异个数 $x$。

如果 $x=2$ 或者 $x=0$ 并且存在相同字符就是可行。

这样就得到了 $O(n^3k)$ 的算法，无法通过。

考虑优化这个过程，貌似只能在 $O(n)$ 找差异上下手了。

不难发现在这个过程中进行了大量无意义的计算，我们完全可以通过上一次计算出来的结果得到下一次计算出来的结果。

具体的，预处理出 $b_i$ 表示 $s_1$ 和 $s_i$ 的差异数。

那么我们交换了 $s_1$ 的 $i,j$ 两位，其他位的差异数之和显然是不变的，考虑这两位的贡献单独计算即可。

预处理时记得先判所有字符串的字符可重集是否相同，以及标记是否存在相同字符。

复杂度 $O(n^2k)$，因为 $n\times k\le 5\times10^3$，所以可以通过此题。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5010,INF=0x3f3f3f3f3f3f3f3f;
int k,n,ff,a[N],b[N],t[N][27];char s[N][N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    k=read();n=read();for(int i=1;i<=k;i++) rd(s[i],n=0);
    for(int i=1;i<=k;i++)//字符集相同
    {
        for(int j=1;j<=n;j++) t[i][s[i][j]-'a']++;
        for(int j=0;j<26;j++) if(t[i][j]!=t[1][j]){put("-1");goto genshin;}
    }for(int i=0;i<=26;i++) if(t[1][i]>=2) ff=1;//是否有相同
    for(int i=2;i<=k;i++) for(int j=0;j<=n;j++) if(s[i][j]!=s[1][j]) a[i]++;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)//枚举交换 i,j 两位
        {
            int f=1;
            for(int l=2;l<=k;l++) b[l]=a[l];
            for(int l=2;l<=k;l++)//check
            {
                if(s[1][i]!=s[l][i]) b[l]--;
                if(s[1][j]!=s[l][i]) b[l]++;
                if(s[1][j]!=s[l][j]) b[l]--;
                if(s[1][i]!=s[l][j]) b[l]++;
                if(b[l]!=2) if(!ff||b[l]!=0) f=0;
            }
            if(f==1)
            {
                swap(s[1][i],s[1][j]);
                for(int l=1;l<=n;l++) put(s[1][l]);
                goto genshin;
            }
        }put("-1");
    genshin:;flush();return 0;
}

```

---

## 作者：__stick (赞：1)

## 题意

给出 $k$ 个字符串，每个长度都是 $n$，构造出来一个字符串，使得每个字符串都能通过这个字符串交换两个不同位置上的字符得到。

$kn\le5000$。

## 思路

一个非常暴力的想法，枚举所有 $k$ 个串的可能的目标串，即交换一次后 $n^2$ 个串所有可能对应的原串，然后一一检验，看是否合法。

算一下复杂度，一共有 $O(kn^2)$ 个可能的目标串，每次检查是 $kn$ 的，于是就炸了，然后想一想会发现，其实如果一个目标串出现了超过  $k$ 次，则肯定合法，因为所有串都能一次操作到达这个串（必须满足每个串提供的目标串不重复）。

这个如果用 trie 树维护，是 $O(kn^3)$ 的复杂度，不行，但是，我们有万能的 hash，由于一共只有 $O(kn^2)$ 个合法目标串，我们求出它们的 hash 值，然后看有没有 hash 值出现超过 $k$ 次即可。

有人会说，求 hash 值的复杂度度不还是 $O(n)$ 的吗，但是这个题有特殊性质，串是由一个串交换而来，检查 hash 函数：

$ans=\sum\limits_{i=1}^ns_i\cdot b^{n-i+1}$ 

假设交换 $u,v$ ，则我们令 $ans=ans-s_u\cdot10^{n-u+1}-s_v\cdot10^{n-v+1}+s_u\cdot10^{n-v+1}+s_v\cdot10^{n-u+1}$。

就求出了交换 $u,v$ 后字符串的 hash 值，此时均摊就可以 $O(1)$ 求 hash 值了，将其扔到数组中排序求出现次数即可。

复杂度 $O(nk^2\log(nk^2))$ ，由于排序 log 很小，估计能过，冲一发。

发现 wa 了 8，造极限数据试一下，发现只跑了 1.2s，也就是说我们只需要将常数除以 $2 $  就能通过了，想一想发现极限情况是 $k=1$ 。而 $k=2$ 的情况就已经常数除以 $2$ 了，所以特判掉 $k=1$ 的情况，此时随便交换两个位置都行。

记得使用双 hash，cf 可能会卡 hash（这个题应该没多少人用 hash 吧）。
## 代码
比较长，hash 没啥技术含量，上面看懂了就自己去写吧。
```cpp
using namespace std;
template<typename T>
inline bool cmax(T& a,const T& b){return a<b?a=b,1:0;}
template<typename T>
inline bool cmin(T& a,const T& b){return b<a?a=b,1:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef vector<int> vi;
typedef vector<vector<int>>vii;
#define X first
#define Y second
#ifdef ONLINE_JUDGE
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#endif
const int mod=998244353;
const ll INF=0x3f3f3f3f3f3f3f3f;
const int MAXN=5009;
const int mod1=1e9+7,mod2=1e9+9,bas=233;
inline pii operator*(const pii& a,const pii& b){return {(ll)a.first*b.first%mod1,(ll)a.second*b.second%mod2};}
inline pii operator+(const pii& a,const pii& b){return {(a.first+b.first)%mod1,(a.second+b.second)%mod2};}
inline pii operator-(const pii& a,const pii& b){return {(mod1+a.first-b.first)%mod1,(mod2+a.second-b.second)%mod2};}
inline pii operator*(const pii& a,const ll& b){return {(ll)a.first*b%mod1,(ll)a.second*b%mod2};}
inline pii operator+(const pii& a,const ll& b){return {(a.first+b)%mod1,(a.second+b)%mod2};}
inline pii operator+=(pii& a,const pii& b){return a=a+b;}
inline pii operator-=(pii& a,const pii& b){return a=a-b;}
pii h[MAXN];
pii p[MAXN];
pii get(int l,int r)
{
	return h[r]-h[l-1]*p[r-l+1];
}
char s[MAXN][MAXN];
int cnt[MAXN],sum[MAXN];
pii ve[MAXN*MAXN];
signed main()
{
	p[0]={1,1};
	for(int i=1;i<MAXN;i++)p[i]=p[i-1]*bas;
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(20);
	int k,n;cin>>k>>n;
	for(int i=1;i<=k;i++)cin>>(s[i]);
	for(int i=0;i<n;i++)cnt[s[1][i]-'a']++;
	if(k==1)
	{
		swap(s[1][0],s[1][1]);
		cout<<s[1];
		return 0;
	}
	bool flag=1;
	for(int i=2;i<=k;i++)
	{
		for(int j=0;j<n;j++)
		{
			sum[s[i][j]-'a']++;
		}
		for(int i=0;i<26;i++)if(sum[i]!=cnt[i])flag=0;
		memset(sum,0,sizeof(sum));
	}
	if(!flag)
	{
		cout<<-1;
		return 0;
	}
	int cnt=0;
	for(int i=1;i<=k;i++)
	{
		pii h={0,0};
		for(int j=0;j<n;j++)h+=p[n-j]*s[i][j];
		pii a;
		bool flag=0;
		for(int u=0;u<n;u++)
			for(int v=u+1;v<n;v++)
			{
				if(s[i][u]==s[i][v])//一个字符串不能提供相等的目标串，否则会 wa 14
				{
					flag=1;
					continue;
				}
				a=h;
				a-=p[n-u]*s[i][u];
				a-=p[n-v]*s[i][v];
				a+=p[n-u]*s[i][v];
				a+=p[n-v]*s[i][u];
				ve[++cnt]=a;
			}
		if(flag)ve[++cnt]=h;
	}
	sort(ve+1,ve+cnt+1);
	pii ans={-1,-1};
	for(int i=1;i<=cnt;)
	{
		int j=i+1;
		while(j<=cnt&&ve[j]==ve[i])j++;
		if(j-i>=k)
		{
			ans=ve[i];
			break;
		}
		i=j;
	}
	if(ans.first==-1)
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=k;i++)
	{
		pii h={0,0};
		for(int j=0;j<n;j++)h+=p[n-j]*s[i][j];
		pii a;
		for(int u=0;u<n;u++)
			for(int v=u+1;v<n;v++)
			{
				a=h;
				a-=p[n-u]*s[i][u];
				a-=p[n-v]*s[i][v];
				a+=p[n-u]*s[i][v];
				a+=p[n-v]*s[i][u];
				if(a==ans)
				{
					swap(s[i][u],s[i][v]);
					cout<<(s[i]);
					return 0;
				}
			}
	}
	return 0;
}
```


---

## 作者：迟暮天复明 (赞：0)

前言：看到这个题想到了一个一百行的做法和一个立方做法，然后仔细实现了立方做法，然后就寄啦！

一百行的做法简述：枚举每一对串，找一对距离最大的，然后按照距离是 $2,3,4$ 分讨，时间复杂度 $O(n^2k+ nk2^t)$，其中 $t$ 是最大距离。

以下是正文。

枚举换的两个位置，预处理一下每一个串和第一个串的距离，然后就能 $O(1)$ 算出每个串和换完之后的第一个串的距离。显然这个距离只有是 $0$ 或者 $2$ 的时候才成立。如果距离是 $0$ 那么还要判一下是否存在两个相同的字符给他换。总时间复杂度 $O(n^2k)$。

---

