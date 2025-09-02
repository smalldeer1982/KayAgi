# [AHOI2017初中组] alter

## 题目描述

有 $n$ 盏灯排成一列，其中有些灯开着，有些灯关着。小可可希望灯是错落有致的，他定义一列灯的状态的不优美度为这些灯中最长的连续的开着或关着的灯的个数。小可可最多可以按开关 $k$ 次，每次操作可以使该盏灯的状态取反：原来开着的就关着，反之开着。现在给出这些灯的状态，求操作后最小的不优美度。

## 说明/提示

$30\%$ 的数据：$1\le k \le n\le20$；

$50\%$ 的数据：$1\le k \le n\le300$；

另有 $15\%$ 的数据：$1\le k \le n\le 10^5$，字符串为全 `N` 或全 `F`；

$100\%$ 的数据：$1\le k \le n\le 10^5$。

本题已经加入 hack 数据。

## 样例 #1

### 输入

```
8 1
NNNFFNNN```

### 输出

```
3```

# 题解

## 作者：Sooke (赞：38)

像这一题，要求最远距离最小，必定有二分的份啦~（暴力循环必死）


那么本题除了普通的二分，还有几个坑点（我也是被坑了好几次才A的）：

- 二分可以求出最小的不优美度，但是当最小值为 1 的时候请特判！

- 注意是最多按几次灯，不是必须要按几次灯！（也就是说，可以不按灯~）

- 二分得出一个可能的不优美度，当超过它而需要按下一个灯的时候，请格外注意赋值的量的大小关系，不要混淆！


这里先重点讲一下特判，由于字符串中的字符不是 N 就是 F ，所以想要让一排灯的不优美度为 1，有两种情况。

以字符串 FNNNFFNN 为例，如果最多能按 4 次开关，求最小的不优美度。

按照上面所说的，可以变成：

- FNFNFNFN （需要按 3 次开关）

- NFNFNFNF （需要按 5 次开关）

不难得出，想要让一排灯（灯数 ＞ 1）不优美度为 1 共有两种情况，而变成这两种情况所需要按开关的次数之和正好是灯数。

所以我们只要特判出一种情况，灯数 - 需要按的次数 = 另一种情况需要按的次数。特判两个次数是不是小于等于可以按的次数。


完整的代码如下：

```cpp
#include <iostream>
using namespace std;
int main()
{
    int n,k,p=0,g,t,ans;
    char c[2]={'F','N'}; //灯的状态对应的字符
    string s;
    cin >> n >> k >> s;
    for(int i=0;i < n;i++)
    if(s[i] == c[i % 2]) p++;
    if(p <= k || n-p <= k)
    {cout << 1; return 0;}
    //上面所说的特判方法
    int lb=2,rb=n / k+1,mb; //准备二分
    while(lb <= rb)
    {
        mb=(lb+rb) / 2; //得出可能的不优美度
        g=0;
        for(int i=0,j=0,l=0;i < n;i++)
        {
            if(s[j] == s[i]) l++;
            else j=i,l=1;
            if(mb < l) j=i+1,l=0,g++;
            //这个步骤请大家仔细思考。i 表示连续着的灯的最右段， j 表示连续着的灯的最左段，l 表示连续着的灯的长度，g 表示最少需要按多少次灯
        }
        if(g <= k)
        {
            rb=mb-1;
        } else
            lb=mb+1;
        //根据情况进行二分的分段
    }
    cout << lb;
    //输出最小的不优美度
    return 0;
}
```

---

## 作者：radish布団 (赞：18)

啊啊...这道题一定要写一篇题解...

由于楼上大佬们都已经给出了正确的解法，因此本题解不会再次对正确解法进行阐述。本题解要说明的内容主要有2个：

1. 为什么 $sta[i]/(mid+1)$ 这个式子是正确的；
2. 一个~~分数高到无需打正解的~~错误解法错在了哪里。

### 为什么 $sta[i]/(mid+1)$ 这个式子是正确的？

其实挺显然的...只需在每 $mid$ 个灯后面改变 $1$ 盏灯的状态即可满足条件。

### 一个95分的错误解法是如何炼成的？

这个错误解法如下：
```
#include<algorithm>//STL通用算法
#include<bitset>//STL位集容器
#include<cctype>
#include<cmath>
#include<complex>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<deque>//STL双端队列容器
#include<list>//STL线性列表容器
#include<map>//STL映射容器
#include<iostream>
#include<queue>//STL队列容器
#include<set>//STL集合容器
#include<stack>//STL堆栈容器
#include<utility>//STL通用模板类
#include<vector>//STL动态数组容器
#define INF 0x3f3f3f3f
#define ll long long
using namespace std;
int n,m,ans,sta[100010];
char a[100010];
int chk(int x)
{
	int sum=1,tot=0;
	static int tmp[100010];
	tmp[1]=sta[1];
	for(int i=2;i<=n;i++)
	{
		if(tmp[i-1]!=sta[i]) sum=1,tmp[i]=sta[i];
		else if(sum==x) tot++,tmp[i]=sta[i]^1,sum=1;
		else sum++,tmp[i]=sta[i];
	}
	return tot;
}
int main()
{
	scanf("%d%d",&n,&m);
	scanf("%s",a+1);
	for(int i=1;i<=n;i++)
		if(a[i]=='N') sta[i]=1;
	int l=1,r=n;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		int tmp=chk(mid);
		if(tmp<=m||n-tmp<=m) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
```
这个解法的核心思想是：枚举到第 $i$ 盏时，判断在这盏灯之前的处于同一状态且相连的灯是否已经达到 $mid$ 盏，且当前这盏灯是否与上一盏状态相同。若以上两个条件均满足，则改变当前这盏灯的状态。

乍一看这个贪心思路并没有什么问题，然而有一类数据是可以卡掉这个解法的：
```
Input：
7 1
NNFFFNN

Output：
2
```
然而用以上解法跑出来的答案是 $3$。

为什么呢？我们来手动模拟一遍这个解法。

以下变量中：第 $i$ 盏灯的初始状态为 $sta[i]$，最终状态为 $fin[i]$，当前已有 $sum$ 盏状态相同的灯相连，需改变状态的灯有 $tot$ 盏。

当 $mid=2$ 时：

$i=1,sum=1,tot=0,fin=N;$

$i=2,sum=2,tot=0,fin=NN;$

$i=3,sum=1,tot=0,fin=NNF;$

$i=4,sum=2,tot=0,fin=NNFF;$

$i=5,sum=1,tot=1,fin=NNFFN;$

$i=6,sum=2,tot=1,fin=NNFFNN;$

$i=7,sum=1,tot=2,fin=NNFFNNF;$

可以发现，最优的最终状态应为 $NNFNFNN$，然而由于贪心策略中“**只有达到 $\mathbf{mid}$ 盏才改变灯的状态**”这一条使得答案错误。

我相信得到95分的大佬大多是运用了以上错误解法。如果我的解释能给您提供一个更加清晰的解题思路，我将不胜荣幸。

---

## 作者：AK_Automata (赞：12)

~~真的好简单啊，去年想错了，否则一等没问题~~

按照标签做法：二分答案

二分答案模板就不用多说了吧。

主要是ok函数

