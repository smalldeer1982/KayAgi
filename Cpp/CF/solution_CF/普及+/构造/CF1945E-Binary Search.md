# Binary Search

## 题目描述

Anton got bored during the hike and wanted to solve something. He asked Kirill if he had any new problems, and of course, Kirill had one.

You are given a permutation $ p $ of size $ n $ , and a number $ x $ that needs to be found. A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

You decided that you are a cool programmer, so you will use an advanced algorithm for the search — binary search. However, you forgot that for binary search, the array must be sorted.

You did not give up and decided to apply this algorithm anyway, and in order to get the correct answer, you can perform the following operation no more than $ 2 $ times before running the algorithm: choose the indices $ i $ , $ j $ ( $ 1\le i, j \le n $ ) and swap the elements at positions $ i $ and $ j $ .

After that, the binary search is performed. At the beginning of the algorithm, two variables $ l = 1 $ and $ r = n + 1 $ are declared. Then the following loop is executed:

1. If $ r - l = 1 $ , end the loop
2. $ m = \lfloor \frac{r + l}{2} \rfloor $
3. If $ p_m \le x $ , assign $ l = m $ , otherwise $ r = m $ .

The goal is to rearrange the numbers in the permutation before the algorithm so that after the algorithm is executed, $ p_l $ is equal to $ x $ . It can be shown that $ 2 $ operations are always sufficient.

## 样例 #1

### 输入

```
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1```

### 输出

```
0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3```

# 题解

## 作者：Sternenlicht (赞：9)

思路：分类讨论。

先要想到一个性质：若 $x$ 在二分过程中没有作为 $p_m$ 进行比较，则二分结束后将 $x$ 与 $p_l$ 交换，并不会影响原来二分的运行过程。

1. 二分结束后 $p_l = x$。
	
    此时显然不用交换，已经满足题意。输出 ``0`` 即可。

2. 二分结束后 $p_l \neq x$。
    
	* $p_l < x$。这时，我们要考虑 $x$ 在二分过程中是否作为 $p_m$ 进行比较过。
    
    	若是，那么当 $x = p_m$ 的时候，$l$ 是要赋为 $m$ 的，此时 $p_l = x$。那为什么最后 $p_l < x$ 呢？显然，在此次判断之后，$l$ 还被更新过至少 $1$ 次。我们考虑将二分结束后的 $p_l$ 与 $x$ 交换后，会发生什么。由于 $p_l$ 和 $x$ 均满足 $\le x$ 这个条件，即都是使 $l$ 更新，所以二分时进行的操作是一样的！也就是说，把这两个数交换后，并不会影响原二分的运行过程。那么交换 $x$ 和 $p_l$ 即可，操作次数为 $1$。
        
       若否，那么由性质可知，交换 $x$ 和 $p_l$ 即可，操作次数为 $1$。
       
  	* $p_l > x$。这时我们想想，什么时候才会更新 $l$？当 $p_m \le x$ 的时候，$l$ 会赋值为 $m$。也就是说，如果 $l$ 被更新过，那么 $p_l$ 是一定满足条件 $p_l \le x$ 的。但现在 $p_l > x$，说明 $l$ 并没有被更新过！即二分过程中，只有 $r$ 在更新。那什么时候会更新 $r$？当 $p_m > x$ 的时候。这说明 $x$ 没有作为 $p_m$ 进行比较过，那么由性质可知，交换 $x$ 和 $p_l$ 即可，操作次数为 $1$。
    
现在观察分类讨论的第 $2$ 种情况中的 $3$ 种状态，发现它们竟然是一样的。那在程序中把它们合并在一起就行了。

注意输出的是交换数字的位置，在读入时记录 $x$ 的出现位置 $pos$ 即可。

```cpp
#include <bits/stdc++.h>
#define il inline
namespace Fast_IO {
	template <typename T> il void read(T &x) {
		x = 0; int f = 0; char ch = getchar();
		while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
		while (isdigit(ch)) x = x * 10 + (ch - 48), ch = getchar();
		x = f ? -x : x;
	}
	template <typename T, typename ...Args>
	il void read(T &x, Args& ...args) {read(x), read(args...);}
	template <typename T> il void write(T x, char c = '\n') {
		if (x) {
			if (x < 0)x = -x, putchar('-');
			char a[30]; short l;
			for (l = 0; x; x /= 10) a[l ++] = x % 10 ^ 48;
			for (l --; l >= 0; l --) putchar(a[l]);
		} else putchar('0');
		putchar(c);
	}
} using namespace Fast_IO;
using namespace std;

const int Maxn = 200005;
int a[Maxn];
signed main() {
	int T; read(T);
	while (T --) {
		int n, x, ans; read(n, x);
		for (int i = 1; i <= n; i ++) {
			read(a[i]);
			if (a[i] == x) ans = i;
		}
		int l = 1, r = n + 1;
		while (r - l > 1) {
			int mid = (l + r) >> 1;
			if (a[mid] <= x) l = mid;
			else r = mid;
		}
		if (a[l] == x) puts("0");
		else puts("1"), write(l, ' '), write(ans);
	}
	return 0;
}
```

