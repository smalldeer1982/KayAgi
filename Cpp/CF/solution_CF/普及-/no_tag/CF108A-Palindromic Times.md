# Palindromic Times

## 题目描述

Tattah is asleep if and only if Tattah is attending a lecture. This is a well-known formula among Tattah's colleagues.

On a Wednesday afternoon, Tattah was attending Professor HH's lecture. At 12:21, right before falling asleep, he was staring at the digital watch around Saher's wrist. He noticed that the digits on the clock were the same when read from both directions i.e. a palindrome.

In his sleep, he started dreaming about such rare moments of the day when the time displayed on a digital clock is a palindrome. As soon as he woke up, he felt destined to write a program that finds the next such moment.

However, he still hasn't mastered the skill of programming while sleeping, so your task is to help him.

## 样例 #1

### 输入

```
12:21
```

### 输出

```
13:31
```

## 样例 #2

### 输入

```
23:59
```

### 输出

```
00:00
```

# 题解

## 作者：Eason_AC (赞：4)

## Content
现在是 $h$ 时 $m$ 分，请求出在此之后（不包含此时）的第一个回文时间。

**数据范围：$0\leqslant h\leqslant 23,0\leqslant m\leqslant 59$。**
## Solution
众所周知，回文时间每个小时段最多只有一个，我们来枚举一下：$00:00,01:10,02:20,03:30,04:40,05:50,10:01,11:11,12:21,13:31,14:41,15:51,20:02,21:12,22:22,23:32$。就只有以上这 $16$ 个时间是回文时间，因此，我们一步一步往后推时间，并判断是不是上面的这 $16$ 个时间就好了。

注意，这里输出时间只有 $1$ 位的要补足输出，所以我们可以用 $\texttt{printf}$ 的奇技淫巧—— $\texttt{\%0xd}$ 输出（其中 $x$ 代表的是输出的位数，不足这个位数的话自动向前面用 $0$ 补足，例如下面的 $\texttt{\%02d}$ 就是按照两位输出，不足两位的话自动向前面用 $0$ 补足）。
## Code
```cpp
#include <cstdio>
using namespace std;

int main() {
	int h, m;
	scanf("%d:%d", &h, &m);
	while(1) {
		m++;
		if(m > 59)	h++, m = 0;
		if(h > 23)	h = 0;
		if((h == 0 && m == 0) || (h == 1 && m == 10) || (h == 2 && m == 20) || (h == 3 && m == 30) || (h == 4 && m == 40) || (h == 5 && m == 50) || (h == 10 && m == 1) || (h == 11 && m == 11) || (h == 12 && m == 21) || (h == 13 && m == 31) || (h == 14 && m == 41) || (h == 15 && m == 51) || (h == 20 && m == 2) || (h == 21 && m == 12) || (h == 22 && m == 22) || (h == 23 && m == 32))	{
			printf("%02d:%02d", h, m);
			break;
		}
	}
	return 0;
}
```

---

## 作者：༺ʚFLYɞ༻ (赞：1)

## 这道题根本不需要暴力，思路都在程序里，话不多说直接亮程序
# 请勿抄袭！！！
```cpp
#include<bits/stdc++.h>
using namespace std;
#define  qingwuchaoxi int
qingwuchaoxi a1,d,b,a[24]={0,110,220,330,440,550,660,770,880,990,1001,1111,1221,1331,1441,1551,1661,1771,1881,1991,2002,2112,2222,2332};//打表，因为是回文数，其实是只要知道前两个数就行了（00~24） 
char c;//c用来输入“：”，b用来输入小时，d用来输入分钟 
int main()
{
    cin>>b>>c>>d;
    a1=b*100+d;//把时间转换成数字 
    if(a[b]<=a1&&a[b+1]>a1)// b是小时刚好可以当a[] 下标 
    { //因为有可能a[b ]>或<a1所以要判断q 
    	while(a[b+1]%100>=60)
        b++;
    	if(a[b+1]/1000==0&&a[b+1]%100/10==0)//输出要分两部分，如0110，分为01 10，其中01在c++会变成1
		                                    //                如1001,分为10 01，其中01在c++会变成1要判断 
    	cout<<"0"<<a[b+1]/100<<":0"<<a[b+1]%100;
    	else if(a[b+1]/1000==0)
    	     cout<<"0"<<a[b+1]/100<<":"<<a[b+1]%100;
		     else if(a[b+1]%100/10==0)
		          cout<<a[b+1]/100<<":0"<<a[b+1]%100;
		          else cout<<a[b+1]/100<<":"<<a[b+1]%100;
	}
    else if(a[b]>a1)//因为有可能a[b ]>或<a1所以要判断
    {
        while(a[b]%100==0)//分钟有可能>=60要判断 
        b++;
    	if(a[b]/1000==0&&a[b]%100/10==0)//输出要分两部分，如0110，分为01 10，其中01在c++会变成1
		                                //                如1001,分为10 01，其中01在c++会变成1要判断 
    	cout<<"0"<<a[b]/100<<":0"<<a[b]%100;
    	else if(a[b]/1000==0)
    	     cout<<"0"<<a[b]/100<<":"<<a[b]%100;
		     else if(a[b]%100/10==0)
		          cout<<a[b]/100<<":0"<<a[b]%100;
		          else cout<<a[b]/100<<":"<<a[b]%100;
	}
	else cout<<"00:00";//特殊情况23:59后是00:00 
    return 0;
}
```
运行结果https://www.luogu.com.cn/record/30308576
### 本人的第一个题解不好请见谅

