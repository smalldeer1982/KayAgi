# [ARC013A] 梱包できるかな？

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc013/tasks/arc013_1

この春から新生活を始める今城くんは引越しを考えています。  
 そのため、自分の荷物をダンボールに梱包しなければなりませんが、今城くんの手元には１つのダンボールしかありません。  
 今城くんはこのサイズ $ N×M×L $ のダンボールに、サイズ $ P×Q×R $ の荷物をできるだけたくさん詰め込みたいです。  
 彼はこのダンボールにどれだけ荷物を詰め込むことができるでしょうか。  
  
 彼はとても几帳面な性格なので、荷物を全て同じ向きで梱包します。  
 さらに、今城くんは荷物が運送中に壊れることを防ぐため、斜めに入れることはありません。  
 つまり、荷物の少なくとも1つの面が、ダンボールか他の荷物のある面にぴったりとくっつくように梱包します。  
 ただし、荷物を横に90度倒すことはできます。  
 入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $ $ L $ $ P $ $ Q $ $ R $

1. $ 1 $ 行目には整数 $ N $ 、 $ M $ 、$ L $ が与えられる。

- $ N $ は今城くんが持っているダンボールのタテの長さです。
- $ M $ は今城くんが持っているダンボールのヨコの長さです。
- $ L $ は今城くんが持っているダンボールの高さです。
- $ 1≦N,M,L≦100 $ であることは保証されています。

5. $ 2 $ 行目には整数 $ P $ 、 $ Q $ 、$ R $ が与えられる。
- $ P $ は今城くんが持っている荷物のタテの長さです。
- $ Q $ は今城くんが持っている荷物のヨコの長さです。
- $ R $ は今城くんが持っている荷物の高さです。
- $ 1≦P,Q,R≦100 $ であることは保証されています。
 
 今城くんがダンボールに詰め込むことができる荷物の数の最大値を $ 1 $ 行で出力すること。  
 また、出力の最後には改行をいれること。 ```
<pre class="prettyprint linenums">
10 10 10
1 1 1
```

 ```
<pre class="prettyprint linenums">
1000
```

- 10\*10\*10のダンボールに、1\*1\*1の荷物を梱包すると、最大で1000個の荷物を梱包することができます。
 
```
<pre class="prettyprint linenums">
10 3 1
2 1 1
```

 ```
<pre class="prettyprint linenums">
15
```

- 10\*3\*1のダンボールに、2\*1\*1の荷物を梱包すると、最大で15個の荷物を梱包することができます。
 
```
<pre class="prettyprint linenums">
5 10 3
2 5 3
```

 ```
<pre class="prettyprint linenums">
5
```

- 5\*10\*3のダンボールに、2\*5\*3の荷物を梱包すると、そのままの向きでは、2\*2\*1の4つの荷物を梱包することができます。
- ですが、この向きを変えて、5\*2\*3の荷物とみなすことで、最大5個の荷物を梱包することができます。
 
```
<pre class="prettyprint linenums">
8 8 8
1 1 9
```

 ```
<pre class="prettyprint linenums">
0
```

- 荷物を90度回転させることはできますが、傾けて入れることは出来ない為、この荷物を入れることは出来ません。

# 题解

## 作者：Kazdale (赞：3)

楼上大佬们竟一个用sort的都没有
------------
sort的头文件是#include <algorithm>（注意拼写）
  
用法：sort(a(数组名) + n(起始元素) , a + m(结束元素));
# 注意：sort是升序排序！！！
上代码：
```cpp
#include <iostream>
#include <algorithm>//头文件
using namespace std;
int main(){
	int a1,a2,a3,b1,b2,b3;//新建变量
	cin >> a1 >> a2 >> a3 >> b1 >>b2 >> b3;//输入
    int n[6] = {(a1/b1)*(a2/b2)*(a3/b3),(a1/b1)*(a3/b2)*(a2/b3),(a2/b1)*(a1/b2)*(a3/b3),(a2/b1)*(a3/b2)*(a1/b3),(a3/b1)*(a1/b2)*(a2/b3),(a3/b1)*(a2/b2)*(a1/b3)};//把数据存在数组里，准备输出
	sort(n+0,n+6);//排序（n+0中的+0可省略）
	cout << n[5] << endl;//由于是升序排序，所以小的在前，大的在后，最后一个数据已经是最大的，也就是第六个，n[5];
	return 0;
}
```
第一篇题解，好激动


