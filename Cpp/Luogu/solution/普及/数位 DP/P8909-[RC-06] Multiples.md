# [RC-06] Multiples

## 题目描述

给出 $n$，以及一个长度为 $n$ 的数组 $a$，$a_1\sim a_n$ 都是正整数，且 $a_i$ 在 $[1,10^9]$ 均匀随机生成。

对每个 $0\le k\le n$ 计算 $[1,m]$ 中有几个正整数 $x$ 恰好是 $k$ 个 $a_i$ 的倍数（也就是恰好存在 $k$ 个 $1\le i\le n$，$a_i\mid x$）。

## 说明/提示

本题没有部分分，只有 AC 才能得分。

所有数据均满足：$1\le n\le 2500$，$1\le m\le 10^9$，$1\le a_i\le 10^9$，且 $a_i$ 在 $[1,10^9]$ 中均匀随机生成。

**本题有 $6$ 组数据满足 $n=2500$，$2$ 组数据满足 $n\le 10$，共 $8$ 组数据。**

**所有数据都是如下方式生成：运行以下伪代码恰好一次生成，将其输出作为你的输入。**

```
function rnd(int l,int r):

return [l,r] 之内的随机整数

function main():

输入本组数据的 n,m
输出 n,m
输出 n 个正整数，都是 rnd(1,10^9) 的返回值
```

如果你不理解上面的生成方式，也可以阅读对应的 C++ 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	freopen("in.txt","w",stdout);
	int n,m;
	cin>>n>>m;
	cout<<n<<' '<<m<<'\n';
	mt19937_64 rng(time(0));
	const int M=1e9;
	for(int i=1;i<=n;i++)cout<<rng()%M+1<<' ';
}
```

样例不满足 $a_i$ 在 $[1,10^9]$ 均匀随机生成，因此样例不是合法的输入数据。测试数据中不包含样例。

## 样例 #1

### 输入

```
5 1000000
1 2 3 4 5```

### 输出

```
0 266666 333335 266665 116668 16666```

# 题解

## 作者：yeshubo_qwq (赞：2)

## Solution

首先考虑最简单的暴力。

对于每个数 $x$，枚举它的倍数 $j$，并给 $a_j$ 增加 $1$。

统计 $a_j>0$ 的数中满足 $a_j=k$ 的数量，减一减就是 $a_j=0$ 的数量。

在随机数据下跑的飞快。

注意到数据的确是随机的，交一发，AC 了！

## Code

```cpp
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
//#define int long long
using namespace std;
using namespace __gnu_pbds;
int n,m,i,x,j,ans[2505];
gp_hash_table <int,int> a;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for (i=1;i<=n;i++){
		cin>>x;
		for (j=x;j<=m;j+=x) a[j]++;
	}
	int tot=m;
	for (gp_hash_table <int,int>::iterator it=a.begin();it!=a.end();it++)
		ans[it->second]++,tot--;
	cout<<tot<<' ';
	for (i=1;i<=n;i++) cout<<ans[i]<<' ';
	return 0;
}
```


---

## 作者：Convergent_Series (赞：1)

考虑暴力枚举 ``a[i]`` 的倍数，用桶记录每个数被枚举的次数。

于是，这是我第一次的代码（错误）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[3000],t[3000];
short cnt[1000000010];
int main(){
	cin>>n>>m;
	int i,j,s;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n;i++){
		for(j=1;j*a[i]<=m;j++) cnt[a[i]*j]++;
	}
	for(i=1;i<=m;i++) t[cnt[i]]++;
	for(i=0;i<=n;i++) cout<<t[i]<<" ";
	return 0;
}
```
很明显爆空间了，``cnt`` 数组太大，考虑改进。

由于数据随机生成，所以满足 ``cnt[i]==0`` 的 $i$ 肯定很多。如果用 ``map`` 代替桶，则为 $0$ 的数据不会被记录，虽然可能容易被卡（样例超时），但完全可以通过随机数据。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[3000],t[3000];
map<int,int>cnt;
int main(){
	cin>>n>>m;
	int i,j,s;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n;i++){
		for(j=1;j*a[i]<=m;j++) cnt[a[i]*j]++;
	}
	cout<<m-cnt.size();
	for(map<int,int>::iterator ii=cnt.begin();ii!=cnt.end();ii++) t[ii->second]++;
    //用迭代器遍历
	for(i=1;i<=n;i++) cout<<" "<<t[i];
	return 0;
}
```

---

## 作者：zhyou (赞：0)

## 思路
这道题，我们很容易想到开一个桶统计 $[1, m]$ 中每个数是序列中几个数的倍数。但是如果直接用数组，那很明显会 MLE，所以我们使用 STL 中的 map，动态管理空间，避免超空间的问题。理论上这么做会超时，但是代码在随机数据下跑得飞快，所以此方法可行。

## C ++ 代码
```
#include <bits/stdc++.h>

