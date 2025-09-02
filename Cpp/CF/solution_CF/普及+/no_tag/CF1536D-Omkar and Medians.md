# Omkar and Medians

## 题目描述

Uh oh! Ray lost his array yet again! However, Omkar might be able to help because he thinks he has found the OmkArray of Ray's array. The OmkArray of an array $ a $ with elements $ a_1, a_2, \ldots, a_{2k-1} $ , is the array $ b $ with elements $ b_1, b_2, \ldots, b_{k} $ such that $ b_i $ is equal to the median of $ a_1, a_2, \ldots, a_{2i-1} $ for all $ i $ . Omkar has found an array $ b $ of size $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ , $ -10^9 \leq b_i \leq 10^9 $ ). Given this array $ b $ , Ray wants to test Omkar's claim and see if $ b $ actually is an OmkArray of some array $ a $ . Can you help Ray?

The median of a set of numbers $ a_1, a_2, \ldots, a_{2i-1} $ is the number $ c_{i} $ where $ c_{1}, c_{2}, \ldots, c_{2i-1} $ represents $ a_1, a_2, \ldots, a_{2i-1} $ sorted in nondecreasing order.

## 说明/提示

In the second case of the first sample, the array $ [4] $ will generate an OmkArray of $ [4] $ , as the median of the first element is $ 4 $ .

In the fourth case of the first sample, the array $ [3, 2, 5] $ will generate an OmkArray of $ [3, 3] $ , as the median of $ 3 $ is $ 3 $ and the median of $ 2, 3, 5 $ is $ 3 $ .

In the fifth case of the first sample, the array $ [2, 1, 0, 3, 4, 4, 3] $ will generate an OmkArray of $ [2, 1, 2, 3] $ as

- the median of $ 2 $ is $ 2 $
- the median of $ 0, 1, 2 $ is $ 1 $
- the median of $ 0, 1, 2, 3, 4 $ is $ 2 $
- and the median of $ 0, 1, 2, 3, 3, 4, 4 $ is $ 3 $ .

In the second case of the second sample, the array $ [1, 0, 4, 3, 5, -2, -2, -2, -4, -3, -4, -1, 5] $ will generate an OmkArray of $ [1, 1, 3, 1, 0, -2, -1] $ , as

- the median of $ 1 $ is $ 1 $
- the median of $ 0, 1, 4 $ is $ 1 $
- the median of $ 0, 1, 3, 4, 5 $ is $ 3 $
- the median of $ -2, -2, 0, 1, 3, 4, 5 $ is $ 1 $
- the median of $ -4, -2, -2, -2, 0, 1, 3, 4, 5 $ is $ 0 $
- the median of $ -4, -4, -3, -2, -2, -2, 0, 1, 3, 4, 5 $ is $ -2 $
- and the median of $ -4, -4, -3, -2, -2, -2, -1, 0, 1, 3, 4, 5, 5 $ is $ -1 $

For all cases where the answer is NO, it can be proven that it is impossible to find an array $ a $ such that $ b $ is the OmkArray of $ a $ .

## 样例 #1

### 输入

```
5
4
6 2 1 3
1
4
5
4 -8 5 6 -7
2
3 3
4
2 1 2 3```

### 输出

```
NO
YES
NO
YES
YES```

## 样例 #2

### 输入

```
5
8
-8 2 -6 -5 -4 3 3 2
7
1 1 3 1 0 -2 -1
7
6 12 8 6 2 6 10
6
5 1 2 3 6 7
5
1 3 4 3 0```

### 输出

```
NO
YES
NO
NO
NO```

# 题解

## 作者：water_tomato (赞：5)

本文同步发表于个人博客：[Link](https://www.watertomato.com/cf1536d-omkar-and-medians-%e9%a2%98%e8%a7%a3/)。

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF1536D)。

记 $b_i$ 为 $a_1 \sim a_{2i-1}$ 的中位数，给定序列 $b$，询问是否存在合法的序列 $a$。

## 解析

考虑 $b_i$ 和 $b_{i-1}$ 的关系。我们先假设 $b_1 \sim b_{i-1}$ 均合法。

- 若 $b_{i-1}=b_i$，则新增的两个数只需一大一小地取即可，$b_i$ 也一定合法。
- 若 $b_{i-1}<b_i$，因为 $b_{i-1}$ 是 $2i-3$ 个数的中位数，所以序列中一定有 $i-1$ 个数比 $b_i$ 小。对于任意一个 $b_j(j<i-1)$ ，如果其满足 $b_j \le b_{i-1}$，则它可以作为这 $i-1$ 个数中的一个数，不影响结果。若其满足 $b_{i-1} < b_j < b_i$，则此时我们发现序列中至少有 $i$ 个数比 $b_i$ 小，这就是不合法的。
- 若 $b_{i-1}>b_i$，同理寻找有无一个 $b_j$ 满足 $b_{i-1}>b_j>b_i$ 即可。

我们发现所有相同的数出现一次和出现多次在统计答案时没有区别，因为可以简单地使用一个 set 维护，每次查询时：

