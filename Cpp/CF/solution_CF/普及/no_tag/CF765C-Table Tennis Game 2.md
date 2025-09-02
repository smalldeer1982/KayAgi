# Table Tennis Game 2

## 题目描述

Misha and Vanya have played several table tennis sets. Each set consists of several serves, each serve is won by one of the players, he receives one point and the loser receives nothing. Once one of the players scores exactly $ k $ points, the score is reset and a new set begins.

Across all the sets Misha scored $ a $ points in total, and Vanya scored $ b $ points. Given this information, determine the maximum number of sets they could have played, or that the situation is impossible.

Note that the game consisted of several complete sets.

## 说明/提示

Note that the rules of the game in this problem differ from the real table tennis game, for example, the rule of "balance" (the winning player has to be at least two points ahead to win a set) has no power within the present problem.

## 样例 #1

### 输入

```
11 11 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
11 2 3
```

### 输出

```
-1
```

# 题解

## 作者：DPseud (赞：5)

[戳这里返回题目](https://www.luogu.com.cn/problem/CF765C)

大佬们都是用很多个 if-else 语句的，但是代码要追求简洁，是用三目运算符和逻辑运算符可以将主体缩到一行，大致思路就是如果 $a$ 和 $b$ 都大于 $k$，直接都除以 $k$ 就能让局数最多，如果 $a$ 或 $b$ 大于 $k$，那么需要判断大于 $k$ 的一方能否被 $k$ 整除，如果不能被整除，那么显然是不可能的，要输出 -1，因为另一方已经没有赢过了，而这一方又无法被 $k$ 整除，能看出这一方是不能通过任何方式获得分数的，自然不可能，至于 $a$ 和 $b$ 都小于 $k$ 的，那就更不行了。

最后放一下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int a,b,k;
	cin>>k>>a>>b;
	cout<<(((a>=k&&b>=k)||(a>=k&&b<k&&a%k==0)||(b>=k&&a<k&&b%k==0))?a/k+b/k:-1);//因为优先级问题，三目运算符外面必须再加一个括号
 	return 0;
}
```


---

## 作者：_Haoomff_ (赞：3)

要求比赛的局数最多，只有两人轮流赢，才会达到条件。

“请注意，每一局都是完整的一局”，这是重点。接下来，就会出现几种情况：第一种，两人的分数都不到结束条件，即 $a$ 和 $b$ 都小于 $k$，不完整，输出“-1”；第二种，一人的分数不到结束条件，但是另一人的分数不是结束条件的倍数，也不完整，亦输出“-1”，但是注意，这里可能是 $a$ 不到，$b$ 超出，也有可能是 $b$ 不到，$a$ 超出，因此要判断两次；第三种，就是正常情况，输出两人得分除以结束条件的和即最多局数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int k,a,b;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>k>>a>>b;
	if(a<k&&b<k)cout<<-1;
	else if(a/k==0&&b%k!=0)cout<<-1;
	else if(b/k==0&&a%k!=0)cout<<-1;
	else cout<<a/k+b/k;
	return 0;
}
```


---

## 作者：Refined_heart (赞：2)

题目大意就是给出胜利标准和总分，求总场数。

$\text{Solution:}$

显然每次让一个人全胜这样的局数最多。

考虑无解情况，这也是坑点。

一种，最大值都小于胜利标准，显然无解。

另一种，当自己的分数和胜利标准的余数有剩余的时候，且自己没有输过任何一局的时候，显然是不能成立的。故也无解。

