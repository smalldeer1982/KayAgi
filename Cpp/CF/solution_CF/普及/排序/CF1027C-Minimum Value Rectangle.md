# Minimum Value Rectangle

## 题目描述

You have $ n $ sticks of the given lengths.

Your task is to choose exactly four of them in such a way that they can form a rectangle. No sticks can be cut to pieces, each side of the rectangle must be formed by a single stick. No stick can be chosen multiple times. It is guaranteed that it is always possible to choose such sticks.

Let $ S $ be the area of the rectangle and $ P $ be the perimeter of the rectangle.

The chosen rectangle should have the value $ \frac{P^2}{S} $ minimal possible. The value is taken without any rounding.

If there are multiple answers, print any of them.

Each testcase contains several lists of sticks, for each of them you are required to solve the problem separately.

## 说明/提示

There is only one way to choose four sticks in the first list, they form a rectangle with sides $ 2 $ and $ 7 $ , its area is $ 2 \cdot 7 = 14 $ , perimeter is $ 2(2 + 7) = 18 $ . $ \frac{18^2}{14} \approx 23.143 $ .

The second list contains subsets of four sticks that can form rectangles with sides $ (1, 2) $ , $ (2, 8) $ and $ (1, 8) $ . Their values are $ \frac{6^2}{2} = 18 $ , $ \frac{20^2}{16} = 25 $ and $ \frac{18^2}{8} = 40.5 $ , respectively. The minimal one of them is the rectangle $ (1, 2) $ .

You can choose any four of the $ 5 $ given sticks from the third list, they will form a square with side $ 5 $ , which is still a rectangle with sides $ (5, 5) $ .

## 样例 #1

### 输入

```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5
```

### 输出

```
2 7 7 2
2 2 1 1
5 5 5 5
```

# 题解

## 作者：Siyuan (赞：6)

