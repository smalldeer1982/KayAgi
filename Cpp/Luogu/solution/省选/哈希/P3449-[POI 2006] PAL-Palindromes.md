# [POI 2006] PAL-Palindromes

## 题目描述

Johnny 喜欢玩文字游戏。

他写下了 $n$ 个回文串，随后将这些串两两组合，合并成一个新串。容易看出，一共会有 $n^2$ 个新串。

两个串组合时顺序是任意的，即 `a` 和 `b` 可以组合成 `ab` 和 `ba`，另外自己和自己组合也是允许的。

现在他想知道这些新串中有多少个回文串，你能帮帮他吗？

## 样例 #1

### 输入

```
6
2 aa
3 aba
3 aaa
6 abaaba
5 aaaaa
4 abba```

### 输出

```
14```

# 题解

## 作者：Limie (赞：24)

### 1. 前言
感觉我的做法很简单啊，怎么题解区没有人写？

### 2. 前置知识点

哈希判断回文，快速幂求乘法逆。

### 3. 做法

设串 $s$ 的长度为 $|s|$，哈希值为 $a$，串 $t$ 的长度为 $|t|$，哈希值为 $b$。

不妨设哈希 base 为 $p$。

**很难不发现** $s$ 与 $t$ 拼接起来为回文的条件为 $a \times p^{|t|}+b=b \times p^{|s|}+a$（因为 $s$ 和 $t$ 都是回文串），所以有 
$$
\frac{a}{p^{|s|}-1}=\frac{b}{p^{|t|}-1}
$$

那么只要哈希求出每个串的哈希值，再对每个串算出上面的值然后扔到 map 里统计数量即可。

#### Code

```cpp
#include<bits/stdc++.h>
namespace Limie{
	#define x first
	#define y second
	using namespace std;
	typedef long long LL;
	typedef unsigned long long ULL;
	typedef pair<int,int> PII;
}using namespace Limie;
const int mod=1e9+7,P=13331;
int n;
unordered_map<int,int> mp;
int qmi(int a,int b=mod-2)
{
	int ans=1;
	while(b){
		if(b&1)ans=(LL)ans*a%mod;
		b>>=1,a=(LL)a*a%mod;
	}return ans;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int i;LL ans=0;
	cin>>n;
	for(i=1;i<=n;i++){
		int c=0;char ch;
		cin>>c;
		LL s=0,t=1;
		while(c--){
			cin>>ch;
			t=t*P%mod;
			s=(s*P+ch)%mod;
		}
		s=s*qmi(t-1)%mod;
		ans+=mp[s]++;
	}
	cout<<ans*2+n;
}
```

---

## 作者：Cry_For_theMoon (赞：11)

[传送门](https://www.luogu.com.cn/problem/P3449)（POI的题怎么都毒瘤的一批）

既然给了原本都是回文串这个条件说明一定很重要。

首先我们知道，对于回文串 $S$，其开头 $a$ 个字符和其结尾 $a$ 个字符应该是刚好相反的。比方说 $S=abcba$，那么开头 $3$ 个字符是 $abc$，结尾$3$ 个字符是 $cba$，确实刚好相反。这个性质显然成立。

然后回文串 $A,B$ 拼接有两种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/svr973wc.png)
这种情况下如果 $AB$ 依旧是回文串，由刚才的性质可得，$A$ 与 $B$ 的后 $|A|$ 个字符完全相反；又因为刚才的性质我们知道 $B$ 的后 $|A|$ 个字符与其前 $|A|$ 个字符完全相反。既然 $A$ 和 $B$ 的 $|A|$ 前缀都与一个相同的串完全相反，那么它们两也就相同。

