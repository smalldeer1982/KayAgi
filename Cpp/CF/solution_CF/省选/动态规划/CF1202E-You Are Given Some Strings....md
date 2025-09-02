# You Are Given Some Strings...

## 题目描述

You are given a string $ t $ and $ n $ strings $ s_1, s_2, \dots, s_n $ . All strings consist of lowercase Latin letters.

Let $ f(t, s) $ be the number of occurences of string $ s $ in string $ t $ . For example, $ f('\text{aaabacaa}', '\text{aa}') = 3 $ , and $ f('\text{ababa}', '\text{aba}') = 2 $ .

Calculate the value of $ \sum\limits_{i=1}^{n} \sum\limits_{j=1}^{n} f(t, s_i + s_j) $ , where $ s + t $ is the concatenation of strings $ s $ and $ t $ . Note that if there are two pairs $ i_1 $ , $ j_1 $ and $ i_2 $ , $ j_2 $ such that $ s_{i_1} + s_{j_1} = s_{i_2} + s_{j_2} $ , you should include both $ f(t, s_{i_1} + s_{j_1}) $ and $ f(t, s_{i_2} + s_{j_2}) $ in answer.

## 样例 #1

### 输入

```
aaabacaa
2
a
aa
```

### 输出

```
5
```

## 样例 #2

### 输入

```
aaabacaa
4
a
a
a
b
```

### 输出

```
33
```

# 题解

## 作者：万弘 (赞：12)

