# The Fair Nut and Elevator

## 题目描述

The Fair Nut lives in $ n $ story house. $ a_i $ people live on the $ i $ -th floor of the house. Every person uses elevator twice a day: to get from the floor where he/she lives to the ground (first) floor and to get from the first floor to the floor where he/she lives, when he/she comes back home in the evening.

It was decided that elevator, when it is not used, will stay on the $ x $ -th floor, but $ x $ hasn't been chosen yet. When a person needs to get from floor $ a $ to floor $ b $ , elevator follows the simple algorithm:

- Moves from the $ x $ -th floor (initially it stays on the $ x $ -th floor) to the $ a $ -th and takes the passenger.
- Moves from the $ a $ -th floor to the $ b $ -th floor and lets out the passenger (if $ a $ equals $ b $ , elevator just opens and closes the doors, but still comes to the floor from the $ x $ -th floor).
- Moves from the $ b $ -th floor back to the $ x $ -th.

 The elevator never transposes more than one person and always goes back to the floor $ x $ before transposing a next passenger. The elevator spends one unit of electricity to move between neighboring floors. So moving from the $ a $ -th floor to the $ b $ -th floor requires $ |a - b| $ units of electricity.Your task is to help Nut to find the minimum number of electricity units, that it would be enough for one day, by choosing an optimal the $ x $ -th floor. Don't forget than elevator initially stays on the $ x $ -th floor.

## 说明/提示

In the first example, the answer can be achieved by choosing the second floor as the $ x $ -th floor. Each person from the second floor (there are two of them) would spend $ 4 $ units of electricity per day ( $ 2 $ to get down and $ 2 $ to get up), and one person from the third would spend $ 8 $ units of electricity per day ( $ 4 $ to get down and $ 4 $ to get up). $ 4 \cdot 2 + 8 \cdot 1 = 16 $ .

In the second example, the answer can be achieved by choosing the first floor as the $ x $ -th floor.

## 样例 #1

### 输入

```
3
0 2 1
```

### 输出

```
16```

## 样例 #2

### 输入

```
2
1 1
```

### 输出

```
4```

# 题解

## 作者：RealityCreator (赞：3)

我们这么想：
当电梯在b层，人在a层时

若a $\leq$ b，则电梯需上到b层，再到1层，再回b层，从1楼接人也相同，我们发现电梯走了2*b层

若a>b， 则电梯先到b，再到1，再到a，电梯走了2a层，去1楼接人时层数相同

不难发现，电梯对于每一个人来讲，要走4max(a,b)层

所以b越小越好

### 所以将其放在1层是最好的选择

### 总走的层数即为每个人所在的那一层到第一层的距离的四倍

附上代码：
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	int a[102];
	int ans=0;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		ans+=a[i]*(i-1)*4;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lhjy666 (赞：2)

```cpp
#include<bits/stdc++.h>
#define ll long long 
#define MOD 1000000007
using namespace std;
int a[10005];
int minn=99999999;
int main()
{
	int n;
	scanf("%d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for (int i=1;i<=n;i++)
	{
		int t=0;
		for (int j=1;j<=n;j++)
		{
			t+=a[j]*(abs(j-i)+j+i-2)*2;
		}
		if(t<minn) minn=t; 
	}
	printf("%d",minn);
	return 0;
}
```

---

## 作者：昊月星辰 (赞：2)

##  暴力水题一道
逐层枚举输出总和即可。

$AC\ Code$

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans;//记录总和
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int u;
        cin>>u;//输入层数
        ans+=u*i*4;//总和即为他所在的一层距离第一层的距离的4倍
    }
    cout<<ans;//输出答案
    return 0;
}
```


---

## 作者：reclusive (赞：1)

# 题意分析：

有一个电梯，然后有 $n$ 层楼，每层楼上有 $a_i$ 个人。

每次电梯只能运一个人去 1 楼，运完后电梯又会回到当前楼层。

然后问你电梯总共会经过多少楼层。

# 解题思路：

这道题的思路就是模拟电梯运行，然后推算经过多少楼就好了。

首先我们知道，每一层有 $a_i$ 个人。

早上他们要下到 1 楼，电梯所经过的楼层为：

```cpp
(i-1)*a[i]*2
```
然后我们通过观察可以知道，晚上电梯所运行的楼层数和早上是相同的。

所以我们将早上的楼层数算出来后，在乘以 2 就好了。

# AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101];
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];//简单的输入 
	}
	int ans=0; 
	for(int i=1;i<=n;i++)
	{
		ans=ans+(i-1)*a[i]*2;//早上的楼层数 
	}
	cout<<ans*2;//输出结果 ，要乘以2 
	return 0;//完结撒花 
}
```


