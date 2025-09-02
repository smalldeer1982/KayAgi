# Logging

## 题目描述

The main server of Gomble company received a log of one top-secret process, the name of which can't be revealed. The log was written in the following format: «\[date:time\]: message», where for each «\[date:time\]» value existed not more than 10 lines. All the files were encoded in a very complicated manner, and only one programmer — Alex — managed to decode them. The code was so complicated that Alex needed four weeks to decode it. Right after the decoding process was finished, all the files were deleted. But after the files deletion, Alex noticed that he saved the recordings in format «\[time\]: message». So, information about the dates was lost. However, as the lines were added into the log in chronological order, it's not difficult to say if the recordings could appear during one day or not. It is possible also to find the minimum amount of days during which the log was written.

So, to make up for his mistake Alex has to find the minimum amount of days covered by the log. Note that Alex doesn't have to find the minimum amount of days between the beginning and the end of the logging, he has to find the minimum amount of dates in which records could be done. (See Sample test 2 for further clarifications).

We should remind you that the process made not more than 10 recordings in a minute. Consider that a midnight belongs to coming day.

## 说明/提示

Formally the 12-hour time format is described at:

- http://en.wikipedia.org/wiki/12-hour\_clock.

 The problem authors recommend you to look through these descriptions before you start with the problem.

## 样例 #1

### 输入

```
5
[05:00 a.m.]: Server is started
[05:00 a.m.]: Rescan initialized
[01:13 p.m.]: Request processed
[01:10 p.m.]: Request processed
[11:40 p.m.]: Rescan completed
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
[09:00 a.m.]: User logged in
[08:00 a.m.]: User logged in
[07:00 a.m.]: User logged in
```

### 输出

```
3
```

# 题解

## 作者：Rainbow_qwq (赞：10)