---

## 作者：DPseud (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF108A)

[博客使用更佳](https://dguru.blog.luogu.org/)

# 题目思路

各位大佬用的都是一些很深奥的方法，本蒟蒻不懂，这里我介绍一种新的方法：60 进制：

我们都知道，时间单位之间的进率是 60，因此我们可以将 h:m 的形式转换为 m 的形式，这样做一些运算会更为方便，虽然本题只是增加 1 ，但是 60 进制的方法却能让代码更简短。

因为数据不大，因此简单的模拟是没有问题的，但是这题需要注意三点：

1. 要注意回文时间，00:00 也算

2. 遍历时可能到达第二天，需要 %24

3. 要注意格式，个位数要加前缀 0

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int gtime[2];//将读入的字符串转换为两个数 
string format(int n)//将常数转换为时间格式（即个位数补前缀0） 
{
	if(n>=10)
	{
		char c1,c2;
		c1=n/10+48;
		c2=n%10+48;
		string s="";
		s+=c1,s+=c2;
		return s;
	}
	if(n<10)
	{
		char c1='0',c2;
		c2=n+48;
		string s="";
		s+=c1,s+=c2;
		return s;
	}
}
int main()
{
	static int ptime[16][2]={0,0,1,10,2,20,3,30,4,40,5,50,10,1,11,11,12,21,13,31,14,41,15,51,20,2,21,12,22,22,23,32};//因为一天内只有16个回文时间，所以可以打一个二维表 
	string s;
	cin>>s;
	gtime[0]=(s[1]-48)+(s[0]-48)*10;//将字符串转换为两个时和分 
	gtime[1]=(s[4]-48)+(s[3]-48)*10;
	int sixty=gtime[0]*60+gtime[1];//转换为60进制 
	while(1)//因为条件较难打，可以来一个while(1) 
	{
		sixty++;//下一分 
		gtime[0]=sixty/60;//将60进制转换为时和分 
		gtime[1]=sixty%60;
		if(gtime[0]>23)gtime[0]-=24;//因为数据中有可能有23:32之后的（即下一个回文时间是00:00），所以这里做个特判 
		for(int i=0;i<16;i++)
		{
			if(gtime[0]==ptime[i][0]&&gtime[1]==ptime[i][1])//判断是否与某一个回文时间相同 
			{
				cout<<format(gtime[0])<<":"<<format(gtime[1]);
				return 0;//直接退出，这里不能用break，否则只会退出for 
			}
		}
	}
	return 0;
}
```


---

## 作者：Waaifu_D (赞：0)

**思路**

按照题意，如果本小时没有符合条件的时间，就循环到下一个小时，如果下一个小时也没有符合的，就继续循环到下一个小时。

**注意事项**

1.如果小时数大于24，就要取模24，就像样例2给的情况一样，我这点是用特判来解决的.

2.分钟数也要取模60。

3.特判一定要结束程序！！！（因为这点卡了我半小时）。

AC代码如下

```cpp
#include <iostream>
#include<cstdio>
using namespace std;
int hh,mm,xh,xm;//hh，mm为输入数据，xm为要反转的分钟
int main()
{
    scanf("%d:%d",&hh,&mm);//小技巧，scand两个%x%x之间的符号会被省略不被输入
    xm=(hh%10)*10+hh/10;//反转小时数
    if(hh==23&&mm>32)//这个特判可以节省不少时间（并没有）
    {
        cout<<0<<0<<":"<<0<<0;//直接输出
        return 0;
    }
    if(xm>=60||xm<=mm)
    {
        int mi=0;
        while(1)//循环找符合条件的时间
        {   
            hh=(hh+1)%24;
            mi=(hh%10)*10+hh/10;
            if((hh%10)*10+hh/10==mi&&mi<60)//如果满足回文且分钟数少于60
            {
                if(hh<10)//也要判断前导9
                {
                    cout<<0<<hh;
                }
                else
                {
                    cout<<hh;
                }
                cout<<":";//记得输出冒号
                if(mi<10)
                {
                 cout<<0<<mi;
                 }
                else{
                 cout<<mi;
                 }
                 return 0;//直接结束程序即可
            }
        }
    }
    else//不用进行特判循环，可以直接输出的类型，如12:10这种的
    {
        if(hh<10)//不足10要输出前导0
        {
            cout<<0<<hh;
            cout<<":";
        }
        else
        {
            cout<<hh<<":";
        }
        if(xm<10)//同上
        {
            cout<<0<<xm;
        }
        else{
            cout<<xm;
        }
        return 0;
    }
}

```


---

## 作者：Query_Failed (赞：0)

本题其实是比较简单的一道模拟题，直接上思路。
### 思路：
我们需要进行分类讨论。

第一种情况：在本小时内会出现大于现在时间的回文时刻，直接输出即可。

第二种情况：在本小时内没有大于现在时间的回文时刻，我们就需要**循环**直到找到能够满足题意的回文时刻。


------------

1. 如果判断出是第一种情况，我们就可以直接输出。代码如下：
```cpp
int mm;   //用来存储回文后的分钟。
mm=(h%10)*10+h/10;
if(mm<60 and mm>m) 
{
	if(h<10) cout<<"0"<<h;  //注意不满10的时候需要前补0。
	else cout<<h;
	cout<<":";
	if(mm<10) cout<<"0"<<mm;
	else cout<<mm;
	return 0;
}
```
2. 如果不是第一种情况，我们就需要用到 while 循环，按小时数枚举，并算出对应的回文时刻然后再判断。代码如下：
```cpp
else
{
	h=(h+1)%24;
	mm=(h%10)*10+h/10;
	m=0;
	while(mm>=60 or mm<m)
	{
		h=(h+1)%24;
		mm=(h%10)*10+h/10;
	}
}
mm=(h%10)*10+h/10;
if(h<10) cout<<"0"<<h;
else cout<<h;
cout<<":";
if(mm<10) cout<<"0"<<mm;
else cout<<mm;
```

## 完整代码：
```cpp
#include <iostream>
using namespace std;
int main()
{
	int h,m,cha;
	char gj;   //用来输入冒号。
	cin>>h>>gj>>m;
	int mm;	  
	mm=(h%10)*10+h/10;
	if(mm<60 and mm>m) 
	{
		if(h<10) cout<<"0"<<h; 
		else cout<<h;
		cout<<":";
		if(mm<10) cout<<"0"<<mm;
		else cout<<mm;
		return 0;
	}
	else
	{
		h=(h+1)%24;  //注意需要考虑到23点变为0点的情况。
		mm=(h%10)*10+h/10;
		m=0;
		while(mm>=60 or mm<m)
		{
			h=(h+1)%24;
			mm=(h%10)*10+h/10;
		}
	}
	mm=(h%10)*10+h/10;
	if(h<10) cout<<"0"<<h;
	else cout<<h;
	cout<<":";
	if(mm<10) cout<<"0"<<mm;
	else cout<<mm;
	return 0;
}

```



---

## 作者：BBD186587 (赞：0)

说实话这道题不难，然而我却get了那么多次UKE。。。

我的思路其实很简单，就是暴力枚举。。。

话不多说，上代码（我的代码为了防UKE写了有点长）

分割线（抄袭可耻）

—————————————————————————————————————————————
```
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
  int a,b;
  scanf("%d:%d",&a,&b);
  b=b+1;
  if(b<=a/10+a%10*10&&a/10+a%10*10<60)//这些是特判（为了防UKE。。。）
  {
      b=a/10+a%10*10;
      printf("%02d:%02d",a,b);
      return 0;
  }
  else
  {//开始正式判断
    a=a+1;
    for(;a<=23;a++)
        for(b=1;b<=59;b++)//暴力上双重循环
            if(a/10==b%10&&a%10==b/10)//一堆判断
            {
                printf("%02d:%02d",a,b);
                return 0;
			}
  }
  cout<<"00:00";//yeqingbuyaozai login erroe le    最后来发注释保佑下
  return 0;//qingbuyaozaiUKEle
}
```
可能我的代码不是最优解，但它应该是最容易看懂的~~~ 码字不易，且看且珍惜。

---

## 作者：灵光一闪 (赞：0)

看了看tj，感觉我这个超好理解的 ~~（蜜汁兴奋~~

# 壮哉我STL！

这题可以说是C++水题，首先：这题数据范围贼小 ~~（24*60？~~

于是，我们可以提前暴力枚举所有的可能出现的数，然后存在两个``map``里，一个序号转字符串，另一个反之

CODE：
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<map>
#include<string>
using namespace std;
map <int,string> mp;
int tep;
map <string,int> mp2;
string s;
string str;
string ans;
void ycl(){
    for(int i=0;i<24;i++){//循环小时
        for(int j=0;j<=59;j++){//分钟
            str="";
            if(i<10){//不满两位补个0
                str=str+'0'+(char)(i+'0');
            }
            else{//不然就正常压进去
                str=str+(char)(i/10+'0')+(char)(i%10+'0');
            }
            str+=':';//一定要压一个':'
            if(j<10){//同上
                str=str+'0'+(char)(j+'0');
            }
            else{//emming……
                str=str+(char)(j/10+'0')+(char)(j%10+'0');
            }
            ans=str;
            reverse(str.begin(),str.end());
            if(ans==str){
//                cout<<ans<<endl;
                mp[tep++]=ans;
                mp2[ans]=tep;
            }
            else{
                if(ans>"23:32"){//特判，如果比最后一个回文串还大就赋为0
                    mp[tep]=ans;
                    mp2[ans]=0;
                }
                else{//不然就正常
                    mp[tep]=ans;
                    mp2[ans]=tep;//这里压得是下一个回文串的序号
                }
            }
        }
    }
    return;
}
int main(){//精简的主程序
    ycl();
    cin>>s;                        ——————
    cout<<mp[mp2[s]]<<endl;//转化成|下一个|回文串的序号
    return 0;			   		   ——————
}
```

