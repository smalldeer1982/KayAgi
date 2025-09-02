# Reverse

## 题目描述

You are given a permutation $ p_1, p_2, \ldots, p_n $ of length $ n $ . You have to choose two integers $ l,r $ ( $ 1 \le l \le r \le n $ ) and reverse the subsegment $ [l,r] $ of the permutation. The permutation will become $ p_1,p_2, \dots, p_{l-1},p_r,p_{r-1}, \dots, p_l,p_{r+1},p_{r+2}, \dots ,p_n $ .

Find the lexicographically smallest permutation that can be obtained by performing exactly one reverse operation on the initial permutation.

Note that for two distinct permutations of equal length $ a $ and $ b $ , $ a $ is lexicographically smaller than $ b $ if at the first position they differ, $ a $ has the smaller element.

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

In the first test case, the permutation has length $ 1 $ , so the only possible segment is $ [1,1] $ . The resulting permutation is $ [1] $ .

In the second test case, we can obtain the identity permutation by reversing the segment $ [1,2] $ . The resulting permutation is $ [1,2,3] $ .

In the third test case, the best possible segment is $ [2,3] $ . The resulting permutation is $ [1,2,4,3] $ .

In the fourth test case, there is no lexicographically smaller permutation, so we can leave it unchanged by choosing the segment $ [1,1] $ . The resulting permutation is $ [1,2,3,4,5] $ .

## 样例 #1

### 输入

```
4
1
1
3
2 1 3
4
1 4 2 3
5
1 2 3 4 5```

### 输出

```
1 
1 2 3 
1 2 4 3 
1 2 3 4 5```

# 题解

## 作者：8atemak1r (赞：5)

## Description

已知 $1$ ～ $n$ 的一个排列 $a$，你可以选择它的一个非空子序列将其翻转，求正好翻转一次后可以得到的字典序最小的 $1$ ～ $n$ 的排列。

$t$ 组数据。





## Solution

先给思路：从 $1$ ～ $n$ 遍历这个排列，如果位置 $i$ 上的数非 $i$， 则跳出循环，将 $i$ 作为子序列的开头，将数 $i$ 所在的位置 $j$ 作为子序列的结尾。



**正确性证明：**

首先我们要证明对于每一个位置 $i$ 上的数非 $i$ 的情况，数 $i$ 都在位置 $i$ 的后面。

此证明非常简单：若数 $i$ 不在位置 $i$ 的后面，由于位置 $i$ 上的数非 $i$，所以数 $i$ 一定在位置 $i$ 的前面，也就是说存在 $j$ 使得 $a_j ≠ j$ 且 $j < i$，所以遍历的时候先遇到了位置 $j$ 上的数非 $j$，这时我们已经跳出了循环。

接下来，我们就要证明这个贪心的正确性了，其实也不难，由于  $1$ ～ $n$ 的排列中最小的是 $1,2,3,\dots,n$，而显然我们跳出循环前，数列里的数为 $1,2,3,\dots,i - 1$，且在位置 $i$ 上的数 $j$ 大于 $i$。接下来考虑两种不采取刚才策略的策略：

1. 不将位置 $i$ 作为子序列的开头。则位置 $i$ 上的数 $j$ 大于 $i$，由于在采取刚才的策略之后，位置 $i$ 上的数为 $i$，所以刚才的策略相较于这种策略来说更优。

2. 将位置 $i$ 作为子序列的开头，但是不将数 $i$ 所在的位置 $j$ 作为子序列的结尾。则由于 $1$ ～ $i - 1$ 的数已出现过，则剩下的数均大于等于 $i$，所以这种情况位置 $i$ 上的数 $j$ 同样大于 $i$，劣于刚才的策略。

由于除了这三种策略囊括了所有的情况，故证毕。



## Summary

贪心重要的不是结论，而是证明过程，这里使用了一种叫 **exchange argument** 的证明思想，即证明在任何时候换一个决策都不会有更好的结果，许多的贪心题目都可以用这种思路证明，希望读者多多思考。



---

## 作者：Engulf (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1638A)

