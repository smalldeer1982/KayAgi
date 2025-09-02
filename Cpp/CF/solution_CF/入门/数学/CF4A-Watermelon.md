# Watermelon

## 题目描述

一个炎热的夏天，Pete 和他的朋友 Billy 感到十分口渴，于是在西瓜摊上买了一个重 $w$ 公斤的西瓜。

他们回到家准备分西瓜。因为两个人都十分喜爱偶数，所以他们俩希望分出来的两块西瓜的重量都是偶数公斤。帮助他们判断是否可能做到这一点。

## 样例 #1

### 输入

```
8
```

### 输出

```
YES
```

# 题解

## 作者：zhanghanbin (赞：32)

本大菜鸡最喜欢使用 $Latex$

## 目录：

- 普及幼儿园数学知识---**奇偶性**

- 填一个大坑---**2能分成 ? 和 ?**

- 代码亮相^o^

------

### 1.奇偶性

首先，能分成任意两个偶数的数一定要是一个**偶数**，$3$你来试试，$1.5+1.5 = ?$

然后就有了一个非常简单的代码：

```cpp
if (n % 2 == 0) cout << "YES" << endl;
else cout << "NO" << endl;
```

没错就是这么简单，不过......

### 2.填坑

就是这样吗？？？怎么可能！！！

CF可不是这么友善的人，所以

$2$ 不能被分成 **两个偶数**

于是：

zhb：$2$ 不能被分成 **两个偶数**

cg：$0 + 2 = 2$ 是什么鬼

zhb：$0$ is 正数？小学数学！

cg：呜呜呜。。。

所以就又有了一个非常简单的代码：

``` cpp
if (n == 2) {
	cout << "NO" << endl;
	return 0;
}
```

### 3.代码

就是这样子啦：
``` cpp
#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
	int n;
	cin >> n;
	if (n == 2) cout << "NO" << endl;
	else if (n % 2 == 0) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
```


---

## 作者：Unknown_Error  (赞：10)

原网站：https://www.luogu.org/problemnew/show/CF4A

#  \_此题有一种很简单的方法。\_

这里要让我们判断一个数能否分成两个正偶数。

# 什么情况才可以？

∵偶+偶=偶；


∴输入的数是一个偶数。

### 原来如此简单！！！

# 但是,有坑！！

我最先就掉下了这个坑


题目要求的是一个**正**偶数。


## 1+1=0+2=2

# 0是正数吗？

本道题告诉我们，简单题有坑！！！

# 参考代码：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n%2==0&&n!=2)//判断奇数偶数，注意n！=2
    cout<<"YES";
    else
    cout<<"NO";
}
```

---

## 作者：Kujo_Jotaro (赞：7)

本题挺简单的，题意就是判断输入的数能否被分成两个**正偶数**相加。

大家看到题，一般都会想到用一种**数学方法**，用我们四年级学的知识：
### **偶数+偶数=偶数**

~~所以所有的偶数都能分为两个正偶数相加，~~ 囧，打住，难点来了。这就是卡住大家的第5个样例！
# 	**2**

2不能分为两个正偶数相加，2=1+1（怎么可能？？），2=0（不是正偶数）+2，所以需要特判
## 					2

# （就这破玩意儿害本蒟蒻WA了几次  QwQ）

好！激动人心的时候到了！献上代码
```cpp
	#include<iostream>
	#include<fstream>
	#include<algorithm>
	#include<cstdio>
	#include<cmath>
	#include<string>
	#include<cstring>
	using namespace std;
	int n;//定义不说
	int main()
	{
	    cin>>n;//cin不说
	    if(n==2){cout<<"NO";return 0;}//重要！！特判2
	    if(n%2==0)cout<<"YES";//如果n是偶数（除了2），	输出“YES”
	    else cout<<"NO";//否则输出“NO”
	    return 0;
	}
