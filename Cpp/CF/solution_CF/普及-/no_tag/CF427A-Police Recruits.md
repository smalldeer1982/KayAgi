# Police Recruits

## 题目描述

The police department of your city has just started its journey. Initially, they don’t have any manpower. So, they started hiring new recruits in groups.

Meanwhile, crimes keeps occurring within the city. One member of the police force can investigate only one crime during his/her lifetime.

If there is no police officer free (isn't busy with crime) during the occurrence of a crime, it will go untreated.

Given the chronological order of crime occurrences and recruit hirings, find the number of crimes which will go untreated.

## 说明/提示

Lets consider the second example:

1. Firstly one person is hired.
2. Then crime appears, the last hired person will investigate this crime.
3. One more person is hired.
4. One more crime appears, the last hired person will investigate this crime.
5. Crime appears. There is no free policeman at the time, so this crime will go untreated.
6. One more person is hired.
7. One more person is hired.
8. One more person is hired.

The answer is one, as one crime (on step 5) will go untreated.

## 样例 #1

### 输入

```
3
-1 -1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
1 -1 1 -1 -1 1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
11
-1 -1 2 -1 -1 -1 -1 -1 -1 -1 -1
```

### 输出

```
8
```

# 题解

## 作者：Yaixy (赞：5)

# 题意及注意点

- 你有一个银行账户，需要进行 $n$ 次操作。给出 $n$ 以及 $a_1$ 到 $a_n$，如果输入的数为 $-1$，那么**账户余额减 $1$ 或透支金额加$1$**；如果输入的数 $a_i$ 大于 $0$，那么余额加上 $a_i$。

- 输入 $-1$ 时需进行特判，输入的数大于 $0$ 时则不用。

- 此题正解为**模拟** （~~不用说就知道~~

# 思路

分类讨论一下（雾），此题共有两种情况：

- **第一种**：输入 $-1$

此时，如果账户中有余额，那么余额 $--$，如果账户中没有余额，那么透支度数 $++$。

- **第二种**：输入一个大于 $0$ 的数 $x$。

这时候，什么都不用管，在账户余额中加上 $x$。

 _**P.S.**_  需要注意的是，在第二种情况下之所以**不往减少透支这方面考虑**是因为题目中已经说明**充值并不能补回你原来透支的钱**。
 
 接下来，就放代码啦qwq
 
#  代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int ans=0,sum=0,x,n;//ans和sum初值必须为0
int main()
{
    cin>>n;//输入
    while(n--)
     {
        cin>>x;
        if(x<0&&sum<1) ans++;//第一种情况
        if(x<0&&sum) sum--;//同上
        if(x>0) sum+=x;//第二种情况 
	 }
    cout<<ans;//输出
    return 0;
}
```

完结撒花OvO

---

## 作者：infinities (赞：5)

首先得膜拜一下翻译的神仙，这题的背景本来是招募警察+治理犯罪的，不知那位翻译题面的神仙是怎么想的，竟然译成了关于征税+存钱的背景（然而这样也是可做的）

给一下原题面真正的简单翻译：

我们的警察局刚刚成立，刚开始没有警察，但是城里却不断发生犯罪，于是开始招聘警察，但是一名警察一生只能处理一件案子，且没有空闲的警察，这个案件就不会被受理（~~工作效率极其低下，治安极其混乱~~）

现在一共有 $n$ 天(也可以理解为由n个事件)，每天可能会有一件犯罪案件发生(即输入-1)或者警局会招募 $x$ 个人（输入一个大于0的数），求一共有多少案件不会被受理

数据范围：$1\le n\le 10^5$

首先呢我们不难看出这题就是裸的模拟，所以模拟就好啦

$code:$
```cpp
#include<bits/stdc++.h>

int num,n,get,ans;//num为没有能够受理的案件，n为天数，get为获得了案件或者警员，ans统计空闲警员

signed main(){
    std::cin>>n;
    
    for(int i=1;i<=n;i++){
        std::cin>>get;
        
        if(get>0)ans+=get;else //现在还有ans个正处于空闲中的警察
        
        if(get==-1){
            if(ans>0)ans--;else num++;//警员匮乏，犯罪成功，民众受难
        }
    }
    
    std::cout<<num;//这n天有这些案件没有被受理
}

```


---

## 作者：TRZ_2007 (赞：2)

## Solution
这题目是一个典型的~~大~~小型模拟，我们用一个变量$num$来存你充了多少钱，用$ans$来存你欠了多少钱最后兵来将挡一波即可。
## $code$
```
#include <bits/stdc++.h>
using namespace std;

int x,ans,n,num_1;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(x == -1&&num_1 == 0) ans++;//你透支了
		else if(x == -1&&num_1 > 0) num_1--;//你还有钱
		else num_1+=x;//你在充钱
	}
	cout<<ans<<"\n";
}
```

---

## 作者：dk——又哇红题 (赞：0)

题目类型——模拟。

所以，看看就知道，“循环结构”。

如果输入的数大于0，加上它，不然，如果此时卡里总价钱为零，ans+1，代表透支了一元，如果大于零，减去透支的钱。

代码如下
```
#include<bits/stdc++.h>//1111 
using namespace std;
const int N=10000;
int a[N];
int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]>=0)
		{
			cnt+=a[i];
		}
		else
		{
			if(cnt==0)
			{
				ans++;
			}
			else
			{
				cnt+=a[i];
			}
		}
	}
	cout<<ans;
	return 0;
}
```
抄袭有赏

---

## 作者：Autism_ever (赞：0)

### 此题很水
### 原题为招聘警察的题目，不知哪位大佬写成了银行
### 上代码
```cpp
#include<bits/stdc++.h>//万能头 
using namespace std;
int n, sum, ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int a;
		cin>>a;
		if(a<0&&ans<1)//判断 
		{
			sum++;
		}
		if(a<0&&ans!=0)//第二个判断 
		{
			ans--;
		}
		if(a>0)//第三个判断 
		{
			ans+=a;
		}
	}
	cout<<sum<<endl;//输出 
	return 0;//华丽的结尾 
}

