# Expensive Strings

## 题目描述

You are given $ n $ strings $ t_{i} $ . Each string has cost $ c_{i} $ .

Let's define the function of string ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF616F/a2be2e6a84d9d8ad3e2e42357554f4328caffa73.png), where $ p_{s,i} $ is the number of occurrences of $ s $ in $ t_{i} $ , $ |s| $ is the length of the string $ s $ . Find the maximal value of function $ f(s) $ over all strings.

Note that the string $ s $ is not necessarily some string from $ t $ .

## 样例 #1

### 输入

```
2
aa
bb
2 1
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2
aa
ab
2 1
```

### 输出

```
5
```

# 题解

## 作者：grass8cow (赞：9)

题解都是广义 SAM ……我不会。考虑 SA 做法。

先把所有串接起来，插入不同的分隔符，然后跑一遍 SA。

那么这个 $f(s)$ , 其实就是出现的所有位置的权值和乘上它的长度。

Q：s 包含了间隔符呢？

A：因为间隔符互不相同，它必然只会出现一次。后面特判。

考虑所有长度为 $L$ 的子串，如果左端为 $a$ 和左端为 $b$ 的子串相同，那么有 $L\le lcp(s_a,s_b)$  ，其中 $s_i$ 表示整个串左端为 $i$ 的后缀。

然后就发现，$lcp(s_a,s_b)=\min_{i=rk_a+1}^{rk_b}h_i$ ，所以对于 $rk_a< i \le rk_b $ ，有 $L\le h_i$ 。类似品酒大会的套路，建个图，如果 $rk_a,rk_b$ 在一个联通块，则 $L\le lcp(s_a,s_b)$ 。

把 $L$ 从大到小考虑，那么对于当前所有的 $h_i=L$ ,把 $i$ 和 $i-1$ 之间连一条边。同时维护一下当前联通块的权值和，把答案用每个新联通块的 $L\cdot sz$ 更新即可。但需要注意的是，由于权值存在负数，所以对每个 $L$ ,得先连完边，再更新答案。

Q：如果 $L$ 变小，$sz$ 为负数，联通块权值不是变大了吗？

A：$L$ 是正数，所以权值是负的，可取空串就能使 $ans=0$ 。

上面部分， $ans$ 都是用新联通块更新的，所以没有串只出现一次的情况，都是合法的串。那么出现一次的串，首先左端不能是间隔符；其次，令左端为 $i$ , 则有 $\max(h_{rk_i},h_{rk_i+1})+1\le p$ ，其中 $p$ 为左端 $i$ 能取到的最长串。根据上面的讨论，这样就涵盖了最优解。做完了。

