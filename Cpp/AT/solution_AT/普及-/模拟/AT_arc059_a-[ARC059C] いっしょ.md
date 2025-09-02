# [ARC059C] いっしょ

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc059/tasks/arc059_a

$ N $ 個の整数 $ a_1,a_2,..,a_N $ が与えられます。えび君はこれらを書き換えて全て同じ**整数**にしようとしています。各$ a_i\ (1≦i≦N) $は高々一回しか書き換えられません(書き換えなくても良い)。整数$ x $を整数$ y $に書き換えるとき、コストが$ (x-y)^2 $かかります。仮に$ a_i=a_j\ (i≠j) $だとしても、ひとつ分のコストで同時に書き換えることは出来ません(入出力例$ 2 $ を参照)。えび君が目的を達成するのに必要なコストの総和の最小値を求めてください。

## 说明/提示

### 制約

- $ 1≦N≦100 $
- $ -100≦a_i≦100 $

### Sample Explanation 1

全てを$ 6 $に書き換えると、コストの総和は$ (4-6)^2+(8-6)^2=8 $となり、これが最小です。

### Sample Explanation 2

全てを$ 2 $に書き換えると$ (1-2)^2+(1-2)^2+(3-2)^2=3 $となります。各$ a_i $ごとに書き換えるので、二つの$ 1 $を一度にコスト$ (1-2)^2 $で書き換えられるわけではないことに注意してください。

### Sample Explanation 3

$ 4 $は書き換えずに、$ 2 $と$ 5 $を共に$ 4 $に書き換えることで$ (2-4)^2+(5-4)^2=5 $が達成できて、これが最小です。

### Sample Explanation 4

何も書き換えなくともえび君は目的を達成しています。よってこの場合コストは$ 0 $です。

## 样例 #1

### 输入

```
2
4 8```

### 输出

```
8```

## 样例 #2

### 输入

```
3
1 1 3```

### 输出

```
3```

## 样例 #3

### 输入

```
3
4 2 5```

### 输出

```
5```

## 样例 #4

### 输入

```
4
-100 -100 -100 -100```

### 输出

```
0```

# 题解

## 作者：encore (赞：6)

这个题目最最最坑的地方在于题目描述。第四组样例里没有输出。然后我就莫名其妙wa了三四个点。**其实就算答案是0也要输出的。**这还是我改的时候失误发现的。~~所以我交了6次才过~~

好了不多说，上代码：

```cpp
#include<iostream>
#include<cmath>
#define f(x) (x)*(x)

using namespace std;

int n;
int a[1001];
int cnt;
int ans;
int tt=0x7fffffff;

int main()
{
	cin>>n;
	int mi=tt,ma=-tt;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		cnt+=a[i];
		if(a[i]<mi) mi=a[i];
		if(a[i]>ma) ma=a[i];
	}
	int t=cnt/n;
	for(int k=mi;k<=ma;k++)
	{
		ans=0;
		for(int i=1;i<=n;i++)
		{
			ans+=f(a[i]-k);
		}
		if(ans<tt) tt=ans;
	}
	cout<<tt;
	return 0;
}
```

这个其实很好想：要改就在a数组的最大值和最小值之间选一个数改。数据那么水，暴力枚举不就好了。

当然还有一个技巧型的代码：

```cpp
#include<iostream>
#include<cmath>
#define f(x) (x)*(x)

using namespace std;

int n;
int a[1001];
int cnt;
int ans;
int ans2;
int ans3;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        cnt+=a[i];
    }
    int t=cnt/n;
    for(int i=1;i<=n;i++)
    {
        ans+=f(a[i]-t);
        ans2+=f(a[i]-t-1);
        ans3+=f(a[i]-t+1);
    }
    int tt=ans<ans2? ans:ans2;
    tt=tt>ans3? ans3:tt;
    cout<<tt;
    return 0;
}
```

原理的话很玄学。你可以试试看画一个函数~~或者凭直觉~~发现只可能是平均值和离平均值最近的两个点这三个点。

~~其实这本来就是一道考循环嵌套的水题，钻深了不要得不偿失~~

以上代码均AC。

---

## 作者：PrincessQi (赞：2)

这里是一个对于此题结论的稍微严谨一些的证明。

设最后所有数均为 $a$。

则所求的值为

$$\sum\limits_{i=1}^n(x_i-a)^2$$

$$=\sum\limits_{i=1}^nx_i^2+na^2-2a\sum\limits_{i=1}^nx_i$$

令 $\sum\limits_{i=1}^nx_i=S$，则

$$\sum\limits_{i=1}^nx_i^2+na^2-2a\sum\limits_{i=1}^nx_i$$

$$=\sum\limits_{i=1}^nx_i^2+na^2-2aS$$

$$=\sum\limits_{i=1}^nx_i^2+n(a^2-2a\frac{S}{n}+\frac{S^2}{n^2})-\frac{S^2}{n^2}$$

$$=\sum\limits_{i=1}^nx_i^2+n(a-\frac{S}{n})^2-\frac{S^2}{n^2}$$

所以，当 $a$ 最接近 $\frac{S}{n}$ 时，原式最小。

以下是代码：

```python

n=int(input())
s=input()
s.split(" ")
S=0
SS=0
for i in range(0,n-1):
    S=S+int(s[i])
    SS=SS+int(s[i])*int(s[i])
print(int(SS+n*(S/n-round(S/n))*(S/n-round(S/n))-S*S/n/n))

```

---

## 作者：Cocoly1990 (赞：0)

## 思路

~~题目没看懂真就没救了~~

**小坑点就在于哪怕是**$0$**也要输出**

~~所以做题别看样例~~

