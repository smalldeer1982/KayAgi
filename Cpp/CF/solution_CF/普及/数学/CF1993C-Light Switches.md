# Light Switches

## 题目描述

一栋公寓楼里面有 $n$ 个房间，初始时每个房间的灯都是关的。为了更好地对房间里的灯进行控制，房东计划在不同时间给每个房间安装芯片。具体地，房东给每个房间安装芯片的时刻可以用包含 $n$ 个整数的数组 $a$ 来表示，其中第 $i$ 个元素 $a_i$ 表示房东给第 $i$ 个房间安装芯片的时刻。

一旦某个房间被安装上了芯片，这个房间里面的灯的状态每隔 $k$ 分钟就会发生一次变化，也就是说，安装商芯片的这一时刻起，这个房间里面的灯会先被点亮，$k$ 分钟后被熄灭，$k$ 分钟后再被点亮，如此循环往复。形式化的来讲，对于第 $i$ 个房间的灯，它的状态会在第 $a_i,a_i+k,a_i+2k,\dots$ 分钟发生变化。

现在请你求出所有房间的灯都被点亮的最小时刻，或者报告不存在所有房间的灯都被点亮的时刻。

## 说明/提示

对于所有数据：

- $1\leqslant T\leqslant 10^4$。
- $1\leqslant k\leqslant n\leqslant 2\times 10^5$，$\sum n\leqslant 2\times 10^5$。
- $1\leqslant a_n\leqslant 10^9$。

Translated by [Eason_AC](/user/112917)。

## 样例 #1

### 输入

```
9
4 4
2 3 4 5
4 3
2 3 4 5
4 3
3 4 8 9
3 3
6 2 1
1 1
1
7 5
14 34 6 25 46 7 17
6 5
40 80 99 60 90 50
6 5
64 40 50 68 70 10
2 1
1 1000000000```

### 输出

```
5
-1
10
8
1
47
100
-1
-1```

# 题解

## 作者：wangzc2012 (赞：8)

