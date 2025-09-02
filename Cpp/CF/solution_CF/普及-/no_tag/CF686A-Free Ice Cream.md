# Free Ice Cream

## 题目描述

凯和格尔达开了个冰淇凌店。他们最开始有x个冰淇淋。冰淇淋是免费的。人们可以给他们提供d个冰淇淋，也可以从他们这里要d个冰淇淋。若他们的冰淇淋不够给要冰淇淋的人，要冰淇淋的人会失落，他们的冰淇淋不会减少。他们想知道收摊以后，他们还剩多少冰淇淋和有多少失落的人。

## 样例 #1

### 输入

```
5 7
+ 5
- 10
- 20
+ 40
- 20
```

### 输出

```
22 1
```

## 样例 #2

### 输入

```
5 17
- 16
- 2
- 98
+ 100
- 98
```

### 输出

```
3 2
```

# 题解

## 作者：zilingheimei (赞：2)

我觉得这题是真的水也不知道怎么上橙的

于是马上就打好了代码

------------

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,x,ans;//n为人数x为冰淇淋数ans为失落人数
int a[1010]; 
char c[1010];//正负 
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>c[i]>>a[i];
		if(c[i]=='-')a[i]*=-1;//判断正负
		if(x+a[i]>=0)x+=a[i];//判断冰淇淋够不够，够就加上
		else ans++;//不够失落人数++
	}
	cout<<x<<" "<<ans;
	return 0; 
}

```
然后这串代码的核心代码（~~也许因为题太水不算核心代码~~）是这个：

```cpp
if(c[i]=='-')a[i]*=-1;
if(x+a[i]>=0)x+=a[i];
else ans++;
```
这段代码大概这个意思：

如果数字前面符号为负的变成负数

如果现在的冰淇淋加上这个不小于0就加上它

如果小于0说明冰淇淋不够失落人数++

然后怀着信心提交

wa了

------------
想了一下什么原因

发现数字最大10^9所以改了longlong

提交一下就a了

下面完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x,ans;//n为人数x为冰淇淋数ans为失落人数
int a[1010]; 
char c[1010];//正负 
int main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++){
		cin>>c[i]>>a[i];
		if(c[i]=='-')a[i]*=-1;//判断正负
		if(x+a[i]>=0)x+=a[i];//判断冰淇淋够不够，够就加上
		else ans++;//不够失落人数++
	}
    //然后答案就出来了
	cout<<x<<" "<<ans;
	return 0; 
}
```
~~我太菜了只能水橙题解~~

~~以后再也不用int了~~

------------



---

## 作者：我是蒟弱 (赞：1)

## 思路
不断更新、统计总数，有人给就加总数，有人要就判断：

能否给

	给得了
    
		给
        
   给不了
   
		失落人数+1
      
##### ~具体实现看代码~满满的注释~
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int main(){
    long long n/*有n个人*/,now/*现在有的冰淇淋数*/,want/*题目中的d*/,disappointed=0/*失落的人数*/;//必须开long long，要不然会爆掉！ 
    char op;//输入的'+'或'-' 
    cin>>n>>now;//输入第一行 
    for(int i=1;i<=n;i++){//不段来人 
        cin>>op>>want;//输入字符和d 
        if(op=='+'){//给冰淇淋 
            now+=want;//加上 
        }else{//要冰淇淋 
            if(want<=now){//能给 
                now-=want;//给 
            }else{//不能给 
                disappointed++;//失落的人数+1 
            }
        } 
    }
    printf("%lld %lld",now,disappointed);//按照题意输出 
    return 0;
}

```


---

## 作者：asasas (赞：0)

一道模拟题。

如果读入的字符是'+'，直接加就行了，如果是'-'，就有两种情况：

1.读入的数字小于当前有的糖果数，直接减去这个数

2.读入的数字大于当前有的糖果数， 失落的人数就要+1

最后输出当前糖果数和失落的人数即可。

代码：
```cpp
#include <bits/stdc++.h> 
using namespace std;
int main(){
	long long n,x,ans=0;//注意，要开long long
	cin >> n >> x;
	char qwq;
	for (register int i=1;i<=n;i++){
		int d;
		cin >> qwq >> d;//读入符号和当前这个人想要的糖果数
		if (qwq=='+') x+=d;//直接加
		else 
		if (x-d>=0){
			x-=d;//大于直接减
		} 
		else ans++;//否则失落的人数+1
	} 
	cout << x << ' ' << ans;//输出
}
```


---

## 作者：fls233666 (赞：0)

看到题目，整理一下思路，大概就是用**模拟**解决问题。方案如下：

1. 读入$n$和$x$；
2. 读入'+'或'-'和$d$；
3. 如果是'+'，执行x+=d；
4. 如果是'-'，进一步判断，如果$x>=d$就执行x-=d，否则把失落的人数$ans$++；
5. 重复2~4步$n$遍；

代码如下：

```cpp
#include<iostream>
using namespace std;
int main(){
    int n,x,ans=0;
    cin>>n>>x;
    char c;  //存储'+'或'-'
    for(int d,i=0;i<n;i++){
        cin>>c>>d;
        switch(c){  //根据c执行对应操作
            case '+': x+=d; break;
            case '-': if(x>=d) x-=d;
                        else   ans++;
        }
    }
    cout<<x<<" "<<ans<<endl;  
    return 0;
}
```

评测到第$3$个点就 _WA_ 了

## ？？？

我一看数据范围：

$(1<=n<=1000,0<=x<=10^9,1<=d_i<=10^9)$

**10的9次方再加加减减一下早就把int爆了**

开long long int,果然就 _AC_ 了。代码如下：

```cpp
#include<iostream>
using namespace std;
int main(){
    long long int n,x,ans=0,d,i;
    cin>>n>>x;
    char c;
    for(i=0;i<n;i++){
        cin>>c>>d;
        switch(c){
            case '+': x+=d; break;
            case '-': if(x>=d) x-=d;
                        else   ans++;
        }
    }
    cout<<x<<" "<<ans<<endl;
    return 0;
}
```


---

## 作者：打表大蒟蒻 (赞：0)

一道大水题！
~~不知道怎么搞的，最近突然喜欢上刷水题了呢~~
这么一道水题竟然没有题解，那本蒟蒻就来发个题解吧


------------
这道题可以分几种情况来讨论

1.如果读入数据是＋，直接加就行了；

2.如果读入数据是-，又有两种情况

(1)如果减去的数大于总冰淇淋数的话，失落的人数自增1；

(2)如若不然，总数减去就好了。

明白这些后，我就把我的代码信心满满的交上去了
代码在此
```
#include <bits/stdc++.h>
using namespace std;
int main ()
{
	int n, x, d, ans=0;
	char a;
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>d;
		if(a=='+') x+=d;
		else 
		{
			if(x>=d) x-=d;
			else ans++;
		}
	}
	cout<<x<<" "<<ans<<endl;
	return 0;
}
```
可我惊讶的发现，第三个点就WA了，于是，我看了看数据范围。唉，好吧，要开long long.改动一下就AC了

AC代码在此！！！
```cpp
#include <bits/stdc++.h>
using namespace std;
int main ()
{
	long long n, x, d, ans=0;
	char a;
	cin>>n>>x;
	for(int i=1;i<=n;i++)
	{
		cin>>a>>d;
		if(a=='+') x+=d;
		else 
		{
			if(x>=d) x-=d;
			else ans++;
		}
	}
	cout<<x<<" "<<ans<<endl;
	return 0;
}
```
温馨提示：~~十年OI一场空，不开long long见祖宗~~

---

