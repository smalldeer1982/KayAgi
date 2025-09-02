# Number Game

## 题目描述

Ashishgup and FastestFinger play a game.

They start with a number $ n $ and play in turns. In each turn, a player can make any one of the following moves:

- Divide $ n $ by any of its odd divisors greater than $ 1 $ .
- Subtract $ 1 $ from $ n $ if $ n $ is greater than $ 1 $ .

Divisors of a number include the number itself.

The player who is unable to make a move loses the game.

Ashishgup moves first. Determine the winner of the game if both of them play optimally.

## 说明/提示

In the first test case, $ n = 1 $ , Ashishgup cannot make a move. He loses.

In the second test case, $ n = 2 $ , Ashishgup subtracts $ 1 $ on the first move. Now $ n = 1 $ , FastestFinger cannot make a move, so he loses.

In the third test case, $ n = 3 $ , Ashishgup divides by $ 3 $ on the first move. Now $ n = 1 $ , FastestFinger cannot make a move, so he loses.

In the last test case, $ n = 12 $ , Ashishgup divides it by $ 3 $ . Now $ n = 4 $ , FastestFinger is forced to subtract $ 1 $ , and Ashishgup gets $ 3 $ , so he wins by dividing it by $ 3 $ .

## 样例 #1

### 输入

```
7
1
2
3
4
5
6
12```

### 输出

```
FastestFinger
Ashishgup
Ashishgup
FastestFinger
Ashishgup
FastestFinger
Ashishgup```

# 题解

## 作者：江户川·萝卜 (赞：12)

## [CF1370C Number Game](https://www.luogu.com.cn/problem/CF1370C) 题解