# CF1993C Light Switches
## 思路分析
首先，根据题意不难得出，由于灯的开关存在循环，所以最终的答案一定会在最后一个亮起的灯亮起的时间里。  
换句话说，如果我们用 $maxa$ 表示最后一个给房间安装芯片的时刻，那么答案一定在 $maxa$ 至 $maxa+k-1$ 之间。  
因此，我们定义两个指针 $l$ 和 $r$ 并遍历所有的 $a_{i}$，计算当前灯在 $maxa$ 至 $maxa+k-1$ 之间的亮起时间，同时更新 $l$ 和 $r$。  
最后，如果 $l \le r$，则存在所有的灯都同时亮起的时刻，因此输出 $l$，否则不存在这样的时刻，输出 $-1$。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,a[200005];
int main(){
    cin>>t;
    while (t--){
        int maxa=0;
        cin>>n>>k;
        for (int i=1;i<=n;i++){
            cin>>a[i];
            maxa=max(maxa,a[i]);  //计算最大值
        }
        int l=maxa,r=maxa+k-1;  //全部灯都亮起的时刻一定在l和r中间
        for (int i=1;i<=n;i++){
            if (((maxa-a[i])/k)%2==1) l=max(l,a[i]+((maxa-a[i])/k+1)*k);  //判断当前的灯是否亮起，如果亮起，更新左边界
            else r=min(r,a[i]+((maxa-a[i])/k+1)*k-1);  //如果未亮起，更新右边界
        }
        if (l<=r) cout<<l<<'\n';  //如果存在这样的时刻，输出最小时刻
        else cout<<-1<<'\n';  //不存在这样的时刻，输出-1
    }
    return 0;
}
```

---

## 作者：UniGravity (赞：6)

## Solution CF1993C Light Switches

记最大的 $a_i$ 记为 $maxa$。显然最后的答案必然在区间 $[maxa,maxa+k)$ 间。

丢张图：  
![](https://cdn.luogu.com.cn/upload/image_hosting/so70jc9o.png)  

灰色是 $maxa$ 代表的区间。可以发现每个区间覆盖只会覆盖头或尾。判断可行的方法就是判断某个位置是否被所有 $n$ 个区间覆盖。

上面的判断问题可以使用差分数组 $d$ 进行处理。

周期是 $2k$，可以想到对 $(maxa-a_i)\bmod2k$ 的结果进行分类讨论：
* 若 $(maxa-a_i)\bmod2k<k$，则属于上图红色部分，将区间 $[0,k-(maxa-a_i)\bmod k-1]$ 加一即可。
* 否则是蓝色部分，区间 $[k-(maxa-a_i)\bmod k,k-1]$ 加一。

具体实现可以看[完整代码](https://codeforces.com/contest/1993/submission/274391379)。

---

## 作者：myyyIisq2R (赞：3)

要求最早的同时亮灯的时候，拿样例来模拟一下：
$a_i = 2,k=4$ 时：亮灯的时刻为 $2,3,4,5,10,11,12,13,18,19,20,21\dots$，发现这些数对 $2k$ 取模的值永远与 $[a_i,a_i+k)$ 模 $2k$ 的值相同。那么我们只需要枚举每一个 $a_i$，并且给 $[a_i,a_i+k)$ 模 $2k$ 的值累计贡献。当 $i =n$ 时，输出第一个贡献数到 $n$ 的 $a_i+j,j\in[0,k)$ 即可。若没有，输出 $-1$。

上述复杂度是 $O(nk)$ 的，必然不能通过。发现区间累计的过程可以用线段树维护，用线段树优化可以做到 $O(n\log k)$。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 4e5+5;
int a[N];
int vis[N];
struct TREE
{
	#define lson(x) x<<1
	#define rson(x) x<<1|1
	struct NODE
	{
		int l{},r{},val{},lz{};
	}tree[N<<2];
	void pushup(int x)
	{
		tree[x].val = tree[lson(x)].val + tree[rson(x)].val;
	}
	void build(int l,int r,int x)
	{
		tree[x].l = l,tree[x].r = r;
		int mid = (l+r)>>1;
		tree[x].lz = 0;
		tree[x].val = 0;
		if(l == r){tree[x].val = vis[l];return;}
		build(l,mid,lson(x)),build(mid+1,r,rson(x));
		pushup(x);
	}
	void pushdown(int x)
	{
		if(tree[x].lz)
		{
			tree[lson(x)].lz += tree[x].lz;	tree[rson(x)].lz += tree[x].lz;
			int mid = (tree[x].l +tree[x].r) >> 1;
			tree[lson(x)].val += tree[x].lz * (mid - tree[x].l + 1);
			tree[rson(x)].val += tree[x].lz * (tree[x].r - mid);
			tree[x].lz &= 0;
		}
	}
	void update(int l,int r,int k,int x)
	{
		if(l<=tree[x].l&&tree[x].r<=r)
		{
			tree[x].val += k*(tree[x].r-tree[x].l+1);
			tree[x].lz += k;
			return ;
		}
		pushdown(x);
		int mid = (tree[x].l + tree[x].r) >> 1;
		if(l<=mid) update(l,r,k,lson(x));
		if(r>mid) update(l,r,k,rson(x));
		pushup(x);
	}
	int query(int l,int r,int x)
	{
		if(l<=tree[x].l && tree[x].r <= r) return tree[x].val;
		pushdown(x);
		int res{};
		int mid = (tree[x].l+tree[x].r) >> 1;
		if(l<=mid) res += query(l,r,lson(x));
		if(r>mid) res += query(l,r,rson(x));
		return res;
	}
}tree;
signed main()
{
	#ifdef LOCAL
	freopen("in.in","r",stdin);
//	freopen("out.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	int T = read();
	while(T--)
	{
		int n = read(),k = read();
		memset(vis,0,sizeof(int)*(k*2+3));
		bool ok{};
		for(int i{1};i<=n;i++)
			a[i] = read();
		sort(a+1,a+1+n);
		
		tree.build(1,(2*k),1);
		for(int i{1};i<n;i++)
		{
			int val = a[i];
			int l = val % (2 *k);
			int r = (val+k-1) % (2*k);
			l++,r++;
			if(l<=r) tree.update(l,r,1,1);
			else tree.update(l,2*k,1,1),tree.update(1,r,1,1);
			
		}
		int val = a[n];
		for(int j{val};j<val+k;j++) 
		{
//			cout<<j<<":"<<tree.query((j%(2*k))+1,(j%(2*k))+1,1)<<" ";
			if(tree.query((j%(2*k))+1,(j%(2*k))+1,1) == n-1) 
			{
				writeln(j);
				ok = true;
				break;
			}
		}
		if(ok) continue;
		writeln(-1);
	 } 

	return 0;

 }
```

