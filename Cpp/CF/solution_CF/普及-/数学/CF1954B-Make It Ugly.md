# Make It Ugly

## 题目描述

Let's call an array $ a $ beautiful if you can make all its elements the same by using the following operation an arbitrary number of times (possibly, zero):

- choose an index $ i $ ( $ 2 \le i \le |a| - 1 $ ) such that $ a_{i - 1} = a_{i + 1} $ , and replace $ a_i $ with $ a_{i - 1} $ .

You are given a beautiful array $ a_1, a_2, \dots, a_n $ . What is the minimum number of elements you have to remove from it in order for it to stop being beautiful? Swapping elements is prohibited. If it is impossible to do so, then output -1.

## 说明/提示

In the first testcase, it is impossible to modify the array in such a way that it stops being beautiful. An array consisting of identical numbers will remain beautiful no matter how many numbers we remove from it.

In the second testcase, you can remove the number at the index $ 5 $ , for example.

The resulting array will be $ [1, 2, 1, 2] $ . Let's check if it is beautiful. Two operations are available:

- Choose $ i = 2 $ : the array becomes $ [1, 1, 1, 2] $ . No more operations can be applied to it, and the numbers are not all the same.
- Choose $ i = 3 $ instead: the array becomes $ [1, 2, 2, 2] $ . No more operations can be applied to it either, and the numbers are still not all the same.

Thus, the array $ [1, 2, 1, 2] $ is not beautiful.

In the fourth testcase, you can remove the first three elements, for example. The resulting array $ [5, 3, 3, 3] $ is not beautiful.

## 样例 #1

### 输入

```
4
3
2 2 2
5
1 2 1 2 1
1
1
7
3 3 3 5 3 3 3```

### 输出

```
-1
1
-1
3```

# 题解

## 作者：_ckx_ (赞：5)

## 题目大意

有 $t$ 组数据，每组数据给定一个长度为 $n$ 的“美丽的”数列 $a$。

定义“美丽的”数列：当且仅当对这个数列进行**任意**次操作后，使 $a$ 中每个元素相同。

定义一次操作: 选择一个整数 $i$ $(2 \le i \le n-1)$，若  $a_{i-1}=a_{i+1}$，则可以将 $a_i$ 变为 $a_{i-1}$。

## 题目分析

可以想到 $a$ 中元素最终都会变为 $a_1$ 和 $a_n$ （因为 $a_1$ 和 $a_n$ 必定相等，所以后面都用 $a_1$ 代替）。

因为必须要求满足 $a_{i-1}$ 和 $a_{i+1}$ 相等时才能改变 $a_i$，所以只要有连续两个与 $a_1$ 不相等，这个数列就会不再“美丽”。

所以我们只要让两个与 $a_1$ 不相等的数挨在一起就行了。

可以用 vector 来存储每一个与 $a_1$ 不相等的数的下标，枚举 $i$ $(2 \le i \le |v|)$，$v_i-v_{i-1}-1$ 就是 $ a_{v_i}$ 和 $a_{v_{i-1}}$ 挨在一起所需删掉的数的数量，取个最小值就行了。

另外还有一种把数列变“丑”的办法就是让 $a_1$ 和 $a_n$ 变得不相等（不断删除头或尾直到不相等），因为 $a_1$ 和 $a_n$ 无法操作，所以永远不可能相等，可以再写一个判断，或者像我一样（具体见代码）。

## code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 300010;
int a[N];
vector<int> v;

