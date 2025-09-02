# [ABC300F] More Holidays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc300/tasks/abc300_f

`o` と `x` からなる長さ $ N $ の文字列 $ S $ と、整数 $ M,K $ が与えられます。  
$ S $ には少なくとも $ 1 $ つの `x` が含まれることが保証されます。

$ S $ を $ M $ 個連結して得られる長さ $ NM $ の文字列を $ T $ とします。 $ T $ に含まれる `x` のうち丁度 $ K $ 個を選んで `o` に変えることを考えます。  
あなたの目標は、変更後の $ T $ に `o` のみからなるできるだけ長い連続部分文字列が含まれるようにすることです。  
`o` のみからなる連続部分文字列の長さとして達成可能な最大値を求めてください。

## 说明/提示

### 制約

- $ N,M,K $ は整数
- $ 1\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ M\ \le\ 10^9 $
- $ x $ を文字列 $ T $ に含まれる `x` の総数としたとき、 $ 1\ \le\ K\ \le\ x $
- $ S $ は `o` と `x` からなる長さ $ N $ の文字列
- $ S $ には少なくとも $ 1 $ つの `x` が含まれる

### Sample Explanation 1

$ S= $ `ooxxooooox` 、 $ T= $ `ooxxooooox` です。 $ 3 $ 文字目と $ 4 $ 文字目の `x` を `o` に変更することにより、変更後の $ T= $ `ooooooooox` となります。 このとき `o` のみからなる長さ $ 9 $ の連続部分文字列が得られ、これが達成可能な最大値です。

### Sample Explanation 2

$ S= $ `oxxox` 、 $ T= $ `oxxoxoxxoxoxxox` です。 $ 5,7,8,10 $ 文字目の `x` を `o` に変更することにより、変更後の $ T= $ `oxxooooooooxxox` となります。 このとき `o` のみからなる長さ $ 8 $ の連続部分文字列が得られ、これが達成可能な最大値です。

## 样例 #1

### 输入

```
10 1 2
ooxxooooox```

### 输出

```
9```

## 样例 #2

### 输入

```
5 3 4
oxxox```

### 输出

```
8```

## 样例 #3

### 输入

```
30 1000000000 9982443530
oxoxooxoxoxooxoxooxxxoxxxooxox```

### 输出

```
19964887064```

# 题解

## 作者：linyihdfj (赞：9)

