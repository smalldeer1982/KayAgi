# [ABC372D] Buildings

## 题目描述

这里有 $N$ 栋房子，从 $1$ 到 $N$ 依次编号。它们按照顺序排成一排。第 $i(1\le i\le N)$ 的房子的高度为 $H_i$。 

对于每一个 $i=1,2,\dots,N$，找到满足以下条件的整数 $j(i<j\le N)$ 的数量：

- 没有一栋在 $i$ 和 $j$ 之间的房子比 $j$ 要高。

## 说明/提示

- $1\le N\le 2\times 10^5$
- $1\le H_i\le N$
- $H_i\not=H_j(i\not= j)$
- 所有输入都为整数

## 样例 #1

### 输入

```
5
2 1 4 3 5```

### 输出

```
3 2 2 1 0```

## 样例 #2

### 输入

```
4
1 2 3 4```

### 输出

```
3 2 1 0```

## 样例 #3

### 输入

```
10
1 9 6 5 2 7 10 4 8 3```

### 输出

```
2 3 3 3 2 1 2 1 1 0```

# 题解

## 作者：chatoudp (赞：7)

单调栈。

用单调栈求出每个建筑左边第一个比它高的建筑：$t_i$，如没有则：$t_i=0$。

我们可以发现：对于每个位置，以它做右端点，从 $t_i$ 到 $i-1$ 都可以作为左端点，其它位置则不行。于是我们可以用（~~线段树~~）差分进行区间加操作（把 $t_i$ 到 $i-1$ 的位置加 $1$）。

接下来是 AC 时间：

```cpp
#include <bits/stdc++.h>
#define I return
#define AK 0
#define IOI ;
#define itn int
#define Please int
#define AC main(){
#define pritnf printf
using namespace std;
typedef long long ll;
int ans[200005],n,a[200005],t[200005];
stack<int> st;
Please AC//'_' T_T ^_^
	scanf("%d",&n);
	for(int i=1;i<=n;i++) t[i]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		while(!st.empty()&&a[st.top()]<=a[i]) st.pop();
		if(!st.empty())t[i]=st.top();st.push(i); 
	}
	for(int i=1;i<=n;i++)
		ans[t[i]]++,ans[i]--;
	for(int i=1;i<=n;i++) ans[i]+=ans[i-1],printf("%d ",ans[i]);
	I AK IOI
}

```

---

## 作者：zlqwq (赞：7)

[Atcoder题面](https://atcoder.jp/contests/abc372/tasks/abc372_d)

## 正解：

考虑维护一个单调栈，每次将当前元素和栈顶元素作比较。

然后反向维护，就不用写前缀和了。


```cpp
#include<iostream>
#include<stack> 
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18

using namespace std;
const int N = 2e5 + 5;
int n,h[N],sum[N];
stack<int> stk;
signed main() {
	cin >> n;
	for(int i = 1;i <= n;++i) {
		cin >> h[i];
	}
	int ans = 0;
	for(int i = n;i >= 1;--i) {//蒟蒻太懒了
		sum[i] = stk.size();
		while(stk.size() && stk.top() < h[i]) stk.pop();
		stk.push(h[i]); 
	}
	for(int i = 1;i <= n;++i) {
		cout << sum[i] << " ";
	}
	return 0;
}

```

---

## 作者：hzxphy (赞：5)

## 题目大意
给定 $n$ 个数的数组 $H$，对每一个 $1\le i\le n$，求满足以下条件的个数：
- $i<j\le n$
- 在区间 $H(i,j]$ 中 $H_j$ 是最大的。
## 思路
从后往前搞，我们可以以样例为例：

1. 初始为 $[2,1,4,3,5]$。
2. $5$ 没有满足条件的 $j$。
3. $4$ 有满足条件的 $[5(H_5=5)]$。
4. $3$ 有满足条件的 $[4(H_4=3),5(H_5=5)]$。
5. $2$ 有满足条件的 $[3(H_3=4),5(H_5=5)]$。
6. $1$ 有满足条件的 $[2(H_2=1),3(H_3=4),5(H_5=5)]$。

很明显的单调队列好吧。

**Update：本质上是单调栈。**
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
int n,h[MAXN+1],ans[MAXN+1];
deque<int>Q;//双端队列

int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>h[i];
    }
    for(int i=n;i>=1;i--){
        ans[i]=Q.size();//应该在更新之前
        while(!Q.empty()&&h[Q.front()]<h[i]){
            Q.pop_front();//更新
        }
        Q.push_front(i);//插入新的数值
//        cout<<"***\n";
    }
