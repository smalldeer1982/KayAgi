# Harry Potter and the History of Magic

## 题目描述

The History of Magic is perhaps the most boring subject in the Hogwarts school of Witchcraft and Wizardry. Harry Potter is usually asleep during history lessons, and his magical quill writes the lectures for him. Professor Binns, the history of magic teacher, lectures in such a boring and monotonous voice, that he has a soporific effect even on the quill. That's why the quill often makes mistakes, especially in dates.

So, at the end of the semester Professor Binns decided to collect the students' parchments with notes and check them. Ron Weasley is in a panic: Harry's notes may contain errors, but at least he has some notes, whereas Ron does not have any. Ronald also has been sleeping during the lectures and his quill had been eaten by his rat Scabbers. Hermione Granger refused to give Ron her notes, because, in her opinion, everyone should learn on their own. Therefore, Ron has no choice but to copy Harry's notes.

Due to the quill's errors Harry's dates are absolutely confused: the years of goblin rebellions and other important events for the wizarding world do not follow in order, and sometimes even dates from the future occur. Now Ron wants to change some of the digits while he copies the notes so that the dates were in the chronological (i.e. non-decreasing) order and so that the notes did not have any dates strictly later than $ 2011 $ , or strictly before than $ 1000 $ . To make the resulting sequence as close as possible to the one dictated by Professor Binns, Ron will change no more than one digit in each date into other digit. Help him do it.

## 样例 #1

### 输入

```
3
1875
1936
1721
```

### 输出

```
1835
1836
1921
```

## 样例 #2

### 输入

```
4
9999
2000
3000
3011
```

### 输出

```
1999
2000
2000
2011
```

## 样例 #3

### 输入

```
3
1999
5055
2000
```

### 输出

```
No solution
```

# 题解

## 作者：xiaoyuchenp (赞：3)

这道题最方便的做法，是使用**字符串**。

**数学模型**

给定一个均为四位数的数列 $(y_1,y_2...y_n)$ ,更改其中某些数的一位数字，使该数列不下降并且数列中的任意元素 $y_i$ 满足 $1000 \le y_i \le 2011$ 。

**思路**

很惊讶题解中只有小部分题解使用了 $\texttt{string}$ 这一数据类型。因为此题涉及到某一数位上的修改，因此 $\texttt{string}$ 数据类型肯定优于 $\texttt{int}$ 数据类型。加上 $\texttt{string}$ 类可以方便判断大小，所以能让代码更简洁。

确定了题目所用的数据类型，我们再来构想本题的主要思路。首先，我们可以用到一个小小的**贪心算法**。即将数列的前面一位修改得越小越好，这样让下一位的的取值范围更大，更方便判断无解的情况。

我们可以自定义一个 $\texttt{string returnmin(string a,string b)}$ 函数返回 $\texttt{b}$ 在 $\geq$ $\texttt{a}$ 情况下的最小取值。然后遍历数列枚举判断即可，若 $y_n \geq 2012$，则判定为无解，输出 ```No solution``` 。

**代码（仅供参考）**

```cpp
#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
int n;
string y[MAXN];

string returnmin(string a,string b){//返回最小值函数
    string ans="2012";
    for(int i=0;i<4;i++){
        for(int j=0;j<=9;j++){//暴力枚举所有情况，打擂台取最小值
            string tmp=b;tmp[i]=j+48;
            if(tmp>=a)ans=min(tmp,ans);
        }
    }
    return ans;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>y[i];
    y[0]="1000";//灵活处理，为了方便y[1]的取值
    for(int i=1;i<=n;i++)
        y[i]=returnmin(y[i-1],y[i]);
    if(y[n]>"2011")cout<<"No solution";//无解
    else for(int i=1;i<=n;i++)cout<<y[i]<<'\n';
    return 0;//好习惯（部分编译器没有会爆CE）
}
```

---

## 作者：LKY928261 (赞：2)

看到别的题解没有用字符串做的，就来写一篇。

## 大致题意

给你 $n$ 个四位数 $y_{1\dots n}$。需要更改其中一些数的任意**一位**数字，使序列不下降且 $\forall i\in [1\dots n],1000\le y_i\le 2011$ 。

其中 $1\le n\le 1000,1000\le y_i\le 9999$。

## 题目分析

若从前往后枚举，由于每个 $y_i$ 所能取的值都与 $y_{i-1}$ 的取值有关，所以前面的 $y_i$ 越小越好，这样才能使后面的数取值范围更大。（即贪心）

对于每个 $y_i$ ，在确定了前面的 $y_{i-1}$ 的状态下，暴力枚举所有可能的更改后的值，取满足 $y_i\ge y_{i-1}$ 的所有 $y_i$ 中的最小值即可。

