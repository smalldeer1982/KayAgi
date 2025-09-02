# Right Left Wrong

## 题目描述

Vlad发现了一个由 $n$ 细胞组成的条带，从左到右从 $1$ 到 $n$ 编号。在 $i$ 中，有一个正整数 $a_i$ 和一个字母 $s_i$ ，其中所有 $s_i$ 都是'L'或'R'。

Vlad邀请您尝试通过执行任意(可能为零)操作来获得最大可能的分数。

在一次操作中，您可以选择两个索引 $l$ 和 $r$ ( $1 \le l < r \le n$ )，使 $s_l$ = `L` 和 $s_r$ = `R`，并执行以下操作:

- 在当前分数基础上增加 $a_l + a_{l + 1} + \dots + a_{r - 1} + a_r$ 分;

- 将 $s_i$ 替换为`.`

- 对于所有 $l \le i \le r$ ，这意味着您不能再选择这些索引。

例如，考虑下面的strip:

| $3$ | $5$ | $1$ | $4$ | $3$ | $2$
|  --- | --- | --- | --- | --- | ---  |
| l | r | l | l | l | r |

您可以先选择 $l = 1$ ， $r = 2$ ，并将 $3 + 5 = 8$ 添加到您的分数中。

| $3$ | $5$ | $1$ | $4$ | $3$ | $2$
|  --- | --- | --- | --- | --- | ---  |
|。|。| l | l | l | r |

然后选择 $l = 3$ ， $r = 6$ 并将 $1 + 4 + 3 + 2 = 10$ 添加到您的分数中。

| $3$ | $5$ | $1$ | $4$ | $3$ | $2$
|  --- | --- | --- | --- | --- | ---  |
|。|。|。|。|。|。|

因此无法再进行其他操作，最终得分为 $18$ 。

能达到的最高分数是多少?

## 样例 #1

### 输入

```
4
6
3 5 1 4 3 2
LRLLLR
2
2 8
LR
2
3 9
RL
5
1 2 3 4 5
LRLRR```

### 输出

```
18
10
0
22```

# 题解

## 作者：SXqwq (赞：3)

笑点解析：场上看错题了，后来发公告我才明白。

本来不想打了，睡了一觉，做梦梦到做法了，就起来写了。

### Description

有一个长度为 $n$ 的序列 $s$，$s_i$ 要么是 `l`，要么是 `r`。对于 $\forall s_i$ 都有一个价值 $a_i$。每次可选择一个 `l` 和一个 `r`，记作 $s_x,s_y$，获得 $\sum\limits_{i=x}^ya_i$ 的价值。每次操作后自动将 $s_i(i\in[l,r])$ 置为 `.`，即不可再次选择。求最大价值。

保证 $a_i \ge 1$。

要求复杂度线性。

### Analysis

注意到该操作和括号匹配差不多。贪心地考虑，**我们一定希望尽可能从序列中间开始取**，这样每个数都能产生多次贡献。

即若序列为 `llrr`，先取中间的 `l r` 一定是更优的。

但是这并不好操作。

正难则反。我们可以先取 **最前面的 `l`，最后面的 `r`**。以此类推。

具体地，首先对 $a$ 数组进行前缀和处理。从前到后扫一遍 $s$，并标记所有 `l` 位置。再从后往前扫一遍 $s$，标记所有 `r` 位置。然后一一配对，算贡献即可。

### Code

```cpp
typedef pair<int,int> PAIR;
constexpr int N = 5000010;
int T;
int a[N],sum[N];
PAIR p[N];
void solve()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],sum[i] = sum[i-1] + a[i];
    string s;
    cin>>s;
    int ans = 0,cnt = 0;
    for(int i=0;i<s.size();i++)
        if(s[i] == 'L') p[++cnt].first = i+1;
    int cnt1 = 0;
    for(int i=s.size()-1;i>=0;i--)
        if(s[i] == 'R') p[++cnt1].second = i + 1;
    for(int i=1;i<=min(cnt,cnt1);i++)
    {
        if(p[i].first >= p[i].second) continue;
        ans += sum[p[i].second]-sum[p[i].first-1];
    }
    cout<<ans<<endl;
    return 0;
```

---

## 作者：__O_v_O__ (赞：2)

考虑贪心，每次选择能选择的最长区间。

具体实现可以使用双指针：定义指针 $l,r$，初始分别指向数组左端点和右端点。

重复把 $l$ 向右移动，直到碰到 `L` 为止，把 $r$ 向左移动，直到碰到 `R` 为止。这就找到了当前的最长区间。

