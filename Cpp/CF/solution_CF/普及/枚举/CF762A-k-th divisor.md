# k-th divisor

## 题目描述

你被给了两个整数$n$ 和$k$ 。找到$n$ 的第$k$ 小因子，或者告知其不存在。

任意一个可以除$n$ 而没有余数的自然数都是$n$ 的因子。

## 说明/提示

在第一个样例中，数字$4$ 有三个因子：$1$ ，$2$ 和$4$ 。第二小的为$2$ 。

在第二个样例中，数字$5$ 仅有两个因子$1$ 和$5$ 。第三个因子是不存在的，因此答案是-1。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
4 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
12 5
```

### 输出

```
6
```

# 题解

## 作者：伟大的王夫子 (赞：6)

如果想要更好的体验，可以到[我的博客](https://www.luogu.org/blog/I-AK-IOI/)去看

整体的算法比较暴力，就是先把$n$的约数求出，然后在排个序，再输出第$k$个

时间复杂度$O(\sqrt n)$

说具体点，就是枚举$i \in [1, \sqrt n]$，如果$i |n$, 则$\dfrac{n}{i} | n$ ，然后加入即可

注意事项
	
   - 有一个数据点是 $1 \,\,\,2$。刚开始就坑在这个点上，因为我刚开始加约数加的是$1$和$n$，但是因为$n=1$,所以多加了一个$1$。那样结果肯定会错，本来答案是$-1$,我的程序输出了$1$
    - 必须要开long long!因为n很大，用int是完全存不下的。否则您就可以欢快的WA了
    - 如果第一次做错了，要重新提交，但是代码没改，必须得随便加一点注释否则您会被CF给坑掉的
    
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
long long k, p[10000010], cnt;
int main() {
	cin >> n >> k;
	p[1] = 1;
	cnt = 1;
	if (n != 1) p[2] = n, cnt = 2;//特判1
	for (register long long i = 2; i <= sqrt(n); ++i) {
		if (n % i == 0) {
			p[++cnt] = i;
			if (i != n / i) p[++cnt] = n / i;
		}
	}//筛出他的约数
	sort(p + 1, p + cnt + 1);
	if (k <= cnt) cout << p[k];
	else puts("-1");//dssdsds
} 
```
	

---

## 作者：Khassar (赞：3)

不想写题的我，特来水一篇题解。

CFA题嘛，一般都是水题。水题怎么做呢？ — 枚举啊！

很简单的想法就是枚举$1$到$n$的所有数，看它是不是$n$的因数，累加计数器到$k$的时候输出这个因数。

但是$1\leq n\leq 10^{15}$，oh~~，随便还有$1\leq k\leq 10^9$说明基于O(k)的枚举也不怎么行。

这可怎么办呢？显然的一个事实是，对于$x*y=n$（$x\leq y$）有$x\leq \sqrt n$。

$\sqrt n$嘛，大概是$10^7$满能接受的，但是$k$也可能超过$\sqrt n$，那后面就要基于$k$枚举了吗？显然也不用，我们可以把$x$都存下来反推出$y$，枚举x时从大到小枚举就能使$y$是从小到大的了。两个一拼是$2\cdot \sqrt n$ 就这样过了。~~由此可见很有可能会输出-1。~~

当然还要特判一下$x*x=n$的情况，这样反推出的$y$还是$x$，不是一个新因子。

最后在贴一下没什么用还吃藕的代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<string>
#include<queue>
#include<map>
#include<vector>
#include<ctime>
#include<set>

#define int long long
#define R register
#define IL inline
#define Rf(a,b,c) for(R int (a)=(b);(a)<=(c);++(a))
#define Tf(a,b,c) for(R int (a)=(b);(a)>=(c);--(a))
#define MP make_pair
#define PA pair<int,int>
#define MES(a,b) memset((a),(b),sizeof((a)))
#define MEC(a,b) memcpy((a),(b),sizeof((b)))
#define D double

using namespace std;

const int N=1e7;

int n,c[N],tot,k;


IL int read() {
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=(ch-'0');ch=getchar();}
    return x*f;
}
IL void write(int x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}

signed main()
{
	n=read();k=read();
	for(R int i=1;i*i<=n;++i) if(n%i==0) {
		c[++tot]=i;
		k--;
		if(!k) {
			write(i);
			return 0;
		}
	}
	if(c[tot]*c[tot]==n) tot--;//特判
	Tf(i,tot,1) {
		k--;
		if(!k) {
			write(n/c[i]);
			return 0;	
		}
	}
	write(-1);

    return 0;
}

