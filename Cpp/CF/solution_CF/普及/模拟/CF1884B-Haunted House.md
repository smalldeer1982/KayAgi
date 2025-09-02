# Haunted House

## 题目描述

You are given a number in binary representation consisting of exactly $ n $ bits, possibly, with leading zeroes. For example, for $ n = 5 $ the number $ 6 $ will be given as $ 00110 $ , and for $ n = 4 $ the number $ 9 $ will be given as $ 1001 $ .

Let's fix some integer $ i $ such that $ 1 \le i \le n $ . In one operation you can swap any two adjacent bits in the binary representation. Your goal is to find the smallest number of operations you are required to perform to make the number divisible by $ 2^i $ , or say that it is impossible.

Please note that for each $ 1 \le i \le n $ you are solving the problem independently.

## 说明/提示

In the first test case, we cannot swap any elements, and the number $ 1 $ is not divisible by $ 2 $ .

In the second test case, the initial number is $ 1 $ . It is not divisible by $ 2 $ , but if we perform the operation, then we obtain the number with binary representation $ 10 $ , which is equal to $ 2 $ in decimal representation, thus, it is divisible by $ 2 $ . But this number is not divisible by $ 4 $ and we cannot obtain any other number using the operations.

In the third test case, the initial number is $ 2 $ . For $ i = 1 $ we do not have to perform any operations since the initial number is divisible by $ 2 $ . For $ i = 2 $ we can perform one operation swapping the first two bits (we would obtain $ 100 $ in binary representation, which corresponds to number $ 4 $ ). There is no answer for $ i = 3 $ .

## 样例 #1

### 输入

```
6
1
1
2
01
3
010
5
10101
7
0000111
12
001011000110```

### 输出

```
-1 
1 -1 
0 1 -1 
1 3 -1 -1 -1 
3 6 9 12 -1 -1 -1 
0 2 4 6 10 15 20 -1 -1 -1 -1 -1```

# 题解

## 作者：N_Position (赞：6)

# CF1884B 题解
## 题目翻译
共 `t` 数据，对于每一组数据，有一个正整数 `n` 和一个仅由数字 `0` 和 `1` 组成的长度为 `n` 的字符串。

每一次操作，你可以交换相邻的两个字符。

对于每一个 $i\in\left[1,n\right]$ 输出最小的操作次数使得原字符串对应的二进制数是 $2^{i}$ 的倍数。

## 题目分析
当 $i=1$ 时，显然只要字符串的最后一位为 `0` 即可。
设倒数第 $i$ 个 `0` 位于整个字符串的倒数第 $k_i$ 位，操作所需的次数 $ans_1$ 为 $k_1-1$。

同理当 $i\ne1$ 时，操作次数为 $ans_i=ans_{i-1}+k_i-k$ 次。

对于无解情况：当需要 `0` 的个数大于所有的 `0` 的个数时，显然无解。 
## 代码实现
实现复杂度为 $O(tn)$，其中 `j` 表示最后一个未使用过的 `0` 的位置，注意 `ans` 可能会爆 `long long`。

```cpp
for(ll i=1;i<=n;i++){
	while(s[j] != '0' && j>=0){
		j--;
	}
	if(j < 0){
		printf("-1 ");
	}
	else{
		ans += (n-i-j);
		printf("%lld ",ans);
	}
	j--;
}
```

