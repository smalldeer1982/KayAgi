# Balloons

## 题目描述

There are quite a lot of ways to have fun with inflatable balloons. For example, you can fill them with water and see what happens.

Grigory and Andrew have the same opinion. So, once upon a time, they went to the shop and bought $ n $ packets with inflatable balloons, where $ i $ -th of them has exactly $ a_i $ balloons inside.

They want to divide the balloons among themselves. In addition, there are several conditions to hold:

- Do not rip the packets (both Grigory and Andrew should get unbroken packets);
- Distribute all packets (every packet should be given to someone);
- Give both Grigory and Andrew at least one packet;
- To provide more fun, the total number of balloons in Grigory's packets should not be equal to the total number of balloons in Andrew's packets.

Help them to divide the balloons or determine that it's impossible under these conditions.

## 说明/提示

In the first test Grigory gets $ 3 $ balloons in total while Andrey gets $ 1 $ .

In the second test there's only one way to divide the packets which leads to equal numbers of balloons.

In the third test one of the boys won't get a packet at all.

## 样例 #1

### 输入

```
3
1 2 1
```

### 输出

```
2
1 2
```

## 样例 #2

### 输入

```
2
5 5
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
1
10
```

### 输出

```
-1
```

# 题解

## 作者：sheeplittlecloud (赞：3)

## Part 0 翻译补充
题目翻译中没有输入输出数据翻译，所以可能会让大家有些懵，所以这里给出翻译：      

**输入格式：**      
第 $1$ 行一个 $n$ ,表示有 $n$ 袋气球     
第 $2$ 行包含 $n$ 个空格隔开的正整数 $a_i$，表示每袋气球里的气球个数

**输出格式：**    
共 $2$ 行。      
第一行为分给其中一人的气球袋数，           
第二行为每袋的编号。     

## Part 1 分析
因为题目要求分给两人的气球个数不得一致，而且是输出任意一种情况。所以我们将分给一个人的气球个数尽量少，也就是只分一袋，再输出这一袋的编号。     
即：     
```cpp
for(i=1;i<=n;i++) b[i]=a[i];//复制，方便查找位置。
sort(a+1,a+n+1);//排序找出最小的数
for(i=1;i<=n;i++)
	if(a[1]==b[i]) //找到立即退出，i就是最小数所在编号
		break;
cout<<1<<endl<<i;//输出个数和编号
```
但这样还不完整。    

## Part 2 特判
我们发现：   
当 $n=1$ 时，它是没法分的。
当 $n=2$ 且 $a[1]=a[2]$ 时由于会分的相等，所以也是没法分的。    
这种情况下就输出 $-1$ 。

## Part 3 代码     
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,a[1001],b[1001];
int main()
{
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	if(n==1||(n==2&&a[1]==a[2]))
	{
		cout<<-1;
		return 0;
	}
	for(i=1;i<=n;i++) b[i]=a[i];
	sort(a+1,a+n+1);
	for(i=1;i<=n;i++)
		if(a[1]==b[i]) 
			break;
	cout<<1<<endl<<i;
	return 0;
}
```
完结撒花~

---

## 作者：LLGZ (赞：1)

**让我们先分析题面：**

首先，我们要输入$n$个数，每个数包含两个数据一个是它所包含的气球个数（这要我们来输入），另一个是它的序号（这需要我们在输入过程中为它赋值）

也就是↓
```cpp
   	cin>>n;
   	for(int i=1;i<=n;i++)
   	{
   		cin>>a[i].s;
   		a[i].i=i;
   	}
```
是不是很简单？

然后要将这$n$袋气球就要分给两个人，每个人至少分给一袋，输出一种情况即可，

注意：既然每个人至少分一袋，而只输出一种情况即可。

那么我们无论有多少袋都只输出一袋的那种情况，岂不美哉？

但还要注意两点

>1.当只有1袋时，分不了，输出-1

>2.当只有2袋且每袋气球个数相同时，分不了，输出-1

在输出之前，来个$sort$点睛之笔，就完美了

**贴上代码**
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct node
{
	int s,i;
}a[10010];
bool cmp(node x,node y)
{
	return x.s<y.s;
}
int n;
int main()
{
   	cin>>n;
   	for(int i=1;i<=n;i++)
   	{
   		cin>>a[i].s;
   		a[i].i=i;
   	}
   	
   	if(n==1)
   	cout<<-1;
   	
   	else
    if(n==2&&(a[1].s==a[2].s))
   	cout<<-1;
   	
   	else
   	{
       sort(a+1,a+1+n,cmp);
	   
	   cout<<"1"<<endl;
	   cout<<a[1].i;
   	}
	return 0;
}
```


---

## 作者：清清老大 (赞：0)

## 思路

当 $n=1$ 时，显然分不了

当 $n=2$ 时，如果两数相等就不满足题意，没法分。如果两数不相等就各分一袋。

