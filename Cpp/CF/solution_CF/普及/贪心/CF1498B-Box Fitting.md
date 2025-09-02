# Box Fitting

## 题目描述

You are given $ n $ rectangles, each of height $ 1 $ . Each rectangle's width is a power of $ 2 $ (i. e. it can be represented as $ 2^x $ for some non-negative integer $ x $ ).

You are also given a two-dimensional box of width $ W $ . Note that $ W $ may or may not be a power of $ 2 $ . Moreover, $ W $ is at least as large as the width of the largest rectangle.

You have to find the smallest height of this box, such that it is able to fit all the given rectangles. It is allowed to have some empty space left in this box after fitting all the rectangles.

You cannot rotate the given rectangles to make them fit into the box. Moreover, any two distinct rectangles must not overlap, i. e., any two distinct rectangles must have zero intersection area.

See notes for visual explanation of sample input.

## 说明/提示

For the first test case in the sample input, the following figure shows one way to fit the given five rectangles into the 2D box with minimum height:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1498B/c4bb98ad37834f3e833cc55e38d3b77b700a7197.png)In the figure above, the number inside each rectangle is its width. The width of the 2D box is $ 16 $ (indicated with arrow below). The minimum height required for the 2D box in this case is $ 2 $ (indicated on the left).

In the second test case, you can have a minimum height of three by keeping two blocks (one each of widths eight and two) on each of the three levels.

## 样例 #1

### 输入

```
2
5 16
1 2 8 4 8
6 10
2 8 8 2 2 8```

### 输出

```
2
3```

# 题解

## 作者：HuangBarry (赞：53)

**注意：此代码含有整活元素，警惕阅读。**

贪心。每次在底下放入最大的元素是最优的，所以每放一个物品后，每次挑最长的放入即可。使用优先队列，最大的始终会在队头。

代码如下：

