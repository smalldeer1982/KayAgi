# Isomorphic Strings

## 题目描述

You are given a string $ s $ of length $ n $ consisting of lowercase English letters.

For two given strings $ s $ and $ t $ , say $ S $ is the set of distinct characters of $ s $ and $ T $ is the set of distinct characters of $ t $ . The strings $ s $ and $ t $ are isomorphic if their lengths are equal and there is a one-to-one mapping (bijection) $ f $ between $ S $ and $ T $ for which $ f(s_{i})=t_{i} $ . Formally:

1. $ f(s_{i})=t_{i} $ for any index $ i $ ,
2. for any character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/f0f59850188390351c083ddc0339cc47c4315e9d.png) there is exactly one character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/cfd6520533d25a050303bbfc24cf098c4a7d5d3f.png) that $ f(x)=y $ ,
3. for any character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/cfd6520533d25a050303bbfc24cf098c4a7d5d3f.png) there is exactly one character ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985F/f0f59850188390351c083ddc0339cc47c4315e9d.png) that $ f(x)=y $ .

For example, the strings "aababc" and "bbcbcz" are isomorphic. Also the strings "aaaww" and "wwwaa" are isomorphic. The following pairs of strings are not isomorphic: "aab" and "bbb", "test" and "best".

You have to handle $ m $ queries characterized by three integers $ x,y,len $ ( $ 1<=x,y<=n-len+1 $ ). For each query check if two substrings $ s[x...\ x+len-1] $ and $ s[y...\ y+len-1] $ are isomorphic.

## 说明/提示

The queries in the example are following:

1. substrings "a" and "a" are isomorphic: $ f(a)=a $ ;
2. substrings "ab" and "ca" are isomorphic: $ f(a)=c $ , $ f(b)=a $ ;
3. substrings "bac" and "aba" are not isomorphic since $ f(b) $ and $ f(c) $ must be equal to $ a $ at same time;
4. substrings "bac" and "cab" are isomorphic: $ f(b)=c $ , $ f(a)=a $ , $ f(c)=b $ .

## 样例 #1

### 输入

```
7 4
abacaba
1 1 1
1 4 2
2 1 3
2 4 3
```

### 输出

```
YES
YES
NO
YES
```

# 题解

## 作者：peterwuyihong (赞：14)

题意：定义两个字符串 $a,b$ 相等为其中一个字符串的字母可以替换另一个字符串的字母，举个例子，$\text{ccf=fft}$ 。给定一个字符串，每次询问两个子串问是否相等。

萌萌题，考虑每个字母是否出现的 $01$ 序列， $\text{Hash}$ 之后每次做个 $26$ 次，把转化为的 $01$ 序列塞入一个 $\text{vec}$ 里，排一下序，判断是否相等即可。

```cpp
#define maxn 200010
typedef unsigned long long ull;
const int p=1e9+7;
int n,m;
char s[maxn];
ull f[maxn][26];
ull pw[maxn];
ull H(int l,int r,int k){
	return (f[r][k]-f[l-1][k]*pw[r-l+1]%p+p)%p;
}
int l,r,len;
vector<int>va,vb;
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	cin>>n>>m;
	cin>>s+1;
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*13331%p;
	for(int i=0;i<26;i++)
	for(int j=1;j<=n;j++)f[j][i]=(f[j-1][i]*13331+(s[j]==i+'a'))%p;
	while(m--){
		cin>>l>>r>>len;
		va.clear(),vb.clear();
		for(int i=0;i<26;i++)va.push_back(H(l,l+len-1,i));
		for(int i=0;i<26;i++)vb.push_back(H(r,r+len-1,i));
		sort(va.begin(),va.end()),sort(vb.begin(),vb.end());
		cout<<(va==vb?"YES":"NO")<<endl;
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
~~自然溢出挂了，差评，这就是CF吗~~

---

## 作者：rui_er (赞：4)

考虑使用字符串哈希。

由于允许将相同的字母替换，我们考虑怎么保证进行替换前后的哈希值不变。容易想到分别对 $26$ 个字母，将原字符串中当前字母替换成 $1$，其它字母替换成 $0$，得到 $26$ 个 `01` 串，对他们进行哈希后排序。此时对字母进行替换不会改变排序后的 $26$ 个哈希值。然后套模板即可。

时间复杂度 $O(n)$，有 $26\log{26}$ 的常数，空间复杂度 $O(n)$。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
using namespace std;
typedef long long ll;
const int N = 2e5+5, B = 101, P = 1e9+7;

int n, m, a[26][N];
char s[N];
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}
struct Hash {
	int h[N], pw[N];
	void init(int *p, int x) {
		pw[0] = 1;
		rep(i, 1, x) h[i] = (1LL * h[i-1] * B % P + p[i]) % P;
		rep(i, 1, x) pw[i] = 1LL * pw[i-1] * B % P;
	}
	int get(int L, int R) {
		return (h[R] - 1LL * h[L-1] * pw[R-L+1] % P + P) % P;
	}
}hsh[26];
vector<int> D, K, ans;

int main() {
	scanf("%d%d%s", &n, &m, s+1);
	rep(i, 1, n) ++a[s[i]-'a'][i];
	rep(i, 0, 25) hsh[i].init(a[i], n);
	rep(i, 1, m) {
		int x, y, len;
		scanf("%d%d%d", &x, &y, &len);
		D.clear(); K.clear();
		rep(k, 0, 25) D.push_back(hsh[k].get(x, x+len-1));
		rep(k, 0, 25) K.push_back(hsh[k].get(y, y+len-1));
		sort(D.begin(), D.end());
		sort(K.begin(), K.end());
		puts(D==K?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：1saunoya (赞：4)

想了几分钟就会了。

我们考虑一个字母在这个区间的出现状况，用 01 表示，区间的 01 用哈希值表示。

考虑搞 26 次，如果对于一个字母有一个和它对应的哈希值，那么这个是可行的。

所以就做完了。

```cpp

