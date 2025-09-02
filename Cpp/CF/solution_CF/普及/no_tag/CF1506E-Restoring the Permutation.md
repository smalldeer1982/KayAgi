# Restoring the Permutation

## 题目描述

A permutation is a sequence of $ n $ integers from $ 1 $ to $ n $ , in which all numbers occur exactly once. For example, $ [1] $ , $ [3, 5, 2, 1, 4] $ , $ [1, 3, 2] $ are permutations, and $ [2, 3, 2] $ , $ [4, 3, 1] $ , $ [0] $ are not.

Polycarp was presented with a permutation $ p $ of numbers from $ 1 $ to $ n $ . However, when Polycarp came home, he noticed that in his pocket, the permutation $ p $ had turned into an array $ q $ according to the following rule:

- $ q_i = \max(p_1, p_2, \ldots, p_i) $ .

Now Polycarp wondered what lexicographically minimal and lexicographically maximal permutations could be presented to him.

An array $ a $ of length $ n $ is lexicographically smaller than an array $ b $ of length $ n $ if there is an index $ i $ ( $ 1 \le i \le n $ ) such that the first $ i-1 $ elements of arrays $ a $ and $ b $ are the same, and the $ i $ -th element of the array $ a $ is less than the $ i $ -th element of the array $ b $ . For example, the array $ a=[1, 3, 2, 3] $ is lexicographically smaller than the array $ b=[1, 3, 4, 2] $ .

For example, if $ n=7 $ and $ p=[3, 2, 4, 1, 7, 5, 6] $ , then $ q=[3, 3, 4, 4, 7, 7, 7] $ and the following permutations could have been as $ p $ initially:

- $ [3, 1, 4, 2, 7, 5, 6] $ (lexicographically minimal permutation);
- $ [3, 1, 4, 2, 7, 6, 5] $ ;
- $ [3, 2, 4, 1, 7, 5, 6] $ ;
- $ [3, 2, 4, 1, 7, 6, 5] $ (lexicographically maximum permutation).

For a given array $ q $ , find the lexicographically minimal and lexicographically maximal permutations that could have been originally presented to Polycarp.

## 样例 #1

### 输入

```
4
7
3 3 4 4 7 7 7
4
1 2 3 4
7
3 4 5 5 5 7 7
1
1```

### 输出

```
3 1 4 2 7 5 6 
3 2 4 1 7 6 5 
1 2 3 4 
1 2 3 4 
3 4 5 1 2 7 6 
3 4 5 2 1 7 6 
1 
1```

# 题解

## 作者：Cutest_Junior (赞：1)

## 题解 CF1506E 【Restoring the Permutation】

### 题意

+ 给出一个长度为 $n$ 的数组 $q$；
+ 求前缀最大值为该数组的字典序最大和最小的排列 $a$ 和 $b$；
+ 多组数据，$1\le q_i\le n\le2\times10^5$，$q_i\le q_{i+1}$。

### 做法

不妨设 $q_0=0$，则对于任何 $i$ 满足 $q_i>q_{i-1}$，$a_i=b_i=q_i$。

没有 $q_i<q_{i-1}$ 的情况。

对于 $q_i=q_{i-1}$ 的情况，
+ 为使字典序最大，$a_i$ 选最大的不超过 $q_i$ 的没选过的数，可以用一个栈维护；
+ 为使字典序最小，$b_i$ 选最小的没选过的数，直接用一个用一个 vis 数组标记是否选过，再用一个指针存最小的没选过的数。

### 代码

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 2e5 + 5;

int a[N];
bool b[N];

struct stack {
	int s[N], t;
	
	stack() {
		memset(s, 0, sizeof s);
		t = 0;
	}
	
	void push(int x) {
		s[t] = x;
		++t;
	}
	
	void pop() {
		--t;
	}
	
	int top() {
		return s[t - 1];
	}
};

