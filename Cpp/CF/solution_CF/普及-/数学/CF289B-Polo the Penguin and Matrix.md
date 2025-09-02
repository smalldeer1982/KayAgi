# Polo the Penguin and Matrix

## 题目描述

Little penguin Polo has an $ n×m $ matrix, consisting of integers. Let's index the matrix rows from 1 to $ n $ from top to bottom and let's index the columns from 1 to $ m $ from left to right. Let's represent the matrix element on the intersection of row $ i $ and column $ j $ as $ a_{ij} $ .

In one move the penguin can add or subtract number $ d $ from some matrix element. Find the minimum number of moves needed to make all matrix elements equal. If the described plan is impossible to carry out, say so.

## 样例 #1

### 输入

```
2 2 2
2 4
6 8
```

### 输出

```
4
```

## 样例 #2

### 输入

```
1 2 7
6 7
```

### 输出

```
-1
```

# 题解

## 作者：大宝和小宝 (赞：3)

此题意思是对矩阵中的元素进行加减一个常量 $d$，让矩阵中每个元素值相同，问最少需要进行多少次加减操作。显然，如果矩阵中的元素除以 $d$ 的余数不相同，那么无论多少次加减都不可能让所有数相等。在余数相同的情况下，可以对矩阵中的元素进行排序，以中间的数为基准，小的数加 $d$，大的数减 $d$，遍历统计即可。

-----
```cpp
#include <iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
 
int a[1000010];
 
int main()
{
	int sum,n,m,d,r,w,i;
	scanf("%d %d %d",&n,&m,&d);
	sum=n*m;
	scanf("%d",&a[0]);
	r=a[0]%d;
	for(i=1;i<sum;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]%d!=r)
		{
			printf("-1\n");
			return 0;
		}
	}
	sort(a,a+sum);
	r=a[sum/2];
	w=0;
	for(i=0;i<sum;i++)
	{
		w+=abs(a[i]-r)/d;
	}
	printf("%d\n",w);
	return 0;
}
```


---

## 作者：_Ventus_ (赞：2)

提供一种 $\Theta(n^2m^2)$ 的做法。

显然，若所有元素对 $d$ 取模之后的值不完全相等，那么就输出 `-1`，因为你无论怎么增加或减少 $d$，都无法使 $A$ 中的所有元素全都相等。

否则，先枚举每一个 $A_{ij}$，然后再计算出 $\sum\limits_{k=1}^n\sum\limits_{l=1}^m \frac{\left | A_{i,j}-A_{k,l} \right |}{d} $，取其中最小值。本题时限较大，该算法可以通过。

代码放上：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
const int N = 110, D = 1e4 + 10;
int a[N][N], mod[D];
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, m, d;
	cin >> n >> m >> d;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) { cin >> a[i][j]; mod[a[i][j] % d]++; }
	for (int i = 0; i < d; i++)
		if (mod[i] && mod[i] != n * m) { cout << "-1\n"; return 0; }
	int ans = 1e9;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			int sum = 0;
			for (int k = 1; k <= n; k++) 
				for (int l = 1; l <= m; l++) sum += abs(a[k][l] - a[i][j]) / d;
			ans = min(ans, sum);
		}
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：Eason_AC (赞：2)

## Content
有一个 $n\times m$ 的矩阵 $A$，每次操作你可以将某一个元素增加或减少 $d$，求是所有元素相等的最小操作次数，或者不存在这样的操作方案。

**数据范围：$1\leqslant n,m\leqslant 100$，$1\leqslant A_{i,j},d\leqslant 10^4$。**
## Solution
提供一种 $\Theta(n^2m^2)$ 的做法。

首先一个很显然的结论，若所有元素对 $d$ 取模之后的值不完全相等，那么就不存在操作方案，因为你无论怎么加减 $d$，都无法使 $A$ 中的所有元素全都相等。

否则，先 $\Theta(nm)$ 枚举出每一个 $A_{i,j}$，然后再 $\Theta(nm)$ 计算出 $\sum\limits_{k=1}^n\sum\limits_{l=1}^m |A_{k,l}-A_{i,j}|$，然后取最小值。这种复杂度在这道题目里面是足够可以过的。
## Code
```cpp
int n, m, d, a[107][107], vis[10007], ans = 0x3f3f3f3f;

int main() {
	n = Rint, m = Rint, d = Rint;
	F(i, 1, n) F(j, 1, m) vis[(a[i][j] = Rint) % d]++;
	F(i, 1, n) F(j, 1, m) if(vis[a[i][j] % d] < n * m) return printf("-1"), 0;
	F(i, 1, n) F(j, 1, m) {
		int sum = 0;
		F(k, 1, n) F(l, 1, m) sum += abs(a[k][l] - a[i][j]) / d;
		ans = min(ans, sum);
	}
	return write(ans), 0;
}
```

