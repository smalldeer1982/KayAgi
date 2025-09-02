# Rock-Paper-Scissors

## 题目描述

Nikephoros and Polycarpus play rock-paper-scissors. The loser gets pinched (not too severely!).

Let us remind you the rules of this game. Rock-paper-scissors is played by two players. In each round the players choose one of three items independently from each other. They show the items with their hands: a rock, scissors or paper. The winner is determined by the following rules: the rock beats the scissors, the scissors beat the paper and the paper beats the rock. If the players choose the same item, the round finishes with a draw.

Nikephoros and Polycarpus have played $ n $ rounds. In each round the winner gave the loser a friendly pinch and the loser ended up with a fresh and new red spot on his body. If the round finished in a draw, the players did nothing and just played on.

Nikephoros turned out to have worked out the following strategy: before the game began, he chose some sequence of items $ A=(a_{1},a_{2},...,a_{m}) $ , and then he cyclically showed the items from this sequence, starting from the first one. Cyclically means that Nikephoros shows signs in the following order: $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{m} $ , $ a_{1} $ , $ a_{2} $ , $ ... $ , $ a_{m} $ , $ a_{1} $ , $ ... $ and so on. Polycarpus had a similar strategy, only he had his own sequence of items $ B=(b_{1},b_{2},...,b_{k}) $ .

Determine the number of red spots on both players after they've played $ n $ rounds of the game. You can consider that when the game began, the boys had no red spots on them.

## 说明/提示

In the first sample the game went like this:

- R - R. Draw.
- P - S. Nikephoros loses.
- S - P. Polycarpus loses.
- R - P. Nikephoros loses.
- P - R. Polycarpus loses.
- S - S. Draw.
- R - P. Nikephoros loses.

Thus, in total Nikephoros has $ 3 $ losses (and $ 3 $ red spots), and Polycarpus only has $ 2 $ .

## 样例 #1

### 输入

```
7
RPS
RSPP
```

### 输出

```
3 2```

## 样例 #2

### 输入

```
5
RRRRRRRR
R
```

### 输出

```
0 0```

# 题解

## 作者：chlchl (赞：1)

看到这题挺有意思的，就来写篇题解练练手。
## 题目大意
两个（机器）人玩石头剪刀布，每个人都有一个出牌的周期。现在有 $n$ 局，问这两个人分别输了几场。

## 做法和思路
本题主要考察**简单数论**和**模拟**，还有一点点**思维**。这题其实就是求两个周期的匹配问题，只是匹配规则改成了石头剪刀布的规则。

首先考虑直接枚举，但是发现 $n\leq 2\times 10^9$，$O(n)$ 直接优美 TLE。所以，需要找到一种更方便的做法，使其枚举个数减少。

注意到每一个周期长度都不大于 $1000$，所以考虑在这上面做手脚：预先求出他们长度的 $lcm$（最小公倍数），记为 $l$。枚举 $l$ 局内双方输的局数，再看看 $n$ 中有几个 $l$，最后乘起来，枚举余数即可。

## 技巧
1. ``lcm(a,b) = a / gcd(a,b) * b``。
3. $\gcd$ 函数可以直接使用 C++ 中自带的 ``__gcd()``，CSP 已经给用啦（~~不会还有人不知道吧~~）！

## 代码
以下是参考代码，珍爱生命，远离抄袭。

Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, l, cnt, q, lens, lent, losea, loseb;
string s, t;

int lcm(int a, int b){return a / __gcd(a, b) * b;}

void iswin(int a, int b){
	if(s[a] == 'R' && t[b] == 'S')	loseb++;
	if(s[a] == 'S' && t[b] == 'R')	losea++;
	if(s[a] == 'S' && t[b] == 'P')	loseb++;
	if(s[a] == 'P' && t[b] == 'S')	losea++;
	if(s[a] == 'P' && t[b] == 'R')	loseb++;
	if(s[a] == 'R' && t[b] == 'P')	losea++;
}

