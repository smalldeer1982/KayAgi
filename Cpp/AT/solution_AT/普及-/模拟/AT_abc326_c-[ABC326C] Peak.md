# [ABC326C] Peak

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc326/tasks/abc326_c

高橋くんは数直線上に $ N $ 個のプレゼントを置きました。そのうち $ i $ 個目のプレゼントは座標 $ A_i $ に置かれました。

あなたは数直線上の長さ $ M $ の半開区間 $ [x,x+M) $ を選び、そこに含まれるプレゼントを全て獲得します。  
 より詳しくは、以下の手順でプレゼントを獲得します。

- まず、実数 $ x $ をひとつ選択する。
- その後、プレゼントのうち置かれている座標が $ x\ \le\ A_i\ <\ x+M $ を満たすものを全て獲得する。
 
最大でいくつのプレゼントを獲得することができますか?

## 说明/提示

### 制約

- 入力は全て整数
- $ 1\ \le\ N\ \le\ 3\ \times\ 10^5 $
- $ 1\ \le\ M\ \le\ 10^9 $
- $ 0\ \le\ A_i\ \le\ 10^9 $
 
### Sample Explanation 1

例えば、半開区間 $ [1.5,7.5) $ を指定します。 このとき、座標 $ 2,3,5,7 $ にある $ 4 $ つのプレゼントを全て獲得することができ、これが獲得可能な最大の個数です。

### Sample Explanation 2

同一の座標に複数のプレゼントが置いてあることもあります。

## 样例 #1

### 输入

```
8 6
2 3 5 7 11 13 17 19```

### 输出

```
4```

## 样例 #2

### 输入

```
10 1
3 1 4 1 5 9 2 6 5 3```

### 输出

```
2```

## 样例 #3

### 输入

```
10 998244353
100000007 0 1755647 998244353 495 1000000000 1755648 503 1755649 998244853```

### 输出

```
7```

# 题解

## 作者：rainygame (赞：3)

感觉难度大于普通的 C。

首先 $x$ 一定在某个 $A_i$ 上面，因为这样一定会更优。

然后用一个指针 $r$ 表示在答案区间里面最右边的是 $A_r$。可以发现随着 $x$ 的右移，$r$ 也会右移，可以在右移的同时统计答案。因为 $x$ 只扫了一遍，$r$ 也是，所以复杂度为 $O(n)$。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, m, r, ans;
int a[300001];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i(1); i<=n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    a[n+1] = INT_MAX;
    for (int i(1); i<=n; ++i){
        while (r <= n+1 && a[i]+m > a[r]) ++r;
        ans = max(ans, r-i);
    }

    cout << ans;

    return 0;
}

```


---

## 作者：kimidonatsu (赞：2)

# AT_abc326_c [ABC326C] Peak 题解

关于题目中对区间的定义是左开右闭：对于一个坐标 $x$，我们能获取的礼物是 $x + 1, x + 2, x + 3, \dots, x + M - 1$，注意不能获取 $x + M$ 坐标上的礼物。

虽然坐标达到了 $10^9$ 级别，但是实际上总的礼物个数只有 $3 \times 10^5$ 个，考虑从礼物个数入手。

记录每个礼物在数轴上的坐标为 $a_i$，然后进行从小到大的排序，对于第 $i$ 个礼物的位置 $a_i$，往右延伸右指针 $r$ 直到距离 $a_r - a_i \lt M$，记录 $r - i$ 即为能获取的礼物总数。

当然也可以上二分或者滑动窗口优化。

```cpp
#include <bits/stdc++.h>

using i64 = long long;
constexpr i64 INF = 1e18;

void solve() {
	i64 n, m;
	std::cin >> n >> m;
	std::vector<i64> a(n + 5);
	for (i64 i = 1; i <= n; i++)
		std::cin >> a[i];
	std::sort(a.begin() + 1, a.begin() + n + 1);
	a[n + 1] = INF;
	i64 ans = -INF;
	i64 r = 1;
	for (i64 i = 1; i <= n; i++) {
		while (a[r] < a[i] + m)
			r++;
		ans = std::max(ans, r - i);
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	solve();
	return 0;
}

```


---

## 作者：xxr___ (赞：1)

### 思路：
直接按题意从一枚举一遍，枚举每次用二分求大于这个数的个数，不断更新最大值即可，注意二分前需要排序，我这个蒟蒻就因为忘了排序调了十分钟。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=300005;
int a[N];
bool cmp(int x,int y){
	return x<y;
}
int main(){
	int n,m,maxn=-1;
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	for(int i=1;i<=n;++i){
		int pos=lower_bound(a+1,a+n+1,a[i]+m)-a -i;
		maxn=max(maxn,pos);
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：Forever_LYD (赞：1)

很水的一道题，不需要二分加前缀和优化，基本思路就是弄一个区间窗口扫描，双指针也可，使得该区间礼物数量最多(求取最大值)扫描前记得要先排序，时间为排序的复杂度。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn =1e6+5;
int a[maxn];
int tot=-1,c=1,aa=1;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    while(c<=n){
        if(a[c]-a[aa]<m) c++;
        else aa++;
        if(c-aa>tot)tot=c-aa;
    }
    cout<<tot<<endl;
    return 0;
}
```


---

## 作者：Zikake (赞：1)

# 题意
给你 $ n $ 个数，让你求出 $ l $ 和 $ r $，让 $ a_l $ 到 $ a_r $ 的差小于 $ m $，并让 $ r-l+1 $ 最大。

# 思路
把 $ n $ 个数排序，用双指针求出 $ l $ 和 $ r $。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5+10;
int n,w;
int a[N];
signed main()
{
	cin>>n>>w;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);//排序 
	int l=1;//双指针l 
	int ans=INT_MIN;
	for(int i=1;i<=n;i++){//i为双指针r 
		if(a[i]-a[l]<w){//注意为小于 
			ans=max(ans,i-l+1);
		}else{
			l++;
		}
	}
	cout<<ans<<endl;//输出答案 
	return 0;
}


