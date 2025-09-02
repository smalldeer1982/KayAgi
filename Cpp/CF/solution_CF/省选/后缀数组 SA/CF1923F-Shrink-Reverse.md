# Shrink-Reverse

## 题目描述

给定一个长度为 $n$ 的二进制字符串 $s$（即由 $n$ 个字符组成，每个字符都是 $0$ 或 $1$）。

我们将 $s$ 看作某个整数的二进制表示，并称该整数为字符串 $s$ 的值。例如，$000$ 的值是 $0$，$01101$ 的值是 $13$，$100000$ 的值是 $32$，以此类推。

你最多可以对 $s$ 执行 $k$ 次操作。每次操作可以是以下两种类型之一：

- SWAP：选择 $s$ 中的两个下标 $i < j$，交换 $s_i$ 和 $s_j$；
- SHRINK-REVERSE：删除 $s$ 的所有前导零，然后将 $s$ 反转。

例如，对 $000101100$ 执行 SHRINK-REVERSE 操作后，会得到 $001101$。

请问，最多经过 $k$ 次操作后，$s$ 的最小可能值是多少？由于答案可能很大，请输出对 $10^9+7$ 取模的结果。

注意，你需要最小化原始值，而不是最小化取模后的结果。

## 说明/提示

在第一个样例中，一种最优策略如下：

1. $10010010 \xrightarrow{\texttt{SWAP}} 00010110$；
2. $00010110 \xrightarrow{\texttt{SWAP}} 00000111$。

$00000111$ 的值为 $7$。

在第二个样例中，一种最优策略如下：

1. $01101000 \xrightarrow{\texttt{SHRINK}} 1101000 \xrightarrow{\texttt{REVERSE}} 0001011$；
2. $0001011 \xrightarrow{\texttt{SWAP}} 0000111$。