int main()
{
	int t;
	scanf("%d",&t);
	
	while (t--)
	{
		v.clear(); //注意要clear 
		int n;
		scanf("%d",&n);
		
		for (int i = 1;i <= n;i++)
		{
			scanf("%d",&a[i]);
		}
		bool f = true; //f标记每个元素是否相等 
		for (int i = 2;i <= n;i++)
		{
			if (a[i] != a[i - 1])
			{
				f = false; 
				break; //如果有一个与前项不相等就退出 
			}
		}
		if (f)
		{
			printf("-1\n"); //全部相等时输出-1 
			continue;
		}
		
		v.push_back(0); //把0加入v可以在下面的for循环中随便吧不断删除头的方法判掉 
		for (int i = 2;i <= n;i++)
		{
			if (a[i] != a[i - 1] && a[i] != a[i + 1] && a[i] != a[1])
			{
				v.push_back(i);
			}
		}
		v.push_back(n + 1); //把n+1加入v则可以判掉不断删除尾的方法 
		
		int ans = (int) 2e9; //初始化ans为无穷大 
		int len = v.size();
		for (int i = 1;i < len;i++)
		{
			ans = min(ans ,v[i] - v[i - 1] - 1); //计算要删掉的数的数量，并计算min 
		}
		
		printf("%d\n",ans); 
	}
	
	return 0;
}
```

---

## 作者：xhhhh36 (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF1954B)

# 题目大意
每一次操作可以任选一个 $i$ 满足 $2\le i \le n$ 且 $a_{i-1}=a_{i+1}$，让 $a_{i-1}\to a_i$。一个数组是美丽的表示这个数组进行任意次操作后其中所有数均相等，给定一个长度为 $n$ 的美丽的数组 $a$。求使它不美丽至少要删去数组 $a$ 中的几个数（不能删完），无法完成输出 $-1$。
# 题目解法
可以发现数组中的 $a_1$ 和 $a_n$ 是无法通过操作改变的，所以经过任意次操作后数组中所有的数都会等于 $a_1$，那么要让这个数组不美丽只需让其中一个数不能变成 $a_1$ 即可。

要将 $a_i$ 变成 $a_1$ 需要 $a_{i-1} = a_{i+1} $ 并且 $a_{i-1} = a_1$。因为 $a$ 数组是美丽的，所以与 $a_1$ 不相等的数只能单独存在，不能连续。由于删去与 $a_1$ 不相等的恕不能让原数组变成不完美的。那么只需删去 $a$ 数组中等于 $a_1$ 的连续段中最小的那一段即可。理由如下：
- 若删去的是开头或结尾，那么此时 $a_1$ 与 $a_n$ 不相等，无法通过操作改变这两个数，数组不美丽。
- 否则可以使两个与 $a_1$ 不相等的数挨在一起，同样无法通过操作改变这两个数，数组不美丽。

若整个数组都相等无解。
# AC code
```cpp
#include <bits/stdc++.h>

