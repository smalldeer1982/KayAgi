# Cookies

## 样例 #1

### 输入

```
1
1
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10
1 2 2 3 4 4 4 2 2 2
```

### 输出

```
8
```

## 样例 #3

### 输入

```
11
2 2 2 2 2 2 2 2 2 2 99
```

### 输出

```
1
```

# 题解

## 作者：RioBlu (赞：4)

直接把饼干总数加起来

看看饼干总数减去$a[i]$是否是偶数
```
#include<bits/stdc++.h>
using namespace std;
int a,b[105],c,ans;
int main()
{
    cin>>a;
    for(int s=0;s<a;s++)//s就是i，本人习惯用s
    {
        cin>>b[s];
        c=c+b[s];//把饼干数量加起来
    }
    for(int s=0;s<a;s++)
    {
        if((c-b[s])%2==0)//饼干总数减去a[i]（b[s]就是a[i]）
        {
            ans++;//答案
        }
    }
    cout<<ans<<endl;//输出
    return 0;//完美结束
}
```

---

## 作者：bym666 (赞：2)

# CF129A 【Cookies】
这道题我们许哟用到两个很简单的、小学生都知道的公式：
## 奇数+偶数=奇数
## 偶数+偶数=偶数
通过这两个公式，我们就可以想出这题的思路：求出饼干的个数，如果是奇数个，就拿掉奇数个数的袋子，否则就拿掉偶数个数的袋子。

代码如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
int n,a[101],s,ans;
int main()
{
	cin>>n;//输入 
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//输入 
		s+=a[i];//求和 
	}
	if(s%2==0)//如果是偶数 
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]%2==0) ans++;//求偶数个饼干袋的个数 
		}
	}
	else//如果是奇数 
	{
		for(int i=1;i<=n;i++)
		{
			if(a[i]%2==1) ans++;//求奇数个饼干袋的个数 
		}
	}
	cout<<ans;//输出个数 
	return 0;//结束程序 
} 
```


---

## 作者：米奇奇米 (赞：2)

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main()
{
	int n,a[1005];//开一个数组，最好开得大一点
	int s=0,ans=0,k;//初始化
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	    s=s+a[i];//累加饼干的数量
	    int k=s;//用一个变量来储存数量
	}
	for(int i=1;i<=n;i++)
	 {
	 	if((s-a[i])%2==0)//按照题意，若是偶数，方案数加1
	 	{
	 		ans++;
	 		s=s;//还原，继续循环
		 }
		 else s=s;//不然，继续循环
	 }
	 cout<<ans;//输出方案数
	 return 0;
 } 

```

---

## 作者：Hzq11_ (赞：2)

#### ~~论如何挑战最短代码~~
其实此题很简单,分别累加奇数偶数,再判断输出  
送上仅0.15k的代码:
```cpp
#include<iostream>
using namespace std;
int o,e,n,a,s;
int main(){
	cin>>n;
    while (n--)
        cin>>a,a%2==0?e++:o++,s+=a;
    return (cout<<(s%2==0?e:o))&&0;
}
```

---

## 作者：Franka (赞：1)

~~小学生都会的题目。~~

### 首先温故一下小学的知识：

* #### 奇数-奇数=偶数；
* #### 偶数-偶数=偶数；
* #### 奇数-偶数=奇数；
* #### 偶数-奇数=奇数。
~~然而这里只能用到前两个。~~

### 所以，只用把这$n$个数的和加以来，然后把这$n$个数的奇偶性分清楚，就可以潇洒的解决这题了。
```
var n,i,x,ji,ou:longint;
    s:0..1;
begin
 readln(n);//读入n
 for i:=1 to n do
  begin
   read(x);//读入第i个数
   if odd(x) then inc(ji)//判断奇偶性，如果是奇数，就加到奇数的桶里
             else inc(ou);//否则加到偶数的桶里
   s:=(s+x) mod 2;//把和加起来
  end;
 if odd(s) then writeln(ji)//如果和是奇数，那么就要拿奇数的桶去减，所以输出奇数的桶
           else writeln(ou);//同理
end.
```

---

## 作者：Elma_ (赞：1)

蒟蒻又来水题解了。

在做这道题之前我们可以先来复习一下小学知识：
- ### 偶数=偶数+偶数
- ### 奇数=偶数+奇数
本题就可以通过以上两个公式求解。

对于饼干的总数$sum$,则有以下两种情况：

