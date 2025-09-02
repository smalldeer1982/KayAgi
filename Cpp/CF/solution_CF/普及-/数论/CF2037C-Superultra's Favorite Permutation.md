# Superultra's Favorite Permutation

## 题目描述

Superultra, a little red panda, desperately wants primogems. In his dreams, a voice tells him that he must solve the following task to obtain a lifetime supply of primogems. Help Superultra!

Construct a permutation $ ^{\text{∗}} $ $ p $ of length $ n $ such that $ p_i + p_{i+1} $ is composite $ ^{\text{†}} $ over all $ 1 \leq i \leq n - 1 $ . If it's not possible, output $ -1 $ .

 $ ^{\text{∗}} $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

 $ ^{\text{†}} $ An integer $ x $ is composite if it has at least one other divisor besides $ 1 $ and $ x $ . For example, $ 4 $ is composite because $ 2 $ is a divisor.

## 说明/提示

In the first example, it can be shown that all permutation of size $ 3 $ contain two adjacent elements whose sum is prime. For example, in the permutation $ [2,3,1] $ the sum $ 2+3=5 $ is prime.

In the second example, we can verify that the sample output is correct because $ 1+8 $ , $ 8+7 $ , $ 7+3 $ , $ 3+6 $ , $ 6+2 $ , $ 2+4 $ , and $ 4+5 $ are all composite. There may be other constructions that are correct.

## 样例 #1

### 输入

```
2
3
8```

### 输出

```
-1
1 8 7 3 6 2 4 5```

# 题解

## 作者：ridewind2013 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF2037C)

## **题目描述**

输入 $n$，用 $1$ 到 $n$ 中的所有数构造一个数列，使得数列中任意相邻两个数的和为合数。如果可以输出任意一组，否则输出 $-1$。

## **分析**

除 $2$ 以外的偶数都是合数，所以只需要奇数挨着奇数，偶数挨着偶数，最小的一个奇数和一个偶数的和为质数是 $5$ 和 $4$，所以在奇数与偶数的交界处分别放 $5$ 和 $4$，就可以构造出这个数列。

> - 当 $n \le 4$ 时，无解，输出 $-1$。
>  
> - 否则，先在放置除 $5$ 以外的奇数，再分别放置 $5$ 和 $4$，最后放置除 $4$ 以外的偶数。