int n,m;
const int N = 2e5 + 1;
char s[N];
const int P = 1e9 + 7;
const int base = 2;

int add(const int&x,const int&y){
	if(x+y>=P)
		return x+y-P;
	else
		return x+y;
}

int dec(const int&x,const int&y){
	return add(x,P-y);
}

int mul(const int&x,const int&y){
	return 1ll*x*y%P;
}
int pw[N];
struct gethsh{
	int hsh[N];
	
	int get(int l,int r) {return dec(hsh[r],mul(hsh[l-1],pw[r-l+1]));}
	void init(int k) {rep(i,1,n)hsh[i]=add(mul(hsh[i-1],base),s[i]=='a'+k);}
} hsh[26];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin>>n>>m;
	
	pw[0]=1;
	rep(i,1,n)pw[i]=mul(pw[i-1],base);
	cin>>s+1;
	
	rep(i,0,25)hsh[i].init(i);
	
	while(m--){
		int l1,l2,k;
		cin>>l1>>l2>>k;
		int r1=l1+k-1;
		int r2=l2+k-1;
		vector<int>a,b;
		rep(i,0,25)a.push_back(hsh[i].get(l1,r1));
		rep(i,0,25)b.push_back(hsh[i].get(l2,r2));
		sort(a),sort(b);
		if(a==b)cout<<"YES"<<'\n';
		else cout<<"NO"<<'\n';
	}
	return 0;
}
```

---

## 作者：lalaji2010 (赞：3)

# CF985F

## 思路

题目需要在同一个字符串中不停地截取子串，并询问截出来的两个字符串是否“同构”。

其实我们通过观察就可以发现，如果两个字符串是同构的，那么枚举每一个字母，如果字符串第 $i$ 位等同于当前的字母，则将此位记为 $1$，反之则记为 $0$。

这样我们就得到了 $26$ 个 $01$ 串，根据题目所说的同构字符串的定义，如果两个字符串同构，那么将这 $26$ 个 $01$ 串排个序，它们就必定一一对应。由此可以实现本题的暴力解法。

优化其实也很简单，我们比较 $01$ 串的时间完全可以通过字符串哈希来优化成 $O(1)$ 的，那么本题的时间复杂度就成功优化为了 $O(n+m)$。刚好可以通过本题。

## AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int n,q,l,r,len;
string s;
vector<pair<int,int> > vl,vr;
struct HASH{
    long long sed,mod,has[N][30],pw[N];
    void init(){
        pw[0]=1;
        for(int i=1;i<=200002;i++){
            pw[i]=(pw[i-1]*sed)%mod;
        }
    }
    void Hash(string s_in){
        for(int i=1;i<=s.size()-1;i++){
            for(int j=0;j<26;j++){
                has[i][j]=has[i-1][j]*sed%mod;
                if(s[i]==j+'a'){
                    has[i][j]+=1;
                }else{
                    has[i][j]+=0;
                }
            }
        }
    }
    int get(int l,int r,int lett){
        return (has[r][lett]-has[l-1][lett]*pw[r-l+1]%mod+mod)%mod;
    }
}S1,S2;
int main(){
    cin>>n>>q;
    cin>>s;
    s=" "+s;
    S1.sed=128,S2.sed=131;
    S1.mod=1e9+7,S2.mod=998244353;
    S1.init();
    S2.init();
    S1.Hash(s);
    S2.Hash(s);//双哈希
    while(q--){
    	vl.clear();
    	vr.clear();
        cin>>l>>r>>len;
        for(int i=0;i<26;i++){
        	vl.push_back(make_pair(S1.get(l,l+len-1,i),S2.get(l,l+len-1,i)));
        	vr.push_back(make_pair(S1.get(r,r+len-1,i),S2.get(r,r+len-1,i)));//分别获取两个子串的26个01串
        }
	sort(vl.begin(),vl.end());
	sort(vr.begin(),vr.end());
	if(vl==vr){
		puts("YES");//puts确实是快而且方便
	}else{
		puts("NO");
	}
    }
    return 0;
}
```

