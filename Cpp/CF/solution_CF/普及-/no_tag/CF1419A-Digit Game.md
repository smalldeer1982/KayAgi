# Digit Game

## 题目描述

Everyone knows that agents in Valorant decide, who will play as attackers, and who will play as defenders. To do that Raze and Breach decided to play $ t $ matches of a digit game...

In each of $ t $ matches of the digit game, a positive integer is generated. It consists of $ n $ digits. The digits of this integer are numerated from $ 1 $ to $ n $ from the highest-order digit to the lowest-order digit. After this integer is announced, the match starts.

Agents play in turns. Raze starts. In one turn an agent can choose any unmarked digit and mark it. Raze can choose digits on odd positions, but can not choose digits on even positions. Breach can choose digits on even positions, but can not choose digits on odd positions. The match ends, when there is only one unmarked digit left. If the single last digit is odd, then Raze wins, else Breach wins.

It can be proved, that before the end of the match (for every initial integer with $ n $ digits) each agent has an ability to make a turn, i.e. there is at least one unmarked digit, that stands on a position of required parity.

For each of $ t $ matches find out, which agent wins, if both of them want to win and play optimally.

## 说明/提示

In the first match no one can make a turn, the only digit left is $ 2 $ , it's even, so Breach wins.

In the second match the only digit left is $ 3 $ , it's odd, so Raze wins.

In the third match Raze can mark the last digit, after that Breach can only mark $ 0 $ . $ 1 $ will be the last digit left, it's odd, so Raze wins.

In the fourth match no matter how Raze plays, Breach can mark $ 9 $ , and in the end there will be digit $ 0 $ . It's even, so Breach wins.

## 样例 #1

### 输入

```
4
1
2
1
3
3
102
4
2069```

### 输出

```
2
1
1
2```

# 题解

## 作者：Constant (赞：5)

# 题意简述：

给定一个长度为 $N$ 的数字，Raze只能选择奇数位上的数标记， Breach只能选择偶数位上的数标记，这样依次轮流标记，Raze先开始，最后剩下的数是奇数，Raze获胜，反之亦然，两人都按照最优策略进行游戏，问哪一方会获胜。

# Solution：

两人都按照最优策略，所以两人一定会减少自己所能标记的，对自己不利的数的个数。

Raze一定会先标记奇数位的偶数。Breath一定会先标记偶数位的奇数。

在这个策略下，统计数字串中奇数位上的奇数个数 $s1$ 和偶数位上的偶数个数 $s2$ ，判断即可。

如果 $N$ 为奇数，则最后剩下的一定是奇数位上的某个数，判断奇数位上是否存在奇数，即 $s1$ 是否大于等于 $1$ 即可，如果存在，那么Raze必胜。

如果 $N$ 为偶数，则最后剩下的一定是偶数位上的某个数，判断偶数位上是否存在偶数，即 $s2$ 是否大于等于 $1$ 即可，如果存在，那么Breath必胜。

时间复杂度 $O(TN)$。

