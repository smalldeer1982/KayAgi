# Very Different Array

## 题目描述

Petya has an array $ a_i $ of $ n $ integers. His brother Vasya became envious and decided to make his own array of $ n $ integers.

To do this, he found $ m $ integers $ b_i $ ( $ m\ge n $ ), and now he wants to choose some $ n $ integers of them and arrange them in a certain order to obtain an array $ c_i $ of length $ n $ .

To avoid being similar to his brother, Vasya wants to make his array as different as possible from Petya's array. Specifically, he wants the total difference $ D = \sum_{i=1}^{n} |a_i - c_i| $ to be as large as possible.

Help Vasya find the maximum difference $ D $ he can obtain.

## 说明/提示

In the first example, Vasya can, for example, create the array $ (1, 5, 7, 2) $ . Then the total difference will be $ D = |6-1|+|1-5|+|2-7|+|4-2| = 5+4+5+2 = 16 $ .

In the second example, all the integers available to Vasya are equal to 1, so he can only create the array $ (1, 1, 1) $ , for which the difference $ D = 0 $ .

In the third example, Vasya can, for example, create the array $ (5, 4, 3, 2, 1) $ . Then the total difference will be $ D = |1-5|+|2-4|+|3-3|+|4-2|+|5-1| = 4+2+0+2+4 = 12 $ .

## 样例 #1

### 输入

```
9
4 6
6 1 2 4
3 5 1 7 2 3
3 4
1 1 1
1 1 1 1
5 5
1 2 3 4 5
1 2 3 4 5
2 6
5 8
8 7 5 8 2 10
2 2
4 1
9 6
4 6
8 10 6 4
3 10 6 1 8 9
3 5
6 5 2
1 7 9 7 2
5 5
9 10 6 3 7
5 9 2 3 9
1 6
3
2 7 10 1 1 5```

### 输出

```
16
0
12
11
10
23
15
25
7```

# 题解

## 作者：foryou_ (赞：11)

补充一个对本题贪心思路更（？）清楚的解释。

本题贪心思路：

- 在 $a_i,b_i$ 分别升序的情况下，对于每个 $a_i$，与它差值最大的 $b_i$ 只可能出现在 $b_{n-i+1}$ 与 $b_{m-i+1}$ 这两者中。

证明：

首先，假设我们有一个长度为 $n$ 的升序序列 $s$。

则对于 $s_1$，与它差值最大的元素为 $s_n$；

对于 $s_2$，与它差值最大的元素为 $s_{n-1}$。

于是综上，我们得到对于 $s_i$，与它差值最大的元素为 $s_{n-i+1}$。

同理，对于每个 $a_i$，与它差值最大的元素一定形如 $b_{x-i+1}$。

那么，在所有的形如 $b_{x-i+1}$ 的元素中，最小的一定是 $b_{n-i+1}$，最大的一定是 $b_{m-i+1}$。

原因如下：

- 首先，不会有比 $n-i+1$ 更小的下标，因为 $i$ 最大为 $n$。

- 其次，也不可能存在 $b_{x-i+1}$ 使得它小于 $b_{n-i+1}$ 且 $x>n$，因为 $b_i$ 升序。

同理也可得最大的一定是 $b_{m-i+1}$。

然后又因为只有最小值和最大值才能成为与 $a_i$ 差值最大的元素，所以对于每个 $a_i$，与它差值最大的 $b_i$ 只可能出现在 $b_{n-i+1}$ 与 $b_{m-i+1}$ 这两者中。

*证毕*。

代码非常好写，就不贴了。

---

## 作者：Pump_kin (赞：2)

我们对于这道题目，发现 $n,m\le 2\times 10^5$，那么我们考虑贪心。

我们发现，因为题目上有绝对值，所以，我们考虑让一个最大值，配上一个最小值，就可以了。