---

## 作者：yeshubo_qwq (赞：3)

## Solution

哈希。

两个字符串匹配，与字母无关，而与字母出现的位置有关。

将每个字母出现的位置用 01 表示出来，例如：```ababyz```

$a \to 101000$

$b \to 010100$

$c \to 000000$

...


$x \to 000000$

$y \to 000010$

$z \to 000001$

可以得到 $26$ 个极长的二进制数。

用类似于[字符串哈希](https://www.luogu.com.cn/problem/P3370)的方法，将这 $26$ 个极长的二进制数压缩成可以在 ll 范围内存储的数。

如果两个字符串匹配，将这 $26$ 个数排序得到的数列肯定是相同的。

据此，即可判定两个字符串是否匹配。

## Code

单哈希比较容易被卡，建议使用双哈希。

```cpp
#include <bits/stdc++.h>
#define int long long // 不开 ll 见祖宗！
#define go(i,x,y) for (int i=x;i<=y;i++)
using namespace std;
const int N=2e5+5;
template <typename type>
void read(type &x){
	char c=getchar();
	int F=0;
	while (c!='-' && (c<'0' || c>'9')) c=getchar();
	if (c=='-') F=1,x=0; else x=(c^48);
	c=getchar();
	while (c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if (F) x=-x;
}
template <typename type,typename ... types>
void read(type &x,types &... y){ read(x);read(y...);}
struct node{
	int num[26];
	bool operator == (const node &t) const {
		go(i,0,25) if (num[i]!=t.num[i]) return 0;
		return 1;
	}
};
int n,m,l,r,x;
char str[N];
struct Hash{
	int mod,base;
	int res[26][N],B[N];
	void clear(int t1,int t2){
		base=t1,mod=t2;
		memset(res,0,sizeof(res));
		memset(B,0,sizeof(B));
	}
	void init(){
		go(c,97,122)
			go(i,1,n)
				res[c-97][i]=(res[c-97][i-1]*base%mod+(str[i]==c))%mod;
		B[0]=1;
		go(i,1,n)
			B[i]=(B[i-1]*base)%mod;
	}
	int query(int l,int r,int c){
		return (res[c][r]-res[c][l-1]*B[r-l+1]%mod+mod)%mod;
	}
	node check(int l,int r){
		node tmp;
		go(c,0,25) tmp.num[c]=query(l,r,c);
		sort (tmp.num,tmp.num+26);
		return tmp;
	}
} H,H1;
signed main(){
	read(n,m), scanf("%s",str+1);
	H.clear(2,1e9+7);
	H1.clear(131,994381747);
	H.init(),H1.init();
	go(i,1,m){
		read(l,r,x);
		puts((H.check(l,l+x-1)==H.check(r,r+x-1) && H1.check(l,l+x-1)==H1.check(r,r+x-1)) ? "YES" : "NO");
	}
	return 0;
}

```


---

## 作者：__Hacheylight__ (赞：2)

### CF985F Isomorphic Strings

【题意】

定义两个字符串$S1,S2$同构当且仅当有一种映射关系，使得$S1$映射后与$S2$相同

然后给出一个字符串，给出Q组询问，每组询问S1字符串中$S1[x][x+len-1]$与$S2[y][y+len-1]$的子串是否是同构的

【分析】

读完题之后一头雾水。先打个暴力？TLE 9

之后只能够想正解。 

我们发现两个字符串成映射关系必须满足他们的相邻相同字母的排列方式是相同的。

可能比较绕，我们通过样例来说明一下。

S1：$aabbbc$

S2：$ddeeef$

他们的子串排列方式都是2+3+1的（aa + bbb + c 和 dd + eee + f)

有了这个结论有什么用？ 当然有用。

对于每一个字符，我们哈希出他们的位置(~~位置还能哈希？~~)

怎么哈希我就不说了吧。

例如$S1$

枚举$a$时，我们的哈希值是$(221111)$

枚举$b$时，我们的哈希值是$(112221)$

枚举$c$时，我们的哈希值是$(111112)$

而其他字符的哈希值都是$(111111)$

这样操作又有什么用?用处大着呢

我们发现对于$S2$的哈希值也是$(221111),(1122221),(111112)$,其余23个$(111111)$

我们发现他们的哈希值也成对应关系

**太棒了！ 这样问题就可以解了！**

大家知道再怎么做么？不需要$O(26^2)$的枚举了。直接搞两个$multiset$，把26个哈希值扔进去，判两个$multiset$相同就行了。

算法很牛逼666

【关于哈希的玄学故事】

双哈希在这题上跑的是挺慢的，慢的测试点2300ms，时限是3s，很慌的。

三哈希肯定TLE了

有一位叫做KrK的大佬，过了G题，F题双哈希被Hack了！也是一个红名大佬Hack的

本来这个人最好Rank1

所以写哈希的时候种子最好是$rand$一下哈。

