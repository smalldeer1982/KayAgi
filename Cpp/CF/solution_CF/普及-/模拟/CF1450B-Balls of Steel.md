# Balls of Steel

## 题目描述

You have $ n $ distinct points $ (x_1, y_1),\ldots,(x_n,y_n) $ on the plane and a non-negative integer parameter $ k $ . Each point is a microscopic steel ball and $ k $ is the attract power of a ball when it's charged. The attract power is the same for all balls.

In one operation, you can select a ball $ i $ to charge it. Once charged, all balls with Manhattan distance at most $ k $ from ball $ i $ move to the position of ball $ i $ . Many balls may have the same coordinate after an operation.

More formally, for all balls $ j $ such that $ |x_i - x_j| + |y_i - y_j| \le k $ , we assign $ x_j:=x_i $ and $ y_j:=y_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1450B/bd476820b8f47c8050ef448d8375a731892e001a.png) An example of an operation. After charging the ball in the center, two other balls move to its position. On the right side, the red dot in the center is the common position of those balls. Your task is to find the minimum number of operations to move all balls to the same position, or report that this is impossible.

## 说明/提示

In the first test case, there are three balls at $ (0, 0) $ , $ (3, 3) $ , and $ (1, 1) $ and the attract power is $ 2 $ . It is possible to move two balls together with one operation, but not all three balls together with any number of operations.

In the second test case, there are three balls at $ (6, 7) $ , $ (8, 8) $ , and $ (6, 9) $ and the attract power is $ 3 $ . If we charge any ball, the other two will move to the same position, so we only require one operation.

In the third test case, there are four balls at $ (0, 0) $ , $ (0, 1) $ , $ (0, 2) $ , and $ (0, 3) $ , and the attract power is $ 1 $ . We can show that it is impossible to move all balls to the same position with a sequence of operations.

## 样例 #1

### 输入

```
3
3 2
0 0
3 3
1 1
3 3
6 7
8 8
6 9
4 1
0 0
0 1
0 2
0 3```

### 输出

```
-1
1
-1```

# 题解

## 作者：dead_X (赞：3)

## 思路
怎么还是沙雕题啊（恼）

考虑答案显然只能是 $-1$ 和 $1$。

**证明**:

* 如果答案等于 $t(t\geq 2)$，显然我们可以拆分成前 $t-1$ 步和最后一步。
* 假设第 $t-1$ 步对点 $A$ 进行操作。
* 如果第 $t$ 步对点 $A$ 进行操作，显然什么也不会发生，因为符合的点已经被合并了。
* 如果第 $t$ 补不对点 $A$ 进行操作，显然点 $A$ 并不会被合并，因为剩下的点和 $A$ 的哈密顿距离必然大于 $k$。

因此我们只要判断一下一步能不能完成，由于数据范围很小直接 $O(Tn^2)$ 搞定。
## 代码
```
#include<bits/stdc++.h>
#define mp make_pair
#define pi pair<int,int>
#define pb push_back
//#define int long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int x[1003],y[1003];
signed main()
{
	int T=read();
	while(T--)
	{
		int n=read(),k=read();
		for(int i=1; i<=n; i++) x[i]=read(),y[i]=read();
		bool f=0;
		for(int i=1; i<=n; i++)
		{
			int mx=0;
			for(int j=1; j<=n; j++) if(i!=j) mx=max(mx,abs(x[i]-x[j])+abs(y[i]-y[j]));
			if(mx<=k)
			{
				f=1;
				break;
			}
		}
		if(f) puts("1"); else puts("-1");
	}
	return 0;
}


```

---

## 作者：Allanljx (赞：0)

## 思路
这题的答案只能是$1$或$-1$。如果你的其中一个点可以吸完，输出$1$，都吸不完的话，必定会有遗漏，输出$-1$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
struct point//结构体
{
    int x,y;
}p[250];
int main()
{
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        for(int i=1;i<=n;i++)
        {
            cin>>p[i].x>>p[i].y;
        }
        bool flag=false;
	    int ans=-1;//初始化
	    for(int i=1;i<=n;i++)
	    {
	        flag=false;
			for(int j=1;j<=n;j++)
			{
	            if(abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y)>k)//曼哈顿距离
	            {
	                flag=true;
	                break;
	            }
	        }
	        if(!flag)//可以吸完
	        {
	            ans=1;
	            break;
	        }
	    }
	    cout<<ans<<endl;
    }
    return 0;
}
```


---

## 作者：Forever1507 (赞：0)

# [传送门](https://www.luogu.com.cn/problem/CF1450B)

~~有点恶心~~

非常明显，此题答案要么是$1$,要么是$-1$,因为如果你的其中一个点可以吸完，那么其他点可不可以就不重要了，都吸不完的话，必定会有遗漏。

坑点：

必须一个个的判断，不然可能经过中转到达。

这样的话代码就很简单：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{//不会二元组，结构体挺香的
	int x,y;
}dian[105];
int Get(node a,node b){//曼哈顿距离
	return abs(a.x-b.x)+abs(a.y-b.y);
}
int t,n,k;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		bool flag=false;
		cin>>n>>k;
		for(int j=1;j<=n;j++){
			cin>>dian[j].x>>dian[j].y;
		}
		for(int j=1;j<=n;j++){
			int cnt=0;
			for(int q=1;q<=n;q++){
					if(Get(dian[j],dian[q])<=k){
						cnt++;//累加
					}	
			}
			if(cnt==n){
				cout<<1<<endl;
				flag=1;
				break;
			}
		}
		if(flag)
		continue;
		else
		cout<<-1<<endl;
	}
	return 0;
}
```


---

## 作者：zmza (赞：0)

首先，这题答案只能是-1或1。

为什么呢？因为如果没有一个点能将所有点都移动在一起，那么一定有两个点的曼哈顿距离大于$k$。所以没有办法移动在一起，输出-1。

如果可以的话，那么最少的次数就是一次性都移动在一起。所以输出1。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
pair<int,int>a[105];
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,k;
		scanf("%d%d",&n,&k);
		for(int i = 1; i <= n; i++)
		{
			scanf("%d%d",&a[i].first,&a[i].second);
		}
		bool flag = 0;
		for(int i = 1; i <= n; i++)
		{
			int sum = 0;
			for(int j = 1; j <= n; j++)
			{
				if(j == i)
				{
					continue;
				}
				int ans = abs(a[i].first - a[j].first) + abs(a[i].second - a[j].second);
				if(ans <= k)
				{
					sum++;
				}
			}
			if(sum == n - 1)
			{
				puts("1");
				flag = 1;
				break;
			}
		}
		if(flag == 0)
		{
			puts("-1");
		}
	}
	return 0;
}
```


---