```


---

## 作者：FreedomKing (赞：1)

### 思路

简单题，直接用二分寻找每个 $a_i$ 对应的最远的礼物。

事实上，按照题意使用 `lower_bound` 有些许的麻烦，要处理一些奇奇怪怪的东西，用 `upper_bound` 去找以每个 $a_i$ 为区间右端点的左边最远的物品即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],b[N],n,m,t,k,ans;
vector<int>e[N];
stack<int>st;
bool vis[N];
queue<int>q;
string s;
inline int qread(){
#define qr qread()
	int x=0,c=getchar(),t=1;
	while(c<'0'||c>'9'){
		if(c=='-') t=0;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=(x<<3)+(x<<1)+c-'0';
		c=getchar();
	}
	return (t?x:-x);
}
inline int qpow(int x,int p,int mod){
	x=(p?x:1);
	mod=(mod?mod:LONG_LONG_MAX);
	int t=1;
	while(p>1){
		if(p&1) t=(t*x)%mod;
		x=(x*x)%mod;
		p>>=1;
	}
	return (x*t)%mod;
}
signed main(){
	n=qr;m=qr;
	for(int i=1;i<=n;i++) a[i]=qr;
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=1;i<=n;i++){
		int pos=upper_bound(a+1,a+n+1,a[i]-m)-a;
		ans=max(ans,i-pos+1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：N_Position (赞：1)

# AT_abc326_c
## 题目翻译
有 $n$ 个物品，第 $i$ 个物品位于 $a_i$ 处，现在你可以拿走 $[x,x+m)$ 这个区间内的物品，问最多能拿走几个物品。

## 题目分析
显然要将物品按位置从小到大排序。

本题主要有两种方法。

+ 法一：二分查找，时间复杂度为 $O(n\log{n} +n\log{n})$；
+ 法二：双指针，时间复杂度为 $O(n\log{n}+n)$。

对于法一，枚举每一个可能的终点，二分查找最小的对应的起点即可。

法二则是在法一基础上的延伸，每在右边新加入一个物品，左边便可能会少几个物品。即只需要判断最左侧物品是否过期即可。时间复杂度为 $O(n\log{n}+n)$。

## 代码实现

法二的关键代码，其中 $l$ 为左侧商品的下标，$ans$ 为长度：
```cpp
for(int i=1;i<=n;i++){
	ans ++;
	if(a[i] - a[l] >= m){
		l++;
		ans--;
	}
	max_ans = max(ans,max_ans);
}
```
[法二完整代码](https://www.luogu.com.cn/paste/ozu6eqd4)

---

## 作者：2huk (赞：1)

二分答案入门题。

首先我们二分答案 $mid$，表示题意中可以选择多少个能被区间包含的点。然后判断其是否合法。若是，则尝试往大里找，否则往小里找。关键是如何判断其是否合法。

很显然的，只要存在一个长度为 $mid$ 的区间 $[l, r]$，使得 $a_l$ 与 $a_r$ 的距离够小，可以被 $[x, x + M)$ 这个区间包括，就代表这是一种合法方案。这也就转化成了是否有 $a_l + M > a_r$，表示在 $x = a_l$ 时，区间 $[x, x + M)$ 是否能够包含住 $a_r$。保证这一步的正确性需要提前将 $a_i$ 从小到大排序。

```cpp
int n, a[N], m;

bool chk(int mid)
{
	for (int l = 1, r = mid; r <= n; ++ l, ++ r )
		if (a[r] < a[l] + m)
			return true;
	return false;
}

