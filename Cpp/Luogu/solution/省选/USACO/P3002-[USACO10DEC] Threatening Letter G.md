# [USACO10DEC] Threatening Letter G

## 题目描述

FJ has had a terrible fight with his neighbor and wants to send him a nasty letter, but wants to remain anonymous. As so many before him have done, he plans to cut out printed letters and paste them onto a sheet of paper. He has an infinite number of the most recent issue of the Moo York Times that has N (1 <= N <= 50,000) uppercase letters laid out in a long string (though read in as a series of shorter strings). Likewise, he has a message he'd like to compose that is a single long string of letters but that is read in as a set of shorter strings.

Being lazy, he wants to make the smallest possible number of cuts. FJ has a really great set of scissors that enables him to remove any single-line snippet from the Moo York Times with one cut. He notices that he can cut entire words or phrases with a single cut, thus reducing his total number of cuts.

What is the minimum amount of cuts he has to make to construct his letter of M (1 <= M <= 50,000) letters?

It is guaranteed that it is possible for FJ to complete his task.

Consider a 38 letter Moo York Times:

```cpp
THEQUICKBROWNFOXDO 
GJUMPSOVERTHELAZYDOG 
from which FJ wants to construct a 9 letter message: 
FOXDOG 
DOG 
```
These input lines represent a pair of strings:
THEQUICKBROWNFOXDOGJUMPSOVERTHELAZYDOG 

FOXDOGDOG 

Since 'FOXDOG' exists in the newspaper, FJ can cut this piece out and then get the last 'DOG' by cutting out either instance of the word 'DOG'. 

Thus, he requires but two cuts.

FJ 刚刚和邻居发生了一场可怕的争吵，他咽不下这口气，于是决定佚名发给他的邻居一封脏话连篇的信。他有无限张完全相同的已经打印好的纸张，都包含 $N$ 个字母。他有一把举世无双的剪刀，可以从某张纸中通过一刀剪出连续的一段（也可以通过一刀获得整个字符串）。他想知道获得这封 $M$ 个字母的长信最少需要剪多少刀。保证这总是可能的。

## 样例 #1

### 输入

```
38 9 
THEQUICKBROWNFOXDO 
GJUMPSOVERTHELAZYDOG 
FOXDOG 
DOG 
```

### 输出

```
2 
```

# 题解

## 作者：Graphcity (赞：6)

看到题面，首先可以想到一个 DP：设 $f(i)$ 为剪出第二封信的前 $i$ 个字符所需要的最小次数，显然有 $f(i)=1+\min_{i-val_i\le j<i} f(j)$，其中 $val_i$ 为以 $i$ 结尾能够剪出的最大后缀长度。这个 DP 可以利用线段树优化成 $O(n\log n)$，所以关键在于如何求 $val_i$。

根据 “子串是前缀的后缀”，$val_i$ 即为第二封信的前缀 $i$ 与第一封信的任意前缀的 **最大公共后缀**。将两封信翻转，就变成了求第二封信的一个后缀与第一封信的任意后缀的 **最大公共前缀**。

将第一封信与第二封信拼在一起，中间用特殊字符连接，跑一遍后缀数组，求出 $height(i)$，根据 $lcp(sa_i,sa_j)=\min_{i+1\le k\le j}height(k)$，建立 ST 表就可以用 $O(n\log n)-O(1)$ 的时间复杂度求出任意两个后缀的最大公共前缀。

根据上面的定理，若 $sa_i$ 与 $sa_j$ 距离越远，它们的最大公共前缀就越小。所以，在求 $val_i$ 时，寻找 $sa$ 数组上左右距离 $rk_i$ 最近的两个点求最大公共前缀，然后取最大值即可。

