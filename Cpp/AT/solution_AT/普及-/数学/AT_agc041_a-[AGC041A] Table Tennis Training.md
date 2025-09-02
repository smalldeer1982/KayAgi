# [AGC041A] Table Tennis Training

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc041/tasks/agc041_a

$ 2N $ 人の卓球選手が、$ 1 $ から $ N $ までの番号がついた $ N $ 台の卓で実戦練習を行います。

練習は複数の *ラウンド* からなります。 各ラウンドでは、選手たちは $ 1 $ 卓につき $ 1 $ ペアの合計 $ N $ ペアに分かれます。 そして、各ペアの選手同士で試合を行い、$ 1 $ 人が勝利してもう $ 1 $ 人が敗北します。

卓 $ X $ で勝利した選手は、次のラウンドでは卓 $ X-1 $ で試合を行います。 ただし、卓 $ 1 $ で勝利した選手は卓 $ 1 $ に留まります。

同様に、卓 $ X $ で敗北した選手は、次のラウンドでは卓 $ X+1 $ で試合を行います。 ただし、卓 $ N $ で敗北した選手は卓 $ N $ に留まります。

ある $ 2 $ 人の選手は友達同士で、最初のラウンドの試合を異なる卓 $ A,\ B $ で行います。 彼らは十分な腕前を持ち、各試合での自分の勝敗を自由に操れるとします。 この $ 2 $ 人同士で試合を行えるまでに、最小で何回のラウンドが必要でしょうか？

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^{18} $
- $ 1\ \leq\ A\ <\ B\ \leq\ N $
- 入力中のすべての値は整数である。

### Sample Explanation 1

最初のラウンドで $ 1 $ 人目が敗北して $ 2 $ 人目が勝利すると、$ 2 $ 人とも卓 $ 3 $ に移動し、次のラウンドでは彼ら同士で試合を行えます。

### Sample Explanation 2

$ 2 $ 人とも $ 2 $ 連続で勝利すれば、両者とも卓 $ 1 $ に移れます。

## 样例 #1

### 输入

```
5 2 4```

### 输出

```
1```

## 样例 #2

### 输入

```
5 2 3```

### 输出

```
2```

# 题解

## 作者：_farawaystar_ (赞：3)

#### 题意简述

1. 乒乓球，每桌 $2$ 人。每轮比赛后，必有一赢一输。

2. $x(1<x<n)$ 桌赢者去到 $x+1$ 桌，输者去到 $x-1$ 桌。

3. $1$ 桌输者不动，赢者去到 $2$ 桌； $n$ 桌赢者不动，输者去到 $n-1$ 桌。

#### 题目分析：

分情况讨论：

1. 当两者位置差为偶数时，就只需要每次两人都向中间靠近一个台即可，需要 $(b-a)/2$ 步。

2. 当两者位置差为奇数时，则必须要到 1 台或 n 台停留一次，两者先同时往近的一边移动，需要 $\min(n-b,a-1)$ 次移动，加上停留，共移动 $\min( n-b , a-1 )+1$ 次，即 $\min(n-b+1,a)$ 次，就成了情况 1 ，两者位置差 $b-a-1$ 台，总共移动 $\min(n-b+1,a)+(b-a-1)/2$ 次。

代码：

```cpp

#include<iostream>
using namespace std;
int main(){
	long long n,a,b;
	cin>>n>>a>>b;
	(b-a)%2==1?cout<<min(n-b+1,a)+(b-a-1)/2:cout<<(b-a)/2;//三目运算代表上面两种情况
	return 0;
} 

```

附卡常代码：

```cpp

#include<cstdio>
#include<iostream>
using namespace std;
inline long long read(){ 
	register long long x=0,f=1;
	register char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
inline void print(long long x){
	if(x<0)putchar('-'),x=~x+1;
	if(x>9)print(x/10);
	putchar(x%10+'0');
}
int main(){
   	register long long n,a,b;
   	n=read(),a=read(),b=read();
   	(b-a)&1==1?print(min(n-b+1,a)+((b-a-1)>>1)):print((b-a)>>1);
	return 0;
}

```

谢谢大家！！！

---

## 作者：123456zmy (赞：2)

