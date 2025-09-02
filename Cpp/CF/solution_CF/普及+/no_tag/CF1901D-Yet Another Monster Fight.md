# Yet Another Monster Fight

## 题目描述

小V遇到了 $ n $ 个怪物排成一排，每一个怪物的血量为 $ a_i $ 。小V决定用魔法消灭它们。

在施展魔法时，小V会先选择一个怪物所在的位置 $ i $ ，作为这个魔法**直接**攻击的怪物。然后，他会选择魔法的威力 $ x $ 。

然而，这种魔法十分特殊，会以一定顺序攻击这 $ n $ 个怪物，第 $ i $ 个受攻击怪物会受到 $ x-i+1 $ 点的伤害。具体来说，这个魔法每次会随机选择一个与被攻击过的怪物相邻且没有被攻击的怪物作为对象施展一次攻击。

小V对自己的实力很自信，所以他想知道在他能随意选择第一个攻击位置 $ i $ 的情况下，最小要用多少的威力 $ x $ 使得无论魔法沿什么顺序攻击都能杀死所有的怪物。但小V不会这个问题，就把它交给了你。

注：两个怪物视作相邻当且仅当它们之间没有任何其它活着的怪物

## 说明/提示

保证 
 $ 1 \le n \le 3 \cdot 10^5 $ ，且 $ 1 \le a_i \le 10^9 $

## 样例 #1

### 输入

```
6
2 1 5 6 4 3```

### 输出

```
8```

## 样例 #2

### 输入

```
5
4 4 4 4 4```

### 输出

```
8```

## 样例 #3

### 输入

```
2
1 1000000000```

### 输出

```
1000000000```

# 题解

## 作者：2huk (赞：9)

## Description

有 $n$ 个怪物排成一排，每一个怪物有初始血量 $a_i$。当一个怪物的血量 $\le 0$ 时，这个怪物就没了。

每次魔法需要选择一个起始位置 $i$，并给予 $i$ 怪兽 $x$ 的伤害。其中 $i, x$ 都是可以任意选的。

然后每次需要选择一个**没有被施魔法**的且**与一个已经施魔法的怪兽相邻**的怪兽施魔法。若这个怪兽是第 $j$ 次施的魔法，则它受的伤害为 $x - j + 1$。

请你选择一个初始血量 $x$ 和起始位置 $i$，使得对于任意满足上述条件的施魔法的顺序都能将所有怪兽打败。请你求出最小的 $x$。

## Solution

我们枚举第一个受攻击的怪兽 $i$，然后计算最坏情况下需要的初始血量 $x$。每一个 $x$ 中的最小值即为答案。

考虑对于一个怪兽 $j$ 而言，在能打败它的最坏情况下初始血量是多少：

- $i = j$：这是第一个怪兽，需要用 $a_i$ 才能打败；
- $i > j$：这个怪兽在最开始的怪兽的左边，那么最坏情况就是在怪兽 $j$ 右边的所有怪兽都被打败时来打它。因此需要用 $a_j + n - j$ 才能打败；
- $i < j$：跟上面类似。这个怪兽在最开始的怪兽的右边，那么最坏情况就是在怪兽 $j$ 左边的所有怪兽都被打败时来打它。因此需要用 $a_j + j - 1$ 才能打败；

综上，如果第一个攻击的怪兽是 $i$，最坏情况下最少的初始血量为：
$$
\max(a_i, \max_{j = 1}^{i - 1} (a_j + n - j), \max_{j = i + 1}^n(a_j + j - 1))
$$
定义 $x_i = \max_{j = 1}^{i} (a_j + n - j)$，$y_i = \max_{j = i}^n(a_j + j - 1)$，那么答案为：
$$
\min_{i=1}^n \max(a_i, x_{i - 1}, y_{i + 1})
$$
很显然 $x_i, y_i$ 可以 $\mathcal O(n)$ 预处理，所以答案可以在 $\mathcal O(n)$ 的时间复杂度内计算。

## Code

