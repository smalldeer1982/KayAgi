# A+B Problem（升级版）

## 题目背景

小明这在写作业，其中有一道A+B Problem ，他想啊想啊想，就是想不出来，于是就找到了会编程的你......


## 题目描述

这里的 $A+B$ 是很奇特的。它是按质数的顺序来进位的。例如：$1,0+2,1$ ＝ $1,0,1$（用 $\verb!,!$ 来分隔每一位）。个位是 $2$ 进制，十位是 $3$ 进制，百位是 $5$ 进制，千位是 $7$ 进制，万位是 $11$ 进制……两个加数的最高位是万位（万位可能有两位）。

## 样例 #1

### 输入

```
1,0+2,1```

### 输出

```
1,0,1```

# 题解

## 作者：Blue_wonders (赞：65)

# 题目没读懂的往这看，详细解释题目输入输出


------------

## 按照题意简单的模拟(绝对简单易懂)
### 这次排坑和思路放在一起了
```
样例输入： 
      1     ,      0     +      2      ,     1
第一个数十位  第一个数个位  第二个数十位 第二个数个位
相加变成                 0 , 0 , 0 , 0 , 3 , 1 
(这里是每一位的进位大小)  13  11  7   5   3   2
所以变成了               0 , 0 , 0 , 1 , 0 , 1
输出按照从高位到低位输出   1  ,   0  ,   1
                        百位   十位   个位
样例输出：1,0,1


自己写的输入,并附上自己的做法：
输入：12,1,4,6,8+26,4,7,9,5
输出：3,6,1,3,0,1
做法：从后往前入(从个位输入,好处是方便判断数的位数)
  位数表      十万  ,  万  ,  千  ,  百  ,  十  ,  个 
 每一位的进制   13      11      7     5      3      2
 
1、输入第二个数 0       26      4      7      9      5
2、加上第一个数 0       38      5     11     15     13
3、从最小位     0       38      5     11    15+6     1
   判断是否     0       38      5    11+7     0      1
   需要进位     0       38     5+3     3      0      1
   并进位       0      38+1     1      3      0      1
   	          0+3       6      1      3      0      1
   	           3        6      1      3      0      1
4、输出3,6,1,3,0,1 
```
### AC代码在这

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int c[7]={0,2,3,5,7,11,13};//判断每一位数进位的标准 
int a[7];//存放每一位数的容器 
void chack(int q){//进位函数
	a[q+1]=a[q+1]+(a[q]/c[q]);//上一位加上这一位进的数
	a[q]=a[q]%c[q];//这一位是进完位之后剩下的数
	return;
}
int main(){
	cin>>s;//按照字符串读入 
	int n=s.size(),i=n-1,u=1;
	while(i>=0){//从最后判断，从个位数加起 
		if(s[i]>='0'&&s[i]<='9'){//如果是数字 
			if(s[i-1]>='0'&&s[i-1]<='9'){//如果是两位数 
				a[u]=a[u]+(s[i-1]-48)*10+(s[i]-48);//在数位上加入这个数 
				i--;//前面的数已经被加上了，不能循环 
			}
			else a[u]=a[u]+s[i]-48;//是一位数,就在这个数位上加这个数 
			u++;//加入数字后，下一个数字要在下一个数位上 
		}
		if(s[i]=='+')u=1;//如果是加号，那么代表这个数输完了，重新从各位开始 
		i--;//循环下一个数 
	}
	for(int i=1;i<=5;i++)chack(i);//将每个数位都判断是否需要进位 
	int t=0;//t用来标记最大位的位置 
	for(int i=6;i>=1;i--)if(a[i]!=0){t=i;break;};//先找最大位是哪个 
	for(int i=t;i>=2;i--)cout<<a[i]<<",";//从最大位输出，一直输出到10位，后面加‘，’ 
	cout<<a[1];//最后输出各位后面没有‘，’ 
	return 0;
}
```
感谢大家看我的题解~！

---

## 作者：jingkongwanglimiaoa (赞：18)

## 前言
如果只是想通过此题，那么该篇题解将会显得非常冗长，但我想说考试题不会纯出一道只有一个简单高精式子的题目。

举个例子，它有时会在 dp 题中出高精，`max/min` 的操作与加减乘除的操作混着一起来，这个时候难道还继续沿用主函数里套个循环的写法吗？

## 大致做法

由题意，我们会发现这就是普通的高精 $a+b$ 然后改了下每一位的模数。

竖式模拟加法，不同的是之前是满十进一，而这题是要预处理每一位对应的质数，满该质数进一，我们可以使用一个 `pri` 数组来存它。

由于数据不会大，我们可以用朴素方法枚举质数，而不必用什么什么筛法（还占空间）。

### 质数的预处理

```
...
bool check(int n)//判断是否为质数
{
	for (int i = 2; i * i <= n; i++) if (n %  i == 0) return false;
	return true;
}
...
hp = 1;
pri[1] = 2;//第一位对应的质数为2
int num = 3;//从3开始判断
while (hp <= 600)//600位足矣
{
	if (check(num)) pri[++hp] = num;//如果是质数就存下来
	num++;//枚举下一个数
}
```

### 重点：高精度部分

要想处理一些复杂的高精操作，必须要创建结构体，然后通过重载运算符/构建函数来解决。

#### 创建结构体

```cpp
struct GJ{
	int len,p[666];//len代表数字长度，p数组就是数字
	GJ()//用来初始化
	{
		len = 0;
		memset(p,0,sizeof(p));
	}
	void print()//用来输出，反着来是因为我们处理时常常把数字顺序反过来，即低位在前，输出的时候自然要先把高位输出
	{
		for (int i = len; i >= 1; i--) printf("%d%c",p[i],i == 1 ? ' ' : ',');
	}
}x,y;
```
这个东西会有什么用呢？

- 它可以直接创建一个高精度变量，用来定义高精度数组时会好看些，如下
```cpp
GJ dp[666][666];
int dp[666][666][666];//多出来的最后一维就是用来处理高精的
```


- 它可以初始化它创建的高精度变量，相信没人会想让自己的代码里出现 n 多次 `memset	` 的吧。
- 它可以直接输出一个高精度变量，如下

```cpp
ans.print();
```



这便是结构体的创建。

#### 重载运算符

```cpp
GJ operator + (const GJ &a,const GJ &b)
{
	GJ c;
	c.len = a.len > b.len ? a.len : b.len;
   /*三目运算符，作用形同 if(a.len > b.len) c.len = a.len; else c.len = b.len;*/
	for (int i = 1; i <= c.len; i++)//高精加部分
	{
		c.p[i] += a.p[i] + b.p[i];//注意这里是加等于，因为还有进位在这之前加上去了
		c.p[i + 1] = c.p[i] / pri[i];//把进位加上，如果c.p[i] < pri[i] 就是加上0，因为c++中除法向下取整
		c.p[i] %= pri[i];
	}
	if (c.p[c.len + 1]) c.len++;//最高位有进位特殊处理
	return c;//直接返回一个GJ类型的变量
}
```

你会发现这不就是普通的高精加套了点语法嘛。

的确如此，但你把加法重构掉了，只要你在你的程序写了这个，你的高精加立马可以变成
```cpp
GJ a,b,c;//三个数的是GJ类型的变量
a = b + c;//由于加被重载掉了，此处都是高精加
b = a + c;//随便加
c = a + a + c;
b = a + c
a = b + c;
//以上五行都在随便加
```

哎，就是随便加，就是玩，而且它不会影响到你其它普通的加法，顿时有了比 py 更强的快感！这个方法同样使用于其它运算符号，文末会给出。

至于语法，其实多打几遍就背熟了。

### 读入

我只能讲完高精度再讲读入，不然会让人一头雾水。

**注意**：$x,y$ 都是 `GJ` 类型的变量。

其实就是遇到逗号就代表一个数位的终结，遇到加号就代表一个数字的终结，注意要有 `-'0'` 操作才能把字符转成数。

然后我还会有一个数位颠倒的操作，其实这不难想到，是因为高位会被先输入进来，但是我们通常都是从低位开始处理，同时这样也方便处理进位，同时也方便我们调用对应位所对应的质数。至于怎么样数位颠倒，我们可以让首位与最后一位交换，然后让第二位与倒数第二位交换，依次类推，直至交换到最中间。

两个数字交换我并没有使用中间变量，我是这样做的


------------

有 $a,b$ 两数，

新 $a$ 等于旧 $a$ $+$ 旧 $b$，

新 $b$ 等于新 $a$ $-$ 旧 $b$ 即为旧 $a$，

新新 $a$ 等于新 $a$ $-$ 新 $b$ 即为旧 $b$，

现在的 $a$ 就会等于原来的 $b$，而现在的 $b$ 就会等于原来的 $a$ 了。


------------


所以交换 $a,b$ 的代码可写为
```cpp
a = a + b;
b = a - b;
a -= b;

