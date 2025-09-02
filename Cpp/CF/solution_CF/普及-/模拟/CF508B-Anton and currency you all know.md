# Anton and currency you all know

## 题目描述

Berland, 2016. The exchange rate of currency you all know against the burle has increased so much that to simplify the calculations, its fractional part was neglected and the exchange rate is now assumed to be an integer.

Reliable sources have informed the financier Anton of some information about the exchange rate of currency you all know against the burle for tomorrow. Now Anton knows that tomorrow the exchange rate will be an even number, which can be obtained from the present rate by swapping exactly two distinct digits in it. Of all the possible values that meet these conditions, the exchange rate for tomorrow will be the maximum possible. It is guaranteed that today the exchange rate is an odd positive integer $ n $ . Help Anton to determine the exchange rate of currency you all know for tomorrow!

## 样例 #1

### 输入

```
527
```

### 输出

```
572
```

## 样例 #2

### 输入

```
4573
```

### 输出

```
3574
```

## 样例 #3

### 输入

```
1357997531
```

### 输出

```
-1
```

# 题解

## 作者：bigju (赞：1)

### 题目大意

给定一个非常大的奇数，让你交换它的两位，使得得到的数为偶数并且最大。

### 做法

比较容易想到，我们肯定要拿最高位的偶数来交换，这样增加的最多。

但是这里有一个问题。比如下面这个数字： $85321$ 。如果我们用上面的做法交换，那么就会得到 $15328$ 这个数字，很显然，最佳的答案是 $85312$ 。

所以我们把上面的做法修改一下：**把最高位并且小于最后一位的偶数来交换，如果没有则把最低位的偶数与最后一位交换。**

如果都没有，这说明比最后一位大的偶数没有，比最后一位小的偶数也没有，那么它就没有偶数，直接输出无解。

代码：
```cpp
#include<cstdio>
#include<iostream>
#define ll long long
using namespace std;
string ch;
bool temp=1;
int fir,las=-1;
int main()
{
    cin>>ch;
    for(int i=0;i<ch.size();i++)
    {
    	if((ch[i]-'0')%2==0&&ch[i]<ch[ch.size()-1]) //如果有比他小的偶数，因为我们是从前往后筛的，直接交换 
		{
			swap(ch[i],ch[ch.size()-1]);
			cout<<ch;
			return 0;
		}
	}
	for(int i=ch.size()-1;i>=0;i--)//如果没有比他小的偶数，那只能尽可能减少损失了 
	{
		if((ch[i]-'0')%2==0) 
		{
			swap(ch[i],ch[ch.size()-1]);
			cout<<ch;
			return 0;
		}
	}
	//此时我们把比最后那个奇数大的偶数和小的偶数都筛完了，发现都没有 
	cout<<-1;//上述两种情况都没发生，说明一个偶数没有 
	return 0;
}

```


---

## 作者：Franka (赞：0)

~~翻译有问题。~~
### **题目**
给你一个**字符串**$n$，求**交换一次**后**最大的偶数**，如果**不能**，则输出$-1$。

