# Penchick and Satay Sticks

## 题目描述

Penchick and his friend Kohane are touring Indonesia, and their next stop is in Surabaya!

In the bustling food stalls of Surabaya, Kohane bought $ n $ satay sticks and arranged them in a line, with the $ i $ -th satay stick having length $ p_i $ . It is given that $ p $ is a permutation $ ^{\text{∗}} $ of length $ n $ .

Penchick wants to sort the satay sticks in increasing order of length, so that $ p_i=i $ for each $ 1\le i\le n $ . For fun, they created a rule: they can only swap neighboring satay sticks whose lengths differ by exactly $ 1 $ . Formally, they can perform the following operation any number of times (including zero):

- Select an index $ i $ ( $ 1\le i\le n-1 $ ) such that $ |p_{i+1}-p_i|=1 $ ;
- Swap $ p_i $ and $ p_{i+1} $ .

Determine whether it is possible to sort the permutation $ p $ , thus the satay sticks, by performing the above operation.

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, we can sort permutation $ p = [2, 1, 3, 4] $ by performing an operation on index $ 1 $ ( $ |p_2 - p_1| = |1 - 2| = 1 $ ), resulting in $ p = [1, 2, 3, 4] $ .

In the second test case, it can be proven that it is impossible to sort permutation $ p = [4, 2, 3, 1] $ by performing the operation. Here is an example of a sequence of operations that can be performed on the permutation:

- Select $ i = 2 $ ( $ |p_3 - p_2| = |3 - 2| = 1 $ ). This results in $ p = [4, 3, 2, 1] $ .
- Select $ i = 1 $ ( $ |p_2 - p_1| = |3 - 4| = 1 $ ). This results in $ p = [3, 4, 2, 1] $ .
- Select $ i = 3 $ ( $ |p_4 - p_3| = |1 - 2| = 1 $ ). This results in $ p = [3, 4, 1, 2] $ .

Unfortunately, permutation $ p $ remains unsorted after performing the operations.

## 样例 #1

### 输入

```
2
4
2 1 3 4
4
4 2 3 1```

### 输出

```
YES
NO```

# 题解

## 作者：Lyw_and_Segment_Tree (赞：3)

## 题意简述

给定一个序列 $\{p_i\}$，可进行若干次如下操作：

- 选择一个索引 $i$，且满足 $|p_i - p_{i + 1}| = 1$，则可以交换 $p_i$ 和 $p_{i + 1}$。

确定是否可以通过上述操作使得对于所有的 $1 \le i \le n$，有 $p_i = i$。

## 开始解题！

我们可以从小的子问题进行解决，过程如下：

首先我们假设 $p$ 是一个从 $1$ 到 $n$ 的排列，则

- 当 $n = 1$ 时，显然可以满足。

- 当 $n = 2$ 时，只有 $1, 2$，$2, 1$ 两种情况，均可完成。

- 当 $n = 3$ 时，有 $1, 2, 3$，$1, 3, 2$，$2, 1, 3$，$2, 3, 1$，$3, 1, 2$，$3, 2, 1$ 这六种情况，而不难发现 $2, 3, 1$ 与  $3, 1, 2$ 与 $3, 2, 1$ 这三种情况无法解决，并且这三种情况都满足存在一个 $p_i$ 满足 $|p_i - i| \ge 2$，于是我们可以猜测当 $p$ 中存在任意一个  $|p_i - i| \ge 2$ 时无法完成，你提交了上去，并且过了。


接下来我们证明一下（摘自官方题解，笔者在自己做题时仅猜想结论，并未做严谨证明）：

假设我们从同位排列（即对于每个 $1 \le i \le n$，满足 $p_i = i$ 的排列）开始。考虑一下 $p_i = i$ 和 $p_{i + 1} = i + 1$ 互换后的情况。交换后，元素 $p_1$ 至 $p_{i - 1}$ 将由 $1$ 至 $i - 1$ 组成，而 $p_{i + 2}$ 至 $p_n$ 将由 $i + 2$ 至 $n$ 组成。因此， $p_i = i + 1$ 不可能与 $p_{i - 1} \lt i$ 交换， $p_{i + 1} = i$ 也不可能与 $p_{i + 2} \gt i + 1$ 交换。

