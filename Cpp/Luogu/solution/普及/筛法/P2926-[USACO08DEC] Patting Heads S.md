# [USACO08DEC] Patting Heads S

## 题目描述

今天是 Bessie 的生日，正是玩派对游戏的好时机！Bessie 指示编号为 1 到 N 的 N 头奶牛（1 <= N <= 100,000）围成一个圆圈坐下（因此奶牛 i [除了两端] 坐在奶牛 i-1 和 i+1 的旁边；奶牛 N 坐在奶牛 1 的旁边）。与此同时，Farmer John 往一个桶里装了一十亿张纸条，每张纸条上都写着一个范围在 1 到 1,000,000 之间的整数。

每头奶牛 i 然后从这个巨大的桶中抽取一个数字 A\_i（1 <= A\_i <= 1,000,000）（当然，这个数字不一定是唯一的）。轮到每头奶牛 i 时，她会绕着圈走一圈，拍所有其他奶牛 j 的头，只要她的数字 A\_i 能被奶牛 j 的数字 A\_j 整除；然后她回到原来的位置坐下。

奶牛们希望你帮助她们确定，对于每头奶牛，她应该拍多少头其他奶牛的头。



## 说明/提示

5 头奶牛分别被赋予数字 2、1、2、3 和 4。


第一头奶牛拍了第二和第三头奶牛；第二头奶牛没有拍任何奶牛；等等。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
5 
2 
1 
2 
3 
4 
```

### 输出

```
2 
0 
2 
1 
3 
```

# 题解

## 作者：zhukewen123 (赞：218)

# 本蒟蒻的一篇题解~~~
由于本题纯暴力枚举会炸的

所以应该采用一种特殊方法

思路分析:首先使用一个b数组来存储奶牛手上数字出现的次数,比如数字是3,那么b[3]++,数字是2,就b[2]++.然后列举奶牛手上的所有数字i,如果他们的倍数j也在b数组中,就用一个cnt数组记录,即cnt[ixj]++,代表有数字i*j的奶牛可以拍手上数字为i的奶牛的头.举个例子,奶牛数字2,4,6,若i是2,那么它的整数倍为j为2,4,6,8,10......发现奶牛有2,4这两个数字,那么cnt[4]++,cnt[6]++.然后i=4,i=6不断往后推即可......最终输出cnt[奶牛数字]即可.

### 代码如下
```
#include<bits/stdc++.h>
using namespace std;
int a[10000005];
int n,mx=-100;
int b[10000005];
int cnt[10000005];
void get_factor(){
    for (int i = 1;  i <= 10000000; i++){
    	if(!b[i]) continue;//奶牛数字中必须有i
    	for (int j = 1; j <= 10000000 / i; j++){
    		 if(b[i*j]) cnt[i*j]+=b[i];
    		 if(i*j==i) cnt[i]--;
             //防止奶牛拍自己的头QWQ
        }   	
    } 
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        b[a[i]]++;
    }
    get_factor();
    for(int i=1;i<=n;i++)
        cout<<cnt[a[i]]<<endl;
    //华华丽丽的输出
} 
```
### 求过QWQ~~~
看懂了不要忘了点赞哦QWQ

---

## 作者：AMSDE (赞：41)

一拿到这道题，肯定会想到N^2的想法，就是从1到n扫i，再从1到n扫j，最后check一下，累计答案。但这样肯定会WA，所以就会想到提前构造答案。

我们可以从1到Max{a[i]}开始刷，凡是这个数的倍数，那么答案就加上它的个数。记住，最后要把自己本身减去。

时间O(MAXN\*MAXN)，但其实只是O(N\*sqrt(MAXN))或更少，绰绰有余。

最后附上代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,Max,a[100005],num[1000005]/*记录每个数字出现的个数*/,ans[1000005]/*记录每个数字的答案*/;
inline int read(){//读数据 
    int N=0;char ch=getchar();
    while (ch>'9'||ch<'0') ch=getchar();
    while (ch>='0'&&ch<='9') N=N*10+ch-'0',ch=getchar();
    return N;
}
int main()
{
    n=read();
    for (int i=1;i<=n;i++) a[i]=read(),num[a[i]]++,Max=max(Max,a[i]);
    for (int i=1;i<=Max;i++){//开始构造答案 
        if (num[i]==0) continue;//如果这个数字不存在，则跳过 
        for (int j=i;j<=Max;j+=i) ans[j]+=num[i];//i能被j除就把ans[j]加上num[i]，累计j的答案 
    }
    for (int i=1;i<=n;i++) printf("%d\n",ans[a[i]]-1);//最后输出，记得把自己本身减去 
    return 0;
}
```