```
#### 好了！希望这篇题解能审核成功，如果审核成功，希望能帮助大家解决难题！

今天就讲到这，有什么疑惑请私信 @修罗神 （It's me）！祝大家早日AC！

---

## 作者：Loner_Knowledge (赞：5)


---

此题的题意就是判断输入的数能否被分成两个**偶数**。


明显的，**奇数**均无法满足上述要求，而**偶数中的2**也无法满足上述要求。


于是只需要判断输入的数是否是奇数或者是2即可。


```cpp
#include<cstdio>
int main() {
    int w;
    scanf("%d",&w);
    printf("%s",(w&1||w==2)? "NO":"YES");
    //w&1!=0相当于w%2==1，即是判断w是否是奇数
    return 0;
}
```

---

---

## 作者：真·峭岩仙道 (赞：4)

其实本题还是很水的。

首先要判断负数，然后排除2就行了。

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
long long m;
  cin>>m;
  if(m<=0){
return 0;
           }
           else if(m==2){
           cout<<"NO";
           }
                  else if(m%2==0){
                  cout<<"YES";
                  }
return 0;
}
```
其实题解区dalao们说的已经很明白了，我只是认为负数也最好判断一下。

---

## 作者：applese (赞：3)

此题要满足输入的正整数能否分成两个正偶数，能则输出YES，不能则输出NO，一般有人不会预料到2这个数。便可能做出这样的程序：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int a;
    cin>>a;
    if(a%2==0)
    cout<<"YES";
    else
    cout<<"NO";
} 
```
这样不得满分，我们要考虑2这个数，因为2只能分为1和1.

正确解法：

```cpp
#include<iostream>
using namespace std;
int main()
{
    int a;
    cin>>a;
    if(a%2==0&&a!=2)
    cout<<"YES";
    else
    cout<<"NO";
} 
```

---

## 作者：C3765428 (赞：2)

##### 这是一道小学数学水题。
#### 让我们判断输入的数能否被分成两个偶数。
## 但是
### 我们还是要注意一些细节
### 1.偶数=偶数+偶数
### 所以奇数被排除
### 2.2不能2 不能被分成 两个偶数
# 上代码
```
#include <iostream>
#include <cstdio> 
using namespace std;
int main() {
    int n;
    scanf("%d",n);
    if (n == 2){//特判n==2 
    cout << "NO" << endl;
	}
    else if (n % 2 == 0) {
    cout << "YES" << endl;
	}
	else
	cout << "NO" << endl;
    return 0;
}
```




---

## 作者：wpy233 (赞：2)

楼上的大佬们代码几乎一致。。。

所以本萌新来个不寻常的。。。利用尾数判断

如楼上大佬所说的，当输入的n为2时，是无法拆成两个正偶数的（因为只能拆成1+1）

对于其它的数，如果他们的最后一位（也就是个位）是0、2、4、6、8时，便满足题目中的要求。

话不多说，上代码
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
string a; 
bool pd(int n)//核心函数判断
{
	if(a[n]=='0'||a[n]=='2'||a[n]=='4'||a[n]=='6'||a[n]=='8')//判断个位是否满足要求
		return true;
	return false;
}
int main()
{
	cin>>a;
	if(a=="2")//特判n=2
		cout<<"NO"<<endl;
	else 
		if(pd(a.size()-1))
			cout<<"YES"<<endl;
		else
			cout<<"NO"<<endl;//输出
	return 0;
} 
```

---

## 作者：ygl666666 (赞：1)

