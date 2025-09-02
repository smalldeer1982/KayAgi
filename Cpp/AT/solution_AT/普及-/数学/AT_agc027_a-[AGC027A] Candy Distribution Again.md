# [AGC027A] Candy Distribution Again

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc027/tasks/agc027_a

$ N $ 人の子供がいます。 子供たちには $ 1,\ 2,\ ...,\ N $ と番号が振られています。

すぬけ君は、$ x $ 個のお菓子を子供たちに配ることにしました。 このとき、すぬけ君は $ x $ 個のお菓子をすべて配り切らなければなりません。 なお、お菓子を貰わない子供がいても構いません。

各 $ i $ ($ 1\ \leq\ i\ \leq\ N $) について、子供 $ i $ はちょうど $ a_i $ 個のお菓子を貰うと喜びます。 すぬけ君は、お菓子を配る方法を工夫し、喜ぶ子供の人数を最大化しようとしています。 喜ぶ子供の人数の最大値を求めてください。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ x\ \leq\ 10^9 $
- $ 1\ \leq\ a_i\ \leq\ 10^9 $

### Sample Explanation 1

例えば、$ (20,\ 30,\ 20) $ とお菓子を配ればよいです。

### Sample Explanation 2

$ (0,\ 0,\ 10) $ とお菓子を配ればよいです。

### Sample Explanation 3

$ (1,\ 10,\ 100,\ 1000) $ とお菓子を配ればよいです。

### Sample Explanation 4

どのようにお菓子を配っても、どの子供も喜びません。

## 样例 #1

### 输入

```
3 70
20 30 10```

### 输出

```
2```

## 样例 #2

### 输入

```
3 10
20 30 10```

### 输出

```
1```

## 样例 #3

### 输入

```
4 1111
1 10 100 1000```

### 输出

```
4```

## 样例 #4

### 输入

```
2 10
20 20```

### 输出

```
0```

# 题解

## 作者：Liweiang (赞：6)

