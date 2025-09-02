# Choose the Different Ones!

## 题目描述

给定一个长度为 $n$ 的数组 $\{a\}$、一个长度为 $m$ 的数组 $\{b\}$ 和一个**偶数** $k$，求是否能在 $a$ 和 $b$ 中各选 $\frac{k}{2}$ 个数，使得这些数包括从 $1$ 到 $k$ 的所有整数。

## 说明/提示

对于所有测试点，保证 $1\le T\le10^4$，$1\le n,m\le 2\times10^5$，$2\le k\le 2\times\min(n,m)$，$k$ 是偶数，$1\le a_i,b_j\le10^6$，单测试点所有测试数据中 $n,m$ 之和不超过 $4\times10^5$。

## 样例 #1

### 输入

```
6
6 5 6
2 3 8 5 6 5
1 3 4 10 5
6 5 6
2 3 4 5 6 5
1 3 8 10 3
3 3 4
1 3 5
2 4 6
2 5 4
1 4
7 3 4 4 2
1 4 2
2
6 4 4 2
1 5 2
3
2 2 1 4 3```

### 输出

```
YES
NO
YES
YES
NO
NO```

# 题解

## 作者：littlebug (赞：8)

**形式化题意**：给定一个长度为 $n$ 的数组 $\{a\}$、一个长度为 $m$ 的数组 $\{b\}$ 和一个**偶数** $k$，求是否能在 $a$ 和 $b$ 中各选 $\frac{k}{2}$ 个数，使得这些数包括从 $1$ 到 $k$ 的所有整数。

首先，一个数（从 $1$ 到 $k$）在 $a$ 和 $b$ 中的出现情况共有 $4$ 种：

1. 在 $a$ 和 $b$ 中都没出现。
2. 在 $a$ 中出现，$b$ 中没出现。
3. 在 $a$ 中没出现，$b$ 中出现。
4. 在 $a$ 和 $b$ 中都出现。

分类讨论一下：

- 只要出现了情况 $1$，就一定没有合法答案。
- 在情况 $2,3$ 中，这个数必须选。
- 在情况 $4$ 中，这个数可以在 $a$ 中选，也可以在 $b$ 中选。

我们设必须在 $a$ 中选的数字个数为 $ca$，必须在 $b$ 中选的数字个数为 $cb$，可以在 $a$ 中选也可以在 $b$ 中选的数字个数为 $cn$。那么如果有解，必须满足以下条件：

- $ca$ 和 $cb$ 必须都 $\le\frac{k}{2}$，因为如果其中有一个 $\gt\frac{k}{2}$ 的，那就无法做到在 $a$ 和 $b$ 中各选 $\frac{k}{2}$ 个数了。
- $ca+cb+cn$ 必须 $\ge k$，否则无法做到所选数包括从 $1$ 到 $k$ 的所有整数了。

至于统计是否出现，因为 $1 \le a_i \le 10^6$，所以可以直接开两个 `bitset` 存就行了。

时间复杂度 $O(n+m+k)$。

**code**：
```cpp
#include<iostream>
#include<cstdio>
#include<bitset>
using namespace std;
const int MAXN=2e5+5,MAXA=1e6+5;
int T;
int n,m,k;
bitset <MAXA> a,b;
int ca,cb,cn; //cnt_a cnt_b cnt_unknown 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>T;
	int in;
	bool ok;
	while(T--)
	{
		cin>>n>>m>>k;
		a&=0,b&=0;
		for(int i=1;i<=n;++i)
		{
			cin>>in;
			a[in]=1;
		}
		for(int i=1;i<=m;++i)
		{
			cin>>in;
			b[in]=1;
		}
		ok=1;
		ca=0,cb=0,cn=0;
		for(int i=1;i<=k;++i)
		{
			if((!a[i]) && (!b[i])) //情况1 
			{
				ok=0;
				cout<<"NO\n";
				break;
			}
			if(a[i] ^ b[i])
			{
				if(a[i]) //情况2 
					++ca;
				if(b[i])
					++cb; //情况3 
			}
			else //情况4 
				++cn;
		}
		if(!ok)
			continue;
		if(ca<=k/2 && cb<=k/2 && ca+cb+cn>=k)
			cout<<"YES\n";
		else
			cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：what_can_I_do (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1927C)

开一个桶记录 $a$ 序列和 $b$ 序列当中的数的出现情况。然后从 $1$ 枚举到 $k$，如果有一个数在 $a$ 和 $b$ 中都没出现，就输出 `No`。用两个数来分别统计只有在 $a$ 出现过的数的个数和只有在 $b$ 出现过的数的个数，记为 $c$ 和 $d$。如果 $c$ 或 $d$ 有其中一个数大于 $\frac{k}{2}$，但是题目中要求一个序列只能选择 $\frac{k}{2}$ 个数，那么就说明你一个序列就算选满了 $\frac{k}{2}$ 个数也还是有一些数是只有这一个序列才有的，在另一个序列选不到，那么 $1$ 到 $k$ 当中就有这么一些数是不会被选到的，也输出 `No`，否则输出 `Yes`。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m,k,d;
int a[400010]={0},b[400010]={0};
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cin>>n>>m>>k;
		d=k/2;
		for(register int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			if(x<=k) a[x]++;
		}
		for(register int i=1;i<=m;i++)
		{
			int x;
			scanf("%d",&x);
			if(x<=k) b[x]++;
		}
		int sa=0,sb=0,f=0;
		for(register int i=1;i<=k;i++)
		{
			if(a[i]&&!b[i]) sa++;
			if(!a[i]&&b[i]) sb++;
			if(!a[i]&&!b[i]){f=1;break;}
		}
		if(sa>d||sb>d||f) puts("No");
		else puts("Yes");
		for(register int i=1;i<=k;i++) a[i]=b[i]=0;
	}
	return 0;
}
```

