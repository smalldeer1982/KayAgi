# Charmed by the Game

## 题目描述

Alice 和 Borys 在打网球。

网球比赛有很多局，每局有一个人发球，有一个人接发球。这样轮流交换，一人一局。

每局比赛都有一个胜者，如果胜者是发球者，那么称为保发，反之称为破发。

我们知道 Alice 赢了 $a$ 局，Borys 赢了 $b$ 局，但我们不知道谁先发球和每局谁赢了。

问所有可能的总破发次数。

## 样例 #1

### 输入

```
3
2 1
1 1
0 5```

### 输出

```
4
0 1 2 3
2
0 2
2
2 3```

# 题解

## 作者：KSToki (赞：4)

# 题目大意
两个人交叉先后手进行了 $a+b$ 轮博弈，A 赢了 $a$ 轮，B 赢了 $b$ 轮，第一轮任意一个人先手，问可能有多少轮后手赢。
# 题目分析
可能和大众做法枚举判断不太一样。

这题我们可以转化一下，令 A 赢为 $1$，B 赢为 $0$。若 A 先手，则求在奇数位上的 $1$ 的数量和在偶数位上 $0$ 的数量；若 B 先手，则求在偶数位上的 $1$ 的数量和在奇数位上 $0$ 的数量。到时候分情况算即可。

假设现在已经有一个 $01$ 序列，得出按上述方法计算的答案，那我们总可以通过交换两个不同位置上的数从而生成任意情况的 $01$ 序列，**而这个操作不会改变答案的奇偶性**，证明很简单，分类讨论有效或无效的 $01$ 就可以了。

因此我们只需要得到某一种情况下的上下界就可以得出答案了。上下界还是比较好构造的，先 $01$ 交替再把剩下的填后面，可以发现如果 $a+b$ 是偶数，那么两种情况下的答案是一样的，而 $a+b$ 是奇数的时候两种情况下的答案会差 $1$，产生的原因就是后面剩的那一串 $0$ 或 $1$ 了。

