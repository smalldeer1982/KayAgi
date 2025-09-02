# Largest Subsequence

## 题目描述

Given is a string $ s $ of length $ n $ . In one operation you can select the lexicographically largest $ ^\dagger $ subsequence of string $ s $ and cyclic shift it to the right $ ^\ddagger $ .

Your task is to calculate the minimum number of operations it would take for $ s $ to become sorted, or report that it never reaches a sorted state.

 $ ^\dagger $ A string $ a $ is lexicographically smaller than a string $ b $ if and only if one of the following holds:

- $ a $ is a prefix of $ b $ , but $ a \ne b $ ;
- In the first position where $ a $ and $ b $ differ, the string $ a $ has a letter that appears earlier in the alphabet than the corresponding letter in $ b $ .

 $ ^\ddagger $ By cyclic shifting the string $ t_1t_2\ldots t_m $ to the right, we get the string $ t_mt_1\ldots t_{m-1} $ .

## 说明/提示

In the first test case, the string $ s $ is already sorted, so we need no operations.

In the second test case, doing one operation, we will select cb and cyclic shift it. The string $ s $ is now abc which is sorted.

In the third test case, $ s $ cannot be sorted.

In the fourth test case we will perform the following operations:

- The lexicographically largest subsequence is zca. Then $ s $ becomes abzc.
- The lexicographically largest subsequence is zc. Then $ s $ becomes abcz. The string becomes sorted.

Thus, we need $ 2 $ operations.

## 样例 #1

### 输入

```
6
5
aaabc
3
acb
3
bac
4
zbca
15
czddeneeeemigec
13
cdefmopqsvxzz```

### 输出

```
0
1
-1
2
6
0```

# 题解

## 作者：wmrqwq (赞：7)

**upd：感谢评论区指出"最大字典序一定是这个字符串的后缀" 这个地方显然是错的，现已修改。**

# 题目链接

