# Tricky and Clever Password

## 题目描述

In his very young years the hero of our story, king Copa, decided that his private data was hidden not enough securely, what is unacceptable for the king. That's why he invented tricky and clever password (later he learned that his password is a palindrome of odd length), and coded all his data using it.

Copa is afraid to forget his password, so he decided to write it on a piece of paper. He is aware that it is insecure to keep password in such way, so he decided to cipher it the following way: he cut $ x $ characters from the start of his password and from the end of it ( $ x $ can be $ 0 $ , and $ 2x $ is strictly less than the password length). He obtained 3 parts of the password. Let's call it $ \mathit{prefix} $ , $ \mathit{middle} $ and $ \mathit{suffix} $ correspondingly, both $ \mathit{prefix} $ and $ \mathit{suffix} $ having equal length and $ \mathit{middle} $ always having odd length. From these parts he made a string $ A+\mathit{prefix}+B+\mathit{middle}+C+\mathit{suffix} $ , where $ A $ , $ B $ and $ C $ are some (possibly empty) strings invented by Copa, and « $ + $ » means concatenation.

Many years have passed, and just yesterday the king Copa found the piece of paper where his ciphered password was written. The password, as well as the strings $ A $ , $ B $ and $ C $ , was completely forgotten by Copa, so he asks you to find a password of maximum possible length, which could be invented, ciphered and written by Copa.

## 样例 #1

### 输入

```
abacaba
```

### 输出

```
1
1 7
```

## 样例 #2

### 输入

```
axbya
```

### 输出

```
3
1 1
2 1
5 1
```

## 样例 #3

### 输入

```
xabyczba
```

### 输出

```
3
2 2
4 1
7 2
```

# 题解

## 作者：luanyanjia (赞：4)

考虑先贪心中间的回文串 $b$，因为这即使影响了两边的字符串，也不会改变最终的总串长。所以先使用 manacher 跑出来每个位置的最长回文半径。

在考虑怎样找出最长的 $a$ 和 $a'$。可以二分答案，设此时答案为 $k$，找出的 $b$ 串为 $s[l\dots r]$，那么其合法的条件就是存在 $i \in [1,l-k]$ 使得 $lcp(s[i\dots n],rev(s)) \ge k$。前缀查询 $lcp$，使用 Z 函数预处理前缀 $\max$ 即可。