using namespace std;
int T,n,a[300005];
signed main()
{
	cin>>T;
	while (T--)
	{
		cin>>n;
		int tmp=0;
		for (int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		int ans=INT_MAX;
		for (int i=1;i<=n;i++)
		{
			if (a[i]==a[1]) tmp++;
			else if (tmp) ans=min(ans,tmp),tmp=0;
		}
		if (tmp!=n) ans=min(ans,tmp);
		if (ans==INT_MAX) cout<<"-1"<<endl;
		else cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Wrong_Accept (赞：5)

[传送门](https://www.luogu.com.cn/problem/CF1954B)

## 题目分析

感性理解：一共有 $n$ 个人站成一排，两边的人靠墙。他们有两种身份，一种**杀戮者**，一种**被杀者**。杀戮者杀被杀者需要通过“**左右夹攻**”的方式。如果杀戮者能**杀光**被杀者，则数列是“好数列”。

不难发现，被杀者的生存条件是“**靠墙**”或“**抱团**”。所以，当被杀者中有人“靠墙”或“抱团”时，数列**不再是“好数列”**。

由于题目保证给出的数列是“好数列”，则杀戮者是与 $a_1$ 和 $a_n$ 相同的数，其他数都是被杀者。

不难得出，当我们干掉**任意两个被杀者之间**或**一个被杀者和墙之间**所有的杀戮者时，也就是帮助被杀者“靠墙”或“抱团”，就能让数列不再是“好数列”。贪心可得，我们只需要干掉**两个相邻被杀者之间**与**一个靠墙被杀者和墙之间**杀戮者段中杀戮者**最少的一段**即可。

## AC Code

```cpp
#include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--)
    {
        int n, cnt = 0, ans = 3e5 + 1;
        std::cin >> n;
        std::vector<int> a(n);
        for (auto &it : a)
            std::cin >> it;
        const int f = a.front();
        for (int i = 0; i < n; i++)
        {
            if (a[i] == f)
                ++cnt;
            else
            {
                ans = std::min(ans, cnt);
                cnt = 0;
            }
        }
        ans = std::min(ans, cnt);
        std::cout << (ans == n ? -1 : ans) << std::endl;
    }

    return 0;
}
```

---

## 作者：ReTF (赞：4)

发现一个序列是美丽的，其充要条件是存在某个正整数 $x$，满足 $\forall a_i\neq x$，$2\le i\le n-1 \land a_{i-1}=a_{i+1}=x$。我们把这样的正整数 $x$ 称作是合法的。

进而发现一个 $x$ **可能**是合法的当且仅当其在序列中的出现次数不小于一半。这样的 $x$ 仅可能有一个，把他找出来。题目保证 $x$ 合法。

现在要把序列变成不美丽的。我们把所有等于 $x$ 的元素看为 $1$，把所有不等于 $x$ 的元素看为 $0$。此时需要删掉若干个 $1$ 使得存在两个 $0$ 相邻或者序列开头或结尾为 $0$。答案即为最短 $1$ 连续段的长度。

---

## 作者：Graix (赞：4)

## CF1954B Make It Ugly 题解

### 思路
由题意得，显然在美丽的数列中 $a_1$ 必定等于 $a_n$，这也就引出了使这个数列变得不美丽的一种方法：使 $a_1$ 不等于 $a_n$。考虑到只有 $a_{i-1}$ 等于 $a_{i+1}$ 时才能改变 $a_i$ 的值，所以另一种使数列不美丽的方法就是找到连续的两个不等于 $a_1$ 的数即可。

那么无解的情况就是给出的美丽的数列中数字全部相等。

对于第一种情况，显然只有一个与 $a_1$不相等的数，令与 $a_1$ 不相等的数为 $x$，则只需要从前删到 $x$ 或从后删到 $x$，取两种删法的最小值即可。

对于第二种情况，需要统计出每一个与 $a_1$ 不相等的数的下标，取相邻两个下标差的最小值即可。

### 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
const int maxn=3e5+7;
int a[maxn];
int b[maxn];
int32_t main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		int y=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			 
			if(i!=1&&a[i]==a[i-1])y++;
		}
		if(y==n-1) {
			cout<<-1<<'\n';
		}
		else{
			int ans=LONG_LONG_MAX;
			int cnt=0;
			for(int i=1;i<=n;i++){
				if(a[i]==a[1])cnt++;
				else{
					if(cnt!=0){
						ans=min(ans,cnt);
						cnt=0;
					}
				}
			}
			cout<<min(ans,cnt)<<'\n';
		}
		
	}
	return 0;
}
```

---

## 作者：kimidonatsu (赞：2)

尝试简化题意，容易发现以下结论：

1. 由于不能选取第一个和最后一个元素，所以它们的值始终保持不变，结论显然。
2. 每个元素最多只会被更改一次。注意到变化规律为将 $a_{i - 1}$ 的值修改为 $a_{i + 1}$，之后 $a_i$ 再被赋值为 $a_{i - 1}$，所以 $a_{i + 1}, a_{i - 1}$ 都会保持新值不变，这是因为在任何与它们相关的操作中，$a_i$ 都会被带进来参与运算。
3. 由于我们可以判出应该等于什么值，所以对于不等于这个数的元素进行运算即可。由上知，可能的情况当且仅当 $a$ 中没有两个连续的数字不等于该值。

有上述结论，不难推出做法：找到等于 $a_1$ 的最短数块，删除掉。$O(n)$ 跑即可。

要特判所有元素都等的情况。

[Submission](https://codeforces.com/contest/1954/submission/257723205)

---

## 作者：littlebug (赞：2)

## Description

给定一个长度为 $n$ 的「美丽」的数组 $a$，求删掉 $a$ 中**至少**几个元素后，$a$ 变为不「美丽」的。

定义一个数组 $a$ 是「美丽」的，当且仅当在进行**任意次**以下操作后，$a$ 中所有的元素都相同。

定义一次操作为：选择任意一个 $i$，满足 $2\le i\le n-1$ 且 $a_{i-1}=a_{i+1}$，将 $a_i$ 变为 $a_{i-1}$。

## Solution

首先考虑一个数组是「美丽」的需要满足什么样的条件。

由题意可知，对数组的改变仅当三个连续元素形如 $x,y,x$ 的时候才可以变为 $x,x,x$，而如果出现 $x,y,y,x$ 之类的情况（即两个 $x$ 之间夹着**连续**的任意个 $y$），那这个数组一定不是「美丽」的。因为数组在任意一次操作后一定会出现 $x,x,x$ 的情况，所以，我们可以得知，若数组 $a$ 是「美丽」，则 $a$ 在进行任意次操作后只能变为一个元素。

即：不存在两个（或多个）不同的 $x_1,x_2$，使得「美丽」的数组 $a$ 既可以都变为 $x_1$，也可以都变为 $x_2$。**这是一条很重要的结论**。

接下来，再考虑如何确定这个唯一的 $x$。我们容易知道，因为在一次操作中，$i$ 满足 $2\le i\le n-1$，所以 $a_1$ 和 $a_n$ 一定就是 $x$ 了（前提已知 $a$ 是「美丽」的）。

于是形式化地，我们可以得出数组 $a$ 是「美丽」的当且仅当：

对于数组 $a$ 中所有 $\neq a_1$ 的元素 $a_i$，有 $a_{i-1}=a_{i+1}=a_1$，也就是说不存在两个**连续的且 $\neq a_1$ 的**元素。

既然我们确定了数组 $a$「美丽」的条件，于是问题就迎刃而解了。只需要删除掉数组 $a$ 中从 $a_l$ 至 $a_r$ 的数，满足这段数全部 $=a_1$，且 $a_{l-1}\neq a_1$，$a_{r+1}\neq a_1$ 就可以了，最小化答案就是找所有满足条件的答案的最小值。

即 $a$ 中最短的连续且 $=a_1$ 的子段的长度就是答案。

对于无解的情况，因为只要 $a$ 中有 $\neq a_1$ 的元素就一定有解，所以若 $a$ 中的元素全部相等则无解。

## Code

```cpp
#include<iostream>
#include<cstdio>
#define il inline
#define inf (int)(2e9)
using namespace std;
const int MAXN=3e5+5;
int n;
int a[MAXN];
il void solve()
{
	cin>>n;
	for(int i=1;i<=n;++i)
		cin>>a[i];
	int k=a[1];
	bool same=1;
	for(int i=1;i<=n;++i)
	{
		if(a[i]!=k)
		{
			same=0;
			break;
		}
	}
	if(same)
	{
		cout<<-1<<'\n';
		return;
	}
	int ans=inf,now=0;
	for(int i=1;i<=n;++i)
	{
		if(a[i]==k)
			++now;
		else
		{
			if(now<ans)
				ans=now;
			now=0;
		}
	}
	if(now<ans && now)
		ans=now;
	cout<<ans<<'\n';
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：11514zbs (赞：1)

仔细观察题面，会发现一个突破口（至少我认为是），那就是：

> 选择一个 $i$ 满足 $2 \le i \le n - 1$ 

这就说明了 $a_1$ 和 $a_n$ 是不可能被修改的，那么只要让 $a_1$ 和 $a_n$ 不相等，这道题自然就迎刃而解了。

那么又应该怎样让 $a_1$ 和 $a_n$ 不相等呢？我们可以从左边开始搜索到第 $1$ 个与 $a_1$ 不相等的数，并记录下来要删几个数；再从右边开始搜索到第 $1$ 个与 $a_n$ 不相等的数，并记录下来要删几个数，最后取最小值就可以了。

如果答案等于 $n$ ，这说明要全部删去，所以输出 $-1$ 。

所以我们只要先输入，再分别统计左右两边要上去的数量，接着取最小值，最后判断答案是不是等于 $n$ ，如果是，就输出 $-1$ ，否则就输出两边的最小值。

```cpp
#include <cstdio>
long long a[300005], t, n, b, s;
int main()
{
	scanf("%lld", &t);
	while (t--)
	{
		scanf("%lld", &n);
		b = -1;
		s = n;
		for (int i = 0; i < n; i++)
		{
			scanf("%lld", &a[i]);
		}
		for (int i = 0; i < n; i++)
		{
			if (a[i] != a[0])
			{
				if (s > i - b - 1)
				{
					s = i - b - 1;
				}
				b = i;
			}
		}
		if (s > n - b - 1)
		{
			s = n - b - 1;
		}
		if (s == n)
		{
			printf("-1\n");
		}
		else
		{
			printf("%lld\n", s);
		}
	}
	return 0;
}

```

> 我讲的这么详细你们应该听得懂吧。

 ~~本蒟蒻的第三篇题解awa~~

---

## 作者：liujinxv123 (赞：1)

### 题目大意
就是说经过一些次数操作后，让数组的元素不全部相同，此处的操作是指：若 $a_{i-1}=a_{i+1}$，则用 $a_{i-1}$ 替换 $a_i$。最后求多少次操作后可以让它的元素不全部相同，不可以实现则输出 -1。
### 题目详解
本题共有 2 种情况，其中一种需要特判。

**我们首先判断 -1 的情况：** 
我们发现如果 $a_1=a_2=\cdots=a_n$，此时无论如何替换都无法使数组不美丽，**故输出 -1，以下的代码便是对此段文字的描述。**
```cpp
int last = a[1];
bool bol = 1;
for(int i = 1;i <= n;i ++){
	if(a[i] != last){
		bol = 0;
		break;
	}
}
if(bol){
	cout << "-1\n";
	continue;
}
```
**我们接下来判断其它情况：**
首先我们定义 $cnt$ 变量用来记录数组中有多少个 $a_i=a_1$，并且定义 $ans$ 变量来计算答案，还用一重循环遍历整个数组，并在循环时判断：

当 $a_i=a_1$，将 $cnt$ 加上1；否则 $ans=\min(ans,cnt)$，并将 $cnt$ 清 0。

最后输出 $ans$，下面是这段文字的代码描述：
```cpp
int ans = 0x3f3f3f3f,cnt = 0;
for(int i = 1;i <= n;i ++){
	if(a[i] == last) cnt ++;
	else{
		if(cnt < ans) ans = cnt;
		cnt = 0;
	}
}
if(cnt < ans && cnt) ans = cnt;
cout << ans << "\n";
```
最后我们将两端代码合并在一起，下面给出完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int a[N];
int main(){
	int T;
	cin >> T;
	while(T --){
		int n;
		cin >> n;
		for(int i = 1;i <= n;i ++) cin >> a[i];
		int last = a[1];
		bool bol = 1;
		for(int i = 1;i <= n;i ++){
			if(a[i] != last){
				bol = 0;
				break;
			}
		}
		if(bol){
			cout << "-1\n";
			continue;
		}
		int ans = 0x3f3f3f3f,cnt = 0;
		for(int i = 1;i <= n;i ++){
			if(a[i] == last) cnt ++;
			else{
				if(cnt < ans) ans = cnt;
				cnt = 0;
			}
		}
		if(cnt < ans && cnt) ans = cnt;
		cout << ans << "\n";
	}
	return 0;
}
```

---

## 作者：__bjxx0201__ (赞：0)

## 题面大意

有 $t$ 组数据，对于每一组数据选择一个数字 $i$，满足 $2\le i \le n-1$ 且 $a_{i-1}=a_{i+1}$，将 $a_{i-1}$ 的值变成 $a_i$ 的值。

当这个序列的数字全部相等时，就输出操作的次数，否则输出 `-1`。

## 思路

[题目传送门](https://www.luogu.com.cn/problem/CF1954B)

有解时 $a$ 数组的最终元素就会是 $a_1$ 和 $a_n$，因为这两个数无法改变值。

首先我们需要知道，如果无解，最直接的就是序列数字全部相等，不需要操作了，输出 `-1` 即可。

接下来先枚举每一个可能出现的 $i$，判断是否成立，上文已说明。如果没有一个成立的，也可以输出 `-1` 了。

对于有解时，$2$ 个和第 $a_1$ 不一样的数就可以使得序列不美丽，那么我们就可以找出这两个数字，将之前的所有数字只能够移除了。或者让两个和 $a_1$ 不相等的数挨在一起，也不能改变操作的个数。

---

## 作者：NEKO_Daze (赞：0)

[洛谷CF1954B](https://www.luogu.com.cn/problem/CF1954B) || [CodeForces 1954 B](https://codeforces.com/contest/1954/problem/B)

### 简要题意

对于一个数列，如果可以通过任意次操作，每次操作可以选取非数列两端的一个元素 $a_i$，使 $a_i=a_{i-1}$，最后整个数列所有元素一样，那么这个数列是美丽的。

现给出一个长度为 $n$ 的数列，至少删去几个数才能使其变得不美丽（即无法成为美丽的数列），但不能删完所有元素。若无解输出 `-1`。

### 思路

由于我们只能操作数列中间的元素，所以无论什么时候，$a_1$ 和 $a_n$ 的值都是不变的。那么，如果一个数列可以通过任意次操作后变得美丽，那么一定有 $a_1=a_n$。换而言之，如果想让一个数列变得不美丽，我们只需要使数列的两端元素不再相等即可。

但如果仔细观察样例，容易发现，当整个数列的元素都相等，即所需操作次数为 $0$ 的美丽的数列，这种情况是无解的，当然 $n=1$ 的情况也无解，这两种情况特判输出 `-1` 即可。

对于删数操作，可以从两端开始扫，寻找最近的不同元素并标记，最后取较小的答案即可。时间复杂度为 $O(Tn)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t;
int main()
{
	cin >> t;
	while (t--)
	{
		int n, a[300005];
		cin >> n; bool flag = true;
		for (int i = 1; i <= n; i++) {cin >> a[i]; if (i > 1 && a[i] != a[1]) flag = false;}
		if (n == 1 || flag) cout << "-1\n";
		else {
			int l, r;
			for (int i = 2; i <= n; i++)
			{
				if (a[i] != a[1]) {l = i; break;}
			}
			for (int i = n-1; i >= 2; i--)
			{
				if (a[i] != a[n]) {r = i; break;}
			}
			cout << min(l, r) - 1 << endl; //注意到记录的是不同元素的值，这个元素并不用删除，所以要对答案-1
		}
	}
}
```

---

## 作者：floodfill (赞：0)

# CF1954B Make It Ugly 题解
### 题目大意
给定一个长度为 $n$ 的美丽的数列 $a$，求使它不美丽至少要删去当中的几个数（不能删完）。若无法完成，输出 ```-1```。

定义：
- 一个数列是美丽的，当且仅当该数列进行任意次操作后数列中的所有元素均相等。
- 选择一个 $i$ 满足 $2≤i≤n−1$ 且 $a_{i-1}=a_{i+1}$，即可将 $a_i$ 的值修改为 $a_{i-1}$ 的值。
### 大致思路
由题意，在一个美丽的数列中，第 $1$ 个数和第 $n$ 个数显然是不能操作的，它们的值也就保持不变。更进一步地，我们可以由此发现在一个美丽的数列中第 $1$ 个数和第 $n$ 个数相等，即
 $$a_{1}=a_{n}$$
 由上，只要把任意一边破坏，这个数列就不再美丽了。

另外，我们还需要注意数列项项相等的情况，即对于 $∀i,j∈[1,n]$ 存在 $a_i= a_j$，以及 $n=1$ 的情况。

这两种情况就需要特判了。显然，我们无法进行操作，所以数列必然是美丽的。直接输出 ```-1``` 即可。

只要知道这几点，解题就会容易一些。~~代码就不贴了~~，希望对你有帮助。

---

## 作者：TemplateClass (赞：0)

注意到每次只会修改 $a _ 2 \sim a _ {n - 1}$ 这些位置的数，所以它们最终都会等于 $a _ 1$ 或 $a _ n$。由于题目说操作后 $a$ 全部相等，所以给定的 $a _ 1$ 必等于 $a _ n$，设它们的值为 $x$。

让序列变得不美丽的最容易想到的方法就是使 $a _ 2 \sim a _ {n - 1}$ 中的某个元素永远无法 $= x$。思考修改操作的过程，显然 $a _ i \leftarrow x$ 的前提是 $a _ {i - 1} = a _ {i + 1} = x$。换句话说，由于要求是 $a _ {i - 1} = a _ {i + 1} = x$，也就意味着那些 $\neq x$ 的元素（例如此处的 $a _ i$）只能单独地出现，被夹在两个 $x$ 之间（例如此处的 $a _ {i - 1}$ 和 $a _ {i + 1}$）。

不难发现，删除掉那些 $\neq x$ 的元素只会使 $a$ 更快地全部相等。所以我们考虑删除一些 $= x$ 的元素。由于我们提到，那些 $\neq x$ 的元素只能单独地出现，被夹在两个 $x$ 之间。所以我们考虑让两个 $\neq x$ 的元素相邻即可。不难发现删除元素个数最少的办法即为删除掉一段连续的等于 $x$ 的区间。

注意特判 $a$ 全部相等的情况，由于不能删完，所以此时无解，输出 $-1$。

```cpp
const int N = 3e5 + 5;

int n, a[N];

inline bool check() {
	for(int i = 2; i <= n; ++i) {
		if(a[i] != a[i - 1]) {
			return false;
		}
	}
	return true;
}
	
void solve(){
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		std::cin >> a[i];
	}
	
	if(check()) {
		std::cout << -1 << "\n";
		return ;
	}
	
	int len = 0, ans = n;
	for(int i = 1; i <= n; ++i) {
		if(a[i] == a[1]) {
			++len;
		} else {
			ans = std::min(ans, len);
			len = 0;
		}
	}
	ans = std::min(ans, len);
	
	std::cout << ans << "\n";
}
```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1954B)

# 题意：

一个数组中，对于一个位置，其两边的数字相同，则可以将中间的数字变为与之一样。如果最后能将所有数字变为同一个，则称原数组为美丽的数组、现在给出一个美丽的数组，需要通过移除一些数字，破坏它的美丽，即让其最终无法变为同一个数字。问最少需要移除多少个。

# 思路：
一个美丽的数组，它的第一个元素和最后一个元素一定是一样的，因为我们变化数据只能选择中间的数，两边无法操作。

所以我们想将他变的不美丽，第一种方法就是破坏这个性质，从左找到第一个不等于 $a_1$ 的数据，将左边的全部移除，这样新的第一个就不等于我们的最后一个了。同理，也可以从右边找到第一个不等于 $a_1$ 的数据，把它右边的所有数据移除，这样新的最后一个就不等于我们的第一个了。

再思考，对于中间的元素，如果我们能够通过移除，使得两个连续的数字不等于 $a_1$，也可以达到目的。因为如果两个连续的数字都与 $a_1$ 不同，我们无法通过变化使他们两个均变为 $a_1$（可以自己思考一下，一个数据一定只能变为与他相邻左右数据相同），比较以上三种方法，找到最短的一种，便是我们的答案了。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int t,n,a[N],s,ans=INF;
signed main(){
	cin>>t;
	while(t--){
        cin>>n;
        s=0;
        ans=3e5+10; 
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            if(a[i]!=a[1]){
                ans=min(i-s-1,ans);
                s=i;
            }
        }
        ans=min(ans,n-s);
        if(ans==n){
            cout<<-1<<endl;
        }else{
            cout<<ans<<endl;
        }
	}
	return 0;
} 
```
完结撒花~

---

## 作者：MA_tian (赞：0)

# 题目大意
给你一个数组，保证这个数组可以通过特殊操作变得全是同一个数。现在你可以删除其中的数，问至少要删除多少才能使得上述情况不成立。

特殊操作定义为：若 $ a_{i-1} = a_{i+1} $，则用 $ a_{i-1} $ 替换 $ a_i $。
# 题目解法
观察题面后不难得出结论，只有当左右两端相等时才能完成特殊操作。也就是说，只要能破坏左右两边任意一边，就足以破坏特殊操作了。于是得出做法，遍历整个数组，寻找最短的相同区间，即是答案。

注意，本题需要特判所有数都相等的情况，以及 $ n=1 $ 的情况。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,a[300005];
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		if(n==1){
			cout<<-1<<endl;
			continue;
		}
		int flag=0;
		for(int i=0;i<n;i++){
			if(a[i]!=a[0]){
				flag=1;
				break;
			}
		}
		if(!flag){
			cout<<-1<<endl;
			continue;
		}
		int ans=20230128,cnt=-1;
		for(int i=0;i<n;i++){
			if(a[i]!=a[0]){
				ans=min(ans,i-cnt-1);
				cnt=i;
			}
		}
		ans=min(ans,n-cnt-1);
		if(ans==n){
			cout<<-1<<endl;
			continue;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：HasNoName (赞：0)

### 思路

由于一开始时数列美丽，所以最后一定只能将所有数变成第一个数。

只需要将两个和第一个数不同的数放在一起则数列不美丽。

考虑模拟。

### 代码

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=300005;
int a[N],n;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n;
        int ans=1e9;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
        }
        int t=a[1];
        int w=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]==t)continue;
            if(!w)w=i;//更新坐标
            else
            {
                ans=min(ans,i-w-1);//得到最小距离
                w=i;
            }
        }
        for(int i=1;i<=n;i++)//开头或结尾连续相同的数字删除也可以
        {
            if(a[i]!=a[1])
            {
                ans=min(ans,i-1);
                break;
            }
        }
        for(int i=n;i>=1;i--)
        {
            if(a[i]!=a[n])
            {
                ans=min(ans,n-i);
                break;
            }
        }
        if(ans==1e9)ans=-1;//无解
        cout<<ans<<'\n';
    }
    return 0;
}
```

