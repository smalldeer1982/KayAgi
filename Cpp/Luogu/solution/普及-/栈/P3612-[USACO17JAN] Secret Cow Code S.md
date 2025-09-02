# [USACO17JAN] Secret Cow Code S

## 题目描述

奶牛们正在实验秘密代码，并设计了一种方法用于生成无限长度的字符串，作为他们代码的一部分。

给定一个字符串 $s$，令 $F(s)$ 为 $s$ 后接 $s$ 向右“旋转”一个字符的结果（在右旋转中，$s$ 的最后一个字符旋转并成为新的第一个字符）。给定初始字符串 $s$，奶牛们通过重复应用 $F$ 来构建他们的无限长度代码字符串；因此每一步都会使当前字符串的长度翻倍。

给定初始字符串和一个索引 $N$，请帮助奶牛计算无限代码字符串中第 $N$ 个位置的字符。

## 说明/提示

在这个例子中，初始字符串 COW 按以下方式扩展：

COW -> COWWCO -> COWWCOOCOWWC

## 样例 #1

### 输入

```
COW 8```

### 输出

```
C```

# 题解

## 作者：issue_is_fw (赞：427)

## 前言:在这道题目卡了很久，所以我想把自己的理解说出来，希望能帮到你们。管理大大让我过吧，(●ˇ∀ˇ●)自认为表达地比一些题解要好。

先看样例

$COW->COWWCO->COWWCOOCOWWC$

我们把这三个字符串编号为$1,2,3$

现在我们要求第8位，假如我们已经知道在3串，能否逆推出在第2串中的位置呢?如果能，似乎问题就迎刃而解了,因为2逆推到1也是一个相同的子问题。

题目的古怪要求复制要先复制最后一个字符，再复制前缀，我们姑且先直接复制前缀.

$COW->COWCOW->COWCOWCOWCOW$

现在求3串的8位置，3串长L,逆推回2串即为$8-L/2$位置

但我们复制的时候是先复制最后一个字符,所以要多减一为$8-1-L/2$

特别的,如果求的n刚好是先复制原串的那个位置,特殊处理，具体看代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
long long n,num,i;
int main()
{
	//代码部分借鉴1楼 
	cin>>s>>n;
	num=s.length(); 
	while(num<n)
	{
		i=num;
		while(n>i)	i*=2;//求出当前刚好包括n位置的串长 
		i=i/2;//得到当前串的一半长 
	//	if(n==i+1)	n=i;特殊处理，假如这里n位置是i+1
	//那么经过下面这步操作后，变成了0，那我们下面对0特判 
		n-=(i+1); 
		if(n==0)	n=i;
	}
	cout<<s[n-1];
}
```


---

## 作者：pluszero (赞：118)

这道题其实很简单，通过观察我们可以发现，每一次增长增长的部分的第一位跟原部分的最后一位相同，增长部分的第二位到最后一位跟原部分的第一位到倒数第二位相同。 以样例为例：COW------->CO W W CO--------->COWWC O O COWWC。 可以发现第二次增长的第一位到第二位与第五位到第六位相同。第三次增长的第一位到第五位与第八位到第十二位相同。所以可以不断的把前面一半不用的删除掉，最后剩下原字符时输出即可。


下面是代码：

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
using namespace std;
char a[1000001];

int main()
{
    char ch;
    long long n,num=0;
    while(scanf("%c",&ch),ch!=' ')
        a[++num]=ch;
    scanf("%lld",&n);
    while(num<n)
    {
        long long i=num;
        while(n>i*2) i*=2;
        n-=(i+1);
        if(n==0) n=i;
    }
    printf("%c",a[n]);
    return 0;
}
```

---

## 作者：火车司机 (赞：84)

## 梳理题意

给定一个字符串，每次将其最后一个字符移到最前方，形成的新串接到原串后作为下一次操作的字符串

现询问第 $N$ 个位置的字符

## 简要分析

看一眼数据范围， $N<10^{18}$ ，显然不能模拟，所以我们从每一次操作入手

很明显，每一次操作过后，串的长度就会成为原先的两倍，所以可以想到以下这个算法。

------------

#### **分治**

分治，即为分而治之，顾名思义，就是把一个问题分成若干个子问题，然后对每个子问题分别处理，最后再将每个子问题的结果合并起来。

