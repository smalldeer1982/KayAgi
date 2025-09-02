# 『GROI-R2』 紫水晶

## 题目描述

爱丽丝不曾忘记过她曾经存在于纸牌的世界。

于是魔法让她的手里出现了一些牌，同时魔法也让坦尼尔手里出现了一些牌，而且每张牌上都写着一个正整数——尽管他们如今所处的，是玻璃王国的世界中。

牌张很快一消而散，而他们也准备启程。爱丽丝只记住了每相邻两张牌的**最大公约数之和**，坦尼尔只记住了每相邻两张牌的**最小公倍数之和**。

你还在这个宫殿里，你想重现当时的牌张。

**形式化题面**

给定 $q$ 次询问，每次询问为以下两种之一：

- ``1 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$。

- ``2 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$。

且对于任意输出的 $a_i$ 不应超出 C++ 语言中 ``int`` 的存储范围。

其中 $\gcd$ 和 $\operatorname{lcm}$ 分别为最大公约数和最小公倍数，如有多解，输出任意一个即可。如果无解，输出 ``-1``。

## 说明/提示

**数据范围**

**本题采用捆绑测试**。

| $\text{Subtask}$ | $\sum n\le$ | $x\le$ | 特殊性质 | 分值 |
| :-----------: | :-----------: | :-----------: | :-----------: | :-----------: |
| $1$ | $5$ | $10$ | | $10$ |
| $2$ | $50$ | $200$ | | $20$ |
| $3$ | $5\times 10^5$ | $2^{31}-1$ | $\text{A}$ | $15$ |
| $4$ | $5\times 10^5$ | $2^{31}-1$ | $\text{B}$ | $15$ |
| $5$ | $5\times 10^5$ | $2^{31}-1$ | | $40$ |

特殊性质 $\text{A}$：保证对于任意询问满足 $op=1$。

特殊性质 $\text{B}$：保证对于任意询问满足 $op=2$。

对于 $100\%$ 的数据满足 $2\le n\le 5\times 10^5$，$2\le \sum n\le 5\times 10^5$，$1\le x \le 2^{31}-1$，$op\in\{1,2\}$。


## 样例 #1

### 输入

```
5
1 5 4
2 3 8
1 5 10
2 6 34
1 3 1```

### 输出

```
1 1 1 1 1
2 2 3
1 1 1 7 7
1 1 4 5 1 4
-1```

# 题解

## 作者：RJSPZ (赞：4)

读题，第一反应构造。

情况一：

$ n $ 个数的最大公约数之和为 $ x $。

显然，构造 $ n-2 $ 个 1，2 个 $ x-n+2 $，最大公约数之和为 $ n-2+x-n+2=x $。

情况二：

$ n $ 个数的最小公倍数之和为 $ x $。

显然，构造 $ n-2 $ 个 1，1 个 $ x-n+2 $，最小公倍数之和为 $ n-2+x-n+2=x $。

Code:
```cpp
#include<cstdio>
using namespace std;
const int N=5e5+7;
int T,a[N];
signed main(){
	scanf("%d",&T);
	while(T--){
		int op,n,x;
		scanf("%d%d%d",&op,&n,&x);
		if(op==1){
			int num=x-n+2;
			if(num<=0){
				putchar('-'),putchar('1');
				goto print;
			}
			for(int i=1;i<=n-2;i++){
				putchar('1'),putchar(' ');
			}
			for(int i=n-1;i<=n;i++){
				printf("%d ",num);
			}
		}
		else{
			int num=x-n+2;
			if(num<=0){
				putchar('-'),putchar('1');
				goto print;
			}
			for(int i=1;i<=n-1;i++){
				putchar('1'),putchar(' ');
			}
			printf("%d",num);
		}
		print:
			putchar('\n');
	}
	return 0;
}
```

---

## 作者：myyyIisq2R (赞：3)

## [P9652紫水晶](https://www.luogu.com.cn/problem/P9652)
# Solution
观察数据，当 $op$ 取 $1$ 时，样例输出的前几位全是 $1$，可以提供思路：

