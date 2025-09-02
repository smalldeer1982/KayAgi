# [USACO24DEC] Roundabount Rounding B

## 题目描述

奶牛 Bessie 回到学校了！她开始做她的数学作业，在作业中她被要求将正整数四舍五入到 $10$ 的幂。

要将一个正整数 $a$ 四舍五入到最接近的 $10^b$，其中 $b$ 为正整数，Bessie 首先找到从右往左数第 $b$ 个数位。令 $x$ 为这个数位。

如果 $x≥5$，Bessie 将 $a$ 增加 $10^b$。

然后，Bessie 将从右侧开始直至第 $b$ 个数位的所有数位均设置为 $0$。

例如，如果 Bessie 想要将 $456$ 四舍五入到最接近的 $10^2$（百位），Bessie 会首先找到从右往左数第 $2$ 个数位 $5$。这意味着 $x=5$。然后由于 $x≥5$，Bessie 将 $a$ 增加 $100$。最后，Bessie 将 $a$ 中从右侧开始直至第 $2$ 个数位的所有数位设置为 $0$，结果为 $500$。

但是，如果 Bessie 将 $446$ 四舍五入到最接近的 $10^2$，她将得到 $400$。

在看了 Bessie 的作业后，Elsie 认为她已经发明了一种新的舍入方式：链式舍入。要链式舍入到最接近的 $10^b$，Elsie 将首先舍入到最接近的 $10^1$，然后舍入到最接近的 $10^2$
，以此类推，直至舍入到最接近的 $10^b$。

Bessie 认为 Elsie 是错误的，但她太忙于数学作业，无法确认她的怀疑。她请你计算出存在多少个不小于 $2$ 且不超过 $N$ 的整数 $x$（$1≤N≤10^9$），使得将 $x$ 四舍五入到最接近的 $10^P$ 与链式舍入到最接近的 $10^P$ 的结果不同，其中 $P$ 是满足 $10^P≥x$ 的最小整数。

## 说明/提示

### 样例解释
考虑样例中的第二个测试用例。$48$ 应当被计算在内，因为 $48$ 链式舍入到最接近的 $10^2$ 是 $100$（$48→50→100
$），但 $48$ 四舍五入到最接近的 $10^2$ 是 $0$。

在第三个测试用例中，$48$ 和 $480$ 是两个被计算在内的整数。$48$ 链式舍入到 $100$ 而不是 $0$，$480$ 链式舍入到 $1000$ 而不是 $0$。但是，$67$ 不被计算在内，因为它链式舍入到 $100$，与 $67$ 四舍五入到最接近的 $10^2$ 相同。

### 测试点性质
- 测试点 1：样例。
- 测试点 2-4：$N≤10^3$。
- 测试点 5-7：$N≤10^6$。
- 测试点 8-13：没有额外限制。

## 样例 #1

### 输入

```
4
1
100
4567
3366```

### 输出

```
0
5
183
60```

# 题解

## 作者：jianhe (赞：6)

### 前言：
MnZn 第一次打 USACO，降智降到用数位 dp 过了这个题。

喜提洛谷最劣解。

有一说一在理解数位 dp 的前提下还是非常好懂（doge）。
### 题意：
求在 $[2,n]$ 中 **逐位四舍五入** 和 **直接四舍五入** 不同的数的个数。
### 思路：
首先逐位四舍五入肯定不小于直接四舍五入。

容易发现，如果想要两者不同的话，只能是逐位四舍五入多进了一些位。

怎么样才能达到呢？只有一串 $4$ 后面跟上 $\ge 5$ 的数才行。

数位 dp 即可。判当前的有效位数并记录是否填过 $\ge 5$ 的数，按照一串 $4$ 后跟一个 $\ge 5$ 来填，后面的数随便填就可以了。

代码里有详细注释。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=11;
ll T,n,dp[N][N][2];
vector<ll> p;
ll dfs(ll x,bool up,bool z,ll wei,bool wu){
    // x 表示位数（从大到小），up 表示当前是否取满（即当前位是能取到 9 还是只能取到 p[x]）
    // z 表示是否有前导零，wei 表示当前有效位的位数（即去除前导零），wu 表示是否存在 4...4 (>=5)
    if(!~x) return wu;
    if(!up&&!z&&~dp[x][wei][wu]) return dp[x][wei][wu];// 记忆化
    ll ct=0;// 答案
    if(!wei) ct+=dfs(x-1,0,1,0,0);// 前导零特判
    for(int i=0;i<=(up?p[x]:9);i++)
        if((!wei&&i==4)||(wei>=1&&!wu&&i>=4)||wu)
            ct+=dfs(x-1,up&&i==p[x],z&&(!i),wei+1,wu|(i>=5));
            // !wei&&i==4 ：第一位填 1
            // wei>=1&&!wu&&i>=4 ：一串 4 后面填 >=5 的数
            // wu ：前面已经满足条件了，这位可以随便填（只要在范围内）
            // up&&i==p[x] ：下一位是否取满
            // z&&(!i) ：下一位是否还都是前导零
            // wei+1 ：有效位 +1
            // wu|(i>=5)：是否存在 4...4 (>=5)
    if(!up&&!z) dp[x][wei][wu]=ct;// 记忆化
    return ct;
}
ll C(ll n){// 将 n 拆成一位一位
    p.clear();
    while(n) p.push_back(n%10),n/=10;// 十进制拆分
    return p.size()-1;
}
ll solve(ll n){memset(dp,-1,sizeof dp);return dfs(C(n),1,1,0,0);}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin>>T;while(T--) cin>>n,cout<<solve(n)<<"\n";
    return 0;
}
```

---

## 作者：蔡涵秋2011 (赞：5)

[传送门](https://www.luogu.com.cn/problem/P11449)

## 1. 题意简述
其实题面说的很清楚，就是繁琐了一点：

有两种四舍五入的办法，一种是传统的办法，一种是题目里详细解释了的“链式舍入”。

你要计算出存在多少个不小于 $2$ 且不超过 $N$ 的整数 $x$（$1 \leq N \leq 10^9$），使得将 $x$ 四舍五入到最接近的 $10^P$ 与链式舍入到最接近的 $10^P$ 的结果不同。

大致如此，如果依然不懂建议多读几遍题目。

## 2. 思路分析
### 暴力分思路
最直白的做法。

根据题意，很容易想到循环从 $2$ 到 $N$ 的所有数并检查。

代码非常好实现，就不在此展示了。

然后，你将会光荣地得到一片 TLE……这是可以预见的。

### 100分思路

刚开始你肯定很懵，因为发现自己完全不知道如何下手（好吧，其实说的就是刚看到题的我）。

不会怎么办呢？

先举几个例子、打打表会直观很多。

这时候，我们之前的暴力代码就可以发挥用处了。在循环中把符合要求（也就是两种方法结果不同）的数输出，你会发现：

```cpp
45
46
47
48
49
445
446
447
448
……
497
498
499
4445
4446
4447
……
4997
4998
4999
……
```
随便挑一个看看，比如讲 $49$ 四舍五入到 $10^2$，大家都知道四舍五入是 $0$，但是在“链式舍入”里会先把 $49$ 舍入成为 $50$，再成为 $100$，这样两个结果就不一样了。

这样是不是更好理解一点？

与此同时，神奇的事情发生了！

我们仔细观察数据，会发现这些数是有规律的，而且十分明显！开头都是很多个 $4$ 加上末尾一个 $5$，结尾都是一个 $4$ 加上很多个 $9$。（这样讲未必精确，但我个人认为最容易理解）

知道了范围求数量就简单了，减一减就出来了。

## 3. 正确答案
我觉得代码还是比较清楚的，上面看不懂的可以看代码。
```cpp
#include <bits/stdc++.h>
#define int long long // 记得开 long long，否则会爆 
using namespace std;