那么类比第二种情况：
![](https://cdn.luogu.com.cn/upload/image_hosting/9ds0xquf.png)
不难得出相同的结论。

所以才有了一切的一切：若两个回文串 $A,B(|A|<=|B|)$ 拼接的字符串 $AB(BA)$ 依旧是回文串，则 $A$ 是 $B$ 的前缀。

也就是说我们对于这种二元关系的题目依旧 $O(n)$ 枚举钦定 $(A,B)$ 中的 $B$。然后找到所有字符串中 $B$ 的前缀串，对这些串判断组合后是否回文。关于查询前缀自然而然想到字典树。只有单词节点在根到 $B$ 的路径上的字符串才可能与 $B$ 组合成回文串。这里遍历的复杂度显然是 $O(\sum{|S|}<=2*10^6)$ 的。

那么在知道了 $A,B$ 的情况下如何对其进行判断是否回文。这里不大可能是manacher，因为即使确定了 $B$，可能的前缀也不止一个，marnarcher要跑的次数会很多。与回文有关的另一个经典算法是哈希，因为回文本质上就是判断左边和右边是不是完全相反，这只需要对字符串进行正反两边hash就可以。具体在本题，只需对 $B$ 进行一次哈希（还记得他们回文吗。不过我写题的时候没注意到这里正反都哈希了）。由于 $A$ 就是 $B$ 的前缀所以不需要额外对其hash。然后暴力判断即可。这样期望复杂度大概就是 $O(\sum{|S|})$ 的（常数不低）。

但这题细节非常烦，因为怕开 $2*10^6$ 个 string 会TLE/MLE 所以我用了一个字符串储存所有字符，不过这个就和算法没关系了qwq

```cpp
//POI,2006
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
typedef unsigned long long ull;
using namespace std;
const int MAXN=2e6+10,BASE=131;
int n,sz[MAXN],len,ans;
char tmp[MAXN],s[MAXN];
int ch[MAXN][26],vis[MAXN],tot;
ull f1[MAXN],f2[MAXN],power[MAXN];
inline void add(const char* s,int len){
	int u=0;
	for(int i=0;i<len;i++){
		int nxt=s[i]-'a';
		if(!ch[u][nxt])ch[u][nxt]=++tot;
		u=ch[u][nxt];
	}
	vis[u]=1;
}
inline void visit(const char* s,int len){
	ull sum=0;
	for(int i=0;i<len;i++){
		sum=sum*BASE+(s[i]-'a');
		f1[i]=sum;
	}
	sum=0;
	for(int i=len-1;i>=0;i--){
		sum=sum*BASE+(s[i]-'a');
		f2[i]=sum; 
	}
	int u=0;
	for(int i=0;i<len-1;i++){
		int nxt=s[i]-'a';
		u=ch[u][nxt];
		if(vis[u]){
			//计算答案
			int sz=i+1+len;
			//s[0..i]+s[0..len-1] 
			int pre=sz/2-i-1,l=sz/2;
			if(f1[i]*power[pre]+(pre?f1[pre-1]:0) == f2[len-l]){
				ans++;
			}
			//s[0..len-1]+s[0..i]
			if(f1[l-1] == f2[len-i-1]*power[pre]+(pre?f2[len-pre]:0)){
				ans++;
			}
		}
	}
}
int main(){
	scanf("%d",&n);
	ans=n;
	for(int i=1;i<=n;i++){
		scanf("%d%s",&sz[i],tmp);
		for(int j=len;j<len+sz[i];j++){
			s[j]=tmp[j-len];
		}
		len+=sz[i];
	}
	power[0]=1;
	for(int i=1;i<=len;i++)power[i]=power[i-1]*BASE;
	//insert
	ull sum=0;
	for(int i=1;i<=n;i++){
		add(s+sum,sz[i]);
		sum+=sz[i];
	}
	//visit
	sum=0;
	for(int i=1;i<=n;i++){
		visit(s+sum,sz[i]);
		sum+=sz[i];
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：bymhq (赞：10)

看到这道题后想了一个~~证不出来~~的结论，交了一下竟然过了。
然后查题解找证明没有找到。。。如果有大佬会证明方法，请不吝赐教%%%。
结论是：

**当且只当，a、b两个回文串的最小循环节一样时，a+b是回文串。**

（这里最小循环节长度必须为回文串的约数）

比如ababa和aba的最小循环节分别为ababa、aba，不一样所以ababaaba不是回文串

abaaba和abaabaaba的最小循环节分别为aba，一样所以连起来是回文串；

因为如果s是回文串，所以s的最小循环节是回文串。

之后就不太会证了qwq

当然，有可能结论根本就是错的，可蒟蒻找不到hack的数据

下面是code，大佬帮忙hack
```cpp
#include<bits/stdc++.h>
#define ll long long
#define u unsigned int
using namespace std;
const u bas=233;
int n,m;
u hsh[2000100],now,k[2000100];
char a[2000100];
u hh(int l,int r){return hsh[r]-hsh[l-1]*k[r-l+1];}
bool pd(int x)
{//cout<<now<<" "<<x<<endl;
	for(register int i=1;i<=m;i+=x){//cout<<hh(i,i+x-1)<<" ";
	if(hh(i,i+x-1)!=now)return 0;}return 1;
}
main()
{
	scanf("%d",&n);k[0]=1;
	multiset<u>s;for(int i=1;i<=2e6;i++)k[i]=k[i-1]*bas;
	for(int ii=1;ii<=n;ii++)
	{
		scanf("%d",&m);
		scanf("%s",a+1);
		for(int i=1;i<=m;i++)
		hsh[i]=hsh[i-1]*bas+a[i];
		for(int i=1;i<=m;i++)
		{
			if(m%i)continue;
			now=hh(1,i);
			if(pd(i))
			{//cout<<endl;
				s.insert(now);break;
			}//cout<<endl;
		}
	}
	ll ans=0;
	while(!s.empty())
	{
		int o=*s.lower_bound(0),oo=s.count(o);//cout<<oo<<endl;
		ans+=(ll)oo*oo;s.erase(o);
	}cout<<ans;
}
```


---

## 作者：Alex_Wei (赞：9)

Upd on 2022.9.3：换成更自然的推导方式。

> *[P3449 [POI2006]PAL-Palindromes](https://www.luogu.com.cn/problem/P3449)

好题。

若 $s_i + s_j$ 是回文串，因为 $s_i, s_j$ 均回文，所以当 $|s_j| < |s_i|$ 时，$s_j$ 是 $s_i$ 的前缀且 $s_i[|s_j| + 1, |s_i|]$ 回文，当 $|s_j| = |s_i|$ 时，$s_i = s_j$，当 $|s_j| > |s_i|$ 时，$s_i$ 是 $s_j$ 的前缀且 $s_j[|s_i | + 1, |s_j|]$ 回文。因此，对于任意长度不等的字符串无序对 $s_i$ 和 $s_j$，若它们之间存在前缀关系，则对答案产生 $2$ 的贡献。最后将答案加上 $n$ 即可。

具体实现方法为枚举每个 $s_i$ 的每一位 $p(1\leq p < |s_i|)$，求出 $s_i[1, p]$ 在 $s$ 中的出现次数，以及 $s_i[p + 1, |s_i|]$ 是否是回文串。前者用字典树维护，后者用 Manacher 维护，可以做到时间复杂度线性，空间复杂度线性字符集。

实际上本题还有更巧妙的做法。

我们观察 $x, y(|x| < |y|)$ 和 $x + y$，它们都是回文串。首先将 $y$ 分成 $p = y[1, |y| - |x|]$ 和 $q = y[|y| - |x| + 1, |y|]$，可知 $q = x$，则 $x + y = xpx$。因为 $y$ 为回文串，所以 $y$ 既然以 $p$ 作为前缀，那么以 $p$ 作为后缀，因此 $y = px = px'p$，$x + y = x'p / px'p$。又因为 $x + y$ 关于最中间的 $p$ 回文，所以 $x'p$ 是回文串，可知 $x'$ 有长为 $p$ 的前缀。因此 $x + y = px''p / ppx''p$，再根据 $y$ 为回文串推出 $x + y = px'''pp / ppx'''pp$，以此类推。简单地说，不断运用 $y$ 和 $x + y$ 为回文串的性质，可以推得 $x$ 和 $y$ 有相同的长度为 $|y| - |x|$ 的 **回文周期**。

进一步地，我们发现若 **回文串** $a$ 有长为 $|b|$ 的回文周期且 $|b| \nmid |a|$，则 $a$ 有长为 $|b| - |a|$ 的回文周期。推导过程是类似的：设 $a = bbb \cdots bc$，$c$ 为 $b$ 的前缀，$c ^ R$ 表示 $c$ 翻转后得到的串。

因为 $a, b$ 均为回文串，所以 $a = c ^ Rb \cdots bbb$。

- 因为 $c$ 和 $c ^ R$ 均为 $s$ 的前缀，所以 $c$ 回文。

- 因为 $bbb\cdots bc = c ^ Rb\cdots bbb$，所以 $bbb\cdots b$ 为 $a$ 的 border，因此 $|c|$ 为 $a$ 的周期。

综合上述两点，可知 $|c|$ 为 $a$ 的回文周期。

不断应用上述结论，可知

> 若长度为 $n$ 的 **回文串** $s$ 存在 **回文** 周期 $p$，则 $s$ 存在长为 $\gcd(n, p)$ 的 **回文整周期**。

结合辗转相减法和上述结论易证。

又因为 $x$ 和 $y$ 均有相同的长度为 $|y| - |x|$ 的回文周期，且 $\gcd(|x|, |y| - |x|) = \gcd(|y|, |y| - |x|)$，得到 $x, y$ 具有 **完全相同的回文整周期**，这是必要条件。反过来易证其充分性。

综上，KMP 求出每个字符串的 $nxt$ 数组，反证法可证若 $|s| - nxt_{|s|}$ 整除 $|s|$ 则 $s[1, |s|-nxt_{|s|}]$ 是最短回文整周期字符串，否则最短回文整周期字符串就是 $s$ 本身。

每个本质不同的字符串对答案的贡献为 $c ^ 2$，其中 $c$ 表示它作为 $c$ 个串的最短回文整周期字符串。为此，排序并检查相邻两个最短回文周期字符串是否相等。时间复杂度线性对数。[代码](https://vjudge.net/solution/38075469/DeLoR6hXjh5RTTUMsowb)。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define TIME 1e3 * clock() / CLOCKS_PER_SEC
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
inline int read() {
  int x = 0;
  char s = getchar();
  while(!isdigit(s)) s = getchar();
  while(isdigit(s)) x = x * 10 + s - '0', s = getchar();
  return x;
}
inline void print(int x) {
  if(x < 0) return putchar('-'), print(-x);
  if(x >= 10) print(x / 10);
  putchar(x % 10 + '0');
}
bool Mbe;
constexpr int N = 2e6 + 5;
int n, nxt[N];
char str[N];
string s[N];
bool Med;
int main() {
  fprintf(stderr, "%.3lf MB\n", (&Mbe - &Med) / 1048576.0);
  #ifdef ALEX_WEI
    FILE* IN = freopen("1.in", "r", stdin);
    FILE* OUT = freopen("1.out", "w", stdout);
  #endif
  ios::sync_with_stdio(0);
  cin >> n;
  for(int i = 1; i <= n; i++) {
    int m;
    cin >> m >> str + 1;
    for(int j = 2, p = 0; j <= m; j++) {
      while(p && str[p + 1] != str[j]) p = nxt[p];
      nxt[j] = p += str[p + 1] == str[j];
    }
    if(m % (m - nxt[m]) == 0)
      for(int j = 1; j <= m - nxt[m]; j++)
        s[i] += str[j];
    else
      for(int j = 1; j <= m; j++)
        s[i] += str[j];
  }
  sort(s + 1, s + n + 1);
  ll ans = 0;
  for(int i = 1; i <= n; i++) {
    int r = i;
    while(r < n && s[r + 1] == s[i]) r++;
    ans += 1ll * (r - i + 1) * (r - i + 1);
    i = r;
  }
  cout << ans << "\n";
  cerr << TIME << " ms\n";
  return 0;
}
/*
2022/9/3
author: Alex_Wei
start coding at 6:58
finish debugging at 7:05
*/
```

---

## 作者：lzyqwq (赞：6)

[**cnblogs**](https://www.cnblogs.com/MnZnOIerLzy/articles/17702734.html)

> - 给出 $n$ 个回文串 $s_1\sim s_n$，将它们两两组合拼接得到 $n^2$ 个新串。求这些新串中有多少回文串。
>
> - $\sum\limits_{i=1}^n|s_i|\le 2\times 10^6$。

约定：

- 记字符串 $s$ 的反串为 $s^R$，比如 $(\texttt{ab})^R=\texttt{ba}$。

- 记 $pre(s,l)$ 为字符串 $s$ 长度为 $l$ 的前缀，$suf(s,l)$ 为字符串 $s$ 长度为 $l$ 的后缀。

其实 $s_1\sim s_n$ 不是回文串也可以做的，所以不管这个性质。

考虑哈希，定义字符串 $s$ 的哈希函数 $H(s)=\sum\limits_{i=1}^{|s|}(P^{|s|-i}\times \text{ASCII}(s_i))$，其中取 $P=1145141$，函数的返回值类型为 `unsigned long long`，在计算过程中自然溢出，默认不会冲突。

用哈希求解回文串题目先预处理出正、反串的前缀哈希值。开两个桶 $mp_{0/1,x}$ 表示正/反串哈希值为 $x$ 的 $s$ 数量。然后我们将新串分为两类：

- 拼接的两个字符串长度相同

    枚举位于前面的那个串 $s_i$，显然贡献为 $\sum\limits_{j=1}^n[s_j=s_i^R]$，即 $mp_{1,s_i}$。
	
- 拼接的两个字符串长度不同

    枚举较长的那个串 $s_i$，用它去和较短的串拼接。又分为两类：
	
    - $s_i$ 在前
	
	  这种情况一定是 $s_i$ 的一个非空真后缀回文，且该非空真后缀之前的非空真前缀与短串对称。枚举回文非空真后缀的位置 $j$，用哈希判断，贡献为 $mp_{1,H(pre(s_i,j-1))}$。
	  
	- $s_i$ 在后
	
	  这种情况一定是 $s_i$ 的一个非空真前缀回文，且该非空真前缀之后的非空真后缀与短串对称。枚举回文非空真前缀的位置 $j$，用哈希判断，贡献为 $mp_{0,H((suf(s_i,j+1))^R)}$。
	
	可以看到两种情况的讨论是类似的。有人可能会问 $mp$ 是对全局维护的，上面用 $mp$ 计算贡献会不会算上比 $s_i$ 长的串。显然是不会的，因为上面使用 $mp$ 时均访问了短串的哈希值的下标以统计个数，而长串的哈希值时不会和短串的哈希值冲突的。

使用 `__gnu_pbds::gp_hash_table` 维护桶，时间、空间复杂度均为 $\mathcal{O}\left(\sum\limits_{i=1}^n |s_i|\right)$。

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define ull unsigned long long
using namespace std; const int N = 2e6 + 5; const ull P = 1145141;
vector<ull> H[N][2]; int a[N], n; string s; ull ans, pw[N];// 0 正; 1 反
__gnu_pbds::gp_hash_table<ull, ull> mp[2];
ull Hash(int id, bool type, int l, int r) {
   if (!type) return H[id][0][r] - H[id][0][l - 1] * pw[r - l + 1];
   return H[id][1][l] - H[id][1][r + 1] * pw[r - l + 1];
}
signed main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0); cin >> n;
    for (int i = pw[0] = 1; i < N; ++i) pw[i] = pw[i - 1] * P;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> s; s = ' ' + s;
        H[i][0].resize(a[i] + 5), H[i][1].resize(a[i] + 5);
        for (int j = 1; j <= a[i]; ++j) H[i][0][j] = H[i][0][j - 1] * P + s[j];
        for (int j = a[i]; j >= 1; --j) H[i][1][j] = H[i][1][j + 1] * P + s[j];
        ++mp[0][H[i][0][a[i]]], ++mp[1][H[i][1][1]];
    }
    for (int i = 1; i <= n; ++i) {
        ans += mp[1][H[i][0][a[i]]];
        for (int j = 1; j < a[i]; ++j)
            if (Hash(i, 0, 1, j) == Hash(i, 1, 1, j)) ans += mp[0][H[i][1][j + 1]];
        for (int j = 2; j <= a[i]; ++j)
            if (Hash(i, 0, j, a[i]) == Hash(i, 1, j, a[i]))
                ans += mp[1][H[i][0][j - 1]];
    }
    return cout << ans, 0;
}
```

---

## 作者：0x3F (赞：6)

~~定义新运算~~ $p \times S$（$p$ 为正整数，$S$ 为字符串）为 $S$ 连写 $p$ 遍。

先说结论：如果 $A, B, A+B$ 均为回文串，则 $A$ 和 $B$ 的循环节相同。

也就是说，存在 $C$，使得 $A = a \times C, B = b \times C$

~~我看过这道题的题解，都用了这个结论，可惜没有人有严谨（？）证明~~

下面是证明：

使用**数学归纳法**证明。

定义命题 $P(a, b)$ 为：

> 对于任意两个分别长为 $a, b$ 的回文串 $A, B$，如果 $A+B$ 为回文串，则必定存在 $C$，使得 $A = p \times C, B= q \times C$

首先 $P(a, a)$ 显然成立。

现在证明当 $P(a, b)$ 时，$P(a, a+b)$ 必然成立。

证明：（$Pal(S)$ 表示 $S$ 是回文串）

$$len(A) = a, len(C) = a + b$$

$$\text{设 C 的前 b 位为 B，后 a 位为 D}$$


$$\therefore Pal(A), Pal(B+D), Pal(A+B+D)$$

$$\because len(A) = len(D), Pal(A+B+D),$$

$$\therefore A=D, Pal(B), Pal(D)$$

$$\because \begin{cases}len(B) = b \\ len(D) = a \\ Pal(B) \\ Pal(D) \\ Pal(B+D) \\ P(b, a)\end{cases}$$

$$B = p \times S, D = q \times S$$

$$\because A = D, \therefore A = q \times S$$

$$\because C = B + D, \therefore C = p \times S + q \times S = (p+q) \times S$$

$$\therefore\begin{cases}A = q \times S \\ C = (p+q) \times S\end{cases}$$

$$\therefore P(a, a+b)$$

所以我们知道：

$$\begin{cases}P(a, a) \\ P(a, b) \Rightarrow P(a, a+b)\end{cases} \Rightarrow P(a, b)$$

$$\Huge{\mathcal{Q.E.D.}}$$

于是我们只需要找出每一个字符串的**最短**循环节即可。

枚举字**符串长度的因子**，求出分出的每段子串的**哈希值**，判断是否相等即可。

注意一点：**两数相减可能为负**，此时应当 $\%mod$，再 $+mod$，再 $\%mod$。

最后排一下序，把循环节相同的分为一组，由于每组内可以随意配对，所以最终答案即为每组元素个数的平方和。

还有，答案要开 **`long long`**！

时间复杂度约为 $\Theta(n \log n)$。~~其实我也算不清楚~~

你们最想看的代码，他来了！

```cpp
#include <bits/stdc++.h>
#define mod 1000000007ll
#define base 233ll
using namespace std;
int n, len;
long long cnt, sum;
int pows[2000010];
int hash[2000010];
string str, ans[2000010];

