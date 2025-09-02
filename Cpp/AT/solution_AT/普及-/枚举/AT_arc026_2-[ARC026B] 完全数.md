# [ARC026B] 完全数

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc026/tasks/arc026_2

高橋君は完全なものが大好きです。

自然数には、完全数というものがあります。 完全数というのは、自分以外の約数の総和が自分と等しくなる自然数のことです。 例えば $ 6 $ の場合 $ 1\ +\ 2\ +\ 3\ =\ 6 $となるので完全数です。 それに対して、自分以外の約数の総和が自分より小さくなる場合は不足数と言い、大きくなる場合は過剰数と言います。

高橋君には今気になっている自然数があります。高橋君のために、それが完全数なのか不足数なのか過剰数なのか判定してください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ 1\ ≦\ N\ ≦\ 10^5 $を満たすデータセットに正解した場合は $ 50 $ 点が与えられる。
- $ 1\ ≦\ N\ ≦\ 10^{10} $を満たすデータセットに正解した場合はさらに $ 50 $ 点が与えられる。合計で$ 100 $点となる。

### Sample Explanation 1

$ 1\ +\ 2\ +\ 3\ =\ 6 $なので$ 6 $は完全数です。

### Sample Explanation 2

$ 1\ +\ 2\ +\ 3\ +\ 4\ +\ 6\ +\ 8\ +\ 12\ >\ 24 $なので$ 24 $は過剰数です。

### Sample Explanation 3

$ 1\ +\ 3\ +\ 9\ <\ 27 $なので$ 27 $は不足数です。

## 样例 #1

### 输入

```
6```

### 输出

```
Perfect```

## 样例 #2

### 输入

```
24```

### 输出

```
Abundant```

## 样例 #3

### 输入

```
27```

### 输出

```
Deficient```

## 样例 #4

### 输入

```
945```

### 输出

```
Abundant```

# 题解

## 作者：EtOH_Lewis (赞：17)

## 这道题并不难，不就是约数和吗！

