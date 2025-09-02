# [ABC305D] Sleep Log

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc305/tasks/abc305_d

高橋くんは睡眠記録をつけています。 睡眠記録は奇数長の数列 $ A=(A\ _\ 1(=0),\ A\ _\ 2,\ldots,A\ _\ N) $ で表され、奇数番目は起床時刻を、偶数番目は就寝時刻を表しています。 より厳密には、睡眠記録をつけている間に高橋くんは次のような睡眠をとりました。

- すべての $ 1\leq\ i\leq\dfrac{N-1}2 $ を満たす整数 $ i $ について、睡眠記録をつけ始めてから $ A\ _\ {2i} $ 分後ちょうどに寝て、$ A\ _\ {2i+1} $ 分後ちょうどに起きた。
- それ以外の時間に寝ることも起きることもなかった。
 
次の $ Q $ 個の質問に答えてください。 $ i $ 番目の質問では、$ 0\leq\ l\ _\ i\leq\ r\ _\ i\leq\ A\ _\ N $ を満たす整数の組 $ (l\ _\ i,r\ _\ i) $ が与えられます。

- 睡眠記録をつけ始めてから $ l\ _\ i $ 分後ちょうどから $ r\ _\ i $ 分後ちょうどまでの $ r\ _\ i-l\ _\ i $ 分のうち、高橋くんが寝ていたのは何分間ですか？

## 说明/提示

### 制約

- $ 3\leq\ N\lt2\times10^5 $
- $ N $ は奇数
- $ 0=A\ _\ 1\lt\ A\ _\ 2\lt\cdots\lt\ A\ _\ N\leq10^9 $
- $ 1\leq\ Q\leq2\times10^5 $
- $ 0\leq\ l\ _\ i\leq\ r\ _\ i\leq\ A\ _\ N\ (1\leq\ i\leq\ Q) $
- 入力はすべて整数
 
### Sample Explanation 1

