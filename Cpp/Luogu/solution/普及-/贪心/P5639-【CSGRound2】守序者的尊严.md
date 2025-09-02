# 【CSGRound2】守序者的尊严

## 题目背景

由于 Y 校最近进行了对学校食堂的全面改革与对小卖部的全面整治(乱搞)，导致学校小卖部卖的零食被禁售了；学校食堂的炸鸡窗口也消失了；

并且学校的学生处 Q 主任严禁学生点外卖，日夜监察。

都说民以食为天，由于整天挨饿，全校同学处于水深火热之中。

## 题目描述

zhouwc 的朋友（朋友就是自己系列）小 Z 由于饥饿难忍，不得不铤而走险点外卖。

但是学校的 Q 主任为了能够抓住点外卖的学生布置了天罗地网——监控。

但是由于学校给 Q 主任的经费有限，所以这些监控不能持续工作，工作一秒之后便要暂停休息一秒，**即开启一秒后关闭一秒再开启一秒...以此类推**。

还是由于 Q 主任的经费有限，这些监控被排成了一条直线，这条直线便在学生通往学生外卖驻点——二号门（没有门卫）的必经之路上。

因为小 Z 修习了疾跑技能，所以小 Z 通过任意个数关闭的监控的时间均为 
 $1$（即一次行动可以经过若干个未开的监控）。

由于小 Z 想吃外卖又不想受到正在监控室看着监控的 Q 主任的处分，请你告诉他至少要多少时间才能安全到达外卖驻点。

## 说明/提示

#### 数据范围：

对于 $10\%$ 的数据，$1 \leq n \leq 10$

对于 $30\%$ 的数据，$1 \leq n \leq 100$

对于 $50\%$ 的数据，$1 \leq n \leq 10^3$

对于 $70\%$ 的数据，$1 \leq n \leq 10^5$

对于$100\%$的数据，$1 \leq n \leq 10^6$

监控的开关情况均用 $0$ 和 $1$ 来表示。

#### 样例解释一：

小 Z 在第一秒时冲到第二个监控处，用时 $1$ 秒，总用时 $1$ 秒。

第二秒时，监控的开关状况变为了 $1 1 0 0 1 0$。

这时，小 Z 迅速从二号监控处冲到了四号监控处，用时 $1$ 秒，总用时 $2$ 秒。

第三秒时，监控的开关状况变为了 $0 0 1 1 0 1$。

这时，小 Z 迅速从四号监控处冲到了五号监控处，用时 $1$ 秒，总用时 $3$ 秒。

第三秒时，监控的开关状况变为了 $1 1 0 0 1 0$。

这时，小 Z 迅速从五号监控处冲出了监控区域，用时 $1$ 秒，总用时 $4$ 秒。

#### 样例解释二

小Z在第一秒直接冲出了监控区域。

## 样例 #1

### 输入

```
6
0 0 1 1 0 1```

### 输出

```
4```

## 样例 #2

### 输入

```
6
0 0 0 0 0 0```

### 输出

```
1```

# 题解

## 作者：zhouwc (赞：24)

## 官方题解

### I 50pt
每一秒变化一次，就直接一次一次地改动监控的开关情况再走路

这样的时间复杂度 $O(n^2)$

你可以顺利的拿到50分

### II 100pt
其实这个监控的变化只是为了你能够顺利到达终点而已。

就是一个模拟题，直接判断一下初始的监控开关状况即可。

连在一起的0和连在一起的1都可以1秒经过（因为1可以变成0，0可以还是0）。只要把连续的0或连续的1的段数加起来就完事了。

时间复杂度 $O(n)$

### std
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005],n;
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
        scanf("%d",&a[i]);
    int ans=1;
    for (int i=2;i<=n;i++)
        if (a[i]!=a[i-1]) ans++;
    printf("%d\n",ans);
}
```


---

## 作者：十四日的夏 (赞：10)

~~此题非常之水~~  
其实也用到一点点贪心  
当能向前走时一定会走直到碰到监控，所以只要判断01转换次数再+1就好了QAQ  
附上代码

```cpp
#include<iostream>
#include<cstdio>
#include<ctime>
#include<cmath>
#include<algorithm>
#define ll long long int
#define For(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
int sum,pre,n;
int x[1000001];
int main()
{
	cin>>n;
	pre=0;
	For(i,1,n)
	{
		scanf("%d",&x[i]);
	}
	pre=0;
	For(i,0,n-1)
	{
		if(x[i+1]!=pre)
		{
			sum++;
			pre=x[i+1];
		}
	}
	cout<<sum+1;
	return 0;
}

```



---

## 作者：冬天的雨 (赞：6)

# 又是蒟蒻的题解                  
[题目链接](https://www.luogu.org/problem/P5639)        
首先我们来审审题：一排摄像头排成一列，每隔一秒开关状态变换一次，只能在关闭状态下通过摄像头，求最短通过时间。                
这道题明显是一道水的纯模拟，但是如果直接按照题目所说的每次更新一次状态肯定会$ TLE$，所以我们可以将模拟进行优化。      	          
按照样例$1$可以画出如下表格：      

 
| 第一秒 | 0 | 0 | 1 | 1 | 0 | 1 |        
| -----------: | -----------: | -----------: | -----------: | -----------: | -----------: | -----------: |       
| 第二秒 | 1 |1  |0  | 0 | 1 |0  |        
| 第三秒 | 0 | 0 | 1 | 1 | 0 | 1 |                      
| 第四秒 | 1 | 1 | 0 | 0 | 1 |0  |              
这样很容易可以看出，题目中所说的什么开关根本就是瞎扯，没有什么用。。。这样题目就简化为了给你一个数列，求里面不相同的元素个数。注意将ans初始化为1                     
$AC$代码附上：                    
```cpp
#include<algorithm>
#include<cstdlib>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
using namespace std;//蒟蒻我不喜欢写万能头，CSP禁止，所以多写几个 
int n,a[1000001],ans=1;//由于题目里给的是一百万所以要定义1000001的数组
//当然如果在主程序里定义的话有RE的风险 
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]); 
	}
	//-------------读入------------------------------------------------ 
	for(int i=1;i<=n;i++){
		if(a[i]!=a[i-1]){//如果和前一个的状态不一样 
			ans++;//答案加一 
		}
	}
	//-----------以上为操作部分---------------------------------------- 
	printf("%d",ans);//输出 
	return 0;//一定一定要注意！！！不加的话珂能UKE！！！ 
} 
```     
蒟蒻不会用$Unique$。。。写题解不易，求赞


---

## 作者：Phoenix_lily (赞：4)

首先我们来看题

小Z的疾跑技能很快，一次通过任意个数的监控需要的时间都为1

~~这怕不是瞬移~~

既然如此，那我们每次都是尽可能往前冲就好了，显然，我们每次都只能冲到下一个开着的监控前面，等待一秒后监控开关状态转变，我们再往前冲

也就是说，我们每次~~瞬移~~走过一段路后，前面所有连续的开着的监控将会是我们下一秒可以走过的，（因为它们下一秒会变成关的）

所以很容易想到，每一段连续的0或1都需要一秒来走

题目就转化成了求连续的0或1的串数

~~众所周知~~只需要求有多少个数与上一个数不一样即可

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
bool kkk,last=1;     //kkk用来表示当前输入的数，last自然是上一个数            
                   //last定义为1是为了防止漏数第一串0
                   //第一串一定是0，否则将无法走出
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>kkk;
		if(kkk!=last)
		ans++;     //如果与上一个不同，答案就+1
		last=kkk;	 
	}
	cout<<ans;
	return 0;
 } 
```