# 翻译
一个炎热的夏天，皮特和他的朋友比利决定买一个西瓜。在他们看来，他们选择了最大最成熟的一个。然后称西瓜的重量，秤上显示的重量是多少公斤。他们迫不及待地赶回家，决定把浆果分开，然而他们遇到了一个难题。
皮特和比利都是偶数的忠实粉丝，这就是为什么他们要把西瓜分成两部分，每部分的重量都是偶数公斤，同时，这两部分并不一定要相等。孩子们非常累，想尽快开始吃饭，所以你应该帮助他们，看看他们是否能按照他们想要的方式分割西瓜。当然，他们每个人都应该得到一部分正体重。 
## 偶数的终极粉丝？？？
总结一下就是强迫症。。。
### 前面文章有~~屁用~~啊
####  思路
这题就是要看判断输入的正整数能否分成两个正偶数。
众所周知，偶数只能成偶数+偶数。
所以只要他不是2并且是偶数即可
##### 代码部分，AC代码
```
#include<bits/stdc++.h>//万能头
using namespace std;
int main(){
	int a;
	cin>>a;
	if(a!=2&&a%2==0){//判断
		cout<<"YES";//正确输出YES
	}else{
		cout<<"NO";//否则NO
	}
	return 0;
}
```


---

## 作者：GusyNight (赞：1)

**写一个读入+快读的程序只是个人的习惯~~~**
```cpp
#define TP long long
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
long long init(){
	n=read();
}
```
然后才是主体部分，我个人非常喜欢写函数~~~
```cpp
bool Watermelon(int n){
	if(n%2==0){
		return true;
	}
	return false;
}
```
后来才发现，2不可以拆成2个偶数相加，有人要问了：

0不是偶数吗？2=0+2对不对？
=

***我说一句：0是正数吗？***

0是正数吗？
=
回答是肯定的：0不是正数！
=

***沉默 ing ............***

如果这个数是2的倍数且不为2，那么必定可以分解为2个偶数~~~

所以正确的函数为：
```cpp
bool Watermelon(int n){
	if(n%2==0&&n!=2){
		return true;
	}
	return false;
}
```
有了函数就不难了~~~

**完整的代码！**

```cpp
#include<bits/stdc++.h>
#define TP long long
using namespace std;
inline TP read(){
    char c=getchar();
    TP x=0;
    bool f=0;
    while(!isdigit(c))f^=!(c^45),c=getchar();
    while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f)x=-x;return x;
}
long long n;
long long init(){
	n=read();
}
bool Watermelon(int n){
	if(n%2==0&&n!=2){
		return true;
	}
	return false;
}
int main(){
	init();
	if(Watermelon(n)){
		puts("YES");
	}
	else{
		puts("NO");
	}
	return 0;
}
```

---

## 作者：Gu_Ren (赞：1)

这题是真水啊

竟然没有人水一篇暴力枚举的题解吗~~（坏笑）~~

以上全是废话，以下为我的各种花式枚举

### 最正常的
```cpp
var
  i,j,n:longint;
begin
  read(n);
  for i:=1 to n do
  for j:=1 to n do
  if (i+j=n)and(i mod 2=0)and(j mod 2=0) 
  then begin 
    write('YES'); 
    exit;
  end;
  write('NO');
end.
```
### 稍加优化的for 循环
```cpp
  for i:=2 to n-2 do
  for j:=2 to n-i do
end.
```

### 再加优化的for 循环
```cpp
  for i:=1 to n div 2 do
  for j:=1 to n div 2-i do
  if i*2+j*2=n then ***********
```

### 还可以用while 
```cpp
i:=2;
while i<n do
begin
j:=n-i;
if j mod 2=0 then *********
inc(i,2);
end;
```

## 注:别忘记加对2的特判，因为2：=2+0 ，而0不是正偶数

---

## 作者：LCuter (赞：1)

首先明确：

# 偶数+偶数=偶数

所以，这必须是一个偶数才能分为两个偶数相加

我们可以发现任意正偶数，只要能分解为另两个正偶数和的

必然有一种分解情况$2+x$（x $mod$ 2 =0）

而2这个特殊数字恰巧不能分解为以上形式，那就解决了这个特殊问题

**于是得到满足条件为${n|n-2>0,(n-2) mod 2=0}$**

上代码

