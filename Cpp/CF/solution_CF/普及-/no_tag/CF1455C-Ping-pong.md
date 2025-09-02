# Ping-pong

## 题目描述

Alice and Bob play ping-pong with simplified rules.

During the game, the player serving the ball commences a play. The server strikes the ball then the receiver makes a return by hitting the ball back. Thereafter, the server and receiver must alternately make a return until one of them doesn't make a return.

The one who doesn't make a return loses this play. The winner of the play commences the next play. Alice starts the first play.

Alice has $ x $ stamina and Bob has $ y $ . To hit the ball (while serving or returning) each player spends $ 1 $ stamina, so if they don't have any stamina, they can't return the ball (and lose the play) or can't serve the ball (in this case, the other player serves the ball instead). If both players run out of stamina, the game is over.

Sometimes, it's strategically optimal not to return the ball, lose the current play, but save the stamina. On the contrary, when the server commences a play, they have to hit the ball, if they have some stamina left.

Both Alice and Bob play optimally and want to, firstly, maximize their number of wins and, secondly, minimize the number of wins of their opponent.

Calculate the resulting number of Alice's and Bob's wins.

## 说明/提示

In the first test case, Alice serves the ball and spends $ 1 $ stamina. Then Bob returns the ball and also spends $ 1 $ stamina. Alice can't return the ball since she has no stamina left and loses the play. Both of them ran out of stamina, so the game is over with $ 0 $ Alice's wins and $ 1 $ Bob's wins.

In the second test case, Alice serves the ball and spends $ 1 $ stamina. Bob decides not to return the ball — he loses the play but saves stamina. Alice, as the winner of the last play, serves the ball in the next play and spends $ 1 $ more stamina. This time, Bob returns the ball and spends $ 1 $ stamina. Alice doesn't have any stamina left, so she can't return the ball and loses the play. Both of them ran out of stamina, so the game is over with $ 1 $ Alice's and $ 1 $ Bob's win.

In the third test case, Alice serves the ball and spends $ 1 $ stamina. Bob returns the ball and spends $ 1 $ stamina. Alice ran out of stamina, so she can't return the ball and loses the play. Bob, as a winner, serves the ball in the next $ 6 $ plays. Each time Alice can't return the ball and loses each play. The game is over with $ 0 $ Alice's and $ 7 $ Bob's wins.

## 样例 #1

### 输入

```
3
1 1
2 1
1 7```

### 输出

```
0 1
1 1
0 7```

# 题解

## 作者：Thomas_Cat (赞：5)

首先，我们命名发球员为 $a$，接球员为 $b$。则 $a$ 的体力为 $x$，$b$ 的体力为 $y$。

分情况讨论：

- 当 $a$ 想要获胜时：

原始体力为 $f(x,y)$ ，则如果 $a$ 想要获胜并且 $a$ 为发球员，则可以从主观判断：$b$ **永远接不到球**，则 $a$ 每一次就可以获得 $1$ 个获胜机会，体力为：$f(x-1,y) (x \ge 2)$。

同理，如此下去，当 $x=1$ 时，$a$ 的体力值为 $f(1-1)=f(0)$ ，则无力回球，而此时 $b$ 的体力仍然为 $f(y)$：

则共进行：$x-1$ 次回球。$a$ 获得 $x-1$ 分。

- 当 $b$ 想要获胜时：

原始体力为 $f(x,y)$ 由于 $a$ 时发球员，$b$ 接球，体力：$f(x-1,y-1)$，此时 $a$想要保存体力，体力仍然为 $f(x-1,y-1)$。

由此下去，$b$ 获得 $y$ 点体力。