水平有限，如有错误，敬请指正





---

## 作者：沉冥Charming (赞：3)

- 发现目前有的题解的解法跟我的不太一样呢

- 其实这题可以纯模拟无脑暴力的,不需要思考太多想到连续的0或连续的1

- ### 监控只有两个状态，所以可以用两个数组存储状态，每过一秒就切换到另一个状态，不需要每次都去修改状态，这样避免了 n ^ 2 算法

- 然后从起点循环直到达到终点，模拟一下就可以了

- 代码如下：

```cpp
#include <iostream>
using namespace std;
int n,a[1000005][3],t,step=1;
int main()
{
    cin>>n;
    for (int i=1; i<=n; i++)
    {
        cin>>a[i][0];
        if (a[i][0])
            a[i][2]=0;
        else
            a[i][2]=1;
    }
    for (int k=-1; step<=n; k=-k)//k表示监控状态
    {
        t++;
        for (int j=step; j<=n; j++)
        {
            if (a[j][k+1])
                break;
            step++;
        }
    }
    cout<<t;
    return 0;
}
```



---

## 作者：Edmundino (赞：3)

这算是比赛中的签到题了

这道题其实很好想，首先我们先看一下50%的数据

其实就是n^2算法，

首先需要一个队头指针，当队头指向的值为0时，

就把队头传出

然后在把1换0,0换1；

50%代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

const int N=1000050;

int n,a[N],s,front;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	while(front<n)
	{
		while(a[front+1]==0)
		{
			front++;
		}
		s++;
		for(int i=1;i<=n;i++)
		{
			if(a[i]==0)
			  a[i]=1;
			else
			  a[i]=0;
		}
	}
	cout<<s;
	return 0;
}
```

接着我们来想正解

其实就是奇偶性

但时间为偶数时，判断队头是否为0

但时间为奇数时，判断队头是否为1

正解AC代码
```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

const int N=1000050;

int n,a[N],s,front;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	while(front<n)
	{
		if(s%2==0)
		while(a[front+1]==0)
		{
			front++;
		}
		if(s%2==1)
		while(a[front+1]==1)
		{
			front++;
		}
		s++;
	}
	cout<<s;
	return 0;
}
```


---

## 作者：flash666 (赞：3)

对于开关状态相同的一段，他都可以在一秒之内走完

所以只要统计有几个开关状态不同的段即可

特别地，有以下两点要注意

1.如果第一个开关的开始状态为关的话，TA必须在原地等一秒，所以若a[1]=1,t++;

2.我算的是开关状态变化了几次，所以要+1才是实际次数

上代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool a[1000001];//保存开关状态
int t=0,n;
int main()
{
	cin>>n;
	cin>>a[1];
	if(a[1]==1)//第一个为关，必须等一秒
	t++;
	for(int i=2;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]!=a[i-1])//如果状态与上一个不同，t++
		t++;
	}
	cout<<t+1;//记得+1
        return 0;
}
```


---

## 作者：bus_station (赞：3)

## 50pts做法
我们看一下这些监控的规律:每过一秒，0 -> 1, 1 -> 0，~~非常显然地~~可以看出就是对每一位进行了取反，所以可以用c++STL的bitset来模拟这些监控。

代码：
```cpp
# include <bits/stdc++.h>
using namespace std;

bitset< 1000005 >jiankong;//定义一个长度为1000005的bitset

int main()
{
    int n, ans = 0;
    int cur;
    
    scanf("%d", &n);//scanf比cin更快
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &cur);
        jiankong[i] = bool(cur);//用强制转换是因为bool类型好像没有占位符
    }
    //输入每一位
    for (int i = 0; i < n;)//i表示小Z到了第几个监控
    {
        ans++;//躲过监控，时间++
        while (jiankong[i] == 0){
        	i++;//能走就走
        	if (i > n)break;//成功躲过所有监控
        }
        jiankong.flip();//flip()是对每一位取反
    }
    cout << ans << endl;
    return 0;
}
```

时间复杂度$O(N^2)$,无法通过本题 ~~毒瘤~~

## 70pts做法
~~大家都知道STL搭配O2食用更佳~~开O2卡常，实测可得70pts

代码：无

## 100pts做法
既然小Z可以通过任意一串0，那么任意一串1呢？显然任意一串1在下一秒会变成一串0，所以我们循环一遍，看到和前面不同的记录即可。

代码：

```cpp
# include <bits/stdc++.h>
using namespace std;

bool jiankong[1000005];

int main()
{
    int n, ans = 1;//第一个肯定要花费一秒
    int cur;
    
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &cur);
        jiankong[i] = bool(cur);
    }
    for (int i = 2; i <= n; i++)
    {
        if (jiankong[i] != jiankong[i - 1])ans++;//和前面一个不同则++
    }
    cout << ans << endl;
    return 0;
}
```

时间复杂度$O(N)$,可以通过本题

---

## 作者：xh39 (赞：3)

做法:模拟

就模拟小z的走路方式。能走就尽量走,走了反正没有坏处。如果不走,等到监控开了就走不了了。

我们可以一次性通过同样的一段序列,所以只要数有多少个连通块就可以了。
```cpp
#include<iostream>
using namespace std;
int open[1000005];
int main(){
	int n,i,sum=0;
	bool ykb=0;
	cin>>n;
	for(i=0;i<n;++i){
		scanf("%d",open+i);
	}
    //ykb=0表示第偶数次,ykb=1表示第奇数次。
	for(i=0;i<n;++i){
		if(ykb!=open[i]){ //不一样,就表示换了一个连通块。
			ykb=!ykb;
			sum++;
		}
	}
	cout<<sum+1; //别忘了+1,连通块一开始就有1个。
	return 0;
}
```

