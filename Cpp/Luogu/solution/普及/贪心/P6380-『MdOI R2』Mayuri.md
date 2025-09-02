# 『MdOI R2』Mayuri

## 题目背景

「万由里……怎么会？为什么你要……」

『我是灵力的结晶体，实施了封印，我当然会消失，不是吗？』

「封印？但是你和我……」

『第一次见面不能封印吗？笨蛋，我可是从大家的灵力里出生的，怎么可能讨厌你？从一出生，我就爱着你。』

「万由里……」

『虽然我竭力不让自己去想，但我一定是很羡慕大家……』

「等一下，万由里，不要消失……」

『但是我还是有一件能向大家炫耀的事，只有我和士道一样……』

「一样？」

『我已经不再是只为了消失而出生的生命。因为我遇见了你……已经足够了。』

「万由里……」

『谢谢你，士道。 』

![](https://cdn.luogu.com.cn/upload/image_hosting/9w6a0deg.png)

## 题目描述

在离开这个世界前，万由里想要寻找属于她的 Lucky Number。

万由里会给出一个数 $a$，以及一个长度为 $b$ 的 01 串 $S$。

简单的说，她的 Lucky Number 是满足以下条件的**正整数** $n$：

 - $n$ 的位数为 $b$ 且不含前导 $0$。

 - 若 $S$ 的第 $i$ 位为 $1$，则 $n$ 的前 $i$ 位组成的数是 $a$ 的倍数，否则 $n$ 的前 $i$ 位组成的数不是 $a$ 的倍数。

对于一个数，前 $i$ 位组成的数是指这个数前 $i$ 个数码依次拼接形成的数。例如 $312311$ 前 $3$ 位组成的数为 $312$，前 $5$ 位组成的数为 $31231$。


现在，请你帮助万由里计算一下，她的 Lucky Number 是多少。

由于满足条件的数可能会有多个，你需要输出**最小**的一个。若不存在，则请输出 `-1`。

## 说明/提示

【帮助与提示】

为方便选手测试代码，本题额外提供一组附加样例供选手使用。

[样例输入](https://www.luogu.com.cn/paste/5gnn8mg0) [样例输出](https://www.luogu.com.cn/paste/sgxjkbjd)

------
【样例解释】

对于样例一，$10$ 是 $2$ 位数，且 $10$ 的前 $1$ 位组成的数 $1$ 不是 $2$ 的倍数，而前 $2$ 位组成的数 $10$ 是 $2$ 的倍数。由于 $10$ 已经是最小的两位数，故不存在比 $10$ 更小的满足条件的数。

对于样例二，我们需要构造一个 $1$ 位数，满足这个 $1$ 位数整除 $10$。显然，这样的数不存在。

---

【数据范围】

**本题采用捆绑测试**


| 子任务编号 | $a \leq$ | $b\le$  | 分值   |
| ---------- | -------- | :------ | ------ |
| Subtask 1  | $10$     | $ 1$    | $20$   |
| Subtask 2  | $10 $    | $2$     | $20$  |
| Subtask 3  | $10 $    | $ 6$    | $20$  |
| Subtask 4  | $ 2$     | $ 18$   | $20$ |
| Subtask 5  | $ 10$    | $ 10^5$ | $20$ |


对于全部数据，保证 $2\le a\le 10$，$1\le b\le 10^5$，$S$ 中只包含 `0` 和 `1`。

## 样例 #1

### 输入

```
2 2
01```

### 输出

```
10```

## 样例 #2

### 输入

```
10 1 
1```

### 输出

```
-1```

## 样例 #3

### 输入

```
6 6
110100```

### 输出

```
601210```

# 题解

## 作者：BFqwq (赞：36)

看了看题解区的题解，纠结了一下还是把官方题解发出来吧。

感觉做的都比较麻烦，仅有的几个贪心写法的基本也都没给证明。

以下是官方题解。

------

首先，我们分析输出 `-1` 的情况。

容易发现，当 $a=10$ 并且 $S$ 的第一个字符为 `1` 时显然无解，具体证明同样例二。

除此以外的情况都是有解的。证明如下：

对于 $1$ 位数的情况，显然有解。

假设对于 $k(k\ge 1)$ 位有解，则对于 $k+1$ 位一定有解。

假设 $k$ 满足前位的一个数为 $c$，

则只需证明 $c\times 10,c\times 10+1\ldots c\times 10+9$ 中必有一个数为 $a$ 的倍数，且必有一个不为 $a$ 的倍数。

熟知对于任意正整数 $m$，相邻的 $m$ 个正整数中，必有 $1$ 个数为 $m$ 的倍数，$m-1$ 个数不为 $m$ 的倍数。

由于 $a\ge 2$，$c\times 10,c\times 10+1\ldots c\times 10+a-1$ 为 $a$ 个相邻的整数，

故它们中必定有一个数为 $a$ 的倍数，$a-1(a-1\ge 1)$ 个不为 $a$ 的倍数。

故在接下来的讨论中排除无解的情况。

------

### Subtask 1:

由于 $n$ 是正整数，在字符串长度为 $1$ 位的情况下，如果输入的串是 `0` ，则 $1$ 显然是最小的答案。

如果输入的串是 $1$ ，则显然直接输出 $a$ 是最小的，因为 $a$ 的最小倍数就是 $a$ 本身。

------

### Subtask 2:

对于 $n$ 为两位数的情况，我们可以选择直接打表，直接算出每种可能的对应最小解。

我们也可以采用枚举所有两位数逐个判断的方式。

当我们判断某一个数是否符合条件时，我们通过除以 $10$ 的方式得到其第一位，并判断其是否整除 $a$。

如果第一位符合条件，我们再直接判断其是否整除 $a$ 以判断前 $2$ 位是否满足条件。

------
### Subtask 3:

与上面的做法相似，直接枚举所有 $6$ 位数。

不同的是对于每一个数我们要判断 $6$ 次。

我们通过除以 $100000$ 得到其第一位，通过除以 $10000$ 得到其前两位构成的数，以此类推。

对于每个数，逐一判断。先分离其第一位判断是否满足条件，若满足则分离前两位，以此类推。

由于 $6$ 位数一共只有 $900000$ 个，因此我们只需要经过不超过 $900000$ 次枚举就可以找到符合条件的数。

------

### Subtask 4:

要判断一个数是否是 $2$ 的倍数只需要判断最后一位是否为 $2$ 的倍数 。

所以我们可以考虑从高位开始往后添加数字。

如果某一位是 `1` ，则我们需要添加的数字是 $2\ 4\ 6\ 8\ 0$ 中的一个。本着最小的原则，我们选择 $0$ 。

同理，如果某一位是 `0` 则我们选择添加一个 $1$。

另外，如果字符串的第一位是 `1` ，则我们需要进行特判。

------

### Subtask 5:

考虑延续上面的做法，从高位往后添加数字。

由于我们是在高位上添加的，因此我们只需保证我们添加的数字最小，就一定是最优的。

对于第一位，如果第一位的字符是 `0` 则我们添加 $1$ 最优，否则第一位添加 $a$ 最优。

然后对于后面的每一位，设我们当前的数是 $n_1$ ，添加的数是 $j$ ，则得到的数是 $10\times n_1+j$。

由于 $j$ 只有十种可能性，分别枚举尝试，选取最小的加到数的尾端。

另外，由于 $n$ 过大，无法直接记录，故每添加一个数后对 $a$ 取模，然后输出时以字符串的方式输出。

------
以下是 std 代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
char c[100005],n[100005];
int a,b;
int now;
int main(){

	cin>>a>>b>>c;
	if(c[0]=='0')n[0]='1',now=1;
	else{
		if(a==10){
			puts("-1");
			return 0;
		}
		else n[0]=a+'0';
	};
	for(int i=1;i<b;i++){
		now*=10;
		for(int j=0;j<=9;j++)
		if((now+j)%a==0&&c[i]=='1'||(now+j)%a!=0&&c[i]=='0'){
			now+=j;
			now%=a;
			n[i]=j+'0';
			break;
		}
	}
	cout<<n;
	return 0;
} 
```


---

## 作者：grass8cow (赞：9)

该题妥妥的贪心。

$now_i$ 表示答案的前 $i$ 位除以 $a$ 的余数。

$ans_i$表示从左往右第$i$位是哪个数字。

我们得使答案里的高位尽量小，这样才能使答案尽量小。

我们发现，当$c_i=1$时，无论 $now_{i-1}$ 是多少，
$now_{i-1}*10+ans_i$ 总是被 $a$ 整除 ，此时设$b$为$now_{i-1}*10$除以$a$的余数,则：$ans_i=a-b$ 。若 $b=0$ ，$ans_i=0$ 即可。可发现这样能使 $ans_i$ 最小，此时 $now_i=0$

当 $c_i=0$ 时，无论怎么选后面都有办法，那就选 $0$ 吧！

此时 $now_i=now_{i-1}*10$ ，再除以 $a$ 的余数。

但如果 $now_{i-1}*10$ 除以 $a$ 的余数为 $0$ ，我们就必须使$ans_i=1$，这样 $now_i$ 才不会被 $a$ 整除，此时 $now_i=1$

特殊处理最高位：

若 $c_1=0$ ，则 $ans_1=1$ ，否则 $ans_1=a$ ，此时唯一需要输出 $-1$ 的情况出现了：若 $c_1=1$ ，且 $a=10$ ，此时首位无法是$0$，也无法是 $10$ （它只是个数字啊），所以无解。

关于代码: $now$ 明显不需要数组，$ans$ 可一边计算，一边输出。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,i,now;
char c;
int main()
{
	cin>>a>>b>>c;
	if(a==10&&c=='1'){cout<<-1;return 0;}//特判无解 
	if(c=='1')cout<<a;
	else cout<<1,now=1;//特判首位 
	for(i=1;i<b;i++)
	{
		cin>>c; 
		now=now*10%a;
		if(c=='0'){if(now)cout<<0;else cout<<1,now=1;}
		else cout<<(a-now)%a,now=0;//如上文所述
	}
	return 0;
}
```
一个数组都没开耶！完结撒花！

---

## 作者：幻之陨梦 (赞：7)

$Solution:$

这道题是一道很基础的贪心题（~~但是我却没有AC，捂脸~~），这道题在构造时只有两种情况，第一种是当前位之前的数不能被 $a$ 整除，另一种就是需要被整除。这时候我们只需要用一个变量 $sum$ 来记录就行了。还有就是千万不能用getchar读入，我就错在了这个上面，导致我一直在WA。具体细节看代码注释。

$code:$
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char c=getchar();
    while(c<'0' || c>'9'){if(c=='-') f=0;c=getchar();}
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
    return f?x:-x;
}
int a,b,ans[100010],f;
long long sum;
char s;
int main()
{
    a=read(),b=read();
    for(int i=0;i<b;i++)
    {
        scanf(" %c",&s);
        if(s=='0')
        //如果当前位是0代表这个数字和之前的数字组成的多位数不能被 a 整除
        {
            f=0;//设一个变量f用于判断是否无解
            for(int j=0;j<=9;j++)//循环0~9逐个判断，运用贪心思想
            {
                if(((sum*10)+j)%a!=0)//如果不会被 a 整除
                {
                    if(i==0 && j==0) continue;//再判断是否含有前导 0
                    ans[i]=j;//将j记录到 ans 数组以便输出
                    sum=((sum*10)+j)%a;//将 sum 更新
                    f=1;//将 f 设为 1
                    break;
                }
            }
            if(f) continue;//如果找到了数就跳过
            puts("-1");没找到，输出 -1
            exit(0);//退出程序
        }
        else
        {
            f=0;//同上
            for(int j=0;j<=9;j++)//同上
            {
                if(((sum*10)+j)%a==0)//如果能被 a 整除
                {
                    if(i==0 && j==0) continue;//判断前导 0
                    ans[i]=j;//记录答案
                    sum=((sum*10)+j)%a;//更新 sum
                    f=1;//同上
                    break;
                }
            }
            //同上
            if(f) continue;
            puts("-1");
            exit(0);
        }
    }
    for(int i=0;i<b;i++) printf("%d",ans[i]);
    return 0;
}
```
如果有疑问比如说为什么不能直接输出，欢迎在讨论区里评论

如果这篇文章给予了你帮助，那您就点个赞再走吧，Thanks♪(･ω･)ﾉ

---

## 作者：NXYorz (赞：5)

[题目连接](https://www.luogu.com.cn/problem/P6380)

~~首先出题人还是很良心的给了80分暴力分~~

我们可以看出当$b \le 18$时可以用爆搜啊！我们只需要从小开始枚举每一位上的数就可以了。

代码大概是这样的：
```cpp
void dfs(int x)
{
    if(x==b+1)
        print();
    if(s[x-1]=='0')
    {
        for(int i=0;i<=9;i++)
            if((ans*10+i)%a!=0)
            {   
                ans= ans*10+i;
                dfs(x+1);
                ans=(ans-i)/10;
            }
    }
    else 
    {
        for(int i=0;i<=9;i++)
            if((ans*10+i)%a==0)
            { 
                if(x==1&&i==0) continue;  
                ans=ans*10+i;
                dfs(x+1);
                ans=(ans-i)/10;
            }
    }
}
```

拿到这80分之后我们想该怎么拿到剩下的$20$分。

不难发现目前我们面临的最大的问题就是这个数太“长”了，我们存不下，我们可以考虑用字符串来存这个答案，但是我们依旧面临的一个问题是：我们依旧不能来判断当前答案是否符合题意，即我们不能像小数据那样愉快的搜索了。

可以考虑模运算的性质，我们手完几个竖式之后就可以发现：

对于一个数$S$，如果可以分解为$S=S_1 * 10 + S_2$，那么 $S\mod k=((S_1\mod\ k) * 10+ S_2 )\mod k$

~~这是从竖式中可以看出来的东西，如果实在不懂可以尝试手完几个竖式。~~

明白了这一点我们就可以直接维护当前的余数就可以了，代码大概张这样：
```cpp
void Dfs(int x)
{
    if(x==b+1)
        print1();
    if(s[x-1]=='0')
    {
        for(int i=0;i<=9;i++)
            if((yu*10+i)%a!=0)
            {   
                sum[++l]=i+'0';
                long long c=yu;
                yu=(yu*10+i)%a;
                Dfs(x+1);
                yu=c;l--;
            }
    }
    else 
    {
        for(int i=0;i<=9;i++)
            if((yu*10+i)%a==0)
            { 
                if(x==1&&i==0) continue;  
                sum[++l]=i+'0';
                long long c=yu;
                yu=0;
                Dfs(x+1);
                yu=c;l--;
            }
    }
}
```

~~但是如果给的字符串全是1的话容易被卡~~

全部的代码就是这个样子：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100001
using namespace std;
int a,b,l;
string s;
char sum[N];
long long ans,yu;
void print()
{
    printf("%lld",ans);
    exit(0);
}
void print1()
{
    for(int i=1;i<=l;i++)
        printf("%c",sum[i]);
    exit(0);
}
void dfs(int x)
{
    if(x==b+1)
        print();
    if(s[x-1]=='0')
    {
        for(int i=0;i<=9;i++)
            if((ans*10+i)%a!=0)
            {   
                ans= ans*10+i;
                dfs(x+1);
                ans=(ans-i)/10;
            }
    }
    else 
    {
        for(int i=0;i<=9;i++)
            if((ans*10+i)%a==0)
            { 
                if(x==1&&i==0) continue;  
                ans=ans*10+i;
                dfs(x+1);
                ans=(ans-i)/10;
            }
    }
}
void Dfs(int x)
{
    if(x==b+1)
        print1();
    if(s[x-1]=='0')
    {
        for(int i=0;i<=9;i++)
            if((yu*10+i)%a!=0)
            {   
                sum[++l]=i+'0';
                long long c=yu;
                yu=(yu*10+i)%a;
                Dfs(x+1);
                yu=c;l--;
            }
    }
    else 
    {
        for(int i=0;i<=9;i++)
            if((yu*10+i)%a==0)
            { 
                if(x==1&&i==0) continue;  
                sum[++l]=i+'0';
                long long c=yu;
                yu=0;
                Dfs(x+1);
                yu=c;l--;
            }
    }
}
void subtask1()
{
    dfs(1);
    printf("-1");
}
void subtask()
{
    Dfs(1);
    printf("-1");
}
int main()
{
    //freopen("aa.in","r",stdin);
    scanf("%d%d",&a,&b);
    cin>>s;
    if(b<=18) subtask1(); 
    else subtask();
    return 0;
}
```

[安利博客(~~光速逃~~](https://www.luogu.com.cn/blog/niexiaoyang12138/)

~~错别字已修改QWQ~~

---

## 作者：monstersqwq (赞：4)

题目很容易理解，这里就不解释了，重点讲5个sub分别怎么做。

首先，因为 $a=10$ 的情况比较特殊，最好先特判一下，对以后有好处，而且可以涵盖 Sub1-5。

做法：对于第 $i$ 位，如果需要整除 $ans_i=0$，不要整除 $ans_i=1$（因为要求最小的 Lucky Number），如果第一位要求整除则无解。实际上，答案就是 $S$ 的“反码”，再特判一下第一位即可。

Sub1-3：很容易发现，这题的写法可能是个 dfs，枚举每一位，对照着 $S$ 看看能否整除即可，一旦搜出答案，就标记搜出，以后就不再搜索了，看起来复杂度很高，其实不高，待会会有讲解。

Sub4:其实可以和前三个合并，但是观察到 $a=2$，其实特判更好写。

做法：和 $a=10$ 几乎完全一样，除了当第一位要求整除时，$ans_1=2$ 而不是无解。

Sub5：看起来需要上高精模，而且做法也较麻烦，但是实际上用一些简单数论就可解决。

对于一个数 $n$，$10 \times n+c\quad(1\le c\le 10)$ 中总有一个数 $(10 \times n+c_1) \bmod a=0\quad(1\le a\le 9)$（$a=10$ 解决过了），这很好证明。

所以，每次 dfs 循环枚举的第一个符合题意的解，都包含着一个符合所有条件的解，这就是为什么 dfs 复杂度并不高的原因。

知道了这个，就可以从 dfs 变成直接循环每一位解决了。还有一个避开高精的方法：用模 $a$ 后的余数计算，每求出一位，就输出一位的解。

至于求每一位的方法，非常的简单，可以直接看我代码理解。

代码：
```cpp
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <queue>
using namespace std;
string s;
long long a,b,ans=0;
bool flag=false;
void dfs(long long step)
{
	if(flag) return;
	if(step>b)
	{
		cout<<ans<<endl;
		flag=true;
	}
	long long tmp=ans;
	for(long long i=0;i<=9;i++)
	{
		if(i==0&&step==1) continue;
		if(s[step-1]=='1')
		{
			if((ans*10+i)%a==0)
			{
				ans=ans*10+i;
				dfs(step+1);
				ans=tmp;
			}
		}
		else
		{
			if((ans*10+i)%a!=0)
			{
				ans=ans*10+i;
				dfs(step+1);
				ans=tmp;
			}
		}
	}
}
int main()
{
	cin>>a>>b;
	cin>>s;
	if(a==2)
	{
		for(int i=0;i<b;i++)
		{
			if(s[i]=='1')
			{
				if(i!=0)
				cout<<"0";
				else
				cout<<"2";
			}
			else
			{
				cout<<"1";
			}
		}
		return 0;
	}//Sub4
	if(a==10)
	{
		for(int i=0;i<b;i++)
		{
			if(s[i]=='1')
			{
				if(i==0)
				{
					cout<<"-1"<<endl;
					return 0;
				}
				else
				{
					cout<<"0";
				}
			}
			else
			{
				cout<<"1";
			}
		}
		return 0;
	}//a=10特判 
	if(b<=18)
	{
		cin>>a>>b;
		cin>>s;
		dfs(1);
		if(flag=false)
		{
			cout<<"-1"<<endl;
		}
		return 0;
	}//Sub1-3
	if(a!=10&&a!=2&&b>18)
	{
		long long momomo=0,tmpp=s.length() ;//momomo记录当前数mod a的值 
		if(s[0]=='1')
		{
			cout<<a;
		}
		else
		{
			cout<<"1";
			momomo=1;
		}//特判第一位 
		for(long long i=1;i<tmpp;i++)
		{
			momomo=(momomo*10)%a;
			if(s[i]=='1')
			{
				if(momomo==0)
				{
					cout<<momomo<<endl;
				}
				else
				{
					cout<<a-momomo;
				}
				momomo=0;
			}
			else
			{
				if(momomo==0)
				{
					cout<<"1";
					momomo=1;
				}
				else
				{
					cout<<"0";
				}
			}
		}
	}//sub5
	
    return 0;
}
```


---

## 作者：SpeedStar (赞：3)

# 算法分析
由于并不知道这题有什么规律，于是可以考虑暴力模拟+贪心的做法。

1. 根据题意我们只需处理$b$位，故最后所求的结果一般也是$b$位。另外考虑到数字可能会很大，所以我们可以直接输出每一位。

2. 考虑到不能有前导0，所以我们得把第1位和其他位分开处理。其中在第1位处有一种特殊情况，就是$a$为$-1$,此时将没有满足条件的数，故直接输出-1即可。至于其他情况，按题意直接模拟一下就行了。

3. 还有个小细节就是，考虑到$n$可能会爆，所以每次得把$n$模掉$a$。

## C++代码
```cpp
#include <iostream>

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	string s;
	cin >> s;
	
	int n = 0;
	for (int i = 0; i < b; i++) {
		if (i == 0) {
			if (s[0] == '0') {
				cout << 1;
				n = 1;
			}
			else {
				if (a == 10) {
					cout << "-1\n";
					break;
				}
				else {
					cout << a;
					n = a;
				}
			}
		}
		else {
			if (s[i] == '0') {
			for (int j = 0; j <= 9; j++) {
				if ((n * 10 + j) % a != 0) {
					cout << j;
					n = (n * 10 + j) % a;
					break;
				}
			}
		}
		else {
			for (int j = 0; j <= 9; j++) {
					if ((n * 10 + j) % a == 0) {
						cout << j;
						n = (n * 10 + j) % a;
						break;
					}
				}
			}
		}
	}
	
	return 0;
}
```


---

## 作者：ADay (赞：3)

### 先来个60Pts做法：
暴力枚举所有$b$位数，就可以拿60Pts  
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read()//快读
{
    int s=0,f=1;
    char ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')f=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        s=(s<<3)+(s<<1)+ch-48;
        ch=getchar();
    }
    return s*f;
}

inline void write(int x)//快写
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10^48);
}

