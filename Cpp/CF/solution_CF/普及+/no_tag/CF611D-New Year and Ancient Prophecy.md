# New Year and Ancient Prophecy

## 题目描述

给一个n位数，要求将该n位数拆分成若干数字，且需满足：
- 数字的顺序要严格递增
- 数字都是正整数
- 没有前导零

求所有可能的方案数

## 说明/提示

在第一个样本中有8种方法：
“123434”=“123434”（也许给定的序列只是一个大数字）
“123434”=“1”+“23434”
“123434”=“12”+“3434”
“123434”=“123”+“434”
“123434”=“1”+“23”+“434”
“123434”=“1”+“2”+“3434”
“123434”=“1”+“2”+“3”+“434”
“123434”=“1”+“2”+“3”+“4”+“34”

请注意，“123434”=“12”+“34”+“34”不算方案数，因为数字必须严格增加。

在第二个样本中有4种方式：
“20152016”=“20152016”
“20152016”=“20”+“152016”
“20152016”=“201”+“52016”
“20152016”=“2015”+“2016”

## 样例 #1

### 输入

```
6
123434
```

### 输出

```
8
```

## 样例 #2

### 输入

```
8
20152016
```

### 输出

```
4
```

# 题解

## 作者：冒泡ioa (赞：6)

> [博客链接](http://bubbleioa.top/archives/780)
## 题解
$f[i][j]$ 表示 当前串为第j个位置到第i个位置的串的方案数

$O(n^3)$ 做法  
$ f[i][j]=\sum_{j-k< i-j}f[j][k]$   

若 $s(k+1,j)< s(j+1,i),j-k=i-j$ 则 $f[i][j]+=f[j][k]$

$O(n^2)$ 做法  
考虑 $O(1)$ check $s(k+1,j)<s(j+1,i)$   


~~逗逼~~神仙做法：SA  
简单做法：求 $lcp(I,j)$ 即$s[i],s[j]$ 的最长公共前缀
若 $lcp(k,j)<j-k-1 $ 并且  $s[k+ lcp(k,j)+1]< s[j+ lcp(k,j)+1]$ 则合法

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=5010,MOD=1e9+7;
char str[MAXN];
ll f[MAXN][MAXN],sum[MAXN][MAXN];
int lcp[MAXN][MAXN];
int n,a[MAXN];

int check(int x,int y){
	if(lcp[x][y]>=y-x)return false;//y-x就是区间长度
	if(a[x+lcp[x][y]]<a[y+lcp[x][y]])return true;
	if(a[x+lcp[x][y]]>a[y+lcp[x][y]])return false;
	return 0;
}
/*sum[i][j]保存的是f[i][1]+f[i][2]+...+f[i][j]*/
int main(){
    cin>>n;
    scanf("%s",str+1);
    for(int i=1;i<=n;i++){
        a[i]=str[i]-'0';
    }
    for(int i=n;i>=1;i--){//预处理最长公共前缀
        for(int j=n;j>=1;j--){
            if(a[i]==a[j])lcp[i][j]=lcp[i+1][j+1]+1;
        }
    }
    for(int i=1;i<=n;i++)f[i][1]=1;//初始化
    for(int i=1;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(a[j]==0)continue;//不能有前导0
            int k=2*j-i;k=max(1,k);//左端点
            f[i][j]=(f[i][j]+sum[j-1][j-1]-sum[j-1][k-1]+MOD)%MOD;
            k--;
            if(k>=0&&check(k,j))f[i][j]=(f[i][j]+f[j-1][k])%MOD;
        }
        for(int j=1;j<=i;j++)sum[i][j]=(sum[i][j-1]+f[i][j])%MOD;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)ans=(ans+f[n][i])%MOD;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：2)

