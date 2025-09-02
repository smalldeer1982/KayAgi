# 3分割ゲーム

## 题目描述

[problemUrl]: https://atcoder.jp/contests/cf16-relay-open/tasks/relay_f

長さが正の整数の紐があります。以下の操作を紐の長さが $ 2 $ 以下になるまで続けます。

- 操作: 紐を $ 2 $ 箇所で切り、長さが正の整数である紐 $ 3 $ つに分ける。 この中で最長のもの $ 1 $ つと最短のもの $ 1 $ つを捨てる。

長さ $ N $ の紐からこの操作を始めたときに、この操作を続けることが出来る回数の最大値を $ f(N) $ とします。

正整数 $ X $ が与えられるので、$ f(N)=X $ となる最大の整数 $ N $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ X\ \leq\ 40 $

## 样例 #1

### 输入

```
2```

### 输出

```
14```

# 题解

## 作者：luckyPidgey (赞：5)

先理解题目的意思：f(x)=n 表示最大操作次数x次时对应的最大绳长。

首先一次操作是什么？将一段绳子切分成三段（都为整数），保留第二长绳子。

操作结束的标志是什么？保留的绳长小于等于2。

那么怎么达到最大操作次数？要让操作次数最多，就要让第二长的绳子尽量长，才能让操作次数尽量大。从而应该让最短的绳子为1，最长的绳子和第二长绳子尽量一样长。如果某次绳长为偶数，操作一次对应三段为：1，第二长绳长，第二长绳长+1；如果为奇数，操作一次对应：1，第二长绳长，第二长绳长（最长和第二长相等）。当绳长为f(x)=max{f(x-1)+f(x-1)+1,f(x-1)+f(x-1)+1+1}=f(x-1)+f(x-1)+1+1=f(x-1)*2+2.得递归式

```c
#include<stdio.h>
long long f(int x){
	if(x==0){
		return 2;
	}else{
		return f(x-1)*2+2;
	}

}
int main(){
	int x;
	scanf("%d",&x);
	printf("%lld",f(x));
	return 0;
}
```


---

## 作者：CZQ_King (赞：3)

这题居然没有人发题解??
![](https://cdn.luogu.com.cn/upload/pic/1436.png)
### 这题很简单,一个for搞~~腚~~定
废话不多说,上代码
```cpp
#include<bits/stdc++.h>//头文件不多说
using namespace std;
long long a,b=2;//一定要用long long,否则在#31-#41会WA
int main(){
    cin>>a;
    for(int i=0;i<a;i++)b=(b+1)*2;//乘法分配律
    cout<<b<<endl;
}
```

---

## 作者：向日葵小班 (赞：3)

**又是一道岛国大水题啊啊，不顾它那~~红红~~的标题所望，小学生水平(~~虽然我也是小学生~~)**

**,由于太这题很~~water~~，不放思路了，直接在程序里讲**

**用递归就行了**

##  放代码时间到 

```cpp
#include<iostream>//一坨头文件
#include<cstdio>
using namespace std;
int n;
long long f[400];//一定要开long long，不然有点会WA!
int main()
{
    cin>>n;
    f[0]=2;//给第一个数组赋2
    for(int i=0;i<=n;i++)
    {
    f[i]=f[i-1]*2+2;//递推算式
    }
    cout<<f[n]<<endl;//输出，注意AT要换行！
    return 0;
}
```

**~~过吧luogu~~**

---

## 作者：不到前10不改名 (赞：2)

```
//本题第一个递推递归题解
#include<stdio.h>
long long n,srx[101];//同各位大佬的说法
int i;
long long lgx(long long n)//递推递归函数
{
    if(srx[n])
    return srx[n];//记忆
    if(n>0)
    srx[n]=lgx(n-1)*2+2;//递推递归式
}
int main()
{
    scanf("%d",&n);
    srx[0]=2;
    lgx(n);
    printf("%lld\n",srx[n]);
}
```

---

## 作者：醉梦未苏 (赞：2)

##### 这是一道简单的红题，~~废话,红题不简单还是红题吗~~

- $\textrm{pyhton}$爬一波

- 由题意,我们能很快的得出递推式:

$f[n]=f[n-1]\times2+2$

其中 $f[0]=2$

- 接下来就能开始愉快的递推了


```python
n=int(input()) #输入
f=[2] #初始值为2
for x in range(1,n+1): #递推
    f.append(f[x-1]*2+2)
print (f[n]) #输出

#很短是不是
```

~~求过，求赞~~

---

## 作者：封禁用户 (赞：1)

这递归...五年级水平。      
这题递归可用函数或过程           
（不过个人认为函数简单，过程的基本上都是回溯）        
上代码：
```pascal
var
    n:longint;
function dg(a:longint):int64;//函数（回溯请出门左转）简单！
begin
    if(a=0)then dg:=2//递归边界
    else dg:=dg(a-1)*2+2; //递归公式
end;
begin
    readln(n);
    writeln(dg(n));//输出
end.

```

---

## 作者：封禁用户 (赞：0)

这道AT红题讲，要最多的操作次数

那么最短的那段最短也就是1

最长的和第二长的要相对接近，力求最长的最短，就是(n-1)/2

### code(代码):
```
#include<bits/stdc++.h>
using namespace std;
long long n,ans=2;//初始化一下
int main()
{
   cin>>n;
   for(int i=1;i<=n;i++）ans=ans*2+2;//变量(无数组)递推
   cout<<ans<<"\n";//cyy等于288___why提醒您:AT不换行，爆零两行泪
   return 0;
}
```
适度抄题解爽，过度抄题解悲

code(代码)中有错误，~~小心(防抄题解)~~

---

## 作者：封禁用户 (赞：0)

题意是怎样使$n$最大

首先,要使最短的那一段长度为$1$,其次剩下的两段长必定度尽量接近,也就是第二长的绳子的长度最大，所以可以推导出递推公式：$a[i]=a[i-1]*2+2$ (其中$a[1]=2$)。

于是就有了如下的代码($c++$)：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[1005];//一定要开long long,不然要爆
int main()
{
	cin>>n;
	a[1]=2;//初始化
	for(int i=2;i<=n+1;i++)
		a[i]=a[i-1]*2+2;//递推公式
	cout<<a[n+1]<<endl;
	return 0;
}

```

$AT$要换行哟

---

## 作者：泰山飞狐 (赞：0)

# **居然没有打表的题解，那我就捷足先打了**


### **表生成器**
```
#include<bits/stdc++.h>
using namespace std;
long long j,i,ans=2;

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	for(i=1;i<=40;i++)
	{
		for(j=0;j<i;j++)
		ans=(ans+1)*2;
		cout<<ans<<",";
		ans=2;
	}
	return 0;
}
```
------------
### **AC代码**
```
#include<bits/stdc++.h>
using namespace std;
long long x;
long long a[43]={0,6,14,30,62,126,254,510,1022,2046,4094,8190,16382,32766,65534,131070,262142,524286,1048574,2097150,4194302,8388606,16777214,33554430,67108862,134217726,268435454,536870910,1073741822,2147483646,4294967294,8589934590,17179869182,34359738366,68719476734,137438953470,274877906942,549755813886,1099511627774,2199023255550,4398046511102};//a[0]不用考虑（x>=1嘛）
int main()
{
	cin>>x;
	cout<<a[x];
	return 0;
}
```
_



---