inline int qpwm(int x,int y)//快速幂
{
    int res=1;
    while(y)
    {
        if(y&1)res=res*x;
        y>>=1;
        x=x*x;
    }
    return res;
}

int a,b;
const int Sz=1e5+5;
char s[Sz];

int main()
{
    a=read();b=read();
    scanf("%s",s+1);
    for(int i=qpwm(10,b-1);i<qpwm(10,b);i++)//暴力
    {
        bool flag=1;
        int tmp=i;
        for(int j=b;j>=1;j--)
        {
            if(s[j]-48)
            {
                if(tmp%a)
                {
                    flag=0;
                    break;
                }
                tmp/=10;
                continue;
            }
            if(tmp%a==0)
            {
                flag=0;
                break;
            }
            tmp/=10;
        }
        if(flag)
        {
            write(i);
            return 0;
        }
    }
    puts("-1");
    return 0;
}
```
~~给60分算仁慈了~~    
## 100Pts做法：$\mathcal{DFS}$
从最高位开始$\mathcal{DFS}$最后**字符串**答案$ans$的每一位，保存现在的余数$rem$和已枚举的位数$step$。
### 余数操作：往后拓展一位就$rem\times=10$
每一次字符串$s$的这一位有两种情况01： 
 ### 为0：
 即让$a$不整除，又要保证$ans$最小，那么考虑0或1，因为0和1相邻，总有一个能让$a$不整除，看余数决定即可(如果用0不行就选1，可以就尽量选0来保证最小)
 ### 为1：
 看余数,让这以为把剩下的余数补上，就能让$a$整除了  
 ## 代码：
 其他事项都在代码里了
 ```cpp
 #include<bits/stdc++.h>
