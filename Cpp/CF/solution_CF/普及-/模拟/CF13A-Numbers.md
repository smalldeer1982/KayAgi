# Numbers

## 题目描述

Little Petya likes numbers a lot. He found that number 123 in base 16 consists of two digits: the first is 7 and the second is 11. So the sum of digits of 123 in base 16 is equal to 18.

Now he wonders what is an average value of sum of digits of the number $ A $ written in all bases from $ 2 $ to $ A-1 $ .

Note that all computations should be done in base 10. You should find the result as an irreducible fraction, written in base 10.

## 说明/提示

In the first sample number 5 written in all bases from 2 to 4 looks so: 101, 12, 11. Sums of digits are 2, 3 and 2, respectively.

## 样例 #1

### 输入

```
5
```

### 输出

```
7/3
```

## 样例 #2

### 输入

```
3
```

### 输出

```
2/1
```

# 题解

## 作者：BYWYR (赞：7)

这道题就是 gcd 和 进制转换

gcd方法如下：

辗转相除法

```cpp
int gcd(int big,int small){
    if(small==0) return big;
    return gcd(small,big%small);
}
```


------------
而进制转换在c++中，可以用取余数的方法：

```cpp
int deal(int k,int x){
    int num[100005],cnt=0;
    while(x>0){
        cnt++;
        num[cnt]=x%k;
        x/=k;
    }
}
```


------------
代码：

```cpp
#include<iostream>
using namespace std;
int n,fenzi,fenmu,g;//变量有点low，望谅解QAQ
int gcd(int big,int small){//采用了辗转相除法
    if(small==0) return big;
    return gcd(small,big%small);
}
int deal(int k,int x){//采用取余求进制，和加到sum里，记得sum=0
    int sum=0;
    while(x>0){
        sum+=x%k;
        x/=k;
    }
    return sum;
}
int main(){
    cin>>n;
    for(int i=2;i<=n-1;i++)
        fenzi+=deal(i,n);//从2~n-1累加
    fenmu=n-2;//一共累加了几次
    g=gcd(fenzi,fenmu);//最大公约数
    fenzi/=g;
    fenmu/=g;//约分
    cout<<fenzi<<'/'<<fenmu;//输出
    return 0;//养成好习惯
}

```

---

## 作者：hensier (赞：3)

这道题的核心是进制转换以及$gcd$。

我们任意取一个十进制数$N$和进制基数$p$。
这里令$N=41238,p=14$。

转换过程：（用$Rn$表示余数为$n$）

|序号|当前被除数|除法运算|商|余数|
| :----------: | :----------: | :----------: | :----------: | :----------: |
|$1$|$41238$|$÷14=$|$2945$|$R8$|
|$2$|$2945$|$÷14=$|$210$|$R5$|
|$3$|$210$|$÷14=$|$15$|$R0$|
|$4$|$15$|$÷14=$|$1$|$R1$|
|$5$|$1$|$÷14=$|$0$|$R1$|

我们将上表的余数倒过来，得：

$(41238)_{10}=(11058)_{14}$

我们~~通过某种方式~~来验证结果是否正确：

