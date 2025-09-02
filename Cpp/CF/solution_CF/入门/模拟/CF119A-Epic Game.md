# Epic Game

## 题目描述

Simon和Antisimon在玩石子游戏。

共有n颗石子，Simon先拿。

Simon能拿当前n和a的最大公约数，Antisimon能拿当前n和b的最大公约数。

当有一个人不能拿时（n=0）那个人就输了。

求谁赢了。

## 说明/提示

gcd(0,x)=gcd(x,0)=x;

对于样例1：

Simon拿gcd(3,9)=3颗

Antisimon拿gcd(5,6)=1颗

Simon拿gcd(3,5)=1颗

Antisimon拿gcd(5,4)=1颗

Simon拿gcd(3,3)=3颗

Antisimon输了

感谢@引领天下 提供的翻译

## 样例 #1

### 输入

```
3 5 9
```

### 输出

```
0```

## 样例 #2

### 输入

```
1 1 100
```

### 输出

```
1```

# 题解

## 作者：引领天下 (赞：5)

此题很简单，直接模拟即可。

思路不多说，相信大家都知道。

代码：
```cpp
#include <cstdio>
int a,b,n;//同题面
bool turn;//到谁了
int gcd(int a,int b){return !b?a:gcd(b,a%b);}//求最大公约数
int main(void){
    scanf ("%d%d%d",&a,&b,&n);
    while (n)n-=gcd(n,turn?b:a),turn=!turn;//模拟，n-石子，换下一个人
    //n=0即有人输时退出
    printf ("%d",!turn);//turn是输的人，求赢的人直接取反
}
```

---

## 作者：云浅知处 (赞：4)

第一步，审题：
***
>Simon和Antisimon在玩石子游戏。

>共有n颗石子，Simon先拿。

>Simon能拿当前n和a的最大公约数，Antisimon能拿当前n和b的最大公约数。

>当有一个人不能拿时（n=0）那个人就输了。

>求谁赢了。
***

第二步，大致思路：
***
$1.$定义整形变量$\operatorname{a,b,n,turn}$并输入。其中$\operatorname{turn}$是用来记录此时轮到的那个人的。

$2.$将$n$减去$a,n$的最大公因数，交换$a,b$。

(这里交换$a,b$就可以达到Simon与Antisimon轮流拿棋子的效果。)

$3.$如果$turn$此时是$1$，变成$0$；如果是$0$，变成$1$。
***
第三步，一步一步写代码实现思路：
***
$1.$实现最大公因数：

可以使用$\operatorname{C\footnotesize{++}}$中自带的```__gcd(a,b)```，其返回值为$a,b$的最大公因数。
***
$2.$实现交换$a,b$

可以使用$\operatorname{C\footnotesize{++}}$中自带的```swap(a,b)```，它没有返回值，作用是将$a,b$的值互换。
***
$3.$实现$turn$在$0$与$1$之间的互换
***
一种思路是狂打```if```：
```cpp
if(turn==1){//如果turn的值是1
    turn=0;//将turn的值变成0
    break;//立刻结束程序，不然在下一个if判断中turn还会变回1
}
if(turn==0){//同上
    turn=1;
    break;
}
```
***
不过我们还有更优的思路：

### 采用以2为模的算术！

具体操作只有一行：
```turn=(turn+1)%2```

这是，$turn$就能从$0$变成$1$，从$1$变成$0$了。

原理如下：
***
当$turn$的值是$0$时，$(turn\small+1)\mod2$（也就是$turn$除以$2$的余数）的值就是$(0+1)\mod2=1;$

当$turn$的值时$1$时，$(turn\small+1)\mod2$的值就是$(1+1)\mod2=0$

