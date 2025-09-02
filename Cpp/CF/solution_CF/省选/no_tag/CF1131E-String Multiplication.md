# String Multiplication

## 题目描述

Roman 和 Denis 正在前往编程比赛的旅途中。由于旅途漫长，他们很快就感到无聊，于是决定想点新花样。Roman 发明了一种披萨的做法，而 Denis 则发明了一种字符串乘法。根据 Denis 的定义，长度为 $m$ 的字符串 $s$ 与字符串 $t$ 的乘积（即 $s \cdot t$）是一个新字符串，其形式为 $t + s_1 + t + s_2 + \ldots + t + s_m + t$，其中 $s_i$ 表示字符串 $s$ 的第 $i$ 个字符，"+" 表示字符串拼接。例如，字符串 "abc" 和 "de" 的乘积为 "deadebdecde"，而字符串 "ab" 和 "z" 的乘积为 "zazbz"。注意，与数字的乘法不同，字符串 $s$ 与 $t$ 的乘积不一定等于 $t$ 与 $s$ 的乘积。

Roman 对 Denis 的这个有趣操作感到有些嫉妒，于是他也想发明点与字符串相关的东西。Roman 是个美感爱好者，他定义字符串的“美丽值”为其中只包含同一个字母的最长连续子串的长度。例如，字符串 "xayyaaabca" 的美丽值为 $3$，因为有子串 "aaa"；而字符串 "qwerqwer" 的美丽值为 $1$，因为其中所有相邻字符都不相同。