---

## 作者：piggymichael (赞：2)

很简单，如果遇到0就往前走，遇到1就停下。

那么就是求有多少组一样的，1的下一个是0或0的下一个是1就再需要一秒，统计一下就行了。

上代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
int ans=1,n;//注意ans一开始是1
bool a[3];
int main()
{
	cin>>n;
	for(int i=1;i<=n;++i)
	{
		cin>>a[i%2];
		if(a[i%2]!=a[1-i%2])//如果前后不一样就再需要一秒
			ans++;
	}
	cout<<ans<<endl;//输出
	return 0;
}
```
仔细想想就简单地结束啦！

---

## 作者：Fatalis_Lights (赞：2)

## Solution

观察题意，可以很明显的发现题目让你求连通块的个数，这种连通块由(0,1)构成。

比如下面这个样例：

Sample input 1: 6 1 0 0 1 1 0

观察一下，6个数，应该这样跑：1|0 0|1 1|0

所以输出是4。

模拟了一下，我们明白了，只需要求相邻两数不同的二元组数量再加1，加1是因为其实第一步也需要1s时间。

所以code:

```cpp
#include<bits/stdc++.h>
#define N 1000009
#define int long long
using namespace std;

int n,ans=1,a[N];

void print(int x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10);
    putchar(x%10+'0');
}

void read(int &x){
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

signed main(){
	read(n);
	for(register int i=1;i<=n;i++) read(a[i]); 
	for(register int i=1;i<=n;i++)
		if(i>1 && a[i]!=a[i-1]) ans++;
	print(ans);
	return 0;
}

```

---

## 作者：StudyingFather (赞：2)

每一秒，小 Z 都可以通过一段数字相同的区间。

问题就变成了极大连续数字相同区间的数量。

可以很轻松地在 $O(n)$ 的时间内解决。

```cpp
#include <cstdio>
int main()
{
 int n,ans=0;
 scanf("%d",&n);
 int lastx=1;
 for(int i=1;i<=n;i++)
 {
  int x;
  scanf("%d",&x);
  if(lastx!=x)ans++,lastx=x;
 }
 printf("%d\n",ans);
 return 0;
}
```


---

## 作者：Coding__QAQ (赞：2)

想法很简单，直接照题意模拟即可。

现在，唯一的难点就在如何模拟“开”，“关”两种状态。

易发现在$time$为奇时状态即为原状态，而$time$为偶时状态为其相反态，那我们不妨直接开两个数组$a$,$b$，$a$表示
$time$为奇状态,$b$表示$time$为偶状态，直接模拟即可。


------------

AC code:
```
#include<bits/stdc++.h>
using namespace std;
int n,pl,tim,a[1000050],b[1000050];
int main()
{
	scanf("%d",&n);
	for(int i=0;i<=n+1;i++)
		a[i]=9,b[i]=9;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		b[i]=a[i]==1?0:1;
	}
	while(pl<n)
	{
		tim++;
		if(tim%2!=0)
			while(a[pl+1]==0)pl++;
		else 
			while(b[pl+1]==0)pl++;
	}
	printf("%d",tim);
	return 0;
}
```


---

## 作者：R·Buffoon (赞：2)

**让我们一起来赞美良心出题人吧**
***
$T2$明显比$T1$简单，但$T1$是$\color{#ee0000}\text{红题}$，而$T2$是$\color{orange}\text{橙题}$？~~（$T1$由于多循环了一次被卡$92$，丢人）~~
***
```cpp
#include<bits/stdc++.h>
#define RI register int
#define LL long long
using namespace std;

inline LL in()//为什么开long long？因为T1
{
	LL aa=0,ff=1;char cc=getchar();
	for(;!isdigit(cc);cc=getchar())if(cc=='-')ff=-1;
	for(;isdigit(cc);cc=getchar())aa=(aa<<3)+(aa<<1)+(cc&15);
	return aa*ff;
}

const int N=1e6+5;

int n,cnt=0;
int a[N],ans;
int flag;

int main()
{
	n=in();
    for(RI i=1;i<=n;++i) a[i]=in();
    flag=a[1],a[n+1]=-1;//赋值-1，不然如果a[n]=0的话会被卡
    if(flag) ans=1;//如果第一个监控开启，要多等1秒
    else ans=0;
    while(cnt<=n)//开跑
    {
        while(a[++cnt]==flag);//为相同状态，可以跑过
        ++ans,flag^=1;//加1秒，改变监控器状态
    }
    cout<<ans<<endl;
	
	return 0;
}
```
看到大佬都是1个循环跑过的，顿时感觉我好菜（好吧，我确实菜）

~~不过，我这个代码可以跑$88ms$，而大佬跑$44ms$，我的吉利度更高！~~

---

## 作者：Eason_AC (赞：2)

这题目怀疑和[P4439](https://www.luogu.org/problem/P4439)撞Idea了，因为都差不多好吗！

---

首先我们来看这道题目，诶？这不就是算整体吗？然后立马想到了~~刚做的~~P4439，发现这两道题目Idea差不多，都是算一个序列里整体的个数。这道题目中，~~管理员~~小$Z$每次只能走都是$0$的一段，而一开始必定是$0$，所以小$Z$最少走过的秒数肯定是这一段里面所有整体的个数。所以这样就很简单了，$O(n)$做法轻松搞定。

下面贴上我的$AC$代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int n, a[1000007], ans;

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if(i == 1)	ans++;
		if(i > 1 && a[i] != a[i - 1])	ans++;
	}
	printf("%d", ans);
	return 0;
}
```

---

