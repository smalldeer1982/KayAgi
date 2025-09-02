# Cinema Line

## 题目描述

新电影《虎胆龙威》刚刚上映了！  
有n位观众正~~焦急地~~站在电影院售票处并且排成了一列长队。他们或多或少都有**一张**100,50或是25卢布（毕竟是毛子的oj网站）的钞票。  
一张《虎胆龙威》的票价是25卢布。  
那么问题是：如果这位售票员最初没有钱，并且严格地按照人们排队的顺序（有素质）卖票，售票员能否将一张票卖给每位观众并且找零吗？

## 样例 #1

### 输入

```
4
25 25 50 50
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
25 100
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4
50 50 25 25
```

### 输出

```
NO
```

# 题解

## 作者：爬行者小郑 (赞：3)

## 这道题一定要考虑清楚
题目中说有3中面值的钱币，一定要想清楚100块的可以用3个25块的**或者1个50，1个25**来找钱，并且要尽可能用这种方法，因为这样可以节省25的个数，毕竟50的零钱只有100能用。如果没有注意就会像我第一次的代码一样：

```cpp
#include <iostream>
using namespace std;
int n;
int tot;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;//输入钱数
		x/=25;//方便计算，所有的都除以25
		if(x==1)tot++;//如果是25，总和加1
		else
		{	
			x-=1;//先付钱
			if(x>tot)//找不开
			{
				cout<<"NO"<<endl;
				return 0;
			}
			tot-=x;//用掉找的钱
		}
	}
	cout<<"YES"<<endl;
	return 0;
} 
```

在这里我没有考虑50的个数，只用了一个tot来统计25的个数，这样一定是不行的。

修改后：
```cpp
#include <iostream>
using namespace std;
int n;
int tot25,tot50;//分开存放，无需统计100的
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(x==25)tot25++;//分三种情况讨论
		else if(x==50)
		{
			if(tot25<1)
			{
				cout<<"NO"<<endl;
				return 0;//直接退出
			}
			else
			{
				tot25--;//25的用一个
				tot50++;//50的加一个
			}
		}
		else
		{
			if(tot50>=1&&tot25>=1)//最优方法
			{
				tot50--;
				tot25--;
			}
			else if(tot50<1&&tot25>=3)//次好方法
			{
				tot25-=3;//用掉三个
			}
			else
			{
				cout<<"NO"<<endl;
				return 0;
			}
		}
	}
	cout<<"YES"<<endl;
	return 0;
} 
```
## C党参考
```c
#include <stdio.h>//标准输入输出流
int n,i;//循环变量一定要放在外面
int tot25,tot50;
int main()//剩下的和刚才一样
{
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if(x==25)tot25++;
		else if(x==50)
		{
			if(tot25<1)
			{
				printf("NO\n");
				return 0;
			}
			else
			{
				tot25--;
				tot50++;
			}
		}
		else
		{
			if(tot50>=1&&tot25>=1)
			{
				tot50--;
				tot25--;
			}
			else if(tot50<1&&tot25>=3)
			{
				tot25-=3;
			}
			else
			{
				printf("NO\n");
				return 0;
			}
		}
	}
	printf("YES\n");
	return 0;
} 
```
谢谢大家

---

## 作者：tryrtj (赞：0)

题解应当写仔细一点

虽然是道水题，但还是仔细分析一下：

面值只有25，50，100，明显25不需要找钱，50只能用一个25的找回，100可以用一个50与一个25或三个25找回，在找100的时候，要尽量用50的，因为50的只能找回100，所以程序就很简单了，代码如下：

```
#include<iostream>
using namespace std;
int q25=0,q50=0,q100=0;
int n;
int main(){
    cin>>n;
    int q;
    for(int i=0;i<n;i++){
        cin>>q;
        if(q==25)q25++;
        if(q==50){
            if(q25>0){
                q25--;
            }
            else{
                cout<<"NO"<<endl;
                return 0;
            }
            q50++;
        }
        if(q==100){
            if(q25>0&&q50>0){
                q50--;
                q25--;
            }
            else if(q25>=3){
                q25-=3;
            }
            else {
                cout<<"NO"<<endl;
                return 0;
            }
            q100++;
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
```
ty

---

## 作者：　　　吾皇 (赞：0)

### 直接根据题意模拟便可，但要注意一些细节
```cpp
#include<bits/stdc++.h>
using namespace std;
#define F(i,a,b) for(int i=a;i<=b;i++)
int n,a[100001],x,y;//x,y分别代表售货员有几张50元,25元,毕竟100元没用 
int main(){
	cin>>n;
	F(i,1,n) cin>>a[i];
	F(i,1,n) {
		switch(a[i]){
			case 100:{
				if((x>=1&&y>=1)||y>=3){
					if(x>=1) x--,y--;
					else y-=3; 
				}//如果有1张50,一张25或者三张25就可以,否则输出NO 
				else {
					cout<<"NO";
					return 0;
				}
				break;
			}
			case 50:{
				if(y>=1) {
					x++;
                    y--;
				} //有1张25,同时收入50
				else {
					cout<<"NO";
					return 0;
				} 
				break;
			}
			case 25:{
				y++;//25不用找，直接收入 
				break;
			} 
		} 
	}
	cout<<"YES";//不是不能当然就可以啦
	return 0; 
}
```
部分注释标在上面，这题难度入门左右

---

## 作者：yuangq (赞：0)

这题很简单，只要模拟即可

~~~
#include<iostream>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<climits>
#include<vector>
using namespace std;
int a,b,c;//a表示25元，b表示50元，c表示100元  
int n; 
int main()
{
    cin>>n;//n个顾客 
    for(int i=1;i<=n;i++)
    {
    	int mon;//n块钱 
    	cin>>mon;
    	if(mon==25)//如果为25元直接放入25元的钱堆 
    	{
    		a++;
    	}
    	if(mon==50)//如果为50元 
    	{
    		if(a>=1)//如果有25元则找给他 
    		{
    			a--;
    			b++;
    		}
    		else//没有就输出NO 
    		{
    			cout<<"NO";
				return 0; 
    		}
    	}
    	if(mon==100)//如果为100元 
    	{
    		if(b>=1 && a>=1)//找一张50一张25 
    		{
    			b--;
    			a--;
    			c++;
    		}
    		else if(a>=3)//找三张25 
    		{
    			a--;
    			a--;
    			a--;
    			c++;
    		}
    		else//没有就输出NO
    		{
    			cout<<"NO";
				return 0; 
    		}
    	}
    }
    cout<<"YES";//如果都能找开就输出YES 
    return 0;
}
~~~

---

