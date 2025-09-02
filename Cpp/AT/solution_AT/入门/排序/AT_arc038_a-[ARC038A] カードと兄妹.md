# [ARC038A] カードと兄妹

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc038/tasks/arc038_a

$ N $ 枚のカードがあり、$ i\ (1\ ≦\ i\ ≦\ N) $ 枚目のカードには整数 $ A_i $ が書かれています。ゲーム好きの兄妹はこれらのカードを使ってゲームをしようとしています。

- 最初に全てのカードを、カードに書かれた整数が見えるようにテーブルの上に並べる。
- プレイヤーは自分のターンに、テーブルの上にあるカードからちょうど $ 1 $ 枚のカードを選んで取る。
- テーブルの上にカードがなくなるまで、交互にターンを繰り返す。
- 最終的に、自分が取ったカードに書かれた整数の和がプレイヤーの **スコア** となる。

$ 2 $ 人ともが自分のスコアを出来るだけ大きくしようとしたとき、先手のスコアはいくつになるでしょうか？

## 说明/提示

### Sample Explanation 1

この例では、ゲームは以下のように進行します。 - 先手が $ 2 $ 枚目のカードを取る。 - 後手が $ 1 $ 枚目のカードを取る。 このとき、先手のスコアは $ 628 $ となり、後手のスコアは $ 400 $ となります。

### Sample Explanation 2

この例では、ゲームは以下のように進行します。 - 先手が $ 3 $ 枚目のカードを取る。 - 後手が $ 4 $ 枚目のカードを取る。 - 先手が $ 2 $ 枚目のカードを取る。 - 後手が $ 5 $ 枚目のカードを取る。 - 先手が $ 1 $ 枚目のカードを取る。 このとき、先手のスコアは $ 16 $ となり、後手のスコアは $ 11 $ となります。

## 样例 #1

### 输入

```
2
400 628```

### 输出

```
628```

## 样例 #2

### 输入

```
5
2 5 9 6 5```

### 输出

```
16```

# 题解

## 作者：wushuang0828 (赞：5)

**思路：先排序（本人用的是选择排序），然后将下标 mod 2=0的数组元素相加，再将下标 mod 2=1的数组元素相加**

题目水，废话不多说，放代码：
```pascal
var
 n,i,j,t,s,ss:longint;
 a:array[0..1001] of longint;
begin
 readln(n);
 for i:=1 to n do
  read(a[i]);
 for i:=1 to n-1 do
  for j:=i+1 to n do//选择排序
   if a[i]<a[j] then
    begin
     t:=a[i];//交换
     a[i]:=a[j];//交换
     a[j]:=t;//交换
    end;
 for i:=1 to n do
  if i mod 2=0 then s:=s+a[i]//下标是偶数的相加
               else ss:=ss+a[i];//下标是奇数的相加
 if s>ss then writeln(s)
         else writeln(ss);//输出较大的
end.
```

---

## 作者：醉梦未苏 (赞：3)

#### 这道题只有一篇$C++$题解？

#### $\huge\text{python}$题解爬过来~~凑个热闹~~

> 隔壁的题解好详细啊。。。(恐惧)

- 本题的作法就如题目所描述,排序后按要求累加

- 输出$max(\text{奇数和,偶数和})$即可

```python
#输入
n=int(input()) 
kkk=map(int,input().split(' ')) #皮一下
a=list(kkk) #将kkk作成list型(逃
a.sort() #排序
tot1=0;tot2=0 #初始化
for x in range(n): #开始统计
    if((x+1)%2==0): #因为数组从0开始计数,故在此加1
        tot2=tot2+a[x]
    else:
        tot1=tot1+a[x]
print (max(tot1,tot2)) #输出较大的
```

求过，求赞

---

## 作者：丁丁の丁丁 (赞：2)

好吧，本蒟蒻看不懂各位大佬的神代码，只能手打一个通俗易懂的差代码（适合蒟蒻用）
~~~
#include<bits/stdc++.h>						 
using namespace std;
int main()
{
long long n,m,i,j,c,p,s=0,x=0;
cin>>n;
long long a[n];
for(m=1;m<=n;m++)
{
	cin>>a[m];
}
for(i=1;i<=n-1;i++)
for(j=i+1;j<=n;j++)
{
	if(a[i]>a[j])
	{
		c=a[i];
		a[i]=a[j];
		a[j]=c;
	}
}//排序，排序！不用说了大家都做过，也很熟悉
for(p=1;p<=n;p++)
{
	if(p%2==0) s=s+a[p];
	else x=x+a[p];//重点来了——判断读入的数是偶数还是奇数，并加上。
}
if(s>x) cout<<s<<endl;
else cout<<x<<endl;//判断是奇数大还是偶数大，并打印
return 0;
}	
~~~~
是不是通俗易懂？？？

---

## 作者：I_will (赞：1)

这是一道排序的题，只要求出奇数偶数和，并输出最大的和即可。

* 输入：输入n和n个数。
* 排序：从小到大
* 过程1：排序后，用两个数组分别存x[奇数下标]和x[偶数下标]的数。
* 过程2：在分别有两个统计和（h1,h2）来分别计算奇数和偶数和。
* 输出：输出max(奇数和，偶数和);

