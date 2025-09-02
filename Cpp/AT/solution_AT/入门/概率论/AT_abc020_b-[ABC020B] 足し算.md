# [ABC020B] 足し算

## 题目描述

给定两个正整数 $A$ 和 $B$。请将 $A$ 的十进制表示与 $B$ 的十进制表示（不在前面补零）连接起来，得到一个新的整数。请输出该整数的两倍。

## 说明/提示

### 样例解释 1

$123 \times 2 = 246$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 23```

### 输出

```
246```

## 样例 #2

### 输入

```
999 999```

### 输出

```
1999998```

# 题解

## 作者：Messi李 (赞：24)

题目大意：输入两个正整数a, b 求把a和b拼接起来成为ab的值的两倍。（我不是翻译，只是讨论区的搬运工）

思路：拼起来可以用字符串

代码

```
#include <bits/stdc++.h>
using namespace std;
string a,b;//定义两个字符串
std::string str;
int main(){
    cin>>a>>b;//输入
    str=a+b;//拼起来
    int n = atoi(str.c_str());//string形式转int形式
    cout<<2*n<<endl;//输出
}
```

中间转形式有点难

附上方法:

std::string str;

int n = atoi(str.c_str());

谢谢观看，不要抄袭

蒟蒻求赞

---

## 作者：HOIer_9_42 (赞：6)

这是一段~~令人惊奇~~愚蠢的故事……

```
   /*

   被和谐部分

   */
```

最终，我用自己想出来的类似哈希的方法~~然而时间复杂度为O(n)十分垃圾~~一遍A掉了这道题！！！~~这绝对是个意外~~

好了，下面跟大家分享一下我的较复杂的解法——

1.首先，看到“拼数”这项操作，一想，这不是基础吗??! ^_^可是一看，$A$,$B$的位数是不确定的，如果要暴力模拟还得分类讨论，于是我略加思索了一番，决定使用字符串模拟来解决这道题。

其次，要怎么用字符串类型模拟出奇迹呢？思路（与注意事项）如下——

在把同一个字符串转成长整型变量的时候注意位数进率(即10次幂)的处理~~小学知识？？~~

$For 一个sample：$

$$
123 \to 3\cdot x\cdot 10^0+2\cdot x\cdot 10^1+1\cdot x\cdot 10^2
$$

2.两个不同字符串衔接的处理方法——可以先把第一个字符串转化为整型变量再乘上字符串的长度加上第二个已转化为整型变量的字符串，处理出来的数即为两个数拼在一起的数。很显然的，想一想为什么。

下面给出AC代码——

```cpp
#pragma GCC optimize(3)
#pragma GCC optimize("inline")
#pragma once
#include
#define q register
typedef long long ll;
using namespace std;
string a,b;
ll ansb,ansa,ans,upcent;
  //这里upcent表示把第一个字符串A与
  //字符串B进行衔接的转化率
inline void qwrite(ll v)
{
    if(v>9)   qwrite(v/10);
    putchar(v%10+'0');
} //快写加速   
inline bool juds(ll c)
{
    if(c>=0){
        return true;
           return 0;
    }
    return false;
} 
//这里独立成一个函数其实没什么必要（判断正负）
inline ll qpow(ll a,ll b)
{
    ll ans=1;
    for(q ll i=1;(i-1)^b;i++){
        ans*=a;
    }
    return ans;
}
//史上最垃圾的快速幂，主要是处理10的次幂
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);//cin读入的加快
    cin>>a>>b;
for(q ll i=b.length()-1,j=0;juds(i);i--,j++){
        ansb+=(b[i]-'0')*qpow(10,j);
    }
    //把第二个字符串先转成整型变量
    upcent=qpow(10,b.length());
    //处理衔接时的转化率
