# [ABC330C] Minimize Abs 2

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc330/tasks/abc330_c

正整数 $ D $ が与えられます。

非負整数 $ x,y $ に対する $ |x^2+y^2-D| $ の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\leq\ D\ \leq\ 2\times\ 10^{12} $
- 入力は全て整数
 
### Sample Explanation 1

$ x=4,y=2 $ のとき $ |x^2+y^2-D|\ =\ |16+4-21|=1 $ となります。 $ |x^2+y^2-D|=0 $ を満たすような非負整数 $ x,y $ は存在しないので、答えは $ 1 $ です。

## 样例 #1

### 输入

```
21```

### 输出

```
1```

## 样例 #2

### 输入

```
998244353```

### 输出

```
0```

## 样例 #3

### 输入

```
264428617```

### 输出

```
32```

# 题解

## 作者：OldDriverTree (赞：5)

# Solution
从 $1$ 到 $\lfloor\sqrt D\rfloor$ 枚举 $x$，分类讨论。

$x^2+y^2\le D$ 的情况 $y$ 就取 $\lfloor\sqrt{D-x^2}\rfloor$。

$x^2+y^2\ge D$ 的情况 $y$ 就取 $\lceil\sqrt{D-x^2}\rceil$。

统计最小值即可。

时间复杂度 $O(\sqrt D)$。

# Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;

