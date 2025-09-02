# [GCJ 2008 #1A] Minimum Scalar Product

## 题目描述

给定两个向量 $v_1 = (x_1, x_2, ..., x_n)$ 和 $v_2 = (y_1, y_2, ..., y_n)$。这两个向量的标量积是一个单一的数，计算方式为 $x_1y_1 + x_2y_2 + ... + x_ny_n$。

现在你可以任意排列每个向量的坐标。请选择两个排列，使得这两个新向量的标量积尽可能小，并输出这个最小的标量积。

## 说明/提示

**数据范围**

**小数据集（5 分，测试集 1 - 可见）**

- $T = 1000$
- $1 \leq n \leq 8$
- $-1000 \leq x_i, y_i \leq 1000$

**大数据集（10 分，测试集 2 - 隐藏）**

- $T = 10$
- $100 \leq n \leq 800$
- $-100000 \leq x_i, y_i \leq 100000$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
3
1 3 -5
-2 4 1
5
1 2 3 4 5
1 0 1 0 1```

### 输出

```
Case #1: -25
Case #2: 6```

# 题解

## 作者：abc1234shi (赞：5)

# 分析
题目就相当于给出两个序列，让你两个序列每次都各给出一个数，两两相乘。把积加起来，求这些积的和的最小值。

最小值这不一眼贪心吗？那要如何贪心呢？我们来分析分析。
# 前置知识
一个很常用的数学理论，两数和一定时，差越大，积越小。
# 思路
那么我们使每次相乘的数的差尽可能的大，那么它们的积就最小了，积最小了，所有积的和不就最小了吗？
# 思路实现
将两个序列，一个从大到小排序，一个从小到大排序。

接下来将每一项都拿出来相乘。因为两个序列一个从大到小，一个从小到大排序了。那么对于从大到小排序的序列，第一项最大，最后一项最小。对于从小到大排序的序列，第一项最小，最后一项最大。

那么每一项相乘就是当前从大到小排序的序列的最大值乘上当前从小到大排序的序列的最小值，不就满足我们的思路了吗？

再将所有相乘的积相加，不就是要求的答案了吗？

# 注意
- 乘积最大值 $10^{10}$，乘积最小值 $-10^{10}$，开 ```long long```。

- 如果你开的是全局数组，注意清空。

- 注意换行。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(long long a, long long b) {
	return a > b;
}
int main() {
	int T;
	cin >> T;
	for (int j = 1; j <= T; j++) {
		int n;
		cin >> n;
		long long a[805], b[805];
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];
		sort(a + 1, a + n + 1);
		sort(b + 1, b + n + 1, cmp);
		long long s = 0;
		for (int i = 1; i <= n; i++) s += a[i] * b[i];
		cout << "Case #" << j << ": " << s << '\n';
	}
	return 0;
}
```

---

## 作者：xyx404 (赞：3)

## 简要题意：

给定两个 vector，$v_1 = (x_1, x_2, \cdots, x_n)$ 和 $v_2 = (y_1, y_2,\cdots, y_n)$，要求最小化标量积 $x_1 \times y_1 + x_2 \times y_2+ \cdots + x_n \times y_n$，两个 vector 中的元素可以任意更改位置。

## 思路：

将 $v_1$ 和 $v_2$ 分别按升序和降序进行排序，然后计算即可。

证明在最后。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define itn int
#define ull unsigned long long
int T;
LL a[810],b[810];
int cnt;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>T;
    while(T--){
        cnt++;
        int n;cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        for(int i=1;i<=n;i++)cin>>b[i];
        sort(a+1,a+1+n);
        sort(b+1,b+1+n);
        LL ans=0;
        for(int i=1,j=n;i<=n;i++,j--){
            ans+=a[i]*b[j];
        }
        cout<<"Case #"<<cnt<<": "<<ans<<"\n";
    }
    return 0;
}
```

## 证明：

尽管比较显然，但我们还是证明一下，考虑反证法。

假设存在另一种配对方式，使得标量积比 $v_1$ 升序，$v_2$ 降序的配对方式更小。

设 $v_1$ 按升序排序 $x_1 \le x_2 \le \cdots \le x_n$，$v_2$ 降序排序 $y_1 \ge y_2 \ge \cdots y_n$，这样的标量积为 $S_1 = x_1 \times y_1 + x_2 \times y_2 + \cdots + x_n \times y_n$。