[博客食用更佳](https://www.luogu.com.cn/blog/258085/solution-cf1370c)

这道题其实翻译有些不准确。

>Divide n by any of its odd divisors **greater than 1**.
Subtract 1 from n if n is **greater than 1**.

`greater than 1` 也即 $>1$ 没翻译出来。

从而两个操作就变成了:

1. 将 $n$ 除以一个 $n$ 的大于一的奇数因子。
2. 如果 $n>1$ ，将 $n$ 减去 $1$。

获胜条件就是先得出 $1$。

-----
分情况考虑。
1. $n=1$

那先手就不能进行操作，所以无必胜策略。

2. $n=2$

先手有必胜策略。先手进行操作2，让后手陷入情况1。

3. $n$ 是奇数($n\not=1$) 

先手有必胜策略。先手进行操作1，因为一个数的本身也是它的因子，而且它是个奇数，所以可以除以它本身，让后手陷入情况1。

-----
4. $n$ 是偶数($n\not=2$)

偶数肯定不能进行操作2，因为`偶-1=奇`，让后手变成情况3，后手就赢了。

首先将 $n$ 表示成如下式子：
$$n=2^k\times m$$
其中 $m$ 为奇数。

继续分情况考虑。

4.1. $m=1$

也即 $n=2^k$。 

因为 $2^k$ 没有任何奇因子（除1外），所以只能进行操作2，后手就赢了。所以无必胜策略。

4.2. $m$ 是个质数

需要用到基础的判断质数方法。
```cpp
bool isprime(int n){
    if(n<2) return false;
    for(int i=2;i*i<=n;i++)
        if(n%i==0) return false;
    return true;
}
```
当 $m$ 是个质数时，操作1只能除以 $m$ ，剩下 $2^k$ 。

4.2.1. $k=1$

则除完 $m$后只剩下 $2$， 让后手变成情况2，后手就赢了，无必胜策略。

4.2.2. $k>1$

让后手陷入情况4.1，先手赢，有必胜策略。

4.3. $m$不是个质数

也即：
$$n=2^k\times p_1^{a_1}\times p_2^{a_2}\times\cdots\times p_m^{a_m}(m>1)$$

4.3.1. $k=1$

此时只要除以$p_1^{a_1}\times p_2^{a_2}\times\cdots\times p_i^{a_i}\times\cdots\times p_m^{a_m}\times p_i^{-1}(1\le i\le m)$就行了，

剩下$2\times p_i$ 让后手陷入情况4.2.1，先手赢，有必胜策略。

4.3.2. $k>1$

除以$p_1^{a_1}\times p_2^{a_2}\times\cdots\times p_m^{a_m}$，剩下 $2^k$，让后手陷入情况4.1，先手赢，有必胜策略。

所以情况4.3都有必胜策略。

----
### Code:
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int t,n;
string win[2]={"Ashishgup","FastestFinger"};
bool isprime(int n){
    if(n<2) return false;
    for(int i=2;i*i<=n;i++)
        if(n%i==0) return false;
    return true;
}//判断是否为质数
int main(){
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        if(n==1) cout<<win[1]<<endl;//1
        else if(n==2) cout<<win[0]<<endl;//2
        else if(n%2==1) cout<<win[0]<<endl;//3
        else{//4
            int x=n,cnt=0;
            while(x%2==0) x/=2,cnt++;
            if(x==1) cout<<win[1]<<endl;//4.1
            else if(isprime(x)){
                if(cnt==1) cout<<win[1]<<endl;//4.2.1
                else cout<<win[0]<<endl;//4.2.2
            }
            else cout<<win[0]<<endl;4.3
        }
    }
    return 0;
}
```

后话：感觉有些长，应该可以让我这样的萌新更好理解吧。

---

## 作者：b6e0_ (赞：6)

[CF题面传送门](https://codeforces.com/contest/1370/problem/C) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF1370C) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF1370C)

突然发现这题没什么人写题解，~~热心的~~我就来写一篇了。

题目中的两个人简称为A和F。

分析出一些最优策略：一个人不能使得$n$变成奇数，因为如果是奇数那么另一个人就能直接除完。一个人将$n$变成$2$的次方是一定能获胜的（特殊地，变成$2$会输），因为变成$2$的次方后对手就只能将$n-1$，这样会变成一个奇数。

下面开始分情况讨论：如果$n=2\times\cdots$，那么判断除$2$以外的质因子的指数之和，如果正好为$1$那么F赢，因为A只能将那个质因子除掉，剩下就是一个$2$，F赢。其他情况A胜。这个判断包含了$n=2$时的情况。

剩下如果$n$是$2$的幂次方，F赢（因为A只能$-1$），否则A赢（奇数）。

代码是赛时写的，被改了很多次，所以有很多地方可以简化，大佬勿喷：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
	int t,n,i,tot;
	cin>>t;
	while(t--)
	{
		cin>>n;
		if(n%4&&(n&1)==0)//n=2*...
		{
			tot=0;//累计指数和
			for(i=3;i*i<=n;i+=2)//这里要写成i*i<=n的形式，否则会超时
				while(n%i==0)
				{
					tot++;
					n/=i;
				}
			if(n>2)//如果最后还剩下不是2的数，那么就还剩下最后一个质因子
				tot++;
			if(tot==1)
				cout<<"FastestFinger\n";
			else
				cout<<"Ashishgup\n";
			continue;
		}
		while(!(n&1))//这儿其实可以直接判断奇数的
			n>>=1;
		if(n==1)//2的次方
			cout<<"FastestFinger\n";
		else
			cout<<"Ashishgup\n";
	}
	return 0;
}
```
时间复杂度为$O(t\sqrt n)$。

---

## 作者：KellyFrog (赞：6)

那么首先，拿到$1$的人是输的。

然后，可以把数字变成$1$的人是赢的，也就是说$2$和$2n+1$是赢的。

那么只能把数字变成上面两个的是输的，也就是说，$2^k$（$k\neq 1$）是输的，因为只能$-1$变成奇数，对手是必赢的。

那么$2^k\cdot n$（$n$为奇数，$k\neq 1$）是赢的，因为可以一下变到$2^k$，而对手的$2^k$是必输的。

