# Petr#

## 题目描述

很久很久以前，当Petya还是一个学生汪的时候，他对Petr#语言的语法极感兴♂趣。在一堂课上Petya对如下问题产生了兴♂趣：给定字符串t，该字符串以s begin开头，s end结尾的连续子串有多少个。当且仅当子串所含字符不同时，他们被认为是不同的。它们在t中出现的位置与他们是否相同并无关系。Petya的数学并不好（？？？），所以他并不能得出这一数字。帮♂帮他吧！

## 样例 #1

### 输入

```
round
ro
ou
```

### 输出

```
1
```

## 样例 #2

### 输入

```
codeforces
code
forca
```

### 输出

```
0
```

## 样例 #3

### 输入

```
abababab
a
b
```

### 输出

```
4
```

## 样例 #4

### 输入

```
aba
ab
ba
```

### 输出

```
1
```

# 题解

## 作者：zyx1013 (赞：1)

看到子串查找，首先想到哈希。

这题我们先对三个串 $t,sbegin,send$ 进行哈希计算，然后看见长度 $\le 2000$，想到在 $t$ 串里暴力查找符合条件的子串。

去重时要将符合状态的哈希存到一个 STL 里面，这里我用的是 bitset。判断一个符合要求的子串是否之前就计算过，若没有，再累加答案。

# AC CODE

我用的双哈希。

时间复杂度 $O(\left |t\right |^2)$。

