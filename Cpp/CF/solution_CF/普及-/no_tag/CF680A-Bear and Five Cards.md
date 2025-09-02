# Bear and Five Cards

## 题目描述

A little bear Limak plays a game. He has five cards. There is one number written on each card. Each number is a positive integer.

Limak can discard (throw out) some cards. His goal is to minimize the sum of numbers written on remaining (not discarded) cards.

He is allowed to at most once discard two or three cards with the same number. Of course, he won't discard cards if it's impossible to choose two or three cards with the same number.

Given five numbers written on cards, cay you find the minimum sum of numbers on remaining cards?

## 说明/提示

In the first sample, Limak has cards with numbers $ 7 $ , $ 3 $ , $ 7 $ , $ 3 $ and $ 20 $ . Limak can do one of the following.

- Do nothing and the sum would be $ 7+3+7+3+20=40 $ .
- Remove two cards with a number $ 7 $ . The remaining sum would be $ 3+3+20=26 $ .
- Remove two cards with a number $ 3 $ . The remaining sum would be $ 7+7+20=34 $ .

You are asked to minimize the sum so the answer is $ 26 $ .

In the second sample, it's impossible to find two or three cards with the same number. Hence, Limak does nothing and the sum is $ 7+9+1+3+8=28 $ .

In the third sample, all cards have the same number. It's optimal to discard any three cards. The sum of two remaining numbers is $ 10+10=20 $ .

## 样例 #1

### 输入

```
7 3 7 3 20
```

### 输出

```
26
```

## 样例 #2

### 输入

```
7 9 3 1 8
```

### 输出

```
28
```

## 样例 #3

### 输入

```
10 10 10 10 10
```

### 输出

```
20
```

# 题解

## 作者：Dimly_dust (赞：2)

这道题实际是穷举法来做的。


------------


1. 先设一个数组，即题中：**给定5个正整数**
```cpp
	int a[10];
	for(int i=1;i<=5;i++) cin>>a[i];

```


---------------



再看看题中：**你可以从中去除2个或3个相同的数。如果没有相同的数，即不能去除。求去除1次后剩余数字的最小和。**

2. 说明什么？说明一般最大的在较大的数前，所以要排数。
```cpp

#include<bits/stdc++.h>
using namespace std;
bool cmp(int x,int y)
{
	return (x>y);
}
int main()
{
	int a[10];
	for(int i=1;i<=5;i++) cin>>a[i];
	sort(a+1,a+5+1,cmp);
	return 0;
}

```


------------


再就是穷举了。

3. 保存后两个或后三个的和。
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(int x,int y)
{
	return (x>y);
}
int s[101];
int main()
{
	int a[10];
	for(int i=1;i<=5;i++) cin>>a[i];
	sort(a+1,a+5+1,cmp);
	int max=-1;
	for(int i=1;i<=5;i++)
	{
		if(a[i]==a[i+1]&&a[i]==a[i+2]) s[i]=s[i]+a[i]*3;
		else if(a[i]==a[i+1]) s[i]=a[i]*2;
		if(s[i]>max)max=s[i];
	}
	return 0;
}
```


------------
好了，现在来看看。

4. 输出结果：
```cpp
	int sum=0;
	for(int i=1;i<=5;i++)
	{
		sum+=a[i];
	}
	cout<<sum-max;//去除2个或3个相同的数中最大的数
```


------------
所以代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool cmp(int x,int y)
{
	return (x>y);
}
int s[101];
int main()
{
	int a[10];
	for(int i=1;i<=5;i++) cin>>a[i];
	sort(a+1,a+5+1,cmp);
	int max=-1;
	for(int i=1;i<=5;i++)
	{
		if(a[i]==a[i+1]&&a[i]==a[i+2]) s[i]=s[i]+a[i]*3;
		else if(a[i]==a[i+1]) s[i]=a[i]*2;
		if(s[i]>max)max=s[i];
	}
	int sum=0;
	for(int i=1;i<=5;i++)
	{
		sum+=a[i];
	}
	cout<<sum-max;
	return 0;
}

```
求通过！！！


---

## 作者：lucky2008 (赞：1)

# CF680A 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF680A)

### 题目大意

给定 $5$ 个正整数，你可以从中去除 $2$ 个或 $3$ 个相同的数 。

如果没有相同的数，即不能去除。求去除 $1$ 次后剩余数字的最小和。

### 思路

这题非常简单，我看了很多题解都用了排序所以我就写一个暴力枚举。

### 坑点

这种要求最大最小的题目 $ans$ 要先初始化。

## AC 代码

