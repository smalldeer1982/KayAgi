# [NOISG 2024 Prelim] Tourist

## 题目背景

翻译自 [NOI SG 2024 Prelim A.Tourist](https://github.com/noisg/noi-2024-prelim)。

## 题目描述

你是一名游客，你想要在 $n$ 天内游览一座城市。

你已经为自己安排好了行程。第 $i$ 天你需要乘坐 $a_i$ 次火车。

你了解到有以下两种火车票：

- 单程票：花费 $x$ 元购买一张单程票，可以乘坐 $1$ 次火车。

- 单日票：花费 $y$ 元购买一张单日票，可以在一天中不限次数地乘坐任意次火车。

请你求出购买火车票需要的最小花费。

## 说明/提示

### 【样例 #1 解释】

你的行程有 $3$ 天，一张单程票 $4$ 元，一张单日票 $9$ 元。

在第一天，购买 $2$ 张单程票，花费 $8$ 元。

在第二天，购买 $1$ 张单日票，花费 $9$ 元。

在第三天，购买 $2$ 张单程票，花费 $8$ 元。

最小花费为 $8+9+8=25$ 元。

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$100$|无|

对于 $100\%$ 的数据，$1 \le n,x \le 1000,1 \le y \le 10^6,1 \le a_i \le 10^4$。

## 样例 #1

### 输入

```
3 4 9
2 3 2
```

### 输出

```
25```

# 题解

## 作者：DFs_YYDS (赞：6)

挺简单的一道贪心题，评红吧。
# 题目大意
给你 $n$ 天坐的火车（~~不应该是地铁吗~~）次数，每天可以买单程票，坐一次付 $x$ 元；也可以直接买单日票，一天只需要付 $y$ 元即可。
# 具体思路
对于每天的行程，比较买单程票的价钱和单日票的价钱，即比较 $a_i \times x$ 和 $y$，选择较小的，用 $ans$ 记录下来，最后输出即可。
# 完整代码
```cpp
#include<bits/stdc++.h>//万能头文件。 
using namespace std;
int main(){//主函数部分。 
    int n/*天数n*/,x/*单程票的价钱*/,y/*单日票的价钱*/,ans=0/*答案*/;
    cin>>n>>x>>y;//读入。 
    for(int i=0;i<n;i++){//循环天数。 
    	int a;//坐火车的次数a。 
    	cin>>a;//读入a。 
    	ans+=min/*min函数，用于求两项中的最小值*/(x*a/*单程票的价钱*/,y/*单日票的价钱*/);
    	/*
    	上面的一行代码等价于：
		if(x*a<y)ans+=x*a;
		else ans+=y;
		和：
		ans+=x*a<y?x*a:y;
		这3段代码的效果是一样的。 
    	*/
    }
    cout<<ans;//输出结果ans。 
    return 0;
}
```

---

## 作者：wheat__ (赞：2)

专栏地址：[https://www.luogu.com.cn/user/771125#article](https://www.luogu.com.cn/user/771125#article)
- ### 读题

有两种票型，一种为单程票，一种为单日票。

单程票为一次乘车需花的钱，而单日票可以一日内无限次乘车。

- ### **思考**

很显然这需要做比较。再说数据较小，可以直接循环。

很明显的**模拟**。

模拟代码见下：

```cpp
#include<iostream>
using namespace std;
int main(){
	int n,x,y;
	cin>>n>>x>>y;
	int a[1010];
	int money=0;//买票的钱
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]*x<y)money+=a[i]*x;//当单程票更省钱
		else money+=y;//当单日票更省钱
	}
	cout<<money;
	return 0;
}
```

这题比较简单，算模拟题。如果模拟不好，可以做做 2021 CSP-J 的第三四题。链接如下：

[P7911 [CSP-J 2021] 网络连接](https://www.luogu.com.cn/problem/P7911)

[P7912 [CSP-J 2021] 小熊的果篮](https://www.luogu.com.cn/problem/P7912)

当然你还可以**递推**：

```cpp
#include<iostream>
using namespace std;
int main(){
	int n,x,y;
	cin>>n>>x>>y;
	int a[1010],dp[1010];
	dp[0]=0;//定义初始值
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1]+min(a[i]*x,y);//思路跟模拟差不多，只不过另一种形式
	}
	cout<<dp[n];
	return 0;
}
```

##### ~~建议加强数据。~~

---

## 作者：abc1234shi (赞：2)

这是一道简单的贪心题，这题我们比较第 $i$ 天是买单程票更省钱还是买单日票更省钱，也就相当于在比较 $a_i\times x$ 是否小于 $y$，如果小于就将答案增加 $a_i\times x$，否则就将答案增加 $y$。最后输出答案就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1100];
long long sum;
int main() {
    int n,x,y;
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
    	if(a[i]*x<y)sum+=a[i]*x;
		else sum+=y;
	}
	cout<<sum;
    return 0;
}
```

---

## 作者：Fuxh_18 (赞：2)

## 思路
一共有 $N$ 天，单程票 $x$ 元，单日票 $y$ 元，第 $i$ 天坐 $a_i$ 次。所以每天有**两种**买票方案：

1. 买单程票。就需要 $x \times a_i$ 元。
2. 买单日票。就需要 $y$ 元。

我们只需要判断每天买哪种票更划算，再把每天的加起来，就能通过此题。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,s; //分别为：天数，单程票，单日票，总钱数
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){ //循环判断每天最小值
		int a;
		cin>>a;
		s+=min(a*x,y);
	}
	cout<<s;
	return 0;
}
```

求过 TnT 。

---

## 作者：Licis_Subway (赞：2)

# 题目简述
本题中，题目想让我们设计一种方案来坐火车。

题目中有两种方式：

1. 购买单日票，可以在一天中不限次数地乘坐任意次火车。

2. 购买单程票，可以乘坐 $1$ 次火车。

我们要求出最少的花费。

# 思路
购买单日票或单程票的花费分别求出后进行比大小即可。

每天：

- 单日票价格：$a_i\times x$。
- 单程票价格：$y$。

每天都算出后求 $\min(a_i\times x,y)$。

本题解没有使用数组而使用了变量。
# 代码
```cpp
#include<cstdio>
int y,n,x,ans;
inline int min(const int x,const int y){return x<=y?x:y;}
int main()
{
	scanf("%d%d%d",&n,&x,&y);
	for(int i=1;i<=n;i++)
	{
		int cur;
		scanf("%d",&cur);
		ans+=min(cur*x,y);
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：zhuxiangrui_2010 (赞：2)

# P10708 [NOISG2024 Prelim] Tourist 题解
## 题意
$N$ 天内游览一座城市，有单程票和单日票供你选择，求买票的最小花费。
## 思路
由于有 $N$ 天，我们可以每一天分别讨论。

在每一天中，取 $a_i$ 张单程票和单日票的最小价格，然后将每天花费累加，求出的数即买票的最小花费。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,t=0;
int main(){
    cin>>n>>x>>y;
    for(int i=1;i<=n;i++){
        int k;
        cin>>k;
        t+=min(x*k,y);//累加每天最小花费
    }
    cout<<t;
	return 0;
}
```
~~求通过~~。

---

## 作者：keep_shining (赞：2)

应该都看懂题了吧？

## 思路：
很明显，如果第 $i$ 天乘坐 $a_i$ 次火车，用第一种的价钱为 $a_i \times x$，用第二种的价钱为 $y$，那我们在这两种价钱中取最小值就是第 $i$ 天最少要花费的价钱，然后我们累计 $n$ 天最少要花费的价钱即为答案。

## 代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

#define fst ios::sync_with_stdio(false);cin.tie();cout.tie();
#define Endl endl
#define itn int
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define endl '\n'

const int N=1e6+5;
const int M=2e3+5;

int read()
{
	register int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}

void write(int x)
{
	if(x>9)write(x/10);
	putchar(x%10+'0');
}

int n,x,y,ans,a;

int main()
{
	cin>>n>>x>>y;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        ans+=min(a*x,y);//两种方式取最小值并累计
    }
	cout<<ans;
    return 0;
}
```

---

## 作者：2022_37_yzyUUU (赞：2)

# P10708题解

## 题面

你需要坐 $n$ 天火车，每天要坐 $a_i$ 次火车。

买火车票有两种方案，一种是每次买一张 $x$ 元的一次性票，另一种是买一张 $y$ 元的一天内可以坐无数次火车的票。

求最小花费。

## 思路

要让总花费最小，可以让每天的花费尽量小，所以每天应从两种方案中选一个价格低的方案。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int n,x,y,ans;
int a[1005];//数组多开一点
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<=n;i++)
		ans+=min(x*a[i],y);//取最小值
	cout<<ans;
   return 0;//好习惯
}
```

---

## 作者：AnotherDream (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10708)

这道题考虑贪心。每天选择单程票和单日票花费最少的一个，总的火车票价格固然最少。  

**Code:**
``` cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,x,y;
	cin>>n>>x>>y;
	int sum=0;//局部变量一定要赋值！ 
	for(int i=0;i<n;i++)
	{
		int a;
		cin>>a;
		sum+=min(x*a,y);//x*a是单程票的价格， y是单日票的价格，两者取最小值。 
	}
	cout<<sum;
	return 0;
 } 
```

---

## 作者：Tommyshizichen (赞：1)

简单的模拟，比较每天用单程票和单日票那个便宜并求和即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,x,y,cs;
	cin>>n>>x>>y;
	long long ans=0;
	for(int i=1;i<=n;i++){
		cin>>cs;
		ans+=min(cs*x,y);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：cqbzrjx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10708)

# 思路

一眼**贪心**呀，记 $sum_i$ 为 $a_i$ 的全用单程票或单日票的**最小值**。最后记录**总和**即可。

# AC code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1005;//数据范围
int n,x,y,sum;//sum为最小花费
int a[maxn];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n>>x>>y;//输入
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i];
	}
	for(int i = 1;i <= n;i++)
	{
		sum += min(a[i] * x,y);//求全用单程票或单日票的最小值
	}
	cout<<sum;//输出
	return 0;//完结，撒花
}
```

---

## 作者：leo120306 (赞：1)

每一天，我们都可以选择买单程票还是全日票。因此，我们只需要比较买单程票还是全日票便宜。我们选择便宜的方案，随后计算和即可。考虑到结果最大可能为 $10^{10}$（$10^6\times 10^4$），所以结果要用 long long。

```cpp
#include <cstdio>
using namespace std;

