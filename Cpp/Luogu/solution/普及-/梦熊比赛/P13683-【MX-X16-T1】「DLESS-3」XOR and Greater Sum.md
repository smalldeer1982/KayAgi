# 【MX-X16-T1】「DLESS-3」XOR and Greater Sum

## 题目描述

给定长度为 $n$ 的非负整数序列 $a_1, \ldots, a_n$。

小 H 希望选出其中若干个数，使得这些数的按位异或和大于剩下数的按位异或和。小 H 可以选 $0$ 个，此时这些数按位异或和为 $0$；也可以全选，此时剩下的数按位异或和为 $0$。

请你告诉他是否有解。

## 说明/提示

**【样例解释】**

对于第一组数据，序列 $a$ 为 $[1, 1, 4, 5, 1, 4]$。我们可以选择子序列 $[5]$，其异或和为 $5$。剩下的数字为 $[1, 1, 4, 1, 4]$，其异或和为 $1\oplus 1\oplus 4\oplus 1\oplus 4=1$。因为 $5>1$，所以有解。

对于第二组数据，序列 $a$ 为 $[1, 1, 4, 5, 1]$。可以证明对于任意一种划分，选出数的异或和总是不大于剩下数的异或和。

对于第三组数据，可以选择子序列 $[9,1]$，其异或和为 $8$。剩下数的异或和为 $1\oplus 9\oplus 8\oplus 1\oplus 0=1$。因为 $8>1$，所以有解。

**【数据范围】**

对于所有数据，保证 $1\le T\le 10^5$，$1\le n,\sum n\le 10^6$，$0\le a_i<2^{30}$。

各测试点特殊限制如下：

|测试点编号|$\sum n\le$|$a_i<$|
|:-:|:-:|:-:|
|$1\sim 4$|$20$|$2^{30}$|
|$5\sim 10$|$5000$|$2^6$|
|$11\sim 20$|$10^6$|$2^{30}$|



## 样例 #1

### 输入

```
4
6
1 1 4 5 1 4
5
1 1 4 5 1
7
1 9 1 9 8 1 0
7
1 9 1 9 8 1 9
```

### 输出

```
Yes
No
Yes
No```

# 题解

## 作者：luogu_gza (赞：4)

如果整个序列异或和为 $0$，那么无论我们怎么选，选定的数的异或和与剩下的数的异或和总是相等，因此输出 `No`。

否则，我们直接把所有数选上，剩下的数异或和为 $0$，因此输出 `Yes`。

核心代码：

```cpp
const int N=1e6+10;
int n;
int a[N];
void solve()
{
  n=R;
  int sum=0;
  fo(i,1,n) a[i]=R,sum^=a[i];
  if(sum==0) puts("No");
  else puts("Yes");
}
void main(){
  MT solve();
}
```

---

## 作者：Clare613 (赞：2)

## 思路：
我们可以发现，如果一个数列，所有的数的异或和为 $0$，那么可以正好分为两组，但是可以发现，这两组的值一定相等，应为拆散一对，两边都会得到一样的值。所以说只需要判断异或和是否为 $0$，是输出 `No`，不是输出 `Yes`。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int T;
	cin>>T;
	while(T--){
		int x=0,n;
		cin>>n;
		while(n--){
			int s;
			cin>>s;
			x^=s;
		}
		if(x==0){
			cout<<"No\n";
		}
		else{
			cout<<"Yes\n";
		}
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：2)

按位异或有性质：若 $x\oplus y=0$，则 $x=y$。证明显然（$x$ 和 $y$ 的每个二进制位都相等）。