通过的代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t;
int a[200005],b[200005];
int read(){
	int ans=0;
	char op=getchar();
	while(op<'0'||op>'9'){
		op=getchar();
	}
	while(op<='9'&&op>='0'){
		ans=(ans<<3)+(ans<<1)+op-'0';
		op=getchar();
	}
	return ans;
}
long long ans;
int main(){
	t=read();
	while(t--){
		n=read(),m=read();ans=0;
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=m;i++)b[i]=read();
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		for(int i=1;i<=n;i++){
			ans+=(max(abs(a[i]-b[n-i+1]),abs(a[i]-b[m-i+1])));
		} 
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：梦应归于何处 (赞：2)

### 题目大意

一个人有一个长度为 $N$ 的序列，现在另一个人有一个长度为 $M(N\le M)$ 的序列，这个人想从 $M$ 个数中挑 $N$ 个组成一个序列让两个序列的差异最大。

设长度为 $N$ 的序列为 $a$，长度为 $M$ 个挑 $N$ 个的序列为 $b$。

则两个序列的差异为：

$$\sum_{i=1}^N |a_i-b_i|$$

现在你要使这两个串的差异最大。

### 思路

这道题得差异跟序列的顺序没有关系，所以我们可以先排序。

两个序列都排完序之后就会发现贪心结论：一定是原数组前面某一段用另一个数组的最大值，后面某一段用最小值。

然后我们预处理出两个数组，最后答案取最大值就可以了。

### 代码

~~~cpp
#include <bits/stdc++.h>
#define ll long long
#define ex exit(0)
#define _endl_ puts("");
#define inl inline
#define null NULL
#define pll pair<ll,ll>
#define mkp make_pair
using namespace std;
ll a[200005], b[200005];
ll f[200005], g[200005];
int main() {
	//freopen(".in","r",stdin);    1 2 4 6
	//freopen(".out","w",stdout);  7 5 2 1
	ll t;
	cin >> t;
	while (t--) {
		ll n, m;
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int j = 1; j <= m; j++) {
			cin >> b[j];
		}
		sort(a + 1, a + n + 1);
		sort(b + 1, b + m + 1);
		memset(f, 0, sizeof(f));
		for (int i = 1; i <= n; i++) {
			f[i] = f[i - 1] + abs(a[i] - b[m - i + 1]);
		}
		memset(g, 0, sizeof(g));
		for (int i = n; i >= 1; i--) {
			g[i] = g[i + 1] + abs(a[i] - b[n - i + 1]);
		}
		ll ans = 0;
		for (int i = 0; i <= n; i++) {
			ans = max(ans, f[i] + g[i + 1]);
		}
		cout << ans << endl;
	}
	return 0;
}
~~~

---

## 作者：FlyPancake (赞：1)

## [CF1921D Very Different Array](https://www.luogu.com.cn/problem/CF1921D) 题解

题意：给定一个长度为 $n$ 的序列 $a$，和一个长度为 $m$ 的序列 $b$，其中 $m≥n$。

在 $b$ 中选出 $n$ 个数以任意顺序组成序列 $c$，规定 $D=\sum _{i=1}^n \left\vert a_i-c_i \right\vert$，求 $D$ 的最大值。

## Ideas

考虑**贪心**，要使总和最大就要使每一项的数最大。因为有绝对值，所以要尽量让 $a_i$ 最大，$b_i$ 最小，或者让 $a_i$ 最小，$b_i$ 最大，这样每一项的差的绝对值才能最大。

每一项为以上两种情况的最大值。用变量存储输出即可。

注意答案要开 long long。
## Code

