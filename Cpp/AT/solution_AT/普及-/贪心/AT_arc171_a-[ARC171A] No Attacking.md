# [ARC171A] No Attacking

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc171/tasks/arc171_a

縦 $ N $ マス、横 $ N $ マスのチェス盤があります。チェス盤の上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と呼びます。  
 これから駒を盤に並べます。駒は $ 2 $ 種類あり、それぞれ **ルーク**, **ポーン** と呼びます。  
 駒の並び方が次の条件を満たすとき **良い配置** と呼びます。

- $ 1 $ つのマスにつき $ 0 $ 個または $ 1 $ 個の駒が置かれている。
- $ (i,\ j) $ にルークがあるとき、$ k\ \neq\ j $ であるすべての $ k $ $ (1\ \leq\ k\ \leq\ N) $ に対して $ (i,\ k) $ に駒が存在しない。
- $ (i,\ j) $ にルークがあるとき、$ k\ \neq\ i $ であるすべての $ k $ $ (1\ \leq\ k\ \leq\ N) $ に対して $ (k,\ j) $ に駒が存在しない。
- $ (i,\ j) $ にポーンがあり、かつ $ i\ \geq\ 2 $ であるとき、$ (i-1,\ j) $ に駒が存在しない。
 
$ A $ 個のルークと $ B $ 個のポーンを良い配置になるように全て盤に並べることは可能ですか？

$ T $ 個のテストケースが与えられるので、それぞれについて答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 10^5 $
- $ 1\ \leq\ N\ \leq\ 10^4 $
- $ 0\ \leq\ A,\ B $
- $ 1\ \leq\ A\ +\ B\ \leq\ N^2 $
- 入力される値は全て整数
 
### Sample Explanation 1

$ 1 $ 番目のテストケースでは、例えばルークを $ (1,\ 1) $ と $ (2,\ 4) $ に、ポーンを $ (3,\ 3) $ と $ (4,\ 2) $ と $ (5,\ 3) $ に配置することで全ての駒を良い配置になるように並べることが可能です。 $ 2 $ 番目のテストケースでは、全ての駒を良い配置になるように並べることは不可能です。

## 样例 #1

### 输入

```
8
5 2 3
6 5 8
3 2 2
11 67 40
26 22 16
95 91 31
80 46 56
998 2 44353```

### 输出

```
Yes
No
No
No
Yes
No
Yes
Yes```

# 题解

## 作者：maomao233 (赞：7)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc171_a)  
[AT 传送门](https://atcoder.jp/contests/arc171/tasks/arc171_a)

在下文中，车 表示题面中的 ルーク，兵 表示题面中的 ポーン。

---

读题我们得知，每个车必须独自占据一行一列，也就是说在棋盘中车最多只能放 $N$ 个。所以 $A>N$ 的情况就可以特判掉了。

然后我们看向样例的第五组：$N=26$，$A=22$，$B=16$。  
我们使用 Excel 画图以理解：  
（在下文图中，我们用白色表示空格，黄色表示兵，绿色表示车，红色表示不能下棋的位置。）

![](https://cdn.luogu.com.cn/upload/image_hosting/rtjuo57i.png?x-oss-process=image/resize,m_lfit,h_10000,w_10000)

首先我们考虑没有车的时候。显然此时将兵放在所有奇数行是最优的。  
如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/37haabdl.png?x-oss-process=image/resize,m_lfit,h_10000,w_10000)

然后我们开始放车。显然车放在哪些列是不重要的，而尽量放在偶数行是最优的。  
如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5430x276.png?x-oss-process=image/resize,m_lfit,h_10000,w_10000)

显然车只能放 $\dfrac{N}{2}=\dfrac{26}{2}=13$ 个。于是我们将剩余的 $22-13=9$ 个车放在奇数行。  
如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/51of79dg.png?x-oss-process=image/resize,m_lfit,h_10000,w_10000)

车放完了，我们将不能下棋的位置涂上红色。  
如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/7ejxx15d.png?x-oss-process=image/resize,m_lfit,h_10000,w_10000)

显然此时能放 $4\times4=16$ 个兵，刚好满足要求。~~而不是像我一样傻傻地把对角线放满车再计算。~~

所以我们可以得出每列放兵的最大数量：

- 当所有车能放在所有偶数行内，即 $A\le\dfrac{N}{2}$ 时，每列放兵的最大数量为 $\bigg\lfloor\normalsize\dfrac{N+1}{2}\bigg\rfloor$ 个。
- 当所有车不能放在所有偶数行内，即 $A>\dfrac{N}{2}$ 时，每列放兵的最大数量为 $(N-A)$ 个。