```cpp
int n, a[N]; 
int x[N], y[N], res = INF;

signed main()
{
	n = read();
	
	fup (i, 1, n) a[i] = read();
	fup (i, 1, n) x[i] = Max(x[i - 1], a[i] + n - i);
	fdw (i, n, 1) y[i] = Max(y[i + 1], a[i] + i - 1);
	
	fup (i, 1, n)
	{
		// 第一个目标为 i
		res = Min(res, Max(a[i], Max(x[i - 1], y[i + 1]))); 
	}
	
	wel(res);
	
	return 0;
}
```

---

## 作者：Crazyouth (赞：7)

**分析**

此题求的是满足条件的最小值，不难想到二分答案，关键在于 `check()` 怎么写。

若当前施法强度为 $x$，则 $d_i=x-a_i+1$ 代表的是 $i$ 最晚可能被击中的时间，则有若 $d_i<i$，则施法位置 $k$ 不能小于 $i$；同理若 $d_i<n-i+1$，施法位置 $k$ 不能大于 $i$。若 $k$ 不存在满足上述条件的取值，`check()` 返回 $0$，否则返回 $1$。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[300010],n;
int check(int x)
{
	int l=0,r=n;
	for(int i=1;i<=n;i++)
	{
		if(x-a[i]+1<i) l=i;
		if(x-a[i]+1<n-i+1) r=min(r,i);
	}
	if(l<=r) return 1;
	return 0;
}
signed main()
{
	int maxx=-1;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],maxx=max(maxx,a[i]);
	int l=maxx,r=1e18,mid;
	while(l<r)
	{
		mid=l+(r-l>>1);
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}

---

## 作者：zhangqiuyanAFOon2024 (赞：2)

### 思路
写一篇蒟蒻都能看懂的题解。

不难看出，此题要用二分答案。

我们先设当前判断的是 $mid$，然后去限制攻击点的范围。

设当前限制的是 $a_i$，由于题目中魔法是任意的，所以考虑最坏情况。

如果魔法点在 $i$ 的左边，那么最坏就是把左边全部打完，再去打 $a_i$。

此时，因为 $a_i$ 是第 $i$ 个被打的，所以就只有 $mid-i+1$ 的攻击力来打 $a_i$。

那么，如果 $mid-i+1<a_i$，那么就显然不行，即魔法点要在 $i$ 右边。

同理，如果 $mid-(n-i+1)+1<a_i$ 那么魔法点要在 $i$ 左边。

那维护个 $l$ 和 $r$ 就行了。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+10;
int a[N],n;
bool check(int mid){
	int l,r;
	l=r=0;
	for(int i=1;i<=n;i++){
		if(mid-i+1<a[i]) l=i;//在 i 的右边（取最后）
		if(mid-(n-i+1)+1<a[i]&&!r) r=i;//在i的左边（取最前）
	}
	if(!r||!l) return 1;//没有 r 限制或没有 l 限制，显然可行
	return (l<=r);
}
signed main(){
	int maxn=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		maxn=max(maxn,a[i]);//最大
	}
	int l=maxn,r=1e18,ans;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}//二分
	cout<<ans;
}
```

---

## 作者：_JF_ (赞：2)

GDKOI PJ DAY1 T2 原。

终于有时间来补题了。

还是考虑二分答案，因为他要求最大值最小。

然后考虑怎么检验，考虑求出 $s_i=x-a_i+1$ 表示打死当前这个怪物的最慢的时刻。如果 $s_i<i$ 则说明小于 $i$ 的位置都不可取，（因为题目要求用任意的攻击顺序，如果取了 $i$ 以前的话可以把 $i$ 以前的全部打完再来打 $i$，但这不合法。）同理，如果 $s_i>n-i+1$，则说明大于 $i$ 的位置都不可取。

所以对每个怪物遍历求最后可以施展攻击的交集即可。

时间为 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long 
int a[N],n;
bool check(int x){
	int l=1,r=n;
	for(int i=1;i<=n;i++){
		if(x<a[i])	return false;
		int lst=x-a[i]+1;
		if(lst<i)	l=max(l,i);
		if(lst<n-i+1)	r=min(r,i);	
	}
	if(l<=r)	return true;
	return false;
}
void Find(){
	int l=1,r=2e9,ans=0;
	while(l<r){
		int mid=(l+r)>>1;
		if(check(mid))	ans=mid,r=mid;
		else	l=mid+1;
	}
	cout<<ans<<endl;
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i];
	Find();
	return 0;
}

```