```cpp
#include<cstdio>
int main(){
    int n;
    scanf("%d",&n);
    n-=2;
    if(n>0&&!(n%2)){
        printf("Yes");
    }
    else{
        printf("No");
    }
    return 0;
}
```

---

## 作者：紫金依旧 (赞：1)

这其实是一道~~大水题~~.

其实这道题运用的知识非常简单——

# **偶数=偶数+偶数**

由此可以得出:

奇数是不可能符合此条件的

# 但是

### 我们要特判2这个特例,因为2无法分解为两个偶数的和

上代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
	cin>>n;
	if(n%2!=0&&n==2)
		cout<<"NO";
	else
		cout<<"YES";	
	return 0;
}
```

# 求通过

---

## 作者：Andysun06 (赞：1)

## ~~太难了~~

### 就一个地方要注意：2不能分成两个偶数！！！

------------------------------------

##### pascal题解：

```cpp
var n,m,a,b:longint;
begin
 readln(n);
 if n<>2 then//注意：2不能分成两个偶数！！！（我之前就
```
死在这儿！）







   




   






```cpp
 begin
  if n mod 2=0 then
   begin
    writeln('Yes');//'Y'要大写！！
    halt;
   end
   else
    begin
     writeln('No');//'N'要大写！！
     halt;
    end;
    end
    else
    writeln('No');//'N'要大写！！
end.    

```

---

## 作者：SKTelecomT1_Faker (赞：0)

方法其实有好几种，接下来介绍两种：

1.运用小学奥数知识，除了0，2以外的偶数都可以被表示成两个非零偶数之和，所以公式其实很简单：
### 偶数=偶数+偶数
好了上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main( )
{
	int n;
	cin>>n;
	if(n%2==0&&n!=2) cout<<"YES"<<endl;//判断是否满足情况
	else cout<<"NO"<<endl;
	return 0;
} 
```
一开始可能不会过，主要原因是没有判断2这种情况。