signed main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i ) cin >> a[i];
	sort(a + 1, a + n + 1);
	
	int l = 0, r = n, res;
	
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (chk(mid)) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	
	cout << res;
	
	return 0;
}
```



---

## 作者：_ZML_ (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_abc326_c)

## 题目思路
这个问题要求找到一个半开区间，使得在这个区间内包含尽可能多的礼物。首先，我们需要将输入的礼物坐标按照从小到大的顺序进行排序。然后，我们可以使用双指针的方法来寻找最佳的区间。

# 代码
以下是代码解释：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
#define int long long
int a[maxn];
int sum[maxn];
int n,len;

// 去除重复的坐标
void uni(){
    int m=0;
    a[0]=-1;
    for(int i=1;i<=n;i++){
        if(a[i]!=a[i-1]) a[++m]=a[i];
    }
    n=m;
}

signed main(){
    ios::sync_with_stdio(0);
    cin>>n>>len;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    
    // 去除重复的坐标
    uni();
    
    int i=n,j=n,ans=0;
    while(i>=1&&j>=1){
        ans=max(ans,j-i+1); // 记录当前区间的长度
        if(j<i) i=j; // 如果 j < i，则将 i 设置为 j，表示需要向右移动 i 来扩大区间
        if(a[j]-a[i-1]<len) i--; // 如果区间长度小于 len，向左移动 i，扩大区间
        else j--; // 否则向左移动 j，缩小区间
    }
    cout<<ans;
    return 0;
}
```

# 高清无码代码



---

## 作者：__Emerald__ (赞：1)

## 如何解决此题
这题很明显，$x$ 应取 $A$ 数组里一元素。

我们可以用数组 $num$ 存储对于 $x$ 为每一个 $A_i$ 的答案，然后求出其最大值并输出即可。

那么如何得到这个答案？设 $A$ 是已经排好序的，$x=A_i$，你可以二分查找 $A$ 中最后一个小于 $x+M$ 的位置，$num_i$ 就是那个位置减去 $i$ 加 $1$，因为 $A$ 的第一个在区间 $[x,x+M)$ 的位置就是 $i$，而最后一个位置就是刚才计算得到的位置。

这种做法时间复杂度为 $O(N\log N)$。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a[300005],num[300005],mx = 0;
int main(){
	cin >> n >> m;
	for (int i = 1;i <= n;i++) cin >> a[i];
	sort(a + 1,a + n + 1);
	for (int i = 1;i <= n;i++){
		int l = i,r = n,mid;
		while (l <= r){
			mid = l + r >> 1;
			if (a[mid] < a[i] + m && a[mid + 1] >= a[i] + m) break;
			if (a[mid] < a[i] + m) l = mid + 1;
			else r = mid;
		}
		num[i] = mid - i + 1;
	}
	for (int i = 1;i <= n;i++) mx = max(mx,num[i]);
	cout << mx;
	return 0;
}
```
[AC记录](https://atcoder.jp/contests/abc326/submissions/47140052)

---

## 作者：_RainCappuccino_ (赞：1)

# 题意简述

> 给你 $n$ 个物品和他们的坐标 $a_i$，求坐标区间 $\left [ x,x+m \right ) $ 内的最大物品数量。

# $\mathtt{problem.1}$ 区间枚举
最先想到的是标记坐标，然后按坐标枚举区间，取最大值。

这样绝对是会超时的。

不妨考虑从每个礼物的坐标出发，寻找 $\left [a_i,a_i+m \right)$ 中的元素个数。

这样的区间一定能包含一个物品，所以应该从他们出发，省去许多不必要的区间。

# $\mathtt{problem.2}$ 快速求出这个区间中的元素个数

由于本题坐标值域很大，所以先对坐标排序，考虑每个区间中最后包含的元素是哪一个，然后就能 $O(1)$ 求出一个以物品坐标为左端点的区间物品个数。

即，求出第一个坐标小于 $a_i + m$ 并且大于等于 $a_i$ 的元素。

可以使用二分以 $O(\log n)$ 的时间复杂度解决。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
int a[300010];
int main(){
	cin >> n >> m;
	for (int i = 1; i <= n; i ++){
		cin >> (a + i)[0];
	}
	sort(a + 1, a + 1 + n);
	int ans = 0;
	for (int i = 1; i <= n; i ++){
		int l = i, r = n;
		while(l < r){//二分找出第一个小于 a[i]-m 的数
			int mid = (l + r + 1) >> 1;
			if(a[mid] - a[i] >= m) r = mid - 1;
			else l = mid;
		}
		ans = max(ans, l - i + 1);
	}
	cout << ans << endl;
	return 0;
}
```

# 后言

其实此题有更优秀的方法，不算排序 $O(n)$ 解决的双指针做法。

但是~~我不会~~我要另辟蹊径。

---

## 作者：sfqxx1 (赞：1)

## 题意

Takahashi 在数字线上放置了 $N$ 个礼物。第 $i$ 个礼物放置在坐标 $A_i$ 处。