显然能放兵的列数最多为 $(N-A)$ 列。于是我们得出棋盘放兵的最大数量为：

$$\min\{\bigg\lfloor\normalsize\dfrac{N+1}{2}\bigg\rfloor,N-A\}\cdot(N-A)$$

判断其是否 $\ge B$ 即可。于是有代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
#define lb(x) x&-x
#define itn int
inline string its(int x){stringstream ss;string s;ss<<x;ss>>s;return s;}
inline int sti(string s){stringstream ss;int x;ss<<s;ss>>x;return x;}
inline string jia(string a1,string b1){int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=max(lena,lenb),t=0;for(int i=0;i<lenc;i++){c[i]=a[i]+b[i]+t;if(c[i]>=10){t=1,c[i]%=10;}else{t=0;}}if(t==1){lenc++;c[lenc-1]=1;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline string jian(string a1,string b1){if(a1.size()<b1.size()||a1.size()==b1.size()&&a1<b1){pc('-'),swap(a1,b1);}int a[10010],b[10010],c[10010];int lena=a1.size(),lenb=b1.size();for(int i=0;i<lena;i++){a[i]=a1[lena-1-i]-'0';}for(int i=0;i<lenb;i++){b[i]=b1[lenb-1-i]-'0';}int lenc=lena;for(int i=0;i<lenc;i++){if(a[i]<b[i]){a[i+1]--,a[i]+=10;}c[i]=a[i]-b[i];}while(lenc>=1&&c[lenc-1]==0){lenc--;}string s;for(int i=lenc-1;i>=0;i--){s+=c[i]+'0';}return s;}
inline int qpow(int a,int b,int p){int ans=1;while(b){if(b&1){ans=(ans*a)%p;}b>>=1;a=(a*a)%p;}return ans;}
inline int qp(int a,int b){int ans=1;while(b){if(b&1){ans*=a;}b>>=1;a*=a;}return ans;}
signed main()
{
	int t;
	rd(t);
	while(t--)
	{
		int n,a,b;
		rd(n,a,b),puts(a>n?"No":min((n+1)/2,n-a)*(n-a)>=b?"Yes":"No");
	}
	return 0;
}
```

---

## 作者：rui_er (赞：4)

先考虑没有车时怎么做，显然在所有奇数行放满兵是最优的。

每个车必须独自占据一行一列，放在哪些列是不重要的，但是要优先放在偶数行，这样可以尽量多地放兵。

按以上策略放完车之后判断卒是否放得下即可。

```cpp
cin >> n >> a >> b;
int k = n - max(n / 2, a);
if(n >= a && b <= (n - a) * k) cout << "Yes" << endl;
else cout << "No" << endl;
```

---

## 作者：Hadtsti (赞：3)

### 题意简述

在一个 $N\times N$ 的方格子棋盘上放置 A、B 两种棋子。A 棋子吃法形如国际象棋中的车，B 棋子只能吃掉向上 $1$ 格的棋子。问对于给定的 $N\times N$ 棋盘，能否摆下 $a$ 个 A 棋子和 $b$ 个 B 棋子满足它们之间互相无法吃到。数据为多测。

### 题目分析

首先每个 A 棋子都会占掉一整行和一整列，所以如果 $a>N$ 则无解。

否则，我们需要将 B 棋子放置在 A 棋子的攻击盲区内。注意到 A 棋子的攻击盲区实际上是一个被拆散的 $(N-a)\times (N-a)$ 方格，考虑怎样能使得 B 棋子尽可能地多放。

由于 B 棋子的吃法与列之间无关，我们把每一列拆出来考虑。称不被 A 棋子攻击到的格子为空格，则对于不被 A 棋子攻击到的每一列，都有着固定的 $N-a$ 个空格，而相邻行的一对空格势必会让其中一个格浪费，所以我们应该尽可能减少这种情况，即让空格之间不相邻。具体地，我们只需要让上下两行都没有空格的空格数量最多即可。如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/ql7rfsvf.png)

正确性证明考虑调整法。对于任意一种空格的分布方式，如果存在由 $x(x>1)$ 个空格构成的一段，我们考虑把它拆成 $x-1$ 的一段和一个单独空格，则浪费的空格数量不会增多，即调整后的方案不劣于原方案。

最后判断空格数量是否大于等于 $b$ 即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b;
int calc(int x,int y)
{
	return (x+1)/2*y;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d",&n,&a,&b);	
		if(a>n)
			printf("No\n");
		else if(a>=n/2)
			printf((n-a)*(n-a)>=b?"Yes\n":"No\n");
		else
			printf(a*a+calc(n-2*a,1)*a+calc(1,n-2*a)*a+calc(n-2*a,n-2*a)>=b?"Yes\n":"No\n");
	}
	return 0;
}
```

---

## 作者：mc_him (赞：2)

## 题目大意

在一个棋盘上放满指定个数的兵和车。已知兵只能向上走，而车可以向上下左右走任意格。问有没有方案能满足没有棋子一步就能吃掉其他棋子。
## 题目分析
很明显的一道贪心题目，我们先考虑只有兵的情况下，代表只要它的上方没有棋子就行了，那么最优解就是在奇数行上放满兵。

那么再考虑只有车的情况，那么只要在一个地方放上了车，那一行与那一列都不能放任何棋子。

那么把这两种棋子放在一起，车总共占了车的数量行与车的数量列，那么能放的兵的数量是总行数减车的数量的平方再除以二，因为兵只能放在奇数行。

所以，要想能满足条件，至少满足：

1. 车的数量不能大于行数。
1. 兵的数量不能大于行数减车的数量再乘上列数减车的数量再除以二。

## 正确代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b,t;
int main() {
	cin>>t;
	while(t--) scanf("%d%d%d",&n,&a,&b),n>=a&&b<=(n-a)*(n-max(n/2,a))?printf("Yes\n"):printf("No\n");
}
```

---

## 作者：pfrig729 (赞：2)

这是一道贪心题。

### 分析
首先考虑卒，因为其可以控制它上面的格子，所以为了节约空间，我们将卒放在 **奇数行** 上，而有车的行必定不能放卒，所以车优先放在 **偶数行** 上。

为了方便理解，我们来看一个例子。
![](https://s11.ax1x.com/2024/02/09/pF3QaIe.png)
在这个例子中，$n=7$，$a=4$，$b=9$。

可以看到，卒能放到的列数就是 $n-a$，在没有车的情况下，卒能放到的行数是 $\lceil n \div 2 \rceil$。

接着考虑车的情况，如果车的数量比 $\lfloor n \div 2 \rfloor$ 小，那么对卒没有影响。相反，卒的行数需要减去车减去 $\lfloor n \div 2 \rfloor$ 后剩余的数量。
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int t;
inline bool is_car_ok(int x,int y)//车可以吗
{
	return x>=y;
}
inline bool is_die_ok(int x,int y,int z)//卒可以吗
{
	int die_cross=x/2+x%2,die_line=x-y;
	y=max(y-x/2,0);
	die_cross-=y;
//	cout<<die_cross<<' '<<die_line<<endl;
	return die_cross*die_line>=z;
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int n,a,b;
		scanf("%d%d%d",&n,&a,&b);
		if(is_car_ok(n,a)&&is_die_ok(n,a,b))
		{
			puts("Yes");
			continue;
		}
		puts("No");
	}
	return 0;
}
```

---

## 作者：Xiphi (赞：2)

傻逼细节题。首先考虑放车必定会占用 $1$ 行加上 $1$ 列的空间，那么最后留给兵的一定是 $(n-x)\times(n-x)$ 个空间。考虑怎么放车最优，对于 $n\le x\times 2$  的情况，把车摆成对角线的形式必然不优，其中一种最优形式是在 $1,3,5,\dots$ 行放上车，在 $n=5,x=3$ 的情况下，最优摆放方式如下图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/plkc4jzi.png)

至于为什么这样是最优的，读者自证不难。

对于 $n > x\times 2$  的情况，考虑到车控制的区域除前 $2 \times x$ 行势必会空出 $(n-x)\times(n-2\times x)$ 个位置，而兵在其中最多放 $\lceil (n-x)\times(n-2\times x)÷2 \rceil$ 个兵（这里默认把车按在 $1,3,5,\dots$ 行的形式摆放）。

剩下的就是一些简单特判，也没啥好说的了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,T;
signed main(){
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>T;
	while(T--){
		int x,y;
		cin>>n>>x>>y;
		int sum=(n-x);
		if(sum==0){
			if(!y) cout<<"Yes\n";
			else cout<<"No\n";
		}
		else if(sum<0){
			cout<<"No"<<'\n';
		}else{
			if(x*2>=n)
				if(sum*sum>=y) cout<<"Yes\n";
				else cout<<"No\n";
			else
				if(sum*(x)+(sum*ceil(1.0*(n-x*2)/2.0))>=y) cout<<"Yes\n";
				else cout<<"No\n";
		}
	}
	return 0;
}




```

---

## 作者：Fiendish (赞：1)

看到题目，很容易想到要让卒可以攻击到的地方和车可以攻击到的地方尽量重合或在棋盘外。

于是就可以得到策略，将车优先放到偶数行，而卒放到剩下的行、列中，这样卒所能攻击到的地方就都是车可以攻击到的地方（最下面一行的卒可以攻击到的地方在棋盘外），除非车的个数不足 $\dfrac{n}{2}$。车放在哪几列无所谓，只要一个车所在的列上没有其它棋子即可。

代码：

```cpp
#include<iostream>
using namespace std;
int t,n,a,b;
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n>>a>>b;
        int x=n-max(n/2,a);//放卒的行数
        if(n>=a&&b<=(n-a)/*放卒的列数*/*x) cout<<"Yes\n";
        else cout<<"No\n";
	}
	return 0;
}
```


---

## 作者：Otue (赞：1)

考虑车可以控制住一行一列，那么最多放 $n$ 个车。

如果一个车都不放，那么卒占满奇数行最优。所以说车尽量先放偶数行，给卒留出足够空间。

* 若 $A \leq \lfloor \dfrac{n}{2} \rfloor$，即车的数量没有偶数行多，车可以在偶数行自由摆放。此时卒的可用空间为全部奇数行，为 $(n-a)\times \lceil \dfrac{n}{2} \rceil$。

* 若 $A > \lfloor \dfrac{n}{2} \rfloor$，即车的数量比偶数行多，车要摆放在奇数行。此时卒的可用空间为剩下行， $(n-a)\times (n-a) $。

最后比较卒的个数和卒的可用空间的大小关系即可。

```c++
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 3e5 + 5;

