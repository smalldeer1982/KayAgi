# [SEERC 2020] Mistake

## 题目描述

你有 $k$ 个机器，每个机器都**未按序**存储了 $1 \sim n$ 共 $n$ 个数，当你启动某个机器时，该机器会将其存储的数最前面的数打印出来，然后删除它。

但是很幸运，你知道 $m$ 对 $(a_i,b_i)$，表示每个存储的 $a_i$ 都在 $b_i$ 前面。

你还知道你依次启动的机器输出了哪些，请对于每个打印的数，确定一种方案表示它是由哪个机器启动得来，保证每个数出现的次数 $=n$。

存在多种可行解，输出任何都可以得分。

## 样例 #1

### 输入

```
3 3 2
1 2
1 3
1 1 2 3 3 2 1 2 3```

### 输出

```
1 2 2 1 2 1 3 3 3```

# 题解

## 作者：_hxh (赞：2)

## 分析

题意还是非常清楚的，为了帮助理解，我们把样例中依次启动的机器输出的序列和合法的启动方案放在一起看。（${\color{red} 第一台机器}，{\color{green} 第二台机器}，{\color{blue} 第三台机器}$）

$${\color{red} 1} {\color{green} 1} {\color{green} 2} {\color{red} 3} {\color{green} 3} {\color{red} 2} {\color{blue} 1} {\color{blue} 2} {\color{blue} 3}$$

因为每个数都出现了 $k$ 次，所以正好于 $k$ 台机器匹配。注意到题目中说“输出**一种**合法的启动方案”就可以，所以我们可以调整一下：

$${\color{red} 1} {\color{green} 1} {\color{red} 2} {\color{red} 3} {\color{green} 3} {\color{green} 2} {\color{blue} 1} {\color{blue} 2} {\color{blue} 3}$$
 
我们可以让该数字第 $j$ 次出现被第 $j$ 台机器打印，这样可以直接用一个数组记录。设 $pos_{i,j}$ 为数字 $i$ 第 $j$ 次出现的位置，那么 $pos_{1,1} < pos_{1,2} < \dots < pos_{1,k},pos_{2,1} < pos_{2,2} < \dots < pos_{2,k}\dots$ 一定成立。而输入的依次启动的机器输出的序列一定是合法的，这样 $pos_{1,j},pos_{2,j},\dots,pos_{n,j}$ 位置上的数字就可以匹配到第 $j$ 台机器上啦。
 
为什么 $m$ 对 $(a_i,b_i)$ 没有用呢？因为依次启动的机器输出的序列一定是合法的，即一定满足每个存储的 $a_i$ 都在 $b_i$ 前面，不需要开数组进行存储。
 
## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5; 
int n,k,m,a,b,x,nk[N];
int main()
{
	cin >> n >> k >> m;
	for (int i = 1;i <= m;i++)
		cin >> a >> b;
	for (long long i = 1;i <= n * k;i++)
	{
		cin >> x;
		cout << ++nk[x] << " ";
	}
	return 0;
}
```

---

## 作者：__HappY__ (赞：2)

###  题意

有 $k$ 个机器，每个机器内都有 $ 1 ∼ n $ 共 $n$ 个数，进行 $n \times k$ 次操作，按要求输出。

###  思路

其实 $a_i$ 和 $b_i$，没什么用，因为保证有解且每个机器内的数都相同。我的思路是开一个桶记录每次输入这个数的次数，并输出。

###  讲解

为什么这个思路正确？当我们输入一个数后，再输入这个数，就要换另一个机器，为了方便，第一次输入就是第的一台机器，再一次输入就是第二台机器，第 $n$ 次输入就是第 $n$ 台机器。

###  代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, k, m;
const int N = 5e5 + 911;
int a[N], ans[N];
int main() {
	cin >> n >> k >> m;
	for(int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
	}
	int j = 1;
	for(int i = 1; i <= (n * k); i++) {
		int num;
		cin >> num;
		a[num]++;
		ans[j] = a[num];
		j++;
	}
	for(int i = 1; i <= (n * k); i++) {
		cout << ans[i] << ' ';
	}
	return 0;
}

``````

---

## 作者：TheForgotten (赞：1)

# P10748 [SEERC2020] Mistake 题解

[题目传送门](https://www.luogu.com.cn/problem/P10748)

## 题目大意
有 $k$ 个机器，每个机器都未按序存储了 $1 \sim n$ 共 $n$ 个数，知道 $m$ 对 $(a_i,b_i)$，表示每个存储的 $a_i$ 都在 $b_i$ 前面，还有依次启动的机器输出了哪些。对于每个打印的数，确定一种方案表示它是由哪个机器启动得来。

## 思路
输出的数在之前启动的机器中，所以这个数下一次出现肯定在别的未启动机器里。记录一下输入的数，如果这个数出现了 $i$ 次，那么就让它位于第 $i$ 个机器中。对于给出的 $m$，既然保证有可行解，就不用再想每个数在机器中的顺序了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,m,a,b,x;
int o[500005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(),cout.tie();
	cin>>n>>k>>m;
	for(int i=0;i<m;i++){
		cin>>a>>b;
	}
	for(int i=0;i<n*k;i++){
		cin>>x;
		cout<<++o[x]<<" ";
	}
	return 0;
}

```

