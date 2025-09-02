# [ARC003A] GPA計算

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc003/tasks/arc003_1

高橋君はアメリカに留学しようと考えており、成績表を提出することになりました。  
 アメリカ留学の成績表には、学力を測る指標であるGPAを表記する必要があります。  
 GPAとは各単位に対する評価(A,B,C,D,F)を点数に換算して平均した値で、点数への換算は以下のようになります。

- A評価 → $ 4 $ 点
- B評価 → $ 3 $ 点
- C評価 → $ 2 $ 点
- D評価 → $ 1 $ 点
- F評価 → $ 0 $ 点
 
 全てF評価だった場合は、GPAは $ 0 $ になります。  
 高橋君の各単位に対する評価をもとにGPAを求めなさい。 入力は以下の形式で標準入力から与えられる。 > $ N $ $ r_{1}r_{2}...r_{N} $

- $ 1 $ 行目は、単位の総数を表す整数 $ N\ (1\ ≦\ N\ ≦\ 100) $ が与えられる。
- $ 2 $ 行目には、単位に対する評価を表す $ N $ 文字の文字列が与えられる。
- $ i $ 文字目の文字 $ r_{i} $ は `A`, `B`, `C`, `D`, `F` のいずれかである。

 入力として与えられた単位の評価をもとにしたGPAを標準出力に $ 1 $ 行で出力せよ。  
 誤差は絶対誤差あるいは相対誤差の少なくとも片方が $ 1e-9 $ 以下であれば許容する。$ (1e-9=10^{-9}) $  
 なお、最後には改行を出力せよ。 ```
<pre class="prettyprint linenums">
34
ABABAAABACDDDABADFFABABDABFAAABFAA
```

 ```
<pre class="prettyprint linenums">
2.79411764705882
```

- 各評価の個数は以下のようになります。
- A評価 … $ 16 $ 個
- B評価 … $ 8 $ 個
- C評価 … $ 1 $ 個
- D評価 … $ 5 $ 個
- F評価 … $ 4 $ 個

- したがって、点数の総和は $ 4×16+3×8+2×1+1×5+0×4=95 $ になり、平均は $ 95÷34=2.79411764705882 $ です。
 
```
<pre class="prettyprint linenums">
5
FFFFF
```

 ```
<pre class="prettyprint linenums">
0
```

- F評価が $ 5 $ つなのでGPAは $ (0×5)÷5=0 $ になります。

# 题解

## 作者：ruler✘_梦 (赞：4)

我想大家一定通过了这道题，接下来我推荐一个~~非常冷门的~~方法——

## switch

不说了，上代码

```c
#include<bits/stdc++.h>//万能头

using namespace std;

int n;
char c[102];

int main(){

    int i,ans=0;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>c[i];

        switch(c[i]){
            case 'A':ans+=4;break;
            case 'B':ans+=3;break;
            case 'C':ans+=2;break;
            case 'D':ans+=1;break;
            default:ans+=0;
        }

    }
    if(ans) printf("%.14f",ans*1.0/n);
    else cout<<0;

    return 0;
}
```


---

## 作者：不到前10不改名 (赞：3)

```
//这种水题还能错，ε=(´ο｀*)))唉，我真弱~
#include<stdio.h>
int srx,i,n;
char sry;
double lhy;
void mzy()
{
    scanf("%d",&n);
    for(i=0;i<=n+1;i++)//奇怪的是为什么我正常做比其他人要多输入两个（想不通~）
    {scanf("%c",&sry);
    if(sry=='A')
    srx+=4;
    if(sry=='B')
    srx+=3;
    if(sry=='C')
    srx+=2;
    if(sry=='D')
    srx+=1;
    else
    srx+=0;}//边输入边累加
}
void zjq()
{
    lhy=srx;//写成lhy=srx/n的后果就是wa~（呜呜呜）
    lhy/=n;
    if(srx==0)
    {printf("0\n");
    return ;}
    printf("%.14f\n",lhy);//回车不说了，小数只要.9f就行了
}
int main()
{
    mzy();//函数名防伪
    zjq();
    return 0;
}
```

---

## 作者：_newbie_ (赞：3)

```c
#include<cstdio>
#include<iostream> 
#include<cmath>
#include<cstring>
using namespace std;
int main()
{
    int n;cin>>n;  //n不用管，只用做末尾除数
    string a;
    cin>>a;
    int ans=0; 
    for(int i=0;i<a.size();i++)
    {
    	if(a[i]=='A') {ans+=4;} //统计分数
    	if(a[i]=='B') {ans+=3;} 
    	if(a[i]=='C') {ans+=2;} 
    	if(a[i]=='D') {ans+=1;} 
    }
    if(ans==0) cout<<0<<endl;  //全是F
    else
    printf("%.14lf\n",(double)ans/(double)n); //保留14位
    return 0;
}
```