代码实现起来可以简化很多。
# 代码
```cpp
#include<bits/stdc++.h>
#define YPC rubbish 
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pb push_back
#define pii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define chkmin(x,y) (x=min(x,y))
#define chkmax(x,y) (x=max(x,y))
#define inv(x) ksm(x,Mod-2)
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
#define For(i,x,y) for(R int i=x;i<=y;++i)
#define Rof(i,x,y) for(R int i=x;i>=y;--i)
#define ForG(i,edge,x) for(auto i:edge[x])
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,a,b,n;
int main()
{
	T=read();
	while(T--)
	{
		a=read();
		b=read();
		n=a+b;
		if(a>b)
			swap(a,b);
		int l=(n-2*a)/2,r=(n-2*a+1)/2+2*a;
		if(n&1)
		{
			putint(r-l+1);
			For(i,l,r)
				printf("%d ",i);
		}
		else
		{
			putint((r-l)/2+1);
			for(R int i=l;i<=r;i+=2)
				printf("%d ",i);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：3)

# CF1558A Charmed by the Game 题解

大家好像都用的很复杂的算法，所以我来发一篇简单找规律的题解。

## 题目大意

------------
Alice 和 Borys 打网球，网球比赛由局组成，每局有 $1$ 名选手执发，$1$ 名选手接发，选手轮流执发。如果执发的选手输了，则称为破发。

Alice 赢了 $a$ 局，Borys 赢了 $b$ 局，不确定是谁先执发。

找出所有的 $k$ 值，使得 Alice 和 Borys 之间的比赛恰好有 $k$ 局破发。

## 题目分析

------------

找规律加分类讨论即可。

### 举个例子：

#### $4$ 局的情况：

```txt
2 2        1 3        0 4
0 V        0 X        0 X
1 X        1 V        1 X
2 V        2 X        2 V
3 X        3 V        3 X
4 V        4 X        4 X
```

#### $5$ 局的情况：

```txt
2 3        1 4        0 5
0 V        0 X        0 X
1 V        1 V        1 X
2 V        2 V        2 V
3 V        3 V        3 V
4 V        4 V        4 X
5 V        5 X        5 X
```

### 总结一下规律：

#### 当总局数为奇数时：
+ 开头结尾各有 $(\text{差}-1)\div 2$ 个不存在的解。

#### 当总局数为偶数时：

+ 开头结尾各有 $\text{差}\div 2$ 个不存在的解。
+ 如果 $\text{差}\bmod 4 = 0$：则偶数时存在。
+ 如果 $\text{差}\bmod 4 = 1$：则奇数时存在。

理清思路后，代码就很容易写了。
## 代码
```
#include<bits\stdc++.h>
using namespace std;
int t , a , b , c , k , ans[200005];
void ok()
{
	if(c % 2 == 1)
	{
		int tmp = b - a - 1;
		for(int i = tmp / 2 ; i <= c - tmp / 2 ; i++)
		{
			ans[k] = i;
			k++;
		}
	}
	else
	{
		int tmp = b - a;
		for(int i = tmp / 2 ; i <= c - tmp / 2 ; i++)
		{
			if(tmp % 4 == 0 && i % 2 == 0)
			{
				ans[k] = i;
				k++;
			}
			if(tmp % 4 == 2 && i%2 == 1)
			{
				ans[k] = i;
				k++;
			}
		}
	}
	return;
}
int main()
{
	cin >> t;
	while(t--)
	{
		k = 0;
		scanf("%d%d" , &a , &b);
		c = a + b;
		if(b < a)
		{
			swap(a , b);
		}
		ok();
		printf("%d\n" , k);
		for(int i = 0 ; i < k ; i++)
		{
			printf("%d " , ans[i]);
		}
		cout << endl;
	}
	return 8;
}
```

---

## 作者：qusia_MC (赞：2)

**以下简称保发为保，破发为破。**
## 题目大意
就是两个人轮流比赛，依次打先手。对方先手赢了为破。已知两个人赢得局数，求破的所有可能性。
## round 1（找规律）
看一下样例：（方便一些，一组一组看）
```
输入：2 1
输出：
4
0 1 2 3
输入：1 1
输出：
2
0 2
```
发现了神马？？
- 当两个数 $a,b$ 的和为奇数的时候输出的是一个公差为 $1$ 的等差数列。

- 反之，当两个数 $a,b$ 的和为偶数的时候输出的是一个公差为 $2$ 的等差数列。

接下来我们还要判断这个等差数列的首项和末项。(假设 Alice 胜的次数比 Borys 多)

- 破最少的情况下，Alice 和 Borys 一起在各自的先手局里赢了 $\min(a,b)$ 场，剩下的全都是 Alice 赢了。

- 破最多的情况下，我们把 Alice 和 Borys 一起赢得那些全都变反。这样就能最多。

那具体怎么算呢？
- 当 $a+b$ 的和为偶数的时候，每个人都发了 $\frac{a+b}{2}$ 次。此时，破最大就是 $|a-\frac{a+b}{2}|$ 次。由于我们之前假设 $a$ 一定比 $b$ 大，所以可以去掉绝对值。破最大就是全都反过来，是两人赢得局数之和减去上面求出来的破最少的次数（由于全都反过来，所以本来是破就变成保了）。

- 当 $a+b$ 的和为奇数的时候，Alice 发了 $\lceil \frac{a+b}{2}\rceil$ 次，反之，Borys 发了 $\lfloor\frac{a+b}{2}\rfloor$ 次。同样的，我们和上面一种情况一样，破最小是 $a-\lceil\frac{a+b}{2}\rceil$ 次，破最大就是是两人赢得局数之和减去上面求出来的破最少的次数。

好了，有了这个思路就能打出大致代码：

```
int a,b,t;
cin>>t;
while(t--)
{
    int a,b,maxn,minn;
    cin>>a>>b;
    if(a<b)swap(a,b);
    if((a+b)%2==0)
    {
        minn=a-(a+b)/2,maxn=a+b-minn;
        cout<<(maxn-minn)/2+1<<endl;
        for(int i=minn;i<=maxn;i+=2)
        {
            cout<<i<<" ";
         }
     }
     else
     {
         minn=a-ceil(1.0*(a+b)/2)),maxn=a+b-minn;
         cout<<maxn-minn+1<<endl;
        for(int i=minn;i<=maxn;i++)
        {
            cout<<i<<" ";
         }
     }
     cout<<endl;
 }
 ```
 ## round 2(证明）
做题不能这样啊，只是找个规律，还要证明一下。
 
由于胜局是一定的，所以我们让他们有两局赢得情况反过来。这样，就有三种情况：

- 全是保：反过来都变成破，破次数   $+2$。

- 全是破：反过来都变成保，破次数   $-2$。

- 一破一保：反过来是一保一破，没有意义（由于只统计次数）。

**很多人都会好奇：为什么奇数和偶数输出有区别呢？？**

首先，如果是奇数的话，我们完全可以换个人发球，由于发球次数是不同的，所以可以让 Alice 赢得后面几球中的保和破反过来。由于后面的局数一定是奇数，所以每次就能让破的次数 $+1$ 或 $-1$。而偶数就不行了，怎么换都不会改变。

做个图你们看看（$1$ 表示赢，反之 $0$ 就是输）：

奇数：（假设 Alice 赢了 $5$ 局，borys 赢了 $2$ 局）

|发球人：  | Alice |borys  | Alice |borys  |  Alice|  borys |Alice |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| Alice: |  1| 0 | 1 | 0 |  1|  1|1  |
| borys: |  0|  1|  0|  1|0  | 0 | 0 |

此时，破次数为 $1$（在第 $6$ 局）。
交换一下两人的发球：（前面还是全保，到了后面再看）

|发球人：  | borys |Alice  | borys |Alice   |  borys|  Alice  |borys |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| Alice: |  0| 1 | 0 | 1 |  1|  1|1  |
| borys: |  1|  0|  1|  0|0  | 0 | 0 |

此时，破次数为 $2$（第 $5,7$ 局）。

怎么样，明白了吧？

再做个对比，偶数（设 Alice 赢了 $4$ 局，borys 赢了 $2$ 局）

|发球人：  |Alice   |borys  |Alice  |borys |  Alice  |  borys|
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | 
| Alice: |  1| 0 | 1 | 0 |  1|  1|
| borys: |  0|  1|  0|  1|0  | 0|

此时，破次数为 $1$（在第 $6$ 局）。
交换一下两人的发球：（前面还是全保，到了后面再看）

|发球人：  | borys |Alice  | borys |Alice   |  borys|  Alice  |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | 
| Alice: |  0| 1 | 0 | 1 |  1|  1|1  |
| borys: |  1|  0|  1|  0|0  | 0 | 0 |

破次数还是 $1$（第 $5$ 局）。

这下明白了吧？奇数破的情况是交错的（类似于下图）：
```
Alice: 3    5    7
borys:   4    6
      ↓ ↓ ↓ ↓ ↓