**此代码在 CodeForces 原 OJ 是可以正常 AC 的，[AC 记录](https://codeforces.com/problemset/submission/1498/302618522)**

```cpp
#include<bits/stdc++.h>
#define 使用 using
#define 命名空间 namespace
#define 标准命名空间 std
#define 然后 ;
#define 整型 int
#define 主函数 main
#define 左圆括号 (
#define 右圆括号 )
#define 左花括号 {
#define 右花括号 }
#define 返回 return
#define 零 0
#define 输入 cin>>
#define 入 >>
#define 输出 cout<<
#define 出 <<
#define 加 +
#define 换行 '\n'
#define 若条件成立则一直循环 while
#define 减一 --
#define 加一 ++
#define 十的五次幂 1e5
#define 十五 15
#define 左方括号 [
#define 右方括号 ]
#define 循环 for
#define 等于 =
#define 一 1
#define 小于等于 <=
#define 排序 sort
#define 逗号 ,
#define 大的在前 greater
#define 左尖括号 <
#define 右尖括号 >
#define 优先队列 priority_queue
#define 如果 if
#define 是空的 .empty()
#define 放入 .push
#define 减 -
#define 否则 else
#define 的队头元素 .top()
#define 弹出队首 .pop()
#define 的大小 .size()
#define 或者 ||
#define 小于 <
/*--------------------------------------------------------------------------------------*/
使用 命名空间 标准命名空间 然后
整型 t 逗号 n 逗号 w 逗号 a 左方括号 左圆括号 整型 右圆括号 十的五次幂 加 十五 右方括号 然后
整型 主函数 左圆括号 右圆括号 左花括号
    输入 t 然后
	若条件成立则一直循环 左圆括号 t 减一 右圆括号 左花括号
		输入 n 入 w 然后
        循环 左圆括号 整型 i 等于 一 然后 i 小于等于 n 然后 i 加一 右圆括号
            输入 a 左方括号 i 右方括号 然后
        排序 左圆括号 a 加 一 逗号 a 加 一 加 n 逗号 大的在前 左尖括号 整型 右尖括号 左圆括号 右圆括号 右圆括号 然后
		优先队列 左尖括号 整型 右尖括号 q 然后
        循环 左圆括号 整型 i 等于 一 然后 i 小于等于 n 然后 i 加一 右圆括号 左花括号
            如果 左圆括号 q 是空的 或者 q 的队头元素 小于 a 左方括号 i 右方括号 右圆括号
                q 放入 左圆括号 w 减 a 左方括号 i 右方括号 右圆括号 然后
			否则 左花括号
                整型 x 等于 q 的队头元素 然后
                q 弹出队首 然后
                q 放入 左圆括号 x 减 a 左方括号 i 右方括号 右圆括号 然后
			右花括号
		右花括号
        输出 q 的大小 出 换行 然后
	右花括号
    返回 零 然后
右花括号
```

---

## 作者：SpeedStar (赞：6)

#### 算法分析


可以考虑每一行尽可能放宽度大的矩形。

具体实现：

- 先对所给的矩形按其宽度从大到小的顺序排序；
- 开一个带有大顶堆的优先队列来存每一行剩余空间的宽度，这一部分以后可能还会用到；
- 初始时先把 $0$ 压入大顶堆，表示当前没有剩余空间；
- 然后扫描一下所有的矩形宽度，同时取出大顶堆的队头元素 $x$ （即剩余空间最大的那一行的所剩空间） 并弹出。如果当前矩形宽度比 $x$ 大的话，说明还需要一行，对答案 `+1` 跳到下一行即可，并把 $x$ 和 $w - a_i$ 都压入大顶堆（把 $x$ 重新压入大顶堆指的是之前剩余空间最大的那一行剩余的 $x$ 的空间没有使用，把 $w - a_i$ 压入大顶堆表示当前剩余空间最大的那一行还有 $w - a_i$ 的剩余空间可以使用）；否则的话就把 $x - a_i$ 压入大顶堆（表示当前剩余空间最大的那一行还剩 $x - a_i$ 的空间可利用）。


#### C++ 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)

using std::cin;
using std::cout;
using std::vector;
using std::priority_queue;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	int t;
	cin >> t;
	
	while (t--) {
		priority_queue<int> q;
		q.push(0);
		int n, w;
		cin >> n >> w;
		vector<int> a(n);
		rep(i, n) cin >> a[i];
		sort(a.rbegin(), a.rend());
		int ans = 0;
		rep(i, n) {
			int x = q.top(); q.pop();
			if (x < a[i]) {
				q.push(x);
				q.push(w - a[i]);
				ans++;
			}
			else q.push(x - a[i]);
		}
		cout << ans << '\n';
	}
	
	return 0;
}
```


---

## 作者：cunzai_zsy0531 (赞：3)

### [题目链接](https://www.luogu.com.cn/problem/CF1498B)

这个题考试的时候 $+4$，原因是 $multiset$ 不会用……

很容易想到一种贪心策略，就是把每一层剩下的长度都放到一个 $multiset$ 里，每次对于一个长度 $a_i$，找出最小的大于等于 $a_i$ 的那一层即可。

一定要注意，在 `multiset` 里二分，不能用 `lower_bound(t.begin(),t.end(),a[i])`，要用 `t.lower_bound(a[i])`！

上代码：
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;
inline int rd(){
	int res=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) res=(res<<1)+(res<<3)+(c-'0'),c=getchar();
	return res;
}
const int N=1e5+13;
int n,w,a[N];
inline void solve(){
	int cnt=0;
	multiset<int> t;
	multiset<int>::iterator it;	
	for(int i=1;i<=n;++i){
		if(t.empty()){//注意对t是否为空的判断！
			++cnt;
			if(w!=a[i]) t.insert(w-a[i]);
			continue;
		}
		it=t.lower_bound(a[i]);//这个地方，吃一堑长一智！
		if(it==t.end()){
			++cnt;
			if(w!=a[i]) t.insert(w-a[i]);//如果不剩下，那么就不用加进去了
		}
		else{
			int p=(*it);
			t.erase(it);
			if(p!=a[i]) t.insert(p-a[i]);
		}
	}
	printf("%d\n",cnt);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		n=rd(),w=rd();
		for(int i=1;i<=n;++i) a[i]=rd();
		sort(a+1,a+n+1,greater<int>());
		solve();
	}
	return 0;
}
```


---

## 作者：vectorwyx (赞：3)