没学过小学数学的都知道，作为 **「基准」** 的那个数绝对在$MAX$和$MIN$之间 ， 包括两端

就两重循环按题意模拟就好了。

其实这题也有复杂度更低的方法，但是我不会证明，其难度也远远超过了红题，详细的证明可以参照题解区的某位大佬。

## Code

$xxs$最喜欢的代码时间
```cpp
#include<bits/stdc++.h>
using namespace std ;
long long n , a[100007] , _max = -0x7ffffff , _min = 0x7ffffff, s , sum , ans = 0x7ffffff;
int main()
{
    cin >> n ;
    for(int i = 1 ; i <= n ; i ++)
    {
        cin >> a[i] ;
        _max = max(_max , a[i]) ;
        _min = min(_min , a[i]) ;
    }
    for(int j = _min ; j <= _max ; j ++)
        {
            sum = 0 ;
            for(int i = 1 ; i <= n ; i ++)
            {
            sum += (a[i] - j) * (a[i] - j) ;
            }
            if(sum < ans) ans = sum ;
        }


    cout << ans ;
    //system("pause") ;
    return 0 ;
    
}
```

---

## 作者：phil071128 (赞：0)

## 题解 AT2019 【[ARC059A] いっしょ / Be Together】

思路：暴力枚举

这道题简单分析一下样例，就能得出这题的大意

### 样例1：
$4  $ $ 8$

我们只需要选择 $6 $，就可以让结果最小

$(6-4)^2+(8-6)^2=8$

### 样例2：
$1  $ $ 1$ $ 3$

我们只需要选择 $2 $，就可以让结果最小

$(2-1)^2+(2-1)^2+(3-2)^2=3$

### 样例3：
$4  $ $ 2$ $ 5$

我们只需要选择 $4 $，就可以让结果最小

$(4-4)^2+(4-2)^2+(5-4)^2=5$


这样大体就出来了，暴力代码：

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int a[100000];
int main(){
	int n;
	cin>>n;
	int maxx=-0x7ffffff,minn=0x7ffffff;//初始化一个非常小的数和一个非常大的数
	for(int i=1;i<=n;i++){
		cin>>a[i];
		maxx=max(a[i],maxx);//求最大值
		minn=min(a[i],minn);//求最小值
	}
	long long sum=0;  //统计花费
	long long ans=0x7ffffff;//也要初始化为一个非常大的数
	for(int k=minn;k<=maxx;k++){  //k为选择的这个数，并且选择的这个数一定是在这个数列的范围内的，可以稍微缩小枚举范围
		sum=0;  //别忘了清0
		for(int i=1;i<=n;i++){
			sum+=(a[i]-k)*(a[i]-k);  //题目已经给出
		}
		ans=min(ans,sum);  //如果当前得出的最终结果要之前的都要小，更新
	}
	cout<<ans;
	return 0;
}
```
其实稍微看一看也能得出，选择的数是这个数列中最大值与最小值的中间值

核心代码：
```
int mid=(maxx+minn+1)/2; 
long long sum=0;
for(int i=1;i<=n;i++){
	sum+=(mid-a[i])*(mid-a[i]);
}
```



---

## 作者：勘探员·引魂人 (赞：0)

**前言：震惊！洛谷终于有道AT入门不一般的题了！**

**思路：首先算出数组的总和，接下来判断总和%n是否==0。如果总和%n==0，那么就算出平均数，然后从1~n循环，答案+=(a[i]-平均数)平方；如果总和%n!=0，还是先算出平均数,然后从1~n循环，答案(ans)+=(a[i]-平均数)平方,接着平均数+=1，再从1~n循环，另一个答案(ans1)+=(a[i]-平均数)平方，输出min(ans,ans1)**

```
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>//文件头还要我讲吗？
using namespace std;
int a[110];//定义个little数组
int main()
{
    int n;//定义n
    scanf("%d",&n);//输入n
    int sum=0;//sum为总和
    for(int i=1;i<=n;i++)//从0到i循环
        scanf("%d",&a[i]),sum+=a[i];//输入数组并计算总和
    if(sum%n==0)//判断sum%n是否==0.....
    {
    	//符合！
        int k=sum/n;//算出平均数
        int ans=0;//定义答案变量
        for(int i=1;i<=n;i++)//从1到n循环
            ans+=(a[i]-k)*(a[i]-k);//a[i]-k代表次数与平均数之差，由于题目所说“将一个整数xx转换为一个整数yy会花费他(x−y)的平方美元。”，所以我们的答案要+=(a[i]-k)*(a[i]-k)
        printf("%d\n",ans);//执行完后输出ans
    }
    else//否则...
    {
    	//不符合！
        int k=sum/n;//算出平均数
        int ans=0;//定义答案变量
        for(int i=1;i<=n;i++)//从1到n循环
            ans+=(a[i]-k)*(a[i]-k);//a[i]-k代表次数与平均数之差，由于题目所说“将一个整数xx转换为一个整数yy会花费他(x−y)的平方美元。”，所以我们的答案要+=(a[i]-k)*(a[i]-k)
        int ans1=0;//定义答案变量*2(因为如果sum%n!=0的话需要有2个平均数)
        k++;//平均数++
        for(int i=1;i<=n;i++)
            ans1+=(a[i]-k)*(a[i]-k);//a[i]-k代表次数与现在平均数之差，由于题目所说“将一个整数x转换为一个整数y会花费他(x−y)的平方美元。”，所以我们的答案要+=(a[i]-k)*(a[i]-k)
        printf("%d\n",min(ans,ans1));//算出2个答案的最小值
    }
    //作者懒得打return 0  (￣︶￣)
}//结束“题解 AT2019 【いっしょ / Be Together】”
```

---

