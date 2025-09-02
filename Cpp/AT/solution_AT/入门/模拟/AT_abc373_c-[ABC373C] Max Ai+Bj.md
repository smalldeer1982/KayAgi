# [ABC373C] Max Ai+Bj

## 题目描述

给定两个长度为 $N$ 的整数数列 $ A,B $。选择两个整数 $i,j(1 \le i,j \le n)$，使得 $a_i+b_j$ 的值最大。

## 说明/提示

- $ 1\ \leq\ N\ \leq\ 5\ \times\ 10^5 $
- $ |A_i|\ \leq\ 10^9\,(i=1,2,\dots,N) $
- $ |B_j|\ \leq\ 10^9\,(j=1,2,\dots,N) $
- 所有输入都是整数
 
#### 样例一解释

对于 $ (i,j)=(1,1),(1,2),(2,1),(2,2) $ 中所有 $ A_i+B_j $ 的値分别为 $ 2,-8,8,-2 $，所以 $ A_i+B_j $ 的最大值为 $ 8 $。

感谢 [hyl_____](https://www.luogu.com.cn/user/1035028) 。

## 样例 #1

### 输入

```
2
-1 5
3 -7```

### 输出

```
8```

## 样例 #2

### 输入

```
6
15 12 3 -13 -1 -19
7 17 -13 -10 18 4```

### 输出

```
33```

# 题解

## 作者：ikunTLE (赞：11)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc373_c)

### 思路

题目要求选择整数 $i,j$，使 $A_i+B_j$ 的值最大化，也就是要使 $A_i$ 最大且 $B_j$ 最大，即求序列 $A$ 的最大值与序列 $B$ 的最大值之和。

**注意事项**

- 序列 $A$ 和序列 $B$ 中的值可能为负数。

**AC CODE**

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){int x=0;char f=1,ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}

int main(){
	int n=read();
	int max_a=INT_MIN;
	for(int i=1;i<=n;++i)
		max_a=max(max_a,read());
	int max_b=INT_MIN;
	for(int i=1;i<=n;++i)
		max_b=max(max_b,read());
	printf("%d\n",max_a+max_b);
	return 0;
}
```

---

## 作者：xiaoke2021 (赞：3)

水。

---

用“打擂法”扫描 $a$ 和 $b$，再将最大值相加。


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a,b;
long long max1=-1e9-7,max2=-1e9-7;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
    	cin>>a;
    	max1=max(max1,a);
	}for(int i=1;i<=n;i++){
		cin>>b;
		max2=max(max2,b);
	}cout<<max1+max2;
	return 0;
}
```

---

## 作者：Imerance1018 (赞：3)

### Description

[传送门](https://atcoder.jp/contests/abc373/tasks/abc373_d)

### Solution

显然，对 $a$ 数组和 $b$ 数组分别取最大值再相加即可。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,a[N],b[N],smax=-1e15,ans=-1e15;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		smax=max(smax,a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		ans=max(ans,b[i]);
	}
	cout<<smax+ans;
	return 0;
}
`````

---

## 作者：zlqwq (赞：3)

我就是说，这题也太水了吧。

直接 $O(N)$ 处理一遍 $a$ 数组最大值。

然后 $O(N)$ 处理一遍 $b$ 数组最大值。

将两个数加起来即可。


```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#define int long long
#define debug cout << "zlqwq"
#define inf 1e18

using namespace std;
int n;
int ma = -2147483648,mb = -2147483648;
signed main() {
	cin >> n; 
	for(int i = 1;i <= n;++i) {
		int a;cin >> a;
		ma = max(ma,a);
	}
	for(int i = 1;i <= n;++i) {
		int b;cin >> b;
		mb = max(mb,b);
	}
	cout << ma + mb;
	return 0;
}
```

---

## 作者：hjyowl (赞：2)

###  题目大意

给定你两个序列，要求你求出从两个序列当中任意选择两个能得到和的最大值。

### 思路

很明显，把两边的最大的用来相加一定是最优的。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
int n,m;
int a[N],b[N];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++ ){
		cin >> a[i];
	}
	for (int i = 1; i <= n; i ++ ){
		cin >> b[i];
	}
	sort(a + 1,a + 1 + n);
	sort(b + 1,b + 1 + n);
	cout << a[n] + b[n];
	return 0;
}
```

