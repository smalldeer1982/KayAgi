# Dasha and friends

## 题目描述

小A和小B参加障碍跑，跑道可能有多个，所有跑道是环形的，按逆时针方向跑，长度都是是L，都有n个障碍。 小A从起点A开始跑，沿途记录下经过的障碍物离开起点A的距离，如2,4,6；小B从起点B开始跑，沿途记录下经过的障碍物离开起点B的距离，如1,5,7。距离均为整数。 现在请你判断，小A和小B的使用的是否是同一个跑道。

## 样例 #1

### 输入

```
3 8
2 4 6
1 5 7
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
4 9
2 3 5 8
0 1 3 6
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
2 4
1 3
1 2
```

### 输出

```
NO
```

# 题解

## 作者：___new2zy___ (赞：4)

## 题解 CF761B 【Dasha and friends】

题目传送门:

https://www.luogu.org/problemnew/show/CF761B

本题还是有点水的，数据小= =暴力应该可以过吧

本人未亲测，但是用的是**最小表示法**

==========================================

好了好了，言归正传= =

### 本题大意：

有两个人在跑步，跑道总长为L，现给出**n个跑步时碰到的障碍与起点的距离**，请问这两个人是否在同一条跑道上跑步

**注意，跑道为环状**

如果再次简化题面：

对于**两个环**，给出每个点到起点的距离，**试问这两个环是否相同**

那么对于这个简化之后的问题，我们可以想到：

**如果这个环恰好经过“转”操作之后，这两个环恰好重合，那么这两个环一定相同**

那么当然有：**每两个障碍之间的距离一定相同**

（这里指的是**对于两个完全相同的环**）

其实也可以理解成**环上的一段弧相等**

那么我们有以下思路：

	1.对于两个环，把障碍之间的距离当做要判断的量，预处理距离即可
    
    2.然后通过“转”的操作判断距离是否相等即判断这两个环是否相等
    
那么如何解决这个问题：**通过“转”的操作判断距离是否相等就能判断这两个环是否相等**

对于这个问题，我们自然的能想到对于字符串进行操作的**最小表示法**

最小表示法的**优点**：

能够在O(n)的时间内判断两个长度相等的字符串是否是**循环同构**的

为什么说最小表示法适用呢？因为本题是一个环形跑道，而经过分析，**通过“转”的操作判断两个环是否相等正好符合最小表示法的解决范围**，所以使用最小表示法是~~显然~~合理的

那么关于最小表示法，直接看这个链接吧= =在这个题例我讲过了= =但是下面的代码中也会有解释，不懂的同学可以私信我= =

https://www.luogu.org/blog/new2zy/solution-p1368

温馨提示：不了解最小表示法下面代码会非常蒙，所以**强烈建议大家看看这个链接**

这个题其实和**p1368 工艺**差不多的（考虑的方面还比它多一点），上面这个链接就是工艺这个题

都可以做一做

**p1368工艺**链接:

https://www.luogu.org/problemnew/show/P1368

但是~~（废话开始）~~这个题由于数据很弱（n<=50）
所以说目测暴力判断也可以过= =本人就不测试了

下面直接放代码吧= =code:

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;
typedef long long ll;
const int inf=1e9+7;
inline int read()
{
    int p=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){p=p*10+c-'0';c=getchar();}
    return f*p;}