综上所述：答案为 $f(x-1),f(y)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
    cin>>t;
    while(t--){
    	int a,b;
        cin>>a>>b;
        cout<<a-1<<' '<<b<<endl;
    }
	return 0;
}
```

---

## 作者：Tenshi (赞：4)

# 分析：推理题

做这种题的时候先动手~~膜你~~模拟一下，找一下思路。

我们记Alice体力为a，Bob体力为b

我们来模拟一下：

a=100 b=3

Bob会怎么做呢？

因为他的首要任务是让自己赢球最多，那当然就是赢三场（等到a->0的时候发三球赢下来（~~毫无体育精神~~）），这样的话Alice可以赢100场，Bob有无办法让Alice赢少点呢？有，在
Alice还剩0体力的时候击球（Alice刚发完求，体力：1->0）。这样回球的时候就可以赢下那局，让Alice少赢一把

于是胜利局数为：Alice：99 Bob：3

推得公式为：胜利局数 a-1 b

可知其它情况策略类似。

代码（超短！）：

```cpp
#include <bits/stdc++.h>
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int a,b; cin>>a>>b;
      cout<<a-1<<' '<<b<<endl;
	}
	return 0;
}
```



---

## 作者：wmy_goes_to_thu (赞：3)

首先，我们进行 dp。

设 $f_{i,j}$ 代表 Alice 有 $i$ 个且 Bob 有 $j$ 个现在该 Alice 的最好代价，是一个二元组。

转移方程自然是 $f_{i,j}=better(Bob) f_{i-1,j}+Alice,Rev(f_{j,i-1})$。

比如 $f_{3,5}=(2,5),f(5,3)=(4,3)$，那么 $f(4,5)=better(Bob) (3,5) (3,4)=(3,5)$。

然后推一推就发现 $f(i,j)=(i-1,j)$。

交上去就过了。

---

## 作者：想不好名字 (赞：1)

大家好，我又来水一波题解，望大家能耐着性子看完



------------
#### 题面
$Alice$有$x$点体力，$Bob$有$y$点体力,每次击球会消耗1点体力。如果体力不足则不能击球。每轮比赛开始的一方如果有体力必须发球。如果两人都没有体力则游戏结束。

$Alice$和$Bob$都采取最优策略进行游戏。他们希望首先最大化自己获胜的场数，其次最小化对方获胜的场数



------------
#### 分析

首先，$Alice$先发球，若$Alice$发球，$Bob$就会打回去的话，那两者获胜次数最小，因此，对于$Bob$来说最好的方法就是到$Alice$没有体力了在发动~~致命一击~~，当$Alice$还剩下最后一点体力时，$Alice$发球，$Bob$回击，$Alice$体力不足，以后$Bob$发球都无法回击，这样最优解就出来了


------------
#### 代码
```c
#include<iostream>
using namespace std;
int main()
{
	int n,a,b;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a>>b;
		cout<<a-1<<" "<<b<<endl;
	}
	return 0;
} 
```



------------



## **管理员大大求过审**

---

## 作者：_•́へ•́╬_ (赞：1)

### 博弈策略

A 发球。

如果 B 还手，那么

- 如果 A 还手，那么 B 肯定少赢一局了。
- 如果 A 放弃，尽管这次 B 赢了，但是下一局 B 发球，主动权还是在 A 手里，不利于 B。

如果 B 放弃，那么主动权还在 B 手里。



具体地，B 有策略可以赢到 $y$ 局。

策略：

- 前 $x-1$ 局 A 发球，B 放弃。结果：A 赢 $x-1$ 局。
- 第 $x$ 局 A 发球，B 还手，A 没有体力还手了。结果：B 赢 $1$ 局。
- 后 $y-1$ 局 B 发球，A 没有体力还手了。结果：B 赢 $y-1$ 局。

总结：主动权一直在 B 手里。A 赢 $x-1$ 局。B 赢 $y$ 局。

### $code$

```cpp
#include<stdio.h>
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	register char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
main()
{
	register int t,x,y;
	for(read(t);t--;)
	{
		read(x);read(y);
		printf("%d %d\n",x-1,y);
	}
}
```



---

## 作者：小蒟蒻皮皮鱼 (赞：1)

本题重点：

**对于每个人，最大化获胜的场数是第一位的**。

而最大化自己获胜的场数，也就是要尽可能**减少获胜每一场所消耗的体力值。**

一个显然的结论是获胜一场所消耗的最小体力值就是 1 ，即发球所需的体力。

以 $x=2,y=1$ 举例。此时 A 先发球，消耗一点体力。B 如果选择回球，则 B 无法取得胜场。所以此时 B 不回球，A胜利。

此时 $x=1,y=1$ 。A 先发球，发完球后 A 没有体力，B 选择回球，B 胜利。

那么结合上面的结论，由于 A 先发球，则最后的答案是 $x-1, y$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000005;
int T;
int a, b;
int s[10005];
int main()
{
	scanf("%d", &T);
	while(T --)
	{
		scanf("%d%d", &a, &b);
		a --;
		printf("%d %d\n", a, b);
	}
}
```