上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int sum(int x)//约数和的函数
{
	int counter=0;//计数器归零
    for(int i=1;i<=x;i++)
    {//从1到x枚举
        if(x%i==0)counter+=i;
        //如果是因数，计数器加1             
    }
    return counter;//把这个值返回到主函数
}
int main()
{
    int n;cin>>n;
    if(sum(n)==n)cout<<"Perfect"<<endl;
    if(sum(n)<n)cout<<"Deficient"<<endl;
    if(sum(n)>n) cout<<"Abundant"<<endl;
    //按照题意
    return 0;
}
```
### 满怀信心交上去，有WA有TLE也有AC

分析一下为什么：

    1.读题面，后面日文部分（1 ≦ N ≦ 1010 を満たすデータセットに正解した場合はさらに 50 50 50 点が与えられる。合計で 100 100 100 点となる。），说是最大值是10的10次方
    
    2.10的10次方是10000000000
    
    3.int最大值是  2147483647
    
    4.哦哦，得开long long

分析完了，把代码重交一遍！

```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum(long long x)//全部开long long
{
	long long counter=0;
    for(int i=1;i<=x;i++)
    {
        if(x%i==0)counter+=i;
    }
    return counter;
}
int main()
{
    long long n;cin>>n;
    if(sum(n)==n)cout<<"Perfect"<<endl;
    if(sum(n)<n)cout<<"Deficient"<<endl;
    if(sum(n)>n) cout<<"Abundant"<<endl;
    return 0;
}
```

## 提交成功，只有TLE和AC了！

### 继续！时间优化！

如果我们在主函数里面，先把m储存起来，判断的时候再单独把值拎出来就是了。这样至少得省三分之一的时间！

```cpp
int main()//主函数
{
    long long n,m;cin>>n;
    if(m==n)cout<<"Perfect"<<endl;
    if(m<n)cout<<"Deficient"<<endl;
    if(m>n)cout<<"Abundant"<<endl;
    return 0;
}
```

## 提交了，TLE貌似少点了
### 继续！

一个数，不管它有几个约数，它除了1外，最少就是2，所以，我们把子函数里的for循环，x改成x/2也没有事，可以优化50%的时间。

```cpp
long long sum(long long x)
{
    long long counter=0;
    for(int i=1;i<=x/2;i++)
    //高枕无忧，比如24，它的约数里有2，但是因为是<=，所以没事
    {
        if(x%i==0)counter+=i;
    }
    return counter;
}
```

## TLE更少了，但是还有。还能怎么优化呢？？

### 对了，记得求质数的方法，可以用开跟法啊！

### 判断质数就是2~sqrt(x)之间没有约数。

### 所以我们就可以用1~sqrt(x)里面的约数之和。

来吧！
```cpp
#include<bits/stdc++.h>
using namespace std;
long long sum(long long x)
{
	long long counter=0;
    double k=sqrt(x);//只能这样了！
    for(int i=1;i<=k;i++)//需要cmath，但是bits/stdc++.h已经包括了！
    {
        if(x%i==0)counter+=i;
    }
    return counter;
}
int main()
{
    long long n,m;cin>>n;m=sum(n);
    if(m==n)cout<<"Perfect"<<endl;
    if(m<n)cout<<"Deficient"<<endl;
    if(m>n) cout<<"Abundant"<<endl;
    return 0;
}
```
## 惊奇了WA了

为什么？？

>举个例子，12，int(sqrt(12))取3，1 2 3都能取到，但是，4 6 呢？

```
#include<bits/stdc++.h>
using namespace std;
long long sum(long long x)
{
	long long counter=0;
    double k=sqrt(x);
    for(int i=1;i<=k;i++)
    {
        if(x%i==0)counter+=(i+x/i);
    }
    return counter;
}
```
## 也WA
这种方法好。比如12, 2能被统计到，6就能被统计到！

但是，如果1能取到，12就可以取到！哦哦，如果12被取到就错了！

```
#include<bits/stdc++.h>
using namespace std;
long long sum(long long x)
{
	long long counter=1;
    double k=sqrt(x);
    for(int i=1;i<=k;i++)
    {
        if(x%i==0 && i!=1)counter+=(i+x/i);
        //这样就对了，i不等于1的时候再来。但是1呢？看counter的初始赋值是1！巧妙！
    }
    return counter;
}
int main()
{
    long long n,m;cin>>n;m=sum(n);
    if(m==n)cout<<"Perfect"<<endl;
    if(m<n)cout<<"Deficient"<<endl;
    if(m>n) cout<<"Abundant"<<endl;
    return 0;
}
```

## AC!

推荐：[P1075 质因数分解](https://www.luogu.org/problem/P1075)和[AT261 与えられた数より小さい素数の個数について](https://www.luogu.org/problem/AT261)

---

## 作者：LJC00111 (赞：6)

判断因数的个数

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,ans=1;
	cin>>n;
	if(n==1)//1无法判断，所以要提前判断。
	{
		cout<<"Deficient"<<endl;
		return 0;
	}

	for(int i=2;i<=sqrt(n);i++)//统计因数个数，仅需统计1到n开根号，不然会超时
	{
		if(n%i==0)//如果是n的因数
		{
			ans=ans+i;//加上他
			ans=ans+n/i;//加上另一个
		}
		if(i==sqrt(n)&&n%i==0)//如果n是平方数
		{
			ans=ans-i;//减去这个数
		}
	}
	if(ans==n)
	cout<<"Perfect"<<endl;
	else if(ans<n)
	cout<<"Deficient"<<endl;
	else 
	cout<<"Abundant"<<endl;
	return 0;
}
```

---

## 作者：珅肐 (赞：4)

## 水题 ~~虽然卡了我好几遍~~
思路与楼下差不多
### 代码：

```c
#include<iostream>//不解释
#include<cmath>
using namespace std;
long long n,ans;
int main()
{
    cin>>n;//输入
    for(int i=1;i<=sqrt(n);i++)//循环找其因数，到sprt（n)是减少循环次数，优化
		if(n%i==0)
        {
            ans=ans+i;//累加因数
            ans=ans+n/i;//累加相对的因数
        }
    if(sqrt(double(n))==sqrt(n))//判断是否为完全平方数
            ans-=sqrt(n);//如果是，就减去
	//因为1也是完全平方数，不用另行判断
	if(ans-n==n)  cout<<"Perfect"<<endl;
    else if(ans-n<n) cout<<"Deficient"<<endl;
    else cout<<"Abundant"<<endl;
    return 0;
}
```

---

## 作者：tiaotiao (赞：3)

