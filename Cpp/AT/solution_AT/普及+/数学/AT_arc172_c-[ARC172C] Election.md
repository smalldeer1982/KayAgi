# [ARC172C] Election

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc172/tasks/arc172_c

今年の AtCoder 市長選挙には A 候補と B 候補の $ 2 $ 人が立候補し、$ N $ 人の有権者が投票しました。 投票者にはそれぞれ $ 1 $ から $ N $ までの番号が付けられており、投票者 $ i $ $ (1\ \leq\ i\ \leq\ N) $ は $ c_i $ 候補に投票しました。

さて、これから開票作業が行われます。 開票作業では $ 1 $ 票ずつ票が開けられていき、票が開けられるたびに、現時点での開票結果が以下の $ 3 $ つのうちどれであるかが発表されます。

- **結果 A:** 現時点で、A 候補の方が獲得票数が多い。
- **結果 B:** 現時点で、B 候補の方が獲得票数が多い。
- **結果 C:** 現時点で、A 候補と B 候補の獲得票数が同数である。
 
ここで開票の順番にはルールがあり、投票者 $ 1 $ 以外の票は、投票者の番号の小さい順に開票されなければなりません。 (投票者 $ 1 $ の票は好きなタイミングで開票してかまいません)

発表される開票結果の列としてあり得るものが何通りあるかを答えてください。

 開票結果の列とは$ i $ 票目 $ (1\ \leq\ i\ \leq\ N) $ が開けられたタイミングで報告された結果を $ s_i $ (`A`, `B`, `C` のいずれか) とするとき，文字列 $ s_1\ s_2\ \dots\ s_N $ のことを指します。

## 说明/提示

### 制約

- $ N $ は $ 2\ \leq\ N\ \leq\ 1000000 $ を満たす整数
- $ c_1,\ c_2,\ \dots,\ c_N $ は `A` または `B`
 
### Sample Explanation 1

この入力例では、開票が行われる順番として以下の $ 4 $ 通りが考えられます。 - 投票者 $ 1\ \to\ 2\ \to\ 3\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 1\ \to\ 3\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 3\ \to\ 1\ \to\ 4 $ の順に開票が行われる。 - 投票者 $ 2\ \to\ 3\ \to\ 4\ \to\ 1 $ の順に開票が行われる。 開票結果の列は上から順に `AAAC`、`AAAC`、`ACAC`、`ACBC` となるため、開票結果の列としてあり得るものは $ 3 $ 通りです。

### Sample Explanation 2

どのような順序で開票を行っても、開票結果の列は `AAAA` となります。

## 样例 #1

### 输入

```
4
AABB```

### 输出

```
3```

## 样例 #2

### 输入

```
4
AAAA```

### 输出

```
1```

## 样例 #3

### 输入

```
10
BBBAAABBAA```

### 输出

```
5```

## 样例 #4

### 输入

```
172
AABAAAAAABBABAABBBBAABBAAABBABBABABABBAAABAAABAABAABBBBABBBABBABBBBBBBBAAABAAABAAABABBBAABAAAABABBABBABBBBBABAABAABBBABABBAAAABAABABBBABAAAABBBBABBBABBBABAABBBAAAABAAABAAAB```

### 输出

```
24```

# 题解

## 作者：Register_int (赞：8)

首先如果第一个人投给了 $\verb!B!$，那直接把所有位反转。这样就只要处理 $\verb!A!$ 的情况。

我们将投票过程看作一条折线，那么 $\verb!A!$ 是上升的线段，$\verb!B!$ 是下降的线段。我们可以将第一个 $\verb!A!$ 不断交换到最后一个来计算答案。

显然相同的段都是连续的，所以只要判断交换过后是否与原情况相同即可。设当前第一个 $\verb!A!$ 在第 $i$ 位，分讨：

- 若 $s_{i+1}=\verb!A!$，则交换前与交换后的字符序列一样。不统计。
- 否则，有以下三种情况会改变投票序列：

