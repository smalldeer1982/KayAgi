# Sale

## 题目描述

Once Bob got to a sale of old TV sets. There were $ n $ TV sets at that sale. TV set with index $ i $ costs $ a_{i} $ bellars. Some TV sets have a negative price — their owners are ready to pay Bob if he buys their useless apparatus. Bob can «buy» any TV sets he wants. Though he's very strong, Bob can carry at most $ m $ TV sets, and he has no desire to go to the sale for the second time. Please, help Bob find out the maximum sum of money that he can earn.

## 样例 #1

### 输入

```
5 3
-6 0 35 -2 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4 2
7 0 0 -7
```

### 输出

```
7
```

# 题解

## 作者：empty (赞：8)

## ~~买东西还能倒贴，良心~~           
所以说要买的是价钱为负数的电视           
于是我在开始就把读入的钱反一下           
正数的是负数，负数的是正数，            
那么这样的话只需要愉快的排序了
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<string>
#include<map>
#include<vector>
using namespace std;
int n,m,a[101],money=0;
int main()
{
 cin>>n>>m;
 for(int i=1;i<=n;i++) 
 {
  int x;
  cin>>x;
  a[i]=0-x; //转化成相反数
 }
 sort(a+1,a+n+1);
 for(int i=n;i>=n-m+1;i--)
 {
  if(a[i]>0) money+=a[i];
        else break;
 }
 cout<<money;
}
```

---

## 作者：xuezhe (赞：4)

Bob 要想赚到钱，就必须要让对方贴钱，也就是电视价格必须为负数。

于此同时，为了使赚到的钱最大，对方贴的钱要最多，电视的价格就要最小。

所以我们要在所买电视数量不超过 $m$ 且所买电视价格为负数的前提下，尽可能买价格低的电视，且尽可能多买电视。

从代码实现的角度来讲，我们只需要将电视价格从小到大排序，然后依次按照条件判断即可。

这里给出Python3代码：

```
n,m=[int(i) for i in input().split()]
a=[int(i) for i in input().split()]
a.sort()
i=0
s=0
while i<m and a[i]<0:
    s-=a[i]
    i+=1
print(s)
```

---

## 作者：Cinderella (赞：3)

本蒟蒻又来发题解啦！

话不多说，进入正题。

本题要我们求Bob最终能赚到多少钱。

接下来就是我滴思路：

1.输入n和m

2.输入数组a

3.排序数组a

4.判断，如果当前的这个数小于或等于0,(也就是负数)，则用能赚的钱数减去当前这个数

献上代码↓
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstring>

using namespace std;
long long n,m,q;
int a[110];
int main()
{
	scanf("%I64d%I64d",&n,&m);
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=m;i++) if(a[i]<=0)q=q-a[i];
	cout<<q;
return 0;
}
```
好啦，以上就是CF34B 【Sale】的题解，如有不足，请各位dalao在右边→评论区指出！

---

## 作者：☆芝麻大饼☆ (赞：2)

一道简单的题

就是坑多

呵呵

# 无坑不成题

当你看到这道题，不要心焦，其实就是sort

现在先读读题吧，你会发现更多的坑，~~我就跌了好几次~~

话不多说，来，上c++代码：
```
#include<iostream>
#include<algorithm>//标准头文件
using namespace std;
int n,m,a[10000],sum;
int main()
{
    cin>>n>>m;//正常输入 
    for(int i=0;i<n;i++)
    {
        cin>>a[i];//循环输入 
    }
    sort(a,a+n);//排序
    for(int i=0;i<m;i++)
    {
        if(a[i]>=0)
        {
            break;//到0就停
        }
        sum+=0-a[i];//坑！注意是赚的钱，要用零减

     } //题目说了：最多m台 
    cout<<sum;//输出 
    return 0; 
 } 
```
本蒟蒻第一次发题解，请多包涵。

望通过

---

## 作者：时律 (赞：1)

根据贪心思想自然是要买为负数价格的电视机。