```
读入部分的代码如下


```cpp
	cin >> str;//输入字符串
	for (int i = 0; i < str.size(); i++)
	{
		hp++;
		while (str[i] != ',' && str[i] != '+') x.p[hp] = x.p[hp] * 10 + str[i] - '0',i++;//把每个数字还原
		if (str[i] == '+')//遇到+说明跳到下一个数
		{
			f = i + 1;//记录下一个数的开头
			break;//跳出循环
		}
	}
	x.len = hp;//记录数字长度
	for (int i = 1; i <= hp / 2; i++)//颠倒数位顺序
	{
		x.p[i] += x.p[hp - i + 1];
		x.p[hp - i + 1] = x.p[i] - x.p[hp - i + 1];
		x.p[i] -= x.p[hp - i + 1];//交换，如上文字说明
	}
	hp = 0;//回收废物利用 
	for (int i = f; i < str.size(); i++)//同上
	{
		hp++;
		while (i != str.size() && str[i] != ',' && str[i] != '+') y.p[hp] = y.p[hp] * 10 + str[i] - '0',i++;
	}
	y.len = hp;//记录数字长度
	for (int i = 1; i <= hp / 2; i++)//同上
	{
		y.p[i] += y.p[hp - i + 1];
		y.p[hp - i + 1] = y.p[i] - y.p[hp - i + 1];
		y.p[i] -= y.p[hp - i + 1];
	}