```
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5+5;

ll a[N], b[N];

int main() {
	int n, m, T; cin>>T;
    while(T--){
        cin>>n>>m; ll ans = 0;
        for(int i=1; i<=n; i++) cin>>a[i];
        for(int i=1; i<=m; i++) cin>>b[i];
        sort(a+1, a+1+n);
        sort(b+1, b+1+m);
        for(int i=1; i<=n; i++)
            ans += max(abs(a[i]-b[n-i+1]), abs(a[i]-b[m-i+1]));
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：mgcjade (赞：1)

# [CF1921D Very Different Array](https://www.luogu.com.cn/problem/CF1921D) 题解

## 题目大意

一个长度为 $n$ 的序列 $a$，和一个长度为 $m$ 的序列 $b$，其中 $1 \le n \le m \le 2×10^5,1 \le a_i,b_i \le 10^9$。

在序列 $b$ 中选出 $n$ 个数，以任意顺序组成序列 $c$，使得 $\sum_{i=1}^{n}\left|{a_i-c_i}\right|$ 最大。

## 思路

仔细阅读题目，发现：

- 以任意顺序；

- $m \ge n$。

看见了数据范围，就猜到单次时间复杂度约为 $O(n)$，所以考虑贪心。

贪心方法：

- 将 $a$ 的最大值和 $b$ 的最小值配对；

- 将 $a$ 的最小值和 $b$ 的最大值配对。

两种情况中取最大值。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e5 + 5;
int t;
int n, m;
int a[N], b[N];
ll ans;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= m; i++)
            cin >> b[i];
        sort(a + 1, a + n + 1);
        sort(b + 1, b + m + 1);
        ans = 0;
        for (int i = 1; i <= n; i++)
            ans += max(abs(a[i] - b[n - i + 1]), abs(a[i] - b[m - i + 1]));
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：Vct14 (赞：1)

### 题面翻译

给定一个长度为 $n$ 的序列 $a$ 和一个长度为 $m$ 的序列 $b$（$m≥n$）。

你需要是在 $b$ 中选出 $n$ 个数以任意顺序组成序列 $c$，输出 $\sum _{i=1}^n \left\vert a_i-c_i \right\vert$ 的最大值。多组测试数据。

### 思路

容易想到，用两个序列的最大值和最小值相减答案最大。因此将 $a$ 的最小值和 $b$ 的最大值依次相减，再将 $a$ 的最大值和 $b$ 的最小值依次相减，取两者较大值输出即可。

提示：一个长度为 $s$ 的数列 $A$，从小到大排序后第 $i$ 小的是 $A_i$，第 $i$ 大的是 $A_{s-i+1}$。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int a[N],b[N];
int mx[N],mn[N];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		for(int i=1; i<=n; i++) cin>>a[i];
		for(int i=1; i<=m; i++) cin>>b[i];
		sort(a+1,a+n+1);sort(b+1,b+m+1);
		for(int i=1; i<=n; i++) mx[i]=abs(a[i]-b[m-i+1]),mn[i]=abs(a[i]-b[n-i+1]);
		long long sum=0;
		for(int i=1; i<=n; i++) sum+=max(mx[i],mn[i]);
		cout<<sum<<"\n";
	}
	return 0;
}
```

---

## 作者：KyleShen1213 (赞：0)

## 题意
给定两个数组， $a$ 数组长度为 $n$ ，$b$ 数组长度为 $m$ 。
在 $b$ 数组中随意选取 $n$ 个元素组成长度为 $n$ 新数组 $c$ 。
要求 $D= {\textstyle \sum_{i=1}^{n}} \left | a_{i}-c_{i}   \right | $的值最大。
## 思路
明显是贪心。
要使总和最大就要使每一项的差最大。
我们让 $a$ 数组的最大值和 $b$ 数组的最小值做差，或让 $a$ 数组的最小值和 $b$ 数组的最大值做差，然后就可以取到最大值。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[200005],b[200005];
long long ans;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		ans=0;
		cin>>n>>m;//输入 
		for(int i=1;i<=n;i++)  cin>>a[i];
		for(int i=1;i<=m;i++)  cin>>b[i];
		sort(a+1,a+n+1);sort(b+1,b+m+1);//快排 
		for(int i=1;i<=n;i++)
		{
			ans+=((long long)max(abs(a[i]-b[n+1-i]),abs(a[i]-b[m+1-i])));//取最大值 
		}
		cout<<ans<<endl;//输出 
	} 
	return 0;
}
```
望管理员通过，谢谢！

---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1921D)

我们发现题目是求出 $\displaystyle \sum|a_i-c[i]|$ 的最大值。

我们考虑贪心，我们要使总和最大就要使每一项的数最大。

我们就可以让 $a$ 数组的最大值和 $b$ 数组的最小值做差，或者是让 $a$ 数组的最小值和 $b$ 数组的最大值做差，然后取最大值就可以了。

我们可以证明这个贪心是正确的。

那么代码如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+100;
int n,m,t;
int a[N],b[N];
#define ll long long
ll ans;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&m);
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<=m;i++)scanf("%d",&b[i]);
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		for(int i=1;i<=n;i++){
			ans+=((ll)max(abs(a[i]-b[n-i+1]),abs(a[i]-b[m-i+1])));
		}
		printf("%lld\n",ans);
		ans=0;
	} 
	return 0;
}
```