今天早上碰到了@[xieyi0408](https://www.luogu.org/user/135964)，然后他展示了一下他的写法，我发现他的比我的还要简单那么一点，所以把他的也贴一下：
```cpp
#include<bits/stdc++.h>
#define int long long//好东西 
using namespace std;
int ans,now,last=-1,n;
int read(){
	int x=0,s=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')s=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*s;
}
main(){
	n=read();
	for(int i=1;i<=n;i++){
		now=read();
		if(now!=last)last=now,ans++;
	}
	printf("%lld",ans);
}
```
他这个写法就是直接保存上一个点的状态，如果目前的状态比上一个状态不同就将last赋值为目前的状态，以便之后的比较，然后再将答案计数。

---

这两个代码都仅供参考，有什么不懂的请私信我或@[xieyi0408](https://www.luogu.org/user/135964)。

~~这次月赛是不是该调个顺序，感觉难度安排有点不妥~~

---

## 作者：江山_远方 (赞：1)

~~这题应该是红题+1~~

看到题目，我一脸蒙逼：什么鬼？

然后我不看题目，只看样例，顿时豁然开朗：

这题原来就是求出有多少个不同的区间个数

为自己的智商悲哀……

言归正传，当即我就码出了代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
int a[1000010]; 
int main()
{
	cin>>n;
	ans=1;//注意！不管有多少个监控都至少要跑一秒！
	for(register int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(register int i=2;i<=n;i++)if(a[i]!=a[i-1])ans++;//如果区间状态与上一个不一样，做一个计数器
	cout<<ans;
	return 0;
}
```
然后优化了一下空间：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,ans; 
int main()
{
	cin>>n;
	ans=1;
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		if(x!=y)ans++;
		y=x;
	}
	cout<<ans;
	return 0;
}
```
~~AC抱回家~~


---

## 作者：MoXiaodu (赞：1)

### 题目背景

由于$Y$校最近进行了对学校食堂的全面改革与对小卖部的全面整治(乱搞)，导致学校小卖部卖的零食被禁售了；学校食堂的炸鸡窗口也消失了；

并且学校的学生处$Q$主任严禁学生点外卖，日夜监察。

都说民以食为天，由于整天挨饿，全校同学处于水深火热之中。

### 题目描述

$zhouwc$的朋友（朋友就是自己系列）小$Z$由于饥饿难忍，不得不铤而走险点外卖。

但是学校的$Q$主任为了能够抓住点外卖的学生布置了天罗地网——监控

但是由于学校给$Q$主任的经费有限，所以这些监控不能持续工作，工作一秒之后便要暂停休息一秒，即开启一秒后关闭一秒再开启一秒...以此类推。

还是由于$Q$主任的经费有限，这些监控被排成了一条直线，这条直线便在学生通往学生外卖驻点——二号门（没有门卫）的必经之路上。

因为小$Z$修习了疾跑技能，所以小$Z$通过任意个数关闭的监控的时间均为1（即一次行动可以经过若干个未开的监控）。

由于小$Z$想吃外卖又不想受到正在监控室看着监控的$Q$主任的处分，请你告诉他至少要多少时间才能安全到达外卖驻点。

------------
### 解法：
用一个变量储存所有的读入的值，一个变量记录前一个值，如果当前与前一个不相等，$ans$++。

时间复杂度$O(n)$,空间复杂度$O(1)$
### 完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,dq=1,ans,ls;
inline long long read(){//读入优化
	long long f=1,out=0;char c=getchar();
	while(c>'9'||c<'0'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		out*=10;out+=c-'0';
		c=getchar();
	}
	return f*out;
}
int main(){
	n=read();
	for(long long i=1;i<=n;i++){
		ls=read();//读入
		if(ls!=dq){//不相等ans++
			ans++;
			dq=ls;
		}
	}
	cout<<ans;
	return 0;
} 
```

---

## 作者：Crab_Dave (赞：1)

~~$T2$比$T1$简单系列qwq...~~

求连续的01区间数量就行。

详见代码qwq
```cpp
#include<cstdio>
using namespace std;//头文件

int n,ans;
int a[1000005];

int main()
{
	scanf("%d",&n);//输入n
	for(register int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);//输入a[i]
		if(i==1)continue;
		if(a[i]!=a[i-1])ans++;//如果不连续了ans+1
	}
	printf("%d",ans+1);//刚开始的时候还有一段
   return 0;//结束了罪恶的一生qwq
}
```
泥萌康窝辛辛枯枯写题解，资瓷一下叭qwq

---

## 作者：XianChanting (赞：1)

_~~这题很简单~~_ 

__不用模拟！！！__

------------


对数据进行观察，不难发现：

**需要等的次数是0与1的交界点的个数+1**

知道这一点后直接上代码（ 很简单 )：
```cpp
#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include<cstdio>
inline int read() { //快读
	register int x=0;
	register char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=x*10+c-'0',c=getchar();
	return x;
}
inline void put_int(int x) {//快输
	if(x>9) put_int(x/10);
	putchar(x%10+'0');
}
int main() {
	register int n,num=1,last,now,i;
	n=read(),now=last=read();//now存储这次读入的，last存储上次读入的
	for(i=1;i<n;++i){
		last=now,now=read();//不难理解，迭代
		if(last!=now)++num;//求0与1的交界
	}
	put_int(num);//直接输出
	return 0;
}
```


---

## 作者：翰森锐 (赞：1)


# 难度有误

## 这个T2好简单~~T1有些变态~~

## 思路：



>不用按照样例解释去开关开关模拟

>我们只要计算连续不变化子串的个数就可以了。（自取的名字

什么是连续不变化子串？

设一个串叫0 1 1 1 0 0 0 1 0

连续不变化子串分别为 0，1 1 1，0 0 0，1和0：




有了思路，又怎么去实现呢

需要一个变量记录上一个字串或直接对比

代码：

```
//#include<bits/stdc++。h>好东西
//#define INF 1000001宏定义是个好东西，
//using namespace std;
//int n,a[INF+INF-12342];//不解释
//int ans,now;
inline int read()//读入优化
{
	int n_d=0,o_d=1;
	char c_d=getchar();
	while(c_d<'0'||c_d>'9')
	{
		if(c_d=='-')
			o_d=-1;
		c_d=getchar();
	}
	while(c_d>='0'&&c_d<='9')
	{
		n_d=n_d*10+c_d-'0';
		c_d=getchar();
	}
	return n_d*o_d;
}
int main()
{
	
 	//freopen(".in","r",stdin)
	//freopen(".out","w",stdout)
    n=read()；
	a[0]=read()；
	now=a[0]；
	if(a[0]==1)ans++；//特判开头就是1的情况
	for(int i=1;i<n;i++){
		a[i]=read();
		if(a[i]!=now)ans++,now=a[i];//计算连续子串
	}
	printf("%d",ans+1)；//总次数会少一，so ++
	putchar('\n');
	return 0;
}```


留个赞再走吧。



---

## 作者：love_luke (赞：1)

这是一道只要看样例就能过的题。。。

观察题目发现，小Z每次可以用一秒越过所有关闭的监控，又保证了第一个监控是关闭的，所有监控变化周期又是一样的，只要求输入数据中连续0和连续1的总段数就行了。

代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005];
int main()
{
	int n,sum=1;
	scanf("%d",&n);
	scanf("%d",&a[1]);
	for (int i=2;i<=n;++i)
	{
		scanf("%d",&a[i]);
		if (a[i]!=a[i-1]) sum++;//如果前一个和当前不一样表明又多了一段
	}
	cout<<sum;
	return 0;
}
```


---

## 作者：　　　吾皇 (赞：1)

不难发现，$ans$的值即为监控序列中~~连续串~~（也不知道应该叫啥）的数量。

甚至连数组都可以抛弃掉，直接判断这个监控和我目前遇到的监控开关情况是否一致，一致我就走，不一致我就$ans$++，同时改变目前遇到的监控开关情况的值。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,p,ans;
static char buf[100000],*pa=buf,*pb=buf;
#define gc pa==pb&&(pb=(pa=buf)+fread(buf,1,100000,stdin),pa==pb)?EOF:*pa++
inline int read(){
    register int x(0);register char c(gc);
    while(c<'0'||c>'9')c=gc;
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc;
    return x;
}//读入优化
int main(){
	n=read(),x=read();//先读入初始状态
	for(register int i=2;i<=n;i++) {
		p=read();//读入当前监控的开关状态
		if(p!=x) ans++,x=p;//如果不一致更改，答案+1
	}
	printf("%d",ans+1);//由于第一串并不会被算进去，所以输出时要+1
}

```


---

## 作者：爱晚亭哦 (赞：1)

因为穿过连续0或1只需要时间1，所以只要判断a[i]？=a[i+1]即可，若不等则时间加1.

注意到终点时间也要加1

Code:

```
#include<cstdio>
int a[1000001];//开个数组比较好写
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		if(a[i]!=a[i+1])//判断，不等则时间+1
			ans++;
	if(ans==0||a[n]==0)//如果全是1或0时间算1，到终点时间也算1
		ans++;
	printf("%d",ans);
}
```
~~怎么T1难度比T2还大啊~~

---

## 作者：vеctorwyx (赞：1)

## 贪心

好像比第一题~~还简单~~

那就直接上代码吧
```cpp
#include<iostream>
using namespace std;
int n,ji,ans;
bool a[1000010],bijiao;
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	cin>>a[i];
	while(ji<n)
	{
		if(a[ji]==bijiao)
		{
			ji++;//每一秒通过的关的监控数
		}
		else 
		{
			ans++;//监控开着不能过
			bijiao=!bijiao;//监控开关
		}
	}
	cout<<ans+1;
}
```


---

## 作者：Heap_Sort (赞：1)

或许是最简短的代码？

感觉比T1还水……  
其实只要找主序列被分成几个连续为1或0的序列，如果第一个为1的话，小Z不能在第一秒直接冲过去，要+1。

并且边读边处理即可，不需要用数组存啊（为什么题解里都用了数组？？）

Pascal代码（我应该是最早发pascal题解的人吧）
```pascal
var 
  n,a,b,c,d:longint;