int T, n, a, b;

signed main() {
	cin >> T;
	while (T--) {
		cin >> n >> a >> b;
		if (a > n) puts("No");
		else {
			int c = 0;
			if (a <= n / 2) c = (n + 1) / 2;
			else c = n - a;
			if (c * (n - a) >= b) puts("Yes");
			else puts("No");
		}
	}
}
```

---

## 作者：__Floze3__ (赞：1)

## 思路简介

显然，车对于棋子摆放方式的影响比兵要大得多，因此我们优先考虑怎么安放车。

首先，显然的，每个车一定要占掉一行和一列的棋盘。因此，如果 $n < a$，那么一定是无法摆放的，直接输出 No 即可。

继续考虑 $n \ge a$ 的情况。我们首先考虑 $n$ 为奇数的情况。既然每一个车都要占掉一行和一列的棋盘，并且兵只能影响它上一行的棋盘，那么每一个能放兵的行，都一定只能放 $n - a$ 个兵；同时，由于有兵的影响，两个兵不能放在一列上，只能隔一行放一个，我们可以想到：用车将棋盘分为一行一行的是最优的，这样兵之间不会互相干扰。

可能讲的有些抽象，其实就像这张图一样：![](https://cdn.luogu.com.cn/upload/image_hosting/wia4tt54.png)

要把所有的行分为一格高，需要 $\lfloor \dfrac{n}{2} \rfloor$ 个车。显然，如果 $\lfloor \dfrac{n}{2} \rfloor \ge a$，一定会有空出来的有奇数行的矩形空着。但是，这样的矩形与被分割成一行一行的矩形，能容纳的兵的数量是相同的。因为，在一个有奇数行的矩形中，一定是从第一行开始，隔一行放一行兵最优。如图：![](https://cdn.luogu.com.cn/upload/image_hosting/v1nj6gku.png)

因此，在这种情况下，能放置兵的行数即为 $\lfloor \dfrac{n}{2} \rfloor + 1$，能放置兵的最大数量即为 $(n - a) \times (\lfloor \dfrac{n}{2} \rfloor + 1)$。

在 $\lfloor \dfrac{n}{2} \rfloor \le a$ 的情况下则更为简单，因为在将棋盘分割成一行一行的矩形后还有车剩余，又要占掉几行，因此能够容纳兵的行数即为 $n - a$，能够容纳兵的最大数量即为 $(n - a)^2$。

那么，如果 $n$ 为偶数呢？我们只需要在左上角放置一个车，就可以把棋盘转化为 $n$ 为奇数的情况。如果没有车，只需要额外特判此时能够容纳的兵的数量最大值即可。

## 代码

```cpp
#include <bits/stdc++.h>
typedef long long i64;