---

## 作者：Garrison (赞：30)

这道题很容易想到用o(n^2)的方法，但是时间上肯定是不行的。所以要用一种筛选的方法。

86分的方法：

1、在输入的时候找到其中的最大值。将所有数存入数组。
```
for(int i=1;i<=n;++i){
        cin>>a[i];
        m=max(m,a[i]);
    }
```
2、从1~n挨个开始，将数组中的数的每个倍数(为了节约时间，要<=所找到的最大值)都加上1。
```
 for(int i=1;i<=n;++i){
        for(int j=1;j*a[i]<=m;++j)
            ++ans[j*a[i]];
    }
```
3、最后输出每个数的因子出现个数-1。
```
for(int i=1;i<=n;++i){
        cout<<ans[a[i]]-1<<endl;
    }
```
PS：减去1是因为它自己也算自己的因子(重复了)


**100分的做法**

前言：因为每一个数有重复的，所以在找倍数的时候可以加上一个小的优化，不要每次加一，就一次性加上重复出现的次数就好了。为了更好地实现，我们可以设一个桶，输入时处理
```
	cin>>a[i];
	++b[a[i]];
```
然后每次就加
```
	ans[j*i]+=b[i];
```
下面双手奉上完整代码(其实叫86分的而言只有一点点小小的改动)

```
#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define M 1000005
int a[N];
int m,n;
int ans[M],b[M];
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		++b[a[i]];
		m=max(m,a[i]);
	}
	for(int i=1;i<=m;++i){
		if(b[i]!=0)
			for(int j=1;j*i<=m;++j)
				ans[j*i]+=b[i];
	}
	for(int i=1;i<=n;++i){
		cout<<ans[a[i]]-1<<endl;
	}
	return 0;
}

```
 _~~说实话，我都没觉得我能过这道较为**弱智**的题~~_ 


---

## 作者：Aragron_II (赞：15)

### [P2926](https://www.luogu.com.cn/problem/P2926) 题解


------------
#### 做法1：

暴力枚举，但时间复杂度为：
$$ O(n^2) $$


无法通过本题。


------------

#### 做法2：

从枚举约数的角度思考，对于每个数 $ a[i] $ 枚举它所有的约数，然后看这些约数在 $ n $ 个数中出现了多少次，对其求和，最后输出；但时间复杂度为：
$$ O(n\sqrt{\smash[b]{A}}) $$

开 $ O2 $ 也无法通过。


------------

#### 做法3（正解）：

从枚举倍数的角度思考：对于一个数 $ i $ 若它在原数组中出现了 $ c[i] $ 次，那么 $ i $ 这个数会对它的每一个倍数产生 $ c[i] $ 的贡献。这样就可以通过查询这样产生的贡献的总和来计算答案了，其时间复杂度为：
 
$$ O(nlogn) $$

时间复杂度不高，不用开 $ O2 $ 即可通过。

### 代码：
```
#include <bits/stdc++.h>
using namespace std;
const int Maxn=1000100;//数组大小
const int Bignumber=1000000;
int n,a[Maxn],c[Maxn],w[Maxn];//n个数，数列，数字统计容器，贡献值
int main() {
	scanf("%d",&n);//输入
	for(int i=1;i<=n;i++) {
		scanf("%d",&a[i]);//输入数列
		c[a[i]]++;
	}
	for(int i=1;i<=Bignumber;i++) 
		for(int j=i;j<=Bignumber;j+=i)
			w[j]+=c[i];//i这个数会对j产生c[i]的贡献
	for(int i=1;i<=n;i++) 
		printf("%d\n",w[a[i]]-1);//输出时要把a[i]对自己的贡献减去
	return 0;
}
```


