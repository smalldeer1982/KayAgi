# Colors

## 题目描述

Linda likes to change her hair color from time to time, and would be pleased if her boyfriend Archie would notice the difference between the previous and the new color. Archie always comments on Linda's hair color if and only if he notices a difference — so Linda always knows whether Archie has spotted the difference or not.

There is a new hair dye series in the market where all available colors are numbered by integers from $ 1 $ to $ N $ such that a smaller difference of the numerical values also means less visual difference.

Linda assumes that for these series there should be some critical color difference $ C $ ( $ 1 \le C \le N $ ) for which Archie will notice color difference between the current color $ \mathrm{color}_{\mathrm{new}} $ and the previous color $ \mathrm{color}_{\mathrm{prev}} $ if $ \left|\mathrm{color}_{\mathrm{new}} - \mathrm{color}_{\mathrm{prev}}\right| \ge C $ and will not if $ \left|\mathrm{color}_{\mathrm{new}} - \mathrm{color}_{\mathrm{prev}}\right| < C $ .

Now she has bought $ N $ sets of hair dye from the new series — one for each of the colors from $ 1 $ to $ N $ , and is ready to set up an experiment. Linda will change her hair color on a regular basis and will observe Archie's reaction — whether he will notice the color change or not. Since for the proper dye each set should be used completely, each hair color can be obtained no more than once.

Before the experiment, Linda was using a dye from a different series which is not compatible with the new one, so for the clearness of the experiment Archie's reaction to the first used color is meaningless.

Her aim is to find the precise value of $ C $ in a limited number of dyes. Write a program which finds the value of $ C $ by experimenting with the given $ N $ colors and observing Archie's reactions to color changes.

## 说明/提示

Comments to the example input line by line:

1. $ N = 7 $ .
2. Answer to the first query is meaningless (can also be $ 0 $ ).
3. $ C \leq 5 $ .
4. $ 3 < C \leq 5 $ . It would be wise to check difference $ 4 $ . However, this can not be done in the next query since $ 4 + 4 = 8 $ and $ 4 - 4 = 0 $ both are outside the allowed interval $ 1 \le P \le 7 $ .
5. $ 3 < C \leq 5 $ .
6. $ 3 < C \leq 4 $ . Therefore, $ C = 4 $ .

## 样例 #1

### 输入

```
1

7

1

1

0

0

1```

### 输出

```
? 2

? 7

? 4

? 1

? 5

= 4```

# 题解

## 作者：zyh_helen (赞：2)

这题好难。

---
---

首先常规二分的难点在于长度较长时在 $[1,n]$ 中难以放入一个区间。

简单的思路是可以左右横跳（雾

![](https://cdn.luogu.com.cn/upload/image_hosting/p6fi3py2.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

所以我们需要找到一个合适的点，从这个点向左向右交替查询来二分。

---

找到这个点，可以逆序考虑。

对我们来说，这个点每次跳跃的距离会有两种情况：
- 缩小至原来 $\frac{1}{2}$，显然不会跳出边界；
- 扩大至原来 $\frac{3}{2}$，我们可以预处理出每次跳跃的距离，倒序找到初始点，便一定不会跳出边界。

---

找到这个点后直接常规二分即可，只用注意每次都要朝着与上次相反的方向跳。

---
---

```cpp
#include<bits/stdc++.h>
#define int long long
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 2e6 + 10, M = 7001, inf = 1e12, mod = 998244353;
const double eps = 1e-8, pi = 3.1415926;
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/

//int head[N], tot;
//struct edge{
//	int t;
//	int next;
//}e[N << 1];
//void edge_add(int u, int v){
//	e[++tot].next = head[u];
//	e[tot].t = v;
//	head[u] = tot;
//}
//int qmr(int x, int a){
//	x %= mod;
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}

int n, a[N];
int ask(int x){
	printf("? %lld\n", x);
	fflush(stdout);
	int y;
	scanf("%lld", &y);
	return y;
}
signed main(){
	int t;
	cin >> t;
	while(t--){
		cin >> n;
		int l = 0, r = n, st = 0, f = 1;
		vector<int>s;
		while(r - l > 1){
			l = (l + r) / 2;
			s.push_back(l);
		}
		for(int i = s.size() - 1;~i;i--)st += s[i] * f, f = -f;
		l = 0;
		ask(st + 1);
		while(r - l > 1){
			int y = l + r >> 1;
			st += f * y;
			f = -f;
			if(ask(st + 1))r = y;
			else l = y;
		}
		printf("= %lld\n", r);
		fflush(stdout);
	}
	return 0;
}

---

## 作者：Inui_Sana (赞：0)

挺简单的交互题。不知道为什么这题评了 *2700。

题解双倍经验。（bushi）

首先显然是要二分答案然后用交互 check 的。我们先尝试从 $P=1$ 开始是否可行。容易发现，如果得到 $ans>mid$，$P$ 此时原本在 $\dfrac{n}{2}$ 左右，而第二次我们要找到一个 $P'$ 使得 $|P'-P|\approx \dfrac{3n}{4}$。这显然是无解的。

不过这也启示我们应该从每次跳的距离都最大的情况去考虑，如何找到一个合法的起点。

因为极端情况下 $mid$ 不断变大，于是倒序考虑，先确定终点在 $1$，处理出每次的 $mid$，在数轴上考虑，每次先往右再往左跳。跳完所有的 $mid$ 时在的位置就是我们要的起点。

此时就会有一个问题：会不会向左/右的空间不够导致奇怪的 $P$ 的重复呢？其实是不会的，因为容易发现每次就相当于把一个区间不断缩小，直到区间长度 $=\dfrac{n}{2}$。

于是我们就可以想出这么一种构造：从这个起点开始，二分同时依次向左向右跳（根据上面处理起点时的相反顺序来）。

然后又有一个问题了：这样会不会重复？感性理解一下是不会的，有具体证明可以敲敲我。

code：

```cpp
ll n,m,a[107];
il ll ask(ll x,int op){
	if(op){
		printf("= %lld\n",x);
		fflush(stdout);
		return 0;
	}
	printf("? %lld\n",x);
	fflush(stdout);
	ll y;scanf("%lld",&y);
	return y;
}
void Yorushika(){
	scanf("%lld",&n),m=0;
	ll l=1,r=n-1;
	while(l<=r){
		ll mid=(l+r)>>1;
		a[++m]=mid,l=mid+1;
	}
	reverse(a+1,a+m+1);
	ll p=1;
	rep(i,1,m){
		if(i&1){
			p+=a[i];
		}else{
			p-=a[i];
		}
	}
	ll x=ask(p,0);
	l=1,r=n-1;
	ll ans=n,cnt=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		cnt++;
		if(abs(m-cnt)&1){
			x=ask(p+=mid,0);
		}else{
			x=ask(p-=mid,0);
		}
		if(x){
			ans=mid;
			r=mid-1;
		}else{
			l=mid+1;
		}
	}
	ask(ans,1);
}
signed main(){
	int t=1;
		scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

