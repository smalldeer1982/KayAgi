# Gorilla and the Exam

## 题目描述

# Gorilla and the Exam


由于“T世代”高年级学生的教师短缺，决定由一只巨大的雄性猩猩来为学生们进行考试。然而，这并不是那么简单；为了证明其能力，它需要解决以下问题。

给定一个数组 $ b $ ，我们定义函数 $ f(b) $ 为将数组 $ b $ 变为空所需的最小操作次数：

- 选择两个整数 $ l $ 和 $ r $ ，满足 $ l \le r $ ，并令 $ x $ 为数组 $ b_l, b_{l+1}, \ldots, b_r $ 中的最小值；
- 然后，删除所有满足 $ l \le i \le r $ 且 $ b_i = x $ 的元素，删除后的元素将被移除，剩余元素的索引重新编号。

现在给定一个长度为 $ n $ 的数组 $ a $ 和一个整数 $ k $ 。你可以至多进行 $ k $ 次修改操作，每次可以选择数组中的任意索引 $ i $ （$ 1 \le i \le n $）和任意整数 $ p $ ，将 $ a_i $ 替换为 $ p $ 。

帮助猩猩求出经过至多 $ k $ 次替换操作后，数组 $ a $ 的 $ f(a) $ 可以达到的最小值。

## 说明/提示

- 在第一个测试数据中，数组 $ [48843] $ 只包含一个元素，因此 $ f([48843]) = 1 $，只需一次操作即可删除该元素。
- 在第二个测试数据中，你可以将数组 $ [2, 3, 2] $ 中的第二个元素修改为 $ 2 $ ，使得数组变为 $ [2, 2, 2] $ ，此时 $ f([2, 2, 2]) = 1 $ ，因为可以选择整个数组，最小值为 $ 2 $，然后一次删除所有的 $ 2 $ 元素。

## 样例 #1

### 输入

```
6
1 0
48843
3 1
2 3 2
5 3
1 2 3 4 5
7 0
4 7 1 3 2 4 1
11 4
3 2 1 4 4 3 4 2 1 3 3
5 5
1 2 3 4 5```

### 输出

```
1
1
2
5
2
1```

# 题解

## 作者：TainityAnle (赞：4)

### 题意

给定一个序列，每次选中区间 $[l,r]$，删除区间中的最小值。把这个序列删光的最小次数为 $f(x)$。

有 $k$ 次操作，每次操作可以改变序列中的一个数。求 $k$ 次操作后 $f(x)$ 的最小值。

### 思路

这个题我开题之后就发现区间选整个序列一定是最优的，因为整个序列的范围一定比区间的范围大。即使某个某区间内的最小值 $x$ 的个数比整个序列的最小值的个数多也没关系。因为只要每次都选整个区间，一定会有某次序列的最小值是 $x$，然后把它删掉。

如果每次都选整个序列，容易发现删的次数实际上就是序列中不同数字的个数。

最小化 $f(x)$ 就相当于最小化序列中不同数字的个数。$k$ 次操作，每次把出现次数最少的数变成出现次数最多的数即可。

这样，对每个数字出现的次数从小到大排序。到第 $i$ 个数字时，如果 $k$ 大于等于当前数字出现的次数，就用 $k$ 减去出现次数，否则输出答案。

设原序列不同数字的个数是 $m$，由于我们现在已经将 $i-1$ 个数全部转换为其它数字，答案就是 $m-i$。

如果已经遍历完了，还没输出过答案，说明 $k$ 很大，能把所有数都转换成一个数。输出 $1$ 即可。

用 `map` 开桶维护每个数字出现的次数。

最后，多组数据记得清空。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,x;
map<int,int> t;
vector<int> a;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>k;
		t.clear(),a.clear();
		for(int i=1;i<=n;i++) cin>>x,t[x]++;
		for(auto c:t) a.push_back(c.second);
		sort(a.begin(),a.end());
		int m=a.size(),flag=0;
		for(int i=0;i<m;i++){
			if(k>=a[i]) k-=a[i];
			else{
				cout<<m-i<<endl;
				flag=1;
				break;
			}
		}
		if(!flag) cout<<1<<endl;
	}
	return 0;
}
```

---

还有一种统计答案的方法。就是用优先队列维护最小值，$k$ 次操作，每次拿出队头，将它减一再放回去，最后输出队列长度即可。如果最后队被删空，也是都被转化成了一个数，输出 $1$。因为优先队列的常数，比上面稍慢一些，但代码更好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,k,x;
map<int,int> t;
priority_queue<int,vector<int>,greater<int> > q;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>k;
		t.clear();
		while(!q.empty()) q.pop();
		for(int i=1;i<=n;i++) cin>>x,t[x]++;
		for(auto a:t) q.push(a.second);
		for(int i=1;i<=k;i++){
			int tmp=q.top();
			q.pop();
			if(tmp-1) q.push(tmp-1);
		}
		cout<<(q.size()?q.size():1)<<endl;
	}
	return 0;
}
```