2.直接暴力计算，两个for循环，如果i+j为n（输入数据）并且i，j均为非零偶数则输出YES，打标记bool flag=1并结束程序。最后如果flag为零输出NO，时间复杂度为O(n²），n在1到100，可以过。上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main( )
{
	int n,flag=0;
	cin>>n;
	for(int i=1;i<=n;i++)
   	for(int j=1;j<=n;j++)
   	{
  		if(i+j==n&&i%2==0&&j%2==0)
  		{
  			cout<<"YES"<<endl;
  			flag=1;
		}
   	}
   	if(flag==0) cout<<"NO"<<endl;
	return 0;
} 
```
我的解析就到这里，希望能对大家有帮助

---

## 作者：有限光阴 (赞：0)

## 真是一道水题啊!!!
一看就知道是一道小学的题目
### 1.我们知道偶数=偶数+偶数


所以2*n=偶数+偶数

所以可得以下代码
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main(){//主函数
	int a;//定义
	cin>>a;//输入
	if(a%2==0){//判断是否为偶数
		if(a>=4){//因为2不行,所以要特判
			cout<<"YES"<<endl;//输出
		    return 0;
		}
	}
	cout<<"NO"<<endl;//输出
	return 0;//好习惯
}
```
希望大家都可以AC这题

---

## 作者：bym666 (赞：0)

# CF4A 【Watermelon】
在讲这道题目之前，我们先来复习一个小学生都会的知识。
## 奇数=奇数+偶数
## 偶数=偶数+偶数
（不知道什么是奇数偶数的出门右转[奇数](https://baike.sogou.com/v315239.htm?fromTitle=%E5%A5%87%E6%95%B0)[偶数](https://baike.sogou.com/v4798.htm?fromTitle=%E5%81%B6%E6%95%B0)）

这两个公式告诉我们，只要是偶数，就输出YES，不是就输出NO。但是，真的是这样吗？我们提交来看一看。
```
#include <bits/stdc++.h>
using namespace std;
int w;
int main()
{
	cin>>w; 
	if(w%2==0)cout<<"YES";
	else cout<<"NO";
	return 0;
}
```
WA了，这是为什么呢？

偶数里面，有一个数不能分解为两个正偶数，是哪个数呢，是2。所以我们要加一个特判来判断是不是2。

代码如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
int w;
int main()
{
	cin>>w;//输入 
	if(w%2==0)//如果是偶数 
	{
		if(w==2) cout<<"NO";//如果是2，输出NO 
		else cout<<"YES";//如果不是2，输出YES 
	}
	else cout<<"NO";//如果是奇数，输出NO
	return 0;//结束程序 
}
```

---

## 作者：静之城 (赞：0)

# 这是一道水题!
### 我们只要判断是否n是偶数就行，但2不行！
# 上代码！！
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	scanf("%d",&n);
	if(n%2==0&&n!=2)
	{
    		cout<<"YES";
	}
	else                //不是就输入NO
	{
		cout<<"NO";
	}
	return 0;
}
```
### 若嫌这个麻烦
#### 窝老师教了这个
```c
#include<iostream>
#include<stdio.h>
#include<string>
int main()
{
    int n;
    cin>>n;
    printf("%s",(w&1||w==2)? "NO":"YES");//重要！
    return 0;
}//赞赞！！
```
### [ 插个广告---my blog](https://184060.blog.luogu.org/)


---

## 作者：一滴小水滴 (赞：0)

# 这道题简直是不能在水一点了，只需要判断他是不是大于2的偶数就可以啦 
## ~~真的不明白为什么通过率这么低~~
***
## 完整代码（真的只有这一点）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    if(n%2==0&&n!=2)cout<<"YES"<<endl;
    else cout<<"NO"<<endl;    //如果这个数是大于2的偶数就输出"YES",
                              否则输出"NO"。
    return 0;
}
```
***
## 大家早日AC吧

---

## 作者：sycqwq (赞：0)

这题竟然没有过水已隐藏？我真是醉了。。。

题意相信大家都看得懂吧，判断一个数是不是偶数，注意特判一下这个数是2的话直接输出“NO”。
话不多说，直接上代码：

```cpp
#include<bts/stdc++.h>
using namespace std;
int main()
{
  int n;
  cin>>n;
  if(n%2==0&&n!=2) //判断是不是偶数并且不是2
  		cout<<"YES";
  else  
  		cout<<"NO";
    return 0;
}
```

---

## 作者：明空 (赞：0)

~~一道水题~~

**~~众所周知~~**：
除了2以外，所有的正整偶数都能分成两个正整偶数

所以，只要先特判下是不是2，再判断n是不是偶数即可（~~不用判断n是不是正整数，因为输入的都是正整数~~）

上代码
```cpp
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;//输入
	if(n==2)cout<<"NO"; //特判下n是不是2
	else if((n%2)==0) cout<<"YES"; //判断是不是偶数
	else cout<<"NO";
	return 0;
}
```


---

## 作者：Eason6 (赞：0)

蒟蒻第一篇题解QAQ，如有错误，大佬勿喷。


------------
正偶数=正偶数+正偶数

所以先要判断是否为正偶数，而由于最小正偶数为2，因此最小为4。所以要同时满足。（**0不是正数！！！！**）
  

好了，上代码。
```
#include<bits/stdc++.h>//万能头文件
using namespace std;//命名空间
int main(){//主函数
	int a;//定义
	cin>>a;//输入
	if(a<=0){//判断正负
		cout<<"NO";//如为负直接输出
		return 0;//输出后立即退出（节约时间）
	} 
	else if(a%2==0 && a>=4){//判断奇偶且至少为4（两个2至少为四）
		cout<<"YES";
		return 0; //同上
	} 
	else{
		cout<<"NO";
		return 0;
	}//如均不满足，输出“NO”
	return 0;//结束程序
}
```




---

## 作者：来自WTK的路人 (赞：0)

好像还没有人用C，我就来一篇吧。
```
#include <stdio.h>
int main(){
	unsigned int a;scanf("%d",&a);printf("%s",(a&1||a==2)? "NO\n":"YES\n");return 0;//直接判断
}
```
------------
只需一个小学二年级的公式：**偶数=偶数+偶数**
### 2是个特例，因为
# 2只=1+1（在正数范围内！！！！！！）。
## 题目说了One hot summer day Pete and his friend Billy decided to buy a watermelon，不存在0重西瓜~~~~
~~（坑人啊啊啊！！！）~~

---

## 作者：Ace_Radom (赞：0)

这题只需要用一下一个定理：

# 偶数+偶数=偶数
### 即可

但要注意：2是个很特殊的玩意儿

	2 = 0 + 2
      = 1 + 1
      = 2 + 0

0,1都不是偶数

## 所以，2要除去

只需要在开头判断，正确直接输出+return即可

code：

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin >> n;
	if ( ( n % 2 == 0 ) && ( n != 2 ) )  //判断是否满足
	{
		cout << "YES";
		return 0;  //这是个人习惯，else当然可以
	}
	cout << "NO";
	return 0;
}
```