---

## 作者：AlicX (赞：2)

这里是二分解法。

假设魔法值 $x$ 满足条件，则 $y(y>x)$ 一定满足条件，所以答案具有单调性，考虑二分。

考虑对于 $mid$ 的 `check`：对于第 $i$ 个位置，令 $c=mid-a_i$，如果 $c < 0$，说明 $mid$ 不满足条件；反之说明起始位置在 $i$ 满足条件。如果 $c \geq i-1$，说明起始位置在 $1 \sim i-1$ 都可行，因为最坏情况下也只需要 $i-1$ 次移动就能到 $i$。如果 $c \geq n-i$，说明起始位置在 $i+1 \sim n$ 都可行，原因同上。最后只需要判断是否有一个点可以成为 $n$ 个点的起始位置即可。

注意二分边界要开到 $10^9+3\times 10^5$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define x first 
#define y second 
#define debug() puts("-------") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=3e5+10; 
int n,x; 
int a[N],b[N]; 
bool check(int mid){ 
	for(int i=1;i<=n;i++) b[i]=0;
	for(int i=1;i<=n;i++){ 
		if(mid<a[i]) return false; 
		int x=mid-a[i]; b[i]++,b[i+1]--; 
		if(i-1<=x) b[1]++,b[i]--; 
		if(n-i<=x) b[i+1]++,b[n+1]--; 
//		b[max(0ll,l)]++,b[min(r+1,n+1)]--; 
	} 
//	return true; 
	for(int i=1;i<=n;i++){ 
		b[i]+=b[i-1]; 
		if(b[i]>=n) return true; 
	} return false; 
} 
void work(){ 
	cin>>n; 
	for(int i=1;i<=n;i++) cin>>a[i]; 
	int l=1,r=1e10+7,ans=0; 
	while(l<=r){ 
		int mid=l+r>>1; 
		if(check(mid)) r=mid-1,ans=mid; 
		else l=mid+1; 
	} printf("%lld\n",ans); 
} 
signed main(){ 
	int T=1;
	while(T--) work(); return 0; 
} 
```


---

## 作者：wuyin331 (赞：2)

# 题解
首先我们可以选择任意一个怪物进行攻击，攻击是一个链式递减的。一开始想到的是选择最高生命的进行攻击，发现并不是最优做法。比如该数据。
```c
5
5 1 6 1 1
```
如果选第三个怪物为第一个攻击目标，那么需要 $9$ 点伤害，而选择第一个怪物则为 $8$ 点伤害。继续研究发现对于第 $i$ 个怪物的最差情况的第一个目标伤害和第一个选择目标与第 $i$ 个怪物的位置有关。则有如下结论。

如果第一个目标在右边，对于第 $i$ 个怪物的最差情况的第一个目标伤害应该为 $nums[i]+n-i$。

如果第一个目标在左边，对于第 $i$ 个怪物的最差情况的第一个目标伤害应该为 $nums[i]+i-1$。

如果能够快速求出第一个目标左边的怪物的最差情况与右边怪物的最差情况，那么我们就只需要枚举哪一个为第一个怪物即可，当然这就是我们的前缀和大法。

```cpp
#include<iostream>
#include<cstdio>
#include<climits>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
#include<set>
#include<string>
#include<cstring>
#include<unordered_map>
#include<unordered_set> 
#include<cmath>
#include<numeric>
#define int long long
using namespace std;
int t, n, m, k, nums[300005],pre[300005],lst[300005];
map<string, int>ans;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	pre[0]=0;lst[n+1]=0;
	for(int i=1;i<=n;i++) cin>>nums[i];
	for(int i=1;i<=n;i++) pre[i]=max(pre[i-1],nums[i]+n-i);
	for(int i=n;i>=1;i--) lst[i]=max(lst[i+1],nums[i]+i-1);
	int ans=0x3f3f3f3f;
	for(int i=1;i<=n;i++){
		ans=min(ans,max(max(pre[i-1],lst[i+1]),nums[i]));
	}
	cout<<ans<<'\n';
	return 0;
}
```


---

## 作者：Jerrycyx (赞：1)

因为每次攻击的怪物都与已被攻击过的怪物相邻，所以被攻击的怪物一定组成一个连通区间，且每次攻击都是在将这个区间向左或向右扩大一个位置。

假设我们选择的位置是 $p$，初始攻击为 $x$，考虑最坏情况：

+ 如果要攻击 $p$ 左边某怪物 $i$，最坏情况是魔法最开始每次都往右边打（$(n-p)$ 次攻击），右边打完了以后再从 $p$ 向左边打到 $i$（$(p-i)$ 次攻击），算上最初的一次，打到 $i$ 最多需要 $(n-p)+(p-i)+1=n-i+1$ 次攻击，此时还剩下的攻击力为 $x-(n-i+1)+1=x-n+i$。要击杀这个怪物，攻击力必须大于其血量，所以 $x-n+i \ge a_i$，转化一下得到 $x \ge a_i+n-i$。

+ 同理，如果要攻击 $p$ 右边某怪物 $i$，最坏情况是魔法先往左边打 $(p-1)$ 次，再向右边打 $i-p$ 次打到 $i$，算上最初一次，一共 $i$ 次攻击。此时还剩下的攻击力为 $x-i+1$，又因为 $x-i+1 \ge a_i$，所以 $x \ge a_i+i-1$。

综上所述，所选择的 $x$ 和 $p$ 需要满足以下条件：

$$
\begin{aligned}
x \ge a_i+n-i,&\quad i<p \\
x \ge a_i+i-1,&\quad i>p \\
x \ge a_i,&\quad i=p
\end{aligned}
$$

而上述条件可以转化一下：

$$
\begin{aligned}
x& \ge \max_{i=1}^{p-1}\{a_i+n-i\} \\
x& \ge \max_{i=p+1}^{n}\{a_i+i-1\} \\
x& \ge a_p
\end{aligned}
$$

上面的最大值可以预处理，即可以设 $lmax_i = \max_{j=1}^{i}\{a_j+n-j\}$，$rmax_i = \max_{j=i}^{n}\{a_j+j-1\}$。

解法也就出来了，枚举每一个可能的 $p$，此时的 $x$ 就为 $\max\{lmax_{p-1}, rmax_{p+1}, a_p\}$，对所有的 $x$ 取最小值即为答案。

核心代码：

```cpp
for(int i=1;i<=n;i++)
	lmax[i]=max(lmax[i-1],a[i]+n-i);