[更好的阅读体验](https://www.luogu.com.cn/blog/t-m-j-y-h-0-9/solution-cf1638a)

## 题意简述

给定一个长度 $n$ 的排列 $p_1\sim p_n$，可反转 $p_l\sim p_r(l,r\in [1,n])$，求一次反转后字典序最小的排列。

## 分析

分类讨论 $p_i$ 的情况：

### 1. $p_i= i$

这种情况的话，字典序已是最小，不需要反转它，不用考虑。

### 2. $p_i\neq i$

上面说道，$p_i=i$ 的情况字典序已是最小，所以直接往后暴力查询等于 $i$ 的元素下标 $j$，反转 $[i,j]$ 即可。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch))f^=!(ch^45),ch=getchar();
    while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return f?-x:x;
}
inline void write(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

int T;
int a[505],n;

int main(){
    T=read();
    while(T--){
        n=read();
        for(int i=1;i<=n;i++)a[i]=read();
        int x,y,v;
        for(int i=1;i<=n;i++){
            if(a[i]!=i){
                for(int j=i+1;j<=n;j++){
                    if(a[j]==i){
                        reverse(a+i,a+j+1);
                        goto pre;
                    }
                }
            }
        }
        pre:
        for(int i=1;i<=n;i++)write(a[i]),putchar(' ');
        puts("");
    }
    system("pause");
}
```

---

## 作者：郑朝曦zzx (赞：2)

[CF1638A翻译](https://www.luogu.com.cn/discuss/409966)

# 一 解题思路
**预处理：**

对于每一小问，输入的排列，记录下每个数字出现在那里（输入时即可预处理）。
```cpp
for (int i = 1; i <= n; ++i)
{
    scanf("%d", &num[i]);
    pos[num[i]] = i;
}
```
**枚举：**

判断要从哪位到哪位翻转。
```cpp
for (int i = 1; i <= n; ++i)
{
    if (num[i] != i)
    {
	
        break;
    }
}
```
**翻转：**
```cpp
reverse(num + i, num + pos[i] + 1);
//stl函数，所用头文件：#include <algorithm>
//功能：将第 i 位到第 pos[i] 位翻转
```
# 二 参考代码：
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int t;
void solve()
{
	int n;
	int num[510], pos[510];
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &num[i]);
		pos[num[i]] = i;
	}
	for (int i = 1; i <= n; ++i)
	{
		if (num[i] != i)
		{
			reverse(num + i, num + pos[i] + 1);
			break;
		}
	}
	for (int i = 1; i <= n; ++i)
		printf("%d ", num[i]);
	printf("\n");
}
int main()
{
	scanf("%d", &t);
	for (int i = 1; i <= t; ++i)
		solve();
	return 0;
}
```


---

## 作者：Galois_Field_1048576 (赞：2)

因为你只可以翻转一次，所以观察字典序性质发现数字越在前面字典序的影响越大，所以考虑将第一个不是错位的数字翻转过来。  
具体地，让 $i$ 在 $1\sim n$ 遍历，如果 $a_i \ne i$ 则找到一个 $j$ 使得 $a_j = i$， 将 $[i,j]$ 区间翻转，然后退出循环。  
时间复杂度 $\Theta(Tn)$。
```cpp
/*
 * @Date: 2022-02-14 22:37:54
 * @LastEditors: 1048576
 * @FilePath: \code\CF1638A.cpp
 * @MajorAlgorithm:
 */
#include <bits/stdc++.h>
using namespace std;
int t, n, a[501];
bool ok;
int main()
{

    cin >> t;
    for (; t--;)
    {
        ok = false;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int i = 1; i <= n; i++)
            if (a[i] != i)
            {
                int x;
                for (int j = 1; j <= n; j++)
                    if (a[j] == i)
                        x = j;
                // cout << i << " " << x << endl;
                for (int j = 0; j < (x - i + 1) / 2; j++)
                {
                    int tmp = a[i + j];
                    a[i + j] = a[x - j];
                    a[x - j] = tmp;
                }
                for (int j = 1; j <= n; j++)
                    cout << a[j] << ' ';
                ok = true;
                break;
            }
        if (!ok)
            for (int j = 1; j <= n; j++)
                cout << a[j] << ' ';
        cout << endl;
    }
    return 0;
}
```


---

## 作者：FFTotoro (赞：1)

题目要求最终输出字典序最小，可以发现，排在越前面的数越小，字典序也就越小。

我们知道 $p_i=i$ 时字典序为最佳方案。所以，将输入的数值对其下标进行比较，若比下标大，则证明这不是最优方案，以此为交换区间的左端点，找到下标的值在数组中的位置，为右端点，交换这一段，使得 $p_i=i$，即可将字典序最小化，是最佳选择。

放代码：

```cpp
#include<iostream>
using namespace std;
int a[100001];
int main(){
	ios::sync_with_stdio(false);
	int t; cin>>t;
	while(t--){
		int n,f=0,f2=0,flag=false,flag2=false; cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]!=i&&!flag){f=i,flag=true;} // 左端点
			else if(!flag2&&flag&&a[i]==f)f2=i,flag2=true; // 右端点
		}
		if(!f&&!f2){
			for(int i=1;i<=n;i++)cout<<a[i]<<' ';
			cout<<endl; continue;
		}
		for(int i=1;i<f;i++)cout<<a[i]<<' ';
		for(int i=0;i<=f2-f;i++)cout<<a[f2-i]<<' '; // 倒序输出
		for(int i=f2+1;i<=n;i++)cout<<a[i]<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：一个简单名字 (赞：1)

# CF1638A

## 题意

给你一个 $1 \sim n$ 序列（不含重复元素)，让你找到一个 $l$ 位置和 $r$ 位置。将 $l \sim r$ 位置上的元素翻转，即变成 $p_1,p_2,…p_{l-1},p_r,p_{r-1},…p_l,p_{r+1},p_{r+2},…p_n$ 的形式，使翻转后的序列的字典序最小。

## solution

注意此题的原序列是不含重复元素的，所以本题的解题难度大大下降。我考场上由于没看到这个条件白白浪费了一个小时……首先我们来思考，让一个数字序列的字典序尽量小该怎么操作？显然，让字典序越小的元素放在序列越靠前的位置。考虑代码实现，由于原序列中无重复元素，所以排序后的序列一定是严格递增的，而且原序列中一定只有一个点使翻转后的序列的字典序最小。在考场上我的思路是将原序列 $p$ 记录一个 $id$ 即这个值所在的位置（原序列的下标）。将原序列复制到一个新的序列 $b$ 中，将 $b$ 排序。之后枚举每个位置 $i$ 比较 $p_i$ 和 $b_i$ 找到第一个 $b_i<p_i$ 的位置，将该位置记为 $l$，$id_{b_i}$ 记为 $r$ 然后按题意输出即可。

## 证明

因为此时 $b$ 是有序的

 
$$
b_1<b_2<b_3…b_i…b_n
$$
若此时的 $i$ 为找到的第一个 $b_i<p_i$ 的位置，则此时的 $p$ 序列满足
$$
p_1<p_2<p_3…<p_i…
$$
$i$ 之前的位置一定已经为最小字典序，所以 $l$ 即为 $i$ 位置。

又因为此时 $b_i<p_i$，所以一定有一个 $p_k<p_i$ 并且 $k>i$。

将 $k$ 位置与 $i$ 位置进行翻转操作所得的序列一定是最优的。

---

## 作者：pandaSTT (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1638A)

[更好的阅读体验？](https://www.luogu.com.cn/blog/557117/solution-cf1638a)

# Thinking

首先考虑暴力枚举反向操作的的左右端点，同时用一个循环进行反向操作。

时间复杂度 $ O ( T n^3 ) $

$ T $ 与 $ n $ 的范围都是 $ 500 $ ，明显会 TLE。

进一步考虑，由于答案需要字典序最小，且只能进行一次反向操作。所以我们可以用一次操作将尽可能小的数提前。

我们用循环从小到大遍历查找第一个不在所在位置的数，进行反向操作，就可以让小提前，从而使得字典序最小。

时间复杂度 $ O ( T n^2 ) $

预计得分 $ 100 $ $ pts $

# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  const int N=505;
  int T,n,a[N],b[N];
  signed main(){
      cin>>T;
      while(T--){
          cin>>n;
          for(int i=1;i<=n;cin>>a[i++]);
          for(int i=1;i<=n;i++){
              if(a[i]!=i){
                  int k=i;
                  while(a[k]!=i){
                      k++;
                  }
                  for(int j=i;j<=k;j++){
                      b[j]=a[j];
                  }
                  for(int j=i,l=k;j<=k;j++,l--){
                      a[l]=b[j];
                  }
                  break;
              }
          }
          for(int i=1;i<=n;i++){
              cout<<a[i]<<" ";
          }
          putchar('\n');
      }
      return 0;
  }
```


---

## 作者：Milmon (赞：1)

[in Blog](//milk-lemon.blog.luogu.org/solution-CF1638A) & [Problem](//www.luogu.com.cn/problem/CF1638A)

## 题目大意
给定一个长度为 $n$ 的数列 $p$，你可以将其中任意一段进行翻转，求翻转后的字典序最小的序列。

## 解题思路
首先分析第一个数。第一个数如果是 $1$，那么字典序必然更小。如果不是 $1$，那么尽可能让 $1$ 翻转到第一个数的位置来，这样的字典序必然比第一个数不是 $1$ 的数列要小。  
如果第一个数本身是 $1$，那么必然不动第一个数，接着同理地分析第二个数、第三个数……  
找到一个不是最优的位置，再向后找到一个放在这里最优的数，以它们为起点和终点进行翻转即可。
时间复杂度 $\Theta(tn)$。

## AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T; scanf("%d",&T);
	while(T--){
		int n,a[501]={}; scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",a+i);
		int j=1; while(a[j]==j&&j<=n)j++;//找到不是最优的位置
		if(j>n){
			for(int i=1;i<=n;i++)
				printf("%d ",i);
			printf("\n"); //如果已经是最优，就直接输出
		}else{
			int k=j+1; while(a[k]!=j)k++;//往后找到这个数
//			cout<<j<<' '<<k<<endl;
			for(int l=j,r=k;l<r;l++,r--)swap(a[l],a[r]);//翻转
			for(int i=1;i<=n;i++)
				printf("%d ",a[i]);
			printf("\n"); 
		}
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：1)

### 题意简述

求出将数组连续的一段翻转后，字典序最小的序列是什么。

### 分析

题目要求字典序最小，那么就要将更小的数字放在前面。因此我们从第一个元素开始，寻找第一个不能保证字典序最小的元素（即，在数组第 $i$ 位但是数值不是 $i$ 的元素）。设它的下标为 $l$。然后找到可以保证字典序最小的数（即数值为 $i$ 的数）（设下标为 $r$）。之后翻转 $[l,r]$ 就好啦。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[510];
int main(){
	int t,n,p;
	scanf("%d",&t);
	while(t--){
		p=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
        for(int i=1;i<=n;i++){
        	if(a[i]!=i){  //第一个不能保证字典序最小的数
        		for(int j=i+1;j<=n;j++){
        			if(a[j]==i){  //找到并交换
        				reverse(a+i,a+j+1);  //STL大法好！
        				p=1;
        				break;
        			}
        		}
        	}
        	if(p==1){
        		break;
        	}
        }
		for(int i=1;i<=n;i++){
			printf("%d ",a[i]);
		}
		printf("\n");
	}
}
```


---

## 作者：Aurora_Borealis_ (赞：0)

贪心是显然的：

在之允许一次操作的情况下，为了维持词典需最小，必然是将第一个不在“对应位置”上的数与其“对应位置”的数之间的区间反转。

（“在对应位置”指 $ i $ 在第 $ i $ 个下标上）

代码：

```cpp
#include<iostream>
using namespace std;
int t,n,a[505],p[505];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			p[a[i]]=i;
		}
		for(int i=1;i<=n;i++){
			if(a[i]==i){
				cout<<a[i]<<" ";
				continue;
			}
			for(int j=p[i];j>=i;j--){
				cout<<a[j]<<" ";
			}
			for(int j=p[i]+1;j<=n;j++){
				cout<<a[j]<<" ";
			}
			break;
		}
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：bmatrix (赞：0)

考虑这样一种贪心策略：

按序号遍历 $a$，如果 $a_i=i$ 则继续，否则暴力向下找到一个 $a_j=i$，暴力翻转区间 $[i,j]$，然后退出。

正确性证明：

当遍历到 $a_i$ 时，$a_1$ 到 $a_{i-1}$ 一定已经是不需要翻转就已经字典序最小，因为如果不是的话程序在这之前就已经退出了。

再考虑 $a_i$：

- 如果 $a_i=i$，那么 $a_1$ 到 $a_{i}$ 仍是最小字典序，继续遍历即可。
- 如果 $a_i\neq i$，我们进行暴力翻转后 $a_i=i$，$a_1$ 到 $a_{i}$ 变成了最小字典序。根据字典序性质，所有 $a_1$ 到 $a_i$ 不是最小字典序的序列一定比 $a_1$ 到 $a_i$ 是最小字典序的序列要小。因此这时得到的序列一定是进行一次操作可以得到最小的，退出即可。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505];
int main(){
    int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
            if(a[i]!=i){
                int j=i+1;
                while(a[j]!=i)j++;//找到一个值为i的a[j]
                for(int k=i;k<j;k++,j--)swap(a[k],a[j]);//暴力翻转区间
                break;
            }
        for(int i=1;i<=n;i++)printf("%d ",a[i]);
        putchar(10);
    }
    return 0;
}
```

---

## 作者：miao5 (赞：0)

算是道签到题吧。

题目给你一个从 $1$ 到 $n$ 的排列 $a$，你可以反转 $a$ 的任意部分，求一次反转过后字典序最小的方案。

我们考虑一个字典序最小的排列 $a$，它对于 $1\le i\le n$，一定满足 $a_i=i$。

所以最优的方案就是每一位上的数等于它自己，并且越靠前的数越能影响字典序。

我们考虑暴力枚举 $i$ 从 $1$ 到 $n$，找到第一个 $i$ 使得 $a_i\ne i$。最优的方案肯定是在数组上进行一次反转，使得这里 $a_i=i$。我们暴力寻找 $i$ 这个数在 $a$ 中的位置，找到之后记录位置 $x$，使得 $a_x=i$。之后反转数组上 $i$ 到 $x$ 这一段就可以了。

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int read(){
	int s=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)){
		s=s*10+c-'0';
		c=getchar();
	}
	return s;
}
int a[505];
int main(){
	int t;
	t=read();
	while(t--){
		int n;
		n=read();
		for(int i=1;i<=n;i++) a[i]=read();
		int tmp=n;
		for(int i=1;i<=n;i++){
			if(a[i]!=i){
				tmp=i;
				break;
			}
		}
		int k=n;
		for(int i=tmp;i<=n;i++){
			if(a[i]==tmp){
				k=i;
				break;
			}
		}
		for(int i=1;i<tmp;i++) cout<<a[i]<<' ';
		for(int i=k;i>=tmp;i--) cout<<a[i]<<' ';
		for(int i=k+1;i<=n;i++) cout<<a[i]<<' ';
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：zhongcy (赞：0)

[Problem](https://codeforces.com/problemset/problem/1638/A)


### Solution

------------

令 $ p_i $ 为 $ p $ 中第一个满足 $ p_i \ne i $ 的元素。

显然，$ p_1 = 1 , p_2 = 2 , \dots p_{ i - 1 } = i - 1 $。所以，我们不用改变这些数因为它们已经满足字典序最小了。但是，我们希望 $ p_i = i $ ，所以我们可以反转区间 $  [ i , j ] $，其中 $ j $ 满足 $ p_j = i $。

------------

可以证明该算法的正确性。

Proof：设最优旋转区间为 $ [ u , v ] $ 且 $ u < v $。

- 对于 $ u < i $,显然 $ p_u < p_v $，则翻转之后的序列的第 $ u $ 项必然增大，矛盾

- 对于 $ u > i $，显然 $ p_i < p_u $，则翻转之后的序列的第 $ i $ 项保持不变，必然不是最优解，矛盾

综上，$ u = i $。同理可证 $ v = j $。


### Code

------------

根据上述结论，模拟即可。
时间复杂度 $ O (tn) $。



```cpp
#include<bits/stdc++.h>
#define N 501
using namespace std;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--)
	{
		int n;cin>>n;
		int p[N],pos[N];//pos记录数字出现位置
		for(int i=1;i<=n;i++)
		{
			cin>>p[i];
			pos[p[i]]=i;
		}
		for(int i=1;i<=n;i++)
			if(p[i]!=i)
			{
				reverse(p+i,p+pos[i]+1);//反转区间
				break;
			}
		for(int i=1;i<=n;i++)
			cout<<p[i]<<' ';//输出
		cout<<'\n';
	}
	return 0;
} 
```



---

## 作者：yinhy09 (赞：0)

## 思路讲解：

因为原本的序列是由 $1$ 到 $n$ 的，所以一旦出现 $a_{i}$ 不等于 $i$，那么意味着序列不是最优的。我们希望刚才的第 $i$ 位是 $i$，那么我们就可以继续往后找到 $a_{j}=i$，然后对第 $i$ 到 $j$ 位翻转即可。

## AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin>>T;
	const int maxn=500+5;
	int a[maxn];
	int s,t;
	while(T--)
	{
		s=0,t=0;
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]==i)
			{	
				s++;
				continue;
			}
			if(a[i]!=i)
			{
				s=i;
				break;
			}
		}
		for(int i=s+1;i<=n;i++)
		{
			cin>>a[i];
			if(a[i]==s)t=i;
		}
		if(s==n&&t==0)
		{
			for(int i=1;i<=n;i++)cout<<a[i]<<" ";
			cout<<endl; 
		}
		else
		{
			for(int i=1;i<s;i++)cout<<a[i]<<" ";
			for(int i=t;i>=s;i--)cout<<a[i]<<" ";
			for(int i=t+1;i<=n;i++)cout<<a[i]<<" ";
			cout<<endl;
		}
	} 
	return 0;
}

```