```

## 完整清晰版代码

```cpp
# include <cstdio>
# include <iostream>
# include <string>
# include <cstring>
using namespace std;
string str;
int hp,f,pri[666];
bool check(int n)
{
	for (int i = 2; i * i <= n; i++) if (n %  i == 0) return false;
	return true;
}
struct GJ{
	int len,p[666];
	GJ()
	{
		len = 0;
		memset(p,0,sizeof(p));
	}
	void print()
	{
		for (int i = len; i >= 1; i--) printf("%d%c",p[i],i == 1 ? ' ' : ',');
	}
}x,y;
GJ operator + (const GJ &a,const GJ &b)
{
	GJ c;
	c.len = a.len > b.len ? a.len : b.len;
	for (int i = 1; i <= c.len; i++)
	{
		c.p[i] += a.p[i] + b.p[i];
		c.p[i + 1] = c.p[i] / pri[i];
		c.p[i] %= pri[i];
	}
	if (c.p[c.len + 1]) c.len++;
	return c;
}
int main()
{
	cin >> str;
	for (int i = 0; i < str.size(); i++)
	{
		hp++;
		while (str[i] != ',' && str[i] != '+') x.p[hp] = x.p[hp] * 10 + str[i] - '0',i++;
		if (str[i] == '+')
		{
			f = i + 1;
			break;
		}
	}
	x.len = hp; 
	for (int i = 1; i <= hp / 2; i++)
	{
		x.p[i] += x.p[hp - i + 1];
		x.p[hp - i + 1] = x.p[i] - x.p[hp - i + 1];
		x.p[i] -= x.p[hp - i + 1];
	}
	hp = 0;
	for (int i = f; i < str.size(); i++)
	{
		hp++;
		while (i != str.size() && str[i] != ',' && str[i] != '+') y.p[hp] = y.p[hp] * 10 + str[i] - '0',i++;
	}
	y.len = hp;
	for (int i = 1; i <= hp / 2; i++)
	{
		y.p[i] += y.p[hp - i + 1];
		y.p[hp - i + 1] = y.p[i] - y.p[hp - i + 1];
		y.p[i] -= y.p[hp - i + 1];
	}
	hp = 1;
	pri[1] = 2;
	int num = 3;
	while (hp <= 600)
	{
		if (check(num)) pri[++hp] = num;
		num++;
	}
	x = x + y;
	x.print();
	return 0;
}
```

注释之前各个板块都有，就给了一份清晰无注释版的了。

## 写在最后
我之前提到过，其它运算符也可以这样处理。

给出乘法的以供比对，为了不占太多版面，使用云剪贴板形式如下

[高精乘低精(重载运算符)](https://www.luogu.com.cn/paste/wxwrquwx)

[高精max(函数)](https://www.luogu.com.cn/paste/d9hlngz6)

[高精乘高精(重载运算符)](https://www.luogu.com.cn/paste/d7vhw4qy)


---

## 作者：tututu (赞：9)

我这个程序好像是最短的了...

按照题意模拟.困难的主要是读入部分吧

见程序:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
const int num[6]={0,2,3,5,7,11};
int a[7],b[7],c[7];
char ch;
void f(int a[]){//f()把数组倒过来 
  memcpy(c,a,sizeof c);
  rep(i,1,a[0]) a[i]=c[a[0]-i+1];
}
int main(){
  scanf("%d%c",&a[++a[0]],&ch);//读入第一对 
  while(ch!='+') scanf("%d%c",&a[++a[0]],&ch);//读到'+' 
  while(cin>>b[++b[0]]>>ch);//读完 
  f(a);//倒过来 
  f(b);//也倒过来 
  rep(i,1,5) c[i]=a[i]+b[i];//相加 
  rep(i,1,5){//进位 
    c[i+1]+=c[i]/num[i]; 
    c[i]%=num[i];
  }
  c[0]=max(a[0],b[0])+(c[max(a[0],b[0])+1]>0);//压了一下代码长度...就是判断是否超出原来a和b的长度 
  cout<<c[c[0]]; 
  for(int i=c[0]-1;i;i--) cout<<','<<c[i];//输出 
  return 0;
}
```

