# [ABC324E] Joint Two Strings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc324/tasks/abc324_e

英小文字からなる $ N $ 個の文字列 $ S_1,\ S_2,\ \ldots,\ S_N $ 、および、英小文字からなる文字列 $ T $ が与えられます。

$ 1 $ 以上 $ N $ 以下の $ 2 $ つの整数からなる組 $ (i,\ j) $ は $ N^2 $ 個ありますが、そのうち下記の条件を満たすものの個数を出力してください。

- $ S_i $ と $ S_j $ をこの順に連結して得られる文字列は、$ T $ を（連続とは限らない）部分列として含む。

## 说明/提示

### 制約

- $ N $ は整数
- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ S_i $ および $ T $ は英小文字からなる長さ $ 1 $ 以上 $ 5\ \times\ 10^5 $ 以下の文字列
- $ S_1,\ S_2,\ \ldots,\ S_N $ の長さの総和は $ 5\ \times\ 10^5 $ 以下
 
### Sample Explanation 1

問題文中の条件を満たす組 $ (i,\ j) $ は、下記に示す $ 3 $ 個の組 $ (1,\ 2),\ (1,\ 3),\ (2,\ 3) $ です。 - $ (i,\ j)\ =\ (1,\ 2) $ について、$ S_1 $ と $ S_2 $ をこの順に連結して得られる文字列 `abbabcb` は `bac` を部分列として含みます。 - $ (i,\ j)\ =\ (1,\ 3) $ について、$ S_1 $ と $ S_3 $ をこの順に連結して得られる文字列 `abbaaaca` は `bac` を部分列として含みます。 - $ (i,\ j)\ =\ (2,\ 3) $ について、$ S_2 $ と $ S_3 $ をこの順に連結して得られる文字列 `bcbaaca` は `bac` を部分列として含みます。

## 样例 #1

### 输入

```
3 bac
abba
bcb
aaca```

### 输出

```
3```

## 样例 #2

### 输入

```
5 xx
x
x
x
x
x```

### 输出

```
25```

## 样例 #3

### 输入

```
1 y
x```

### 输出

```
0```

## 样例 #4

### 输入

```
10 ms
mkgn
m
hlms
vmsle
mxsm
nnzdhi
umsavxlb
ffnsybomr
yvmm
naouel```

### 输出

```
68```

# 题解

## 作者：不知名用户 (赞：8)

给定字符串 $S_1,S_2,\cdots,S_n;T$，求有多少个 $(i,j),1\le i,j\le n$ 满足 $T$ 是 $S_i+S_j$ 的子序列（这里 $+$ 表示字符串拼接）。$n\le5\cdot 10^5;\sum\limits_{i=1}^n|S_i|,|T|\le 5\cdot10^5$