---

## 作者：spfa_ (赞：8)

[CF1945E Binary Search](https://www.luogu.com.cn/problem/CF1945E)

### 题目翻译

给一个排列 $a$ 和一个数 $x$，可以交换任意两个位置（可以不做，次数不超过 $2$），满足若对其做二分（见题目），最后落到的位置为 $x$，给一个交换方案。

### 题目分析

若直接对其做二分，结果就是 $x$，那么就不用操作。

否则，我们可以考虑将 $x$ 交换到二分所落到的位置，有两种情况：

1. 若 $x$ 不在任意一个 $m$ 上（换句话说就是没有判定这个数），则直接交换即可。

2. 若 $x$ 在其中一个 $m$ 上，如果我们交换了它，那么可能会影响二分的过程。所以我们可以选择一个不在判定点上的数且小于 $x$，交换这两个数。再将 $x$ 交换到二分落到的点上，次数为 $2$。

那么问题来了，怎么确定一定存在一个不在判定点上且小于 $x$ 的数？若不存在小于 $x$ 的数，那么显然 $x=1$，这种情况是显然不用操作的。

[code](https://codeforces.com/contest/1945/submission/252393755)

---

## 作者：JOE_ZengYuQiao_0928 (赞：6)

## [先看题](https://www.luogu.com.cn/problem/CF1945E)
## 题目大意：
在一个未排序的 $a$ 数组中不断交换两个数（最多两次），使得二分查找 $x$ 的结果是正确的。

求交换方法。
## 解题思路
经过我 ~~两分半时间~~ 的推理，得出一条结论：因为二分中 $a_{mid} \le x$ 的约束，所以二分的结果 $a_1$ 一定不比  $x$ 大，那么如果交换 $x$ 的位置和二分的结果位置 $l$ 后再次二分，结果依然还是那个位置，那不就是正确答案了吗？

## 代码 ~~相信大多数人会看到这里~~
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,a[N],x,ans;
void w(){
	ans=0;//清空 
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==x)ans=i;//统计x的位置 
	}
	int l=1,r=n+1; 
	while(l+1<r){
		int mid=(l+r)/2;
		if(a[mid]<=x)l=mid;
		else r=mid;
	}//简单的二分 
	if(a[l]==x)cout<<"0\n";//找到了正确位置不用交换 
	else cout<<"1\n"<<l<<" "<<ans<<"\n";//没找到正确位置不用交换 
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int t;
	cin>>t;
	while(t--){
	    w(); 
	}//CF的题有多组数据 
	return 0;
}	 	 		  		  	  	 				 	 			
```

---

## 作者：__Floze3__ (赞：3)

## 思路简述

由于这道题毒瘤的二分写法，我们可以发现这样一个事实：至多只需要 $1$ 次操作，便可以使最后二分得到的值为 $x$~~（所以题目在骗人）~~。这个方法即为：将 $x$ 所在的位置与最终得到的 $l$ 交换即可。以下是证明：

#### 1. 最后得到的值即为 $x$

那么我们不需要进行任何操作。

#### 2. 最后得到的值比 $x$ 小

那么交换 $x$ 与位置为 $l$ 的值并不会对二分的过程造成任何影响，直接交换即可。

#### 3. 最后得到的值比 $x$ 大

我们知道这样一个事实：最后得到的 $l$ 如果不是 $1$，那么一定是之前被当成 $m$ 检查过的。那么，最后得到的值比 $x$ 大只有一种可能：$l$ 为 $1$，在之前的二分过程中，每一次取到的 $m$ 所对应的值都比 $x$ 大，因此区间的右边界不断左移。那么，容易想到，我们将 $x$ 与第一个元素交换不会对二分的过程造成任何影响。

综上所示，只需要不多于 $1$ 次的操作即可让二分的结果为 $x$。

## 代码

```cpp
#include <bits/stdc++.h>
#define read std::cin
#define write std::cout