using namespace std;

int a,b;
const int Sz=1e5+5;
char s[Sz],ans[Sz];

void dfs(int step,int rem)
{
    if(step==b)//最后一位时，同下
    {
        if(s[step]-48)//S这一位是1
        {
            rem*=10;
            rem=a-rem;
            while(rem<0)rem+=a;
            ans[step]=rem%a+48;
            if(a==10)ans[step]=48;
            puts(ans+1);//输出
        }
        else//是0
        {
            rem*=10;
            rem%=a;
            ans[step]=rem?48:49;
            puts(ans+1);//输出
        }
        exit(0);//退出程序
    }
    if(s[step]-48)//S这一位为1
    {
        rem*=10;
        rem=a-rem;
        while(rem<0)rem+=a;//可能是负数，补成非负
        ans[step]=rem%a+48;//补上余数
        if(a==10)ans[step]=48;//a是10一定为0
        dfs(step+1,0);//下一位
    }
    else//为0
    {
        rem*=10;
        rem%=a;
        if(!rem)ans[step]=49,rem=1;//余数是0就上1，且余数设为1
        else ans[step]=48;
        dfs(step+1,rem);//下一位
    }
}

int main()
{
    scanf("%d%d",&a,&b);//输入啊a，b
    if(b==1)//特判b=1
    {
        int t;
        cin>>t;
        if(t)
        {
            if(a==10)puts("-1");//一位不可能是10的倍数
            else putchar(a+48);
        }
        else putchar(49);
        return 0;
    }
    scanf("%s",s+1);//输入s
    if(s[1]-48)
    {
        if(a==10)
        {
            puts("-1");//第一位不可能是10的倍数
            return 0;
        }
        ans[1]=a+48;
        dfs(2,0);//从第二位开始
    }
    else
    {
        ans[1]=49;//首位不为0
        dfs(2,1);
    }
    return 0;
}
 ```
## 完结撒花！！！
~~可是为什么比赛时才80分5555~~

---

## 作者：__frj (赞：3)

# 本蒟蒻的第二篇题解，若有不足请多多指教


------------

本题是一道略有思维难度的题，但总体难度不高

## Subtask 1~4（80 pts）
由于b值不大，直接暴力模拟即可，下面贴代码
```cpp