## **代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
	cin>>t;
	while(t--){
        int n;
		cin>>n;
		if(n<=4)cout<<-1<<"\n";//无解
		else{
			for(int i=1;i<=n;i++){//放置除5以外的奇数
				if(i%2!=0&&i!=5){
					cout<<i<<" ";
				}
			}
			cout<<5<<" "<<4<<" ";//放置交界处
			for(int i=1;i<=n;i++){
				if(i%2==0&&i!=4){//放置除4以外的偶数
					cout<<i<<" ";
				}
			}
			cout<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：K_yuxiang_rose (赞：2)

一道简单构造题。

这里先引入一些小学知识：
>奇数 $+$ 奇数 $=$ 偶数
>
>偶数 $+$ 偶数 $=$ 偶数
>
>除 $2$ 以外，任何偶数都是合数

那么我们可以考虑将偶数放在一边，奇数放在另一边，这样只有数列中间的两个数字和是奇数，此时可以使用最小的奇合数 $9$ 来作为两数之和，而 $9$ 可以被分成 $4$ 和 $5$，于是我们只需将 $4$ 和 $5$ 放在数列中间即可。

当 $n \le 4$ 时，可以通过暴力枚举来证明无解。


```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		if(n<=4)
		{
			cout<<-1<<endl;
			continue;
		}
		for(int i=2;i<=n;i+=2)
		{
			if(i!=4) cout<<i<<" ";
		}//先将偶数放在一边
		cout<<"4 5 ";//将4和5放在中间
		for(int i=1;i<=n;i+=2)
		{
			if(i!=5) cout<<i<<" ";
		}//再将奇数放在另一边
		cout<<endl;
	}
	return 0;
}
```
AC记录：

![](https://cdn.luogu.com.cn/upload/image_hosting/xby1d0su.png)

---

## 作者：RAY091016 (赞：2)

### 0. 题目链接

[CF2037C Superultra's Favorite Permutation](https://www.luogu.com.cn/problem/CF2037C)

**请没读过题目的读者先去读题！！！**


### 1. 题目解释

**多测**，对于每一组数据，请给出一个 $n$ 的全排列，使得相邻两项的和为合数。

### 2. 思路

通过一组暴力的 DFS 我们可以看出，在 $n\le 4$ 的情况下是无解的。

然后我们考虑构造这个数列。

发现题目要求的是全排列而且相邻两项的和为合数。

而众所周知，偶数（除了 $2$）以外都是合数，而全排列的条件又恰好避免了 $2$ 的出现。

考虑构造一个前部全为奇数而后部全为偶数的数列，这样就可以使得相邻两项的和（除了奇偶交接处）都为大于 $2$ 的偶数，即为合数。

然后考虑奇偶交接处，由于此处和为奇数，自然考虑奇合数。

又众所周知最小的奇合数是 $9=4+5$。

所以我们考虑构造这样一个数列：前半部分为奇数且最后一个为 $5$，后半部分为偶数且第一个为 $4$。

正确性不难证明。

### 3. 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		if(n<=4){
			cout<<-1<<endl;
		}
		else{
			for(int i=1;i<=n;i++){
				if(i%2==1&&i!=5){
					cout<<i<<" ";
				}
			}
			cout<<"5 4 ";
			for(int i=1;i<=n;i++){
				if(i%2==0&&i!=4){
					cout<<i<<" ";
				}
			}
			cout<<endl;
		}
	}
	return 0;
}
```

---

## 作者：WRT_Partisan (赞：1)

# 题解：CF2037C Superultra's Favorite Permutation

[题目链接](https://www.luogu.com.cn/problem/CF2037C)

## 题目大意

给定 $n$，构建长度为 $n$ 的排列 $p$，使对于每一个 $1\leq i\leq n-1$，$p_i+p_{i+1}$ 不为素数。

## 解题思路

可以发现，当 $n\leq 4$ 时是无解的。

当 $n\geq 5$ 时，先将偶数和偶数放在一起（$\text{偶数}+\text{偶数}=\text{偶数}$ ），将 $4$ 放在最后，然后将 $5$ 放在 $4$ 后面（$5+4=9=3\times 3$），最后再在后面放上奇数（$\text{奇数}+\text{奇数}=\text{偶数}$）。

## 代码

```cpp
/*
 * @FilePath: \c++\CF2037C.cpp
 * @Author: WRT_Partisan
 * @Date: 2024-11-23 20:40:56
 */
#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef unsigned long long ull;
int t, n;
signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        scanf("%lld", &n);
        if (n <= 4)
            printf("-1\n");
        else
        {
            for (int i = 2; i <= n; i += 2)
                if (i != 4)
                    printf("%lld ", i);
            printf("4 5 ");
            for (int i = 1; i <= n; i += 2)
                if (i != 5)
                    printf("%lld ", i);
            printf("\n");
        }
    }
    return 0;
}
```

---

## 作者：DoubleQLzn (赞：1)

一道简单的构造题，建议评橙。

### Description

对于每个 $n$ 构造一个 $1-n$ 的排列，使每两个相邻元素何均为合数。

### Solution

小学数学学过，除了 $2$ 以外所有偶数都是合数。

于是我们可以优先让和之间为偶数。若 $(a+b)\bmod 2=0$，则 **当且仅当** 下面两种情况:

- $a\bmod 2=0$ 且 $b\bmod 2=0$
- $a\bmod 2=1$ 且 $b\bmod 2=1$

因此，我们可以先输出所有奇数，再输出所有偶数。但这时就出现了一个问题：奇数与偶数中间的和。于是，我们可以 **固定两个数，使他们相加为合数，且一个是奇数，一个是偶数**。其中最小的一个即为 $(4,5)$。而这两个数在分别输出奇数与偶数时跳过即可。

思路很显然，接下来是无解的情况，由于最小的中间衔接部分的两个数中最大的为 $5$。所以 $n<5$ 的时候输出无解。

### Code

请勿抄袭。

```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n;
void solve()
{
	cin >> n;
	if (n < 5)
	{
		cout << "-1\n";
		return ;
	} //若 n < 5，输出无解
	for (int i = 1;i <= n;i = i + 2)
	{
		if (i != 5) cout << i << ' ';
	} //输出除 5 以外的奇数
	cout << "5 4 "; //输出 (5,4)
	for (int i = 2;i <= n;i = i + 2)
	{
		if (i != 4) cout << i << ' ';
	} //输出除 4 以外的偶数
	cout << '\n';
}
int main()
{
	cin >> t;
	while (t--)
	{
		solve();
	}
  return 0;
}

---

## 作者：Sakura_Emilia (赞：1)

# 构造题