```


---

## 作者：_Luminous (赞：0)

### · 题意

------------
~~%%%翻译神仙~~

给定n个数，

①x=-1，说明银行~~抢~~了你的钱；

②x＞0，说明你往银行里充值了x次，并且获得了x次免税。

### · 解题方法

------------
按照题意**模拟**即可。

### · Code


------------
```cpp
#include <iostream>
using namespace std;
int n,sum,ans;
//n表示有n个数，sum表示免税次数，ans表示账户透支次数
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1,x;i<=n;i++){
		cin>>x;
		if(x>0)//充值了x次
			sum+=x;//免税总次数加上x次
		else if(x==-1){//银行来抢钱啦（
			if(sum>0)//如果还有免税次数
				sum--;//那就使用一次免税
			else
				ans++;//账户透支次数++
		}
	}
	cout<<ans<<endl;
    return 0;
}
```


---

## 作者：FJ·不觉·莫笑 (赞：0)

### **一道模拟题**  
### **题意：**  
  现在你的卡里没有钱，接下来$n$天，你每天可以透支一元或充一元，求$n$天后你透支了多少元。  
### **思路：**   
  采用模拟思路（若卡中没钱就透支一元，有钱不透支，但卡中减一元），用$cnt$储存当前卡中的钱，$ans$储存透支的钱数。  
### **代码如下**：  
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[500000];
int main()
{
  	int n,cnt=0,ans=0;//n：总天数，cnt：当前卡中的钱，ans：透支的钱数
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]==-1&&cnt== 0) 
  			ans++;//你卡中没钱且今天要扣钱
		else 
       		 {
  			if(a[i]==-1&&cnt>0) 
  				cnt--;//今天扣钱但你卡中有钱
		    else 
			    cnt+=a[i];//今天你充钱
       		 }
	}
	cout<<ans;//输出透支的钱数
}
```


---

## 作者：2132B (赞：0)

### 题意
首先，~~我不得不说这翻译够牛的~~

