# Scuza

## 题目描述

Timur has a stairway with $ n $ steps. The $ i $ -th step is $ a_i $ meters higher than its predecessor. The first step is $ a_1 $ meters higher than the ground, and the ground starts at $ 0 $ meters.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1742E/1bd007a2ef6a288af14a4e7592f626054d160b81.png)The stairs for the first test case.Timur has $ q $ questions, each denoted by an integer $ k_1, \dots, k_q $ . For each question $ k_i $ , you have to print the maximum possible height Timur can achieve by climbing the steps if his legs are of length $ k_i $ . Timur can only climb the $ j $ -th step if his legs are of length at least $ a_j $ . In other words, $ k_i \geq a_j $ for each step $ j $ climbed.

Note that you should answer each question independently.

## 说明/提示

Consider the first test case, pictured in the statement.

- If Timur's legs have length $ 1 $ , then he can only climb stair $ 1 $ , so the highest he can reach is $ 1 $ meter.
- If Timur's legs have length $ 2 $ or $ 4 $ , then he can only climb stairs $ 1 $ , $ 2 $ , and $ 3 $ , so the highest he can reach is $ 1+2+1=4 $ meters.
- If Timur's legs have length $ 9 $ or $ 10 $ , then he can climb the whole staircase, so the highest he can reach is $ 1+2+1+5=9 $ meters.

 In the first question of the second test case, Timur has no legs, so he cannot go up even a single step. :(

## 样例 #1

### 输入

```
3
4 5
1 2 1 5
1 2 4 9 10
2 2
1 1
0 1
3 1
1000000000 1000000000 1000000000
1000000000```

### 输出

```
1 4 4 9 9 
0 2 
3000000000```

# 题解

## 作者：szhqwq (赞：7)

## 题目大意

给你 $n$ 个 $a_i$，表示当前这一阶楼梯与上一阶楼梯的高度差，再给你 $q$ 个 $k$，表示腿长，到下一阶楼梯的条件是 $k \le a_i$，问你能到达多少高度。

## 分析

这道题如果我们正常遍历 $a_i$ 来判断最高能到达的高度，则时间复杂度为 $O(Tqn)$，但是 $1 \le n,q \le 2 \times 10^5$ 如果这个时间复杂度的话会 TLE。

所以我们需要考虑优化。仔细阅读题目你会发现：因为 $1 \le a_i \le 10^9$，所以将每个楼梯的实际高度计算出来是**单调不递减**的，那么，我们就可以考虑二分。

二分的时间复杂度为 $O(Tq \log n)$，不会超时，那么我们就可以每一次去二分查找那个最高能到达的高度，利用前缀和预处理即可。

AC code

```cpp
#include <bits/stdc++.h>

#define int long long

using namespace std;

const int N = 2e5 + 10;

int n,q;
int a[N],s[N]; // 注意此处a数组是用来判断是否可以到达下一阶楼梯的

inline int read() { int x; cin >> x; return x; }

signed main() {
	int T;
	cin >> T;
	while (T --) {
		n = read(); q = read();
		for (int i = 1; i <= n; i ++ ) {
			int x = read();
			a[i] = max(a[i - 1],x);// 如果x还没有上一阶的高度高，那么一定能到达这一阶楼梯
			s[i] = s[i - 1] + x;
		}
		while (q --) {
			int k = read();
			int l = 0,r = n + 1;
			while (l < r) {
				int mid = l + r >> 1;
				if (a[mid] <= k) l = mid + 1;
				else r = mid;
			}
			cout << s[l - 1] << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：CQ_Bab (赞：3)

# 前言
~~个人认为这道题还是挺水的，毕竟本蒟蒻都做出来了~~。这道题只需要你学会前缀和与二分即可。
# 思路
知道题我们用一个前缀和数组来统计 $1\sim i$ 的和（便于最后输出），然后存下从 $1\sim i$ 的最大跨度，存下最大跨度好判断是否可以到达。这是你会发现楼梯跨度一定是非负数那么它的前缀和就一定具有单调性那么就能想到二分了，所以我们只需要用二分去枚举出当最大跨度为 $q$ 时最大能跨到哪然后输出到 $l$ 的前缀和即可。
# 代码
比赛代码，码风丑，请见谅！
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q;
int a[200100],pre[200100];
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>q;
		for(int i=1;i<=n;i++) {
			int x;
			cin>>x;
			a[i]=max(a[i-1],x); //存下从 1到i 的最大跨度（便于二分）
			pre[i]=pre[i-1]+x; //前缀和（便于输出）
		}
		while(q--) {
			int k;
			cin>>k;
			int l=0,r=n;
			while(l<=r) { //二分模板
				int mid=l+r>>1;
				if(a[mid]>k) r=mid-1;//判断是否可以跨过去
				else l=mid+1;
			}
			cout<<pre[l-1]<<" ";//输出
		}
		puts("");
	}
	return false; //又AC了
}

```


---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF1742E)