下面是我的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[2005];
int n,t,s1,s2; 
int main()
{
    scanf("%d",&t);
    while(t--)
    {
    	scanf("%d",&n);
    	scanf("%s",a+1);
    	s1=0;
    	s2=0;
    	for(int i=1;i<=n;i++)
    	{
    		if(i%2==1)
    		{
    			if(int(a[i]-'0')%2==1) s1++;
			}
			else
			{
				if(int(a[i]-'0')%2==0) s2++;
			}
		}
		if(n%2==0)
		{
			if(s2>=1) printf("2\n");
			else printf("1\n");
		}
		else
		{
			if(s1>=1) printf("1\n");
			else printf("2\n");
		}
	}
    return 0;
} 
```




---

## 作者：Night_sea_64 (赞：2)

一道字符串和博弈论的简单题。

我们先来看看样例。前两组数据太简单，重点来分析一下后两组数据。

设这个长度为 $n$ 的数为 $x$。第三组数据，$x=102$。很显然 A 会操作 $1$ 次，B 也会操作 $1$ 次。偶数位的数只有一个，所以 B 没得挑，只能把 $0$ 标记上。可是奇数位的数有 $2$ 个，所以 A 可以选择其中一个标记上。A 肯定会选择把 $2$ 标记上，留下 $1$。所以 A 会胜利。

第四组数据，$x=2069$。A 操作 $2$ 次，B 操作 $1$ 次。这回轮到 A 没有选择了，B 可以选择一个偶数位的数字留下。于是 A 把奇数位的数字全部标记，B 标记 $9$，把 $0$ 留下。所以 B 会胜利。

有兴趣的话可以再选几个数试一试。我们就能发现，如果长度是奇数的话，B 一定没得选，A 可以选择留下一个数字。反之 A 没得选，B 可以选择留下一个数字。

然后我们分类讨论就行了，找出能选择留下一个数字的那个人，能不能留下一个数字让自己胜利。如果不能，则对方胜利。

#### AC Code:

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        string s;
        cin>>n>>s;
        int a=s.size()/2,b=s.size()-1-a;
        if(s.size()%2)//长度是奇数，A 能留下一个数字。
        {
            bool flag=0;
            for(int i=0;i<s.size();i+=2)
                if((s[i]-'0')%2)flag=1;
            //如果奇数位的数字中存在奇数，则 A 胜利。
            //如果奇数位的数字全是偶数，则 B 胜利。
            if(flag)cout<<1<<endl;
            else cout<<2<<endl;
        }
        else //长度是偶数，B 能留下一个数字。
        {
            bool flag=0;
            for(int i=1;i<s.size();i+=2)
                if((s[i]-'0')%2==0)flag=1;
            //如果偶数位的数字中存在偶数，则 B 胜利。
            //如果偶数位的数字全是奇数，则 A 胜利。
            if(flag)cout<<2<<endl;
            else cout<<1<<endl;
        }
    }
    return 0;
}
```

---

## 作者：冰糖鸽子 (赞：2)

#### 前言

这题考场上想复杂了，打了十几分钟/kk

还有翻译咋不翻译输入格式啊，只看样例完全不好懂