int main(){
	int n,x,y;
	long long ans=0;
	scanf("%d%d%d",&n,&x,&y);
	while(n--){
		int t;
		scanf("%d",&t);
		if(x*t<y) ans+=x*t;
		else ans+=y;
	}
	printf("%lld",ans);
	
	return 0;
}
```

---

## 作者：yfl20130101 (赞：1)

### 思路
我们对于每一天坐火车的次数，算出使用单程票和单日票的价格，然后把答案累加上它们的最小值即可。
### 代码
```cpp
#include<iostream>
using namespace std;
int a[1005];
int main(){
	int n,x,y;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	long long sum=0;
	for(int i=1;i<=n;i++){
		if(y<a[i]*x){
			sum+=y;
		}
		else{
			sum+=a[i]*x;
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P10708)

这道题最开始我想的是用 DFS 解决，然后 TLE 了，实际不用这么麻烦。既然要求最小花费，那么只要在每一天求出当天的最小花费，也就是 $a\times x$ 和 $y$ 的最小值，最终肯定是 $N$ 天总共的最小花费。

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, x, y;
    cin >> n >> x >> y;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        ans += min(a * x, y);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：shlsew (赞：1)

每天乘坐 $a_i$ 次火车，一次需要 $x$ 元，那么需要 $x \times a_i$ 元。

每天可以**无限**次坐火车，需要 $y$ 元。

答案就是 $\sum_{i=1}^{n} \min(x\times a_i,y)$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
signed main(){
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int n,x,y;
	cin>>n>>x>>y;
	int ans=0;
	for(int i=1;i<=n;i++){
		int t;
		cin>>t;
		ans+=min(y,x*t);
	}
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：LYRT_Subway (赞：1)

# P10708
## 解法说明

由题意，每天要乘坐 $a_i$ 次火车。

当购买日票的价格**低于**每一次乘车都购买单程票的价格，就直接选择购买日票。反之，则购买单程票。（显而易见地，直接购买日票比买日票后某些车次再买单程票更便宜）

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long int n,x,y,ans=0;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		int tmp;
		cin>>tmp;
		ans+=min(x*tmp,y);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：FurippuWRY (赞：1)

计算第 $i$ 天中两种购买方式的花费（$a_i\times x$ 和 $y$），取最小值并累加。

```cpp
#include <bits/stdc++.h>
using namespace std;
int x, y, n, a, ans;
int main() {
    cin >> n >> x >> y;
    for (int i = 1; i <= n; ++i) {
    	cin >> a;
    	ans += min(a * x, y);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：luckyqwq (赞：1)

# P10708 [NOISG2024 Prelim] Tourist 题解

### 大致思路：

我们设当天乘火车的次数为 $a_i$，那么每次选的显然是每次 $x$ 元乘上次数，和第 $i$ 天一次性花 $y$ 元，两者取小值，用公式写就是求出所有的 $\min(a_{i} × x, y)$，相加即可。

### 代码实现：

```
#include <bits/stdc++.h>
using namespace std; 
int n, x, y, a[1005], mx;
int main()
{
	cin >> n >> x >> y;
	for(int i = 1;i <= n; ++ i)
	{
		cin >> a[i];
		mx += min(a[i] * x, y);
	}
	cout << mx << "\n";
}
```

这样这道题目就完成啦！！！

---

## 作者：IOI_official (赞：1)

## 思路：

一道贪心题。只需要判断当日用第一种票花钱多还是第二种票花钱多，再将花钱少的哪一种加入到总钱数中即可。

## AC 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,a,c;
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a*x>=y){
			c+=y;
		}
		else{
			c+=a*x;
		}
	}
	cout<<c;
	return 0;
}
```

---

## 作者：JYX0924 (赞：1)

直接按照题意模拟。

对于每一个 $a$，第一种情况是全用单程，令答案是 $b$，则 $b=a \times x$；第二种情况是用一张单日票，答案是 $y$。

所以最优解就是 $\min \{b,y\}$。

下面是我的 AC 代码。

```c
#include<bits/stdc++.h>
#define ll long long 
using namespace std;
ll n,x,y,a,ans;
int main()
{
	ios::sync_with_stdio(false); cin.tie(0);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		cin>>a; ans+=min(x*a,y);
	}
	cout<<ans;
	return 0;
}
```
谢谢大家！！！

---

## 作者：cmask4869 (赞：0)

## 思路
简单的一道模拟题，只需要依次将每天的票价算出来然后比较哪种票便宜，最后将每天票价相加就可以了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std ;
typedef long long ll ;
int a[10005] ;

int main(){
	int n,x,y ;
	cin >> n >> x >> y ;
	for (int i=1 ; i<=n ; i++){
		cin >> a[i] ;
	}
	int ans=0 ;
	for (int i=1 ; i<=n ; i++){
		int sum1=a[i]*x ; int sum2=y ;
		ans+=min(sum1,sum2) ;
	}
	cout << ans ;
	return 0 ;
}
```

---

## 作者：LostKeyToReach (赞：0)

一道贪心题。

我们可以证明每次的代价为 $\min(a_i \times x, y)$ 是最优的。

如何证明呢？首先，我们如果买 $k$ 张单程票（$k < a_i$）和一张单日票，那么代价为 $kx + y$，显然大于等于 $y$，所以这个策略不是最优的。

因此，我们选择全买单程票或买一张单日票最优，代价就是两者的最小值，最后我们累加这些代价即可。

时间复杂度为 $O(n)$。

参考代码如下：

```cpp
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
#define ll long long
#define writes(x) write(x), putchar(' ')
#define writeln(x) write(x), putchar('\n');
static char buf[100000], * pa(buf), * pb(buf);
#define gc pa == pb && (pb = (pa = buf) + fread(buf, 1, 100000, stdin), pa == pb) ? EOF : *pa++
using namespace std;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
template <typename T> void read(T& x) {
    T t = 0, sgn = 1;
    char ch = gc;
    while (!isdigit(ch)) {
        if (ch == '-') sgn = -sgn;
        ch = gc;
    }
    while (isdigit(ch)) {
        t = (t << 3) + (t << 1) + (ch ^ 48);
        ch = gc;
    }
    x = sgn * t;
}
template <typename T, typename ...Args> void read(T& tmp, Args &...tmps) {
    read(tmp); read(tmps...);
}
template <typename T> void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
template <typename T, typename ...Args> void write(T& tmp, Args &...tmps) {
    writes(tmp);
    writes(tmps...);
}
template <typename T> T rand(T l, T r) {
    return rnd() % (r - l + 1) + l;
}
int main() {
    ll n, x, y;
    read(n, x, y);
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll a;
        read(a);
        ans += min(a * x, y);
    }
    write(ans);
}
```

---

## 作者：HsNu1ly7_ (赞：0)

## 思路

根据题意模拟即可。

判断该天车次数乘上 $x$ 小还是 $y$ 小即可。 

代码如下：

```cpp
#include <iostream>
using namespace std ;
#define int long long
int n , x , y ;
int arr[1010] ;
int ans ;
signed main (){
	ios::sync_with_stdio(0) ;
	cin.tie(0) ;
	cout.tie(0) ;
	cin >> n >> x >> y ;
	for ( int i = 1 ;i <= n ; i++ ){
		cin >> arr[i] ;
		if ( arr[i] * x < y ){
			ans += arr[i] * x ;
		}else{
			ans += y ;
		}
	}
	cout << ans ;
	return 0 ;
}
```

---

## 作者：GoodLuckCat (赞：0)

P10708 题解

这题只需要算出每一天买两种票分别花费的钱数，因为要最省钱，所以取最小值相加即可。

$a_i\times x$ 的最大值是 $10^9$，不用判断溢出问题，开 `int` 即可。

代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n,x,y,h=0;
    cin>>n>>x>>y;
    while(n--)
    {
        int a;
        cin>>a;
        h+=min(a*x,y);
    }
    cout<<h;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

## P10708

### Sol

我们首先来分析一下，两种情况要花多少钱。第一种单程票要坐 $a_i$ 次，一次 $x$ 元，共 $x \cdot a_i$ 元。第二种单日票，就是 $y$ 元。显而易见的，第 $i$ 天坐火车最少费用就是 $\min(x \cdot a_i,\ y)$。

### Code

```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
 
using namespace std;
 
using ll = long long;
 
const int kMaxN = 1010, kInf = (((1 << 30) - 1) << 1) + 1, kMod = 998244353;
const ll kLInf = 9.22e18;

ll n, x, y, a[kMaxN], ans = 0;

int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n >> x >> y;
  for (int i = 1; i <= n; ++ i) {
    cin >> a[i];
    if (x * a[i] < y) {
      ans += x * a[i];
    } else {
      ans += y;
    }
  }
  cout << ans << '\n';  
  return 0;
}
```

---

## 作者：cqbzhzf (赞：0)

[博客食用效果更佳](https://www.luogu.com.cn/article/h3votb7a)
### 思路
拿到题目，很容易想到贪心。因为在第 $i$ 天要么直接购买单日票，消费 $y$ 元；要么购买 $a_i$ 张单程票，消费 $a_i \times x$ 元。最后只需要遍历一遍 $a$ 数组取 $\min$ 即可，时间复杂度为 $O(n)$。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,a[1002],ans;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ans+=min(a[i]*x,y);//a[i]*x为买单程票，y为买单日票，ans取每日最小花费
	}
	cout<<ans;
	return 0;
}

---

## 作者：Vct14 (赞：0)

注意到每一天的选择不影响其他天的选择，因此贪心地使用局部最优解即可。如果当天买单程票所用的钱数 $a_ix$ 大于买单日票所用的钱数，那么选择买单程票，否则买单日票。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int n,x,y;cin>>n>>x>>y;
	int sum=0,a;
	while(n--){
		cin>>a;
		sum+=min(a*x,y);
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：fengyuxuan (赞：0)

# 题目大意

要在 $N$ 天内游览一座城市。

第 $i$ 天你需要乘坐 $a_i$ 次火车。

共有以下两种火车票：

- 单程票：花费 $x$ 元购买一张单程票，可以乘坐 $1$ 次火车。

- 单日票：花费 $y$ 元购买一张单日票，可以在一天中不限次数地乘坐任意次火车。

# 题目解析

思路：贪心！！

枚举每个 $a_i$ 计算买单程票和单日票那个更便宜，最后累加即可。

# 最终代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,a,ans;
int main()
{
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)
		cin>>a,ans+=min(a*x,y);
	cout<<ans;
	return 0;
}
```

---

## 作者：Ricardo_M (赞：0)

### 1.思路
很显然，此题是求总和最小，而每天对于火车票的选择都不会影响到第二天，那么题目就变成了求每天所需钱数的最小值，进一步说，就是比较当天是买单程票还是日票划算。

特别的，如果日票和单程票所花钱数一样，那么选择哪种都是一样的。
### 2.代码
```c
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,x,y;
    int tmp=0;//用变量tmp存最小钱数
    cin>>n>>x>>y;//读入
    for(int i=0;i<n;i++){
    	int a;
    	cin>>a;//读入每日所需乘车数
  	//如果买单程票更划算就选择单程票
    	if(a*x<=y){
    	     tmp+=a*x;
	}
     	//否则就买日票
	else{
	     tmp+=y;
	}
   } 
   cout<<tmp;//输出答案
   return 0;
}
```

---

## 作者：watergod (赞：0)

# Tourist 题解

## 分析

这题比较水。

可以想到一个简单的思路，就是对于每一天，都比较买单程票和全日票的价格，只要使每天的价格保证最少，就可以保证整个出行的价格最小。这样就可以达到题目的要求了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,x,y;
int money;

int main(){
	cin >> n >> x >> y;
	int t;
	for(int i=1;i<=n;i++){
		cin >> t;
		money += min(t*x,y);
	}
	cout << money << endl;
	return 0;
}
```

---

## 作者：donnieguo (赞：0)

为了使花费最小，我们要考虑哪种买票方式更优：

两种方法：

- 买 $a_i$ 张票价为 $x$ 元的单程票。

- 买一张票价为 $y$ 的单日票。

所以对于每一天，我们只需要判断 $x \times a_i$ 与 $y$ 的大小，然后将较小者累加起来就行了。

code:

```cpp
#include <iostream>
using namespace std;

int N, x, y;
int sum;
int main()
{
	cin >> N >> x >> y;
	for (int i = 1, k; i <= N; i++)
	{
		cin >> k;
		if (k * x <= y) sum += k * x;
		else sum += y;	
	} 
	cout << sum << '\n';
	return 0;
}
```

---

## 作者：hexuchen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10708)

[更好的阅读体验？](https://www.luogu.com.cn/article/0u8aj13z)

## 题目大意

你会坐 $N$ 天的火车，你可以购买单程票，每坐一次车花费 $x$ 元。你也可以购买单日票，这一天所有要坐的火车钱为 $y$ 元。求这 $N$ 天坐火车的最少花费。

## 思路分析

一道水题。

明显地，一天的旅程只有两种可能：全买单程票和只买单日票。那买单程票还是买单日票呢？我们可以求出全买单程票的钱，即 $a_i \times x$ 元。只买单日票的钱就是 $y$ 元。只要比较它们，取小者求和即可。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,x,y,a,ans=0;
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a;
		int once=a*x;  //全买单程票的钱
		ans+=min(once,y);  //比较，取小者求和。
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

注意到每一天都是独立的，因此我们只要在每天取尽可能少的票价即可。

因此答案就是 $\sum\limits_{i=1}^n\min\{xa_i,y\}$。
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,x,y,ans=0; 
	cin>>n>>x>>y;
	while(n--)
	{
		int d;
		cin>>d;
		ans+=min(x*d,y);
	}
	cout<<ans;
 	return 0;
}
```

---

## 作者：emo_zkt (赞：0)

这道题本人认为也就是个红题。因为 $x$ 元一张单程票，第 $i$ 天有 $a_{i}$ 次车，买单程票一天要花 $a_{i}\times x$ 元，如果比 $y$ 大就买包天的，所以你只需要每次判断 $a_{i}\times x$ 是否大于 $y$ 就行了。取小的那个累加，最终得到答案。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,x,y,a,ans=0;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a*x>=y)ans+=y;
		else ans+=a*x;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Mortidesperatslav (赞：0)