int main() {
	pows[0] = 1;
	for (int i = 1; i <= 2000000; i++) {
		pows[i] = (long long) pows[i-1] * base % mod;
	}
	cin >> n;
	for (int a = 1; a <= n; a++) {
		cin >> len >> str;
		hash[0] = str[0];
		for (int i = 1; i < len; i++) {
			hash[i] = (hash[i-1] + (long long)pows[i] * str[i]) % mod;
		}
		for (int i = 1; i <= len; i++) {
			if (len % i) continue;
			int t = hash[i-1];
			for (int j = i*2; j <= len; j += i) {
				t = (long long)t * pows[i] % mod;
				if (t != (hash[j-1] - hash[j-i-1] + mod) % mod) goto fail;
			}
			ans[a] = str.substr(0, i);
			break;
			fail:;
		}
	}
	sort(ans+1, ans+n+1);
	for (int i = 1; i <= n; i++) {
		if (ans[i] == ans[i-1]) cnt++;
		else sum += cnt * cnt, cnt = 1;
	}
	sum += cnt * cnt;
	cout << sum << endl;
	return 0;
}
```


---

## 作者：KSkun (赞：5)

感谢远航之曲提供思路，这是他的原博文[bzoj 1524 [POI2006]Pal | 远航休息栈](http://www.yhzq-blog.cc/bzoj-1524-poi2006pal/)。

另外本题解同步发布于我的博客[[POI2006]PAL-Palindromes 题解 | KSkun's Blog](https://ksmeow.moe/pal_poi06_sol/)，欢迎来逛~

# 题解
这个拼接成回文串的情况，肯定是较短串是较长串的前缀时成立，因此可以Trie树处理这些字符串，然后枚举每个字符串的前缀是否也在里面，在的话试着拼接一下。

判断是否是回文串的方法可以用哈希处理。前串的哈希乘上哈希基的后串长次方再加后串的哈希就能完成拼接。对于每一对这样的字符串显然是反着拼也成立，统计答案是要乘2。自己和自己拼算了两次要减掉。

# 代码
```cpp
// Code by KSkun, 2018/2
#include <cstdio>
#include <cstring>
#include <string>