#### 思路

 首先，有两种情况：
 
 - $x$ 个偶数位，$x+1$ 个奇数位
 
 - $x$ 个偶数位，$x$ 个奇数位
 
 （不会出现 $x$ 个偶数位，$x-1$ 个奇数位的情况，因为一个偶数位必定对应一个奇数位，反之则不然 ）
 
 其次，由于最后剩下的一个数保留 $&&$ 先标记奇数位，所以上面两种情况分别对应了两种情况：
 
 - 剩一个奇数位，也就是偶数位都没有用了（偶数位：我不要面子的吗？？）（判断获胜为下文获胜条件①）
 
 - 剩一个偶数位，也就是奇数位都没有用了（奇数位：我也不要面子的吗？）（判断获胜为下文获胜条件②）
 
 最后，由于 A 和 B  都采取了最佳选择，所以获胜条件为：①只要奇数位上有一个奇数，则 A 获胜，反之 B 获胜 ② 只要偶数位上有一个偶数，则 B 获胜，反之 A 获胜
 
 代码就很好写了
 
 #### 代码
 
 ```
 #include <bits/stdc++.h>
using namespace std;
int t,f,os,js,sl;
string s;
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> f >> s;
		os=js=0;
		for(int i = 0;i < f;i++)
		{
			if(i%2==1)
			{
				if((s[i]-'0')%2==0)
				{
					os=1;
				}
			}
			else
			{
				if((s[i]-'0')%2==1)
				{
					js=1;
				}
			}
		}
		if(f%2==0)
		{
			cout << (os?2:1) << endl;
		}
		else
		{
			cout << (js?1:2) << endl;
		}
	}
	return 0;
}
 ```
 
 ----
 
 [AC记录](https://www.luogu.com.cn/record/39003130)

---

## 作者：pigstd (赞：1)

~~为啥这题要模拟啊~~

首先我们发现，能否赢只和最后剩下的一位数有关，最后剩下的一位数的位置的奇偶性是和$n$有关的

直接分类讨论：

1.如果$n$是偶数，那么显然最后一个数会在偶数位中，那么如果偶数位中有偶数，那么 Breach 一定能赢：只要留下这个偶数就行，所以输出$2$，否则输出$1$

2.如果$n$是奇数，那么显然最后一个数会在奇数位中。如果奇数位中有奇数，那么 Raze 一定能赢：留下这个奇数就行，输出$1$，否则输出$2$

代码就不贴了，时间复杂度$O(n \times T)$，能过

---

## 作者：jun头吉吉 (赞：1)

## 题意

有一个长为$n$的数字，从高位到低位分别为$1,2,\ldots,n$。小R和小B轮流标记数，小R只能标记奇数位上的数字，小B能标记偶数位上的数字，不能重复标记。当只剩下奇数时，小R获胜，否则小B获胜

小R胜输出1，小B胜输出2(两位选手都十分聪明)

## 题解
加入你是小R，那么你的目标就是让偶数尽可能少。因此你先标记的必定是能标记偶数，再标记奇数。小B也是同理。

那么我们只需要写个程序模拟就行了
## ~~送我fst的~~代码
```cpp
#include<bits/stdc++.h>
namespace in{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline int getc(){
	    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
	}
	template <typename T>inline void read(T& t){
	    t=0;int f=0;char ch=getc();
	    while (!isdigit(ch)){
	        if(ch=='-')f = 1;
	        ch=getc();
	    }
	    while(isdigit(ch)){
   	    	t=t*10+ch-48;
   	    	ch = getc();
   		}
		if(f)t=-t;
	}
	template <typename T,typename... Args> inline void read(T& t, Args&... args){
	    read(t);read(args...);
	}
	char getdigit(){
		char c=getc();
		while(!isdigit(c))c=getc();
		return c;
	}
}
namespace out{
	char buffer[1<<21];
	int p1=-1;
	const int p2 = (1<<21)-1;
	inline void flush() {
		fwrite(buffer,1,p1+1,stdout),
		p1=-1;
	}
	inline void putc(const char &x) {
		if(p1==p2)flush();
		buffer[++p1]=x;
	}
	template <typename T>void write(T x) {
		static char buf[15];
		static int len=-1;
		if(x>=0){
			do{
    			buf[++len]=x%10+48,x/=10;
    		}while (x);
		}else{
    		putc('-');
			do {
    			buf[++len]=-(x%10)+48,x/=10;
			}while(x);
		}
		while (len>=0)
			putc(buf[len]),--len;
	}
}
using namespace std;
int t,n,a,N[2][2]; 
signed main(){
	in::read(t);
	while(t--){
		in::read(n);N[0][0]=N[0][1]=N[1][0]=N[1][1]=0;
		for(int i=1;i<=n;i++)
			N[i%2][(in::getdigit()-'0')%2]++;
		//2 B取偶数位  有偶数胜
		//1 R取奇数位  有奇数胜
			if((N[1][1]+N[0][1])==0&&(N[1][0]+N[0][0]!=0)){puts("2");goto loop;}
			if((N[1][1]+N[0][1])!=0&&(N[1][0]+N[0][0]==0)){puts("1");goto loop;}
		while((N[0][0]+N[0][1]!=0)&&(N[1][1]+N[1][0]!=0)){
			if(N[1][0])N[1][0]--;
			else N[1][1]--;
			if((N[1][1]+N[0][1])==0&&(N[1][0]+N[0][0]!=0)){puts("2");break;}
			if((N[1][1]+N[0][1])!=0&&(N[1][0]+N[0][0]==0)){puts("1");break;}
			if(N[0][1])N[0][1]--;
			else N[0][0]--;
			if((N[1][1]+N[0][1])==0&&(N[1][0]+N[0][0]!=0)){puts("2");break;}
			if((N[1][1]+N[0][1])!=0&&(N[1][0]+N[0][0]==0)){puts("1");break;}
			
		}loop:;
	}
	out::flush();
	return 0;
}
```


---

## 作者：PeaceSunset (赞：0)

这题是一道非常入门的**博弈论**。
#### 思路：
因为 $A$ 获胜的条件是剩下的是奇数，且 $A$ 只能标记奇数位上的数，所以 $A$ 要尽可能地标记奇数位上的偶数。

而 $B$ 获胜的条件是剩下的是偶数，且 $B$ 只能标记偶数位上的数，所以 $B$ 要尽可能地标记偶数位上的奇数。

那我们设 $ji$ 记录奇数位上的偶数的数量，$ou$ 记录偶数位上奇数的数量。

最后当位数为奇数时，只要 $ou$ 大于零，$B$ 就赢了，反之 $A$ 就赢了。

如果位数是偶数，只要 $ji$ 大于零，$A$ 就赢了，反之 $B$ 就赢了。

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,ji,ou;
char a[2010];
int main(){
    cin>>t;
    while(t--){
    	cin>>n;
    	cin>>a+1;
    	ji=ou=0;
    	for(int i=1;i<=n;i++){
    		if(i%2==1){
    			if(int(a[i]-'0')%2==1)ji++;
			}
			else{
				if(int(a[i]-'0')%2==0)ou++;
			}
		}
		if(!n%2){
			if(ou>=1)cout<<"2\n";
			else cout<<"1\n";
		}
		else{
			if(ji>=1)cout<<"1\n";
			else cout<<"2\n";
		}
	}
    return 0;
} 
```


---

## 作者：Forever1507 (赞：0)

既然说两人都会选择最优策略，显然会先划掉不利于自己的数（具体来说，就是 $A$ 会先划掉偶数， $B$ 会先划掉奇数。）

当给定数的位数为奇数时，显然划掉最后一个数的人是 $A$ ,那么只要他所管的数字中有奇数即可获胜。

位数是偶数时也一样，只要看 $B$ 所管的数字中有没有偶数就行了。

时间复杂度为 $O(TN)$ , 在 $1 \le t \le 100$ 且 $1 \le n \le 10^3$ 的情况下时间可以通过。

至于实现方面，对于每一位的处理字符串的表现比 `int` 优秀很多，可以减少码量。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n; 
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n;
		string s;
		cin>>s;
		int num1=0,num2=0;//num1->奇数位上的奇数数量。num2->偶数位上的偶数数量 
		for(int i=0;i<n;i++){
			if((i+1)%2==1&&(s[i]-'0')%2==1)num1++;
			if((i+1)%2==0&&(s[i]-'0')%2==0)num2++;
		}
		if(n%2==0){//归B管
			if(num2>=1){
				cout<<2<<'\n';
			}else cout<<1<<'\n';
			continue;
		}
		else{//归A管
			if(num1>=1){
				cout<<1<<'\n';
			}
			else cout<<2<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：szkzyc (赞：0)

这道题在比赛时算是简单的一种题了，坑也不多，思路也非常好想。

题意就先不说了，翻译已经很清楚了。

这道题的重点就是如何避免暴力枚举，因为对于这道题来说数据范围虽说不是很大，但如果每次查询第 $k$ 大的值也是肯定 TLE 无疑的。

但由于题目条件很特殊，所以根本不用去一个一个排序。

为什么呢？首先，序列里非 $0$ 即 $1$，并且操作只有两个：分别是修改和查询第 $k$ 个最大值

修改很简单，时间复杂度 $O(1)$，但如何将查询的时间复杂度也降到 $O(1)$ 呢？

又有只有 $0$ 和 $1$,所以第 $k$ 个最大值肯定也是 $1$ 或 $0$。

所以只要随时统计与更新目前 $0$ 和 $1$ 的个数就行了。

也就是当 $1$ 的个数大于等于 $k$ 时，就输出 $1$, 否则就输出 $0$。

### 赛时代码（本人AC）

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int c0, c1, a[100005];
int main(){
 
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
    	cin >> a[i];
    	if(a[i] == 1) c1++;
    	else c0++; //统计01个数 
	}
	while(k--){
		int t, x;
		cin >> t >> x;
		if(t == 1){ //如果为1，那么将0变1,1变0，相应的计数器也更新 
			if(a[x] == 1) c1--, c0++, a[x] = 0; 
			else c1++, c0--, a[x] = 1;
		} 
		else{ //如果为2,1计数器大于等于k（我变量名写的x） 的话就输出1，否则输出0 
			if(c1 >= x) cout << 1 << endl;
			else cout << 0 << endl;
		}
	}
	return 0;
}
//在昨天的CF比赛上亲测AC 
```


---

## 作者：daniEl_lElE (赞：0)

一道适合萌新练习题（初学者）。

先判断串长。

若为偶数的话，就在偶数位上找偶数（ ~~听起来好别扭~~ ），如果有，输出$2$，若没有，就输出$1$。

若为奇数的话，就在奇数位上找奇数（ 同上 ），如果有就输出$1$，不然输出$2$。

下为代码：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		string s;
		cin>>s;
		if(s.size()%2==0){
			int mark=0;
			for(int k=1;k<s.size();k+=2){
				if((s[k]-'0')%2==0){
					mark=1;
					break;
				}
			}
			if(mark){
				cout<<2;
			}
			else{
				cout<<1;
			}
		}
		else{
			int mark=0;
			for(int k=0;k<s.size();k+=2){
				if((s[k]-'0')%2==1){
					mark=1;
					break;
				}
			}
			if(mark){
				cout<<1;
			}
			else{
				cout<<2;
			}
		}
		cout<<endl;
	}

	return 0;
}

