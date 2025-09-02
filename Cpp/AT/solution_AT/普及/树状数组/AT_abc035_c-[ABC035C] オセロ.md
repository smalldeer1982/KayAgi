# [ABC035C] オセロ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc035/tasks/abc035_c

黒の面に`0`、白の面に`1`が書かれた $ N $ 個のオセロの駒が、どの駒も黒の面が上を向くように一列に並べられています。その後、ある区間にある駒を全て裏返すという操作が $ Q $ 回だけ行なわれました。 具体的には $ i $ 回目の操作においては、左から $ l_i $ 番目の駒から $ r_i $ 番目の駒までの駒全てが裏返されました。

最終的な盤面を求めてください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1≦N,Q≦2,000 $ を満たすデータセットに正解した場合、 $ 60 $ 点が与えられる。
- 追加制約のないデータセットに正解した場合は、追加で $ 40 $ 点が与えられ、合計 $ 100 $ 点が得られる。

### Sample Explanation 1

\- 盤面ははじめ`00000`です。 - $ 1 $ 回目の操作により、 盤面は`11110`となります。 - $ 2 $ 回目の操作により、 盤面は`10001`となります。 - $ 3 $ 回目の操作により、 盤面は`10101`となります。 - $ 4 $ 回目の操作により、 盤面は`01010`となります。 - 最終的な盤面である`01010`が求める答えです。 - このケースは部分点の追加制約を満たします。

### Sample Explanation 2

\- このケースは部分点の追加制約を満たします。

## 样例 #1

### 输入

```
5 4
1 4
2 5
3 3
1 5```

### 输出

```
01010```

## 样例 #2

### 输入

```
20 8
1 8
4 13
8 8
3 18
5 20
19 20
2 7
4 9```

### 输出

```
10110000011110000000```

# 题解

## 作者：CleverRaccoon (赞：2)

### 前言

是看到题目名称 [オセロ（点开有惊喜）](https://music.163.com/#/song?id=2085560360) 才来做这道题的捏。

题解区好像还没有这种做法。这道题和 [P5057](https://www.luogu.com.cn/problem/P5057) 的区别在于，这道题只需要最后询问一次即可，因此不需要使用线段树或树状数组，只需要使用最基础的前缀和维护即可解决。

### 思路

每次修改时，和前缀和模板一样：

```cpp
++a[l],--a[r+1];
```

然后生成前缀和数组：

```cpp
for(int i=1;i<=n;i++)a[i]+=a[i-1];
```

得到前缀和的数组后，如何将其处理为答案呢？

可以发现，操作次数为奇数的位置，是背面的，即 $1$；反之，操作次数为偶数的位置，是正面的，即 $0$，所以只需要判断奇偶性即可（这段代码中，使用了 `&` 运算符，即位运算中的与运算符。奇数的二进制表示中，末位为 $1$；偶数末位为 $0$。奇数 `xxxxxxx1` 与上一个 `00000001` 结果是 $1$；偶数 `xxxxxxx0` 与上一个 `00000001` 结果是 $0$。反过来说，一个数 `&1` 如果结果为 $1$，那么说明这一数是奇数；反之为偶数）：

```cpp
cout<<(a[i]&1);
```

### 注意

Atcoder 评测姬输出的最后需要换行，否则会喜提零分。

### 代码

以下为简短版代码，提交时的代码见 [这里](https://www.luogu.com.cn/paste/p2khfrc9)。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=200007;
int n,q,a[N];
int main(){
	cin>>n>>q;
	for(int l,r;q--;)cin>>l>>r,++a[l],--a[r+1];	// 前缀和处理
	for(int i=1;i<=n;i++)a[i]+=a[i-1],cout<<(a[i]&1);cout<<'\n';	// 累加前缀和并输出正反面
	return 0;
}
```

### 后记

> 是黑非白，先决定好吧。

---

## 作者：庄nnnn额 (赞：1)

这题不就跟 [P5057](https://www.luogu.com.cn/problem/P5057) 差不多么。。。

由于区间异或满足区间加法原则，可以使用树状数组，把两个函数改动一下，就可以 AC 了。在代码里有标出改动处。

## Code
```
#include <bits/stdc++.h>
using namespace std;
int n;
bool c[500005];
inline int lowbit(int n){
	return n&(-n);
}
void update(int x){
	while(x<=n){
		c[x]^=1;//①
		x+=lowbit(x);
	}
}
bool getsum(int x){
	bool ans=0;
	while(x){
		ans^=c[x];//②
		x-=lowbit(x);
	}
	return ans;
}
int main(){
	int m,op,x，y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		update(x);
		update(y+1);
	}
	for(int i=1；i<=n；i++)printf("%d",getsum(i));
	putchar('\n');
	return 0;
}
```
然后，就：
[![](https://www.luogu.com.cn/images/congratulation.png)](https://www.luogu.com.cn/record/68988324)

---

## 作者：Otomachi_Una_ (赞：1)

首先，这道题暴力方法时间复杂度为 $O(NQ)$ 不过这种方法会稳稳地超时。

介绍一下差分的方法。

考虑其翻转范围为一个连续的区间，可以使用差分。

用 $a_i$ 来记录第 $i$ 张牌与第 $i-1$ 张牌所表示数字是否相同。

在进行操作时直接把 $a_l$ 与 $a_{r+1}$ 的数值翻转 ($0 \leftrightharpoons 1$)

最后直接计算答案即可。

## _code_

```cpp
#include<iostream>
using namespace std;
const int MAXN=2e5+5;
int n,q,l,r;
bool a[MAXN];
bool t;
int main(){
	cin>>n>>q;
	while(q--){
		cin>>l>>r;
		a[l]=!a[l];
		a[r+1]=!a[r+1];
	}
	for(int i=1;i<=n;i++){
		if(a[i])
			t=!t;
		cout<<t;
	}
	cout<<endl;
}
```


---

