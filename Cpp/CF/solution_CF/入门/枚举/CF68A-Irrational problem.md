# Irrational problem

## 题目描述

Little Petya was given this problem for homework:

You are given function ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/8b7b3ed792043adfb79a0ac45ad9dbf53894718f.png) (here ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/99fd5677ca5c02520be7595d9b1eaf3e9972e601.png) represents the operation of taking the remainder). His task is to count the number of integers $ x $ in range $ [a;b] $ with property $ f(x)=x $ .

It is a pity that Petya forgot the order in which the remainders should be taken and wrote down only 4 numbers. Each of 24 possible orders of taking the remainder has equal probability of being chosen. For example, if Petya has numbers 1, 2, 3, 4 then he can take remainders in that order or first take remainder modulo 4, then modulo 2, 3, 1. There also are 22 other permutations of these numbers that represent orders in which remainder can be taken. In this problem 4 numbers wrote down by Petya will be pairwise distinct.

Now it is impossible for Petya to complete the task given by teacher but just for fun he decided to find the number of integers ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF68A/5fea0bb6257453a51324f60c43779399607ff809.png) with property that probability that $ f(x)=x $ is not less than $ 31.4159265352718281828459045% $ . In other words, Petya will pick up the number $ x $ if there exist at least $ 7 $ permutations of numbers $ p_{1},p_{2},p_{3},p_{4} $ , for which $ f(x)=x $ .

## 样例 #1

### 输入

```
2 7 1 8 2 8
```

### 输出

```
0
```

## 样例 #2

### 输入

```
20 30 40 50 0 100
```

### 输出

```
20
```

## 样例 #3

### 输入

```
31 41 59 26 17 43
```

### 输出

```
9
```

# 题解

## 作者：Alex_Wei (赞：17)

#### 这题可以 $\mathcal O(1)$ 过。

- 一个数 $\bmod\ p$ 为本身，那么它一定小于 $p$。 

所以我们可以把题目理解为：

求 $\ge a$ ， $\leq b$ 且 $<p1,p2,p3,p4$ 的整数一共有多少个。

下面是代码：
```
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,f;//c,d,e,f分别对应题目中的p1,p2,p3,p4
int main()
{
	cin>>c>>d>>e>>f>>a>>b;
	cout<<max(0,min(min(min(c-1,d-1),min(e-1,f-1)),b)-a+1);
//	设 min(min(min(c-1,d-1),min(e-1,f-1)),b)为k 
//	k是满足题意的最大数（想想为什么） 
//	a是满足题意的最小数 
//	则这个符合题意的数的个数为k-a+1（之前这里忘记+1了QWQ）
//	但是当a>k的时候，答案不是负数，而是0，因为没有数能满足题意 
//	所以答案为max(0,min(min(min(c-1,d-1),min(e-1,f-1)),b)-a+1)
	return 0;
}
```