```
代码也不短，就是一些比较繁琐的结论。

---

## 作者：过往梦魇之殇 (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1419A)

**思路简述：**

考虑到最后判断输赢的是最后一个剩下的数，且剩下的必然是奇数或偶数位的数，

则可讨论：

当$n$是偶数时，最后剩下的必然是偶数位的数。

> 题目中已经给出 **"我们假定两位选手都能做出最佳的选择。"**

> 所以如果偶数位有一个偶数，那么$B$必然不会去选那个偶数而将其他的数选完，则必然$B$赢。

当$n$是奇数时，同理最后剩下的是奇数位的数，且如果奇数位有一个奇数，则$A$必赢。

所以由这个可以判断$A,B$的输赢，且必然不会有其他情况被遗漏。

**代码展示：**

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
int t,n,c1,c2;
string str;
int main(){
	scanf("%d",&t);
	while(t--){
		c1=c2=0;
		scanf("%d",&n);
		cin>>str;
		int len=str.size();
		for(re int i=0;i<len;i+=2){
			if((int)(str[i]-'0')%2){
				++c1;
			}
		}
		for(re int i=1;i<len;i+=2){
			if((int)(str[i]-'0')%2==0){
				++c2;
			}
		}
		if(((n&1)&&c1)||((n%2==0)&&(!c2))){
			puts("1");
		}
		else{
			puts("2");
		}
	}
	return 0;
}
```

