# [USACO24JAN] Nap Sort G

## 题目描述

Bessie 正在尝试使用她自己的排序算法对一个整数数组进行排序。她有一堆共 $N$（$1\le N\le 2\cdot 10^5$）个整数 $a_1,a_2,\ldots,a_N$（$1\le a_i\le 10^{11}$），她将会按排序顺序将这些数放入一个单独的数组中。她反复查找这堆数中的最小数，将其删除，同时将其添加到数组的末尾。Bessie 在 $p$ 个数的堆中找到最小数需要花费 $p$ 秒。

Farmer John 命令了农场中其他一些奶牛帮助 Bessie 完成任务，她们很懒，然而 Bessie 利用了这一点。她将整数分成两堆：Bessie 堆和助手堆。对于 Bessie 堆中的每个整数，她会正常执行她的算法。对于助手堆中的每个整数，她将其分配给不同的助手奶牛。Farmer John 有一个很大的农场，所以 Bessie 可以找来任意多的助手奶牛。如果助手收到整数 $a_i$，Bessie 会指示该牛小睡 $a_i$ 秒，并在她们醒来时立即将该整数添加到数组末尾。如果 Bessie 和一个助手同时向数组添加整数，Bessie 的整数将优先被添加，因为她是领导者。如果多个助手被分配了相同的整数，她们会同时将多个该整数添加到数组中。

请帮助 Bessie 划分她的数，使得最终得到的数组是排序的，并使得排序该数组所需的时间最少。 

## 说明/提示

### 样例解释 1

在第一个测试用例中，Bessie 可以将 $1,2$ 分配给助手，将 $4,5,10^{11}$ 留给自己。

| 时间 | 事件 |
| :-----------:| :----------- |
| $1$ | 助手添加了 $1$ |
| $2$ | 助手添加了 $2$ |
| $3$ | Bessie 添加了 $4$ |
| $5$ | Bessie 添加了 $5$ |
| $6$ | Bessie 添加了 $10^{11}$ |

在第二个测试用例中，Bessie 的最优方案是自己对所有数进行排序。一个不正确的划分是 Bessie 将 $4$ 分配给助手，其余的分配给她自己，因为助手将 $4$ 添加到数组之前 Bessie 就会将 $17$ 添加到数组中。

在第三个测试用例中，Bessie 可以将所有数都分配给助手。

在第四个测试用例中，Bessie 可以将 $1,4,5$ 分配给助手，将 $2,5,100$ 留给自己。

| 时间 | 事件 |
| :-----------:| :----------- |
| $1$ | 助手添加了 $1$ |
| $3$ | Bessie 添加了 $2$ |
| $4$ | 助手添加了 $4$ |
| $5$ | Bessie 添加了 $5$ |
| $5$ | 助手添加了 $5$ |
| $6$ | Bessie 添加了 $100$ |

### 测试点性质

- 测试点 $2$：$N\le 16$。
- 测试点 $3-5$：$N\le 150$。
- 测试点 $6-8$：$\sum N\le 5000$。
- 测试点 $9-11$：没有额外限制。

## 样例 #1

### 输入

```
4
5
1 2 4 5 100000000000
5
17 53 4 33 44
4
3 5 5 5
6
2 5 100 1 4 5```

### 输出

```
6
15
5
6```

# 题解

## 作者：IamZZ (赞：11)

**G组练习总结#13**

场切题！USACO 真的很喜欢放二分题目（笑）。

### 题目大意

Bessie 又在制造麻烦事！

她现在有一个长度为 $n(n\le2\times10^5)$ 的数组 $a(a_i\le10^{11})$，她现在想要用自己发明的排序方法让其排好序。

具体来说，她的排序方法是：

首先，她会新建一个数组 $t$，用来记录排好序后的 $a$。

然后 Bessie 会自己选取一些数自己处理，假设她目前手上有 $p$ 个数，她需要花费 $p$ 的时间去找到最小的数并马上把它加入 $t$ 的最后。

简单来说，设一开始的集合大小是 $p$，第一个数会在 $p$ 时加入，第二个数会在 $2p-1$ 时，第三个会在 $3p-3$ 以此类推。

但她还有另一种选择，她可以把数交给朋友们来操作，朋友们很懒，假设他们拿到的数是 $v$，他们先睡 $v$，在 $v$ 时加入 $t$ 末尾。

