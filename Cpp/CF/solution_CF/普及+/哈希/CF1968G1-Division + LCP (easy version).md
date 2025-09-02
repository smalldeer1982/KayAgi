# Division + LCP (easy version)

## 题目描述

This is the easy version of the problem. In this version $ l=r $ .

You are given a string $ s $ . For a fixed $ k $ , consider a division of $ s $ into exactly $ k $ continuous substrings $ w_1,\dots,w_k $ . Let $ f_k $ be the maximal possible $ LCP(w_1,\dots,w_k) $ among all divisions.

 $ LCP(w_1,\dots,w_m) $ is the length of the Longest Common Prefix of the strings $ w_1,\dots,w_m $ .

For example, if $ s=abababcab $ and $ k=4 $ , a possible division is $ \color{red}{ab}\color{blue}{ab}\color{orange}{abc}\color{green}{ab} $ . The $ LCP(\color{red}{ab},\color{blue}{ab},\color{orange}{abc},\color{green}{ab}) $ is $ 2 $ , since $ ab $ is the Longest Common Prefix of those four strings. Note that each substring consists of a continuous segment of characters and each character belongs to exactly one substring.

Your task is to find $ f_l,f_{l+1},\dots,f_r $ . In this version $ l=r $ .

## 说明/提示

In the first sample $ n=k $ , so the only division of $ aba $ is $ \color{red}a\color{blue}b\color{orange}a $ . The answer is zero, because those strings do not have a common prefix.

In the second sample, the only division is $ \color{red}a\color{blue}a\color{orange}a $ . Their longest common prefix is one.

## 样例 #1

### 输入

```
7
3 3 3
aba
3 3 3
aaa
7 2 2
abacaba
9 4 4
abababcab
10 1 1
codeforces
9 3 3
abafababa
5 3 3
zpozp```

### 输出

```
0
1
3
2
10
2
0```

# 题解

## 作者：Pursuewind (赞：7)

简单题赛时都写了 30 分钟，菜。

## 题意简述

给你一个长度为 $n$ 的字符串 $s$ 和两个整数 $l,r$。

定义 $f(k)$ 表示你将字符串 $s$ 分为 $k$ 个连续的子串，它们的最长公共前缀的长度的最大值。

例如，$s=abcdabc$ 时 $f(2)=3$，因为可以这样划分：$(abcd)(abc)$，它们的最长公共前缀为 $abc$，长度为 $3$。

对于所有的 $l \le k \le r$，输出 $f(k)$，简单版本中 $l=r$。

## 做法

考虑二分出最长公共前缀的长度。

想一下，对于一个长度，你如何判断它是否合法呢？

设这个长度为 $len$。

设 $t=s_{1}+s_{2}+\dots+s_{len}$，这里的加号表示连接字符。

我们用 KMP 求出 $s$ 中所有 $t$ 出现的位置，如果出现的次数大于等于 $k$，就合法。

但是这样会有问题，例如：$s=ababa$，$k=3$，会在 $s$ 中找到 $2$ 个 $aba$，但实际上划分时我们只能划分出一个。

所以我们还需要判定一下两个区间是否重叠。

