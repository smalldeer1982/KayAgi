# Basil's Garden

## 题目描述

There are $ n $ flowers in a row, the $ i $ -th of them initially has a positive height of $ h_i $ meters.

Every second, the wind will blow from the left, causing the height of some flowers to decrease.

Specifically, every second, for each $ i $ from $ 1 $ to $ n $ , in this order, the following happens:

- If $ i = n $ or $ h_i > h_{i + 1} $ , the value of $ h_i $ changes to $ \max(0, h_i - 1) $ .

How many seconds will pass before $ h_i=0 $ for all $ 1 \le i \le n $ for the first time?

## 说明/提示

In the first test case, the flower heights change as follows: $ [1, 1, 2] \rightarrow [1, 1, 1] \rightarrow [1, 1, 0] \rightarrow [1, 0, 0] \rightarrow [0, 0, 0] $ .

In the second test case, the flower heights change as follows: $ [3, 1] \rightarrow [2, 0] \rightarrow [1, 0] \rightarrow [0, 0] $ .

## 样例 #1

### 输入

```
4
3
1 1 2
2
3 1
1
9
5
7 4 4 3 2```

### 输出

```
4
3
9
7```

# 题解

## 作者：luckyqwq (赞：6)

# CF1987C Basil's Garden 题解

### 大致意思：

现在有一个序列 $h$，每秒时如果第 $i$ 项，满足 $h_i > h_{i + 1}$，或者 $i = n$，则 $h_i$ 变为 $\max(0,h_{i} - 1)$。问所有 $h_{i}$ 都变成 $0$ 的时间。

### 大致思路：

你会发现这道题目正着想，可谓是思路特别乱，所以考虑逆向思考。我们考虑最后一个数字变为 $0$，要花费最后一个数字的时间。我们设当前数为 $a_{i}$，则后面一个数为 $a_{i + 1}$，接下来进行分类讨论：

- $a_{i} > a_{i + 1}$，那么要花费 $i$ 的时间，可以发现它是与目前其他满足此条件的数互不影响的。

- $a_{i} \le a_{i + 1}$，我们会发现，当 $a_{i + 1}$ 变为 $0$ 的时候，$a_{i}$ 是 $1$，也就是说这种情况下，会花费 $a_{i + 1} + 1$ 的时间。

当然 $a_n$ 的位置是不会受上面条件影响的，由此可知，倒着推，我们设答案为 $res$，那么每次 $res$ 就是 $\max(res +1,a_i)$，也就是上面分类讨论的两种情况取大值，最后输出即可，这样做每次询问的时间复杂度为 $O(n)$，线性复杂度，显然能过。

