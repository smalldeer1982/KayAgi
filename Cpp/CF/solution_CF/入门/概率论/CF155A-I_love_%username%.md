# I_love_%username%

## 题目描述

Vasya很喜欢一个coder，他喜欢看那个coder的节目，那个coder每次编程可以得到一个非负分数（不超过10000），而有两种情况能使Vasya惊讶：
·coder得到的分数完全大于过去的分数；
·coder得到的分数完全小于过去的分数。
注意：第一次得到的分数不会使人惊讶。
给定coder编程次数n，给定每次编程得到的分数，请你求出Vasya的惊讶次数。

~~看着题面上好像没有介绍输入输出和数据范围就来多嘴一句~~

## 样例 #1

### 输入

```
5
100 50 200 150 200
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10
4664 6496 5814 7010 5762 5736 6944 4850 3698 7242
```

### 输出

```
4
```

# 题解

## 作者：绝顶我为峰 (赞：10)

看到大佬们都是用的同一种思路，本~~(～￣(OO)￣)ブ~~蒟蒻颤抖着来献上自己的解法。![](https://img.shields.io/badge/蒟蒻是我-珂怕-blue.svg)

-------------我--------------是--------------分--------------割--------------线-------------

这题的题意也可以这样解释：

你是一个蒟蒻，正在参加AK模拟赛，你第一次提交，得到了一个分数20分，你心平气和的接受了这个成绩，内心毫无波澜︿(￣︶￣)︿。然后你改了代码，又提交了一次，历史最低~~爆0了~~让你十分惊讶(ΩДΩ)，心想：~~我怎么可以这么菜呢~~，于是发愤图强，得了历史最高60分，这也会让你惊讶(～￣▽￣)～，心想：~~我是大佬~~，请统计，认为自己很菜或是大佬的时候出现了几次？

能够让你失去信心或是信心百倍的分数有什么特性呢？如果将这次成绩同之前成绩放在一个数组里排序后（不是第一次）一定是以下两种情况之一：

1.排在整个数组第一个，且与第二个数字不同；

2.排在整个数组最后一个，且与倒数第二个数字不同。

所以只要满足两个条件之一，ans（计数器）+1。

拿样例1演示一下（橙色满足条件，黑色不满足，大家自行了解）：

![](https://cdn.luogu.com.cn/upload/pic/21217.png)

综上所述，代码很简单了，但是在这里要对大家说（滑稽）：

# sort大法好！！！

上代码喽(｡◕ˇ∀ˇ◕)（注释部分为调试代码，请忽视）

```cpp
#include<iostream>
#include<algorithm>//一个神奇的库
using namespace std;
int n,k,a[1001],ans;
int main()
{
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>k;//输入副本，以备比较
        a[i]=k;//保存
        sort(a,a+i+1);//排序
        //for(int j=0;j<=i;j++)
			//cout<<a[j]<<" "; 
        if(((a[0]==k&&a[1]!=k)||(a[i]==k&&a[i-1]!=k))&&i!=0)//判断条件
            ans++;//符合就+1
        //cout<<endl;
    }
    cout<<ans<<endl;//输出
    return 0;
}
```

~~**蒟蒻已经逃跑了，没法和大家说再见**~~

---

## 作者：陈LC (赞：1)

~~嗯，一道超级H2O的题目~~

这道题只需要模拟就可以啦！

上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e3+5;
int p[maxn];//定义一个数组用于存分数
bool choose(int x){
    int i,cnt=0;
    for(i=0;i<x;i++){//先做全部小于的判断
        if(p[i]<p[x]){
            cnt++;//小于则cnt++
        }
    }
    if(cnt==x){//判断是否全部小于
        return true;//符合return true
    }else{
        cnt=0;
        for(i=0;i<x;i++){//再做全部大于的判断
            if(p[i]>p[x]){
                cnt++;//大于则cnt++
            }
        }
        if(cnt==x){//判断是否全部大于
            return true;//符合return true
        }
    }
    return false;//如果两个都不符合return false
}
int main(){
    int n,i,ans=0;//n,i不解释;ans为惊讶的次数
    scanf("%d",&n);//输入
    for(i=0;i<n;i++){
        scanf("%d",&p[i]);//输入分数
    }
    for(i=1;i<n;i++){
        if(choose(i)){//调用函数并判断
            ans++;
        }
    }
    printf("%d",ans);//输出结果
    return 0;//好习惯～～～
}
```

---

## 作者：cbyybccbyybc (赞：1)

AC记录https://www.luogu.org/recordnew/show/16387168

先模拟一下：
1：100 ans=0;             
2: 100 50 **50<100** ans=1;                 
3: 100 50 200 **50<100<200** ans=2;                   
4: 100 50 200 150 200 **50<100<150<200** ans=2;
5: 100 50 200 150 200 **50<100<150<200=200** ans==2;
输出2


主要部分：
```cpp
for(int i=1;i<n;i++)//从1~n枚举
    {
    	for(int j=0;j<i;j++)//枚举前面的
    	{
    		if(a[i]>a[j]) flag++;//如果比前面的大，flag++
    		else if(a[i]<a[j]) flag--;//如果前面小，flag--
    	}
    	if(flag==i||flag==0-i)//判断是否前面全部大于或小于a[i]
    		ans++;//成立 ans++
    	flag=0;//flag归零
    }
```


完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;//输入
    int a[n+100];
    for(int i=0;i<n;i++)
    cin>>a[i];//输入
    int ans=0,flag=0;
    for(int i=1;i<n;i++)
    {
    	for(int j=0;j<i;j++)
    	{
    		if(a[i]>a[j]) flag++;
    		else if(a[i]<a[j]) flag--;
    	}
    	if(flag==i||flag==0-i)
    		ans++;
    	flag=0;
    }
    cout<<ans;//输出
    return 0;
}
```

这题很水！！！
希望大家能看懂！！！
Thanks♪(･ω･)ﾉ

---

## 作者：土川崇贺 (赞：0)

        本题比较简单，先将最大值、最小值赋为第一个输入的数，之后每输入一个就判断是否大于最大值或者小于最小值，如果是的话最大值最小值就赋为这个新的值，同时计数器+1；
        代码奉上：
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
int main()
{
    long long n,c=0,a;//定义总个数、计数器、暂存变量
    cin>>n;//输入总个数
    cin>>a;//输入暂存变量
    long long max=a,min=a;//定义最大值、最小值，赋初值为a
    for(int i=1;i<n;i++)
    {
    	cin>>a;//输入a
    	if(a>max)//如果a大于最大值
        {
    	    c++;//计数器+1
    	    max=a;//最大值赋为a
        }
        if(a<min)//如果a小于最小值
        {
             c++;//计数器+1
	     min=a;//最小值赋为a
        }
    }
    cout<<c;//输出计数器
    return 0;//程序结束
}

```

---

## 作者：PeppaPig (赞：0)

本人萌新一枚，以下代码供各位大佬、神犇参考，不对之处望指正
```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
	int n,maxn=0,minn=10010,k=-2;// ·coder为了处理第一次的分数 
    int a[1010]; 
    cin>>n; 
    for(int i=0;i<n;i++){ 
    	cin>>a[i]; 
    	if(a[i]>maxn){ 
    		maxn=a[i]; 
            k++;// ·coder得到的分数完全大于过去的分数 
        } 
        if(a[i]<minn){ 
        	minn=a[i]; 
            k++;
        }// ·coder得到的分数完全小于过去的分数  
	}
    if(k<0) k=0;//特殊处理
    cout<<k;//输出
    return 0;
}
```

---

## 作者：Neoomgg (赞：0)

这倒水题怎么那么多坑！！！

第一个是只有分数的情况，本JR代码直接越界RE

第二个是前两个分数相同，本JR多记一次WA

另附：此方法纯粹模拟，大佬见笑了！

---

（上面依旧是一条蟒蛇）

```python
n = int(input())
p = list(map(int, input().split()))
'''!!!'''
if n == 1:
    print(0)
'''!!!'''
else:
    d = max(p[0], p[1])
    x = min(p[0], p[1])
    '''!!!'''
    if d == x:
        s = 0
    else:
        s = 1
    '''!!!'''
    for i in range(2, n):
        if p[i] > d:
            d = p[i]
            s += 1
        elif p[i] < x:
            x = p[i]
            s += 1
    print(s)

```

---

## 作者：Obito (赞：0)

# 又是道大水题，本~~神犇~~蒟蒻表示真的很简单，具体见代码。


```
#include<bits/stdc++.h>
//毅然决定万能头
using namespace std;
int i,j,k,n,m,a[10001],mx,mi,ans;//a数组为存储每一个数，
//mi，mx存储每次最大最小值，ans计惊讶总数。
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);noip文件
    cin>>n;//输入编码数量
    for(i=1;i<=n;i++){
        scanf("%d",&a[i]);//输入
        if(i==1){//第一次，不算给记下来
            mi=a[1];
            mx=a[1];
            continue;
        }
        else {//如果不是第一个的话就与之前的比较，如果大就
        //记下大的，惊讶数++，同理：小的一样
            if(a[i]<mi)mi=a[i],ans++;
            if(a[i]>mx)mx=a[i],ans++;
        }
    }
    cout<<ans;//输出惊讶总数
    return 0;//完美结束
}
```
## 打字不累，希望采纳。祝洛谷越来越好。祝各位大神（洛谷里除了本蒟蒻以外的都是大神）事事顺心。

---

## 作者：温情 (赞：0)

emmm...这道题我觉得可以这么理解.

你参加了N次考试,如果某次考试考的比之前都高,或者比之前都低,那么你就会开始心情复杂(0.0).

所以记住你目前考过的最高分和最低分就好了,如果心情复杂了就计数并更新最高分或者最低分.

记住第一次考试的时候不管考多少分都不心情复杂,而且此时最高分和最低分都等于第一次考试的分数.

```
#include<iostream>
using namespace std;
int main()
{
	int n,amazing=0,max,min,temp;
	cin>>n;
	for(int i=0;i<n;i++)
	{
		cin>>temp;
		if(!i)                                    //第一次 
		{
			max=temp;
			min=temp;
		}
		else
		{
			if(temp>max)                          //考的比之前都高 
			{
				amazing++;                        //计数,心情复杂 
				max=temp;                         //更新最大值 
			}
			else if(temp<min)
			{
				amazing++;
				min=temp;
			}
		}
	}
	cout<<amazing;
	return 0;
}
```

---

## 作者：OdtreePrince (赞：0)

# -纯模拟-

其实这道题不需要打得多复杂，第1个特判可以用以下操作省略。

cin>>n>>k;

for(int i=1;i<n;i++){

        cin>>k;
        
        if(k>maxx) maxx=k,ans++;
        
        if(k<minn) minn=k,ans++;
    
    }

为什么呢？答案显而易见。只要不在循环中输入即可。

每次更新最大值和最小值，ans就在眼前！！

是不是很简单呢？

~~~
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,k,maxx,minn,ans=0;
    cin>>n>>k;
    maxx=k;
    minn=k;
    for(int i=1;i<n;i++){
        cin>>k;
        if(k>maxx) maxx=k,ans++;
        if(k<minn) minn=k,ans++;
    }
    cout<<ans<<endl;
    return 0;
}~~~

---