应该是这套题目的打卡题。

贪心，把每个 $a_i \times x$ 和 $y$ 比较，然后求和就好了。

然后讲几点。

## 强化：如果卡空间怎么办？

这题的 $a_i$ 用完就不用了，所以没必要开数组。

## 提问：为什么本题不用开 long long？

相信有人会问这个问题，但是 $ny$ 的最大值是 $10^9$。尽管 $n \times a_i \times x$ 可能爆 `int`，但是当 $x \times a_i > 10^6$ 时显然选择 $y$。所以不用开 `long long`。

代码很简短：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, x, y;
int ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> n >> x >> y;
	for (int i = 1; i <= n; i++){
		int a;
		cin >> a;
		ans += min(a * x, y);
	}
	cout << ans;
}
```

---

## 作者：Drifty (赞：0)

### Solution

建议降红。

直接贪心，对于每一天，选取全买单次票和买一张全天票的最小值即可。

### AC-Code

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	int N, x, y, ans = 0;
    cin >> N >> x >> y;
    for (int i=0, a; i<N; i++)
        cin >> a, ans += min(a * x, y);
    cout << ans;
	return 0;
}
```

---

## 作者：lichenzhen (赞：0)

## 题目大意
你要用 $N$ 天游览一座城市，并且乘坐火车，第 $i$ 天要乘坐 $a_i$ 次火车。火车票单程票 $x$ 元每张，只能用一次；单日票 $y$ 元每张，一天内无限次使用。