[$$\Large\texttt{My Blog}$$](https://hydingsy.github.io/)

---

> 题目链接：[Codeforces 1027C](https://codeforces.com/contest/1027/problem/C)

给出 $n$ 条线段，在其中选择 $4$ 条线段组成一个矩形，记 $P$ 为围成的矩形的周长，$S$ 为围成的矩形的面积，求使得 $\frac{P^2}{S}$ 最小的 $4$ 条线段（多组数据）。

数据范围：$1\leqslant T\leqslant 10^6$，$4\leqslant\sum n\leqslant 10^6$，$1\leqslant a_i\leqslant 10^4$

---

## Solution

设 $4$ 条线段为 $a,a,b,b\ (a\leqslant b)$，则有 $P=2\cdot(a+b)$，$S=ab$，可得

$$\frac{P^2}{S}=\frac{4a^2+4b^2+8ab}{ab}=4(\frac{a}{b}+\frac{b}{a})+8$$

因此我们只需要最小化 $\frac{b}{a}$ 即可（千万注意此处 $a\leqslant b$）。

**分类讨论**

1. 如果有 $4$ 条相等的线段，肯定选取这 $4$ 条。
2. 否则将数量不小于 $2$ 的线段从小到大排序，贪心选择相邻的线段。将当前的 $a',b'$ 和已知的较优解 $a,b$ 比较得出更优解。

**注意精度问题！**我们可以将判定条件 $\frac{b'}{a'}<\frac{b}{a}$ 转化为 $ab'<a'b$ 即可防止精度问题。

**时间复杂度**：$\Theta(T\cdot n\log a_{\max})$

---

## Code

```cpp
#include <cstdio>
#include <cctype>
#include <map>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
inline char in() {
    static char buf[10001],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
template <class Tp> void read(register Tp &s) {
    s=0;
    register bool neg=0;
    register char c;
    while(!isdigit(c=in())) if(c=='-') neg=1;
    while(s=(s<<3)+(s<<1)+c-48,isdigit(c=in()));
    s=(neg?-s:s);
}

int T,n,a[1000005];
std::map<int,int> cnt;
int main() {
    for(read(T);T;--T) {
        cnt.clear();
        read(n);
        int t,m=0;
        FOR(i,1,n) read(t),cnt[t]++;
        bool flg=0;
        for(std::map<int,int>::iterator it=cnt.begin();it!=cnt.end();++it) {
            if((*it).second>=2) a[++m]=(*it).first;
            if((*it).second>=4) {
                flg=1;
                int ans=(*it).first;
                printf("%d %d %d %d\n",ans,ans,ans,ans);
                break;
            }
        }
        if(flg) continue;
        int x=a[1],y=a[2];
        FOR(i,3,m) if(x*a[i]<a[i-1]*y) x=a[i-1],y=a[i];
        printf("%d %d %d %d\n",x,x,y,y);
    }
    return 0;
}
```

---

## 作者：HansLimon (赞：3)

## 一种很简单的解法
### Part 1
先提一下大体思路：set查重后记录，algorithm排序，最后跑一趟for
###### 主要因为有2秒时限qwq
因为我们要构成一个矩形, 所以对于输入的木棍, 每出现两次才加入我们的候选数组中, 这一步通过set实现. 当然, 也可以用**布尔数组**标记
###### ~~但是我懒~~
```cpp
std::set<int> corder;
std::set<int>::iterator cnt;//迭代器, 应该能理解所以就不说了qwq
for (register int i = 1;i <= n;i ++){
	scanf("%d", &now);
	cnt = corder.find(now);
	if (cnt == corder.end())corder.insert(now);
	else {
		stick[++ tmp] = *cnt;//stick是我们的备选数组
		corder.erase(cnt);
	}
}
```

------------

### Part 2
然后就来求解这个问题了. 稍微提一下过程:
## $ {{P^2} \over {S}} $ \-\-\> $ {{(2(a + b))^2} \over {ab}} $ \-\-\> $ {{2a^2 + 4ab + 2b^2} \over {ab}} $ \-\-\> $ {{a} \over {b}} + {{b} \over {a}} $
最后一步各位可能会觉得有问题, 但请注意, 被删去的**都是常数级的值**, 是不会影响判定的.

下面的代码请勿尝试理解, 因为尚未讲完:
```cpp
void compare(){
	register int a = stick[1], b = stick[2];
	register double _min = b/(double)a;
	for (register int i = 2, x = a, y = b;i <= tmp;i ++, x = y, y = stick[i])
		if (y/(double)x < _min){
			_min = y/(double)x;
			a = x, b = y;
		}
	printf("%d %d %d %d\n", a, b, a, b);
}
```
很明显, 存在错误, 因为此时的stick数组是无序的. 应把每个元素挨个比较, 但是这样又太麻烦了(显而易见qwq). 所以我们换个思路: 把它变得有序.
	
    std::sort(stick + 1, stick + tmp + 1);
可能有人会想知道: 因为sort是从小到大排, 而我们的目的是最小比值, 是否有误?

实际上是无误的
###### 废话, 不然我还能发题解?
#### 比值表示了元素的差值, 而sort保证了相邻两元素的差值不会被第三元素影响(也就是说它一定是最小的)
###  Part 3 放代码:
```cpp
#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

const int N = 1e6 + 7;
int T, n, now, tmp, stick[N];
set<int> corder;
set<int>::iterator cnt;

void compare(){
	register int a = stick[1], b = stick[2];
	register double _min = b/(double)a;
	for (register int i = 2, x = a, y = b;i <= tmp;i ++, x = y, y = stick[i])
		if (y/(double)x < _min){
			_min = y/(double)x;
			a = x, b = y;
		}
	printf("%d %d %d %d\n", a, b, a, b);
}

int main(){
	scanf("%d", &T);
    while (T --){
		scanf("%d", &n);
		for (register int i = 1;i <= n;i ++){
			scanf("%d", &now);
			cnt = corder.find(now);
			if (cnt == corder.end())corder.insert(now);
			else {
				stick[++ tmp] = *cnt;
				corder.erase(cnt);
			}
		}
		sort(stick + 1, stick + tmp + 1);
		compare();
		tmp = 0;
		corder.clear();//记得初始化!qwq
    }
	return 0;//啊朋友再见~
}
```
咕咕咕~~

---

## 作者：YellowBean_Elsa (赞：2)

#### 数学题

令矩形边长为 $a,b$，则 $S=ab$，$P=2(a+b)$

$$\frac{P^2}{S}=\frac{4(a+b)^2}{ab}$$
$$=4(\frac{a}{b}+\frac{b}{a}+2)$$

我们只需求令 $\frac{a}{b}+\frac{b}{a}$ 最小的 $a,b$ 即可。

设 $x=\frac{a}{b}$，则：

$$\frac{a}{b}+\frac{b}{a}=x+\frac{1}{x}$$

由**对钩函数**可知，$x$ 越接近 $1$ 越佳。

那么我们对选出的成对的边长排序，这样易知选相邻的边长最佳。

（反证易得）

那我们扫一遍就行了。注意比较两组解优劣时为防精度挂掉可以转化成乘法，且记得开 long long。

特别地，如果有四边相等的正方形，则一定是最优解，可以特判优化。（然而你不特判会T嘤嘤嘤）

```cpp
//coder: Feliks*GM-YB
#include<bits/stdc++.h>
#define fu(i,a,b) for(int i = a, I = (b) + 1; i < I; ++i)
#define fd(i,a,b) for(int i = a, I = (b) - 1; i > I; --i)
typedef long long ll;
using namespace std;
const int N=1e6+5;
const int M=1e4+5;
namespace rd{
	const int BUF=1<<21;
	char rB[BUF],*rS,*rT;
	inline char gc(){
		return rS==rT&&(rT=(rS=rB)+fread(rB,1,BUF,stdin),rS==rT)?EOF:*rS++;
	}inline int read(){
	    int x=0;char ch=gc();
	    while(!isdigit(ch))ch=gc();
	    while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=gc();
	    return x;
	}
}using namespace rd;
int T,n;
int a[N],b[N],cnt,p[M];
//从a中选成对的放入b；p是map的作用 
bool vis[M];
int ans1,ans2;
inline void init(){
	memset(p,0,sizeof(p));
	memset(vis,0,sizeof(vis));
	cnt=0;
}
int main(){
	T=read();
	while(T--){
		init();
		n=read();
		fu(i,1,n){
			a[i]=read();
			p[a[i]]++;
		}bool flg=0;
		fu(i,1,n){
			if(vis[a[i]])continue;//注意别重复选了 
			vis[a[i]]=1; 
			if(p[a[i]]>=4){//正方形最佳特判 
				flg=1;
				printf("%d %d %d %d\n",a[i],a[i],a[i],a[i]);
				break;
			}if(p[a[i]]>=2)b[++cnt]=a[i];
		}if(flg)continue;
		sort(b+1,b+cnt+1);
		ans1=b[1],ans2=b[2];
		fu(i,2,cnt-1)//找最小值 
			if(1LL*b[i]*ans2>1LL*b[i+1]*ans1)ans1=b[i],ans2=b[i+1];
		printf("%d %d %d %d\n",ans1,ans1,ans2,ans2);
	}
	return 0;
}
```



---

## 作者：轻绘 (赞：1)

## 数学前置
### 需要用到小学数学及基本不等式。
我们先设长为 $a$ ,宽为 $b$ 。

 $$\dfrac{P^2}{S}=\dfrac{(2(a+b))^2}{ab}=\dfrac{4a^2+4b^2}{ab}+4=\dfrac{4a}{b}+\dfrac{4b}{a}+4$$
 
 根据基本不等式当 $a>0,b>0$ 时 $\dfrac{4a}{b}+\dfrac{4b}{a}>=8$
 
 当且仅当 $\dfrac{4a}{b}=\dfrac{4b}{a}$ 时取到等号，即 $a=b$ 时 
 $\dfrac{P^2}{S}$ 最小。  
 

------------

 
题目要求使 $\dfrac{P^2}{S}$ 尽量小，于是问题转换成了
### 在已有边中选择两组差最小的边组成矩形

### 注意：这里的“差最小”是指 $\dfrac{b}{a}$ 最接近 $1$ ，即两数最接近。

## 思路

因为 $a_i \leq 10000$ 所以对每一条输入的边进行桶排序。

然后用 **$O(n)$** 时间对长度相邻的两个边长求比值 $\dfrac{a_i}{a_{i+1}}$,对每个比值取最小值，记录对应边长即为答案。

### 几个易错点：
1. 每次对 $a$ 数组清零。

2. 关键变量要用 `double`,比值多为小数

3. 保证边的条数大于等于 $2$ 才进行尝试

4. 若同一长度边数大于 $4$ 直接输出，因为正方形必然是最优解

5. 每次 $ans$ 一开始设为无穷大
 
## 代码 

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')	f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar(); 
	}
	return x*f;
}
int t,n,ma,mi,o;
bool f;
int a[10001];
struct node{
	int now,la;
	double ans;
}b;//记录答案
int main(){
	t=read();
	while(t--){
		n=read();
		ma=-1;//桶中出现最小位置
		mi=999999999;//最大位置
		b.ans=999999999;//ans记为无穷大
		memset(a,0,sizeof(a));//桶清零
		o=0;
		f=0;
		for(register int i=1;i<=n;i++){
			int x=read();
			if(mi>x) mi=x;
			if(ma<x) ma=x; //更新
			++a[x];
		}
		for(register int i=mi;i<=ma;i++){
			if(a[i]>=4){//若可以构成正方形直接输出
				printf("%d %d %d %d\n",i,i,i,i);
				f=1;//已找到答案
				break; 
			}
			if(a[i]>=2){//边数大于两条可尝试
				if(!o)	o=i;//第一次发现可用边，记下与后面一条比较
				else{
					if(i*1.00000000/o<b.ans){//答案可更新
						b.la=o;//宽
						b.now=i;//长
						b.ans=b.now*1.00000000/b.la;//比值
					}
					o=i;//更新前一条边
				}
			}
		}
		if(!f){
			printf("%d %d %d %d\n",b.la,b.la,b.now,b.now);
		}
	}
	return 0;
} 
```

 
 
 
 
 
 

---

## 作者：Apocalypsis (赞：1)

$a$和$b$是组成矩形的两条边长，且$a>b>0$，则有

$\frac{P^2}{S}=\frac{(2a+2b)^2}{a*b}=4(\frac{a}{b}+\frac{1}{\frac{a}{b}})+8$

根据对勾函数性质可知，$\frac{a}{b}$越接近1，则有$\frac{P^2}{S}$的值越小

当有某数值出现的次数大于等于4时，即存在$a,b$，使得$a=b$，

即有$\frac{P^2}{S}$的最小值等于16，此时可以直接保存答案退出循环

```
#include<bits/stdc++.h>
using namespace std;
int T,n,t[10001],cnt,a,a1,a2;
double c,minn,sc[20001];
int main(){
    scanf("%d",&T);
    while(T--){
        memset(t,0,sizeof t);
        a1=0;a2=0;cnt=0;minn=1000000;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a);
            t[a]++;
            if(t[a]==2) sc[++cnt]=a;
            if(t[a]==4) sc[++cnt]=a;
        }
        sort(sc+1,sc+cnt+1);
        for(int i=1;i<cnt;i++){
            if(sc[i]==sc[i+1]){
                a1=sc[i];a2=sc[i];
                break;
            }
            c=(double)(sc[i+1]/sc[i]);
            if(c<minn) a1=sc[i],a2=sc[i+1],minn=c;
        }
        printf("%d %d %d %d\n",a1,a1,a2,a2);
    }
}
```

---

## 作者：LXH5514 (赞：1)

## CF1027C

### 题目大意

多测：给你n个长度为 $a_i$ 的木棍，然后选出4根组成长方形，使得$\frac{S}{P^2}$ 最小，（$4 \le n \le 1e6$，$1 \le a_i \le 1e4$）。

### 思路

首先很明显，我们要让 $\frac{S}{P^2}$ 最小，如果要将每一个 s 和 p 都求出来，未必太麻烦，而且没有规律性，那么我们要寻找两条边的关系，因此

解 ~~数学习惯，嘿嘿~~

设长方形的长和宽为 a ，b(a>b)。

$P=2（a+b）,S=a* b$ 。

$\frac{S}{P^2} = \frac{a*b}{4*(a+b)^2}$

最终化简可得$\frac{S}{p^2}=\frac{1}{4}*(\frac{a}{b}+\frac{b}{a}+1/2)$。

设$\frac{b}{a}=t$。

那么$\frac{S}{p^2}=1/8+\frac{1}{4}*(\frac{1}{t}+t)$，由于 $0<t \le 1$，因此 $\frac{S}{p^2}$ ，在这个区间内单调递增，因此我们要找最大 $\frac{S}{p^2}$ 就找最大的 $b/a$ 即可。

一开始我看到数据范围$1 \le a_i \le 1e4$ ，就想到桶排，然后 $O(1e8)$ 暴力就可，后来为了写的方便就先将数据sort一下，将每个数去重，同时统计个数，，数值的个数只有 1000 ，因此时间复杂度还是 $O（1e8）$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+f*(c-'0'),c=getchar();
	return x;
}
const int MAXN=1e6+10;
int a[MAXN],b[MAXN],bb[MAXN];
int n,t,maxn=-1;
int ans1,ans2;
double ans=1e9;
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++)
		a[i]=read();
		sort(a+1,a+1+n);
		int p=0;
		for(int i=1;i<=n;i++)
		if(a[i]!=a[i-1])b[++p]++,bb[p]=a[i];//去重 ,并统计个数 
		else b[p]++;
		for(int i=1;i<=p;i++)
		{
			if(b[i]>=4)
			{
				ans1=bb[i];
				ans2=bb[i];//特判正方形 
				break;
			}
			if(b[i]<2)continue;//如果这个数值的木棍不足2个，那么不可能构成长方形 
			for(int j=i+1;j<=p;j++)
			{
				if(b[j]>=2)
				{
					if((double)bb[j]/bb[i]<ans)
					{
						ans=(double)bb[j]/bb[i];
						ans1=bb[i];
						ans2=bb[j];
						break; //在分子确定的情况下，分母越小越好，那么找到一个就可以跳出了 
					}
				}
			}
		}
		printf("%d %d %d %d\n",ans1,ans1,ans2,ans2);
		for(int i=1;i<=p;i++)
		b[i]=0;
		ans=1e9; 
	}
return 0;
}

```