即能够完成的条件如下（对于每个 $p_i$，任满足其中一条即可）：

- $p_i = i$

- $p_i = i + 1, p_{i + 1} = i$

- $p_i = i - 1, p_{i - 1} = i$

把这些条件进行一个简单的转换即可得出我们的结论 $|p_i - i| \lt 2$，即若 $|p_i - i| \ge 2$，则不可行。

时间复杂度 $O(Tn)$，代码易得。

code : 

```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double

using namespace std;

char buf[1 << 21], *p1 = buf, *p2 = buf;

const ll getc() {
    return p1 == p2 && ( p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1 ++;
}

const ll read() {
	ll x = 0, f = 1;
	
	char ch = getc();
	
	while (ch < '0' || ch > '9') {
		if (ch == '-') f = -1; ch = getc();
	}
	
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getc();
	}
	
	return x * f;
}

const void write(string s) {
	ll sz = s.size();

	for (ll i = 0; i < sz; i++) {
		putchar(s[i]);
	}

	return ;
}

int main() {
	ll T = read();

	while (T--) {
		ll n = read(); bool flag = true;

		for (ll i = 1; i <= n; i++) {
			ll x = read();

			if (abs(x - i) > 1) {
				flag = false;
			}
		}

		if (flag) {
			write("YES");
		} else {
			write("NO");
		}

		puts("");
	}

	return 0;
}
```