#include<bits/stdc++.h>
using namespace std;
string s;
long long n=0;//开longlong，便于多骗点分
int main(){
	int a,b;
	cin>>a>>b;
	cin>>s;
	if(a>=10&&s[0]=='1'){//n的第一位要求构造一个非1位数倍数的数，显然这是不可能的，如样例二
		cout<<-1;
		return 0;
	}
    for(int i=0;i<b;i++){
		if(s[i]=='0'){//n的前i位不是a的倍数
			for(int j=0;j<=9;j++){//暴力枚举n的第i位，因为要求构造的数尽量小，所以从小往大找
				if(i==0&&j==0){//若此时构造的是最高位，这个数一定不是0
					continue;
				}
				if((n*10+j)%a!=0){//若符合要求
					n=n*10+j;//n值更新
					break;//结束枚举
				}
			}
		}
		if(s[i]=='1'){//n的前i位是a的倍数
			for(int j=0;j<=9;j++){//同上
				if(i==0&&j==0){
					continue;
				}
				if((n*10+j)%a==0){
					n=n*10+j;
					break;
				}
			}
		}
	}
	cout<<n;//输出答案
}

```
这种算法在Subtask 5时会因爆精度而出错，所以我们需要一个更优解

## Subtask 5（20 pts）
下面介绍正解
由于n与a的倍数有关，所以我们大可不必直接算n，只要计算n%a的值就可以了

在n%b=mod时，n*=10，b不变，不难得出mod=（10*mod）%b。
了解这一点后，此题便能迎刃而解了


------------

```cpp
#include<bits/stdc++.h>
using namespace std;
char s[100007];//定义一个字符数组存S
long long n=0;
int main(){
	int a,b,mod=0;
	cin>>a>>b;
	scanf("%s",s);//输入S
	if(a>=10&&s[0]=='1'){
		cout<<-1;
		return 0;
	}
    for(int i=0;i<b;i++){
    	if(i==0){
    		if(s[i]=='1'){//当n的最高位是a的倍数时
    			printf("%d",a);//由于mod=0，输出a即可保证n的最高为是a的倍数
    			mod=0;//可不加，因为没有变化
			}
			if(s[i]=='0'){
				printf("1");//由于最高位的数≠0，且a>1,直接输出1即可保证n的最高位不是a的倍数
				mod=1;//余数变成1
			}
		}
		else{
			mod=mod*10%a;//在n的位数变高后，n%b的值也随即发生改变
			if(s[i]=='1'){
				if(mod==0){//若余数等于0，输出0即可保证n的前i位是a的倍数
					printf("0");
				}
				else{//若余数不是0，则n的第i位要变成a-mod才能保证n的前i位是a的倍数
					printf("%d",a-mod);
				}
				mod=0;//经过一顿操作以后，余数归零
			}
			if(s[i]=='0'){
				if(mod!=0){//若余数不是0，符合要求，直接输出0，余数不改变
					printf("0");
				}
				if(mod==0){//若余数是0，则n的第i位变成1即可打破n的前i位是a的倍数
					printf("1");
					mod=1;//余数变为1
				}
			}
		}
	}
}