---

## 作者：PanH (赞：0)

思路和别人稍稍有点不同，但我觉得也比较好懂。

题目要求最小的 $\dfrac{4(a+b)^2}{ab}$ ，可以展开再去掉常数项，即要求最小化 $\dfrac{a^2+b^2}{ab}$ ,减去一个常数 $2$ 可以转化为求最小的 $\dfrac{(a-b)^2}{ab}$ 。

这样问题就很简单了，枚举每一个合法的 $a$ ，找到一个最大的小于 $a$ 的合法 $b$ ,此时分子一定最小，分母一定最大，保证了柿子的值最小。

时间复杂度 $O(n\log n)$。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int T,n,t[N],a[N];
template<class T>inline void read(T &x)
{
	x=0;int f=0;char ch=getchar();
	while(!isdigit(ch))	f=ch=='-',ch=getchar();
	while(isdigit(ch))	x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=f?-x:x;
}
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		for(int i=1;i<=n;i++)
			read(a[i]),t[a[i]]++;	
		sort(a+1,a+n+1);
		double ans=2e9;
		int res[4],pre=0;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==a[i-1])	continue;
			if(t[a[i]]>=4)	{ans=16,res[0]=res[1]=res[2]=res[3]=a[i];break;}
			else if(t[a[i]]>=2)
			{
				if(!pre)	{pre=a[i];continue;}
				if(ans>4.0*(a[i]+pre)*(a[i]+pre)/(1.0*a[i]*pre))
					res[0]=res[1]=a[i],res[2]=res[3]=pre,ans=4.0*(a[i]+pre)*(a[i]+pre)/(1.0*a[i]*pre);
				pre=a[i];
			}
		}
		for(int i=1;i<=n;i++)	t[a[i]]--;
		printf("%d %d %d %d\n",res[0],res[1],res[2],res[3]);
	}
	return 0;
}
```


---

## 作者：Mickey_snow (赞：0)

[CF1027C](http://codeforces.com/problemset/problem/1027/C) _Minimum Value Rectangle_ ：贪心。

题目大意：给你 $n$ ($4 \leq n \leq 10^6$) 根木棍，不允许拼接或折断，选择四根组成矩形，求所有合法矩形中周长平方与面积比最小的一个，输出拼成这个矩形的四根木棍。具体的数据范围见英文题面。

这题巧妙至极，看数据范围就很容易想到这题很有可能是一个贪心。

我们记一个矩形周长为 $C$ ，面积为 $S$ . 记 $P = \frac{C^2}{S}$ .

　

正式贪心之前，先证明一个引理：

#### 引理：$\forall$ 两个合法矩形 $A$ 和 $B$ ，如果它们拥有同等的宽，且 $A$ 的长小于 $B$ 的长，那么 $P_A \leq P_B$ .

证明：

假设矩形 $A,B$ 宽为 $a$ ,$A$ 的长为 $b$ ,$B$ 的长为 $b+b_1$ .且 $a,b,b_1 \in R^+$ . 则需证明

 $$\forall a,b,b_1. P_A - P_B \ge 0$$ 

代入数据，也就是

 $$ \frac{[2a+2(b+b_1)]^2}{ab+ab_1} - \frac{(2a+2b)^2}{ab} \ge 0$$

显而易见，分母大于0，乘上 $ab(ab+ab_1)$ 不会改变这个不等式.

$$4a^3b+4ab^3+4abb_1^2+8ab^2b_1+8a^2b^2+8a^2bb_1-4a^3b-4ab^3-8a^2b^2-4a^3b_1-4ab^2b_1-8a^2bb_1 \ge 0$$  

整理得

$$4abb_1^2 + 4ab^2b_1 - 4a^3b_1 \ge 0$$  

没有了同类项，式子的正确性变得不那么显然了，我们一项项分析。$4abb_1^2$  一定大于0，而且可以判断出 $4ab^2b_1 - 4a^3b_1 \ge 0$ . 理由如下：

因式分解得 

$$4ab^2b_1 - 4a^3b_1 = 4ab_1(b^{2} - a^{2}) = 4ab_1(a+b)(b-a)$$  

$\because 4ab_1 , (a+b) \ge 0 $，由于 $b$ 为长，$\therefore b-a \ge 0$ .  $\therefore 4ab^2b_1 - 4a^3b_1 \ge 0$ .

$\therefore P_A \leq P_B$ .

证毕。

　

#### 实现

由引理可知，$\forall$ 矩形的宽$a$ ，能使这个矩形 $P$ 值最小的必定是一个最小的 $b$ 满足 $b \ge a$.

将木棍配对，假设最终可用的木棍为 $m$ ,每一对木棍的长度分别为 $a_i$ ,那么我们只用扫一遍，找到一组 $P$ 值最小的 $a_i$ 和 $a_{i+1}$ 即可。

由于任何一个木棍长度都不会超过 $10^4$ ,所以我们可以开一个一维数组，读入的同时桶排序，如果发现超过两个就放一对木棍进入 $b$ 数组，如果超过四个就再放一对。这样就自动过滤掉了多余的无用木棍。完成这一步后需要对 $b$ 数组进行排序。

这一步结束后，我们应该有一个数组 $b$ ,$b_i$ 代表第 $i$ 对木棍长度。前面提到过，$b$ 中元素个数为 $m$.

最后就扫一遍就完了，按照公式 $O(1)$ 算出 $P$ 值，$O(M)$ 结束整个过程。

对于每一组数据，时间复杂度为 $O(N\log{N}+M)$.

代码如下：

```c#
using System;
using System.Collections;

