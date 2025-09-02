# [ABC180D] Takahashi Unevolved

## 题目描述

Iroha 正在玩一个宠物养成的游戏。

Iroha 的宠物名字叫 Takahashi。初始，Takahashi 的 **STR** 值为 $X$，**EXP** 值为 $0$。Iroha 可以带宠物到以下任意一个 Gym 进行训练：

- Kakomon Gym：**STR** 值将会变为原来的 $A$ 倍，**EXP** 值将会加上 $1$。
- AtCoder Gym：**STR** 值将会加上 $B$，**EXP** 值将会加上 $1$。

当 Takahashi 的 **STR** 值大于等于 $Y$，Takahashi 会进化形态。

但是 Iroha 认为进化的 Takahashi 没那么可爱，于是 Iroha 想求出在保证 Takahashi 不进化的情况下，能达到的最大 **EXP** 值是多少。

## 样例 #1

### 输入

```
4 20 2 10```

### 输出

```
2```

## 样例 #2

### 输入

```
1 1000000000000000000 10 1000000000```

### 输出

```
1000000007```

# 题解

## 作者：So_noSlack (赞：11)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc180_d)&[Atcoder 链接](https://atcoder.jp/contests/abc180/tasks/abc180_d)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

现有 $STR$ 和 $EXP$ 两个变量，初始化分别为 $X$ 和 $0$，可对变量 $STR$ 做以下两种操作：

1. 将 $STR$ 乘 $A$，并将 $EXP$ 自加 $1$。

2. 将 $STR$ 加上 $B$，并将 $EXP$ 自加 $1$。

在 $STR < Y$ 的情况下，求 $EXP$ 的最大值。

## 思路

本蒟蒻读完题目后：“**贪心**!”

那么贪心该怎么贪？通过题意我们很容易想到，无论是执行第一个造作还是第二个操作对 $EXP$ 的影响不变，故就需要我们衡量操作一或二的优势。

如执行操作一比执行操作二**更优**，则有：

$$STR \times A < STR + B$$

同时需满足：

$$STR \times A < Y$$

而自信提交的我结果就可想而知了，重新看了一遍题目，发现数据范围：$1 \le X < Y \le 10^{18}$，$2 \le A \le 10$，$1 \le B \le 10^9$。

那么 $STR \times A$ 就有爆 $\text{long long}$ 的可能，通过简单的不等式移项可变化为：

$$STR < Y / A$$

这样操作一比操作二更优的情况就解决了。又因为贪心思想，当操作二更优时可直接计算还可加多少 $B$，直接加到 $ans$ 里即可，因为此时再进行操作一**必定超过** $Y$ 或 $STR \times A \ge STR + B$。

经过以上分析，即可得到以下代码：

```cpp
#include<iostream>
using namespace std;

long long x, y, a, b, ans = 0; // 开 long long

int main() {
    cin >> x >> y >> a >> b; // 输入
    while(x < y) {
        if(x < y / a && x * a < x + b) x *= a, ans ++; // 操作一比操作二更优，防止爆 long long 优化
        else break; // 操作二更优
    }
    ans += (y - x - 1) / b; // 计算操作二还可执行多少次
    cout << ans << endl; // 输出，换行好习惯
    return 0; 
}
```