---

## 作者：Lemon_zqp (赞：1)

### 题意
这题题意很简单，就是说确定是否有可能从两个数组中精确地选择 $\frac{k}{2}$ 元素，从而在所选元素中包含从 $1$ 到 $k$ 的每个整数。
### 思路
我们可以把两个数组的数据记起来，然后判断一下，如果 $a$ 数组有一个在 $1$ 到 $k$ 区间范围内的数，但是 $b$ 没有，就在 $acnt$ 这个变量里加 $1$，表示必须在 $a$ 数组里选的数，同理，如果 $b$ 数组有一个在 $1$ 到 $k$ 区间范围内的数，但是 $a$ 没有，就在 $bcnt$ 这个变量里加 $1$，表示必须在 $b$ 数组里选的数，如果两个都有就在 $cnt$ 里加 $1$，表示两个数组都可以选的数有几个，最后还要注意如果两个数组都没有，那么直接输出 `No` 结束。否则判断一下 $acnt$ 和 $bcnt$ 是否都小于等于 $\frac{k}{2}$ 并且 $acnt+bcnt+cnt$ 小于等于 $k$，那么输出 `Yes`，否则输出 `No`。
### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
 
bool a[1000005], b[1000005];
 
signed main()
{
	int t;
	cin >> t;
	while(t--){
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		int n, m, k;
		cin >> n >> m >> k;
		for(int i = 1; i <= n; i++){
			int ai;
			cin >> ai;
			a[ai] = true;
		}
		for(int i = 1; i <= m; i++){
			int bi;
			cin >> bi;
			b[bi] = true;
		}
		int acnt = 0, bcnt = 0, cnt = 0;
		bool if_s = false;
		for(int i = 1; i <= k; i++){
			if(a[i] == true && b[i] == false){
				acnt++;
			}
			if(a[i] == true && b[i] == true){
				cnt++;
			}
			if(a[i] == false && b[i] == true){
				bcnt++;
			}
			if(a[i] == false && b[i] == false){
				cout << "No" << endl;
				if_s = true;
				break;
			}
		}
		if(if_s){
			continue;
		}
		if(acnt <= (k / 2) && bcnt <= (k / 2)){
			if(( + bcnt + cnt) <= k){
				cout << "Yes" << endl;
				continue;
			}
		}
		cout << "No" << endl;
	}
	return 0;
}
```


---

## 作者：2huk (赞：1)

> 给定长度为 $n$ 的数组 $a$ 和长度为 $m$ 的数组 $b$ 和一个偶数 $k$。
>
> 你需要判断能否在 $a, b$ 中分别选择恰好 $\frac k2$ 个元素，使得选出的总共的 $k$ 个元素中包含 $1 \sim k$ 中的所有整数。
>
> 输出 YES 或 NO。
>
> 多测。$t \le 10^4$，$\sum n + m \le 4 \times 10^5$，$2 \le k \le 2 \cdot \min(n, m)$，$k$ 为偶数，$1 \le a_i \le 10^6$。

我们可以将 $1 \sim k$ 中的整数 $i$ 分为 $4$ 类（若大于 $k$ 就忽略它）：

- $i \notin a$ 且 $i \notin b$。显然无解，输出 NO 结束。

- $i \in a$ 且 $i \in b$。那么显然这个数字从哪个数组里面选都可以。先忽略它。
- $i \notin a$ 且 $i \in b$。只能从 $b$ 中选它。
- $i \in a$ 且 $i \notin b$。只能从 $a$ 中选它。

记满足第三个条件的 $i$ 的数量为 $k_0$，满足第四个条件的 $i$ 的数量为 $k_1$。那么有解的充要条件为 $k_0 \le \frac k2$ 且 $k_1 \le \frac k2$。

```cpp
void solve() {
	int n = read(), m = read(), k = read();
	vector<int> a(n), b(m), p0(k + 1), p1(k + 1);
	for (int &t : a) t = read(), t <= k ? ++ p0[t] : 0;
	for (int &t : b) t = read(), t <= k ? ++ p1[t] : 0;
	
	int k0 = 0, k1 = 0;
	fup (i, 1, k) {
		if (!p0[i] && p1[i]) ++ k0;
		if (!p1[i] && p0[i]) ++ k1;
		if (!p0[i] && !p1[i]) return puts("NO"), void();
	}
	
	if (k0 <= k / 2 && k1 <= k / 2) puts("YES");
	else puts("NO");
	return;
}
```



---

## 作者：Special_Tony (赞：0)

# 思路
也是一个贪心题。可以枚举 $1\sim k$ 的所有数，若此数在 $a$ 和 $b$ 中都未出现过，则一定无解了；若只在 $a$ 中出现而不在 $b$ 中出现，则说明不能用 $b$ 里的数字，$totb$ 加 $1$，只在 $b$ 中出现同理。结束时，如果 $totb>\frac k2$ 或 $tota>\frac k2$，则说明无解了。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a[200005], b[200005], i, j, tot1, tot2;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m >> k;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		for (int i = 0; i < m; ++ i)
			cin >> b[i];
		sort (a, a + n), sort (b, b + m);
		n = unique (a, a + n) - a, m = unique (b, b + m) - b;
		a[n] = b[m] = i = j = tot1 = tot2 = 0;
		for (int x = 1; x <= k; ++ x)
			if (a[i] != x)
				if (b[j] != x) {
					cout << "NO\n";
					goto there;
				} else
					++ j, ++ tot1;
			else if (b[j] != x)
				++ i, ++ tot2;
			else
				++ i, ++ j;
		k >>= 1;
		if (tot1 > k || tot2 > k)
			cout << "NO\n";
		else
			cout << "YES\n";
there:
		;
	}
	return 0;
}
```