把答案加上区间和，再将 $l$ 加一，$r$ 减一。继续寻找最长区间，直到 $l>r$，当前记录的答案就是最终答案。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,a[2000001],l,r,q[2000001],an;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		l=0,r=n+1;
		q[0]=0,an=0;
		for(int i=1;i<=n;i++)
			cin>>a[i],q[i]=q[i-1]+a[i];
		string s;
		cin>>s,s=' '+s;
		while(1){
			l++,r--;
			while(l<=r&&s[l]!='L')l++;
			while(l<=r&&s[r]!='R')r--;
			if(l>r)break;
			an+=q[r]-q[l-1];	
		}
		cout<<an<<'\n';
	}
	return 0;
}
```

---

## 作者：jubaoyi2011 (赞：1)

其实很简单，~~个人感觉不值得评黄~~

我们可以定义两个指针 $l$  和 $r$，令 $l$ 等于数组 $s$ 的左端点减一,$r$ 等于数组 $s$ 的右端点加一。然后再贪心，每一次令 $l + 1$ 直到遇到```L```，$r - 1$直到遇到```R```，然后把区间和累加进答案直到 $l > r$，最后累加的和就是答案。


```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200005],l,r,p[200005];
char s[200005];
signed main() {
    cin>>T;
    while(T--){ 
		cin>>n;
    	int ans=0,l=0,r=n+1;
    	//p[0]=0; 
    	for(int i=1;i<=n;i++){
        	cin>>a[i];
			p[i]=p[i-1]+a[i];//前缀和  
		}
	    cin>>s;
		s=' '+s;
	    while(l<=r){//计算l,r的区间和 
    	    l++;
			r--;
        	while(l<=r&&s[l]!='L')l++;//s[l]不等于'L'则l++ 
    	    while(l<=r&&s[r]!='R')r--;//s[r]不等于'R'则r-- 
        	ans+=p[r]-p[l-1];
    	}
    	cout<<ans<<endl;
    } 
    return 0;
}
```

---

## 作者：roumeideclown (赞：1)

# 题解：CF2000D Right Left Wrong

[题目传送门](https://codeforces.com/problemset/problem/2000/D)

## 解法分析

我们不妨考虑贪心，设有四个下标 $x,y,z,w$ 且 $x < y < z < w$，则先选择 $y$ 与 $z$ 不会影响我们之后选择 $x$ 与 $w$，但是先选 $x$ 与 $w$ 我们之后就无法选择 $y$ 与 $z$。

显然，我们采用前一种选择顺序得到的权值会小于后一种。

因此在存在区间相互包含的情况下，我们应先选则里面的，再选择外面的。（区间交叉的情况其实与区间相互包含是一样的，我们只需考虑区间相互包含即可）

在实际编码时，我们可以先从左到右存下所有 $s_i = L$ 的下标，再从右到左存下所有 $s_i = R$ 的下标，依次配对求和即可。区间和用前缀和维护。

## 代码实现

我的代码可能写得比较冗长，见谅。~~抄题解建议复制其他代码。~~

```cpp
#include<bits/stdc++.h>
//#pragma G++ optimize(2,3,"Ofast")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const ll N=2e5+5;
ll n,a[N],sum[N];
string s;
void solve() {
//输入
	scanf("%lld",&n);
	for(ll i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
   //维护前缀和
		sum[i]=sum[i-1]+a[i];
	}
	cin>>s;
//存L与R的下标
	vector<int> le,ri;
	for(ll i=1;i<=n;i++) {
		if(s[i-1]=='L') le.push_back(i);
	}
	for(ll i=n;i>=1;i--) {
		if(s[i-1]=='R') ri.push_back(i);
	}
//配对
	vector<pii> op;
	for(ll i=0,j=0;i<le.size()&&j<ri.size()&&le[i]<ri[j];i++,j++) {
		op.push_back(make_pair(le[i],ri[j]));
	}
//求和
	ll ans=0;
	for(ll i=0;i<op.size();i++) {
		ans+=(sum[op[i].second]-sum[op[i].first-1]);
	}
//输出
	printf("%lld\n",ans);
}
int main() {
//多组数据の输入
	ll t;
	scanf("%lld",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：cute_overmind (赞：0)

### 题目大意
[看](https://www.luogu.com.cn/problem/CF2000D)

### 题目分析
考虑贪心。

看到题目要求，我们每一次可以选择一个最长区间进行记录答案 $ans$。

实现可以选择使用 $l,r$ 两个变量进行重复操作来寻找最长区间：
- 可以将 $l$ 向右移动直到遇到 `L`。
- 可以将 $r$ 向左移动直到遇到 `R`。

将区间和加入 $ans$ 以后，如果 $l \le r$ 那么便可以继续找，直到 $l > r$。最终 $ans$ 里面的就是最终答案。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e6 + 10;
int t , n , a[N] , l , r , sum[N];
string s;
void solve(){
	cin >> n;
    int ans = 0 , l = 0 , r = n + 1;
    for(int i = 1;i <= n;i++)
        cin >> a[i] , sum[i] = sum[i - 1] + a[i];
    cin >> s;
	s = ' ' + s;
    while(l <= r){
        l++ , r--;
        while(l <= r && s[l] != 'L') l++;
        while(l <= r && s[r] != 'R') r--;
        ans += sum[r] - sum[l - 1];
    }
    cout << ans << '\n';
}
signed main() {
    cin >> t;
    while(t--) solve();
    return 0;
}
```

---

## 作者：_Delete_ (赞：0)

## 思路

通过手推样例以及题意，可以发现我们的最优解是：对于每个区间，先选择此区间中的最大区间，再选择此区间。而对于全局最优解，为选择全局的最大区间，对于每个选出的区间进行上述操作。

注意到不管如何选择小区间，大区间是必选的，所以最优解也等于选择当前可以选择的最大区间。此操作可用双指针维护。

由于区间对于答案贡献的是区间和，所以可以维护一个前缀和数组。

## 代码


```cpp
#include<bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
//value 
ll a[2000005],pre[2000005];
char ch[2000005];


//function 
void solve(){
	ll n;
	cin>>n;
	for(ll i=1;i<=n;i++)cin>>a[i];
	for(ll i=1;i<=n;i++)cin>>ch[i];
	
	for(ll i=1;i<=n;i++)pre[i]=pre[i-1]+a[i];
	
	ll l=1,r=n,ans=0;
	while(l<=r){
		if(ch[l]=='L' && ch[r]=='R'){
			ans+=pre[r]-pre[l-1];
			l++;
			r--;
		}
		while(ch[l]!='L'&&l<=n&&l<=r)l++;
		while(ch[r]!='R'&&r>=1&&l<=r)r--;
	}
	cout<<ans<<endl;
	
}

 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	
	int t;
	cin>>t;
	while(t--)solve();
	
	
	
	return 0;
}

```

---

## 作者：hytallenxu (赞：0)

## 前言
本人没参加 CF Div.3，这道题纯粹只是早上看到了讨论区后口胡的题解，祭之。

## 正文
题目大概就是说有每次操作可以选择两个端点 $l,r$，操作的贡献便是 $\sum\limits_{i=l}^r a_i$，每次操作后区间内的所有点不能再选为端点，求最大贡献值。

这道题是简单贪心。

很显然我们要获取最大的贡献的前提是，尽可能多的匹配字符串中多的 `l` 和 `r`。

我们考虑在这样的情况下如何最大化贡献值。

显然，我们应该从尽量靠后的 `l` 和尽量靠前的 `r` 开始匹配，最后逐步扩展，慢慢的匹配到正数第一个 `l` 和 倒数第一个 `r`。

这么做的正确性是有保证的，因为假如我们第一次操作就匹配了第一个 `l` 和 倒数第一个 `r`，中间可能存在的贡献就没办法匹配了。

同时我们也是优先用中间短的区间计算贡献，保证答案最大化。

我们拿这个样例来讲解一波。

```
5
1 2 3 4 5
LRLRR
```

我们将最后一个 `l` 匹配第一个 `r`，得到贡献 $3+4=7$。

后面我们匹配第一个 `l` 和最后一个 `r`，得到贡献 $1+2+3+4+5=15$。

所以最大总贡献就是 $15+7=22$。

具体实现的时候，我们可以用队列分别加入顺序的 `l` 出现的下标和倒序的 `r` 出现的下标，最后队列匹配，弹出后加上贡献即可。

记得要用前缀和快速算出 $\sum\limits_{i=l}^r a_i$，还有一个细节就是匹配当中假如 `r` 的下标小于 `l` 的下标就可以终止了，否则可能会算出负数总贡献。

## Code
对于单次测试，时间复杂度 $O(n)$，应对 $\sum n\le2\times 10^5$ 绰绰有余。

```cpp
#include <bits/stdc++.h>
#define int long long
#ifdef LOCAL
	#include "debug.h"
#else
	#define debug(...) 42
#endif
#define mp make_pair
#define pb emplace_back
#define endl "\n"
using namespace std;
using ll = long long;
int n,t,cnt=0;

void solve(){
	int ans=0;
	cin>>n;
	vector<int> arr(n+1),sum(n+1);string s;
	for(int i=1;i<=n;i++) cin>>arr[i],sum[i]=sum[i-1]+arr[i];
	cin>>s;s='$'+s;
	queue<int> left,right;
	for(int i=1;i<=n;i++){
		if(s[i]=='L') left.push(i);
	}
	for(int i=n;i>=1;i--){
		if(s[i]=='R') right.push(i);
	}

	while(left.size() && right.size()){
		if(right.front()>left.front()){
			ans+=(sum[right.front()]-sum[left.front()-1]);
			left.pop();right.pop();
		}else{
			break;
		}
		
	}
	cout<<ans<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：cqbzrjx (赞：0)

[原题传送门](https://codeforces.com/problemset/problem/2000/D)

## 前置知识

[前缀和](https://oi-wiki.org/basic/prefix-sum/)

[双指针](https://oi-wiki.org/misc/two-pointer/?query=%E5%8F%8C%E6%8C%87%E9%92%88)

## 思路

已知题目要求 $s_i$ 只能用一次，使用贪心思想，我们可以利用双指针 $l$ 和 $r$，从左右两端开始遍历。每次求 $l$ 和 $r$ 的最大可能的和，再改变一下 $s_i$ 的值。考虑细节，如果和最大，那就可以查找 $l < r \le n$ 之中最远的 $r$。再考虑优化，可以利用前缀和记录区间 $[l,r]$ 之间和。记 $sum_i = sum_{i-1} + a_i$。最后求值的时候，直接作差求值即可。

时间复杂度： $O(n \times t)$

## AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;
int t,n;
ll a[maxn],sum[maxn];//不开longlong见祖宗
ll l,r,res;
string s;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>t;//输入
	while(t--)
	{
		cin>>n;
		memset(sum,0,sizeof sum);//多测不清空
		for(int i = 1;i <= n;i++)
		{
			cin>>a[i];
			sum[i] = sum[i - 1] + a[i];//前缀和
		}
		cin>>s;
		l = 0,r = s.size() - 1;//左端点和右端点
		res = 0;
		while(l < r)//双指针遍历
		{
			while(l < r && s[l] != 'L')//遍历l
			{
				l++;
			}
			while(l < r && s[r] != 'R')//查找最远的r
			{
				r--;
			}
			if(l < r)
			{
				res += sum[r + 1] - sum[l];//利用前缀和求值
				l++,r--;//二分思想遍历下一个
			}
			else break;//否则结束循环
		}
		cout<<res<<"\n";//输出，记得换行
	}
	return 0;//完结，撒花
}
```

[AC submissions](https://codeforces.com/contest/2000/submission/277476737)

---

## 作者：Manki23333333 (赞：0)

菜死了，C 题都没调出来。

#### 题目翻译

给定一个 $n$ 长序列 $a$ 和一个由 `L` 和 `R` 构成的字符串 $s$，每次可以选择 $1 \le l \lt r \le n$ 且 $s_l = \text{L}$， $s_r = \text{R}$，把答案加上 $\sum\limits^r_{i = l} a_i$，并删除 $s_l$ 与 $s_r$。求能获得的最大贡献。

#### 题目思路

遇到这种题，我们经常可以画图求解。

![](https://cdn.luogu.com.cn/upload/image_hosting/ko6djduk.png)

显然，我们要么选择绿色的方案，要么选择深蓝色的方案，这两种方案得到的结果是一样的，所以我们其实并不在乎区间叠加和区间重合的不同，我们只需要选择一种方案处理就可以了。因为绿色的方案比较好写，所以我们选择绿色的方案。

#### 题目实现

很容易想到双指针做法，用两个指针向内逼近，前缀和统计答案。

我的写法加了个小优化，直接跳转到最近的一个。这个优化其实不用加，但是我最开始写的时候逻辑写错了，也就懒得删了。

#### 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

long long n, m, a [200005], sum [200005];
int nxt [200005], pre [200005];
string str;
void Turn () {
	cin >> n;
	
	for (int i = 1 ; i <= n ; i ++) {
		cin >> a [i];
		sum [i] = sum [i - 1] + a [i];
	}
	
	cin >> str;
	
	int wt = 0;
	for (int i = 0 ; i < str. size () ; i ++) {
		if (str [i] == 'L') {
			nxt [wt] = i + 1;
			wt = i + 1;
		}
	}
	
	nxt [wt] = n + 1;
	
	wt = n + 1;
	for (int i = str. size () - 1 ; i > -1 ; i --) {
		if (str [i] == 'R') {
			pre [wt] = i + 1;
			wt = i + 1;
		}
	}
	
	pre [wt] = -1;
	
	int l = nxt [0], r = pre [n + 1];
	long long ans = 0;
	
//	cout << l << ", " << r << endl;
	
	while (l < r) {
//		cout << l << ", " << r;
		
		ans += sum [r] - sum [l - 1];

		l = nxt [l];
		r = pre [r];
		
//		cout << " -> " << l << ", " << r << endl;
	}
	
	cout << ans << endl;
}

int main () {
	int T;
	cin >> T;
	
	while (T --) {
//		cout << 114514 << endl;
		Turn ();
	}
	return 0;
}
```

---