显然 $T$ 作为子序列一部分在 $S_i$，一部分在 $S_j$ 中，而这两部分分别为 $T$ 的前后缀。于是就想到求出每个 $S_i$，$T$ 的前缀 / 后缀最长能为多少使得还是 $S_i$ 的子序列，这个可以用类似双指针做。设前缀后缀长度分别为 $L_i,R_i$，最后就变成问 $L_i+R_j\ge|T|$ 的个数，直接预处理 $L$ 的前缀和（更具体地说，前缀和数组第 $i$ 个元素表示 $L_x\ge i$ 的个数）对每个 $R$ 计算即可。[AC code](https://atcoder.jp/contests/abc324/submissions/46550490)。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;

string s[N], t;

int l[N], r[N], w[N];

int main()
{
	int n, i, j;
	long long ans = 0;
	cin>>n>>t;
	for(i=1;i<=n;i++)
	{
		cin>>s[i];
		int p = 0, x = 0;
		for(j=0;j<s[i].size();j++)
			if(p<t.size()&&s[i][j]==t[p])
				p++;
		l[i] = p;
		p = t.size() - 1;
		for(j=s[i].size()-1;~j;j--)
			if(p>=0&&s[i][j]==t[p])
				p--, x++;
		r[i] = x;
		w[l[i]]++;
	}
	int m = t.size();
	for(i=m;~i;i--) w[i] += w[i+1];
	for(i=1;i<=n;i++)
		ans += w[m-r[i]];
	cout<<ans;
	return 0;
}
```

---

## 作者：MornStar (赞：3)

# [ABC324E] Joint Two Strings 题解
## 题目大意
给定 $n$ 个字符串 $S_1,S_2,\cdots,S_n$ 和字符串 $T$。

求有多少组 $S_i(1\le i\le n)$ 和 $S_j(1\le j\le n)$ 满足将 $S_j$ 拼在 $S_i$ 后面组成的新字符串中，$T$ 是其子序列。
## 思路
以下定义：$T$ 关于 $S$ 前缀最长子序列，表示在 $T$ 的所有前缀当中，最长的满足其是 $S$ 的子序列的字符串。

如：```abbc``` 关于 ```aabcc``` 的前缀最长子序列是 ```ab```。

后缀最长子序列同样如此。

有拼接和子序列的问题，首先想到维护前缀最长子序列和后缀最长子序列。

这样的话就可以方便地维护两个字符串拼接后是否会产生有 $T$ 为子序列的字符串。

至于怎么维护呢？

设 $pre_i$ 为 $T$ 关于 $S_i$ 前缀最长子序列在 $T$ 中的右端点的位置。$suf_i$ 为 $T$ 关于 $S_i$ 后缀最长子序列在 $T$ 中的左端点的位置。

如果 $suf_j-pre_i\le1$ 则 $S_i$ 和 $S_j$ 满足条件（请自行思考）。

因为枚举过程中，$pre_i$ 固定，维护所有 $suf_j-pre_i\le1$ 的 $suf_j$ 的个数用差分即可。

至于求前缀最长子序列和后缀最长子序列的方法。

前缀最长子序列的右端点 $l$	初始等于 $0$。

前缀最长子序列可以遍历 $S_i$，如果 $S_i$ 的某一位与 $T_l$ 相同，$l$ 加一。

后缀最长子序列只需要反着遍历一遍。

具体自己在代码中理解。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,pre[500005],sumsuf[500005];
long long ans;
string a,s[500005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>a;
	int len=a.length();
	for(int i=1;i<=n;i++){
		cin>>s[i];
		int l=0,r=len-1;
		for(int j=0;j<(int)s[i].length();j++){
			if(s[i][j]==a[l])	l++;
		}
		pre[i]=l-1;
		for(int j=(int)s[i].length()-1;j>=0;j--){
			if(s[i][j]==a[r])	r--;
		}
		sumsuf[r+1]++;
	}
	for(int i=1;i<=len;i++)	sumsuf[i]+=sumsuf[i-1];
	for(int i=1;i<=n;i++)	ans+=sumsuf[pre[i]+1];
	cout<<ans;
}
```


---

## 作者：fcy20180201 (赞：2)

## 题意
高桥有一个字符串 $T$ 和 $N$ 个字符串 $S_1,S_2,S_3,\cdots S_N$。问有多少个 $(i,j)(1\le i,j \le N)$，满足将 $S_i$ 在 $S_j$ 前与 $S_j$ 串联起来，使得 $T$ 是串联后字符串的一个子序列（可以不连续）。

## 解法
蒟蒻刚学树状数组，就用树状数组写一篇题解吧（其实是不会别的方法 QWQ）。

总体想法是输入 $S_i$ 后，做亿点点处理，然后把 $S_i$ 与之前字符串产生的答案算出来（**但要注意，$S_i$ 与自己也可能对答案有贡献**）。

容易想到，若 $T$ 是连接后字符串的子序列，那么一定是前一个字符串包含了 $T$ 的前一半，后一个字符串包含了 $T$ 的后一半。又因为 $\sum_{i=1}^{N}|S_i|\le5\times10^5$，所以可以用两次双指针求出 $S_i$ 最多**按 $T$ 中顺序**包含 $T$ 的前几位与后几位，然后存到两个数组 `pre` 和 `suf` 中，$pre_i$ 表示到 $S_i$ 为止有多少个字符串正好能包含 $T$ 的前 $i$ 位，$suf_i$ 表示到 $S_i$ 为止有多少个字符串正好能包含 $T$ 的后 $i$ 位。

预处理解决了，那怎么算答案呢？我们设 $frt$ 为 $S_i$ 包含 $T$ 前面的位数，$bck$ 为 $S_i$ 包含 $T$ 后面的位数。如果 $S_i$ 在前，那么后面接的字符串必须包含 $T$ 最后**大于等于 $|T|-frt$** 位，$S_i$ 在后同理。这时我们发现，求答案是找后缀和，增加是一个点，所以就可以用改一下下的树状数组维护 `pre` 和 `suf`。（见代码）

这道题就做完了？没有！还有一些小细节要处理！

1. 如果 $S_i$ 包含了整个 $T$ 那么求答案时就会出现 `ask(0)` 的情况，又因为这是后缀和树状数组，所以会出现死循环，一定要特判！
2. $S_i$ 可能与自己连接，但由于在 `pre` 和 `suf` 中都加了一次，所以 $(i,i)$ 被算了两次，要减一。

## 代码
**请勿 Ctrl+C，Ctrl+V！！！**

```cpp
int n,ss;
ll pre[500005],suf[500005],ans;
char s[500005],t[500005];//s 是题目中的 T，t 是题目中的 S。

void addpre(int x){while(x)pre[x]++,x-=(x&-x);}
ll askpre(int x){return (x<=ss?(askpre(x+(x&-x))+pre[x]):0);}//维护 pre 的后缀树状数组。
void addsuf(int x){while(x)suf[x]++,x-=(x&-x);}
ll asksuf(int x){return (x<=ss?(asksuf(x+(x&-x))+suf[x]):0);}//维护 suf 的后缀树状数组。

int main(){
	scanf("%d%s",&n,s);
	ss=strlen(s);//一定要在循环外面求，不然会超时！！！
	for(int i=1;i<=n;i++){
		scanf("%s",t);
		int frt=0,bck=0,st=strlen(t);
		for(int i=0;t[i] && s[frt];i++)if(t[i]==s[frt])frt++;//双指针
		for(int i=st-1;~i && (ss-bck);i--)if(t[i]==s[ss-bck-1])bck++;//双指针
		addpre(frt),addsuf(bck);//加到 pre 和 suf 里。
		if(frt>=ss || bck>=ss){ans+=(ll)(i*2-1);}//特判能整个包含 T（代码中的 s） 的情况。
		else ans+=askpre(ss-bck)+asksuf(ss-frt)-(frt+bck>=ss);//计算答案，最后记得减一。
	}
	printf("%lld",ans);
	return 0;
}
```

蒟蒻的方法细节太多，望各位大佬指教！！！

---

## 作者：robertuu (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc324_e)

由于拼接字符串很慢，会超时，需要使用其他方法帮助判断。

记 $T$ 的长度为 $m$。预处理出每个字符串包含 $T$ 的前缀和后缀长度，若一个字符串包含 $T$ 的前缀长度为 $x$，则其可以成功与后缀长度大于等于 $m - x$ 的字符串匹配。

因此，可以统计后缀长度为每个值的字符串数量（不需要多想，自己可以和自己匹配），之后进行前缀和即可完成（输出时不需要累加大于等于）。

```cpp
#include<bits/stdc++.h>
using namespace std;
int pre[500001],suf[500001];
long long ssuf[500001];
int main()
{
	int n,m,l;
	string s,t;
	cin >> n >> t;
	l = t.length();
	for(int i = 1;i <= n;i++)
	{
		cin >> s;
		m = s.length();
		for(int j = 0;j < m;j++)
			if(pre[i] < m && t[pre[i]] == s[j]) pre[i]++; // 前缀（字符串处理防止越界！）
		suf[i] = l-1;
		for(int j = m-1;j >= 0;j--)
			if(suf[i] >= 0 && t[suf[i]] == s[j]) suf[i]--; // 后缀（字符串处理防止越界！）
		suf[i]++; pre[i]--; // 注意细节，要左右平移一个！
		ssuf[suf[i]]++; // 累加计数
	}
	for(int i = 1;i <= l;i++) ssuf[i] += ssuf[i-1]; // 前缀和
	long long ans = 0;
	for(int i = 1;i <= n;i++) ans += ssuf[pre[i]+1];
	cout << ans;
	return 0;
}
```


---

## 作者：CrTsIr400 (赞：2)

## ABC324E **Joint Two Strings**

### 题意

给你 $N(N\le 5\times 10^5)$ 个由小写英文字母组成的字符串 $S_1, S_2, \ldots, S_N$，和一个由小写英文字母组成的字符串 $T$。

在 $1$ 和 $N$ 之间有 $N^2$ 对 $(i, j)$ 整数。请输出满足条件的**数对个数**：

- 把 $S_i$ 和 $S_j$ 拼接起来，包含 $T$ 这个（**不一定连续的**）**子序列**。

### 思路

赛时就想到了，但是因为判断子序列的那个部分打炸了，没过。

暴力一个个拼 $S_i+S_j$ 是没有前途的，我们考虑一个 $S$ 串对答案的贡献为多少。

很明显，若是把 $S_i$ 和 $S_j$ 拼起来，可以证明 $S_i$ 中一定出现了 $T$ 的一个前缀，$S_j$ 中一定出现了 $T$ 的一个后缀。

于是我们统计每个 $S$ 串最长出现 $T$ 的前缀和后缀有多长。这里可以 $O(\sum_{i=1}^n |S_i|)$ 实现。

具体而言就是双指针法。枚举当前字符 $a[i]$，如果当前字符和待匹配字符 $b[j]$ 相等，那么就给 $j+1$。在此过程中 $i$ 会不断加一。

这里 $i$ 的指针会不断挪动，$j$ 的指针也在不断挪动，所以不会出现相等字符不断匹配的问题。

于是我们就处理出来了每条串的前缀答案 $c[i]$ 和后缀答案 $b[i]$。

考虑把题目中的条件变成 $c[i]+d[j]\ge |T|$，给 $c,d$ 分别排序，双指针法就搞定了。

代码很简短，不到 1k。

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
#define fo(i,a,b) for(auto i(a),_ed(b);i<=_ed;++i)
#define gch(k) for(;(k);CH=getchar())
using namespace std;using I=int;using LL=long long;using V=void;I FL,CH,InNum;LL in(){InNum=0;FL=1;gch(!isdigit(CH)&&CH!=EOF)FL=(CH=='-')?-1:1;gch(isdigit(CH))InNum=10*InNum+CH-'0';return InNum*FL;}
string s,sr,t;
const I N=5e5+10;
I c[N],fs[N],n,m;LL ans;
I pp(string&a,string&b){I j=0;
	for(I i:a)if(j<m&&i==b[j])++j;
	return j;}
I main(){n=in();gch(!isalpha(CH));
	gch(isalpha(CH))s+=CH,++m;
	sr=s;reverse(sr.begin(),sr.end());
	fo(i,1,n){t="";gch(!isalpha(CH));
		gch(isalpha(CH))t+=CH;
		fs[i]=pp(t,s);
		reverse(t.begin(),t.end());
		++c[pp(t,sr)];}
	for(I i(m);~i;--i)c[i]+=c[i+1];
	fo(i,1,n)ans+=c[m-fs[i]];
	return printf("%lld\n",ans),0;}
```

---

小插曲：比赛的时候炸了这题，慌了。

为什么我枚举 $b[j]$ 判断 $a[i]$ 时候不行呢？因为搞不好匹配到 $j$ 的时候，$i$ 的指针**没有挪动**。实际上需要挪动一位。

提供一组 `hack` 数据：答案应该输出 $0$。若你的程序输出 $4$，那么就大概是上述错误。

```plain
2 aaa
a
a
```



---

## 作者：_lqs_ (赞：1)

简述题意：给定 $n$ 个字符串 $s$ 和一个串 $t$，对于所有 $1 \le i,j \le n$，有多少组 $(i,j)$ 把 $s_{j}$ 拼到 $s_{i}$ 后包含 $t$ 这个子序列。$1 \le n \le 5\times 10^5$。

容易想到的是我们对所有的 $s$ 先对 $t$ 进行前缀匹配，设最远匹配到第 $k$ 位，则我们只需找与多少个 $j$ 满足对 $t$ 进行后缀匹配后最远能匹配到第 $g(1 \le g \le k+1)$ 位。

发现“找后缀匹配的个数”这个玩意非常可以预处理，于是我们先处理所有 $s_{i}$ 的后缀对 $t$ 匹配所能到的最远长度。我们发现假设能匹配到第 $k$ 位的也一定能匹配到 $k+1$ 位，因此我们还需要一个前缀和，记到 $q$ 里。设当前 $s_{i}$ 前缀能匹配到最远为 $x$，则 $i$ 对答案的贡献为 $q_{x+1}$。

复杂度线性。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 500005
#define int long long
int n,m,i,j,ans;
char s[N],t[N];
int L[N],R[N],mp[N],q[N];
signed main(){
	scanf("%lld%s",&n,s+1),m=strlen(s+1);
	for(i=1;i<=n;i++){
		scanf("%s",t+1);
		int len=strlen(t+1);
		int l=m,r=1;
		for(j=len;j>=1;j--) if(t[j]==s[l]) l--;
		for(j=1;j<=len;j++) if(t[j]==s[r]) r++;
		l++,r--;
		R[i]=r,mp[l]++;
	}
	for(i=1;i<=m+1;i++) q[i]=q[i-1]+mp[i];
	for(i=1;i<=n;i++){
		int k=q[R[i]+1];
		ans+=k;
	}
	printf("%lld\n",ans);
	return 0;
} 
```


---

## 作者：qejwdi (赞：0)

我们考虑一个 `(i,j)` 满足要求的条件，可以发现 $S_i$ 匹配的是 T 的一个前缀，$S_j$ 匹配的是 T 的一个后缀，那么你就对于每一个 $S_i$ 都考虑它最多能匹配多少的后缀和前缀，设他们为 $l_i,r_i$，那么 `(i,j)` 满足条件即：

$l_i+r_j \geq |T|$

移项得：

$r_j \geq |T|-l_i$

我们直接对于每一个 $l_i$ 统计这样的 $r_j$ 的个数即可，这个东西直接前缀和查询一下就行了。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
#define rep(i,l,r) for (int i = (l); i <= (r); i++)
#define per(i,r,l) for (int i = (r); i >= (l); i--)
#define debug(x) cout << #x << '=' << x << '\n'
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int, int> PII;
typedef double db;
void tomax(int& a, int b) {a = max(a, b);}
void tomin(int& a, int b) {a = min(a, b);}
const int N = 5e5 + 5;
int n, l[N], r[N];
string s[N], t;
int lent;
int pre[N];
int query(int l, int r) {
    return pre[r] - pre[l-1];
}
int main() {
    cin >> n >> t;
    lent = t.size();
    rep(i,1,n) {
        cin >> s[i];
        int len = s[i].size();
        int x = 0, y = 0;
        while (x < len && y < lent) {
            if (s[i][x] == t[y])
                ++x, ++y;
            else
                ++x;
        }
        l[i] = y;
        x = 0, y = 0;
        while (x < len && lent-y-1 >= 0) {
            if (s[i][len-x-1] == t[lent-y-1])
                ++x, ++y;
            else
                ++x;
        }
        r[i] = y;
        pre[r[i]]++;
    }
    rep(i,1,500000)
        pre[i] += pre[i-1];
    /*
    对于一个i，考虑j的数量：
    l_i+r_j>=lent
    r_j>=lent-l_i
    前缀和
    */
    ll ans = 0, ans_ = 0;
    rep(i,1,n) {
        int low = lent - l[i];
        ans += query(low, 500000);
    }
    cout << ans << '\n';
    return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

# 题目大意
给你 $n$ 个字符串 $s$，和一个字符串 $t$。

问你，有多少组是 $s_j$ 拼在 $s_i$ 后面所组成的新字符串中，$t$ 是其子序列。

## 思路
分析：$5 \times 10^5$ 的数据肯定需要 $O(n)$ 或 $O(n \log n)$ 的时间复杂度过掉，$\log n$ 很容易想到应该是二分，于是我们就往二分的思路去想。

首先先进行预处理：

我们可以遍历 $n$ 个 $s$。我们可以开两个数组：
- $f$ 数组，$f_i$ 记录的是每一个 $s_i$ 的最长前缀 
- $b$ 数组，$b_i$ 记录的是每一个 $s_i$ 的最长后缀 

当什么情况两个字符串拼起来的新字符串，$t$ 可以是它们的子序列呢？

如果前面的字符串的**最长前缀** $+$ 后面的字符串的**最长后缀**的长度**大于等于** $t$ 的长度，那么我们就可以拼出一个子序列。

于是，我们可以枚举前面的字符串，然后二分出最长后缀**大于等于** $n$ **减去**这个字符串的**最长前缀**的个数。那么就是这个字符串后面可以接着的字符串的个数，然后对答案 $ans$ 加上这个数。

因此我们就完成这一题了。

最后的提醒：**十年 OI 一场空，不开 long long 见祖宗**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5+5;
int n;
string t,s[N];
int f[N],b[N]; // 前缀和后缀数组
signed main(){
	cin >> n >> t;
	for(int i = 1 ;i <= n;i++)
		cin >> s[i];
	for(int i = 1;i <= n;i++){
		for(int j = 0 ;j < s[i].size();j++)
			if(s[i][j] == t[f[i]])
				f[i]++;//计算si的最大前缀
		for(int j = s[i].size()-1;j >= 0;j--)
			if(s[i][j] == t[t.size()-1-b[i]])
				b[i]++;//计算si的最大后缀
	}
	int m = t.size();
	sort(f+1,f+1+n);sort(b+1,b+1+n);//排序以便二分
	int ans=0;
	for(int i = 1;i <= n;i++) ans+= n-(lower_bound(b+1,b+1+n,m-f[i])-b)+1;//进行二分的操作，计算以si为前面的字符串，后面有多少种可能
	cout<<ans;
	return 0;
}
```

[AC链接](https://atcoder.jp/contests/abc324/submissions/46606446)

---

## 作者：FL_sleake (赞：0)

## 题意简述

给定 $n$ 个字符串 $s_1,s_2,\dots,s_n$，一个标准串 $T$。问有多少个 $(i,j)$ 满足：

$T$ 是 $s_i+s_j$ 的子串。

## 解题思路

处理出每个 $s_i$ 从后往前最多能匹配 $T$ 多少位，然后处理出每个 $s_i$ 从前往后最多能匹配多少位。

若 $s_i$ 从前往后匹配的位数加上 $s_j$ 从后往前匹配的位数大于等于 $T$ 的长度，就一定是可行的。因为这时有重叠部分存在。对于每个 $i$，可以二分地寻找 $j$。具体细节见代码。

## 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string s[500010],x;
int ans[500010];
int main(){
	cin>>n>>x;
	x=" "+x;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++){
		int num=x.size()-1;
		for(int j=s[i].size()-1;j>=0;j--){
			if(s[i][j]==x[num]) num--;
		}
		ans[i]=x.size()-1-num;//从后往前匹配
	}
	sort(ans+1,ans+n+1);
	int Ans=0;
	for(int i=1;i<=n;i++){
		int num=1;
		for(int j=0;j<s[i].size();j++){
			if(s[i][j]==x[num]) num++;
		}
		num--;
		int id=lower_bound(ans+1,ans+n+1,x.size()-1-num)-ans;
        //二分找答案
		Ans+=(n-id+1); 
	}
	cout<<Ans<<endl;
	return 0;
}
```

---

## 作者：incra (赞：0)

### [题目链接](https://www.luogu.com.cn/problem/AT_abc324_e)
### 题解
显然，一对数 $(i,j)$ 满足条件，当且仅当 $s_i$ 从前往后匹配 $t$ 的字母数加上 $s_j$ 从后往前匹配的字母数之和大于等于 $t$ 的长度。

所以我们预处理出每一个字符串从前往后和从后往前匹配 $t$ 的字母数，设这两个预处理出的字母数为 $ans1,ans2$，则问题转化为从 $ans1,ans2$ 各选一个数，求这两个数的和大于等于 $n$ 的方案数。这个很简单，二分即可，这里就不赘述。
### 代码
```cpp
#include <bits/stdc++.h>
#define x first
#define y second
#define pb push_back
#define desktop "C:\\Users\\incra\\Desktop\\"
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,-1,0,0},dy[] = {0,0,1,-1};
bool LAST = false;
istream& operator >> (istream& in,char* s) {
    if (LAST) return in;
	char ch = cin.get ();
	while ((isspace (ch) || ch == '\n') && ch != EOF) ch = cin.get ();
	int n = 0;
	while (!(isspace (ch) || ch == '\n') && ch != EOF) s[n++] = ch,ch = cin.get ();
	s[n] = '\0';
	if (ch == EOF) LAST = true;
	return in;
}
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		p >>= 1;
	}
	return ans;
}
const int N = 500010;
int n,m;
int q;
string s;
string t;
int main () {
	cin >> q >> s;
	n = s.size ();
	s = ' ' + s;
	vector <int> ans1,ans2;
	while (q--) {
		cin >> t;
		m = t.size ();
		t = ' ' + t;
		int pos = 1,cnt = 0;
		while (pos <= m) {
			if (t[pos] == s[cnt + 1]) cnt++;
			pos++;
		}
		ans1.push_back (cnt);
		pos = m,cnt = n + 1;
		while (pos >= 1) {
			if (t[pos] == s[cnt - 1]) cnt--;
			pos--;
		}
		ans2.push_back (n + 1 - cnt);
	}
	sort (ans1.begin (),ans1.end ()),sort (ans2.begin (),ans2.end ());
	LL ans = 0;
	for (int x : ans1) {
		int l = 0,r = ans2.size () - 1;
		while (l < r) {
			int mid = l + r >> 1;
			if (ans2[mid] + x >= n) r = mid;
			else l = mid + 1;
		}
		if (ans2[l] + x >= n) ans += ans2.size () - l;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：0)

考虑维护每个字符串最多可以是 $T$ 后缀几位，记录一个后缀和，然后在 $O(n)$ 枚举 $s_i$，找当前 $s_i$ 是 $T$ 前缀几位，然后查找最低需要 $T$ 的后缀和即可。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define int long long
#define open(x) freopen(#x".in", "r", stdin);freopen(#x".out", "w", stdout);
#define close fclose(stdin);fclose(stdout);
#define all(x) x.begin(), x.end()
namespace FastIO {
	template <typename T = int>
	inline T read() {
		T s = 0, w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		return s * w;
	}
	template <typename T>
	inline void read(T &s) {
		s = 0;
		int w = 1;
		char c = getchar();
		while (!isdigit(c)) {
			if (c == '-') w = -1;
			c = getchar();
		}
		while (isdigit(c)) s = (s << 1) + (s << 3) + (c ^ 48), c = getchar();
		s = s * w;
	}
	template <typename T, typename... Args> inline void read(T &x, Args &...args) {
		read(x), read(args...);
	}
	template <typename T>
	inline void write(T x, char ch) {
		if (x < 0) x = -x, putchar('-');
		static char stk[25];
		int top = 0;
		do {
			stk[top++] = x % 10 + '0', x /= 10;
		} while (x);
		while (top) putchar(stk[--top]);
		putchar(ch);
		return;
	}
} using namespace FastIO;
string s[501010];
int q[501010];
signed main() {
	int n = read(), ans = 0;
	string t;
	cin >> t;
	for (int i = 1; i <= n; ++i) {
		cin >> s[i];
		int cnt = 0, j = t.size()-1;
		for (int k = s[i].size() - 1; k >= 0 && j >= 0; --k) {
			if (s[i][k] == t[j]) {
				--j;
				++cnt;
			}
		}
		q[cnt]++;
	}
	for (int i = t.size(); ~i; --i) q[i] += q[i+1];
	for (int i = 1; i <= n; ++i) {
		int cnt = 0, j = 0, len = s[i].size(), lt = t.size();
		for (int k = 0; k < len && j != lt; ++k) {
			if (s[i][k] == t[j]) {
				++j;
				++cnt;
			}
		}
		ans += q[lt - cnt];
	}
	write(ans, '\n');
	return 0;
}
```

---

## 作者：_liuyi_ (赞：0)

# 题意
有 $n$ 个字符串  $S$，选其中两个字符串，可以重复，拼接起来，问有几组拼接起来后的子序列有目标串 $T$。
# 思路
因为这里的子序列不是连续的，我们可以考虑对每个字符串枚举与 $T$ 前缀最长子序列和后缀最长子序列，这个东西可以双指针。然后拼接的问题，其实就是前缀加上后缀是否大于等于 $\left|T\right|$，这个东西很明显将后缀值排序后二分找就可以了，时间复杂度 $O(n \log n+\sum \left|S\right|)$。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define fi first
#define se second
#define pb push_back
#define mem(a,x) memset(a,x,sizeof(a))
#define all(x) x.begin(),x.end()
#define lisan(x) {sort(all(x));x.erase(unique(all(x)),x.end());}
#define SZ(x) ((int)((x).size()))
#define debug(x) cout<<#x<<"="<<x<<"\n";
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef vector<int> VI;
typedef vector<vector<int>> VII;
typedef vector<ll> VL;
typedef vector<vector<ll>> VLL;
typedef unsigned long long ull;
typedef double db;
template<typename T> inline void cmax(T &a,const T b){if(a<b) a=b;}
template<typename T> inline void cmin(T &a,const T b){if(a>b) a=b;}
template<typename T> inline T gcd(T a,T b){return b?gcd(b,a%b):a;}
template<typename T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
constexpr int N=1e6+10;
constexpr int mod=1e9+7;
//constexpr int mod=998244353;
int n,pre[N],suf[N];
string s[N],t;
VI pos;
ll ans;
inline void solve(){
 	std::ios::sync_with_stdio(false);
 	std::cin.tie(nullptr);
 	cin >> n >> t;
 	rep(i,1,n) cin>>s[i];
 	rep(i,1,n){
 		for(int l1=0,l2=0;l1<=SZ(s[i])-1&&l2<=SZ(t)-1;){
 			if(s[i][l1]==t[l2]){
 				pre[i]++;
 				l1++;
 				l2++;
 				continue;
 			}
 			l1++;
 		}
 		for(int l1=SZ(s[i])-1,l2=SZ(t)-1;l1>=0&&l2>=0;){
 			if(s[i][l1]==t[l2]){
 				suf[i]++;
 				l1--;
 				l2--;
 				continue;
 			}
 			l1--;
 		}
 	}
 	rep(i,1,n) pos.pb(suf[i]);
 	sort(all(pos));
 	rep(i,1,n){
 		int id=SZ(pos)-(lower_bound(all(pos),SZ(t)-pre[i])-pos.begin());
 		ans=ans+id;
 	}
 	printf("%lld",ans);
}
int main(){
    int T=1;
    //scanf("%d",&T);
    while(T--) solve();
}
```


---

