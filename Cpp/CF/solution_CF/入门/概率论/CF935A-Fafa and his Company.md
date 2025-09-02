# Fafa and his Company

## 题目描述

Fafa owns a company that works on huge projects. There are $ n $ employees in Fafa's company. Whenever the company has a new project to start working on, Fafa has to divide the tasks of this project among all the employees.

Fafa finds doing this every time is very tiring for him. So, he decided to choose the best $ l $ employees in his company as team leaders. Whenever there is a new project, Fafa will divide the tasks among only the team leaders and each team leader will be responsible of some positive number of employees to give them the tasks. To make this process fair for the team leaders, each one of them should be responsible for the same number of employees. Moreover, every employee, who is not a team leader, has to be under the responsibility of exactly one team leader, and no team leader is responsible for another team leader.

Given the number of employees $ n $ , find in how many ways Fafa could choose the number of team leaders $ l $ in such a way that it is possible to divide employees between them evenly.

## 说明/提示

In the second sample Fafa has 3 ways:

- choose only $ 1 $ employee as a team leader with $ 9 $ employees under his responsibility.
- choose $ 2 $ employees as team leaders with $ 4 $ employees under the responsibility of each of them.
- choose $ 5 $ employees as team leaders with $ 1 $ employee under the responsibility of each of them.

## 样例 #1

### 输入

```
2
```

### 输出

```
1
```

## 样例 #2

### 输入

```
10
```

### 输出

```
3
```

# 题解

## 作者：OdtreePrince (赞：7)

# -数论吧-

如果说，组长个数为i，则组数为i，则组员有（n-i）个人

也就是说                                     $\color{blue}\texttt{if((n-i)模i==0) ans++}$。

输出ans 水过！！！！
~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,ans=0;
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        if((n-i)%i==0) ans++;
    }
    printf("%d",ans);
    return 0;
}~~~

---

## 作者：引领天下 (赞：4)

数论题不是用来氵的

所以，我们果断地选择了分解质因数

于是就可以用公式：

$$ n=(p_{1}^{a_{1}})*(p_{2}^{a_{2}})*...*(p_{k}^{a_{k}}) $$

n的因子个数$$ =(a_{1}+1)*(a_{2}+1)*...*(a_{k}+1) $$

代码：

```cpp
#include <cstdio>
int n,ans=1;
int main(void){
    scanf ("%d",&n);
    for (int i=2;i<=n;i++)if (n%i==0){
        int k=0;
        while (n%i==0)n/=i,k++;//分解质因数，看有多少重
        ans*=(k+1);
    }
    printf ("%d",ans-1);
}
```

---

## 作者：return先生 (赞：2)

这道题，我一开始用了很麻烦的办法：

```cpp
#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(i*j==n)
			{
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}
```

十分暴力，对吧。结果华丽丽的TLE了……

但其实转念一想，答案其实就是他可以被几个整数整除，啊！

```cpp
#include<iostream>
using namespace std;
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n/2;i++)
	{
		if(n%i==0)
		{
			ans++;
		}
	}
	cout<<ans;
	return 0;
}
```

成功的过了，（所以做题的时候不要把它想象的太难……）

---

## 作者：Register (赞：2)

# 记得小学四年级学的分解质因数吗？
好吧，这只是我自己的课本，不过当时也没讲因数个数定理

我们来分析一下这道题：
```
	设有m个员工要升官了，既然平均分配，就说明(n-m)/m是可以整除的。
    如果这个系数是k，就说明员工有m(k+1)个，因此可以证明只要选的领导个数能够被n整除即可
    因此就说明了选领导的方案是n的因数个数
    不过每一个领导必须要个马仔呀！所以排除掉因数是本身的情况，所以最后减一
```
我再来科普一下因数个数定理吧：
```
	以60举个栗子：
    60=2^2*3^1*5^1
    这下把每一个质因子头上的次幂分别加1后相乘就是因数个数
    因数个数=(2+1)*(1+1)*(1+1)=12
    大家可以自己枚举一下。。。
```
所有都明白了，可以上代码了：
```cpp
#include <iostream>
using namespace std;
int main(){
	int n,sum=1/*因数个数*/,k/*当前状态下的质因子*/;
	cin>>n;
	while(n!=1)//只要n还没有被除以到1，也就是没有因数了
	{
		int tot=1;//这个质因子头上的次幂加1的统计
		while(n%k==0)//看看能凑到几次幂
		{
			tot++;//增一次
			n/=k;//除以一次
		}
		sum*=tot;//话说没有的话*1还是一样的
		k++;//n的质因子判断系数加1
	}
	cout<<sum-1<<endl;//因为要有马仔呀。。。所以减1
	return 0;
}
```

---

## 作者：PC_DOS (赞：1)

本题就是计算输入的数除了它本身之外所有约数的个数。暴力枚举即可。

代码:
```
#include <iostream>
using namespace std; //头文件和命名空间
int main(){
   ios::sync_with_stdio(false); //输入输出加速
    int nPeople, i, nCount = 0; //nPeople-总人数；i-循环计数器；nCount-分组方法数
    cin>>nPeople; //读入总人数
    for (i = 1; i <= nTask / 2; ++i){ //枚举
        if (nPeople%i == 0){ //是约数
            ++nCount; //方案数加1
        }
    }
    cout<<nCount; //输出答案
    return 0; //结束
}
```

---

## 作者：inoichi_lim (赞：0)

分解质因数。

显然$n=\prod_{i=1}^m p_i^{a_i}$。

那么$n$的因数个数就是$\prod_{i=1}^m (a_i+1)$。

暴力即可。

```cpp
#include <bits/stdc++.h>
int n,ans=1;
int main(){
    scanf("%d",&n);
    for(int i=2;i<=n;i++){
        if(n%i==0){
            int k=0;
            while(n%i==0) n/=i,k++;//分解。
            ans*=(k+1);
        }
    }
    printf ("%d",ans-1);
    return 0;
}
```

---

## 作者：开心的猪 (赞：0)

这道题的本质就是求出除了1以外n的所有约数个数。由于这道题目的数据范围比较小，所以直接模拟并不会超时。

下面是代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int n;
	scanf("%d", &n);
	int ans=0;
	for(int i=1; i<=n/2; i++)
	{//由于1和n都一定是n的约数，所以在这里本来应该去掉1，现在去掉的是n.
		if(n%i==0)
		{
			ans++;//如果这个数字是约数，计数器加一。
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：Jinyeke (赞：0)

#### 没有pascal的题解？那我来啦。
#### 思路还是比较简单的，由于数据比较小，n<=100000,直接暴力枚举。
###  大概思路：
### 枚举1~n，因为一个团队不能只有一个领导者而没有员工，所以要把n个人分成n组的情况排除掉，至于其他就看看能不能平均分了，也是n mod i=0，不过由于要排除特殊情况，再加一个条件n div i<>1（也就是只有领导者没有员工），那么代码只要实现一下就可以了。
 代码如下:
 ```pascal
var
 n,i,s:longint;
begin
 read(n);//输入
 for i:=1 to n do 
  if (n mod i=0) and (n div i<>1)//分组的条件（上面写了）
   then inc(s);//符合条件就+1
 write(s);//输入符合条件的组数
end.
```


---

## 作者：RioBlu (赞：0)

思路前面的大佬都说了，但py党表示不服，为什么没有py题解呢？

于是我默默的打了**python2**代码
___
这绝对是最短代码：
```python2
a=input()
ans=0
for i in range(1,a,1):
    if (a-i)%i==0:
        ans=ans+1
print ans
```

---