假设存在另一种配对方式，存在两个位置 $i$ 和 $j$，$x_i$ 和 $y_j$ 配对，$x_j$ 和 $y_i$ 配对，且这种配对的标量积 $S_2 < S_1$，则需要满足 $x_i \times y_i + x_j \times y_j > x_i \times y_j + x_j \times y_i$。

考虑两种配对方式带来的差异：

- $x_i$ 和 $y_i$ 配对，$x_j$ 和 $y_j$ 配对，和为 $x_i \times y_i + x_j \times y_j$。
- $x_i$ 和 $y_j$ 配对，$x_j$ 和 $y_i$ 配对，和为 $x_i \times y_j + x_j \times y_i$。

我们计算差值，以此比较大小：

![](https://cdn.luogu.com.cn/upload/image_hosting/fxb3x8la.png)

因此，不存在比 $v_1$ 升序，$v_2$ 降序的配对方式更小的标量积。

故代码正确。

---

## 作者：chenzefan (赞：3)

Update 2025/08/05：修改了一些语法错误。

[题目传送门](https://www.luogu.com.cn/problem/P13457)
## 前言
$3.00s$ 的水题，冲题解！
## 思路
简单的**贪心**题。

先上结论：将两数组分别升序和降序，然后计算答案最优。

证明：

- 方法一：观察样例可以得到结论。
- 方法二：由于我们小学学过，当一个矩形周长固定时，围成正方形面积最大，设矩形长宽分别为 $a$ 和 $b$，则在 $a+b$ 固定时，$ab$ 要想最大当且仅当 $a=b$ 时，简单描述为“**和同近积大**”。\
  于是将结论带入这道题，可以想到，当两个数大小关系确定时，两个数越接近，乘积越大。\
  可以得到结论。
- 方法三：不难想到，大的数乘大的数乘积越大，小的数乘小的数乘积越小，于是可以猜测到，不能让两个很大的数相乘，更进一步我们可以让最大的数乘上最小的数，这样可以将乘积降到最小。

然后，直接实现代码，把一个排列升序，一个降序，对应位相乘求和，即可。

显然这题需要开 long long。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
	int t,n,a[805],b[805],cnt=0;
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++) scanf("%lld",a+i);
		for(int i=1;i<=n;i++) scanf("%lld",b+i);
		sort(a+1,a+n+1);//升序
		sort(b+1,b+n+1,greater<int>());//降序
		int ans=0;
		for(int i=1;i<=n;i++) ans+=a[i]*b[i];
		printf("Case #%lld: %lld\n",++cnt,ans);
	}
	return 0;
}
```
~~顺便夸赞一下这题的满分分数。（$15$ 分？）~~

撒花！

---

## 作者：封禁用户 (赞：3)

# [P13457 [GCJ 2008 #1A] Minimum Scalar Product](https://www.luogu.com.cn/problem/P13457)
## 题目介绍：

本题要求找到两个向量在任意排列后的最小标量积。标量积的计算方式是将两个向量对应位置的元素相乘后相加。需要通过重新排列两个向量的元素顺序，使得它们的标量积达到最小。

## 分析做法：

要最小化标量积，我们需要让大的正数与大的负数相乘。这可以通过以下策略实现：

1. 将一个向量按升序排列。
2. 将另一个向量按降序排列。
3. 将对应位置的元素相乘后相加。

这种排列方式确保了最大的正数与最大的负数相乘，从而最小化总和。

奉上代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 805; 

int v1[N], v2[N];

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int T;
	cin >> T;
	for (int i = 1; i <= T; ++i) {
	    int n;
	    cin >> n; 
	    for (int j = 0; j < n; ++j) {
	        cin >> v1[j];
	    }
	    for (int j = 0; j < n; ++j) {
	        cin >> v2[j];
	    }
	    sort(v1, v1 + n);
	    sort(v2, v2 + n, greater<int>());
	    int ans = 0;
	    for (int j = 0; j < n; ++j) {
	        ans += v1[j] * v2[j];
	    }
	    cout << "Case #" << i << ": " << ans << endl;
	}
	return 0;
}
```

谢谢观看，求过求赞。

---

## 作者：alice_c (赞：2)

## 题意

有两个数组 $a$ 和 $b$，有 $n$ 次操作，每次你需要选择 $a_i$ 和 $b_j$，使 $\sum a_i b_j$ 最小。

