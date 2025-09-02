# Dasha and Nightmares

## 题目描述

Dasha, an excellent student, is studying at the best mathematical lyceum in the country. Recently, a mysterious stranger brought $ n $ words consisting of small latin letters $ s_1, s_2, \ldots, s_n $ to the lyceum. Since that day, Dasha has been tormented by nightmares.

Consider some pair of integers $ \langle i, j \rangle $ ( $ 1 \le i \le j \le n $ ). A nightmare is a string for which it is true:

- It is obtained by concatenation $ s_{i}s_{j} $ ;
- Its length is odd;
- The number of different letters in it is exactly $ 25 $ ;
- The number of occurrences of each letter that is in the word is odd.

For example, if $ s_i= $ "abcdefg" and $ s_j= $ "ijklmnopqrstuvwxyz", the pair $ \langle i, j \rangle $ creates a nightmare.

Dasha will stop having nightmares if she counts their number. There are too many nightmares, so Dasha needs your help. Count the number of different nightmares.

Nightmares are called different if the corresponding pairs $ \langle i, j \rangle $ are different. The pairs $ \langle i_1, j_1 \rangle $ and $ \langle i_2, j_2 \rangle $ are called different if $ i_1 \neq i_2 $ or $ j_1 \neq j_2 $ .

## 说明/提示

In the first test, nightmares are created by pairs $ \langle 1, 3 \rangle $ , $ \langle 2, 5 \rangle $ , $ \langle 3, 4 \rangle $ , $ \langle 6, 7 \rangle $ , $ \langle 9, 10 \rangle $ .

## 样例 #1

### 输入

```
10
ftl
abcdefghijklmnopqrstuvwxy
abcdeffghijkllmnopqrsttuvwxy
ffftl
aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyy
thedevid
bcdefghhiiiijklmnopqrsuwxyz
gorillasilverback
abcdefg
ijklmnopqrstuvwxyz```

### 输出

```
5```

# 题解

## 作者：灵茶山艾府 (赞：8)

### 提示 1

设拼接后的字符串为 $S$。如果 $S$ 能满足后两个要求，那么 $S$ 的长度一定是奇数。所以只需关注后面两个要求。

### 提示 2

题目要求 $S$ 恰好有 $25$ 种不同字母。我们可以枚举不包含的那个字母，记作 $k$。

### 提示 3

下面的讨论，假设字符串均不包含 $k$。

题目要求每种字母的出现次数均为奇数，这可以用二进制表示，二进制从低到高的第 $i$ 位是 $1$，就表示第 $i$ 个字母出现了奇数次。

拼接成 $S$ 的这两个字符串的二进制，分别记作 $m_i$ 和 $m_j$。

问题相当于求满足

$$
m_i\operatorname{xor} m_j = 2^{26}-1-2^k
$$

的 $(m_i,m_j)$ 数对个数。

