# Appending Mex

## 题目描述

一开始有一个空的序列，每一次可以选取这个序列的一个子序列，并将这个子序列的 $\text{mex}$ 值加入到序列的尾部。

给定长度为 $n$ 的序列 $a_i$，求最小的 $t$ 使得无法通过若干次操作得到序列 $a_1,\ldots,a_t$。

## 样例 #1

### 输入

```
4
0 1 2 1
```

### 输出

```
-1```

## 样例 #2

### 输入

```
3
1 0 1
```

### 输出

```
1```

## 样例 #3

### 输入

```
4
0 1 2 239
```

### 输出

```
4```

# 题解

## 作者：玉树临风英俊潇洒 (赞：3)

# 思路
直接从 $1$ 到 $n$ 暴力枚举

维护变量 $maxn$ 表示当前最大值。

遍历 $a_i$：

1. 如果 $a_i > m$，就直接输出 $i$。

1. 如果 $a_i = m$，就让 $maxn$ 加一。

1. 如果 $a_i < m$，就直接跳过即可。

# 代码

```
#include<iostream>
#define int long long
using namespace std;
int n;
int a[100005];
main() 
{
	cin >> n;
	for(int i = 1;i <= n;++i)cin >> a[i];
	int maxn = 0;
	for(int i = 1;i <= n;++i) {
		if(a[i] > maxn) {
			cout << i;
			return 0;
		}
		else if(a[i] == maxn) maxn++;
		else continue;
	}
	cout << -1;
	return 0;
}
```
在此骗个赞再求一个关注。

---

## 作者：shenbairui (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1054B)

### 题目大意

一开始有一个空的序列，每一次可以选取这个序列的一个子序列，并将这个子序列的 $\text{mex}$ 值加入到序列的尾部。

给定长度为 $n$ 的序列 $a_i$，求最小的 $t$ 使得无法通过若干次操作得到序列 $a_1,\ldots,a_t$。

### 题目分析 
维护一个 $m$ 表示当前可加入的最大数。

直接从 $1$ 到 $n$ 暴力枚举，维护变量 $maxx$ 表示当前最大值。

遍历到 $a_i>m$ 时：就直接输出 $i$。

如果 $a_i=m$，就让 $maxx$ 加一。

如果 $a_i<m$，就直接跳过即可。
### 代码

```cpp
#include<iostream>
#define int long long
using namespace std;
int n,a[100005],maxn;
signed main() {
	cin >> n;
	for(int i = 1;i <= n;i++) cin >> a[i];
	for(int i = 1;i <= n;i++) {
		if(a[i] > maxn) {
			cout << i;
			return 0;
		}
		else if(a[i] == maxn) maxn++;
		else continue;
	}
	cout << -1;
	return 0;
}
```
### [通过记录](https://codeforces.com/contest/1054/submission/295996819)

下次见！拜拜！

---

## 作者：zlqwq (赞：1)

直接从 $1$ 到 $n$ 暴力枚举，维护变量 $maxn$ 表示当前最大值。

遍历到 $a_i$ 时：

如果 $a_i>m$，就直接输出 $i$。

如果 $a_i=m$，就让 $maxn$ 加一。

如果 $a_i <m$，就直接跳过即可。


```cpp
#include<iostream>
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18

using namespace std;
const int N = 1e5 + 5;
int n;
int a[N];
signed main() {
	cin >> n;
	for(int i = 1;i <= n;++i) {
		cin >> a[i];
	}
	int maxn = 0;
	for(int i = 1;i <= n;++i) {
		if(a[i] > maxn) {
			cout << i;
			return 0;
		}
		else if(a[i] == maxn) maxn++;
		else continue;
	}
	cout << -1;
	return 0;
}

```

---

## 作者：John_yangliwu (赞：1)

## 前言

感觉这题没有蓝题水平，也就橙题？

## 思路
要得到 $0$，就选择一个空集；要得到 $1$，选择的子集就要包含 $\{0\}$；$\ \dots\dots $ 要得到 $k$，选择的子集就要包含 $\{0, 1, 2 \dots k-1\}$。

如果目标数组中有一个数 $a_i>\max\limits_{1\le j<i}{a_j}+1$，那么即使我们选 $\{a_{1\dots i-1}\}$ 做子集，得到的 $mex$ 最大也就是 $a_i-1$，达不到目标。

所以我们用 $maxi$ 维护当前出现过的最大值（初值为 $-1$，因为 $0$ 是无论如何都可以得到的），从前往后扫描 $a$。如果发现 $a_i>maxi+1$，则 $a_i$ 不可能得到，令 $t=a_i$，结束循环；反之 $a_i$ 可以得到，令 $maxi=\max(maxi, a_i)$ 即可。

