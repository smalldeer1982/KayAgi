# Integers Shop

## 题目描述

The integers shop sells $ n $ segments. The $ i $ -th of them contains all integers from $ l_i $ to $ r_i $ and costs $ c_i $ coins.

Tomorrow Vasya will go to this shop and will buy some segments there. He will get all integers that appear in at least one of bought segments. The total cost of the purchase is the sum of costs of all segments in it.

After shopping, Vasya will get some more integers as a gift. He will get integer $ x $ as a gift if and only if all of the following conditions are satisfied:

- Vasya hasn't bought $ x $ .
- Vasya has bought integer $ l $ that is less than $ x $ .
- Vasya has bought integer $ r $ that is greater than $ x $ .

Vasya can get integer $ x $ as a gift only once so he won't have the same integers after receiving a gift.

For example, if Vasya buys segment $ [2, 4] $ for $ 20 $ coins and segment $ [7, 8] $ for $ 22 $ coins, he spends $ 42 $ coins and receives integers $ 2, 3, 4, 7, 8 $ from these segments. He also gets integers $ 5 $ and $ 6 $ as a gift.

Due to the technical issues only the first $ s $ segments (that is, segments $ [l_1, r_1], [l_2, r_2], \ldots, [l_s, r_s] $ ) will be available tomorrow in the shop.

Vasya wants to get (to buy or to get as a gift) as many integers as possible. If he can do this in differents ways, he selects the cheapest of them.

For each $ s $ from $ 1 $ to $ n $ , find how many coins will Vasya spend if only the first $ s $ segments will be available.

## 说明/提示

In the first test case if $ s = 1 $ then Vasya can buy only the segment $ [2, 4] $ for $ 20 $ coins and get $ 3 $ integers.

The way to get $ 7 $ integers for $ 42 $ coins in case $ s = 2 $ is described in the statement.

In the second test case note, that there can be the same segments in the shop.

## 样例 #1

### 输入

```
3
2
2 4 20
7 8 22
2
5 11 42
5 11 42
6
1 4 4
5 8 9
7 8 7
2 10 252
1 11 271
1 10 1```

### 输出

```
20
42
42
42
4
13
11
256
271
271```

# 题解

## 作者：qfpjm (赞：6)

# 题解

- 考虑贪心。

- 显然，我们每次只需要包含当前左端点最左的区间和右端点最右的两个或是一个区间。我们不关心其长度，只关心这个区间是否包含当前两个端点，且价钱最低。

- 当然我们不能直接每次暴力排序，我们可以每次更新两个区间的价格。因为有当前区间包含整个区间的情况，我们再用一个变量记录。最后取两个区间价格之和与一个区间包含的情况的较小值即可。

# 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int T;

int main()
{
	cin >> T;
	while (T --)
	{
		int n;
		cin >> n;
		int l = INT_MAX, r = 0;
		int lans = INT_MAX, rans = INT_MAX, ans = INT_MAX;
		for (int i = 1 ; i <= n ; i ++)
		{
			int li, ri, ci;
			cin >> li >> ri >> ci;
			if (l > li)
			{
				l = li;
				lans = ci;
				ans = INT_MAX;
			}
			if (l == li)
			{
				lans = min(lans, ci);
			}
			if (r < ri)
			{
				r = ri;
				rans = ci;
				ans = INT_MAX;
			}
			if (r == ri)
			{
				rans = min(rans, ci);
			}
			if (li == l && ri == r)
			{
				ans = min(ans, ci);
			}
			cout << min(ans, lans + rans) << endl;
		} 
	}
	return 0;
}