void read() {};
template<class T,class ...Ts>
void read(T& x,Ts&... xs) {
	x=0; bool f=false; char ch=0;
	while (!isdigit(ch) ) f|=(ch=='-'),ch=getchar();
	while (isdigit(ch) ) x=(x<<3)+(x<<1)+(ch&15),ch=getchar();
	if (f) x=-x; read(xs...);
}
main()
{
	int d,x,y,ans;
	read(d),ans=d;
	for (int x=0;x*x<=d;x++) {
		y=sqrt(d-x*x);
		ans=min(ans,d-x*x-y*y);
		y=ceil(sqrt(d-x*x) );
		ans=min(ans,x*x+y*y-d);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：time_keeper (赞：4)

# 题意简述

题目要求给定一个正整数 $D$，需要找到非负整数 $x$ 和 $y$，使得 $|x^2 + y^2 - D|$ 的值最小。

# 思路

枚举每个 $x,y$,找到一个数使得 $|x^2 + y ^ 2 - D|$ 最小。

考虑优化

在求解满足 $|x^2 + y ^ 2 - D|$ 的 $x,y$ 时, $y$ 的取值是尽可能接近 $\sqrt{D - x ^ 2}$ 的,也就是说，不需要枚举全部的 $y$ 即可求解。

见代码注释

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll; // 定义 long long 类型

ll d, i, j, min_dist = 1e12; // 声明变量 d、i、j 和 min_dist，并初始化 min_dist 为 1e12

ll Abs(ll a) { // 定义函数 Abs，用于计算绝对值,long long 的 abs 会CE()
    return a >= 0 ? a : -a; // 返回 a 的绝对值
}

int main() {
    scanf("%lld", &d); // 从标准输入读取一个整数 D

    // 遍历所有可能的非负整数 x 和 y
    for (i = 1; i * i <= d; ++i) {
        j = sqrt(d - i * i); // 计算 y 的可能取值
        ll dist1 = d - i * i - j * j; // 计算 x^2 + y^2 - D 的值
        ll dist2 = Abs(d - i * i - (j + 1) * (j + 1)); // 计算 x^2 + (y+1)^2 - D 的值
        min_dist = min(min_dist, min(dist1, dist2)); // 更新最小 min_dist
    }

    printf("%lld\n", min_dist); // 输出

    return 0; // 完结撒花
}
```






---

## 作者：zhangboyong (赞：3)

## 题意简述

给定一个整数 $D$，找到 $x$ 和 $y$，使得 $\lvert x^2+y^2-D \rvert$ 最小，求出最小值。

## 思路

我们可以枚举一个 $x$，然后二分求出 $y^2$ 的值。注意要找到第一个大于 $D-x^2$ 的数和第一个小于 $D-x^2$ 的数，将绝对值进行比较。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int d;
int ans = 1000000000;
int pfs[5000005];//存储平方数
signed main(){
	cin >> d;
	for(int i = 0;i<=5000000;i++){
		pfs[i] = i*i;
	}
	for(int i = 1;i*i<=d;i++){
		int rst = d-i*i;
		int y = lower_bound(pfs,pfs+5000001,rst)-pfs;
		if(pfs[y]==rst){
			cout << 0;
			return 0;
		}else{
			if(rst-pfs[y-1]<pfs[y]-rst){
				ans = min(ans,rst-pfs[y-1]);
			}else{
				ans = min(ans,pfs[y]-rst);
			}
		}
	}
	cout << ans;
}

```

---

## 作者：qqqaaazzz_qwq (赞：2)

### [My Blog](https://www.luogu.com.cn/blog/Hello-2023/)

首先可以证明答案 $\leq D$。因为我们令 $x=0,y=0$，这就是一组合法的解，且 $|0^2+0^2-D|=|0-D|=D$。⭐进一步我们可以证明在最优解里面 $x \leq 2 \times 10^6$。因此我们直接枚举 $x$，然后二分去确定最优的 $y$，就可以通过此题了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int d;

signed main()
{
	cin >> d;
	int ans = 1e18;
	for (int x=0;x<=2e6;x++)
	{
		int l = 0,r = 2e6;
		while(l<=r)
		{
			int y = (l+r)/2;
			ans = min(ans,abs(x*x+y*y-d));
			if(x*x+y*y<d) l = y+1;
			else r = y-1;
		}
	}
	cout << ans << "\n";
	return 0;
}
```
对于⭐处的补充说明：

$(2 \times 10^{6})^2 = 4 \times 10^{12}$

$(4 \times 10^{12})-10^{12}=(3 \times 10^{12})\geq 10^{12}$

故最优解里 $x$ 肯定 $\leq 2 \times 10^6$ 

---

## 作者：joe_zxq (赞：1)

# 思路

由于 $1 \le D \le 2 \times 10^{12}$，所以 $x$ 和 $y$ 都不大于 $\sqrt{2 \times 10^{12}} \approx 1414214$。于是我们可以枚举 $x$ 然后计算 $y$。

对于每一个算出的 $x$，最优的 $y$ 显然就是 $[\sqrt{D-x^2}]$ 和 $[\sqrt{D-x^2}]+1$。这里 $[x]$ 表示不超过实数 $x$ 的最大整数，我们分别计算 $|x^2+y^2-D|$，然后更新最小值即可。
# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ll d, ans = 1e18;
    cin >> d;
    for (ll x = 0; x <= 2e6; x++) {
        ll y = sqrt(d - x * x);
		ans = min(ans, abs(x * x + y * y - d));
		ans = min(ans, abs(x * x + (y + 1) * (y + 1) - d));
	}
	cout << ans;
	return 0;
}
```



---

## 作者：_H17_ (赞：1)

## 题目分析

情况 $1$：$x=\lceil \sqrt{n} \rceil,y=0$，稍微超出一点。

情况 $2$：$x=1\sim\lfloor \sqrt{n} \rfloor$，此时讨论 $y$。

$y$ 同样可以类似情况 $1,2$ 那样向上、下取整 $\sqrt{n-x^2}$。

## 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long //不开 ll 见祖宗
using namespace std;
int n,k,ans;
signed main(){
	cin>>n;
	k=sqrt(n),ans=(k+1)*(k+1)-n;//情况 1
	for(int x=1,j,y;x<=k;x++){//枚举 x
		j=n-x*x;
		y=sqrt(j);//下取整
		ans=min(ans,llabs(j-y*y));
		y++;//上取整
		ans=min(ans,llabs(j-y*y));//更新两个 y 的答案
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Pink_Cut_Tree (赞：1)

# AT_abc330_c [ABC330C] Minimize Abs 2 题解

本题可以用暴力枚举的做法来做。

### 明确概念

对于 $\forall k(k\in \bold R),k^2\geq 0$，“$=$” 成立当且仅当 $k=0$。

### 解法

对于 $10^{12}$ 的数据，我们可以枚举 $x$，根据 $x$ 的取值算出 $y$ 的取值，再算出 $ |x^2+y^2-D| $ 的最小值即可。

枚举量也是很小的，对于 $10^{12}$ 的数据范围，只需枚举到 $\sqrt{10^{12}}=10^6$ 即可。

时间复杂度 $\text O(\sqrt n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long D,lft,cha=1e12,sqt;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>D;
	for(long long i=1;i*i<=D;i++){
		lft=D-i*i; //算出剩下的值
		sqt=sqrt(lft);
		cha=min(cha,min(abs(lft-sqt*sqt),abs(lft-(sqt+1)*(sqt+1)))); //记得取绝对值
	}	
	cout<<cha;
return 0;
}
```


---

## 作者：Otue (赞：1)

## 思路
枚举一个 $x$，算出 $x^2+y^2\leq D$ 的最大的 $y$，用一个变量更新 $x^2+y^2$ 答案。但这是错误的，因为有绝对值。

所以说还要在 $x,y$ 周围几个值算一下。用 for 循环即可。

复杂度 $O(\sqrt n)$。

## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e5 + 5;
int d, res = 2e18;

signed main() {
	cin >> d;
	int t = sqrt(d);
	for (int i = 1; i <= d / i; i++) {
		int t = d - i * i;
		if (t == 0) res = min(res, t);
		else {
			int w = sqrt(t);
			for (int j = i - 5; j <= i + 5; j++) { // 周围再算几个
				for (int ww = w - 5; ww <= w + 5; ww++) {
					if (j < 0 || ww < 0) continue;
					res = min(res, abs(d - j * j - ww * ww));
				}
			}
		}
	}
	cout << res << endl;
}
```

---

## 作者：xu222ux (赞：0)

## 思路

暴力枚举所有的 $x$，对于每个 $x$ 再把 $\sqrt{d-x^2}$ 算出来，最后算出一个结果比一下最小值就行。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
	scanf("%lld",&n);
	long long ans=n;
	for(long long i=1;i*i<=n;i++){
		long long k=i*i,o=sqrt(n-i*i);
		ans=min(ans,min(abs(n-k-o*o),abs(n-k-(o+1)*(o+1))));
		if(ans==0)break;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：yhx0322 (赞：0)

upd on $2023.12.13$：更改了 $\LaTeX$ 公式的写法。
## Description
给定一个整数 $D$，求出两个非负整数 $x,y$，使得 $|x^2 + y^2 - D|$ 的结果最小。

## Solution
比较考验思维。

我们可以先枚举 $x$，范围是 $1 \sim \lfloor \sqrt{D} \rfloor$。接下来，列出等式：$D - x^2 = y ^ 2$，知道了等式左边的值，记为 $t$，便可以求出 $y = \sqrt{t}$。

然后记录答案 $ans$，初始化设为无穷大，每次比较两次 $\min$，第一次是取 $t - y ^ 2$ 的最小值，再将 $y$ 自增，第二次取 $y ^ 2 - t$ 的最小值即可。

## Code
```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int d, ans = LONG_MAX;
signed main() {
	cin >> d;
	for (int x = 1; x <= sqrt(d); x++) {
		int t = d - x * x;
		int y = sqrt(t);
		ans = min(ans, t - y * y);
		y++;
		ans = min(ans, y * y - t);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Crazyouth (赞：0)

**分析**

注意到，我们可以枚举 $x$，然后判断 $y$。$x$ 的枚举范围是 $0\sim \lceil \sqrt{d}\rceil$，要使 $x^2+y^2$ 离 $d$ 最近，那么 $y$ 的取值必然是 $\sqrt{d-x^2}$ 或 $\sqrt{d-x^2}+1$，所以枚举 $x$，再用刚才所取得的 $y$ 更新答案即可。

**AC Code**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int llabs(int x)
{
	if(x>=0) return x;
	else return -x;
}
signed main()
{
	int d,ans=1e18;
	cin>>d;
	for(int i=0;i*i<=d;i++)
	{
		int sy=sqrt(d-i*i);
		ans=min(ans,llabs(i*i+sy*sy-d));
		sy++;
		ans=min(ans,llabs(i*i+sy*sy-d));
	}
	cout<<min(ans,llabs((int)(sqrt(d)+1)*(int)(sqrt(d)+1)-d));
	return 0;
}

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc330_c)

## 思路

看到数据范围 $2\times 10^{12}$，第一想到二分。

我们可以求出 $1$ 到 $\sqrt{2\times 10^{12}}$ 每个数的平方，然后从 $1$ 循环到最接近 $D$ 的一个值。

循环出当前的值为 $x^2$，这时候我们通过 `upper_bound` 找我们已求数列中第一个大于 $x^2-D$ 的值，即为 ${y_1}^2$，是 $x^2+y^2-D$ 为负数的一个值，将这个值记为 `ans1`。再求刚才所求 $y^2$ 的上一个值，即为 ${y_2}^2$，是 $x^2+y^2-D$ 为正数的一个值，将这个值记为 `ans2`。取 `min(ans1,ans2)` 与结果变量中最小的一个计入结果变量。

最后输出结果变量即可。

## AC 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e6+10;
ll n,p[N],cnt,ans=1e18;//10 年 oi 一场空，不开 long long 见祖宗。
int main(){
	cin>>n;
	for(int i=1;i<=(int)2e6;++i)p[++cnt]=1ll*i*i;
	for(int i=1;p[i]<=n;++i){
		ll x=upper_bound(p+1,p+1+cnt,n-p[i])-p;
		ll y=x-1;
		ans=min({ans,abs(p[i]+p[x]-n),abs(p[i]+p[y]-n)});
	}
	cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/136920624)

---

## 作者：无钩七不改名 (赞：0)

~~退役后的第一场 abc，因为码力太差掉分了~~。

容易发现当 $0\le (x+1)^2\le D$ 时才可能取到最优解，可以直接枚举 $x$，然后确定 $y$，此时 $y$ 只有两种取值，一种是最大的 $y$ 使得 $x^2+y^2\le D$，另一种是最小的 $y$ 使得 $x^2+y^2\ge D$。

### 赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=1005;

long long d,ans;

long long read(){
	long long k=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){
		k=k*10+c-'0';
		c=getchar();
	}
	return k;
}

int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	d=read();/*
	long long y=sqrt(d-x*x);
	ans=min(min(d-x*x+y*y,abs(d-x*x+(y+1)*(y+1))),(x+1)*(x+1)-d);*/
	long long x=sqrt(d);
	ans=(x+1)*(x+1)-d;
	for(long long i(0);i*i<=d;++i){
		long long res=d-i*i;
		long long y=sqrt(res);
		ans=min(ans,min(res-y*y,(y+1)*(y+1)-res));
	}
	printf("%lld",ans);
	return 0;
}
```


---