附赛时代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e5 + 5;
int nxt[N], pos[N], lena, lenb;
int n, l, r; 
string a, b;
bool check(int mid){
	lena = n;
	lenb = mid;
	b = " ";
	int tot = 0;
	for (int i = 1; i <= mid; i ++){
		b += a[i];
	} 
	int j = 0;
    for (int i = 2; i <= lenb; i ++){     
		while (j > 0 && b[i] != b[j + 1]){
	   		j = nxt[j];  
	   	}  
       	if (b[j + 1] == b[i]){
       		j ++; 
	   	}   
	   	nxt[i] = j;
    }
    j = 0;
    for (int i = 1; i <= lena; i ++){
        while (j > 0 && b[j + 1] != a[i]){
        	j = nxt[j];
		}
        if (b[j + 1] == a[i]){
        	j ++;
		}
        if (j == lenb){
			pos[++ tot] = i - lenb + 1; //pos 记录了模式串 b 在 a 中出现的第一个位置
			j = nxt[j];
		}
	}
	int res = 1, lst = pos[1];
	for (int i = 2; i <= tot; i ++){
		if (pos[i] >= lst + mid){ //如果两个字串无交
			res ++;
			lst = pos[i];
		} 
//		cout << pos[i] << " ";
	}
	return res >= l;
}
void solve(){
	cin >> n >> l >> r;
	cin >> a;
	a = " " + a;
	int L = 0, R = n;
	while (L < R){
		int mid = L + R + 1 >> 1;
//		cout << "mid = " << mid << ", ";
		if (check(mid)) L = mid;
		else R = mid - 1;
//		cout << "\n";
	}
	cout << L << "\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t --) solve();
    return 0;
}
```

---

## 作者：I_will_AKIOI (赞：2)

### 题目大意

给你一个长度为 $n$ 的字符串 $s$，请将 $s$ 划分为 $k$ 个连续子串，最大化这些子串的最长公共前缀。

由于我们必须将 $s$ 的前缀划分在第一个子串，所以我们可以二分这个前缀的长度，接着在 $s$ 中找有几个不相交的子串。

朴素的方法找子串的复杂度为 $O(n^2)$，肯定是无法接受的。所以我们使用区间哈希。这样可以 $O(n)$ 匹配字符串。

但是，这里哈希一定要随机模数！作者赛时没搞随机模数 FST 了，导致掉了 $25$ 分，血的教训啊。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,mod,h[200005],p[200005];
char s[200005];
vector<int>v;
int Hash(int l, int r){return (h[r]-h[l-1]*p[r-l+1]%mod+mod)%mod;}//区间哈希
bool check(int mid)
{
  int cnt=1,p=0;
  for(int i=mid+1;i+mid-1<=n;i++) if(Hash(i,i+mid-1)==Hash(1,mid)) cnt++,i=i+mid-1;
  //看这个子串是否和前缀匹配，将i往后跳是为了防止子串相交
  return cnt>=x;
}
void solve()
{
  cin>>n>>x>>y>>s+1;
  p[0]=1;
  for(int i=1;i<=n;i++) p[i]=p[i-1]*13331%mod,h[i]=h[i-1]*13331%mod+s[i]-'a';
  //预处理哈希值
  int l=0,r=n,mid,ans=0;
  while(l<r)
  {
    mid=l+r+1>>1;
    if(check(mid)) l=ans=mid;
    else r=mid-1;
  }
  cout<<ans<<"\n";
  return;
}
signed main()
{
  ios::sync_with_stdio(0);
  srand(time(0));
  mod=1000000007+rand();//随机模数
  int t;
  cin>>t;
  while(t--) solve();
  return 0;
}
```

---

## 作者：junee (赞：1)

# CF1968G1题解

## 前置知识

KMP，二分。

## 题目分析

