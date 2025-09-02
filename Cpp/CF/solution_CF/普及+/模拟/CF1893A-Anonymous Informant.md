# Anonymous Informant

## 题目描述

You are given an array $ b_1, b_2, \ldots, b_n $ .

An anonymous informant has told you that the array $ b $ was obtained as follows: initially, there existed an array $ a_1, a_2, \ldots, a_n $ , after which the following two-component operation was performed $ k $ times:

1. A fixed point $ ^{\dagger} $ $ x $ of the array $ a $ was chosen.
2. Then, the array $ a $ was cyclically shifted to the left $ ^{\ddagger} $ exactly $ x $ times.

As a result of $ k $ such operations, the array $ b_1, b_2, \ldots, b_n $ was obtained. You want to check if the words of the anonymous informant can be true or if they are guaranteed to be false.

 $ ^{\dagger} $ A number $ x $ is called a fixed point of the array $ a_1, a_2, \ldots, a_n $ if $ 1 \leq x \leq n $ and $ a_x = x $ .

 $ ^{\ddagger} $ A cyclic left shift of the array $ a_1, a_2, \ldots, a_n $ is the array $ a_2, \ldots, a_n, a_1 $ .

## 说明/提示

In the first test case, the array $ a $ could be equal to $ [3, 2, 3, 4, 3] $ . In the first operation, a fixed point $ x = 2 $ was chosen, and after $ 2 $ left shifts, the array became $ [3, 4, 3, 3, 2] $ . In the second operation, a fixed point $ x = 3 $ was chosen, and after $ 3 $ left shifts, the array became $ [3, 2, 3, 4, 3] $ . In the third operation, a fixed point $ x = 3 $ was chosen again, and after $ 3 $ left shifts, the array became $ [4, 3, 3, 2, 3] $ , which is equal to the array $ b $ .

In the second test case, the array $ a $ could be equal to $ [7, 2, 1] $ . After the operation with a fixed point $ x = 2 $ , the array became $ [1, 7, 2] $ . Then, after the operation with a fixed point $ x = 1 $ , the array returned to its initial state $ [7, 2, 1] $ . These same $ 2 $ operations (with $ x = 2 $ , and $ x = 1 $ ) were repeated $ 49 $ times. So, after $ 100 $ operations, the array returned to $ [7, 2, 1] $ .

In the third test case, it can be shown that there is no solution.

## 样例 #1

### 输入

```
6
5 3
4 3 3 2 3
3 100
7 2 1
5 5
6 1 1 1 1
1 1000000000
1
8 48
9 10 11 12 13 14 15 8
2 1
1 42```

### 输出

```
Yes
Yes
No
Yes
Yes
No```

# 题解

## 作者：EternityLove (赞：10)

正着想操作不是很好想，考虑倒着想操作。

当你考虑操作的逆操作时，你会发现，相当于每次回退 $a_n$ 格，这可以简单证明：你每次正着操作选择 $a_x=x$ 的值，然后循环左移 $x$ 位，那么原来 $a_x$ 的值一定落在新的序列的 $a_n$ 的位置。

那么你的问题转变为，$b$ 序列能不能进行 $k$ 次逆操作。

考虑什么时候不能进行逆操作，即当且仅当 $a_n\gt n$ 时，序列不可进行逆操作。

此时可以考虑模拟整个过程，值得注意的是，我们每次操作不需要去移动数组，而只需要修改最后一个数的指针位置即可，比如当且最后一个数的指针在 $now$ 的位置，那么模拟一次操作相当于只需要将这个指针循环左移 $a_{now}$ 位即可。

由于 $k$ 很大，我们完全模拟会超时，考虑优化。容易发现，如果当前指针已经被访问过了，说明已经进行了一个循环了，那么此时肯定有解，所以我们至多只需要模拟 $n$ 次即可得到答案。

~~~cpp
#include <bits/stdc++.h>
#define N 500010
#define ll long long
#define endl '\n'
using namespace std;

inline ll read() {
    char ch=getchar();ll ans=0,f=1;
    for (;!isdigit(ch);ch=getchar()) if (ch=='-') f=-1;
    for (;isdigit(ch);ch=getchar()) ans=(ans<<3)+(ans<<1)+ch-'0';
    return ans*f;
}

int a[N],flag[N];

void slv() {
    int n,k;
    cin>>n>>k;
    for (int i = 0;i < n;++ i) cin>>a[i],flag[i]=0;
    int now=n-1;
    while (k && !flag[now]) {
        flag[now]=1;
        if (a[now]>n) {
            cout<<"No"<<endl;
            return;
        }
        now=(now-a[now]+n)%n;
        --k;
    }
    cout<<"Yes"<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int T=1;
    cin>>T;
    while (T--) {
        slv();
    }
    return 0;
}


