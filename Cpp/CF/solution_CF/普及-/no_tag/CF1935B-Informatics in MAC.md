# Informatics in MAC

## 题目描述

In the Master's Assistance Center, Nyam-Nyam was given a homework assignment in informatics.

There is an array $ a $ of length $ n $ , and you want to divide it into $ k > 1 $ subsegments $ ^{\dagger} $ in such a way that the $ \operatorname{MEX} ^{\ddagger} $ on each subsegment is equal to the same integer.

Help Nyam-Nyam find any suitable division, or determine that it does not exist.

 $ ^{\dagger} $ A division of an array into $ k $ subsegments is defined as $ k $ pairs of integers $ (l_1, r_1), (l_2, r_2), \ldots, (l_k, r_k) $ such that $ l_i \le r_i $ and for each $ 1 \le j \le k - 1 $ , $ l_{j + 1} = r_j + 1 $ , and also $ l_1 = 1 $ and $ r_k = n $ . These pairs represent the subsegments themselves.

 $ ^{\ddagger}\operatorname{MEX} $ of an array is the smallest non-negative integer that does not belong to the array.

For example:

- $ \operatorname{MEX} $ of the array $ [2, 2, 1] $ is $ 0 $ , because $ 0 $ does not belong to the array.
- $ \operatorname{MEX} $ of the array $ [3, 1, 0, 1] $ is $ 2 $ , because $ 0 $ and $ 1 $ belong to the array, but $ 2 $ does not.
- $ \operatorname{MEX} $ of the array $ [0, 3, 1, 2] $ is $ 4 $ , because $ 0 $ , $ 1 $ , $ 2 $ , and $ 3 $ belong to the array, but $ 4 $ does not.

## 说明/提示

In the first test case, the array $ a $ can be divided into $ 2 $ subsegments with boundaries $ [1, 1] $ and $ [2, 2] $ :

- $ \operatorname{MEX} $ of the first subsegment $ [0] $ is $ 1 $ , as $ 0 $ belongs to the subsegment, but $ 1 $ does not.
- $ \operatorname{MEX} $ of the second subsegment $ [0] $ is $ 1 $ , as $ 0 $ belongs to the subsegment, but $ 1 $ does not.

In the second test case, it can be proven that the required division does not exist.

In the third test case, the array $ a $ can be divided into $ 3 $ subsegments with boundaries $ [1, 3] $ , $ [4, 5] $ , $ [6, 8] $ :

- $ \operatorname{MEX} $ of the first subsegment $ [0, 1, 7] $ is $ 2 $ , as $ 0 $ and $ 1 $ belong to the subsegment, but $ 2 $ does not.
- $ \operatorname{MEX} $ of the second subsegment $ [1, 0] $ is $ 2 $ , as $ 0 $ and $ 1 $ belong to the subsegment, but $ 2 $ does not.
- $ \operatorname{MEX} $ of the third subsegment $ [1, 0, 3] $ is $ 2 $ , as $ 0 $ and $ 1 $ belong to the subsegment, but $ 2 $ does not.

## 样例 #1

### 输入

```
5
2
0 0
5
0 1 2 3 4
8
0 1 7 1 0 1 0 3
3
2 2 2
4
0 1 2 0```

### 输出

```
2
1 1
2 2
-1
3
1 3
4 5
6 8
3
1 1
2 2
3 3
-1```

# 题解

## 作者：Kindershiuo (赞：4)

# 解题思路
题目是让我们想办法把数组分成 $k$ 个段，让这 $k$ 个段的 $\operatorname{mex}$ 相同，题目让我们分成 $k$ 段，那我们一定可以把中间一些段给合并，然后就只剩 $2$ 段，这应该是一个很显而易见的结论，所以我们就是维护一个前缀 $\operatorname{mex}$ 数组还有后缀 $\operatorname{mex}$ 数组，然后再枚举每一个下标 $i$ 都当成一次断点，如果存在一个前缀 $\operatorname{mex}$ 等于后缀 $\operatorname{mex}$，那么我们就输出答案，如果不存在，那就无解。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T;