套路和 [1. 两数之和](https://leetcode.cn/problems/two-sum/) 是一样的，用哈希表或者数组解决。

```go
package main
import("bufio";."fmt";"os")

func main() {
	in := bufio.NewReader(os.Stdin)
	var n, ans int
	var s string
	Fscan(in, &n)
	a := make([]struct{ m, all uint32 }, n)
	for i := range a {
		Fscan(in, &s)
		for _, c := range s {
			b := uint32(1) << (c - 'a')
			a[i].m ^= b
			a[i].all |= b
		}
	}
	for k := 0; k < 26; k++ {
		cnt := map[uint32]int{}
		for _, p := range a {
			if p.all>>k&1 == 0 { // 只统计不包含 k 的字符串
				ans += cnt[1<<26-1^1<<k^p.m]
				cnt[p.m]++
			}
		}
	}
	Print(ans)
}
```

时间复杂度：$\mathcal{O}(L+|\Sigma|n)$。其中 $L$ 为字符串长度之和，$|\Sigma|$ 为字符集合的大小，本题中字符均为小写字母，所以 $|\Sigma|=26$。

欢迎关注 [B站@灵茶山艾府](https://space.bilibili.com/206214)


---

## 作者：苏联小渣 (赞：5)

题目条件有点多，这里先梳理一下：

询问有多少对 $(i,j)$ 满足：

- $i<j$（事实上，$i=j$ 一定不合法）

- 字符串 $s_is_j$ 中出现了 $25$ 种字母，每种字母出现了奇数次。容易发现这个已经涵盖了长度为奇数的条件。

这个题看似很难找到切入点，但是我们发现这题的特殊之处，出现 $25$ 种字母，也就是说，有且只有一种没有出现过。我们不妨枚举哪个字母没有出现过，那么就相当于确定了所选字母的种类。

假设当前枚举字母 $C$ 没有出现过。这样，所有包含 $C$ 的字符串都不能被选。发现要求与字母出现顺序无关，那不妨记录 $f_{i,c}$ 表示第 $i$ 个字符串中字母 $c$ 出现的次数。对于一个合法的字符串 $s_j$，合法的 $i$ 满足的条件可以转化如下：

- $i<j$

- $f_{i,C}=0$

- $\forall C'\ne C,(f_{i,C'}+f_{j,C'}) \bmod 2=1$。

前两个条件容易满足。对于第三个条件，发现只与奇偶性有关，但这个东西看起来又很难维护，这个时候不难想到二进制，把对于一个 $j$ 的所有 $C' \ne C,f_{j,C'} \bmod 2$ 压成一个二进制串，它转成十进制的范围在 $[1,2^{25}]$ 之间，可以用数组统计。这样，$f_{i,C'}$ 对应的二进制串就可以唯一确定。那么开个数组统计即可。时间复杂度 $O(26^2 \times n)$，勉强可以通过。

注意不要用 map，会 FST。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int n, a[200010], vis[200010], mp[40000010], tot[200010][27];
long long ans;
string s[200010];
vector <int> del;
int main(){
	scanf ("%d", &n);
	for (int i=1; i<=n; i++){
		cin >> s[i];
		a[i] = s[i].size();
		for (int j=0; j<a[i]; j++){
			tot[i][s[i][j]-'a'+1] ++;
		}
	}
	for (char C='a'; C<='z'; C++){
		memset(vis, 0, sizeof(vis));
		for (int i=1; i<=n; i++){
			if (tot[i][C-'a'+1]) vis[i] = 1;
		}
		del.clear();
		for (int i=1; i<=n; i++){
			if (vis[i]) continue;
			int sta = 0, oth = 0;
			for (int j=1; j<=26; j++){
				if (j == C-'a'+1) continue;
				sta = sta * 2 + tot[i][j] % 2;
				if (tot[i][j] % 2 == 0) oth = oth * 2 + 1;
				else oth = oth * 2;
			}
			ans += mp[oth];
			mp[sta] ++;
			del.push_back(sta);
		}
		for (int i=0; i<del.size(); i++){
			mp[del[i]] --;
		}
	}
	printf ("%lld\n", ans);
	return 0;
}
```

---

## 作者：Diaоsi (赞：2)

[Dasha and Nightmares](https://www.luogu.com.cn/problem/CF1800F)

注意到恰好出现 $25$ 次的这个条件，不妨反过来枚举哪个字母没出现。

枚举没有出现的字符 $c$，将不含字母 $c$ 的字符串 $s$ 划进一个集合 $P$，只需要对 $P$ 单独求解，接下来的讨论均限制在 $P$ 中。

用二进制串记录状态 $S_i$，表示字符串 $s_i$ 中每种字符出现次数的奇偶性，于是我们只需要求解有多少个 $j$ 满足 $S_i\oplus S_j=T$。$T$ 表示除 $c$ 外所有字符均出现了奇数次。

显然某个字符出现了奇数次这个条件要比存在某个字符更强，且 $25$ 个字符出现奇数次也满足了拼起来的字符串长度为奇数的条件，这样一来 $\left\langle i,j \right\rangle$ 就一定是合法的。

开一个桶记录一下状态为 $S_i$ 的字符串有多少个，再将要满足的式子移个项：

$$S_i\oplus S_j=T\ \Rightarrow S_j=S_i\oplus T$$

于是对于每一个 $S_i$，我们只需要查询 $S_i\oplus T$ 对应的桶，然后计入贡献即可。

但是 $S_i$ 的状态数会达到 $2^{26}$ 种，直接开桶有点过于浪费空间了。注意到 $S_i$ 一定有固定的一位为 $0$，我们不妨把这一个 $0$ 直接压掉，这样就只需要开 $2^{25}$ 大小的桶，空间直接少一半。

时间复杂度 $\mathcal{O}\left(\big|\sum S\big|+|\Sigma|n\right)$，此处的 $\big|\sum S\big|$ 指的是字符串的长度的总和，$|\Sigma|$ 为字符集的大小。轻松地跑到了最优解（296ms）。

```Code:```
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N=200010,M=5000010,INF=0x3f3f3f3f;
inline int max(int x,int y){return x>y?x:y;}
inline int min(int x,int y){return x<y?x:y;}
inline void swap(int &x,int &y){x^=y^=x^=y;}
int n,m,t[N],s[N],mp[M<<3];
ll ans;
char c[M];
vector<int> v;
int hsh(int S,int i){
	return ((S>>(i+1))<<i)+(S&((1<<i)-1));
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		m=strlen(c+1);
		for(int j=1;j<=m;j++)
			s[i]^=1<<(c[j]-'a'),t[i]|=1<<(c[j]-'a');
	}
	for(int i=0;i<26;i++){
		v.clear();
		for(int j=1;j<=n;j++){
			if((t[j]>>i)&1)continue;
			v.push_back(s[j]);
			mp[hsh(s[j],i)]++;
		}
		for(int z:v)ans+=mp[hsh(z^(((1<<26)-1)^(1<<i)),i)];
		for(int z:v)mp[hsh(z,i)]=0;
	}
	printf("%lld\n",ans>>1);	
	return 0;
}
```


---

## 作者：GGapa (赞：0)

如果条件 $2$、$3$ 满足则条件 $1$ 是不用管的，因为每次都缺少了一个字符，考虑依次枚举缺的是哪一个字符。

由于每个字母出现的个数都是奇数，相同字符在两个字符串之间的出现次数的奇偶性肯定不相同。

考虑将其压入二进制中保存，如果这个字符的出现次数为 $1$，将其对应的二进制标记为 $1$，否则为 $0$，奇偶性不相同对应了二进制的取反操作。

注意：取反的时候要注意不能将缺少的字符一同取反。

```cpp
 #include <bits/stdc++.h>
 #define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
 #define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
 using namespace std;
 using LL = long long;
 using VI = vector<int>;
 
unordered_map<int, int> mp;

 signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<string> A(n + 1);
    vector<VI> cnt(n + 1, VI(27));
    vector<int> F(n + 1);
    int tp = (1 << 26) - 1;
    rep(i, 1, n) {
        cin >> A[i];
        for(auto c : A[i]) cnt[i][c - 'a']++;
        int t = 0;
        rep(j, 0, 25) t |= ((cnt[i][j] & 1) << j);
        F[i] = t;
    }
    LL ans = 0;
    rep(del, 0, 25) {
        mp.clear();
        rep(i, 1, n) if(!cnt[i][del]) {
            ans += mp[F[i] | (1 << del)];
            mp[(F[i] ^ tp) | (1 << del)] += 1;
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：CQ_Bob (赞：0)

## 分析

考虑枚举。

注意到第二个条件是必须要有 $25$ 个字符在里面出现过，故考虑枚举唯一没出现过的字符 $k$，然后再枚举 $s_i$。

令 $cnt_{i,j}$ 表示 $s_i$ 中字符 $c$ 出现的奇偶性。如果有字符 $c \ne k \land cnt_{i,c}=0$，则在 $s_j$ 中必有 $cnt_{j,c}=1$；反之同理。

枚举字符 $c$，可以得到要与 $s_i$ 匹配的字符串 $s_j$ 中所有字符出现次数的奇偶情况。把这玩意看成二进制拿个桶记录答案就行了。复杂度 $O(a^2n)$，$a=26$。

注：桶里的东西不能在 $k$ 之外预处理，因为可能有 $cnt_{i,k}=0$ 但 $k$ 在 $s_i$ 中出现过的情况。这样会使你答案大很多。对于每次桶的清空，如果直接枚举所有状态复杂度会高不止一点。发现我们放桶里面的二进制值最多有 $n$ 个，所以随便拿个东西存一下往那些桶放了值即可。


## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=2e5+10,M=(1<<26);
int n;
bool cnt[N][26],cnt2[N][26];
int Cnt[N],num[M];
vector<int> d;
long long ans;

il void solve(){
	n=read();
	for(re int i=1;i<=n;++i){
		string s;cin>>s;
		for(re int j=0;j<s.size();++j) cnt[i][s[j]-'a']^=1,cnt2[i][s[j]-'a']=1;
		for(re int j=0;j<26;++j) Cnt[i]+=(cnt[i][j]*(1<<j));
	}
	for(re int k=0;k<26;++k){
		for(re int i=1;i<=n;++i)
		if(!cnt2[i][k]){
			int now=0;
			for(re int c=0;c<26;++c) if(!cnt[i][c]&&c!=k) now+=(1<<c);
			ans+=num[now],++num[Cnt[i]],d.push_back(Cnt[i]);
		}
		for(re int i=0;i<d.size();++i) --num[d[i]];
		d.clear();
	}
	printf("%lld\n",ans);
	return ;
}

signed main(){
//	int t=read();while(t--)
	solve();
	return 0;
}
```


---

## 作者：AlicX (赞：0)

## Solution 

考虑转化题目条件，因为要求字符串恰好有 $25$ 个字符，所以考虑枚举没出现过的字符，令其为 $k$。再令 $f_{i,p}$ 表示第 $i$ 个字符串 $p$ 字符出现次数的奇偶，于是题目条件即为：

- $f_{i,k}=f_{j,k}=0$。
- $f_{i,p}+f_{j,p} \bmod 2=1$。

于是考虑用一个 $2^{26}$ 的桶或 `bitset` 表示出每个字符串，即如果 $f_{i,p} \bmod 2=1$，$num \gets num+2^p$，把 $num$ 放入桶，统计答案的时候将 $f_{i,p} \bmod 2=0$ 的 $j$ 加入 $num$ 即可，时间复杂度为 $O(nV^2)$，$V$ 为 $26$。

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define x first 
#define y second 
#define il inline 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=2e5+10,M=26; 
int n; 
int f[N][M]; 
string s[N]; 
int mp[1<<M]; 
bool st[N][M]; 
il void work(){ 
    cin>>n; ll ans=0; 
    for(int i=1;i<=n;i++){ 
        cin>>s[i]; 
        for(int j=0;j<M;j++) f[i][j]=0; 
        for(int j=0;j<s[i].size();j++) f[i][s[i][j]-'a']++,st[i][s[i][j]-'a']=true; 
    } for(int k=0;k<M;k++){ 
        for(int i=1;i<=n;i++){ 
            if(st[i][k]) continue; int num=0; 
            for(int j=0;j<M;j++) if(f[i][j]&1) num+=(1<<j); 
            mp[num]++;  
        } for(int i=1;i<=n;i++){ 
            if(st[i][k]) continue; int num=0; 
            for(int j=0;j<M;j++) if(j!=k&&(!(f[i][j]&1))) num+=(1<<j); 
            ans+=1ll*mp[num]; 
        } for(int i=1;i<=n;i++){ 
            if(st[i][k]) continue; int num=0; 
            for(int j=0;j<M;j++) if(f[i][j]&1) num+=(1<<j); 
            mp[num]--; 
        } 
    } printf("%lld\n",ans/2); 
} 
signed main(){ 
    int T=1; 
    while(T--) work(); return 0; 
} 
```


---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1800F)

一道字符串题。

既然两个字符串拼接后有一种字符不能出现，那么可以枚举这个字符，我们就只需要关注没有出现过这种字符的字符串了。

剩下的字符串仅会出现 $25$ 种字符，而我们并不关心字符串里字符的顺序，仅关心字符出现的个数的奇偶性，因此我们可以把字符串看做是一个长度为 $25$ 的二进制数 $x_i$，如果某一位为 $1$ 表明这种字符在字符串中的出现次数为奇数，如果某一位为 $0$ 则表明为偶数。

那么接下来题目就转变为有多少对 $i,j$ 满足 $x_i\oplus x_j =2^{25}-1$，可以使用 `std :: map` 统计。

### Code
```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef __float128 f128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i ++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i --)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
ll n, ans;
ll cnt[200005][26];
string s[200005];
vector <ll> x;
map <ll, ll> mp;
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n;
	REP(i, 1, n) {
		cin >> s[i];
		REP(j, 0, s[i].size() - 1) cnt[i][s[i][j] - 'a'] ++;
	}
	REP(c, 0, 25) {
		mp.clear(), x.clear();
		REP(i, 1, n) {
			if (cnt[i][c]) continue;
			x.push_back(0);
			REP(j, 0, 25) {
				if (j == c) continue;
				x[x.size() - 1] = (x[x.size() - 1] << 1) | (cnt[i][j] & 1);
			}
		}
		for (auto v : x) {
			mp[v] ++;
			ans += mp[v ^ (1 << 25) - 1];
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Mikefeng (赞：0)

## 题意

给定 $n$ 和 $n$ 个字符串 $s_i$。

问有多少对不同的 $\langle i,j\rangle(1\leq i\leq j\leq n)$，使得 $s_i$ 和 $s_j$ 拼接后的字符串满足下列条件：
- 长度为奇数
- 恰好出现 $25$ 个字母
- 每个字母出现次数为奇数

## 做法

给出一个期望 $O(26n)$ 的做法。

长度为奇数好处理，开两个哈希表，按长度奇偶性分别存储。

恰好出现 $25$ 个字母可以枚举，对于每个哈希表再分 $26$ 组，分别表示缺少哪个字母。

最后只剩了每个字母出现次数为奇数，我们可以将一个字符串压成 $26$ 位的二进制数，每次查询压缩后为 $a_i\oplus (2^{26}-1)$ 的数的个数。

## 代码

手写探查哈希浅看一下就好。（经常比 unordered_map 快

```cpp
const int N=2e5+5;
const int p=1145141;
int n;
ll ans;
int a[N];
string s[N];
int num[N][26];
struct hash{
	int a[p],k[p];
	int find(int key){
		key^=key>>16;
		int i=key%p,j=1;
		while(k[i]&&k[i]!=key) i=(i+j*j)%p;
		return a[i];
	}
	void add(int key){
		key^=key>>16;
		int i=key%p,j=1;
		while(k[i]&&k[i]!=key) i=(i+j*j)%p;
		if(!k[i]) k[i]=key;
		a[i]++;
	}
}val[2][26];
int main(){
	n=read();
	F(i,1,n){
		cin>>s[i];
		F(j,0,(int)s[i].size()-1) num[i][s[i][j]-'a']++;
		F(j,0,25) a[i]+=(1<<j)*(1-(num[i][j]&1));
	}
	F(i,1,n){
		int id=s[i].size()&1,sum=(1<<26)-1-a[i],lst=ans;
		F(j,0,25) if(!num[i][j]){
			ans+=val[id^1][j].find(sum+(1<<j));
			val[id][j].add(a[i]);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