您将在数轴上选择长度为 $M$ 的半开区间 $[x,x+M)$，并获得其中包含的所有礼物。

求最多可以获得多少份礼物？

## 思路

可以先把列表排序，然后直接按照题意进行枚举即可。

## 代码

```
N, M = map(int, input().split())
A = list(map(int, input().split()))
A_2 = sorted(A)
r = 0
ans = 0
for l in range(N):
    while r < N and A_2[r] < A_2[l] + M:
        r += 1
        ans = max(ans, r - l)
print(ans)
```

---

## 作者：Jamal_Musiala (赞：0)

## ABC326C

最简单的思路是对整个数轴开桶记录，但是这样空间会炸掉。

但是我们考虑到桶的大部分位置都是没有意义的，只有放礼物的位置作为区间端点时才有可能取到最大值作为答案。

于是我们可以只考虑每个礼物的坐标作为左端点统计答案。

排序 + 前缀和后二分或者双指针即可。

时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
const int N = 5e5 + 7;
const int mod = 1e9 + 7;
int n,m;
int s[N];
int ans;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>s[i];
	sort(s+1,s+n+1);
	for(int i=1;i<=n;++i){
		int l = i,r = n,cur = 0;
		while(l<=r){
			int mid = (l+r)/2;
			if(s[mid]<s[i]+m) l = mid + 1,cur = mid;
			else r = mid - 1;
		}
		ans = max(ans,cur-i+1);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：indream (赞：0)

# \[ABC326C] Peak 题解
[洛谷](https://www.luogu.com.cn/problem/AT_abc326_c) | [AtCoder](https://atcoder.jp/contests/abc326/tasks/abc326_c)

## 思路
### 错解
排序后暴搜会时间会超(AtCoder 实测 TLE\*18)，复杂度为 $O(n^2-n)$。
```
#include<bits/stdc++.h>
using namespace std;
int a[300005],n,m,cnt,ans=-1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>a[i];
    sort(a,a+n);
    for(int i=0;i+1<n;i++){
        cnt=1;
        for(int j=i+1;j<n && a[i]+m>a[j];j++)//查找区间有多少礼物
            cnt++;
        if(cnt>ans)//更新答案
            ans=cnt;
    }
    cout<<ans;
    return 0;
}
```
---
### 正解
先排序，然后利用 `lower_bound()` 可以以 $O(\log n)$ 的时间复杂度实现二分查找允许的坐标最大的礼物，每次更新最大值即可。加上外层循环，最大复杂度为 $O(n \log n)$。
```
#include<bits/stdc++.h>
using namespace std;
int a[300005],n,m,cnt,ans=-1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>a[i];
    sort(a,a+n);//二分查找需要排序
    for(int i=0;i+1<n;i++){
        cnt=lower_bound(a,a+n,a[i]+m)-a-i;
        //-i前是从a[0]至a[n]中有多少礼物坐标小于a[i]+m
        //-i是去掉前i个礼物，即现在为a[i]到a[n]间符合要求的礼物数
        if(cnt>ans)//更新答案
            ans=cnt;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：rainbow_cat (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_abc326_c)    
[博客链接](https://www.luogu.com.cn/blog/533160/solution-at-abc326-c)   
### 思路：
这道题的二分做法比较好想。    
很明显，将区间的开头放在一个礼物上的答案最优。   
那么我们在进行排序后二分终点，与起点相减就可以了。    
这里可以直接使用自带的 `lower_bound()`。      
时间复杂度：$O(n \log n)$       
[惨遭AC](https://www.luogu.com.cn/record/133072859)    
[lower_bound() oiwiki链接](https://oi-wiki.org/basic/binary/)
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[300010],ans;
int find(int st,int x,int y)
{
	int ed=lower_bound(a+1,a+n+1,y)-a;//只需要二分终点
	return ed-st;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)ans=max(ans,find(i,a[i],a[i]+m));//把起点放在一个礼物的价格上使答案最有
	cout<<ans;
	return 0;
}
```    
（注：同学有用双指针通过的，时间复杂度为 $O(n)$ 更优）

---

## 作者：InversionShadow (赞：0)

首先先对位置从小到大排序。

贪心的思考，什么时候最优：肯定是区间 $[l,l+m)$ 中包含了物品，也就是说我们枚举的区间就是 $[a_i,a_i+m)$。

那么怎么确定区间内的物品数量呢？我们使用二分，二分出第一个 $a_k<a_i+m$ 的位置，减去 第一个 $a_l<a_i$ 的位置，就是区间 $[a_i,a_i+m)$ 包含的物品个数了。

时间复杂度：$\mathcal{O(n\log n)}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 100;

int n, m, a[N];

int find(int x) { // 找出最大的 a[k] < x 
	int l = 1, r = n, ans = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (a[mid] < x) {
			l = mid + 1; 
			ans = mid;
		} else {
			r = mid - 1;
		}
	}
	return ans;
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + 1, a + n + 1);
	int maxx = 0;
	for (int i = 1; i <= n; i++) {
		maxx = max(maxx, find(a[i] + m) - find(a[i]));
	}
	cout << maxx << endl;
	return 0;
}
```

---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/AT_abc326_c)

因为输入的数字都为整数，$x$ 根本就不需要考虑实数。所以我们先排序，然后再使用双指针维护一下即可，当右指针的数字与左指针的数字小于等于 $M$ 时，则代表这个区间是可行的，那么更新答案即可，否则我们把左端点移动到可行的位置。

主要代码
```cpp
sort(a+1,a+n+1);//先排序
int l=1;//l为左端点
for(int r=1;r<=n;r++)
{
    if(a[r]-a[l]<=M) ans=max(ans,r-l+1);	
	else while(a[r]-a[l]>M) ++l;
}
```

## 建议评橙

---

## 作者：AlexandreLea (赞：0)

## 题目大意

给出一条数轴以及在数轴上分布的 $n$ 个点 $A_1,A_2,\cdots,A_n$，求一条长为 $M$ 的左开右闭线段最多能覆盖多少个点。

## 题目思路

首先由于有重复并且需要排列在数轴上，所以我们先对 $A$ 排序。 

然后，怎么办呢？首先，我们把线段的左端点放在某个已存在的 $A$ 上一定比放在某个空地上更好。而后，我们可以枚举每一个 $A$，来找到对应的右端点。

怎么找右端点呢？由于我们排过序，因此二分查找即可。

程序如下。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
const int SIZE=3e5+10;
int main(){
    int n,m,a[SIZE],ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        int fv=lower_bound(a+1,a+n+1,a[i]+m)-a-1;
        ans=max(ans,fv-i+1);
    }
    cout<<ans<<endl;
    return 0;
}
```

