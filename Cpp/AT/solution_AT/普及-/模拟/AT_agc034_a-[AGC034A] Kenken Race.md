# [AGC034A] Kenken Race

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc034/tasks/agc034_a

$ N $ 個の一列に並んだマス目があり、左から順に番号 $ 1,\ 2,\ ...,\ N $ がついています。長さ $ N $ の `.`, `#` からなる文字列 $ S $ が与えられ、$ S $ の $ i $ 文字目が `#` のときマス目 $ i $ には岩が置かれており、$ S $ の $ i $ 文字目が `.` のときマス目 $ i $ には何も置かれていません。

最初、マス目 $ A $ にすぬけ君、$ B $ にふぬけ君がいます。

あなたは以下の操作を好きなだけ繰り返すことができます。

- すぬけ君かふぬけ君を選び、$ 1 $ マス右か $ 2 $ マス右にジャンプさせる。このときジャンプ先にマスが存在しなければならず、またそのマスに岩が置かれていたりもう一人がいてはならない。

あなたはこの操作を繰り返し、マス目 $ C $ にすぬけ君が、$ D $ にふぬけ君がいるようにしたいです。

このようなことが可能かどうかを判定してください。

## 说明/提示

### 制約

- $ 4\ \leq\ N\ \leq\ 200,000 $
- $ S $ は `.`, `#` からなる長さ $ N $ の文字列
- $ 1\ \leq\ A,\ B,\ C,\ D\ \leq\ N $
- マス目 $ A,\ B,\ C,\ D $ に岩は置かれていない
- $ A,\ B,\ C,\ D $ はすべて異なる
- $ A\ <\ B $
- $ A\ <\ C $
- $ B\ <\ D $

### Sample Explanation 1

たとえば、以下のように移動させれば良いです(すぬけ君、ふぬけ君を `A`, `B` で表します) ``` A#B.#.. A#.B#.. .#AB#.. .#A.#B. .#.A#B. .#.A#.B .#..#AB ```

## 样例 #1

### 输入

```
7 1 3 6 7
.#..#..```

### 输出

```
Yes```

## 样例 #2

### 输入

```
7 1 3 7 6
.#..#..```

### 输出

```
No```

## 样例 #3

### 输入

```
15 1 3 15 13
...#.#...#.#...```

### 输出

```
Yes```

# 题解

## 作者：Strelitzia_ (赞：4)

## 题目大意

------------
一排 $n$ 个格子，每个格子可走或不可走。有两个点，一个起点为 $A$ 终点为 $C$，一个起点为 $B$ 终点为 $D$，每次只能跳一个或两个格子，问这两个点能不能都走到终点。

## 思路

------------
首先，最多跳两个格子，那么可以先从起点到终点扫一遍，如果发现有连着两个格子不能走，那就到不了。

然后我们分类讨论一下：如果 $C$ 在 $D$ 前面，那么先让第二个点走，这时就变成两个点能不能单独到达。此时，用上面的方法扫一遍直接结束。

另一种情况：$D$ 在 $C$ 前面，那么这时就要考虑第二个点对第一个点的影响了。我们还是先扫一遍，同时用一个变量记录 $D$ 周围是否有障碍，因为这时就需要让第一个点和第二个点交换位置了。

然后再扫一遍，如果有连着的 $3$ 个可走的格子，这样就可以让他们交换位置；再判断一下即可。

代码：

```cpp
#include<bits/stdc++.h>
#define lxl long long
#define db double
#define N 114514
#define M 1919810

using namespace std;
const double lxy=-1;

int n,a,b,c,d;
char s[N*2];
int pan=1;

int main(){
	scanf("%d%d%d%d%d%s",&n,&a,&b,&c,&d,s+1);
	if(c<d){
		for(int i=a;i<=d;i++){
			if(s[i]=='#'&&s[i+1]=='#'){
				printf("No\n");
				return 0;
			}
		}
		printf("Yes\n");
		return 0;
	}
	for(int i=a;i<=c;i++){
		if(s[i]=='#'&&s[i+1]=='#'){
			printf("No\n");
			return 0;
		}
		if(s[i]=='#'&&(i+1==d||i-1==d)) pan=0;
	}
	for(int i=b;i<d;i++)
	 if(s[i-1]=='.'&&s[i]=='.'&&s[i+1]=='.') pan=1;
	if(pan){
		printf("Yes\n");
		return 0;
	}
	printf("No\n");
	return 0;
}
```


---

## 作者：sudaJones (赞：1)