## 思路

我们让最小的 $a_i$ 和最大的 $b_j$ 相乘，能使答案最小。

怎么证明呢？先考虑 $n=2$ 的情况，我们假设 $a_1 < a_2$ 且 $b_1 < b_2$，那么 $
(a_1 b_1 + a_2 b_2) - (a_1 b_2 + a_2 b_1) = (a_1 - a_2) (b_1 - b_2) > 0$。

所以我们可以把 $a$ 从小到大排序，把 $b$ 从大到小排序，让后让 $a_i$ 和 $b_i$ 相乘求和即可。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <functional>
using namespace std;
int T,n,a[805],b[805];
int main()
{
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&b[i]);
        sort(a+1,a+n+1);
        sort(b+1,b+n+1,greater<int>());
        long long ans=0;
        for(int i=1;i<=n;i++)
            ans+=1ll*a[i]*b[i];
        printf("Case #%d: %lld\n",t,ans);
    }
}
``````

---

## 作者：WsW_ (赞：2)

### 思路
感觉到，想要让结果尽可能小，得让最小的负数去乘最大的正数。  
所以猜测结论：若 $x_i$ 升序排列，则当且仅当 $y_i$ 降序排列时结果最小。  
显然这是贪心的思想，证明贪心的正确性一般使用**邻项交换法**。  
已知 $x_i<x_{i+1}$，$y_i>y_{i+1}$，交换 $y_i$ 与 $y_{i+1}$ 比较前后结果的大小。比较大小可以使用**作差法**。  

$$
\begin{aligned}
&(x_iy_{i+1}+x_{i+1}y_{i})-(x_iy_i+x_{i+1}y_{i+1}) \\
= &x_i(y_{i+1}-y_i)+x_{i+1}(y_{i}-y_{i+1}) \\
= &(x_{i+1}-x_i)(y_{i}-y_{i+1})>0
\end{aligned}
$$
所以交换后的结果比交换前的结果要大，交换前的结果已经是最优解。  

时间复杂度为 $O(Tn\log n)$。

---
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void work(){
	int n;cin>>n;
	vector<int>a,b;
	for(int i=0;i<n;i++){
		int x; cin>>x;
		a.push_back(x);
	}
	for(int i=0;i<n;i++){
		int x; cin>>x;
		b.push_back(x);
	}
	sort(a.begin(),a.end());
	sort(b.begin(),b.end());
	ll ans=0;
	for(int i=0;i<n;i++)ans+=(ll)a[i]*b[n-i-1];
	cout<<ans<<'\n';
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T; cin>>T;
	for(int i=1;i<=T;i++){
		cout<<"Case #"<<i<<": ";
		work();
	}
	return 0;
}
```

---

## 作者：Circle_Table (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13457)

翻译一下题意：每组测试样例给定 $x_1, x_2, ..., x_n$ 和 $y_1, y_2, ..., y_n$ 两个数列，需要你改变其顺序，使 $x_1y_1 + x_2y_2 + \cdots + x_ny_n$ 最小。

由二次函数知识，我们可以想到，两个数相隔得越远，其乘积越小。然而起决定性作用的是绝对值最大的两个数。于是我想到将这两个序列排序，一个升序，另一个降序，然后对应位上相乘，取乘积之和即可。想明白后实现方式倒也显而易见了。

## 代码如下

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ri register int
using namespace std;
const int inf=0x3f3f3f3f;
const int mod=998244353;
const int N=805;
int T,n;
ll a[N],b[N];

// 我是直接开的 long long 保险
signed main()
{
	scanf("%d",&T);
	for(ri qwq=1;qwq<=T;qwq++)
	{
		ll ans=0; // 多测清空
		scanf("%d",&n);
		for(ri i=1;i<=n;i++)
		{
			scanf("%lld",&a[i]);
		}
		for(ri i=1;i<=n;i++)
		{
			scanf("%lld",&b[i]);
		}
		sort(a+1,a+1+n);
		sort(b+1,b+1+n,greater<ll>());
        // a 数组为升序，b 数组为降序。
		for(ri i=1;i<=n;i++)
		{
			ans+=a[i]*b[i];
		}
		printf("Case #%d: %lld\n",qwq,ans);
	}
	return 0;
}
```

感谢阅读。

---