//    cout<<"u\n";
    for(int i=1;i<=n;i++){
       cout<<ans[i]<<' ';
    }
    return 0;
}
```

---

## 作者：cjh_trailblazer (赞：2)

[at原题面](https://atcoder.jp/contests/abc372/tasks/abc372_d)
## 题目简述：
给 $n \le 2 \times 10^5$，$n$ 个数排成的序列，要求对每个序列位置中 $i \le n$ 和 $i< j \le n$ 而言，$i$ 和 $j$ 之间没有数比 $j$ 位置的数大。输出对于每个 $i$ 位置而言，$j$ 可取的位置数量。
## 题目分析：
注意到题目要求每个 $i$ 到 $j$ 之间没有数比 $j$ 大，暴力跑肯定会炸，需要考虑线性复杂度。

容易发现，对于 $j$ 而言，从前往后维护无法做到线性，考虑从后往前维护。  
~~由于我画图软件炸了，各位自己画个图~~。发现对于所处位置若想被选取，该数需要比下一个数大。换言之，对于该数来说，所有前面比它小的都能计入答案，所以我们需要维护一个具有单调性的序列，考虑使用单调栈。

维护单调栈单调递减，这样对于每一个新数而言，其答案数即为栈中元素数量。压入前，对栈顶元素大小进行判断，维护其单调递减性质即可。
## 代码：

```cpp
#include<bits/stdc++.h>
#define starrail main
#define int long long
#define lowbit(x)  (x&(-x))
#define re register
using namespace std;
inline int read(){
	int w=1,s=0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-') w=-1;ch=getchar();}
	while(isdigit(ch)){s=s*10+(ch-'0');ch=getchar();}
	return w*s;
}
const int N=2e5+10;
int n,a[N],ans[N];
stack<int>st;
signed starrail(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	reverse(a+1,a+1+n);
	for(int i=1;i<=n;i++){
		ans[i]=st.size();
		while(!st.empty()&&st.top()<a[i])	st.pop();
		st.push(a[i]);
	}
	for(int i=n;i>=1;i--)	cout<<ans[i]<<' ';
	return 0;
}


```

---

## 作者：hjyowl (赞：2)

### 题目大意

给定 $n$ 个数，请你求出对于每个 $i$，有多少个 $j$ 满足两点之间没有任何一个位置的高度大于 $j$ 的高度。

### 思路

考虑定住右端点。

首先使用跳表预处理出任意两点之间的最大值。

接下来考虑使用二分枚举左端点，这里有很显然的单调性，就是离当前右端点越近的点越有可能成功。

二分出了最极限情况下的左端点过后，直接使用差分数组对极限的左端点到 $i$ 减一之间全部加一，最后输出即可。

### 时间复杂度

很明显，二分和跳表预处理是瓶颈，故时间复杂度 $\Theta(n \log n)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010, M = 18;
int n, m;
int w[N];
int f[N][M];
int mp[N];
int s[N];
void init(){
	for (int j = 0; j < M; j ++ ){
		for (int i = 1; i + (1 << j) - 1 <= n; i ++ ){
			if (!j){
				f[i][j] = w[i];
			}
			else{
				f[i][j] = max(f[i][j - 1],f[i + (1 << j - 1)][j - 1]);
			}
		}
	}
}
int query(int l,int r){
	int len = r - l  + 1;
	int k = log(len) / log(2);
	return max(f[l][k],f[r - (1 << k) + 1][k]);
}
int main(){
	cin >> n;
	for (int i = 1; i <= n; i ++ ){
		cin >> w[i];
	}
	init();
	for (int i = 1; i <= n; i ++ ){
		int l = 1,r = i - 1;
		while (l < r){
			int mid = l + r >> 1;
			if (query(mid + 1,i) == w[i]){
				r = mid;
			}
			else{
				l = mid + 1;
			}
		}
		s[l] ++ ,s[i] -- ;
//		for (int j = i - 1; j >= 1; j -- ){
//			if (query(j + 1,i) == w[i]){
//				mp[j] ++ ;
//			}
//			else{
//				break;
//			}
//		}
	}
	for (int i = 1;i <= n; i ++ ){
		s[i] += s[i - 1];
		cout << s[i] << " ";
	}
	return 0; 
}
```

---

## 作者：Dtw_ (赞：1)

