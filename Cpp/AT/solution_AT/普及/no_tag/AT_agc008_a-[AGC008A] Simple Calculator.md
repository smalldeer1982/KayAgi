# [AGC008A] Simple Calculator

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc008/tasks/agc008_a

すぬけ君は電卓を持っています。 この電卓にはディスプレイと $ 2 $ 個のボタンが付いています。

最初、ディスプレイの値は整数 $ x $ です。 すぬけ君の目標は、ディスプレイの値を整数 $ y $ にすることです。 そのために、すぬけ君は次の $ 2 $ 個のボタンを好きな順番で何回か押すことができます。

- ボタン A : ディスプレイの値を $ 1 $ 増やす。
- ボタン B : ディスプレイの値の符号を反転する。

目標を達成するためにすぬけ君がボタンを押す回数の最小値を求めてください。 なお、整数 $ x $, $ y $ の値によらず、必ず目標を達成できることが示せます。

## 说明/提示

### 制約

- $ x $, $ y $ は整数である。
- $ |x|,\ |y|\ <\ =\ 10^9 $
- $ x $, $ y $ は相異なる。

### Sample Explanation 1

ボタン A を $ 10 $ 回押せばよいです。

### Sample Explanation 2

ボタン B を $ 1 $ 回押せばよいです。

### Sample Explanation 3

次の順でボタンを押せばよいです。 - ボタン B を $ 1 $ 回押す。 - ボタン A を $ 10 $ 回押す。 - ボタン B を $ 1 $ 回押す。

## 样例 #1

### 输入

```
10 20```

### 输出

```
10```

## 样例 #2

### 输入

```
10 -10```

### 输出

```
1```

## 样例 #3

### 输入

```
-10 -20```

### 输出

```
12```

# 题解

## 作者：qbf！ (赞：9)

提供一个不用分讨的做法。

容易发现乘 $-1$ 只会出现在第一步和最后一步。