const int N = 2e5 + 5;

int T, n, x, a[N], pos;

int main() {
    read >> T;
    while (T--) {
        read >> n >> x;
        for (int i = 1; i <= n; i++) {
            read >> a[i];
            if (a[i] == x) pos = i;
        }
        int l = 1, r = n + 1;
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            if (a[mid] <= x) l = mid;
            else r = mid;
        }
        if (a[l] == x) write << "0\n";
        else write << "1\n" << l << ' ' << pos << '\n';
    }
    return 0;
}
```

---

## 作者：TSY48 (赞：2)

**解题思路**

本蒟篛在看到题的第一个想法就是对原数组进行二分，将二分的结果与 $x$ 交换（若相等就不换），结果过了。

下面来证明下介个结论：

分析以原数列二分出的位置（设为 $pos$）与 $x$ 的关系，不难发现若 $l \ne 1$，则 $p_{pos}\le x$（因为任意一次执行 $l=mid$ 时，都满足 $p_{mid}\le x$）。而若 $l=1$，则 $p_{1}=x$（不然 $x$ 就不存在了），下面只需考虑 $l\ne1$ 时的情况即可。

有上述可知，在 $l>1$ 时，$p_{pos} \le mid$，则在二分中不对结果造成任何影响。**结论成立**。

AC code
```
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define m_p make_pair
#define str string
#define lowbit(x) (x&(-x))
#define fi first
#define se second
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
//typedef __int128 it;
const int Maxn=2e5+10;
const int inf=0x3f;
int p[Maxn];
inline void solve()
{
    int n,x;
    scanf("%d%d",&n,&x);
    int pos=-1;
    for(int i=1;i<=n;i++) scanf("%d",&p[i]),pos=(p[i]==x?i:pos);
    int l=1,r=n+1;
    while((r-l)>1){
        int mid=(l+r)>>1;
        if(p[mid]<=x) l=mid;
        else r=mid;
        // printf("%d %d\n",l,r);
    }
    if(p[l]==x) printf("0\n");
    else printf("1\n%d %d\n",l,pos);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) solve();
    return 0;
}
```

---

## 作者：Sorato_ (赞：2)

# CF1945E Binary Search

## 题目大意

给定一个 $1\sim n$ 的排列 $A$（不保证有序），对这个排列用如下代码片段二分，查找 $m$ 的位置。

```c++
int l=1,r=n+1;
while(r-l>1)
{
    int mid=(l+r)/2;
    if(A[mid]<=m)	l=mid;
    else	r=mid;
}
cout<<l;
```

显然不一定能查找到正确位置，所以在开始查找之前，可以进行至多 $2$ 次操作，每次操作可交换任意两个数的位置，可以保证 $2$ 次操作一定能使答案正确。

## Solve

由于题面说 $2$ 次操作一定能使答案正确，我们不妨大胆地猜测一下：

先对原数列使用上面的代码，进行二分，将二分出来的位置（记为 $x$）与 $m$ 的位置交换即可。

然后就发现 AC 了。

考虑证明一下正确性：

**显然我们最后二分出的 $p_x$ 一定是 小于等于 $m$ 的。**然后考虑分情况讨论：

- 如果二分过程中 $\forall mid,A_{mid}\neq m$，那么这样交换肯定是没问题的，因为交换之后不会对 `A[mid]<=m` 这句话有影响。
- 如果 $\exist mid,A_{mid}=m$，那么交换之后 $A_{mid}$ 就等于 $p_x$ 了，此时 `A[mid]<=m` 仍然为真，不影响二分端点的变化。

得证。

## Code

```c++
#include<bits/stdc++.h>
#pragma GCC optimize(1,2,3,"Ofast","inline")
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int t,n,m,a[200010],pos;
signed main()
{
	t=read();
	for(int i=1;i<=t;i=-~i)
	{
		n=read();m=read();
		for(int j=1;j<=n;j=-~j)
		{
			a[j]=read();
			if(a[j]==m)	pos=j;
		}
		int l=1,r=-~n;
		while(r-l>1)
		{
			int mid=l+r>>1;
			if(a[mid]<=m)	l=mid;
			else	r=mid;
		}
		printf("1\n%lld %lld\n",l,pos);
	}
	return 0;
}
```

---

## 作者：Exp10re (赞：1)

构造好玩。

## 解题思路

注意到只能交换两次，猜测两次交换都与 $x$ 有关。

分析题目的二分，发现位置 $1$ 不会在最后一次二分之前被访问。

考虑一下构造方法：

- 对原数组进行二分查找。

- 查找过程中碰到 $x$ 就交换 $(1,x)$。

- 对于最终查找到的位置 $p$ 交换 $(p,x)$。

由于以上性质正确性显然。

代码如下：

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MAXN=200100;
long long a[MAXN],mov[3][2],m;
void movment(long long ta,long long tb)
{
	if(ta==tb)
	{
		return;
	}
	m++;
	mov[m][0]=ta;
	mov[m][1]=tb;
	swap(a[ta],a[tb]);
	return;
}
void work()
{
	long long n,p,i,j,recx,x;
	scanf("%lld%lld",&n,&x);
	for(i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		if(a[i]==x)
		{
			recx=i;
		}
	}
	m=0;
	long long l=1,r=n+1,mid;
	while(r-l>=2)
	{
		mid=(l+r)/2;
		if(a[mid]==x)
		{
			movment(1,mid);
			recx=1;
		}
		if(a[mid]<=x)
		{
			l=mid;
		}
		else
		{
			r=mid;
		}
	}
	movment(recx,l);
	printf("%lld\n",m);
	for(i=1;i<=m;i++)
	{
		printf("%lld %lld\n",mov[i][0],mov[i][1]);
	}
	return;
}
int main()
{
	long long T;
	scanf("%lld",&T);
	while(T--)
	{
		work();
	}
	return 0;
}
```

