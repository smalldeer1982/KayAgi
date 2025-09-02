# Buy a Shovel

## 题目描述

Polycarp urgently needs a shovel! He comes to the shop and chooses an appropriate one. The shovel that Policarp chooses is sold for $ k $ burles. Assume that there is an unlimited number of such shovels in the shop.

In his pocket Polycarp has an unlimited number of "10-burle coins" and exactly one coin of $ r $ burles ( $ 1<=r<=9 $ ).

What is the minimum number of shovels Polycarp has to buy so that he can pay for the purchase without any change? It is obvious that he can pay for 10 shovels without any change (by paying the requied amount of 10-burle coins and not using the coin of $ r $ burles). But perhaps he can buy fewer shovels and pay without any change. Note that Polycarp should buy at least one shovel.

## 说明/提示

In the first example Polycarp can buy 9 shovels and pay $ 9·117=1053 $ burles. Indeed, he can pay this sum by using 10-burle coins and one 3-burle coin. He can't buy fewer shovels without any change.

In the second example it is enough for Polycarp to buy one shovel.

In the third example Polycarp should buy two shovels and pay $ 2·15=30 $ burles. It is obvious that he can pay this sum without any change.

## 样例 #1

### 输入

```
117 3
```

### 输出

```
9
```

## 样例 #2

### 输入

```
237 7
```

### 输出

```
1
```

## 样例 #3

### 输入

```
15 2
```

### 输出

```
2
```

# 题解

## 作者：Scrutiny (赞：9)


# CF732A Buy a Shovel

破题：我们设答案为$i$,那么$i*k$或$i*k-r$是$10$的倍数。（即求最小的满足要求的$i$）

显然$i=10$是满足条件的，但不一定是最小的。

那么我们珂以枚举$i$:从$1$枚举到$10$，看看有没有比$10$小的满足条件的$i$(显然不会$TLE$)

#### **CODE:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
	int k,r;
	cin>>k>>r;
	for(int i=1;i<=10;i++){
		if(i*k%10==r||i*k%10==0){
			cout<<i;
			return 0;
		}
	}
	return 0;
}

```


---

## 作者：bym666 (赞：3)

# CF732A 【Buy a Shovel】
这道题我用的是枚举（最近我经常用枚举法啊），枚举个数，符合条件直接输出。

代码及详细注释如下：
```
#include <bits/stdc++.h>//万能头文件 
using namespace std;
long long k,t,r,ans=1;//定义（保险起见还是用long long吧） 
int main()
{
	cin>>k>>r;//输入 
	while(1)//一直找下去 
	{
		t=k;
		t*=ans;//需要的价钱 
		if(t%10==0)//如果用10元硬币就能解决了 
		{
			cout<<ans;//输出买的个数 
			return 0;//结束程序 
		}
		if((t-r)%10==0)//如果加上一枚r元硬币能解决了 
		{
			cout<<ans;//输出买的个数 
			return 0;//结束程序 
		}
		ans++;//如果都不能，买的个数加一 
	} 
}               
```


---

## 作者：thename (赞：1)

其实这道题很水

我用的简（~~bao~~）单（~~li~~）枚举法，一次次加十（~~钱~~~~真多~~）最后再判断；

**注意：**r硬币可以不使用，如果测试数据结尾为5，且硬币不为0和5，就会陷入死循环。

```
#include<iostream>
using namespace std;
int k,j,z,d;
int main()
{
	cin>>k>>j;//输入 
	d=j;//记录下第一个数，等会要用 
	while(j%k!=0)//循环 
	{
		j+=10;//每次加上一张面值为10得钞票 ，不要忘了零钱 
		int sum=j-d;//如果是那个死循环数据，这条语句加上下面那条可以算出得数，也就是不加零钱 
		if(sum%k==0){cout<<sum/k;return 0;}//判断并输出不用零钱的得数 
	}
	cout<<j/k;//如果没走那条if语句，那就正常输出 
	return 0;//完美结束 
}
```


---

## 作者：jinhangjie2006 (赞：1)

暴力枚举

```
var
  i,n,r:longint;
 begin
   read(n,r);
  for i:=1 to 10000 do
    begin
     if ((n*i) mod 10=0) or ((n*i) mod 10=r) then//看看买i件商品能不能刚好付完不找零钱，有无穷多的10元，那就看看i件商品就用10元可不可以付完，不可以就再看看把10元付完之后还不够的钱，是不是就是在加上r就可以刚好付清了
        begin 
         write(i);//要i件物品付清了，输出
         exit;//找到了就直接结束
   end;
  end;
