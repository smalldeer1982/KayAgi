# [APC001] E - Linear Map

## 题目背景

**请注意本题的特殊时间限制，并酌情使用较快的输入输出方式**。

在广阔的 florr 世界中，有一个不为人知的角落，它的建立是为了方便快速测试新 mob，而现在它被废弃了，但没有消失。

冒险者 MF 找到了这里，并发现其名字为：Linear map。

## 题目描述

Linear map 可看作一个字符串，每个字符都是一个 $0\sim 9$ 的数字。

MF 认为，如果一个字符串存在两段长度均 $>1$ 的不同区间的和相同，那么该字符串是无趣的。

比如，$3421$ 就是无趣的字符串，因为 $3+4=4+2+1$，而 $5023$ 也是无趣的字符串，因为 $5+0=2+3$。相反，$13$ 和 $285$ 都不是无趣的字符串。

MF 打算将 Linear map 划分为若干非空连续且不重复的子段，这些子段包含了整个字符串的所有字符，且满足每个子段都不是无趣的字符串。

MF 是一个有趣的人，于是它想算出划分的方案数，并对 $998244353$ 取模。

## 说明/提示

### 样例解释

- 样例 $\tt\#1$
	
所有划分均合法：$\{453\},\{45,3\},\{4,53\},\{4,5,3\}$。

- 样例 $\tt\#2$
	
合法方案为：$\{33,33\},\{33,3,3\},\{3,33,3\},\{3,3,33\},\{3,3,3,3\}$。

### 数据范围

对于 $100\%$ 的数据，满足 $1\le |s|\le 1.5\times 10^7$，且 $s$ 中仅包含数字。

## 样例 #1

### 输入

```
453```

### 输出

```
4```

## 样例 #2

### 输入

```
3333```

### 输出

```
5```

## 样例 #3

### 输入

```
9475739582850286```

### 输出

```
9360```

# 题解

## 作者：時空 (赞：7)

[In Luogu](https://www.luogu.com.cn/problem/P11140)

好题啊。感觉绿有点虚高，上位黄应该是。

注意到 $n \le 1.5 \times 10^7$，所以只能有 $\mathcal{O(n)}$ 的做法。

记 $f_i$ 表示将前 $i$ 个数进行划分的方案数。

则显然有 $f_i = \sum{f_j}$，其中 $j$ 满足 $j < i$ 且 $[i,j]$ 不为无趣的字符串。

手玩一下第三个样例，发现一个很好的性质：不为无趣字符串的字符串长度不会超过 $18$。具体会不会更小，出题人的爆搜表明不会超过 $9$，这里不考虑。

那么就可以 $\mathcal{O(n^2)}$ 了，瓶颈在于检查一个区间是否“无趣”。

要做到 $\mathcal{O(n)}$，检查必须是 $\mathcal{O(1)}$ 的。那么进行预处理：记 $L_i$ 表示以 $i$ 为右端点，能向左扩展的最远点，满足区间 $[L_i, i]$ 不“无趣”。

显然这个东西是单调的。若 $[x,i]$ 不“无趣”，则对于任意 $x \le k \le i$，区间 $[k,i]$ 均不“无趣”。

那么双指针预处理即可。每次右端点 $r$ 右移时，加入 $r$ 的贡献，即将 $[l,r],[l+1,r], \cdots, [r-1,r]$ 的和加入，如果其中有出现过的（即 $[l,r]$ “无趣”），就左端点 $l$ 不断右移，并删除 $l$ 的贡献，直到没有重复出现的，即 $[l,r]$ 不“无趣”。

判断是否重复出现可以开一个数组。那么就做完了。

注意有点卡常，把取模运算换成减法即可。

代码很丑，不放了。具体代码可以参考官方题解。

---

## 作者：ylch (赞：2)

遇到计数题，不是排列组合就是 dp。这道题显然是 dp。

考虑如何设计状态，序列划分问题有通用状态：设当前位置、上一次的分割点、分的段数、最后一段的信息等。

对于本题，由于不考虑段数和其他信息，不妨先简单地设 $dp_i$ 表示前 $i$ 个位置的分段方案数。

定义若 $[j,i]$ 有趣，则 $\text{check}(j,i)$ 为真。

转移类似最长上升子序列，考虑枚举前一次的分段位置 $j(j<i)$，若 $[j,i]$“有趣”则可以转移：
$$
f_i = \sum\limits_{1 \leq j \leq i} f_{j-1} \cdot [\text{check}(j,i)]
$$
（从 $j-1$ 转移是因为我们把位置 $j$ 也算作当前段的一部分）。

这样加上判定时间复杂度是 $O(n^4)$ 的，其中 $\text{check}$ 函数的时间复杂度就占了 $O(n^2)$，考虑优化判定函数和 dp 转移。

---

先优化判定函数。

判定函数的关键就是用一个桶去重，优化思路大体应该是看看能不能在遇到每个新位置时利用一下旧的桶数组，从而减少运行次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/7rja7gdk.png)

