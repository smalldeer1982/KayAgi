# Business trip

## 题目描述

多么令人开心啊！Petya的父母去了一个长达一年的商业旅行并且把这个爱玩的孩子独自留下了。Petya高兴到了极点。他跳上床并扔了一整天的枕头，直到...
（这和做题有什么关系，汗）

今天Petya打开橱柜发现了一个吓人的字条。他的父母给他留了家务：他应该给他们最喜爱的花浇一整年的水，每一天，无论早上，下午，还是晚上。“等一下”——Petya想。他明白一个事实，如果他在一年中的第$i$月（$1\leq i\leq12$）完成父母的任务，这个花就会生长$a_i$厘米，并且如果他在第$i$月不给花浇水，花在这个月就不会长。他的父母不会相信他给花浇过水了，如果这花生长的严格少于$k$厘米。

帮助Petya选择最少的月数浇花，使得这花能够长得不少于$k$厘米。

## 说明/提示

让我们考虑第一个样例。在第七个月和第九个月给花浇水。然后花长五厘米。

第二样例Petya的父母会相信他，即使花不生长（$k=0$ ）。所以，Petya可能根本不浇花。

Translated by @Khassar

## 样例 #1

### 输入

```
5
1 1 1 1 2 2 3 2 2 1 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
0
0 0 0 0 0 0 0 1 1 2 3 0
```

### 输出

```
0
```

## 样例 #3

### 输入

```
11
1 1 4 1 1 5 1 1 4 1 1 1
```

### 输出

```
3
```

# 题解

## 作者：hensier (赞：2)

这道题其实归结下来可以算是一道贪心题。这种贪心题只需要配合$sort$即可。

需要注意的是本题的一些特判——如果$n==0$直接输出$0$，如果$12$个月总和$S$满足$S<n$直接输出$-1$。这些特判考虑之后，再进行程序的其他处理。

代码如下：

```cpp
#include<cstdio>
#include<algorithm>//sort（快排STL大法）的头文件
int n,i,a[12],s,S;
int main()
{
    scanf("%d",&n);
    if(!n)//特判
    {
        printf("0");
        return 0;
    }
    for(;i<12;i++)scanf("%d",&a[i]),S+=a[i];//边输入边求和
    if(S<n)//特判
    {
        printf("-1");
        return 0;
    }
    std::sort(a,a+12);//快排
    for(i=11;i>=0;i--)//从后往前推
    {
        s+=a[i];//累加
        if(s>=n)break;//满足就跳出循环
    }
    printf("%d",12-i);//输出12-i（i为循环变量，因为是从后往前，所以要用12减掉）
}
```

---

## 作者：小张的8424 (赞：1)

又发现一道没题解的题目，又不算太难，于是就写了这一篇题解。
## 题目意思
$12$个月中，Petya知道每个月如果浇水植物生长的高度$a_i(0\leq a_i\leq 100)$厘米（如果不浇水植物就不生长），求最少浇水多少个月使植物生长高度不少于$k(0\leq k\leq 100)$厘米，输出浇水月数。如果无论如何都没法长$k$厘米则输出-1。