因此我们枚举第一步和最后一步即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int A[2],B[2];
int main(){
	int x,y;
	scanf("%d%d",&x,&y);
	A[0]=x;
	A[1]=-x;
	B[0]=y;
	B[1]=-y;
	int ans=2e9;
	for(int i=0;i<=1;++i)
		for(int j=0;j<=1;++j)
			if(A[i]<=B[j])ans=min(ans,i+j+B[j]-A[i]);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Starlight_Glimmer (赞：4)

直接枚举的话，也不难 一波if搞定

但是显而易见的，对于A,x和y我们可以都不取反，取其中一个，或是都取反。对于B，如果x<=y 直接y-x就可以 但如果x>y 则必须二者都取反，再进行A操作 因为只能动x，并且只能加

可以将思路模式化，代码量大大减小，且便于阅读。

```cpp


#include<cstdio>
#include<algorithm>
using namespace std;
int s(int x,int y)
{
	if(x<=y) return y-x;
		else return x-y+2;
}
int main()
{
	int x,y;
	scanf("%d %d",&x,&y);
	printf("%d\n",min(s(x,y),min(s(-x,y)+1,min(s(x,-y)+1,s(-x,-y)+2))));
	return 0;
}
```

---

## 作者：xzy090626 (赞：1)

[原题传送门](https://www.luogu.com.cn/problem/AT2263)

---
## 题意
给你两个数 $x,y$，你的每次操作可以给 $x$ 加上 1 或者使它变成它的相反数，求最少需要多少次操作能使 $x=y$。

---
## 分析
我们可以从两种操作入手。

由于我们要使 $x=y$，因此我们分类讨论：
1. 当 $x,y$ 同号时，
在此基础上，我们讨论：
- 如果 $x,y > 0$，那么有两种情况：如果 $x>y$，那么我们无法通过只用第一种操作完成任务。必须先进行第二种操作，然后再反复执行第一种操作直到 $x=-y$，此时再次进行第二种操作，就完成了任务。而如果 $x<y$ 那就好办的多了，只需要反复执行第一种操作直到 $x=y$ 就可以了。当然，如果 $x=y$ 的话，就不需要进行任何操作了。
- 如果 $x,y<0$，此时与第一种情况完全一致。
2. 当 $x,y$ 异号时，继续讨论：
- 如果 $|x|>y$，
此时，如果 $x>0，y<0$，那么需要先将 $x$ 进行第二种操作，于是 $x<y$，就可以将 $x$ 不断进行第一种操作直到 $x=y$。如果 $x<0,y>0$，那么需要先不断进行第一种操作，再进行一次第二种操作，事实上与第一种情况是刚好颠倒了一下。这个时候，我们会发现共进行了 $｜a+b｜+1$ 次操作。
- 如果 $|x|<y$，此时同理，仍然需要进行 $｜x+y｜+1$ 次操作。
3. 不要忘记，此外还有一种情况，那就是 $x,y$ 中出现了 0。此时，容易知道，共需要进行 $｜a-b｜$ 次操作。

以上就是对于本题的全部分析。容易得出，我们只需要运用分支结构进行判断，就可以完成目标。

---
## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int main(){
	cin>>a>>b;
	int k = abs(a-b);
	if(a==b) cout<<0; //此时 a = b
	else if(!(a&&b)){ //此时 a,b 中有 0
		if(a>b) cout<<k+1;
		else cout<<k;
	}
	else if((a>0&&b>0)||(a<0&&b<0)){ //此时 a,b 同号
		if(a<b) cout<<k;
		else cout<<k+2;
	}
	else cout<<abs(a+b)+1; //此时 a,b 异号
}
```
## 总结
本题是一道主要考察分支结构的题目，对代码能力与算法技巧没有太多的关系。然而，本题对选手的分类讨论能力（数学能力）却有很大的要求，需要选手具有较强的逻辑性。

---

## 作者：cjZYZtcl (赞：1)

## if语句练手题
### 我们可以分类讨论：
- 当 $x=y$ 时，输出0（不用改变）
- 当 $x+y=0$（也就是 $x=-y$）时，输出1（取相反数）
- 当 $x=0$ 时：
  - 如果 $y>0$，输出 $y-x$（一直加）
  - 如果 $y<0$，输出 $-y+1$（加到 $-y$ 后取相反数）
- 当 $x>0$ 时：
  - 如果 $y>x$，输出 $y-x$（一直加）
  - 如果 $y<x$ 且 $y>0$，输出 $x-y+2$（先取相反数，然后加到 $-y$，再取相反数）
  - 如果 $y=0$，输出 $x-y+1$（先取相反数，然后加到 $y$）
  - 如果 $y<0$，输出 $\left|\ -x-y\ \right|+1$（取反和增加两步的先后看 $y$ 的大小定）
- 当 $x<0$ 时：
  - 如果 $y<x$，输出 $x-y+2$（先取反，然后加到 $-y$，再取反）
  - 如果 $y>x$ 且 $y\le0$，输出 $y-x$（一直加）
  - 如果 $y>0$，输出 $\left|\ -x-y\ \right|+1$（取反和增加两步的先后看 $y$ 的大小定）

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read(){
	int x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * m;
}
inline void write(int x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main(){
	int x = read(), y = read();
	if(x == y){
		write(0);
	}
	else if(x == -y){
		write(1);
	}
	else{
		if(x == 0){
			if(y > 0) write(y);
			else write(-y + 1);
		}
		else if(x > 0){
			if(y > x) write(y - x);
			else if(y > 0) write(x - y + 2);
			else if(y == 0) write(x - y + 1);
			else write(abs(-x - y) + 1);
		}
		else{
			if(y < x) write(x - y + 2);
			else if(y <= 0) write(y - x);
			else write(abs(-x - y) + 1);
		}
	}
}
```


---

## 作者：RioBlu (赞：1)

本题题意：输入x,y

你可以

 * **把x变成x的相反数，操作次数加1**
 * **或者x加一，操作次数加1**

最少多少次操作就可以变成y呢？

枚举所有可能性即可
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,ans;
int main()
{
	cin>>a>>b;
	if(a==0||b==0)//有一个是0
	{
		if(a>b)//a>b
		{
			cout<<abs(a-b)+1<<endl;
			exit(0);
		}
		cout<<abs(a-b)<<endl;//a<=b
		exit(0);
	}
	if(a>0&&b>0)//都是正数
	{
		if(a<b)//a>b
		cout<<abs(a-b)<<endl;
		else
		cout<<abs(a-b)+2<<endl;
	}
	if(a>0&&b<0||a<0&&b>0)cout<<abs(abs(a)-abs(b))+1<<endl;//有一个是负数
	if(a<0&&b<0)//都是负数
	{
		if(a==b)cout<<0<<endl;//相等
		if(a>b)cout<<abs(abs(a)-abs(b))+2<<endl;//a>b
		if(a<b)cout<<abs(abs(a)-abs(b))<<endl;//a<b
	}
}
```

---