代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);          
} 
const int N=1e5+5;
char c[N],rv[N];
int n,p[N],z[N],zt[N],pr[N];
int ans,apos,mx=-1;
inline void manacher(){
	int now=0,mid=0;
	c[0]='~',c[n+1]='!';
	for(int i=1;i<=n;i++){
		if(i<=now)p[i]=min(p[2*mid-i],now-i+1);
		else p[i]=1;
		while(c[i+p[i]]==c[i-p[i]])++p[i];
		if(i+p[i]-1>=now)now=i+p[i]-1,mid=i;
	}
}
inline void ZAlgorithm(){
	int l=0,r=0;
	for(int i=2;i<=n;i++){
		if(i<=r)z[i]=min(z[i-l+1],r-i+1);
		else z[i]=0;
		while(i+z[i]<=n&&rv[i+z[i]]==rv[z[i]+1])++z[i];
		if(i+z[i]>r)r=i+z[i]-1,l=i;
	}
}
inline void zzz(){
	int l=0,r=0;
	for(int i=1;i<=n;i++){
		if(i<=r)zt[i]=min(z[i-l+1],r-i+1);
		else zt[i]=0;
		while(i+zt[i]<=n&&c[i+zt[i]]==rv[zt[i]+1])++zt[i];
		if(i+zt[i]>r)r=i+zt[i]-1,l=i;
	}
}
signed main(){
	scanf("%s",c+1);
	n=strlen(c+1);
	manacher();
	for(int i=1;i<=n;i++)rv[i]=c[n-i+1];
	ZAlgorithm();zzz();
	for(int i=1;i<=n;i++)pr[i]=max(pr[i-1],zt[i]);
	for(int i=1;i<=n;i++){
		int l=i-p[i]+1,r=i+p[i]-1;
		int L=0,R=min(n-r,l-1);
		while(L<=R){
			int k=(L+R)>>1;
			if(pr[l-k]>=k)L=k+1;
			else R=k-1;
		}
		if(R*2+p[i]*2-1>mx)ans=R,apos=i,mx=R*2+p[i]*2-1;
	}
	if(ans){
		printf("3\n");
		for(int i=1;i<=n;i++){
			if(zt[i]>=ans){
				printf("%d %d\n",i,ans);
				break;
			}
		} 
		printf("%d %d\n",apos-p[apos]+1,2*p[apos]-1);
		printf("%d %d\n",n-ans+1,ans);
	}else{
		printf("1\n%d %d\n",apos-p[apos]+1,2*p[apos]-1);
	}
	return 0;
}
```

---

## 作者：y2823774827y (赞：4)

该串分为$x+A+y+B+z+C$

$xyz$是来捣乱的，$A$与$C$对称，$B$长度为奇数，关于中心对称

- $B$可以用$manacher$做一下

- 观察$A,C$，直接在原串的基础上不好匹配，我们把原串翻过来，$C$所处的位置是前缀，可以用$kmp$做一下

>初赛rp++！！

代码有点不可看，只适合拍

```cpp
#include<bits/stdc++.h>
typedef int LL;
const LL maxn=1e6+9;
LL n,ans,az,al;
char s[maxn],s1[maxn],T[maxn];
LL hw[maxn],nxt[maxn],suf[maxn],sux[maxn],sua[maxn];
inline void Change1(){
	for(LL i=1;i<=n;++i){
		s1[i*2-1]=s[i];
		s1[i*2]='#';
	}
}
inline void Manacher(){
	hw[1]=1; LL mid=1,Maxr(1);
	for(LL i=2,N=n<<1;i<=N;++i){
		if(i<Maxr) hw[i]=std::min(hw[(mid<<1)-i],hw[mid]-(i-mid));
		else hw[i]=1;
		while(s1[i-hw[i]]==s1[i+hw[i]]) ++hw[i];
		if(i+hw[i]>Maxr){
			Maxr=i+hw[i]; mid=i;
		}
		
	}
	for(LL i=3;i<=(n<<1);i+=2){
		if(s1[i+hw[i]]=='#') hw[i]--;
		else hw[i]-=2;
		hw[(i>>1)+1]=hw[i]+1;
	}
}
inline void Change2(){
	for(LL i=1,up=n>>1;i<=up;++i) T[i]=s[n+1-i],T[n+1-i]=s[i];
	for(LL i=2,j=0;i<=n;++i){
		while(T[j+1]!=T[i] && j) j=nxt[j];
		if(T[j+1]==T[i]) ++j,nxt[i]=j;
		else nxt[i]=0;
	}
	for(LL i=1,j=0;i<=n;++i){
		while(T[j+1]!=s[i] && j) j=nxt[j];
		if(T[j+1]==s[i]) ++j,suf[i]=j;
		else suf[i]=0;
	}
}
int main(){
	scanf("%s",s+1); n=strlen(s+1);
	Change1();
	Manacher();
	Change2();
	for(LL i=1;i<=n;++i){
		if(suf[i]>=sux[i-1]) sux[i]=suf[i],sua[i]=i;
		else sux[i]=sux[i-1],sua[i]=sua[i-1];
	}
	for(LL i=1;i<=n;++i){
		if(ans<hw[i]+(std::min((sux[i-(hw[i]>>1)-1]),n-(i+(hw[i]>>1)))<<1)){
			ans=hw[i]+(std::min((sux[i-(hw[i]>>1)-1]),n-(i+(hw[i]>>1)))<<1);
			az=i; al=sua[i-(hw[i]>>1)-1];
		}
	}
	if((n-(az+(hw[az]>>1))) && al && suf[al]){
		puts("3");
		LL len(std::min(suf[al],n-(az+(hw[az]>>1))));
		printf("%d %d\n",al-len+1,len);
		printf("%d %d\n",az-(hw[az]>>1),hw[az]);
		printf("%d %d\n",n-len+1,len);
	}else{
		puts("1");
		printf("%d %d",az-(hw[az]>>1),hw[az]);
	}
	return 0;
}
```

---

## 作者：Durant_Lee (赞：3)

我们来重新定义一下题目：

一个长度为奇数的回文串可以写成$a+b+a'$的形式（$a$可以为空），其中$a'$是$a$的反串。现在将它加密成$S$，变成了$x+a+y+b+z+a'$的形式，给出$S$，求最长可能的原串。

一个很显然的结论是：若$i$为原串的中心，则我们一定会选择$S$中以它为中心的最长回文串来作为$b$，这个可以马拉车也可以二分哈希啥的。

那么现在就是要在两边寻找最长匹配。

对于$S$中一个长度的后缀，发现可以和它匹配的位置一定越靠前越优。

因此我们先求对于每个位置向后能和后缀匹配的最长长度，记为$p_i$，这个二分哈希一下就行了。

然后再维护一个数组$h_i$表示长度为$i$的后缀匹配最早出现的位置，这个只需要从左往右扫描$p$，对于第$i$个位置，$h_1\sim h_{p_i}$答案都不会超过$i$，每个位置最多会会被更新一次。

最后我们枚举中心点然后二分左右串的长度即可。
复杂度$O(n\log n)$。

【参考代码】

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define mkp make_pair
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
const int N=1e5+10,bas[]={29,31};
const int mod[]={998244353,19260817};
int n;
int f[N],g[N];
int t[2],pw[2][N],hsl[2][N],hsr[2][N];
pii ans[5];
char s[N];

void iniths()
{
	for(int k=0;k<2;++k)
	{
		pw[k][0]=1;
		for(int i=1;i<=n;++i) pw[k][i]=(ll)pw[k][i-1]*bas[k]%mod[k];
	}		
	for(int k=0;k<2;++k)
	{
		for(int i=1;i<=n;++i) hsl[k][i]=((ll)hsl[k][i-1]*bas[k]+(s[i]-'a'+1))%mod[k];
		for(int i=n;i;--i) hsr[k][i]=((ll)hsr[k][i+1]*bas[k]+(s[i]-'a'+1))%mod[k];
	}
}
pii gethsl(int l,int r)
{
	for(int k=0;k<2;++k) 
		t[k]=(hsl[k][r]-(ll)hsl[k][l-1]*pw[k][r-l+1]%mod[k]+mod[k])%mod[k];
	return mkp(t[0],t[1]);
}
pii gethsr(int l,int r)
{
	for(int k=0;k<2;++k) 
		t[k]=(hsr[k][l]-(ll)hsr[k][r+1]*pw[k][r-l+1]%mod[k]+mod[k])%mod[k];
	return mkp(t[0],t[1]);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("CF30E.in","r",stdin);
	freopen("CF30E.out","w",stdout);
#endif
	scanf("%s",s+1);n=strlen(s+1);iniths();
	for(int i=1;i<=n;++i)
	{
		int l=1,r=min(i,n-i+1);f[i]=1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(gethsl(i-mid+1,i)==gethsr(i,i+mid-1)) f[i]=mid,l=mid+1;
			else r=mid-1;
		}
	}
	//for(int i=1;i<=n;++i) printf("%d ",f[i]); puts("");
	for(int i=1;i<=n;++i)
	{
		int mxl=0,l=1,r=n-i+1;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(gethsl(i,i+mid-1)==gethsr(n-mid+1,n)) mxl=mid,l=mid+1;
			else r=mid-1;
		}
		if(mxl) for(int j=mxl;j && !g[j];--j) g[j]=i;
	}
	int anslen=0;
	for(int k=0;k<3;++k) ans[k]=mkp(-1,-1); 
	for(int i=1;i<=n;++i)
	{
		if(f[i]*2-1>anslen) 
		{
			anslen=f[i]*2-1;
			ans[0]=ans[2]=mkp(-1,-1);ans[1]=mkp(i-f[i]+1,i+f[i]-1);
		}
		int l=1,r=min(i,n-i+1),mxl=0;
		while(l<=r)
		{
			int mid=(l+r)>>1;
			if(n-mid+1>i+f[i]-1 && g[mid] && g[mid]+mid-1<i-f[i]+1) mxl=mid,l=mid+1;
			else r=mid-1;
		}
		if(mxl)
		{
			if(mxl*2+f[i]*2-1>anslen)
			{
				anslen=mxl*2+f[i]*2-1;
				ans[0]=mkp(g[mxl],g[mxl]+mxl-1);ans[1]=mkp(i-f[i]+1,i+f[i]-1);ans[2]=mkp(n-mxl+1,n);
			}
		}
	}
	if(!~ans[0].fi) printf("1\n%d %d",ans[1].fi,ans[1].se-ans[1].fi+1);
	else
	{
		puts("3");
		for(int k=0;k<3;++k) printf("%d %d\n",ans[k].fi,ans[k].se-ans[k].fi+1);
	}
	return 0;
}
```