const int MO = 1e9 + 7, base = 255;

int ch[2000005][26], tot = 1;
int wrd[2000005], cnt[2000005];

int n, len[2000005], hash[2000005], bpow[2000005];
std::string str[2000005];
char strt[2000005];
long long ans = 0;

inline void insert(char* str, int id) {
    int t = 1;
    for(int i = 0; i < len[id]; i++) {
        if(!ch[t][str[i] - 'a']) {
            t = ch[t][str[i] - 'a'] = ++tot;
        } else {
            t = ch[t][str[i] - 'a'];
        }
    }
    wrd[t] = id;
    cnt[t]++;
}

inline int calhash(char* str, int len) {
	long long res = 0;
	for(int i = 0; i < len; i++) {
		res = (res * base + str[i]) % MO;
	}
	return res;
}

int main() {
	scanf("%d", &n);
	bpow[0] = 1;
	for(int i = 1; i < 2000005; i++) {
		bpow[i] = (1ll * bpow[i - 1] * base) % MO;
	}
	for(int i = 1; i <= n; i++) {
		scanf("%d%s", &len[i], strt);
		insert(strt, i);
		hash[i] = calhash(strt, len[i]);
		str[i] = strt;
	}
	for(int i = 1; i <= n; i++) {
		int u = 1;
		for(int j = 0; j < len[i]; j++) {
			u = ch[u][str[i][j] - 'a'];
			if(wrd[u]) {
				if((1ll * hash[wrd[u]] * bpow[len[i]] % MO + hash[i]) % MO == (1ll * hash[i] * bpow[len[wrd[u]]] % MO + hash[wrd[u]]) % MO) {
					ans = ans + 1ll * cnt[u] * 2;
				}
			}
		}
	}
	printf("%lld", ans - n);
	return 0;
}
```

---

## 作者：Baihua (赞：4)

### 【题解】[POI2006]PAL-Palindromes

* [题目地址](https://www.luogu.org/problemnew/show/P3449)

---

思路：

* 回文串和自己相加仍是回文串。

* 当$S[i]$是$S[j]$的前缀时，$S[i]+S[j]$可能构成回文串。

* 对于$S[i]​$，利用$Trie​$获得是$S[i]​$的前缀的字符串。再利用字符串的$Hash​$判断是否回文。

* 知道前串的长度、两串的散列值，就可以获得两串连接后的散列值。如下：

  * ```c++
    HashLink = HashValue[Left] * HashPow[Right.Length] + HashValue[Left]
    ```

下面是部分代码（头文件省略）。

* 把字符串加入字典树，并且计算$Hash$值和长度。

```c++
int Add (int From ) {
	int P = 0 ,R = 1 ;
	unsigned long long int NowHash = 0 , NowLen = 0;
	for (int i = From ; S[i] != '0' ; ++ i) {
		if (!T[P][S[i] - 'a']) T[P][S[i] - 'a'] = ++ Tot;
		P = T[P][S[i] - 'a'] ;
		++ R;
		NowHash = NowHash * HashBase + S[i] ;
		++ NowLen ;
	}
	++ End[P] ;
	Len[P] = NowLen , HashValue[P] = NowHash ;
	return From + R ;
}
```

* 对于每一个字符串，枚举它的前缀，并且判断$Hash(Left + Right) == Hash(Right + Left)$。如果成立，那将对答案贡献2。

  * ```c++
    void Ask (int P , int Now , int E ) {
    
    	if (Now > E) {
    		NowP = P ;
    		return ;
    	}
    	Ask (T[P][S[Now] - 'a'] , Now + 1 , E ) ;
    
    	if (End[P]) {
    		if (HashValue[NowP] * HashPow[Len[P]] + HashValue[P] == HashValue[P] * HashPow[Len[NowP]] + HashValue[NowP]) {
    			Ans += 2 ;
    			if (P == NowP) -- Ans ;
    		}
    	}
    }
    ```

* 最后，每个字符串和自己可以连接。

* 完整代码：

  ```c++
  #include <stdio.h>
  #include <string.h>
  #define Clean(X,K) memset(X,K,sizeof(X))
  using namespace std ;
  #include <iostream>
  const int Maxn = 2000005 , Base = 26 ;
  int N , Tail = 0 , T[Maxn][Base] , End[Maxn] , Tot = 0 , Len[Maxn];
  unsigned long long HashValue[Maxn] , HashBase = 17 , HashPow[Maxn] = {1} , Ans = 0;
  char S[Maxn * 2] , Tmp[Maxn];
  int Add (int From ) {
  	int P = 0 ,R = 1 ;
  	unsigned long long int NowHash = 0 , NowLen = 0;
  	for (int i = From ; S[i] != '0' ; ++ i) {
  		if (!T[P][S[i] - 'a']) T[P][S[i] - 'a'] = ++ Tot;
  		P = T[P][S[i] - 'a'] ;
  		++ R;
  		NowHash = NowHash * HashBase + S[i] ;
  		++ NowLen ;
  	}
  	++ End[P] ;
  	Len[P] = NowLen , HashValue[P] = NowHash ;
  	return From + R ;
  }
  int NowP ;
  void Ask (int P , int Now , int E ) {
  
  	if (Now > E) {
  		NowP = P ;
  		return ;
  	}
  	Ask (T[P][S[Now] - 'a'] , Now + 1 , E ) ;
  
  	if (End[P]) {
  		if (HashValue[NowP] * HashPow[Len[P]] + HashValue[P] == HashValue[P] * HashPow[Len[NowP]] + HashValue[NowP]) {
  			Ans += 2 ;
  			if (P == NowP) -- Ans ;
  		}
  	}
  }
  
  int main () {
  //	freopen ("P3449.in" , "r" , stdin) ;
  	Clean (T , 0) , Clean (End , 0) , Clean (Len , 0);
  	scanf ("%d" , &N) ;
  	for (int i = 1 ; i <= N; ++ i) {
  		int L ;
  		scanf ("%d " , &L) ;
  		scanf ("%s" , Tmp) ;
  		for (int j = 0 ; j < L; ++ j) S[Tail + j] = Tmp[j] ;
  		Tail += L ;
  		S[Tail++] = '0' ;
  	}
  	-- Tail ;
  	int Now = 0 , Cnt = -1;
  	while (Now <= Tail) Now = Add (Now) ;
  	for (int i = 1 ; i < Maxn ; ++ i) HashPow[i] = HashPow[i - 1] * HashBase ;
  	int Lst = 0 ;
  	Cnt = -1 ;
  	for (int i = 1 ; i <= Tail ; ++ i)
  		if (S[i] == '0') {
  			Ask (0 , Lst , i - 1) ;
  			Lst = i + 1 ;
  		}
  	cout << Ans + N<<endl;
  	fclose (stdin) , fclose (stdout) ;
  	return 0 ;
  }
  ```

  

---

## 作者：Utilokasteinn (赞：3)

题目大意：有 $n$ 个**回文串**，任选两个回文串收尾相接组成 $n^2$ 个字符串（可以自己于自己组合）。求这 $n^2$ 个字符串中有几个是回文串。

注意，给出的全都是回文串。

首先容易发现，**回文串的循环节一定是回文串**。

**所以当 $a$ ，$b$ 两个回文串的最小循环节一样时， $ab$ 是回文串**。

证明：

>若回文串 $a$ 是由 $x$ 个回文串 $c$ 组成，回文串 $b$ 是由 $y$ 个回文串 $c$ 组成。则相接后 $ab$ 是由 $x+y$ 个回文串 $c$ 组成。

>在字符串 $ab$ 中，第 $1$ 个 $c$ 与第 $x+y$ 个 $c$ 回文时对应，第 $2$ 个 $c$ 与第 $x+y-1$ 个 $c$ 回文时对应，以此推类。

>若 $x+y$ 为偶，显然 $ab$ 回文。若 $x+y$ 为奇，则还剩第 $(x+y+1)\div2$ 个 $c$ 无串与它回文。因为 $c$ 本来就是回文串，所以不管 $x+y$ 是偶是奇， $ab$ 都是回文串。

那如果 $a$ ，$b$ 两个回文串的最小循环节不一样时， $ab$ 就一定不是回文串吗？

证明：

>若回文串 $a$ 是由 $x$ 个回文串 $s1$ 组成，回文串 $b$ 是由 $s2$ 个回文串 $v$ 组成。

>若相接要回文，及 $s1$ 要与 $s2$ 的后缀回文（假设 $len_s1\le len_s2$）。显然， $s1$ 不可能为 $s2$ 的循环节，那 $s1$ 也就肯定不可能与 $s2$ 回文，及 $ab$ 不回文。

**所以当且仅当 $a$ ，$b$ 两个回文串的最小循环节一样时， $ab$ 是回文串**。

代码就很好写了：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
using namespace std;
ull hash[2000100],mul[2000100],base=31;
int n,m;
ll ans;
char s[2000100];
multiset<ull>se;
inline ull cal(int l,int r)
{
    return hash[r]-hash[l-1]*mul[r-l+1];
}
bool solve(int x)
{
	ull now=cal(1,x);
	for(int i=1;i<=m;i+=x)
	    if(cal(i,i+x-1)!=now)return false;
	se.insert(now);
	return true;
}
int main()
{
    mul[0]=1;
	scanf("%d",&n);
	for(int i=1;i<=2e6;i++)
	    mul[i]=mul[i-1]*base;
	while(n--)
	{
		scanf("%d%se",&m,s+1);
		for(int i=1;i<=m;i++)
		    hash[i]=hash[i-1]*base+s[i];
		for(int i=1;i<=m;i++)
		{
			if(m%i)continue;
			if(solve(i))break;
		}
	}
	while(!se.empty())
	{
		ll num=*se.lower_bound(0);
		ll cnt=se.count(num);
		ans+=cnt*cnt;
		se.erase(num);
	}
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：SovietPower✨ (赞：3)

//学的不久，仅个人理解，可能不对，有错请指出

若要两个回文串相连后仍是回文串，那回文串 si一定是 sj(leni<=lenj)的循环节(可以相等，每个回文串自己+自己肯定是个回文串)

是循环节也就是是前缀

先用Trie树得出一个串上每个点的前缀情况，再通过Hash判断是否为其循环节

这样得出所有 len[i]<=len[j]的满足条件的(si,sj),同样也有(sj,si)

so 答案再\*2 ，但是每个(i,i)仅有一个，这样有n个在res\*2时多了n，so res = res\*2-n


另对于Hash判断循环节，若i是j的循环节，满足：

Hash[i]\* p^len[j]+Hash[j] == Hash[j]\* p^len[i]+Hash[i]

设字串i为abc，母串j为abcabc，选的Hash进制为p

Hash[i](len=3) = ((0+a)p+b)p+c = ap2+bp+c (数字均为次数)

Hash[j](len=6) = (((((0+a)p+b)p+c)p+a)p+b)p+c = ap5+bp4+cp3+ap2+bp+c

现令 x = Hash[i]\* Base^len[j] + Hash[j] = I\*p^6 + J

 y = Hash[j]\* Base^len[i] + Hash[i] = J\*p^3 + I

可得 x = y = ap8+bp7+cp6+ap5+bp4+cp3+ap2+bp+c

(一推就出)

非指针版 817ms 290640kb 内存比较。。

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
using namespace std;
const int N=2000005,base=233;
typedef unsigned long long ull;

int n,len[N],t[N][27],sz,val[N],belong[N];
//belong[i]:i这个节点属于哪个串的 
//注意总长不会超过N，即节点数也不会超过N 
//val[N*27] 过大导致一直RE。。 
ull p[N],Hash[N];
string s[N];
char tmp[N];

inline int read()
{
    int now=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar())
      if(c=='-') f=-1;
    for(;isdigit(c);c=getchar())
      now=(now<<3)+(now<<1)+c-'0';
    return now*f;
}

void Pre()
{
    p[0]=1;
    for(int i=1;i<=2000000;++i)
        p[i]=p[i-1]*base;
}

int main()
{
    Pre();
    n=read();
    for(int i=1;i<=n;++i)
    {
        len[i]=read();
        scanf("%s",tmp);s[i]=tmp;//这样读string会快 
//    TLE:cin>>tmp;
        int u=0;
        ull v=0;
        for(int j=0;j<len[i];++j)
        {
            int id=s[i][j]-'a';
            if(!t[u][id])
                t[u][id]=++sz;
            u=t[u][id];
            v=v*base+(ull)(id+1);
        }
        ++val[u],belong[u]=i,Hash[i]=v;
    }
    long long res=0;
    for(int i=1;i<=n;++i)
    {
        int u=0;
        for(int j=0;j<len[i];++j)
        {
            u=t[u][s[i][j]-'a'];
            if(val[u] && Hash[belong[u]]*p[len[i]]+Hash[i]==Hash[i]*p[len[belong[u]]]+Hash[belong[u]])
                res+=val[u];
        }
    }
    printf("%lld",res*2-n);
    
    return 0;
}
```
指针版 优化内存 941ms 101609kb