## 作者：Wangchenxi2013 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13457)
## 思路
一道贪心题，策略是将 $v_1$ 升序排序，$v_2$ 降序排列，以下给出证明。
## 证明
考虑 $n=2$，$v_1=(x_1,x_2)$，$x_1\leq x_2$。$v_2=(y_1,y_2)$，$y_1\leq y_2$。

需证明 $x_1y_2+x_2y_1\leq x_2y_2+x_1y_1$，即 $x_2(y_2-y_1)+x_1(y_1-y_2)\ge0$。

设 $y_2-y_1=k(k\ge0)$，则 $(x_2-x_1)k\ge0$。

$\because x_2\ge x_1$，$\therefore (x_2-x_1)k\ge0$，证毕。

当 $n\ge2$，每两个数都可以像如上排序，从而取到最小值。
## 代码
证明之后就可以按照贪心策略写出代码了：
```c++
#include<bits/stdc++.h>
using namespace std;
const int N=802;
long long t,n,a[N],b[N];
bool cmp1(int x,int y){
	return x<y;
}
bool cmp2(int x,int y){
	return x>y;
}
int main(){
	scanf("%lld",&t);
	for(int test=1;test<=t;test++){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",a+i);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",b+i);
		}
		long long sum=0;
		sort(a+1,a+1+n,cmp1);sort(b+1,b+1+n,cmp2); 
		for(int i=1;i<=n;i++){
			sum+=a[i]*b[i];
		}
		printf("Case #%d: %lld\n",test,sum);
	}
} 
```

---

## 作者：linhanmo (赞：1)

# 题解：[P13457 [GCJ 2008 #1A] Minimum Scalar Product](https://www.luogu.com.cn/problem/P13457)

为了使标量积尽量小，我们考虑贪心，将大的数乘以小的数，小的数乘以大的数。

## 证明

假设 $a_i<a_j$ 且 $b_i>b_j$。

则要证 $a_ib_i+a_jb_j<a_ib_j+a_jb_i$。

将两边重新排列：$a_ib_i+a_jb_j-a_ib_j-a_jb_i<0$。

合并同类项：$a_i(b_i-b_j)+a_j(b_j-b_i)$

提取公因式 $(b_i-b_j)$：$(a_i-a_j)(b_i-b_j)<0$

$\because a_i<a_j$（即 $a_i-a_j<0$） 且 $b_i>b_j$ （即 $b_i-b_j>0$）

$\therefore (a_i-a_j)(b_i-b_j)<0$。

## 算法流程

1. 将 $v_1$ 升序排序，将 $v_2$ 降序排序。
2. 求 $\sum_{i = 1}^n {v_1}_i{v_2}_i$。

## [AC](https://www.luogu.com.cn/record/227528934) code

```cpp lines=11-14
#include <bits/stdc++.h>
using namespace std;
#define F(i, t) for (int i = 1; i <= (t); ++i)
constexpr int N = 801; int n, v1[N], v2[N];
int main(void) {
    int t; scanf("%d", &t);
	F(cs, t) {
	    scanf("%d", &n);
	    F(i, n) scanf("%d", v1 + i);
	    F(i, n) scanf("%d", v2 + i);
	    sort(v1 + 1, v1 + n + 1);  // 升序排序
        sort(v2 + 1, v2 + n + 1, greater<int>()); // 降序排序 
        long long sum = 0; // 十年 OI 一场空，不开 long long 见祖宗
	    F(i, n) sum += 1ll * v1[i] * v2[i]; // 求和
	    printf("Case #%d: %lld\n", cs, sum);
	}
	return 0;
}
```

---

## 作者：Clouds_dream (赞：1)

### 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P13457)

### 题目分析
我首先想到的是暴力枚举所有可能的情况，但是在 $100 \le n \le 800$ 的约束条件下的效率是非常低下的。  
换一个思路。将这两个向量一个升序排列，一个降序排列，就可以得到这个最小的标量积。  
::::info[证明]
将向量排序后，确保了两个向量中最大数与最小数相乘。
::::
::::warning[注意]
十年 OI 一场空，不开 long long 见祖宗。
::::

### 代码实现
```cpp
#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

#define int long long

#define fst ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

void f(int t){
	int n;
	int ans=0;
	cin>>n;
	int a[n],b[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){
		cin>>b[i];
	}
	sort(a,a+n);
	sort(b,b+n,greater<int>());
	for(int i=0;i<n;i++){
		ans+=a[i]*b[i];
	}
	cout<<"Case #"<<t<<": "<<ans<<endl;
}

signed main()
{
	fst
	int t;
	cin>>t;
	for(int i=1;i<=t;i++){
		f(i);
	}
	return 0;
}
```