---

## 作者：BugGod (赞：0)

模拟，橙。

我们可以先列举出 `yes` 的充分必要条件：

1. 在每个数组内，经过去重后（因为一样的数字只选一次），所有小于等于 $k$ 的数字（大了没用）的数量大于等于 $\frac{k}{2}$（小了选不出来）。
1. 筛选后（去重和去掉大于 $k$ 的数）两个数组的并集包含 $1\sim k$ 的所有数（不包含就无法形成排列）。

为什么充分？因为只要有 $1\sim k$ 这些数字，并且每个数组都能选出 $\frac{k}{2}$ 个数字，那么一定有办法：不妨设筛选后集合为 $a,b$ 且 $|a|\ge |b|$，那么我们先选出 $b$ 中所有数字，如果 $a$ 中不能选出剩余的数字，设剩余没选的有一个数为 $y$，那么显然 $y\notin a,y\notin b,y\in \lbrace x|1\le x\le k,x\in \mathbb{N}_+\rbrace$，所以 $y\notin a\cup b$。但由于 $a\cup b=\lbrace x|1\le x\le k,x\in \mathbb{N}_+\rbrace$，所以矛盾，所以不存在 $y$ 没有选。

CODE：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define mp make_pair
#define fi first
#define se second
void IOS()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}
void file(string file_name)
{
	freopen((file_name+".in").c_str(),"r",stdin);
	freopen((file_name+".out").c_str(),"w",stdout);
}
int t,n,m,k,a[200010],b[200010];
void solve()
{
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=m;i++)cin>>b[i];
	sort(a+1,a+1+n);
	sort(b+1,b+1+m);
	//cout<<n<<' '<<m<<'\n';
	n=unique(a+1,a+1+n)-a-1;
	m=unique(b+1,b+1+m)-b-1;
//	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
//	cout<<'\n';
//	for(int i=1;i<=m;i++)cout<<b[i]<<' ';
//	cout<<'\n';
	int nn=n,mm=m;
	//cout<<n<<' '<<m<<'\n';
	for(int i=1;i<=nn;i++)if(a[i]>k)n--;
	for(int i=1;i<=mm;i++)if(b[i]>k)m--;
	//if(b[mm]>k)puts("AKIOI");
	//cout<<m<<'\n';
	if(n<k/2)
	{
		cout<<"no\n";
		return ;
	}
	if(m<k/2)
	{
		cout<<"no\n";
		return ;
	}
	//cout<<n<<' '<<m<<'\n';
	map<int,int>ma;
	for(int i=1;i<=n;i++)ma[a[i]]++;
	for(int i=1;i<=m;i++)ma[b[i]]++;
	for(int i=1;i<=k;i++)
	{
		if(!ma[i])
		{
			cout<<"no\n";
			return ;
		}
	}
	cout<<"yes\n";
}
signed main()
{
	//IOS();
	//file("");
	cin>>t;
	while(t--)solve();
	return 0;
}