但是$2\cdot n$（$n$为奇质数）是输的，因为要除必须要除以$n$，而$2$对手必赢的；减一的话就变成了奇数，对手还是必赢的。

同样地，$2\cdot n$（$n$为奇数，不为质数）是赢的，因为我们可以把$n$除掉一个因数变成质数，而对手是必输的。

综上，Ashishgup能赢的条件是：

- $x=2^k\times n$（$k>1$，$n>1$且为奇数）
- $x=2\times n$（$n$为奇合数或$n=1$）
- $x$为奇数

```cpp
#include <iostream>
#include <algorithm>

using namespace std;

bool Prime(int x) {
	for(register int i = 2; i * i <= x; i++) {
		if(x % i == 0) {
			return false;
		}
	}
	return true;
}

void Solve() {
	int x;
	cin >> x;
	if(x == 1) {
		cout << "FastestFinger" << endl;
	} else if(x & 1) {
		cout << "Ashishgup" << endl;
	} else if(x == 2) {
		cout << "Ashishgup" << endl;
	} else if(x & 3) {
		x >>= 1;
		if(Prime(x)) {
			cout << "FastestFinger" << endl;
		} else {
			cout << "Ashishgup" << endl;
		}
	} else {
		while((x & 1) == 0) {
			x >>= 1;
		}
		if(x == 1) {
			cout << "FastestFinger" << endl;
		} else {
			cout << "Ashishgup" << endl;
		}
	}
}

int main() {
	int t;
	cin >> t;
	while(t--) {
		Solve();
	}
}
```

---

## 作者：Priori_Incantatem (赞：5)

最开始，我们可以把 $n$ 分成三种情况

- 当 $n=1$，后手赢
- 当 $n$ 为奇数，先手赢，$n$ 直接除以自身就可以了

前两种情况都比较简单，下面来讨论当 $n$ 为偶数的情况  
当 $n$ 为偶数（$2$ 的倍数），想赢的话肯定不能使用减 $1$ 的操作，因为这样后手必胜。那么就考虑除以约数  
由于 $n$ 为偶数，我们一定可以将 $n$ 分解成一些质数与 $2$ 的正整数次幂之积 $n=p_1 \times p_2 \times \cdots \times p_m \times 2^k$ $(k>0,m \ge 0)$，并且满足这些质数都不是 $2$ 的倍数  
又因为每次除掉的值可以是多个质因数的积（只要是约数就行），所以只要 $m>1$，`Ashishgup` 就可以很灵活的选择约数。    
最后，当 $n$ 被除地只剩 $2^k$ 时，又会有两种情况

1. $n=2$ ，先取的人赢：判断是否能将 $m$ 个质数转化成偶数个不为 $1$ 的数的乘积，如果可以的话说明当前 `Ashishgup` 可以先取（`Ashishgup` 获胜）  
2. $n>2$ ，后取的人赢：判断是否能将 $m$ 个质数转化成奇数个不为 $1$ 的数的乘积，如果可以的话说明当前 `Ashishgup` 可以后取（`Ashishgup` 获胜） 

否则获胜的就是 `FastestFinger` 啦