[AC record](https://codeforces.com/contest/2031/submission/291811793)

---

## 作者：fishing_cat (赞：3)

[传送门](https://codeforces.com/problemset/problem/2031/B)

### 题意

考虑反向操作，变成给定一个 $1$ 到 $n$ 的严格递增排列，可以进行一种操作，即将两个绝对值差为一的两个数交换位置，问所给排列是否能通过一定次数的操作实现。

### 思路

和[官解](https://codeforces.com/blog/entry/136260)做法不一样。

因为这种独特的交换条件，可以发现在位置 $x$ 的数 $h_x$ 只可能到达 $h_{x-1}$ 和 $h_{x+1}$，或者位置不变。所以可以扫一遍，直接判断这个数和其位置的绝对值差，不符合一定不合法。

然后我们再考虑符合后就一定合法了吗？我们可以从排列最前端开始考虑。对于 $h_1$ 只有两种可能操作，不变和与 $h_2$ 交换。而如果交换了，下一个数的操作其实就已经确定了（因为再重新交换回原来的状态没有意义）。所以只需要满足上面的条件，其实就是合法的。可以自己画画，理解一下。

~~CF思维题~~猜结论题，纪念我因数组开小而获得的一发罚时。

### code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define il inline
using namespace std;
/*快读省了*/
ll t, n, h[200200];

int main() {
	read(t);
	while (t--) {
		read(n);
		for (int i = 1; i <= n; i++) {
			read(h[i]);
		}
		ll key = 1;
		for (int i = 1; i <= n; i ++) 
			if (abs(h[i] - i) >= 2) {
				key = 0;
				break;
			}
		
		if (key == 0) puts("No");
		else puts("Yes");
	}
	return 0;
}

```

---

## 作者：Ivan422 (赞：1)

题目大意：给你一个排列 $p$，要求你可以通过交换相邻两个数差为 $1$ 的数，让排列变成单调递增的，即对于 $i$ 在 $1$ 到 $n$ 之中时，$p_i=i$。

做法：首先考虑分析哪些数可以互换。当 $p_i$ 可以与 $p_{i-1}$ 和 $p_{i+1}$ 交换时，我们发现，任意一组交换后，剩下的一组都会拆散。我们再考虑，可不可以用超过 $2$ 次交换让 $p_i=i$。显然我们发现，一个数只能与 $p_i-1$ 与 $p_i+1$ 交换，而一个数 $p_{i-1}$ 通过 $p_i$ 能够连环交换到 $i+1$ 的位置，就必须满足：$p_{i-1}$ 与 $p_{i+1}$ 可以交换，才能在与 $p_i$ 交换完之后再进行交换，$p_i$ 与 $p_{i-1}$ 能交换。当然，在这个问题中，我们假设三个数中每一个数都不满足 $p_i\neq i$，才会有交换的必要，因为是排列，所以 $p_i=p_{i+1}$，并且由于 $p_i$ 与 $p_{i+1}$ 都能与 $p_{i-1}$ 交换，所以 $|p_i-p_{i+1}|=2$，这显然不能交换，所以综上所述，**操作仅限于相邻两项**，所以我们就可以轻松过掉这题了。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int _,n,a[N];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>_;
	while(_--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		for(int i=1;i<=n;i++){
			if(i==a[i])continue;
			if(i<n&&a[i+1]==i&&a[i]==i+1){swap(a[i],a[i+1]);}
			else goto nxt;
		}
		if(true){cout<<"Yes\n";}
		else{nxt:;cout<<"No\n";}
	}
	return 0;
}
```

---

## 作者：GCSG01 (赞：1)

### 思路
赛时凭直觉想到每个数最多交换一次，为什么呢？  
首先 $i$ 换的情况为 $a[i]>a[i+1]$，因为只有这样交换才有意义，能使数组递增。所以当对应 $i$ 的那个数不在 $i-1,i,i+1$ 的位置上时，这个数组不符合条件，因为它无法仅用一次换回正确位置。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
signed main()
{
    #ifndef ONLINE_JUDGE
        freopen("1.in","r",stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n,f=0;
        cin>>n;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        for(int i=1;i<=n;i++)
            if(a[i]!=i-1&&a[i]!=i&&a[i]!=i+1)
            {
                cout<<"No\n";
                f=1;
                break;
            }
        if(!f)cout<<"Yes\n";
    }
    return 0;
}
```

---

## 作者：AK_400 (赞：1)

首先 $1$ 只能和 $2$ 换，所以要么 $p_1=1$，要么 $p_1=2,p_2=1$，否则无解。然后 $1$ 归位后 $2$ 只能和 $3$ 换，和 $1$ 同理。于是枚举索引 $i$，如果 $p_i=i$，那么继续枚举，否则如果 $p_i=i+1\land p_{i+1}=i$，交换 $p_i$ 和 $p_{i+1}$，继续枚举，否则无解。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[200005];
void slv(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>p[i];
    for(int i=1;i<=n;i++){
        if(p[i]==i)continue;
        if(p[i+1]==i&&abs(p[i]-p[i+1])==1)swap(p[i],p[i+1]);
        else {
            cout<<"NO"<<endl;
            return;
        }
    }
    cout<<"YES"<<endl;
}
int main(){
    int T;cin>>T;while(T--)
    slv();
    return 0;
}
```

---

## 作者：Quartz_Blocks (赞：0)

介绍一种时间慢但是特殊的做法。
###### (大炮轰蚊子？)

众所周知，有一种数据结构叫 ST 表，它可以 $O(1)$ 解决 RMQ 问题的单次查询。

众所又周知，对于一个位于 $i$ 的元素 $a_i$，需要移动到位置 $j$ ($i < j$)，若 $\max{(a_i,a_i+1,\dots,a_j)} - a_i > 1$ 或者 $a_i - \min{(a_i,a_i+1,\dots,a_j)} > 1$，那么 $a_i$ 在通过交换操作往 $j$ 位置移动时一定不能到达。因为在这个区间当中存在无法与 $a_i$ 交换的值，所以 $a_i$ 一定无法到达 $j$ 位置。

那求 $\max{(a_i,a_i+1,\dots,a_j)} - a_i > 1$ 和 $a_i - \min{(a_i,a_i+1,\dots,a_j)} > 1$ 的过程不就是 RMQ 问题吗？

我们就可以预处理两个 ST 表，一个用于存储最大值，一个用于存储最小值。

既然有了这两个 ST 表，问题自然就迎刃而解了！

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#include<bits/stdc++.h>
using namespace std;
int n;
int a[200010];//存储序列
int log_2[200010];//预处理 log_2 的值
int mx[200010][21];// mx 数组（也就是 ST 表）
int mn[200010][21];// mx 数组（也就是 ST 表）
inline int read(){//快速读入
	int x = 0,f = 1;// x 代表数字，f 代表符号
	char ch = getchar();//读入字符
	while(ch < '0' || ch > '9'){//没读入到数字
		if(ch == '-') f = -1;//读入到了负
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){//读入到了数字
		x = x*10 + ch-48;//加入 x
		ch = getchar();
	}
	return x * f;
}
void gen(){
	cin >> n;
	for(int i = 1;i <= n;i++){
		a[i] = read();
		mx[i][0] = a[i];//初始化 mx[i][0]，单个数字的区间最大值肯定是那个数字。
		mn[i][0] = a[i];//初始化 mx[i][0]，单个数字的区间最大值肯定是那个数字。
	} 
	
	
	for(int j = 1;j <= log_2[n];j++){// 先以 j 为维度
		for(int i = 1;i + (1 << j) - 1 <= n;i++){//再生成
			mx[i][j] = max(mx[i][j-1],mx[i+(1 << (j-1))][j-1]);//状态转移
			mn[i][j] = min(mn[i][j-1],mn[i+(1 << (j-1))][j-1]);//状态转移
		}
	}
	return;
}
int que(int l,int r,bool op){//op == 1 max      op == 0 min
	int t = log_2[r-l+1];
	return (op ? max(mx[l][t],mx[r - (1 << t) + 1][t]) : min(mn[l][t],mn[r - (1 << t) + 1][t]));
}

void solve(){
	gen();
	for(int i = 1;i <= n;i++){
		if(a[i] != i){
			bool flag = 1;
			if(que(min(i,a[i]),max(i,a[i]),1) - a[i] >= 2){
				flag = 0;
			}
			if(a[i] - que(min(i,a[i]),max(i,a[i]),0) >= 2){
				flag = 0;
			}
			if(flag == 0){
				cout << "NO\n";
				return;
			}
		}
	}
	cout << "YES\n";
	return;
}
// n + n log n + T()
int main(){
	log_2[1] = 0;//log 1 = 0
	for(int i = 2;i <= 200000;i++){
		log_2[i] = log_2[i / 2] + 1;//计算 log 的值。
	}
	int T;
	cin >> T;
	while(T--){
		solve();
	}
	
	
	return 0;
}

```

---

## 作者：YuYuanPQ (赞：0)

碰到可进行任意次数的操作的题，首先想想上界。\
可以发现：这道题的操作次数最多就是 $1$ 次。

为什么？

当前数 $p_{i}$ 与下一个数 $p_{i+1}$ 进行交换，而这 $1$ 次交换后，整个序列中满足差值为 $1$ 的就只有 $p_{i+1}$，但是 $p_{i+1}$ 已经去了 $p_{i}$ 前面，所以不能再进行操作了。

得到这个结论就很好做了：如果 $p_{i}$ 与它应在的位置 $i$ 的差值 $\geq 2$，那 $p_{i}$ 就回不去了，即无解；否则，有解。

说句闲话：如果这个题不限制 $p_{i}$ 只能与 $p_{i+1}$ 进行交换，那么会复杂很多。

## Code
[Link](https://codeforces.com/contest/2031/submission/291756722)

---

## 作者：tai_chi (赞：0)

可以在 [cnblog](https://www.cnblogs.com/tai-chi/p/18549167) 中阅读。

#### 题意

给一个排列，每次操作可以交换相邻且相差为 $1$ 的两个数，问通过这样的交换是否可以将这个排列排序为递增。

#### 分析

一个关键性质是任何数不会被交换两次，这表明模拟这个过程的复杂度是线性的，那就按照题意模拟就行了。

如果两个数满足相差为 $1$ 且前面的数不在它应该在的位置上我们就选择交换，扫一遍后检查数组是否已经排序。

```cpp
void solve()
{
	int n; cin>>n;
	vector<int> a(n+5);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i]==i) continue;
		else if(a[i]!=i&&abs(a[i]-a[i+1])==1) swap(a[i],a[i+1]);
	}
	bool flag=1;
	for(int i=1;i<=n;i++) if(a[i]!=i) {flag=0; break;}
	if(flag) cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}
