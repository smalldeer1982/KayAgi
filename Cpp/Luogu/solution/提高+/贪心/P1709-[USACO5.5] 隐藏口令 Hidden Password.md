# [USACO5.5] 隐藏口令 Hidden Password

## 题目描述

有时候程序员有很奇怪的方法来隐藏他们的口令。Binny 会选择一个字符串 $S$（由 $N$ 个小写字母组成，$5 \le N \le 5 \times {10}^6$），然后他把 $S$ 顺时针绕成一个圈，每次取一个做开头字母并顺时针依次取字母而组成一个字符串。这样将得到一些字符串，他把它们排序后取出第一个字符串。把这个字符串的第一个字母在原字符串中的位置减 $1$ 做为口令。

如字符串 `alabala`，按操作的到 $7$ 个字符串，排序后得：

`aalabal`

`abalaal`  
`alaalab`  
`alabala`  
`balaala`  
`laalaba`  
`labalaa`

第一个字符串为 `aalabal`，这个 `a` 在原字符串位置为 $7$，$7-1=6$，则 $6$ 为口令。


## 说明/提示

题目满足：

$30 \%$ 的数据 $n \le {10}^4$。  
$70 \%$ 的数据 $n \le {10}^5$。  
$100 \%$ 的数据 $1 \le n \le 5 \times {10}^6$。

时限 1s

题目翻译来自NOCOW。

USACO Training Section 5.5

// 20170523 新增数据四组


## 样例 #1

### 输入

```
7
anabana
```

### 输出

```
6```

# 题解

## 作者：Lin1043 (赞：39)