void solve() {
	int n;
	cin>>n;
	map<int,int>ma;
	map<int,int>mb;
	int mex1[n+5];
	int mex2[n+5];
	memset(mex1,0,sizeof mex1);
	memset(mex2,0,sizeof mex2);
	int a[n+5];
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		mex1[i]=mex1[i-1];
		ma[a[i]]++;
		while(ma[mex1[i]])mex1[i]++;
	}
	for(int i=n;i>=1;i--){
		mex2[i]=mex2[i+1];
		mb[a[i]]++;
		while(mb[mex2[i]])mex2[i]++;
	}
	for(int i=1;i<=n;i++){
		if(mex1[i]==mex2[i+1]){
			cout<<2<<endl;
			cout<<1<<" "<<i<<endl;
			cout<<i+1<<" "<<n<<endl;
			return;
		}
	}
	cout<<-1<<endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
//	T=1;
	while (T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：ylch (赞：2)

## Description（描述）

有一个长度为 $n$ 的数组 $a(0 \le a_i \le n)$，把它分成 $k \ge 1$ 个子段，使每个子段上的 $\text{MEX}$ 都等于相同的整数。

> 一个数列的 $\text{MEX}$ 是指一个数列中没有出现过的最小自然数。

## Analysis（分析）

首先考虑 $\text{MEX}$ 的一些基本的性质。

若序列 $a$ 的 $\text{MEX}$ 为 $k$，序列 $b$ 的 $\text{MEX}$ 也为 $k$，那么将序列 $a$ 和 $b$ 合并，则合并的序列 $\text{MEX}$ 也为 $k$。

由此可以得到，若可以分为若干个 $\text{MEX}$ 为 $k$ 的序列，则一定可以分成两个 $\text{MEX}$ 为 $k$ 的序列。

### 方法 $1$：
若一个序列 $\text{MEX}$ 为 $k$，则这个序列中一定不存在 $k$。由此，两个序列的 $\text{MEX}$ 一定不能在原序列中出现。可以推出，两个序列的 $\text{MEX}$ 一定为整个序列的 $\text{MEX}$。

然后就是判断是否存在一个分割点，使得分割点左右两个序列全都包含小于整个序列的 $\text{MEX}$ 的所有数字。

### 方法 $2$：
求出原数组 $a$ 的前缀、后缀 $\text{MEX}$，找到一个分割点，使得分割点左右两个序列的 $\text{MEX}$ 相等即可。

## Code（代码）

### 方法 $1$：

我们要求出分割点左右两个序列是否凑齐所有小于整个序列的 $\text{MEX}$ 的数，可以用类似滑动窗口的方法，配合桶数组解决。

具体地，假设分割点为 $i$，我们用两个桶 $vis1,vis2$ 分别记录 $[1,i]$ 和 $[i+1,n]$ 两个段中每个数字出现的次数，用 $cnt1,cnt2$ 分别记录以上两段中不同的小于整个序列的 $\text{MEX}$ 的数的个数。

不断维护两个变量，如果 $cnt1=cnt2=\text{MEX}$，则说明分割点左右两个序列全都包含小于整个序列的 $\text{MEX}$ 的所有数字（即 $[0,\text{MEX}-1]$ 的所有数字），符合条件。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve()
{
    int n;
    cin >> n;
    vector <int> a(n + 1);

    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }

    // 预先求出整个序列的mex
    set <int> s;
    for(int i = 0; i <= n; i ++) s.insert(i);
    for(int i = 1; i <= n; i ++){
        if(s.find(a[i]) != s.end()) s.erase(a[i]);
    }
    int mex = *s.begin(); // 存储一下

    int cnt1 = 0, cnt2 = 0; // 表示[1,i]、[i+1,n]两个段不同的小于mex的数字个数
    unordered_map <int, int> vis1, vis2; // 记录两段里数字出现的个数

    for(int i = n; i >= 1; i --){
        vis2[a[i]] ++;
        if(vis2[a[i]] == 1 && a[i] < mex) ++ cnt2; // 统计所有小于mex的不同的数的个数
    }

    for(int i = 1; i <= n; i ++){
        // 维护变量
        vis1[a[i]] ++;
        if(vis1[a[i]] == 1 && a[i] < mex) ++ cnt1;
        vis2[a[i]] --;
        if(vis2[a[i]] == 0 && a[i] < mex) -- cnt2;
        // cnt1==cnt2说明两个序列中小于mex的不同的数的个数相等，cnt1==cnt2==mex说明它们包含小于mex的所有数(0~mex-1)，即它们的mex都等于原序列mex
        if(cnt1 == cnt2 && cnt1 == mex){
            cout << 2 << '\n' << 1 << ' ' << i << '\n' << i + 1 << ' ' << n << '\n';
            return ;
        }
    }
    cout << -1 << '\n'; // 找不到输出-1
}