### 最大公因数的情况：
令输出序列的前 $n-2$ 位全部为 $1$，最后两位待定。此时为满足累加和为 $q$，序列的前 $n-2$ 位的已累加和为 $n+3$ 仍需要 $q-n-3$ ，那么我们令最后两位的值相等可为累加和贡献 $1$，那么该为取值的贡献只需要为 $q-n-2$，又因为前一个数是 $1$，则后两位相等的数只需取 $q-n-2$ 就可满足题目要求。需要特判的是 $q-n-2$ 应该大于 $0$，否则输出 $-1$。

### 最小公倍数同理，详见代码

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int op,n,q;
		cin>>op>>n>>q;
		if(op == 1)
		{
			if(q-(n-2) <=  0) puts("-1");
			else
			{
				for(int i{1};i<n-1;i++)
					cout<<1<<" ";
				cout<<q-(n-2)<<" "<<q-(n-2)<<endl;
			}
         //5 4
			// 1 1 1 2 2
		}
		else
		{
			if(q-n+2<=0) 
			{
				puts("-1");
				continue;
			}
			for(int i{1};i<n;i++)
			{
				cout<<1<<" ";
			}
			cout<<q-n+2<<endl;
			
			
		}
	}
}
```

---

## 作者：_O_v_O_ (赞：1)

月赛签到题。

先放结论：

- 如果 $x<n-1$，输出 $-1$。
- 如果 $x\ge n-1$ 并且 $op=1$，则输出 $1{,}1{,}1{,}\cdots{,}1{,}x-n+2{,}x-n+2$，其中 $1$ 有 $n-2$ 个。
- 如果 $x\ge n-1$ 并且 $op=2$，则输出 $1{,}1{,}1{,}\cdots{,}1{,}x-n+2$ 其中 $1$ 有 $n-1$ 个。

证明：

- 对于输出 $-1$ 的情况：因为 $a$ 的相邻 $\gcd$ 和相邻 $\operatorname{lcm}$ 有 $n-1$ 项，而这 $n-1$ 项至少全是 $1$，加起来至少是 $n-1$，所以如果 $x<n-1$，输出 $-1$。
- 对于 $x\ge n-1$ 并且 $op=1$：因为构造出来的数组相邻 $\gcd$ 分别为：$1{,}1{,}1{,}\cdots{,}1{,}x-n+2$ 其中 $1$ 有 $n-2$ 个，它们加起来刚好是 $x$。
- 对于 $x\ge n-1$ 并且 $op=1$：因为构造出来的数组相邻 $\operatorname{lcm}$ 分别为：$1{,}1{,}1{,}\cdots{,}1{,}x-n+2$ 其中 $1$ 有 $n-2$ 个，它们加起来刚好也是 $x$。

代码：

```
#include<bits/stdc++.h>
using namespace std;

int T,op,n,x;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin>>T;
	while(T--){
		cin>>op>>n>>x;
		if(x<n-1){
			puts("-1");
			continue;
		}
		if(op==1){
			for(int i=1;i<n-1;i++){
				cout<<1<<' ';
			}
			cout<<x-n+2<<' '<<x-n+2<<endl;
		}
		if(op==2){
			for(int i=1;i<n;i++){
				cout<<1<<' ';
			}
			cout<<x-n+2<<endl;
		}
	}
	return 0;
}
```


---

## 作者：Moon_Wind (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9652)



------------

**题意简述**：

给定 $op,x,n$。

- $op=1$ 时，构造一个长度为 $n$ 的序列，使 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$。
- $op=2$ 时，构造一个长度为 $n$ 的序列，使 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$。

**算法分析**：

- 先解决 $op=1$ 时的构造问题。众所周知，$\gcd(1,1)=1$，$\gcd(x,x)=x$，考虑在序列的前 $n-2$ 个位置上放 $1$，然后在最后 $2$ 个位置上都放上 $x-n+2$，即可使 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$ 成立。

- $op=2$ 时的构造问题也大同小异。因为 $\operatorname{lcm}(1,1)=1$，$\operatorname{lcm}(1,x)=x$，考虑在序列的前 $n-1$ 个位置上放 $1$，然后在最后 $1$ 个位置上都放上 $x-n+2$，即可使 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$ 成立。

- 在 $x<n-1$ 时，无解。



**代码部分**：



------------
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	while(n--){
		int op,l,k;
		cin>>op>>l>>k;
		if(op==1&&k>=l-1){
			for(int i=1;i<l-1;i++) cout<<1<<' ';
			cout<<k-l+2<<' '<<k-l+2; 
		} //算gcd时。
		else if(op==2&&k>=l-1){
			for(int i=1;i<l;i++) cout<<1<<' ';
			cout<<k-l+2;
		} //算lcm时。
		else cout<<-1;//无解
		cout<<endl;
	} 
	return 0;
} 
```