高橋くんは、以下の図のように睡眠をとりました。 ![](https://img.atcoder.jp/abc305/fe8152a63de7fea649d1d02197649a6a.png) それぞれの質問の答えは以下のようになります。 - 睡眠記録をつけ始めてから $ 480 $ 分後から $ 1920 $ 分後の間、高橋くんは $ 480 $ 分後から $ 720 $ 分後、$ 1320 $ 分後から $ 1440 $ 分後、$ 1800 $ 分後から $ 1920 $ 分後の $ 3 $ つの睡眠をとりました。睡眠時間の合計は $ 240+120+120=480 $ 分です。 - 睡眠記録をつけ始めてから $ 720 $ 分後から $ 1200 $ 分後の間、高橋くんは睡眠をとりませんでした。睡眠時間の合計は $ 0 $ 分です。 - 睡眠記録をつけ始めてから $ 0 $ 分後から $ 2160 $ 分後の間、高橋くんは $ 240 $ 分後から $ 720 $ 分後、$ 1320 $ 分後から $ 1440 $ 分後、$ 1800 $ 分後から $ 2160 $ 分後の $ 3 $ つの睡眠をとりました。睡眠時間の合計は $ 480+120+360=960 $ 分です。 よって、それぞれの行に $ 480,0,960 $ と出力してください。

## 样例 #1

### 输入

```
7
0 240 720 1320 1440 1800 2160
3
480 1920
720 1200
0 2160```

### 输出

```
480
0
960```

## 样例 #2

### 输入

```
21
0 20 62 192 284 310 323 324 352 374 409 452 486 512 523 594 677 814 838 946 1000
10
77 721
255 541
478 970
369 466
343 541
42 165
16 618
222 592
730 983
338 747```

### 输出

```
296
150
150
49
89
20
279
183
61
177```

# 题解

## 作者：ljlawa (赞：3)

先求个前缀和，然后对于每个输入通过二分找到第一个大于等于它的数，然后进行调整。算多了而且那段时间按在睡觉就要减去，算少了而且那段时间在睡觉就要加回来。

```
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 5;

int n, a[N], sum[N];
int q, l, r;

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++)
	{
		cin >> a[i];
		if (i % 2 == 1) sum[i] = sum[i - 1] + a[i] - a[i - 1];
		else sum[i] = sum[i - 1];
	}
	cin >> q;
	while (q --)
	{
		cin >> l >> r;
		int x = lower_bound (a + 1, a + 1 + n, l) - a;
		int y = lower_bound (a + 1, a + 1 + n, r) - a;
		int ans = sum[y] - sum[x];
		int u = a[x] - l;
		if (x & 1) ans += u;
		int v = a[y] - r;
		if (y & 1) ans -= v;
		cout << ans << endl;  
	}
    return 0;
}

```


---

## 作者：Crazyouth (赞：1)

**题意**

给你一个高桥君的睡眠表 $a$，若 $i$ 为奇数，表示在 $a_i$ 到 $a_{i+1}$ 这段时间，高桥君醒着，否则他在 $a_i$ 到 $a_{i+1}$ 这段时间在睡觉，给你 $q$ 次询问，问你在 $[l,r]$ 这个区间内，高桥君有多少分钟在睡觉。

**分析**

明显，需要找到 $[l,r]$ 对应的两个 $a_i$（用 lower_bound），然后再继续找他在这段时间内睡了多久，这个值用前缀和维护就行了。

最后一步，分类讨论 $l,r$ 与边界的两个 $a_i$ 的差，判断他是否有在这个时间睡觉，因为 $l,r$ 不一定完全是 $a$ 中的数。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[int(2e5+10)],sum[int(2e5+10)];
int main()
{
	int n,s,t,l,r,mid,sp,ep,q;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	sum[1]=0;
	for(int i=2;i<=n;i++)//前缀和维护a_i之前他的睡眠时间
	{
		if(i%2==0)
		{
			sum[i]=sum[i-1];
			continue;
		}
		sum[i]=sum[i-1];
		sum[i]+=a[i]-a[i-1];
	}
	cin>>q;
	int ans=0;
	while(q--)
	{
		ans=0;
		cin>>s>>t;
		if(t==0)//假如右端点为0，直接跳过
		{
			cout<<0<<endl;
			continue;
		}
		sp=lower_bound(a,a+n,s)-a;//左指针
		if(sp==0) sp++;//lower_bound可能返回0，这种情况表示他在s=0，因此给左指针加一
		ep=lower_bound(a,a+n,t)-a-1;//又指针
		if(sp%2) ans+=a[sp]-s;//假如左指针是奇数，说明他在a数组左指针到s之间有睡觉时间，加上
		ans+=sum[ep]-sum[sp];//加上前缀和结果
		if(ep%2==0) ans+=t-a[ep];//同上
		cout<<ans<<endl;
	}
	return 0;
}

---

## 作者：CheZiHe929 (赞：1)

# AT_abc305_d 题解
## 原题链接
[**洛谷**](https://www.luogu.com.cn/problem/AT_abc305_d)

[**Atcoder**](https://atcoder.jp/contests/abc305/tasks/abc305_d)

## 题目大意
给你 $ n $ 个时间点，其中：
- 当时间点 $ i $ 为奇数时，表示高桥刚刚醒来的时间点。
- 当时间点 $ i $ 为偶数时，表示高桥开始睡觉的时间点。
给你 $ q $ 次询问，每次询问给定一个 $ l $ 和一个 $ r $，让你求出在 $ [ l , r ] $ 这个区间范围内高桥共睡了多长时间。

## 思路分析
### 1.处理前缀和
- 如果枚举到的 $ i $ 为奇数，就说明刚刚睡醒，所以要加上上一次的睡觉时间，即 ```qzh[i]=qzh[i-1]+a[i]-a[i-1]```。
- 如果枚举到的 $ i $ 为偶数，就说明准备睡觉，睡觉时间没有改变，所以 ```qzh[i]=qzh[i-1]``` 即可。

### 2.二分
利用 STL 中的 `lower_bound` 求出第一个 $ \geq l $ 和第一个 $ \geq r $ 的位置分别为 `stll` 和 `stlr`。

### 3.分类讨论
我们需要根据 `stll` 和 `stlr` 的奇偶性来分四种情况讨论：
1. `stll` 为偶数，`stlr` 为偶数，即为 `stll%2==0&&stlr%2==0`。
2. `stll` 为偶数，`stlr` 为奇数，即为 `stll%2==0&&stlr%2==1`。
3. `stll` 为奇数，`stlr` 为偶数，即为 `stll%2==1&&stlr%2==0`。
4. `stll` 为奇数，`stlr` 为奇数，即为 `stll%2==1&&stlr%2==1`。

这里注意不要把 `a` 数组和 `qzh` 数组弄混。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int qzh[200005];
int n,q;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=2;i<=n;i++){
		if(i%2==1)qzh[i]=qzh[i-1]+a[i]-a[i-1];
		else qzh[i]=qzh[i-1];//1.处理前缀和  
	}
	cin>>q;
	while(q--){//q次询问 
		int l,r;
		cin>>l>>r;
		int stll=lower_bound(a+1,a+n+1,l)-a;
		int stlr=lower_bound(a+1,a+n+1,r)-a;//2.二分 找出stll和stlr 
		if(stll%2==0){
			if(stlr%2==0)//l 未睡觉，r 未睡觉 
				cout<<qzh[stlr]-qzh[stll]<<endl;
			else//l 未睡觉，r 睡觉中 
				cout<<qzh[stlr]-qzh[stll]-(a[stlr]-r)<<endl;
		}
		else{
			if(stlr%2==0)//l 睡觉中，r 未睡觉 
				cout<<qzh[stlr]-qzh[stll]+(a[stll]-l)<<endl;
			else //l 睡觉中，r 睡觉中 
				cout<<qzh[stlr]-qzh[stll]+(a[stll]-l)-(a[stlr]-r)<<endl;
			}
		//3.分类讨论
	}
	return 0;
}

```

## AC 记录
[**洛谷**](https://www.luogu.com.cn/record/112632818)

[**Atcoder**](https://atcoder.jp/contests/abc305/submissions/42234589)

**THE END.**

**THANK YOU.**

---

## 作者：_zzzzzzy_ (赞：1)

# 思路
我们可以对这些睡觉时间的做一遍前缀和，然后二分找一下被全部覆盖的睡觉区间的最左边和最右边，我们可以用前缀和求出，剩下零散的可以特判一下就可以了。

这里看一下二分查找的操作。

```cpp
int idl = lower_bound(a, a + n + 1, l) - a;
int idr = lower_bound(a, a + n + 1, r) - a - 1;
```

我们就可以用前缀和和二分解出这道题了。

# 思路
```cpp

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
const int maxn = 1000000;
int sum[maxn], a[maxn];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];

	}
	for (int i = 1; i <= n ;i++) {
		sum[i] = sum[i - 1];
		if (i % 2 == 1) {
			sum[i] += a[i] - a[i - 1];
		}
	}
	int m = 0;
	cin >> m;
	for (int i = 1; i <= m; i++) {
		int l, r;
		cin >> l >> r;
		int idl = lower_bound(a, a + n + 1, l) - a;
		int idr = lower_bound(a, a + n + 1, r) - a - 1;
		int ans = sum[idr] - sum[idl];

		if (idl % 2 == 1) {
			ans += a[idl] - l;
		} 
		if (idr % 2 == 0) {
			ans += r - a[idr];
		}
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc305_d)    
又是一道代码又臭又长的 ABC D 题。     
## 题意
给你 $n$ 个整数，记为 $a_1$ 到 $a_n$。       
其中，$a_{i}$ 和 $a_{i+1}$ 是一段睡觉的时间（$i$ 为偶数），其他时间都是醒的。     
$q$ 次询问，每次给定 $l$ 和 $r$，求这段时间中的睡觉时间有多长。     
## 解法
对于第 $i$ 次询问，我们设 $lp$ 为整个时间表里比 $l$ 严格大于的第一个位置，设 $rp$ 为整个时间表里小于等于 $r$ 的第一个位置。           
那么，我们先考虑一般情况：     
如果 $lp$ 为奇数，那么说明 $l$ 时刻在睡觉，这里产生了 $a_{lp}-l$ 的答案贡献，否则为 $0$。     
如果 $rp$ 为偶数，那么说明 $r$ 时刻在睡觉，这里就产生了 $r-a_{rp}$ 的贡献，否则为 $0$。     
特殊情况即 $lp>rp$。    
这种情况我们先对其进行交换。    
交换后，这种情况与一般情况正好相反：    
- 如果 $lp$ 是奇数且 $rp$ 是偶数，那么这种情况没有睡觉时间。   
- 否则，睡觉时间是 $r-l$。      

