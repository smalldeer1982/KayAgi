# Removals Game

## 题目描述

Alice 得到了一个排列 $a_1, a_2, \ldots, a_n$，它是 $[1,2,\ldots,n]$ 的一个排列，而 Bob 也得到了另一个排列 $b_1, b_2, \ldots, b_n$，同样是 $[1,2,\ldots,n]$ 的一个排列。他们打算用这两个数组来进行一个游戏。

每轮游戏中，以下事件按顺序发生：

- Alice 选择她数组中的第一个或最后一个元素并将其从数组中移除；
- Bob 选择他数组中的第一个或最后一个元素并将其从数组中移除。

游戏持续进行 $n-1$ 轮，之后两个数组都将只剩下一个元素：$a$ 数组中的 $x$ 和 $b$ 数组中的 $y$。

如果 $x=y$，Bob 获胜；否则，Alice 获胜。假设两个玩家都采取最优策略，请找出哪个玩家将获胜。

## 说明/提示

在第一个测试用例中，Bob 可以通过删除与 Alice 相同的元素来赢得游戏。

在第二个测试用例中，Alice 可以在第一轮删除 $3$，然后在第二轮删除与 Bob 第一轮删除的不同元素来赢得游戏。

## 样例 #1

### 输入

```
2
2
1 2
1 2
3
1 2 3
2 3 1```

### 输出

```
Bob
Alice```

# 题解

## 作者：Distorted_Fate_ (赞：2)

## 题意简述

爱丽丝和鲍勃正在进行一个游戏：他们每人都有一个数列，他们每次可以进行如下操作：

- 删除当前数列的第一个元素；

- 删除当前数列的最后一个元素。

两人都使用最优策略。如果最终他们剩下的一个数相同则鲍勃赢，反之爱丽丝赢。

## 分析

数据范围不大，多测，细节也不多，所以不用多余的算法。

不难看出爱丽丝的赢面比较大，所以我们优先考虑鲍勃赢的情况。

首先我们思考：如果两人数组中的每一个元素都能对应上，那鲍勃肯定是赢的。但是这种情况只适用于正序对应（完全相同）和逆序对应（完全相反），如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/u5hm2nc6.png)

代码很好写，没有坑点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int t,n;
int a[N],b[N];
bool check1(){//正序对应
	for(int i=1;i<=n;i++){
		if(a[i]!=b[i])return 0;
	}
	return 1;
}
bool check2(){//逆序
	for(int i=1;i<=n;i++){
		if(a[i]!=b[n-i+1])return 0;
	}
	return 1;
}
signed main(){
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b[i];
		}
		if(check1()||check2()){//能赢的两种情况
			cout<<"Bob\n";
		}
		else cout<<"Alice\n";
	}
	return 0;
}

//作者画工不好，见谅
```

---

## 作者：lzh9 (赞：2)

## 思路

考虑当前 Alice 删除的元素 Bob 无法删除，这时 Bob 删除的元素 Alice 一定没有删除，所以 Alice 只需要留下 Bob  已经删除掉的元素就可以使她获胜。如果 Bob 想要获胜就需要不出现上述情况。

为了下文便于表述，把数列 $a$ 表示成以下形式：

$$a_{s_1}a_{s_2}\dots a_{t_2} a_{t_1}$$

把目前的局势 $(a,b)$ 分为三种情况：

1. $a_{s_1}=b_{s_1}$ 且 $a_{t_1}=b_{t_1}$。
2. $a_{s_1}=b_{t_1}$ 且 $a_{t_1}=b_{s_1}$。
3. 不为前两种情况。

根据上文，第三种情况一定是 Alice 赢。考虑第一种情况，如果 Bob 想要获胜，则删除一个后的情况也要 Bob 获胜（不可能是第三种情况）。不妨设删除 $s_1$ 位置，因为 $t_1$ 位置相同，则删除后只可能是第一种情况，则 $a_{s_2}=t_{s_2}$。这样推下去，每个位置都相同，则如果一开始是第一种情况，则 $a=b$ 时 Bob 获胜。第二种情况同理，推到后发现 $b$ 是 $a$ 倒过来，这样也是 Bob 获胜。所以，Bob 获胜的情况只有这两种，其他都是 Alice 获胜。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[1000000+5],b[1000000+5];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long t;
	cin>>t;
	while(t--)
	{
		cin>>n;
		bool flag1=1,flag2=1;
		for(long long i=1;i<=n;i++) cin>>a[i];
		for(long long i=1;i<=n;i++) cin>>b[i];
		for(long long i=1;i<=n;i++)
		{
			if(a[i]!=b[i]) flag1=0;
			if(a[i]!=b[n+1-i]) flag2=0;
		}
		if(flag1||flag2) cout<<"Bob\n";
		else cout<<"Alice\n";
	}
	return 0;
}
```