signed main()
{
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while(t --) solve();
    return 0;
}
```

### 方法 $2$：

注意到隐藏在数据范围中的关键条件：$0 \le a_i \le n$。

由此，就可以求出 $a$ 数组的前缀、后缀 $\text{MEX}$。

考虑用 set 实现，预先添加 $0 \sim n$ 的数字到 set 中，每出现一个 $a_i$，就从 set 中把 $a_i$ 删除（注意每个相同的 $a_i$ 只能删一次）。当前每个位置的 $\text{MEX}$ 就是 set 中最小的数。

~~STL 大法好！~~

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve()
{
    int n;
    cin >> n;
    vector <int> a(n + 1);

    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }

    vector <int> v1(n + 1), v2(n + 1); // 前缀、后缀MEX数组
    set <int> st; // 处理mex数的集合

    // 前缀mex
    for(int i = 0; i <= n; i ++) st.insert(i); // a[i]的值域是0~n
    for(int i = 1; i <= n; i ++){
        if(st.find(a[i]) != st.end()){ // 如果还在set中
            st.erase(a[i]);
        }
        v1[i] = *st.begin(); // 每个位置的前缀mex就是集合中最小的数
    }
    st.clear();

    // 后缀mex
    for(int i = 0; i <= n; i ++) st.insert(i); // a[i]的值域是0~n
    for(int i = n; i >= 1; i --){
        if(st.find(a[i]) != st.end()){ // 如果还在set中
            st.erase(a[i]);
        }
        v2[i] = *st.begin(); // 每个位置的前缀mex就是集合中最小的数
    }
    
    // 枚举前后mex一致的分割点
    for(int i = 2; i <= n; i ++){
        // v1[i] 1~i的mex；v2[i] i~n的mex
        if(v1[i - 1] == v2[i]){ // 1~i-1的mex = i~n的mex
            cout << 2 << '\n' << 1 << ' ' << i - 1 << '\n' << i << ' ' << n << '\n';
            return ;
        }
    }
    cout << -1 << '\n'; // 找不到输出-1
}

signed main()
{
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while(t --) solve();
    return 0;
}
```

## End

管理员大大辛苦啦~

谢谢大家！

---

## 作者：hgckythgcfhk (赞：2)

一眼，线段树二分。

发现如果有解一定可以分成两段，假设有分成 $3$ 段的解但是没有分成两端的解，设 $k+1=\operatorname{mex}$，$3$ 段一定都没有 $k+1$，更大的数没有贡献，就当没有这些数，中间段一定是 $0$ 到 $k$ 组成的，不管从哪里把这一段拆开与前后合并不影响答案，这个结论显然对于原序列的任意一个子段成立，所以可以证明对于整个序列更多段也成立，那我们就试着分两段，枚举分界点，快速求 $\operatorname{mex}$，这一步可以用线段树二分实现，具体的，你可以想一下根据定义暴力求 $\operatorname{mex}$。