signed main(){
	scanf("%d", &n);
	cin >> s >> t;
	lens = s.length(), lent = t.length();
	l = lcm(lens, lent);
	for(int i=0;i<l;i++)	iswin(i % lens, i % lent);
	cnt = n / l, q = n % l;
	losea *= cnt, loseb *= cnt;
	for(int i=0;i<q;i++)	iswin(i % lens, i % lent);//是 0 到 q-1，不是1到q，卡了我好久，第三个点过不去
	cout << losea << ' ' << loseb << endl;
	return 0;
}
```



---

## 作者：Eason_AC (赞：1)

## Content
有 $2$ 个人在玩石头剪刀布，已知他们的出手都有一定的规律，求 $n$ 局之后两个人各输了几局。

**数据范围：$1\leqslant n\leqslant 2\times 10^9$，周期长度不超过 $10^3$。**
## Solution
一个一个模拟肯定不现实，会 TLE，所以我们应当考虑是否有更快速的方法。

我们设第一个人的周期长度为 $a_1$，第二个人的周期长度为 $a_2$，则很容易发现，在 每 $\operatorname{lcm}(a_1,a_2)$ 局里面，他们输的局数是固定的，因为他们正好能够做完整数个周期，而且可以证明 $\operatorname{lcm}(a_1,a_2)<10^6$，所以我们考虑将一个周期里面每局的情况都统计出来，如果能凑出 $\operatorname{lcm}(a_1,a_2)$ 局出来，就计算有多少个 $\operatorname{lcm}(a_1,a_2)$ 局，显然有 $\left\lfloor\dfrac{n}{\operatorname{lcm}(a_1,a_2)}\right\rfloor$ 个，直接拿两个人在每 $\operatorname{lcm}(a_1,a_2)$ 局里面输的次数乘上 $\left\lfloor\dfrac{n}{\operatorname{lcm}(a_1,a_2)}\right\rfloor$，再加上他们剩下来的几局中的输的次数即可。
## Code
```cpp
string s1, s2;
int n, loses[1000007], loset[1000007], lose1, lose2, ans1, ans2;

inline int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}
inline int lcm(int a, int b) {return a / gcd(a, b) * b;} //NOIP2020T1 血的教训