```

---

## 作者：infinities (赞：2)

个人觉得之前的dalao们还是太强了，对待一道枚举的水题没必要写那么难懂的代码。

其实要想会写此题，你首先要了解一样东西，那就是一个数(以下简称n)如果已经有了一个因数，那么在$sqrt(n)$的另一边，还会有一个因数。知道了这个，你不仅可以做这道题，还可以暴力跑跑[这道题](https://www.luogu.com.cn/problemnew/show/P3383)（说是线性筛其实可以暴力AC）。

还有一件事，C++乘法运算和sqrt运算时间浪费比较大，所以要提前算好，以免被某些凉心出题人卡掉

所以呢，我们写暴力的第一步肯定要有一个这样的枚举

```cpp
int t=sqrt(n);
for(signed i=1;i<=t;i++)if(n%i==0)q[++ans]=i;
```

既然题目要求是从小到大枚举，那么一部分人可能会继续这么写：

```cpp
for(signed i=1;i<=t;i++)if(n%i==0)q[++ans]=n/i;
```

慢着，这么写是错的，因为要进行一次除法，所以要从大向小枚举

然后，你会发现，这么写也不能AC

Q：为什么哪？

#### A：Great！恭喜您找到了本题最大坑点！

由于出题人不想放跑错解，所以ta加了一些n是完全平方数时的情况，这就要求我们做一个特判（烦人的分析环节总算结束了）。

最后，放——

code(12 lines):
```cpp
#include<bits/stdc++.h>
#define signed long long
const int MAXN=1e7*3+10;
signed n,k,q[MAXN],ans;
int main(){
    std::cin>>n>>k;
    signed t=std::sqrt(n);
    for(signed i=1;i<=t;i++)if(n%i==0)q[++ans]=i;
    for(signed i=t-(t*t==n)/*这里是一个bool类型的表达式，就是一个减便写法，当t*t==n时返回1，反之亦然*/;i>=1;i--)if(n%i==0)q[++ans]=n/i;
    if(ans<k)std::cout<<-1;else
    std::cout<<q[k];//其余的具体内容上面都讲了，自己看吧
}
```


---

## 作者：Kevin_Zhen (赞：1)

题目链接 [$\mathfrak{CF762A}$](https://www.luogu.com.cn/problem/CF762A)。

### 题目大意
求整数 $n$ 的第 $k$ 小因数 $(1\le n\le 10^{15},1\le k\le 10^9)$。

### 变量介绍
输入的两个整数 $\operatorname{n}$ 和 $\operatorname{k}$，注意要开 $\operatorname{long\ long}$。  
保存求出的因数：$\operatorname{ans}$。
```cpp
typedef long long ll;

ll n, k;
vector <ll> ans;
```


### 思路
很容易想到暴力枚举，从 $1$ 到 $n$ 找出 $n$ 的所有因数，输出第 $k$ 小。因为此题 $n$ 可以到 $10^{15}$，此算法超时。

运用类似于**判断质数时的试除法**的思想，我们只需找出 $1-\left\lfloor\sqrt{n}\right\rfloor$ 中的 $n$ 的因数即可，其余的因数可以通过 $n$ 除以已找出的因数得到。

此算法时间复杂度 $O(\sqrt{n})$。具体操作次数在 $10^7$ 级别，$\operatorname{2s}$ 的时限没问题。

注意，如果 $n$ 为完全平方数，$n$ 的因数 $\sqrt{n}$ 只需记录一次，所以需要特判。

具体代码实现如下。
```cpp
if (n % i) continue;
ans.push_back(i);
if (i * i != n) ans.push_back(n / i);
```

### AC CODE
```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n, k;
vector <ll> ans;