## 代码
```cpp
#include <iostream>
using namespace std;

const int MAXN = 1e5 + 5;
int a[MAXN];
int n, t;

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    int maxi = -1;
    for(int i = 1; i <= n; i++) {
        if(a[i] > maxi + 1) {//得不到 a[i]
            t = i; break;
        }
        else maxi = max(maxi, a[i]);//更新 maxi
    }

    if(t == 0) cout << -1 << endl;
    else cout << t << endl;

    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/47029186)

---
$\Large\text{THE\ \ END}$

---

## 作者：Konnyaku_LXZ (赞：1)

这题题面咋把做法都告诉你了啊，这是我见过的最奇怪的题目了。

**要想得到数字0，可以选择空集作为子集；要想得到数字k，选择的子集必须包含{0,1,...,k-1}。于是，从前往后扫给的数组a，当前的数字最多能比之前出现过的数字大1，否则这个数字是不能被得到的，当前位置就是t。**

换种说法，设当前出现过的最大值为 $maxx$，初始值为 $-1$ 。若 $a_i>maxx+1$ ，则 $i$ 位置的数无法得到；否则在 $a_i$ 和 $maxx$ 中取最大值作为 $maxx$ 的值然后继续遍历即可。

Code：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<cmath>
#include<stack>
using namespace std;

const int MAXN=1e5+50;

int N,a[MAXN],maxx=-1,Ans=0;
bool flag=false;

void Init(){
	cin>>N;
	for(int i=1;i<=N;++i) scanf("%d",&a[i]);
}

void Solve(){
	for(int i=1;i<=N;++i){
		if(a[i]>maxx+1){Ans=i;return;}
		else maxx=max(maxx,a[i]);
	}
	flag=true;
}

void Print(){
	printf("%d\n",flag?-1:Ans);
}

int main(){
	Init();
	Solve();
	Print();
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1054B)

从 $1$ 到 $n$ 枚举这一位能不能由前面得到。

维护一个 $m$ 表示当前可加入的最大数。

如果 $a_i > m$，说明这个数不能由前面得到，直接输出 $i$。

如果 $a_i = m$，把 $a_i$ 加入后可以用整个序列得出 $a_i + 1$，所以让 $m$ 加一。

否则，当 $a_i < m$ 时，可以直接得到 $a_i$，不用对 $m$ 进行操作。

$\mathbb{H} \varepsilon \text{r} \epsilon ' \mathfrak{s}\ \mathcal{M} \mathsf{y}\ \complement o\texttt{d}\mathbf{e}$：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a[100001], m = 0;
int main(){
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++){
		if (a[i] > m){printf("%d", i); return 0;}
		else if (a[i] == m) m++;
	}
	puts("-1");
	return 0;
}
```

---

## 作者：ylch (赞：0)

# [CF1054B](https://www.luogu.com.cn/problem/CF1054B) Appending Mex 题解

## 题意

开始有一个空序列，每次可以选择一个这个序列的子序列，并将这个子序列的 $\text{mex}$ 值插入到这个这个序列的尾部。

给定一个数列 $a_1,a_2,\cdots,a_n$，求最小的 $t$ 使得无法通过上述操作得到 $a_1,a_2,\cdots,a_t$。如果可以通过若干次操作得到整个序列 $a_1,a_2,\cdots,a_n$，则输出 $-1$。

## 解题思路

一个序列的 $\text{mex}$ 指一个序列中最小的未出现过的大于等于 $0$ 的正整数。

也就是说，如果要得到一个 $a_i=k$，则要求选取的子序列中要包含 $\{0,1,2,\cdots,k-1\}$。

所以，如果对于每个 $a_i>0$，都保证 $0,1,2,\cdots,a_i-1$ 在之前的数列中，则一定可以构造出该序列。也就是对于每个 $a_i$，都保证 $a_i-1 \le \max\{a_1,a_2,\cdots,a_{i-1}\}$。

反之，如果 $a_i > \max\{a_1,a_2,\cdots,a_{i-1}\}+1$，说明即使用 $\text{mex}$ 最大的序列 $\{a_1,a_2,\cdots,a_{i-1}\}$ 做被选择的子序列，最大的 $\text{mex}$ 也只能到 $a_i-1$，无法成功构造。

## AC Code
```cpp
#include <iostream>
#include <vector>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector <int> a(n + 1);
    for(int i = 1; i <= n; i ++) cin >> a[i];

    int maxx = -1, t = -1;
    for(int i = 1; i <= n; i ++){
        if(a[i] > maxx + 1){ t = i; break; } // 不符合要求
        maxx = max(maxx, a[i]); // 维护最大值
    }
    cout << t << "\n";
}

signed main()
{
    ios :: sync_with_stdio(false), cin.tie(0), cout.tie(0);
    solve();
    return 0;
}
```

## End

管理员大大辛苦啦~

有不懂的地方欢迎私信、评论，不定期回复。谢谢大家！

---

## 作者：drop (赞：0)

## 思路

首先，从题目里可以得知：$\rm mex$ 是该序列最小的未出现的自然数，就比如：

$\rm mex(0, 2, 3)=1 $ 

$\rm  mex(1, 2, 1)=0 $


所以，可以肯定，如果 $[0,\max(a)]$ 内所有自然数在序列中都有存在，输出 `-1` 否则，输出缺少数字的下标

对于每次加入序列的 $a_i$，如果 $a_i>\max(a_{1\sim i-1})+1$ 那么输出 `i`，否则输出 `-1`

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
int n,mx=-1;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		int a;
		cin>>a;
		if(a>mx+1){
			cout<<i;
			return 0;
		}else mx=max(mx,a);
	}
	cout<<-1;
	return 0;
}
```

---

## 作者：Hutao__ (赞：0)

## 思路


考虑维护一个变量 $maxn$，当 $a_i > maxn $ 时，输出这个 $i$；如果 $a_i = maxn$ 时，$maxn$ 加一。

## 代码

```cpp
//lgRMJ坏了不保证此代码能通过此题
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],maxn;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		if(a[i]>maxn){
			cout<<i;
			return 0;
		}else if(a[i]==maxn)maxn++;
	}
	cout<<-1;
}
```

---

## 作者：ZY当幸福来敲门 (赞：0)

```

 #include<bits/stdc++.h>
using namespace std;
int maxn,n;

int main()
{
   cin>>n;
   for(int i=1;i<=n;i++)
   {
       int x;cin>>x;
       if(x>maxn) { cout<<i<<endl; return 0;}
       if(x>=maxn) maxn=x+1;
   }
   cout<<"-1"<<endl;
   return 0;
}
```

---