const int maxn=57;
int n,L;
int A[maxn],B[maxn];
int s1[maxn],s2[maxn];
inline int Min_show(int s[])
//求出串的最小表示 
{
	int i=0,j=1,k=0;
	//两个指针i,j,当前匹配长度为k
	//我们保证对于任意时刻i!=j
	while(i<n&&j<n&&k<n)
		  {
		  	if(s[(i+k)%n]==s[(j+k)%n])
		  	//两个位置相同匹配长度k++
		  		k++;
		  	else
				{
					if(s[(i+k)%n]>s[(j+k)%n])
						i+=k+1;
					//因为[i,i+k)与[j,j+k)相同
					//则在[i,i+k)中不可能有最小表示 
					//之后令i+=k+1,令匹配长度k=0即可 
					else j+=k+1;//同上 
					if(i==j)i++;//满足i!=j 
					k=0;
				}
		  }
	return min(i,j);
	//串的最小表示 
}
int main()
{
	n=read(),L=read();
	for(int i=0;i<=n-1;i++)
		A[i]=read();
	for(int i=0;i<=n-1;i++)
		B[i]=read();
	A[n]=A[0]+L;
	B[n]=B[0]+L;
	//读入+成环(最后一个点要回到起点) 
	for(int i=0;i<=n-1;i++)
		{
			s1[i]=A[i+1]-A[i];
			s2[i]=B[i+1]-B[i];
		}
	//处理障碍之间的距离 
	int ans1=Min_show(s1);
	int ans2=Min_show(s2);
	//求出两个环的最小表示 
	for(int i=0;i<=n-1;i++)//开始判断 
		if(s1[(i+ans1)%n]!=s2[(i+ans2)%n])
		   {
		   		//发现两个环循环后有位置不等 
				//那么两个环不相等 
		   		printf("NO\n");
		   		return 0;
		   }
	//正常结束即两环相等 
	printf("YES\n");
	return 0;
}
```

没啦，感谢阅读~~~

~~话说这样是不是在骗访问量= =~~

~~（厚颜无耻的。。。 老贼）~~

最后推广一下我的博客：

https://www.luogu.org/blog/new2zy/

拜拜~~~






---

## 作者：BushHuang (赞：1)

题目大意：给定两个环，判断它们是否相同。

此题数据量并不大 $(1\le n\le 50,n\le L\le 100)$, 因此可以使用暴力的方式：

通过旋转 $A$ 环，每次将环上的第 $i$ 个元素移到第 $i+1$ 个位置(最后一个元素移到第一个元素的位置），并将旋转完毕后的 $A$ 环与 $B$ 环相比较，即可得出正解。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,x,t; 
bool a[100],b[100],flag; //AB两环 (bool型,1表示有障碍物,0表示没有障碍物) 
int main()
{
	cin>>n>>l;
	for(int i=1;i<=n;i++) //输入A,B两环 
	{
		cin>>x;
		a[x]=true;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		b[x]=true;
	}
	for(int i=1;i<=l;i++)
	{
		t=a[l-1]; //将最后一个元素存下来 
		for(int j=l-1;j>=1;j--) //将第j个元素移到j+1的位置 
		{
			a[j]=a[j-1];
		} 
		a[0]=t;	//把最后一个元素存到第一个位置 
		flag=true;
		for(int j=0;j<l;j++) //判断A环是否与B环相同 
		{
			if(a[j]!=b[j]) flag=false;
		}
		if(flag)
		{
			cout<<"YES"<<endl; //如果相同输出"YES" 
			return 0;
		}
	}
	cout<<"NO"<<endl; //如果转了一圈还没有重合输出"NO" 
	return 0;
}
```


---

## 作者：kaaaai (赞：0)

难得的简单暴力~~还能水题解的~~题。

题目大意就是给出两个环和环上一些元素的位置，问两个环是否可以通过旋转后重合。
由于 $n$ 和 $L$ 的范围都很小，那么可以暴力。直接模拟将 $A$ 环旋转的操作，再把 $A$ 环与 $B$ 环比对即可。如果旋转了 $L$ 次也没有重合，那么说明两环不同。

将 $A$ 环旋转的操作具体为把环上每个元素的位置 $i$ 移到 $i+1$，把最后一个元素移到第一个。

时间复杂度 $O(L^2)$，通过绰绰有余。

