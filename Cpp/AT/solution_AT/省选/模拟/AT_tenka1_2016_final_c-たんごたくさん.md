# たんごたくさん

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2016-final/tasks/tenka1_2016_final_c

文字列 $ S $ と、要素数 $ M $ の単語の集合 $ P=\{P_1,\ P_2,\ …,\ P_M\} $ が与えられます。単語 $ P_i $ は、整数の重み $ W_i $ を持っています。

文字列 $ S $ から、$ P $ に含まれる単語を重なり合わないように取り出すことを考えます。単語の重みの総和が最大値をとるように取り出すとき、その最大値はいくつでしょうか？

なお、同じ単語を複数回取り出した場合、それらの単語は別々に数えることとします。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 200000 $
- $ 1\ \leq\ M\ \leq\ 5000 $
- $ 1\ \leq\ |P_i|\ \leq\ 200 $
- $ 1\ \leq\ W_i\ \leq\ 10000 $
- $ S $, $ P_i $ は英小文字からなる文字列である

## 样例 #1

### 输入

```
abcabcabc
3
ab
bc
ca
1
1
1```

### 输出

```
4```

## 样例 #2

### 输入

```
abracadabra
4
b
abra
cad
rac
1
10
50
100```

### 输出

```
111```

## 样例 #3

### 输入

```
abcd
2
ad
bc
1192
794```

### 输出

```
794```

# 题解

## 作者：_sunkuangzheng_ (赞：1)

AC 自动机太 hard 了，提供一个无脑 SA 做法。 

---

考虑 dp：设以 $i$ 开头的后缀的最大权值为 $f_i$，显然有转移 $f_i = \max\limits_{s[i:i+l_j-1] = p_j}\{f_{i+l_j}+w_j\}$。至此有 $\mathcal O(nm)$ 做法：枚举 $i,j$，判断是否能转移。判断可以通过建 SA 来 $\mathcal O(1)$ 求 $\operatorname{LCP}$。很遗憾，可能因为 st 表的常数较大，它不能通过。

我们考虑枚举 $|p_j|$ 的值，找到 $\operatorname{LCP} \ge |p_j|$ 的极长排名区间，求出所有满足长度为 $|p_j|$ 且排名在该区间里的串的 $w$ 最大值。找 $w$ 可以通过建 $200$ 个 st 表实现，每次二分得到区间即可。

记 $k = \sum |p_i| + |s|,l = 200$，时间复杂度 $\mathcal O(k + nl \log k)$，前半部分是线性 SA，后半部分是 dp。可能需要卡一下常数。