# 题意
长度为 $N$ 的数列，对于所有的 $i$ 求有多少 $j$ 满足 $[i, j]$ 中的数都不大于 $a_j$。
# Solution
首先，对于 $i$ 求有点麻烦，所以我们可以对于每个 $j$ 算一个最小的 $i$，那么 $[i,j]$ 里的 $i$ 就都满足。

所以可以用单调栈维护出，最后一个大于 $a_i$ 的数，那么当 $i$ 作为 $j$ 出现的时候，栈顶元素的下标到 $i-1$ 这一段都是合法的，区间加，所以差分一下就好。
# Code

```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define fi first
#define se second

#define int long long

#define pii pair<int, int>

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

const int INF = 0x3f3f3f3f3f3f3f3f;

const int P = 998244353;

const int N = 1e6 + 10;

int n, h[N], a[N];

signed main()
{
    fst
	cin >> n;
	for (int i=1; i<=n; i++) cin >> h[i];
	stack<pii> st;
	st.push({h[1], 1});
	for (int i=2; i<=n; i++)
	{
		while (st.size() && st.top().fi <= h[i]) st.pop();
		if (st.empty()) a[1]++, a[i]--;
		else a[st.top().se]++, a[i]--;
		st.push({h[i], i});
	}
	for (int i=1; i<=n; i++) a[i] += a[i-1], cout << a[i] << " ";
	return 0;
}



```

---

## 作者：Malkin_Moonlight (赞：1)

# 题解：AT_abc372_d [ABC372D] Buildings

对于每个 $i$，设 $J_i$ 为按升序排序的符合条件的 $j$ 序列，使得 $H_{J_{i,1}} < H_{J_{i,2}} < H_{J_{i,3}} < \ldots$ （1）成立。

对于 $i \neq N$，关注 $J_{i+1}$ 和 $J_i$ 之间的差异。$J_i$ 总是包含 $(i+1)$。因此，任何满足 $H_{i+1} > H_j$ 的 $j \in J_{i+1}$ 都不包含在 $J_i$ 中。同时，任何满足 $H_{i+1} < H_i$ 的 $j \in J_{i+1}$ 始终包含在 $J_i$ 中。根据（1），可以通过以下步骤从 $J_i$ 得到 $J_{i+1}$：

1. 设 $A = J_{i+1}$。
2. 当 $A$ 非空时，重复以下操作：
    - 取 $A$ 的初始元素 $j$。如果 $H_{i+1} > H_j$，则从 $A$ 中移除 $j$。
    - 否则，终止此循环。
3. 将 $(i+1)$ 推入 $A$ 的前面。
4. 当前的 $A$ 即为 $J_i$。

管理最后一个元素比第一个元素更为方便，我们可以用反向顺序管理 $J_i$。现在可以使用像栈这样的数据结构。

时间复杂度为 $O(N)$。

---

## 作者：Your_Name (赞：1)

## 题意
给一个序列 $a_1...a_N$ 求对于每一个 $i$ 有多少个 $j$ 满足：
* $i < j \le N$。
* $\forall k$ 满足 $i<k<j$ 有 $a_k<a_j$。

$a$ 数组无重复元素。
## 思路
这里提供一种冷门的做法。

首先，我们看出，对每个 $(i,j)$ 他们之间的所有元素都小于 $a_j$。

所以我们可以从 $a_{i+1}$ 用单调栈直接找到比他大的第一个元素，然后重复这一过程，跳了多少次再加上 $i+1$ 本身就是满足条件的 $j$ 的个数。

正确性简单证明一下：

因为每次找的是一个大于本身的数，所以在两个元素之间的所有元素都严格小于两个元素。重复操作同理。

当然，每次跳还是 $O(n^2)$ 的，所以直接用 st 表跳，每跳一次，答案就加上 $2^j$ 即可。

## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int n, a[N], f[N][21];
stack<int> st;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
        while(!st.empty() && a[st.top()] < a[i]){
            f[st.top()][0] = i;
            st.pop();
        }
        st.push(i);
    }//单调栈计算每个元素第一个比他大的下标
    for(int j = 1; j < 20; j ++){
        for(int i = 1; i <= n; i ++){
            f[i][j] = f[f[i][j - 1]][j - 1];
        }
    }//预处理st表
    for(int i = 1; i <= n; i ++){
        if(i == n){
            cout << 0;
            return 0;
        }//特判
        int k = i + 1, ans = 0;
        for(int j = 19; j >= 0; j --){
            if(f[k][j] != 0){//能跳
                k = f[k][j];//跳
                ans += (1 << j);//跳了2^j步，累计答案
            }
        }
        cout << ans + 1 <<' ';//加上i+1本身。
    }
    return 0;
}
```
 _完结撒花_

---

## 作者：xvl_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc372_d)

一道数据结构题。

发现对于每个 $i$ 要求的是 $\sum\limits_{j=i+1}^{n}[\max\limits_{k=i+1}^{j-1}a_k\le a_j]$。

如果正着考虑较为难算，因为 $j$ 不存在任何有用的性质，那不妨反着思考：对于每一个 $j$ 看会对哪些 $i$ 做贡献。

由于 $a_j$ 是个定值，所以 $\max\limits_{k=i+1}^{j-1}a_k\le a_j$ 有了单调性，因为最大值只会越来越大。那么就可以二分最小的 $i$，并将区间 $[i,j)$ 的答案全部加 $1$，可以差分解决。

二分时求区间最大值可用 ST 表解决。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

using ll = long long;
using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ {
    #define SP(n, x) std :: setprecision(n) << std :: fixed << x
    #define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
    #define fst first
    #define snd second
    template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
    template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int N = 200005;
int n;
int p[N], st[N][25], lg[N], ans[N];
int query(int l, int r) { return Max(st[l][lg[r - l + 1]], st[r - (1 << lg[r - l + 1]) + 1][lg[r - l + 1]]); }
void add(int l, int r) { ans[l] += 1, ans[r + 1] -= 1; }
int f(int l, int r, int pos) {
	int res = pos;
	while (l <= r) {
		int mid = l + r >> 1;
		if (mid + 1 > pos - 1 or query(mid + 1, pos - 1) <= p[pos]) {
			res = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return res;
}
int main() {
    // freopen("InName.in", "r", stdin);
    // freopen("OutName.out", "w", stdout);
    ios :: sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i], st[i][0] = p[i];
    lg[0] = -1;
    for (int i = 1; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= 20; i++) {
    	for (int j = 1; j <= n; j++) {
    		if (j + (1 << i - 1) <= n) st[j][i] = Max(st[j][i - 1], st[j + (1 << i - 1)][i - 1]);
    	}
    }
    for (int i = 1; i <= n; i++) add(f(1, i, i), i - 1);
    for (int i = 1; i <= n; i++) {
    	ans[i] = ans[i - 1] + ans[i];
    	cout << ans[i] << ' ';
    }
    return 0;
}
```

---

## 作者：Exscallop64_ (赞：0)

## AtCoder abc372_d

### 题目简述

有 $n$ 个正整数，第 $i$ 个数为 $h_i$，试求对于所有的 $1 \le i \le n$ 求以下式子的值。

$$
\sum_{j=i+1}^{n} {[\max_{k=i+1}^{j} {h_k} = h_i]}
$$

即对于 $i$ 来言，求有多少个 $j$，使得 $h_j$ 是 $h_{i+1} \sim h_j$ 中最大的。

### 思路

提供一种非单调栈的做法。

我们不妨反过来求，对于当前 $j$，能对哪些 $1 \le i < j$的答案加 $1$。

我们定义 $[i,j]$ 可行当且仅当 $\max_{k=i+1}^{j} {h_k} = h_i$。

可以发现，若 $[i, j]$ 可行，则 $[i+1,j]$ 也可行（最大值是有单调性的）。

因此，对于所有 $1 \le j \le n$ 可以二分找到最小的 $1 \le i \le j$，使得 $[i,j]$ 可行， 而对于所有 $i \le k < j$的 $k$ 答案加 $1$
，可以进行差分。

检查答案是否可行的函数需要判断 $[x, j]$ 是否可行（$x$ 为二分得到的答案），而区间最大值可以使用ST表维护。

### 复杂度分析

+ 时间复杂度：对于所有 $1 \le j \le n$ 进行求解 $O(n)$，二分 $O(\log n)$，总时间复杂度 $O(n \log n)$。

+ 空间复杂度：$h$ 数组即差分数组空间复杂度为 $O(n)$，ST表空间复杂度 $O(n \log n)$， 总空间复杂度 $O(n \log n)$。

PS：由于 $\max$ 有幂等律，因此查询ST表的时间复杂度可从 $O(\log n)$ 优化为 $O(1)$。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5, X = 18;

int n, h[N], d[N];
int st[X][N], log_2[N];

void init(){
  for(int i = 1; i <= n; i++){
  	st[0][i] = h[i];
  }	
  for(int x = 1; x < X; x++){
  	for(int i = 1; i + (1 << x) - 1 <= n; i++){
  	  st[x][i] = max(st[x - 1][i], st[x - 1][i + (1 << x - 1)]);	
	}
  }
  for(int i = 2; i <= n; i++){
  	log_2[i] = log_2[i >> 1] + 1;
  }
}