[提交记录](https://cdn.luogu.com.cn/upload/image_hosting/adgq8gdw.png)

$\text{The End!!!}$

---

## 作者：1qaz234Q (赞：2)

### 题意简述
有一只宠物，初始的 STR 值为 $X$，初始的 EXP 值为 $0$。它可以去 Kakomon Gym 或 AtCoder Gym 训练。如果去 Kakomon Gym，那么 STR 值变为原来的 $A$ 倍。如果去 AtCoder Gym，那么 STR 值会增加 $B$。无论去 Kakomon Gym 还是 AtCoder Gym，EXP 值都会增加 $1$。要保证 STR 值小于 $Y$，求最大的 EXP 值。
### 题目分析
这道题要使用贪心算法。因为无论去 Kakomon Gym 还是 AtCoder Gym，EXP 增加的值都相等，所以我们要让 EXP 值增加的次数多。那么我们要在保证 STR 值小于 $Y$ 的前提下，尽可能去 STR 值增加小的地方。

如果要去 Kakomon Gym，那么我们按照题意模拟就可以了。如果要去 AtCoder Gym，那么没必要按照题意模拟，我们只需要求出可以去多少次 AtCoder Gym，然后更新 EXP 值，最后跳出循环，输出答案。

因为 $1\leq X<Y\leq10^{18}$，所以要开 long long。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    int x, y, a, b, exp = 0;
    cin >> x >> y >> a >> b;
    while (x < y)
    {
        if (x < y / a && x * a < x + b) // 保证 x 变为原来的 a 倍后小于 y 并且去 Kakomon Gym 的 x 小于去 AtCoder Gym 的 x，也就是去 Kakomon Gym。注意，写成 x * a < y 后会爆 long long
        {
            exp++;     // EXP 值增加 1
            x = x * a; // x 变为原来的 a 倍
        }
        else // 去 AtCoder Gym
        {
            exp = exp + (y - x - 1) / b; //(y - x - 1) / b 表示可以去多少次 AtCoder Gym，因为要使变化后的 x 小于 y，所以要减 1。让后更新 EXP 值
            break;                       // 跳出循环
        }
    }
    cout << exp;
}
```

---

## 作者：Molina (赞：2)

# 本题大意：
### 题目链接：[luogu](https://www.luogu.com.cn/problem/AT_abc180_d) && [atcoder](https://atcoder.jp/contests/abc180/tasks/abc180_d)

给你了 $ 4 $ 个数，$ x $，$ y $，$ a $，$ b $。以及 $ str $ 和 $ exp $。其中 $ str $ 初始值为 $ x $，$ exp $ 初始值为 $ 0 $。

有两种操作方式：

1. $ str $ 变为原来的 $ a $ 倍，$ exp $ 加一。
2. $ str $ 加上 $ b $，$ exp $ 加一。

求当 $ str<N $ 时，$ exp $ 最大取多少。
# 本题思路：
 就是**贪心思想**！
 
 因为两种操作方式 $ exp $ 都会加一，所以考虑**贪心**：只要 $ str $ 值加得越慢，最后得到的 $ exp $ 值就越多，所以要尽可能的多进行操作，**加上 $ str \times a $ 与 $ str+b $ 中较小的值。**
 
 先开一个循环，（循环条件 $ x<y $），当 $ x $ 符合情况时（循环条件：$x<y / a$ 和 $ x*a<x+b $，第一个是防止 $ x $ 乘上 $ a $ 后会大于 $ y $，第二个是防止用第一种方法的 $ str $ 值会大于第二种方法），则将 $ x $ 乘上 $ a $ 倍，将答案加一。
 
 当不符合情况时，退出循环，计算还可以加多少个 $ b $，再加答案。
# 代码来咯~
```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,y,a,b,ans=0;
int main(){
	cin>>x>>y>>a>>b;
	while(x<y){//开循环
		if(x<y/a  &&  x*a<x+b)
			x*=a,ans++;//符合就加答案
		else  break;
	}
	ans+=(y-x-1)/b;//计算可以加多少个b
	cout<<ans;
	return 0;
}
```

---

## 作者：Archy_ (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_abc180_d)

## 题目大意：

输入 $X$，$Y$，$A$，$B$。有如下两种操作：

1. 将 $X$ 自乘 $A$，$EXP$ 加 $1$。

2. 将 $X$ 加上 $B$，$EXP$ 加 $1$。

求 $X < Y$ 时，$EXP$ 的最大值。

## 思路：

首先看到题目数据范围**暴力枚举肯定会超时**，所以我们应该如何去优化呢？

要想使 $EXP$ 最大，我们应进行的**操作尽可能的多**，当有 $X \times A < X + B $ 时显然操作 $1$ 更优，枚举操作 $1$ 时要时刻注意 $X \times A < Y$，但由于题目数据范围过大，$X \times A$ 显然会**爆 long long**，所以此时应改为 $X<Y\div A$。

枚举完操作1的数量后则剩下值 $Y-X-1$，减去 $1$ 是因为把 $X = Y$ 的部分减掉，则操作 $2$ 的数量为 $(Y-X-1) \div B$。

将 $2$ 次操作相加输出即可。
## code：
```cpp
#include<iostream>
using namespace std;
long long x,y,a,b,cnt;
int main(){
	cin>>x>>y>>a>>b;
	while(1){
		if(x*a<x+b&&x<y/a)x*=a,cnt++;//操作1优
		else break; //操作2优
 	}
	cnt+=(y-x-1)/b;//计算操作2次数
	cout<<cnt<<"\n"; //记得换行
	return 0;
}
```

---

## 作者：H_space (赞：1)

原题地址：[洛谷原题](https://www.luogu.com.cn/problem/AT_abc180_d) & [Atcoder原题](https://atcoder.jp/contests/abc180/tasks/abc180_d)

## 题目简述

现有 $STR$ 和 $EXP$ 两个变量，$STR$ 的初始量为 $x$，$EXP$ 的初始量为 $0$。

输入 $A，B，X，Y$ 四个整数，现可对变量 $STR$ 作如下操作：

操作一： $STR$ 值将会变为原来的 $A$ 倍，$EXP$ 值将会加上 $1$。

操作二： $STR$ 值将会加上 $B$，$EXP$ 值将会加上 $1$。

当 $STR < Y$ 时，求 $EXP$ 的最大值。

## 思路：

看到此题我们不免可以分析出其所考查的内容是**贪心算法**。
   
再结合题意，我们可以发现题目中所给的两个操作都只对 $EXP$ 加了 $1$，因此对于 $EXP$ 而言，操作的影响不大。
   
所以我们就要利用贪心思想，对操作一和操作二的优势进行斟酌。
   
这里以操作一的优势大于操作二举例，则得到如下不等式：
   
$$STR \times A < STR + B$$
   
且需同时满足：
   
$$STR \times A < Y$$  
     
根据以上思路就可得到如下代码：

```cpp
#include<iostream> //头文件
using namespace std;//使用命名空间

