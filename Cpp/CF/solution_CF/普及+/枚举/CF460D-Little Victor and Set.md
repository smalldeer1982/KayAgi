# Little Victor and Set

## 题目描述

Little Victor adores the sets theory. Let us remind you that a set is a group of numbers where all numbers are pairwise distinct. Today Victor wants to find a set of integers $ S $ that has the following properties:

- for all $ x $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/26c8948a606517ebae5f50ff9b8fc7d91f76f3df.png) the following inequality holds $ l<=x<=r $ ;
- $ 1<=|S|<=k $ ;
- lets denote the $ i $ -th element of the set $ S $ as $ s_{i} $ ; value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/7523823a9f324064de1df35c0e0503740f7be786.png) must be as small as possible.

Help Victor find the described set.

## 说明/提示

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) represents the operation of bitwise exclusive OR. In other words, it is the XOR operation.

## 样例 #1

### 输入

```
8 15 3
```

### 输出

```
1
2
10 11
```

## 样例 #2

### 输入

```
8 30 7
```

### 输出

```
0
5
14 9 28 11 16
```

# 题解

## 作者：TKXZ133 (赞：3)

[Little Victor and Set](https://www.luogu.com.cn/problem/CF460D)

### 题目大意

在 $[l,r]$ 中选不超过 $k$ 个相异的数使得异或和最小，输出方案。

### 思路分析

分类讨论：

- 当 $k=1$ 时：

显然选 $l$ 是最优的。

- 当 $r-l+1\le 10$ 时：

直接 $O(n2^n)$ 暴力枚举每个数选或不选即可。

（判了这个之后后面的很多讨论会简单很多。）

- 当 $k=2$ 时：

我们发现两个不同的数的异或和最小为 $1$，因为当且仅当两个数相同时异或和为 $0$。

所以我们可以在 $[l,r]$ 内任找一个偶数 $x$，那么方案就是 $x$ 和 $x+1$。

（因为 $r-l+1>10$ 所以一定能找到）

- 当 $k\ge 4$ 时：

容易发现对于任意 $k\in N$，均有 $4k\oplus(4k+1)\oplus(4k+2)\oplus (4k+3)=0$，所以我们只需要任取一个 $k$ 就行了。

（因为 $r-l+1>10$ 所以一定能找到）

- 当 $k=3$ 时：

首先，我们可以按照 $k=2$ 的方法得到异或和为 $1$ 的答案，我们只需要考虑是否存在异或和为 $0$ 的方案即可。

我们枚举 $i,j\,(i>j)$，构造 $A=2^i+2^j,B=2^i+2^j-1,C=2^{j+1}-1$，容易发现 $A\oplus B\oplus C=0,A>B>C$，考虑证明这样构造的合法性：

**证明**：

我们只需要证明如果存在异或和为 $0$ 的选法，一定存在一种选法满足以上的形式即可。

将 $A,B,C$ 的二进制形式列出：

$$\begin{cases} A=00...00100...00100...00\\
			   B=00...00100...00011...11\\
           C=00...00000...00111...11\\
           \qquad\;\;\;\;{\color{red}^1}\;\;\;\;\;  i\;\;\;\;\;{\color{red}^2}\;\;\;\;j\;\;\;\;{\color{red}^3}\end{cases}$$
           
           
当 $A$ 固定时，$C$ 不可能更大，因为当 $C$ 增大时，${\color{red}2}$ 部分会多出若干 $1$，那么 $B$ 就必须也在 $2$ 部分增加若干 $1$，那么 $B$ 就大于 $A$ 了，不符合题设。

若 $A$ 的二进制表示中 $1$ 的个数大于 $2$，那么 ${\color{red}3}$ 部分会多出若干 $1$，$B,C$ 中必要有一个在对应的位置去掉若干个 $1$ 来满足异或和为 $0$ 的条件，故要么 $B$ 变小要么 $C$ 变小，如果这时的 $A,C$ 在 $[l,r]$ 的范围内，那么之前的 $A,C$ 也一定在 $[l,r]$ 的范围内。

若 $A$ 的二进制表示中只有一个 $1$，那么不存在满足条件的 $B,C$。

### 代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int N = 200200, V = 40;
#define inf 0x3f3f3f3f3f3f3f3f
#define int long long

int l, r, k;

vector <int> ans;

void add(int x){
    ans.push_back(x);
}

template <typename types, typename... Args> void add(types x, Args... args){
    add(x), add(args...);
}

signed main(){
    cin >> l >> r >> k;
    if (k == 1) add(l);
    else if (r - l + 1 <= 10) {
        int len = r - l + 1, minans = inf, way = 0;
        for (int i = 1; i < (1ll << len); i ++) {
            int ans = 0, cnt = 0;
            for (int j = 0; j < len; j ++)
                if (i >> j & 1) {
                    ans ^= (l + j);
                    cnt ++;
                }
            if (cnt <= k && ans < minans) {
                minans = ans;
                way = i;
            }
        }
        for (int i = 0; i < len; i ++)
            if (way >> i & 1) add(l + i);
    }
    else if (k == 2) {
        if (l & 1) l ++;
        add(l, l + 1); 
    }
    else if (k == 3) {
        int flag = 0;
        for (int i = 0; i <= V && !flag; i ++) 
            for (int j = i + 1; j <= V; j ++) {
                int x = (1ll << i) | (1ll << j), y = x - 1, z = (x ^ y);
                if (x <= r && z >= l) {add(x, y, z); flag = 1; break;}
            }
        if (!flag) {
            if (l & 1) l ++;
            add(l, l + 1); 
        }
    }
    else if (k >= 4) {
        for (int i = l; i <= l + 4; i ++)
            if (i % 4 == 0) {
                add(i, i + 1, i + 2, i + 3); break;
            }
    }
    int res = 0;
    for (auto it : ans) res ^= it;
    cout << res << '\n';
    cout << ans.size() << '\n';
    for (auto it : ans) cout << it << ' ';
    return 0;
}
```

---

## 作者：mrsrz (赞：2)

首先，当$r-l+1$比较小的时候，直接$O(2^nn)$枚举。

之后的讨论中，我们至少要保证区间长度大于等于5。

对$k$分类讨论：

1. $k=1$，则$l$最小。
2. $k=2$，则任选一个偶数$p$，这个数和$p+1$的异或结果为1，选$p$和$p+1$即可。显然不可能再小了。
3. $k=4$，则任选两个偶数$p,q$，则它们分别异或$p+1,q+1$后的结果为1，然后再异或起来得到0。要保证能这么选，区间长度至少5，所以不到的时候要暴力。
4. $k > 4$，则按照$k=4$的选法即可。
5. $k=3$，以下考虑这种情况。

首先，按照$k=2$的选法，能得到异或和为1的选法。所以，我们要考虑能否得到异或和为0的选法。

我们设$A\oplus B\oplus C=0$，且$A>B>C$。

则，存在如下选取方法：

$$A=100\dots00100\dots00$$
$$B=100\dots00011\dots11$$
$$C=000\dots00111\dots11$$

发现，$A$有且仅有2个二进制位为1。设$A=2^x+2^y(x>y)$。

而$B=A-1$，$C=2^{y+1}-1$。

当$A$确定的时候，$C$不可能再大了，否则，$C$一定会在$y+2\sim x-1$位中多出一些1来，而$B$也要相应加上这些1来抵消。那么显然不满足$A>B$了。

若$A$的二进制1个数大于2，则一定会在$0\sim y-1$位中多出一些1来，则需要$B$或$C$去掉相应位置的1来抵消，这样$A$变大了，$C$要么不变，要么变小。若此时的$A',C'$满足$l\leqslant A'< C'\leqslant r$，则显然也满足$l\leqslant A< C\leqslant r$。

而若$A$只有一个二进制位为1，则不存在$C< B< A$使得$A\oplus B\oplus C=0$，因为$A$那个二进制位无法被抵消掉。

上面的一大堆话说明了：如果有异或和为0的选法，则一定存在一种选法，满足$A$恰有2个二进制位为1，$B=A-1$，$C=A\oplus B$。

所以只需要枚举两个二进制位，然后判断$A,B,C$是否在$[l,r]$内即可。

## Code：
```cpp
#include<cstdio>
#include<vector>
#define LL long long
LL l,r;int k;
#define D "%I64d "
int main(){
	scanf(D D"%d",&l,&r,&k);
	if(r-l+1<=12){
		std::vector<LL>v;
		for(LL i=l;i<=r;++i)v.push_back(i);
		int sz=v.size(),C=1<<sz,zt=0;
		LL mn=1e17;
		for(int i=1;i<C;++i)
		if(__builtin_popcount(i)<=k){
			LL ans=0;
			for(int j=0;j<sz;++j)
			ans^=(i>>j&1)*v[j];
			if(ans<mn)mn=ans,zt=i;
		}
		printf(D"\n%d\n",mn,__builtin_popcount(zt));
		for(int i=0;i<sz;++i)
		if(zt>>i&1)printf(D,v[i]);
	}else
	if(k==1)printf(D"\n1\n" D,l,l);else
	if(k==2)printf("1\n2\n" D D,l+2>>1<<1,(l+2>>1<<1)+1);else
	if(k>=4)printf("0\n4\n" D D D D,l+2>>1<<1,(l+2>>1<<1)+1,l+4>>1<<1,(l+4>>1<<1)+1);else{
		for(int i=40;i;--i)
		for(int j=i-1;~j;--j){
			LL A=(1LL<<i)|(1LL<<j),C=A^(A-1);
			if(C>=l&&A<=r){
				printf("0\n3\n" D D D,A,C,A-1);
				return 0;
			}
		}
		printf("1\n2\n" D D,l+2>>1<<1,(l+2>>1<<1)+1);
	}
	return 0;
}
```

---

## 作者：pkh68 (赞：2)

这道题的思路真奇妙啊（~~qwq~~）！

### 解析

我们观察题目，考虑构造最优解，可以发现，对于集合 $A$ { $2k$，$2k+1$ }，他们的异或和为1，对于集合 $B$ { $2k$，$2k+1$，$2k+2$，$2k+3$ }，他们的异或和为0，则它们是最优解与次优解。

### $case1.$

$k=1$ ,取 $l$ 即可。

### $case2.$

$k=2$ ,若有集合 $B$ ，则取 $B$ ,否则 $r-l+1=2$，且 $l$ 为奇数，此时比较 $l$ , $l$ $xor$ $r$ ,	取最小值即可。

### $case3.$

$k=3$ ,考虑构造为0的解，枚举最高位，则$1$的个数为$2$,即：

$$00...001...$$
$$00...001...$$
$$00...000...$$

考虑下一位，若有$3$个$0$,则：

$$00...0010...$$
$$00...0010...$$
$$00...0000...$$

则不如取：

$$00...0001...$$
$$00...0001...$$
$$00...0000...$$

(注：这种情况必定成立，且定会枚举到。)

所以可以贪心地构造出对于当前枚举的最高位最优的解，即使两个以$1$开头的数尽量小，以$0$开头的数尽量大（想一想，为什么）。

即如下方案：

$$00...110000...$$
$$00...101111...$$
$$00...011111...$$

最后检查一下情况是否成立就行了，若找不到这样的解，则取集合 $B$ 即可。

### $case4.$

$k=4$ ,若有集合 $A$ ，则取 $A$ ,否则 $r-l+1=4$，且 $l$ 为奇数，此时取集合 $B$ 即可。


### 附上我真心丑陋的代码：

```cpp

#include<iostream>
#include<cstdio>
#include<cstdlib>
#define LL long long
#define re register
using namespace std;
LL l,r,k;
int main(){
	scanf("%lld%lld%lld",&l,&r,&k);
	if(k==1ll) printf("%lld\n%lld\n%lld\n",l,1ll,l);
	else if(k==2ll){
		if(l==1ll) printf("%lld\n%lld\n%lld\n",1ll,1ll,l);
		else if(r-l==1ll&&(l&1ll)){
			LL ans=l^(l+1);
			if(l<ans) printf("%lld\n%lld\n%lld\n",l,1ll,l);
			else printf("%lld\n%lld\n%lld %lld\n",ans,2ll,l,l+1);
		}
		else if(l&1ll) printf("%lld\n%lld\n%lld %lld\n",1ll,2ll,l+1,l+2);
		else printf("%lld\n%lld\n%lld %lld\n",1ll,2ll,l,l+1);
	}
	else if(k==3ll){
		bool flag=false;
		for(re int i=62;i>=0;--i){
			LL d1=(1ll<<i),d2=(1ll<<(i-1));
			LL a=d1|d2,b=d1|(d2-1),c=d1-1;
			if((l<=a&&a<=r)&&(l<=b&&b<=r)&&(l<=c&&c<=r)){
				flag=true;
				printf("%lld\n%lld\n%lld %lld %lld\n",0ll,3ll,a,b,c);
				break;
			}
		}
		if(!flag){
			if(l&(1ll)) printf("%lld\n%lld\n%lld %lld\n",1ll,2ll,l+1,l+2);
			else printf("%lld\n%lld\n%lld %lld\n",1ll,2ll,l,l+1);
		}
	}
	else{
		if(r-l+1>4){
			if(l&1ll) printf("%lld\n%lld\n%lld %lld %lld %lld\n",0ll,4ll,l+1,l+2,l+3,l+4);
			else printf("%lld\n%lld\n%lld %lld %lld %lld\n",0ll,4ll,l,l+1,l+2,l+3);
		}
		else if(r-l+1==4ll){
			bool flag=false;
			for(re int i=62;i>=0;--i){
				LL d1=(1ll<<i),d2=(1ll<<(i-1));
				LL a=d1|d2,b=d1|(d2-1),c=d1-1;
				if((l<=a&&a<=r)&&(l<=b&&b<=r)&&(l<=c&&c<=r)){
					flag=true;
					printf("%lld\n%lld\n%lld %lld %lld\n",0ll,3ll,a,b,c);
					break;
				}
			}
			if(!flag){
				if(l&1ll) printf("%lld\n%lld\n%lld %lld\n",1ll,2ll,l+1,l+2);
				else printf("%lld\n%lld\n%lld %lld %lld %lld\n",0ll,4ll,l,l+1,l+2,l+3);
			}
			
		}
	}
	return 0;
}

```


---

## 作者：船酱魔王 (赞：1)

### 题意回顾

在 $ [l,r] $ 找出最多 $ k $ 个、最少 $ 1 $ 个互异的整数使得异或和最小。

### 分析

$ k $ 上限很大，$ l,r $ 范围也很大，目测不是很好设计动态规划，猜测最终的集合不会很大。

* $ k=1 $ 时，$ \{l\} $ 即为答案。

* $ k=2 $ 时，若区间长度为 $ 2 $，答案显然；否则，必然存在 $ \{p,p+1\} \in [l,r] $ 使得 $ p \equiv 0 \pmod 2 $，此时，$ p $ 与 $ p+1 $ 除了最后一位以外所有位都相同，最后一位异或值即总异或值为 $ 1 $。因为 $ l>0 $ 且集合元素互异，所以当集合元素个数为 $ 1 $ 或 $ 2 $ 时，异或值必然大于 $ 0 $。

* $ k=3 $ 时，区间长度大于 $ 2 $，自然可以依照 $ k=2 $ 方法构造出异或和为 $ 1 $ 的集合；考虑能否异或和等于 $ 0 $，则集合元素个数为 $ 3 $，考虑找到 $ x,y,z \in [l,r] $ 使得 $ x,y,z $ 互异且 $ x \oplus y = z $，因为 $ l>0 $ 所以 $ x \oplus y = z $ 时 $ x,y,z $ 必然互异，所以只用考虑 $ [l,r] $ 范围及异或限制即可，可以使用类似于数位 DP 的方法尝试寻找可行解。

* $ k \ge 4 $ 时，若区间长度大于 $ 7 $，则能找到 $ \{p,p+1,p+2,p+3\} \in [l,r] $ 且 $ p \equiv 0 \pmod 4 $，此时四个数的除了最后两位外的所有位均相同，最后两位异或值即总异或值为 $ 0 $，为最优解；否则区间长度不超过 $ 7 $ 时可以暴力枚举解决。

### 参考实现

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
long long l, r, k;
int vis[60][64];
long long whr, gzh, todie;
bool solve(int w, int sta) {
	if(w < 0) return true;
	if(vis[w][sta]) return false;
	vis[w][sta] = 1;
	int xmin = (sta & 1) ? 0 : ((l >> w) & 1);
	int xmax = (sta & 2) ? 1 : ((r >> w) & 1);
	int ymin = (sta & 4) ? 0 : ((l >> w) & 1);
	int ymax = (sta & 8) ? 1 : ((r >> w) & 1);
	int zmin = (sta & 16) ? 0 : ((l >> w) & 1);
	int zmax = (sta & 32) ? 1 : ((r >> w) & 1);
	for(int xt = xmin; xt <= xmax; xt++) {
		for(int yt = ymin; yt <= ymax; yt++) {
			int zt = xt ^ yt;
			if(zmin <= zt && zt <= zmax) {
				int newsta = sta;
				if(xt > xmin) newsta |= 1;
				if(xt < xmax) newsta |= 2;
				if(yt > ymin) newsta |= 4;
				if(yt < ymax) newsta |= 8;
				if(zt > zmin) newsta |= 16;
				if(zt < zmax) newsta |= 32;
				if(solve(w - 1, newsta)) {
					if(xt) whr ^= (1ll << w);
					if(yt) gzh ^= (1ll << w);
					if(zt) todie ^= (1ll << w);
					return true;
				}
			}
		}
	}
	return false;
}
int main() {
	cin >> l >> r >> k;
	if(k == 1) {
		printf("%lld\n1\n%lld\n", l, l);
	} else if(k == 2) {
		if(r - l + 1 >= 3 || l % 2 == 0) {
			long long tp = l;
			if(l % 2) tp++;
			printf("1\n2\n%lld %lld\n", tp, tp + 1);
		} else {
			if((l ^ r) < l && (l ^ r) < r) {
				printf("%lld\n2\n%lld %lld\n", l ^ r, l, r);
			} else {
				printf("%lld\n1\n%lld\n", l, l);
			}
		}
	} else if(k >= 4) {
		if(r - l + 1 >= 7) {
			for(long long ti = l; ti <= r; ti++) {
				if(ti % 4 == 0) {
					printf("0\n4\n%lld %lld %lld %lld\n", ti, ti + 1, ti + 2, ti + 3);
					break;
				}
			}
		} else {
			long long tr = (long long)1e18 + 5;
			int gzh = 0;
			for(int whr = 1; whr < (1 << (r - l + 1)); whr++) {
				long long nt = 0;
				int cm = 0;
				for(int i = 0; i < r - l + 1; i++) {
					if(whr & (1 << i)) nt ^= l + i, cm++;
				}
				if(cm > k) continue;
				if(nt < tr) gzh = whr, tr = nt;
			}
			vector<long long> vec;
			vec.clear();
			printf("%lld\n", tr);
			for(int i = 0; i < r - l + 1; i++) {
				if(gzh & (1 << i)) vec.push_back(l + i);
			}
			printf("%d\n", vec.size());
			for(int i = 0; i < vec.size(); i++) {
				printf("%lld", vec[i]);
				if(i + 1 < vec.size()) printf(" ");
				else printf("\n");
			}
		}
	} else if(k == 3) {
		if(solve(59, 0)) {
			printf("0\n3\n%lld %lld %lld\n", whr, gzh, todie);
		} else {
			long long tp = l;
			if(l % 2) tp++;
			printf("1\n2\n%lld %lld\n", tp, tp + 1);
		}
	}
	return 0;
}
```

---

## 作者：Priestess_SLG (赞：0)

首先特判 $r-l+1\le 20$ 的情况，可以直接暴力枚举。

剩下的分类讨论：

+ $k\ge 4$，构造任意相邻四个元素即可，异或值为 $0$。
+ $k=1$，构造最小值 $l$ 即可。
+ $k=2$，构造 $2k,2k+1$ 相邻两个数即可，异或值为 $1$。
+ $k=3$。考虑到构造 $k=2$ 时异或值就可以为 $1$，所以只需要考虑是否可以构造出 $0$。那么可以发现构造 $2^{j+1}-1,2^i+2^j-1,2^i+2^j$ 一定是最优解。贪心的理性证明，若钦定 $i$ 位置前两个数选择了 $1$，$j$ 位置后两个串选择了 $1$，那么为了贪心的让极差最小，肯定后面部分让后面两个串一直都选 $1$，第一个串 $i$ 后面一直都选 $0$ 最优。枚举 $i,j$ 判断是否有合法解即可。时间复杂度为 $O(\log^2n)$ 可以随便通过。

```cpp
#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500100;
const int mod = 1e9 + 7;
int a[N], n, s;
int power(int a, int b, int c) {
    int ans = 1;
    while (b) {
        if (b & 1) ans = ans * a % c;
        a = a * a % c, b >>= 1;
    }
    return ans;
}
int inversion(int x, int mod) {
    return power(x, mod - 2, mod);
}
int binom(int a, int b) {
    if (a < b) return 0;
    int res = 1;
    a %= mod;
    for (int i = 1; i <= b; ++i) res = res * (a - i + 1) % mod;
    for (int i = 1; i <= b; ++i) res = res * inversion(i, mod) % mod;
    return res;
}
inline int op(int x) { return x * 2 - 1; }
signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int l, r, k;
    cin >> l >> r >> k;
    int mi = 1e18;
    vector<int> res;
    if (r - l <= 20) {
        for (int i = 1; i < (1 << (r - l + 1)); ++i) {
            if (__builtin_popcount(i) > k) continue;
            int xr = 0;
            for (int j = 0; j < r - l + 1; ++j)
                if (i >> j & 1) xr ^= (j + l);
            if (xr < mi) {
                mi = xr;
                res.clear();
                for (int j = 0; j < r - l + 1; ++j)
                    if (i >> j & 1) res.emplace_back(j + l);
            }
        }
        cout << mi << '\n' << res.size() << '\n';
        for (int &i : res) cout << i << ' ';
        cout << '\n';
    } else if (k == 1) {
        cout << l << '\n' << 1 << '\n' << l << '\n';
    } else if (k == 2) {
        int id = -1, mi = 1e18;
        for (int i = l; i < r && i <= l + 100; ++i)
            if ((i ^ (i + 1)) < mi) mi = i ^ (i + 1), id = i;
        cout << mi << '\n' << 2 << '\n';
        cout << id << ' ' << id + 1 << '\n';
    } else if (k == 3) {
        for (int i = 60; i; --i)
            for (int j = i - 1; ~j; --j) {
                int x = (1ll << i) | (1ll << j), b = x ^ (x - 1), c = x - 1;
                if (x >= l && x <= r && b >= l && b <= r && c >= l && c <= r) {
                    cout << 0 << '\n' << 3 << '\n' << x << ' ' << b << ' ' << c << '\n';
                    return 0;
                }
            }
        int id = -1, mi = 1e18;
        for (int i = l; i < r && i <= l + 100; ++i)
            if ((i ^ (i + 1)) < mi) mi = i ^ (i + 1), id = i;
        cout << mi << '\n' << 2 << '\n';
        cout << id << ' ' << id + 1 << '\n';
    } else {
        int id = -1, mi = 1e18;
        for (int i = l; i + 2 < r && i <= l + 100; ++i)
            if ((i ^ (i + 1) ^ (i + 2) ^ (i + 3)) < mi) mi = i ^ (i + 1) ^ (i + 2) ^ (i + 3), id = i;
        cout << mi << '\n' << 4 << '\n';
        cout << id << ' ' << id + 1 << ' ' << id + 2 << ' ' << id + 3 << '\n';
    }
    return 0;
}

```

---

## 作者：king_xbz (赞：0)

超级恶心毒瘤的分类讨论构造题目，考察细心程度和进制运算的基本功；

首先，通过之前做题的经验(CF15C)，我们知道，一个偶数xor(这个偶数+1)=1，而两对这样的异或组合异或和为0；

而拼凑最小的异或和自然需要尽可能凑0，然后是1……。但是我们还应该考虑是否有别的能构成0的情况，比如$a\ xor\  b=c$，那么$a\ xor\ b\ xor\ c=0$，同理更多的数也满足条件。

这样我们就有个大体笼统的思路了。

具体需要分16类讨论：

1:$k=1$

2:$k=2,l=1$

3:$k=2,len=2,l\&1,l<l\ xor \ (l+1)$

4:$k=2,len=2,l\&1,l>=l\ xor \ (l+1)$

5:$k=2,l\&1,len!=2$

6:$k=2,!(l\&1),len!=2$

7:$k=3,a\ xor \ b=c$

8:$k=3,a\ xor \ b!=c,l\&1$

9:$k=3,a\ xor \ b!=c,!(l\&1)$

10:$len>=4,k>=4,!(l\&1)$

11:$len>4,k>=4,l\&1$

12:$len=4,l\&1,a\ xor \ b\ xor \ c=0$

13:$len=4,l\&1,a\ xor \ b\ xor \ d=0$

14:$len=4,l\&1,a\ xor \ d\ xor \ c=0$

15:$len=4,l\&1,d\ xor \ b\ xor \ c=0$

16:$len=4,l\&1$除上面四种之外的情况

还有，不开long long见祖宗

完整注释代码：

```cpp
#include<bits/stdc++.h>
#define fint register int
#define H 5001
#define N 3457984
#define int long long
using namespace std;
signed main()
{
	int l,r,k;
	cin>>l>>r>>k;
	int len=r-l+1;
	if(k==1)//只能选1个数异或，那就选最小的那个 
	{
		cout<<l<<endl<<1<<endl<<l;
		return 0;
	}
	else 
	if(k==2)//只能选两个数异或，最少就是个1，不然的话就是l^(l+1) 
	{
		if(l==1) 
		cout<<1<<endl<<1<<endl<<1;
		else 
		if(len==2&&(l&1LL))
		{
			int ans=l^(l+1);
			if(l<ans) 
			cout<<l<<endl<<1<<endl<<l;
			else 
			cout<<ans<<endl<<2<<endl<<l<<" "<<l+1;
			return 0;
		}
		else 
		if(l&1LL)
		{
			cout<<1<<endl<<2<<endl<<l+1<<" "<<l+2;
			return 0;
		}
		else
		{
			cout<<1<<endl<<2<<endl<<l<<" "<<l+1;
			return 0;
		}
	}
	else 
	if(k==3)//选3个数，暴力枚举每种情况 
	{
		bool ff=0;
		for(fint i=62;i>=0;--i)//枚举2^i下a^b=c的情况 
		{
			int x=(1LL<<i),y=(1LL<<(i-1));
			int a=x|y,b=x|(y-1),c=x-1;
			if(l<=a&&a<=r&&l<=b&&b<=r&&l<=c&&c<=r&&((a^b^c)==0))
			{
				ff=1;
				cout<<0<<endl<<3<<endl<<a<<" "<<b<<" "<<c;
				return 0;
			}
		}
		if(!ff)
		{
			if(l&1LL) 
			cout<<1<<endl<<2<<endl<<l+1<<" "<<l+2;
			else 
			cout<<1<<endl<<2<<endl<<l<<" "<<l+1;
			return 0;
		}
	}
	else
	if(len>=4&&k>=4)//有至少4个数异或且至少四个数可选 
	{
		if(l%2==0)//第一个数为偶数，直接取前四个 
		cout<<0<<endl<<4<<endl<<l<<" "<<l+1<<" "<<l+2<<" "<<l+3;
		else
		if(len>4)//第一个数为奇数，取第2，3，4，5个，此时需要区间内至少有5个数 
		cout<<0<<endl<<4<<endl<<l+1<<" "<<l+2<<" "<<l+3<<" "<<l+4;
		else
		if(len==4&&k==4&&l%2==1)
		goto lb;
		return 0;
	}
	else
	if(len==4&&(l&1LL))
	{
		lb:
		int a=l,b=l+1,c=l+2,d=r;
		if((a^b^c)==0)//此时需要满足三数相互异或和为0,总共4种可能情况 
		{
			cout<<0<<endl<<3<<endl<<a<<" "<<b<<" "<<c;
			return 0;
		}
		else
		if((a^b^d)==0)
		{
			cout<<0<<endl<<3<<endl<<a<<" "<<b<<" "<<d;
			return 0;
		}
		else
		if((a^d^c)==0)
		{
			cout<<0<<endl<<3<<endl<<a<<" "<<c<<" "<<d;
			return 0;
		}
		else
		if((d^b^c)==0)
		{
			cout<<0<<endl<<3<<endl<<b<<" "<<c<<" "<<d;
			return 0;
		}
		else//否则的话就是异或和为1，也就是第二个数(偶)^第三个数(奇) 
		{
			cout<<1<<endl<<2<<endl<<b<<" "<<c;
			return 0;
		}
	}
	return 0; 
}
```



---

