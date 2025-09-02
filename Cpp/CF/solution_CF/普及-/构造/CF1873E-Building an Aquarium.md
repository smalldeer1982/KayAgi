# Building an Aquarium

## 题目描述

You love fish, that's why you have decided to build an aquarium. You have a piece of coral made of $ n $ columns, the $ i $ -th of which is $ a_i $ units tall. Afterwards, you will build a tank around the coral as follows:

- Pick an integer $ h \geq 1 $ — the height of the tank. Build walls of height $ h $ on either side of the tank.
- Then, fill the tank up with water so that the height of each column is $ h $ , unless the coral is taller than $ h $ ; then no water should be added to this column.

 For example, with $ a=[3,1,2,4,6,2,5] $ and a height of $ h=4 $ , you will end up using a total of $ w=8 $ units of water, as shown.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1873E/7c1e58fc4d1641ece42f30c898039b9158eaffda.png)  You can use at most $ x $ units of water to fill up the tank, but you want to build the biggest tank possible. What is the largest value of $ h $ you can select?

## 说明/提示

The first test case is pictured in the statement. With $ h=4 $ we need $ 8 $ units of water, but if $ h $ is increased to $ 5 $ we need $ 13 $ units of water, which is more than $ x=9 $ . So $ h=4 $ is optimal.

In the second test case, we can pick $ h=4 $ and add $ 3 $ units to each column, using a total of $ 9 $ units of water. It can be shown that this is optimal.

In the third test case, we can pick $ h=2 $ and use all of our water, so it is optimal.

## 样例 #1

### 输入

```
5
7 9
3 1 2 4 6 2 5
3 10
1 1 1
4 1
1 4 3 4
6 1984
2 6 5 9 1 8
1 1000000000
1```

### 输出

```
4
4
2
335
1000000001```

# 题解

## 作者：yszkddzyh (赞：9)

### 前置芝士 

二分答案。建议先完成以下题目：

[P1873 砍树](https://www.luogu.com.cn/problem/P1873)，[P2440 木材加工](https://www.luogu.com.cn/problem/P2440)，[P2678 跳石头](https://www.luogu.com.cn/problem/P2678)。

### 题目大意

给出一个正整数数列 $\{a_n\}$，求出最大的 $h$，使得：

$$\sum_{i=1}^n\max(h-a_i,0)\leq x$$

其中，$x$ 是题目所给出的。

### 题目分析

这一道题其实很好看出来是二分答案，尤其是与 [P1873](https://www.luogu.com.cn/problem/P1873) 非常相像。

我们发现，当 $h$ 越小时，$\sum_{i=1}^n\max(h-a_i,0)$ 越小，当 $h$ 越大时，上式越大。所以上式符合单调性，可以使用二分。

我们每次二分时，把 $mid$ 作为 $h$ 带入上式检查，看所得结果是否小于等于 $x$。如果大于，说明 $mid$ 大了，在左边继续找；否则说明 $mid$ 小了，在右半部分找。

### 代码

```cpp
/* 码风良好 */

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 2e5 + 5;
int t, n, x, a[N];

bool check(int h){//检查式子结果是否不超过 x
	ll c = 0;
	for(int i = 1; i <= n; i++)
		if(a[i] < h)
			c += h - a[i];
	return c <= x;
}

int main(){
	
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &x);
		for(int i = 1; i <= n; i++)
			scanf("%d", a + i);
		int l = 1, r = 2e9, mid, ans;
		while(l <= r){
			mid = (r - l >> 1) + l;
			if(check(mid)) l = mid + 1, ans = mid;
			else r = mid - 1;
		}
        //二分推荐写法：记录答案
        //这种写法对于初学者比较好调试
		printf("%d\n", ans);
	}
	
	return 0;
}

/* MADE IN CHINA */
```

---

## 作者：Larryyu (赞：4)

## _Description_
你需要修一个水池，水池的底部高低不一，第 $i$ 格高 $a_i$。

如果修了一个高 $h$ 的水池，会先在两侧修高度为 $h$ 的墙壁防止水溢出，然后对每一格注水：
- 对于第 $i$ 格，需要向其注水 $h-a_i$ 个单位的水，如果 $a_i>h$，则不用注水。
- 水可以有剩余，但不能少，少了就无法修建高度为 $h$ 的水池。

你一共有 $x$ 个单位的水，问 $h$ 最大能是多少。
## _Solution_
先将 $a$ 从小到大排序，如果水面高度已经达到 $a_i$，继续增加 $h$ 有两种情况：
- 加到 $a_{i+1}$，剩余水量 $x$ 减去 $(a_{i+1}-a_i)\times i$，因为前 $i$ 个格子都低于水面，要注水，每格都注了 $a_{i+1}-a_i$ 个单位
- $x$ 不够，加不到 $a_{i+1}$，只能再加 $\lfloor\dfrac{x}{i}\rfloor$ 格

每一次更新 $x$ 即可，注意 $h$ 的初始值是 $a_1$。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,k;
int a[200200];
void solve(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+1+n);
	int sum=0,h=a[1];  //sum是已经用了多少水
	for(int i=2;i<=n;i++){
		int up=min(a[i]-a[i-1],(k-sum)/(i-1));
		sum+=up*(i-1);
		h+=up;
	}
	cout<<h+(k-sum)/n<<endl;
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}	
	return 0;
}

