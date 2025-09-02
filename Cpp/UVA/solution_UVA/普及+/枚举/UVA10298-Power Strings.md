# Power Strings

## 题目描述

### 题意简述：

求一个字符串最多由多少个重复的子串连接而成。

例如 `ababab` 由三个 `ab` 连接而成，`abcd` 由一个 `abcd` 连接而成。

## 说明/提示

$1\le |s|\le 10^6$。

## 样例 #1

### 输入

```
abcd
aaaa
ababab
.```

### 输出

```
1
4
3```

# 题解

## 作者：qwerta (赞：131)

这里是对目前最高赞题解结论的证明。

结论：设字符串长度为$n$，最长相同前后缀的长度为$next[i]$，

如$n$%$(n-next[n])=0$，则答案为$n/(n-next[n])$，否则为$1$。

证明：

我们求$next$数组的时候，相当于每次把当前串这样对齐了一下↓

![](https://i.loli.net/2018/10/17/5bc72efee4fd5.png)

而$next$求到$n$时，上面串的$n$对应的就是下面串的$next[n]$。

![](https://i.loli.net/2018/10/17/5bc7304c7e0d0.png)

这时候的$n-nxt[n]$就是箭头指向的绿色部分。

![](https://i.loli.net/2018/10/17/5bc730f1e9ffc.png)

而上下两串其实是一样的，所以下面串的前$n-nxt[n]$格和上面串的前$n-nxt[n]$相同。

又因为两串由蓝色框住的部分匹配，所以下面的绿框对应的部分和绿框相同。

![](https://i.loli.net/2018/10/17/5bc731f0cae32.png)

依此递推，可以得到，**如果循环节多于一个**，以前$n-nxt[n]$个为循环节，是可以铺满整串的。而且因为$nxt[n]$是尽量大的，所以这样得到的循环节长度为所有可能情况中最小的，也就是我们所求的。

而如果$n$%$(n-next[n])≠0$，可以认为之前的循环节匹配仍然可以进行，但是最后一个循环节被强行割掉了一些。

![](https://i.loli.net/2018/10/17/5bc733c407237.png)

显然这样就怎么都安排不上了。

所以如$n$%$(n-next[n])=0$，就能排上，答案为$n/(n-next[n])$，否则只能以自己为循环节，答案为$1$。

代码实现的时候注意一下自己代码中$n$的定义和$nxt$数组的定义什么的。

还是放一下我的代码叭qwq
```
/*
    qwerta
    UVA10298 Power Strings
    Accepted
    代码 C++，0.65KB
    提交时间 2018-10-12 17:59:53
    耗时/内存
    100ms, 0KB
*/
#include<iostream>
#include<cstdio>
using namespace std;
int nxt[1000003];
int main()
{
    //freopen("a.in","r",stdin);
    while(1)
    {
        string s;
        getline(cin,s);//读入一整行，放进s
        if(s.length()==1&&s[0]=='.')break;
        int lens=s.length();
        //kmp求next
        int k=-1;
        nxt[0]=-1;
        for(register int i=1;i<lens;++i)
        {
            while(k!=-1&&s[i]!=s[k+1])k=nxt[k];
            if(s[i]==s[k+1])k++;
            nxt[i]=k;
        }
        int n=lens-1;
        if((n+1)%(n-nxt[n])==0)//如果能恰好排满循环节
        printf("%d\n",((n+1)/(n-nxt[n])));//输出总长除以循环节长度
        else printf("1\n");//否则输出1
    }
    return 0;
}
```


------------


以上18.10.17

20.12.7更新：

关于讨论中提到的“可能有比(n-nxt[n])更长的目标子串”，可证该情况不存在，证明如下：

反证：如果存在，则有如图情况：

[![DxrvPU.png](https://s3.ax1x.com/2020/12/07/DxrvPU.png)](https://imgchr.com/i/DxrvPU)

即左上方绿色段+橙色段=右下方黄色段+绿色段。

则推出左上方绿色段由黄色段开头，且两个绿色段相同。

推出右下方绿色段由黄色段开头...（这个递推和前文的递推类似

最后得出该目标子串由黄色小段重复而成，和题目要求的“最短字串”不符。

所以不存在比(n-nxt[n])更长的目标子串，原结论正确。

//~~没想到都大学了我还能看懂当年的题解，泪目~~

---

## 作者：llldx03 (赞：22)


//先说一下题意：给定若干个长度小于等于1000000的字符串，询问每个字符串最多由多少个相同的子串重复连接而成，如ababab，由3个ab重复连接而成

//其实看到 “子串”，“相同的”“重复连接”这些关键词，很容易就能想到KMP算法（不会KMP可以跳p3375或自行百度）

//那么KMP算法怎么在这道题实际应用呢？其实我们想到KMP的核心是在求next数组，我们不妨就利用next数组来解这道题，大家可以先想一想，如果一个字符串是由n个相同的字符串重复连接，那么它的next数组会有什么特点呢？

abcdabcdabcd    aaaaaaaaa   ababababab

000012345678    012345678   0012345678

//写几个字符串并把它的next数组写出来，我们会发现这种字符串其实除了前面有几个0以外后面是每次加1的，那么这里面就有规律供我们解题了

//我们假定这个字符串长度为n，那么n-next[n]（n减去第n个字符的next值）这个位置一定是重复的那个最长子串最后一个字符所在的位置

//那么我们进一步思考，如果这整个字符串真的是由好几个相同字符串重复连接，那么n一定能整除n-next[n]，并且n/(n-next[n])就是最后的答案

//思路构建完成√，开始代码实现
```
#include<cstdio>
#include<cstring>
using namespace std;
char s[1000010];
int next[1000010];
int k,ans;//k的初始值为0 
int main()
{
	scanf("%s",s);//输入字符 
	while(s[0]!='.')//循环条件：只要字符不是‘. ’输入和询问就没有结束 
	{
		int len=strlen(s);//计算字符串长度 
		for(int i=1;i<len;i++)//kmp标准模板 
		{
			while(k&&s[i]!=s[k])k=next[k];
			next[i+1]=s[i]==s[k]?++k:0;
		}
		ans=len%(len-next[len])?1:len/(len-next[len]);//看看是否能被整除，如果能被整除，那么子串个数就是冒号后面那一坨，否则就是1 
		printf("%d\n",ans);//输出答案 
		k=0;//一定要将k重置为0！！！很重要！！没有这步操作会使整个程序瘫痪 
		scanf("%s",s);//再输字符串，从而通过循环条件的判断决定是否退出 
	}
	return 0; 
}
```

---

## 作者：bigmurmur (赞：12)

#字符串题目就用哈希~~水~~过去吧

很容易知道子串的长度只有是n的因数才有可能成为循环节。

那么我们从第一个字符开始枚举循环节可能的长度k(1<=k<=n)

如果所枚举的长度k是长度n的因数，就走进check函数判断s[1]~s[k]所组成的字符串是否可以作为循环节

不难想到只需要判断s[1]~s[k] , s[k+1]~s[2k] …… s[n-k+1]~s[n] 是否全部相等,相等说明 s[1]~s[k] 是一个循环节，输出 n/k即可

以上内容全程可用[hash](https://www.luogu.org/problemnew/show/P3370)解决

代码如下，敬请观赏

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
typedef unsigned long long LL;
const LL base=131;
const int N=1000010;
int n;
LL power[N],sum[N];
bool check(LL v,int k)  //判断s[1]~s[k]是否是循环节
{
	for(register int i=1;i<=n;i+=k){
		if(v!=sum[i+k-1]-sum[i-1]*power[k]) return 0;
	}
	return 1;
}
int main()
{
	power[0]=1;
	for(register int i=1;i<=N-10;++i) //hash准备工作
    	power[i]=power[i-1]*base;
	char s[N];
	while(scanf("%s",s+1)){
		if(s[1]=='.')break;
		n=strlen(s+1);
		sum[0]=0;
		for(register int i=1;i<=n;++i) sum[i]=sum[i-1]*base+LL(s[i]);
		for(register int i=1;i<=n;++i){
			if(n%i)continue;
			LL expect=sum[i];
			if(check(expect,i)){
				printf("%d\n",n/i);
				break;
			}	
		}
	}
	return 0;
}
```

不是所有的MURMUR都叫[bigmurmur](https://www.luogu.org/space/show?uid=113959)

---

## 作者：AFO蒟蒻选手 (赞：10)

这题是讲字符串的，所以我看楼上楼下都用的Hash与KMP，~~只有我一个蒟蒻在墙角瑟瑟发抖~~

话归正传，虽说我们没用Hash，但实际思想与Hash一样，都是用滚动数组来进行比较。即从第一个开始，一旦发现前面与后面的不一样，就把后面的贴在比较数组的后面。

但为什么要这样呢？因为如果用最暴力的做法，把所有的都扫一遍，时间复杂度明显超时。不过要实现滚动数组也并非易事，最核心的代码如下：

```cpp
bool check(int sizea){//sizea为比较数组的长度
    int sizes=s.size(),i;
    for(i=0;i<sizes;i++){
        if(s[i%sizea]!=s[i]){//利用同余思想进行比较
            return false;
        }
    }
    return true;
}
```

但这样就可以了吗？别急，如果就此提交，你还是会超时(~~只要数据不水~~)。我们又很快发现，假如字符串长度无法被比较数组长度整除，就一定无法达到最优解(请参见上篇题解)，而且如果比较数组长度超过字符串本身的一半，就无须再比了。

于是综上所述，AC代码如下：
```cpp
#include<bits/stdc++.h>//万能头文件好处多
using namespace std;
string s;
bool check(int sizea){
    int sizes=s.size(),i;
    if(sizes%sizea!=0){//如果不能整除就结束
        return false;
    }
    for(i=0;i<sizes;i++){
        if(s[i%sizea]!=s[i]){
            return false;//不符合条件就返回
        }
    }
    return true;
}
int main(){
    int i,size;
    bool out;
    for(;;){
        cin>>s;
        if(s=="."){//结束条件
            break;
        }
        i=0;
        size=s.size();
        out=true;
        while(i<=size/2){//比到一半就不比了
            if(check(i+1)){//如果符合条件就输出
                cout<<size/(i+1)<<endl;
                out=false;//out是判断之后是否输出一
                break;
            }
            i++;//不对就继续找
        }
        if(out){
            cout<<1<<endl;
        }
    }
    return 0;
} 
```

最后在这里求管理员过QTQ，也顺便求个赞QAQ

---

## 作者：嗯。 (赞：8)

这道题我是在练习字符串哈希时做到的题，一开始我用的字符串哈希调了好久，结果交到loj上只有60分　

~~是我太菜了~~

附上丑陋的60分代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,ans,flag,,t=131;
unsigned int pow[100101],has[100101];
char str[100101];
int main()
{
	pow[0]=1;
	for(register int i=1;i<=100001;i++)
	pow[i]=(pow[i-1]*t);
	scanf("%s",str+1);
	while(str[1]!='.')
	{
		flag=ans=1;
		n=strlen(str+1);
		for(register int i=1;i<=n;i++)
		has[i]=(has[i-1]*t+(str[i]-'a'+1));
		for(register int len=1;len<=n;len++)
		if(!(n%len))
		{
			flag=1;
			unsigned int h=has[len];
			for(register int i=len;i<=n;i+=len)
			if(h!=has[i]-(has[i-len]*pow[len]))
		  	{
				flag=0;
				break;
			}
			if(flag)
			{ans=n/len;break;}
		}
		printf("%d\n",ans);
		scanf("%s",str+1);
	}
	return 0;
}
```
过了一下我发现这是我校某位大佬之前给我们这些蒟蒻考试时考过的题，当时KMP和哈希都不会，然后就打了个~~暴力~~交了上去，结果AC了~~别人奔着正解打还没我优~~，然后那次考试拿了我校rank3.

好了好了，不多bb了，讲正事，虽然当时奔着暴力去的，但是现在突然发现复杂度是可以过去的．

思路就是：因为选出来的循环节的长度一定是整个串的约数（显然），而且题目是要循环次数多（即循环长度小）所以可以从小到大枚举循环节的长度，然后当他的长度是整个字符串的约数时再进行操作．

复杂度：因为一个数的约数是有限的所以可以减掉很多枝（我校某位大佬说这是调和级数，被证明了是In(n)的），所以这道题可以过去

其他：这里介绍STL(string)里的一个函数assign(好像是叫截取函数)
```cpp
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string str1="yesterday once more";
    string str2("my heart go on");
    string str3,str4;
    str3.assign(str2,3,6);//=heart(从3开始的长度为六)
    str4.assign(str2,3,string::npos); // = heart go on (从3开始到结尾赋给str4)
    str4.assign("gaint");//=gaint
    str4.assign("nico",5);//=nico
    str4.assign(5,'x'); //=xxxxx
    return 0;
}
```

附上丑陋的看似暴力的AC代码：
```cpp
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string str,s;
int ans=1,n,flag;
int main()
{
	cin>>str;
	while(str!=".")
	{
		ans=1;
		n=str.size();
		for(register int len=1;len<=n;len++)//不加register不爽
		if(!(n%len))//是约数才进行操作
		{
			s.assign(str,0,len);//STL大法好
			flag=0;
			for(register int i=0;i<=n-1;i++)
			if(s[i%len]!=str[i])//暴力匹配
			{flag=1;break;}
			if(flag==0)
			{ans=n/len;break;}
		}
		printf("%d\n",ans);
		cin>>str;
	}
	return 0;
}
```

---

## 作者：oistr (赞：5)

## 前置知识
- KMP（至少要知道如何求 $\operatorname{next}$ 数组）

## 分析
这道题的大意是让你求一个给定字符串的最短循环节（如果没有输出 `1`）

为了讨论方便，我们约定 $s_{i..j}$ 表示 $s_i$ 至 $s_j$ 的子串。约定字符串下标 $0$ 开始。约定 $s_1s_2$ 表示拼接两个字符串得到的新字符串。约定 $|$ 为整除符号。

考虑一个如下的有 $5$ 个长度为 $k$ 的最短循环节的长度为 $n$ 的 字符串 $s$（为了讨论方便，令 $k=4$）：

```
循环节编号：	|   A   |   B   |   C   |   D   |   E   |
字符串内容：	|A B C D|A B C D|A B C D|A B C D|A B C D| 
```

则我们只需要求出 $k$（题目要求输出的循环节个数就是 $\dfrac{n}{k}$）。

我们计算它的 $\operatorname{next}$ 数组，为：

```
循环节编号：  |   A   |   B   |   C   |   D     |   E       |
字符串内容：  |A B C D|A B C D|A B C D|A B  C  D|A  B  C   D| 
next 数组：  |0 0 0 0|0 1 2 3|4 5 6 7|8 9 10 11|12 13 14 15|16
```

那么 $\operatorname{next}$ 数组为什么是这个值呢？考虑 $\operatorname{next}_n$。

$\operatorname{next}_n$ 指的是 $s_{0..n-1}$ 之间的最长边界串，即 $s$ 的最长边界串（边界串就是既是一个字符串前缀又是它的后缀的子串）。由于整个字符串是由 $5$ 个循环节组成的，那么 $ABCD$ 和 $BCDE$ 显然是相同的，且为最长边界串（由于 $A$，$B$，…… ，$E$ 都是**最短**循环节，可以很容易的用反证法得出不存在更长的边界串）。因此 $\operatorname{next}_n$ 就是 $ABCD$ 的结尾，从而有 $\operatorname{next}_n=16$ 。

因为 $\operatorname{next}_n$ 是 $ABCD$ 的结尾，而 $n$ 是 $ABCDE$（整个串 $s$） 的结尾，因此 $n-\operatorname{next}_n$ 就是 $E$ 的长度，即一个循环节的长度 $k$。

$$n-\operatorname{next}_n=k$$

因此，我们只需要借用 KMP 中求 $\operatorname{next}$ 数组的过程，递推求出 $\operatorname{next}_n$ 即可。

注意到上述讨论是在假设原始字符串**存在循环节**的前提下的，实际应用中需判断是否存在循环节。容易想到如果 $k|n$ 则存在循环节。否则不存在。

单次询问复杂度为 $\mathcal{O}(n)$，总复杂度为 $\mathcal{O}(Tn)$，一个非常高效的算法。

## 核心代码

### 求出 $\operatorname{next}$ 数组

不多说了，不会的可以去学一学 KMP 算法。

```cpp
void kmpFindNext(string p)
{
	int j=-1;
	nxt[0]=-1;
	for(int i=0;i<p.length();i++)
	{
		while(j>=0 &&p[i]!=p[j])
		{
			j=nxt[j];
		 } 
		j++;
		nxt[i+1]=j;
	} 
}
```
### 主函数

这才是最重要的！

```cpp
while(cin>>s)
	{
		int n=s.length();
		if(s.length()==1 && s[0]=='.')
		{
			break;
		}
        //注意每次将 nxt 数组归零
        //next 会引起重名冲突，所以此处用了 nxt。
		memset(nxt,0,sizeof(nxt));
		kmpFindNext(s);
        //求出 k
		int k=n-nxt[n];
        //判断是否存在循环节
		if(!(n%k))
		{
			cout<<(n/k)<<endl;
		}
        //不要忘了不存在也要输出 1！
		else
		{
			cout<<1<<endl;
		}
	}
```

---

## 作者：lianliangyu (赞：4)

看大家都在交字符串$hash$和$KMP$的题解，那我就交一发分治暴力的方法。

我的方法与分块类似，能将一个原串分成相同部分的子串长度必然能整除原串长度，那么我们就枚举原长的约数，将原串分成长度相等的部分。如下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/uynqht2u.png)

显然，如果这些块都相同的话，那么它们合并在一起也是相同的。比如图中$1,2$块和$3,4$块分别合并起来也是相同的。

基于这种思想，我们就可以运用二分的思想，把原来的整块分成两部分，再判断两部分是否相同。如果相同，那么就选取左边这部分，继续重复上述步骤，直到分到底层为止；如果不同，那么就说明不成立，直接跳出递归，执行下一层枚举。

另外，如果在二分时遇到块数为奇数个的情况，这时就单独挑出最后一块，与第一块进行比较。如果相同，就取剩下部分继续进行二分操作；如果不同，直接跳出。

这种枚举是不会出现不存在的情况的，因为在枚举时，会出现块数为$1$的情况，这种情况下调用函数时一下就到最底层，直接判断可行。所以枚举时分成的块长要从小到大枚举，遇到可行的，直接输出，停止剩下的枚举。
```cpp
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
using namespace std;
int a[1000005],tot,n;
char s[1000005];
inline bool check(int num,string k,int l)           //num为该区间内块的个数，k为第一块（貌似不需要），l为1-l区间的右端点。 
{
	if(num==1)                                      //如果到最底层 
	{
		for(register int i=0;i<l;i++)
		if(s[i]!=k[i]) return false;                //判断(貌似不需要)
		return true;
	}
	int len;
	if(num&1)                                       //如果块数为奇数 
	{
		len=l-k.size();
		for(register int i=len;i<l;i++)             //取最后一块比较 
		if(s[i]!=k[i-len]) return false;
		l=len;num--;
	}
	len=l>>1;
	for(register int i=0;i<len;i++)                 //判断2部分是否相等 
	if(s[i]!=s[i+len]) return false;
	return check(num>>1,k,len);                     //递归 
}
int main()
{
//	freopen("powerstr.in","r",stdin);freopen("powerstr.out","w",stdout);
	int i,T,k;
//	scanf("%d",&T);
	scanf("%s",s);
	while(s[0]!='.')
	{
		n=strlen(s);
		string t;
		tot=0;bool ok=0;
		for(i=1;i*i<=n;i++)                        //枚举约数 
		if(n%i==0)
		{
			a[++tot]=n/i;                          //记录另一半，减少枚举次数 
			t="";
			for(register int j=0;j<i;j++) t+=s[j];
//			cout<<t<<endl;
			if(check(n/i,t,n))
			{
				ok=1;
				printf("%d\n",n/i);                //找到就跳出 
				break;
			}
		}
		if(!ok)
		for(i=tot;i;i--)
		{
			t="";
			for(register int j=0;j<a[i];j++) t+=s[j];
//			cout<<t<<endl;
			if(check(n/a[i],t,n))
			{
				printf("%d\n",n/a[i]);
				break;
			}
//			cout<<t<<endl;
		}
		scanf("%s",s);
	}
	return 0;
}
```


---

## 作者：hyfhaha (赞：4)

此题我写的是后缀数组SA解法，如果不会后缀数组的可以跳过本篇blog了。

参考文献：罗穗骞 2009集训队后缀数组论文

# 前记
最近学后缀数组，肝了不少题，也分出了后缀数组的几个题型，看这题没有后缀数组的解法，于是我决定来水一波。

注：思想正确，代码不一定正确。

## 分析题意
给定一个字符串 L，已知这个字符串是由某个字符串 S 重复 R 次而得到的，
求 R 的最大值。

其实就是求字符串L的连续重复子串。连续重复子串就是后缀数组的一个题型。

## 算法分析
1、我们需要最大的R，就说明我们需要连续重复子串的子串长度最小，那我们就可以首先枚举子串的长度k。

2、如何判断枚举出的子串是否符合题意，为L的连续重复子串。相信学过后缀数组的大家一定知道如何求最长公共前缀，我在这里简要提一下。

## 最长公共前缀
### 定义&&性质
一、

Suf(i)为字符串S的从i位开始的后缀。

例：S="LAHAKIOI"

Suf(0)="LAHAKIOI".Suf(4)="AKIOI".（字符串从0开始）

二、

height[i]为Suf(SA[i])和Suf(SA[i-1])的最长公共前缀

![例子1](https://cdn.luogu.com.cn/upload/pic/49033.png)

三、

h[i]=height[rank[i]]，也就是 Suf(i)和在它前一名的后缀的最长公共前
缀。

h数组有以下性质：
h[i]≥h[i-1]-1

具体证明这里不给出，如果有需要可以看我blog里的后缀数组全讲。

四、

Suf(j)和Suf(k)的最长公共前缀为（height[rank[j]+1],height[rank[j]+2],height[rank[j]+3],……,height[rank[k]]）的最小值。

具体证明依然不给出，有需要可以看我的blog。

------------

正所谓我们使用后缀数组求出了SA数组和Rank数组，我们想要求最长公共前缀，就要高效求出height数组。

求height数组，我们可以根据h数组的性质(三)，对于每一个后缀和他上一个的字符串，我们不需要从头开始寻找他们的最长公共前缀，这样时间复杂度高达O(n^2)，我们可以直接从h[i-1]-1处开始判断，因为根据h数组的性质，这两个字符串的前h[i-1]-1位一定是相同的。

这样时间复杂度降到O(n).

这里可能大家看的不是很懂，不过代码比较简单，比较容易懂:
```cpp
void get_height(){		//求height数组
    int k=0;
    for(int i=0;i<n;i++){
        if(k)k--;       //h数组可以直接用一个计数器代替
        int j=sa[rank[i]-1];
        if(rank[i]-1==-1)continue;  //因为我的排名从0开始，所以排名是0时要特判
        while(s[i+k]==s[j+k])k++;   //从k处找最长公共前缀
        height[rank[i]]=k;          //记录height数组
    }
}
```
------------
那我们求出了最长公共前缀就可以判断长度为k的子串是否满足为连续最长子串。

### 判断长度为k的子串是否满足为连续最长子串
1、首先，我们要判断字符串长度n是否能整除k，如果不能就显然不行。

2、再看Suf(0)到Suf(k)的最长公共前缀是否为n-k。前面根据性质四，我们可以知道Suf(0)到Suf(k)的最长公共前缀，但每一次的时间都为O(n)，整体下来时间复杂度十分高。

但我们可以看到Suf(0)是固定的，所以我们可以预处理出只需求出 height 数组中的每一个数到height[rank[0]]之间的最小值记为ans数组即可。

全部代码：
```cpp
#include<string>
#include<stdio.h>
#include<string.h>
#include<iostream>
#define maxn 300001
using namespace std;
char s[maxn];
int n,sa[maxn],rank[maxn],newRK[maxn],key2[maxn],sum[maxn],height[maxn],k;
int level;
void get_sum(int m){
    for(int i=0;i<=m;i++) sum[i]=0;
    for(int i=0;i<n;i++) sum[rank[i]]++;
    for(int i=0;i<m;i++) sum[i]+=sum[i-1];
}
bool cmp(int x,int y,int L){
    if(rank[x]!=rank[y])return false;
    if((x+L>=n&&y+L<n)||(x+L<n&&y+L>=n))return false;
    if(x+L>=n&& y+L>=n) return true;
    return rank[x+L] == rank[y+L];
}
void get_height(){		//求height数组
    int k=0;
    for(int i=0;i<n;i++){
        if(k)k--;       //h数组可以直接用一个计数器代替
        int j=sa[rank[i]-1];
        if(rank[i]-1==-1)continue;  //因为我的排名从0开始，所以排名是0时要特判
        while(s[i+k]==s[j+k])k++;   //从k处找最长公共前缀
        height[rank[i]]=k;          //记录height数组
    }
}
void Suffix_Sort(){         //SA板子
    for(int i=0;i<n;i++) rank[i]=s[i];
    get_sum(356);
    for(int i=n-1;i>=0;i--)
        sa[--sum[rank[i]]]=i;
    int w=1,m=max(n,356);
    while(w<n){
        int p=0;
        for(int i=n-w;i<n;i++)key2[p++]=i; 	//第二关键字越界排前
        for(int i=0;i<n;i++)if(sa[i]>=w)key2[p++]=sa[i]-w;//如果当前长度有第一关键字就记录
        //以上按第二关键字排序
        get_sum(m);
        for(int i=n-1;i>=0;i--){
            int j=key2[i];
            sa[--sum[rank[j]]]=j;
        }
        //以上按第一关键字排序，直接覆盖之前的sa数组，不需要再开一个key1
        newRK[sa[0]]=0;
        level=1;
        for(int i=1;i<n;i++){
            if(cmp(sa[i-1],sa[i],w))
                newRK[sa[i]]=level-1;
            else
                newRK[sa[i]]=level++;
        }
        for(int i=0;i<n;i++)
            rank[i]=newRK[i];
        //以上计算长度2*w的rank数组
        if (level==n)break;
        w<<=1;
    }
}
int main(){
    while(1){
        int ans[maxn];
        memset(sa,0,sizeof(sa));
        memset(height,0,sizeof(height));
        memset(ans,0,sizeof(ans));
        memset(rank,0,sizeof(rank));
        scanf("%s",s);n=strlen(s);
        if(s[0]=='.')break;
        Suffix_Sort();get_height();
        //下面求ans数组
        int a=rank[0],minx=10000000;
        for(int i=a;i>=1;i--){
            minx=min(minx,height[i]);
            ans[sa[i-1]]=minx;
        }
        minx=10000000;
        for(int i=a+1;i<=n;i++){
            minx=min(minx,height[i]);
            ans[sa[i]]=minx;
        }
        for(int i=1;i<=n;i++){
            if(n%i==0){
                if(ans[i]==n-i)
                {
                    printf("%d\n",n/i);
                    break;
                }
            }
        }
    }
}
```
# 谢谢观赏

---

## 作者：谜之soul_北冥X (赞：3)

# 蒟蒻只会用哈希~~水~~了
## dalao轻喷
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull h[2000000],pw[2000000];
char st[2000000];
ull hsh(ull h[],int l,int r)
{
	return h[r]-h[l-1]*pw[r-l+1];
}//普通的hash 
int main()
{
	pw[0]=1;
	for(int i=1;i<=2000000;i++)
		pw[i]=pw[i-1]*233;//预处理 
	while(scanf("%s",st)==1&&st[0]!='.')
	{
		int l=strlen(st);ull hs=0;
		for(int i=1;i<=l;i++) 
			h[i]=h[i-1]*233+st[i-1];
		for(int i=1;i<=l;i++)
		{
			hs=hs*233+st[i-1];//每次都要算 
			if(l%i!=0) 
            		continue;//子串对不上直接跳过 
			int pd=1;
			for(int j=1;j<=l&&pd;j+=i)
            		//每一段都比较一下
			if(hsh(h,j,j+i-1)!=hs)
			pd=0;
			if(pd)//如果配对成功
			{
				printf("%d\n",l/i);
                		//总长除以子串长算数量 
				break;
			}
		}
	}
	return 0;//AC 
}
```


---

## 作者：qpdk777 (赞：2)

## 一、前言

很多题解都用的是KMP，

对于像我这样的蒟蒻，

字符串Hash才是最好的选择。

以下如果没有特别说明，数组的下标均是指某一序列的结尾。

## 二、解题步骤

1. 预处理$pown[]$数组，递推计算出膜数$d$的$n$次方，这里我直接离线了；
2. 输入待求字符串，计算长度 $l$ ；
3. 递推计算待求字符串的Hash值，需要用到的公式是
	$hashn[i]=hashn[i-1]*d+s[i]-'a'+1;$
4. 枚举子串终点。既然字符串是由若干个子串重复连接而成的，那么最小的子串必然会出现在字符串的前i位上。求出这个i，再用$l\div i$就求出了答案。
其实在开始判断之前是可以剪枝的，如果$l\bmod i \not=0$，那么显然前i个字符不可能是最小的子串，因为我们无法通过重复前i个字符恰好凑出长度为l个字符的字符串来。
    
5. 判断是否为待求子串。我定义了一个递归函数$hello(over,start)$，表示以前$over$个字符组成的子串，是否能够通过重复组成前$start+over$个字符组成的子串。这里用到了滚动哈希，即用一部分哈希值和另一部分哈希值加减，得到新的一段字符串的哈希值。
	公式为$hashn[over] == hashn[start+over]-hashn[start]*pown[over]$

	如果该表达式成立，那么继续搜索，直到$start == l$为止；
   否则直接返回0。

## 三、代码

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#define ull unsigned long long
using namespace std;

int flag;
ull d = 19260817;
ull hashn[1000010],pown[1000010];//本题是RemoteJudge，小心变量函数重名！！！
string s;

bool hello(int over,int start){
	if(start == s.length()-1)
		return 1;
	if(hashn[over] == hashn[start+over]-hashn[start]*pown[over])//注意这里的over是待比对的字符串的长度，start是起始点前一位 
		return hello(over,start+over);
	else
		return 0;
}

int main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	pown[0] = 1;
	for(int i = 1; i <= 1000000; ++i)
		pown[i] = pown[i-1]*d;
	while(cin>>s && s!="."){
		flag = 0;
		int l = s.length();
		s.insert(0," ");
		for(int i = 1; i <= l; ++i)
			hashn[i] = hashn[i-1]*d+s[i]-'a'+1;
		for(int i = 1; i < l; ++i)
			if(l%i == 0)
				if(hello(i,i)){
					cout<<l/i<<'\n';
					flag = 1;
					break;
				}
		if(!flag) cout<<1<<'\n';
	}
	
	
	return 0;
}
```


---

## 作者：Strelitzia (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/UVA10298)

---

没人用 $\text{KMP}$ 暴力吗？

其实这道题 $\text{KMP}$ 暴力不会 $\operatorname{T}$，因为子串长必须为串长的因子。

所以我们就可以直接暴力了，不过注意，匹配成功后，已匹配的串就不能再匹配了。

见代码标示处。

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
    T f = 1;x = 0;char s = getchar();
    while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
    while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
    x *= f;
}
template<typename T>void print(T x) {
    if(x < 0) putchar('-'),x = -x;
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
const int maxn = 1000005;

int pre[maxn];

void make_pre(char b[],int lenb) {
	int len = 0;
	pre[0] = 0;
	int i = 1;
	while (i < lenb) {
		if (b[i] == b[len]) pre[i ++] = ++ len;
		else if (len > 0) len = pre[len - 1];
		else pre[i ++] = 0;
	}
	for (int i = lenb ; i > 0 ; -- i) pre[i] = pre[i - 1];
	pre[0] = -1;
}

int cnt;

void KMP(char a[],char b[],int lena,int lenb) {
	int i = 0,j = 0;
	while (i < lena) {
		if (j == lenb - 1 && a[i] == b[j]) {
			cnt ++;
			j = 0; //-------------------------//
			i ++; //--------------------------//
		}
		else {
			if (a[i] == b[j]) ++ i,++ j;
			else {
				j = pre[j];
				if (j == -1) ++ j,++ i;
			}
		}
	}
}

char a[maxn],b[maxn];

int lena,lenb;

int main () {
	scanf("%s",a);
	lena = strlen(a);
	while (!(*a == '.' && lena == 1)) {
		memset(b,0,sizeof b);
		memset(pre,0,sizeof pre);
		lenb = 0;
		for (int i = 1 ; i <= lena ; ++ i) {
			lenb ++;
			b[i - 1] = a[i - 1];
			if (lena % i == 0) {
				cnt = 0;
				make_pre(b,lenb);
				KMP(a,b,lena,lenb);
				if (lena / i == cnt) {
					break;
				}
			}
		}
		if (cnt) print(cnt),putchar('\n');
		else print(1),putchar('\n');
		scanf("%s",a);
		lena = strlen(a);
	}
	return 0;
}
```

---

## 作者：lucywhite (赞：2)

主要用了哈希算法，没别的。(水题)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N=1e6+5;
const ull prime=233317;
ull power[N]={1},h[N]; 
int main()
{
    int l,i,j;
    string a;
    for(i=1;i<N;i++){
    	power[i]=power[i-1]*prime;
    }
    while(cin>>a)
    {
        if(a==".")
            break;
        l=a.size();
        h[0]=ull(a[0]);
        for(i=1;i<l;i++){
        	h[i]=h[i-1]*prime+ull(a[i]);
        }
        for(i=1;i<=l;i++)
        {
            if(l%i)
                continue;
            bool f=1;
            for(j=i-1;j<l;j+=i){
            	if(h[j]-h[j-i]*power[i]!=h[i-1]){
                    f=0;
                    break;
                }
            }
                
            if(f){ 
                cout<<l/i<<endl;
                break;
            }
        }
    }
    return 0;
}

```

---

## 作者：cxlcxl (赞：1)

好吧这一题 -> 刚学完hash  ~~本来想打忘了怎么mod了~~


------------
正题：用unsigned long long 就好了
自然溢出会帮你求余的     ->  %2^64

算出主串的hash值，然后循环 ~~暴力~~ 区间长度

然后一一配对就好了：水嫩嫩的题

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int b=1e6+3;
typedef unsigned long long ll;
char s[1000100];
ll sum[1000100],base[1000001];
int main() {
	base[0]=1;
	for(int i=1;i<1000000;i++) base[i]=base[i-1]*b;
	while(scanf("%s",s+1)!=EOF) {
		int i,j,k;
		if(s[1]=='.') break;
		int len=strlen(s+1),f=0;
		for(i=1;i<=len;i++) {
			sum[i]=sum[i-1]*b+(ll)(s[i]-'a'+1);
			if(s[i]!=s[i-1]&&i!=1) f=1;
 		}
		if(!f) {cout<<len<<endl;continue;}
		f=0;
		for(i=2;i<=len;i++) {
			f=0;
			if(len%i!=0) continue;      //不能填满的省略掉就好 
			k=i;
			for(j=k;j<=len;j+=k) {
				if(sum[j]-sum[j-k]*base[i]!=sum[i]) {  //配对 
					f=1;
					break;
				}
			}
			if(!f) {
				cout<<len/i<<endl; // 输出 
				break;
			}
		}
	}
	return 0;
}
```

第一次发blog ：小激动 ->  手动笑哭


---

## 作者：qwaszx (赞：1)

hash/KMP(蒟蒻的KMP已经忘得一干二净，所以只有hash了)

题意就是找最短的子串使得整个串可以由这个子串复制几次得到

一开始想二分，然后发现答案并不单调

然后不会做了emmm

最后下定决心打暴力，打之前忽然发现暴力复杂度是对的

emmmm

做法:从小到大枚举子串长度，hash判断原串的每一段是不是都和子串吻合

复杂度:$T(n)=O(\sum_{i=1}^nn/i)=O(nH_n)=O(n\ln n)$

实际上还要考虑约数，所以还要松一点

真的没有什么好说的了...见注释吧

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#define ull unsigned long long
using namespace std;
ull h[2000000],pw[2000000];
char st[2000000];
void hash_make(char st[],ull h[],int l)
{
	for(int i=1;i<=l;i++)
		h[i]=h[i-1]*233+st[i-1];
}
ull hsh(ull h[],int l,int r){return h[r]-h[l-1]*pw[r-l+1];}
//普通的hash
int main()
{
	pw[0]=1;
	for(int i=1;i<=1000000;i++)pw[i]=pw[i-1]*233;
	while(scanf("%s",st)==1&&st[0]!='.')
	{
		int l=strlen(st);ull hs=0;
		hash_make(st,h,l);
		for(int i=1;i<=l;i++)
		{
			hs=hs*233+st[i-1];//注意这里每次都要算
			if(l%i!=0)continue;//不整除直接舍去
			int pd=1;
			for(int j=1;j<=l&&pd;j+=i)//每一段都吻合
				if(hsh(h,j,j+i-1)!=hs)
					pd=0;
			if(pd){printf("%d\n",l/i);break;}
		}
	}
}
```

---

## 作者：香风智乃 (赞：1)

**hash+乘法逆元+**一点点数学知识

我们用取余法算出主串的hash，然后从小到大枚举子串的长度

显然，如果若干个子串的复制的hash值之和等于主串的hash值，那么答案就得到了。

然后我们计算子串（设子串长度为 $i$ ,hash 值为 $t$ ）的hash值：

$hash=t*(1+base^i+base^{2i}+...+base^{len-i})$

如果直接暴力求，那么显然会TLE

于是我们进行推导：

设：
$S_i=1+base^i+base^{2i}+...+base^{len-i}$

$S=S_i*base^i=base^{i}+base^{2i}+base^{3i}+...+base^{len}$

所以：$S-S_i=base^{len}-1=S_i*(base^i-1)$

$S_i=(base^{len}-1)/(base^i-1)$

我们利用快速幂可以很快地得出结果

但是涉及到取模除法运算，所以我们可以用乘法逆元，这里不详细讲了

根据费马小定理

$base^i-1$关于$mod$的乘法逆元为 $(base^i-1)^{mod-2}$


------------


然鹅主流的判断的方法[point here](https://www.luogu.org/problemnew/solution/P3538)
（本题强化版）

所以说我这是非正解qwq（逃

------------

end.

[juruo's blog](https://www.cnblogs.com/kafuuchino/p/9599119.html)

```
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef unsigned long long ull; 
const int mod=1e9+7;
const int base=131;
char c[2000004];
inline ull ksm(int x,int y){ //快速幂
    ull ans=1;
    for(;y;y>>=1){
        if(y&1) ans=ans*(ull)x%mod;
        x=1LL*x*x%mod;
    }
    return ans%mod;
}
int main(){
    do{
        scanf("%s",c);
        if(c[0]=='.') return 0;
        int ans=1,len=strlen(c);
        ull tot=0,t=0;
        for(int i=0;i<len;++i) tot=(tot*base+(ull)c[i])%mod; //计算主串hash值
        for(int i=1;i<=len/2;++i){
            t=(t*base+(ull)c[i-1])%mod; //子串hash值
            if(len%i) continue; //子串长度不被整除不可能有解
            ull tmp=ksm(base,i)-1; 
            ull s=(ksm(base,len)-1)*ksm(tmp,mod-2)%mod;
            if(t*s%mod==tot){ //刚好可以填充
                ans=len/i; break;
            }
        }
        printf("%d\n",ans);
    }while(1);
}
```

---

## 作者：lixiao189 (赞：1)

### 解法：
其实用很普通的“自然溢出法的Hash”就可以过这道题目（ps：出题人真良心没有故意卡我的Hash）。首先我们先枚举字串的长度length_k，之后我们在找出每个长度为length_k的字串，用Hash判断一下这些字串是否相同就可以了。时间复杂度：
$$ O (n/1+n/2+n/3+\cdots+n/n)\approx O(n)$$

### 代码：
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e6+5;
const int Base = 31;

char s[N];
unsigned long long Hash[N];
unsigned long long power[N]; //power[i]=base^i;

int main(){
	power[0]=1;
	for(int i=1;i<N;i++) power[i]=power[i-1]*Base;
	while(true){
		scanf("%s",s);
		if(s[0]=='.') break;
		int length=strlen(s); //获取字符串的长度
		Hash[0]=0;Hash[1]=(unsigned long long)s[0];
		for(int i=2;i<=length;i++) Hash[i]=Hash[i-1]*Base+(unsigned long long)s[i-1]; //计算Hash值
		for(int length_k=1;length_k<=length;length_k++){ //枚举可能匹配的长度
			if(length%length_k!=0) continue;
			unsigned long long t; //用于储存上一个k
			bool flag=true;
			for(int i=length_k;i<=length;i+=length_k){ //枚举起点
				unsigned long long k=Hash[i]-Hash[i-length_k]*power[length_k];
				if(i!=length_k){
					if(t!=k){
						flag=false;
						break;
					}
				}
				t=k;
			}
			if(flag){
				printf("%d\n",length/length_k);
				break;
			}
		}
	}
	return 0;
}
```

---

## 作者：_Clown_ (赞：0)

这是一道$KMP$算法题。

首先$GetNext$，这是不用说的，$GetNext$可以说是每一道$KMP$都要做的。

接下来我们考虑如何求解。

我们不妨假设这个字符串长度为$N$，那么$N-Next[N]$这个位置一定是重复的那个最长子串最后一个字符所在的位置

那如果这整个字符串真的是由好几个相同字符串重复连接，那么
$$
Nmod(N-Next[N])=0
$$
所以答案是
$$
N/(N-Next[N])
$$
```cpp
#include<bits/stdc++.h>
using namespace std;
string S;
int L;
int Next[1000001];
inline void GetNext()
{
	register int i,j;
	i=0;
	j=-1;
	Next[0]=-1;
	while(i<L)
	{
		if(j==-1||S[i]==S[j])
		{
			Next[++i]=++j;
		}
		else
		{
			j=Next[j];
		}
	}
}
int main(void)
{
	while(cin>>S)
	{
		if(S==".")
		{
			return 0;
		}
		L=S.size();
		GetNext();
		if(L%(L-Next[L])==0)
		{
			cout<<L/(L-Next[L])<<endl;
		}
		else
		{
			cout<<1<<endl;
		}
	}
	return 0;
}
```

---

## 作者：ღ﹏ﻬ北❦栀 (赞：0)

## KMP做法
KMP，模式串如果第i位与文本框第j位不匹配，就要回到第p[i]位继续与文本串第j位匹配，则模式串第i位到p[n]与模式串第（n-p[n]）位到n位是匹配的。所以如果n%（n-p[n]）=0,则存在重复连续子串，长度为n-p[n],循环次数为n/（n-p[n]）


------------
### 举个栗子
![](https://cdn.luogu.com.cn/upload/image_hosting/vz1tf3gy.png)


上表中将长度为20的字符串分为5个部分，~~容易看出~~如果（n%（n-p[n]）=0），那么p[n]%(n-p[n])=0，就可以将它最多分为n/（n-p[n]）段，且每段长度相等，易得p[n]=16,所以ABCD段=BCDE段，所以A=B,B=C,D=E，所以A=B=C=D=E，存在重复连续子串长度为4.

下面附代码：
```
#include<bits/stdc++.h>
using namespace std;
char a[1000005];
int p[1000005],n;
void prepare() 
{
	p[1]=0;
	int j=0;
	for(int i=1; i<n; i++) {
		while(j>0&&a[j+1]!=a[i+1])j=p[i];
		if(a[j+1]==a[i+1])j++;
		p[i+1]=j;
	}
}
int main() 
{
	for(;;)
	{
	scanf("%s",a+1);
	if(a[1]=='.')break;
	n=strlen(a+1);
	prepare();
	if(n%(n-p[n])==0)printf("%d\n",n/(n-p[n]));
	else printf("1\n");
}
return 0;
}
```

希望大家能早日AC，和艾克。如果有什么更好的办法，还请大家教教我，谢谢Thanks♪(･ω･)ﾉ

---

## 作者：Gorun (赞：0)

# Power Strings

这一道题用的是KMP算法，只要预先处理处p数组，我们就可以找到循环的次数了。

##### 源代码
```
#include <cstdio>
#include <cstring>
using namespace std;
const int max_a=1000000;
char a[max_a];
int p[max_a],len;
void getP()
{
    p[1]=0;
    int j=0;
    for (int i=1;i<=len;i++)
    {
        while (j>0&&a[j+1]!=a[i+1])
            j=p[j];
        if (a[j+1]==a[i+1])
            j++;
        p[i+1]=j;
    }
}
int main()
{
    while (true)
    {
        scanf(" %s",a+1);
        if (a[1]=='.')
            break;
        len=strlen(a+1);
        getP();
        if (len%(len-p[len])==0)
            printf("%d\n",len/(len-p[len]));
        else
            printf("1\n");
    }
}
```

##### 参考链接

DHOJ http://47.104.154.247/problem.php?cid=1015&pid=1

LOJ https://loj.ac/problem/10035

---