for(q ll i=a.length()-1,j=0;juds(i);i--,j++){
        ansa+=(a[i]-'0')*qpow(10,j);
    }
    ans=ansb+ansa*upcent;
    //合并已转化成整型的变量
    ans*=2;
    qwrite(ans);
    putchar('\n');
    return 0;
}
```

感觉已经讲得非常清楚了。最后祝各路巨佬早日AKIOI！~~

---

## 作者：A10Nec37 (赞：4)

# [博客广告](https://zhoushuren.blog.luogu.org/)

# 本题解由[ZCY(ChrisMountain)](https://www.luogu.org/space/show?uid=214934)大佬武装逼更，在此膜拜ZCY神犇　Orz。
### [题目入口](https://www.luogu.org/problemnew/show/AT1266)

**前置知识**

小一 快读（将字符转换为INT）  
小二 循环  
~~小三 四则运算~~

----
**思路**  

对于这道题，我在阅读题面时，想到了另一个基础——快读。读入时，即可完成对数字的处理，省去了再开空间来拼接字符串。  
其他大佬的一些枚举方法，可以使用，但对稍微增强的数据 $(1≤A,B≤10^9)$都变得极其复杂，所以并不推荐。  

---
**具体实现**

![ASCII码表.jpg](https://i.loli.net/2019/05/22/5ce520d3a62de78847.jpg)
↑ ASCII码表，即C++中char类型储存的值

由图（红框圈起）可知，在C++中，'0'字符的值是48，所以，我们将字符转化为数字的方法就显而易见了—— **(ch-48)** 就是ch变为INT的值。  
而转化完后，我们要按题意添加进数字，显而易见，我们只要将要添加的数字乘10，空出个位，就能添加了。

---

下面给出AC代码（完结撒花）：

```cpp
/***************************
Created at 2019-05-17
By A10Nec37 (Richard Guo)
For NOIP 2019
All Rights Reserved
***************************/
#include <cstdio>

int main() {
	char ch = getchar();//getchar()读入一个字符
	int num = 0;//初始值为0
   
	while ( ch != EOF ) { //没读完
		if( ch >= '0' && ch <= '9' ) //读入字符符合条件
			num = num * 10 + ch -48;//这句就是将字符变为数字并添加
        //num*10 就是留出个位
        //ch-'0' 就是将字符变为数字
		ch = getchar();//继续读
	}
   
	printf("%d\n", num*2);//按要求输出
	return 0;
}
```

[**评测结果**](https://www.luogu.org/recordnew/show/19118819)

### 题解虽好，请勿抄袭。最后祝您身体健康。O(∩_∩)O~

---

## 作者：lsyx0918 (赞：1)

这道题主要考察的是string类型转int类型，在这里向大家推荐一个函数：

**atoi()**

这个函数就是用于string类型转int类型的，当然只是给各位蒟蒻们科普一下的。

现在我们开始进入正题，上代码：
```cpp
#include<bits/stdc++.h>//万能头，不建议用
using namespace std;
string a,b;
string str;
//定义字符串
int main()//主函数
{
	cin>>a>>b;//输入
	str=a+b;//拼接
	int n=atoi(str.c_str());//利用atoi()函数转换类型
	cout<<n*2<<endl;//输出
	return 0;//结束
}
```
最后，在提醒一下：

**AT不换行，暴零两行泪**

---

## 作者：meyi (赞：1)

# ~~各位神犇都不看数据范围的吗？~~
## 既然 1<=A,B<=999 ，所以纯暴力就可以过了啊。
## 废话不多说，上代码：
```cpp
#include<cstdio>
main(){
    int a,b;
    scanf("%d%d",&a,&b);
    printf("%d\n",(a*(b>99?1000:b>9?100:10)+b)*2);
    //设b为k位数，a就乘10的k次方，这里用一个三目替代了k的计算。
}
```

---

## 作者：UnyieldingTrilobite (赞：0)

这题······

算个python福利罢。

众所周知python字符串强转int肥肠方便。

于是按题目连接字符串，没了······

不知道有什么好说的罢。

```py
a,b=input().split()#输入
print(int(a+b)*2)#拼接乘2
```

没了，真没了······

---

## 作者：⚡zhangjingcan⚡ (赞：0)

可以用高精度加法的思想。

2x=x+x

所以用高精加法就可以了。

不多说废话，上代码
```c
#include <bits/stdc++.h>
#define f(i,s,n)for(register int i=s;i<=n;++i)//宏
#define ff(i,s,n)for(register int i=n;i>=s;--i)
using namespace std;
int a[20],b[20],c[20];
string add(string s1,string s2){//高精加法
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));//清0，比较保险
	string ans;
	int len1=s1.size();
	int len2=s2.size();
	f(i,0,len1-1)a[len1-i-1]=s1[i]-'0';
	f(i,0,len2-1)b[len2-i-1]=s2[i]-'0';//转换为数字
	int t=0;
	int len=max(len1,len2);
	f(i,0,len-1){
		t+=a[i]+b[i];//进位处理
		c[i]=t%10;
		t/=10 ;
	}
	if(t>0){
	   c[len++]=t;
	}
	ff(i,0,len-1){
		ans+=c[i]+'0';//转换为字符
	}
	return ans;//返回答案
}
int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	string a,b;
	cin>>a>>b;
	a+=b;//接在一起
	cout<<add(a,a)<<"\n";//输出
	return 0;//结束
}