- 若$sum$为偶数，则要使剩下的饼干数为偶数，拿走的袋子中就必须是偶数个饼干。所以拿走饼干袋子的方案数就等于饼干数为偶数的袋子个数。

- 若$sum$为奇数，则要使剩下的饼干数为偶数，拿走的袋子中就必须是奇数个饼干。所以拿走饼干袋子的方案数就等于饼干数为奇数的袋子个数。

解法显然。先分别记录饼干的总数、饼干数量为偶数的袋数、饼干数量为奇数的袋数。如果饼干总数为偶数，输出饼干数量为偶数的袋数；反之，输出饼干数量为奇数的袋数。当然我们可以一边读入一边操作。

### CODE

```cpp
#include <iostream>
using namespace std;

int n, a[105];
int js,os,num;//js记录饼干数为奇数的袋子个数，os记录饼干数为偶数的袋子个数，num记录饼干总数

int main(void)
{
	cin>>n;
	
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		
		if(a[i]%2 == 0)//判断这个袋子的饼干数是奇数还是偶数
			os++;
		else
			js++；
		
		num += a[i];
	}//输入并统计
	
	if(num%2 == 0)//如果饼干总数为偶数
		cout<<os<<endl;//方案数为饼干数为偶数的袋子个数
	else//饼干总数为奇数
		cout<<js<<endl;//方案数为饼干数为奇数的袋子个数
	
	return 0;//完美AC~
}
```

---

## 作者：hensier (赞：0)

这道题其实可以不使用数组保存$n$个数，不过本蒟蒻当时没有想到这种方法。

其实就是模拟——输入$n$个数并求和，即$S$，并判断奇偶性。再搜索每一个元素，看有多少个奇偶性与$S$相同即可。

$AC$代码：

```cpp
#include<cstdio>
int n,a[100],i,s,S;
int main()
{
    scanf("%d",&n);
    for(;i<n;i++)scanf("%d",&a[i]),s+=a[i];//边输入边累加，求和
    for(i=0;i<n;i++)if(a[i]%2==s%2)S++;//如果该元素奇偶性与和相同则计数器加1
    printf("%d",S);//输出计数器所保存的数，即有多少个奇偶性与和相同，即题目所求答案（不需要对没有这样的数进行特判，因为直接输出0）
}
```

---

## 作者：FP·荷兰猪 (赞：0)

> 题意：有n袋饼干，每袋有a[i]个，现在拿走一袋饼干，使得剩下的饼干数是偶数，问有多少种方案

此题数据范围很小，直接模拟即可。

详见代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int x,i,cnt,even,odd;
	cnt=even=odd=0;//顾名思义，even记录偶数的个数，odd记录奇数的个数
	for (i=1;i<=n;i++)
	{
		cin>>x;//可以不用开数组，节约空间
		cnt+=x;//cnt累加出所有数的和
		if (x%2==0)
		{
			even++;//统计数的奇偶性
		}
		else
		{
			odd++;
		}
	}
	if (cnt%2==0)//如果总和是偶数，则可以去掉一个偶数，否则去掉一个奇数
	{
		cout<<even<<endl;
	}
	else
	{
		cout<<odd<<endl;
	}
	return 0;
}
```

---

## 作者：OdtreePrince (赞：0)

# -数论-

作为一位数学爱好者，数论≠题解是我的风格，能用数论的就用数论

本题就是考察奇偶性，j统计奇数个数，o统计偶数个数，sum统计和，如果和为奇，输出j（奇数个数）；否则，输出o（偶数个数）

OK，上代码！

~~~
#include<bits/stdc++.h>
using namespace std;
int n,a,j,o,sum;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        if(a%2==1) j++;
        else o++;
        sum+=a;
    }
    if(sum%2==1) cout<<j;
    else cout<<o;
    return 0;
}
~~~

---

## 作者：Hola_chen (赞：0)


```cpp
//本题解用了string函数输入（getline）字符串形式
//用for循环判断
//for循环必须从0开始
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int a,c;//int
    int ans=0;//int
    string b;//string
    cin>>a;//读入
    getline(cin,b);//读入
    a=b.size();//求长度（字符串）
    for(int i=0;i<a;i++)//for
    {
        c=c+b[i];
    }
    for(int i=0;i<a;i++)//for
    {
        if((c-b[i])%2==0)//if判断
        {
            ans++;
        }
    }
    cout<<ans<<endl;//输结果
    return 0;
}
```

---