考虑所有数的按位异或和。
- 若为 $0$，则无论如何选择，两部分的异或和一定相等，即一定无解。
- 否则，易得全选符合要求。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n;int x,ans=0;
		while(n--){
			cin>>x;
			ans^=x;
		}
		puts(ans?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：lilong (赞：2)

首先给出结论：当且仅当所有数的异或和不为 $0$ 时有解。

接下来证明正确性：当异或和不为 $0$ 时，选择全部数，剩下的为 $0$，显然合法；当异或和为 $0$ 时，从中选若干个数，那么选的数的异或和一定与剩余的数的异或和相等（否则与异或和为 $0$ 矛盾），不合法。

时间复杂度 $O(\sum n)$。

```cpp
#include<iostream>
#include<cstdio>
#define N 1000010
using namespace std;
int n,k,a[N];
void solve(){
    cin>>n;k=0;
    for(int i=1;i<=n;i++)
        cin>>a[i],k^=a[i];
    if(k)cout<<"Yes\n";
    else cout<<"No\n";
    return;
}
int main(){
    int T;
    cin>>T;
    while(T--)
        solve();
    return 0;
}
```

---

## 作者：_____Elysia_____ (赞：2)

~~[双倍经验。](https://www.luogu.com.cn/problem/P2197)~~

这道题让我们求出是否存在一种方案选出数组中的一些数，使得这些数的按位异或和大于剩下数的按位异或和，可以不选或全选。

记 $x$ 为数组中所有数的按位异或和，分类讨论一下：

### $x>0$
此时所有数的按位异或和大于 $0$，而根据题意，全选的时候剩下的数的按位异或和等于 $0$，因此全选就是一组解。

### $x=0$
当所有数的按位异或和等于 $0$ 的时候，无论如何选数，两部分的按位异或和必然相等（因为所有数的按位异或和都等于 $0$ 了，把两部分的按位异或和异或起来就等于 $0$，因此两部分的按位异或和相等），所以不存在方案满足条件。

代码就不贴了。

---

## 作者：Na1L0n9 (赞：2)

# Solution
## 思路
题目中已经给我们暗示了，如果选择序列里的所有数，那么剩下的数按位异或和为 $0$。所以如果这个序列的异或和大于 $0$，答案肯定为 `Yes`。接下来只要看序列异或和为 $0$ 的情况了。

我们可以记被选择的数的异或和为 $a$，未被选择的数的异或和为 $b$，由于异或满足交换律和结合律，所以显然有 $a\oplus b=0$，再根据异或的自反性可得，$a\oplus 0=b$，因为一个数异或 $0$ 的结果是它本身，所以 $a=b$，即无法构造出 $a>b$ 的情况，答案为 `No`。
## Code
```cpp
#include <bits/stdc++.h>
#define Write ios::sync_with_stdio(0);
#define by cin.tie(0);
#define AquaDaMean1e cout.tie(0);
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 10;
ll T, n, xr, a[N];
int main() {
	Write by AquaDaMean1e
	cin >> T;
	while (T--) {
		cin >> n;
        xr = 0;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
            xr ^= a[i];
		}
		cout << (xr > 0 ? "Yes\n" : "No\n");
	}
	return 0;
}
```

---

## 作者：XingYueLi (赞：1)

## 思路

设所有数的总异或为 $X=a_1\oplus a_2\oplus\cdots\oplus a_n$.

若我们选出的子集异或为 $A$，剩下的异或就是 $B=X\oplus A$。要求 $A>B$，即 $A>X\oplus A$。

当 $X=0$ 时：此时 $B=X\oplus A=A$，无论怎么选都有 $A=B$，不可能 $A>B$。

当 $X\neq0$ 时，观察最高不同位：$A$ 与 $B$ 的最高不同位必然是 $X$ 的最高置位（记为第 $k$ 位）。在这一位上，若 $A_k=1$ 则 $A>B$，若 $A_k=0$ 则 $A<B$。

因此只要能让 $A$ 在第 $k$ 位取到 1，就一定有解。

而第 $k$ 位能否取到 1，只取决于我们从数组中挑的、在第 $k$ 位为 1 的元素的个数奇偶性。因为 $X$ 的第 $k$ 位为 1，说明整个数组在该位上有**奇数个** 1，所以我们总能挑出**奇数个**这样的元素，使得 $A_k=1$。

于是答案等价于 $X\neq 0$。

## Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        int x = 0;
        for (int i = 0; i < n; ++i) {
            int a;
            cin >> a;
            x ^= a;
        }
        cout << (x != 0 ? "Yes" : "No") << endl;
    }
    return 0;
}
```

时间复杂度 $O(\sum n)$，空间 $O(1)$。

---

## 作者：ylch (赞：1)

设整个序列的异或和为 $S$。

如果 $S > 0$，则选择整个序列（全选）时，子序列异或和为 $S$，剩余部分异或和为 $0$，满足 $S > 0$。

如果 $S = 0$，则无论选择哪个子序列，设其异或和为 $X$，剩余部分的异或和也为 $X$（因为 $S \oplus X = 0 \oplus X = X$），无法满足 $X > X$。

因此，当且仅当 $S > 0$ 时，存在满足条件的子序列（全选即可）。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 7;

vector<int> a[maxn];

signed main()
{
	ios :: sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
	int T; cin >> T;
	for(int i = 1; i <= T; i ++){
		int n; cin >> n; a[i].push_back(n); // a[i][0]=n
		for(int j = 1, x; j <= n; j ++){
			cin >> x; a[i].push_back(x);
		}
	}
	for(int p = 1; p <= T; p ++){
		int s = 0, n = a[p][0];
		for(int i = 1; i <= n; i ++) s ^= a[p][i];
		puts(s > 0? "Yes" : "No");
	}
	return 0;
}

```

