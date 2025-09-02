# [ABC270E] Apple Baskets on Circle

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc270/tasks/abc270_e

$ 1,2,\ldots,N $ の番号がついた $ N $ 個のかごが円状に置かれています。  
 $ 1\leq\ i\ \leq\ N-1 $ についてかご $ i $ の右隣にはかご $ i+1 $ があり、かご $ N $ の右隣にはかご $ 1 $ があります。

かご $ i $ の中には $ A_i $ 個りんごが入っています。

高橋君は最初かご $ 1 $ の前におり、以下の行動を繰り返します。

- 目の前にあるかごの中にりんごがあれば $ 1 $ 個かごから取り出して食べる。その後、りんごを食べたかどうかにかかわらず、右隣のかごの前に移動する。

高橋君がちょうど $ K $ 個のりんごを食べた時点で、各かごの中に残っているりんごの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^{12} $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- りんごは全部で $ K $ 個以上ある。すなわち、$ \sum_{i=1}^{N}A_i\geq\ K $
- 入力に含まれる値は全て整数である

### Sample Explanation 1

高橋君は次のように行動します。 - 目の前にあるかご $ 1 $ の中にりんごがあるので $ 1 $ 個かごから取り出して食べる。その後、かご $ 2 $ の前に移動する。この時点で各かごの中のりんごの個数は $ (0,3,0) $ である。 - 目の前にあるかご $ 2 $ の中にりんごがあるので $ 1 $ 個かごから取り出して食べる。その後、かご $ 3 $ の前に移動する。この時点で各かごの中のりんごの個数は $ (0,2,0) $ である。 - 目の前にあるかご $ 3 $ の中にりんごはない。かご $ 1 $ の前に移動する。この時点で各かごの中のりんごの個数は $ (0,2,0) $ である。 - 目の前にあるかご $ 1 $ の中にりんごはない。かご $ 2 $ の前に移動する。この時点で各かごの中のりんごの個数は $ (0,2,0) $ である。 - 目の前にあるかご $ 2 $ の中にりんごがあるので $ 1 $ 個かごから取り出して食べる。その後、かご $ 3 $ の前に移動する。この時点で各かごの中のりんごの個数は $ (0,1,0) $ である。

## 样例 #1

### 输入

```
3 3
1 3 0```

### 输出

```
0 1 0```

## 样例 #2

### 输入

```
2 1000000000000
1000000000000 1000000000000```

### 输出

```
500000000000 500000000000```

# 题解

## 作者：FFTotoro (赞：6)

赛时二分答案调挂了，因为这题细节很多……希望大家引以为戒，二分答案时一定要注意**答案到底是 $l$ 还是 $mid$，check 函数判断合法性要用 $\le$ 还是 $<$**，以及各类其他问题。