```


---

## 作者：XL4453 (赞：1)

### $\text{Difficulty : 1500}$

---
### 解题思路：

考虑区间 $[a,b]$，如果位置 $a$ 和位置 $b$ 都被买了，那么一整个区间都可以送。

而题目要求的是优先保证买到的整数数量多，所最左端和最右端的两个值都一定需要购买。一种可能的情况是两个端点都买，否则就是一整个区间都通过某一个套餐买。

那么直接统计最左端和最右端的两个位置，如果出现了一个新的值使得其能够拓展，则之前的整个区间购买方案无效，且当前的这个使区间拓展的套餐一定要买。如果恰好拓展到要买的位置，则将这个值与区间端点比较。最后特判是否这个套餐能直接包含整个区间。将购买左右两个端点所在的区间与一下子购买整个区间比较得出较小者即可。


---
### 代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN=100005;
int T,n,ll,rr,l[MAXN],r[MAXN],c[MAXN],lans,rans,aans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		ll=2147483647;
		rr=0;
		
		for(int i=1;i<=n;i++)
		scanf("%d%d%d",&l[i],&r[i],&c[i]);
		
		for(int i=1;i<=n;i++){
			if(ll>l[i])ll=l[i],lans=c[i],aans=2147483647;
			if(ll==l[i])lans=min(lans,c[i]);
			
			if(rr<r[i])rr=r[i],rans=c[i],aans=2147483647;
			if(rr==r[i])rans=min(rans,c[i]);
			
			if(ll==l[i]&&rr==r[i])aans=min(aans,c[i]);
			
			printf("%d\n",min(lans+rans,aans));
		}
	}
	return 0;
}
```

---

## 作者：SuyctidohanQ (赞：0)

### 题目分析

显然是一道贪心题。

输入后，进行贪心操作。不难发现，只要维护一下最左、右端以及其对应的最小花费，同时维护最大线段的长度以及花费，即可得出答案。

具体解法：统计最左、右端的两个位置，如果出现了一个新的数值使得其能够拓展，则之前的整个区间购买方案无效，且当前的这个使区间拓展的套餐一定要买。

如果恰好拓展到要买的位置，则将这个数值与区间端点比较。最后特判是否这个套餐能直接包含整个区间。

将购买左右两个端点所在的区间与一下子购买整个区间比较得出较小者即可。



### 代码实现


```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void read ();
const ll MAXN = 1e5 + 10;
ll T, N, l[MAXN], r[MAXN], c[MAXN], lans = INT_MAX, rans = INT_MAX, cunans = INT_MAX;
void read () {
	ll lmax = INT_MAX, rmax = INT_MAX;
	cin >> N;
	lmax = INT_MAX; rmax = INT_MIN;
	for (ll i = 1; i <= N; i ++) cin >> l[i] >> r[i] >> c[i];
	for (ll i = 1; i <= N; i ++) {
		if (lmax > l[i]) {
			lmax = l[i];
			lans = c[i];
			cunans = INT_MAX;
		}
		if (lmax == l[i]) lans = min (lans, c[i]);
		if (rmax < r[i]) {
			rmax = r[i];
			rans = c[i];
			cunans = INT_MAX;
		}
		if (rmax == r[i]) rans = min (rans, c[i]);
		if (lmax == l[i] && rmax == r[i]) cunans = min (cunans, c[i]);
		cout << min (lans + rans, cunans) << endl;
	}	
}
int main () {
	cin >> T;
	while (T --) read ();
	return 0;
}
```

---

## 作者：清烛 (赞：0)

发现，我们要尽可能取到最左边和最右边的数字。所以无非两种情况：

- 取最左边的区间和最右边的区间
- 用一整个大区间覆盖掉

所以维护一下最左端/最右端以及其对应的最小费用，同时维护最大线段的长度以及其费用，即可求解本题。

~~不知道为什么当时 WA 了 5 发~~。

```cpp
int main() {
    int T; read(T);
    while (T--) {
        int n; read(n);
        int minl = 2e9, lcost = 2e9;
        int maxr = 0, rcost = 2e9;
        int maxlen = 0, lencost = 2e9;
        while (n--) {
            int l, r, c; read(l, r, c);
            if (l < minl) minl = l, lcost = c;
            if (l == minl) chkmin(lcost, c);
            if (r > maxr) maxr = r, rcost = c;
            if (r == maxr) chkmin(rcost, c);
            if (r - l + 1 > maxlen) maxlen = r - l + 1, lencost = c;
            if (r - l + 1 == maxlen) chkmin(lencost, c);
            int ans = lcost + rcost;
            if (maxlen == maxr - minl + 1) chkmin(ans, lencost);
            print(ans);
        }
    }
    return output(), 0;
}
```

---