i64 T, n, a, b;

inline void solve() {
    std::cin >> n >> a >> b;
    if (n % 2 == 0){
        if (a) --n, --a; // 用一个车使偶数列变成奇数列
        else { // 没有车时的特判
            if (n * n / 2 >= b) std::cout << "Yes\n";
            else std::cout << "No\n";
            return ;
        }
    }
    if (n < a) { // 不可能容纳
        std::cout << "No\n";
        return ;
    }
    if ((n >> 1) > a) {
        i64 l = n - a, w = (n >> 1) + 1;
        if (l * w >= b) std::cout << "Yes\n";
        else std::cout << "No\n";
    }
    else {
        i64 l = n - a, w = n - a;
        if (l * w >= b) std::cout << "Yes\n";
        else std::cout << "No\n";
    }
    return ;
}

int main() {
    std::cin >> T;
    while (T--) solve();
    return 0;
}
```

---

## 作者：KyleShen1213 (赞：0)

## 解题思路
一道简单的贪心题。

很明显，如果车的个数大于 $n$，必定无法满足要求。

卒的攻击范围只有前面一格，故考虑优先摆车，车一行空一行摆，若摆不下，再在空的行上摆，卒就摆在车剩下的能摆的地方。但如果车的数量小于 $n$ 的一半，卒也只能在右半边摆，所以需要特判。

## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a,b,x;
int main()
{
	cin>>t;
	for(int i=1;i<=t;i++)//t组数据 
	{
		cin>>n>>a>>b;
		if(n<a){cout<<"No"<<endl;continue;}//n<a，无法摆，输出No并continue 
		x=n-max(a,n/2);//摆卒的剩余行数 
        if(b<=(n-a)*x)  cout<<"Yes"<<endl;//能摆就输出Yes
        else  cout<<"No"<<endl;//不能摆就输出No
	}
	return 0;
}
```