因为 $y_1$ 有且仅有 $y_1\ge 1000$ 这一个限制，我们可以假定 $y_0=1000$ ，再用一般情况的处理方法做。~~（什么？你问我这有什么用？当然是减少代码量喽！）~~

而代码中需要修改数字的数位，如果用 $\texttt{int}$ 存储数据，代码会比较繁琐。考虑到题目和代码中涉及到的数都是四位数，数字位数相同，因此可以用 $\texttt{string}$ 来存储数据，这样修改数位和比较大小都很方便。

## 参考代码

代码仅供参考。

~~请不要在意我独特的码风。。。~~

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,i,j,g;string a[1005],k,t;
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n;a[0]="1000";
	for(i=1;i<=n;i++){
		cin>>a[i];k="2012";
		for(j=0;j<4;j++)for(g=0;g<=9;g++){//暴力枚举
			t=a[i];t[j]=g+48;//修改数位
			if(t>=a[i-1])k=min(k,t);//判断+取最小
		}
		if(k>"2011"){cout<<"No solution\n";return 0;}//判断是否超过2011
		a[i]=k;
	}
	for(i=1;i<=n;i++)cout<<a[i]<<"\n";
}
```

---

## 作者：李至擎 (赞：1)

[点我看题](https://www.luogu.com.cn/problem/CF65B)

题意：改变年份中的一位数字，使所有年份升序排列，且所有年份 $x$ 均满足 $1000 \le x \le 2011$ 。

思路&方法：每次修改时，分别对每一位进行尝试，最后将其修改成最小的符合条件的年份（因为这样可以使得后面的年份有更大的范围进行修改）。

细节：

- 1.最高位千位在修改时不能改成 $0$ ；

- 2.不能边输入边输出。因为，如果进行到其中的某个年份时，我们无法通过修改某一位使其符合要求，那么我们就要输出无解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,la,Ans[1005];//n如题意，x是输入的每个年份，la是上一个年份，Ans是储存答案的数组 
int main()
{
	cin>>n;
	for(int k=1;k<=n;k++)
	{
		cin>>x;
		int a,b,c,d,ok=0,ans=1e9;//a、b、c和d是年份的千百十个位，okans 
		d=x%10;
		x/=10;
		c=x%10;
		x/=10;
		b=x%10;
		x/=10;
		a=x%10;
		for(int i=0;i<=9;i++)
		{
			int y=a*1000+b*100+c*10+i;
			if(y>=la&&y>=1000&&y<=2011)
			{
				ans=min(ans,y);
				ok=1;
			}
		}
		for(int i=0;i<=9;i++)
		{
			int y=a*1000+b*100+i*10+d;
			if(y>=la&&y>=1000&&y<=2011)
			{
				ans=min(ans,y);
				ok=1;
			}
		}
		for(int i=0;i<=9;i++)
		{
			int y=a*1000+i*100+c*10+d;
			if(y>=la&&y>=1000&&y<=2011)
			{
				ans=min(ans,y);
				ok=1;
			}
		}
		for(int i=1;i<=9;i++)
		{
			int y=i*1000+b*100+c*10+d;
			if(y>=la&&y>=1000&&y<=2011)
			{
				ans=min(ans,y);
				ok=1;
			}
		}
		if(!ok)
		{
			cout<<"No solution\n";
			return 0;
		}
		else Ans[k]=la=ans;
	}
	for(int i=1;i<=n;i++)
	{
		cout<<Ans[i]<<endl;
	}
	return 0;
}
```

---

## 作者：ztxtjz (赞：1)

# 【题意】
改变年份中的一位数字，使所有年份升序排列，且年份在[1000,2011]内。
# 【思路】
### 贪心
将前面的年份修改为最小的符合条件的年份，使得后面的年份有更大的范围进行修改。
### 暴力
①从千位到个位，将当前位置上的数不断减一，若符合条件则更新。

②从个位到千位，将当前位置上的数不断加一，若符合条件则更新。

③若没有更新，输出“No solution”。

# 【代码】
```cpp
#include <cstdio>
int n,a[1005],k[5]={0,1,10,100,1000};
bool deal(int s)
{
	for(int w=4;w;w--) //操作①
	{
		for(int j=(a[s]/k[w])%10;j;j--)
		{
			int t=a[s]-k[w]*j;
			if(t>=1000&&t<=2011&&t>=a[s-1])
			{
				a[s]=t;
				return 1;
			}
		}
	}
	for(int w=1;w<=4;w++)  //操作②
	{
		for(int j=0;j<=9-(a[s]/k[w])%10;j++)
		{
			int t=a[s]+k[w]*j;
			if(t>=1000&&t<=2011&&t>=a[s-1])
			{
				a[s]=t;
				return 1;
			}
		}
	}
	return 0;  //操作③
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(!deal(i))
		{
			printf("No solution");
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
		printf("%d\n",a[i]);
	return 0;
}
```

