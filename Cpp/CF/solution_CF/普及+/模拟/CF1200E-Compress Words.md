# Compress Words

## 题目描述

Amugae has a sentence consisting of $ n $ words. He want to compress this sentence into one word. Amugae doesn't like repetitions, so when he merges two words into one word, he removes the longest prefix of the second word that coincides with a suffix of the first word. For example, he merges "sample" and "please" into "samplease".

Amugae will merge his sentence left to right (i.e. first merge the first two words, then merge the result with the third word and so on). Write a program that prints the compressed word after the merging process ends.

## 样例 #1

### 输入

```
5
I want to order pizza
```

### 输出

```
Iwantorderpizza```

## 样例 #2

### 输入

```
5
sample please ease in out
```

### 输出

```
sampleaseinout```

# 题解

## 作者：yangrunze (赞：99)

这件事情，要从一条犇犇说起

![](https://cdn.luogu.com.cn/upload/image_hosting/a7oc8sj1.png)

于是，我就怀着能害死猫的好奇心，打开了CF1200E，从此就走上了一条不归路……

题目说人话就是这样的：

给你$n$个字符串，相同的地方可以拼接在一起（如$\text {be\color{purple}{ast}}$和$\text {\color{purple}{ast}\color{black}onish}$珂以拼在一起变成$\text {be\color{purple}{ast}\color{black}onish}$），问你最后能拼成什么东西

仔细分析一下，这个题目就是找 **第一个串的$\text {\color{purple}{后缀}}$和第二个串的$\text {\color{purple}{前缀}}$** ，找到他们 **$\text {\color{purple}{最长}}$的$\text {\color{purple}{公共部分}}$** 拼在一起


等会，最长？公共？？？前后缀？？？？？

这不就是 **$\text {\color{purple}{KMP}}$中$\text {\color{purple}{next数组}}$的定义吗？！**

所以，我们珂以**对一个字符串进行KMP，求出它的next数组**，进而解决问题

那问题来了：究竟如何构造出这个字符串呢？？？

构造什么样的字符串？无非就是**让这个字符串的前缀和后缀分别对应第一个字符串的前缀这第二个字符串的后缀**

也就是说，我们能把刚才的例子里的两个字符串拼成$\text {\color{purple}{ast}\color{black}onishbe\color{purple}{ast}}$，用这个字符串去搞一搞KMP，求出next数组，就可以轻松得到公共部分为长度为$3$的$\text{\color{purple}ast}$

这么快就搞定了思路，世界上竟然还有这么简单而E题？！我一边这样想，一边打出了代码：

```cpp
//这边我采用了STL中的string
//string多香啊，可以直接加减，还有好用的成员函数，除了慢亿点点外简直毫无缺点！
//那些叫嚣着说string不如char数组的，这些东西你们有吗？！
//消灭char数组暴政，世界属于string！！！
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int nxt[1000005];//next数组（不要写next，在CF上是关键字，会CE）
void kmp(string s){//我懒得讲KMP了怎么办啊QwQ
	int l=s.size();
	s=' '+s;//前面加个空格，让s下标从1开始
	nxt[0]=nxt[1]=0;//初始化next数组
	int j=0;//下标
	for(int i=2;i<=l;i++){
		while(j>0&&s[i]!=s[j+1])j=nxt[j];//如果不匹配，就借用已知信息跳到next
		if(s[i]==s[j+1])j++;//匹配成功！j++;
		nxt[i]=j;//更新next数组的信息
	} 
}
int main(){
    ios::sync_with_stdio(false);//让cin变得快一点
	int n;
    cin>>n;
	string s,ans;
	cin>>ans;//先拿第一个字符串当成答案，后面逐步合并
	for(int i=2;i<=n;i++){
		cin>>s;//输入
		string ss=s+ans;//构造新的字符串
		kmp(ss);//进行kmp
		for(int j=nxt[ss.size()];j<s.size();j++)//更新不是公共部分（也就是下标>=next[ss.size()]的部分）到ans里
		ans+=s[j];
	}
	cout<<ans;//输出
} 
```
结果呢？？？

![](https://cdn.luogu.com.cn/upload/image_hosting/f78owapq.png)

~~毒瘤！！！！！~~

到底为啥T了呢？本蒻从上午想到下午，才发现了端倪

如果我们的两个字符串是这样的：

答案串：$\text{stOOOOOOOOOOOOOOOOOOOOO}\cdots \text{（此处略去}10^6\text{个O）Orzvector\purple{wyx}}$

新输入的文本串：$\text{\purple{wyx}tql}$


这样的话，拼接出的字符串长度简直比《清明上河图》还长……这要是KMP一遍，得匹配到猴年马月啊……

这时候我们就注意啦！我们的前后缀只有一个长度为3的字符串$\text{\purple {wyx}}$，跟前面的$\text{stOOOOOOOOOOOOO}\cdots$一点关系都没有！所以，**最长公共前后缀的长度实际上只要到$\min(\text{字符串1的长度},\text{字符串2的长度})$就行**啦！

所以，这里最长公共前后缀的长度最多为$6$，那我们直接截取前面的字符串的后$6$个字符，拼接成$\text{\purple{wyx}tqltor\purple{wyx}}$，是不是清爽了不少？而且效果一点也不差呢！

所以，我们只需要把代码里的更新字符串那句改成：

```cpp
		int l=min(s.size(),ans.size());//真正需要KMP的长度		
		string ss=s+ans.substr(ans.size()-l,l);//利用string里的substr函数，截取从下标ans.size()-l，长度为l的子串，也就是后l个字符
```
经过这样一优化，终于不再是TLE了，取而代之的是

![](https://cdn.luogu.com.cn/upload/image_hosting/orssyded.png)

为啥就WA了嘞？实在找不到有啥坑点了，于是我只好去了CF，找到了传说中的**测试数据**：

输入：

```
5
1101 1001 001001 101 010
```
标准答案：
```
1101001001010
```
我的输出：
```
110100100101
```

经过检查，是最后将$101$和$010$合并后KMP时出现了问题

合并后的字符串：$101010$

最长公共前后缀长度：$4$

？？？

这个KMP的匹配确实是没毛病的，但问题是他俩**隔着不同的字符串求出了一个next值**，跨界了喂！

那怎么办呢？我们学习一下王母娘娘对付牛郎织女的方法，**从字符串中间加一些奇奇怪怪的东西，把两个字符串隔开**，叫你们跨界约会，哼！

```cpp
string ss=s+"#*@$woxiangqiediaoYnoi,yingyingying~~~"+ans.substr(ans.size()-l,l);//奇怪的东西增加了！
```
（咦，这里的Markdown和$\LaTeX$炸了？我也不知道为什么，凑活着看吧）

![](https://www.luogu.com.cn/images/congratulation.png)

最后，祝大家的CF稳涨Rating哦！$\large{\color{yellow}{QwQ}}$

---

## 作者：He_Ren (赞：24)

# 哈希

直接哈希

每次判断当前串的每一个前缀是否是答案的后缀，取最长的满足条件的前缀

如何判断？

按照哈希的方法：

```cpp
hans1[ansl] = ((ll)hans1[ansl-1]*b1 + s[i])%mod1;//b1是随机出来的进制
```

只要这样：

```cpp
(h1 + (ll)hans1[ansl-i]*pb1[i])%mod1
```

即：用当前“位数”为 $i$ 的哈希值(```h1```)去 “替换” 当前答案的后$i$位

如果这个值与当前答案相等，那么它就是当前答案的后缀

使用了双哈希

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
typedef long long ll;
const int MAXL = 1e6 + 5;
const int mod1 = 19260817;
const int mod2 = 19491001;

int b1,pb1[MAXL],b2,pb2[MAXL];
int hans1[MAXL],hans2[MAXL];

char ans[MAXL],s[MAXL];

int main(void)
{
	srand(time(0));
	
	b1 = rand()%321 + 233;
	pb1[0] = 1;
	for(int i=1; i<MAXL; ++i) pb1[i] = (ll)pb1[i-1]*b1 %mod1;
	
	b2 = rand()%233 + 321;
	pb2[0] = 1;
	for(int i=1; i<MAXL; ++i) pb2[i] = (ll)pb2[i-1]*b2 % mod2;
	
	int n;
	scanf("%d",&n);
	
	int ansl=0;
	for(int j=1; j<=n; ++j)
	{
		scanf("%s",s+1);
		int sl = strlen(s+1);
		
		int h1=0, h2=0, len=0;
		for(int i=1; i<=sl && i<=ansl; ++i)
		{
			h1 = ((ll)h1*b1%mod1 + s[i]) %mod1;
			h2 = ((ll)h2*b2%mod2 + s[i]) %mod2;
			
			if(hans1[ansl] == (h1 + (ll)hans1[ansl-i]*pb1[i])%mod1 && hans2[ansl] == (h2 + (ll)hans2[ansl-i]*pb2[i])%mod2)
				len=i;
		}
		
		for(int i=len+1; i<=sl; ++i)
		{
			ans[++ansl] = s[i];
			hans1[ansl] = ((ll)hans1[ansl-1]*b1 + s[i])%mod1;
			hans2[ansl] = ((ll)hans2[ansl-1]*b2 + s[i])%mod2;
		}
	}
	printf("%s",ans+1);
	return 0;
}
```

# z算法

取当前串$a$的长度与当前答案$ans$长度的min

设$size = \min(|a|,|ans|)$

重合在一起的长度最长是就$size$

于是把当前串的前$size$位，与答案的后$size$位拼在一起（中间加一个不可能出现的字符"$"）

$S = a[1,2,\cdots,size] + \$ + ans[ansl-size+1,\cdots,ansl]$

求出z数组

如果一个元素$S_i$(属于$S$的后$size$位），它的z值等于它到结尾的距离

即：它是$ans$的某一个后缀，且它等于$a$的前缀

```cpp
if(z[sz-i] == i)
```

那么，它就是一个可行的重合部分

**这是里本算法的核心**

```cpp
#include<cstdio>
#include<cstring>
const int MAXL = 1e6 + 5;

const int min(int a,int b){ return a<b? a: b;}

char a[MAXL],s[MAXL*2],ans[MAXL];
int z[MAXL*2];

int main(void)
{
	int n;
	scanf("%d",&n);
	
	int ansl=0;
	for(int j=1; j<=n; ++j)
	{
		scanf("%s",a);
		int al = strlen(a), bl = min(al,ansl);
		
		int sz = bl*2 + 1;
		for(int i=0; i<bl; ++i)
			s[i]=a[i], s[i+bl+1] = ans[ansl-bl+i];
		s[bl] = '$';
		s[sz] = 0;
		
		int l=0,r=0;
		for(int i=1; i<sz; ++i)
		{
			z[i]=0;
			if(i<r) z[i] = min(r-i,z[i-l]);
			while(s[z[i]] == s[i+z[i]]) ++z[i];
			if(i+z[i]>r) l=i, r=i+z[i];
		}
		
		int len = 0;
		for(int i=bl; i>=1; --i)
			if(z[sz-i] == i)
			{
				len=i;
				break;
			}
		for(int i=len; i<al; ++i) ans[ansl++] = a[i];
	}
	printf("%s",ans);
	return 0;
}
```

---

## 作者：Frozencode (赞：18)

这题事实上要我们求的是:

当前拼接好的串的**后缀** 和 待拼接串的**前缀** 的**最大匹配长度**。

可能有点绕，我们结合样例2来理解下。

当前拼接好的串 $sample$

待拼接串 $please$

后缀和前缀的最大匹配 $ple$ 

最大匹配长度 $3$

所以我们只要把 $ase$ 加入到当前拼接好的串。

此时当前拼接好的串 $samplease$

~~这下应该理解了吧~~

那么怎么求最大匹配长度呢？

匹配？想到啥？ KMP!

和待拼接串的前缀匹配？

那么构造一个待拼接串在**前**,当前拼接好的串在**后**的新串，求出当前拼接好的串的**最后一个字符**的$kmp[i]$值不就行了？(啥是[$kmp[i]$](https://www.luogu.org/problem/P3375)?)

值得注意的是最大匹配长度不会超过待拼接串的长度，所以每次只要截取当前拼接好的串的一部分串就行了

理解的话代码实现并不困难:

```cpp
/*
	Author:Frozencode
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pii;
const ll maxn = 1000010;
const ll INF = 2147483647;
ll n,len,anslen,top,minn,kmp[maxn];
char c[maxn],ans[maxn];
int main()
{ 
	cin>>n;
	for(int i = 1;i <= n;i++){
		scanf("%s",c + 1);
		len = strlen(c + 1);
		minn = min(anslen,len);//截取长度。
		top = len;
		c[++top] = '#';//加个奇怪字符防止最大匹配长度超过待拼接串的长度。
		kmp[0] = 0;
		kmp[1] = 0;
		for(int j = 1;j <= minn;j++)c[++top] = ans[anslen - (minn - j)];//拼接。
		for(int j = 1;j < top;j++){
			ll k = kmp[j];
			while(k && c[k + 1] != c[j + 1])k = kmp[k];
			if(c[k + 1] == c[j + 1])k++;
			kmp[j + 1] = k;
		}//求kmp数组的值,这里不理解的话可以点上面的链接进去看看。
		for(int j = kmp[top] + 1;j <= len;j++)ans[++anslen] = c[j];//更新当前拼接好的串。
	}
	for(int i = 1;i <= anslen;i++)cout<<ans[i];
	return 0;
}
```


---

## 作者：fls233666 (赞：8)

刚刚学了 kmp，想找点简单的模版题刷，于是我找到了这题。

------------

首先，这题要先注意题面。如果你把合并单词的过程理解成“单词与单词合并”，你就会被 test 4 卡掉。~~【调了很久才发现】~~

正确的理解方式是：“**单词与合并完成的句子合并**”

想清楚题面问题后，我们只要把每个单词与合并完成的答案句子进行 kmp 匹配，匹配后删掉相应长度的单词前缀即可。

于是我敲出了下面这段代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#define rgt register int
using namespace std;

const int mxn = 1e6+6;

int n,f[mxn],nxt[mxn];
string words[mxn],ans="";

inline int kmp(string s1,string s2){
	memset(nxt,0,sizeof(nxt));  //重置next数组
	int ls1=s1.size(),ls2=s2.size();
	for(rgt j,i=1;i<ls2;i++){
		j=nxt[i];
		while(j&&s2[i]!=s2[j])
			j=nxt[j];
		if(s2[i]==s2[j])
			nxt[i+1]=j+1;
	}   //求next数组
    
	memset(f,0,sizeof(f));  //重置f数组，f[i]记录s1的第i个位置匹配到s2的第j个字符
	for(rgt j=0,i=0;i<ls1;i++){
		while(j&&s1[i]!=s2[j])
			j=nxt[j];
		if(s1[i]==s2[j])
			j++;
		f[i]=j;
	}
	return f[ls1-1];  //显然，f[s1的长度-1]就是重复的前缀长度
}

int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(rgt i=1;i<=n;i++)
		cin>>words[i];
        
	ans+=words[1];
	for(rgt l,i=2;i<=n;i++){
		l=kmp(ans,words[i]);
		words[i].erase(0,l);   //删掉对应前缀
		ans+=words[i];   //合并答案句子
	}
    
	cout<<ans;
	return 0;
}
```

然后，它在test 3超时了.....

----------

开始考虑如何进一步优化代码。

首先我们发现，上面的 f 数组是不需要的，我们最后返回 j 即可。因为 j 在最后记录的就是匹配成功的单词前缀长度。

其次，我们想到一个问题：**每次匹配都要从 ans 字符串的开头开始匹配吗？**

我们只想要知道匹配成功的后缀长度。而匹配成功的后缀长度最长也只能是 $\min(ans.size(),words_i.size())$。于是这里可以减少一次匹配需要花费的时间。

进行了上述优化，超时的问题就解决了。

另外，这题也可以用 hash 通过。有能力的人可以自行尝试一下。

下面是本人用 kmp 通过此题的完整代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#define rgt register int
using namespace std;

const int mxn = 1e6+6;

int n,nxt[mxn],lans,lw;
string words[mxn],ans="";

int main(){
  
	ios::sync_with_stdio(false);
	cin>>n;
	for(rgt i=1;i<=n;i++)
		cin>>words[i];
	ans+=words[1];
	lans=ans.size();
  
	for(rgt j,i=2;i<=n;i++){
       
               //为了节省函数调用需要的时间，把kmp写到了主函数里面
		lw=words[i].size();
		memset(nxt,0,sizeof(int)*lw);  //用更快的方法初始化next数组
		for(rgt ki=1;ki<lw;ki++){
			j=nxt[ki];
			while(j&&words[i][ki]!=words[i][j])
				j=nxt[j];
			if(words[i][ki]==words[i][j])
				nxt[ki+1]=j+1;
		}//求next数组
        
		int tp=lans<lw?lans:lw;  //取需要匹配的最小长度
		j=0;
		for(rgt ki=lans-tp;ki<lans;ki++){
			while(j&&ans[ki]!=words[i][j])
				j=nxt[j];
			if(ans[ki]==words[i][j])
				j++;
		}  //进行匹配
        
		words[i].erase(0,j);  //删除前缀
		ans+=words[i];  //合并答案串，更新答案串长度
		lans+=words[i].size();
	}
	cout<<ans;
	return 0;
}
```



---

## 作者：When (赞：7)

### 大!细节题

#### 算法

KMP

#### 思路

其实还蛮好想的，题目要求最长相同前后缀，于是想到$KMP$，每次将新单词放到原句前面再跑$KMP$，同时，为了防止$nxt$找到新单词后面，要在新单词与原句之间加一些分隔符号（如“￥%……@%”）。

**然而**，~~它毕竟是一道E题~~，这样会被第三个点卡掉（好像总共有**一百三十**多个点呢~），因为原句可能长达$1e6$，这样暴力合并显然是无法接受的。

考虑优化，不难发现，每一次的$nxt_n$最多不超过新单词的长度，于是我们只需要把$min({原句长度，新单词长度)}$的部分合并。

#### 注意！！！！

+ 不要每次用$memset$清空$nxt$，因为$memset$并不是$O(1)$的
+ 不要将$strlen$放在内部的$for$里面（不然会后悔的）
+ $string$大法好，**but**为了宁的生命安全，还是用$*char$吧
+ 一定要**想清楚**再开始写，~~不然你会像我一样调一下午~~

#### 代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e6 + 10;
int n,nxt[maxn],top;
char ans[maxn],s[maxn];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i){
        scanf("%s", s + 1);    
        if(i == 1){
            int len = strlen(s + 1);
            for(int j = 1; j <= len; ++ j) ans[++top] = s[j];
        }
        else{
            int lena = top, lenb = strlen(s + 1);
            int nlen = min(lena, lenb), cnt = lenb;
            s[++cnt] = '@';
            for(int j = 1; j <= nlen; ++ j) s[++cnt] = ans[lena - nlen + j];
            //cout << cnt << endl;
            nxt[0] = nxt[1] = 0; int j = 0;
            for(int k = 2; k <= cnt; ++ k){
                while(j && s[k] != s[j + 1]) j = nxt[j];
                if(s[k] == s[j + 1]) j += 1;
                nxt[k] = j;
            }
            for(int j = nxt[cnt] + 1; j <= lenb; ++ j) ans[++top] = s[j];
        }
    }
    for(int i = 1; i <= top; ++ i) cout << ans[i];
    cout << endl;
    return 0;
}
```



希望对宁有所帮助



---

## 作者：Buried_Dream (赞：5)

## 题意：

将字符串接起来，相邻的字符串的公共前后缀要只留下一个。

比如 `abcabc` 和 `bcd` 接起来就是 `abcabcd`。

## 思路：

我们考虑哈希。

用一个 $ans$ 数组来存储答案字符串。

有两个哈希数组，一个是子串的，一个是答案串的。

每读入一个子串，将这个字串的哈希值计算，然后与答案数组匹配，匹配到最优的地方后跳出来更新 $ans$ 数组和他对于的哈希数组。

## Code:

```cpp
/*
	Work by: TLE_Automation
*/
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
#define int long long
using namespace std;

const int N = 1e6 + 10;
const int MAXN = 2e5 + 10;

inline char readchar() {
	static char buf[100000], *p1 = buf, *p2 = buf;
	return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}

inline int read() {
#define readchar getchar
	int res = 0, f = 0;char ch = readchar();
	for(; !isdigit(ch); ch = readchar()) if(ch == '-') f = 1;
	for(; isdigit(ch); ch = readchar()) res = (res << 1) + (res << 3) + (ch ^ '0');
	return f ? -res : res;
}

inline void print(int x) {
	if (x < 0 ) putchar('-'), x = -x;
	if (x > 9 ) print(x / 10);
	putchar(x % 10 + '0');
}
const int base = 131;
typedef unsigned long long ull;

int has[N], pw[N], Hans[N];
char s[N], ans[N];
int sc = 0;


signed main() {
	int Q = read();
	pw[0] = 1;
	for(int i = 1; i <= N; i++) pw[i] = pw[i - 1] * base;
	for(int i = 1; i <= Q; i++) {
		cin >> (s + 1);
		int Len = strlen(s + 1);
		int wz = 0;
		for(int j = 1; j <= Len; j++) has[j] = (has[j - 1] * base + s[j]);
		for(int j = min(Len, sc); j >= 0; j--) {
			if(has[j] == Hans[sc] - Hans[sc - j] * pw[j]) {
				wz = j; break;
			}
		}
		for(int j = wz + 1; j <= Len; j++) {
			ans[++sc] = s[j];
			Hans[sc] = Hans[sc - 1] * base + (ans[sc]);
		}
	}
	for(int i = 1; i <= sc; i++) cout << ans[i];
	return 0;
}

---

## 作者：Soulist (赞：5)

这道题也是非常毒了。。。

~~主要是题意，我猜应该有很多人和我一样以为是合并$i$和$i-1$吧~~

~~实际上~~题意是说每新读入一个新字符串就将其和已有的字符串合并。

$Sol.$

考虑每次新加入一个单词，我们可以枚举一个长度，判断其前缀和已有字符串的后缀是否相同。

这个相同用$hash$判就好了。

然后暴力算的话复杂度会带个$\log$，所以还要预处理一下每个数前面的系数的$k$次方在$\%hash$意义下是多少。

这样就是$O(S)$了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep( i, s, t ) for( register int i = s; i <= t; ++ i )
#define re register
#define int long long
int read() {
	char cc = getchar(); int cn = 0, flus = 1;
	while(cc < '0' || cc > '9') {  if( cc == '-' ) flus = -flus;  cc = getchar();  }
	while(cc >= '0' && cc <= '9')  cn = cn * 10 + cc - '0', cc = getchar();
	return cn * flus;
}
const int mod = 1e9 + 7 ;
const int mod2 = 1e9 + 9 ;
const int ha = 233 ; 
const int ha2 = 377 ;
const int N = 1e6 + 5 ;
int n, cnt, r, inv[N], inv2[N] ;
char out[N], s[N] ; 
signed main()
{
	n = read() ; int Maxa = 1e6 ; inv[0] = 1, inv2[0] = 1 ; 
	rep( i, 1, Maxa ) inv[i] = ( inv[i - 1] * ha ) % mod, inv2[i] = ( inv2[i - 1] * ha2 ) % mod ; 
	rep( i, 1, n ) {
		scanf("%s", s + 1 ) ;
		r = strlen( s + 1 ) ; 
		int hash1 = 0, hash2 = 0 ;
		int hash12 = 0, hash22 = 0 ;
		int k = min( r, cnt ), ans = 0 ;
		rep( i, 1, k ) {
			hash1 = ( hash1 * ha + s[i] ) % mod ;
			hash2 = ( hash2 + out[cnt - i + 1] * inv[i - 1] ) % mod ;
			hash12 = ( hash12 * ha2 + s[i] ) % mod ;
			hash22 = ( hash22 + out[cnt - i + 1] * inv2[i - 1] ) % mod ;
			if( hash1 == hash2 && hash12 == hash22 ) ans = i ;
		}
		for( int i = ans + 1; i <= r; ++ i ) out[++ cnt] = s[i] ;
	}
	rep( i, 1, cnt ) printf("%c", out[i] ) ;
	return 0;
}

```

---

## 作者：封禁用户 (赞：4)

#### 思路

使用哈希算法

每次用哈希求最长公共前后缀

但是只能当更新字符串时求哈希，时间复杂度最大为 $ 10 ^ 6 $ 

可以过

#### 代码

单哈希就过了 $ QWQ $

```
#include <bits/stdc++.h>
using namespace std; 
#define sed 131
#define mod 998244353
typedef long long ll;
const int N = 1000000 + 5; 
int t , n , m;
ll h[N] , H[N] , pw[N];
char s[N] , ans[N];
int query(int l , int r)
{
	if(l > r) return 0;
	return (H[r] - H[l - 1] * pw[r - l + 1] % mod + mod) % mod;
}
void debug()
{
	cout << m << endl;
	for(int i = 1 ; i <= m ; ++ i) cout << ans[i];
	cout << endl;
}
int main()
{
	cin >> t;	
	pw[0] = 1;
	for(int i = 1 ; i < N ; ++ i ) pw[i] = pw[i - 1] * sed % mod;
	for(int i = 1 ; i <= t ; ++i )
	{
		cin >> (s + 1);
		n = strlen(s + 1);
		int l = 0;
		for(int j = 1 ; j <= n ; ++ j) h[j] = (h[j - 1] * sed % mod + s[j]) % mod;
		for(int j = min(n , m) ; j >= 0 ; -- j)
		{
			if(h[j] == query(m - j + 1 , m)) 
			{
				l = j;
				break; 
			}
		}
		for(int j = l + 1 ; j <= n ; ++ j){
			ans[++m] = s[j];
			H[m] = (H[m - 1] * sed % mod + s[j]) % mod;
		}
//		debug();
	}
	for(int i = 1 ; i <= m ; ++ i) cout << ans[i];
	return 0;	
}

---

## 作者：ningago (赞：3)

暴力数据结构做法。

需要意识到区间多项式定值求值是可以线段树维护的。

式子：$a_l+a_{l+1}x^1+a_{l+2}x^2+\cdots+a_{r}x^{r-l}=\dfrac{pre(r)-pre(l-1)}{x^{l-1}}$

其中 $pre(t)=a_1+a_2x^1+a_3x^2+\cdots+a_tx^{t-1}$。

于是可以利用哈希优化暴力判断两子串是否相等。

复杂度 $O(m\log m)$，$m=10^6$。

其它思路都跟暴力一样，由于只需要单点插入，树状数组甚至直接前缀和就可以维护。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define N 1000010
#define mod 998244353
#define int long long

int n;
const int base = 121;
int basepow[N];
int basepowinv[N];
int tr[N];
int ksm(int a,int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1)
			res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

void add(int x,int z)
{
	while(x <= N - 10)
	{
		tr[x] = (tr[x] + z) % mod;
		x += (x & (-x));
	}
}

int query(int x)
{
	int res = 0;
	while(x)
	{
		res = (res + tr[x]) % mod;
		x -= (x & (-x));
	}
	return res;
}

void init()
{
	basepow[0] = 1;
	for(int i = 1;i <= N - 10;i++)
		basepow[i] = basepow[i - 1] * base % mod;
	basepowinv[0] = 1;
	basepowinv[1] = ksm(base,mod - 2);
	for(int i = 2;i <= N - 10;i++)
		basepowinv[i] = basepowinv[i - 1] * basepowinv[1] % mod;
}

int query_hash(int l,int r)
{
	int t = query(r) - query(l - 1);
	t = (t + mod) % mod;
	t = t * basepowinv[l - 1] % mod;
	return t;
}

char str[N];
char ans[N];
int top;

int getid(char x)
{
	if('0' <= x && x <= '9')
		return x - '0' + 1;
	if('A' <= x && x <= 'Z')
		return 11 + x - 'A';
	return 10 + 26 + 1 + x - 'a';
}

signed main()
{
	init();
	scanf("%lld",&n);
	int idx = 0;
	for(int i = 1;i <= n;i++)
	{
		scanf("%s",str + 1);
		int m = strlen(str + 1);
		int s = 1;
		int now = 0;
		for(int j = 1;j <= m;j++)
		{
			now += getid(str[j]) * basepow[j - 1] % mod;
			now %= mod;
			if(idx - j + 1 >= 1 && now == query_hash(idx - j + 1,idx))
			{
				s = j + 1;
			}
		}
		for(int j = s;j <= m;j++)
		{
			idx++;
			add(idx,getid(str[j]) * basepow[idx - 1]);
			ans[++top] = str[j];
		}
	}
	for(int i = 1;i <= top;i++)
		putchar(ans[i]);
	return 0;
}
```

---

## 作者：WJX3078 (赞：3)

# 1.题意简述
给定n个字符串，将其从左到右依次合并，并在合并时去重（去重的定义：找最大的i(i≥0),满足第一个单词的长度为i的后缀和第二个单词长度为i的前缀相等,然后把第二个单词第i位以后的部分接到第一个单词后面）。

# 2.题解
这是一道裸的KMP算法的题。~~前缀、后缀、最大相同的位置已经暴露了本题算法~~

既然已经确定了算法，那我们就来想一想以谁为模式串？由题意知，单词的总长度不超过1e6，~~（众所周知，OI中的不超过就是最大数据为1e6）~~如果我们以最终的答案串为模式串，那肯定会被T飞的。

这时候，就需要我们脑动优化时间复杂度，我们可以观察到最长匹配长度（题意简述中的i）<=min（答案串长度，新字符串长度）。那我们只需要将答案串中后min（答案串长度，新字符串长度）和新字符串中前min（答案串长度，新字符串长度）放在一起组成模式串，在对这个模式串进行一遍KMP即可。

每当我们得意之时，现实总会给我们当头一棒。因为以上算法过不了以下样例

	答案串:ababa
    新字符串:baba
	合并后的模式串:ababababa
	前缀:a,ab,aba,abab,ababa,ababab,abababa,abababab,ababababa
	后缀:a,ba,aba,baba,ababa,bababa,abababa,babababa,ababababa
很明显，这时i=7，等等，这不是跨过了两个字符串了吗？不符合最长匹配长度（题意简述中的i）<=min（答案串长度，新字符串长度）。那我们是不是要从头在来了呢？也不是，三峡不是可以将江面分成两半吗，我们也可以在这两个字符串中间加一点东西隔开它们。题目保证了每个单词都是非空的，由大小写英文字母和数字组成，那只要加一些不是英文字母和数字的字符进去即可。

# 3.好了，讲了这么久，就上代码吧
```cpp
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define ll long long
#define gc getchar
#define R register
using namespace std;
//---------------------初始函数-------------------------------
//初始函数中都是一些优化，没有也没太大影响
il int read(){
	R int x=0;R bool f=0;R char ch=gc();
	while(!isdigit(ch)) {f|=ch=='-';ch=gc();}
	while(isdigit(ch)) {x=(x<<1)+(x<<3)+(ch^48);ch=gc();}
	return f?-x:x;
}

il int max(int a,int b) {return a>b?a:b;}

il int min(int a,int b) {return a<b?a:b;}


//---------------------初始函数-------------------------------

const int MAXN=1e6+10;
int n,len,anslen,top,minlen;//len:新字符串的长度，anslen:答案串的长度，top:合并后模式串的长度，minlen:min（答案串长度，新字符串长度）
int kmp[MAXN];//用于匹配失配数组
char ans[MAXN],opt[MAXN];//ans:答案串,opt:新字符串

signed main(){//signed main==int main
	n=read();
	for(R int i=1;i<=n;++i){
		scanf("%s",opt+1);//将其整体往右移一位，方便之后的处理
		top=len=strlen(opt+1);
		minlen=min(anslen,len);
		opt[++top]='~';//将答案串和新字符串隔开
		for(R int j=1;j<=minlen;++j) opt[++top]=ans[anslen-(minlen-j)];//合并后的模式串
        //KMP算法求失配数组
		kmp[0]=0;kmp[1]=0;
		for(R int j=1;j<top;++j){
			int k=kmp[j];
			while(k&&opt[k+1]!=opt[j+1]) k=kmp[k];
			if(opt[j+1]==opt[k+1]) {++k;}
			kmp[j+1]=k;
		}
         //KMP算法求失配数组
		for(R int j=kmp[top]+1;j<=len;++j) ans[++anslen]=opt[j];
        //kmp[top]表示最长匹配长度，那kmp[top]+1到len就是答案串和新字符串不重合的部分，就将其加入到答案串中
	}
	for(R int i=1;i<=anslen;++i) printf("%c",ans[i]);
	return 0;
}
```


---

## 作者：OldPan (赞：3)

我的第一篇 *luogu* 题解

### 题目
[CF1200E Compress Words](https://www.luogu.com.cn/problem/CF1200E)

大意: 按给定顺序合并 *N* 个字符串(总长 *S* ), 要求每次合并单词的最长前缀.  ( $N\leq10^5,\ S\leq 10^6$ )

比如, *last* $+$ *step* $=$ *lastep*; *moon* $+$ *on* $=$ *moon*

### 简析
> 一道字符串的题目关系前后缀, 则 *KMP* 有很大嫌疑

研究题目性质, 发现一个字符 *B* 若要接到 *A* 的后面,则**重合部分的长度最多为 *B* 的长度**, 于是直接在 *A* 的末尾匹配 *B*

```cpp
void KMP(char B[M], int len){
    int j = 0;
    REP(i, max(1, top-len+1), top){
        while(j && A[i] != B[j+1]) j = Next[j];
        if(A[i] == B[j+1]) ++j;
    }
    while(j < len) A[++top] = B[++j];
}
```

复杂度 $O(S)$

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#define REP(i, a, b) for(int i=(a); i<=(b); ++i)
using namespace std;

const int N=1e5+9, M=1e6+9;
int n, m;
int lens; char s[M];
int top; char S[M];
int Next[M];

void init_Next(char s[M], int len){
    int j=0;
    REP(i, 2, len){
        while(j && s[j+1] != s[i]) j = Next[j];
        if(s[j+1] == s[i]) ++j;
        Next[i] = j;
    }
}

void KMP(char s[M], int len){
    int j=0;
    REP(i, max(1, top-len+1), top){
        while(j && S[i] != s[j+1]) j = Next[j];
        if(S[i] == s[j+1]) ++j;
        // if(j==len) j = Next[j];		// (⊙_⊙)
    }
    while(j<len) S[++top] = s[++j];
}

int main(){
    scanf("%d", &n);
    REP(i, 1, n){
        scanf("%s", s+1), lens=strlen(s+1);
        init_Next(s, lens);
        KMP(s, lens);
    }
    REP(i, 1, top) putchar(S[i]);	// putchar 比 printf 速度更快~
    return 0;
}
```
总时间 *1.81 s*

---

## 作者：Clyfort (赞：2)

# Solution
假设前 $i - 1$ 个字符串已经进行了合并，组合成了字符串 $t$，现在要将字符串 $s$ 与 $t$ 进行合并。

只需要算出字符串 $s$ 的前缀函数值，再以此算出 $t$ 最后一个字符的前缀函数值，就能够知道 $s$ 与 $t$ 重合的部分。

考虑使用离线版 `KMP`，由于有很多字符串，每次添加一个新的字符串，$t$ 都会发生变化，于是又要重新计算 $t$ 的前缀函数值。时间复杂度 $\mathcal{O}(n \times |s|)$，超时。

因为需要计算 $s$ 和 $t$ 的重合部分最长值，相当于计算 $t$ 最后一个字符的前缀函数值 $p$，则 $p$ 定不会超过 $|s|$，所以只需要 $t$ 中末尾的 $|s|$ 个字符，计算这些字符的前缀函数值，这样 $p$ 能够保证正确，虽然其他 $|s| - 1$ 个字符的前缀函数值不能保证正确，但是不难发现，它们不影响 $p$ 的计算。尽管这样也需要做 $n$ 次前缀函数值的计算，但是整体长度只有 $10^6$，所以时间复杂度为 $\mathcal{O}(|s|) = \mathcal{O}(10^6)$。

# Tip
本题每次合并是与前面已经合并完的整个字符串进行合并，而不是与前一个字符串进行合并。

# Code
```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;

int n;
vector <int> p;
char s[maxn], t[maxn];

void prefix(int len)
{
    p[0] = 0;
    for (int i = 1; i < len; i ++)
    {
        int j = p[i - 1];
        while (j > 0 && s[i] != s[j])
            j = p[j - 1];
        if (s[i] == s[j])
            j ++;
        p[i] = j;
    }
}

// 计算 s 和 t 的重合部分，相当于将 t 中 |s| 个字符添加到 s 末尾
int KMP(int len1, int len2)
{
    int pre = 0, pos = max(len2 - len1, 0);
    if (s[0] == t[pos])
        pre ++;
    for (int i = pos + 1; i < len2; i ++)
    {
        int j = pre;
        while (j > 0 && t[i] != s[j])
            j = p[j - 1];
        if (t[i] == s[j])
            j ++;
        pre = j;
    }
    return pre;
}

int main()
{
    cin >> n;
    cin >> t;
    int lent = strlen(t);
    for (int i = 2; i <= n; i ++)
    {
        cin >> s;
        int lens = strlen(s);
        int cnt;
        p.resize(lens);
        prefix(lens);
        cnt = KMP(lens, lent);
        for (int j = cnt; j < lens; j ++)
            t[lent ++] = s[j];
    }
    cout << t;
    return 0;
}
```

---

## 作者：ezoiHQM (赞：2)

利用哈希表，加入一个串时直接暴力枚举相同的长度判断是否相等然后合并就行了。

但是这是CF的题，用哈希很容易被Hack

一开始写了两个base+一个模数被Hack了

然后两个base+双模数还是被Hack了

然后又改成了三个base+三个模数还是被Hack了......（orz zh大佬）

于是就改成了随机三base三模数

有人有兴趣卡的话可以去CF卡一下：[58846690](http://codeforces.com/problemset/submission/1200/58846690)

还有一个提交是另一个同机房大佬的，也可以去尝试一下：[58847045](http://codeforces.com/problemset/submission/1200/58847045)
```cpp
#include<ctime>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int mod1,mod2,mod3;
long long base1,base2,base3;
const int L=1000010,N=10000010;
int n,lens,lent,tot,hashs1[L],hasht1[L],bs1[L],hashs2[L],hasht2[L],bs2[L],hashs3[L],hasht3[L],bs3[L],prm[N],vis[N];
char s[L],t[L];
void init(){
	for(int i=2;i<N;i++){
		if(!vis[i])
			prm[tot++]=i;
		for(int j=0,p=prm[j],k=p*i;j<tot&&k<N;j++,p=prm[j],k=p*i){
			vis[k]=1;
			if(!(i%prm[j]))
				break;
		}
	}
	return;
}
int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	srand(time(NULL));
	init();
	int x=((rand()<<15ll)+rand())%(tot/2);
	x+=tot/2;
	mod1=prm[x];
	x=((rand()<<15ll)+rand())%(tot/2);
	x+=tot/2;
	mod2=prm[x];
	x=((rand()<<15ll)+rand())%(tot/2);
	x+=tot/2;
	mod3=prm[x];
	x=((rand()<<15ll)+rand())%(tot/2);
	base1=prm[x];
	x=((rand()<<15ll)+rand())%(tot/2);
	base2=prm[x];
	x=((rand()<<15ll)+rand())%(tot/2);
	base3=prm[x];
	lens=strlen(s+1);
	bs1[0]=bs2[0]=bs3[0]=1;
	for(int i=1;i<=1000000;i++)
		bs1[i]=bs1[i-1]*1ll*base1%mod1,bs2[i]=bs2[i-1]*1ll*base2%mod2,bs3[i]=bs3[i-1]*1ll*base3%mod3;
	for(int i=1;i<=lens;i++)
		hashs1[i]=(hashs1[i-1]*1ll*base1+s[i])%mod1,hashs2[i]=(hashs2[i-1]*1ll*base2+s[i])%mod2,hashs3[i]=(hashs3[i-1]*1ll*base3+s[i])%mod3;
	for(int i=2;i<=n;i++){
		scanf("%s",t+1);
		lent=strlen(t+1);
		for(int j=1;j<=lent;j++)
			hasht1[j]=(hasht1[j-1]*1ll*base1+t[j])%mod1,hasht2[j]=(hasht2[j-1]*1ll*base2+t[j])%mod2,hasht3[j]=(hasht3[j-1]*1ll*base3+t[j])%mod3;
		for(int j=min(lens,lent);j>=0;j--)
			if((hashs1[lens]-1ll*hashs1[lens-j]*bs1[j]%mod1+mod1)%mod1==hasht1[j]&&(hashs2[lens]-1ll*hashs2[lens-j]*bs2[j]%mod2+mod2)%mod2==hasht2[j]&&(hashs3[lens]-1ll*hashs3[lens-j]*bs3[j]%mod3+mod3)%mod3==hasht3[j]){
				for(int k=lens+j+1;k<=lens+lent;k++)
					hashs1[k-j]=(hashs1[k-j-1]*1ll*base1+t[k-lens])%mod1,hashs2[k-j]=(hashs2[k-j-1]*1ll*base2+t[k-lens])%mod2,hashs3[k-j]=(hashs3[k-j-1]*1ll*base3+t[k-lens])%mod3,s[k-j]=t[k-lens];
				lens+=lent-j;
				break;
			}
	}
	s[lens+1]='\0';
	printf("%s",s+1);
	return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

最长相同前后缀，考虑 KMP。

对于当前答案串 $q$，要合并的单词 $s$，求出 $s+q$ 的 border 即为最长相同前后缀。

注意到 $q$ 的长度可能相当长，而 border 长度不超过 $|s|$，所以只需要截取 $q$ 长度为 $\min(|q|,|s|)$ 的后缀即可。

注意到所求前后缀不应相交，可以在 $s$ 与 $q$ 之间加入特殊字符解决。
```cpp
#include <string>
#include <iostream>
using namespace std;
int n, K[1000050];
string s, q, a;
int main()
{
    cin >> n;
    for (int i = 1, l, m; i <= n; ++i)
    {
        cin >> s;
        l = min(s.length(), q.length());
        a = s + '\0' + q.substr(q.length() - l); //截取 q 的后缀，加入特殊字符
        m = a.length();
        a = '\0' + a;
        for (int i = 2, j = 0;i <= m;++i) //KMP
        {
            while(j && a[i] != a[j + 1]) j = K[j];
            K[i] = j += a[i] == a[j + 1];
        }
        q += s.substr(K[m]);
    }
    cout << q;
    return 0;
}
```


---

## 作者：智子 (赞：1)

## 题意简述

- 给定 $n$ 个单词，将这 $n$ 个单词从前往后拼接在一起，若相邻两个单词的后缀和前缀相同则将其重合在一起。

- 如输入 sample please ease in out，sample 与 please 拼接得 samplease，samplease 与 ease 拼接仍得 samplease，最终得 sampleaseinout

## 题目分析

题目的关键在于求出两个字符串之间的最长公共部分，即相等的前缀与后缀。这很容易让人联想到 KMP 的 $next$ 数组，它的定义是一个字符串的前缀的最长的相同的前缀与后缀的长度，$next[len - 1]$ 的定义就是这个字符串的最长的相同的前缀与后缀的长度。

因此，对于字符串 $s1$ 和 $s2$，我们只需要将 $s2$ 拼接在 $s1$ 前面，例如将 sample 与 please 拼接为 pleasesample，再求出这个字符串的 $next[len - 1]$ 等于 $2$，就可以简单地得到公共部分为 ple，再从 $2$ 开始截取 please 的后半部分 ease 拼接到 sample 后面即可。

对于 $n$ 个字符串，则应该按照上面的方法依次拼接。

P.S. 一个优化：因为两个字符串之间的最长公共部分的长度显然不可能大于其中任意一个字符串的长度，所以在一开始拼接时，只需要求出两个字符串中较短的的长度 $l$，将第一个字符串的后 $l$ 个字符拼接到第二个字符串后面，再求 $next[len - 1]$ 的值。

同时，为了防止求next时将另一个字符串也算进来，导致“共同部分”跨过两个字符串之间，要在中间插入一段数据中几乎不可能出现的字符串。因为如果某个真子串在字符串中只出现一次，最长的相同前后缀就不可能包括这个字串，也就杜绝了求出的长度越过两个字符之间的可能性。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000000 + 500;

int nxt[MAXN];

int getNext(string s2) {
	nxt[0] = -1;
	int i = 0, j = -1;
	int len2 = s2.size();
	while(i < len2) {
		if(j == -1 || s2[i] == s2[j]) {
			i++;
			j++;
			nxt[i] = j;
		} else {
			j = nxt[j];
		}
	}
	return j;
}

int main() {
	string s, ans;
	int n, len;
	
	cin >> n >> s;
	ans = s;
	for(int i = 2; i <= n; i++) {
		cin >> s;
		len = min(ans.size(), s.size()); //显然，共同部分的长度不会超过两个字符串中的任何一个
        //为了防止求next时将另一个字符串也算进来，导致“共同部分”跨过两个字符串之间，要在中间插入一段数据中几乎不可能出现的字符串
		string tmp = s + "Idealistoj neniam maljuniĝas." + ans.substr(ans.size() - len);
		int res = getNext(tmp); //求出相同的最长前缀和后缀，即两个字符串的公共部分的长度
		ans += s.substr(res); //0 ~ res-1 的部分都是与s的公共部分，只要将res之后的部分接到ans后面既可以了
	}
	
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：世末OIer (赞：1)

赛场上用KMP水过，这里介绍用Z算法AC的方法

Z Algorithm

对Z算法不熟悉的可以去[我的博客](https://www.luogu.org/blog/gaofeiji/qian-tan-z-suan-fa)里了解一下


```cpp
#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
using namespace std;
int n;
string s[100005],t;
int z[2000005];
inline void calc_z(string s){         //计算所有的z[i]
	for(int i=0;i<s.size();++i)z[i]=0;
    int l=0,r=0,n=s.size();
    for(int i=1;i<n;++i){
        if(i<=r)z[i]=min(r-i,z[i-l]);
		for(;i+z[i]<n&&s[z[i]]==s[i+z[i]];)++z[i];
		if(i+z[i]>r)l=i,r=i+z[i]; 
    }
    return;
}
int main(){
	ios_base::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=0;i<n;++i)cin>>s[i];
	t=s[0];
	for(int i=1;i<n;++i){
		string st=s[i]+'$'+t.substr(max(0,int(t.size()-s[i].size())));  //连接起来。这是一个贪心，只用截取与它的长度相等的字符串与它匹配。多的肯定匹配不上
		calc_z(st);
		int mx=st.size();
		for(int j=st.size()-1;st[j]!='$';--j)if(j+z[j]==st.size())mx=j;  //如果j+z[j]==st.size(),说明完全重合，则答案更新
		int len=st.size()-mx;
		for(int j=len;j<s[i].size();++j)t+=s[i][j];
	}
	cout<<t<<endl;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题意

给你 $n$ 个字符串，要求把他们拼接在一起，相同的部分可以互相重合。

## 思路

看到字符串和相同的部分，想到 $\text{KMP}$ 匹配算法，由于相同的部分肯定是最长的相同的部分，所以想到 $\text{KMP}$ 的 $\text{next}$ 数组。

假如我们要把 $s_1$ 和 $s_2$ 这两个字符串合并，那么如何求出它们最长可以重叠的部分呢？我们可以将 $s_2$ 和 $s_1$ 完完全全拼接起来，注意，$s_2$ 在前面。这样的话最长的重叠部分的长度就是这个新的字符串的最长公共前后缀了！

我们来分析一下这个算法的复杂度：

由于要合并 $n$ 个串，一共有 $10^5$ 个串，总长度为 $10^6$，所以复杂度大概就是 $O(n|s|) = O(10^5 \times 10^6) = O(10^{11})$，kls 来了都要叹气。

我们想，假设之前那个串满足条件 $|s_1| > |s_2|$，那么显然 $s_2 + s_1$ 这个字符串的最长公共前后缀最长也就只有 $|s_2|$ 这么长，所以我们可以截取 $s_1$ 的后 $|s_2|$ 位为 $s_3$，这样我们只用求 $s_3 + s_2$ 的最长公共前后缀就可以了。

我们发现，这样做的复杂度最多是 $O(2|s|)$ 的，而 $|s|$ 是 $10^6$ 级别的，**在时间复杂度上是可以过的。**

但是，我们写完代码，发现提交到 Codeforces 上奇妙的 WA 了，这并不是你代码写错了，而是上面算法的正确性有问题，本题解的精髓就来了。

为了方便表示，我们令上述算法 $s_3 + s_2$ 为字符串 $s_4$。我们可以发现，当 $s_4$ 的最长公共前后缀的长度 $> |s_3|$ 时（由于 $|s_2| = |s_3|$，所以描述了 $s_4 > s_3$ 后，$s_4 > s_2$ 就是必然的），我们会发现错误，因为最长公共前后缀的长度都大于了 $s_3$，还讲什么重叠不重叠呢？

可能有人听不懂，放个样例来看看：

```
2
010 101
```

显然此时的 $s_4$ 为 $101010$，我们发现最长公共前后缀长度为 $4$，但是合并出来的结果是 $010101$，这时因为 $4 > |010|$，这个最长重叠的串在 $010$ 与 $101$ 中都没有出现过。

这下听懂了吧！我们可以将 $s_4$ 设为 $s_3 + c + s_2$，其中 $c$ 是什么，待会再讲。

现在来解释这个神奇的 $c$，**理论来讲**，$c$ 可以为任意一个字符。本人曾经耗费精力证明 $c$ 为一个字符是假的，但事实证明是本人假了。

**下面内容想深究的可以看，不然可以直接看代码。**

我们可以简单构造一组数据：

```
3
1 1 1
```

本来希望程序输出个错误结果，没想到输出了 $1$。

我们思考为什么会输出 $1$，我们拼接的 $s_4$ 为 $101$，而 $0$ 为 $c$，此时我们发现，哦！由于 $\text{next}$ 数组的定义是所有前缀的最长公共**真**前后缀，所以其实 $101$ 的最长公共前缀为 $1$，可以证明所有这种情况以及其他情况都会得出正确结果。

那为什么有的题解 $c$ 为一个字符串过了呢？下面解释：

我们设 $c$ 为 `IAKIOI!!!`

那么下面这组样例即可卡掉：

```
2
IAKIOI!!! IAKIOI!!!IAKIOI!!!
```

此时我们在中间加上 `IAKIOI!!!` 就会变成这样：

```
IAKIOI!!!IAKIOI!!!IAKIOI!!!IAKIOI!!!
```

此时显然最长公共前后缀为 $3$ 个 `IAKIOI!!!`，而这个长度要比输入的两个字符串都要长，所以会错。

我们得出结论，对于任意的 $c$，我们总是可以出以下这组数据卡掉：

```
2
c cc
```

其中 $c$ 代表的是一个字符串。

但是字符串组合这么多，所以没有出全，所以才会有 $c$ 为一个长度 $> 1$ 的字符串时 AC 了。

上面的 hack 仅适用于第一种暴力算法，并且没有考虑 $|s_1| < |s_2|$，更多的 $\text{hack}$，可以在 Codeforces 上找。

最后注意，这种情况只适用于 $|s_1| > |s_2|$ 的情况，至于 $|s_1| < |s_2|$ 的情况，跟上面的差不多，这里就不多说了。

## 代码

代码就好理解了：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 5;

int n;
int nxt[N];
string s[N], ans;

int getnxt(string t){ //求 next 数组
	int i = 0, j = -1;
	nxt[0] = -1;
	for(; i < t.size(); ){
		if(j == -1 || t[i] == t[j]){
			nxt[++i] = ++j;
		}
		else{
			j = nxt[j];
		}
	}
	return j;   //这里的 j 表示最长公共前后缀的长度，也可以用 nxt[n] 表示
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> s[i];
	}
	ans = s[1];
	for(int i = 2; i <= n; ++i){
		int len = min(ans.size(), s[i].size()), res = 0;  //这里要考虑 s1 < s2 的情况
		int start = ans.size() - len;  //开始的位置
		string tmp = s[i] + "w" + ans.substr(start);  //中间加字符
		res = getnxt(tmp);
		res = min(res, len);   //要考虑 < 的情况
		ans += s[i].substr(res);
	}
	cout << ans;
	return 0;
}
```

---

## 作者：SunsetSamsara (赞：0)

## 前置知识
KMP
## 分析
### 题意
1. 输入一堆字符串，你需要把它们拼接起来，相同的地方只需保留一次，求最后拼成什么
2. （简化了的题意？）输入一堆字符串，输出最短的包含每个字符串（按顺序出现）的字符串


### 思路
首先维护一个当前的字符串答案，每次插入时字符串匹配，匹配到最后时的下标就是相同的地方，后面直接插入。

然后注意这里有一些可以优化的地方。

1. 获取 nxt 数组时因为匹配时只需匹配答案串，所以只需要枚举到 $\min\{l1, l2\}$ 即可
2. 匹配时因为只需匹配后缀，所以只需从 $l1 - \min\{l1, l2\} + 1$ 开始匹配。

这道题就做完了。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int nxt[1000001];
int l1, l2;
void getnxt(const char * cstr) {
	nxt[1] = 0;
	for (int i = 2, j = 0; i <= l1 && i <= l2; ++ i) {
		while (j && cstr[i] != cstr[j + 1])
			j = nxt[j];
		if (cstr[i] == cstr[j + 1]) ++ j;
		nxt[i] = j;
	}
}
// 获取 nxt 数组 
int match(const char * str1, const char * str2) {
	int ret = 0;
	for (int i = l1 - min(l1, l2) + 1; i <= l1; ++ i) {
		while (ret && str1[i] != str2[ret + 1])
			ret = nxt[ret];
		if (str1[i] == str2[ret + 1])
			++ ret;
	}
	return ret;
}
// 字符串匹配 
char ans[2000001];
int cnt;
void insert(const char * cstr) {
	l2 = strlen(cstr + 1);
	getnxt(cstr);
	int k = match(ans, cstr);
	// 在 k 个之后才有没匹配的部分 
	for (int i = k + 1; i <= l2; ++ i)
		ans[++ l1] = cstr[i];
}
int n;
char str[1000001];
int main() {
	scanf("%d%s", &n, ans + 1);
	l1 = strlen(ans + 1);
	for (int i = 1; i < n; ++ i) {
		scanf("%s", str + 1);
		insert(str); // 插入 
	}
	printf("%s\n", ans + 1);
}
```

---

## 作者：让风忽悠你 (赞：0)


[原题](https://www.luogu.com.cn/problem/CF1200E)
## 前言

萌新刚学 KMP 的第一篇题解。

## 题意

给出 $n$ 个单词，要求将这 $n$ 个单词组合成一个句子，即要找到最大的 $i (i≥0)$，满足第一个单词的长度为 $i$ 的后缀和第二个单词长度为 $i$ 的前缀相等，然后把第二个单词第 $i$ 位以后的部分接到第一个单词后面。

## 做法

不难想到将后一个单词和前一个单词合并为一个单词，然后对这个单词做 KMP，**注意是后一个单词在前**，因为我们要求的是后一个单词的前缀和后一个单词的后缀。

但是我们会看到单词数是 $10^5$，而单词长度到了 $10^6$，显然会炸空间，所以可以考虑只记录答案串和当前串。

此时提交就会发现在第三个点就 T 了，**为啥会这样呢**，因为我们前面是将整个答案串记录起来，所以答案串有可能很长很长，那就会导致做 KMP 时枚举了一个很长的串。**如何解决这个问题呢**，想一想可以发现，因为当前串的长度是固定，所以公共部分必然是不会大于当前串的长度，所以表示前缀和后缀的字符串的长度必然都不会超过 $\min(\text{答案串长度,当前串长度})$。

## 代码

```cpp
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define N 100005
#define M 1000005

using namespace std;

int n; 
string s,ans,cur;
int nxt[M];

inline int kmp(string s){
	int n=s.size(),j=0;
	s=' '+s; // 前加一个空格让字符串从一开始 
	nxt[1]=nxt[0]=0; // 不用把 nxt 数组清空 
	for(int i=2;i<=n;++i){
		while(j && s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) ++j;
		nxt[i]=j;
	}
	return nxt[n];
} 

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		cin>>s;
		if(i==1) ans+=s;
		else{
			int minn=min(s.size(),ans.size());
			int len=kmp(s+'#'+ans.substr(ans.size()-minn,minn)); // substr中第一个数表示开始位置，第二个数表示字符串长度 
			for(int j=len;j<s.size();++j)
				ans+=s[j];
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：弦巻こころ (赞：0)

## 这道题还是挺裸的,就是太坑了!

题意：给你n个单词，然后把n个单词变成一个句子，每次合并都是将之前单词形成的句子与当前单词合并合并两个单词的时候,要找到最大的$i$,满足第一个单词的长度为$i$的后缀和第二个单词长度为$i$的前缀相等,然后把第二个单词第$i$位以后的部分接到第一个单词后面.输出最后那个单词.

思路：这道题思路其实~~非常简单，(就是一个KMP板子题)~~。

我们发现它要求的其实就是$kmp$板子(求一个字符串的前缀与另一个字符串的后缀的最大相同子串),所以我们可以每次对单词和之前答案求个$kmp$。然后求$n$次$kmp$,但交上去却发现$T$掉了。

为什么呢？ 因为到最后答案串的长度非常大，每次求得时间复杂度可以视为$1e6$.那这样时间复杂度最差就为 $O(nm)$的，而$n$为$1e5$,$m$为$1e6$,这样肯定就$T$掉了

考虑优化算法。

由于每次$kmp$我们都只是求答案串的后缀与当前单词的前缀,所以我们最多截取 答案串与当前单词的长度取$min $的值跑$kmp$ 就行了.

需要注意的小细节挺多的,详见代码.

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
char ans[1000005],s[1000005],str[1000005];
int kmp[1000015];
int  KMP(char *a,int la)
{
	for(int i=0;i<=la;++i)kmp[i]=-1;
	for(int i=1;i<la;i++)
	{
		int j=kmp[i-1];
		while((~j)&&a[j+1]!=a[i])
		{
			j=kmp[j];
		}
		if(a[j+1]==a[i])j++;
		kmp[i]=j;
	}
	int j=kmp[la-1]//由于答案串可能自己匹配自己,所以我们需要跳到单词串上
	while(j>=la/2)//直到跳到单词串上才行
	{
		j=kmp[j];
	}
	return j+1;
}
int main()
{
	scanf("%d",&n);
	cin>>ans;
	int L=strlen(ans);
	for(int i=2;i<=n;i++)
	{
		scanf("%s",s);
		int l=strlen(s);
		int ne=min(l,L);//要取两串最小值
		for(int j=0;j<ne;++j)str[j]=s[j];
		for(int j=0;j<ne;j++)
		{
			str[j+ne]=ans[L-ne+j];
		}
		int len=KMP(str,ne*2);//这里要讲长度*2传上去
      len=min(len,ne);//记得去min
		for(int j=len;j<l;j++)//复制答案
		{
			ans[L]=s[j];++L;
		}
	}
	cout<<ans;
}
```


---

## 作者：mraymes (赞：0)

本文将同步到 [Hexo 博客](https://mraymes.github.io).

字符串匹配板子题. ~~Dilute: 最近 CF 的题目质量越来越低了...~~

大部分人都用的是双模哈希, 但由于种种原因, 有一部分 FST 了.  
这里提供一种 KMP 的做法, 虽然码量大了一点, 难想一点, ~~但不会被叉~~.

普通的 KMP 算法是完全匹配, 但这里只是找了同时作为一个字符串的后缀, 另一个字符串的前缀的最长字符串, 所以需要在原算法基础上修改一下.

有人说用拓展 KMP, 但是并没必要 ~~而且我不会~~.

值得注意的是, 两个字符串操作完了之后, 要和操作完后的字符串与下一个字符串匹配.  
test 4 卡了那些没完全理解题意的人的做法 ~~(我也是其中一个)~~

数据:  
```
3
abcde bcdef abcdefg
```

具体见代码.

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
char str[1000001];
int lps[1000001]; // 同时作为 str[0..i] 的前缀与后缀的字符串的最大长度
char ans[1000001]; // 答案
int len;
int pos; // 匹配到的位置
int l_ans; // ans 串的长度

template <typename T>
inline T read() {
    T x = 0;
    T multiplier = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            multiplier = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch & 15);
        ch = getchar();
    }
    return x * multiplier;
}

int main() {
    n = read<int>();

    for (int i = 1; i <= n; i++) {
        scanf("%s", str);
        len = strlen(str);

        if (i == 1) { // 第一个字符串作为初始 ans 串
            copy(str, str + len, ans);
            l_ans = len;
        } else {
            // 自行匹配, 与原 KMP 算法相同, 计算出 lps[] 数组
            int l = 0;
            for (int j = 1; j < len; j++) {
                while (l != 0 && str[j] != str[l]) {
                    l = lps[l - 1];
                }

                if (str[j] == str[l]) {
                    lps[j] = ++l;
                } else {
                    lps[j] = 0;
                }
            }

            pos = -1;
            l = 0;
            // 此处有改动.
            // 因为要求的是同时为 ans 的后缀与 str (当前字符串) 的前缀
            // 的字符串的长度, 所以如果匹配位置使得 str 被完全包围, 那么
            // 这种就是不合法的.
            // 比如:
            //        0123456          012
            // ans = "abcdefg", str = "cde"
            // 此时, 匹配到的 pos 为 2, 但因为 "cde" 并不是后缀, 所以舍
            // 去.
            // 为了解决, 就从 ans 串的第 l_ans - len 位置开始匹配.
            // 并因为这里是不完全匹配, 最后匹配到 l_ans + len - 1 的位置.
            // 相当于在 ans 串的后面添加 len 个通配符.
            for (int j = l_ans - len; j < l_ans + len; j++) {
                while (j < l_ans
                       && (l >= len || l != 0 && ans[j] != str[l])) {
                    // 失配
                    // 必须满足 j < l_ans, 因为一旦超过了原 ans 串的最右端,
                    // 就不再会出现失配情况.
                    l = lps[l - 1];
                }

                // 继续匹配
                if (j >= l_ans || ans[j] == str[l]) {
                    l++;
                }
                // 匹配完毕
                if (l == len && j >= l_ans - 1) {
                    // 第一次匹配完毕即可退出.
                    // 因为要满足两串重叠部分尽量长.
                    pos = j - l + 1;
                    break;
                }
            }

            // 匹配失败
            if (pos == -1) {
                pos = l_ans;
            }

            // 从 pos 处开始, 将新串添加到 ans 串.
            for (int j = pos, k = 0; k < len; j++, k++) {
                ans[j] = str[k];
            }
            // 更新长度
            l_ans = pos + len;
        }
    }

    cout << ans << '\n';

    return 0;
}
```

---