加入的时候，如果 Bessie 和朋友同时加数，Bessie 优先级更高。

现在 Bessie 也想去睡觉啦（不是），她想知道最短的加入所有数的时间。

数据有 $T(T\leq10)$ 组。

### 解题思路（暴力）

处理肯定按照顺序，所以我们可以直接将 $a$ 从小到大排序。

我们考虑最后一个数 $a_n$ 是由谁处理的，如果是 Bessie，所需要的时间就是 $\frac{p(p+1)}2$，如果是朋友们，那就是 $a_n$。

因此，我们考虑枚举集合大小 $p$，判断当前钦定的 $p$ 是否可以让 $a_n$ 被选入集合？

至于向集合内加数需要满足，比如，加第一个时，我们要把 $a_i<p$ 的数都交给朋友们，然后把第一个 $a_j\ge p$ 的数交给 Bessie。

为什么要这样？因为 Bessie 加入的第一个数肯定在 $p$ 时加入，那 $a_i<p$ 的必须满足在她之前处理完了，所以要找朋友帮忙。

而且注意，因为 Bessie 的优先级大于朋友们，所以如果她们同时在 $p$ 加入数，必须满足 Bessie 手上的数小于或等于朋友的，固 $a_j$ 等于 $p$ 的情况不能漏。

对于其他的情况，也都是这样处理，依次处理完所有 $p$ 个数，判断是否处理完了 $a_n$。

时间复杂度 $\Theta(n\sqrt A)$，$A$ 为 $a$ 的值域。

### 参考代码（暴力）

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=2e5+5;
typedef long long ll;
int t,n,c;
ll a[N],m,p;
int main() {
	int i,j;
	scanf("%d",&t);
	while(t) {
		--t;
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
			scanf("%lld",a+i);
		sort(a+1,a+n+1);
		m=a[n];
		for(j=1; 1ll*(j+1)*j/2<=a[n]; ++j) {//枚举集合大小p
			c=j;
			p=0;
			for(i=1; i<=n; ++i) {
				if(!c)
					break;
				if(a[i]>=p+c) {//依次往集合里面塞数
					p=p+c;//记录当前Bessie加数的时间
					--c;
				}
				if(i==n)
					m=min(m,1ll*j*(j+1)/2);//找答案
			}
			if(m<a[n])
				break;
		}
		printf("%lld\n",m);
	}
	return 0;
}
```

### 解题思路（正解）

突然发现几乎没有什么好说的啊……

这个题目的答案具有单调性啊，集合大小的可行性是有单调性的？

没错，这个也挺好想的，越大的集合我们就可以处理更多数！

这么好的代码（不是），一改就可以适应一个二分对吧！

新的时间复杂度 $\Theta(n\log_2\sqrt A)$，完结撒花(●'◡'●)！

### 参考代码（正解）

```c++
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=2e5+5;
typedef long long ll;
int t,n,l,r,d;
ll a[N],m,p;
int check(int c) {
	int i;
	p=0;
	for(i=1; i<=n; ++i) {
		if(!c)
			return 0;
		if(a[i]>=p+c) {
			p=p+c;
			--c;
		}
	}
	return 1;
}
int main() {
	int i,j;
	scanf("%d",&t);
	while(t) {
		--t;
		scanf("%d",&n);
		for(i=1; i<=n; ++i)
			scanf("%lld",a+i);
		sort(a+1,a+n+1);
		m=a[n];
		l=1,r=sqrt(a[n]);
		while(l<=r) {//只不过改了，枚举变成二分就好啦~
			d=l+r>>1;
			if(check(d)) {
				r=d-1;
				m=1ll*d*(d+1)/2;
			} else
				l=d+1;
		}
		printf("%lld\n",m);
	}
	return 0;
}
```

---

## 作者：Ia_aI (赞：5)

# 题意简述
小 J 手上有一堆数字，称为 $A$ 数组，他可以选择将其中一些数字给小 K，也可以全部自己来操作。

设小 J 手上有 $n$ 个数字，则从其中找出一个最小的数字出来，要花 $n$ 个时间。

现在小 J 希望将所有数字一个个找出来，丢到 $B$ 数组，并实现升序。

小 K 将在根据他手上的数字的权值 $x$，在第 $x$ 个时间丢到 $B$ 数组中。

如果在同一时间两个人都丢了数字，则小 J 手上的数字优先进入到 $B$ 数组中。

问至少要花多少时间实现升序操作。

# 解法
考虑二分 Bessie 添加的数字的个数，设为 $mid$。

那么 Bessie 添加的数字被加入序列的总时间就是 $mid + (mid - 1) + \cdots + 1$，也就是 $\frac{mid \times (mid + 1)}{2}$。

所以先要把输入的数据从小到大排序，然后在二分的过程中得出 $\frac{mid \times (mid + 1)}{2}$ 的最小值，再与 $a _ {n}$ 取最小值，即为答案。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,a[1000001],l,r,mid,ans;
bool check(int x)
{
  int nw = 0;
  for(int i = 1;i <= n;i++)
  {
    if(x == 0) return 0;
    if(a[i] >= nw + x)
    {
      nw += x;
      x--;
    }
  }
  return 1;
}
signed main()
{
  cin>>t;
  while(t--)
  {
    cin>>n;
    for(int i = 1;i <= n;i++) cin>>a[i];
    sort(a + 1,a + 1 + n);
    l = 1;
    r = sqrt(a[n]);
    ans = a[n];
    while(l <= r)
    {
      mid = (l + r) / 2;
      if(check(mid) == 1)
      {
        r = mid - 1;
        ans = min(ans,mid * (mid + 1) / 2);
      }
      else l = mid + 1;
    }
    cout<<ans<<endl;
  }
  return 0;
}
```