---

## 作者：fish_shit (赞：2)

不难发现，每一次操作后数列的最后一个数便是这一次操作所做的轮换的次数。因为最后一个数往前轮它本身次时，它一定会回到下标为它本身的位置上。所以如果这一次操作后，最后一个数大于 $n$，就说明初始序列不存在。

我们考虑从 $b$ 序列倒着去操作。每一次确定下一次操作轮换的次数。具体实现可以用一个变量存着每次操作后最后一个数所在的位置。

我们倒着去操作时最多操作 $n$ 和 $k$ 中较小者次。如果操作 $k$ 次没发生问题，就说明初始序列存在；如果操作 $n$ 次后还没发生问题，就说明序列轮换产生了循环且经过的每个数都没问题，也能说明初始序列存在。

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int b[210000];
bool vis[210000];
int main(){
	int t;
	cin>>t;
	while(t--){
		memset(vis,0,sizeof(vis));
		int n,k,pos;
		cin>>n>>k;
		pos=n;
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		k=min(k,n);
		bool flag=0;
		for(int i=1;i<=k;i++){
			if(vis[pos]){
				cout<<"Yes"<<endl;
				flag=1;
				break;
			}
			else{
				vis[pos]=1;
			}
			if(b[pos]>n){
				cout<<"No"<<endl;
				flag=1;
				break;
			}
			pos-=b[pos];
			if(pos<1){
				pos=n-(1-pos)+1;
			}
		}
		if(!flag){
			cout<<"Yes"<<endl;
		}
	}
	return 0;
}

```


---

## 作者：wangyibo201026 (赞：1)

## 题目思路

**本文中的 $a$ 均为题面中的 $b$。**

首先发现这个东西是轮换，而轮换一共只有 $n$ 种，我们用 $x$ 来表示一个轮换，定义一个以 $a_x$ 开头的轮换。

然后我们发现，对于每一个轮换，都又若干种方式转移到一个轮换，**不难发现转移次数是 $O(n)$ 级别的**，具体的证明，考虑每一个 $i$，以它为转移的只有一个（$i - a_i + 1 \Rightarrow i + 1$），所以转移一共是 $O(n)$ 级别的。

把这张转移图**倒着**建出来，暴力从 $1$ 开始跑，如果跑到一个环，就肯定可以，如果跑到尽头了还是没有跑完，就不行了（就是最长路与 $k$ 的大小关系），这样每个点每条边最多遍历一次，复杂度 $O(n)$。

## 题目代码

Code：

```cpp
#include <Touwenjian>

using namespace std;

#define int long long
#define fir first
#define sec second
#define mkp make_pair 
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;

char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}

template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int t, n, k;
int a[N];
bool vis[N], flag;

int check_id ( int x ) {
	if ( x <= 0 ) {
		return x + n;
	}
	else if ( x > n ) {
		return x - n;
	}
	else {
		return x;
	}
}

int head[N], tot;

struct Graph {
	int to, next;
} edges[N << 1];

void add ( int u, int v ) {
	tot ++;
	edges[tot].to = v;
	edges[tot].next = head[u];
	head[u] = tot;
}

void dfs ( int x, int p ) { // 暴力跑最长路
	if ( vis[x] || p == k ) { // 有环或者已经满了
		flag = 1;
		return ;
	}
	vis[x] = true;
	for ( int i = head[x]; i; i = edges[i].next ) {
		dfs ( edges[i].to, p + 1 );
	}
}

void Solve () {
	cin >> t;
	while ( t -- ) {
		tot = 0, flag = 0;
		memset ( head, 0, sizeof ( head ) );
		memset ( vis, 0, sizeof ( vis ) );
		cin >> n >> k;
		for ( int i = 1; i <= n; i ++ ) {
			cin >> a[i];
		}
		for ( int i = 1; i <= n; i ++ ) {
			if ( a[i] <= n ) {
				add ( check_id ( i + 1 ), check_id ( i - a[i] + 1 ) ); // 这里就是反着建图，轮换从 i - a[i] + 1 转移到 i + 1，手动模拟一下就知道了
			}
		}
		dfs ( 1, 0 );
		if ( flag ) {
			cout << "Yes\n";
		}
		else {
			cout << "No\n";
		}
	}
}

signed main () {
#ifdef judge
	freopen ( "Code.in", "r", stdin );
	freopen ( "Code.out", "w", stdout );
	freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

---