```

---

## 作者：qingyun111 (赞：0)

## 传送门：

[洛谷 CF1927C](https://www.luogu.com.cn/problem/CF1927C)

[CF1927C](https://codeforces.com/contest/1927/problem/C)

## 题目大意：

分别给你两个数组，让你在其中找到 $1$ 到 $k$ 的数。其中，每个数组你只能找 $\frac{k}{2}$ 个数。 

## 分析：

看样例我们可以看到，在同一个数组，都会有相同数字或者是大于 $k$ 的情况，但我们只需要找 $1$ 到 $k$ 的数，所以在同一个数组中，**可以进行去重与筛选**。

每一个数组只有 $\frac{k}{2}$ 个机会，而两个数组都有可能有相同的数字（如第一个样例）导致我们需要进行特判，去看哪边数组剩下的机会多，然后再选上共同有的数字。

这么一看，就是一个很明显的暴力贪心。~~我一开始就是这么做，用两个数组进行记录出现次数进行特判，但我爆了。~~ 

**那有没有更好的办法呢？有。**

思路拓开，我们只需要记录哪些我们需要的数字出现了，存入，然后进行判断每个数组符合的数量是否满足 $\ge \frac{k}{2}$ 个即可。至于两个都有的数字？不用额外判断，下边代码我将详细描述。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
namespace fastio{
    struct reader{
        template<typename T>reader&operator>>(T&x){
            char c=getchar();short f=1;
            while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}
            x=0;while(c>='0'&&c<='9'){
                x=(x<<1)+(x<<3)+(c^48);
                c=getchar();
            }x*=f;return *this;
        }
    }cin;
    struct writer{
        template<typename T>writer&operator<<(T x){
            if(x==0)return putchar('0'),*this;
            if(x<0)putchar('-'),x=-x;
            static int sta[45];int top=0;
            while(x)sta[++top]=x%10,x/=10;
            while(top)putchar(sta[top]+'0'),--top;
            return*this;
        }
    }cout;
};
#define vll vector<ll>
#define pll pair<ll,ll>
#define pii pair<int,int>
#define vpll vector<pll>
#define endl '\n'
#define yes cout<<"Yes"<<endl;
#define no cout<<"No"<<endl;
const int N=100010;
ll num[N];

void solve() {
    ll  n,m,k,ans,a,b,c,d,e,boll,tem,val,x,y,z,sum,sum1,sum2,maxx,minn,temp1,temp2;
    ans=sum=tem=val=sum1=sum2=temp1=temp2=0,maxx=-1e18,minn=1e18;
    a=b=c=d=x=y=0;
    cin>>n>>m>>k;
    set<ll>st1,st2,st;//set可以自动去重
    for(int i=1;i<=n;i++){
        cin>>x;
        if(x<=k){//符合 1~k 的，都进行存入
            st1.insert(x);
        }
    }
    for(int i=1;i<=m;i++){
        cin>>y;
        if(y<=k){//同上
            st2.insert(y);
        }
    }
    if(st1.size()<(k/2)||st2.size()<(k/2)){//如果一个数组中符合的个数都不够，
        no;                                //怎么可能会 yes。
        return;
    }else{
        for(auto i:st1)st.insert(i);//关键：因为两边数组符合的个数都满足 k/2，
        for(auto j:st2)st.insert(j);//而set自带去重，所以两个数组都有的数字只会用一次
        for(int i=1;i<=k;i++){//上边的if已经进行了一次特判，去重后仍然满足至少有 k/2 个，那么一定不会让一个数组进行大于 k/2 次提取操作。
            if(st.find(i)==st.end()){//遍历 1~k，这个if就是如果没有找到的情况。
                no;
                return;
            }
        }
    }
    yes;
    return;
}
int main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int t=1;
    cin>>t;
    while(t--) {
        solve();
    }
    
    return 0;
}
```



---

## 作者：Weekoder (赞：0)

# CF1927C Choose the Different Ones! 题解

## 题意简述

给定两个数列 $a$ 和 $b$，还有一个偶数 $k$，需要从两个数列中分别选取 $\frac{k}{2}$ 个数，使得选取的数能刚好组成 $1,2,3,\dots,k$。

## 分析

首先可以将 $a,b$ 两个数列合并，并用一个标记 $f$ 来记录属于哪个数列，$f\in\{0,1\}$。我们用结构体存储，并将合并的数列排序。

接着，我们可以用一个数组 $g$ 来存储每个 $1$ 到 $k$ 的数字的情况。对于数字 $i$，若没有 $i$，则 $g_i$ 为 $-1$，若有 $i$，则 $g_i$ 为 $i$ 的 $f$ 值。若 $i$ 在两个数列中都出现了，即 $i$ 的 $f$ 值为 $0$ 或 $1$，则 $g_i$ 的值为 $2$。$g$ 数组的获取见代码。