---

## 作者：Cloud_Umbrella (赞：1)

## 分析

这是道简单题，我们思考，一个矩阵同时加减同个数，所以它们模这个数的值一定要相同，也就是任意两个，证明也比较好证:

1. 设两个数 $x$，$y(x,y \in\mathbb N)$，模数为 $d$。并规定 $x\ge y$。
2. 因为 $x$ 和 $y$ 的差相等，则 $x+kd=y-kd(k\in \mathbb N)$，可得 $x+2kd=y$，同减 $x$，得 $y-x=2kd$。
3. 两边同时模 $d$，可得 $y-x\equiv 2kd \pmod d$，因为等式右边含有 $d$，所以 $y-x\equiv0\pmod d$。得到结论 $y\equiv x \pmod d$。

反之，直接输出 $-1$，结束程序。再反之，肯定有解，取中间值（指相对的），将小于中间值的加 $d$，大于中间值的加上 $d$。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int a[10010];//这里笔者比较懒，反正开一维也不影响
int n,m,d,mod;
int main(){
	scanf("%d%d%d",&n,&m,&d);
	cin>>a[1],mod=a[1]%d;
	for(int i=2;i<=n*m;i++){
		scanf("%d",a+i);//a+i相当于&a[i]
		if((a[i]%d)!=mod) return puts("-1"),0;//小技巧，相当于puts(-1);return 0;
	}
	sort(a+1,a+1+n*m);
	long long ans=0;
	for(int i=1;i<=n*m;i++)
		ans+=abs(a[i]-a[(n*m+1)/2])/d;//相对中间值
	printf("%lld",ans);
	return 0;//好习惯伴终生
}
```

---

## 作者：ztxtjz (赞：1)

## 【题意】
给一个 $n$ 行 $m$ 列的矩阵，给一个 $d$ 值，要求将矩阵里的每个数字变成一个相等的数字，每次操作可以将任意一个数 $+d$ 或 $-d$ 。若能实现，输出最小操作次数；反之输出$-1$。
## 【思路】
存储数据时，将二维矩阵压成一维来存储，比较方便排序。

判断能否实现时，因为任意两个数 $x$ ， $y$ ，都要保证 $(x-y)\bmod d=0$ ，即 $x\bmod d=y\bmod d$ 。用 $mod$ 数组记录每一个数对$d$取余的值。比较相邻的两个值是否相同，一旦不相同输出 $-1$ 并退出程序。

**算法：贪心**

要解决所有的数变成哪一个数的问题，不妨设几个数字模拟一下。

设 $a=k\times t-d,b=k\times t,c=k\times t+d$

变为$a$和$c$都要$3$次，变成$b$需要$2$次。

严格的证明楼上已经写出，这里只是举一个例子更加清晰地说明结论，以及证实贪心的正确性。

所以要使所有的数通过最少操作数变成同一个数，应该变为它们的中位数，即排序后数组中第 $(n\times m+1)/2$ 个数。

那么为什么是第 $(n\times m+1)/2$ 个数呢？这里**分类讨论**：

①当 $n\times m$ 为奇数时，中位数显然只存在一个。

②当 $n\times m$ 为偶数时，中位数存在两个，取任意一个都行，可以把它看作对称，选择哪个不会对结果有影响。我选的是前一个数，并不会向楼上所说的那样中位数是第$0$个，$(1\times 1+1)/2=1$ 。

设当前数为 $xi$ ，中位数为 $mid$ ，操作数为 $ti$ 。再次**分类讨论**：

①当$xi<mid$时，$ti=(mid-xi)/d$ ；

②当 $xi=mid$ 时, $ti=0$ ；

③当 $xi>mid$ 时， $ti=(xi-mid)/d$ 。

综合一下, $ti=abs(mid-xi)/d$，$ans=\sum\limits_{i=1}^{n\times m}ti$ 。
## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,d,ans,a[10005],mod[10005];
int main()
{
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1;i<=n*m;i++)
	{
		scanf("%d",&a[i]);
		mod[i]=a[i]%d;
	}
	for(int i=2;i<=n*m;i++) if(mod[i]!=mod[i-1]){printf("-1");return 0;}  //无法通过加减d的操作使数字相同
	sort(a+1,a+n*m+1);
	for(int i=1;i<=n*m;i++) ans+=abs((a[i]-a[(n*m+1)/2])/d);
	printf("%d",ans);
	return 0;
}
```