谢谢观看

---

## 作者：lsr1409111459 (赞：0)

### 1.CF1638A Reverse

#### 1.1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1638A)）

##### 1.1.1 题目大意

给定一个 $1$ 到 $n$ 的一个排列 $p_1,p_2,...,p_n$ 。

要求采用 **恰好** 一次操作：

- 选择两个整数 $l,r\ (\ 1\leq l\leq r \leq n\ )$ ，将区间 $[l,r]$ 翻转得到 $p_1,p_2,...,p_{l-1},p_r,r_{r-1},...,p_l,p_{r+1},p_{r+2},...,p_n$ 。

使得得到的新排列 **字典序最小** 。

##### 1.1.2 输入格式

第一行一个整数 $t\ (\ 1\leq t\leq 500\ )$ ，表示测试组数。

每组第一行一个整数 $n\ (\ 1\leq n\leq 500\ )$ ，表示排列的长度。

每组第二行 $n$ 个整数 $p_1,p_2,...,p_n\ (\ 1\leq p_i\leq n\ )$ ，表示给定的一个长度为 $n$ 的排列。

##### 1.1.3 输出格式

共 $t$ 行。

对于每组测试，输出你可以得到的字典序最小的排列。

##### 1.1.4 样例

###### 输入 #1

```cpp
4
1
1
3
2 1 3
4
1 4 2 3
5
1 2 3 4 5
```

