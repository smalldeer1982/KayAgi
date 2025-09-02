# 部分文字列

## 题目描述

[problemUrl]: https://atcoder.jp/contests/s8pc-2/tasks/s8pc_2_e

$ square1001 $「$ E869120 $は全て文字の$ character $が違うが、$ square1001 $は文字の$ character $が一致するものが$ 2 $個もある！」

$ E869120 $「ということは、部分文字列の種類数も違うのでは…」

$ square1001 $「たとえば$ 1001 $では、$ 2 $文字目だけの$ '0' $と$ 3 $文字目だけの$ '0' $が重複しているのではないか！($ '1' $もそうです)」

ということで、今回は文字列Sの部分文字列を全て列挙し、文字列の重複を$ 1 $つにまとめて数えたときのの文字数の合計を求めてください。

例えば、$ "aba" $のとき、{$ "a","b","a","ab","ba","aba" $}の$ 6 $通りが考えられますが、$ "a" $は重複しているので、

部分文字列としては$ 5 $種類が考えられます。

{$ "a","b","ab","ba","aba" $}の合計$ 1+1+2+2+3=\ 9 $文字となります。

注意：答えは$ 32 $ビット整数型に収まらない可能性があります。

- $ a,\ b,\ c,\ ab,\ bc,\ abc $ が $ abc $ の部分文字列であり, 合計は $ 10 $ 文字である。

- 重複があることに注意してください。

## 说明/提示

### 制約

- $ 1 $ ≦ $ |S| $ ≦ $ 100,000 $
- 含まれる文字の種類はalphabetの小文字だけ

### 小課題

小課題 $ 1 $ \[ $ 15 $ 点 \]

- $ 1≦|S|≦100 $ を満たす。

小課題 $ 2 $ \[ $ 35 $ 点 \]

- $ 1≦|S|≦2,000 $ を満たす。

小課題 $ 3 $ \[ $ 50 $ 点 \]

- 追加の制約はない。

## 样例 #1

### 输入

```
abc```

### 输出

```
10```

## 样例 #2

### 输入

```
aaqqz```

### 输出

```
33```

## 样例 #3

### 输入

```
atcoder```

### 输出

```
84```

# 题解

## 作者：aulive (赞：4)

