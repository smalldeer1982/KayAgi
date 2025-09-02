# [ABC058D] 井井井

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc058/tasks/arc071_b

$ 2 $ 次元平面上に $ x $ 軸と平行な直線が $ m $ 本と $ y $ 軸と平行な直線が $ n $ 本引いてあります。 $ x $ 軸と平行な直線のうち下から $ i $ 番目は $ y\ =\ y_i $ で表せます。 $ y $ 軸と平行な直線のうち左から $ i $ 番目は $ x\ =\ x_i $ で表せます。

この中に存在しているすべての長方形についてその面積を求め、 合計を $ 10^9+7 $ で割ったあまりを出力してください。

つまり、$ 1\leq\ i\ <\ j\leq\ n $ と $ 1\leq\ k\ <\ l\leq\ m $ を満たすすべての組 $ (i,j,k,l) $ について、  直線 $ x=x_i $, $ x=x_j $, $ y=y_k $, $ y=y_l $ で囲まれる 長方形の面積を求め、合計を $ 10^9+7 $ で割ったあまりを出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ n,m\ \leq\ 10^5 $
- $ -10^9\ \leq\ x_1\ <\ ...\ <\ x_n\ \leq\ 10^9 $
- $ -10^9\ \leq\ y_1\ <\ ...\ <\ y_m\ \leq\ 10^9 $
- $ x_i,\ y_i $ は整数である。

### Sample Explanation 1