~~码风太丑勿喷。~~

---

## 作者：__CJY__ (赞：1)

## 思路
设总异或和为 $res$，选中的异或和 $S$，剩下的就是 $res \oplus S$ 了。

我们需要使得 $S>(res \oplus S)$，那么就要分类讨论：
* 当 $res \ne 0$ 时：让 $S=res$ 使得 $res \oplus S=0$，那 $S>(res \oplus S)$ 就成立了。
* 当 $res=0$ 时：必有 $S=res \oplus S=0$，永远无法满足 $S>(res \oplus S)$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int a[maxn],n,res,T;
void solve(){
	cin>>n,res=0;
	for(int i=1;i<=n;i++) cin>>a[i],res^=a[i];
	if(res) cout<<"Yes\n";
	else cout<<"No\n";
}
int main(){
	cin>>T;
	while(T--) solve();
}
```

---

## 作者：__DayLight__ (赞：1)

## 前言
赛时瞎猜的结论然后对了，现在开始验证。

## 思路

简化一下题目：给出一个集合 $$S$$，让你分成两个子集，满足其中一个子集的异或和**大于**另外一个。

>注意：可以出现空集。

所以我们完全可以忽略分解集合 $S$ 的过程，直接让 $S$ 的异或和 与 $0$ 进行比较（因为空集的异或和为 $0$）。

很容易产生一个疑问：若集合 $S$ 的异或和也为 $0$ 怎么办？  
那就是无解咯。

因为如果将集合 $S$ 分成子集 $X$ 与 子集 $Y$，那么只有 $X$ 的异或和与 $Y$ 的异或和相等的时候才满足 $S$ 的异或和为 $0$，不满足题意。  
所以此时再思考如何分子集将**毫无意义**。

那就成功得出了结论：
>若集合 $S$ 的异或和不为 $0$ 则有解，反之无解。

核心出装如下。
```cpp
while(n--)
{
      int x;
      cin>>x;
      sum^=x;
}
```

---

## 作者：SuyctidohanQ (赞：1)

### 思路分析

首先，一个结论是：整个序列异或为 $0$ 答案就是 `No` 否则 `Yes`。

以下是证明：

> 设序列的总异或和为 $sum = a_1 \oplus a_2 \oplus \ldots\oplus a_n$。
>
> 设选出的子序列异或和为 $S$，则剩下的数的异或和为 $S' = sum \oplus S$，然后题目就转化为了是否存在 $S$ 使得 $S > S'$。
>
> 若序列总异或和 $sum \neq 0$，尝试选择所有元素，则剩余元素的异或和为 $0$。由于 $sum \neq 0$ 显然 $sum > 0$ 即 $S = sum > 0 = S'$ 存在满足条件的选择。
>
> 若序列总异或和 $sum = 0$，则对任意选择的子序列异或和 $S$，剩余元素的异或和为 $S$，此时 $S = S'$，即无论如何选择子序列，选出元素的异或和都等于剩余元素的异或和，不可能满足 $S > S'$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
void solve() {
	int n; scanf("%d", &n);
	int a[n + 10];
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	int XOR = 0;
	for(int i = 1; i <= n; i++) {
		XOR = XOR ^ a[i];
	}
	if(XOR == 0) printf("No\n");
	else printf("Yes\n");
}
int main() {
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}
```