begin
  readln(n);
  for a:=1 to n do 
   begin 
    read(b);
    if b<>c then inc(d);//当第一个为1时自然进入语句，答案+1
    c:=b;
   end;
  writeln(d+1);
end.
```


---

## 作者：Azazеl (赞：1)

来自一个第一题只拿了$92pts$的蒟蒻  

这道题我们通过读题就可以发现，**连续的所有当前状态相同监控摄像头都可以在遇见时用$1s$直接跑过去。**

举个简单的栗子（z代表小z）
```
Z  0   1   0   0   1
```
首先我们用$1s$跑过第一个关闭的摄像头，此时总用时$=1s$
情况如下:
```
1 Z 0   1   1   0
```
然后第二个摄像头已经关闭,我们也可以用$1s$跑过去，总用时$2s$  
```
0   1 Z 0   0   1
```
接下来两个摄像头都是关闭的,直接跑过去，总用时$3s$  
```
1   0   1   1 Z 0
```
接下来直接跑过去，就有可口的外卖了，总用时$4s$  

所以很容易发现ans=初始情况下连续为0或1的子段个数  

由于题目保证**第一个监控一定是关闭的**
所以我们不用花时间来等第一个摄像头关闭，可以直接跑过去 
（其实要的话也只需要加一个特判然后ans+1就可以）  

又是喜闻乐见的代码时间  
```cpp
#include <cstdio>
int a[1000005];
int main() {
	int n,tot=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(i>1)
		{
			if(a[i]!=a[i-1]) tot++;
		}
	}
	printf("%d",tot+1);
   	//由于最后一段在第n个的时候会被结束无法统计，所以需要手动+1
   	//此外，也可以在a数组最后设置一个-1（非0或1即可）帮助统计
	return 0;
}
```
就这样了，蒟蒻去回肝$T1$和$T3$了，债见。


---

## 作者：six_小6猪 (赞：1)

~~被第一题虐了~~

**来水下第二题**
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
	int a,ans=1;//ans从1开始
    short k,s;
	cin>>a;
	cin>>k;//最开始
	for(int i=2;i<=a;i++)//从2开始！
	{
		cin>>s;//边输入边判断
		if(k!=s)
		{
			ans++;//多一种情况
			k=s;//换情况
		} 
	}
	cout<<ans;
}
```
很水的打法，大佬勿喷！ 

打模拟是一个OIer的基础
                --沃兹.基胡硕德
                
就是这样
拜拜（撒花）
（请勿抄袭~~虽然题很水~~）

---

## 作者：Kevin_Wa (赞：1)

### 题目大意

这题的意思大概就是有$n$个监控，每个监控有一个状态$0$或$1$。由于题面里提到了小$Z$穿过同一状态的监控只需要一个单位的时间，所以本题就是让你求连续的同状态的序列有多少个。

### 评价

~~我怎么感觉这题才是入门题~~

在比赛中一次就过了。