---

## 作者：zhangxiaohan007 (赞：2)

这道题他给你写了很长一段，实际上就是求改 $k$ 个数之后总共有多少种数。那这道题就很简单了，我们只需要先离散化，然后用桶统计有多少种数，接着每种数按数量从小到大排序，接着把数组遍历一遍，只要次数还没用完把这种数给变成数量最多的那种数即可。

下面给出代码理解：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
using namespace std;
int n,k,a[114514],tot,s[114514];
map<int,int>mp;//用map离散化
void solve()
{
	mp.clear();
	tot=0;
	cin>>n>>k;
	for(int i=0;i<=n;i++)
	{
		s[i]=0;
	}//多测不清空，爆零两行泪
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(mp.count(a[i])==0)mp[a[i]]=++tot;
		a[i]=mp[a[i]];
		s[a[i]]++;//桶，存每种数的数量
	}
	sort(s+1,s+n+1);//按数量从小到大排序
	int i=1,ans=0;
	while(s[i]==0)i++;//除去没有的那些数
	for(i;i<n;i++)
	{
		if(k>=s[i])//如果还能换
		{
			ans++;
			k-=s[i];
//把这种数给变成数量最多的那种数（最后那种数是不被
//遍历的，因为至少要删一次，所以最后的数不用加桶）
		}
	}
	cout<<tot-ans<<"\n";//总的数的种数数量减去变掉的
	
}
int main()
{
	int t;
	cin>>t;
	while(t--)//多测
	{
		solve();
	}
	return 0;
}
```

---

## 作者：JimmyQ (赞：2)

# CF2057B Gorilla and the Exam

## 思路

不难发现其实每次操作就是把数组 $a$ 内所有值为 $y$ 的数都删除掉（$y$ 为数组 $a$ 中的莫一个值）。所以我们需要把尽可能多的数都变成原来数组里出现次数最多的数（从出现数量最少的开始，这样能使得消失的数值种类最大化）。首先想到使用数组进行统计，但是又发现 $a_i\le 10^9$ 远远大于数组可以设置的范围，所以可以使用 MAP。最后的答案为原来数组不同值的种类 $-$ 消失的数值种类。

## AC 代码

```
#include<bits/stdc++.h>
using namespace std;
long long t,x,n,k,cnt,ans;
map<long long,long long>mp;
bool cmp(pair<long long,long long>&a,pair<long long,long long>&b){
	return a.second<b.second;
}
int main(){
	cin>>t;
	while(t--){
		mp.clear();
		cin>>n>>k;
		cnt=ans=0;
		for(int i=1;i<=n;i++){
			cin>>x;
			mp[x]++;
			if(mp[x]==1) ans++;
		}
		vector<pair<long long,long long>> v(mp.begin(),mp.end());
		sort(v.begin(),v.end(),cmp);
		for(pair<long long,long long> e:v){
			if(e.second<=k) k-=e.second,cnt++;
		}
		cout<<max(1ll,ans-cnt)<<endl;
	}
}
```

[AC 记录](https://codeforces.com/contest/2057/submission/299635946)

---

## 作者：Kawaii_qiuw (赞：1)

题面很好理解，不再赘述。

### 解题思路

首先执行 $k$ 次操作，这些操作能够将数组中的一个数变为任意数。

然后执行删除操作，求使数组为空的最小删除操作次数。

注意删除操作的性质——一次操作能够将数组中所有最小值删除。

也就是说，每次操作能够删除一种数，那么问题变成运用 $k$ 次操作，使得数组中的数的种类最少。

显然的思路是按照数的频率排序，然后依次进行 $k$ 次操作即可。

### 代码

```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
void solve() {
    int n, k;
    cin >> n >> k;
    map<int,int>cnt;
    int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        cnt[x]++;
    }
    vector<int>oc;
    for (auto [x, y] : cnt) {
        oc.push_back(y);
    }
    sort(oc.begin(), oc.end());
    int ans = 1;
    for (int i = 0; i < oc.size() - 1; i++) {
        if(k >= oc[i])k -= oc[i];
        else ans++;
    }
    cout << ans << "\n";
    return;
}
 
int main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

继续加油。

---

## 作者：Drifty (赞：1)

### Solution