现在没有Hack了于是随便写$seed$就行了。

【代码】

头文件太长请见谅

```cpp
#include <bits/stdc++.h>
using namespace std ;

#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define Rep(i, a, b) for (int (i) = (a) - 1; (i) < (b); (i)++)
#define REP(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define Sort(a, len, cmp) sort(a + 1, a + len + 1, cmp)
#define ass(a, sum) memset(a, sum, sizeof(a))

#define ls ((rt) << 1)
#define rs ((rt) << 1 | 1)
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl '\n'
#define ENDL cout << endl
#define SZ(x) ((int)x.size())

typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef pair <ll, ll> pll ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
typedef map <ll, ll> mll ;

const int N = 200010 ;
const double eps = 1e-8 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const double dinf = 1e30 ;
const int MOD1 = 1000000007 ;
const int MOD2 = 1000000009 ;
const int b1 = 41 ;
const int b2 = 37 ;

inline int read(){
    int X = 0, w = 0 ;
    char ch = 0 ;
    while (!isdigit(ch)) { w |= ch == '-' ; ch = getchar() ; }
    while (isdigit(ch)) X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar() ;
    return w ? - X : X ;
}

void write(int x){
     if (x < 0) putchar('-'), x = - x ;
     if (x > 9) write(x / 10) ;
     putchar(x % 10 + '0') ;
}

void print(int x) {
    cout << x << endl ;
    exit(0) ;
}

void PRINT(string x) {
    cout << x << endl ;
    exit(0) ;
}

void douout(double x){
     printf("%lf\n", x + 0.0000000001) ;
}

pii H[30][N] ;
int pw1[N], pw2[N] ;
int n, m ;
char str[N] ;

pii Get(pii H[], int l, int r) {
    pii ans = H[r] ;
    l-- ;
    if (l >= 0) {
        ans.fi = (ans.fi - ll(H[l].fi) * pw1[r - l] % MOD1 + MOD1) % MOD1 ;
        ans.se = (ans.se - ll(H[l].se) * pw2[r - l] % MOD2 + MOD2) % MOD2 ;
    }
    return ans ;
}

signed main() {
    pw1[0] = pw2[0] = 1 ;
    scanf("%d%d", &n, &m) ;
    scanf("%s", str + 1) ;
    for (int i = 1; i <= n; i++) {
        pw1[i] = 1ll * pw1[i - 1] * b1 % MOD1 ;
        pw2[i] = 1ll * pw2[i - 1] * b2 % MOD2 ;
    }
    for (int i = 1; i <= n; i++)
    for (int j = 0; j < 26; j++) {
        H[j][i].fi = (ll(H[j][i - 1].fi) * b1 + ll(1 + ('a' + j == str[i]))) % MOD1 ;
        H[j][i].se = (ll(H[j][i - 1].se) * b2 + ll(1 + ('a' + j == str[i]))) % MOD2 ;
    }
    while (m--) {
        int x, y, len ;
        scanf("%d%d%d", &x, &y, &len) ;
        multiset <pii> A, B ;
        for (int i = 0; i < 26; i++) {
            A.insert(Get(H[i], x, x + len - 1)) ;
            B.insert(Get(H[i], y, y + len - 1)) ;
        }
        printf("%s\n", A == B ? "YES" : "NO") ;
    }
}
```


---

## 作者：Arghariza (赞：2)

其实哈希有一个技巧，开ull直接让它自然溢出。

~~啥事没有。~~

哈希还有个技巧，在比对字符串的时候同时比较长度，这样冲突的概率会小一点。

考虑两个字符串匹配，对于两个字符串里面每一个字母写出这个字母在串每一位是否存在的情况，例如：

$abacabcaabbaab$：

$a:10101001100110$

$b:01000100011001$

$c:00010010000000$

$d\to z:00000000000000$

然后把两个字符串用字符串哈希处理一下丢进 muliset 里自己比较是否相同就行了。

运气好，单哈希能过；~~运气不好，双哈希也不一定能过...~~

但是双哈希跑得飞快，单哈希慢成了树懒。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
    inline int read() {
        int w = 1, q = 0;
        char ch = ' ';
        while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
        if (ch == '-') w = -1, ch = getchar();
        while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
        return w * q;
    }
    inline void write(int x) {
        if (x < 0) {
            x = ~(x - 1);
            putchar('-');
        }
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace std;
using namespace mystd;

const int maxn = 2e5 + 200;;
const int mod = 1e9 + 7;
const int base = 114514;

int n, m, pw[maxn], h[26][maxn];;
char ch[maxn];

int get(int id, int l, int r) {
    int res = h[id][r];
    l--;
    if (l >= 0) {
        res = (res - h[id][l] * pw[r - l] % mod + mod) % mod;
    }
    return res;
}

signed main() {
    pw[0] = 1;
    for (int i = 1; i < maxn; i++) {
        pw[i] = pw[i - 1] * base % mod;
    }
    n = read();
    m = read();
    scanf("%s", ch + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= 25; j++) {
            h[j][i] = (h[j][i - 1] * base + 1 + (j == ch[i] - 'a')) % mod;
        }
    }
    for (int k = 1, l, r, len; k <= m; k++) {
        l = read();
        r = read();
        len = read();
        multiset<int> s, t;
        for (int i = 0; i <= 25; i++) {
            s.insert(get(i, l, l + len - 1));
            t.insert(get(i, r, r + len - 1));
        }
        printf("%s\n", s == t ? "YES" : "NO");
    }
    return 0;
}