### 代码实现：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 10;
inline int read()
{
	int r = 0, w = 1;
	char c = getchar();
	while(c < '0' || c > '9'){if(c == '-'){w = -1;}c = getchar();}
	while (c >= '0' && c <= '9'){r = (r << 3) + (r << 1) + (c ^ 48);c = getchar();}
	return r * w;
}
int T, n, a[N];
signed main()
{
	T = read();
	while (T --)
	{
		n = read();
		for (int i = 1;i <= n; ++ i) a[i] = read();
		for (int i = n - 1;i >= 1; -- i) a[n] = max(a[n] + 1, a[i]);//分别是i<=i+1和i>i+1的情况
		cout << a[n] << "\n"; 
	}
	return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：xiaoxiongbinggan (赞：5)

# CF1987C Basil's Garden 题解

### 题目分析：

给出 $n$ 个数，每一秒时这 $n$ 个数会发生两种情况的变化。

第一种：当 $a_{i+1}<a_i$ 时，$a_i-1$ 。

第二种：除以上情况外，不变。

问：何时数组中所有数均为 $0$？

不管怎样，这个数组到最后总会变成降序排列，为什么呢?

### 证明：

第一种情况：未经变化的数组呈升序，(即：对于任何 $i$，都有 $a_{i-1}\le a_i \le a_{i+1}$)。只有最后一个位置的数先减少，当第 $n$ 个数减少到它前一个数减 $1$ 时，倒数第二个数也开始减少，且倒数第二个数一定等于最后一个数 $+1$。以此类推，数组中最后一定是严格递减，且相邻两个数之间的差值为 $1$。

第二种情况：数组相邻两个数之间没有规律，刚开始时每一个比它后一个数大的数会自减，直到数组呈严格递减状（可以自己手写一下，单凭脑子不好想）。

证明结束。

经过以上证明可以发现：从前往后找答案不简单，那不妨从后往前找一找。

## 分析：

第 $n$ 个数变成 $0$ 时花费时间为 $a_n$，若前一个数比这个数小，则前一个数花费的时间为 $a_n+1$(因为需要等到最后一个数减到倒数第二个数减 $1$，此时所花费时间为 $a_n-a_{n-1}+1$，再加上自己减到 $0$ 所花费的时间为 $a_n-a_{n-1}+1+a_{n-1}$ 即为 $a_n+1$ ,前 $n-2$ 个数同理 此时找到最大值即可。

### code:
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'
int T;
int n;
int a[10000000];
int anss(){
	int ans=0;
	for(int i=n;i>=1;i--){
		ans=max(ans+1,a[i]);
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		cout<<anss()<<endl;
	}
	return 0;
}
```

---

## 作者：junee (赞：4)

# CF1987C 题解

## 题目分析

对于一个数，如果他大于后面的数则它每轮减一，可以画一个图理解一下。

![](https://cdn.luogu.com.cn/upload/image_hosting/z7o8tbib.png)

看图发现最高的那条线每轮高度一定都会减 1，如果最高的线跟某条线重合，那么该线也会减 1，对应的那个数也会减 1，那么此时这两条线都是最高的，所以找到 $a_i + i - 1$ 的最大值即可。

## Code

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int N=1e5+10;
int n,T,a[N];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        int k=0;
        for(int i=1;i<=n;i++)k=max(a[i]+i,k);
        cout<<k-1<<"\n";
    }
    return 0;
}
```

---

## 作者：mystic_qwq (赞：3)

前言：赛时被这题薄纱 www（

给一个序列 $\{h_1,h_2,\cdots,h_n\}$，每秒 $h_n\gets \max\{0,h_n-1\},\forall i\in[1,n)$，若 $h_i>h_{i+1}$，则 $h_i\gets \max\{0,h_i-1\}$。问过多少秒全变成 $0$。

考虑从后往前推。首先最后一个数变为 $0$ 花费正好是最后一个数的时间。再考虑前面一个数。发现若该数字开始时小于最后一个数，则后面一个数变为 $0$ 时前面的数是 $1$。否则答案变为前面的数（也就是将前面的数视为最后一个数）。所以我们逆推即可。每次 $ans\gets\max\{ans+1,h_i\}$。

时间复杂度 $O(n)$。

```cpp
int n,h[N];
cin>>n;
for(int i=1;i<=n;++i) cin>>h[i];
int ans=h[n];
for(int i=n-1;i;--i) ans=max(ans+1,h[i]);
cout<<ans<<'\n';
```

---

## 作者：zg_ji (赞：2)

### 题目分析

将 $h_{i}$ 都变为 $0$ 的话，根据题目中给的公式，我们可以发现，只有 $h_{i}-1$ 为 $0$ 或负数时才可以将 $h_{i}$ 变为 $0$，那么我们就可以反向思考，从末尾开始判断。

当最后一个数为 $0$ 的时候，我们所花费的时间为 $n$，当我们将倒数第二个数变为 $0$ 时，前面的数也就是倒数第三个数将会是 $1$，可以由此递推，当 $h_{i}$ 为 $0$ 的时候 $h_{i-1}$ 一定为 $1$。由此可得我的时间可能是这个数列中最大的数或者是老老实实操作完所用的次数。

### Code

```
#include<bits/stdc++.h>
const int N=1e5+100;
using namespace std;

int T; 
int n;
int ans;
int a[N];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--)
	{
		ans=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=n;i>=1;i--)
			ans=max(ans+1,a[i]);
		cout<<ans<<'\n';
	}
	
	return 0;
	
}
```

此题翻译已提交，望审核。

---

## 作者：wmrqwq (赞：1)

# 题目链接

[CF1987C Basil's Garden](https://codeforces.com/contest/1987/problem/C)

# 提示

1. 不妨把这个序列当做一个弹簧来处理。

2. 弹簧会产生连锁反应。

# 解题思路

我们发现这个序列的区间是一段一段的，我们可以将每一段都当成一个弹簧，每两个数都会多产生 $1$ 的贡献，那么这个区间的贡献就是这个区间的最大值加上这个区间的长度减去 $1$。

于是我们就可以定义只要 $a_i > a_{i+1}$，那么就可以从 $i$ 和 $i + 1$ 这两个位置之间断开。

问题至此解决。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
ll t;
ll n;
ll a[1000010],ans,sum;
void solve()
{
	ans=sum=0;
	cin>>n;
	forl(i,1,n)
		cin>>a[i],ans=max(ans,a[i]);
	forr(i,n,1)
	{
		if(a[i]>sum)
			ans=max(ans,sum),sum=a[i];
		else
			sum++;
	}
	cout<<max(ans,sum)<<endl;
}
int main()
{
	IOS;
	t=1;
 	cin>>t;
	while(t--)
		solve();
	QwQ;
}
```

---

## 作者：zhangzirui66 (赞：0)

注意到一盆花有两种情况。

- $a_i>a_{i+1}$ 则需花费 $i$ 个单位时间。
- $a_i\le a_{i+1}$ 则 $a_{i+1}$ 为 $0$ 时 $a_i$ 为 $1$，需要花费 $a_{i+1}+1$ 个单位时间。

设答案为 $ans$，结合两点可得出 $ans$ 每次应更新为 $\max(ans+1,a[i])$。

注意需要倒推，因为 $ans$ 实际是 $a_n$ 的时间，时间复杂度 $O(n)$。

**Code:**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[200005];
int main(){
    int t;
    cin >> t;
    while(t --){
        cin >> n;
        for(int i = 1; i <= n; i ++) cin >> a[i];
        int ans = a[n];
        for(int i = n - 1; i >= 1; i --) ans = max(ans + 1, a[i]);
        cout << ans << "\n";
    }
    return 0;
}
```

---

## 作者：zhoujunchen (赞：0)

做题思路
------
由题目可知只有后面的数能影响到前面的数，我们不妨从后往前遍历。对于单个数字，需要消耗它本身的高度值为时间，每遍历到前一个数字，本个数字应减到前一个数的高度减一，这时耗时又加了一。

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
    cin>>t;
    while(t--){
        int n,h[100005],ans=0;
        cin>>n;
        for(int i=0;i<n;i++)cin>>h[i];
        for(int i=n-1;i>=0;i--)ans++,ans=max(ans,h[i]);
        cout<<ans<<"\n";
    }
    return 0;
}
```

---

## 作者：jwsdy (赞：0)

## 大致思路

据题目描述可知，当 $i=n$ 或者 $h_i>h_{i+1}$ 时 $h_i$ 才会减一，也就是说**后面的数总是对前面的数产生影响**，所以我们不妨**从后往前遍历**来实现操作。

## 解题过程

每次自减均会耗费一秒钟的时间（包括从 $1$ 减到 $0$），使每棵树都减到 $0$，对于单棵树而言，需要耗费它本身的高度值为时间，每遍历到前一棵树，本棵树的高度应减到前一棵树的高度减一才行，此时耗时又增加了 $1$。

**注意**：此题我们要求的是**所有**树木高度均减为 $0$ 的总耗时，则我们需要找的是在遍历过程中**用时最长**的那一棵树的耗时。

奉上代码：

### code
```
#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
//快读 
template<typename T> void read(T&x){
	int s=1;
	x=0;
	char c;
	do{
		c=getchar();
		if(c=='-') s=-1;
	}while(!isdigit(c));
	do{
		x=x*10+c-'0';
		c=getchar();
	}while(isdigit(c));
	x*=s;
}
const int N=2e5+100;
int n,t;
int h[N];
int ans;
signed main(){
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
	read(t);
	while(t--){
		ans=0;
		read(n);
		for(int i=1;i<=n;i++) cin>>h[i];
		for(int i=n;i>=1;i--){
			ans++;//遍历到前一课树，耗时+1 
			ans=max(ans,h[i]);//查找耗时最多的一次 
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/CF1987C)

**思路：**

若 $h_i$ 在 $t_i$ 秒变成 $0$，则 $h_{i+1}$ 在 $t_i$ 秒以前就已经变成 $0$。

$h_i$ 变成 $0$ 至少花费 $h_i$ 秒，$h_{i+1}$ 先变成零至少花费 $t_{i+1}+1$ 秒。

将 $t_i$ 用 $h_i$ 替代，则 $h_i=\max(h_i,h_i+1)$。

时间复杂度 $O(\sum n)$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int T,n,h[N];
int main(){
	cin>>T;
	while(T--){
		cin>>n;
		h[n+1]=0;
		for(int i=1;i<=n;i++)
			cin>>h[i];
		for(int i=n;i>=1;i--)
			h[i]=max(h[i+1]+1,h[i]);
		cout<<h[1]<<"\n";
	}
	return 0;
}
```

---

## 作者：Specthraimn (赞：0)

# Basil’s Garden 题解  
### 大致题意  
有一个长为 $n$ 的数列，对于每一次操作，若 $h_i\gt h_{i-1}$，或是 $i=n$，则 $h_i=\max(0,h_i-1)$。求使数列变为零的最小操作次数。
### 思路  
1. 若该序列为公差为 1 的递减序列，即满足 $H_i = n-i+1(1\le i \le n)$，显而易见地，答案为 $h_1$。
2. 若该数列的任意一项大于以 $h_1$ 为首项，公差为 1 的递减序列，即满足 $H_i=n-i+1(1\le i \le n, i \ne j)$，存在 $h_j$，使得 $h_i-h_j\ge 1$，答案即为 $h_j+j-1$。
3. 若该数列的任意一项小于以 $h_1$ 为首项，公差为 1 的递减序列，即满足 $H_i=n-i+1(1\le i \le n, i \ne j)$， 存在 $h_j$，使得 $h_i-h_j\le 1$，答案仍为 $h_1$。  

综上所述，$ans = \max(a_i-(a_1-i+1))+h_1$，即 $\max(a_i + i - 1)(1\le i \le n)$，可求出 3 种情况。空间复杂度 $O(n)$，时间复杂度 $O(n)$，可以通过。
### AC代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
int a[N];
signed main()
{
	int t;
	cin >> t;
	//多组数据 
	while(t--)
	{
		int n, ans = 0;;
		cin >> n;
		for(int i = 1; i <= n; i++)
		{
			cin >> a[i];
			//输入 
			ans = max(ans, a[i] +i - 1);
			//遍历数组求最大值 
		}
		cout << ans << "\n";
		//输出 (莫忘换行！！) 
	}
	return 0;
}
```
### 完结撒花✿✿ヽ(°▽°)ノ✿

---

## 作者：zhangxiaohan007 (赞：0)

这题其实写起来很简单，但还是 ```CF``` 的惯例，往往都比较的难想 ~~```CF better``` 的翻译我看了半天没看懂。。。~~

回到正题，题目要求所有花都被吹倒需要多久。看到数据范围，肯定又是一道思维题。我们读题发现，当一朵花后面的花比他低时这朵花才会降低。
显而易见，如果后面一朵花比这朵花低，那这朵花肯定就要花它的高度 $h_{i}$ 的时间倒下；如果后面一朵花比这朵花高，那么当后面一朵花被吹倒时当前这朵花还会剩下 $1$ 的高度。

当然，注意到题目最后一朵花无论如何都会变矮，所以我们从后往前统计。

下面贴出代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define inf 2e9
using namespace std;
int n,h[100005];
void solve()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>h[i];
	}
	int ans=0;
	for(int i=n;i>=1;i--)
	{
		ans=max(ans+1,h[i]);
	}
	cout<<ans<<"\n";
}
int main()
{
	int t;
	cin>>t;
	while(t--)solve();
	return 0;
}

```

---

## 作者：zhuxiangrui_2010 (赞：0)

## 翻译
有 $n$ 朵花，第 $i$ 朵的高度为 $h_i$ 。

对于从 $1 \le i \le n$ 的每个 $i$，每秒会发生以下情况：

- **如果 $i=n$ 或 $h_i>h_{i+1}$，则 $h_i$ 的值会变为 $\max(0,h_i−1)$。**

求这些花的高度几秒之后全部为 $0$。
## 题意
给定一个有 $n$ 个数的序列 $h$。对于序列中的每一个数，如果大于序列中的下一个数则每轮减一，求何时 $h$ 中的所有 $h_i$ 都变为 $0$。
## 思路
易知最后一个数变为 $0$ 一定会花费最后一个数大小的时间，而对于前一个数可以分两种情况讨论：

- 如果 $h_{i-1} \le h_i$，$h_i$ 变为 $0$ 时 $h_{i-1}$ 一定是 $1$，总用时为 $h_i+1$ 秒。
- 如果 $h_{i-1} > h_i$，$h_i$ 变为 $0$ 时 $h_{i-1}$ 为 $h_{i-1}-h_i$，总用时为 $h_{i-1}$ 秒。

逆推即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,a[100010];
signed main(){
    cin>>t;
    while(t--){
        int n,k=-114514;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=n;i>=1;i--){
            k++;
            k=max(k,a[i]);
        }
        cout<<k<<endl;
    }
    return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
正难则反。设 $dp_i$ 表示把 $i\sim n$ 置零所要用的最少次数，显然若 $a_i>dp_{i+1}$，则说明后边都处理完了这个还没搞完，$dp_i=a_i$；否则就要等后面搞完后下一分钟它才能搞完，$dp_i=dp_{i+1}+1$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, a[100005];
ll dp[100005];
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n;
		dp[n] = 0;
		for (int i = 0; i < n; ++ i)
			cin >> a[i];
		for (int i = n - 1; ~i; -- i)
			dp[i] = a[i] > dp[i + 1] ? a[i] : dp[i + 1] + 1;
		cout << dp[0] << '\n';
	}
	return 0;
}
```

---

## 作者：technopolis_2085 (赞：0)

动态规划。由于 $h_i$ 要和 $h_{i+1}$ 比较，如果从前往后做的话会有后效性，所以从后往前做。

设 $dp_i$ 表示 $i$ 号元素从什么时候开始每一次操作都会减 $1$。设 $suf_i$ 表示当 $i$ 号元素开始持续减 $1$ 时，$h_i$ 的值。可以理解为 $h_i$ 用了 $dp_i$ 次操作变成了 $suf_i$。

显然，$dp_n$ 等于 $0$，因为从第一次操作开始 $h_n$ 每次都会减 $1$。$suf_n$ 等于 $h_n$。

从后往前推，对于 $i$ 号元素：

- $h_i ≤ suf_{i+1}$。此时此刻 $h_{i+1}$ 等于 $suf_{i+1}$ 并开始持续减 $1$。这意味着当 $h_{i+1}$ 持续减 $1$ 到 $h_i-1$ 时，$suf_i$ 才会开始持续减 $1$。所以此时 $dp_i$ 等于 $dp_{i+1}+suf_i-h_i+1$，$suf_i$ 等于 $h_i$。

- $h_i ＞ suf_{i+1}$。此时需要 $h_i-suf_{i+1}$ 次操作使得 $h_i$ 变为 $suf_{i+1}$，而将 $h_{i+1}$ 变为 $suf_{i+1}$ 需要 $dp_i+1$ 次操作。此时分两种情况：

	情况一：$h_i-suf_{i+1}＞dp_{i+1}$。这说明 $h_i$ 还没有减到 $suf_{i+1}$ 时，$i+1$ 号元素已经开始持续减 $1$ 了，所以 $i$ 号元素会一直减 $1$。根据 $dp_i$ 和 $suf_i$ 的定义，$i$ 号元素从第一次操作就开始一直减 $1$，所以 $dp_i$ 等于 $0$，$suf_i$ 等于 $h_i$。
    
    情况二：$h_i-suf_{i+1}＜dp_{i+1}$。此时 $h_i$ 会用 $h_i-suf_{i+1}$ 次操作变为 $suf_{i+1}$，然后变成之前所说的情况，只不过这 $h_i-suf_{i+1}$ 次操作涵盖在 $dp_{i+1}$ 的次数里了，只需要将 $suf_{i+1}$ 多操作一次就可以使得 $h_i$ 持续减 $1$ 了。所以 $dp_i=dp_{i+1}+1$，$suf_i=suf_{i+1}$。
 
最后，计算答案。$h_i$ 通过 $dp_i$ 次操作变为 $suf_i$，又持续减了 $suf_i$ 次的 $1$ 使其变为 $0$，所以对 $i$ 号来说，答案为 $dp_i+suf_i$。对所有的取最大值即可。

时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
 
const int maxn=1e5+10;
int a[maxn];//指h数组
int dp[maxn];
int suf[maxn];
 
void solve(){
	int n;
	scanf("%lld",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	
	dp[n]=0;
	suf[n]=a[n];
	for (int i=n-1;i>=1;i--){
		int flag=0; 
		if (a[i]<=suf[i+1]) dp[i]=dp[i+1]+(suf[i+1]-a[i]+1);
		else{
			if (a[i]>dp[i+1]+suf[i+1]) dp[i]=0,flag=1;
			else dp[i]=dp[i+1]+1;
		}
		
		if (flag==0) suf[i]=min(suf[i+1],a[i]);
		else suf[i]=a[i]; 
		
//		printf("dp[%lld]=%lld\n",i,dp[i]);
	}
	
	int ans=0;
	for (int i=1;i<=n;i++) ans=max(ans,dp[i]+suf[i]);
	printf("%lld\n",ans);
}
 
signed main(){
	int T;
	scanf("%lld",&T);
	while (T--) solve(); 
	return 0;
}
```

---

## 作者：ANDER_ (赞：0)

考察：动态规划、贪心。
## 题意
给定一个长度为 $n$ 的序列 $f$，每一轮中，当 $i = n \lor f_i > f_{i + 1}$ 为真时，$f_i$ 减一。求序列 $f$ 中所有元素的值均为 $0$ 时，共过去了多少轮。共有 $t$ 组数据。

## 思路
考虑动态规划。

我们可以发现，对于 $f_i$，我们只需要观察 $f_{i +1}$，以及 $f_{i +1}$ 什么时候倒即可将答案转移过来。当 $ f_i$ 要小于等于 $f_{i + 1}$ 的时候，进行转移。这样就可以将答案转移到 $f_1$ 了。

时间复杂度 $O(\sum n)$。

## 代码
```cpp
//by Alexander_1
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, high[100005];
inline void solve() {
    cin>>n;
    for(int i = 1 ; i <= n ; i++) {
        cin>>high[i];
    }
    for(int i = n - 1 ; i >= 1 ; i --) {
        if(high[i] <= high[i + 1]) {
            high[i] = high[i + 1] + 1;
        }
    }
    cout<<high[1]<<endl;
    return;
}
signed main() {
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	cin>>t;
	while(t --) {
		solve();
	}
	return 0;
}
```

---