---

## 作者：AK_400 (赞：2)

首先对每个灯的开关周期都是 $2\times k$，于是我们开一个数组  $b$ 使 $b_i=a_i \bmod (2\times k)$。

发现第 $i$ 个灯亮的区间为 $[b_i,b_i+k)$，于是我们做区间加，最后查哪个加到了 $n$，找不到就无解。

这个可以线段树、树状数组、差分来做，我用的是差分。

你现在找到了周期中最小的可被覆盖 $n$ 次的时间，我们从 $\max_{i=1}^na_i$ 开始枚举，找到第一个在周期中被覆盖 $n$ 次的时间即可。

实现时可以把差分数组开到  $4\times k$ 这样你可以做 $b_i\ge k$ 的部分时不用取模。 

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,k,a[200005],b[200005],d[800005],cnt1[800005];
void slv(){
    for(int i=0;i<=k+k+k+k;i++)d[i]=cnt1[i]=0;
    cin>>n>>k;
    for(int i=1;i<=n;i++){;
        cin>>a[i];
        b[i]=a[i]%(k+k);
        d[b[i]]++;
        d[b[i]+k]--;
        d[b[i]+k+k]++;
        if(b[i]<k)d[b[i]+k+k+k]--;
    }
    cnt1[0]=d[0];
    for(int i=1;i<k+k+k+k;i++)cnt1[i]=cnt1[i-1]+d[i];
    int p=-1;
    for(int i=0;i<k+k+k+k;i++){
        if(cnt1[i]==n){
            p=i;
            break;
        }
    }
    if(p==-1){
        cout<<-1<<endl;
        return;
    }
    p%=k+k;
    int mx=0;
    for(int i=1;i<=n;i++)mx=max(a[i],mx);
    int ans=mx;
    for(int i=0;i<k;i++){
        if((mx+i)%(k+k)==p)ans=mx+i;
    }
    cout<<ans<<endl;
    return;
}
signed main(){
    cin>>T;
    while(T--)slv();
    return 0;
}/**/
```

---

## 作者：jiayixuan1205 (赞：1)

## 题解：CF1993C Light Switches
### 分析

模拟赛的题目，当时也想了一个 $O(k)$ 的类似做法，同样是记录区间，但是不知道怎么写挂了，学习了一下之后决定记录一下更简便的做法。

可以发现，第 $i$ 盏灯在 $a_i$ 时间后以 $2k$ 为周期开关。由于开灯的时间长度恒为 $k$。要求答案最短，那么答案一定存在于 $[a_{max},a_{max}+k)$ 区间内（在此之前 $a_{max} $ 恒不亮，在此之后是相同周期性重复）。所以我们只需要判断每一个 $a$ 在该区间内的覆盖距离即可。

- 如果前面有奇数段 $k$ 已被经过，那么在 $a_{max}$ 处灯是关闭的，应该枚举下一个区间记录左端点。
- 如果前面有偶数段，那么在 $a_{max}$ 处灯是打开的，直接记录该段的右端点比较覆盖即可。

只要最后得到的右端点在左端点的右侧即存在一段合法区间即有解，那么无解的情况也就很好判断了——不存在合法区间，最小值就是所得的左端点。

### 注意
区间是左闭右开的，存右端点时记得减一。
### 代码展示
```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'

