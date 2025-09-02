# [ARC145B] AB Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc145/tasks/arc145_b

以下のゲームをゲーム $ n $ と呼びます。

> Alice と Bob でゲームをします。はじめ $ n $ 個の石があります。
> 
> Alice から始めて、交互に次の操作を行い、操作を行えなくなった方が負けとなります。
> 
> - もし Alice が操作を行うなら、石を $ A $ の正の倍数の個数取り除く。
> - もし Bob が操作を行うなら、石を $ B $ の正の倍数の個数取り除く。

ゲーム $ 1 $、ゲーム $ 2 $、…、ゲーム $ N $ のうち、二人が最適に行動したとき Alice が勝つゲームは何個あるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ ,A,B\ \leq\ 10^{18} $
- 入力は全て整数

### Sample Explanation 1

ゲーム $ 1 $ では、Alice は操作を行えないため Alice の負けとなります。 ゲーム $ 2 $ では、Alice が石を $ 2 $ 個取ることで Bob は操作を行えなくなり、Alice の勝ちとなります。 ゲーム $ 3 $ では、Alice が石を $ 2 $ 個取り、Bob が石を $ 1 $ 個取るとAlice は操作を行えないため Alice の負けとなります。 ゲーム $ 4 $ では、Alice が石を $ 2\ \times\ 2\ =\ 4 $ 個取ることで Bob は操作を行えなくなり、Alice の勝ちとなります。 以上より、ゲーム $ 1,2,3,4 $ のうちAlice が勝つゲームは $ 2 $ 個です。

## 样例 #1

### 输入

```
4 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
27182818284 59045 23356```

### 输出

```
10752495144```

# 题解

## 作者：chinazhanghaoxun (赞：5)

## 题意

~~这道题的翻译真幽默，连获胜条件都不给的。~~

感谢其它楼主的翻译，我只是复述一遍哦。给出 $n$，$a$，$b$ 三个正整数。进行 $n$ 轮博弈，第 $i$ 轮博弈有 $i$ 颗石子，Alice 可以从里面取走 $a$ 的正整数颗石子，Bob 可以从里面取走 $b$ 的正整数颗石子，首先无法行动的一方失败。Alice 为先手。假设两人都已最优的策略取走石子，求在这 $n$ 轮博弈中，Alice 能取胜的局数。
## 分析

首先，对于一道博弈论的题目，我们一定要分类思考，因为最后的代码大概率直接可以用几个判断语句解决。那我们就能想了，要让一个人拿不了，必须得让当前的石子数小才行，也就是说我们每次都要尽量多拿，其实就是拿 $n-(n \bmod a)$，意思就是把能拿的都拿走，那么接下来就要进行分类讨论了。

第一种情况，如果 $a$ 比 $n$ 大的话，则 Alice 直接输掉比赛，因为她一次也拿不了。

其他情况，把博弈分段，分为一段长为 $a$ 的博弈，$n\div a-1$ 段长为 $a$ 的博弈，以及剩下的一段长为 $n \bmod a$ 的博弈，分别表示的是一次拿的，中间几次拿的，和最后一次剩余小于 $a$ 的石子，也就是 Alice 拿不了的。最后得到的答案公式为 $1+(\lfloor \frac{n}{a} \rfloor −1)\times \min(a,b)+\min(n \bmod a,b−1)$，分别表示的就是上面那三个状态。
## 代码+注释