---

## 作者：smzzl (赞：11)

先用桶把牛装起来

对于每一头牛，sqrt（N）时间枚举它的因子统计答案即可

注意特判完全平方数

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int n;
int bac[1000005],a[100005];
int main()
{
	cin>>n;
	for (int i=1;i<=n;i++) cin>>a[i],bac[a[i]]++;//装桶
	for (int i=1;i<=n;i++){
		int ans=0;
		bac[a[i]]--;//防止算自己
		for (int fac=1;fac<=sqrt(a[i]);fac++) if (a[i]%fac==0)//如果是因数就统计答案{
			ans+=bac[fac]+bac[a[i]/fac];
			if (fac==a[i]/fac) ans-=bac[fac];//特判完全平方数
		}
		bac[a[i]]++;
		cout<<ans<<endl;
	}
}
```

---

## 作者：countryhope_lzc (赞：6)

### 水了一发数论题（近两周来唯一一道自己写的题）
   这道题是放在一本通的质数那一章的习题（蒟蒻不太明白，这题和质数有毛线关系，可能是用到了筛的思想）
   
### 好了，进入正题

 #### 法一：
         暴力模拟
         时复度：O(n^2);
         这个复杂度在1e6的数据下肯定爆。
 #### 法二：
       考虑到Ai<=1e6,Ai=x*y,其中x,y中必有一个小于等于sqrt（Ai）。
    根据题意，只要Ai可以整除Aj那么ans[i]就++。
    所以我们可以统计每个Ai有几个，有一个Ai就令g[Ai]++。
    sqrt(Ai)又很小，所以我们就枚举x，算出y，
    若x与y合法
         ans[i] += g[x]+g[y];（其中x==y时只加一个）
    最后，ans[i]-1,(因为你自己拍了自己那下要减掉)。
   时间复杂度：O（n*sqrt(Aimax)） 实际不会达到这么大，所以足够了。
   
   
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e6+5;

int a[N];
int ans[N];
int g[N];
int n;

int main(){
//	freopen("123.txt","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        g[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        for(int x=1;x<=sqrt(a[i]);x++){
            int y = a[i]/x;
            if(x*y!=a[i])continue;
            if(x!=y) ans[i] += g[x],ans[i] += g[y];
            else ans[i] += g[x];
        }
    }
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]-1);
    return 0;
}
```

   
  萌新题解，求大佬指教，也求luogu给过。
  
  

---

## 作者：Constant (赞：4)

# 题意归纳

给出一个数列，对于第 $i$ 项 $Ai$ ，看数列中有多少个数是他的约数。


# Solution

算法1 暴力：

枚举任意两个数，判断是否有约数关系，统计个数。

时间复杂度 $O(N^2)$ 。对于 $N=10^6$ ，显然超时。

算法2 因子范围优化：

我们知道，判断质数时只需要到： $sqrt(N)$ 进行判断（证明不细讲）。

故对于这道题，数组 $vis$ 记录一下每个数字出现的次数。

在 $sqrt(N)$ 中寻找约数，找到后，判断是否在数列中即可。

易错警示：

 一.对于完全平方数：
 
 $ans=ans+vis[p]+vis[a[i]/p]$ 时。

会将一个数出现的次数加两次，重复，故减去一次。

二.每次计算会拍到自己的头（自己也是自己的约数），故也减去一次。