[code](https://codeforces.com/problemset/submission/1935/251846193)

---

## 作者：2huk (赞：2)

> 给定一个长度为 $n$ 的序列 $a$。请你找一种将 $a$ 划分成若干个「段」的方案，使得每个「段」的 $\operatorname{mex}$ 都相等。或报告无解。

大胆猜结论。

如果我们将 $a$ 划分成 $> 2$ 个「段」并且使得了每个「段」的 $\operatorname{mex}$ 都相等了，那么我们一定可以通过合并「段」使得最后只剩下 $2$ 段，而且这两个「段」的 $\operatorname{mex}$ 也是相等的。

所以我们只需要考虑划分成两个「段」是否可行。

分别维护前后缀 $\operatorname{mex}$，并枚举断点 $i$，然后判断 $\operatorname{mex}$ 是否相等即可。

预处理每个前缀或后缀的 $\operatorname{mex}$ 可以用 set + map，具体实现如下。

```cpp
#include <bits/stdc++.h>

using namespace std;

//#define int long long
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct FASTREAD {
	template <typename T>
	FASTREAD& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	FASTREAD& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct FASTWRITE {
	template <typename T>
	FASTWRITE& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	FASTWRITE& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	FASTWRITE& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 1e6 + 10;
const int P = 998244353;

int n, a[N], pre[N], suf[N];

void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i <= n; ++ i ) fin >> a[i];
	
	set<int> S;
	for (int i = 0; i < n; ++ i ) S.insert(i);
	map<int, int> P;
	
	for (int i = 1; i <= n; ++ i ) {
		++ P[a[i]];
		if (P[a[i]] == 1) S.erase(a[i]);
		pre[i] = *S.begin(); 
	}
	
	S.clear();
	for (int i = 0; i < n; ++ i ) S.insert(i);
	P.clear();
	
	for (int i = n; i; -- i ) {
		++ P[a[i]];
		if (P[a[i]] == 1) S.erase(a[i]);
		suf[i] = *S.begin(); 
	}
	
	for (int i = 2; i <= n; ++ i )
		if (pre[i - 1] == suf[i]) {
			fout << 2 << '\n' << 1 << ' ' << i - 1 << '\n' << i << ' ' << n << '\n';
			return;
		}
	puts("-1");
}

signed main() {
	int Testcases = 1;
	fin >> Testcases;
	while (Testcases -- ) Luogu_UID_748509();
	return 0;
}
```

---

## 作者：fast_photon (赞：1)

## CF1935B 题解  

### 1. 题意  
给定一个长度为 $n$ 的序列 $\{a_n\}$。问是否存在一种划分方案，把序列划分成若干个区间，使得每个数被划分到恰好一个区间，且每个区间的 $\operatorname{mex}$ 相等。若存在请给出任意一组。  
对于自然数序列 $\{b_m\}$，它的 $\operatorname{mex}$ 表示其中最小的未出现的的自然数。即 $\min x\in \mathbb{N}$，使得 $\forall 1\le i\le m,b_i\neq x$。  
$0\le a_i<n,2\le n\le 10^5$。

### 2. 分析  
此处采用一种经典的刻画 $\operatorname{mex}$ 的方法。  
对于一个数列 $\{b_m\}$，若其 $\operatorname{mex}$ 为 $x$，则：  
+ $\forall 0\le i<x,\ \exists j,\ b_j=i$。即任意不超过 $x$ 的自然数都出现了  
+ $\forall j,\ b_j \neq x$，即 $x$ 没有出现  

同时成立。  
如果这个序列被划分成了至少三段，我们考虑任意两段，它们同时满足这两条性质，因此合并后也满足这两条性质，故合并后 $\operatorname{mex}$ 不变。  
所以如果存在方案。则一定存在划分为 $2$ 个区间的方案。枚举断点，用 `multiset` 维护两侧的 $\operatorname{mex}$ 即可。  

在实现时，我们可以根据定义即“最小没有出现自然数”优化代码，因为值域较小，可以维护要维护的集合在值域上的补集，每次查询取其中最小值即可。  
又因为前缀是正向维护，后缀是反向维护，所以每一次修改之后都是上一次的超集，所以不需要考虑删数的问题。

### 3. 代码  
```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<algorithm>
#define maxn 200005
#define int long long

using namespace std;

set<int> st;

int n, a[maxn], pre[maxn], suf[maxn];
// pre 记录从 1 到 i 的 mex，suf 记录从 i 到 n 的 mex

void work() {
	cin >> n;
	st.clear(); //多测清空
	for(int i = 0; i <= n; i++) { //一定要记得比值域多放进去一个，比如 ai 的最大值是1000，就要把 0~1001都放进去
		st.insert(i); // 值域作为全集
	}
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		st.erase(a[i]); //集合加数等价于补集删数
		pre[i] = *st.begin(); // 取最小值
	}
	st.clear();
	for(int i = 0; i <= n; i++) {
		st.insert(i);
	}
	for(int i = n; i >= 1; i--) {
		st.erase(a[i]);
		suf[i] = *st.begin(); 
	}
	for(int i = 2; i <= n; i++) {
		if(suf[i] == pre[i - 1]) { //若 1~i 和 i+1~n 的 mex 相等，输出方案。
			cout << "2\n1 ";
			cout << i - 1 << '\n' << i << ' ' << n << '\n';
			return ;
		}
	}
	cout << "-1\n"; //否则无解
}

signed main() {
	ios::sync_with_stdio(false); cin.tie(0);
	int _; cin >> _; while(_--) work();
} 
```

---

## 作者：kczw (赞：1)

# 题意
共 $t$ 组数据。

每组数据，给定一个长 $n$ 序列 $a$，问是否有方法将其分为 $k(2\le k\le n)$ 段使得每段的 $MEX$ 相等。

$MEX$ 的定义为序列中最小不存在的非负整数。
# 思路
首先，若有方法使分成的 $k$ 段中的 $MEX$ 相等，那么 $k$ 肯定可以为 $2$。

若先将 $a$ 分成每段 $MEX$ 相等的 $k$ 段，那么每段的最小不存在整数是一样的，所以相邻两段合并成的一段最小不存在整数也还是原来的 $MEX$。

所以，若 $k=2$，则 $k=2$。若 $k\ne 2$，则通过相邻段合并的操作，最后还是可以得到 $k=2$。

于是我们只须枚举左右两段序列的界限，枚举到有 $MEX$ 相等的情况即可。若没有 $MEX$ 相等的情况，则说明无解，输出 `-1` 即可。
# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n,k,ans,a[N],vis[N],now[N],bak;
string x,y;
main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			now[i]=now[i-1];
			scanf("%lld",&a[i]);
			vis[a[i]]++;
			while(vis[now[i]])now[i]++;
		}
		for(int i=0;i<n;i++)
			vis[i]=0;
		bool flag=1;
		bak=0;
		for(int i=n;i>=1;i--){
			vis[a[i]]++;
			while(vis[bak])bak++;
			if(now[i-1]==bak){
				flag=0;
				printf("2\n1 %lld\n%lld %lld\n",i-1,i,n);
				break;
			}
		}
		for(int i=0;i<n;i++)
			vis[i]=0;
		if(flag)puts("-1");
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 思路：

