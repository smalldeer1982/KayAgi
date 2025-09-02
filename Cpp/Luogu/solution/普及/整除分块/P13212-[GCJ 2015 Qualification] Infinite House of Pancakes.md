# [GCJ 2015 Qualification] Infinite House of Pancakes

## 题目描述

在 Infinite House of Pancakes（无限煎饼屋），实际上只有有限数量的煎饼，但有无限多的食客愿意来吃！当餐厅早晨开门时，在无数食客中，恰好有 $D$ 位食客的盘子里有煎饼；第 $i$ 位食客的盘子里有 $P_i$ 块煎饼。其他所有人的盘子都是空的。

通常情况下，每过一分钟，每个盘子里有煎饼的食客会吃掉自己盘子中的一块煎饼。然而，有些分钟可能是“特殊分钟”。在特殊分钟里，主服务员会请大家注意，选择一位盘子里有煎饼的食客，从该食客的盘子中取出若干块煎饼，并将这些煎饼转移到另一位食客（无论其盘子是否为空）的盘子里。在特殊分钟里，没人会吃煎饼，因为那样太不礼貌了。

你是今天早上的主服务员，你需要决定哪些分钟（如果有的话）是特殊分钟，以及哪些煎饼要转移到哪里。也就是说，每一分钟，你可以选择什么都不做，让食客们吃煎饼，或者宣布这是一个特殊分钟，打断食客们，进行一次煎饼的转移操作，如上所述。

当所有煎饼都被吃完时，早餐结束。你能让早餐在最短的时间内结束吗？

## 说明/提示

**样例解释**

在第 1 组样例中，一位食客一开始有 3 块煎饼，其他人的盘子都是空的。一种最优策略如下：

第 1 分钟：什么都不做。该食客吃掉一块煎饼。

第 2 分钟（特殊分钟）：打断，取出一块煎饼放到另一位空盘子的食客那里。（注意，无论有多少食客一开始有煎饼，总有无限多的空盘子可用。）

第 3 分钟：什么都不做。这两位食客各自吃掉最后一块煎饼。

在第 2 组样例中，最优策略是不进行任何打断，让食客们连续吃 2 分钟即可吃完所有煎饼。

在第 3 组样例中，一位食客一开始有 4 块煎饼，其他人的盘子都是空的。最优策略是在第 1 分钟进行一次特殊分钟，将两块煎饼分给另一位空盘子的食客，然后在第 2、3 分钟什么都不做，让两位食客各自吃掉剩下的煎饼。

**数据范围**

- $1 \leq T \leq 100$。

**小数据集（9 分）**

- 时间限制：~~240~~ 5 秒。
- $1 \leq D \leq 6$。
- $1 \leq P_i \leq 9$。

**大数据集（12 分）**

- 时间限制：~~240~~ 10 秒。
- $1 \leq D \leq 1000$。
- $1 \leq P_i \leq 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1
3
4
1 2 1 2
1
4```

### 输出

```
Case #1: 3
Case #2: 2
Case #3: 3```

# 题解

## 作者：hlb44 (赞：1)

~~看来最优解被我抢了qwq…~~

[题目传送门](https://www.luogu.com.cn/problem/P13212)

容易发现，总时间由两部分构成：

特殊分钟数（$k$）：转移煎饼的次数。

正常分钟数（$m$）：由转移后最大的煎饼堆决定。

我们成功的将问题转化成求最小的 $k + m$。

最开始不进行任何转移，所以总时间为最大的煎饼数量。

可以优化：

我们对于每个煎饼堆，它需要被分割成若干份，每份应该小于等于 $m$，所需的转移次数为分割份数减 $1$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define fo(i,begin,end) for(int i=begin;i<=end;++i)
#define of(i,begin,end) for(int i=begin;i>=end;--i)
#define fos(i,begin,end,ADD) for(int i=min(begin,end);i<=max(begin,end);i+=ADD)
#define ofs(i,begin,end,ADD) for(int i=max(begin,end);i>=min(begin,end);i-=ADD)
#define debug(val) cout<<#val<<':'<<(val)<<'\n'
#define debug_1(name,i,x) cout<<#name<<"["<<i<<"]:"<<x<<'\n';
#define debug_2(name,i,j,x) cout<<#name<<"["<<i<<"]["<<j<<"]:"<<x<<"\n";
#define ll long long
int main() {
	int T;
	cin>>T;
	for(int cn=1; cn<=T; ++cn) {
		int D;
		cin>>D;
		vector<int>P(D);
		for(int i=0; i<D; ++i) {
			cin>>P[i];
		}
		int max_p=*max_element(P.begin(),P.end());
		int ans=max_p;//初始时间：不进行任何转移
		for(int m=1; m<max_p; ++m) {
			int k=0;//总转移次数
			for(int pi:P) {
				if(pi<=m)continue;//无需转移
//计算pi需要分成多少份（每份≤m）
				int parts=(pi+m-1)/m;//等价于ceil(pi/m)
				k+=parts-1;//转移次数=份数-1
			}
			ans=min(ans,k+m);
		}
		cout<<"Case #"<<cn<<": "<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：Dicer_L (赞：0)

### 前情提要

今天学了整除分块，想找一道题练练手。

### 简述题意

在序列中有 $n$ 个数，进行操作最终使每个数变成 0。操作方式有两种，一是序列每个数全部减一，二是选择一个数将它分成两个数，删除原来的数并将两个新数插入序列。两种操作的时间消耗都是 1，求最少消耗时间。

### 思路

核心矛盾：操作 1 会减小数，操作 2 会使后续减小数速度变快。需平衡操作 1 和操作 2。

那么如何平衡呢，一开始我想动态规划，但是一看数据范围和时间限制

> - 时间限制：240 秒。
> - $1 \leq D \leq 6$。
> - $1 \leq P_i \leq 9$。

好了不用想了，直接暴力枚举。

外层循环枚举操作 1 的次数。而操作 1 的最多次数就是原序列中最大值。

内侧循环枚举序列中每个数，可以通过操作 1 的次数和数的大小推断出操作 2 的次数。

操作 1 的次数加操作 2 的次数即为所花费的时间。

通过外层循环记录所花费的时间的最小值。

确实可以继续优化，但是没必要，到目前为止我是最优解。

### 附上代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int T,D;
signed main(){
    ios::sync_with_stdio(false);
    cin>>T;
    for(int j=1;j<=T;j++){
        cin>>D;
        vector<int> P(D);
        for(int i=0;i<D;i++)  cin>>P[i];
        int maxn=*max_element(P.begin(),P.end());
        int minn=maxn;
        for (int m=1;m<maxn;m++){
            int f=0;
            for(int p : P) f+=(p+m-1)/m-1;
            if(f+m<minn)  minn=f+m;
        }
        cout<<"Case #"<<j<<": "<<minn<<'\n';
    }
}
```

---