最后附上ac代码。
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[6],ans=99999;
int main()
{
	cin>>a[1]>>a[2]>>a[3]>>a[4]>>a[5];
	int sum=a[1]+a[2]+a[3]+a[4]+a[5];
	for(int i=1;i<=5;i++)//两个重复的情况
	{
		for(int j=i+1;j<=5;j++)
		{
			if(a[i]==a[j]) 
				ans=min(ans,sum-2*a[i]); 
		}
	}
	for(int i=1;i<=5;i++)//三个重复的情况
	{
		for(int j=i+1;j<=5;j++)
		{
			for(int k=j+1;k<=5;k++)
			{
				if(a[i]==a[j]&&a[i]==a[k]&&a[j]==a[k]) 
					ans=min(ans,sum-3*a[i]); 
			}		
		}
	}
	cout<<min(ans,a[1]+a[2]+a[3]+a[4]+a[5]);//如果没有重复的情况也不能落下
	return 0;
}
```


---

## 作者：封禁用户 (赞：1)

题目传送>>[CF680A](https://www.luogu.com.cn/problem/CF680A)。  
### 题意简述：  
给定 $5$ 个正整数，如其有 $2$ 个或 $3$ 个相同的数，则你可任选其一方式将其去除。求去除 $1$ 次后剩余数字的最小和。  
### 题目分析：  
要使剩余数字的和最小，则需尽可能去除大值（如果能去除的话）（不能去除数则结果就是这 $5$ 个数的和），需对这 $5$ 个数进行排序。而对于出现既有 $2$ 个数相同，又有 $3$ 个数相同的相同数情况，又不一定往大去除了好，因为万一你去除 $3$ 个并非最靠大的相同数却比去除 $2$ 个最靠大的相同数而造成剩余数字的和最小，我们可以分别计算并比较去除最靠大的 $3$ 个相同数和去除最靠大的 $2$ 个相同数而造成剩余数字的和，其较小值即结果。  
### Code:  
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
#define endl '\n'
ll a[6];   //开数组存数 
ll ans=0,ans_two,ans_three;   //定义数总共和、去除最靠大的2个相同数而造成剩余数字的和、去除最靠大的3个相同数而造成剩余数字的和 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	for(ll i=1;i<=5;i++)
	{
		cin>>a[i];
		ans+=a[i];
	}
	ans_two=ans,ans_three=ans;   //给其赋值，以免出现无相同数而不能去除数的情况 
	sort(a+1,a+1+5);  //排序（默认递增） 
	for(ll i=5;i>=1;i--)
	{
		if(i==1) break;  //没有继续往下举的必要 
		if(a[i]==a[i-1])
		{
			ans_two=ans-a[i]-a[i-1];
			break;
		}
	}
	for(ll i=5;i>=1;i--)
	{
		if(i==2) break;   //没有继续往下举的必要 
		if(a[i]==a[i-1] and a[i-1]==a[i-2])
		{
			ans_three=ans-a[i]-a[i-1]-a[i-2];
			break;
		}
	}
	cout<<min(ans_two,ans_three);   //比较并输出较小值 
	return 0;
 } 
```
### 结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/pagtnqf4.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：帝千秋丶梦尘 (赞：1)

## [题目链接](https://www.luogu.com.cn/problem/CF680A)

第一眼下去，以为是个桶排，仔细一看，只有五个数。。。

我们排序后直接循环一遍判断就好了啦

CODE：

```cpp
#include<bits/stdc++.h>
#define ri register
using namespace std;
int sum,Max;//sum记录总数，Max纪录最多能减去的数目
int a[7];
int main(void)
{
	std::ios::sync_with_stdio(false);
	for(ri int i(1);i<=5;++i)
	{
		cin>>a[i];
		sum+=a[i];//加总起来
	}
	sort(a+1,a+6);//快排
	for(ri int i(2);i<=5;++i)//可以从第二个数开始判断
	{
		if(a[i]==a[i-1]&&a[i-1]==a[i-2])//若有三个数相同
		{
			Max=max(Max,a[i]*3);//取最大值
		}
		else if(a[i]==a[i-1])//三个数判完后看两个数的情况
		{
			Max=max(Max,a[i]*2);//同上
		}
	}
	cout<<sum-Max<<endl;//减一减得最后答案
	return 0;
}
```
QwQ

---

## 作者：happybob (赞：0)

来个map解法

对于这个题目，我的思路是这样的，既然是拿走2或3个一样的，我们把一样的挑出来，每个算出拿走的价值，最后用总数 - 最大价值，类似贪心思路

我采用的是unordered_map，速度会比map快