------------


---

## 作者：Pink_Cut_Tree (赞：1)

# P9652 『GROI-R2』 紫水晶 题解

~~说句闲话：这题的输入样例怕是根据输出样例造的。~~

## 解法

我们分三部分解决：

### 1.`gcd`

我们将 $x$ 的最大公约数贡献分成两部分。

第一部分：前面的 $n-1$ 个数，全是 $1$；

第二部分：最后两个数的最大公约数，是最后的那个数，即 $x-n+2$。

所以我们可以这么做：

对于前面的前 $n-2$ 个数，输出 `1`。后面两个数，均输出 $x-n+2$ 即可。

正确性验证：

整个序列的最大公约数之和是 $1\times(n-2)+x-n+2=x$。符合要求。

### 2.`lcm`

类似地，我们将 $x$ 的最小公倍数贡献分成两部分。

第一部分：前面的 $n-1$ 个数，全是 $1$；

第二部分：最后两个数（$1$ 和最后的那个数）的最小公倍数，也是最后的那个数，即 $x-n+2$。

所以我们可以这么做：

对于前面的前 $n-1$ 个数，输出 `1`。最后一个数，输出 $x-n+2$ 即可。

正确性验证：

整个序列的最大公约数之和是 $1\times(n-2)+x-n+2=x$。符合要求。

### 3.`-1` 的输出

显而易见，每一个数都是正整数，如果 $n-x\geq2$（即哪怕每一个数都是 $1$，总和也会超），则输出 `-1`。

## 代码

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int Q;
int op,n,x;
bool flag;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin>>Q;
	while(Q--){
		cin>>op>>n>>x;
		if(n-x>=2){
			cout<<"-1\n"; continue;
		}
		if(op==1){
			for(int i=1;i<=n-2;i++){
				cout<<"1 ";
			}
			cout<<x-n+2<<" "<<x-n+2<<"\n";
		}
		else{
			for(int i=1;i<=n-1;i++){
				cout<<"1 ";
			}
			cout<<x-n+2<<"\n";
		}
	}
return 0;
}
```


---

## 作者：sbno333 (赞：1)

本题是一道构造题，思路如下：

对于最大公因数，前两个数可以赋值为 $s$，后面的数为 $1$，不难发现，此时的最大公因数的和为 $s+n-2$，此时我们只需要讨论 $s$ 的值即可。

由于 $n$ 确定，和确定，因此 $s$ 很好就能得出，如果 $s$ 小于等于 $0$，则无解。

对于最小公倍数之和，我们可以仅将第一个数赋值为 $s$，其他数为 $1$，此时的和仍为 $s+n-2$，$s\le0$ 则无解。

因此代码就出来了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000009];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		int o,n,x,s;
		cin>>o>>n>>x;
		s=x-(n-2);
		if(s<=0){
			cout<<-1<<endl;
		}else{
			int inn;//方便输出
			inn=1;
			cout<<s<<" ";
			if(o==1){//最大公因数要输出两个s
				inn++;
				cout<<s<<" "; 
			}
			for(int i=inn+1;i<=n;i++){//剩下的都是1
				cout<<"1 ";
			}
			cout<<endl;
		}
	}
	return 0;
} 
```