说实在的这翻译翻的是什么玩意！

这一道题水模拟，但要开 long long。这道题可以先求 $a_i$ 的前缀和，求出所有楼梯的高度，并且用 $a$ 数组存改楼梯需要多大的腿长才能爬到。最后再二分查找一下答案就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,q,a[200010]={0},v[200010]={0},k[200010]={0},x;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		long long maxx=-1;
		scanf("%lld%lld",&n,&q);
		for(register int i=1;i<=n;i++)
		{
			scanf("%lld",&x),v[i]=v[i-1]+x;
			if(maxx<x) maxx=x,a[i]=x;
			else a[i]=maxx;
		}
		a[n+1]=9999999999;
		for(register int i=1;i<=q;i++) scanf("%lld",&k[i]);
		for(register int i=1;i<=q;i++)
		{
			long long l=0,r=n+1;
			while(l<r)
			{
				long long mid=(l+r)/2;
				if(a[mid]<=k[i]) l=mid+1;
				else r=mid;
			}
			printf("%lld ",v[l-1]);
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：hu_led (赞：1)

## 题意简述
$t$ 组数据，对于每组数据：

有 $n$ 级台阶，每级台阶比上一级高 $a_i$ 米。有 $q$ 次询问，每次询问给出一个腿长 $k$,问在每次跨上的高度不大于腿长 $k$ 的前提下最多能走到的高度。
## 思路
要想到达第 $i$ 级台阶，就必须要先走过前 $i-1$级台阶，可见台阶第 $i$ 级可以到达的限制条件是： $k\geqslant \max\{a_j\}(1\leqslant j\leqslant i)$。

该限制条件是单调不下降的，即每一级台阶要想到达的最小的 $k\geqslant$ 它前面的每一级的最小的 $k$。那么我们可以先预处理到达每一级所需的最小的 $k$，每次询问的时候二分查找最多到哪个台阶，再用个前缀和算出高度即可。

时间复杂度：$O(tqlogn)$。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 200010
using namespace std;
int t,q,n,a[MAXN],k,cnt;
int re[MAXN],sum[MAXN];
signed main()
{
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld%lld",&n,&q);
		cnt=0;
		memset(re,0,sizeof(re));
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]),re[i]=max(re[i-1],a[i]),sum[i]=sum[i-1]+a[i];
		for(int i=1;i<=q;i++)
		{
			scanf("%lld",&k);
			int l=0,r=n+1;
			while(l<r)
			{
				int mid=(l+r)>>1;
				if(re[mid]<=k)l=mid+1;
				else r=mid;
			}
			printf("%lld ",sum[l-1]);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：AlicX (赞：0)

### 题目大意

给你 $n$ 个 $a_i$，表示这级台阶和上级台阶的高度差，再给你 $q$ 个 $k$，表示你的腿长，如果你的腿长足够跨过这级台阶，那么继续走。问最终能到达的最高高度。

## 思路

要想到达 $i$ 这级台阶，显然是需要跨过前 $i-1$ 级台阶，手动模拟样例你会发现这个条件保证了一个非常重要的性质——那就是答案是递增的。通过递增这条性质，我们就可以联想到二分，没错，每次二分判断这个高度是不是可行的，最后输出即可。

## AC Code
```cpp

#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+10;
int n,k;
int a[N];
int cnt=0;
int s[N],t[N];
map<int,int> mp;
struct Node{
	int l,r;
}tr[N];
inline int query(int x){
	if(x<a[1]) return 0;
	int d=0;
	int l=1,r=cnt;
	while(l<=r){
		int mid=l+r>>1;
		if(tr[mid].l<=x&&x<=tr[mid].r){
			d=mid;
			break;
		}
		if(tr[mid].l>x) r=mid-1;
		else if(tr[mid].r<x) l=mid+1;
	}
//	cout<<d<<" ";
	return mp[d];
}
signed main(){
// 	freopen("E.in","r",stdin);
// 	freopen("E.out","w",stdout);
	int T;
	cin>>T;
	while(T--){
		cnt=0,mp.clear();
		memset(s,0,sizeof s);
		memset(t,0,sizeof t);
		memset(tr,0,sizeof tr);
		cin>>n>>k;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++) t[i]=t[i-1]+a[i],s[i]=max(s[i-1],a[i]);
		for(int i=1,j;i<=n;i=j){
			j=i+1;
			while(j<=n&&s[i]==s[j]) j++;
			int p=s[j]-1;
			if(j>n) p=1e9+7;
			tr[++cnt]={s[i],p},mp[cnt]=t[j-1];
		}
//		for(int i=1;i<=cnt;i++) cout<<tr[i].l<<" "<<tr[i].r<<endl;
		while(k--){
			int x;
			cin>>x;
			cout<<query(x)<<" ";
//			cout<<endl;
		}
		cout<<endl;
	}
	return 0;
}/*
1
4 5
1 2 1 5
1 2 4 9 10

3
4 5
1 2 1 5
1 2 4 9 10
2 2
1 1
0 1
3 1
1000000000 1000000000 1000000000
1000000000
*/
```


---

## 作者：Symbolize (赞：0)

# 思路
这题暴力显然会超时，那我们需要优化时间复杂度，我们会发现一个特点，判断能否到达这一级台阶的前提肯定是能通过上一级，这就说明能上的级数具有单调性，所以用二分答案来优化。

二分能到达的级数，用一个 $x$ 数组来存放截止 $i$。与前一级台阶高度差最大的高度差的值。二分判断输入的 $k$ 是否大于等于这个值。答案可以用前缀和来记录。

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e6+10;
using namespace std;
int t,n,q,a,x[N],s[N];
void getans()
{
	cin>>n>>q;
	rep1(i,1,n)
	{
		cin>>a;
		x[i]=max(x[i-1],a);
		s[i]=s[i-1]+a;
	}
	while(q--)
	{
		cin>>a;
		int l=0,r=n+1;
		while(l<r)
		{
			int mid=l+r>>1;
			if(x[mid]<=a) l=mid+1;
			else r=mid;
		}
		cout<<s[l-1]<<' ';
	}
	putchar('\n');
	memset(s,0,sizeof s);
	memset(x,0,sizeof x);
	return;
}
signed main()
{
	cin>>t;
	while(t--) getans();
	return 0;
}
```

---

## 作者：WaterSun (赞：0)

2022/11/23：修改了一下代码。

# 题意

有 $T$ 组数据，每次给出一个 $n,q$，表示台阶的数量和询问的次数。

然后再给出一个 $a_i$ 为台阶高度的差分数组。

每次询问给出一个 $k$，表示每次能走 $k$ 个单位的高度。

问：最高能到达的高度。

# 思路

考虑暴力，我们知道了高度的差分数组，那么我们就可以直接算出当前的高度。然后，直接暴力即可。

但是，这样的时间复杂度是不对的，为：$O(Tqn)$ 的，显然会超时，那么我们只有想一想优化了。

因为对于每一个 $a_i$，$1 \leq a_i$ 的，所以，我们的高度是单调递增的。因此，我们可以用二分的方法来优化。

我们可以用一个数组 $c$ 维护 $a_1 \sim a_i$ 最大值，因为我们的操作中，如果你能走到 $i$，那么你一定能走过 $1 \sim i$ 的台阶，而对我们最有限制的便是 $\max(a_i)$。

最后，再来分析一下时间复杂度为：$O(Tq\log n)$ 的，不会超时。

# code

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2e5 + 10;
int T,n,q,k;
int arr[N],c[N],s[N];

inline int read(){
	int r = 0,w = 1;
	char c = getchar();
	while (c < '0' || c > '9'){
		if (c == '-') w = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9'){
		r = (r << 3) + (r << 1) + (c ^ 48);
		c = getchar();
	}
	return r * w;
}

signed main(){
	T = read();
	while (T--){
		n = read();
		q = read();
		for (int i = 1;i <= n;i++){
			arr[i] = read();
			c[i] = max(c[i - 1],arr[i]);//max(a[i]) 
			s[i] = s[i - 1] + arr[i];//差分数组的前缀和就为当前的值 
		}
		while (q--){
			k = read();
			int l = 0,r = n;//二分板子 
			while (l <= r){
				int mid = l + r >> 1;
				if (c[mid] > k) r = mid - 1;//重点 
				else l = mid + 1;
			}
			printf("%lld ",s[l - 1]);//输出 
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：HNOIRPplusplus (赞：0)

## 题意
+ 你有一堆台阶，每一个比上一个高 $a_i$（而并不是台阶本身高 $a_i$）。  
+ 你每次可以往上爬 $k$ 的高度。
+ 求可以爬多少个台阶。

## 部分分
显然可以直接依照题目模拟。每次往上爬 $k$ 格，再把高度差加起来输出就可以了。  
虽然这个题目限时 $3s$，但是我们不能因此就使用 $O(nq)$ 的做法。  
喜提 [Time limit exceeded on test 9](https://codeforces.com/contest/1742/submission/178291214) 一个。（但是洛谷上是[UKE](https://www.luogu.com.cn/record/91997558)）

## 正解
因此，我们不可能使用超级慢的遍历查找，所以我们应该使用更快的[二分查找](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE/10628618)。  
每一次算高度差的和也太浪费了，干脆换成前缀和好了。  
现在算法的时间复杂度降到了 $O(q\log{n})$，通过这道题绰绰有余。  
### 为什么可以用二分
我们如果有一个台阶上不去，那么上面的台阶无论怎么平缓也没有用。  
所以，我们到达每一个台阶所需要的 $k$ 其实是单调不递减的！  
只要在每个测试点前面处理一下就可以轻轻松松的通过本题。

## 代码
```
#include <iostream>

using namespace std;

const int N = 200005;

int a[N], f[N];
long long sum[N];

int main() {
  int t;
  cin >> t;
  while(t--) {
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
      f[i] = max(f[i - 1], a[i]);
      sum[i] = sum[i - 1] + a[i];
    }
    while(q--) {
      int k;
      cin >> k;
      int l = 0, r = n + 1;
      while(l < r) {
        int mid = (l + r) >> 1;
        if(f[mid] <= k) {
          l = mid + 1;
        } else {
          r = mid;
        }
      }
      cout << sum[l - 1] << ' ';
    }
    cout << '\n';
  }
  return 0;
}
```
[AC 1.32s 3.07MB](https://www.luogu.com.cn/record/92000204)

#### 能不能再加把火？
当然能！用上STL中的 `upper_bound`，加上快读快写，再把O2打开你就无敌了！[AC 249ms 3.07MB](https://www.luogu.com.cn/record/92001996)  
诚然，算前缀和的同时，可以直接将 $a$ 数组处理成二分查找能用的数组，还请大家自己尝试一下。

---

## 作者：Allanljx (赞：0)

## 思路
记录一个前缀和和前缀最大值 $qz_i$，想到达台阶 $i$ 当且仅当 $k\geq qz_i$。所以每次询问时二分答案来找出最大的 $i$。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,q;
int a[200005];
int qz[200005];
int qz1[200005];
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		cin>>n>>q;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			qz[i]=max(qz[i-1],a[i]);
			qz1[i]=qz1[i-1]+a[i];
		}
		for(int i=1;i<=q;i++)
		{
			int k;
			cin>>k;
			int l=0,r=n,ans=0;
			while(l<=r)
			{
				int mid=(l+r)/2;
				if(qz[mid]>k) r=mid-1;
				else l=mid+1,ans=mid;
			}
			cout<<qz1[ans]<<' ';
		}
		cout<<endl;
	}
}
```

---

## 作者：小明小红 (赞：0)

# CF1742E题解

这道题不简单，要用很多思路。

**思路**：用 $s_i$ 来记录走到每个台阶所需要的腿长。查询是用二分 $O(   \log n)$ 查询输入的长度可以走到哪。

# code
```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll T,a,b,s[200009],c,sum[200009];
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>a>>b;
		memset(s,0,sizeof(s));
		memset(sum,0,sizeof(sum));//初始化 
		for(ll i=1;i<=a;i++)//输入+预处理 
		{
			cin>>c;
			s[i]=max(c,s[i-1]);//记录每级所需腿长 
			sum[i]=sum[i-1]+c;//前缀和 
		}
		for(ll i=1;i<=b;i++)//查询 
		{
			cin>>c;
			ll l=0,r=a+1;
			while(l<r)
			{
				ll mid=(l+r)/2;
				if(s[mid]<=c)
				{
					l=mid+1;
				}
				else
				{
					r=mid;
				}
			}
			cout<<sum[l-1]<<' ';//一定要减一，上面的二分是取不到的最小 
		}
		cout<<endl;
	}
	return 0; 
}
```


---