这道题题意如下：

第一行，输入一个数$n$。

第二行，输入$n$个数，这些数分两类：

$1$. -1，表示银行~~抢~~征了你一次钱。

$2$.一个正整数$x$，表示你充了x次值（注意：**充了$x$次值相当于免$x$次税**）当银行来抢钱时你没有免税次数，就算是一次透支。

### 思路

这无非就是个膜拟吗！

具体实现：

对于输入的每一个数有如下处理

如果大于$0$，就表明这是一次充值，免税次数加上这个数

如果等于$-1$，就表明这是一次抢钱，这时有两种情况

$1$.有免税次数，消耗一次免税次数

$2$.无免税次数，透支数$+1$

### $Code$

```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int n, x, ans, tot;//ans用来记录透支次数，tot用来记录可用于免税的充值次数
int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)
	{
		cin >> x;
		if (x > 0)
			tot += x;//充值处理
		if (x == -1)//抢钱处理
		{
			if (tot > 0)//有免税次数
				tot--;
			else//无免税次数
				ans++;//透支次数+1
		}
	}
	cout << ans;
	return 0;
}//完结！
```


---

## 作者：KazamiHina (赞：0)

~~咕值没了，于是就来水个题解~~

### 题目大意

这个题目的意思大概是这样：如果 $a[i]$ 是 $-1$，则表示发生案件，需要消耗一个警察，否则表示招募 $a[i]$ 的警察，然后一开始没有警察，求有多少个案件没有处理。

于是可以就按照题意进行模拟

$code:$

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>//头文件，多写好看（bushi）

using namespace std;

int now=0;
int n,in;int ans=0;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&in);
		if((in==-1) && (now==0))ans++;//如果有案件且没有警察，那么这个案件不能处理
		else if((in==-1) && (now>=1))now--;//如果有案件，但是有警察，那么警察减一
		else now+=in;//不然就是招募警察
	}
	printf("%d",ans);//输出
	return 0;
}
```

$qwq$

---

## 作者：Fatelism (赞：0)

这道题是求银行账户里最多透支了多少钱，我们也可以将它转换一下，变为：负数为花掉的钱，若钱不足就先欠着，正数为赚的钱，求账户里最多的欠了多少钱。 
```cpp
#include<cstdio>
using namespace std;
int main(){
	int n,sum=0//银行账户里没有一分钱
   int max；//账户里目前没有欠钱
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		int x;
		scanf("%d",&x);//消费/赚钱记录
		sum+=x;//账户里钱的总数
		if(sum<0&&-sum>max)max=-sum;//如果钱数为负数且绝对值最大，则记录
	}
	printf("%d",max);
	return 0;
}
```


---

## 作者：Cult_style (赞：0)

这道题用模拟就可以了

首先，我们知道，值为-1的数就可以算是把现有的一个人给抵掉了，那我们就可以得出代码

```
#include<bits/stdc++.h>
using namespace std;
int n;
int x;
//表示现有的人
int a;
//输入的数
int ans;
//记录答案
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d",&a);
	if(a==-1){
	    x--;
	    if(x<0)
		ans++;
	}
	else{
           x+=a;
	}
    }
    printf("%d",ans);
	
    return 0;
}
```
是的，我们轻松的WA了。。。

为什么会WA呢，试了一下，发现第三个样例就错了

11

-1-1 2 -1 -1 -1 -1 -1 -1 -1 -1

模拟一下：

i=1的时候,x=-1,ans=1

i=2的时候,x=-2,ans=2

i=3的时候,x=0,ans=2

i=4的时候,x=-1,ans=3

到这时候，我们发现，x一定要在小于1的时候清空，不然没有判的案子也算在了其中，下面就献上AC代码
```
#include<bits/stdc++.h>
using namespace std;
int n;
int x;
int a;
int ans;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d",&a);
	if(a==-1){
	    x--;
	    if(x<0){
		ans++;
		x=0;
	    }
	}
	else x+=a;
    }
	printf("%d",ans);
	
	return 0;
}
```


---

