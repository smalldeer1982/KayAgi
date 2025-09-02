# Matryoshkas

## 题目描述

Matryoshka is a wooden toy in the form of a painted doll, inside which you can put a similar doll of a smaller size.

A set of nesting dolls contains one or more nesting dolls, their sizes are consecutive positive integers. Thus, a set of nesting dolls is described by two numbers: $ s $ — the size of a smallest nesting doll in a set and $ m $ — the number of dolls in a set. In other words, the set contains sizes of $ s, s + 1, \dots, s + m - 1 $ for some integer $ s $ and $ m $ ( $ s,m > 0 $ ).

You had one or more sets of nesting dolls. Recently, you found that someone mixed all your sets in one and recorded a sequence of doll sizes — integers $ a_1, a_2, \dots, a_n $ .

You do not remember how many sets you had, so you want to find the minimum number of sets that you could initially have.

For example, if a given sequence is $ a=[2, 2, 3, 4, 3, 1] $ . Initially, there could be $ 2 $ sets:

- the first set consisting of $ 4 $ nesting dolls with sizes $ [1, 2, 3, 4] $ ;
- a second set consisting of $ 2 $ nesting dolls with sizes $ [2, 3] $ .

According to a given sequence of sizes of nesting dolls $ a_1, a_2, \dots, a_n $ , determine the minimum number of nesting dolls that can make this sequence.

Each set is completely used, so all its nesting dolls are used. Each element of a given sequence must correspond to exactly one doll from some set.

## 说明/提示

The first test case is described in the problem statement.

In the second test case, all matryoshkas could be part of the same set with minimum size $ s=7 $ .

In the third test case, each matryoshka represents a separate set.

## 样例 #1

### 输入

```
10
6
2 2 3 4 3 1
5
11 8 7 10 9
6
1000000000 1000000000 1000000000 1000000000 1000000000 1000000000
8
1 1 4 4 2 3 2 3
6
1 2 3 2 3 4
7
10 11 11 12 12 13 13
7
8 8 9 9 10 10 11
8
4 14 5 15 6 16 7 17
8
5 15 6 14 8 12 9 11
5
4 2 2 3 4```

### 输出

```
2
1
6
2
2
2
2
2
4
3```

# 题解

## 作者：Lovely_Elaina (赞：7)

### 思路

STL 大法好。

使用桶 + 贪心思想。

说白了就是 map + 贪心。

每组测试数据都会输入一个数列 $a$。

开一个 map 名字为 $m$，$m_i$ 表示 $a_i$ 出现的次数。

然后将 $a$ 排序，从大到小遍历一次，对于每次遍历：

1. 如果 $m_{a_i}$ 为 $0$，遍历下一个，否则 $ans$（输出的值）加 $1$；
2. 定义一个值 $p=a_i$；
3. 对于当前遍历的值，每次遍历将 $m_p$ 减 $1$；
4. 遍历一个区间，这是一个连续的区间，从 $p$ 开始往前遍历，当 $m_{p-1}$ 不为 $0$ 时继续往前遍历，同时 $m_p$ 减 $1$。

最后输出 $ans$。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200005;

inline int read(){
    int f=1,x=0;char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    x *= f; return x;
}

int t,n,a[N];
map<int,int> m;