画个图，假设当前枚举到区间 $[j,i]$，发现每增加一个新位置 $x$，新出现的区间都是由这个新位置和其前面的一个连续区间 $[x-1,k]$ 拼成，那么我们不妨在转移时从后往前枚举 $k$，这样不就能利用之前的桶数组减少时间开销了吗？

注意题目中判定要求是“两段**长度均 $>1$** 的不同区间”。

$\text{check}\ O(n)$，总时间复杂度 $O(n^3)$：

```cpp
void solve()
{
	cin >> s; int n = s.size(); s=' '+s;
	for(int i = 1; i <= n; i ++){
		sum[i] = sum[i - 1] + (s[i] - '0');
	}
		
	dp[0] = 1; // 表示空串也是1个方案（用来转移[1,i]全选的状态）
	for(int i = 1; i <= n; i ++){
		unordered_set<ll> vis; // 桶数组，用来判重（放在这里便于复用）
		auto check = [&](int l, int r){
			if(l == r) return true;
			for(int k = l + 1; k <= r; k ++){ // 从l+1开始枚举是因为题目说长为1的段不算重复
				if(vis.count(sum[k] - sum[l - 1])) return false;
				vis.insert(sum[k] - sum[l - 1]);
			}
			return true;
		};
		
		for(int j = i; j >= 1; j --){ // 转移，倒叙枚举以减小复杂度
			if(check(j, i)){
				dp[i] = (dp[i] + dp[j - 1]) % mod;
			}
		}
	}
	cout << dp[n] << '\n';
}
```

---

下面优化 dp 转移。

想化简好像只能从 $\text{check}(j,i)$ 入手。

打印一下，我们惊奇地发现 $\text{check}(j,i)$ 竟然满足单调性！即对于一个固定的 $i$，存在一个分界点 $j$，使得 $1 \sim j-1$ 之间的位置都满足 $\text{check}$ 为假，$j \sim i$ 之间的位置 $\text{check}$ 为真。

> 单调性证明：如果一个区间“无趣”，包含这个区间的大区间肯定也“无趣”，满足单调性。

既然这样，考虑用双指针，枚举每一个右端点 $r$（就是前文中的 $i$），并找到最小的使 $[l,r]$ 有趣的 $l$ 进行转移。

但因为端点的枚举逻辑变了，所以修改和撤销桶数组的方式也要变。

重新从左端点枚举到右端点肯定是来不及了，那么考虑每次从端点处向左右延申，这样就能匹配上双指针的操作了。（详见代码）

最后，由于 **$l$ 单调不降**，所以时间复杂度可以做到 $O(n^2)$。

---


最后的最后，~~根据其他题解~~通过爆搜可以**得出“有趣”字符串的最大长度只有 $9$**！所以我们转移时 $j$ 与 $i$ 的距离一定不会超过 $9$。常数忽略不计，时间复杂度就是线性 $O(n)$ 的了。

好题呀！！！

> 注：本题需要卡常。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1.5e7 + 7, mod = 998244353;

string s;
ll dp[maxn];

int vis[maxn + 1000]; // 桶数组，用来判重（不要用map）
int same = 0; // 存当前重复的段个数（是否有重复）