この入力を図にすると、以下のようになります。 !\[sample1-1\](https://atcoder.jp/img/arc071/aec4d5cc2e5c73dbee455be237a649a5.png) 長方形 A,B,...,I それぞれの面積を合計すると $ 60 $ になります。 !\[sample1-2\](https://atcoder.jp/img/arc071/f0771c0f7e68af2b00e7513186f585ff.png)

## 样例 #1

### 输入

```
3 3
1 3 4
1 3 6```

### 输出

```
60```

## 样例 #2

### 输入

```
6 5
-790013317 -192321079 95834122 418379342 586260100 802780784
-253230108 193944314 363756450 712662868 735867677```

### 输出

```
835067060```

# 题解

## 作者：xibaohe (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc071_b)


------------


# 题目大意
给你若干条横或竖着的直线，求出由这些直线围成的所有长方形的面积之和。


------------


# 题目思路
这道题最简单的思路就是 $4$ 层循环暴力枚举矩形的四个点，但只有 $12$ 分，下面出示的是暴力代码，思路简单，不再解释。

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
long long n,m,x[100005],y[100005],ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>x[i];
	}
	for(int i=1;i<=m;i++)
	{
		cin>>y[i];
	}
	for(int xa=1;xa<=n;xa++)
	{
		for(int xb=xa+1;xb<=n;xb++)
		{
			for(int ya=1;ya<=m;ya++)
			{
				for(int yb=ya+1;yb<=m;yb++)
				{
					ans+=(x[xb]-x[xa])*(y[yb]-y[ya]);
				}
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


------------


# 时间效率优化
为了优化时间效率，我们可以求矩形总共的长和宽，最后再相乘。推导过程如下：

![推导过程](https://cdn.luogu.com.cn/upload/image_hosting/umzdhauy.png)

![推导过程](https://cdn.luogu.com.cn/upload/image_hosting/t271obw2.png)



------------


# 满分代码

```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;

const int MOD = 1e9 + 7;
int n, m, x[100005], y[100005];

int main()
{
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> x[i];
	for(int i = 1; i <= m; i++) cin >> y[i];
	
	long long sumx = 0, sumy = 0; //所有矩形的长之和sumx， 宽之和sumy
	for(int i = 1; i <= n; i++)
		sumx = (sumx + (long long)(2*i-1-n) * x[i]) % MOD;
	for(int i = 1; i <= m; i++)
		sumy = (sumy + (long long)(2*i-1-m) * y[i]) % MOD;
	
	cout << (sumx * sumy) % MOD << endl;
	
	return 0;
}
```


---

## 作者：TonyYin (赞：3)

## $\rm{Description}$

在平面直角坐标系中，给定 $n$ 条平行于 $y$ 轴的线和 $m$ 条平行于 $x$ 轴的线，求由这些线组成的矩形的面积和。

## $\rm{Solution}$

### $\rm{subtask}$ $\rm{1}$ 

考虑暴力做法，枚举矩形的左上角和右下角，也就是求：
$$
\sum_{1\leq i\leq j\leq n}\sum_{1\leq k\leq l\leq m}(x_j-x_i)\cdot(y_l-y_k)
$$
时间复杂度是 $\mathcal{O}(n^2m^2)$ .

### $\rm{subtask}$ $\rm{2}$

对于任意一个矩形，想要确定它，只需要固定一条平行于 $x$ 轴的线段和一条平行于 $y$ 轴的线段。

所以最终的答案可以写成：
$$
\sum_{i\leq i\leq j\leq n}(x_j-x_i)\sum_{1\leq k\leq l\leq m}(y_l-y_k)
$$
记 $A=\sum\limits_{1\leq i\leq j\leq n}(x_j-x_i)$，$B=\sum\limits_{1\leq k\leq l\leq m}(y_l-y_k)$，那么我们可以分开计算 $A$ 和 $B$。也就是分别计算：所有**平行于 $x$ 轴的线段长度和**，以及所有**平行于 $y$ 轴的线段长度和**。

这样可以得到 $\mathcal{O}(n^2)$ 级别的算法。

### $\rm{subtask}$ $\rm{3}$

#### 思路：

对于满分做法，我们期望 $\mathcal{O}(n)$ 的算法，现在想要进一步简化上面的式子。

考虑如何快速求出所有**平行于 $x$ 轴的线段长度和**。容易想到，我们只需要统计每条小线段被算了几次。显然对于线段 $(x_{i-1}, x_{i})$，被计算了 $(i - 1) \times(n-i-1)$ 次，于是我们就有了线性的做法。

对于平行于 $y$ 轴的线段，计算方法完全相同。

**如果到此为止您看懂了，那可以直接看代码了，如果没看懂，请看下面这部分。**

#### 具体地：

定义一个线段是**基本线段**，当且仅当线段的两个端点**之间不存在另一个端点**，那么我们可以将每条线段拆成基本线段的和的形式，之后分别计算每条基本线段的贡献。

比如：

![](https://gitee.com/TonyYin0418/Typora/raw/master/image/geogebra-export.png)


对于这张图，线段长度和为 $|AB|+|AC|+|AD|+|BC|+|BD|+|CD|$.

那么我们将上图中每个线段表示成**基本线段的和**的形式，比如 $|AC|=|AB|+|BC|$，整理之后即：
$$
3|AB|+4|BC|+3|CD|
$$
现在考虑如何计算每条基本线段的贡献。

根据小学数学知识，线段 $(x_i, x_{i - 1})$ 被算的次数是 $(i-1)\times (n - i - 1)$ ，这样我们就能 $\mathcal{O}(n)$ 地算出平行于 $x$ 轴的线段长度和。

对于平行于 $y$ 轴的，用同样的方法计算。

## $\rm{Code}$

```cpp
#include <bits/stdc++.h>
#define int long long
#define MAXN 100008
using namespace std;
int n, m, x[MAXN], y[MAXN];
int A, B; //A为所有平行于 x 轴的线段长度和，B为平行于 y 轴的线段长度和
const int mod = 1e9 + 7;
signed main() {
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; i++) scanf("%lld", &x[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &y[i]);
	sort(x + 1, x + n + 1); //横纵坐标升序排序
	sort(y + 1, y + m + 1);
	for(int i = 2; i <= n; i++) { //计算与x轴平行的所有线段的长度和
		A = (A + (x[i] - x[i - 1]) * (i - 1) * (n - i + 1)) % mod;
	}
	for(int i = 2; i <= m; i++) {
		B = (B + (y[i] - y[i - 1]) * (i - 1) * (m - i + 1)) % mod;
	}
	printf("%lld\n", A * B % mod);
	return 0;
}
```

---

## 作者：STARSczy (赞：2)

# 思路：
我的做法似乎与其他人的不一样。

这道题按题意枚举时间复杂度是 $\Theta(n^2m^2)$ 的时间复杂度，但是我们可以得出答案 $ans=(\sum\limits_{i=1}^{i \le n}\sum\limits_{j=0}^{j \le n-i} x_{i+j}-x_j)\times(\sum\limits_{i=1}^{i \le n}\sum\limits_{j=0}^{j \le n-i} y_{i+j}-y_j)$，详细的证明可以去看别人的题解，这里部详细阐述。使用前缀和就是 $\Theta(n^2)$ 的时间复杂度。

看了楼下的代码，都是得到这个式子了之后进一步在数学角度优化的，而我是从代码的角度进行优化。

我们现在先在这一阶段上打个暴力。主要部分：

```cpp
for(int i=1;i<=n;++i) for(int j=0;j<=n-i;++j) aans=(aans+aq[i+j]-aq[j])%mod;
for(int i=1;i<=m;++i) for(int j=0;j<=m-i;++j) bans=(bans+bq[i+j]-bq[j])%mod;
```

虽然会 TLE，但是我们可以化简得：

```cpp
for(int i=1;i<=n;++i){
	for(int j=i;j<=n;++j) aans=(aans+aq[j])%mod;
	for(int j=0;j<=n-i;++j) aans=(aans-aq[j]+mod)%mod;
}
for(int i=1;i<=n;++i){
	for(int j=i;j<=n;++j) bans=(bans+bq[j])%mod;
	for(int j=0;j<=n-i;++j) bans=(bans-bq[j]+mod)%mod;
}
```

因此，我们可以直接地看出此时应再套一层前缀和优化，即二重前缀和，详细见代码。

# 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=1e5+10,mod=1e9+7;
int n,m,aans,bans,a[maxn],b[maxn],
aq[maxn],bq[maxn]/*第一重前缀和数组*/,
ap[maxn],bp[maxn]/*第二重前缀和数组*/;

signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i) scanf("%lld",a+i);
	for(int i=1;i<=m;++i) scanf("%lld",b+i);
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	for(int i=1;i<n;++i) aq[i]=aq[i-1]+a[i+1]-a[i];
	for(int i=1;i<m;++i) bq[i]=bq[i-1]+b[i+1]-b[i];
	n--,m--;
	
	//优化部分
	for(int i=1;i<=n;++i) ap[i]=(ap[i-1]+aq[i])%mod;
	for(int i=1;i<=m;++i) bp[i]=(bp[i-1]+bq[i])%mod;
	for(int i=1;i<=n;++i) aans=((aans+ap[n]-ap[i-1]-ap[n-i])%mod+mod)%mod;//直接使用二重前缀和计算
	for(int i=1;i<=m;++i) bans=((bans+bp[m]-bp[i-1]-bp[m-i])%mod+mod)%mod;
	
	cout<<(aans*bans+mod)%mod;
	return 0;
}
```

---

## 作者：_Above_the_clouds_ (赞：0)

# 思路：
求所有矩阵面积和，就用二重前缀和。

所以，如何用二重前缀和呢？

众所周知，前缀和就是前 $i-1$ 个数的和加上第 $i$ 个数，也就是 $s_i=s_{i-1}+a_i$。

拓展到二重前缀和，就需要考虑两个坐标轴，那么对于每一个点的值就是：$(x_i-x_{i-1})\times(i-1)\times(n-i+1)$，$y$ 轴的值也是同理，最后输出 $x$ 的前缀和与 $y$ 轴的前缀和的乘积即可。

# 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m;
long long ans,sumx,sumy;
long long x[100005],y[100005];
int main() {
	cin>>n>>m;//输入
	for(int i=1; i<=n; i++) cin>>x[i];
	for(int i=1; i<=m; i++) cin>>y[i];
	for(int i=2; i<=n; i++) sumx=(sumx+(x[i]-x[i-1])*(i-1)*(n-i+1))%mod;//二维前缀和
	for(int i=2; i<=m; i++) sumy=(sumy+(y[i]-y[i-1])*(i-1)*(m-i+1))%mod;
	ans=(sumx*sumy)%mod;
	cout<<ans;//输出
	return 0;
}
```

---

## 作者：shaozhehan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/AT_arc071_b)

[AtCoder 链接](https://atcoder.jp/contests/abc058/tasks/arc071_b)

题目大意：

在平面直角坐标系中，给你 $n$ 条平行于 $x$ 轴的直线（第 $i$ 条直线的坐标为 $x_i$）和 $m$ 条平行于 $y$ 轴的直线（第 $i$ 条直线的坐标为 $y_i$），求这些直线组成的所有的长方形的面积。

思路：

显然，由第 $i$ 条和第 $j$ 条平行于 $x$ 轴的线和第 $k$ 条和第 $l$ 条平行于 $y$ 轴的线组成的长方形的面积为 $|x_i-x_j||y_k-y_l|$。由此可以得出，答案就是 $x$ 和 $y$ 升序排列后 $\sum\limits_{1\leq i<j\leq n}\sum\limits_{1\leq k<l\leq m}(x_j-x_i)(y_l-y_k)$。暴力解法求出答案的时间复杂度为 $\mathcal{O}(n^2m^2)$，明显超时。我们需要考虑时间复杂度更低的算法。

我们可以简化上述式子。显然，$x_j-x_i=\sum\limits_{k=i}^{j-1}(x_{k+1}-x_k)$。考虑包含 $x_{i-1}$ 和 $x_i$ 组成的线段的数量。我们可以选取左端点和右端点，可以得知共有 $(i-1)(n-i+1)$ 条线段符合上述要求。同理，包含 $y_{i-1}$ 和 $y_i$ 组成的线段的数量是 $(i-1)(m-i+1)$。这样，我们可以分别暴力枚举两个式子中的 $i$，求和并求出乘积，最后输出。（具体细节见代码）

坑点：

1. $x$ 和 $y$ 序列需要升序排列才能进行计算！
1. 答案要对 $10^9+7$ 取模！
1. 我们需要时时刻刻取模，以防炸精度！
1. 全程开 ```long long```，否则会炸精度！

上代码：
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int mod = 1e9 + 7;
int x[100001], y[100001];

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);// cin、cout 加速
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        cin >> x[i];
    }
    for (int i = 1; i <= m; i++){
        cin >> y[i];
    }
    sort(x + 1, x + n + 1);// x 和 y 序列升序排列
    sort(y + 1, y + m + 1);
    long long sum1 = 0, sum2 = 0;
    // x 序列的公式求和
    for (int i = 2; i <= n; i++){
        sum1 = (sum1 + 1ll * (i - 1) * (n - i + 1) % mod * (x[i] - x[i - 1]) % mod) % mod;// 时时刻刻取模
    }
    // y 序列的公式求和
    for (int i = 2; i <= m; i++){
        sum2 = (sum2 + 1ll * (i - 1) * (m - i + 1) % mod * (y[i] - y[i - 1]) % mod) % mod;// 时时刻刻取模
    }
    cout << sum1 * sum2 % mod << "\n";// 求出乘积，取模，输出
    return 0;
}
```

---