**EOF**

---

## 作者：heyx0201 (赞：0)

# Peak 题解
## Description
> 给定 $N,M$，还有 $N$ 个数 $a_1,a_2,\dots a_n$ 表示 $a_i$ 上有一个点，求出半开区间 $[x,x+M)$ 内的最大的点的个数。

## Solution
既然是 $N$ 个点，我们就可以对 $a$ 排序，然后类似于双指针的方法来求解答案。

对于每个点 $i$：
- 设一个 $j$，一开始等于 $i$；
  - 一直向后移动，直到 $a_{j + 1} - a_i \ge M$，就停止。
- 然后就是更新答案：$j - i + 1$。

### Time & Memory
时间：线性 $O(N)$；

空间：一个 $a$ 数组 $O(N)$。
## Accept Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3e5 + 10;

int n, m, a[MAXN], ans;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  sort(a + 1, a + n + 1);
  for (int i = 1, j = 1; i <= n && j <= n; i++) {
    for (; j < n && a[j + 1] - a[i] < m; j++) {
    }
    ans = max(ans, j - i + 1);
  }
  cout << ans;
  return 0;
}
```

---

## 作者：BugGod (赞：0)

考虑贪心。首先我们可以得出：起点在某个礼物位置，一定能得到最大的礼物数。

我们设现在我们要放在 $a_i$，上一个礼物在 $a_{i-1}$（已经按照升序排列），则我们可以获得 $[a_i,a_i+m)$ 的礼物，显然，如果起点在 $(a_{i-1},a_i)$ 的区间里，那么相对于前一个区间，右边少了一部分，可能会少拿礼物，左边多了一部分，由于上一个礼物还在 $a_{i-1}$，而起点 $x$ 一定大于 $a_{i-1}$，所以不会多拿礼物。总体上，只会少拿，不会多拿。

那么我们就有了思路：枚举起点（每个 $a_i$），用 `lower_bound` 函数直接算出 $a_i$ 中第一个大于等于 $a_i+m$ 的位置，那么如果这个位置为 $k$，则 $i,i+1,\cdots,k-1$ 编号的礼物全部都能拿，取最大值即可。

CODE：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[300010],ans;
signed main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);//注意要排序，不然二分会错
    for(int i=1;i<=n;i++)
    {
        int l=a[i],r=a[i]+m;
        int x=lower_bound(a+1,a+1+n,r)-a;
        ans=max(ans,x-i);
    }
    cout<<ans;
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

本题很板，但是注意坑点：半开区间。

那么二分求解即可。

对于一个数 $a_i$，二分求解最小的小于 $a_i+k$（$k$ 指代码中的 $k$）的数的下标即可。

时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[500005];
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+1+n);//先排序
	int res=0;
	for(int i=1;i<=n;i++){//枚举每一个数
		int l=i,r=n,ans=i;
		while(l<=r){//二分主体
			int mid=(l+r)>>1;
			if(a[mid]<a[i]+k)ans=mid,l=mid+1;//注意小于
			else r=mid-1;
		}
		res=max(res,ans-i+1);//求最大值即可
	}
	cout<<res;
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：
题意很简单，就是找一个区间内的最多数目。

我们读入、排序后，不断尝试从每个点向后搜。

用两个变量 $i$ 和 $tep$ 分别表示当前查询到的点和从 $tep$ 作为区间最左端。

当 $tep+m \le a_i$ 时，尝试更新最大值为 $i-tep$。

最后再尝试更新最大值为 $n+1-tep$。

输出最大值即可。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[500050];
int maxn;
int tep=1;
signed main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++){
		cin>>a[i];
	}	
	sort(a+1,a+n+1);
	if (a[1]+m>a[n]){
		return cout<<n,0;
	}
	for (int i=1;i<=n;i++){
		while (a[i]>=a[tep]+m){
			maxn=max(i-tep,maxn);
			tep++;	
		}
	}
	maxn=max(n+1-tep,maxn);
	cout<<maxn;
	return 0;
}
```