> $Thanks$ $For$ $Watching!$

---

## 作者：—维尼— (赞：0)

## 题目简述
给定一个数字串，Raze，Breach两个人都以最优策略进行游戏：两人轮流对该数字串进行标记，Raze只能标记奇数位上的数，Breach只能标记偶数位上的数，如果最后一个没被标记的数字（即最后剩下的数）是奇数，那么Raze胜出，否则Breach胜出

ps:原题中的（make a turn）个人感觉是个多余点，~~垃圾翻译~~可以直接忽略

## 解决方法
可以把数字长度分为奇偶两种情况讨论：

1.1. 如果有奇数个，并且奇数位上至少有一个奇数，因为最后一个数肯定在Raze范围内，所以他肯定可以保证这个数留在最后，所以Raze获胜

1.2. 如果没奇数那当然赢不了啦

2.1 如果有偶数个同理：如果偶数位上至少有一个偶数,那么Breach肯定能用最优策略取胜

2.2 如果没有的话还是只能看着对面赢
代码如下：
```c++
#include<bits/stdc++.h>
using namespace std;
char a[1005];
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
        cin>>a[i];
        int odd=false;
		int even=false;
        for(int i=1;i<=n;++i){
            if (i%2==1&&a[i]%2==1)
            odd++;
			else if(i%2==0&&a[i]%2==0)
            even++;
        }
        if(n%2==1){
        	if(odd)
        	cout<<1<<endl;
			else
			cout<<2<<endl;
		}
        else{
        	if(even)
        	cout<<2<<endl;
        	else
        	cout<<1<<endl;
        }
    }
    return 0;
}


---

## 作者：SSerxhs (赞：0)

当 $n$ 为偶数时，奇数位和偶数位数量相等，由于先标奇数位，最后剩下的一定是偶数位上的数，则只要偶数位出现一个偶数 Breach 就把这个数留到最后就可以了

当 $n$ 为奇数时，最后剩下的一定是奇数位上的数，则只要奇数位出现一个奇数 Raze 就把这个数留到最后就可以了

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e3+2;
int a[N];
int n,c,fh,i,t,cnt;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(t);
	while (t--)
	{
		cnt=0;
		read(n);while ((c<48)||(c>57)) c=getchar();
		a[1]=(c&1);
		for (i=2;i<=n;i++) a[i]=(getchar()&1);
		if (n&1)
		{
			for (i=1;i<=n;i+=2) if (a[i]) break;
			if (i<=n) puts("1"); else puts("2");
		}
		else
		{
			for (i=2;i<=n;i+=2) if (!a[i]) break;
			if (i<=n) puts("2"); else puts("1");
		}
	}
}
```