这道题其实有点类似于素数环问题，一开始尝试使用 DFS 直接搜索。但其实没必要进行搜索，直接特殊构造即可。要求相邻的两个数相加为合数，在构造时选取最特殊的情况，相邻两个数为偶数即可。

如何构造使得相邻的两个数相加为偶数？最简单的方案是将 $n$ 个数分为奇数和偶数两部分，两个奇数相加一定是偶数，两个偶数相加一定是偶数。唯一的特殊情况就是，奇数区域与偶数区域相邻的交接处，如何构造一个奇数和偶数相加，结果为合数。

最小的同时为奇数和合数的数是 $1+8=9$，因此当 $n$ 大于 $8$ 时可以直接按照这种方案进行构造，奇数区域与偶数区域相邻的交接处放置 $1$ 和 $8$。对于 $n$ 小于 $8$ 时，直接构造特例单独判断即可。

# Code

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define Ciallo main
#define int long long
using namespace std;

int T, n;

inline void solve() {
    cin >> n;
    if(n <= 4)
        cout << -1 << endl;
    else if(n == 5)
        cout << "1 3 5 4 2" << endl;
    else if(n == 6)
        cout << "1 3 5 4 2 6" << endl;
    else if(n == 7)
        cout << "1 3 5 4 6 2 7" << endl;
    else if(n == 8)
        cout << "1 3 5 4 2 6 8 7" << endl;
    else {
        for(int i = 3; i <= n; i++)
            if(i % 2 == 1)
                cout << i << ' ';
        cout << 1 << ' ' << 8 << ' ';
        for(int i = 2; i <= n; i++)
            if(i % 2 == 0 and i != 8)
                cout << i << ' ';
        cout << endl;
    }
}

signed Ciallo() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> T;
    while(T--)
        solve();

    return 0;
}
```

---

## 作者：chengjindong (赞：0)

[题目](https://www.luogu.com.cn/problem/CF2037C)

除了 $2$ 之外的偶数，都不是质数，那么，只需要奇数挨奇数，偶数挨偶数，就行了。最小的又是奇数又是合数的数是 $9$，能拆成 $4$ 和 $5$，把 $4$ 和 $5$ 放中间分隔偶数和奇数即可。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int t;
	cin >>t;
	while(t--){
		int n;
		cin >>n;
		if(n<=4){//特判，这个情况无解 
			cout<<-1<<endl;
		}else{
			for(int i=2;i<=n;i+=2){//偶数
				if(i!=4){//不能是4 
					cout<<i<<" ";
				}
			}
			cout<<"4 5 ";//分开偶数和奇数 
			for(int i=1;i<=n;i+=2){//奇数
				if(i!=5){//不能是5 
					cout<<i<<" ";
				}
			}
			cout<<endl;//换个行 
		}
	}
	return 0;
}
```

---

## 作者：programmer330 (赞：0)

## 题解：CF2037C Superultra's Favorite Permutation

### 题意复述

给定一个自然数 $n$，用 $1$ 到 $n$ 中的所有数构造一个数列 $a_1,a_2,a_3,\cdots,a_n$，使得数列中任意相邻两个数的和为合数。

### 思路分析

首先，除 $2$ 之外所有的偶数均为合数。引用小学知识：奇数与奇数和为偶数，偶数与偶数和为偶数。所以一个理想的方案就是在前面放奇数，在后面放偶数。

那么在奇数与偶数的交界处呢？$1$ 与 $2$ 的和 $3$ 为质数，$2$ 与 $3$ 的和 $5$ 为质数，$3$ 与 $4$ 的和 $7$ 为质数，$4$ 与 $5$ 的和 $9$ 为合数。

所以可以得到：当 $n<5$ 时，一定构造不出符合要求的数列；当 $n\ge5$ 时，在奇数与偶数的交界处分别放 $5$ 和 $4$ 即可。

### 代码实现


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t;
signed main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		if(n<5){
			cout<<-1<<endl;
		}else{		
			for(int i=1;i<=n;i+=2){
				if(i!=5)cout<<i<<" ";
			}
			cout<<5<<" "<<4<<" ";
			for(int i=2;i<=n;i+=2){
				if(i!=4)cout<<i<<" ";
			}
			cout<<endl;
		}
	}
	return 0;
}