###### 输出 #1

```cpp
1 
1 2 3 
1 2 4 3 
1 2 3 4 5
```

##### 1.1.5 样例解释

- 第一组测试，排列的长度为 $1$ ，所以选择区间 $[1,1]$ 翻转，得到的排列为 $[1]$ 。
- 第二组测试，选择区间 $[1,2]$ 翻转，得到的排列为 $[1,2,3]$ 。
- 第三组测试，最佳选择区间 $[2,3]$ 翻转，得到的排列为 $[1,2,4,3]$ 。
- 第四组测试，排列已经字典序最小，所以所以选择区间 $[1,1]$ 翻转，得到的排列为 $[1,2,3,4,5]$ 。

#### 1.2 解题思路

贪心。因为要求字典序最小，所以只需找到第一个和下标不同的数字，将其变为下标即可。

举个例子， $[1,2,4,5,3]$ ，要想得到字典序最小，只需让 $4$ 变为 $3$ 即可（因为最多翻转一次）。于是翻转区间 $[3,5]$ 得到排列 $[1,2,3,5,4]$ 。

所以翻转的左端点为第一个和数字不同的下标 $i$ ，右端点为数字 $i$ 所在的下标。

#### 1.3 解题代码

```cpp
#include <iostream>
using namespace std;
int T,n;
int a[510],b[510];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            b[i]=a[i];
        }
        int l=0,r=0,t=0;//l,r为区间左右端点，t为第一个和数字不同的下标i
        for(int i=1;i<=n;i++)
        {
            if(a[i]!=i&&!l){l=i;t=i;}
            if(a[i]==t){r=i;break;}
        }
        for(int i=l;i<=r;i++)
            a[i]=b[r-i+l];
        for(int i=1;i<=n;i++)printf("%d ",a[i]);
        printf("\n");
    }
    return 0;
}
```