void solve() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	memset(b, 0, sizeof b);
	int minn = 1;
	for (int i = 1; i <= n; ++i) {
		if (!b[a[i]]) {
			printf("%d ", a[i]);
			b[a[i]] = 1;
		}
		else {
			while (b[minn]) {
				++minn;
			}
			printf("%d ", minn);
			b[minn] = 1;
		}
	}
	printf("\n");
	stack s;
	a[0] = 0;
	for (int i = 1; i <= n; ++i) {
		if (a[i] != a[i - 1]) {
			printf("%d ", a[i]);
			b[a[i]] = 1;
			for (int j = a[i - 1] + 1; j < a[i]; ++j) {
				s.push(j);
			}
		}
		else {
			printf("%d ", s.top());
			s.pop();
		}
	}
	printf("\n");
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}
```

---

## 作者：wmrqwq (赞：0)

duel 到的。

# 题目链接

[CF1506E](https://www.luogu.com.cn/problem/CF1506E)

# 解题思路

有一个显然的性质就是这个序列的前缀最大值是单调不降的。

于是我们就可以对于每个位置考虑还可以填哪些数，对于字典序最小的肯定填当时可填的最小数字，对于字典序最大的肯定填当时可填的最大数字，因为你可以通过填一个数的方式来满足要求，因此该构造方案一定不劣。

使用优先队列维护上述过程即可。时间复杂度 $O(n \log n)$。

# 参考代码

```cpp
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll t;
ll n;
ll a[200010],vis[200010],ma,L,R;
maxqueue q;
void solve()
{
	while(!q.empty())
		q.pop();
	cin>>n;
	forl(i,1,n)
		cin>>a[i];
	ma=0,L=1;
	forl(i,1,n)
		vis[i]=0;
	forl(i,1,n)
	{
		if(ma!=a[i])
		{
			cout<<a[i]<<' ';
			vis[a[i]]=1;
			ma=a[i];
			continue;
		}
		else
		{
			while(vis[L])
				L++;
			cout<<L<<' ';
			vis[L]=1;
		}
	}
	cout<<endl;
	ma=0,R=n;
	forl(i,1,n)
		vis[i]=0;
	forl(i,1,n)
	{
		if(ma!=a[i])
		{
			cout<<a[i]<<' ';
			vis[a[i]]=1;
			forl(j,ma+1,a[i])
				if(!vis[j])
					q.push(j);
			ma=a[i];
			continue;
		}
		else
		{
			while(!q.empty())
			{
				ll num=q.top();
				q.pop();
				if(!vis[num])
				{
					cout<<num<<' ';
					vis[num]=1;
					break;
				}		
			}		
		}
	}
	cout<<endl;
}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```

---

## 作者：hswfwkj_ (赞：0)

[$Link$](https://www.luogu.com.cn/problem/CF1506E)
## 题意简述：
给定一个长度为 $n$ 的数组 $q$，要求你给出满足如下条件的长度为 $n$ 的序列 $p$：

- 该序列是 $1-n$ 的一个排列
- $q_i=\max(p_1,p_2,\cdot\cdot\cdot,p_i)$

分别输出满足条件序列的最小字典序序列和最大字典序序列。

## 思路简介：

首先对于最小字典序，可以定义一个指针，开始指着 $1$，然后如果 $q_i>q_{i-1}$ 直接输出 $q_i$，否则将指针跳到目前能选的最小的数，然后输出。

对于最大字典序，输出 $q_i$ 的情况和上面一样，否则，我们就在 $1-q_i$ 的数里选一个能选的最大的，输出就行。这里可以用链表来记录，每个点对应的比它小的能选的最大的数，就是它的后继。每次选数时更新一下就行。

时间复杂度 $O(n)$。

贴上代码，更易于理解：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=2e5+5;
int T,n,d[N],q[N],nxt[N],last[N];;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		memset(d,0,sizeof(d));
		int p=1;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>q[i];
		for(int i=1;i<=n;i++)
		{
			if(!d[q[i]])
			{
				d[q[i]]=1;
				cout<<q[i]<<' ';
			}
			else
			{
				while(d[p])p++;
				d[p]=1;
				cout<<p++<<' ';//只需要一个指针，最多只会移动 n 次，不用担心时间复杂度
			}
		}
		cout<<'\n';
		memset(d,0,sizeof(d));
		for(int i=1;i<=n;i++)
			nxt[i]=i-1,last[i]=i+1;
		for(int i=1;i<=n;i++)
		{
			if(!d[q[i]])
			{
				cout<<q[i]<<' ';
				d[q[i]]=1;
				nxt[last[q[i]]]=nxt[q[i]];
				last[nxt[q[i]]]=last[q[i]];
			}
			else
			{
				cout<<nxt[q[i]]<<' ';//用链表来进行更新
				nxt[last[nxt[q[i]]]]=nxt[nxt[q[i]]];
				last[nxt[nxt[q[i]]]]=last[nxt[q[i]]];
				nxt[q[i]]=nxt[nxt[q[i]]];
			}
		}
		cout<<'\n';
	}
	return 0;
}
```

---

## 作者：Marxistdzy (赞：0)

### 题意简述
给定一个长度为 $n$ 的序列 $q$，生成的排列 $a$，满足 $\forall a_i \in [1, n]$ 有 $q_i = \max_{j = 1}^{i} a[j] $，求字典序最小和最大的排列。

### 解题方法
定义 vector 可变数组来算就可以啦。
- 为使字典序最大，$a_i$ 选最大的不超过 $q_i$ 的没选过的数。
- 为使字典序最小，$b_i$ 选最小的没选过的数，用一个指针存最小的没选过的数。
- 可选的数用 set 维护。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define vc vector
#define int long long
#define forn(i, n) for (int i = 0; i < n; ++i)
//为了节省输入时间

void solve () {
    int n;
    cin >> n;
    vc <int> p(n);
    forn (i, n)
        cin >> p[i];
    set <int> s;
    forn (i, n)
        s.insert(i + 1);
    forn (i, n) {
        if (i == 0 || p[i] != p[i - 1]) {
            cout << p[i] << ' ';
            s.erase(p[i]);
        } else {
            cout << *s.begin() << ' ';
            s.erase(s.begin());
        }
    }
    cout << '\n';
    forn (i, n)
        s.insert(i + 1);
    forn (i, n) {
        auto x = prev(s.upper_bound(p[i]));
        cout << *x << ' ';
        s.erase(x);
    }
    cout << '\n';
}

signed main() {
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}
```
如有不当之处，请各位大佬指正！

---

