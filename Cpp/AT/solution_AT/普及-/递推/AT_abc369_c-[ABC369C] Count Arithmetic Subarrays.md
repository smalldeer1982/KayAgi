# [ABC369C] Count Arithmetic Subarrays

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc369/tasks/abc369_c

長さ $ N $ の正整数列 $ A=(A_1,A_2,\dots,A_N) $ が与えられます。

$ 1\leq\ l\leq\ r\leq\ N $ を満たす整数の組 $ (l,r) $ であって、数列 $ (A_l,A_{l+1},\dots,A_r) $ が等差数列であるようなものが何通りあるか求めてください。

なお、数列 $ (x_1,x_2,\dots,x_{|x|}) $ が等差数列であるとは、ある $ d $ が存在して $ x_{i+1}-x_i=d\ (1\leq\ i\ <\ |x|) $ であることをいいます。 特に、長さ $ 1 $ の数列は常に等差数列です。

## 说明/提示

### 制約

- $ 1\leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力は全て整数
 
### Sample Explanation 1

条件を満たす整数の組 $ (l,r) $ は $ (1,1),(2,2),(3,3),(4,4),(1,2),(2,3),(3,4),(1,3) $ の $ 8 $ 通りです。 実際、$ (l,r)=(1,3) $ のとき $ (A_l,\dots,A_r)=(3,6,9) $ は等差数列なので条件を満たしますが、 $ (l,r)=(2,4) $ のとき $ (A_l,\dots,A_r)=(6,9,3) $ は等差数列ではないので条件を満たしません。

### Sample Explanation 2

すべての整数の組 $ (l,r)\ (1\leq\ l\leq\ r\leq\ 5) $ が条件を満たします。

## 样例 #1

### 输入

```
4
3 6 9 3```

### 输出

```
8```

## 样例 #2

### 输入

```
5
1 1 1 1 1```

### 输出

```
15```

## 样例 #3

### 输入

```
8
87 42 64 86 72 58 44 30```

### 输出

```
22```

# 题解

## 作者：PineappleSummer (赞：7)