```

---

## 作者：cqbzhzf (赞：0)

### 思路
- 读完题，可以发现，如果把奇数和偶数穿插排列情况会很复杂，考虑把奇数与偶数，分别放一起。
- 如果把奇数和偶数分别放一起就只用考虑偶数与奇数的交界处。因为奇数加奇数和偶数加偶数都是偶数，肯定是合数，满足题目要求。
- 对于奇数与偶数的交界处，如果加起来不是合数则无解，考虑如何构造。
- 可以发现，一奇一偶相加得奇。而满足这种构造的最小数为 $9（5+4）$，所以当 $n<5$ 时，无解；当 $n\ge 5$ 时把 $4$ 和 $5$ 放中间，其它偶数和奇数分别放左右两边，注意实现细节即可。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
int t,n,a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		memset(a,0,sizeof(a));
		cin>>n;
		if(n<5)
		{
			cout<<"-1\n";
			continue;
		}
		int l,r;
		if(n%2!=0)
		{
			a[(n+1)/2]=5;
			a[n/2]=4;
			l=n/2-1,r=(n+1)/2+1;
			int cnt1=2,cnt2=1;
			while(l>=1||r<=n)
			{
				if(cnt1==4)
					cnt1+=2;
				if(cnt2==5)
					cnt2+=2;				
				if(l>=1)
					a[l]=cnt1;
				if(r<=n)
					a[r]=cnt2;
				cnt1+=2;
				cnt2+=2;
				l--,r++;
			}			
		}
		else
		{
			a[n/2]=4;
			a[n/2+1]=5;
			l=n/2-1,r=n/2+2;
			int cnt1=2,cnt2=1;
			while(l>=1||r<=n)
			{
				if(cnt1==4)
					cnt1+=2;
				if(cnt2==5)
					cnt2+=2;				
				if(l>=1)
					a[l]=cnt1;
				if(r<=n)
					a[r]=cnt2;
				cnt1+=2;
				cnt2+=2;
				l--,r++;
			}	
		}
		for(int i=1;i<=n;i++)
			cout<<a[i]<<" ";
		cout<<"\n";
	}
	return 0;
}

---

## 作者：_colin1112_ (赞：0)

## 思路

构造题。

大概意思就是构造数列 $p$，使得对于 $1 \leq i \leq n - 1$，$a_i + a_{i + 1}$ 不是素数。

易证当 $n \leq 4$ 时，无解。

因为偶数 + 偶数 = 偶数，奇数 + 奇数 = 偶数。所以在数列左边放偶数，右边放奇数即可。但是在偶数和奇数在接口处可能会出现素数，于是在偶数与奇数处放 `4` 和 `5` 作为接口即可。

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll t;
ll x;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> x;
        if (x <= 4)
        {
            cout << -1 << endl;
            continue;
        }
        for (int i = 2; i <= x; i += 2)
            if (i != 4)
                cout << i << ' ';
        cout << "4 5 ";
        for (int i = 1; i <= x; i += 2)
            if (i != 5)
                cout << i << ' ';
        cout << endl;
    }
    return 0;
}
```

---

## 作者：Stars_visitor_tyw (赞：0)

## 题解：CF2037C Superultra's Favorite Permutation
### 分析
复合整数的概念其实就是合数。

先判无解，手动模拟一下，$n \le 4$ 时，无论怎么排列都无解。

根据两个奇数的和为奇数，两个偶数的和为偶数可以得出大概思路：奇数放在一起，偶数放在一起。那么问题来了：偶数和奇数的交界处如何处理呢？考虑固定一个奇数一个偶数放在奇偶交界处，比如说 $4$ 和 $5$，这样就可以使得交界处的两个数字之和一定为合数。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
signed main()
{
	int t;
	for(cin>>t;t;t--)
	{
		cin>>n;
		if(n<5)
		{
			cout<<"-1\n";
			continue;
		}
		for(int i=1;i<=n;i+=2)
		{
			if(i==5)
			{
				continue;
			}
			cout<<i<<" ";
		}
		cout<<"5 4 ";
		for(int i=2;i<=n;i+=2)
		{
			if(i==4)continue;
			cout<<i<<" ";
		}
		cout<<"\n";
	}
}

---

## 作者：O_v_O (赞：0)

题目算法： #构造 
## 题意

你需要用 $n$ 个数字构造除一个**排列**，使得任意相邻两项的和**不是质数**，如果无法构造输出 $-1$，否则请输出一种情况。

## 思路

我们都知道，奇 + 奇 = 偶，偶 + 偶 = 偶，而偶数只有 $2$ 是质数，但不可能有方法使得在这个序列中相邻项的和为 $2$，所以我们可以把所有的奇数放一起，所有的偶数放一起。