code:

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int c[600010];char p[500010];int m=128,rk[600010],sa[600010],t[600010],tr[600010],h[600010];
vector<int>g[600010];
void SA(int n){
	for(int i=1;i<=n;i++)t[rk[i]=c[i]]++;
	for(int i=1;i<=m;i++)t[i]+=t[i-1];
	for(int i=1;i<=n;i++)sa[t[c[i]]--]=i;
	for(int k=1;;k<<=1){
		int p=0;
		for(int i=1;i<=m;i++)t[i]=0;
		for(int i=n-k+1;i<=n;i++)tr[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)tr[++p]=sa[i]-k;
		for(int i=1;i<=n;i++)t[rk[i]]++;
		for(int i=1;i<=m;i++)t[i]+=t[i-1];
		for(int i=n;i>=1;i--)sa[t[rk[tr[i]]]--]=tr[i];
		p=1;swap(tr,rk);rk[sa[1]]=1;
		for(int i=2;i<=n;i++)rk[sa[i]]=(tr[sa[i]]==tr[sa[i-1]]&&tr[sa[i]+k]==tr[sa[i-1]+k])?p:++p;
		if(n==p)break;m=p;
	}
	for(int i=1,k=0;i<=n;i++){
		if(k)k--;int j=sa[rk[i]-1];
		while(c[i+k]==c[j+k])k++;
		g[k].push_back(rk[i]);h[rk[i]]=k;
	}
}
int n,l[100010],f[600010],cp[600010],lp[100010];ll v[100010],sz[600010],ans;
int find(int x){if(x==f[x])return x;return f[x]=find(f[x]);}
ll merge(int u,int v){
	u=find(u),v=find(v);f[u]=v;sz[v]+=sz[u];
	return sz[v];
}
int main(){
	int len=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",p);l[i]=strlen(p);
		for(int j=0;j<l[i];j++)c[++len]=p[j],cp[len]=i;
		lp[i]=len;if(i<n)m++,c[++len]=m;
	}
	for(int i=1;i<=n;i++)scanf("%lld",&v[i]);
	SA(len);
	for(int i=1;i<=len;i++){
		f[i]=i,sz[i]=v[cp[sa[i]]];
		if(max(h[i],h[i+1])+1<=lp[cp[sa[i]]]-sa[i]+1)ans=max(ans,(lp[cp[sa[i]]]-sa[i]+1)*sz[i]);
	}
	for(int i=len;i;i--){
		for(int j=0;j<g[i].size();j++)merge(g[i][j]-1,g[i][j]);
		for(int j=0;j<g[i].size();j++)ans=max(ans,sz[find(g[i][j])]*i);
	}
	return printf("%lld",ans),0;
}
```


---

## 作者：Alex_Wei (赞：8)

> [CF616F Expensive Strings 题面传送门](https://www.luogu.com.cn/problem/CF616F)

> 题意简述：给出 $t_{1,2,\cdots,n}$ 和 $c_{1,2,\cdots,n}$，求 $\max f(s)=\sum_i^n c_i\times p_{s,i} \times |s|$ 的最大值，其中 $s$ 为任意字符串，$p_{s,i}$ 为 $s$ 在 $t_i$ 中的出现次数。

[我的 SAM 学习笔记 —— cnblogs](https://www.cnblogs.com/alex-wei/p/Suffix_Automaton.html)。

---

广义 SAM 板子题。

考虑 SAM 上每个状态所表示的意义：出现位置相同的字符串集合。也就是说，对于 SAM 上的一个状态 $t$，它所表示的所有字符串 $s$ 的 $\sum_{i=1}^n c_i\times p_{s,i}$ 是相同的，所以它对答案的可能贡献就是 $\sum_{i=1}^n c_i\times p_{s,i}\times len(t)$。$\sum_{i=1}^n c_i\times p_{s,i}$ 可以直接在 $link$ 树上树形 DP 求出。~~我一开始还以为要线段树合并，做题做傻了。~~

一些注意点：如果你写的是 $las=1$ 版本的伪广义 SAM，如果不判重，可能会建空节点 $p$，此时 $len(link(p))=len(p)$。所以特判一下这种情况就行了，否则会 WA on 16，并且 “expected 0，found 500”。

同时，答案的初始值应赋为 $0$ 而不是 $-\infty$，因为只要让 $s$ 不在任何一个 $t_i$ 中出现过就可以 $f(s)=0$。

~~一开始直接拿 P4022 熟悉的文章 的广义 SAM 写的，那个题目是 01 串，所以复制儿子只复制了 0 和 1（这题就是 a 和 b），然后过了 43 个测试点。~~

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

//#pragma GCC optimize(3)

//using int = long long
//using i128 = __int128;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using db = double;
using ld = long double;
using pii = pair <int,int>;
using pll = pair <ll,ll>;
using pdd = pair <double,double>;
using vint = vector <int>;
using vpii = vector <pii>;

#define fi first
#define se second
#define pb emplace_back
#define mpi make_pair
#define all(x) x.begin(),x.end()
#define sor(x) sort(all(x))
#define rev(x) reverse(all(x))
#define mem(x,v) memset(x,v,sizeof(x))
#define mcpy(x,y) memcpy(x,y,sizeof(y))
#define Time 1.0*clock()/CLOCKS_PER_SEC

const int N=1e6+5;

// Suffix_Automaton
int cnt,las;
int fa[N],len[N],son[N][26];
ll val[N];
vector <int> e[N];
void ins(int it,int v){
	int p=las,cur=++cnt;
	len[cur]=len[las]+1,las=cur,val[cur]=v;
	while(p&&!son[p][it])son[p][it]=cur,p=fa[p];
	if(!p)return fa[cur]=1,void();
	int q=son[p][it];
	if(len[p]+1==len[q])return fa[cur]=q,void();
	int cl=++cnt;
	fa[cl]=fa[q],fa[q]=fa[cur]=cl,len[cl]=len[p]+1;
	mcpy(son[cl],son[q]);
	while(p&&son[p][it]==q)son[p][it]=cl,p=fa[p];
} void build(string s,int v){
	las=1;
	for(int i=0;i<s.size();i++)ins(s[i]-'a',v);
} void dfs(int id){
	for(int it:e[id])dfs(it),val[id]+=val[it];
}

int n;
ll ans;
string s[N];
int main(){
	cin>>n,cnt=1;
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=1,c;i<=n;i++)cin>>c,build(s[i],c);
	for(int i=1;i<=cnt;i++)e[fa[i]].pb(i);
	dfs(1); for(int i=1;i<=cnt;i++)if(len[fa[i]]!=len[i])ans=max(ans,len[i]*val[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：方123456 (赞：4)

几位神仙讲的 SA 做法我都不太明白，经过一段时间的思考我终于理解了一点。

我们先把这些字符串串起来，然后中间的分隔符号用 `'z'+i`，这样的话就可以保证分隔符号不会影响我们后缀排序。

然后我们需要知道的是，对于一个目标字符串，如果他出现了两次，那么必然是某个排名为 $i$ 和排名为 $i+1$ 的 LCP。

---

证明是这样的，假如说这个不是 LCP，设这个字符串是 $s1$，那么必然会存在一个 LCP，设为 $s2$，使得 $s1$ 是 $s2$ 的前缀。

那么我们看看这个柿子会发现，出现次数是不变的，如果发生了改变那么必然是有单独的一个 $s1$，所有 $s1$ 出现的地方，肯定都是被 $s2$ 给覆盖的。

设 $|s|$ 为字符串 $s$ 的长度。

然后我们将这个柿子稍微改一改就变成了 $|s| \sum c_i \times p_{i,s}$，假如说 $\sum c_i \times p_{i,s}$ 是负数，那么必然一点用处都没有，因为我们可以随便选一个未出现过的字符串，那么也就是说后面那个和肯定是一个正数，由于要求答案尽量大，所有长度肯定是越长越好。

所以我们证明了上面那个结论

---

然后我们就需要用 SA 的经典套路了，相信学过 SA 的都应该做过 P4248 [AHOI2013]差异 ，对于一个 LCP 而言，他能扩展到的左边界是 height 都大于他的地方，右边界也是一样的。

我们计算当前这个字符串每一个点是在哪一个字符串，然后赋值为对应的 $c_i$，做一遍前缀和就能快速的维护这个问题了！

然后对于出现一次的子串可以暴力判断，即枚举头，然后判断前后两个 height 就可以了！

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=2e6+5;
int n,rk[INF],sa[INF],sa1[INF],sum[INF],rk1[INF],he[INF],c[INF],m,vis[INF],q[INF],r;
int L[INF],R[INF],P[INF];
int aa[INF];
signed main()
{
    ios::sync_with_stdio(false);
    cin>>m;
    for (int i=1;i<=m;i++) {
        string s1;cin>>s1;
        // s2=s2+(char)(i+'z')+s1;
        aa[++n]=(i+'z');
        for (char i:s1) aa[++n]=i;
    }
    for (int i=1;i<=n;i++) sa[i]=i,rk[i]=aa[i]-'a'+1;
    for (int i=1;i<=m;i++) cin>>c[i];
    int l=0;
    for (int i=1;i<=n;i++) {
        if (aa[i]>='a' && aa[i]<='z') vis[i]=l;
        else l++;
    }
    for (int i=n;i>=1;i--)
        if (aa[i]>='a' && aa[i]<='z') P[i]=P[i+1]+1;
    for (int w=1;w<n;w*=2) {
        int N=1e5;
        for (int i=0;i<=n+N;i++) sum[i]=0;
        for (int i=1;i<=n;i++) sum[rk[sa[i]+w]]++;
        for (int i=1;i<=n+N;i++) sum[i]+=sum[i-1];
        for (int i=n;i;i--) 
            sa1[sum[rk[sa[i]+w]]--]=sa[i];
        for (int i=1;i<=n;i++) sa[i]=sa1[i];

        for (int i=0;i<=n+N;i++) sum[i]=0;
        for (int i=1;i<=n;i++) sum[rk[sa[i]]]++;
        for (int i=1;i<=n+N;i++) sum[i]+=sum[i-1];
        for (int i=n;i;i--) 
            sa1[sum[rk[sa[i]]]--]=sa[i];
        for (int i=1;i<=n;i++) sa[i]=sa1[i];

        for (int i=1;i<=n;i++) rk1[i]=rk[i];
        int tot=0;
        for (int i=1;i<=n;i++)
            if (i>1 && rk1[sa[i-1]+w]==rk1[sa[i]+w] && rk1[sa[i]]==rk1[sa[i-1]]) rk[sa[i]]=tot;
            else rk[sa[i]]=++tot;
    }
    // cout<<n<<"\n";
    // for (int i=1;i<=n;i++) cout<<aa[i]<<" ";
    // cout<<"\n";

    // for (int i=1;i<=n;i++) cout<<sa[i]<<" ";
    // cout<<"\n";

    for (int i=1;i<=n;i++) rk[sa[i]]=i;
    for (int i=1;i<=n;i++) {
        if (rk[i]==1) continue;
        if (he[i-1]) he[i]=he[i-1]-1;
        int j=sa[rk[i]-1];
        while (j+he[i]<=n && i+he[i]<=n && aa[j+he[i]]==aa[i+he[i]]) he[i]++;
        // if (i==8) cout<<j<<" "<<i<<" "<<he[i]<<" ???\n";
    }
    // cout<<s2<<" "<<n<<" endl\n";
    // for (int i=1;i<=37;i++) cout<<i<<" "<<sa[i]<<" "<<he[sa[i]]<<" "<<he[37]<<" kelkel\n";
    for (int i=1;i<=n;i++) sum[i]=sum[i-1]+c[vis[sa[i]]];
    int ans=0;r=0;
    for (int i=2;i<=n;i++) {
        while (r && he[sa[q[r]]]>=he[sa[i]]) r--;
        if (r) L[i]=q[r]+1;
        else L[i]=1;
        q[++r]=i;
    }
    r=0;
    for (int i=n;i>1;i--) {
        while (r && he[sa[q[r]]]>=he[sa[i]]) r--;
        if (r) R[i]=q[r]-1;
        else R[i]=n;
        q[++r]=i;
    }

    for (int i=1;i<=n;i++) {
        if (aa[i]<'a' || aa[i]>'z') continue;
        // he[i] & he[sa[rk[i]+1]]
        // cout<<i<<" "<<c[vis[i]]<<" "<<P[i]<<" "<<he[i]<<" "<<he[sa[rk[i]+1]]<<" "<<sa[rk[i]-1]<<" bomb\n";
        if (max(he[i],he[sa[rk[i]+1]])!=P[i]) 
             ans=max(ans,c[vis[i]]*P[i]);
    }

    for (int i=2;i<=n;i++) {
        // cout<<i<<" "<<he[sa[i]]<<" "<<(sum[R[i]]-sum[max(0ll,L[i]-2)])<<" kqwe\n";
        // cout<<sa[i]<<" "<<sa[i-1]<<" "<<L[i]<<" "<<R[i]<<" oqwe\n"; 
        ans=max(ans,he[sa[i]]*(sum[R[i]]-sum[max(0ll,L[i]-2)]));
    }
    cout<<ans<<"\n";
    return 0;
}
```


