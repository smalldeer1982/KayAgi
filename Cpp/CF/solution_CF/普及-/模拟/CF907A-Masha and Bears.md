# Masha and Bears

## 题目描述

A family consisting of father bear, mother bear and son bear owns three cars. Father bear can climb into the largest car and he likes it. Also, mother bear can climb into the middle car and she likes it. Moreover, son bear can climb into the smallest car and he likes it. It's known that the largest car is strictly larger than the middle car, and the middle car is strictly larger than the smallest car.

Masha came to test these cars. She could climb into all cars, but she liked only the smallest car.

It's known that a character with size $ a $ can climb into some car with size $ b $ if and only if $ a<=b $ , he or she likes it if and only if he can climb into this car and $ 2a>=b $ .

You are given sizes of bears and Masha. Find out some possible integer non-negative sizes of cars.

## 说明/提示

In first test case all conditions for cars' sizes are satisfied.

In second test case there is no answer, because Masha should be able to climb into smallest car (so size of smallest car in not less than 21), but son bear should like it, so maximum possible size of it is 20.

## 样例 #1

### 输入

```
50 30 10 10
```

### 输出

```
50
30
10
```

## 样例 #2

### 输入

```
100 50 10 21
```

### 输出

```
-1
```

# 题解

## 作者：YUYGFGG (赞：4)


思路：
- Masha 三辆车都能进，那么一定有$vm\leq car3$。
- Masha 要喜欢最小的那一辆车，那么还要满足$2 \times vm\ge  car3$
- Masha 只喜欢最小的那一辆，那么说明不喜欢最大的和中间大的，那么$2\times vm < car1$，$2\times vm < car2$。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int v1,v2,v3,vm;
    cin>>v1>>v2>>v3>>vm;
    if(vm>2*v3||v3>2*vm||v2<=vm){
        cout<<-1<<endl;
    }
    else{
        cout<<2*v1<<endl<<2*v2<<endl<<max(v3,vm)<<endl;
    }
    return 0;
}
```


---

## 作者：信息向阳花木 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF907A)

写一个连 xxs 都能看懂的题解。

分两点考虑：
* 什么情况下无解？

* 有解的话答案是什么？



------------
#### 无解情况

1. 如果人的身高比小熊身高的两倍还高，那么无解。原因：若要满足 **小熊喜欢小车** 的话，那么车的大小 **一定小于** 小熊身高的两倍，那就相当于人的身高大于车的大小，所以人无法开小车。

2. 如果小熊的身高比人的身高的两倍还高，那么无解。原因和情况 1 类似，若要满足 **人喜欢小车** 的话，那么小熊就无法开小车啦。

3. 如果母熊的身高 **不大于** 人的身高，那么无解。原因：如果母熊喜欢中车的话，那么人也一定会喜欢中车。但人只喜欢小车，矛盾。


#### 有解情况

这个其实很简单。

* 大车：公熊身高的两倍大于等于车的大小，不如车的大小就等于公熊身高的两倍吧。

* 中车：同理，车的大小就等于母熊身高的两倍吧。

* 小车：车的大小小于等于人的身高、小熊的身高的最大值的两倍，但由于人只喜欢小车（也就是说不喜欢中车和大车），所以 小车的大小 $\leq$ 人的身高的两倍 $<$ 中车和大车的大小。（小车要尽量小）所以，车的大小就取 **人的身高、小熊的身高的最大值** 吧。（再小的话，人、熊至少其中一者就开不了车了）



------------
代码已经不难啦，说一下代码里的变量：

$v1$，$v2$，$v3$，$vm$ 分别代表 公熊、母熊、小熊和人的身高。

```cpp
#include <iostream>
using namespace std;
int v1,v2,v3,vm;
int main() {
    cin>>v1>>v2>>v3>>vm;
    if(vm>2*v3||v3>2*vm||v2<=vm) {
        cout<<-1<<endl;
    }
    else {
        cout<<2*v1<<endl<<2*v2<<endl<<max(v3,vm)<<endl;
    }
    return 0;
}
```

---

## 作者：Lucifer_Bartholomew (赞：2)

# 数学计算
本题正向想直接去求车大小不太容易,所以反向想,去求不满足的情况。由题意可知,车不满足时有三种情况:
1. 母熊的高度不大于人的高度
2. 小熊的高度的两倍比人的高度小
3. 人的高度的两倍比小熊的高度小

所以判断以上三种情况是否存在,若存在,即为不满足,输出"-1";否则为满足,随意输出一组满足条件的解,保险起见,大车和中车输出值为大熊和母熊的高度的两倍,小车的高度由于受小熊和人的高度两个因素影响,输出小熊和人的高度中更大的值。
```cpp
#include <cstdio>
#include <algorithm>
#define rr register int
using namespace std;
inline int read()
{
	char ch=getchar();
	if(!(~ch))return 0;
	int f=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}
	int x=0;
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int main()
{
	int v1=read(),v2=read(),v3=read(),vm=read();
	if(v2<=vm||vm>v3<<1||vm<<1<v3)puts("-1");//不满足
	else printf("%d\n%d\n%d\n",v1<<1,v2<<1,max(v3, vm));
	return 0;
}
```
~~我是蒟蒻~~

---

## 作者：lrmlrm_ (赞：0)

# 题意

   masha和公熊、母熊、小熊在一起，身高分别是 $ V_1 $ , $ V_2 $ , $ V_3 $  , $ V_m $，他们有三辆车。公熊能驾驶大车，也喜欢大车。母熊能开中车，也喜欢中车。小熊能开小车，也喜欢小车。  masha  能开大、中、小三辆车，但只喜欢小车。规定一个人或熊能开一辆车当他的身高 $ \ngtr $ 这辆车的大小，喜欢一辆车当他的身高 $ \times 2 \nless $ 这辆车的大小。要求找到大车,中车,小车,大小,如无解输出 $ -1 $。 $ \left( 1 \leq V_1,V_2,V_3,V_m \leq 100 , V_1 > V_2 > V_3 \right) $  
 
# 思路

将大车的大小设为  car1  , 中车的大小设为  car2  ,小车的大小设为  car3 ,那么根据题意,不难得出下面的式子:

```
if(v1>car1||v2>car2||v3>car3||vm>car3||v1*2<car1||v2*2<car2||v3*2<car3||vm*2<car3)printf("-1");
```

化简消掉  car1 , car2 , car3  后,得到:

```
if(v2<=vm||vm>v3*2||v3>vm*2)cout<<-1;
```

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int v1,v2,v3,vm;
int main(){
	scanf("%d%d%d%d",&v1,&v2,&v3,&vm);
	if(v2<=vm||vm>v3*2||v3>vm*2)cout<<-1;
	else printf("%d\n%d\n%d",v1+v1,v2+v2,max(v3,vm));
	return 0;
}
```