int T, N, ans; // T，N 意思见题面，ans 是数量 

int f1(int x) // 找开头，具体规律见上面分析 
{
	int ret = 0;
	for (int i = 1; i <= x; i++)
		ret = ret * 10 + 4;
	return ret + 1; // 这里偷了个懒，我是一堆 4 最后加了一个 1，最后出来是一样的 
}

int f2(int x) // 找结尾，具体规律见上面分析 
{
	int ret = 4;
	for (int i = 1; i < x; i++)
		ret = ret * 10 + 9;
	return ret; // 很好理解，不再多说 
}

void solve()
{
	cin >> N;
	int x = 2;
	while (true)
	{
		int num1 = f1(x), num2 = f2(x);
		// 找出开头和结尾 
		if (num1 > N)	break;
		// 超过限制就走人 
		ans += min(num2, N) - num1 + 1;
		// 可能结尾比 N 大，要注意 
		x++;
	}
	cout << ans << endl;
	ans = 0;
}

signed main()
{
	cin >> T;
	while (T--)	solve(); // 这样看得比较清楚 
	return 0;
}
```

---

## 作者：__yrq__ (赞：5)

## 思路：

明显的，当 $n$ 为个位数的时候，两种方法的结果是相同的。\
那我们就可以从两位数开始考虑：

- 当我们直接四舍五入的时候，如果一开始 $n < 50$，那么 $n$ 就会变成 $0$，否则 $n$ 就会变成 $100$。

- 当我们进行链式舍入的时候，如果一开始 $n < 45$，那么 $n$ 就会变成 $0$，否则 $n$ 就会变成 $100$。

很明显只有当 $n \in [45,49]$ 时用这两种方法得到的结果不同。

那么按照这样推下去我们就会得到一个结论：

- 只有在 $n \in [44 \dots 45,499 \dots 9]$ 时，用两种方法得到的结果不同。

那么我们就可以写代码啦！

下面是我赛时写的代码，写的有些复杂了，可以不用这么多 if 的，建议可以去看一下别的题解写的代码。

## 赛时代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n<45) cout<<"0\n";
		else if(n>=45&&n<=49) cout<<n-45+1<<endl;
		else if(n<445) cout<<"5\n";
		else if(n>=445&&n<=499) cout<<5+n-445+1<<endl;
		else if(n<4445) cout<<5+55<<endl;
		else if(n>=4445&&n<=4999) cout<<5+55+n-4445+1<<endl;
		else if(n<44445) cout<<5+55+555<<endl;
		else if(n>=44445&&n<=49999) cout<<5+55+555+n-44445+1<<endl;
		else if(n<444445) cout<<5+55+555+5555<<endl;
		else if(n>=444445&&n<=499999) cout<<5+55+555+5555+n-444445+1<<endl;
		else if(n<4444445) cout<<5+55+555+5555+55555<<endl;
		else if(n>=4444445&&n<=4999999) cout<<5+55+555+5555+55555+n-4444445+1<<endl;
		else if(n<44444445) cout<<5+55+555+5555+55555+555555<<endl;
		else if(n>=44444445&&n<=49999999) cout<<5+55+555+5555+55555+555555+n-44444445+1<<endl;
		else if(n<444444445) cout<<5+55+555+5555+55555+555555+5555555<<endl;
		else if(n>=444444445&&n<=499999999) cout<<5+55+555+5555+55555+555555+5555555+n-444444445+1<<endl;
		else cout<<5+55+555+5555+55555+555555+5555555+55555555<<endl;
	}
    return 0;
}
```

---

## 作者：DrDuck (赞：4)

这道题让我们求链式四舍五入和普通四舍五入的差异。比如数 $4445$ 如果用链式四舍五入，那么将会依次变成 $4450$ 和 $4500$ 和 $5000$ 和 $10000$，与原来的答案 $0$ 不符。

发现了什么？
在进行链式四舍五入的时候，较低位上的 $5$ 会对高位造成影响，但是只有在上一位是 $4$ 的时候才会造成影响，比如 $4435$ 进完位是 $4440$ 不会造成影响。

所以考虑四位数中错误的链式舍入，从 $4445$ 到 $4999$ 都是不行的。

按以上思路，预处理出 $10$ 位数中所有不符合要求的链式舍入。

```cpp
  int p = 5;
	f[2] = 5;
	g[2] = 44;
	h[2] = 50;
	for (int i = 3; i <= 10; i++)
	{
		p = p * 10 + 5;
		f[i] = f[i - 1] + p;
		g[i] = 10 * g[i - 1] + 4;
		h[i] = h[i - 1] * 10;
	}
```
其中数组 $f$ 是错误链式舍入的个数，数组 $g$ 是左区间，数组 $h$ 是右区间。

比如四位数中错误链式舍入的区间就是 $[4445,5000)$。

然后对数所在的区间进行分类讨论。

