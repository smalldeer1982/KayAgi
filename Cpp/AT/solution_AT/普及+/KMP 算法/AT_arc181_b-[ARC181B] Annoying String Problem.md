# [ARC181B] Annoying String Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc181/tasks/arc181_b

英小文字からなる文字列 $ S,T $ および `0`, `1` からなる文字列 $ X $ に対し、英小文字からなる文字列 $ f(S,T,X) $ を以下のように定めます。

- 空文字列に対し、 $ i=1,2,\dots,|X| $ の順に、 $ X $ の $ i $ 文字目が `0` なら $ S $ を、 `1` なら $ T $ を末尾に結合することで得られる文字列
 
英小文字からなる文字列 $ S $ および `0`, `1` からなる文字列 $ X,Y $ が与えられます。

英小文字からなる文字列 $ T $ （空文字列でもよい）であって、 $ f(S,T,X)=f(S,T,Y) $ が成り立つようなものが存在するか判定してください。

$ t $ 個のテストケースが与えられるのでそれぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ t\ \leq\ 5\ \times\ 10^5 $
- $ 1\ \leq\ |S|\ \leq\ 5\times\ 10^5 $
- $ 1\ \leq\ |X|,|Y|\ \leq\ 5\times\ 10^5 $
- $ S $ は英小文字からなる文字列
- $ X,Y $ は `0`, `1` からなる文字列
- $ 1 $ つの入力に含まれるテストケースについて、 $ |S| $ の総和は $ 5\ \times\ 10^5 $ 以下
- $ 1 $ つの入力に含まれるテストケースについて、 $ |X| $ の総和は $ 5\ \times\ 10^5 $ 以下
- $ 1 $ つの入力に含まれるテストケースについて、 $ |Y| $ の総和は $ 5\ \times\ 10^5 $ 以下
 
### Sample Explanation 1

以下、文字列の結合を $ + $ を用いて表します。 $ 1 $ 番目のテストケースについて、 $ T= $`ara` とすると $ f(S,T,X)=S+T= $`araaraara` $ ,\ f(S,T,Y)=T+T+T= $`araaraara` となるため、 $ f(S,T,X)=f(S,T,Y) $ が成り立ちます。 $ 2,3 $ 番目のテストケースについて、条件を満たす $ T $ は存在しません。

### Sample Explanation 2

$ T $ は空文字列であっても構いません。

## 样例 #1

### 输入

```
3
araara
01
111
araaaa
100100
0010111
abacabac
0
1111```

### 输出

```
Yes
No
No```

## 样例 #2

### 输入

```
2
empty
10101
00
empty
11111
111```

### 输出

```
Yes
Yes```

# 题解

## 作者：Register_int (赞：10)

显然可以先解出 $T$ 的长度 $m$，不是整数或者为 $0$ 为负数的情况先判掉。那么一定会出现：

- $S$ 为 $T$ 的前缀或 $T$ 为 $S$ 的前缀。
- $S$ 为 $T$ 的后缀或 $T$ 为 $S$ 的后缀。

所以必定有 $S,T$ 中较短者为较长者的 $\text{border}$。

不妨设 $n>m$。初始时刻一侧是 $S$ 一侧是 $T$，那么 $S-T$ 剩下的长度为 $n-m$ 的段也是 $S,T$ 的 $\text{border}$。

发现构成了一个辗转相减的过程，减出来的就是两者共同的最小循环节。设其长度为 $l$，直接判断是否有 $l\mid m$ 即可。时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e5 + 10;

int T, n, p, q; char s[MAXN], x[MAXN], y[MAXN];

int cx, cy, len, nxt[MAXN]; ll m;