using namespace std;

const int N = 2e5+10;
int T;
int n,k,a[N];

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		int maxx=-1;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			maxx=max(a[i],maxx); 
		}
		int l=maxx,r=maxx+k-1;
		for(int i=1;i<=n;i++)
		{
			int tmp=(maxx-a[i])/k;
			if(tmp&1) l=max(l,a[i]+k*(tmp+1));
			else r=min(r,a[i]+k*(tmp+1)-1); 
		}
		if(r<l) cout<<-1<<endl;
		else cout<<l<<endl;
	}
	return 0;
}
```

---

## 作者：tzzl3035 (赞：1)

# 1993C 题解
### 题目大意
有 $t$ 组数据，每组给出两个正整数 $n$ 和 $k$，以及 $n$ 个正整数 $a_i$，表示第 $i$ 盏灯第一次开启的时间，之后每隔 $k$ 个单位时间改变一次状态，求所有灯最早同时亮起的时间，若无解则输出 `-1`。
### 大致思路
寻找规律可以发现，只需统计最后一个第一次亮起的灯第一次亮起开始计算的 $k$ 个单位时间中每个灯亮起的时刻的左边界和右边界即可。若左边界更大，则无解，否则答案为左边界。
### 核心代码
```cpp
void solve() {
  // 输入
  int n, k; std::cin >> n >> k;
  std::vector<long long> a(n+3);
  long long omax = 0;
  for(int i = 1; i <= n; ++i) {
    std::cin >> a[i];
    omax = std::max(omax, a[i]);
  }
  // 统计左右边界
  long long l=omax, r=omax+k-1;
  for(int i = 1; i <= n; ++i) {
    long long tmp = (omax - a[i]) / k;
    if(tmp & 1) {
      l = std::max(l, a[i] + (tmp+1) * k);
    }
    else {
      r = std::min(r, a[i] + (tmp+1) * k - 1);
    }
  }
  // 输出
  if(l > r) std::cout << -1 << '\n';
  else std::cout << l << '\n';
}