但我们还需要考虑一个问题，就是偶数和奇数的接口处如何处理。其实我们可以固定一个接口数字，代码里我写的是 $5$ 和 $4$ 为固定的接口数字。

## 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int t, n;
bool vis[N];

void solve() {
  cin >> n;
  if (n < 5) {
    cout << -1 << '\n';
    return;
  }
  for (int i = 1; i <= n; i += 2) {
    if (i == 5)
      continue;
    cout << i << ' ';
  }
  cout << "5 4 ";
  for (int i = 2; i <= n; i += 2) {
    if (i == 4)
      continue;
    cout << i << ' ';
  }
  cout << '\n';
}

int main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

## CF2037C Superultra's Favorite Permutation

### Sol

非常简单，我们知道偶+偶=偶，奇+奇=偶，所以将奇数偶数分开排列就可以了。可是，有一个问题，偶数和奇数的交界处怎么办，万一是 $\cdots 2, 3, \cdots$ 那不就完了？很简单，随便找一个偶数一个奇数加起来不是质数的，比如 $4 + 5 = 9$。然后，把 $4$ 提到偶数队列最后边，$5$ 提到奇数队列最左边就可以了。

最后，还有一点，当 $n \le 4$ 时要输出 $-1$，可以证明当 $n \le 4$ 时奇数偶数交界处加起来一定为质数。

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int kMaxN = 2e5 + 20;
const ll kMod = 998244353;

int n;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int t;
  for (cin >> t; t; -- t) {
    cin >> n;
    if (n <= 4) {
      cout << "-1\n";
    } else {
      for (int i = 2; i <= n; i += 2) {
        if (i == 4) {
          continue;
        }
        cout << i << ' ';
      }
      cout << 4 << ' ' << 5 << ' ';
      for (int i = 1; i <= n; i += 2) {
        if (i == 5) {
          continue;
        }
        cout << i << ' ';
      }
      cout << '\n';
    }
  }
  return 0;
}
```

---

## 作者：xueruhao (赞：0)

挺巧妙的一道题，赛时写得有点暴力，但还是过了。
## 题意概述
给你一个整数 $n$，构造一个长度为 $n$ 的序列 $p$，其中：
- $1 \leq p_i \leq n (1\leq i \leq n)$；
- 所有的 $p_i+p_{i+1} (1\leq i \leq n-1)$ 都是合数。

输入满足所有 $p_i$ 互不相同。


## 解题思路
看到要构造合数，不难想到最简单的方法是构造除了 $2$ 之外的偶数。

学过小学数学的都知道有如下性质：
- $\text{奇数}+\text{奇数} = \text{偶数}$
- $\text{偶数}+\text{偶数} = \text{偶数}$

手动模拟一下发现 $n \leq 4$ 时无解，直接输出 $-1$。

于是 $n>4$ 的思路就很显然了，可以先把 $1$ 到 $n$ 的所有偶数顺次填入，然后枚举每一个奇数，看哪个奇数和最后一位的偶数之和为合数，直接填入，最后把剩下的奇数填入即可。

这么说可能有点抽象，给大家举个例子：


当 $n = 6$ 时，

1. 先把偶数顺次填入：`2 4 6`；
2. 再枚举每一个奇数，看哪个奇数和最后一位的偶数之和为合数，发现 $3$ 可以，直接填入：`2 4 6 3`；
3. 最后把剩下的奇数填入：`2 4 6 3 5 1`。

发现 `2 4 6 3 5 1` 的确是一个合法的序列。

## 赛时AC代码：
```cpp
#include <bits/stdc++.h>
using namespace std;

bool CK(int x) {
    if (x <= 1) return false;
    for (int i = 2; i * i <= x; ++i) {
        if (x % i == 0) return true;
    }
    return false;
}

int main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n <=4) {
            cout << -1 << endl;
        } else {
            vector<int> ans;
            vector<int> A, B;
            for (int i = 2; i <= n; i += 2) {
                B.push_back(i);
            }
            int cnt = n;
            if(n&1) cnt++;
            
            for (int i = cnt - 1; i >= 1; i -= 2) {
                A.push_back(i);
            }
            ans.insert(ans.end(), B.begin(), B.end());
            
            for (int i = 0; i < A.size(); ++i) {
                if (CK(B.back() + A[i])) {
                    ans.push_back(A[i]);
                    A.erase(A.begin() + i);
                    break;
                }
            }

            ans.insert(ans.end(), A.begin(), A.end());
            for (int i = 0; i < n; ++i) {
                cout << ans[i] << " ";
            }
            cout << '\n';
        }
    }

    return 0;
}
```

---