首先容易发现，最后答案的 $\operatorname{MEX}$ 肯定不是序列中出现过的数。

那么对于 $[l_1,r_1]$ 和 $[l_2,r_2]$ 这两段，如果其 $\operatorname{MEX}$ 相同，可以直接合并成 $[\min(l_1,l_2),\max(r_1,r_2)]$，其 $\operatorname{MEX}$ 是不变的。

所以题目中的求 $k$ 段 $\operatorname{MEX}$ 相同的都可以通过合并变成两段 $\operatorname{MEX}$ 即可，那么考虑第一个段的右端点 $i$，则第二个段的左端点为 $i+1$。

因为需要写一个支持删除和插入后求 $\operatorname{MEX}$ 的数据结构，所以可以用 ``set`` 维护当前序列中没有出现过的数，其 $\operatorname{MEX}$ 为集合最小值。

插入时将当前数在集合中删除；删除时要注意细节，如果当前数有多个则不变，只有一个就可以将该数添加到集合中。

时间复杂度为 $O(T N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll T,n,cnt;
ll a[N],b[N],l[N],r[N];
set<ll> S1,S2;
void Print(ll n){
	write(n);
	putchar('\n');
	for(int i=1;i<=n;i++){
		write(i);
		putchar(' ');
		write(i);
		putchar('\n');
	}
}
void solve(){
	memset(b,0,sizeof(b));
	bool f=1;
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[a[i]]++;
		f&=(a[i]!=0);
	}
	if(f){
		Print(n);
		return ;
	}
	S1.clear(),S2.clear();
	for(int i=0;i<=n;i++)
	  S1.insert(i),S2.insert(i);
	for(int i=1;i<=n;i++)
	  if(S2.count(a[i]))
	    S2.erase(a[i]);
	for(int i=1;i<n;i++){
		b[a[i]]--;
		if(!b[a[i]])
		  S2.insert(a[i]);
		if(S1.count(a[i]))
		  S1.erase(a[i]);
//		cerr<<*S1.begin()<<' '<<*S2.begin()<<'\n';
		if(*S1.begin()==*S2.begin()){
			puts("2");
			printf("1 %d\n",i);
			printf("%d %lld\n",i+1,n);
			return ;
		}
	}
	puts("-1");
}
int main(){
	T=read();
	while(T--)
	  solve();
	return 0;
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：CF1935B Informatics in MAC

[题目传送门](/problem/CF1935B)

~~不过洛谷文章区更新确实很舒服~~。。。

## 题意简述

有 $T$ 次询问，每次询问给长度为 $n$ 的数组，你要将其划分为 $k(1 < k \le n)$ 段，使得对每段的 $mex$ 值相等。如果没有方案，输出 $-1$；否则输出 $k+1$ 行：第一行一个正整数 $k$，表示划分成的段数；接下来 $k$ 行，每行两个正整数，表示每个区间的开始和结束。

**$mex$ 是对于可重集的函数，其取值为这个可重集内没有出现的最小的自然数**。

## 思路

首先，可以发现，如果两个相邻的区间都没有 $x$，那合并起来也一定没有 $x$。所以如果两个相邻的区间的 $mex$ 相等，那一定可以合并成一个区间。所以只需要考虑 $k=2$ 的情况就可以了。我们可以暴力在序列中找一个分割点，通过预处理前缀 $mex$ 和后缀 $mex$ 把复杂度降到 $O(n)$。总体复杂度为 $O(T\times n)$。

## 代码展示


```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define elif else if
#define fin(x) freopen (x,"r",stdin)
#define fout(x) freopen (x,"w",stdout)
#define rnt register int
#define reg(i,x,y) for (register int i=(x);i<=(y);++i)
#define Reg(i,x,y) for (register int i=(y);i>=(x);--i)
using namespace std;
namespace rwm {inline int read () {int s=0,w=0;char c=getchar ();while (!isdigit (c)){w|=(c=='-');c=getchar ();}while (isdigit (c)) {s=(s<<1)+(s<<3)+(c^48);c=getchar ();}return w?-s:s;}inline void write (int x) {if (x<0) putchar ( '-'),x=-x;if (x>9) write (x/10);putchar (x%10|48);}inline void writesp (int x) {write (x),putchar (' ');}inline void writeln (int x) {write (x),putchar ('\n');}inline int square (int x) {return x*x;}inline int floor (double x) {return x;}inline int ceil (double x) {return (int)(x+0.5);}inline int gcd (int x,int y) {int z=x%y;while (z) x=y,y=z,z=x%y;return y;}inline int lcm (int x,int y) {return x/gcd (x,y)*y;}};
using namespace rwm;
int T,n,a[100001],b[100001],c[100001];
inline void work (void)
{
	n=read ();
	reg (i,1,n) a[i]=read ();
	/*unordered_*/set<int> st;
	reg (i,0,n) st.insert (i);
	reg (i,1,n)
	{
		if (st.find (a[i])!=st.end ()) st.erase (a[i]);
		b[i]=*st.begin ();
	}
	reg (i,0,n) st.insert (i);
	Reg (i,1,n)
	{
		if (st.find (a[i])!=st.end ()) st.erase (a[i]);
		c[i]=*st.begin ();
	}
	reg (i,2,n)
		if (b[i-1]==c[i]) 
		{
			writeln (2);
			writesp (1),writeln (i-1);
			writesp (i),writeln (n);
			return ;
		}
	writeln (-1);
	return ;
}
signed main ()
{
	T=read ();
	while (T--) work ();
	return 0;
}

```

---

## 作者：Andy_WA (赞：0)

## 前置知识
$\operatorname{mex}$ 是一个数学术语，代表最小排除数 $\tt{Minimum~ Excluded}$。

所谓排除数，指的是在一组数中从小到大排列，存在的但未被选中的最小的正整数。例如，数列 ${1,2,4,5,7}$ 的 $\operatorname{mex}$ 为 $3$，数列 ${2,3,5,7}$ 的 $\operatorname{mex}$ 为 $1$。
## 分析题目
+ $2≤n≤10^5$
+ $0≤a_i<n$
+ $2≤k≤n$
## 题目思路
>求出原数组 $arr$ 的前缀和、后缀和 $\operatorname{mex}$，并枚举一个分割点——$i$，使得分割点左右两个序列的 $\operatorname{mex}$ 相等即可。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;//n的范围
int a[N];
void solve() {
	int n;
	cin >> n;
	map<int, int>mp;
	for (int i = 1; i <= n; i++) cin >> a[i], mp[a[i]] = 1;
	int mex = 0;
	for (int i = 0; i <= n; i++) {
		if (!mp[i]) {
			mex = i;
			break;
		}
	}
	vector<pair<int, int>>ans;
	mp.clear();
	int cnt = 0, lastl = 1;
	for (int i = 1; i <= n; i++) {//枚举mex的分界下标i
		if (a[i] < mex) {
			if (!mp[a[i]]) {
				mp[a[i]] = 1;
				cnt++;
			}
		}
		if (cnt == mex) {
			ans.push_back({lastl, i});
			lastl = i + 1;
			cnt = 0;
			mp.clear();
		}
	}
	if (ans.size() < 2) {
		cout << -1 << endl;
		return;
	}
	int id = ans.size();
	cout << id << endl;
	for (int i = 0; i <= id - 2; i++) cout << ans[i].first << " " << ans[i].second << endl;
	if (ans[id - 1].second != n) {
		cout << ans[id - 1].first << " " << n << endl;
	} else cout << ans[id - 1].first << " " << ans[id - 1].second << endl;
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		solve();//计算答案
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：0)

### 思路

将每个值出现的个数存起来，从小到大枚举每一个数，如果这个数出现个数为 $0$，则所有数的 $\operatorname{MEX}$ 值为这个数；如果这个数出现个数为 $1$，则一定不行，答案为 $-1$。

枚举每一个 $a_i$，如果 $a_i$ 能使当前数的 $\operatorname{MEX}$ 为整个数组的 $\operatorname{MEX}$，则一定可行。因为把剩下数放入下一个数组中一定也行。

若最终只分出一个完整的数组，则无解。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int a[N],w[N],l[N],r[N],n;
bool t[N];
void clean()//多测清空
{
    for(int i=0;i<n;i++)
    {
        w[i]=0;
        t[i]=0;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            w[a[i]]++;
        }
        bool flag=0;
        int c=0;//整组数的MEX
        for(int i=0;i<n;i++)
        {
            if(w[i]==1)
            {
                cout<<"-1\n";
                flag=1;//无解
                break;
            }
            if(w[i]==0)
            {
                c=i;
                break;
            }
        }
        if(flag==1)
        {
            clean();
            continue;
        }
        if(c==0)//整组数MEX为0
        {
            cout<<2<<"\n1 "<<n-1<<'\n'<<n<<' '<<n<<'\n';
            clean();
            continue;
        }
        int ans=1,u=c;//ans表示k
        l[1]=1;
        for(int i=1;i<=n;i++)
        {
            if(a[i]<c)
            {
                if(!t[a[i]])
                {
                    u--;
                    t[a[i]]=1;//已在数组中出现
                    if(u==0)//小与c的数均已在数组中出现
                    {
                        u=c;
                        r[ans]=i;
                        ans++;
                        l[ans]=i+1;
                        for(int j=0;j<c;j++)//清空统计数组，因为至少要个c次才会清空，所以不影响复杂度
                            t[j]=0;
                    }
                }
            }
        }
        if(u)ans--;//还有剩余，不是完整数组
        if(ans==1)//k>1
        {
            cout<<"-1\n";
            clean();
            continue;
        }
        r[ans]=n;//r[k]=n
        cout<<ans<<'\n';
        for(int i=1;i<=ans;i++)//输出答案
        {
            cout<<l[i]<<' '<<r[i]<<'\n';
        }
        clean();
    }
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题目大意

给你一个长度为 $n$ 的序列 $a$，要求分成若干段（段数不为 $1$），使得每段的 $\text{mex}$ 相同。

$1 \le n \le 10^5, 0 \le a \le n$。

## 题目思路

对于区间仔细分析后发现是可以合并的，具体来说：

- 对于 $\text{mex}(i, k) = \text{mex}(k + 1, j) = x$，可以得出 $\text{mex}(i, j) = x$。

简单证明一下就是考虑 $[i, k]$ 中没有出现 $x$，$[k + 1, j]$ 中也没有出现 $x$，那么 $[i, j]$ 中也没有出现 $x$，因此得 $\text{mex}(i, j) = x$。

那么问题就变得很简单了，因为划分 $k$ 段合法是划分 $2$ 段合法的充分条件，所以只要能划分出 $2$ 段就可以了，预处理前缀/后缀 $\text{mex}$ 就好了。

---

## 作者：Wf_yjqd (赞：0)

橙。

------------

看到划分 $k$ 段，直接考虑划分成 $2$ 段是否能判定无解。

显然，若存在一种 $\ge 3$ 段的划分方法，任意连续两个段合并后依然成立，所以我们直接求 $k=2$ 的情况。

维护前缀、后缀 $\operatorname{mex}$ 并找前缀和后缀相等的位置断点即可。

------------

写慢了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+26;
int T,n,a[maxn],cnt[2][maxn],mex[2][maxn];
bool b;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<=n;i++)
            cnt[0][i]=cnt[1][i]=0;
        mex[1][n+1]=mex[0][0]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            cnt[0][a[i]]++;
            mex[0][i]=mex[0][i-1];
            while(cnt[0][mex[0][i]])
                mex[0][i]++;
        }
        for(int i=n;i>=1;i--){
            cnt[1][a[i]]++;
            mex[1][i]=mex[1][i+1];
            while(cnt[1][mex[1][i]])
                mex[1][i]++;
        }
        b=0;
        for(int i=1;i<n;i++)
            if(mex[0][i]==mex[1][i+1]){
                printf("2\n1 %d\n%d %d\n",i,i+1,n);
                b=1;
                break;
            }
        if(!b)
            puts("-1");
    }
    return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