```
### [RESULT](https://codeforces.com/contest/1993/submission/274408376)

---

## 作者：Heldivis (赞：1)

## CF1993C Light Switches

只需要将 $a_i$ 以 $2k$ 为周期，映射到最小的大于等于 $\max\{a_i\}$ 的区域即可。

这样我们得到了一个新的 $a_i$，在同一个周期中。那么如果 $\max\{a_i\} - \min\{a_i\} + 1 \le k$，说明最后这 $n$ 个在同一个周期内，并且开灯的差时间不超过 $k$，最小的可行时间就是 $\max\{a_i\}$（因为要保证每一个灯都是开的）。

代码：

```cpp
void Main() {
  n = read(), k = read();
  for (int i = 1; i <= n; ++i) a[i] = read();
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; ++i) {
    // 除法加速 while (a[n] - a[i] - k + 1 > 0) a[i] += 2 * k;
    if (a[n] - a[i] - k + 1 <= 0)
      p = 0;
    else
      p = (a[n] - a[i] - k) / (2 * k) + 1;
    a[i] = p * 2 * k + a[i];
  }
  if (*max_element(a + 1, a + 1 + n) - *min_element(a + 1, a + 1 + n) + 1 > k)
    puts("-1");
  else
    printf("%lld\n", *max_element(a + 1, a + 1 + n));
}
```

---

## 作者：Mirage_Insane (赞：1)

考虑答案的性质。

根据题目描述，可以发现一个数 $x$，若能成为答案，则一定满足：对于 $\forall i,x \geq a_i$ 且 $\lceil \frac{x - a_i + 1}{k} \rceil$ 是奇数。

进一步观察可以发现，设 $p$ 为序列中的最大值，则 $\lceil \frac{x - p + 1}{k} \rceil$ 一定为 1。感性理解一下，若 $\lceil \frac{x - p + 1}{k} \rceil$ 大于 1 且当前的 $x$ 可以成为答案，则 $x - 2 \times k$ 也一定可以成为答案。

因此我们枚举 $p$ 到 $p + k - 1$，对于每一个数，判断其是否能成为答案，如果可以就输出并跳出循环。若一个合法的数都没有，就无解了。

这样的时间复杂度是 $\mathbb{O}(nk)$ 的，仍需优化。

由于答案出现的范围大小只有 $k$，所以对于 $\forall \lceil \frac{x - a_i + 1}{k} \rceil$，其值最多增加 1。因此我们先判断 $p$ 是否合法，若不合法，则找到所有不满足条件的 $i$，计算出其对应的另一个值 $\lceil \frac{x - a_i + 1}{k} \rceil \times k + a_i$，这个数即为在 $p$ 和 $p + k - 1$ 之间的最小的能使 $i$ 满足条件的数。设 $Max$ 为这些数的最大值，判断其是否合法。合法即为答案，否则无解。

时间复杂度 $\mathbb{O}(n)$。

### Code:

```cpp
#define Vanishment return
#define This 0
#define World ;
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
int a[200005], n, k;
bool check(int x) {
    bool flag = true;
    for(int i = 1; i <= n; i++) flag &= (((x - a[i] + k) / k) & 1);
    return flag;
}
signed main() {
    int T;
    SF("%lld", &T);
    while(T--) {
        SF("%lld%lld", &n, &k);
        int p = 0;
        for(int i = 1; i <= n; i++) SF("%lld", &a[i]), p = max(p, a[i]);
        bool flag = false;
        if(!check(p)) {
            int Max = 0;
            for(int i = 1; i <= n; i++) {
                if(!(((p - a[i]) / k + 1) & 1)) {
                    int sum = (p - a[i]) / k + 1;
                    Max = max(Max, sum * k + a[i]);
                }
            }
            if(check(Max)) {
                PF("%lld\n", Max);
                flag = true;
            }
        }
        else {
            PF("%lld\n", p);
            flag = true;
        }
        if(!flag) PF("-1\n");
    }
    Vanishment This World
}
```

---

## 作者：CNS_5t0_0r2 (赞：0)

从同余这方面考虑了半个小时无果，我是唐氏。

因为所有灯亮起和熄灭的周期相同，所以如果存在符合要求的时刻，这个时刻最早一定在最后一个安上芯片的灯第一次亮灯的周期内（记为 $[\max_a,\max_a + k - 1]$）。

同样是因为所有灯亮起和熄灭的周期相同，每盏灯在 $[\max_a,\max_a + k - 1]$ 这个区间内一定会有一段时刻是亮起的，这又要分两种情况：

1. 第 $i$ 盏灯在 $$[a_i + (\lfloor \frac{(\max_a - a_i)}{k} \rfloor + 1) \times k,\max_a + k - 1]$$ 时刻亮起，说明 $[\max_a,a_i + (\lfloor \frac{(\max_a - a_i)}{k} \rfloor + 1) \times k - 1]$ 这段时刻是不合法的。

2. 第 $i$ 盏灯在 $$[\max_a,a_i + (\lfloor \frac{(\max_a - a_i)}{k} \rfloor + 1) \times k - 1]$$ 时刻亮起，说明 $[a_i + (\lfloor \frac{(\max_a - a_i)}{k} \rfloor + 1) \times k,\max_a + k - 1]$ 这段时刻是不合法的。

因此，我们维护 $l,r$ 表示满足条件的时刻区间为 $[l,r]$。

两种情况判断条件详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 9;
int n,k;
int a[N],max_a;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T--){
		max_a = 0;
		cin >> n >> k;
		for(int i = 1;i <= n;i++){
			cin >> a[i];
			max_a = max(max_a,a[i]);
		}
		int l = max_a,r = max_a + k - 1;
		for(int i = 1;i <= n;i++){
			if((max_a - a[i]) / k % 2 == 1)
				l = max(l,a[i] + ((max_a - a[i]) / k + 1) * k/*第i盏灯在区间内亮起的第一个时刻*/);
			else
				r = min(r,a[i] + ((max_a - a[i]) / k + 1) * k - 1/*第i盏灯在区间内亮起的最后一个时刻*/);
		}
		if(l <= r)
			cout << l << '\n';
		else
			cout << "-1\n";
	}
	return 0;
}
```