---

## 作者：xyf007 (赞：1)

### 暴力枚举每一层楼的结果即可
~~虽然rxj大佬说只要枚举第一层~~
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,a[1001];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	int ans=2e9;
	for(int i=1;i<=n;i++)
	{
		int sum=0;
		for(int j=1;j<=n;j++)
		{
			sum+=2*a[j]*(abs(j-i)+j+i-2);
		}
		if(sum<ans)
		{
			ans=sum;
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：fuzhelin1984 (赞：0)

## 题意

虽然题目中说电梯初始可以在任意位置，但我们可以发现，接送每个人时都需要回到或从一层开始，而且在完成一次接送后还必须回到初始位置，所以易知电梯放在第一层能使运行楼层最少。

分析题目中的接送操作，容易得出对每个人，电梯都要运行四倍于这个人楼层的层数。所以代码也很简单，在读入时计算出结果即可。
     
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
inline int _read()
{
    register int x=0,f=0;register char ch=getchar();
    while(ch<'0'||ch>'9')f|=ch=='-',ch=getchar();
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return f?-x:x;
}
inline void read(int& t)
{
	t=_read();
}
template<typename ...Arg> inline void read(int& t, Arg& ...args)
{
	t = _read();
	read(args...);
}
signed main()
{
	int n,syy,ans = 0;
	read(n);
	for(int i = 1;i <= n;++i) 
	{
		read(syy);
		ans += (i-1)*4*syy;
	}
	return cout<<ans,0;
}

```


---

## 作者：翼德天尊 (赞：0)

## STEP 1 浅谈解法

仔细思考题面，我们来尝试推一下式子。

想到不知道电梯的初始位置，我们可以分类讨论。设电梯初始在第 $y$ 层，该乘客在第 $x$ 层，则：

1. $x\le y$

则我们的电梯需要先下到乘客层，再下到一层，然后回到第 $y$ 层；回来的时候同理。则需要走 $2(y+y)=4y$ 层。

2. $x>y$

则我们的电梯需要先上到乘客层，再下到一层，然后回到电梯层；回来的时候同理。则需要走 $2(x+x)=4x$ 层。

综上所述，答案应为 $4(x,y)_{max}$ 层。

所以要使答案最小，就需要使 $y$ 尽可能的小，所以我们就让 $y=1$ 即可。答案即为 $4x$。

## STEP 2 AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,ans;
int read(){//显得累赘的快读
	int w=0;
	char c=getchar();
	while (c>'9'||c<'0'){
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w;
}
int main(){
	n=read();
	for (int i=0;i<n;i++) a=read(),ans+=4*i*a;//公式推出
	printf("%d\n",ans);
	return 0;
}
```

✿✿ヽ(°▽°)ノ✿

---

## 作者：末置lzy (赞：0)

# CF1084A 【The Fair Nut and Elevator】题解
题目传送门：[The Fair Nut and Elevator](https://www.luogu.com.cn/problem/CF1084A)

**题目分析**

看题，就是让你将不同层数的人都拉倒一楼再拉回去就行了，并且输入第几个数就是第几层楼，所以核心代码就这：

```cpp
a[i]*i*4;
```
表示每层楼人数每次要算的次数，i主要因为我的循环从0开始的，a[i]就是每层的人数，所以

# AC CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100000];
int main()
{
    long long n,ans=0;//十年OI一场空，不开long long见祖宗qwq
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        ans+=a[i]*i*4;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：CobaltChloride (赞：0)

```
#include<bits/stdc++.h>
using namespace std;
long long n,i,j,a[101],ans=999999999999,ans1;//ans存储最小值
int main(){
	cin>>n;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n;i++){
		ans1=0;
		for(j=1;j<=n;j++) ans1+=4LL*a[j]*(max(i,j)-1);//一个个暴力枚举
		if(ans>ans1) ans=ans1;//更新
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：shenmadongdong (赞：0)

```
var n,s,i,j,min:longint;
    a:array [1..100] of longint;
begin
  read(n);
  for i:=1 to n do read(a[i]);
  for i:=1 to n do
    begin
      s:=0;
      for j:=2 to n do s:=s+a[j]*(j-1)+a[j]*abs(j-i)+a[j]*(i-1);
      s:=s*2;
      if (s<min)or(min=0) then min:=s;
    end;
  writeln(min);
end.
```

---