```

---

## 作者：InversionShadow (赞：4)

我们发现答案满足单调性，所以我们考虑二分答案。

我们从 $1 \sim 10^8$ 去二分水池的高度，那么 `check` 函数怎么写呢？

观察题目给出的图片，发现如果 $a_i<mid$，那么他就要补上 $mid-a_i$ 这么多的水，所以我们可以统计 $\sum\limits_{i=1}^n\max(0,mid-a_i)$，然后去跟 $x$ 比较就可以啦！

```cpp
#include <bits/stdc++.h>
#define int unsigned long long

using namespace std;

const int MAXN = 2e5 + 100;

int t, n, x, a[MAXN];
string s;

bool check(int mid) {
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    if (a[i] < mid) {
      sum += mid - a[i];
    }
  }
  return sum  <= x;
}

void solve() {
  cin >> n >> x;
  int maxxa = 0;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  } 
  int l = 1, r = 1e18 + 100, ans = 0;
  while (l <= r) {
    int mid = l + r >> 1;
    //cout << l << ' ' << r << endl;
    if (check(mid)) {
      l = mid + 1; 
    } else {
      r = mid - 1;
    }
  }
  cout << r << endl;
}

signed main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

## 作者：minVan (赞：3)

**题目大意**

给定 $n$ 个柱子，每个柱子的高度为 $a_1,a_2,\cdots,a_n$。现往里头注入不大于 $x$ 的水，对于每个单位的水，如果它两边的柱子高度比它矮，它将会流下去。

问水的最低深度的最大值 $h$。

**解题思路**

比赛时一看这题，就觉得是个二分题。

由于水量不超过 $x$，所以 $h$ 一定小于 $\max\limits_{i\in [1,n]}\{a_i\}+x$。从而把 $h$ 在 $[1,\max\limits_{i\in [1,n]}\{a_i\}+x]$ 中二分即可。

判断函数如下：