```

---

## 作者：Juanzhang (赞：2)

**$\verb|soltion:|$**

- 考虑 $hash$，$hash$ 出每个字符在两个区间中的出现位置，然后排序判是否相等即可

那么如何 $hash$ ？

要 $hash$ 出每个字符出现为止到区间开头的距离。

对于每个字符存下所有的出现位置，即 $$h_i=pos_1\times base^{tot-1}+pos_2\times base^{tot-2}+\cdots+pos_{tot}$$

每个字符到查询区间（$[l,r]$）区间开头的位置即为 $$(pos_x-l)\times base^{y-x}+(pos_{x+1}-l)\times base^{y-x-1}+\cdots+(pos_y-l)$$

即 $$pos_x\times base^{y-x}+pos_{x+1}\times base^{y-x-1}+\cdots+pos_y-l(1+base+base^2+\cdots base^{y-x})$$

用等比数列求和 $$pos_x\times base^{y-x}+pos_{x+1}\times base^{y-x-1}+\cdots+pos_y-\frac{l\times(base^{y-x+1}-1)}{base-1}$$

求一下逆元，然后就普通 $hash$ 就好了

**代码：**（用的双 $hash$ ~~代码略显臃肿~~，又记了一下区间字符个数防被插 $Q\omega Q$）

``` cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> pii;
const int maxn = 2e5 + 10, base = 1e5 + 3, P1 = 1e9 + 7, P2 = 1e9 + 9, inv_b1 = 540539193, inv_b2 = 63828724;
int n, m, sum[26][maxn], pow1[maxn], pow2[maxn]; char str[maxn]; pair <pii, int> s1[26], s2[26];
struct hashmap {
	vector <int> vec, sum1, sum2;
	void init(char c) {
		vec.push_back(0), sum1.push_back(0), sum2.push_back(0);
		for (int i = 1; i <= n; i++) {
			if (str[i] == c) {
				vec.push_back(i);
				sum1.push_back((1ll * base * sum1.back() + i) % P1);
				sum2.push_back((1ll * base * sum2.back() + i) % P2);
			}
		}
	}
	pii get(int l, int r) {
		int pl = lower_bound(vec.begin(), vec.end(), l) - vec.begin();
		int pr = upper_bound(vec.begin(), vec.end(), r) - vec.begin() - 1;
		return pr < pl ? pii(-1, -1) :
    	pii(((sum1[pr] - 1ll * sum1[pl - 1] * pow1[pr - pl + 1] % P1 + P1) % P1 - 1ll * l * (pow1[pr - pl + 1] + P1 - 1) % P1 * inv_b1 % P1 + P1) % P1,
            ((sum2[pr] - 1ll * sum2[pl - 1] * pow2[pr - pl + 1] % P2 + P2) % P2 - 1ll * l * (pow2[pr - pl + 1] + P2 - 1) % P2 * inv_b2 % P2 + P2) % P2);
	}
} h[26];