int main() {
	n = Rint; str(s1, len1); str(s2, len2);
	int round = lcm(len1, len2);
	F(i, 0, round - 1) {
		if((s1[i % len1] == 'R' && s2[i % len2] == 'P') || (s1[i % len1] == 'P' && s2[i % len2] == 'S') || (s1[i % len1] == 'S' && s2[i % len2] == 'R'))
			loses[i + 1]++, lose1++;
		if((s2[i % len2] == 'R' && s1[i % len1] == 'P') || (s2[i % len2] == 'P' && s1[i % len1] == 'S') || (s2[i % len2] == 'S' && s1[i % len1] == 'R'))
			loset[i + 1]++, lose2++;
	}
	F(i, 1, n % round) ans1 += loses[i], ans2 += loset[i];
	return printf("%d %d", ans1 + lose1 * (n / round), ans2 + lose2 * (n / round)), 0;
}
```

---

## 作者：fzj2007 (赞：1)

`CF`的题挺有意思的。。

# 第一步 读题

> 有两个人在玩石头剪刀布游戏： $R$ -石头 $P$ -布 $S$ -剪刀 每个人都会按照一个周期出石头，剪刀或布。 周期肯定在 $1000$ 以内（包括 $1000$ ）问玩 $n$ 把后， 双方各**输**了多少次。

简化一下，就是相当于两个机器玩石头剪刀布，每个机器都会按照一个周期来出。最后问各$\color{red}\text{输}$了多少次。

坑点：

1、问的是各输了多少次而不是各赢了多少次！

# 第二步 思路

思路一：一次一次模拟，时间复杂度是 $O\left(n\right)$，但是 $n$ 的上限是 $2\times 10^9$，明显超时。

思路二：由于是有周期性的，那么我们可以寻找一个周期包含了这两个周期（即合并这两个周期，就是 $\operatorname{lcm}(m,k)$），这样剩下的直接看有几次周期再加上剩余的次数就解决问题了。时间复杂度是$O\left(\max\left(m,k\right)\right)$，由于 $m$，$k$ 的范围是 $1000$，所以不会超时。

# 第三步 知识点讲解

上面我们涉及到了一个最小公倍数。下面我们来讲解一下编程实现。

由最小公倍数的定义我们可以得到 $\operatorname{lcm}(a,b) = \gcd(a,b) \times \frac{a}{\gcd(a,b)}\times \frac{b}{\gcd(a,b)} = \frac{a\times b}{\gcd(a,b)}$

我们知道 $\gcd(a,b)$ 可以用[辗转相除法](https://baike.baidu.com/item/%E6%AC%A7%E5%87%A0%E9%87%8C%E5%BE%97%E7%AE%97%E6%B3%95/1647675?fromtitle=%E8%BE%97%E8%BD%AC%E7%9B%B8%E9%99%A4%E6%B3%95&fromid=4625352&fr=aladdin)来求解。辗转相除法代码：

```cpp
int gcd(int x,int y){
	if(y==0) return x;
   	retun gcd(y,x%y);
}
```

压行：

```cpp
int gcd(int x,int y){
	return !y?x:gcd(y,x%y);
}
```
# 第四步 代码讲解

终于到了你们最喜欢的时刻了......

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
inline int read(){//习惯快读
	int ans=0,flag=1;
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+(ch^'0');
		ch=getchar();
	}
	return ans*flag;
}
int n,len,al,bl;// n用于输入，len保存整个周期长度，al和bl保存最终结果
string a,b;//读入的数据
int gcd(int x,int y){//这个是辗转相除法
	return !y?x:gcd(y,x%y);
}
inline int lcm(int x,int y){//最小公倍数
	return x*y/gcd(x,y);
}
inline int findint(char u){//返回一个整数值QAQ,本人很讨厌字符串和字符
	return (u=='S'?1:(u=='P'?2:3));
	//剪刀1，布2，石头3 
}
inline int win(char x,char y){//判断谁胜利，如果第一个人胜利返回1，如果第二个人胜利返回2，平局返回0
	int nowx=findint(x),nowy=findint(y);
	if(nowx==nowy) return 0;
	if(nowx==1&&nowy==2) return 1;//石头剪刀布都会玩吧QAQ，下面都是这样的判断，可以参考上面的findint来理解。
	if(nowx==1&&nowy==3) return 2;
	if(nowx==2&&nowy==3) return 1;
	if(nowx==2&&nowy==1) return 2;
	if(nowx==3&&nowy==2) return 2;
	if(nowx==3&&nowy==1) return 1;
}
int main(){
	n=read();//读入
	cin>>a>>b;//不得不使用cin......
	len=lcm(a.length(),b.length());//寻找周期长度
	for(int i=0;i<len;i++)//注意一定是<len，被卡了好几次。因为下标是0开始！
		if(win(a[i%(a.length())],b[i%(b.length())])==1) bl++;//由于len有很大可能超过原本数据长度，所以需要进行取模，表示进行循环。
		else if(win(a[i%(a.length())],b[i%(b.length())])==2) al++;	//同上
	al*=(n/len);//周期次数
	bl*=(n/len);//周期次数
	for(int i=0;i<n%len;i++)//下面同上
		if(win(a[i%(a.length())],b[i%(b.length())])==1) bl++;
		else if(win(a[i%(a.length())],b[i%(b.length())])==2) al++;	
	printf("%d %d\n",al,bl);//最后输出！		
	return 0;//23333byebye
}
```

# 第五步 宣传

如果有帮助，请点个赞，谢谢！（撰文不易，dalao勿喷！）如果发现我的讲解有bug，请及时指出！


---

## 作者：JimmyF (赞：1)


此为本题第一篇题解：

### 题目直通车 [CF173A Rock-Paper-Scissors](https://www.luogu.com.cn/problem/CF173A)