end.

```


---

## 作者：shuntian (赞：1)

没有人用dfs吗？？

搜索练手好题
~~根本不像搜索~~

话不多说，上代码：
Code:


```cpp
#include<iostream>
using namespace std;
int x,y;  //x是k,y是r
void dfs(int k)   //买第k把铲子
{
    int sum=x*k;  //用的钱
    if (sum%10==y||sum%10==0) //刚好不多不少
    {
        cout<<k;  //输出他
        return;   //再见
    }
    else dfs(k+1);
}
int main()
{
    cin>>x>>y;
    dfs(1);   //买第一把铲子
    return 0;
}
```

---

## 作者：Trans_Portal (赞：1)

# 解析
暴力枚举物品数量，当总价除以十余下r时，退出循环并输出。

但是注意：r元的硬币可以不使用，导致物品买的数量小于等于10，如果不考虑这点，那么下面三个数据将会死循环。
```
14 1
15 2
16 3
```
所以当总价可以被十整除时，也是符合题意的。
# 代码
```cpp
#include<iostream>
using namespace std;
int main(){
	int i,r,k;
	cin>>k>>r;
	for(i=1;(k*i)%10!=r&&(k*i)%10!=0;i++){}
	cout<<i;
    return 0;
}
```

---

## 作者：chenyilai (赞：0)

- 本题思想：暴力枚举
- 如何实现：根据题意，我们可以枚举Polycarp最少要买商品的数量（后称 $s$）。如果 $s\times k\ \bmod 10=r$ 或 $0$（不使用 $r$ 元硬币），及判断 $s\times k$ 的个位是否 为 $r$ 或 $0$。如果可以，那么Polycarp就可以顺利的买下这样东西。
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main(){
	long long m,n;//变量定义
	scanf("%lld%lld",&m,&n);//读入
	for (int i=1;;i++) 
	//其实这一步可以改成for (int i=1;i<=10;i++),因为当s=10的时候,s*k mod 10=0 ，不过效果一样。
		if (i*m%10==n||i*m%10==0){//如果满足条件
			printf("%d",i); return 0;//输出，并退出主程序。
		}
}
```

---

## 作者：chenpengda (赞：0)

循环，每次累加商品价格，枚举**个位数**（能不能买其实本质就是个位数是不是$0$或者$r$），如果是$0$，那么就可以买这么多商品，用若干个$10$元。如果是$r$,减去这个$r$元也可以用若干个$10$元购买。

以下是参考代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int k,r,cnt=1;
	cin>>k>>r;
	k%=10;//首先取个位
	int firstk=k;
	while(!(k==0||k==r))//为什么这么做已经提过了
	{
		k=(k+firstk)%10;//累加，看个位
		//cout<<cnt<<" "<<k<<endl;
		cnt++;
	}
	cout<<cnt;
} 
```




---

## 作者：不到前10不改名 (赞：0)

//数论水题一道（其实也能暴力）
```
#include<stdio.h>
#include<string.h>
int srx,n,i;
int main()
{
    scanf("%d%d",&n,&srx);
    for(i=1;i<=10;i++)//这里买铲子如果是10把，总价就一定是10的倍数，理由小学三年级就知道
    if(n*i%10==0||n*i%10==srx)//如果单价是5的倍数的话，就是2把，否则就用零钱
    {printf("%d",i);
    break;}//这里不跳的话到10还会再输出
    return 0;
    }

```

---

## 作者：HNYLMS_MuQiuFeng (赞：0)

这道题目已经说的很简单明了了。

## 只要判断n把铲子所需钱数的尾数是否等于0或r即可

下面直接上代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int k,r;
int main()
{
	cin>>k>>r;
	if(k%10==0||k%10==r)//判断是否满足条件
	{
		cout<<1;
		return 0;
	}//判断完以后接下来就是愉快的暴力模拟啦
	for(int i=2;i<=10;i++)//10把肯定够所以只循环到10
	{
		if((k*i)%10==0||(k*i)%10==r)
		{
			cout<<i;return 0;//满足条件就输出并结束程序
		}
	}
 } //所以就这么愉快的AC了呢
```
## 杜绝抄袭，从我做起！！！

---

