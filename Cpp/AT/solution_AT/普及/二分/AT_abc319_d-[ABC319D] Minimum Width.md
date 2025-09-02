# [ABC319D] Minimum Width

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc319/tasks/abc319_d

高橋くんは、$ N $ 個の単語からなる文章をウィンドウに表示させようとしています。 すべての単語の縦幅は等しく、$ i $ 番目 $ (1\leq\ i\leq\ N) $ の単語の横幅は $ L\ _\ i $ です。

文章は、横幅 $ 1 $ の空白を単語の区切りとしてウィンドウに表示されます。 より厳密には、高橋くんが横幅 $ W $ のウィンドウに文章を表示しているとき、次の条件が成り立っています。

- 文章はいくつかの行に分かれている。
- $ 1 $ 番目の単語は一番上の行の先頭に表示されている。
- $ i $ 番目 $ (2\leq\ i\leq\ N) $ の単語は、$ i-1 $ 番目の単語の次に間隔を $ 1 $ だけ開けて表示されているか、$ i-1 $ 番目の単語が含まれる行の下の行の先頭に表示されているかの一方である。それ以外の場所に表示されていることはない。
- それぞれの行の横幅は $ W $ を超えない。ここで、行の横幅とは最も左にある単語の左端から最も右にある単語の右端までの距離を指す。
 
高橋くんが文章をウィンドウに表示したとき、文章が $ M $ 行に収まりました。 ウィンドウの横幅としてありえる最小の値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ M\leq\ N\leq2\times10\ ^\ 5 $
- $ 1\leq\ L\ _\ i\leq10^9\ (1\leq\ i\leq\ N) $
- 入力はすべて整数
 
### Sample Explanation 1