---

## 作者：xzz_0611 (赞：0)

[洛谷题目传送门](/problem/AT_arc171_a)  
[AtCoder 题目传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/arc171_a)
## 分析
显然，在一个 $N\times N$ 的网格里，如果要放超过 $N$ 个车，那么是肯定无法完成的。

很明显，车放都在偶数行是最优的，如果不够了就放在奇数行，然后再把所有的兵都放在奇数行。

还可以知道，对于一个 $N\times N$ 的方格，一共会有 $\lfloor\frac{N}{2}\rfloor$ 个偶数行，$\lceil\frac{N}{2}\rceil$ 个奇数行。

若：
- $A\le\lfloor\frac{N}{2}\rfloor$：这时刚好所有的奇数行都不会被车吃到，但有 $A$ 列会被车吃到，所以这时有 $\lceil\frac{N}{2}\rceil\times (N-A)$ 个位置可以放兵。
- $A>\lfloor\frac{N}{2}\rfloor$：由于偶数行只能放 $\lfloor\frac{N}{2}\rfloor$ 个车，所以这时会有 $A-\lfloor\frac{N}{2}\rfloor$ 个奇数行能被车吃到，故只有 $\lceil\frac{N}{2}\rceil-A+\lfloor\frac{N}{2}\rfloor$ 行能够放兵，而由于有 $A$ 列会被车吃到，所以只有 $(\lceil\frac{N}{2}\rceil-A+\lfloor\frac{N}{2}\rfloor)\times(N-A)$ 个位置可以放兵。

然后再判断能不能放下 $B$ 个车即可。
## Code
```cpp
#include<iostream>
#define ceil(n) (n%2?n/2+1:n/2)
using namespace std;
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	int t,n,a,b,sum;
	cin>>t;
	while(t--) {
		cin>>n>>a>>b;
		if(a>n) {
			cout<<"No\n";
			continue;
		}
		sum=(a<=n/2?ceil(n)*(n-a):(ceil(n)-a+n/2)*(n-a));//计算能放的兵的数量最多是多少
		if(b<=sum) cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
```

---

## 作者：Eterna (赞：0)

贪心。

奇数行放兵比偶数行放兵放的多，所以优先在偶数行放车。

然后直接对比兵的数量和剩余可放置格子的数量即可。

轻松实现 $O(1)$ 查询。

```cpp
#include<bits/stdc++.h>
using namespace std;
main()
{
	int t,n,a,b;cin>>t;
	while(t--&&scanf("%d%d%d",&n,&a,&b)!=EOF)
		if(n<a)puts("No");
		else if(min((n-a),(n+1)/2)*(n-a)<b)puts("No");
		else puts("Yes");
}
```

---

## 作者：Magus (赞：0)

贪心。

## 题意

给定一个 $n \times n$ 的棋盘，棋盘上有两种棋子车和卒。

车可以移动到与它同一行或者同一列的任意位置，卒只能向前移动一格。
 
判断是否能在此棋盘上放置 $a$ 个车和 $b$ 个卒使得他们互相吃不掉彼此。

## 思路

首先很难不发现，因为车独占一行一列，所以车最多只能放 $n$ 个。

其次我们考虑棋盘上没有车只有卒时的情况，因为卒只能向前走一格，我们需要避免它们一个吃掉另一个，所以将卒全部放在奇数行是最优的。