别忘了数据范围为 $10^{18}$，**一定要开 long long**。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int n,a,b;
	cin>>n>>a>>b;
	if(a>n) //第一种情况 
		cout<<0;
	else //其他情况 
		cout<<1+(n/a-1)*min(a,b)+min(n%a,b-1);
	return 0;
}
```

---

## 作者：luxiaomao (赞：1)

## 前言（~~废话~~）

用来练习博弈论，拓展一下思维还是可以的。

看到楼下 dalao 的分析和证明过于简短，还有部分错漏，决定写篇题解造福和我一样的蒟蒻。

## 分析

### 题意

~~Alice 和 Bob 怎么又是你们两个。。。~~

给出 $n$，$a$，$b$ 三个正整数。

进行 $n$ 轮博弈，第 $i$ 轮博弈有 $i$ 颗石子，Alice 可以从里面取走 $a$ 的正整数颗石子，Bob 可以从里面取走 $b$ 的正整数颗石子，首先无法行动的一方失败。Alice 为先手。

假设两人都已最优的策略取走石子，求在这 $n$ 轮博弈中，Alice 能取胜的局数。

### 模拟 $\to$ 公式

首先我们不难想出，让先手尽量取多石子（即 $n-(n\bmod a)$），剩下的 $n \bmod a$ 如果比 $b$ 小，那么后手就无法取（因为后手最少只能取 $b$ 颗），我们就可以得到一次博弈的结果啦。

然而，这只是**一次博弈**喔，题目要求进行 $n$ 轮博弈，$n \le 10^{18}$ 的数据范围告诉我们连 $O(n)$ 的模拟也将无法通过，我们必须考虑如何实现 $O(1)$ 的解法。（似乎本题没有 $O(\log n)$ 的解法，但是既然可以 $O(1)$ 解决那又有什么关系捏嘿嘿嘿）

我采用的方法是将博弈的过程进行分段。

请看一组数据（我自己搓的，方便理解）：

```test
11 3 2
```

我把它这么分段：

```test
○○○|○○○|○○○|○○
```
即分成 $\lfloor \frac{n}{a} \rfloor$ 段长 $a$ 的部分和一段长 $n \bmod a$ 的部分。

很明显，在第一段中，只能在第三次我才能赢（因为第一次和第二次先手无法取那么少的石子）。可以证明所有类似的划分中，第一段只能为我们产生 $1$ 的贡献。

那么，接下来考虑剩余 $\lfloor \frac{n}{a} \rfloor -1$ 段长为 $a$ 的博弈。如果 $b > a$，很显然我每一段都能赢得所有 $a$ 次博弈，否则我也能赢得 $b$ 次。用公式表述就是 $\min(a,b)$，那么中间这几截的贡献为 $(\lfloor \frac{n}{a} \rfloor -1) \times \min(a,b)$。

最后是多出来的长为 $n \bmod a$ 的一截，我们可以取得 $b-1$ 的贡献，但是前提是这个数字不会超过这一截本身的长度，所以贡献为 $\min(n \bmod a,b-1)$。

整合一下公式：

$$1 + (\lfloor \frac{n}{a} \rfloor -1) \times \min(a,b) + \min(n \bmod a,b-1)$$

## Code Time

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n,a,b;

int main()
{
	scanf("%lld%lld%lld",&n,&a,&b);
	if(a > n)//特判，无需进行公式计算
		printf("0");
	else
		printf("%lld",1 + min(a,b)*(n/a-1) + min(b-1,n%a));
	return 0;
}
```

---

## 作者：lzxyl (赞：0)

### 题目大意

给出 $n,a,b$ 三个正整数。共进行 $n$ 轮博弈，第 $i$ 轮博弈有 $i$ 颗石子，Alice 可以从里面取走 $a$ 的正整数倍颗石子，Bob 可以从里面取走 $b$ 的正整数倍颗石子，首先无法行动的一方失败。Alice 为先手。

假设两人都已最优的策略取走石子，求在这 $n$ 轮博弈中，Alice 能取胜的局数。

### 解决方法

博弈论

首先进行分类讨论：

$1^\circ$ $a \ge n$
此时 Alice 无法下棋，因此 $ans = 0$；

$2^\circ$ $a \le n$
此时我们可以把 $n$ 分成三段：

#### 第一段：$1$ 到 $a$（$1$ 段长为 $a$ 的博弈）。

很明显，在这一段中，只能在第 $a$ 次时 Alice 才能赢（因为前面的 $a-1$ 次先手无法取那么少的石子），所以这一段 Alice 赢的次数为 $1$。

#### 第二段：$a+1$ 到 $n-(n \bmod a)$（$n \div a-1$ 段长为 $a$ 的博弈）。

在这一段中，每增加 $a$ 个棋子，Alice 赢的次数就会增加一个固定的数 $x$。那这个固定的数是多少呢？分两种情况：① $a\ge b$，$x=b$；② $a\le b$，$x=a$。

所以这一段 Alice 赢的次数为 $(n\div a-1)\times \min(a,b)$。

#### 第三段：$n-(n \bmod a)+1$ 到 $n$（$1$ 段长为 $n \bmod a$ 的博弈）。

对于这一段，Alice 最多可以赢 $b-1$ 次（如果 $n\bmod a\ge b-1$ 的话），所以这一段 Alice 赢的次数为 $\min(n\bmod a,b-1)$。

#### 最后来整合一下：

当 $a\ge n$ 时，$ans=0$；