```cpp
	for (int i = 1; i <= t; i++)
	{
		cin >> n;
		string s = to_string(n);
		int wei = s.length();
		if (g[wei] <= n && h[wei] <= n)//落在区间右侧
		{
			cout << f[wei] << endl;
		}
		else if (g[wei] <= n && h[wei] > n)//落在区间中
		{
			cout << f[wei - 1] + n - g[wei] << endl;
		}
		else//落在区间左侧
		{
			cout << f[wei - 1] << endl;
		}
	}
```
完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n;
int f[20];
int g[20];
int h[20];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	int p = 5;
	f[2] = 5;
	g[2] = 44;
	h[2] = 50;
	for (int i = 3; i <= 10; i++)
	{
		p = p * 10 + 5;
		f[i] = f[i - 1] + p;
		g[i] = 10 * g[i - 1] + 4;
		h[i] = h[i - 1] * 10;
	}
	for (int i = 1; i <= t; i++)
	{
		cin >> n;
		string s = to_string(n);
		int wei = s.length();
		if (g[wei] <= n && h[wei] <= n)//落在区间右侧
		{
			cout << f[wei] << endl;
		}
		else if (g[wei] <= n && h[wei] > n)//落在区间中
		{
			cout << f[wei - 1] + n - g[wei] << endl;
		}
		else//落在区间左侧
		{
			cout << f[wei - 1] << endl;
		}
	}
	return 0;
}
```
拒绝抄袭！

---

## 作者：WFHFAQFXY (赞：4)

# Roundabount Rounding

**观察数字，则有以下规律：**

先分析最高位：

- 最高位如果为 $[5,9]$，那么无论如何总是会有两个方式一样，都是向前进位。
- 最高位如果为 $[1,3]$，那么就算后面进位了，也只能是 $4$ 而不能够进位，自然两个也是一样的。

于是我们发现最高位只能为 $4$，且后面一定要能够进位。

然后分析除了最后的其他位，可分为两种：

- 为 $[5,9]$，直接可以进位。
- 为 $4$，需要后面进位。

然后分析最低位：

- 若前面有 $[5,9]$ 中的任意一个，任意一个数字都可以。
- 若前面全都是  $4$，那么最后一位必须为 $[5,9]$ 中的一个。

# 结论
这个数字一定属于 $[444…45,499…99]$，数字其实不大，在程序前面可以进行打表来获取边界判断并计数即可。

---

## 作者：superLouis (赞：4)

## 题解：P11449 [USACO24DEC] Roundabount Rounding B

本蒟蒻第一次比赛 USACO，没想到居然第一题在我五次提交后通过了，非常兴奋，专门写一篇题解留念一下～

----------
### 1. 大致题意
现在有两种对数进行操作的方法：

1. “直接四舍五入”，即看这个数的首位（最高位）。令这个数的位数为 $p$，若首位 $\ge 5$，则最终答案为 $10^p$；否则，最终答案为 $0$。
2. “链式四舍五入”，即从最低位开始到最高位结束，每位都依次进行四舍五入的操作并且有进位。

我们举一个例子，将 $48$ 分别进行两种四舍五入：

1. “直接四舍五入”，因为 $4 < 5$ 所以答案为 $0$。
2. “链式四舍五入”，答案为 $100$。

现在给你 $t$ 组测试数据，每组数据给你一个数 $n$，求从 $2$ 到 $n$ 的数中两种四舍五入的结果不一样的数的个数。

----------
### 2. 解题思路
我们稍微分析一下就会发现，“链式四舍五入”得到的结果一定大于等于“直接四舍五入”的结果。


还是令 $n$ 的位数是 $p$，则得到的两个答案一定是 $0$ 和 $10^{p+1}$ 中的。两种四舍五入唯一不同的地方其实就是“链式四舍五入”可以进位，即操作的数 $\ge 5$ 时会给下一位进位。

稍加思考就会发现，答案一定是 $444\dots45$ 到 $4999\dots9$ 之间的。我在代码里采用了稍加打表的方法。

----------
### 3. 代码实现
我掉了数不胜数的坑，一点要避开啊！

##### (1) 坑点一
注意比它位数少的也要算上，建议预处理。  
我是这么做的：

1. `const int a[] = {0, 0, 5, 55, 555, 5555, 55555, 555555, 5555555, 55555555, 555555555, 5555555555};` 
2. `for (int i = 1; i <= 11; i++) pre[i] = pre[i - 1] + a[i];`

##### (2) 坑点二
注意要判断 $n$ 与 $4999\dots9$ 的大小。  
我是这么做的：

1. `const int maxx[] = {0, 0, 49, 499, 4999, 49999, 499999, 4999999, 49999999, 499999999, 4999999999, 49999999999};`
2. `min(maxx[digit], n);`

##### (3) 坑点三
注意要判断 $n$ 与 $444\dots45$ 的大小。   
我是这么做的：

1. `const int minn[] = {0, 0, 45, 445, 4445, 44445, 444445, 4444445, 44444445, 444444445, 4444444445, 44444444445};`
2. `if (n < mn) cout << pre[digit-1] << "\n";`

我们回到代码，有点冗余，但懒得改了。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int a[] = {0, 0, 5, 55, 555, 5555, 55555, 555555, 5555555, 55555555, 555555555, 5555555555};
const int minn[] = {0, 0, 45, 445, 4445, 44445, 444445, 4444445, 44444445, 444444445, 4444444445, 44444444445};
const int maxx[] = {0, 0, 49, 499, 4999, 49999, 499999, 4999999, 49999999, 499999999, 4999999999, 49999999999};
int pre[15];
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	for (int i = 1; i <= 11; i++) pre[i] = pre[i - 1] + a[i];
	int t; cin >> t;
	while (t--) {
		int n; cin >> n;
		if (n < 10) {
			cout << "0\n";
			continue;
		}
		int digit = log10(n) + 1;
		int mn = minn[digit];
		if (n < mn) cout << pre[digit-1] << "\n";
		else {
			int x = 0;
			for (int i = 1; i <= digit; i++) x *= 10, x += 4;
			x += 1;
			cout << min(maxx[digit], n) - x + 1 + pre[digit-1] << "\n";
		}
	}
	return 0;
}
```

---

## 作者：Pratty (赞：3)

题意如下：

有两种四舍五入的方式：