![](https://cdn.luogu.com.cn/upload/image_hosting/q78l9rgw.png)

此时满足 $i$ 处的 $\verb!A!$ 票数减去 $\verb!B!$ 票数在 $[-1,1]$ 间。直接朴素判断即可。时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

int n, a[MAXN], ans; char s[MAXN];

int main() {
	scanf("%d%s", &n, s + 1), ans = 1;
	if (s[1] == 'B') for (int i = 1; i <= n; i++) s[i] = s[i] == 'A' ? 'B' : 'A';
	for (int i = 1; i <= n; i++) a[i] = a[i - 1] + (s[i] & 1 ? 1 : -1);
	for (int i = 2; i <= n; i++) if (s[i] == 'B' && abs(a[i]) <= 1) ans++;
	printf("%d", ans);
}

```

---

## 作者：elbissoPtImaerD (赞：4)

$c_i = \texttt A$ 看做 $1$，$\texttt B$ 视为 $-1$，则答案序列相当于是 $c_i$ 前缀和（记为 $s$）的正负性。

考虑将 $c_0$ 不断往后交换一位。

设现在是 $c_{[1,i)} c_0 c_{[i,n)}$。

若 $c_0 = c_i$，则显然不会影响 $s$。

$c_0 \neq c_i$ 时，我们会改变 $s$ 的差分。

此时只要 $|s_i| \le 1$ 即可影响 $s$ 正负性。

$O(n)$ 扫一遍即可。

而且由于每次改变的位置不同，所以不重不漏，正确性得以保证。

[$\color{green}{\checkmark}$](https://atcoder.jp/contests/arc172/submissions/51366989)

---

## 作者：251Sec (赞：3)

感觉官方做法太费脑子了，给大家整点弱智做法。

维护出没有第一个人的情况下每个时刻 A 比 B 多几票，则第一个人相当于选一个后缀把它们全部加上 $1$（或者 $-1$）然后再把自己拼在这个后缀前面。

考虑直接枚举第一个人的位置，对原题要求的那个数列作哈希然后拿个 unordered_set 什么的统计一下不同哈希值的个数。则我们需要维护不被第一个人影响的情况下每个前缀的哈希值，以及被第一个人影响的情况下每个后缀的哈希值，然后直接在中间加入第一个人再把哈希值拼起来就可以了。这些都是容易做的。总复杂度 $O(N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
int n, s[1000005], w0;
char a[1000005];
ull pw[1000005], f[1000005], g[1000005];
unordered_set<ull> ans;
int W(int x) { return x > 0 ? 0 : x == 0 ? 1 : 2; }
int main() {
	scanf("%d%s", &n, a);
	for (int i = 1; i < n; i++) s[i] = s[i - 1] + (a[i] == 'A' ? 1 : -1);
	pw[0] = 1;
	for (int i = 1; i <= n; i++) pw[i] = pw[i - 1] * 3;
	w0 = a[0] == 'A' ? 1 : -1;
	for (int i = 1; i < n; i++) {
		f[i] = f[i - 1] * 3 + W(s[i]);
	}
	for (int i = n - 1; i; i--) {
		g[i] = g[i + 1] + pw[n - 1 - i] * W(s[i] + w0);
	}
	for (int i = 0; i < n; i++) ans.insert(f[i] * pw[n - i] + W(s[i] + w0) * pw[n - i - 1] + g[i + 1]);
	printf("%d\n", (int)ans.size());
	return 0;
}
```

---

## 作者：未来姚班zyl (赞：2)

~~是这场 ARC 前 3 题中最容易一眼做出的一题~~

## 题目大意

有 $n$ 个人给出选票 `A` 或 `B`，除了第一个人以外，其它的人的选票需按顺序加入结算。即第一个人的选票可以插在任何一个位置处，然后依次加入选票进行结算。

根据已经加入的选票的数量多少，结果分为 `A` 赢、`B` 赢和打平。求可能的结果序列有多少种。

## 题目分析

将选票 `A` 视为 $+1$，选票 `B` 视为 $-1$，则结果相当于前缀和的正负性，先将初始序列的前缀和序列求出来，使用哈希表维护局面。

然后考虑每次将一号选票与下一张选票交换，这个操作只会影响前缀和序列中的一个位置，暴力修改即可，复杂度 $O(n\log n)$，使用 $O(1)$ 插入/查询的哈希表可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define repn(x) rep(x,1,n)
#define ui unsigned ll
inline int read(){int s=0,w=1;char c=getchar();while(c<48||c>57) {if(c=='-') w=-1;c=getchar();}while(c>=48&&c<=57)s=(s<<1)+(s<<3)+c-48,c=getchar();return s*w;}
using namespace std;
const int N =1e6+5;
int n,a[N],b[N],ans,cas[N];
string c;
const ui base=13331;
ui p[N],all;
void modify(int x,int k){
	all-=p[x]*cas[x];
	cas[x]=k;
	all+=p[x]*cas[x];
}
map<ui,bool>P;
void sol(int i){
	if(b[i]>0)modify(i,1);
	else if(b[i]<0)modify(i,2);
	else modify(i,3);
}
void Main(){
	n=read(),cin >>c,c='#'+c;
	repn(i)if(c[i]=='A')a[i]=1;
	else a[i]=-1;
	p[1]=1;
	rep(i,2,n)p[i]=p[i-1]*base;
	repn(i)b[i]=b[i-1]+a[i]; 
	repn(i)sol(i);
	P[all]=1;
	rep(i,1,n-1){
		b[i]=b[i-1]+a[i+1],b[i+1]=b[i]+a[i];
		sol(i),sol(i+1);
		P[all]=1;
		swap(a[i],a[i+1]);
	}
	cout <<(int)P.size();
}
signed main(){
	int T=1;
	while(T--)Main();
	return 0;
}
```


---

## 作者：Neil_Qian (赞：2)

# [ARC172C] Election 题解

## 题目描述

给出长度为 $n$ 的序列 $a$，每个位置表示这个人投票给 $1$ 还是给 $2$，投票状态定义为每个时刻两人得票大于、等于、小于构成的序列。

现在把序列中第一个人的投票插入到每一个位置，问有多少种不同的投票状态。

$n<=10^6$。

## 解决方案

提供一种好想的做法。

考虑插入后对序列的影响。

设将 $1$ 号插入到 $i$ 号和 $i+1$ 号中间。对于 $2\sim i$ 来说，不受影响。对于 $i+1\sim n$ 来说，要受到影响。每一次只有一个下标从受到影响变成不受影响，并且对后面的来说没有影响（这里指 $1\sim i$ 对后面的影响），考虑哈希（看看这是什么比赛）。

记录 $L$ 表示左边不受影响的哈希值，$R$ 表示右边不受 $1$ 影响的话产生的贡献，$change$ 表示右边受到 $1$ 影响产生的变化。每次还要考虑 $1$ 的影响。注意从 $R$ 变到 $L$ 时位置会改变，哈希时要注意一下。每一次变更都是很好维护的，再用数据结构维护即可。时间复杂度由数据结构而定。

## 赛时代码

比较丑，见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;const ll N=1e6+2,base=13331;
ll n,pw[N],s1[N],s2[N],rev[N],L,R,change,T;string str;set<ll> s;
inline ll getrev(ll x,ll y){
	if(x>y)return 1;
	else if(x<y)return 2;
	else return 3;
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),
	cin>>n>>str,str=" "+str,pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*base;
	for(int i=2;i<=n;i++){
		s1[i]=s1[i-1]+(str[i]=='A'),s2[i]=s2[i-1]+(str[i]=='B'),
		rev[i]=getrev(s1[i],s2[i]),R+=pw[i]*rev[i];
		if(str[1]=='A'){
			if(s1[i]<s2[i]&&s1[i]+1==s2[i])change+=pw[i];
			else if(s1[i]==s2[i])change-=2*pw[i];
		}
		else{
			if(s2[i]<s1[i]&&s2[i]+1==s1[i])change+=2*pw[i];
			else if(s1[i]==s2[i])change-=pw[i];
		}
	}
	T=pw[1]*getrev((str[1]=='A'),(str[1]=='B')),s.insert(R+change+T);
	for(int i=2;i<=n;i++){
		if(str[1]=='A'){
			if(s1[i]<s2[i]&&s1[i]+1==s2[i])change-=pw[i];
			else if(s1[i]==s2[i])change+=2*pw[i];
			T=pw[i]*getrev(s1[i]+1,s2[i]);
		}
		else{
			if(s2[i]<s1[i]&&s2[i]+1==s1[i])change-=2*pw[i];
			else if(s1[i]==s2[i])change+=pw[i];
			T=pw[i]*getrev(s1[i],s2[i]+1);
		}
		L+=rev[i]*pw[i-1],R-=rev[i]*pw[i],s.insert(L+R+change+T);
	}
	return cout<<s.size()<<"\n",0;
}
```

感觉评上位黄或者下位绿比较合适。

---

## 作者：Ivan422 (赞：1)

我没有打这次的比赛，结果学校出了这道原题。

题目大意：在 $n-1$ 个结果序列中有多少种不同的情况。

题意转换：首先我们发现可以按照顺序调转相邻 $2$ 个字符，这样就能满足第 $1$ 个人在任意人后面投票了。于是我们就把这题的题面转换为：在一个投票序列中，按顺序交换相邻 $2$ 个字符，求在交换过程中产生的结果序列有多少种不同的情况。

预处理：这时我们可以对字符串求出两个人票的前缀数组，即 第 $i$ 次投票后第一个人有 $a_i$ 票，第二个人有 $b_i$ 票。求出前缀后，接着处理出结果序列 $r$。

调换相邻字符：我们会发现调换相邻的字符时，要是这两个字符是相等的，那就没有变化了。要是两个字符不相等，这时前面的 $1$ 到 $i-1$ 项和后面的 $i+1$ 到 $n$ 项是没有变化的，只有第 $i$ 项原来位置上的字符会变，只修改 $a_i$ 和 $b_i$ 即可。我们会发现当 $s_i$ 为 $A$ 时，调换后的 $a_i$ 减少 $1$，$b_i$ 增加 $1$。反之，当 $s_i$ 为 $B$ 时，调换后的 $b_i$ 减少 $1$，$a_i$ 增加 $1$。这时再随之更新 $r$，我们会发现也只有 $r_i$ 会修改，于是不使用字符串判断，直接用 $pr$ 记录之前的字符，要是有修改更新答案 $ans$ 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=1e6+10,M=1010,P=1e9+7,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,a[N],b[N],ans;
string s,r;
char pr;
signed main(){
    cin>>n>>s;s=" "+s;r=" "+r;
    for(int i=1;i<=n;i++){
        a[i]=a[i-1]+(s[i]=='A');
        b[i]=b[i-1]+(s[i]=='B');
        if(a[i]==b[i])r+="E";
        if(a[i]>b[i])r+="B";
        if(a[i]<b[i])r+="L";
    }
    ans++;
    for(int i=1;i<n;i++){
        if(s[i]!=s[i+1]){
            if(s[i]=='A'){a[i]--;b[i]++;}
            else{b[i]--;a[i]++;}
            pr=r[i];
            if(a[i]==b[i])r[i]='E';
            if(a[i]>b[i])r[i]='B';
            if(a[i]<b[i])r[i]='L';
            if(pr!=r[i])ans++;
        }
        swap(s[i],s[i+1]);
    }
    cout<<ans;
    return 0;
}
```
代码不长，思路有点难想，建议评黄。

---

## 作者：封禁用户 (赞：1)

## 前言：
竟然有如此水的绿题。

## 思路：

这道题目，我们要考虑枚举 $1$ 号应该放哪个位置。

我们可以发现无论把选民 $1$ 放在哪个位置，他都不会影响他前面的临时投票结果，所以我们不妨倒着来模拟一遍选民 $1$ 放在每处的情况。

假设现在 $1$ 号放在位置 $i$ 的话，且 $i$ 及之前的结果都计算完毕。如果 $1$ 号挪到位置 $i+1$，那么 $i$ 前面（不包括 $i$）的结果不受影响，$i+1$ 及以后的结果也不受影响。

所以如果位置 $i$ 的结果变化了，答案就会增加 $1$。而这个很好计算。于是只需记录初始每个位置 $A、B$ 两人的票数即可。

## AC Code：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,cnt1,cnt2;
const long long N=1000010;
long long s1[N],s2[N];
long long res[N],ans=1;
char a[N];
int main()
{
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for(long long i=1;i<=n;i++)
	{
		cin >> a[i];
		if(a[i]=='A')
		{
			cnt1++;
		}
		else
		{
			cnt2++;
		}
		s1[i]=cnt1;
		s2[i]=cnt2;
		if(cnt1>cnt2)
		{
			res[i]=1;
		}
		else if(cnt1<cnt2)
		{
			res[i]=2;
		}
		else
		{
			res[i]=3;
		}
	}
	cnt1=cnt2=0;
	for(long long i=2;i<=n;i++)
	{
		if(a[i]=='A')
		{
			cnt1++;
		}
		else
		{
			cnt2++;
		}
		long long now;
		if(cnt1>cnt2)
		{
			now=1;
		}
		else if(cnt1<cnt2)
		{
			now=2;
		}
		else
		{
			now=3;
		}
		if(now!=res[i-1])
		{
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
``````

---

## 作者：rui_er (赞：1)

只有我觉得这场 $C<B<A$ 吗。

考虑所有的 $n$ 个顺序：

- $1\to 2\to 3\to 4\to\cdots$。
- $2\to 1\to 3\to 4\to\cdots$。
- $2\to 3\to 1\to 4\to\cdots$。
- $2\to 3\to 4\to 1\to\cdots$。
- $\cdots$。

考察任意相邻两项的所有前缀构成的集合，发现第 $i$ 个顺序与第 $i+1$ 个顺序仅有前缀 $[1,i]$ 的集合有区别。这意味着一旦“開票結果の列”有一位发生变化，其永远也不可能变化回去。因此，我们只需考虑相邻的两个顺序的“開票結果の列”是否相同即可。

第 $i$ 个顺序与第 $i+1$ 个顺序的前缀 $[1,i]$ 的集合分别是 $[1,i]$ 和 $[2,i+1]$，前缀和判断即可。

```cpp
const int N = 1e6 + 5;

int n, a[N], b[N];
string s;

int sign(int x) {
    if(x > 0) return +1;
    if(x < 0) return -1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> s;
    rep(i, 1, n) a[i] = s[i - 1] == 'A' ? +1 : -1;
    rep(i, 1, n) b[i] = b[i - 1] + a[i];
    int ans = 1;
    rep(i, 1, n - 1) {
        int cnt1 = b[i], cnt2 = b[i + 1] - b[1];
        if(sign(cnt1) != sign(cnt2)) ++ans;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：zhangjiahe__ (赞：0)

# 题面：

有 $n$ 个人，每人要选举一个人且心中已经确定投谁的票，第 $2$ 到 $n$ 个人的投票顺序固定，而第一个人可在任意时刻投票，每投一张票就输出票数高的人或平票，求有多少种输出方案。

# 思路：

暴力时间复杂度 $\Theta (n^2)$，无法接受。考虑使用前缀和优化，投 $A$ 记作 $1$，投 $B$ 记 $-1$，进行累计就能知道除第一个人外得票情况。

接下来，考虑第 $1$ 个人什么时候投票有影响。若此时投票的人和第 $1$ 人投相同票就不会对结果有影响。还有，如果 $A,B$ 两人得票差距超过 $1$，即使他投票也无法改变结果，在代码中判断即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, sum[1000005], ans;
string s;
int main()
{
	cin >> n;
	cin >> s;
	for(int i = 0; i < n; i++)
	{
		int k = (s[i]=='A')?1:-1; //判断投票
		sum[i] = sum[i-1]+k; //前缀和
	}
	for(int i = 1; i < n; i++)
	{
		if(s[i] != s[0] && abs(sum[i])<=1) ans++; //受影响多出一种方案
	}
	cout << ans+1; //记得加上不受任何影响的1种方案
}
```

---

## 作者：AstaSunch_ (赞：0)

说实话这道题挺水的。
# $\mathbf{0x01}$ 思路
前缀和。
以下记投票给 $\text{A}$ 的人有 $n_1$ 个，投票给 $\text{B}$ 的人有 $n_2$ 个，思考什么时候会影响最终结果的变化？

很明显，当 $-1\leq n_1-n_2\leq 1$ 时，会出现以下三种改变当前序列的情况：

- $n_1-n_2=-1$ 且下一个人投票给 $\text{A}$ 时，字符会由 $B$ 变成 $C$；
- $n_1-n_2=0$ 且下一个人投票给 $\text{A}$ 或 $\text{B}$ 时，字符会分别由 $C$ 变成 $A$ 或 $B$；
- $n_1-n_2=1$ 且下一个人投票给 $\text{B}$ 时，字符会由 $A$ 变成 $C$；

所以我们就可以通过前缀和来统计 $n_1-n_2$ 的值，对于第 $i$ 位，$s_i=A$ 的时候就是 $1$，前缀和数组 $g_i$ 相应地加 $1$；$s_i=B$ 的时候就是 $-1$，前缀和数组 $g_i$ 相应地减 $1$；

进一步分析，如果第一个人还没投票，前缀和为 $g_i$；投票后则变成了 $g_{i-1}+k$，这里的 $k$ 就是第一个人投票的结果（$A$ 是 $1$，$B$ 是 $-1$）。

所以当字符发生改变时，$g_i$ 和 $g_{i-1}+k$ 的正负号一定不同（其中也可以有一个是 $0$），即 $g_i\times (g_{i-1}+k)\leq0$。然而这两个还不能同为 $0$（要不然没有新情况产生），所以还要特判一下。

# $\mathbf{0x02}$ 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,g[1000006],ans=1;
string s;
int main(){
	memset(g,0,sizeof(g));
	cin>>n>>s;
	for(ll i=1;i<n;i++){
		g[i]=g[i-1]+(s[i]=='A'?1:-1);
	}
	int k=(s[0]=='A'?1:-1);
	for(ll i=1;i<n;i++){
		if(((g[i-1]+k)*g[i]<=0)&&((g[i-1]+k)||g[i]))ans++;
	}
	cout<<ans;
}
```

---

## 作者：Night_sea_64 (赞：0)

考虑枚举 $1$ 号放哪个位置。

假设现在 $1$ 号放在位置 $i$，且 $i$ 及之前的结果都计算完毕。如果 $1$ 号挪到位置 $i+1$，那么 $i$ 前面（不包括 $i$）的结果不受影响，$i+1$ 及以后的结果也不受影响。

所以如果位置 $i$ 的结果变化了，答案就会增加 $1$。而这个很好计算。于是只需记录初始每个位置 A、B 两人的票数即可。

```cpp
#include<iostream>
using namespace std;
int n,cnt1,cnt2;
int s1[1000010],s2[1000010];
int res[1000010],ans=1;
char a[1000010];
int main()
{
  cin>>n;
  for(int i=1;i<=n;i++)
  {
    cin>>a[i];
    if(a[i]=='A')cnt1++;
    else cnt2++;
    s1[i]=cnt1,s2[i]=cnt2;
    if(cnt1>cnt2)res[i]=1;
    else if(cnt1<cnt2)res[i]=2;
    else res[i]=3;
  }
  cnt1=cnt2=0;
  for(int i=2;i<=n;i++)
  {
    if(a[i]=='A')cnt1++;
    else cnt2++;
    int now;
    if(cnt1>cnt2)now=1;
    else if(cnt1<cnt2)now=2;
    else now=3;
    if(now!=res[i-1])ans++;
  }
  cout<<ans<<endl;
  return 0;
}
```

---

## 作者：NATO (赞：0)

首次场切了三道题，故予作文以记之。

### 解题思路：

我们将 A 看作是 $+1$，B 看作是 $-1$，设前 $x$ 个结果的前缀和为 $sum_x$，那么当前的三种临时结果对应就是 $sum_x>0,sum_x<0,sum_x=0$ 这三种情况。

考虑到 $2,3,...,n$ 的计票顺序是固定的，那么也就是 $1$ 的票只可以插入到两端和任意两个相邻票之间，一共就是 $n$ 种情况。

我们枚举这 $n$ 种情况，显然你如果每次都暴力重算再验重的话是 $O(n^2)$ 的，不可接受。考虑我们插入位置从 $i+1$ 变成 $i$ 究竟会产生什么样的变化。可以发现，只有 $sum_i$ 可能会发生变化（显然 $x<i$ 时插入位置从 $i+1$ 变成 $i$ 对 $sum_x$ 没有影响，$x>i$ 时 $x$ 前面 A 和 B 的数量也是不变的，故都不会变化），如果 $sum_i$ 没有变化那么就是一个相同的结果，而如果发生了变化那么必然是一个不同的结果（在枚举到 $i$ 之前的 $i'>i$，故 $sum_i$ 始终没有变，那么此时 $sum_i$ 如果变化了就必然与之前不同），答案 $+1$ 即可。

倒着扫一遍即可（正着扫一遍亦可，在此保留笔者的赛时做法），时间复杂度 $O(n)$。

这实际上是一种类似于交换贪心的思路，即在不影响其它元素的情况下我们只考虑交换两个相邻元素对这两个相邻元素的影响，从而转移到我们想要的情况。

#### 赛时代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
string s;
ll sum[1000005];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>s;
	for(ll i=1;i<n;++i)
	sum[i]=sum[i-1]+(s[i]=='A'?1:-1);
	sum[n]=sum[n-1]+(s[1]=='A'?1:-1);
	ll res=1;
	for(ll i=n-1;i>0;--i)
	{
		ll ys=sum[i];
		if((sum[i-1]+(s[0]=='A'?1:-1))*ys<=0&&(ys||(sum[i-1]+(s[0]=='A'?1:-1))))
		++res;
	}
	cout<<res;
}
```


---

## 作者：HHYQ_07 (赞：0)

# [题目链接](https://www.luogu.com.cn/problem/AT_arc172_c)

# [AT链接](https://atcoder.jp/contests/arc172/tasks/arc172_c)

# 前言

此题是本次 arc 最简单的一道了，比曾经的 c 题简单不少。感觉官方题解做得复杂了，~~反正我是没怎么理解~~，我认为我的思路比较清晰，大家也可以看看[官方题解](https://atcoder.jp/contests/arc172/editorial/9349)。

# 思路

可以发现无论把选民 $1$ 放在哪个位置，他都不会影响他前面的临时投票结果，所以我们不妨倒着来模拟一遍选民 $1$ 放在每处的情况。

# 具体操作

记录两个变量 `sum1` 和 `sum2`，分别代表目前为止投 A 和投 B 的票数。记录一个字符数组 $c_i$，代表前 $i$ 人投票的临时结果（要从第二个人开始算，可以整体向前移一位，即 $i$ 为 $1$ 到 $n-1$）。输入时处理出前 $1$ 到 $n-1$ 人的 `sum1` 和 `sum2`（即前 $2$ 到 $n$ 人，具体见我的代码）。倒着推的时候到每一位调整当前的 `sum1` 和 `sum2`，代表第 $i$ 位时，选民 $1$ 插在了第 $i-1$ 和 $i$ 人之间（第 $i$ 和 $i+1$ 人之间）。然后再计算当前到第 $i$ 位临时选票结果，如果和之前的 $c_i$ 不一样，说明有新的序列了，答案加一。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+5;
int n,sum1,sum2,ans;
char now,a[N],c[N],t;
signed main()
{
	cin>>n>>t;
	if(n==1)
	{
		cout<<1;
		return 0;
	}
	for(int i=1;i<n;i++)
	{
		cin>>a[i];
		if(a[i]=='A')sum1++;
		else sum2++;
		if(sum1==sum2)c[i]='C';
		else if(sum1>sum2)c[i]='A';
		else c[i]='B';
	}
	for(int i=n;i;i--)
	{
		if(a[i]=='A')sum1--;
		else if(a[i]=='B') sum2--;
		if(t=='A')sum1++;
		else sum2++;
		if(sum1==sum2)now='C';
		else if(sum1>sum2)now='A';
		else now='B';
		if(now!=c[i])ans++;
		if(t=='A')sum1--;
		else sum2--;
	}
	cout<<ans;

	return 0;
}
```

---