```cpp
/**
 *    author: sunkuangzheng
 *    created: 05.01.2024 09:49:05
**/
#include<bits/stdc++.h>
#ifdef DEBUG_LOCAL
#include <mydebug/debug.h>
debug_helper deg;
#endif
#include <atcoder/string>
using namespace atcoder;
using ll = long long;
const int N = 1e6+4e5+5;
using namespace std;
int T,n,rm,al[N],len[N],sa[N],rk[N],m,ok[N],h[N],a[N],w[N],f[N];string s,t;
vector<int> le[205],ww[205];
struct st{
    vector<int> st[22]; int op;
    inline int cmp(int x,int y){return op ? max(x,y) : min(x,y);}
    inline void init(int _op,int m,int *a){
        op = _op;if(!m) return ;
        for(int i = 0;i <= 20;i ++) st[i].resize(m + 1);
        for(int i = 1;i <= m;i ++) st[0][i] = a[i];
        for(int j = 1;j <= __lg(m);j ++) for(int i = 1;i + (1 << j) - 1 <= m;i ++)
            st[j][i] = cmp(st[j-1][i],st[j-1][i+(1<<j-1)]);
    }inline int qry(int l,int r){
        if(l > r) return 0;
        int k = __lg(r - l + 1);
        return cmp(st[k][l],st[k][r-(1<<k)+1]);
    }
}st,ts[205];
inline void los(){
    cin >> s,s += '#',rm = s.size() - 1;
    cin >> n;
    for(int i = 1;i <= n;i ++) cin >> t,al[i] = s.size() + 1,s += t + '#',len[i] = t.size();
    for(int i = 1;i <= n;i ++) cin >> w[i];
    m = s.size();vector<int> _sa = suffix_array(s);s = " " + s;
    for(int i = 1;i <= m;i ++) sa[i] = _sa[i-1] + 1,rk[sa[i]] = i;
    for(int i = 1,k = 0;i <= m;h[rk[i ++]] = k) 
        for(k --,k = max(k,0);s[i + k] != '#' && s[i + k] == s[sa[rk[i] - 1] + k];k ++);
    st.init(0,m,h);
    auto lcp = [&](int i,int j){
        if(i == j) return m - sa[i] + 1;
        return st.qry(i + 1,j);
    };
    for(int i = 1;i <= n;i ++) le[len[i]].push_back(rk[al[i]]),ww[len[i]].push_back(i);
    // for(int i = 1;i <= m;i ++) cout << i << " " << s.substr(sa[i],m - sa[i] + 1) << "\n";
    for(int j = 1;j <= 200;j ++){
        sort(ww[j].begin(),ww[j].end(),[&](int x,int y){return rk[al[x]] < rk[al[y]];});
        sort(le[j].begin(),le[j].end());
        for(int i = 0;i < le[j].size();i ++) a[i+1] = w[ww[j][i]];
        ts[j].init(1,le[j].size(),a);
    }for(int i = rm;i >= 1;i --){
        f[i] = f[i + 1]; int k = rk[i],l,r,ql,qr,lstl = 1,lstr = m;
        for(int j = 1;j <= 200 && j + i - 1 <= rm;j ++){
            if(!le[j].size()) continue;
            for(l = lstl,r = k;l <= r;){
                int mid = (l + r) / 2;
                if(lcp(mid,k) >= j) r = mid - 1; else l = mid + 1;
            }ql = r + 1;
            for(l = k,r = lstr;l <= r;){
                int mid = (l + r) / 2;
                if(lcp(k,mid) >= j) l = mid + 1; else r = mid - 1;
            }qr = l - 1;
            int tl = lower_bound(le[j].begin(),le[j].end(),ql) - le[j].begin(),
                tr = upper_bound(le[j].begin(),le[j].end(),qr) - le[j].begin();
            f[i] = max(f[i],f[i + j] + ts[j].qry(tl+1,tr));
            lstl = ql,lstr = qr;
        }
    }cout << *max_element(f+1,f+n+1) << "\n";
}int main(){
    ios::sync_with_stdio(0),cin.tie(0);
    for(T = 1;T --;) los();
}
```

---

## 作者：Le0Chan (赞：1)

很套路的 ac 自动机+dp。

考虑对 $T$ 建出 ac 自动机。将每个串的权值挂在他在 trie 树上的末端节点。对于节点来说，定义 $mx_p$ 为上述权值。把 $S$ 拉到 $T$ 上进行匹配。对于 $S$ 的第 $i$ 位，假设当前匹配到了节点 $p$。则一直跳 $p$ 的失配指针可以得到所有满足其是 $T$ 中某个串的前缀，且是 $S[1,i]$ 的后缀的串。这一点由失配指针的定义是最长真后缀可知。

于是直接有了一个显然的 dp。方便起见，设 $len_p$ 为 $p$ 节点在 trie 树上的深度。

设 $dp_i$ 为匹配了 $S$ 的前 $i$ 位可得到的最大权值。则不断跳 $p$ 的失配指针。有 $dp_i=\max\{dp_{i-len_p}+mx_p\}$。