要想层数最少，每一层就得尽量填满。因此我们可以采用贪心的策略，按长度从大到小填。如果当前这一层已经无法再填了，就把答案加 $1$，进入下一层。朴素的实现是 $O(n^2)$ 的。而由于长条的长度一定能表示成 $2^p$ 的形式，所以我们可以只记录这个指数 $p$，通过桶排序把时间复杂度降到 $O(\log(w)n)=O(20n)$，能够通过本题。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=2e6+5,lim=20;
int a[N],n,w,c[N],rp[N];

void work(){
	n=read(),w=read();
	fo(i,0,lim) rp[i]=0;
	fo(i,1,n) a[i]=read(),rp[c[a[i]]]++;
	int ans=0;
	while(1){
		ans++;
		int t=w;
		go(i,lim,0){
			int k=min(t/(1<<i),rp[i]);
			rp[i]-=k;
			t-=k*(1<<i);
		}
		bool fl=1;
		fo(i,0,lim) if(rp[i]) fl=0;
		if(fl) break;
	}
	cout<<ans;
	puts("");
}

int main(){
	fo(i,0,lim) c[1<<i]=i;
	int T=read();
	while(T--) work(); 
	return 0;
}
```


---

## 作者：wawatime1 (赞：3)

### 问题分析
本题的核心是要找到一个最小高度的二维盒子，使得给定的 $n$ 个宽度为 $2$ 的方幂的长条能够在不旋转、不重叠的情况下放入宽度为 $W$ 的盒子中。
### 算法思路
- 我们采用二分答案来解决这个问题。二分答案的范围是从 $1$ 到 $n$（因为最多需要 $n$ 层来放置所有长条）。
- 对于二分答案中的每一个中间高度 $h$，我们使用一个优先队列（最大堆）来模拟将长条放入高度为 $h$、宽度为 $W$ 的盒子的过程。
- 如果在这个模拟过程中，所有长条都能成功放入，说明当前高度 $h$ 是可行的，我们可以尝试更小的高度；否则，我们需要尝试更大的高度。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, w, a[100005];
int calc (int h){
	priority_queue <int> q;
	for (int i = 1; i <= h; i++)
		q.push (w);
	for (int i = 1; i <= n; i++){
		if (q.top() < a[i] || q.empty()){
			return 0;
		}
		if (q.top() > a[i]){
			q.push (q.top() - a[i]);
			q.pop();
		} 
		else{
			q.pop();
		}
	}
	return 1;
}
int main () {
	scanf ("%d", &t);
	while (t--) {
		scanf ("%d%d", &n, &w);
		for (int i = 1; i <= n; i++) {
			scanf ("%d", &a[i]);
		}
		sort (a + 1, a + 1 + n, greater<int>());
		int l = 1, r = n + 1;
		while (l < r){
			int mid = (l + r) >> 1;
			if (calc(mid))
				r = mid;
			else
				l = mid + 1;
		}
		printf ("%d\n", l);
	}
	return 0;
}
```

---

## 作者：xuorange (赞：2)

思路：动态贪心。

易知先放大物品可使决策更优，故先将物品从大到小排序；每放一个物品，挑选剩下长度最长的行，可以用大顶堆维护每行剩余长度。

用优先队列记录答案，这样就可以自动排序，节省时间复杂度。

```
#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;cin>>t;
	while (t--){
		int n,w;
		cin>>n>>w;
		int a[n+1];
		for(int i=1;i<=n;i++)cin>>a[i];
		sort(a+1,a+1+n,greater<int>()); //贪心 
		priority_queue<int>q; //优先队列是个好东西 
		for(int i=1;i<=n;i++){
			if(q.empty())q.push(w-a[i]);
			else{
				if(q.top()<a[i])q.push(w-a[i]);
				else{
					int t=q.top();
                    q.pop();
					t-=a[i];
					q.push(t);
				}
			}
		}
		cout<<q.size()<<endl;
	}
}
```

---

## 作者：lzy120406 (赞：1)

## [原题](https://codeforces.com/problemset/problem/1498/B)
题目要求我们将一组高度为 `1`，宽度为 `2` 的幂次的矩形，放入一个宽度为 $W$ 的容器中，使得容器的高度最小化。需要注意的是，矩形的宽度不能旋转，且任何两个矩形不能重叠。

## 思路
这种放置问题，考虑贪心，**尽量将矩形紧凑地放入容器中。**

