# [ABC057C] Digits in Multiplication

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc057/tasks/abc057_c

整数 $ N $ が与えられます。   
 ここで、$ 2 $ つの正の整数 $ A,B $ に対して、$ F(A,B) $ を「$ 10 $ 進表記における、$ A $ の桁数と $ B $ の桁数のうち大きい方」と定義します。   
 例えば、$ F(3,11) $ の値は、$ 3 $ は $ 1 $ 桁、$ 11 $ は $ 2 $ 桁であるため、$ F(3,11)=2 $ となります。   
 $ 2 $ つの正の整数の組 $ (A,B) $ が $ N=A×B $ を満たすように動くとき、$ F(A,B) $ の最小値を求めてください。

## 说明/提示

### 制約

- $ 1≦N≦10^{10} $
- $ N $ は整数である。

### Sample Explanation 1

$ (A,B)=(100,100) $ のときに $ F(A,B) $ は最小値をとるため、$ F(100,100)=3 $ を出力します。

### Sample Explanation 2

条件を満たす $ (A,B) $ の組は $ (1,1000003) $ と $ (1000003,1) $ の $ 2 $ 通りで、$ F(1,1000003)=F(1000003,1)=7 $ です。

## 样例 #1

### 输入

```
10000```

### 输出

```
3```

## 样例 #2

### 输入

```
1000003```

### 输出

```
7```

## 样例 #3

### 输入

```
9876543210```

### 输出

```
6```

# 题解

## 作者：MaoHanKun (赞：10)

	#include<cstdio>//输入输出要用的文件。 
	#include<cmath>//sqrt要用的文件。 
	using namespace std;
	long long n,ans;//10的10次方超int。 
	int s;
	int main(){
	    scanf("%lld",&n);//long long的scanf要用lld。 
	    for(int i=sqrt(n);i>0;--i) //从平方根开始搜索，用n除以搜到的第一个数，计算出它的位数就是答案。 
   	    	if(n%i==0){
        		ans=n/i;
        		break;
			}
		while(ans>0){//计算位数。 
			++s;
			ans/=10;
		}
		printf("%d\n",s);//s为int型变量。 
    	return 0;
	}//完美结束。 

---

## 作者：TRZ_2007 (赞：1)

请安静的注视这一行：```给你一个整数n 求F ( A，B )的最小值为 使得 N = A×B```  
## 是不是十分地似曾相识！  
## 这是小学时长方形的面积公式！（看$N=A*B$）  

所以说，如果想要$F(A,B)$的值最小，就是让$A$和$B$的位数相接近，就是让$A$和$B$的差的绝对值最小，达到了这个目的，再做到$N=A*B$就可以完美的解决这道题目了。  

$Accepted$  
```
#include <bits/stdc++.h>//万能头文件
using namespace std;
typedef long long ll;//注意要开long long
namespace doit
{
	inline ll read()//快读函数
	{
		ll x=0,p=1;
		char c;
		c=getchar();
		while(c<'0'||c>'9')
		{
			if(c=='-')
				p=-1;
			c=getchar();
		}
		while(c>='0'&&c<='9')
		{
			x=x*10+c-'0';
			c=getchar();
		}
		return x*p;
	}
	inline int f(ll n)//求数的位数
	{
		int len=0;
		while(n)
		{
			n/=10;
			len++;
		}
		return len;
	}
	inline void put()
	{
		ll n,ans;
		n=read();
		for(register int i=sqrt(n);i>=1;i--)//从sqrt(N)开始找
			if(n%i==0)//如果找到了
			{
				ans=n/i;//就为最优解
				break;
			}
		std::cout<<f(ans)<<"\n";//输出位数就OK了
	}
}
int main()
{
	ios::sync_with_stdio(false);
	doit::put();
}
```

---

## 作者：4kilometers (赞：1)

######  我~~这样的巨佬~~只能发发入门题解自我锻炼了

## 温柔凝视此式:** A * B = N**

这跟小学奥数中给定矩形面积与周长的关系有点联系。这个问题就相当于给定面积为N的矩形，求min(F(长,宽)),可以想到当然是正方形啦~
于是我们就把N开平方,保存平方根 i 和 n / i的值。

懒得写while循环累计位数，我们可以把i 和 n / i用sprintf写入字符串，比较字符串长度就好啦~~~