---

## 作者：QingDeng_Star (赞：0)

## 题目大意
Alice 和 Bob 有 $n$ 个数，每次他们要删掉这些数中第一个或最后一个数，最后每人都只剩下一个数。
如果两数一样，Bob 赢，否则 Alice 赢。如果两人都用最优策略，那么谁能赢？
## 思路
很明显 Bob 赢的可能性小，所以先考虑 Bob 赢的情况。
不难发现，如果两人的数列一样，那么 Bob 肯定能赢，或者是 Alice 的数列翻转过来和 Bob 的数列一样，那么 Bob 也能赢。

讲得这么清楚了，还要代码？

---

## 作者：cute_overmind (赞：0)

### 题目大意
在每一轮中：
- Alice 选择她数组中的第一个或最后一个元素并将其从数组中移除；
- Bob 选择他数组中的第一个或最后一个元素并将其从数组中移除。

游戏持续进行 $n-1$ 轮，之后两个数组都将只剩下一个元素：$a$ 数组中的 $x$ 和 $b$ 数组中的 $y$。

如果 $x=y$，Bob 获胜；否则，Alice 获胜。假设两个玩家都采取最优策略，请找出哪个玩家将获胜。

### 题目分析
考虑最优策略的分析。

我们发现，当 Bob 无法取到和 Alice 一样的数时，Bob是必定输的。所以我们要使 Bob 胜利，我们应该使 $A = B$ 或 $A$ 和 翻转的 $B$ 相等。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
bool flag;
int n , a[N] , b[N];
void solve(){
	cin >> n;
	for(int i = 1;i <= n;i++)
		cin >> a[i];
	for(int i = 1;i <= n;i++)
		cin >> b[i];
	for(int i = 1;i <= n;i++)
	{
		if(a[i] != b[i]) break;
		if(i == n)
		{
			cout << "Bob\n";
			flag = true;
			break;
		}
	}
	if(flag) continue;
	for(int i = 1;i <= n;i++)
	{
		if(a[i] != b[n - i + 1]) break;
		if(i == n)
		{
			cout << "Bob\n";
			flag = true;
			break;
		}
	}
	if(flag) continue;
	cout << "Alice" << endl;
}
int main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Magallan_forever (赞：0)

#### 简要说明题意：

有两个 $\{1,2,\dots,n\}$ 的序列，两人轮流删除各自序列头或尾的一个数，两人序列均剩一个数时，若两数相同则第二个人获胜，否则第一个人获胜。给出序列，求两人均最优操作时的胜者。

#### 题目分析

题解提到只要字符串不相同且不是互为逆序，` Alice` 必然获胜。下面进行简单的分析：

假设最后剩下的 $3$ 个数不相同，则 `Alice` 必然获胜。

假设存在序列 $a,b,c$ 和 $a,c,b$，则 `Alice` 只要先对 `Bob` 不可删除的 $c$ 动刀，再对 `Bob` 选择的数动刀，`Bob`必然不可能保证两数相同。

此外，对于存在不同且长度超过 $2$ 的序列（如 $a,b,c,d$ 和 $a,b,d,c$），`Alice` 只要尽可能删成前两种情况（如无脑删到只剩 $a,b,c$，为了最优 `Bob` 只能跟着删你删的）。

