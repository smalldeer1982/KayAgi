# 「TAOI-2」Ciallo～(∠・ω< )⌒★

## 题目背景

柚子厨差不多得了。

~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)~(·<)

![](https://cdn.luogu.com.cn/upload/image_hosting/0nqiwonz.png)

## 题目描述

小 δ 喜欢造词。他学习了一种造词方法。

首先，他拥有一个「模板串」，设为 $s$。然后他会选择一对 $1 \le l \le r \le |s|$，将 $s$ 的第 $l$ 至 $r$ 个字符删掉，把两边的字符串拼起来，他设得到的这个新字符串为 $s'$。

接下来，他会选择一对新的 $1 \le l' \le r' \le |s'|$，然后设 $s'$ 的第 $l'$ 至 $r'$ 个字符组成的字符串为 $s''$。他所造出的这个词就是 $s''$。

例如，如果「模板串」为 $s=\texttt{cciaohalloo}$，那么一种造词方法是，选择 $l=5$，$r=7$，得到 $s'=\texttt{ccialloo}$，然后选择 $l'=2$，$r'=7$，得到 $s''=\texttt{ciallo}$。

现在小 δ 有一个「目标串」 $t$，他想知道有多少种不同的方案，可以使用「模板串」$s$ 造出单词 $t$。定义两种方案相同当且仅当选择的 $l,r,l',r'$ 均相同。

## 说明/提示

### 数据范围

**本题采用捆绑测试**。

- Subtask 0（6 points）：$|s| \le 400$，$|t| \le 200$。
- Subtask 1（10 points）：$|s| \le 700$，$|t| \le 300$。
- Subtask 2（10 points）：$\forall i,j,s_i=t_j$。
- Subtask 3（10 points）：$|t|=1$。
- Subtask 4（20 points）：$|s| \le 10^4$，$|t| \le 3 \times 10^3$。
- Subtask 5（14 points）：$|t|=2$。
- Subtask 6（30 points）：无特殊限制。

对于所有测试数据，$1 \le |s| \le 4 \times 10^5$，$1 \le |t| \le 2 \times 10^5$。$s,t$ 只包含小写英文字母。

## 样例 #1

### 输入

```
aabbaaba
aba```

### 输出

```
23```

## 样例 #2

### 输入

```
ciaohallo
ciallo```

### 输出

```
2```

## 样例 #3

### 输入

```
babacbbaababbacbababbabbbaaabaabababbabbabababba
ababab```

### 输出

```
1535```

## 样例 #4

### 输入

```
sssssssssssssssssssssssssssssssssssss
sss```

### 输出

```
15470```

## 样例 #5

### 输入

```
abcbbbcbcbcbacbacbaaabcbcbcbaabacbca
cb```

### 输出

```
3995```

# 题解

## 作者：251Sec (赞：19)

昨天晚上看到室友在玩一个叫千恋万花的游戏，[中间忘了](https://www.luogu.com.cn/paste/rsy48wor)，现在我才认清我室友自私自利的嘴脸，根本不值得我给他分享好东西。 

---

一句话题意：求字符串 $s$ 删去每个区间后字符串 $t$ 出现的次数之和。

下文字符串下标从零开始编号。

删去一个区间等价于取一个前缀 $pre$ 和一个后缀 $suf$，满足 $|pre|+|suf|<|s|$。$t$ 在 $pre$ 或 $suf$ 内部的情况是 trivial 的，我们可以一遍字符串匹配处理掉，考虑 $t$ 横跨两边的情况。

考虑枚举 $t$ 的哪一部分在 $pre$ 中，设这一部分为 $t_{0..i}$，则我们求出所有 $s$ 中匹配 $t_{0..i}$ 的左端点，设为 $A_i$，求出所有匹配 $t_{i+1..|t|-1}$ 的右端点，设为 $B_i$，则对答案的贡献为 $\sum\limits_{x \in A_i,y \in B_i}[y-x \ge |t|]$。

乍一看 $\sum |A_i|$ 和 $\sum |B_i|$ 都是 $O(n^2)$ 级别的，似乎没有什么高效算法，但是我们注意到 $\forall i < j, A_j \subseteq A_i, B_i \subseteq B_j$，于是我们考虑只记录 $A_i$ 和 $B_i$ 在 $i$ 增加时发生的变化，可以发现总变化量是 $O(n)$ 的，这样只要维护变化就可以维护出每个时候的 $A_i$ 和 $B_i$，然后每次 $A_i$ 和 $B_i$ 变化时，$\sum\limits_{x \in A_i,y \in B_i}[y-x \ge |t|]$ 的改变可以用一个树状数组统计。

考虑怎么维护 $A_i$ 和 $B_i$ 的变化，我们对于每个 $s$ 中的位置可以二分加哈希求出以这个位置为左端点能匹配的 $t$ 的最长长度，这样就可以维护出 $A_i$ 的变化，类似地，可以维护出 $B_i$ 的变化。

总复杂度 $O(n \log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int bas = 256, mod = 1e9 + 7;
int n, m;
string s, t;
int hasS[400005], hasT[400005];
int basPw[400005];
int GetHashS(int l, int r) { return (hasS[r] - 1ll * hasS[l - 1] * basPw[r - l + 1] % mod + mod) % mod; }
int GetHashT(int l, int r) { return (hasT[r] - 1ll * hasT[l - 1] * basPw[r - l + 1] % mod + mod) % mod; }
vector<int> lcg[400005], rcg[400005];
struct BIT {
    ll f[400005];
    void Modify(int i, int x) {
        for (; i <= n; i += i & -i) f[i] += x;
    }
    ll Query(int l, int r) {
        if (r < l) return 0;
        ll res = 0; l--;
        for (; r; r &= r - 1) res += f[r];
        for (; l; l &= l - 1) res -= f[l];
        return res;
    }
} tf, tg;
ll sum, ans;
void ModifyF(int i, int x) {
    tf.Modify(i, x);
    sum += tg.Query(1, max(i - m, 0)) * x;
}
void ModifyG(int i, int x) {
    tg.Modify(i, x);
    sum += tf.Query(min(i + m, n + 1), n) * x;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> s >> t;
    n = s.length(); m = t.length(); s = '$' + s; t = '$' + t;
    for (int i = 1; i <= n; i++) hasS[i] = (1ll * hasS[i - 1] * bas + s[i]) % mod;
    for (int i = 1; i <= m; i++) hasT[i] = (1ll * hasT[i - 1] * bas + t[i]) % mod;
    basPw[0] = 1;
    for (int i = 1; i <= max(n, m); i++) basPw[i] = 1ll * basPw[i - 1] * bas % mod;
    for (int i = 1; i <= n; i++) {
        int l = 1, r = min(m, n - i + 1), res = 0;
        while (l <= r) {
            int mid = l + r >> 1;
            if (GetHashS(i, i + mid - 1) == GetHashT(1, mid)) {
                res = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        lcg[res].emplace_back(i);
    }
    for (int i = 1; i <= n; i++) {
        int l = 1, r = min(m, i), res = 0;
        while (l <= r) {
            int mid = l + r >> 1;
            if (GetHashS(i - mid + 1, i) == GetHashT(m - mid + 1, m)) {
                res = mid;
                l = mid + 1;
            }
            else {
                r = mid - 1;
            }
        }
        rcg[m - res + 1].emplace_back(i);
    }
    for (int i = 0; i <= m; i++) for (int j : lcg[i]) ModifyG(j, 1);
    for (int i : rcg[1]) ModifyF(i, 1);
    for (int i = 1; i < m; i++) {
        for (int j : lcg[i - 1]) ModifyG(j, -1);
        for (int j : rcg[i + 1]) ModifyF(j, 1);
        ans += sum;
    }
    for (int i = 1; i <= n - m + 1; i++) {
        if (GetHashS(i, i + m - 1) == GetHashT(1, m)) {
            int x = i, y = i + m - 1;
            ans += 1ll * (n - y + 1) * (n - y) / 2;
            ans += 1ll * (x - 1) * x / 2;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Register_int (赞：10)

用 $S(l,r)$ 来表示 $S$ 左端点为 $l$，右端点为 $r$ 的子串。先来观察 $l'$ 和 $r'$ 能选在什么地方。

先来计算 $T$ 直接出现在 $S$ 中的情况。合法的删去子串的方案只有两类：均在 $T$ 左侧或均在 $T$ 右侧，可以直接计算。

其余情况不难发现满足三个要求：

- $r'-l'\ge m$。
- $S(l',r')$ 与 $T$ 的最长公共前、后缀长度之和 $\ge m$。

分别对 $S$ 的正反串跑一遍扩展 KMP，即可得到 $S$ 所有子串与 $T$ 的最长公共前、后缀长度。下文设 $x_i=\text{LCP}(S(i,n), T)$，$y_i=\text{LCS}(S(1,i), T)$。

先来计算方案数。假设我们已经选定了 $l',r'$，那么我们需要选定一段区间 $l,r$ 来满足删除后该串与 $T$ 相等。由于区间 $[l,r]$ 的长度固定，我们只需要考虑 $l$ 在 $x_i$ 上删去的后缀长度。根据前后缀长度的限制，可以得到方案数为：

$$\min(m,x_{l'}+1)-\max(1,m-y_{r'})$$

很明显，前半部分只跟 $x$ 有关，后半部分只跟 $y$ 有关，可以拆开考虑。现在能造成贡献的 $l',r'$ 满足：

- $l'\le r'-m$
- $m-x_{l'}\le y_{r'}$

显然是一个二维偏序关系，使用树状数组统计答案。时间复杂度 $O(n+m+n\log m)$。

~~鲜花：凭啥开 2s，我最大点就跑了 23ms。~~

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 4e5 + 10;

int z[MAXN];

inline 
void getz(char *s, int n) {
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; i++) {
		z[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
		while (i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
}

inline 
void exkmp(char *s, char *t, int n, int *p) {
	for (int i = 1, l = 0, r = 0; i <= n; i++) {
		if (i <= r) p[i] = min(z[i - l + 1], r - i + 1);
		while (i + p[i] <= n && s[i + p[i]] == t[p[i] + 1]) p[i]++;
		if (i + p[i] - 1 > r) l = i, r = i + p[i] - 1;
	}
}

ll c[MAXN], d[MAXN]; int n, m;

inline 
void add(int k, int x) {
	for (int i = ++k; i <= m + 1; i += i & -i) c[i]++, d[i] += x;
}

inline 
ll ask(int k) {
	ll res = 0;
	for (int i = ++k; i; i &= i - 1) res += c[i];
	return res;
}

inline 
ll query(int k) {
	ll res = 0;
	for (int i = ++k; i; i &= i - 1) res += d[i];
	return res;
}

inline 
ll s2(ll n) {
	return (n + 1) * n / 2;
}

int x[MAXN], y[MAXN]; ll ans;

char s[MAXN], t[MAXN];

int main() {
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1), m = strlen(t + 1);
	getz(t, m), exkmp(s, t, n, x);
	reverse(s + 1, s + n + 1), reverse(t + 1, t + m + 1);
	getz(t, m), exkmp(s, t, n, y), reverse(y + 1, y + n + 1);
	for (int i = 1; i <= n; i++) if (y[i] == m) ans += s2(i - m) + s2(n - i);
	for (int i = m + 1; i <= n; i++) {
		add(m - x[i - m], min(m, x[i - m] + 1));
		ans += query(y[i]) - max(1, m - y[i]) * ask(y[i]);
	}
	printf("%lld", ans);
}
```

---

## 作者：_Ch1F4N_ (赞：7)

赛时没仔细想，赛后才发现并不难。

将 $l,r$ 与 $l',r'$ 是否相交分开讨论。

假若不相交，那么 $l',r' < l$ 或者 $l',r' > r$ 并且 $[l',r']$ 内的字符一定与字符串 $t$ 匹配上了，考虑做一遍字符串匹配再利用乘法原理计算 $l,r$ 的取值数量即可。

假若相交，那么就是区间 $[l',l]$ 与区间 $[r,r']$ 拼接起来构成了字符串 $t$，不难想到这一定是一段 $t$ 的前缀后缀拼接起来，所以自然可以考虑对于 $s$ 字符串中每个位置求出其与 $t$ 匹配的最大前缀后缀，然后实际上问题就变成了一个二维数点，考虑离线扫描一遍，线段树维护贡献即可。

考虑使用字符串哈希加上二分快速的求出相匹配的最大前缀后缀，加上线段树，总复杂度 $O(n \log n)$，其中 $n$ 是字符串长度。

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
//#define lowbit(x) (x&-(x))
using namespace std;
const int maxn = 1e6+114;
const int base = 1331;
int _pow[maxn];
int pre[maxn];//s的前缀哈希值
int Pre[maxn];//t的前缀哈希值
int L[maxn],R[maxn];//从s第i位开始匹配往左往右最多匹配多少位
char s[maxn],t[maxn];//字符串 s,t 下标从 1 开始
int ans;
int lens,lent;
bool check1(int pos,int len){
	if(pos-len+1<1) return false;
	int lt=pos-len+1,rt=pos;
	int Lt=lent-len+1,Rt=lent;
	return (pre[rt]-pre[lt-1])*_pow[Lt]==(Pre[Rt]-Pre[Lt-1])*_pow[lt];
}
bool check2(int pos,int len){
	if(pos+len-1>lens) return false;
	int lt=pos,rt=pos+len-1;
	int Lt=1,Rt=len;
	return (pre[rt]-pre[lt-1])*_pow[Lt]==(Pre[Rt]-Pre[Lt-1])*_pow[lt];
}
void init(){//预处理好以上所有数组 
	lens=strlen(s)-1;
	lent=strlen(t)-1;
	_pow[0]=1;
	for(int i=1;i<maxn;i++) _pow[i]=_pow[i-1]*base;
	for(int i=1;i<=lens;i++) pre[i]=pre[i-1]+(int)(s[i])*_pow[i];
	for(int i=1;i<=lent;i++) Pre[i]=Pre[i-1]+(int)(t[i])*_pow[i];
	for(int i=1;i<=lens;i++){
		int l=0,r=lent+1;
		while(l+1<r){
			int mid=(l+r)>>1;
			if(check1(i,mid)==true) l=mid;
			else r=mid;
		}
		L[i]=l;
		l=0,r=lent+1;
		while(l+1<r){
			int mid=(l+r)>>1;
			if(check2(i,mid)==true) l=mid;
			else r=mid;
		}
		R[i]=l;
	}
	for(int i=1;i<=lens;i++){
		if(R[i]==lent){//匹配区域与删除区域不交 
			if(i>=1) ans+=(i-1)*i/2;
			if(i<=lens-lent) ans+=(lens-(i+lent-1))*(lens-(i+lent-1)+1)/2;
		}
	}
} 
int tr[maxn<<2],tag[maxn<<2];
#define ls(cur)(cur<<1)
#define rs(cur)(cur<<1|1)
void pushup(int cur){
	tr[cur]=tr[ls(cur)]+tr[rs(cur)];
}
void pushdown(int cur,int lt,int rt){
	int mid=(lt+rt)>>1;
	tr[ls(cur)]+=tag[cur]*(mid-lt+1);
	tag[ls(cur)]+=tag[cur];
	tr[rs(cur)]+=tag[cur]*(rt-mid);
	tag[rs(cur)]+=tag[cur];
	tag[cur]=0;
}
void add(int cur,int lt,int rt,int l,int r,int v){
    if(lt>rt) return ;
	if(l<=lt&&rt<=r){
		tr[cur]+=v*(rt-lt+1),tag[cur]+=v;
		return ;
	}
	if(rt<l||lt>r) return ;
	pushdown(cur,lt,rt);
	int mid=(lt+rt)>>1;
	add(ls(cur),lt,mid,l,r,v);
	add(rs(cur),mid+1,rt,l,r,v);
	pushup(cur);
}
int query(int cur,int lt,int rt,int l,int r){
    if(lt>rt) return 0;
	if(l<=lt&&rt<=r) return tr[cur];
	if(rt<l||lt>r) return 0;
	pushdown(cur,lt,rt);
	int mid=(lt+rt)>>1;
	return query(ls(cur),lt,mid,l,r)+query(rs(cur),mid+1,rt,l,r);
}
signed main(){
	scanf("%s%s",s+1,t+1);
    s[0]=t[0]='a';
	init();
	for(int i=lens;i>=1;i--){
		if(i+lent<=lens){
			add(1,1,lent,1,min(L[i+lent],lent-1),1);
		}
		ans+=query(1,1,lent,max((int)(1),lent-R[i]),lent-1);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：xtzqhy (赞：7)

柚子厨差不多得了。

设字符串 $s$ 的长度为 $n$，$t$ 的长度为 $m$。

我们先对 $[l,r]$ 和 $[l',r']$ 是否相交进行讨论。

若不交，则说明删除没有任何影响。那么我们找出 $s$ 中的所有 $t$，设匹配右端点为 $i$，则方案数为 $\binom{i-m}{2}+\binom{n-i}{2}$。

若相交，则合法情况一定类似下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/w9lqmjrz.png)

图中 $x_i,y_i$ 分别表示 $\operatorname{LCP}(s(i,n),t),\operatorname{LCS}(s(1,i),t)$，红色部分表示重复部分。

重复部分的长度为 $x_{l'}+y_{r'}-m$，则方案数为 $x_{l'}+y_{r'}-m+1$。

可以发现，这部分贡献的 $[l',r']$ 需要满足：
$$
r'-l'\ge m
\\
x_{l'}+y_{r'} \ge m
\\
x_{l'} \neq m
\\
y_{r'} \neq m
$$
不能等于 $m$ 是因为这部分贡献已经在前面算过了，不能重复计算。

可以发现，这是一个二维数点。

因为不能等于 $m$，所以在数点时还要把这部分的贡献减去。

$x_i,y_i$ 可以二分+哈希求出，二维数点可以树状数组维护，总复杂度为 $O(n\log n)$。
```cpp
#include"bits/stdc++.h"
#define re register
#define int long long
#define lb(x) (x&(-x))
using namespace std;
const int maxn=4e5+10,base=131,mod=1e9+7;
int n,m,ans;
char s1[maxn],s2[maxn];
int pw[maxn];
int h1[maxn],h2[maxn];
int x[maxn],y[maxn];
struct BIT{
    int tr[maxn];
    //因为会用到 0 这个位置，所以需要整体加个偏移量。
    inline void add(int x,int val){++x;while(x<maxn) tr[x]+=val,x+=lb(x);}
    inline int query(int x){++x;int res=0;while(x>0) res+=tr[x],x-=lb(x);return res;}
}a,b;
inline int calc1(int l,int r){return ((h1[r]-h1[l-1]*pw[r-l+1]%mod)%mod+mod)%mod;}
inline int calc2(int l,int r){return ((h2[r]-h2[l-1]*pw[r-l+1]%mod)%mod+mod)%mod;}
inline bool check1(int pos,int len){
    if(pos+len-1>n) return 0;
    return calc1(pos,pos+len-1)==calc2(1,len);
}
inline bool check2(int pos,int len){
    if(pos-len+1<1) return 0;
    return calc1(pos-len+1,pos)==calc2(m-len+1,m);
}
inline void init(){
    pw[0]=1;
    for(re int i=1;i<maxn;++i) pw[i]=pw[i-1]*base%mod;
    for(re int i=1;i<=n;++i) h1[i]=(h1[i-1]*base+s1[i])%mod;
    for(re int i=1;i<=m;++i) h2[i]=(h2[i-1]*base+s2[i])%mod;
    for(re int i=1,l,r,mid,res;i<=n;++i){
        l=0,r=m,res=0;
        while(l<=r){
            mid=(l+r)>>1;
            if(check1(i,mid)) res=mid,l=mid+1;
            else r=mid-1;
        }
        x[i]=res;
        l=0,r=m,res=0;
        while(l<=r){
            mid=(l+r)>>1;
            if(check2(i,mid)) res=mid,l=mid+1;
            else r=mid-1;
        }
        y[i]=res;
    }
}
signed main(){
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
#endif
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>(s1+1)>>(s2+1);n=strlen(s1+1),m=strlen(s2+1);
    init();
    for(re int i=1;i<=n;++i) if(y[i]==m) ans+=((i-m)*(i-m+1)/2+(n-i)*(n-i+1)/2);
    for(re int i=m+1;i<=n;++i){
        a.add(m-x[i-m],1),b.add(m-x[i-m],x[i-m]);
        ans+=b.query(y[i])+(y[i]-m+1)*a.query(y[i]);
        if(y[i]==m) ans-=a.query(y[i]); 
        ans-=a.query(0);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Jeefy (赞：6)

# 「TAOI-2」Ciallo～(∠・ω< )⌒★ 题解

不难发现，答案可以分成两种：

- 整段的

- 中间删一点，两端凑一起的

考虑分开计算贡献。

如果 $s$ 中存在子串等于 $t$，那么自然，可以删左边的任何一段，或者右边的任何一段。

不妨设子串开始的位置为 $i$，于是其贡献为 $(1 + 2 + \cdots + i - 1) + (1 + 2 + \cdots +(|s| - i - |t| + 1))$。

**接下来**考虑中间删一点，两端凑一起的情况。

令 $f_i$ 表示 $s$ 从 $i$ 开始与 $t$ 的最长相同前缀的长度，$g_i$ 表示 $s$ 从 $i$ 向前与 $t$ 的最长相同后缀的长度。

**NOTICE**：由于需要排除第一种情况，所以对于 $f, g$，都需要对于 $|t| - 1$ 取 $\min$。

这部分可以通过哈希和二分完成（或者 Z 函数也行）

于是需要考虑 $f, g$ 如何相互贡献。

不难发现，对于两个端点 $i \le j$ 可以做出贡献，需要满足：

- $i + |t| - 1 \lt j$。考虑中间必须删一点，所以必须**严格小于**，这样才不会重叠或者接在一起。

- $f_i + g_j \ge |t|$。这样才能凑出完整的目标串。

那么其最终的贡献为 $f_i + g_j - |t| + 1$。

于是可以得到表达式：

$$
\sum_{i = 1}^n \sum_{j = i + |t|}^n [f_i+ g_j \ge |t|](f_i + g_j - |t| + 1)
$$

不难发现可以倒着扫一遍，然后利用树状数组求和即可。

> 考场上以防万一，我用的双哈希……但好像有点多余。

```cpp
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;
const int N = 4e5 + 7, BASE = 131, mod = 1331;

string s, t;

using hI = unsigned long long;
using hP = unsigned int;

hI sha[N], tha[N];
hI sha2[N], tha2[N];
hI ofs[N], ofs2[N];

hI shash(int l, int r) {
    hI sha1 = sha[r] - sha[l - 1] * ofs[r - l + 1];
    sha1 += (sha2[r] + mod - sha2[l - 1] * ofs2[r - l + 1] % mod) % mod;
    return sha1;
}

hI thash(int l, int r) {
    hI tha1 = tha[r] - tha[l - 1] * ofs[r - l + 1];
    tha1 += (tha2[r] + mod - tha2[l - 1] * ofs2[r - l + 1] % mod) % mod;
    return tha1;
} 

int f[N], g[N];

#define lowbit(i) (i & -i)
// 这是倒着的树状数组！
struct BIT {
    long long b[N];
    void update(int i, int x) {
        for (; i; i -= lowbit(i)) b[i] += x; 
    }
    long long query(int i) {
        long long r = 0;
        for(; i < N; i += lowbit(i)) r += b[i];
        return r;
    }
} cnt, sum;

long long get(long long x) {
    return (1 + x) * x / 2;
}

int main() {
    cin >> s >> t;

    int n = s.size(), m = t.size();
    for (int i = 1; i <= n; ++i) {
        sha[i] = sha[i - 1] * BASE + s[i - 1] - 2;
        sha2[i] = (sha2[i - 1] * 17 % mod + s[i - 1] - 2) % mod;
    }

    for(int i = 1; i <= m; ++i) {
        tha[i] = tha[i - 1] * BASE + t[i - 1] - 2;
        tha2[i] = (tha2[i - 1] * 17 % mod + t[i - 1] - 2) % mod;
    }

    ofs[0] = ofs2[0] = 1;
    for (int i = 1, ie = max(s.size(), t.size()); i <= ie; ++i) {
        ofs[i] = ofs[i - 1] * BASE;
        ofs2[i] = ofs2[i - 1] * 17 % mod; 
    }

    long long ans = 0;

    // 简单倍增
    int W = 1 << ((int)log2(t.size()) + 1);    
    for (int i = 1; i <= n; ++i) {
        f[i] = g[i] = -1;

        for (int w = W; w; w >>= 1) {
            if (i + f[i] + w - 1 <= n && 1 + f[i] + w - 1 <= m 
                && shash(i, i + f[i] + w - 1) == thash(1, 1 + f[i] + w - 1))
                f[i] += w;

            if (i - g[i] - w + 1 > 0 && m - g[i] - w + 1 > 0 
                && shash(i - g[i] - w + 1, i) == thash(m - g[i] - w + 1, m))
                g[i] += w;
        }

        if (f[i] >= m) ans += get(i - 1) + get(n - i - m + 1), --f[i];
    }

    for (int i = n; i > m; --i) {
        if (g[i] >= m) --g[i];
        cnt.update(g[i], 1);
        sum.update(g[i], g[i]);

        ans += sum.query(m - f[i - m]) + (f[i - m] - m + 1) * cnt.query(m - f[i - m]);
    }

    cout << ans << '\n'; 
}
```


---

## 作者：Coffins (赞：5)

## 前言
如果你会 exKMP 的话，这就是个相当裸的题，

就算不会也可以二分哈希，也不困难，

只要别像我跟个傻子一样死磕 KMP 就行。
## 简化题意
题目其实**大概**就是让你从 $S$ 里抠出来不相邻的两段子串，求能拼成 $T$ 的方案数。

为什么说大概呢？因为可以从 $S$ 中直接选出来 $T$。

这种情况单独直接算一下即可。

## 解法

设 $S$，$T$ 长度分别为 $n$，$m$。

### Sustack 0&1&3&4&5

把 $T$ 拆开，对所有前缀后缀做 KMP，直接统计答案。

期望复杂度：$O(nm)$。

### Substack 2

组合数学硬刚。

### Substack 6

考虑 Subatck 0&1&3&4&5 的做法，实际上可以把 $a_i=\operatorname{LCP}(T,S[i:n])$ 预处理出来来算出每个位置向前能贡献最长的前缀，后缀同理（设处理后是 $b_i$），把 $S$，$T$ 翻转即可。

#### 处理 $\{a_n\}$ 和 $\{b_n\}$

如果你会 exKMP，一眼 exKMP，可以 $O(n+m)$。

如果你比较熟二分哈希，一眼二分哈希，可以 $O(m+n+n\log m)$。

如果你死磕 KMP。。。

反正我比较菜没磕出来。。。

#### 计算答案

考虑处理出来 $\{a_n\}$ 和 $\{b_n\}$ 后怎么办。

发现 $i$，$j$ 只要满足：
$$i+m\le j$$
$$a_i+b_j\ge m$$ 

就可以产生一定贡献~~具体多少请读者自行计算。~~

然后发现是个二维偏序，

然后就完事了捏。

复杂度：$O(n+m+n\log m)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Max=6e5+5;
//exKMP
int z[Max],p[Max];
char s[Max],t[Max];
int n,m;
void Z(char* s,int n)
{
	memset(z,0,sizeof(z));
	z[1]=n;
	int l=0,r=0;
	for(int i=2;i<=n;i++)
	{
		if(i<=r)
		{
			z[i]=min(z[i-l+1],r-i+1);
		}
		while(i+z[i]<=n&&s[i+z[i]]==s[z[i]+1])
		{
			z[i]++;
		}
		if(i+z[i]-1>r)
		{
			l=i;
			r=i+z[i]-1;
		}
	}
}
void exkmp(char* s,int n,char* t,int m)
{
	Z(t,m);
	memset(p,0,sizeof(p));
	int l=0,r=0;
	for(int i=1;i<=n;i++)
	{
		if(i<=r)
		{
			p[i]=min(z[i-l+1],r-i+1);
		}
		while(i+p[i]<=n&&s[i+p[i]]==t[p[i]+1])
		{
			p[i]++;
		}
		if(i+p[i]-1>r)
		{
			l=i;
			r=i+p[i]-1;
		}
	}
}
//
//BIT
long long tr[Max],d[Max];
#define lowbit(x) ((x)&(-x))
void add(int x,int val)
{
	x++;
	while(x<=m+1)
	{
		d[x]+=val;
		tr[x]++;
		x+=lowbit(x);
	}
}
long long query(int x)
{
	long long ans=0,sum=0,val=x;
	x++;
	while(x)
	{
		ans+=d[x];
		sum+=1ll*tr[x]*max(1ll,m-val);
		x-=lowbit(x);
	}
	return ans-sum;
}
//
int tog[2][Max];
long long ans=0;
int main()
{
	cin>>s+1>>t+1;
	n=0,m=0;
	while(s[++n]!='\0');
	while(t[++m]!='\0');
	n--;
	m--;
	exkmp(s,n,t,m);
	for(int i=1;i<=n;i++)
	{
		tog[0][i]=p[i];//处理 a_i
		//cout<<tog[0][i]<<' ';
	}//cout<<'\n';
	reverse(s+1,s+n+1);
	reverse(t+1,t+m+1);
	exkmp(s,n,t,m);
	for(int i=1;i<=n;i++)
	{
		tog[1][i]=p[n-i+1];//处理 b_i
		if(p[n-i+1]==m)
		{
			ans+=1ll*(n-i)*(n-i+1)/2;//单独处理T
			ans+=1ll*(i-m)*(i-m+1)/2;
		}
	}
	for(int i=m+1;i<=n;i++)
	{
		add(m-tog[0][i-m],min(m,tog[0][i-m]+1));
		ans+=query(tog[1][i]);//二维偏序可爱捏
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：MaxBlazeResFire (赞：5)

**这里是一种极为暴力的使用后缀自动机的码量巨大的做法 ~~（再给我 20 分钟就调出来了啊啊啊啊啊啊啊）~~。**

记串 $s$ 的长度为 $n$，串 $t$ 的长度为 $m$。

首先，如果串 $t$ 能够完好无损地出现在 $s$ 中，对于每一个 $t$，它出现位置两侧的任意一个子区间都可以被第一次选择。故 $t$ 每在 $[p,p+m-1]$ 出现一次，会带来 $\displaystyle\frac{p(p-1)+(n+1-m-p)(n+2-m-p)}{2}$ 的贡献。这里我选择在最后跑一遍 $\rm KMP$ 来统计答案。

否则 $t$ 就被分为了 $[1,p]$ 与 $[p+1,m]$ 两个部分。问题转变为了求有多少对 $l+1<r$（因为不能选择空区间删去），使得 $t[1,p]$ 是 $s[1,l]$ 的后缀且 $t[p+1,m]$ 是 $s[r,n]$ 的前缀。

第一个想法，我们考虑对 $s$ 建立后缀自动机后跑线段树合并。然后我们在 $\rm SAM$ 上扔两个动态代表 $t[1,p]$ 与 $t[p+1,m]$ 的指针，枚举 $p$ 的时候移动它们。前缀串移动一步即可，后缀串判一下 $\rm parent$ 树上的长度关系也可以做到 $O(1)$。

好，现在我们得到了两棵值域线段树 $S,T$，我们想要知道有多少种从 $S$ 中选出 $l$ 并从 $T$ 中选出 $r$ 的方式使得 $l+1<r$。我们发现，这个东西复杂度至少是 $O(n)$（甚至可能还做不到线性），而算上枚举 $p$ 的复杂度，显然不行。

怎么优化这个东西呢？我们欣然发现，$t[p+1,m]$ 显然是在 $\rm parent$ 树的一条祖先链上 **深度递减地** 移动的，但 $t[1,p]$ 的移动却杂乱无章。怎么办呢？很明显，对 $s$ 建立反串的后缀自动机，那么 $t^T[1,p]$ 在反串 $\rm SAM$ 上随着 $p$ 的增长，移动轨迹也是一条祖先链，且 **深度递增**。

也就是说，考虑维护集合 $\rm S,T$ 分别表示 $t[p+1,m]$ 的所有出现位置末尾与 $t[1,p]$ 的所有出现位置开头（反串中出现位置的末尾），那么 $p$ 每移动一步，我们可能会往 $S$ 中加入一些元素；相反地，我们可能会从 $T$ 中删除一些元素。我们想要知道，每一次移动后，有多少种从 $S$ 中选出 $r$，从 $T$ 中选出 $l$ 的方式，使得 $r\geq l+m$。

很明显，我们用两个树状数组分别维护 $S$ 中 $r$ 的变化与 $T$ 中 $l+m$ 的变化就行了。

那么我们每走一步，怎么知道添加了哪些元素，又删除了哪些元素呢？换句话说，**我在祖先链上向上 / 向下走一步时，我的 $\rm endpos$ 集合会多 / 少哪些元素呢？**

记我们出发的起点（以向上走为例）为 $st$，从 $u$ 走到 $link_u$ 时，所有满足 $lca(pre,st)=link_u$ 的前缀节点 $pre$ 的贡献会被加入。那么我们只需要在一开始求出所有前缀节点与 $st$ 的最近公共祖先 $w$，然后把 $pre$ 对应在原串的位置扔到 $w$ 里面；之后走到 $w$ 的时候在树状数组里修改就行。

问题来了，怎么找这个 $st$ 呢？我们只需要在一开始二分 $t$ 然后暴力匹配，找到它在正串 / 反串中出现的最长后缀 / 前缀就行了。

总复杂度为 $O(n\log n)$。还有不明白的地方可以看参考代码。

（实际上就是把正解搬到后缀自动机上了……这样可能求解变化量的时候更直观些吧？）

```cpp
#include<bits/stdc++.h>
using namespace std;

#define MAXN 800005

int n,m,edp[MAXN],edn[MAXN];
int minp,maxp,Mpreach,Mnreach;
long long Ans;
int trAdd[MAXN],trSub[MAXN],Nxt[MAXN][26],border[MAXN];
char s[MAXN],t[MAXN];

vector< pair<int,int> > pathup,pathdn;

inline void add( int *tr , int x , int k ){ for( ; x <= MAXN ; x += x & -x ) tr[x] += k; }
inline int sum( int *tr , int x ){ int ret = 0; for( ; x ; x -= x & -x ) ret += tr[x]; return ret; }

struct SAM{
	int nodecnt,nxt[MAXN][26],maxlen[MAXN],link[MAXN];
	int f[MAXN][20],dep[MAXN];
	vector<int> E[MAXN],Savs[MAXN];
	inline void init(){ nodecnt = 1; }
	inline int insert( int last , int ch ){
		int cur = ++nodecnt,p = last; maxlen[cur] = maxlen[p] + 1;
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
		for( int i = 1 ; i <= nodecnt ; i ++ ) E[link[i]].emplace_back( i );
		for( int i = 1 ; i <= nodecnt ; i ++ ) f[i][0] = link[i];
		for( int j = 1 ; j <= 19 ; j ++ )
			for( int i = 1 ; i <= nodecnt ; i ++ )
				f[i][j] = f[f[i][j - 1]][j - 1];
	}
	inline void dfs( int x , int fa ){
		dep[x] = dep[fa] + 1;
		for( int v : E[x] ) dfs( v , x );
	}
	inline int Lca( int u , int v ){
		if( dep[u] != dep[v] ){
			if( dep[u] < dep[v] ) swap( u , v );
			for( int i = 19 ; ~i ; i -- )
				if( dep[f[u][i]] <= dep[v] ) continue;
				else u = f[u][i];
			u = f[u][0];
		}
		if( u == v ) return u;
		for( int i = 19 ; ~i ; i -- )
			if( f[u][i] == f[v][i] ) continue;
			else u = f[u][i],v = f[v][i];
		return f[u][0];
	}
	inline int match( int x , int typ ){
		int now = 1;
		if( typ == 0 ){
			for( int i = x ; i <= m ; i ++ ){
				int ch = t[i] - 'a';
				now = nxt[now][ch];
				if( !now ) return 0;
			}
		}
		else{
			for( int i = x ; i >= 1 ; i -- ){
				int ch = t[i] - 'a';
				now = nxt[now][ch];
				if( !now ) return 0;
			}
		}
		return now;
	}
	inline void get_exist( int typ ){
		if( typ == 0 ){
			int l = 1,r = m + 1;
			while( l <= r ){
				int mid = ( l + r ) >> 1,tmp;
				if( tmp = match( mid , typ ) ) Mpreach = tmp,minp = mid - 1,r = mid - 1;
				else l = mid + 1;
			}
		}
		else{
			int l = 0,r = m;
			while( l <= r ){
				int mid = ( l + r ) >> 1,tmp;
				if( tmp = match( mid , typ ) ) Mnreach = tmp,maxp = mid,l = mid + 1;
				else r = mid - 1;
			}
		}
	}
	inline void get_path( int x , int type ){
		if( type == 0 )
			while( x ) pathup.emplace_back( make_pair( x , maxlen[x] ) ),x = link[x];
		else{
			while( x ) pathdn.emplace_back( make_pair( x , maxlen[x] ) ),x = link[x];
			reverse( pathdn.begin() , pathdn.end() );
		}
	}
}Pos,Neg;

inline long long S( int x ){ return 1ll * x * ( x + 1 ) / 2; }

signed main(){
	Pos.init(),Neg.init();
	scanf("%s%s",s + 1,t + 1); n = strlen( s + 1 ),m = strlen( t + 1 );
	for( int i = 1 , last = 1 ; i <= n ; i ++ ) edp[i] = last = Pos.insert( last , s[i] - 'a' );
	for( int i = n , last = 1 ; i >= 1 ; i -- ) edn[i] = last = Neg.insert( last , s[i] - 'a' );
	Pos.build(),Neg.build(),Pos.dfs( 1 , 0 ),Neg.dfs( 1 , 0 );
	Pos.get_exist( 0 ),Neg.get_exist( 1 );
	if( minp > maxp ){ printf("0\n"); return 0; }
	Pos.get_path( Mpreach , 0 ),Neg.get_path( Mnreach , 1 );
	for( int i = 1 ; i <= n ; i ++ ){
		int w = Pos.Lca( edp[i] , Mpreach );
		Pos.Savs[w].emplace_back( i );
	}
	for( int i = n ; i >= 1 ; i -- ){
		int w = Neg.Lca( edn[i] , Mnreach );
		Neg.Savs[w].emplace_back( i );
	}
	int Ulen = pathup.size(),Dlen = pathdn.size(),unow = 0,dnow = 0;
	for( int i = 1 ; i <= n ; i ++ ) add( trSub , i + m , 1 );
	long long delta = 0;
	for( int p = max( 1 , minp ) ; p <= min( m - 1 , maxp ) ; p ++ ){
		while( m - p <= pathup[unow].second ){
			for( int e : Pos.Savs[pathup[unow].first] ) delta += sum( trSub , e ),add( trAdd , e , 1 );
			unow ++; if( unow == Ulen ) break;
		}
		while( p > pathdn[dnow].second ){
			for( int e : Neg.Savs[pathdn[dnow].first] ) delta -= sum( trAdd , n + m ) - sum( trAdd , e + m - 1 ),add( trSub , e + m , -1 );
			dnow ++; if( dnow == Dlen ) break;
		}
		Ans += delta;
	}
	for( int i = 0 , now = 0 ; i < m ; i ++ ){
		int ch = t[i + 1] - 'a';
		now = Nxt[now][ch];
		border[i + 1] = now;
		Nxt[i][ch] = i + 1;
		for( int j = 0 ; j < 26 ; j ++ )
			if( j != ch ) Nxt[i][j] = Nxt[border[i]][j];
	}
	for( int j = 0 ; j < 26 ; j ++ )
		Nxt[m][j] = Nxt[border[m]][j];
	for( int i = 1 , now = 0 ; i <= n ; i ++ ){
		now = Nxt[now][s[i] - 'a'];
		if( now == m ) Ans += S( i - m ) + S( n - i );
	}
	printf("%lld\n",Ans);
	return 0;
}
```

---

## 作者：Eliauk_FP (赞：2)

cnblogs：[Link](https://www.cnblogs.com/Eliauk-FP/p/18752118)。

如果在分割前 $t$ 就在 $s$ 里面，并且分割时 $t$ 没有被“割开”，也就是 $[l, r]$ 与 $[l ^ \prime, r ^ \prime]$ 不交（这里将 $l^\prime$ 和 $r^\prime$ 对应到了原来的 $s$ 串中），可以直接统计。

接下来我们讨论 $t$ 被割开，也就是 $t$ 由 $[l ^ \prime, l]$ 与 $[r, r ^ \prime]$（这里区间表示 $s$ 的子串）组成时的情况。

首先有一种非常暴力的做法，枚举字符串 $t$ 的分割点，然后在 $s$ 中匹配。

举个例子，就针对题目中第一个样例，我们如果将 $t$ 分割成：

$$
{\color{red}\texttt{a}}{\color{blue}\texttt{ba}}
$$

那么它在 $s$ 中的一组匹配是：

$$
\texttt{a}{\color{red}\texttt{a}}\texttt{bbaa}{\color{blue}\texttt{ba}}
$$

其实这就相当于在 $s$ 中删去了中间的 $\texttt{bbaa}$，剩下的串拼成了 $\texttt{a}{\color{red}\texttt{a}}{\color{blue}\texttt{ba}}$，最后再选取出了 ${\color{red}\texttt{a}}{\color{blue}\texttt{ba}}$。

这样做总复杂度是 $O(n^3)$，实现好的话也许可以 $O(n^2)$，但这两种复杂度都是不能接受的。

观察上述做法，发现它依赖于分割点，这样复杂度一定有一个枚举分割点的 $O(n)$，很难优化。

不妨换个角度入手，观察上面的例子，你会发现红色部分（就是 $\color{red}\texttt{a}$）是 $t$ 的一段前缀，蓝色部分（就是 $\color{blue}\texttt{ba}$）是 $t$ 的一段后缀。再观察它们在 $s$ 中出现的位置，$\color{red}\texttt{a}$ 是 $s$ 的后缀 ${\color{red}\texttt{a}}\texttt{bbaa}{\color{blue}\texttt{ba}}$ 的一段前缀，$\color{blue}\texttt{ba}$ 是 $s$ 的前缀 $\texttt{a}{\color{red}\texttt{a}}\texttt{bbaa}{\color{blue}\texttt{ba}}$ 的一段后缀。

仔细观察上面的例子与它的性质，将它刻画成更一般的形式。这样，你会发现，合法的情况都形如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9hp5ddad.png)

这里有两个性质，等会会用到：

1. $s$ 的前后缀不能离得太近，要不然中间没有可以切开的地方。具体地，它们（端点）的距离要大于 $\lvert t \rvert$。
2. 红色部分的长度与蓝色部分的长度之和等于 $\lvert t \rvert$。

还是上面那个图，现在，我们固定这个前缀和后缀。记 $\text{lcp}$ 表示这个后缀与 $t$ 的最长公共前缀，记 $\text{lcs}$ 表示这个前缀与 $t$ 的最长公共后缀，在图中可以画成：

![](https://cdn.luogu.com.cn/upload/image_hosting/ggmzlkh3.png)

你会发现，红色部分不超过 $\text{lcp}$，蓝色部分不超过 $\text{lcs}$，即：

![](https://cdn.luogu.com.cn/upload/image_hosting/6y9yzfkv.png)

也就是说，一个 $\text{lcp}$ 贡献了长度为 $1\sim \lvert \text{lcp} \rvert$ 的前缀，一个 $\text{lcs}$ 贡献了长度为 $1\sim \lvert \text{lcs} \rvert$ 的一个后缀。这样，我们就可以枚举 $s$ 的前缀和后缀，然后根据性质二直接统计答案。这样做时间复杂度是 $O(n^2)$，不能接受。

考虑优化。根据性质一，我们可以双指针枚举前缀和后缀。观察一个 $\text{lcs}$，根据性质二，它需要的前缀长度为 $\lvert t \rvert - \lvert \text{lcs} \rvert$ 到 $\lvert t \rvert - 1$。这样，我们每次枚举到一个前缀，就在它可贡献范围内（$1\sim \lvert \text{lcp} \rvert$）区间加一，枚举到一个后缀时，就统计它需要的前缀长度（$\lvert t \rvert - \lvert \text{lcs} \rvert$ 到 $\lvert t \rvert - 1$）的区间和，线段树维护即可，时间复杂度 $O(n \log n)$。

求 $\text{lcp}$ 和 $\text{lcs}$ 可以使用扩展 KMP 算法（Z 函数）在 $O(n)$ 的时间复杂度内求出，总时间复杂度 $O(n \log n)$。

当然，你也可以把上面的限制刻画成一个二元偏序关系，然后直接二维数点解决。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long 
#define ls u << 1
#define rs u << 1 | 1
using namespace std;

const int N = 1e6 + 10;
typedef long long ll;
int n, m;
char a[N], b[N];
int f[N], p[N], s[N];
int ans = 0;

struct tree{
    int l, r;
    int val, lzy;
}t[N << 2];

void pushup(int u) {
    t[u].val = t[ls].val + t[rs].val;
}
void maketag(int u, int x) {
    t[u].val += (t[u].r - t[u].l + 1) * x;
    t[u].lzy += x;
}
void pushdown(int u) {
    if (!t[u].lzy) return ;
    maketag(ls, t[u].lzy);
    maketag(rs, t[u].lzy);
    t[u].lzy = 0;
}
void build(int u, int l, int r) {
    t[u].l = l, t[u].r = r;
    if (l == r) return ;
    int M = (l + r) >> 1;
    build(ls, l, M);
    build(rs, M + 1, r);
    pushup(u);
}
void modify(int u, int l, int r, int x) {
    if (l <= t[u].l && t[u].r <= r) maketag(u, x);
    else {
        int M = (t[u].l + t[u].r) >> 1;
        pushdown(u);
        if (l <= M) modify(ls, l, r, x);
        if (r > M) modify(rs, l, r, x);
        pushup(u);
    }
}
int query(int u, int l, int r) {
    if (l <= t[u].l && t[u].r <= r) return t[u].val;
    int M = (t[u].l + t[u].r) >> 1, res = 0;
    pushdown(u);
    if (l <= M) res += query(ls, l, r);
    if (r > M) res += query(rs, l, r);
    pushup(u);
    return res;
}


signed main() {
    cin >> a + 1 >> b + 1;
    n = strlen(a + 1), m = strlen(b + 1);
    b[m + 1] = '*';
    for (int i = m + 2; i <= m + n + 1; i++) b[i] = a[i - m - 1];
    int k1 = 0, k2 = 0;
    f[1] = m;
    for (int i = 2; i <= m + n + 1; i++) {
        if (k2 >= i) f[i] = min(k2 - i + 1, f[i - k1 + 1]);
        while (i + f[i] <= n + m + 1 && b[1 + f[i]] == b[i + f[i]]) f[i]++;
        if (i + f[i] - 1 >= k2) k1 = i, k2 = i + f[i] - 1;
    }
    for (int i = m + 2; i <= m + n + 1; i++) p[i - m - 1] = f[i];
    reverse(a + 1, a + n + 1);
    reverse(b + 1, b + m + 1);
    for (int i = m + 2; i <= m + n + 1; i++) b[i] = a[i - m - 1];
    memset(f, 0, sizeof f);
    k1 = 0, k2 = 0;
    f[1] = m;
    for (int i = 2; i <= m + n + 1; i++) {
        if (k2 >= i) f[i] = min(k2 - i + 1, f[i - k1 + 1]);
        while (i + f[i] <= n + m + 1 && b[1 + f[i]] == b[i + f[i]]) f[i]++;
        if (i + f[i] - 1 >= k2) k1 = i, k2 = i + f[i] - 1;
    }
    for (int i = m + 2; i <= m + n + 1; i++) s[i - m - 1] = f[i];
    reverse(s + 1, s + n + 1);
    build(1, 1, n);
    for (int i = 1; i <= n; i++) {
        int j = m + i;
        if (j > n) break;
        if (p[i]) modify(1, 1, p[i], 1);
        if (s[j]) ans += query(1, max(1ll, m - s[j]), m - 1);
    }
    for (int i = 1; i <= n; i++) {
        if (p[i] < m) continue;
        int l = i - 1, r = i + p[i];
        if (l >= 1) ans += l * (l + 1) / 2;
        if (r <= n) ans += (n - r + 2) * (n - r + 1) / 2;
    }
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：Bitaro (赞：1)

乐了，柚子厨差不多得了。

感觉是很经典的步骤啊！从思考到代码都很经典。

---------

我们来看看操作的意义，实际上就是删一段区间，然后选出一个子串。首先把选择的字符串分成两种：

1. 原串的子串。
2. 由第一步操作后拼接而成的串。

为什么要分两种呢？因为第一种的操作模式和第二种是不同的。在第一种里，删去一段区间是无效操作，保证这个子串不被删除的情况下我们可以任意删除。

所以对于第一种子串，我们用哈希进行判断，然后统计有多少个区间与子串不交即可。

对于第二种，我们通过扫描统计出每个字符作为 $t$ 的第一个字符时产生的最长前缀 $pre$，与作为 $t$ 最后一个字符时产生的最长后缀 $suf$。

合法答案可以抽象为四元组 $(l,r,lenL,lenR)$，表示以 $l$ 作为 $t$ 的第一个字符，其包含在长为 $lenL$ 的 $t$ 的前缀中，以 $r$ 作为 $t$ 的最后一个字符，其包含在长为 $lenR$ 的 $t$ 的后缀中。四元组需要满足限制 $lenL+lenR=len_t,lenL\le pre_l,lenR\le suf_r,r-l+1\ge len_t$。即合并后为 $t$，不能有不合法的匹配，且原长度不得小于 $t$ 的长度。

由于有 $r-l+1\ge len_t$ 限制的存在，$l$ 对答案的贡献应该在枚举到 $l+m-1$ 时加入。所以我们枚举终点，并延迟加入起点。然后问题变为经典拼接问题，采用线段树维护区间加和区间查询即可。

不要忘了特殊讨论第一种字符串！

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define pre(i,a,b) for(int i=a;i<=b;++i)
#define suf(i,a,b) for(int i=a;i>=b;--i)
using namespace std;
#define endl '\n'
const int N=6e5+5;
const ll base=1331,mod=19260817;
ll n,m;
ll pw[N],S[N],T[N];
string s,t;
ll del(ll a,ll b) { return (((a-b)%mod)+mod)%mod; }
ll Hash(ll *h,int l,int r) {
  return (del(h[r],(l==0?0:h[l-1]*pw[r-l+1])%mod))%mod; 
}
#define ls(u) (u<<1)
#define rs(u) ((u<<1)|1)
#define mid ((l+r)>>1)
ll lt[N<<2],tr[N<<2];
void c(int u,int l,int r,ll val) {
  tr[u]+=val*(r-l+1);
  lt[u]+=val;
}
void pd(int u,int l,int r) {
  c(ls(u),l,mid,lt[u]);
  c(rs(u),mid+1,r,lt[u]);
  lt[u]=0;
}
void add(int fl,int fr,ll val,int u=1,int l=1,int r=m) {
  if(fl<=l&&r<=fr) return c(u,l,r,val);
  if(lt[u]) pd(u,l,r);
  if(mid>=fl) add(fl,fr,val,ls(u),l,mid);
  if(mid<fr) add(fl,fr,val,rs(u),mid+1,r);
  tr[u]=tr[ls(u)]+tr[rs(u)];
}
ll query(int fl,int fr,int u=1,int l=1,int r=m) {
  if(fl<=l&&r<=fr) return tr[u];
  if(lt[u]) pd(u,l,r);
  ll ans=0;
  if(mid>=fl) ans+=query(fl,fr,ls(u),l,mid);
  if(mid<fr) ans+=query(fl,fr,rs(u),mid+1,r);
  return ans;
}
#undef mid
vector<int> pl[N];
void solve() {
  ll ans=0;
  cin>>s>>t;
  n=s.size(),m=t.size();
  if(t.size()==1) {
    pre(i,0,s.size()-1) if(s[i]==t[0]){
      if(i>0) ans+=((i-m)*(i-m+1))/2;
      if(i<n-1) ans+=((n-1-i)*(n-1-i-1))/2;
      ans+=i-m+1;
      ans+=n-1-i;
      ans-=m-1;
    }
    cout<<ans<<endl;
    return ;
  }
  S[0]=s[0]-'a'+1;
  pre(i,1,n-1) S[i]=((S[i-1]*base)+s[i]-'a'+1)%mod;
  T[0]=t[0]-'a'+1;
  pre(i,1,m-1) T[i]=((T[i-1]*base)+t[i]-'a'+1)%mod;
  pw[0]=1;
  pre(i,1,n) pw[i]=(pw[i-1]*base)%mod;
  pre(i,0,n-1) {
    int l=0,r=n;
    while(l<r) {
      int mid=(l+r+1)>>1;
      if(Hash(S,i,i+mid-1)!=Hash(T,0,mid-1)) r=mid-1;
      else l=mid;
    }
    int L=l;
    l=0,r=m;
    while(l<r) {
      int mid=(l+r+1)>>1;
      if(i-mid+1<0||Hash(S,i-mid+1,i)!=Hash(T,m-mid,m-1)) r=mid-1;
      else l=mid;
    }
    int R=l;
    if(R==m) {
      if(i>0) ans+=((i-m)*(i-m+1))/2;
      if(i<n-1) ans+=((n-1-i)*(n-1-i-1))/2;
      ans+=i-m+1;
      ans+=n-1-i;
      ans-=m-1;
    }
    if(L) pl[i+m-1].push_back(L==m?L-1:L);
    for(auto v:pl[i]) add(1,v,1);
    ans+=query(max(m-R,1ll),m);
  }
  cout<<ans<<endl;
}
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);

  int T=1;
  while(T--) solve();
  
	return 0;
}
```


---

## 作者：DerrickLo (赞：0)

分两种情况，第一种是第二次选的区间在原来的 $s$ 中没被切断，那么直接枚举起点，然后第一次选的区间就必然是两边的子区间，简单算贡献即可。然后是第二次选的区间在原来的 $s$ 中被切断了，考虑先记 $a_i$ 表示 $s[i,n]$ 与 $t$ 的最长公共前缀，$b_i$ 表示 $s[1,i]$ 与 $t$ 的最长公共后缀，那么如果枚举起点 $i$ 和终点 $j$，那么可以凑成 $t$ 当且仅当 $a_i+b_j\ge m$，然后选的第一个区间的方案数就是满足 $x_i\le a_i,y_i\le b_i,x_i+y_i=m$ 的 $(x_i,y_i)$ 的方案数，可以发现是 $a_i+b_i-m+1$。优化就将起点从后往前扫，然后使用树状数组维护 $b_i\ge m-a_i$ 的个数和 $b_i$ 的和即可。时间复杂度 $\mathcal O(n\log n)$。

```cpp
int n,m,ans,a[400005],b[400005],tr[2][400005];
string s,t;
void add(int op,int x,int k){while(x)tr[op][x]+=k,x-=x&-x;}
int query(int op,int x){int ans=0;while(x<=m)ans+=tr[op][x],x+=x&-x;return ans;}
int c(int x){return x*(x+1)/2;}
int lcp(int i){
	int l=1,r=min(m,n-i+1),ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(hs1.qry1(i,i+mid-1)==hs2.qry1(1,mid)&&hs1.qry2(i,i+mid-1)==hs2.qry2(1,mid))ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int lcs(int i){
	int l=1,r=min(m,i),ans=0;
	while(l<=r){
		int mid=l+r>>1;
		if(hs1.qry1(i-mid+1,i)==hs2.qry1(m-mid+1,m)&&hs1.qry2(i-mid+1,i)==hs2.qry2(m-mid+1,m))ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>s>>t,n=s.size(),m=t.size(),s=" "+s,t=" "+t,hs1.init(n,s),hs2.init(m,t);
	for(int i=1;i<=n-m+1;i++)if(hs1.qry1(i,i+m-1)==hs2.qry1(1,m)&&hs1.qry2(i,i+m-1)==hs2.qry2(1,m))ans+=c(i-1)+c(n-i-m+1);
	for(int i=1;i<=n;i++){
		a[i]=lcp(i),b[i]=lcs(i);
		if(a[i]==m)a[i]--;if(b[i]==m)b[i]--;
	}
	for(int i=n-m;i;i--){
		add(0,b[i+m],1),add(1,b[i+m],b[i+m]);
		ans+=query(0,m-a[i])*(a[i]-m+1)+query(1,m-a[i]);
	}
	cout<<ans;
}
```

---

## 作者：MutU (赞：0)

$300$ ac 祭！

巡厨不请自来～(∠・ω< )⌒★

以下 $n=|s|$，$m=|t|$，数组下标从 $0$ 开始。

要我们求把 $s$ 取一段前缀 $p$ 和一段后缀 $q$，满足 $|p|+|q|<|s|$。求将这两段拼起来后的串中 $t$ 的出现次数之和。

对于完整存在于一段前缀或后缀中的 $t$，我们可以简单求出数量。具体而言，若 $s_{i...i+m-1}=t$，对答案的贡献是 $(1+n-i-m)\times(n-i-m)\div2+i\times(i+1)\div2$。

那么剩下的就是 $t$ 横跨两段的情况。

枚举 $t$ 在 $p$ 中的长度 $len_p$，同时得到 $t$ 在 $q$ 中的长度 $len_q=m-len_p$。

令所有可以作为 $t$ 前 $len_p$ 位左端点的位置的集合为 $A$，可以作为 $t$ 后 $len_q$ 位右端点的位置的集合为 $B$。那么对于 $x\in A$ 和 $y\in B$，如果满足 $y-x\ge|t|$，则贡献一种方案。

此时问题转化为二维偏序，考虑用树状数组维护。

注意到随着 $len_p$ 增大，$A$ 和 $B$ 的变化总数为 $O(n)$ 级别。利用哈希值在每个位置上二分可以求出这个位置往左或往右最多与 $t$ 的前或后若干位相同。然后简单维护修改即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
using namespace std;
const int N = 400100;
const ull base = 29;
string s,t;
int n,m,ans;
int maxa[N],maxb[N];
vector <int> vea[N],veb[N];
ull p[N],hs[N],ht[N];
int gets(int l,int r){
	if(l==0) return hs[r];
	return hs[r]-hs[l-1]*p[r-l+1];
}
int gett(int l,int r){
	if(l==0) return ht[r];
	return ht[r]-ht[l-1]*p[r-l+1];
}
struct BIT{
	int tree[N];
	int lowbit(int x){
		return x & (-x);
	}
	inline void updata(int x,int d){
		int u=x;
		while(u<=n){
			tree[u]+=d;
			u+=lowbit(u);
		}
		return;
	}
	int query(int x){
		int u=x,ans=0;
		while(u>0){
			ans+=tree[u];
			u-=lowbit(u);
		}
		return ans;
	}
};
BIT A,B;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>s>>t;
	n=s.size(),m=t.size();
	p[0]=1,hs[0]=s[0]-'a'+1,ht[0]=t[0]-'a'+1;
	for(int i=1;i<=n+2;i++) p[i]=p[i-1]*base;
	for(int i=1;i<n;i++) hs[i]=hs[i-1]*base+(s[i]-'a'+1);
	for(int i=1;i<m;i++) ht[i]=ht[i-1]*base+(t[i]-'a'+1);
	for(int i=0;i<=n-m;i++){
		if(gets(i,i+m-1)==ht[m-1]) ans+=(1+n-i-m)*(n-i-m)/2+i*(i+1)/2;
	}
	for(int i=0;i<n;i++){
		int l=1,r=max(m,n-i);
		while(l<=r){
			int mid=l+r>>1;
			if(gets(i,i+mid-1)==gett(0,mid-1)) maxa[i]=mid,l=mid+1;
			else r=mid-1;
		}
		l=1,r=max(m,i+1);
		while(l<=r){
			int mid=l+r>>1;
			if(gets(i-mid+1,i)==gett(m-mid,m-1)) maxb[i]=mid,l=mid+1;
			else r=mid-1;
		}
		vea[maxa[i]].push_back(i);
		veb[maxb[i]].push_back(i);
	}
	for(int i=0;i<n;i++) A.updata(i+1,1);
	for(int i=0;i<veb[m].size();i++) veb[m-1].push_back(veb[m][i]);
	int cnt=0;
	for(int i=1;i<m;i++){
		int j=m-i;
		for(int k=0;k<vea[i-1].size();k++){
			int u=vea[i-1][k];
			if(u+m<=n) cnt-=(B.query(n)-B.query(u+m));
			A.updata(u+1,-1);
		}
		for(int k=0;k<veb[j].size();k++){
			int u=veb[j][k];
			cnt+=A.query(u-m+1);
			B.updata(u+1,1);
		}
		ans+=cnt;
	}
	cout<<ans;
	return 0;
}
```

###### 但是魔女的夜宴真的很好玩啊。

---

## 作者：Demeanor_Roy (赞：0)

- [原题链接](https://www.luogu.com.cn/problem/P9576)

------------

不妨分两部分计算答案：$t$ 为 $s$ 某个子串，$t$ 为 $s$ 两个子串的拼接。

前者跑一遍 kmp，每次匹配成功时 $l',r'$ 确定，加上 $l,r$ 位置的方案数即可。

重点来看后者。求出 $f_i,g_i$ 分别表示以 $s_i$ 开始能与 $t$ 匹配的最长前缀，以 $s_i$ 结束能与 $t$ 匹配的最长后缀。这个可以用 exkmp 在 $O(n)$ 内求出。

考虑对于某对 $l,r$，若满足 $r-l+1 > m$，则可以产生 $\min(f_l,g_r,f_l+g_r+1-\vert t \vert,\vert t \vert -1)$ 的贡献。这一点手玩一下不难察觉。

双指针维护 $l$ 以及对其合法的 $r$，贡献可以拆成 $g$ 的区间加和 $f$ 区间查，树状数组维护即可。时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int N=4e5+10;
int n,m,f[N],g[N],z[N],nx[N];
char s[N],t[N];
LL ans;
struct BIT
{
	LL C1[N],C2[N];
	inline void add(int x,int y,LL C[]){for(;x<=min(n,m);x+=x&-x) C[x]+=y;}
	inline LL query(int x,LL C[]){LL res=0;for(;x;x-=x&-x) res+=C[x];return res;}
	inline void add(int l,int r)
	{
		if(l>r) return;
		add(l,1,C1);add(l,l,C2);
		add(r+1,-1,C1);add(r+1,-(r+1),C2);
	}
	inline LL query(int l,int r){return query(l-1,C1)*(r-l+1)+(query(r,C1)-query(l-1,C1))*(r+1)-query(r,C2)+query(l-1,C2);}
}C;
inline LL calc(int x){return 1ll*x*(x+1)/2;}
inline void kmp()
{
	for(int i=2,j=0;i<=m;i++)
	{
		while(j&&t[i]!=t[j+1]) j=nx[j];
		if(t[i]==t[j+1]) ++j;nx[i]=j;
	}
	for(int i=1,j=0;i<=n;i++)
	{
		while(j&&s[i]!=t[j+1]) j=nx[j];
		if(s[i]==t[j+1]) ++j;if(j==m) ans+=calc(i-m)+calc(n-i);
	}
}
inline void exkmp(int n,int m,char a[],char b[],int p[])
{
	z[1]=n;
	for(int i=2,r=0,c=0;i<=n;i++)
	{
		z[i]=(r>=i?min(r-i+1,z[i-c+1]):0);
		while(i+z[i]<=n&&a[z[i]+1]==a[i+z[i]]) ++z[i];
		if(i+z[i]-1>r) r=i+z[i]-1,c=i;
	}
	for(int i=1,r=0,c=0;i<=m;i++)
	{
		p[i]=(r>=i?min(r-i+1,z[i-c+1]):0);
		while(p[i]+1<=n&&i+p[i]<=m&&a[p[i]+1]==b[i+p[i]]) ++p[i];
		if(i+p[i]-1>r) r=i+p[i]-1,c=i;
	}
}
int main()
{
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1);m=strlen(t+1);
	kmp();exkmp(m,n,t,s,f);reverse(t+1,t+m+1);reverse(s+1,s+n+1);exkmp(m,n,t,s,g);reverse(g+1,g+n+1);
	for(int i=n,j=n+1;i>=1;i--)
	{
		while(j-i>m) --j,C.add(1,g[j]);
		f[i]=min(f[i],m-1);ans+=C.query(m-f[i],m-1);
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Supor__Shoep (赞：0)

手玩了一个小时终于做出来了，这不得写一篇题解记录一下？？

下面设 $s$ 的长度为 $n$，$t$ 的长度为 $m$。

考虑分类讨论：

如果 $s$ 中有一个子串 $s'$ 与 $t$ 完全相同（可以用**哈希**进行比较），设 $s'$ 是 $s$ 的第 $l$ 到第 $r$ 个字符组成的字符串，则我们可以删除 $[1,l-1]$ 或者 $[r+1,n]$ 的某一个子区间，计算出它们的总个数就是 $\dfrac{l\times (l-1)}{2}$ 和 $\dfrac{(n-r)\times (n-r+1)}{2}$，两者之和就是这一种情况的方案数。

我们也可以选定一个子串 $s'$，满足 $s'$ 的某一段前缀 $pre$ 和某一段后缀 $suc$ 不相交且两者连接到一起就是 $t$。这样的话我们删掉 $pre$ 和 $suc$ 中间的字符就符合条件了。

例如 `ciaohallo` 要变成 `ciallo` 就可以选取前缀 `cia` 和后缀 `llo`，它们拼在一起就是我们要得到的字符串。值得注意的是，为了避免掉与上一种情况出现重复计算，我们需要满足 $pre$ 和 $suc$ 中间**必须留有至少一个字符**。在上面的例子中，$pre$ 和 $suc$ 之间就留有 `oha` 这一段字符。

但是怎么计算满足上述条件的 $s'$ 的个数呢？我们可以设 $p_i$ 表示 $s$ 的第 $i$ 个到第 $n$ 个字符与 $t$ 的**最大公共前缀**的长度，$q_i$ 表示 $s$ 的第 $1$ 个到第 $i$ 个字符与 $t$ 的**最大公共后缀**的长度。对于 $\forall i\in [1,n],j\in[i+m,n]$，如果有 $p_i+q_j≥m$，则区间 $[i,j]$ 组成的子串 $s'$ 就是满足条件的。当然 $s'$ 变成 $t$ 的删除方法也会有不同的代价。但是我们其实可以推出这个代价就是 $p_i+q_j-m+1$。

为什么是对的？我们来看一下这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/br4cg90e.png)

图中第一行是 $[i,i+p_i-1]$ 的字符串 $A$，第二行是 $[j-q_j+1,j]$ 的字符串 $B$，我们有 $p_i=6,q_j=4,m=7$，则 $p_i+q_j≥m$，这个时候我们将它们进行对齐就得到了这张图。由于 $p_i+q_j≥m$，所以 $A$ 和 $B$ 一定有重合部分。由图可知重合部分的长度为 $p_i+q_j-m=3$。

我们可以考虑 $pre$ 的选择方法，进行得到唯一确定的 $suc$ 的选择方法。我们的 $pre$ 可以选择 `ABA`，`ABAA`，`ABAAB`，`ABAABA`，即重合部分的长度加一 $p_i+q_j-m+1$。不难发现 $pre$ 最长的时候就是取 $A$，最短的时候就是取 $A$ 中不与 $B$ 重合的部分。这个结合图片应该是非常好理解的，大家可以自己思考一下。

综上所述，对于每一个 $i$，我们找到所有的 $j\in[i+m,n]$ 满足 $p_i+q_j≥m$，给答案增加 $p_i+q_j-m+1$。当然我们还需要事先让 $p_i,q_j$ 与 $m-1$ 取一个最小值，因为当 $p_i$ 或者 $q_j$ 等于 $m$ 时，就会和第一种情况算重。

可是暴力找是 $O(n^2)$ 的，我们需要优化。条件 $p_i+q_j≥m\iff q_j≥m-p_i$，所以每一个 $q_j$ 都是在 $[m-p_i,m-1]$ 内的，这样我们就不难想到**权值线段树**，储存区间范围内的 $sum=\sum q_j$ 以及 $q_j$ 的个数 $num$。则对于每一个 $i$，它所带来的代价就是 $sum+num\times (p_i-m+1)$。

然后就可以愉快地打出代码了：

```cpp
#include<bits/stdc++.h>
#define Q(id,x,y,flag) query(1,1,id,x,y,flag)
using namespace std;
const int MAXN=4e5+5;
const unsigned long long base=179;
int n,m;
char a[MAXN],b[MAXN];
unsigned long long mul[MAXN],Hash1[MAXN],Hash2[MAXN];
int p[MAXN],q[MAXN];
struct node
{
	long long sum;
	int num;//sum表示和，num表示个数
}T[MAXN<<2];
void pushup(int x){ T[x].num=T[x<<1].num+T[x<<1|1].num,T[x].sum=T[x<<1].sum+T[x<<1|1].sum; }
void change_tree(int x,int l,int r,int k)
{
	if(l>r) return;
	if(l==r)
	{
		T[x].sum+=l,T[x].num++;
		return;
	}
	int mid=(l+r)/2;
	if(k<=mid)  change_tree(x<<1,l,mid,k);
	else    change_tree(x<<1|1,mid+1,r,k);
	pushup(x);
}
long long query(int x,int l,int r,int L,int R,int flag)
{
	if(L>R) return 0;
	if(L<=l&&r<=R)
	{
		if(!flag)   return T[x].sum;
		return T[x].num;
	}
	int mid=(l+r)/2;
	long long res=0;
	if(L<=mid)  res+=query(x<<1,l,mid,L,R,flag);
	if(R>mid)   res+=query(x<<1|1,mid+1,r,L,R,flag);
	return res;
}
long long solve(int x){ return 1ll*x*(x+1)/2; }
int main()
{
	cin>>(a+1)>>(b+1);
	n=strlen(a+1),m=strlen(b+1);
	mul[0]=1;
	for(int i=1;i<=n;i++)   Hash1[i]=Hash1[i-1]*base+a[i],mul[i]=mul[i-1]*base;//哈希预处理
	for(int i=1;i<=m;i++)   Hash2[i]=Hash2[i-1]*base+b[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=b[1])  continue;
		int l=1,r=min(n-i+1,m);
		while(l<=r)//二分找最长公共前缀
		{
			int mid=(l+r)/2;
			if(Hash1[i+mid-1]-Hash1[i-1]*mul[mid]==Hash2[mid])  p[i]=mid,l=mid+1;
			else    r=mid-1;
		}
		p[i]=min(p[i],m-1);
	}
	for(int i=n;i>=1;i--)
	{
		if(a[i]!=b[m])  continue;
		int l=1,r=min(i,m);
		while(l<=r)//同理找后缀
		{
			int mid=(l+r)/2;
			if(Hash1[i]-Hash1[i-mid]*mul[mid]==Hash2[m]-Hash2[m-mid]*mul[mid])  q[i]=mid,l=mid+1;
			else    r=mid-1;
		}
		q[i]=min(q[i],m-1);
	}
	long long res=0;
	for(int i=1;i<=n-m+1;i++)
	{
		if(Hash1[i+m-1]-Hash1[i-1]*mul[m]==Hash2[m])    res+=solve(i-1)+solve(n-i-m+1);//第一种情况
	}
	if(q[n])	change_tree(1,1,m-1,q[n]);
	for(int i=n-m;i>=1;i--)//注意是逆序！！！！
	{
		if(p[i])	res+=Q(m-1,m-p[i],m-1,0)+Q(m-1,m-p[i],m-1,1)*(p[i]-m+1);
		if(q[i+m-1])	change_tree(1,1,m-1,q[i+m-1]);//每次要记得更新线段树
	}
	cout<<res;
	return 0;
}
```

---