---

## 作者：yhx0322 (赞：0)

upd on $2023.12.12$：更改了标题行的内容 & 大小。
## Description
数字线上放置了 $N$ 个礼物。第 $i$ 个礼物放置在坐标 $A_i$ 处。

可以在数轴上选择长度为 $M$ 的半开区间 $[x,x+M)$，并获得其中包含的所有礼物。

求：最多可以获得多少份礼物？

## Solution
二分/双指针都可。

### Solution1 - 二分答案
二分出最多可以获得多少份礼物，答案为右边界。

每次 `check`，枚举 $a$ 数组的每个数，看看 $a_{i+mid-1} - a_i$ 是否 $< m$ 即可。

### Solution2 - 双指针
每次 $l$ 从 $1 \sim n$，用 while 循环枚举的最大右端点，即最大的满足 $a_r - a_l \le m$ 的点，然后求一个 $\max$。

## Code
### Solution1
```cpp
#include <bits/stdc++.h>


using namespace std;

const int N = 3e5 + 10;
int a[N];
int n, m;
map<int, int> mp[N];
set<int> st[N];

int l = 0, r, mid;

bool check(int mid) {
    for (int i = 1; i <= n - mid + 1; i++) {
        if (a[i + mid - 1] - a[i] < m) return true;
    }
    return false;
}

int main() {
    cin >> n >> m;
    r = n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    while (l <= r) {
        mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << l - 1;
    return 0;
}
```
### Solution2
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;
int a[N];

int main() {
    int n, m, ans = 0;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + n + 1);
    int now = 1;
    for(int i = 1; i <= n; i++) { // 枚举左指针
        while(now < n && a[now + 1] - a[i] < m) now++; // 满足条件就一直自增
        ans = max(ans, now - i + 1);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题其实很简单，我们只需要暴力一下就可以了。

我们给每一个位置先去排一下序，然后二分查找当前位置之后第 $m$ 个小的第一个数的位置，然后减一下就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[300001];
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int ma=0;
	sort(a+1,a+1+n);a[0]=-1;
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=a[i-1])
		{
			int ans=0,r=n,l=i;
			while(l<=r)
			{
				int mid=(l+r)/2;
				if(a[mid]<a[i]+m) ans=mid,l=mid+1;
				else r=mid-1;
			}
			ma=max(ma,ans-i+1);
		}
	}
	cout<<ma;
	return 0;
}

```

---

## 作者：ilibilib (赞：0)

## 题目分析

这道题目给出了一些礼物的坐标，需要我们选择一个长度为 $M$ 的半开区间，使得这个区间内包含的礼物数量最多。我们需要找到一个策略，使得能够尽可能多地获取礼物。

## 解题思路

我们可以使用双指针的方法来解决这个问题。

首先，将所有礼物的坐标按照从小到大的顺序进行排序。

我们用两个指针 $l$ 和 $r$ 来表示区间的起始位置和结束位置，然后我们不断移动 $r$ 指针，直到区间的长度小于等于 $M$，并记录此时区间内的礼物数量。

接下来，我们将 $l$ 指针向右移动，同时更新区间内的礼物数量，直到区间的长度再次小于等于 $M$。在每次移动 $l$ 指针时，我们需要从区间内剔除左边界元素。

在整个过程中，我们记录下每个区间内的礼物数量，并取其中最大值作为答案。

## 算法步骤

1. 将所有礼物的坐标进行排序。

2. 初始化 $l$ 和 $r$ 指针为 $0$，初始化最大礼物数量 $max\_gifts$ 为 $0$。

3. 当 $r$ 指针小于 $N$ 时，执行以下循环：

   a.将 $r$ 指针向右移动，同时更新区间内的礼物数量。

   当区间的长度大于 $M$ 时，执行以下循环：

   b.将 $l$ 指针向右移动，同时更新区间内的礼物数量。

   c.更新最大礼物数量 $max\_gifts$，使其等于当前区间内的礼数量和 $max\_gifts$的较大值。

4. 输出最大礼物数量 $max\_gifts$。

## 复杂度分析

假设 $N$ 为礼物的数量。

- 排序所有礼物的坐标的时间复杂度为 $O(N\log N)$。
- 使用双指针的过程中，$r$ 指针最多移动 $N$ 次，$l$ 指针最多移动 $N$ 次。因此，整个过程的时间复杂度为 $O(N)$。

综上所述，总的时间复杂度为 $O(N\log N)$。

空间复杂度为 $O(N)$，用于存储礼物坐标的数组。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int A[314514];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)cin>>A[i];
	sort(A+1,A+n+1);
	int max_gifts=0,l=1,r=1;
	while(l<=n)
	{
		while(r<=n&&A[r]<A[l]+m) ++r;
		max_gifts=max(max_gifts,r-l);
		++l;
	}
	cout<<max_gifts;
	return 0;
}
```