本题容易看出我们可以二分答案高桥君吃的“圈数”，如果完整地吃了 $x$ 圈那么每一个篮子中的苹果数量就变为 $\max\{a_i-x-1,0\}$ 或 $\max\{a_i-x,0\}$。至于到底是哪一个，取决于吃完 $x$ 圈后数量是否不到 $k$，这个地方判断一下即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int n,k,x,l=0,r=0; cin>>n>>k;
  vector<int> a(n);
  for(auto &i:a)cin>>i,r=max(r,i); // 求出答案上限 r
  while(l<=r){
    int mid=l+r>>1,c0=0;
    for(auto &i:a)c0+=min(i,mid); // 判断每个篮子能吃多少个
    if(c0>k)r=mid-1;
    else l=mid+1,x=mid; // 调端点
  }
  for(auto &i:a)k-=min(i,x);
  for(auto &i:a){
    if(k>0){ // k 是否还有剩
      if(i-x-1>=0)cout<<i-x-1<<' ',k--; // 这一个篮子还剩下苹果，如下同理
      else cout<<"0 "; // 没剩下任何苹果
    }
    else cout<<max(i-x,0ll)<<' ';
  }
  return 0;
}
```

---

## 作者：Mingrui_Yang (赞：5)

[luogu 传送门](https://www.luogu.com.cn/problem/AT_abc270_e)

## 题意

有 $N$ 个篮子围成一圈，第 $i$ 个篮子里有 $A_i$ 个苹果。    
现在你需要从 $1$ 个篮子开始，依次拿掉一个苹果，直到一共拿到 $K$ 个苹果。如果篮子里没有苹果（即苹果被拿完了）就直接跳到下一个篮子。   
求最终 $N$ 个篮子中每个篮子的苹果数量。

## 思路

这道题其实可以模拟。  
由数据范围（$1 \le N \le 10^5$，$1 \le K \le 10^{12}$），我们看出可以从 $N$ 入手而不是 $K$。

首先，我们应该知道，如果有 $m$ 个篮子有苹果，那么拿掉一圈的苹果数量就一定是 $m$ 个。  

将每个篮子里的苹果数量抽象成一个柱状图   
![](https://cdn.luogu.com.cn/upload/image_hosting/fdhvcyzx.png)   
（如图）第一次找到苹果数量最少的的篮子（即 $a_5$），假设拿了 $a_5$ 圈，则拿掉的苹果数量就是 $a_5 \times n$ 个（即黄线以下）。如果 $a_5 \times n \le K$，则说明拿掉的圈数一定小于等于 $a_5$；否则说明圈数一定大于 $a_5$，并需要进行第二次查找。

第二次找到苹果数量第二少的篮子（即 $a_2$），假设拿了 $\left( a_2 - a_5 \right)$ 圈，注意当前篮子数量是 $n - 1$，则 $\left( a_2 - a_5 \right) \times \left(n - 1 \right)$ 即为本次拿掉的苹果数量（即蓝线与黄线之间）。如果 $\left( a_2 - a_5 \right) \times \left(n - 1 \right) \le K - a_5 \times n$，则说明拿掉的圈数一定小于等于 $a_2$；否则说明圈数一定大于 $a_2$，并需要进行第三次查找。

以此类推。。。

## 实现

首先，我们用 `a[]` 存下每个篮子的苹果数量，再定义 `b[]` 将 `a[]` 拷贝一份。  
将 `a[]` 从小到大排序，便能通过遍历得到第一小、第二小……   
再定义一个 `last` 存下上一个的值。   

在每次比较时，当前的个数都是 `last` 到 `a[i]` 之间的个数，所以每次比较后都将 $K$ 减去当前的个数：
```cpp
k -= (a[i] - last) * (n - i + 1);
last = a[i];
```

如果当前枚举到的个数大于 $K$，便可以停止枚举输出答案（因为题目保证 $\sum_{i = 1}^{N} A_i \ge K$，所以程序一定在这里结束
），注意输出时应该使用之前拷贝下来的原数组 `b[]`：
```cpp
t = k / (n - i + 1), d = k % (n - i + 1);
for (int i = 1, j = 1; i <= n; i ++ ) {
	if (b[i] - last <= 0) cout << 0 << " "; // 已经被吃光
	else if (b[i] - last - t - (j <= d) < 0) cout << b[i] - last - t << " "; // 不能再多拿
	else cout << b[i] - last - t - (j <= d) << " ", j ++ ; // 多的
}
return 0;
```

## CODE

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 1e5 + 10; 
int n, k, a[N], b[N];
signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i ++ ) cin >> b[i], a[i] = b[i];
	sort(a + 1, a + n + 1);
	int last = 0, t, d, k1 = k;
	for (int i = 1; i <= n; i ++ ) {
		if (a[i] && (a[i] - last) * (n - i + 1) >= k) {
			t = k / (n - i + 1), d = k % (n - i + 1);
			for (int i = 1, j = 1; i <= n; i ++ ) {
				if (b[i] - last <= 0) cout << 0 << " ";
				else if (b[i] - last - t - (j <= d) < 0) cout << b[i] - last - t << " ";
				else cout << b[i] - last - t - (j <= d) << " ", j ++ ;
			}
			return 0;
		}
		else {
			k -= (a[i] - last) * (n - i + 1);
			last = a[i];
		}
	}
	return 0;     
}
```

~~bye~~~~

---