---

## 作者：tobie (赞：1)

这道题都已经把各种可能的算式都给出来了，所以我们只需要枚举最大值即可。
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int a1,a2,a3,b1,b2,b3,ans;
int main()
{
    scanf("%d%d%d%d%d%d",&a1,&a2,&a3,&b1,&b2,&b3);//输入
    ans=max(ans,(a1/b1)*(a2/b2)*(a3/b3));
    ans=max(ans,(a1/b1)*(a3/b2)*(a2/b3));
    ans=max(ans,(a2/b1)*(a1/b2)*(a3/b3));
    ans=max(ans,(a2/b1)*(a3/b2)*(a1/b3));
    ans=max(ans,(a3/b1)*(a1/b2)*(a2/b3));
    ans=max(ans,(a3/b1)*(a2/b2)*(a1/b3));//枚举每一个结果
    printf("%d",ans);//输出
    return 0;
}
```


---

## 作者：林家三少 (赞：1)

这道题考的**应该**是：

$$\color{#dedede}\boxed{\color{black}\text{排序|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~}}$$ 
 
因为它已经给出了所有可能答案：

```cpp
(a1/b1)*(a2/b2)*(a3/b3)

(a1/b1)*(a3/b2)*(a2/b3)

(a2/b1)*(a1/b2)*(a3/b3)

(a2/b1)*(a3/b2)*(a1/b3)

(a3/b1)*(a1/b2)*(a2/b3)

(a3/b1)*(a2/b2)*(a1/b3)
我们只需要求出这些答案，再输出最大的即可
```

我看到dalao们都是用了sort、还有直接判断的，但...

$\boxed{\color{red}\text{为什么没人用选排呢？？？}}$

这一切的背后，究竟是网络的扭曲，

还是机房的腐败...keke，跑题了，我们回归正题

其实选排也很容易，循环只需要这样：

```cpp
for(int i=1;i<6;i++)  //注意这里i是＜6
  for(int j=i+1;j<=6;j++)  //注意这里j是i+1
```

接下来就是重点了：交换，我一开始是这样写的：

```cpp
if(c[i]>c[j])
  swap(c[i],c[j]);
```

结果...

![](https://cdn.luogu.com.cn/upload/image_hosting/n0v3akq9.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

然而正确的是这样的：

```cpp
if(c[i]<c[j])  //注意，是c[i]<c[j]，我一开始写成了：c[j]<c[i]
  swap(c[i],c[j]);  //交换
```

上程序：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int a1,a2,a3,b1,b2,b3;  //定义变量
int c[8];  //定义答案数组
int main()
{
	cin>>a1>>a2>>a3>>b1>>b2>>b3;  //输入
	c[1]=(a1/b1)*(a2/b2)*(a3/b3);  //可能的答案1
	c[2]=(a1/b1)*(a3/b2)*(a2/b3);  //可能的答案2
	c[3]=(a2/b1)*(a1/b2)*(a3/b3);  //可能的答案3
	c[4]=(a2/b1)*(a3/b2)*(a1/b3);  //可能的答案4
	c[5]=(a3/b1)*(a1/b2)*(a2/b3);  //可能的答案5
	c[6]=(a3/b1)*(a2/b2)*(a1/b3);  //可能的答案6
	for(int i=1;i<6;i++)  //选派循环
	  for(int j=i+1;j<=6;j++)  
	    if(c[i]<c[j])  //选排交换
	      swap(c[i],c[j]);
	cout<<c[1]<<"\n";  //最后输出那个最大的
	return 0;
}
```


---

## 作者：wushuang0828 (赞：0)

题意很容易理解，因为除号是整除，所以对于Pascal应该是div

所以只要找出

(a1 div b1)*(a2 div b2)*(a3 div b3)

(a1 div b1)*(a3 div b2)*(a2 div b3)

(a2 div b1)*(a1 div b2)*(a3 div b3)

(a2 div b1)*(a3 div b2)*(a1 div b3)

(a3 div b1)*(a1 div b2)*(a2 div b3)

(a3 div b1)*(a2 div b2)*(a1 div b3)

中的最大值