---

## 作者：Kiloio (赞：0)

## （以下称$Alice$为A，$Bob$为B）    
# 1. $Alice$的情况
- 我们可从题面中得知，如果$A$想赢，她就一定会赢。  

- 然而，$A$是**先手**，最终她发球后，她就没体力接$B$的球了。

- 所以，$A$最多获得$x-1$分.  
# 2. $Bob$的情况
- 我们也从题面中得知，如果$B$想赢，他也一定可以赢。

- 然而，$B$是**后手**，最终$A$发球后，他任然会有体力接球。

- 所以，$B$最多获得$y$分.  

代码：  
```
#include <bits/stdc++.h>
using namespace std;
long long n,x,y;
int main(){
	cin>>n;
	for(int i=1; i<=n; i++){
		scanf("%lld%lld",&x,&y);
		printf("%lld %lld\n",x-1,y);
	}
	return 0;
}
```


---

## 作者：Chtholly_L (赞：0)

# 题解 CF1455C 【Ping-pong】


#### 首先分析一下题， **$A$ 和 $B$ 再玩乒乓球， $A$ 有 $x$ 体力，$B$ 有 $y$ 体力。每次只要和球有交互就会消耗一个体力。**
---

每次由 $A$ 先发球，那么 $A$ 就会先消耗一个体力，假装 $B$ 每次都不回球，那么 $A$ 就会得 $x-1$ 分。

同理， $B$ 不回球，就不会减去第一个体力值，所以 $B$ 会得 $y$ 分，依次，可得最简代码，简单的不得了是不是？？？

接下来上代码

## $Ac$ $Code$
```cpp
#include<iostream>
using namespace std;
int main()
{
	long long Alice,Bob;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>Alice>>Bob;
		cout<<Alice-1<<" "<<Bob<<endl;
	}
	return 0;
}
```
[评测记录](https://www.luogu.com.cn/record/46291914)

[博客食用更佳](https://www.luogu.com.cn/blog/maxsuper/)

---

## 作者：asasas (赞：0)

这题要分开讨论。

$Alice$:由于$Alice$是发球员，所以第一球有$Alice$开始，假设每一球$Bob$都不接，那么$Alice$就可以得分。由于$Alice$获胜了，所以还是她发球，这样知道$Alice$只剩一点体力时，$Bob$接球，$Alice$就不能得分了。所以$Alice$最多能得$x-1$分。

反观$Bob$，当$Alice$体力耗尽后，每一球$Bob$都可以得分，所以$Bob$最多可以得到$y-1$分。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define r register
int main(){
    int n;
    cin >> n;
    while(n--){
    	int a,b;
    	cin >> a >> b;
    	cout << a-1 << ' ' << b << endl;
    }
    return 0;
}
```


---

## 作者：Waaifu_D (赞：0)

~~水题~~

因为A先手，所以最后A只剩最后一点体力时，打出去球就无法还击，所以直接输出**A-1**，B则可以一直还击，故直接输出**B**


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,b,i;//没错这种题都要longlong
int main()
{
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a>>b;
		cout<<a-1<<" "<<b<<endl;
	}
	return 0;
}
```
PS:题库还有一道名为Ping—Pong的题，为黑题，只差一个大小写。。。

---

