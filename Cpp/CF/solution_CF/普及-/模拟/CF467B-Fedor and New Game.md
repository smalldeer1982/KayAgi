# Fedor and New Game

## 题目描述

After you had helped George and Alex to move in the dorm, they went to help their friend Fedor play a new computer game «Call of Soldiers 3».

The game has $ (m+1) $ players and $ n $ types of soldiers in total. Players «Call of Soldiers 3» are numbered form $ 1 $ to $ (m+1) $ . Types of soldiers are numbered from $ 0 $ to $ n-1 $ . Each player has an army. Army of the $ i $ -th player can be described by non-negative integer $ x_{i} $ . Consider binary representation of $ x_{i} $ : if the $ j $ -th bit of number $ x_{i} $ equal to one, then the army of the $ i $ -th player has soldiers of the $ j $ -th type.

Fedor is the $ (m+1) $ -th player of the game. He assume that two players can become friends if their armies differ in at most $ k $ types of soldiers (in other words, binary representations of the corresponding numbers differ in at most $ k $ bits). Help Fedor and count how many players can become his friends.

## 样例 #1

### 输入

```
7 3 1
8
5
111
17
```

### 输出

```
0
```

## 样例 #2

### 输入

```
3 3 3
1
2
3
4
```

### 输出

```
3
```

# 题解

## 作者：Lucky_Cloud (赞：2)

## 前言