---

## 作者：lsj2009 (赞：1)

## Problem

一共 $q$ 次询问，每次为以下两种之一：

- ``1 n x`` 表示要求输出一长度为 $n$ 的正整数序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$。

- ``2 n x`` 表示要求输出一长度为 $n$ 的正整数序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$。

$\sum n\le 5\times 10^5,x\le 2^{31}-1$。

## Solution

构造题。

我们看到 $\gcd$ 和 $\operatorname{lcm}$ 考虑一个特殊的数字：$1$。

我们不妨考虑让绝大多数的 $\gcd(a_i,a_{i+1})$ 的 $\operatorname{lcm}(a_i,a_{i+1})$ 值均为 $1$。为什么这么想？因为哪怕我们堆了一堆 $1$，但是因为如果数据有解，所以当前的 $\gcd$ 或 $\operatorname{lcm}$ 必然不大于 $x$，我们还有继续填充数字的空间。

- 当 $op=1$ 时，我们不妨考虑令 $a_{1\sim n-2}$ 均为 $1$ 且 $a_{n-1}=a_n=x-n+2$。这样前 $n-1$ 个数两两之间 $\gcd$ 均为 $1$，这样子我们已经得到了 $\sum\limits_{i=1}^{n-2} \gcd(a_i,a_{i+1})=n-2$，然后我们要让 $\gcd(a_{n-1},a_n)=x-(n-2)$，显然的，令 $a_{n-1}=a_n=x-n+2$ 即可。

- 当 $op=2$ 时，本质上与 $op=1$ 的情况相同，但需要注意的是 $\operatorname{lcm}(1,v)=v$，所以我们要令 $a_{n-1}=1$，其余同上述一样。

至于无解的情况，显然是 $x<n-1$ 时。

## Code

```cpp
#include<bits/stdc++.h>
//#define int long long
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;

signed main() {
    int q;
    scanf("%d",&q);
    while(q--) {
        int op,n,x;
        scanf("%d%d%d",&op,&n,&x);
        if(x<n-1)
            puts("-1");
        else if(op==1) {
            rep(i,1,n-2)
                printf("%d ",1);
            printf("%d %d\n",x-n+2,x-n+2);
        } else {
            rep(i,1,n-1)
                printf("%d ",1);
            printf("%d\n",x-n+2);
        }
    }
    return 0;
}


```

---

## 作者：渡墨残殇 (赞：0)

对于这个题我要先说一句，不能被样例迷惑，因为决定这个题的关键只是再最后两个数而已。

另外很早之前有个月赛的题和这个很像都是要还原原来的数列。

