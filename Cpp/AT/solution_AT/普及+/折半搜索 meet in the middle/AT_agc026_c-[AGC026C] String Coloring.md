# [AGC026C] String Coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc026/tasks/agc026_c

長さ $ 2N $ の，英小文字のみからなる文字列 $ S $ が与えられます。

$ S $ の各文字を赤色か青色かに塗り分ける方法は $ 2^{2N} $ 通りありますが，このうち以下の条件を満たす塗り分け方は何通りですか？

- 赤色に塗られた文字を**左から右に**読んだ文字列と，青色に塗られた文字を**右から左に**読んだ文字列が一致する

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 18 $
- $ S $ の長さは $ 2N $ である
- $ S $ は英小文字のみからなる

### Sample Explanation 1

以下の $ 4 $ 通りの塗り分け方が存在します。 - cabaacba - cabaacba - cabaacba - cabaacba

### Sample Explanation 4

答えは32bit整数型で表せないこともあります。

## 样例 #1

### 输入

```
4
cabaacba```

### 输出

```
4```

## 样例 #2

### 输入

```
11
mippiisssisssiipsspiim```

### 输出

```
504```

## 样例 #3

### 输入

```
4
abcdefgh```

### 输出

```
0```

## 样例 #4

### 输入

```
18
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa```

### 输出

```
9075135300```

# 题解

## 作者：Hadtsti (赞：4)

### 题意简述
给出一个长度为 $2n(1\le n\le18)$ 的全部由小写字母构成的字符串 $S$。对其红蓝染色，求使得红色字母组成的字符串翻转后与蓝色字母组成的字符串完全相同的染色方案数。
### 题目分析
折半搜索的经典题了吧。

很明显直接枚举染色情况时间复杂度会炸，所以我们考虑更优的做法。

我们先来看看什么是折半搜索。
> 双向同时搜索（折半搜索，又称 Meet in the middle 算法）的基本思路是从状态图上的起点和终点同时开始进行广搜或深搜。如果发现搜索的两端相遇了，那么可以认为是获得了可行解。

> 暴力搜索的复杂度往往是指数级的，而改用折半搜索后复杂度的指数可以减半，即让复杂度从 $O(a^b)$ 降到 $O(a^{b/2})$。

> ——OI Wiki

本题就可以采用折半搜索。具体来说，可以将 $S$ 分为前后长度都为 $n$ 的两段 $S_0$ 和 $S_1$。两段的染色情况可以分别考虑。设前半段的红串为 $red_0$，蓝串为 $blue_0$；后半段红串为 $red_1$，蓝串为 $blue_1$。注意到：