**代码**
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n;
int main()
{
//	freopen("in.txt","r",stdin);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		if(n==1){puts("FastestFinger");continue;}
		if((n & 1) || n==2){puts("Ashishgup");continue;}
		int tot=0;
		for(int i=2;i*i<=n;++i)
		if((i & 1) && n%i==0) // 注意这里只能把为奇数的质因数
		while(n%i==0)++tot,n/=i;
		for(int i=2;i*i<=n;++i)
		{
			int tmp=n/i;
			if((tmp & 1) && n%i==0)
			while(n%tmp==0)++tot,n/=tmp;
		}
		if(n==2)
		{
			if(tot!=1)puts("Ashishgup");
			else puts("FastestFinger"); // 如果只有一个质数的话就不能化为偶数个数之积
		}
		else
		{
			if(tot)puts("Ashishgup");
			else puts("FastestFinger"); // 这里特判的是0，跟上面原理相同
		}
	}
	return 0;
}
```

---

## 作者：LEle0309 (赞：2)

[博弈论](https://www.luogu.com.cn/problem/list?tag=13)题目。评黄实在有点偏低，毕竟[这题](https://www.luogu.com.cn/problem/P3150)也才评黄。

博弈论的一个重要思想：能使对手只能陷入必败则这种情况你就取胜。

#### 题目大意：

对一个数 $ x $ 进行操作，可以除以一个大于 $ 1 $ 的奇数因子，或把它减去 $ 1 $。

#### 题目分析：

首先，拿到 $ 1 $ 的人肯定无从下手，所以后手胜。

然后 $ 2 $ 和奇数时先手必胜。而 $ 2^n $ 后手必胜，因为**它没有一个奇数因子**，先手只能减 $ 1 $，变成奇数，后手胜。

所以，$ 2^n $ 乘上一个奇质数后手必胜，因为先手减 $ 1 $ 后变成奇数，除以这个奇质数变成 $ 2^n $，而两种情况都会让后手胜。

而 $ 2^n $ 乘上一个奇合数先手必胜，因为先手可以除以一个奇因数使得情况变为上一种，使得先手胜。

所以，代码自然而然的出来了：

```cpp
#include<iostream>
using namespace std;
int n,t,s;
bool prime(int n)
{
	if(n<2)return 0;
	for(int i=2;i*i<=n;i++)if(n%i==0)return 0;
	return 1;
}//判断质数
int main()
{
	cin>>t;
	while(t--)//t组数据
	{
		cin>>n;s=0;//多测不清空，提交两行泪
		if(n==1)cout<<"FastestFinger";//n=1
		else if(n==2||n%2==1)cout<<"Ashishgup";//2或奇质数
		else
		{
			while(n%2==0)//分解
			{
				n/=2;
				s++;//统计2的次幂
			}
			if(s==1&&prime(n)||n==1)cout<<"FastestFinger";//奇合数乘2，后手胜
			else cout<<"Ashishgup";//先手胜
		}
		cout<<endl;//注意换行
	}
	return 0;//完结撒花！
}
```
~~为什么题解区的巨佬们都用位运算，本蒟蒻深感看不懂。~~

---

## 作者：B_1168 (赞：2)

题意：$T$组数据，每组数据给定一个数$n$，两人（`Ashishgup`和`FastestFinger`）玩一个游戏，其中`Ashishgup`先手。玩家可以进行以下操作：

- 将$n$除以它的任意一个大于`1`的奇因子*
- 如果$n>1$，将$n$减去$1$。

规定：当一个人不能进行操作时，该人输掉这一轮游戏。

已知二人按最优策略进行操作，试求每组数据的赢家。

题解：

由样例易知：当$n=1$的时候，`Ashishgup`将不能进行操作，因此`FastestFinger`在此情况下可赢得游戏。

不妨分析样例中显示`FastestFinger`赢得游戏的另外两种情况，即$4$和$6$：

当$n=4$，`Ashishgup`显然只能选择相减操作，使得$n=3$，此时`FastestFinger`可直接进行`n/=3`的操作，使得$n=1$。

扩展分析，当$n=2^k$,其中$k\in\mathbb{Z}^+,k>1$，`Ashishgup`同样只能进行`n--`操作；因为$2^k-1$必为奇数，`FastestFinger`可立即进行除法操作，使得$n=1$，藉此赢得比赛。

当$n=6=2\times 3$，`Ashishgup`可以选择通过`n/=3`使得$n=2$，但`FastestFinger`可通过相减操作使得$n=1$，藉此赢得比赛。

可以设想，当$n=2\times p$，其中$p$为满足满足某些性质的正数时，可以迫使`Ashishgup`进行`n/=p`的操作，使得$n=2$，让`FastestFinger`赢得比赛。

一些实验后，可以发现：当且仅当$p\in\mathbb{P}$时，能迫使`Ashishgup`进行`n/=p`的操作。设想：

当$n=1919810=491\times23\times17\times5\times2$，既然已知`Ashishgup`进行`n/=959905`操作会导致其输去该场比赛时，`Ashishgup`可以选择进行`n/=191981`的操作，使得$n=10$，将原本是`Ashishgup`的问题转化给`FastestFinger`。

简单总结：`FastestFinger`会且仅会在以下情况赢得比赛：
- $n=1$
- $n=2^k$ , 其中 $k\in\mathbb{Z}^+,k>1$
- $n=2\times p$ , 其中 $p\in\mathbb{P}$

赛时代码如下：

```cpp
//Luogu_Resubmission
#include<bits/stdc++.h>
using namespace std;
 