求购买火车票需要的最小花费。

## 题目解法
很简单的一道题目，很显然只需要让每天花费最少即可。

每天的花费考虑两种票的价格哪个更低，即当天最小花费为 $a_i\times x$ 与 $y$ 的较小值。

### 参考代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,a,ans;
int main(){
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		cin>>a;
		ans+=(a*x>y)?y:a*x;
	} 
	cout<<ans;
} 
```

---

## 作者：_little_Cabbage_ (赞：0)

# P10708 [NOISG2024 Prelim] Tourist 题解

## 前言

~~失踪人口回归。~~

再不回来水几篇题解该掉橙了。

## 思路

这是一道贪心题。

我们可以发现，对于第 $i$ 天，如果我们全部使用单程票，需要花的钱数是 $a_i\times x$，而使用单日票需要的钱数就是 $y$。

所以，我们比较每一天是使用单程票划算还是单日票划算，如果单程票划算，答案加上 $a_i\times x$，否则答案加上 $y$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1010];
signed main()
{
	long long n,x,y;
	scanf("%lld%lld%lld",&n,&x,&y);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
	}
	long long ret=0;
	for(int i=1;i<=n;i++)
	{
		if(x*a[i]<y)
		{
			ret+=x*a[i];
		}
		else
		{
			ret+=y;
		}
	}
	printf("%lld",ret);
	return 0;
}
```