int main() {
	int p1, p2, k; pow1[0] = pow2[0] = 1;
	scanf("%d %d %s", &n, &m, str + 1);
	for (int i = 0; i < 26; i++) {
		h[i].init('a' + i);
	}
	for (int i = 1; i <= n; i++) {
		pow1[i] = 1ll * base * pow1[i - 1] % P1;
		pow2[i] = 1ll * base * pow2[i - 1] % P2;
		for (int j = 0; j < 26; j++) {
			sum[j][i] = sum[j][i - 1];
		}
		sum[str[i] - 'a'][i]++;
	}
	while (m--) {
		scanf("%d %d %d", &p1, &p2, &k);
		for (int i = 0; i < 26; i++) {
			s1[i] = make_pair(h[i].get(p1, p1 + k - 1), sum[i][p1 + k - 1] - sum[i][p1 - 1]);
			s2[i] = make_pair(h[i].get(p2, p2 + k - 1), sum[i][p2 + k - 1] - sum[i][p2 - 1]);
		}
		bool flg = 1;
		sort(s1, s1 + 26), sort(s2, s2 + 26);
		for (int i = 0; i < 26 && flg; i++) {
			flg &= s1[i] == s2[i];
		}
		puts(flg ? "YES" : "NO");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

先讲下题意：给你一个字符串，m次查询，每次查询给你两个起点和长度，问这两个字符串是否为同构字符串（通过映射）

我们可以使用哈希来做

对于每个字母，我们记录他出现的位置，并且哈希，加前缀和。

对于每次查询，把26个字母的位置的哈希值放到multiset或vector排序
如果一样就是YES否则是NO

最好使用双哈希，否则可能会被hack（KrK双哈希也被hack了-^^-）

具体细节见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
const int mod1=1000000007;
const int mod2=1000000009;
const int arg1=20040911;
const int arg2=20050715;
int pw1[N],pw2[N];
int n,m;
char str[N];
vector<int>v;
pair<int,int>h[26][N];
pair<int,int>get(pair<int,int>h[],int lef,int rig)
{
	pair<int,int>my=h[rig];
	lef--;
	if(lef>=0)
	{
		my.first=(my.first-(long long)(h[lef].first)*pw1[rig-lef]%mod1+mod1)%mod1;
		my.second=(my.second-(long long)(h[lef].second)*pw2[rig-lef]%mod2+mod2)%mod2;
	}
	return my;
} 
int main()
{
	pw1[0]=pw2[0]=1;
	for(int i=1;i<N;i++)
	{
		pw1[i]=(long long)pw1[i-1]*arg1%mod1;
		pw2[i]=(long long)pw2[i-1]*arg2%mod2;
	}
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<26;j++)
		{
			h[j][i].first=((long long)(h[j][i-1].first)*arg1+(long long)(1+('a'+j==str[i])))%mod1;
			h[j][i].second=((long long)(h[j][i-1].second)*arg2+(long long)(1+('a'+j==str[i])))%mod2;
		}
	}
	while(m--)
	{
		int x,y,len;
		scanf("%d%d%d",&x,&y,&len);
		multiset<pair<int,int>>a,b;
		for(int i=0;i<26;i++)
		{
			a.insert(get(h[i],x,x+len-1));
			b.insert(get(h[i],y,y+len-1));
		}
		printf("%s\n",a==b?"YES":"NO");
	}
	return 0;
}

```

---

## 作者：Hoks (赞：1)

## 前言
比较简单的题。

摘自 [杂题选做](https://www.luogu.com.cn/training/518105)。
## 思路分析
字符串匹配但是与字母无关，而与顺序有关。

比较自然的一个思路，考虑给字符串前后搞个差值匹配下避免字符的差异。

显然不可行，因为前后差值不相等。

貌似没有什么能够线性的做法了？

那么就把值域也扔上去试试。

枚举每个字符 $j$，那么字符串即可变为一个 $01$ 串。

那么题意就可以转化为对于两个组中的 $26$ 个 $01$ 串能不能都匹配上。

考虑直接排序，按照顺序尝试匹配即可。

复杂度 $O(nmw\log w)$，其中 $w=26$。

考虑优化这个过程。

因为不带修，考虑进行 Hash，就可以把 $n$ 优化掉，复杂度来到 $O(mw\log w)$，可以通过。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,V=1e5+10,M=24,mod=1004535809,p=13331;
int n,m,op[N],h[27][N];char s[N];vector<int>a,b;
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='.'||c=='#'); }
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
inline int hsh(int i,int x,int l){return (h[i][x+l-1]-h[i][x-1]*op[l]%mod+mod)%mod;}
signed main()
{
    read(),m=read();rd(s,n);for(int i=op[0]=1;i<=n;i++) op[i]=op[i-1]*p%mod;
    for(int j='a';j<='z';j++) for(int i=1;i<=n;i++) h[j-'a'][i]=h[j-'a'][i-1]*p%mod+(s[i]==j);
    for(int i=1,x,y,l;i<=m;i++)
    {
        x=read(),y=read(),l=read();int f=0;a.clear();b.clear();
        for(int j='a';j<='z';j++) a.emplace_back(hsh(j-'a',x,l)),b.emplace_back(hsh(j-'a',y,l));
        sort(a.begin(),a.end());sort(b.begin(),b.end());
        for(int j=0;j<a.size();j++) f|=(a[j]!=b[j]);
        put(f?"NO\n":"YES\n");
    }
    genshin:;flush();return 0;
}
```

---

## 作者：shinkuu (赞：1)

今天翻过的题时发现我用了一种不一样的哈希方法。我觉得也很自然的啊！为什么题解都是一个做法/yiw

注意到没有两个相同的字符会转换成同一个字符，反之亦然。所以我们只用关心同种字符之间的相对位置关系。

看到这个东西就想到对 $lst_i$ 进行哈希，$lst_i$ 表示在 $i$ 之前第一个和 $s_i$ 相同的位置。

但是显然还有个问题，就是在该子串中 $lst_i<l$ 的情况要去掉。去掉的方式可以直接减掉哈希值，这些位置显然最多只有 $\left|\sum\right|$ 个并且可以直接 $O(n\left|\sum\right|)$ 预处理出来。然后就做完了。

code：