```

---

## 作者：Your_Name (赞：0)

## 题意
给一个 $1$ 到 $n$ 的排列。

只能交互相邻差为 $1$ 的项，问能不能使序列变为 $1...n$。

## 题解

发现如果能交换就交换一定不会出现非最优解，于是直接交互即可，最后再判断序列是否满足要求即可。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], T, k[N], x;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> T;
    while(T --){
        cin >> n;
        for(int i = 1; i <= n; i ++){
            cin >> x;
            a[x] = i;//记录这个数在哪
            k[i] = x;//记录序列
        }
        for(int i = 2; i <= n; i ++){
            if(a[i - 1] - a[i] == 1){
                swap(a[i], a[i - 1]);
                swap(k[a[i]], k[a[i - 1]]);
            }//交换
        }
        bool fl = 1;
        for(int i = 1; i <= n; i ++){
            if(k[i] != i){
                fl = 0;
                break;
            }
        }
        if(fl)cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
    return 0;
}
```

---

## 作者：lilong (赞：0)

提供一个比较好想的思路。

读题发现给定的序列是一个排列，即任意两个数互不相同。考虑 $n$ 这个数，它只能与 $n-1$ 交换，因此它要么在第 $n$ 个位置上，要么在第 $n-1$ 个位置上，且在后者情况下必须满足 $p_n=n-1$ 才能有解。将 $n$ 固定下来后，$n-1$ 只能与 $n-2$ 交换了，和上一步十分相似，以此类推即可。