int main() {

    t = read();
    while(t--){
        n = read();
        for(register int i = 1; i <= n; i++){
            a[i] = read();
            m[a[i]]++;
        }
        sort(a+1,a+n+1);
        int ans = 0;
        for(register int i = n; i >= 1; i--){
            if(!m[a[i]]) continue;
            int p = a[i];
            m[p]--;
            while(1){
                if(m[p-1] > 0)
                    p--,m[p]--;
                else break;
            }
            ans++;
        }
        printf("%d\n",ans);
    }
    return 0;

}
```

---

## 作者：arrow_king (赞：2)

用不着平衡树，STL map 轻松水过。

## 思路

开一个 `map<int,int>` 类型的映射 $mp$，$mp[i]$ 表示数组中数字 $i$ 出现的个数。

每输入一个数，map 中对应元素加 $1$。

随后将整个数组排序，每次从 $n$ 到 $1$ 枚举。每次检测 $mp$ 中是否存在比当前数小 $1$，如果是的话将这个数对应的 $mp$ 值减 $1$，同时这个数也减 $1$。本次检测结束后，答案加 $1$。

因为每个数只会被删去一次，所以均摊复杂度 $\mathcal O(n\log n)$。

## 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
#define ll long long
#define il inline
il ll read() {
	ll x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') {f=-1;} c=getchar();}
	while(c>='0'&&c<='9') {x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return x*f;
}
int t,n;
int a[200005];
map<int,int> mp;
int main() {
	t=read();
	while(t--) {
		n=read();
		for(int i=1;i<=n;i++) {
			a[i]=read();
			mp[a[i]]++;
		}
		sort(a+1,a+n+1);
		int ans=0;
		for(int i=n;i>=1;i--) {
			if(mp[a[i]]==0) continue;
			int now=a[i];
			mp[now]--;
			while(1) {
				if(mp[now-1]>0) {
					now--;
					mp[now]--;
				}
				else break;
			}
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：loser_seele (赞：2)

观察样例，可以发现答案的一种构造方法：

首先显然数组的顺序不影响答案，于是先排序。

定义一个极长区间为一个不能往两端扩展的区间，例如如果选定元素为 $ [2,3,4] $ 且数组内没有 $ 1 $ 和 $ 5 $，则这些元素被称为极长区间。

一个做法是不断找出极长区间后删除，最后统计一共删除了多少次即可。

我们思考为什么这样是对的：

如果原数组中极长区间间没有公共元素则显然上述做法正确。

设原数组中有两个极长区间有公共元素，则我们可以构造出另一种方案：设两个极长区间为 $ a,b $，则可以取 $ a \cap b,a \cup b $ 为新的答案即可使得新区间不含公共元素，不难证明上面两个集合仍然是极长区间。

于是排序后每次找出仍存在的最小元素，暴力扩展极长区间，扩展的过程中删除，直到区间右端点不存在，统计这个过程执行的次数即为答案。

因为每个元素最多插入一次删除一次则总时间复杂度 $ \mathcal{O}(n\log{n}) $，来自排序的时间复杂度。

因为值域 $ 10^9 $ 可以离散化，这里用 map 实现。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[2000020];
map<int,int>cnt;
main()
{
int T;
cin>>T;
while(T--)
{
	int n;
	cin>>n;
	cnt.clear();
	for(int i=1;i<=n;i++)
		cin>>a[i],cnt[a[i]]++;
	sort(a+1,a+n+1);
	int ans=0;
	for(int i=1;i<=n;i++)
	if(cnt[a[i]])
	{
		int now=a[i];
		while(cnt[now])
			cnt[now]--,now++;
	ans++;
	}
	cout<<ans<<'\n';
}
}
```


---

## 作者：SuperCowHorse (赞：1)

>此题是我赛时过得最不可思议的一题。

---
### 题意
将 $n$ 个数分成尽可能多的组，要求：每组从大到小排序后依次相差 $1$。

---
### 思路
考虑进行贪心。

贪心策略很容易想到：对于**没用过的数**中最小的值开始枚举，每次枚举都加 $1$，并开个 $\operatorname{map}$ 存储，如果遍历到了就减 $1$。

其他好说，问题来了：如何求没有用过的最小值呢？

再仔细联想。用过一个数表示**把他删除**。有什么数据结构支持插入、删除和最小值查询呢？~~平衡树！~~

所以：~~此题是我赛时过得最不可思议的一题。~~

根据[普通平衡树](https://www.luogu.com.cn/problem/P3369)模板，我们可以愉快的 AC 此题。（最小值转化成区间第 $k$ 小，其实就是区间第 $1$ 小）

Code:[link](https://codeforces.com/contest/1790/submission/190830944)

---