## 大水题，但是容易被隔壁atcoder卡
### 思路很简单，大致就是循环枚举因数然后加起来
### 只要能整除就是因数，因此一次循环可以加上两个因数，所以只要循环sqrt(n)次（否则会TLE）
### 举例：10=2*5  2是10的因数，5也是10的因数
### 完全平方数的一个因数会被统计两次，需要减去
### 1需要特判
### 数据范围10^10,需要long long
# 注意！！！本题输出答案需要\n！！！否则爆零！！！
    #include <cstdio>
	#include <cmath>
	int main()
	{
		long long n;
		scanf("%lld",&n);
		long long sum=0;
		if(n==1)//1需要特判
		{
			printf("Deficient\n");
			return 0;
		}
		for(long long i=1;i<=sqrt(n);i++)
		{
			if(n%i==0)
			{
				sum+=i;sum+=n/i;
			}
		}
		sum-=n;//这个数本身作为因数被统计了，要减去
		long long sqn=sqrt(n);
		if(sqn*sqn==n)sum-=sqn;//特判完全平方数
		if(sum==n)printf("Perfect\n");
		if(sum<n)printf("Deficient\n");
		if(sum>n)printf("Abundant\n");
		return 0;
	}

---

## 作者：dmslhy (赞：2)

### ~~本蒟蒻的第一篇题解。~~

这道题是一个比较有坑的题，主要以下几个坑。

可以判断因数和时一次找一对，因为因数B=因数A/N，否则会T。

和弄好之后需要减一，因为还有1这个因数。

1需要特判一下，因为一可以通过素数判断，但1不是素数。

需要特判N是完全平方数；

贴代码
```
#include<bits/stdc++.h>//不会别的头文件了
using namespace std;
int main(){
	long long int n,he=0;
	cin>>n;
	for(int i=2; i<=sqrt(n); ++i) {//只要到N的平方根
		if(n%i==0) {
			he+=i;
			he+=n/i;
			if(i==n/i) {//特判N是完全平方数
				he-=i;
			}
		}
	}
	++he;//加上一
	if(n==1) {//一的特判
		cout<<"Deficient"<<'\n';//岛国题目输出完后要换行
		return 0;
	}
	if(he==n) {
		cout<<"Perfect"<<'\n';
		return 0;
	}
	if(he>n) {
		cout<<"Abundant"<<'\n';
		return 0;
	}
	if(he<n) {
		cout<<"Deficient"<<'\n';
		return 0;
	}
}//结束错了很多次的程序。
```
~~希望大家看得懂我这种缩进风格~~
## 祝大家早日AC


---

## 作者：勘探员·引魂人 (赞：2)

  本蒟蒻第一次刷AT的**tímù**，也第一次发AT的**tí jiě**

  由于AT的**tí** **~~很难~~** ，所以本蒟蒻只写了个部份分的**tí jiě**

  下面，请看我 **~~枚举+暴力~~** 的解法吧。

    #include<iostream>
    #include<fstream>
    #include<algorithm>
    #include<cmath>//本蒟蒻不想打万能文件头。  
    long long n,j,sum,pf;//定义变量。 
    int main()
    {
        scanf("%lld",&n);//输入需判断的数。 
        if(n==1){printf("Deficient\n");}//同意dàlǎo们的思路，特判1。 
        for(j=1;j<=n/2;j++)//从1到n/2枚举循环。 
        {
            if(n%j==0)//如果n/j余数为0的话...... 
        sum=sum+j; //和加等于j。 
        }
        if(sum==n)printf("Perfect\n");//如果和是n，输出Perfect。 
       if(sum<n)printf("Deficient\n");//如果和小于n，输出Deficient。
       if(sum>n)printf("Abundant\n");//如果和大于n，输出Abundant。

      return 0;//结束我们“完美”的程序。 
    }

---

## 作者：zzhz (赞：1)

这题不难,其实就是求因数的和，    
但要注意一点：
## 是求除自己以外的因数！ 
~~我第1次提交是就WA了~~    
双手奉上代码   
代码如下：  

```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;//定义空间
int n,s=0;
int main(){//主函数
    cin>>n;//输入
    for(int i=1;i<n;i++){
        if(n%i==0)s+=i;
    }
    if(s==n)cout<<"Perfect";//因数和等于原数
    if(s>n)cout<<"Abundant";//因数和大于原数
    if(s<n)cout<<"Deficient";//因数和小于原数
    cout<<endl;//一定要记得换行
    return 0;//结束
}
```
最后提醒一点：   
AT的题一定要换行！   
本蒟蒻心地善良   
但是，    
非紧急情况不要用此功能！    

---

## 作者：唐一文 (赞：0)

此题不难，就是求**因数和**

但是
###  不包括数本身！！！
**精髓**：
```cpp
x=sqrt(n);
for(i=1;i<=x;i++){  //i<=x是为了防止超时
    if(n%i==0){  //找到整除n的数
        s=s+i+n/i;  //因为i整除n，所以n/i也整除n
    }
}
s-=n;  //不含n自己
if(x==(int)x){  //判断n是否为完全平方数
    s-=x;
}
```

---