int query(int l, int r){
  int lg = log_2[r - l + 1];
  return max(st[lg][l], st[lg][r - (1 << lg) + 1]);
}

bool check(int l, int r){
  int mx = query(l + 1, r);
  return mx == h[r]; 
}

int two_search(int R){
  int l = 1, r = R - 1;
  while(l < r){
  	int mid = (l + r) >> 1;
	check(mid, R) ? r = mid : l = mid + 1;   
  }	
  return l;
}

int main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for(int i = 1; i <= n; i++){
  	cin >> h[i];
  }
  init();
  for(int r = 1; r <= n; r++){
  	int l = two_search(r);
  	d[l]++, d[r]--;
  }
  for(int i = 1; i <= n; i++){
  	d[i] += d[i - 1];
  	cout << d[i] << " ";
  }
  return 0;
}
``````

---

## 作者：rainbow_cat (赞：0)

我们可以先考虑暴力做法。   
对于每个 $i$ 维护一个最大值 $mx$ 以及一个指针 $j$。若 $h_j>mx$ 则答案加一。但这个做法会超时，问题也显而易见，对于每个 $i$ 都会做一次统计。   
为了解决这个问题，我们把原序列倒过来，再使用树状数组记录比当前建筑高的建筑中，编号的最大值。   
维护一个 $ans$ 数组逐步计算即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],b[200010],dp[200010],bit[200010];
int lowbit(int x){return x&-x;}
void add(int x,int y){for(;x;x-=lowbit(x))bit[x]=max(bit[x],y);}
int query(int x)
{
	int res=0;
	for(;x<=n;x+=lowbit(x))res=max(res,bit[x]);
	return res;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[n-i+1]=a[i];
	for(int i=1;i<=n;i++)
	{
		dp[i]=dp[query(b[i])]+1;
		add(b[i],i);
	}
	for(int i=1;i<n;i++)cout<<dp[n-(i+1)+1]<<' ';
	cout<<0;
	return 0;
}
```
注：似乎只有我写了树状数组，虽然其时间复杂度为 $O(n \log n)$，劣于单调栈的 $O(n)$，但也是可以通过此题的。

---

## 作者：cheng2010 (赞：0)

## Buildings

### 思路
对于一个 $i$，设 $lst_i$ 为下一个大于等于 $h_i$ 的 $h$ 的编号，再设 $f_i$ 为 $i$ 可以用 $lst$ 跳多少下，转移即为 $f_i=f_{lst_i}+1$，注意逆序枚举。

### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+7;
int n;
int h[N];
int lst[N];
stack<int> q;
int f[N];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	for(int i=1;i<=n;i++)
	{
		while(!q.empty()&&h[q.top()]<=h[i])
			lst[q.top()]=i,q.pop();
		q.push(i);
	}
	for(int i=n;i>=1;i--)
		f[i]=f[lst[i]]+1;
	for(int i=1;i<=n;i++)
		printf("%d ",f[i+1]);
}
```

---

## 作者：doumingze (赞：0)

题目里是找 $i$ 位置后面的有多少个 $j$ 位置满足 $\forall k \in (i, j), H_k < H_j$。那我们反向考虑：求解 $i$ 前面有哪些 $j$ 符合 $\forall k \in (j, i), H_k < H_i$。

那么我们就可以找到 $i$ 位置前面第一个严格大于 $H_i$ 的 $H_j$（如果不存在这样的 $j$，就令$j = 0$），这样根据题意，$j$ 前面的任何一个 $k$ 位置（不包括 $j$）在统计答案的时候 $i$ 都不会对它们产生贡献（因为在区间 $(k, i)$ 中由于 $k < j$，所以可以找到一个位置不符合题意且这个位置就是 $j$）。

根据上面的这段话，容易发现一个 $i$ 会对区间 $[j, i)$ 产生贡献，于是直接差分就可以了。而找一个位置前面第一个比它大的位置，最简单的方法就是维护一个单调栈，具体地，栈底到栈顶单调不上升，每次加入一个位置的时候先弹栈维持单调性，弹完之后的栈顶就是满足条件的位置，你就有产生贡献的区间了。这样就可以了。

时间复杂度 $O(n)$，码长是几乎没有的。

具体看 [link](https://atcoder.jp/contests/abc372/submissions/57971445) 去。

---

