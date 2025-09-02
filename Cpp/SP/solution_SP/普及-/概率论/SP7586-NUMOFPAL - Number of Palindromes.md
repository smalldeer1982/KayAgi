# NUMOFPAL - Number of Palindromes

## 题目描述

Each palindrome can be always created from the other palindromes, if a single character is also a palindrome. For example, the string "malayalam" can be created by some ways:

  
\* malayalam = m + ala + y + ala + m  
\* malayalam = m + a + l + aya + l + a + m  
  
We want to take the value of function NumPal(s) which is the number of different palindromes that can be created using the string S by the above method. If the same palindrome occurs more than once then all of them should be counted separately.

## 说明/提示

**Limitations**

0 < |s| <= 1000

## 样例 #1

### 输入

```
malayalam```

### 输出

```
15```

# 题解

## 作者：codesonic (赞：4)

也不用写太麻烦的回文自动机

用马拉车求出以每个字母为对称轴的回文串长度，因为一个回文串长度/2就是这个回文串包含的子回文串长度，所以最后统计一下即可~
```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define maxn 51000100
using namespace std;
int n,hw[maxn],ans;
char a[maxn],s[maxn<<1];
void manacher()
{
    int maxright=0,mid;
    for(int i=1;i<n;i++)
    {
        if(i<maxright)
            hw[i]=min(hw[(mid<<1)-i],hw[mid]+mid-i);
        else
            hw[i]=1;
        while(s[i+hw[i]]==s[i-hw[i]])
        	++hw[i];
        if(hw[i]+i>maxright)
        {
            maxright=hw[i]+i;
            mid=i;
        }
    }
}
void change()
{
    s[0]=s[1]='#';
    for(int i=0;i<n;i++)
    {
        s[i*2+2]=a[i];
        s[i*2+3]='#';
    }
    n=n*2+2;
    s[n]=0;
}
int main()
{
    scanf("%s",a);
    n=strlen(a);
    change();
    manacher();
    ans=1;
    for(int i=0;i<n;i++)
        ans+=hw[i]/2;
    printf("%d",ans-1);
    return 0; 
}
```

---

## 作者：critnos (赞：3)

一个简单的哈希做法

我们设 $h(x)$ 为字符串 $x$ 的哈希值。

容易得知，若 $x$ 是回文串，那么 $h(x)=h(\text{reverse}(x))$。对于 $x$ 是非回文串的情况，基本是不可能成立的。

那么正反两次维护整个序列的哈希值然后比较就行了。

```cpp
for(i=1;i<=len;i++)
	for(j=i;j<=len;j++)
		a[i][j]=a[i][j-1]*114514+x[j];
for(i=len;i>=1;i--)
	for(j=i;j>=1;j--)
		b[i][j]=b[i][j+1]*114514+x[j];
for(i=1;i<=len;i++)
	for(j=i;j<=len;j++)
		s+=a[i][j]==b[j][i];
```
（其实并不需要 $b$ 数组，直接在线就行了，我这样写是为了更漂亮一些）

---

## 作者：__Unknown (赞：2)

## 暴力题解！
	emmmm……，其实仔细看看数据，只需要暴力过一遍字符串就可以了。第一次循环字符串，将每个字符作为对称轴来找最宽的回文串，这个字符串长度是一个奇数。那么包含这个对称轴字符的子回文串就是它的长度/2（呃，下取整），然后再过一遍字符串，，寻找长度为偶数的，最宽的字符串（其实像传统做法，在字符串中插入其他字符的做法也可以啦~），子回文串也是长度/2，然后再累加一下就出来了！话不多说，放码过来
   ## ~~实践出真知，暴力出奇迹~~#
   ```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
string s1;
long long sum,len[1005],l,r;//左、右边界
int len1;
int main()
{
	cin>>s1;
	len1=s1.length();
	for(int i=0;s1[i]!='\0';i++){
		l=i;
		r=i;
		while(1){
			if(l<0||r>=len1||s1[l]!=s1[r])
			break;
			else{
				l--;
				r++;
				len[i]++;//累计个数
			} 
		}
		l=i;
		r=i+1;//注意，这里是寻找长度为偶数的字符串，r是i+1.
		while(1){
			if(l<0||r>=len1||s1[l]!=s1[r])
			break;
			else{
				l--;
				r++;
				len[i]++;//累计个数
			}
		}
	}
	for(int i=0;i<s1.length();i++)
	sum+=len[i];//求和
	cout<<sum<<endl;
	return 0;
 } 
```
	

---

## 作者：cyrxdzj (赞：1)

### 一、思路