---

## 作者：CatFromMars (赞：2)

注意到，$B$ 应该是一个回文串，同时 $B$ 取得最长的回文串的时候并不会对答案产生影响。这是因为：
- $B$ 最长会和一组 $A,C$ 重叠：说明此时 $B$ 不是最长，矛盾
- $B$ 最长不会和 $A,C$ 重叠，此时只需要让 $A,C$ 最长即可。

不难对每一个 $i$ 求出以 $i$ 为中心的最长回文串半径。问题转化成：对于区间 $[L, R]$ 要求在 $[R, n)$ 中找到一个最长的后缀 $C$，使得在 $[1, L)$ 中可以找到一个 $C$ 的倒序 $A$。此时只要找到最靠前的 $A$ 即可。

记 $x = |C|$，令 $\operatorname{M}(x)$ 为长度为 $x$ 的后缀的倒序在原串中出现的最靠前位置。显然 $M(x)$ 随着 $x$ 增大单调不降（证明：如果 $\operatorname{M}(x) > \operatorname{M}(y), x < y$，那么显然 $\operatorname{M}(x) = \operatorname{M}(y)$ 成立且更优，与定义矛盾），因此只需要双指针再用用一个字符串哈希维护即可 $O(n)$ 求出 $\operatorname{M}(x)$。

回到原来的问题。

> 在 $[R, n)$ 中找到一个最长的后缀 $C$，使得在 $[1, L)$ 中可以找到一个 $C$ 的倒序 $A$。此时只要找到最靠前的 $A$ 即可。

可以二分判定。

上面说的好混乱 QAQ 具体见代码。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5;
const ll bas = 218721, Mod = 1e9 + 7;
ll has[N + 10][2], pb[N + 10];
//0-for the org       1- for the rev
string str[2];
int n;
void prep() {
	str[1] = str[0];
	reverse(str[1].begin(), str[1].end());
	str[0] = "#" + str[0], str[1] = "#" + str[1];

	n = str[0].size() - 1;
	pb[0] = 1;
	for(int i = 1; i <= n; i++) {
		for(int j = 0; j <= 1; j++)
			has[i][j] = (has[i - 1][j] * bas + str[j][i]) % Mod;
		pb[i] = pb[i - 1] * bas % Mod;
	}
}
ll getlr(int l, int r, int opt) {
	return ((has[r][opt] - has[l - 1][opt] * pb[r - l + 1]) % Mod + Mod) % Mod;
}