---

## 作者：ZKqwq (赞：0)

题意大概是这样的：给你 $n$ 个数保证每个数大于 $1000$ 并且小于 $2011$。你可以改变 $z_i$ 之间的任意一位数，使它们变成升序数列。如果不可以，那么输出 `No solution`。

已知数据范围 $1$ $≤$ $n$ $≤$ $1000$ ，大模拟可以考虑。我们需要把每一个 $z_i$ 尽可能改为大于等于上一个数并且满足数据要求的数。边运行边输出？不可以！总司令。

那么如何实现呢？考虑从 $0$ 到 $9$ 模拟，用一个变量记录更改的数位所改得数。注意，只有个位、十位、百位、千位四个数位。可能会有一些取整。

Code：

```cpp
/*
Code By Modern_Deer And Alano_ZK.
Solution By Modern_Deer
By C++14(GCC 9)   On 2023/2/19.
*/
#include<bits/stdc++.h>
using namespace std;
int n,x,last,Ans[1005];//n如题意，x是输入的每个年份，last是上一年.
int main()
{
	cin>>n;
	for(int k=1;k<=n;k++)
	{
		cin>>x;//输入
		int a,b,c,d,ok=0,ans=1e9;//a、b、c和d是年份的千百十个位
		d=x%10;//简单的取模算个十百千位方法，在此不做赘述。
		x/=10;
		c=x%10;
		x/=10;
		b=x%10;
		x/=10;
		a=x%10;
		for(int i=0;i<=9;i++)//模拟枚举每个数字
		{
			int y=a*1000+b*100+c*10+i;//再把这个四位数还原回来，位置原理
			if(y>=last&&y>=1000&&y<=2011)
			{
				ans=min(ans,y);
				ok=1;
			}
		}
		for(int i=0;i<=9;i++)
		{
			int y=a*1000+b*100+i*10+d;//继续模拟枚举
			if(y>=last&&y>=1000&&y<=2011)//如果满足条件
			{
				ans=min(ans,y);//求最小值
				ok=1;
			}
		}
		for(int i=0;i<=9;i++)
		{
			int y=a*1000+i*100+c*10+d;
			if(y>=la&&y>=1000&&y<=2011)
			{
				ans=min(ans,y);
				ok=1;
			}
		}
		for(int i=1;i<=9;i++)
		{
			int y=i*1000+b*100+c*10+d;
			if(y>=la&&y>=1000&&y<=2011)
			{
				ans=min(ans,y);
				ok=1;
			}
		}
		if(!ok)//如果无法满足条件
		{
			cout<<"No solution"<<endl;//换行。。。
			return 0;
		}
		else Ans[k]=la=ans;//存个答案吧，记住，不要直接输出。
	}
	for(int i=1;i<=n;i++)
	{
		cout<<Ans[i]<<endl;//直接输出
	}
	return 0;
}
```

---

## 作者：Lyrella (赞：0)

# 题意

你可以修改以下 $n$ 个数的其中一位，使：

- 数列非严格单调递增 $(a_{i-1}\leq a_i)$。

- $1000\leq a_1$ 且 $a_n\leq 2011$。

# 思路

因为 $n\leq 1000$ 且数列 $a$ 都为四位数，所以直接**暴力**枚举数列 $1$ 到 $n$ 的每一位，每次枚举取合法最小值（最小值一定最优）。

**时间复杂度** $\Theta(40\times n)$。

# 注意

- **强烈推荐** $string$。