```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int, int> mp; //定义map

inline int sum(unordered_map<int, int>& x)
{
    int ans = 0;
    unordered_map<int, int>::iterator first = x.begin();
    unordered_map<int, int>::iterator last = x.end();
    for(register unordered_map<int, int>::iterator it = first; it != last; ++it)
    {
        ans += (it -> second) * (it -> first);
    }
    return ans;
}

inline int max(const int& x, const int& y)
{
    return (x > y ? x : y);
}

int main()
{
    int x;
    for(register int i = 1; i <= 5; i++)
    {
        cin >> x;
        mp[x]++;
    }
    int all = sum(mp);
    if(mp.size() == 5)
    {
        cout << all << endl;
        return 0;
    }
    int sum = 0, a, b;
    a = b = 0;
    unordered_map<int, int>::iterator first = mp.begin();
    unordered_map<int, int>::iterator last = mp.end();
    for(register unordered_map<int, int>::iterator it = first; it != last; ++it)
    {
        if(it -> second > 1)
        {
            a = (it -> second >= 3 ? 3 * it -> first : 2 * it -> first);
        }
        b = max(a, b);
    }
    cout << all - b << endl;
    return 0;
}
```


---

## 作者：Cult_style (赞：0)

这道题不算很难，其实只是找到最大而且连续三个以上的数，我们用y来代替，然后找到最大而连续两个的数，我们用x来代替，最后判断**3y**跟**2x**哪个更大，输出所有数的和减去更大的那个数就可以了，不过要先排序

献上代码：
```
#include<bits/stdc++.h>
using namespace std;
int a[10];
int x,y;
int s=1;
//s表示连续的数连续了几个
int ans;
int n=5;
int main(){
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		ans+=a[i];
        	//先累计总和
	}
	sort(a+1,a+1+n);
        //排好序
	for(int i=1;i<=n;i++){
		if(s==3){
        	//一定要单独判断，不然如果等到有不相等的数再判断的话又一直是同一个数的话不会执行此操作
			if(a[i]>y)
				y=a[i];
            		//如果连续了三个并且比以前的大，就替换掉y
			s=1;
            		//赋值回一
		}
		if(a[i]==a[i+1])
			s++;
            	//如果有连续的就加一
		else{
			if(s==2){
				if(a[i-1]>x){
					x=a[i-1];
				}
			}
			if(s==3){
				if(a[i-1]>y){
					y=a[i-1];
				}
			}
			s=1;
		}
	}
	x*=2;
	y*=3;
	printf("%d",ans-max(x,y));
        //找更大的
	
	return 0;
}
```
~~求过求赞~~


---

## 作者：codemap (赞：0)

我用了一种比较简单想的方法:直接开一个数组记录每种删除方式得到的剩下和,最后排下序即可

上代码:
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int a[6],i,s=0,t[11]={},p=0;//t记录每次结果,p记录t数组下标,s记录一下全部的和
	for(i=1;i<=5;i++)
	{
		cin>>a[i];
		s+=a[i];//s记录全部和
	}
	sort(a+1,a+6);//要对a数组排下序才能判断是否有重复
	for(i=2;i<=4;i++)//不能取两边
	{
			if(a[i]==a[i-1]&&a[i]!=a[i+1])//如果只删两个
				t[++p]=s-a[i-1]-a[i];//总和减去这两个
			if(a[i]==a[i-1]&&a[i]==a[i+1])//如果删三个
				t[++p]=s-a[i-1]-a[i]-a[i+1];//总和减去这三个
	}
	if(a[4]==a[5])//要判断一下最后两个是否有删的可能
		t[++p]=s-a[4]-a[5];//总和减去最后两个
	sort(t+1,t+p+1);//对结果数组排序
	if(t[1]==0)//如果没有赋过值(最开始初值为0)
		cout<<s;//就不删,输出总和
	else//如果有删的方案
		cout<<t[1];//输出剩下最小的
	return 0;//完美结束
}
```
# 请勿抄袭

---

## 作者：Lily_White (赞：0)

扫描：枚举所有的删除2个和删除三个的情况，在其中选取最小的一个解。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;char c=cin.get();
	while (c<'0'||c>'9')
	{
		if (c=='-')
			f=-1;
			c=cin.get();
	}
	while (c<='9'&&c >='0')
	{
		x=x*10+c-'0';
		c=cin.get();
	}
	return x*f;
}
int main()
{
	int a[60];
	int s=0;
	memset(a,0,sizeof(a));
	for (int i=0;i<5;i++)
	{
		a[i]=read();
		s+=a[i];
	}
	int ans=s;//注意：必须初始化为s
	for (int i=0;i<5;i++)
		for (int j=i+1;j<5;j++)
			if (a[i]==a[j])
				ans=min(ans,s-2*a[i]);
	for (int i=0;i<5;i++)
		for (int j=i+1;j<5;j++)
			for (int k=j+1;k<5;k++)
			if (a[i]==a[j]&&a[j]==a[k])
				ans=min(ans,s-3*a[i]);
	cout<<ans<<endl;
	return 0;
}
```

---