int x, y, a, b, ans=0;//定义变量，注意ans初始化

int main(){
	cin >> x >> y >> a >> b;
	while(x < y){
		if(x * a < y && x * a < x + b)x = x * a, ans ++;//这里是对操作一进行判断
		else break;//否则就是操作二更有优势
	}
	ans = ans + (y - x - 1) / b;//计算操作二还可以执行多少次
	cout << ans << endl; //输出答案，记得换行
	return 0; //不要忘记返回哦！
}
```

仔细查看题目的数据范围，发现需要开 $\text{long}$ $\text{long}$。

之后我们为防止爆 $\text{long}$ $\text{long}$，就需要把上面的不等式简单的移项可得：     

$$STR < Y / A$$


可得代码如下：

```cpp
#include<iostream> 
using namespace std;

long long x, y, a, b, ans=0; //开longlong

int main(){
	cin >> x >> y >> a >> b;
	while(x < y){
		if(x < y / a  && x * a < x + b)x = x * a, ans ++; //将不等式移项
		else break;
	}
	ans = ans + (y - x - 1) / b;
	cout << ans << endl; 
	return 0;
}
```

$$\texttt{The End!}$$


---

## 作者：Moon_Traveller (赞：1)

[>> 传送门 <<](https://www.luogu.com.cn/problem/AT_abc180_d)

[>> 原 OJ 传送门 <<](https://atcoder.jp/contests/abc180/tasks/abc180_d)

### 题目大意

小可爱有两个属性：$STR$ 和 $EXP$。

给你四个数 $X~Y~A~B$。并将 $STR$ 赋值为 $X$，将 $EXP$ 赋值为 $0$。

现在你可以进行两种操作：

1. $STR = STR \times A$，$EXP = EXP + 1$

2. $STR = STR + B$，$EXP = EXP + 1$

小可爱想知道，当 $EXP < Y$ 时，$STR$ 最大可以达到多少？

### 思路

明显可以**贪心**。我们只需要比较两种操作的价值，选用价值大的即可。

即判断：

$$STR \times A < STR + B$$

如果判别式的值为 $True$，即第一种操作的价值相对较大。那么我们就选用第一种操作，注意要判断乘积是否小于 $Y$。

然后你就可以写出如下代码（注意！这是错的！）：

```cpp
while(STR * a < y && STR * a < STR + b)
{
    STR *= a;
    EXP++;
}
```

提交上去之后，你就会喜提 WA 啦（雾

观察一下数据范围，$1 \le X \lt Y \le 10^{18}$， 
$2 \le A \le 10^9$，显然 $X \times A$ 会超出 long long 的范围。那么我们就需要稍微变化一下，把乘法变为除法：

$$STR \times A \lt Y$$

不等式两边同时除以 $Y$，变为：

$$STR \lt Y \div A$$

代码就改好了：

```cpp
while(STR < y / a && STR * a < STR + b)
{
    STR *= a;
    EXP++;
}
```

~~（没错，只需要限制前面一半，我也不知道为什么后面不需要，可能是因为 $STR$ 太大，直接被咔了吧……）~~

~~（这里好像也可以通过其他玄学方法限制，感兴趣的可以自己尝试）~~

第一种操作搞定了，那么剩下的就是第二种方法啦。按照正常的思路，你可能会写出这样的代码（注意！还是错的！）：

```cpp
while(STR + b < y)
{
    STR += b;
    EXP++;
}
```

把这段代码放上去，你又会喜提 TLE。~~这个不用我说你也知道为什么对吧？你很聪明的对吧？~~ 没错，是因为循环次数太多了！那么我们只需要把循环简单的改成数学算式就可以啦：

```cpp
EXP += (y - STR - 1) / b;
```

为什么要减 $1$？因为我们要考虑的是 $STR < Y$，所以只有 $STR+B<Y$ （也就是 $\le Y-1$）时，才可以继续操作。

### 最终代码

```cpp
#include <iostream>
using namespace std;
#define int long long

