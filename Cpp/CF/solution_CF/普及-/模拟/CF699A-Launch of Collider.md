# Launch of Collider

## 题目描述

There will be a launch of a new, powerful and unusual collider very soon, which located along a straight line. $ n $ particles will be launched inside it. All of them are located in a straight line and there can not be two or more particles located in the same point. The coordinates of the particles coincide with the distance in meters from the center of the collider, $ x_{i} $ is the coordinate of the $ i $ -th particle and its position in the collider at the same time. All coordinates of particle positions are even integers.

You know the direction of each particle movement — it will move to the right or to the left after the collider's launch start. All particles begin to move simultaneously at the time of the collider's launch start. Each particle will move straight to the left or straight to the right with the constant speed of $ 1 $ meter per microsecond. The collider is big enough so particles can not leave it in the foreseeable time.

Write the program which finds the moment of the first collision of any two particles of the collider. In other words, find the number of microseconds before the first moment when any two particles are at the same point.

## 说明/提示

In the first sample case the first explosion will happen in $ 1 $ microsecond because the particles number $ 1 $ and $ 2 $ will simultaneously be at the same point with the coordinate $ 3 $ .

In the second sample case there will be no explosion because there are no particles which will simultaneously be at the same point.

## 样例 #1

### 输入

```
4
RLRL
2 4 6 10
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
LLR
40 50 60
```

### 输出

```
-1
```

# 题解

## 作者：pandaSTT (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/CF699A)

## 前言

这道题其实根本不用像第二篇题解一样排序，题目中说了

	It is guaranteed that the coordinates of particles are given in the increasing order.
###### 翻译：保证粒子的坐标以递增的顺序给出……

所以时间复杂度只需要 $ O(n) $ 即可

## 思路

首先分析题目，**求相遇的最小时间**。如果要相遇，只有两种情况：

>	1. 同向：两个粒子朝同一方向前行，需要满足两个粒子面朝同一方向且在后的粒子的速度必须大于在前的粒子的速度才能相遇，而本题中明确表示了所有粒子的速度均为 1，这种情况排除。


>
>	2. 相向：两个粒子朝相反的方向前行，需要满足两个粒子面朝不同方向，此题可以满足。

综上，我们只需要查找同向的两个粒子相遇所需要的时间。

求相遇时间 $ t $,则需要用到公式 $ t=\frac{s_1-s_2}{v_1+v_2} $，而题目保证粒子的坐标以递增的顺序给出，所以只需要求 $ min \sum_{i=1}^n (arr[i].position-arr[i-1].position)/2 \ $ 就行了。

## 代码

```cpp
  #include <bits/stdc++.h>
  #define INF 0x3f3f3f3f
  using namespace std;
  int read(){//加个快读快一丢丢 qwq
      int k=0,x=0; 
      char s=getchar(); 
      while(s<'0'||s>'9'){
          k|=s=='-'; s=getchar(); 
      }
      while(s>='0'&&s<='9'){ 
          x=(x<<3)+(x<<1)+(s^48); 
          s=getchar(); 
      }
      return k?-x:x; 
  }
  int n,ans=INF;//答案求最小值，所以初始值应设为极大值，如: 0x3f3f3f3f
  string s;
  struct nobe{
      int position;
      char direction;//其实就是位置与方向的英文，这样写显得我很有文化 qwq
  }arr[200005];
  int main(){
      n=read();
      cin>>s;
      for(int i=1;i<=n;i++){
          arr[i].position=read();
          arr[i].direction=s[i-1];//string 类型的下标是从 0 开始的，所以第 i 个粒子的方向应该为字符串中下表为 i-1 的字符
          if(i!=1){
              if(arr[i].direction=='L'&&arr[i-1].direction=='R'){//如果这两个粒子是相向而行，那么就会有相遇
                  ans=min(ans,(arr[i].position-arr[i-1].position)/2);//套用思路里的公式
              }
          }
      }
      if(ans==INF){//没有能相遇的两个粒子就把答案设为 -1
          ans=-1;
      }
      cout<<ans;
      return 0;
  }
```


---

## 作者：开始新的记忆 (赞：2)

题意没啥好讲的，就是n个点，告诉你每个点的朝向，给你每个点的坐标，每个点在单位时间内都会运动单位长度，问你最少什么时间会有点碰撞。

不难发现，只有当形如RL时才会碰撞，其余则不可能