---

## 作者：aaron0919 (赞：0)

# [AT_abc326_c の题解](https://www.luogu.com.cn/problem/AT_abc326_c)

### 题目大意

有 $n$ 数，在一个数轴上。

你有一条长为 $m$ 的杆子，问你最多能盖住多少数。

### 理性分析

这道题类似于滑动窗口，我们可以用双指针（$i, j$ 分别为左右指针）。

例如：

$n=6, m=5, A=9,2,5,14,8,18$

将 $A$ 排序。

$A=2,5,8,9,14,18$

然后得到一个数轴（第一个为零，$i, j$ 表示 $A_i$ 或 $A_j$）：

`--x--x--xx----x---x`

然后我们来滑一根杆：

```
--x--x--xx----x---x
  ^^^^^
  i  j
i = 0 // 第一个数
j = 1 // 第二个数
```

这样，当前的答案就等于 $ans=\max(0,j-i+1)=2$。

接着杆移到下一个数。

```
--x--x--xx----x---x
     ^^^^^
     i
i = 1
j = 1 // 没动
```

$j$ 就循环判断，能不能往右盖数，能的话就往右跑。

```
--x--x--xx----x---x
     ^^^^^
     i   j
i = 1
j = 3
ans = max(2, 3) = 3
```

由于上一次的一定能被盖住，所以当前的盖住的数目就等于右指针减左指针加一。

剩下的就不解释了，伴着代码吃吧。。。

---
```
--x--x--xx----x---x
        ^^^^^
        ij
i = 2
j = 3
ans = max(3, 2) = 3
```
---
```
--x--x--xx----x---x
         ^^^^^
         i
i = 3
j = 3
ans = max(3, 1) = 3
```
---
```
--x--x--xx----x---x
              ^^^^^
              i   j
i = 4
j = 5
ans = max(3, 2) = 3
```
---
```
--x--x--xx----x---x
                  ^^^^^
                  i
i = 5
j = 5
ans = max(3, 1) = 3
```

### 代码实现

用双指针。

先排序，然后跑双指针。

具体实现就是定义一个右指针。如果杆子能覆盖到右边的数，就加，然后循环判断，不断覆盖，最后计算答案即可。

#### 补充

记得在最后加一个数，否则

```cpp
while (a[i] + m > a[j])
```

这行会无限执行。。。

### code

[AC 记录](https://atcoder.jp/contests/abc326/submissions/47090844)

```cpp
#include<bits/stdc++.h>

long long n, m, ans;
long long a[300050];

int main()
{
	scanf("%lld%lld", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%lld", &a[i]);
	}
	a[n] = 1e18;
	std::sort(a, a + n + 1);
	for (int i = 0, j = 0; i < n; i++)
	{
		while (a[i] + m > a[j])
		{
			j++;
		}
		ans = std::max(ans, 0LL + j - i);
	}
	printf("%lld", ans); /?_?\
}
```

---

## 作者：Crazyouth (赞：0)

**分析**

不难想到双指针，两个指针 $l,r$，代表选择区间 $[l,r)$，若此区间不合题意，也就是 $a_r-a_l\ge m$，就先更新 $ans$，再不断增加 $l$，直到 $a_r-a_l<m$。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[int(3e5+10)];
int main()
{
	int n,l=1,r=1,ans=1,tp=1,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	while(r<n)
	{
		r++;
		tp++;
		while(a[r]-a[l]>=m) l++,tp--;
		ans=max(ans,tp);
	}
	cout<<ans;
	return 0;
}

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc326_c)

一道二分题。

首先非常显然，你选择的这个区间左端点在 $a_i$ 上肯定更优，因此我们可以枚举左端点 $l$。然后剩下的就是使用二分求出有多少个 $a_i$ 满足 $l\le a_i< l+m$，具体可以使用 `std :: upper_bound` 实现。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