---

## 作者：lanbing_e (赞：1)

这道题十分的简单，应该没有人做不出来吧。

思路就是把两个数组遍历一遍，找出两个数组的最大值相加就行。

接下来就上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,max1=-1e9,max2=-1e9;
int main()
{
	cin>>n;
    for(int i=0;i<n;i++)
    {
    	cin>>a;
    	if(a>max1) max1=a;
	}
	for(int i=0;i<n;i++)
    {
    	cin>>a;
    	if(a>max2) max2=a;
	}
	cout<<max1+max2;
    return 0;
}
```

---

## 作者：sherry_lover (赞：0)

# AT_abc373_c [ABC373C] Max Ai+Bj 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc373_c)

## 思路
想要让两个数的和最大，就要让这两个数取最大值。找出两个数组的最大值相加即可，注意是 $|A_i| \le 10^9$，所以最小值的变量初始值要设成 $-10^9$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m = -1e9-7,mm = -1e9-7,x;
int main()
{
	cin >> n;
	for(int i = 1;i <= n;i++)
	{
		cin >> x;
		m = max(m,x);
	}
	for(int i = 1;i <= n;i++)
	{
		cin >> x;
		mm = max(mm,x);
	}
	cout << m+mm;
	return 0;
}
```

---

## 作者：lilong (赞：0)

### 题意

给定两个长度为 $N$ 的序列 $A,B$，求 $A_i+B_j(1 \le i,j \le N)$ 的最大值。

$1 \le N \le 5 \times 10^5,1 \le \left| A_i\right|,\left| B_j\right| \le 10^9$。

### 解法

显然有 $\max (A_i+B_j)=\max A_i + \max B_j(1 \le i,j \le N)$，因此对 $A,B$ 序列分别求最大值，相加即为答案。

时间复杂度 $O(n)$，实现时可以将第一个数直接作为最大值，避免初始化的问题。


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#define int long long

using namespace std;

int n,mx1,mx2,a;

signed main()
{
	cin >> n;
	cin >> mx1;
	for( int i = 2 ; i <= n ; i ++ )
	{
		cin >> a;
		mx1 = max( mx1 , a );
	}
	cin >> mx2;
	for( int i = 2 ; i <= n ; i ++ )
	{
		cin >> a;
		mx2 = max( mx2 , a );
	}
	cout << mx1 + mx2;
	return 0;
}
```

---

## 作者：wuyouawa (赞：0)

这是一篇 python 题解。

### 题目大意

给一个整数 $N$，和两个长度为 $N$ 的序列 $A$ 和 $B$，求 $A$ 中的最大值与 $B$ 中的最大值相加的结果。

### 思路

这题由于数据太大，要用高精，但 python 自带高精，所以 python 代码很简洁。直接模拟求最大值再相加即可。

### CODE

```python
def main():
 # 读入N
 n=int(input())
 # 下面两行读入序列A并找最大值
 a=list(map(int,input().split()))
 ma=max(a)
 # 下面两行读入序列B并找最大值
 b=list(map(int,input().split()))
 mb=max(b)
 # 输出相加的结果，python自带高精
 print(ma+mb)

if __name__=="__main__":
 main()
```

---

## 作者：zjj2024 (赞：0)

### 思路
猜测 $A$ 中的最大值加 $B$ 中的最大值为答案最大值。

考虑证明。

使用反证法。

如果 $A$ 中最大值为 $x$，$B$ 中最大值为 $y$，实际最优值为 $x'$ 和 $y'$，且 $x'<x$ 或 $y'<y$。

则将小的值变大答案也将变大，与 $x'+y'>x+y$ 矛盾，故 $x+y$ 为最大。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+14;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,x,y,a=-1e9,b=-1e9;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		a=max(x,a);//最大值
	}
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		b=max(b,x);
	}
	cout<<a+b<<'\n';
	return 0;
}
```