[CF1905C Largest Subsequence](https://www.luogu.com.cn/problem/CF1905C)

# 题意简述

你可以对一个字符串 $s$ 进行无限次对这个字符串的最大字典序的子序列进行向右的循环移位操作，你需要求出让字符串从小到大排序的最少的操作次数，若无解，则输出 `-1`。

# 解题思路

我们发现，想要让整个字符串从小到大排序，那么最大字典序一定是每次贪心的在选的最右边的字符之后的最大字典序字母的最左边，直到不能再取为止，因此有一个显然的结论，那就是**字符串的最左边的最大字典序的字母的左边的字符串一定要从小到大排序，否则一定无解**，因为最大字典序的字母会一直往右移动，而不会向左移动，因此前面的结论是正确的。然后我们可以先找出一个原字符串的最大字典序序列，容易得出将这个最大字典序序列反过来就是最终得到的序列了，这样的操作次数也是比较好求的，如果此时字符串依然没有串从小到大排序，则输出 `-1`，否则直接输出操作次数即可。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define map unordered_map
#define forl(i,a,b) for(register long long i=a;i<=b;i++)
#define forr(i,a,b) for(register long long i=a;i>=b;i--)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) x&-x
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
long long t,n,ans,maxn,sum,vis[1000010];
string s,ss;
bool pd(string ss)
{
	for(int i=0;i<ss.size()-1;i++)
		if(ss[i]>ss[i+1])
			return 0;return 1;
}
int main()
{
	//IOS;
//	cout<<("aa">"a")<<" "<<("z"<"a");
	cin>>t;
	while(t--)
	{
		ss="";
		long long maxn=0;
		cin>>n>>s;
		for(int i=0;i<=n;i++)
			vis[i]=0;
		if(pd(s))
		{
			cout<<0<<endl;
			continue;
		}
		else
		{
			for(int i=n-1;i>=0;i--)
			{
				if((long long)s[i]>=maxn)
					maxn=(long long)s[i],vis[i]=1,ss+=s[i];
			}
		}
		for(int i=ss.size()-1;i>=0;i--)
			if(ss[i]!=ss[i-1])
			{
				ans=i;
				break;
			}
		//ans=(int)ss.size()-1;
		long long k=0;
		for(int i=0;i<n;i++)
			if(vis[i])
				s[i]=ss[k++];
		if(pd(s))
			cout<<ans<<endl;
		else
			cout<<-1<<endl;
	}
	QwQ;
}
/*
Hack:
1
5
acbab
Hack2:
1
6
abbaaa
*/
```

---

## 作者：huangrenheluogu (赞：5)

首先先发现一个特征，最大的子序列是单调不升的，否则，可以让最大的当第一个。

维护出最长的这个子序列，发现在子序列里最后一个（最小）到第一个（排序后在子序列中的相对位置），所以子序列是可以内部排序的。

发现开始的这个子序列外部是没有节点可以在排序过程中进入子序列的，所有要求其他点已经排序。

判断一下即可，如果可以，子序列需要移动 $len-1$ 次，所以答案就是 $len-1$。

然后发现 WA 了，喜提 $-50$ 分。

原因在于，比如子序列是 `zzy`，那么移动一次，子序列相对顺序就是 `yzz`，已经达到要求，所以，应该是 $len-len_1$，其中 $len_1$ 是最后一个字母相同字母的长度。

[code](https://codeforces.com/contest/1905/submission/237493931)

---

## 作者：w9095 (赞：3)

[CF1905C Largest Subsequence](https://www.luogu.com.cn/problem/CF1905C)

首先考虑如何生成一个字典序最大的子序列。我们先考虑找到字符串中的最大元素，然后在其之后找到第二大的元素，重复这个过程，直到达到序列末尾。

我们可以通过记录每种字母的出现位置，从大往小枚举。每碰到一个字母在当前位置之后，将这个字母加入序列，并将当前位置修改为这个位置。

容易发现，最后的操作一定是对于初始字符串中字典序最大的子序列进行多次移位操作。

因为一次移位之后，最大字符只是被移向该子序列后一位，除去被移走的元素，下一次操作的字符集没有改变，一定是初始字符串中字典序最大的子序列的子序列。而根据生成方式，被移走的元素字典序靠后，故字典序偏小，被移到前面没有坏处，故不需要第二次移动。所以，我们可以看做每次操作最初的序列，已经移到开头的较小元素不再被移动。

因此，我们只考虑操作最初的子序列。根据生成方式，在这个子序列中，较小的元素靠后，所以为了消除所有逆序对，我们需要把最大的元素移动的最后。

注意并不一定是要把第一个元素移动到最后，因为可能会存在多个相同的元素，只要其中一个移动到序列末尾即可，再移动没有意义。

根据上述移动方式，序列中最小的元素一定移动到开头，最大的元素一定移动到末尾。我们直接记录这个序列，然后翻转即可。

操作结束后，直接判定是否存在逆序对即可。顺序遍历序列，记录遍历过的最大值，如果现在的元素小于最大值，证明存在逆序对，无解。

总体时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long t,n,cnt,now,cw[300000],cv[300000];
char s[300000];
vector<long long>w[30];
int main()
{
	scanf("%lld",&t);
	while(t--)
	   {
	   	long long ans=0;
	   	cnt=0,now=0;
	   	scanf("%lld",&n);
	   	scanf("%s",s+1);
	   	for(int i=1;i<=26;i++)w[i].clear();
	   	for(int i=1;i<=n;i++)w[s[i]-'a'+1].push_back(i);
	   	for(int i=26;i>=1;i--)
	   	    {
	   	    long long l=w[i].size();
	   	    for(int j=0;j<l;j++)
	   	        if(w[i][j]>now)now=w[i][j],cw[++cnt]=w[i][j],cv[cnt]=i;
			}
		ans=cnt-1;
		while(cv[cnt-ans]==cv[1]&&ans>=0)ans--;
		ans++;
		for(int i=1;i<=cnt;i++)s[cw[i]]='a'+cv[cnt-i+1]-1;
		now=0;
		for(int i=1;i<=n;i++)
		    if(s[i]-'a'+1>=now)now=s[i]-'a'+1;
		    else
		       {
		       	ans=-1;
		       	break;
			   }
		printf("%lld\n",ans);
	   }
	return 0;
}
```

---

## 作者：梦应归于何处 (赞：1)

### 题目大意

对于一个长度为 $n$ 的序列，每次操作选出一个当前序列中字典序最大的子序列作为你需要进行操作的串。然后把这个串最右边的字符移动到这个串的最左边，这就是一次操作。

现在问你最少要操作多少次才能使得这个串变成一个升序状态，如果不行请输出 $-1$。

### 思路

这道题让我们每次挑出一个字典序最大的子序列，但是我们会发现，只需要刚开始挑一个字典序最大的子序列然后每次对这个串进行操作就可以了。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define db double
#define ll long long
#define ex exit(0)
#define endl "\n"
#define inl inline
#define null NULL
#define pll pair<ll,ll>
#define mkp(a,b) make_pair(a,b)
using namespace std;
vector<ll> a[30];
int main() {
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ll t;
	cin >> t;
	while (t--) {
		ll n;
		scanf("%lld", &n);
		string s, st;
		cin >> s;
		for (int i = 0; i < 26; i++) {
			a[i].clear();
		}
		for (int i = 0; i < n; i++) {
			a[s[i] - 'a'].push_back(i);
		}
		ll last = -1;
		vector<ll> weizhi;
		weizhi.clear();
		for (int i = 25; i >= 0; i--) {
			for (auto j : a[i]) {
				if (j > last) {
					last = j;
					weizhi.push_back(j);
				}
			}
		}
		ll l = 0, r = weizhi.size() - 1;
		while (l < r) {
			swap(s[weizhi[l]], s[weizhi[r]]);
			l++, r--;
		}
		bool flag = 1;
		for (int i = 0; i < n - 1; i++) {
			if (s[i] > s[i + 1]) {
				flag = 0;
				break;
			}
		}
		if (flag) {
			ll cnt = 1;
			for (int i = n - 1; i > 0; i--) {
				if (s[i] == s[i - 1]) {
					cnt++;
				} else {
					break;
				}
			}
			printf("%lld\n", weizhi.size() - cnt);
		} else {
			printf("-1\n");
		}
	}
	return 0;
}
~~~

---

## 作者：Luzhuoyuan (赞：1)

### 题目链接
[[to Codeforces]](https://codeforces.com/contest/1905/problem/C) [[to Luogu]](https://www.luogu.com.cn/problem/CF1905C)

### 题意简述
给定一个长度为 $n$ 的仅由小写英文字母组成的字符串 $s$，每次操作为选出其中字典序最大的子序列，并将其向右旋转。向右旋转的定义是将 $t_1t_2\dots t_m$ 变成 $t_mt_1\dots t_{m-1}$。问使字符串被从小到大排序的最小操作次数。若无解输出 `-1`。

每个测试点 $t$ 组测试用例。

$1\le t\le 10^4,1\le n\le 2\cdot 10^5,\sum n\le 2\cdot 10^5$。

### 做法
首先，考虑字典序最大的子序列长什么样：就是先找到串中最大的字符（如果有一样大的找最先出现的），然后在这个字符之后再找到最大的，重复直到选完 $s_n$ 为止。如果每次暴力修改，复杂度有 $O(n^2)$。

我们思考一次旋转是怎样的。以样例第 5 个串为例，首先我们找到最大子序列（标红）：

$$\text{c\textcolor{red}{z}dde\textcolor{red}{n}eeee\textcolor{red}{migec}}$$

然后转一次，把原来在最大子序列中而现在不在的标橙：

$$\text{c\textcolor{orange}{c}dde\textcolor{red}{z}eeee\textcolor{red}{nmige}}$$

再转：

$$\text{c\textcolor{orange}{c}dde\textcolor{orange}{e}eeee\textcolor{red}{znmig}}$$

直到转完：

$$\text{c\textcolor{orange}{c}dde\textcolor{orange}{e}eeee\textcolor{orange}{gimn}\textcolor{red}{z}}$$

此时进入死循环了，但是我们发现已经排好序了。

同时，我们观察到红色、橙色的位置始终没有变，以及，红、橙的字母相对于开始恰好整体翻转了一下。以及的以及，操作次数刚好是红橙的位置数减一。

为什么要减一呢？因为最后一个 `z` 不用进行操作就已经在最后了，所以严格来说应当是红橙位置数减去字符串中最大字符的出现次数。这个问题能从第 6 组用例体现出来。

于是方法来了：找到最大子序列，记录长度并将它翻转。如果翻转后排好序了，输出子序列长度减去最大字符的出现次数，否则输出 `-1`。于是我们就能愉快地切掉这题了。单组测试用例时间复杂度 $O(n)$。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,b[N],bn,nx[N],mxn;
char s[N];
signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%s",&n,s+1);mxn=bn=0;
        for(int i=n;i>=0;i--){
            nx[i]=mxn;
            if(s[i]>=s[mxn])mxn=i;
        }//nx[i] 表示 i 之后第一个最大的字符位置
        char tmp=s[nx[0]];int num=0;
        for(int i=nx[0];i;i=nx[i])b[++bn]=i,num+=(s[i]==tmp);
        //b 数组表示最大子序列的位置集合，num 是最大字符出现次数
        for(int i=1;i<=(bn>>1);i++)swap(s[b[i]],s[b[bn-i+1]]);//把子序列翻转
        bool c=true;
        for(int i=2;i<=n;i++)
            if(s[i]<s[i-1]){c=false;break;}
        if(!c)printf("-1\n");
        else printf("%d\n",bn-num);
    }
    return 0;
}
```
（逃

---

## 作者：Silvestorm (赞：0)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF1905C)。

对于一个长为 $n$ 的字符串 $s$，一次操作定义为将 $s$ 的字典序最大的子序列 $t$ 拉出来进行一次右 shift 操作，再原位放进去。

shift 操作是指将字符串的末位放到首位，如 abcd 变成 dabc。

求 $s$ 有序的操作次数，或者报告不可能。

多组输入，$\sum n\le 2\times 10^5$。

### 题目类型

字符串。

### 解题思路

按照题目模拟，最后检查字符串是否有序。

先弄明白为什么会出现不可能的情况。$s$ 的字典序最大的子序列 $t$，$t$ 的首位一定是 $s$ 中最大的字母，当然字母可能重复出现，因此我们要找的是最右边的最大字母，在操作中，它不断向右移动，直到它来到了最右边。这时再进行 shift 操作也是无效的，如果 $s$ 还是无序，那就输出 $-1$ 了。

另外，不难看出，一次操作后，$t$ 最右边的字母被扔到左边，就不被之后的操作考虑在内，一次每一次找到的 $t$ 的长度只是不断缩小，相对内容是不变的。我们只需要找到最初的 $t$，对其进行若干次操作，然后放进原字符串即可，这样大大缩减了时间。

最后，要输出的是最少操作次数，一次要做出一点小处理。

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n, m, k, ans, len, l, r, mid, num[200100], id[200010], g;
string s;
void solve()
{
	len = 0;
	ans = 1;
	cin >> n >> s;
	num[0] = s[n - 1];
	id[0] = n - 1;
	for (int i = n - 2; i >= 0; i--) // 取出子序列t，个人感觉倒着取比较方便
	{
		if (s[i] >= num[len])
		{
			num[++len] = s[i];
			id[len] = i; // 记录位置
		}
	}
	int k = len; // 操作次数
	for (int i = len - 1; i >= 0; i--)
	{
		if (num[i] == num[i + 1]) // 小处理
			k--;
		else
			break;
	}
	for (int i = 0; i <= (len) / 2; i++)
	{
		swap(num[i], num[len - i]); // shift操作的优化版本
	}
	for (int i = 0; i <= len; i++)
		s[id[i]] = char(num[i]); // 插入原来的字符串
	for (int i = 1; i < n; i++)	 // 检查字符串是否有序
		if (s[i] < s[i - 1])
		{
			ans = 0;
			break;
		}
	if (ans)
		cout << k << '\n';
	else
		cout << "-1\n";
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}

```


