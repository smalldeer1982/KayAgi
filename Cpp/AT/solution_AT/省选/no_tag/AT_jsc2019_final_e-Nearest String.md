# Nearest String

## 题目描述

[problemUrl]: https://atcoder.jp/contests/jsc2019-final/tasks/jsc2019_final_e

高橋くんは、文字列 $ a $ に対して、以下の $ 2 $ 種類の操作が行なえます。

- $ a $ の先頭、または末尾の $ 1 $ 文字を削除する。これには $ X $ のコストがかかる。
- $ a $ の末尾に、好きな $ 1 $ 文字を追加する。これには $ Y $ のコストがかかる。

高橋くんは今、$ N $ 個の文字列 $ S_0,S_1,\cdots,S_{N-1} $ を持っています。 高橋くんの友達の青木くんは、高橋くんに次の $ Q $ 個の質問を行います。

- 質問 $ i $ ($ 0\ \leq\ i\ \leq\ Q-1 $): 青木くんが文字列 $ T_i $ を見せる。 $ T_i $ に上記の操作を繰り返し行い、高橋くんの持っている $ N $ 個の文字列のいずれかに一致させるために必要なコストの最小値を求めよ。

多忙な高橋くんの代わりに、これらの質問に答えるプログラムを作成してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ Q\ \leq\ 10^5 $
- $ 1\ \leq\ X,Y\ \leq\ 10^9 $
- $ 1\ \leq\ |S_i| $
- $ \sum_{i=0}^{N-1}\ |S_i|\ \leq\ 5\ \times\ 10^5 $
- $ S_i\ \neq\ S_j $ ($ i\ \neq\ j $)
- $ 1\ \leq\ |T_i| $
- $ \sum_{i=0}^{Q-1}\ |T_i|\ \leq\ 5\ \times\ 10^5 $
- $ T_i\ \neq\ T_j $ ($ i\ \neq\ j $)
- 入力される数はすべて整数である。
- 入力される文字列はすべて英小文字からなる文字列である。

### Sample Explanation 1

例えば、質問 $ 2 $ について考えると、以下のように操作するのが最適です。 - `abc` の先頭の文字を削除して、`bc` を得る。コストが $ 4 $ かかる。 - `bc` の末尾に `d` を追加して、`bcd` を得る。コストが $ 2 $ かかる。

## 样例 #1

### 输入

```
3 3 4 2
b
bcd
cd
a
ab
abc```

### 输出

```
6
4
6```

## 样例 #2

### 输入

```
4 3 1 100
a
aaaa
aaaaaaa
aaaaaaaaaa
aaa
aaaaaa
aaaaaaaaa```

### 输出

```
2
2
2```

## 样例 #3

### 输入

```
10 10 86 69
bbabbaaaaa
babaababab
bbababbbba
aaaaaaaaab
bbbbbbaabb
aabbabbbba
babbbbbbaa
baaabbaaaa
aaaaababbb
ababaaaaaa
bbaabbbbaa
abbbbabbbb
abbaaabaaa
ababaaaaab
bbaabbaaaa
abbbbbbabb
aabbbabbba
aaabbbaaaa
abbbababab
babaaabbbb```

### 输出

```
930
620
775
155
775
465
775
930
620
620```

# 题解

## 作者：songhongyi (赞：4)