~~为了刷时间，我还开了火车头~~

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000010],cnt;
template <typename T> void read(T &x) {
x = 0; char c = getchar();int f=1;
for (; !isdigit(c); c = getchar()) if (c=='-') f=-1;
for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
x*=f;
}
int main()
{
//freopen(".in","r",stdin);
//freopen(".out","w",stdout);
read(n);
for (int i=1;i<=n;i++)
  read(a[i]);
int cnt=0;
a[0]=a[1];a[n+1]=-1;
for (int i=1;i<=n+1;i++)
  if (a[i]!=a[i-1]) cnt++;
printf("%d\n",cnt);
return 0;
}
```


---

## 作者：irosalies (赞：0)

~~一个卑微的蒟蒻的题解~~

其实这道题真的很简单
因为监控变化时间一定，所以只需要求出有几段不同的监控（或为1，或为0）
代码如下：
```cpp
#include<bits/stdc++.h>//万能头
using namespace std;
int main(){
	int n,ai,a,s=1,t;//把s设置为1是为了能够判断监控末尾的情况，不然会少算
	cin>>n;
   cin>>a;//先读入第一个数
   t=a;//把t赋成a
   for(int i=0;i<n-1;i++){
    cin>>ai;
    if(ai!=t)s++;//判断，若新读入的数和前一个数不同，说明又有一段不同的监控，计数器++
    t=ai;//把t赋成新读入的数
	}
	cout<<s;//输出计数器
	return 0;
}
```
望通过


---

## 作者：蒟蒻lxy (赞：0)

### By：QAQer

欢迎到[**我的博客**](https://www.luogu.org/blog/lxy0508cpp/solution-p5639)中查看

## 1.分析
我看了一下似乎官方题解没有我这个方法啊。

此题是一道**贪心**题。    
对于每一秒，小Z可以冲到前方最远的关闭的监控下（即连续0中的最后一个）。      
直接每次更新位置就可以了

Q：怎么处理监控的开/关？    
A：先预处理``a``数组的0为-1，再设定f在1和-1之间变化即可（具体见代码）

### 时间复杂度

虽然是双重while，但是每一个点最多访问1次，即**O(n)**    
~~若有错请勿喷，请在评论区提出~~

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005],ans,now,f=-1;//f用于处理监控的开/关
int main()
{
	cin >> n;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		if(a[i]==0)
			a[i]=-1;//预处理，-1表示监控关闭
	}
	while(now<n)
	{
		f*=-1;//f在1与-1之间变化，f==-1时监控状态取反，f==0时不变
		int noww=now;//noww记录可以到达的最远位置
		while(a[noww+1]*f==-1) noww++;
		//a[noww+1]*f表示本次的监控经过改变后的状态
		now=noww;//重置位置，只考虑本位置之后的监控
		ans++;//次数累加
	}
	cout << ans << endl;
	return 0;
}

```
~~Ps：小Z不用跑回来吗(逃~~

---

## 作者：_扶笙_ (赞：0)


由于这个9102年用Pascal的人太少了，我就来发一发。

[题目链接](https://www.luogu.org/problem/P5639)

由于是官方比赛，题意描述的非常清楚，连我这个蒟蒻都看懂了，这点非常好评！

来看看怎么做，由于本蒟蒻太蒻了，根本不会50分的做法，就在这里讲讲100分。

其实上，小Z一次最多冲多少呢？

答案是非常显然的，在当前位置之后的连续的关闭的都冲过去。然后1s过去了，关闭的开启了，开启的关闭了，小Z就可以继续冲过去了。

可能描述的不太清楚，来看一组数据您就一定可以明白了。

10

1 2 3 4 5 6 7 8 9 10

0 0 0 1 1 1 0 1 0  0

第一次肯定冲到位置3，然后关的开，开的关，第二次冲到6，第三次冲到7，第四次冲到8，最后一次直接冲走。所以答案是5。

考虑如何实现，既然一次直接冲过去，而且每隔1s就会轮换，那么也就是说，只要找有多少个连续的0和连续的1就行了。

这样分析下来就非常简单了，如果当前元素和前一个元素不同的话，ans+1就行了，但是记得输出的时候ans加上一，因为这样做出来的ans是连续两个元素不同的个数，所有连续的相同的是连续两个不同的个数加上一。


最后帖代码（~~Pascal九排超短代码~~）
```
var n,i,ans:longint;
a:array[0..1000000] of longint;
begin
readln(n);
for i:=1 to n do read(a[i]);
for i:=1 to n do
  if a[i]<>a[i-1] then ans:=ans+1;
writeln(ans+1);
end.
```

---

## 作者：optimize_2 (赞：0)

## 异或系列

`0^0=0`

`1^0=1`

`0^1=0`

`1^1=0`



首先我们看看上面4个等式可以发现:对于值为0或1的两个变量a,b,如果**b==0**,则a**不变**,如果**b==1**,则a**取反**.

这是不是刚好对应着监控的开关?

`bool f=0;`和`f=!f;`就完美控制了监控状态.

```
#include<bits/stdc++.h>
using namespace std;

int n;
int ans;
bool a[1000010],f;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		while(!(a[i]^f)&&i<=n) i++;  //a[i]^f:通过f来控制第i个监控.
//i++:如果那里可以走,往前一步
		i--;//走过头了,回来
		ans++;//时间+1
		f=!f;//开->关,关->开
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：pomelo_nene (赞：0)

小蒟蒻只能过掉前面两道题 发篇题解安慰心情

我们知道小z跑一段只用1秒，所以说我们把相邻的1或0缩成一个1或0（因为都只需要1秒）然后统计1和0的个数和即可

我们不用储存，边读边处理即可

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
//int a[1000005];
int read()
{
	char c=getchar();
	int x=0,f=1;
	while(c<'0' || c>'9')
	{
		if(c=='-')	f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')	x=(x<<1)+(x<<3)+(c^'0'),c=getchar();
	return x*f;
}
int main(){
	int t=2,ans=1;
	int n=read();
	while(n-->0)
	{
		int x=read();
		if(t!=2 && x!=t)	++ans,t=x;//如果我们这个监控和上一段不一样，我们需要多用一秒
		if(t==2)	t=x;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Starlight237 (赞：0)

T2

由题：要使得zhouwc所用的时间最短，每一次都必然会选择跑到能到达的最远点。将这些监控分为一些连续段，满足每一段监控的状态相同。假设目前跳过了某个连续为0的路段，且下段监控都为开启状态，则下一秒，下一路段的监控将会关闭，故可以再跳过一段。又由于题目保证$a_1=0$，即最开始的一段监控为关闭状态。故必然有解。

由归纳法知答案即为连续段的个数。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
#define IOSIZE 2200000
static char in[IOSIZE],*p=in,out[20],*q=out,ch[20],*t=ch;
inline int read(){
	reg int x=0;
	while(*p<48)++p;
	while(*p>47)x=(x<<1)+(x<<3)+(*p++^48);
	return x;
}
inline char gc(){
	while(isspace(*p))++p;
	return *p++;
}
inline void write(int x){
	x<0&&(*q++='-',x=-x);
	!x&&(*q++='0');
	while(x)*t++=x%10+48,x/=10;
	while(t!=ch)*q++=*--t;
}
int main(){
	fread(in,1,IOSIZE,stdin);
	int n=read();
	reg int ans=1;reg char ch,lst;
	lst=gc();
	for(reg int i=1;i<n;++i)
		ch=gc(),ch!=lst&&(lst=ch,++ans);
	write(ans);
	fwrite(out,1,q-out,stdout);
	return 0;
}
```

---

## 作者：文·和 (赞：0)

这道题看起来花里胡哨，我们看看样例发现其实就是有几段不同，如果开始为1就时间加个1就OK。

### 怎么证明呢？？

我们推一推：

如果当前在面前的是1比如：11000011

那么我们等1秒，变成00111100.

花一秒走过去，11000011，此时我们面前还是0

再走过这串零，前面的1又变成了0.....

所以我们在中间是不要等待的。答案也就是段数。

### 具体方法

不开long long见祖宗，还是开一个好。

数组开大1个方便加上最后一段。

#### 第0个赋0,很巧妙，如果第一个是0则不加秒数，不是0则加一秒。

加上的最后一个赋为不同于原来的最后的值，也就可以把最后一段加上。

不说了，看代码：


```
#include <bits/stdc++.h>
using namespace std；
bool p[1000002];//监控开启状态
long long n,i,ans;
int main(){
cin>>n;
for(i=1;i<=n;i++) cin>>p[i];  //输入
p[0]=0;   //第0个赋0
p[n+1]=1-p[n];  //加上一个赋为1-最后一个
for(i=1;i<=n+1;i++) if(p[i]!=p[i-1]) ans++;  //求中间的段数
cout<<ans; //输出
return 0;
}
```

珍爱账号，请勿抄袭（抄袭有惊~~吓~~喜哦~）


---

## 作者：jbc392 (赞：0)

一道水题

就是求有几个连续且相同的块

样例1：

![](https://cdn.luogu.com.cn/upload/image_hosting/kyx8p17m.png)

看图可知一共四个块

思路：

从头开始模拟遇到不一样的就累加答案

最后一个要特判

AC code：

```
#include <bits/stdc++.h>
#define r register
using namespace std;

int n ,now ,last ,ans;//now表示现在输入的，last表示上一个不同的

inline int read()//快读
{
	int x = 0;
	char c = getchar();
	while(!isdigit(c))
	{
		c = getchar();
	}
	while(isdigit(c))
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	return x;
}

int main()
{
	n = read();
	for(r int i = 1;i <= n;i++)
	{
		now = read();
		if(now != last)//遇到不一样的就累加答案
		{
			ans++;
			last = now;
		}
	}
	if(now == last) ans++;//最后的特判
	cout << ans;
	
	return 0;//好习惯
}
```


---

## 作者：Create_Random (赞：0)

~~为什么我感觉T2比T1简单~~

本蒟蒻思路：

直接判断出第i个和第i+1个是否相同

每次将答案+1即可

注意如果开始时也为1

贴代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int a[1000010];
int ans=1;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]!=a[i-1])判断第i个和第i+1个是否相同
		{
			ans++;将答案每次+1
		}
	}
	printf("%d",ans);
	return 0;
}
```

[提交记录](https://www.luogu.org/record/26707489)

---

## 作者：stywzh (赞：0)

### 感觉这个题才应该是~~红题~~？！
比起第一题卡了5次92分，~~这题明显水啊~~。

------------

由题意可知，我们只要在是零的地方尽量走，走到一段零的最右端，再从下一次是零的地方做同样的操作就可以了。


------------
这也就意味着，在题目输入的序列中，我们只要找连续是零，和连续是一的区间就可以了。
（因为在下一秒，这一秒的零会变成一，一会变成零）


------------
Code:
```cpp
#include<iostream>
using namespace std;