有不懂的还请指出。

---

## 作者：wind_whisper (赞：4)

[更糟的阅读体验](https://blog.csdn.net/BUG_Creater_jie/article/details/122254012)
## $\text{Descripion}$
给你 $n$ 个字符串。每个字符串的成本都是 $c_i$。
定义字符串的函数，其中 $f(s)=\sum_{i=1}^n c_i \cdot p_{s,i} \cdot |s|$，$p_{s,i}$ 是 $s$ 在 $t_i$ 中出现的次数，$|s|$ 是字符串 $s$ 的长度。求**所有字符串函数 $f(s)$ 的最大值**。

注意字符串 $s$ **不一定**是 $t$ 中的某个字符串。
## $\text{Solution}$
据说用广义 SAM 的话就是板子了。
但是我并不会qwq。  

考虑使用 SA。  
先把所有串连起来，中间夹一些泥巴。  
后缀排序后先求出 $\operatorname{height}$。
每个后缀的价值定义为其所属串的价值，并求出价值的前缀和。  
然后如果选择区间 $[l,r]$ 的所有字符串，那么选择的价值就是：
$$(\min_{i=l+1}^{r}\operatorname{height}_i )\times sum_r-sum_{l-1}$$
因为贪心的考虑一定使这个串最长。   
那么我们悬线法求出每个 $height$ 作为最小值的有效区间，扫一遍取最大值即可。  
但这样是无法考虑这个串只出现一遍的情况的，这个串一定就是某个串本身，`map` 暴力判一下即可。
### update on 2022.1.1
感谢 [@望月Asta](https://www.luogu.com.cn/user/122520) 提供的hack，上面的算法会在下面这个数据出错：
```
2
od
iod
2 -1
ans:2
```
原因是之前 `map` 判整串判的过于草率了，正确的做法应该是记录每个串开头的位置 $pl$，然后看看 $height_{pl}$ 和 $height_{pl+1}$ 是否都小于该串长度。

## $\text{Code}$

```cpp
# include <bits/stdc++.h>
# include <bits/extc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

const int N=1e6+100;
const int mod=1e9+7;

int n,m,tot;
int sa[N],rk[N],id[N],oldrk[N],bel[N],len[N],p,cnt[1234567],a[N],l[N],r[N];
ll h[N],c[N];
void calc(){
  for(int k=0,i=1;i<=n;i++){
    if(k) --k;
    while(a[i+k]==a[sa[rk[i]-1]+k]) ++k;
    h[rk[i]]=k;
  }
  return;
}
bool jd[N];
ll ans,sum[N];
string s[N];
map<string,int>mp;

signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  m=read();
  for(int i=1;i<=m;i++){
    cin>>s[i];
    n=s[i].size();
    for(int j=0;j<n;j++) a[++tot]=s[i][j]-'a'+1,bel[tot]=i;
    a[++tot]=i+26;
    bel[tot]=i;jd[tot]=1;
    len[i]=n;
    mp[s[i]]++;
  }
  for(int i=1;i<=m;i++) c[i]=read();//ans=max(ans,c[i]*len[i]);
  for(int i=1;i<=m;i++) if(mp[s[i]]==1) ans=max(ans,c[i]*len[i]);
  n=tot;
  m+=26;
  for(int i=1;i<=n;i++) ++cnt[rk[i]=a[i]];
  for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
  for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
  for(int w=1;;w<<=1){
    p=0;
    for(int i=n;i>n-w;i--) id[++p]=i;
    for(int i=1;i<=n;i++){
      if(sa[i]>w) id[++p]=sa[i]-w;
    }
    memset(cnt,0,sizeof(cnt));
    memcpy(oldrk,rk,sizeof(rk));
    //for(int i=1;i<=n;i++) printf("%d ",id[i]);
    //putchar('\n');
    for(int i=n;i>=1;i--) ++cnt[rk[id[i]]];
    for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
    for(int i=n;i>=1;i--) sa[cnt[rk[id[i]]]--]=id[i];
    p=0;
    for(int i=1;i<=n;i++){
      if(oldrk[sa[i]]==oldrk[sa[i-1]]&&oldrk[sa[i]+w]==oldrk[sa[i-1]+w]) rk[sa[i]]=p;
      else rk[sa[i]]=++p;
    }
    m=p;
    //for(int i=1;i<=n;i++) printf("%d ",sa[i]);
    //putchar('\n');
    if(m==n) break;
  }
  calc();
  for(int i=1;i<=n;i++) sum[i]=sum[i-1]+c[bel[sa[i]]];  
  for(int i=1;i<=n;i++){
    l[i]=i;
    //printf("i=%d\n",i);
    while(l[i]>1&&h[l[i]-1]>=h[i]) l[i]=l[l[i]-1];
  }
  for(int i=n;i>=1;i--){
    r[i]=i;
    while(r[i]<n&&h[r[i]+1]>=h[i]) r[i]=r[r[i]+1];
  }
  //for(int i=1;i<=n;i++){
    //printf("i=%d pl=%d h=%lld l=%d r=%d sum=%lld tmp=%lld\n",
    //	   i,sa[i],h[i],l[i],r[i],sum[i],h[i]*(sum[r[i]]-sum[max(0,l[i]-2)]));
  //}
  for(int i=2;i<=n;i++){   
      ans=max(ans,h[i]*(sum[r[i]]-sum[max(0,l[i]-2)]));
  }
  printf("%lld\n",ans);
  return 0;
}
/*
5
bbbab
bbaab
bbbaa
bbabb
babba
3 -9 8 -3 9 
 */

```


---

## 作者：lfxxx (赞：2)

首先你发现一定是某个子串，不然贡献肯定是 $0$。

然后既然是子串，直接全部丢广义 SAM 上，一个节点除开字符串长度外的贡献为 $endpos$ 中字符串的贡献之和。

然后直接在 parent 树上 dp 统计出一个点除开自己字符串长度外的贡献再乘上这个点的字符串最大长度即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;;
struct SAM{
	int len,fa;
	int son[26];
}nd[maxn]; 
int tot,lst,q;
int dp[maxn];
void ins(char c){
    if(nd[lst].son[c-'a']!=0){
    	int q=nd[lst].son[c-'a'],v=lst;
        if(nd[q].len==nd[v].len+1){
        	lst=q;
        	return ;	
		}
        int nq=++tot;
        lst=nq;
        nd[nq]=nd[q];
        nd[nq].len=nd[v].len+1;
        nd[q].fa=nq;
        while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
        return ;
    }
    int u=++tot,v=lst;
	nd[u].len=nd[lst].len+1;
  	lst=u;
	while(v!=0&&nd[v].son[c-'a']==0) nd[v].son[c-'a']=u,v=nd[v].fa;
	if(v==0){
        nd[u].fa=1;
        return ;
    }else{
        int q=nd[v].son[c-'a'];
        if(nd[v].len+1==nd[q].len){
            nd[u].fa=q;
            return ;
        }else{
            int nq=++tot;
            nd[nq]=nd[q];
            nd[nq].len=nd[v].len+1;
            nd[u].fa=nq;
            nd[q].fa=nq;
            while(v!=0&&nd[v].son[c-'a']==q) nd[v].son[c-'a']=nq,v=nd[v].fa;
            return ;
        }
    }
    return ;
}
vector<int> E[maxn];
void init(){
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
    return ;
}
string t[maxn];
int c[maxn],n,ans;
void dfs(int u){
    for(int v:E[u]){
        dfs(v);
        dp[u]+=dp[v];
    }
    ans=max(ans,dp[u]*nd[u].len);
}
signed main(){
    ans=-1e18-114;
    lst=++tot;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i];
    for(int i=1;i<=n;i++){
        cin>>c[i];
        lst=1;
        for(char x:t[i]){
            ins(x);
            dp[lst]+=c[i];
        }
    }
    init();
    dfs(1);
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：快乐的大童 (赞：0)

~~隔壁 CF316G3 远比这题难吧，为什么那题 2400 这题 2700？~~

### 题目描述
有 $n$ 个字符串 $t_i$，第 $i$ 个字符串的价值为 $c_i$。现在想求一个字符串函数 $f(S)=\sum_{i=1}^n |S|\cdot c_i\cdot p_{S,t_i}$，其中 $p_{S,T}$ 表示字符串 $S$ 在 $T$ 中的出现次数。求 $f(S)$ 的最大值，$S$ 可以为空。

$n\le 10^5,\sum |t_i|\le 5\times10^5,|c_i|\le 10^7$。
### 分析
将 $n$ 个串用奇怪字符拼起来做后缀数组。那么一个子串在某个字符串中出现就相当于它是某个后缀的前缀。由于奇怪字符的存在，可以保证一个子串不会从一个字符串匹配到另一个字符串上。

对于每个属于字符串 $t_i$ 的后缀的开头，赋上权值 $c_i$，表示若该后缀和某子串匹配会对该子串有 $c_i$ 的权值。那么 $f(S)$ 就相当于 $S$ 能匹配上的后缀的权值和乘上 $|S|$。

由于 height 数组的性质，一个子串只会在 sa 数组上某个连续的区间出现，该串长度即为区间 height 最小值，权值就相当于区间和，做一遍前缀和即可。此时即便该子串出现区间的权值和是负数（子串长度永远非负），我们也可以通过取空串使得 $ans=0$，因此可以保证子串取可能最大值一定不劣。

那么做法就显然了，考虑每个 $height_i$ 的贡献区间的左右端点是左右第一个 $height_j<height_i$ 的 $j$ 的前/后一位，单调栈做即可。

特判单独取这 $n$ 个整串的情况，其中**特判某个整串是另一个整串的子串的情况**。我们只需要取出以该整串为开头的后缀（设该后缀开头为 $k$），看看 $height_k,height_{k+1}$ 的值是否都小于 $|t_i|$ 即可。

[code](https://codeforces.com/contest/616/submission/244904359)

---

## 作者：xtx1092515503 (赞：0)

首先，若我们需要的 $s$ 至少在某个串里出现了一次，则其一定是所有串中某些串的子串。于是我们建立广义SAM。

广义SAM中所有节点涵盖了所有 $n$ 个串的所有子串。于是我们只需要依次遍历所有节点，找到所有节点中最优的那一个节点即可。

考虑一个节点的贡献，即为其对应的 $\text{endpos}$ 集合中所有串的贡献。我们考虑将贡献计算公式 $\sum\limits_{i=1}^nc_i\times p_{s,i}\times|s|$ 拆开，拆成 $\Big(\sum\limits_{i=1}^n\sum\limits_{j=1}^{p_{s,i}}c_i\Big)|s|$。显然，对于某个固定的节点内的串的贡献，括号内的东西总是相等（$\text{endpos}$ 集合不变），影响其的只有 $|s|$。显然，当括号内的东西 $>0$ 时，$|s|$ 越大越好，因此此时就直接取 $|s|=len$ 即可。而当括号内的东西 $\leq0$ 时，显然无论 $|s|$ 怎么取，这一大坨东西最终的结果都 $\leq0$，一定不优于未在任何串内出现的 $s$，故直接跳过即可。

于是我们考虑括号里的东西。其就是对于 $i$ 串的每一次出现，都计入一次 $c_i$。于是就在 parent tree 上DP，求出 $f_i$ 表示上述括号内东西即可。

时间复杂度 $O(n|\Sigma|)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,cnt=1,S;
struct Suffix_Automaton{int ch[26],len,fa;}t[1000100];
int Add(int x,int c){
	if(t[x].ch[c]){
		int y=t[x].ch[c];
		if(t[y].len==t[x].len+1)return y;//(x,c) has been added into the tree already.
		int yy=++cnt;t[yy]=t[y];
		t[yy].len=t[x].len+1,t[y].fa=yy;
		for(;x&&t[x].ch[c]==y;x=t[x].fa)t[x].ch[c]=yy;
		return yy;
	}
	int xx=++cnt;t[xx].len=t[x].len+1;
	for(;x&&!t[x].ch[c];x=t[x].fa)t[x].ch[c]=xx;
	if(!x){t[xx].fa=1;return xx;}
	int y=t[x].ch[c];
	if(t[y].len==t[x].len+1){t[xx].fa=y;return xx;}
	int yy=++cnt;t[yy]=t[y];
	t[yy].len=t[x].len+1;
	t[y].fa=t[xx].fa=yy;
	for(;x&&t[x].ch[c]==y;x=t[x].fa)t[x].ch[c]=yy;
	return xx;
}
char s[500100];
vector<int>id[100100],v[1001000];
ll res,f[1001000];
void dfs(int x){for(auto y:v[x])dfs(y),f[x]+=f[y];}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",s),S=strlen(s);
		for(int j=0,las=1;j<S;j++)id[i].push_back(las=Add(las,s[j]-'a'));
	}
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		for(auto j:id[i])f[j]+=x;
	}
	for(int i=2;i<=cnt;i++)v[t[i].fa].push_back(i);
	dfs(1);
	for(int i=1;i<=cnt;i++)res=max(res,f[i]*t[i].len);
	printf("%lld\n",res);
	return 0;
}
```



---

## 作者：lory1608 (赞：0)

本题考查$parent$树的性质，直接在上面$dp$即可。

先建出$Trie$树，对于每个节点的价值，为经过他的串的价值之和，对于$Trie$树建立广义后缀自动机，如果你不会广义后缀自动机，可以移步 [P6139【模板】广义后缀自动机（广义SAM）](https://www.luogu.com.cn/problem/P6139) 。

本题建完广义后缀自动机后，$dp$一下，统计答案就$OK$了,$ans=\max\{dp[u]\times len[u],ans\}$。

**注意开$long\ long$**。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#define int long long
#define ll long long
#define ull unsigned long long
using namespace std;
inline int getint()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return (f==1)?x:-x;
}
const int maxn=1e6+5;
int val[maxn];
ll dp[maxn],ans;
struct Trie
{
	int tot;
	int ch[maxn][26];
	inline void insert(string s,int v)
	{
		int now=1;
		for(int i=0;i<s.size();++i)
		{
			if(!ch[now][s[i]-'a'])
			{
				ch[now][s[i]-'a']=++tot;
			}
			now=ch[now][s[i]-'a'];
			val[now]+=v;
		}
	}
}trie;
int last=1,tot=1,fa[maxn],now[maxn],p[maxn],sz,len[maxn];
struct edge
{
	int v,nxt;
	edge(){}
	edge(int vv,int nn){v=vv,nxt=nn;}
}e[maxn];
struct SAM
{
	int son[maxn][26],val[maxn];
	inline void insert(int c,int p)
	{
		int np=++tot;
		last=np,len[np]=len[p]+1;
		while(p&&!son[p][c])son[p][c]=np,p=fa[p];
		if(!p)fa[np]=1;
		else
		{
			int q=son[p][c];
			if(len[q]==len[p]+1)fa[np]=q;
			else
			{
				int nq=++tot;
				len[nq]=len[p]+1;
				memcpy(son[nq],son[q],sizeof(son[q]));
				fa[nq]=fa[q];
				fa[np]=fa[q]=nq;
				while(p&&son[p][c]==q)son[p][c]=nq,p=fa[p];
			}
		}
	}
}sam;
inline void add(int u,int v)
{
	e[++sz]=edge(v,p[u]);
	p[u]=sz;
}
inline void dfs1(int u)
{
	int temp=last;
	dp[last]=val[u];
	for(int i=0;i<=25;++i)
	{
		if(trie.ch[u][i])
		{
			sam.insert(i,temp);
			dfs1(trie.ch[u][i]);
		}
	}
}
inline void dfs(int u)
{
	for(int i=p[u];i!=-1;i=e[i].nxt)
	{
		int v=e[i].v;
		dfs(v);
		dp[u]+=dp[v];
	}
	ans=max(ans,dp[u]*len[u]);
}
int n;
char s[maxn];
vector<string>v;
signed main()
{
	memset(p,-1,sizeof(p));
	scanf("%d",&n);
	trie.tot=1;
	for(int i=1;i<=n;++i)
	{
		string s;
		cin>>s;
		v.push_back(s);
	}	
	for(int i=0;i<=n-1;++i)
	{
		int va=getint(); 
		string s=v[i];
		trie.insert(s,va);
	}
	dfs1(1);
	for(int i=2;i<=tot;++i)add(fa[i],i);
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}
```

---

