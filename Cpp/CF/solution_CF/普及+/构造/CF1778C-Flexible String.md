# Flexible String

## 题目描述

You have a string $ a $ and a string $ b $ . Both of the strings have length $ n $ . There are at most $ 10 $ different characters in the string $ a $ . You also have a set $ Q $ . Initially, the set $ Q $ is empty. You can apply the following operation on the string $ a $ any number of times:

- Choose an index $ i $ ( $ 1\leq i \leq n $ ) and a lowercase English letter $ c $ . Add $ a_i $ to the set $ Q $ and then replace $ a_i $ with $ c $ .

For example, Let the string $ a $ be " $ \tt{abecca} $ ". We can do the following operations:

- In the first operation, if you choose $ i = 3 $ and $ c = \tt{x} $ , the character $ a_3 = \tt{e} $ will be added to the set $ Q $ . So, the set $ Q $ will be $ \{\tt{e}\} $ , and the string $ a $ will be " $ \tt{ab\underline{x}cca} $ ".
- In the second operation, if you choose $ i = 6 $ and $ c = \tt{s} $ , the character $ a_6 = \tt{a} $ will be added to the set $ Q $ . So, the set $ Q $ will be $ \{\tt{e}, \tt{a}\} $ , and the string $ a $ will be " $ \tt{abxcc\underline{s}} $ ".

You can apply any number of operations on $ a $ , but in the end, the set $ Q $ should contain at most $ k $ different characters. Under this constraint, you have to maximize the number of integer pairs $ (l, r) $ ( $ 1\leq l\leq r \leq n $ ) such that $ a[l,r] = b[l,r] $ . Here, $ s[l,r] $ means the substring of string $ s $ starting at index $ l $ (inclusively) and ending at index $ r $ (inclusively).

## 说明/提示

In the first case, we can select index $ i = 3 $ and replace it with character $ c = \tt{d} $ . All possible pairs $ (l,r) $ will be valid.

In the second case, we can't perform any operation. The $ 3 $ valid pairs $ (l,r) $ are:

1. $ a[1,1] = b[1,1] = $ " $ \tt{a} $ ",
2. $ a[1,2] = b[1,2] = $ " $ \tt{ab} $ ",
3. $ a[2,2] = b[2,2] = $ " $ \tt{b} $ ".

In the third case, we can choose index $ 2 $ and index $ 3 $ and replace them with the characters $ \tt{c} $ and $ \tt{d} $ respectively. The final set $ Q $ will be $ \{\tt{b}\} $ having size $ 1 $ that satisfies the value of $ k $ . All possible pairs $ (l,r) $ will be valid.

## 样例 #1

### 输入

```
6
3 1
abc
abd
3 0
abc
abd
3 1
xbb
xcd
4 1
abcd
axcb
3 10
abc
abd
10 3
lkwhbahuqa
qoiujoncjb```

### 输出

```
6
3
6
6
6
11```

# 题解

## 作者：_acat_ (赞：2)

## Sol

注意到如果能满足条件进行操作后使得 $a_{l,r}=b_{l,r}$，设 $len=r-l+1$, 则会产生 $len \times (len+1) \div 2$ 种二元组。

因此，对于左端点 $l$，找到能满足条件的尽可能大的端点 $r$，则可进行计算。

然而取枚举 $l$ 和 $r$ 时间复杂度 $O(n^2)$，会 TLE。

注意到 $k \le 10$ 且 $a$ 串最多有 $10$ 个不同字母，因此往集合 $Q$ 里放最多 $10$ 个。
因此我们可以转而去考虑 $a$ 的不同字母的情况, 假设个数为 $num$。

又注意到往集合里放的不同字母越多对答案贡献更优，因此可以尽可能多放，$k=\min(k, num)$。

利用 dfs 去搜索使用了 $num$ 个里的多少个。

设 `dfs(pos,cnt)` 表示到了 $num$ 个不同字母的第 $pos$ 个，且往集合 $Q$ 里放了 $cnt$ 个不同的情况。

则有: 第 $pos$ 个不用，则 `dfs(pos+1,cnt)`。 否则如果用，则  `dfs(pos+1,cnt+1)`，并打标记。

当 $pos$ 与 $num$ 相等时，我们可以计算方案数。

此时扫描字符串 $a$, 将 $a$ 分成一段一段，每段与 $b$ 相等或者在已经标记使用的情况下，算出这段长度 $len$, 则该段对答案贡献为 $\binom{len}{2}$。