---

## 作者：hyl_____ (赞：0)

## Part 0 前言
好水。
## Part 1 思路
用两个变量找出 $A$ 和 $B$ 中最大的两数即可，最后输出和。
## Part 2 AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,b;
	cin>>n;
	long long max1=-1e9,max2=-1e9;//初始化
	for(int i=1;i<=n;i++){
		cin>>b;
		max1=max(max1,b);
	}
	for(int i=1;i<=n;i++){
		cin>>b;
		max2=max(max2,b);
	}
	cout<<max1+max2;
	return 0;
}
```

---

## 作者：__galaxy_1202__ (赞：0)

## 解题思路：
最水 C 题，没有之一，枚举出两个序列中的最大值，求和即可。
## CODE：

```cpp
#include <iostream>
using namespace std;
long long n, a, b, ma = -1e18, mb = -1e18;
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a;
        ma = max(ma, a);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b;
        mb = max(mb, b);
    }
    cout << ma + mb;
    return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

这是自我打 ABC 以来最简单的一道 C。

贪心。找出 $A,B$ 两数组中的最大值，并输出他们的和。
核心代码如下：
```cpp
inline void Solve(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a,ma=max(ma,a);
	for(int i=1;i<=n;i++)cin>>b,mb=max(mb,b);
	cout<<ma+mb;
}
```
**你以为写到这里就结束了？**

不可能。这篇题解还将教会你一种奇葩的求数组最值法，让你~~在同学面前装逼~~更深刻地理解递归。

对，你没听错，递归。每次将数列分成前后两部分直到区间长度为 $1$。每次操作都返回区间最大值。时间复杂度 $O(N+\log N)$。

```cpp
int dfs(int l,int r){
    if(l==r)return a[l];
    int mid=l+(r-l)/2;
    return max(dfs(l,mid),dfs(mid+1,r));
}
```

这种做法还可以扩展到求区间最大公约数等满足结合律的操作。~~其实除了给 CCF 出阅读理解以外没什么用。~~

[正解代码](https://atcoder.jp/contests/abc373/submissions/58197959)

---

## 作者：zhangzirui66 (赞：0)

其实没有 C 题难度。

直接找出两个数组中分别的最大数即可，最后相加。

注意有负数，要将最大值初始化为极小值。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[500005], b[500005], amax = -2e9, bmax = -2e9;
int main(){
	cin >> n;
	for(int i = 1; i <= n; i ++) cin >> a[i], amax = max(amax, a[i]);
	for(int i = 1; i <= n; i ++) cin >> b[i], bmax = max(bmax, b[i]);
	cout << amax + bmax;
	return 0;
}
```

---

## 作者：Your_Name (赞：0)

## 题意
在 $A$ 和 $B$ 中找两个数，使得他们的和最大。
## 思路
考虑贪心，只要分别找到 $A$ 与 $B$ 中的最大值然后相加就是答案，正确性显然。

建议评红。
## AC_Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = -1e9 - 10;//有可能最小值为负
int n, mxa = N, mxb = N;
int main(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        int x;
        cin >> x;
        mxa = max(mxa, x);
    }
    for(int i = 1; i <= n; i ++){
        int x;
        cin >> x;
        mxb = max(mxb, x);
    }
    cout << mxa + mxb;
    return 0;
}
```

---

## 作者：CSP_SAKME (赞：0)

贪心策略，选择两个数组中最大的数，再相加。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,a[500001],b[500001];
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) cin >> b[i];
    sort(b+1,b+n+1);
    cout << a[n]+b[n] << endl;
    return 0;
}
```

---

