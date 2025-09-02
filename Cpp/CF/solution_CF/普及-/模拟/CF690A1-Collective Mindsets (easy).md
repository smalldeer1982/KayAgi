# Collective Mindsets (easy)

## 题目描述

Tonight is brain dinner night and all zombies will gather together to scarf down some delicious brains. The artful Heidi plans to crash the party, incognito, disguised as one of them. Her objective is to get away with at least one brain, so she can analyze the zombies' mindset back home and gain a strategic advantage.

They will be $ N $ guests tonight: $ N-1 $ real zombies and a fake one, our Heidi. The living-dead love hierarchies as much as they love brains: each one has a unique rank in the range $ 1 $ to $ N-1 $ , and Heidi, who still appears slightly different from the others, is attributed the highest rank, $ N $ . Tonight there will be a chest with brains on display and every attendee sees how many there are. These will then be split among the attendees according to the following procedure:

The zombie of the highest rank makes a suggestion on who gets how many brains (every brain is an indivisible entity). A vote follows. If at least half of the attendees accept the offer, the brains are shared in the suggested way and the feast begins. But if majority is not reached, then the highest-ranked zombie is killed, and the next zombie in hierarchy has to make a suggestion. If he is killed too, then the third highest-ranked makes one, etc. (It's enough to have exactly half of the votes – in case of a tie, the vote of the highest-ranked alive zombie counts twice, and he will of course vote in favor of his own suggestion in order to stay alive.)

You should know that zombies are very greedy and sly, and they know this too – basically all zombie brains are alike. Consequently, a zombie will never accept an offer which is suboptimal for him. That is, if an offer is not strictly better than a potential later offer, he will vote against it. And make no mistake: while zombies may normally seem rather dull, tonight their intellects are perfect. Each zombie's priorities for tonight are, in descending order:

1. survive the event (they experienced death already once and know it is no fun),
2. get as many brains as possible.

Heidi goes first and must make an offer which at least half of the attendees will accept, and which allocates at least one brain for Heidi herself.

What is the smallest number of brains that have to be in the chest for this to be possible?

## 样例 #1

### 输入

```
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4
```

### 输出

```
2
```

# 题解

## 作者：朦胧细雨 (赞：4)

## 分析过程：

如题（$2021/8/12$ 翻译），这些海盗都是绝对理智，他们也知道其他海盗都是绝对理智。那么就意味着**不会有人死亡**。
***
***
接下来：

已知不会有人死亡，那么就说明你所提出的方案就必须一次通过，而通过的条件就是题目翻译说的**至少一半或恰好一半人赞同**

我们可以场景代入一下：

如果你拿到的金币数比拿到最多金币数的人的金币数要少，那么你就应该投不赞成。

如下：

|海盗标号  | $1$  | $2$  | $3$  | $4$  |
|:------:  | :--: | :--: | :--: | :--: |
|所得金币  | $2$  | $1$  | $1$  | $0$  |
|是否赞成  | √ | × | × | × |

显而易见，GAMEOVER。
***
***
所以想要活下来，就必须拉拢别人，而题目又说要输出最小金币数。很简单，只拿一金币就好了。

如下：

|海盗标号  | $1$  | $2$  | $3$  | $4$  |
|:------:  | :--: | :--: | :--: | :--: |
|所得金币  | $1$  | $1$  | $0$  | $0$  |
|是否赞成  | √ | √ | × | × |

这就是样例。
***
***

## 结论：

让一半的人都分到 $1$ 金币就可以了，但是注意向上取整。

代码（省略头文件）：
```cpp
int main()
{
	std::cin>>n;
	std::cout<<((n-1)/2);
	return 0;
}
```

### 后记：

计算 $A÷B$ 向上取整的小技巧：$(A+B-1)÷B$。

---

## 作者：Confringo (赞：3)

## 问题简述
有 $N$ 个僵尸想要大脑，请你提出一个方案使一半以上（或刚好一半）的僵尸通过该方案（包括你自己也可以投票），最少需要多少个脑子才行？（此处尊重原题）

---

## 推导过程
我们从最后一个提出方案的僵尸开始推导：  

注意：此处我们把所有僵尸的顺序反了一下，原来是 $1..N$，现在变为 $N..1$。

### 第 $1$ 个僵尸（最后一个提方案的）
如果第 $1$ 个僵尸提出方案，不管怎么样都可以得到所有大脑。

### 第 $2$ 个僵尸（倒数第二个，以下略）
因为第 $1$ 个僵尸一定会投反对票（不管怎么样他的方案都不会比自己的好），所以干脆一个大脑都不分配给第 $1$ 个僵尸，自己全部拿走。

### 第 $3$ 个僵尸
第 $3$ 个僵尸想到第 $1$ 个僵尸绝对没有希望提出方案，而 $1$ 号自己得不到任何大脑，所以只要给他 $1$ 个大脑就可以让他支持自己，自己得到其他所有大脑。

### 第 $4$ 个僵尸
第 $4$ 个僵尸想到第 $2$ 个僵尸不希望看到第 $3$ 个僵尸提出方案，（他自己也不愿意，显而易见，不然他就没了）所以他会用 $1$ 个大脑让第 $2$ 个僵尸支持他，这样他获得其余全部大脑。

### 下同。

显而易见地，只需要让序号和自己同奇偶性的僵尸都分配到 $1$ 个大脑，自己获得其他全部就可以了。

当 $N$ 为奇数时，让别的僵尸支持你需要 $\lfloor\frac{N}{2}\rfloor$ 个大脑，自己需要至少 $1$ 个大脑，所以就是 $\lfloor\frac{N}{2}\rfloor+1$，也就是 $\lceil\frac{N}{2}\rceil$ 个。

当 $N$ 为偶数时，让别的僵尸支持你需要 $N\div2-1$ 个大脑，自己需要至少 $1$ 个大脑，所以就是 $N\div2$个，也可以写作 $\lceil\frac{N}{2}\rceil$ 个。

因此不论奇数偶数，需要的最少大脑都是 $\lceil\frac{N}{2}\rceil$ 个，因此即为 $\lceil\frac{N}{2}\rceil$。

---

## 答案
最少需要 $\lceil\frac{N}{2}\rceil$ 个大脑。

---

## 完整代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    cout<<int(ceil(n/2.0));
    return 0;
}
```

---

## 作者：断清秋 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF690A1)

经典的海盗分金币问题。与经典模型不同的地方是只要投反对票的人**不超过**半数，这个人就不会死，并且如果某个人当前分得的金币数**不优于**以后可能获得的最大金币数，也会投反对票。

不过可以发现在这个问题中，这两个不同点都不是问题。因为第一个海盗至少要 $1$ 枚金币，所以他只会获得一枚金币，其余必须要花费的金币就要给那些编号为 $2$ 的海盗不会给金币的海盗们，于是他的最佳分配方案必然是 $1010101…$ 依次分配，与经典模型的分配规律完全一致。

因此答案就是 $\left\lceil\dfrac{n}{2}\right\rceil$。

时间复杂度 $O(1)$。

代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define back return
#define ri register int
#define ull unsigned ll
using namespace std;
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=x*10+ch-'0';
		ch=getchar();
	}
	back x*f;
}
ll t,n,s;
int main()
{
	n=read();
	cout<<(n+1)/2<<"\n";
	back 0;
}
```

