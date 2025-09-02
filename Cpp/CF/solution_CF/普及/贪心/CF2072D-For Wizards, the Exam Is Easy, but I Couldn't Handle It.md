# For Wizards, the Exam Is Easy, but I Couldn't Handle It

## 题目描述

Akito 厌倦了在银行当普通锁匠的工作，因此他决定进入魔法学院并成为世界上最强的巫师！然而，为了入学，他需要解决考试中的唯一一道题目，而这位雄心勃勃的英雄却未能成功。

题目给出一个长度为 $n$ 的数组 $a$。Akito 需要在使用恰好一次咒语后，使数组中的逆序对数量 $^{\text{∗}}$ 最小化。咒语的使用方式很简单：Akito 必须选择两个数 $l$ 和 $r$（满足 $1 \le l \le r \le n$），并对子数组 $[l, r]$ 进行一次向左循环移位。

更正式地说，Akito 选择子数组 $[l, r]$ 并按以下方式修改数组：

- 原始数组为 $[a_1, a_2, \ldots, a_{l - 1}, \mathbf{ a_l }, \mathbf{ a_{l + 1} }, \mathbf{ \ldots }, \mathbf{ a_{r - 1} }, \mathbf{ a_r }, a_{r + 1}, \ldots, a_{n - 1}, a_n]$，修改后的数组变为 $[a_1, a_2, \ldots, a_{l - 1}, \mathbf{ a_{l + 1} }, \mathbf{ a_{l + 2} }, \mathbf{ \ldots }, \mathbf{ a_{r - 1} }, \mathbf{ a_{r} }, \mathbf{ a_{l} }, a_{r + 1}, \ldots, a_{n - 1}, a_{n}]$。

Akito 渴望开始他的学习，但他仍未通过考试。请帮助他入学并解决这道题目！

$^{\text{∗}}$ 在长度为 $m$ 的数组 $b$ 中，逆序对被定义为满足 $1 \le i < j \le m$ 且 $b_i > b_j$ 的索引对 $(i, j)$。例如，在数组 $b = [3, 1, 4, 1, 5]$ 中，逆序对为索引对 $(1, 2)$、$(1, 4)$ 和 $(3, 4)$。

## 说明/提示

在第一个示例中，数组 $[1, 4, 3, 2, 5, 3, 3]$ 将变为 $[1, 3, 2, 5, 3, 3, 4]$。其中的逆序对为 $(2, 3)$、$(4, 5)$、$(4, 6)$ 和 $(4, 7)$。可以证明无法获得少于 $4$ 个逆序对。

在第二个示例中，数组 $[1, 4, 3, 2, 5, 3]$ 将变为 $[1, 3, 2, 4, 5, 3]$。其中的逆序对为 $(2, 3)$、$(4, 6)$ 和 $(5, 6)$。选择 $l = 2$ 和 $r = 6$ 同样有效，此时数组变为 $[1, 3, 2, 5, 3, 4]$，其中也有 $3$ 个逆序对：$(2, 3)$、$(4, 5)$ 和 $(4, 6)$。可以证明无法获得少于 $3$ 个逆序对。

在第四个示例中，选择 $l = 4$ 和 $r = 6$ 将数组变为 $[1, 1, 1, 1, 1, 5, 5, 6, 7, 8]$。该数组已排序，因此没有逆序对。

在最后一个示例中，数组初始时已排序，因此对长度至少为 $2$ 的段进行任何操作只会增加逆序对的数量。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
7
1 4 3 2 5 3 3
6
1 4 3 2 5 3
8
7 6 5 8 4 3 2 1
10
1 1 1 5 1 1 5 6 7 8
2
1337 69
4
2 1 2 1
3
998 244 353
3
1 2 1
9
1 1 2 3 5 8 13 21 34```

### 输出

```
2 7
2 4
1 8
4 6
1 2
1 4
1 3
2 3
5 5```

# 题解

## 作者：f_K_e1207 (赞：6)

很有意思的一道数列题。题意中给出翻转序列的操作还是比较复杂，转换一下表述，就是将位置 $l$ 的数插入到 $r$ 与 $r+1$ 之间。

题面中保证所有 $n^2$ 之和不超过 $4\times 10^6$，这启发我们设计一个 $O(n^2)$ 的算法。对于此类寻找区间的题目，自然地，我们想到枚举左右端点，复杂度也恰好是 $O(n^2)$。

接下来，我们应该思考如何最优化这个区间，注意到操作后所有逆序对的变化都只与区间内的数有关。则逆序对总的减少量，为减少的逆序对数量减去增加的逆序对的数量。那怎么样才会使逆序对数量减少或增加呢？在本题中，逆序对减少意味着 $a_l$ 移动到了比它小的数后面，增加意味着 $a_l$ 移动到了比它大的数后面。增加和减少多少都分别等于区间内大于和小于 $a_l$ 的数的个数。其数学语言是：
$$
\Delta_{max}=\max_{1\le l\le r\le n}\{\sum_{i=l+1}^r[x_i<x_l]-\sum_{i=l+1}^r[x_i>x_l]\}
$$
此时的算法已经非常显然了，贴个代码：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[2010],l,r,val;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	for (cin>>t;t;t--)
	{
		cin>>n;
		l=1,r=1,val=0;
		for (int i=1;i<=n;i++)
			cin>>a[i];
		for (int i=1;i<=n;i++)
		{
			int cntb=0,cnts=0;
			for (int j=i;j<=n;j++)
			{
				if (a[j]>a[i]) cntb++;
				if (a[j]<a[i]) cnts++;
				if (cnts-cntb>val)
				{
					val=cnts-cntb;
					l=i;
					r=j;
				}
			}
		}
		cout<<l<<' '<<r<<'\n';
	}
	return 0;
}
~~~
不得不说 cf 上的很多简单题都很有质量。

---

## 作者：Pyrf_uqcat (赞：1)

直接枚举将第 $i$ 个数移到 $j$ 位置时的答案，数据 $O(n^2)$ 能过。

关于过程，我们先用两层循环枚举上面说的，然后进行逐个比较并记录比当前值的大的数量和比当前值小的数量，为了让逆序对更少，只需每次对比大的数量减比小的数量作为答案进行更新即可。

代码中有注释。


```cpp
#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)
#include <bits/stdc++.h>
#define int long long 