所以车要优先放偶数行来保证兵的数量放的最多。

## Code
```cpp
#include<bits/stdc++.h>
#define FastIO ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define int long long
#define I using
#define AK namespace
#define NOIP2024 std
I AK NOIP2024;
const int maxn=1e7+10,maxm=1e3+10,mod=998244353;
int t,n,m,x,y,arr[maxn],arr_II[maxn],arr_2d[maxm][maxm];
signed main()
{
	FastIO;
	cin>>t;
	while(t--)
	{
		cin>>n>>x>>y;
		m=n-max(n/2,x);
		if(n>=x and y<=(n-x)*m)
		{
			cout<<"Yes\n";
		}
		else
		{
			cout<<"No\n";
		}
	}
	return 0;
}
/*
「我梦见一片焦土...」
「一株破土而生的新蕊...」
「它迎着朝阳绽放...」
「向我低语呢喃...」
「飞萤扑火，
向死而生。 」
*/ 
```

---

## 作者：lym12 (赞：0)

简单的一匹。

简单推一下：车能放到偶数行就放到偶数行，卒放到剩下的地方去，这样卒能攻击到的地方就都是车可以攻击到的地方。但如果车的个数不足 $\frac{n}{2}$ 个，车放在哪几列就都无所谓了，只需一个车所在的列上没有其它棋子即可。

然后简单无比的题解。

code：
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int T; cin >> T;
    while (T --){
        int n, a, b;
        cin >> n >> a >> b;
        if (n >= a && b <= (n - a) * (n - max(n / 2, a))){
            cout << "Yes\n";
        }else{
            cout << "No\n";
        }
    }
}
```

---

## 作者：Genshin_ZFYX (赞：0)

在只有兵的情况下，只要保证每个兵的上方没有棋子就行，最优解即把所有兵都放在奇数行。

有车的行和列是不能放其他的棋子的，所以需要满足 $a\le n$。车要尽量地放在偶数行，这样才能给奇数行留下更多的空间，也就是说让兵放的最多。至于车放在那几列，似乎并没有什么影响。

我们可以得出每行放兵的最大数量时 $n-a$，每列放兵最大数量为 $n-\max\{a,\lfloor n\div 2\rfloor\}$。

AC 代码：
```
#include<bits/stdc++.h>
using namespace std;
//#define int long long
#define I return
#define love 0
#define FIRESTARS ;
signed main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;cin>>t;
    while(t--)
    {
    	int n,a,b;
    	cin>>n>>a>>b;
    	if(a<=n&&b<=(n-max(a,n/2))*(n-a))cout<<"Yes"<<'\n';
    	else cout<<"No"<<'\n';
	}
	I love FIRESTARS
}

```

---

## 作者：recollect_i (赞：0)

如果只考虑放置「卒」，我们可以每隔一排防止一个「卒」，这样我们一个可以放置 $n\lceil \frac n 2\rceil$ 个「卒」。

然后考虑放置「车」，我们优先在没有放置「卒」的一行放置，可以放置 $\lfloor \frac n 2\rfloor$ 个「车」，然后在放置「卒」的一行放置，可以放置 $\lceil \frac n 2\rceil$ 个「车」，且每放置一个「车」就有一列不能放「卒」。

---

## 作者：what_can_I_do (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_arc171_a)

我们发现两行连着的当中每一列只能有一行放兵，那么另一行就可以统一用来放车。

那么我们就采取两行放一辆车的方式来放。但是有可能车会放不下，那么就把剩下的车放到目前空着的行里。然后考虑奇数行放兵，偶数行放车，这样的话如果车不够可以补，并且在有奇数行的情况下最后一行会利用来放兵，可以将放兵的空间放大到最大。我们得到放兵的最大空间之后，再来调节车的数量，这样可以保证在车放得下的情况下放的兵最多。然后只要先判断车是否放得下，再按照策略把车放下之后判断兵是否放得下就行了。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main()
{
	cin>>t;
	while(t--)
	{
		int n,a,b;
		cin>>n>>a>>b;
		if(n-a<0){puts("No");continue;}
		int d=ceil(n*1.0/2);
		if((n-a)<d)
		{
			if((n-a)*(n-a)>=b) puts("Yes");
			else puts("No");
		}
		else
		{
			if(d*(n-a)>=b) puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
```

---

## 作者：WhileTrueRP (赞：0)

# AT_arc171_a

## 题意

在一个 $N\times N$ 的棋盘上放置 $A$ 个中国象棋中的车和 $B$ 的只能向上共计的卒（即未过河的卒），问：是否存在一种方案使得棋子之间互不攻击？