有了这个 $g$ 数组，我们就可以很方便地判断是否能选出 $1$ 到 $k$ 的所有数了。只要在 $g$ 中，有任意一个数为 $-1$，则某个数根本没有，输出 $\texttt{NO}$。如果全都不是 $-1$，就说明所有数都出现了，那么我们现在要做的就是让 $f$ 值为 $0$ 的数和 $f$ 值为 $1$ 的数的数量相等。如果发现不相等，我们就可以用 $g_i$ 为 $2$，就是既可以为 $1$，也可以为 $0$ 的数来填补。我们计算出两种数之间的差 $num$，如果 $g_i$ 为 $2$ 的数的数量 $cnt<num$，那就不够填补，输出 $\texttt{NO}$。（赛时代码加了一些无用的奇偶判断，其实 $k$ 为偶数就不用判断）最后输出 $\texttt{YES}$。

这是赛时代码。

# $\text{Code:}$

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 4e5 + 5;

struct node {
    int val, f;
    bool operator<(const node &x)const {
        return val < x.val;
    }
}a[N];

int T, g[N];

int main() {
    cin >> T;
    while (T --) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 1; i <= n + m; i++) {
            cin >> a[i].val;
            if (i <= n) a[i].f = 0;
            else a[i].f = 1;
        }
        sort(a + 1, a + 1 + n + m);
        memset(g, -1, sizeof g);
        bool flag = 0, NO_flag = 0;
        int flag_id;
//        for (int i = 1; i <= n + m; i++) cout << a[i].val << " " << a[i].f << " ";
//        cout << "\n";
        for (int i = 1; i <= n + m; i++) {
            if (a[i].val == k) flag = 1, flag_id = i;
            if (i > 1 && a[i].val != a[i - 1].val) {
                if (a[i].val - a[i - 1].val > 1 && a[i].val <= k) {
                    cout << "NO\n";
                    NO_flag = 1;
                    break;
                }
                if (g[a[i - 1].val] == -1 && a[i].val - a[i - 1].val <= 1)
                    g[a[i - 1].val] = a[i - 1].f;
            }
            if (i > 1 && a[i].val == a[i - 1].val) {
                if (a[i].f != a[i - 1].f) g[a[i].val] = 2;
                else g[a[i].val] = max(g[a[i].val], a[i].f);
            }
        }
        if (NO_flag) continue;
        if (g[k] == -1 && flag) g[k] = a[flag_id].f;
//        for (int i = 1; i <= k; i++) cout << g[i] << " ";
//        cout << "\n";
        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        NO_flag = 0;
        for (int i = 1; i <= k; i++) {
            if (!g[i]) cnt0++;
            if (g[i] == 1) cnt1++;
            if (g[i] == 2) cnt2++;
            if (g[i] == -1) {
                cout << "NO\n";
                NO_flag = 1;
                break;
            }
        }
        if (NO_flag) continue;
        if (cnt0 != cnt1) {
            int num = abs(cnt0 - cnt1);
            if (cnt2 < num) {
                cout << "NO\n";
                continue;
            }
            cnt2 -= num;
            if (cnt2 & 1) {
                cout << "NO\n";
                continue;
            }
        }
        cout << "YES\n";
    }
    return 0;
}
```

---

## 作者：atomic_int (赞：0)

模拟。$1 \sim k$ 如果 $a,b$ 都没有，输出 `NO`；如果 $a$ 选不出 $\frac{k}{2}$ 个，输出 `NO`，否则记 $a$ 中与 $1 \sim k$ 的交集为 $p$，此时 $b$ 中应该有 $t$ 个元素满足 $\in [1,k]$ 且 $t \ge \mathrm{size}(p)-\frac{k}{2}$。

```cpp
void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  vector<int> a(n + 1), b(m + 1);
  map<int, bool> mp1, mp2;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    mp1[a[i]] = true;
  }
  for (int i = 1; i <= m; i++) {
    cin >> b[i];
    mp2[b[i]] = true;
  }
  vector<int> p;
  for (int i = 1; i <= k; i++) {
    if (mp1[i]) {
      p.push_back(i);
    }
    if (!mp1[i] && !mp2[i]) {
      cout << "NO\n";
      return;
    }
  }
  if (p.empty() || p.size() < k / 2) {
    cout << "NO\n";
    return;
  }
  int cnt = 0;
  for (auto i : p) {
    if (mp2[i]) cnt++;
  }
  if (cnt >= p.size() - k / 2) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
}
```

---

## 作者：vorDeal (赞：0)

好题。

考虑开两个桶 $abk$ 和 $bbk$，分别记录 $a$ 与 $b$ 中每个数是否出现。遍历 $1 \sim k$，对于每个自然数，考察其出现情况。

1. 均未出现。
2. 仅在 $a$ 中出现。
3. 仅在 $b$ 中出现。
4. 均出现了。

若出现情况 1，则定然无方案。

若情况 2、3 之出现均小于等于 $\frac{k}{2}$ 次，则存在方案。

否则也无方案。

~~数据千万条，清空第一条。多测不清空，爆零两行泪。~~

**AC Code：**
```cpp
#include <bits/stdc++.h>
using namespace std;