```cpp
#include<cstdio>
#include<cctype>
#include<cstring>
#include<iostream>
using namespace std;
const int N=2000005,base=233;
typedef unsigned long long ull;

int n,len[N];
struct Node
{
    int val,belong;
    Node *nxt[27];
    Node()
    {
        val=0;memset(nxt,NULL,sizeof nxt);
    }
};
Node *root=new Node();
Node *rt;
ull p[N],Hash[N];
string s[N];
char tmp[N];

inline int read()
{
    int now=0,f=1;char c=getchar();
    for(;!isdigit(c);c=getchar())
      if(c=='-') f=-1;
    for(;isdigit(c);c=getchar())
      now=(now<<3)+(now<<1)+c-'0';
    return now*f;
}

void Pre()
{
    p[0]=1;
    for(int i=1;i<=2000000;++i)
        p[i]=p[i-1]*base;
}

int main()
{
    Pre();
    n=read();
    for(int i=1;i<=n;++i)
    {
        len[i]=read();
        scanf("%s",tmp);s[i]=tmp;//这样读string会快 
//    TLE:cin>>tmp;
        rt=root;
        ull v=0;
        for(int j=0;j<len[i];++j)
        {
            int id=s[i][j]-'a';
            if(rt->nxt[id]==NULL)
                rt->nxt[id]=new Node();
            rt=rt->nxt[id];
            v=v*base+(ull)(id+1);
        }
        ++rt->val,rt->belong=i,Hash[i]=v;
    }
    long long res=0;
    for(int i=1;i<=n;++i)
    {
        rt=root;
        for(int j=0;j<len[i];++j)
        {
            rt=rt->nxt[s[i][j]-'a'];
            if(rt->val && Hash[rt->belong]*p[len[i]]+Hash[i]==Hash[i]*p[len[rt->belong]]+Hash[rt->belong])
                res+=rt->val;
        }
    }
    printf("%lld",res*2-n);
    
    return 0;
}
```