每一步的时间复杂度均为 $O(n\log n)$，所以总时间复杂度为 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Rof(i,a,b) for(i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,inf=1e9;

int m1,m2,n,i,j,m,p,t,seg[Maxn*4+5]; char s1[Maxn+5],s2[Maxn+5],s[Maxn+5],str[Maxn+5];
int sa[Maxn+5],rk[Maxn+5],ht[Maxn+5],cnt[Maxn+5],id[Maxn+5],px[Maxn+5],old[Maxn+5];
int f[Maxn+5],val[Maxn+5],pos[Maxn+5][2],lg[Maxn+5],st[Maxn+5][20],vis[Maxn+5];
inline int cmp(int x,int y) {return (old[x]==old[y] && old[x+t]==old[y+t]);}
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void Init()
{
    int res=0;
    scanf("%d%d",&m1,&m2); n=m1+m2+1,m=200;
    while(1)
    {
        scanf("%s",str+1); int siz=strlen(str+1);
        For(i,1,siz) s1[res+i]=str[i];
        res+=siz; if(res==m1) break;
    }
    res=0;
    while(1)
    {
        scanf("%s",str+1); int siz=strlen(str+1);
        For(i,1,siz) s2[res+i]=str[i];
        res+=siz; if(res==m2) break;
    }
    For(i,1,m1) s[i]=s1[m1-i+1];
    s[m1+1]='#';
    For(i,1,m2) s[m1+1+i]=s2[m2-i+1];
}
inline void SA()
{
    For(i,1,n) cnt[rk[i]=s[i]]++;
    For(i,1,m) cnt[i]+=cnt[i-1];
    Rof(i,n,1) sa[cnt[rk[i]]--]=i;
    for(t=1;t<=n;t<<=1,m=p)
    {
        for(p=0,i=n;i>n-t;--i) id[++p]=i;
        For(i,1,n) if(sa[i]>t) id[++p]=sa[i]-t;
        memset(cnt,0,sizeof(cnt));
        For(i,1,n) cnt[px[i]=rk[id[i]]]++;
        For(i,1,m) cnt[i]+=cnt[i-1];
        Rof(i,n,1) sa[cnt[px[i]]--]=id[i];
        memcpy(old,rk,sizeof(rk));
        for(p=0,i=1;i<=n;++i) rk[sa[i]]=(cmp(sa[i-1],sa[i])?p:++p);
    }
}
inline void Build()
{
    int res=0;
    For(i,1,n)
    {
        while(s[sa[rk[i]-1]+res]==s[i+res]) res++;
        ht[rk[i]]=res,res=max(0,res-1);
    }
}
inline void BuildST()
{
    For(i,2,n) lg[i]=lg[i>>1]+1;
    For(i,1,n) st[i][0]=ht[i];
    For(j,1,19) For(i,1,n)
    {
        st[i][j]=st[i][j-1];
        if(i+(1<<j-1)<=n) st[i][j]=min(st[i][j],st[i+(1<<j-1)][j-1]);
    }
}
inline int Count(int l,int r)
{
    int len=lg[r-l+1];
    return min(st[l][len],st[r-(1<<len)+1][len]);
}
inline void Tag()
{
    For(i,0,n+1) pos[i][0]=0,pos[i][1]=n+1;
    For(i,1,m1) vis[rk[i]]=1;
    For(i,1,n) pos[i][0]=(vis[i]?i:pos[i-1][0]);
    Rof(i,n,1) pos[i][1]=(vis[i]?i:pos[i+1][1]);
}
inline void GetVal(int x)
{
    int l=pos[rk[n-x+1]][0],r=pos[rk[n-x+1]][1];
    if(l) val[x]=max(val[x],Count(l+1,rk[n-x+1]));
    if(r!=n+1) val[x]=max(val[x],Count(rk[n-x+1]+1,r));
}
inline void push_up(int p) {seg[p]=min(seg[ls(p)],seg[rs(p)]);}
inline void Update(int l,int r,int p,int pos,int k)
{
    if(l==r) {seg[p]=k; return;}
    int mid=(l+r)>>1;
    if(pos<=mid) Update(l,mid,ls(p),pos,k);
    else Update(mid+1,r,rs(p),pos,k);
    push_up(p);
}
inline int Count(int nl,int nr,int l,int r,int p)
{
    if(l<=nl && nr<=r) return seg[p];
    int mid=(nl+nr)>>1,res=inf;
    if(l<=mid) res=min(res,Count(nl,mid,l,r,ls(p)));
    if(r>mid) res=min(res,Count(mid+1,nr,l,r,rs(p)));
    push_up(p); return res;
}
inline void GetAns()
{
    For(i,1,m2)
    {
        if(val[i]==i) f[i]=1;
        else f[i]=Count(1,n,i-val[i],i-1,1)+1;
        Update(1,n,1,i,f[i]);
    }
    printf("%d\n",f[m2]);
}

int main()
{
    Init(),SA(),Build(),BuildST(),Tag();
    For(i,1,m2) GetVal(i);
    GetAns();
    return 0;
}
```

---

## 作者：Fading (赞：6)

这题读入比较奇怪，不知道为什么样例有这么多行……所以我建议就这么读入：


```

inline int read(){
	char ch=getchar();
	while (!isalpha(ch))  ch=getchar();
	return ch-'A';
}
//------main------
for (int i=1;i<=n;i++){
	sa.insert(read());
}
for (int i=1;i<=m;i++){
	sa.doit(read());
}
```
题意简述：
```
给你一个长度为n的串s1，再给你一个长度为m的串s2，问需要至少多少个s1的子串才可以拼成s2？
```

回到正题，我们先对第一个串建一个$SAM$。

然后把第二个串放在$SAM$上跑，用一个指针$pos$记录现在在$SAM$的哪个节点。

如果不匹配了就$ans++$，并且$pos$回到根节点，这说明必须要用新的子串才可以继续拼了。

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	char ch=getchar();
	while (!isalpha(ch))  ch=getchar();
	return ch-'A';
}
int ans;
struct Suffix_Automaton{
	int cnt,last,g[2000001][27],NOW,pa[2000001],len[2000001];
	inline void init(){
		cnt=last=1;NOW=1;
	}
	inline void insert(int ch){
		int np=++cnt,pos=last;last=cnt;len[np]=len[pos]+1;
		for (;pos&&!g[pos][ch];pos=pa[pos]) g[pos][ch]=np;
		if (!pos) pa[np]=1;
		else{
			int posx=g[pos][ch];
			if (len[pos]+1==len[posx]) pa[np]=posx;
			else{
				int q=++cnt;
				len[q]=len[pos]+1;
				for (int i=0;i<26;i++) g[q][i]=g[posx][i];
				pa[q]=pa[posx];pa[posx]=pa[np]=q;
				for (;g[pos][ch]==posx;pos=pa[pos]) g[pos][ch]=q;
			}
		}
	}
	inline void doit(int ch){
		if (g[NOW][ch]) NOW=g[NOW][ch];//如果匹配继续跑
		else{//如果不匹配了
			ans++;
			NOW=g[1][ch];
		}
	}
}sa;
int main(){
	int n,m;cin>>n>>m;
	sa.init();
	for (int i=1;i<=n;i++){
		sa.insert(read());
	}
	ans=1;
	for (int i=1;i<=m;i++){
		sa.doit(read());
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：StayAlone (赞：2)

### 题意

给定两个串 $s,t$，初始有一个空串 $p$。每次可以选出一个 $s$ 的子串拼到 $p$ 后面。求最少的操作次数使得最终 $p = t$。

$1\leq |s|,|t| \leq 5\times 10^4$。

### 思路

考虑贪心：每一次截取尽量长的子串拼上去。比较好证：

- 设存在一个更短的串 $q_2$ 优于更长的串 $q_1$。而接下来要拼的串对于 $q_2$ 会比 $q_1$ 更长。那么一旦能给 $q_2$ 拼，给 $q_1$ 拼的方案一定存在且不劣。

大概是这样的。

所以 SA 求出 height。套路地，把 $s,t$ 拼到一起并且中间分隔符，再用一个贪心：由于子串是后缀的前缀，所以问题转化成了确定了其中一个串，再在另一些串里面选一个使得这两个串的 LCP 最大。由于 LCP 是一堆连续 height 的 min，现在已经确定了一个位置，那么另一个位置显然是越靠近确定的那个位置越好。

所以存下来 $s$ 的所有 rnk 并排序，每一次 lower_bound 之后配合 ST 表回答询问即可。时间复杂度 $\Theta(n\log n)$。

输入有点恶心，写得丑。

[AC code record](https://www.luogu.com.cn/record/97784345)
```cpp
string s, s2;
int n, m, mii[MAXN][LOGN + 5], lg[MAXN];
int tmp[MAXN], cnt[MAXN], rnk[MAXN << 1], prnk[MAXN << 1], sa[MAXN], hgt[MAXN];
vector <int> frk;

il int query(int l, int r) {
	int k = lg[r - l + 1];
	return min(mii[l][k], mii[r - (1 << k) + 1][k]);
}

int main() {
	read(n, m); string k;
	while (s.size() < n) cin >> k, s += k;
	while (cin >> k) s2 += k;
	s = '@' + s; s += char(0); s += s2; n += m + 1;
	rep1(i, 2, n) lg[i] = lg[i >> 1] + 1;
	rep1(i, 1, n) sa[i] = i, rnk[i] = s[i];
	int p = 127;
	for (int w = 1; w < n; w <<= 1) {
		memset(cnt, 0, sizeof(int) * (p + 1));
		rep1(i, 1, n) ++cnt[rnk[sa[i] + w]];
		rep1(i, 1, p) cnt[i] += cnt[i - 1];
		rep2(i, n, 1) tmp[cnt[rnk[sa[i] + w]]--] = sa[i];
		memcpy(sa, tmp, sizeof(int) * (n + 1));
		memset(cnt, 0, sizeof(int) * (p + 1));
		rep1(i, 1, n) ++cnt[rnk[sa[i]]];
		rep1(i, 1, p) cnt[i] += cnt[i - 1];
		rep2(i, n, 1) tmp[cnt[rnk[sa[i]]]--] = sa[i];
		memcpy(sa, tmp, sizeof(int) * (n + 1));
		
		memcpy(prnk, rnk, sizeof(int) * (n + 1)); p = 0;
		rep1(i, 1, n) {
			if (prnk[sa[i]] == prnk[sa[i - 1]] && prnk[sa[i] + w] == prnk[sa[i - 1] + w]) rnk[sa[i]] = p;
			else rnk[sa[i]] = ++p;
		}
		if (p == n) break;
	}
	rep1(i, 1, n) {
		int k = max(0, hgt[rnk[i - 1]] - 1), t = max(i, sa[rnk[i] - 1]);
		while (t + k <= n && s[i + k] == s[sa[rnk[i] - 1] + k]) ++k;
		hgt[rnk[i]] = k;
	}
	rep1(i, 1, n) mii[i][0] = hgt[i];
	rep1(j, 1, lg[n]) rep1(i, 1, n - (1 << j) + 1) mii[i][j] = min(mii[i][j - 1], mii[i + (1 << j - 1)][j - 1]);
	n -= m + 1;
	rep1(i, 1, n) frk.eb(rnk[i]);
	sort(frk.begin(), frk.end());
	int ans = 0, idx = 0;
	while (idx < s2.size()) {
		auto it = lower_bound(frk.begin(), frk.end(), rnk[n + 2 + idx]);
		int now = 0;
		if (it != frk.end()) now = max(now, query(rnk[n + 2 + idx] + 1, *it));
		if (it != frk.begin()) now = max(now, query(*--it + 1, rnk[n + 2 + idx]));
		idx += now; ++ans;
	} printf("%d", ans);
	rout;
}
```

---

## 作者：creation_hy (赞：0)

这水题啊。

很显然贪心从匹配串开头开始找最长可以匹配的串是正确的，因为下一次匹配的字符串无论开头去掉多少，它们都是全拿完的后缀，也就导致你全拿完要切的地方不拿完也要切。

然后判断一个串是否在另一个串里面就很简单了，直接 SAM。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 114514;
int n, m;
string s1, s2;
struct SAM
{
    int tot, last, len[N], t[N][26], fa[N];
    inline SAM()
    {
        fa[tot = last = 0] = -1;
    }
    inline void insert(char c)
    {
        c -= 'A';
        int cur = ++tot;
        len[cur] = len[last] + 1;
        int p = last;
        last = cur;
        while (~p && !t[p][c])
            t[p][c] = cur, p = fa[p];
        if (p == -1)
        {
            fa[cur] = 0;
            return;
        }
        int x = t[p][c];
        if (len[x] == len[p] + 1)
            fa[cur] = x;
        else
        {
            len[++tot] = len[p] + 1;
            fa[tot] = fa[x];
            memcpy(t[tot], t[x], sizeof(t[x]));
            while (~p && t[p][c] == x)
                t[p][c] = tot, p = fa[p];
            fa[cur] = fa[x] = tot;
        }
    }
    inline int match(string s)
    {
        int cur = 0, res = 1;
        for (char c : s)
        {
            c -= 'A';
            if (t[cur][c])
                cur = t[cur][c];
            else
                cur = t[0][c], res++;
        }
        return res;
    }
} sam;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    while (s1.size() < n)
    {
        string tmp;
        cin >> tmp;
        s1 += tmp;
    }
    int res = 0;
    while (s2.size() < m)
    {
        string tmp;
        cin >> tmp;
        s2 += tmp;
    }
    for (char c : s1)
        sam.insert(c);
    cout << sam.match(s2);
    return 0;
}
```

---