当 $n>2$ 时，为了保证两人分到的数不相等，给第一个人最小的数，所以输出最小值和它的编号。

可以边输入边处理，每次发现最小值时更新最小值和编号。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,a,mina = 302986,minaid;
    cin >> n;
    if(n == 1)
    {
        cout << -1;
        return 0;
    }
    if(n == 2)
    {
        int a2;
        cin >> a >> a2;
        if(a == a2)
        {
            cout << -1;
            return 0;
        }
        else
        {
            cout << 1 << endl << 1;
            return 0;
        }
    }
    for(int i = 1;i <= n;i ++)
    {
        cin >> a;
        if(a < mina)
        {
            mina = a;
            minaid = i;
        }
    }
    cout << "1\n" << minaid;
}
```


---

## 作者：Trollz (赞：0)

### 看题
你需要输入一串数列，把这些数字分给两个人，使得这两个人获得的数字总和不一样。如果无法做到不一样，输出$-1$。

~~这是不是很容易做到！！！~~

### 分析
看到这道题，马上就可以 ~~偷懒~~ 想到思路：

**把最小的数分配给一个人，把其他的全部分给另外一个，不就满足条件了！**

**并且题面说至少分到一袋，如果像上面那么处理，第一行只要输出1就可以了，第二行只要输出这个数列中最小数字的地址就好了！**

那么第一步我们需要找到最小的数字：
```cpp
for(int i=1;i<=n;i++){
		cin>>a[i];
		minn=min(a[i],minn);
}
```
然后再查找一遍数列，如果查找到了最小的数字，存储地址。
```cpp
for(int i=1;i<=n;i++){
	if(minn==a[i]){
		存储地址的变量=i;
		break;
	}
}
```
但是数列**无法满足题意**就会输出```-1```，所以仅有这两个板块的程序是不够的，会导致程序错误。那么怎么判断无法满足题意的情况呢？

**当数列只有一个数字或者数列仅有的两个数字相等的时候无法满足题意！**

当只有一个数字的时候，无法把一个数字分给两个人；仅有的两个数字相等的话，每个人分到的数字必然是相同的！

那么漂亮的程序出来了！
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[10001];
int main(){
	int n,sum=0,minn=39204092;
	int minxia=0;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		minn=min(a[i],minn);
	}//查找最小的数字
	for(int i=1;i<=n;i++){
		if(minn==a[i]){
			minxia=i;
			break;
		}
	}//查找最小数字的地址
	if(n==1||n==2&&(a[1]==a[2])){
		cout<<"-1"<<endl;
	}else{//特判
		cout<<1<<endl;
		cout<<minxia<<endl;
	}
	return 0;
}
```

---

## 作者：Creator_157 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF998A)
### 题意：

有 $n$ 袋气球，每袋气球有$a_i$个气球，将它们分成两组，使每组的气球总数不一样。


------------

### 思路：

#### 特判：

①当 $n$ 等于 $1$ 时，绝对不会分成两组。

②当 $n$ 等于 $2$ 时，如果这两组数量一样，也不会分成不同的两组。

------------

#### 特判之后

让第一个人拿一袋最少的气球就 $OK$

------------
### code

```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;
int n;
struct ball{
    int x,y;
}a[15];
bool cmp(ball a,ball b)
{
    return a.x<b.x;
}
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i].x;
        a[i].y=i;
    }
    if(n==1||(n==2&&(a[1].x==a[2].x)))//特判
    {
        cout<<-1;
    }
    else
    {
        sort(a+1,a+n+1,cmp);//找最少气球
        cout<<1<<endl<<a[1].y;
    }
    return 0;
}
```


---

## 作者：codemap (赞：0)

我用了一种非常无脑的方法:

用一个结构体存每个袋子的编号和内有的气球数目

然后将这些袋子按照内有的气球数目从小到大排序

如果气球数目最小的拿一个袋子内的气球数目不等于其他袋子的总和,那么输出1和第一个袋子的编号即可,如果不是,输出-1(可以自己思考一下为什么)

注意要特判一下n=1的情况

上代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
struct node
{
	int num;//气球数目
	int number;//编号
}a[11];
bool cmp(node x,node y)
{
	return x.num<y.num;//气球数目小的在前面
}
int main()
{
	int n,i,s=0;
	cin>>n;
	if(n==1)//n=1特判
	{
		cout<<-1;//输出-1
		return 0;//直接结束程序
	}
	for(i=1;i<=n;i++)
	{
		cin>>a[i].num;//输入
		a[i].number=i;//编号等于i
	}
	sort(a+1,a+n+1,cmp);//按气球数目从小到大排序
	for(i=2;i<=n;i++)//从第二个开始
		s+=a[i].num;//计算总和
	if(s!=a[1].num)//如果剩下的不等于第一个
		cout<<1<<endl<<a[1].number;//输出1和第一个袋子编号即可
	else//否则
		cout<<-1;//输出-1
	return 0;//完美结束
}
```
# 请勿抄袭

---