---

## 作者：Prean (赞：1)

其实每个串都不是回文串也能做的说。。。

题意：给定 $ n $ 个互不相同的串，两两拼接一共能够拼出 $ n^2 $ 个串，问这 $ n^2 $ 个串中有几个回文串。

首先假设拼接出来的串是 $ AB $，且 $ A $ 的长度大于 $ B $ 的长度。

$ AB $ 是回文串，那么回文中心一定在 $ A $ 上，那么就说明 $ B $ 的反串一定是 $ A $ 的前缀。将 $ A $ 去掉这个前缀后，剩下的后缀一定也是回文串。

然后问题就变成了了询问有多少个串是一个串的前缀，以及一个串的后缀是否是回文串。前者用 Trie，后者用 Hash 就好了。

每个串都是回文串只是方便了处理而已，处理后缀是否为回文串相当于处理前缀是否为回文串。

不懂为什么是紫题。。。
```cpp
#include<algorithm>
#include<cstdio>
typedef unsigned ui;
const ui M=2e6+5,mod=998244353;
ui n,m,mx,tot(1),p[M],len[M],cnt[M],chi[M][26];char s[M],*S[M];bool Vis[M],*vis[M];long long ans;
inline void Insert(char*s,const ui&len){
	ui i,now(1);
	for(i=0;i^len;++i)!chi[now][s[i]-97]&&(chi[now][s[i]-97]=++tot),now=chi[now][s[i]-97];++cnt[now];
}
inline void Match(char*s,const ui&id,const ui&len){
	ui i,now(1);
	for(i=0;i^len;++i)cnt[now]&&vis[id][len-i-1]&&(ans+=cnt[now]),now=chi[now][s[i]-97];
}
signed main(){
	ui i,j,h1,h2;scanf("%u",&m);S[1]=s;vis[1]=Vis;p[0]=1;
	for(i=1;i<=m;++i)scanf("%u%s",len+i,S[i]),S[i+1]=S[i]+len[i],Insert(S[i],len[i]),len[i]>mx&&(mx=len[i]);
	for(i=1;i^mx;++i)p[i]=13331ull*p[i-1]%mod;
	for(j=1;j<=m;++j){
		vis[j+1]=vis[j]+len[j];h1=h2=0;
		for(i=0;i^len[j];++i)h1=(1ull*p[1]*h1+(S[j][i]-97))%mod,h2=(h2+1ull*p[i]*(S[j][i]-97))%mod,vis[j][i]=h1==h2;
	}
	for(i=1;i<=m;++i)Match(S[i],i,len[i]);printf("%lld",(ans<<1)+m);
}
```