---

## 作者：cff_0102 (赞：4)

设 Bessie 选择其中的 $x$ 个数，那么她放下最后一个数的时间就是 $\frac{x(x+1)}2$。因此，无论如何，数组中最后一个数放下的时间只可能是 $a_n$ 或 $\frac{x(x+1)}2$。$a_n$ 显然改变不了，那么要让这个数更小，就只能尝试改变 $\frac{x(x+1)}2$ 的值。假设我们确定了 $x$，那么首先最后一个数显然要给 Bessie 选。接着从后往前扫，对于一个数，如果能分配给助手就给助手，否则如果把这个数给助手会让助手在更晚的时间放进来的话（即大于等于 Bessie 会把下一个数放进来的时间），那么这个数就不能给助手，只能给 Bessie 了。如果最后发现给 Bessie 的数的数量大于 $x$，则 $x$ 是不合法的。这样就能 $O(n)$ 判断一个数 $x$ 是否合法。

注意到存在一个数 $x$ 使得如果 Bessie 拿到的数的数量大于等于 $x$ 则能够成功排序，小于 $x$ 则不能成功排序，因此可以二分求解。

注意最后要输出的答案是 $\min(a_n,\frac{x(x+1)}2)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[240520];
int n;
bool check(int x){
    int s=x*(x+1)/2;
    int nw=1;
    for(int i=n-1;i>=1;i--){
        if(a[i]>=s)s-=nw++;
        if(nw>x)return 0;
    }
    return 1;
}
void mian(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+1+n);
    int l=1,r=n;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)){
            r=mid;
        }else{
            l=mid+1;
        }
    }
    cout<<min(a[n],l*(l+1)/2)<<endl;
}
signed main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int aqua;cin>>aqua;while(aqua--)mian();
    return 0;
}
```

---

## 作者：OtterZ (赞：3)

# 1.两种情况
我们知道答案有两种情况：

1. `bessie` 放了最后一个。
2. 小助手放了最后一个

对于情况 $1$，我们尽量把机会给小助手，对于情况 $2$，我们应尽量给 `bessie`。
# 2.如果确定了给小助手几个
我们确定 `bessie` 放元素的时间，然后对于第 $x$ 小的元素，若 `bessie` 下一次放元素时间为 $y$，有：

1. 给小助手，当 $a_x < y$，且没有给够元素给小助手。
2. 给 `bessie`，对于其他情况。

易判定最后一个元素是否给了小助手。
# 3.怎么求答案
我们按第 $2$ 部分判定，用二分法得到 $x$，使：

1. 若给 $x$ 个元素，`bessie` 放最后一个元素；
2. 若给 $x + 1$ 个元素，小助手放最后一个。

给 $x$ 和 $x + 1$ 两种情况取最优即可。
# 4.Talks are cheap,show my codes

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n;
long long a[200005],b[200005];
bool chk(int x){
	int cnt = 0,cst = n - x;
	for(int i = 1; i <= n - x; i ++){
		b[i] = b[i - 1] + cst;
		cst--;
	} 
	b[n - x + 1] = 9e18;
	int nw = 1; 
	bool flg = false;
	long long ans = 0;
	for(int i = 1; i <= n; i ++){
		if(a[i] < b[nw] && cnt < x){
			cnt++;
			ans = max(ans,a[i]);
			flg = true;
		}
		else{
			ans = max(ans,b[nw]);
			nw++;
			flg = false;
		}
	}
	return flg;
}
long long get(int x){
	int cnt = 0,cst = n - x;
	for(int i = 1; i <= n - x; i ++){
		b[i] = b[i - 1] + cst;
		cst--;
	} 
	b[n - x + 1] = 9e18;
	int nw = 1; 
	long long ans = 0;
	for(int i = 1; i <= n; i ++){
		if(a[i] < b[nw] && cnt < x){
			cnt++;
			ans = max(ans,a[i]);
		}
		else{
			ans = max(ans,b[nw]);
			nw++;
		}
	}
	return ans;
}
void slv(){
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++){
		scanf("%lld",&a[i]);
	}
	sort(a + 1,a + n + 1);
	int l = 0,r = n + 1;
	while(l + 1 < r){
		int mid = (l + r) >> 1;
		if(chk(mid))
			r = mid;
		else
			l = mid;
	}
	long long ans = 9e18;
	ans = min(get(l),get(r));
	printf("%lld\n",ans);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		slv();
	}
	return 0;
}
```


