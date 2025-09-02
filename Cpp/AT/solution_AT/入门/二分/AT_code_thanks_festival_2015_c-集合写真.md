# 集合写真

## 题目描述

有N个人（1<=N<=50）按照从矮到高左右排列，这时候又来了一个人，请你确定这个人的位置

## 样例 #1

### 输入

```
3
11 18 22
17```

### 输出

```
2```

## 样例 #2

### 输入

```
5
30 40 50 60 70
10```

### 输出

```
1```

## 样例 #3

### 输入

```
6
11 24 44 56 78 99
100```

### 输出

```
7```

# 题解

## 作者：蒟蒻取不来名 (赞：13)

蒟蒻的第一个题解，

很暴力,(能过就行)

觉得（非常）啰嗦，

无视注释就行。
```cpp
int n, a[101], i, x;
int main()
{
	cin >> n;//输入原来有几个人 
	for(i = 1;i <= n; i++)
	cin >> a[i];//循环输入开始的人的身高 
	cin >> x;//输入迟到的人的身高 
	if(x > a[n])//判断有没有人比迟到的人高 
	{
		for(i = 1; i <= n; i++)
			if(x < a[i])//如果找到比这个人高的就输出这个人的序号并直接结束程序
			{ 
			cout << i << endl;//endl划重点，当时就是因为这个WA的TAT
			return 0;
			}
	}
	else
	cout << n + 1 << endl;//当没人比他高将他放在最后一个 
	return 0;
}
```
~~据说发题解会加社会贡献分~~
最后各种求过，谢谢啦

---

## 作者：顾z (赞：10)

因为此题给定一个递增序列让我们找一个位置放入一个人(此人身高给定.)

所以我们考虑的做法可以有

 1.插入排序
 
 2.二分查找
 
 3.sort
 
     这里送上二分查找做法 :
      规定左右两端边界,low,high,每次求mid位置
      然后我们可以比较进来人的身高与
      当前mid位置人的身高的大小位置关系
      因为序列是递增的 
      所以我们可以缩减区间范围.
      从而我们可以一步一步的逼近该有的位置