for(int i=n;i>=1;i--)
	rmax[i]=max(rmax[i+1],a[i]+i-1);
int ans=0x7fffffff;
for(int i=1;i<=n;i++)
	ans=min(ans,max({a[i],lmax[i-1],rmax[i+1]}));
```

[AC 记录 + 完整代码](https://codeforces.com/contest/1901/submission/290992749)

---

## 作者：_qingshu_ (赞：1)

# 题意：

这个题翻译好像有点问题？第四段这个他是指我们自己...

有一个长度为 $n$ 的数列，我们可以选择一个起点 $i$，开始的能量 $x$，在能量传递的过程每一次传递能量会递减，在最劣传播路径（规定仅能传递两个之间没有还未被传递的数的数）下，$x$ 永远不小于当前所在的数的最小值是多少。

# 思路：

既然是传递，那么就会有状态的继承，有状态的继承就可以考虑 DP。

我们定义 $lefs_{i}$ 为传递完 $i$ 及其左边的数字所需要的最小 $x$。

$rigs_{i}$ 同理为传递完 $i$ 及其右边的数字所需要的最小 $x$。

因为传递每一次递减一，那么对于 $x$ 来说就是每一次递增一，且该点传递到的值一定不会小于该点，我们就可以得出转移方程。

$$
lefs_i=\max(lefs_{i-1}+1,a_{i})
$$

$$
rigs_i=\max(rigs_{i+1}+1,a_{i})
$$

考虑答案的统计。

当任意一边的数字被传递完之后，传递路线便唯一化了，只需要再增加剩下的数的个数就可以了。

注意，每到一个点答案处理使用的是 $lefs_{i-1}$ 与 $rigs_{i+1}$。

# code：

```
#include<bits/stdc++.h>
using namespace std;
int n;
int a[300010];
int lefs[300010];
int rigs[300010];
int ans=INT_MAX;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		lefs[i]=max(lefs[i-1]+1,a[i]);
	}
	for(int i=n;i>=1;i--){
		rigs[i]=max(rigs[i+1]+1,a[i]);
		ans=min(ans,max(a[i],max(lefs[i-1]+n-i+1,rigs[i+1]+i)));
	}
	cout<<ans<<endl;
}
```

update：

23.12.20：

- 修改了数学公式语言表达

- 修改了英文与中文之间的空格缺失

23.12.21：

- 修改了行间公式

---

## 作者：Struct_Sec (赞：1)

容易发现答案具有单调性，考虑二分答案。

直接暴力 check 是 $O(N^2)$ 的，考虑转换限制条件。

设当前答案为 $x$，对于每个点 $i$，设 $s=x-a_{i}+1$。若 $s<i$ 合法点不能在 $i$ 后面，否则先把 $i$ 前面的攻击后再攻击 $i$ 就不合法了。同理，若 $s\ge i$ 则满足条件的点只能在 $i$ 的后面。

于是我们从前往后扫一遍，用 $l$，$r$ 分别记录合法点所在区间，最后判断 $l$ 是否大于 $r$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+5;
int n,a[N],mx;
bool check(int x){
	int l=0,r=1e18;
	for(int i=1;i<=n;i++){
		int s=x-a[i]+1;
		if(s<i) l=i;
		if(s<n-i+1) r=min(r,i);
	}
	return l<=r;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],mx=max(mx,a[i]);
	int l=mx,r=1e10,ans;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：Keroshi (赞：1)

首先假设现在初始目标是第 $i$ 个怪物，要计算当前需要的能量最小值，就需要考虑最坏的情况。  

在此基础上再假设一个编号为 $j$ 的怪物，且这个怪物在初始目标右边，即 $i<j$，  

那么我们现在考虑第 $j$ 个怪物对于最小能量的最大贡献，

能量会随攻击怪物的数量而递减，所以攻击第 $j$ 个怪物的时候能量衰减越多，需要的初始能量就越多，产生的贡献就越大。  

而要让能量衰减多，就需要在之前攻击尽可能多的怪物，  

所以可以先攻击所有在第 $j$ 个怪物左边的怪物，再往右攻击。

这样就得到了一个 $\Theta(n^2)$ 朴素做法。

考虑优化，对于一个初始怪物，需要分别计算左右两端的最大贡献，而且贡献是可以进行转移的。

所以考虑两次 dp，假设 $f_{i}$ 表示从第 $i$ 个怪物开始从右往左攻击所需的最小能量值，

那么由于能量衰减，要击败前面的怪物需要的能量是 $f_{i-1} + 1$，还要求能量比当前的怪物大，

所以转移方程为 $f_{i}=\max(f_{i-1}+1, a_i)$。

还有一个反方向的 dp 同理，假设数组为 $g$，

最后用 dp 数组加上另外一边所需的能量，取最大值，

答案为 $\min_{i=1}^{n}\max(a_i,f_{i-1}+n-i+1,g_{i+1}+i)$。

### 代码
```cpp
#define FOR(i, m, n) for(int i=(m);i<=(n);i++)
#define ROF(i, m, n) for(int i=(m);i>=(n);i--)
template <typename T, typename U>
inline bool chmax(T& a, U b) { return a < b ? (a = b, true) : false; }
template <typename T, typename U>
inline bool chmin(T& a, U b) { return a > b ? (a = b, true) : false; }
const int N = 3e5 + 5;
const int INF = 2e9 + 7;
int n, a[N], f[N][2];
void solve() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    int ans = INF;
    FOR(i, 1, n) f[i][0] = max(a[i], f[i - 1][0] + 1);
    ROF(i, n, 1) f[i][1] = max(a[i], f[i + 1][1] + 1);
    FOR(i, 1, n) {
        int res = a[i];
        chmax(res, f[i - 1][0] + n - i + 1);
        chmax(res, f[i + 1][1] + i);
        chmin(ans, res);
    }
    cout << ans << endl;
}
```

---

## 作者：__Louis__ (赞：0)

### 题解：CF1901D Yet Another Monster Fight

### 思路

这道题其实是一个 trick，如果想到某一点就可以很快做完。

首先，既然问最大的最小，那么就是求最坏情况。很容易看出最坏的情况是一次性走到两头。

那么接下来就是如何计算走到两头的答案。

其实不需要模拟，每一个点的权值其实就 $arr_i+pos_i$，也就是本身的值加上其下标对应的值，那么维护这个最大值即可。

预处理完后，遍历每一个位置，判断能量下限的瓶颈在哪里，分成三种判断方式。

- 左边的最大值+右边怪兽的个数。

- 右边的最大值+左边怪兽的个数。

- 能量也需要比当前这个数大。

那么就 $O(n)$ 做完这道题了。

### code


```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int maxn=3e5+10;
int arr[maxn],pre[maxn],suf[maxn];
signed main(){
		int n;
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&arr[i]); 
		}
		for(int i=0;i<=n+5;i++){
			pre[i]=suf[i]=0;
		}
		int sum=0;
		int mx=0;
		for(int i=1;i<=n;i++){
			mx=max(arr[i]-i+1,mx);
			pre[i]=mx+sum;
			sum++; 
		}
		mx=0,sum=0;
		for(int i=n;i>=1;i--){
			mx=max(arr[i]-(n-i),mx);
			suf[i]=mx+sum;
			sum++;
		}
		int ans=0x3f3f3f3f3f3f;
		for(int i=1;i<=n;i++){
			int f=0;
			f=max({pre[i-1]+n-i+1,suf[i+1]+i,arr[i]});
			ans=min(ans,f);
		}
		printf("%lld\n",ans);
}