---

## 作者：wYYSZLwSSY (赞：2)

怎么没有三分的做法啊。
## 题解
首先把 $a$ 数组从小到大排序。

考虑枚举由 Bessie 排序的数字的个数，计算最小时间。做法是从小到大枚举 $a$，如果能睡眠排序的话就尽可能睡眠排序，因为 Bessie 排序的时间是固定的，所以最小时间就取决于睡眠排序的最大时间，所以尽可能睡眠较小的数。可以睡眠的条件是假设 Bessie 排下一个数字，结束的时间比前面这个数字小（或者两个数字相等，结束时间也可以等于这个数，再或者后面没有手排了）。

可能有的疑问是这样的算法会不会前面优秀了最后最大值并不是最优的，其实不会，因为除了后面没有手排的情况，某个数可以填的原因一定是前面有了足够多的手排数。

这样做时间复杂度是 $O(n^2)$，考虑优化。

前面说了，总时间是睡眠结束时间和手动排序时间的较大值。前置随手排数量增加而减少，后者随手排数量增加而增加，显然取 $\max$ 后是单谷或者单调的，可以三分，时间复杂度 $O(n\log n)$。
## 代码
代码比二分写法短，但还是有一些细节的。
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,a[200005],T;
void ini(){;}
int check(int p){
	int num=0,ans=0,d=1;
	while(d<=n and num<p){
		while(d<=n and n-d+num>=p and (a[d]<ans+p-num or a[d]==a[d+1] and a[d]==ans+p-num))
          //n-d+num>=p 表示无需再睡眠排序
			++d;
		if(d<=n)ans+=p-num,++num,++d;
		else ans=a[n];//注意这里
	}
	return max(p*(p+1)/2,(d>n?ans:a[n]));//d<=n 表示没到最后就用完了手排
}
void mymain(){
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];
	a[n+1]=0;
	sort(a+1,a+n+1);
	int l=0,r=n;
	while(l<r){
		int lmid=(2*l+r)/3,rmid=(2*r+l)/3;
		if(check(lmid)<check(rmid))r=rmid;
		else l=lmid+1;
	}
	int ans=3e18;
	for(int i=max(0ll,l-2);i<=min(n,l+2);++i)ans=min(ans,check(i));//懒了，直接这样写了，其实就是避免三分有偏移
	cout<<ans<<'\n';
	return ;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
