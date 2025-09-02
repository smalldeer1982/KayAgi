# Karen and Morning

## 题目描述

可怜已经准备好迎接在学校的新的一天。

现在是hh:mm，一个被以24小时制给与的时间。正如你所知道的，可怜喜欢回文，并且她相信如果在她醒来时的时间是回文的话会给她带来好运。

当她醒来时时间是回文的话，她最少应当睡多长时间？

记住，一个回文数是一个从前读和从后读相同的字符串。例如，05:39是不是回文数，因为05:39倒着读是93:50。另一方面，05:50是回文，因为05:50倒着读是05:50。

## 说明/提示

在第一个样例中，可怜最少应睡的时间为$11$ ，这样她可以在05:50时醒来，这是一个回文时间。

在第二个样例中，可怜可以立刻起来，当前时间13:31就是一个回文。

在第三个样例中，可怜最少应睡的时间为$1$ 分钟。她可以在00:00醒来，这是一个回文时间。

感谢@Khassar 提供的翻译

## 样例 #1

### 输入

```
05:39
```

### 输出

```
11
```

## 样例 #2

### 输入

```
13:31
```

### 输出

```
0
```

## 样例 #3

### 输入

```
23:59
```

### 输出

```
1
```

# 题解

## 作者：引领天下 (赞：4)

其实此题并不用转整数啊？