using namespace std;

const int N=2e5+5;

int n,a[N];

int ans,ans1,ans2;

signed main()
{
	int t;cin>>t;
	while(t--)
	{
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        ans=0,ans1=1,ans2=1;
        //设为1是因为当答案没有更新时就输出1 1
        for(int i=1;i<=n;i++)
        //枚举要移动的数
		{
            int cnt[2]={};
            //分别记录比当前值大的数量和比小的数量
            for(int j=i+1;j<=n;j++)
            //枚举移动位置
			{
                if(a[i]>a[j]) cnt[0]++;
                if(a[i]<a[j]) cnt[1]++;
                int res=cnt[0]-cnt[1];
                if(ans<res)
                //更新答案
                {
					ans=res;
					ans1=i,ans2=j;
					//存储答案
				}
            }
        }
        cout<<ans1<<' '<<ans2<<endl;
        
	}
	return 0;
}
```

---

## 作者：_O_w_O_ (赞：0)

我们设 $f(l,r)$ 为 $[l,r]$ 内的 $>a_l$ 的数的数量，那么对 $[l,r]$ 做操作后，带来的新的逆序对数为 $-f(l,r)+(r-l-f(l,r))$，因为 $[l,r]$ 内 $<a_l$ 的数无法产生贡献，但 $>a_l$ 的数产生了新的贡献。

那么直接暴力枚举 $[l,r]$，计算一下即可。

code：<https://codeforces.com/contest/2072/submission/309458453>

---

## 作者：tzzl3035 (赞：0)

### CF2072D 题解

#### 大致思路

就是向后移动一个数，使得逆序对数量最大地减小。逆序对，不就是后面比前面小，所以在区间 $(l, r]$ 中，我们要尽量让小于 $a_l$ 的尽量多，大于 $a_l$ 的尽量少。加上数据限制，使用 $O(n^2)$ 的算法，即可通过本题。

#### 代码详解

```cpp
#include <bits/stdc++.h>

int main() {
  int t; std::cin >> t;
  for(; t; --t) {
// 输入
    int n; std::cin >> n;
    std::vector<int> arr(n+3, 0);
    for(int i = 1; i <= n; ++i) 
      std::cin >> arr[i];
// 统计答案
    int ans = 0, l = 1, r = 1;
    for(int i = 1; i <= n; ++i) { // 固定 l
      int cnt1 = 0, cnt2 = 0;
      for(int j = i; j <= n; ++j) {
// 用cnt分别统计比 a[l] 大的和比 a[l] 小的
        if(arr[j] > arr[i]) ++cnt2;
        if(arr[j] < arr[i]) ++cnt1;
        if(ans < cnt1 - cnt2) // 更新答案
          ans = cnt1 - cnt2, l = i, r = j;
      }
    }
    std::cout << l << ' ' << r << '\n'; // 输出
  }
}
```

#### [RESULT](https://codeforces.com/contest/2072/submission/309231149)

---

## 作者：IGpig (赞：0)

## CF2072D
### Problem
给你一个数列，长度为 $n$，现在移动一个位置的数，问让移动后数列中逆序对的数量最少的方法。
### Solution
我们首先可以想到就是要让减少的逆序对最多，然后可以发现题目中有一句话：

It is guaranteed that the sum of $n^2$ across all test cases does not exceed $4⋅10^6$.

意思就是用 $O(n^2)$ 的算法可以过，实际上存在复杂度更优的解法（数据结构维护）。
那么显然想到先枚举一个数 $a_i$，然后枚举目标位置 $j$，那么怎么计算减少的数量呢？
考虑记录一下：

- $cnt$:$a_j>a_i$ 的 $j$ 的数量。
- $cntt$:$a_j=a_i$ 的 $j$ 的数量。

所以最后减少的就是：
$$cnt-(i-j-cnt-cntt)$$
$$2\times cnt+cntt-(j-i)$$

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
LL n,a[500005],ans,l,r,t;
int main(){
    cin>>t;
    while(t--){
        ans=0;
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        for(int i=1;i<=n;i++){
            LL cnt=0,cntt=0;
            for(int j=i+1;j<=n;j++){
                if(a[j]==a[i]) cntt++;
                if(a[j]<a[i]){
                    cnt++;
                    if(ans<=2*cnt+cntt-(j-i)){
                        ans=2*cnt+cntt-(j-i);
                        l=i,r=j;
                        //cout<<ans<<l<<' '<<r<<endl;
                    }
                }
            }
        }
        if(ans==0) l=r=1;
        cout<<l<<' '<<r<<endl;
    }
    return 0;
}
```

---

## 作者：wmrqwq (赞：0)

这是一篇视频题解。

![](bilibili:BV1FHP3eAEWj?t=433)

[代码链接](https://codeforces.com/contest/2072/submission/307826922)

---