---

## 作者：幻影星坚强 (赞：0)

如果n为奇数，那么最后一个数肯定是在Raze所取范围内（即为奇数位），偶数位上的数会全部取完。那么如果奇数位上有奇数，那么Raze肯定能够保留这个奇数使他获胜，如果没有奇数那他怎么样也无法获胜。

n为偶数同理。

```
#include <iostream>
#include <cstdio>
using namespace std;
int t;
int n;
char c[100010];
int main()
{
    scanf("%d", &t);
    while(t --)
    {
        scanf("%d", &n);
        scanf("%s", c);
        int fl = 1 + (n & 1);
        for (int i = 2 - (n & 1); i <= n; i += 2)
        {
            if(!((n & 1) ^ (c[i - 1] - '0') & 1))
            {
                fl = 2 - (n & 1);
                break;
            }
        }
        printf("%d\n", fl);
    }
}

```


---

## 作者：ql12345 (赞：0)

### 题意：

t组数据，每组给一个n和一个n位的数字

小A和小B轮流取数字，小A先开始：

小A只能取奇数位上的数字，小B只能取偶数位上的数字（一个数字所在的位数不会变化）

取到最后只剩一个数字结束，剩的是奇数（数值，而不是所在数位），小A赢；偶数，小B赢

### Solution：

- n固定，最后剩下的一位是奇数位还是偶数位就是固定的：

n为奇数：剩下奇数位（奇偶各取了(n-1)/2个）

n为偶数：剩下偶数位（奇取了n/2个，偶取了n/2-1个）

