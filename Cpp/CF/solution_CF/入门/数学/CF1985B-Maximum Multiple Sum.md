# Maximum Multiple Sum

## 题目描述

给定一个整数$ n $，找到一个整数$ x $，这样:

- $ 2 \leq x \leq n $。
- 将 $ x $ 中小于等于 $ n $ 的倍数之和取最大值。形式上是 $ x + 2x + 3x + \dots + kx $，其中 $ kx \leq n $ 比 $ x $ 的所有可能值都大。

## 说明/提示

对于“$ n = 3 $”，“$ x $”可能取值为“$ 2 $”和“$ 3 $”。所有小于等于$ n $的$ 2 $的倍数之和为$ 2 $，所有小于等于$ n $的$ 3 $的倍数之和为$ 3 $。因此，$ 3 $是$ x $的最优值。

对于$ n = 15 $, $ x $的最优值为$ 2 $。小于或等于$ n $的所有$ 2 $的倍数之和为$ 2 + 4 + 6 + 8 + 10 + 12 + 14 = 56 $，可以证明它是$ x $的所有其他可能值的最大值。

## 样例 #1

### 输入

```
2
3
15```

### 输出

```
3
2```

# 题解

## 作者：Flaw_Owl (赞：8)

# Maximum Multiple Sum 题解