// 	freopen("1.in","r",stdin);
	cin>>T;
	while(T--)ini(),mymain();
	return 0;
}
```

---

## 作者：huazai676 (赞：1)

[题目](https://www.luogu.com.cn/problem/P10139)

设 $a$ 已经排过序。由于最大数总是最后被加进去，如果 Bessie 将它加入，答案则为 $\frac{k\times(k+1)}{2}$（$k$ 为 Bessie 加入数字的总数），如果它 nap 后加入则答案为 $a_n$。

于是可以枚举 Bessie 加入数字的总数 $k$，判断是否可以达到。令 $s_i$ 表示 Bessie 第 $i$ 次加入数字的时间。则原问题可以转化为：数轴上有 $n$ 个点（$a_1 , a_2,\cdots , a_n$）和 $k$ 个空缺（$s_1,s_2,\cdots,s_k$），需要选 $k$ 个点补到空缺上并且使这些点的相对顺序不变（并且要求选最后一个点）。发现如果不要求选最后一个点无论如何都可以满足。这样从后往前扫一遍就能判断了。
（实现上要注意点可能重合的细节，但数据没卡）

然后发现 $k$ 越小用时越少，也越难实现。枚举改成二分复杂度就对了，$O(n\log n)$。

```cpp
#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

typedef long long ll;

const int N=2e5+10;
const ll inf=1e18;

int n,pre[N];
ll a[N],s[N];

bool check(int k)
{
	if(k==n+1) return true;
	for(int i=1;i<=k+1;i++) s[i]=s[i-1]+k-i+1;
	int i=n-1,j=k-1;
	while(a[i]>=s[j+1])
	{
		if(a[i+1]==a[i]&&a[pre[i]]<s[j+1]) return true;
		if(!j) return false;
		i--,j--;
	}
	return true;
}

void solve()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) pre[i]=a[i]==a[i-1]? pre[i-1]:i-1;
	int l=1,r=n+1;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	check(l);
	printf("%lld\n",min(a[n],l<=n? s[l]:inf));
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--) solve();
	
	return 0;
}
```


---

## 作者：chenwenmo (赞：0)

## 提供一个瓶颈是基数排序的做法

首先对原数组排序，方便考虑。

考虑先枚举 Bessie 堆的大小 $m$，

如果 $a_n$ 是助手堆的，那么答案就是 $a_n$；否则答案是 $\frac{m\cdot(m+1)}{2}$。因此强制让 $a_n$ 放入 Bessie 堆。

那么现在的问题就是 check $m$ 是否存在包含 $a_n$ 的合法方案。

在一个方案中，Bessie 堆的数把原序列划分成若干段，那么原序列中助手堆的数，会有对应的合法值域区间，每个助手堆中的数必须在相应区间中，方案才能合法。

因此我们可以 $O(n)$ 从后往前分段。假设枚举到 $a_i$，如果 $a_i$ 是在当前合法值域区间里，就把 $a_i$ 分到这一段，否则 $a_i$ 就设为这一段的左端点（即把 $a_i$ 放入 Bessie 堆中），然后考虑 $a_{i-1}$。放完最后一个 Bessie 数后，再 check 序列前面剩下的一些数是否在合法区间中，即可。这样做是 $O(n^2)$ 的。

这样做其实非常麻烦，因为我们只关心是否存在方案，而不关心具体方案。

考虑不合法的情况长什么样。已经选了 $a_n$，考虑 $a_{n-1}$，如果 $a_{n-1}<\sum\limits_{j=1}^{m}j$，这就意味着 $a_1,a_2,\dots,a_{n-1}$ 是一定存在方案的，不用再往前分段考虑了。

否则，我们就必须选 $a_{n-1}$，然后继续依次往前考虑 $a_{n-x}$，直到 $a_{n-x}<\sum\limits_{j=x}^{m}j$。

也就是说，$m$ 合法，当且仅当存在 $i\in[n-m,n-1]$，使得 $a_{i}<\sum\limits_{j=n-i}^{m}j$。于是就有了更简便的 $O(n^2)$ 写法。

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 2e5 + 5;

int n;
LL a[N], b[N];

LL sum(int l, int r) {
    return b[r] - b[l - 1];
}

void solve() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        b[i] = b[i - 1] + i;
    }
    sort();
    LL ans = a[n];
    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= n - i + 1; j--) {
            if (a[j - 1] < sum(n - j + 1, i)) {
                ans = min(ans, sum(1, i));
            }
        }
    }
    printf("%lld\n", ans);
}
```

继续考虑优化，发现 $i,j$ 可以交换枚举顺序，然后二分，即可做到 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 2e5 + 5;

int n;
LL a[N], b[N];