## 作者：Tsawke (赞：3)

#  [[ABC270E] Apple Baskets on Circle](https://www.luogu.com.cn/problem/AT_abc270_e) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.tsawke.com?t=ABC270E)

## 题面

存在 $ n $ 个筐围成一圈，第 $ i $ 个有 $ A_i $ 个苹果。你需要从第 $ 1 $ 个筐开始依次拿掉一个苹果，直到拿了 $ k $ 个。如果筐内没有苹果那么直接拿下一个筐。求最终每个筐里还剩多少个苹果。

## Solution

题解区怎么都是二分答案的做法，来一发 VP 时糊出来的更加无脑的模拟做法。

首先假设一圈里有 $ k $ 个篮子里有苹果，那么转一圈一定会拿走 $ k $ 个苹果，然后当拿空了一个篮子之后就会 $ k \leftarrow k - 1 $。所以我们考虑维护一下当前一共还有多少个篮子里有苹果，然后给所有 $ A_i $ 排个序，每次取最小的然后判断是否能拿空，如果可以的话那么直接拿空，否则尽量拿多圈，此时剩下的所有显然不足一圈，此时再次遍历一遍即可。

然后注意其中有一步 $ cur \times v $，这个东西我感觉似乎是 $ 10^{24} $ 级别的，于是开了个 `__int128_t`。

审核没通过，说太简略了，那么就把具体过程再说一下吧：

维护一个 $ minus $ 表示当前一共拿过了多少圈，每次取一个苹果数最小的篮子并去掉已经拿走的 $ minus $ 个，然后考虑现在剩下的有苹果的篮子数，即 $ cur $ 乘上最小的剩的苹果数，如果可以全部取走那么就都取走，然后 $ minus \leftarrow minus + v $。反之尽量拿更多圈，记录剩余多少个苹果没拿，显然其会小于剩余的存在苹果的篮子数，此时暴力枚举跑一下即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW void* Edge::operator new(size_t){static Edge* P = ed; return P++;}

using namespace std;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template < typename T = int >
inline T read(void);

int N; ll K;
ll A[210000];
priority_queue < ll, vector < ll >, greater < ll > > buc;

