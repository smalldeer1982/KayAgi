# [Algo Beat Contest 001 D] Dreamed Sequence

## 题目背景

|               Problem               | Score |                         Idea                          |                             Std                              |                      Data                       |                            Check                             |                           Solution                           |
| :---------------------------------: | :---: | :---------------------------------------------------: | :----------------------------------------------------------: | :---------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|    $\text{D - Dreamed Sequence}$    | $425$ |  [orchardist](https://www.luogu.com.cn/user/347582)   |      [orchardist](https://www.luogu.com.cn/user/347582)      | [joe_zxq](https://www.luogu.com.cn/user/623577) |     [fcy20180201](https://www.luogu.com.cn/user/866154)      | [Link](https://www.luogu.com.cn/article/8ibxe6et) by [joe_zxq](https://www.luogu.com.cn/user/623577) |

![](https://pic.imgdb.cn/item/6719d910d29ded1a8ca39d07.png)

## 题目描述

给定长度为 $N$ 的序列 $A$ 和 $B$。

定义 $A$ 和 $B$ 两序列相乘 $A\times B$ 的规则如下，其中模数 $M=10^9+7$：

* 设 $A$ 序列为 $\{A_1,A_2,\dots,A_N\}$，$B$ 序列为 $\{B_1,B_2,\dots,B_N\}$，则相乘得到的序列为 $\{A_1B_1 \bmod M,A_2B_2 \bmod M,\dots,A_NB_N \bmod M\}$。

数学家小 G 梦想着让 $A\times B$ 得到的序列中出现次数最多的数出现的次数尽可能大。为了实现这一点，小 G 可以将 $B$ 数组任意重排列。小 G 想知道，出现次数最多的数最多出现多少次。

请你帮小 G 找到他梦想中的序列。如果小 G 获得了诺贝尔数学奖，他将会与你分享奖金。


## 说明/提示

#### 样例解释 #1

重排 $B$ 序列得 $\{8,4,5,2,6\}$，此时 $A\times B$ 得到的数组为 $\{8,8,15,8,30\}$，其中 $8$ 出现次数最多，出现 $3$ 次。

可以证明不存在重排 $B$ 序列的方式，使得答案大于 $3$。

#### 数据范围

对于 $100\%$ 的数据，保证 $1 \le N \le 2000$，$1 \le A_i,B_i \le 10^9$。


## 样例 #1

### 输入

```
5
1 2 3 4 5
2 4 6 8 5```

### 输出

```
3```

## 样例 #2

### 输入

```
10
1 12 38 48 10 19 23 19 32 6
10 46 20 11 36 25 36 28 50 50
```

### 输出

```
3```

## 样例 #3

### 输入

```
2
1 999999999
1 1000000000```

### 输出

```
1```

# 题解

## 作者：ARIS2_0 (赞：7)

### 前言

赛时被小黄题创飞了，写个题解长长教训。

### 思路

设 $c_i$ 为 $a_j=i$ 的 $j$ 的个数，$d_i$ 为 $b_j=i$ 的 $j$ 的个数。

则对于一个数 $x$，它的最大出现次数为：

$$\sum_{i=1}^{10^9}\sum_{j=1}^{10^9}\min(c_i,d_j)[i\times j\bmod M=x]$$

注意到这里取 $\min$ 是正确的，因为 $a_i,b_i\le 10^9$ 且 $M=10^9+7$ 是质数，所以对于 $a_i\not=a_j$，不存在 $b_k$ 使得 $a_i\times b_k\equiv a_j\times b_k\pmod M$。

**所以，如果有 $i\times j\bmod M=x$，那 $i$ 乘其他数、$j$ 乘其他数都不能得到 $x$，所以可以取 $\min$。**

那么，我们枚举满足 $c_i\not=0$ 的 $i$ 与 $d_j\not=0$ 的 $i,j$，计算出 $x=i\times j\bmod M$，然后将 $ans_x$ 加上 $\min(c_i,d_j)$，最后计算 $ans$ 数组中的最大值就可以了。

$c,d,ans$ 数组需要用 ```unordered_map``` 实现，时间复杂度 $O(n^2)$，常数稍大。

### Code

经过少许压行，马蜂不好还请见谅。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
unordered_map<int,int>c,d,ans;
int main(){
	int n;cin>>n;
    for(int i=1,p;i<=n;i++)cin>>p,c[p]++;
    for(int i=1,p;i<=n;i++)cin>>p,d[p]++;
    for(pii i:c)for(pii j:d)ans[1ll*i.first*j.first%1000000007]+=min(i.second,j.second);
    int pos=0;for(pii i:ans)pos=max(pos,i.second);cout<<pos;
}
```

---

## 作者：哈哈人生 (赞：3)

## 题外话
很有意思的一道题。

## 思路
容易发现相乘之后顶多只有 $n^2$ 个不同的数，考虑对每个不同的数求出最多出现多少次，这里可以离散化后用桶统计。带着取模不太好想，先思考如果没有取模，怎么统计每个数最多出现多少次，最后把取模后相同的数的出现次数加起来取最大值即可。现在问题转为，对于一个数 $x$，如何求出在任意重排 $b$ 序列后 $\sum^{n}_{i=1} [a_i\times b_i=x]$ 的最大值。

考虑贪心，对于还未被重排的 $b$ 序列。假如现在有两个数 $1\le i,j\le n$ 且 $a_i\times b_j=x$，我们重排时只需使 $j=i$ 一定是不劣的，因为这一定会使答案增加一（如果换种匹配方式答案最多也只会加一不会更优）。于是我们只需统计有多少对 $(i,j)$，满足 $1\le i,j\le n$ 且 $a_i\times b_j=x$，并且 $i$ 之间互不相同（这是序列 $a$ 的下标），$j$ 之间也互不相同（这是序列 $b$ 的下标）。如何标记一个位置 $i$ 或 $j$ 是否已经匹配了又成了难点。但我们有发现了一个性质，重排 $b$ 其实可以转换为把 $a,b$ 都重排，这是显然的。那假如我们把 $a$ 正序排列，$b$ 倒序排列，那么对于确定的 $x$，互相可以匹配的 $(i,j)$ 就也一定是分别递增的了。我们可以设两个桶 $t1_x,t2_x$ 分别表示最后一个完成匹配的序列 $a,b$ 的下标，只需判断当前的 $i,j$ 是否都分别大于 $t1_x,t2_x$，这题就做完了。

实现的时候可以先对 $a,b$ 排序，再直接双层循环枚举乘积 $x$，对 $x$ 的几个信息进行维护即可。由于有离散化和排序，总时间复杂度 $O(n^2 \log n^2)$。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
typedef int type;
inline type read(){
	type x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
inline void write(type x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x / 10);
	putchar(x%10+'0');
}
const int mod=1e9+7;
int n,a[2005],b[2005],maxx=0,mp[2000*2000+5],mp2[2000*2000+5],mp3[2000*2000+5],lsh[2000*2000+5],tot=0,lsh2[2000*2000+5],tot2=0,mp4[2000*2000+5];
int fd(int x){
	return lower_bound(lsh+1,lsh+tot+1,x)-lsh;
}
int fd2(int x){
	return lower_bound(lsh2+1,lsh2+tot2+1,x)-lsh2;
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			lsh[++tot]=a[i]*b[j];
			lsh2[++tot2]=a[i]*b[j]%mod;
		}
	}
	sort(lsh+1,lsh+tot+1);//离散化
	tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	sort(lsh2+1,lsh2+tot2+1);
	tot2=unique(lsh2+1,lsh2+tot2+1)-lsh2-1;
	sort(a+1,a+n+1);//对a正序排序
	sort(b+1,b+n+1,greater<int>());//对b倒序排序
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int tmp=fd(a[i]*b[j]);//这就相当于x
			if(mp2[tmp]>=i||mp3[tmp]>=j)continue;//判断当前i,j是否都大于t1[x],t2[x]。
			mp[tmp]++;//统计最多出现次数
			mp2[tmp]=i,mp3[tmp]=j;//更新标记
		}
	}
	for(int i=1;i<=tot;i++){
		int tmp=fd2(lsh[i]%mod);//取模后的数值
		mp4[tmp]+=mp[fd(lsh[i])];//相同的数值出现次数相加
		maxx=max(maxx,mp4[tmp]);//取最大值即是出现最多的次数
	}
	write(maxx);
	return 0;
}
```

---

## 作者：joe_zxq (赞：2)

显然最终的序列中 $x$ 最多出现的次数为 $\sum\limits_{i=1}^{10^9}\sum\limits_{j=1}^{10^9}\min(c_i,d_j)[i \times j \mod M=x]$，其中 $c_t,d_t$ 分别表示 $t$ 在序列 $A,B$ 种出现的次数。

虽然序列元素的数据范围很大，但是一个序列中的不同元素显然最多只有 $N$ 个。考虑分别处理出两个序列的不同元素即它们分别的出现次数。于是乎只需要考虑存在于序列中的的 $i,j$ 按上述式子计算即可。

时间复杂度：$O(N^2)$。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll mod = 1e9 + 7;

ll n, x, y, ans, a[114514], b[114514];
unordered_map<ll, ll> cnt, mp;
set<ll> s;
pair<ll, ll> c[114514], d[114514];

ll op(ll t[], pair<ll, ll> p[], ll tot = 0) {
	s.clear();
	cnt.clear();
	for (ll i = 1; i <= n; i++) {
		cin >> t[i];
		cnt[t[i]]++;
	}
	for (ll i = 1; i <= n; i++) {
		s.insert(t[i]);
	}
	for (ll kk : s) {
		tot++;
		p[tot] = {kk, cnt[kk]};
	}
	return tot;
}

void solve() {
	cin >> n;
	x = op(a, c);
	y = op(b, d);
	for (ll i = 1; i <= x; i++) {
		for (ll j = 1; j <= y; j++) {
			mp[c[i].first * d[j].first % mod] += min(c[i].second, d[j].second);
		}
	}
	for (pair<ll, ll> kk : mp) {
		ans = max(ans, kk.second);
	}
	cout << ans;
}

int main() {
	
	solve();
	
	return 0;
}
```

---

## 作者：__CJY__ (赞：1)

## 题意简述
给定两个长度为 $N$ 的序列 $A$ 和 $B$，你可以任意重排 $B$，目的是让 $A \times B$ 中某个元素值出现的次数最大化。这里的乘法是逐元素相乘，并对每个结果取模 $M=10^9+7$。
## 思路
用两个 `unordered_map` 记录每个元素在 $A$ 和 $B$ 中的频次，分别为 $c,d$。

读取数组 $A$ 并统计每个元素的频次；读取数组 $B$ 并统计每个元素的频次。

遍历 $A$ 中每个元素 $i$ 及其频次；遍历 $B$ 中每个元素 $j$ 及其频次，并计算乘积。更新 $ans$ 中该乘积的频次，即这对元素可以形成的最大对数。

其中循环变量 $i,j$ 为 `pair<int,int>` 类型。

找到频次最高的乘积，并输出频次最高的乘积的出现次数。

有问题请指出！

---

## 作者：xplor (赞：1)

## 前言

模拟赛硬控我 1h。

第一篇题解，求通过。

## 题目大意

输入两个长度为 $N$ 的序列 $A$ 和 $B$， 将 $B$ 任意排列使得 $A_i \times B_i$ 构成的序列 $C$ 中众数的数量最多，求出这个最大值。

## 思路

注意到 $1 \le N \le 2000$ 所以我们可以思考时间复杂度为 $O(N^2)$ 的算法，但 $A_i \times B_i$ 显然不能存进数组, 所以我们可以考虑先用一个结构体存 $A$ 下标，$B$ 下标和乘积，接着将这个结构体按乘积排序，接着计算众数的个数每个数判断下标是否标记过，若标记过则 continue。否则，数量加 $1$ 并标记下标，最后输出最大值。

## code


```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL N = 2010, inf = 1e9 + 7;
LL n;
LL a[N], b[N];
struct node {
	LL A;
	LL B;
	LL sum;
};

bool cmp (node x, node y) {
	return x.sum < y.sum;
}
node c[N * N];
LL idx;
LL res, tot, ans;
LL st_a[N], st_b[N];
int main () {
	scanf ("%lld", &n);
	for (LL i = 1; i <= n; i ++ ) scanf ("%lld", &a[i]);
	for (LL i = 1; i <= n; i ++ ) scanf ("%lld", &b[i]);	
	for (LL i = 1; i <= n; i ++ ) {
		for (LL j = 1; j <= n; j ++ ) {
			c[ ++ idx].A = i, c[idx].B = j, c[idx].sum = a[i] * b[j] % inf;
		}
	}
	sort (c + 1, c + 1 + idx, cmp);
	c[0] = {0, 0, -1};
	for (LL i = 1; i <= idx; i ++ ) {
		if (c[i].sum == c[i - 1].sum) {
			if (st_a[c[i].A] != tot && st_b[c[i].B] != tot) {
				res ++ ;
				st_a[c[i].A] = st_b[c[i].B] = tot;
			}
		} else {
			ans = max (res, ans);
			res = 1;
			tot ++ ;
			st_a[c[i].A] = st_b[c[i].B] = tot;
		}
	}
	ans = max (res, ans);
	printf ("%lld\n", ans);
	return 0;
}

```

---

## 作者：Hy13_xsm (赞：1)

## 题目大意

给出两个长度为 $N$ 的数组 $A$ 和 $B$，将 $B$ 中数字任意排序再和 $A$ 数组中的数两两配对并且相乘，求最后的结果中出现同一数字的最大数量是多少。

## Solution

先看范围，$N\le 2000$，所以可以试着用 $O(N^2)$ 的方法解决。将两个数组中的数字去重并且记录每个数出现的个数。使用一个 map，将两个数组任意相乘的结果记录下来，再计算贡献。举个例子，如果 $A_i$ 的个数是 $2$，$B_i$ 的个数是 $1$，那么它们只能产生 $1$ 个相同的乘积，因为同一个数字**不能**重复使用。枚举操作结束过后就可以统计哪一个结果可以用最多的方式构成。这么说不够清晰，看一下代码就懂了。

## AC 代码


```cpp
#include<bits/stdc++.h>
#define N 2005
#define int long long
using namespace std;
int n,ta[N],tb[N],cnta,cntb;
struct node{
	int x,y;
}a[N],b[N];
const int mod=1e9+7;
unordered_map<int,int>f;//不排序的 map，时间复杂度更低
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)cin>>ta[i];
	for(int i=1;i<=n;i++)cin>>tb[i];
	sort(ta+1,ta+n+1);sort(tb+1,tb+n+1);
	for(int i=1;i<=n;i++)
	{
		if(ta[i]!=ta[i-1])a[++cnta].x=ta[i];//去重
		a[cnta].y++;//统计个数
	}
	for(int i=1;i<=n;i++)
	{
		if(tb[i]!=tb[i-1])b[++cntb].x=tb[i];
		b[cntb].y++;
	}
	for(int i=1;i<=cnta;i++)
		for(int j=1;j<=cntb;j++)
			f[a[i].x*b[j].x%mod]+=min(a[i].y,b[j].y);//计算贡献
	int ans=0;
	for(auto i:f)ans=max(ans,i.second);//求出最值
	cout<<ans;
	return 0;
}
```

---

## 作者：postpone (赞：1)

先统计 $a$ 和 $b$ 中元素出现的数量，然后直接枚举两序列中的元素，统计相乘的数量就行了。

具体地，对于 $a$ 中出现了 $y_1$ 次的元素 $x_1$，$b$ 中出现了 $y_2$ 次的元素 $x_2$，其对 $x_1 x_2 \bmod M$ 贡献为 $\min(y1, y2)$。

复杂度 $O(n^2)$。

我估计出题者是想放 $O(n^2\log n^2)$ 过去的，但对于这个数据范围，实在是有点极限。

```cpp
constexpr int P = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    unordered_map<int, int> cnta, cntb;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnta[x]++;
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cntb[x]++;
    }

    unordered_map<int, int> sum;
    for (auto [x1, y1] : cnta) {
        for (auto [x2, y2] : cntb) {
            sum[1ll * x1 * x2 % P] += min(y1, y2);
        }
    }

    int ans = 0;
    for (auto [x, y] : sum) {
        ans = max(ans, y);
    }
    cout << ans << "\n";

    return 0;
}
```

---

## 作者：lanchenhao2010 (赞：1)

~~截止我写这篇题解时这题还是橙……~~

~~全谷最难橙题。~~

# 洛谷 P11682
## 简要题意

记模数 $M = 1000000007$，你有两个长为 $N$ 的数列 $A,B$，你可以将 $B$ 数列任意重排列。定义数列 $C$ 满足 $C_i = (A_i \times B_i) \bmod M$，求对于 $B$ 的所有重排列的方式，$C$ 中**出现次数最多的数出现的次数**的最大值是多少。

## 分析

首先考虑暴力枚举重排列，但就算用上哈希复杂度也是 $\mathcal{O}(N \cdot N!)$ 的，$0$ 分。

设 $1 \le i,j \le N$，我们发现，无论 $B$ 数列怎么重排列，$C$ 中的任意一个数一定是由某个 $A_i$ 与某个 $B_j$ 相乘再模 $1000000007$ 得到的。换言之，如果我们把所有 $A_i \times B_j \bmod M$ 都算出来，那么 $C$ 数列的取值一定在这 $N^2$ 个数中。

我们想象把这 $N^2$ 个数放在一张正方形棋盘上，第 $i$ 行第 $j$ 列的数为 $A_i \times B_j \bmod M$，那么我们的问题就变成了：在棋盘上选取最多的格子，这些格子上的数都相同且**任意两个格子不在同一行或同一列**（因为在任意一种重排列中一个 $A_i$ 只能对应一个 $B_j$）。

考虑怎么解决。~~（显然不能深搜。）~~ 我们发现一个性质：若 $A_i \times B_j \bmod M = A_i \times B_k \bmod M$，则 $B_j = B_k$，交换 $A$、$B$ 字母亦然。

**证明**：由 $A_i,B_i \le 10^9 < 1000000007 = M$ 且 $M$ 为质数，故对于每个 $A_i,B_i$ 在模 $M$ 意义下有唯一逆元。记 $A_i \times B_j \bmod M = A_i \times B_k \bmod M = X$ ，则 $B_j = X \times A_i ^ {-1} \bmod M = B_k$。交换 $A$、$B$ 字母亦然。

有了这个性质，我们可以提前将数列 $A$、$B$ 排序。这样，棋盘的横轴和纵轴就被分割成了许多小段，对应的，棋盘本身被分割成了许多矩形，每一个矩形内的元素相等，且任意两个元素相等的矩形不在同一行或同一列。举个栗子：设 $A = {1,1,4,5,1,4}$，$B = {2,1,5,4,1,2}$，最后划出来的矩形应该是这样：


|横A竖B|1（3个）|4（2个）|5（1个）|
|:-:|:-:|:-:|:-:|
|1（2个）|1（3×2）|4（2×2）|5（1×2）|
|2（2个）|2（3×2）|8（2×2）|10（1×2）|
|4（1个）|4（3×1）|16（2×1）|20（1×1）|
|5（1个）|5（3×1）|20（2×1）|25（1×1）|


然后我们就可以分别计算每个矩形的答案。对于每个矩形，问题转化为：在矩形内最多能选多少的格子，使得这些格子中任意两个不在同一行或同一列？答案显然为矩形的短边长度，于是这题就做完了。

且慢！我们如何合并相同元素的不同矩形的答案？可以使用 map 或 unordered_map，不过我的方法比较暴力：设当前矩形的答案为 $x$，直接往一个数组里添加 $x$ 个当前矩形的元素，最后再排序扫一遍就好了。总时间复杂度为 $\mathcal{O}(N^2 \log N)$ ，可以通过此题。
## 代码

码风可能不太好看 qwq。

```cpp
#include <bits/stdc++.h>
using namespace std;
int lty = 1000000007;
int a[2005],b[2005];
int ra[2005],rb[2005];
int c[4000005];
int acnt = 0,bcnt = 0;
int cnt = 0,n;
int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) scanf("%d",a + i);
	for(int i = 1;i <= n;i++) scanf("%d",b + i);
	sort(a + 1,a + n + 1);
	sort(b + 1,b + n + 1);
	for(int i = 1;i <= n;i++){
		if(i == n || a[i] != a[i + 1]) ra[++acnt] = i;
		if(i == n || b[i] != b[i + 1]) rb[++bcnt] = i;
	}
	for(int i = 1;i <= acnt;i++){
		for(int j = 1;j <= bcnt;j++){
			int res = 1LL * a[ra[i]] * b[rb[j]] % lty;
			int len = min(ra[i] - ra[i - 1],rb[j] - rb[j - 1]);
			while(len--) c[++cnt] = res;
		}
	}
	sort(c + 1,c + cnt + 1);
	//for(int i = 1;i <= cnt;i++) printf("%d ",c[i]);printf("\n");
	int last = 0,ans = 0;
	for(int i = 1;i <= cnt;i++){
		if(i == cnt || c[i] != c[i + 1]){
			//printf("%d ",i);
			ans = max(ans,i - last);
			last = i;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：nbhs23a28 (赞：1)

省流：这又又又是一道外强中干的纸老虎题，建议评黄。

本题题面相当唬人，可是一看数据范围 $N \le 2000$，其思路也就明晰了：可以先暴力枚举所有可能的乘积，再对其排个序找相等。 

接下来就是本题的玄机了，就是利用贪心思想，遍历每一组相等，得到每一组相等最大能达到个数（记为 $cnt$）。我们注意到，当且仅当 $a_i$ 或 $b_i$ 中有相等的数，才会在每组内部产生矛盾，而相等的无论取什么都是等价的，所以不妨贪心地假设其中任意一个正确即可（可按序）。答案便是 $cnt$ 中的最大值。

时间复杂度 $O(N^2 \log N^2)$，可卡过此题。

[Code](https://www.luogu.com.cn/paste/stp57cwa)

---