---

## 作者：Charged_Charge (赞：1)

# 洛谷 P13683
## 题目大意：
给定 $t$ 组数据，每一个数据包含一个 $n$，接下来有 $n$ 个数，分别为每一个 $a_i$。对于每一组数据，如果可以通过选一些数异或和大于剩下的数的异或和，就输出 `Yes`，否则输出 `No`。
## 解题思路：
这道题很简单，只用判断全选后，异或和是否为 $0$。因为如果全选还不满足，不全选更不能满足。如果全选后异或和确实不为零，输出 `Yes`，否则输出 `No`。
## AC 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6+20;
int t, n;
int a[N];
signed main() {
	cin >> t;

	while (t--) {
		cin >> n;
		int sum = 0;

		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			sum ^= a[i];
		}

		if (sum == 0) {
			cout << "No" << endl;
		} else {
			cout << "Yes" << endl;
		}
	}

	return 0;
}
```

---

## 作者：xtzhangziche (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13683)

## 题目大意
题目的意思其实就是将一个序列分成两份，问两份的异或和相不相等，相等输出 `Yes`，不相等输出 `No`。

## 思路
首先，我们可以求所有数的异或和。

因为 $a \oplus a = 0$，就可以得知：

如果所有数的异或和为 $0$，则分成两堆的糖果的异或和相等，当所有数的异或不为 $0$ 时，则分成两堆的糖果的异或和不同，输出 `Yes`，否则输出 `No`。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,a;
signed main(){
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>T;
    while(T--)
    {
     cin>>n;
     int t=0;
     while(n--) cin>>a,t^=a;
     if(t) cout<<"Yes\n";
     else cout<<"No\n";
    }
	return 0;
}
```

---

## 作者：wbqhasvcf (赞：0)

这是道妥妥的诈骗题。

判断是否有解，那就要考虑何种情况是无解的?看题，“使得这些数的按位异或和**大于**剩下数的按位异或和”，这是有解的条件，那无解就是把“大于”这个词换成“不大于”呗，而不大于分小于和等于两种情况，有“小于”就一定有“大于”，而无解是保证任何选数方案都不符合条件，所以只有“等于”这种情况符合了。

所以翻译为人话，无解，等价于，“使得这些数的按位异或和**等于**剩下数的按位异或和”。那如何保证任何一种选数方案都能满足这种条件呢？很简单，只要序列的异或和为 $0$ 即可。如果一个序列有一种选数方案能保证划出来的两组数的异或和相等，那么整个序列的异或和便为 $0$，注意**异或运算满足交换律**，那么~~星星之火可以燎原~~，其他的所有选数方案便也一定满足划出来的两组数异或和相等！所以“序列的异或和为 $0$”是无解的充要条件。