我们贪心，显然让每次操作的 $l = 1, r = n$ 一定不劣。

那么我们会发现每这样操作一次实际上就是把 $a$ 中的 $\min\{a_i\}$ 全删了。那么我们如果直接操作，就需要操作序列中数的种数次。

考虑加入 $k$ 次修改后怎么做。我们一直修改当前最少的数，显然只有一种数修改完全后，才能能使操作数减 $1$。那么我们判断最多能完全修改多少种数就好了。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
int T, n, k;
void solve() {
    cin >> n >> k;
    vector <int> a(n + 1); a[n] = -1;
    for (int i = 0; i < n; i ++) cin >> a[i];
    sort (a.begin(), a.end() - 1);
    vector <int> siz;
    int l = 1;
    for (int i = 1; i <= n; i ++)
        if (a[i] != a[i - 1]) siz.push_back(l), l = 1; else l ++;
    sort (siz.begin(), siz.end());
    int p = 0, ans = siz.size();
    while (k >= siz[p]) {
        k -= siz[p ++]; ans --;
        if (p >= (int)siz.size()) break;
    }
    cout << max(ans, 1) << '\n';
}
int32_t main() {
    cin.tie(NULL) -> sync_with_stdio(false);
    for (cin >> T; T --; ) solve();
    return 0;
}

```

---

## 作者：FXLIR (赞：0)

### 思路

不难发现，$l$ 和 $r$ 的最优选择一定是 $l=1,r=n$（即覆盖整个区间）。

然后可以得出，如果不做任何修改的话，删除这个数组所需的次数就是数组中不同元素的个数，因为在  $l=1,r=n$ 的情况下，每次删除都会删除整个数组中所有值相同的元素。

那么，如果需要最小化删除次数，我们就需要在修改时最小化数组中不同元素的个数。

显然，如果重复“把数组中所有出现次数最少的元素改为出现次数最多的元素”这一过程的话，当无法再修改时，数组中不同元素的个数就是最终的答案。

在实际的代码编写中，我们并不用模拟修改元素的过程，只需要用优先队列存储每个元素出现的次数，然后每次将优先队列中最小的元素取出，如果其小于等于剩余的修改次数，就把它从优先队列中弹出。否则退出修改过程，此时优先队列中剩余的元素个数就是最终的答案。

需要注意的是，如果 $k=n$，优先队列中的元素会被全部删除，需要特判这种情况。

### 代码
```cpp
#include<map>
#include<queue>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=1e5+5,INF=1e9;
map<int,int> mp;//用于统计各个元素出现的次数
int t,n,k,a,ans;
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		mp.clear();
		priority_queue<int,deque<int>,greater<int> > q;//优先队列
		cin>>n>>k;
		for(int i=1;i<=n;i++){
			cin>>a;
			mp[a]++;
		}
		for(auto i:mp){
			q.push(i.second);
		} 
		while(k){
			int t=q.top();
			if(t<=k){
				q.pop();
			}
			k=max(0ll,k-t);
		}
		cout<<max((int)q.size(),1ll)<<"\n";
	}
	return 0;
}
```

---

## 作者：_ayaka_ (赞：0)

### 思路

开题就发现最优的 $l$ 和 $r$ 也就是覆盖全区间，问题变成修改一个区间里 $k$ 个元素的值，求最少有多少种元素。

刚好我手里有大根堆的优先队列，就用优先队列来写了。做法就是先开一个 `map<int,int>` 存一下输入，然后把 `map` 存到优先队列里，每次判断能否把第一项全部改变，可以就将其 `pop` 出去并将 $k$ 减去此项的大小，否则结束这段判断。最后输出优先队列的大小即可。时间复杂度 $O(Tn\log n)$，可以通过此题。

注意，如果 $k=n$，会将优先队列全吐完，所以要将优先队列的大小与 $1$ 取 $\max$。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, k, x;
priority_queue<int, vector<int>, greater<int>> q;
map<int, int> a;
signed main() {
	cin >> t;
	while (t--) {
		a.clear();
		cin >> n >> k;
		for (int i = 1; i <= n; i++) {
			cin >> x;
			a[x]++;
		}
		for (auto i : a) q.push(i.second);
		while (!q.empty()) {
			if (k >= q.top()) {
				k -= q.top();
				q.pop();
			} else break;
		}
		cout << max((int)q.size(), 1) << "\n";
		while (!q.empty()) q.pop();
	}
	return 0;
```

---

## 作者：god_std (赞：0)

### 题目大意

翻译已经很清楚了。
### 分析与解

如果不能换，显然，$f(a)$ 就等于 $a$ 数组内元素的种类个数。

