# [COCI 2010/2011 #6] OKUPLJANJE

## 题目描述

一场巨大的派对结束以后，有五家报纸刊登了参加这场派对的人数，然而这些报纸上的数字可能是错误的。

现在你知道整个会场的面积是 $L$ 平方米，并且平均每平方米上有 $p$ 个人。现在请分别求出这五家报纸刊登的参加人数与实际参加人数之差。

## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq L, p \leq 10^9$，$0 \leq a_i \leq 10^{18}$。

#### 说明

**题目译自 [COCI2010-2011](https://hsin.hr/coci/archive/2010_2011/) [CONTEST #6](https://hsin.hr/coci/archive/2010_2011/contest6_tasks.pdf) *T1 OKUPLJANJE***，翻译来自 @[一扶苏一](https://www.luogu.com.cn/user/65363)，数据范围略有修改。

## 样例 #1

### 输入

```
1 10
10 10 10 10 10
```

### 输出

```
0 0 0 0 0
```

## 样例 #2

### 输入

```
5 20
99 101 1000 0 97
```

### 输出

```
-1 1 900 -100 -3```

# 题解

## 作者：Utilokasteinn (赞：14)

大水题，入门水平。不过要注意数据范围，不开long long见祖宗。

思路很简单，就是先算出总人数，就是l*p。然后把每个报纸的报道人数减去总人数就是答案，代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long l,p,a[6];//一定要开long long，否则全部WA 
	cin>>l>>p;//输入会场面积和每平方米上的人 
	for(int i=1;i<=5;i++)
	    cin>>a[i];//输入5个报社报道的人数 
	for(int i=1;i<=5;i++)
	    cout<<a[i]-l*p<<" ";//输出相差值 
	return 0;//结束 
}
```
谢谢观赏

---

## 作者：Into_qwq (赞：5)

直接开始写吧

因为会场是$l$平方米,每平方米有 $p$ 人 

~~根据公式~~我们可以求得会场一共有 $l$×$p$人

因为要求输出的是每家报纸刊登人数与实际人数之差

所以我们直接输出每家报纸刊登人数减去实际人数($l$ × $p$)就可以了.

P.S.别忘了输出时数之间的空格

## 代码如下

``` c++
#include<bits/stdc++.h>//万能头
using namespace std;
typedef long long ll;
ll p,l,a[6],sum;
int main()
{
	scanf("%lld %lld",&l,&p);
	sum=l*p;//实际人数
	for(ll i=1;i<=5;i++){
		scanf("%lld",&a[i]);
		printf("%lld ",a[i]-sum);//输出差，别忘了空格
	} 
 	return 0;
}
```

`是不是很简单呢?`

---

## 作者：konglk (赞：2)

俗话说的好：十年OI一场空，不开long long见祖宗所以看到数据范围，首先要开long long！

那么究竟应该怎样算出来实际人数呢？L平方米，每平方米p个人->显然，一共有L\*p个人。

对于输入的刊登人数a，只需要算它与实际人数的差即可。即使a比L\*p小，也可以直接减，因为a-L\*p此时的结果会是负数。

所以代码就很好写了：
```
#include<iostream> 
using namespace std;
int main()
{
	long long x,y,a;//此处x为题意中L，y为题意中p
	cin>>x>>y;
	for(int i=0;i<=4;i++)
	{
		cin>>a;
		cout<<a-x*y<<" ";
	}
	return 0;
}
```
谢谢大家观看。

---

## 作者：bovine__kebi (赞：1)

写在前面：
啊，三年$OI$一场空，不开$long\; long$见祖宗啊/kk

------------
咳咳咳，进入主题，首先我来简化一下题意：
$\text{
给出两个数，和五个标准，求这两个数的乘积与这五个标准的差。}$  

题意简化成这样之后，就直接看代码吧
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//typedef是可以用来自己定义东西的东西，这里就是把long long定义为ll，就是为了不那么麻烦
ll L,P;//输入的两个数
int main()
{
    scanf("%lld %lld",&L,&P);
    ll M=P*L;//卷成一个乘积，之后直接比较就好了，记得开long long/kk
    for(int i=1;i<=5;i++)
    {
        ll a;//记得开long long/kk
        scanf("%lld",&a);
        printf("%lld ",a-M);//直接输出就好了
    }
    return 0;
}
```

---

