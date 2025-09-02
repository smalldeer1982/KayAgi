# 整数割り算

## 题目描述

两个实数A,B(B!=0)被赋值后,除法A/B的结果我认为是谁都知道的.

对于这个问题,两个整数A,B(B!=0)被赋值后,请写出计算整数除法A DIV B的程序.

在这里,整数除法A DIV B的意思是,当A,B为实数时将A/B计算结果的小数部分忽略而得到的整数.

例如,4 DIV 3的结果就是4/3=1.3333...的小数部分忽略后得到的1,4 DIV (-3)的结果就是4/(-3)=-1.3333...的小数部分忽略后得到的-1.

另外,8/2=4=3.9999...,但是,当A/B为整数时,A/B就要作为A DIV B的结果.也就是说8 DIV 2=4.

## 说明/提示

- 0<=T<=10^6
- -2^63<=A,B<=2^63
- B!=0

感谢@神云_cloud 提供的翻译

# 题解

## 作者：Yoo_ (赞：3)

这道题是真的坑。。。首先我们要看范围，要开longlong，其次，1号数据要特判，因为有一个地方longlong也没办法。。。
其他的就是正常的除法
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n;
    scanf("%lld",&n);
    long long a[n+5],b[n+5];//害怕越界
    for(register int i=1;i<=n;i++)
    {
    	scanf("%lld%lld",&a[i],&b[i]);//正常读入
    }
    for(register int i=1;i<=n;i++)
    {
    	if(a[i] == LLONG_MIN && b[i] == -1)//这就是坑点，要特判
    	    puts("9223372036854775808"); //特判输出
        else
            printf("%lld\n",a[i]/b[i]);//正常输出(这才是常规操作)
    }
    return 0;//终于结束这个毒题
}
```

---

## 作者：云浅知处 (赞：1)

这题真的非常非常坑

注意：

$1.$一定要开$\text{long long}$

$2.$ $\text{long long}$ 的范围是 $\small-\normalsize2^{63}\sim2^{63}\small-\normalsize1$。

但是这题有一种神奇的情况：当 $a=-2^{63},b=-1$ 时，$a\div b=2^{63}$ ，刚好比 $\text{long long}$ 所能存储的的最大数大$1$

于是需要特判 $a=-2^{63},b=-1$ 的情况。
***
接下来：开写代码！

```cpp
#include<bits/stdc++.h>//万能头棒棒哒
using namespace std;
long long a,b,n;//a,b,n如题意
int main(){
	scanf("%lld",&n);//输入数据组数
	for(long long i=1;i<=n;i++){//循环n次，注意i要设成long long型的数
		scanf("%lld%lld",&a,&b);//输入a,b
		if(a==-9223372036854775808&&b==-1){//特判，如果 a=-2³²=-9223372036854775808,b=-1,那么就会爆long long
			printf("9223372036854775808\n");//输出答案"9223372036854775808"，记得换行
		}
		else{//如果没有爆long long
			printf("%lld\n",a/b);//正常输出a÷b，记得换行
			//这里不需要特意搞什么 floor,(int) 之类的，由于a,b都是长长整形数，它们的商也会自动变成长长整形数，会自动向下取整
		}
	}
	return 0;//完结撒花
}

```

---

## 作者：勘探员·引魂人 (赞：1)

**前言：这么少人发题解吗？**

**思路：输出a/b（需特判）**

```
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<string>
#include<cstring>
#include<cmath>
#include<cfloat>//文件头，我与你不打不相识
using namespace std;
long long n;//定义n
long long a,b;//定义a,b
int main()
{
	scanf("%lld",&n);//输入n
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a,&b);//输入a,b
		if(a==-2147483647&&b==-1) cout<<"9223372036854775808"<<endl;//特判（记得换行）
		else cout<<a/b<<endl;//输出a/b（记得换行）
	}
	
	return 0;//结束“题解 AT786【整数除法】”
}
```

---

## 作者：LiveZoom (赞：0)

# AT786 整数割り算 题解
## 这可能是史上最坑爹OI题目了
- 1.要开long long
- 2.当a=-9223372036854775808,b=-1时会爆long long！！！
唉，交了我3遍。上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b;
int t;
int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&a,&b);
		if(a==-9223372036854775808&&b==-1)printf("9223372036854775808\n");
		else{
			long long ans;
			ans=a/b;
			printf("%lld\n",ans);
		}
	}
	return 0;
}
```

# The end

---