[题目地址](https://www.luogu.com.cn/problem/AT4991)

管理大神放过我。

为什么我总是要看好多遍才能看懂 $ AT $ 的题目？

本蒟蒻第二篇题解。

借鉴了 @火车司机 的题解，非常感谢。

### 题目意思：

有 $ n $ 个格子，分别为 $ S_1 $,$ S_2 $,$ S_3 $...$ S_n $。

每个格子为  ```#```  或者  ``` .```。

 ``` # ```  不能踩， ``` . ```  能踩。

有两个棋子，分别在 $ A $ 和 $ B $。

我们要把他们挪到 $ C $ 和 $ D $。

要求：

> 棋子每次跳  1 或  2 步，只能向右移。

> 不可以在障碍处停留，不能跳到已经有棋子的格子。

能否使 $ A $ 中的棋子最终到达 $ C $，$ B $ 中的棋子最终到达 $ D $。

保证$ A < B $,$ A < C $,$ B < D $。


### 样例分析：

```
7 1 3 6 7
.#..#..
```

```
Yes
```
过程：

```
 A # B . # . . 
 A # . B # . . 
 . # A B # . . 
 . # A . # B . 
 . # . A # B . 
 . # . A # . B 
 . # . . # A B 
```

### 思路：

分类讨论:

当 $ c < d $ 时，$ B $ 不会影响 $ A $,直接分开考虑单独能不能到达即可。

当 $ d < c $ 时，先看 $ B $ 到 $ D $ 之后会不会影响 $ A $ 不能到 $ C $。

假如 **会** 的话，去寻找在 $ B $ 到 $ D $ 之间有没有连续  3  个及以上的空位能让他们交换相对位置。

交换位置之后就直接类似第一种情况分开考虑即可。

### 代码分析：

1. 读入

```cpp
	cin>>n>>a>>b>>c>>d;
	for(int i=1;i<=n;i++)cin>>s[i];
```

2. 第一种情况

```cpp
//以下是b不影响a时 
	if(c<d){
		for(int i=b; i<=d;i++)//有没有一定过不去的 
			if(s[i]=='#'&&s[i+1]=='#'){//如果连续两个障碍，就一定过不去 
				cout<<"No"<<endl;
				return 0;
			}
		for(int i=a;i<=c;i++)
			if(s[i]=='#'&&s[i+1]=='#'){//同理
				cout<<"No";
				return 0;
			}
		cout<<"Yes"<<endl;
		return 0;
	}
```

3. 第二种情况

```cpp
for(int i=b;i<=d;i++)
		if(s[i]=='#'&&s[i+1]=='#'){
			cout<<"No";
			return 0;
		}
	for(int i=a;i<=c&&f==1;i++)if((s[i]=='#'||i==d)&&(s[i+1]=='#'||i+1==d))f=0;
	if(f==1){
		cout<<"Yes";
		return 0;
	}
```
先是 $ B $。

```cpp
f=1;
	for(int i=b;i<d&&f==1;i++)if(s[i-1]=='.'&&s[i]=='.'&&s[i+1]=='.')f=0;
	if(f==1){
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=a;i<=c;i++)
		if(s[i]=='#'&&s[i + 1]=='#'){
			cout<<"No"<<endl;
			return 0;
		}
```

再是 $ A $。

```cpp
cout<<"Yes"<<endl;
```

最终符合。

$\color{Red}\colorbox{white}{注意：}$

1. 该题目中 $ Yes $ 和 $ No $ 不要全部大写。

2. 不要忘了 ```return 0;```。

### 最终代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,b,c,d,f=1;
char s[200007];
int main(){
	cin>>n>>a>>b>>c>>d;
	for(int i=1;i<=n;i++)cin>>s[i];
	//以下是b不影响a时 
	if(c<d){
		for(int i=b; i<=d;i++)//有没有一定过不去的 
			if(s[i]=='#'&&s[i+1]=='#'){//如果连续两个障碍，就一定过不去 
				cout<<"No"<<endl;
				return 0;
			}
		for(int i=a;i<=c;i++)
			if(s[i]=='#'&&s[i+1]=='#'){
				cout<<"No";
				return 0;
			}
		cout<<"Yes"<<endl;
		return 0;
	}
	//以下是分述判断 
	for(int i=b;i<=d;i++)
		if(s[i]=='#'&&s[i+1]=='#'){
			cout<<"No";
			return 0;
		}
	for(int i=a;i<=c&&f==1;i++)if((s[i]=='#'||i==d)&&(s[i+1]=='#'||i+1==d))f=0;
	if(f==1){
		cout<<"Yes";
		return 0;
	}
	f=1;
	for(int i=b;i<d&&f==1;i++)if(s[i-1]=='.'&&s[i]=='.'&&s[i+1]=='.')f=0;
	if(f==1){
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=a;i<=c;i++)
		if(s[i]=='#'&&s[i + 1]=='#'){
			cout<<"No"<<endl;
			return 0;
		}
	cout<<"Yes"<<endl;
	return 0;
}
```




---

## 作者：火车司机 (赞：0)

## 简要分析

分类讨论

当 $c<d$ 时，直接分开考虑单独能不能到达即可

当 $d<c$ 时，先看让 $b$ 到 $d$ 之后会不会使得 $a$ 不能到 $c$

假如会的话，去寻找在 $b$ 到 $d$ 之间有没有连续 $3$ 及以上的空位能让他们交换相对位置

能交换位置之后就直接类似第一种情况分开考虑即可

## 完整代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define ri register int
#define N 200005
using namespace std;
int n, a, b, c, d, f = 1;
char s[N];
signed main()
{
	scanf("%lld%lld%lld%lld%lld%s", &n, &a, &b, &c, &d, s + 1);
	if (c < d)
	{
		for (ri i = b; i <= d; ++i)
			if (s[i] == '#' && s[i + 1] == '#')
			{
				puts("No");
				return 0;
			}
		for (ri i = a; i <= c; ++i)
			if (s[i] == '#' && s[i + 1] == '#')
			{
				puts("No");
				return 0;
			}
		puts("Yes");
		return 0;
	}
	for (ri i = b; i <= d; ++i)
		if (s[i] == '#' && s[i + 1] == '#')
		{
			puts("No");
			return 0;
		}
	for (ri i = a; i <= c && f; ++i)
		if ((s[i] == '#' || i == d) && (s[i + 1] == '#' || i + 1 == d))
			f = 0;
	if (f)
	{
		puts("Yes");
		return 0;
	}
	for (ri i = b; i < d && !f; ++i)
		if (s[i - 1] == '.' && s[i] == '.' && s[i + 1] == '.')
			f = 1;
	if (!f)
	{
		puts("No");
		return 0;
	}
	for (ri i = a; i <= c; ++i)
		if (s[i] == '#' && s[i + 1] == '#')
		{
			puts("No");
			return 0;
		}
	puts("Yes");
	return 0;
}
```


---