int n,a[1000086],ans;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	for(int i=1;i<n;i++)
		if(a[i]!=a[i+1])ans++;
	cout<<ans+1<<endl;
	return 0;
}
```
## 信心赛警告

---

## 作者：USER113968 (赞：0)


首先看题面，可能有些同学没有理解，我来讲一下是什么意思。

大意是说，有一条线段，线段上有均匀分布的n个点。某人想从点1到达点n，他每次可以耗费一秒，穿越一个区间，且这个区间内所有点都为0，并一定会在第一个是1的点前面停下，且每一秒，每个点的状态都会变化——1变成0，0变成1。问，他穿越整个线段需要多少秒。

那么，可以想到一种很容易理解的算法——模拟。首先，看看能从这个点跑到哪个点。接下来，将坐标设为更新点。最后，把所有点更新一下。代码如下

```c++
#include<stdio.h>
unsigned int light[1000001];//使用数组存储每个点的状态
int main()
{
	int n;//表示有多少个点
	scanf("%d",&n);
	register int x=1;//初始站在一号点前面
	register int time=0;//用了的时间为0
	register int i;
	for(i=1;i<=n;++i)
		scanf("%d",&light[i]);//读入
	while(x<=n)//还没有到达终点
	{
		for(i=x;light[i]!=1&&i<=n;++i)
			;//计算能跑到哪一个点
		x=i;//更新坐标
		++time;
		for(i=x;i<=n;++i)//由于一直往后跑，只需要更新后面的点
			light[i]=!light[i];//更新
	}
	printf("%d",time);//输出最终时间
	return 0;
}
```



不过，这份代码会超时：50分。



那么，应该怎么优化呢？事实上，我们发现，如果不更新点，那么是第一次通过为0的点，第二次通过为1的点，第三次通过为0的点，第四次通过为1的点······



每次走的都是上一次走的点的逆转。上次走1，这次走0；上次走0，这次走1······



那么，我们可以设置一个变量，每次循环都更新，每次都跑过跟这个变量相等的点。这样就避免了每次的序列修改。AC代码如下



```c++
#include<stdio.h>
unsigned int light[1000001];
int main()
{
	int n;
	scanf("%d",&n);
	register int x=1;
	register int time=0;
	register int i;
	for(i=1;i<=n;++i)
		scanf("%d",&light[i]);
	int flag=1;//每次遇到后应该停下的点（可以跑过值为!flag的点）
	while(x<=n)
	{
		for(i=x;light[i]!=flag&&i<=n;++i)
			;
		x=i;
		++time;
		if(flag)
			flag=0;
		else
			flag=1;
        //更新这个标记变量
	}
	printf("%d",time);//输出答案
	return 0;
}
```



---

## 作者：lapidot (赞：0)

其实吧，此题为模拟信心题。~~斗胆来水一篇题解。~~

由题意，得小~~Rainbow~~D~~ash~~可花费一秒通过一片全为0的区域。所以将问题转化为求**与上一段不同的字符串**的个数即可。

放出个人辣鸡代码（只是为了说明，大犇请无视）
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans;
char a[1000001];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		if(a[i]!=a[i-1])ans++;
	}
	cout<<ans<<endl;
}
```
加上lby或ljh友情提供的[四十九行大优化](https://www.luogu.org/blog/lby-2006-07-26/post-49-xing-tai-you-hua)或食用更佳


---

## 作者：氷芽川四糸乃 (赞：0)

>这些监控不能持续工作，工作一秒之后便要暂停休息一秒，即开启一秒后关闭一秒再开启一秒...以此类推

>一次行动可以经过若干个未开的监控

>保证第一个监控一定是关闭的

注意这几点结论就很显然了，由于一次能经过的长度是无限的，所以限制的只有监控的是否开关了，对于一次疾跑，他所经过的最长距离即为连续的相同 $\text{0/1}$ 序列的长度。

所以这道题就变成了：给你一个 $\text{0/1}$ 序列，求有多少个不同的连续 $\text{0/1}$ 子序列。

基于上述结论，就可以愉快的秒切这题啦。~~虽然机房大佬在开赛3分钟内就切了1-2了~~

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	int n;
	int last = 1;//第一个监控必定关闭，所以初值设为1.
	int ans = 0;

	cin >> n;

	for(int i = 1; i <= n; i ++) {//边读边做，遇到不同的ans就++.
		int input;

		cin >> input;
		
		if(input != last) {
			last ^= 1;//0切换为1 | 1切换为0.
			ans ++;
		}
	}
	cout << ans;
	return 0;
}

