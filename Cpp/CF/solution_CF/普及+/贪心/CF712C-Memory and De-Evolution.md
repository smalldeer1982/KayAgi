# Memory and De-Evolution

## 题目描述

Memory 对物体，尤其是三角形的变化感兴趣。 他有一个边长为 $x$ 的等边三角形，他希望通过一些操作获得一个边长为 $y$ 的等边三角形。

他一次可以修改当前三角形一边的长度，修改后也应为合法的三角形。每次修改后，每一边的长度都应该是整数。

Memory 要获得边长 $y$ 的等边三角形，所需的最小修改次数是多少？

## 样例 #1

### 输入

```
6 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
8 5
```

### 输出

```
3
```

## 样例 #3

### 输入

```
22 4
```

### 输出

```
6
```

# 题解

## 作者：吴思诚 (赞：6)

# CF712C Memory and De-Evolution
[题目传送门](https://www.luogu.com.cn/problem/CF712C)

考虑倒着贪心，每次都要使得边长到极限。
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,t,a[4],m,i;
int main(){
	scanf("%d%d",&x,&y);
	a[1]=a[3]=a[2]=y;
	while(a[1]<x||a[2]<x||a[3]<x){
		t++;
		sort(a+1,a+4);
		a[1]=a[2]+a[3]-1;
	}
	printf("%d",t);
	return 0;
}
```


---

## 作者：sinsop90 (赞：1)

这道题给定两个等边三角形,在每次修改边后保证三条边仍然能构成三角形,求最小修改数使得一个三角形变成另一个三角形

我们假设 $m$ $＜$ $n$,将三条边排序后,找到最小的边进行修改

这时我们可以将修改分为两种情况:

1. 其余两条边的和减去$1$大于$n$

这时我们将最小的边赋值为$n$

2. 其余两条边的和减去$1$小于或等于$n$

这时我们将最小的边赋值为其余两条边的和减$1$即可

减$1$时因为两边之和大于第三边,而不是大于或等于

这时我们可以发现已经得出了最小操作的次数

因此有如下代码:

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,m,a[4],b[4],ans=0,k;
	scanf("%d%d",&n,&m);
	a[1] = a[2] = a[3] = m;//m<=n
	while(!(a[1]==n && a[2]==n && a[3]==n)){
		ans++;
		sort(a+1,a+1+3);//将3条边从小到大排序
		if(a[2]+a[3]-1>n){//上述第一种情况
			a[1] = n;
		}
		else{//上述第二种情况
			a[1] = a[2]+a[3]-1;
		}
	}
	cout<<ans<<endl;
}
```


---

## 作者：_Felix (赞：1)

看到题我第一反应就是while循环

但是我竟然想正着推，失败，卡了十几分钟

后来我回来看到第三组测试数据

想到倒推

但是没坚持

于是我又卡了很久

过会我又回来想

AC了。。。

这个故事告诉我们，要努力找规律~
```cpp
#include<bits/stdc++.h>//万能库
using namespace std;
int x,y;
int main()
{
	cin>>x>>y;//读入
	int cnt=2;//注意不是0
	int a,b,c;
	a=b=c=y;//前方倒推预警
	while(a<=x)
	{
		cnt++;
		c=b;
		b=a;
		a=a+c-1;//改变值，就是暴力的找规律
	}
	cout<<cnt<<endl;//输出
	return 0;
 } 
```
所以大家要坚持自己的想法哦

**By 你们最最阔耐的czy**

---

## 作者：lihanyang (赞：1)

# 贪心思想：从结束往开始推，每一次都要加到最大极限或直接到达原来的边。
## 从结束往开始推
```
1.其实只要从后往前倒推
2.推到相等就可以了
3.每次都要排序，加上得数
```
```cpp
#include<bits/stdc++.h>//万能头文件
#define ll long long//ll定义long long（偷懒）
using namespace std;
int main()
{
	ll ans=0;//答案
	ll x,y;
	cin>>x>>y;
	ll a[10];//数组可以sort
	a[1]=y;a[2]=y;a[3]=y;//初始化
	while(1)
	{
		if(a[1]==x&&a[2]==x&&a[3]==x) break;//跳出
		if(a[2]+a[3]-1<x)
		{
			a[1]=a[2]+a[3]-1;//
		}
		else a[1]=x;ans++;
		sort(a+1,a+4);//sort
	}
	cout<<ans<<endl;//输出
}
```

---

## 作者：lhjy666 (赞：1)

### 这题题意就是给定原正三角形的边长n，求将边长变成m的最小次数
### 你可以随意改变边长，但每个边长必须能构成三角形 
### 其实就是贪心：
### 只要将最短的边长变成当前最长可变成的边长就好了 
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll a[1000];
int main()
{
	ll n,m,t=0;
	scanf("%lld%lld",&n,&m);
	a[1]=m;
	a[2]=m;
	a[3]=m;
	while(1)
	{
		t++;
		ll k=min(a[1],min(a[2],a[3]));//取最小的 
		if(k==a[1])
		{
			if(a[2]+a[3]-1<=n)//如果大于n则变成n 
			{
				a[1]=a[2]+a[3]-1;
			}
			else
			{
				a[1]=n;
			}
		}
		else
		{
			if(k==a[2])
			{
				if(a[1]+a[3]-1<=n)
				{
					a[2]=a[1]+a[3]-1;
				}
				else
				{
					a[2]=n;
				}
			}
			else
			{
				if(a[2]+a[1]-1<=n)
				{
					a[3]=a[1]+a[2]-1;
				}
				else
				{
					a[3]=n;
				}
			}
		}
		if(a[1]==n&&a[2]==n&&a[3]==n)
		{
			printf("%lld",t);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：Fat_Fish (赞：0)

**题意：**	给定一个边长为 $x$ 的正三角形，让你求至少改变几次边的长度，才能使其成为一个边长为 $y$ 的正三角形。 (每次修改后的三角形必须合法）

**思路:** 对于此题，直接正推肯定不是最方便的，所以我们选择进行倒推。

**策略:** 假设该三角形的边长分别为 $a$ , $b$ , $c$ ,且 $ a \leq b \leq c$ ,则我们令 $a = c-b+1 $ ,一直推下去，直到推到目标值方可停止。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-'){
			f=-1;
		}
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}//日常快读
int x,y,a,b,c,cnt;
signed main(){
	x=read(),y=read();
	a=b=c=y;//从后往前推
	while(true){
		if(a==x&&b==x&&c==x){
			break;//达到目标值就退出
		}
		++cnt;//累加步数
		int tar=min(a,min(b,c));//找到最小值
		if(a==tar){
			a=min(x,b+c-1);
		}else if(b==tar){
			b=min(x,a+c-1);
		}else {
			c=min(x,a+b-1);
		}
	}
	printf("%d\n",cnt); //最后输出答案
	return 0;
} 
```


---