这题如果直接循环到
$n$
，那时间复杂度就是
$O(n)$
，也就是
$O(2$
$\times$
$10^9$
$)$
，肯定超时。


所以就把这题转化成一个很简单一个周期问题。

先来思考周期长度：也就是两个人周期的**最小公倍数**
```cpp
string a,b;  //定义
cin>>a>>b;  //输入
al=a.size(),bl=b.size();  //测长
int t=al*bl/__gcd(al,bl);   //算出周期长度
```

但一个周期有可能超过了两个人出拳的周期长度，比如：

```cpp
a:RPS
b:RSPP
周期长度:12
a:RPS_ _ _ _ _ _ _ _ _
b:RSPP _ _ _ _ _ _ _ _ 
-------------------分割线------------------
a:RPS RPS RPS RPS
b:RSPP RSPP RSPP
```


所以接下来就是将两个人出拳周期补全。

```cpp
for(int i=al; i<t; i++)
a[i]=a[i-al];
for(int i=bl; i<t; i++)
b[i]=b[i-bl];
	
```

或者可以直接计算出当前位置在两人出全周期里的哪个位置。
```cpp
for(int i=0; i<t; i++)
    at=i%al,bt=i%bl;   //用当前位置分别%一下两人出拳的周期就行了
```

然后判断两人胜负的情况：
```
if(a[at]=='R'&&b[bt]=='S')bh++;
if(a[at]=='S'&&b[bt]=='R')ah++;
if(a[at]=='S'&&b[bt]=='P')bh++;
if(a[at]=='P'&&b[bt]=='S')ah++;
if(a[at]=='P'&&b[bt]=='R')bh++;
if(a[at]=='R'&&b[bt]=='P')ah++;
```

然后
$ah$
和
$bh$
分别表示在一个周期内两人分别赢了多少次，再计算出
$n$
里面有多少个周期，就是
$n/t$。
代表有
$n/t$
个
$ah$
和
$bh$
。所以：
```cpp
ah*=n/t,bh*=n/t;
```
但是别忘了
$n\%t$
不一定等于
$0$
，可能会有余数，所以我们要针对余数再做一次处理：
```cpp
for(int i=1; i<=n%t; i++)  //注意是n%t
{
    ......                
}
```
最后输出
$ah$
和
$bh$
。

时间复杂度为
$O(1000^2)$
。

完整代码：


```cpp
#include<bits/stdc++.h>  //头文件
using namespace std;
int n,t,at,bt,al,bl,ah,bh;  
string a,b;  //定义（变量有些随意，请见谅）
int main()
{
	cin>>n>>a>>b;  //输入
	al=a.size(),bl=b.size();  //测长
	t=al*bl/__gcd(al,bl);   //算出周期长度
	for(int i=0; i<t; i++)
	{
		at=i%al,bt=i%bl;  //算位置（大家可以自己在草稿本上推一推）
		if(a[at]=='R'&&b[bt]=='S')bh++;
		if(a[at]=='S'&&b[bt]=='R')ah++;
		if(a[at]=='S'&&b[bt]=='P')bh++;
		if(a[at]=='P'&&b[bt]=='S')ah++;
		if(a[at]=='P'&&b[bt]=='R')bh++;
		if(a[at]=='R'&&b[bt]=='P')ah++;
        //六种情况判断胜负
	}  
    //处理一个周期
	ah*=n/t,bh*=n/t;  //计算所有周期的胜负
	for(int i=1; i<=n%t; i++)  //注意是n%t
	{
		at=(i-1)%al,bt=(i-1)%bl;
		if(a[at]=='R'&&b[bt]=='S')bh++;
		if(a[at]=='S'&&b[bt]=='R')ah++;
		if(a[at]=='S'&&b[bt]=='P')bh++;
		if(a[at]=='P'&&b[bt]=='S')ah++;
		if(a[at]=='P'&&b[bt]=='R')bh++;
		if(a[at]=='R'&&b[bt]=='P')ah++;
	}
    //处理余数
	cout<<ah<<" "<<bh<<endl;  //输出
	return 0;  //完结撒花
}
```