---

## 作者：fysbb (赞：7)

先将字符串中的两个加数转为整形存入数组，之后按照题意进行计算即可。

```cpp
var
   s:string;
   i,j,k,le:longint;
   a:array[1..2,1..55]of longint;
   b:array[1..55]of longint;
begin
  readln(s);
  j:=1;k:=1;le:=0;
  for i:=length(s) downto 1 do  begin
    if s[i]='+' then begin inc(k);le:=j;j:=1;end
      else if s[i]<>',' then begin a[k,j]:=ord(s[i])-48;inc(j);end;
    if j=7 then begin a[k,5]:=a[k,5]+a[k,j-1]*10;a[k,j-1]:=0;dec(j);end;
  end;
  if le<j then le:=j;
  dec(le);
  for i:=1 to le do b[i]:=a[1,i]+a[2,i];
  if b[1]>=2 then begin k:=b[1] div 2;b[1]:=b[1] mod 2;inc(b[2],k);end;
  if b[2]>=3 then begin k:=b[2] div 3;b[2]:=b[2] mod 3;inc(b[3],k);end;
  if b[3]>=5 then begin k:=b[3] div 5;b[3]:=b[3] mod 5;inc(b[4],k);end;
  if b[4]>=7 then begin k:=b[4] div 7;b[4]:=b[4] mod 7;inc(b[5],k);end;
  if b[5]>=11 then begin k:=b[5] div 11;b[5]:=b[5] mod 11;inc(b[6],k);end;
  if b[le+1]<>0 then write(b[le+1],',');
  for i:=le downto 2 do write(b[i],',');
  write(b[1]);
  readln;
  readln;
end.
```

---

## 作者：FANTA5TlC (赞：5)

大家好，我是dyisz