[$\texttt{Problem Link}$](https://codeforces.com/contest/611/problem/D)

# 简要题意

给定一个数字，可以把数字进行划分成很多连续的段，

问分出的段按顺序单调递增的划分方案有多少种。

# 思路

可以设 $f_{i,j}$ 表示以第 $i$ 个数结尾，且最后一段的长度长为 $j$ 的方案数。

容易得到状态转移方程：
$$
f_{i,j} = \sum\limits^{j}_{k = 1} {f_{i - j - 1,k}}[s[i - j + 1,i] > s[i - j - k + 1, i - j]]
$$

$s[l,r]$ 表示区间 $[l,r]$ 拼成的数。

发现当 $k < j$ 时方案一定合法，可以用前缀和维护，再判断长度为 $j$ 时，是否合法就可以了，具体实现可以看代码。

[$\texttt{Code}$](https://codeforces.com/contest/611/submission/255994923)

---

## 作者：Jμdge (赞：2)

为什么我总在想着用 sam 处理 lcp 呢。。。

这道题支持 $n^2$ lcp 的啊，为什么要费一堆码量去写个那么长的 lcp 呢（虽说会快一丢）

于是就用朴素的写法好了

# noteskey


和楼上大佬讲的一样， dp 状态设计就是：

设 $f[i][j]$  为当前串为 $s[j]...s[i]$ 的方案数

转移就是：

$$f[i][j]=\sum_{k=2·j-i}^{j-1}f[j-1][k]+[s[2j-1...j-1]<=s[j...i]]f[j-1][2j-i-1]$$

后面那一串就是说长度相等要比较两个字符串大小

然后比较字符串大小自然就是求个lcp 然后比较 lcp 后面那位大小了

所以关键还是求两个字符串 lcp 长度

这时候可以用到我们万能的 sam ，但是那个码量啊。。。

所以我们还是用个 $n^2$ 的 lcp 求法吧...

就是我们倒着扫描字符串，令 $lcp[x][y]$ 表示 x、y 开头的两个字符串的 lcp 长度，然后如果 $s[x]==s[y]$ 我们 就可以让 $lcp[x][y]=lcp[x+1][y+1]+1$ 了



# code

```
//by Judge
#include<cstdio>
#include<cstring>
#include<iostream>
#define Rg register
#define fp(i,a,b) for(Rg int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(Rg int i=(a),I=(b)-1;i>I;--i)
#define go(G,u) for(Rg int i=G.head[u],v=G.e[i].to;i;v=G.e[i=G.e[i].nxt].to)
#define ll long long
using namespace std;
const int mod=1e9+7;
const int M=5003;
typedef int arr[M][M];
#ifndef Judge
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
#endif
char buf[1<<21],*p1=buf,*p2=buf;
inline int Max(int x,int y){return x>y?x:y;}
inline int inc(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int read(){ int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0'; return x*f;
} inline void reads(string& s){ char c=getchar();
	for(;!isdigit(c);c=getchar()); s=" ";
	for(;isdigit(c);c=getchar()) s+=c;
} int n,ans; string s; arr lcp,f,sum;
inline bool check(int x,int y){
	if(lcp[x][y]>=y-x) return 0;
	return s[x+lcp[x][y]]<s[y+lcp[x][y]];
}
int main(){ n=read(),reads(s);
	fd(i,n,1) fd(j,n,1) if(s[i]==s[j])
		lcp[i][j]=lcp[i+1][j+1]+1;
	fp(i,1,n) f[i][1]=1;
	fp(i,1,n){
		fp(j,1,i) if(s[j]>48){
			int k=Max(1,2*j-i);
			f[i][j]=inc(f[i][j],inc(sum[j-1][j-1],mod-sum[j-1][k-1]));
			if(--k>=0&&check(k,j)) f[i][j]=inc(f[i][j],f[j-1][k]);
		}
		fp(j,1,i) sum[i][j]=inc(sum[i][j-1],f[i][j]);
	}
	fp(i,1,n) ans=inc(ans,f[n][i]);
	return !printf("%d\n",ans);
}
```





---

## 作者：Schwarzkopf_Henkal (赞：1)

**一道稍微需要想一想的简单DP题。**

在[Soviet Union](http://175.24.116.241/index.php/2020/07/16/cf611d-nyaap/)观看！

一眼看出是个DP，切了，状态$dp_{i,j}$是最后一个数字的范围是$[i,j]$的方法数。对于每个状态，暴力枚举之前的结尾是$i-1$的状态，如果那个状态长度小于或者长度等于但是$substr(k,i-1)<substr(i,j)$，那么就让当前这个状态加上那个状态。然后T了。

显然的，这样的时间复杂度是严格$O(n^3)$，毫无疑问地会T，那么有没有优化的方法？有，其他题解写的都什么鬼？平民优化方法是前缀和。我们注意到当前面的状态的长度小于当前状态的时候允许跳过字符串比较直接加上去，只有当两个状态的长度相同的时候才需要字符串比较。 那么显然的，只要在状态转移的时候直接加上结尾是$i-1$的，长度小于等于$j-i$的状态的和，然后再看和当前状态长度相同的状态在之前有没有可能出现，如果有，尝试比较字符串并且加上（如果比较通过发现之前状态符合要求）那个状态。

这样的时间复杂度是不严格$O(n^3)$，因为仍然存在一个字符串比较的过程，这个过程是$O(n)$的，事实上，在我的[记录](https://www.luogu.com.cn/record/35228613)里有很多个点是接近时限的，如#19,#20,#52等，但是天佑CF，我过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long Mod=1e9+7;
long long n,dp[5005][5005],sum[5005][5005];
string x;
int main(){
    cin>>n>>x;
    x="+"+x;
    for(int i=1;i<=n;i++)
        dp[1][i]=1;
    for(int i=1;i<=n;i++){//尾
        for(int j=i;j>=1;j--){//头
            if(x[j]=='0')
                dp[j][i]=0;//前导零特判
            else {
                dp[j][i]=(dp[j][i]+sum[j-1][min(i-j,j-1)])%Mod;//直接加上前缀和
                if(2*j-i-1>0&&x.substr(j,i-j+1)>x.substr(2*j-i-1,i-j+1))
                    dp[j][i]=(dp[j][i]+dp[2*j-i-1][j-1])%Mod;
            }
            sum[i][i-j+1]=(sum[i][i-j]+dp[j][i])%Mod;//更新前缀和
        }
    }
    long long ans=0;
    for(int i=1;i<=n;i++)
        ans=(ans+dp[i][n])%Mod;
    cout<<ans;
}
```

I'm Schwarzkopf Henkal.

---

## 作者：ifffer_2137 (赞：0)

脑瘫了，没想到严格 $\mathcal O(n^2)$ 做法，二分 HASH 卡常过了。
### 题意
给一个 $n$ 位数，要求将该 $n$ 位数拆分成若干数字，且需满足：

- 数字的顺序要严格递增。
- 数字都是正整数。
- 没有前导零。

求所有可能的方案数，对 $10^9+7$ 取模。
### 分析
暴力 DP，考虑 $\mathcal O(n^2)$ 地设计状态，不难想到令 $f_{i,j}$ 表示第 $i$ 结尾，最后一个数长度为 $j$ 的方案数，那么我们枚举前一个数，由于单调递增，所以转移方程可以容易得到：
$$f_{i,j}=f_{i-j,j}\times[a(i-2j+1,i-j)<a(i-j+1,i)]+\sum_{1\leq k<j}f_{i-j,k}$$
因为一个数小于另一个数，要么位数小于它，要么位数相等。位数严格小于的那部分可以前缀和优化，现在只要判断两个位数相等的数的大小关系就好了，只需要求出它们的最长公共前缀，比较后一位即可。这里我脑瘫没想到预处理，就写了二分 HASH，卡卡常就过了。

具体可以见代码。
### 代码
```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
const int maxn=5e3+5;
const int mod=1e9+7;
const int base=11;
int n;
string a;
int hs[maxn];
int f[maxn][maxn],s[maxn][maxn];
int pw[maxn];
inline int min(int x,int y){
	return x<y?x:y; 
}
inline int HASH(int l,int r){
	int res=hs[r]-1ll*hs[l-1]*pw[r-l+1]%mod+mod;
	if(res>mod) res-=mod;
	return res;
}
inline bool cmp(int x,int y,int len){
	int l=0,r=len,mx=0;
	while(l<=r){
		int m=(l+r)>>1;
		if(HASH(x,x+m-1)==HASH(y,y+m-1)){
			mx=m;
			l=m+1;
		}else{
			r=m-1;
		}
	}
	if(mx==len) return false;
	return a[x+mx]<a[y+mx];
}
signed main(){
	cin.tie(0),cout.tie(0);
	n=read();
	pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=1ll*pw[i-1]*base%mod;
	cin>>a;
	a=' '+a;
	for(int i=1;i<=n;i++){
		hs[i]=1ll*hs[i-1]*base%mod+(a[i]-'0');
		if(hs[i]>mod) hs[i]-=mod;
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<i;j++){
			if(a[i-j+1]=='0') f[i][j]=0;
			else{
				f[i][j]=s[i-j][min(i-j,j-1)];
				if(i>=j*2&&cmp(i-j*2+1,i-j+1,j)){
					f[i][j]=f[i][j]+f[i-j][j];
					if(f[i][j]>mod) f[i][j]-=mod;
				}
			}
			s[i][j]=s[i][j-1]+f[i][j];
			if(s[i][j]>mod) s[i][j]-=mod;
		}
		f[i][i]=1;
		s[i][i]=s[i][i-1]+1;
	}
	if(s[n][n]>mod) s[n][n]-=mod;
	cout<<s[n][n]<<endl;
	return 0;
}
```

---

## 作者：vanyou (赞：0)

## 题目大意

给一个 $n$ 位的大数，把它分成若干个没有前导零的数，并且每个数单调严格递增的划分方法模 $10^9+7$ 的值。

## 思路

考虑使用 dp 求解。

设 $dp_{i,j}$ 表示前 $i$ 个数，第 $i$ 个数必须是某个数的结尾，这个数有 $j$ 位的划分方法。

暴力枚举 $i$ 和 $j$，再枚举上一个数字并判断是否满足条件，即从高位到低位一位位地比大小，这样是 $\mathcal{O}(n^4)$ 的，考虑优化。

可以发现，长度为 $[1,j-1]$ 的数一定满足条件。那么要转移的一定会有 $dp[i-j][1]$ 到 $dp[i-j][j-1]$，这个可以用前缀和优化，只用判长度是 $j$ 的数字是否满足条件就可以了，$\mathcal{O}(n^3)$，继续优化。

判断一个字符串的大小其实可以用倍增思想的 hash 用 $\log$ 的时间得到，本质就是把两个字符串相同的跳过，再判下一个谁大谁小，$\mathcal{O}(n^2 \log n)$，可过。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int M=1e9+7,p=113;
int n,dp[5010][5010],pn[13],h[5010][13];//h数组就是倍增的hash
string s;

bool compare(int x,int y,int len){
	if(x<1) return 1;//长度小于j一定可以 
	for(int j=12;j>=0;j--){
		if((1<<j)>len) continue;
		if(h[x][j]==h[y][j]) len-=(1<<j),x+=(1<<j),y+=(1<<j);//跳过前面相等的部分
	}
	return len&&h[x][0]<h[y][0];//len=0说明完全相等，不满足条件
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	pn[0]=p;
	for(int i=1;i<13;i++) pn[i]=pn[i-1]*pn[i-1]%M;
	cin>>n>>s;
	s=" "+s;
	for(int i=1;i<=n;i++) h[i][0]=s[i];
	for(int j=1;j<13;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) h[i][j]=(h[i][j-1]*pn[j-1]%M+h[i+(1<<j-1)][j-1])%M;//处理倍增
	for(int i=1;i<=n;i++) dp[i][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(s[i-j+1]=='0') continue;//有前导零 
			if(compare(i-2*j+1,i-j+1,j)) dp[i][j]=(dp[i][j]+dp[i-j][j])%M;
			else dp[i][j]=(dp[i][j]+dp[i-j][j-1])%M;
		}
		for(int j=1;j<=n;j++) dp[i][j]=(dp[i][j]+dp[i][j-1])%M;//前缀和 
	}
	cout<<dp[n][n];
	return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[CF611D New Year and Ancient Prophecy](https://www.luogu.com.cn/problem/CF611D)。

不会 SA，用 hash 加二分算 LCP。

## 思路

考虑 dp 状态的设计，$dp_{i,j}$ 表示把从 $i$ 到 $j$ 划成一段的方案总数，答案就是 $\sum^n_{i=1} dp_{i,n}$，不过由于不能有前导零的要求，字符串第 $i$ 位不能为 $0$。

考虑 dp 的转移，如果后面一段比前面一段长（没有前导零，下同），那么一定是可以的，这一部分可以用前缀和优化掉。

如果前一段比后一段长，那么一定不可以，不需要考虑转移，需要考虑的是 $dp_{i-(j-i),i-1}$ 是否可以转移到 $dp_{i,j}$（$i-(j-i)>0$）。

如果可以转移，那么从 $i\sim j$ 这一段需要大于 $i-(j-i)\sim i-1$ 这一段，这里显然直接去掉 LCP 然后比较第一位不同的就可以了，SA 或者 SAM 的板子。

可惜我不会 SA，所以考虑用 hash，然后二分去猜前面 LCP 的长度，算 LCP 的时间复杂度是 $O(\log n)$ 的。

一个双 hash 加手写二分，总时间复杂度为 $O(n^2\log n)$，$n\leq 5000$，CF 神机竟然只跑 300ms 就过了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define pb push_back
#define fir first
#define sec second
#define pii pair<int, int>
#define all(v) v.begin(),v.end()
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
#define lowbit(a) a &(-a)
const int mod = 1e9+7, INF = 1e9;
const int N = 5005, M = 5e5+5;
int dp[5003][5003],q[5003][5003],n;
string s;
unsigned ll h1[N],h2[N],p1[N],p2[N];
bool check(int l1,int r1,int l2,int r2) {
    if(r1<l1) return true;
    unsigned ll za=h1[r1]-h1[l1-1]*p1[r1-l1+1];
    unsigned ll zb=h1[r2]-h1[l2-1]*p1[r2-l2+1];
    unsigned ll xa=h2[r1]-h2[l1-1]*p2[r1-l1+1];
    unsigned ll xb=h2[r2]-h2[l2-1]*p2[r2-l2+1];
    return za==zb && xa==xb;
}
bool cmp(int l1,int r1,int l2,int r2) {
    if(check(l1,r1,l2,r2)) return false;
    int lef=0,rig=r1-l1+1,res=0;
    while(lef<=rig) {
        int mid=lef+rig>>1;
        if(check(l1,l1+mid-1,l2,l2+mid-1)) res=mid,lef=mid+1;
        else rig=mid-1;
    } return s[l1+res]<s[l2+res];
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr),cout.tie(nullptr);
    cin>>n>>s;
    s=" "+s;
    p1[0]=p2[0]=1;
    rep(i,1,n) {
        h1[i]=h1[i-1]*13+(s[i]-'0');
        p1[i]=p1[i-1]*13;
        h2[i]=h2[i-1]*17+(s[i]-'0');
        p2[i]=p2[i-1]*17;
    }
    rep(i,1,n) {
        if(s[i]=='0') continue;
        int cur=0;
        rep(j,i,n) {
            if(i==1) dp[i][j]=1;
            else {
                dp[i][j]+=cur;
                dp[i][j]%=mod;
                int st=i-(j-i+1);
                if(st>0&&cmp(st,i-1,i,j))
                    dp[i][j]+=dp[st][i-1],
                    dp[i][j]%=mod;
                if(st>0) cur+=dp[st][i-1],cur%=mod;
            }
        }
    } int res=0;
    rep(i,1,n) res+=dp[i][n],res%=mod;
    cout<<res<<'\n';
    return 0;
}
```

---

## 作者：ademik (赞：0)

> 给定一个 $n$ 位数，将其拆分成若干个**没有前导零**的**正整数**，满足拆分出的每个正整数**单调递增（不能相等）**，求方案数。

我们记由区间 $[x, y]$ 组成的正整数为 $\overline{(x, y)}$。

我们考虑 DP 解题，令 $f(i, j)$ 表示当前分得的正整数为 $\overline{(j, i)}$ 这一段，初状态为 $f(i, 1)= 1$。转移方程为：

$$f(i, j) = \sum\limits_{k = 1}^{j - 1}f(k, j) \times [\overline{(j, i)} > \overline{(k, j - 1)}]$$

答案即为 $\sum_{i = 1}^{n}f(n, i)$，时间复杂度为  $O(n^4)$，转移 $O(n^3)$，判段大小最劣 $O(n)$。

考虑优化，注意到一个数的位数越多，那么这个数一定越大，故而我们直接求比它位数小的状态，然后再考虑与它长度相等的状态即可。

记 $sum(i, j) = \sum_{j = 1}^{i}f(i, j)$，表现为 以 $i$ 结尾，起点小于等于 $j$ 的方案数。我们可以直接加上长度小的方案数 $sum(j - 1, j - 1) - sum(j - 1, k)$，其中 $k = \max(2 \times j - i, 1)$，表示上一个正整数的起点应该在 $[1, k]$ 之内，此时转移方程为：

$$f(i, j) = sum(j - 1, j - 1) - sum(j - 1, k) + f(j - 1, k) \times [\overline{(j, i)} > \overline{(k, j - 1)}]$$

时间复杂度为 $O(n^3)$。

在考虑优化比较函数，注意到我们实际上比较的是两个串的 $LCP$ 和 $LCP$ 后的第一个字符，故而可以 $O(n^2)$ 预处理出两个串的 $LCP$ 即可。

总时间复杂度为 $O(n^2)$。

#### Code：

```cpp
# include <bits/stdc++.h>
# define TIME 1e3 * clock() / CLOCKS_PER_SEC
using namespace std;
typedef long long i64;
const int N = 5005, Mod = 1e9 + 7;
int n, lcp[N][N];
i64 dp[N][N], sum[N][N]; 
char ch[N]; 
bool check(int x, int y)
{
	if(lcp[x][y] >= y - x) return false;
	if(ch[x + lcp[x][y]] < ch[y + lcp[x][y]]) return true;
	if(ch[x + lcp[x][y]] > ch[y + lcp[x][y]]) return false;
	return false;
}
int main()
{
	ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); 
	cin >>n >>(ch + 1);
	for(int i = n; i >= 1; i --) {
		for(int j = n; j >= 1; j --) {
			if(ch[i] == ch[j]) lcp[i][j] = lcp[i + 1][j + 1] + 1;  
		}
	}
	for(int i = 1; i <= n; i ++) dp[i][1] = 1; 
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= i; j ++) {
			if(ch[j] == '0') continue;
			int k = 2 * j - i; k = max(1, k); 
			(dp[i][j] += sum[j - 1][j - 1] - sum[j - 1][k - 1] + Mod) %= Mod; 
			k --;
			if(k >= 0 && check(k, j)) (dp[i][j] += dp[j - 1][k]) %= Mod; 
		}
		for(int j = 1; j <= i; j ++) sum[i][j] = (sum[i][j - 1] + dp[i][j]) % Mod; 
	}
	i64 ans = 0;
	for(int i = 1; i <= n; i ++) (ans += dp[n][i]) %= Mod; 
	cout <<ans <<endl;
	return 0; 
}
```

---