---

## 作者：SKTelecomT1_Faker (赞：1)

```cpp
#include<bits/stdc++.h>
using namespace std;
char a[100001];
double n;
signed main( )//谨慎的写法
{
	cin>>n;
	double ans=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++)
	{
		if(a[i]=='A') ans+=4;
		else if(a[i]=='B') ans+=3;
		else if(a[i]=='C') ans+=2;
		else if(a[i]=='D') ans+=1;
		else if(a[i]=='F') ans+=0;
	}//判断是什么之后累加
	printf("%.14lf",ans/n);//不要写成%.14d,会错的
	return 0;
}
```
这题的基本思路为判断输入字符串中有什么样的字母，先用char定义数组后输入，再用for循环依次判断并用累加器ans累加，注意n和ans都要开double，最后用printf输出ans/n的值即可，总的来说比较简单。
希望对大家有帮助。

---

## 作者：Tommy2017 (赞：1)

这道题我用了ASCII码值来做，感觉是个挺新奇的思路QWQ

首先分析一波：

仔细读题可发现这道题他是ABCDF，，，，
对！没有E，所以需要将F单独判断

那么蒟蒻代码（代码里有详解）如下：
```cpp
#include<bits/stdc++.h>
#define re register
template <typename T> inline void read(T &x)//快读 
{
	x=0;int f=1;char c=getchar();
	for(;c>'9'||c<'0';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x*=f;
}
int main()
{
	int n;
	char c;
	read(n);
	int ans=0;
	for(re int i=1;i<=n;++i)
	{
		scanf("%c",&c);
		if(c=='F') continue;//因为没有E！！所以必须要加判断 
		ans+=21-(c-'0');
//A的ASCII码值为65，"0"的为48，那么可算出21-A+"0"=4，BCD同理。 
	}
	printf("%.14lf",ans*1.0/n);//保留14位小数输出 
	puts("");
	return 0;
}
```


---

## 作者：A_Plus_Gu (赞：0)

**考察内容|** 简单模拟、字符串

**思路|** 按照题目说的做即可（这就是模拟）。

**代码|**

```
AT162 GFA計算
此题并不是难题，适合新手（以后都是比我强的大佬）入门
部分代码看不懂可以在下面找到解释
#include<bits/stdc++.h>
#define int long long（Q1A1）
using namespace std;
int n,ans;
signed main(){（Q2A2）
	cin>>n;
	for(int i=1;i<=n;i++){
		char ch;
		cin>>ch;
		if(ch=='A') ans+=4;
		if(ch=='B') ans+=3;
		if(ch=='C') ans+=2;
		if(ch=='D') ans+=1;
	}
	if(ans)printf("%.14f\n",(double)ans/n);
	else puts("0");
	return 0;
}
```
**问答|**

Q1：下面这行代码是什么意思？
```
#define int long long
```
A1：这行代码可以看做将代码中所有的int换成long long。

Q2：signed main()是什么意思？为什么不写成int main()？

A2：由于前面int被define成了long long，如果写int main()的话会被替换成long long main()，会编译错误（CE）。而用signed main()可以避免此错误。

其他的大家就自己去体会啦，其他部分并不是特别难理解。

---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题十分符合红题难度，废话不多说，代码来一波！

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    long long n,he,td;
    char a;//定义变量
    int main()
    {
        cin>>n;//读入n
        td=n;
        while(td>0)//为了和其他大佬区分，用while
        {
            td--;//最终还是读入n次
            cin>>a;//读入当前字符
            if(a=='A')he+=4;//如当前字符是A，he加4
            if(a=='B')he+=3;//如当前字符是B，he加3
            if(a=='C')he+=2;//如当前字符是C，he加2
            if(a=='D')he+=1;//如当前字符是D，he加1
            if(a=='F')he+=0;//如当前字符是F，he不变
        }
        printf("%.14f\n",he*1.0/n);//输出结果并换行
        return 0;//要有好习惯
    }
好了，本蒟蒻就讲到这里，希望对读者有所帮助
    

---

## 作者：WOWHandsome (赞：0)

这题虽然非常简单，但是发现楼下的几个题解都是直接用 `switch / if` 进行枚举 `A ~ D` 的加分。其实并不需要写出如此长的代码。

**创新之处**

1. `getchar` 读入字符，又快又准
2. 使用了一个表达式来处理 `A ~ D` 的加分，详见代码
3. 并没有 `using namespace std` （逃

**坑点**

