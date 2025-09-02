# Ryouko's Memory Note

## 题目描述

Ryouko is an extremely forgetful girl, she could even forget something that has just happened. So in order to remember, she takes a notebook with her, called Ryouko's Memory Note. She writes what she sees and what she hears on the notebook, and the notebook became her memory.

Though Ryouko is forgetful, she is also born with superb analyzing abilities. However, analyzing depends greatly on gathered information, in other words, memory. So she has to shuffle through her notebook whenever she needs to analyze, which is tough work.

Ryouko's notebook consists of $ n $ pages, numbered from 1 to $ n $ . To make life (and this problem) easier, we consider that to turn from page $ x $ to page $ y $ , $ |x-y| $ pages should be turned. During analyzing, Ryouko needs $ m $ pieces of information, the $ i $ -th piece of information is on page $ a_{i} $ . Information must be read from the notebook in order, so the total number of pages that Ryouko needs to turn is ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF433C/b1558cfe9712df6ce45ac8cd0bb182f42456cdc9.png).

Ryouko wants to decrease the number of pages that need to be turned. In order to achieve this, she can merge two pages of her notebook. If Ryouko merges page $ x $ to page $ y $ , she would copy all the information on page $ x $ to $ y (1<=x,y<=n) $ , and consequently, all elements in sequence $ a $ that was $ x $ would become $ y $ . Note that $ x $ can be equal to $ y $ , in which case no changes take place.

Please tell Ryouko the minimum number of pages that she needs to turn. Note she can apply the described operation at most once before the reading. Note that the answer can exceed 32-bit integers.

## 说明/提示

In the first sample, the optimal solution is to merge page 4 to 3, after merging sequence $ a $ becomes $ {1,2,3,3,3,2} $ , so the number of pages Ryouko needs to turn is $ |1-2|+|2-3|+|3-3|+|3-3|+|3-2|=3 $ .

In the second sample, optimal solution is achieved by merging page 9 to 4.

## 样例 #1

### 输入

```
4 6
1 2 3 4 3 2
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 5
9 4 3 8 8
```

### 输出

```
6
```

# 题解

## 作者：RedreamMer (赞：5)

### [CF433C](https://www.luogu.com.cn/problem/CF433C)

算法标签：贪心

### Meaning

给你 `m` 个数（每个数均不超过 `n` ），你可以使用一次修改操作，使序列中所有等于 `x`（自己给定）的数替换成 `y`（自己给定），求最小化$\sum^{i\leq m-1}_{i=1} |a_{i}-a_{i+1}|$

### Solution

其实这道题目并不难，观察每个数最后为最终答案的贡献，对于每个 $a_x(x\in[2,m-1])$ ，它的贡献就是$|a_x-a_{x-1}|+|a_x-a_{x+1}|$。

那么我们可以将所有与 $a_x$ 相等的数的相邻两个数放入一个数组 $b$ ，将 $b$ 排序后，若要改变这个数，那么最优方案一定是改成$b_{len/2}$，即这个数组的中位数，是显然最优的(~~初一上册数学知识~~)。

维护每个不相同的 $a_i$ 的 $b$ 数组，时间复杂度为 $O(M)$ ，再将种方案计算一遍，时间复杂度**大约**为 $O(M\log M)$，可以过 $1e5$ 的数据。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long//或许会暴int
const int N=1e5+1;