题目链接：[Maximum Multiple Sum](https://www.luogu.com.cn/problem/CF1985B)

## 题目分析

### $O(N)$ 的暴力做法

抽象题目，即对于给定的 $n$，求解唯一确定的一个 $x$ 满足 $2 \leq x \leq n$，使得

$$ \sum_{i=1}^{\lfloor \dfrac{n}{x} \rfloor} ix = x \cdot \lfloor \frac{n}{x} \rfloor \cdot \dfrac{1 + \lfloor \dfrac{n}{x} \rfloor}{2} $$

这个转换应用了等差数列的求和公式。

由于本题的 $n$ 范围较小，最大只有 $100$，可以考虑暴力枚举 $x$ 的值，并维护最后的答案和该式的最大值。该时间复杂度为 $O(N)$。显然可以通过。

下面给出关键代码：

```cpp
n = read(); // read() 是手写快读
mx = -1;    // 维护最大值
for (int i = 2; i <= n; i++)
{
    int k = n / i;
    if ((1 + k) * k / 2 * i > mx)
    {
        // 更新答案和最大值
        ans = i;
        mx = (1 + k) * k / 2 * i;
    }
}
printf("%d\n", ans);
```

### $O(1)$ 的数论方法

事实上，这道题的最优解是利用数学方法推导出一个 $O(1)$ 的数学结论。在 $n$ 的数据量极大时，就只能使用这种方式。该结论在其他题解中也有提及，即：**当 $n = 3$ 时，$x = 3$；反之，$x = 2$。**

然而，其他题解中并没有对该结论给出较为严谨的数学证明。下面将以不知道这个结论的前提下，从头开始推导。

#### 尝试

首先，观察式子，我们可以将其写成函数的形式。令

$$ z = x \cdot \lfloor \dfrac{y}{x} \rfloor \cdot \dfrac{1 + \lfloor \dfrac{y}{x} \rfloor}{2} $$

（注：函数的变量取值范围始终和题目所给相同，出于书写整洁性不再单独列出。同时，题目要求 $x,n$ 都是正整数，为了保证函数的连续性，在就图像进行分析的时候认为 $x,n$ 都是实数。下同）

可以发现，$z$ 是一个二元函数。然而，由于取整函数（指向下取整函数，下同）的存在，这个函数并不连续。作为第一步分析，我们可以先去掉取整函数，即

$$ z = x \cdot \dfrac{y}{x} \cdot \dfrac{1 + \dfrac{y}{x}}{2} = \dfrac{xy + y^2}{2x} $$

这个二元函数可以被几何描述为一个光滑的曲面。题目所求即为分析 $x$ 在 $y$ 确定的情况下的变化与 $z$ 变化的关系，在空间中表示为该曲面和平面 $y = n$ 的交线。联立得该交线方程:

$$ z = \dfrac{nx + n^2}{2x} = \dfrac{n^2}{2} \cdot \dfrac{1}{x} + \dfrac{n}{2} $$

显然该函数单调递减，在 $x = 2$ 处取到最大值。

#### 进一步分析

去掉取整函数之后，我们对该交线图像有了大致的认知。然而，在加上取整函数之后，图像将不再连续。为了分析它们的变化，我们不妨比较：

$$ y_1 = x \cdot \lfloor \frac{n}{x} \rfloor \cdot \dfrac{1 + \lfloor \dfrac{n}{x} \rfloor}{2} $$

$$ y_2 = x \cdot \dfrac{n}{x} \cdot \dfrac{1 + \dfrac{n}{x}}{2} $$

令 $\lfloor \dfrac{n}{x} \rfloor = \dfrac{n}{x}$，可知此时 $\dfrac{n}{x}$ 是一个整数。设其为 $q$，则 $x = \dfrac{n}{q}$。对于连续整数 $q_1 < q_2$，我们令 $a = \dfrac{n}{q_2},b = \dfrac{n}{q_1}$，就有：

$$\forall x \in (a,b],\lfloor \dfrac{n}{x} \rfloor = \dfrac{n}{x}$$

因此，$x \in (a,b]$ 时，$y_1$ 在 $(a,b]$ 上单调递增。同时，当 $x = b$，即 $y_1$ 在该区间上取得最大值时，有 $y_1 = y_2$。在上面的分析中，我们得知 $y_2$ 在整个 $x$ 的正半轴上单调递减。因此，我们可以分析出图像特征：将每一个因数间隔看作一条左空心右实心的线段，而实心点整体呈下降趋势。

其中，$\dfrac{n}{n},\dfrac{n}{q_1},\dfrac{n}{q_2},\cdots,\dfrac{n}{1}$ 就是每一个线段的右端点。

#### 正式证明

当 $n \bmod 2 = 0$ 时，$x = 2$ 满足 $q = \dfrac{n}{2}$ 是一个整数。故它是线段的右端点，又因为 $x \geq 2$，显然在此处函数取到最值。

当 $n \bmod 2 \neq 0$ 时，$x = 2$ 不再是函数的右端点，假设它属于 $(1,p]$ 区间，其中 $p$ 是这个线段的右端点。由于 $x$ 实际上只能取整数，那么如果可以证明 $2 < p < 3$，使得 $\lfloor \dfrac{n}{p} \rfloor = \dfrac{n}{p}$，就可以说明当 $x = 2$ 时取得最大值。

根据上面的假设，转化为证明存在一个整数 $q$ 使得 $\dfrac{n}{3} < q < \dfrac{n}{2}$。根据假设，$n$ 是一个奇数，则始终存在一个正整数满足

$$\lfloor \dfrac{n}{2} \rfloor < \dfrac{n}{2}$$

那么因为关系

$$ \dfrac{n}{3} < q \leq \lfloor \dfrac{n}{2} \rfloor < \dfrac{n}{2}$$

只需证明

$$\dfrac{n}{3} < \lfloor \dfrac{n}{2} \rfloor$$

根据取整函数的性质，我们有

$$ \dfrac{n}{2} -1 \leq \lfloor \dfrac{n}{2} \rfloor \leq \dfrac{n}{2} $$

令 $\dfrac{n}{2} - 1 > \dfrac{n}{3}$，解得 $n > 6$。对于剩下的奇数，直接枚举即可。$n = 3$ 时，$1 < 1$ 显然不成立，$n = 5$ 时，$\dfrac{5}{3} < 2$ 成立。

故得证当 $n \neq 3$ 时，$x = 2$ 能够使函数取得最大值。

特殊地，当 $n = 3$ 时，函数 $y_1$ 在 $(1,3]$ 范围内单调递增。$x = 3$ 能够使得函数取到最大值。

至此，我们得以将该算法优化到 $O(1)$ 的复杂度。

```cpp
n = read();
if (n == 3)
    printf("3\n");
else
    printf("2\n");
```

---

## 作者：cute_overmind (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1985B)

### 题目大意
给定你一个数 $n$，寻找一个数 $x$ 满足以下条件：
- $2\le x \le n$
- 小于或等于 $n$ 的 $x$ 的倍数之和最大，形式上，满足 $x+2x+3x+\dots+kx$，其中 $kx \le n$ 在 $x$ 的所有可能值中最大。

### 题目分析
观察条件二可得，$x+2x+3x+\dots+kx$ 应是一个首项为 $x$，末项为 $kx$，项数为 $\lfloor \frac{n}{x} \rfloor$ 的等差数列。又观察可得，数据样例中 $x \le 100$。所以我们可以采取暴力求解的方法。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t;
void solve(){
	int n;
	cin >> n;
	int maxn = 0 , ans = n;
	for(int i = 2;i <= n;i++){
		int sum = 0;
		for(int j = 1;j * i <= n;j++)  sum += j * i;
		if(sum > maxn) ans = i , maxn = sum;
	}
	cout << ans << "\n";
}
signed main()
{
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：mc_xiexie (赞：2)

# CF1985B Maximum Multiple Sum
[翻译](https://www.luogu.com.cn/paste/iz90bppr)
## 思路
### 方法1

因为：
- $ 2 \leq x \leq n $。
- 将 $ x $ 中小于等于 $ n $ 的倍数之和取最大值。形式上是 $ x + 2x + 3x + \dots + kx $，其中 $ kx \leq n $ 比 $ x $ 的所有可能值都大。

所以这道题其实就是让你在 $n$ 的范围内找一个 $x$ 的倍数之和最大的一个，所以直接枚举：
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;
	cin>>t;
	while(t--){
		ll n,a;
		ll maxn=-1;
		cin>>n;
		for(int i=2;i<=n;i++){
			ll sum=0;
			for(int j=1;j<=n;j++){
				if(j%i==0){
					sum+=j;
				}
			}
			if(sum>maxn){
				a=i;
				maxn=sum;
			}
			sum=0;
		}
		cout<<a<<"\n";
	}
	return 0;
}
```
### 方法2
我们可以发现，当 $2x$ 大于 $n$ 时，$x$ 的倍数之和等于 $x$，倍数之和肯定不会是最大的，除了 $2$ 或 $3$ 时，因为最小值 $2$ 乘 $2$ 都小于 $n$，此时输出 $n$。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;
	cin>>t;
	while(t--){
		ll n;
		cin>>n;
		ll maxn=-1,a=n;
		for(int i=2;i*i<=n;i++){
			ll sum=0;
			for(int j=1;j<=n;j++){
				if(j%i==0){
					sum+=j;
				}
			}
			if(sum>maxn){
				a=i;
				maxn=sum;
			}
			sum=0;
		}
		cout<<a<<"\n";
	}
	return 0;
}
```
### 方法3
我们同时发现，只要不为 $3$，答案就为 $2$，因为 $2$ 的倍数是最多的，并且是最密集的，所以之和是最大的。（$2$ 时答案就为 $2$，方法2已证）

不懂的话见此。例如 $2$ 和 $3$ 作比较，假设 $n$ 是 $3$ 的倍数，此时 $3$ 的倍数之和是最大的（因为 $3k = n$），同时 $n$ 非 $2$ 的倍数,此时 $2$ 的倍数之和是最小的（因为 $2x = n-1$）。

此时 $3$ 的倍数为 $ 3 + 6 + 9 + \dots + n $,，此时 $2$ 的倍数为 $ 2 + 4 + 6 + 8+ \dots + n-1 $。只算最后四个倍数，$3$ 最后四个倍数之和等于 $n+n-3+n-6+n-9=4n-18$，$2$ 最后四个倍数之和等于 $n-1+n-3+n-5+n-7=4n-16$，所以答案就为 $2$。
```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;
	cin>>t;
	while(t--){
		ll n;
		cin>>n;
		if(n==3){
			cout<<n<<"\n";
		}
		else{
			cout<<2<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：ZnHF (赞：2)

# 题意简述

给定整数 $n$ ，求整数 $x$，满足：

- $2 \leq x \leq n$。

- 小于等于 $n$ 的 $x$ 的倍数之和最大。

# 题目分析

本题数据范围较小，直接枚举可以通过本题。

具体地，从 $2$ 开始枚举 $x$，当 $x > n$ 时停止枚举。对于每个 $x$，计算小于等于 $n$ 的 $x$ 的倍数之和并与当前记录的最大值进行比较，如果前者更大，则更新最大值并记录答案。

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){register int t1=0,t2=0;register char x=getchar();while(x<'0' || x>'9'){if(x=='-') t1|=1;x=getchar();}while(x>='0' && x<='9'){t2=(t2<<1)+(t2<<3)+(x^48);x=getchar();}return t1?-t2:t2;}
inline void write(int x){if(x<0){putchar('-');x=-x;}int sta[100],top=0;do{sta[top++]=x%10;x/=10;}while(x);while(top) putchar(sta[--top]+48);}
int T,n,ans1,ans2;
signed main(){
	T=read();
	while(T--){
		ans1=0;
		ans2=0;
		n=read();
		for(int i=2;i<=n;i++){
			int sum=0;
			for(int j=1;i*j<=n;j++){
				sum+=i*j;
			}
			if(sum>ans1){
				ans1=sum;
				ans2=i;
			}
		}
		write(ans2);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

## 题解：CF1985B Maximum Multiple Sum
## 思路
观察数据范围，发现数据太小，$n$ 最大才 $100$，所以直接暴力。
先来一层循环，从 $2$ 开始到 $n$。求 $x+  2x+  3x+  \dots +  kx$，更新最大的和与其对应的 $i$ 就可以通过此题。
## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
#define pb emplace_back
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9 + 7;

ll T, n, i, j;

int main()
{
	//freopen("xxx.in","r",stdin);
	//freopen("xxx.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> T;
	while (T--)
	{
		cin >> n;
		ll Max = 0, ans = n;
		for (i = 2; i <= n; i++)
		{
			ll sum = 0;
			for(j = 1; j * i <= n; j++)  sum += j * i;
			if(sum > Max)
			{
				ans = i;
				Max = sum;
			}
		}
		cout << ans << endl;
	}
	return 0;
}

```

---

## 作者：BrotherCall (赞：1)

## 题意

给定整数 $n$，求一个整数 $x$，满足：

- $2\leq x \leq n$。

- $\displaystyle \sum\limits_{i = 1}^k i\cdot x$ 最大，其中 $k$ 为满足 $kx \leq n$ 最大的正整数。

## 思路

### 赛时思路

可以直接枚举 $x$ 的所有情况，暴力计算答案。

由于是像筛法那样的暴跳，总复杂度为 $O(Tn\log n)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define int long long
using namespace std;

const int N = 1e6 + 100; 
int t , n;

signed main() {
	cin >> t;
	while(t --) {
		cin >> n;
		int maxx = 0 , ans = n;
		for(int j = 2;j <= n;j ++) {
			int sum = 0;
			for(int k = 1;k * j <= n;k ++) 
				sum += k * j;
			if(sum > maxx) {
				ans = j;
				maxx = sum;
			}
		}
		cout << ans << "\n";
	}
	return 0;
}
```

### 另解

我们注意到当 $n = 3$ 时，答案为 $3$。否则答案一定为 $2$。

### 证明：

$n=2$ 和 $n = 3$ 的情况显然，这里我们证明 $n \geq 4$ 的情况。

根据等差数列求和公式我们得到：

$$\displaystyle \sum\limits_{i = 1}^k i\cdot x = \displaystyle x\cdot \frac{(1+\lfloor \frac{n}{x} \rfloor)\cdot \lfloor \frac{n}{x} \rfloor}{2}$$

$$\because \displaystyle x\cdot\left\lfloor \frac{n}{x}\right\rfloor = n - n \bmod x$$

$$\therefore \displaystyle n - x + 1\leq x\cdot\left\lfloor \frac{n}{x}\right\rfloor \leq n$$

根据以上式子放缩：

当 $x$ 取 $2$，原式 $\leq \displaystyle \frac{(n - 1)\cdot(1+\lfloor \frac{n}{2} \rfloor)}{2}$。

当 $x$ 取 $s(s \geq 3)$，原式 $\geq \displaystyle \frac{n\cdot(1+\lfloor \frac{n}{s} \rfloor)}{2} \geq \displaystyle \frac{n\cdot(1+\lfloor \frac{n}{3} \rfloor)}{2}$。

上式比下式：
$$\displaystyle \frac{n - 1}{n} \cdot \frac{1+\lfloor \frac{n}{2} \rfloor}{1+\lfloor \frac{n}{3} \rfloor}$$

我们只需要证明这个式子 $\geq 1$ 即可证明 $2$ 为答案，这里我们分类讨论一下。

若 $n = 6m$ 或 $6m + 1$，此时 $m \geq 1$，则原式 $\displaystyle\geq \frac{n - 1}{n}\cdot \frac{1+3m}{1+2m} \geq \frac{5}{6}\cdot\frac{4}{3} = \frac{10}{9}$。

若 $n = 6m + 2$，此时 $m \geq 1$，则原式 $\displaystyle\geq \frac{n - 1}{n}\cdot \frac{2+3m}{1+2m} \geq \frac{7}{8}\cdot\frac{5}{3} = \frac{35}{24}$。

若 $n = 6m + 3$，此时 $m \geq 1$，则原式 $\displaystyle\geq \frac{n - 1}{n}\cdot \frac{2+3m}{2+2m} \geq \frac{8}{9}\cdot\frac{5}{4} = \frac{10}{9}$。

若 $n = 6m + 4$ 或 $6m + 5$，此时 $m \geq 0$，则原式 $\displaystyle\geq \frac{n - 1}{n}\cdot \frac{3+3m}{2+2m} \geq \frac{3}{4}\cdot\frac{3}{2} = \frac{9}{8}$。

证毕。

如果有简单证明请速速告诉我，我被这证明折磨麻了！

---

## 作者：ZhaoV1 (赞：1)

方法一：因为给的 $n$ 和 $x$ 范围很小，所以我们依照题意直接枚举得到答案。（见代码）

方法二：可证得，$n>3$ 的情况下，$x=2$ 的所有合理倍数的和一定最大，所以只需判断 $n$ 的范围即可。（无代码）

Code
------------

```cpp
int t,n,x;
void solve(){
	cin >> n;
	int index = 0;
	int res = 0;
	for(int i=2;i<=n;i++){
		int sum = 0;
		for(int j=i;j<=n;j+=i){
			sum += j;
		}
		if(sum > res){
			res = sum;
			index = i;
		}
	}
	cout << index << '\n';
}
```

---

## 作者：jess1ca1o0g3 (赞：0)

数据太小，直接暴力。

$i$ 从 $2$ 开始，求 $i+2i+3i+4i+⋯+ki$，直到 $ki>x$，然后更新最大的和以及对应的 $i$ 即可。

代码：

```cpp
#include<bits/stdc++.h>
#define i64 long long
#define L(a,b,c) for(register int i=a;i<=b;i+=c)
#define R(a,b,c) for(register int i=a;i>=b;i-=c)

using namespace std;

const int N=1e5+5,M=998244353;
int T;
void solve();

signed main(){
  
  ios::sync_with_stdio(0);
  cin>>T;
  
  while(T--){
    solve();
  }
  return 0;
}

void solve(){
  int n,ans1=-1e9,ans2=0;
  cin>>n;
  L(2,n,1){
    int sum=0,j=0;
    while(i*(++j)<=n){
      sum+=i*j;
    }
    if(sum>ans1) ans1=sum,ans2=i; 
  }
  cout<<ans2<<endl;
}
```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
预处理出 $100$ 以内的数的不超过 $100$ 的所有倍数，然后每次询问都将  $2 \sim n$ 的所有数的不超过 $n$ 的所有倍数加起来，如果比之前的最大值还要大，更新答案。
### 代码
```cpp
#include<iostream>
#include<climits>
#include<queue>
#include<map>
#define int long long
std::map<int,std::vector<int>>pre; 
void solve(int T){
	if(T==0)return;
	int n;
	std::cin>>n;
	int maxValue=LLONG_MIN,ans;
	for(int i=2;i<=n;i++){
		int temp=0;
		for(auto j:pre[i]){
			if(j<=n)temp+=j;
			else break;
		}
		if(temp>maxValue){
			ans=i;
			maxValue=temp;
		}
	}
	std::cout<<ans<<"\n";
	solve(T-1);
} 
signed main(){
	std::ios::sync_with_stdio(0);
	int T;
	std::cin>>T;
	for(int i=2;i<=100;i++){
		for(int j=i;j<=100;j+=i){
			pre[i].push_back(j);
		}
	}
	solve(T);
}
```

---

## 作者：LostKeyToReach (赞：0)

这道题是简单题，模拟即可，时间复杂度 $O(n \log n)$。

当然，直接可以用数学的方法直接优化到 $O(n)$，式子请读者自行推导。

代码如下：

```cpp
int check(int x, int n) {
    int res = 0, cnt = 0;
    while (cnt * x <= n) {
        res = res + (cnt + 1) * x;
        ++cnt;
    }
    if (res > n) res = res - cnt * x;
    return res;
}
int main() {
    int t;
    read(t);
    while (t--) {
        int n;
        read(n);
        int maxn = -1, pos = 0;
        FORL(i, 2, n, 1) {
           // cout << check(i, n) << endl;
            if (check(i, n) > maxn) {
                maxn = check(i, n);
                pos = i;
            }
        }
        writeln(pos);
    }
}
```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/CF1985B)
### 题目翻译
给定一个 $n$，寻找一个 $x$ 使得：
- $2\le x\le n$。
- 所有小于等于 $n$ 的 $x$ 的倍数的和最大。

输出这个 $x$。

**本题每个样例有 $t$ 组测试数据。**
### 思路
对于这道题，可以枚举 $x$ 的值，找到符合要求的 $x$。

显然，对于每一个 $x$ 直接暴力累加倍数和会 TLE。可以发现，对于任意一个数，它的倍数是一个等差数列，故可以用高斯求和法求和。所以可以得到，对于任意一个 $x$，所有小于等于 $n$ 的 $x$ 的倍数的和为：
$$\frac{(x+n-n\bmod x)\times(\frac{n-n\bmod x-x}{x}+1)}{2}$$
### Code
```cpp
#include<iostream>
using namespace std;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int t,n,ans,x,ma;
	cin>>t;
	while(t--) {
		cin>>n,ma=0;
		for(x=2;x<=n;++x) {//枚举x的值
			int sum=(x+n-n%x)*((n-n%x-x)/x+1)/2;//套入公式，int会自动向下取整
			if(sum>ma) ans=x,ma=sum;//比较大小
		}
		cout<<ans<<"\n";//输出答案，记得换行
	}
	return 0;
}
```

---

## 作者：FXLIR (赞：0)

### 题意

给你一个数 $n$，求出一个满足下面条件的数 $x$：

- $2 \leq x \leq n$。

- $x + 2x+ 3x + \dots +kx$ 最大。其中，$kx \leq n$。

### 做法

由于 $n$ 最大也只到 $100$，所以可以直接枚举 $x$ 解决。

观察到 $x + 2x+ 3x + \dots +kx$ 是一个等差数列，可以使用等差数列求和公式进行优化。其中，首项为 $x$，末项为 $kx$，项数为 $\lfloor n \div x \rfloor$。

### AC code
```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=1e5+5;
int t,n;
int sum(int x){
	return (x+n/x*x)*(n/x)/2;
}
int answer(int n){
	int num=0,maxx=0,ret=0;
	for(int i=2;i<=n;i++){
		num=sum(i);
		if(num>maxx){
			maxx=num;
			ret=i;
		}
	}
	return ret;
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		cout<<answer(n)<<"\n";
	}
	return 0;
}
```

---

## 作者：Dream_Mr_li (赞：0)

## 题目简述

$t$ 组数据，每组数据给定整数 $n$，求一个整数 $x$，使得：

- $2 \leq x \leq n$。

- 小于或等于 $n$ 的 $x$ 的倍数之和最大。形式上，$x + 2x + 3x + \dots + kx$（$kx \leq n$）在 $x$ 的所有可能值中最大。

## 思路

此题数据范围较小，直接暴力枚举可以通过此题，时间复杂度 $O(tn)$。

对于每一次询问，只需枚举每一个大于 $2$ 的 $x$，找出最大的 $\sum_{i=1}^{\frac{x}{i}} \times x$ 输出就可以了。

**注：在处理前缀和的时候可以用等差数列求和公式 $sum=\frac{n \times (n+1)}{2}$ 来优化时间复杂度。**

## 代码

```c++
#include<bits/stdc++.h>
#define TRACE 1
#define tcout TRACE && cout
#define int long long
#define endl '\n'
const int N=1e6+10;
using namespace std;
int t,n;
signed main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		int ans=0,mx=0;
		cin>>n;
		for(int i=2;i<=n;i++){
			if(((n/i)*(n/i+1)/2)*i>mx){
				mx=((n/i)*(n/i+1)/2)*i;
				ans=i;//更新答案
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：chenlongli (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1985B)
### 思路
本题可以暴力枚举 $x$，对于每个 $x$，序列必然为 $x,2x,3x,4x ⋯ cx$，且 $cx \le n$，我们可以将这个序列的所有元素相加，最后求出加和最大的那个 $x$ 即可。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin>>t;
    for (int i=0;i<t;i++)
    {
        int n;
        cin>>n;
        long long ans=0,x;
        for (int j=2;j<=n;j++)
        {
            long long sum=0;
            int c=1;
            while (j*c<=n)
            {
                sum=sum+j*c;
                c=c+1;
            }
            if (sum>ans)
            {
                ans=sum;
                x=j;
            }
        }
        cout<<x<<endl;
    }
}
```

---

## 作者：xiaoxiaoxia (赞：0)

# 题目大意
给定整数 $n$，求整数 $x$，使得：
- $2 \leq x \leq n$
- 小于或等于 $n$ 的 $x$ 的倍数之和最大。
# 思路
没什么说的，直接高斯求和暴力拿下。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
		int n, pos, cnt=-1;
		cin>>n;
		for(int i=2;i<=n;i++)
		{
			int maxn=0;
			int k=n/i;
			maxn=((1+k)*k/2)*i;
			if(maxn>cnt)
			{
				cnt=maxn;
				pos=i;
			}
		}
		cout<<pos<<endl;
	}
    return 0;
}
```

---