$t$ 的操作形式是取 $t$ 的子串 $t'$ 再向后添加字符，其代价为 $x\cdot(|t|-|t'|)+y\cdot(|s|-|t'|)$。而由于 $x,y$ 是正的，所以 $|t'|$ 越小代价越大。而因为 $t'$ 是和 $s$ 匹配的一段 $s'$，因而可以把代价拆成独立的两份。只和 $s$ 相关的 $y\cdot |s|-x\cdot |s'|-y\cdot |s'|$ 和 $x\cdot|t|$。前者在 $s$ 建立的 AC 自动机上维护，后者每次查询的时候加上即可。复杂度线性。

```cpp
//
// Problem: Nearest String
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_jsc2019_final_e
// Memory Limit: 1 MB
// Time Limit: 3000 ms

#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;
const int MAXN = 5e5 + 10;
long long int x, y;
struct ACATM
{
    int tr[ MAXN ][ 26 ], fail[ MAXN ];
    int c;
    long long int v[ MAXN ];
    void init()
    {
        memset( v, 0x3f, sizeof( v ) );
    }
    int insert( string s )
    {
        int len = s.size();
        int u = 0;
        v[ u ] = min( v[ u ], 1ll * y * len );
        for ( int i = 0; i < len; i++ )
        {
            if ( !tr[ u ][ s[ i ] - 'a' ] )
            {
                tr[ u ][ s[ i ] - 'a' ] = ++c;
            }
            u = tr[ u ][ s[ i ] - 'a' ];
            v[ u ] = min( v[ u ], 1ll * y * len - 1ll * ( i + 1 ) * ( x + y ) );
        }
        return u;
    }
    void build()
    {
        queue< int > q;
        for ( int i = 0; i < 26; i++ )
        {
            if ( tr[ 0 ][ i ] )
            {
                q.push( tr[ 0 ][ i ] );
            }
        }
        while ( q.size() )
        {
            int u = q.front();
            q.pop();
            v[ u ] = min( v[ u ], v[ fail[ u ] ] );
            for ( int i = 0; i < 26; i++ )
            {
                if ( tr[ u ][ i ] )
                {
                    fail[ tr[ u ][ i ] ] = tr[ fail[ u ] ][ i ];
                    q.push( tr[ u ][ i ] );
                }
                else
                {
                    tr[ u ][ i ] = tr[ fail[ u ] ][ i ];
                }
            }
        }
    }
    long long int query( string s )
    {
        long long int res = 1e18;
        int u = 0, len = s.size();
        for ( int i = 0; i < len; i++ )
        {
            u = tr[ u ][ s[ i ] - 'a' ];
            // cerr << u << ' ' << v[ u ] << endl;
            res = min( res, 1ll * x * len + v[ u ] );
        }
        return res;
    }
} T;
int main()
{
    cin.tie( 0 );
    int n, q;
    cin >> n >> q >> x >> y;
    T.init();
    for ( int i = 1; i <= n; i++ )
    {
        string s;
        cin >> s;
        T.insert( s );
    }
    T.build();
    for ( int i = 1; i <= q; i++ )
    {
        string t;
        cin >> t;
        cout << T.query( t ) << '\n';
    }
}
```

---

## 作者：Reunite (赞：3)

一个显然的观察是，如果我们在末尾添加了字符，那后面一定不会再删除末尾，不然不如不加。所以就相当于取出 $t$ 的子串 $t'$，并找到一个前缀是 $t'$ 的串 $s$，有 $x(|t|-|t'|)+y(|s|-|t'|)$ 的权值。我们希望最小化这个值。

考虑把所有 $s$ 串放到字典树上，为了快速找到 $t_{[l,r]}$ 在字典树上的定位，需要记录每个前缀的哈希值与节点编号的单射。枚举左断点位置 $l$，二分出最大的 $r$ 满足这个子串是 $s$ 中的前缀，并定位到节点 $u$。显然 $u$ 到根链上的点都是可用的，设 $d$ 为到根链上一点 $pos$ 的深度，$l$ 为经过 $pos$ 的最短 $s$ 串长度，则权值可改写为：

$$x(len_t-d)+y(l-d)=(x\cdot len_t)+(y\cdot l-d(x+y))$$

我们发现左右两边独立，只需要记录每个点到根链上式子右边的最小值即可 $O(1)$ 得到确定一个左端点的最小权值。

然后就做完了，用双哈希压缩串信息并用哈希表记录单射，复杂度 $O(\sum s_i+\sum t_i\log t_i)$。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <random>
#include <ctime>
#define ll long long
#define mod1 1000000009
#define mod2 1000000007
#define mod 9191891
using namespace std;

int n,q,x,y,tot,mnlen=1e9,cnt;
ll to[26];
ll h1[500005];
ll h2[500005];
ll b1[500005];
ll b2[500005];
ll val[500005];
char c[500005];
int ch[500005][26];
int h[9191895];
struct node{ll x;int u,nxt;}edge[500005];
mt19937 rnd(time(NULL));

inline void add(ll x,int u){
	edge[++cnt]={x,u,h[x%mod]};
	h[x%mod]=cnt;
	return ;
}

inline int Find(ll x){
	for(int i=h[x%mod];i;i=edge[i].nxt)
		if(edge[i].x==x) return edge[i].u;
	return 0;
}

inline void ins(){
	int len=strlen(c+1),u=0,d=0;
	mnlen=min(mnlen,len);
	ll h1=0,h2=0;
	for(int i=1;i<=len;i++){
		h1=(h1*131+to[c[i]-'a'])%mod1;
		h2=(h2*2333+to[c[i]-'a'])%mod2;
		d++;
		ll v=1ll*y*len-1ll*d*(x+y);
		int c=::c[i]-'a';
		if(!ch[u][c]) ch[u][c]=++tot,add(h1*h2,tot);
		u=ch[u][c];
		val[u]=min(val[u],v);
	}
	return ;
}

inline void dfs(int u){
	for(int i=0;i<26;i++){
		int v=ch[u][i];
		if(!v) continue;
		val[v]=min(val[v],val[u]);
		dfs(v);
	}
	return ;
}

inline ll get1(int l,int r){return (h1[r]-h1[l-1]*b1[r-l+1]%mod1+mod1)%mod1;}
inline ll get2(int l,int r){return (h2[r]-h2[l-1]*b2[r-l+1]%mod2+mod2)%mod2;}

int main(){
	for(int i=0;i<26;i++) to[i]=rnd();
	scanf("%d%d%d%d",&n,&q,&x,&y);
	b1[0]=b2[0]=1,val[0]=1e18;
	for(int i=1;i<=500000;i++) b1[i]=b1[i-1]*131%mod1,b2[i]=b2[i-1]*2333%mod2,val[i]=1e18;
	for(int i=1;i<=n;i++) scanf("%s",c+1),ins();
	dfs(0);
	while(q--){
		scanf("%s",c+1);
		int m=strlen(c+1);
		for(int i=1;i<=m;i++) h1[i]=(h1[i-1]*131+to[c[i]-'a'])%mod1,h2[i]=(h2[i-1]*2333+to[c[i]-'a'])%mod2;
		ll mn=1ll*x*m+1ll*y*mnlen;
		for(int i=1;i<=m;i++){
			int l=i,r=m,mid,u=0;
			while(l<=r){
				mid=(l+r)>>1;
				ll x=get1(i,mid)*get2(i,mid);
				if(Find(x)) u=Find(x),l=mid+1;
				else r=mid-1;
			}
			if(!u) continue;
			mn=min(mn,1ll*x*m+val[u]);
		}
		printf("%lld\n",mn);
	}

	return 0;
}
```

---