我们把回文字符串分成两种：长度为奇数的回文，和长度为偶数的回文。

对于长度为奇数的字符串，我们可以枚举输入字符串中的每一个字符，定义 `left` 和 `right` 为左右指针，初始值均为当前位置。

然后，循环进行比较。

- 如果两个指针指向的字符相同：
  
  计数器加 $1$，并将 `left` 往左移动，`right` 往右移动。
  
- 如果不相同或越界：
  
  退出循环。

对于长度为偶数的字符串，逻辑基本一致，只是 `right` 的初始值不能是当前位置，而是当前位置的右边一个字符。

由此，我们就可以得出完整代码。

### 二、完整代码

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
char input[1005];
int ans;
int main()
{
	scanf("%s",&input);
	int len=strlen(input);//字符串长度。
	for(int i=0;i<len;i++)//对于长度为奇数的回文字符串。
	{
		int now_left=i,now_right=i;//两个关键指针。
		while(now_left>=0&&now_right<len)//越界检测。
		{
			if(input[now_left]==input[now_right])//左右指针一致。
			{
				ans++;
			}
			else
			{
				break;
			}
			now_left--;//移动指针。
			now_right++;
		}
	}
	for(int i=0;i<len-1;i++)//对于长度为偶数的回文字符串。
	{
		int now_left=i,now_right=i+1;
		while(now_left>=0&&now_right<len)
		{
			if(input[now_left]==input[now_right])
			{
				ans++;
			}
			else
			{
				break;
			}
			now_left--;
			now_right++;
		}
	}
	printf("%d\n",ans);//输出。
	return 0;//完结撒花！
}

```

### 三、后记

记录：<https://www.luogu.com.cn/record/51908392>。

By [dengzijun](https://www.luogu.com.cn/record/51908392)

---

## 作者：Mono_pigsicklie (赞：1)

#### 可以用hash求最长回文子串/回文子串数，这样子就不需要写马拉车了。
```cpp
#include"bits/stdc++.h"
using namespace std;
typedef unsigned long long ull;

#define N 10111

#define base 13131

char s[N];
ull h1[N];
ull h2[N];
ull p[N],ans=0;

int n;

ull gh1(int l,int r) {
	return h1[r]-h1[l-1]*p[r-l+1];
}

ull gh2(int l,int r) {
	return h2[l]-h2[r+1]*p[r-l+1];
}

ull query1(int x) {
	int l=1,r=min(x,n-x);
	while(l<=r) {
		int mid=(l+r)>> 1;
		if(gh1(x-mid,x+mid)==gh2(x-mid,x+mid))
			l=mid+1;
		else r=mid-1;
	}
	return r;
}

ull query2(int x) { //偶
	int l = 1, r = min(x, n - x);
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(gh1(x - mid + 1, x + mid) == gh2(x - mid + 1, x + mid))
			l = mid + 1;
		else r = mid - 1;
	}
	return r;
}