---

## 作者：XYQ_102 (赞：0)

首先我们把字典序最大的子序列找出，方法就是从大到小枚举每个字母，然后能加就加入。

然后我们可以发现我们能做的只有对这个子序列排序，每次循环位移之后一定是把子序列最后的字符（最小的字符）放到最前面，然后相当于把这个字符从子序列里删掉了。

所以我们只需要判断把这个序列排序后能否使得原序列有序即可。

操作次数是子序列除了最大的字符以外的其他字符的数量。
## Code
```cpp
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
using LL = long long;

int main(){

#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    int T;
    cin >> T;
    while(T--){
        int n; string s;
        cin >> n >> s;
        vector<vector<int> > pos(26);
        for(int i = 0; i < n; i++){
            pos[s[i] - 'a'].push_back(i);
        }
        vector<int> p;
        int mx = -1;
        int cnt = 0;
        for(int i = 25; i >= 0; i--){
            auto it = upper_bound(pos[i].begin(), pos[i].end(), mx);
            p.insert(p.end(), it, pos[i].end());
            if (cnt == 0) cnt = p.size();
            if (!p.empty()) mx = p.back();
        }
        auto q = p;
        sort(q.begin(), q.end(), [&](int x, int y){
            return s[x] < s[y];
        });
        string t = s;
        for(int i = 0; i < p.size(); i++){
            t[p[i]] = s[q[i]];
        }
        if (!is_sorted(t.begin(), t.end())){
            cout << -1 << '\n';
        }
        else{
            cout << p.size() - cnt << '\n';
        }
    }

}
```