---

## 作者：Archy_ (赞：1)

## 题目描述

你有 $k$ 个机器，每个机器都**未按序**存储了 $1 \sim n$ 共 $n$ 个数，当你启动某个机器时，该机器会将其存储的数最前面的数打印出来，然后删除它。

你还知道你依次启动的机器输出了哪些，请对于每个打印的数，确定一种方案表示它是由哪个机器启动得来。

**重点两句话：**

1. 保证每个数出现的次数 $=n$。

2. 存在多种可行解，输出任何都可以得分。

## 题目思路

看到每个数出现的次数 $=n$，我们想到，依次启动的机器输出了 $x$，那么 $x$ 下一次出现就可以是下一个机器输出的，用数组 $f$ 记录出现次数，而出现次数恰好是此时对应机器的编号，直接输出。

这里有个疑问，本题的 $m$ 对数具体应用在哪里？

## CODE
~~你没看错，一道黄题就这么短。~~
```cpp
#include <iostream>
using namespace std;
int f[500005], m, n, k;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k >> m;
	for (int i = 1; i <= m; i ++) {
		int x, y; cin>>x>>y;
	}
	for(int i = 1; i <= n * k; i ++) {
		int x; cin>>x;
		f[x] ++;
		cout<<f[x]<<" ";
	}
	return 0;
}
```

---

## 作者：Breath_of_the_Wild (赞：0)

其实最简单的一种方案就是，在这 $n\times k$ 个数中，对于同一个数，如果没有出现过，就用机器 $1$（输出 $1$）。如果出现过一次，即用过一次，就用机器 $2$（输出 $2$），以此类推。

因此我们可以用一个记录每个数次数的数组，在读入 $n\times k$ 个数的时候，对应的数组位置计数器先加 $1$，再输出当前的数。

所以 $a_i,b_i,m$ 一点用没有。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,k,cnt[N],x;
int main(){
	cin>>n>>k>>m;
	while(m--) cin>>x>>x;
	for(int i=1;i<=n*k;i++){
		cin>>x;
		cout<<++cnt[x]<<" ";
	}
	return 0;
}

---

## 作者：__Sky__Dream__ (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/P10748)

## 题目大意
给定 $n,k,m$，给出 $m$ 组依赖关系，要求将给出的 $n \times k$ 个数分为 $k$ 组，使每组内的先后顺序都满足前文依赖关系下的拓扑序。

## 解题思路
~~真不知道本题中的依赖方案有什么用……~~

遍历 $n \times k$ 个数，对于遇到的每一个数，如果这个数此前没有出现过，那就把它放到第一组，如果出现过，那就放到第出现的次数 $+1$ 组里。

有一个简单的证明：对于每一个数，如果它所依赖的数出现过，那么它依赖的数同样依次被放进了 $1,2,...,k$ 中，所以这样的方法可以必定满足依赖方法。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5;
set<int>a[maxn+10];
void dfs()
{
	int n,k,m;
	cin>>n>>k>>m;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
	}
	for(int i=1;i<=n*k;i++)
	{
		int t;
		cin>>t;
		if(a[t].empty())
		{
			cout<<1<< " ";
			a[t].insert(1);
		}
		else
		{
			int tt=*prev(a[t].end())+1;
			cout<<tt<< " ";
			a[t].insert(tt);
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	dfs();
	return 0;
}
```

拜拜！

---

## 作者：xiangxiyu (赞：0)

## 思路

对于每个机器，它存储的数的顺序并不重要，无论 $a_i$ 是否大于 $b_i$，我们肯定能找到一种顺序满足条件，同时题目只要输出一种情况。而一个机器不能重复存储同一个数，所以只要每重复出现一个数，就多一个机器就可以了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+20;
int a[N],ans[N];
signed main(){
	int n,m,k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		int x,y;
		cin>>x>>y; 
	}
	for(int i=1;i<=n*m;i++){
		int x;
		cin>>x;
		ans[x]++;
		cout<<ans[x]<<" ";
	}
}
```

---

## 作者：xiezheyuan (赞：0)

## 思路

不知道 $a_i,b_i$ 的限制用意何在。

我们发现，每一台机器都存储了 $1\sim n$ 这些数，因此，假如遇到了一个数，这个数已经出现了，那么只能给一个新的机器中。具体来说，我们就放到出现次数对应的机器中。

为什么这样是对的呢，因为假如我们用这种方法遇到了一个 $x$，使得放入我们的策略需要放的位置时，违反了一条限制。则我们只能将其放到一个新的机器中，而放到一个新的机器中后，被我们忽略的机器最后也必定会放的，还是会违反限制。因此我们就感性地证明了这个结论。

时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;

const int N = 5e5 + 5;
int n, k, m, a[N];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> n >> k >> m;
    for(int i=1,a,b;i<=m;i++) cin >> a >> b;
    for(int i=1;i<=(n * k);i++){
        int v; cin >> v;
        cout << (++a[v]) << ' ';
    }
    return 0;
}

// Written by xiezheyuan
```

---