这里解释一下第一个。        
我们的 $lp$ 和 $rp$ 是经过了交换的，所以与一般情况正好相反。这种情况实际上是在一个区间内，所以其余情况没有特殊的答案贡献。             
[CODE](https://www.luogu.com.cn/paste/x73j52eb)

---

## 作者：Jerry_heng (赞：0)

（一）

直接用二分找出大于输入的 $l$ 和 $r$ 的数。

利用前缀和快速求出中间的几块的睡眠时间和。

然后处理最左边和最右边两块的睡眠时间。

二分可以用 `upper_bound` 直接解决。

（二）

AC 代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[200001],s[200001],l,r;
int solve(int x,int y){
	if(x&1)return s[y/2-1]-s[x/2];
	else return s[y/2-1]-s[x/2-1];
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n/2;i++)s[i]=s[i-1]+a[i*2+1]-a[i*2];
	cin>>q;
	while(q--){
		cin>>l>>r;
		int sitl=upper_bound(a+1,a+n+1,l)-a;
		int sitr=upper_bound(a+1,a+n+1,r)-a;
		int ans=solve(sitl,sitr);
		if(sitl&1){
			if(sitr&1)cout<<a[sitl]-l+r-a[sitr-1]+ans<<endl;
			else cout<<a[sitl]-l+ans<<endl;
		}
		else{
			if(sitr&1)cout<<r-a[sitr-1]+ans<<endl;
			else cout<<ans<<endl;
		}
	}
	return 0;
}
```

---

## 作者：Frictional (赞：0)

## 题意
给出高桥君的睡眠时间节点组成的序列 $a$，设当前这个节点是第 $i$ 个，即 $a_i$，当 $i$ 为奇数时，那么 $a_i$ 到 $a_{i+1}$ 这段时间内，高桥君醒着。反之，他在睡觉。给出 $Q$ 个询问，每次询问给出，问在 $[l,r]$ 这个区间中，高桥君有多少时间在睡觉。
## 思路
先前缀和出在 $a_i$ 之前总共的睡眠时间记为 $sleep[i]$，再通过二分查找出 $\ge l$ 的最小 $a_i$ 的值与 $\ge r$ 的最小的 $a_i$ 的值。把中间的算出来，再分类处理一下边界就可以了。
## AC code
```cpp
#include<bits/stdc++.h>
#define int long long
#define frz(a,b,c) for(int a=b;a<=c;a++)
#define frj(a,b,c) for(int a=b;a>=c;a--)
#define wh(a,b) while(a<=b)
#define wh1 while(1)
#define gc getchar()
#define pc putchar
#define pcs putchar(' ')
#define pcen putchar('\n')
using namespace std;
int rd(){
	int x=0,f=1;
	char ch=gc;
	while(ch<48||ch>57){if(ch=='-') f=-1;ch=gc;}
	while(ch>=48&&ch<=57) x=x*10+ch-48,ch=gc;
	return x*f;
}
void wr(int x){
	if(x<0) x=-x;
	if(x>9) wr(x/10);
	pc(x%10+48);
} 
int n,q;
int a[(int)2e5+5];
int sleep[(int)2e5+5];
int l,r;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=2;i<=n;i++){
		if(i%2)sleep[i]=sleep[i-1]+a[i]-a[i-1];
		else sleep[i]=sleep[i-1];
	}
	cin>>q;
	while(q--){
		cin>>l>>r;
		int le=lower_bound(a+1,a+n+1,l)-a;
		int ri=lower_bound(a+1,a+n+1,r)-a;
		if(le%2){
			if(ri%2) cout<<sleep[ri]-sleep[le]+(a[le]-l)-(a[ri]-r)<<endl;
			else cout<<sleep[ri]-sleep[le]+(a[le]-l)<<endl;
		}
		else{
			if(ri%2) cout<<sleep[ri]-sleep[le]-(a[ri]-r)<<endl;
			else cout<<sleep[ri]-sleep[le]<<endl;
		}
	}
	return 0;
}