为什么题解区只有后缀数组，我后缀树第一个第一个不服。\
[不会后缀树的点这里](https://www.luogu.com.cn/article/nre3vsql)\
[动态构建后缀树](http://brenden.github.io/ukkonen-animation/)
# Solution
看到求本质不同的子串长度，很容易想到后缀树。\
对于后缀树来说，每一条根到点的路径都是一个子串。\
每条父边都是一个起始位置相同且长度连续的子串集合。\
那么可以处理出父边代表子串的区间长度 $[l,r]$，则对答案的贡献为 $\frac{(l+r)\times(r-l+1)}{2}$，遍历后缀树即可。
# Code
不知为何，行末要输出换行。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5;
const int inf=1e8;
string s;
int ans;
struct suffixtree{
	int len[maxn+5],st[maxn+5],link[maxn+5],s[maxn+5],tot,rem,now,n;
	int ch[maxn+5][27];
	suffixtree(){
		now=tot=1;
		rem=n=0;
		len[0]=inf;
	}
	int new_node(int start,int le){
		++tot;
		st[tot]=start,len[tot]=le,link[tot]=1;
		return tot;
	}
	void insert(int x){
		s[++n]=x;rem++;
		int last=1;
		while(rem){
			while(rem>len[ch[now][s[n-rem+1]]])
				rem-=len[now=ch[now][s[n-rem+1]]];
			int &v=ch[now][s[n-rem+1]];
			int c=s[st[v]+rem-1];
			if(c==x||!v){
				link[last]=now,last=now;
				if(!v)v=new_node(n,inf);
				else break;
			}else{
				int u=new_node(st[v],rem-1);
				len[v]-=rem-1,st[v]+=rem-1;
				ch[u][c]=v,ch[u][x]=new_node(n,inf);
				link[last]=v=u,last=u;
			}
			if(now==1)rem--;
			else now=link[now];
		}
	}
	void solve(int now,int dept){
		int isleaf=1,le=len[now];
		for(int i=0;i<=26;i++){
			int to=ch[now][i];
			if(!to)continue;
			isleaf=0;
			solve(to,dept+len[to]);
		}
		if(isleaf){
			dept-=len[now];
			dept+=n-st[now];
			le=n-st[now];
		}//特判叶子节点
		int l=dept-le+1,r=dept;
		ans+=(l+r)*(r-l+1)/2;
	}
}tree;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>s;
	for(int i=0;i<s.size();i++)tree.insert(s[i]-'a');
	tree.insert(26);
	tree.solve(1,0);
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
$\mathrm{SA}$ 板子题喵。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
首先发现题目让我们求的是本质不同子串总长。

先考虑下我们怎么求的本质不同子串数。

就是 $\sum\limits_{i=1}^ni-height_i$。

这个过程相当于是去掉了前面重复的前缀，加上了后面新出现的前缀。

那么我们知道对于一个长度为 $len$ 的串，其子串个数为 $\frac{len(len+1)}{2}$。

所以把这个式子改为 $\sum\limits_{i=1}^n\frac{i(i+1)}{2}-\frac{height_i(height_i+1)}{2}$ 即可。

远古题，记得换行。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,mod=1e9+7,INF=0x3f3f3f3f3f3f3f3f;
int n,k,m,ans;char s[N];
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
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
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
namespace SA
{
    const int lim=20,ST=127;
    int sa[N],rk[N],old[N],c[N],h[N],st[lim+1][N];
    inline void get_SA()
    {
        m=ST;
        for(int i=1;i<=n;i++) ++c[rk[i]=s[i]];
        for(int i=2;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i>=1;i--) sa[c[rk[i]]--]=i;
        for(int k=1;k<=n;k<<=1)
        {
            int tot=0;
            for(int i=n-k+1;i<=n;i++) old[++tot]=i;
            for(int i=1;i<=n;i++) if (sa[i]>k) old[++tot]=sa[i]-k;
            for(int i=1;i<=m;i++) c[i]=0;
            for(int i=1;i<=n;i++) c[rk[i]]++;
            for(int i=2;i<=m;i++) c[i]+=c[i-1];
            for(int i=n;i>=1;--i) sa[c[rk[old[i]]]--]=old[i],old[i]=0;
            swap(rk,old);rk[sa[1]]=1;tot=1;
            for(int i=2;i<=n;i++) rk[sa[i]]=(old[sa[i]]==old[sa[i-1]]&&old[sa[i]+k]==old[sa[i-1]+k])?tot:++tot;
            if(tot==n) break;m=tot;
        }
    }
    inline void get_height()
    {
        for(int i=1,k=0,j;i<=n;i++)
        {
            if(k) --k;j=sa[rk[i]-1];
            while(s[i+k]==s[j+k]) k++;
            h[rk[i]]=k;
        }
    }
    inline void get_ST()
    {
        for(int i=1;i<=n;i++) st[0][i]=h[i];
        for(int j=1;j<=lim;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                st[j][i]=min(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }
    inline int lcp(int l,int r){int k=log2(r-l);l++;return min(st[k][l],st[k][r-(1<<k)+1]);}
}
using namespace SA;
signed main()
{
    rd(s,n);get_SA();get_height();
    for(int i=1;i<=n;i++) ans+=i*(i+1)/2-h[i]*(h[i]+1)/2;
    print(ans);put('\n');
    genshin:;flush();return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：1)

给你一个字符串，求其所有本质不同子串的长度和。

---

后缀数组模板题。$ht_i$ 即 SA 里的 $height$ 数组。

我们把子串看作后缀的前缀，长为 $l$ 的后缀所有前缀的长度和是 $\dfrac{l(l+1)}{2}$，有 $ht_i$ 个前缀在上一个后缀已经计算过，因此答案是 $\sum \limits_{i=1}^n \dfrac{i(i+1)}{2}-\dfrac{ht_i(ht_i+1)}{2}$。

 

```cpp
#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
int n; string s;  
int main(){
    cin >> s,n = s.size(); long long ans = 0;
    for(int i = 1;i <= n;i ++) ans += 1ll * i * (i + 1) / 2;
    vector<int> sa = atcoder::suffix_array(s),h = atcoder::lcp_array(s,sa);
    for(int i : h) ans -= 1ll * i * (i + 1) / 2;
    cout << ans << "\n";
}
```

---

## 作者：hzjnsy (赞：1)

**[AT](https://atcoder.jp/contests/s8pc-2/tasks/s8pc_2_e) [洛谷](https://www.luogu.com.cn/problem/AT_s8pc_2_e)**

> - 给出一个字符串 $S$，求 $S$ 的所有本质不同子串的长度之和。
>
> - $|S| \le 10^5$。

看到本质不同子串，先做后缀排序把 $\text{height}$ 数组求出来，然后排名为 $i$ 的后缀能带来的本质不同子串个数为 $|S|-sa_i+1-\text{height}_i$，这些子串的长度为 $\text{height}_i+1\sim |S|-sa_i+1$，等差数列求和计算即可。

时间复杂度为 $\mathcal{O}(|S|\log |S|)$，空间复杂度为 $\mathcal{O}(|S|)$。由于是 AT 远古题，所以行末要输出换行。

**[提交记录](https://atcoder.jp/contests/s8pc-2/submissions/45902260)**


```cpp
#include <bits/stdc++.h>
#define P pair
#define fi first 
#define se second 
#define mst memset
#define int long long
#define sof sizeof
using namespace std; const int N = 1e5 + 5; int len; string a;
struct SuffixArray {
    int rk[N], sa[N], ht[N], cnt[N]; P<P<int, int>, int> p[N], tmp[N];
    void init() {
        mst(rk, 0, sof rk); mst(ht, 0, sof ht); 
        mst(p, 0, sof p); mst(cnt, 0, sizeof cnt);
    }
    void Sort() {
        for (int i = 1; i <= len; ++i) ++cnt[a[i]];
        for (int i = 'a'; i <= 'z'; ++i) cnt[i] += cnt[i - 1];
        for (int i = 1; i <= len; ++i) rk[i] = cnt[a[i] - 1] + 1;
        for (int l = 1, id; l <= len; l <<= 1) {
            for (int i = 1; i <= len; ++i)
                p[i] = {{rk[i], i + l > len ? 0 : rk[i + l]}, i};
            mst(cnt, 0, sizeof cnt);
            for (int i = 1; i <= len; ++i) ++cnt[p[i].fi.se];
            for (int i = 1; i <= len; ++i) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; --i) tmp[cnt[p[i].fi.se]--] = p[i];
            for (int i = 1; i <= len; ++i) p[i] = tmp[i];
            mst(cnt, 0, sizeof cnt);
            for (int i = 1; i <= len; ++i) ++cnt[p[i].fi.fi];
            for (int i = 1; i <= len; ++i) cnt[i] += cnt[i - 1];
            for (int i = len; i >= 1; --i) tmp[cnt[p[i].fi.fi]--] = p[i];
            for (int i = 1; i <= len; ++i) p[i] = tmp[i]; id = 0;
            for (int i = 1; i <= len; ++i) { 
                if (i == 1 || p[i].fi != p[i - 1].fi) ++id; rk[p[i].se] = id; 
            }
            if (id == len) break;
        }   
        for (int i = 1; i <= len; ++i) sa[rk[i]] = i;
    }
    void height() {
        for (int i = 1, k = 0; i <= len; ++i) {
            if (rk[i] == 1) { k = 0; continue; }
            if (k) --k; int j = sa[rk[i] - 1];
            for (; i + k <= len && j + k <= len && a[i + k] == a[j + k]; ++k); 
            ht[rk[i]] = k;
        }
    }
    int calc() {
        int ret = 0;
        for (int i = 1; i <= len; ++i)
            ret += (len - sa[i] + 1 - ht[i]) * (ht[i] + 2 + len - sa[i]) >> 1;
        return ret;
    }
} SA;
signed main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0); 
    cin >> a; len = a.size(); a = ' ' + a; SA.init(); SA.Sort(); SA.height();
    return cout << SA.calc() << '\n', 0;
}
```


---

## 作者：hzoi_Shadow (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_s8pc_2_e)

# 前置知识

[后缀数组简介](https://oi-wiki.org/string/sa/)

# 解法

对于一个后缀 $s_{sa_{i} \sim n}$，它产生了 $n-sa_{i}+1$ 个前缀，其长度和为 $\frac{(n-sa_{i}+1)(n-sa_{i}+2)}{2}$；和 $s_{sa_{i-1} \sim n}$ 相比产生了 $height_{i}$ 个相同的前缀，其长度和为 $\frac{height_{i}(height_{i}+1)}{2}$。

最终，有 $\sum\limits_{i=1}^{n}\frac{(n-sa_{i}+1)(n-sa_{i}+2)}{2}-\sum\limits_{i=1}^{n}\frac{height_{i}(height_{i}+1)}{2} $ 即为所求，化简完得到 $\frac{1}{2} \times (\frac{n(n+1)(2n+1)}{6}+\frac{n(n+1)}{2})-\sum\limits_{i=1}^{n}\frac{height_{i}(height_{i}+1)}{2}$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define ull unsigned long long
#define sort stable_sort 
#define endl '\n'
ll sa[100010],rk[200010],oldrk[200010],id[100010],cnt[100010],key[100010],height[100010],a[100010],b[100010],fminn[100010][20];
char s[100010];
ll val(char x)
{
	return (ll)x;
}
void counting_sort(ll n,ll m)
{
	memset(cnt,0,sizeof(cnt));
	for(ll i=1;i<=n;i++)
	{
		cnt[key[i]]++;
	}
	for(ll i=1;i<=m;i++)
	{
		cnt[i]+=cnt[i-1];
	}
	for(ll i=n;i>=1;i--)
	{
		sa[cnt[key[i]]]=id[i];
		cnt[key[i]]--;
	}
}
void init_sa(char s[],ll len)
{
	ll m=127,tot=0,num=0,i,j,w;
	for(i=1;i<=len;i++)
	{
		rk[i]=val(s[i]);
		id[i]=i;
		key[i]=rk[id[i]];
	}
	counting_sort(len,m);
	for(w=1;tot!=len;w<<=1,m=tot)
	{
		num=0;
		for(i=len;i>=len-w+1;i--)
		{
			num++;
			id[num]=i;
		}
		for(i=1;i<=len;i++)
		{
			if(sa[i]>w)
			{
				num++;
				id[num]=sa[i]-w;
			}
		}
		for(i=1;i<=len;i++)
		{
			key[i]=rk[id[i]];
		}
		counting_sort(len,m);
		for(i=1;i<=len;i++)
		{
			oldrk[i]=rk[i];
		}
		tot=0;
		for(i=1;i<=len;i++)
		{
			tot+=(oldrk[sa[i]]!=oldrk[sa[i-1]]||oldrk[sa[i]+w]!=oldrk[sa[i-1]+w]);
			rk[sa[i]]=tot;
		}
	}
	for(i=1,j=0;i<=len;i++)
	{
		j-=(j>=1);
		while(s[i+j]==s[sa[rk[i]-1]+j])
		{
			j++;
		}
		height[rk[i]]=j;
	}
}
int main()
{
	ll n,sum=0,i;
	scanf("%s",s+1);
    n=strlen(s+1);
	init_sa(s,n);
	for(i=1;i<=n;i++)
	{
		sum+=height[i]*(height[i]+1)/2;
	}
	cout<<(n*(n+1)*(2*n+1)/6+n*(n+1)/2)/2-sum<<endl;
	return 0;
}
```

---