```
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],ans=0x7fffffff;
string s;

int main()
{	cin>>n>>s;
	for(int i=0;i<n;++i)
		cin>>a[i];
	for(int i=1;i<n;++i)
		if(s[i-1]=='R' && s[i]=='L')
			ans=min(ans,abs(a[i-1]-a[i])/2);
	if(ans==0x7fffffff)
		cout<<-1<<endl;
	else 
		cout<<ans<<endl;
    return 0;
}
```


---

## 作者：peppaking8 (赞：1)

### 思路

首先，很容易想到的是，两个东西**能够相遇**的充要条件是：在左边的东西向右走，也即方向为 ```R```；在右边的东西向左走，也即方向为 ```L```。

所以我们可以分别枚举每两个点相遇的时间，然后取最小值即可。如果这两个东西 $a_i,a_j$ 可以相遇，那么相遇时间就是 $\dfrac{|a_i-a_j|}{2}$。

但是，因为 $n\le 2\times 10^5$，所以这样的思路肯定**超时**了。

考虑优化，我们将这 $n$ 个数从左到右排序，对于每个方向是 ```L``` 的东西，可以找出前面的东西中方向是 ```R``` 且最靠右的东西，他们两个的距离就可以统计答案。如果我们**预处理**出所需寻找的东西，那么时间复杂度降为了 $O(n\log n)$，可以通过这道题。瓶颈是排序的过程。

$$\text{Talk is cheap, show you the code.}$$

### Code

```
#include<bits/stdc++.h>
#define INF 2147483647
using namespace std;
const int N=200005;
int n;
struct Node{
	int pos;//处在的位置
	char way;//方向，存储L或者R
}a[N];//将每个东西的信息捆成一个结构体。
char readchar(){
	char xx=0;
	while(xx!='L'&&xx!='R') xx=getchar();
	return xx;
}
bool cmp(Node k1,Node k2){//排序函数
	if(k1.pos!=k2.pos) return k1.pos<k2.pos;
    //如果两个东西的位置不同，靠左的在前面
    //如果相同，则方向是L的排在前面
	if(k1.way=='L') return true;
	if(k2.way=='L') return false;
	return true;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) a[i].way=readchar();
	for(int i=1;i<=n;i++) scanf("%d",&a[i].pos);
	sort(a+1,a+n+1,cmp);//排序
	int Max=-1;//Max代表前面所有方向为R的最靠右的坐标
	int ans=INF;//ans记录答案的最小值
	for(int i=1;i<=n;i++){
		if(a[i].way=='R') Max=max(Max,a[i].pos);
        //如果是R，则更新Max
		else{//如果是L，则更新答案ans
			if(Max==-1) continue;//还未出现R，跳过
			ans=min(ans,a[i].pos-Max);//记录
		}
	} 
	if(ans==INF){//如果没有出现，输出-1
		printf("-1\n");
	}
	else printf("%d\n",ans/2);//否则输出答案
    return 0;
}
```

写一篇题解不容易，看完记得点个赞哦~

---

## 作者：pengzy___ (赞：0)

### 题意：
在一条直线上，有一些粒子，它们分别为左右方向， 若能相撞则输出相撞时间，否则输出 -1 。

### 思路：
按照题意可以分为两种情况：

- 粒子同向和反向：永远不可能相撞，直接输出 -1 ，因为直线的长度是无限的，而粒子的速度是相同的。

- 粒子相向：枚举所有的情况，取最小值。

如果两个粒子是相向的，则速度是 $\sum_{i=0}^{n}( a_{i}-a_{i-1}/2)$ 取最小值，因为所有的数据都是单调上升的。

---

## 作者：pengzy___ (赞：0)

### 题意：

在一条直线上，有一些粒子，它们分别为左右方向， 若能相撞则输出相撞时间，否则输出 -1 。

### 思路：

按照题意可以分为两种情况：

- 粒子同向和反向：永远不可能相撞，直接输出 -1 ，因为直线的长度是无限的，而粒子的速度是相同的。

- 粒子相向：枚举所有的情况，取最小值。