[完整代码](https://www.luogu.com.cn/paste/ys9shq2p)

---

## 作者：Big_Dinosaur (赞：2)

事实上题目就是让你用最少的操作次数使最后 $i$ 位都变成 $0$。

设 $a_i$ 为 $i$ 的解，$cnt$ 为 $0$ 的个数，则 $i\le cnt$ 时有解，$z_i$ 为倒数第 $i$ 个 $0$ 的下标，解为 $|n-i+1-z_i|+a_{i-1}$，$a_0$ 为 $0$。

原因：让操作次数最少，因让最靠后的 $0$ 进行调换。

[AC Code](https://codeforces.com/contest/1884/submission/229176829)

---

## 作者：Novelist_ (赞：1)

这道题要求我们使用最小的操作次数使原数能被 $2^i$ 整除。而在二进制里，一个数能不能被 $2^i$ 整除，取决于此数最后 $i$ 位是否为零。因此，此题就可以转变为用最小的次数，使原数末尾有 $i$ 个 $0$。

现在，我们设 $x _ {i}$ 是最后 $i$ 中自带的 $0$ 的个数，然后我们只需要从 $i-1$ 位一直向前找，找到 $i-x _ {i}$ 个 $0$ 为止，然后统计一下步数。特别的，如果 $i$ 超过了当前 $0$ 的总数，那就不用找了，直接输出 $-1$ 就行了。

下面是代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long i,j,n,m,b[200005]={},t,tt=0,ttt=0;//记得开long long
  string a;
  cin>>t;
  while(t--)
  {
    cin>>n>>a;
    tt=b[0]=0;ttt=n-1;
    for(i=n-1;i>=0;--i)
    if(a[i]=='0')
    {
      ++tt;
      b[tt]=b[tt-1]+ttt-i;
      --ttt;
    }
    for(i=1;i<=n;++i)
    if(i<=tt)
    cout<<b[i]<<' ';
    else cout<<"-1 ";
    cout<<'\n';
  }
  return 0;
}
```

---

## 作者：xiaoxiaoxia (赞：1)

## 题目大意
这道题目我们不难发现题目说了这么多废话，事实上就是让我们求用最少的操作次数使最后 $i$ 位都变成 $0$。
## 思路概述
然后具体的思路的话就是有 $k$ 个 $0$ 就需要交换 $k$ 次，所以统计一下有多少个 $0$。就好了。
## 代码部分

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int f[1000005],n,pos,cnt;
string s;
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n;
		pos=n-1;
		cnt=0;
		cin>>s;
		f[0]=0;
		for(int i=n-1;i>=0;i--)
		{
			if(s[i]=='0') 
			{
				f[++cnt]=pos-i;
				f[cnt]+=f[cnt-1];
				--pos;
			}			
		}
		for(int i=1;i<=n;i++)
		{
			if(i>cnt) 
				cout<<-1<<' ';
			else 
				cout<<f[i]<<' ';
		}
		cout<<endl;
	}
	return 0; 
}

```

---

## 作者：copper_ingot (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1884B)

一个非常显然的结论是，如果一个二进制数 $x$ 是 $2^i$ 的倍数，那么 $x$ 的后 $i$ 位都为 $0$。所以，第 $i$ 次输出的是使二进制串 $s$ 的后 $i$ 位都为 $0$ 所需要的最小交换次数。

具体过程是这样的：对于每个 $i$，找到在倒数第 $i$ 位左侧的第一个 $0$，这可以用一个 $pos$ 维护。然后计算出把 $pos$ 上的 $0$ 移到倒数第 $i$ 位需要的步数并用 $ans$ 累加。如果找不到有其他的 $0$ 了，就全部输出 $-1$。

最后记得开 `long long`。

$\mathbb{H} \varepsilon \text{r} \mathsf{e} ' \mathfrak{s}\ \mathcal{M} \gamma\ \complement o\texttt{d}\mathbf{e}$：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int t, n, a[200001], pos, ans;
string s;
signed main(){
	scanf("%lld", &t);
	while (t--){
		scanf("%lld", &n); cin >> s; pos = 1, ans = 0;
		for (int i = n - 1; i >= 0; i--) a[n - i] = s[i] - '0';
		a[n + 1] = 0;
		for (int i = 1; i <= n; i++){
			while (a[pos]) pos++;
			if (pos > n){
				for (int j = i; j <= n; j++) printf("-1 ");
				break;
			}
			ans += pos - i;
			a[i] = 0, a[pos] = 1;
			printf("%lld ", ans);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：Igallta (赞：1)

显然，如果是 $2^i$ 的倍数，那么在二进制中 $i$ 位后面肯定都是 $0$。

- 在下文 $0$ 的数量用 $cnt0$ 表示。

这里就分两种情况：

1. $i > cnt0$，肯定无法创造 $i$ 位后面全是 $0$，因为 $cnt0$ 根本填不满。
2. 这一种状况就代表填的满。我们要操作次数最少肯定是选择最近的 $0$ 来进行填充。使用数组进行维护。

这样就行了。

```
#include <bits/stdc++.h>
#define int long long
#define LL k<<1
#define RR k<<1|1
#define lg log2
using namespace std;
const int maxn=4e5+1;
int f[maxn],n,t,pos,cnt;
string s;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		pos=n-1;
		cnt=0;
		cin>>s;
		f[0]=0;
		for(int i=n-1;i>=0;i--){
			if(s[i]=='0') {//统计&维护
				f[++cnt]=pos-i;
				f[cnt]+=f[cnt-1];
				--pos;
			}			
		}
		for(int i=1;i<=n;i++){
			if(i>cnt) cout<<-1<<' ';
			else cout<<f[i]<<' ';
		}
		cout<<'\n';
	}
	return 0; 
}
```

---

## 作者：_Sky_Dream_ (赞：1)

# [传送门](https://www.luogu.com.cn/problem/CF1884B)

引入一个重要的解题关键：$2^i$ 的后 $i$ 位一定是 $0$。

举个栗子：$4_{(10)}=2^2=100_{(2)}$，后 $2$ 位是 $0$。

因为二进制逢二进一，并且 $2_{(10)}=10_{(2)}$，那么 $2^i$ 就是 $i$ 个 $2$ 的二进制数相乘，也就是 $(10_{(2)})^i$，根据二进制乘法法则，末尾有 $i$ 个 $0$。

那么问题就简单了，变成了用最少的步数让字符串末尾有 $i$ 个 $0$，$1 \le i \le n$。

友情提醒：十年 OI 一场空，不开 long long 见祖宗。

Ac Code:
```cpp
//#pragma GCC optimize(1)
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define itn int
#define tni int
#define tin int
#define nit int
#define nti int
#define int long long
using namespace std;
int T,n,ans,sum,b[200005];
string a;
void Main(){
	cin>>n>>a;
	memset(b,0,sizeof(b));
	ans=0;
	sum=n-1;//初始化
	for(int i=n-1;i>=0;--i)
		if(a[i]=='0'){
			++ans;//统计0的个数
			b[ans]=b[ans-1]+(sum-i);//sum-i即为最少移动步数
			--sum;
		}
	for(int i=1;i<=n;++i)
		if(i<=ans)cout<<b[i]<<' ';//0足够
		else cout<<"-1 ";//0不够
	cout<<endl;//注意换行
}
void Enchanted() {
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	cin>>T;
	while(T--)Main();//T组数据
	exit(0);
}
signed main() {Enchanted();}
```

---

## 作者：Shadow_T (赞：0)

### 题目分析

很明显，对于可以整除 $2^i$ 的数二进制的后 $i$ 位一定为 $0$。

- 首先，对于如果 $i$ 大于序列中 $0$ 的数量，那么无法创造出后 $i$ 位全为 $0$，输出 $-1$。

- 对于移动 $0$，最好的就是把最近的 $0$ 移过来。可以使用一个数组维护移过来的数字。

复杂度 $O(tn)$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int f[maxn];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		string s;
		cin>>s;
		int pos=n-1,cnt=0;
		f[0]=0;
		for(int i=n-1;i>=0;i--)
		if(s[i]=='0') 
		{
			f[++cnt]=pos-i;
			f[cnt]+=f[cnt-1];
			pos--;
		}
		for(int i=1;i<=n;i++)
		{
			if(i>cnt) cout<<-1<<" ";
			else cout<<f[i]<<" ";
		}
		cout<<"\n";
	}
}
```

---

## 作者：xhz0311 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1884B)

## 思路分析
题目给出的数据范围为 $\sum n\le2\times10^5$，极限情况为 $t=1,\ n=2\times10^5$。所以显然对每组数据都是线型复杂度。但每组数据都要输出 $n$ 个数，所以对每个 $i$ 都是 $O(1)$ 的。综上：考虑递推。

规定：$k_1$ 为最低位，$k_{n}$ 为最高位。

先给出结论：   
假设已经求出使序列所代表的二进制数被 $2^{i}$ 整除的最少操作次数 $ans_{i}$，则如果要使二进制数被 $2^{i+1}$ 整除的最少操作次数 $ans_{i+1}=ans_{i}+f_{i+1}$，这里 $f_{i+1}$ 指 $k_{i+1},k_{i+2},\dots,k_{n}$ 中，最近的没用过的 $0$ 位到 $i+1$ 位的距离。

这是因为：   
一个二进制数 $k_{1}k_{2}k_{3}\dots k_{n}$ 被 $2^{i}$ 当且仅当 $k_{1}=0,k_{2}=0,\dots,k_{i}=0$（这个表达式后面简记为 $p(i)$）。此时已经可以用 $ans_{i}$ 次操作使 $p(i)$ 成立，则只用考虑最少的操作次数使得 $k_{i+1}=0$。  

两种情况：

- 这一位已经为 $0$，不操作即可（其实这个情况在 $2\le i$ 时是不可能的，因为按此操作方法一定是让 $k_{1}=0,k_{2}=0,\dots,k_{i}$ 中的 `1` 聚集在 $i+1$ 及其相邻的若干位上）。
- 这一位为 $1$，只用找到高位最近没用过的 $0$，用与 $i+1$ 的距离次操作使这个一与找到的零交换位置。

不管怎么样，都是找到更高位（包括自身）中最近的没用过 $0$，再用与 $i+1$ 的距离次操作。

## 代码实现
对每个输入的 $n$ 和字符串 $s$，先翻转并在最前面加个随便什么符号，否则循环是从 $n-1$ 开始倒序的很丑陋（个人看法）而且与上面的标记不符。这只会增加常数。

外层循环记录当前的 $i$ 值，再用一个 $j$ 的内层循环扫描后面最近的没用过的 $0$，更新 $ans$ 并输出。如果后面没有 $0$，了，说明 $0$ 不够用，此时无解，直接输出一堆 $-1$ 并跳出外层循环。

## 注意事项
用 `string s;` 存二进制数，`reverse(s.begin(),s.end()); s=(char)0+s;` 翻转并平移到 $1 \sim n$。   
开 `long long`。   
如果你把 $ans$ 定义到主函数外面去了，注意多测不清空，爆零两行泪。   
新扫描到的 $j$ 必须在之前没用过，因此把 $j$ 定义为一个下标，代表用到了哪一位的 $0$，保证不会把同一个 $0$ 位扫到两次。
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
long long ans,t,n;
string s;
int main()
{
	cin>>t;
	while (t--)
	{
		cin>>n; cin>>s;
		reverse(s.begin(),s.end()); s=(char)0+s;
        int j=1;
		for (int i=1; i<=n; i++)
		{
        	while (s[j]=='1' && j<=n) j++;
			if (j<=n)
			{
				ans+=j-i;//下标相减即为距离
				cout<<ans<<" ";
			}
			else
			{
				for (int k=i; k<=n; k++)
				{
					cout<<-1<<" ";
				}
				break;
			}
			j++;//要保证j没用过!!!
		}
		cout<<endl;
		ans=0;
	}
}
```

虽然看似是两层循环，但对每组数据，$i$ 至多 $1\sim n$，$j$ 至多 $1\sim n$，故时间复杂度为 $O(\sum n)$。

---

## 作者：aCssen (赞：0)

### Solution
首先观察到，一个二进制数能被 $2^i$ 整除当且仅当这个数从低到高的前 $i$ 位均为 $0$，这个应该比较好理解。

接下来考虑如何快速得到结果。

为了方便处理，先把串翻转。

首先我们要满足 $i$ 的条件，就是要把题目给出的串中 $1 \sim i$ 位中的 $1$ 全部交换到 $>i$ 的位置。 

设 $sum_i$ 为前 $i$ 个 $0$ 的**编号**的前缀和，$tot$ 为处理到当前位 $1$ 的**编号**和，$cnt$ 为处理到当前位 $1$ 的数量，则答案为 $sum_{i}-sum_{i-cnt}-tot$。

感性理解一下，我们需要把这 $cnt$ 个 $1$ 移动到前面，最终会有 $i$ 个 $0$ ，所以会需要 $sum_{i}-sum_{i-cnt}$，但是这样会多算一部分，因为这种考虑方式相当于从 $1$ 一位一位的交换，但所有 $1$ 都有一个初始位置，把这些位置的和减去就得到了正确答案。

注意开 `long long`，以及当 $i>z$ 是无解，其中 $z$ 是字符串中 $0$ 的个数。

时间复杂度 $\mathcal{O}(\sum n)$。

### Code
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int maxn=1e5+5;
int a[maxn],n;
ll sum[maxn];
void solve(){
	scanf("%d\n",&n);
	int z=0,cnt=0;
	ll tot=0;
	for(int i=1;i<=n;i++){
		a[i]=getchar()^48;
		if(!a[i]) z++;
	}
	reverse(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(!a[i]){
			cnt++;
			sum[cnt]=sum[cnt-1]+i;
		}
	}
	cnt=0;
	for(int i=1;i<=n;i++){
		if(a[i]){
			tot+=i;
			cnt++;
		}
		if(i>z){
			printf("-1 ");
			continue;
		}
		ll ans=sum[i]-sum[i-cnt]-tot;
		printf("%lld ",ans);
	}
	printf("\n");
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

---

## 作者：forever_nope (赞：0)

借鉴了当前 [另一篇题解](https://www.luogu.com.cn/blog/_post/655309)，加了更多的说明。

## 简化题意

给定一个长度为 $n$ 的二进制串 $S$，求 $f(1),f(2),\cdots,f(n)$。

其中，$f(i)$ 定义为，每次交换相邻的两个二进制位，将 $S$ 的后 $i$ 为全变为 $0$ 的最小交换次数。

## 分析

特殊的，$f(0)=0$。

假设我们已经求出了 $f(i-1)$，那么就可以用 $f(i-1)$ 步将后 $i-1$ 位变为 $0$。

然后考虑再处理一位。

先贪心的考虑这一位，一定是将这个 $1$ 与后面的第一个 $0$ 交换，而交换的花费为这两位的下标相减（需要依次交换这么多个相邻元素。

以上如果不理解的，可以自己手动模拟两个。

然后，为什么一位一位的考虑，就一定是最优解呢？

证明：这个操作方法，截至到每一位，后面所有的 $1$ 一定会依次从后往前占用前面的 $0$，而不存在比这更优的方法。

## 实现

两个指针，一个 $i$ 记录当前的位置，一个 $j$ 记录前面第一个 $0$。

注意：每次都需要将 $j$ 指针前移一位，表示这个 $0$ 已经被占用。

## 代码

评测记录：<https://codeforces.com/contest/1884/submission/230477092>

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(int n, string s) {
    ll ans = 0;
    for (int i = n - 1, j = n - 1; ~i; --i, --j) {
        while (j >= 0 && s[j] == '1') --j;
        if (j < 0) printf("-1 ");
        else printf("%lld ", ans += i - j);
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; string s;
        cin >> n >> s;
        solve(n, s);
    } return 0;
}
```


---

## 作者：WaterSun (赞：0)

# 思路

首先对于一个二进制数，如果它能被 $2^i$ 整除，一定满足在此数中所有的 $1$ 都在 $i$ 或 $i$ 的左边。

那么对于所有在 $i$ 右边的 $1$，都应该到 $i$ 的左边。考虑用 `vector` 维护所有在 $i$ 左边的 $0$ 的位置。

显然对于所有的不合法的 $1$，都会到 $i$ 左边第 $1$ 个 $0$ 的位置，这个可以利用 `lower_bound` 实现。

令这个位置为 $j$，那么对答案的贡献就是 $j - i$。

# code

```cpp
#include <bits/stdc++.h>
#define re register
#define int long long

using namespace std;

int T,n;
string s;

inline void solve(){
	int ans = 0;
	vector<int> v;
	cin >> n >> s;
	reverse(s.begin(),s.end());
	s = ' ' + s;
	for (re int i = n;i;i--){
		if (s[i] == '0') v.push_back(i);
	}
	for (re int i = 1;i <= n;i++){
		if (s[i] == '0') cout << ans << " ";
		else{
			while (!v.empty() && v.back() <= i) v.pop_back();
			if (v.empty()) cout << "-1 ";
			else{
				int id = v.back();
				v.pop_back();
				ans += id - i;
				s[id] = '1';
				cout << ans << " ";
			}
		}
	}
	cout << "\n";
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while (T--) solve();
	return 0;
}
```

---

## 作者：HUANGRUI11 (赞：0)

## 题意描述
给定一个 $01$ 字符串，交换后使其在十进制下成为 $2^i$。

## 思路
观察数据可得，有 $k$ 个 $0$ 就可以满足题意。那么是否有 $i$ 个 $0$ 就是在十进制下是否位 $2^i$。

我们只需要统计 $0$ 的个数，然后计算最小步数即可。

完结撒花。

---

## 作者：Novelist_ (赞：0)

该题实际上是求用最少的操作次数让最后 $i$ 位数字变 $0$。

下文最后连续的数字 $0$ 的个数用 $S$ 来表示。

第一种：$i \le S$

这种就可以整除 $2^i$，那就找最近的 $0$ 来填满。

第二种：$i > S$

这种就是数字 $0$ 不够，无法被 $2^i$ 整除，输出 $-1$。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long i,j,n,m,b[200005]={},t,tt=0,ttt=0;//不开可能会炸
  string a;
  cin>>t;
  while(t--)
  {
    cin>>n>>a;
    tt=b[0]=0;ttt=n-1;
    for(i=n-1;i>=0;--i)
    if(a[i]=='0')
    {
      ++tt;
      b[tt]=b[tt-1]+ttt-i;
      --ttt;
    }
    for(i=1;i<=n;++i)
    if(i<=tt)
    cout<<b[i]<<' ';
    else cout<<"-1 ";
    cout<<'\n';
  }
  return 0;//这是一个好习惯
}
```


---

## 作者：Novelist_ (赞：0)

之前那偏题解有误，请不要通过。

实际就是用最少的操作次数让最后 $i$ 位数字变 $0$。

拥有的数字 $0$ 的个数用 $S0$ 来表示。

第一种：$i \le S0$

这种就可以填满，那就找最近的 $0$ 来填满。

第二种：$i > S0$

这种就是数字 $0$ 的个数供不应求，绝对填不满。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long i,j,n,m,b[200005]={},t,tt=0,ttt=0;//记得开郎朗
  string a;
  cin>>t;
  while(t--)
  {
    cin>>n>>a;
    tt=b[0]=0;ttt=n-1;
    for(i=n-1;i>=0;--i)
    if(a[i]=='0')
    {
      ++tt;
      b[tt]=b[tt-1]+ttt-i;
      --ttt;
    }
    for(i=1;i<=n;++i)
    if(i<=tt)
    cout<<b[i]<<' ';
    else cout<<"-1 ";
    cout<<'\n';
  }
  return 0;
}
```


---