如果可以换，则将所有元素种类中元素最少的一个元素种类替换为元素种类中元素最多的元素种类，再将元素第二少的元素种类替换，以此类推，知道无法替换为止，此时计算 $f(a)$ 的值。

时间复杂度：$O(nT)$，但是可以 AC。

---

## 作者：nannangua (赞：0)

[传送门](https://codeforces.com/problemset/problem/2057/B)

### 题意分析
首先如果要使 $ f(a) $ 最小，就要用较小的 $ k $ 删除尽量多的数，所以我们可以先用 `map` 统计每个数字出现的次数，再用 `vector` 记录一遍出现的次数，最后将每个出现过的次数排序

这样，我们遍历到第 $ i $ 个数字时，如果 $ k\geq b_i $，那么就用  $ k-b_i $，否则输出答案。

当遍历完后，如果没有输出过答案，那么得出答案为 $ 1 $。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> a;
vector<int> b; 
void CLEAR()
{
	a.clear();
	b.clear();
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T,n,k;
	cin>>T;
	while(T--)
	{
		int ans=0;
		cin>>n>>k;
		CLEAR();
		for(int i=1;i<=n;i++)
		{
			int o;
			cin>>o;
			a[o]++;
		}
		for(auto c:a) b.push_back(c.second);
		sort(b.begin(),b.end());
		bool f=0;
		for(int i=0;i<b.size();i++)
		{
			if(k>=b[i]) k-=b[i];
			else
			{
				cout<<b.size()-i<<endl;
				f=1;
				break;
			}
		}
		if(!f) cout<<1<<endl;
	}
	return 0;
} 
```

---

## 作者：zhangxiao666 (赞：0)

显然每次可以选择整个数列，一定不劣，则 $f$ 可以转化为数列元素种类数，将出现次数数排序，每次修改数量最少的即可。


```cpp
#include <bits/stdc++.h>
#define dbg(x) cout << #x << '=' << x << endl
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define frep(i, r, l) for (int i = (r); i >= (l); i--)
//#define int long long
using namespace std;

const int N = 1e5 + 10;

int n, nm, k;
int a[N], b[N], tot[N];

void Lisan()
{
    rep(i, 1, n) b[i] = a[i];
    sort(b + 1, b + n + 1);
    nm = unique(b + 1, b + n + 1) - b - 1;
    rep(i, 1, n) a[i] = lower_bound(b + 1, b + nm + 1, a[i]) - b;
    rep(i, 1, n) tot[i] = 0;
    rep(i, 1, n) tot[a[i]]++;
}

void work()
{
    cin >> n >> k;
    rep(i, 1, n) cin >> a[i];
    Lisan();
    sort(tot + 1, tot + nm + 1);
    int sum = nm;
    rep(i, 1, nm)
    {
        if (k <= 0 || sum == 1) break;
        if (k >= tot[i]) sum--;
        k -= tot[i];
    }
    cout << sum << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1, opinput = 1;
    if (opinput) cin >> T;
    while (T--) work();
    return 0;
}
```

---

## 作者：ybclch2026 (赞：0)

## 题目大意
给定一个序列，每次选择区间 $[l,r]$，记 $x=min_{l≤i≤r}$，删除区间内所有 $a_i=x$。把这个序列删光的最小次数为 $f(x)$。

有 $k$ 次操作，每次操作可以改变序列中的一个数。求 $k$ 次操作后 $f(x)$ 的最小值。

## 思路
删完序列的次数就是序列里数字的种类，那让 $f(x)$ 最小就是让序列里数字的种类最小。

所以将数字的种类的尽可能多减少，答案就是剩下的数字的种类。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn = 1e5 + 5;
int t, n, a[maxn], vis[maxn], cnt, k;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> k;
		memset(vis, 0, sizeof vis);
		cnt = 0;
		for (int i = 1; i <= n; i++)cin >> a[i];
		sort(a + 1, a + 1 + n);
		vis[++cnt] = 1;
		for (int i = 2; i <= n; i++) {
			if (a[i] != a[i - 1])cnt++;
			vis[cnt]++;
		}
		sort(vis + 1, vis + 1 + cnt);
		int op = cnt - 1, f = 0;
		for (int i = 1; i <= n; i++) {
			k -= vis[i];
			if (k < 0) {
				op = i - 1;
				break;
			}
			f = 1;
		}
		if (!f)cout << cnt << endl;
		else cout << cnt - op << endl;
	}
	return 0;
}
```

---

## 作者：SmartWind (赞：0)

根据题目要求，我们可以把这个问题转化为：经过至多 $k$ 次操作后，数组中数字的最少种类数。

> 十年 cf 一场空，开 `unordered_map` 见祖宗。（2025.1.5 02:01）

使用 `map` 把大数转换为小数，记录每种数字出现的次数，然后对于这些次数从小到大排序后求前缀和，最后二分查找修改 $k$ 次以后数组中被修改的数字种类个数，具体可以看代码实现。


```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+7;

int tim[N],a[N];
int t,n,k,cnt;

signed main(){
    cin>>t;
    while(t--){
        for(int i=1;i<=cnt;i++) tim[i]=0;
        cnt=0;
        map<int,int> mp;
        cin>>n>>k;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(mp[a[i]]==0) mp[a[i]]=++cnt;
            tim[mp[a[i]]]++;
        }
        sort(tim+1,tim+cnt+1);
        for(int i=1;i<=cnt;i++){
            tim[i]+=tim[i-1];
        }
        int ans=cnt;
        int pos=upper_bound(tim+1,tim+cnt+1,k)-tim;
        ans-=pos-1;
        if(ans<=0) ans=1;
        cout<<ans<<"\n";
    }
    return 0;
}

```

---

## 作者：_anll_ (赞：0)

## 思路
尝试手玩样例，可以得到的结论是，在每一轮变化中，我们都尝试将出现次数最少的那个数变成出现次数最多的数，这样一定是最优的。

对于实现，我们考虑开个 map 去存每个数出现了几次，然后将出现次数丢进优先队列里，注意小根堆。然后每次取出一个数，看当前的剩余操作次数能否支持将其完全删除，若可以则删除，不可以就结束遍历。

## 代码
```cpp
#include<iostream>
#include<map>
#include<queue>
#define int long long
using namespace std;
int n,k;
map<int,int> mo;
void solve(){
	cin>>n>>k;int x,ans=0;mo.clear();
	priority_queue<int> qo;
	for(int i=1;i<=n;i++){
		cin>>x;mo[x]++;
	}
	for(auto a:mo){
		qo.push(-a.second);
		ans++;
	}
	while(!qo.empty()){
		x=-qo.top();qo.pop();
		if(x>k||!qo.size()) break;
		k-=x,ans--;
	}
	cout<<ans<<endl;
}
signed main(){
	int t;cin>>t;while(t--) solve();
	return 0;
}
```

---

## 作者：cqbzhzf (赞：0)

[vjudge 中文翻译](https://vjudge.net/problem/CodeForces-2057B#author=GPT_zh)
### 思路
要使 $f(a)$ 最小，那么就要使用**尽量小**的 $k$ 删除**尽量多**的数，所以很容易想到对不同的 $a_i$ 的个数从小到大排序，然后进行删除操作，并统计答案。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n,k,a[N];
map<int,int> mp;
vector<int> tt;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)
			cin>>a[i],mp[a[i]]++;//map 统计次数
		for(auto[x,y]:mp)//注意支持本写法的语言环境
			tt.push_back(y);//用 vector 记录每个数出现过的次数
		sort(tt.begin(),tt.end());//将每个数出现过的次数排序，显然 O(nlogn) 的时间复杂度是可以接受的
		int ans=tt.size();//不做任何操作时，答案为不同数字的个数
		for(int i=0;i<tt.size()-1;i++)//答案至少为 1，注意循环边界
		{
			if(k>=tt[i])//如果当前数字能进行修改操作，更新答案与 k 值
			{
				k-=tt[i];
				ans--;
			}
			else
				break;
		}
		cout<<ans<<"\n";
		mp.clear();//多测要清空
		tt.clear();
	}
	return 0;
}
```

---

## 作者：yvbf (赞：0)

![](bilibili:BV1dkruY8ETZ?t=223)

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2057B)

## Statement

给定数组 $a$，定义每次操作为选择区间 $[l,r]$，记 $x = \min_{l\leq i \leq r}{a_i}$，删除区间内所有 $a_i = x$，给你 $k$ 次修改的机会，每次修改某一个位置的数，问最少需要几次操作使得原数组全为 $0$。

## Solution

最初不做任何修改的操作次数定为原数组中不同数的个数，记它为 $cnt_i$，$k$ 次修改等效于抵消掉了一部分 $cnt_i$，如果 $cnt_i > k$ 并不能一次操作消掉区间内所有数。

记 $k$ 能抵消到的最远位置为 $x$，剩余的 $n - x + 1$ 个是必须要操作的，即为答案。

如果 $\sum cnt_i \geq k$，可以修改之后一次操作全部消掉，答案即为 $1$，以上两种情况讨论即可。

## code

[Submission](https://codeforces.com/contest/2057/submission/299771584)

---