首先，由于 $l=r$ 所以我们只需要考虑分成 $l$ 段的情况。我们可以发现本题的答案具有单调性，上界为 $\frac{n}{l}$，那么我们只需要找到相同的字串个数 $\ge l$ 个且互不相交，我们可以想到用 KMP 来做。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=2e5+10;
char a[N];
int ne[N];
int n,l,r,T;
bool check(int k){
	int ans=1;
	for(int i=k+1,j=0;i<=n;i++){
		while(j&&a[i]!=a[j+1])j=ne[j];
		if(a[i]==a[j+1])j++;
		if(j==k){
			ans++,j=0;
			if(ans>=l)return 1;
		}
	}
	return 0;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>l>>r;
		for(int i=1;i<=n;i++)cin>>a[i];
		if(l==1){
			cout<<n<<'\n';
			continue;
		}
		for(int i=2,j=0;i<=n;i++){
			while(j&&a[j+1]!=a[i])j=ne[j];
			if(a[j+1]==a[i])j++;
			ne[i]=j;
		}
		int L=0,R=n/l;
		while(L<R){
			int mid=(L+R+1)>>1;
			if(check(mid))L=mid;
			else R=mid-1;
		}
		cout<<L<<"\n";
	}
	return 0;
}
```

---

## 作者：DrAlfred (赞：1)

摘要：二分，字符串哈希，记忆化

[Easy version：https://www.luogu.com.cn/problem/CF1968G1](https://www.luogu.com.cn/problem/CF1968G1)

[Hard version：https://www.luogu.com.cn/problem/CF1968G2](https://www.luogu.com.cn/problem/CF1968G2)

## 题意

给定一个字符串 $s$，对于一个正整数 $k$，我们考虑将 $s$ 分成 $k$ 个连续的子串 $w_1, \cdots, w_k$。定义 $f_k$ 是在所有分割方案中最大的 $LCP\left(w_1, \cdots, w_k\right)$，即 $w_1, \cdots, w_k$ 的最长公共前缀的长度。

现在，给定一个范围 $[l, r]$，求 $f_l, f_{l + 1}, \cdots, f_r$。

## 分析思路

本题解中 $s$ 的下标从 $1$ 开始。

### I. Easy version

首先我们来考察 `Easy version`，即 $k = l = r$ 的情况。

我们考虑枚举最长公共前缀的长度 $len$。注意到 $len$ 变大时，在 $s$ 中的出现次数是不增的。也就是说，为了使每一段都有长为 $len$ 的前缀，相应分割的段数就会减少。于是我们考虑在 $[0, \frac{n}{k}]$ 上二分 $len$。

那么，如何检验 $len$ 是否合法呢？我们需要贪心地从第一个位置开始匹配与 $s[1:len]$ 相等的不交的子串个数。考虑用字符串哈希进行快速判断两段子串是否相等。最后只要个数大于等于 $k$ 即可。

于是我们用 $O\left(n \log n\right)$ 的算法解决了 `Easy version`。 

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
class HashedString {
private:
    // change M and B if you want
    static const i64 M = (1LL << 61) - 1;
    static const i64 B;
    // pow[i] contains B^i % M
    static vector<i64> pow;
    // p_hash[i] is the hash of the first i characters of the given string
    vector<i64> r_hash, p_hash;
    i128 mul(i64 a, i64 b) { return (i128)a * b; }
    i64 mod_mul(i64 a, i64 b) { return mul(a, b) % M; }

public:
    HashedString(const string &s) : r_hash(s.size() + 1), p_hash(s.size() + 1) {
        while (pow.size() < s.size()) { pow.push_back(mod_mul(pow.back(), B)); }
        p_hash[0] = 0;
        r_hash[0] = 0;
        for (size_t i = 0; i < s.size(); i++) {
            p_hash[i + 1] = (mul(p_hash[i], B) + s[i]) % M; // 1-based
        }
        i64 sz = s.size();
        for (int i = sz - 1, j = 0; i >= 0; i--, j++) {
            r_hash[j + 1] = (mul(r_hash[j], B) + s[i]) % M;
        }
    }
    i64 getHash(int start, int end) { // 0 based
        i64 raw_val = p_hash[end + 1] - mod_mul(p_hash[start], pow[end - start + 1]);
        return (raw_val + M) % M;
    }
    i64 getRHash(int start, int end) { // 0 based
        i64 raw_val = r_hash[end + 1] - mod_mul(r_hash[start], pow[end - start + 1]);
        return (raw_val + M) % M;
    }
};
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
vector<i64> HashedString::pow = {1};
const i64 HashedString::B = uniform_int_distribution<i64>(0, M - 1)(rng);
int t = 1, n, l, r;
inline void solve(void) {
    std::string S;
    cin >> n >> l >> r >> S;
    HashedString H(S);
    auto check = [&](int len, int k) {
        int cnt = 1;
        for (int i = len; i + len - 1 < n; i++) {
            if (H.getHash(0, len - 1) == H.getHash(i, i + len - 1)) {
                ++cnt, i = i + len - 1;
            }
        }
        return cnt >= k;
    };
    int L = 0, R = n / l, mid;
    while (L < R) {
        mid = (L + R + 1) >> 1;
        if (check(mid, l)) {
            L = mid;
        } else {
            R = mid - 1;
        }
    }
    cout << L << '\n';
}
inline void optimizeIO(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
}
int main(int argc, char const *argv[]) {
    optimizeIO(), cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：Starrykiller (赞：1)

先考虑 G1 怎么做。

答案显然存在单调性，套路地考虑二分答案。

如果你之前没想到二分答案，可以先关掉题解思考下如何二分答案。


我们将问题转化为：找到一段最长的前缀（记长度为 $len$），使得它在串中出现次数不小于 $l$。注意，这里要求任意两个“出现”是不交的。


由于 SA，SAM 我都不会，所以不难注意到这很像 KMP 的匹配过程，模板串是 $s_{len+1..n}$，模式串是 $s_{1..len}$。直接做 KMP 即可。

但是需要注意的是，在找到一次出现后，由于我们要求无交，所以需要令 $j\gets 0$。

时间复杂度 $\Theta(n\log n)$。

[Submission for G1](https://codeforces.com/contest/1968/submission/259213763).

[这](https://www.luogu.com.cn/article/zonuzxqx)是 G2 的题解。

---

## 作者：迟暮天复明 (赞：1)

楼上的老哥提到了二分之后 KMP 匹配，我猜一手是学字符串学魔怔了。

首先总得二分答案，由于长度为 $k-1$ 的串可以由长度为 $k$ 的串删除末尾字符得到，所以这个问题显然具有可二分性。

二分完之后只需要统计当前前缀长度能分出多少个字符串了，直接哈希解决。自然溢出哈希被构造数据干了。

[提交记录](https://codeforces.com/contest/1968/submission/259825759)

---

## 作者：Coffee_zzz (赞：0)

注意到问题可以转化为，找到最大的非负整数 $i$，使得 $s$ 中存在至少 $l$ 个不相交的等于 $s[1,i]$ 的子串。

显然，如果 $s$ 中存在至少 $l$ 个不相交的等于 $s[1,i+1]$ 的子串，那么 $s$ 中必然存在至少 $l$ 个不相交的等于 $s[1,i]$ 的子串。答案存在单调性，于是我们可以尝试通过二分找到最大的满足条件的非负整数 $i$。

判断是否存在至少 $l$ 个不相交的等于 $s[1,i]$ 的子串是简单的，只需要从左往右枚举每个长度为 $i$ 的子串，通过字符串 Hash 判断是否和 $s[1,i]$ 相等即可。  
注意这些子串不能相交，所以如果 $s[k,k+i-1]$ 匹配成功了，下一次需要从 $k+i$ 开始枚举。

直接二分 $i$ 即可。时间复杂度 $\mathcal O(n \log n)$。

---

## 作者：jhdrgfj (赞：0)

## 解法

我们发现分出的 $l$ 个字符串中若存在长度为 $k$ 的公共前缀，那么它们一定存在长度为 $k-1$ 的公共前缀。因此可以直接上二分。

考虑如何 `check(k)`。我们发现分出来的第一个子串 $w_1$ 长度为 $k$ 的前缀是唯一确定的，所以最终的公共前缀就是原串 $s$ 长度为 $k$ 的前缀。

所以我们只用判断 $s$ 长度为 $k$ 的前缀是否出现了 $\ge l$ 次，用 KMP 可以做到线性。总体时间复杂度为线性对数。

补充一下 KMP 的细节。具体的，我们将模式串 $t$ 设为 $s_1s_2...s_k$。求 `fail` 数组与 KMP 模板无异。当失配指针 $c$ 等于 $k$ 时就代表成功匹配了一次模式串，此时我们令匹配成功次数 $r + 1\to r$。因为分割出来的字符串不能有公共部分，所以不能重复利用模式串前缀与后缀的相同部分，因此应直接将失配指针 $c$ 清零。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n,v,f[1919810];
bool ck(int k)
{
	int r=0,c=0;
	string t;
	for (int i=0;i<=k;i++){
		t+=s[i];
	}
	for (int i=2;i<=k;i++){
        while (c && t[c+1]!=t[i]){
        	c=f[c];
		}
		if (t[c+1]==t[i]){
			f[i]=++c;
		}
    }
    c=0;
    for (int i=1;i<=n;i++){
       	while (c && t[c+1]!=s[i]){
       		c=f[c];	
		}
		if (t[c+1]==s[i]){
			c++;
		}
		if (c==k){
			r++;
			c=0;
		}
    }
    for (int i=0;i<=k;i++){
    	f[i]=0;
	}
    return r>=v;
}
signed main()
{
    int t;
    cin>>t;
    while (t--){
    	cin>>n>>v>>v>>s;
		int l=1,r=n,ans=0;
		s=' '+s;
		while (l<=r){
			int mid=l+r>>1;
			if (ck(mid)){
				l=mid+1;
				ans=mid;
			}else{
				r=mid-1;
			}
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定长度为 $n$ 的字符串 $s$ 以及 $l,r$。

对于所有 $k\in[l,r]$ 求出将 $s$ 分成 $k$ 段后每段的 LCP 长度最大值。

LCP 是最长公共前缀。

$1\leq n\leq 2\times 10^5,1\leq l\leq r\leq n$。多测。$1\leq \sum n \leq 2\times 10^5$。

在 Easy Version 中，满足 $l=r$。

# 题目思路

也就是 Easy Version 只要求出一个 $k$ 对应的解。

我们考虑到 LCP 长度有单调性，可以二分答案。

当然开头的若干个就是需要判断是否合法的 LCP。

check 考虑贪心枚举每一位，判断将这一位作为开头是否有一个 LCP，如果可以直接跳掉。最后判一下是否有 $\geq mid$ 个位置开头能构成 LCP。

考虑到你不在前一位截出一个 LCP，在后一位开始只会导致少截出 LCP。贪心正确。

# 代码链接

<https://codeforces.com/contest/1968/submission/259503131>

这个代码是 G2 过了交上的，但是问题不大。这里的 calc 函数就是求答案。直接 `cout << calc(l) << endl;` 是可以过 G1 的。

---

## 作者：lfxxx (赞：0)

建出 SAM，然后枚举原串的一个前缀 $s$，我们假若能找出其所有出现位置，然后贪心的选取一个前缀段划分，得到 $k$ 段，那么就可以对 $f_1 \to f_k$ 做贡献。

考虑在 parent 树上 dsu 的方式求出所有出现位置，用一个 set 维护出所有出现位置，每次到一个前缀节点就用 lower_bound 找出所有划分段，由于至多有 $\frac{n}{len}$ 个所以总操作数是 $O(\sum_{i=1}^{n} \frac{n}{i})  =  O(n \log n)$，再算上 set 和 dsu 的复杂度，总复杂度就是 $O(n \log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+114;
struct SAM{
	int len,fa;
	int son[26];
}nd[maxn];
int tot,lst;
int chifan[maxn];
vector<int> E[maxn];
void ins(char c,int pos){
    int u=++tot,v=lst;
	nd[u].len=nd[lst].len+1;
    chifan[u]=pos;
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
}
int rt;
void insert(string s){
    lst=rt;
    for(int i=0;i<s.size();i++) ins(s[i],i+1);
}
set<int> S;
int sz[maxn],son[maxn],L[maxn],R[maxn],node[maxn],dfncnt;
void dfs(int u){
    L[u]=++dfncnt;
    node[dfncnt]=u;
    sz[u]=1;
    for(int v:E[u]) dfs(v),sz[u]+=sz[v],son[u]=(sz[v]>sz[son[u]]?v:son[u]);
    R[u]=dfncnt;
}
int dp[maxn];
void dsu(int u,bool keep){
    for(int v:E[u]){
        if(v!=son[u]) dsu(v,false);
    }
    if(son[u]!=0) dsu(son[u],true);
    for(int v:E[u]){
        if(v!=son[u]){
            for(int i=L[v];i<=R[v];i++)
                if(chifan[node[i]]!=0) S.insert(chifan[node[i]]);
        }
    }
    if(chifan[u]!=0){
        S.insert(chifan[u]);
        int cnt=0,now=1;
        while(S.lower_bound(now)!=S.end()){
            now=(*S.lower_bound(now))+chifan[u];
            cnt++;
        }
        dp[cnt]=max(dp[cnt],chifan[u]);
    }
    if(keep==false){
        for(int i=L[u];i<=R[u];i++)
            if(chifan[node[i]]!=0) S.erase(chifan[node[i]]);
    }
    return ;
}
void work(){
    dfncnt=0;
    S.clear();
    rt=++tot;
    int n,l,r;
    cin>>n>>l>>r;
    string s;
    cin>>s;
    insert(s);
    for(int i=2;i<=tot;i++) E[nd[i].fa].push_back(i);
    dfs(1);
    dsu(1,false);
    for(int i=n;i>=1;i--) dp[i]=max(dp[i],dp[i+1]);
    for(int i=l;i<=r;i++) cout<<dp[i]<<' ';
    cout<<'\n';
    for(int i=1;i<=tot;i++)
        for(int j=0;j<26;j++) nd[i].len=0,nd[i].fa=0,nd[i].son[j]=0,chifan[i]=0,sz[i]=0,son[i]=0,L[i]=0,R[i]=0,node[i]=0,dp[i]=0,E[i].clear();
    tot=lst=rt=0;
    return ;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) work();
    return 0;
}
/*
2
3 1 3
aba
3 2 3
aaa
*/
```

---