int a,b,s[N],ans,sum;
vector<int> st[N];
signed main() {
	// freopen("in2.in","r",stdin);
	// ios::sync_with_stdio(0);
	// cin.tie(0);
	// cout.tie(0);
	while(cin>>a>>b){
		for(int i=1;i<=a;i++) st[i].clear();
		memset(s,0,sizeof s);
		ans=sum=0;
		for(int i=1;i<=b;i++)
			cin>>s[i];
		for(int i=1;i<=b;i++){
			if(i!=1) ans+=abs(s[i]-s[i-1]);//计算初始答案
			if(i!=1&&s[i]!=s[i-1]) st[s[i]].push_back(s[i-1]);//值得一提的是这里，若两个相邻的数相同，那么就不要入数组了，否则会重复计算出错，而且要特判是不是首尾
			if(i!=b&&s[i]!=s[i+1]) st[s[i]].push_back(s[i+1]);
		}
		sum=ans;
		// cout<<ans<<endl;
		for(int i=1;i<=a;i++){
			if(!st[i].empty()){
				sort(st[i].begin(),st[i].end());
				int p=st[i][st[i].size()/2];
				// cout<<i<<' '<<p<<' '<<s[i]<<endl;
				int s1=0,s2=0;
				for(int j=0;j<st[i].size();j++){
					s1+=abs(i-st[i][j]);//计算原贡献值
					s2+=abs(st[i][j]-p);//计算改后贡献值
				}
				sum=min(sum,ans-s1+s2);
				// cout<<s1<<' '<<s2<<' '<<sum<<endl;
			}
		}
		cout<<sum<<endl;
	}
	return 0;
}
```

#### [$\color{blue}\text{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：AKPC (赞：4)

### 思路
这题可以用贪心做。

本题需要使 $\displaystyle\sum_{i=1}^{m-1}|a_i-a_{i+1}|$ 最大，我们可以很好的计算改变每个数字，对答案所得的贡献：假设 $a_0=a_1$，$a_{m+1}=a_m$，则 $a_i$ 对答案的贡献为 $|a_{i-1}-a_i|+|a_{i+1}-a_i|$，其中 $i\in[1,n]$。那么，计算 $a_i$ 贡献值的关键还是 $a_{i-1}$ 和 $a_{i+1}$。我们可以开 $n$ 个 `vector` 存储这些 $a_{i-1}$ 和 $a_{i+1}$。

存储好之后，枚举一遍每个 $a$ 数组出现了的值，遍历对应的 `vector`，计算答案即可。怎么计算答案呢？第一步显然是给 `vector` 排序，然后从这个 `vector` 中找出修改的值 $a_j$。

怎么找这个值呢？这就相当于问你，数轴上有 $p$ 个点（$p$ 表示该 `vector` 元素个数），这些点的位置正好是每个 `vector` 的元素值，然后求一个点使得这个点与 $p$ 个点的距离之和最小。显然答案就是该 `vector` 里面的中位数了，这就是贪心思路了。`vector` 经过排序后，中位数显然就是下标 $\lfloor\dfrac{len}{2}\rfloor$ 的元素了。

最后把每个答案取一个最小值，输出即可。注意题目说了 $i$ 可以等于 $j$，也就相当于可以不改，所以先计算一遍不修改时的答案，然后跟其他答案一起取最小值。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
    int x=0;bool f=1;register char c=getchar();
    while (c<48||c>57){if(c=='-') f=0;c=getchar();}
    while (c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
int n=read(),m=read(),a[100001],ans,minn;
vector<int>f[100001];
signed main(){
	for (int i=1;i<=m;i++) a[i]=read();
	for (int i=1;i<=m;i++){
		if (i!=1) ans+=labs(a[i]-a[i-1]);
		if (i!=1&&a[i-1]!=a[i]) f[a[i]].push_back(a[i-1]);
		if (i!=m&&a[i+1]!=a[i]) f[a[i]].push_back(a[i+1]);
	}
	minn=ans;
	for (int i=1;i<=n;i++){
		if (f[i].empty()) continue;
		sort(f[i].begin(),f[i].end());
		int k=f[i][f[i].size()/2],s1=0,s2=0;
		for (int j=0;j<(int)f[i].size();j++) s1+=labs(f[i][j]-i),s2+=labs(f[i][j]-k);
		minn=min(minn,ans-s1+s2);
	}
	cout<<minn;
	return 0;
}
```


---

## 作者：When (赞：2)

#### 题意

给出2个正整数 $n,m(1\leq n,m \leq 10^5)$与长度为$m$的序列$a[1-m]$，保证$a[i]\leq n$，你可以把所有值为$a[i]$的元素改为$a[j]$，可以不改且只能改一次，要求最小化$\sum\limits_{i=1}^{i\leq m-1} |a_i-a_{i+1}|$。

#### 算法

贪心，暴力枚举

#### 思路

首先要知道一个结论：

> 当$a$为序列$b$的中位数时，$\sum\limits_{i=1}^{i\leq n}{|a-b_i|}$最小。

放到这个题目里，对于每一个元素$a[i]$，序列$b$就是与它相邻且不相等的元素集合。所以，我们可以统计出与每一个相邻的数，排序之后用中位数计算对答案的贡献。

由于每一个数最多被枚举了2遍，所以总复杂度为$O(2mlogm)$。

具体实现请看代码。

#### 参考代码

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>
#define LL long long

using namespace std;