#### 1.4 解题心得

签到题。以后做考试的签到题时应该将时间压缩在 10min 内，这样能保证后面题目的时间充裕。

不要把时间浪费在 入门/普及- 的题目上。

---

## 作者：断清秋 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1638A)

题意是说给一个序列，可以任意翻转一段区间 $[l,r]$，然后问翻转后字典序最小的序列。

考虑字典序最小的情况，肯定是 $a_i=i$，所以要把第一个不满足条件的位置改成 $a_i=i$，修改后的序列显然是唯一的。

然后考虑字典序的定义，只需要找到第一个 $a_i ≠ i$ 的位置，记 $s=i$，再找到 $a_j=s$，然后翻转区间 $[i,j]$ 即可。

时间复杂度 $O(tn)$。

---

## 作者：CmsMartin (赞：0)

## 题意简述

给你一个序列 $p_1,p_2,\dots,p_n$ ,保证序列中的数字不重复且为 $1 ∼ n$ 。你可以选择反转序列中的一个区间（当然也可以不反转），求操作后字典序最小的序列。

[题目传送门](https://codeforces.com/problemset/problem/1638/A)

## 思路

首先我们可以检查该序列是否有序，有序（即 $p_i=i$）时则已经为字典序最小，则不用反转。

在考虑要反转时的情况。我们找到第一个不有序的位置（即 $p_i \neq i$），此时显然 $i$ 数字一定在 $p_{i + 1}$ ~ $p_n$ 中（设 $p_x = i$），那为了保证字典序小，只需将 $p_i$ ~ $p_x$ 反转即可。正确性显然。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int T;
int N;
int Num[510];

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N;
        for(int i = 1; i <= N; i++) {
            cin >> Num[i];
        }
        for(int i = 1; i <= N; i++) {
            if(Num[i] != i) {
                for(int j = i + 1; j <= N; j++) {
                    if(Num[j] == i) {
                        for(int k = 1; k < i; k++) {
                            cout << Num[k] << " ";
                        }
                        for(int k = j; k >= i; k--) {
                            cout << Num[k] << " ";
                        }
                        for(int k = j + 1; k <= N; k++) {
                            cout << Num[k] << " ";
                        }
                        cout << endl;
                        goto end;
                    }
                }
            }
        }
        for(int i = 1; i <= N; i++) {
            cout << Num[i] << " ";
        }
        cout << endl;
        end:
            continue;
    }
    return 0;
}
```

---

## 作者：windflower (赞：0)

**简要题意：**  
>对区间内的数字进行翻转，使得翻转后得到的数组按字典序最小。

**可以知道：**
- 可以通过一次翻转将某个数移到任意位置。
- 最靠左的数要尽可能小。  

那么就很简单了。最小的数要移到最左边，如果最小的数已经在最左边了，那就把次小的数移到次左边，以此类推。  
附 AC 代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[505],n,t;
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i];
		int i=1;
		while(i<=n&&a[i]==i)i++;
		if(i!=n+1){
			int k=i;
			while(a[i]!=k)i++;
			reverse(a+k,a+i+1);
		}
		for(int i=1;i<=n;i++)printf("%d ",a[i]);
		printf("\n");
	}
	return 0;
}
```


