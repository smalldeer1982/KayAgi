# Voting for Photos

## 题目描述

给定一个数组，找出出现最多的数，若有多个，输出最后一次出现时最靠前的数。

## 样例 #1

### 输入

```
5
1 3 2 2 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
9
100 200 300 200 100 300 300 100 200
```

### 输出

```
300
```

# 题解

## 作者：Viston (赞：5)

This Explanation is written by viston. (If you do many red subjects ,you'll sometimes see me).

好的让我们开始讲中文！    
这题本来是红题的被我提交过了以后点了入门难度就变橙了？大雾.....    
这道题就开个桶，每次判断桶内的值是否大于最大值，如果大于则更新。
```
#include<bits/stdc++.h>
using namespace std;
int a,b[1000002],c=0,d,e,f,g,h,i,j;
int main()
{
	
	cin>>a;
	for(i=1;i<=a;i++)
	{
		cin>>d;
		b[d]++;//入桶
		if(b[d]>c)//更新最大值
		{
			c=b[d];
			e=d;//存哪位选手
		}
	}
	cout<<e;//输出
	return 0;
}
```

See you Next red subject!

---

## 作者：封禁用户 (赞：1)

## CF637A Voting for Photos
[原题链接](https://www.luogu.com.cn/problem/CF637A)

## 分析
在一个数组中找出现次数最多的数，可以用一个关联容器进行对应计数。题中另有 **出现次数最多的数中，输出最后一次出现时最靠前的数** ，则用一变量记录次数最多且末位置最靠前的数即可。

## 思路
提到关联容器，能够想到 STL 中的容器：
```cpp
map<key , value>name
```
其中 $key$ 为关键字，$value$ 为关键字的值。

在这道题中，我们将其数据类型定义为两个整数型，每个数字与它的出现次数相对应，读入数据时记录 **最大出现次数** 及 **数字的值** ，并用进行判断筛去后面出现的“出现次数相同的数字”，最后得到的数字值即为 **最后一次出现时最靠前的数** 。

## Code
```cpp
#include<iostream>
#include<cstdio>
#include<map>
using namespace std;
map<int , int>b; //建立map 
int x,ans=0,t=0;
int main(){
	int n;cin>>n;
	for(int i=1;i<=n;i++){
		cin>>x;
		b[x]++; //这时关键字为数，其值为出现次数 
		if(b[x]>ans){ //判断出现次数是否大于记录的最大次数，不能用"=" 
		    ans=b[x]; //记录最大次数 
		    t=x; //记录目前位置数字的值 
		}
	}
	cout<<t;
	return 0; //end 
}
```



---

## 作者：封禁用户 (赞：1)

题目传送>>[CF637A](https://www.luogu.com.cn/problem/CF637A)  
### 题意简述  
- 给定 $n$ 个数，求其出现最多者，如有多者输出其最先出完者。  
- $1 \le n \le 1000$，数 $\in[1,1000000]$。  

### 题目分析  
开桶存各数出现次数并记录当前数，如有出现次数更多者则更新，这样即可达求出现次数最多者且为最先出完者的目的。  
### Code:  
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
int n, s, temp, result;   //定义数的个数，数，记录当前最多次数，结果数
int a[1000001];   //开数组记录各数出现次数
int main()
{
	ios::sync_with_stdio(0);   //关同步流加速cin输入和cout输出
	cin >> n;
	while (n--)
	{
		cin >> s;
		a[s]++;   //记录累加当前数出现次数
		if (a[s] > temp)   //如有出现次数更多者则更新
		{
			temp = a[s];    //更新当前最多次数
			result = s;    //更新结果数		
        }
	}
	cout << result;
	return 0;  //结束整个程序
}
```
### 结果（未吸氧）:   
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/4mfubdpu.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：WinterRain208 (赞：0)

###  题意

请返回原题查看。

###  做法

本题思路：桶计数

桶是一个初始值全部为0的数组，可用于求一段区间内，每个数组分别出现了多少次，前提是所有待统计数值要小。

通过用数字作为下标来索引，可以实现线性的统计，但是也有缺点，就是空间要求太大。

这种情况下我们一般使用map来节省不必要的空间，但时间会增多，map另外的好处就是数据结构可以做索引。

本题中数字范围够用，选择时间，用数组计数，读入同时计数并打擂台求最值，最后输出

###  代码

这里给出代码的主要部分。

```cpp
long long n,a[20000005],x,M=-1,ans; 
int main(){
	n=read();
	F(i,1,n){
		x=read();++a[x];
		if(a[x]>M)M=a[x],ans=x;
	}
	write(ans);
    return 0;
}

```

点个赞再走吧！


---

## 作者：guoyicheng_gg (赞：0)

思路简单，就是拿一个桶来记录数出现的次数，再不断更新次数最大值，因为题目说最后一次出现时最靠前的数，就直接用大于号判断就好了
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;//命名空间
const int MAXN=1005;
const int MAXNN=1000000+5;
int a[MAXN];
int b[MAXNN];//定义桶
int main()
{
	int n;
	cin>>n;//输入n
	int maxn=0,ans=0;//最大数以及答案的规定
	for(int i=1;i<=n;i++)//接下来开始循环
	{
		cin>>a[i];
		b[a[i]]+=1;//桶排基本过程
		if(b[a[i]]>maxn)//判断
		{
			maxn=b[a[i]];
			ans=a[i];	//更新答案	
		}
	}
	cout<<ans<<endl;//输出答案
	return 0;//结束程序
}
```


---

## 作者：XMK_萌新 (赞：0)

有些懵逼的交了自己的代码~~然后WA了？~~

改了一下，然后，额，AC咯耶。。

放代码
```
#include <iostream>
using namespace std;
int n,p[1003],x[1000003],lastseen[1000003];
//p是读入的数字
//x是一只桶，存桶内数字（不用担心浮点或负数会爆，底下原文说输入的是positive number哦qwq）
//lastseen是表示每个数字最后一次出现的坐标
int opt,ans,minv=100000+233;
//opt是输出的答案
//ans是答案的数字出现次数（有些懵逼啊），初值为0
//minv是最后一次出现的位置，初值当然要开大点咯qwq
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++) 
    {
        cin>>p[i];
        x[p[i]]++;	//这个数字出现次数++
        lastseen[p[i]]=i;	//偷懒写法，，把当前数字的最后一次出现位置更新到当前位置
    }
    for(int i=1;i<=n;i++)	//对于每个数字
    {
        if(x[p[i]]==ans&&lastseen[p[i]]<minv||x[p[i]]>ans)	//出现次数更多 或 出现次数一样但最后一次出现位置更靠前
        {
            ans=x[p[i]];	//更新
            minv=lastseen[p[i]];	//更新
            opt=p[i];	//更新
            //cout<<"redo"<<i<<endl;
            //cout<<ans<<" "<<minv<<endl;
            //上面两句注释是debug的
        }
    }
    cout<<opt;	//输出
    return 0;	//还是比较简单的
}
```

---

## 作者：_Qer (赞：0)

搞个$O(n)$做法

用map来存每个数出现次数和达成的时间（最后出现的时间），按题目要求取就行了

```cpp
#include <bits/stdc++.h>
using namespace std;
int arr[1010];//存输入的数组
map<int, pair<int, int> > mp;
//map，key是数值，value的前一个是出现次数，后一个是最后出现的时间
int n, cnt1, cnt2, ans;
//n如题，cnt1是当前（扫的时候）最大出现次数，cnt2是出现最多的数最晚出现的时间，ans是输出的答案
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
        ++mp[arr[i]].first;//出现次数+1
        mp[arr[i]].second = i;//更新最晚出现时间
    }
    for (int i = 1; i <= n; ++i) {
        if (mp[arr[i]].first > cnt1 || (mp[arr[i]].first == cnt1 && mp[arr[i]].second < cnt2)) {
        	//有两种情况需要更新当前最优解
            //1、出现次数更多
            //2、出现次数相等但最晚出现时间更早
            cnt1 = mp[arr[i]].first;
            cnt2 = mp[arr[i]].second;
            ans = arr[i];
            //记录当前最优
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

