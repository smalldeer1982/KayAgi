# The Time

## 题目描述

You are given the current time in $ 24 $ -hour format hh:mm. Find and print the time after $ a $ minutes.

Note that you should find only the time after $ a $ minutes, see the examples to clarify the problem statement.

You can read more about $ 24 $ -hour format here [https://en.wikipedia.org/wiki/24-hour\_clock](https://en.wikipedia.org/wiki/24-hour_clock).

## 样例 #1

### 输入

```
23:59
10
```

### 输出

```
00:09
```

## 样例 #2

### 输入

```
20:20
121
```

### 输出

```
22:21
```

## 样例 #3

### 输入

```
10:10
0
```

### 输出

```
10:10
```

# 题解

## 作者：xzllll07 (赞：2)

我们要解决的问题有这些：

	1.如何输入并分离时与分？
   	2.处理跨天、跨小时？
    3.如何控制输出前导 0？
    
第一个问题，本蒟蒻的思路很简单：

由于输入格式一定是 hh:mm，所以直接输入五个字符，再转化为两个整数即可。思路：

	输入5个字符 a,b,c,d,e。
    小时=(a-'0')*10+(b-'0')  
    分钟=(d-'0')*10+(e-'0')


写成代码就是：
```cpp
void in()
{
    a=getchar(),b=getchar(),c=getchar(),d=getchar(),e=getchar();
    hour=(a-'0')*10+(b-'0');
    min=(d-'0')*10+(e-'0');
}
```
那我们再来看第二个问题：

众所周知，60 分钟为 1 小时，24 小时为 1 天（废话）。

也就是说，如果分钟数超过了 60，将它对 60 取余即可。（记得向小时进位）

同样的，如果小时数超过了 24，就将它对 24 取余。

代码如下：

```cpp
void calc()
{
    scanf("%d",&n);//输入经过的分钟数
    min+=n;
    hour+=(min/60);
    min%=60;
    hour%=24;
}

```
第三个问题就更简单了，只需要判断一下，如果小时、分钟数 $<$ 10，就在数值前输出一个 0。

代码如下：

```cpp
void out()
{
    if (hour<10) printf("0");
    printf("%d:",hour);
    if (min<10) printf("0");
    printf("%d",min);
}

```

至此为止，所有步骤就已经全部写完了，我们还需要一个主函数。

```cpp
int main()
{	
    in();
    calc(); 
    out();
    return 0;
}

```
这样就完成啦 (＾－＾)V



---

## 作者：UKE自动稽 (赞：2)

水题一道

思路，看看n里有几个小时，几分钟，小时%24，防止过n分钟后是下一天。

  $\color{black} \text{}  \colorbox{black}{PS:程序依然有语法错误，想复制的，一定会CE哦！}$  

```
#include<iostream>
using namespace std;
int main()
{
    int h, m;
    scanf("%d:%d", &h,&m);
    int n;
    scanf("%d",&n);
    m += n; h += m / 60;  //进位
    h %= 24;//取模，防止n分钟后就是第二天
    m %= 60;//取模，算出n分钟后是几分
    printf("%02d:%02d\n", h, m);
    return 0;
}
```

---

## 作者：Franka (赞：1)

~~迷你时钟好评。~~
### **题目**
给出一个时间（$24$进制），求它经过$a$分钟后的时间。
### **思路**
先将时和分都分离出来，其次将a分钟加到分里，处理进位，最后将时$\bmod$ $24$即可。
### **代码**
```pascal
var n:string;x,y,s,k:longint;
begin
 readln(n);//读入字符串
 readln(s);//读入要加的数
 val(copy(n,1,pos(':',n)-1),x);delete(n,1,pos(':',n));val(n,y);//分离出来
 y:=y+s;k:=y div 60;y:=y mod 60;x:=x+k;x:=x mod 24;//处理
 if x<10 then write(0);write(x);write(':');if y<10 then write(0);write(y);//输出
end.
```


---

## 作者：Dimly_dust (赞：1)

### 题意翻译
给定一个24小时制的时间,请输出这个时间过了 $a$ 分钟后的样子。

这道题是字符串题，因为此字符串有特殊情况可以进行预判：
```cpp
	string n;
	cin>>n;
	int a=(n[0]-'0')*10+n[1]-'0',b=(n[3]-'0')*10+n[4]-'0';//分解时和分
```
得到时和分后就可以大胆分类了：
```cpp
	int s;
	cin>>s;
	b+=s;
	a=(a+(b/60))%24;//时
	b%=60;//分
```
于是源代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string n;
	cin>>n;
	int a=(n[0]-'0')*10+n[1]-'0',b=(n[3]-'0')*10+n[4]-'0';
	int s;
	cin>>s;
	b+=s;
	a=(a+(b/60))%24;
	b%=60;
	if(a<10) cout<<0;
	cout<<a<<":";
	if(b<10) cout<<0;
	cout<<b;
	
	 
	return 0;
}