1. 使用 `float` 会导致精度不足，而部分编译器在本地会给出正确样例
2. 输出 `0` 要特判，否则会输出 小数点后 `14` 个 `0`
3. 必须读掉第一行的换行符

主要都写在注释里面了。因为代码短，就给出 `Sublime Text` 的高亮截图，好看一点~~防抄袭~~。

![](https://ae01.alicdn.com/kf/H82b7671ea0d14f81b2891fdb5fa62aebB.jpg)

好吧还是贴一个源代码 [**here传送门**](https://www.luogu.org/paste/qqcygwdi)

最后，祝大家国庆节快乐~洛谷4越来越好~CSP全都拿省一~

---

## 作者：Higashikata_Jousuke (赞：0)

这道题不难，只要认真看题，就一定会做的 ~~那你写题解干嘛~~

直接上代码

```
#include<cstdio>
//为了printf控制输出小数的位数
#include<iostream>
#include<cstring>
#include<bits/stdc++.h>
//头文件不必多说
using namespace std;
char a;//用a来储存评估等级
int n,s;//s用于统计分数
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a;
        //输入评估等级
        if(a=='A')s+=4;
        else if(a=='B')s+=3;
        else if(a=='C')s+=2;
        else if(a=='D')s+=1;
        else if(a=='F')s+=0;
        //将评估等级所对应的分数累加进s里
    }
    printf("%.14lf",(double)s/(double)n*1.0);
    //输出，用printf把小数控制在14位，总分数和单元数相除得到平均值
    return 0;
    //完美结束
}
```

### 题解仅供参考，题目并不难，只要你认真去想，一定能做出来的，请勿抄袭！qwq

###### 管理给过鸭，辛苦了！qwq


---

## 作者：Hokage (赞：0)


## 这题思路比较简单

### 查找出A，B，C，D的数量
### 分别为 x1，x2 ，x3 ，x4
### sum是总和
### 然后，再
$sum=(x1*4)+(x2*3)+(x3*2)+(x4*1)$
### 最后用sum除于总数取14位输出就好了
### 二话不说，下面献上c++代码

```
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int main()
{
    int k;  //k只是当作最后算平均值的除数 
    int sum=0;//sum是所有分数的总和，当作算平均值的被除数 
    char a[152600];//输入字符串 
    int x1=0,x2=0,x3=0,x4=0;//分别表示A~D的数量 
    cin>>k;
    cin>>a;
    for(int i=0;i<k;i++)//循环查找A~D的数量 
    {
    	if(a[i]=='A')
    	x1++;//A的数量加 1 
    	if(a[i]=='B')
    	x2++;//B的数量加 1 
    	if(a[i]=='C')
    	x3++;//C的数量加 1 
    	if(a[i]=='D')
    	x4++;//D的数量加 1 
    }
    sum=(x1*4)+(x2*3)+(x3*2)+(x4*1);//计算出总和 
    int hahaha=0;//开个玩笑 
    if(sum==0)
    cout<<hahaha<<endl;//直接输出0就可以了 
    else
    printf("%.14lf",(double)sum/(double)k); //依题意保留14位
    return 0;//程序拜拜 
}
```

### 本蒟蒻第一次交题解，求给过

---

## 作者：TRZ_2007 (赞：0)

发现没有人像本蒟蒻一样用$map$的~~  
今天是本蒟蒻第一次打破了$C$党的传统而是用$STL$模板。
首先我们要定义一个$map$函数库中的数组，比如叫$score$吧！定义它的代码如下：
```
#include <stdio.h>
#include <map>//STL模板库中的map库
using namespace std;//注意必须加上这一条！
map<char,int>score;//由于数组下表是字符类型，于是定义成了<char,int>
```
接着再初始化：
```
void init()
{
	score['A']=4;//a等4分
	score['B']=3;//b等3分
	score['C']=2;//c等2分
	score['D']=1;//d等1分
	score['F']=0;//f等0分
}
```
于是，愉快第开始了主程序：
```
int main()
{
	init();//初始化十分重要！
	int n,i;//定义n和i
	double ans=0;//ans初始值为0
	scanf("%d",&n);//读入
	char a[n];//定义长度为n的字符数组
	getchar();//读空格
	for(i=0;i<n;i++)
		scanf("%c",&a[i]);//循环读入，也可以写成gets(a)
	for(i=0;i<n;i++)
		ans+=score[a[i]];//循环累加分数
	double endscore=double(ans/n)*1.0;//相除
	printf("%.14lf\n",endscore);//注意保留14位小数，记得换行
}
```
所有的程序如下（注释在上头，合起来就不放了）：
```
#include <stdio.h>
#include <map>
using namespace std;
map<char,int>score;
void init()
{
	score['A']=4;
	score['B']=3;
	score['C']=2;
	score['D']=1;
	score['F']=0;
}
int main()
{
	init();
	int n,i;
	double ans=0;
	scanf("%d",&n);
	char a[n];
	getchar();
	for(i=0;i<n;i++)
		scanf("%c",&a[i]);
	for(i=0;i<n;i++)
		ans+=score[a[i]];
	double endscore=double(ans/n)*1.0;
	printf("%.14lf\n",endscore);
}
```

---

## 作者：CZQ_King (赞：0)

## 这道题好~~难~~
### 我用了$ascii$码判断，好像字符判断不行啊（我在本地过不了）
~~**小数那么多位是脑抽吗**~~
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a;
double c;//最后要的10^-9小数
char b;//字符b，评估值
int main(){
    cin>>a;
    for(int i=0;i<a;i++){
        cin>>b;
        switch(int(b)){//多重判断b的ascii值
            case 65:c+=4;break;//A的ASCII码为65
            case 66:c+=3;break;//同上
            case 67:c+=2;break;//同上
            case 68:c+=1;break;//同上
            case 70:c+=0;break;//同上
        }
    }
    c=c/a;//求平均数
    cout<<fixed<<setprecision(9)<<c<<endl;//输出小数（好麻烦）
    return 0;//完美结束
}
```

---

## 作者：FCBM71 (赞：0)

  楼下两位cpp大佬已经提供了全面的cpp题解，于是我也用pascal来水一波~~~
 
思路很简单，只用遍历每一个字符，用一个case语句它是A、B、C还是D,再为累加器加上对应的值。(F可以直接不考虑了，反正又没什么影响)

废话不多说，直接上代码：


------------

```pascal
program hrn;
 var
  s:string;
  l,m,i:longint;  //l代表字符串长度,m是累加器
  x:double;       //x是最终成绩
 begin
  readln(l);read(s);  //读入
  for i:=1 to l do
   case s[i] of
    'A':m:=m+4;
    'B':m:=m+3;
    'C':m:=m+2;
    'D':m:=m+1;
   end;               //判断情况&累加
  x:=m/l;             //计算最终成绩
  writeln(x:0:15);    //输出（我是保留的十五位小数，实际上9位就够了）
  readln;readln;
 end.

```


---

## 作者：yuzhechuan (赞：0)

话不多说，上代码


------------

```cpp
#include <bits/stdc++.h>//万能头文件
using namespace std;

int main()
{
    int n,sum=0;//累加器清零
    char c;
    scanf("%d",&n);
    getchar();//读取多余的换行
    for(int i=1;i<=n;i++)
    {
    	scanf("%c",&c);//读入字符成绩
    	if(c=='A')sum+=4;//转成数字成绩后用sum累加为总分
    	if(c=='B')sum+=3;
    	if(c=='C')sum+=2;
    	if(c=='D')sum+=1;
	}
    printf("%.9lf",1.0*sum/n);//用1.0*将本次运算转为实数运算 
			//.9lf为保留小数点后9位（题目要求>=9就行）
}
```

---

## 作者：PC_DOS (赞：0)

本题为字符串模拟题，只需要读入字符串、遍历求总绩点并输出平均绩点即可。

由于C++自身的特性，因此为了得到比较精确的结果，我们应当将读入的用时通过double()转换为双精度型再计算，否则会发生错误。

为了保证精度，输出时可以通过cout.setf(ios::fixed)指定定点输出，并在输出答案前调用setprecision()方法设定小数位数。可能需要引入iomanip头文件。

代码:
```
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	int iLength, iGP=0; //iLength-长度；iGP-总绩点
	register int i; //循环计数器
	string sGrade; //成绩
	while (cin >> iLength >> sGrade){ //读入长度和成绩
		for (i = 0; i < iLength; ++i){ //遍历字符串
			switch (sGrade[i]){ //判断当前位置的成绩符号
			case 'A': //A加4个绩点
				iGP += 4;
				break;
			case 'B': //B加3个绩点
				iGP += 3;
				break;
			case 'C': //C加2个绩点
				iGP += 2;
				break;
			case 'D': //D加1个绩点
				iGP += 1;
				break;
			case 'F': //F加0个绩点
				iGP += 0;
				break;
			default: //非法字符不计
				iGP += 0;
				break;
			}
		}
		cout.setf(ios::fixed); //设置定点输出
		cout << setprecision(15) << double(iGP) / double(iLength) << endl; //输出，勿忘设置精度、类型转换以及换行
		iGP = 0; //计数器清零
	}
	return 0; //结束
}
```

---