using namespace std;

const int N = 2505;
map<int, int> mp;
int ans[N], n, m;

int main(){
	scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= n; i ++ ) {
		int a;
		scanf("%d", &a);
		for (int j = a; j <= m; j += a) mp[j] ++; //统计
	}
	
	int tot = m; //用来统计 [1, m] 中有几个数不是数组中任何数的倍数
	for (pair<int, int> it : mp){ //遍历map
		int now = it.second;
		ans[now] ++,tot --; 
	}
	
	printf("%d ", tot); 
	for (int i = 1; i <= n; i ++ ) printf("%d ", ans[i]); //输出
	
	return 0;
}
```

---

## 作者：yinpeichu2021 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P8909)

# 思路

考虑暴力，对于每一个 $a_i$ 将它的倍数 $j$ 并让 $s_j$ 加上一，然后再统计使得 $s_j=k(1\le k\le n)$ 的 $j$ 的个数。当 $k=0$ 时，答案为

$$m-\sum_{i=1}^n s_i$$

注意到题目中说的数据均为随机生成，此方法可行。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[2505],ans[2505];
map<int,int>mp;
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        for(int j=a[i];j<=m;j+=a[i])mp[j]++;
    }
    for(auto it:mp)ans[it.second]++;
    int s=m;
    for(int i=1;i<=n;i++)s-=ans[i];
    cout<<s;
    for(int i=1;i<=n;i++)cout<<' '<<ans[i];

    return 0;
}
```

---

## 作者：ryf_loser (赞：0)

此题正解是暴力。

如果直接开数组暴力，很明显会超空间，我们可以考虑用 STL 中的 map，动态管理空间。

枚举每个给出的 $a$ 的 $j$ 倍，并且 `a_{j}++`。

这样经过预处理后，我们可以统计 $a_{j}=x$，的数量，用 $m$ 减去数量即可得到答案数量，并输出。

这样的思路在样例中会被卡，建议使用洛谷在线 IDE 编译运行，但是在随机数据下跑的很快，不会被卡。

AC CODE

```cpp
#include<cstdio>
#include<map>
using namespace std;
int n,m,a,ans[2502];
map<int,int>t;
int main(){
	scanf ("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf ("%d",&a);
		for(int j=a;j<=m;j+=a)
			t[j]++;//统计
	}
	for(auto i=t.begin();i!=t.end();i++)ans[i->second]++,m--;//运用迭代器处理
	printf("%d ",m);
	for(int i=1;i<=n;i++)printf ("%d ",ans[i]);//打印答案
	return 0;
}
```


---

## 作者：Nuyoah_awa (赞：0)

楼上的大佬们已经介绍了暴力，$\operatorname{map}$ 等解法，我就补充一下~~非正解~~的链表和 $\operatorname{map}$。
## 题目分析
1. 首先看到这道题先想到暴力，枚举每个 $a_i$ 的 $k$ 倍，开个桶子计算出现几次。但是发现数太大了，桶开不下($1 \leq m \leq 10^9$)。

2. 先写个桶会发现中间有很多没有参与的数浪费很多空间，于是就可以把桶换成链表来模拟。

说白了就是将 $a_i$ 的 $k$ 倍这个数和出现次数压缩成一个结构体数组（链表）进行遍历。

但是要注意到链表中不需要删除元素，且只会在末尾添加，所以又变成了一个按下标遍历的链表。

### code
```cpp
struct list{
	int val, id;		//枚举出的a[i]的k倍的数， 出现过的次数 
}p[200000];			//这样就省下了中间很多根本不会用到的数
int n, m, a[2510], ans[2510], ln;
bool in[1000000010];
int main()
{
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	for(int i = 1;i <= n;i++)
	{
		for(int j = a[i];j <= m;j += a[i])
		{
			if(!in[j])
			{
				in[j] = true;
				ln++;
				p[ln].val = j, p[ln].id = 1;
			}
			else
			{
				for(int k = 1;k <= ln;k++)
				{
					if(p[k].val == j)
					{
						p[k].id++;
						break;
					}
				}
			}
		}
	}
	cout << m - ln;
	for(int i = 1;i <= ln;i++)
        ans[p[i].id]++;
	for(int i = 1;i <= n;i++)
		cout << " " << ans[i];
	return 0;
}
```
但是会发现总有一个点 **MLE**。