完整程序如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y;
int c[1005];
int a[505];
int b[505];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	
	{
		cin>>c[i];
	}
	sort(c+1,c+1+n);
	for(int i=1;i<=n;i+=2)
	{
		a[(i+1)/2]=c[i];
		b[(i+1)/2]=c[i+1];
		
	}
	if(n%2==1)a[n/2+1]=c[n];
	for(int i=1;i<=(n+1)/2;i++)
	{
		x+=a[i];
	}
	for(int i=1;i<=n/2;i++)
	{
		y+=b[i];
	}
	cout<<max(x,y)<<endl;
	return 0;
}
```


---

## 作者：_Qer (赞：1)

~~真是水啊~~

对于这题，我们有两种做法：

前提：设数组中第$i$个数下标为$i$，数字的数量为$n$
____


1:

所有数**从大到小**排序，拿走所有下标 $ i\mod2 == 0$（下标0开始）的数，输出总和。

若下标1开始则拿走下标 $i\mod2 == 1$ 的数

```cpp
	for (int i = 0; i < n; i += 2) {//这里直接+2省去判断过程
        ans += num[i];
    }
```

这种方法有点麻烦，因为还要写一个排序的函数，加入sort。（sort默认从小到大排序，推荐方法2）
____
2:

所有数**从小到大**排序，拿走所有下标 $(n-i)\mod2 == 0$ 的数（下标0开始），输出总和。

若下标1开始则拿走下标 $(n-i)\mod2 == 1$ 的数

```cpp
	for (int i = n - 1; i >= 0; i -= 2) {//-2省去判断
        ans += num[i];
    }
```
____
本人AC代码，用的方法2
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, num[1010];
int ans;
int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    sort(num, num + n);
    for (int i = n - 1; i >= 0; i -= 2) {
        ans += num[i];
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：勘探员·引魂人 (赞：1)

**前言：今天的天气真晴朗，我要做一个愉快的 ~~说书人~~ 发题解的人**

**思路：输入数组，分别求出数组奇数位的和和偶数位的和，算出这两个和的最大值**

**开始 ~~说书~~ 讲题了：**

```
#include<iostream>
#include<cstdio>
#include<algorithm>//我不会打万能文件头
using namespace std;
long long n,j,o;//用long long定义n，奇数个数变量，偶数个数变量
int a[5010];//定义数组
```
**欲知后事如何，请听下回分解**

**........**

**上回书说道,我们定义了变量和数组，接下来我们开始真正的过程**
```
int main()
{
	scanf("%lld",&n);//输入n
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);//输入数组
	}
	sort(a+1,a+1+n);//排序数组
```
**欲知后事如何，请听下回分解**

**上回书说道,我们输入了数组，接下来我们开始求出数组奇数位的和和偶数位的和并算出这两个和的最大值**

```
	for(int i=1;i<=n;i+=2)//从1循环到n（i+=2会更快）
	{
		j+=a[i];//算出奇数位置的和
	}
	for(int i=2;i<=n;i+=2)//从2循环到n（因为是求偶数位置的和，所以从2开始，i+=2会更快）
	{
		o+=a[i];//算出偶数位置的和
	}
	cout<<max(j,o)<<endl;//算出奇数位置的和和偶数位置的和的最大值
	
	return 0;//结束程序
}
```

---

## 作者：林家三少 (赞：0)

>题解+1

这一题只要跟着题目描述走就行了，

1. 输入
2. 排序
3. 奇偶都累加
4. 比较输出

~~求过~~

代码:

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;
int n;
int ans1,ans2;
int a[1000+10];
//定义变量
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
    //步骤1
	sort(a+1,a+1+n);
    //步骤2
	for(int i=1;i<=n;i++)
	{
		if(i%2==0)
			ans2+=a[i];
		else
			ans1+=a[i];
	}
    //步骤3
	if(ans2>ans1)
		cout<<ans2<<"\n";
	else
		cout<<ans1<<"\n";
    //步骤4
	return 0;
} 
```


---

## 作者：HOIer_9_42 (赞：0)

新加一篇c++题解，望过^_^

其实这道红题，对时间效率的要求非常低，根据题意进行模拟就行了。用循环变量i作为下标用a【i】数组存数字，题目要求我们先排序，于是先sort一遍，（STL大法好！~~），接着，就开始寻找下标分别为奇数和偶数的元素，时间复杂度O(n)，超不了时，然后再比较一下就可以了。

下面是AC代码——

```cpp
#pragma GCC otimize(3)
#pragma once
#include<bits/stdc++.h>
using namespace std;
const int hxj=10001;
int a[hxj],sum1=0,sum2=0,i,j,k,n,ans;
int main()
{
	ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);//输入输出优化
    memset(a,0,sizeof(a));
	cin>>n;
	for(register int i=1;i<=n;i++)
	   cin>>a[i];
	sort(a+1,a+n+1);//对所有元素进行排序
	for(register int i=1;i<=n;i++){
	   if(i%2){
	      sum1+=a[i];//下标为奇数的元素求和
	   }
	   else{
	      sum2+=a[i];//下标为偶数的元素求和
	   }
	}
    ans=sum1>sum2?sum1:sum2;//三目运算符比大小
    cout<<ans<<endl;
	return 0; 
}
```

---