```
# The End.


---

## 作者：Gokix (赞：2)

[题目](https://www.luogu.com.cn/problem/P6380)

可爱的月赛T2，我竟然太弱了没能AC，事后发题解以祭之。

O=w=O

------------

前面4个 Substack 很简单，只需要模拟就好了。

假设我们现在计算到了第 $i$ 位，记录一个 $last$ 变量记录前 $i-1$ 位形成的数字。接下来从 $0$ 到 $9$ 进行枚举，看能不能成立，成立了就 $\operatorname{break}$ 掉。

需要注意的是没有前导0，特判一下就好了。

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;
long long last,a,b;
char s[1000010];
int main()
{
	long long i,j,u,v;
	cin>>a>>b;
	scanf("%s",s+1);
	if(a==10 && s[1]=='1')//这个无解的情况大家都能看懂吧，1位数不可能是10的倍数
	{
		cout<<"-1"<<endl;
		return(0);
	}
	for(i=1;i<=b;i++)
	{
		last*=10;
		if(s[i]=='1')
		{
			for(j=0;j<=9;j++)
			{
				if(i==1&&j==0)//一定记得特判
				{
					continue;
				}
				if((last+j)%a==0)
				{
					last+=j;
					break;
				}
			}
		}
		else
		{
			for(j=0;j<=9;j++)
			{
				if(i==1&&j==0)//一定记得特判
				{
					continue;
				}
				if((last+j)%a!=0)
				{
					last+=j;
					break;
				}
			}
		}
		cout<<j;
	}
	cout<<endl;
	return(0);
}
```


------------


我在比赛的时候以为 Substack5 是写高精的，然后没写，就跑了。

