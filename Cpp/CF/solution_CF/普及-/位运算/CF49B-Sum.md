# Sum

## 题目描述

Vasya终于学会了进位制，但他经常忘记写算式的基数。有一次，他看到他的笔记本上写着a+b=？，但是没有写明基数。现在Vasya认为算式的基数为p。他知道算式在不同的基数下，会有不同的结果，甚至在有些基数下是没有意义的。算式78+87的值在十六进制下为FF，在十五进制下为110，十进制下为165，九进制下为176，更小的基数下就没有意义了。现在，Vasya想要知道算式结果的最大长度。
我们定义数字的长度为数字的字符个数，在不同的进制下，同一个数字有不同的数字长度。

## 样例 #1

### 输入

```
78 87
```

### 输出

```
3
```

## 样例 #2

### 输入

```
1 1
```

### 输出

```
2
```

# 题解

## 作者：花园Serena (赞：7)

话说这个题目是蓝题就比较离谱

首先说结论，对于两个数 $x, y$ 相加，最终数字的长度最多为原来的两个数中位数较多的那个数的位数加一，这个是显然的就不细说了。

而我们在考虑的时候，其实只需要考虑一个进制，即 $x, y$ 各个位置上最大的那个数加一的这个进制。什么意思呢，打个比方

>设$x, y$ 分别为 76617 和 32219

那我们就考虑 10 进制，即 $y$ 中最大的那个数加一

为什么这样是对的呢？首先我们能够对答案作出贡献一定是因为进位，而我们得到的是在不同进制意义下相同的一个加法，所以我们考虑如何才会更容易进位，显然是基数越小越好，所以我们直接取到最小，即如果基数再小就会使式子没有意义的时候，如果连他都不能够进位，那么显然是不能对答案造成贡献的，反之答案则为 $x, y$ 中较大的那个数的位数加一。

那么怎么检查是否有解？很简单，就是 ｋ 进制高精度加法即可，最后判断是否进位

下为代码，如果有任何错误或疑问欢迎私信或是评论