---

## 作者：zjj2024 (赞：0)

### 思路

将每个灯开的时间在加上很多个 $k$ 之后，与最大的数在同一个 $k$ 的范围以内，可以证明，如果有解，在 $5\times k$ 的范围以内一定会出现题目中所描述的情况。

模拟即可，但要卡常。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
ll a[N];
int b[5*N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll T,n,k;
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		ll maxn=0,p=2*k,minn=1e9+10;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			maxn=max(maxn,a[i]);
		}
		for(int i=1;i<=n;i++)
		{
			a[i]=a[i]+(maxn-a[i])/p*p;//平移到同一个k的范围以内
			minn=min(minn,a[i]);//记录最小值
		}
		int flag=1;
		for(int i=1;i<=n;i++)
		{
			b[a[i]-minn]++;
			b[a[i]+k-minn]--;
			b[a[i]+2*k-minn]++;
			b[a[i]+3*k-minn]--;//5k范围内的区间进行标记，使用差分进行优化
		}
		for(int i=0;i<=2*p+k;i++)
		{
			if(i)b[i]=b[i-1]+b[i];
			if(b[i]==n)
			{
				cout<<i+minn<<'\n';
                flag=0;
				break;
			}
		}
		for(int i=0;i<=2*p+k;i++)b[i]=0;//清空数组
        if(flag)cout<<"-1\n";
	}
	return 0;
}
```

---

## 作者：GGapa (赞：0)

考虑题目中的灯开启得条件为 $\lfloor \frac{(time - a_i)}k \rfloor \equiv0 \pmod 2$，其中 $time$ 代表时间，显然先将 $a_i$ 排序并不会影响最终的答案。

结论：最终答案只可能从 $[a_{mx}, a_{mx} + k]$ 中选取，证明：

> 使用反证法，若对于某个 $i$，灯开启的区间与 $[a_{mx} + 2k, a_{mx} + 3k]$ 有交集，但与 $[a_{mx}, a_{mx} + k]$ 没有交集，又有开关灯以 $2k$ 为一个循环，故其与区间 $[a_{mx}, a_{mx} + k]$ 一定有交集，与假设不符，证毕。

考虑贪心，将 $a_i$ 从大往小排序，依次选取对于每个 $a_i$ 最小的使 $1 - i$ 均满足条件的 $time$，$time$ 是不减的，归纳法，将 $a_1$ 和 $a_2$ 带入，有 $a_1 = time_1$，若 $time_1 > time_2$，则 $time_2 < a_1$ 这很显然是不可能的。

最终的 $time_n$ 即为答案，不要忘记全部扫一遍判断是否有解。

```cpp
void solve() {
    int n; cin >> n;
    int k; cin >> k;
    vector<int> A(n + 1);
    rep(i, 1, n) cin >> A[i];
    sort(A.begin() + 1, A.end());
    int it = A[n];
    per(i, n, 1) {
        while((it - A[i]) / k % 2 && it <= A[n] + k) it++; 
        if((it - A[i]) / k % 2 || it >= A[n] + k) return cout << -1 << '\n', void();
    }
    rep(i, 1, n) if((it - A[i]) / k % 2) return cout << -1 << '\n', void();
    cout << it << '\n';
}
```

---

## 作者：Daniel_yao (赞：0)

# Solve

很神奇的一道题。

考虑直接枚举位置 $x$ 为答案，然后对所有 $n$ 个点进行判断。第 $i$ 个点的位置为 $a_i$，若 $a_i$ 合法当且仅当 $x$ 在 $a_i$ 的开灯范围之内，所以若 $\frac{(x-a_i)}{k}$ 为偶数即合法。

还可以缩小一下答案枚举的范围，记 $l,r$ 为答案合法范围。将 $a$ 数组排序，初始来看答案只有可能出现在 $[a_n,a_n+2k-1]$ 这个范围之内，因为存在循环节，后面的所有答案有合法却不是最小的。对于每一个位置 $i$ 都要枚举所有的合法区间，然后对于所有的区间取交集即可。

枚举 $l$ 至 $r$，然后判断合法即可。

时间复杂度 $O((r-l+1)\times n)$，$[l,r]$ 长度期望极小且严格跑不满。可以通过本题。

# Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)

using namespace std;

const int N = 2e5 + 10;

int T, n, k, a[N], ans;

void solve() {
  cin >> n >> k;
  For(i,1,n) cin >> a[i];
  sort(a + 1, a + n + 1);
  int l = a[n], r = a[n] + 2 * k - 1;
  For(i,1,n) {
    for (int j = 0; a[i] + k * j <= r && a[i] + (j + 1) * k - 1 >= l; j += 2) {
      r = min(r, a[i] + (j + 1) * k - 1);
      l = max(l, a[i] + k * j);
    }
  }
  For(i,l,r) {
    For(j,1,n) {
      if(((i - a[j]) / k) % 2 != 0) {
        goto yzy;
      }
    }
    cout << i << '\n';
    return ;
    yzy:;
  }
  cout << "-1\n";
  return ;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> T;
  while(T--) solve();
  return 0;
}
```