int main() {
	scanf("%s",s+1);
	p[0]=1;
	n=strlen(s+1);
	for(int i=1; i<=n; i++) {
		h1[i]=h1[i-1]*base+s[i];
		p[i]=p[i-1]*base;
	}
	for(int i=n; i; i--)h2[i]=h2[i+1]*base+s[i];
	for(int i=1; i<=n; i++) {
		ans+=query1(i)+query2(i);
	}
	printf("%llu\n",ans+n);
	return 0;
}
```


---

## 作者：drophell (赞：1)

回文自动机板子题

每次在LAST上CNT++，

最后从父亲累加儿子的CNT，因为如果fa[v]=u，则u一定是v的子回文串;
统计答案

```
#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll unsigned long long
#define mem(a,b) memset(a,b,sizeof(a))
#define mec(a,b) memcpy(a,b,sizeof(b))
using namespace std;
const int  MAXN=1000+50;
char str[MAXN];
int len;
ll ans;
int hd[MAXN],ect;
struct Edge{int nx,to,w;}ar[MAXN];
void adds(int u,int v,int w){ar[++ect].to=v,ar[ect].w=w,ar[ect].nx=hd[u],hd[u]=ect;}
struct 	PAM
{
    int tot,last,n;
    int fa[MAXN],ln[MAXN],s[MAXN],cnt[MAXN];
    void init()
    {
    	fa[0]=fa[1]=1;
    	ln[tot=1]=-1;ln[last=n=ect=0]=0;
    	s[0]=-1;
    }
    int ge(int u,int w)
    {for(int e=hd[u],v=ar[e].to;e;v=ar[e=ar[e].nx].to)if(ar[e].w==w)return v;return 0;}
    int gf(int k){while(s[n-ln[k]-1]^s[n])k=fa[k];return k;}
    inline void extend(int x,int c)
    {
        s[++n]=c;last=gf(last);
        if(!ge(last,c))
        {
        	fa[++tot]=ge(gf(fa[last]),c);
        	ln[tot]=ln[last]+2;
        	adds(last,tot,c);
        	
        }
        cnt[last=ge(last,c)]++;
    }
	void calc()
	{
		for(int i=tot;i>=2;i--)
		{
			cnt[fa[i]]+=cnt[i];
			ans+=cnt[i];
		}
	}
}pam;
int main()
{
	
	pam.init();
	scanf("%s",str+1);len=strlen(str+1);
	//for(int i=1;i<=len;i++)printf("%c",str[i]);
	for(int i=1,x;i<=len;i++)pam.extend(i,str[i]-'a');
	pam.calc();
	printf("%lld ",ans);
    return 0;
 	       
}
```

---

## 作者：Jsxts_ (赞：0)

这道题是一个几乎模板的字符串哈希题，~~虽然我也调了很久~~。

首先，如果枚举子串头和尾再一位一位对应的话，$O(n^3)$ 的复杂度肯定会超时，于是我们就要想方法$O(1)$判断一个子串是否是回文串，就要用到字符串哈希。

字符串哈希，其实就是将一个字符串转换为整数存储，多用于判断字符串是否出现过，相关问题请左转[传送门](https://blog.csdn.net/diandie7589/article/details/101255163?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522159823353619725219948367%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=159823353619725219948367&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v3~rank_business_v1-3-101255163.ecpm_v3_rank_business_v1&utm_term=%E5%AD%97%E7%AC%A6%E4%B8%B2%E5%93%88%E5%B8%8C&spm=1018.2118.3001.4187)。

字符串哈希模板：

```cpp
#define ull unsigned long long //ull溢出之后自动取模，不用模数
const int base = 131;//哈希的基数
ull get(int l,int r) {
	return h[r] - h[l-1] + p[r-l+1];//区间哈希值
}
void Hash() {
	p[0] = 1;
	for (int i = 1;i <= n;i ++ ) {
		h[i] = h[i-1] * base + s[i] - 'a' + 1;//i后缀的哈希值
		p[i] = p[i-1] * base;
	}
}
```


因为相同字符串的哈希值肯定是一样的，所以我们就很容易想到一个做法，就是判断字符串$s$与$s$的倒序字符串的哈希值**是否相同**，如果相同就肯定是回文串。

倒序哈希值和正序差不多，只是反过来计算哈希而已。

倒序哈希：

```cpp
#define ull unsigned long long
const int base = 131;
ull get2(int l,int r) {
	return h2[l] - h2[r+1] * p[r - l + 1];
}
void Hash2() {
	for (int i = 1;i <= l;i ++ ) {
		hr[l-i+1] = hr[l-i+2]*base + s[l-i+1]-'a'+1; 
		p[i] = p[i-1] * base;
	}
}
```
之后只用判断正序与倒序的哈希值是否相同，如相同就是回文，否则不是。最后的时间复杂度：$O(n^2)$。

上代码：

```cpp
#include <iostream>
#include <cstring>
#define ull unsigned long long
using namespace std;
const int base = 131;//base一般选131，重复的可能性小 
ull hl[1010],p[1010],hr[1010];//ull自动取模 
char s[1010];
ull get1(int l,int r) {//求正序区间哈希值 
	return hl[r] - hl[l-1] * p[r-l+1];
}
ull get2(int l,int r) {//求倒序区间哈希值 
	return hr[l] - hr[r+1] * p[r - l + 1];
}
int main() {
	scanf("%s",s+1);
	p[0] = 1;
	int l = strlen(s+1);
	for (int i = 1;i <= l;i ++ ) {
		hl[i] = hl[i-1] * base + s[i] - 'a' + 1;//计算字符串哈希数组 
		hr[l-i+1] = hr[l-i+2] * base + s[l-i+1]-'a'+1;
		p[i] = p[i-1] * base;
	}
	int ans = 0;
	for (int i = 1;i <= l;i ++ )//长度1000，可以暴力枚举子串头和尾 
		for (int j = i;j <= l;j ++ )
			if (get1(i,j) == get2(i,j)) 
				ans ++;//判断正序哈希值与倒序哈希值是否相同，相同就是回文串 
	cout << ans;
	return 0;
}
```

蒟蒻第一篇题解，大佬轻喷~


---

## 作者：KSToki (赞：0)

提意已经很简单了，求一个串中包含几个回文串。

这是我学完manacher算法后做的例题，看到串中的回文串，很自然就想到用manacher去做。manacher算法的核心是数组$p$，$p_i$代表以$i$为中心的回文半径，由于我们插入了$'#'$字符，相当于我们把真实的回文半径扩大了两倍。

至此思路就很明确了，$p_i$实际上也代表了以$i$为中心的回文串的个数（显然），真实回文串个数即为$p_i/2$，每跑一次$ans+=p_i/2$即可.

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[22000005];//不要问我为什么数组开这么大，因为我是从模板过来的
int len,p[22000005],ans,mx,mid;
int main()
{
	ans=mx=mid=0;
	memset(p,0,sizeof(p));
	scanf("%s",s+1);
	len=strlen(s+1);
        ////
	for(register int i=len;i;--i)
	{
		s[i<<1]=s[i];
		s[(i<<1)|1]='#';
	}
	s[0]=s[1]='#';
	len<<=1;
        //插入#字符
        ////
	for(register int i=1;i<=len;++i)
	{
		if(i<=mx)
		    p[i]=min(p[(mid<<1)-i],mx-i+1);
		while(s[i-p[i]]==s[i+p[i]])
		    ++p[i];
		if(i+p[i]>mx)
		{
			mx=i+p[i]-1;
			mid=i;
		}
		ans+=(p[i]>>1);//唯一不同的地方
	}
        //manacher模板即可
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：chihik (赞：0)


不懂回文自动机的可以看[这篇博客](https://www.luogu.com.cn/blog/chihik/hui-wen-zi-dong-ji)。

用[P5496 【模板】回文自动机（PAM）](https://www.luogu.com.cn/problem/P5496) 的方法（[这篇题解](https://www.luogu.com.cn/blog/chihik/solution-p5496)）求出以每个位置结束的回文串个数，答案为所有位置的和。


```cpp
#include <cstdio>
#include <cstring>

