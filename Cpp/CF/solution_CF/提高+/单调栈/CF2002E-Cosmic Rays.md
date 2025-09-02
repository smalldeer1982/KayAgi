# Cosmic Rays

## 题目描述

给定一个整数数组 $s_1, s_2, \ldots, s_l$，每过一秒，宇宙射线会使所有满足 $i=1$ 或 $s_i\neq s_{i-1}$ 的 $s_i$ 同时被删除，剩下的部分会按顺序拼接成新的数组 $s_1, s_2, \ldots, s_{l'}$。

定义一个数组的“强度”为其变为空所需的秒数。

你得到的整数数组以 $n$ 个对的压缩形式给出，描述了从左到右的数组。每个对 $(a_i, b_i)$ 表示 $a_i$ 个 $b_i$，即 $\underbrace{b_i, b_i, \cdots, b_i}_{a_i\textrm{ 次}}$。

对于每个 $i=1,2,\dots,n$，请你求出由前 $i$ 个对描述的序列的强度。

## 说明/提示

在第一个测试用例中，长度为 $4$ 的前缀对应的变化为 $[0,0,1,0,0,0,1,1,1,1,1]\rightarrow[0,0,0,1,1,1,1]\rightarrow[0,0,1,1,1]\rightarrow[0,1,1]\rightarrow[1]\rightarrow[]$，因此该数组在 $5$ 秒后变为空。

在第二个测试用例中，长度为 $4$ 的前缀对应的变化为 $[6,6,6,6,3,6,6,6,6,0,0,0,0]\rightarrow[6,6,6,6,6,6,0,0,0]\rightarrow[6,6,6,6,6,0,0]\rightarrow[6,6,6,6,0]\rightarrow[6,6,6]\rightarrow[6,6]\rightarrow[6]\rightarrow[]$，因此该数组在 $7$ 秒后变为空。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
4
2 0
1 1
3 0
5 1
6
4 6
1 3
4 6
4 0
7 6
6 3
7
9 0
7 1
5 0
7 1
9 0
1 1
2 0
10
10 7
4 9
2 2
7 9
2 8
8 5
11 7
15 5
12 7
4 0```

### 输出

```
2 2 4 5 
4 4 7 7 10 10 
9 9 9 9 9 9 10 
10 10 10 10 10 10 12 15 15 15```

# 题解

## 作者：int08 (赞：12)

## 前言

你觉得你是 *$2300$ 吗？

我觉得我是。
## 简要题意

一个序列，每次消掉所有极长连续相等段的第一个数，问多少秒消完。

现在序列初始为空动态添加 $n$ 次，每次在末尾加入 $a_i$ 个 $b_i$，每次加入都回答一次这个问题。

$n,b_i\le 10^5,a_i\le 10^9$。
# Solution
第一反应是 $\max a_i$，但是不对，因为后面可能跟前面相等的数合并（当中间全部消耗完的时候），合并之后两段合起来了，每次只消一个数，用时就会变长。

然后发现两个同颜色段能合并当且仅当中间都比他们短，而且一旦合并了，中间就没有意义了（因为已经完全被隔开了），不可能再和后面加入的合并或者影响答案的。

另外如果后面添加的比前面的多，前面也不可能和后面加入的合并，也没必要留着了。

于是想到维护一个单调栈，这题就结束了。

具体的，维护一个数量依次递减的单调栈，每次从最后一个一个把栈顶不同色且更小的弹出，碰到同色就吸收，具体的，设现在加入的数量为 $a$，栈顶同色的为 $x$，刚刚弹出的异色栈顶为 $y$，则合并为 $a+x-y$ 继续下传。

每次答案就是栈底。

## AC Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 333664
pair<int,int> sta[N];
int pt,n,i,j,a[N],b[N],T;
signed main()
{
	cin>>T;
	while(T--)
	{
		cin>>n;
		for(i=1;i<=n;i++)
		{
			cin>>a[i]>>b[i];b[i]++;
			while(pt>0&&sta[pt].first<=a[i])
			{
				if(sta[pt-1].second==b[i]) a[i]+=sta[pt-1].first-sta[pt].first,pt--;
				pt--;
			}
			sta[++pt]={a[i],b[i]};
			cout<<sta[1].first<<" ";
		}
		cout<<endl;
		pt=0;
	}
	return 0;
}
```
The End.

---

## 作者：tzl_Dedicatus545 (赞：1)

### Preface

被 $2300$ 击杀了。

### Solution

我们首先考虑边界情况，如果边界两段满足 $a_1\leq a_2$，那么 $a_1$ 就是没有用的（因为 $a_2$ 被杀掉的时候 $a_1$ 一定死了）

这启示我们考虑维护一个单调栈结构，接下来步骤就是简单的了，每次 `pop` 的时候看一下是否需要相同颜色合并即可。

复杂度 $O(n)$。

---

## 作者：chlchl (赞：1)

信息课摸鱼。

## Solution
题意等价于每秒删掉每一个连续段的第一个数，求每个前缀的最小删除秒数。

首先有个结论：若 $a_i\le a_{i+1}$，$b_i\ne b_{i+1}$，那么 $i$ 不会对后面的答案产生贡献，因为它一定在 $i+1$ 之前被消完。

所以有用的 $a_i$ 除去可以合并的情况外，一定是单调下降的。

其次我们第一眼都有直觉是 $\max a_i$，但是很遗憾是错的，因为前后两段有可能可以合并，答案会大于这个数。

那么来考虑两段可以合并需要满足什么条件：显然地，这两段之间的所有段的 $a$ 都要小于这两段的 $a$。

即若 $a_i,a_j$ 可以合并，则 $\forall k\in(i,j)$，有 $a_k<a_i,a_k<a_j$。

这个从尾部加然后判断一个后缀的操作，启发我们用一个先进后出的数据结构维护——单调栈。

我们每加进一个 $(a_i,b_i)$ 时，讨论栈顶元素 $(a_t,b_t)$ 的情况：
- 栈顶的 $b$ 一定不可能与 $b_i$ 相同，因为题目保证了；
- 但是如果栈顶下面那个元素 $b_{t-1}=b_i$，并且 $a_t\le a_i$，那么这两段是可以合并的，新合并完后的 $a=a_i+a_{t-1}-a_t$。
- 否则只要 $a_t\le a_i$，那么 $t$ 对 $i$ 处的答案无影响，直接弹出。

最后把 $(a_i,b_i)$ 扔进去即可，还有一点点细节。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 3e5 + 10;
int n, tp;
struct point{
	ll a, b;
} c[N];
point st[N];

void i_love_xyr(int i){
	while(tp > 0 && st[tp].a <= c[i].a){
		if(st[tp - 1].b == c[i].b){
			c[i].a += st[tp - 1].a - st[tp].a;
			--tp;
		}
		--tp;
	}
	st[++tp] = c[i];
	printf("%lld ", st[1].a);
}

void solve(){
	scanf("%d", &n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld", &c[i].a, &c[i].b);
	tp = 0;
	for(int i=1;i<=n;i++)
		i_love_xyr(i);
	printf("\n");
}

int main(){
	int T;
	st[0] = {-1, -1};
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}

```

---