typedef long long ll;
typedef __int128 i128;
typedef long double ld;
typedef __float128 f128;

namespace xvl_ { 
	#define SP(n, x) std :: setprecision(n) << std :: fixed << x
	#define REP(i, l, r) for (auto i = (l); i <= (r); i++)
	#define PER(i, r, l) for (auto i = (r); i >= (l); i--)
	#define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
	template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
	template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
ll n, m, ans;
int a[300005];
int main() {
	// freopen("InName.in", "r", stdin);
	// freopen("OutName.out", "w", stdout);
	ios :: sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> m;
	REP(i, 1, n) cin >> a[i];
	sort(a + 1, a + 1 + n);
	REP(i, 1, n) {
		ll loc = upper_bound(a + 1, a + 1 + n, a[i] + m - 1) - a - 1;
		ans = Max(ans, loc - i + 1);
	}
	cout << ans;
	return 0;
}
```


---

## 作者：MMXIandCCXXII (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc326_c)

## 题目大意
给定 $n$ 个点的位置，选取一个左闭右开的区间 $\left [ x, x + m \right )$，使包含在其中的点最多。

## 思路
首先想到，排好序后枚举从每一个点开始的区间能包含多少点，求最大值。用给出的点做区间起点是因为这样不会浪费前面一段区间长度。但是如果每次都去遍历求这个区间有几个点，超时是必然的。所以，我们可以用单调栈或其他方法优化。

我用的是双指针，枚举一个数后面第一个超出区间的数的位置，因为排好序的数组是不下降的，所以可以直接从上一个数的区间终点去找，不用回头。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

int a[300010];
int b[300010];

signed main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort (a + 1, a + n + 1);
    int last = 2;
    for (int i = 1; i <= n; i++)
    {
        while (a[i] + m > a[last] && last < n + 1) last++;
        b[i] = last;
    }
    int maxn = 0;
    for (int i = 1; i <= n; i++)
    {
        maxn = max (maxn, b[i] - i);
    }
    cout << maxn << endl;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

前置知识：

- 双指针

不会的自行[百度](https://www.iduba.com/sv.html?f=chedhntab)

## 题意：

给 $n$ 个坐标，让你选定一个长度为 $m$ 的区间，使得最多的坐标包含在这里面（区间是左闭右开的）

## 初始化：

1. 按照题意输入

2. 因为这个坐标不是按顺序输入的，所以要先将其进行排序（单调递增）

## 正片：

可以设定两个指针 $h=1,t=1$ 分别表示头和尾,使用 `while()` 循环进行双指针取最大值，一直遍历到 $t=n$

### 栗子：

设 $n=7,m=10$ ，排序后的 $a[]=3,6,12,13,14,15,21$ 

$h=1,t=3$ 区间 $[3,12]$

$...$

$h=3,t=7$ 区间 $[12,21]$

得解

## 代码

**警告：抄袭者后果自负**

```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int a[N];
int h=1,t;
int ans=-1;
int main(){
	int n,m,j,sum;
	scanf("%d%d",&n,&m);
	--m;//左闭右开
	for(int i=1;i<=n;++i){
		scanf("%d",a+i);
	}sort(a+1,a+n+1);		
	while(t<n){
		++t;
		if(h<t&&a[t]-a[h]>m){
			++h;
		}
		ans=max(ans,t-h+1);
	}
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：_sumshine_ (赞：0)

这里既然要求长度为 $k$ 的区间内最多的礼物数量，显然不能使用纯暴力来查看，则不妨边做边预处理，则维护一个队列，并且让这个队列中所有的均为循环中当前点的距离符合要求，这样使得每一个礼物都只在队列中入队出队各一次，不会存在暴力多次重复的情况（就是用队列优化了那一层循环）。

### code
```cpp
q.push(a[i]);
while(q.front()>=a[i]+k)q.pop();
if(ans<q.size()ans=q.size();
```
剩下的请读者自行思考。

---

## 作者：_shine_ (赞：0)

感性理解：现在有 $n$ 个点，问长度为 $k$ 个区间内最多有多少的点。

一眼想到 ```queue```，不妨维护队列表示以当前为坐标后的 $k$ 区间内有多少个点，不停的加入新的点，并且删除距离超标的点即可。
#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
queue<int>q;
int n,k,ans,a[maxn];
signed main(){
	cin >> n >> k;
	for(int i=1;i<=n;++i){
		cin >> a[i];
	}
	sort(a+1,a+n+1);
	for(int i=n;i>=1;--i){
//		cout << a[i] << " 111 " << endl;;
		q.push(a[i]);
		while(q.front()>=a[i]+k)q.pop();
		if(ans<q.size()){
//			cout << ans << " " << q.size() << " " << i << endl;
			ans=q.size();	
		}
	}
	cout << ans << endl;
	return 0;
}

```


---