如果两个粒子是相向的，则速度是 $\sum_{i=0}^{n} \left ( a_{i}-a_{i-1}/2 \right )$ 取最小值，因为所有的数据都是单调上升的。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
char s[MAXN];
int n,a[MAXN],ans=0x3f3f3f3f;
int main() 
{
    cin>>n>>s;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=2;i<=n;i++)
        if(s[i-1]=='R'&&s[i]=='L')
            ans=min(ans,(a[i]-a[i-1])/2);
    cout<<(ans==0x3f3f3f3f)?-1:ans;
    return 0;
}
```


---

## 作者：ForeverCC (赞：0)

因为运动的速度相同，所以通向、反向而行都是不能相遇的。只有相向而行可以。

所以只要判断两个方向是否为相向，计算时间，跟新最小值即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],ans=1e9;
string s;
int main() {
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
		if(s[i-1]=='R'&&s[i]=='L')//只有这种情况才相向
			ans=min(ans,abs(a[i-1]-a[i])/2);
	if(ans==1e9)puts("-1");
	else printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 辆车在一条数轴上，第 $i$ 辆车在 $a_i$ 上，每辆车要么向左，要么向右。开始，它们以 $1$ 个单位每秒的速度在行驶。问你第一次撞车发生在第几秒的时候，或者根本不会撞车。

**数据范围：$1\leqslant n\leqslant 2\times 10^5,0\leqslant x_i\leqslant x_{i+1}\leqslant 10^9$。**
## Solution
我们可以很容易的发现，当且仅当相邻的两个车，左边的向右开，右边的向左开时会发生撞车。所以，枚举这样的两个车之间的距离并取最小值 $dis$，答案就是 $\dfrac{dis}{2}$。
## Code
```cpp
#include <cstdio>
#include <algorithm>
using namespace std;

char s[200007];
int n, a[200007], ans = 0x3f3f3f3f;

int main() {
	scanf("%d%s", &n, s + 1);
	for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for(int i = 2; i <= n; ++i)
		if(s[i - 1] == 'R' && s[i] == 'L')	ans = min(ans, (a[i] - a[i - 1]) / 2);
	printf("%d", (ans == 0x3f3f3f3f) ? -1 : ans);
}
```

---

## 作者：　　　吾皇 (赞：0)

### 拿到题后我们不妨先思考，因为每个东西的速度一样，所以如果他们可以相撞那么一定是一个向右，一个向左。明显的，如果向右走的在向左走的右边，他们就不可能相撞显然，只有R在L的左边才能追上，所以还有啥好说的呢（刚开始没发现x是顺序的，坑啊） 那么代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
int a1[200000],n,ans=1<<30;string s;//先给ans定一个很大的值，后面只要看值有没有被改变就知道可不可以了
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++) cin>>a1[i];
	for(int i=1;i<n;i++)
		if(s[i-1]=='R'&&s[i]=='L') ans=min(ans,(a1[i+1]-a1[i])/2);//如果两个相邻的东西分别向右和向左，那么答案就是原答案和他们相撞的时间的最小值（只考虑相邻的是因为相邻的两个满足条件的最小值肯定小于不相邻的最小值）
	if(ans==1<<30) cout<<"-1";
	else cout<<ans;
}
```


---

## 作者：灵光一闪 (赞：0)

emming……  
这题真心没啥好讲的，直接上代码

```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>
#include<string>
using namespace std;
int a[200005];
int l[200005],r[200005];//分类储存，以后有用
int ltep,rtep;
int n;
string s;
void ok(int i)
{
    cout<<i<<endl;
    exit(0);
}
int main()
{
    cin>>n;
    cin>>s;
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        if(s[i]=='L')
            l[ltep++]=a[i];
        else
            r[rtep++]=a[i];
    }
    for(int i=s.find("R");i<s.size();i++)//能不能撞上
        if(s[i]=='L')
            goto go;
    puts("-1");
    return 0;
go:
    int ans=2e9;//定大一点
    for(int i=0;i<rtep;i++)
    {
        for(int j=0;j<ltep;j++)
        {
            if(l[j]>r[i])
            {
                ans=min((l[j]-r[i])/2,ans);
                //要除2的鸭，因为是两个一起跑
                break;
            }
        }
    }
    cout<<ans;//输出
    return 0;
}
```

---

## 作者：Beep_Monkey (赞：0)

因为速度都一样，所以只有两个玩意反向的时候才会相撞。

所以只要求出两个反向的，距离最近的两个点的相遇时间即可。

## 上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],ans=1e9;
char s[200005];
int main(){
	scanf("%d%s",&n,s);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=1;i<n;i++)
		if(s[i-1]=='R' && s[i]=='L')//如果它们两个会相撞 
			ans=min(ans,abs(a[i-1]-a[i])/2);//更新答案 
	if(ans==1e9) printf("-1\n");
	else printf("%d",ans);
    return 0;
}
```


---