[题面](https://www.luogu.com.cn/problem/P1581)

[更好的阅读体验](https://www.luogu.com.cn/blog/297798/solution-p1581)

今天，本蒟蒻看到10篇题解没有1篇是python

于是本蒟蒻秃发奇想，写出了本程序

## 思路
思路比较简单，把输入的两个数转成字符串，然后题目要你怎么算就怎么算（转化类型是相对于别的语言）

代码本蒟蒻直接贴上了
```python
t=input() #input输入直接是字符串
s=t.split('+')
s1=s[0].split(',')
s1.reverse() #这里要倒一下字符串，方便处理
s2=s[1].split(',')
s2.reverse()
z=max(len(s1),len(s2)) #处理过程
if len(s1)<z:
    for i in range(z-len(s1)):
        l1.append(0)
if len(s2)<z:
    for i in range(z-len(s2)):
        l2.append(0)
s3=[]
for i in range(z):
    s3.append(int(s1[i])+int(s2[i]))
s3.append(0)
jin=[2,3,5,7,11] #jin数组表示进制
for i in range(len(s3)-1):
    if s3[i]>=jin[i]:
        s3[i]-=jin[i]
        s3[i+1]+=1 #按要求计算
s3.reverse() #倒回来输出
if s3[0] is 0:
    s3.remove(0) #移除前导0
print(s3[0],end="")
for i in range(1,len(s3)):
    print(','+str(s3[i]),end="") #输出
```

---

## 作者：Level_Down (赞：3)

[可能会有更好的阅读体验](https://www.luogu.com.cn/blog/wangjinhao/solution-p1581)

题意不再说明了，这里主要讲一下方法和几个坑点。

第一阶段：

在这一阶段中你需要清楚的知道这道题所需的方法：

首先是读入，然后需要每一位每一位按照类似高精度加法的方法来加。

只不过高精加法是满十进一，这里是满 $prime[i]$ （即第 $i$ 个质数）进一。

最后是输出。

第二阶段：

在这一阶段你需要在知道方法的情况下实现代码。

首先是读入：

```cpp
cin >> a[++cnt1];	//一个一个读入。
while(scanf("%c",&ch) != EOF) 
	{
		if (ch == '+') flag = 1;//如果是加号，那接下来读入的就是b数组的数。
		flag ? cin >> b[++cnt2] : cin >> a[++cnt1];
      		//通过flag来判断应该读入哪个数组的数。  
	}
cnt2--;//因为最后还会读入一个代表结束的符号，所以cnt2--。
```

***坑点**： **不可以**写以下这份代码，因为万位可能有两位，这个代码每次只能读入一位数。

```cpp
cin >> s;
for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '+') {flag = 1;continue;}
		if (s[i] == ',') continue;
		flag ? b[++cnt2] = s[i] - '0' : a[++cnt1] = s[i] - '0';
	}
```


然后就是加法的步骤：

**切记切记切记**要先把 $a$ 和 $b$ 两个数组得数都反转一遍，因为一开始输入的是最高位。

然后就是正常的加法步骤了，质数表自己手打就行了：

```cpp
len = max(cnt1,cnt2);//len相当于其他一些代码中的c[0]。
for (int i = 1; i + i <= cnt1; i++) swap(a[i],a[cnt1 - i + 1]);	//反转。
for (int i = 1; i + i <= cnt2; i++) swap(b[i],b[cnt2 - i + 1]);	
for (int i = 1; i <= len; i++)//正常加法步骤
	{
		c[i] += a[i] + b[i];
		c[i + 1] = c[i] / prime[i],c[i] %= prime[i];	
	}	
if (c[len + 1]) len++;
//这上面一行是特殊进位。
```

最后是输出：

~~**我绝对不会告诉你因为样例正反输出都一样就没有反着输出结果只得了20分的。**~~

```cpp
cout << c[len];//注意要反着输出就行了。
for (int i = len - 1; i >= 1; i--) cout << "," << c[i];
```

至此，我们就可以愉快地AC本题了：

```cpp
#include <bits/stdc++.h>//目测是最短代码，只有20行。 
using namespace std;//并且是截至作者写题解时的全洛谷最优解。 
int a[10],b[10],c[10],flag,cnt1,cnt2,len,prime[10] = {0,2,3,5,7,11,13,17,19};char ch; string s;
int main(){//不加注释了。 
	cin >> a[++cnt1];	
	while(scanf("%c",&ch) != EOF) {
			if (ch == '+') flag = 1;
			flag ? cin >> b[++cnt2] : cin >> a[++cnt1];
		}
	cnt2--,len = max(cnt1,cnt2);
	for (int i = 1; i + i <= cnt1; i++) swap(a[i],a[cnt1 - i + 1]);	
	for (int i = 1; i + i <= cnt2; i++) swap(b[i],b[cnt2 - i + 1]);	
	for (int i = 1; i <= len; i++){
			c[i] += a[i] + b[i],c[i + 1] = c[i] / prime[i],c[i] %= prime[i];
		}	
	if (c[len + 1]) len++;
	cout << c[len];
	for (int i = len - 1; i >= 1; i--) cout << "," << c[i];
	return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/39859685)

---

## 作者：DWT8125 (赞：2)

### 题目评论
- 这一道题有点像[P1601](https://www.luogu.com.cn/problem/P1601)，就是改了一下每个位的进制，以及用到了字符串。
- 易上手的模拟题，值得萌新一做。

### 注意事项
1. **读入部分**。字符串输入，加号前面是第一个数,加号后面是第二个数，注意分离每个数位。
1. **万位可能有两位**。这个不用我多说吧，加个判断就行了。~~因为没注意这个[第一次我就得了80分](https://www.luogu.com.cn/record/49991686)……~~

### AC代码
我的主要方法是从后往前遍历，方便从低位到高位存入数组，用变量 $ab$ 来标记此时是该存入 $a$ 数组还是 $b$ 数组，遇到加号就标记一下 $b$ 数组存完了。

请看注释，代码的解释都在里面了。

```cpp
//P1581 AC代码 
#include<bits/stdc++.h> //万能头 
using namespace std;
const int p[8]={0,2,3,5,7,11,13}; //小型质数表 
int a[10],b[10],c[10],al=0,bl=0; //al表示此时a数组的长度，bl同理 
int main(){
	string s; cin>>s;
	bool ab=false; //false即为b数组未存完 
	for(int i=s.size()-1;i>=0;i--){ //从最后一位遍历起 
		if(s[i]>='0'&&s[i]<='9'){
			if(s[i+1]>='0'&&s[i+1]<='9'){ //如果出现有两位数，例如当有数字10时，在1会触发判断 
				if(ab) a[al]+=(s[i]-'0')*10; //（接上）在0存的位置做处理 
				else b[bl]+=(s[i]-'0')*10;
//				printf("%d\n",ab?al:bl);	<-测试使用，没有意义 
			}
			else if(ab) a[++al]=s[i]-'0';
			else b[++bl]=s[i]-'0';
		}	
		else if(s[i]=='+') ab=true; //b数组已存完 
	}
	int cl=al>bl?al:bl;
	for(int i=1;i<=cl;i++){
		c[i]+=a[i]+b[i];
		c[i+1]=c[i]/p[i];
		c[i]%=p[i];
	}
	if(c[cl+1]) cl++; //以上7行为模拟 
	printf("%d",c[cl]); //第一个数前面没有','，提前输出 
	for(int i=cl-1;i>0;i--) printf(",%d",c[i]);
	return 0; //别忘了 
}
```


---

## 作者：wawcac (赞：2)

居然没有c的题解，我来发一个

本题我认为最重要的就是看懂样例，不然就会像我一样一直20分

###是(1,0)+(2,1) 不是1,(0+2),1

知道了这一点，就可以直接模拟了，可能输入还有点问题，我们可以这么看，读入一个数字后，剩下的就是(符号数字)(符号数字)了，知道这个周期，输入就好办了，至于结束，while(scanf("%c%d",&c,&b[lenb++])==2)就可以了


```cpp
#include<stdio.h>
int main()
{
    int zs[10]={2,3,5,7,11,13,17,19};
    int lena=1,lenb=1,a[10]={0},b[10]={0};
    char c=',';
    scanf("%d%c",&a[0],&c);
    while(c!='+')
    {
        scanf("%d%c",&a[lena++],&c);
    }
    scanf("%d",&b[0]);
    while(scanf("%c%d",&c,&b[lenb])==2)lenb++;
    for(int qi=0,zhi=lena-1;qi<zhi;qi++,zhi--)
    {
        int t=a[qi];
        a[qi]=a[zhi];
        a[zhi]=t;
    }
    for(int qi=0,zhi=lenb-1;qi<zhi;qi++,zhi--)
    {
        int t=b[qi];
        b[qi]=b[zhi];
        b[zhi]=t;
```
}//这两个循环把a、b翻转过来，使个位对齐
```cpp
    for(int i=0;i<8;i++)
    {
        a[i]+=b[i];//每一位相加
        if(a[i]>=zs[i])//该进位就进位
        {
            a[i+1]+=a[i]/zs[i];
            a[i]%=zs[i];
        }
    }
    lena=9;
    while(a[lena]==0) lena--;
    printf("%d",a[lena]);
    for(int i=lena-1;i>=0;i--)
    {
        printf(",%d",a[i]);
```
}//输出
    return 0;

}


---

## 作者：一碗粥 (赞：2)

这题可以说是a+b里最难的题了，需要用到类似高精度的方法才能够得出答案

```delphi
var  
s:string;  
l,p,j,k,i,t:longint;  
a,b,c,d:array[1..10000] of longint;  
f:boolean;  
  
begin  
  readln(s);  
  l:=length(s);  
  p:=pos('+',s);j:=1;  
  for i:=1 to p-1 do  
   begin  
    if s[i]=',' then  
     begin  
      j:=j+1;  
      continue;  
    end;  
    if (s[i]<='9') and (s[i]>='0') then  
     begin  
      a[j]:=a[j]*10+ord(s[i])-48;  
      continue;  
    end;  
  end;  
  k:=1;  
  for i:=p+1 to l do  
   begin  
    if s[i]=',' then  
     begin  
      k:=k+1;  
    end;  
    if (s[i]<='9') and (s[i]>='0') then  
     begin  
      b[k]:=b[k]*10+ord(s[i])-48;  
      continue;  
    end;  
  end;  
  for i:=1 to j div 2 do  
   begin  
    t:=a[i];a[i]:=a[j-i+1];a[j-i+1]:=t;  
  end;  
  for i:=1 to k div 2 do  
   begin  
    t:=b[i];b[i]:=b[k-i+1];b[k-i+1]:=t;  
  end;  
  if j<k then j:=k;  
  d[1]:=2;d[2]:=3;d[3]:=5;d[4]:=7;d[5]:=11;d[6]:=10000;  
  for i:=1 to 6 do  
   begin  
    c[i]:=a[i]+b[i]+c[i];  
    c[i+1]:=c[i] div d[i];  
    c[i]:=c[i] mod d[i];  
  end;  
  f:=true;  
  for i:=6 downto 2 do  
   begin  
    if c[i]<>0 then f:=false;  
    if f and (c[i]=0) then continue;  
    write(c[i],',');  
  end;  
  writeln(c[1]);  
end.  
```

---

## 作者：doby (赞：2)

字符串的各种处理是必要的……

由于本题精度较小，手动处理即可……

如果用字符串，其实根本不用处理两位数，直接特判带过就好了，我的代码里竟然还特别麻烦地搞了一堆……

```cpp
#include<iostream>
#include<string>
using namespace std;
int a[9],b[9],c[9],num1=1,num2=1,p=0;
string s,s1,s2;
void print(int p[])//输出
{
    int fir=0;
    for(int i=9;i>=1;i--)
    {
        if((p[i]==0)&&(fir==0)){continue;}
        if(fir==0){cout<<p[i];}//如果第一位没出来就不输出逗号
        else{cout<<","<<p[i];}//否则输出逗号
        fir++;
    }
    cout<<"\n";
    return;
}
void pluss()
{
    for(int i=1;i<=9;i++){c[i]=a[i]+b[i];}//加法
    if(c[1]>=2){c[1]=c[1]-2,c[2]++;}//精度较小，手动进位
    if(c[2]>=3){c[2]=c[2]-3,c[3]++;}
    if(c[3]>=5){c[3]=c[3]-5,c[4]++;}
    if(c[4]>=7){c[4]=c[4]-7,c[5]++;}
    if(c[5]>=11){c[5]=c[5]-11,c[6]++;}
}
int ad(int sta,int endd,string ss)
{
    int s=sta,sum=0;
    while((s>=endd)&&(ss[s]>='0')&&(ss[s]<='9'))
    {
        sum=sum*10+ss[s]-48,//一位位取出累加
        s--;
    }
    if(ss[sta]=='0'){sum=sum*10;}//微小的特判，防止输入“10”
    return sum;
}
int main()
{
    cin>>s;
    while(s[p]!='+'){p++;}//找出加号位置
    for(int i=p-1;i>=0;i--)
    {
        if((s[i]>='0')&&(s[i]<='9'))
        {
            a[num1]=ad(i,0,s),//取出数字
            num1++;
            if(a[num1-1]==10){i--;}//如果是10，跳位（其实是break，因为是最后一位……）
        }
    }
    for(int i=s.size()-1;i>p;i--)
    {
        if((s[i]>='0')&&(s[i]<='9'))
        {
            b[num2]=ad(i,p+1,s),//同上
            num2++;
            if(b[num2-1]==10){i--;}
        }
    }
    pluss();
    print(c);
    return 0;
}
```

---

## 作者：luky2008 (赞：1)

# 上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int c[7]={0,2,3,5,7,11,13};//判断每一位数进位的标准 
int a[7];//存放每一位数的容器 
void chack(int q){//进位函数
    a[q+1]=a[q+1]+(a[q]/c[q]);//上一位加上这一位进的数
    a[q]=a[q]%c[q];//这一位是进完位之后剩下的数
    return;
}
int main(){
    cin>>s;//按照字符串读入 
    int n=s.size(),i=n-1,u=1;
    while(i>=0){//从最后判断，从个位数加起 
        if(s[i]>='0'&&s[i]<='9'){//如果是数字 
            if(s[i-1]>='0'&&s[i-1]<='9'){//如果是两位数 
                a[u]=a[u]+(s[i-1]-48)*10+(s[i]-48);//在数位上加入这个数 
                i--;//前面的数已经被加上了，不能循环 
            }
            else a[u]=a[u]+s[i]-48;//是一位数,就在这个数位上加这个数 
            u++;//加入数字后，下一个数字要在下一个数位上 
        }
        if(s[i]=='+')u=1;//如果是加号，那么代表这个数输完了，重新从各位开始 
        i--;//循环下一个数 
    }
    for(int i=1;i<=5;i++)chack(i);//将每个数位都判断是否需要进位 
    int t=0;//t用来标记最大位的位置 
    for(int i=6;i>=1;i--)if(a[i]!=0){t=i;break;};//先找最大位是哪个 
    for(int i=t;i>=2;i--)cout<<a[i]<<",";//从最大位输出，一直输出到10位，后面加‘，’ 
    cout<<a[1];//最后输出各位后面没有‘，’ 
    return 0;
}
```


---

## 作者：Ufowoqqqo (赞：1)

按照题意模拟。

```delphi

type data=array [0..10] of integer;//高精度数类型

const prime:array [1..5] of integer=(2,3,5,7,11);//质数表前5项

var
 s:string;//式子
 a,b:data;//两个加数
 
procedure work(s:string;var a:data);//把用逗号隔开的每一位分别存入数组里方便计算
var
 i:longint;
 t:data;
begin
 s:=s+',';
 fillchar(a,sizeof(a),0);
 repeat
  inc(a[0]);
  val(copy(s,1,pos(',',s)-1),a[a[0]]);
  delete(s,1,pos(',',s));
 until s='';
 t:=a;
 for i:=1 to a[0] do a[i]:=t[a[0]-i+1];
end;

function plus(a,b:data):data;//高精度加法
var
 i:longint;
begin
 fillchar(plus,sizeof(plus),0);
 if a[0]>b[0] then plus[0]:=a[0] else plus[0]:=b[0];
 for i:=1 to plus[0] do
 begin
  inc(plus[i],a[i]+b[i]);
  plus[i+1]:=plus[i] div prime[i];
  plus[i]:=plus[i] mod prime[i];
 end;
 if plus[plus[0]+1]>0 then inc(plus[0]);
end;

procedure print(a:data);//输出
var
 i:longint;
begin
 for i:=a[0] downto 2 do write(a[i],',');
 write(a[1]);
end;

begin
 readln(s);
 work(copy(s,1,pos('+',s)-1),a);//转换第一个加数
 work(copy(s,pos('+',s)+1,length(s)),b);//转换第二个加数
 print(plus(a,b));//运算并输出
end.

```

---

## 作者：taophee (赞：1)

思路：分开截取，分开处理（方法类似高精度的存储方式）

程序：

```delphi

var
s:ansistring;
l,p,j,k,i,t:longint;
a,b,c,d:array[1..10000] of longint;
f:boolean;

begin
  readln(s);
  l:=length(s);
  p:=pos('+',s);j:=1;
  for i:=1 to p-1 do
   begin
    if s[i]=',' then
     begin
      j:=j+1;
      continue;
    end;
    if (s[i]<='9') and (s[i]>='0') then
     begin
      a[j]:=a[j]*10+ord(s[i])-48;
      continue;
    end;
  end;
  k:=1;
  for i:=p+1 to l do
   begin
    if s[i]=',' then
     begin
      k:=k+1;
      continue;
    end;
    if (s[i]<='9') and (s[i]>='0') then
     begin
      b[k]:=b[k]*10+ord(s[i])-48;
      continue;
    end;
  end;
  for i:=1 to j div 2 do
   begin
    t:=a[i];a[i]:=a[j-i+1];a[j-i+1]:=t;
  end;
  for i:=1 to k div 2 do
   begin
    t:=b[i];b[i]:=b[k-i+1];b[k-i+1]:=t;
  end;
  if j<k then j:=k;
  d[1]:=2;d[2]:=3;d[3]:=5;d[4]:=7;d[5]:=11;d[6]:=10000;
  for i:=1 to 6 do
   begin
    c[i]:=a[i]+b[i]+c[i];
    c[i+1]:=c[i] div d[i];
    c[i]:=c[i] mod d[i];
  end;
  f:=true;
  for i:=6 downto 2 do
   begin
    if c[i]<>0 then f:=false;
    if f and (c[i]=0) then continue;
    write(c[i],',');
  end;
  writeln(c[1]);
end.

```

---