- 剩不下的那位对应的那个人的策略是无用的

显然~

所以可以剩下的那个人；会尽量让剩下的数字是自己能赢的数字

因为对方不能取自己位置上的数字，所以只要有能让自己赢的数字，就能赢

具体而言：

1. n为奇数：小A如果能再奇数位找到奇数，小A赢

1. n为偶数：小B如果能在偶数位找到偶数，小B赢

1. 对方赢不了，自己就赢呗！

### 实现：

- 根据上述第三点：

我们令答案先为对方能赢，之后在扫的时候如果找到自己能赢，就改一下答案，最后输出即可

- scanf("%1d",&c)可以一次输入一个数（不需要遇到空格、换行）

### Code:

```cpp
int t,n,ans;
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		ans=0;
		if(n&1)ans=2;else ans=1;
		for(re int i=1,c;i<=n;++i){
			scanf("%1d",&c);
			if((i&1)&&(c&1)&&(n&1))ans=1;
			if(!(i&1)&&!(c&1)&&!(n&1))ans=2;
		}
		cout<<ans<<endl;
	}
}
```

---

## 作者：onglu (赞：0)

# Codeforces Round #668 (Div. 2)  
## A.Digit Game  
### 题目大意  
A和B进行游戏，给定一列数，每次A可以标记一个没有被标记的奇数位置的数，每次B可以标记一个没有被标记的偶数位置的数。如果最后一个被标记的数是奇数就是A赢否则B赢。  
### 思路  
一眼题，显然如果数是奇数个，最后一个打标记的肯定是A，否则肯定是B。  
然后A可以选择奇数位置的任何一个数做最后一次标记，B亦然。  
于是就讨论就行了。  
* 假如有奇数个：  
1.  假如奇数位置存在奇数，则A必胜。  
2.  假如奇数位置不存在奇数，则A必输。   
* 假如有偶数个：  
1.  假如偶数位置存在偶数，则B必胜。  
2.  假如偶数位置不存在偶数，则B必输。  

### 代码  
```cpp
#include <bits/stdc++.h>
#define Mid ((l + r) >> 1)
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define ll long long
#define ull unsigned long long
#define FILL ""
using namespace std;
const int N = 0, M = 0;
int read(){
	char c; int num, f = 1;
	while(c = getchar(),!isdigit(c)) if(c == '-')f = -1; num = c - '0';
	while(c = getchar(), isdigit(c)) num = num * 10 + c - '0';
	return num * f;
}
int n, a[1009], f[2][2];
void work(){
	memset(f, 0, sizeof(f));
	char c;
	n = read();
	for(int i = 1; i <= n; i++){
		scanf("%c", &c);
		a[i] = c - '0';
		f[i & 1][a[i] & 1] = 1;
	}
	if(n & 1){
		printf("%d\n", f[1][1] ? 1 : 2);
	}else {
		printf("%d\n", f[0][0] ? 2 : 1);
	}
}
int main()
{
	int Case = read();
	while(Case--)work();
	return 0;
}
```

---

## 作者：Ryo_Yamada (赞：0)


上来一个 A 就是博弈论，没想到没想到。当时先开的 D1。而且还有好多人 FST 是什么鬼啊。

若 $n$ 为奇数且所有奇数位上的数都是偶数则输出 $2$，否则输出 $1$。

$n$ 为偶数同理，若所有偶数位上的数都是奇数则输出 $1$，否则输出 $2$。

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

bool flag1, flag2;

int main() {
	int T;
	cin >> T;
	while(T--) {
		flag1 = flag2 = true;
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) {
			int k;
			scanf("%1d", &k);
			if((k & 1) && (i & 1)) flag1 = false;
			if((k & 1) == 0 && (i & 1) == 0) flag2 = false;
		}
		if(n & 1) flag1 ? puts("2") : puts("1");
		else flag2 ? puts("1") : puts("2");
	}
	return 0;
}

```


---