洛谷的$L^AT_EX$可能挂，请在[My blog](https://oierwanhong.cc/2020/04/18/CF1202E/)查看

## CF1202E

题意：给一个串$T$和$n$个串$s_i$.定义$f(T,s)$表示$s$在$T$中的出现次数。

求$\sum_{i=1}^n\sum_{j=1}^nf(T,s_i+s_j)$. 数据范围：$|T|,\sum_{i=1}|s_i|\le 2\times 10^5$

<!--more-->

解：考虑枚举划分点$x$，该点及之前为$s_i$,该点之后为$s_j$,统计一下$s_i,s_j$的数量$f1(x),f2(x+1)$然后乘法原理相乘即可。

具体如何统计？该问题等价于，给一个文本串和一些模式串，要对文本串的每个前缀求出有多少模式串是他的后缀（后面那个只要把串反转就好）
文本串长度至多2e5,模式串长度和至多2e5.  
对模式串建AC自动机，考虑fail指针指向的是根到当前串的最长后缀。而所求等价于为模式串的后缀的数量，因此通过fail求和即可。

时间复杂度为线性。
```
#define MAXN 400011
struct ACAM
{
    ll t[MAXN][26],val[MAXN],fail[MAXN],vis[MAXN];//val[u]表示点根到u的串的为模式串的后缀数量
    ll cnt=0;
    void insert(char* a,ll n)
    {
        ll u=0;
        for(ll i=1;i<=n;++i)
        {
            ll &v=t[u][a[i]-'a'];
            if(!v)v=++cnt;
            u=v;
        }
        ++val[u];
    }
    void build()//建AC自动机并求val
    {
        std::queue<ll>q;
        for(ll i=0;i<26;++i)
            if(t[0][i])q.push(t[0][i]);
        while(!q.empty())
        {
            ll u=q.front();q.pop();
            for(ll i=0;i<26;++i)
            {
                ll &v=t[u][i];
                if(v)fail[v]=t[fail[u]][i],val[v]+=val[fail[v]],q.push(v);
                else v=t[fail[u]][i];
            }
        }
    }
    void Query(char* a,ll n,ll f[])//求f
    {
        for(ll i=0;i<=cnt;++i)vis[i]=0;
        ll u=0;
        for(ll i=1;i<=n;++i)
        {
            u=t[u][a[i]-'a'];
            f[i]=val[u];
        }
    }
}ac,Rac;//ac自动机和反串的ac自动机
ll f1[MAXN],f2[MAXN];
char a[MAXN],b[MAXN];
int main()
{
    scanf("%s",a+1);
    ll n=read(),la=strlen(a+1);
    while(n--)
    {
        scanf("%s",b+1);
        ll lb=strlen(b+1);
        ac.insert(b,lb);//插入ac自动机
        std::reverse(b+1,b+lb+1);Rac.insert(b,lb);
    }
    ac.build();Rac.build();
    ac.Query(a,la,f1);std::reverse(a+1,a+la+1);Rac.Query(a,la,f2);
    ll ans=0;
    for(ll i=1;i<=la;++i)
	{
		ans+=f1[i]*f2[la-i];//注意这里的f2没有反转，如果反转了就应该是f1[i]*f2[i+1]
	}
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：唐一文 (赞：10)

首先记 $f_i$ 为以 $i$ 开头的字符串个数，$g_i$ 为以 $i$ 结尾的字符串个数，那么答案为 $\sum_{i=1}^{|t|}g_if_{i+1}$。，考虑如何计算 $f_i$ 和 $g_i$。

根号分治。记一个阈值 $B$，长度大于 $B$ 的串不超过 $\dfrac{\sum|s|}{B}$ 个，直接暴力跑匹配，将匹配上的字符串开头的 $f_i$ 和结尾的 $g_i$ 加一。

然后枚举 $t$ 中长度为 $1\sim B$ 的子串，对每个子串统计出所有长度不大于 $B$ 的串中与其相同的个数，将该子串开头的 $f_i$ 和结尾的 $g_i$ 加上个数。

可以用一些字符串算法优化匹配和找相同字符串的过程，复杂度为 $O(\dfrac{\sum|s|}{B}|t|+B|t|)$，当 $B=\sqrt{\sum|s|}$ 时最优。

这里用的是哈希。不过这题把单哈希几个常见的模数卡掉了，所以用了双哈希。

[Code](https://www.luogu.com.cn/paste/7mn3mza5)

---

## 作者：极寒神冰 (赞：6)

由于直接计算每一对$s_i+s_j$的出现次数并不好做，考虑枚举它们分割的位置（$s_i$结束$s_j$开始处）来计算总数。

因此任何在分割处结束的$s_i$都可以与从这里开始的$s_j$配对。

所以说我们只需要对每一个后缀计算从这里开始的字符串$s_i$的数量，以及对每一个前缀计算从这里结束的字符串$s_i$的数量。计算前缀可以通过反转$t$和所有的$s_i$转化为计算后缀。

所以我们需要对于每个位置$pos$计算从$pos$开始或结束的字符串个数。个人的做法是SAM，但官方题解有一种有趣的根号分治做法。

先确定一个阙值$MAG$。然后将字符串分为长或短两类：若$|s_i|\leq MAG$就当做短的，否则当做长的。显然不会有超过$\frac{\sum|s_i|}{MAG}$个长字符串。对于这些长字符串可以用Z函数或者前缀函数找到它的所有出现。这部分的时间复杂度为$O(\frac{\sum |s_i|}{MAG}+\sum |s_i|)$。

然后对于短的字符串考虑直接建一棵Trie。这棵Trie将会有$O\left(\sum |s_i| \right)$个点，但是最大深度为$MAG$。所以可以对于每个$pos$向下移动遍历Trie，同时计算出现次数，这只使用了$s[pos\ldots (pos+MAG)]$这部分子串。所以这部分的时间复杂度为$O(|t|\cdot MAG)$。

所以当$MAG=\sqrt{\sum |s_i|}$时，总时间复杂度为$O\left(\sum |s_i|+|t|\sqrt{\sum |s_i|} \right)$。这没有使用任何字符串数据结构。



然后讲一下线性时间复杂度的SAM做法。

对于$t$和$\operatorname{reverse}(t)$建出SAM，然后对于每个$s_i$和$\operatorname{reverse}(s_i)$在SAM上跑一遍，并对于它的结束位置的整个子树打个标记。最后直接计算每个位置存在的字符串数量就可以得到答案。

```cpp
string str;
int t[222222];

int n,lent;
struct SAM
{
    struct node
    {
        int len,nxt,son[26];
    }a[444444];
    int ans[444444],edp[444444],cnt[444444];
    int lst,tn;
    vector<int>e[444444];
    inline void init_SAM()
    {
        tn=lst=1; 
    }
    void extend_SAM(int c)
    {
        int cur=++tn,p=lst;
        a[cur].len=a[p].len+1;edp[cur]=a[p].len;
        for(;p&&!a[p].son[c];p=a[p].nxt) a[p].son[c]=cur;
        if(!p) a[cur].nxt=1;
        else
        {
            int v=a[p].son[c];
            if(a[v].len==a[p].len+1) a[cur].nxt=v;
            else
            {
                int x=++tn;a[x]=a[v];
                a[x].len=a[p].len+1;edp[x]=-1;
                for(;p&&a[p].son[c]==v;p=a[p].nxt)a[p].son[c]=x;
                a[cur].nxt=a[v].nxt=x;
            }
        } 
        lst=cur;
    }
    void solve(const string &s)
    {
        int p=1,len=(int)s.size(),x;
        R(i,0,len-1) 
        {
            x=s[i]-'a';
            if(!a[p].son[x]) return;
            p=a[p].son[x];
        }
        ++cnt[p];
    }
    void dfs(int u)
    {
        
        if(~edp[u]) ans[edp[u]]=cnt[u];
        for(int v:e[u]) cnt[v]+=cnt[u],dfs(v);
    }
    void mian()
    {
        R(i,2,tn) e[a[i].nxt].pb(i);
        dfs(1);
    }
}SAM1,SAM2;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    SAM1.init_SAM(),SAM2.init_SAM();
    cin>>str>>n;lent=str.size();
    R(i,0,lent-1) t[i]=str[i]-'a';
    R(i,0,lent-1) SAM1.extend_SAM(t[i]);
    L(i,0,lent-1) SAM2.extend_SAM(t[i]);    
    R(i,1,n)
    {
        cin>>str;
        SAM1.solve(str);
        reverse(str.begin(),str.end());
        SAM2.solve(str);
    }
    SAM1.mian();
    SAM2.mian();
    ll ans=0;
    R(i,0,lent-2) ans+=1ll*SAM1.ans[i]*SAM2.ans[lent-i-2];
    cout<<ans;
}
```

---

## 作者：Alex_Wei (赞：5)

> [CF1202E You Are Given Some Strings... 题目传送门](https://www.luogu.com.cn/problem/CF1202E)。

> 题意简述：给出 $t$ 与 $s_{1,2,\cdots,n}$。求对于所有 $i,j\in[1,n]$，$s_i+s_j$ 在 $t$ 中出现次数之和。

[在我的 cnblogs 内查看](https://www.cnblogs.com/alex-wei/p/CF1202E.html)。

---

如果只有 $s_i$ 那么显然是 ACAM 的板子题，对每个位置 $p$ 记录它的前缀的所有后缀能与多少 $s_i$ 相等，即为 $a_p$（即有多少 $i$ 满足 $t[p-|s_i|+1:p]=s_i$。实际上就是该位置前缀 $t[1:p]$ 在 ACAM 上跑到的位置在 fail 树上与根的路径上有多少 $s_i$ 的终止节点）。如果再加上 $s_j$，就要求一个位置的后缀有多少与 $s_j$ 相等的前缀，即为 $b_p$。那么可以建 $s$ 所有反串的 ACAM，再用 $t$ 的反串上去跑即可。根据乘法原理，答案为 $\sum a_ib_{i+1}$。

时间复杂度为字符总长度乘以字符集大小。

```cpp
/*
	Powered by C++11.
	Author : Alex_Wei.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) x.begin(),x.end()
#define rev(x) reverse(all(x))

const int N=2e5+5;
const int S=26;

struct ACAM{
	int cnt,f[N],son[N][S],ed[N];
	void ins(string s){
		int p=0;
		for(char it:s){
			if(!son[p][it-'a'])son[p][it-'a']=++cnt;
			p=son[p][it-'a'];
		} ed[p]++;
	} void build(){
		queue <int> q;
		for(int i=0;i<26;i++)if(son[0][i])q.push(son[0][i]);
		while(!q.empty()){
			int t=q.front(); q.pop();
			for(int i=0;i<26;i++)
				if(son[t][i])f[son[t][i]]=son[f[t]][i],q.push(son[t][i]);
				else son[t][i]=son[f[t]][i];
			ed[t]+=ed[f[t]];
		}
	}
}a,b;

ll n,ans,s[N];
string t;

int main(){
	cin>>t>>n;
	for(int i=1;i<=n;i++){
		string s; cin>>s;
		a.ins(s),rev(s),b.ins(s);
	} a.build(),b.build();
	for(int i=1,p=0;i<=t.size();i++)
		p=a.son[p][t[i-1]-'a'],s[i]=a.ed[p];
	for(int i=t.size(),p=0;i;i--)
		p=b.son[p][t[i-1]-'a'],ans+=s[i-1]*b.ed[p];
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：_edge_ (赞：4)

诶我就不用 AC 自动机，我就不用 SA，我就要哈希！！

当然问题还要稍微转换一下，直接暴力做不太现实。

看到这种总长度的有限制的一般就可以进行根号分治了。

先不管题目里面要求的东西。

这里的 $|s|$ 表示字符串 $s$ 的长度。

首先，对于 $|s_i| \ge B$ 的，暴力在 $t$ 上面匹配，匹配过程可以用哈希实现，复杂度是 $O(\dfrac{\sum |s_i|}{B} \times |t|)$ 的。

然后对于小的，可以枚举 $t$ 和小的字符串长度，开个哈希表记下来匹配即可，复杂度 $O(|t| \times B)$，由于长度均同阶，所以 $B$ 取 $300$ 左右就可以，当然由于哈希表常数原因，块长可以调小，这是次要的。

然后由于 `__int128` 会被卡常，所以直接双模哈希，自然溢出配合单模哈希，这样就能通过这个题了。

哈希表内部能存点东西，所以不用担心哈希表里面找错了元素。

设 $b_i$ 为 $t_i$ 开头和 $s_i$ 匹配的数量。

然后我们对于 $[l,r]$ 能匹配 $b_l$ 个字符串之后，他对于答案的贡献就是 $b_l \times b_{r+1}$ 了。

然后就可以过掉这道题了，稍微有点小卡常。

缺省源删了，要看完整代码的可以去 CF 上搜 fzx。

```cpp
#include <bits/stdc++.h>
#define int unsigned long long
#define pb push_back
using namespace std;
const int B=85;
const int INF=2e5+5;
const int base=233;
const int base1=191;
const int Mod=1e9+7;
string s1;
int n,ba[INF],hash1[INF],b[INF],ans,q,vis2[INF],vis3[INF],ba1[INF],hash2[INF];
string s3[INF];
int mul(long long a,long long b,long long mod) {
    long long d=(long double)a/mod*b;
    long long ans=(unsigned long long)a*b-(unsigned long long)d*mod;
    return (ans+mod)%mod;
}
const int Mod3=3000017;
struct hash2{
	vector <int> h2[Mod3+6],h3[Mod3+6];
	void ins(int x) {
		int xx=x%Mod3,len=h2[xx].size();
		for (int i=0;i<len;i++) 
			if (h2[xx][i]==x) {h3[xx][i]++;return ;}
		h2[xx].pb(x);
		h3[xx].pb(1);
	}
	int query(int x) {
		int xx=x%Mod3,len=h2[xx].size();
		for (int i=0;i<len;i++) 
			if (h2[xx][i]==x) return h3[xx][i];
		return -1;
	}
}HH;
//unordered_map <int,int> Map; // 等会在说 
int Get(int l,int r) {
	return (hash1[r]-hash1[l-1]*ba[r-l+1]);
}
int Get2(int l,int r) {
    return (hash2[r]-hash2[l-1]*ba1[r-l+1]%Mod+Mod)%Mod;
}
signed main()
{
    // freopen("data.in","r",stdin);
	cin>>s1>>q;
	int n=s1.size();
	s1=" "+s1;
	ba[0]=1;ba1[0]=1;
	for (int i=1;i<=n;i++) ba[i]=ba[i-1]*base;
    for (int i=1;i<=n;i++) ba1[i]=ba1[i-1]*base1%Mod;
	for (int i=1;i<=n;i++)
		hash1[i]=hash1[i-1]*base+s1[i],
        hash2[i]=hash2[i-1]*base1%Mod+s1[i],hash2[i]%=Mod;
	
	for (int i=1;i<=q;i++) {
		string s2;cin>>s2;s3[i]=s2;
		if (s2.size()>B) {
			int H=0,H1=0;
			for (char x:s2)
				H=(H*base+x);
            for (char x:s2)
				H1=(H1*base1%Mod+x)%Mod;
			vis2[i]=H;vis3[i]=H1;
			for (int j=1;j<=n;j++) {
				int r=j+s2.size()-1;
				if (r>n) break;
				if (Get(j,r)==H && Get2(j,r)==H1) b[j]++;
			}
		}
		else {
			int H=0;
			for (char x:s2)
				H=(H*base+x);
//			Map[H]++;
			HH.ins(H);
		}
	}
	
	for (int i=n;i;i--) {
		for (int j=1;j<=B;j++) {
			if (i+j-1>n) continue;
			int xx=Get(i,i+j-1);
			int qq=HH.query(xx);
			if (qq!=-1) 
				b[i]+=qq,ans+=qq*b[i+j];
		}
	}
	
	for (int i=1;i<=q;i++) {
		if (s3[i].size()>B) {
			int H=vis2[i],H1=vis3[i];
			for (int j=1;j<=n;j++) {
				int r=j+s3[i].size()-1;
				if (r>n) break;
				if (Get(j,r)==H && Get2(j,r)==H1) ans+=b[r+1];
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：良心WA题人 (赞：4)

# 原题连接

[洛谷的](https://www.luogu.com.cn/problem/CF1202E)

[CF的](http://codeforces.com/problemset/problem/1202/E)

[VJ的](https://vjudge.net/problem/CodeForces-1202E)

# 问题描述
给定出一大堆字符串，要求任意两个字符串拼在一起在 t 串中出现的个数之和。有多任意呢？只要满足这两个字符串都是这一大堆的字符串中的就行（拼起来一样的两组算两个，同一个字符串也可以拼起来）。

~~说实话，我这概括的描述比洛谷的描述还多~~

# 解决问题
看到一大堆字符串要匹配，二话不说，先看漏要两个字符串拼在一起的条件，跑一遍 AC 自动机。那么两个字符串拼到一起呢？反着跑一遍再接上不就行了嘛。怎么接上呢？记录正着匹配和反着匹配在 i 结束匹配的数量，那就是小学数学——乘法原理了。注意，这个题要用优化的 AC 自动机，否则你就 TLE 了。

# 丑陋代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=2e5+4;
string s[NN];
int ne[NN][2],st[NN][30][2],sum[NN][2],res[NN][2],idx[2],len;
void insert(string x,int k)
{
	int len=x.size(),u=0;
	for(int i=0;i<len;i++)
	{
		if(!st[u][x[i]-'a'][k])
			st[u][x[i]-'a'][k]=++idx[k];
		u=st[u][x[i]-'a'][k];
	}
	sum[u][k]++;
}
void before_ACAM()
{
	queue<int>q;
	for(int k=0;k<2;k++)
	{
		for(int i=0;i<26;i++)
			if(st[0][i][k])
				q.push(st[0][i][k]);
		while(q.size())
		{
			int t=q.front();
			q.pop();
			for(int i=0;i<26;i++)
			{
				int u=st[t][i][k];
				if(u)
				{
					ne[u][k]=st[ne[t][k]][i][k];
					sum[u][k]+=sum[ne[u][k]][k];
					q.push(u);
				}
				else
					st[t][i][k]=st[ne[t][k]][i][k];
			}
		}
	}
}
void ACAM(string t,int k)
{
	int u=0;
	for(int i=0;i<len;i++)
	{
		u=st[u][t[i]-'a'][k];
		res[i][k]=sum[u][k];
	}
}
int main()
{
	string t;
	int n;
	cin>>t>>n;
	len=t.size();
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
		insert(s[i],0);
		reverse(s[i].begin(),s[i].end());
		insert(s[i],1);
	}
	before_ACAM();
	ACAM(t,0);
	reverse(t.begin(),t.end());
	ACAM(t,1);
	long long ans=0;
	for(int i=0;i<len-1;i++)
		ans+=1ll*res[i][0]*res[len-i-2][1];
	cout<<ans;
	return 0;
}
```

---

## 作者：Engulf (赞：2)

考虑在 $t$ 上枚举 $s_i + s_j$ 的分割点 $x$，求出有多少个 $s$ 是 $t_{1,x}$ 的后缀，记为 $f_x$，再求出有多少个 $s$ 是 $t_{x + 1, |t|}$ 的前缀，记为 $g_x$，根据乘法原理，最终的答案就是 $\sum\limits_{i = 1}^{|t| - 1} f_i \cdot g_{i + 1}$。

考虑怎么求出 $f$ 和 $g$。不妨建出所有 $s$ 的 AC 自动机，思考匹配的过程。$t$ 在 AC 自动机上跑，相当于不断地舍去一些前缀，使得根到当前这个节点（记为 $p$）的字符串能够匹配到新的这个字符。

也就是说，根到 $p$ 这个字符串就是当前枚举的 $t$ 的前缀的最长的一个后缀。根据 fail 指针的性质，$p$ 的 fail 所在的那个字符串也一定出现在了这个后缀上，可能造成贡献。

所以最终的做法就是，每插入一个字符串，在终止节点处记录出现次数。构建 AC 自动机时，累加 fail 处的出现次数。

上面说的是 $f$ 的求法，$g$ 的话只要把字符串全部反转过来做就行了。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int tr[N][26], idx, fail[N], cnt[N];

void insert(string s) {
    int p = 0;
    for (auto c: s) {
        if (!tr[p][c - 'a']) tr[p][c - 'a'] = ++idx;
        p = tr[p][c - 'a'];
    }
    cnt[p]++;
}

void build() {
    queue<int> q;
    for (int i = 0; i < 26; i++) if (tr[0][i]) q.push(tr[0][i]);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < 26; i++)
            if (tr[u][i]) {
                fail[tr[u][i]] = tr[fail[u]][i];
                cnt[tr[u][i]] += cnt[fail[tr[u][i]]];
                q.push(tr[u][i]);
            } else
                tr[u][i] = tr[fail[u]][i];
    }
}

int f[N], g[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<string> s(n);
    for (auto &str: s) cin >> str, insert(str);
    build();
    int p = 0;
    for (int i = 0; i < t.size(); i++) {
        p = tr[p][t[i] - 'a'];
        f[i] = cnt[p];
    }
    for (auto &str: s) reverse(str.begin(), str.end());
    memset(tr, 0, sizeof tr);
    memset(fail, 0, sizeof fail);
    memset(cnt, 0, sizeof cnt);
    idx = 0;
    for (auto str: s) insert(str);
    build();
    p = 0;
    for (int i = t.size() - 1; ~i; i--) {
        p = tr[p][t[i] - 'a'];
        g[i] = cnt[p];
    }
    ll ans = 0;
    for (int i = 0; i < t.size() - 1; i++)
        ans += 1ll * f[i] * g[i + 1];
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：intel_core (赞：2)

如果直接求和，$s_i+s_j$ 的组合有 $O(n^2)$ 种，直接硬干极为困难。

运用算两次的想法，转而考虑 $s_i,s_j$ 之间的分割位置 $k$。

转化之后，只需统计多少个模板串是 $t_1t_2\cdots t_k$ 的后缀及多少个模板串是 $t_{k+1}t_{k+2}\cdots t_n$ 的前缀即可。

设 $f_k$ 表示是 $t_1t_2\cdots t_k$ 的后缀的模板串的个数。

对模板串建 $\text{AC}$ 自动机，找到当前自动机上对应的节点；一直沿着 $\text{fail}$ 指针跳，此时 $f_k$ 为所有跳到的节点上以这些节点结尾的模板串的个数。

前缀和后缀的统计方法是一样的，把文本串和模板串翻转一下就可以了。

最后把每个位置的贡献加一下就好了，复杂度 $O(26n)$。



---

## 作者：pipiispig (赞：2)

题很有趣呢，其实也很简单，把模式串和匹配串正着跑一边Ac automaton再用他们的反串跑一次，然后一边求fail指针一边计数，最后匹配一次以及乘法原理就可以ac了；
```
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int N = 2 * 1e5 + 10;
char s[N], t[N];
int trie[N][26][2], tot[2], size[N][2];
inline void insert(char *a, int len, bool k) {
    int p = 0;
    for (int i = 0; i < len; i++) {
        int c = a[i] - 'a';
        if (!trie[p][c][k])
            trie[p][c][k] = ++tot[k];
        p = trie[p][c][k];
    }
    size[p][k]++;
}
int fail[N][2], num[N][2];
inline void bfs() { 
	queue<int> q;
    for (int k = 0; k <= 1; k++) {
        for (int i = 0; i < 26; i++)
            if (trie[0][i][k])
                q.push(trie[0][i][k]);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                int v = trie[x][i][k];
                if (v) {
                    fail[v][k] = trie[fail[x][k]][i][k];
                    size[v][k] += size[fail[v][k]][k];
                    q.push(v);
                } else
                    trie[x][i][k] = trie[fail[x][k]][i][k];
            }
        }
    }
}
inline void cale(char *a, int len, int k) {
    int p = 0;
    for (int i = 0; i < len; i++) {
        p = trie[p][a[i] - 'a'][k];
        num[i][k] = size[p][k];
    }
}
int n;
long long ans;
int main() {
    scanf("%s", &s);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s", &t);
        int len = strlen(t);
        insert(t, len, 1);
        reverse(t, t + len);
        insert(t, len, 0);
    }
    bfs();
    int len = strlen(s);
    cale(s, len, 1);
    reverse(s, s + len);
    cale(s, len, 0);
    for (int i = 0; i < len; i++) ans += (long long)(num[i][1]) * num[len - i - 2][0];
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：qiyue7 (赞：1)

难度一般的字符串题目...   看到这种两串拼接的题目一般情况下会先考虑是否能通过对原序列进行dp或计算得到答案，那么这题答案还是比较显然的，即枚举每个切分点两端的标记点的个数乘起来加和就可以得到答案了

每个前缀的标记点个数即为其fail指针上所有的标记点数量的和，SAM正向递推预处理一下，然后正反各做一遍预处理再乘起来就是答案。


AC代码：

```java
import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class Main {
    static String pp[];
    static String s;
    static long prefix[], suffix[];
    static int n;
    static void solve(long res[])
    {
        SAM1 sam=new SAM1();
        sam.init(410000,26);
        for(int i=0;i<s.length();++i)
        sam.insert(s.charAt(i) - 'a');
        sam.topo();
        SAM_node k = sam.root;
        for (int i = 1; i <= n; ++i)
        {
            k = sam.root;
            for (int j=0;j<pp[i].length();++j)
            if (k!=null)
                k = k.next[pp[i].charAt(j) - 'a'];
            if (k!=null)
                k.times++;
            StringBuilder sp=new StringBuilder(pp[i]);
            sp.reverse();
            pp[i]=sp.toString();
        }
        int cnt = sam.cur;
        for (int i = 1; i < cnt; ++i)
            sam.pool[i].times += sam.pool[i].pre.times;
        k = sam.root;
        for (int i = 0; i < s.length(); ++i)
        {
            k = k.next[s.charAt(i) - 'a'];
            res[i + 1] = k.times;
        }
    }
    public static InputReader in = new InputReader(System.in);
    public static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static void main(String[] args)
    {
        prefix=new long[210000];
        suffix=new long[210000];
        long suffix2[]=new long[210000];
        Arrays.fill(suffix2,0);
        Arrays.fill(prefix,0);
        Arrays.fill(suffix,0);
        pp=new String[210000];
        s=in.next();
        n=in.nextInt();
        for(int i=1;i<=n;++i)
            pp[i]=in.next();
        solve(prefix);
        StringBuilder sp=new StringBuilder(s);
        sp.reverse();
        s=sp.toString();
        solve(suffix);

        for (int i = 1; i <= s.length(); ++i)
            suffix2[i]=suffix[s.length()-i+1];
        long ans = 0;
        for (int i = 1; i < s.length(); ++i)
            ans += prefix[i] * suffix2[i + 1];
        out.println(ans);
        out.flush();
        out.close();
    }
}
class SAM_node
{
    SAM_node pre,next[];
    int step;
    long times;
    SAM_node(int sigma)
    {
        times=0;
        next=new SAM_node[sigma];
        step=0;
        pre=null;
    }
}
class SAM1
{
    SAM_node SAM_pool[],root,last;
    int d[];
    SAM_node pool[];
    int cur;
    int sigma;
    void topo() {
        // 求出parent树的拓扑序
        int cnt = cur;
        int maxVal = 0;
        Arrays.fill(d, 0);
        for (int i = 1; i < cnt; i++) {
            maxVal = Math.max(maxVal, SAM_pool[i].step);
            d[SAM_pool[i].step]++;
        }
        for (int i = 1; i <= maxVal; i++)
            d[i] += d[i - 1];
        for (int i = 1; i < cnt; i++)
            pool[d[SAM_pool[i].step]--] = SAM_pool[i];
        pool[0] = root;
    }
    void init(int a,int b)
    {
        d=new int[a];
        pool=new SAM_node[a];
        SAM_pool=new SAM_node[a];
        SAM_pool[0]=new SAM_node(b);
        sigma=b;
        root=last=SAM_pool[0];
        cur=1;
    }
    void insert(int w)
    {
        SAM_node p=last;
        SAM_pool[cur]=new SAM_node(sigma);
        SAM_node np=SAM_pool[cur];
        last=np;
        cur++;
        np.step=p.step+1;
        while (p!=null && p.next[w]==null)
        {
            p.next[w]=np;
            p = p.pre;
        }
        if(p==null)
        {
            np.pre=root;
        }
        else
        {
            SAM_node q=p.next[w];
            if(p.step+1==q.step)
                np.pre=q;
            else {
                SAM_node nq = SAM_pool[cur++] = new SAM_node(sigma);
                nq.next = Arrays.copyOf(q.next, sigma);
                nq.step = p.step + 1;
                nq.pre = q.pre;
                q.pre = nq;
                np.pre = nq;
                while (p != null && p.next[w]==(q)) {
                    p.next[w] = nq;
                    p = p.pre;
                }
            }
        }
    }
}
class InputReader{
    private final static int BUF_SZ = 65536;
    BufferedReader in;
    StringTokenizer tokenizer;
    public InputReader(InputStream in) {
        super();
        this.in = new BufferedReader(new InputStreamReader(in),BUF_SZ);
        tokenizer = new StringTokenizer("");
    }
    public boolean hasNext() {  //处理EOF
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
                String line = in.readLine();
                if(line == null) return false;
                tokenizer = new StringTokenizer(line);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return true;
    }
    public String next() {
        while (!tokenizer.hasMoreTokens()) {
            try {
                tokenizer = new StringTokenizer(in.readLine());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        return tokenizer.nextToken();
    }
    public int nextInt() {
        return Integer.parseInt(next());
    }
    public long nextLong()
    {
        return Long.parseLong(next());
    }
}
```


---

## 作者：Reunite (赞：0)

## 一
---

对着式子硬想很久无果，考虑经典拆贡献：枚举断点。

假如我们能够统计出，在文本串中 $[1,i]$ 且以 $i$ 结尾能匹配的所有模式串个数为 $s1_i$，$(i,m]$ 且以 $i+1$ 开头能匹配的所有模式串个数为 $s2_{i+1}$，那么答案显然为 $\sum\limits_{i=1}^{m-1} s1_i\cdot s2_{i+1}$。简单乘法原理即可解释。

因为求出 $s2$ 与求出 $s1$ 本质相同，这里我们只讨论如何求得 $s1$。根据套路，我们讲所有模式串建成 ACAM，顺便构建出 fail 树，在所有模式串结尾的地方打上标记。在 ACAM 上跑文本串，假设当前我们处理到了文本串的第 $i$ 个位置，目前跑到了 ACAM 上的 $u$ 节点，那么此时我们不断在 fail 树上跳父边，一直到根的所有节点的标记之和就是 $s1_i$ 的值。换句话说，$s1_i$ 就是从根到 $u$ 的祖孙链上的权值和。

因为是静态的，所以根本不需要数据结构，也不需要真正建出 fail 树，在建 ACAM 的同时顺便记录标记的前缀和即可，BFS 建自动机的顺序也保证了正确性。

$s2$ 的求法与 $s1$ 相同，具体地，只需要把所有串的反串重新做一遍即可。

## 二
---

时间复杂度为 $O(|t|+n+|s||\sum|)$。瓶颈在建 ACAM。

```cpp

int n,m;
char c[200005];
char t[200005];
int s1[200005];
int s2[200005];

struct ACAM{
	int tot;
	int cnt[200005];
	int son[200005][26];
	int fail[200005];
	vector <int> g[200005];
	
	inline void insert(){
		int len=strlen(t+1),u=0;
		for(int i=1;i<=len;i++){
			if(!son[u][t[i]-'a']) son[u][t[i]-'a']=++tot;
			u=son[u][t[i]-'a'];
		}
		cnt[u]++;
		return ;
	}
	
	inline void build(int s[]){
		queue <int> q;
		for(int i=0;i<26;i++)
			if(son[0][i]) q.push(son[0][i]);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int i=0;i<26;i++){
				int v=son[u][i];
				if(!v) son[u][i]=son[fail[u]][i];
				else fail[v]=son[fail[u]][i],q.push(v),cnt[v]+=cnt[fail[v]];
			}
		}
		int u=0;
		for(int i=1;i<=m;i++) u=son[u][c[i]-'a'],s[i]=cnt[u];

		return ;
	}

}a1,a2;

int main(){
	scanf("%s",c+1);
	m=strlen(c+1);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",t+1);
		int len=strlen(t+1);
		a1.insert();
		reverse(t+1,t+1+len);
		a2.insert();
	}
	a1.build(s1);
	reverse(c+1,c+1+m);
	a2.build(s2);
	ll ans=0;
	for(int i=1;i<=m;i++) ans+=1ll*s1[i]*s2[m-i];
	printf("%lld\n",ans);

	return 0;
}

```

---

## 作者：Pwtking (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1202E)

考虑在文本串上枚举每一个中间点作为 $s_i$ 和 $s_j$ 的分界点，所以 $s_i$ 就是文本串分界点左边（以下简称左文本串）的后缀，$s_j$ 就是文本串分界点右边（以下简称右文本串）的前缀。若将 ACAM 上的某个节点设为 $a$，它的 fail 节点设为 $b$，则根到 $b$ 所代表的字符串一定是根到 $a$ 所代表的字符串的后缀，所以我们可以在从左到右进行文本串查询操作的时候，把每个开始向上跳 fail 指针的起点作为分界点，那么这个点能向上跳到的终止结点的个数就是以该起点为结尾的后缀个数。

处理出每个分界点情况下的 $s_i$ 个数之后，因为我们接下来要求的是前缀，所以我们再反向建一次 ACAM，再和求后缀的流程一样再跑一次即可。

---

## 作者：_HL_ (赞：0)

似乎题解区还没这个做法

首先有个蛮经典的性质 对于互不相同的 $T_1\dots T_n$ 在 $S$ 中的出现位置量级是 $O(|S|\sqrt{\sum T_i})$ 的

证明的话 考虑 $T$ 与 $S[1,i]$ 的后缀的相同情况 

由于 $T$ 中串不同 所以匹配长度只能是 $1,2,3,\dots i$ 总和是平方量级的 所以只能有 $T$ 总长根号量级

所以总共的匹配次数是每个前缀的后缀与 $T$ 匹配成功的次数和 是 $|S|\sqrt{\sum |T_i|}$ 的

回到这道题 我们考虑如果知道每个串 $T_i$ 在 $S$ 中所有出现位置后如何解决此问题

我们记录一个数组 给每个串所有出现开头位置都 $+1$ 然后进行查询 每个串查所有出现开头位置减去 $|T_i|$ 的位置的值加到答案中即可 思路有点像点分治的处理过程

实现上可以用AC自动机 把所有 $T_i$ 插进AC自动机 顺便完成了去重 记录一个 nxt 数组 处理 fail 树上上一个是完整串的位置 然后让 $S$ 在自动机上跑 跳所有 nxt 统计答案即可

总复杂度是 AC自动机的常规复杂度和 $O(|S|\sqrt{\sum |T_i|})$ 的

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int ll
#define pii pair<int,int>
#define fi first
#define se second
#define mk make_pair
#define pb emplace_back
const int N=2e5+7;
int a[N],ANS;
struct AC
{
	signed d[N][26],tot,fail[N],len[N],nxt[N];
	int v[N];
	void ins(string &s,int n)
	{
		int x=0;
		for(int i=1;i<=n;i++)
		{
			int c=s[i]-'a';
			if(!d[x][c])d[x][c]=++tot;
			x=d[x][c];
		}
		v[x]++,len[x]=n;
	}
	void build()
	{
		queue<int>q;
		for(auto y:d[0])if(y)q.push(y);
		while(!q.empty())
		{
			int x=q.front();
			q.pop();
			nxt[x]=v[x]?x:nxt[fail[x]];
			for(int i=0;i<26;i++)
			{
				if(d[x][i])fail[d[x][i]]=d[fail[x]][i],q.push(d[x][i]);
				else d[x][i]=d[fail[x]][i];
			}
		}
	}
	void solve(string &s,int n)
	{
		for(int i=1,x=0;i<=n;i++)
		{
			int c=s[i]-'a';
			x=d[x][c];
			int y=nxt[x];
			while(y)
			{
				a[i]+=v[y];
				y=nxt[fail[y]];
			}
		}
		for(int i=1,x=0;i<=n;i++)
		{
			int c=s[i]-'a';
			x=d[x][c];
			int y=nxt[x];
			while(y)
			{
				ANS+=a[i-len[y]]*v[y];
				y=nxt[fail[y]];
			}
		}
	}
}ac;
inline int lth(string &s)
{
	s=' '+s;
	return s.size()-1;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	string s;
	cin>>s;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		ac.ins(s,lth(s));
	}
	ac.build();
	ac.solve(s,lth(s));
	cout<<ANS;
	return 0;
}
```


---

## 作者：wrzSama (赞：0)

## 题意

给定 $1$ 个字符串 $t$ $(1 \le \lvert t \rvert\le 2 \times 10^5$)，和 $n$ $(1 \le n \le 2 \times 10^5)$ 个字符串 $s_1,s_2,\cdots,s_n$，保证 $\sum\limits_{i=1}^n \lvert s_i \rvert\le 2 \times 10^5$。请计算 $\sum\limits_{i=1}^n \sum\limits_{j=1}^n f(t,s_i+s_j)$，其中 $f(t,s_i+s_j)$ 表示字符串 $s_i+s_j$ 在字符串 $t$ 中的出现次数，$s_i+s_j$ 表示将 $s_j$ 拼在 $s_i$ 的后面。

## 思路

我们可以考虑枚举字符串 $t$ 的每个位置作为 $s_i+s_j$ 中的断点，若这个位置为 $i$，那么对答案的贡献就是以 $i$ 为结尾的 $s$ 的数量乘上以 $i+1$ 为开头的 $s$ 的数量。计算以 $i$ 为结尾的 $s$ 的数量，我们可以对所有的 $s$ 建 $1$ 个 AC 自动机，并统记 $s$ 作为后缀在 AC 自动机上每个节点代表的字符串中的出现次数，再在 AC 自动机上跑一遍 $t$ 就能求出答案。计算以 $i+1$ 为开头的 $s$ 的数量，我们可以把 $t$ 和所有的 $s$ 反转，同理建 AC 自动机跑一遍也能求出。

## 代码

```cpp
#include<bits/stdc++.h>
#define re register
#define ll long long
using namespace std;
inline int read()
{
	int res=0;
	bool op=0;
	char ch=getchar();
	while(!isdigit(ch))
	{
		op|=ch=='-';
		ch=getchar();
	}
	while(isdigit(ch))
	{
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	return op?-res:res;
}
inline void write(ll x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10^48);
}
int n,tr[200005][26],tot,fail[200005];
ll c[200005],sum[200005],ans;
vector<int>g[200005];
string t,s[200005];
inline void insert(int x)
{
	int o=0;
	for(re int i=0;i<s[x].size();++i)
	{
		if(!tr[o][s[x][i]-'a']) tr[o][s[x][i]-'a']=++tot;
		o=tr[o][s[x][i]-'a'];
	}
	++c[o];
}
inline void build()
{
	queue<int>q;
	for(re int i=0;i<26;++i) if(tr[0][i]) q.push(tr[0][i]);
	while(q.size())
	{
		int u=q.front();
		q.pop();
		g[fail[u]].push_back(u);
		for(re int i=0;i<26;++i)
		{
			if(tr[u][i])
			{
				fail[tr[u][i]]=tr[fail[u]][i];
				q.push(tr[u][i]);
			}
			else tr[u][i]=tr[fail[u]][i];
		}
	}
}
inline void dfs(int u)
{
	for(re int i=0;i<g[u].size();++i)
	{
		int v=g[u][i];
		c[v]+=c[u];
		dfs(v);
	}
}
inline void query()
{
	int o=0;
	for(re int i=1;i<=t.size();++i)
	{
		o=tr[o][t[i-1]-'a'];
		sum[i]=c[o];
	}
}
int main()
{
	cin>>t;
	n=read();
	for(re int i=1;i<=n;++i)
	{
		cin>>s[i];
		insert(i);
	}
	build();
	dfs(0);
	query();
	for(re int i=0;i<=tot;++i)
	{
		c[i]=fail[i]=0;
		g[i].clear();
		for(re int j=0;j<26;++j) tr[i][j]=0;
	}
	tot=0;
	for(re int i=1;i<=n;++i)
	{
		reverse(s[i].begin(),s[i].end());
		insert(i);
	}
	build();
	dfs(0);
	reverse(t.begin(),t.end());
	int o=0;
	for(re int i=1;i<t.size();++i)
	{
		o=tr[o][t[i-1]-'a'];
		ans+=c[o]*sum[t.size()-i];
	}
	write(ans);
	return 0;
}
```


---

## 作者：issue_is_fw (赞：0)

[LINK](https://www.luogu.com.cn/problem/CF1202E)

---

考虑把所有串建立$ACAM$

那么其实问题等价于

计算$t$串的每个前缀中,有多少后缀匹配多少$s_i+s_j$的形式

**于是现在我们单独对每一个前缀来计算答案**

我们预处理一个$ok[x]$表示节点$x$能通过$fail$边转移到多少个单词

那么设$x_1,x_2$都是串$t$的前缀节点,$|x_1|,|x_2|$分别表示这两个前缀的长度

$x_2$通过跳$fail$变能到一个长度为$k$的单词,且满足$|x_2|-k=|x_1|$

那么答案自然可以加上$ok[x_1]$

于是有代码[LINK](https://paste.ubuntu.com/p/zVVxwh57Rg/)

---

不难发现这样暴力跳$fail$,是不合理的,$2*10^5$个$'a'$就会被卡死了

设$t$串的某个前缀节点是$x$,不妨考虑$ok[x]$被计算多少次

$ok[x]$被计算的次数,就是$[x+1,|t|]$所有前缀被匹配的次数

前缀是算不了的,$ACAM$只能计算后缀....

所以我们再把$t$的反串也插入$ACAM$,那么反串的后缀就是正串的前缀嘛!!

同时注意,$t$的正串和反串需要分别建立自动机,因为反串自动机插入的字符串也必须是反的

因为匹配的时候是在拿反串匹配

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 4e5+10;
int n,ID[maxn];
char t[maxn],s[maxn],ft[maxn];
struct ACAM
{
	int ok[maxn],fail[maxn],zi[maxn][26],id;
	void insert(char a[],int val)
	{
		int len = strlen( a+1 ), now = 0;
		for(int i=1;i<=len;i++)
		{
			if( !zi[now][a[i]-'a'] )	zi[now][a[i]-'a'] = ++id;
			now = zi[now][a[i]-'a']; 
		}
		ok[now]+=val;
	}
	void get_fail()
	{
		queue<int>q;
		for(int i=0;i<=25;i++)
			if( zi[0][i] )	q.push( zi[0][i] );
		while( !q.empty() )
		{
			int u = q.front(); q.pop();
			ok[u] += ok[fail[u]];
			for(int i=0;i<=25;i++)
			{
				if( zi[u][i] )	fail[zi[u][i]] = zi[fail[u]][i],q.push( zi[u][i] );
				else	zi[u][i] = zi[fail[u]][i];
			}
		}
	}
}T1,T2;
signed main()
{
	scanf("%s",t+1 ); 
	int l = strlen( t+1 ); for(int i=1;i<=l;i++)	ft[i] = t[l-i+1]; 
	T1.insert( t,0 );  T2.insert( ft,0 );
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1 ),T1.insert( s,1 );
		reverse(s+1,s+1+strlen(s+1) ); T2.insert( s,1 );
	}
	T1.get_fail(); T2.get_fail();
	
	int now = 0, len = strlen( t+1 ), ans = 0;
	for(int i=1;i<=len;i++) { now = T2.zi[now][ft[i]-'a'];	ID[i] = now; }//保存反串的所有下标 
	now = 0;
	for(int i=1;i<=len-1;i++)
	{
		now = T1.zi[now][t[i]-'a'];
		ans += T1.ok[now]*T2.ok[ID[len-i]];
	}
	cout << ans;
}
```


---