附本蒟蒻AC代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL; //打板子留下的习惯~
LL n;
char s[11],s2[11]; //存储i 和 n / i,便于计算位数
int main()
{
    cin >> n;
    for (int i = sqrt(n); i >= 1; -- i) //正方形的启发
    {
        if (n % i == 0)
        {
            int i2 = n / i; //存储n / i
            sprintf(s,"%d",i);
            sprintf(s2,"%d",i2);//写入字符串
            cout << max(strlen(s),strlen(s2)) << endl; //strlen()函数直接搞定位数问题
            break;//由于从大到小枚举因数，故找到的一定是最优解，找到一组解直接跳循环
        }
    }
    return 0;
}
```

一定要记得AT的题目要打换行哦~ ~~**否则稻花香里说丰年**~~

---

## 作者：chengni (赞：1)

按照题目意思，从这个数的平方开始寻找因数，离平方越近越优，然后选择后面那个较大的数，输出他的位数就可以了。


```cpp
#include<bits/stdc++.h>

using namespace std;

long long int n;

int main(){
	cin>>n;
	for(int i=sqrt(n);i>=1;i--)
	{
		if(n%i==0){
			int t=i,l=n/i;
			int s=1;
			while(l>=10){
				s++;
				l/=10;
			}
		cout<<s;
		return 0;
		}
	}
}
```

---

## 作者：happybob (赞：0)

这道题目先要学会分析

两个数相乘等于n，位数最好是要一样的，会想到平方根不？

判断平方根是否是整数，是就输出位数，不是从1到平方根慢慢找

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    double f = sqrt(n);
    if(f == (int)f)
    {
        int digit = 0, c = (int)f;
        while(c)
        {
            digit++;
            c /= 10;
        }
        cout << digit << endl;
    }
    else
    {
        for(int i = (int)f; i >= 1; i--)
        {
            if(n % i == 0)
            {
                int x = (i > n / i ? i : n / i);
                int digit = 0;
                while(x)
                {
                    digit++;
                    x /= 10;
                }
                cout << digit << endl;
                break;
            }
        }
    }
    return 0;
}
```


---

## 作者：赤霞QvQ (赞：0)

###### 做法：因为数据很水，直接枚举，把 sqrt(n)sqrt(n) 以内的数枚举一遍，找到整除n的数，越接近 sqrt(n)sqrt(n) 越好，因为要求这两个数中长度大的，所以这两个数越接近越好，这样才能使它们中长度长的最短（像绕口令似的）。
###### 上代码：
```cpp
#include<bits/stdc++.h>   //万能头，竞赛不建议使用，占内存太大
using namespace std;
int main()
{
    long long n,min,l=0;     //十位数要开long long
    cin>>n;
    min=n;      //长度最小的
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)     //N=A*B故要整除
        {
            min=n/i;     //因为A*B中我们枚举的是A，然而A是不可能超过B，即A的长度不可能超过B，故取B的值
        }
    }
    while(min!=0)
    {
        min/=10;
        l++;
    }            //长度
    cout<<l<<endl;
    return 0;
}
```
其实反过来枚举更好，只要找到能整除n的就退出循环，一样的道理。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n,min,l=0;
    cin>>n;
    for(int i=floor(sqrt(n));i>=1;i--)    //要floor，不然i大几率不是整数
    {
        if(n%i==0)
        {
            min=i;
            break;
        }
    }
    while(min!=0)
    {
        min/=10;
        l++;
    }
    cout<<l<<endl;
    return 0;
}
```
结束！！！QED！！

---

## 作者：meyi (赞：0)

**本蒟蒻手打了一个暴力AC后，看见各位大佬的题解，只能自愧不如。**

**但是！由于数据范围较小，本题也是可以模拟的！**

**接下来上代码：**
```cpp
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
inline ll f(ll a){
    return a?f(a/10)+1:0;	//按照题意模拟
}
inline ll f(ll a,ll b){
    return max(f(a),f(b));	//按照题意模拟
}
main(){
    ll n,m,s=11;	//int最大值为2147483647，即为2的31次方减1,10的10次方会爆
    scanf("%lld",&n);
    m=sqrt(n);
    for(register ll i=1;i<=m;++i)if(n%i==0)s=min(s,f(i,n/i));	//按照题意模拟
    printf("%lld",s);
}
```

---