const int maxn = 1e5 + 10;
int n,a[maxn],m;
LL Ans = 0;
vector<int> v[maxn];

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++ i) scanf("%d", a + i);
    for(int i = 1; i <= m; ++ i){
        if(a[i] != a[i - 1] && i != 1) v[a[i]].push_back(a[i - 1]);
        if(a[i] != a[i + 1] && i != m) v[a[i]].push_back(a[i + 1]);
        if(i != 1) Ans += abs(a[i] - a[i - 1]);  //先处理出初始答案
    }
    LL ls = Ans;
    for(int i = 1; i <= n; ++ i){
        int len = v[i].size();
        if(!len) continue;
        sort(v[i].begin(), v[i].end());
        int pos = v[i][len / 2]; LL ret = ls;
        for(int j = 0; j < len; ++ j){
            ret -= abs(i - v[i][j]);
            ret += abs(pos - v[i][j]); //计算更改后的答案
        }
        Ans = min(Ans, ret);
    }
    printf("%lld\n", Ans);
    return 0;
}
```



---

## 作者：_Flame_ (赞：1)

## 思路

贪心。

首先可以发现，当序列中所有数都相等时，无论怎么修改最后答案都为零，直接特判可以过。

然后考虑一般情况，可以发现，每一个数 $a_i$ 对最终答案的贡献只有 $\mid a_i-a_{i-1}\mid+\mid a_i-a_{i+1}\mid$。

然后思路就比较明显了，我们可以先存下每个值为 $x$ 的数的左右两边的数，然后计算总贡献的最小值。

然后用一个结论：

- 当 $x$ 为长度为 $n$ 序列 $y$ 的中位数时，可以使得 $\min\sum \limits_{i=1} ^ {i \le n}\mid x-y_i\mid$。

具体证明可以用绝对值的几何意义。

具体到这道题中就是对存下的左右两边的数进行排序，取中位数使得贡献最小化即可解决。

## Code

```cpp

#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=100010;
const int maxm=110;
const int mod=1e9+7;
const int inf=1e18;

int n,m;
int tot;
int a[maxn];
bool flag=0;

vector<int> cnt[maxn];

int ans=inf,sum;

void solve(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		a[i]=read();
	}
	for(int i=1;i<=m;i++){
		if(a[i]!=a[i-1]&&i!=1){
			cnt[a[i]].push_back(a[i-1]);
		}
		if(a[i]!=a[i+1]&&i!=m){
			cnt[a[i]].push_back(a[i+1]);
		}
	}
	for(int i=2;i<=m;i++){
		sum+=abs(a[i]-a[i-1]);
	}
	for(int i=1;i<=n;i++){
		int len=cnt[i].size();
		if(len){
			flag=1;
			sort(cnt[i].begin(),cnt[i].end());
			int x=cnt[i][len/2];
			int cnt1=0;
			for(int j=0;j<len;j++){
				cnt1+=abs(cnt[i][j]-x)-abs(i-cnt[i][j]);
			}
			ans=min(ans,sum+cnt1);
		}
	}
	if(flag==1){
		write(ans);
		puts("");
	}
	else{
		puts("0");
	}
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}



```



---

## 作者：gdf_yhm (赞：1)

[CF433C](https://www.luogu.com.cn/problem/CF433C)

### 思路

出于习惯，调换 $n$ 和 $m$，$n$ 为数组长度，$m$ 为值域。

考虑枚举被替换的 $a_i$。枚举值域 $1$ 到 $m$ 的权值 $x$。

每个权值为 $x$ 的点 $a_i$ 的贡献是 $\mid a_i-a_{i-1} \mid+\mid a_i-a_{i+1} \mid$。由于 $a_i$ 被更改，贡献会随之变化，与之有关的是所有 $a_i$ 的左右两边的点。将这些点全部放进 vector 里。设 $p_x$ 表示所有这样的点。

如果要把 $x$ 改为 $y$ 并令 $ans$ 最小，受影响的是 $\sum \mid x-p_{i,j} \mid$ 变为 $\sum \mid y-p_{i,j} \mid$，要使 $\sum \mid y-p_{i,j} \mid$ 最小。

由 $\textbf{初一}$ 知识，当取 $y$ 为 $p_{i,0}$ 到 $p_{i,len}$ 的中位数时，式子最小。一开始我以为是平均数，整半天。

用最开始算出的不修改答案 $num$ 减去 $\sum \mid x-p_{i,j} \mid$ 加上 $\sum \mid y-p_{i,j} \mid$ 得到修改 $x$ 的最小答案，再取最小值。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1000000000;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn],ans,num;
vector<int> p[maxn];
int sum,x,sum1;

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	m=read();n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		if(i!=1)num+=abs(a[i]-a[i-1]);
	}
	for(int i=1;i<=n;i++){
		if(a[i-1]&&a[i-1]!=a[i])p[a[i]].push_back(a[i-1]);
		if(a[i+1]&&a[i+1]!=a[i])p[a[i]].push_back(a[i+1]);
	}
	ans=num;
	for(int i=1;i<=m;i++){
		if(p[i].size()){
			sort(p[i].begin(),p[i].end());
			sum=sum1=0;x=p[i][p[i].size()/2];
			for(int j=0;j<p[i].size();j++){
				sum+=abs(i-p[i][j]);
				sum1+=abs(x-p[i][j]);
			}
			ans=min(ans,num-sum+sum1);
		}
	}
	printf("%lld\n",ans);
}

```