```

---

## 作者：Purple_sword (赞：0)

题解：CSG Round2 T2 守序者的尊严

对于开关性相同的一段,显然可以用疾跑在1s内走完；

对于开关性不相同的,他就得等一秒后再出发.

*因为给我们的是第0s的状态,若第一个数为1,则还需等1s;若为0,则可直接出发.

*根据题意,t必须初始化为1.

于是我们就有了以下代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t=1;//t初始化为1
bool flag,last;//flag记录当前状态,last是前一个的状态(初始为0)
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		cin>>flag;//输入当前状态
		if(flag!=last)//若与前面状态不同,t+1,再将last更新为flag
			++t,last=flag;
	}
	printf("%d",t);//输出时间
    return 0;
}
```
亲测手打3分钟过了,果然比第一题简单呢。。

---

## 作者：S1gMa (赞：0)

做此次月赛唯一感觉的就是T1 难度 ~~入门x 普及+ ✔ 。。。。~~

~~所以秒出T2的我来发个题解~~

###### 首先 根据题意来分析题面，
```
但是由于学校给Q主任的经费有限
所以这些监控不能持续工作
工作一秒之后便要暂停休息一秒
即开启一秒后关闭一秒再开启一秒
以此类推
```
 而这里： 
###  即开启一秒后关闭一秒再开启一秒
## 为重点！！！！

###### 转换为 每当前一个数不等于当前数则时间（步数）加一

这里我写的有点麻烦因为开关的话只含 $0$ $1$ QAQ

# 出代码

```
#include <bits/stdc++.h>
//万能头不解释
using namespace std;

int main(){
    int n, f;
    // n 为总个数
    cin >> n;
    int sum = 0, qwq = 1;// 为1的原因是， 至少都要走一步
    // sum 来统计， qwq 来计算走几次
 
    cin >> f;
    // 先输入一个 f 表示第一个数 
    sum = f;// 将 sum 赋 为 f
    for (int i = 1; i < n; i++)
        {
            cin >> f;//每次读入
            if(sum != f){//分别判断一次是否等于前一个几个数
                sum = f;//如果不等于说明我们要变化一次， 因此 将 sum 赋成当前的 f
                qwq++;//步数++
            }
        }
        cout << qwq << endl;//输出
}
```

其实直接水过去就好了

---

## 作者：Cyancer (赞：0)

首先，注意题面的这里：  
>这些监控不能持续工作，工作一秒之后便要暂停休息一秒，即开启一秒后关闭一秒再开启一秒...以此类推  
  
>小Z通过任意个数关闭的监控的时间均为1（即一次行动可以经过若干个未开的监控）

也就是说，对于所有开始处于同一状态的监控，在任意时刻它们的状态都是相同的，那么这个问题就转化为求内部元素相同的连续区间个数。  
我们用${f}$来存储开始的状态，也就是第一个摄像头的状态，${time}$记录时间，${num}$记录下一个摄像头的初始状态，如果${f}$==${num}$，就代表下一个摄像头与当前摄像头初始状态相同，~~可以继续冲~~，如果${f}$！=${num}$那么${time}$++，并改变${f}$，${f}$变化一次，就代表进入下一个区间于是${time}$++。  
剩下的看代码吧 （~~快读快输是用来蹭rank的可以不用~~）：
```cpp
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<cctype>
#include<cmath>
#define mx 1000005
#define mod 998244353
#define ll long long
#define reg register long long
using namespace std;
ll n,num,tim=1,f;
//快读
template <typename N>
inline void Cin(N &x){
	x=0;
	char c=getchar();
	while(!isdigit(c)){
		c=getchar();
	}
	while(isdigit(c)){
		x=(x<<3)+(x<<1)+c-48,c=getchar();
	}
}
//快输
template <typename N>
inline void Cout(N x){
	if(x>9){
		Cout(x/10);
	}
	putchar(x%10+48);
}
int main(){
	Cin(n);
	for(reg i=1;i<=n;i++){
		Cin(num);
		if(num==f){
			continue;
		}
		tim++;
		f=num;
	}
	Cout(tim);
	return 0;
}
```


---

## 作者：静之城 (赞：0)

### 不要看着（普及-）
很简单！

先看 1 1 0 0 0 1 0

我们会把他这样分{11}{000}{1}{0}

瞧这不就是答案了么！
：
有4组，4+1=5！
别忘了第一个是一搭时候要加加哦——
## 上代码！
```
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[1000000]={0};
	for(int i=0;i!=n;i++)
	{
		cin>>a[i];
	}
	int da=0;
	if(a[0]==1)
	{
		da++;
	}
	for(int i=1;i!=n;i++)
	{
		if(a[i]!=a[i-1])
		{
			da++;
		}
	}//静之城
	cout<<da+1;
	return 0;
}
```
while（1）；

求过~


---

## 作者：ShineEternal (赞：0)

[好东西](https://blog.csdn.net/kkkksc03/article/details/102994393)

## solution:

这道题也许比T1还简单？

因为监控开一次关一次，所以我们完全可以遇到一段0变成1，或者1变成0就记录一下。

- 然后特殊处理一下开头

因为开头一定需要花费一段时间

## code:
```cpp
#include<cstdio>
using namespace std;
int a[1000005];
int main()
{
	int n;
	scanf("%d",&n);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		if(a[i]!=a[i-1]||i==1)
		{
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