int main() {
	scanf("%lld%lld", &n, &k);
	for (ll i = 1; i * i <= n; ++i) {
		if (n % i) continue;
		ans.push_back(i);
		if (i * i != n) ans.push_back(n / i);
	}
	if (ans.size() < k) { printf("-1"); return 0; }
	sort(ans.begin(), ans.end());
	printf("%lld", ans[k - 1]);
	return 0;
}
```

### 感谢观赏！

---

## 作者：αnonymous (赞：1)

这题只需几个小小的优化便可AC:

1、因为n的因数都是成对出现（$a*b=n$，此处a和b即是n的因数）,假设$a>b$，则$a$越小，$b$越大。当$a=b$时，$a=b=\sqrt{n}$

所以最多有$2*\sqrt{n}$个因数，特判$k>2*\sqrt{n}$时，无解

2、枚举$1-\sqrt{n}$中n的因数（即较小的因数）,求出个数为$pn$,因数的个数$all$就是$pn*2$。如果$n$是完全平方数,$all-=1$

3、若$k\leqslant pn$，则直接调取;若$k>all$，则无解；否则$k$在较大的因数中，可通过$n$除以对应较小的因数求出，不需要再求出个列表。
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
unsigned long long n,k,pri[30000010],pn,all,i;
int main(){
	scanf("%lld%lld",&n,&k);
	if(k>2*sqrt(n))//特判：k是否在粗略的范围内
		cout<<"-1"<<endl;
	else{
		for(i=1;i*i<=n;++i)
			if(n%i==0)//枚举较小的因数
				pri[++pn]=i;
		all=pn*2;//总因数个数
		if(pri[pn]*pri[pn]==n)//若n为完全平方数
			all--;
		if(k<=pn)
			cout<<pri[k]<<endl;
		else if(k>all)
			cout<<"-1"<<endl;
		else
			cout<<n/pri[all-k+1]<<endl;
	}
	return 0;
}
```


---

## 作者：crh1272336175 (赞：0)

一个很暴力的数论题

因为数据范围n很大，所以我们只能考虑sqrt(n)的复杂度，于是我们需要用一个vector存下n所有的因子，不然大于sqrt(n)的因子我们无法统计

于是乎，简明的思路出来了:枚举1~sqrt(n)，把n的因子储存下来，然后排个序,
如果因子数量<k，输出-1；否则输出第k个因子

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,k;
vector<ll> a; 
int main()
{
	scanf("%lld%lld",&n,&k);
	for(ll i=1; i*i<=n; i++)
		if(n%i==0) 
		{
			a.push_back(i);
			if(i*i!=n) a.push_back(n/i); 
		}
	if(a.size()<k) puts("-1");
	else 
	{
		sort(a.begin(),a.end());
		printf("%lld\n",a[k-1]);
	}
	return 0;
} 
```


---

## 作者：leoair (赞：0)

# k-th divisor

题目大意:给定整数$n$和$k$，求$n$的第$k$大约数。

这题不就是个枚举么？从$1$到$n$循环找第$k$个约数。**你看数据范围了吗？**$1 \leq n \leq 10^{15}, k \leq 10^{9}$**~~(你号还要吗？)~~**

看来只能试试其他方法了。~~众所周知，~~因为约数是**成对出现**的(除$n$是完全平方数时的$\sqrt{n}$ )，所以我们只需要从$1$枚举到$\sqrt{n}$就行了，然后再特判一下$n$是否是**完全平方数**。

接下来看看实现:

### Code:

```cpp
#include <bits/stdc++.h>
#define REP(i, a, b) for (long long i = a; i <= b; ++i)
#define ll long long
#define N 10000010										//1e7+10
using namespace std;

ll n, m, k, a[N];