需要注意的地方:
       
      1.岛国的题末尾要加(重点：换行符 ！
      2.区间范围限制 (要不然会死循环 !
送上我优(chou)美(lou)的代码
```cpp
#include<bits/stdc++.h>//万能库
#define RI register int//register加速
int n,I,low,high;
int height[55];
int main()
{
	std::cin>>n;
	for(RI i=1;i<=n;i++)std::cin>>height[i];
	std::cin>>I;//需要进去的人的身高
	low=1,high=n;
	while(low<=high)//区间范围限制
	{
		int mid=low+high>>1;
		if(height[mid]>I)high=mid-1;
		else low=mid+1;
        //根据上面的 就是缩减区间范围
        //如果mid位置人的身高比我高,
        //那我就缩减一下右端范围
        //左端同理
	}
	std::cout<<low;
}
```

---

## 作者：Messi李 (赞：4)

题目大意：输入一些人身高，再输入一个人身高

这个人站哪里，输出他站的位置

思路：当这个人身高小于他前面这个人的时候，输出这个位置

如果没有人比他高，站在最后面

代码
```
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[100];
//数组开大点，在数组没开大卡了很久，谢谢某dalao指点
int main(){
    cin>>n;//输入
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    cin>>m;
    for(int i=1;i<=n;i++)//进行循环，执行自己的思路
    {
        if(m < a[i]){ cout<<i<<endl;return 0;}
        //输出了就马上结束程序，以免重复
    }
    cout<<n+1<<endl;//最高的那位
}
```

---

## 作者：wubaiting2020 (赞：2)

思路：将其先放在数组最后一个，用sort快排后，枚举寻找他的位置。
代码：
```cpp
#include<iostream>
#include<algorithm>//快排的头文件
using namespace std;
int main()
{
	int n,a[55],m;
	cin>>n;//人数
	for(int i=1;i<=n;i++)cin>>a[i];//其他人的高度
	cin>>m;//读入后来的人
	a[n+1]=m;//放入数组
	sort(a+1,a+n+2);//快排，（因为又来了一个人所以为n+2）
	for(int i=1;i<=n+1;i++)//多来了一个人，为n+1
    if(a[i]==m){cout<<i<<endl;return 0;}//如果为这个人输出他所在的位置
	return 0;
}
```

---

## 作者：jiangXxin (赞：2)

这道题，其实应该是比较容易想的，首先输入一系列数据，就不用说了，主要是要注意的就是要对数据进行特盼，比如这个后来的人是前面N人中最高的，或者是最矮的，之后一个循环就OK了，一旦发现符合条件的，输出，结束

贴代码：

```cpp
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;
int a[9999];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	int x;
	cin>>x;
	if(x<a[1])//特判
	{
		cout<<"1"<<endl;
		return 0;
	}
	if(x>a[n])//特判
	{
		cout<<n+1<<endl;
		return 0;
	}
	for(int i=1;i<=n;i++)
	{
		if(x>=a[i]&&x<=a[i+1])//发现符合条件的
		{
			cout<<i+1<<endl;//输出
			return 0;//结束
		}
	}
    return 0;
}
```

---

## 作者：lzxhdxx (赞：1)

# ~~我又来发题解了~~
### 题目简述：

有N个人吃饭，他们的身高是H1,H2……HN，后来又来了一个人，他的身高是X。他们位置的排列按从矮到高排，问后来的人应该排第几位？

### 解决思路

1.普通做法：统计N个人的身高，然后找比迟到的人矮的人数，输出这个人数+1（因为比他矮的人数是说在他前面已经被占的位置数，所以要+1）

2.二分查找，这个在这里就不讲了（~~我也不会~~）

3.排序，这种方法有很多种解决方案，前面的大佬拿出了快排，插排一系列排序方法，这里蒟蒻的我拿一个桶排！

题目给出1<=H<=100，桶排完全可以接受！

## Code:
```cpp
#include <iostream>

using namespace std;

int book[110] = { 0 };
int n, m;

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)//输入n个人的身高
	{
		int tmp;
		cin >> tmp;
		book[tmp]++;//下标为tmp的桶+1
              //意思就是身高为tmp的人数+1
	}
	cin >> m;  //后来的人的身高
	int sum = 0;  //sum是有多少人比后来的人矮
	for (int i = 1; i <= m; i++)
		sum += book[i];  //遍历比m矮的桶，把总人数加起来
	cout << sum + 1 << endl;  //AT的题要换行！
	return 0;
}
```
注意：

1.输出一定不要忘了sum+1

2.AT的题一定不要忘了换行

3.桶排的题目数组一定要开的够大

4.不要忘了return 0;

到这里，这道题目就完美AC了！

---

## 作者：yu__xuan (赞：1)

这题看到的第一眼以为需要排序，实际上排序真的可以做。但不排序也可以。
思路为：因为不存在重复的身高，所以完全可以开一个数组来存这个身高是否有人。最后只需要从小到大去找最后一个人的身高即可。记下他前面有多少人，最后输出人数加一。。。
代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
bool flag[1001];

int main()
{
	int n,m;
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		int a;
		cin>>a;
		flag[a]=1;
	}
	int b;
	cin>>b;
	flag[b]=1;
	int sum=0;
	for(int i=1;i<=1001;++i)
	{
		if(i!=b&&flag[i]==1)
		{
			sum++;
		}
		if(i==b) break;
	}
	cout<<sum+1<<endl;
	return 0;
}
```
（就是这样了，望通过，喵呜~）

---

## 作者：MaoHanKun (赞：1)

	#include<cstdio>//本题主要运用了设墙法（为了判断出插入的数比原数组中任何数都大的情况）。 
	using namespace std;
	int n,s[55],x；
	int main(){
		scanf("%d",&n);
		for(int i=0;i<n;++i) scanf("%d",&s[i]);
		scanf("%d",&x);//以上三行都是输入。 
		s[n]=1<<30;//在数组后设一堵墙。
		for(int i=0;i<=n;++i)//循环时将墙包含进去。 
			if(x<=s[i]){//当小于等于这个数时，就输出i+1，应为下标为0。 
				printf("%d\n",i+1);
				break;
			}
		return 0;
	}//完美结束。

---

## 作者：Cambridge (赞：0)


小学生又来发题解了！

这道题十分简单，十分适合新手。我们先把原先队列从小到大排序，再读入新来的人，逐个逐个位置跟他进行比较，找出他应该在的地方，输出即可。真的符合红题。

    #include<iostream>
    #include<cstring>
    #include<cstdio>
    #include<cmath>
    #include<string>
    #include<cstdlib>
    #include<algorithm>//文件头不解释
    using namespace std;
    int n,m;
    int a[1000];//定义变量
    int main()
    {
    cin>>n;//有n个人
    for(int i=1; i<=n; i++)cin>>a[i];//读入数据
    sort(a+1,a+1+n);//从小到大排序
    cin>>m;//读入新来的人
    a[0]=-210;//特殊情况处理
    for(int i=1; i<=n; i++)
    {
        if(a[i-1]<m&&m<a[i])
        {
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<n+1<<endl;//如果新来的人比其他人都高，排n+1个。
    return 0;
    }

好了，本蒟蒻就讲到这里，希望对读者有所帮助。


---