---

## 作者：Zjb13927701829 (赞：1)

# P13457 [Minimum Scalar Product](https://www.luogu.com.cn/problem/P13457) 题解
## 题目简述
题目给我们两个大小为 $n$ 的数组 $x$ 和 $y$，让我们对其重新排序，使得 $x_1 \times y_1 + x_2 \times y_2 + \dots x_n \times y_n$ 的值**最小**。
## 题目思路
在数学乘法运算中，存在这样一个公式：\
$\text{当 } a+b=c+d\text{ 且 }\left|a-b\right|>\left|c-d\right|$\
$\text{那么 }c\times d>a\times b$。

简单来说就是一个口诀：**和一定，差小积大；和一定，差大积小。**

所以我们要将 $x$ 和 $y$ 相同下标的元素的差**尽量的大**，也就是将 $x$ 升序排列、$y$ 降序排列（倒过来也可以），然后计算向量积。

到这一步问题就很好解决了，下面放出我的 [AC](https://www.luogu.com.cn/record/226940608) 代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int T;
    scanf("%d",&T);
    for(int cn=1;cn<=T;cn++){
        int n;
        scanf("%d",&n); //输入数据
        int x[n+10],y[n+10];
        for(int i=1;i<=n;i++)
            scanf("%d",&x[i]);
        for(int i=1;i<=n;i++)
            scanf("%d",&y[i]);
        sort(x+1,x+n+1); //排序
        sort(y+1,y+n+1,greater<int>());
        long long ans=0;
        for(int i=1;i<=n;i++) //计算最小向量积
            ans+=1ll*x[i]*y[i];
        printf("Case #%d: %lld\n",cn,ans);
    }
    return 0;
}
```

---

## 作者：chen_zhe (赞：1)

本题解来自于[《挑战程序设计竞赛》](https://www.luogu.com.cn/training/813583)。

---

$v_{1}$ 和 $v_{2}$ 各自的分量的顺序都可以任意交换，因此可以先把 $v_{1}$ 的顺序固定下来只交换 $v_{2}$ 的顺序。为了方便分析先将 $v_{1}$ 按升序排好序。接下来枚举 $v_{2}$ 的分量所有的排列顺序，一共有 $n!$ 种排列，还需要对每种排列计算内积，总的复杂度是 $O(n! \times n)$ 。这个算法在 Small 的情况，因为 $n \leqslant 8$ 所以没有问题，但在 Large 的情况时就远远不够了。

在此隐约会觉得把 $v_{2}$ 按降序或者升序排序的话，所得的内积是最小的。事实上，如果将 $v_{2}$ 按降序排序的话，所给的两个样例都能够得到最小值。这个设想的确是对的，$v_{1}$ 和 $v_{2}$ 的内积在将 $v_{1}$ 按升序，将 $v_{2}$ 按降序排序时取得最小值。下面我们来证明这一设想。首先考虑 $n=2$ 的情况。

考虑 $v_{1}=(x_{1}, x_{2})$ ，$v_{2}=(y_{1}, y_{2})$ ，假设 $v_{1}$ 已经按升序排好序了，即有 $x_{1} \leqslant x_{2}$ ，比较 $x_{1} \times y_{1} + x_{2} \times y_{2}$ 和 $x_{2} \times y_{1} + x_{1} \times y_{2}$ 的大小关系。

$x_{1} \times y_{1} + x_{2} \times y_{2} - x_{2} \times y_{1} - x_{1} \times y_{2} = x_{1} (y_{1} - y_{2}) + x_{2} (y_{2} - y_{1}) = (x_{1} - x_{2}) (y_{1} - y_{2})$

由此可知，$y_{1} \geqslant y_{2} \Leftrightarrow x_{1} \times y_{1} + x_{2} \times y_{2} \leqslant x_{2} \times y_{1} + x_{1} \times y_{2}$ 。因此 $n=2$ 时结论成立。

接下来考虑 $n$ 大于 2 的情况。如果 $v_{2}$ 不是按降序排序的，那么存在 $i < j$ 使得 $y_{i} < y_{j}$ ，根据对 $n=2$ 的情况的分析可以知道，交换 $y_{i}$ 和 $y_{j}$ 后就得到了更小的内积。因此，当将 $v_{2}$ 按降序排序时，所得的内积最小。

数组排序的复杂度为 $O(n \log n)$ ，所以发现这一结论后，只要做两次排序就可以简单高效地计算答案了。那么，要怎样才能去想到这个设想呢？

首先就是靠直觉。比较容易想到的姑且先排序试试看。

第二个就是样例。原本的问题描述中并没有说明 $v_{1}$ 和 $v_{2}$ 在什么情况下取得最小值。但是，因为样例的规模比较小，所以可以手工验算。因而可以找到使得内积最小的 $v_{1}$ 和 $v_{2}$ 。通过观察对应的 $v_{1}$ 和 $v_{2}$ ，想要得到刚才的结论也并不是那么难。

第三个就是像证明中的那样，从像 $n=2$ 这样小规模的情况出发，推广到一般的情况从而证明结论。在这个问题中，很容易证明对 $n=2$ 的情况结论成立，接着同样可以证明对一般的情况结论都成立。

最后需要注意的是，即使推导出了正确的算法，如果程序的实现中有漏洞的话也是徒劳。在这道题中，$v_{1}$ 的分量和 $v_{2}$ 的分量的乘积可能会导致 32 位整数溢出。即使认为找到了正解，不到最后提交结果正确的那一刻，都不能掉以轻心呢。

```cpp
typedef long long ll;