---

## 作者：zplqwq (赞：0)

# CF907A

Hello 

在颓废了非常久后我终于回来了。

## 题目分析

个人认为题意很明确，而且一上来应该就可以感受到这是一道数学题。

可能会有人第一想法是正面去算车的大小，也不是不可以，只是有点难算。

我们可以先考虑**不满足的情况**。

+ 母熊的高度$≤$人的高度​
+ 小熊的高度$*2＜$人的高度
+ 人的高度$*2＜$小熊的高度

即

```c++
vm>2*v3 or v3>2*vm or v2<=vm
```

接下来，什么情况满足呢？

只要不是不满足的情况即可。

**注意**这**不等于**可以随便输出，为了保险起见，我们可以把大车和中车值设为大熊和母熊的高度的两倍。而小车的高度由于会接受小熊和人的高度两个因素影响，我们输出小熊和人的高度中更大的值。

即

```C++
cout<<2*v1<<endl;//大车
cout<<2*v2<<endl;//中车
cout<<max(v3,vm)<<endl;//小车
```

## 代码

```C++
#include<bits/stdc++.h>
using namespace std;

int v1,v2,v3,vm;

int main()
{
    cin>>v1>>v2>>v3>>vm;
    if(vm>2*v3 or v3>2*vm or v2<=vm)
	{
        cout<<-1<<endl;
    }
    else
	{
        cout<<2*v1<<endl;
		cout<<2*v2<<endl;
		cout<<max(v3,vm)<<endl;
    }
    return 0;
}
```





---