---

## 作者：Cure_Wing (赞：1)

### 题目：

有 $n$ 个海盗被编号为 $1\sim n$，并且他们都是绝对理智的，并且他们都知道他们都是绝对理智的，等等。

现在他们要分一些金币。从编号 $1$ 的海盗开始，每个人依次提出一个分配方案，如果有至少一半人（恰好一半也行）赞成则通过此方案，否则将这个人杀死并由下一个继续提出分配方案。

每个海盗的第一目标都是保命，其次是拿到更多的金币，再其次是杀掉更多的人。

现在你编号为 $1$ 的海盗，求金币数至少为多少时，你可以在活下来的同时拿到至少 $1$ 枚金币。

金币不可分割，只能给人分配整数枚金币。

### 思路
你作为编号为 1 的海盗，你要做的是什么？活下去！  
为了活下去，你必须使一半以上的人同意你不死，为了使损失（付出的金币）最少，那么我们最好贿赂最少的人，就是恰好一半。那么哪些人会不让你死呢？就是那些得到金币（得到好处）的人。  
那么我们要让一半的人得到金币~~跟你去做无耻的事~~，就认为我们至少要付出一半的人数的金币，也就是付出 $\left\lceil\frac{N}{2}\right\rceil$ 枚金币就可以了，~~尽管其他人十分气愤，也没办法改变法律。~~

### 代码：
十分简单的代码：
```python
n=int(input())
if n%2:
    print(n//2+1)//付出一半多的金币的情况
else:
    print(n//2)//恰好付出一半的情况
################# python3
```


---

## 作者：Yyxxxxx (赞：0)

## $Solution$
对于第$n-1$个人的情况，没有拿到钻石的人一定要在第$n$个人的情况下拿到钻石才会支持第$n$ 个人。    

枚举易得
个数即为$0,1,1,2,2,3,3,4,4,5,5...$   
归纳容易得出$Ans=\lceil \dfrac{n}{2}\rceil$
## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){int x;scanf("%d",&x);printf("%d",x+1>>1);}
```

---