---

## 作者：_qingshu_ (赞：0)

# 思路：

可以把整个序列分为 $p_i\le x$ 和 $p_i>x$，我们先模拟一次二分的过程，找到最后 $lef$ 的位置。

后面我们分类讨论：

- $a_{lef}=x$ 不需要交换。

- $lef=0$ 说明二分过程中不存在 $p_i\le x$ 的情况，那么我们最后的 $rig=1$，所以我们把目标点与 $p_1$ 替换。

- $lef\ne 0$ 一定有 $p_{lef}\le x$，同时 $x\le x$，所以我们可以把目标点与 $lef$ 替换。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,lef,rig,a[5200010],id;
inline void solve(){
	cin>>n>>m;lef=1;rig=n+1;
	for(int i=1;i<=n;i++){
		cin>>a[i];if(a[i]==m)id=i;
	}
	while(lef<rig&&rig-lef!=1){
		int mid=lef+rig>>1;
		if(a[mid]<=m)lef=mid;
		else rig=mid;
	}
	if(a[lef]==m)cout<<"0\n";
	else if(lef==0){
		cout<<1<<"\n"<<1<<" "<<id<<"\n";
	}
	else{
		cout<<1<<"\n"<<lef<<" "<<id<<"\n"; 
	}
}
int main(){
	int T;cin>>T;
	while(T--)solve();
}
```

---

## 作者：zxh923 (赞：0)

# CF1945E Binary Search 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1945E)

### 思路

我们首先分类讨论题目中二分的最终值：

+ 如果比目标小，没有影响，直接把最终值换过去即可。

+ 如果是目标，那么显然不用动。

+ 如果比目标大，可以发现他不会更新答案所在边界，那么既然没有更新，说明目标没有参与比较，故交换不会有影响。

综上所述，我们在需要交换的时候直接交换目标所在位置和二分到达位置即可。

### 代码

```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 300005
using namespace std;
int t,n,x,a[N],l,r,mid,pos;
void solve(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]==x)pos=i;
	}
	l=1;r=n+1;
	while(r-l>1){
		mid=(l+r)>>1;
		if(a[mid]<=x)l=mid;
		else r=mid;
	}
	if(pos==l){
		cout<<"0\n";
		return;
	}
	cout<<"1\n"<<pos<<' '<<l<<'\n';
}
signed main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：L_xcy (赞：0)