- 链式舍入：从个位开始四舍五入，如果四舍不用操作，五入则给十位加一，其余同理，直到最高位。最后最高位判断是舍还是入。
- 整体舍入：直接判断最高位是舍还是入。

如果两种四舍五入的形式使得最高位的舍入情况不同，则称这个数为**异果数**。（此处声明一下，题目中并未对异果数做任何解释，此处使用只是为了后面方便讲解，请悉知。）

现在每次输入一个正整数 $N$，你需要求出 $2\sim N$ 之间有多少异果数。

思路如下：

考虑异果数的性质：要使得两种舍入方式得到的结果不同，无非一种情况：**原数最高位为 $4$，链式舍入时在次高位进一，使最高位为 $5$**，只有这样，才可使最终结果不同。

我们可以通过暴力输出结果发现：$2$ 位的异果数共 $5$ 个，$3$ 位的异果数共 $55$ 个，$4$ 位的异果数共 $555$ 个……，以此类推。若输入的 $N$ 为 $k$ 位，则可以用这种方式提前计算掉 $1\sim k-1$ 位的答案，最后再特判 $N$ 位的答案。

特判方式：通过模拟发现，最小的一个值一定是最低位为 $5$、其他位为 $4$ 的数，最大的值一定为最高位为 $4$，其他位为 $9$ 的数，可以相减计算答案。记得最大值不可以超过 $N$！