---

## 作者：lucky2008 (赞：0)

# CF173A题解

## [题目传送门](https://www.luogu.com.cn/problem/CF173A)

### 题目大意

有 $2$ 个人在玩石头剪刀布，已知他们的出手都有一定的规律，求 $n$ 局之后两个人各输了几局。

### 思路

这提数据很大 $O(n)$ 枚举肯定超时，但这题给定了出手的规则只需枚举周期即可。

## AC代码

最后附上ac代码。

```cpp
#include<iostream>
#include<queue>
#include<algorithm>
#include<string>
using namespace std;
int n,x,y; 
string a,b;
queue<char> p,q;//队列模拟过程会很方便 
void f(char a,char b)//模拟猜拳 
{
	if(a==b)
		return;
	if(a=='R')
	{
		if(b=='P')
			x++;
		else
			y++;
	}
	if(a=='P')
	{
		if(b=='S')
			x++;
		else
			y++;
	}
	if(a=='S')
	{
		if(b=='R')
			x++;
		else
			y++;
	}
	return;
}
int gcd(int a,int b)//最大公因数 
{
	while(b)
	{
		int tmp=b;
		b=a%b;
		a=tmp;
	}
	return a;
}
int main()
{
	cin>>n;
	cin>>a>>b;
	for(int i=0;i<a.size();++i)
		q.push(a[i]);
	for(int i=0;i<b.size();++i)
		p.push(b[i]);
	int len=(a.size()*b.size())/gcd(a.size(),b.size());//算最小公倍数 
	for(int i=1;i<=len;++i)
	{
		f(q.front(),p.front());//每次队头两个进行猜拳 
		q.push(q.front());p.push(p.front());//猜完拳就 
		q.pop();p.pop();
	}
	int s1=n/len,s2=n%len;//s1表示有多少个完整周期，s2表示最后一个周期还剩下多少个 
	x=s1*x;y=s1*y;
	for(int i=1;i<=s2;++i)
	{
		f(q.front(),p.front());
		q.push(q.front());p.push(p.front());
		q.pop();p.pop();
	}
	cout<<x<<" "<<y;
	return 0;
}

```


---

## 作者：Autism_ever (赞：0)

## 此题不可以循环枚举
## 要用最小公倍数
## 否则会超时TLE
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
string s, k;//规律 
int l, h; 
int n;
int gcd(int a, int b)//最大公约数 
{
	if(b==0)return a;//递归循环 
	return gcd(b,a%b);
}
int main()
{
	cin>>n;//输入 
	cin>>s>>k;
	int x=(s.size()*k.size())/(gcd(s.size(),k.size()));//求俩长度的最小公倍数，用两数之积除两数的最大公因数 
	for(int i=1;i<=x;i++)
	{
		if(s[i%s.size()]==k[i%k.size()])//判断胜负局 
		{
			continue;
		}
		else if(s[i%s.size()]=='P'&&k[i%k.size()]=='S')//先判断第一个人输的 
		{
			l++;
		}
		else if(s[i%s.size()]=='S'&&k[i%k.size()]=='R')
		{
			l++;
		}
		else if(s[i%s.size()]=='R'&&k[i%k.size()]=='P')
		{
			l++;
		}
		else
		{
			h++;
		}
	}
	int sum=n/x;//有多少次 
	int num=n%x;//剩下多少次 
	l=l*sum;
	h=h*sum;
	for(int i=1;i<=num;i++)
	{
		if(s[i%s.size()]==k[i%k.size()])//判断 
		{
			continue;
		}
		else if(s[i%s.size()]=='P'&&k[i%k.size()]=='S')
		{
			l++;
		}
		else if(s[i%s.size()]=='S'&&k[i%k.size()]=='R')
		{
			l++;
		}
		else if(s[i%s.size()]=='R'&&k[i%k.size()]=='P')
		{
			l++;
		}
		else
		{
			h++;
		}
	}
	cout<<l<<" "<<h<<endl;//输出 
	return 0;//华丽的结尾-v- 
}