```cpp
const int mod1=998244853,base1=19260817,mod2=1e9+9,base2=142857;
int n,m,pw1[N],pw2[N],s1[N],s2[N],pre[N],c1[N],c2[N],suf[N][26],lst[26];
char str[N];
mt19937 rnd(time(0));
il pii get_hash(int l,int r){return Mp((s1[r]-1ll*s1[l-1]*pw1[r-l+1]%mod1+mod1)%mod1,(s2[r]-1ll*s2[l-1]*pw2[r-l+1]%mod2+mod2)%mod2);}
void Yorushika(){
	scanf("%d%d%s",&n,&m,str+1);
	rep(i,1,n)c1[i]=i,c2[i]=i;
	pw1[0]=pw2[0]=1;
	rep(i,1,n){
		pw1[i]=1ll*pw1[i-1]*base1%mod1;
		pw2[i]=1ll*pw2[i-1]*base2%mod2;
		int x=str[i]-'a';
		pre[i]=i-lst[x],lst[x]=i;
		s1[i]=(1ll*s1[i-1]*base1+c1[pre[i]])%mod1;
		s2[i]=(1ll*s2[i-1]*base2+c2[pre[i]])%mod2;
	}
	mems(lst,0x3f);
	drep(i,n,1){
		int x=str[i]-'a';
		lst[x]=i;
		rep(j,0,25)suf[i][j]=lst[j];
	}
	rep(i,1,m){
		int x,y,l;scanf("%d%d%d",&x,&y,&l);
		pii a=get_hash(x,x+l-1),b=get_hash(y,y+l-1);
		rep(j,0,25){
			if(suf[x][j]<x+l){
				int p=suf[x][j];
				a.fi=(a.fi+mod1-1ll*c1[pre[p]]*pw1[x+l-p-1]%mod1)%mod1;
				a.se=(a.se+mod2-1ll*c2[pre[p]]*pw2[x+l-p-1]%mod2)%mod2;
			}
			if(suf[y][j]<y+l){
				int p=suf[y][j];
				b.fi=(b.fi+mod1-1ll*c1[pre[p]]*pw1[y+l-p-1]%mod1)%mod1;
				b.se=(b.se+mod2-1ll*c2[pre[p]]*pw2[y+l-p-1]%mod2)%mod2;
			}
		}
		puts(a==b?"YES":"NO");
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

## 作者：Y_ATM_K (赞：1)

## 分析
我们发现对于同构串，我们只关心字符的位置。

于是对于每种字母，统计每个位置是否出现过的 $01$ 序列。

这样每个询问，只要把其中一个子串中每个字母的 $01$ 序列哈希值丢进 map 里面，若另一个子串所有哈希值都能在 map 中找到，则这两个串是同构的。

如果用 unordered_map，那么时间复杂度为 $O(m)$。

## 代码
```cpp
#include <bits/stdc++.h>
#define N 200005
using namespace std;
const int P=1e9+7,base=13331;
int n,m,h[26][N],b[N];
char s[N];
unordered_map<int,bool> mp;
int main() {
	scanf("%d%d%s",&n,&m,s);
	b[0]=1;
	for(int i=1;i<=n;++i) b[i]=1ll*b[i-1]*base%P;
	for(int i=0;i<26;++i) {
		int res=0;
		for(int j=0;j<n;++j) {
			res=(1ll*res*base+(s[j]-'a'==i))%P;
			h[i][j]=res;
		}
	}
	while(m--) {
		int xl,yl,len;
		scanf("%d%d%d",&xl,&yl,&len);
		xl--,yl--;
		mp.clear();
		int xr=xl+len-1,yr=yl+len-1;
		for(int i=0;i<26;++i) {
			mp[((h[i][xr]-1ll*h[i][xl-1]*b[len]%P)%P+P)%P]=1;
		}
		bool flg=1;
		for(int i=0;i<26&&flg;++i) {
			if(mp.find(((h[i][yr]-1ll*h[i][yl-1]*b[len]%P)%P+P)%P)==mp.end()) flg=0;
		}
		flg?puts("YES"):puts("NO");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

#### 思路

对每一个字符构建一个 $ 01 $ 串，表示原字符串第几个位置是否是这个字符。每次询问只需将所有小写字母的 $ 01 $ 串的哈希值找出，排序，然后判断是否依依相等即可。

#### 代码

```
#include <bits/stdc++.h>
using namespace std;
#define sed 2
#define mod 998244353
typedef long long ll;
const int N = 2e5 + 5 , M = 26 + 5;
int n , m , x , y , len;
char s[N];
ll a[N][M] , h[N][M] , pw[N] , p[M] , q[M];
ll query(int l , int r , int p)
{
	return (h[r][p] - h[l - 1][p] * pw[r - l + 1] % mod + mod) % mod;
}
int main()
{
	cin >> n >> m;
	cin >> (s + 1);
	pw[0] = 1;
	for(int i = 1 ; i <= n ; ++ i )
	{
		pw[i] = pw[i - 1] * sed % mod;
		for(int j = 'a' ; j <= 'z' ; ++ j )
		{
			int k = j - 'a' + 1;
			a[i][k] = (s[i] == j);
			h[i][k] = (h[i - 1][k] * sed % mod + a[i][k]) % mod;
		}
	}
	while(m --)
	{
		cin >> x >> y >> len;
		bool flag = 0;
		for(int i = 1 ; i <= 26 ; ++ i)
		{
			p[i] = query(x , x + len - 1 , i);
			q[i] = query(y , y + len - 1 , i); 
		}
		sort(p + 1 , p + 1 + 26);
		sort(q + 1 , q + 1 + 26);
		for(int i = 1 ; i <= 26 ; ++ i)
		{
			if(p[i] != q[i])
			{
				flag = 1;
				break;	
			}	
		} 
		if(!flag) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}

---

## 作者：Planetary_system (赞：0)

## 题面解释：
长度为 $n$ 的字符串，问两个子串是否匹配，即字母满足唯一替换。

## 思路分析：
两个字符串匹配，当且仅当其中相同字母的分布情况相同，那么我们可以将 $26$ 种字母分别考虑，若交换后可以相同即满足匹配。

不难想到使用字符串哈希，将 $26$ 个字母分别哈希，然后排序后进行匹配。

对于 $\left [ l,r \right ]$ 的哈希值，可以通过 $hs_r-hs_{l-1}\times p^{r-l+1}$ 对所选取的模数取模，其中 $p$ 为选取的哈希值。

建议使用双哈希。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int mod=1e9+7;
const int h1=1e5+7;
const int h2=1e7+7;
char s[N];
int n,m,p1[N],p2[N];
pair<int,int>hs[30][N];
vector<pair<int,int> >v1,v2;
int f1(int q,int l,int r){
	return (hs[q][r].first-hs[q][l-1].first*p1[r-l+1]%mod+mod)%mod;
}
int f2(int q,int l,int r){
	return (hs[q][r].second-hs[q][l-1].second*p2[r-l+1]%mod+mod)%mod;
}
signed main(){
	scanf("%lld%lld%s",&n,&m,s+1);
	p1[0]=p2[0]=1;
	for(int i=1;i<=n;i++)
		p1[i]=p1[i-1]*h1%mod,
		p2[i]=p2[i-1]*h2%mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=26;j++)
			hs[j][i].first=(hs[j][i-1].first*h1+(s[i]-'a'+1==j))%mod,
			hs[j][i].second=(hs[j][i-1].second*h2+(s[i]-'a'+1==j))%mod;
	while(m--){
		v1.clear(),v2.clear();
		int x,y,len,res11=0,res21=0,res12=0,res22=0;
		scanf("%lld%lld%lld",&x,&y,&len);
		for(int i=1;i<=26;i++)
			v1.push_back(make_pair(f1(i,x,x+len-1),f2(i,x,x+len-1))),
			v2.push_back(make_pair(f1(i,y,y+len-1),f2(i,y,y+len-1)));
		sort(v1.begin(),v1.end()),sort(v2.begin(),v2.end());
		if(v1==v2)printf("YES\n");
		else printf("NO\n");
	}
	return 0;
} 
```

谢谢！

---

## 作者：Rosent (赞：0)

[Link](https://www.luogu.com.cn/problem/CF985F)

显然一眼字符串哈希。

我们会发现，一个询问是符合条件的，与其中的每个字符是什么无关，而与每个字符的出现位置有关。

所以我们可以记录每个不同字符在串中的出现位置，第 $i$ 位字符 $j$ 出现用 $a_{i,j}=1$ 表示，否则用 $a_{i,j}=0$ 表示，可以将每个字符的出现位置串进行哈希操作，排序后判断询问的串所有字符出现位置的哈希值是否相等即可。

特别注意的是：codeforces 题目不要使用自然溢出或单哈希，请使用双哈希。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
#define mod 998244353
#define maxn 400050
using namespace std;
char s[maxn];
int has[maxn][30];
int bas[maxn];
priority_queue <int>q1,q2;
bool check()
{
	for(int i=1;i<=26;i++)
		if(q1.top()!=q2.top())
			return false;
	return true;
}
int h(int a,int len,int l)
{
	return (has[a+len-1][l]-(has[a-1][l]*bas[len])%mod+mod)%mod;
}
signed main()
{
	int n,m;
	cin>>n>>m;
	cin>>s+1;
	int base=13331;
	bas[0]=1;
	for(int i=1;i<=n;i++)
		bas[i]=(bas[i-1]*base)%mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=26;j++)
			has[i][j]=((s[i]-'a'+1==j?1:0)+(has[i-1][j]*base)%mod)%mod;
	for(int i=1;i<=m;i++)
	{
		int a,b,len;
		cin>>a>>b>>len;
		for(int j=1;j<=26;j++)
		{
			q1.push(h(a,len,j));
			q2.push(h(b,len,j));
		}
		if(check()) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
		while(!q1.empty())
			q1.pop();
		while(!q2.empty())
			q2.pop();
	}
	return 0;
}
```

---