代码一枚：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, n, top[1000], ans, don[1000];
signed main() {
	scanf("%lld", &t);
	while (t--) {
		scanf("%lld", &n);
		ans = 0;
		vector<int> shu;
		int x = n;
		while (x) {//计算位数，保存每一位
			shu.push_back(x % 10);
			x /= 10;
		}
		for (int wei = 2; wei < shu.size(); wei++) {
			int num = 0;
			for (int i = 1; i < wei; i++) {
				num = num * 10 + 5;//提前预处理，这一部分亦可以在代码开头存入数组，减少时间的浪费 
			}
			ans += num;
		}
		int num = 0, tt = 4;
		for (int j = 0; j < shu.size(); j++) {
			num = num * 10 + 4;
			if (j) tt = tt * 10 + 9;
		}
		num++;
		ans += max(0LL, min(tt, n) - num + 1LL);
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Swordmaker (赞：3)

# Roundabount Rounding B

# 思路分析
对于 Bessie 的四舍五入，只需找到从右往左第一个大于等于 $5$ 的自然数，而对于链式四舍五入来说**当前数位的值会受到后一位的影响**，且这种影响会一直向前传递至最高位。

那么又该如何思考链式四舍五入的性质呢？

由于前一位会受到后一位的影响，因此可以**从最高位**开始思考，最高位的数的值会被第二位的数的值影响，而第二位的数的值会被第三位的数的值影响……以此类推。

不难得出如下的规律。由于数据范围不大，对每个区间的左端和右端可以打表来进行处理。

```
int fir[10]={0,45,445,4445,44445,444445,4444445,44444445,444444445,4444444445};
int sec[10]={0,50,500,5000,50000,500000,5000000,50000000,500000000,5000000000};//我这里用的是开区间，也可以写成闭区间
```

那么接下来只需对 $N$ 进行搜索即可，看其是否在当前区间内。如果小于区间左端就代表搜索完毕，输出答案。如果大于区间右端就加上这个区间的数的个数，并搜索下一个区间。如果在当前区间内，就加上当前区间内小于等于 $N$ 的数的个数并输出。  

最后附上代码

# AC Code
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,ans=0,n;
int fir[10]={0,45,445,4445,44445,444445,4444445,44444445,444444445,4444444445};
int sec[10]={0,50,500,5000,50000,500000,5000000,50000000,500000000,5000000000};  
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
//	freopen("Roundabount Rounding.in","r",stdin);
//	freopen("Roundabount Rounding.out","w",stdout);
 	cin>>t;
 	while(t--)
 	{
 		ans=0; 
 		cin>>n;
 		for(int i=1;i<=9;i++)
 		{
 			if(n<fir[i]) break;
 			if(n>=sec[i]) ans+=sec[i]-fir[i];
 			else ans+=n-fir[i]+1;
		}
		cout<<ans<<"\n";
	}
    return 0;
}
```

---

## 作者：Mzk2333 (赞：2)

给一个考场做繁了的数位 DP 做法。

发现当且仅当首位为 $4$ 且后面会产生进位时链式舍入和四舍五入到最近的 $10^P$ 的结果不同，即前面全部为前导零后的第一个 $4$ 时开始记录答案。

记录当前状态是否需要产生进位，以及是否顶到限制。在没有顶到限制的情况下，无论进位与否，在个位返回的数都是五个；顶到限制时，在个位需要对当前位再进行一次讨论。

对于非个位对是否进位进行无脑分类讨论即可，代码有注释。

```cpp
#include<bits/stdc++.h>
using namespace std;

int dp[9][9][9];
int num[9],j;

int dfs(int pos,int carry,bool limit,bool zero){
	if(pos==1){
		if(zero) return 0;
		if(limit){ // 有限制
			if(carry){
				if(num[pos]>=5) 
					return num[pos]-4;
				else 
					return 0;
			}else{
				return min(num[pos]+1,5);
			}
		}else return 5; //无限制
	}
	if(!limit && dp[pos][carry][zero]) 
		return dp[pos][carry][zero]; 
	
	int ret=0; 
	int up=limit?num[pos]:9;
	
	if(zero){
		ret+=dfs(pos-1,1,0,1);
		if(up>=4) ret+=dfs(pos-1,1,limit && 4==up,0); //前面为前导零，最高位为 4 且需要进位
	}else{
		for(int i=0;i<=up;++i){
			if(!carry){
				if(i<=3){
					ret+=dfs(pos-1,0,limit && i==up,zero && i==0);
					ret+=dfs(pos-1,1,limit && i==up,zero && i==0);
				} 
				if(i==4)
					ret+=dfs(pos-1,0,limit && i==up,zero && i==0);
			}else{
				if(i>=5){
					ret+=dfs(pos-1,0,limit && i==up,zero && i==0);
					ret+=dfs(pos-1,1,limit && i==up,zero && i==0);
				}
				if(i==4)
					ret+=dfs(pos-1,1,limit && i==up,zero && i==0);
			}// 对于当前位的数字和是否进位进行讨论
		}	
	}
	if(!limit) dp[pos][carry][zero]=ret;
	return ret;	
}
void solve(int x){
	j=0;
	while(x){
		num[++j]=x%10;
		x/=10;
	}
	cout<<dfs(j,1,1,1)<<'\n';
}
signed main(){
   	int T; cin>>T;
   	while(T--){
   		int n; cin>>n;
   		solve(n);
	}
}
```

---

## 作者：masonxiong (赞：2)

# 暴力打表发现规律

首先一个暴力是显然的：我们枚举每一个数，模拟四舍五入以及链式舍入过程，判断其是否合法，并统计答案。

我们可以用这个暴力程序打表，发现这样一个规律：

> 以下范围中的数的四舍五入与链式舍入结果不同：
>
> - $[45,49],[445,499],[4445,4999],[44445,49999]\dots$

我们不妨大胆假设在数据范围大的时候这个规律依然成立，那么我们就很容易写出以下这个程序，并通过本题。

# 根据规律写出代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long integer;
const integer Answer[] = {0, 0, 0, 5, 60, 615, 6170, 61725, 617280, 6172835, 61728390};
const integer Lowerlimit[] = {9, 9, 45, 445, 4445, 44445, 444445, 4444445, 44444445, 444444445, 4444444445ll};
const integer Upperlimit[] = {9, 9, 49, 499, 4999, 49999, 499999, 4999999, 49999999, 499999999, 4999999999ll};
integer t, n, s;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (cin >> t; t--; ) {
        cin >> n, s = to_string(n).size();
        cout << (s == 1 ? 0ll : Answer[s] + max(min(n, Upperlimit[s]) - Lowerlimit[s] + 1, 0ll)) << '\n';
    }
    return 0;
}
```

# 规律的分析

如果这是赛时，只要答案对了就够了，并不需要细究。但是这不是赛时，我们需要分析一下为什么这个规律是正确的。

我们设有一个正整数 $x$。

若 $x$ 的最高位 $\le3$，那么四舍五入肯定会变为 $0$。而链式舍入最多使最高位 $+1$，变为 $4$，之后还是变为 $0$。所以**若 $x$ 的最高位 $\le3$，则四舍五入和链式舍入的结果相同**。

若 $x$ 的最高位 $\ge5$，那么四舍五入肯定变为 $10^P$（其中 $P$ 是最小的满足 $10^P>x$ 的正整数）。而链式舍入最多使最高位 $+1$，变为 $6$，之后还是变为 $10^P$。所以 **若 $x$ 的最高位 $\ge5$，则四舍五入和链式舍入的结果相同**。

若 $x$ 的最高位为 $4$，四舍五入肯定是 $0$，这个时候为了让 $x$ 链式舍入的结果与之不同，其链式舍入的结果只能为 $10^P$。

为了达成这一条件，需要使得次高位能够向最高位进位，也就是**次高位舍入后在 $[5,9]$ 范围内**。若次高位在 $[5,9]$ 范围内，显然满足要求；否则类似的，要求**次次高位舍入后在 $[5,9]$ 范围内**。

这样一直推下去，推到个位不能推了，就看个位是否在 $[5,9]$ 范围内了。这样我们就得出了之前得出的规律。

---

## 作者：Eason_cyx (赞：2)

首先我们打个表找出位数较小的时候的规律。当位数为 $k$ 时，符合条件的数就是 $\underbrace{444\dots444}_{k-1\  个\  4}5 \sim 4\underbrace{999\dots999}_{k-1\ 个\ 9}$。

我们先来考虑对于一个 $N$，计算所有 $K$ 位满足条件的数的个数。显然这个东西就是 $\max(\max({N,4\underbrace{999\dots999}_{k-1\ 个\ 9}}) - \underbrace{444\dots444}_{k-1\  个\  4}5,0)$，这个不难发现。

那么我们只要枚举所有位，累加答案即可。时间复杂度 $O(T\log_{10}N)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
signed main() {
	int t; cin >> t; while(t--) {
		int n; cin >> n;
		long long ans = max(min(n, 49) - 44, 0) + max(min(n, 499) - 444, 0) + max(min(n, 4999) - 4444, 0) + max(min(n, 49999) - 44444, 0) + max(min(n, 499999) - 444444, 0) + max(min(n, 4999999) - 4444444, 0) + max(min(n, 49999999) - 44444444, 0) + max(min(n, 499999999) - 444444444, 0);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：2)

## 思路分析

很显然，这样的数只能介于形如 $44\dots 5$ 和 $499\dots9$ 的数之间。看一眼数据范围，果断打表。

所以说，打表出省一！代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int arr[18] = { 45,49,445,499,4445,4999,44445,49999,444445,499999,4444445,4999999,44444445,49999999,444444445,499999999,4444444445,4999999999 };
int a[10], b[10], n, v, ans;
signed main() {
	ios::sync_with_stdio(0);
	for (int i = 1; i <= 9; ++i)
		a[i] = arr[(i - 1) * 2],
		b[i] = arr[i * 2 - 1],
		cerr << a[i] << " " << b[i] << endl;
	for (cin >> n; n; n--) {
		cin >> v; ans = 0;
		int ps = upper_bound(a + 1, a + 10, v) - a - 1;
		if (v > b[ps]) {
			for (int i = 1; i <= ps; ++i)
				ans += (b[i] - a[i] + 1);
			cout << ans << endl;
		}
		else {
			for (int i = 1; i < ps; ++i)
				ans += (b[i] - a[i] + 1);
			ans += (v - a[ps] + 1);
			cout << ans << endl;
		}
	}
}
```

---

## 作者：hwc2011 (赞：2)

观察到有一部分数据不是很大，可以先~~打个表~~，然后会发现链式舍入和四舍五入不同的数分别是 $45$，$\dots$，$49$，$445$，$\dots$，$499$，$4445$，$\dots$，$4999 \dots$，也就是这些数都在一个 $4 \dots 45$ 至 $49 \dots 9$ 的区间内，为什么呢？  
以 $445$ 为例，四舍五入应化为 $0$，但是链式舍入却化成 $1000$，我们来推一下它是怎么做的：
- 首先按 $10^1$ 舍入，化为 $450$。
- 接着按 $10^2$ 舍入，化为 $500$。
- 最后按 $10^3$ 舍入，化为 $1000$。

然后就会发现原因所在，因为这些数在某一次舍入时会化成 $5 \dots 0$，导致最后会化成 $100 \dots 0$，而不是 $0$。  
发现结论就很好做了，只需要根据 $N$ 的大小，计算它覆盖了哪些区间就行了。
```cpp
#include<bits/stdc++.h>
#define int long long//不要见祖宗！
using namespace std;
int T,n;
signed main(){
	cin>>T;
	while(T--){
		cin>>n;
		int l=45,r=49,ans=0;
		while(l<=n&&l>0){
			ans+=min(r,n)-l+1;
			l=l*10-5;
			r=r*10+9;
		}
		cout<<ans<<'\n';
	}
}
```

---

## 作者：sherry_lover (赞：1)

# P11449 [USACO24DEC] Roundabount Rounding B 题解

[题目传送门](https://www.luogu.com.cn/problem/P11449)

## 思路

考虑符合条件的数的规律。容易发现 $x$ 一定是 $44 \dots 45$ 到 $499 \dots 9$ 之间的数。因为这些数的“正常四舍五入”都为 $0$，而“链式四舍五入”都是 $10^n$，其中 $n$ 是该数的位数。

故打表所有的范围，然后每次遍历所有的范围，统计答案就行了。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,ans,a[15][2] = {{45,49},{445,499},{4445,4999},{44445,49999},{444445,499999},
                    {4444445,4999999},{44444445,49999999},{444444445,499999999}};
int main()
{
	cin >> T;
	while(T--)
	{
		ans = 0;
		cin >> n;
		for(int i = 0;i <= 7;i++)
		{
			ans += max(0,min(a[i][1]-a[i][0]+1,n-a[i][0]+1));
		}
		cout << ans << endl;
	}
	return 0;
}


```

---

## 作者：c_legg (赞：1)

~哇噢，第一次打 USACO 就能写题解。~

## 思路

观察题目我们可以发现：对于一个整数数 $x=\theta\times10^n(1\le\theta\lt10,n\in\mathbb{N})$，如果 $\theta\lt5$，Bessie 就把它约成 $0$；如果 $\theta\ge5$，Bessie 就把它约成 $10^{n+1}$。

对于 Elsie 的“链式舍入”而我们可以把 $x$ 分成两部分：$x=a\times10^n+b\times10^{n-1}(a\in\mathbb{N},1\le a\lt10,1\le b\lt10)$，当 $a\neq4$ 时，情况是很简单的：
* $a\lt4$ 时，Elsie 把它约成 $0$。
* $a\gt4$ 时，Elsie 把它约成 $10^{n+1}$。

当 $a=4$ 时我们来重点考虑：Elsie 约到第二高的数位时，$b$ 已经发生了改变，如果此时 $b\ge5$，Elsie 就把 $x$ 约成 $10^{n+1}$；如果此时 $b\lt5$，Elsie 还是把它约成 $0$。那接下来我们只要考虑 Elsie 会把 $b\times10^{n-1}$ 约成几就行了。

Bessie 和 Elsie 舍入的方法我们都知道了，问题就迎刃而解了。

我们用一个布尔数组 $\text{arr}$ 来表示 Elsie 与 Bessie 是否一致，那算 $x$ 时只要把 $\text{arr}_{b\times10^{n-1}}$ 取出就行了。

## 代码

### 注意点

1. $N$ 比较大（$1\le N\le 10^9$），所以要用 bitset。
2. $T$ 也比较大（$1\le N\le 10^5$），直接在线操作会 TLE，所以要用离线操作，先排序，再求值。
3. 注意数组越界。

``` cpp
#include <bits/stdc++.h>
using namespace std;

int t, cnt, ln=44; // ln 指最长的 N 从 44 开始因为这之前都没有不一致的

bitset<1000000009> arr;

pair<int, pair<int, int> > n[114514]; // 离线操作用来存 N 的数组 第一个是 N 第二个是读入时的编号 第三个是答案

int ans[114514]; // 离线操作用来存答案的数组

int main() {
    for(int xi=10; xi<=pow(10, 9)/5; xi*=10) { // 计算是否一致
        for(int i=xi*4+5; i<xi*5; i++) {
            if(i-xi*4>=xi/2 || (arr.test(i-xi*4) && i-xi*4>=xi/10)) { // 用上面的方法
                arr.set(i, true);
            }
        }
    }

    cin>>t;

    for(int i=0; i<t; i++) { // 看，离线操作是不是很烦
        cin>>n[i].first;
        n[i].second.first=i;
    }

    sort(n, n+t);

    for(int i=0; i<t; i++) {
        for(int j=ln+1; j<=n[i].first; j++) cnt+=arr.test(j);
        n[i].second.second=cnt;
        ln=n[i].first;
    }

    for(int i=0; i<t; i++) {
        ans[n[i].second.first]=n[i].second.second;
    }
    for(int i=0; i<t; i++) { // 输出
        cout<<ans[i]<<endl;
    }
    return 0;
}
```

---

## 作者：signed_long_long (赞：1)

# 题目解法

不难发现，如果一个数 $x$ 满足题目中的条件（链式舍入得到的数不等于普通四舍五入得到的数）一定满足 $44 \cdots 45\le x < 500\cdots 0$，所以题目等价于求 $1\sim n$ 之间有多少个数满足 $44 \cdots 45\le x < 500\cdots 0$。

所以可以用打表的方法，把所有$44 \cdots 45$ 和 $500\cdots 0$ 存起来。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int minn[]={0,45,445,4445,44445,444445,4444445,44444445,444444445,4444444445};
int maxn[]={0,50,500,5000,50000,500000,5000000,50000000,500000000,5000000000};
int max(int a,int b){return a>b?a:b;}
void work(){
	int n;
	int ans=0;
	cin>>n;
	for(int i=1;i<=9;i++){
		if(n>=minn[i]){
			ans+=min(maxn[i]-minn[i],n-minn[i]+1);
		}
	}
	return printf("%lld\n",ans),void();
}
signed main(){
	int T;
	scanf("%lld",&T);
	while(T--) work();
	return 0;
}
```

---

## 作者：Malkin_Moonlight (赞：1)

## Solution

## 28pts

就是暴力分，写两个函数分别计算四舍五入和链式舍入的结果即可。

## 100pts

通过刚才的暴力程序打表找到规律，四舍五入与链式舍入结果不同的范围是：当位数为 $x$，$444 \cdot \cdot \cdot 45$ 到 $499\cdot \cdot \cdot 99$ 就是符合条件的数。其中第一个数有 $x - 1$ 个 $4$，第二个数有 $x - 1$ 个 $9$。

那么，为什么是在这个区间内？我们拿 $4455$ 来举例，四舍五入答案是 $4000$，但是链式舍入答案却是 $10000$。以下是链式舍入的过程。

1. 按 $10^1$ 舍入，变成 $4460$。
2. 按 $10^2$ 舍入，变成 $4500$。
3. 按 $10^3$ 舍入，变成 $5000$。
4. 按 $10^4$ 舍入，变成 $10000$。

发现了吗？是因为在链式舍入中变成了 $5 \cdot \cdot \cdot 0$，最后才会变成 $10 \cdot \cdot \cdot 0$ 的。

答案就是 $\min(N, 499\cdot \cdot \cdot 99) - 444 \cdot \cdot \cdot 45$，但是，当 $N \le 444 \cdot \cdot \cdot 45$ 时，答案为 $0$。

---

## 作者：_EternalRegrets_ (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/P11449)

-----

### 题目大意：
>给定在 $[0,10^9]$ 范围内的整数 $x$，求解 $[0,x]$ 范围内的整数 $t$ **从最高位四舍五入** 与 **从末尾开始到最高位依次四舍五入** 结果不同的 $t$ 的个数。

### Solution:

比较容易发现，对于长度为 $len$ 的 $t$ 来说，满足题意的数字在 $[4...45,49...9]$ （区间边界均为长度为 $len$ 的数）范围内。

同时，$x$ 范围比较小，最大只到 $10^9$，所以可以考虑打表~~来偷懒~~。

对于长度小于 $x$ 的长度的数，直接对答案累加 $[4...45,49...9]$ 中整数的个数即可。

对于长度小于 $x$ 的长度的数，讨论 $x$ 与区间的关系，即可计算。（式子是 ```max(0ll,min(r[len],x)-l[len]+1)```，其中 $len$ 表示 $x$ 的长度）

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;


int L(int n){
    int tmp; tmp=n;

    int ret; ret=0;
    while(tmp){
        tmp/=10;
        ret++;
    }

    return ret;
}

const int l[]={0,0,45,445,4445,44445,444445,4444445,44444445,444444445};
const int r[]={0,0,49,499,4999,49999,499999,4999999,49999999,499999999};

signed main(){
    int t; cin>>t;

    while(t--){
        int x; cin>>x;
        int len; len=L(x);

        int ans; ans=0;
        for(int i=2;i<=len;i++){
            if(i==len){
                ans+=max(0ll,min(r[i],x)-l[i]+1);
            }
            else{
                ans+=r[i]-l[i]+1;
            }
        }

        cout<<ans<<endl;
    }

    return 0;
}
```

---

## 作者：wawatime1 (赞：1)

### 题目大意
给定两种四舍五入的方式：一种直接舍入到最高位，一种从最低位依次舍入。求：$1∼n$ 中有多少个数按照两种方式分别舍入的结果不同。
### 题目分析
枚举几个样例。

我们发现当且仅当首位为 $4$。

且后面的数可以链式舍入到 $10 ^ {p - 1}$ 得到非零值。发现数的长度为 $k$ 的可行的区间为 $[444…45,499…99]$。

这个数字一定属于 $[444…45,499…99]$。

---

## 作者：greater_than (赞：1)

### 思路
直接明着讲，就是求 $ 45 \sim 49 $，$ 445 \sim 499 $，$ 4445 \sim 4999 \dots $ 的个数，每个都要 $ \le n $。     
接着可以观察，$ 45 \sim 49 $ 有 $ 5 $ 个数，$ 445 \sim 499 $ 有 $ 55 $ 个数。答案就是 $ 5 + 55 + 555 + ... $ 加到 $ n \le 499\dots9 $ 然后再加上 $ n - 455\dots5 $ 即可。
### Code:
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,ans;
signed main(){
    cin>>T;
    while(T--){
        cin>>n;
        ans=0;
        for(register int i=45,j=40,k=50;i<=n;j*=10,k*=10,i+=j){
            ans+=min(n-i+1,k-i);
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：GFyyx (赞：1)

## 题目大意
看完英语，讲人话，就是找出 $N$ 以内有多少个形如 $44…5$ 到 $499…9$ 之间的数。

## 考场做法
没话说，就是打表，在 $O(\log_{10}N)$ 的时间内处理完每一组询问。根据题目大意，我们可以把每个位数存在非法四舍五入的个数打表出来，直接查询，综合时间复杂度 $O(T\log_{10}N)$。

## 忠告
USACO 比赛没看懂题最好看看英语原版，一定有收获。

边界条件好好检查，不然 Debug 半天调不出来。

## 场切代码
```cpp
#include<iostream>
using namespace std;
long long a[114],b[114],sum[114];
void init(){
	a[1]=b[1]=0;
	a[2]=5,b[2]=45,sum[2]=5;
	for(int i=3; i<=12; i++){
		a[i]=a[i-1]*10+5;
		b[i]=(b[i-1]-1)*10+5;
		sum[i]=sum[i-1]+a[i];
	}
}//打表
int main(){
	int n,t; cin >> t;
	init();
	long long cnt,x,ans;
	while(t--){
		cin >> n;
		cnt=0,x=n;
		while(x) x/=10,cnt++;//拆位
		if(n-b[cnt]>=a[cnt]) ans=sum[cnt];
		else ans=sum[cnt-1];//边界条件别错
		if(n>=b[cnt]&&n-b[cnt]<a[cnt]) ans+=n-b[cnt]+1;
		cout << ans << endl;
	} 
}
```

---

## 作者：wht_1218 (赞：1)

假设一个正整数 $x$ 从左往右第 $1$ 位是 $4$。那么它四舍五入到最接近的 $10^y$ 将会是 $0$。如果能通过进位使得第 $1$ 位最终为 $5$，那么链式舍入到最接近的 $10^y$ 将不会是 $0$。

不难发现，只要第 $2,3,4\cdots$ 位都 $\ge 4$ 且至少有一位是 $5$，那么就可以进位。依此可以打出暴力（预处理）。

由于小于 $10^y$ 且满足条件的数总是 $444\cdots 45\sim 4999\cdots 9$，所以使用数学方法求解即可。


```cpp
int x;cin>>x;
int p=10,ans=0,p2=4;
long double sum=log10(x)+1;
for(int i=1; ;++i){
  if(i==floor(sum)){
    x=min(x,p/2-1);
    if(x<p2)break;
    ans+=(x-p2);
    break;
  }else ans+=(p/2-p2-1);
  p*=10;
  p2+=(pow(10,i)*4);
}cout<<ans<<"\n";
//有些地方写的很抽象...
```

---

## 作者：shinzanmono (赞：1)

我们发现当且仅当首位为 $4$，且后面的数可以链式舍入到 $10^{P-1}$ 得到非零值。归纳一下可以知道数的长度为 $k$ 的可行的区间为 $[44444\ldots45,49999\ldots99]$，其中每个数字长度都为 $k$。

然后瞎写写就过了，没啥难度，代码不放了。

---

## 作者：vanueber (赞：1)

# 题目大意

给定两种四舍五入的方式：一种直接舍入到最高位，一种从最低位依次舍入。求： $1 \sim n$ 中有多少个数按照两种方式分别舍入的结果不同。

# 题目分析

朴素的想法是按照题意模拟，复杂度肯定爆了。

但是手玩几组数据，可以发现一些规律：

造成结果不同的数一定在区间 $[l,r]$ 中，其中 $l,r$ 满足 

$$
l =\underbrace{44\ldots4}_{n \text{ 个 } 4} x \underbrace{000\ldots0}_{m \text{ 个 } 0}\\
r =\underbrace{44\ldots4}_{n \text{ 个 } 4} x \underbrace{999\ldots9}_{m \text{ 个 } 9}\\
x \in \{5,6,7,8,9\}
$$

感性理解一下：

这些数的数位 $x$ 可以做出贡献，连续舍入下来，使最终的数最高位大于等于 $5$，从而实现进位。

于是可以将这些答案区间预处理出来，加个前缀和，计算答案则二分查找数 $n$ 所在的区间。

时间复杂度 $\Theta(T \log n)$。

# 代码实现


```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

inline int read()
{
	int w=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		w=(w<<1)+(w<<3)+(ch^48);
		ch=getchar();
	}
	return w*f;
}

inline void write(int x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}

int T;
const int maxn=500000;
vector<pair<int,int>> blk;
int pre[maxn],fi[maxn];
int tot;
int to_int(string ss)
{
	int res=0;
	for(int i=0;i<ss.size();++i)
	{
		res=res*10+ss[i]-'0';
	}
	return res;
}
void init()
{
	string b="";
	for(int num_4=1;num_4<=9;++num_4)
	{
		b+="4";
		for(int sec='5';sec<='9';++sec)
		{
			string base=b+"5";
			base[base.size()-1]=sec;
			string s1,s2;
			for(int num=0;num<=9;++num)
			{
				if(to_int(base+s1)>10000000000) break;//太大就break掉
				blk.push_back(make_pair(to_int(base+s1),to_int(base+s2)));
				s1+="0",s2+="9";
			}
		}
	}
	//构造形如上式的区间
	sort(blk.begin(),blk.end());
	tot=blk.size();
	for(int i=1;i<=tot;++i)
	{
		fi[i]=blk[i-1].first;
		pre[i]=pre[i-1]+blk[i-1].second-blk[i-1].first+1;
		//预处理前缀和
	}
}
int x;
signed main()
{
	init();
	int T=read();
	while(T--)
	{
		x=read();
		int pos=upper_bound(fi+1,fi+tot+1,x)-fi-1;//二分
		if(pos==0)
		{
			cout<<0<<endl;
			continue;
		}//分类：数是否在一个区间中，这需要另外贡献答案
		else if(x>=blk[pos-1].first&&x<=blk[pos-1].second)
		{
			cout<<pre[pos-1]+x-blk[pos-1].first+1<<endl;
		}
		else cout<<pre[pos]<<endl;	
	}
	return 0;
}
```

---

## 作者：K_yuxiang_rose (赞：0)

很容易发现满足条件的数就是 $444\dots5$ 到 $499\dots99$，设 $len(n)$ 表示 $n$ 的位数，则第一个数有 $len(n)-1$ 个 $4$，第二个数有 $len(n)-1$ 个 $9$。

于是答案就是 $\min(N,499\dots99)-444\dots5$。特别地，当 $N<444\dots5$ 时，答案为零。

赛时代码比较丑，完全不用这么复杂的。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[15];
signed main()
{
	for(int i=2;i<=10;i++)
	{
		int x=5;
		for(int j=1;j<=i-1;j++) x*=10;
		int y=4;
		for(int j=1;j<=i-1;j++) y*=10,y+=4;
		y++;
		a[i]=x-y;
	}
	int t;
	cin>>t;
	while(t--)
	{
		string s;
		cin>>s;
		int ans=0,x=4;
		for(int i=1;i<s.length();i++) x=x*10+4;
		if(s[0]>='5')
		{
			s[0]='4';
			for(int i=1;i<s.length();i++) s[i]='9';
		}
		int n=s[0]-'0'; 
		for(int i=1;i<s.length();i++) n=n*10+s[i]-'0';
		n-=x;
		if(n<=0) n=0;
		for(int i=1;i<s.length();i++) ans+=a[i];
		ans+=n;
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

## 作者：Your_Name (赞：0)

## 题解
玩样例发现，发现满足条件答案的首位一定是 $4$ 并且后面一定会向第一位有进位，于是答案的区间显然就是形如 $[4555...,4999...]$。

于是直接把表打出来然后直接看 $N$ 到哪里就行。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7 + 10;
int T, n, sum[N], m, ans;
pair<int, int> q[9] = {{45, 49}, {445, 499}, {4445, 4999}, {44445, 49999}, {444445, 499999}, {4444445, 4999999}, {44444445, 49999999}, {444444445, 499999999}};
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> T;
	while(T --){
		cin >> n;
		ans = 0;
		for(int i = 0; i < 8; i ++){
			if(n >= q[i].second)ans += q[i].second - q[i].first + 1;
			else{
				if(n >= q[i].first)ans += n - q[i].first + 1;
				break;
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
```
 _完结撒花。_

---