namespace CF1027C 
{
	class Program 
	{
		public class Global {
			public static int[] len;
			public static ArrayList arr;
			public static void RestoreAll() {
				arr = null;len = null;
				len = new int[10005];arr = new ArrayList { };
			}
		}

		static void Main(string[] args) 
		{
			string[] inp;
			int totCases = Convert.ToInt32(Console.ReadLine()), totNums, a, b;
			decimal _minVal;

			while(totCases-->0)
			{
				totNums = Convert.ToInt32(Console.ReadLine());
				Global.RestoreAll();inp = Console.ReadLine().Split(' ');

				for(int i = 0;i < totNums;i++) {
					a = Convert.ToInt32(inp[i]);
					Global.len[a]++;
					if(Global.len[a] == 2 || Global.len[a] == 4)
						Global.arr.Add(a);
				}Global.arr.Sort();

				a = (int)Global.arr[0];b = (int)Global.arr[1];_minVal = Solve(1);
				for(int i = 2;i < Global.arr.Count;i++)
					if(Solve(i) < _minVal) {
						_minVal = Solve(i);
						a = (int)Global.arr[i - 1];b = (int)Global.arr[i];
					}

				Console.WriteLine(a.ToString() + " " + a.ToString() + " " + b.ToString() + " " + b.ToString());
			}

		}

		static decimal Solve(int pos) {
			return ((decimal)(((int)Global.arr[pos] + (int)Global.arr[pos - 1]) << 1) * (((int)Global.arr[pos] + (int)Global.arr[pos - 1]) << 1)) / (decimal)((int)Global.arr[pos] * (int)Global.arr[pos - 1]);
		}
	}
}
```

---