const int MAXN = 500000 , MAXK = 26;
char str[ MAXN + 5 ];
struct Palindrome_Automaton{
	int Size , Last , Root0 , Root1 , Trans[ MAXN + 5 ][ MAXK + 5 ] , Link[ MAXN + 5 ];
	int Len[ MAXN + 5 ] , Cnt[ MAXN + 5 ];
	
	Palindrome_Automaton( ) {
		Root0 = Size ++ , Root1 = Size ++; Last = Root1;
		Len[ Root0 ] = 0  , Link[ Root0 ] = Root1;
		Len[ Root1 ] = -1 , Link[ Root1 ] = Root1; 
	}
	void Extend( int ch , int dex ) {
		int u = Last;
		for( ; str[ dex - Len[ u ] - 1 ] != str[ dex ] ; u = Link[ u ] );
		if( !Trans[ u ][ ch ] ) {
			int Newnode = ++ Size , v = Link[ u ];
			Len[ Newnode ] = Len[ u ] + 2;
			
			for( ; str[ dex - Len[ v ] - 1 ] != str[ dex ] ; v = Link[ v ] );
			Link[ Newnode ] = Trans[ v ][ ch ] , Trans[ u ][ ch ] = Newnode;
			Cnt[ Newnode ] = Cnt[ Link[ Newnode ] ] + 1;
		}
		Last = Trans[ u ][ ch ];
	}
	
	void Build( char *str ) {
		int len = strlen( str );
		for( int i = 0 ; i < len ; i ++ )
			Extend( str[ i ] - 'a' + 1 , i );
	}
    int Calc( ) {
        int Ans = 0;
        for( int i = 1 ; i <= Size ; i ++ )
            Ans += Cnt[ i ];
        return Ans;
    }
}PAM;