我们以题目中的数据为例，有如下的一个字符串：



  ![](https://cdn.luogu.com.cn/upload/pic/6280.png) 

对于这个字符串，我们定义两个指针分别为 i 和  j 分别指向 ‘a’ 和 ’n’ 即 i = 0 j = 1 再定义一个累加器 k 则表示分别以 i 和 j 为首的字符串的第 k 个字符.



 ![](https://cdn.luogu.com.cn/upload/pic/6281.png) 

根据贪心思想,每一项显然要选最小的最好。在这里 ’n’ 的字典序大于 ’a’ 那么j显然不会是我们所要的答案那么我们就对j进行移位即 j++接下来我们便重复上面的操作



 ![](https://cdn.luogu.com.cn/upload/pic/6282.png) 

因为 i 和 j 所指的值是相同的，所以我们并不能通过比较这一位从而得出这两个字符串的顺序关系所以我们就要对 k 进行移位即 k++


  ![](https://cdn.luogu.com.cn/upload/pic/6283.png) 

我们对 i+k 和 j+k 所指的字符进行比较，显然可以得出 ’b’ 是比 ’n’ 要更优的那么这时候我们就要对i进行移位，因为在 [i ,i+k) 内我们都已经判断完了，那么我们就可以将 i 移到 i+k+1 继续接下来的判断。根据如上的操作我们就可以写出如下的伪代码:

```cpp
    i = 0 ; j = 1 ; k = 0;
    while(i < length && j < length){
        if s[i + k] == s[j + k] k++
        if s[i + k] >  s[j + k] i = i + k + 1;
        if s[i + k] <  s[j + k] j = j + k + 1;
        ……
    }
```
但是我们还要考虑以下几个问题

1.当i=j时，我们的操作便无法正常的运行，因为显然的在i=j时，i+k=j+k，这样的话我们的k就会不断的增加从而导致WA

2.  i+k 和 j+k是可能越界的

3.  k是可能大于length的

解决方法如下:

1.当i=j时，j++

2.只要将i+k和j+k Mod length即可

3.限制k < length ,在k = length 直接返回i和j中位置较前的即可


完整代码如下:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=5000110;
int n;
char s[maxn];
int Mini(int l)    
{    
    int i,j,k;  
    i=0;j=1;k=0;  
    while(i<l&&j<l)  
    {  
        k=0;  
        while(s[(i+k)%l]==s[(j+k)%l]&&k<l) k++;  
        if(k==l) return (i<j)?i:j;  
        if(s[(i+k)%l]>s[(j+k)%l])i=i+k+1;
        else j=j+k+1;
        if(i==j)j++;
    } 
    return (i<j)?i:j;
}     
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)cin>>s[i];
    int l=Mini(n);
    cout<<l<<endl;
    return 0;
}
```

---

## 作者：SIXIANG32 (赞：7)

蓝紫黑百题祭，发个题解纪念。  
~~害又暴露出我这个辣鸡水平了~~  
闲话少说，切入正题——  

---
这道题其实是个最小表示法的裸题。  
最小表示法是这个东西——  
> 如果你有一个字符串 $str$，我们不断的把这个字符串的末尾放到前面来，组成的所有字符串中字典序最小的就是这个字符串的最小表示法。  

emmm 这是不是和题目的描述一毛一样！   
最小表示法是个很奇妙的东西。  
首先我们也可以像题目这样把字符串看成一个字符环，学过区间 dp 的人都知道有个叫断环成链的技巧，我们也可以把这个字符环看成一个复制了一遍的双倍长度字符串，就好比 $\texttt{pika}$ 变成 $\texttt{pikapika}$。  
这个时候我们就会发现从任意一个点开始后面 $n$ 个字符排在一块就是一个重构。  

---
解决了表示的问题，我们还要想怎么找出来。  
先造两个指针 $qwq,qaq$，表示当前搞到了这两个点。  
然后我们要转移这两个点对不对。  
显然一个个找是很麻烦的，我们先找到一个 $k$ 使得 $str_{qwq + k} \ne str_{qaq + k},0 \le k < n$。  
这个有什么用呢，如果 $str_{qwq + k} > str_{qaq + k}$，那么显然无论如何 $str_{qwq}$ 是不可能作为最小表示法的第一个字符。  
为什么呢？因为前 $k - 1$ 个字符是一样的，你突然 $str_{qwq + k}$ 大于人家 $str_{qaq, k}$，那么显然字典序势必会比 $str_{qaq + k}$ 大的。  
所以呢我们要将 $qwq$ 变为 $qwq + k + 1$，如果 $qwq + k + 1 = qaq$，我们还要加一个 $1$（你都一样了还比什么比）。  
那如果 $str_{qaq + k} > str_{qwq + k}$ 同理。  

---
那么最后的结果（最小表示法的开头下标）就是 $\min(qwq, qaq)$ 啦。  
这个算法的时间复杂度多少呢？  
显然的，$qwq,qaq$ 在任意时刻肯定是不会超过 $n$ 的，且 $qwq,qaq$ 都是呈上升趋势，也就是说两个指针顶多就会移动 $2n$ 次，时间复杂度为 $O(n)$。   

---
回到这道题来。  
我们已经能求出来最小表示法的开头下标 $pos$ 了，那么根据题意 $pos - 1$ 就是答案。   
代码——  
```cpp
#include <iostream> 
#include <string> 
#define MAXN 5000000
#define QWQ cout << "QWQ" << endl;
using namespace std;
char a[MAXN * 2 + 10];
int main() {
	int n, qwq = 1, qaq = 2, k;
	cin >> n;
	for(int p = 1; p <= n; p++)
		cin >> a[p], a[p + n] = a[p];
	while(qwq <= n && qaq <= n) {
		for(k = 0; k < n && a[qwq + k] == a[qaq + k]; k++) ;//找到一个 k
		if(k == n) break;//全一样，也就是说扫描完了
		if(a[qwq + k] > a[qaq + k]) {//上面的情况判断
			qwq = qwq + k + 1;
			if(qwq == qaq) qwq++;
		}
		else {
			qaq = qaq + k + 1;
			if(qwq == qaq) qaq++; 
		}
	}
	int pos = min(qwq, qaq);//开头下标
	cout << pos - 1 << endl;
}
```


---

## 作者：yeaDonaby (赞：6)

把S顺时针绕成**一个圈**，每次取一个做**开头字母**并**顺时针**依次取字母而组成一个字符串。这样将得到一些字符串，他把它们排序后取出第一个字符串。把这个字符串的**第一个字母在原字符串中的位置**-1做为口令。



------------
### ~~显然~~是最小表示法中**开头字母**的位置。

如字符串*alabala*，按操作的到7个字符串，排序后得：

**aalabal**

abalaal

alaalab

alabala

balaala

laalaba

labalaa

第一个字符串为aalabal，这个a在原字符串位置为7，7-1=6，则6为口令。
![](https://cdn.luogu.com.cn/upload/pic/71431.png)
![](https://cdn.luogu.com.cn/upload/pic/71428.png)
很容易对这里的i,j 产生误会  误以为i为ans,j为比较指针

实际上这题中 i,j 都可能存有ans 两者互相更新，直到有一个更新后超过了len（包括len） 的时候 另一个即为正解

# 注意：
1.n<=5000000，则空间开10000000
2.
```
do
	{
		c=getchar();
	}
	while(c==' '||c=='\n');
```
window才下可用
可以写成：

（1）：
```
do
	{
		c=getchar();
	}
	while(c==' '||c=='\r'||c=='\n');
```
（2）：
```
do
	{
		c=getchar();
	}
	while(c<'a'||c>'z');
```

```
#include<stdio.h>
#include<string>
#define R register
#define I inline
#define maxn 10000001
using namespace std;
int n;
string s;
char c;
I int read(void)
{
	int X=0;
	bool F=0;
	char a=getchar();
	while(a<'0'||a>'9')
	{
		if(a=='-')
		{
			F=1;
		}
		a=getchar();
	}
	while(a>='0'&&a<='9')
	{
		X=(X<<1)+(X<<3)+int(a-'0');
		a=getchar();
	}
	return F?-X:X;
}//就一个数还用快读？？？
int main()
{
	n=read();
	for(R int i=1; i<=n; i++)
	{
		do
		{
			c=getchar();
		}
		while(c==' '||c=='\r'||c=='\n');
		s+=c;
	}
	s+=s;
	int x=0,y=1,k;
	while(x<n&&y<n)
	{
		k=0;
		while(k<n)
		{
			if(s[x+k]!=s[y+k])
			{
				break;
			}
			k++;
		}
		if(k==n)
		{
			break;
		}
		if(s[x+k]<s[y+k])
		{
			y+=k+1;
		}
		else if(s[x+k]>s[y+k])
		{
			x+=k+1;
		}
		if(x==y)
		{
			y++;
		}
	}
	printf("%d",x<y?x:y);
	return 0;
}
```

---

## 作者：姚文涛 (赞：4)

// 算法的意思就是说用一个V[I]表示第I位开始的长度为V[I]的字符串是所有长度为V[I]的字符串中最小的，然后就是不停得想办法增大V[I]。


// 增大的方法就是看如果V[I+V[I]]不为-1的话，那就说明这两段字符串都是所在长度中最小的，所以显然合起来还是最小的，所以就把V[I]赋为V[I]+V[V[I]+I]由于后面那段字符串包含在新的字符串里面了，所以后面那段就没有用了，把V[I+V[I]]赋为-1。


// 但是每次扫描的时候都要取最大的V[I+V[I]]然后才更新，所以每次必须先把序列扫描一遍，取出可以更新的放到新的序列里，每次做完一遍把新的序列赋给老的序列，循环着做，一直到序列里只剩一个元素为止。


// 注意一开始所有的V都是0这样是没办法更新的，所以一开始就是要找最小的那些字母然后把他们赋为1。


// 有几个技巧，首先是把字符串复制一下让两个原字符串连起来方便做绕回来的情况。另外就是有可能最后会超出字符串一位（检查最小字符的时候），可以把字符串加一位赋成一个ASC2码很大的字符，这样就不会201了，另外注意超出范围的时候STRING类型是不会报错的，ANSISTRING会。



//C++ //（其实还是觉

/\*

Problem: P1709


Knowledge: FindMinStringOfAString


Writer: AKBOY


PS: All of the code is writen by AKBOY,not by the others.


\*/

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=6666666,NEXTLINE=72;
int n;
char str[N*2];
void Read(int num,char *s)
{
    for(int i=1;i<=num;++i){
        s[i]=getchar();
        if(s[i]<'a'||s[i]>'z')--i;
        s[i+n]=s[i];
    }
}
int FindMinString(int len,char *s);
int main(void)
{
    scanf("%d",&n);
    Read(n,str);
    printf("%d\n",FindMinString(n,str)-1);
    return 0;
}
int FindMinString(int len,char *s)
{
    int flag1=1,flag2=2,lastlen=0;
    while(flag2<=len){
        lastlen=0;
        while(s[flag1+lastlen]==s[flag2+lastlen]&&lastlen<len)++lastlen;
        if(lastlen==len)return flag1;
        if(s[flag1+lastlen]<s[flag2+lastlen])
            flag2=flag2+lastlen+1;
        else{
            int t=flag2;
            flag2=max(flag1+lastlen,t)+1;
            flag1=t;
        }
    }
    return flag1;
}
```

---

## 作者：qwqwq (赞：3)

!qw是最胖的！

5M的数据，26进制哈希用来比较大小long long显然是存不下。但是我们可以比较HASH值闲的出最长公共前缀。
对于最优与当前位置，二分比较段落哈希值大小，然后比较最大匹配位置的后一位字典序。
时间复杂度为O（n~~nlogn）玄学。
!大力HASH!哄！

```cpp
/*
ID: QW请你出来一下
LANG: C++
PROG: hidden
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <vector>
#include <string.h>
#include <cmath>
#include <stack>
#include <map>
#define siji(i,x,y) for(int i=(x);i<=(y);++i)
#define gongzi(j,x,y) for(int j=(x);j>=(y);--j)
#define xiaosiji(i,x,y) for(int i=(x);i<(y);++i)
#define sigongzi(j,x,y) for(int j=(x);j>(y);--j)
#define inf 0x5f5f5f5f
#define ivorysi
#define mo 97797977
#define hash 974711
#define base 47
#define pss pair<string,string>
#define MAXN 5000
#define fi first
#define se second
#define pii pair<int,int>
#define esp 1e-8
typedef long long ll;
using namespace std;
char str[1000005],t[1000005];
int l,e[1000005],ha[1000005],x,cnt,c;
bool check(int a,int b,int len) {
    return ((ll)e[2*l-a-len]*(ha[a+len-1]-ha[a-1])%mo - (ll)e[2*l-b-len]*(ha[b+len-1]-ha[b-1])%mo)%mo==0;
}
int binary(int a,int b) {
    int le=0,ri=l,mid;
    while(le<ri) {
        mid=(le+ri+1)>>1;//因为最后返回的是le
        if(check(a,b,mid)) le=mid;
        else ri=mid-1;
    }
    return le;
}
bool cmp(const int &a,const int &b) {
    x=binary(a,b);
    return x==l ? a<b : str[a+x]<str[b+x];
} 
void solve() {
    scanf("%d",&l);
    siji(i,1,(l-1)/72+1) {
        scanf("%s",str+1+(i-1)*72);
    }
    strcpy(t+1,str+1);
    strcat(str+1,t+1);
    e[0]=1;
    siji(i,1,2*l) {
        e[i]=(ll)e[i-1]*base%mo;
    }
    siji(i,1,2*l) {
        ha[i]=(ll)(ha[i-1]+(ll)e[i]*(str[i]-'a'+1)%mo)%mo;
    }
    c=1;
    siji(i,2,l) {
        if(cmp(i,c)) c=i;
    }
    printf("%d\n",c-1);
}
int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
```

---

## 作者：「QQ红包」 (赞：2)

题解 by:redbag

然后还是用暴力搞的

扫描一遍，把最小的字母记录下来，然后倒着搜，最小字母连续的出现次数，

如果出现次数一样，再往后搜，比较


```cpp
/*
ID: ylx14271
PROG: hidden
LANG: C++
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;
char c[10000100];
int f[10000100];
int n,i,j;
char ch1,mi;
int d,max1;
int main()
{
    freopen("hidden.in","r",stdin);
    freopen("hidden.out","w",stdout);
    scanf("%d",&n);
    mi='z';
    i=-1;
    while (scanf("%c",&ch1)==1)
    {
        if ('a'<=ch1&&ch1<='z') 
        {
            c[++i]=ch1;//这样读入只是为了吃掉换行符和行末空格 
            mi=min(c[i],mi);//找到最小的那个字符 
        }
    }
    for (i=n;i<n*2-1;i++)//把环拉直 
    {
        c[i]=c[i-n];
    }
    for (i=n*2-2;i>=0;i--)//找 最小的那个字符 最多的 连续出现次数 
    {
        if (c[i]==mi) f[i]=f[i+1]+1;
        else f[i]=0;
        max1=max(max1,f[i]);
    }
    d=-1;
    for (i=0;i<n;i++)
    {
        if (f[i]==max1) //对相同的情况进行处理  
        {
            if (d==-1) d=i; else
            {
                j=f[i];
                while (c[i+j]==c[d+j]) //一个一个的比较 
                {
                    j++;
                    if (i+j>=n*2-2||d+j>=n*2-2) break;//防炸（超长度了 
                } 
                if (c[i+j]<c[d+j]) d=i;
            }
        }
    }
    printf("%d\n",d);
    return 0;
}

```

---

## 作者：loi_wzhd (赞：1)

ps ： 发现没有人用链表优化过。


我们先来看一下这道题，我们的任务是从从一堆字符串中选出一个序列，使其字典序最小，很明显我们要找以最小的字母打头的序列，如果有多个我们再继续比对下一位。直到只剩下一个最小的字母，这就是我们的思路。


但是当我们遇到

aaaaaaaaaaaaaaaaaaaaaaaaaaab……

or
abcabcabcabcabcabcabcabcabc……


像这样的字符串就会卡成O（n^2）。


我们来观察一下这两个式子，发现他们的链表会有重叠部分。由于链表头总是最小的，所以当某链表的头被包含在前一个链表的尾部时，这个答案一定不如前一个链表优。所以这个链表我们会删去。值得一提的是，这个被删去的链表的下一位我们最好也访问一下，因为如果这个链表后面又是一个链表头，我们可以追加删去一条链表。


那我们来估一下时间复杂度，我们发现每条链表都没有重叠部分，那时间复杂度就是的链表平均长度 \* 链表的条数，由于链表平均长度 \* 链表条数 = 链表总长度。所以几乎是O（n）的。


实际上，很多人不是很会用链表，比如说我。我们可以观察到，我们使用的所有的链表实际上都只与链表尾部与链表头有关，那么我们只用一个只记录头与尾结构体队列就可以了，而对于删去一条链表，我们只需要阻止它重新入队就可以了。


附加代码:


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct zt
{
    int f,v;
}dian[5000005];
queue<zt>q,p;
int n,ans,cnt,vis[5000005];
char num[5000005],b,c;
int main()
{
    freopen("aaa.in","r",stdin);
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        cin>>num[i];
        if(num[i] < b||!b) b = num[i];
    }
    for(int i = 0;i < n;i ++)
        if(num[i] == b) q.push((zt){i,i});
    while(q.size() > 1)
    {
        c = '0';cnt ++;
        while(!q.empty())
        {
            zt u = q.front();q.pop();
            if(u.v + 1 >= n) u.v -= n;
            if(c != '0'&&num[u.v + 1] > c) continue;
            vis[u.v + 1] = 1;
            if(vis[u.f]) continue;
            if(c == '0') c = num[u.v + 1];
            else if(c > num[u.v + 1]) {while(!p.empty()) p.pop();c = num[u.v + 1];}
            p.push((zt){u.f,u.v + 1});
        }
        while(!p.empty())
        {
            zt u = p.front();p.pop();q.push((zt){u.f,u.v});
        }
    }
    zt u = q.front();
    ans = u.v;
    ans = (n + ans - cnt) % n;
    printf("%d",ans);
    return 0;
}
```

---

## 作者：MilkyCoffee (赞：0)

这是一道最小表示法的裸题。

最小表示法的定义详见 [OI-wiki相关页面](https://oi-wiki.org/string/minimal-string/)

下面所有的 $s$ 表示输入的字符串。

对于最小表示法，我们只需要将原字符串乘 $2$（例如 $\texttt{milky}$ 变成了 $\texttt{milkymilky}$）并使用指针查询即可。

对于最小表示法的题目，我们需要寻找一个 $k$ ，使得 $s_{l+k} ≠ s_{r+k}$ 且其前面的 $k$ 个字符串都相等，然后用两个指针求出最小表示法的开头，并且根据题意，最小表示法的开头 $-1$ 即是我们要求的值。

AC 代码：

```cpp
// jaco2567 AK IOI
// #include <bits/stdc++.h>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

inline int read() {
    int res = 0, F = 1;
    char k;
    while (!isdigit(k = getchar())) if (k == '-') F = -1;
    while (isdigit(k)) {
	  	res = res * 10 + k - '0';
        k = getchar();
    }
    return res * F;
}

const int NR = 5e6 + 5;

int n, l = 1, r = 2;
// string s; <- 有问题
char s[NR*2];

int main() {
	n = read();
	// cin >> s;

	for (int i = 1; i <= n; i++) {
		cin >> s[i];
		s[i+n] = s[i];
	}

	int k = 0;
	while (l <= n && r <= n) {
		k = 0; // 注意每次都要清零
		while (k < n && s[l+k] == s[r+k]) k++;
		// 寻找 k

		if (k == n) break; // 都相等

		if (s[l+k] > s[r+k]) {
			l += (k + 1);
			if (l == r) l++;
		} else {
			r += (k + 1);
			if (l == r) r++; 
		}
	}

	cout << min(l, r) - 1 << endl;
	return 0;
}
```

---

## 作者：joyoi (赞：0)

### 这道题我们可以如下来设计：

对于这个字符串，我们定义两个指针分别为 i 和 j 分别指向 a 和 n 即 i = 0, j = 1 再定义一个累加器 k 则表示分别以 i 和 j 为首的字符串的第 k 个字符, 根据贪心思想,每一项显然要选最小的最好。在这里 n 的字典序大于 a, 那么 j 显然不会是我们所要的答案那么我们就对 j 进行移位即 j++ 接下来我们便重复上面的操作

因为 i 和 j 所指的值是相同的，所以我们并不能通过比较这一位从而得出这两个字符串的顺序关系所以我们就要对 k 进行移位即 k++。我们对 i + k 和 j+k 所指的字符进行比较，显然可以得出 b 是比 n 要更优的那么这时候我们就要对 i 进行移位，因为在 (i, i + k) 内我们都已经判断完了，那么我们就可以将 i 移到 i + k + 1 继续接下来的判断。

但是我们还要考虑以下几个问题:

- 当i = j时，我们的操作便无法正常的运行，因为显然的在 i=j 时，i+k = j+k，这样的话我们的k就会不断的增加从而导致 WA
- i + k 和 j + k 是可能越界的
- k 是可能大于 length 的

解决方法如下:

- 当 i = j 时，j++
- 只要将 i + k 和 j + k  Mod length 即可
- 限制 k < length, 在 k = length 直接返回 i 和 j 中位置较前的即可


代码如下:
```cpp
#include <bits/stdc++.h>
#define N 5000002

using namespace std;
int n, i, j = 1, k;
char c[N];

int main()
{
    cin >> n;
    for(i = 0; i < n; i++) cin >> c[i];
    i = 0;
    while(i < n && j < n)
    {
        k = 0;
        while(c[(i + k) % n] == c[(j + k) % n] && k < n) k++;
        if(k==n) break;
        if(c[(i + k) % n] > c[(j + k) % n]) i = i + k + 1;
        else j = j + k + 1;
        if(i == j) j++;
    }
    cout << min(i, j) << endl;
    return 0;
}

```





---

## 作者：Allan (赞：0)

最小表示法
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
struct mm
{
   char data;
   int num;
}s[50000005];
int main()
{
   scanf("%d",&n);
   for(int i=0;i<n;i++)
   {
      cin>>s[i].data;
      s[i].num=i+1;
      s[n+i].data=s[i].data;
      s[n+i].num=s[i].num;
   }
   int i=0,j=1,k;//使用两个指针
   while(i<n&&j<n)
   {
      for(k=0;k<n && s[i+k].data==s[j+k].data;k++);
      if(k==n)break;//s只有一个字符构成
      if(s[i+k].data>s[j+k].data)//i+k，j+k意思是逐位表示
      {
         i=i+k+1;跨一个区间
         if(i==j)i++;
      }
      else
      {
         j=j+k+1;
         if(i==j)j++;
      }
   }   
   //cout<<k;
   //cout<<s[p].data;
   //cout<<min(i,j);//此时是最小表示
   cout<<s[min(i,j)].num-1;
   return 0;
}
```

---

## 作者：zhangjianweivv (赞：0)

这道题的话……是我低估它了。它是真蓝题，A的也挺艰难的。所以就在这里写一篇题解吧（因为最近结束停课了，所以做题的速度就慢了下来，题解也就不是很经常写了）

----

好，先讲讲思路吧。一开始看到这道题，是想着用暴力的。但是暴力最多只能做到只TLE一个点，没有办法A。后来听猴子dalao说了一种神奇的思路（好像叫……什么匹配还是什么的）

就是说，逐位逐位的去比较，然后如果发现了不一样的，就看大小。如果ch[a]>ch[b]，那i就跳到i+k+1，反之，如果ch[b]>ch[a]，那j就跳到j+k+1。

然而还是a不了。看了下面dalao的题解，发现有i==j的情况，用j++来优化一下。

然后具体就见代码了。还有一点就是之前一直T嘛，然后就加了很多很多优化。

```cpp
/*
ID:zhangji78
LANG:C++
TASK:hidden
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char ch[100010];int n;
//这里有点坑，洛谷要开到5000010,但是usaco只用开到100010就行了
inline void read()
{
	int len=0;
    //这个是专门打的输入，因为可能会有换行（见下面的数据）
	while(len<n)
	{
		char c=getchar();
		if(c<'a'||c>'z')continue;
		ch[++len]=c;
	}
}
inline int readln()
{//为了省时间顺手打的一个假快读，然而并没有省多少时间
	char c=getchar();
	int x=0;
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x;
}
int main()
{
//	freopen("hidden.in","r",stdin);
//	freopen("hidden.out","w",stdout);
	n=readln();read();
	int i=1,j=2,k=0;
    //因为我是习惯从1开始的，然而这也造成了一点小麻烦（见下面）
	while(i<=n&&j<=n)
	{
		int a=i,b=j;k=0;
		while(ch[a]==ch[b]&&k<n)
		{//这就是那个小麻烦了——%n有可能为零，要特判
			k++;a=k+i;b=k+j;
			a%=n;a=(a==0)?n:a;//小特判，望理解
			b%=n;b=(b==0)?n:b;
		}
		if(k==n){printf("%d\n",min(i-1,j-1));return 0;}
        //由于“第一个字符串为aalabal，这个a在原字符串位置为7，7-1=6，则6为口令。”（这是题目原话）
        //所以min里面放的是i-1和j-1
		if(ch[a]>ch[b])i=i+k+1;
		else j=j+k+1;//emmm......这就是主要思路了
		if(i==j)j++;//这就是下面dalao的判断，学起来学起来
	}
	printf("%d\n",min(i-1,j-1));
	return 0;
}
/*
emmm......这个是一个数据……为了图方便neng在这里的
200
bcbaadccdcddeadecbaadcdeabecaccbaedcedbcaecbeccdeceebeddbabbcdeeedddbbcd
cebbcdcbcbceabcbbaeaebcdeccceecbbdaadcbaaababbeebaccbebabaecbbeebbeedcca
daaebbedcbadcdbadcdceebcabeaddabdcdabeddaadeebeeeebadaca
*/
```

---

## 作者：Celebrate (赞：0)

这一道题就用最小表示发来做

首先第定义两个指针l,r表示字符串的两个开头，不断的比较两个开

头，l或r大于n就退出即可，时间一般在O(n)左右，非常的快

其中有一个k，表示当前分别为宜l开头和以r开头的第k个字符，用

a[l+k]和a[r+k]比较就可以了

不过有几点需要注意：

（1）k<n，l+k和r+k可能大于n，所以我们可以把这些数复制一份

（2）l != r，等于了就会出问题

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[11000000];
int n;
int main()
{
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++)
    {
    	a[i]=getchar();
    	if(i%72==0) getchar(),getchar();//去掉空格 
    	a[i+n]=a[i];//复制一份数放在后面 
    }
    int l=1,r=2,k;//两个指针 
    while(l<=n && r<=n)
    {
    	for(k=0;k<n && a[l+k]==a[r+k];k++);//不管相等的地方 
    	if(k==n) break;
    	if(a[l+k]<a[r+k])//如果以l开头更优 
        {
            r=r+k+1;//r继续往后找，记得加k，“+1”应该也可以，只是慢了很多 
            if(l==r)r++;//不能相等 
        }
    	else if(a[l+k]>a[r+k])
        {
            l=l+k+1;
            if(l==r)l++;
        }
    }
    printf("%d\n",min(l,r)-1);//肯定用那个没有超过n的
    return 0;
}
```

如果为了加快，可以把开头改为这样

```cpp
r=1;while(scanf("%s",a+r)!=EOF)r+=72;
```
还有把l+k和r+k改为(l+k)%n和(r+k)%n

可以快许多

---