---

## 作者：ttq012 (赞：0)

思维题。

字符串字典序比较，是按照从前到后的顺序，依次比较两个字符的大小的。

对于一个长度为 $n$ 的排列，字典序最小的那一个必然是 $1, 2, 3, \cdots, n$。


那么对于这个题目，我们可以贪心地找出第一个令 $a_i \neq i$ 的字符，然后暴力地找出下一个满足 $a_j = i$ 的字符，将这一段字符串翻转即可。

**Code**

```cpp
#include <bits/stdc++.h>

using namespace std;

int a[1000001];

signed main() {
    int t;
    cin >> t;
    while (t --) {
        int n;
        scanf ("%d", &n);
        for (int i = 1; i <= n; i ++) scanf ("%d", &a[i]);
        bool flag = true;
        int idl = n, idr = n;
        vector <int> b;
        for (int i = 1; i <= n; i ++) if (a[i] != i) {
            idl = i, idr = i;
            for (int j = i + 1; j <= n; j ++) if (a[j] == i) {
                idr = j;
                flag = false;
                break;
            } if (! flag) break;
        } for (int j = idl; j <= idr; j ++) {
            b.push_back(a[j]);
        } reverse(b.begin(), b.end()); for (int i = 1; i < idl; i ++) {
            printf ("%d ", a[i]);
        } for (int i = idl, j = 0; i <= idr; i ++, j ++) {
            printf ("%d ", b[j]);
        } for (int i = idr + 1; i <= n; i ++) printf ("%d ", a[i]);
        puts("");
    }
    return 0;
}
```