int T,cnt,k;
 
int isprime(int p){
	if(p==1)return 0;
	if(p==2||p==3)return 1;
	if(p%6!=1&&p%6!=5)return 0;
	for(int i=5;i<=sqrt(p);i+=6){
		if(p%i==0||p%(i+2)==0){
			return 0;
		}
	}
	return 1;
}
 
int ist(int k){
	int temp=0;
	while(k%2==0) {
		if(k){
			temp++;
			k/=2;
		}
	}
	return temp;
}
 
void solve(int n){
	if(n==1){
		printf("FastestFinger\n");
		return;
	}
	else{
		int p=ist(n),q=n/(int(pow(2,p)));
		if(p==1){
			if(isprime(q)){
				printf("FastestFinger\n");
				return;
			}
			else{
				printf("Ashishgup\n");
				return;
			}
		}
		else {
			if(p==0){
				printf("Ashishgup\n");
				return;
			} 
			else{
				if(q>1){
					printf("Ashishgup\n");
					return;
				}
				else{
					printf("FastestFinger\n");
					return;
				}
			}
		}
	}
}
 
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&k);
		cnt=0;
//		printf("%d\n",ist(k)); 
		solve(k);
	}
}
```

彩蛋：

本图来自出题者（`Ashishgup`）的[题解博文](https://codeforces.com/blog/entry/79107)。
![](https://codeforces.com/predownloaded/39/39/393940bb7f6d81615f01986e2329f668a181beac.png)

---

## 作者：_QWQ__QWQ_ (赞：1)

本蒟蒻的第二篇题解，~~找题归功于教练~~

[题目传送门](https://www.luogu.com.cn/problem/CF1370C)

这道题目找好了规律很简单：

### 具体思路：

#### 题目大意：
有一个正整数 $ n $。两名玩家轮流操作。每次操作可以执行以下一种：
- 将 $ n $ 除以一个 $ n $ 的奇数因子。
- 将 $ n $ 减去 $ 1 $。

问先手是否有必胜策略。如果先手有必胜策略，输出 ```Ashishgup```，否则输出 ```FastestFinger```。

#### 题目分析：
首先，拿到 $ 1 $ 的会输掉。

直观分析可以得到：

- 当 $ A $ 拿到 $ 2 $ 或奇数的时候必赢，因为 $ 2-1 $ 或奇数 $ \div $ 奇数都使得对方得到 $ 1 $。

在此基础上继续分析其他数值：设 $ p_i $ 为奇质数：

-  如果一个数是 $ 2\times p $，那么 $ A $ 只能执行 $ \div $ 奇数操作，对方拿到 $ 2 $，对方必赢，因此 $ A $ 必输。
  
- 如果一个数是 $ 2\times p_1\times p_2\times... $ 那么 $ A $ 可以执行 $ \div $ 奇数操作，是的对方拿到 $ 2\times p $，因此 $ A $ 必赢。

- 当 $ A $ 为 $ 2^k,k>1 $ 时候， $ A $ 只能执行 $ -1 $ 操作，因此 $ A $ 必输。

- 如果一个数是是 $ 2^k\times p_1\times p_2... $，$ A $ 执行 $ \div $ 奇数操作，对方得到 $ 2^k $，对方必输，因此 $ A $ 必赢。







![](https://cdn.luogu.com.cn/upload/image_hosting/y1nhiqki.png)


知道以上信息代码就很简单了。

## 源码:

```cpp