int main() {
	for (scanf("%d", &T); T--;) {
		scanf("%s%s%s", s, x, y), cx = cy = 0, *nxt = -1;
		n = strlen(s), p = strlen(x), q = strlen(y);
		if (p == q) { puts("Yes"); continue; }
		for (int i = 0; i < p; i++) x[i] & 1 ? cy++ : cx++;
		for (int i = 0; i < q; i++) y[i] & 1 ? cy-- : cx--;
		if ((ll)cx * cy > 0 || !cy || (ll)n * abs(cx) % abs(cy) != 0) { puts("No"); continue; }
		m = (ll)n * -cx / cy;
		for (int i = 0, j = -1; i < n; !~j || s[i] == s[j] ? nxt[++i] = ++j : j = nxt[j]);
		len = n - nxt[n]; if (n % len != 0) len = n;
		puts(m % len == 0 ? "Yes" : "No");
	}
}
```

---

## 作者：qiaochenya (赞：9)

# 题目大意
对于由小写英文字母组成的字符串 $S$ 和 $T$ 以及由 $0$ 和 $1$ 组成的字符串 $X$ ，请定义由小写英文字母组成的字符串 $f(S,T,X)$ 如下：

- 从空字符串开始，对于每个 $i = 1 , 2 , … , ∣ X ∣$ ，如果 $X$ 的第 $i$ 个字符是 $0$ ，则将 $S$ 追加到尾部，如果是 $1$ ，则将 $T$ 追加到尾部。

给你一个由小写英文字母组成的字符串 $S$ 以及由 $0$ 和 $1$ 组成的字符串 $X$ 和 $Y$。

请判断是否存在一个字符串 $T$ （可以为空），使得 $f(S, T, X) = f(S, T, Y)$。

# 思路

$T$ 的长度是可以通过解方程求出来的， $|T| = -\frac{Scnt_0 - Tcnt_0}{Scnt_1 - Tcnt_1}$ ，若长度不为正整数就是无解。

先说结论，当 $X \neq Y$ 时，显然有解， 当  $\gcd(|S|,\ |T|)$ 是 $S$ 的循环节时，有解，那么就非常好做，比赛时想不出来。

证明：

  - 当 $X = Y$ 时显然有解。

  - 讨论 $X \neq Y$ 的情况。

    令 $|S| \leq |T|$ ， $|T| \leq |S|$ 也是同理。

    把 $X,\ Y$ 的相同前后缀删去，那么 $X,\ Y$ 的第一个字符必然不同，$0$ 或 $1$ ，那么 $|T|$ 肯定是 $|S|$ 的一个前缀，令 $|T| = |S| + |T^{'}|$ ，并且将 $X$ 和 $Y$ 的 $1$ 替换成 $01$ ，然后就出现了子问题 $f(S, T^{'}, X^{'}) = f(S, T^{'}, Y^{'})$ ，并且去掉 $X^{'},\ Y^{'}$ 的相同前后缀后，第一个字符必然不同，那么可以用相同的方法一直递归下去，直到 $S$ 或 $T$ 变成空串。

    这就是一个辗转相减法的过程， $\gcd(|S|,\ |T|) = \gcd(|S|, |T| - |S|)$ ，最后的剩余不是空串的长度就是 $\gcd(|T|,\ |S|)$ ，可以得出去掉 $T,\ S$ 相同的部分得到的就是最小循环节， $T,\ S$ 必然是由循环节组成，得证。

最后计算 $|T|$ 时会爆掉，记得开```long long```。

# Code

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long i64;

i64 gcd(i64 a, i64 b) {
	return b ? gcd(b, a % b) : a;
}

bool solve() {
	string s, x, y;
	cin >> s >> x >> y;
	i64 n = s.size(), X = x.size(), Y = y.size();
	i64 cnt[2] = {};
	for (auto x : x) {
		cnt[x - '0']++;
	}
	for (auto x : y) {
		cnt[x - '0']--;
	}
	if (!cnt[0]) {
		return true;
	}
	if (cnt[1] == 0 || n * cnt[0] % cnt[1] != 0 || -n * cnt[0] / cnt[1] < 0) {
		return false;
	}
	i64 m = -n * cnt[0] / cnt[1];
	assert(m >= 0);
	i64 g = gcd(n, m);
	for (int i = 0; i + g < n; i++) {
		if (s[i] != s[i + g]) {
			return false;
		}
	}

	return true;
}

signed main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	
	int T; cin >> T;
	while (T--) {
		cout << (solve() ? "Yes\n" : "No\n");
	}
	
	return 0;
}
```

---

## 作者：I_will_AKIOI (赞：6)

要满足 $f(S,T,X)=f(S,T,Y)$，首先他们的长度得相等。我们已经知道了 $|S|$，就可以通过方程求出 $|T|$。我们定义两个变量 $cnt1,cnt2$，统计 $0$ 和 $1$ 的数量，遍历 $X$ 时对应变量 $+1$，遍历 $Y$ 时对应变量 $-1$。于是列出方程：$cnt1\cdot|s|+cnt2\cdot|T|=0$。解出来 $\displaystyle|T|=-\frac{cnt1\cdot|s|}{cnt2}$。如果解出来不是正整数，说明无解，注意要特判 $cnt1$ 或 $cnt2$ 为 $0$ 的情况。