```


---

## 作者：OIerBoy (赞：0)

# 题目大意
给 $N$ 个时刻：

- 当 $i$ 为奇数时，$A_i$ 表示刚刚起床的时刻。
- 当 $i$ 为偶数时，$A_i$ 表示开始睡觉的时刻。

有 $Q$ 次询问，每次求在 $[l,r]$ 区间内睡了多长时间。
# 分析
首先我们要考虑处理边界情况。

每一次二分查找第一个大于等于 $l$ 和 $r$ 的时刻 $x$ 和 $y$。

分别判断 $x$ 和 $y$ 是起床还是开始睡觉。
 
- 如果是起床，则说明上一段时间正在睡觉，就记录贡献。
- 如果是开始睡觉，则说明上一段时间未睡觉，就不用管。

处理完边界条件后就只需要处理中间整段的睡觉时间。

这个用一个前缀和维护即可。

具体细节请看代码。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
int n,Q,a[N];
int p[N];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		p[i]+=p[i-1];//前缀和
		if(i%2==1)p[i]+=a[i]-a[i-1];
	}
	cin>>Q;
	while(Q--){
		int l,r,ans=0;
		cin>>l>>r;
		int x=lower_bound(a,a+n,l)-a;//lower_bound查找下一个时刻
		int y=lower_bound(a,a+n,r)-a;
		if(x%2==1)ans+=a[x]-l;//判断边界贡献
		if(y%2==1)ans+=r-a[y-1];
		ans+=p[y-1]-p[x];//处理中间部分
		cout<<ans<<endl;
	}
	return 0;
}

```

---