题意：  
有两个人，他们在分别在两个长度为 $N$ 的队里，每次可以往前或往后移动 $1$ 位（第一个和最后一个可以不动，不能从 $1$ 到 $n$ 也不能从 $n$ 到 $1$）求至少要几次两人编号才能相同。(~~极度简化的题意~~)
___
如果两人编号奇偶性相同则往中间走，否则在 $1$ 或 $n$ 卡一下再向中间走。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b;
int main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	if((b-a)&1)printf("%lld",min((unsigned long long)((n<<1)-a-b+1),(unsigned long long)(a+b-1))>>1);
	else printf("%lld",b-a>>1);
	printf("\n");
	return 0;
}
```

---

## 作者：陪你看流星雨 (赞：1)

题意就是说赢了的去上一张桌，输的去下一张桌，在第一张桌和第 N 张桌可以不动

如果 A 桌和 B 桌都是单数或都是双数，直接向中间靠就好

上代码



------------
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	long long n,a,b;//不开 long long 见祖宗
	cin>>n>>a>>b;//输入
	if((b-1-a)%2==1) //判断是不是单数
	{ 
		cout<<(b-a-1)/2+1;
		return 0;
	}
	cout<<min(a,n+1-b)+(b-1-a)/2;//细节输出
	return 0;//好习惯
}





---

## 作者：Maysoul (赞：0)

### 题意：
这道题并非是模拟题，而是一道公式总结题。

第  $  X  $  桌比赛的获胜者在  $  X-1  $  桌比赛，但  $  1  $  桌比赛的获胜者仍然留在  $  1  $  桌。

同样，下一轮在第  $  X  $  桌比赛的失败者在  $  X+1  $  桌比赛，但第  $  N  $  台比赛的失败者仍然留在第  $  N  $  桌。
### 分析：
如果 AB 二人位置之差是奇数，那么一个只管获胜，一个只管失败，移动  $  (a-b)/2  $  次就能聚合。

如果 AB 二人位置之差是偶数，那么他们就往边界靠拢，首先两个人都胜利/失败，直至一个人靠拢至边界，然后那个人位置保持不变，直至另一个人也靠拢至边界。

公式有了，写罢。
### AC Code：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long a,b,n;//亲测，int类型过不去的
	cin>>n>>a>>b;
	if(abs(a-b)%2==0)//是a,b的绝对值，因为其顺序未知。
	{
		cout<<abs(a-b)/2<<endl;//同理
	}
	else
	{
		cout<<min(n-b+1,a)+(b-a-1)/2;
	}
	return 0;
}
```
### 写在后边：
~~这是这篇题解第七次提交。之前因为格式问题被打回六次。~~

~~关于 LaTeX ，我尽力了。~~

对不起各位审核君QAQ。



---

## 作者：零殇 (赞：0)

#### 题意

有 $ n $ 个位置，第一个人在第 $ a $ 个位置，第二个人在第 $ b $ 个位置。每轮两个人都可以到前或到后一个位置，边界可以不动。求最少要多少轮会到同一个位置。

#### 思路

因为求的是最少轮数，所以两个人最好是一直向中间靠近的。

因为最后要到同一个位置，所以中间一定要有奇数个位置。

分情况讨论。

如果两个位置中间的位置有奇数个，那么就输出 $(b-a-1)÷2+1$ 。

如果中间有偶数个位置，那么我们就必须讲一个挪到边界，等待 $ 1 $ 轮。然后就变成了奇数个。

移动到边界并等待 $ 1 $ 轮的次数是 $ \min(a,n-b+1) $ ，此时中间的位置数减去 $ 1 $ ，所以答案就再加上 $(b-a-1)/2$ 。

上代码：
```
#include<bits/stdc++.h>
using namespace std;
int main() {
	long long n,a,b;
	scanf("%lld%lld%lld",&n,&a,&b);
	if((b-a-1)%2==1) { 
		cout<<(b-a-1)/2+1<<endl;
		return 0;
	}
	cout<<min(a,n-b+1)+(b-a)/2<<endl;
	return 0;
}
```
完结撒花~

---

## 作者：shenmadongdong (赞：0)

分类讨论。

如果 $A$ 和 $B$ 奇偶性一样，那么显然应该第一个人全输第二个人全赢，答案是 $\frac{B-A}{2}$ 。

如果 $A$ 和 $B$ 奇偶性不一样，注意到只有在第 $1$ 桌赢或者第 $n$ 桌输时才能让 $A$ 和 $B$ 的奇偶性一致。

假定第一个人在 第 $1$ 桌赢，那么需要 $A - 1$ 局到达第一桌，然后在赢上一场，此时 $A$ 和 $B$ 的差值是 ${B-A-1}$ 。然后可以转化为前一个问题，总答案为 $A - 1 + 1 + \frac{B-A-1}{2}$ 。

另一种情况同理，此时的答案为 $N - B + 1 + \frac{B-A-1}{2}$ 。所以 $A$ 和 $B$ 奇偶性不同时的答案为 $\min(A - 1 , N - B) + 1 + \frac{B-A-1}{2}$ 。

代码应该不用解释了。

```cpp
#include<bits/stdc++.h>
long long n,a,b;
int main()
{
	std::cin>>n>>a>>b;
	if (b-a&1ll) std::cout<<std::min(2*n+1-b-a>>1,b+a>>1);
    else std::cout<<(b-a>>1);
    return 0;
}
```

---