```cpp
#include <bits/stdc++.h>
using namespace std;
#define R register int
const int MAXN = 1e3 + 10;
int a[MAXN], b[MAXN], c[MAXN];
int main() {
    int x, y; scanf("%d%d", &x, &y);
    int cnt = 0, tot = 0, p = -1;
    while (x) {
        a[++ cnt] = x % 10;
        x /= 10; p = max(p, a[cnt]);
    }
    while(y) {
        b[++ tot] = y % 10;
        y /= 10; p = max(p, b[tot]);
    }
    int ans = max(tot, cnt);
    for(R i = 1; i <= ans; i ++) {
        c[i] += a[i] + b[i];
        if(c[i] > p) c[i + 1] ++;
    }
    if(c[ans + 1]) ans ++;
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：liulif (赞：3)

*既然这题没有人发题解，那本蒟蒻就来水一篇吧。*

**其实这题的思路(~~大佬说：这题这么水还要思路吗？~~)跟高精度加法是一样的**

下面上代码：
```cpp
#include<iostream>
#include<string>
using namespace std;
string a1,b1;
int a[1005],b[1005],sum[1005];
int x,r,len;
int main()
{
    cin>>a1>>b1;	//字符串读入a和b
    r=-0x3f3f3f3f;	
    for(int i=0;i<a1.length();i++) 
    {
        r=max(r,a1[i]-48);
        a[a1.length()-1-i]=a1[i]-48;
    }
    for(int i=0;i<b1.length();i++) 
    {
        r=max(r,b1[i]-48);		//寻找所有数位中最大的基数
        b[b1.length()-1-i]=b1[i]-48;	//按位倒序存储a和b两个数字
    }
    r++;len=0;	//r++后就是r进制了(满r进1）
    while(len<=a1.length()||len<=b1.length())
    {
        sum[len]=a[len]+b[len]+x;	//a和b按位相加，x为上一次相加的进位
        x=sum[len]/r;	
        sum[len++]%=r;	//满r则进
    }
    while(!sum[len]&&len>0) len--;	//删除多余的前导0
    len++;		//由于我的数组是从0开始的，输出长度时还要加1
    cout<<len<<endl;
    return 0;
}
```
---
最后十分感谢[liuzhenhao](https://www.luogu.org/space/show?uid=59894)巨佬给予我的帮助,我是真的菜啊！

---

## 作者：MarchKid_Joe (赞：2)

# 背景

~~(2021-1-04)留下的坑，居然留到现在~~。所以我只是想把这道历史遗留问题解决掉。

# 形式化题意

求在 $x$ 进制下 $a+b$ 的数位个数。

# 思路

先考虑十进制，小学竖式。那 $x$ 进制同理。

所以这题只需要一个 $x$ 进制**高精度加法**的板子。

现在考虑如何求 $x$ ，既然让结果长度最长，那么肯定进制越**小**结果越长。又要让 $x$ 进制合法，只需要对 $a,b$ 的每一位的数字取最大值，最后再加 $1$ （ $x$ 进制没有 $x$ 吧），就行了。

- 流程
    
    对 $a,b$ 每一位取 $\max$ ，求得 $x$ 。
    
    模拟 $x$ 进制高精度加法。
    
    输出答案的长度。
    
# 高精度

建议熟悉高精度加法的dalao s 直接跳过。

本人喜欢**倒位存储**，这样就不用向前**补**0了。

比如 $a=9998,b=8$

$$
\begin{aligned}
 &8\\
+&8999\\
=&60001
\end{aligned}
$$

- 倒位存储

    ```cpp
	int input(int x[10],int len=0,char k=getchar())
	{
		int Length=0;
		int t[10]={};
		while(k<'0'||k>'9')	k=getchar();
		while(k>='0'&&k<='9'){t[++len]=k-'0';k=getchar();}
		while(len>0)x[++Length]=t[len--];
		return Length;
	}
    ```

那倒位存储的好处就体现出来了：低位下标低，低位向高位进位好处理，首先初始化结果的长度为 $\max (lena,lenb) + 1$ 。

至于加 $1$ ，因为可能会进位，最后在判断最高位是否为 $0$ ，也就是去除前导 $0$ 的过程。

设当前位为 $i$ ，第 $i$ 位对应的数字为 $number[i]$ 。
 $x\leqslant number[i]$ ，第 $i + 1$ 位进位 $\lfloor\frac{number[i]}{x}\rfloor$ ，当前位对 $x$ 取模。

最后判断去除前导 $0$ 。

- 初始化 $a+b$ 答案的长度

    ```cpp
    int cnt=max(lena,lenb)+1;
    ```

- 去除前导 $0$

    ```cpp
	while(cnt>0&&!ans[cnt]) cnt--;
    ```
- 模拟 $x$ 进制高精度加法

    ```cpp
	for(int i=1;i<=cnt;i++)
	{
		ans[i]+=a[i]+b[i];
		ans[i+1]+=ans[i]/x;
		ans[i]%=x;
	}
    ```

返回长度，结束了。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans[10],a[10],b[10];
int s,la,lb;
	int input(int x[10],int len=0,char k=getchar())/*倒位储存，当然可以直接输入字符串再倒过来*/
	{
		int Length=0;
		int t[10]={};
		while(k<'0'||k>'9')	k=getchar();
		while(k>='0'&&k<='9'){t[++len]=k-'0';k=getchar();}
		while(len>0)x[++Length]=t[len--];
		return Length;
	}
void get_begin(int *x,int length)/*得到x进制*/
{
	for(int i=1;i<=length;i++)
		s=max(s,x[i]);
}
int length(int x)
{
	int cnt=max(la,lb)+1;/*初始化*/
	for(int i=1;i<=cnt;i++)/*x进制加法*/
	{
		ans[i]+=a[i]+b[i];
		ans[i+1]+=ans[i]/x;
		ans[i]%=x;
	}
	while(cnt>0&&!ans[cnt]) cnt--;/*去除前导0*/
	return cnt;
}
int main()
{
	la=input(a);
	lb=input(b);
	get_begin(a,la);
	get_begin(b,lb);
	printf("%d",length(s+1));/*进制+1，因为x进制不能有x，所以取完最大值之后要+1*/
	return 0;
}
```


---

## 作者：EDqwq (赞：2)

 刚好看到一个帖子在问这道题，点进来就随便做做AC了。同时发现题解只有一篇且十分不清晰所以这里来~~水~~补上一篇题解。

---------------

#### 思路其实很简单，分为几个步骤：

1. 算出对于题目给出的$a$,$b$最小的有意义的进制数$n$。

1. 我们在$n$进制下算出$a + b$（得数为$n$进制数），该得数有几位便为答案。