- **强烈推荐预处理** $a_0=1000$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1005;
int n;
string a[N];
signed main()
{
	cin >> n;
	a[0] = "1000";
	for(int i = 1; i <= n; i++)cin >> a[i];
	for(int i = 1; i <= n; i++)
	{
		string ch, mi = "9999";
		for(int j = 0; j < 4; j++)
		for(int k = 0; k < 10; k++)
		{
			ch = a[i];
			ch[j] = k + '0';
			if(ch >= a[i - 1])mi = min(ch, mi);
		}
		if(mi > "2011")
		{
			puts("No solution");
			return 0;
		}
		a[i] = mi;
	}
	for(int i = 1; i <= n; i++)cout << a[i] << endl;
	return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给你 $n$ 个年份 $x_{1...n}$.

请你更改一些数字，使年份按时间顺序（即非递减）排列，以使其中没有任何日期晚于 $2011$ 或早于 $1000$.

在每个日期中最多只能将一位数字改成别的数字.
$1\le n\le10000,1000\le x_i\le9999$.
## $\text{Solution}$
不难发现贪心策略，使前面的年份尽可能的小，一定是不劣的.  
分情况讨论，如果大于前一项，从高位开始尝试往低改；如果小于前一项，就从低位开始尝试往高改即可.  
最后判一下是否超过 $2011$.  
实现上，有一些上下取整的细节，但整体还不算太恶心.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=4e5+100;
const int mod=998244353;
//char buf[1<<23],*p1=buf,*p2=buf,obuf[1<<23],*O=obuf;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
int a[1050],mi[5]={1,10,100,1000,10000};
inline int f(int x,int pos){
  return x%mi[pos+1]/mi[pos];
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  for(int i=1;i<=n;i++) a[i]=read();
  a[0]=1000;
  for(int i=1;i<=n;i++){
    if(a[i]>=a[i-1]){
      int d=a[i]-a[i-1];
      for(int k=3;k>=0;k--){
	int o=f(a[i],k);
	if(!o||d<mi[k]) continue;
	a[i]-=min(d/mi[k]*mi[k],o*mi[k]);break;
      }
    }
    else{
      int d=a[i-1]-a[i];
      for(int k=0;k<=3;k++){
	int o=9-f(a[i],k);
	if(o*mi[k]<d) continue;
	a[i]+=(d+mi[k]-1)/mi[k]*mi[k];
	//printf("k=%d o=%d d=%d add=%d\n",k,o,d,(d+mi[k]-1)/mi[k]);
	break;
      }
    }
    //printf("%d\n",a[i]);
    if(a[i]<a[i-1]){
      printf("No solution");return 0;
    }
  }
  if(a[n]>2011) printf("No solution");
  else{
    for(int i=1;i<=n;i++) printf("%d\n",a[i]);
  }
}
/*
*/

```


---

## 作者：Nt_Tsumiki (赞：0)

### 题意
[题目传送门](https://www.luogu.com.cn/problem/CF65B)

给你 $n$ 个数保证每个数 $1000\leq z_i \leq 2011$，现在，你可以改变每个 $z_i$ 中的任意一位数，使他们变为升序序列，求改完后的升序序列。

如没有更改操作，输出 ```No solution```。

### 做法
数据范围 $1 \leq n \leq 1000$，很明显大模拟能过，所以我们考虑贪心。

#### 算法构造
我们可以把每一个 $z_i$ 改为在 $[1000,2011]$ 范围内大于等于 $z_{i-1}$ 的最小的数，即可求得结果。

注意不能边运行边输出。

#### 算法实现
写一个函数，里面把 $i$ 从 $0$ 到 $9$ 模拟一遍，其中 $i$ 为当前更改的数位（个位，十位，百位，千位）上所改为的数。

### Code
```cpp
#include <iostream>
#include <string>

using namespace std;
int n,last,ans[100001];

bool work(int t1,int t2,int t3,int t4) {
    int ans=1e9;
    bool b=0;
    for (int i=0;i<=9;i++) {//大模拟
        int tmp=t1*1000+t2*100+t3*10+i;
        if (tmp>=last and tmp>=1000 and tmp<=2011)//个位
            ans=min(ans,tmp),b=1;
        tmp=t1*1000+t2*100+i*10+t4;
        if (tmp>=last and tmp>=1000 and tmp<=2011)//十位
            ans=min(ans,tmp),b=1;
        tmp=t1*1000+i*100+t3*10+t4;
        if (tmp>=last and tmp>=1000 and tmp<=2011)//百位
            ans=min(ans,tmp),b=1;
        tmp=i*1000+t2*100+t3*10+t4;
        if (i!=0 and tmp>=last and tmp>=1000 and tmp<=2011)//千位
            ans=min(ans,tmp),b=1;
    }
    last=ans;
    return b;
}

int main() {
    cin>>n;
    for (int i=1;i<=n;i++) {
        string s;//输入字符串更好转换
        cin>>s;
        int t1=s[0]-'0',t2=s[1]-'0',t3=s[2]-'0',t4=s[3]-'0';
        if (!work(t1,t2,t3,t4)) {//判断是否无操作
            cout<<"No solution";
            return 0;
        }
        ans[i]=last;//储存答案
    }
    for (int i=1;i<=n;i++) cout<<ans[i]<<endl;//输出答案
    return 0;
}
```

---