inline ll read(){										//快读 
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') w *= -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

inline void work(){
	n = read(), k = read();
	REP(i, 1, sqrt(n))
		if (n % i == 0){
			a[++m] = i;									//记录约数 
			k--;										//一边操作一边减 
			if (!k){									//如果已经是第k个约数了 
				printf("%lld\n", i);					//输出 
				exit(0);								//等同于main函数里的retrun 0 
			}
		}
	if (a[m] * a[m] == n) m--;							//特判n是否是完全平方数
	if (k > m) puts("-1");								//如果没有第k个约数，就输出-1 
	else printf("%lld\n", n / a[m - k + 1]);			//否则输出n除以这个和它成对出现的数的商
}

int main(){
	work();
	return 0;
}
```



---

## 作者：文·和 (赞：0)

~~洛谷网校讲得题马上来水题解~~
我们得弄清楚，只需要把1到$\sqrt n$扫一遍就能弄清楚n有哪些因数。

问题来了：怎么把因数直接按小到大排好？时间复杂度只允许我们用O(1)方法存储每个因子。

**双端队列**了解一下~~不会问度娘~~，我们需要**倒序**从$\sqrt n$扫描到1，每次扫到因数就将**大**因数从后面加入队列而将**小**因数从前端插入，这样扫描完就可以将所有因数排好，又因为双端队列可以**直接访问**，最后输出答案时也可以**直接输出**。

而直接求$\sqrt n$，就用自带的**向下取整**就可以了。

最后一点 **不开LL见祖宗鸭！**

根据思路打出代码 ~~好短~~

```
#include <bits/stdc++.h>
using namespace std;
long long n,k,i;  //变量命名
deque<long long> q;   //双端队列
int main(){
cin>>n>>k;    //输入
for(i=floor(sqrt(n));i>=1;i--)   //从根号n扫描到1
if(n%i==0){      //不要忘记判断整除
if(i*i!=n) q.push_front(i),q.push_back(n/i);   //如果两个因数不同就都塞进队列
else q.push_front(i);   //两个因数相同时只可能是一开始队空，前后都可以
}
if(q.size()<k) cout<<-1;  //如果没有k个因数则无解
else cout<<q[k-1];   //记住双端队列数组从0开始，所以要k-1
return 0;
}
```

谢谢大家！

---

## 作者：andyli (赞：0)

注意到约数总是成对出现：  
若$d$是$n$的约数，则$\frac{n}{d}$也是$n$的约数。  
在一对约数中，必有一个不大于$\sqrt{n}$，另一个不小于$\sqrt{n}$，因此枚举$1..\sqrt{n}$就能求出$n$的所有约数。  
代码如下（[快读模板](https://andyli.blog.luogu.org/read-template)）：  
```cpp
const int maxn = sqrt(10000000) + 5;

LL divisors[maxn];
int main()
{
    LL n, k;
    io.read(n, k);
    int m = sqrt(n), cnt = 0;
    for (int i = 1; i <= m; i++)
        if (n % i == 0)
            divisors[++cnt] = i;
    if (1LL * m * m == n)
        cnt--;
    for (int i = m; i >= 1; i--)
        if (n % i == 0)
            divisors[++cnt] = n / i;
    writeln(cnt < k ? -1 : divisors[k]);
    return 0;
}
```

---

## 作者：Jelly_Goat (赞：0)

emmm...不能说是水题吧...小金羊以为考的是STL（手动滑稽）...  
行，这个题说让分解因数（**不一定非得质因数**）。  
我们考虑到有**第k个数有可能有$x\cdot x=n$的毒瘤**情况，  
并且题目明确要求说**从小到大**  
——set<unsigned long long int>帮助你轻松水过去。  
emmm....题目范围说是
$$1\leq n\leq 10^{15},1\leq k\leq 10^9$$
  很明显朴素算法炸了！  
#### 我们需要知道$x\cdot y=n$的时候$x\leq\sqrt{n}$，两侧同时平方，得到$x^2\leq n$。  
省下一大笔时间。
去重和排序、排名的工作留给set，我们只需要往里面插入元素就好了。  
再说一下setのrank（第k个）的原理:  
set自建一颗R-B T(Red-Black Tree)，是平衡二叉搜索树，二叉搜索树嘛，rank是其基本算法原理。平衡让其效率更高，让两侧子树尽量平衡元素个数，避免长链的出现。  
最后本题解还要说明set<ulli>iterator（迭代器）的本题用法：  
迭代器就是一个集合形式的指针，指向特定容器的某一元素。  
但是迭代器不能像指针一样＋－×÷，c++ 11的标准好像只支持++或者--。
如果k大于set内部元素个数，就输出-1。如果小于等于，就把iterator移动到  
指向k-th个元素上就行。  
Code:
```cpp
#include <iostream>
#include <cstdio>
#include <set>//set库

using namespace std;
typedef unsigned long long int ulli;//毒瘤数据

set<ulli>divisors;
set<ulli>::iterator iter;
void divide(ulli num)
{
	for (register ulli i=1;i*i<=num;i++)
	{
		if (num%i==0)
		{
			divisors.insert(i);//把x压入set
			divisors.insert(num/i);//把另一半也压进去
		}
	}
}

int main()
{
	ulli num,k;
	cin>>num>>k;
	divide(num);
	if (k>divisors.size())//范围超出
	{
		printf("-1");
	}
	else
	{
		iter=divisors.begin();//使其指向容器的第一个元素
		for (register ulli i=1;i<=k-1;i++,iter++/*仅能使用++*/)
		{;}//挪动器（手动滑稽）
		cout<<*iter;//注意输出的时候要加上*
	}
	return 0;
}
```
~~实在是看不懂楼上的码风，就发一篇题解方便大家理解~~。  
~~不会告诉你们一开始输出%d来着~~  
最多一个点177ms,836kB,能接受的范围之内。

---