是个有一定思维难度的题目。

但是代码说不上复杂：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[300001],b[300001];
bool cnta[300001],cntb[300001];
int main(){
    int T,n,ai,aj,bi,bj;
    bool mark0,mark1;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<n;++i) scanf("%d",a+i);
        for(int i=0;i<n;++i) scanf("%d",b+i);
        mark0=true,mark1=true;
        for(int i=0;i<n;++i){
            if(a[i]^b[i]) mark0=false;
            if(a[i]^b[n-i-1]) mark1=false;
        }
        printf(mark0||mark1?"Bob\n":"Alice\n");
    }
    return 0;
}
```

---

## 作者：yangzimu0131 (赞：0)

# 题解
首先考虑 Bob 要赢的情况，只要 Bob 无法与取 Alice 相同的数，Bob 必输。因此要想让鲍勃获胜，要么是 $A=B$，要么是 $A=\textrm{reverse}(B)$。
# Code
```
#include<bits/stdc++.h>
using namespace std;
int a[300010],b[300010];
int main()
{
	int T,n;
	bool f;
	cin>>T;
	while(T--)
	{
		f=0;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		for(int i=1;i<=n;i++)
			cin>>b[i];
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=b[i])
				break;
			if(i==n)
			{
				cout<<"Bob"<<endl;
				f=1;
				break;
			}
		}
		if(f)
			continue;
		for(int i=1;i<=n;i++)
		{
			if(a[i]!=b[n-i+1])
				break;
			if(i==n)
			{
				cout<<"Bob"<<endl;
				f=1;
				break;
			}
		}
		if(f)
			continue;
		cout<<"Alice"<<endl;
	}
	return 0;
}
```

---

## 作者：RaymondOccam (赞：0)

### 题目传送门
[link](https://codeforces.com/problemset/problem/2002/B)

### 题意简述
Alice 有 $n$ 个数，Bob 有 $n$ 个数，每次他们只能删掉这些数中第一个或最后一个数，最后每人获得一个数。

如果两数相等，Bob 赢，否则 Alice 赢。请你判断谁能赢？（两人足够聪明）

### 思路
我们会发现 Bob 赢的几率比 Alice 少许多，所以我们只需要考虑 Bob 能赢的情况。

我们发现，Bob 的数组如果和 Alice 的不同，那么 Alice 一定会赢，因为两人是足够聪明的，且一定存在一种取数方案使得 Alice 剩下的数字与 Bob 不同。

那如果两人数组相同呢？

每次 Alice 取走第一个数，Bob 要想赢必须取走第一个数；Alice 取走最后一个数的话，Bob 也必须取走最后一个数。所以最后 Bob 必赢。所以我们得出结论：两人数组如果相同，Alice 不管怎么取，Bob 一定会赢。

这就结束了吗？

我们可以发现，对于两人数组相同的情况，Alice 取走哪一个数，Bob 也取走一个位置上的数。我们思考如果 Alice 取走第一个数，让 Bob 取走最后一个数；Alice 取走最后一个数，让 Bob 取走第一个数呢？如果这种情况下 Bob 赢了，那就说明 Alice 数组倒转过来就是 Bob 的数组。所以我们发现 Alice 的数组反转过来和 Bob 的数组一样，Bob 也一定会赢。

判断数列是否相同，可以使用 STL 中的 vector 实现判等。

**对于每个测试点注意重置 vector。**

### 代码

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
ll t;

ll n, m;
ll x;
vector<ll> a, b;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> t;

    while (t--)
    {
        a.clear(), b.clear();
        cin >> n;

        for (ll i = 1; i <= n; i++)
            cin >> x,
                a.push_back(x);

        for (ll i = 1; i <= n; i++)
            cin >> x,
                b.push_back(x);

        if (a == b)
        {
            cout << "Bob\n";
            continue;
        }
        reverse(a.begin(), a.end());
        if (a == b)
        {
            cout << "Bob\n";
            continue;
        }

        cout << "Alice\n";
    }
    return 0;
}
```

---