## Code
```cpp
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define RFOR(i,a,b) for(int i=(a);i>=(b);i--)
typedef long long ll;
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}
const int N=1e6+5;
int t,n,k,num;
ll ans;
string a,b;
char valid[30];
bool vis[30];
int c[30];
ll cal(){
	ll res,cnt;
	res=cnt=0;
	for(int i=0;i<n;i++){
		if(a[i]==b[i]||vis[a[i]-'a']) cnt++;
		else{
			res+=cnt*(cnt+1)/2;
			cnt=0;
		}
	}
	res+=cnt*(cnt+1)/2;
	return res;
}
void solve(int pos,int cnt){
	if(cnt>k) return;
	if(pos==num){
		if(cnt==k) ans=max(ans,cal());
		return;
	}
	solve(pos+1,cnt);
	vis[valid[pos]-'a']=1;
	solve(pos+1,cnt+1);
	vis[valid[pos]-'a']=0;
	
}
int main(){
	t=read();
	while(t--){
		n=read(),k=read();
		cin>>a>>b;
		memset(c,0,sizeof c);
		num=0;
		for(int i=0;i<n;i++) c[a[i]-'a']++;
		for(int i=0;i<=25;i++){
			if(c[i]){
				valid[num]=i+'a';
				num++;
			}
		}
		k=min(k,num);
		ans=0;
		memset(vis,0,sizeof vis);
		solve(0,0);
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：ningago (赞：2)

首先 $k\leq 10$ 肯定是突破口。

对于同一字符 $c$，如果要修改它，最优的方案肯定是对于所有 $a_i=c$，将 $a_i$ 替换为 $b_i$。

所以考虑枚举 $a$ 中每种颜色是否修改。限制即为修改字符种类数不超过 $k$。

使用 bitset 维护每种颜色的出现位置。

枚举后求出答案即可，注意判断原本就 $a_i=b_i$ 的位置。

时间复杂度 $O(n\cdot 2^k)$。

然后严峻的问题出现了，bitset 没有 resize 函数，导致多测让时间复杂度变得不稳定。这里的解决方案是手写 bitset。

```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>

#define N 100010

int T;
int n,K;
int id[30],idx;
struct botset
{
	bool c[N];
	int sz;
	void resize(int sz_)
	{
		sz = sz_;
	}
	void reset()
	{
		for(int i = 0;i <= sz + 1;i++)
			c[i] = 0;
	}
	void set(int i)
	{
		c[i] = i;
	}
	void operator |= (const botset &B)
	{
		for(int i = 1;i <= sz;i++)
			c[i] |= B.c[i];
	}
	void operator = (const botset &B)
	{
		for(int i = 1;i <= sz;i++)
			c[i] = B.c[i];
	}
	bool operator [](const unsigned &i)
	{
		return c[i];
	}
};