```

---

## 作者：COsm0s (赞：0)

一个**最大值最小化**问题，显然想到二分。

我们二分 $x$ 的值，并设 $val_i$ 为 $x-a_i+1$。

那么 $i$ 被击中的时间一定 $\leq val_i$。

所以 $val_i < i$ 时，施法位置必定 $\geq i$；$val_i < n - i + 1$ 时，施法位置必定 $\leq i$。

那么 $\Theta(n)$ 扫一遍，联立不等式可求得施法位置的范围。当施法位置无解时，说明当前 $x$ 不可取。

注意：$x$ 一定要大于任意 $a_i$，否则无解。

复杂度 $\Theta(n\log n)$。

```cpp
#include <bits/stdc++.h>
#define REP(i, l, r) for (int i = (l); i <= (r); ++ i)
#define DOW(i, r, l) for (int i = (r); i >= (l); -- i)
#define int long long
#define pii pair<int, int>
#define MPR make_pair
#define L first
#define R second
using namespace std;
namespace Cosmos {
	const int N = 1e5 + 5, inf = 1e9, mod = 998244353;
	const double PI = acos(-1);
	int n, a[N];
	bool check(int x) {
		int l = 0, r = n;
		REP(i, 1, n) {
			if(x < a[i]) return false;
			if (x - a[i] + 1 < i) l = i;
			if (x - a[i] + 1 < n - i + 1) r = min(r, i);
		}
		return l <= r;
	}
	int main() {
		cin >> n;
		REP(i, 1, n) cin >> a[i];
		int l = 1, r = 1e18;
		while (l < r) {
			int mid = l + r >> 1;
			if (check(mid)) r = mid;
			else l = mid + 1;
		}
		cout << l << '\n';
		return 0;
	}
}
signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int T = 1;
//	cin >> T;
	while (T --) Cosmos::main();
	return 0;
}
```


---

## 作者：qscisQJing (赞：0)


# CF1910D 题解
我们可以先考虑对于我们选择的每个位置 $ i $ ，在最坏的情况下要用多大的威力能使其保证被完全消灭。

显然，对于第 $ j $ 个怪物来说，最坏的情况是魔法在这个序列的一边把其他的怪物全部打了一遍，然后再来打第 $ j $ 个。那么，我们就已经有了一个复杂度 $ O(n^2) $ 的暴力，考虑优化它。

不难发现对于每一个 $ j $ 来说，它所受到的最小伤害只和 $ i $ 与它的相对位置有关。那么我们就可以预处理出 $ l_i $ 与 $ r_i $ 分别表示 $ i $ 选在它左边或右边时收到的最小伤害。

对于位置 $ i $ 来说，最小威力 $ x=\max(l_{i-1},r_{i+1},a_i) $ 。

然后只要线性扫一遍就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=3e5+5;
#define ll long long
ll a[MAXN],l[MAXN],r[MAXN],ans=1e18;
int main()
{
	int n;cin>>n;
	for(int i=1;i<=n;i++)scanf("%lld",a+i);
	for(int i=1;i<=n;i++)
	{
		l[i]=max(l[i-1],a[i]);
		if(i>1)l[i]=max(l[i],a[i-1]+n-i+1);
	}
	for(int i=n;i>=1;i--)
	{
		r[i]=max(r[i+1],a[i]);
		if(i<n)r[i]=max(r[i],a[i+1]+i);
	}
	for(int i=1;i<=n;i++)
	{
		ans=min(ans,max(l[i],r[i]));
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Register_int (赞：0)

枚举施法的位置 $i$。由于往哪边弹是随机的，所以我们需要求出最坏情况。对于 $j$ 上的怪物 $a_j$：

- 若 $i=j$，则初始能量值必须 $\ge a_j$。
- 若 $i<j$，则最坏情况是 $<j$ 的全被打死了才到 $j$，初始能量值 $\ge a_j+j-1$。
- 若 $i>j$，则最坏情况是 $>j$ 的全被打死了才到 $j$，初始能量值 $\ge a_j+n-j$。

所以说，当施法在 $i$ 时，答案为：

$$\max\left\{a_i,\max^{i-1}_{j=1}a_j+n-j,\max^n_{j=i+1}a_j+j-1\right\}$$

预处理出前后缀的最大值，时间复杂度 $O(n)$。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 10;

int n, a[MAXN], pre[MAXN], suf[MAXN], ans = 2e9;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) pre[i] = max(pre[i - 1], a[i] + n - i);
	for (int i = n; i; i--) suf[i] = max(suf[i + 1], a[i] + i - 1);
	for (int i = 1; i <= n; i++) ans = min(ans, max({ pre[i - 1], a[i], suf[i + 1] }));
	printf("%d", ans);
}
```

---

## 作者：DerrickLo (赞：0)

我们考虑对于每个数作为起点的贡献，容易想到对于这个数左边的数 $i$，需要用的最大值是 $a_i+n-i$，因为选完这个数后还需要选 $i-1$ 个数，所以这个数的最后可能的出现位置是 $n-i$。而对于这个数右边的 $i$，类似地可以求出需要用的最大值是 $a_i+i-1$，原因类似。

那么求出 $a_i+n-i$ 的前缀最大值，$a_i+i-1$ 的后缀最大值，对于每个数作为起点就能算出最小需要多少，然后取最小值即是答案。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[300005],maxn=LONG_LONG_MAX,cnt,max1[300005],max2[300005],b[300005],c[300005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i]-i+n,c[i]=a[i]+i-1;
	for(int i=1;i<=n;i++)max1[i]=max(max1[i-1],b[i]);
	for(int i=n;i;i--)max2[i]=max(max2[i+1],c[i]);
	for(int i=1;i<=n;i++)maxn=min(maxn,max({max1[i-1],max2[i+1],a[i]}));
	cout<<maxn;
	return 0;
}
```

---