为了娱乐 Roman，Denis 在纸上写下了 $n$ 个字符串 $p_1, p_2, p_3, \ldots, p_n$，并让 Roman 计算字符串 $((\ldots(((p_1 \cdot p_2) \cdot p_3) \cdot \ldots ) \cdot p_n)$ 的美丽值（其中 $s \cdot t$ 表示字符串 $s$ 与 $t$ 的乘积）。Roman 还没完全理解 Denis 的字符串乘法，于是向你寻求帮助。Denis 知道 Roman 很容易被震撼，他保证最终结果的美丽值不会超过 $10^9$。

## 说明/提示

在第一个样例中，字符串的乘积为 "abaaaba"。

在第二个样例中，字符串的乘积为 "abanana"。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
a
b
a
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2
bnn
a
```

### 输出

```
1
```

# 题解

## 作者：Lynkcat (赞：8)

这里给一个不太一样的做法，这种做法与字符具体是什么无关。目前是 cf 上最快解。

这个做法源自我看错了题，我将 $s$ 和 $t$ 看反了，导致 $s \times t$ 被我错误理解成 $s+t_1+s+t_2+……+t_{len}+s$。

考虑如果是这个形式怎么做，显然我们只要记录当前 $s$ 这个串如下的信息：是否全部相等，最左边的字符及前缀最长相同段长度，最右边的字符及后缀最长相同段长度。然后在乘上一个字符串时维护一下就行。做法十分简单，且与字符是什么无关。

但题目里并不是这种形式，这怎么办呢。然后你仔细想一想，发现把输入的字符串倒序做一遍如上的乘积等价于原题。然后就做完了。时间复杂度和空间复杂度均为线性。

```c++
//The Hunting Party - Keys To The Kingdom
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define ll long long
#define mp make_pair
#define pa pair < int,int >
#define fi first
#define se second
#define inf 1e18
#define mod 998244353
#define int ll
#define N 100005
using namespace std;
inline char gc(){static char buf[1000000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n;
string b[N],nowst,st,NOW;
void LYC_music()
{
	IOS;
	cin>>n;
	int ans=0;
	int sx=0,x=0,y=0,sy=0,allsm=1,lst=0;
	for (int i=1;i<=n;i++) cin>>b[i];
	nowst=b[n];
	for (int i=1;i<nowst.length();i++)
	{
		if (nowst[i]!=nowst[0]) allsm=0;
		if (nowst[i]!=nowst[i-1])
		{
			ans=max(ans,i-lst);
			if (lst==0) x=i;
			lst=i;
		}
	}
	if (allsm) ans=nowst.length(),x=y=ans;
	else ans=max(ans,max(x,y));
	y=nowst.length()-lst;
	sx=nowst[0];
	sy=nowst.back();
	ans=max(ans,(int)nowst.length()-lst);
	for (int i=n-1;i>=1;i--)
	{
		st=b[i];
		if (allsm)
		{
			allsm&=(st[0]==sx);
			for (int j=1;j<st.length();j++)
			{
				allsm&=(st[j]==st[0]);
			}
			if (allsm) x=y=st.length()*x+x+st.length(),ans=max(ans,x);
			else
			{
				int X=0,Y=0;
				for (int j=0;j<st.length();j++)
				{
					if (st[j]!=sx)
					{
						X+=x;
						break;
					}
					X+=x;
					X+=1;
				}
				for (int j=st.length()-1;j>=0;j--)
				{
					if (st[j]!=sx)
					{
						Y+=x;
						break;
					}
					Y+=x;
					Y+=1;
				}
				int lst=0;
				for (int i=0;i<st.length();i++)
				{
					lst+=x;
					ans=max(ans,lst);
					if (st[i]==sx)
					{
						lst+=1;
					} else lst=0;
				}
				ans=max(ans,lst+x);
				x=X,y=Y;
				ans=max(ans,max(x,y));
			}
		} else
		{
			for (int j=0;j<st.length();j++)
			{
				if (st[j]==sy&&st[j]==sx)
				{
					ans=max(ans,x+y+1);
				} else
				if (st[j]==sy)
				{
					ans=max(ans,y+1);
				} else 
				if (st[j]==sx)
					ans=max(ans,x+1);
			}
		}
	}
	cout<<ans<<endl;			
}
signed main()
{
	int T=1;
	while (T--)
	{
		LYC_music();
	}
}
/*
*/
```


---

## 作者：LJC00118 (赞：4)

对于每个字母分类讨论，设当前字母为 $ c $，上一次操作连续的 $ c $ 的个数的最大值为 $ maxn $

现在有一个新的字符串 $ str $，它的长度为 $ len $, $ left $ 和 $ right $ 分别表示在 $ str $ 最左边和最右边的 $ c $ 的连续个数，$ mid $ 表示连续的 $ c $ 的个数的最大值

- 如果 $ str $ 的每个字符都是 $ c $，那么新的 $ maxn $ 就是 $ maxn + (maxn + 1) * len $
- 如果 $ str $ 中有别的字符且 $ maxn != 0 $， $ maxn = max(mid, left + right + 1) $
- 如果 $ str $ 中有别的字符且 $ maxn == 0 $，$ maxn = mid $

最后取个 $ max $ 即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 100005;

string p[N];
int n, ans, maxn;

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    for(register int i = 1; i <= n; i++) cin >> p[i];
    for(char c = 'a'; c <= 'z'; c++) {
        maxn = 0;
        for(register int i = 1; i <= n; i++) {
            bool ok = 1;
            for(register unsigned j = 0; j < p[i].size(); j++) {
                if(p[i][j] != c) {
                    ok = 0;
                    break;
                }
            }
            int left = 0, mid = 0, right = 0, now = 0;
            for(register unsigned j = 0; j < p[i].size(); j++) {
                if(p[i][j] == c) ++now;
                else now = 0;
                mid = max(mid, now);
            }
            for(register unsigned j = 0; j < p[i].size(); j++) {
                if(p[i][j] == c) ++left;
                else break;
            }
            for(register unsigned j = p[i].size() - 1; j >= 0; j--) {
                if(p[i][j] == c) ++right;
                else break;
            }
            ll new_ans = 0;
            if(ok) {
                new_ans = maxn + 1ll * (maxn + 1) * mid;
            } else if(maxn) {
                new_ans = max(mid, left + right + 1);
            } else new_ans = mid;
            if(new_ans > (int)1e9) new_ans = (int)1e9;
            maxn = new_ans;
        }
        ans = max(ans, maxn);
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：AThousandSuns (赞：1)

在我的博客上看效果更佳：[点这里](https://www.cnblogs.com/1000Suns/p/10424675.html)

---
官方题解讲的很复杂，但看起来也就是个暴力大模拟，跟我的做法差不多。

为叙述方便，令 $P_i=((p_1p_2)p_3)\dots p_i$。

我们现在考虑如何从 $P_{i-1}$ 转移到 $P_i$。

对于每个 $P_i$，我们维护 $s[i][c]$ 表示 $P_i$ 中最长的连续 $c$ 的长度。

先不考虑乘法，将 $s[i][c]$ 设为 $p_i$ 中的连续长度。

定义 $lc$ 为 $p_i$ 最长的连续字母前缀，$rc$ 为最长的连续字母后缀。

首先如果 $p_i$ 的首尾字母不相同，那么 $s[i][{p_i}_1]$ 就可以从 $lc+[P_{i-1}\text{中出现过}{p_i}_1]$ 更新（接在原来字符的后面组成）。$s[i][{p_i}_{|p_i|}]$ 同理。

否则如果 $p_i$ 不由相同字母构成，那么：
- 如果 $P_i$ 中出现过 ${p_i}_1$，$s[i][{p_i}_1]$ 就可以从 $lc+rc+1$ 更新。（前缀接在这个字符后面，前一个后缀接在这个字符前面）
- 否则，$s[i][{p_i}_1]$ 就可以从 $\max(lc,rc)$ 更新，这不会更优，可以省略。
否则，就可以把 $s[i-1][{p_i}_1]$ 个 ${p_i}_1$ 拿出来，前后接上 $p_i$，那么 $s[i][{p_i}_1]$ 就可以从 $|p_i|(s[i-1][{p_i}_1]+1)+s[i-1][{p_i}_1]$ 更新。

注意最后 $P_{i-1}$ 会被拆成一个个字符，他们对 $s[i]$ 的贡献就是每个字符有没有出现过，而不是出现次数。

最后所有 $s[n][c]$ 的最大值就是答案。

时间复杂度 $O(\sum |p_i|)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=100010;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline int read(){
    char ch=getchar();int x=0,f=0;
    while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
    while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    return f?-x:x;
}
int n,cont[100010][26],s[26];
char str[maxn];
inline void chkmax(int &x,int y){
    if(y>x) x=y;
}
int main(){
    n=read();
    FOR(nn,1,n){
        scanf("%s",str+1);
        int len=strlen(str+1);
        int cnt=1;
        FOR(i,1,len)
            if(str[i]!=str[i+1]){
                chkmax(cont[nn][str[i]-'a'],cnt);
                cnt=1;
            }
            else cnt++;
        int lcnt=1,rcnt=1;
        FOR(i,2,len){
            if(str[i]==str[1]) lcnt++;
            else break;
        }
        ROF(i,len-1,1){
            if(str[i]==str[len]) rcnt++;
            else break;
        }
        if(nn!=1){
            if(lcnt==len && rcnt==len) chkmax(cont[nn][str[1]-'a'],len*(cont[nn-1][str[1]-'a']+1)+cont[nn-1][str[1]-'a']);
            else if(str[1]==str[len]){
                if(cont[nn-1][str[1]-'a']) chkmax(cont[nn][str[1]-'a'],lcnt+rcnt+1);
            }
            else{
                chkmax(cont[nn][str[1]-'a'],lcnt+!!cont[nn-1][str[1]-'a']);
                chkmax(cont[nn][str[len]-'a'],rcnt+!!cont[nn-1][str[len]-'a']);
            }
        }
        FOR(i,0,25) chkmax(cont[nn][i],!!cont[nn-1][i]);
    }
    int res=0;
    FOR(i,0,25) res=max(res,cont[n][i]);
    printf("%d\n",res);
}
```

---

## 作者：蒟蒻丁 (赞：0)

### 关于发现调了两个小时的题被学长场切了  
##  一些结论  
翻一下题面给出的“乘法”，其实就是把一个字符串重复插入到另一个字符串中。  
首先可以发现，除了 $p_n$ ，其他字符串至多只有 1 的权值，所以我们先考虑 $p_n$ 。  
可以想到，相乘只会让字符串前缀权值或者后缀权值变大，也就是说相乘后会有变化的地方只有前缀和后缀。  
进一步可以想到，如果该字符串并非整个串都是同一个字符，那么该字符串首位相连之后就不会再变化了。  
所以考虑整个字符串字符相同的时候，就直接把 $p_n$ 按题意乘到 $p_{n-1}$ 里面，再按一般的方法处理。   
注：图片中从上到下插入，根据题意实际上是从下到上乘。
![IGuGSP.png](https://z3.ax1x.com/2021/11/08/IGuGSP.png)
## 做法  
* 倒序考虑这个式子，首先处理 $p_n$。
* 如果这个字符串并不是整个串都相等的，就考虑直接在其中找一个合法子序列。
* 然后考虑前后缀，如果前后缀是同一个字符，那么就在前面的字符串中找到一个一样的字符，用来把前后缀接在一起，前后缀不相同时也是一样。
* 如果整个串都相同，那么就把它和上一个串合并（因为如果整个串都相同，其实这个串性质和一个字符差不多）。
* 而对于递归到的串，也和上面的法则一样处理——连接前后缀、合并，用一个简单的乘法原理就能统计答案了。

```c++11
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define ll long long
using namespace std;
char c[100001];
vector<char>ch[100100];
ll n,len,a[100001],ans(1),m;
bool pool[100001][30];

void dfs(ll dep,char sam='\0'){
    if(dep<1)return ;
    ll g=ch[dep].size();
    for(ll i=1;i<=g;i++)a[i]=0;
    for(ll i=0;i<=ch[dep].size();i++)c[i+1]=ch[dep][i];
    for(ll i=1;i<=g;i++){
        if(sam=='\0'||c[i]==sam){
            ll j=i;
            for("lmh qs rrd";j<=g;j++)
                if(c[i]!=c[j])break;
            j--;
            for(ll k=i;k<=j;k++)a[k]=j-i+1;
            ans=max(ans,(j-i+1)+len*(j-i+2));
            i=j;
        }
    }
    if(sam=='\0')sam=c[1];
    if(a[1]!=g){
        if(c[1]==c[g]){
            // ans=max(ans,(a[1]+a[g])+(a[1]+a[g]+2)*len);
            for(ll i=1;i<dep;i++)
                for(ll j=0;j<=ch[i].size();j++)
                    if(ch[i][j]==sam)ans=max((a[1]+a[g])+(a[1]+a[g]+2)*len+1,ans);
        }
        else {
            for(ll i=1;i<dep;i++)
                for(ll j=0;j<=ch[i].size();j++)
                    if(ch[i][j]==sam)ans=max(ans,1+(a[1]+1)*len+a[1]);
            for(ll i=1;i<dep;i++)
                for(ll j=0;j<=ch[i].size();j++)
                    if(ch[i][j]==sam)ans=max(ans,1+a[g]+(a[g]+1)*len);
        }
    }
    else {
        len=g+(g+1)*len;
        dfs(dep-1,c[1]);
    }
}

int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++){
        cin>>c+1;
        m=strlen(c+1);
        for(ll j=1;j<=m;j++)
            ch[i].push_back(c[j]);
    }
    dfs(n);
    cout<<ans;
    return 0;
}
```


---

## 作者：duyi (赞：0)

# CF1131E String Multiplication

设$f[i][j]$表示在串$p_1\cdot  p_2\cdots p_i$（也就是前$i$个串的乘积）中，字符$j$出现的最长子串长度为多少。

初始时，$f[0][0\dots 25]$都等于$0$。

考虑从$f[i-1][\dots]$转移到$f[i][\dots ]$。

1. 如果$f[i-1][j]>0$，则$f[i][j]$至少为$1$。
2. 如果字符$j$在串$p_i$里出现过，则$f[i][j]$至少为$j$在$p_i$出现的最长子串长度。
3. 考虑$p_i$的极长的、仅有一种字符的前缀，设长度为$x$，设这个字符为$c$，则$f[i][c]$至少为$x+[f[i-1][c]>0]$。
4. 考虑$p_i$的极长的、仅有一种字符的后缀，设长度为$y$，设这个字符为$c$，则$f[i][c]$至少为$y+[f[i-1][c]>0]$。
5. 如果$p_i$的第一个字符等于最后一个字符（设这个字符为$c$），且$f[i-1][c]>0$，则$f[i][c]$至少为$x+y+1$。
6. 如果$p_i$里只有一个字符。设这个字符为$c$，设$p_i$长度为$l$，则$f[i][c]$至少为$(f[i-1][c]+1)\times l +f[i-1][c]$。

综合以上六条，取$\max$即可。

时间复杂度$O(n\times26+\sum|p_i|)$。

参考代码：

```cpp
//problem:CF1131E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

template<typename T>inline void ckmax(T& x,T y){x=(y>x?y:x);}
template<typename T>inline void ckmin(T& x,T y){x=(y<x?y:x);}

const int MAXN=1e5,MAXLEN=1e5;
int n;
ll f[MAXN+5][26];
char s[MAXLEN+5];

int main() {
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>(s+1);
		int len=strlen(s+1);
		int pre=1;
		for(int j=2;j<=len;++j){
			if(s[j]==s[1]) pre++;
			else break;
		}
		int suf=1;
		for(int j=len-1;j>=1;--j){
			if(s[j]==s[len]) suf++;
			else break;
		}
		for(int j=0;j<26;++j){
			f[i][j]=(f[i-1][j]>0);
		}
		for(int j=1;j<=len;++j){
			int k=j;
			while(k+1<=len && s[k+1]==s[j])
				++k;
			ckmax(f[i][s[j]-'a'], (ll)k-j+1);
			j=k;
		}
		if(pre==len){
			// 全部都是同一种颜色
			f[i][s[1]-'a'] = (f[i-1][s[1]-'a']+1)*len + f[i-1][s[1]-'a'];
		}
		else{
			ckmax(f[i][s[1]-'a'], (ll)pre + (f[i-1][s[1]-'a']!=0));
			ckmax(f[i][s[len]-'a'], (ll)suf + (f[i-1][s[len]-'a']!=0));
			if(s[1]==s[len] && f[i-1][s[1]-'a']){
				ckmax(f[i][s[1]-'a'], (ll)pre+suf+1);
			}
		}
	}
	ll ans=0;
	for(int j=0;j<26;++j) ckmax(ans, f[n][j]);
	cout<<ans<<endl;
	return 0;
}
```





---

## 作者：Purple_wzy (赞：0)

[题面](https://www.luogu.com.cn/problem/CF1131E)
[英文题面](http://codeforces.com/problemset/problem/1131/E)      
题意：定义两个字符串$s$和$t$（$s$的长度为$m$）的乘积为: 

$t+s_1+t+s_2+\dots+t+s_m+t$ 。

定义一个字符串的美丽度为最长的相同字母连续子序列的长度。现在给出$n$个字符串$p_i$ ，问 
$((p_1p_2)p_3)\dots p_n$的美丽度。

$|s|,|t|,n,\sum p_i \leq 10^5$

题解：
对每个字母分别考虑。

设最后一个串为$S$。
发现答案只可能是$S$的一个子串，或是$S$的一段前缀和后缀，或是若干个完整的$S$拼接起来。

对于第一种情况，直接扫一遍就行了。

对于后两种情况，由于前$n-1$个串最后都得分开，它们只能作为连接两个或若干个$S$的连接字符。

那么对于第二种情况，显然贡献就是$S$的一段后缀+1+$S$的一段前缀。

对于第三种情况，也就是当前串所有字符都为指定的字符时，我们需要维护之前的操作得到的串的最长连续字符个数。

设之前的最长连续字符数为$sum$，当前$t$串的长度为$len$，那么操作后得到的最长连续字符个数即为：$len*(sum+1)+sum$。

时间复杂度：$O(\sum p_i)$

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
char s[101000];
vector<int>c[101000];
int n,m,ans,len[101000],pre[101000],suf[101000],mx[101000],cnt;
I solve(int x){
	F(i,1,n){
		pre[i]=0;
		while(pre[i]<len[i]&&c[i][pre[i]+1]==x)pre[i]++;
		suf[i]=0;
		while(suf[i]<len[i]&&c[i][len[i]-suf[i]]==x)suf[i]++;
		mx[i]=cnt=0;
		F(j,1,len[i]){
			if(c[i][j]==x)cnt++;
			else cnt=0;
			mx[i]=max(mx[i],cnt);
		}
//		cout<<pre[i]<<" "<<suf[i]<<" "<<mx[i]<<endl;
//		ans=max(ans,mx[i]);
	}
	ans=max(ans,mx[n]);
	re num=mx[1];
	F(i,2,n){
		if(pre[i]==len[i]){
			if(num)num+=(len[i]*(num+1));
			else num=len[i];
		}
		else num?num=pre[i]+suf[i]+1:num=max(pre[i],suf[i]);
		num=max(num,mx[i]);
//		cout<<num<<endl;
	}
	ans=max(ans,num);
//	cout<<endl;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);
	cin>>n;
	F(i,1,n){
		cin>>s+1;len[i]=strlen(s+1);c[i].resize(len[i]+1);
		F(j,1,len[i])c[i][j]=s[j]-'a'+1;
	}
	F(t,1,26)solve(t);
	cout<<ans;
	return 0;
}
```

---