如果想对分治算法了解更多的同学，可以移步[此处](https://oi-wiki.org/basic/divide-and-conquer/#_5)

------------

#### 那么这道题目该如何分治呢

首先，为了找到第 $N$ 个字符，我们可以用一个 $t$ 变量记录在什么时候字符串长度超过 $N$ ，代码如下

```cpp
while (t < n) t <<= 1;	//位运算更快
```

通过题意可得，当第 $N$ 个字符在长度为 $t$ 的字符串的后半段时，前半段字符串中的第 $N-1-t/2$ 个字符肯定与第 $N$ 个字符相同，因为第 $N$ 个字符在前一次操作时就是有第 $N-1-t/2$ 个字符转换过来的，所以我们可以由此写出以下代码

```cpp
while (t != l) t >>= 1, n -= 1 + t;
```
但是上面这段代码离正确代码虽然接近，却又相差甚远

在原操作中，我们是将字符串的最后一个字符移到第一个后接到原串后的。倒推可得，在长度为 $t$ 的字符串中，当 $N$ 等于 $t/2+1$ 时，即第 $N$ 个字符为后半段字符串的第一个时，与之必定相同的字符位置应为 $t/2$ 或 $N-1$，因此加入这个特判后的代码如下

```cpp
while (t != l) {
	t >>= 1;
	if (t + 1 == n) n = t;
	else n -= 1 + t;
}
```

使用三目运算符也可以简写成以下代码

```cpp
while (t != l) t >>= 1, n = (t + 1 != n) ? n - 1 - t : t;
```

以上所有代码都是建立在第 $N$ 个字符在长度为 $t$ 的字符串的后半段时，当第 $N$ 个字符在长度为 $t$ 的字符串的前半段时，我们就不需要做任何操作，直接将 $t/2$ 就行了，代码如下

```cpp
while (t != l) {
	t >>= 1;
	if (n <= t) continue;
	if (t + 1 == n) n = t;
	else n -= 1 + t;
}
```

## 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
long long l, n, t;
char s[55];
int main() {
	scanf("%s%lld", s + 1, &n), l = t = strlen(s + 1);
	while (t < n) t <<= 1;
	while (t != l) t >>= 1, n = n > t ? ((t + 1 != n) ? n - 1 - t : t) : n;
	putchar(s[n]);
	return 0;
}
```

------------

最后，这里再推荐两道分治好题——>[平面最近点对（加强版）](https://www.luogu.org/problem/P1429)和[地毯填补问题](https://www.luogu.org/problem/P1228)


---

## 作者：yyyhy (赞：33)

这道题可以用到递归，来寻找第 $n$ 个字符是由原字符串中的哪个字符翻转而来的。

首先把字符串输入（为了让下标从 $1$ 开始，在前面插一个空格）：
```cpp
string in;
int len;
cin >> in;
in = ' ' + in;
len = in.length() - 1;
```
此时我们可以定义一个变量 $l$ 来储存最后一次反转前字符串的长度。

显然，$l$ 最少是 $len$。  
之后模拟变化过程，每次长度翻一倍。  
为了防止爆 `long long`，我们用除法。
```cpp
long long l;
l = len;
while (l < 1.0 * n / 2) l *= 2;
```
然后上重点：

由题意可知，当 $i=l$ 时，因为 $i$ 是最后一个，所以 $i$ 在接上来的字符串中在第一个，此时 $i$ 翻转后会变到第 $i+1$ 个，所以当 $n=l+1$ 时，$n$ 翻转前在第 $l$ 个。

$i\neq l$ 时，字符串内的第 $i$ 字符在翻转之后会翻转到 $i+l+1$ 个，即 $n=i+l+1$，所以 $i=n-l-1$。即 $n\neq l+1$ 时，第 $n$ 个字符是由第 $n-l-1$ 个字符翻转而来。

由此可以得出代码：
```cpp
char work(long long n, long long l) {
	if (n <= len) return in[n]; //长度翻到len以内就返回
	long long ll = l, nn = n - l - 1; //nn即i
	if (!nn) nn = ll;
	while (ll >= nn) ll /= 2; //求出下一层的l
	return work(nn, ll);
}
```
最后附上完整代码：
```cpp
#include <iostream>
using namespace std;

string in;
int len;

char work(long long n, long long l) {
	if (n <= len) return in[n];
	long long ll = l, nn = n - l - 1;
	if (!nn) nn = ll;
	while (ll >= nn) ll /= 2;
	return work(nn, ll);
}

long long n, l;

int main(void) {
	cin >> in;
	in = ' ' + in;
	len = in.length() - 1;
	cin >> n;
	l = len;
	while (l < 1.0 * n / 2) l *= 2;
	cout << work(n, l) << endl;
	
	return 0;
}
```
Updated on 2024·10·29 增加 $\LaTeX$ 使用。  
Updated on 2024·12·9 使符合规范。

---

## 作者：Hongse_Fox (赞：23)

[题目链接](https://www.luogu.org/problem/P3612)

（拿到题目的众多第一件事之一就是看数据范围

1e18 如此大的数就连平时比较好看的线性算法都跑不过去

那我们就必须用一些 玄学 优秀的方法搞一个O(log n)或者$O(\sqrt n)$的复杂度


我们先考虑一下正向思维

如果光看题目样例模拟一遍还是lou得住的
但是如果数据大那么一丢丢，比如CGYAKIOI的第6666666位

如果正着去思考的话，就不一定可以lou得住了

因为如果正向思考的话我们需要搞出每一个位置的字符，$O(n)$过1e18，想想都不可能


但其实在正向思考的时候，我们跑了很多毫不相干的点，但是由于不确定目标位置是从谁那里推过去的，因此我们不可避免地要把每个位置都求出来，剪掉那些无用点也就成为我们的复杂度瓶颈。

------------

在毫无头绪的情况下，我们不妨再重新审视一遍样例。

我们思考：

第八个位置上的C是通过第五个位置上的C搞过来的，而第五个C又是从第一个C那里搞过来的

那么我们就可以反过来想，第八个位置是从第五个位置搞过来的，而第五个位置又是从第一个位置搞过来的，而第一个位置我知道，那玩意儿是C，所以第八位是C

想到这里，我们就可以发现其实反着想比正着想要好得多，因为反着想只需要考虑目标位置上的字母，那么那些一点血缘关系都木有的位置就可以鸟都不鸟了

而目标位置的形成最多也是log级别的，这样子跑一遍就可以lou住了


因此我们可以想象到要从第n个位置往前推，如果可以找到那么一种规律使其可以快速从后一个位置推到前面的位置，那么这道题也就可以迎刃而解了



------------


不妨设原序列长度为k，那么对于第n个位置，我们不难发现它的前一个位置只有两种可能：

1、当n-1等于k*2^x(x为非负整数)，那么n的上一个位置必然是n-1

2、当n-1不满足上述情况，那么n的上一个位置是n-2^x(x为使n-k*2^x>=0的最大负整数)

如果用代码实现就是这个样子：
```cpp
if(n==length*m[help]+1) n-=1;	//如果是在头头的情况就减减 
else n-=length*m[help]+1;		//否则就把它往左边搞 
```

每次求x也是一个很让人 ~~dt~~ 困惑的地方

我们先假设当前位置刚好不在2^n*k次方这种刁钻的地方

那么必然会有 k*2^x < n < k*2^x+1

如果两边同除一个k就会有2^x<n/k<x^x+1

这个玩意儿应该不难求吧

用代码实现就是：
```cpp
unsigned long long k=n/length;
unsigned long long help=0;
while(k){
	help++;
   k>>=1;
}
```
那么对于当前位置就是那么刁钻的情况，我们经过样例模拟可以发现这个 dt 令人烦躁的东西恰好等于按照上面那种情况求出的答案再减一



------------


于是实现起来也就很方便了
```cpp
#include<cstdio>
#include<cstring>
using namespace std;
char s[45],ch;
int length;	//原来字符串的长度 
unsigned long long n;
unsigned long long m[65]={0,1};
int main(){
    for(register int i=2;i<=64;i++) m[i]=m[i-1]<<1;	//此处可以事先把2的n次幂储存起来，方便后面使用 
    ch=getchar();
    while(ch>='A' && ch<='Z'){	//不停读入字母 
        s[++length]=ch;
        ch=getchar();
    }
    scanf("%llu",&n);
    if(length==1){	//如果字符串长度只有一，那就可以不加思考地输出唯一的字母 
        printf("%c",s[1]);
        return 0;
    }
    while(n>length){//当推到当前状态的位置n还不在原字符串的长度之内，那就继续推下去吧 
        unsigned long long k=n/length;
        unsigned long long help=0;
        while(k){
            help++;
            k>>=1;
        }								//这一坨都是用来求help使得2^help<=n/k && 2^help+1>n/k 
        if(n==m[help]*length) help-=1;	//如果刚好在边界的话，那就help--
        if(n==length*m[help]+1) n-=1;	//如果是在头头的情况就减减 
        else n-=length*m[help]+1;		//否则就把它往左边搞 
    }
    printf("%c",s[n]);					//输出 
    return 0;
}
```
其实如果一开始就可以敏锐地感觉到要倒着推的话，这道题是可以秒切的（当然我功力不足，秒切什么的还是不可能的

所以还是推荐大家平时一定要多刷一些题目，越毒瘤的就题目越要搞懂，而且一定要写做题记录，这样可以在以后的比赛中轻松提取模型+轻松切题

Finally，谢谢观看

---

## 作者：Malixin1234 (赞：21)

[题目链接](https://www.luogu.com.cn/problem/P3612)   

题目很好懂，就是对于任意一个字符串s，将它的最后一个字符  s[s.length()-1]  继续拼接到原字符串后，再把原字符串的  s[0]  到  s[s.length()-2]  拼接到自己的后面，形成一个新字符串。  
eg.   COW    
     COW  WCO  
     COWWCO OCOWWC   
因为数据范围是  N≤10^18  ，太大，所以直接模拟全部的字符串会爆空间，只能得到  40  分。   
那么，不难想出，题目要我们给出的一个字符，那我们就只求这一个字符就可以了。
对于一个长度为 n 的字符串：
### 1,2,3,4,5，···n。（这个表示的是编号）
如果对它进行一次操作，就会变成：
### 1,2,3,4,5,···，n,n+1,n+2···2*n.
  s[n]==s[n+1]  ,  s[1]  到  s[n-1]  依次与     s[n+2]  到  s[2*n]  相等。
如果我们要求一个规模为  2*n  的问题，根据上面的对应相等原则，我们就可以把它转换成一个求规模为 n 的问题了。
因此，对于我们要求的第 k 位置上的字符，都只有两种情况：
### （1） k  位于第  n+1  的位置上，那么我们就可以把它转换成一个求 k-1 位置上的字符的问题，因为 s[k] 与 s[k-1] 一定相等。
### （2）  k 不位于第 n+1 的位置上，而位于第   n+2 到第 2*n 的位置上的一个。那么如果我们要让 n+2 与 1 相等的话，就要把 n+2 减去 n ，再减去一个 1 .考虑一下 n 为多少呢？  n 就是 s.length()*2^x （ x 的取值要使 n 为小于 k 的最大值），因为每次操作都会增加 n 的长度，这种关系就是 2 ^ x 的函数关系，再乘以字符串长度，就是 n 的大小了。
这样问题就解决了，当我们要求的k不断缩小直到     k<s.length() 时，就可以直接输出了。
##### 注意：在上文中我用的是 k ，在实际代码中我用的是题目中的 n ，即代码中的 n 就是题目中的 n 的意思，但在代码注释中我用的还是上文中的含义。（原谅本人的懒惰····
CODE:
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
string s;
int length;
void work(long long n)
{
	if(n<=length)//边界条件：k<s.length()
	{
		cout<<s[n-1];
		return ;
	}
	long long i=length;//初始赋值为length，就不用在后面再乘了。
        while((i<<1)<n) i<<=1;//位运算更快，相当于i*2。
        n-=(i+1);
        if(n==0) n=i;//对于k在第n+1位置上的特判。
        work(n);//递归调用
}
int main()
{
	long long n;
	cin>>s>>n;
	length=s.length();
	work(n);
	return 0;
}
```


---

## 作者：jhc060321 (赞：19)

### 方法1：

先输入一个$string$，然后模拟整个过程，最后输入第$n$个数即可。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long n;
long long l;
int main()
{
	cin>>s>>n;
	l=s.size();
	while(l<n)
	{
		string t="x";
     	//
		t+=s;
		t[0]=s[s.size()-1];
        //把队尾移到队首。
		s=s+t;
		s.erase(s.end() - 1);//删去队尾多余元素。
		l=l*2;
	}
	printf("%c",s[n-1]);
}
```
这样，你可以拿到40$pts$的高分。[提交记录。](https://www.luogu.com.cn/record/33759372)
因为$string$存不下这么大的字符串。
### 方法2：（重点）
思路：
你可以把$n$转化一下，比如说，一个字符串$MCO$会变成$MCOOMC$,如果$n$为6，则对应的原先字符串中的第二位。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
long long n;
long long l;
int main()
{
	cin>>s>>n;
	l=s.size();
    long long a=l;
	while(l<n)l=l*2;
	l=l/2;//找到需要变成的字符串长度，并与n比较。
    while(n>a)//如果n<=a,则可以直接输出了。
    {
    	if(n==l) n=n/2;//这句话是废话。
    	else
    	if(n-l>1)
        n=n-l-1;//自己在草稿本推一下。
        else
        if(n-l==1) n=l;//特判。此时s[n]是移到队首的s[l]。
        
        l/=2;
    }
	printf("%c",s[n-1]);
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/npksonez.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

这样可以拿到100pts，[提交记录](https://www.luogu.com.cn/record/33759754)([或者这个](https://www.luogu.com.cn/record/33815221))

但是这里有很多细节，否则容易$WA$。

---

## 作者：Lin1043 (赞：10)

考试做的题……一开始在考场上想的是递归分治，结果因为longlong然后爆栈了.分治的思想还是很好想的显然我们可以把当前串分成两部分一个是原串，一个是操作串，操作串实际是由原串整体后移一位得到的，那么就是$new_{i}=old_{i-1}$且当$i-1=0$时$i$的值应为$old_{old.len}$所以把这种操作方式直接用$while$处理出来，就避免了爆栈的危险

放上代码

```cpp
#include <iostream>
using namespace std;
string s;
long long n,temp=1,l;
int main(){
    cin>>s>>n;
    l=s.length();
    for(temp=l;temp<=n;temp<<=1);//原串的长度每次翻倍
    temp>>=1;
    n-=1;//一定要减一，因为sting从0开始
    while(temp>=l){
        if(n>=temp){
            n-=temp;
            if(n==0)n=temp-1;
            else n-=1;
        }
        temp>>=1;
    }
    cout<<s[n%l]<<endl;
    return 0;
}
```

---

## 作者：jinyijiang (赞：10)

这道题是一道**分治**

容易发现每经过一次增长，len都会乘2

我们算出这个数最少经过多少次才能被取到

每次我们算出所求位置在（1~len/2）或（len/2+1~len）中

好，上代码

```cpp
//防止爆掉，开ull
#include <cstdio>
#include <iostream>
using namespace std;
string s;
char solve(unsigned long long a,unsigned long long n,unsigned long long i)
{
	if(i==1)//如果是最后一次，返回此位置
	{
		return s[n-1];
	}
	unsigned long long x=a/2; //二分
	if(n<=x)//在左边
	{
		return solve(x,n,i-1);
	}
	else
	{
		if(n==(x+1))//如果是第一个，要特判
			return solve(x,n-1,i-1);
		else
			return solve(x,n-x-1,i-1);
	}
}
int main()
{
	unsigned long long n;
	cin>>s;
	cin>>n;
	unsigned long long a=s.size();
	unsigned long long i=1;
	while(a<=n)//算出几次变换之后len>n
	{
		i++;
		a*=2;
	}
	cout<<solve(a,n,i)<<endl;//a:长度，n:位置，i:第几次变换之后
	return 0;
}
```

---

## 作者：NaVi_Awson (赞：5)

说下解题思路：

不妨把样例给的字符串按题目要求拓展一下：

（COW）【WCO】{OCOWWC}

（）内为初始串

【】内为第一次拓展

{}内为第二次拓展

可以发现字符串的总长度为len\*2^n

其中len为初始串长，n为第n次拓展

了解这个规律后我们再想：无论怎么拓展都还是原串的几个字符，那我们可以从未知串通过规律转换到已知串

首先将拓展的串还原：第一个字母放在串末，再整体向左移动，再将处理后的pos=pos-len\*2^n，新的pos便是第n-1次拓展时该字符的pos，直到n==1。

当然不用暴力转移，接近用pos操作就行了

附上伪代码：

```cpp
void doit()
{
    while(当前非初始串)
    {
        if (是拓展串的第1位) 将其移至串尾；
        pos=(pos-1)-len*2^n；
    }
}
```

---