```
//结束，祝大家AC

---

## 作者：Chouquet (赞：0)

用字符串一遍过，~~好轻松的~~

直接把a和b连接起来就可以了

代码如下

```cpp
#include <cstdio>
#include <cstring>
using namespace std;
int main(){
	char a[12],b[5];scanf("%s%s",a,b);//输入a和b
	strcat(a,b);//连接字符串a,b,相当于拼成一个数
	int ans=0;
	for(int i=0;a[i];i++) ans=ans*10+a[i]-'0';//转换为数字
	printf("%d\n",ans*2);//输出乘2的结果
	return 0;
}
```

注：strcat(a,b)字符串连接，作用是将字符串b连接到字符串a的后面，其中
### a的长度一定要足够大！

~~话说Atcoder的题目怎么都那么水？~~

---

## 作者：stry (赞：0)

这题的思路很简单：一共分为3种情况，
#### 第一是b为一位数，a*10+b就是新生成的数
#### 第二是b是两位数，a*100+b就为新生成的数
#### 第三是b是三位数，a*1000+b就为新生成的数
接下来再把组成的数*2就是答案了。
### 接下来是程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,xs=1,bb;
	cin>>a>>b;
	if(b/100>=1){xs=a*1000+b;bb=1;} 
	if(b/10>=1&&bb!=1){xs=a*100+b;bb=1;} 
	if(bb!=1){xs=a*10+b;}
	cout<<xs*2; 
    return 0;
}
```
### 这个程序对应的分值是：
![](https://cdn.luogu.com.cn/upload/image_hosting/evlexjpv.png)
### 0分
我想了一下原来是岛国题。
$\color{red}\text{岛国题要换行！}$ 
## 又一个程序：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,xs=1,bb;
	cin>>a>>b;
	if(b/100>=1){xs=a*1000+b;bb=1;} 
	if(b/10>=1&&bb!=1){xs=a*100+b;bb=1;} 
	if(bb!=1){xs=a*10+b;}
	cout<<xs*2<<"\n"; 
    return 0;
}
```
## 这个程序对应的分值是：
![](https://cdn.luogu.com.cn/upload/image_hosting/0jt17ku8.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
## 50分
我又看了看，$\color{red}\text{发现了变量初始值没赋值为零}$，
# 又一个程序:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,b,xs=1,bb=0;
	cin>>a>>b;
	if(b/100>=1){xs=a*1000+b;bb=1;} 
	if(b/10>=1&&bb!=1){xs=a*100+b;bb=1;} 
	if(bb!=1){xs=a*10+b;}
	cout<<xs*2<<"\n"; 
    return 0;
}
```
# 这次对应的分值是：
![](https://cdn.luogu.com.cn/upload/image_hosting/9n1amf8u.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
# 100分



---

## 作者：qyuqxun (赞：0)

python有以下好处 input读入类型字符串
字符串可以直接转换 int字符串相加是直接加在后面 所以
代码如下
```python
a, b = raw_input( ).split( ) 
c=a+b
print int(c)*2
```


---

## 作者：yazzkl (赞：0)

## Q:看似是字符串操作？
## A:是的，但也可以用纯数学方法
因为看见了把**数字拼在一起**，联想到了**位值原理**

看两个数的数据范围，不大。也才0~999

## ------->好像可以分类讨论

讨论第二个数字，看它是几位，再确定第一个数乘以10的几次方。

# code
```
#include <string>
#include <iostream>
using namespace std;
int main(void){           //做个实验，不要学我
  int a,b,jieguo;
  cin >> a >> b;
  int x;                  //看a乘几
  if(b < 10){             //枚举  
    x = 10;               //情况一
  }else if(b < 100){
    x = 100;              //情况二
  }else{
    x = 1000;             //情况三
  }
  jieguo=a*x + b;            //位值原理
  cout << 2*jieguo << endl;
}

```
这道题告诉我们，，，敢于枚举。不要想太多。

---

## 作者：PC_DOS (赞：0)

这是一道模拟题，要求将输入的两个数字连接起来并计算所得数字的两倍，一般来说有两种思路: 数学处理和字符串

### 第一种思路: 直接以数字的形式读入两个数字，之后计算第二个数字的位数L，将第一个数字乘上10的L次方后与第二个数字相加。

计算一个十进制数字N的位数L，可以使用以下公式:

```
L=int(log10(N))+1;
```

所以得到代码:

```
#include <iostream>
#include <cmath>
using namespace std; //头文件和命名空间
int main(){
    ios::sync_with_stdio(false); //输入输出加速
    int iNum1,iNum2,iLength; //两个数字和第二个数字的长度
    cin>>iNum1>>iNum2; //读入两个数字
    iLength=log10(iNum2) + 1; //计算第二个数字的长度
    iNum2+=iNum1*pow(10,iLength); //将第一个数连接到第二个数字的前面
    cout<<2*iNum2<<endl; //输出答案，勿忘换行
    return 0; //结束
}
```

### 第二种思路: 以字符串的形式读入两个数字，执行字符串拼接操作之后转换成数字。

在这里可以通过C++提供的 **字符串流(StringStream)** 来实现字符串的拼接和转换工作，字符串流包含在头文件`<sstream>`中，使用时需要定义一个StringStream对象:

```
stringstream ssStream;
```

StringStream重载了插入运算符<<和提取运算符>>，只需要像平时使用输入输出流一样使用即可。但是务必注意，使用完StringStream之后最好执行一次clear()操作以免导致后续调用时发生潜在的错误。

代码:

```
#include <iostream>
#include <string>
#include <sstream>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	stringstream ssStream; //定义字符串流对象
	string sNum1, sNum2; //两个数字
	int iNum; //拼接后的数字
	cin >> sNum1 >> sNum2; //读入数字
	ssStream << sNum1 << sNum2; //插入字符串流
	ssStream >> iNum; //提取
	ssStream.clear(); //清空字符串流
	cout << iNum * 2 << endl; //输出答案，勿忘换行
	return 0; //结束
}
```

---

## 作者：emm··· (赞：0)

好像没有我的做法。。。

暴力把B的长度算出来，然后再将A乘上相应的数
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int a,b,w;
	scanf("%d%d",&a,&b);
	if(1<=b && b<=9) w=10;
	if(10<=b && b<=99) w=100;
	if(100<=b && b<=999) w=1000;
	printf("%d\n",(a*w+b)*2);
	return 0; 
}
```

---

## 作者：climax (赞：0)

这道题太简单了！先输入两个数，再用一个while循环统计第二个数有几位（好进行拼接）。然后我们再把这两个数接在一起，再乘以2就可以了!
上AC代码：
```c
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,l,d=1;//d是用来统计第二个数的位数的。
	cin>>n>>m;//输入
    l=m;//由于等下还要对m进行操作，所以把m的值给l。
	while(l>0)//开始统计第二个数有几位。
	{
		d*=10;//每去掉一位，d的位数就加1个。
		l/=10;//去位。
	}
	n=n*d+m;//拼接。
	cout<<n*2<<endl;//最后输出n乘2，记得换行。
	return 0;//完美结束。
}
```

---

## 作者：wubaiting2020 (赞：0)

题意：输入两个正整数a, b 求把a和b拼接起来成为ab的值的两倍。

1 <= a, b <= 999


------------
思路：先读入，再循环算出b的数位s，最后把（a*10^s+b）*2即为解。


------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
int a,b,x=0,s=0;
cin>>a>>b;
x=b;
while(b!=0)//循环算出b的数位
{
s++;
b/=10;
}
x=(x+a*pow(10,s))*2;//计算ab*2
cout<<x<<endl;
return 0;
}
```

---