3. 用 $\operatorname{map}$ 代替桶。
这里讲一个关于 $\operatorname{map}$ 的知识点，就是如何快速遍历 $\operatorname{map}$，这里用到了 $\operatorname{map}$ 函数库的
$\operatorname{begin()}$——返回指向 $\operatorname{map}$ 头部的迭代器，
$\operatorname{end()}$——返回指向 $\operatorname{map}$ 尾部的迭代器 等函数。
代码如下：
```cpp
map<int,int>::iterator i = mp.begin();i != mp.end();i++
```

## 最后附上本蒟蒻的代码
```cpp
#include <iostream>
#include <cstdio>
#include <map>
using namespace std;
map <int, int> mp;
int n, m, a[3000], ans[3000];
int main()
{
	cin >> n >> m;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	for(int i = 1;i <= n;i++)
		for(int j = a[i];j <= m;j += a[i])
			mp[j]++;
	cout << m - mp.size();
	for(map<int,int>::iterator i = mp.begin();i != mp.end();i++)
		ans[i->second]++;
	for(int i = 1;i <= n;i++)
		cout << " " << ans[i];
	return 0;
}
```
### 附件
- [$\operatorname{map}$ 详解](https://blog.csdn.net/m0_67403076/article/details/124503868)

---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P8909)

**思路：**

这道题有一句话非常关键：$a_i$ 在 $[1,10^9]$ 均匀随机生成。

那么只需要按题目意思把每一个 $a_i$ 的倍数加一，开一个 $ans$ 数组统计结果并输出。

对于 $ans_0$，先把值定为 $m$。最后统计时，每一次 $ans_i(i>0)$ 加一，$ans_0$ 就减一。最后 $ans_0$ 就等于 $m-ans_1-ans_2-...-ans_n$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,ans[2510];
map<int,int>mp;
int main(){
	cin>>n>>m;
	ans[0]=m;
	for(int i=1;i<=n;i++){
		cin>>a;
		for(int j=a;j<=m;j+=a)
			mp[j]++;
	}
	for(auto i=mp.begin();i!=mp.end();i++){
		ans[i->second]++;
		ans[0]--;
	}
	for(int i=0;i<=n;i++)
		cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：BlanketRice (赞：0)

### 题目大意

给定 $ n $ 个数，令 $ 0 \le k \le n $ ，若 $ k = i $ 时，求恰好是 $ n $ 个数中 $ k $ 个数的倍数的数有几个。

### 思路

由于是随机数据，暴力枚举即可。我们设一个数组 $ m $，令 $ m_i $ 表示数 $ i $ 同时为几个数的倍数。$ ans_i $ 表示同时为 $ i $ 个数的倍数的数有几个。

我们分别枚举 $ a_i $ 的所有倍数 $ j $，枚举时 `++m[j]`，不要忘了在这之前先令 `--ans[m[j]]` 然后修改完之后再 `++ ans[m[j]]`。也就是说发现有同时是这个数的倍数，就更新一下。其实很简单。

### 代码
```cpp
# include <bits/stdc++.h>

# define gt getchar

# define pc putchar

# define rep(i, a, b) for (register int i = (a); i <= (b); ++ i)

# define per(i, a, b) for (register int i = (a); i >= (b); -- i)

# define File(x, y) freopen (x, "r", stdin), freopen (y, "w", stdout)

# define int LL

using namespace std;

typedef long long LL;

typedef unsigned long long ULL;

const int N = 10000005;

const int M = 5005;

const int INF = 2147483647;

namespace IO {

    inline void read (int &x) {

        int ret = 0, sgn = 0, ch = gt ();

        while (! isdigit (ch)) sgn |= ch == '-', ch = gt ();

        while (isdigit (ch)) ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gt ();

        x = (sgn ? -ret : ret);

    }

    inline void print (int x) {

        if (x < 0) pc ('-'), x = -x;

        int ret = 0, ch[40];

        do { ch[++ ret] = x % 10 + 48, x /= 10; } while (x);

        while (ret) pc (ch[ret]), -- ret;

    }

    inline void printsp (int x) {

        print (x);

        pc (' ');

    }

    inline void println (int x) {
        
        print (x);

        pc ('\n');

    }

    inline void puts (string s) {

        int len = s.length ();

        rep (i, 0, len - 1) pc (s[i]);

        pc ('\n');

    }

} ;

using namespace IO;

inline void solve () ;

signed main () {

    int T = 1;

    // read (T);

    while (T --) {

        solve ();

    }

    return 0;

}

int n, m, a[N];

int ma[N], ans[N];

inline void solve () {

    read (n), read (m);

    rep (i, 1, n) read (a[i]);

    ans[0] = m;

    rep (i, 1, n) {

        for (register int j = a[i]; j <= m; j += a[i]) {

            -- ans[ma[j]];

            ++ ma[j];

            ++ ans[ma[j]];

        }

    }

    rep (i, 0, n) printsp (ans[i]);

    return ;

}
```

---