int x, y, a, b;
int STR, EXP;

signed main()
{
    cin >> x >> y >> a >> b;
    STR = x; // 当然你也可以直接对x操作，这里我为了方便阅读，就多定义了一个变量
    while(STR < y / a && STR * a < STR + b)
    {
        STR *= a;
        EXP++;
    }
    EXP += (y - STR - 1) / b;
    cout << EXP << endl;
    return 0;
}
```

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

大家的思路讲得很详细，这里补充一下，因为即将开始 CSP，所以来讲一下做这道题的心路历程，以便于更好的 ~~AKCSP~~ 临场发挥。

Part $1$ 暴力答题--找寻思路

在考场上遇到的肯定是你没遇见过的题。所以先打暴力是好的选择。

第一种情况，打了，过了大样例，很不错！看下一题（但是要检查有没有细节出错）。

第二种情况，打了，大样例卡了，开始优化。

第三种情况，打了，大样例错了，深入分析，然后找到错因改正。

第四种情况，干等着爆零。

所以打暴力没啥坏处，尽情去打吧。

分析暴力代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long int
main(){
	int a,b,c,d,ans=0;
	cin>>a>>b>>c>>d;
	while(a<b){
		a=min(a*c,a+d);
		ans++;
	}
	ans-=1;//减去溢出的
	cout<<ans;
	return 0;
}
```

Part $2$ 深入分析--优化改错

如上所言，大样例爆了。

寻找可供优化的点。

只有一个 while，比较简单就能找到：如果最终的结果很大，而且每次都很大，就会爆。

贪心分析得如果这次选加，那么接下来一定选加。

那么把这些加和放在一起判断，就少了 while 占的时间。

优化代码：

```cpp
while(a<b){
		if(a*c<a+d){
			a*=c;
			ans++;
		}else{
			e=1;
			break;
		}
	}
	if(e){
		ans+=(b-a-1)/d;
	}else{
		ans--;
	}
```
Part $3$ 找寻细节--细致纠错

很容易把这份代码当作最终答案，可惜不是。

在提交后，T 了一个点。

能够 T 掉 $2$ 秒的单重循环，八成是成了死循环。

再仔细检查数据范围，发现尽管使用了 ull，还是有爆掉的可能！

