# [BalticOI 2009] Radio Transmission 无线传输

## 题目描述

给你一个字符串 $s_1$，它是由某个字符串 $s_2$ 不断自我连接形成的（保证至少重复 $2$ 次）。但是字符串 $s_2$ 是不确定的，现在只想知道它的最短长度是多少。

## 说明/提示

#### 样例输入输出 1 解释
对于样例，我们可以利用 $\texttt{abc}$ 不断自我连接得到 $\texttt{abcabcabcabc}$，读入的 $\texttt{cabcabca}$，是它的子串。

#### 规模与约定
对于全部的测试点，保证 $1\le L \le 10^6$。

## 样例 #1

### 输入

```
8
cabcabca```

### 输出

```
3```

# 题解

## 作者：LYYY (赞：296)

刚学了KMP算法见到这道题，完全没有思路，但是真的想出来了之后，真的对KMP算法中的next数组有了更深的认识。



------------


------------


 _按照题意，读入字符串长度n和字符串ss_ ；
 
 

这道题求的是字符串ss最小长度的循环，我们称之为“**ss的循环子串**”，首先引入结论：
## ans=n-next[n]

------------

现在解释为什么答案是 n-next[n] ：

![https://cdn.luogu.com.cn/upload/pic/51890.png](https://cdn.luogu.com.cn/upload/pic/51890.png)

一、
先求出next数组（~~其实只求出next[n]就行了~~），即求出字符串的最大公共前后缀；

假设这两段是整个字符串ss的最大公共前后缀；

第一段： 1~next[n]

第二段： n-next[n]+1~n

为了方便观察，我将前缀和后缀分开，令它们上下一一对应； 

![https://cdn.luogu.com.cn/upload/pic/51892.png](https://cdn.luogu.com.cn/upload/pic/51892.png)

二、
现在我们人为地把字符串按照红色段的长度划分为若干段并标号（图中的第1,2,3,4,5,6,7,8,9段）；

容易看出，红色的一段和后缀合起来就是原字符串；

### 所以推出：

**1. 因为上下对应相等，故第1段等于红色段；**

**2. 因为是公共前后缀，故第2段等于第1段；**

**3. 因为上下对应相等，故第3段等于第2段；**

**4. 因为是公共前后缀，故第4段等于第3段；**

**5. ......**

**6. 红色段就是循环子串；**

三、从而，我们知道了原字符串ss除去公共前后缀（图中的黑色段）中的一个剩下的就是循环子串（图中的红色段）；同样，易知原串ss除去开头（或结尾）的循环子串（图中的红色段）剩下的部分就是公共前后缀（图中的黑色段）。

至此，问题中要求的原字符串ss的**最小循环子串**，就转化成了求原字符串ss的**最大公共前后缀**；

因此，有 **ans=n-next[n]** 。

AC代码（kmp数组即next数组）

```cpp
#include<cstdio>
using namespace std;
const int maxn=1111111;
int n,kmp[maxn];//kmp数组即next数组
char ss[maxn];
int main()
{
	scanf("%d%s",&n,ss+1);
	int j=0;
	for(int i=2;i<=n;++i)
	{
		while(j&&ss[i]!=ss[j+1]) j=kmp[j];
		if(ss[i]==ss[j+1]) ++j;
		kmp[i]=j;
	}
	printf("%d",n-kmp[n]);
	return 0;
}
```

谢谢阅览

---

## 作者：lei_yu (赞：87)

刚学KMP，理解之后感觉对整个人都 **升华** 了。


------------

首先看字符串是整周期的例子，例如一个字符串$ababababab$，$ab$就是一个周期，最长公共前后缀如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/cknym26m.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

对于答案$N-next[N]$可以这样理解：从字符串的某一处开始到串末，和串首到某一处是完全相等的，其中最长的就是最长公共前后缀（若有不适稍微坚持一下）。

具体到那个例子就是1~8和3~10完全相等。

**头脑风暴：  
第一个周期和第二个周期完全相等（1~2和3~4），  
第二个周期又和第三个周期完全相等（3~4和5~6）。  
......  
既然相等当然就可以匹配了  
也就是最长公共前后缀就是第1个周期开始到第2个周期   
然后是第2个周期到第3个周期  
......**

因为不可能第一个周期自己和自己匹配，就算一个周期中间有公共前后缀（例如abacaabaca，周期为abaca），也不可能后面完全匹配（例子中的第6个字符和第2个字符失配了）。

就算真的有，那么就表明有更短的周期（KMP会自己克服的）

**那么最长公共前后缀就是第 $1.2.3.4$ 个周期和第 $2.3.4.5$ 个周期,也就是前缀不包含最后一个周期，后缀不包含第一个周期。**

**那么就很好理解了：字符串的长度减去这个周期的长度就是一个周期的长度（相当于第一个周期），便有了$N-next[N]$这个公式。**

具体到那个例子就是1~2（或者9~10）是一个完整的周期。

（你成功一半了加油！ヾ(◍°∇°◍)ﾉﾞ）

------------

万一不是整周期呢？答案依然是成立的。

例如这个字符串cabcabca（周期可以看做abc），如图所示：
![](https://cdn.luogu.com.cn/upload/image_hosting/v1y85ooc.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

从字符串的某一处开始到串末，和串首到某一处是完全相等的，其中最长的就是最长公共前后缀。我们首先将第一个c看做第0个周期的最后一个字符。

**头脑风暴二号：  
第0个周期的最后一个字符c和第1个周期的最后一个字符c相等，  
第一个周期和第二个周期相等，  
第二个周期的前两个字符和第三个周期的前两个字符相等。**

既然相等，那么我们又可以进行匹配了......


（是不是有点感觉）

**这里的最长公共前后缀就是：  
第0个周期的最后一个字符c、第一个周期以及第二个周期的前两个字符  
和第一个周期的第最后一个字符c、第二个周期以及第三个周期的前两个字符**

和前面说的一样，最长公共前后缀的不可能在一个周期里面自己匹配，否则就有更短的周期。

于是KMP算法就会从（第0个周期的最后）一个字符c和第一个周期的最后一个字符c开始匹配，正好就会空出一个完整的周期cab，仅仅是顺序不同。

（KMP算法如此强大，如果还不理解可以再多想想）


------------

代码贴不贴都无所谓了
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int size1,nex[1000001],j;
char s1[1000001];
int main()
{
  
	cin>>size1;
	cin>>s1+1;
	j=0;
	for(int i=1;i<=size1;i++)
	{
		if(s1[j+1]!=s1[i+1]&&j>0)j=nex[j];
		if(s1[i+1]==s1[j+1])
		nex[i+1]=++j;
	}
	cout<<size1-nex[size1]<<endl;
}
```


------------
做完这道题别慌着走，这里还有几道题供您使用

**[UVA10298](https://www.luogu.com.cn/problem/UVA10298)**

**[P2445](https://www.luogu.com.cn/problem/P2445)**

---

## 作者：Caicz (赞：28)

> **刚学完KMP不到1小时就来做这道题，本题对next数组的理解和运用很巧妙**

+ 刚一做题，第一思路是先求出整条串的next值，然后从小到大枚举**for(i=2;i<=n;i+=2) 当i=2 * next[i]时，输出此时的next值**
> 但是该思路对以下两种情况无法处理
>> 1. 给定字符串为单个字符时 **例： 1 a**  此时的next数组全为0无法解决
>>
>> 2. 还是直接举例: **8 aabaabaa** 此时若用以上算法，会将最小循环子串误判长度为 1
+ 所以，我们就得从next数组中找规律
+ 设最小循环子串长度为 x，那么可以得到next[x]==0;
> 证明：
>> 如果next[x]==len（0<len<x）,那么就有s[len]==s[x];
>> 
>> 那么去掉s[x]后得到的[1,x-1]依旧是原串的循环子串，因为 x 为最短长度，所以可得 next[x]一定为0;
>>>证毕；
+ 所以我们可以推论得到**next[x+1]==1; next[x+2]==2...**
+ 最终得到 **nxet[n]==n-x**

所以最终我们的答案即为 **n-next[n]**

代码：
```cpp
#include<stdio.h>
#include<iostream>
#include<cstring>
using namespace std;
int n,len,next[1000005];
char s[1000005];

int main()
{
	scanf("%d %s",&n,s+1);
	int t1=0,t2;
	next[0]=t2=-1;
	while(t1<=n)
	{
		if(t2==-1||s[t2+1]==s[t1+1])
			next[++t1]=++t2;
		else
			t2=next[t2];
	}
	printf("%d",n-next[n]);
	return 0;
}
```


---

## 作者：scp233 (赞：25)

首先，这题应该用KMP做（建议先做P3375的模板题）  
样例的说明其实有些难以理解，把'abc'换成'cab'自我复制会更好理解一点  
题目保证是由某个字符串自我复制的，我们可以利用这一点来做，即利用这种“复制串”的特性，  
也就是：设最短的长度为x，那么前x个next数组的值为0（什么是next数组请参考模板题），next[x+1]=1，next[x+2]=2,以此类推（为什么是这样，大家可以对着样例看看就懂了）因此，n-next[n]就是x的值

直接放程序吧……
```cpp


#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
#include<map>
#include<queue>
#define rep(a,b,c) for(int a=b;a<=c;a++)
#define drp(a,b,c) for(int a=b;a>=c;a--)
#define HY 7006
#define lo long long
#define qword unsigned long long
#define mod 1000000007
#define maxlongint 2147483647
#define PI 3.141592653589793238462643383279
#define INF 0x3f3f3f3f
using namespace std;

char ch[1000006];
int j,n,a[1000006];

int main(){
  cin>>n;
   scanf("%s",ch+1);
  
   rep(i,2,n){
    j=a[i-1];
    while(j&&ch[j+1]!=ch[i]) j=a[j];
    if(ch[j+1]==ch[i]) j++;
    a[i]=j;
   }
   
 cout<<n-a[n];
return 0;
}


```

---

## 作者：柏木由纪AKB48 (赞：18)

就像noip2017第一题一样

不是所有人都能打表发现规律的，更何况是在考场上用严谨的证明来验证猜想，所以也应该有通用的解法，本题通用的解法我认为就是倍增

用倍增来完全模拟全过程即可得出解答，没错，就是这么暴力

就拿输入样例来说

cabcabca

next为：00012345
我们发现next[6]=3 next[6]*2==6

这里正好被两段相同的循环节给覆盖，所以给出一个长度为lenght的循环节，该循环节值得一试的条件是  next[2 x lenght] x 2>=lenght x 2

当然当循环节长度超过总长度时可以直接 lenght+next[n]==n 来判定

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char b[1000005];
int next[1000005],n,flag;
void getnext(){
    for(int i=2,j=0;i<=n;i++){              
    	while(j&&b[i]!=b[j+1]) j=next[j];
    	if(b[i]==b[j+1]) j++;
    	next[i]=j;
    }
}
int main(){
	scanf("%d",&n);
	scanf("%s",b+1);
    getnext();
    for(int i=2;i<=n;i+=2){
    	flag=1;
    	if(next[i]*2>=i){
    		int len=i/2,p=i;
    		for(;p<=n;p*=2){
    			if(next[p]*2<p){
    				flag=0;break;
				}
			}if(flag==0) continue;
			if(p>n) p/=2;p=p+1;int u=1;
			for(p;p<=n;p++){
				if(b[p]!=b[u]){
					flag=0;break;
				}
				u++;
				if(u>len) u=1;
			}if(flag==0) continue;
			printf("%d\n",len);
			return 0;
		}
	}
    for(int i=n/2;i<=n;i++){
    	if(next[n]+i==n){
    		printf("%d",i);
    		return 0;
		}
	}	
	return 0;
}
```


---

## 作者：功在不舍 (赞：14)

KMP的模板题已经不让发题解了，难受。

我发现网上的KMP大多是从匹配挪动开始讲的，说实话我没听懂。这里我来讲一下静态角度看KMP。

记号：pre(s,i) 指s串的前i个字符构成的前缀，suf(s,i) 指s串的后i个字符构成的后缀。

1.Border与周期

 周期定义：$ 0<p<|s|$ 且 $ s[i]=s[i+p] ,\forall i \in \{ 1,2,...,|s|-p\}$
 
 这个定义其实和数学里的函数周期定义差不多。
 
 注意Border的长度不允许是自己，周期也不允许是0！
 
 Border：$ 0<r<|s|,pre(s,r)=suf(s,r) $，则$pre(s,r)$为s的一个Border（其实就是即在头，又在尾）
 
  不难发现 $pre(s,k)$为s串的Border$\iff |s|-k$是s的周期
  
  因为$ s[i]=s[i+|s|-k] ,\forall i \in \{ 1,2,...,|s|-(|s|-k)\}$ 其实就是$pre(s,k)=suf(s,k)$
  
我们继续研究一下Border有什么性质
 
 2.Border的传递性以及强传递性
 
 Border的本质是前缀和后缀相同，可以发现两个性质。
 
 Border的传递性：s为t的Border，t为r的Border，则s也是r的Border
 
 Border的强传递性：s为r的Border，长于s的串t也是r的Border，则s是t的Border。
 
 这两句话证明很简单，留给读者自己想（自己画画图）。
 
 由上面两条，能得到记mb(s)为s的最长Border长度，那么pre(s,mb(s)),pre(s,mb(mb(s))),pre(s,mb(mb(mb(s))))......构成了s串的所有Border。
 
 原因：强传递性，s串的其他Border一定是最大Border的Border，
 mb(s)和mb(mb(s))之间不可能存在其他的Border，故每次找最大的一定不重不漏。 
 
 3.KMP-$next[i]$的定义
 
 KMP:给定模式串s和文本串t，求s在t中出现了多少次？
 
 讲了这么多Border的东西，你可能会想：这和KMP有啥关系？接着听就好了。
 
 还记得上面的mb(s)吗？我们发现，只要记录了每个前缀的最大Border的长度，就能的到整个串s的所有Border。
 
 定义:$next[i]=mb(pre(s,i))$即为长度为i的前缀的最大Border长度。现在该怎么求这$next[i]$数组呢？
 
假设$pre(s,j)$为$pre(s,i)$的Border，则$s[1 \ to \ j]=s[i-j+1 \ to \ i]$,那么显然有$s[1 \ to \ j-1]=s[i-j+1 \ to \ i-1]$且$s[j]=s[i]$，所以$s[1 \ to \ j]=s[i-j+1 \ to \ i]
\iff pre(s,j-1)$为$pre(s,i-1)$Border且$s[j]=s[i]$。

求$next[i]$时我们已经知道$next[1 \ to \ i-1]$。

假设$pre(s,i-1)$的所有Border长度为$k_1=next[i-1]>k_2>k_3>......$,求$next[i]$其实就是找到最大的$k_i$,使得$s[k_i+1]=s[i]$ 就是上面那个定理的过程
 
当然$pre(s,i) $可能没有Border,$next[i]=0$

我们通过把$next[0]=-1$来实现这个效果

以下是部分代码

 ```cpp
    next[0]=-1;next[1]=0;
	for(int i=2;i<=n;i++)
	{
		k=next[i-1];
		while(k!=-1&&s[k+1]!=s[i])k=next[k];
		next[i]=k+1;
	}
```
 
4.KMP-$next[i]$与匹配过程
 
 求出了$next[i]$ 数组有什么用？可以帮你快速找到一个前缀的所有Border。
 
 我们把满足$t[i-k+1 \ to \ i]=s[1 \ to \ k]$的 $k$ 称为 $i$位的一个匹配长度，其中最大的称为 $i$ 位的最大匹配长度，明显当$k=n$时，$i$位就匹配成功了。
 
怎么把最大匹配长度和Border关联呢？

假设$k_1<k_2$为i位的两个不同匹配长度，即$s[1\ to\ k_1 ]=t[i-k_1+1\ to\ i]$且$s[1\ to\ k_2 ]=t[i-k_2+1\ to\ i]$

由于$ s[1\ to \ k_1]$是$ s[1\ to \ k_2]$的前缀，$t[i-k_1+1\ to\ i]$是$t[i-k_2+1\ to\ i]$的后缀，可以发现$pre(s,k1)$是$pre(s,k2)$的Border！


所以，如果找到$i$位的最大匹配长度$k_0$,则所有的i位匹配长度为$k_0,next[k_0],next[next[k_0]]......$

由于 $s[1\ to \ k]=t[i-k+1\ to\ i]\iff s[1\ to \ k-1]=t[i-k+1\ to\ i-1]$且$s[k]=t[i]$ 

求i位的最大匹配长度的时候i-1位的最大匹配长度已经求得。

所以我们找到i-1位的一个尽量大的匹配长度k，使得$s[k+1]=t[i]$,就得到了i位的最大匹配长度，结合上面的定理，可以写出一个跳next实现的代码,若$k=n$则成功匹配。

 ```cpp
    k=0;
	for(int i=1;i<=m;i++)
	{
	    while(k!=-1&&s[k+1]!=t[i])k=next[k];
		k=k+1;
        if(k==n)js++,printf("%d\n",i-n+1);	
	}
 ```

 5.时间复杂度证明
   
   重点在于while循环到底执行了多少次。（AC自动机也类似）
   
   由定义可以知道$next[i]<i$，每一次执行while循环 $k$ 至少下降1且不能为负数，求$next[i]$和匹配的的时候，每次for循环k都只+1，所以while循环最多减少$O(m+n)$ 次，时间复杂度$O(m+n)$
   
6.殊途同归

   通过模拟我们可以发现，next其实就是帮我们在无法匹配时不要从头再来匹配，从而节省下复杂度的过程，我们最终和 网上的流行 版本 殊途同归，但是我认为这样讲解更能让人懂得KMP的精髓，还便于理解AC自动机里的fail指针：最长可识别后缀。

7.本题：求一个字符串的最小周期

见第一部分：Border与周期

求最小周期 $\iff$ 求最大Border长度:即$next[n]$

答案就是$n-next[n]$



---

## 作者：Timothy (赞：11)

这道题好像都是KMP和nlogn的哈希的题解，这里我提供一种O(N)的哈希的做法，而且代码短，内存小，时间快（误）。

以样例为例：
我们考虑字符串相同长度L(L=1...n)的前缀和后缀，

当L=2时：

                          cabcabca
                          ca
                                ca

我们发现前缀和后缀是相等的，同时可以发现(n-L)是该字符串的一个循环节。
所以我们只需要把L枚举一遍就行了。

需要注意的是，哈希可能会被卡，所以mi的取值很关键。

mi=26时就被卡了，亲测。

【代码】
```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
const int N=1e6+5;
int n,ans,s1,s2,mi;
char ch[N];
int main (){
	scanf ("%d%s",&n,ch+1);
	ans=n;mi=1;
	for (int i=1;i<n;++i){
		s1=s1*37+ch[i];
		s2=ch[n-i+1]*mi+s2;mi*=37;
		if (s1==s2)ans=n-i;
	}
	printf ("%d\n",ans);
	return 0;
}
```

P.S. 其实这就是KMP中的next数组，但是哈希更为直观的来求最长的前缀等于最长的后缀。

---

## 作者：leader_one (赞：11)

很明显这道题可以用hash来做

枚举子串长度，用哈希判断是否相等

时间复杂度为O(nlogn) 可以过；

类似的题参考UVA10298

基本类似

~~hash是万能的~~
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#define ull unsigned long long
using namespace std;
const int MAXN=1e6+100;
ull mod=107;
char ch[MAXN];
ull p[MAXN],sum[MAXN],n;
ull get(int l,int r)
{
	return sum[r]-sum[l-1]*p[r-l+1];
}
int main()
{
	cin>>n;
	p[0]=1;
	for(int i=1; i<=MAXN-1; i++)
		p[i]=p[i-1]*mod;//预处理模数的次方
	scanf("%s",ch+1);
	for(ull i=1; i<=n; i++)//预处理hash值
		sum[i]=sum[i-1]*mod+ch[i];
	for(ull i=1; i<=n; i++)//枚举子串长度
	{
		ull flag=1;
		ull last=get(1,i);
		for(int j=1; (j+1)*i<=n; j++)//整段判断
		{
			if(get(j*i+1,(j+1)*i)!=last)
			{
				flag=0;
				break;
			}
		}
		if(n*i!=0)//末位多出来的判断
		{
			ull len=n%i;
			if(get(1,len)!=get(n-len+1,n))
				flag=0;
		}
		if(flag)
		{
			printf("%d\n",(int)i);
			break;//找到答案，直接输出
		}
	}
}
```

---

## 作者：Nanchtiy (赞：10)

更好的阅读体验：[Nanchtiy's Blog](https://www.cnblogs.com/BrokenString/p/9781626.html)

### 思路
对于给定的字符串
运用KMP思想

设P[x]为前x个字符前缀和后缀相同的最长长度

则对于题目中的长度len有：

**len-p[len]为第一个重复子串的最后一个字符位置**

因此**len-p[len]即重复子串长度**

### 证明：

因为p[len]为前len个字符中前缀和后缀相同的最长长度 

先对于一个重复串来观察

abcd abcd abcd

则对于p[12]=8 就是它**后面多出来的重复串**

用**总长把多出来的重复串减去即可得到原始重复串的长度**

通过题目已经知道原串是一条自重复串

那么不妨设x为原始重复串的长度 **则x+1到len都是他重复的部分**

因此我们求出p[len]就是**后面重复部分的长度 **

则len-p[len]就满足原始重复串的长度


### 模拟样例：

字符串：c a b c a b c a

对应P：  0 0 0 1 2 3 4 5

则len-p[len]的位置为3

因为1~5的cabca与4~8的cabca相同

对于4~8的字符串都是原始字符串的重复部分

所以只要再补上一个b

即可满足重复串cabcabcab

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define maxn 1000010
char a[maxn];
int p[maxn];
int len,j;
int main()
{
	scanf("%d",&len);
    scanf("%s",a+1);
	for(int i=2;i<=len;i++)//常规KMP求P数组 
	{
	    while(j&&a[j+1]!=a[i]) j=p[j];
		if(a[j+1]==a[i]) j++;
		p[i]=j;	
	}	
	printf("%d",len-p[len]);//输出原始重复串长度 
} 
```


---

## 作者：guoshaoyang (赞：9)

## 算法：KMP
### [KMP算法讲解](https://www.luogu.org/blog/guo-shao-yang-2005/kmp-suan-fa)
这题的题意很简单，在一个字符串中找出最小周期，但这个周期在开头和结尾不一定是完整的，例如

	周期：abc
	样例：a[bcabcabcab]c
我们设最长相同前后缀的长度为len，总长度为LEN，那么周期就为LEN-len  
为什么？

	原串：CABCABCA
    前缀：CABCA
    后缀：   CABCA
无论周期为多少，最长前缀一定匹配到和最后一个字符相同的前一个字符，而最长后缀一定匹配到和第一个字符相同的后一个字符，所以中间刚好空了一整个周期

所以我们只要求出最长相同前后缀就行了
代码就是KMP的模板

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN=1024*1024;
int n,next[MAXN];
char str[MAXN];
int main(){
    scanf("%d%s",&n,str+1);
    for(int i=2,j=0;i<=n;i++){
        while(j&&str[j+1]!=str[i]){
            j=next[j];
        }
        if(str[j+1]==str[i]){
            j++;
        }
        next[i]=j;
    }
    printf("%d",n-next[n]);
    return 0;
}
```

---

## 作者：rainygame (赞：2)

本题的哈希题解较少，且部分并不完善，所以补一篇题解。

本题的题面可能有些难懂，我翻译一下：

给定长度为 $L$ 的字符串 $s_1$，你需要找到一个尽量短的 $s_1$ 前缀 $s_2$，使得 $s_1$ 是 $s_2s_2\dots s_2$ 的子串。

我们可以假定 $s_1$ 是一个形如 $s_2s_2\dots s_2s_3$ 的字符串，其中 $s_3$ 是 $s_2$ 的一个**前缀**。这样并不会使得答案改变。比如此时样例的 $s_2$ 就变为 $\texttt{cba}$。

我们可以枚举 $s_3$ （尽管我们甚至并不知道 $s_2$ 是什么），假设我们枚举 $s_3 = s_1[1\dots i]$，那么如果 $s_1[L-i+1\dots n]=s_3$，说明这个 $s_3$ 是可行的，那么 $s_1[1\dots L-i]$ 就一定可以作为一个 $s_2$。

因为如果直接比较字符串，时间复杂度会搞到 $O(L^2)$，无法通过。因此我们考虑字符串哈希。

设 $s_1[1\dots i]$ 的哈希为 $h_1$，$s_1[L-i+1\dots n]$ 的哈希为 $h_2$。

那么更新就是：

- 前缀新增 $s_i$：$h_1 \leftarrow h_1 + s_{i} \times B^{i-1}$。
- 后缀新增 $s_{L-i-1}$：$h_2 \leftarrow h_2 \times B+s_{L-i-1}$。

注意后缀是 $h_2 \times b$ 后再加 $s_{L-i-1}$，具体原因请自行思考。

其中 $B$ 是要乘的数。

然后对于每个 $i$ 都判一遍，如果 $h_1=h_2$ 就用 $L-i$ 更新答案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int BASE(23);

int n, ans;
unsigned int ha1, ha2, base(1);
string str;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    cin >> n >> str;
    ans = n;
    
    for (int i(0); i<n-1; ++i){
    	ha1 = ha1 + str[i] * base;
    	ha2 = ha2 * BASE + str[n-i-1];
    	if (ha1 == ha2) ans = n-i-1;
    	base *= BASE;
	}
	
	cout << ans;

    return 0;
}

```


---

## 作者：AuSquare (赞：2)

此题应采用KMP算法。首先附上一张机房大佬给我们讲KMP时用的图

![辅助讲解]http://a2.qpic.cn/psb?/V11PBDVY0zQUrh/zW5h1PqkylRwfbVX6sCzx4xbcaVh7QazSNlSRDm8dlQ!/m/dDEBAAAAAAAA&bo=VwJ.AAAAAAADBwk!&rf=photolist
在此图中border即为该串后缀与前缀匹配的最大长度（即程序中的pre数组），则最终len-pre[len]即为所求（具体原因见代码）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxd=1001000;
char s[maxd]; int pre[maxd];
int main() {
  
    int l; scanf("%d", &l);
    scanf("%s", s+1);
    memset(pre, 0, sizeof(pre)); //pre[i] 用于记录当匹配到模式串的第 i 位之后失配,该跳转到模式串的哪个位置（即该位置与该位置前的字符串匹配的所有位置） 
    int k=0;//模式串自匹配前缀与后缀匹配时前缀匹配到的位置
    for (int i=2; i<=l; i++) {//模式串自匹配 ，枚举后缀匹配到的位置
        while (k>0 && s[i]!=s[k+1]) k=pre[k]; //如果当前已匹配完成的部分下一位不相等，则前缀的位置向前跳至前缀上一次与此位置相等的字符重新匹配(即该字串的前缀与后缀相等） 
        if (s[i]==s[k+1]) k++;//匹配相同，模式串前缀匹配位置向后
        pre[i]=k;
    }
    printf("%d", l-pre[l]);
    //如果最后一位匹配的前缀长度小于等于串长的1/2， 易知匹配上的后缀之前的部分即为period（多余部分舍去）
    //如果最后一位匹配的前缀长度大于串长的1/2， 由于匹配的前缀与后缀完全相等， 则前缀去掉公共部分的前缀可由反复迭代相等证得该串由此部分反复自我复制得到
    //即该前缀的非公共部分与后缀相等长度的前缀相等，又与前缀的公共部分的前缀相等，而已完成比较的前缀与后缀完全相等，以此类推 
    return 0;
}
```

---

## 作者：oneman233 (赞：1)

~~看到本题都是字符串哈希以及kmp，我对我的暴力算法感到深深羞愧。。。~~

先说想法，暴力O(n)枚举前缀长度，然后进行检查，检查需要满足两个条件：

1、与循环串长度相同的字串必须与他一模一样

2、最后剩下长度小于循环串的部分应当与循环串的某个前缀相匹配

需要知道的是答案的上限也不过是n，毕竟任何一个字符串只需要循环一次就可以得到自己了嘛。

**然后是一个优化，用来防止TLE**

**如果字符串中所有字符没有在循环串中至少出现一次的话，这个位置一定不能作为开始位置**

这个优化用map的size互相比较大小就可以方便地判断。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
string s;
map<char,int> a,b;

bool chk(int x)
{
    int flg=x;
    while(flg+x<n){
        if(s.substr(0,x)!=s.substr(flg,x))
            return false;
        flg+=x;
    }
    for(int i=0;i<x&&flg<n;i++,flg++)
        if(s[i]!=s[flg])
            return false;
    return true;
}

int main()
{
    cin>>n>>s;
    for(int i=0;i<n;++i)
        a[s[i]]++;
    int start;
    for(int i=0;i<n;++i){
        b[s[i]]++;
        if(b.size()==a.size()){
            start=i;
            break;
        }
    }
    bool can=false;
    for(int i=start+1;i<=n;++i)
        if(chk(i)){
            cout<<i;
            break;
        }
    return 0;
}

```
当然我觉得kmp一定是要学习一个的，字符串哈希的做法也很美妙！

---

## 作者：yzhang (赞：0)

### [更好的阅读](https://www.cnblogs.com/yzhang-rp-inf/p/9979375.html)

### [原题传送门](https://www.luogu.org/problemnew/show/P4391)

### 这题需要用到[kmp匹配](https://www.cnblogs.com/yzhang-rp-inf/p/9978063.html)

推导发现：

设循环节的长度为x，那么kmp数组前x个都是0，后面kmp[x+n]=n

先求出kmp数组

答案实际就是len-kmp[len]

```cpp
#include <bits/stdc++.h>
#define N 1000005
using namespace std;
char a[N];
int kmp[N];
int main()
{
	int n;
	scanf("%d%s",&n,a);
	kmp[0]=kmp[1]=0;
	for(register int i=1,k=0;i<n;++i)
	{
		while(k&&a[i]!=a[k])
			k=kmp[k];
		kmp[i+1]=a[i]==a[k]?++k:0;
	}
	printf("%d",n-kmp[n]);
	return 0;
}
```





---

## 作者：timeclimber (赞：0)

这道题理解了next数组的含义就很好解决了。
next数组指的是以该位置为前缀的字符串的最大前后缀的长度。
所以我们假设重复的最小单元为x，那么对于任意的以x为最小重复单元字符串都可以用xx...xxx这样的形式来表示，那么用len-next[len-1]得到的值即为最小的重复单元长度。
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1e6+5;
char str[maxn];
int ne[maxn];
void make_next(char p[],int ne[],int len)
{
    ne[0]=0;
    for(int i=1,k=0;i<len;i++)
    {
        while(p[i]!=p[k]&&k>0) k=ne[k-1];
        if(p[i]==p[k]) k++;
        ne[i]=k;
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    scanf("%s",str);
    make_next(str,ne,n);
    printf("%d\n",n-ne[n-1]);
    return 0;
}

```

---