---

## 作者：Lightwhite (赞：0)

发现这个过程等价于找到这个字符串的最长字典序下降子序列，并将这个子序列的每一个后缀按长度从大到小依次向右循环移位一位。

因为不在这个子序列的子母不可能是 $s$ 中字典序最大的字母，在最后一个字典序最大的字母之后，不在这个子序列的子母不可能是 $s$ 中字典序第二大的字母……以此列推，总之就是不可能有不在这个子序列的字母不可能在任何一个时间段的最长字典序下降子序列中。

而“将这个子序列的每一个后缀按长度从大到小依次向右循环移位一位”等价于对这个子序列翻转。如果翻转后没有排好序就是无解，因为翻转后每次得到的最长字典序下降子序列都是所有字典序最大字母构成的子序列了，操作不会对序列产生改变。

若翻转后排好了序，则答案为 子序列长度减去字典序最大字母个数。因为当最长字典序下降子序列都是所有字典序最大字母构成的子序列时就不需要再循环移位了。

```cpp
// STOOOOOOOOOOOOOOOOOOOOOOOOO hzt CCCCCCCCCCCCCCCCCCCCCCCORZ
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using LL = long long;
using PII = pair<int, int>;

int T, n;
string s, t;
bool f[200010];
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> T;
  while (T--) {
    cin >> n >> s;
    {
      int p = 0;
      for (char c = 'z'; c >= 'a'; c--) {
        for (int i = p; i < n; i++) {
          if (s[i] == c) {
            t += c, p = i + 1;
            f[i] = 1;
          }
        }
      }
      reverse(t.begin(), t.end());
    }
    for (int i = 0, j = 0; i < n && j < t.size(); i++) {
      if (f[i]) {
        s[i] = t[j++];
      }
    }
    if (is_sorted(s.begin(), s.end())) {
      int ans = 0;
      for (char c = 'z'; c >= 'a' && !ans; c--) {
        ans = count(s.begin(), s.end(), c);
      }
      cout << t.size() - ans << '\n';
    } else {
      cout << "-1\n";
    }
    t.clear();
    fill_n(f, n, 0);
  }
  return 0;
} 
```