如果复杂度有误请指出，因为我不知道 bitset 的复杂度。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
il ll read(){
	char c(getchar());
	ll x(0),f(1);
	for(;c<'0'||c>'9';){
		if(c=='-') f=-1;
		c=getchar();
	}
	for(;c>='0'&&c<='9';) x=x*10+c-'0',c=getchar();
	return f*x;
}
il void write(ll x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
il void write(ll x,char c){
	write(x);putchar(c);
}
il void file(){
	freopen("a.txt","w",stdout);
}
const ll base=137,mod1=1e9+7,N=2005,mod2=1e9+9;
char t[N],sb[N],se[N];
ll ht1[N],hsb1[N],hse1[N];
ll ht2[N],hsb2[N],hse2[N];
ll lt,lsb,lse,pw1[N],pw2[N],ans;
bitset<mod2+5> b1,b2;
il ll cmp(ll x,ll y){
	if(y-x+1<lsb||y-x+1<lse) return 0;
	ll tb1=(ht1[x+lsb-1]-ht1[x-1]*pw1[lsb]%mod1+mod1)%mod1,tb2=(ht2[x+lsb-1]-ht2[x-1]*pw2[lsb]%mod2+mod2)%mod2;
	ll sb1=hsb1[lsb],sb2=hsb2[lsb];
	if(!(sb1==tb1&&sb2==tb2)) return 0;
	ll te1=(ht1[y]-ht1[y-lse]*pw1[lse]%mod1+mod1)%mod1,te2=(ht2[y]-ht2[y-lse]*pw2[lse]%mod2+mod2)%mod2;
	ll se1=hse1[lse],se2=hse2[lse];
	if(!(se1==te1&&se2==te2)) return 0;
	ll k1=(ht1[y]-ht1[x-1]*pw1[y-x+1]%mod1+mod1)%mod1,k2=(ht2[y]-ht2[x-1]*pw2[y-x+1]%mod2+mod2)%mod2;
	if(b1[k1]&&b2[k2]) return 0;
	b1[k1]=b2[k2]=1;
	return 1;
}//比较子串是否相同且是否未曾被统计过
int main(){
	scanf("%s%s%s",t+1,sb+1,se+1);
	lt=strlen(t+1);
	lsb=strlen(sb+1);
	lse=strlen(se+1);
	for(ll i=1;i<=lt;i++) ht1[i]=(ht1[i-1]*base+t[i]-'a'+1)%mod1,ht2[i]=(ht2[i-1]*base+t[i]-'a'+1)%mod2;
	for(ll i=1;i<=lsb;i++) hsb1[i]=(hsb1[i-1]*base+sb[i]-'a'+1)%mod1,hsb2[i]=(hsb2[i-1]*base+sb[i]-'a'+1)%mod2;
	for(ll i=1;i<=lse;i++) hse1[i]=(hse1[i-1]*base+se[i]-'a'+1)%mod1,hse2[i]=(hse2[i-1]*base+se[i]-'a'+1)%mod2;
	for(ll i=pw1[0]=pw2[0]=1;i<=lt;i++) pw1[i]=pw1[i-1]*base%mod1,pw2[i]=pw2[i-1]*base%mod2;
	//哈希模版 
	for(ll i=1;i<=lt;i++){
		for(ll j=i;j<=lt;j++){
			if(cmp(i,j)) ans++;
		}
	}
	write(ans,'\n');
	return 0;
}
```

---

## 作者：kimi0705 (赞：1)

一眼题。

暴力枚举 $i,j$，即 $[i,j]$ 范围的子串。

用哈希判断 $s_{begin}$ 是否是它的前缀， $s_{end}$ 是否值它的后缀，简单哈希即可。

去重用一下 bitset 即可。

时间复杂度 $O(\frac{n^3}{\omega})$。

---

## 作者：Katyusha_01 (赞：1)

### 看到别的题解都是哈希，提供一种 Trie 树做法

首先对于每一个位置，暴力匹配判断是否可以作为起点/终点。

从每个起点开始，在 Trie 树上暴力向后扫，如果扫到的位置可以作为终点，在 Trie 树上标记出来，最后统计标记个数即可(记得判断长度是否合法)。

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef struct{
	int son[26];
	bool b;
}Trie;
Trie t[2000011];
int idx;
int n,x,y;
char s[2011],B[2011],E[2011];
bool a[2011],e[2011];
int ans = 0;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin >> s;n = strlen(s);
    for(int i = n;i;i--)
    	s[i] = s[i - 1];
    cin >> B;x = strlen(B);
    for(int i = x;i;i--)
    	B[i] = B[i - 1];
    cin >> E;y = strlen(E);
    for(int i = y;i;i--)
    	E[i] = E[i - 1];
    for(int i = 1;i + y - 1 <= n;i++)
    {
    	bool flag = 1;
    	for(int j = 1;j <= y;j++) if(s[i + j - 1] != E[j])
    		flag = 0;
    	e[i + y - 1] = flag;
	}
	for(int i = 1;i + x - 1 <= n;i++)
	{
		bool flag = 1;
		for(int j = 1;j <= x;j++) if(s[i + j - 1] != B[j])
			flag = 0;
		a[i] = flag;
	}
	for(int i = 1;i <= n;i++) if(a[i])
	{
		int p = 0;
		for(int j = i;j <= n;j++)
		{
			if(!t[p].son[s[j] - 'a'])
				t[p].son[s[j] - 'a'] = ++idx;
			p = t[p].son[s[j] - 'a'];
			if(e[j] && !t[p].b && (j - i + 1) >= max(x,y))
				ans++,t[p].b = 1;
		}
	}
	cout << ans;
    return 0;
}
```

---

## 作者：Imerance1018 (赞：0)

### Description

[传送门](https://codeforces.com/problemset/problem/113/B)

### Solution

考虑字符串哈希，定义 $hs_{i,j}$ 表示原字符串第 $i$ 位到第 $j$ 位的哈希值。

然后我们可以 $O(n^2)$ 地枚举子串，再判断子串开头是否为 $s_{begin}$，结尾是否为 $s_{end}$，如果是则将其哈希值加入一个 vector（注意此处如果加入的是字符串会 MLE）。

最后将 vector 去重即可。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2010,p=133331,mod=1e15+9;
string x,bg,ed;
int n;
int hs[N][N],x1,x2; 
vector<int>ans;
signed main()
{
	cin>>x>>bg>>ed;
	n=x.size();
	int len1=bg.size();
	int len2=ed.size();
	x='*'+x;
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++) 
			hs[i][j]=(hs[i][j-1]*p+(long long)x[j])%mod;//预处理哈希
	for(int i=0;i<len1;i++)x1=(x1*p+(long long)bg[i])%mod;
	for(int i=0;i<len2;i++)x2=(x2*p+(long long)ed[i])%mod;
	for(int i=1;i<=n;i++)
	{
		for(int j=i;j<=n;j++)
		{
				if(j-i+1>=max(len1,len2))
					if(hs[i][i+len1-1]==x1&&hs[j-len2+1][j]==x2)//O(1)判断
						ans.emplace_back(hs[i][j]);
		}
	}
	sort(ans.begin(),ans.end());
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	cout<<ans.size();
	return 0;
}
``````

---

## 作者：dthythxth_Huge_Brain (赞：0)

## 题目大意
给你三个字符串 $s,a,b$，问你有多少个不同字符串以 $a$ 开头，以 $b$ 结尾，且是 $s$ 的子串。

注意这里的不同指的是两个字符串至少有一个字符不相同或者长度不同，字符串长度小于 $2000$。

## 解题思路

观察到字符串长度很小，我们首先有一个 $O(\left|s\right|^3)$ 的暴力做法，即枚举每个 $s$ 的子串的两端，判断该串是否合法。

考虑优化，我们发现可以将 $s$ 的所有子串和 $a,b$ 哈希，最后暴力枚举子串的两端，$O(1)$ 判断这个子串的头和尾是否与 $a$ 和 $b$ 相等，再把哈希值存进哈希表里，最后输出哈希表大小。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define int long long
const int base=13331,mod=1e13+19;//哈希的基数和模数 
char s[2003],beg[2003],ed[2003];
int hash[2003][2003],n,l1,l2,hsh1,hsh2;
std::unordered_set<int>set;//哈希表 
signed main(){
	scanf("%s%s%s",s+1,beg+1,ed+1),n=strlen(s+1),l1=strlen(beg+1),l2=strlen(ed+1);
	for(int l=1;l<=n;l++)for(int r=l;r<=n;r++)hash[l][r]=(hash[l][r-1]*base+s[r])%mod;//对 s 进行哈希
	for(int i=1;i<=l1;i++)hsh1=(hsh1*base+beg[i])%mod;//对 a 进行哈希
	for(int i=1;i<=l2;i++)hsh2=(hsh2*base+ed[i])%mod;//对 b 进行哈希
	for(int l=1;l<=n;l++)for(int r=l;r<=n;r++)if(r-l+1>=std::max(l1,l2)&&hash[l][l+l1-1]==hsh1&&hash[r-l2+1][r]==hsh2/*判断子串的头尾哈希值是否相等 */)set.insert(hash[l][r]);//存入哈希表 
	printf("%lld",set.size());
	return 0;
}

```

---

## 作者：xxxxxzy (赞：0)

#### CF113B Petr# 题解

看到要找到相同的字串，很容易想到字符哈希。

用一个数组记录原来字符串，再用两个变量贮存前缀和后缀的哈希值。

注意到数据量很小，可以直接暴力 $O(n^2)$ 枚举左右端点，然后再判断即可。

对于一个合法字串，只需要把字串的哈希值扔到 map 里面再统计个数就行了。

（数据也是挺水的，没卡哈希）

给出代码：

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int p[500005],d[500005],m,len,ans,fro,bak;
vector<int> ed;
char s[500005];
string fr,ba;
int ask(int l,int r){
	return d[r]-d[l-1]*p[r-l+1];
}
unordered_map<int,bool> cnt;//更快
signed main(){
	scanf("%s",s+1);
	len=strlen(s+1);
	d[0]=p[0]=1;
	for(int i=1;i<=len;i++){
		d[i]=d[i-1]*131+s[i]-'a'+1;
		p[i]=p[i-1]*131;
	}
	cin>>fr>>ba;
	for(int i=0;i<fr.length();i++) fro=fro*131+fr[i]-'a'+1;
	for(int i=0;i<ba.length();i++) bak=bak*131+ba[i]-'a'+1;
	int pos=max(fr.length(),ba.length()),len2=fr.length(),len3=ba.length();
	for(int i=pos;i<=len;i++){
		for(int j=1;j+i-1<=len;j++){
			int l=j,r=j+i-1;
			if(ask(l,l+len2-1)==fro&&ask(r-len3+1,r)==bak){
				int d=ask(l,r);
				if(!cnt[d]) cnt[d]=1,ans++;
			}
		}
	}
	cout<<ans;
}
```



---

## 作者：andyli (赞：0)

给定字符串 $s$，问该字符串以 $x$ 开头，$y$ 结尾的连续子串有多少个。  
可以通过枚举 $x$ 和 $y$ 的中间部分并用字符串哈希判断左右是否分别为 $x$ 和 $y$ 来枚举这样的子串，然后使用 `std::set` 对这样子串的哈希值去重。  

```cpp
int main() {
    dR(std::string, s, x, y);
    RollingHash h;
    auto S = h.build(s), X = h.build(x), Y = h.build(y);
    auto hx = h.query(X), hy = h.query(Y);
    gp<u64, bool> a;
    for (int r = 0; r <= len(s); r++)
        for (int l = 0; l < r; l++)
            if (r - l >= len(x) && r - l >= len(y))
                if (h.query(S, l, l + len(x)) == hx && h.query(S, r - len(y), r) == hy)
                    a[h.query(S, l, r)] = true;
    writeln(len(a));
    return 0;
}
```

---

## 作者：Allanljx (赞：0)

## 思路
用哈希值快速判断出所有的前后缀的起始位置，分别存入 $t1$ 数组和 $t2$ 数组，然后枚举两个数组，在确保前缀的结尾在后缀的结尾之前时将整个字串的哈希值存入 $ans$ 数组中，然后排序，前后缀不矛盾时就 ``ans++``。
## 代码
```cpp
#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
char s[4005],s1[4005],s2[4005];
int db[4005],ha[4005],ans;
vector<int> t1,t2;
int ans1[4000005],top;
signed main()
{
	scanf("%s%s%s",(s+1),(s1+1),(s2+1));
	int l=strlen(s+1),l1=strlen(s1+1),l2=strlen(s2+1);
	db[0]=1;
	for(int i=1;i<=l;i++) db[i]=db[i-1]*27;
	for(int i=1;i<=l;i++) ha[i]=ha[i-1]*27+s[i]-'a'+1;
	int h1=0,h2=0;
	for(int i=1;i<=l1;i++) h1=h1*27+s1[i]-'a'+1;
	for(int i=1;i<=l2;i++) h2=h2*27+s2[i]-'a'+1;
	for(int i=1;i+l1-1<=l;i++)//前缀的起始位置
		if(h1==ha[i+l1-1]-ha[i-1]*db[l1]) t1.push_back(i);
	for(int i=1;i+l2-1<=l;i++)//后缀的起始位置
		if(h2==ha[i+l2-1]-ha[i-1]*db[l2]) t2.push_back(i);
	for(int i=0;i<t1.size();i++)
	{
		for(int j=0;j<t2.size();j++)
		{
			if(t1[i]>t2[j]||t1[i]+l1-1>t2[j]+l2-1) continue;
			int sum=ha[t2[j]+l2-1]-ha[t1[i]-1]*db[(t2[j]+l2-t1[i])];
			ans1[++top]=sum;//存入hash值
		}
	}
	sort(ans1+1,ans1+1+top);
	for(int i=1;i<=top;i++) if(ans1[i]!=ans1[i-1]) ans++;//去重
	printf("%u",ans);
    return 0;
}
```

---

## 作者：TsH_GD (赞：0)

### 前言

应该算是远古时期的一道题了吧，不过感觉挺经典的。

题意是给出三一个字符串，求以 $a$ 开头 $b$ 结尾的本质不同的字符串数。

## 讲解

字符串匹配加一个字符串哈希判重。

字符串哈希就是把字符串转成一个 $p$ 进制的数，每一段字符串都有一个对应的哈希值。 $p$ 尽量取质数


###  ACcode:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N=2005;
const int pr=131;
ull power[N],h[N],b,e;
char t[N],sb[N],se[N];
int tx,ty,x[N],y[N],lt,lb,le,ans;
void pre() {
    power[0]=1;
    for(int i=1; i<=lt; ++i)
        power[i]=power[i-1]*pr,h[i]=h[i-1]*pr+t[i]-'a'+1;
    for(int i=1; i<=lb; ++i)b=b*pr+sb[i]-'a'+1;
    for(int i=1; i<=le; ++i)e=e*pr+se[i]-'a'+1;
}
ull has(int l,int r) {
    return h[r]-h[l-1]*power[r-l+1];
}
unordered_map<ull,bool>mp;
int main() {
    scanf("%s%s%s",t+1,sb+1,se+1);
    lt=strlen(t+1);
    lb=strlen(sb+1);
    le=strlen(se+1);
    pre();
    for(int i=1; i<=lt-lb+1; ++i) 
        if(has(i,i+lb-1)==b)x[++tx]=i;
    for(int i=le; i<=lt; ++i)
        if(has(i-le+1,i)==e)y[++ty]=i;
    for(int i=1; i<=tx; ++i)
        for(int j=1; j<=ty; ++j)
            if(x[i]<=y[j]&&y[j]-x[i]+1>=max(le,lb))
            {
                ull ha=has(x[i],y[j]);
                if(!mp[ha])++ans,mp[ha]=true;
            }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：peterwuyihong (赞：0)

# 大家好，我叫$ Peter $
这道题我$K$了好久好久就是少加了一句话$orz$\
我是这么做的$↓$\
先用字符串$Hash$判断出两个子串的出现位置，放在两个数组$C,P$里\
在暴力枚举这两个数组判断一下\
因为要去重，所以要把$Hash$值丢到一个桶里，排序，去重即可
## 注意
比如说这种数据：
```latex
abcde
cde
abc
```
## 贼坑
你的两个数组是这样的$C: \{  3 \} $ $P:\{ 3 \}$ \
此时是合法的，但是这并不符合要求，连不起来\
所以要加上这样一句话
```cpp
if(pos[i]<=POS[j]&&POS[j]-pos[i]+1>=max(lenc,lenp))
```
其他都没有问题，可以看看这个$Hash$[Hash](https://blog.csdn.net/pengwill97/article/details/80879387)
## 贴上代码一枚
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ULL unsigned long long
#define maxn 5000
#define base 131
ULL f[maxn],t[maxn];
char c[maxn],p[maxn],a[maxn];
ULL C,P;
int pos[maxn],POS[maxn],Cindy,Peter;
int lena,lenc,lenp;
void work(ULL&x,char *s)
{
	x=0;
	for(int i=1;i<=strlen(s+1);i++)
	x=x*base+s[i]-'a'+1;
}
void init()
{
	scanf("%s",a+1);
	scanf("%s",c+1);
	scanf("%s",p+1);
	lena=strlen(a+1);
	lenc=strlen(c+1);
	lenp=strlen(p+1);
	t[0]=1;
	for(int i=1;i<=lena;i++)
	t[i]=t[i-1]*base,f[i]=f[i-1]*base+a[i]-'a'+1;
	work(C,c),work(P,p);
}
ULL H(int l,int r)
{
	return f[r]-f[l-1]*t[r-l+1];
}
ULL Love[maxn*maxn];int tot;
int main()
{
	init();
	for(int i=1;i<=lena-lenc+1;i++)
	if(H(i,i+lenc-1)==C)pos[++Cindy]=i;
	for(int i=lenp;i<=lena;i++)
	if(H(i-lenp+1,i)==P)POS[++Peter]=i;
	for(int i=1;i<=Cindy;i++)
	for(int j=1;j<=Peter;j++)
	if(pos[i]<=POS[j]&&POS[j]-pos[i]+1>=max(lenc,lenp))
	Love[++tot]=H(pos[i],POS[j]);
	sort(Love+1,Love+tot+1);
	printf("%d",unique(Love+1,Love+tot+1)-Love-1);
}
```
###### 祝$ Cindy $在$ 6 $班越来越好

---