更好的阅读体验，就点[这里](https://www.cnblogs.com/linyihdfj/p/17488679.html)吧。

## F.More Holidays

### 题目分析：

提供一种线性做法。

仿佛见过一道类似的题，不确定是不是就是这道。

考虑我们最后得到的极长连续的 `o` 串，一定是形如：($S$ 的一段后缀) + (若干个完整的 $S$) + ($S$ 的一段前缀)。

对于若干个完整的 $S$ 我们可以直接求出来它的个数，设 $tot$ 为 $S$ 中 `x` 的个数则中间完整 $S$ 的个数就是 $\lfloor \frac{k}{tot} \rfloor$。

而对于 ($S$ 的一段后缀) + ($S$ 的一段前缀)，我们可以考虑把他们拼在一起，也就是将 $S$ 变成 $SS$ 即二倍字符串长度，这样我们发现 $SS$ 的任意一个子串都可以表示为上述形式，但是任意的上述形式就是 $SS$ 的某一子串嘛？

其实不一定吧，因为我们上述的形式其实并不完整，因为我们可能连一整段都取不到所以可能最后取到的极长字串就是 $S$ 内的一段区间，但是这样会发现虽然不完全，但是我们依旧可以对于 $S$ 的每一个子串找到 $SS$ 中的一个子串使得他们相等，所以就没有什么问题。

解决这个问题，一个想法就是直接枚举左端点，然后右端点就可以二分取得。

但是你会发现二分右端点是一个很傻的行为，因为随着左端点的增加右端点单调不降，所以可以直接使用双指针优化到 $O(n)$。

需要注意的细节就是：有 $m$ 个的限制所以可能我们没办法取得 ($S$ 的一段后缀) + ($S$ 的一段前缀)。

### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e6+5;
char s[N];
int pre[N];
signed main(){
	int n,m,k;scanf("%lld%lld%lld",&n,&m,&k);
	scanf("%s",s+1);
	for(int i=1; i<=n; i++)	s[i+n] = s[i];
	for(int i=1; i<=2 * n; i++)	pre[i] = pre[i-1] + (s[i] == 'x');
	int ans = k / pre[n] * n,tmp = 0;
	m -= k / pre[n];
	k = k % pre[n];
	for(int l=1,r = 1; l<=n; l++){
		while(r + 1 <= 2 * n && pre[r + 1] <= k + pre[l-1]) ++r;
		if(m == 1)	tmp = max(tmp,min(r,n) - l + 1);
		else if(m > 1)	tmp = max(tmp,r - l + 1);
	}
	printf("%lld\n",ans + tmp);
	return 0;
}
```

---

## 作者：Kylin_ZHH (赞：5)

# ABC300 F题解
如果我们可以尝试在 $T$ 中连续 $o$ 的同位位置，那么我们可以得到正确答案。（但是，不可能检查可能的 $NM$ 初始位置。

我们可以有一个最优解，其中最长的连续也就是 $o$ 从 $T$ 的第 $N$ 字符个或先验字符开始。

假设最优解决方案具有从 $N+1$ 个或更晚字符开始的最长连续$o$。然后，对于第 $i$ 个字符的每个修饰，我们决定修改第$i-N$个字符（如果存在）。

那么，现在我们有了一个最优解，其中最连续的 $o$ 比以前开始 $N$ 个字符。

归结一下问题（~~凑字数~~）就是解决掉所有的$i$（就是$i=1,2 \cdots N$）
 
我们希望从 $T$ 的第 $i$ 个字符开始拥有尽可能多的连续得 $o$，找到最大长度。

这个问题是可以用以下方法解决的：

1. 在最远的一端进行二叉搜索。

2. 二叉搜索中的条件分支可以通过检查初始字符和最后一个字符之间的$x$数是否为$K$或更少来确定。

在二分搜索中，我们需要回答以下问题：“有多少 $x$ 是 $T$ 的第一字符？"

这可以用$O(1)$时间的$T$和累积的总和来回答。

看代码吧：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int flag(int x,int n,vector<int> &rew){
  int res=(x/n)*rew[n];
  int rem=x%n;
  res+=rew[rem];
  return res;
}
signed main(){
  int n,m,k;
  string str;
  cin >>n>>m>>k>>str;
  vector<int> rew(n+1,0);
  for(int i=0;i<n;i++){
    rew[i+1]=rew[i];
    if(str[i]=='x'){rew[i+1]++;}
  }
  int res=0;
  for(int i=1;i<=n;i++){
    int fbeg=flag(i-1,n,rew);
    int l=i,r=n*m;
    while(l<=r){
      int te=(l+r)/2;
      if(flag(te,n,rew)-fbeg<=k){l=te+1;}
      else{r=te-1;}
    }
    res=max(r-i+1,res);
  }
  cout<<res<<endl;
  return 0;
}
```


---

## 作者：luogu_gza (赞：4)

考虑一个二分。

发现固定起始点，二分终点是一个不错的想法。

由于直接求一段内 `x` 的个数不怎么现实，所以考虑进行前缀和转化。

于是问题转化为了如何求 $1$ 到 $a$ 的 `x` 的个数。

分为两部分，循环的部分和零散部分。

最后，注意二分边界。

AC 代码（细节在注释中）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define MT int TTT=R;while(TTT--)
#define pc putchar
#define R read()
#define fo(i,a,b) for(register int i=a;i<=b;i++)
#define rep(i,a,b) for(register int i=a;i>=b;i--)
#define m1(a,b) memset(a,b,sizeof a)
int read()
{
    int x=0;
    char ch=getchar();
    bool f=0;
    while(!isdigit(ch)){if(ch=='-') f=1;ch=getchar();}
    while(isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f) x=-x;
    return x;                                       
}
template<typename T> inline void write(T x)
{
    if(x<0)
    {
        pc('-');
        x=-x;
    }
    if(x>9) write(x/10);
    pc(x%10+'0');
}
const int mod=998244353;
int qmi(int a,int b,int p)
{
    int res=1;
    while(b)
    {
        if(b&1) res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}
const int N=3e5+10;
int n,m,k,ans;
string S;//输入的字符串
int s[N];//1~i（小范围）的字符 x 的个数
int calc(int x)//1~x 的字符 x 的个数
{
    return s[n]*(x/n)+s[x%n];
}
signed main(){
    n=R,m=R,k=R;
    cin>>S,S='>'+S;//方便处理下标
    fo(i,1,n) s[i]=s[i-1]+(S[i]=='x');//小范围的预处理
    fo(i,1,n) if(!(S[i]=='x'&&k==0))//这个 if 是为了防止二分出来的答案无法实施
    {
        int l=i,r=n*m;
        while(l<r)
        {
            int mid=l+r+1>>1;//注意二分边界！
            if(calc(mid)-s[i-1]<=k) l=mid;
            else r=mid-1;
        }
        ans=max(ans,l-i+1);
    }
    write(ans);
}
```

---

## 作者：GONGX (赞：2)

### 解题思路
首先我们很容易发现，我们可以枚举所选子串的左端点，然后二分求替换操作后子串的最远右端点位置，再用此时组成的连续子串长度更新答案即可。但由于 $T$ 是无法直接存下的，所以我们可以运用循环节的思想，因为答案最优时连续子串中完整的 $S$ 个数一定，所以可以提前预处理子串中完整的 $S$，然后枚举所选子串左端点在 $S$ 中的位置后二分求右端点在 $S$ 中的位置即可。当然，我们也可以直接通过取模运算处理下标来代替预处理循环节。此时算法的时间复杂度约为 $O(N\log_2N)$，可以通过本题。

但是经过进一步思考我们可以发现，随着子串左端点位置的增大，子串右端点的位置一定是单调不减的。于是我们可以用双指针的方法来代替二分查找，每次同样是枚举连续子串的左端点，然后通过上一个左端点得到的子串右端点位置得到当前子串右端点的位置，再更新答案即可。此时算法的时间复杂度就降至 $O(N)$ 级别了。

注意 $T$ 的最长长度较大，请使用合适的数据类型。并且对于预处理循环节的做法，当预处理完循环节后只剩一段 $S$ 时，请注意特判，本人在此处卡了很久。具体细节可参考本人代码实现。

### 代码展示
#### 二分答案做法
```cpp
#include <iostream>
using namespace std;
#define int long long // 防止爆 int 的偷懒做法
const int N = 3e5 + 5;
int n, m, sum[N];
long long k;
char c[N];
inline int Find1(int l) { // 二分查找 1 
	int r = n - 1, mid; // 此时右端点不可能在 N 处 
	const int ret = sum[l - 1] + k;
	while (l <= r)
		if (sum[mid = l + r >> 1] > ret) // 即 sum[mid] - sum[l - 1] > k 
			r = mid - 1;
		else l = mid + 1;
	return r;
}
inline int Find2(int r, const int ret) { // 二分查找 2 
	int l = 1, mid;
	while (l <= r)
		if (sum[mid = l + r >> 1] > ret) // ret 为此时新的 k
			r = mid - 1;
		else l = mid + 1;
	return r;
}
signed main() { // 二分查找 
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> k >> c + 1;
	for (register int i = 1; i <= n; ++i) 
		sum[i] = sum[i - 1] + (c[i] == 'x');
	if ((long long)sum[n] * m <= k) // 此时 T 中 'x' 的总数不超过 K 
		cout << n * m, exit(0);
	register long long Length = (long long)(k / sum[n]) * n;
	m -= k / sum[n], k %= sum[n]; // 预处理循环节内容 
	register int maxn = 0;
	for (register int i = 1; i <= n; ++i)
		if (sum[n] - sum[i - 1] > k) // 此时直接二分子串的右端点位置
			maxn = max(maxn, Find1(i) - i + 1); 
		else { // 此时二分左端点位置
			if (m > 1) // 此时 i 作为子串左端点，查找子串新的右端点
				maxn = max(maxn, n - i + 1 + Find2(i - 1, k - sum[n] + sum[i - 1]));
			else { // 当预处理循环节后只剩一段 S 时不能再到另一个 S 中查找子串左端点
				maxn = max(maxn, n - i + 1);
				break; // 由于此时答案单调下降，所以提前结束循环即可 
			} 
		}
	cout << Length + maxn; // 输出答案
	return 0;
}
```
#### 双指针做法
```cpp
#include <iostream>
using namespace std;
#define int long long // 注意数据范围
const int N = 3e5 + 2;
int n, m, sum[N << 1]; // 注意 sum 开两倍空间方便处理双指针 
long long k;
char c[N];
signed main() { // 双指针做法
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); // 关闭同步流，加速 cin 和 cout
	cin >> n >> m >> k >> c; // 注意此时字符数组下标从零开始
	for (register int i = 1; i < n * 2; ++i) // 将 sum 数组扩大一倍，方便后面的处理
		sum[i] = sum[i - 1] + (c[(i - 1) % n] == 'x');
	if ((long long)sum[n] * m <= k) // 此时 T 中字符 'x' 的总数不超过 K 
		cout << n * m, exit(0);
	register long long Length = (long long)(k / sum[n]) * n;
	m -= k / sum[n], k %= sum[n]; // 预处理循环节
	register int l = 1, r = 1, maxn = 0; // 注意 sum 数组下标从一开始 
	while (r + 1 < n * 2) { // 双指针
		while (r + 1 < n * 2 && sum[r + 1] - sum[l - 1] <= k)
			++r; // 调整右指针的位置 
		if (m > 1)
			maxn = max(maxn, r - l + 1), ++l;
		else // 注意当处理完循环节后只剩一个 S 时 r 不能超过 N 
			maxn = max(maxn, min(r, n) - l + 1), ++l;
	}
	cout << Length + maxn;
	return 0;
}
```

---

## 作者：elbissoPtImaerD (赞：2)

> Stop learning useless algorithm, learn how to use binary search.

考虑：枚举答案的左端点，考虑右端点最远的位置。

怎么 check？

$[l,r]$ 能达成当且仅当 $\sum\limits_ {j=l}^r [T_j = \texttt x] \le k$。

那个求和式怎么算？

$T$ 有特性：由 $S$ 重复 $m$ 次。

可以拆成若干段整段和一个散段来求。

做完啦！


```cpp
il void Init()
{
	rd(n,m,k,s),s="!"+s;
	for(int i=1;i<=n;++i) f[i]=f[i-1]+(s[i]=='x');
	return;
}
il int F(int x){return --x,x/n*f[n]+f[x%n+1];}
il int Solve()
{
	int ans=0;
	for(int l=1,x;l<=n;++l)
	{
		x=0;
		for(int i=50,r;~i;--i)
		{
			r=l+(x|1ll<<i);
			if(r>n*m) continue;
			if(F(r)-F(l-1)<=k) x|=1ll<<i;
		}
		cx(ans,x+1);
	}
	return ans; 
}
```

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/abc300/submissions/42097086)。

---

## 作者：xpz0525 (赞：0)

### [ABC300F] More Holidays 题解
首先容易想到，最终最长 `o` 的区间内原来应该恰好有 $K$ 个 `x`，我们不可能替换区间之外的 `x`。

如果 $N \times M$ 较小，我们可以考虑枚举最终区间的左端点，然后用前缀和 + 二分查找去找出区间内恰好有 $K$ 个 `x` 的最右的端点，左右端点之间的距离即为一个可行的答案。

但是当 $N \times M$ 变大后，我们还能这样做么？

---

容易发现，最终区间左端点的枚举不会受到影响。由于 $T$ 中每个字符串 $S$ 都是相同的，假设一个区间左端点在第二个字符串 $S$ 的 $i$ 下标处，那将左端点挪到第一个字符串 $S$ 的 $i$ 下标处答案一定不会变得恶劣。
所以对于左端点其实只用在第一个字符串的范围内枚举即可。

对于二分查找，时间复杂度为 $O(\log NM)$，是可以承受的。

最大的影响在于前缀和，前缀和会占用 $O(NM)$ 的时间和空间。我们真的需要这么长的前缀和吗？——**并不需要**。我们只需要计算 $S$ 的前缀和 $ps$。之后对于全串的前缀和 $pre_i$ 只需要通过 $\lfloor \frac{i}{n} \rfloor \times S_n + ps_{i\bmod n}$ 即可得到。

其实我们还可以进一步优化二分查找的范围到一个具体的 $S$ 串内，这样二分查找的时间复杂度也能降至 $O(\log N)$。

*AC* 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,k,ans;
char s[300005];
ll ps[300005];
ll pre(ll p){
    ll count = p/n;
    return count*ps[n] + ps[p%n];
}
int main(){
    cin>>n>>m>>k;
    cin>>&s[1];
    for(int i=1;i<=n;i++){
        ps[i]=ps[i-1];
        if(s[i]=='x')ps[i]++;
    }
    for(int i=1;i<=n;i++){
        ll pos=(k-(ps[n]-ps[i-1]) + ps[n]-1)/ps[n]+1; // 计算右端点所在的字符串
        ll l=i, r=m*n, res; // 如果S[1]='o'，有可能会超过第pos个字符串
        while(l<=r){
            ll mid=(l+r)/2;
            ll xcnt=pre(mid)-pre(i-1);
            if(xcnt<k){
                l=mid+1;
            }else if(xcnt>k){
                r=mid-1;
            }else{
                res=mid;
                l=mid+1; // 要找到最右边的值
            }
        }
        ans=max(ans,res-i+1);
    }
    cout<<ans;
}
```

---

## 作者：Genius_Star (赞：0)

### 题意：

给定一个长为 $N$ 的字符串 $S$，其中至少包含 $1$ 个字符 $x$，同时给定整数 $M$ 和 $K$。将字符串 $S$ 重复连接成长度为 $NM$ 的字符串 $T$，并将其中恰好 $K$ 个字符 $x$ 替换成字符 $o$，求得到的字符串 $T$ 中仅包含字符 $o$ 的最长连续子串的长度的最大值。

### 思路：

这道题目可以使用二分答案来解决。

因为我们需要找到尽可能长的由 'o' 组成的连续子串，所以可以尝试对答案进行二分。

假设当前二分的答案为 $len$，那么我们需要判断是否存在一个方案，使得 $T$ 中长度至少为 $len$ 的连续子串全部由“o”组成。

对于判断方案是否存在的问题，可以使用滑动窗口来解决。

我们从左到右扫描字符串 $T$，每次维护一个长度为 $len$ 的滑动窗口。

如果窗口中“x”的数量小于等于 $K$，那么说明我们可以将窗口中的 $K$ 个“x”替换成“o”，使得窗口中的所有字符均为“o”。

此时我们就可以将窗口右端点右移，尝试找到长度更长的由“o”组成的连续子串。

如果窗口中“x”的数量大于 $K$，那么说明我们无法将窗口中的 $K$ 个“x”替换成“o”，使得窗口中的所有字符均为“o”。

此时我们就需要将窗口左端点右移，尝试找到一个新的窗口，使得其中的所有字符均为“o”'。

假设当前滑动窗口的左右端点为 $l$ 和 $r$，那么我们可以使用两个指针 $l$ 和 $r$ 分别表示滑动窗口中第一个“x”和最后一个“x”出现的位置，从而计算窗口中“x”的数量。

我们可以通过一次遍历来找到 $l$ 和 $r$，然后计算它们之间的“x”的数量即可。

综上所述，我们就可以使用二分答案和滑动窗口来解决这道题目。
### 完整代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

#define all(x) (x).begin(), (x).end()
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)