[题目传送门](https://www.luogu.org/problemnew/show/CF149A)
## 分析
假如我只浇水$1$个月，那么肯定要选生长高度最大的那个月。就算我要浇水好几个月，先选择最大的那个月也绝对不会亏。

所以，选择最大的那几个月就是正解，因为换成别的月会导致生长高度下降，可能达不到$k$，那样就需要多浇水$1$个月才能达到要求，这样就不是最优了。

以下是正解方法：

1. 排递减序
2. 从第$1$个开始选，直到达到$k$为止
3. 统计一下要浇水的月数，这就是答案。

AC代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    bool cmp(int a,int b);
    //排序方案函数申明
    int a[12],n,i,sum=0;
    cin>>n;
    //定义和输入
    for(i=0;i<12;i++)
        cin>>a[i];
    //依然是输入
    sort(a,a+12,cmp);
    //按排序方案函数来排序，调用cmp函数
    for(i=0;i<=12;i++)
    {
        if(sum>=n)
        //如果定下来的生长高度比要求高，就可以停了。
        {
            //必须先判断，样例中有不需要浇水的情况
            cout<<i<<endl;
            //这里的i代表已扫描的月数
            //由于是递减序，扫描过的都是大的
            //所以扫描过的都已经定下来了
            return 0;
            //由于任务完成，直接退出程序
        }
        if(i<12)
            sum+=a[i];
        //当月数比13月小的时候累加
        //因为没有13月
        //这里第i月其实代表第i+1月
    }
    cout<<-1<<endl;
    //能走到这里说明全都浇水都没法完成任务，输出-1
    return 0;
}
bool cmp(int a,int b)
//前面已经申明，可以放心使用
{
    return a>b;
    //排序方法，a>b代表前面大于后面，即递减序
}
```

---

## 作者：YUYGFGG (赞：1)

**宣传本人[博客](http://yuygfgg.tk)**

思路：贪心。要让浇水的月份最少，就要让每个浇水月收益最大，所以做法是先将每个月的收益从大到小排序，尽量在收益大的月份浇水。

用multiset排序，每次取第i大累加直到满足要求即可
```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int> a;
int main(){
	int n,tmp,d=0,s=0,k;
	cin>>k;
	for(int i=1;i<=12;i++){
		cin>>tmp;//输入临时变量再插入
		a.insert(tmp);
	}
	if(k==0){//目标为0的话直接输出0
		cout<<0<<endl;
		return 0;
	}
	set<int>::iterator it=a.end();//指向最大值的iterator
	it--;//.end()指向的是最大值还要后面一个，所以要--
	for(;it!=a.begin();it--){
		d+=*it;
		s++;
		if(d>=k){//完成
			cout<<s<<endl;
			return 0;
		}
	}
	d+=*it;//如果不补一次循环，第一个元素不会被遍历到
	s++;
	if(d>=k){//完成
		cout<<s<<endl;
		return 0;
	}
	cout<<-1<<endl;//无法完成目标
	return 0;
}
```


---

## 作者：zzhhf (赞：1)

## 为什么都要直接调用排序。
## 这样领悟不到排序的精髓。
我这里是用的选择排序。我的思路是这样的：

    1.输入12个数。
    2.进行选择排序。
    3.用while循环进行判断如果k>0或者i>12就跳出循环。
AC代码：

    #include<bits/stdc++.h> 
    using namespace std;
    int a[100];
    int main()
    {
    	int i,j,k,s,n,t;
    	bool p;
    	cin>>k;
    	n=12;
    	for(i=1;i<=n;i++)       
    	  cin>>a[i];            //输入12个数
    	for(i=1;i<n;i++)
    	  for(j=i+1;j<=n;j++)
    	    if(a[i]<a[j]){       //如果a[j]比a[i]大就交换
    	    	t=a[i];
    	    	a[i]=a[j];
    	    	a[j]=t;        //选择排序
    		}
    	i=0;
    	p=true;  
    	while(k>0)   
    	{
    		i++;     //累加天数
    		k-=a[i];
	    	if(i==12&s<k)  //如果i>12就输出-1
    		{
    			cout<<-1<<endl;
    			p=false;     //要把p改成错误的
    			break;   //跳出循环语句不加会死循环
    		}
    	}
    	if(p==true)cout<<i<<endl;  //如果k<=0就正常输出
    }

---

## 作者：Arghariza (赞：0)

来来介绍黑科技了

首先我们想一想这题咋做

其实很简单，假设——

```a[] = 1 2 3 2 1```

于是我们可以把他从大到小排排序（为什么是从大到小呢？是因为我们尽量选择长得厘米多的月份，这是一个贪心的思想）：

```a[] = 3 2 2 1 1```

然后我们从```a[1]```开始选月份，如果```k```大于0的话，我们就选择a[ans]，并且ans++:

```
while(k > 0) {
    ans++;
    k -= a[ans];
}
```

那么问题来了，怎么从大到小排序呢？

- 冒泡排序，桶排序，归并排序，快速排序.....懒得打

所以就用sort吧！

那么问题又来了：

- 排序函数懒得打，咋办？

~~你这么懒，咋不去shi呢~~

广告：本C++隆重推出functional头文件！内含从大到小排序函数```greater<int> ()```！！！一行代码解决了排序函数！心动不如行动，赶快来试试吧！

~~咳咳~~，没错，```greater<int> ()```的确可以充当**从大到小**的比较函数，所以我们的排序算法就变成了一行：

```sort(a + 1, a + n + 1, greater<int> ())```

所以我们的整个代码就出来了：

```
#include <iostream>
#include <functional>
#include <algorithm>
using namespace std;

int k, n = 12, a[100001], ans;//月份总数为n（一共12个月），a数组为输入数组，ans为答案

int main() {
    cin >> k;//输入k
    for (int i = 1; i <= n; i++) cin >> a[i];//输入a
    sort(a + 1, a + n + 1, greater<int> ());//排序
    while(k > 0) {//如果k > 0
        ans++;//答案++
        k -= a[ans];//求出剩余厘米数数量
    }
    cout << ans;
    return 0;
}
```

---

## 作者：封禁用户 (赞：0)

一道贪心水题，用sort()和reverse()就可以水过了。~~（STL大法好！）~~
```cpp
#include<bits/stdc++.h>//万能头，不解释
using namespace std;
int wsq[13]={0};//向一位提高大佬致敬
int main()
{
    int k,ans=0;//ans定义在外面就不用=0了
    cin>>k;
    for(int i=1;i<=12;i++)
    cin>>wsq[i];
    sort(wsq+1,wsq+13);//sort排序贼快，贼好用
    reverse(wsq+1,wsq+13);//reverse就是将排好的翻过来
    int a=1;
	while(k>0&&a<=12)//判断，当一年到头时或已经不用浇了时结束
    {
    	ans++;
    	k-=wsq[a];
    	a++;
	}
	if(k>0)//判断输出
	cout<<"-1"<<endl;
	else
	cout<<ans<<endl;
    return 0;//完美运行
}
```

---