ウィンドウの横幅が $ 26 $ のとき、以下のようにして与えられた文章を $ 3 $ 行に収めることができます。 !\[\](https://img.atcoder.jp/abc319/710c42acf58eacf40178e28a0a0b3a2c.png) ウィンドウの横幅が $ 25 $ 以下のときは与えられた文章を $ 3 $ 行に収めることができないため、$ 26 $ を出力してください。 単語を複数の行にまたがって表示させたり、行の横幅がウィンドウの横幅を上回ったり、単語を並べ替えたりしてはいけないことに注意してください。 !\[\](https://img.atcoder.jp/abc319/ed3aac3d0c0eb00c5663aa6a95023b33.png)

### Sample Explanation 2

答えが $ 32\operatorname{bit} $ 整数に収まらない場合があることに注意してください。

## 样例 #1

### 输入

```
13 3
9 5 2 7 1 8 8 2 1 5 2 3 6```

### 输出

```
26```

## 样例 #2

### 输入

```
10 1
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
10000000009```

## 样例 #3

### 输入

```
30 8
8 55 26 97 48 37 47 35 55 5 17 62 2 60 23 99 73 34 75 7 46 82 84 29 41 32 31 52 32 60```

### 输出

```
189```

# 题解

## 作者：Dream_poetry (赞：4)

### 思路：
考虑二分答案。

我们使答案 $ans$ 为所要求的宽度。首先使得 $l$ 为 $L$ 数组中的最大值，$r$ 为无限大，不断尝试 $mid = \frac{(l+r)}{2}$ 时，是否能满足条件。

当 $mid$ 满足条件时，我们将 $r$ 调为 $mid-1$，并将 $ans$ 记为 $mid$；当无法满足条件时，只需将 $l$ 变为 $mid+1$，不需要对 $ans$ 进行处理。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int  l=0,r=1e15,ans;
int n,m,a[200010];
bool check(int x){ // 二分 
	int now=a[1],cnt=1;
	for(int i=2;i<=n;i++){
		if(now+1+a[i]>x){
			cnt++;
			now=a[i];
		}
		else
			now+=a[i]+1;
	}
	return cnt<=m;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		l=max(l,a[i]); // 记录 l 
	}
	while(l<=r){
		int mid=(l+r)/2;
		if (check(mid))
			r=mid-1,ans=mid; //调整 r 并改变 ans 
		else
			l=mid+1; // 调整 l 
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：dayz_break404 (赞：3)

## 题意描述

一段文字有 $n$ 个单词，需要将这段文字显示在每行一定宽度和一定行数的框中。每个字母占 $1$ 个单位宽度，若两两相邻的单词都在同一行，则两个单词之间需要宽度为 $1$ 的间隔。并限制每个独立的单词必须在同一行，最大行数为 $m$，求满足条件的每行最小宽度最大是多少。

## 题目分析

求最小宽度最大，很明显可以用二分解决。

对于判定每个二分的结果，遍历每个单词，并记录当前一行所用的宽度。若当前宽度大于设定的宽度，则换到下一行，并记录所用的行数 $k$。若 $k \le m$，则设定成立，并继续二分缩小范围，得出答案。

## Code
记得开 ```long long```，并注意二分右端点 $r$ 的初值。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
#define ll long long
ll l=1,r=1e15,n,m,a[maxn],ans;
inline int check(ll x){
	ll now=0,k=1;
	for(int i=1;i<=n;i++){
		if(a[i]>x) return 0;
		if(!now) now--;
		if(now+a[i]+1<=x) now+=a[i]+1;
		else k++,now=a[i];
	}
	return k<=m;
}
int main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1; 
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：Allen_yang (赞：3)

## 题目大意
给定一个包含 $N$ 个单词的句子，其中第 $i$ 个单词的宽度是 $L_i$。

单词显示在由宽度为 $1$ 的空格分隔的窗口中。更准确地说，当句子显示在宽度 $W$ 的窗口中时，满足以下条件。

- 该句子分为几行。
- 第一个单词显示在顶行的开头。
- 第 $i$ 个单词 $(2≤i≤N)$ 的显示方式为：在第 $i$ 个单词之后间隔 $1$
第 $i - 1$ 个单词，或位于包含第 $i - 1$ 个单词的行下方的行的开头。 它不会在其他地方显示。
- 每行的宽度不超过 $W$。这里，行的宽度是指从最左边的单词的左端到最右边的单词的右端的距离。
- 最后的行数小于等于 $M$。

求最小的 $W$。

## 题目思路
显然，当 $W$ 的大小增加到某个临界值，不论增加多少，都一定可以满足所有条件。因为当临界值满足条件时，只需要将临界值的宽度往右边增加，不需要改变行数。有时候甚至可以减少行数。

满足单调性，考虑二分答案。

左边界条件为单词中最长一个的长度，右边界条件为把所有单词排成一整行的长度。也就是:
$$ \sum_{\mathclap{i = 1}}^{\mathclap{n}} L_i + n - 1$$

## Code
```cpp
// LUOGU_RID: 124266199
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const ll MAXN = 2e5 + 5;
ll len[MAXN], n, m, lmax = 0, lmin = 0;
bool check(ll le){
	ll cnt = 1, sum = -1;  // cnt是行数，sum是当前的Li总和
   // sum赋值-1是为了省略判断是否加上单词间隔
	for(int i = 1; i <= n; i ++){
		sum += len[i] + 1;  
		if(sum > le){  // 判断是否需要换行
			cnt ++;
			sum = len[i];
		}
		if(cnt > m){  // 判断行数是否合法
			return false;
		}
	}
	return true;
}
int main(){
	cin >> n >> m;
	for(ll i = 1; i <= n; i ++){
		cin >> len[i];
		lmax += len[i];
		lmin = max(lmin, len[i]);
	}
	ll l = lmin, r = lmax + n - 1, ans = 0;
	while(l <= r){
		ll mid = (l + r) >> 1;
		if(check(mid)){
			ans = mid;
			r = mid - 1;
		}else{
			l = mid + 1;
		}
	}
	cout << ans;
	return 0;
} 
```

---

## 作者：zhizhi_c (赞：2)

一眼丁真，鉴定为：数列分段 II。

### 前置题目：
[数列分段 I](https://www.luogu.com.cn/problem/P1181)

此题很简单，就是尽可能的使每一段接近 $M$，就是再加一个数就会大于 $M$。

[数列分段 II](https://www.luogu.com.cn/problem/P1182)

此题是二分，由于 $M$ 越大分出来的段数最少，满足单调性，所以二分。

### solution：
其实你可以把此题理解为数列分段 II，意思其实就是把 $N$ 个单词分成 $M$ 组，求这些单词组经过处理后的长度之和的最大值的最小值。
### AC 代码：
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int n, m;
ll l, r;
int a[200005];

bool check(ll mid) {
	ll c = 0, sum = -1;
	for (int i = 1; i <= n; sum += a[i++] + 1) //若处于行中，则需再加一个空格，而行头则正好与-1抵消
		if (sum + a[i] + 1 > mid) sum = -1, c++; //条件被合并，所以 sum 初始值为-1
	return c >= m;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), l = max(l, (ll)a[i]), r += a[i];
	r += n - 1; //最坏情况是 n 个单词排成 1 行，也就是 a 数组之和，要注意间隔不要漏
	while (l < r) {
		ll mid = l + r >> 1;
		if (check(mid)) l = mid + 1;
		else r = mid;
	}
	printf("%lld", l);
	return 0;
}
```

---

## 作者：Genius_Star (赞：2)

~~突然发现最近 ABC 的好多 C/D 题都是二分答案。~~

### 题意：

给你了 $n$ 个单词，每一个单词的长度为 $l_i$，有一个窗口，它的长度（竖着的）为 $m$（即有 $m$ 行），横着的不限，从第一个单词开始，放在了第一行的第一个位置，对于第 $i$ 个单词，可以放在第 $i-1$ 的下边或者右边，如果放在右边会多一个空格字符，放在下面则不会。

问横着的长度最少是多少可以放下所有字符？

### 思路：

考虑二分答案算法，我们二分窗口的横着的长度，现在我们考虑如何 $O(n)$ 的验证。

考虑贪心的去验证，即只要当前行可以放下下一个字符，那就放，否则就换行，最后我们判断一下换行的次数要小于 $m$ 就可以了。

还需要注意一点儿小细节，如果二分答案的这个值比 $l_i$ 小的话，我们就可以直接返回 $0$ 错误了，毕竟窗口连一个字符都放不下了。

时间复杂度：$O(n \log B)$（$B$ 为横着长度的范围）

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=200200;
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
ll n,m;
ll a[N];
bool check(ll x){ //验证答案 
	ll sum=0,k=1;
	for(int i=1;i<=n;i++){
		if(a[i]>x)
		  return 0;
		if(sum+a[i]>x){
			sum=0;
			k++;
		}
		sum+=a[i]+1;
	}
	return (k<=m);
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
	  a[i]=read();
	ll l=1,r=1e18;
	while(l<r){ //二分答案 
		ll mid=(l+r)>>1;
		if(check(mid))
		  r=mid;
		else
		  l=mid+1;
	}
	write(l);
	return 0;
} 
```


---

## 作者：Halberd_Cease (赞：1)

显然，一行宽度越宽，那么它可以容下的字符串一定不小于宽度窄的，因此宽度从小到大的时候，答案是单调不升的。

那么考虑二分答案，每一次钦定一个宽度 $len$，然后让字符排版，贪心来想如果可以塞下就塞在这一行，否则塞到下一行。

然后就是裸的二分了。

细节：可以直接把每一个单词的长度加一，答案方案末尾会多出来一个空格，再减掉就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, k, t, ans;
int a[200005];
bool f(int mid)
{
	int gr = 1, sum = 0;
	for (int i = 1; i <= n; i++)
	{
		if (a[i] > mid)
			return 0;
		if (sum + a[i] <= mid)
		{
			sum += a[i];
		}
		else
			sum = a[i], gr++;
	}
	return gr <= k;
}

signed main()
{
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		a[i]++;
	}

	int l = 2, r = 1e18;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (f(mid))
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	cout << ans - 1 << endl;
	return 0;
}
```

---

## 作者：zhujiangyuan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_d)

二分好题，但是赛时第一眼没看出来是二分，掉大分啊啊啊。

二分这个宽度 $x$，判断每一行的宽度都不超过 $x$ 的情况下行数是否小于等于 $m$，如果小于 $m$，说明最终答案小于等于 $x$，更新二分右边界，否则说明答案大于 $w$，更新答案左边界。

check 代码：
```cpp
bool check(ll x)
{
	ll sum=0,now=0;//sum为行数，now为当前行的宽度
	for(int i=1;i<=n;++i)
	{
		if(now+a[i]>x) now=a[i]+1,sum++;//加上a[i]后当前行宽度大于x，再新开一行
		else if(now+a[i]==x) now=0,sum++;///加上a[i]后当前行宽度正好等于x，now变为0
		else now+=a[i]+1;//加上a[i]和两个数字之间的宽度1
	}
	if(now) sum++;//如果最后一行有数字，答案加1
	return sum<=m;
}
```

[完整代码](https://atcoder.jp/contests/abc319/submissions/45411247)

---

## 作者：_zzzzzzy_ (赞：0)

# 思路

发现可以二分长度然后进行判断，这里只讲一些可能会错的细节和一些实现操作。

我们在枚举下一个单词的时候，就先加上他，然后判断是否超过了，假入超过了就新开一行，否则就让现在的长度加上单词的长度，然后最后要判断是否顶到了一行的最后，假如没顶到就加上一。

然后最后要把行数加一。

最后就是要把二分的上下边界求对，下边界就是最大的单词长度，上边界就是所有单词加起来，最后加上单词数量个空格。

# 代码

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (l); i >= (r); i--)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
using i64 = long long;
const int maxn = 1000000;
int n, m;
i64 a[maxn];
i64 check(i64 mid) {
	i64 now = 0;
	i64 cnt = 0;
	rep(i, 1, n) {
		now += a[i];
		if (now > mid) {
			cnt++;
			now = a[i];
		} if (now != mid) {
			now++;
		}
	}
	if (now) {
		cnt++;
	}
	return cnt > m;
}
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	
	cin >> n >> m;
	i64 l = 0, r = 0, ans;
	rep(i, 1, n) {
		cin >> a[i];
		l = max(l, a[i]);
		r += a[i] + 1;
	}
	while (l <= r) {
		i64 mid = (l + r) / 2;
		if (check(mid)) {
			l = mid + 1;
		} else {
			r = mid - 1;
			ans = mid;
		}
	}
	cout << ans << "\n";
	return 0;
}
```

---

## 作者：FreedomKing (赞：0)

二分板子题。

### 思路

直接看巨大的数据范围，枚举宽度绝对是不行的，考虑二分宽度，唯一有点东西的就是判断函数了，关于它的解释直接看代码注释。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k,l,r;
bool check(int x){
	int cnt=1,sum=0;
   //cnt 为行数计数器，需要先开一行来放东西
   //sum 是目前这行已经放了多少
	for(int i=1;i<=n;i++){
		sum+=a[i];//直接加上
		if(sum>x){//超出长度了
			cnt++;//新开一行
			sum=a[i];//把它放到新的一行
		}
		if(sum!=x) sum++;//没有到行末，加上空格
	}
	return cnt<=m;//判断是否在 m 行内
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		l=max(l,a[i]);
		r+=a[i]+1;
	}
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
```

---

## 作者：zhangjiting (赞：0)

## 思路

这道题一看就是二分答案。

我们二分一个数，下边界为 $\max_{i = 1}^{n} a_i$，上边界是 $\sum_{i = 1}^{n} (a_i+1)$。


根据题意，直接模拟，我们可以写出 `check` 函数。

```cpp
bool check(int x){
	int s=1;
	int now=x;
	for(int i=1;i<=n;i++){
		if(now-a[i]<0){
			now=x;
			s++;
		}
		now-=a[i];
		now--;
	}
	if(s>m) return 0;
	else return 1;
}
```
注意，记录当前宽度对应的高度的变量，也就是我的代码里面的 $s$，初值要赋为 $1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005];
int n,m;
bool check(int x){
	int s=1;
	int now=x;
	for(int i=1;i<=n;i++){
		if(now-a[i]<0){
			now=x;
			s++;
		}
		now-=a[i];
		now--;
	}
	if(s>m) return 0;
	else return 1;
}
signed main(){
	int l=0,r=0,ans;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],l=max(l,a[i]),r+=a[i]+1;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc319_d)

## 题目大意

有 $N$ 个单词，第 $i\space (1\le i\le N)$ 个单词的长度是 $L_i$。现在我们要把这些单词排成 $M$ 行，排列的规则如下：

- 第一行的第一个单词在第一行的第一个格。

- 两个单词间要有一个空格，空格占 $1$ 个位置。

- 行末的单词后边不用空格。

- 单词不可以换行写。

现在我们要求在满足上述排列规则的条件下，每行最少要多少个位置才能使得单词可以**恰好**排成 $M$ 行。

## 思路

一道很明显的**二分答案题**。

我们考虑在读入完数据后用二分答案的方法，查找到最小的单行位置数并输出。

在检查当前找到的单行位置数是否满足条件时，可以采用双重循环枚举。第一重循环枚举每一行，第二层循环**贪心**地选择可以放进这行的单词，并放入，此时要分类讨论：

- 如果这行剩下的位置可以放进去这个单词和一个空格，并且放入这个单词和空格后仍有地方放入下一个单词，就放入这个单词**和一个空格**。

- 如果这行剩下的位置只能放进去一个单词，就放入这个单词并**跳出循环**。

- 如果单词被放完了，这行还没有结束，就跳出循环。

- 如果这行剩下的位置放不进去下一个单词了，就跳出循环。

- 如果以上情况都不符合，跳出循环（防止死循环或越界）。

之后我们判断，如果单词被**放完了且还没放到第 $M$  行**，说明单行位置数定小了，返回主函数继续二分。

如果放完了 $M$ 行，就分两类讨论：

- 如果单词还没放完，说明单行位置数定小了。

- 如果单词放完了，说明单行位置数可以继续缩小。

返回主函数不断二分，最后输出结果即可。

### 注意事项

- 数据不保证在 $32$ 位整型范围内，记得开 long long。

- 防止 AT 的 RMJ 爆 UKE 小技巧：不要在 Wating 的时候刷新。

## AC Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pf push_front
#define pob pop_back
#define pof pop_front
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
inline void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}
const int N=2e5+10;
ll n,m,a[N],sum;//记得开 long long。
inline bool check(ll x){
	ll p=0;//当前放入了 p 个单词。
	for(int i=1;i<=m;++i){//循环枚举 m 行。
		ll cnt=0;//这行共占了几个位置。
		while(1){//分类讨论。
			if(p>=n)break;
			if(cnt+a[p+1]+1<x)cnt+=a[++p]+1;
			else if(cnt+a[p+1]==x){
				cnt+=a[++p];
				break;
			}
			else if(cnt+a[p+1]<=x&&p+2<=n&&cnt+a[p+1]+1+a[p+2]>x){
				p++;
				break;
			}
			else if(cnt+a[p+1]>x)break;
			else break;
		}
		if(i<m&&p==n)return 1;
		
	}
	if(p<n)return 0;
	else return 1;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		scanf("%lld",a+i);
		sum+=a[i]+1;//求最大可能的单行位置数，方便上界赋值。
	}
	ll l=1,r=sum,ans;
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```

[已 AC](https://www.luogu.com.cn/record/124265173)

---

## 作者：ldj2006 (赞：0)

# [ABC319D] Minimum Width 题解

## 题意分析

&emsp;&emsp;给定 $n$ 个单词，现在想像“记事本”一样把它们依次地一行一行显示出来。每个字母宽度为一，单词之间需要有空格，宽度也为一。一个单词不可以成两部分显示在两行。如果单词最后一个字母来到行末，直接换行，不用空格。

&emsp;&emsp;给定窗口最大高度 $E$ ，求窗口最小宽度 $L$。

## 思路

&emsp;&emsp;根据朴素的生活经验，随着 $L$ 的增大，$E$ 非严格单调递减。于是我们可以二分 $L$，然后解决。

&emsp;&emsp;为什么是单调的呢？因为如果一行越宽，那么这一行可能容纳的单词数量就越多。那么总行数就一定是会持平于当前或者变少的。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 2e5 + 5;

LL n,m,a[N];

LL check(LL width)
{
	LL cnt = 1;
	LL idx = 0;
	for(int i = 1;i <= n;i++)
	{
		if(width < a[i])
			return 1e18;
		if(idx + a[i] + 1 <= width)
		{
			idx += a[i] + 1;
		}
		else if(idx + a[i] == width)
		{
			idx += a[i];
			cnt++;
			idx = 0;
		}
		else
		{
			cnt++;
			idx = a[i] + 1;
		}
	}
	if(idx == 0) cnt--;
	return cnt;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
	{
		cin >> a[i];
	}
	LL l=0,r=1e18,mid;
	while(l < r)
	{
		mid = (l + r) / 2ll;
		LL res = check(mid);
		if(res > m)
			l = mid+1ll;
		else if(res <= m)
			r = mid;
	}
	cout << l << "\n";
	return 0;
}
```

---

## 作者：ZeroF (赞：0)

本题考虑使用二分答案。

## 思路

关于本题单调性的证明：因为显示器的宽度越大，一行能显示的宽度越多，所以显示需要的行数越少（单词总量不变）。所以显示器的宽度和显示需要的行数**具有单调递减的关系**，所以可以使用二分。

二分枚举显示器的宽度 $w$，然后计算**以 $w$ 为宽度显示单词需要的最少行数**，如果需要的行数小于等于 $m$，则符合要求，否则不符合要求。

怎么计算呢？

如果显示器的宽度 $w$ 小于单词的最大宽度 $mw$，说明一个单词都无法放进显示器中，显然是不符合要求的。

令 $sum$ 表示当前行已经用了多少宽度，$cnt$ 表示当前用了多少行，一次枚举单词的长度 $l_i$，如果当前宽度加上一个空格和 $l_i$ 的长度大于 $w$，说明当前行已经放不下这个单词了，需要新开一行，让 $cnt$ 加 $1$，并且让 $sum$ 等于 $l_i$，否则 $sum$ 加上 $l_i$ 和一个空格的长度。

时间复杂度：二分的复杂度是 $O(\log n)$，计算一遍的复杂度是 $O(n)$，整体时间复杂度 $O(n \log n)$。 

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l[1000010],n,m,p,mw;
bool check(int w){
    if(w<mw)return 0;
	int cnt=1,sum=0;
	sum=l[1];
	for(int i=2;i<=n;i++){
		if(sum+l[i]+1>w)sum=l[i],cnt++;
		else sum+=l[i]+1;
	}
	return cnt<=m;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>l[i],mw=max(mw,l[i]);
	for(int i=(1LL<<62);i;i>>=1)if(!check(p+i))p+=i;
	cout<<p+1LL<<endl;
	return 0;
}
```

---

## 作者：xiaoming007 (赞：0)

看要要求行数最小，于是可以考虑二分答案。

设当前二分出来行长度为 $x$，若之前所有的 $a_i$ 相加与空格长度 $> x$，显然需要换一行。合法条件为当前需要行数 $\leq m$。

最小的 $x$ 即为答案。

[代码](https://atcoder.jp/contests/abc319/submissions/45370959)

---

## 作者：iCostalymh (赞：0)

## 题目翻译（简化）

给定 $N$ 个序列，每个序列有一个长度 $L_i$，给序列最多分为 $M$ 段，每一段中相邻的序列隔有 $1$ 个单位长度的空格，并且每一段的开头和结尾没有空格。求给这个序列分段后的最大段长的最小值。

## 分析

原题没有说得这么明显，思考一下发现这题的答案满足单调性，也就是说能二分答案。这样就可以二分每一个最大段长，然后无脑 check 就行了。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int maxn(2e5 + 3);

int n, m, a[maxn], sum[maxn], maxlen;

inline bool check(int x) {
    int last(0), cnt(0);

    for (int i = 1; i <= n; ++i) {
        if (sum[i] - sum[last] - 1 <= x) continue;
        last = i - 1;
        ++cnt;
        if (cnt > m - 1) return false;
    }

    return true;
}

inline int bsearch(int l, int r) {
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    return l;
}

signed main() {
    scanf("%lld%lld", &n, &m);

    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        maxlen = max(maxlen, a[i]);
        ++a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    printf("%lld\n", bsearch(maxlen, sum[n]));

    return 0;
}
```

---

## 作者：tder (赞：0)

[$\Large\color{black}\textbf{AT\_abc319\_d Minimum Width}$](https://www.luogu.com.cn/problem/AT_abc319_d) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/AT_abc319_d)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-AT-abc319-d)

~~二分答案 + 模拟~~

---

$$\large\textbf{题意}$$

小明想在一个软件窗口里显示一句共有 $n$ 个单词的句子，其中第 $i$ 个单词的长度为 $l_i$。

假如这个窗口的宽度为 $w$，那么句子中的单词显示按照如下约定：

- 句子可以被切分成若干行

- 第 $1$ 个单词显示在第 $1$ 行的开头

- 对于 $\forall\ 2\le i\le n$，第 $i$ 个单词只可以显示在上一个单词结束后空一格之后开始的位置，或是在上一个单词的下一行的开头

- 每一行的长度均不能超过窗口宽度 $w$

现在小明希望显示的结果不超过 $m$ 行，求可能的最小的窗口宽度 $w$。

---

$$\large\textbf{思路}$$

显然地，窗口宽度 $w$ 最小为单词长度的最大值，即每个单词独占 $1$ 行时，$\min(w)=\max(l_i)$。最大为单词长度的总和加上空格数，即所有单词均挤在 $1$ 行时，$\min(w)={\sum^{n}_{i=1}}+(n-1)$。综上，$w\in[\max(l_i),{\sum^{n}_{i=1}}+(n-1)]$。

考虑在该范围内进行二分。

~~其实从 $1$ 到 $10^{18}$ 二分也刑（（（~~

对于每次二分进行模拟，用 $cnt$ 表示行数，$t$ 表示当前行的字符数。依次遍历每一个单词，如果当前 $t+l_i+1$ 已经超出了宽度 $w$ 则换行 $cnt\leftarrow cnt+1$，否则 $t\leftarrow t+a_i+1$。最后判断 $cnt$ 和 $m$ 的大小关系，如果 $cnt\le m$ 则继续二分查找左半边，否则查找右半边。

**注意要特判当任意单个单词长度已经超过宽度 $w$ 时直接查找右半边。**

**温馨提逝：$10^9\times(2\times10^5)$ 会！爆！炸！**

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long // DILL 万岁 qwq
const int N = 2e5 + 10, M = 1e18;
int n, m, a[N];
bool check(int x) { // 判断在左边还是右边
	if(a[1] > x) return 0; // 注意特判
	int t = a[1], cnt = 1;
	for(int i = 2; i <= n; i++) {
		if(a[i] > x) return 0; // 特判在右边
		if(t + a[i] + 1 > x) { // 溢出则换行
			cnt++; // 行数累加
			t = a[i];
		}
		else t += a[i] + 1; // 注意要 +1 空格占位
	}
	return cnt <= m; // 判断行数是否不超过 m
}
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin>>n>>m;
	int l = M, r = n - 1; // w 的最大最小值
	for(int i = 1; i <= n; i++) {
		cin>>a[i];
		l = min(l, a[i]); // 取最小值
		r += a[i]; // 累计和
	}
	int ans = M;
	while(l <= r) { // 二分答案
		int mid = (l + r) / 2;
		if(check(mid)) r = mid - 1, ans = mid; // 在左边
		else l = mid + 1; // 在右边
	}
	cout<<ans;
	return 0;
}
```

---