---

## 作者：流绪 (赞：1)

贪心。

已知一个长 n*m 的序列，要把所有数变成同一个数，每次只能改变 d，问最少需要几次。

要变成同一个数且次数要少，比较大的肯定要变小，比较小的数肯定要变大。那么这个比较大、比较小是怎么分的呢？

设 a<b<c，每次变化 d

若变成 a，需要 (b-a+c-a)/d=(b+c-2a)/d 步。

若变成 b，需要 (b-a+c-b)/d=(c-a) 步。

若变成 c，需要 (c-a+c-b)/d=(2c-b-a) 步。

显然变成 b 最好。拓展到普遍情况，对于序列 ai，若让他变成中间的一个数 x，它的首尾走的步数应该是这样的：(x-a1)/d 与 (an*m-x)/d，他们俩的步数和就是 (an*m-a1)/d步，所以这样的组数越多，总步数越少，所以我们让他们都变成中位数！

序列长奇数位的话，中位数很好找，如果序列长为偶数的话，中间两个取哪一个呢？其实取任意一个都是一样的，因为此时整个序列的步数可以两两成对的算,取中间两个的任意一个都是一样的。但是我们要取后面那个！为什么呢？因为如果取前面那个，那么 n=m=1 时，算出来的中位数是第 0 个，不合法。当然这里也可以把这个情况特判，然后就能取前面那个来作为中位数了。

上面只是分析的时候两两合并在一起分析，算还是得分开算，因为要判断能不能变过去。

下面是 AC 代码，细节注释代码里了。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1000000009
using namespace std;
int a[maxn];
int main()
{
	ios::sync_with_stdio(0);
	int n,m,d;
	cin >> n >> m >> d;
	for(int i=1;i<=n*m;i++)
		cin >> a[i];
	sort(a+1,a+1+n*m);
	int x = a[n*m/2+1]; //偶数取后面那个,奇数计算时向下取整,所以都要+1
	int ans = 0;
	for(int i=1;i<=n*m;i++)
		if((a[i]-x)%d)//无法通过加减 d 变过去
		{
			cout << -1;
			return 0;
		}
		else//可以变,加上步数
			ans += abs(a[i]-x)/d;
	cout << ans;
	return 0;
} 
```


---

## 作者：fuwei123 (赞：0)

大氵题。
## 题意

给定数组 $a$（把矩阵看成数组），每次操作可以选择一个位置，将它加 $d$ 或减 $d$，问要让每个数相等需要多少次操作，或报告无解。

## 做法
首先判断无解：若每个数对 $d$ 取余，所得结果不同，则无解。否则，有解。可以这样理解：考虑对数组 $a$，找到一个“**基准数**”，满足对任意的 $1\le i\le n$，$a_i=x+kd$，其中 $k$ 是一个整数。若能找到，我们就可以对每个 $a_i$，进行 $k$ 次操作，使得 $a_i=x$，一定有解，但**不保证**最优。若找不到，就说明无论如何都有数无法和其他数相同，就是无解。

那有解的情况下，$x$ 选什么是最优的呢？当然是 $a$ 的中间值了。

注意一点：算中间值的时候别忘了**向上取整**！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, m, d, a[10005], cnt;
signed main(){
	ios::sync_with_stdio(0);
	cin >> n >> m >> d;
	bool flag = 0;
	int x, sum = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			cin >> a[++cnt];
			sum += a[cnt];
			if(a[cnt] % d != x && !(i == 1 && j == 1))
				flag = 1;
			x = a[cnt] % d;
		}
	}
	if(flag){
		cout << "-1";
		return 0;
	}
	sort(a + 1, a + cnt + 1);
	int mid = a[(int)ceil(cnt / 2.0)], ans = 0;
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			ans += abs(a[(i - 1) * m + j] - mid) / d;
		}
	}
	cout << ans;
	return 0;
}


```


---

## 作者：ssSSSss_sunhaojia (赞：0)