$0000111$ 的值为 $7$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8 2
10010010```

### 输出

```
7```

## 样例 #2

### 输入

```
8 2
01101000```

### 输出

```
7```

## 样例 #3

### 输入

```
30 30
111111111111111111111111111111```

### 输出

```
73741816```

## 样例 #4

### 输入

```
14 1
10110001111100```

### 输出

```
3197```

# 题解

## 作者：MaxBlazeResFire (赞：3)

Observation1：$1$ 的个数不变，且答案下界为 $2^{c_1}-1$；

Observation2：我们不会在翻转之后再进行交换操作。假设在某次翻转之后进行交换操作还能使答案更优，那么必然可以在翻转之前先做交换操作，再翻转，至少可以得到相同的结果；

Observation3：我们不会进行大于 $1$ 次翻转操作。由上述过程可知我们只有可能在最后做翻转操作，那么翻转 $k$ 次和翻转 $k-2$ 次得到的 $v$ 是相同的，因为我们不会再交换。

于是当翻转操作次数为 $0$ 时，我们考虑贪心地把高位的 $1$ 扔到最低位的 $0$，用双指针可以做到 $O(n)$ 解决问题。

当翻转次数为 $1$ 时，先把 $k$ 减 $1$。考虑我们的目标。由于 $1$ 的数量不变，那么我们首先要尝试最小化翻转后最高位 $1$ 的位置。而这个位置同时取决于翻转前整个串前导 $0$ 的个数与最靠右的 $1$ 的位置。

不妨再转化一步。记最优结果翻转前得到的串最左侧、右侧的 $1$ 分别在 $l,r$，也即最终所有 $1$ 都在区间 $[l,r]$ 内，我们发现首要目标是最小化 $[l,r]$ 的区间长度，次要目标是最小化其反串的字典序。

考虑如何求解前者。枚举左端点 $l$，维护钦定最左侧的 $1$ 在 $l$ 时，最右侧的 $1$ 最小可以在哪里（也即 $r$ 的最小值）。考虑一个区间 $[l,r]$ 合法的条件是：$[l,r]$ 外的 $1$ 个数 $\leq k$；$[l,r]$ 外 $1$ 的个数 $\leq[l,r]$ 内 $0$ 的个数。条件容易用前缀和刻画，做到 $O(1)$ 判定。我们发现随着 $l$ 的增大，满足条件的最小 $r$ 不会减小，于是可以双指针求解。

不妨在做上述过程之前把串先反转一次，上面得到的答案是不变的。现在问题转化成，给定目标长度 $L$，把所有合法的长度为 $L$ 的区间当作答案区间模拟操作一遍（把 $1$ 交换到后缀上）之后求其中字典序最小的。

考虑对串求 $sa$，然后直接从小到大枚举所有后缀，判定这个后缀长度为 $L$ 的前缀是否合法，找到第一个合法的区间就是答案。这个步骤的正确性考虑，对于某两个长度为 $L$ 的区间，如果填充 $1$ 影响的位置在 $\rm LCP$ 之后。那么它们之间的顺序取决于 $\rm SA$ 求得的顺序；否则由于所有串变换之后 $1$ 的个数都是 $c_1$，而在 $\rm LCP$ 之前二者相同，那么这两个串被填充后完全相等。

复杂度 $O(n\log n)$，用 $\rm SAM$ 等线性求 $\rm SA$ 的方法可以做到复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 1000005
#define mod 1000000007

int n,k,G[MAXN << 1][2],sa[MAXN],pre[MAXN];
char s[MAXN],t[2][MAXN];

struct SuffixAutomaton{
	int nodecnt,nxt[MAXN << 1][2],maxlen[MAXN << 1],link[MAXN << 1];
	int endp[MAXN << 1],edp[MAXN << 1],deg[MAXN << 1],sid;
	inline void init(){ nodecnt = 1; }
	inline int insert( int last , int ch , int id ){
		int cur = ++nodecnt,p = last; maxlen[cur] = maxlen[p] + 1,endp[cur] = edp[cur] = id;
		for( ; p && !nxt[p][ch] ; p = link[p] ) nxt[p][ch] = cur;
		int q = nxt[p][ch];
		if( !q ) link[cur] = 1;
		else if( maxlen[q] == maxlen[p] + 1 ) link[cur] = q;
		else{
			int clone = ++nodecnt; maxlen[clone] = maxlen[p] + 1;
			memcpy( nxt[clone] , nxt[q] , sizeof( nxt[clone] ) );
			for( int x = p ; x && nxt[x][ch] == q ; x = link[x] ) nxt[x][ch] = clone;
			link[clone] = link[q],link[q] = link[cur] = clone;
		}
		return cur;
	}
	inline void build(){
		for( int i = 2 ; i <= nodecnt ; i ++ ) deg[link[i]] ++;
		queue<int> Q;
		for( int i = 1 ; i <= nodecnt ; i ++ ) if( !deg[i] ) Q.push( i );
		while( !Q.empty() ){
			int u = Q.front(); Q.pop();
			endp[link[u]] = endp[u];
			if( !--deg[link[u]] ) Q.push( link[u] ); 
		}
		for( int i = 2 ; i <= nodecnt ; i ++ ) G[link[i]][s[endp[i] + maxlen[link[i]]] - '0'] = i;
	}
	void dfs( int x ){
		if( edp[x] ) sa[++sid] = edp[x];
		for( int i = 0 ; i < 2 ; i ++ ) if( G[x][i] ) dfs( G[x][i] );
	}
}Sam;

signed main(){
	scanf("%d%d%s",&n,&k,s + 1);
	//钦定不翻转
	memcpy( t[0] , s , sizeof( t[0] ) );
	int l = 1,r = n,tmp = k;
	while( tmp ){
		while( l <= n && t[0][l] == '0' ) l ++;
		while( r >= 1 && t[0][r] == '1' ) r --;
		if( l >= r ) break;
		tmp --,swap( t[0][l] , t[0][r] );
	}
	//钦定翻转
	reverse( s + 1 , s + n + 1 ); Sam.init();
	for( int i = n , last = 1 ; i >= 1 ; i -- ) last = Sam.insert( last , s[i] - '0' , i );
	Sam.build(),Sam.dfs( 1 );
	for( int i = 1 ; i <= n ; i ++ ) pre[i] = pre[i - 1] + ( s[i] == '1' ); k --;
	int L = n;
	for( int l = 1 , r = 1 ; l <= n ; l ++ ){
		while( r <= n ){
			int c1 = pre[l - 1] + pre[n] - pre[r],c0 = ( r - l + 1 ) - ( pre[r] - pre[l - 1] );
			if( c1 <= k && c1 <= c0 ){
				L = min( L , r - l + 1 );
				break;
			}
			r ++;
		}
	}
	memcpy( t[1] , s , sizeof( t[1] ) );
	for( int i = 1 ; i <= n ; i ++ ){
		int l = sa[i],r = sa[i] + L - 1;
		int c1 = pre[l - 1] + pre[n] - pre[r],c0 = ( r - l + 1 ) - ( pre[r] - pre[l - 1] );
		if( c1 <= k && c1 <= c0 ){
			for( int i = 1 ; i <= n - L ; i ++ ) t[1][i] = '0';
			int c1 = pre[n] - ( pre[r] - pre[l - 1] );
			for( int i = n , j = r ; i >= n - L + 1 ; i -- , j -- ){
				if( s[j] == '1' ) t[1][i] = '1';
				else t[1][i] = '0' + ( c1 > 0 ),c1 --;
			}
			break;
		}
	}
	int better = 0;
	for( int i = 1 ; i <= n ; i ++ ){
		if( t[0][i] < t[1][i] ){ better = 0; break; }
		if( t[1][i] < t[0][i] ){ better = 1; break; }
	}
	int val = 0;
	for( int i = 1 ; i <= n ; i ++ ) val = ( 2ll * val % mod + t[better][i] - '0' ) % mod;
	printf("%d\n",val);
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：3)

$\textbf{CF1923F *2800}$

> - 给定 $\texttt{01}$ 串 $s$，最多做 $k$ 次操作，每次操作可以选择：
>    - 选择两个位置 $i,j$ 并交换 $s_i,s_j$。
>    - 删去串 $s$ 的所有前导 $0$ 并翻转串 $s$。
> - 定义串 $s$ 的权值是将 $s$ 看作二进制数字后的值，求能得到的最小权值，模 $10^9+7$。
> - $2 \le n \le 5 \times 10^5,1 \le k \le n$。

要多练找性质的能力了。

- 性质一：操作二最多做一次。

> 首先一定不会做操作二三次及以上，那样我们可以把两次操作合并为一次，节省操作次数。注意到前导 $0$ 对权值没有影响，我们想做两次操作二是为了去除串 $s$ 的后导 $0$，但是这样并不划算：例如串 $\texttt{00111001000}$，操作两次后串变为 $\texttt{111001}$，但是我们可以选择操作一次（串变成 $\texttt{000100111}$）后，将第一个 $1$ 往后放得到 $\texttt{1111}$。也就是说，如果做两次二操作，第二次操作可以被一次一操作替代，且答案会变得不劣。

我们可以直接计算不翻转 $s$ 的答案，即把所有 $1$ 贪心的往后换。以下讨论翻转串 $s$ 后的情况，注意下面的 $s$ 是翻转过的串。

- 性质二：答案串 $s$ 去除前后导 $0$ 后长度一定是可能达到的最小的。

> 因为进行了 $1$ 操作，后导 $0$ 已经被全部删除。比较两个二进制数字大小时第一关键字是长度。

令 $c$ 表示串里 $1$ 的数量，$lt = c-k$ 表示有多少个 $1$ 不能移动位置。答案的下界显然是 $2^c-1$。为了让长度最短，我们希望让不能移动位置的 $1$ 连续，并把外面的 $1$ 换到这个连续段里。记 $\{pos_c\}$ 表示所有 $1$ 的出现位置，如果存在 $i$ 满足 $pos_{i+lt-1}-pos_i+1 \le c$，就说明我们可以用剩余的 $1$ 填满这些 $1$ 中间的 $0$，让答案达到下界。否则，最小的答案串长度就应该是 $\min \limits_{i=1}^{c-lt+1}\{pos_{i+lt-1}-pos_i+1\}$，记这个串为 $t$，此时我们可以把剩余的 $1$ 全部插入到 $t$ 的空隙里。但是长度最短的 $t$ 可能不唯一。

- 性质三：当存在多个长度最短的 $t$ 时，我们选择字典序最小的。

> 考虑我们把剩余的 $1$ 插入到串 $t$ 中时会贪心的从后到前插，那么此时选最小的 $t$ 一定不劣。

如果暴力比较所有最短的串 $t$ 大小可能会被卡到 $\mathcal O(n^2)$，使用后缀数组比较即可。可以用 SA-IS 做到线性。

放一份 $\mathcal O(n \log^2 n)$ 的 SA 代码：

```cpp
/**
 *    author: sunkuangzheng
 *    created: 24.02.2024 16:28:17
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
#endif
using ll = long long;
const int N = 5e5+5;
using namespace std;
int T,n,k,sa[N],ok[N],rk[N]; string s;
void los(){
    cin >> n >> k >> s,s = " " + s;
    auto cmp = [&](string &s,string t){
        return s.size() == t.size() ? (s < t ? s : t) : (s.size() < t.size() ? s : t);
    };
    auto gd = [&](string s){
        int ct = 0;
        for(int i = 1;i <= n;i ++)
            if(ct < k && s[i] == '1') ct ++,s[i] = '0';
        for(int i = n;i >= 1;i --) if(s[i] == '0' && ct) s[i] = '1',ct --;
        return s.substr(s.find('1'));
    };string ans = gd(s);
    reverse(s.begin(),s.end()),k --,s = " " + s;
    vector<int> p;
    for(int i = 1;i <= n;i ++) if(s[i] == '1') p.push_back(i);
    if(k < p.size()){
        int lt = p.size() - k,len = 1e9;
        for(int i = 0;i + lt - 1 < p.size();i ++) len = min(len,p[i + lt - 1] - p[i] + 1);
        if(len <= p.size()) ans = string(p.size(),'1');
        else{
            for(int i = 1;i <= n;i ++) rk[i] = s[i],sa[i] = i;
            for(int j = 1;j <= n;j *= 2){
                for(int i = 1;i <= n;i ++) ok[i] = rk[i]; int p = 0;
                sort(sa+1,sa+n+1,[&](int x,int y){return rk[x] < rk[y] || rk[x] == rk[y] && rk[x + j] < rk[y + j];});
                auto cmp = [&](int x,int y){return ok[x] == ok[y] && ok[x + j] == ok[y + j];};
                for(int i = 1;i <= n;i ++) if(cmp(sa[i],sa[i-1])) rk[sa[i]] = p; else rk[sa[i]] = ++p; if(p == n) break;
            }for(int i = 1;i <= n;i ++){
                int pos = sa[i]; if(s[pos] == '0') continue;
                int d = lower_bound(p.begin(),p.end(),pos) - p.begin();
                if(d + lt - 1 < p.size() && p[d + lt - 1] - p[d] + 1 == len){
                    int l = pos,r = pos + len - 1;
                    for(int j = r;j >= l;j --) if(k && s[j] == '0') k --,s[j] = '1';
                    ans = cmp(ans,s.substr(l,len)); break;
                }
            }
        }
    }else ans = string(p.size(),'1');
    int sum = 0;
    for(char i : ans) sum = (2ll * sum + i - '0') % (int)(1e9+7);
    cout << sum;
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

---

## 作者：Nt_Tsumiki (赞：2)

是很有趣的题啊。

首先不难发现翻转操作最多只会在最后用一次。

证明的话分两部分：

- 一部分是所有交换都在翻转之前，这是显然的，如果你在翻转之后交换，因为你翻转之后能交换的位置还变少了，所以在翻转之前也一定有等价的交换；

- 一部分是翻转只会用一次，大于两次的肯定不优，这里不考虑了，你考虑翻转两次的意义是为了去掉后导零，但是你进行完第一次翻转后的长度和你第二次翻转后的长度是不变的，所以假如说你还可以进行交换操作，那么第二次翻转一定可以不劣的替换成将最高位的 1 和最低位的 0 交换的操作。

那我们现在只用求出不进行反转操作的最小字典序，进行一次反转操作的最小字典序。

无论是哪种情况，都遵循把 1 和最终串中最低位的 0 交换的原则。

对于第一种情况，我们直接按照上面贪心就行。

对于第二种情况，我们考虑对于每个可能的 $i$ 求出最大 $r_i$ 使得 $[i,r_i]$ 中有 $k-1$ 个 0，以及求出最小的 $R_i$ 使得 $[i,R_i]$ 中有 $n-k+1$ 个 1，那么你按照上面贪心的填，肯定是把 $[i,r_i]$ 全填成 1，$[r_i+1,R_i]$ 不变，那么我们比较最后的答案就只需要比较长度和 $s^R[n-R_i+1:n-r_i]$ 的字典序就行。

使用 SA 求 LCP 可以做到 $O(n\log n)$。

[submission](https://codeforces.com/contest/1923/submission/306883050)

---

## 作者：Tx_Lcy (赞：2)

[更好的阅读体验](https://www.cnblogs.com/tx-lcy/p/18031152)

[题目传送门](https://codeforces.com/contest/1923/problem/F)

有趣的字符串题！抢在官方题解之前写一篇题解。

## 思路

因为需要使字符串代表的整数最小化，所以我们显然要删除前导零后的最终序列长度尽可能小。

我们发现为了达成这个目的，可以把所有的 $1$ 都聚集到一个区间内，不妨设这个区间是 $[l,r]$。

那么 $1 \dots l-1$ 和 $r+1 \dots n$ 就全是 $0$，我们可以翻转一次把 $1 \dots l-1$ 的 $0$ 去掉，这样 $r+1 \dots n$ 的 $0$ 就变成前导零了，可以忽略它们。

容易发现使用更多的翻转次数不优，因为若使用更多翻转操作，一定会使得 $[l,r]$ 的长度增大，这与我们“要使最终序列长度尽可能小”的目的背道而驰。

更进一步，我们可以发现两个比较显然的性质：

- 区间 $[l,r]$ 外的 $1$ 一定尽可能移到区间内靠近 $l$ 的位置（因为我们需要翻转序列）。

- $\forall l$，有用的区间只有一个。

我们可以双指针把所有有用的区间找出来，答案区间一定在这些区间中长度最小的那些区间之中。

现在问题变成如何比较两个长度相同的区间最终形成的字符串哪个字典序小。

经过简单的观察，又可以发现一个显然的性质：

- 这两个区间填入的 $1$ 的个数是相同的。

于是问题等价于比较原串的这两个区间翻转之后的字典序（证明不难，可以自己思考一下）。

而这个问题又等价于比较两个前缀翻转之后的字典序。

于是就非常简单了，二分哈希，SA 均可。

但是这个做法当区间 $[l,r]$ 的 $r=n$ 时有点小问题，因为此时有一种特殊的方案是把 $1 \dots l-1$ 的 $1$ 放在倒数若干个 $0$ 上，特判一下即可。

时间复杂度 $\Theta(n \log n)$ 或 $\Theta(n)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
int const N=5e5+10;
int const mod=1e9+7;
int n,k,sm,pw[N],qz0[N],qz1[N];string s;
struct Hash_Table{
    #define ull unsigned long long
    int const B=457;
    ull hsh[N],bse[N];
    inline void init(string s){
        s=" "+s,hsh[0]=bse[0]=1;
        rep(i,1,n) hsh[i]=hsh[i-1]*B+(s[i]-'0')*31+233;
        rep(i,1,n) bse[i]=bse[i-1]*B;
    }
    inline ull qry(int l,int r){
        ++l,++r;
        return hsh[r]-hsh[l-1]*bse[r-l+1];
    }
}T;
inline int qry0(int l,int r){if (l>r) return 0;if (r<0) return 0;if (!l) return qz0[r];return qz0[r]-qz0[l-1];}
inline int qry1(int l,int r){if (l>r) return 0;if (r<0) return 0;if (!l) return qz1[r];return qz1[r]-qz1[l-1];}
inline string get(string ans){
    int r=0; 
    while (ans[r]=='0') ++r;
    string t="";
    rep(i,r,(int)ans.size()-1) t+=ans[i];
    return t;
}
inline string chk(int L,int R){
    string t=s,ans=s;
    vector<int>vec;
    rep(i,L,R) if (t[i]=='0') vec.push_back(i);
    int re=0;
    rep(i,0,L-1) if (t[i]=='1') swap(t[i],t[vec[re]]),++re;
    per(i,n-1,R+1) if (t[i]=='1') swap(t[i],t[vec[re]]),++re;
    if (re<k){
        t=get(t),reverse(all(t)),t=get(t);
        if (t.size()<ans.size()) ans=t;
        else if (t.size()==ans.size()) ans=min(ans,t);
    }
    return ans;
}
inline int qry(int x,int y){
    int l=1,r=y+1,ans=0;
    while (l<=r)
        if (T.qry(x-mid+1,x)==T.qry(y-mid+1,y)) l=(ans=mid)+1;
        else r=mid-1;
    return ans;
}
inline string work(){
    string ans=s;
    vector<int>vec;
    per(i,n-1,0) if (s[i]=='0') vec.push_back(i);
    int m=k,l=0;
    rep(i,0,n-1){
        if (!m) break;
        if (l==(int)vec.size()) break;
        if (ans[i]=='1'){
            if (vec[l]<i) break;
            swap(ans[i],ans[vec[l]]),++l,--m;
        }
    }
    ans=get(ans),l=0;
    int ansl=-1e18,ansr=1e18;
    rep(i,0,n-1){
        while (l<n && (qry1(0,i-1)+qry1(l+1,n-1)>qry0(i,l) || qry1(0,i-1)+qry1(l+1,n-1)>=k)) ++l;
        if (l>=n) break;
        if (l-i+1>ansr-ansl+1) continue;
        if (l-i+1<ansr-ansl+1){ansl=i,ansr=l;continue;}
        int g=qry(l,ansr);
        if (g==ansr+1) continue;
        if (s[l-g]<s[ansr-g]) ansl=i,ansr=l;
    }
    if (ansr-ansl+1<(int)ans.size()) ans=chk(ansl,ansr);
    else if (ansr-ansl+1==(int)ans.size()) ans=min(ans,chk(ansl,ansr));
    return ans;
}
void solve(){
    cin>>n>>k>>s,T.init(s),qz0[0]=s[0]=='0',qz1[0]=s[0]=='1';
    rep(i,1,n-1) qz0[i]=qz0[i-1]+(s[i]=='0'),qz1[i]=qz1[i-1]+(s[i]=='1');
    string ans=work();
    int res=0;
    rep(i,0,(int)ans.size()-1)
        res+=(ans[i]=='1')*pw[ans.size()-1-i],res%=mod;
    cout<<res<<'\n';
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    pw[0]=1;
    rep(i,1,N-1) pw[i]=pw[i-1]*2%mod;
    int t=1;
    // cin>>t;
    while (t--) solve();
    cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
    return 0;
}
```

---

## 作者：Missa (赞：1)

感谢 [Polaris\_Australis\_](https://www.luogu.com.cn/user/576737) 的指导。

称第二种操作为“旋转”。

注意到旋转操作抹去了前导 $0$，先交换再旋转不劣。

1. 至多旋转 $2$ 次。

若旋转 $x \geq 3$ 次，旋转 $x-2$ 次可以达到同样的效果。

2. 不会旋转 $2$ 次。

假设旋转两次最优，注意到旋转两次得到的串是原串去掉前端和后端极长的 $0$，考虑只旋转一次，并使用一次交换操作以严格减小最后得到的串的长度。若无法交换，说明所有 $1$ 仅构成一个极长连续段，此时最后一次旋转操作为多余。

当旋转 $0$ 次时，贪心将最靠前的 $1$ 与最靠后的 $0$ 交换即可。

否则，先考虑最小化位数。假设钦定 $[l, r]$ 作为最后去除前导 $0$ 后剩下的区间，则 $[l, r]$ 外至多只能有 $k-1$ 个 $1$，且 $r-l+1 \geq m$，$m$ 为 $1$ 的个数。固定 $l$，最小的 $r$ 可以通过双指针得出。

假设存在一个合法区间的长度为 $m$，显然不会有区间比它更优；否则，所有极短区间外一定恰好有 $k-1$ 个 $1$。将它们移入区间时，一定尽量靠左端点。


现在只剩 $01$ 个数分别相等的串，考虑如何比较两个串。记把区间内最靠右的 $k-1$ 个 $0$ 变成 $1$ 后得到的串为新串，设原串从右到左第一个不同的位为 $p$ 且 $s_p=1, t_p=0$，若第 $p$ 位被 $1$ 覆盖，则两个新串相同；否则 $s$ 对应的新串对应的数字仍大于 $t$ 对应的新串对应的数字。注意这里考虑的是再做一次翻转后对应的数字。

这个结论告诉我们，只需要比较原串的字典序，即可比较新串对应的数字的大小。跑一个 SA 即可。

---

## 作者：xiezheyuan (赞：0)

明天要讲 SA，提前写一道 SA 题。

## 简要题意

有一个长度为 $n$ 的 $01$ 串 $S$，你可以执行下列两种操作至多 $k$ 次：

- 交换：选定 $1\leq i,j\leq n$ 并交换 $S_i,S_j$。
- Shrink-Reverse 变换（以下简称变换）：先**删除 $S$ 的所有前导 $0$**，然后将 $S$ 翻转。

你需要使 $S$ 表示的二进制数尽可能小，输出这个二进制数值的最小值对 $10^9+7$ 取模。

$2\leq n\leq 5\times 10^5$。

## 思路

超级高明题，难点不在 SA 本身。

### Part 1

难点在于意识到这些结论。

> **引理 1**：我们总是在执行所有交换后进行变换。

**证明**：假如我们在一次变换后进行交换，我们一定可以在找到这两个位置在变换前的下标，改为在变换前进行交换。也就是说在变换前交换是不劣的。

> **引理 2**：我们不会执行超过一次变换。

**证明**：不妨先研究一下变换的过程：

$$
\textcolor{grey}{0\cdots0}\textcolor{red}{\text{AB}}\textcolor{blue}{0\cdots 0}\xrightarrow{\text{Shrink-Reverse}} \textcolor{grey}{0\cdots 0}\textcolor{red}{\text{BA}}\xrightarrow{\text{Shrink-Reverse}}\textcolor{red}{\text{AB}}\xrightarrow{\text{Shrink-Reverse}}\textcolor{red}{\text{BA}}
$$

在上面的示意图中，灰色的 $0$ 表示前导 $0$，蓝色的 $0$ 表示后导 $0$，中间红色的 $\mathrm{AB}$ 表示以 $1$ 开头和结尾的串，用 $\text{AB},\text{BA}$ 区分顺序。

当我们进行超过 $2$ 次变换时，便陷入 BA 与 AB 的循环，那么执行奇数次变换，不如执行一次变换（因为前导 $0$ 在最终比较时是忽略的），执行偶数次变换，不如执行两次变换。所以我们最多执行 $2$ 次变换。

进一步地，考察进行两次变换的影响，发现仅仅在原串的基础上去除了后导 $0$。那么有一种非常神奇的策略：仅执行一次变换，接下来进行调整。

具体的调整策略是，如果中间串全是 $1$，那么无需调整。否则将外侧的一个 $1$ 与内部的一个 $0$ 交换（当然，需要根据引理 1 将这个操作等效替代为变换前的操作），这样有效位数就减小了，比变换两次更优。

### Part 2

由于引理 2，我们只能进行 $0$ 次或 $1$ 次变换。现在考虑进行 $0$ 次的情况。

很容易设计一个贪心，将高位的 $1$ 与低位的 $0$ 交换，正确性是显然的。这个贪心很容易用双指针实现。

同时观察到这个贪心的本质是将 $1$ 尽可能的靠拢在一个区间中。这个思路是可以沿用的。

### Part 3

现在考虑进行 $1$ 次的情况。

根据前面的分析，我们很容易感受出操作的策略是什么，就是选定一个区间，保留其中的所有 $1$，然后将区间外的 $1$ 与区间内交换。

由于我们需要在长度相同的情况下，让字典序最小，于是我们希望 $1$ 在后面，所以需要从后往前填区间外的 $1$。

观察这样的区间 $[L,R]$ 的限制。首先需要将区间外的所有 $1$ 都填进去，所以 $R-L+1$ 要不小于整个序列的 $1$ 的数量。

另外我们有操作次数的限制，所以区间外的 $1$ 的数量必须不大于 $k-1$。

我们发现固定区间的一端，另一端对区间是否合法的影响是单调的，于是可以用双指针维护。

### Part 4

最后我们可以用双指针得到若干个固定左端点，最短的合法区间。我们需要选择最优的。

观察到对于两个候选的子串 $a,b$，如果 $a$ 的长度比 $b$ 小，那么我们肯定选择 $a$。

如果 $a,b$ 长度相同，观察到我们需要从后往前将 $0$ 替换为 $1$。那么如果 $a$ 的字典序比 $b$ 小，那么最终替换后 $a$ 的字典序仍然不比 $b$ 大。这是因为我们定义字典序小，是因为 $a_i=0$ 而 $b_i=1$（$[1,i-1]$ 都相同），而若 $a_i$ 未被替换为 $0$，则结论显然成立。否则 $a_i$ 后面的 $0$ 均是 $1$，由于 $a,b$ 的 $0/1$ 数量相同（都会是 $k-1$，因为 $1$ 的数量在离散意义上是连续的，根据介值定理可以得到本结论），所以 $b_i$ 后面也都是 $1$，此时 $a=b$。本结论得证。

于是现在的问题是，需要比较若干个区间翻转后的字典序的大小，将字符串翻转后使用后缀数组即可做到比较时 $O(1)$。

最终时间复杂度 $O(n\log^\mu(n))$，复杂度瓶颈在 SA 的构建。若使用倍增配合一般的排序求后缀数组，$\mu=2$，若改用基数排序，$\mu=1$，若利用 SA-IS 或 DC3 等科技，$\mu=0$。

## 代码

我的实现 $\mu=2$，足以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
int Add(int x, int y){ return (x + y) >= mod ? (x + y - mod) : (x + y); }
int Sub(int x, int y){ return (x - y) < 0 ? (x - y + mod) : (x - y); }
int Mul(int x, int y){ return 1ll * x * y % mod; }

template<int N>
struct SuffixArray {
    int sa[N], rk[N], tmp[N];

    void build(const string &s){
        int n = s.size() - 1;
        for(int i=1;i<=n;i++) sa[i] = i, rk[i] = s[i];
        for(int k=1;k<n;k<<=1){
            auto mk = [=](int x){ return make_pair(rk[x], rk[x + k]); };
            sort(sa + 1, sa + n + 1, [mk](int x, int y){ return mk(x) < mk(y); });
            for(int i=1,p=0;i<=n;i++){
                if(mk(sa[i - 1]) == mk(sa[i])) tmp[sa[i]] = p;
                else tmp[sa[i]] = ++p;
            }
            copy(tmp + 1, tmp + n + 1, rk + 1);
        }
    }
};

const int N = 5e5 + 5;
int n, k;
string s;
SuffixArray<N> sa;

string solve0(){
    s = ' ' + s;
    int L = 1, R = n;
    string ret = s;
    for(int i=1;i<=k;i++){
        while(L <= n && s[L] != '1') L++;
        while(R >= 1 && s[R] != '0') R--;
        if(L > n || R < 1 || L > R) break;
        swap(ret[L], ret[R]);
        L++, R--;
    }
    return ret;
}

struct node{
    int pos, len;
    bool operator<(const node &rhs) const {
        return len == rhs.len ? sa.rk[pos] < sa.rk[rhs.pos] : len < rhs.len;
    }
};

string solve1(){
    reverse(s.begin(), s.end());
    s = " " + s;
    sa.build(s);
    int R = 0, cnt = 0, total = count(s.begin(), s.end(), '1');
    vector<node> vct;
    for(int L=1;L<=n;L++){
        while(R <= n && !((R - L + 1 >= total) && (total - cnt <= k - 1))) cnt += s[++R] == '1';
        if(R > n) break;
        vct.push_back({L, R - L + 1});
        cnt -= s[L] == '1';
    }
    auto [pos, len] = *min_element(vct.begin(), vct.end());
    string ret = s.substr(pos, len);
    int ext = total - count(ret.begin(), ret.end(), '1');
    reverse(ret.begin(), ret.end());
    for(char& ch : ret){
        if(ch == '0' && (--ext) >= 0) ch = '1';
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

string wash(string s){
    s = s.substr(s.find('1'));
    if(s.empty()) s = "0";
    return s;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k >> s;
    string ret1 = wash(solve0()), ret2 = wash(solve1()), ans;
    if(ret1.size() < ret2.size()) ans = ret1;
    else if(ret1.size() > ret2.size()) ans = ret2;
    else ans = min(ret1, ret2);
    int ret = 0;
    for(char ch : ans) ret = Add(Add(ret, ret), ch == '1');
    cout << ret << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：Komomo (赞：0)

自己想的时候整题思路完全偏了。。。还是挺好的题！

首先我们初步的直觉：reverse 一定是最后进行的，因为交换 swap 和 reverse 实际上对结果没有影响；同时我们就可以得出 reverse 操作不会超过 $2$ 次。

到现在还不是很好做，发现上面的结论可以更强：reverse 操作最多只会进行 $1$ 次，稍微证明一下：

> 考虑操作 $2$ 次等价于把操作 $1$ 次 reverse 后的字符串翻转，于是我们分讨情况：
>
> 1. 字符串中的所有 1 已经全部连在一起，此时第二次 reverse 不会给字符串大小带来影响。
> 2. 字符串的 1 没有全部连在一起，可以将一次 reverse 操作替换为 swap 操作，并把外侧的一个 1 与内部的 0 交换，答案有效位数严格变小。
>
> 故结论成立。

对于操作 0 次 reverse，我们直接将前面的 $1$ 换到后面。

对于操作 1 次 reverse，我们预先把字符串翻转，现在求的就是只用 $k-1$ 次操作，找到最小的答案。枚举答案的左端点 $l$，易求出最小右端点 $r$。现在问题变成了给定最终的 $n$ 个可能答案区间，求出其中最小。

这里有第二个结论：对于两个区间 $x,y$，区间长度越小的答案越小，否则比较字典序。对于后者的证明，如果两个区间都能被 1 填满，则对答案无影响；否则第一个不相同的字符中，字典序小者的这一位为 0，而且是不可能被 1 交换的。

最终问题变成了求在区间长度相同下，字典序最小的后缀，易用 SA 达到 $\mathcal O(n\log n)$ 的复杂度。

---