[P 8278](https://www.luogu.com.cn/problem/P8278)

## 分析
其实这个题和最大公因数和最小公倍数关系不大，就只是需要两个概念即可。 

- $n$ 和 $n$ 的最大公因数是 $n$ 本身

- $n$ 和 $1$ 的最大公因数是 $1$,最小公倍数是 $n$


## 做法

1. $n\leq2$

输出两个 $x$ 即可。

2. $n\geq3$

- 最大公因数

把前面的全赋值为 $1$，前面的空全部为一堆 $1$ 加在一块，然后让最后两个空均输出 $sum-(n-2)$ 即可。

- 最小公倍数

一样，把前面的全赋值为 $1$，前面的空全部为一堆 $1$ 加在一块，最后只需要留出来一个空输出 $sum-(n-2)$ 即可。

另外当 $n-1\gt x$ 时，直接输出 $-1$，因为此时所有均为 $1$ 相加都不满足题意。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[5000100];
void Lcd(int l,int r,int sum)
{
  if(sum<r-1){cout<<"-1\n";return ;}
  if(r==2){
    cout<<sum<<" "<<sum<<"\n";return ;}
  int po=sum-(r-2);
  for(int i=1;i<=r-2;i++){
    cout<<1<<" ";
  }cout<<po<<" "<<po<<"\n";
}
void Lcm(int l,int r,int sum)
{
  if(sum<r-1){cout<<"-1\n";return ;}
  if(r==2){
    cout<<sum<<" "<<sum<<"\n";return ;}
  int po=sum-(r-2);
  for(int i=1;i<=r-1;i++){
    cout<<1<<" ";
  }cout<<po<<"\n";
}
int q;
int main ()
{
    cin>>q;
    while(q--)
    {
      int op,n,x;cin>>op>>n>>x;
      if(op==1)
      {
        Lcd(1,n,x);
      }
      else
      {
        Lcm(1,n,x);
      }
    }
}
```



---

## 作者：hhhppp (赞：0)

_一道构造题。_ 

## 简述题意

给定 $q$ 次询问，每次询问为以下两种之一：

- ``1 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$。

- ``2 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$。

## 思路

###  $op=1$ 的情况：

- #### 前置知识：$\gcd(1,a)=1,\gcd(a,a)=a$。
先把前面的 $n-2$ 个数都赋值为 $1$，那么此时我们得到的值为 $n-2$，要使得值为 $x$，还差 $x-(n-2)$，因为 $\gcd(a,a)=a$，所以直接输出**两个** $x-(n-2)$即可。

###  $op=2$ 的情况：

- #### 前置知识：$\operatorname{lcm}(1,1)=1,\operatorname{lcm}(1,a)=a$。
先把前面的 $n-2$个数都赋值为1，那么此时我们得到的值为 $n-2$，要使得值为 $x$，还差 $x-(n-2)$，因为 $\operatorname{lcm}(1,a)=a$，所以直接输出**一个** $x-(n-2)$ 即可。

### 无解的情况：

题目要求是**正整数**，所以如果 $x-(n-2)$ 为负数时，直接输出 $-1$。

## _那么，理论存在，实践开始。_ 


## 代码实现

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int op,n,x;
		cin>>op>>n>>x;
		if(x-(n-2)<0){//无解的情况 
			cout<<-1<<endl;
			continue;
		}
		if(op==1){//op==1的情况 
			for(int i=0;i<n-2;i++){
				cout<<1<<' ';
			}
			cout<<x-(n-2)<<' '<<x-(n-2)<<endl;//直接输出两个x-(n-2)
		}
		if(op==2){//op==2的情况 
			for(int i=0;i<n-1;i++){
				cout<<1<<' ';
			}
			cout<<x-(n-2)<<endl;//直接输出一个x-(n-2)
		}
	}
	return 0;//完美结束QAQ 
}
```
比赛的时候只想出了 $op=1$ 的情况，后来补题才 AC 的。。。

---

## 作者：WhitD (赞：0)

## 思路
考虑 $\gcd$ 的性质：$\gcd(1,x)=1,\gcd(x,x)=x$。

先考虑 $op=1$ 的情况：既然要让相邻两个数的 $\gcd$ 和为 $x$，假设序列长度为 $n$，我们不妨让序列的第 $1$ 到 $n-2$ 项都为 $1$，此时总和为 $n-3$（注意，虽然有 $n-2$ 个数，但是我们的求和是相邻两数的，因此总和为 $n-3$，下同）。由于我们第 $n-2$ 项为 $1$，因此第 $n-1$ 项不论赋什么，$\gcd$ 依然是 $1$（总和便是 $n-2$），因为我们要让总和为 $x$，因此只要将第 $n-1$ 项和第 $n$ 项赋为 $x-(n-2)=x-n+2$ 即可。

考虑 $\operatorname{lcm}$ 的性质：$\operatorname{lcm}(1,x)=x$。

再看 $op=2$ 的情况：为了方便，我们依然可以让序列的第 $1$ 到 $n-1$ 项都为 $1$，此时总和为 $n-2$，因为我们要让总和为 $x$，（第 $n-1$ 项为 $1$）因此只要将第 $n$ 项赋值为 $x-(n-2)=x-n+2$ 即可。

无解很好判断，若上述赋值过程中出现非正数直接输出 $-1$ 就可。
## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,op,n,x;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>op>>n>>x;
		if(op==1)
		{
			if(x<n-1)
			{
				cout<<-1<<endl;
				continue;
			}
			for(int i=1;i<n-1;i++)
				cout<<1<<" ";
			cout<<x-n+2<<" "<<x-n+2<<endl;
		}
		else
		{
		    if(x-n+2<=0)
		    {
				cout<<-1<<endl;
				continue;
		    }
			for(int i=1;i<n;i++)
				cout<<1<<" ";
			cout<<x-n+2<<endl;
		}
	}
	return 0;
}
```


---

## 作者：JimmyDong (赞：0)

一看就是构造题。

## 思路
- 对于第一种询问，可以构造数列：

$$x-n+2,x-n+2,\begin{matrix}\underbrace{1+1+\cdots+1}\\n-2\end{matrix}$$

- 对于第二种询问，可以构造数列：

$$x-n+2,\begin{matrix}\underbrace{1+1+\cdots+1}\\n-1\end{matrix}$$

---

## 作者：SakurajiamaMai (赞：0)

## 思路:
既然题目要求最大公约数和最小公倍数，可以考虑这种情况，对于最小公倍数， $1$ 和随便一个不是 $1$ 的整数的最小公倍数是那个整数，所以我们可以把前 $n-1$ 个数设成 $1$，然后最后一个数自然而然地为 $m-(n-2)$。对于最大公约数，可以考虑前 $n-2$ 个为 $1$ ，然后最后两个数字为同一个数，原理与最小公倍数相同。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],n,m,t,op;
void solve()
{
    cin>>op>>n>>m;
    if(n-2>=m) return cout<<-1<<endl,void();
    if(op==1){
        for(int i=1;i<=n-2;i++) cout<<1<<' ';
        cout<<(m-(n-2))<<' '<<(m-(n-2))<<endl;
    }
    if(op==2){
        for(int i=1;i<=n-1;i++) cout<<1<<' ';
        cout<<(m-(n-2))<<endl;
    }
}
int main()
{
    cin>>t;
    while(t--) solve();
}
```