## AC代码
~~调试代码吃我好几发。~~
```cpp
#include <bits/stdc++.h>
using namespace std;
bool r1[105],r2[105];
int main(){
	int n,l;
	cin >> n >> l;
	for(int i = 0;i < n;i++){
		int a;
		cin >> a;
		r1[a] = 1;
	}
	for(int i = 0;i < n;i++){
		int a;
		cin >> a;
		r2[a] = 1;
	}
	for(int j = 0;j < l;j++){
		bool last = r1[l-1];
		for(int i = l-1;i >= 1;i--)r1[i] = r1[i-1];
		r1[0] = last;//旋转操作
		
		bool same = 1;
		for(int i = 0;i < l;i++)if(r1[i]!=r2[i])same = 0;//判断是否相同
		if(same){
			cout << "YES";
			return 0;
		}
	}
	cout << "NO";
	return 0;
} 
```

---

## 作者：A_small_WA (赞：0)

开门见山，看到题目的第一眼先观察数据范围：$n$ 和 $L$ 都在 $100$ 以内，所以暴力是肯定能过的。

虽然两人的出发点不一样，但只要在同一个跑道上，不断旋转两人的出发点（即遇到的障碍物），如果有一时刻记录的障碍物完全重合，那么他们一定是在同一个跑道上的。反之，如果转了一圈以后障碍物都没有重合，那么就不在同一跑道上。

问题来了，怎么转呢？

我的思路就是将小 $A$ 记录的所有障碍物 $a_1\sim a_n$ 每次 $+1$，一共转 $L$ 次，枚举完每一种情况，这样就可以实现顺时针转动。有两点注意事项：

- 每次 $a_i+1$ 后，如果 $a_i>L$，那么得 $-L$，防止旋转后的的障碍物超出跑道长度。

- $a_1\sim a_n$ 都 $+1$ 后，需要进行 ```sort```（排序）操作，让障碍物从小到大一一对应。

剩下的，就看代码啦——

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1000],b[1000];
int main(){
	int l,n;
	cin>>n>>l;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	int tmp=0;
	while(1){
		int flag=0;
		for(int i=1;i<=n;i++){
		    a[i]++;
		    a[i]%=l;
	    }
	    sort(a+1,a+n+1);
	    tmp++;
	    for(int i=1;i<=n;i++){
			if(a[i]!=b[i]){
				flag=1;
				break;
			}
	    }
	    if(flag==0){
	    	cout<<"YES";
	    	return 0;
		}
		if(tmp==l){
			cout<<"NO";
			return 0;
		}
	}
	return 0;
}
```
这是蒟蒻的第 $8$ 篇题解，支持一下孩子吧！

---

## 作者：_cpp (赞：0)

### 题目大意：
给你两个圆环，你它们其中一个是否可以通过旋转一定角度与另一个重合。
### 思路：
由于题目中说 $l \le 100 $ 所以可以考虑暴力求解。 每一次都将圆环 $A$ 往后旋转一位，再和圆环 $B$ 进行比较，一样输出 YES，如果旋转了 $l$ 次还没有和 $B$ 匹配的话，输出 NO。时间复杂度 $O(l ^ 2)$，可以通过此题。
### 代码：
```cpp
#include<bits/stdc++.h> 
using namespace std; 
int x,n,l;
bool a[110],b[110];
int main() 
{ 
    cin >> n >> l;
    for(int i = 1;i <= n;i++) cin >> x,a[x] = 1;
    for(int i = 1;i <= n;i++) cin >> x,b[x] = 1;
    for(int i = 1;i <= l;i++){
        int t = a[l - 1];
        int f = 0;
        for(int j = l - 1;j >= 1;j--) a[j] = a[j - 1];
        a[0] = t;  //进行旋转操作，将第一个暂时储存起来，放到最后
        for(int j = 0;j < l;j++)
            if(a[j] != b[j]){
                f = 1;
                break;
            }
        if(!f) return cout << "YES",0;
    }
    cout << "NO";
    return 0; 
}
```


---