---

## 作者：快斗游鹿 (赞：0)

## 思路

先考虑如何构造字典序最大的子序列，显然我们可以倒着构造。从末尾字符开始，只要碰到字典序不小于它的字符，就把这个字符加入，并以这个字符为标准再找下去，最终得到的一定是字典序最大的子序列。为什么呢？考虑我们找出的这个子序列中两个相邻字符 $a_i,a_j$，如果有个点 $k$，满足 $i<k<j,a_k>a_j$，则把 $a_k$ 插到 $a_i$ 后面比把 $a_j$ 插进去优，但按照刚刚的构造方式，这种情况一定会被考虑到，故该构造方案是对的。

然后是位移的问题，比较显然的想法是位移子序列长度减一次。但这是错的，比如说找出的子序列是 $zzza$，事实上只要位移一次就能变成 $azzz$，所以最少操作次数是子序列长度减去末尾相同字符长度。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,a[N],b[N];
bool flag[N];
string s;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int main(){
	//freopen("std.in","r",stdin);
	T=read();
	while(T--){
		n=read();cin>>s;
		for(int i=1;i<=n;i++)a[i]=s[i-1]-'a'+1,flag[i]=0;
		int lst=0,cnt=0;
		int flaga=0,flagb=0;
		for(int i=2;i<=n;i++){
			if(a[i]<a[i-1])flaga++;
			if(a[i]>a[i-1])flagb++;
		}
		/*if(!flaga||!flagb){
			puts("0");continue;
		}*/
		for(int i=n;i>=1;i--){
			if(a[i]>=lst)b[++cnt]=a[i],lst=a[i],flag[i]=1;
		}
		int t=0;
		int pos=0;
		for(int i=cnt;i>1;i--){
			if(b[i]!=b[i-1]){
				pos=i-1;break;
			}
		}
		for(int i=1;i<=n;i++){
			if(flag[i])a[i]=b[++t];
		}
		bool g=0;
		for(int i=2;i<=n;i++){
			if(a[i]<a[i-1]){
				g=1;break;
			}
		}
		//for(int i=1;i<=cnt;i++)cout<<b[i]<<" ";
		if(g)puts("-1");
		else printf("%d\n",pos);
	}
	return 0;
}
```


---