[**原题传送门**](https://www.luogu.com.cn/problem/CF289B)
# 思路：
我们首先要知道，对一个数进行任意次加 $d$ 或减 $d$ 的操作，这个数对 $d$ 取模的余数永远不变。根据这个性质，我们可以知道当整个 $a$ 数组对 $d$ 取模的结果不全都相等的时候，输出 $-1$。

当整个 $a$ 数组对 $d$ 取模的结果全都相等时，就要求出使它们的值全相等的最少步骤数。显然，把它们都变成排序后最中间的那个数，是步骤最少的方案。

# AC Code:
```
#include <bits/stdc++.h>
using namespace std;
#define in inline
#define re register
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
LL n, m, d, a[(LL)1e4 + 10], Ans; 
namespace FastIO {
    char *p1, *p2, buf[1 << 14];
    #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, (1 << 14), stdin), p1 == p2) ? EOF : *p1++)
    template <typename T> inline void read(T& x) {
        x = 0; register int t = 1; register char ch = getchar();
        while (ch < '0' || ch > '9') {if (ch == '-') t = -1; ch = getchar(); }
        while (ch >= '0' && ch <= '9') {x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
        x *= t;
    }
    template <typename T> void write(T x) {
        if (x < 0) {putchar('-'); x = -x; } if (x > 9) write(x / 10);
        putchar(x % 10 ^ 48);
    }
    template <typename T> inline void writeln(T x, char sep = '\n') {write(x); putchar(sep); }
}
using namespace FastIO;
in LL qpow(LL a, LL b) {LL res = 1; while(b) {if(b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
in LL max(LL a, LL b) {return (a > b) ? a : b; }
in LL min(LL a, LL b) {return (a < b) ? a : b; }
int main() {
	IOS;
	read(n); read(m); read(d); 
	read(a[1]); //先输入第一个数
	for(re int i = 1; i  <= n; ++ i) 
		for(re int j = 1; j <= m; ++ j) {
			if(i == 1 && j == 1) continue; //第一个数已经输入过了
			read(a[(i - 1) * m + j]);  
			if(a[(i - 1) * m + j] % d != a[1] % d) return cout << -1, 0; //余数不相等
		} 
	sort(a + 1, a + n * m + 1); //排序
	for(re int i = 1; i <= n * m; ++ i)	
		Ans += abs(a[i] - a[(n * m + 1) / 2]) / d;//求出最少步骤 
	cout << Ans; 
	return 0;
}

```

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF289B) & [CF链接](http://codeforces.com/problemset/problem/289/B)

## 思路分析：

题目清晰明了，在这里就不过多赘述了。

要想让所有元素加减 $d$ 后都相等，当且仅当：$a_i \equiv a_j \pmod d$，其中 $i\ne j$。然后再对数列 $a$ 进行排序，找到中位数计算操作次数即可。

## 代码：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n,a[10010],ans;
int main(){
	int b,c,d;
	cin>>b>>c>>d;
	n=b*c;
	cin>>a[1];
	for(int i=2;i<=n;i++){
		cin>>a[i];
		if(a[i]%d!=a[1]%d){//判断同余
			cout<<-1<<endl;
			return 0;
		}
	}
	stable_sort(a+1,a+1+n);//排序
	int tmp=a[(n+1)/2];//中位数
	for(int i=1;i<=n;i++){
		ans+=abs(a[i]-tmp)/d;//统计答案
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：incra (赞：0)

### 题解
这里提供一个三分的思路。

先考虑输出 $-1$ 的情况。因为每一个数加或减 $d$ 之后模 $d$ 的余数不变，所以我们只需检查每一个数模 $d$ 的结果是否只有一种，如果有多种，则输出 $-1$。

考虑完无解情况，再来考虑有界的情况。先设 $f(x)$ 为所有元素变成 $x$ 的最小代价。不难想到，答案就是 $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\dfrac{|x-a_{i,j}|}{d}$。为了考虑有解的所有情况，$x$ 一定满足 $x=k\pmod{d}$，其中 $k$ 为 $a$ 数组中元素模上 $d$ 后的结果。

最后就是套一个三分的板子。
### 代码
```cpp
#include <iostream>
using namespace std;
const int N = 110,M = 10010;
int n,m,d;
int a[N][N];
bool flag[M];
int f (int x) {
	int ans = 0;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) ans += abs (a[i][j] - x) / d;
	}
	return ans;
}
int main () {
	scanf ("%d%d%d",&n,&m,&d);
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= m;j++) {
			scanf ("%d",&a[i][j]);
			flag[a[i][j] % d]++;
		}
	}
	int sum = 0;
	for (int i = 0;i < d;i++) sum += flag[i];
	if (sum > 1) {
		puts ("-1");
		return 0;
	}
	for (int i = 0;i < d;i++) {
		if (flag[i]) sum = i;
	}
	int l = 0,r = 1e4;
	while (l + 3 < r) {
		int mid = l + r >> 1;
		int mid1 = mid - 1,mid2 = mid + 1;
		if (f (mid1 * d + sum) > f (mid2 * d + sum)) l = mid1;
		else r = mid2;
	}
	int ans = 2e9;
	for (int i = l;i <= r;i++) ans = min (ans,f (i * d + sum));
	printf ("%d\n",ans);
	return 0;
}
```

---

## 作者：xuhanxi_dada117 (赞：0)

[题目大意&题目传送门](https://www.luogu.com.cn/problem/CF289B)

# 解法

## -1

什么时候输出 $-1$？

很明显：$\exists \ \, a[i][j] \not\equiv a[x][y] \pmod d$ 时，问题无解。

``` cout<<"-1"; ```

## 其他

根据数学常识，我们知道这种问题的解法是让所有数变成中位数。

中位数很简单，由于每次操作只修改一个点，所以干脆存成一维。

这样只要排序完了挨个算就行了，复杂度 $\Theta (n \times m)$。

可以 AC。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,d,a[10010],mod;
int main(){
	cin>>n>>m>>d;cin>>a[1];mod=a[1]%d;
	for(int i=2;i<=n*m;++i){
		cin>>a[i];
		if(a[i]%d!=mod){
			cout<<"-1";return 0;
		}
	}sort(a+1,a+n*m+1);
	int mid=a[(n*m+1)/2],ans=0;
	for(int i=1;i<=n*m;++i) ans+=abs((a[i]-mid)/d);
	cout<<ans;
	return 0;
}
```

[AC!](https://www.luogu.com.cn/record/103039979)

---

## 作者：TheShuMo (赞：0)

## 题意
现在给你一个 $n$ 行 $m$ 列的矩阵，每次可以把矩阵中的任意元素增减 $d$，求最小的操作次数，如果不能使所有元素相等，则输出 `-1`。

## 思路


若有两个元素 $a$ 与 $b$ 除以 $d$ 的余数 $a_1$ 与 $b_1$ 不相同，其中 $a = k \times d +a_1$，$b = l \times d +b_1$，那么无论 $a$ 加上或减去多少个 $d$，都是无法等于 $b$ 的 (因为 $a_1 \neq b_1$)。

所以输入后对全部元素取模，如果有多种不相同的余数，则输出 `-1`，无解。

那么我们再来看看有解的情况，即所有元素模 $d$ 的余数都相同的时候。

这个时候如果要使所有数相同的操作次数最少，就是取对所有元素排序后的中位数，所有数与该中位数相减取绝对值再除以 $d$ 的和就是最终的答案了。

## 代码

```cpp
#include<bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include<windows.h>
#endif

#define int long long

using namespace std;

int n, m, d, len = 1;
int a[1000001],c[100010];

signed main(){
    cin >> n >> m >> d;
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= m; j++)
            cin >> a[len++];
    len--;
    int p = a[len] % d;
    for(int i = 1; i <= len; i++) {
        if(a[i] % d != p){
            cout << -1;
            return 0;
        }
    }
    sort(a+1,a+1+len);
    int jz = a[(len + 1) / 2], ans = 0;
    for(int i = 1; i <= len; i++){
        ans += abs(a[i] - jz) / d;
    }
    cout << ans;
    #ifndef ONLINE_JUDGE
    system("pause");
    #endif
}
```

---

## 作者：zsh_haha (赞：0)

这道题非常简单，就是暴力枚举。

### 思路讲解

我们需要在矩阵 $a$ 中枚举每一个数，以当前枚举到的数 $a_{i,j}$ 为参考数，然后看这个矩阵中的每一个数需要加或减多少次才能得到这个数。

**特别的，如果某一次枚举时，一个数发现无法通过加或减得到当前参考数，那么就无解，输出 `-1`。**

这里的范围很小：$n\le100,m\le100$，所以此 $\mathcal{O}((n\cdot m)\cdot(n\cdot m))$ 时间复杂度方法可行。

### AC 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int a[101][101];
int main(){
	int n,m,w;
	cin>>n>>m>>w;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}
	int minn=100000001;
	//暴力 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			int d=a[i][j],sum=0;
			for(int k=1;k<=n;k++){
				for(int q=1;q<=m;q++){
					int ch=abs(d-a[k][q]);//取差的绝对值 
					if(ch%w!=0){
						cout<<-1;//无解 
						return 0; 
					}
					sum+=ch/w;//加减次数 
				}
			}
			minn=min(minn,sum); 
		}
	}
	cout<<minn;
    return 0;
}
```

---