由于 $f(S,T,X),f(S,T,Y)$ 仅由 $S$ 和 $T$ 组成，根据刚才的式子，可以得出 $cnt1$ 个 $S$ 和 $cnt2$ 个 $T$ 连在一起相等。那么他们肯定要有一个公共的循环子串才能凑出。所以这个循环子串的长度为 $|T|$ 的因数。所以要让这个长度尽可能小，于是用哈希找到 $S$ 的最短循环子串，然后看这个子串的长度是不是 $|T|$ 的因子即可。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod1 998244353
#define mod2 1000000007
#define BASE 13331
#define N 500005
#pragma GCC optimize("O3")
using namespace std;
char s[N],x[N],y[N];
int n,m,a,b;
pair<int,int>h[N],p[N];
pair<int,int>Hash(int l,int r)
{
	int x=((h[r].first-h[l-1].first*p[r-l+1].first%mod1)+mod1)%mod1;
	int y=((h[r].second-h[l-1].second*p[r-l+1].second%mod2)+mod2)%mod2;
	return {x,y};
}
void solve()
{
	int cnt1=0,cnt2=0;
	cin>>s+1>>x+1>>y+1;
	n=strlen(s+1),a=strlen(x+1),b=strlen(y+1);
	for(int i=1;i<=a;i++)//记录cnt1和cnt2
	{
		if(x[i]=='0') cnt1++;
		else cnt2++;
	}
	for(int i=1;i<=b;i++)
	{
		if(y[i]=='0') cnt1--;
		else cnt2--;
	}
	if(cnt1==0)
	{
		cout<<"Yes\n";
		return;
	}
	if(cnt2==0||-cnt1*n%cnt2||-cnt1*n/cnt2<0)//方程的解不是正整数
	{
		cout<<"No\n";
		return;
	}
	p[0]={1,1};
	for(int i=1;i<=n;i++)//哈希预处理
	{
		h[i].first=(h[i-1].first*BASE+s[i]-'a'+1)%mod1;
		h[i].second=(h[i-1].second*BASE+s[i]-'a'+1)%mod2;
		p[i].first=p[i-1].first*BASE%mod1;
		p[i].second=p[i-1].second*BASE%mod2;
	}
	m=-cnt1*n/cnt2;
	int res=INT_MAX;
	for(int i=1;i*i<=n;i++)//找最短循环子串
	{
		if(n%i==0)
		{
			if(Hash(1+i,n)==Hash(1,n-i)) res=min(res,i);
			if(Hash(1+n/i,n)==Hash(1,n-n/i)) res=min(res,n/i);
		}
	}
	if(m%res==0) cout<<"Yes\n";
	else cout<<"No\n";
	return;
}
signed main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：suzhikz (赞：3)

UniGravity 一语点醒梦中人啊。给 UniGravity 大神磕头了。

怎么都是找规律大神。

首先你要会计算 T 的长度，别的题解讲的很清楚不再赘述。

还有就是你要判整除，相等，负数三个情况。

取出 X 和 Y 相同的前缀，发现短串一定是长串的前缀、循环节，那么我们先算 S 的哈希，然后算 T 的哈希，这一步要小心，把 T 拆成 S 的循环部分和需要单独算的部分。

然后就可以直接愉快的哈希了。

但是连循环里的变量都要开 long long 是没想到的，现在还没找到原因。