```
成功了！庆祝一下吧。



---

## 作者：七夜 (赞：1)

首先我要说一点废话，也就是所谓的进制问题，分钟是六十进制，而小时是二十四进制

其次就是采取对前导零的处理，只需要判断是否是一位数，也就是是否小于零

那剩下的就奉上分蒟蒻的代码（注释在代码里面）

```
#include<bits/stdc++.h>//偷懒专用库
inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}//快读，可供参考 
using namespace std;
int n,m,a,tot=0;//n表示小时，m表示分钟，a是过得时间，tot在主函数里一看便知 
string s;//直接输入字符串 
int main()
{
	cin>>s;//输入，为什么不用快读呢？我也不知道，反正用了出过错，所以只用快读读入int类型的整数 
	for(int i=0;i<s.size();++i)//进行区分 
	 {
	 	if(s[i]==':')
	 	 {
	 	 	tot=1;
	 	 	continue;
		 }//判断是小时还是分钟 
		if(tot==0)
		 {
		 	n=n*10+(s[i]-'0'); 
		    continue;
		 }//tot为0的时候表示小时， 
		if(tot==1)
		 {
		    m=m*10+(s[i]-'0');
		 }//tot为一的时候表示分钟 
	 }
	a=read();//这里就可以使用快读了，只不过是习惯，可以换成其他的 
    m+=a;//把分钟加上过去的 
    n+=(m/60);//取出进位的加在小时上 
    m%=60;//对分钟取余 
    n%=24;//对小时取余 
    if(n<10)
     cout<<0;//，如果小时是一位数，就对小时加上前导零 
    cout<<n<<":";//输出小时和冒号 
    if(m<10)
     cout<<0;//如果分钟也是个位数，就也给分钟加上前导零 
    cout<<m;//输出分钟 
    return 0;//华华丽丽而又不失优雅的结束 
}
```
通过吧

---

## 作者：applese (赞：1)

此题不难，只需要注意时间即可，我发现下面的题解都是处理完再输出的，这有点麻烦（可能是我个人认为吧QAQ）

附上代码：
```
#include<iostream>
using namespace std;
int h,m;
int main()
{
	char ch;
	cin>>h>>ch>>m;
	int t;
	cin>>t;
	if(m+t>=60)    //当时间（分钟）到达60或更多的时候就得加(m+t)/60个小时
	{
		h+=(m+t)/60;
	}
   //下面就是处理输出了，可以理解的QAQ，但是需要特判：
	if(h%24<10)
	{
		cout<<"0"<<h%24<<":";
		if((m+t)%60<10)
		cout<<"0"<<(m+t)%60;
		else
		cout<<(m+t)%60;
	}
	else
	{
		cout<<h%24<<":";
		if((m+t)%60<10)
		cout<<"0"<<(m+t)%60;
		else
		cout<<(m+t)%60;
	}
	//cout<<h%24<<":"<<(m+t)%60;
	return 0;  //结束
}
```

如果对此题解有疑问，请在右边申诉，谢谢合作QAQ

---

## 作者：jinhangjie2006 (赞：1)

这一题要注意几点：

1：小时和分钟如果是各位数，那么应该补0，比如1点9分，那就是01:09

2:60分钟一个小时，多出来的向前进位。

3：进位后可能大于24小时，所以要进行取余，25小时就是就是01点。
```pascal
var
  n,m,k,h:longint;
  s,s1:string;
begin
  readln(s);//输入现在的时间
  read(n);//输入过了多少分钟
  val(copy(s,1,pos(':',s)-1),h);//有几小时，拷贝出来，然后转化成数字
  val(copy(s,pos(':',s)+1,length(s)),m);//有几分钟，拷贝出来，转化成数字
  m:=m+n;//把过了几分钟和现在的分钟数加上去
  h:=h+m div 60;//进位
  m:=m mod 60;//60分钟一个小时，取余
  h:=h mod 24;//可能已经超过24小时了，取余
  if h<10 then write(0);//如果是各位数，前面补0
  write(h);
  write(':');
  if m<10 then write(0);//如果各位数，补0
  write(m);
end.
```

---

## 作者：封禁用户 (赞：1)

这道题有两个点:第一个是小时是$24$进制,分钟是$60$进制;第二个是不足两位地方用$0$占位(例如要写成$22:09$而不是$22:9$)

详情看代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
char s;//冒号
int x,y,a;
int main()
{
	cin>>x>>s>>y;
	cin>>a;
	if((x+(a/60)+(y+(a%60))/60)%24/10==0)//如果小时进了位之后是一位数(a/60是加上的分钟的进位,y+a%60是分钟,用它/60也是加上的分钟的进位,%24是小时的进位)
		cout<<0;//输出前导零
	cout<<(x+(a/60)+(y+(a%60))/60)%24;//输出小时
	cout<<":";
	if((y+(a%60))%60/10==0)//如果分钟进了位之后是一位数(%60是分钟的进位)
		cout<<0;//输出前导零
	cout<<(y+(a%60))%60;//输出分钟
	return 0;
}
```
虽然感觉if语句里面的东西有点长,但思路清晰吧

---

## 作者：封禁用户 (赞：0)

这道题有两个点:第一个是小时是$24$进制,分钟是$60$进制;第二个是不足两位地方用$0$占位(例如要写成$22:09$而不是$22:9$)

详情看代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
char s;//冒号
int x,y,a;
int main()
{
	cin>>x>>s>>y;
	cin>>a;
	if((x+(a/60)+(y+(a%60))/60)%24/10==0)//如果小时进了位之后是一位数(a/60是加上的分钟的进位,y+a%60是分钟,用它/60也是加上的分钟的进位,%24是小时的进位)
		cout<<0;//输出前导零
	cout<<(x+(a/60)+(y+(a%60))/60)%24;//输出小时
	cout<<":";
	if((y+(a%60))%60/10==0)//如果分钟进了位之后是一位数(%60是分钟的进位)
		cout<<0;//输出前导零
	cout<<(y+(a%60))%60;//输出分钟
	return 0;
}
```


---