int M[N + 10];
void getm() {//求出 M
	int j = 1;
	for(int x = 1; x <= n; x++) {
		while(j + x - 1 <= n && (getlr(1, x, 1) != getlr(j, j + x - 1, 0))) j++;
		if(j + x - 1 <= n && 
			getlr(1, x, 1) == getlr(j, j + x - 1, 0))
			M[x] = j;
		else M[x] = n + 1;
	}
}
int fr[N + 10];
void getr() {//求出以 i 为回文中心的最长回文半径 fr
	for(int i = 1; i <= n; i++) {
		int L = 1, R = min(i, n - i + 1), r = 1;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(getlr(i - mid + 1, i, 0) == 
				getlr(n - (i + mid - 1) + 1, n - i + 1, 1))
					L = mid + 1, r = mid;
			else R = mid - 1;
		}
		fr[i] = r;
		// cout << M[i] << ' ' << fr[i] << endl;
	}
}
void init() {
	cin >> str[0];
	prep();
	getm();
	getr();


	int maxn = 0;
	int rest = 0, maxid = 0;
	for(int i = 1; i <= n; i++) {
		int L = i - fr[i] + 1, R = i + fr[i] - 1;

		int ql = 0, qr = min(n - R, L - 1), ans = 0;
		while(ql <= qr) { //二分
			int mid = (ql + qr) >> 1;
			if(M[mid] + mid - 1 < L && n - mid + 1 > R)
				ql = mid + 1, ans = mid;//判定
			else qr = mid - 1;
		}

		if(ans * 2 + R - L + 1 > maxn) {
			maxn = R - L + 1 + ans * 2;
			maxid = i;
			rest = ans;
		}
	}
	if(!rest) {
		cout << 1 << "\n"
		<< maxid - fr[maxid] + 1 << ' ' << 2 * fr[maxid] - 1 << "\n";
		return ;
	}
	cout << 3 << "\n"
		<< M[rest] << ' ' << rest << "\n"
		<< maxid - fr[maxid] + 1 << ' ' << 2 * fr[maxid] - 1 << "\n"
		<< n - rest + 1 << ' ' << rest << "\n";
}
int main() {
	init();
}
```

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意

将一个字符串分为 $x + a + y + b + z + a'$，使得 $a+b+a'$为回文串，问 $a+b+a'$ 最长的长度。

### 题目分析

首先考虑枚举 $b$ 中心的位置，很明显，对于每个中心 $b$ 越长越好。可以用马拉车快速求出每个点为中心最长的 $b$，然后再考虑对于每个 $b$ 去计算最长的 $a$ 和 $a'$。

因为 $a$ 和 $a'$ 相反，所以可以考虑将原串翻转再与原串做 KMP，记 $a_i$ 表示以 $i$ 结尾，与反串最长匹配长度。特别的，若到 $i$ 可以匹配长度为 $a_i$ 的，也一定可以匹配长度为 $1\sim a_i$ 的。则对于每个 $b_{l\sim r}$，答案为：

$$\max\limits_{i=1}^{i < l} \{\min\{a_i,n-r\}\}\times 2 + r-l+1$$

然后发现我们可以从左到右枚举 $b$ 的中心，然后预处理出 $a$ 的前缀最大即可 $\mathcal O(n)$ 求答案了，记前缀最大为 $s$，则答案为：

$$\max\limits_{i = 1}^{i \le n}\{2 \times \min\{s_i, n-r_i\}+r_i-l_i+1\}$$

然后边更新答案边记录答案的区间即可。

### code
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e5 + 5;
string s, t;
int pi[N], f[N], n, g[N], a[N], b[N], ans, ans1, md, l1, l2, l3, r1, r2, r3;

void Border(string s)
{
	int n = s.size() - 1;
	pi[0] = pi[1] = 0;
	for(int i = 2;i <= n;i++)
	{
		int j = pi[i-1];
		while(j && s[j+1] != s[i])	j = pi[j];
		pi[i] = (s[j + 1] == s[i]) ? j + 1 : 0;
	}
}

int KMP(string s, string t)
{
	int n = s.size() - 1, res = 0;
	Border(t);
	f[0] = 0;
	for(int i = 1;i <= n;i++)
	{
		int j = f[i-1];
		while(j && t[j+1] != s[i])	j = pi[j];
		f[i] = t[j+1] == s[i] ? j + 1 : 0;
		g[i] = f[i];
		if(f[i] == t.size() - 1)	f[i] = pi[f[i]];
	}
	return res;
}

void manacher(string t, int *d)
{
	int mid = 0;
	for(int i = 1;i < t.size();i++)
	{
		if(i < mid + d[mid])	d[i] = min(d[2 * mid - i], mid + d[mid] - i);
		while(i - d[i] >= 0 && t[i - d[i]] == t[i + d[i]])	d[i]++;
		d[i]--;
		if(i + d[i] > mid + d[mid])	mid = i;
	}
}

int main()
{
    cin >> s;
    n = s.size();
    s = "#" + s;
    t = s;
    for(int i = 1;i <= n;i++)   t[i] = s[n-i+1];
    KMP(s, t);
    for(int i = 1;i <= n;i++)
        b[i] = max(b[i-1], g[i]);
    t = "#";
    for(int i = 1;i <= n;i++)   t += s[i], t += "#";
    manacher(t, a);
    for(int i = 1;i <= n;i++)
    {
        if(a[i+i-1] + 2 * min(b[i-a[i+i-1]/2-1], n - i - a[i+i-1]/2) <= ans) continue;
        ans = a[i+i-1] + 2 * min(b[i-a[i+i-1]/2-1], n - i - a[i+i-1]/2);
        ans1 = min(b[i-a[i+i-1]/2-1], n - i - a[i+i-1]/2);
        md = i;
    }
    for(int i = 1;i <= n;i++)
        if(b[i] == ans1)
        {
            r1 = i;
            break;
        }
    l1 = r1 - ans1 + 1;
    l2 = md - a[md+md-1] / 2;
    r2 = md + a[md+md-1] / 2;
    r3 = n;
    l3 = n - ans1 + 1;
    if(ans1 == 0)
    {
        puts("1");
        printf("%d %d\n", l2, r2-l2+1);
    }
    else
    {
        puts("3");
        printf("%d %d\n", l1, r1-l1+1);
        printf("%d %d\n", l2, r2-l2+1);
        printf("%d %d\n", l3, r3-l3+1);
    }
    return 0;
}
```

---

## 作者：C6H14 (赞：2)

## 一点废话

