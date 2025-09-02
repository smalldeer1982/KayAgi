# Gergovia的酒交易 Wine trading in Gergovia

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=22&page=show_problem&problem=1995

[PDF](https://uva.onlinejudge.org/external/110/p11054.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11054/ced1606866ddabe301a52d0310f9433bc4587f7e.png)

## 样例 #1

### 输入

```
5
5 -4 1 -3 1
6
-1000 -1000 -1000 1000 1000 1000
0```

### 输出

```
9
9000```

# 题解

## 作者：billzd (赞：6)

这题不是很难，关键是要知道如何得到最优解。

$ans=\sum^{n}_{i=1}\left|{\sum^{i}_{j=1}a_j}\right|$

我们来想一想为什么是这样。首先每个村庄不是卖酒，就是买酒。

如果是从 $a_i$ 卖 $n$ 瓶酒到 $a_{i-1}$ ,就会等价于 $a_{i-1}$ 卖 $-n$ 瓶酒到 $a_i$ ，劳动力都为 $\left|n\right|$ 。

这样我们就可以得知一个特性：**无论如何，不管 $a_i$ 和 $a_{i-1}$ 有多少存货（哪怕相加为负），都将 $a_{i-1}$ 的货运到 $a_i$。这样得到的就是最优解。**

我们先来看个简单的例子：

```
6
1 1 -4 5 1 -4
```


1. 首先，输入 $a_1$ ，有 1 瓶酒， $ans=1$ 。
1. 输入 $a_2$ ，加上 $a_1$，$ans=1+\left|1+1\right|=3$ 。
1. 输入 $a_3$ ，加上 $a_2$，$ans=3+\left|2-4\right|=6$。
1. 输入 $a_4$ ，加上 $a_3$，$ans=6+\left|-2+5\right|=9$。
1. 输入 $a_5$ ，加上 $a_4$，$ans=9+\left|3+1\right|=12$。
1. 输入 $a_6$ ，加上 $a_5$，$ans=12+\left|4-4\right|=12$。

由此可见 $ans=12$ 为最优解。
___
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO{
	const int SIZE=1<<21;
	static char ibuf[SIZE],obuf[SIZE],*iS,*iT,*oS=obuf,*oT=oS+SIZE-1;
    int qr;
    char qu[55],c;
    bool f;
	#define getchar() (IO::iS==IO::iT?(IO::iT=(IO::iS=IO::ibuf)+fread(IO::ibuf,1,IO::SIZE,stdin),(IO::iS==IO::iT?EOF:*IO::iS++)):*IO::iS++)
	#define putchar(x) *IO::oS++=x,IO::oS==IO::oT?flush():0
	#define flush() fwrite(IO::obuf,1,IO::oS-IO::obuf,stdout),IO::oS=IO::obuf
	#define puts(x) IO::Puts(x)
	template<typename T>
    inline void read(T&x){
    	for(f=1,c=getchar();c<48||c>57;c=getchar())f^=c=='-';
    	for(x=0;c<=57&&c>=48;c=getchar()) x=(x<<1)+(x<<3)+(c&15);
    	x=f?x:-x;
    }
    template<typename T>
    inline void write(T x){
        if(!x) putchar(48); if(x<0) putchar('-'),x=-x;
        while(x) qu[++qr]=x%10^48,x/=10;
        while(qr) putchar(qu[qr--]);
    }
    template<typename T>
    inline void writeln(T x){
		   write(x),putchar('\n');
	}
    inline void Puts(const char*s){
    	for(int i=0;s[i];i++)
			putchar(s[i]);
		putchar('\n');
	}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using IO::read;
using IO::write;
using IO::writeln;
int main(){
	int n;
	read(n);
	while(n){
		int ans=0,now,x;
		read(now);
		for(int i=1;i<n;i++){
			ans+=abs(now);
			read(x);
			now+=x;
		}
		writeln(ans);
		read(n);
	}
	return 0;
}
```
感谢观看！

---

## 作者：LuffyLuo (赞：4)

### 翻译
本文还是需要给个翻译的：

正如你从漫画《阿斯特里克斯和酋长的盾牌》中所知道的那样，格尔戈维亚由一条街道组成，城市里的每个居民都是葡萄酒推销员。你想知道这种经济是如何运作的吗？很简单：每个人都从城市的其他居民那里购买葡萄酒。每天，每个居民都决定要买或卖多少葡萄酒。有趣的是，需求和供给总是一样的，所以每个居民都能得到他想要的。然而，有一个问题：把葡萄酒从一个房子运到另一个房子会导致工作。由于所有的葡萄酒都同样好，Gergovia 的居民不在乎与谁做生意，他们只对销售或购买特定数量的葡萄酒感兴趣。他们足够聪明，能够找到一种交易方式，从而将运输所需的总工作量降至最低。在这个问题中，您需要在 Gergovia 的一天内重建交易。为简单起见，我们假设房屋沿直线建造，相邻房屋之间的距离相等。将一瓶葡萄酒从一所房子运送到相邻的房子需要一个工作单元。

输入由几个测试用例组成。每个测试用例都以居民数量 $n$ 开始 ($2 \le N \le 100000$)。下一行包含 $n$ 个整数 $a_i$(−1000 $\le$ $a_i$ $\le$ 1000)。如果 $a_i\le0$，它意味着居住在第 $i$ 栋房子的居民想要购买 $a_i$ 瓶葡萄酒，否则如果 $a_i\ge0$ 想卖掉 $a_i$ 艾瓶酒。您可以假设数字 $a_i$ 的总和为 0。最后一个测试用例后面是一行，其中包含 0。

对于每个测试用例，打印所需的最小工作单元数量，以便每个居民都有自己的工作单元。

（本人认为百度翻译还是值得信任的）

### 思路
首先我觉得题目给的并不是挺好，我觉得 $a_i$ 为负数应该指他需要 $a_i$ 瓶葡萄酒。这样子我觉得我还好讲一些。

接下来我们以样例一为例：

对于第一个人来说他需要买 5 瓶酒，但是他又只能把这些卖给第二个人，所以我们就可以想到我们不需要考虑中间的小交换，比如你给右边的邻居 1 瓶酒，然后右边的邻居再帮你把这瓶酒送到右右边的那个人。

可能大家还是没听懂，简单的来说就是：

第一个人直接给第二个人一巴掌把自己需要的 5 瓶酒给拿了回来（你懂的）。然后第二个就需要 1 瓶酒了，怎么办？于是他就有找到第三个人给他一个巴掌，弥补自己的需要，你看像这样传递下去，根本就不需要什么特殊处理，对吧！（~~多好的一条直线上的邻居呀！~~）

不过即使你的嘴角微微上扬起来，我们也还是要想一下——这个难道真的就可以了吗？会不会有什么东西把他给推翻，于是我们进入下一步，证明这个方法的正确性：

我们以前三个人举例，既然这个第一个人需要 5 瓶酒，那么我们先让第二个人把他的 4 瓶酒给他，那么他就只需要 1 瓶了，于是我们再次从第三个人那里拿到一瓶先给第二个人再给第一个人，这样三个人都满足了。

那么按照上述过程我们需要多少工作单位呢？答案是 6。

但是如果我们用上面的方法，我直接让第一个人给第二个人一个耳光，从他那拿去 5 瓶酒，这样第二个人反而还需要 1 瓶酒了。于是第二个人又找上第三个人，给他一巴掌，拿到他的那一瓶酒。

这样的过程一下来就都是前两个人都满足了，而且答案都是 6。于是这就帮我们证实了这个方法的正确性。所以我们想在不需要想太多，反正给一巴掌就行了。

但是我们难道一巴掌下去就可以了吗，对于最后一个还有什么措施呢？这是本题思路一个很大的问题。我们假设最后一个人是 7，即需要卖出 7 瓶酒，那么根据题意我们可以得出我们要使最后一个人满足，那么他只能把 7 瓶酒全部买到倒数第二个人那里去，那可不可以呢？

答案是显然的，当然可以啦，题目并不是说要最后每一个人都要满足要求，即都等于 0，只是需要每个人在这个过程可以得到满足就行了，所以我们根本就只需要将最后一个人的巴掌再还给倒数第二个人，就可以了。（~~这可真是一对相亲相爱的好邻居~~）。

### 代码
代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long wine[100010];
int main(){
	while(1){
		int n;
		scanf("%d",&n);
		if(!n) break;
		for(int i=1;i<=n;i++) scanf("%lld",&wine[i]),wine[i]=0-wine[i];//其实可以不要。
		long long answer=0;
		for(int i=2;i<=n;i++){
			if(wine[i-1]>-1) answer+=wine[i-1];
			else answer-=wine[i-1];
			wine[i]+=wine[i-1];
		}
		answer+=abs(wine[n]);
		printf("%lld\n",answer);
	}
	return 0;
}
```

### 注意事项
恐怕每（没）人会注意到要开 long long 吧！

//不用说谢谢，不因客套，只因能见您的笑容，以及您电脑上的 AC，您已经回报。

//祝大家信息学越来越棒哦！


---

## 作者：cryozwq (赞：2)

各位大佬都讲得很好了，但是我的代码和思路不是很一样，而且有个**小细节**大家都没有说，那就是**开 long long**。

### 题目分析
首先，我们不妨这样看：所有村庄都把酒往后面送，用一个变量储存运到目前的村庄的酒，当这个值是负数代表还剩了这么多酒，是正数代表还需要这么多酒，然后每次去减当前输入的值，再把这个值**的绝对值**累加就是答案。

### 参考代码
```cpp
#include<iostream>
#include<math.h>
using namespace std;
int n;
int main()
{
	while(1){
	long long tot=0,i,zz,xx,yy=0; 
	cin>>n;
	if(n==0)
	return 0;
	for(i=1;i<=n;i++)
	{
		cin>>zz;
		xx=yy+zz;
		yy=xx;
		tot+=abs(xx);
	}
	cout<<tot<<endl;
	}
	return 0;
}
```

---

## 作者：JCZhang (赞：2)

# 扫描法
从最左边的村庄考虑，如果$a_1 > 0$，那么一定有就从村庄2运来，这样就把问题简化到村庄$[2,n]$

-----

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

int main()
{
	int n;
	while (scanf("%d", &n) == 1 && n)
	{
		long long ans = 0, now = 0;
		for (int i = 0; i < n; ++i)
		{
			int x;
			scanf("%d", &x);
			ans += std::abs(now);
			now += x;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：Squirrel_GZQ (赞：1)

我们来分析一下题目。

相邻村庄之间的距离相等，将一瓶葡萄酒从一个村庄运送到邻近的村庄需要一个单位的工作量，也就是说，将 $x$ 瓶酒运到距离此村庄 $y$ 个单位长度的另一个村庄需要 $x \times y$ 个劳动力。为了确保劳动力最小，每个村庄应该只和相邻两个村庄之间交易，这样就可以确保进行交易的两个村庄距离为 $1$。我们可以开一个变量 $b$，每次输入 $a_i$ 不论正负都加到 $b$ 里，再用一个变量 $sum$ 用于统计所有 $b$ 的绝对值之和，这样就实现了对劳动力的计算与更新。

注意：由于此题数据较大，我们需要将数据范围设为 `long long`。

完整代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll M =1e5+10;
int n;
ll a[M];
int main(){
    while(1){
    	ll sum=0,i,b=0;
    	cin>>n;
    	if(n==0) return 0;//唯一可能出现的特殊情况 
    	for(i=1;i<=n;i++) cin>>a[i];
    	for(i=1;i<=n;i++){
    		b+=a[i];
    		sum+=abs(b);//计算劳动力
		}
		cout<<sum<<endl;
	}
    return 0;
}
```

---

## 作者：FSHYLHX (赞：0)

# 题目大意
有 $n$ 个酒厂，每个酒厂要买酒或者卖酒，而搬运所需的劳动力为要搬运酒的数量乘上要搬运酒的距离，求最少需要的劳动力数量是多少。
# 思路分析
遍历每一个酒厂，我将第 $k$ 个酒厂要买入或者卖出的酒全部移到第 $k + 1$ 个酒厂，这要就能保证酒的搬运距离为 $1$，每次更新目前总共要搬运的酒的数量和所需要的劳动力即可。
# 代码实现
```c
#include<bits/stdc++.h>
using namespace std;
#define int long long
int i,j,k,m,n,ans,sum,t,l; 
int a[100005];
signed main(){
	while(1){
		int ans = 0, k = 0;
		scanf("%lld",&n);
		if(n == 0) return 0;
		for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
		for(int i=1; i<=n; i++){
			ans += abs(k);
			k += a[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```


---

## 作者：small_john (赞：0)

## 分析
扫描法。

如果村庄 $i$ 需要买酒，则一定有村庄 $i+1$ 向他运酒。这些酒可能是自己生产的，也可能是更右边的村庄运给村庄 $i+1$ 的。所以此时，村庄 $i+1$ 就需要 $a_i+a_{i+1}$ 瓶酒。如果村庄 $i$ 卖酒给村庄 $i+1$，那么村庄 $i+1$ 同样需要 $a_i+a_{i+1}$ 瓶酒。

所以，问题就转化为求对于每个 $i>1$，$\displaystyle |\sum_{k=1}^{i-1} a_k|$ 的和。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
int n,ans,a,last;
signed main()
{
	while(cin>>n,n)
	{
		ans = last = 0;
		for(int i = 1;i<=n;i++)
			cin>>a,ans+=abs(last),last+=a;
		cout<<ans<<'\n';
	}
	return 0;
}

```

---

## 作者：Bloodwonderland (赞：0)


# 解题思路：

定义一个初始为零的变量表示当前需求（正数为出售需求，负数为购买需求）。

随后，从第一个村庄开始，依次对每个村庄做如下操作：

1. 用当前需求量加上村庄需求量。
2. 用所求劳动力（初始为零）加上当前村庄需求量的绝对值（注意当前村庄需求量可能为负，因此需要加上绝对值。）
3. 移步下一个村庄。

如此循环至最后一个村庄，就是所求的答案。

另外，看到这道题的时候的第一想法就是利用数组模拟，只需要定义一个数组以存储所有村庄的需求，然后一步步模拟即可。

## AC 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100000]; //此数组表示所有村庄
int n; //此为题目所输入的村庄数量
long long pre=0,ans=0; //pre 是当前需求量， ans是总需求量（所求答案）
int main()
{
	while(cin>>n&&n!=0)//输入不为零的村庄数量
	{
		for (int i=1; i<=n; i++) cin>>a[i];//输入每个村庄的需求量
		for (int i=1; i<=n; i++)
		{
			pre+=a[i]; //当前需求量加上村庄需求量
			ans+=abs(pre); //总劳动力加上当前需求量的绝对值
		}
		cout<<ans<<"\n";
		pre=0; ans=0;//清零当前及总需求量，准备下次循环
	}
	return 0;
} 
```

注：每进行一次总循环后无需清零数组，因为后续重新读入读入数组的时候会将之前的数据覆盖掉，诸位可以自行琢磨一下。

如此，完美收工。

---

## 作者：CQ_Bab (赞：0)

# 题意

直线上有 $n$ 个等距离的酒厂，有的酒厂买酒有的酒厂卖酒，把 $k$ 个单位的酒运到相邻村庄去需要 $k$ 酒的需求的劳动力,问最少需要多少劳动力才能满足所有的村庄的要求。

# 思路

我们从一到零便利，将第 $i$ 个村庄的酒都运往第 $i+1$ 个酒厂，我们可以用两个变量来存到第 $i$ 个酒厂的总和与答案。

# AC代码

```cpp
#include<bits/stdc++.h>
#define int long long // 切记一定要开long long 
using namespace std;
int n,a[101000];
signed main(){
	while(cin>>n,n){
		int res=0,now=0; // 来存答案和到第i个酒厂的酒总和 
		for(int i=1;i<=n;i++) cin>>a[i]; // 输入 
		for(int i=1;i<=n;i++){
			res+=abs(now); // 将第i个酒厂得酒运往下一个酒厂的总价钱（切记一定要用abs因为a[i]中有负数） 
			now+=a[i]; // 存入这个酒厂运来的酒 
		}
		cout<<res<<endl; // 输出 
	}
	return false; // 完结散花 
}
```


---

## 作者：myyyIisq2R (赞：0)

[UVA11054](https://www.luogu.com.cn/problem/UVA11054)

## 分析
考虑最左边的村庄。如果需要买酒，即 $a_1>0$ ，则一定有劳动力从村庄 $2$ 往左运给村庄 $1$ ，而无论这些酒是从哪里来的（可能是村庄 $2$ 产的，也可能是更右边的村庄运到村庄 $2$ 的）。这样，问题就等价于只有村庄 $2$ $\sim$ $n$ ，且第 $2$ 个村庄的需求为 $a_1+a_2$ 的情形。

## 参考程序
```cpp
#include <bits/stdc++.h>
#define qwq return 0;
using namespace std;
int main()
{
	int n;
	long long ans{},a{},last{};
	while(cin>>n&&n){ 
		ans&=0;a&=0;last&=0;
		for(int i{1};i<=n;i++){cin>>a;ans+=abs(last);last+=a;}
		cout<<ans<<"\n";
	}
	qwq
}
```

---