```


---

## 作者：yxy666 (赞：0)

 题意：有两个机器人在玩石头剪刀布，他们的出牌周期都是固定的。当他们玩了 $n$ 局的时候，每一个人输了几局。
 
  本题最大坑点：题目要求我们求的是每个人输了几局！！！

笨蛋想法：按照规律一次一次的比较，那么时间复杂度就是 $O(n)$ ,然而对于百分百的数据 $n$ 上到了 $10^9$，所以想法太笨了，不采用，$O(2)$吸氧都没用。

聪明蛋想法：说实话，刚看到这道题，我就联想到了周期性问题。因为 $n$ 实在是太大了。但是我们其实只用将  $lcm(len,len2)$ 的值求出来，然后看一下需要算几次就好了。这里的 $len$表示第一个人的周期长度， $len2$ 表示第二个人的周期长度， $lcm$ 指最小公倍数（就是这个数既能被 $len$ 整除，也能被 $len2$ 整除）。然后乘以一共做了多少次，再把最后的一点零头给算上去。

$code$ :
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1000005;
int ans,cnt,n,step;
char first[maxn],last[maxn];
void check(char x,char y){
	if(x==y)return;
	if(x=='R'&&y=='P'){ans++;return;}
	if(x=='R'&&y=='S'){cnt++;return;}
	if(x=='P'&&y=='R'){cnt++;return;}
	if(x=='P'&&y=='S'){ans++;return;}
	if(x=='S'&&y=='R'){ans++;return;}
	if(x=='S'&&y=='P'){cnt++;return;}
}//check这个函数用于求对于这一次对决，到底是平局还是谁输了
int gcd(int x,int y){
	int maxn=max(x,y);
	for(int i=maxn;i<=x*y;i+=maxn)if(i%x==0&&i%y==0)return i;	
}//本人是蒟蒻，不会高端操作。。。一个一个枚举最小公倍数，每次加上两数中的最大值。如果都能整除，就返回这个数
inline int read(){
	int ret=0,f=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-f;ch=getchar();}
	while(isdigit(ch))ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}//快读
int main(){
	n=read();
	scanf("%s",first+1);
	scanf("%s",last+1);
	int len=strlen(first+1),len2=strlen(last+1);
	int m=gcd(len,len2);//求最小公倍数
	for(int i=len+1;i<=m;i++)first[i]=first[++step],step==len?step=0:step;//给第一个人后面的字符串赋值，后面的是三目运算符，等价于if(step==len)step=0;else step=step;
	step=0;
	for(int i=len2+1;i<=m;i++)last[i]=last[++step],step==len2?step=0:step;//给第二个人后面的字符串赋值，后面的是三目运算符，等价于if(step==len2)step=0;else step=step;
	for(int i=1;i<=m;i++)check(first[i],last[i]);//把这m次的求出来
	int size=n/m;n%=m;//size表示一共做了size个m次，n这里表示剩下的零头
	ans*=size;cnt*=size;//一共循环了size次
	for(int i=1;i<=n;i++)check(first[i],last[i]);//处理零头
	printf("%d %d\n",ans,cnt);
	return 0;
}
```


---

## 作者：zmza (赞：0)