LL sum(int l, int r) {
    return b[r] - b[l - 1];
}

void solve() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        b[i] = b[i - 1] + i;
    }
    sort();
    LL ans = a[n];
    for (int i = 1; i <= n; i++) {
        int len = n - i + 1, l = len, r = n, mid;
        while (l < r) {
            mid = l + r >> 1;
            if (a[i - 1] < sum(len, mid)) r = mid;
            else l = mid + 1;
        }
        if (a[i - 1] < sum(len, r)) {
            ans = min(ans, sum(1, r));
        }
    }
    printf("%lld\n", ans);
}
```

更快的做法就是，用初中二次函数相关知识，推一下式子，做到 $O(1)$ 求，那么复杂度瓶颈就是 sort 了，求答案是 $O(n)$ 的。然后我选择 $256$ 进制的基数排序，即可做到非常接近线性。

完整代码：

[提交记录](https://www.luogu.com.cn/record/228929909)

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using DB = double;

namespace FIO {
    char buf[1 << 20], *_now = buf, *_end = buf;
    inline char _getchar() {
        return _now == _end && (_end = (_now = buf) + fread(buf, 1, 1 << 20, stdin), _now == _end) ? EOF : *_now++;
    }
    
    template <typename T>
    void read(T &x) {
        x = 0;
        char c = getchar();
        for (; c < '0' || c > '9'; c = getchar());
        for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + (c ^ 48), c = getchar());
    }
} using FIO::read;

const int N = 2e5 + 5;

int n;
LL a[N], b[N];

LL sum(int l, int r) {
    return b[r] - b[l - 1];
}

// 基数排序
int cnt[260];
LL tmp[N];
void sort() {
    for (int i = 0; i <= 40; i += 8) {
		memset(cnt, 0, sizeof(cnt));
		for (int j = 1; j <= n; j++) cnt[(a[j] >> i) & 255]++;
		for (int j = 1; j < 256; j++) cnt[j] += cnt[j - 1];
		for (int j = n; j >= 1; j--) tmp[cnt[(a[j] >> i) & 255]--] = a[j];
		for (int j = 1; j <= n; j++) a[j] = tmp[j];
	}
}

void solve() {
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        b[i] = b[i - 1] + i;
    }
    sort();
    LL ans = a[n];
    for (int i = 1; i <= n; i++) {
        int len = n - i + 1;
        LL x = a[i - 1] + a[i - 1] + (LL)len * len - len;
        LL dlt = x + x + x + x + 1;
        if (dlt < 0) {
            ans = min(ans, sum(1, len));
            continue;
        }
        LL k = floor((-1 + sqrt(dlt)) / 2 + 1);
        if (k <= n) {
            ans = min(ans, sum(1, max((int)k, len)));
        }
    }
    printf("%lld\n", ans);
}

int main() {
    int T;
    read(T);
    while (T--) solve();
    return 0;
}
```

---

## 作者：Helenty (赞：0)

排序后考虑 $a,b$ 为原始数 $a$ 进去变成 $c$，则 $b$ 一定也得进去，这是完备的条件，这个条件也告诉我们对于不关键的 $c$ 我们取其最近的 $a$ 就行了。

我们要把后缀进去个数与进去个数的关联性进行解析，考虑确定一段作为极长后缀，那么我们只有考虑后缀头的对应 $c$ 最小能是多小保证后缀是稳定的，也就是后缀头的前一个大的合法的，其余的进去部分不关键用上述方法省略即可。

本题另一个角度就是根据题目最终贪心形式决定的，考虑如果集合大小为 $p$ 时包含了 $a_n$ 那么答案一定是 $\frac{p(p+1)}{2}$ 不会是 $a_i$ 因为 $a_i\in[\frac{p(p+1)}{2},a_n]$ 也会进去，所以我们只需要求最小的大小去包含住 $a_n$ 即可。

---

## 作者：Dengkaizhong (赞：0)