那这题我们就做完啦，只要发现诈骗时间复杂度横竖都得是 $O(n)$：
```cpp
#include<iostream>
using namespace std;

int t,n,a;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		int is=0;//观察题目中的数据范围，开int即可
		while(n--)
		{
			cin>>a;
			is^=a;
		}
		if(is) cout<<"Yes"<<endl;
		else cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

[**或许**更好的阅读体验](https://joshuajjm.github.io/2025/08/10/P13683%E9%A2%98%E8%A7%A3/)

# 题解：P13683 【MX-X16-T1】「DLESS-3」XOR and Greater Sum

## 思路

解决这个问题的关键是利用线性基（一种用于处理异或运算的数学工具）和异或的基本性质：

- 异或的基本性质：
  - 若 $A$ 是整个数组的异或和，$B$ 是某个子集的异或和，那么剩余元素的异或和为 $A\oplus B$（因为 $B\oplus(A\oplus B)A$）。
  - 要使子集 $S$ 的异或和等于 $A$，则剩余元素的异或和必为 0（因为 $A\oplus A=0$）。即问题等价于：判断数组是否存在非空真子集，其异或和为 0。
- 线性基的作用：
  - 线性基可以用来表示数组中所有元素的异或组合，基的大小反映了数组中线性无关元素的数量。
  - 若数组的线性基大小小于数组元素个数，则说明存在非空子集的异或和为 0（存在冗余元素）。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(){
	int n;
	cin>>n;
	vector<int> a(n);
	int totxor=0;
	
	for(int i=0;i<n;++i){
		cin>>a[i];
		totxor^=a[i];
	}
	
	if(totxor==0) return false;//如果整个数组的异或和为 0，那么不存在非空真子集的异或和为 0
	
	int k=31-__builtin_clz(totxor);//找到最高位的 1 的位置
	
	vector<int> ans(30,0);
	
	for(auto i:a){//对于每个数，尝试将其插入线性基
		int x=i;
		for(int i=29;i>=0;--i){//从高位到低位
			if((x>>i)&1){
				if(ans[i]==0){//如果当前位为 1，且线性基中没有该位为 1 的数，那么直接插入
					ans[i]=x;
					break;
				}
				else{
					x^=ans[i];
				}
			}
		}
	}
	
	return ans[k]!=0;
}

int main(){
	int t;
	cin>>t;
	while(t--){
		cout<<(check()?"Yes":"No")<<endl;
	}
	
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/230057257)

## 复杂度分析：

- 时间复杂度：$O(Tn\log n)$，完全可以通过。
- 空间复杂度：$O(n)$，主要用于存储数组和线性基。

---

## 作者：LTTXiaochuan (赞：0)

##### T1 [P13683 【MX-X16-T1】「DLESS-3」XOR and Greater Sum - 洛谷](https://www.luogu.com.cn/problem/P13683?contestId=265699)

**题目大意**：判断是否能将序列分成异或和不等的两部分（空集算作 $0$）。

直接蔡杰伦！

如果整个序列的异或和是 $0$，剩下的空集是 $0$，那一定是不符合条件的。

这个时候从里面分出一个数来，假设分出 $b$，那么前面所有数的异或和设为 $a$，一定有 $a=b$。

此时再拆 $a$，**由于异或运算满足结合律**，无论怎么拆了再分配，得到的两组数的异或和都一定是 $0$。



```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int T;
    cin>>T;
    while(T--)
    {
        int n,x;
        cin>>n;
        int ans=0;
        for(int i=1; i<=n; i++) cin>>x,ans^=x;
        if(ans) cout<<"Yes\n";
        else cout<<"No\n";
    }

    return 0;
}
```

---

## 作者：jcf666 (赞：0)

# 题目大意
能否在数列中取若干个数，使这若干个数的异或和大于未被取的数的异或和？
# 个人思路
异或满足交换律且具有自反性，具体见下：
```
自反性：a xor a = 0
交换律：a xor (b xor c) = (a xor b) xor c
```
由此可以得出当一个数列的异或和为 $0$ 时，不管取哪些数，最终的异或和与未被取的数的异或和都相等。我们可以举个例子，就比如题目样例中的序列 $[1, 1, 4, 5, 1]$，这个序列的异或和就是 $0$，然而也确实取不出符合题目要求的几个数字，取出来数字的异或和永远只能等于没有被取的数字的异或和。

这样，题目的代码就很简单了，判断一下整个序列的异或和是否为 $0$，若是，输出 `No`，若不是，输出 `Yes`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,T;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		a=0;
		for(int i=1,x;i<=n;i++)cin>>x,a^=x;
		if(a)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