---

## 作者：未来姚班zyl (赞：0)

## 题目大意

给出 $n$ 个回文串，将它们两两组合（随意顺序），得到 $n^2$ 个字符串，求这些字符串中有多少还是回文串。

## 题目分析

如果两个字符串长度相等，显然它们得互为反串，而它们都回文，则它们必须相等。

否则，较短的串肯定是较长的串的前缀或后缀的反串。而由于它们都回文，则较长串的前缀和后缀互为反串，而较长串的前缀或后缀的反串又是一个回文串。所以较短串是较长串的前缀。

所以，无论按什么顺序拼，我们只要再满足较长串除去和较短串相同的前缀后，剩下那一段依旧回文。

判断回文可以哈希，统计前缀可以用 trie 树，复杂度 $O(\sum|S_i|)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define L x<<1
#define R x<<1|1
#define mid (l+r>>1)
#define lc L,l,mid
#define rc R,mid+1,r
#define Root 1,1,n
#define OK l>=Ll&&r<=Rr
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define pb push_back
#define ull unsigned ll
#define e(x) for(int i=h[x],y=to[i];i;i=nxt[i],y=to[i])
#define E(x) for(auto y:p[x])
#define Pi pair<int,int>
#define ui unsigned ll
inline ll read(){ll s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57) s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
inline void pf(ll x){if(x<0) putchar('-'),x=-x;if(x>9)pf(x/10);putchar(x%10+48);}
const int N =2e6+5,M=2e6+5,inf=2147000000;
const ll llf=1e18,mod=1e9+7;
const ui base=13331;
using namespace std;
struct node{
	int son[26],end;
}trie[M];
int cnt,n,o;
ll ans;
string s[N];
inline void insert(string s){
	int len=s.length(),now=0;
	rep(i,0,len-1){
		int k=s[i]-'a';
		if(!trie[now].son[k])trie[now].son[k]=++cnt;
		now=trie[now].son[k];
	}
	trie[now].end++;
}
ui H[N],A[N],p[N];
inline ui getHash(int l,int r){
	if(l>r)return 0;
	return H[r]-H[l-1]*p[r-l+1];
}
inline ui gethAsh(int l,int r){
	if(l>r)return 0;
	return A[l];	
}
inline void solve(string s){
	int len=s.length(),now=0;
	rep(i,1,len)H[i]=H[i-1]*base+s[i-1];
	A[len+1]=0;
	per(i,len,1)A[i]=A[i+1]*base+s[i-1];
	rep(i,1,len){
		int k=s[i-1]-'a';
		now=trie[now].son[k];
		if(getHash(i+1,len)==gethAsh(i+1,len))ans+=trie[now].end*(1+(i!=len));
		
	}
}
int main(){
	p[0]=1;
	rep(i,1,N-5)p[i]=p[i-1]*base;
	n=read();
	rep(i,1,n)o=read(),cin >>s[i],insert(s[i]);
	rep(i,1,n)solve(s[i]);
	cout <<ans;
	return 0;
}
```


---