[题目传送](https://www.luogu.com.cn/problem/P10139)
### 题意描述
既然是 USACO 的题，那自然是离不开那个 Farmer John 和奶牛 Bessie 了，让我们看一下今天他们又在做什么~~幺蛾子~~。

今天 Bessie 准备要学会排序，Bessie 她的排序算法非常的朴素，从 $P$ 个数字中用 $P$ 秒找到最小值，在旁边的 Farmer John 看着干着急，连忙又叫其他的奶牛过来帮忙，但是其他的奶牛只想睡觉，Bessie 想到了一个好方法，让她们拿到一个数后就睡觉，睡她拿的那个数秒，然后把他放进去。求排序所需的最短时间。不要以为我在乱读题意，下面才是形式化。

你有 $N$ 个数，你要给他们排序，你有两种代价值，要么在第 $a_i$ 秒放入 $a_i$ 要么把 $x$ 个数单独提出来，分别用 $x , x+x-1 , x+x-1+x-2 \dots \sum^{x}_{i=1} i$ 秒。

### 做题过程

首先读题意，发现这是俩伙人，要排序，第一考虑是用 $x$ 秒加 $x$ 的一定要 $x$ 小于 Bessie 的高级做法所用的时间，在分析下，发现当 Bessie 要分多少个数是确定的，那她的放置时间就一定也确定了，所以开始我们就可以枚举 Bessie 要分多少个数。
    
当我们知道 Bessie 要分多少个数事我们就可以枚举每个数，当他的大小小于了这时 Bessie 放置的时间，就让它提前被助手放进数组，是因为肯定助手能放小的放小的，如果 $x$ 太大了，还让助手放那就废了。
    
注意，我们的助手能放置的数是有限的，所以每放一个就少一个，机会用完了，就只能请 Bessie 来放了。
    
当我们的 Bessie 放完了她能放的最后的一个数时，还有数没放，那就糟糕了，最大的就只能让助手来了，而如果放完了，那时间就是 Bessie 放最后一个的时间。
    
### 时间复杂度

当前时间复杂度先有个 $T$ 的大循环，还要给输入的数组提前排好序，最后枚举 Bessie 要分多少个数用 $N$ 次，循环内还要再循环 $N$ 次遍历每个数。

时间复杂度：$O(T(N \log N+N^2))$

这个时间复杂度能通过前 $8$ 个点，但后面的点依旧不行。

### 优化
#### 玄学思考

由 $1\le N\le 2\cdot 10^5$ 和原本排序就有的 $O(N \log N)$ 的时间复杂度，盲猜最终时间复杂度应为 $O(N \log N)$ 而原本 $O(N^2)$ 怎么优化一个 $N$ 成 $\log N$ 考虑二分。

#### 严谨思考

因为发现当 Bessie 要分多少个数越大只要不让助手丢最后一个进去，那么时间的消耗就越大，当 Bessie 要分多少个数越小那肯定是更小，或者一不小心就让助手睡上个 $x_{max}$ 秒了。所以这个东西实际上整体是具有单调性的考虑二分。

二分就是标准的二分答案，二分 Bessie 要分多少个数，当我们的 Bessie 成功放了最后一个数时，那就让 $R$ 向左偏，当我们的助手一不小心睡到了天荒地老时，就让其 $L$ 向右偏。

最后直接输出最小值就行。

注意这个实际上样例就提出了，int 连输入都存不下了，更别提什么最小值初值用 int 的最大值了。

### ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int ls[200005];
int ans;

signed main()
{
//	freopen("sort.in","r",stdin);
//	freopen("sort.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		ans=LONG_LONG_MAX;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>ls[i];
		}
		sort(ls+1,ls+1+n); 
		int L=1,R=n;
		while(L<=R)
		{
			int i=(L+R)/2;
//			cout<<"I:"<<i<<endl;
			int ti=i;
			int cnt=0;
			int cnt2=n-i;
			for(int j=1;j<=n;j++)
			{
//				cout<<"TI:"<<ti<<" cnt2:"<<cnt2<<endl;
				if(ls[j]>=ti||cnt2==0)
				{
					cnt++;
//					cout<<"cnt:"<<cnt<<" ls[j]:"<<ls[j]<<endl;
					if(cnt==i)
					{
						if(j==n)
						{
							ans=min(ans,ti);
							R=i-1;
						}
						else
						{
							ans=min(ans,ls[n]);
							L=i+1;
						}
						break;
					}
					ti+=(i-cnt);
				}
				else
				{
					cnt2--;
				}
			}
//			cout<<"L:"<<L<<" R:"<<R<<endl;
		}
//		cout<<"ANS:";
		cout<<ans<<endl;
	}
	return 0;
}
```

---