这题是模拟，但是不能像[这题](https://www.luogu.com.cn/problem/P1328)一样，一个一个枚举，不然会超时。应该要找周期。代码里有解释。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b)
{
	if(b == 0)
	{
		return a;
	}
	return gcd(b,a % b);
}
char a[1005],b[1005];//用char数组存
int shub,shua;
int ansa,ansb;
int main()
{
	int n;
	scanf("%d%s%s",&n,a,b);
	int lena = strlen(a);//甲周期长度
	int lenb = strlen(b);//乙周期长度
	int zhou = lena * lenb / gcd(lena,lenb);//算出甲乙周期长度
	for(int i = 0; i < zhou; i++)//算出一个周期甲输了几次，乙输了几次。
	{
		int ia = i % lena;
		int ib = i % lenb;
		if(a[ia] != b[ib])
		{
			if(a[ia] == 'R' && b[ib] == 'S' || a[ia] == 'S' && b[ib] == 'P' || a[ia] == 'P' && b[ib] == 'R')
			{
				shub++;
			}
			else
			{
				shua++;
			}
		}
	}
	ansa = shua * (n / zhou);//先算出几个周期甲乙各输了几次。
	ansb = shub * (n / zhou);
	for(int i = 0; i < n % zhou; i++)//周期的剩余再算出来
	{
		int ia = i % lena;
		int ib = i % lenb;
		if(a[ia] != b[ib])
		{
			if(a[ia] == 'R' && b[ib] == 'S' || a[ia] == 'S' && b[ib] == 'P' || a[ia] == 'P' && b[ib] == 'R')
			{
				ansb++;
			}
			else
			{
				ansa++;
			}
		}
	} 
	printf("%d %d",ansa,ansb);//输出答案
    return 0;
}
```


---

## 作者：hmya (赞：0)

看看这道题，是不是第一时间想到了[生活大伊万版石头剪刀布](https://www.luogu.com.cn/problem/P1328)？

天哪，这不水题吗？这难度还高一点，作者大大良心，诚不欺我！
然后代码一摆：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[3][3]=
{
{1,2,0},
{0,1,2},
{2,0,1}
};
string c,b;
queue<int> r1,r2;
long long int lose1,lose2;
int main(){
	scanf("%d",&n);
	cin>>c;
	cin>>b;
	for(int i=0;i<c.size();i++){
		if(c[i]=='R'){
			r1.push(2);
		}
		if(c[i]=='P'){
			r1.push(1);
		}
		if(c[i]=='S'){
			r1.push(0);
		}
	}
	for(int i=0;i<b.size();i++){
		if(b[i]=='R'){
			r2.push(2);
		}
		if(b[i]=='P'){
			r2.push(1);
		}
		if(b[i]=='S'){
			r2.push(0);
		}
	}
	for(int i=1;i<=n;i++){
		if(a[r1.front()][r2.front()]==0){
			lose1++;
		}
		if(a[r1.front()][r2.front()]==2){
			lose2++;
		}
		r1.push(r1.front());
		r2.push(r2.front());
		r1.pop();
		r2.pop();
	}
	printf("%d %d",lose1,lose2);
	return 0;
}
```

然后，你就会看见刚出炉的新鲜的WA，而且是第一个点就WA了

言归正传，why上面的代码慢？

因为模拟**太费时间**了

n最大为2e9

模拟是会T的（我为什么是WA？？？）

那我们就要想一个更优秀的方法

仔细想，如果我们人工手算，n=2e9，我们会模拟吗？

显然，不可能

那我们用什么方法呢？

难道是传说中的…******周期问题******！

没错，你真是个小机灵鬼！

用公约数算出公倍数，再用公倍数算周期，最后把剩下的数进行模拟，既不会超时，又可以省下来时间复杂度

方向确定了，代码真的不难搞！

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long int n;
int a[3][3]=//存储剪刀石头布的输赢情况，赢为2，输为0
{
{1,2,0},
{0,1,2},
{2,0,1}
};
int gcd(int a,int b){//最大公约数
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
int gbs(int a,int b){//最小公倍数
	return a*b/gcd(a,b);
}
string c,b;
queue<long long int> r1,r2;//模拟队列
long long int lose1,lose2;//统计（注意，要开longlong，不然会爆）
int main(){
	scanf("%lld",&n);
	cin>>c;
	cin>>b;
	for(int i=0;i<c.size();i++){//登记第一个人的周期
		if(c[i]=='R'){
			r1.push(2);
		}
		if(c[i]=='P'){
			r1.push(1);
		}
		if(c[i]=='S'){
			r1.push(0);
		}
	}
	for(int i=0;i<b.size();i++){//登记第二个人的周期
		if(b[i]=='R'){
			r2.push(2);
		}
		if(b[i]=='P'){
			r2.push(1);
		}
		if(b[i]=='S'){
			r2.push(0);
		}
	}
	int len=gbs(c.size(),b.size());//记录周期长度
	for(int i=0;i<len;i++){//循环周期情况
		if(a[r1.front()][r2.front()]==0){//第一个人输了
			lose1++;
		}
		if(a[r1.front()][r2.front()]==2){//第二个人输了
			lose2++;
		}
		r1.push(r1.front());
		r2.push(r2.front());
		r1.pop();
		r2.pop();
	}
	lose1*=(n/len);//周期在n里循环的次数
	lose2*=(n/len);
	while(!r1.empty()){//重置
		r1.pop();
	}
	while(!r2.empty()){//重置
		r2.pop();
	}
	for(int i=0;i<c.size();i++){//重置
		if(c[i]=='R'){
			r1.push(2);
		}
		if(c[i]=='P'){
			r1.push(1);
		}
		if(c[i]=='S'){
			r1.push(0);
		}
	}
	for(int i=0;i<b.size();i++){//重置
		if(b[i]=='R'){
			r2.push(2);
		}
		if(b[i]=='P'){
			r2.push(1);
		}
		if(b[i]=='S'){
			r2.push(0);
		}
	}
	for(int i=0;i<n%len;i++){//周期剩下的次数
		if(a[r1.front()][r2.front()]==0){
			lose1++;
		}
		if(a[r1.front()][r2.front()]==2){
			lose2++;
		}
		r1.push(r1.front());
		r2.push(r2.front());
		r1.pop();
		r2.pop();
	}
	printf("%lld %lld",lose1,lose2);
	return 0;
}//END!
```

如果看不懂，建议回去再看看思路

好了，本次题解就到这里，看懂了就点个赞bia

---

## 作者：hensier (赞：0)

~~深感楼上的方法过于复杂，于是本蒟蒻来补充一下。~~

【基本思路】

由于石头剪刀布是循环的，所以我们只需要找到周期长度即可。周期长度其实就是：

$$lcm(m,k)$$

（`lcm`为最小公倍数，$lcm(a,b)=\frac{ab}{gcd(a,b)}$。题目中已经说了$m$是字符串$A$的长度，$k$是字符串$B$的长度）

也就是说，我们可以将$n$拆分为：

$$n=n/lcm(g,k)·lcm(g,k)+n\,mod\,lcm(g,k)$$

（以上的$/$表示整除）

我们根据这个思路，得到代码：

```cpp
#include<cstdio>
int n,cycle,la,lb,pa,pb,sa,sb,win;
char a[1001],b[1001];
int gcd(int x,int y)//gcd函数
{
    return y?gcd(y,x%y):x;
}
int len(char s[])//求字符串长度
{
    int i=0;
    for(;s[i];i++);
    return i;
}
int check(char a,char b)//判断谁赢谁输（A赢则返回1，B赢则返回-1，平局返回0）
{
    if(a==b)return 0;//相等返回0
    switch(a)
    {
        case 'R':
        {
            if(b=='P')return -1;
            return 1;
        }
        case 'P':
        {
            if(b=='R')return 1;
            return -1;
        }
        case 'S':
        {
            if(b=='R')return -1;
            return 1;
        }
    }
}
void simulate(int bound,int &A,int &B)//取引用是必要的
{
    while(bound--)//循环
    {
        int win=check(a[A++],b[B++]);//判断
        sa+=win==-1?1:0;
        sb+=win==1?1:0;//累加
        if(A==la)A=0;//到头的话要重新赋值为0
        if(B==lb)B=0;
    }
}
int main()
{
    scanf("%d\n%s\n%s",&n,a,b);//输入
    la=len(a);
    lb=len(b);//赋值
    cycle=la*lb/gcd(la,lb);//周期计算
    simulate(cycle,pa,pb);//模拟
    sa*=n/cycle;
    sb*=n/cycle;//输的次数要乘以周期次数
    simulate(n%cycle,pa,pb);//把剩余的判断一遍
    printf("%d %d",sa,sb);//输出
}
```

---