以下就是代码：
```pascal
var
 s,a1,a2,a3,b1,b2,b3:longint;
begin
 readln(a1,a2,a3);
 readln(b1,b2,b3);
 s:=(a1 div b1)*(a2 div b2)*(a3 div b3);//因为s一开始是0，所以不需要比较，就可以赋值
 if s<(a1 div b1)*(a3 div b2)*(a2 div b3) then s:=(a1 div b1)*(a3 div b2)*(a2 div b3);//比较找出两个数中的最大值
 if s<(a2 div b1)*(a1 div b2)*(a3 div b3) then s:=(a2 div b1)*(a1 div b2)*(a3 div b3);//比较找出两个数中的最大值
 if s<(a2 div b1)*(a3 div b2)*(a1 div b3) then s:=(a2 div b1)*(a3 div b2)*(a1 div b3);//比较找出两个数中的最大值
 if s<(a3 div b1)*(a1 div b2)*(a2 div b3) then s:=(a3 div b1)*(a1 div b2)*(a2 div b3);//比较找出两个数中的最大值
 if s<(a3 div b1)*(a2 div b2)*(a1 div b3) then s:=(a3 div b1)*(a2 div b2)*(a1 div b3);//比较找出两个数中的最大值
 writeln(s);//输出最大值
end.
```

---

## 作者：RioBlu (赞：0)

### 首先，本题中间的*被当做斜体处理，所以请看翻译原文

？本题你发现没有？

```
(a1/b1)*(a2/b2)*(a3/b3)

(a1/b1)*(a3/b2)*(a2/b3)

(a2/b1)*(a1/b2)*(a3/b3)

(a2/b1)*(a3/b2)*(a1/b3)

(a3/b1)*(a1/b2)*(a2/b3)

(a3/b1)*(a2/b2)*(a1/b3) 
```

aX aX aX 是一个全排列哎，那就好做了
```
#include<string>
#include<iostream>
using namespace std;
long long a,b,c,d,e,f,m[4],q[4],k[4],ans;
int main()
{
    cin>>a>>b>>c>>d>>e>>f;
    m[0]=a/d;m[1]=a/e;m[2]=a/f;
    q[0]=b/d;q[1]=b/e;q[2]=b/f;
    k[0]=c/d;k[1]=c/e;k[2]=c/f;
    for(int s=0;s<3;s++)
    {
    	for(int v=0;v<3;v++)
    	{
    		for(int n=0;n<3;n++)
    		{
    			if(m[s]*q[v]*k[n]>ans&&s!=v&&s!=n&&v!=n)//3的全排列
    			ans=m[s]*q[v]*k[n];
			}
		}
	}
	cout<<ans<<endl;
    return 0;
}
```

---

## 作者：CZQ_King (赞：0)

### 首先，我们先来个宏定义
```cpp
#define @RioBlu大佬 某人
```

------------

思路：这道题里面，某人已经给出了很明显的做法。我们只需要按照某人给的翻译模拟即可

------------
代码：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a1,a2,a3,b1,b2,b3,a;
int main()
{
    cin>>a1>>a2>>a3>>b1>>b2>>b3;//输入
    a=max(max((a1/b1)*(a3/b2)*(a2/b3),(a1/b1)*(a2/b2)*(a3/b3)),max(max((a2/b1)*(a3/b2)*(a1/b3),(a2/b1)*(a1/b2)*(a3/b3)),max((a3/b1)*(a2/b2)*(a1/b3),(a3/b1)*(a1/b2)*(a2/b3))));//别看了反正也看不懂
    cout<<a<<endl;//输出
    return 0;//结束
}
```
好像有~~一点点~~混乱啊

------------
整齐一点：
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a1,a2,a3,b1,b2,b3,a;
int main()
{
    cin>>a1>>a2>>a3>>b1>>b2>>b3;//输入
    a=max(a,(a1/b1)*(a2/b2)*(a3/b3));
	a=max(a,(a1/b1)*(a3/b2)*(a2/b3));
	a=max(a,(a2/b1)*(a1/b2)*(a3/b3));
	a=max(a,(a2/b1)*(a3/b2)*(a1/b3));
	a=max(a,(a3/b1)*(a1/b2)*(a2/b3));
	a=max(a,(a3/b1)*(a2/b2)*(a1/b3));//比较出方案最优的
	cout<<a<<endl;//输出最优答案
    return 0;//结束
}
```

---