剩下的就直接将两个人的得分除以胜利标准，求和即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll k,a,b,ans,c;
int main(){
	cin>>k>>a>>b;
	if(a<k&&b<k){
		puts("-1");
		return 0;
	}
	ans+=a/k;
	ans+=b/k;
	if(a/k==0&&b%k!=0){
		puts("-1");
		return 0;
	}
	if(b/k==0&&a%k!=0){
		puts("-1");
		return 0;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Orange_Sky_Fish (赞：1)

## 思路

求的是最多的比赛场数，让两方轮流获胜就行了。

但是还是有三个无解的情况。

- 第一种情况是两方分数都达不到指定的分数。
- 第二种情况是第一个人赢不了整数轮而第二个人达不到指定分数。
- 第三种情况是第一个人达不到指定分数而第二个人赢不了整数轮（和第二种差不多）。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int k,a,b;
	scanf("%d%d%d",&k,&a,&b);
	if(a<k&&b<k) {
		printf("-1");
		return 0;
	}
	else if(a%k!=0&&b<k) {
		printf("-1");
		return 0;
	}
	else if(b%k!=0&&a<k) {
		printf("-1");
		return 0;
	}
	else {
		printf("%d",a/k+b/k);
		return 0;
	}
}
```


---

## 作者：Pkixzx (赞：1)

这道题的代码还是比较容易实现的。

因为这道题要判断**是否有可能发生**，所以，我们要按发生或不发生两种情况来考虑。

1.不可能发生

        （1）如果说a,b两数都小于k这种情况显然是不可能发生，要输出'-1'。
        
        （2）如果a每一局都赢了，但是b的值却不为0，显然不可能发生，要输出'-1'。
        
        （3）如果如果b每一局都赢了，但是a的值却不为0，显然不可能发生，要输出'-1'。
        
2.可能发生

          这时，我们让一个人每次全胜，再让另一个人每次全胜，这样即可获得最大值。
          
有了思路就很好写了，我们只需要4个判断即可。（~~话说4个判断为什么是黄题~~

代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int a[1000010],b[100010];
int main(){
	long long n,m,x,y,num,k;
	cin>>k>>n>>m;
	if(n<k&&m<k)//不可能的第一种情况
	cout<<-1;
	else if(n/k==0&&m%k!=0)//不可能的第二种情况
	cout<<-1;
	else if(m/k==0&&n%k!=0)//不可能的第三种情况
	cout<<-1;
	else
	cout<<n/k+m/k;//可能的情况
	return 0;
}
```


---

## 作者：Morax2022 (赞：0)

# CF765C 题解
**思路**

本题要想比赛场数多，只需要让双方轮流获胜就可以了，但是在本题中可能出现胜利分 $a, b$ 未用完的情况。

- 第一种是双方分数都小于要求分。
- 第二种是一方赢不了整数轮而另一方不够胜一轮。

# AC Code
```c
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int k, a, b;//要求分与双方得分
	cin >> k >> a >> b;
	if ((a < k && b < k) || (a % k != 0 && b < k) || (b % k != 0 && a < k))
	cout << "-1";//根本不够赢或一方赢不了整数轮另一方不够赢 
	else cout << a / k + b / k; //双方轮流赢 
} 
```

希望本题解能给大家带来帮助！

---

## 作者：封禁用户 (赞：0)

#### 题目分析

既然题目让我们确定比赛的最多局数，那我们就可以先让其中一个人尽可能多赢，再让另一个人尽可能多赢，这样局数最多。

不过还有一些情况是不可能出现的：

1. $a$ 和 $b$ 都小于 $k$。

2. $a<k$ ，但 $b$ 不是 $k$ 的倍数。

3. $b<k$ ，但 $a$ 不是 $k$ 的倍数。

其余情况输出两个人的得分除以 $k$ 即可。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,k;
int main()
{
	cin>>k>>a>>b;
	if((a<k&&b<k)||(a<k&&b%k!=0)||(b<k&&a%k!=0))cout<<-1;
	else cout<<a/k+b/k;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

# 题意

米莎和瓦尼亚打乒乓球。每盘由几次发球组成，每一次发球都由一名队员赢得，他得一分，输的一分也得不到。一旦其中一个玩家刚好获得 $K$ 分，该分数将被重置，并开始新的一局。

在所有的比赛中，米莎总分 $A$ 分，瓦尼亚总分 $B$ 分。根据这些信息，确定他们比赛的最多局数，或者情况是不可能发生的。

请注意，每一局都是完整的一局。

# 思路

其实不可能只有 $3$ 种情况：

情况 $1$: 当米莎的总分小于 $K$ 且瓦尼亚的总分也小于 $K$ 时输出 $-1$。

情况 $2$：当米莎刚好赢了 $A$ $\div$ $K$ 局时且瓦尼亚的总分 $\%$ $K$ 不为 $0$ 输出 $-1$。

情况 $3$：当瓦尼亚刚好赢了 $B$ $\div$ $K$ 局时且米莎的总分 $\%$ $K$ 不为 $0$ 输出 $-1$。 

其它情况都输出 $A$ $\div$ $K$ 加上 $B$ $\div$ $K$（比赛的最多局数）。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long k,x,y;
int main()
{
	cin>>k>>x>>y;//x代表A，y代表B
	if(x<k&&y<k||x/k==0&&y%k!=0||y/k==0&&x%k!=0) cout<<-1;//不可能的三种情况
	else cout<<x/k+y/k;//比赛的最多局数
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：0)

$\verb!upd:!$ 应审核要求，将丑的不行的 `$\mod$` 换成了 `$\bmod$`。

# 题目大意

米莎和瓦尼亚打乒乓球。每盘由几次发球组成，每一次发球都由一名队员赢得，他得一分，输的一分也得不到。一旦其中一个玩家刚好获得 $K$ 分，该分数将被重置，并开始新的一局。

在所有的比赛中，米莎总分 $a$ 分，瓦尼亚总分 $b$ 分。根据这些信息，确定他们比赛的最多局数，或者情况是不可能发生的，如果不可能，请输出 $\mathbf{-1}$。

**请注意，每一局都是完整的一局。**

# 题目分析

+ 如果 $a,b<k$，绝对不可能，此时输出 $\mathbf{-1}$。

+ 如果 $a<k,b\bmod k\neq0$，表示 $a$ 全都赢了，但是 $b\bmod k\neq0$ 也不可能，输出 $\mathbf{-1}$。

+ 如果 $b<k,a\bmod k\neq0$ 同理。

+ 其他情况输出 $\left\lfloor\dfrac{a}{k}+\dfrac{b}{k}\right\rfloor$。

# 代码

```cpp
//2022/1/14

int k,a,b;

int main(void)
{
	k=read(),a=read(),b=read();
	
	bool mark=(a<k && b<k) || (a<k && b%k!=0) || (b<k && a%k!=0); 
	
	printf("%d\n",mark==true?-1:(a/k)+(b/k));
	
	return 0;
}
```

---

## 作者：Colead (赞：0)

核心思路十分简单：为了多打几局，能让对方爆零就让对方爆零。

- 如果双方得分都不止一局的最大分数，那就直接让对方爆零，多出来的余数随便分给哪一盘。

- 如果有一方得分不止一局的最大分数而另一方没有，说明另一方没赢过，如果多的一方正好分数是一局满分的整数倍，则可以实现。

- 如果两方都没打满一局，当然不可能了。

比较简单。不多说，上代码。
```
#include<bits/stdc++.h>
using namespace std;
long long k,a,b;
int main()
{
	cin>>k>>a>>b;
	if(a>=k&&b>=k)
	{
		cout<<a/k+b/k<<endl;
		return 0;
	}
	else if(a>=k&&b<k)
	{
		if(a%k==0)cout<<a/k<<endl;
		else cout<<"-1"<<endl;
		return 0;
	}
	else if(a<k&&b>=k)
	{
		if(b%k==0)cout<<b/k<<endl;
		else cout<<"-1"<<endl;
		return 0;
	}
	cout<<"-1"<<endl;
	return 0;
}
```

[AC记录谁想看的贴一发](https://www.luogu.com.cn/record/64191619)


---