- 若 $b_{i-1}<b_i$，查询 $b_{i-1}$ 的后继是否为 $b_i$，若不是则不存在合法序列 $a$。
- 若 $b_{i-1}>b_i$，查询 $b_i$ 的后继是否为 $b_{i-1}$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n;
int b[N];
set<int> s;
int main(){
	scanf("%d",&T);
	while(T--){
		bool fl=1;
		s.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&b[i]);
			if(!s.count(b[i])) s.insert(b[i]);//相同的数无意义，直接不加入 set 即可。
			if(b[i]==b[i-1]) continue;
			if(b[i-1]<b[i]){
				if(s.upper_bound(b[i-1])!=s.find(b[i])){
					fl=0;//若 b[i-1] 的后继不为 b[i]，就不合法。
				}
			}
			else{
				if(s.upper_bound(b[i])!=s.find(b[i-1])){
					fl=0;//同理
				}
			}
		}
		if(fl){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
```



---

## 作者：E1_de5truct0r (赞：3)

## 思路

相当于一开始有一个数，每次操作加入两个数，要求每次操作之后中位数为给定的值。

由于每次操作加入两个数，所以中位数最多在加入前的序列中变化 $1$ 位。那么我们就需要保证对于两个不相等且相邻的 $b$，例如 $b_{i-1},b_i$，一定不存在一个 $j \in [1,i-2]$ 使得 $b_j$ 在 $b_{i-1}$ 与 $b_i$ 之间，否则中位数最多就只能变成 $b_j$ 了。

那么我们考虑使用 set 维护 $1 \sim i$ 的集合，则在 set 中，$b_{i-1}$ 和 $b_i$ 中的较小者的后继必须是较大者，否则不合法。

另外还需要注意判断一下 set 里找不到的情况。

复杂度 $O(n \log n)$。

## 代码

[Code & Submission](https://codeforces.com/contest/1536/submission/220000038)

---

## 作者：丛雨 (赞：1)

# CF1536D

> 题意:初始给出长度为$n$的序列$a$,求是否存在长度为$2n-1$的序列$b$,满足$\forall i\in[1,n],b_{1\sim 2i-1}$的中位数为$a_i$
>
> $1\leq T \leq 10^4,\Sigma n\leq 2\times 10^5,|a_i|\leq 10^9$

可以知道，当$i$变为$i+1$时，相当于向$b$中加入2个元素(i=0时除外)，而这样只会让中位数在排序后的$b$中移动至多一位

例如:$\{1,\underline 3,5\}+(4,6)\rightarrow \{1,3,\underline 4,5,6\}$,位置从$'3'$移动到$'4'$移动1位

所以如果**原**$b$中存在我们想要成为中位数的$a_i$,则他们在$b$中的距离不能超过$1$,此时我们加入两个$\pm\infty$使中位数移动

若$a_i=a_{i-1}$,则加入一个$+\infty$一个$-\infty$,使中位数不变

如果原b中存在我们想要成为中位数的$a_i$,则不能存在元素$a_{i-1}<b_x<a_i$,此时加入一个$\pm\infty$和$a_i$使中位数变为$a_i$

为什么加入$\pm \infty$

贪心地想，最理想的情况便是不存在非$a$中的元素挡在$a_{i-1}$和$a_i$之间，而为$\pm \infty$时则满足这个条件

这样这道题就成了个模拟题，如果使用$\tt set$时间复杂度$O(n\log n)$,使用链表时间复杂度$O(n)$

```cpp
//link sum:864ms largest:31ms
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
struct node{
	node *l,*r;
	int v;
	node(int _v=0){l=r=NULL;v=_v;}
}*x,*a=new node[200000];
int main(){
	for(int T=read;T--;){
		int s=read;bool vis=1;
		x=new node(read);
		for(int i=2;i<=s;++i){
			int g=read;
			if(x->v==g)continue;
			if(x->v<g)
				if(x->r&&x->r->v<g){vis=0;while(++i<=s)read;break;}
				else
					if(x->r)
						if(x->r->v!=g){
							node *t=a++;t->v=g;
							t->l=x;t->r=x->r;
							x->r->l=t;x->r=t;x=t;
						}else x=x->r;
					else{
						node *t=a++;t->v=g;
						t->l=x;x->r=t;x=t;
					}
			else
				if(x->l&&x->l->v>g){vis=0;while(++i<=s)read;break;}
				else
					if(x->l)
						if(x->l->v!=g){
							node *t=a++;t->v=g;
							t->r=x;t->l=x->l;
							x->l->r=t;x->l=t;x=t;
						}else x=x->l;
					else{
						node *t=a++;t->v=g;
						t->r=x;x->l=t;x=t;
					}
		}puts(vis?"YES":"NO");
	}
	return 0;
}
```

```cpp
//set sum:? largest:78ms
#include<bits/stdc++.h>
using namespace std;
# define ll long long
# define read read1<ll>()
# define Type template<typename T>
Type T read1(){
	T t=0;
	char k;
	bool vis=0;
	do (k=getchar())=='-'&&(vis=1);while('0'>k||k>'9');
	while('0'<=k&&k<='9')t=(t<<3)+(t<<1)+(k^'0'),k=getchar();
	return vis?-t:t;
}
# define fre(k) freopen(k".in","r",stdin);freopen(k".out","w",stdout)
int s;
set<int>se;
int main(){
	for(int T=read;T--;){
		s=read;se.clear();
		auto w=se.begin();
		bool vis=1;
		for(int i=1;i<=s;++i){
			int x=read;
			if(i==1){se.insert(x);w=se.begin();continue;}
			if(x==*w)continue;
			if(x>*w){++w;
				if(w==se.end()||*w>=x)se.insert(x),w=se.lower_bound(x);
				else{vis=0;while(++i<=s)read;break;} 
			}else
				if(w==se.begin()||*--w<=x)se.insert(x),w=se.lower_bound(x);
				else{vis=0;while(++i<=s)read;break;} 
		}puts(vis?"YES":"NO");
	}
	return 0;
}
```



---