当 $a\le n$ 时，$ans=1+(n\div a-1)\times \min(a,b)+\min(n\bmod a,b-1)$。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,ans;
int main(){
	cin>>n>>a>>b;
	if(a>n) ans=0;
	else ans=1+(n/a-1)*min(a,b)+min(n%a,b-1);
	cout<<ans;
	return 0;
}
```

---

## 作者：Zhl2010 (赞：0)

## 题目概括
一个游戏：  
最初有 $n$ 颗棋子。  
棋手轮流下棋，爱丽丝先下。无法走棋的一方输。

轮到爱丽丝时，她必须取出的棋子数是 $A$ 的正倍数。  
轮到鲍勃时，他必须取出的棋子数是 $B$ 的正倍数。
## 思路
分类讨论（博弈论的难点）。

如果 $a$ 比 $b$ 小：  

$~~~~~$如果 $n$ 太小了:

$~~~~~~~~~~$直接输出 $0$，因为 爱丽丝连第一步都走不了。

$~~~~~$否则：

$~~~~~~~~~~$当局输大于 $a$ 时，爱丽丝一定赢，答案为 $n-a+1$。

### 代码：
```cpp
cout<<max((long long)0,n-a+1)<<endl;
```

否则：

$~~~~~$分段，共 $n$ 个，每 $a$ 个为一段，除去第一组，共 $n/a-1$ 组能赢 $b$ 次。分完段后剩下的赢的局数可以用 $n \mod a+1$ 和 $b$ 的最小值表示，代表前 $b$ 个。

### 代码：
```cpp
cout<<max((long long)0,(long long)((long long)(n/a-1)*b+min(n%a+1,b)))<<endl;
```

---

以上是完整思路，可能会有点难理解。
## AC代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a,b;

signed main(){
	cin>>n>>a>>b;
	if(a<b){
		cout<<max((long long)0,n-a+1)<<endl;
		return 0;
	}
	cout<<max((long long)0,(long long)((long long)(n/a-1)*b+min(n%a+1,b)))<<endl;
	return 0;
}
```

---

## 作者：zcr0202 (赞：0)

## 前置知识

[博弈论。](https://oi-wiki.org/math/game-theory/intro/)

## 题目大意

给你 $n$ 个石子，再给你 $a$ 和 $b$ ，也就是说 ```Alice``` 可以拿 $a$ 的倍数的石子和 ```Bob``` 可以拿 $b$ 的倍数的石子，求每一轮中 ```Alice``` 赢的次数。

## 解题思路

由于楼上楼下都证明了其博弈论的做法，所以我这里不展开来说，我就在这里讲一下结论，帮助大家理清思路。

- 如果 $a \geq n$，那么先手直接赢，直接输出零。

- 否则对答案的贡献为 $1 + min(a, b) \times (n / a - 1) + min(b - 1, n \bmod a)$，最后输出即可。


## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, a, b, ans;
int main() {
    cin >> n >> a >> b;
    if(a > n) {
        ans = 0;
    }
    else {
        ans = 1 + min(a, b) * (n / a - 1) + min(b - 1, n % a);
    }
    cout << ans;
    return 0;
}
```

---

## 作者：Smg18 (赞：0)

题意易懂，讲解思路吧。

思路：

- $a \leq b$ 时，只要 $n > a$，他就赢得游戏。

- 当 $a<b$ 时，如果 $n \geq a$ 且 $n \bmod a<b$，则他能赢得游戏。

- 如果石子数小于他最小拿的数，必输。

- 每玩 $\left\lfloor\dfrac{n}{a}\right\rfloor$ 局（除最后一组局数小于 $a$），即开始第二种游戏模式，每局都可以获得 $\min(a,b)$ 分。在剩下不足 $\left\lfloor\dfrac{n}{a}\right\rfloor$ 局的游戏中，每局可以获得 $b$ 分，但最多只能进行 $n \bmod a$ 次。最后将所有获得的分数加起来，输出即可。

所以代码如下：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define R(i,j) for(auto i:j)
using namespace std;
const int N=1e5+10,NN=1e4+10,mod=100000007;
ll f[N],n,b,a;
int main(){
	cin>>n>>a>>b;
	if(n<a){//如果大就打不过
		cout<<0;
	}
	else{
		cout<<(1+(n/a-1)*(min(a,b)))+min(b-1,n%a);//输出，解答如上
	}
	
	return 0;
}

```

---

## 作者：a18981826590 (赞：0)

# [[ARC145B] AB Game](https://www.luogu.com.cn/problem/AT_arc145_b)
此题较简单，想通了就很好做。
## 解题思路
此题涉及博弈论，需分类讨论。
- 如果 $a \le b$：
	- 如果 $n < a$：答案为 $0$，因为 Alice 第一次都拿不了；
   - 否则 Alice 必赢，答案为 $n-a+1$；
- 如果 $a > b$：答案为 $\lfloor \frac{n}{a} \rfloor \times b+ \min(n \bmod a,b-1)+1$。
## AC代码
警告：**十年 OI 一场空，不开 longlong 见祖宗**
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n,a,b;
int main(){
	cin>>n>>a>>b;
	if(a<=b) cout<<max((long long int)0,n-a+1);
	else cout<<max((long long int)0,(n/a-1)*b+min(n%a,b-1)+1);
	return 0;
}
```

---