下面上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,vis[1000010],a[1000001],ans[1000001];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        vis[a[i]]++;
    }
    for(int i=1;i<=n;i++)
    {   
        for(int j=1;j*j<=a[i];j++)      
        {
            if(a[i]%j==0)
            {
                ans[i]+=vis[j]+vis[a[i]/j];
                if(j==a[i]/j) 
                {
                    ans[i]-=vis[j];
                }
            }
        }
        ans[i]--;
    }

    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    return 0;
}
```

---

## 作者：Ofnoname (赞：3)

并没有发现这道题和标签“质数判断，筛法”有什么关系。

在$N<=10^5$的的数据范围下，$O(N^2)$的暴力算法显然不能通过。

## 优化一：减少重复计算

显然，对于同样的数，它们的答案应该是一样的。数字本身范围M的范围只有10000000，所以我们可以开一个桶来记录每个数出现的次数，每种数统计一次答案。比如样例中有两个2，即$T[2]=2$，那么我们只用计算一次2的答案即可。

## 优化二：使用倍数统计

如果对每个数花$O(\sqrt N)​$的时间统计它的因子，一共将花费$O(N\sqrt N)​$的时间。但如果我们反过来考虑，每个数n，显然会被自己的倍数n,2n,3n....摸一次，所以只要从小到大考虑n,把它的倍数n,2n,3n...都加上$T[n]​$就可以了，时间效率为$O(N+\frac N2+\frac N3+...)=O(NlogN)​$，可以通过本题。

要注意自己可以摸相同数值的人，但是不能摸自己，而“自己”也被统计在$T[n]$里了，所以答案还需要减1。

```cpp
#include <bits/stdc++.h>
#define MAXN (100000+10)
#define MAXM (10000000+10)
using namespace std;

char io[MAXM],*p1=io,*p2=io;//快读
int N,Max,d[MAXN],T[MAXM],ans[MAXM];//Max即最大的数值,T即桶

inline char Getchar()
{
	return getchar();
	if (p1==p2)
		p2=(p1=io)+fread(io,1,MAXM,stdin);
	return (p1==p2)?EOF:*p1++;
}

inline void read(int &a)
{
	register char c=Getchar();
	for (a=0; c<'0'||'9'<c; c=getchar());
	for (; '0'<=c && c<='9'; c=getchar())
		a=a*10+(c^48);
}