共 $T$ 次询问。

## 思路

考虑只有车，则最多可以放置 $N$ 个。

考虑只有卒，则最多 $\lfloor\frac{(N+1)}{2}\rfloor\times N$ 个。

若两个都有，当然是车尽量隔一行放一个啦！这样使得卒和车的共计范围互相重叠，最优。若车的数量过多，就只能在隔一行的空隙里放了。

所以我们可以得出卒最多的个数不超过 $\min(N-A,\lfloor\frac{N+1}{2}\rfloor\times N)$ 个。

## 参考代码

时间复杂度 $O(T)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,n,a,b;
	scanf("%d",&t);
	while(t --){
		scanf("%d%d%d",&n,&a,&b);
		if(n < a){
			puts("No");
		}else if(min((n-a),(n+1)/2) * (n-a) < b){
			puts("No");
		}else{
			puts("Yes");
		}
	}
}
```



---

## 作者：yyrwlj (赞：0)

只切了这道题，刚开始表现分直接 $1949$，实际分是三位数。

## 题意简述

有一个 $n \times n$ 的棋盘，要在上面放 $a$ 个车和 $b$ 个卒，车会攻击同行同列的其它棋子，卒会攻击同一列的下一行的棋子。

是否存在一种让它们互不攻击的方案。

## 思路

显然每行每列最多只能放一个车，那么如果 $a > n$ 就直接无解了。

否则放完 $a$ 个车后，还剩 $n-a$ 行。卒不会攻击同一行的棋子，所以每行都可以放满 $n-a$ 个卒。

考虑如何最大化能使用的行数，不能让两个行挨在一起，所以让车隔一行放一个。

当 $a < \lfloor \frac{n}{2} \rfloor$，光隔一行放一个还会有剩下的。出现这种情况就正常隔着放就行，除了车隔出来的 $a$ 行以外，最多还能放 $\lceil \frac{n-2a}{2} \rceil$ 行。

最后看还能放的格子数和卒的数量的大小关系即可。

## Code

```cpp
if (a > n || a == n && b)
    puts("No");
int col = n - a, row = col;
if (a < n / 2)
    row = a + ((n - a) * 2 + 1) / 2;
if (col * row < b)
    puts("No");
else
    puts("Yes");
```

---

## 作者：FreedomKing (赞：0)

简单思维题。

### 思路

由于是询问我们能不能在有限的空间内放下一定数量的车和兵，所以需要一个最优的放置方案。不难想到，肯定是要让不能放置的格子尽量重合，使他们占用的空间最少，才是最优的方案。

下方示意图图取自@[__QWWQ__](https://www.luogu.com.cn/user/535491)，其中红色代表车占用的格子，绿则代表兵可以摆放的格子。

![](https://s2.loli.net/2024/02/05/FypYCUrifb6ZSmx.png)

这样让车间隔摆放，其间插入兵便一定是最优方案。

有了最优方案还需要进行分类讨论：

- 若 $A\ge \lceil \frac{n}{2} \rceil$，即车的数量可以完全将右侧每行都隔开，直接算出剩余的格子数并与 $B$ 比较即可。

- 否则，就意味着车的数量不足以将右面每行都隔开，需要分开讨论上部被隔开的部分和下部未被隔开的部分，即 $A\times (N-A)+\lceil \frac{N-2\times A}{2} \rceil$，注意式子的第二项的分子中一定是减去 $2\times A$ 而不是只减去 $A$，因为第一项会摆满上方的 $2\times A$ 行格子。

剩下记得考虑一下无解的情况即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5,mN=2e3+5;
//const int mod=1e9+7;
namespace FreedomKing_qwq{};
using namespace FreedomKing_qwq;
namespace FreedomKing_qwq{
	inline int qread(){
#define qr qread()
		int x=0,c=getchar(),t=1;
		while(c<'0'||c>'9'){
			t^=(c=='-');
			c=getchar();
		}
		while(c>='0'&&c<='9'){
			x=(x<<3)+(x<<1)+c-'0';
			c=getchar();
		}
		return (t?x:-x);
	}
	inline void qwrite(int x){
#define qw(_) qwrite(_)
#define qws(_) qw(_),putchar(' ')
#define qwe(_) qw(_),putchar('\n')
		if(x<0) x=-x,putchar('-');
		if(x>9) qwrite(x/10);
		putchar(x%10+'0');
		return;
	}
	inline int qpow(int x,int p,int mod){
		x=(p?x:1);
		mod=(mod?mod:LONG_LONG_MAX);
		int t=1;
		while(p>1){
			if(p&1) t=(t*x)%mod;
			x=(x*x)%mod;
			p>>=1;
		}
		return (x*t)%mod;
	}
	inline int gcd(int x,int y){return (!(x%y)?y:gcd(y,x%y));}
	inline int lcm(int x,int y){x/=gcd(x,y);return (x*y);}
	inline int max(int x,int y){return (x>y?x:y);}
	inline int min(int x,int y){return (x<y?x:y);}
	inline int abs(int x){return (x>0?x:-x);}
	inline int popcount(int x) {
		x=(x&0x5555555555555555)+((x>>1)&0x5555555555555555);
		x=(x&0x3333333333333333)+((x>>2)&0x3333333333333333);
		x=(x&0x0f0f0f0f0f0f0f0f)+((x>>4)&0x0f0f0f0f0f0f0f0f);
		x=(x&0x00ff00ff00ff00ff)+((x>>8)&0x00ff00ff00ff00ff);
		x=(x&0x0000ffff0000ffff)+((x>>16)&0x0000ffff0000ffff);
		x=(x&0x00000000ffffffff)+((x>>32)&0x00000000ffffffff);
		return x;
	}
}
signed main(){
	int T=qr;
	while(T--){
		int n=qr,a=qr,b=qr;
		if(a>=((n+1)>>1)){
			n-=a;
			if(n*n>=b&&n>=0) puts("Yes");
			else puts("No");
		}
		else{
			int cnt=a*(n-a);
			cnt+=((n-2*a+1)>>1)*(n-a);
			if(cnt>=b) puts("Yes");
			else puts("No");
		}
	}
	return 0;
}
```