结果： 3  4  5  6  7
```



  偶数就是重合的：
```
Alice：3  5  7
borys：3  5  7
       ↓ ↓ ↓
结果： 3  5  7
 ``` 
 这下你们明白了吧？
 
 ## code
 ```
 #include<bits/stdc++.h>
using namespace std;
int t,a,b;
int minn,maxn;
int main(){
	cin>>t;
	while(t--){
		cin>>a>>b;
		if(a<b)swap(a,b);
		if((a+b)%2==1){
			minn=a-(a+b+1)/2;
			maxn=a+b-minn;
			cout<<maxn-minn+1<<endl;
			for(int i=minn;i<=maxn;i++){
				cout<<i<<" ";
			}
		}
		else{
			minn=a-(a+b)/2;
			maxn=a+b-minn;
			cout<<(maxn-minn)/2+1<<endl;
			for(int i=minn;i<=maxn;i+=2){
				cout<<i<<" ";
			}
		}
		cout<<endl;
	}
	return 0;
}
```
写了 $150%$ 多行，点个赞再走呗。

---

## 作者：cszhpdx (赞：2)

## 大概题意（本题主要难点

小 A 小 B 轮流负责接球发球，已知小 A 赢了 $a$ 场，小 B 赢了 $b$ 场，求接球手胜利的次数有多少可能，分别是什么

## 解法

设

- ca 为 A 发球的次数
- cb 为 B 发球的次数

---

- AA 为 A 发球 A 赢了的局数
- AB 为 A 发球 B 赢了的局数
- BA 为 B 发球 A 赢了的局数
- BB 为 B 发球 B 赢了的局数

显然 $AA+AB=ca,BA+BB=cb,AA+BA=a,AB+BB=b$ 

于是我们分类讨论 $ca,cb$ 枚举 $AA \in [0,\min(a,ca)]$ 注意到 $a-AA\le cb$ ，也就是 $BA\le cb$ 

这题主要难点在于读题，也许是因为本蒟蒻英语太差了，搞了半天才明白

代码：

```cpp
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define mem(a, x) memset(a, x, sizeof(a))
#define rps(i, b, e) for(int i=(b);i<=(e);i++)
#define prs(i, e, b) for(int i=(e);i>=(b);i--)
#define rp(i, e) rps(i, 1, e)
#define pr(i, e) prs(i, e, 1)
#define rp0(i, e) rps(i, 0, (e)-1)
#define pr0(i, e) prs(i, (e)-1, 0)
#define rpg(i, x) for(int i=head[x];i;i=e[i].nxt)
#define opf(s) freopen(s".in", "r", stdin), freopen(s".out", "w", stdout)
using namespace std;
const int NR=2e5+10;
int T, a, b, n, ca, cb;
//ca,cb分别是A,B发球次数 
char s[NR];
int m, ans[NR];
void calc() {
	rps(i, 0, min(a, ca)) {
		//枚举有多少是A发球的时候A赢的
		if(a-i>cb)continue;
		ans[++m]=a-i+ca-i;
	}
}
int main()
{
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &a, &b);
		m=0, n=a+b;
		ca=n/2+(n&1), cb=n-ca, calc();
		swap(ca, cb), calc();
		sort(ans+1, ans+m+1);
		m=unique(ans+1, ans+m+1)-ans-1;
		printf("%d\n", m);
		rp(i, m)printf("%d ", ans[i]);
		puts("");
	}
	return 0;
}
```

 

---

## 作者：WsW_ (赞：1)

## 更新
1. 2023/7/5 17:01根据要求修改了 $\LaTeX $：更换取较大值函数和调大行内分式  

感谢指出错误！
## 思路：
>题目中提到：  
>>这样轮流交换，一人一局。  

因为不知道谁先发球，因此必须**分类讨论**。  
* 一、$a+b$ 为偶数时。  

此时一定是 A、B 分别发球 $\dfrac{a+b}{2}$ 局，此时答案与谁先发球无关。  
先找“破发”次数**最少**的情况：显然，当发球数尽量与获胜数相近时，“破发”次数最少。简单地说，尽量谁发球谁获胜，剩下配对不了的就是“破发”。设“破发”次数**最少**为 $minn$ ，则 
$$minn= |a- \frac{a+b}{2}|= \max (a,b)- \frac{a+b}{2}$$ 
再找“破发”次数**最多**的情况：显然，当“保发”次数最少时，“破发”次数最多。再上一种情况上，所有发球全部反过来，此时“破发”变“保发”，“保发”变“破发”。设“破发”次数**最多**为 $maxx$ 则
$$maxx=a+b-minn$$
最后，求有哪些**不同**情况：我们对已有情况做出一些调整，交换两场两人的获胜情况，交换后有三种情况。  
1.如果两场都是“破发”，那么交换后都不是“破发”，“破发”次数减二。  
2.如果两场都不是“破发”，那么叫交换后都是“破发”，“破发”次数加二。
3.如果两场一破一保，交换后是一保一破，“破发”次数不变。  
由此可见，“破发”次数要么减二，要么加二，而且必定存在。显然 $maxx$ 和 $minn$ 奇偶性**相同**，所以不断加二或减二就可以得到所有的“破发”次数。
* 二、$a+b$ 为偶数时。

此时 A、B 先发球的人发球 $\dfrac{a+b+1}{2}$ 场，另一个人发球 $\dfrac{a+b-1}{2}$ 场，显然： 
$$\frac{a+b+1}{2}>\frac{a+b-1}{2}$$  
先找“破发”次数**最少**的情况：显然，当发球数尽量与获胜数相近时，“破发”次数最少。我们让获胜次数较多的人对应较多的发球场数，剩下配对不了的就是“破发”。设“破发”次数**最少**为 $minn$ ，则 
$$minn=\max(a,b)-\frac{a+b+1}{2}$$ 
再找“破发”次数**最多**的情况：显然，当“保发”次数最少时，“破发”次数最多。再上一种情况上，所有发球全部反过来，此时“破发”变“保发”，“保发”变“破发”。设“破发”次数**最多**为 $maxx$ 则
$$maxx=a+b-minn$$
最后，求有哪些**不同**情况：我们对已有情况做出一些调整，交换两场两人的获胜情况，交换后有三种情况。  
1.如果两场都是“破发”，那么交换后都不是“破发”，“破发”次数减二。  
2.如果两场都不是“破发”，那么叫交换后都是“破发”，“破发”次数加二。
3.如果两场一破一保，交换后是一保一破，“破发”次数不变。  
由此可见，“破发”次数要么减二，要么加二，而且必定存在。显然 $maxx$ 和 $minn$ 奇偶性**不同**，所以不断加一或减一就可以得到所有的“破发”次数。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,a,b;
int minn,maxx;
int main(){
	cin>>t;
	while(t--){
		scanf("%d%d",&a,&b);
		if((a+b)&1){//奇数
			minn=max(a,b)-(a+b+1)/2;
			maxx=a+b-minn;
			printf("%d\n",maxx-minn+1);
			for(int i=minn;i<=maxx;i++){
				printf("%d ",i);
			}
		}
		else{
			minn=abs(a-(a+b)/2);
			maxx=a+b-minn;
			printf("%d\n",(maxx-minn)/2+1);
			for(int i=minn;i<=maxx;i+=2){
				printf("%d ",i);
			}
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：vectorwyx (赞：1)

我们把问题抽象成 01 串来理解：给定正整数 $a,b$，现在有一个 01 交替出现的 01 串 $s$（开头是 $0$ 是 $1$ 都有可能）和另一个 01 串 $t$，已知 $s$ 和 $t$ 的长度均为 $a+b$ 且 $t$ 有 $a$ 个 $1$。求所有可能的 $\operatorname{popcount}(s \mathbin{\mathrm{xor}} t)$ 并升序输出

~~观察样例不难发现~~对于一个固定的 $s$（注意 $s$ 实际上有两种情况，这里随便取一种，后面会解释），答案序列总是一个公差为 $2$ 的等差数列。为什么？我们先随便写一个满足条件的 $t$，然后考虑交换它的任意相邻两位对于答案的影响。如果交换的是 `11` 或 `00` 则答案不变，如果交换的是 `10` 且 $s$ 对应的两位是 `01` 则答案 $-2$，如果 $s$ 对应的两位是 `10` 则答案 $+2$，其余情况同理。

也就是说交换 $t$ 的相邻两位对于 $\operatorname{popcount}(s \mathbin{\mathrm{xor}} t)$ 的影响只可能是 $-2,0,2$ 中的一个。而从任意一个符合条件的 $t$ 开始执行若干次交换操作总能得到全体满足条件的 $t$ 集合，故答案序列必定是一个公差为 $2$ 的等差数列。

综上，我们只需要求出答案的最小值和最大值就能得到对于某个固定的 $s$ 的答案序列，求最小值只需要把 $t$ 中的 $0$ 尽量和 $s$ 中的 $0$ 放在一块，求最大值只需要把 $t$ 中的 $0$ 尽量和 $s$ 中的 $1$ 放在一块。但 $s$ 有两种情况怎么办？假设第一种情况为 $s1$，第二种情况为 $s2$，由于 $s1$ 和 $s2$ 的每一位均不相同，所以 $s1$ 每有一个答案 $x$，$s2$ 就会有一个答案 $a+b-x$。这样就可以只求一个 $s$ 的答案序列。其实对 $s1$ 和 $s2$ 分别求一遍答案序列再合并也可以，就是略微有点麻烦（

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>
#include<queue>
#include<map>
#define pb push_back
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define db double
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,fh=1; char ch=getchar(); while(!isdigit(ch)){if(ch=='-') fh=-1; ch=getchar();} while(isdigit(ch)){x=(x<<1)+(x<<3)+ch-'0'; ch=getchar();} return x*fh;}

const int N=1e6+5;
int a[N];

void solve(){
	int x=read(),y=read(),z=x+y,c0=z/2,c1=z-c0,l,r;
	fo(i,0,z) a[i]=0;
	if(x<=c1) l=c1-x;
	else l=x-c1;
	if(x<=c0) r=x+c1;
	else r=c0+y;
	for(int i=l;i<=r;i+=2) a[i]=1;
	int rp=0;
	fo(i,0,z) if(a[i]|a[z-i]) rp++;
	cout<<rp<<endl;
	fo(i,0,z) if(a[i]|a[z-i]) printf("%d ",i);puts("");
}

int main(){
	int T=read();
	while(T--) solve(); 
	return 0;
}
/*
-------------------------------------------------
*/
```


---