[更好的阅读体验](https://www.cnblogs.com/luckycloud/p/17831385.html)。

[传送门](https://www.luogu.com.cn/problem/CF467B)。

本题思维难度：橙。

本题代码难度：橙或红。

综合难度：橙。

## 题意

根据题目，若两人一人有 $j$，一人没 $j$，则异或后，第 $j$ 位为 $1$。

那么，题目就可以转化为：已知有 $m + 1$ 个数，求出满足 $a_i$ 异或 $a_{m + 1}$ 结果的 $1$ 的个数小于等于 $k$ 这样的 $i$ 的个数。其中 $1 \le i < m + 1$。

## 分析

题意转化的差不多了。简单模拟即可。

我们并不需要使用 `std::bitset`。

这里，我们引入一个函数 `__builtin_popcount()`，可以计算一个**整数**二进制下有多少个 $1$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
int n, m, k, a[N], ans;

int main() {
	cin >> n >> m >> k;
	m++;
	for (int i = 1; i <= m; i++) cin >> a[i];
	for (int i = 1; i < m; i++) 
		if (__builtin_popcount(a[i] ^ a[m]) <= k)
			ans++;
	cout << ans;
	return 0;
}
```


---

## 作者：lianchanghua (赞：1)

感谢 @[I_like_magic_200911](https://www.luogu.com.cn/user/778235) 帮忙修改 Markdown 和 $\LaTeX$。

#### 题目大意：

由 $m$ 个其他玩家，每个玩家象征着一个二进制编码，你也是一个二进制编码，如果编码种类的差异小于 $k$，那么你就可以交到一个朋友。问：你可以交多少个朋友？

#### 解法：

这道题，我们可以用短除法先将 $a_i$ 的二进制给做出来，再拿来与 Fedor 每位进行异或，然后比较相同位，不同数的个数，如果没有超出我们的 $k$ 的，$ans$ 就加 $1$，最后输出 $ans$ 即可。

最核心的部分便是短除法了，不停除 $2$，将余数与 Fedor 的同位进行比较即可。

代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k;
int ans,a[100010],t,s;
void bs(int d){//二进制转换
	int b=0;
	t=s;
	while(t!=0||d!=0){
		b+=((t%2)^(d%2));
		t/=2,d/=2;
	//	cout<<b<<"\n";
	}
	if(b<=k)	ans++;//符合要求，ans++ 
	return;
}
signed main(){
	ios::sync_with_stdio(false);
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)	cin>>a[i];
	cin>>s;
	for(int i=1;i<=m;i++)	bs(a[i]);//判断每一个 
	cout<<ans;
	return 0;
}

```

---

## 作者：bigclever (赞：0)

## 思路：
因为 $m \le 1000$，所以我们可以暴力判断第 $i$ 位玩家的军队和 Fedor 的军队有几种类型的士兵不同（也就是 $x_i$ 和 $x_{m+1}$ 在二进制下有几位不同）。若不同位数 $\le k$，答案 $+1$。

该算法时间复杂度为 $O(m \log \max^{m+1}_{i=1}x_i) \approx O(mn)$。
## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005];
int cal(int x,int y){//计算x和y在二进制下有几位不同
	int cnt=0;
    //注意当x和y均变为0时才退出循环
	for(;x||y;x>>=1,y>>=1)cnt+=(x&1!=y&1);
	return cnt;
}
int main(){
	int n,m,k,ans=0;
	cin>>n>>m>>k;
	for(int i=1;i<=m+1;i++)cin>>a[i];
	for(int i=1;i<=m;i++)ans+=(cal(a[i],a[m+1])<=k);
	cout<<ans;
	return 0;
}
```

---

## 作者：DERMING (赞：0)

# 题意
给你一个标准数和 $n$ 个待计算数，设标准数与一个待计算数的二进制位有 $m$ 位不同，求有多少个 $m$ 满足 $m<k$（有多少个数与标准数二进制不同位数小于 $k$）。

# 做法
方法1：先将标准数分解二进制，存入数组中，再把待计算数逐个分解计数

方法2：每次都把标准数与一个待计算数同时分解，再对每一二进制位异或一下，计数即可

[AC Link](https://codeforces.com/contest/467/submission/224544640)（因为 RMJ 炸了所以没有你谷记录）

Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010];
int n,m,k;
int divide(int x,int y)
{
	int cnt=0;
	while(x!=0||y!=0)//这里解释一下为什么不是&&：当一者为0时cnt可能不超过k，
                     //因此需要把剩下的二进制位全统计一遍，保证cnt>k
	{
		cnt+=((x%2)^(y%2));//两者相同就为0，不同就为1，加进cnt就可以
//		if(x%2!=y%2)也可以这样写
//		{
//			cnt++;
//		}
		x/=2;
		y/=2;
	}
	if(cnt<=k)//直接判断是否ans++
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int main()
{
	cin>>n>>m>>k;
	for(int i=1;i<=m+1;i++)
	{
		cin>>a[i];
	}
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		ans+=divide(a[i],a[m+1]);//每个数都判断一次
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：Patricky (赞：0)

### 题意

给定 
$m + 1 \; (m \le 10^3)$
个二进制位数不超过 
$n \; (n \le 20)$
的数，问最后给定那个数 $x$ 与前 $m$ 个数有 **至多 $k$ 位不同的数的数量**。

## 解答

有多少位不同，即 **异或** 运算后 $1$ 的数量。

使用 `std::bitset` 可以轻松完成，实际上直接模拟也是一样的效果。

tips: 求二进制下多少个 $1$，可以使用 `std::bitset<xx>(x).count()` 或 `__builtin_popcount(x)` 
  + 其中 $x$ 指代要求的数字，后者类型为 `unsigned int`
    + 更多位数也可以使用 `__builtin_popcountll(uint64_t)`。
  + 而前者只需规定位数 $\operatorname{xx}$，且可使用一个二进制 `std::string` 来构造，十分方便。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0), ios::sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  vector<int> diff(m);
  for (int i = 0; i < m; ++i) {
    cin >> diff[i];
  }

  int x;
  cin >> x;
  bitset<20> X(x);

  int ans = 0;
  for (int i = 0; i < m; ++i) {
    ans += (int)(X ^ bitset<20>(diff[i])).count() <= k;
  }

  cout << ans << "\n";

  return 0 ^ 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF467B)

这题主要是位运算。

把 Fedor 和另一个玩家的兵团异或得到一个数，设为 $r$。

$r$ 里面的 $1$ 就是指这种兵团只有一个人有。

所以我们统计 $r$ 中 $1$ 的个数，如果不大于 $k$ 说明他们可以成为朋友。

最后搞个 $cnt$ 统计 Fedor 的朋友个数。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, k, a[10001], f, ans;
int main(){
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) cin >> a[i];
	cin >> f;
	for (int i = 1; i <= m; i++){
		int r = f ^ a[i], cnt = 0;
		while (r){
			cnt += r % 2;
			if (cnt > k) break;
			r >>= 1;
		}
		if (cnt <= k) ans++;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：guozhe6241 (赞：0)

# 题目传送门

[CF467B](https://www.luogu.com.cn/problem/CF467B)

# 题外

建议橙题。

# 思路

题目说如果二进制最多有 $k$ 位不同就可以成为朋友，那么这题的思路就是暴力。

枚举第 $i$ 位士兵与 Fedor 异或为 $1$。如果位数 $\le k$，答案加 $1$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=5e3+5;
int n,m,k,s;
int a[maxn];
int ans;
int cnt(int x,int t){
	int b=0;//统计异或为1的个数 
	while(t!=0||x!=0){//转换为二进制 
		b+=((t%2)^(x%2));
		t/=2;
		x/=2;
	}
	if(b<=k){
        return 1;
    }
    return 0;
}
signed main(){
	cin>>n>>m>>k;//输入 
	for(int i=1;i<=m;i++){
		cin>>a[i];
	}
	cin>>s;
	for(int i=1;i<=m;i++){//每个点跑一遍 
		ans+=cnt(a[i],s);
	}
	cout<<ans<<endl;
    return 0;
}

```

[AC记录](https://www.luogu.com.cn/record/137248124)

---