~~前面几位神犇写的实在看不懂，写了一种专供我们这类蒟蒻看的~~

首先预处理，将字符串数字化
即将每一段连续的字符串用他们的长度替换。

## 重点：
### ok函数有两种情况

#### 1.如果mid不为1，那么每一次判断当前连续字符串是否长于mid（即答案）
#### 再分两种情况：
#### <1>.如果长于，则将当前所需开关灯次数加上p[i]/(mid+1),也就是将该段的灯开关成最长为mid的连续字符串。（这个公式不难理解，只要一定的数学基础即可）
#### <2>.如果不长于，跳过。

#### 2.如果mid为1，那么就比较麻烦了，我提供一种本人比较蒟蒻的想法，同上也分为两种情况，不过需要预处理，先生成以F，N分别开头的长度为n的连续字符串为1的串，最后只需分别与原串对比有多少不同就行了。

## 代码如下：


```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int M=100005;
int n,k,now,p[M];
char a[M],c[M],b[M];
bool ok(int ans){
	int s=0;
	for (int i=1;i<=now;i++)
		if (p[i]>ans) s+=p[i]/(ans+1);
	return s<=k;
}
bool ok1(int ans){
	int s=0;
	for (int i=1;i<=n;i++)
		if (b[i]!=a[i]) s++;
	if (s<=k) return true;
	s=0;
	for (int i=1;i<=n;i++)
		if (c[i]!=a[i]) s++;
	if (s<=k) return true;
	return false;
}
int main(){
	//freopen("alter.in","r",stdin);
	//freopen("alter.out","w",stdout);
	cin>>n>>k;
	for (int i=1;i<=n;i++)
		if (i%2==0) b[i]='N';
		else b[i]='F';
	for (int i=1;i<=n;i++)
		if (i%2==0) c[i]='F';
		else c[i]='N';
	cin>>a+1;
	p[++now]=1;
	for (int i=2;i<=n;i++)
		if (a[i]==a[i-1]) p[now]++;
		else p[++now]=1;
	int l=1,r=n,mid;
    while (l<r){
		mid=(l+r)>>1;
		if (ok(mid)&&mid!=1) r=mid;
		else l=mid+1;
		if (ok1(mid)&&mid==1) {r=mid;break;}
	    if (!ok1(mid)&&mid==1) l=mid+1;
		//cout<<l<<" "<<r<<" "<<mid<<endl;
	}
	cout<<r<<endl;
	return 0;
}
  
  
 //代码虽然较长，但实际上简单易懂


---

## 作者：Happy_Every_day (赞：7)

[P3718 [AHOI2017初中组]alter](https://www.luogu.com.cn/problem/P3718)

本题的实质呢就是求**最长的一段最短**，又满足单调性，所以可以使用**二分答案**快速求解。

本题分三种情况讨论：

1. 输入的字符串的不优美度已经是最小的了，即调任何一个开关都会使不优美度变大，这个时候我们就不需要拨动开关了，直接输出即可。
   
   那么这时的不优美度是多少呢？很显然，答案是 $1$，例如 `NFNFNF` 这种情况。
   
1. 虽然输入的字符串不优美度不为 $1$，但是我们可以在 $k$ 步之内把它调整为 $1$，这种情况又如何判断呢？

   举个例子，例如 `NFNFNNNF`，假设此时 $k=1$，这种情况的不优美度为 $2$，但是如果拨动倒数第三位上的 `N`，就可以将不优美度调成 $1$。具体如何实现请看代码。
   
1. 以上两种情况都是可以直接特判的，下面我们考虑第三种情况，也就是无论如何也不能将不优美度调成 $1$。
   
   我们可以先把输进来的字符串里所有**相同且连续**的字符数用一个数组记下来。设现在我们想得到的最小的不优美度为 $\text {Mid}$，如果我们可以调到，也就是需要调的次数小于等于 $k$，那么我们可以继续往 $\text {Mid}-1$ 的答案区间里找，如果不可以调到，那么我们就应该往 $\text {Mid}+1$ 答案区间里找。
   
   现在问题来了，我们怎样算需要操作的次数？
   
   现在的答案是 $\text {Mid}$，设我们这一段连续相同的字符的长度为 $a_i$，那么我们只要每隔 $\text {Mid}$ 个长度调一下即可，所以需要的操作数也就是 $\dfrac {a_i}{\text {Mid}+1}$，然后将所有要操作次数相加即可。
   
   
经过以上的讨论，我们来看一看代码是如何实现的吧：

```cpp
#include <cstdio>
using namespace std;
char s[100010];
int n,k,Left,Right,Mid,i,j,a[100010],Cnt,Suma,Sumb; 
int read () {
	int k=0,f=1;
	char c=getchar ();
	while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar ();}
	while (c>='0'&&c<='9') {k=k*10+c-'0';c=getchar ();}
	return k*f;
}
bool Check (int Ans) {
	int i,S;
	for (i=1,S=0;i<=Cnt;i++) S=S+a[i]/(Ans+1);
	if (S<=k) return true;else return false;
}
int main () {
	n=read ();k=read ();
	scanf ("%s",s+1);
	for (i=1;i<=n;i++) if ((i%2==1&&s[i]=='N')||(i%2==0&&s[i]=='F')) Suma++;
	for (i=1;i<=n;i++) if ((i%2==0&&s[i]=='N')||(i%2==1&&s[i]=='F')) Sumb++;
	if (Suma<=k||Sumb<=k) {puts ("1");return 0;}//如果属于第一种情况，那么它必然是 N 和 F 交叉放置的形式。
	for (i=1;i<=n;i++) {
		a[++Cnt]=1;
		while (s[i]==s[i+1]) {a[Cnt]++;i++;} 
	}
	Left=2;Right=n;
	while (Left<=Right) {
		Mid=(Left+Right)>>1;
		if (Check (Mid)==false) 
			Left=Mid+1;
		else 
			Right=Mid-1;
	}
	printf ("%d\n",Left);
	return 0;
}
```

---

## 作者：_•́へ•́╬_ (赞：7)

## 分析

显然二分答案加特判。

本题纯二分和优先队列不可过。问题在吧长度为 2 切成长度为 1 的切分方法。

煮个栗子：

`NFFN`

中间有个长度为 2​ 的。你随便改哪一个，改的那个都会和相邻的 `N` 组成另一个长度为 2。无法简单地切成长度为 1。

所以本题只能先特判能否把原串改成全部都是长度为 1​ 的。如果不能，再二分答案。

## $code$

```cpp
#include<stdio.h>
#define N 100000
int n,k,b[N],sz,l,r,mid,tepan;char a[N];
inline bool jg(const int&x)
{
	register int ans=0;
	for(register int i=0;i<=sz;++i)if(b[i]>x)ans+=b[i]/(x+1);
	return ans<=k;
}
main()
{
	scanf("%d%d%s",&n,&k,a);
	for(register int i=0;i<n;++i)
	{
		if((a[i]=='N')^(i&1))++tepan;
		if(i&&a[i]^a[i-1])b[++sz]=1;
		else ++b[sz];//吧连续的长度写到另一个数组里，方便后面
	}
	if(tepan<=k||n-tepan<=k){puts("1");return 0;}//特判，可以做到长度为1
	for(l=2,r=n;l<=r;)
	{
		mid=l+r>>1;
		if(jg(mid))r=mid-1;
		else l=mid+1;
	}
	printf("%d",l);
}
```



---

## 作者：a_grain (赞：5)



------------
[题面](https://www.luogu.com.cn/problem/P3718)

------------
阅读题目后，我们不难发现：此题具有**单调性**。
因此可以用**二分**做。

我先讲一下个人的判断思路，由于题目中求的是**最长的连续**个数，所以序列中可以有许多个**最长的连续**个数的序列。

而我们只要让超出二分答案个数的连续序列变为与二分答案个数相同的序列就行了，这样需要的次数就会最优，再在最后与 $k$ 做对比。

假设用 $s$ 来存储目前的序列长度，$sum$ 来存储次数，$x$ 为二分的答案。

以 NFFFFNNNFN 为例，二分答案为 $2$，求需要的最少次数。
```
     N F F N                   N F      N F N
   s=1 1 2 3(3>2,'F'->'N',s=1) 2 3(同前)1 1 1;
 sum=0 0 0 1                   1 2      2 2 2;