[[ABC369C] Count Arithmetic Subarrays](https://www.luogu.com.cn/problem/AT_abc369_c)

很多同学因为这题卡了，纷纷表示 C 比 D 难，那么我就来分享一个 C 题的简单做法。

我们记 $b_i$ 表示以第 $i$ 个点结尾的等差数列的最大长度。那么 $b_1=1,b_2=2$。

$i$ 从 $3$ 到 $n$ 枚举，考虑 $b_i$ 如何得到。发现以第 $i-1$ 个点为结尾的等差数列后想要加上第 $i$ 个点，必须满足 $a_i-a_{i-1}=a_{i-1}-a_{i-2}$，此时 $b_i=b_{i-1}+1$。

如果不满足此条件，$b_i$ 为 $2$。此时以第 $i$ 个点为结尾的等差数列只有 $a_{i-1}$ 和 $a_i$ 两个数。

答案即为 $\sum\limits_{i=1}^nb_i$。

```cpp
signed main () {
    ios::sync_with_stdio (false);
    cin.tie (0); cout.tie (0);
    
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    b[1] = 1, b[2] = 2;
    for (int i = 3; i <= n; i++) {
        if (a[i] - a[i - 1] == a[i - 1] - a[i - 2])
            b[i] = b[i - 1] + 1;
        else b[i] = 2;
    }
    for (int i = 1; i <= n; i++) ans += b[i];
    cout << ans;
    return 0;
}
```

记得开 `long long`。

---

## 作者：ikunTLE (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc369_c)

### 思路

开一个变量表示当前等差数列的长度，设其为 $X$。设记录答案的变量为 $S$。

对于第 $i$ 个点，若 $A_i-A_{i-1}=A_{i-1}-A_{i-2}$，说明等差数列长度增加，即 $X\gets X+1$。否则将 $X$ 变为 $2$，因为任意 $2$ 个数都会组成一个等差数列，并用**等差数列求和公式**更改 $S$ 的值，即 $S\gets S+\frac{X^2+X}{2}$。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=2e5+10;
int a[N];
int main(){
	int n=read();
	if(n==1)
		return printf("1\n"),0;
	for(int i=1;i<=n;++i)
		a[i]=read();
	int cnt=1;
	long long ans=n;
	for(int i=2;i<=n;++i)
		if(i>2&&a[i]-a[i-1]==a[i-1]-a[i-2])
			++cnt;
		else{
			ans+=(long long)cnt*(cnt-1)/2;
			cnt=2;
		}
	ans+=(long long)cnt*(cnt-1)/2;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：woden (赞：3)

## 题意简述

给你一个序列，求出这个序列的所有子串中等差数列的个数。

## 思路

暴力枚举肯定是会超时的，我们考虑用时间复杂度 $O(n)$ 的方法解决。

通过观察，我们可以发现：对于每一段等差数列，它的每一个子串都是等差数列，所以我们每次找出一整段数列，求出**它的非空子串的个数**即可。

所以我们可以用双指针来解决这个问题，每次固定左端点，右端点一直增加直到序列不为等差数列为止。

另外还要注意：左右指针之间的差值至少为 $1$（就是说，序列长度至少为 $2$ ），否则无法记录数列公差，就会产生许多 bug。

还有很多细节，在代码中讲解。
## 代码实现
代码如下：
```cpp
#include<bits/stdc++.h>
#define int long long
#define fst ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
using namespace std;
const int N=2E5+99;
int n,a[N];
int sum=0;
signed main() {
	fst;
	cin>>n;
	if(n==1){
		cout<<1;//特判一下。 
		return 0;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=1,r=2,d=a[2]-a[1];//设置左端点和右端点，记录公差。 
	while(r<=n){
		if(a[r]-a[r-1]==d){
			r++;//如果是等差数列，右端点继续右移。 
		}else{//否则： 
			int len=r-l; //注意，这里的右端点不是序列的右端点，要比序列的右端点多1，所以要减去这个1。 
			sum+=(len+1)*len/2;//统计子串个数的公式：(序列长度+1)*(序列长度)/2。 
			l=r-1;//左端点移到当前序列的末尾。 
			d=a[r]-a[l];//更新公差。 
			/*
			假如每次的l,r变化如下：
			1,3
			3,7
			7,9
			我们会发现，除最后一次计算以外，每次都会多计算一个子串：a[r]（也就是下一个子串的左端点）。 
			所以我们要减去重复计算的部分（共有 计算次数-1 次重复）。 
			*/ 
			sum--;
		}
	}
	//最后进行一次计算。 
	int len=r-l;
	sum+=(len+1)*len/2;
	//这里不会再重复了，所以不用减1。 
	cout<<sum;
	return 0;
}
```

---

## 作者：Infinity_Fantasy (赞：2)

根据题意答案至少有 $2n-1$ 为 $n$ 个数和 $n-1$ 个间隙，为长度是 1 或 2 的序列。考虑到如果 $a_1\dots a_m$ 是等差序列，那么 $a_2\dots a_m$ 也是等差序列。也就是说当考虑到 $a_k$ 时 $a_1\dots a_k$ 仍满足条件，那么第 k 位对答案的贡献就是 $k$。这一段的贡献不难发现可以用高斯求和算出来，于是就有了代码。

~~~cpp
#include<bits/stdc++.h>
using namespace std;
long long n,c,ans,l,a[200005];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;ans=n+n-1;
	for(int i=1;i<=n;i++) cin>>a[i];c=a[1]-a[2];
	for(int i=3;i<=n;i++){
		if(a[i-1]-a[i]==c) l++,ans+=l;
		else c=a[i-1]-a[i],l=0;
	}
	cout<<ans;
	return 0;
}
~~~

---

## 作者：fire_and_sweets (赞：1)

本题思路非常简单。

我们考虑预处理出所有的极长等差数列子串。定义一个等差数列子串是极长的，当且仅当他的左端点左移或右端点右移后，他不再是一个极长等差数列。而我们可以用 $\Theta(n)$ 的时间预处理出这些等差数列，扫一遍即可。

预处理之后，我们发现我们可以利用公式计算出一个极长等差数列子串中包含多少个 **子** 极长等差数列子串。

于是便做完了。总复杂度 $\Theta(n)$。

有点坑的一个地方是，如果像我一样实现不是很完美的话，需要特判一下 $n=1$ 的情况。

具体见代码吧，尤其是预处理的部分。

```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010; 
int diff[N], a[N], n, res;
signed main()
{
	cin >> n;
	for (int i = 1; i <= n; i ++ ) cin >> a[i];
	if (n == 1)
	{
		cout << 1;
		return 0;
	}
	for (int i = 1; i <= n; i ++ ) diff[i] = a[i + 1] - a[i];
	int l = 1, r = 1;
	for (int i = 2; i < n; i ++ )
	{
		if (diff[i] != diff[l])
		{
			int len = r - l + 1;
			res += len * (len + 1) / 2;
			l = r = i;
		}
		else r = i;
	}
	int len = r - l + 1;
	res += len * (len + 1) / 2;
	cout << res + n;
	return 0;
} 
```

---

## 作者：Redamancy_Lydic (赞：1)

很水的一道题，但是硬控我半个小时呜呜呜。

它问等差数列的数量，我们发现只要找到所有的等差数列，那么答案一定包含在这些数列的连续子序列中。

求所有等差数列显然可以线性，我们求出每个等差数列的长度 $n$，那么连续子序列个数即为 $n(n+1)\over 2$。

至于求的话我定义了两个指针，每次满足差相等的话右指针右移，否则统计答案，重新赋值指针即可。

给出我的代码：

```cpp
for(int i=2;i<=n;i++)
	{
		if(a[i]-a[i-1]==cha)r++;
		else
		{
			num=r-l+1;
			ans=ans+pre[num];
			l=i-1;
			r=i;
			cha=a[i]-a[i-1];
		}
	}
```

但是单纯做的话答案不是正确的，因为指针重新赋值的话计算答案时当前等差数列末尾元素会重复计算，所以需要统计累加答案的次数最后减去消除影响。

还有一点细节，上面的循环做完以后最后需要再操作一次计算最后一个等差数列的贡献。

然后就做完了。

[提交记录](https://atcoder.jp/contests/abc369/submissions/57300368)

---

## 作者：GreenMelon (赞：1)

## 题目翻译

有一个长度为 $n$ 的序列 $A$，你需要找出 $A$ 中所有的子串中有多少个等差数列。

## 题目分析

我们可以先求出 $A_{i}-A_{i-1}$ 的值存进数组 $b$，后面一个一个去比较，最初 $l$ 等于 $2$，如果此时的 $b_i$ 不等于 $b_{i-1}$，则需要加上 $A$ 的上一个开始的位置至 $A_{l}$ 中的所有子串个数，也就是 $\cfrac{l(l+1)}{2}$，因为最后会和下一个等差数列重复，所以要减去 $1$。然后 $l$ 重新赋值为 $2$。否则 $l$ 一直加上 $1$。

[code](https://atcoder.jp/contests/abc369/submissions/57345042)

---

## 作者：Happy_mouse (赞：1)

# [Count Arithmetic Subarrays](https://www.luogu.com.cn/problem/AT_abc369_c) 题解
[AC证明](https://www.luogu.com.cn/record/175554667)
## 题目大意
求正整数列 $A$ 的所有子串中有多少个等差数列。
## 分析与解答
不知道[等差数列](https://blog.csdn.net/wanghai2018/article/details/140765965)是什么的，赶紧加餐喵。

发现只要一个数列为等差数列，其所有子串均为等差数列。因此只需求出从上一次位置开始的最长等差数列的长度（公差变一次就重新统计长度），然后计算其子串个数，统计即可。

以样例 3 为例。
![](https://cdn.luogu.com.cn/upload/image_hosting/uic8y8d4.png)
如图所示，可以分出三段最长的等差数列。

而如何计算定长数列的子串个数呢？设原数列长度为 $len$，则子串个数为 $sum$，则：
$$
\begin{aligned}
  sum &=\sum_{l=1}^{len} \sum_{r=l}^{len} 1\\
      &=\sum_{l=1}^{len} (len-l+1)\\
      &=\sum_{x=1}^{len} x\\
      &=\frac{len\times (len+1)}{2}
\end{aligned}
$$

思路不太难，来看看如何实现。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+2;
int a[N];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int c=a[2]-a[1],cnt=0,len=2;
	//c 代表当前公差
	//cnt 代表当前计算到的等差数列数
	//len 代表当前等差数列的长度
	//因为两个数一定能组成一个等差数列，因此赋值为 2
	a[n+1]=1e15;//这里赋值是为了保证最后一段等差数列也被计算
	for(int i=2;i<=n;i++){
		if(c==a[i+1]-a[i]) len++;//如果与下一项的差与公差相等，那么增加长度
		else{//否则
			cnt+=(len*(len+1))>>1;//计算子串个数并进行累加
			cnt--;
			//上面那一行很重要，因为当前的最后一位
			//形成的等差数列会跟下一个等差数列的
			//第一位算重复，因此要减一
			len=2;//重新对长度赋值
			c=a[i+1]-a[i];//改变公差
		}
	}
	cout<<cnt+1;//我们给最后一条等差数列也减了一，因此输出时要加回来
	return 0;
}
```

写题解不易，路过/认真看过的大佬们都给个赞呗。

---

## 作者：JackMerryYoung (赞：0)

# 前言

C，不懂这个比赛为啥这么喜欢等差数列（）

# 正文

首先要会 $\mathcal{O}(N ^ 2)$ 暴力，然后考虑优化。

这种统计数列数目的题目我们经常使用尺取优化数数的过程。具体来说：

拿双指针维护数列使它具有等差数列性质，每次从右端点丢进去一个新的值，然后从左端点去杀人直到使数列重新具有等差数列性质，杀完人统计一遍。这样就做完了。

# 代码

``` cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll N, ans = 1;
ll arr[200005];

signed main()
{
	cin >> N;
	for(int i = 1; i <= N; ++ i)
		cin >> arr[i];
	
	int l = 1, r = 1;
	while(l <= r && l <= N && r <= N)
	{
		++ r;
		while(arr[l + 1] - arr[l] != arr[r] - arr[r - 1] && l <= N) ++ l;
		if(l > N || r > N) break;
		ans += (r - l + 1);
	}
	
	cout << ans << endl;
	return 0;
}
```

---

## 作者：T_TLucas_Yin (赞：0)

其实题目就是让你求一个序列中是等差数列的子序列个数。

先提一句，“等差序列”还有一个名字是“算术序列”，ATcoder 的比赛常称等差数列为算术数列，建议记住，避免在读题上浪费时间。

注意到，一个序列若是等差数列，则它的所有连续子段必然也是等差数列，那么该序列包含的等差子序列的数量就可以计算得到。

所以我们可以将整个序列分为若干段，使得每一段再向左或向右延伸一格就不是等差数列。此时整个序列的等差子序列必然仅包含在一段内（因为相邻两段的公差肯定不同，否则就可以合为一段）。因此求出每段包含的子段数目求和即可。

对于一个长度为 $n$ 的序列，它包含的子段数目为 $\frac{n\times(n+1)}{2}$。

实现时不一定要真的分段，遍历一遍得到每一段的段长即可。注意一段的端点独自组成的子段因实现方式不同，可能需要去重。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000005];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int l=1,r=2,sum=0;
	while(l<n){
		while(r<n&&a[r+1]-a[r]==a[r]-a[r-1]) r++;
		sum+=(r-l+2)*(r-l+1)/2-1;
		l=r,r=l+1;
	}
	cout<<sum+1;
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18391497)

### 题意：

判断有多少个区间是等差数列（不能重排）。

$1 \le n \times 10^5$。

### 思路：

赛时看错题了，以为这个区间可以重排，卡了 8min，小丑了。

首先容易注意到，对于一个区间 $[l,r]$，若其是等差数列，则这个区间的子区间 $[l',r']$ 肯定也是子序列，造成的贡献是 $\frac{(r-l+1)(r-l+2)}{2}$。

那么考虑求出所有极长等差区间，设 $d_i = a_{i+1} - a_i$，若 $i$ 能加入 $i-1$ 的等差区间，当且仅当 $d_i = d_{i-1}$；否则就要新开一个等差子区间。

注意最后答案要加 $n-1$。

时间复杂度为 $O(N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(A) memset(A,0,sizeof(A))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N=2e5+6;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,s,ans;
ll a[N],d[N];
int main(){
	n=read();
	For(i,1,n)
	  a[i]=read();
	For(i,1,n)
	  d[i]=a[i+1]-a[i];
	For(i,1,n){
		if(d[i]!=d[i-1]){
			ans+=s*(s+1)/2;
			s=1;
		}
		else
		  s++;		
	}
	ans+=s*(s+1)/2;
	write(ans+n-1);
	return 0;
}
```

---

## 作者：Little_Cabbage (赞：0)

# 解题思路

由题可知，题目中的算数级数就是我们熟悉的等差数列。

对于 $i$ 开始的一个最长的等差数列，它可以构成的等差数列的个数是 $\frac{t \times (t + 1)}{2}$（$t$ 为当前等差数列的长度）。

我们又发现这个等差数列的最后一个数可能是下一个等差数列的第一个数，所以需要让 $i = j$，而不是 $i = j + 1$（$i$ 表示当前等差数列开始位置，$j$ 表示当前等差数列结束位置）。

由于长度为 $1$ 的等差数列会重复计算，所以需要再计算长度的时候减去一个 $t$，再在输出的时候加上一个 $n$。

# 核心代码

```cpp
int i = 1;
while (i < n) {
  int j = i + 1;
  int d = a[j] - a[i];
  while (a[j] - a[j - 1] == d && j <= n) j ++ ;
  j -- ;
  int t = j - i + 1;
  ans += t * (t + 1) / 2 - t;
  i = j;
}
cout << ans + n;
```

---

## 作者：zjj2024 (赞：0)

### 思路

题目相当于是需要求序列中等差序列的个数。

考虑第 $i$ 个点往后多远还是等差数列，则区间中的任意一点均可与第 $i$ 个点组成一等差数列。

答案就是每个点往后能组成等差数列的方案数之和。

每次记录上一项的离它最远的点，再往后看可不可以延长即可。

时间复杂度为 $O(n)$。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
typedef long long ll;
ll a[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int mr=1;//最远点
	a[n+1]=1e18;
	ll ans=0;
	for(int i=1;i<=n;i++)
	{
		if(i==mr&&mr<n)//只有在和上一项最远点重合时才可能更新
		{
			mr++;
			while(a[mr]-a[mr-1]==a[i+1]-a[i])mr++;
			mr--;
		}
		ans+=mr-i+1;//区间[i,mr]中点的数量
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：n_ni (赞：0)

## 题面
给你一个长度为 $n$ 的序列 $A$，问这个序列中有多少个子区间是等差数列（长度为 $1$ 和 $2$ 的也算）。
## 思路
此题可用分治解决。

定义一个函数 $solve(l,r)$ 表示 $A$ 的左端点为 $l$，右端点为 $r$ 的子区间里的等差数列个数。

![](https://cdn.luogu.com.cn/upload/image_hosting/j4d15zmh.png)

那如何计算跨过中点的等差数列的数量呢？  
因为跨过中点的子区间都包含 $A_m,A_m+1$ 而且左端点在 $m$ 左边（或为 $m$），右端点在 $m+1$ 右边（或为 $m+1$），否则就被 $solve(l,m)$ 或 $solve(m+1,r)$ 算过。  
所以只需要找到跨过中点的最长的等差数列的左右端点（记左端点为 $l_0$，右端点为 $r_0$），  
然后用 $(m-l_0+1) \times [r_0-(m+1)+1]$ 即可求出跨过中点的等差数列数量（等差数列的子区间都是等差数列）。

这种方法时间复杂度为 $O(n \log n)$，可以通过此题。

记得开 `long long`。

## 代码
```cpp
#include<iostream>
#include<cmath>
using namespace std;
#define int long long

int a[200010];

int solve(int l,int r){
    if(l>r)return 0;
    if(l==r)return 1;
    int mid=l+r>>1;
    int la=solve(l,mid),ra=solve(mid+1,r);
    int d=a[mid+1]-a[mid];
    int _i=mid,_j=mid+1;
    for(;_i>=l;_i--){
        if(a[_i+1]-a[_i]!=d)break;
    }
    for(;_j<=r;_j++){
        if(a[_j]-a[_j-1]!=d)break;
    }
    //求跨过中点的最长等差数列，从中点往两边拓展即可。注意 a[_i] 和 a[_j] 不属于等差数列中
    _i++,_j--;
    return la+ra+(mid-_i+1)*(_j-(mid+1)+1);
}

signed main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    cout<<solve(0,n-1);
    return 0;
}
```

---

## 作者：gavinliu266 (赞：0)

# 思路
如果一个串是等差数列，那么它的所有子串也是等差数列。

考虑一个长度为 $k$ 的序列，它的子串个数是 $\frac{k(k+1)}{2}$。

于是只要统计有几个大的等差数列子串，然后就可以得到原数列的等差数列子串个数了。

但是统计时可能会重复，所以先统计长度大于等于 $2$ 的，最后加上长度为 $1$ 的。

# 代码实现
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 2e5 + 5;
int n;
int a[N];
long long ans;  // long long
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    int i = 1;
    while(i < n) {
        int d = a[i + 1] - a[i];
        int r = i + 1;
        while(a[r + 1] - a[r] == d && r < n)
            ++r;  // 统计大的等差数列子串长度
        int l = r - i;  // 减 1，统计长度大于等于 2 的
        ans += 1ll * l * (l + 1) / 2;  // 计算它的子串个数
        i = r;
    }
    printf("%lld\n", ans + n);
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_abc369_c 题解

## 题意

给定一个长度为 $N$ 的序列 $a$，找出子序列 $(a_l,\cdots,a_r)$ 的数量，满足子序列是一个等差数列。

## 思路

单独一个数字是一个等差数列，相邻两个数也是等差数列。

考虑 DP，记 $f_i$ 为以 $i$ 为右端点，等差数列的个数。

初始化 $f$ 数组，因为第 $1$ 个位置作为右端点只有一个子序列成立，则 $f_1=1$，对于其它位置 $f_i=2$。

考虑状态转移，对于 $a_i-a_{i-1} = a_{i-1}-a_{i-2}$，说明 $f_i$ 可以由 $f_{i-1}$ 转移，由于长度为 $2$ 的情况已经在初始化时加上，所以这里减去 $1$，即 $f_i=f_{i-1}-1 + [i \neq 1] + 1$。

最后 $ans = \sum\limits_{i=1}^n f_i$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define endl '\n'
#define FRR(file) freopen(file,"r",stdin)
#define FRW(file) freopen(file,"w",stdout)
#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _reps(i,a,b,c) for (int i=(a);i<=(b);c)
#define _rrep(i,a,b) for (int i=(a);i>=(b);--i)
#define _rreps(i,a,b,c) for (int i=(a);i>=(b);c)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)
#define _graph(i,u) for (int i=h[u];~i;i=ne[i])
#define rint register int
#define LL long long

const int N=200005;

int n;
int arr[N];
int f[N];

signed main() {
    scanf("%lld",&n);
    _rep(i,1,n) scanf("%lld",&arr[i]);
    _rep(i,1,n) {
        f[i]=i==1?1:2;
        if (i!=1 && arr[i]-arr[i-1]==arr[i-1]-arr[i-2]) f[i]+=f[i-1]-1;
    }
    int ans=0;
    _rep(i,1,n) {
        ans+=f[i];
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：under_the_time (赞：0)

## 题意

> 给定一个长度为 $n$ 的正整数列 $a$，求 $(l,r)$ 的对数使得 $a_l,a_{l+1},\cdots,a_{r}$ 构成等差序列。
>
> $n\le 2\times 10^5$。

## 解法

翻译的时候把子串翻成了子序列在那怀疑 ABC 的难度……我们考虑对 $a$ 算一个差分数组 $d$，如 $a=\{87,42,64,86,72,58,44,30\}$，令 $d_i=a_{i}-a_{i-1}$，其中 $i\in [2,n]$，那么 $d=\{-45,22,22,-14,-14,-14,-14\}$。可以发现对于 $a$ 的一个构成等差序列的子串 $[l,r]$，在 $d$ 上就表现为 $[l+1,r]$ 相等，这也是等差数列的定义。

于是我们从前往后考虑以每个 $i$ 作为结尾的等差数列，我们找到最长的 $[j,i]$ 使得 $d$ 中 $[j,i]$ 的部分都相等；那么以 $i$ 为右端点，左端点可以取到 $[j,i]$​ 中的所有位置。于是就做完了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 5;
int a[maxn], d[maxn], n;
int main() {
	scanf("%d", &n); long long ans = n; // 记得加上长度为 1 的等差数列。
	for (int i = 1; i <= n; i ++)
		scanf("%d", &a[i]), d[i] = a[i] - a[i - 1];
	for (int i = 2, j = 2; i <= n; i ++) {
		if (d[i] != d[i - 1]) j = i;
		ans += (i - j + 1);
	} printf("%lld", ans);
	return 0;
}
```

---

## 作者：LuukLuuk (赞：0)

# 题解：AT_abc369_c [ABC369C] Count Arithmetic Subarrays
### 题目大意
给定一个序列 $a_1,\dots,a_n$，求其中长度大于等于 $1$ 的连续等差数列的数量。
### 思路
枚举到 $a_i$ 时，记录以当前元素结尾的最大序列长度 $len$，若当前元素可以继续作为之前等差序列的元素 $len$ 就加 $1$，不行的话 $len$ 就变为 $2$。由于 $len$ 也可以表示以当前元素结尾，可以选择的开头元素个数，所以 $a_i$ 对答案的贡献就是 $len$。
### 代码
```cpp

#include <cstdio>
using namespace std;

#define int long long

int a[200010];
int len, ans;
int n, sum;

signed main() {
	scanf("%lld", &n);
	ans = 1;//i=1的情况 
	sum = -2e9;//初始公差不能为任何一个可能存在的公差 
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		if (i == 1)	continue;
		if (a[i] - a[i - 1] == sum) {//接得上 
			len++;
		} else {
			len = 2;
			sum = a[i] - a[i - 1];
		}
		ans += len;
	}
	printf("%lld", ans);
	return 0;
}

```

---

## 作者：liruixiong0101 (赞：0)

# C - Count Arithmetic Subarrays
## 题意：
给定一个长度为 $n$（$1\le n\le 2\times 10^5$）的序列 $a$，求 $a$ 有多少个子串 $b$ 满足 $b$ 升序排列且为等差数列。

## 思路：
容易发现一个性质：若 $a[l\ldots r]$ 为等差数列，且 $a[l\ldots r+1]$ 不为等差数列，那么 $a[l+1\ldots r+1]$ 不为等差数列，$a[l\ldots r+2]$ 也不为等差数列。

那么我们可以双指针，让 $r$ 从 $l$ 开始扩展，扩展到 $a[l\ldots r]$ 为等差数列时，且 $a[l\ldots r+1]$ 不为等差数列时，计算方案数为 $\dfrac{(r-l+1)(r-l+2)}{2}$，但是这样计算会把长度为 $1$ 的子串算重，那么可以将长度为 $1$ 的子串不在双指针中计算，那么每次计算的方案数为 $\dfrac{(r-l)(r-l+1)}{2}$，最后再将答案加 $n$ 即可。

## 代码：
<https://atcoder.jp/contests/abc369/submissions/57289604>

---

## 作者：zzhbpyy (赞：0)

### [Count Arithmetic Subarrays](https://atcoder.jp/contests/abc369/tasks/abc369_c)

## 思路

显然，一个等差数列的任意子段都是符合条件的等差数列。我们可以直接 $O(N)$ 时间遍历整个数列，找到所有**极长**的等差数列。这里的**极长**是指对一个等差数列 $(A_l,A_{l+1},\dots,A_r)$，其相邻的数列 $(A_l,A_{l+1},\dots,A_{r+1})$ 和 $(A_{l-1},A_l,A_{l+1},\dots,A_r)$ 都不是等差数列。

设第 $i$ 个**极长**等差数列长度为 $x_i$，则答案为 $N+\sum x_i\times(x_i-1)/2$，前一项来自长度为 $1$ 的数列。

## Code

```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[200005],n;
vector<int>v;//记录所有极长等差数列的长度
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	int d=INT_MAX,cnt=1;
	for(int i=2;i<=n;i++){
		if(d!=INT_MAX&&a[i]-a[i-1]!=d)//a[i]与a[i-1]差与前面不相等，说明是一段新的等差数列
            v.push_back(cnt),cnt=1;
		d=a[i]-a[i-1];cnt++;
	}v.push_back(cnt);//加入最后一段的答案
	int ans=0;
	for(auto vv:v)ans+=vv*(vv-1)/2;
	cout<<ans+n;
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 题意

给定你一个序列 $A$，问你这个序列里有多少个子串是等差数列。

## 思路

我们可以考虑如果一个等差数列后面接上的一个数，这个数和它前面一项的差与该等差数列的差相等，那么就可以贡献出 $len - 2$ 个长度大于等于 $3$ 且以这个数结尾的等差数列（$len$ 为当前连续等差数列的长度）。

之后我们可以发现一个尽可能长且长度大于等于 $3$ 的等差数列所包含的长度大于等于 $3$ 等差数列子串的个数有 $\sum_{i = 2}^{len -1}  len - i$，化简后的计算公式为：
$$
  \frac {(len - 1)\times(len - 2)}{2}
$$

代码如下：


```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
#define F(i , x , n) for (int i = x ; i <= n; i++)
#define umap unordered_map
#define uset unordered_set
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define frep freopen(".in","r",stdin);freopen(".out","w",stdout);

using u64 = unsigned long long ;

const int mod = 998244353 ;
const int CFMAXN = 2e5 + 10 ;
const int INF = 0x3f3f3f3f3f ;


/*----------------template----------------------*/
int n ;
int arr[CFMAXN] ;
int c[CFMAXN] ;
int dp[CFMAXN] ;
void solve (){
	cin >> n ;
	if ( n == 1 ){//特判，不然会WA
		cin >> arr[1] ;
		cout << 1 ;
		return ;
	}
	int ans = 0 ;
	int d = 0 ;
	int len = 0;
	cin >> arr[1] >> arr[2] ;
	d = arr[2] - arr[1] ;
	len = 2 ;
	for (int i = 3 ; i <= n ; i++){
		cin >> arr[i];
		if ( (arr[i] - arr[i - 1] == d ) ){
			len++ ;
		}else {
			ans += ( len - 1 ) * (len - 2) / 2 ;
			len = 2 ;
		}
		d = arr[i] - arr[i - 1];
	}
	ans += (len - 1) * (len - 2) / 2 ;
	cout << ans + 2 * n - 1 ;
}

signed main (){
	int _ = 1 ;
	//cin >> _ ;
	while ( _-- ){
		solve () ;
	}
	return 0 ;
}
```

---

## 作者：Elysian_Realme (赞：0)

考虑根据原数列两项之间的差分成若干段。每一段都是一个最大的等差数列（即将前一个数或后一个数加入后都不再是等差数列），容易发现两段之间有且仅有首尾两个数与相邻段重叠。然后若第 $i$ 段的长度为 $l_i$，易得该段内共有 $\dfrac{l_i\times(l_i+1)} {2}$ 种可以构成答案的序列，因为单个数也算在内，所以相邻两段重叠的数实际上算了两次，记得减去。

```cpp
// Problem: C - Count Arithmetic Subarrays
// Contest: AtCoder - AtCoder Beginner Contest 369
// URL: https://atcoder.jp/contests/abc369/tasks/abc369_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// By：lmq
// AC Time：2024-08-31 20:02:19

#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
inline void print(int x){
	static int s[20],t=0;
	do s[++t]=x%10,x/=10;while(x);
	while(t) putchar(s[t--] + '0');
}
const int N=2e5+5;
int n,l,d,ans;
int a[N];
signed main(){
	cin>>n;
	if(n==1)cout<<1<<endl,exit(0);
	a[1]=read(),a[2]=read();
	l=2,d=a[2]-a[1];
	for(int i=3;i<=n;i++){
		a[i]=read();
		if(a[i]-a[i-1]!=d){
			ans+=l*(l+1)/2-1;
			d=a[i]-a[i-1],l=2;
		}else l++;
	}
	ans+=l*(l+1)/2;
	cout<<ans<<endl;
	return 0;
}
// 某一日，祂从天坠落。人们抬头仰望，于是看见了星空。
// 星月送来神的女儿，她愿成为人的伴侣。
// 长风化作她的轺车，四海落成她的园圃。鸟雀衔来善的种子，百花编织爱的颂歌。
// 她便是这样降生于世，行于大地，与人类一同长大，与世界一起发芽。
// 而今，「终焉」之时将至。
// 而今，「归去」之时已至。
// 就此告别吧，美丽的世界。
// 此后，将有「群星」闪耀，因为我如今来过。
// 此后，将有「百花」绽放，因为我从未离去。
// 请将我的箭、我的花、与我的爱，织成新生的种子，带向那枯萎的大地。
// 然后，便让它开出永恒而无瑕的…「人性之华」吧。
// 「我名为爱莉希雅……」
// 「最初的律者，人之律者。」
```

---

## 作者：hjyowl (赞：0)

### 题目大意：

给定长度为 $n$ 的序列 $a$，求出有多少对 $(l,r)$，使得 $l$ 到 $r$ 这段子序列是一个等差数列。

### 暴力思路：

枚举 $l$ 和 $r$，然后暴力判断是不是等差数列，如果是，答案加一，时间复杂度 $O(n^3)$ ，不能通过。

### 正确思路：

考虑使用双指针，令两个双指针 $i,j$。$i$ 正常枚举，$j$ 对于每个 $i$ ,往后找出一个长度为 $len$ 的连续的等差数列，然后用组合公式 $C_{len}^2$ 来计算（相当于从长度里面挑选出来 $2$ 个端点）这一段的答案，随后用指针 $j-1$ 更新 $i$。

会发现多算了一些，多算的部分就是相当于两个的交点那个位置，就相当于在更新的时候，定义一个变量 $c$，每次更新时 $c$ 加一，用答案减去 $(c-1)$ 的值就可以了。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 200010;
long long a[N];
bool st[N];
int main(){
	long long n;
	cin >> n;
	for (long long i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	long long res = 0;
	long long cnts = 0;
	for (long long i = 1; i < n; i ++ ){
		long long d = abs(a[i + 1] - a[i]);
		long long cnt = 1;
		long long j = i;
		while (j + 1 <= n && abs(a[j + 1] - a[j]) == d){
			j ++ ;
			cnt ++ ;
		}
		if (cnt >= 2){
			cnts ++ ;//相当于说的c
			res += cnt * (cnt + 1) / 2;//C(len,2)
			i = j - 1;
		}
	}
	cout << res - cnts + 1;
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：0)

### C-Count Arithmetic Subarrays

#### 题意

给出一个长度为 $n$ 的序列 $A$，求有多少个 $A$ 的连续子序列为等差数列。

#### 思路

对于递增的右端点，左端点不减。

使用双指针，枚举右端点，扫描左端点。

时间复杂度：$O(n)$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5 + 5;
int a[N], n;
ll ans;
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = 1, j = 1; i <= n; i ++) {
        j = max(j, i);
        while (i < n && j < n && a[j + 1] - a[j] == a[i + 1] - a[i]) j ++;
        ans += j - i + 1;
    }
    cout << ans << "\n";
}
int main() {
    int T = 1;
    // cin >> T;
    while (T --) 
        solve();
    return 0;
}
```

---

## 作者：seika27 (赞：0)

### 分析
不难发现对于一个长度为 $n$ 的等差数列，其所有子串也都是等差数列。所以其一共会有 $\frac{n(n+1)}{2}$ 个等差数列。

所以我们只需要每次找出一段最长的等差数列，然后计算贡献即可。

于是我们就有了初版代码。

```cpp
int l=1,r=2;
	while(l<=r&&r<=n)
	{
		
		if(a[l+1]-a[l]!=a[r]-a[r-1])
		{
			--r;
			ans+=(1+r-l+1)*(r-l+1)/2;
			l=r;
			r=l+1;
		}
		else ++r;
	}
	cout<<ans+(1+n-l+1)*(n-l+1)/2;
```

然后就惊人的发现连样例都过不了。

原因是当我们计算从 $l\sim r$ 的区间的时候，$a_r$ 被计算了一次，然后我们到下一个区间 $l'\sim r'$ 的时候，不难发现此时 $l'=r$ 所以 $a_{l'}$ 又被算了一次。

所以我们只需要添加一个变量来统计重复的次数就好了。

```cpp
int l=1,r=2;
	while(l<=r&&r<=n)
	{
		
		if(a[l+1]-a[l]!=a[r]-a[r-1])
		{
			--r;
			ans+=(1+r-l+1)*(r-l+1)/2;
			l=r;
			r=l+1;
			++res;
		}
		else ++r;
	}
	cout<<ans+(1+n-l+1)*(n-l+1)/2-res;
```

---

## 作者：Spark_King (赞：0)

# ABC369C 题解

## 题意理解
给定一个长度为 $n$ 的数列 $A$，求该数列中一共有多少个等差子数列。

注意：**长度为 1 或 2 的子数列**也算等差子数列。

## 题意分析
首先我们知道，等差数列中**每相邻的两个数之间的差相等**，所以我们可以定义一个数组 $d$ 用来保存相邻数之间的差。

然后根据等差数列的特性，一个**区间内的差都相等**，就可以认为是一个等差子数列。那么我们只需要计算有多少个相邻的 $d_i$ 相等，然后统计计数就可以了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
ll a[200010], d[200010];
ll ans;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
		d[i] = a[i] - a[i - 1];
	}//计算d数组
	ans = n;//长度为1的子序列也算
	d[n + 1] = -1e18;//保存一个不可能存在的差
	for (ll i = 3, sum = 1, dis = d[2]; i <= n + 1; i++) {
		if (d[i] != dis) {//不同就计数更改
			ans += (1 + sum) * sum / 2;//自行理解
			dis = d[i];
			sum = 1;
		} else sum++;//相等就增加
	}//这里运行到n+1是为了方便统计最后一部分
	cout << ans;
	return 0;
}
```

---

## 作者：D0000 (赞：0)

求序列连续的字串等差序列的个数。

钦定 $r$ 为结尾，发现左端点不为 $l$ 时公差一定为 $a_r-a_{r-1}$，因此记录下所有的差分，从 $r$ 往前最长差分后连续等于  $a_r-a_{r-1}$ 位置的左端点就是以 $r$ 为右端点能匹配的最远的左端点。

每个点可以 $O(1)$ 求出，总共 $O(n)$。

代码：
```cpp
#include<cstdio>
int n,a[200005],ll=-1,lastcha=-(1ll<<31);
long long ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(i==1){
            ans++;
            continue;
        }
        int now=a[i]-a[i-1];
        if(now!=lastcha)lastcha=now,ll=i-1;
        ans+=i-ll+1;
    }
    printf("%lld",ans);
}
```

---

## 作者：__Allen_123__ (赞：0)

> 求序列中等差数列的个数。

双指针。假设每一次滑动之后，总满足从下标 $l$（左指针）到下标 $r$（右指针）内都是等差数列。

右指针滑到 $r$ 的时候，我们检验 $a_r-a_{r-1}$ 是否和原来的等差数列的公差相等（如果原来 $l=r$ 则不必检验）。如果相等，则左指针不必滑动；否则就要滑动到 $r$。

每次滑动完毕以后，把答案加上 $r-l+1$（即以 $r$ 为右端点的等差数列个数）即可。由于初始时 $l=r=1$ 满足上面的假设，所以做法可行。时间复杂度 $O(n)$。

[AC 记录](https://atcoder.jp/contests/abc369/submissions/57282398)。

---