const long long INF = 1LL << 61;
const ll MOD = 998244353;

int main(void) {
    ll n, m, k;
    cin >> n >> m >> k;

    string s;
    cin >> s;

    ll total_x = count_if(all(s), [](ll x){
        return x == 'x';
    });

    vector<ll> bs(n,0), fs(n + 1,0);

    bs[n - 1] = s[n - 1] == 'x';
    for(ll i = n - 2; i >= 0; i--) {
        bs[i] = bs[i + 1] + (s[i] == 'x');
    }

    for(ll i = 0; i < n; i++) {
        fs[i + 1] = fs[i] + (s[i] == 'x'); 
    }

    ll ans = 0;
    rep(i, n){
        // cout << bs[i] << endl;
        if(bs[i] > k) {
            auto itr = upper_bound(all(fs), k + fs[i]);
            auto idx = itr - fs.begin() - 1;
            ans = max(ans, idx - i);
        } else {
            ll tmpk = k - bs[i];
            ll div = tmpk / total_x;
            ll rem = tmpk % total_x;

            auto itr = upper_bound(all(fs), rem);
            auto idx = itr - fs.begin() - 1;
            ans = max(ans, min(n * m - i, n - i + div * n + idx));
        }
    }
    cout << ans << endl;
}
```
祝愿大家 ABC 集体 AK 啦~

---