---

## 作者：PRIMITIVE_LIGHTS (赞：0)

## Description
给你一个长度为 $n$ 的排列 (是由 整数 $1$ ~ $n$ 以任意顺序组成的数列),请你求出翻转一次任意区间 $[l,r]$ 所能得到最大字典序的方案。

## Solution

先扔结论: 
	
1. $1,2,3,....,n$ 是最小的字典序排列  ~~(废话)~~

2. 每一个排列的前端都有长度为 $0$ ~ $n$ 的一段符合上面一条的部分。 ~~(还是废话)~~

3. 在这一段之后，翻转最小的数和不符合第一条的开端这部分区间就可以得到最优解。

证明:

符合第一条的前端是不需要翻转的,因为在这部分之后的数一定大于前端中任意一个数,翻转只会使大数放在前面。

不符合第一条的后端需要翻转最小的数和不符合第一条的开端。若不翻转这一段,那么比这一段最小的数要大的数会翻转到最小的数的前面，不满足字典序最小。

Code Time:
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int T,n;
int a[501];
int IND,indx,ind;
int maxx,maxn;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>T;
	while(T--){
		indx=0x7fffffff;ind=-1;
		bool f=0;
		cin>>n;
		for(int i=1;i<=n;++i){
			cin>>a[i];
			if(f) if(a[i]<indx) indx=a[i],ind=i;
			if(a[i]!=i) if(!f) IND=i,f=1;
		}
		if(ind!=-1)	reverse(a+IND,a+1+ind);
		for(int i=1;i<=n;++i){
			cout<<a[i]<<" ";
		}
		cout<<'\n';
	}
}
```




---

## 作者：Toorean (赞：0)

## 题意
给出一个排列 $p_1,p_2,\cdots,p_n$，将这个排列的 $[l,r]$ 进行反转，问可以得到的最小排列是多少？

## 思路
首先，要想要使当前排列最小，那么必须要使最小的数往前。首先，我们可以定一个分界点 $i$ 表示分界前后，之后再从 $n$ 遍历至 $i$ 查找最小值 $min\_value$ 并记录下标 $r$，再从 $1$ 到 $i$ 查找最前面的比 $min\_value$ 大的值并记录下标 $l$，之后便找到了，跳出循环。将数组的 $[l,r]$ 进行反转，即可求解。

## AC Code
```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>

#define MAXN 510
#define INF 0x3f3f3f3f

int t, n;
int arr[MAXN];

void solve (int n, int arr[]) {
    int l = -1, r = -1, minn = MAXN;
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        minn = INF;

        for (int j = n; j >= i; j--) {
            if (arr[j] < minn) {
                minn = arr[j];
                r = j;
            }
        }
        for (int j = 1; j <= i; j++) {
            if (arr[j] > minn) {
                l = j;
                flag = true;
                break;
            }
        }

        if (flag) {
            break ;
        }
    }

    if (l > 0 && r > 0) {
        int i = l, j = r;
        while (i <= j) {
            std :: swap (arr[i ++], arr[j --]);
        }
    } 
    for (int i = 1; i <= n; i++) {
        printf ("%d ", arr[i]);
    } puts ("");
}

int main (void) {

    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf ("%d", arr + i);
        }

        solve (n, arr);
    }

    return 0;
}
```

---