---

## 作者：icypenguin (赞：0)

### 题目简述

给定 $q$ 次询问，每次询问为以下两种之一：

- ``1 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \gcd(a_i,a_{i+1})=x$。

- ``2 n x`` 表示要求输出一长度为 $n$ 的**正整数**序列 $\{a_n\}$，使得 $\sum\limits_{i=1}^{n-1} \operatorname{lcm}(a_i,a_{i+1})=x$。

且对于任意输出的 $a_i$ 不应超出 C++ 语言中 ``int`` 的存储范围。

其中 $\gcd$ 和 $\operatorname{lcm}$ 分别为最大公约数和最小公倍数，如有多解，输出任意一个即可。如果无解，输出 ``-1``。

### 题目分析

先考虑操作 $1$，我们很容易考虑到一种构造方案，令 $a_1 = a_2 = \dots = a_{n - 2} = 1$，显然，前面这 $n - 2$ 个数字贡献的 $\gcd$ 为 $n - 3$。另外，因为 $a_{n - 2} = 1$，所以无论 $a_{n - 1}$ 是哪个正整数，$\gcd(a_{n - 2},a_{n - 1}) = 1$。那么，前面这 $n - 1$ 个数字贡献的 $\gcd$ 为 $n - 2$。我们知道，$\gcd(d, d) = d$，所以，我们考虑构造相同的 $a_{n - 1}$ 和 $a_n$，很明显，现在还剩余 $x - (n - 2)$ 个 $\gcd$ 需要给出，也就是 $x - n + 2$，所以令 $a_{n - 1} = a_n = x - n + 2$。当然，如果 $a_{n - 1} \leq 0$，则不是正整数序列，不满足题目要求，输出 $-1$。

再考虑操作 $2$，也是很容易考虑到一种构造方案，令 $a_1 = a_2 = \dots = a_{n - 1} = 1$，很明显，$\operatorname{lcm}(1, 1) = 1$，所以前 $n - 1$ 个数字贡献的 $\operatorname{lcm}$ 为 $n - 2$，很明显，现在还剩余 $x - (n - 2)$ 个 $\operatorname{lcm}$ 需要给出，也就是 $x - n + 2$，我们又知道 $\operatorname{lcm}(1, d) = d$，所以令 $a_n = x - n + 2$ 即可。当然，如果 $a_n \leq 0$，则不是正整数序列，不满足题目要求，输出 $-1$。