把所有价格读入进来后排个序，如果最多买的电视机数量超过了价格为负数的电视机数量，就只买价格为负数的电视机就好了，否则会亏。
```
#include<bits/stdc++.h>
using namespace std;
int x[105];
int main()
{
	int a,b,ans=0;
	scanf("%d%d",&a,&b);
	for(int i=1;i<=a;i++)
		scanf("%d",&x[i]);
	sort(x+1,x+1+a);
	for(int i=1;i<=b;i++)
	{
		if(x[i]<0) ans+=0-x[i];//如果是负数就买
		else break;//否则不买，退出
	}
	printf("%d",ans);
}
```

~~买东西倒贴，良心~~

---

## 作者：fls233666 (赞：1)

**2020年2月14日更新：修复题解排版问题**

----------

读题，发现要求的是能赚到的钱的**最大值**，采用**贪心策略**。

因为题目要求**能赚到的钱**，所以**要尽可能的去买价格为负数的电视**。

但是题目又有限制买的个数（只能买 $n$ ），怎么办？

我们拿一个例子来看看：

假如有三台电视，价格分别为 $a_1,a_2,a_3$，且 $a_1<a_2<a_3<0$。

如果**只能买一台**，选择哪台？

肯定是选择价格为 $a_1$ 的电视，因为**它能赚的钱最多**。

如果**再让你选一台**，选择哪台？

选择价格为 $a_2$ 的电视，因为在剩下的两台电视中，**它能赚的钱相对较多**。

好，总结一下：

**我们在所有价格为负的电视中，优先选择价格更低的电视，使每一步决策后都能赚尽量多的钱。** _这就是此题的贪心策略。_ 

----------

### 程序实现流程（本人采用二叉堆实现）

1. 建小根堆；
2. 读入数据，筛出全部负数；
3. 循环将堆顶**累减**（ _使负数转成正数_ ），直到数量超过 $n$ 或堆空；
4. 输出答案。

 _二叉堆的堆顶就是当前的最小价格。_ 

代码如下：

```cpp
#include<iostream>
#include<queue>
using namespace std;
priority_queue< int, vector<int>, greater<int> >q;
//建小根堆
int main()
{
    int n,m,ans=0,a;
    cin>>m>>n;  //读入m与n
    for(int i=0;i<m;i++){
        cin>>a;  //读入每个价格a
        if(a<0)
            q.push(a);  //筛出负数入堆
    }
    //数据读入&预处理
                
    while(!q.empty()){  //在堆不空情况下一直循环
        if(n==0) break;  //数量超过n，跳出循环
        ans-=q.top();    //统计堆顶（注意这里是减，因为要转成正的）
        n--;  //计数
        q.pop();  //删掉堆顶
    }
    cout<<ans;
    //计算&输出
              
    return 0;
}
```


---

## 作者：骗分过样例 (赞：0)

# ~~背包问题~~
# 贪心！！！！
思路：

1：排序。

2：在前m个中买价值为负数的。
# 注意：千万不买价值>=0的！！
上代码：
```
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n,m;
	int a[101],total=0;
	cin>>n>>m;
	for(int i=0;i<n;i++)	cin>>a[i];
	sort(a,a+n);					//排序 
	for(int i=0;i<m;i++)
	{
		if(a[i]>=0)	break;			//赚不了就不买了。
		else		total-=a[i];	//注意不是+=，负数减等于整数加。 
	}
	cout<<total; 
	return 0;						//完美结束。 
}
```


---

## 作者：Playnext (赞：0)

Bob选电视一定选是负权值的，这样才能赚到最多钱。


采用贪心策略，排一次序即可。


#### 注意：是最多买$m$ 台,当选到正权值要及时跳出。~~(被这个坑了好几次2333)~~


```cpp
#include <bits/stdc++.h>
using namespace std;    //BY Playnext
#define REG register
#define FOR(X,Y,Z) for (REG int X=Y; X<Z; X++)
const int MAXN=1e2+1;

int F[MAXN], Ans;

int main () {
//    freopen ("Input.txt", "r", stdin);
//    freopen ("Output.txt", "w",stdout);
    REG int n, m;
    scanf ("%d %d", &n, &m);
    FOR (i,0,n)        scanf ("%d", &F[i]);
    sort (F, F+n);        //排序
    FOR (i,0,m)    {
        if (F[i] >= 0)        //及时跳出
            break;        
        Ans += F[i];
    }
    printf ("%d\n", -Ans);        //由于题目是求盈利，最后取负
    return 0;
}
```

---