$\mathrm{Update:2019.2.16:}$ 感谢 [@henry09](https://www.luogu.org/space/show?uid=176101) 指出的错误。

$\mathrm{Update:2019.12.11:}$ 添加 $\mathrm{Latex}$，美化文章。

---

## 作者：桃夭 (赞：5)

**其实这题有种比较简便的解法**~~虽然也没有简便到哪里去~~

**并不需要用到暴力枚举**

能模四个数还是原值的数肯定是比四个数的最小数还要小的数，所以我们先把四个数中最小的数求出来，然后把最小数减去a即可。**值得注意的是，如果最小数大于b的话，需要加特判，否则会出错。**

------------------------------------代码分割线o(TωT)o-----------------------------------
```
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;
int p1,p2,p3,p4,a,b;
int main()
{
	cin>>p1>>p2>>p3>>p4>>a>>b;
	int ans=0;
	int p=min(p1,p2);	//取最小的模 p 
	p=min(p,p3);
	p=min(p,p4);
	if (b<p)	//特判b<p的情况 
	{
		cout<<b-a+1<<"\n";
		return 0;
	}
	if (p-a>0)
	{
		ans=p-a; 
	}
	cout<<ans<<"\n";
    return 0;
}
```

---

## 作者：piggymichael (赞：3)

~~这真是道水题，虽然我很暴力。~~

好，来看看这道题。我先看完了题意，又仔细一看数据范围，心里不禁窃喜。0<=a<=b<=31415 ，最多也就31415嘛，暴力循环，一个一个枚，爆不了！

上代码：

```
#include<bits/stdc++.h>
using namespace std;
int p1,p2,p3,p4,a,b,ans=0;//定义变量
int main()
{
	cin>>p1>>p2>>p3>>p4>>a>>b;//输入
	for(int i=a;i<=b;++i)//循环，开始暴力
		if(i%p1==i&&i%p2==i&&i%p3==i&&i%p4==i)//一个个判，全满足就符合题意。
			ans++;//统计数量
	cout<<ans<<endl;//输出
	return 0;//结束
}
```
如果你是在看不惯这种暴力，可以不用这种方法。或比p1,p2,p3,p4小了就不用判了。但这种方法很简单，也很好想到，快速（指敲代码）AC，耶！

---

## 作者：BCZSX (赞：1)

~~一道超级简单的暴力题目~~

直接区间枚举一下就可以了
```cpp
#include<cstdio>
using namespace std;
int p1,p2,p3,p4,n,m,sum=0;
int main()
{
    scanf("%d%d%d%d%d%d",&p1,&p2,&p3,&p4,&n,&m);//读入
    for(int i=n;i<=m;i++)
    {
        if(i%p1!=i) continue;
        if(i%p2!=i) continue;
        if(i%p3!=i) continue;
        if(i%p4!=i) continue;
        //判断是否符合题意
        sum++;//答案++
    }
    printf("%d",sum);//输出
    return 0;//完美结束
}
```

---

## 作者：emm··· (赞：1)

看看数据，这道题数据不够强，可以暴力枚举过，所以暴力代码如下：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int p1,p2,p3,p4,a,b,ans=0;//记得先把ans赋值为0
	scanf("%d%d%d%d%d%d",&p1,&p2,&p3,&p4,&a,&b);
	for(int i=a;i<=b;i++)//从a到b循环
	{
		if(i%p1==i && i%p2==i && i%p3==i && i%p4==i) ans++;
	}
	printf("%d",ans);
	return 0;
}
```
请不要copy，谢谢

---

## 作者：FP·荷兰猪 (赞：1)

> 题意：输入p1、p2、p3、p4，输入a和b，求在[a,b]这个区间内有多少个数%p1、%p2、%p3、%p4后还是它本身

这题数据还是良心啊！！！暴搜一遍O(b-a)就AC了：
```cpp
#include <iostream>
using namespace std;
int main()
{
	int p1,p2,p3,p4;
	cin>>p1>>p2>>p3>>p4;
	int a,b;
	cin>>a>>b;
	int i,cnt;
	cnt=0;
	for (i=a;i<=b;i++)//i从a到b遍历一遍
	{
		if ((i%p1==i) && (i%p2==i) && (i%p3==i) && (i%p4==i))//找到合法的数结果++
		{
			cnt++;
		}
	}
	cout<<cnt<<endl;//输出cnt
	return 0;
}
```

---

## 作者：txr20050504 (赞：1)

和Pascal的思路（~~甚至是变量~~）一模一样，~~只是没C++的题解有点难受~~
```
#include<bits/stdc++.h>
using namespace std;
long long p1,p2,p3,p4,a,b,sum,i;
int main(){
    cin>>p1>>p2>>p3>>p4>>a>>b;
    for(int i=a;i<=b;++i)
        if ((((i%p1)%p2)%p3)%p4==i) sum++;
    cout<<sum;
}
```

---

## 作者：开心的猪 (赞：0)

这道题是一道十分纯的模拟。在给定的数据范围内循环一遍，如果符合题目条件的话，计数器加一，最后输出就行了。

以下是代码：

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
	int a, b, ans=0, p1, p2, p3, p4;
	scanf("%d%d%d%d%d%d", &p1, &p2, &p3, &p4, &a, &b);
	for(int i=a; i<=b; i++)
	{
		if((((i%p1)%p2)%p3)%p4==i)
		{
			ans++;
		}
	}
	printf("%d", ans);
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

### ~~一大水题QAQ~~
~~数据水的惊人~~
#### 看到楼下大佬们没用函数做，本蒟蒻水一波QAQ
### 因为题目要求要求在a——b的范围内 所以要
	for(int i=a;i<=b;i++)

### 附上代码qwq
华丽的分割线QAQ


------------

	#include<cstdio>//头文件
	#include<iostream>//这个不说啥了
	#include<cstring>//字符串处理
	#include<algorithm>//算法库
	using namespace std;//标准输入输出流
	int p1,p2,p3,p4,a,b,tot=0;//变量定义
    //tot为计数器
	int qwq(){//定义函数
		for(int i=a;i<=b;i++){//进入循环
        //以为要读人范围 那就从a开始 b结束QAQ
		if(((((i%p1)%p2)%p3)%p4)==i){//由题意得
			tot++;//如果如何条件tot+1
			}
		}
		cout<<tot<<endl;//输出
        //换行祈bao福ming
        }
	int main(){//主程序
		cin>>p1>>p2>>p3>>p4>>a>>b;//读入
		qwq();//调用函数
		return 0;//华华丽丽得结束QAQ
	}
    

------------

    

------------


---

## 作者：风之城0 (赞：0)

这是一道很水很水很水很水很水很水很水很水很水很水很水很水很水很水很水……（此处省略1000000000个“很水”）的题，就像A+B  problem一样，数据范围也不大，暴力枚举就行了，希望同学们赶快AC掉，不然到时就又要少一题了（因为可能会因为太水，而被隐藏），不多说了，C++代码如下：
```cpp
#include<bits/stdc++.h> 
using namespace std;
int main()
{int a,b,c,d,x,y,s=0;
 cin>>a>>b>>c>>d>>x>>y;
 for(int i=x;i<=y;i++)
    {if(i%a==i&&i%b==i&&i%c==i&&i%d==i)
       s++;
	}
 cout<<s;
}
```
希望不要有同学与我雷同呦！

---