int main()
{
	read(N);
	for (register int i=1; i<=N; i++)
	{
		read(d[i]);
		T[d[i]]++;
		Max=(Max>d[i])?Max:d[i//读入，映射，更新最大值
	}
	for (register int i=1; i<=Max; i++)
	{
		if (!T[i]) continue;
		for (register int x=i; x<=Max; x+=i)
			ans[x]+=T[i];//查找i的所有倍数
	}
	for (register int i=1; i<=N; i++)
		printf("%d\n",ans[d[i]]-1);//减1输出
	return 0;
}
```



---

## 作者：RainFestival (赞：3)

基本上不需要优化，求约数即可

把每个奶牛的数字存进一个桶里

然后枚举约数

把约数加入s就可以了

注意自己不拍自己头

所以输出时要-1

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int a[100005],b[1000005];
int main()
{
	int n;
	cin>>n;
	for (int i=1;i<=n;i++)
	  {
	    cin>>a[i];
	    b[a[i]]++;
	  }
	//for (int i=1;i<=10;i++)
	  //cout<<b[i]<<endl;
	for (int i=1;i<=n;i++)
	  {
	  	int s=0;
		for (int j=1;j<=sqrt(a[i]);j++)
	      if (a[i]%j==0) s=s+b[j]+b[a[i]/j];
	    if ((int)sqrt(a[i])*(int)sqrt(a[i])==a[i])
	      s=s-b[(int)sqrt(a[i])];
	    cout<<s-1<<endl;
	  }
	return 0;
}
```

---

## 作者：itandsoon (赞：2)

数据比较大，所以暴力枚举不可行

具体的解法在做的时候让我联想到了**线性筛素数**，就是通过已知的限制去推出可能的所有情况，而不是逐个枚举验证。

我们不需要一个一个去验证所给的数据里面有多少符合的答案，而是用所给的数据去实现一种**对答案的贡献**，即枚举出所有该答案的倍数，那么记录该贡献即可。在枚举过每一个输入数据后，对于一个数来说，它所拥有的贡献的总合就是要求的答案

```c
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
#include<string>
#define m 1000000
using  namespace std;
int ans[m+5],A[m+5],re[m+5];
queue<int>Q;
inline int read() {//数据比较大，通过快读加快速度
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    } 
    while('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}
int main()
{
    int n;
    n=read();
    for(int i=0;i<n;i++)
    {
        int num;
        num=read();
        A[i]=num;
        if(!re[num])Q.push(num);//防止重复相同的数
        re[num]++;//记录每个数能够提供多少贡献
    }
    while(!Q.empty())
    {

        int k=Q.front();
        Q.pop();
        for(int j=k;j<=m;j+=k)
        {
            ans[j]+=re[k];//记录每一个数k的倍数接受的贡献值
        }
    }
    for(int t=0;t<n;t++)
    {
        cout<<ans[A[t]]-1<<endl;//查询，去除自身
    }
}
```


---

## 作者：SUNCHAOYI (赞：1)

**这道题若两层循环i，j，然后扫一遍判断，就会TLE一半的点。错误代码如下：**
```
#include <iostream>
using namespace std;
const int MAX = 100000; 
int a[MAX],ans[MAX] = {0};
int main()
{
	int n;
	cin>>n;
	for(int i = 0;i < n;i++) cin>>a[i];
	for(int i = 0;i < n;i++)
		for(int j = 0;j < n;j++)
			if(i != j && a[i] % a[j] == 0) ans[i]++;
	for(int i  = 0;i < n;i++) cout<<ans[i]<<endl;
	return 0;
}
```

------------

**那怎样才能AC呢？我们尝试做一些操作：**

1.首先设ans[i]为数字为i的奶牛的会拍头的次数

2.再设一个vis数组，vis[i]表示数字为i的奶牛个数，初始化均为0。每输入一个数，便vis[i]++，表示多了为i的奶牛。同时，需要一个变量记录最大的数字

3.循环，i为当前为i数字的奶牛，j从i开始循环，一直到最大数。注意，如果vis[i] = 0，即没有这个数字的奶牛，便不需这次循环。

4.答案的累加怎样实现呢？十分简单：
```
ans[j] += vis[i];
```
5.最后输出答案，由于1的设置，只需
```
ans[a[i]]
```
就是答案了！

#### 但是，这样对吗！！！

**还需要减一再输出，因为自己不需要拍自己哦！（重点在此！）**

------------

**100Code如下：**
```
#include <iostream>
using namespace std;
const int MAX = 1000001; 
int a[MAX],ans[MAX] = {0},vis[MAX] = {0},n,m = -1;
int main()
{
	cin>>n;
	for(int i = 1;i <= n;i++)
	{
		cin>>a[i];
		m = max(a[i],m);//记录最大的数字 
		vis[a[i]]++;
	}
	for(int i = 1;i <= m;i++)
	{
		if(vis[i] == 0) continue;//不存在 
		for(int j = i;j <= m;j += i) ans[j] += vis[i];//累计答案 
	}
	for(int i  = 1;i <= n;i++) cout<<ans[a[i]] - 1<<endl;//除去自己后输出 
	return 0;
}
```

---

## 作者：jingkongwanglimiaoa (赞：0)

~~蒟蒻又来水沝淼㵘题解辣~~

一看到这一题，蒟蒻就想到乐两个字：暴力

一个数一个数地除，时间复杂度为$O(n^2)$,而 $n$最大为$100000$

暴力梦破碎乐

那就让蒟蒻搬出~~某高端大气上档次的编程书上的~~并辅以详细的代码解释

代码如下$↓↓↓$
```cpp
# include <cstdio>//头文件
# include <iostream>
using namespace std;
# define maxn 1000010
int n,a[maxn],w[maxn],c[maxn];//a数组用来存输入的数据，w数组用来存 i 能被多少数整除,c数组用来存i出现乐多少次
int main()
{
	scanf("%d",&n);//输入
	for (int i = 1;i <= n;i++)
	{
		scanf("%d",&a[i]);//输入
		c[a[i]]++;//存多少次
	}
	for (int i = 1;i <= 1000000;i++)//一个数一个数的枚举
		for (int j = i;j <= 1000000;j += i)//找出所有i的倍数
			w[j] += c[i];// i的倍数（即j）要加上i出现的次数
	for (int i = 1;i <= n;i++) printf("%d\n",w[a[i]] - 1);//要-1是因为奶牛不能拍自己（即a[i]不能被a[i]自己整除）
}
```

注：a整除b表示 b % a == 0

很多东西前面的题解都有，那就让蒟蒻讲讲一些难理解的问题吧~~可能只有被蒟蒻才觉得难理解~~

$1.$c数组为什么要存一数出现乐多少次

a:如数据为 

$5$

$2$  $1$  $1$  $1$  $1$

$1$能整除$2$，而出现乐$4$个$1$.因此输出应为

$4$ $0$ $0$ $0$ $0$

同时c数组还有个很重要的作用是判断该数有妹有出现过

若$c[i] == 0$表示 $i$妹有出现过，则i 的 倍数 j += 0

$2.$为什么$j$ 要直接 += $i$

因为第二层循环找的是 i 的 倍数,只有是i的倍数且i出现过才加

### 一些~~废话~~奇妙的东西：蒟蒻的伪优化

真的是**伪**优化呢

分析完刚才那份代码，可能有一些奇妙的想法在你脑子里出现乐~~可能只有本蒟蒻才~~

是的，你会发现那个$1000000$是辣么的碍眼

一个大胆的想法出现乐：在输入的时候存个maxx，表示这堆数字的最大值

这是因为a数组里的数可能很小，a数组里最大的数到1000000中做的运算全浪费乐

当蒟蒻满怀信心地交上去时，奇迹出现乐，总耗时真的小乐一倍！

但仔细一看发现不对，有的测试点是比原来的耗时高很多的

蒟蒻思考乐很久，终于想出来乐，比如

$2$

$1$ $1000000$

你看这个maxx做乐跟没做有区别吗？

最终只会在比较上多花时间

而原解的耗时比较稳定，显然更优

另外还有一种伪优化，看那个第一层循环

本蒟蒻不自觉地想到：直接枚举$a[i]$就好了嘛，干嘛枚举$1 - 1000000?$连c数组都省乐

轻松卡掉这个伪优化的数据↓

$100000$

$1000000$ $1$ $1$ $1$ $1$ $...$ $1$

这也是c数组的作用之体现


另外还有一些乱七八糟的伪优化，都被输出所限制乐，因为你不能改变原数组的顺序~~如果可以是因为本蒟蒻想不到~~

废话乐那么多，主要就是为乐大家别踩坑

~~同时这也证明乐，某高端大气上档次的编程书的题解大部分都是最优的~~

啧打乐好多字

---

## 作者：genshy (赞：0)

# 题目大意

给我们一些数，问我们在这些数中，除了他本身，他的约数一共出现多少次。

# 解法

输入时开个桶记录每个数出现的个数。然后从 $1$ 开始枚举，枚举到 $sqrt（n）$ ，看枚举的数能否被他整除，能整除的话，统计答案。

# 坑点

1. 完全平方数只能被算一次
1. 计算当前这个数是，要减去他本身。

# 代码

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
long long n,maxn,a[1000010],num[1000010],ans[1000010];
int main(){
	scanf("%lld",&n);
	for(int i = 1; i <= n; i++){
		scanf("%lld",&a[i]);
		maxn = max(maxn,a[i]);
		num[a[i]]++;
	}
	for(int i = 1; i <= n; i++)
    {
		for(int j = 1; j <= sqrt(a[i]); j++)
        {
			if(j * j == a[i]) ans[i] += num[j];
	    	else if(a[i] % j == 0)
            {
				ans[i] += num[j];
				ans[i] += num[a[i]/j];
			}
		}
	}
	for(int i = 1; i <= n; i++) printf("%lld\n",ans[i]-1);
	return 0;
}
/*

*/
```
以前的代码没换行，太丑了只能重新再打一遍（~~滑稽~~）

---