但这里就有一个~~无聊到极致~~的问题：**为什么可以直接按最小进制数来呢？**

A：**易知，10进制下的一个数，在1-9进制下就会变“大”一点（其实值是不变的，但是把它当作10进制数看会变大，例如10进制下的2，在二进制下就为“10”），所以直接算最小的即为答案，不必再往上枚举。**

-----------------

思路分享到此为止，下面是几个**小坑**：

1. 我们算出两个数最小的数码要加一开始枚举。

1. **前导多余的0必须删除。**

1. **由于是从0开始循环，我们必须在最后将答案加一。**

--------------
上代码（有注释，可以配套食用）

```cpp
#include<bits/stdc++.h>//养成好习惯

using namespace std;

string aa,bb;
int a[10000],b[10000],c[100000];//a + b = c
int x,maxx = -21000,maxx1 = -21000,maxx2 = -21000,len;//x为进位小尾巴，maxx是最大的数码，len是答案

int main(){
	cin>>aa>>bb;
	//这里开始判断最大的数是多少
	for(int i = 0;i <= aa.length() - 1;i ++){//注意从0开始循环
		maxx1 = max(maxx1,aa[i] - 48);
		a[aa.length() - 1 - i] = aa[i] - 48;//注意string转int要减去48
	}
	for(int i = 0;i <= bb.length() - 1;i ++){
		maxx2 = max(maxx2,bb[i] - 48);
		b[bb.length() - 1 - i] = bb[i] - 48;
	}
	maxx = max(maxx1,maxx2) + 1;//加1开始枚举
	//这里开始高精度加法
	while(len <= max(aa.length(),bb.length())){
		c[len] = a[len] + b[len] + x;//x为进位小尾巴
		x = c[len] / 10;
		c[len ++] %= 10;//满maxx进一
	}
	while(1){//去掉前导可恶的0
		if(c[len] != 0)break;
		if(c[len] == 0)len --;
	}
	len ++;//最后加一因为从0开始循环
	cout<<len;
	return 0;//养成好习惯
}
```

###### 别看了结束了都散了吧

---

## 作者：奥斯卡小冰人 (赞：1)

本人的第一篇题解，如有误敬请谅解。

AC代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,k = 0,p[5],q[5],x = 0,y = 0,t[1000000] = {0};
    cin >> a >> b;
    while(a > 0) x++,p[x] = a % 10,k = max(k,p[x]),a /= 10;//求a的数位中最大的数，顺便把a的长度和数位记下
    while(b > 0) y++,q[y] = b % 10,k = max(k,q[y]),b /= 10;//同上
    x = max(x,y);//不浪费 减少碳排放量 从我做起（bushi
    for(int i = 1;i <= x;i++)
    {
        t[i] += p[i] + q[i];
        if(t[i] >= k + 1) t[i + 1]++;//不用管t[i]，因为只要长度不要具体数值
    }
    if(t[x + 1] != 0)x++;//有可能进位，长度++
    cout << x;
    return 0;
}
```



---

## 作者：wwwwwza (赞：0)

做这道题，我们应该想清楚，在哪种进制下， $a+b$ 得出的结果长度最长。  
我们先枚举一个数，如 $(100)_ {10}$ ，在九进制下等于     $(121)_ {9}$ ，接着计算。
 $(100)_ {10}=(144)_ {8}=(400)_ {5}=(1210)_ {4}=(1100100)_ {2}$ 。
可以发现：当进制数越小，这个数的长度越长，所以就像高精度加法一样就可以了。  
~~从另一个方面想，题目总不能让你枚举每个进制吧。~~  
现在，我们只需想最小进制数是什么就可以了。在十进制中，每一位的数大于十就要向前进位，在每个进制都是一样。所以我们只需求 $a$ 和 $b$ 中最大一位的数字加一（加一才能保证不进位）。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
const int mod = 998244353;
int a,b,k=0,tmp=0,cnt[N];
void rec(int x){
	while(x){
		k=max(k,x%10);
		x/=10;
	}
}
void cmp(int x){
	int tmp=0;
	while(x){
		cnt[++tmp]+=(x%10);
		x/=10;
	}
}
signed main(){
	cin >>a>>b;//输入 
	
	rec(a);rec(b);//确定进制数 
	k++;
	
	cmp(a);cmp(b);//高精度 
	for(int i=N-5;i>=1;i--){
		if(cnt[i]!=0){
			tmp=i;
			break;
		}
	}
	
	for(int i=1;i<=tmp;i++){//判断进位 
		cnt[i+1]+=(cnt[i]/k);
		cnt[i]%=k;
	}
	
	while(cnt[++tmp]){//判断最高位是否要向前移动 
		cnt[tmp+1]=cnt[tmp]/k;
		cnt[tmp]%=k;
	}
	
	cout <<tmp-1;//输出 
	return 0;
}
```

