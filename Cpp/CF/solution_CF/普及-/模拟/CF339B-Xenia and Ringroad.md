# Xenia and Ringroad

## 题目描述

Xenia lives in a city that has $ n $ houses built along the main ringroad. The ringroad houses are numbered 1 through $ n $ in the clockwise order. The ringroad traffic is one way and also is clockwise.

Xenia has recently moved into the ringroad house number 1. As a result, she's got $ m $ things to do. In order to complete the $ i $ -th task, she needs to be in the house number $ a_{i} $ and complete all tasks with numbers less than $ i $ . Initially, Xenia is in the house number 1, find the minimum time she needs to complete all her tasks if moving from a house to a neighboring one along the ringroad takes one unit of time.

## 说明/提示

In the first test example the sequence of Xenia's moves along the ringroad looks as follows: $ 1→2→3→4→1→2→3 $ . This is optimal sequence. So, she needs 6 time units.

## 样例 #1

### 输入

```
4 3
3 2 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4 3
2 3 3
```

### 输出

```
2
```

# 题解

## 作者：Marxistdzy (赞：2)

### 题意简述

- 所有的房子都是建在一个环线上的。有 $m$ 个任务要完成，并只能按顺时针方向走，房子排列号码也为顺时针递增。
- 要完成第 $i$ 个任务，要走到第 $a_i$ 个房里，若两个任务在一个房子里，则可以不走。
- 问她要最少要走多少个单位长度。

### 思路
还是挺简单的一道题。其实就是枚举，然后判断即可。

输入 $n$ 和 $m$，输入 `a[m]` 数组，定义 $b$ 为 $a_0-1$，然后分为两种情况讨论：

- $a_i > a_{i+1}$.$b$ 累加 `n-a[i]+a[i+1]`。
- $a_i \le a_{i+1}$.$b$ 累加 `a[i+1]-a[i]`。

最后输出 $b$ 即可。

注意：这题有个坑点，由于数据量很大，所以要开 long long。看到有的题解说要用快读，其实不用也能过。

AC 代码：

```cpp
#include <cstdio>
#define ll long long
using namespace std;

int main()
{
    ll n, m;
    scanf("%lld %lld", &n, &m); 
    ll a[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%lld", &a[i]);
    }
    ll b=a[0]-1;
    for (int i = 0; i < m-1; i++)
    {
        if (a[i]>a[i+1])
        {
            b+=n-a[i]+a[i+1];
        }
        else
        {
            b+=a[i+1]-a[i];
        }
        
    }
    printf("%lld", b);
    return 0;
}
```
完结撒花！

---

## 作者：Lips (赞：2)

# 我这种蒟蒻只能做做黄题了

康到题面的第一眼，直接想到的就是暴力~~我这种蒟蒻只会暴力了~~，但我们发现，$N,M\le 10^5$，近与 $O(M^2)$ 的暴力做法肯定妥妥地 $T$ 飞，所以，只有 $O(M)$ 才能 $AC$

定义 $now$ 为当前 $\texttt{Xenia}$ 所在的房子，$ans$ 为最终答案，$x$ 为目标房子，那会发现，$now$ 与 $x$ 的关系一共有三种：

1. $x=now$ 

2. $x>now$

3. $x<now$

对于第一种，直接 $continue$ 就好了，不用移动。

对于第二种，我们可以计算 $now$ 到 $x$ 距离就好了，公式为 $ans=ans+(x-now)$

而对于第三种，可以把 $\texttt{Xenia}$ 所走的路线分为两段，第一段：$now->1$，第二段：$1->x$。对于第一段，他就可以拆分为 $now->N$ 的距离 $+1$，公式为：$N-now+1$；对于第二段，公式为：$x-1$。将两段的长度加起来化简可得 $N-now+x$

**最后，注意：** $10$年$\text{OI}$一场空，不开$\text{long long}$见祖宗

$Code:$

```cpp
#include<cstdio>
using namespace std;
long long ans,n,m,now=1,x;//一定要开long long!
inline long long read()//快读，本题数据量大 
{
	long long s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=s*10+(ch-'0'),ch=getchar();
	return s*w;
}
int main()
{
	n=read(),m=read();
	for(register long long i=1;i<=m;i++)
	{
		x=read();
		if(x==now) continue;//相等的情况 
		if(x>now)//若x在now的前方 
		{
			ans=ans+(x-now);//公式 
			now=x;//别忘更新目前的所在点 
			continue;
		}
		ans=ans+(n-now+x);//否则x就在now的后方 
		now=x;//更新 
	}
	printf("%lld\n",ans);//输出 
	return 0;//return 0养成良好习惯 
}
```
对于一个蒟蒻来说，只能写写黄题题解了......