botset bs[30],tmp,now;
char a[N],b[N];

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&K);
		idx = 0;
		for(int i = 1;i <= 26;i++)
		{
			id[i] = 0;
			bs[i].resize(n + 4);
			bs[i].reset();
		}
		tmp.resize(n + 4);
		tmp.reset();
		now.resize(n + 4);
		scanf("%s%s",a + 1,b + 1);
		for(int i = 1;i <= n;i++)
		{
			if(a[i] == b[i])
				tmp.set(i);
			else
			{
				if(!id[a[i] - 'a' + 1])
					id[a[i] - 'a' + 1] = ++idx;
				bs[id[a[i] - 'a' + 1]].set(i);
			}
		}
		long long ans = 0;
		for(int t = 0;t < (1 << idx);t++)
		{
			int cnt = 0;
			for(int i = 1;i <= idx;i++)
			{
				if((1 << (i - 1)) & t)
					cnt++;
			}
			if(cnt > K)
				continue;
			now = tmp;
			for(int i = 1;i <= idx;i++)
			{
				if((1 << (i - 1)) & t)
				{
					now |= bs[i];
				}
			}
			int last = 0;
			long long res = 0;
			for(int i = 1;i <= n + 1;i++)
			{
				if(!now[i])
				{
					if(last)
					{
						int p = i - 1;
						int len = p - last + 1;
						res += 1ll * len * (len + 1) / 2ll;
					}
					last = 0;
				}
				else if(!last)
					last = i;
			}
			ans = std::max(ans,res);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：_Z_F_R_ (赞：1)

因为 $a$ 最多包含 $10$ 个不同的字符，$k \le 10$，可以考虑暴力枚举。
***
### 1. 枚举的方法

容易发现，若 $a_i = b_i$，肯定不会改 $a_i$，但在这里必要时我们可以**视为将其改动**，只不过 $c = a_i$。

对于这最多 $10$ 个字母可以暴力 DFS 枚举它是否在集合 $Q$ 中，若在，改变字符串。设他们的下标为 $k_1,k_2,k_3, \dots ,k_{m - 1},k_m$，执行 $\forall i = [1,m],a_{k_i} = b_{k_i}$。然后根据这个字符串求解，取最大值即可。

### 2. 字符串求解

因为 $b$ 不会改变，所以我们可以把 $a$ 抽象成一个长度为 $|a|$ 的数组 $d$，若 $a_i = b_i$，$d_i$ 为 $1$，否则为 $0$。

不难发现，若 $\forall i = [l,r],d_i = 1$，则 $l \le i \le j \le r$ 时，$a[i,j] = b[i,j]$，答案个数为 $\dfrac{(r - l + 1)\cdot(r - l + 2)}{2}$，遍历一遍 $d$ 数组，遇到全为 $1$ 的区间就计数，时间复杂度 $O(|a|)$。

### 3. 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,k,re_size;
long long maxans = 0;

map<char,vector<int>>represent_t;
vector<vector<int>>represent;
vector<bool> transform(string a,string b)//将 a 转化为一个 bool 类型的数组。
{
    vector<bool>ans;
    int i;
    for(i = 0;i < a.size();i++)
        ans.push_back(a[i] == b[i]);
    return ans;
}
void Init(string s)//取 a 每一个不同字母的位置，同时为了方便将其变成 vector<vector<int>> 类型。
{
    represent_t.clear();
    represent.clear();
    int i;
    for(i = 0;i < s.size();i++)
        represent_t[s[i]].push_back(i);
    represent.push_back(vector<int>());
    for(auto it : represent_t)
        represent.push_back(it.second);
    re_size = represent.size() - 1;
}
vector<bool> change(vector<bool> old,vector<int> insert)//若 x 在集合 Q 中，改变原数组中所有字符为 x 的值。
{
    int i;
    for(i = 0;i < insert.size();i++)
        old[insert[i]] = true;
    return old;
}
long long ans_check(vector<bool> now)//求解
{
    long long ans = 0,i,j;
    for(i = 0;i < now.size();i++)
    {
        if(now[i])
        {
            for(j = i;j < now.size() && now[j];j++) ;
            ans += (j - i) * (j - i + 1) / 2;
            i = j;
        }
    }
    return ans;
}
void dfs(int nowi,int res,vector<bool> now)
{
    int i;
    if(nowi > n)//下标越界
        return ;
    maxans = max(ans_check(now),maxans);
    if(res == 0)//没有改变的机会
        return ;
    for(i = nowi + 1;i <= re_size;i++)//枚举
        dfs(i,res - 1,change(now,represent[i]));
}
int main()
{
    int t;
    string a,b;
    cin >> t;
    while(t--)
    {
        maxans = 0;
        cin >> n >> k >> a >> b;
        Init(a);
        dfs(0,k,transform(a,b));
        cout << maxans << endl;
    }
}
```

---

## 作者：SuperCowHorse (赞：1)

>There is **at most 10 different characters** in the string a.

题目提示得这么明显：$a$ 最多只有 $10$ 个不同的字母。那岂不是提示我们：这题就~~暴力~~？

~~你说得对。~~

考虑枚举 $k$ 个不同的字母，在 $\operatorname{dfs}$ 中，更新 $ans$。

如何进行更新呢？

由于集合中的字母可以随便改，那么就直接把 $a_i$ 改成 $b_i$ 即可，这样收益最大。

那怎么计算区间总和呢？

玩过数三角形吗？与数三角形一样的策略，设有连续的一段 $[l,r]$，长度为 $k$，且对于任意 $l\le i\le r$，都有 $a_i=b_i$，那么这个区间的答案就是：$\dfrac{(k+1)\times k}2$。

另：在这里，$\operatorname{dfs}$ 需要一点优化。由于不需要考虑字母的顺序，那么不需要进行**排列**，可以进行组合数的优化：$\operatorname{dfs}$ 中传参，枚举时从这个参数开始枚举。

``` cpp
inline ll o(){//计算当前 ans
	for(int i=1;i<=n;++i)
		s[i]=a[i];
	for(int i=1;i<=n;++i){//更新字符串数组
		if(s[i]==b[i]) continue;
		if(vis[s[i]-'a'])
			s[i]=b[i];
	}
	int now=0;ll res=0;
	for(int i=1;i<=n;++i){//计算 ans
		if(s[i]==b[i]) ++now;
		else{
			res+=1ll*(now+1)*now/2;
			now=0;
		}
	}
	res+=1ll*(now+1)*now/2;
	return res;
}
inline void dfs(int x,int y){
	if(y>k) return;
	if(y==k){
		ans=max(ans,o());
		return;
	}
	for(int i=x+1;i<=cnt;++i){
		if(!vis[f[i]-'a']){
			vis[f[i]-'a']=1;//统计
			dfs(i,y+1);//下一次从i+1开始枚举
			vis[f[i]-'a']=0;
		}
	}
}
```
Code:[link](https://codeforces.com/contest/1778/submission/191580135)

---

## 作者：luogu_gza (赞：0)

逛了一圈题解区，发现都很长，为了造福人民，我写了这篇题解。

考虑离散化 $a$ 后就是一个简单的枚举了。

枚举每一个字母是否“改变”。

复杂度是 $O(2^k \times \sum n)$。


具体见代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pc putchar
#define R read()
#define fo(i,a,b) for(register int i=a;i<=b;i++)
#define rep(i,a,b) for(register int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
int read()
{
    int x=0;
    char ch=getchar();
    bool f=0;
    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f) x=-x;
    return x;                                       
}
template<typename T> inline void write(T x)
{
    if(x<0)
    {
        pc('-');
        x=-x;
    }
    if(x>9) write(x/10);
    pc(x%10+'0');
}
int qmi(int a,int b,int p)
{
    int res=1;
    while(b)
    {
        if(b&1) res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
const int N=1e5+10;
int T,n,k;
char A[N],B[N];
int a[N],b[N];
map<int,int> ma;
signed main(){
    T=R;
    while(T--)
    {
        ma.clear();
        n=R,k=R;
        scanf("%s%s",A+1,B+1);
        int cnt=0;//离散化最大坐标
        fo(i,1,n) if(!ma.count(A[i])) ma[A[i]]=cnt++;//我使用map进行了离散化
        fo(i,1,n) a[i]=ma[A[i]];//离散化字符串
        int res=0;
        fo(st,0,(1<<cnt)-1) if(__builtin_popcount(st)<=k)//枚举“改变”的字符，并判断是否符合题意<=k个
        {
            int nowlen=0,ans=0;
            fo(i,1,n)   
                if(A[i]==B[i]||(st>>a[i]&1)) nowlen++;//统计当前符合题意的区间的长度
                else
                {
                    ans+=nowlen*(nowlen+1)/2;//该区间对于答案的贡献
                    nowlen=0;
                }
            ans+=nowlen*(nowlen+1)/2;
            nowlen=0;
            res=max(res,ans);//简单的取一个max
        }
        write(res),puts("");
    }
}
```

---

## 作者：loser_seele (赞：0)

首先题目的最多 $ k $ 个元素等价于恰好 $ k $ 个元素，因为多出来的元素显然不影响答案。

注意到 $ a $ 中最多只有 $ 10 $ 个不同的字符这个重要的限制，启发我们可以暴力。

设 $ a $ 的字符集为 $ S $，枚举出所有大小为 $ \min(k,\left| S \right|) $ 的子集，然后对于每种情况将在子集内的元素修改为 $ b $，别的元素不变，这样的贪心显然不会更劣，对于每种情况计算答案之后取最大值即可。

计算题目中的答案可以双指针，每次找到一个极长合法区间之后设区间长度为 $ len $，则答案累加 $ \frac{(len+1)(len)}{2} $。

这个时间复杂度并不好算，但是原问题等价于从 $ n \leq 10 $ 个元素中选取 $ k $ 个，方案数是 $ C_n^k $，由二项式系数的性质可知最大值为 $ C_{10}^5=252 $，于是总时间复杂度为 $ \mathcal{O}(a \sum n) $，其中 $ a \leq 252 $ 为方案数，可以通过。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-'){f=-1;}ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}
    return x*f;
}
const ll N=2e5+10;
ll n,k,d[N],tt;
string s,t;
vector<ll> v[30];
bool ok[N],b[N];
void solve()
{
	cin>>n>>k;
	cin>>s>>t;
	tt=0;
	for(ll i=0;i<26;i++) 
	v[i].clear();
	for(ll i=1;i<=n;i++)
	{
		if(s[i-1]==t[i-1]) 
		ok[i]=1;
		else 
		ok[i]=0;
		v[s[i-1]-'a'].push_back(i);
		d[++tt]=s[i-1]-'a';
	}
	sort(d+1,d+tt+1);
	ll kk=1;
	for(ll i=2;i<=tt;i++)
		if(d[i]!=d[kk]) 
		d[++kk]=d[i];
	tt=kk;k=min(k,tt);ll ans=0;
	for(ll i=0;i<(1<<tt);i++)
	{
		ll cnt=0;
		for(ll j=0;j<tt;j++)
			if(i&(1<<j)) 
			cnt++;
		if(cnt!=k) 
		continue;
		for(ll j=1;j<=n;j++) 
		b[j]=ok[j];
		for(ll j=0;j<tt;j++)
		{
			if(i&(1<<j))
			{
				for(ll p=0;p<v[d[j+1]].size();p++)
				{
					ll vv=v[d[j+1]][p];
					b[vv]=1;
				}
			}
		}
		ll len=0,res=0;
		for(ll j=1;j<=n;j++)
		{
			if(b[j]) 
			len++;
			else 
			res+=len*(len+1)/2,len=0;
		}
		res+=len*(len+1)/2,ans=max(ans,res);
	}
	cout<<ans<<endl;
}
int main()
{
	ll T=read();
	while(T--) 
	solve();
}
```


---

## 作者：yuanruiqi (赞：0)

## 题意简述

给定由小写字母构成的字符串 $a,b$，可以任意更改 $a$ 中的字母，但是 $a$ 中被更改的字母最多只能有 $k$ 种不同的字母，求出 $a$ 与 $b$ 相同位置且相同的子串的数量的最大值。

## 题目分析

字符串 $a$ 中最多只有 10 种字母。所以可以枚举每一个字母是否被更改。$O(2^{10}n)$ 符合题目要求。实际上符合条件枚举量达不到 $2^{10}$。 

## 代码

```cpp
#include <iostream>
#include <algorithm>
#include <bitset>
#include <vector>
#include <string>
using namespace std;
void solve()
{
    int n, k;
    cin >> n >> k;
    string a, b;
    cin >> a >> b;
    bitset<256> vis;
    vector<int> len(n+1);
    for (int i=0;i<n;++i)
        vis[a[i]] = 1;
    vector<char> q;
    for (int i=vis._Find_first();i<256;i=vis._Find_next(i))
        q.push_back(i);
    long long ans = 0;
    for (int i=0;i<(1<<q.size());++i)
        if (__builtin_popcount(i) == k || (i == ((1 << q.size()) - 1) && k >= q.size()))
        {
            string c = a;
            for (int j=0;j<q.size();++j)
                if ((i>>j)&1)
                    for (int k=0;k<n;++k)
                        if (c[k] == q[j])
                            c[k] = b[k];
            for (int i=0;i<n;++i)
                if (i == 0 || c[i] != b[i])
                    len[i] = c[i] == b[i];
                else len[i] = len[i-1] + 1;
            long long as = 0;
            for (int i=0;i<n;++i)
                as += len[i];
            ans = max(ans, as);
        }
    cout << ans << '\n';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
```


---

## 作者：3a51_ (赞：0)

注意到 $a$ 中最多只有 $10$ 个不同字符，所以可以考虑爆搜。

考虑对于这 $\le 10$ 种不同字符，每一种也就是放进集合 $Q$ 或者不放 $2$ 种可能，所以直接暴力。

问题就剩下计算了。不难发现如果 $a,b$ 下标相同的一段长度为 $k$ 的区间相等，则其中选择两个端点 $(l,r)$ 的情况数为 $\binom k2$，于是扫一遍计算就解决了。

叉人的时候看见了一个神奇 dp，差点以为搜会超时，算了一下复杂度也就 $O(2^p\times n)$（$p$ 是不同字符种类的数量，为 $10$），问题不大。

赛时代码：[Link](https://codeforces.com/contest/1778/submission/191576083)

---