**1≤n的长度≤100000。**
### **思路**
一开始看到翻译，以为是$105$位的字符串，就打了一个无脑模拟，秒送$TLE$![](https://cdn.luogu.com.cn/upload/pic/69020.png)。

代码如下（TLE代码）：
```pascal
var
 i,j:longint;//整形
 p:boolean;//布尔类型
 n,m,max:string;//字符类型
function jh(i,j:longint;n:string):string;var ch:char;begin ch:=n[i];n[i]:=n[j];n[j]:=ch; exit(n);end;//用来交换的函数
begin
 readln(n);//读入n
 p:=true;//反证法
 for i:=1 to length(n) do if ord(n[i]) mod 2=0 then p:=false;//如果有偶数，就不必输出-1
 if p then begin writeln(-1);exit;end;//如果没有偶数，直接输出-1并结束程序
 for i:=1 to length(n)-1 do for j:=i+1 to length(n) do//找两个不同的位数
   begin
    m:=jh(i,j,n);//交换
    if ord(m[length(m)]) mod 2=0 then//如果是偶数
     if m>max then max:=m;//找最大值
   end;
 writeln(max);//输出最大值
end.
```

#### 正确思路：找到比最后一位小的偶数，然后交换。再找到另一个偶数，和最后一位交换即可。
### **代码**
```pascal
var
 n:ansistring;//定义超长字符串
 p:boolean;
 i:longint;
procedure jh(i,j:longint;var n:ansistring);//还是交换的函数
var
 ch:char;
begin
 ch:=n[i];n[i]:=n[j];n[j]:=ch;
end;
begin
 readln(n);
 p:=true;
 for i:=1 to length(n) do if ord(n[i]) mod 2=0 then p:=false;
 if p then begin writeln(-1);exit;end;
 //以上依旧还是判断是否全是奇数
 for i:=1 to length(n) do//第一次查找
  if ord(n[i]) mod 2=0 then//偶数
   if n[i]<n[length(n)] then//比最后一位小
    begin
     jh(i,length(n),n);//交换
     break;//推出当前循环
    end;
 for i:=length(n) downto 1 do//同理
  if ord(n[i]) mod 2=0 then
   begin
    jh(i,length(n),n);
    break;
   end;
 writeln(n);//输出n
end.
```


---

## 作者：Oscar12345 (赞：0)

[原题链接](http://codeforces.com/problemset/problem/508/B)

题意：给出一个长度小于105的奇数，交换其中两位，使其变成一个偶数，若有多种做法输出最大的。若不能构造出一个偶数，输出-1。

样例：
input：527
output：572

input：4573
output：3574

input：1357997531
output：-1

思路：贪心。一开始以为只需交换最高位偶数即可，秒送wa。 
正确解法是找出最高位的比最末位奇数小的偶数，交换它们。 
若没有，交换最低位的偶数与最末位奇数。

代码：
```
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define max(a,b) a>b?a:b
#define min(a,b) a>b?b:a
using namespace std;
char a[100010];
int main()
{
    gets(a);
    bool f=0;
    int l=strlen(a);
    for(int i=0;i<l;i++)
    {
        if((a[i]-'0')%2==0&&a[i]<a[l-1])
        {
            f=1;
            swap(a[i],a[l-1]);
            break;
        }
    }
    if(!f)
    {
        for(int i=l-1;i>=0;i--)
        {
            if((a[i]-'0')%2==0)
            {
                f=1;
                swap(a[i],a[l-1]);
                break;
            }
        }
    }
    if(f)
        puts(a);
    else 
        puts("-1");
    return 0;
}
```

---

## 作者：zhanghzqwq (赞：0)

这是一道贪心题，一共三次操作。

先扫一遍，看看那里面有没有偶数，如果没有就直接输出-1，然后return 0。

然后从前往后扫一遍，如果发现有一个偶数，且这个偶数比最末尾的那个奇数要小就交换，之后输出，return 0。

最后到这一步就说明所有的偶数都比那个奇数要大，只需要从后往前扫一遍，发现一个偶数交换即可。

****提醒一下：找到了一定要break出去。

AC代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	string a;
	cin>>a;//输入不解释
	int la=a.size();
	bool found=0;
	for(int i=0;i<la;i++){
		int num=a[i]-'0';
		if(num%2==0){
			found=1;//找到了
			break;//这里不break无所谓，这样快一点
		}
	}
	if(!found){
		cout<<"-1"<<endl;
		return 0;
	}
	int end=a[la-1]-'0';//end是最末尾的奇数
	bool ok=0;
	for(int i=0;i<la;i++){
		int num=a[i]-'0';
		if(num%2==0&&num<end){
			swap(a[i],a[la-1]);
			ok=1;//找到了
			break;//一定要break出去
		}
	}
	if(ok){
		cout<<a<<endl;
		return 0;
	}
	for(int i=la-1;i>=0;i--){//从后往前找
		int num=a[i]-'0';
		if(num%2==0){
			swap(a[i],a[la-1]);
			break;//这里也一定要break出去
		}
	}
	cout<<a<<endl;
	return 0;//完结撒花
}
```


---