综上所述，这一行算式可以实现$turn$在$0$和$1$之间的互换。
***
第四步：开写代码！
***
```cpp
#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;


int main(){
	int a,b,n,turn=1;//a,b,n同题意。turn的初始值要设成1，因为第一个拿的人时Simon，而如果刚开始就没有了石头（虽然这不可能），那么Simon就输了，会输出1.
	cin>>a>>b>>n;//输入

	while(n>0){//当n大于0时，循环将会继续，游戏也在进行，两人还在拿石头
		n-=__gcd(a,n);//将n减去a与n的最大公因数，也就是Simon/Antisimon拿了这么多石头
		swap(a,b);//将a,b互换，如果刚刚Simon拿了石头(减去的是a与n的最大公因数)，下一次拿的就是Antisimon啦(下一次减去b与n的最大公因数)。反之亦然。
		turn=(turn+1)%2;//如果turn是0，把turn变成1；如果turn是1，把turn变成0
	}//游戏结束

	cout<<turn;//输出胜利者
	return 0;//程序结束
}
```
这里有一个[奇葩注释](https://www.luogu.com.cn/blog/wwwluogucn/ji-pa-zhu-shi)版本，如果您很闲，可以点进去看看
***
最后：

$\Huge\color{red}\textrm{共创文明洛谷，拒绝Ctrl+C!!!}$

---

## 作者：hensier (赞：1)

本题要求求最大公因数，因此有两种主流的方法。

【方法$1$：普通】

```cpp
int gcd(int a,int b)
{
    while(a%b)//只要a%b不为0就一直做下去
    {
        int t=a%b;//取a%b
        a=b;
        b=k;//辗转相除
    }
    return b;//返回b
}
```

【方法$2$：递归】

```cpp
inline int gcd(int a,int b){return !b?a:gcd(b,a%b);}//递归大法——如果b为0就返回a，否则返回gcd(b,a%b)——写起来简便但时间消耗较多（递归的弱点）
```

本蒟蒻在把递归函数写成$\#define$ $gcd(a,b)!b?a:gcd(b,a\%b)$，结果酿成大祸。因为宏定义中没有办法使用递归。这也是一个需要注意的地方。

接下来就进入代码部分：

```cpp
#include<cstdio>
inline int gcd(int a,int b){return !b?a:gcd(b,a%b);}//gcd函数
int a,b,n,s[2],t;//a,b,n为输入，t其实可以定义为bool类型，保存现在轮到谁，s数组表示取n和a还是b的最大公约数的值，方便计算、无需判断
int main()
{
    scanf("%d%d%d",&a,&b,&n);
    s[1]=a;
    s[0]=b;//初始化
    while(1)
    {
        t=!t;//每一次t就换一次
        if(!n)//如果n=0就输出赢的一方并退出程序
        {
            printf("%d",t);
            return 0;
        }
        n-=gcd(n,s[t]);//否则总数减对应值
    }
}
```

---

## 作者：judgejudge (赞：1)

# 比较通俗易懂！！


------------

首先我们看，这其实是一道模拟。所以我们的核心是**不断减去最大公约数**。

下面说一下思路：

1. 用while语句，当n>0时，轮数+1
  
1. **如果轮数是奇数，减去gcd(n,a)；如果轮数是偶数减去gcd(n,b)**
 
2. 输出(轮数+1）模2

为什么输出这么奇怪？因为0和1可以直接联想到**2进制**！

**轮数是奇数时，Simon取；**

**偶数时，Antisimon取。**

**但最后Simon赢输出0，所以轮数要加1！**

注意:algorithm既然叫c++标准模板库（STL），里面有一大堆模板函数，直接调__gcd就好辽！

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int i,j,k,n,a,b,groud=0;
	cin>>a>>b>>n;
	while(n>0){
		groud++;//轮数+1
		if(groud%2==1)n-=__gcd(n,a);
		else n-=__gcd(n,b);//判断是模谁的
	}
	cout<<(groud+1)%2<<endl;//（轮数+1）%2
	return 0;
}
```

---

## 作者：打表大蒟蒻 (赞：0)

这道题是一道求最大公因数的水题啊。蒟蒻我迅速用gcd秒掉这道题后，顺便看了看题解，结果惊奇地发现，发题解的人似乎都对STL很感兴趣，用一些STL里的奇奇怪怪的函数做这道题，因此我就发一篇~~正常点的~~题解吧

求最大公因数是数学里的一个重要思想，在计算机编程里也有重要的~~坑人~~作用，在以前，我们很可能会把他们的因数直接暴力枚举，这样也确实能在一些水题中靠数据的水成功通过，但是，时代在变化，枚举因数的方法现在在大部分题目中行不通，并以其低效容易TLE的特性被我们摒弃在求最大公因数的方法之外，因此，我们引进更高效的算法——辗转相除法，又名欧几里德算法。

算法来源：
设两数为 a、b(a>b)，求 a 和 b 最大公约数(a，b)的步骤如下：用 a 除以
b，得 a÷b=q......r1(0≤r1)。若 r1=0，则(a，b)=b；若 r1≠0，则再用 b 除
以 r1，得 b÷r1=q......r2 (0≤r2）.若 r2=0，则(a，b)=r1，若 r2≠0，则继
续用 r1 除以 r2，……如此下去，直到能整除为止。其最后一个为被除数的余数的
除数即为(a, b)。
例如：a=25, b=15，a/b=1......10, b/10=1......5,10/5=2.......0,
最后一个为被除数余数的除数就是 5,5 就是所求最大公约数。

现在我们就可以用辗转相除法来编写求最大公约数的程序，代码如下
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a, b;
int gcd(int a,int b)  //定义 gcd 函数 
{
	while (a%b!=0){
		int k=a%b;  //k 是 a 除以 b 的余数
		a=b;  //类似于迭代
		b=k;  
	}
	return b;  //返回b
}
int main ()
{
	int a, b;
    cin>>a>>b;
    cout<<gcd(a,b)<<"\n";
    return 0;
}
```
现在我们可以做这道题了
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, a, b;
int gcd(int a,int b)  //定义 gcd 函数 
{
	while (a%b!=0){
		int k=a%b;  //k 是 a 除以 b 的余数
		a=b;
		b=k;
	}
	return b;
}
int main ()
{
	scanf("%d %d %d",&a,&b,&n); //标准输入 
	bool k=true;
	while(n>0)  //开始循环
    {
		if(k) n-=gcd(n,a);  //根据题意模拟
		else n-=gcd(n,b);  
		k=!k;  //把k的值颠倒，代表到下一个人了
	}
	if(!k) printf("0");  //输出0
	else printf("1");   //输出1
	return 0;  //完美结束
}
```
是不是很简单呢？
对了，再多说一句这种算法的时间复杂度是O(logN)

顺便吐槽一下，CF的题UKE的几率真的太高了

---

## 作者：不到前10不改名 (赞：0)

//部分博弈论思想+gcd
```
#include<stdio.h>
int n,a,b,i=1;//初值为1，Simon先拿
int lgx(int x,int y)//欧几里得算法
{
    int i;
    while(y)//撵转相除法，求出最大公约数
    {i=x%y;//利用相除取余算出，如果不明白可以百度
    x=y;
    y=i;}
    return x;
}
int main()
{
    scanf("%d%d%d",&a,&b,&n);
    while(n)
    {if(i%2)//判断轮到谁去石子（其实也可以预先记录gcd（a，n），gcd（b，n）的值）
    n-=lgx(a,n);//模拟取石子的状态
    else
    n-=lgx(b,n);
    i++;}//换人
    if(i%2)//判断，此处轮到谁拿谁输（因为此时不能拿了...所以应该拿的人输）
    printf("1");//一开始打反了..然后....
    else
    printf("0");
    return 0;
    }
//qwq
```

---

## 作者：A_Đark_Horcrux (赞：0)

这题主要就是模拟，找最大公约数，然后一直减就是了

值得一提的是我的代码中__gcd函数包含在algorithm头文件里，是可以直接调用的，妈妈再也不用担心我不会写gcd了！

代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
    int n,a,b; bool k=0;
    cin>>a>>b>>n;
    while(n>0)
    {
        k==0?n-=__gcd(n,a):n-=__gcd(n,b);
        k=!k;//相反操作
    }
    cout<<!k;//这里要输出轮到的那一方，所以要再做一次相反操作
    return 0;
}
```

简单

---

## 作者：wushuang0828 (赞：0)

又一道水题……

思路：用i来表示是Simon拿还是Antisimon拿，如果是，再判断，是Simon拿还是Antisimon拿，如果是Simon拿就求a和n的最大公约数，否则求b和n的最大公约数，n再减去这个最大公约数，最后判断谁输了

废话不多说，Pascal的AC代码：
```pascal
var
 i,n,k,a,b:longint;
function gcd(x,y:longint):longint;//求最大公约数的函数
begin
 if x mod y=0 then exit(y)
              else exit(gcd(y,x mod y));
end;
begin
 readln(a,b,n);//输入
 while n>0 do
  begin
   inc(i);//i可以判断是谁拿石子
   if i mod 2=1 then k:=a
                else k:=b;//判断是求哪两个数的最大公约数
   n:=n-gcd(k,n);//总石子数减去要拿的石子数
  end;
 if i mod 2=1 then writeln(0)
	          else writeln(1);//判断是谁输了
end.
```

---