---

## 作者：Arvin2018 (赞：0)

本题求下一个回文时间，**直接模拟**~~暴力~~就行了

解释详见代码

```cpp
#include <bits/stdc++.h>
using namespace std;

bool judge(int m, int h){//判断是否是回文时间
	int a[4];
	a[1] = h%10;
	h /= 10;
	a[0] = h;
	a[3] = m%10;
	m /= 10;
	a[2] = m;
	if(a[0] == a[3] && a[1] == a[2]){//例：1,3,3,1
		return true;
	}
	else return false;
}

int main(){
	int hour, minute;
	string x;
	cin >> x;
	//由于输入的是时间（有冒号），所以要用字符串
	//例:  1     3     :     3     1
	//   x[0]  x[1]  x[2]  x[3]  x[4]  
	hour = (x[0]-'0')*10 + (x[1]-'0');//由于字符串中都是char型变量，所以要减去'0'（数字0的acsii码）
	minute = (x[3]-'0')*10 + (x[4]-'0');
	while(1){
	//一个一个试
		minute++;
		if(minute == 60){//如果minute达到60，minute清零，hour+1
			minute = 0;
			hour += 1;
		}
		if(hour == 24){//如果hour达到24，hour清零
			hour = 0;
		}
		if(judge(minute, hour)){//判断是否回文
			if(hour < 10){//如果是小于10的数字，例如9，会输出“9：xx",而题目要求是”09：xx",所以要判断
				cout << "0" << hour;
			}
			else cout << hour;
			cout << ":";
			if(minute < 10){//同上
				cout << "0" << minute;
			} 
			else cout << minute;
			return 0;
		}
	}
	return 0;
}

```

---