点个赞再走吧Orz



---

## 作者：p924874163 (赞：0)

## 分析

首先，我们可以把这些房子看成一个环，在这一个环中，求长度的方法就是直接暴力枚举，具体见代码。

---

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6;
long long n,m,a[N],last=1,ans;	//ans用来存放答案，last则是上一次完成任务时到的房子的编号
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		cin>>a[i];
	for(int i=1;i<=m;i++)
	{
		if(a[i]>=last)	
        //如果现在房子的编号大于之前编号时，直接加上它们的差，也就是这两座房子的距离
			ans+=a[i]-last;	
		else ans+=(n+a[i]-last);
        //当a[i]<last时，说明已经走过一圈，回到起点了，所以应该加上房子的数量
		last=a[i];//更新last的值
	}	
	cout<<ans;
	return 0;
}
```


---

## 作者：WinterRain208 (赞：0)

题解 CF339B Xenia and Ringroad

题目不赘述了。

### 做法

按题意模拟即可，对于任务数组中相邻的两个元素$a_i$和$a_j$，只需要根据大小判断距离即可。

如果$a_j$大于$a_i$，那么这次需要走的路程不经过点1，只需累加 $a_j-a_i$ 即可。

否则将圆环抽象成一个直线，根据两点位置可知如果目的地比当前位置编号小的话那么累加 $a_j+m-a_i$ 。

读入数据，在数组开头加入当前位置1，然后遍历数组即可。

### 代码

```cpp
long long n,m,a[N],ans=0;
	m=read(),n=read();
	a[1]=1;F(i,2,n+1)a[i]=read();
	F(i,1,n)
		if(a[i]!=a[i+1])ans+=(a[i]>a[i+1]?a[i+1]+m-a[i]:a[i+1]-a[i]);
	write(ans);
```


---

## 作者：sinsop90 (赞：0)

这道题我们只需要判断两种情况:

1.该任务的房子编号 $≥$ 现在在的这个房子编号

直接加上任务房子编号和现在在的这个房子编号的差即可

2.该任务的房子编号 $≤$ 现在在的这个房子编号

不难发现，用房子数量减去现在在的这个房子编号再加上任务房子编号即可

因此有了如下代码：

```
#include <bits/stdc++.h>
using namespace std;
long long n, m, mps[100005], k = 1, ans = 0;//不开long long见祖宗...
int main() {
	scanf("%lld%lld", &n, &m);
	for(int i = 1;i <= m;i++) {
		scanf("%lld", &mps[i]);
		if(mps[i] >= k) {//第一种情况
			ans += mps[i]-k;
		}
		else {//第二种情况
			ans += (n-k+mps[i]);
		}
		k = mps[i];//现在在的位置
	} 
	cout << ans << endl;
}
```


---

## 作者：小豆子范德萨 (赞：0)

- 在线处理即可
- 注意只能顺时针走：初始当前位置ind为1，如果下一个任务a[i]要比当前位置要大，则可以直接走a[i]-in步，若下一个任务的位置要比当前位置小，则需要绕一圈回来，所需步数n-(ind-a[i])。
- 需要注意累加的ans需要定义为long long，否则会产生溢出导致WA。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+10;
int a[maxn];

int main() {
	int n,m;cin>>n>>m;
	for(int i = 0;i < m;i++) cin>>a[i];
	
	int ind = 1;		//当前下标 
	long long ans = 0;
	for(int i = 0;i < m;i++) {
		if(ind < a[i]) {
			ans += (a[i]-ind);
		} else if(ind > a[i]) {
			ans += n - (ind-a[i]); 
		}
		ind = a[i];
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：yzx72424 (赞：0)

题意：给定 n 个地方，然后再给 m 个任务，每个任务必须在规定的地方完成，并且必须按顺序完成，问你最少时间。

简单模拟，在线操作即可，每次操作，计算当前位置到下一个距离，完成之后更新所在的位置和ans，

```
#include <bits/stdc++.h>
using namespace std;
inline int read(){ 
    char ch=getchar();int sum=0;
    while(!(ch>='0'&&ch<='9'))ch=getchar();
    while(ch>='0'&&ch<='9')sum=sum*10+ch-48,ch=getchar();
    return sum;
}
int main(){
    int n=read(),m=read(),x,p=1,a=0;
    while(m--){
            int x=read(); 
         a+=x-p;
            if(x<p)a+=n;
            p=x;
        }
    printf("%d",a);
    return 0;
}//zzz直接copy过不了，有问题可以私信问我
```


---