---

## 作者：Expert_Dream (赞：0)

我们发现，如果一个字符串形如 ```aba```，那么 ```a``` 会合并，然后由此不断继续合并。我们要组织这种情况的个发生。

所以说，我们当遇到上面的情况的时候，我们需要对于左边和右边分别一直循环遍历，找到一个不同的数，即可停止。因为在停止之前，这些数都必须删除，不然，这些数会因为中间的那个不断合并。

所以，遍历左边和右边，然后取最小值，更新答案即可。

见代码：

```cpp
// Author: gsczl71
// Copyright (c) 2024 gsczl71 All rights reserved.
// Problem: B. Make It Ugly
// Contest: Codeforces - Educational Codeforces Round 164 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1954/problem/B
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Date: 2024-04-12 22:46:51

// #pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define i128 __int128
#define ull unsigned long long
#define pii pair<int,int>
#define pll pair<long long, long long>
#define fs first
#define sc second
#define x0 _x0_
#define y1 _y1_
#define endl '\n'
#define re register
#define pb push_back
#define vi vector<int>
#define pq priority_queue
#define mem(a,x) memset((a),(x),sizeof(a))
#define debug puts("AK IOI")
#define sz(s) (int)(s.size())
#define all(a) a.begin(),a.end()
#define rd(l,r) (myrand()%(r-l+1)+l)
#define print(x) {cout<<x<<endl;return;}
#define ctn(e) if(e) continue
#define brk(e) if(e) break
#define rt(e) if(e) return
#define ll_(e) (1ll*(e))
#define For(x,y,z) for(int x = y;x <= z;x++)
#define For_(x,y,z) for(int x = y;x >= z;x--)
#define mkp make_pair
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;
#define int long long
const int mod = 1e9+7;
//const int mod = 998244353;
mt19937 myrand(time(0));
const int inf = 0x3f3f3f3f,N = 3e5+5,M = 1e6+5,K = 3000+5;
const long long linf = 0x3f3f3f3f3f3f3f3f;
int n;
int a[N],vis[N];
void solve(){
	cin>>n;
	For(i,1,n)cin>>a[i];
	int j = 3;
	int cnt=0;
	int flag=1;
	For(i,1,n-1) if(a[i]!=a[i+1]) flag=0;
	if(flag) {cout<<-1<<endl;return ;}
	int ans= 1e9;
	For(i,2,n-1){
		if(a[i+1]==a[i-1] && a[i+1] != a[i]){
			int x=0,y=0;
			for(int j = i+1;j <= n;j++){
				if(a[j]==a[i+1]) x++;
				else break;
			}for(int j = i-1;j >= 1;j--){
				if(a[j]==a[i-1]) y++;
				else break;
			}
			ans = min(ans,min(x,y));
			flag=0;
		}
	}	
if(flag) cout<<-1<<endl;
	else cout<<ans<<endl;
		
}
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T=1;
	cin >> T;
	For(_,1,T) solve();
	return 0;
}
```

---