void solve()
{
	cin >> s; int n = s.size(); s=' '+s;
	
	dp[0] = 1; // 表示空串也是1个方案（用来转移[1,i]全选的状态）
	int l = 1; // 左端点
	for(int r = 1; r <= n; r ++){
		// 扩展左端点+撤销
		while(same && l < r){ 
			int cnt = s[l] - '0'; // 因为题目说和重复的段长度必须>1
			l ++;
			for(int k = l; k <= r; k ++){
				cnt += s[k] - '0';
				same -= ((vis[cnt]--) == 2); // 卡常
			}
		}
		
		// dp转移
		for(int k = r; k >= l; k --){ 
			dp[r] += dp[k - 1];
			if(dp[r] >= mod) dp[r] -= mod; // 卡常
		}
		if(r == n) break; // 防止后面的更新部分越界
		
		// 更新r+1
		int cnt = s[r + 1] - '0';
		for(int k = r; k >= l; k --){ 
			cnt += s[k] - '0';
			same += ((++vis[cnt]) == 2); // 卡常
		}
	}
	
	cout << dp[n] << '\n';
}

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	solve();
	return 0;
}
```

---

## 作者：AirTouch (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P11140)

考虑 dp，设 $f_i$ 表示前 $i$ 个字符合法划分的方案数。

对于 $\forall i$，找到最小的 $j$，满足 $[j,i]$ 是有趣的，那么 $f_i \leftarrow \sum_{k=j-1}^{i-1} f_k$，很明显这个有单调性，如果 $[l,r]$ 有趣，那么对于 $l \le i \le r$， $[i,r]$ 肯定有趣，所以考虑用双指针维护 $[j,i]$

注意不要真的取模，会很慢，判断大于直接减掉就行

代码如下，时间复杂度 $O(n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=15000100,MOD=998244353;
int f[N],cnt,l=1,cc[N],sum;
char s[N];
signed main(){
	cin.tie(0)->ios::sync_with_stdio(0);
	cin>>s+1;
	int n=strlen(s+1);
	f[0]=1;
	for(int r=1;r<=n;r++){
		while(cnt&&l<r){
			sum=s[l]-'0';
			l++;
			for(int k=l;k<=r;k++){
				sum+=s[k]-'0';
				cnt-=((cc[sum]--)==2);
			}
		}
		sum=s[r+1]-'0';
		for(int k=r;k>=l;k--){
			f[r]+=f[k-1];
			if(f[r]>=MOD) f[r]-=MOD;
			sum+=s[k]-'0';
			cnt+=((++cc[sum])==2);
		}
	}
	cout<<f[n];
	return 0; 
}
```

---

## 作者：ELECTRODE_kaf (赞：1)

考虑简单 DP：记 $f_i$ 为以 $a_i$ 结尾的方案数，转移即为对于所有能使 $[j,i]$ 合法的 $j$，$f_i=\sum f_j$。

初始状态：$f_0=f_1=1,f_2=2$。

由于此题有一个性质：爆搜表明，合法串的长度至多为 $9$。所以看似 $O(n^2)$ 的转移实际只有 $O(n)$。

然而这么做常数大，难以通过。考虑对于一个非法串，继续扩大范围必然不会使它变得合法，故双指针预处理下每一位向左扩展的最远点。开个桶动态维护当前每种不同的和出现的次数。

具体地：每次尝试向右扩展，加上包含新的扩展点的和，如果碰到大于 $1$ 的和则非法，此时左端点向右缩减，否则更新答案。

DP 部分代码：

```cpp
dp[0]=dp[1]=1;
dp[2]=2;

rep(i,3,n) {
	rep(j,extend[i]-1,i-1) {
		dp[i]+=dp[j];
		dp[i]=(dp[i]>=mod?dp[i]-mod:dp[i]);
	}

//		cout<<"dp["<<i<<"]="<<dp[i]<<'\n';
}

print(dp[n]);
```

预处理：

```cpp
rep(i,1,n) {
	a[i]=s[i-1]-'0';
	extend[i]=INT_MAX;
}

extend[1]=extend[2]=1;
cnt[a[1]+a[2]]=1;

for(ll i=1,j=2;;) {
	if(j+1>n) break;

	bool legal=1;
	ll sum=a[j+1];

	for(ll k=j; k>=i; k--) {
		sum+=a[k];
		cnt[sum]++;

		if(cnt[sum]>1) {
			legal=0;
			sum=a[j+1];

			for(ll l=j; l>=k; l--) {
				sum+=a[l];
				cnt[sum]--;
			}

			break;
		}
	}

	if(legal==0) {
		sum=a[i];

		rep(k,i+1,j) {
			sum+=a[k];
			cnt[sum]--;
		}

		i++;
	} else {
		j++;
		extend[j]=min(extend[j],i);
	}
}

//	rep(i,1,n) {
//		print(extend[i]);
//		putchar(' ');
//	}

//	putchar('\n');
```