证明下 T 一定是 S 不断循环的字符串的前缀，取出 X 和 Y 相同的前缀，然后一定一个是 1 一个是 0，那么 T 的开头就一定是 S，若 T 比 S 短，那么已经整完了，否则继续往下比，你一直扫开头不为 1 的那个串，如果下一个是 1 ，则你 $n+1$ 到 $2n$ 的位置和前面是相等的然后你可以一只重复这个操作，如果是 0 则说明 T 还在循环 S，继续扫即可。所以 T 一定是 S 一直循环的字符串的前缀。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define db double
#define il inline
#define int long long
using namespace std;
void read(int &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
//void read(ll &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
const int N=5e5+5,mod=1000000007;
int t;ll n,m,hash1,hash2,hashn,hashm,po[N];
char c[N],d1[N],d2[N],tmp[N];
ll qpow(ll x,ll y){
	ll re=1;
	while(y){
		if(y&1)re=re*x%mod;x=x*x%mod;y>>=1;
	}
	return re;
}
signed main(){
	read(t);
	po[0]=1;
	for(int i=1;i<N;i++)po[i]=po[i-1]*27%mod;
	while(t--){
		scanf("%s",c+1);n=strlen(c+1);
		scanf("%s",d1+1);scanf("%s",d2+1);
		int cnt[2][2]={0};
		int sbstrlen1=strlen(d1+1),sbstrlen2=strlen(d2+1);
		for(int i=1;i<=sbstrlen1;i++){
			cnt[0][d1[i]-'0']++;
		}
		for(int i=1;i<=sbstrlen2;i++){
			cnt[1][d2[i]-'0']++;
		}//n*cnt[0][0]+m*cnt[0][1]=n*cnt[1][0]+m*cnt[1][1]
		hash1=hash2=hashn=hashm=0;
		if((cnt[0][0]-cnt[1][0])*(cnt[1][1]-cnt[0][1])<0){
			puts("No");
		}else if(cnt[1][1]-cnt[0][1]==0&&(cnt[0][0]-cnt[1][0])==0){
			puts("Yes");
		}else if(cnt[1][1]-cnt[0][1]==0){
			puts("No");
		}else if(n*(cnt[0][0]-cnt[1][0])%(cnt[1][1]-cnt[0][1])!=0){
			puts("No");
		}else{
			m=n*(cnt[0][0]-cnt[1][0])/(cnt[1][1]-cnt[0][1]);
			for(int i=1;i<=n;i++){
				hash1=hash1*27%mod+c[i]-'a';hash1%=mod; 
			}
			for(int i=1;i<=m/n;i++){
				hash2=hash2*po[n]%mod+hash1;hash2%=mod;
			}
			for(int i=1;i<=m%n;i++){
				hash2=hash2*27%mod+c[i]-'a';hash2%=mod;
			}
			ll book=qpow(27,m);
			for(int i=1;i<=cnt[0][0]+cnt[0][1];i++){
				if(d1[i]=='0')hashn=hashn*po[n]%mod+hash1;
				else hashn=hashn*book%mod+hash2;
				hashn%=mod;
			}
			for(int i=1;i<=cnt[1][0]+cnt[1][1];i++){
				if(d2[i]=='0')hashm=hashm*po[n]%mod+hash1;
				else hashm=hashm*book%mod+hash2;
				hashm%=mod;
			}
			if(hashn==hashm){
				puts("Yes");
			}else{
				puts("No");
			}
		}
	}
	
	return 0;
}

```

---

## 作者：Hadtsti (赞：1)

### 题意简述

给定长为 $n$ 的字符串 $S$ 和两个 $01$ 串 $A,B$。要求判断是否能够构造字符串 $T$ ，使得按如下方式生成的两个字符串相等：

- 取 $i=1,2,\cdots,|A|$，若 $A_i=0$ 则将 $S$ 拼到字符串末尾；否则将 $T$ 拼到字符串末尾。

- 取 $i=1,2,\cdots,|B|$，若 $B_i=0$ 则将 $S$ 拼到字符串末尾；否则将 $T$ 拼到字符串末尾。

$1\le n,|A|,|B|\le 5\times 10^5$。

### 题目分析

场上有个弱智错误到结束也没看出来。感谢 @luanyanjia 大佬指出。



如果我们发现 $A$ 和 $B$ 中 $0$ 的个数一样，那么 $T$ 可以取空串，直接判断有解；否则若 $A$ 和 $B$ 中 $1$ 的个数一样一定没有解。对于其他情况，我们发现 $T$ 的长度 $m$ 其实通过 $n$ 和 $A,B$ 可以直接计算出来。如果得到的结果不是整数**或者是负数**~~（场上就是这里没判还以为是哈希挂了）~~ 就直接输出无解。剩下的情况，我们分析一下 $T$ 长什么样子：$A$ 和 $B$ 开头相同的部分我们可以扔掉，由 $A_i,B_i$ 不同的第一处 $i$ 我们可以推出，若有 $m\le n$ 则 $T$ 一定是 $S$ 长为 $m$ 的前缀；否则我们得到 $T$ 的长为 $n$ 的前缀与 $S$ 相同，剩下的部分可以用类似的方式推断出来要么是 $S$ 多次重复，要么是结尾部分对应 $S$ 的一段前缀。所以我们相当于知道了 $T$ 的具体形态，那如何判断是否合法呢？可以使用哈希简单地算出题目中两种方案对应的哈希值，判断是否相等即可。数据很良心不卡单哈希。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=1145141,M=998244353;
int t,n,X,Y,cnt1,cnt2,pw[2000010],H[2000010],tmp1,tmp2,H1,H2,PW;
long long m;
char str[2000010],S[2000010],T[2000010];
int main()
{
	pw[0]=1;
	for(int i=1;i<=500000;i++)
		pw[i]=1ll*P*pw[i-1]%M;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s%s%s",str+1,S+1,T+1);
		cnt1=cnt2=0;
		n=strlen(str+1);
		X=strlen(S+1);
		Y=strlen(T+1);
		for(int i=1;i<=X;i++)
			if(S[i]=='1')
				cnt1++;
		for(int i=1;i<=Y;i++)
			if(T[i]=='1')
				cnt2++;
		if(Y-cnt2==X-cnt1)
		{
			puts("Yes");
		    continue;
		}
		if(cnt1==cnt2)
		{
			puts("No");
		    continue;
		}
		if(1ll*n*(Y-cnt2-(X-cnt1))%(cnt1-cnt2))
		{
			puts("No");
		    continue;
		}
		m=1ll*n*(Y-cnt2-(X-cnt1))/(cnt1-cnt2);
		if(m<0)
		{
		    puts("No");
		    continue;
		}
		for(int i=1;i<=n;i++)
			H[i]=(1ll*H[i-1]*P%M+str[i])%M;
		tmp1=tmp2=0,H1=H[n],H2=0,PW=1;
		for(int i=1;i<=m/n;i++)
			H2=(1ll*pw[n]*H2%M+H[n])%M,PW=1ll*PW*pw[n]%M;
		PW=1ll*PW*pw[m%n]%M;
		H2=(1ll*H2*pw[m%n]%M+H[m%n])%M;
		for(int i=1;i<=X;i++)
		{
			if(S[i]=='0')
				tmp1=(1ll*pw[n]*tmp1%M+H1)%M;
			else
				tmp1=(1ll*PW*tmp1%M+H2)%M;
		}
		for(int i=1;i<=Y;i++)
		{
			if(T[i]=='0')
				tmp2=(1ll*pw[n]*tmp2%M+H1)%M;
			else
				tmp2=(1ll*PW*tmp2%M+H2)%M;
		}
    puts(tmp1^tmp2?"No":"Yes");
	}
	return 0;
}
```

---

## 作者：banned_gutongxing (赞：1)

## 思路
首先我们可以根据两个字符串算出另外一个字符串 $T$ 的长度。

算出来之后，因为我们要满足等式两边完全相等，所以很容易得出这两个字符串应该都是由一些公共的字串拼接而成的。设 $S$ 串中最小的周期为 $P$。所以应该满足 $| P|\Large{\mid} \normalsize \gcd(|S|,|T|)$。

其中最小周期可以使用 KMP 算法。如果 $(n-nxt_n)\nmid n$，那么最小周期为 0，否则为 $n-nxt_n$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
namespace gtx{
//	Fast IO
	void read(int &x){
		x = 0;int h = 1;char tmp;
		do{tmp=getchar();if(tmp=='-')h*=-1;}while(!isdigit(tmp));
		while(isdigit(tmp)) x*=10,x+=tmp-'0',tmp=getchar();
		x*=h;
	}
	void read(char &x){do{x=getchar();}while(x==' '||x=='\n'||x=='\r');}
	void write(char x){putchar(x);}
	void write(int x){
		if(x<0) putchar('-'),x=-x;int st[200]={0},tot=0;
		do{st[++tot]=x%10,x/=10;} while(x);
		while(tot){putchar(st[tot--]+'0');};
	}
	void write(int x,char y){write(x);write(y);}
#include<bits/stdc++.h>
	using namespace std;
	const int MAXN = 4e6+10;
	char a[MAXN];
	char x[MAXN],y[MAXN];
	int n,nxt[MAXN],p,q,aa,bb,cc,dd;
	signed main(){
		scanf("%s",a+1);
		n = strlen(a+1);
		for(int i = 2;i<=n;i++){
			int j = nxt[i-1];
			while(j&&!(a[j+1]==a[i])) j = nxt[j];
			if(a[j+1]==a[i]) j++;
			nxt[i] = j;
		}
		scanf("%s%s",x+1,y+1);
		p = strlen(x+1);
		q = strlen(y+1);
		aa=bb=cc=dd=0;
		for(int i = 1;i<=p;i++){
			if(x[i]=='0')aa++;
			else if(x[i]=='1')bb++;
		}
		for(int i = 1;i<=q;i++){
			if(y[i]=='0')cc++;
			else if(y[i]=='1')dd++;
		}
		aa-=cc;
		dd-=bb;
		if(dd==0) return puts(aa==0?"Yes":"No");
		int size_of_t = n*aa/dd;
		if(1ll*n*aa%dd!=0) return puts("No"),0;
		if(size_of_t==n) return puts("Yes"),0;
		if(size_of_t<0) return puts("No"),0;
		int len = (n%(n-nxt[n]))?n:n-nxt[n];
		if(__gcd(size_of_t,n)%len==0) return puts("Yes"),0;
		return puts("No"),0;
	}
}
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T = 1;
	gtx::read(T);
	while(T--) gtx::main();
	return 0;
}
```

---

## 作者：Shxt_Plus (赞：1)

个人认为思路比较自然的一道题。

题意：定义 $f(S,T,X)$ 为一个字符串 $Q$：

对于 $1,2,3,\cdots ,len_x$，若 $X_i$ 为 $0$，把 $S$ 拼到字符串 $Q$ 后面，若 $X_i$ 为 $1$，把 $T$ 拼到字符串 $Q$ 后面。

给出 $S,T,X$，问你能否构造出一个 $T$ 使得 $f(S,T,X) =f(S,T,Y)$。

显然可以通过解一个一元一次方程算出 $T$ 的长度。

考虑 $X$ 与 $Y$ 第一个不相同的位置，发现 $T$ 是 $S$ 的不断循环，那么显然可以直接算出 $T$ 的哈希值是多少，然后直接算出 $f(S,T,X)$ 和 $f(S,T,Y)$ 的哈希值再比较即可。

Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using ll=long long;
using namespace std;
const ll mod=998244353,base=131;
int t;
ll po(ll x,int n)
{
	ll tmp=1;
	while(n)
	{
		if(n&1)tmp=tmp*x%mod;
		x=x*x%mod;
		n>>=1;
	}
	return tmp;
}
signed main()
{
	cin>>t;
	while(t--)
	{
		string s,x,y;
		cin>>s>>x>>y;
		int m=s.size();
		ll ht=0,hs=0;
		int a0=0,b0=0,a1=0,b1=0;
		for(int i=0;i<x.size();i++)
		{
			if(x[i]=='0')a0++;
			else a1++;
		}
		for(int i=0;i<y.size();i++)
		{
			if(y[i]=='0')b0++;
			else b1++;
		}
		if(a0==b0)
		{
			cout<<"Yes\n";
			continue;
		}
		if(a1==b1)
		{
			cout<<"No\n";
			continue;
		}
		int u=m*(b0-a0);
		if(u%(a1-b1)!=0)
		{
			cout<<"No\n";
			continue;
		}
		u/=(a1-b1);
		if(u<0)
		{
			cout<<"No\n";
			continue;
		}
		for(int i=0;i<m;i++)
		{
			hs+=po(base,i)*(s[i]-'a'+1)%mod;
			hs%=mod;
		}
		for(int i=0;i<u/m;i++)
		{
			ht+=po(base,i*m)*hs%mod;
			ht%=mod;
		}
		for(int i=u/m*m;i<u;i++)
		{
			ht+=po(base,i)*(s[i%m]-'a'+1)%mod;
			ht%=mod;
		}
		ll hx=0,hy=0,lenx=0,leny=0;
		for(int i=0;i<x.size();i++)
		{
			if(x[i]=='0')hx+=po(base,lenx)*hs%mod,lenx+=m,lenx%=(mod-1);
			else hx+=po(base,lenx)*ht%mod,lenx+=u,lenx%=mod-1;
			hx%=mod;
		}
		for(int i=0;i<y.size();i++)
		{
			if(y[i]=='0')hy+=po(base,leny)*hs%mod,leny+=m,leny%=(mod-1);
			else hy+=po(base,leny)*ht%mod,leny+=u,leny%=(mod-1);
			hy%=mod;
		}
		if(hx==hy)
		{
			cout<<"Yes\n";
		}
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：yanqijin (赞：0)

# 题目大意
给你两个 $01$ 串，按照 $01$ 串的顺序，依次将字符串 $s$ 与 $t$ 接在空字符串的末尾。如果 $01$ 串的当前位为 $1$，接上去字符串 $s$，否则接上字符串 $t$。所以你可以根据两个 $01$ 串生成两个字符串。现在给你字符串 $s$ 以及告诉你这两个 $01$ 串生产出的串相等，问你有没有字符串 $t$ 满足所有条件。
# 思路
首先我们知道想让两字符串相等，则 $t$ 一定是由若干 $s$ 组合成的。所以我们可以通过解方程解出 $t$ 的长度，然后通过字符串哈希对比出两字符串是否相等。
# Code

```cpp
#include<cstdio>
#define mod 1000000007
using namespace std;
long long t,aa,bb,hha,hhb;
char a[500005],b[500005],s[500005];
void read(long long &x)
{
	x=0;
	int w=1;
	char ch=getchar();
	while(ch<'0' or ch>'9')
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0' and ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=w;
}
void write(long long x)
{
	if(x<0){putchar('-');x=-x;}
	int sta[100],top=0;
	do
	{
		sta[top++]=x%10;
		x/=10;
	}while(x);
	while(top--) putchar(sta[top]+48);
	putchar('\n');
}
long long qpow(long long a,long long b)
{
	long long res=1;
	while(b)
	{
		if(b&1) res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
int main()
{
	read(t);
	while(t--)
	{
		scanf("%s",s+1);
		scanf("%s",a+1);
		scanf("%s",b+1);
		aa=0;bb=0;
		long long lens=0;
		for(int i=1;s[i]!=0;i++) ++lens,aa=(aa*26%mod+s[i]-'a'+1)%mod;
		hha=qpow(26,lens);
		long long u=0,u1=0,uu=0,uu1=0,x=0;
		for(int i=1;a[i]!=0;i++)
		{
			if(a[i]=='1') u++;
			if(a[i]=='0') u1++;
		}
		for(int i=1;b[i]!=0;i++)
		{
			if(b[i]=='1') uu++;
			if(b[i]=='0') uu1++;
		}
		if(u==uu && u1==uu1)
		{
			printf("Yes\n");
		}
		else if(u==uu)
		{
			printf("No\n");
		}
		else
		{
			x=(uu1-u1)*lens/(u-uu);//解方程
			if(x<0)
			{
				printf("No\n");
				continue;
			}
			for(int i=1;i<=x/lens;i++)
			{
				bb=(bb*hha%mod+aa)%mod;
			}
			for(int i=1;i<=x%lens;i++)
			{
				bb=(bb*26%mod+s[i]-'a'+1)%mod;
			}
			hhb=qpow(26,x);
			long long ans=0,ans1=0;
			for(int i=1;a[i]!=0;i++)
			{
				if(a[i]=='0')
				{
					ans=(ans*hha%mod+aa)%mod;
				}
				else ans=(ans*hhb%mod+bb)%mod;
			}
			for(int i=1;b[i]!=0;i++)
			{
				if(b[i]=='0')
				{
					ans1=(ans1*hha%mod+aa)%mod;
				}
				else ans1=(ans1*hhb%mod+bb)%mod;
			}
			if(ans==ans1)//判断
			{
				printf("Yes\n");
			}
			else printf("No\n");
		}
	}
	return 0;
}
```

---

## 作者：luogu_gza (赞：0)

不难注意到 $T$ 一定是由 $S$ 的循环节组成的。

首先，我们可以很容易的计算出 $|T|$，由于我们不需要构造方案，因此只需要检查 $\gcd(|S|,|T|)$ 是否为 $|S|$ 的循环节即可。

[code](https://atcoder.jp/contests/arc181/submissions/56350743)。

---