---

## 作者：Link_Cut_Y (赞：0)

## 简要题意：

给你一个 $n \times n$ 的正方形棋盘。有两种棋子：「车」和「卒」。他们的移动规则如下：

 - 「车」可以移动到与它同一行或者同一列的任意位置。
 
 - 「卒」只能向前移动，也就是说，坐标为 $(x, y)$ 的卒，只能移动到 $(x - 1, y)$（如果这个位置没有超出棋盘的话）。
 
给你 $t$ 组询问，每个询问给你三个正整数 $n, a, b$。你需要回答，是否能在 $n \times n$ 的棋盘上放置 $a$ 个「车」和 $b$ 个「卒」，使他们互相不能吃掉彼此。如果能则回答 `Yes`，否则回答 `No`。

## 分析

我们先来分析「卒」。一个 $n \times n$ 的棋盘上，最多放置 $\left \lceil \dfrac{n}{2} \right \rceil \times n$ 个「卒」。如果我们用 `*` 表示「卒」，用 `.` 表示空，那么他们应该这样排布：

```
*****
.....
*****
.....
*****
```

然后我们开始往上放「车」，让「车」尽可能少顶掉「卒」。

首先，将「车」放在空的地方是最好的。我们可以用如下策略放「车」（这里「车」将用 `+` 代替）：

```
*.*.*
.+...
*.*.*
...+.
*.*.*
```

也就是在主对角线上的空格处放「车」。这样最多可以放 $\left \lfloor \dfrac{n}{2} \right \rfloor$ 个车，每个车都会顶掉 $\left \lceil \dfrac{n}{2} \right \rceil$ 个「卒」。

那么如果「车」的数量比 $\left \lfloor \dfrac{n}{2} \right \rfloor$ 多呢？

那就不得不占掉「卒」的位置了。将「车」沿着主对角线，依次顶掉「卒」，直到「车」填到 $a$ 个。设 $B = \left \lceil \dfrac{n}{2} \right \rceil \times 2 - 1$，则第一个「车」顶掉 $B$ 个「卒」，第二个「车」顶掉 $B - 2$ 个「卒」，以此类推，构成一个公差为 $2$ 的等差数列。

将占掉的卒全部扣掉，表示棋盘上最多能放的卒的数量。与 $b$ 进行比较即可。

```cpp
int T, n, a, b;
int calc(int n) { return (n + 1) / 2 * n; }
signed main() {
	scanf("%lld", &T);
	while (T -- ) {
		scanf("%lld%lld%lld", &n, &a, &b);
		if (a > n) { puts("No"); continue; }
		if (b > calc(n)) { puts("No"); continue; }
		int mx = calc(n); if (a <= n / 2) {
			puts(mx - (n + 1) / 2 * a >= b ? "Yes" : "No"); continue;
		} mx -= (n + 1) / 2 * (n / 2); a -= (n / 2);
		int B = ((n + 1) / 2) * 2 - 1; mx -= (2 * B - 2 * a + 2) * a / 2;
		puts(mx >= b ? "Yes" : "No");
	} return 0;
}
```

---