[完整代码](https://www.luogu.com.cn/paste/bxnrg08d)

---

## 作者：Union_Find (赞：1)

这种题一看就很 dp，所以讲一下我看到这道题的思路。

设 $f_i$ 表示前 $i$ 个数字的方案数，那么就可以如下转移，$f_i = \sum_{j = lst_i}^{i - 1} f_j$。

其中 $lst_i$ 表示满足 $[lst_i, i]$ 不是无聊的最小下标。

于是就有了初始版本。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define il inline
#define N 15000005
ll n, a[N], sum[N], f[N];
char s[N];
const ll P = 998244353;
int main(){
	scanf ("%s", s + 1), n = strlen(s + 1);
	for (int i = 1; i <= n; i++) a[i] = s[i] - '0', sum[i] = sum[i - 1] + a[i];
	f[0] = 1;
	for (int i = 1; i <= n; i++){
		set <ll> s;//存出现过的和
		for (int j = i; j >= 1; j--){
			ll flag = 0;
			for (int k = j + 1; k <= i; k++){
				if (s.count(sum[k] - sum[j - 1])){
					flag = 1;
					break;
				}s.insert(sum[k] - sum[j - 1]);
			}if (flag) break;
			f[i] = (f[i] + f[j - 1]) % P;
		}
	}printf ("%lld\n", f[n]);
	return 0;
}
```

第一看这个似乎是 $O(n^3)$ 的，但实际上不无聊的序列最长长度只有 $9$，不信的话可以写一个爆搜试试。

所以上述代码的时间复杂度其实是 $O(n)$ 的，但是常数是 $81$ 的，如果 $n \le 10^5$ 就已经过了，但是这题 $n \le 1.5 \times 10^7$，所以要优化。

我们发现，$lst_i$ 是单调递增的，所以我们并不用从 $i$ 暴力枚举到 $i - 9$，只需要在 $lst_{i - 1}$ 之上向后枚举到第一个不无聊的 $lst_i$。这样子我们就只需要用 $O(9)$ 来检查是否是无聊的序列，这样子时间复杂度就是 $O(n)$ 的时间复杂度，常数只有 $9$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 15000001
#define ll long long
ll n, f[N], t[82], cnt, p;
char s[N];
const ll P = 998244353;
int main(){
	scanf ("%s", s + 1), n = strlen(s + 1);
	f[0] = 1;
	for (int i = 1, j = 1; i <= n; i++){//这里用 j 来代替上述的 lst[i]
		for (;cnt && j < i; j++){//找到 lst[i]
			p = s[j] - '0';
			for (int k = j + 1; k <= i; k++) p += s[k] - '0', cnt -= ((t[p]--) == 2);
		}
		p = s[i + 1] - '0';
		for (int k = i; k >= j; k--)
			f[i] = f[i] + f[k - 1] > P ? f[i] + f[k - 1] - P : f[i] + f[k - 1], p += s[k] - '0', cnt += ((++t[p]) == 2);
	}printf ("%lld", f[n]);
	return 0;
}
```

最后提醒一下，本题时间比较卡，注意卡一下常。

比如以下代码会 TLE。

```
for (int i = 1, j = 1; i <= n; i++){
		for (;cnt && j < i; j++){
			p = s[j] - '0';
			for (int k = j + 1; k <= i; k++){
				p += s[k] - '0';
				if ((t[p]--) == 2) cnt--;//这里改了
			}
		}
		p = s[i + 1] - '0';
		for (int k = i; k >= j; k--){
			f[i] = (f[i] + f[k - 1]) % P, p += s[k] - '0';//取模改了
			if ((++t[p]) == 2) cnt++;//这里也改了
		}
	}printf ("%lld", f[n]);
```

一定要知道，if 语句是比直接写 bool 的表达式更劣的，所以尽量不要使用 if。还有就是取模要改成减法。

---

## 作者：AKPC (赞：1)

出题人似乎写了个 `dfs` 剪枝，作为本题的验题人，我写的是双指针预处理优化 DP，因为做法不同所以来写了一篇题解。

以下 $s$ 字符串下标从 $1$ 开始。

考虑一个暴力 DP 做法：令 $f_i$ 表示 $1\sim i$ 的划分方案数，有 $f_i=\sum\limits_{\operatorname{check}(j+1,i)}f_j$。

容易发现，所有 $>1$ 的区间和不相同等价于所有长度为 $2$ 的区间和不相同。相邻两个数的和只有 $18$ 种，因此只需要枚举 $i$ 之前的 $18$ 个转移点，从后往前枚举转移点的同时判是否合法。

而爆搜发现最长不无趣的字符串长度为 $9$，所以其实枚举前 $9$ 个转移点就行，复杂度线性，常数 $9^2=81$。

但是这个做法不足以通过，可以考虑进一步除以 $9$ 倍常数。

我们定义 $l_i$ 表示不无趣的子串中，右端点下标为 $i$ 时能够在最左边的左端点是哪里。这个很显然是单调的，所以也不难发现可以双指针维护，这样在枚举转移点的时候就不需要暴力判断合法了。

```cpp
int l=1,c=0;
ls[1]=1;
for (int i=2;i<=n;i++){
	int x=s[i]-'0';
	for (int j=i-1;j>=l;j--){
		x+=s[j]-'0';
		if (mp[x]++) c++;
	}
	while (c){
		int x=s[l]-'0';
		for (int j=l+1;j<=i;j++){
			x+=s[j]-'0';
			if (--mp[x]) c--;
		}
		l++;
	}
	ls[i]=l;
}
f[0]=1;
for (int i=1;i<=n;i++){
	bitset<105>vis;
	for (int j=i;j>=ls[i];j--){
		f[i]=(f[i]+f[j-1]);
		f[i]=(f[i]>M?f[i]-M:f[i]);
	}
}
cout<<f[n]<<'\n';
```

---

## 作者：wxzzzz (赞：0)

### 思路

DP，令 $f_i$ 表示 $1\sim i$ 的划分方案数，有：

$$f_i=\sum_{\operatorname{check}(j+1,i)}f_j$$

看上去不好优化，但是你要相信这是 ABC 的 E。

猜测合法串一定非常少，爆搜发现最长合法串长度只有 $9$，而长度 $\le 9$ 的合法串数量为 $36720$。这是为什么呢？首先长度 $>1$ 的区间不能有 $0$，且两个相同数字和它们中间夹着的数字会构成两个和相等的区间。

直接枚举的复杂度是 $O(L^2n)$，卡不过。（其中 $L$ 是合法串长度）

考虑把所有合法串建成一棵 trie 树，从后往前枚举转移点 $j$ 的同时维护在 trie 上的位置 $p$，如果 $p$ 是某个合法串在 trie 上的结尾那么 $j$ 就可以转移到 $i$。

爆搜的过程需要一些优化：

1. 剪枝，不合法了就回溯。

1. 搜的同时记录搜索树上每个点对应的 trie 上的点。

总复杂度 $O(CL+Ln)$，其中 $L,C$ 分别是合法串长度和数量。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, idt, f[15000005], cnt[105], t[50005][10];
bool ed[50005];
char s[15000005];
int mod(int x) {
    return x % 998244353;
}
void dfs(int x, int p) {
    if(p) ed[p] = 1;
    if(x > 9) return;
    for (int i = 0; i <= 9; i++) {
        s[x] = i + '0';
        bool ck = 1;
        for (int j = x - 1, sum = s[x] - '0';j >= 1; j--) {
            sum += s[j] - '0';
            if (cnt[sum]) ck = 0;
            cnt[sum]++;
        }
        if (ck) dfs(x + 1, t[p][i] = ++idt);
        for (int j = x - 1, sum = s[x] - '0'; j >= 1; j--) {
            sum += s[j] - '0';
            cnt[sum]--;
        }
        s[x] = 0;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    dfs(1, 0);
    scanf("%s",s + 1);
    n = strlen(s + 1);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1, p = t[0][s[i] - '0']; j >= 0 && p; j--) {
            if (ed[p]) f[i] = mod(f[i] + f[j]);
            if (!j) p = 0;
            else p = t[p][s[j] - '0'];
        }
    }
    cout << f[n];
    return 0;
}
```

---