赛后经 %[qyc](https://www.luogu.com.cn/user/152213) %[zsy](https://www.luogu.com.cn/user/160484)  两位神仙的提醒我才想明白。

其实很简单，$last$ 边跑边$\mod a$ 就好了。

我看到这个结果时很是惊讶，但转念一想就发现自己的愚蠢。


------------

我们认为 $last = ka+c , now=10 \times last +j$。

所以 $now = 10 ka+10c+j$。

思考 $last$ 边跑边$\mod a$ 干了一件什么事。

观察上面的式子： $10ka$ 一定是 $a$ 的倍数，所以不用管它。现在相当于 $last=10c$ ，我们不要忘了 $c=last \mod a$,所以 $10c$ 的效果和 $10ka+10c$的效果是一样的。所以我们只需要记录 $last \mod a$ 就好了。

然后这个题就愉快的结束了:

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace  std;
long long last,a,b;
char s[1000010];
int main()
{
	long long i,j,u,v;
	cin>>a>>b;
	scanf("%s",s+1);
	if(a==10 && s[1]=='1')
	{
		cout<<"-1"<<endl;
		return(0);
	}
	for(i=1;i<=b;i++)
	{
		last*=10;
		if(s[i]=='1')
		{
			for(j=0;j<=9;j++)
			{
				if(i==1&&j==0)
				{
					continue;
				}
				if((last+j)%a==0)
				{
					last+=j;
					break;
				}
			}
		}
		else
		{
			for(j=0;j<=9;j++)
			{
				if(i==1&&j==0)
				{
					continue;
				}
				if((last+j)%a!=0)
				{
					last+=j;
					break;
				}
			}
		}
		cout<<j;
		last%=a;//就多了这一句
	}
	cout<<endl;
	return(0);
}
```
代码写的时候有些冗长，应该是可以不用大 if 的。~~但是懒得改了。~~

撒花！

---

## 作者：yhk1001 (赞：2)

我来介绍一下 $dfs$ 做法。从第一位开始搜索，从小到大枚举每一个位置上可以填的数字。如果找到了一个解就直接输出结束程序，反之如果所有情况都遍历了还是无解就输出$-1$。

此题的难点在于如何计算前 $i$ 位组成的数除以 $a$ 的余数。考虑到 $a \leq 10$，一个思路是枚举 $a$ 的值并利用整除特征，但是这样会比较麻烦，我们可以利用同余来优化。设前 $i - 1$ 位组成的数除以 $a$ 的余数为 $x$ ，第 $i$ 位为 $y$ ，则前 $i$ 位组成的数除以 $a$ 的余数为 $( x \times 10 + y ) \; \bmod a$。每次递归时记录前面的余数，计算就方便多了。

AC代码 $\;$ [评测记录](https://www.luogu.com.cn/record/35832483)
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<cmath>
using namespace std;

int a,b;
string s;
char ans[100005] = {0};//记录答案的每一位
void dfs(int k,int summ)//第k位，前k-1位组成的数除以a的余数为summ
{
	if (k == b + 1)//有解
	{
		for (int i = 1;i <= b;i++)
		{
			cout << ans[i];
		}
		cout << endl;
		exit(0);//结束程序
	}
	for (int i = 0;i <= 9;i++)
	{
		if (i == 0 && k == 1)//首位不为0
			continue;
		int sum = (summ * 10 + i) % a;//计算余数
		ans[k] = char(i + '0');//记录
		if ((s[k - 1] == '1' && sum == 0) || (s[k - 1] == '0' && sum != 0))
			dfs(k + 1,sum);//递归
	}
}

int main()
{
	cin >> a >> b >> s;
	dfs(1,0);
	cout << -1 << endl;//无解
    return 0;
}
```
打字不易，希望管理给过。

---

## 作者：过往梦魇之殇 (赞：2)

> $ZYX$了我

终于轮到信息课来发题解了$QwQ$

**思路简述：**

结论题？

这道题就是按位搜，复杂度显然是$O(b)$

首先我们需要一个$num$，来记一下$n$的前$i$位，注意要模一下$a$（防止数据爆炸）

再设一个$modd$记一下$num%a$的值

然后分类讨论：

当$s[i]$为$1$时：

	如果是第一位，ans[i]=a-modd
   	否则ans[i]=(a-modd)%a
    这样就能保证此时的a|num
    
当$s[i]$为$0$时：

	如果modd为0时，ans[i]=1
    否则就为0
    
另外地，如果$ans[i]>9$，则不存在满足的数，输出$-1$即可。

最后，输出$ans$就完成了！

**代码展示：**

```cpp
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<list>
#include<deque>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<bitset>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
#include<cmath>
#include<ctime>
#include<iomanip>
#include<complex>
#include<climits>
#define re register
#define in inline
#define pi acos(-1.0)
#define inf 2147483640
#define cd complex<double>
using namespace std;
in int read()
{
    int sum=0,negative=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')negative=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        sum=sum*10+ch-'0';
        ch=getchar();
    }
    return sum*negative;
}
in void write(int X)
{
    if(X<0)putchar('-'),X=-X;
    if(X>=10)write(X/10);
    putchar(X%10+'0');
}
int a,b;
string s;
int ans[100010],num=0;
int main()
{
	a=read();
	b=read();
	cin>>s;
	if(s[0]=='1'&&a>9){
		puts("-1");
		return 0;
	}
	for(re int i=0;i<b;i++){
		int modd;
		if(i){
			num=(num*10+ans[i-1])%a;
		}
		if(s[i]=='1'){
			modd=num*10%a;
			if(!i){
				ans[i]=a-modd;
			}
			else{
				ans[i]=(a-modd)%a;
			}
		}
		else{
			modd=num*10%a;
			ans[i]=modd?0:1;
		}
		if(ans[i]>9){
			puts("-1");
			return 0;
		}
	}
	for(re int i=0;i<b;i++){
		write(ans[i]);
	}
    return 0;
}
/*
8 100
1000000011111011101011110000111001001000011101011001110110110011001001100000111100111001111001110000
*/
```


###### ~~其实挺水的，嘿嘿~~

> $Thanks$ $For$ $Watching!$

---

## 作者：lndjy (赞：2)

这题，一个暴力的方法是枚举1-10，但是你会发现7的情况没有办法，然后你就会正解了。

一个略有思维的构造题。

位数过大，明显需要按位保存，接下来就是怎么判断是否整除。

思考后发现，a%x=(a-b\*x)%x,这就可以每次加一位都模一下。这样就可以了。

对于每一位，如果加上0没有影响，就加0，否则加上满足条件最小的。

注意细节，代码：
```cpp
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int ans[100005];
int f()
{
	cout<<-1;
	return 0;
}
int main()
{
	int a,b;
	string s;
	cin>>a>>b>>s;
	int sum=0;
	if(a==10&&b==1)
	{
		return f();
	}
	for(int i=0;i<b;i++)
	{
		sum*=10;
		if(i==0)//第一位特判，细节
		{
			if(s[i]=='0') ans[i]=1;
			else if(a==10) return f();else ans[i]=a;
		}
		else
		{
			if(s[i]=='0') if(sum%a==0) ans[i]=1;else ans[i]=0;
			else if(sum%a==0) ans[i]=0;else ans[i]=a-(sum%a)//如果加上0没有影响，就加0，否则加上满足条件最小的;
		 } 
		sum=sum+ans[i];
		sum%=a;
	}
	for(int i=0;i<b;i++)
	putchar(ans[i]+'0');
	return 0;
}
```


---

## 作者：Lovable_Wind (赞：1)

所以模拟他不香吗？

题目还是比较水的。

重点1：当搜索至i=0,j=0时，无论满足不满足条件都是不行的

重点2：对于数字和直接加上并验证，注意当计算数字和时不满足整除但是当前字符位为"1"时也能通过，这里是很多人的错点（见*）

重点3：-1的判断这里用了flag

快读只是装13。

直接输出字符数组解决RE问题即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,sum;
string S,ans;
int read()
{
    int ans=0,flag=1;
    char ch=getchar();
    while( (ch>'9' || ch<'0') && ch!='-' ) ch=getchar();
    if(ch=='-') flag=-1,ch=getchar();
    while(ch>='0' && ch<='9') ans=ans*10+ch-'0',ch=getchar();
    return ans*flag;
}
int main()
{
	a=read(),b=read();
	cin>>S;
	for (int i=0;i<b;i++){
		bool flag=0;
		for (int j=0;j<=9;j++){
			if ((sum+j)%a!=0&&S[i]=='0'||(sum+j)%a==0&&S[i]=='1'){//*
				if (i==0&&j==0) continue;
				flag=1;
				sum+=j;
				sum%=a;
				ans[i]=j+'0';
				cout<<ans[i];
				break;
			} 
		}
		if (!flag){
			cout<<-1<<endl;
			return 0;
		}
		sum*=10;
	}
	cout<<ans;
}
```


---

## 作者：J与M等于Y (赞：0)

**告知：此题解一般用于拓展和优化（虽然是蒟蒻的代码**

在月赛时初看到这道题，被 $b=10^5$ 吓了一跳。。。

蒟蒻第一次月赛太紧张了，以为这道题的贪心时复 $O(a^b)$，加上觉得时间充裕，就打了个沙雕代码，时复妥妥的~~吗？~~ $O(a)$ 了。（另：橙题打了190行

步入正题，蒟蒻用的方法比较奇怪，因为 $a<11$，所以窝将所有的整除快速方法罗列出来，整合在一起。求有时间大佬来看看！

### $2,4,8$ 的整除方法

$2$ 的整除方法就不用说了，只需判断末尾数就可以了，废话不多说，直接上代码。

```cpp
void a2(){
	for(int i=0;i<b;i++){
		if(s[i]=='0') printf("1");
		else{
			if(i==0) printf("2");//第一位不能为0，后面不加注释。
			else printf("0");
		}
	}
}
```

$4$ 的整除方法略难一些，但也只需要用一个数存一下就行了，但在整除上为了不用 $for$ 加了些特判。

```cpp
void a4(){
	long long p=0;
	for(int i=0;i<b;i++){
		if(s[i]=='0') {//特判同下
			if(p%2==0) printf("1"),p=1;
			else printf("0"),p=0;
		}
		else{
			if(i==0) printf("4");
			else {//特判，上一位是奇数放2，是偶数放0。
				if(p%2==0) printf("0"),p=0;
				else printf("2"),p=2;
			}
		}
	}
}
```

$8$ 的代码大致和 $4$ 的相同，不过特判似乎更多一些。

```cpp
void a8(){
	long long p=0;
	for(int i=0;i<b;i++){
		if(s[i]=='0') {//是不是感觉特判冗杂，但可以慢慢看，难度系数不大，但要判两位。
			if(p%4==0) printf("1"),p=(p*10+1)%100;
			else printf("0"),p=p*10%100;
		}
		else{
			if(i==0) printf("8");
			else {
				if(p%4==0) printf("0"),p=p*10%100;
				else {
					if(p%2==0) printf("4"),p=(p*10+4)%100;
					else {
						if((p*10+2)%8==0) printf("2"),p=(p*10+2)%100;
						else printf("6"),p=(p*10+6)%100;
					}
				}
			}
		}
	}
}
```
自此，$2,4,8$ 就讲完了。

### $3,6,9$ 的整除方法

$3,6,9$ 的方法一般来说没有 $8$ 那样复杂，也是难度系数不大的几个数。

$3$ 的整除方法就是将所有位相加可以被 $3$ 整除的数可被 $3$ 整除，只需用一个数存一下即可。

```cpp
void a3(){
	long long p=0,y,x;
	for(int i=0;i<b;i++){
		if(s[i]=='0'){
			if(p%3==0) x=1;
			else x=0;
			printf("%d",x);
			p=p+x;//记录位数。
		}
		else{
			if(i==0) {
				printf("3");
				p=3;
			}
			else{
				y=(3-p%3)%3;//防止y=3，可用if代替。
				printf("%d",y);
				p=p+y;
			}
		}
	}
}
```

$6$ 的整除方法即将是 $3$ 的和 $2$ 的相结合得来。在 $3$ 的基础上特判一下奇偶即可。

```cpp
void a6(){
	long long p=0,y;
	for(int i=0;i<b;i++){
		if(s[i]=='0'){//一般使%3!=0
			if(p%3==0) y=1;
			else y=0;
			printf("%d",y);
			p=p+y;
		}
		else{
			if(i==0) {
				printf("6");
				p+=6;
			}
			else{//必须满足奇偶条件，2|y
				if(p%3==0) y=0;
				if(p%3==1) y=2;
				if(p%3==2) y=4;
				printf("%d",y);
				p=p+y;
			}
		}
	}
}
```

$9$ 的代码和三真的没多大区别，将 $3$ 改成 $9$ 就差不多了，在此不再赘述。

### $5,10$ 的整除方法

相信有耐心看到这里的人已经头晕眼花了吧。这个专题就是来愉悦身心的。

$5$ 的代码和 $2$ 一样简单，只需判断最后一位，速度很快，没有玄学的 $%$。

```cpp
void a5(){
	for(int i=0;i<b;i++){//这就没什么可说了
		if(s[i]=='0') printf("1");
		else{
			if(i==0) printf("5");
			else printf("0");
		}
	}
}
```

接下来说 $10$ 了。$10$ 相信很多人也打了特判吧。第一位如果是 $1$，输出 $-1$ 否则 $1$ 为 $0$,$0$ 为 $1$。

```
if(a==10){//不知为何直接在主函数内特判了。。。
		if(s[0]=='1') cout<<-1<<endl;
		else{
			for(int i=0;i<b;i++){
				if(s[i]=='0') printf("1");
				else printf("0");
			}
		}
	}
```

### $7\quad ???$

打到这里，发现还有一个似乎无法解决的 $7$，我的内心是崩溃的。查了下百度，也没有可以实际应用的公式（懒）。

算了，抛开一切，打个贪心吧——玄学地觉得应该不太会有 $7$，不会特别要紧。

```cpp
//应该是唯一一个符合大众思维的函数了
int op[100005]={0};
bool ak(int j,int x){
	while(s[j]=='0'){//优化，碰到1证明前面已经是整除了，无需继续找了
		x=op[j]-x*2;//7的整除方法，没多大用，但可以保证不爆int
		j--;
	}
	return x%7;
}
void a7(){
	long long p=0;
	for(int i=0;i<b;i++){
		if(s[i]=='0'){
			if(s[i-1]=='1') printf("1"),op[i]=1;
			else {
				for(int j=0;j<7;j++){//正常的贪心，没有什么不妥
					if(ak(i-1,j)){
						printf("%d",j);
						op[i]=j;
						break;
					}
				}
			}
		}
		else{
			if(i==0) printf("7"),op[i]=7;
			else{
				if(s[i-1]=='1') printf("0"),op[i]=0;//直接判掉
				else {
					for(int j=0;j<7;j++){//正常的贪心，也没有什么不妥
					    if(!ak(i-1,j)){
							printf("%d",j);
							op[i]=j;
							break;
						}
					}
				}
			}
		}
	}
}
```

自此，$190$ 行的代码就讲完了啦啦啦！

**求管理员大大给通过！！**

---

## 作者：封禁用户 (赞：0)

看到这道题，首先会想到暴搜。考虑到会有高精度对单精度取模，运用同余定理，有以下代码：
```cpp
for(int j=0;j<=i;j++)
	r=(r*10+n[j])%a;
```
其中$r$存储余数，$n$数组存储高精度数，$i$为高精度数位数，$a$为单精度数。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char S[100001];
int a,b,r,n[100000]={1};
int main()
{
	cin>>a>>b>>S;
	for(int i=0;i<b;i++)//逐位处理
	{
		for(;n[i]<10;n[i]++)//从小到大枚举，n[0]即最高位从1开始，其余位从0开始
		{
			r=0;
			for(int j=0;j<=i;j++)//高精度对单精度取模
				r=(r*10+n[j])%a;
			if(bool(S[i]-'0')^bool(r)==true)//即：S[i]=0时，若余数非0则满足条件；S[i]=1时，若余数为0则满足条件
				break;
		}
		if(n[i]==10)//如果0~9（或1~9）都不满足条件则输出-1，退出程序
		{
			printf("-1");
			return 0;
		}
	}
	for(int i=0;i<b;i++)
		printf("%d",n[i]);
	return 0;
}
```

很明显，时间复杂度为$O(n^2)$,T了Subtask5。

怎么办呢？

~~然后我就枚举1~10，枚举了一个小时发现#16是a=7~~

我们想到：可以用$r$存储余数，每处理完一位令$r=(r*10+n[i])\%a$（$n[i]$为当前处理的那一位）即可。

还能发现，当且仅当$a=10$且$S[0]='1'$时不存在所求数，特判一下即可。

此外，由于最高位不为零，要对$n[0]$进行预处理（具体看代码）。

上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char S[100001];
int a,b,r,n[100000];
int main()
{
	cin>>a>>b>>S;
	if(a==10 && S[0]=='1')//特判-1的情况
	{
		cout<<-1;
		return 0;
	}
	n[0]=(S[0]=='1')?a:1;//预处理n[0]，否则S[0]='1'时，n[0]会等于零
	r=(S[0]=='1')?0:1;
	for(int i=1;i<b;i++)//逐位处理
	{
		if(S[i]=='0')//S[i]='0'时，如果前面的数位能被整除则此位为1，不能被整除则为0
			n[i]=bool(r*10%a)?0:1;
		else//否则计算最小的满足条件的值
			n[i]=(a-r*10%a)%a;
		r=(r*10+n[i])%a;//处理余数
	}
	for(int i=0;i<b;i++)
		printf("%d",n[i]);
	return 0;
}
```

---

## 作者：BreakPlus (赞：0)

看到这道题，就觉得这是一道数学题。可我数学不好，比赛的时候就抱着侥幸心理，准备爆搜骗点分。

一下子写了个爆搜代码没测大样例交上去，80分。

code1:

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
long long ans;
char str[1000];
void DFS(int wei)//爆搜
{
    if(str[wei]=='1'&&ans%a) return;
    if(str[wei]=='0'&&(ans%a==0)) return;//判断是否符合，剪枝
    if(wei==b-1)//如果搜完了输出答案
    {
        cout<<ans;
        exit(0);//终止程序
    }
    for(int i=0;i<=9;i++)//枚举下一位
    {
        ans=ans*10+i;
        DFS(wei+1);//搜索
        ans/=10;//回溯
    }
}
int main()
{
    cin>>a>>b>>str;
    for(int i=1;i<=9;i++)//第一位不能是0
    {
        ans=i;
        DFS(0);//爆搜函数
    }
    cout<<-1;//没有答案输出-1
}
```

哎，为什么 Subtask5 我的评测结果是 WA 呢？难道不应该 T 掉吗？

于是我就写了个高精度。结果高精度超时了。


code2:
```cpp
#include<cstdio>
using namespace std;
int a,b;
int ans[100100],len=1;
char str[100100];
int modd(int *anss,int f)
{
    int x=0;
    for(int i=1;i<=len;i++)
        x=(x*10+anss[i])%f;
    if(x==0) return 0;
    return x;
}//高精度
void DFS(int wei)
{
    if(str[wei]=='1'&&modd(ans,a)) return;
    if(str[wei]=='0'&&(modd(ans,a)==0)) return;
    if(wei==b-1)
    {
        for(int i=1;i<=len;i++) printf("%d",ans[i]);
        exit(0);
    }
    for(int i=0;i<=9;i++)
    {
        len++;
        ans[len]=i;
        DFS(wei+1);
        ans[len]=0;
        len--;
    }
}
int main()
{
    scanf("%d%d%s",&a,&b,str);
    for(int i=1;i<=9;i++)
    {
        ans[1]=i;
        DFS(0);
    }
    if(!end) puts("-1");
    return 0;
}
```

后来发现高精度的部分复杂度是 $O(n)$ 的，所以不行。

仔细想想，搜索判断的时候总是 $\bmod \ a$，所以我们可以把 code1 和 code2 结合。一个数组存答案，然后用一个长整型来存储答案 $\bmod \ a $。

问题解决了。

所以，做题的时候要灵活哦。

最后代码：

```cpp
#include<stdio.h>
long long a,b;
long long ans;
int answer[100010],len=1;
char str[1000100];
int end;
void DFS(int wei)
{
    if(end) return;
    if(str[wei]=='1'&&ans%a) return;
    if(str[wei]=='0'&&(ans%a==0)) return;
    if(wei==b-1)
    {
        int i;
        for(i=1;i<=len;i++) printf("%d",answer[i]);
        end=1;
        
    }
    len++;
    long long tmp=ans;
    int i;
    for(i=0;i<=9;i++)
    {
        ans=(tmp*10+i)%a;
        answer[len]=i;
        DFS(wei+1);
        answer[len]=0;
    }
}
int main()
{
    scanf("%lld%lld%s",&a,&b,str);
    int i;
    for(i=1;i<=9;i++)
    {
        ans=i;
        answer[1]=i;
        DFS(0);
    }
    if(!end) puts("-1");
}
```

---