---

## 作者：Sorato_ (赞：0)

# CF1993C Light Switches 题解

## 题目大意

有 $n$ 盏灯，第 $i$ 盏灯亮着的时间为 $[a_i+bk,a_i+(b+1)k-1]$，其中 $k$ 为给定常数，$b$ 为任意非负偶数。求一个最小的 $t$，使得在时间 $t$ 所有灯都是亮着的。

## Solve

令 $m=2k$，显然所有灯的开关状态以 $m$ 为周期，所以我们考虑把所有灯的开关状态映射到 $[0,m)$，并求出每个灯映射的偏移量 $d_i$，即需要往前推多少个周期才能把开关状态映射到 $[0,m)$，显然有 $d_i=\lfloor{a_i\over m}\rfloor$，那么映射后，这盏灯开着的区间即为 $[a_i\bmod m,a_i\bmod m+k-1]$。

对于答案，取 $\min\limits_{cnt_t=n}\{t+mx_t\times m\}$，其中 $t=0,1,\dots,m-1$，$cnt_t$ 为在 $t$ 时刻为开着的灯的个数，$mx_t$ 为在 $t$ 时刻为开着的灯的偏移量的最大值。

但有一些细节。考虑有一些灯的开关状态在 $[0,m)$ 内可能是 `11100011` 这样的，$1$ 在两边。这时候左边的 $1$ 的偏移量为 $\lfloor{a_i\over m}\rfloor+1$，右侧的 $1$ 的偏移量为 $\lfloor{a_i\over m}\rfloor$。

至于具体怎么维护 $cnt_t$ 和 $mx_t$，显然可以上数据结构比如线段树，但这里提供一种不用数据结构的方法。

考虑借用扫描线的思想，对于每个 $a_i$，将对应区间左端点的 $cnt$ 加上 $1$，右端点的 $cnt$ 减去 $1$（相当于差分），遍历 $t$ 时前缀和统计即可。而对于 $mx$，考虑在区间左端点插入二元组 $(d_i,1)$，右端点插入二元组 $(d_i,0)$。遍历 $t$ 时，先操作 $t$ 上的所有二元组，开一个 `set`，若二元组第二维是 $1$，则将 $d_i$ 加入，否则删除。那么 $mx_t$ 即为 `set` 的末尾元素。

## Code