// 输入
int n;
int v1[MAX_N], v2[MAX_N];

void solve() {
    sort(v1, v1 + n);
    sort(v2, v2 + n);
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += (ll)v1[i] * v2[n - i - 1];
    printf("%lld\n", ans);
}
```

---

## 作者：TCY1234567 (赞：0)

### 题意

有两个数组 $a$ 和 $b$，它们的长度均为 $n$，每次你要在 $a$ 数组和 $b$ 数组中分别选一个数，然后将答案加上他们两个数相乘的乘积，已经选过的数无法再选，最后求出 $a$ 数组和 $b$ 数组这个答案的最小值。

### 题解

显然要让这个答案最小时，一定是要尽量保证不会存在大正数乘大正数或是大负数乘大负数。

所以考虑将 $a$ 数组升序排列，将 $b$ 数组降序排序。此时一定能保证是最大数乘最小数，决策一定最优。

### 正确代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1005],b[1005];
int main()
{
	int t;
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		int n;
		scanf("%d",&n);
		for(int j=1;j<=n;j++) scanf("%d",&a[j]);
		for(int j=1;j<=n;j++) scanf("%d",&b[j]);
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);//可以先正序排序，然后乘的时候下标设为 n-i+1 即可
		long long ans = 0;//观察数据范围，发现要开 long long
		for(int j=1;j<=n;j++)
		{
			ans+=1ll*a[j]*b[n-j+1];//计算
		}
		printf("Case #%d: %lld\n",i,ans);//输出
	}
}
```

---

## 作者：xiaowenxu_qwq (赞：0)

# 题目意思
给定两个数组 $v_1$ 和 $v_2$，求排序后他们的 calculated 的最小值是多少？calculated 定义为 $x_1y_1 + x_2y_2 + ... + x_ny_n$。
# 思路
我们可以利用数学中的[排序不等式](https://www.bilibili.com/video/BV1PC4y1272L/?vd_source=c03e731cf95abc789e8b118a4b29805d)来解这一道题。我们先将一个数组 $v_1$ 进行升序排列，再将另一个数组 $v_2$ 进行降序排列，最后将排列好的数组按位相乘并求和，结果即为最小的 calculated。

AC 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+c-'0',c=getchar();
	return x*f;
}//快读
bool cmp(int a,int b){
    return a>b;
}
int v1[1001];
int v2[1001];
signed main()
{
    int T=read(),t=0;
    while(T--){
        t++;
    	int n=read();
        int ans=0;//定义局部变量放止多测没清空
        for(int i=1;i<=n;i++)v1[i]=read();
        for(int i=1;i<=n;i++)v2[i]=read();
        sort(v1+1,v1+n+1);//升序排序
        sort(v2+1,v2+n+1,cmp);//降序排序
        for(int i=1;i<=n;i++){
            ans+=v1[i]*v2[i];
        }
        printf("Case #%lld: %lld\n",t,ans);//按照格式输出
    }
	return 0;
} 
```

---