### 代码实现

```cpp
#include <iostream>
#include <queue>
#include <map>
#define mod 1000000007
#define ll long long
using namespace std;
ll T, a[1000005];
int main(){
    cin >> T;
    while (T--){
        ll op, n, x;
        cin >> op >> n >> x;
        if (op == 1){
            for (ll i = 1; i <= n - 2; i++){
                a[i] = 1;
            }
            a[n - 1] = x - n + 2;
            a[n] = a[n - 1];
            if (a[n] <= 0){
                cout << -1 << endl;
            }else{
                for (ll i = 1; i <= n; i++){
                    cout << a[i] << " ";
                }
                cout << endl;
            }
        }else{
            for (ll i = 1; i <= n - 1; i++){
                a[i] = 1;
            }
            a[n] = x - n + 2;
            if (a[n] <= 0){
                cout << -1 << endl;
            }else{
                for (ll i = 1; i <= n; i++){
                    cout << a[i] << " ";
                }
                cout << endl;
            }
        }
    }
    return 0;
}
```





---

## 作者：哈哈人生 (赞：0)

### 题外话
这题思路很简单，其实没有什么好说的。

### 思路
其实我们可以通过 $1$ 和其他数字凑出 $x$。求最大公倍数的情况先输出 $n-1$ 个 $1$ 凑数，因为 $1$ 和 $1$ 的最大公倍数是 $1$，所以再直接输出一个数字 $x-n+2$ 即可。求最小公因数类似于上面这种情况，不过要注意，先输出的是 $n-2$ 个数凑数了，此外仿照第一种情况即可。无解的情况判断也好理解：只要 $x$ 小于 $n-1$，即上面这样凑都超过了答案，就是无解。

### 代码
非常简单。
```
#include<bits/stdc++.h>

using namespace std;

int q,op,n,x;

void s1(){//第一种情况

	if(n-1>x){

		cout<<"-1\n";

		return;

	}

	else{

		for(int i=1;i<=n-2;i++){

			cout<<1<<" ",x--;

		}

		cout<<x<<" "<<x<<endl;

	}

}

void s2(){//第二种情况

	if(n-1>x){

		cout<<"-1\n";

		return;

	}

	for(int i=1;i<n;i++)cout<<1<<" ",x--;

	cout<<x+1<<endl;

}

int main(){

	cin>>q;

	while(q--){

		cin>>op>>n>>x;

		if(op==1)s1();

		else s2();

	}

	return 0;

}
```
站长曾经说过，不抄袭题解代码，只借鉴题解思路，但应该给题解点个赞。

---

## 作者：tder (赞：0)