[CF1945E Binary Search](https://codeforces.com/problemset/problem/1945/E)

---

### 题目翻译

给一个排列 $a$ 和一个数 $x$，可以交换任意两个位置（可以不做，次数不超过 $2$），满足若对其做题目中指定的二分，最后落到的位置为 $x$，给一个交换方案。

---

### 题目分析

我们可以把题目中的二分先模拟下来，大概长这样。

```cpp
while(r-l!=1){
	m=(l+r)/2;
	if(p[m]<=x)	
		l=m;
	else
		r=m;
}
```

这时候大多数人就会想当然的认为跑一遍这个二分，最后把 $l$ 和 $x$ 的位置交换一下就可以了。

正解便是如此，直接模拟即可。

---

### AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
	int n,x,w,a[200005];
	cin >> n >> x;
	for(int i = 1;i <= n; i++)
	{
		cin >> a[i];
		if(a[i] == x)
			w = i;
	}
	int l = 1,r = n+1;
	while(r - l > 1) 
	{
		int m = (r + l) >> 1;
		if(a[m] <= x)
		 	l = m;
		else
			r = m;
	}
	if(w == l)
		cout << 0 << '\n';
	else
		cout << "1\n" << w << ' ' << l << '\n';
}
int main() {
	int T;
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}
```

---

## 作者：fujiayu (赞：0)

# CF1945E - Binary Search
[原题地址](https://codeforces.com/problemset/problem/1945/E)
## 题意：
对于每组数据，给定一个长为 $n$ 的排列 $p$ 和一个 $\le n$ 的正整数 $x$，执行以下二分查找的操作（$p$ **不一定有序**）：

定义变量 $l=1$，$r=n+1$，循环执行下面的操作：
  1. 如果 $r-l=1$，结束循环。
  2. 定义 $mid=\lfloor\frac{l+r}{2}\rfloor$。
  3. 如果 $p_m\le x$，$l=mid$，否则$r=mid$。

在二分查找之前，执行最多 $2$ 次操作，每次操作可以交换 $p_i$ 和 $p_j$，使结束循环之后的 $p_l=x$。

输出格式：对于每组数据，第一行输出一个整数 $k$，表示执行的操作数，第 $2\sim k+1$ 行，每行输出两个整数 $i,j$，表示交换 $p_i$ 和 $p_j$。

**不需要使执行的操作次数最少，输出任意一组解即可**
## 思路：
分类讨论。

如果 $p$ 本身有序，直接输出 `0` 即可，否则，
定义 $a=$ 最后的 $l$。

先说一个特殊性质：$p_a$ 要么 $\le x$，要么不参与 $mid$ 的计算，因为如果 $p_l$ 参与了 $mid$ 的计算， 那么之后一定还有操作，所以如果 $p_l>x$，$l$ 一定会随着 $mid$ 后移，不会 $=a$，所以把 $p_a$ 替换成 $x$ 并不会影响 $a$。

因此，如果 $x$ 不是任何一个 $p_{mid}$，那么 $x$ 位置的变化并不会影响到最终的 $p_l$，此时把 $x$ 和 $p_a$ 交换即可。

如果 $x$ 是一个 $p_{mid}$，枚举 $i$，如果交换 $x$ 和 $p_i$ 之后，新的 $x$ 不在路径上，再交换 $x$ 和 $p_a$ 即可。
## 代码：
```cpp
#include<iostream>
#define int long long
using namespace std;

const int N = 200010;

int n, x, xp, ll;
int a[N];

bool check(int ii)
{
	swap(a[ii], a[xp]);
	int l=1, r=n+1;
	while(r - l != 1)
	{
		int mid = (l + r) >> 1;
		if(mid == ii)
		{
			return false;
			swap(a[ii], a[xp]);
		}
		if(a[mid] <= x)
			l = mid;
		else
			r = mid;
	}
	swap(a[ii], a[xp]);
	ll = l;
	return true;
}

signed main()
{
	int T; cin >> T;
	while(T --)
	{
		bool flag = false, ff = false;
		cin >> n >> x;
		for(int i=1; i<=n; i++)
		{
			cin >> a[i];
			if(a[i] < a[i-1] && i != 1)
				ff = true;
			if(a[i] == x)
				xp = i;
		}
		if(!ff)
		{
			cout << "0\n";
			continue;
		}
		int l=1, r=n+1;
		while(r - l != 1)
		{
			int mid = (l + r) >> 1;
			if(a[mid] == x)
				flag = true;
			if(a[mid] <= x)
				l = mid;
			else
				r = mid;
		}
		if(!flag)
		{
			cout << "1\n" << xp << " " << l << '\n';
			continue;
		}
		for(int i=1; i<=n; i++)
		{
			if(check(i))
			{
				cout << "2\n";
				cout << i << " " << xp << '\n';
				cout << i << " " << ll << '\n';
				break;
			}
		}
	}
	return 0;
}
```

---