int main(){
    N = read(), K = read < ll >();
    ll cur(0);
    for(int i = 1; i <= N; ++i)if((A[i] = read < ll >()))buc.push(A[i]), ++cur;
    ll minus(0);
    while(!buc.empty()){
        ll v = buc.top() - minus; buc.pop();
        if((__int128_t)cur * v <= K)K -= cur * v, minus += v, --cur;
        else{minus += K / cur, K -= K / cur * cur; break;}
    }
    for(int i = 1; i <= N; ++i)A[i] = max(0ll, A[i] - minus);
    for(int i = 1; i <= N && K; ++i)if(A[i])--A[i], --K;
    for(int i = 1; i <= N; ++i)printf("%lld%c", A[i], i == N ? '\n' : ' ');
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template < typename T >
inline T read(void){
    T ret(0);
    int flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2023_01_27 初稿

update-2023_02_01 审核没过，将叙述改的更详尽一些

---

## 作者：郑朝曦zzx (赞：2)

## 一 解题思路
这次的 E 题比较水，通过数据范围可知直接模拟肯定是不行的。考虑二分，二分一个数 $x$， 表示从每个篮子里拿出 $x$ 个苹果（不够则有多少拿多少），拿出的苹果总数是否小于 $k$，通过二分我们可以得到最大的 $x$，然后我们再扫一遍所有篮子，凑齐 $k$ 个苹果即可。

时间复杂度：$O(n \log k)$

## 二 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
inline LL read()
{
	bool flag = true;
	char c = getchar();
	if (c == '-') flag = false;
	while(!(c >= '0' && c <= '9')) c = getchar();
	LL x = 0ll;
	while(c >= '0' && c <= '9')
	{
		x = (x << 3) + (x << 1) + c - '0';
		c = getchar();
	}
	if (flag == true) return x;
	return -x;
}
LL a[100100];
int n;
LL k, l, r, tmp;
bool check(LL x)
{
	LL tot = 0ll;
	for (int i = 1; i <= n; ++i)
		tot += min(a[i], x);
	return tot <= k;
}
int main()
{
	n = read();
	k = read();
	for (int i = 1; i <= n; ++i)
		a[i] = read();
	l = 1ll; r = k;
	while (l <= r)
	{
		LL mid = (l + r) / 2ll;
		if (check(mid))
		{
			l = mid + 1;
			tmp = mid;
		}
		else r = mid - 1;
	}
	for (int i = 1; i <= n; ++i)
	{
		k -= min(tmp, a[i]);
		a[i] = max(0ll, a[i] - tmp);
	}
	tmp = 0ll;
	for (int i = 1; i <= n; ++i)
	{
		if (tmp == k) break;
		if (a[i]) {++tmp; --a[i];}
	}
	for (int i = 1; i <= n; ++i)
		printf("%lld ", a[i]);
    return 0;
}
```


---

## 作者：Demons_Killer (赞：2)

# 题意：
有 $N$ 个篮子排成一个环，其中 $A_{i}$ 表示第 $i$ 个篮子中有多少苹果。
从左往右依次取，篮子中没有苹果则跳过这个篮子，直到取满 $K$ 个苹果为止。
然后输出每个篮子中苹果的数量。
# 解题思路：
本体算法为模拟。

由题可知，我们每一轮取苹果的个数是不固定的，可以存储一下每一轮中有多少个篮子可以取苹果，再用 $K$ 减去这个数。

问题来了，如果一轮一轮的模拟下去，是大概率会 TLE 的，思考一下，
只有我们去取完了一个篮子，我们下一轮要取的苹果数量才会发生改变，
我们可以一直取取到有篮子为空为止，那么这其中取的次数，应该是不为空的篮子中苹果数最小的篮子中的苹果数。
# code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
int a[N],n,k,cnt;
priority_queue<int,vector<int>,greater<int> > q; //以为每次取最小值，所以可构建一个小根堆 
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=0){
			cnt++;//篮子不为空，要取的苹果数加1 
			q.push(a[i]);
		}
	}
	while(1){
		int t=q.top();//堆顶，即最小篮子 
		q.pop();
		if(t*cnt>k){//不够减完一轮 
			int c=k/cnt,s=k%cnt;
			for(int i=1;i<=n;i++){
				if(a[i]){
					a[i]-=c;
				}
			}
			for(int i=1,j=1;i<=n&&j<=s;i++){
				if(a[i]){
					a[i]--;
					j++;
				}
			}
			break;
		}
		else{
			k-=t*cnt;
			for(int i=1;i<=n;i++){
				if(a[i]){
					a[i]-=t;
					if(!a[i]){
						cnt--;//篮子为空，可取篮子数减1 
					}
				}
			}
		}
		if(!k) break;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：gxp123 (赞：0)

# abc270 E - Apple Baskets on Circle

## 题意

有 $N$ 个编号为 $1,2,\dots, N$ 的篮子排成一个环。

对于每一个 篮子 $i\ (1 \le i \le N-1 $ ) ， 有篮子 $i+1$ 在它的右边。（篮子 $1$ 在 篮子 $N$ 的右边）。

现在第 $i$ 个篮子里有 $A_i$ 个苹果。

高桥君从第 $1$ 个篮子开始，如果他面对的篮子里有至少一个苹果，就拿一个吃掉。然后，不管他有没有吃到苹果，都要去紧靠在右边的下一个篮子，直到他吃到 $K$ 个苹果。

当高桥君吃到 $K$ 个苹果后，求每个篮子里还有多少个苹果。

- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^{12} $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- $ \sum_{i=1}^{N}A_i\geq\ K $

## 题解

我们先按圈考虑。

我们先对所有的数进行排序，我们记录一个 $tag$ 表示圈上有多少个苹果被拿走了。

每次如果最少的哪一堆我们可以全部拿走，我们就全部拿走。

即拿走 $(b_l - tag)\times(n - l + 1) $，$l$ 表示我们当前考虑到第 $l$ 小的，$b$ 表示排完序后的 $a$。

（言外之意就是前 $l-1$ 小的篮子都被取完了）

就是这一轮取 $\min(\lfloor \frac{k}{n - l + 1}\rfloor,b_l - tag)\times(n-l+1)$。

$\lfloor x\rfloor$ 表示 $x$ 向下取整。

取完之后，我们更新一下 $k$。

这样子我们不断的尝试一直取，直到我们无法在把所有有苹果的篮子中的苹果都拿出来一个，即 $k < n - l + 1$ 时，我们就开始单独考虑每个篮子。

对于每个 $i$，$p_i=\min(a_i-tag,0)$，若此时 $p_i > 0$ 且 $k > 0$，我们就从这个篮子中取走一个，然后 $k$ 和篮子里的苹果数量都要减少一，即 `-- p[i],--k`。

时间复杂度：$O(n)$。

## code

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<ll,int> pli;
const int maxN = 1e5 + 10;
ll a[maxN],k;
pli aa[maxN];

int main(){
    int n;
    scanf("%d%lld",&n,&k);
    for(int i = 1 ; i <= n ; ++i){
        scanf("%lld",&a[i]);
        aa[i] = {a[i],i};
    }
    sort(aa + 1,aa + 1 + n);
    int l = 0;
    while(l <= n && aa[l].first == 0) ++l;
    ll op,tag = 0;
    while(l <= n && k > n - l + 1){
        op = min(k / (n - l + 1),aa[l].first - tag);
        tag += op;
        k -= 1ll * op * (n - l + 1);
        while(l <= n && aa[l].first == tag)   ++l;
    }
    for(int i = 1 ; i <= n ; ++i){
        a[i] = max(a[i] - tag,0ll);
        if(a[i] > 0 && k > 0){
            --a[i],--k;
        }
        printf("%lld ",a[i]);
    }
	return 0;
}
```

---

## 作者：0xFF (赞：0)

发现操作数和每个盘子中的苹果数很大，但是盘子数很少且容易判断 $m$ 轮后能不能将 $k$ 个苹果取完。

考虑二分答案，可以知道二分出的结果一定满足剩余的 $k$ 不大于 $n$，只需再扫一遍输出答案即可。

需要注意的是，如果二分答案记录的是刚好能取满 $k$ 个的轮数 $l$，那么应当将每个盘子中的苹果数减去 $\min \left \{ a_i,l-1 \right \} $ 因为刚好取满的上一轮才是使得剩余 $k$ 不大于 $n$ 的轮数。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<map>
#include<climits>
#include<queue>
#include<deque>
#include<vector>
#define int long long
using namespace std;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
const int N = 1e5 + 10;
inline int read(){
	int x=0,f=1;char ch=getchar();
	for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
	for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
	return x*f;
}
int a[N],n,k;
bool F(int x){
	int res = 0;
	for(int i=1;i<=n;i++) res += min(x,a[i]);
	return (res >= k);
}
signed main(){
	n = read() , k = read();
	for(int i=1;i<=n;i++){
		a[i] = read();	
	}
	int l = 0 , r = 1e12 + 10 , mid;
	while(l <= r){
		mid = l + r >> 1;
		if(F(mid) == true) r = mid - 1;
		else l = mid + 1;
	}
	for(int i=1;i<=n;i++){
		int d = min(l - 1,a[i]);
		a[i] -= d;
		k -= d;
	}
	for(int i=1;i<=n&&k>0;i++){
		if(a[i] > 0) a[i]--,k--;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
/*
2 1000000000000
1000000000000 1000000000000

500000000000 500000000000 
*/
```


---

## 作者：xiaomuyun (赞：0)

- [Luogu 传送门](https://www.luogu.com.cn/problem/AT_abc270_e)
- [Atcoder 传送门](https://atcoder.jp/contests/abc270/tasks/abc270_e)

## 思路分析

我们应该有一种思路：如果 $n\le10^5$，而且没有什么比较明显的特征说明可以用某种算法或数据结构解决的话，那时间复杂度就应该是 $\mathcal{O}(n\log n)$ 了。因此对于这道题，我们来思考一下 $\mathcal{O}(n\log k)$ 的做法。

一般复杂度带 $\log$ 的算法有排序，二分等。我们看到这道题，因为排序会影响篮子的顺序，很麻烦，所以我们考虑二分。

可是二分什么呢？总不能二分每个篮子最后剩下的苹果数量吧？仔细想一想可以发现，我们可以二分确定出 **吃 $k$ 个苹果需要转的圈数**。有两个原因：一个是 `check` 函数的时间复杂度为 $\mathcal{O}(n)$，另一个是求出转的圈数之后每个篮子最后剩下的苹果数量都很好求。

## 代码实现

我们来考虑一下如何实现刚刚所讲的二分。每当我们二分出一个可能的圈数 $x$，就遍历一遍每个篮子，维护一个 $s$，每次让 $s$ 增加 $\min(a_i,x)$，$\min(a_i,x)$ 表示转了 $x$ 圈后可以在第 $i$ 个篮子里获得多少苹果。最后，如果 $s\le k$ 的话，就说明答案是可行的，我们只需要求出最大的满足 $s\le k$ 且转完之后恰好拿完的 $x$ 即可。

得到圈数之后，我们先按照圈数把答案统计出来，然后还要统计一下剩下 $k\bmod n$ 个苹果，最后输出答案即可。

```cpp
#include<algorithm>
#include<cstdio>
#define int long long
using namespace std;
const int maxn=1e5+1;
int n,k,a[maxn];
inline bool check(int x){
	int sum=0;//统计可以拿到多少苹果
	for(int i=1;i<=n;++i) sum+=min(a[i],x);
	return sum<=k;
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	int l=0,r=1e12;
	while(r-l>1){//二分部分
		int mid=l+r>>1;
		if(check(mid)) l=mid;
		else r=mid;
	}
	for(int i=1;i<=n;++i){//把转的l圈的答案统计出来
		int t=min(l,a[i]);
		a[i]-=t,k-=t;
	}
	for(int i=1;k;++i){//还要拿k mod n个苹果，再遍历一次，直到彻底拿完
		if(a[i]) --a[i],--k;
	}
	for(int i=1;i<=n;++i) printf("%lld ",a[i]);
	putchar('\n');
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# 思路
观察数据范围，显然从 $n$ 下手，又因为取法固定，故考虑模拟。

正常模拟肯定会超时，但是我们发现，若有一些篮子的苹果会被取完，则这些篮子苹果被取完的顺序固定，而只有当某个篮子的苹果被取完的时候，才会出现循环周期的改变。所以先拿一个数组将排序后的数组存下来，枚举这个数组，每次枚举都算出来在当前规则下会取多少个苹果，若在中途取的所有苹果的总数等于 $k$ 了，则先算出最多进行多少轮操作，再把剩下的不足一轮的操作数逐个解决；若总数不足 $k$ 则将取的数量放入累加数组（累加数组也起到了延迟更新的作用），继续操作。


```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
const int N=1e5+10;
using namespace std;
int n,k,a[N],Min[N],sum;
signed main()
{
// 	freopen("eat.in","r",stdin);
// 	freopen("eat.out","w",stdout);
	cin>>n>>k;
	rep1(i,1,n) cin>>a[i],Min[i]=a[i];
	sort(Min+1,Min+n+1);//排序
	rep1(i,1,n)
	{
		int x=(Min[i]-sum)*(n-i+1);//当前规则下取的总数
		if(k-x>0)//不足
		{
			k-=x;
			sum=Min[i];//取了多少轮
		}
		else
		{
			sum+=k/(n-i+1);//最多走多少轮
			int cnt=k%(n-i+1);//还剩多少没操作
			rep1(j,1,n) if(a[j]-sum>0&&cnt>0) --a[j],--cnt;//单个解决
			break;
		}
	}
	rep1(i,1,n) 
	{
		if(a[i]-sum>0) cout<<a[i]-sum<<' ';//延迟更新并输出
		else cout<<0<<' ';
	}
	putchar('\n');
	return 0;
}
/*
5 13
2 4 1 3 5

0 0 0 0 2
*/ 
```

---