```c++
#include<bits/stdc++.h>
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
const int N=2e5+10;
int t,n,k,c[N<<1],ans,m;
struct zzn{int x;bool op;};
vector<zzn>q[N<<1];
multiset<int>s;//注意可能有相等的元素，故需要multiset
signed main()
{
	t=read();
	while(t--)
	{
		n=read();k=read();ans=1e18;m=k<<1;
		s.clear();
		for(int i=0;i<m;i=-~i)	c[i]=0,q[i].clear();
		for(int i=1,a;i<=n;i=-~i)
		{
			a=read();
			c[a%m]++,q[a%m].push_back({a/m,1});
			if(a%m+k<m)
				c[a%m+k]--,q[a%m+k].push_back({a/m,0});
			else//对应上文中 1 在左右两侧的情况
				c[0]++,q[0].push_back({a/m+1,1}),
				c[(a%m+k)%m]--,q[(a%m+k)%m].push_back({a/m+1,0});
		}
		for(int i=0,cnt=0;i<m;i=-~i)
		{
			cnt+=c[i];
			for(zzn j:q[i])
			{
				if(j.op)	s.insert(j.x);
				else	s.erase(s.find(j.x));//相等的元素只删除一个
			}
			if(cnt==n)	ans=min(ans,i+(*--s.end())*m);
		}
		if(ans==1e18)	puts("-1");
		else	printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：EricWan (赞：0)

这题看着很唬人但是当看到 $k\le n$ 就可以知道这题做法了。

先讲一些性质：

+ 答案属于 $\{-1\}\cup[\max_{i=1}^na_i,\max_{i=1}^na_i+2\times k)$，因为在 $\max_{i=1}^na_i$ 时刻后，循环节为 $2\times k$。

+ 在一个循环节内，一个灯只能被调整两次。

然后我们就可以模拟了。

暴力求出在 $\max_{i=1}^na_i$ 时刻时亮的灯的个数，预处理后面的时刻有多少灯关掉，多少灯打开，依次枚举即可。

代码：

```cpp
maxn = lightcnt = 0;
for (int i = 1; i <= 2 * k; i++)
  light[i] = 0;
cin >> n >> k;
for (int i = 1; i <= n; i++) {
  cin >> a[i];
  maxn = max(maxn, a[i]);
}
for (int i = 1; i <= n; i++)
  if ((maxn - a[i]) % (2 * k) < k)
    lightcnt++;
if (lightcnt == n) {
  cout << maxn << endl;
  continue;
}
for (int i = 1; i <= n; i++) {
  int ti = (maxn - a[i] + k - 1) / k * k + a[i];
  if ((ti - a[i]) % (2 * k) == 0)
    light[ti - maxn]++;
  else if ((ti - a[i]) % (2 * k) == k)
    light[ti - maxn]--;
  ti += k;
  if ((ti - a[i]) % (2 * k) == 0)
    light[ti - maxn]++;
  else if ((ti - a[i]) % (2 * k) == k)
    light[ti - maxn]--;
}
for (int i = maxn + 1; i <= maxn + 2 * k; i++) {
  lightcnt += light[i - maxn];
  if (lightcnt == n) {
    cout << i << endl;
    goto END;
  }
}
cout << "-1\n";
END:;
```

---

## 作者：Special_Tony (赞：0)

# 思路
首先找到最后一个首次开灯的灯，在此以后，每 $2k$ 时间以后会回到同样的情况，所以如果第一个 $2k$ 没有相交则以后也没有。我们只要对每个灯找到第一次关灯的时间 $\ge$ 最后一个开灯的灯的时间，然后判断有没有相交即可。
# 代码
```cpp
# include <bits/stdc++.h>
# define I return
# define AK 0
# define IOI ;
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const int inf = 2e9;
int t, n, a[200005], k, maxl, minr, maxx;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> k, maxl = maxx = 0, minr = inf;
		for (int i = 0; i < n; ++ i)
  		cin >> a[i], maxx = max (maxx, a[i]);
		for (int i = 0; i < n; ++ i) {
			const int x = maxx + ((a[i] + k - 1 - maxx) % (2 * k) + 2 * k) % (2 * k);
			maxl = max (maxl, x - k + 1), minr = min (minr, x);
		}
		cout << (maxl > minr ? -1 : maxl) << '\n';
	}
	I AK IOI
}
```

---