## 题意
把序列 $a$ 分成连续的 $k$ 段，要求 $k>1$，且每段的 $\operatorname{MEX}$ 相同，构造方案或报告不可能。

## 题解
首先，如果相邻的两端 $\operatorname{MEX}$ 相同，显然这两段合并之后 $\operatorname{MEX}$ 不变。这启示我们如果可行，一定可以把序列只分成两段。如果分成两端不可行，那么无解。

于是枚举要分开的前缀，需要查询区间的 $\operatorname{MEX}$，主席树一下就行。

时间复杂度 $O(n^2)$。

```cpp
#include<iostream>
#include<algorithm>
const int N = 1e5 + 10;
int T, n, c, a[N], mx[N<<5], ls[N<<5], rs[N<<5], rt[N];
inline void upd(int o, int &p, int l, int r, int x, int k){
    if(!p) p = ++c; int md = l + r >> 1;
    if(l==r) return void(mx[p]=k);
    if(x <= md) upd(ls[o], ls[p], l, md, x, k), rs[p]=rs[o];
    if(x > md) upd(rs[o], rs[p], md+1, r, x, k), ls[p]=ls[o];
    mx[p] = std::min(mx[ls[p]], mx[rs[p]]);
}
inline int qry(int p, int l, int r, int x){
    if(mx[p] >= x) return x + 1;
    if(l == r) return l; int md=l+r>>1;
    if(mx[ls[p]]<x) return qry(ls[p], l, md, x);
    else return qry(rs[p], md+1, r, x);
}
int main(){
    std::ios::sync_with_stdio(false);
    std::cin >> T; while(T--){
        int f = 0;
        std::cin >> n; rt[0] = ++c;
        for(int i = 1; i <= n; i++) rt[i] = 0;
        for(int i = 1; i <= n; i++)
            std::cin >> a[i], upd(rt[i-1], rt[i], 1, n, a[i]+1, i);
        for(int i = 1; i <= n && !f; i++){
            int l = qry(rt[i], 1, n, 1), r = qry(rt[n], 1, n, i+1);
            l--, r--; if(l == r){
                std::cout << "2\n1 " << i << '\n' 
                    << i+1 << ' ' << n << '\n'; f = 1;
            }
        }
        if(!f) std::cout << "-1\n";
    }
}
```

---