这样的复杂度是 $O(nh)$。其中 $h$ 为 fail 树高。考虑到题目满足 $|P_i|\le 200$，所以 trie 树高 $\le 200$，所以 fail 树高 $\le 200$，所以复杂度正确。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace Le0{
const int N=1e6+5;
int w[N],dp[N];
int n,m;
string s;
struct acam{
	int nt=1;
	int son[N][27],mx[N],len[N],fa[N];
	void build(string ss,int id){
		int l=ss.size(),p=1;
		for(int i=0;i<l;i++){
			if(!son[p][ss[i]-'a']) son[p][ss[i]-'a']=++nt;
			p=son[p][ss[i]-'a'];
			len[p]=i+1;
		}
		mx[p]=max(mx[p],w[id]);
	}
	void work(){
		queue<int> q;
		for(int i=0;i<26;i++) son[0][i]=1;
		q.push(1);
		while(q.size()){
			int x=q.front();q.pop();
			for(int i=0;i<26;i++){
				if(son[x][i]){
					q.push(son[x][i]);
					fa[son[x][i]]=son[fa[x]][i];
				}
				else{
					son[x][i]=son[fa[x]][i];
				}
			}
		}
	}
	void qry(){
		int p=1;
		for(int i=1;i<=n;i++){
			dp[i]=max(dp[i],dp[i-1]);
			p=son[p][s[i]-'a']; 
			for(int j=p;j;j=fa[j]){
				dp[i]=max(dp[i],dp[i-len[j]]+mx[j]);
			}
		}
	}
}ac;
string t[N];
int main(){
	cin>>s>>m;
	n=s.size();
	s=" "+s;
	for(int i=1;i<=m;i++) cin>>t[i];
	for(int i=1;i<=m;i++) cin>>w[i];
	for(int i=1;i<=m;i++) ac.build(t[i],i);
	ac.work();
	ac.qry();
	int ans=*max_element(dp+1,dp+1+n);
	cout<<ans<<"\n";
	return 0;
}
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0);
	return Le0::main();
}

```


---

## 作者：shinkuu (赞：0)

好久没写过 AC-Automaton 了。来一发。

有个显然的 dp 为 $dp_i=\max(dp_j+w[j+1,i])$，其中 $w[l,r]$ 表示字串 $[l,r]$ 对应的模式串的价值。时间复杂度大概是 $O(|S|\sum|P_i|)$ 的。显然不能过。

考虑这种有一个文本串，很多模式串匹配的题一般怎么做，容易发现可以用 AC-Automaton 维护。

先建出 AC-Automaton，然后将文本串丢进去匹配，每次根据 $S_i$ 在字典图上移动。到 $u$ 点后，不断跳 $fail$ 指针，每遇到一个 trie 树上的节点，且它代表某一个模式串 $j$ 的结尾，则可以转移 $dp_i=\max(dp_i,dp_{i-len_j}+w_j)$，$len$ 为模式串长度。还有不管这一位的转移 $dp_i=\max(dp_i,dp_{i-1})$。

因为 $\max P_i\le200$，每次跳 $fail$ 至少让深度 $-1$，所以每次跳 $fail$ 最多跳 $200$ 次。时间复杂度即为 $O(|S|\max|P_i|)$。

code：

```cpp
int n,m,dp[N],ed[N];
char s[N],t[N];
struct AC_Automaton{
	int cur,c[M],l[M],fail[M],tr[M][26];
	void insert(char *str,int k){
		int p=0,len=strlen(str+1);
		rep(i,1,len){
			int x=str[i]-'a';
			if(!tr[p][x]){
				tr[p][x]=++cur;
			}
			p=tr[p][x];
		}
		ed[k]=p,l[p]=len;
	}
	void build(){
		queue<int> q;
		rep(i,0,25){
			if(tr[0][i]){
				q.push(tr[0][i]);
			}
		}
		while(q.size()){
			int u=q.front();
			q.pop();
			rep(i,0,25){
				int &v=tr[u][i];
				if(tr[u][i]){
					fail[v]=tr[fail[u]][i];
					q.push(v);
				}else{
					v=tr[fail[u]][i];
				}
			}
		}
	}
	void solve(){
		int p=0;
		rep(i,1,n){
			int x=s[i]-'a';
			p=tr[p][x];
			int u=p;
			while(u){
				dp[i]=max(dp[i],dp[i-l[u]]+c[u]);
				u=fail[u];
			}
			dp[i]=max(dp[i],dp[i-1]);
		}
	}
}AC;
void Yorushika(){
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	rep(i,1,m){
		scanf("%s",t+1);
		AC.insert(t,i);
	}
	rep(i,1,m){
		scanf("%d",&AC.c[ed[i]]);
	}
	AC.build();
	AC.solve();
	printf("%d\n",dp[n]);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