```cpp
inline bool check(int xx) {
  int cnt = 0;
  for(int i = 1; i <= n; i++) {
    cnt += (a[i] < xx ? xx - a[i] : 0);
  }
  return cnt <= x;
}
```

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, x, a[N];
inline bool check(int xx) {
  int cnt = 0;
  for(int i = 1; i <= n; i++) {
    cnt += (a[i] < xx ? xx - a[i] : 0);
  }
  return cnt <= x;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    int maxi = -1, ans = 0;
    cin >> n >> x;
    for(int i = 1; i <= n; i++) {
      cin >> a[i];
      maxi = max(maxi, a[i]);
    }
    int l = 1, r = maxi + x;
    while(l <= r) {
      int mid = (l + r) >> 1;
      if(check(mid)) {
        ans = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
```

---

## 作者：YangXiaopei (赞：2)

这一道题其实很好看出来是二分答案我们发现，当 $h$ 越小时，$\sum \limits_{i = 1} ^ n \max(h - a_i, 0)$ 越小，当 $h$ 越大$\sum \limits_{i = 1} ^ n \max(h - a_i, 0)$ 越大。

所以答案满足单调性，所以我们可以二分答案。

先看 $h$ 的范围。

在理论上，$h$ 最大可以到 $\max\limits_{i = 1} ^ n a_i + x$，可以直接看成 $2 \times 10 ^ 9$。

接下来就是简单的二分了。

在 `check` 中，每次让 $sum$ 去加上 $\max(h - a_i, 0)$，最后判断是否小于等于 $x$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, x, a[200005];
bool check(int mid){
	int sum = 0;
	for(int i = 1; i <= n; i++){
		sum += max(0ll, mid - a[i]);
	}
	return sum <= x;
}
signed main(){
    cin >> t;
    while(t--){
    	cin >> n >> x;
    	for(int i = 1; i <= n; i++){
    		cin >> a[i]; 
		}
		int l = 0;
		int r = 2e9 + 1;
    	int mid;
	    while(l < r){
	        mid = (l + r) / 2;
	        if(check(mid)){
	            l = mid + 1;
	        }
	        else{
	            r = mid - 1;
	        }
	    }
	    if(!check(l)){
	    	l--;
		}
	    cout << l << "\n";
	}
    return 0;
}
```

---

## 作者：igAC (赞：2)

# $\text{Description}$

[洛谷 link](https://www.luogu.com.cn/problem/CF1873E)

[CFlink](https://codeforces.com/problemset/problem/1873/E)

简要题意：

给定 $n,k$ 和一个长度为 $n$ 的序列 $a$。

求最大的 $h$ 使得 $k \ge \sum_{i=1}^{n}\max(0,h-a_i)$。

# $\text{Solution}$

简单二分，要注意右边界的答案是否会爆 ``long long``。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int T,n,k,a[N];
bool check(int h){
	int res=0;
	for(int i=1;i<=n;++i) res+=max((int)0,h-a[i]);
	return res<=k;
}
void solve(){
	n=read(),k=read();
	for(int i=1;i<=n;++i) a[i]=read();
	int l=1,r=1e10,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1,ans=mid;
		else r=mid-1;
	}
	printf("%lld\n",ans);
}
signed main(){
	T=read();
	while(T--) solve();
	return 0;
}
```

---

## 作者：xuchuhan (赞：2)

## 题意

给你两个数 $n,x$ 和一个序列 $a_1,a_2,...,a_n$，请求出最大的 $h$，使得 $\sum\limits_{i=1}^n \max(h-a_i,0)$ 不超过 $x$。

## 思路

本题需要使用的算法是二分。但我们需要思考一个问题，我们是如何想到用二分解决此题的？

- 题目想让我们求最大值的最小值，典型的二分描述；

- 题目中 $n$ 的取值范围是 $10^5$ 的级别的，需要用时间复杂度在 $\mathcal{O(n \log n)}$ 及以下的算法解决，而二分答案刚好满足此条件；

- 同时，本题的答案会随着 $h$ 的增大越来越大，满足单调性，故考虑二分。

## 实现

二分时把所求到的 $mid$ 代入去算一遍，如果得到的答案不大于 $x$，就把左端点变大，同时记录答案，否则把右端点变小。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,x;
int a[N];
bool check(int mid){
	//带入去算
	int sum=0;
	for(int i=1;i<=n;i++)
		sum=sum+max(0LL,mid-a[i]);
	return sum<=x;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int ans=0;
		int l=1;
		int r=INT_MAX;
		while(l<=r){
			int mid=(l+r)/2;
			if(check(mid))
				l=mid+1,ans=mid;//合法
			else
				r=mid-1;//不合法
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：ArcherHavetoLearnWhk (赞：1)

### 题意

给定 $n$，$x$ 以及序列 $\{a_n\}$，令 $sum=\sum_{i=1}^n{\max(h-a_i,0)}$，求最大 $h$ 使得 $sum \le x$。

### 思路

如果暴力枚举 $h$ 肯定会超时。

我们发现，$h$ 增大，$sum$ 就会增大或不变，不会减少，符合单调性，于是想到二分答案。

每次用 $mid$ 作为 $h$ 算出 $sum$，并和 $x$ 进行比较，这样调整 $l$ 和 $r$，最后得到 $r$ 为答案。

每次遍历算 $sum$ 用 $\Theta(n)$，二分设定右边界为 $r$（$r$ 大概设到 $10^{10}$ 左右即可，不要太大，$10^9$ 也不够），$t$ 组数据，总共 $\Theta(t\cdot n \log r)$。

### 代码

记得开 `long long` 并注意设置好右边界范围。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200005],x;
bool check(long long m){
	long long sum=0;
	for(int i=1;i<=n;i++)
		if(m>a[i])sum+=m-a[i];
	return sum<=x;
}
int main(){
	cin>>t;
	while(t--){
		cin>>n>>x;
		for(int i=1;i<=n;i++)cin>>a[i];
		long long l=0,r=0x3f3f3f3f3f;
		while(l<=r){
			long long mid=(l+r)>>1;
			if(check(mid))l=mid+1;
			else r=mid-1;
		}
		cout<<r<<'\n';
	}
	return 0;
}
```


---

## 作者：phigy (赞：0)

我们要找到一个最大的 $h$ 使得 $\sum_{i=1}^n \max\{0,h-a_i\}\leq x$。

可以发现这个和是一定随 $h$ 增大而增大的。

因此我们可以考虑二分 $h$，并检验是否满足要求。

```cpp
#include <iostream>

#define int long long

using namespace std;

int T;
int n;
int c[2000005];
signed main()
{
    int i,j,k;
    cin>>T;
    while(T--)
    {
        int ans=0;
        cin>>n>>k;
        for(i=1;i<=n;i++)
        {
            cin>>c[i];
        }
        int l=0,r=2000000005;
        while(l+1<r)
        {
            int res=0;
            int mid=(l+r)/2;
            for(i=1;i<=n;i++)
            {
                res+=max((long long)0,mid-c[i]);
            }
            if(res<=k)
            {
                l=mid;
            }
            else
            {
                r=mid-1;
            }
        }
        int res=0;
        int mid=l+1;
        for(i=1;i<=n;i++)
        {
            res+=max((long long)0,mid-c[i]);
        }
        if(res<=k)
        {
            l=mid;
        }
        res=0;
        mid=l+1;
        for(i=1;i<=n;i++)
        {
            res+=max((long long)0,mid-c[i]);
        }
        if(res<=k)
        {
            l=mid;
        }
        res=0;
        mid=l+1;
        for(i=1;i<=n;i++)
        {
            res+=max((long long)0,mid-c[i]);
        }
        if(res<=k)
        {
            l=mid;
        }
        cout<<l<<endl;
    }
    return 0;
}
```


---

## 作者：Natori (赞：0)

>[CF1873E Building an Aquarium](https://www.luogu.com.cn/problem/CF1873E)

二分答案板题。

------------
假设当前墙壁高度为 $x$，那么水需要填充 $a_i<x$ 的所有位置，代价就是这些位置的代价之和。

二分 $x$ 并判断即可，时间复杂度 $\mathcal{O}(n \log V)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
const int N=2e5+8;
int n,m,a[N],suma[N];
bool check(int x){
	int res=0;
	for(int i=1;i<=n;i++)
		if(a[i]<x)
			res+=x-a[i];
	return res<=m;
}
void solve(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	int l=0,r=1e12+8,ans;
	for(int i=1;i<=50;i++){
		int mid=(l+r)/2;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	write(ans),putchar('\n');
}
bool Mend;
signed main(){
//	File_Work();
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	int testnum=read();
	while(testnum--)
		solve();
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
/*
3
4 1
1 4 3 4
7 9
3 1 2 4 6 2 5
1 1000000000
1000000000
*/
```

---