单组数据时间复杂度 $O(n)$，代码十分简洁。


```cpp
#include <iostream>
#include <cstdio>
#define int long long
 
using namespace std;
 
int n,a[1000001],p[1000001],flag;
 
void solve( void )
{
	cin >> n;
	for( int i = 1 ; i <= n ; i ++ )
	{
		cin >> a[i];
		p[a[i]] = i;
	}
	flag = 0;
	for( int i = n ; i > 1 ; i -- )
	{
		if( p[i] == i ) continue;//已经出现在了正确的位置上
		else if( p[i] == i - 1 && p[i - 1] == i )//交换一次
		{
			swap( p[i] , p[i - 1] );
			continue;
		}
		flag = 1;//无解
		break;
	}
	if( !flag ) cout << "YES\n";
	else cout << "NO\n";
	return;
}
 
signed main()
{
	ios::sync_with_stdio( false );
	cin.tie( 0 );
	cout.tie( 0 );
	int T;
	cin >> T;
	while( T -- )
		solve();
	return 0;
}
```

---

## 作者：huanglihuan (赞：0)

#### 题目大意
给定一个长度为 $n$ 的序列 $p$，可以进行若干次操作，对于每次操作：
+ 可以选择正整数 $i\in[1,n-1]$ 且 $|p_{i+1}-p_i|=1$；
+ 交换 $p_i,p_{i+1}$。

要求 $p$ 数组严格递增，即对于 $\forall i\in[1,n-1]$ 都有 $p_i<p_{i+1}$。  
询问是否可以满足要求。
#### 思路
容易发现每个数最多交换一次，且满足 $p_i-p_{i+1}=1$ 因为此时 $p_i>p_{i+1}$ 不满足递增所以交换。  
$n$ 次判断后询问数组 $p$ 是否严格递增。
#### 代码

```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 998244353
#define MOD 1000000007
using namespace std;
const int N = 2e6 + 5,maxn = 3e3 + 5;
int a [N];
void solve ()
{
	int n;
	cin >> n;
	for (int i = 1;i <= n;i ++) cin >> a [i];
	for (int i = 1;i < n;i ++)
	{
		if (a [i] - a [i + 1] == 1) swap (a [i],a [i + 1]);
	}
	for (int i = 1;i < n;i ++)
	{
		if (a [i] >= a [i + 1])
		{
			cout << "NO\n";
			return ;
		}
	}
	cout << "YES\n";
}
signed main ()
{
	int T;
	cin >> T;
	while (T --) solve ();
	return 0;
}
```

---

## 作者：Jerrycyx (赞：0)

从反面思考一下，一个有序序列里任意一个元素最多被交换一次，所以要让一个无序序列通过这种方式变得有序，每个元素也只能被交换最多一次。尝试交换所有可以交换的逆序对，最后判断是否有序即可。


```cpp
const int N=2e5+5;
int n,a[N];

int main()
{
	int T; read(T);
	while(T--)
	{
		read(n);
		for(int i=1;i<=n;i++)
			read(a[i]);
		for(int i=2;i<=n;i++)
			if(a[i-1]-a[i]==1) swap(a[i-1],a[i]);
		puts(is_sorted(a+1,a+n+1)?"YES":"NO");
	}
	return 0;
}
```

---