---

## 作者：NOIAKME (赞：0)

思路：

只要进制小，便越有可能进位。

我们就选一个尽可能小的 $p$，然后计算  ```a+b```。

**最小的有意义的 $p$，就是 $a$ 和 $b$ 的所有数位上的数中最大的那个数加一。**

比如 $78$ 和 $87$（样例），最大的进制是 $8$，所以 $p$ 就是 $9$。
说白了就是多了 $1$ 步的高精啦。

---

## 作者：_wjr_ (赞：0)

本蒟蒻写的一篇题解，码风怪异，不喜勿喷！

## 题目大意

给出两个数 $a , b$ ，问在任意进制下，最终所得到两数之和的长度的最大值是几。

## 题目思路

题目已经为我们把样例1解释了，我们不难猜测，当我们所取得基数最小时，长度会取到最大值。那么为什么呢？

我们不妨设我们有两个基数 $x , y (x < y)$，这样 $a + b_{(10)}$ 就会分别表示为 ${m_1 + {m_2}^x + \cdots + {m_r}^{(x^{r-1})}}_{(x)}$ 与 ${n_1 + {n_2}^y + \cdots + {n_s}^{(y^{s-1})}}_{(y)}$。因为这两个数的值要相等，所以 $r$ 肯定要大于 $s$ ，以弥补在前几位所相差的值。

那么，我们这道题就解完了。

不多说了，上代码！

```cpp
#include<bits/stdc++.h>

using namespace std;

int x[1000010], y[1000010];

int maxnum (int x) //判断整个数中最大的数字
{
    int mxnum = -1;
    while (x)
    {
        mxnum = max (mxnum, x % 10);
        x /= 10;
    }
    return mxnum;
}

int main()
{
    int a, b;
    cin >> a >> b;
    int p = max (maxnum(a), maxnum(b)) + 1;//确定基数
    int c = a, d = b, cnt1 = 0, cnt2 = 0;
    while (c)
    {
        x[++cnt1] = c % 10;
        c /= 10;
    }
    while (d)
    {
        y[++cnt2] = d % 10;
        d /= 10;
    }
    int s = 0, num = 1;
    for (int i = 1; i <= max (cnt1, cnt2); i++)
    {
        s += num * (x[i] + y[i]);
        num *= p;
    }//算出总和在这个基数下如何表示
    int ans = 0;
    while (s)
    {
        ans++;
        s /= p;
    }//求位数
    cout << ans;
    return 0;
}
```

萌新代码，码风奇特，不喜勿喷！

---

## 作者：Allanljx (赞：0)

## 思路
由于我们要长度最长，所以就需要进制尽可能小，所以我们可以找到每位的最大值，再将进制定为比这个数大一就行。然后再一位一位进行加法，跟高精度过程类似。具体模拟过程见代码注释。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s1,s2;
int a[1001],b[1001],maxn;
signed main()
{
	cin>>s1>>s2;
	int l1=s1.length(),l2=s2.length();//长度
	for(int i=l1-1,j=1;i>=0;j++,i--)//倒着存
	{
		a[j]=s1[i]-'0';
		maxn=max(maxn,a[j]);//找最大的数
	}
	for(int i=l2-1,j=1;i>=0;j++,i--)//倒着存
	{
		b[j]=s2[i]-'0';
		maxn=max(maxn,b[j]);//找最大的数
	}
	maxn++;//确定进制
	for(int i=0;;i++)
	{
		if(a[i]+b[i]<maxn/*不能进位*/&&a[i+1]==0/*没有下一位*/&&b[i+1]==0/*没有下一位*/&&i>=max(l1,l2)/*若不加则1001 1会跳出过早*/)
		{
			cout<<i<<endl;//位数
			break;
		}
		if(a[i]+b[i]>=maxn) a[i+1]++;//如果进位
	}
    return 0;
}
```


---