[原题](https://www.luogu.org/problemnew/show/CF16D)

做这道题还是有很多技巧的。

比如，我们可以用scanf格式读入等。

另一位写题解的大佬解释的不清楚，我会解释的清楚一点。

下面是一段我的~~WA代码~~：
```cpp
#include<cstdio>
using namespace std;
char s[10010],ch;
int hour,min,n,ans=1,pre_hour,pre_min;
//pre_hour,pre_min保存上一个语句的小时，分钟。
int main()
{
    scanf("%d",&n);
    getchar();//吃掉换行符
    while(n--)
    {
        scanf("[%d:%d ",&hour,&min);//scanf格式读入,不用再处理字符串了
        ch=getchar();//我们只关心下一个字符是a还是p。
        gets(s);	 //剩下这一行，一概不管，一个gets读掉
        //接下来处理时刻，转换为24小时制。
        hour%=12;
        if(ch=='p')hour+=12;
        //判断
        if(hour<pre_hour||(hour==pre_hour&&min<pre_min))ans++;
        //更新
        pre_hour=hour;pre_min=min;
    }
    printf("%d",ans);
    return 0;
}
```
但是WA了，什么原因呢？？

我只好自己独了一遍英文题面，发现这样一句话：
```cpp
We should remind you that the process made not more than 10 recordings in a minute. 
```
翻译一下：一分钟内不可能有10个以上的任务。

这翻译里没有啊~~~投诉一下翻译~~

于是，我加了一个计数器num就过了。解释在代码中。

**AC 代码**：
```cpp
#include<cstdio>
using namespace std;
char s[10010],ch;
int hour,min,n,ans=1,pre_hour,pre_min;
//pre_hour,pre_min保存上一个语句的小时，分钟。
int main()
{
    scanf("%d",&n);
    getchar();//吃掉换行符
    while(n--)
    {
        scanf("[%d:%d ",&hour,&min);//scanf格式读入,不用再处理字符串了
        ch=getchar();//我们只关心下一个字符是a还是p。
        gets(s);	 //剩下这一行，一概不管，一个gets读掉
        //接下来处理时刻，转换为24小时制。
        hour%=12;
        if(ch=='p')hour+=12;
        //判断
        if(hour<pre_hour||(hour==pre_hour&&min<pre_min))ans++;
        if(hour==pre_hour&&min==pre_min)num++;//时刻没变，计数器++
        else num=1;//时刻变了，计数器重置
        if(num>10)ans++,num=1;//达到10个，计数器重置，天数++
        //更新
        pre_hour=hour;pre_min=min;
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：_zexal_ (赞：2)

## 思路
我们进行模拟,每次记录上一条消息的时间，然后我们比较即可。如果这一条时间小于上一条时间，答案加上一即可。
## 坑点
注意题目中提到 $n\leq100$ 且**一分钟消息不超过十个**(有个人被坑了，我不说是谁)。
## AcCode
```cpp
#include<bits/stdc++.h>
using namespace std;
char s[10010];
int h,m,n,ans,last_h,last_m,number;
int main()
{
    scanf("%d",&n);
   	getchar();
    for(int i=1;i<=n;i++)
    {
     	gets(s);
     	h=(s[1]-'0')*10+s[2]-'0';
     	m=(s[4]-'0')*10+s[5]-'0';
     	//cout<<s;
     	h%=12;
        if(s[7]=='p') h+=12;
      //  cout<<h<<" "<<m<<" "<<endl; 
        if(h<last_h||(h==last_h&&m<last_m))
		{
		ans++; 
		//cout<<i;
		}
		if(h==last_h&&last_m==m) number++;
		else number=1;
		if(number>=10) ans++,number=1;//注意，是不超过，而不是超过！
		last_h=h;
		last_m=m;
    }
    printf("%d",ans+1);
    return 0;
}
```




---

## 作者：Light_az (赞：1)

### 模拟好题

题意：给定多个时间点，问这些时间点最少要多少天可以按时间 **顺序** 发送。

对于最简单的思路，我们记录每一次输入前一天的时间点和这一次的比较，记小时数为 $x$，分钟数为 $y$，首先将 $x$ 取模 $12$ 小时保证是上午时间，如果时间后缀为 `p.m.`，那么我们将 $x$ 加上一个上午的时间即 $12$ 小时，$y$ 一定合法因此我们不需要处理。

然后我们比较上一次的时间点：

- $x$ 相同，则比较 $y$，如果这一次的 $y$ 小于上一次，则天数增加。

- $x$ 不同，则比较 $x$，如果这一次的 $x$ 小于上一次，则天数增加。

最后更新上一次的时间点，整个模拟完成。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,ans=1,t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0,Mod;
string s1,s2;
char s[N];
int main(){
	cin>>T;
	getchar();
	while(T--){
		ll x1,y1;
		scanf("[%lld:%lld ",&x1,&y1);
		gets(s);
		if(s[0]=='p') x1+=12;
		if(x==x1&&y>y1) ans++;
		if(x>x1) ans++;
		x=x1,y=y1;
	}
	cout<<ans;
	return 0;
}
```

当然，没有这么快结束，我们发现第 $14$ 个测试点发生了错误，再次阅读题意我们发现一个时间点有可能连续出现多次，当时间点连续出现超过 $10$ 次时，我们强制认为新的一天到来，因此我们加上一个计数器就可以通过本题了。

## Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,ans=1,t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0,Mod;
string s1,s2;
char s[N];
int main(){
	cin>>T;
	getchar();
	while(T--){
		ll x1,y1;
		scanf("[%lld:%lld ",&x1,&y1);
		gets(s);
		x1%=12;
		if(s[0]=='p') x1+=12;
		if(x==x1&&y==y1) cnt++;
		else cnt=0;
		if(cnt==10) ans++,cnt=0;
		if(x==x1&&y>y1) ans++;
		if(x>x1) ans++;
		x=x1,y=y1;
	}
	cout<<ans;
	return 0;
}
```

## End

[![](https://cdn.luogu.com.cn/upload/usericon/781159.png)](https://www.luogu.com.cn/user/781159)

---

## 作者：天天快乐 (赞：1)

这是一道简单的模拟题。
但是需要注意许多地方，需多看题！！！
具体见代码：
```
#include <bits/stdc++.h>
using namespace std;

char str[105];

int main()
{
	int n;
	cin >> n;
	gets (str);
	
	int ans=1;
	int h=0, m=-1, cnt=1;
	int i;
	
	for (i=0; i<n; i++){
		gets (str);
		int th=10*(str[1]-'0') + (str[2]-'0');
		int tm=10*(str[4]-'0') + (str[5]-'0');
		
		if (th == 12)  th = 0;
		if (str[7] == 'p')  th += 12;
		if (th < h || (th == h && tm < m))  ans++;
		if (th == h && tm == m)  cnt++;
		else  cnt = 1;
		
		if (cnt == 11){
			ans++;
			cnt = 1;
		}
		
		h = th, m = tm;
	}
	
	cout << ans << endl;
	return 0;
}

//请勿抄袭
```

---

## 作者：Mistybranch (赞：0)

[传颂门](https://www.luogu.com.cn/problem/CF16D)

题目大概意思是：根据 $n$ 条记录计算这些记录所覆盖的最小天数，注意一分钟最多 $10$ 条记录。

因为这道题数据量蛮小的（$n \leq 100$），所以直接模拟即可，但是细节蛮多的，下面直接说思路：

- 将所有记录的时间转化为标准的 $24$ 时计时法。

```cpp
scanf("  ");
scanf("%c", &c1);
scanf("%d%c%d", &i1,&c2,&i2);
gets(s);

i1 %= 12;

if (s[1] == 'p') {
	i1 += 12;
}
```

- 接着比较相邻的记录里的时间是否可以在同一天（也就是说第 $i$ 个记录是不是在第 $i + 1$ 条记录时间之前的），如果可以，则结果不加一天，否则结果加一天。

- 同时应该注意的是我们要记录同一分钟内消息出现的次数，满十加一天。

```cpp
if (ans) {
	if (!((i1 < st.top().first) || (i1 == st.top().first && i2 < st.top().second))) {
       ans--;
	}
	
	if (i1 == st.top().first && i2 == st.top().second) {
		cc++;
	}
	
	else {
		cc = 1;
	}
}

if (cc > 10) {
   	ans++;
   	cc -= 10;
}

st.push(make_pair(i1, i2));
ans++;
```

完整代码：
```cpp


#include <bits/stdc++.h>

using namespace std;

int n, ans;
stack<pair<int, int> > st;

int main () {
    char c1, c2, s[49];
    int i1, i2, cc = 0;
		int b,c;
        char d,e,f[40];
    
	scanf("%d", &n);
	
	for (int l = 1; l <= n; l++) {
        scanf("  ");
        scanf("%c", &c1);
        scanf("%d%c%d", &i1,&c2,&i2);
        gets(s);
        
        i1 %= 12;
        
        if (s[1] == 'p') {
        	i1 += 12;
		}
		
        if (ans) {
        	if (!((i1 < st.top().first) || (i1 == st.top().first && i2 < st.top().second))) {
        		ans--;
			}
			
			if (i1 == st.top().first && i2 == st.top().second) {
				cc++;
			}
			
			else {
				cc = 1;
			}
		}
		
        if (cc > 10) {
        	ans++;
        	cc -= 10;
		}
		
        st.push(make_pair(i1, i2));
        ans++;
	} 
	
	cout << ans << endl;
	
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

[CF16D Logging 原题](https://www.luogu.com.cn/problem/CF16D)

[博客内查看效果更加](https://www.luogu.com.cn/blog/2010-05-02/solution-cf16d)
### $讲解$
这道题大体思路是：
- 先不断读入，为了**节省空间**（当然这可以不需要），我们可以直接在读入后进行操作，输入可以用 ```scanf```（更方便），但我给的代码就直接使用 ```cin```。
- 接着就进行直接判断，可以先将时，分转化成目前离当日 $00:00$ **过去了多长时间**，这要好计算，再判断**大小**，要是之前时间 $>$ 现在时间，则~~时光倒流了~~**又过了一天**。
- 切记，还要有一个**计数器**，初值为一，如果之前时间$=$现在时间,则计数器 $+1$ ，否则计数器变为 $1$ ，如果计数器值大于 $10$，则**又过了一天**，并将计数器的值改为 $1$。

### code
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	int cnt = 1;
	int lastt = -1;//上一次的
	int ans = 1;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int h, m, t;
		string s, nouse1/*后面的命令，没用！*/;
		char nouse2/*一开始的[和后面的:*/;
		cin >> nouse2 >> h >> nouse2 >> m >> s;
		getline(cin, nouse1);//输入
		h %= 12;//不能少
		if (s == "a.m.]:")t = h * 60 + m;午
		else t = 720 + h * 60 + m;
		if (lastt == t)//如果之前和现在相同，计数器+1
		{
			cnt++;
		}
		else
		{
			cnt = 1;
		}
		if (lastt > t || cnt > 10)
		{
			ans++;
			cnt = 1;
		}

		lastt = t;


	}
	cout << ans;
	return 0;
}
```
感谢 NaOH_Frog 大佬。


---

## 作者：Query_Failed (赞：0)

本道题在完成时一定要注意细心，~~不然就会像本蒟蒻一样错很多次~~，大体部分上按照题目要就完成即可。

## 重要思路：
1. 本题最重要的思路是在时间的判断上。在判断这些消息是否是同一天时，我们需要判断的是有没有可能出现~~时光倒流的现象~~（雾），即后发出的消息的时间在先发出的消息的时间之前，这种情况**在一天之内不可能发生**，因此肯定它们是在两天的两条消息。以上是最主要的判断方式。

1. 除了以上的判断，我们还需要加上另一项判断。由于题中强调**保证一分钟内消息不超过10个**,因此我们需要单独用一个计数的变量。如果同一分钟消息超过十个，则这些消息也肯定不是同一天的。

## 其他技巧：
1. 输入之后将所有的时间都转换为分钟的单位，方便计算。

1. 在输入“上午或下午”时，只需要读取第一个字符即可判断出是上午还是下午。


## 附AC代码：
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int main()
{
	int n;
	cin>>n;
	char gj1[n];      //工具1，用来输入前方括号。 
	char gj2[n];      //工具2，用来输入冒号。 
	char ap[n];
	string gj3[n];    //工具3，用来输入剩下的一长串无用信息。 
	string gj4;       //工具4，用来输入换行。
	int h[n],m[n];
	getline(cin,gj4);  //输入换行。
	for(int i=0;i<n;i++)
	{
		cin>>gj1[i]>>h[i]>>gj2[i]>>m[i]>>ap[i];
		h[i]%=12;
		if(ap[i]=='p') h[i]+=12;
		m[i]+=h[i]*60;  //将所有时间的单位转换为分钟。 
		getline(cin,gj3[i]);
	}
	int sum=1,count=0;
	for(int i=0;i<n-1;i++)
	{
		if(m[i]>m[i+1]) sum++;    //直接用总分钟数判断。 
		if(m[i]==m[i+1]) count++;
		else count=0;  //如果不是在同一分钟内，计数器清零。 
		if(count==10)
		{
			count=0;
			sum++;
		}
	}
	cout<<sum;
	return 0;
}

```


---

## 作者：liupan2010 (赞：0)

前言：

[题目传送门](https://www.luogu.com.cn/problem/CF16D)

简单模拟。

这篇题解参考了[ Rainbow_qwq 的题解](https://www.luogu.com.cn/blog/151935/solution-cf16d)的读入方式。

思路：

对于读入数据，我们可以用到 `scanf` 的一个小 trick，只读取小时，分钟，以及上下午。

我们先让小时对 $12$ 取模，这样就转变为了 $12$ 小时。

当上下午读取到 $\texttt{'p'}$ 时，我们就将小时加上 $12$。

这个时间做了什么我们就可以将其忽略，只是将其输入。注意，这个行为可能带有空格，所以我们要读取一行。你可以使用 `getline` 或者 `gets`。当然，`gets` 是不安全的，但是它好写啊。

我们可以想到，当这次操作的小时小于上次操作的小时，或者这次操作和上次操作小时相同，但是这次操作的分钟小于这次操作，那就说明跨了一天。这可能比较难理解。

你可以想一下，上次操作在 $18$ 点 $30$ 分，这次操作在 $17$ 点或者在 $18$ 点 $29$ 分。时间不可能倒流，所以跨了一天。

还有，题目中讲了，一分钟内最多有 $10$ 个操作，那么在同一分钟做了超过 $10$ 次操作，这就说明这是在两天的同一时刻做的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,Hour,Minute,PrevHour,PrevMinute,Count,Answer=1;
char AMorPM,Message[25];
int main(){
	cin>>n;
	getchar();
	while(n--){
		scanf("[%d:%d %c.m.]:",&Hour,&Minute,&AMorPM);
		gets(Message);
		Hour%=12,(AMorPM=='p')?Hour+=12:1;
		(Hour<PrevHour||(Hour==PrevHour&&Minute<PrevMinute))?Answer++:1;
		(Hour==PrevHour&&Minute==PrevMinute)?Count++:Count=1;
		(Count>10)?Answer++,Count=1:1;
		PrevHour=Hour,PrevMinute=Minute;
	}
	cout<<Answer;
	return 0;
}
```

---

## 作者：Cuiyi_SAI (赞：0)

## 题目大意

给你多串格式为 $[hour:minute am/pm]$ 的电子时间，求这些时间覆盖的最少天数。

## 解题思路

我们考虑把所给的时间都转换为 $24$ 时计时法，然后将其时分秒压缩为一个 $10^4$ 级别的数字。

例如，对于 $1:03~p.m$，将其转换为 $1303$。

对所有时间都进行以上转化，我们就可以直接考虑通过比较数字的大小来确定时间的先后。具体的来说，该贪心思路就是若当前的时间比前一个时间要早（比如当前是早上而上一个是下午），那么就将 $ans+1$，这样可以保证答案最优。

需要注意的是，由于题目总说了一分钟以内的时间最多出现 $10$ 次，因此若一个时刻连续出现多次，就要通过判断其具体出现了多少次来判断覆盖的天数。

思路都很简单，接下来就是模拟了，本人蒟蒻，被有关 $12:00p.m$ 的处理坑了很久，这里留下一点提示给需要的人吧：要将 $12:00p.m$ 视作第二天的起点而不是这一天的终点，因此应该压缩为 $0$。

## CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[110],ans=1;
string s;
int num(string x)
{
	int m=0;
	for(int i=0;i<x.size()-1;i++)
	{
		if(x[i]>='0'&&x[i]<='9')
		{
			m=m*10+x[i]-'0';
			continue;
		}
	}
	if(x[x.size()-1]=='p'&&(x[0]!='1'||x[1]!='2')) m+=1200;
	if(x[x.size()-1]=='a'&&(x[0]=='1'&&x[1]=='2')) m-=1200;
	return m;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	n++;
	for(int i=1;i<=n;i++)
	{
		getline(cin,s);
		string ff;
		for(int j=1;j<=7;j++) if(s[j]!=' ') ff=ff+s[j];
		a[i]=num(ff);
	}
	int sum=1;
	for(int i=2;i<=n;i++)
	{
		if(a[i]!=a[i-1]) sum=1;
		if(a[i-1]>a[i]) ans++;
		if(a[i]==a[i-1]) sum++;
		if(sum>10) sum=1,ans++;
	}
	cout<<ans;
	return 0;
}
```




---