[题目传送门](https://www.luogu.com.cn/problem/CF30E)

[My blog](https://www.luogu.com.cn/blog/128433/#)

## 思路

首先，$a'$ 必定是原串的一个后缀；

其次，假如我们固定 $a'$，$a$ 必定选第一个与 $a'$ 匹配的串；

第三，可以用马拉车预处理出每个位置 $b$ 最长的长度。

基于上面的结论，我们有了一个 $O (n^2 \log n)$ 的做法：

枚举 $b$ 的中点，对 $a'$ 长度二分，然后跑一边 KMP 判断是否可行。

枚举 $b$ 中点不好优化，考虑对二分的判断下手。

先将原串与反串跑KMP，将每一个位置的 border 先求出来，用数组记录匹配中以原串第 $i$ 位结束的串最长匹配串长度及开头，就可以省掉二分，直接求出每一个位置为中点时的答案了，复杂度 $\Theta (n)$。

---

## 作者：pldzy (赞：1)


manacher + exKMP + 二分。

感觉是最粗暴的方法，想出来之后自己硬莽了 4k，荣获题解区最长。

## Solution

约定：下文所提及到的所有的回文串，均指奇长度回文串。

- 显然把题目拆成两个部分，中间的回文串，以及两边相同的连续子串。考虑一下从哪个入手比较好。

- ~~忘记是咋想的了~~，易得从两边相同连续子串 $a$ 和 $c$ 会方便些。发现，它相当于是原串 $S$ 和它的反串 $S'$ 做一次 exKMP，对于原串的每个位置 $i$，$z_i$ 表示从这一位开始最长的合法的 $a$ 的长度。

- 现在考虑对于确定的 $a,c$，如何找到最长的 $b$。我们发现，如果区间 $[i+z_i,n-z_i]$（$n$ 是最后一个下标）中最长的回文串 $b$ 如果覆盖了整个区间，那么这就是 $k=1$ 的情况，即 $[i,n]$ 是一整个回文串。所以，对于 $k=3$ 的情况，$b$ 不可能覆盖完整个 $[i+z_i,n-z_i]$ 区间，所以直接二分答案找到区间 $[i+z_i,n-z_i]$ 中的最长回文串长度即可。

- 考虑如何找到任意一个区间中最长回文串的长度。方法比较套路，二分一个长度 $mid$，表示查找区间中是否存在 $2\times mid +1$ 的回文串。`check(mid)` 就是询问区间是否存在 $i\in [l+mid,r-mid]$，满足 $p_i\geq 2\times mid +1$，其中 $p_i$ 表示以 $i$ 为中心的最长回文串长度，manacher 预处理就好。

- 总复杂度 $O(n\log n)$，瓶颈在二分，跑了 122 ms，感觉挺不错的了。

## Code

实现的话，细节就很多了。

manacher 和 exKMP 的部分直接套板子就行，注意一下 manacher 是把原串扩充之后做的，但做完得转回原串。

存答案的时候也挺麻烦的。

````cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for(int i = a; i <= b; ++i)
#define per(i, a, b) for(int i = a; i >= b; --i)
const int maxn = 2e5 + 5;
int n, m;
char a[maxn], b[maxn], s[maxn << 1];
int q[maxn << 1], p[maxn];
int nxt[maxn], z[maxn];
int st[maxn][30], lg[maxn];
int ans, typ, pt[5][5];

inline void input(){
	char ch = getchar();
	s[0] = '~', s[m = 1] = '#';
	while(ch < 'a' or ch > 'z') ch = getchar();
	while(ch >= 'a' and ch <= 'z') 
		s[++m] = ch, s[++m] = '#', ch = getchar();
}
inline void manacher(){
	int mx = 0, pos = 0;
	rep(i, 1, m){
		q[i] = mx > i ? min(mx - i + 1, q[pos * 2 - i]) : 1;
		while(s[i + q[i]] == s[i - q[i]]) q[i] += 1;
		if(i + q[i] - 1 >= mx)
			mx = i + q[i] - 1, pos = i;
	}
	int tp = -1;
	rep(i, 1, m) if(s[i] >= 'a' and s[i] <= 'z') p[++tp] = (q[i] / 2 - 1) * 2 + 1;
}
inline void getnxt(){
	nxt[0] = n;
	int mx = 0, pos = 1;
	while(nxt[1] + 1 < n and b[nxt[1]] == b[nxt[1] + 1]) nxt[1] += 1; 
	mx = nxt[1];
	rep(i, 2, n - 1){
		nxt[i] = mx < i ? 0 : min(nxt[i - pos], mx - i + 1);
		while(i + nxt[i] < n and b[i + nxt[i]] == b[nxt[i]]) nxt[i] += 1;
		if(i + nxt[i] - 1 >= mx) 
			mx = i + nxt[i] - 1, pos = i;
	}
}
inline void getz(){
	int mx = 0, pos = 0;
	while(z[0] < n and b[z[0]] == a[z[0]]) z[0] += 1;
	mx = z[0] - 1;
	rep(i, 1, n - 1){
		z[i] = mx < i ? 0 : min(nxt[i - pos], mx - i + 1);
		while(i + z[i] < n and a[i + z[i]] == b[z[i]]) z[i] += 1;
		if(i + z[i] - 1 >= mx)
			mx = i + z[i] - 1, pos = i;
	}
}
inline int Max(int x, int y){ return p[x] > p[y] ? x : y;}
inline void pre_st(){
	lg[0] = -1; rep(i, 1, 2e5) lg[i] = lg[i / 2] + 1;
	rep(i, 0, n - 1) st[i][0] = i;
	for(int j = 1; (1 << j) <= n; ++j)
		for(int i = 0; (i + (1 << j) - 1) < n; ++i)
			st[i][j] = Max(st[i][j - 1], st[i + (1 << j - 1)][j - 1]);
}
inline int qry_st(int l, int r){
	if(l == r) return l;
	if(l > r) return 0;
	int k = lg[r - l + 1];
	return Max(st[l][k], st[r - (1 << k) + 1][k]);
}
int id;
inline int qry_mxlen(int L, int R){
	int l = 1, r = (R - L) / 2 + 1, ans = 1; id = -L;
	while(l <= r){
		int mid = (l + r) >> 1, tmp;
		if(p[tmp = qry_st(L + mid, R - mid)] >= mid * 2 + 1) 
			ans = mid, id = tmp, l = mid + 1;
		else r = mid - 1;
	} 
	if(id == -L) ans = 1, id *= -1; else ans = ans * 2 + 1;
	return ans;
}

signed main(){
	input();
	n = -1;
	rep(i, 1, m) if(s[i] >= 'a' and s[i] <= 'z') a[++n] = s[i];
	rep(i, 0, n) b[n - i] = a[i];
	n += 1;
	manacher(), getnxt(), getz();
	pre_st();
	ans = 1, typ = 1, pt[1][0] = 0, pt[1][1] = 1;
	rep(i, 0, n - 1) if(p[i] > ans) 
		ans = p[i], pt[1][0] = i - (p[i] + 1) / 2 + 1, pt[1][1] = p[i];
	rep(i, 0, n - 1){
		if(i + z[i] >= n - 1 - z[i]){
			int len = (n - i); 
			if(len & 1){ if(ans >= len) continue;} else{ if(ans >= len - 1) continue;}
			if(len & 1){
				ans = len, typ = 1;
				pt[1][0] = i, pt[1][1] = len;
			} else{
				ans = len - 1, typ = 3;
				pt[1][0] = i, pt[1][1] = len / 2 - 1;
				pt[2][0] = i + pt[1][1], pt[2][1] = 1;
				pt[3][0] = pt[2][0] + 2, pt[3][1] = len / 2 - 1;
			}
			continue;
		}
		int len = qry_mxlen(i + z[i], n - 1 - z[i]), 
			fll = (n - 1 - z[i]) - (i + z[i]) + 1,
			op = (len == fll ? 1 : 3);
		if(ans >= len + z[i] * 2) continue;
		ans = len + z[i] * 2, typ = op;
		if(op == 1) pt[1][0] = i, pt[1][1] = ans;
		else{
			pt[1][0] = i, pt[1][1] = z[i];
			pt[2][0] = id - (len + 1) / 2 + 1, pt[2][1] = len;
			pt[3][0] = n - 1 - z[i] + 1, pt[3][1] = z[i];
		}
	}
	printf("%lld\n", typ);
	rep(i, 1, typ) printf("%lld %lld\n", pt[i][0] + 1, pt[i][1]);
	return 0;
}
````

----
Thanks for reading.

---

## 作者：EricWan (赞：1)

很恶心的一个字符串算法乱炖。

### Step1

首先，你需要了解一个贪心策略：作为 $middle$ 的串越长越好。

其它题解（除了 Cxny 大佬的）都没有详细证明，这里我还是证明一下吧：

如果 $middle$ 长度增加 $2$，则 $prefix$ 和 $suffix$ 一定各自减少 $1$。如果 $prefix$ 和 $suffix$ 的大小已经是 $1$ 了，很明显，他们就被挤没了，但是因为 $middle$ 之前的长度大于等于 $1$，所以现在一定大于等于 $3$，因此我们可以将它分成三个串，与之前的一个串结果是一样的。

因此我们就可以得知：$prefix$ 和 $suffix$ 的大小可以为 $0$，$middle$ 为以他自己的中心为对称点的最大的奇回文串。

### Step2

注意到上面我说的：

> $middle$ 为以他自己的中心为对称点的最大的奇回文串。

这玩意不就是我们~~陌生~~熟悉的马拉车吗？跑一遍即可。（二分哈希不是不行）

### Setp3

上一步处理完后，我们就可以把问题“简化”为：

在 $middle$ 后的字符串中找到最长后缀，使得它是一个 $middle$ 前的一个子串的逆序。

我们于是可以提前跑一遍 KMP：

![](https://cdn.luogu.com.cn/upload/image_hosting/n6iogipm.png)

通过各种计算，就结束了，但细节很多。

于 2023 年 12 月 21 号更新了图片，更好理解了

---

## 作者：_sunkuangzheng_ (赞：1)

KMP 和马拉车太 hard 了，来个无脑 SA 做法。

---

考虑串 $b$ 是奇回文串，那我们不妨枚举 $b$ 的回文中心。在这里我们贪心的让 $|b|$ 最大，考虑反证：若 $s_x=s_y,b = s[x+1:y-1]$，如果 $x,y$ 不被 $a,a'$ 包含，那么显然拓展更优；否则，将 $x,y$ 给 $b$，令 $a,a'$ 长度同时减少一位，答案也不变。

设回文中心是 $i$，回文串是 $s[l:r](i-l+1=r-i+1)$，我们希望找到最小的 $i$，使得存在 $1 \le j \le k < l$ 且 $s'[j:k] = s[i:n]$。我们不妨对每一个 $i$ 求出最小的 $k$，显然这个值随着 $i$ 的增加单调不增，查询时二分即可。

令 $t = s + \texttt{\#} + s'$，对 $t$ 建 SA，则以 $i$ 为中心的回文半径等于 $\operatorname{LCP}(i,pos_i)$，$pos_i$ 表示 $i$ 在 $s'$ 里的位置。当然我们也可以根据这个求出每个 $i$ 的 $k$ 值，二分 $rk$ 排名区间，得到区间内最小的 $k$ 即可。

整个做法只需要 SA，时间复杂度 $\mathcal O(n \log n)$。下面的代码采用了 $\log^2$ 的 SA 实现，~~获得了第二劣解~~。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 12.01.2024 14:58:51
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,sa[N],rk[N],ok[N],h[N],n,m,ct[N],mp[N],len[N],ans,rm[N],l1,l2,l3,r1,r2,r3,sm;string s;
struct st{
    int st[22][N];
    void init(int *h){
        for(int i = 1;i <= n;i ++) st[0][i] = h[i];
        for(int j = 1;j <= __lg(n);j ++) for(int i = 1;i + (1 << j) - 1 <= n;i ++)
            st[j][i] = min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }int qry(int l,int r){
        int k = __lg(r - l + 1);
        return min(st[k][l],st[k][r-(1<<k)+1]);
    }
}lp,st,ts;
void los(){
    cin >> s,m = s.size(),s = s + '#' + string(s.rbegin(),s.rend()),n = s.size(),s = " " + s;
    for(int i = 1;i <= n;i ++) sa[i] = i,rk[i] = s[i];
    for(int j = 1;j < n;j *= 2){
        for(int i = 1;i <= n;i ++) ok[i] = rk[i]; int p = 0;
        sort(sa+1,sa+n+1,[&](int x,int y){return rk[x] < rk[y] || rk[x] == rk[y] && rk[x + j] < rk[y + j];});
        auto cmp = [&](int x,int y){return ok[x] == ok[y] && ok[x + j] == ok[y + j];};
        for(int i = 1;i <= n;i ++) if(cmp(sa[i],sa[i-1])) rk[sa[i]] = p; else rk[sa[i]] = ++p; if(p == n) break;
    }for(int i = 1,k = 0;i <= n;h[rk[i ++]] = k) for(k --,k = max(k,0);s[i + k] == s[sa[rk[i] - 1] + k];k ++);
    lp.init(h),rm[m + 1] = 1e9;
    auto lcp = [&](int i,int j){
        if(i == j) return n - i + 1;
        if(i = rk[i],j = rk[j],i > j) swap(i,j);
        return lp.qry(i+1,j);
    };
    auto get = [&](int i){return 2 * m + 2 - i;};
    for(int i = 1;i <= m;i ++) ct[i] = lcp(i,get(i));
    // deg.debuga(1,m,ct);
    for(int i = 1;i <= m;i ++) mp[rk[get(i)]] = i;
    for(int i = 1;i <= n;i ++) if(!mp[i]) mp[i] = 1e9;
    st.init(mp);
    for(int i = m;i >= 1;i --){
        int k = rk[i],l,r,ql,qr;
        for(l = 1,r = k;l <= r;){
            int mid = (l + r) / 2;
            if(lcp(sa[mid],sa[k]) >= m - i + 1) r = mid - 1; else l = mid + 1;
        }ql = r + 1;
        for(l = k,r = n;l <= r;){
            int mid = (l + r) / 2;
            if(lcp(sa[mid],sa[k]) >= m - i + 1) l = mid + 1; else r = mid - 1;
        }qr = l - 1;
        int id = st.qry(ql,qr);
        len[i] = id;
    }//deg.debuga(1,m,len);
    for(int i = 1;i <= m;i ++){
        int ql = i - ct[i] + 1,qr = i + ct[i] - 1,l = qr + 1,r = m;
        while(l <= r){
            int mid = (l + r) / 2;
            if(len[mid] < ql) r = mid - 1; else l = mid + 1; 
        }r ++;
        if(ct[i] * 2 - 1 + (m - r + 1) * 2 > ans){
            ans = ct[i] * 2 - 1 + (m - r + 1) * 2;
            r1 = m - r + 1,l1 = len[r] - r1 + 1,l2 = ql,r2 = ct[i] * 2 - 1,l3 = r,r3 = r1;
        }
    }sm += (!!r1) + (!!r2) + (!!r3);
    cout << sm << "\n";
    if(r1) cout << l1 << " " << r1 << "\n";
    if(r2) cout << l2 << " " << r2 << "\n";
    if(r3) cout << l3 << " " << r3 << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

---

## 作者：Cxny (赞：1)

提供一种简单一些的哈希解法。

---

首先容易发现，$\text{B}$ 串长度取到极长一定是**不劣**的。

感性理解一下，$\text{B}$ 串长度增加 $2$ 最多使 $\text{A}$ 串与 $\text{C}$ 串长度各减少 $1$。

我们可以枚举中心点，并通过哈希二分或马拉车解决这个问题。

那么剩下的问题是**在剩下的串中找出最长的后缀，使得其与前半部分的串匹配。**

考虑预处理出长度为 $l$ 的**真**后缀在串中第一次出现的位置 $pos_l$。

发现对于长度为 $l$ 的真后缀，若其在 $i$ 处出现，则长度为 $l-1$ 的真后缀也一定在 $i$ 处出现了。正确性显然。

于是我们发现，$pos_l$ 随着 $l$ 增大**单调不降**。

$O(n)$ 扫一遍就好了。统计答案的时候二分后缀串长即可。

总时间复杂度 $O(n\log n)$。

哈希表具体实现就不贴了。

```cpp
HashTable lhs, rhs; // 正反哈希值
const int maxn = 1e5 + 10;
int n, pos[maxn], tot, anspos, ar, aa;
string s;
vector<pair<int, int>> final;
int main(){
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> s, n = s.size(), fill(pos + 1, pos + n + 1, -1);
	//哈希表预处理
	lhs.init(s);
	reverse(s.begin(), s.end());
	rhs.init(s);
	int len = 1;
	for(int i = 0; i < n && i + len <= n; i++){
		while(i + len <= n && lhs.geths(i, i + len - 1) == rhs.geths(0, len - 1)) pos[len] = i, len++;
	}
	for(int i = 0; i < n; i++){
		int l = 0, r = min(i, n - i - 1), res = 0, ans = -1;
		while(l <= r){
			int mid = (l + r) >> 1;
			// i - mid ~ i
			if(lhs.geths(i, i + mid) == rhs.geths(n - i - 1, n - i + mid - 1)) res = mid, l = mid + 1;
			else r = mid - 1;
		}
		l = 0, r = min(i - res, n - i - res - 1);
		while(l <= r){
			int mid = (l + r) >> 1;
			if(pos[mid] != -1 && pos[mid] + mid - 1 <= i - res - 1) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		if(res * 2 + 1 + ans * 2 > tot) tot = res * 2 + 1 + ans * 2, anspos = i, ar = res, aa = ans;
	}
	int i = anspos, res = ar, ans = aa;
	final.pb({i - res + 1, res * 2 + 1});
	if(ans) final.pb({n - ans + 1, ans}), final.pb({pos[ans] + 1, ans});
	printf("%d\n", final.size());
	sort(final.begin(), final.end());
	for(auto p : final) printf("%d %d\n", p.fi, p.se);
	return 0;
}
```

---

## 作者：Aiopr_2378 (赞：0)

### 解题思路

发现给出的文本串结尾是 $a'$，而前面又有逆序文本 $a$，这启发我们从这里思考。

考虑枚举中间的长度为奇数的回文串 $b$，再从前面向后面匹配串 $a$，应满足 $a'$是原串的逆串的前缀。

考虑快速进行上面算法。使用 manacher 算法快速找到每个回文中心所匹配的最长回文串 $[l,r]$，然后在 $[1,l-1]$ 的位置中快速匹配出串 $S^R$ 的最长前缀匹配，这一步使用 KMP 快速进行，对于每个结尾位置可以预处理出来。

需要注意一个细节，对于每个回文中心的最长回文串 $[l,r]$，找到的最长 $a$ 串要满足与 $[l,r]$ 不交，同时串 $a'$ 也应与 $[l,r]$ 不交，故需要做一些取舍。

时间复杂度 $O(n)$。

### 参考代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define MAXN 200005
int n,m,d[MAXN],tol[MAXN],tor[MAXN];
int nxt[MAXN],match[MAXN],maxx[MAXN],pos[MAXN];
char s[MAXN],t[MAXN],re[MAXN];
struct node{
    int al,l,bl,ar,r,br,totlen;
}ans;
void manacher(){
    t[0]='$';
    t[++m]='#';
    for(int i=1;i<=n;i++) t[++m]=s[i],t[++m]='#';
    for(int l=0,r=0,i=1;i<=m;i++){
        if(i<=r) d[i]=min(d[l+r-i],r-i+1);
        while(t[i+d[i]]==t[i-d[i]]) d[i]++;
        if(i+d[i]-1>r) r=i+d[i]-1,l=i-d[i]+1;
        if(!(i&1)){
            tol[i/2]=(i-d[i])/2+1;
            tor[i/2]=(i+d[i]-1)/2;
        }
    }
}
void kmp(){
    for(int i=1;i<=n;i++) re[i]=s[n-i+1];
    for(int j=0,i=2;i<=n;i++){
        while(j&&re[i]!=re[j+1]) j=nxt[j];
        if(re[i]==re[j+1]) j++;
        nxt[i]=j;
    }
    for(int j=0,i=1;i<=n;i++){
        while(j&&s[i]!=re[j+1]) j=nxt[j];
        if(s[i]==re[j+1]) j++;
        match[i]=j;
    }
    int tmp=0,p=0;
    for(int i=1;i<=n;i++){
        if(match[i]>tmp){
            tmp=match[i],p=i;
        }
        maxx[i]=tmp;
        pos[i]=p;
    }
}
inline void update(int al,int ar,int l,int r,int bl,int br){
    int len=ar-al+1+r-l+1+br-bl+1;
    if(len>ans.totlen){
        ans.al=al,ans.ar=ar,ans.l=l,ans.r=r,ans.bl=bl,ans.br=br;
        ans.totlen=len;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin>>(s+1);
    n=strlen(s+1);
    manacher();
    kmp();
    for(int i=1;i<=n;i++){
        int l=tol[i],r=tor[i];
        int x=l-1,mx=n-r;
        int al=pos[x]-maxx[x]+1;
        int ar=min(pos[x],al+mx-1);
        int bl=n-(ar-al);
        int br=n;
        update(al,ar,l,r,bl,br);
    }
    int t=0;
    if(ans.al<=ans.ar) t++;
    if(ans.l<=ans.r) t++;
    if(ans.bl<=ans.br) t++;
    cout<<t<<endl;
    if(ans.al<=ans.ar) cout<<ans.al<<" "<<ans.ar-ans.al+1<<endl;
    if(ans.l<=ans.r) cout<<ans.l<<" "<<ans.r-ans.l+1<<endl;
    if(ans.bl<=ans.br) cout<<ans.bl<<" "<<ans.br-ans.bl+1<<endl;
    return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

纯哈希题解。

---

首先 $a$ 和 $a'$ 取到极长肯定是不劣的，因为如果 $a$ 和 $a'$ 变长，最多使 $b$ 减短 $2$。

所以考虑枚举最左侧 $x$ 的长度。

首先我们可以预处理每个点 $i$，最大 $j$ 满足 $s[i,i+j-1]=s[n-j+1,n]$。这个可以通过 KMP 实现，不过二分+哈希能够等效替代，将这个长度记为 $len_i$。注意这里 $len_i$ 的长度**不能超过区间长度的一半**。

然后我们预处理每个点 $i$，以它为中心，最长的回文串长度。这个可以用 manacher 实现，不过二分+哈希可以等效替代，将这个长度记为 $d_i$。

那么我们枚举 $x$ 的长度之后，显然可以由 $len_i$ 得到极长的 $a$ 和 $a'$ 分别是 $[i,i+len_i-1]$ 和 $[n-len_i+1,n]$，记为 $[st,en]$。那么我们需要在 $[st+1,en-1]$ 中找到一个形如 $x+b+y$ 的串并且最大化 $b$ 的长度。

显然我们可以二分这个长度 $L$，则如果想要回文串在 $[st,en]$ 内，其中心一定在 $[st+L,en-L]$ 之间，我们只需要找到这中间的最大的 $d_i$，判断是否大于等于 $L$ 即可。这个可以使用 ST 表维护，预处理复杂度 $O(n \log n)$，单次查询 $O(1)$。

总复杂度 $O(n \log n)$。

---

[Code & Submission](https://codeforces.com/contest/30/submission/232914474)

---