---

## 作者：ToastBread (赞：0)

## 思路
考虑贪心。

为了让价格最少，每天只有两种买法：
- 买 $a_i$ 张单程票，价格为 $a_i\times x$。
- 买 $1$ 张单日票，价格为 $y$。

当日的最小花费就是两者之间的较小值。总的最小值就是把每一天的最小花费加起来即可。

时间复杂度 $O(N)$，可以接受。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,inp,x,y,ans;//ans 总和 
int main()
{
	cin>>n>>x>>y;
	for(int i = 1; i <= n; i++)
	{
		cin>>inp;
		ans+=min(x*inp,y);//取较小值购买 
	}
	cout<<ans;
	return 0;
}


```

---

## 作者：LG086 (赞：0)

### 分析

单程票 $x$ 元，单日票 $y$ 元。若 $a_i \times x \gt y$，则单日票更划算；否则单程票划算。



------------
### 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,x,y,a,ans;
signed main(){
    cin>>n>>x>>y;
    while(n--)cin>>a,
    ans+=min(a*x,y);
    cout<<ans;
}
```

---

## 作者：jsisonx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P10708)

# 题目分析
读题可知，每一天的决策是独立的，也就是说某一天的决策不受其他天的影响，也不影响其它天。因此，第 $i$ 天只需要比较购买 $a_i$ 张单程票与 $1$ 张单日票，选取花费少的方式。具体地，对于第 $i$ 天来说，答案增加 $\min(a_i \times x,y)$。

# 代码

```
#include<iostream>
using namespace std;
long long ans=0;
int main(){
	int n,x,y;
	cin>>n>>x>>y;
	for(int i=0;i<n;i++){
		int a;
		cin>>a;
		ans+=min(a*x,y);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：nightwatch.ryan (赞：0)

### 思路
比较每天购买 $a_i$ 张单程票的价钱和购买单日票的价钱，哪一个价钱小就买哪个，最后累加起来就是答案。
### 代码
```cpp
#include<iostream>
#define N 1005
#define int long long 
int n,x,y,ans;
signed main(){
	std::cin>>n>>x>>y;
	for(int i=1;i<=n;i++){
		int z;std::cin>>z;
		ans+=std::min(x*z,y); 
	}
	std::cout<<ans;
}
```

---

