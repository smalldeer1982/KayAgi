# Mahmoud and Ehab and the MEX

## 题目描述

**题意描述**

在一片邪恶之地，邪恶博士绑架了Mahmoud和Ehab，因为他们在邪恶信息学奥林匹克竞赛(Evil Olympiad in Informatics,EOI)中的突出表现。邪恶博士又决定给他们一些问题让他们回答。问题如下：

邪恶博士对集合很感兴趣。他有一个包含n个整数的集合。邪恶博士认为，如果一个集合的Mex值恰好为x，那么这个集合就是邪恶的。定义Mex值为一个集合中没有出现的最小非负整数。举个例子，Mex（{0,2,4}） = 1，Mex（{1,2,3}） = 0 。

邪恶博士想让他的集合变得邪恶，因此他会执行一些操作。在每个操作中他可能会加入一个非负整数，也可能删去一个数。请问最少需要多少次操作才能让邪恶博士的集合变得邪恶？

## 样例 #1

### 输入

```
5 3
0 4 5 6 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
1 0
0
```

### 输出

```
1
```

## 样例 #3

### 输入

```
5 0
1 2 3 4 5
```

### 输出

```
0
```

# 题解

## 作者：joy2010WonderMaker (赞：10)

喜提最优解，比第二名快了 **45ms**。优秀的 **285ms+0B** 的最优解。

先分析题目。题目的意思是给定 n 个数，使**最小的没有出现在集合里的数为 x**。也就是说，小于 x 的数必须都出现在集合里，而 x 不能出现在集合里。

前置知识：桶。

桶不仅可以来做桶排，**而且还可以统计出现次数**。

本题中桶的作用：本题需要判断小于 x 和 x 出现的次数。将小于 x 的数每个数都添上一个，也就是是让结果+1。把集合中为 x 的数都去掉，也就是减去 x 在集合中出现的次数。

这样一定很清晰了，大佬们可以到此了，其他人来看一下代码吧。

AC Code:

```cpp
#include<cstdio>
int b[101],ans;//b数组是统计每个数字出现的次数，从而判断要加几个减几个
int main(){
    int n,x;
    scanf("%d%d",&n,&x);
    int a;
    while(n--){
        scanf("%d",&a);
        b[a]++;//统计
    }
    if(b[x]>0){//如果集合里出现x，则加上x出现的次数
        ans+=b[x];
    }
    for(int i=0;i<=x;i++){
        if(b[i]==0&&i!=x){
            ans++;//如果集合里有小于x的数没有出现，则加上一个数
        }
    }
    printf("%d",ans);//输出
    return 0;
}
```


---

## 作者：Moon_Lighter (赞：5)

## 解题思路
利用数组是否为空判断数字是否存在。

**小技巧**

从零到该数字进行遍历, 缺少一个数字需要操作一次, 若该数字在原数列中存在 则需要额外多操作一次。


---

### [$\color{#52C41A}\texttt{AC CODE}$](https://www.luogu.com.cn/record/51497224)
```cpp
#include<bits/stdc++.h>//万能头文件。
using namespace std;
int s[105];
int main() 
{
   ios::sync_with_stdio(0);
   cin.tie(0);
   cout.tie(0);
   int a,b,c;
   while(cin>>a>>b)  
   {
	memset(s,0,sizeof(s));//用sizeof判断s的长度,memset是用来初始化数组。 
	int i=a,d=0;
	for(int i=0;i<a;i++) 
	{
		cin>>c;
		s[c]++;//找存在的数字,然后都+1。 
	}
	for(int i=0;i<b;i++) 
	{
	    if(s[i]==0) 
	    {
		d++;
	    }
	}
	if(s[b]!=0)
	{
		d++;//若该数字在原数列中,或存在将此数+1。 
	}
	cout<<d<<endl;//输出执行次数
	}
    return 0;
}
```

---

## 作者：codemap (赞：2)

一道比较简单的模拟题,连数组都不用开

注意题目并没有说已经排好序(~~不过这对我的过程完全没有影响~~),但是集合代表所有数都不一样

基本想法：

输入时,数一下有多少小于x的数(小于x的数必须全有,而因为都是非负整数,所以只需0到x-1都有出现,需操作的就是没有出现的x-s个)

再判断一下有没有x(如果有要去掉)

没有什么可说的直接上代码
```c
#include<iostream>
using namespace std;
int main()
{
    int n,x,t,i,s=0;//s是计数器
    bool f=0;//f判断有没有x
    cin>>n>>x;
    for(i=1;i<=n;i++)
    { 
        cin>>t;//输入
        if(t<x)//如果小于x
            s++;
        if(t==x)//如果等于x
            f=1;
    } 
    s=x-s;//操作没有出现的
    if(f)//如果有x
        s++;//把x删掉
    cout<<s;//输出
    return 0;//完美结束
}
```


---

## 作者：WsW_ (赞：1)

## 思路：  
因为
>定义Mex值为一个集合中没有出现的最小非负整数。 
>
所以  
当 $a_i>x$ 时对结果不影响，忽略即可。  
当 $a_i=x$ 时应删掉这个数，操作次数加一（$ans+1$）。  
当 $a_i<x$ 时，如果这个数字之前没出现，则计数器加一（$tmp+1$），最终应该添加的数为 $x-1-tmp$，因为是从0开始计数的，所以不用减一，为 $x-tmp$。  
所以，最终的操作次数为 $ans+(x-tmp)$，将 $ans$ 初值设为 $x$，则答案为 $ans-tmp$。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
int a,sum,ans;
bool box[105];
int main(){
	scanf("%d%d",&n,&x);
	ans=x;
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		if(a==x)ans++;
		if(!box[a]&&a<x){
			box[a]=1;
			sum++;
		}
	}
	printf("%d",ans-sum);
	return 0;
}
```

---

## 作者：Ender_NaCl (赞：1)

这道题主要是思维
    
我们希望最小的非负整数为 $x$，那么只需要填上从 $0$ 到 $x - 1$ 的所有数，再删掉$x$这个数就行了

在代码实现，我们需要记录某个数有没有出现。因为如果 $0 \le i \le x - 1$ 出现了，或者 $x$ 没出现，就不需要再更改了

上代码

```cpp
#include <iostream>

using namespace std;

bool a[110];

int main()
{
	int n,x,i,co = 0;
	cin>>n>>x;
	for(i = 1;i <= n;i++)
	{
		int x;
		cin>>x;
		a[x] = true; 
	}
	for(i = 0;i < x;i++) if(!a[i]) co++;  
	if(a[x]) co++;
	cout<<co;
	return 0;
}
```


---

## 作者：清清老大 (赞：0)

## 思路

如果要没有出现的最小非负整数最小值变为 $x$ ，则要把比 $x$ 小的数都加入到集合内，把 $x$ 删去。

可以把比 $x$ 小的非负数数量找出来，再拿 $x$ 减去它，得到要添加的次数，再判断 $x$ 有没有出现，得到要删除的次数，总操作数就是两种操作数量相加。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,x,a,ans = 0;
    cin >> n >> x;
    for(int i = 0;i < n;i ++)
    {
        cin >> a;
        if(a < x)
        {
            ans ++;
        }
        if(a == x)//判断删除也可以放到循环里面来，但是加一要改成减一
        {
            ans --;
        }
    }
    cout << x - ans;
}
```


---