int t, n, m, k, p, q, a, b;
bool abk[1000005], bbk[1000005], f;

int main()
{
    cin >> t;
    while (t--)
    {
        memset(abk, 0, sizeof(abk));
        memset(bbk, 0, sizeof(bbk));
        p = q = f = 0;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++)
            cin >> a, abk[a] = true;
        for (int i = 0; i < m; i++)
            cin >> b, bbk[b] = true;
        for (int i = 1; i <= k; i++)
        {
            if (abk[i] && (!bbk[i]))
                p++;
            if ((!abk[i]) && bbk[i])
                q++;
            if ((!abk[i]) && (!bbk[i]))
                f = 1;
        }
        if ((p << 1) <= k && (q << 1) <= k && (!f))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
```

---

## 作者：Lele_Programmer (赞：0)

# CF1927C 题解

题目大致意思：从 $a$ 数组中取出刚刚好 $\frac{k}{2}$ 个数，从 $b$ 数组中取出刚刚好 $\frac{k}{2}$ 个数，使得取出的 $k$ 个数，包含 $1$ 到 $k$ 的所有整数。

对于 $1$ 到 $k$ 的所有整数 $i$，分情况讨论：

1. 若 $i$ 在两个数组中均不存在，则无解。
2. 若 $i$ 只出现在其中一个数组，则必须从这个数组中将 $i$ 取出。
3. 若 $i$ 在两个数组中均存在，则先待定。

将 $a$ 数组中必须取出的整数个数记为 $cnta$ ,将 $b$ 数组中必须取出的整数个数记为 $cntb$，将 $a$ 与 $b$ 皆可取出的整数个数记为 $both$。

如果 $cnta$ 或 $cntb$ 其中一者大于 $\frac{k}{2}$ 了，或是已经出现过上面 3 个情况中的第一种，则无解。

如果 $both$ 能够刚好分成两份，使得 $a$ 和 $b$ 分别加上这两份之后都等于 $\frac{k}{2}$，则有解，否则无解。

设置两个桶，分别表示该数能否在 $a$ 和 $b$ 中取得。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=400005;
const int M=400005;

int T,n,m,k;
int a[N],b[M];
bool fa[N],fb[M]; // 桶

int main() {
    scanf("%d",&T);
    while (T--) {
        scanf("%d %d %d",&n,&m,&k);
        for (int i=1;i<=n;++i) scanf("%d",a+i);
        for (int i=1;i<=m;++i) scanf("%d",b+i);
        memset(fa,0,sizeof(fa)); // 初始化两个桶
        memset(fb,0,sizeof(fb));
        for (int i=1;i<=n;++i) {
            if (a[i]<=k) {
                fa[a[i]]=true; // 标记数字的出现情况
            }
        }
        for (int i=1;i<=m;++i) {
            if (b[i]<=k) {
                fb[b[i]]=true; // 标记数字的出现情况
            }
        }
        int cnta=0,cntb=0,both=0; // 记录 a 必须取出的个数，b 必须取出的个数，以及皆可取出的个数
        bool ok=true;
        for (int i=1;i<=k;++i) {
            if (fa[i] && !fb[i]) cnta++;
            else if (fb[i] && !fa[i]) cntb++;
            else if (fa[i] && fb[i]) both++;
            else {
                ok=false;
                break;
            }
        }
        if (cnta>k/2 || cntb>k/2 || !ok) {
            puts("NO");
            continue;
        }
        if (cntb+(both-(k/2-cnta))==k/2) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
```

---

## 作者：bryce (赞：0)

## 思路分析
开两个桶数组，一个存 $a$ 数组中有没有元素出现，另一个存 $b$ 数组中有没有元素出现。

考虑贪心，$i$ 从 $1$ 到 $k$ 循环，如果其中一个数组中有 $i$，另一个没有 $i$，肯定选择有的那个，两个都没有直接输出 NO，把所有以上两种情况都考虑完之后，再循环一遍，如果两个数组中都有这个元素，只要选的个数没有 $\frac{k}{2}$ 个，随便选哪个数组都行。
## 代码
```cpp
#include<iostream>
#include<cstring>

using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e5 + 10, M = 1e6 + 10;
int T, n, m, k;
int cnt1[M], cnt2[M], s1, s2;

int main(){
	T = read();
	while (T--){
		n = read(), m = read(), k = read(), s1 = 0, s2 = 0;
		bool f = 0;
		for (int i = 1; i <= n; i++){
			int x = read();
			if (x <= k) cnt1[x]++;
		}
		for (int i = 1; i <= m; i++){
			int x = read();
			if (x <= k) cnt2[x]++;
		}
		for (int i = 1; i <= k; i++){
			if (!cnt1[i] && !cnt2[i]){
				cout << "NO\n";
				f = 1;
				break;
			}
			if (cnt1[i] && !cnt2[i]){
				s1++;
				if (s1 > k / 2){
					f = 1;
					cout << "NO\n";
					break;
				}
			}
			if (!cnt1[i] && cnt2[i]){
				s2++;
				if (s2 > k / 2){
					f = 1;
					cout << "NO\n";
					break;
				}
			}
		}
		for (int i = 1; i <= k; i++){
			if (cnt1[i] && cnt2[i]){
				if (s1 < k / 2){
					s1++;
					continue;
				}else if (s2 < k / 2){
					s2++;
					continue;
				}else{
					f = 1;
					cout << "NO\n";
					break;
				}
			}
		}
		if (!f) cout << "YES\n";
		for (int i = 1; i <= k; i++){
			cnt1[i] = cnt2[i] = 0;
		}
	}
	return 0;
}
```


---

## 作者：yyrwlj (赞：0)

## 题意简述

给定两个长度分别为 $n$ 和 $m$ 的序列，分别从两个序列中取出 $\frac{k}{2}$ 个数，是否能使取出的数恰好排列成 $1$ 到 $k$。

## 思路

对于 $1$ 到 $k$ 的每一个数，都有三种情况：

1. 两个序列都没有。

2. 两个序列都有。

3. 只有一个序列有。

对于第一种情况，那就肯定无解了。

对于第二种情况，就后考虑，随机应变。

对于第三种情况，因为每个序列要取出 $\frac{k}{2}$ 个数，那么如果必须某个序列的数大于 $\frac{k}{2}$ 个，那么就无解，否则有解。

## Code

```cpp
const int N = 200005;
typedef long long LL;
typedef pair<int, int> PII;
int a[N], b[N];
bool f[N * 2][2];
void work()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    for (int i=1;i<=m;i++)
        scanf("%d", &b[i]);
    for (int i=1;i<=k;i++)
        f[i][0] = f[i][1] = 0;
    for (int i=1;i<=n;i++)
        if (a[i] <= k)
            f[a[i]][0] = true;
    for (int i=1;i<=m;i++)
        if (b[i] <= k)
            f[b[i]][1] = true;
    int c1 = 0, c2 = 0, c3 = 0;
    for (int i=1;i<=k;i++)
    {
        if (f[i][0] && f[i][1])
            c3 ++;
        else if (f[i][0])
            c1 ++;
        else if (f[i][1])
            c2 ++;
        else
        {
            puts("NO");
            return;
        }
    }
    int k2 = k / 2;
    if (c1 > k2 || c2 > k2)
        puts("NO");
    else
        puts("YES");
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        work();
    return 0;
}
```

---

## 作者：ZettaByte (赞：0)

# CF1927C Choose the Different Ones! 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1927C)

### 题意

给定一个由 $n$ 个整数组成的数组 $a$ ，一个由 $m$ 个整数组成的数组 $b$ 和一个偶数 $k$ 。

你的任务是确定是否有可能从这两个数组中各选择恰好 $\frac{k}{2}$ 个元素，使得所选元素中包括从 $1$ 到 $k$ 的每一个整数。

### 解法

首先统计 $1\sim k$ 的各个元素是否在 $a$ 和 $b$ 里出现过，用 $mpa$ 和 $mpb$ 保存。

- 如果只在 $a$ 数组里出现过且没有在 $b$ 数组里出现过的数数量超过 $\frac{k}{2}$ ，即 $a$ 数组需要取的数数量超过 $\frac{k}{2}$ ，那么输出 `NO` ；

- 如果只在 $b$ 数组里出现过且没有在 $a$ 数组里出现过的数数量超过 $\frac{k}{2}$ ，即 $b$ 数组需要取的数数量超过 $\frac{k}{2}$ ，那么也输出 `NO` ；

- 如果有 $a$ 数组和 $b$ 数组内都没出现过的数，那么还是输出 `NO` ；

- 否则输出 `YES` 。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
map<int, int> mpa, mpb;
 
int main()
{
	int T; scanf("%d", &T);
	while (T--)
	{
		mpa.clear(), mpb.clear(); //多测不清空，爆零两行泪
		int n, m, k, cnta = 0, cntb = 0, cntab = 0, flag = 1; scanf("%d%d%d", &n, &m, &k);
		for (int i = 1, x; i <= n; i++) scanf("%d", &x), mpa[x] = 1;
		for (int i = 1, x; i <= m; i++) scanf("%d", &x), mpb[x] = 1;
		for (int i = 1; i <= k; i++)
			if (mpa[i] && !mpb[i]) cnta++;
			else if (mpb[i] && !mpa[i]) cntb++;
			else if (mpa[i] && mpb[i]) cntab++;
			else { flag = 0; break; }
		if (!flag || cnta > k / 2 || cntb > k / 2 || cnta + cntb + cntab < k) puts("NO"); //判断不行的情况
		else puts("YES"); //否则输出YES
	}
	return 0;
}
```

---

## 作者：Harrylzh (赞：0)

题意：给出有 $n$ 个元素的数组 $a$ 和有 $m$ 个元素的数组 $b$，以及偶数 $k$。回答是否能刚好从 $a$ 和 $b$ 中各取出 $\frac{k}{2}$ 个元素，构成一个 $1$ 到 $k$ 的排列。数据范围保证不存在元素不够取的情况。

思路：

1. 如果 $a$ 和 $b$ 中都没有 $1$ 到 $k$ 中某个元素，则一定不满足条件；

2. 如果 $a$ 或 $b$ 中的 $1$ 到 $k$ 中的元素不足 $\frac{k}{2}$ 个，则一定不满足条件。

排除以上两种情况，剩下的就是满足条件的。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,m,k;
int a[1000000+5];
int b[1000000+5];
bool boxa[1000000+5];//记录某个值是否在a中出现过
bool boxb[1000000+5];//同理
int main()
{
    cin>>t;
    while(t--)
    {
    	bool flag=1;//记录是否已被排除
    	int suma=0,sumb=0;
    	memset(boxa,0,sizeof(boxa));
    	memset(boxb,0,sizeof(boxb));
    	scanf("%lld%lld%lld",&n,&m,&k);
    	for(int i=1;i<=n;i++) scanf("%d",&a[i]),boxa[a[i]]=1;
    	for(int i=1;i<=m;i++) scanf("%d",&b[i]),boxb[b[i]]=1;
    	for(int i=1;i<=k;i++)
    	{
    		suma+=boxa[i],sumb+=boxb[i];
    		if(!boxa[i]&&!boxb[i])
    		{
    			flag=0;
    			break;
			}
		}
		if(suma<k/2||sumb<k/2) flag=0;
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
    return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

一道简单的思维题，感觉还是比较好找突破口的。

先读入，用两个桶记录某个数是否存在。

然后对于每个 $1\sim k$ 的数值遍历一遍：

- 对于两边都没有的，就不用多废话了，输出 `NO`；

- 对于其中一边有的，把有的那边计数器加 $1$；

- 对于两边都有的，先不管。

遍历完之后检查，如果两个计数器有一个大于 $\dfrac{k}{2}$，则说明必须要在这个数里抽取大于 $\dfrac{k}{2}$ 个数才能满足条件，输出 `NO`；

如果都小于等于 $\dfrac{k}{2}$，则可以输出 `YES`（此时剩下的没有被统计进去的数可以任意的放在两边，对正确性没有任何影响）。

同时注意多测清空以及清空方式，都是一些小细节但处理不好影响还是蛮大的。 

代码：

```
#include<bits/stdc++.h>
using namespace std;
bool fa[1000005],fb[1000005];
int a[1000005],b[1000005];
int main(){
	int t;
	cin>>t;
	int lastn=0,lastm=0;
	while(t--){
		for(int i=1;i<=lastn;i++){//清空
			fa[a[i]]=0;
		}
		for(int i=1;i<=lastm;i++){
			fb[b[i]]=0;
		}
		int n,m,k;
		cin>>n>>m>>k;
		lastn=n;
		lastm=m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			fa[a[i]]=1;//桶
		}
		for(int i=1;i<=m;i++){
			cin>>b[i];
			fb[b[i]]=1;
		}
		int cnta=0,cntb=0,fl=1;
		for(int i=k;i>=1;i--){//分讨
			if(fa[i]&&fb[i])continue;
			if(!fa[i]&&!fb[i]){
				fl=0;
				break;
			}
			if(fa[i])cnta++;
			if(fb[i])cntb++;
		}
		if(!fl||cnta>k/2||cntb>k/2){
			cout<<"NO\n";
			continue;
		}
		cout<<"YES\n";
	}
	return 0;
}

```


---

## 作者：aeiouaoeiu (赞：0)

对于一个 $1$ 到 $k$ 的数 $x$，有三种可能的情况：

- $x$ 既不在 $a$ 中，也不在 $b$ 中：此时无法满足条件，直接输出 ``No``。

- $x$ 即在 $a$ 中，也在 $b$ 中：此时一定满足条件。

- $x$ 只在 $a$ 中或只在 $b$ 中：此时记录存在这种情况的 $x$ 的数量。若将只在 $a$ 中的 $x$ 的数量记为 $p$，当 $p>\frac{k}{2}$  时，由于数组 $a$ 只能取 $\frac{k}{2}$ 个数，此时必然有 $p-\frac{k}{2}$ 个 $x$ 是取不到的，故无法满足条件，$b$ 同理。

把 $a$ 和 $b$ 中在 $1$ 到 $k$ 之间的数存进桶中扫一遍即可。[Link](https://codeforces.com/contest/1927/submission/245128164)（注意代码中的 $c3$ 是无用的）。

---