//A 必胜态 2，3，奇数...   2*ji^2,2^k*ji
//A 必输 1，4，8...2^k(k>1)；2*ji 
#include <bits/stdc++.h>
using namespace std;
bool prime(int x) {
	for(int i=2;i*i<=x;i++) {
		if(x%i==0){
			return false;
		}
	}
	return true;
}
bool work() {
	int x;
	cin>>x;
	if(x==1)return 0;//0必输态 
	else if(x==2||x&1) return 1;//2和奇数必赢态 
	else if(x&2) {//2*奇数 
		x>>=1;
		if(prime(x))return 0;//2*奇质数：必输态
		else return 1;//2*奇数*奇数 必赢态 
	}
	else {
		while(!(x&1))x>>=1;
		if(x==1) return 0;//2^k,必输态 
		else return 1;//2^k*ji必赢态。 
	}
}

int main() {
	int t;
	cin>>t;
	while(t--){
		if(work())cout<<"Ashishgup\n";
		else cout<<"FastestFinger\n";
	}
	return 0;
}


```

---

## 作者：Wings_of_liberty (赞：1)

# 思路
对于这道题我们考虑有什么状态是必败的：

1. $n=1$ ，必败，这个不用过多解释。
2. $n=2$ ，必胜，同样不需要解释。
3. $n$ 为奇数，必胜，很明显，先手只需要除本身就可以把 $n$ 变成一
4. $n$ 是 $2^x$ 这种情况下先手只能进行减一操作，使 $n$ 变为一个奇数，特别注意，2是一种特殊情况，对于 $n=2$ 是先手必胜的。
5. $n$ 是偶数，我们需要分类讨论：  
首先，这种偶数不是 $2^x$ 所以说一定有若干个奇数的因子。  
然后，对于只有一个为二的因子，我们需要判断奇数质因子的数量，如果只有一个奇数质因子（这个因子就是 $n/2$ ），那么是必输的（如果进行减一操作必输不解释，如果进行除奇数操作那么就会把二给对方，所以必输）；如果有至少两个为二的因数，那么是必胜的（先手一次将所有奇数因数全部除去，后手处于情况四，，必败，所以先手必胜）。
# 实现
对于一到四点的实现没有什么多说的，主要是第五点，这一点看似比较麻烦（照着思路直接写），但实际上在写代码时可以合并，第一种，只要除了二以外还有一个奇数因子就可以；第二种，除了二以外还有一个二的因子，综上，只要除了二以外还有一个因子（即除以二后是合数）就可以。
# 代码
```
#include <bits/stdc++.h>
using namespace std;
int x;
inline void init(){
	scanf("%d",&x);
}
inline bool check(int x){
	int tmp=1;
	for(int i=1;i<=30;i++){
		tmp<<=1;
		if(tmp==x){
			return true;
		}
	}
	return false;
}
inline void work(){
	if(x==1){
		printf("FastestFinger\n");
		return;
	}
	if(x==2){
		printf("Ashishgup\n");
		return;
	}
	if(x&1){//奇数
		printf("Ashishgup\n");
	}else{
		if(check(x)){
			printf("FastestFinger\n");
		}else{
			x/=2;
			int tmp=sqrt(x);
			bool f=false;
			for(int i=2;i<=tmp;i++){
				if(x%i==0){
					f=true;
					break;
				}
			}
			if(f){
				printf("Ashishgup\n");
			}else{
				printf("FastestFinger\n");
			}
		}
	}
}
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		init();
		work();
	}
	return 0;
} 
```


---