# **华丽结束**

---

## 作者：土川崇贺 (赞：0)

		看见很多dalao直接判断是否为非2偶数，很是羡慕，因为我第一次做就没有想到；还看见有dalao说为什么没有人发布一篇暴力枚举的题解。既然这样，我就发布一篇暴力枚举的题解。    
        暴力枚举十分简单，直接看代码：
```
#include<iostream>
using namespace std;
int main()
{
    long long n; 
    cin>>n;
    for(int i=2;i<=n/2;i+=2) //需要拆分为正偶数，故从2开始枚举；枚举到n-2即可，因为拆法前后对称，如：10=2+8=4+6=6+4=8+2
    {
    	if((n-i)>=2 && (n-i)%2==0) //判断被拆分的两个数是不是正偶数
    	{
    		cout<<"YES"; //输出“YES”
    		return 0; //提前结束程序
		}
	}
	cout<<"NO"; //如果没有提前结束程序，说明不可拆分，输出“NO”
	return 0; //结束程序
}

```
		最后，还请各位julao多多包涵，不要吐槽。

---

## 作者：s5_gan (赞：0)

分为两个正偶数，第一个想法不是正偶数都可以吗？

错！要考虑到2这个数，所以可以加个特判
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int main()
{
    cin>>n;
    if(n==2){
        cout<<"NO";
        return 0;
    }
    if(n%2==0)cout<<"YES";
    else cout<<"NO";
    return 0;
}
```

---

## 作者：Hzq11_ (赞：0)

~~论如何冲刺最短代码~~  
判断其是否是偶数即可。
# 但2要特判!!!
送代码(仅四行):
```cpp
#include <cstdio>
int main(int S){    //变量声明
	return (scanf ("%d",&S),printf (S%2||S==2?"NO":"YES"))&0;
}
```
水题一道

---

## 作者：Aehnuwx (赞：0)

## 实际上，这就是一道数学题。

**敲黑板！**


大家都知道：偶数+偶数~~=~~奇数（用删除线来表示不等于。。看懂就行）。那么偶数+偶数=偶数。因为偶数的字母表达式为$2n$,$2n+2n=4n$。$4n$必定是一个偶数（忍不住普及了一下）


当然：$2$这个数是一个例外。


根据上面的理论，打出代码。


$code$

```cpp
#include <cstdio>
using namespace std;
bool check(int x) {
    if(x == 2) return false;
    if(x & 1) return false;
    return true;
}
int main() {
    int n;
    scanf("%d", &n);
    if(check(n)) printf("YES");
    else printf("NO");
    return 0;
}
```

---