---

## 作者：Cute_yhb (赞：0)

$\color{blue}\texttt{Difficulty: 1800}$

考虑存储每一个数 $x$ 左右两边的所有的数。记这一个数集为 $V_x$。

那么如果要 $x$ 这个数修改的话，为了让 $x$ 对总权值的贡献尽量的小，$x$ 取 $V_x$ 数集的中位数最优。

时间复杂度 $O(n\log n)$。

---

## 作者：MortisM (赞：0)

首先，考虑到每一个数对答案的贡献是 $|a_i-a_{i-1}|+|a_i-a_{i+1}|$，所以可以把相同 $a_i$ 的 $a_{i-1}$ 和 $a_{i+1}$ 都扔到一起。

然后问题转化为对于一个 $x$ 和 $a_1,a_2,\cdots,a_k$ 要求最小的 $\sum_{i=1}^k|a_i-x|$。

小学数学题，取中位数即可。

时间复杂度是单 $\log$ 的。

```cpp
// Author: Jerry_Jiang
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define ALL(a) (a).begin(), (a).end()
#define pb push_back
#define mk make_pair
#define pii pair<int, int>
#define pis pair<int, string>
#define sec second
#define fir first
#define sz(a) int((a).size())
#define Yes cout << "Yes" << endl
#define YES cout << "YES" << endl
#define No cout << "No" << endl
#define NO cout << "NO" << endl
#define debug(x) cerr << #x << ": " << x << endl
#define double long double
#define mms(arr, n) memset(arr, n, sizeof(arr))
#define rep(i, a, n) for (int i = (a); i <= (n); ++i)
#define per(i, n, a) for (int i = (n); i >= (a); --i)
int max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}
int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}
const int INF = 0x3f3f3f3f3f3f3f3f;
const int MOD = 1000000007;
const int N = 1e5 + 10;

// bool st;
int n, m, a[N];
vector<int> vec[N];
// bool en;

void solve()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
		cin >> a[i];
	for (int i = 1; i <= m; i++)
	{
		if (i > 1 && a[i - 1] != a[i])
			vec[a[i]].push_back(a[i - 1]);
		if (i < m && a[i] != a[i + 1])
			vec[a[i]].push_back(a[i + 1]);
	}
	int ans = 0;
	for (int i = 1; i < m; i++)
		ans += abs(a[i + 1] - a[i]);
	int res = ans;
	for (int i = 1; i <= n; i++)
		if (!vec[i].empty())
		{
			sort(ALL(vec[i]));
			int x = vec[i][(int)vec[i].size() / 2], ori = 0, sum = 0;
			for (auto v : vec[i])
			{
				ori += abs(i - v);
				sum += abs(x - v);
			}
			int nw = ans + sum - ori;
			res = min(res, nw);
		}
	cout << res << "\n";
}

signed main()
{
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	// cerr<<(&en-&st)/1024.0/1024.0<<endl;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int testcase = 1;
	// cin >> testcase;
	while (testcase--)
		solve();
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### 题目分析:

首先有一个结论：$\sum_{i=1}^{n}|b-a_i|$，取最小值的时候 $b$ 为 $a$ 数列的中位数。

当然这个取值不一定唯一，若 $n$ 为偶数，则 $b$ 可以取中间两数的数值区间之间的任意一个数。

这个结论感性理解一下就是：当 $b$ 为中位数时向上加会导致小的数与其的差值增大，向下减又会导致大的数与其的差值变大，两项综合考虑就取中间了。

--------
然后就直接对于每一个数将其左右两边的数离线下来，排序，取中位数并用这个中位数去更新答案即可。

值得注意的是，对于重复的数将某一个数夹在中间，即 $a,b,a$ 这样的形式，$b$ 是需要重复计算的。而对于另一种相邻两个数相等的情况，则不能计入。

----------
### 代码：

```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector <long long> num[100005];
long long a[100005],n,m,sum,ans,now,p;
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)scanf("%lld",&a[i]);
	a[0]=a[1];a[m+1]=a[m];
	for(int i=1;i<=m;i++){
		sum+=abs(a[i]-a[i-1]);
		if(a[i]!=a[i-1])num[a[i]].push_back(a[i-1]);
		if(a[i]!=a[i+1])num[a[i]].push_back(a[i+1]);
	}
	ans=sum;
	for(int i=1;i<=n;i++){
		if(num[i].empty())continue;
		sort(num[i].begin(),num[i].end());
		now=sum;p=num[i][((num[i].size())/2)];
		for(int j=0;j<num[i].size();j++)
		now=now-abs(i-num[i][j])+abs(p-num[i][j]);
		ans=min(ans,now);
	}
	printf("%lld",ans);
	return 0;
}
```


---