```
可知把该序列变为最长的连续个数序列为二的操作次数需要 $2$ 次。

所以就变成了
```
if(b[i]!=b[i-1])s=1;
else if(b[i]==b[i-1])s++;
if(s>x)s=1,b[i]=='N'?[i]='F':b[i]='N',sum++;
```

综上所述，此题的代码就能编出来了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,w,mid,ans;
char a[100010],b[100010];
bool check(int x){
	int sum=0,s=1;
	for(int i=1;i<=n;i++)b[i]=a[i];
	for(int i=2;i<=n;i++){
		if(b[i]==b[i-1])s++;
		else s=1;
		if(s>x){
			s=1,sum++;
			b[i]=='N'?b[i]='F':b[i]='N';
		}
	}
	return sum<=k;
}
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",a+1);
	t=1;w=n;
	while(t<=w){
		mid=(t+w)/2;
		if(check(mid))ans=mid,w=mid-1;
		else t=mid+1;
	}
	printf("%d\n",ans);
}
```
可当你提交后，会发现你惊人的 WA 了两个点：[#7 and #21](https://www.luogu.com.cn/record/64120022)。

于是在逛过讨论版后的我发现了解决#21 的方法——特判 $x=1$。
因为当 $x=1$ 时，判断程序会按照第一个位置是不用改的情况做。

例如 NFFNFN，$k$ 为 $2$。答案应该是 $1$，而上一个程序会输出 $2$。

所以在输入后直接特判并把 $t=1$ 改为 $t=2$：
```
for(i=1;i<=n;i++)a[i]==(i%2?'N':'F')?s1++:s2++;
if(min(s1,s2)<=k){printf("1\n");return 0;}
```
这样，你就能 A 了#21。

接下来的错误，就是判断思路的错误了。

例如 NFFFNN，$k=1$。答案应为 $2$，可 $2.0$ 程序为 $3$。

所以我们先做一次二分答案为 $2$ 的情况
```
    N F F N N F
  s=1 1 2 3 2 3;
sum=0 0 0 1 1 2;
```
可见 $sum$ 为 $2$，大于 $k$。

再自己想出一种方案把序列最长连续长度变为 $2$，
发现只要更改第 $3$ 位的 F 就可以了。

为什么会这样呢？因为判断程序把第 $4$ 位改了，没改第 $3$ 位，反而使后面的序列凑成长度为 $3$。

所以只要判断 $b[i]$ 是否等于 $b[i+1]$，如果相等，则改 $i-1$ 的位置最优(因为不会往回做，所以相当与不用改)，否则改 $i$ 的位置最优。

**AC code**
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,w,mid,ans,i,s1,s2;
char a[100010],b[100010];
bool check(int x){
	int sum=0,s=1;
	for(int i=1;i<=n;i++)b[i]=a[i];
	for(int i=2;i<=n;i++){
		if(b[i]==b[i-1])s++;
		else s=1;
		if(s>x){
			s=1,sum++;
			if(b[i+1]==b[i])b[i]=='N'?b[i]='F':b[i]='N';
		}
	}
	return sum<=k;
}
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",a+1);
	for(i=1;i<=n;i++)a[i]==(i%2?'N':'F')?s1++:s2++;
	if(min(s1,s2)<=k){printf("1\n");return 0;}
	t=2;w=n;
	while(t<=w){
		mid=(t+w)/2;
		if(check(mid))ans=mid,w=mid-1;
		else t=mid+1;
	}
	printf("%d\n",ans);
}
```


------------
# The End.

---

## 作者：MyukiyoMekya (赞：5)

@radish布団  的题解里说到 $sta_i/(mid+1)$ 这个柿子是有问题的，但是并没有深入思考这个柿子的改进方法。

首先考虑分段，然后二分答案。

二分答案 check 答案=1，这个总共就两种情况可以直接特判

然后就是答案 >=2 的情况，那么那些感觉很麻烦的长度为 2 的段就不用管了。

那么我们现在就是要快速求出对于每一段至少要翻转多少个才能达到长度限制内，因为长度为 2 的段不用管，所以很显然不会在段的两端翻转

假设第 $i$ 段的长度为 $a_i$ 

```
NNNNNNNN
```

这么一段，$a_i=8$

给他添个 F 进去

```
NNNFNNNN
```

再来一个

```
NNFNNFNN
```

我们发现，添加进去 $x$ 个 F ，段内的 N 的个数就会变为 $a_i-x$ 个，然后要把这些 N 尽可能平均放入 $x+1$ 个分段中

假设 $lim$ 表示现在二分的答案，也就是同种颜色段的长度限制，有：
$$
\lceil \frac {a_i-x}{x+1} \rceil\le lim
$$
现在知道 $lim,a_i$ 要求最小的 $x$

这个直接推推柿子就弄出来发现是个：
$$
x=\lceil \frac {a_i+1}{lim+1} \rceil-1
$$
然后对于每个 $a_i$ 都这么算即可

```cpp
// This code wrote by chtholly_micromaker(MicroMaker)
#include <bits/stdc++.h>
#define reg register
using namespace std;
const int MaxN=100050;
template <class t> inline void read(t &s)
{
	s=0;
	reg int f=1;
	reg char c=getchar();
	while(!isdigit(c))
	{
		if(c=='-')
			f=-1;
		c=getchar();
	}
	while(isdigit(c))
		s=(s<<3)+(s<<1)+(c^48),c=getchar();
	s*=f;
	return;
}
template <class t> inline void write(t x)
{
	if(x<0)
		putchar('-'),x=-x;
	int buf[21],top=0;
	while(x)
		buf[++top]=x%10,x/=10;
	if(!top)
		buf[++top]=0;
	while(top)
		putchar(buf[top--]^'0');
	return;
}
int n,K;
int a[MaxN];
char inp[MaxN];
vector<int> dr;
inline bool check(int lim)
{
	reg int res=0;
	for(int i=0;i<(int)dr.size();++i)
		if(dr[i]>lim)
			res+=(int)ceil(((double)dr[i]+1.0)/((double)lim+1.0))-1;
	return res<=K;
}
signed main(void)
{
	read(n);read(K);
	scanf("%s",inp+1);
	for(int i=1;i<=n;++i)
		a[i]=((inp[i]=='N')?1:0);
	reg int lst=a[1],cnt=1;
	for(int i=2;i<=n;++i)
		if(a[i]==lst)
			++cnt;
		else
			dr.push_back(cnt),lst=a[i],cnt=1;
	dr.push_back(cnt);
	cnt=0;
	for(int i=1;i<=n;++i)
		if(i&1)
		{
			if(a[i])
				++cnt;
		}
		else
		{
			if(!a[i])
				++cnt;
		}
	if(cnt<=K||n-cnt<=K)
	{
		puts("1");
		return 0;
	}
	reg int l=2,r=n,mid,ans=n;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(check(mid))
			ans=mid,r=mid-1;
		else
			l=mid+1;
	}
	write(ans),puts("");
	return 0;
}
```



---

## 作者：无名ZWH (赞：5)

好了，先说说这题的一个暴力代码  
其实是我在题解里面COPY的@cliyx大佬的  
先送上55分代码  
```cpp
#include<bits/stdc++.h>//换了个万能头
using namespace std;
int n, k, cnt = 1, f; //f待会儿说
char las;//记录上一个元素
string s;//读入连续字符不用string要炸
priority_queue<int> li;//优先队列
int main()
{
    cin >> n >> k;
    cin >> s, las = s[0]; //las=s的第一个元素
    for(int i = 1; i < s.size(); i++)
    {
        if(s[i] == las) cnt++;
        else if(s[i] != las) 
        //如果与前一段落元素不同就初始化并且投入段落
        {
            if(i == s.size() - 1) f = 1;   
  //这里的意思是防止最后一个元素被反复投入，见下

            li.push(cnt);
            cnt = 1, las = s[i];
        }
    }
    if(!f) li.push(cnt);//见上
    for(int i = 1; i <= k; i++)   
  //标题里很清楚，当然要记得把元素取出后要删除
    {
        int x = li.top();
        li.pop();
        x /= 2;
        li.push(x);
    }
    cout << li.top(); //输出最大即可
    return 0;
}
```  
以上是@cliyx大佬的55分代码  
其实对@cliyx大佬的55分代码进行一些修改后可以升到72分  
这是我的修改的代码  
```cpp
#include<bits/stdc++.h>//换了个万能头
using namespace std;
int n,k,cnt=1,f,yh,z;//f待会儿说
char las;//记录上一个元素
string s;//读入连续字符不用string要炸
priority_queue<int> li;//优先队列
int main(){
    cin>>n>>k;
    cin>>s,las=s[0];//las=s的第一个元素
    for(int i=1;i<s.size();i++)
    {
        if(s[i]==las) cnt++;
        else if(s[i]!=las)
        //如果与前一段落元素不同就初始化并且投入段落
        {
        	if(i==s.size()-1) f=1;  
        //这里的意思是防止最后一个元素被反复投入，见下
            li.push(cnt);
            cnt=1,las=s[i];
        }
    }
    if(!f) li.push(cnt);//见上
    for(int i=1;i<=k;i++)//标题里很清楚，当然要记得把元素取出后要删除
    {
        int x=li.top();
        li.pop();
        /*x/=2;
        li.push(x);*///这是我修改前的cliyx大佬的代码
        z=x-1;
        if(z%2==0)
        {
        	x=z/2;
        }
        if(z%2!=0)
        {
        	x=z/2+1;
        }
        yh=z-x;
        li.push(x);
        li.push(yh);//这是我修改的代码
    }
    cout<<li.top();//输出最大即可
    return 0;
}
```
问题来了为什么分数会增加呢？  
其实cliyx大佬的代码忽略了一个东西  
在对x/进行操作时不是简单的x=x/2;  
比如说在对一个长度为7的NNNNNNN操作后  
并不是断为一个长度为3的NNN  
而是两个链一个长度为（7-1）/2=3  
另一个长度为（7-1）-3=3  
所以要压回队列中的是两个而不是简单的n/2  
好了为什么没有特判呢？  
因为根本不需要    
在所有链长都为一后代码的操作是正确的  

好了来说说我的代码  
一开始我就想到贪心然后就爆了只有12分  
再一看要求最远距离最小，果断二分  
于是  
```cpp
#include<bits/stdc++.h>
using namespace std;
bool light[100010], L[100010];
int n, k, sum1 = 0, sum2 = 0;
int cheak(int m)
{
    int l = 0, a = 0, need = 0;
    for(int i = 1; i <= n; i++)
    {
        if(light[i] == 1)
        {
            l++;
            if(a > 0)a = 0;
        }
        else
        {
            a++;
            if(l > 0)l = 0;
        }
        if(a > m)
        {
            if(a >= 3 && light[i + 1] == 1)a = 0, l = 0, need++;
            else a = 0, l = 1, need++;
        }
        if(l > m)
        {
            if(l >= 3 && light[i + 1] == 0)a = 0, l = 0, need++;
            else l = 0, a = 1, need++;
        }
        if(need > k)return 0;
    }
    return 1;
}//二分函数
int main()
{
    char s;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        cin >> s;
        if(s == 'N')light[i] = 1;
        else light[i] = 0;
    }//初始化
    int l = 1, r = n;
    while(l < r)
    {
        int mid = (l + r) / 2;
        if(cheak(mid) == 1)r = mid; //二分
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}
```
96分！  
仔细一想
这题的操作一定要注意！！ 这不是优先队列   
二分可以求出最小的链长，但无法解决链长为一的情况  
所以请特判  
好了贴出正确代码  
```cpp
#include<bits/stdc++.h>
using namespace std;
bool light[100010], L[100010];
int n, k, sum1 = 0, sum2 = 0;
int cheak(int m)
{
    int l = 0, a = 0, need = 0;
    for(int i = 1; i <= n; i++)
    {
        if(light[i] == 1)
        {
            l++;
            if(a > 0)a = 0;
        }
        else
        {
            a++;
            if(l > 0)l = 0;
        }
        if(a > m)
        {
            if(a >= 3 && light[i + 1] == 1)a = 0, l = 0, need++;
            else a = 0, l = 1, need++;
        }
        if(l > m)
        {
            if(l >= 3 && light[i + 1] == 0)a = 0, l = 0, need++;
            else l = 0, a = 1, need++;
        }
        if(need > k)return 0;
    }
    return 1;
}//二分函数
int main()
{
    char s;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++)
    {
        cin >> s;
        if(s == 'N')light[i] = 1;
        else light[i] = 0;
        if(i % 2 == 1)L[i] = 0;
        else L[i] = 1;
        if(L[i] != light[i])sum1++;
        else sum2++;
    }//初始化和特判准备
    if(k >= sum1 || k >= sum2)
    {
        cout << "1";
        return 0;
    }//特判
    int l = 1, r = n;
    while(l < r)
    {
        int mid = (l + r) / 2;
        if(cheak(mid) == 1)r = mid;//二分
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}
```
最后感谢cliyx大佬  

---

## 作者：快斗游鹿 (赞：5)

## 思路

正解二分。

考虑二分决策。枚举此时连续的数字个数，当枚举到第 $i$ 个数字超过时，若第 $i+1$ 个值与其相同，就改动当前的。否则改前一个，因为它不会往回处理，所以改前一个时不许做任何处理。

关于正确性证明，其他题解已经足够详细了，这里不再赘述。下面放一下代码。

## 完整代码
```
#include<bits/stdc++.h>
using namespace std;
int n,k,ans; 
int lamp[100010],deng[100010];
bool check(int x){
    int sum=0,s=1;
    for(int i=1;i<=n;i++)deng[i]=lamp[i];
    for(int i=2;i<=n;i++){
        if(deng[i]==deng[i-1])s++;
        else s=1;
        if(s>x){
            s=1,sum++;
            if(deng[i+1]==deng[i])deng[i]==1?deng[i]=0:deng[i]=1;//二分决策
        }
    }
    return sum>k;
}
int main(){
	scanf("%d%d",&n,&k);
	int s1=0,s2=0;
	for(int i=1;i<=n;i++){//转成01串，便于处理
		char s;cin>>s;
		if(s=='N')lamp[i]=1;
		else lamp[i]=0;
		lamp[i]==(i%2?1:0)?s1++:s2++;
	}
	if(min(s1,s2)<=k){cout<<1;return 0;}
	int l=2,r=n,mid;
	while(l<=r){
		mid=(l+r)>>1;
		//cout<<mid<<endl;
		if(check(mid)){//二分
			l=mid+1;
		}
		else{
			ans=mid;
			r=mid-1;
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：yeshubo_qwq (赞：4)

## 声明
本题解仅是对 @a_grain 程序的一个小优化。

不先看看 @a_grain 的[题解](https://www.luogu.com.cn/blog/Nightmaresans/solution-p3718)吗？
## 有效的小优化
可以看到，他的判断函数中每次都给 $b$ 数组重新赋值，这样对时间有不必要的浪费。

为什么有 $b$ 数组？因为按照其思想，$a$ 数组会被改变，导致后面的错误，因此才有 $b$ 数组。

所以我们可以考虑用 $flag$ 做标记代替 $b$ 数组，这样就可以减去给 $b$ 数组重新赋值的时间，优化速度。~~虽然整体还是较慢~~
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t,w,mid,ans;
char a[100010],b[100010];
/*
bool check(int x){//修改前
    int sum=0,s=1;
    for(int i=1;i<=n;i++)b[i]=a[i];
    for(int i=2;i<=n;i++){
        if(b[i]==b[i-1])s++;
        else s=1;
        if(s>x){
            s=1,sum++;
            b[i]=='N'?b[i]='F':b[i]='N';
        }
    }
    return sum<=k;
}
*/
bool check(int x){//修改后
	int sum=0,s=1,flag=0;
	for(int i=2;i<=n;i++){
		if(flag==1)flag=0;
		else if(a[i]==a[i-1])s++;
		else s=1;
		if(s>x){
			s=1,sum++;
			if(a[i+1]==a[i])flag=1;
		}
	}
	return sum<=k;
}
int main(){
    scanf("%d%d",&n,&k);
    scanf("%s",a+1);
    t=1;w=n;
    while(t<=w){
        mid=(t+w)/2;
        if(check(mid))ans=mid,w=mid-1;
        else t=mid+1;
    }
    printf("%d\n",ans);
}
```

---

## 作者：war1111 (赞：4)

贪心+二分答案

二分最终答案长度

主要问题在check上

~~我代码写得巨丑，大家还是不要看我的代码了~~

------------

1:当mid大于1的时候，贪心策略是这样的：

当前连续的长度大于mid时，我不反转最后一个，我也不管它具体反转哪一个，我直接跳过这mid+1个，也就是开始处理i+1。举个例子，
mid=3,k=1,NNNNNNN,我反转第4个，变成NNNFNNN
mid=3,k=1,NNNNFFF,我反转前3个的任意一个
不管怎么反转，前4个对后面是没有影响了，那我就不用管具体怎么反转的


2:当mid等于1的时候，贪心策略是这样的：

跑两遍check,反转第一个，或者不反转第一个，两种情况有一个能行就ok



------------

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
#define inf 2147483647
#define N 1000010
#define p(a) putchar(a)
#define For(i,a,b) for(int i=a;i<=b;++i)
//by war
//2019.8.13
using namespace std;
int n,k,l,r,mid,a[N],cnt,now;
char c[N];
void in(int &x){
    int y=1;char c=getchar();x=0;
    while(c<'0'||c>'9'){if(c=='-')y=-1;c=getchar();}
    while(c<='9'&&c>='0'){ x=(x<<1)+(x<<3)+c-'0';c=getchar();}
    x*=y;
}
void o(int x){
    if(x<0){p('-');x=-x;}
    if(x>9)o(x/10);
    p(x%10+'0');
}

bool check1(int x,int t){//用来判断mid==1的情况
    int lf=k-1;
    For(i,1,n)
        if(c[i]=='N')
            a[i]=1;
        else
            a[i]=0;
    cnt=1;now=t;
    For(i,2,n){
        if(a[i]==now){
            ++cnt;
            if(cnt>x){
                a[i]^=1;
                if(x!=1){
                    now=a[i+1];
                    cnt=0;
                }
                else{
                    now=a[i];
                    cnt=1;
                }
                if(--lf<0)
                    return 0;
            }
        }
        else{
            now=a[i];
            cnt=1;
        }
    }
    return 1;
}

bool check(int x){
    int lf=k;
    For(i,1,n)
        if(c[i]=='N')
            a[i]=1;
        else
            a[i]=0;
    cnt=1;now=a[1];
    For(i,2,n){
        if(a[i]==now){
            ++cnt;
            if(cnt>x){
                a[i]^=1;
                if(x!=1){
                    now=a[i+1];
                    cnt=0;
                }
                else{
                    now=a[i];
                    cnt=1;
                }
                if(--lf<0){
                    if(x==1){
                        if(check1(x,a[1]^1))
                            return 1;
                        return 0;
                    }
                    return 0;
                }
            }
        }
        else{
            now=a[i];
            cnt=1;
        }
    }
    return 1;
}

signed main(){
    in(n);in(k);
    cin>>(c+1);
    l=1;r=n;
    while(l<r){
        mid=(l+r)>>1;
        if(check(mid))
            r=mid;
        else
            l=mid+1;
    }
    o(l);
    return 0;
}
```


---

## 作者：Mine_King (赞：3)

这题，最小不优美度为$m$，那么最小不优美度一定也可以是 $m+1$,所以能二分答案。

对于二分出的一个答案 $m$，我们扫一遍序列。  
扫的同时记录这一段的起始节点 $l$ 和这一段的长度 $res$，然后对于当前点 $i$：

- 若 $i$ 的状态与 $l$ 相同，则 $res++$
- 若 $i$ 的状态与 $l$ 不同，则现在的 $l=i$， $res$ 为 $1$

接着，若此时 $res>m$，则不符合要求，那么要改变 $i$ 的状态，操作次数 $+1$，然后重置 $res=0,l=i+1$。  

注意！还没完！当 $m=1$ 的时候要特判。  
$m=1$，我们可以记录一个 $p$，若 $i$ 为奇数且 状态为开 或  $i$ 为奇数且状态位关则 $p++$，也就是记录最终状态为 $FNFNFNFN\cdots$ 的修改次数为 $p$，那么最终状态为 $NFNFNFNF\cdots$ 的修改次数就是 $n-p$，若 $p \le k$ 或者 $p \le n-k$ 则可以做到 $m=1$。  

具体代码实现:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k,p;
int l,r;
bool a[100005];
bool check(int x)
{
	int sum=0;
	for(int l=1,i=1,res=0;i<=n;i++)
	{
		if(a[i]==a[l]) res++;
		else l=i,res=1;
		if(res>x) sum++,res=0,l=i+1;
	}
	return sum<=k;
}
int main()
{
	scanf("%d %d\n",&n,&k);
	for(int i=1;i<=n;i++)
	{
		char c=getchar();
		a[i]=(c=='N');
		if(i%2&&a[i]) p++;
		else if(!(i%2)&&!a[i]) p++;
	}
	if(p<=k||n-p<=k){puts("1");return 0;}
	l=2,r=n;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid+1;
	}
	printf("%d\n",r);
	return 0;
}
```

---

## 作者：FreeTimeLove (赞：2)

## 题意

给定一个长为 $n$ 的 $01$ 序列，反转**至多** $k$ 次序列中的单个字符，求最终序列中**最长**连续 $0$ 或 $1$ 长度的**最小值**。

## 思路

二分关键字：最大值的最小值。此题可以用二分做。

我们二分最长**连串**（连续的相同字符构成的串）的长度 $mid$，判断是否能够在不超过 $k$ 次内转化为最长连串长度不大于 $mid$ 即可。问题就在于如何判断是否可行。

可以发现，当 $mid\ge2$ 时比较容易判断：将 $01$ 串转化为每个连串的**长度**构成的序列，依次与 $mid$ 比较。如果当前连串长度 $len\le mid$ 说明符合条件，不需要操作；否则，**每** $(mid+1)$ 个字符中就**至少**要有 $1$ 个不同的字符。为了使操作数**尽量少**，我们在**每个**连串中每 $(mid+1)$ 个字符就反转一个字符，那么长为 $len$ 的连串就需要反转 $\lfloor\dfrac{len}{mid+1}\rfloor $ 个字符。因为如果一个连串需要反转字符，$len$ 一定是**不小于** $3$ 的，可以做到左右端点都不改变，所以此时不同连串之间**相互独立、互不影响**。

但是当 $mid=1$ 时却不能这样判断，因为更改一个 $len=2$ 的连串**一定**会影响相邻的连串。这个时候我们可以在二分前先特判一下。如果最长连串长度为 $1$，那么只有两种可能：$010101…$ 和 $101010…$ 。我们只要分别判断原序列和这两种序列的不同字符个数，如果存在一种情况操作次数小于等于 $k$，就说明最长连串长度可以为 $1$，输出即可。

更进一步地，因为一个字符一定是 $0$ 或 $1$，所以它**在且仅在**一种可能当中需要更改，那么两种情况更改次数加起来一定是 $n$，我们只统计一种情况就够了，另一种情况可以计算出来。

## AC code
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
const int N=1e5+5;
int n,k,x,tot,sum,num,ans,que[N],a[N],l,r,maxn;
char s[N];
bool ok(int lim){
	x=lim+1,ans=0;
	for(int i=1;i<=tot;i++)
		ans+=que[i]/x;
	return ans<=k;
}
int main(){
	cin>>n>>k;
	getchar();
	for(int i=1;i<=n;++i)s[i]=getchar();
	for(int i=1;i<=n;i++){
		a[i]=(s[i]=='N')?1:0;
		if((i+a[i])%2)ans++;
	}
	a[n+1]=2;
	if(ans<=k||(n-ans)<=k){//特判mid=1
		cout<<1<<endl;
		return 0;
	}
	
	sum=1,num=a[1];
	for(int i=2;i<=n+1;i++){//计算每个连串长度
		if(a[i]==num)sum++;
		else{
			que[++tot]=sum;
			num=a[i];
			maxn=max(maxn,sum);	
			sum=1;
		}
	}
	l=2,r=maxn;
	while(l<r){//二分操作后的最长连串长度
		int mid=(l+r)>>1;
		if(ok(mid))r=mid;
		else l=mid+1;
	}
	cout<<l<<endl;
	return 0;
}
```
### The End.

---

## 作者：陈昶旭 (赞：2)

一道水题（当年作为蒟蒻的我竟没做出来,一年后发现这么简单）

------------

30%:枚举状态(懒得打代码)


------------

50%:O(n^2)


------------

我们来看看不优美度为p能否做到


------------

将状态化为若干个连续的N/F


------------

如:NNNFFNNN-> 3 2 3
记每一段为a[i]


------------

则p能做到等价为sigama a[i]/(p+1)<=k (自己画图)


------------

然后就简单了,枚举p


------------

100%:O(nlog n)把上面思路的枚举改为二分
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string st;
int a[100010];
int z;
char f;
int l=2,r,mid;
bool judge(int p)
{
	int ans=0;
	for(int i=1;i<=z;i++)ans+=int(a[i]/(p+1));
	if(ans<=k)return true;return false;
}
void get()
{
	if(f=='N')f='F';
	else f='N';
}
int main()
{
	cin>>n>>k;
	cin>>st;
	f=st[0];
	z=1;a[1]=1;
	int cnt=0;
	for(int i=0;i<n;i++)
	{
		if(st[i]!=f)cnt++;
		get();
	}
	if(cnt<=k)
	{
		cout<<1;
		return 0;
	}
	f=st[0];
	for(int i=1;i<n;i++)
	{
		if(st[i]==f)a[z]++;
		else a[++z]=1,get();
	}
	for(int i=1;i<=z;i++)r=max(r,a[i]);
	while(l<=r)
	{
		mid=(l+r)/2;
		if(judge(mid))r=mid-1;
		else l=mid+1;
	}
	cout<<l;
	//system("pause");
	return 0;
}
/*

*/

```

---

## 作者：SIXIANG32 (赞：1)

做一下本省历年的初中题捏=w=

说句实话出的挺不负责的，四题里面基本上都有两题原题（恼

首先这题可能你会想到一个奇怪的贪心，就是我们每次修改，肯定会在一个连续的块里面修改，那么我们修改哪个点呢？我们可能会直观的贪心，想到修改当前最长块的中点。现在这个块分成三个块了（取反的单独算一个块）。块长度用堆维护，时间复杂度 $O(n\log_2n)$。对于块长为 $1$ 或 $2$ 不能修改在块中，必然在边缘上，所以特判即可。

但是这个算法显然是错的，hack 
```
Input:
9 2
NNNNNNNNN
Output:
2
```

不能贪心，那么由于这题最大值最小显然我们考虑二分，而且上面这样修改给我们的二分提供了判定的启示。我们令 $check(x)$ 为答案是否小于等于 $x$。很显然，对于一个连续的块中我们会每次在 $(x+1), 2(x+1)\dots k(x+1)$ 的位置取反。那么也就是说对于一个块，如果长度为 $l$，则需要取反 $\left\lfloor\dfrac{l}{x+1}\right\rfloor$ 下。累加一下和就能得到答案。

不过这个时候就有个问题了，如果块长度恰好为 $(x+1)$ 的倍数，那么会在最后一个位置取反，会影响到下一个块的长度，这样就很麻烦，事实上并不会这样。当 $x\ge 2$ 时，我们可以把最后一个取反位往前移一下，比如说 $x = 2$，有一个为 ```NNNNNN``` 的序列，本来应该是 ```NNFNNF```，后面的连续块必然是 ```F``` 的，这样就会改变后面连续块的长度。不过我们变成 ```NNFNFN```，这样就避免了这个问题。

不过当 $x = 1$ 时，我们这样就必然会和后面的连起来，也就是说 $check(1)$ 是不准确的。这不好。所以我们可以特判一下 $x = 1$ 的情况。注意到 $x = 1$ 的序列必然能变成 ```NFNFNFNF...``` 或者是 ```FNFNFNFN...``` 的样子。显然我们不会取反同样位置两次，我们统计原序列与这两个序列有多少不同位置，数量是否小于等于 $k$，先特判再二分即可。

不过加了这个特判后一定要注意在二分之中要判断答案是否已经取到了 $2$。因为当答案取到 $2$ 后，下一个 $mid$ 就会取 $1$，而且 $check(1)$ 可能能行。但是我们的特判说明是不行的。我试了试不加这个答案等于 $2$ 的特判是 84pts，看到讨论区有个 hack 数据，来搬上来：

```
Input:
7 2
FNNFNNF
Output:
2
```

在二分的时候，如果按照刚才的算法 $check(1)$ 可行，但是实际上是不对的。所以必须要在答案等于 $2$ 时停止二分，否则就会二分到 $1$ 上。

代码：
```cpp
//SIXIANG
#include <iostream> 
#define MAXN 200000
#define QWQ cout << "QWQ" << endl;
using namespace std;
int a[MAXN + 10], bl[MAXN + 10], n, k, pika, c1 = 0, c2 = 0, tot = 0, ct = 1;
char o;
bool check(int x) {
	int rest = 0;
	for(int p = 1; p <= tot; p++)
		rest += (bl[p] / (x + 1));
	return (rest <= k);
}
int twofen() {
	int l = 1, r = n, mid, ans = 114514;
	while(l <= r) {
		int mid = (l + r) >> 1;
		bool pwp = check(mid);
		if(mid == 2 && pwp) {//答案等于 2 的特判
			ans = 2;
			break;
		}	
		if(pwp) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}
int main() {
	cin >> n >> k;
	
	for(int p = 1; p <= n; p++) {
		cin >> o;
		a[p] = (o == 'N');
		if(a[p] == pika) c1++;
		else if(a[p] == (!pika)) c2++;
		pika ^= 1;//不同的位数
	}
	if(c1 <= k || c2 <= k) {//对 1 的特判
		cout << 1 << endl;
		return 0;
	}
	
	for(int p = 2; p <= n; p++) {
		if(a[p] == a[p - 1]) ct++;
		else bl[++tot] = ct, ct = 1;
	}
	bl[++tot] = ct;//计算每个块的长度
	cout << twofen() << endl;
}
```
总而言之也不太难，小细节有点多，多考虑一下也不难 pwp

第一次提交不小心把第一个 hack 写错了(\*/ω＼\*)

---

## 作者：大眼仔Happy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P3718)

------------

本篇是写给那些并没有看懂其他的题解为什么是用 $sta[i]/(mid+1)$ 的人，~~包括我自己。~~

（注： $sta[i]$ 为连续灯的个数，即下文的 $s$ 。）
## 暴力部分：

~~蒟蒻的我认为，这道题看起来很简单啊，直接暴力就可以了啊，然后就写出了以下暴力：~~

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
char a[100005];
bool check(int x)
{
	......
	......
}//判断如果让不优美度<=x，那么需要的操作操作是否<=k。
int main(){
    scanf("%d%d%s",&n,&k,a+1);
    for(int i=1;i<=n;i++)
    {
    	if(check(i)<=k)
    	{
    		cout<<i;
    		return 0;
		}
	}
	return 0;
}
```

~~然后，就TLE了。~~

## 正文部分：

### Part1：

我们看到这道题，先来分析一下。~~显然是二分答案。~~

对于上面的暴力做法，时间复杂度为 $O(n^2)$ 。这明显的超时了。我们尝试优化做法。

不难发现，如果想要让不优美度越小，我们就要关越多的灯。

因为关灯操作的数量是确定的，我们可以通过二分不优美度的大小，接着用 `check()` 求出，（ `check()` 与上面的定义一样）。所以新的时间复杂度为 $O(n\log n)$ ，在时间限制之内。

于是我们就可以在主函数里面写这样的代码：

```cpp
scanf("%d%d%s",&n,&k,a+1);
int l=1,r=n;
while(l<r){
    int mid=(l+r)/2;
    if(check(mid))r=mid;
    else l=mid+1;
}
 printf("%d",l);
 return 0;
```

------------

### Part2：

接下来我们就要思考如何去写 `check()` 。

假设我们现在二分到了 $x$ ，那么也就是要让不完美度 $\le x$ 。我们就记录当前连续相同的灯的个数 $s$ ，如果 $s>x$ ，那我们就将当前的（假设是 $i$ ） $i$ 号灯进行修改。

基于这个想法，我们可以写出以下代码：

```cpp
bool check(int x)
{
	int sum=0,s=0;
	b[0]='A';//哨兵 
	for(int i=1;i<=n;i++)b[i]=a[i];//b用于更改
	for(int i=1;i<=n;i++){
		if(b[i]==b[i-1])s++;
		else s=1;
		if(s>x)
		{
			sum++;
			if(b[i]=='N')b[i]='F';
			else b[i]='N';
			s=1;
		}
	}
	return (sum<=k);
}
```

然后，就完了。~~然后你就发现你没A，92pts的你很抓狂。~~

#### 我们是否漏掉了什么？

------------

### Part3：

带着这个疑问，我们进入到Part3。

首先先给出一组hack数据，如果没过的，可以试一试这个Hack。

```
in:
9 1
NNNNNFFFF
```
```
out:
4
```
上面的代码则是输出 $5$ 。

在这个样例的 $x=4$ 中，我们不能对 $5$ 号灯进行修改，因为修改后变成 `F` ，和第 $6$ 位一样，就会对后面造成影响，但是我们可以对 $4$ 号灯操作，变成 `NNNFNFFFF` 。

但假如是 `NNNNNNFFF` ，那么我们修改 $5$ 号灯就不会对后面影响。

所以总结来说，就是如果枚举到 $i$ 号灯，要进行修改，分一下情况：

1.  $i$ 号灯修改后和 $(i+1)$ 号灯一样，那么应该修改 $(i-1)$ 号灯。

2.  $i$ 号灯修改后和 $(i+1)$ 号灯不一样，那么就修改 $i$ 号灯。

代码如下：
```cpp
void fz(int i)
{
	if(b[i]=='N')b[i]='F';
	else b[i]='N';
}//修改函数
bool check(int x){
	int sum=0,s=0; 
	b[0]=b[n+1]='A';
	for(int i=1;i<=n;i++)b[i]=a[i];//用于更改 
	for(int i=1;i<=n;i++){
		if(b[i]==b[i-1])s++;
		else s=1;
		if(s>x){
			sum++;
			if(b[i+1]!=b[i])fz(i-1);
			else fz(i);
			s=1;
		}
	}
	if(sum<=k)return 1;
	else return 0;
}
```
我们应该思考一下，修改 $(i-1)$ 号灯，或许也会对前面的造成影响，那么怎么办呢?

**答案是特判。**

举个例子：
```
x=1
NFNNF
```
假如枚举到 $4$ 号灯，那么我们按照上面的方法发现需要修改 $3$ 号灯，那么 $2$ 号灯和 $3$ 号灯就会连起来。

```
x=2
NFNNNF
```
如果是这个例子，枚举到 $5$ 号灯，那么就要更改 $4$ 号灯，那么就会对 $3$ 号灯造成影响，但必然不会增大答案，因为 $3$ 号灯和 $5$ 号灯是一样的。

#### 所以，我们只需特判 $x=1$ 的情况。

 $x=1$ 的方案也特别小，就只有 $\texttt{NFNFNFN}\ldots$ 和 $\texttt{FNFNFNF}\ldots$ 两种可能，直接暴力判断原来的和这两个有多少个不同，取最小值返回就完了。

AC Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
char a[100010],b[100010];
void fz(int i)
{
	if(b[i]=='N')b[i]='F';
	else b[i]='N';
}//修改函数
bool check(int x){
	int sum=0,s=0; 
	if(x==1)//特判：考虑只有两种序列,NFNFNFN...和FNFNFNFN，求最小值 
	{
		int ans1=0,ans2=0;
		for(int i=1;i<=n;i++)
		{
			if(i%2==1)
			{
				if(a[i]=='F')ans1++;
				else ans2++;
			}
			else 
			{
				if(a[i]=='N')ans1++;
				else ans2++;
			} 
		}
		if(min(ans1,ans2)<=k)return 1;
		else return 0;
	}
	b[0]=b[n+1]='A';//哨兵 
	for(int i=1;i<=n;i++)b[i]=a[i];//用于更改
	for(int i=1;i<=n;i++){
		if(b[i]==b[i-1])s++;
		else s=1;
		if(s>x)
		{
			sum++;
			if(b[i+1]!=b[i])fz(i-1);//如果i+1和i不一样，那么i+1和翻转的i就一样了，所以就可能对后面的造成影响，所以考虑翻转i-1 
			else fz(i);
			s=1;
		}
	}
	if(sum<=k)return 1;
	else return 0;
}
int main(){
    scanf("%d%d%s",&n,&k,a+1);
    int l=1,r=n;
    while(l<r){
        int mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    printf("%d",l);
    return 0;//完结撒花！！！✿✿ヽ(°▽°)ノ✿
}
```

---

## 作者：嘿嘿嘿嘿嘿嘿6 (赞：1)

首先我们分析可得，这道题应该用二分答案。

为什么呢？

第一点，答案具有单调性。

第二点，答案是让你在一个区间里查找。

接下来二分枚举答案即可，但要注意，不优美度为 1 时需要特判。

下面是我的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[100005];
int a[100005],tot=0,n,k;
bool spj(){
    int x=0,y=0;
    for(int i=1;i<=n;++i){
        if(i%2==1&&ch[i]!='N'||i%2==0&&ch[i]!='F') ++x;//NFNFNFNF
    }
    for(int i=1;i<=n;++i){
        if(i%2==1&&ch[i]!='F'||i%2==0&&ch[i]!='N') ++y;//FNFNFNFN
    }
    return min(x,y)<=k;
}//特判mid=1时，只有两种情况
bool check(long long ans){
    int cnt=0;
    for(int i=1;i<=tot;++i) cnt+=a[i]/(ans+1);
    return cnt<=k;
}//检查函数，每次需要a[i]/(mid+1)次
int main(){
    int j;
    scanf("%d%d",&n,&k);
    scanf("%s",ch+1);
    for(int i=1;i<=n;++i){
        for(j=i+1;j<=n;++j){
            if(ch[j]!=ch[i]) break;
        }
        a[++tot]=j-i;
        i=j-1;
    }
    long long l=1,r=n,mid=l+r>>1;//位运算，就等于(l+r)/2
    while(l<=r){
        if(mid==1){
            if(spj()) r=mid-1;
            else l=mid+1;
        }
        else{
            if(check(mid)) r=mid-1;
            else l=mid+1;
        }
        mid=l+r>>1;//位运算，就等于(l+r)/2
    }
    printf("%lld\n",r+1);
    return 0;
}

```


---

## 作者：Daidly (赞：1)

最小化最大值，使用二分答案。

考虑 `check(x)` 函数：

- 若 $x$ 大于等于最大的连续段，返回可行。

- 寻找相同的段。

- 由于我们想要把当前这个段改成若干个连续段数小于等于 $x$ 的段，最小化“若干个”，所以考虑如何分割：

例如：

`NNNNNNNN`

$x=2,len=8.$

想要把这个长度为 $8$ 的连续段改成几个长度小于等于 $2$ 的连续段，先取出来一个 $2$：

`NNNNNN NN`

然后由于我们需要把前面的分割，所以最小化段数的方法是每一段 $2+1=3$ 个：

`NNF NNF NN`

若不能完全分完，则需要向上取整，所以把长度为 $len$ 的段分为最小的每一段都小于 $x$ 段数需要消耗 $\lceil\frac{len-x}{x+1}\rceil$。

向上取整代码：

`ceil(a/b)=(a+b-1)/b`。

所以即为：

`(len-x+x)/(x+1)=len/(x+1)`

- 遍历一遍字符串，把代价求和，判断是否小于等于 $k$ 即可。

### 坑

若按照上面思路写，似乎只能得到 $28$ 分，hack 数据如下：

```cpp
4 1
FNNF
```
按上文思路会输出 $1$，可是不行，所以我们要特判答案为 $1$ 的情况：

`NFNFN······FNFNF`

`FNFNF······NFNFN`

把修改成上面那样的两种统计一下次数，判断是否小于等于 $k$ 即可，当然也可以统计一个，另一个是灯数减去这一个。

具体细节可参考代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*f;
}

inline void print(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)print(x/10);
	putchar(x%10^48);
}

const int MAXN=1e5+5;
char a[MAXN];
int n,k,maxn,tmp;

bool check(int x){
	if(x>=maxn)return 1;
	int sum=0,len,tmpk=0;
	for(int i=1;i<=n;++i){
		tmp=i;
		while(a[tmp]==a[tmp+1])tmp++;
		len=tmp-i+1;
		if(len>x)tmpk+=len/(x+1);
		i=tmp;
	}
	if(tmpk>k)return 0;
	return 1;
}

int main(){
	n=read(),k=read();
	cin>>a+1;
	for(int i=1;i<=n;++i){
		if((a[i]=='N'&&(i&1))||(a[i]=='F'&&(!(i&1))))tmp++;
	}
	if(tmp<=k||n-tmp<=k){
		puts("1");
		return 0;
	}
	for(int i=1;i<=n;++i){
		tmp=1;
		while(a[i]==a[i+1])i++,tmp++;
		maxn=max(maxn,tmp);
	}
	int l=2,r=n,mid,ans;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid))ans=mid,r=mid-1;
		else l=mid+1;
	}
	print(ans);
	return 0;
}
```
如果对您有帮助就点个赞呗。

---