---

## 作者：Eternity_Yoke (赞：0)

## 题目大意
给定两个数组，$a$ 数组长度为 $n$，$b$ 数组长度为 $m$，$m\ge n$。

在 $b$ 数组中随意选取 $n$ 个元素组成长度为 $n$ 新数组 $c$。

要求 $D={\textstyle \sum_{i = 1}^{n}}\left | a_i - c_i \right |$ 的值最大。
## 解题思路
容易想到用 $a$ 数组的最小值与 $b$ 数组的最大值进行匹配。

但到了中间某处会存在更优解，即此时 $a_i$ 与 $b$ 数组的最小值匹配更优。

考虑进行两次遍历。

第一次用 $a$ 数组的最小值与 $b$ 数组的最大值依次匹配。

第二次用 $a$ 数组的最大值与 $b$ 数组的最小值依次匹配。

最终两次中 $i$ 位置 $D_i$ 值更大的对答案进行贡献。
## 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int t,n,m,x,y;
ll D;
int a[N],b[N],f1[N],f2[N];
int main()
{	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{	cin>>n>>m;
		for(int i=1;i<=n;i++)
		cin>>a[i];
		for(int i=1;i<=m;i++)
		cin>>b[i];
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		for(int i=1;i<=n;i++)
		{	f1[i]=abs(a[i]-b[m-i+1]);
			f2[i]=abs(a[i]-b[n-i+1]);
		}
		D=0;
		for(int i=1;i<=n;i++)
		D+=max(f1[i],f2[i]);
		cout<<D<<endl;
	}
	return 0;
}
```


---

## 作者：Addicted_Game (赞：0)


# [传送门](https://www.luogu.com.cn/problem/CF1921D)

### 题意
给定长为 $n$ 数组 $a$ 与长为 $m$ 的数组 $b$，从 $b$ 中选择 $n$ 个数组成数组 $c$。求 $\sum^n_{i=1} |a_i-c_i|$ 的最大值。

### 思路
明显的贪心题。

为了使差最大，就要将两个极端值（一最大一最小）相减。将 $a$ 数组的最大值与 $b$ 数组的最小值之差的和与 $b$ 数组的最大值与 $a$ 数组的最小值之差的和作比较取最大即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int n,m;
long long a[200005],b[200005];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
		}
		for(int i=1;i<=m;i++){
			scanf("%lld",&b[i]);
		}
		sort(a+1,a+n+1);
		sort(b+1,b+m+1);
		long long s=0;
		for(int i=1;i<=n;i++){
			s+=max(abs(b[n-i+1]-a[i]),abs(b[m-i+1]-a[i]));//取最优。
		} 
		printf("%lld\n",s);
	}
	return 0;
} 
```

---

## 作者：Weekoder (赞：0)

# CF1921D Very Different Array 题解
## 题意
给你一个长度为 $n$ 的序列 $a$，和一个长度为 $m$ 的序列 $b$，其中 $m≥n$。

你的任务是在 $b$ 中选出 $n$ 个数以任意顺序组成序列 $c$，使得 $D=\sum _{i=1}^n \left\vert a_i-c_i \right\vert$ 最大。输出 $D$ 即可。

## 分析
考虑将 $a$ 的最大值和 $b$ 的最小值配对，或者将 $a$ 的最小值和 $b$ 的最大值配对。在两种情况中取最大值，并求和。

先将两个数组排序，然后从 $1$ 循环到 $n$。假设 $a_i$ 为当前 $a$ 数组的较大值，那么就需要和与其相对的 $b_{n-i+1}$ 相减并取绝对值，还有一种情况是 $a_i$ 是较小值，那么就和 $b$ 数组的较大值 $b_{m-i+1}$ 配对。输出即可，需要开 long long。

# $\text{Code:}$
```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 2e5 + 5;

ll T, n, m, a[N], b[N];

int main() {
    cin >> T;
    while (T --) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) cin >> b[i];
        ll ans = 0;
        sort(a + 1, a + 1 + n);
        sort(b + 1, b + 1 + m);
        for (int i = 1; i <= n; i++)
            ans += max(abs(a[i] - b[n - i + 1]), abs(a[i] - b[m - i + 1]));
        cout << ans << "\n";
    }
    return 0;
}
```

---