不妨对于每一层，**从最宽的矩形开始，尽可能多地放入容器中**，直到这一层的剩余空间无法再放下任何矩形。

具体实现如下：

- 统计每种宽度的矩形数量。

- 对于每一层，尝试放入最大宽度的矩形，直到这一层无法再放下任何矩形。

- 重复上述过程，直到所有矩形都被放入容器中，计算需要的总层数。

具体细节看代码。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int w[100005];
void solve() {
	int n, W;
	cin >> n >> W;
	for (int i = 0; i < n; ++i) {
		cin >> w[i];
	}
	// 统计每种宽度的矩形数量
	map<int, int, greater<int>> wcnt;
	for (int i = 0; i < n; ++i) {
		wcnt[w[i]]++;
	}
	int height = 0;
	while (n > 0) {
		int rew = W;
		// 尝试放入最大宽度的矩形
		for (auto& [width, cntt] : wcnt) {
			if (cntt > 0 && width <= rew) {
				int cnt = min(cntt, rew / width);
				rew -= cnt * width;
				cntt -= cnt;
				n -= cnt;
			}
		}
		height++;
	}
	cout << height << "\n";
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
```
时间复杂度 $ \mathcal{O}(tn \log n) $，本题中 $\sum{n} \leq 10^5$，可以通过本题。

---

## 作者：SuperBeetle (赞：0)

这道题贪心 + 优先队列即可，每次选空位最大的，不够就加一层

直接上代码，里面有注释

```cpp
#include <bits/stdc++.h>
#define IAKIOI ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define UPB(x, y, z) upper_bound(x + 1, x + y + 1, z) - x
#define LWB(x, y, z) lower_bound(x + 1, x + y + 1, z) - x
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define pre(i, l, r) for (int i = r; i >= l; i--)
#define UNQIUE(x, y) unqiue(x + 1, x + y + 1)
#define SORT(x, y) sort(x + 1,x + y + 1)
#define pf push_front 
#define pb push_back 
#define IT iterator
#define endl '\n';

const int N = 5e5 + 5, INF = 0x3f3f3f3f;
const double ecnts = 1e-6;

#define int long long

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef double db;

void read(int &x) {
	int f = 1, y = 0;
	char c = getchar();
	while (!isdigit(c)) {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (isdigit(c)) {
		y = y * 10 + c - '0';
		c = getchar();
	}
	x = y * f;
}

void write(int x) {
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

inline int max(int x, int y) {return x > y ? x : y;}
inline int min(int x, int y) {return x < y ? x : y;}

inline void swap(int &x, int &y) {int t = x;x = y, y = t;}
inline int pow(int x, int y) {
	int ans = 1;
	while (y) {
		if (y & 1) ans *= x;
		x *= x, y = y >> 1;
	}
	return ans;
}

int n, w;
int a[N];

void solve() {
	priority_queue<int> q;
	cin >> n >> w;
	rep(i, 1, n) cin >> a[i];
	sort(a + 1, a + 1 + n, greater<int>()); //从大到小排序
	int ans = 0; //层数
	q.push(0); //先扩一层
	rep(i, 1, n) {
		int x = q.top(); //去空位最大的
		q.pop();
		if (x < a[i]) { //没这个进不去了
			q.push(x);//放回去
			q.push(w - a[i]); //再搞一层
			ans++;//加一层
		}
		else q.push(x - a[i]); //够就直接进
	}
	cout << ans << '\n';
}

signed main() {
	IAKIOI;
	int t = 1;
	cin >> t;
	while (t--) {
		solve();
	}
}
```

---

## 作者：lss_ak_gcd (赞：0)

一眼顶针，鉴定为：不会 multiset 的 upper_bound。

有一个很傻的地方是：`multiset` $se$ 中若一个迭代器 $it$ 满足 `it == se.begin()`，那么 `--it` 的值和 `it` 的值一样。实际上这个是一个未定义的行为，不知道其他电脑上怎么样。

然后回归这个问题。容易发现，用 $k$ 个小长方形的和为 $2^w$，则一定不如用 $2^w$，因为长的灵活性不如短的。所以直接用 `multiset` 二分维护当前可以插入进来的最长的线段，若没有就更新一行即可。时间复杂度为 $O(n\log n)$。

---