$$\left\{
\begin{aligned}
&|red_0|+|red_1|=|blue_0|+|blue_1|=n\\
&|red_0|+|blue_0|=|red_1|+|blue_1|=n\\
\end{aligned}
\right.~$$

得到
$$\left\{
\begin{aligned}
&|red_1|=|blue_0|\\
&|red_0|=|blue_1|\\
\end{aligned}
\right.~$$

又有 $red_0+red_1=(blue_0+blue_1)'$，因此有 
$$\left\{
\begin{aligned}
&red_1=blue_0'\\
&red_0=blue_1'\\
\end{aligned}
\right.~$$

也就是说，前半段的红串是后半段的蓝串的反串，前半段的蓝串是后半段红串的反串（本部分证明参考了 [Ezio__Auditore](https://www.luogu.com.cn/user/87329) 大佬的题解，在此膜拜大佬）

那么我们就可以先在前半段暴力枚举每个字母的染色情况，把红串和蓝串一起哈希一下存到哈希表里（可以通过 `map` 实现）；然后在后半段倒着暴力枚举字母的染色情况，把蓝串和红串一起哈希一下，把哈希表里的方案数加到答案里。

最后就是字符串哈希的实现。本题字符串较短，冲突概率相对较小，因此只需要把字符串看作一个 $p$ 进制数（$p$ 为质数）对一个模数取模即可。由于取模运算太慢，我们直接用 `unsigned long long` 存储，这样自然溢出就可以实现对 $2^{64}$ 的取模了，目前最优解。
### 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long
map<pair<ull,ull>,int>mp;//哈希表 
int n;
long long ans;
string s[2];
void dfs(int x,ull hs1/*红串哈希值*/,ull hs2/*蓝串哈希值*/,bool fg) 
{
	if(x>n) 
	{
		if(fg)
			ans+=mp[{hs1,hs2}];//统计方案数
		else
			mp[{hs2,hs1}]++; //前半段的红串蓝串丢到哈希表里 
		return;
	} 
	dfs(x+1,hs1*131ull/*一个质数 p*/+s[fg][x-1],hs2,fg);//第 x 个字符染成红的 
	dfs(x+1,hs1,hs2*131ull+s[fg][x-1],fg);//第 x 个字符染成蓝的
}
int main() 
{
	ios::sync_with_stdio(0);
	cin.tie();
	cout.tie();
	cin>>n>>s[0];
	s[1]=s[0].substr(n,n);
	reverse(s[1].begin(),s[1].end());//方便操作，直接把后半段翻转 
	s[0]=s[0].substr(0,n);//取前半段 
	dfs(1,0,0,0);
	dfs(1,0,0,1);
	cout<<ans;
	return 0;
}
```


---

## 作者：Harrylzh (赞：3)

## 思路

发现数据范围不大，应该是搜索，但 $2^{36}$ 一定超时。所以采用折半搜索，变成 $2^{18}$，不会超时。考虑怎么在确定一般红蓝排列的情况下判断个数。发现前半段的红串和后半段的蓝串长度相等，且都是相同字符串的开头部分，所以它们相等。前半段的蓝串和后半段红串同理。所以只需要分别搜索前半段和后半段，后半段时累加答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
string s;
long long ans=0;
bool plan[50];
map<pair<string,string> ,long long>mp;
void dfs1(long long step)
{
	if(step>n)
	{
		string a="",b="";
		for(long long i=1;i<=n;i++)
		{
			if(plan[i]==0) a=a+s[i];
		}
		for(long long i=1;i<=n;i++)
		{
			if(plan[i]==1) b=b+s[i];
		}
		if(!mp.count(make_pair(a,b))) mp[make_pair(a,b)]=1;
		else mp[make_pair(a,b)]++;//存map中，方便查找
		return;
	}
	plan[step]=0;
	dfs1(step+1);
	plan[step]=1;
	dfs1(step+1);
}
void dfs2(long long step)
{
	if(step>n+n)
	{
		string a="",b="";
		for(long long i=n+n;i>=n+1;i--)
		{
			if(plan[i]==0) a=a+s[i];
		}
		for(long long i=n+n;i>=n+1;i--)
		{
			if(plan[i]==1) b=b+s[i];
		}
		if(mp.count(make_pair(b,a))) ans+=mp[make_pair(b,a)];//查找并累加答案
		return;
	}
	plan[step]=0;
	dfs2(step+1);
	plan[step]=1;
	dfs2(step+1);
}
int main()
{
	cin>>n;
	cin>>s;
	s=' '+s;
	dfs1(1);
	dfs2(n+1);
	printf("%lld",ans);
}
```

---

## 作者：Ezio__Auditore (赞：3)

## AT3972 [AGC026C] String Coloring

[[Statement]](https://www.luogu.com.cn/problem/AT3972)

Date: Apr. 14th

---
#### 题意：
给定一个长度为 $2n$ 的字符串 $S$，对每一个字符红蓝染色，将同色的字符连接成新的字符串，求最后使得 红串 和 翻转后的蓝串 相同的染色方案数。

限制：$n \le 18$
    
---
#### 分析：
比较明显的折半搜索。

记前半段为 $A$， 后半段为 $B$，红色用 $S_r$、蓝色用 $S_b$ 表示，**$S'$  表示 $S$ 翻转后的字符串**。

根据题意有如下关系：
$$
\begin{aligned}
& |A| =  |B| = n\\
& |A|=|A_r| + |A_b|\\
& |B|=|B_r| + |B_b|
\end{aligned}
$$
而红串和蓝串最终翻转后相同，所以有 $|A_r| + |B_r| = |A_b| + |B_b|$ 且 $A_r + B_r = (A_b + B_b)'$。

稍微改写一下：
$$
\begin{aligned}
& |A_r| + |B| - |B_b|  =  |A| - |A_r| + |B_b|\\
& \Rightarrow |A_r| - |B_b| = |B_b| - |A_r|\\
& \Rightarrow |A_r| = |B_b|
\end{aligned}
$$
同理，$|A_b| = |B_r|$。

于是有：

$\because A_r + B_r = (A_b + B_b)'，|A_r| = |B_b|, |A_b| = |B_b|$

$\therefore A_r = B_b', A_b = B_r' $ 

即 **$A$ 中的红串 = $B$ 中的蓝串的反串** 且 **$A$ 中的蓝串 = $B$ 中的红串的反串。**

(这个结论非常符合直觉，可能一眼就能猜到，这里严谨证明一下。)


---
易得折半搜索的方法：

- 我们对 A 串正着搜，记录 $A_r, A_b$ 的 Hash；$B$ 串反着搜，记录 $B_r', B_b'$ 的 Hash。

- 若 $A_r = B_b'\ \text{and}\ A_b = B_r'$ ，就可以将 $A_r, A_b$ 的贡献加入答案一次。

---
#### Code：
实际写折半搜索的时候，不用根据方向分类讨论颜色关系。

因为一种合法的染色方案中，将红蓝对调，也是一种合法的方案。所有红蓝染色的方案一定是"对称"的。

挺小清新的 AT 题。
```cpp
#include <bits/stdc++.h>

template<class _Tp = int> _Tp read() {
  _Tp w = 0;
  bool f = 0;
  char ch = getchar();
  while (!isdigit(ch)) f |= ch == '-', ch = getchar();
  while (isdigit(ch)) w = (w << 3) + (w << 1) + (ch ^ 48), ch = getchar();
  return f ? -w : w;
}
typedef long long ll;
const int kMaxN = 18 + 1;
std::map<std::pair<ll, ll>, int> map;

int n;
ll ans;
char s[kMaxN << 1];

ll shift(ll hs, char c) {
  static int base = 29, mod = 1019260817;
  return (hs * base + c - 'a' + 1) % mod;
}
void dfs(int x, ll hs1, ll hs2, int d) {
  if (d == 1 && x > n) {
    map[std::make_pair(hs1, hs2)]++;
    return;
  } 
  if (d == -1 && x <= n) {
    ans += map[std::make_pair(hs1, hs2)];
    return;
  }
  dfs(x + d, shift(hs1, s[x]), hs2, d);
  dfs(x + d, hs1, shift(hs2, s[x]), d);
}

int main() {
  n = read();
  scanf("%s", s + 1);
  dfs(1, 0, 0, 1);
  dfs(n << 1, 0, 0, -1);
  std::cout << ans << std::endl;
  return 0;
}
```

---
**END.**

---

## 作者：Krimson (赞：3)

安利个人[blog](https://www.cnblogs.com/Guts/p/14655127.html)


------------

~~这题挺简单的，就是有点难~~  
这题都快把折半搜索写在题面里了，考虑如何折半。  

如果前半部分搜出来的两种颜色字符串哈希值是 $(x_l,y_l)$ ，后半部分搜出来是 $(x_r,y_r)$，哈希的底是 $D$ ，那么这两个能匹配起来的条件是：  
$
\begin{aligned}
x_l+D^n x_r&=y_r+D^n y_l\\
x_l+D^n y_l&=y_r -D^n x_r\\
\end{aligned}
$

到这一步就不用多解释了，直接上map。  
时间复杂度 $O(n2^n)$。    


_Code_
------------
```cpp

#include<bits/stdc++.h>
using namespace std;
#define il inline
#define ri register int
#define ll long long
#define ui unsigned int
il ll read(){
    bool f=true;ll x=0;
    register char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=false;ch=getchar();}
    while(ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    if(f) return x;
    return ~(--x);
}
il void write(const ll &x){if(x>9) write(x/10);putchar(x%10+'0');}
il void print(const ll &x) {x<0?putchar('-'),write(~(x-1)):write(x);putchar('\n');}
il ll max(const ll &a,const ll &b){return a>b?a:b;}
il ll min(const ll &a,const ll &b){return a<b?a:b;}
char s[40];
int n;
const ll mod1=998244353,mod2=1e9+7,d=131;  
struct node
{
    ll x,y;
    bool operator==(const node &p)const{
        return x==p.x&&y==p.y;
    }
    ll operator %(const ll &p)const{
        return x*y%p;
    }
    node operator *(const node &p)const{
        return (node){x*p.x%mod1,y*p.y%mod2};
    }
    node operator +(const node &p)const{
        return (node){(x+p.x)%mod1,(y+p.y)%mod2};
    }
    node operator -(const node &p)const{
        return (node){(x-p.x+mod1)%mod1,(y-p.y+mod2)%mod2};
    }
}B,D;
struct hmap{
    static const int P=2e6+3,M=3e7+10;
    int hed[M],nxt[M],cnt;node val[M];ll as[M];
    bool count(node x){
        int c=hed[x%P];
        while(c){
            if(val[c]==x) return 1;
            c=nxt[c];
        }return 0;
    }
    ll& operator [](node x){
        int c=hed[x%P];
        while(c){
            if(val[c]==x) return as[c];
            c=nxt[c];
        }
        ++cnt;val[cnt]=x;nxt[cnt]=hed[x%P];hed[x%P]=cnt;
        return as[cnt];
    }
    int size(){return cnt;}
}f;
#define T pair<node,node> 
ll base[42],ans;
T solve(ll x){
    node l=(node){0,0},r=(node){0,0};
    for(ri i=0;i<n;++i){
        if(base[i]&x){
            l=l*D;
            l=l+(node){s[i],s[i]};
        }
    }
    for(ri i=n-1;~i;--i){
        if(!(base[i]&x)){
            r=r*D;
            r=r+(node){s[i],s[i]};
        }
    }
    return (T){l,r};
}
int main(){
    n=read();
    scanf("%s",s);
    D=B=(node){d,d};
    base[0]=1;
    for(ri i=1;i<=n;++i) B=B*D,base[i]=base[i-1]<<1;   
    for(ri i=0;i<base[n];++i){
        T now=solve(i);
        f[now.first*B-now.second]++;
    }
    for(ri i=0;i<n;++i)s[i]=s[n+i];
    for(ri i=0;i<base[n];++i){
        T now=solve(i);
        if(f.count(now.second*B-now.first))ans+=f[now.second*B-now.first];
    }
    print(ans);
    return 0;
}
```

---

## 作者：__KevinMZ__ (赞：2)

# [题解：AT\_agc026\_c \[AGC026C\] String Coloring](https://www.luogu.com.cn/problem/AT_agc_026_c)

## 感受

一道明显的折半搜索（meet in the middle）。

## 思路

暴力枚举 $\Theta(2^{2n})$，Time Limit Exeeded for you！

考虑折半搜索。

字符串砍半：$S=s_1+s_2(\mid\!s_1\!\mid=\mid\!s_2\!\mid)$

${s_1}_{red}+{s_2}_{red}={s_2}_{blue}+{s_1}_{blue}$（blue 反着存即可）

$\therefore({s_1}_{red},{s_2}_{red})=({s_2}_{blue},{s_1}_{blue})$

二分结束。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ONLINE_JUDGE
inline void read(int&k){
    int f=1;
    k=0;
    char ch=getchar();
    while(!isdigit(ch))(ch=='-'?f*=-1:f*=1),ch=getchar();
    while(isdigit(ch))k=(k<<3)+(k<<1),k+=ch-'0',ch=getchar();
    k*=f;
}
inline void write(int k){
    if(k<0)putchar('-'),k*=-1;
    if(k>=10)write(k/10);
    putchar(k%10+'0');
}
template<typename ...Args>
void read(int&t,Args&...args){
	read(t);
	read(args...);
}
template<typename ...Args>
void write(int&t,Args&...args){
	write(t);
	cout<<" ";
	write(args...);
}
inline int qpow(int x,int y,const int mod=-1){int ans=1;while(y){if(y&1)ans*=x;x*=x;if(mod!=-1)ans%=mod,x%=mod;y>>=1;}return ans;}
//↑陋习↑
int n,ans;
vector<pair<string,string>>lft,rgt;
string s;
void dfs(int l,int r,vector<pair<string,string>>&x,string red,string blue){//折半搜索
	if(l==r){
		x.push_back({red,blue});
		return;
	}
	dfs(l+1,r,x,red+s[l],blue);
	dfs(l+1,r,x,red,s[l]+blue);
	//红色从左到右，蓝色从右到左
} 
signed main(){
#ifndef ONLINE_JUDGE//随手调试好习惯
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
#endif
	cin>>n>>s;
	dfs(0,n,lft,"","");//前一半
	dfs(n,s.size(),rgt,"","");//后一半
	sort(rgt.begin(),rgt.end());
	for(auto i:lft){
		pair<string,string>j={i.second,i.first};
		ans+=upper_bound(rgt.begin(),rgt.end(),j)-lower_bound(rgt.begin(),rgt.end(),j);//计算对应个数
	}
	cout<<ans;
    return 0;
}

```

---

## 作者：ylch (赞：1)

来一发不用搜索的。

## 0x00 问题分析

涂色方案需满足红色字符串（从左到右）等于蓝色字符串（从右向左）。蓝色字符串从右向左读相当于将蓝色字符按原字符串的逆序排列。

考虑折半枚举（Meet in the Middle）：将字符串分成前后两半（各长 $n$），分别枚举前后两半的涂色方案，利用 map 存储前一半的结果，再匹配后一半的结果。

## 0x01 条件推导

前一半：红色子序列为 $A$，蓝色子序列为 $B$。

后一半：红色子序列为 $C$，蓝色子序列为 $D$。

条件要求 $A + C = \text{reverse}(D) + \text{reverse}(B)$。通过推导可知，等价于 $A = \text{reverse}(D)$ 且 $C = \text{reverse}(B)$。

## 0x02 实现思路

枚举前一半所有涂色方案，存储 $(A, B)$ 的出现次数。枚举后一半时，计算 $(\text{reverse}(D), \text{reverse}(C))$ 作为键，累加匹配的计数。

枚举前后两半各 $2^n$ 种方案，时间复杂度 $O(2^n \cdot n)$。

## 0x03 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	int n; string s; cin >> n >> s;
	string s1 = s.substr(0, n);
	string s2 = s.substr(n, n);
	
	map<pair<string, string>, ll> mp1;
	for(int bit = 0; bit < (1 << n); bit ++){
		string red1, blue1;
		for(int i = 0; i < n; i ++){
			if(bit & (1 << i)) red1 += s1[i];
			else blue1 += s1[i];
		}
		mp1[{red1, blue1}] ++;
	}
	
	ll ans = 0;
	for(int bit = 0; bit < (1 << n); bit ++){
		string red2, blue2;
		for(int i = 0; i < n; i ++){
			if(bit & (1 << i)) red2 += s2[i];
			else blue2 += s2[i];
		}
		string red = red2; reverse(red.begin(), red.end());
		string blue = blue2; reverse(blue.begin(), blue.end());
		
		auto key = make_pair(blue, red);
		if(mp1.find(key) != mp1.end()) ans += mp1[key];
	}
	
	cout << ans;
	return 0;
}
```

---

## 作者：never_knew (赞：1)

[不会折半搜索的点过来](https://blog.csdn.net/tanjunming2020/article/details/134107949)。

其实题目给了一个小暗示，就是字符串的长度是 $2\times n$。

如果直接爆搜时间复杂度是 $2^{18\times 2}$，铁超时。

但是我们先把前一半的所有可能都搜出来，并且存起来，搜完后一半后，看有多少种前面搜出来的字符串与它匹配。

这时 map 的作用就出现了。

[map](https://blog.csdn.net/weixin_41501074/article/details/114532738)。

map 可以把前面搜出的情况全部存起来，在追后统计的时候发挥重要的作用。

代码如下。

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
int cnt=0;
int n;
struct Stu
{
    string a,b;
    friend bool operator <(const Stu a1,const Stu id1)
	{
		if(a1.a!=id1.a)
		{
			return a1.a<id1.a;
		}
		else
		{
			return a1.b<id1.b;
		}
	}
};
map<Stu,int>mp;
void dfs(int x,string s1,string s2)
{
    if(x==n)
    {
        Stu qwq;
        qwq.a=s1;
        qwq.b=s2;
        mp[qwq]++;
        return;
    }
    dfs(x+1,s1+s[x],s2);
    dfs(x+1,s1,s2+s[x]);
}
int sum=0;
void dfs1(int x,string s1,string s2)
{
    if(x==s.size())
    {
        Stu qwq;
        qwq.a=s2;
        qwq.b=s1;
        sum+=mp[qwq];
        return;
    }
    dfs1(x+1,s[x]+s1,s2);
    dfs1(x+1,s1,s[x]+s2);
}
signed main()
{
    cin>>n>>s;
    dfs(0,"","");
    dfs1(n,"","");
    cout<<sum;
    return 0;
}
```

---

## 作者：Swirl (赞：1)

# 思路简述

本题有 $n \le 18$，考虑到经典搜索 $O(2^{2n})$ 会超时，不难想到 **折半搜索**（不会的童鞋出门左转 OI-wiki）。

那么设前半段的红、蓝色部分分别为：
$$
Lred、Lblue
$$
后半段为：
$$
Rred、Rblue
$$

根据题目要求，有：
$$
Lred + Rred = (Lblue + Rblue)^{\prime}
$$

其中一撇代表反转该字符串。

将其拆开，易得：
$$
Lred + Rred = Rblue^{\prime} + Lblue^{\prime}
$$

再根据题意，得：
$$
|Lred| + |Rred| = |Lblue| + |Rblue|
$$

根据我们的假设，得：
$$
|Lred| + |Lblue| = |Rred| + |Rblue|
$$

联立上述两方程，得：
$$
|Lred| = |Rblue|\\
|Rred| = |Lblue|
$$

最后，根据我们的两个结论，有：
$$
Lred = Rblue^{\prime}\\
Rred = Lblue^{\prime}
$$

据此，即可写出代码：

[code](https://atcoder.jp/contests/agc026/submissions/52945569)。

---

## 作者：Hhy140516 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_agc026_c)
# 题意
有一个长度是 $2n$ 的 $s$ 字符串，选 $n$ 个字符从左往右念和另一些没选的 $n$ 个字符串从右往左念一样，问有几种选法。
# 分析
$n$ 只有 $18$，考虑折半搜索。

如果你不了解折半搜索，[看这里](https://www.luogu.com.cn/problem/P1466)。

那么，搜索中，记录现在这边选的字符和没选的字符，存入容器。

搜索另一边时，发现如果相同，这边没选的字符就是另一边选的字符，这边选的字符就是另一边没选的字符。

因此，直接记录答案即可。
# 代码
```cpp
//Code by hhy
#include<bits/stdc++.h>
#define F(i , a , b , c) for( int i = (a) ; ((c > 0) ? i <= (b) : i >= (b)) ; i += c )
#define T(i , root , b , c) for( int i = root ; b ; c )
#define int long long
#define W(f) while(f)
#define ull unsigned long long
#define pb push_back
#define fi first
#define se second
#define ll long long
#define debug(...){\
	cout<<"debug in function "<<__FUNCTION__<<",line "<<__LINE__<<"\n";\
	string s=#__VA_ARGS__,s2="";\
	vector<string>v;\
	for(auto i:s){\
		if(i==','){\
			v.push_back(s2);\
			s2="";\
		}else{\
			s2+=i;\
		}\
	}\
	v.push_back(s2);\
	vector<int>v2={__VA_ARGS__};\
	for(int i=0;i<v.size()-1;i++){\
		cout<<v[i]<<"="<<v2[i]<<"\n";\
	}\
	cout<<v[v.size()-1]<<"="<<v2[v2.size()-1]<<"\n\n";\
}
using namespace std ;
const int kMaxN = 1e7 + 5 , kMaxM = 100005 , MOD = 998244353 , INF = 1e18 ;
struct Edgepr
{
	int u , w ;
};
struct Edgeve
{
	int v , w ;
};
struct node
{
  int x , y , id ;
}Node[kMaxN] ;
int n , cnt ;
string s ;
map<pair<string , string> , int> mp ; 
inline ll ksm(ll a , ll b)
{
	ll mul = 1 ;
	while(b)
	{
		if(b & 1) mul *= a , mul %= MOD ;
		a *= a ;
		a %= MOD ;
		b >>= 1 ;
	}
	return mul ;
}
inline int read()
{
    int x = 0 , f = 1 ;
    char ch = getchar() ;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1 ;
        ch = getchar() ;
    }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0' , ch = getchar() ;
    return x * f ;
}
void write(int x)
{
    if(x < 0) putchar('-') , x = -x ;
    if(x > 9) write(x / 10) ;
    putchar(x % 10 + '0') ;
}
void dfs_l(int step , string le , string ri)
{
	if(step > n / 2)
	{
		mp[make_pair(le , ri)]++ ; // 上文所说的容器
		return ;
	}
	dfs_l(step + 1 , le + s[step] , ri) ;
	dfs_l(step + 1 , le , s[step] + ri) ; // 因为是从右往左，所以添加在左边
}
void dfs_r(int step , string le , string ri)
{
	if(step > n)
	{
		cnt += mp[make_pair(ri , le)] ; // 反过来记录答案
		return ;
	}
	dfs_r(step + 1 , le + s[step] , ri) ;
	dfs_r(step + 1 , le , s[step] + ri) ; // 因为是从右往左，所以添加在左边
}
void Read()
{
	cin >> n ;
	cin >> s ;
	s = ' ' + s ; // 错位
}
void work()
{
  Read() ;
  n *= 2 ;
  // 折半
  dfs_l(1 , "" , "") ; // 前一半
	dfs_r(n / 2 + 1 , "" , "") ; // 后一半
	cout << cnt ;
}
signed main()
{
//	freopen(".in" , "r" , stdin) ;
//	freopen(".out" , "w" , stdout) ;
	ios::sync_with_stdio(0) , cin.tie(0) , cout.tie(0) ;
  int t = 1 ;
  // cin >> t ;
  while(t--) work() ;
  return 0 ;
}
```

---

## 作者：junee (赞：0)

# [AGC026C] String Coloring 题解

## 前置知识

折半搜索。

## 题目分析

首先直接爆搜做时间复杂度为 $O(2^{2n}2n)$，你会似掉，这是显然的。

但是如果题目告诉你 $n\le 18$ 说明你应该写一个 $O(2^n)$ 的东西。

然后你自己手玩一下发现，你把字符串分成两个长度为 $n$ 的字符串后要求你前半段的红串和后半段的蓝串的串形成回文串，前半段的蓝串和后半段红串形成回文串。

那么用哈希维护一下回文，将前半段的哈希值扔到 map 里面，后半段再去 map 里面匹配。

```
#include<iostream>
#include<iomanip>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
#include<chrono>
#include<map>
using namespace std;
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<ULL,ULL>PUL;
const int N=40,base=13331;
int n;
LL ans=0;
char a[N],b[N];
map<PUL,int>mp;
void dfs(int u,ULL hsh1,ULL hsh2,int f){
	if(u==n+1){
		if(f)ans+=mp[{hsh1,hsh2}];
		else mp[{hsh1,hsh2}]++;
		return;
	}
	dfs(u+1,hsh1*base+(f?b[u]:a[u]),hsh2,f);
	dfs(u+1,hsh1,hsh2*base+(f?b[u]:a[u]),f);
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i;i--)cin>>b[i];
	dfs(1,0,0,0);
	dfs(1,0,0,1);
	cout<<ans;
	return 0;
}

```

---

## 作者：Chillturtle (赞：0)

# 前置知识（折半搜索）

著名 OI 网站 OIWiki 上是这样介绍折半搜索的：

>Meet in the middle 算法的主要思想是将整个搜索过程分成两半，分别搜索，最后将两半的结果合并。

>暴力搜索的复杂度往往是指数级的，而改用 Meet in the middle 算法后复杂度的指数可以减半，即让复杂度从 $O(a^b)$ 降到 $O(a^{b \div 2})$。

# 题意

有一个长度为 $2 \times n$ 的字符串 $S$。我们可以把这个字符串的每一个字符染成红色或蓝色。

- 使从左到右读红色字符形成的字符串和从右到左读蓝色字符形成的字符串一样。

问有多少种染色方案可以使得上述条件成立。

# 思路

首先，看到 $1 \le n \le 18$ 我们进行简单分析得，如果进行暴力计算，那么时间复杂度将会是 $O(2^{36})$，明显超时。所以我们就可以考虑使用 Meet in the middle 算法将时间复杂度降到 $O(2^{18})$。

Meet in the middle 算法是基于我们需要将原数据分成两个部分来算的。怎么分？题目说，有红蓝两个颜色的字符串，那么我们不妨将整个字符串红蓝两部分，并且将红蓝两个字符串再次分成两部分，用折半搜索跑。

此处我们设前半段红色为 $red_1$，后半段红色为 $red_2$。前半段蓝色为 $blue_1$，后半段蓝色为 $blue_2$。

首先，由题目得：

$$
|red_1| + |red_2| = |blue_1| + |blue_2| = n
$$

且：

$$
|red_1| + |blue_1| = |red_2| + |blue_2| = n
$$

由上两个式子可得：

$$
|red_2| = |blue_1|
$$
并且：

$$
|red_1| = |blue_2|
$$

推到现在，我们可以再次看一眼题目。可以再得到一个式子：

$$
(red_1 + red_2) = (blue_1 + blue_2)'
$$

我们把两个式子结合一下就可以得到我们最后想要的东西：

$$
red_2 = (blue_1)'
$$

且：

$$
red_1 = (blue_2)'
$$

说直白一点就是**前半段的红串是后半段的蓝串的反串，前半段的蓝串是后半段红串的反串**。

现在我们就可以用 map 和 hash 进行折半搜索了。此处因为数据不太大，所以我的 hash 所用质数用的是 $233$。

# AC code
```cpp
#include<bits/stdc++.h>
#define int long long
const int hsh=233;
using namespace std;
map<pair<int,int>,int> mp;
int n,ans;
string s[2];
void dfs(int k,int red,int blue,bool flag){
	if(k>n){
		if(flag==1){
			ans+=mp[{red,blue}];
		}else{
			mp[{red,blue}]++;
		}
		return;
	}
	dfs(k+1,red*hsh+s[flag][k-1],blue,flag);
	dfs(k+1,red,blue*hsh+s[flag][k-1],flag);
}
signed main(){
	cin>>n;
	cin>>s[0];
	s[1]=s[0].substr(n,n);
	reverse(s[1].begin(),s[1].end());
	s[0]=s[0].substr(0,n);
	dfs(1,0,0,0);
	dfs(1,0,0,1);
	cout<<ans<<endl;
return 0;
}
```


注：此篇题解有借鉴 [Hadtsti](https://www.luogu.com.cn/user/333675) 的 [题解](https://www.luogu.com.cn/article/7ndcqvfz)，在此膜拜大佬。

---

## 作者：Vindictae (赞：0)

# 题目大意
一个字符串，分成两个，求第一个正序读和第二个倒序读相同的情况有多少种。
# 题目思路
看到大家都用的折半搜索，我来用一个不一样的。  
先用一个 map 将分成的两个字符串所有可能的情况有多少个存起来，然后把所有满足题意的情况求出来，将答案加上 map 中存的当前两个字符串的个数即可。  
在这里用了一个小技巧，希望大家能看懂，就是要求一个 01 串的所有情况，直接枚举十进制数，转化为二进制数即可。
# AC Code
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f

using namespace std;

int n, k, ans;
string s, a, b;
map<string, map<string, int>> mp;

void init() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}

signed main() {
	init();
    cin >> n >> s;

    for (int i = 0; i < (1 << n); ++ i) {
        a = "";
        b = "";

        for (int j = 0; j < n; ++ j) {
            if ((i >> j) & 1) {
                a += s[j];
            } else {
                b += s[j];
            }
        }

        ++ mp[a][b];
    }

    for (int i = 0; i < (1 << n); ++ i) {
        a = "";
        b = "";

        for (int j = 0; j < n; ++ j) {
            if ((i >> j) & 1) {
                a += s[2 * n - 1 - j];
            } else {
                b += s[2 * n - 1 - j];
            }
        }

        ans += mp[a][b];
    }

    cout << ans;
    return 0;
}
```

---