[$\Large\color{black}\textbf{P9652 『GROI-R2』 紫水晶}$](https://www.luogu.com.cn/problem/P9652) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/P9652)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-P9652)

~~第一次写月赛题解嗷吼 qwq（大声的显示我的无知）~~

~~简简单单的构造题~~

---

$$\large\textbf{思路}$$

看到 $\gcd$ 和 $\operatorname{lcm}$ 的构造题马上考虑最特殊的 $1$！

众所周知，对于 $\forall\ a\in\mathbb N_+$，有 $\gcd(1,a)=1$，可以简单粗暴的构造 $n-2$ 个 $1$，它们的最大公约数的和就是 $\sum_{i=1}^{n-2}\gcd(a_i,a_{i+1})=\sum_{i=1}^{n-2}\gcd(1,1)=n-2$，则 $\gcd(a_{n-1},a_n)=x-(n-2)$。又因为 $\gcd(a,a)=a$，后面两个数均为 $x-(n-2)$ 即可。

同理，当 $op=2$ 时，对于 $\forall\ a\in\mathbb N_+$，有 $\operatorname{lcm}(1,a)=a$，此时构造 $n-1$ 个 $1$，其最小公倍数之和即 $\sum_{i=1}^{n-2}\operatorname{lcm}(a_i,a_{i+1})=\sum_{i=1}^{n-2}\operatorname{lcm}(1,1)=n-2$。所以最后一个数为 $x-(n-2)$ 即可，使得 $\operatorname{lcm}(a_{n-1},a_n)=\operatorname{lcm}(1,x-(n-2))=x-(n-2)$。

**特别的，当 $x-(n-2)\le0$ 时无解。**

简单证明，第二种同理：

$\text{令对于 }\forall\ i\in[1,n-2],a_i=1$

$\text{则 }\sum_{i=1}^{n-3}\gcd(a_i,a_{i+1})=\sum_{i=1}^{n-3}\gcd(1,1)=n-3$

$\therefore\sum_{i=n-2}^{n}\gcd(a_i,a_{i+1})=\gcd(a_{n-2},a_{n-1})+\gcd(a_{n-1},a_n)=x-(n-3)$

$\therefore\gcd(a_{n-1},a_n)=\sum_{i=n-2}^{n}\gcd(a_i,a_{i+1})-\gcd(a_{n-2},a_{n-1})=x-(n-3)-1=x-n+2$

$\text{又 }\gcd(x-(n-2),x-(n-2))=x-(n-2)$

$\therefore\text{当 }a_{n-1}=a_n=x-(n-2)\text{ 时，}$

$\text{有 }\sum_{i=1}^{n-1}\gcd(a_{i+1},a_i)=\sum_{i=1}^{n-3}\gcd(1,1)+\gcd(1,x-(n-2))+\gcd(x-(n-2),x-(n-2))=x$

$\therefore\text{满足条件，证毕}$

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long // DILL 万岁！（其实可以不用）
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t;
	cin>>t;
	while(t--) { // t 组数据
		int op, n, x;
		cin>>op>>n>>x;
		if(op == 1) { // 第一种情况
			if(x <= n - 2) { // 特判无解
				cout<<-1<<endl;
				continue;
			}
			for(int i = 1; i <= n - 2; i++) cout<<1<<" ";
			// 构造 n - 2 个 1
			cout<<x - (n - 2)<<" "<<x - (n - 2)<<endl; // 最后两个 x - (n - 2)
		} else {
			if(x <= n - 2) {
				cout<<-1<<endl;
				continue;
			}
			for(int i = 1; i <= n - 1; i++) cout<<1<<" "; // 构造 n - 1 个 1
			cout<<x - (n - 2)<<endl; // 最后一个 x - (n - 2)
		}
	} 
	return 0;
}

```

---

## 作者：Clarinet (赞：0)

对于我这种比赛时只做出一题的蒟蒻，也就只能写写第一题的题解来攒点咕值了……
# 简要题意
给出 $q$ 次询问，每次给出三个正整数 $op$，$n$，$x$，分别代表类型、牌的张数和和。其中当 $op=1$ 时 $x$ 表示相邻两数间**最大公因数**的和，当 $op=2$ 时表示相邻两数间**最小公因数**的和。求还原后的数组。
# 分析
首先看到 Special Judge，这道题就十拿九稳地要往极端方向思考了。即然给出了和，那不妨我们就让前面所有的牌都为 1，然后在最后再补齐需要的和。然后众所周知 1 和任何数的最大公因数都为 1，但是 1 和任何数的最小公倍数都为这个数，所以当 $op=1$ 时需要输出两个非零的数，反之则需要一个。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,op,n,x;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>op>>n>>x;
		if(x<n-1){
			cout<<-1<<endl;
			continue;
		}
		if(op==1){
			for(int j=1;j<n-1;j++)cout<<"1 ";
			cout<<x-(n-2)<<" "<<x-(n-2)<<endl;
		}
		else{
			for(int j=1;j<n;j++)cout<<"1 ";
			cout<<x-(n-2)<<endl;
		}
	}
	return 0;
}
```
感谢阅读！

---