那么以除代乘，化简精度问题，就可以 [AC](https://atcoder.jp/contests/abc180/submissions/45438784) 了。

谢谢观赏，祝大家 CSP 取得好成绩！

---

## 作者：whx2009 (赞：0)

## 本题思路：
这道题其实没有其他的算法要用，直接去枚举就可以了。但是直接枚举每一步操作会超时，这里我们就可以先把乘 $A$ 比加 $B$ 小的先进行操作，然后把剩下的直接一步加满就可以了。
## 本题代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long x,y,a,b,ans=0;
	cin>>x>>y>>a>>b;
	for(;x<y;)
	{
		if(x<y/a && x*a<x+b) x*=a,ans++;
		else
		{
			ans+=(y-x-1)/b;//直接算出答案
			cout<<ans;
			return 0;
		}
	}
}
```


---

## 作者：lilong (赞：0)

贪心思想，STR 值增长得越慢，可能得到的 EXP 值就越多。

根据此，我们在 $x$ 较小时，可以乘 $a$ 也可以加 $b$，选择运算后较小的一种情况。在某一时刻，当 $x \times a > x + b$ 时，可知一直到最后都应选择加 $b$（前者是几何级增长，后者是算术级增长）。然后计算能加的次数即可。

具体实现如下：

```cpp
#include <iostream>
#include <cstdio>
#define int long long

using namespace std;
signed main()
{
	int x,y,a,b,k,ans=0;
	cin >> x >> y >> a >> b;
	while(x < y/a && x*a < x+b)//注意，这里不可写成 x*a<y,否则会因超过极限最大值变为负数，从而导致死循环	
		x *= a,ans++;
	k = y - x - 1;
	ans += k / b;
	cout << ans;
	return 0;
}
```


---

## 作者：hellolin (赞：0)


**UPD1**：修改了代码中的一个小错误。

[题面(洛谷)](https://www.luogu.com.cn/problem/AT_abc180_d)

[题面(AtCoder)](https://atcoder.jp/contests/abc180/tasks/abc180_d)

## 题意

- 给定正整数 $X,\ Y,\ A,\ B$。初始，**STR** 值等于 $X$，**EXP** 值为 $0$；
- 可以选择让 **STR** 值乘 $A$ 或加 $B$，两种操作都会使 **EXP** 值加 $1$；
- **STR** 值不能大于 $Y$，问你经过若干次操作后，**EXP** 值最大是多少；
- $1\le X< Y\le 10^{18},\ 2\le A\le 10^9,\ 1\le B\le 10^9$。

## 思路

这是一道贪心题目。

既然要使得 **EXP** 值尽量高，就是让操作次数尽可能多，即优先选择 **STR** 值增长较慢的方式。

如果直接进行模拟的话，会 TLE。毕竟 $10^{18}$ 的范围可不是闹着玩的。

考虑优化，可以试着找找使 **STR** 增长较慢的规律：

题目中 **STR** 增长的两种方式是乘 $A$ 或加 $B$，那么应该先乘还是先加呢？

如果先加后乘各一次，**STR** 值变化如下：

$$X \to X + B \to A \cdot (X + B)$$

如果先乘后加各一次：

$$X \to A\cdot X \to A\cdot X + B$$

很容易看出来，后面这种方法（先乘后加）的 **STR** 值增长较少。

当 $X<\frac{Y}{A}$（再乘一次不会超出 $Y$）且 $X\cdot A<X+B$（乘 $A$ 比加 $B$ 更划算）时，使 $X$ 乘 $A$。

接下来的加法运算就没必要循环了，直接加上 $\frac{Y-X-1}{B}$ 就可以了（分子减一是为了保证加上的这些不会超出 $Y$ 的范围）。

## 代码

``` cpp
// Coder          : Hellolin
// Time           : 2023-02-03 13:01:22
// Problem        : [ABC180D] Takahashi Unevolved
// Contest        : Luogu
// URL            : https://www.luogu.com.cn/problem/AT_abc180_d
// Time Limit     : 2000 ms
// Memory Limit   : 1 GiB

#include <iostream>
#define ll long long // 开 long long 防止溢出

ll x, y, a, b, ans;

int main()
{
    // 加速输入输出
    std::ios::sync_with_stdio(false);
    
    std::cin>>x>>y>>a>>b;

	// 循环进行乘法操作
    for (ans=0; x<(y/a) && (x*a)<(x+b); x*=a) ++ans;

	// 进行加法操作
    std::cout<<ans+((y-x-1)/b)<<std::endl;

    return 0;
}
```


---