直接string做不就行了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
string s;
int ans;//答案
inline string r(string n){string k="";for (int i=n.size()-1;i>=0;i--)k+=n[i];return k;}//反转
int main(void){
    cin>>s;
    while (s!=r(s)){//不回文
        ans++;
        s[4]++;//分+1
        if (s[4]>'9')s[4]='0',s[3]++;//分满十进一
        if (s[3]>='6')s[3]=s[4]='0',s[1]++;//十满六进一
        if (s[1]>'9')s[1]='0',s[0]++;//时满10进一
        if (s[0]=='2'&&s[1]=='4')s[0]=s[1]='0';//时满24归零
    }
    cout<<ans;//ok
}
```

---

## 作者：zwy__ (赞：1)

## 整体思路
这是一道纯模拟题，我们用字符串把时间存起来，每一次将最后一位加一，在做好时间的处理，最后在输出次数就好了。
## 具体细节
首先，用字符串存好时间。每一次字符串的最后一位加一。如果最后一位满十，想前一位进一。如果前一位满六，再向前一位进一。如果在前一位满十，在想前一位进一。如果前两位已经到了二十四，时间清零。如果运行到回文，结束循环，输出次数。
## 具体代码如下↓↓↓
```cpp
#include<bits/stdc++.h>
using namespace std;
string st;
int sum;
bool check(string x)
{
	string k="";
	for(int i=x.size()-1; i>=0; i--)k+=x[i];
	return k==x;
}//用来判断是否是回文的函数
int main()
{
	cin>>st;
	while(check(st)==false)
	{
		sum++;//次数加一
		st[4]++;//每次最后一位加一
		if(st[4]>'9')//细节的处理
		{
			st[4]='0';
			st[3]++;
		}
		if(st[3]>='6')
		{
			st[3]='0';
			st[4]='0';
			st[1]++;
		}
		if(st[1]>'9')
		{
			st[1]='0';
			st[0]++;
		}
		if(st[0]=='2'&&st[1]=='4')
		{
			st[0]='0';
			st[1]='0';
		}
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：GZY007 (赞：1)

### 整体思路
这是一道模拟题，但这题可以用其他方法做。首先，我们可以枚举二十四小时内每个回文时间，并把它们记录下来，然后根据 Karen 的睡觉时间，找出比它晚的第一个回文时间，然后求出它们的差值即可。
### 具体思路
在枚举每一个回文时间时，我们可以枚举每一个小时，对于每个小时，都会有一个分钟与它成为回文，我们只需要判断这个时间是否合法就可以了。然后再把合法的回文时间转成分钟为单位放入数组即可。

在求比 Karen 的睡觉时间晚的首个回文时间时，可以使用   STL 中的函数或者手写二分或一个个枚举都可以。

还有最后要加个特判，让它过了二十四小时后归零。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[30],cnt,h,m,ans,t;
int main(){
	for(int i=0;i<=23;i++){
		int x=(i%10)*10+i/10;
		if(x>59) continue ;
		a[++cnt]=i*60+x;
	}
	scanf("%d:%d",&h,&m);
	t=h*60+m;
	if(t>a[cnt]) ans=1440-t+a[1];
	else ans=a[lower_bound(a+1,a+cnt+1,t)-a]-t;
	printf("%d",ans);
return 0;
}

```


---

## 作者：Eason_AC (赞：1)

## Content
给定一个时间 $h:m$，求从现在这个时间开始到第一个回文时间要多久？

**数据范围：$0\leqslant h\leqslant 23,0\leqslant m\leqslant 59$。**
## Solution
其实 ``scanf`` 有个特别的技巧叫做按格式读入，比如说这里我们就可以用 ``scanf("%d:%d", ...);`` 来按照 $h:m$ 的格式读入。

然后，正如我在 [CF108A 的题解](https://www.luogu.com.cn/blog/EasonBlog1/solution-cf108a)里面讲的那样，一共的回文时间只有 $16$ 个（具体是哪几个自己点进去看），所以先判断是否是回文，然后再往后一步一步地推时间就好了。

这题貌似和 [CF108A](https://www.luogu.com.cn/problem/CF108A) 差不多，只是要求的不是具体的时间而是过了多久罢了。
## Code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#define _for(i, a, b) for(int (i) = (a); (i) <= (b); ++(i))
#define _rep(i, a, b) for(int (i) = (a); (i) >= (b); --(i))
using namespace std;

typedef long long ll;

inline void getint(int& x) {
	int f = 1; x = 0;
	char c = getchar();
	while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
	while(isdigit(c)) {x = x * 10 + c - '0'; c = getchar();}
	x *= f;
}
inline void getll(ll& x) {
	ll f = 1; x = 0;
	char c = getchar();
	while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
	while(isdigit(c)) {x = x * 10 + c - '0'; c = getchar();}
	x *= f;
}
inline void writeint(int& x) {
	if(!x) {printf("0"); return;}
	else if(x < 0) printf("-");
	int tmp = x < 0 ? -x : x, digit[17] = {0};
	while(tmp) {digit[++digit[0]] = tmp % 10; tmp /= 10;}
	_rep(i, digit[0], 1)	printf("%d", digit[i]);
}
inline void writell(ll& x) {
	if(!x) {printf("0"); return;}
	else if(x < 0) printf("-");
	ll tmp = x < 0 ? -x : x;
	int digit[27] = {0};
	while(tmp) {digit[++digit[0]] = tmp % 10; tmp /= 10;}
	_rep(i, digit[0], 1)	printf("%d", digit[i]);
}

int main() {
//	freopen(".in", "r", stdin);
//	freopen(".out", "w", stdout);
	int h, m, ans = 0;
	scanf("%d:%d", &h, &m);
	while(1) {
		if((h == 0 && m == 0) || (h == 1 && m == 10) || (h == 2 && m == 20) || (h == 3 && m == 30) || (h == 4 && m == 40) || (h == 5 && m == 50) || (h == 10 && m == 1) || (h == 11 && m == 11) || (h == 12 && m == 21) || (h == 13 && m == 31) || (h == 14 && m == 41) || (h == 15 && m == 51) || (h == 20 && m == 2) || (h == 21 && m == 12) || (h == 22 && m == 22) || (h == 23 && m == 32)) {
			writeint(ans);
			break;
		}
		m++, ans++;
		if(m > 59)	h++, m = 0;
		if(h > 23)	h = 0;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
```

---

## 作者：Query_Failed (赞：0)

由于题解中大佬的思路基本都是模拟然后判断的思路，于是本蒟蒻决定发一篇思路不一样的题解。

### 整体思路：
将 Karen 的每一个起床的小时枚举，算出与之对应的满足回文时间的时刻，然后再算出 Karen 的睡眠时间。

### 具体思路：
首先明确本题需要一个小小的**分类讨论**。

在第一种情况下，本时刻就能够找到满足题意的回文数，这样可以直接计算。

第二种情况就需要**循环**直到能够找到满足题意的回文时刻。

1. 第一种情况：我们只需要直接算出回文时间的分钟与现在的分钟数之差。代码如下：
```cpp
if(mm<60 and mm>=m) 
{
	cout<<mm-m;
	return 0;
}
```
2. 第二种情况：我们需要判断，然后循环到能够找到满足条件的回文时刻，我们需要一个 sum 变量存储一共的时间。代码如下：
```
else
{
	h=(h+1)%24;
	sum+=60-m;
	mm=(h%10)*10+h/10;
	m=0;
	while(mm>=60 or mm<m)
	{
		h=(h%23)+1;
		sum+=60;
		mm=(h%10)*10+h/10;
	}
    cout<<sum+mm;
}
```

## 完整代码：
```cpp
#include <iostream>
using namespace std;
int main()
{
	int h,m;
	char gj;   //用来输入冒号。 
	cin>>h>>gj>>m;
	int mm,sum=0;
	mm=(h%10)*10+h/10;    //回文后的分钟。 
	if(mm<60 and mm>=m) 
	{
		cout<<mm-m;
		return 0;
	}
	else
	{
		h=(h+1)%24;  //注意需要考虑到23点变为0点的情况。 
		sum+=60-m;
		mm=(h%10)*10+h/10;
		m=0;
		while(mm>=60 or mm<m)
		{
			h=(h%23)+1;
			sum+=60;
			mm=(h%10)*10+h/10;
		}
		cout<<sum+mm;
	}
	return 0;
}

```


---

## 作者：happybob (赞：0)

首先我写了个判断是否回文的函数：
```cpp
bool huiwen(string x)//判断是否回文
{
    string y = x;
    int z = y.length();
    for(int i = 0; i <= z / 2; i++)//reverse速度不行，不至于TLE，不过自己写好
    {
        swap(y[i], y[z - i - 1]);//交换
    }
    return y == x;//如果y = x，返回true，回文，否则false
}

```

然后就是时钟模拟了呗

此题比较简单，代码如下：

2.06s，160个全AC，挺壮观！

速度排第5，还不错哦：

```cpp
#include <iostream>
#include <cstring>//string的头文件
#include <algorithm>//swap翻转的头文件
using namespace std;

string str;

bool huiwen(string x)//判断是否回文
{
    string y = x;
    int z = y.length();
    for(int i = 0; i <= z / 2; i++)//reverse速度不行，不至于TLE，不过自己写好
    {
        swap(y[i], y[z - i - 1]);//交换
    }
    return y == x;//如果y = x，返回true，回文，否则false
}

int main()
{
    cin >> str;
    int ans = 0;
    while(!huiwen(str))//循环
    {
        //时钟模拟
        str[4]++;
        if(str[4] > '9')//分钟的个位大于9时十位+1
        {
            str[4] = '0';
            str[3]++;
        }
        if(str[3] >= '6')//十位大于6个位十位都归零
        {
            str[3] = '0';
            str[4] = '0';
            str[1]++;
        }
        if(str[1] > '9')//时的个位大于9，时的十位+1
        {
            str[1] = '0';
            str[0]++;
        }
        if(str[0] == '2')//如果时为24，归0
        {
            if(str[1] == '4')
            {
                str[0] = '0';
                str[1] = '0';
            }
        }
        ans++;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：锦瑟，华年 (赞：0)

大家好，本蒟蒻又来写题解了！

好了，言归正传，这题，很明显是一道大模拟，如果这题还WA了，我也没办法了。

题目：

现在是hh:mm，一个被以24小时制给与的时间。正如你所知道的，可怜喜欢回文，并且她相信如果在她醒来时的时间是回文的话会给她带来好运。

当她醒来时时间是回文的话，她最少应当睡多长时间？

思路：

首先，我们先把hh和mm读进来，或者直接用字符串读也行，接下来，每次给分加上1，再来几个判断，用来进位，这样，就可以模拟闹钟了。

模拟了之后只需加上回文判断，输出即可。

好了，现在来点实际的，上代码：

	#include<stdio.h>
	using namespace std;
	char a[15];
	int hw(){//回文判断
		if(a[1]==a[5]&&a[2]==a[4])return 1;
		else return 0;
	}
	int main(){
		scanf("%s",a+1);
		int ans=0;
		while(hw()==0){
			ans++;
			a[5]++;//模拟时钟
			if(a[5]>'9'){
				a[5]='0';a[4]++;
			}
			if(a[4]>='6'){
				a[4]='0';a[2]++;
			}
			if(a[2]>'9'){
				a[2]='0';a[1]++;
			}
			if(a[1]=='2'&&a[2]>='4'){
				a[1]=a[2]='0';
			}
		}
		printf("%d",ans);//输出
		return 0;//over~
	} 
    
OK,完美结束，求过qwq。

---

## 作者：灵光一闪 (赞：0)

~~我又来写题解了！~~   
~~这个人真是的，睡个觉还有那么多讲究~~  
好了不胡扯了，说正事

# string模拟转进制即可

```
//无脑模拟
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<string>
using namespace std;
void ok(int n)
{
    cout<<n;
    exit(0);//返回主程序并return 0;
}
int main()
{
    string s,t;
    cin>>s;
    t=s;
    reverse(t.begin(),t.end());
    for(int i=0;;i++)
    {
        t=s;
        reverse(t.begin(),t.end());//每一次都要判断一下
//        cout<<s<<endl;
        if(t==s)
            ok(i);
        int a=s[0]-'0',b=s[1]-'0',c=s[3]-'0',d=s[4]-'0';
        d++;
        //模拟进位
        if(d==10)
        {
            d=0;
            c++;
        }
        if(c==6)
        {
            c=0;
            b++;
        }
        if(b==10||(b==4&&a==2))
        {
            b=0;
            a++;
        }
        if(a==3)
        {
            a=0;
            b=0;
            c=0;
            d=0;
        }
        //模拟进位
        s[0]=a+'0';
        s[1]=b+'0';
        s[3]=c+'0';
        s[4]=d+'0';
    }
}

```

---

## 作者：yuzhechuan (赞：0)

话说这160个点全AC了还是很壮观的啊~~~


------------

```cpp
#include<bits/stdc++.h>//方便的万能库，开放的洛谷
using namespace std;

int ih,imin,ans;//ih为时，imin为分

bool check(int x,int y)//判断是否为回文的函数
{                      //因为时与分都是位数<=2的正整数，所以可以如此方便
    return x/10==y%10&&x%10==y/10;
}/*      ------|------|------|-----  
         时十位|分个位|时个位|分十位       */
int main()
{
    scanf("%d:%d",&ih,&imin);//scanf能自动跳过'：'
    if(!check(ih,imin))//特判读入时就是回文的情况
    while(1)//一直循环，直至break
    {
    	ans++;//答案加一
    	imin++;//分钟加一
    	if(imin==60){ih++;imin=0;}//分钟60进一
    	if(ih==24)ih=0;//24:00=>00:00
    	if(check(ih,imin))break;//判断回文
    }
    cout<<ans;//输出结果
    return 0；//嘿嘿嘿
}
```


------------
蒟蒻的~~无脑~~代码.cpp

---

## 作者：PC_DOS (赞：0)

本题只需要一分钟一分钟地模拟，并判断是不是回文时间即可。

输入时间的时候，通过scanf做如下格式设定，可以减少将时间作为字符串处理时的麻烦:

```
scanf("%d:%d", &Hour, &Minute);
```

代码:
```
#include <iostream>
#include <string>
#include <sstream>
using namespace std; //头文件和命名空间
struct Time{ //定义时间结构体
	int iHour=0; //小时
	int iMinute=0; //分钟
};
Time TimeAddByOneMinute(Time tmeOrig){ //将时间增加1分钟
	Time tmeReturn; //返回值
	if (tmeOrig.iHour < 0 || tmeOrig.iHour >= 24 || tmeOrig.iMinute < 0 || tmeOrig.iMinute >= 60){ //防错
		tmeReturn.iHour = 0;
		tmeReturn.iMinute = 0;
		return tmeReturn;
	}
	if (tmeOrig.iHour == 23 && tmeOrig.iMinute == 59){ //23:59特殊处理
		tmeReturn.iHour = 0;
		tmeReturn.iMinute = 0;
	}
	else if (tmeOrig.iMinute == 59){ //改变小时数的其他情况
		tmeReturn.iHour = tmeOrig.iHour + 1;
		tmeReturn.iMinute = 0;
	}
	else{ //一般情况
		tmeReturn.iHour = tmeOrig.iHour;
		tmeReturn.iMinute = tmeOrig.iMinute + 1;
	}
	return tmeReturn;
}
string ToString(int iNum){ //借用字符串流手写ToString
	stringstream ssStream; //定义字符串流
	string sAns; //返回值
	ssStream << iNum; //整数进入流
	ssStream>>sAns; //流进字符串
	return sAns; //返回
}
string ToString(Time tmeTime){ //将时间转化为00:00型式字符串的函数
	string sMinute, sHour, sAns; //sMinute-分钟；sHour-小时；sAns-返回值
	sMinute = ToString(tmeTime.iMinute); //计算分钟
	if (sMinute.length() == 1) //补零
		sMinute = "0" + sMinute;
	sHour = ToString(tmeTime.iHour); //计算小时
	if (sHour.length() == 1) //补零
		sHour = "0" + sHour;
	sAns = sHour + ":" + sMinute; //连接
	return sAns; //返回
}
string strReverse(string strOrigin){ //字符串反转函数
	if (strOrigin.length() == 0){
		return "";
	}
	long long i;
	string ans;
	for (i = strOrigin.length() - 1; i >= 0; --i) ans += strOrigin[i];
	return ans;
}
int main(){
	Time tmeTime; //时间
	string sTime; //字符串形式的时间
	int iMinutes = 0; //所需经历的分钟数
	scanf("%d:%d", &tmeTime.iHour, &tmeTime.iMinute); //读入初始时间
	sTime = ToString(tmeTime); //转为字符串
	while (sTime != strReverse(sTime)){ //不是回文时间时
		tmeTime = TimeAddByOneMinute(tmeTime); //加一分钟
		sTime = ToString(tmeTime); //转为字符串
		++iMinutes; //加一分钟
	}
	printf("%d", iMinutes); //输出所需时间
	return 0; //结束
}
```

---