int main( ) {
	scanf("%s", str );
	PAM.Build( str );
    printf("%d", PAM.Calc( ) );
	return 0;
}
```


---

## 作者：xiayucc (赞：0)

### 从读题到过题只用了一分钟，不说了，要是ICPC也能这么简单就好了

~~回文自动机机裸体~~

在这里分享一下我的模板，每个数组的含义全部已经写在注释中了，剩下的就是自己尝试和摸索了，实在不行去CSDN上看看大佬们的讲解

```c
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 10;
char s[N];
int record[N]; //record记录了节点回文串的结束位置
struct Palindrome_tree{
	int nxt[N][26];
	int fail[N]; // 当前节点最长回文后缀的节点
	int len[N]; // 当前节点表示的回文串的长度
	int cnt[N]; // 当前节点回文串的个数， 在getcnt后可得到全部
	int sed[N]; // 以当前节点为后缀的回文串的个数（并不是表示第i结尾的回文串的种类数，如果要求每个点结尾的数的回文串个数，得用last）
	int tot; // 节点个数
	int last; // 上一个节点
	void init()
	{
		tot = 0;
		memset(fail, 0, sizeof fail);
		memset(cnt, 0, sizeof cnt);
		memset(sed, 0, sizeof sed);
		memset(len, 0, sizeof len);
		memset(nxt, 0, sizeof nxt);
	}
	void build()
	{
		len[0] = 0, len[1] = -1; // 0为偶数长度根， 1为奇数长度根
		tot = 1, last = 0;
		fail[0] = 1;
	}
	int getfail(char *s, int x, int n)
	{
		while (s[n - len[x] - 1] != s[n]||n-len[x]-1<0) // 比较x节点回文串新建两端是否相等
		//n-len[x]-1<0这个是我自己加的，多组的时候光第一个条件是不够的，所以有错请手动删除
			x = fail[x]; // 若不同， 再比较x后缀回文串两端
		return x;
	}
	void insert(char* s, int n)
	{
		for (int i = 0; i < n; i++)
		{
			int c = s[i] - 'a';//全小写要用a 全大写要用A 不然会错
			int p = getfail(s, last, i);// 得到第i个字符可以加到哪个节点的两端形成回文串
			if (!nxt[p][c])
			{
				tot++;
				len[tot] = len[p] + 2;  // 在p节点两端添加两个字符
				fail[tot] = nxt[getfail(s, fail[p], i)][c]; //tot点的后缀回文，可以由上一个节点的后缀回文尝试得到
				sed[tot] = sed[fail[tot]] + 1; // 以当前节点为结尾的回文串个数
				nxt[p][c] = tot; // 新建节点
			}
			last = nxt[p][c]; // 当前节点成为上一个节点
			cnt[last]++; //当前节点回文串++
			record[last] = i;
		}
	}
	void get_cnt()
	{
		for (int i = tot; i > 0; i--)
			cnt[fail[i]] += cnt[i];
		//fail[i] 的节点 为 i 节点的后缀回文串， 所以个数相加
	}
}pdt;
int main()
{
	scanf("%s", s);
	int n = strlen(s);
	pdt.init(); //初始化
	pdt.build();//如果多组测试的时候不仅仅需要init()和build()两个
	pdt.insert(s, n);//在建回文树
	pdt.get_cnt(); //得到当前回文串出现的次数
	ll ans = 0;
	for (int i = 2; i <= pdt.tot; i++) //第一个是无效的 从第二个开始是有效的回文串
	{
		int R = record[i]; //record记录了第i个类型的回文串的结束位置
		int L = record[i] - pdt.len[i] + 1;
		ans += pdt.cnt[i];
	}
	cout << ans << endl;
	return 0;
}


```
**如果看了注解还是不清楚怎么用 可以私聊我**

---

## 作者：顾z (赞：0)

> ### Description
>
> 求一个串中包含几个回文串。
>
> ### Input
>
> 输入一个字符串$S$
>
> ### Output
>
> 包含的回文串的个数.

看到题解里面有人人写回文自动机.

有必要那么麻烦嘛 emmm

我们直接跑$Manacher$就好了啊.

答案就是以每一位为中心的回文串长度/2的和。

(如果添加字符则为回文半径长度/2。)

这个就不多解释了.很明显的一个东西。

不能理解的话,可以看下这个

> ＃ a ＃ a ＃ b ＃ a ＃ a ＃
>
>  1  2 3 2 1 6 1 2 3 2 1
>
> 数字对应于每一个位置的回文半径
>
> .(实际上减去$1$才是,但是计算的时候要加上1,所以代码里面直接用了这个.)

``代码``

```c++
#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#define R register

using namespace std;

const int maxn=1008;

char ch[maxn];
char s[maxn<<2];
int len,RL[maxn<<2],MaxRight,center,ans;
int main()
{
    scanf("%s",ch);
    len=strlen(ch);
    for(R int i=0;i<len;i++)s[2*i+1]=ch[i];
    len=2*len+1;
    for(R int i=0;i<len;i++)
    {
        if(i<=MaxRight)
            RL[i]=min(RL[2*center-i],MaxRight-i);
        else RL[i]=1;
        while(s[i-RL[i]]==s[i+RL[i]] and i-RL[i]>=0 and i+RL[i]<len)
            RL[i]++;
        if(i+RL[i]-1>MaxRight)
            MaxRight=i+RL[i]-1,center=i;
    }
    for(R int i=0;i<len;i++)ans+=RL[i]/2;
    printf("%d",ans);
}
```

---