![](https://cdn.luogu.com.cn/upload/image_hosting/cvth6h8g.png)

通过这种取余数并颠倒的方式，对于$n,p∈Z$可以实现$n_{10}->m_{p}$的转换。转换方式为：（$F(a,b)$在这里为临时定义的函数，表示的是能满足$b^{F(a,b)}\le a$的最大整数（$a,b$为参数））

|序号|当前被除数|除法运算|商|余数|
| :----------: | :----------: | :----------: | :----------: | :----------: |
|$1$|$n$|$÷p=$|$\lfloor\frac{n}{p}\rfloor$|$n-p\lfloor\frac{n}{p}\rfloor$|
|$2$|$n-\lfloor\frac{n}{p}\rfloor$|$÷p=$|$\lfloor\frac{n-\lfloor\frac{n}{p}\rfloor}{p}\rfloor$|$n-\lfloor\frac{n}{p}\rfloor-p\lfloor\frac{n-\lfloor\frac{n}{p}\rfloor}{p}\rfloor$|
|$...$|$...$|$...$|$...$|$...$|
|$F(n,p)$|$1$|$÷p=$|$0$|$1$|

根据上述方式，我们归纳出函数代码。

$gcd$函数其实更加好办——可以通过递归的方式，即：

```cpp
int gcd(int x,int y)
{
    if(!y)return x;
    return gcd(y,x%y);
}
```

结合上述方法，我们可以得出代码：

```cpp
#include<cstdio>
#define f(x,y,z)for(int i=x;y;i+=z)//宏定义for函数，更加方便
int n,a[1000],j,s;
int gcd(int x,int y)//gcd函数
{
    if(!y)return x;
    return gcd(y,x%y);
}
void transfer(int k,int t)//转换函数
{
    j=0;//初始化
    while(k)
    {
        a[j++]=k%t;//每一次j先处理再加1，取余
        k/=t;//除以t，整除
    }
    f(j-1,i>=0,-1)s+=a[i];//求和（注意这里s为全局变量）
}
int main()
{
    scanf("%d",&n);//输入n
    f(2,i<n,1)transfer(n,i);//(2,n)进制转换
    printf("%d/%d",s/gcd(s,n-2),(n-2)/gcd(s,n-2));//最简分数形式输出
}
```

---

## 作者：_Legacy (赞：2)

#### 分析
代码分为两部分：

1. 计算各进制各位之和
2. 计算各位之和与进制数是否可约分

计算原理：

将一个十进制数(n)转成 i 进制数时它的位数(s)计算方式为：
```
while(n>0){
	n/=i;
	s++;
}
```
但这次和他的位数没有关系，只要看他各位之和。

而他的每一位都是用“n%i”求的(求完每一位要n/=i)。

所以样例一中5的二进制格式为：```101```

而二进制转十进制的方法是求每一位(a)的值$(i^a)$X每一位的数，

$1\times2^2+0\times2^1+1\times2^0=5$

#### 上代码
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int ans=0;
	int n,m,x;
	cin >> n;
	for(int i=2;i<n;i++){
		m=n;//备份
		while(m>0){
			ans+=m%i;
			m-=m%i;
			m/=i;
		}//计算 i 进制里各位和
	}
	x=n-2;//从二进制到(n-1)进制
	for(int i=2;i*i<ans;i++){
		while(ans%i==0&&x%i==0){
        	//得用 while ，不是 if
			ans/=i;
			x/=i;
		}
	}//约分
	cout << ans << '/' << x;
} 
//CF13A
```

---

## 作者：打表大蒟蒻 (赞：2)

这题其实不太难，明明就是一道红题。

对于这道题，我们需要定义俩函数，一个用来转换进制，一个用来求gcd，转换进制的方法运用到了数学上的短除法，边%边/。gcd用递归写，模板背都能背下来了，也不必说了。

下面上代码（这里用到了函数的提前声明，码风较丑，不喜勿喷）
```cpp
#include <stdio.h>
using namespace std;  //加上这句话表示我仍心系C++
int gcd(int,int), jz(int,int); //提前声明函数，便于调用
int main ()
{
	int n, s=0, x;  //定义变量
	scanf("%d",&n);  //C语言读入
	for(int i=2;i<n;i++) s+=jz(n,i);  //累加一下
	x=n-2;  //从2到n-1只有n-2个数
	int z=gcd(s,x);  //取最大公约数
	s/=z;  //约分
	x/=z;  //约分
	printf("%d/%d",s,x);  //C语言输出
	return 0;  //警告！！！程序并没有完全结束
}  //最后写函数
int gcd(int x,int y)  //求最大公约数的函数
{
	if(y==0) return x;
	return gcd(y,x%y);
}
int jz(int k,int p)
{
	int sum=0;
	while (k){
		sum+=k%p;  //短除法
		k/=p;  //消去最后一位
	}
	return sum;  //返回数字和
}
```


---

## 作者：PC_DOS (赞：2)

只需要模拟一遍从2到iNum-1进制的转换，每转换出一位就将这一位加到累加器iSum上，最后计算iSum和iNum-2的最大公约数iGCD，并将iSum和iNum-2分别除以iGCD并输出即可。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
long long GetGreatestCommonDivision(long long iNum1, long long iNum2){ //辗转相除法求最大公约数
	if (iNum2 == 0)
		return iNum1;
	else
		return GetGreatestCommonDivision(iNum2, iNum1%iNum2);
}
int main(){
	ios::sync_with_stdio(false); //输入输出加速
	long long iNum, i, iTemp, iSum = 0,iGCD; //iNum-输入的数；i-循环计数器；iTemp-进制转换时的临时变量；iSum-累加器；iGCD-存放iSum和iNum-2的最大公约数
	cin >> iNum; //读入数
	for (i = 2; i <= iNum - 1; ++i){ //模拟一遍从2到iNum-1进制的转换
		iTemp = iNum; //将iTemp恢复到iNum
		while (iTemp != 0){ //开始进制转换，iTemp=0时终止循环
			iSum += iTemp%i; //计算一位数并累加
			iTemp /= i; //除去进制数
		}
	}
	iNum -= 2; //从2到iNum-1共有iNum-2种进制，故减去2
	iGCD = GetGreatestCommonDivision(iSum, iNum); //计算iSum和iNum-2的最大公约数
	iSum /= iGCD; //约分分子
	iNum /= iGCD; //约分分母
	cout << iSum << '/' << iNum; //输出分数
	return 0; //结束
}
```

---

## 作者：LYR_ (赞：1)

这题是个水题，
### 只需要会10转P进制就行了。
PS：答案需要约分，可以直接用c++自带函数__gcd(x,y)。
```cpp
#include<bits/stdc++.h>
using namespace std;
int jz(int x,int p) {
	int s=0,a;
	while(x>0) {//10转P进制
		a=x%p;
		s+=a;//直接将算出的哪一位加上
		x/=p;
	}
	return s;
}
int main() {
	int A,x=0;
	cin>>A;
	int y=A-2;
	for(int i=2;i<A;i++) {//循环从2到A-1
		int t=jz(A,i);
		x+=t;
	}
	int d=__gcd(x,y);//最大公约数函数
	x/=d;y/=d;//约分
	cout<<x<<"/"<<y<<endl;
	return 0;
}

```


---