**题目：**[AT4375 Candy Distribution Again](https://www.luogu.com.cn/problem/solution/AT4375)

## 思路：
先将定义的变量名列出，以便讲解。
```cpp
int a[1001];//每个孩子的糖果需求量
long long n,m,sum=0,ans=0,i;
//m是糖果总量，n是人数，sum是孩子的糖果需求量和，i是循环变量
```

**分类讨论：**

1. 当 $m$ 大于 $sum$ 时：直接输出 $n-1$。

1. 当 $m$ 等于 $sum$ 时：直接输出 $n$。

1. 当 $m$ 小于 $sum$ 时：
用 sort 将 $a$ 数组由小到大排序一遍，再依次将 $m$ 减去 $a_i$，每减去一次 $ans$ 就加一。一旦 $m$ 小于 $a_i$，就退出循环。

**注意：** 当 $ans$ 等于 0 时，就输出 $`0`$。（当时被样例 4 误导了，直接 return 0 ）。


------------


## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1001];
int main() 
{
	long long n,m,sum=0,ans=0,i;
	cin>>n>>m;
	for(i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	sort(a+1,a+n+1);
	if(a[1]>m){//小特判
		cout<<0<<endl; 
		return 0;
	}
	if(sum<m) {//当m大于sum时
		cout<<n-1<<endl;
		return 0;
	}
	if(sum==m){//当m等于sum时
		cout<<n<<endl;
		return 0;
	}
   //当m小于sum时
	i=1;
	while(m>=a[i]){
		m-=a[i];
		ans++;
		i++;
	}
	cout<<ans<<endl;
	return 0;
}
```

------------

**后话：** 本蒟蒻的思路或代码如有问题还请指出，谢谢大家！

---

## 作者：亦枫 (赞：4)

### Solution

题意：有 $ n $ 个小孩子，共有 $ all $ 颗糖。每个孩子需要 $ a_i $ 颗糖，给多或给少了都会不开心，只有正好给 $ a_i $ 颗才能使他开心。

看到这道题，我们只需进行排序，在从前往后枚举比较即可。

Code：
```
cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,all,a[10005],ans,num;
int main() {
	scanf("%d %d",&n,&all);
	for(register int i=1; i<=n; ++i) {
		scanf("%d",&a[i]);
		num+=a[i];
	}
	sort(a+1,a+n+1);//排序
	if(all>num) {
		printf("%d\n",n-1);
		exit(0);
	}
	if(all==num) {
		printf("%d\n",n);
		exit(0);
	}
	if(all<a[1]) {
		printf("0\n");
		exit(0);
	}
	//三个特判，简单优化
	for(register int i=1; i<n; ++i) {
		if(all>=a[i]) {
			ans++;
			all=all-a[i];
		}
	}
	if(all>a[n])ans--;//如果最后仍然有余，最后一个孩子就不开心了
	printf("%d\n",ans);

}
```

---

## 作者：伟大的王夫子 (赞：2)

这道题完全是一道模拟题。

现在我们考虑一下，有哪几种情况，以及每种情况的答案分别是多少。

1.当 $\sum_{i = 1} ^n a_i = m$ 时，此时显然要输出 $n$

2.当 $\sum_{i = 1}^n a_i < m$ 时，可以让 $n$ 个孩子中任意一个不高兴一下， 答案即为 $n - 1$

3.当 $\sum_{i = 1} ^ n a_i > m$ 时，那我们将整个序列    $a$ 排个序。我们找到一个最大的位置 $pos$，使得        $\sum_{i=1}^n a_i \le m$，那样问题便转化成了前两个问题，用类似做法既可。

当然，如果这个位置不存在，那么就输出 0（~~不要被样例蒙骗了~~）

下面给出代码，主要供参考。个别地方可能写的不是很好，请谅解

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
int n, m, a[110], ans;
main() {
	cin >> n >> m;
	for (register int i = 1; i <= n; ++i) scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	if (a[1] > m) {
		puts("0");
		return 0;
	}
	int s = 0, pos = 0;
	for (register int i = 1; i <= n; ++i) {
		s += a[i];
		if (s > m) {
			ans = i - 1;
			break;
		} else if (s == m) {
			cout << i << endl;
			return 0;
		}
	}
	if (s < m) cout << n - 1 << endl;
	else if (s == m) cout << n << endl;
	else if (ans >= 0) cout << ans << endl;
}
```

---

## 作者：·糯· (赞：0)

## 题目分析
这题有三种情况：  
情况一：拥有的糖超过了小朋友的总需求量。  
那么此时我们就在满足条件的情况下，把剩余的糖都分给一个小朋友，只让他不高兴，其他人都高兴（~~话说有点残忍~~）。  
情况二：正好满足需求。  
那就不用说了，正好每个人都满足。  
情况三：糖果不够。  
那就必须得从小的需求到大的需求满足，一旦满足不了了，就输出已满足的数量。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[110];
long long sum,ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		sum+=a[i];
	}
	if(m>sum){
		cout<<n-1<<endl;
		return 0;
	}
	if(m==sum){
		cout<<n<<endl;
		return 0;
	}
	sort(a+1,a+n+1);
	int cnt=1;
	while(m-a[cnt]>=0){
		m-=a[cnt];
		ans++;
		cnt++;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：eEfiuys (赞：0)

题目：[AT4375](https://www.luogu.com.cn/problem/AT4375)
# 贪心。
## 1. 输入：
- $n$ 表示孩子个数, $m$ 表示糖的个数；
- $a_1 - a_n$ 表示每个孩子要的糖的个数。

## 2. 特判：
- 用 $num$ 记录所有孩子要的糖的总个数；
- 如果**糖多了**，即 $m > num$，则至少有 $1$ 个孩子分到的糖多于他要的，因此**直接输出 $n-1$**；
- 如果**糖刚够**，即 $m == num$，则每个孩子都能正好分到他想要的糖，因此**直接输出 $n$**;
- 如果已经输出，那么后面的计算就没有意义，**直接```return 0```**。

#### 代码：
```cpp
cin>>n>>m;
for(ll i=1;i<=n;i++)
{
	cin>>a[i];
	num+=a[i]; //记录需要的糖的总个数。
}
if(m>num) //糖多了。
{
	cout<<n-1<<endl;
	return 0;
}
if(m==num) //糖刚够。
{
	cout<<n<<endl;
	return 0;
}
```

## 3. 计算：
- 对 $a$ 数组**从小到大排序**，通常使用```STL```中的```sort```；
	- 分给每个孩子的糖越少，分给的孩子就越多。
- 从 $a_1$ 开始**枚举**，通常使用```for```循环，用 $k$ 记录分出的糖，用 $ans$ 记录开心的孩子数量。
	- **把糖分给第 $i$ 个孩子**，即 $k$ 加上 $a_i$；
	- 如果**糖不够了**，即 $k > m$，就**输出 $ans$ 并```return 0```**；
   - 如果**糖还够**，即 $k \le m$，那么第 $i$ 个孩子就会因分到他想要的糖而开心，即 **$ans++$**。

#### 代码：
```cpp
sort(a+1,a+n+1)
for(ll i=1;i<=n;i++) //枚举。
{
	k+=a[i]; //分给第i个孩子糖。
	if(k>m) //糖不够了。
	{
		cout<<ans<<endl;
		return 0;
	}
	else //糖还够。
		ans++; //又一个孩子开心了。
}
```

## 4. 提示：
- $num$ 会炸```int```，**要用```long long```**，为了方便，我全都用的```long long```；
- AT 的题最后要**输出换行**；
- ~~应该没有人会故意给一个孩子少分或多分糖吧~~。

------------

# Code:
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m;
ll num,k,ans;
ll a[101];
int main()
{
	cin>>n>>m;
	for(ll i=1;i<=n;i++)
	{
		cin>>a[i];
		num+=a[i]; //记录需要的糖的总个数。
	}
	if(m>num) //糖多了。
	{
		cout<<n-1<<endl;
		return 0;
	}
	if(m==num) //糖刚够。
	{
		cout<<n<<endl;
		return 0;
	}
	sort(a+1,a+n+1);
	for(ll i=1;i<=n;i++) //枚举。
	{
		k+=a[i]; //分给第i个孩子糖。
		if(k>m) //糖不够了。
		{
			cout<<ans<<endl;
			return 0;
		}
		else //糖还够。
			ans++; //又一个孩子开心了。
	}
	return 0;
}
```

---

## 作者：WHJ___ (赞：0)

一道简单的**贪心**题。

我先说明一个结论：我们要让尽量多的孩子开心，就应该优先给需求最少的孩子糖，可能有些同学就不理解了，那么我举个例子：

如果我有 $6$ 颗糖果，需要让 $3$ 个孩子开心，他们的需求分别是 $2$,$3$,$6$ 颗糖果，如果我要让尽量多的孩子开心，我就应该给需求量最少的两个孩子糖果，即需求量为 $2$ 和 $3$ 的孩子，虽然这样会有 $1$ 颗糖果浪费，但是可以使更多的孩子开心。如果我给需求量为 $6$ 的孩子糖果虽然糖果没有浪费，但是不能让尽可能多的孩子开心。简而言之，我们的目的并不是避免糖果浪费，而是让尽可能多的孩子开心。因此，我们应当按照需求从小到大的顺序给孩子糖，可以使用 **sort** 实现，然后再依次扫一遍，对每一个孩子都进行判断，代码即:

```cpp
if(x>=a[i]){//可以给这个孩子糖 
	++ans;
	x-=a[i];
}
else break;//糖不够了 
```


但是问题又来了，这道题最特别的地方是给**多**也会让孩子不高兴（虽然不太合理），如果我的糖果足够多,能够满足所有孩子的需求，而孩子收到过多的糖果也会不高兴，因此我们对最后一个孩子进行特判：如果剩余糖果数量刚好等于最后一个孩子的需求量（这样不仅能排除糖果过多的情况，同时也能排除糖果不足的情况），那么我们就可以使得最后一个孩子也开心。

代码：

```cpp
#include<bits/stdc++.h>
#define I long long
#define RI register int
#define il inline
#define rt return
using namespace std;
const int N=1e2+7;

I n,x,ans,a[N];

il I d(){
	I x=0,f=1;
	char c=0;
	while(!isdigit(c=getchar()))f-=(c=='-')*2;
	while(isdigit(c)){x=(x<<1)+(x<<3)+f*(c-48);c=getchar();}
	rt x;
}

signed main()
{
	RI i,j;
	n=d();x=d();
	for(i=1;i<=n;++i) a[i]=d();
	sort(a+1,a+n+1);//从小到大排序 
	for(i=1;i<n;++i){
		if(x>=a[i]){//可以给这个孩子糖 
			++ans;
			x-=a[i];
		}
		else break;//糖不够了 
	}
	if(x==a[n]) ++ans;//如果剩下的糖刚刚好和最后一个孩子要的数量一样,那么最后一个孩子也会开心 
	cout<<ans<<endl;
	rt 0;
}

```



---

## 作者：Brian_WBY (赞：0)

一道贪心题。

容易知道，我们要尽量把糖送给需要更少的糖的孩子，这样能满足更多的孩子，所以我们可以把孩子需要的糖的数量从小到大排序，然后一个一个去尝试满足：只要当前还剩余的糖的数量大于等于当前孩子的需求，我们就可以满足他。但是如果满足了所有的孩子仍剩余糖的话，我们就不得不把手中的糖全部给某一个孩子，那这个孩子就得不到满足，就就需要将答案 $-1$。

代码如下：

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[101];
int main(void)
{
	int n, x;
	scanf("%d%d", &n, &x);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);//输入
	sort(a + 1, a + n + 1);//从小到大排序
	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (x < a[i])//如果现在剩余的糖已经 < 当前孩子的需求，就不能满足了
		{
			printf("%d", ans);//输出答案
			return 0;//结束程序，不需要继续尝试，因为比当前i大的j都会使a[i] <= a[j]
		}
		++ans;//可以满足这个孩子
		x -= a[i];//糖少了a[i]快
	}
	if (x) --ans;//如果此时还剩下糖，就不得不给某一个孩子，他就得不到满足
	printf("%d\n", ans);//输出答案，注意换行
	return 0;
}
```

---

