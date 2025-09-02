# Chess Placing

## 题目描述

You are given a chessboard of size $ 1×n $ . It is guaranteed that  $ n $ is even. The chessboard is painted like this: "BWBW $ ... $ BW".

Some cells of the board are occupied by the chess pieces. Each cell contains no more than one chess piece. It is known that the total number of pieces equals to ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/e98ace5c1ad627053f6404505602ba90672a171b.png).

In one step you can move one of the pieces one cell to the left or to the right. You cannot move pieces beyond the borders of the board. You also cannot move pieces to the cells that are already occupied.

Your task is to place all the pieces in the cells of the same color using the minimum number of moves (all the pieces must occupy only the black cells or only the white cells after all the moves are made).

## 说明/提示

In the first example the only possible strategy is to move the piece at the position $ 6 $ to the position $ 5 $ and move the piece at the position $ 2 $ to the position $ 3 $ . Notice that if you decide to place the pieces in the white cells the minimum number of moves will be $ 3 $ .

In the second example the possible strategy is to move ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/4f3653422b6429c3f89311497c438fd20547c4f8.png) in 4 moves, then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/6c4181624e2b8f95750df668d534111d8ee2005d.png) in 3 moves, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/74a8630d5d683f941562dca49b5d40bcde2fe1ef.png) in 2 moves and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF985A/b97ec32af1cd5347877d0d15bd3de6cc845fde76.png) in 1 move.

## 样例 #1

### 输入

```
6
1 2 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10
1 2 3 4 5
```

### 输出

```
10
```

# 题解

## 作者：little_sun (赞：2)

~~这是一道水题~~

明显，最后可能的两种情况只有

$$1,3,5,...,n-1$$

和

$$2,4,6,...,n$$

两种

又因为题目要求最小值,所以从小到大排序,将对应位置上的数差的绝对值相加即可


代码:
```
#include<bits/stdc++.h>
using namespace std;
int a[101];
int odd[101]/*奇数*/,even[101]/*偶数*/;
int main()
{
	int n;
	scanf("%d",&n);
	int ans1=0,ans2=0;/*奇,偶情况下的解*/
    for(int i=1;i<=n/2;i++)
	{
        scanf("%d",&a[i]);
	}
	sort(a+1,a+n/2+1);
	for(int i=1;i<=n/2;i++)
	{
    	//算对应位
        odd[i]=i*2-1;
        even[i]=i*2;
        //更新答案
        ans1+=abs(odd[i]-a[i]);//记得绝对值
        ans2+=abs(even[i]-a[i]);
	}
    printf("%d",min(ans1,ans2));//最小值
    return 0;
}
```


---

## 作者：Yizhixiaoyun (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF985A)

## 题目分析

我们发现实际上有两种情况：

1. 棋子放在奇数。

2. 棋子放在偶数。

因此我们只需要分别算出两种可能性，最后使用 $\min$ 取最小即可。

## 贴上代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=60;
int n,a[maxn];
int ans,ans1,ans2;
int main(){
	cin>>n;n/=2; 
    for(register int i=1;i<=n;++i) cin>>a[i];
    sort(a+1,a+n+1);
    for(register int i=1;i<=n;++i) ans1+=abs(a[i]-i*2);
    for(register int i=1;i<=n;++i) ans2+=abs(a[i]-i*2+1);
    ans=min(ans1,ans2);
    cout<<ans;
}
```


---

## 作者：E1_de5truct0r (赞：1)

## 思路

这道题很明显是一道类似贪心的题。

为了使得棋子同色，我们肯定是**隔一个就有一个棋子**（这里用 Q 代替）。

![](https://cdn.luogu.com.cn/upload/image_hosting/4gseizhp.png)

### 我们发现有两种情况：

- 第一种情况就是棋子放在 $1,3,5,7,9$ 即奇数的位置上

- 第二种情况就是棋子放在 $2,4,6,8,10$ 即偶数的位置上

很显然，最优情况是第一个棋子放在第一个位置，第二个棋子对应第二个位置，以此类推。我们分别算一下两种情况的移动次数，然后取 ```min``` 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105];
int main()
{
	//读入，不做解释
	int n; cin>>n;
	for(int i=1;i<=n/2;i++) cin>>a[i];
	sort(a+1,a+1+n/2); //数据可能会出现大小不按顺序的情况，需要重新排序 
	int sum1,sum2; sum1=sum2=0; 
	for(int i=1;i<=n/2;i++)
	{
		int a1=2*i-1,a2=2*i; //a1 为这一位应在的奇数位（情况1），a2 为这一位应在的偶数位（情况2）
		sum1+=abs(a[i]-a1); //如果放在奇数位的移动次数 
		sum2+=abs(a[i]-a2); //如果放在偶数位的移动次数 
	}
	cout<<min(sum1,sum2)<<endl; //取 min 
	return 0;
}
```

谢谢阅读！

---

## 作者：GusyNight (赞：1)

**题意：**

**棋盘格是黑白相间的，**

**往上放棋子，**

**最终的棋子只能是在黑或者白上面，**

**所以只可能是**

```
1，3，5，7，9…
```
**或者**
``` 
2，4，6，8，10…
```
**并且为什么要先排好序那，**

**因为所有的棋子最后都会走到自己对应的**

**2*i上的偶数或者2*i-1上的奇数上，**

**我们这里减的是和i有关的，**

**所以要对应你如果i=2的位置上放到是6,**

**那6本来是移动到12上的，**

**在2上就会移动到4上了，**

**要的是对应，**

**每个人找到自己的位置才能保证移动到对应的位置上**

```cpp
#include<bits/stdc++.h>
#define Max 10009
using namespace std;
int main(){
	int Chess[Max],n,ans;
	cin>>n;
	for(int i=1;i<=n/2;i++){
		cin>>Chess[i];
	}
	int s1=0,s2=0;
	sort(Chess+1,Chess+1+n/2);
	for(int i=1;i<=n/2;i++){
		s1=s1+abs(Chess[i]-(2*i-1));
		s2=s2+abs(Chess[i]-2*i);
	}
	ans=min(s1,s2);
	cout<<ans;
	exit(0);
}
```


---

## 作者：Jerry_heng (赞：0)

（一）

每个棋子的所在格子颜色相同，那么就需要分类讨论都在黑色上或白色上。


黑色： $1,3,5,\cdots,n-1$。

白色： $2,4,6,\cdots,n$。

因为棋子不可能跨过另一个，所以棋子从左到右分别与格子从左到右对应。

也就是第一个棋子对应第一个格子，等等。

由于位置确定，那么每个棋子的对应位置也就确定了。

我们只需要将所有棋子位置从小到大排序，然后通过求对应距离即可。

（二）

AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans1,ans2,a[51];
int main(){
	cin>>n;
	for(int i=1;i<=n/2;i++)cin>>a[i];
	sort(a+1,a+n/2+1);
	for(int i=1;i<=n/2;i++){
                 //abs是用来求绝对值的
		ans1+=abs(a[i]-i*2); //白
		ans2+=abs(a[i]-(i*2-1)); //黑
	}
	cout<<min(ans1,ans2); //选两种方式中较小的
	return 0;
} 
```


---

## 作者：olegekei (赞：0)

考虑一个问题：每个棋子只能向相邻且没有棋子的格子移动。

这也就意味着每个棋子的相对位置总是一定的。即如果棋子 $1$ 在棋子 $2$ 的左侧，那么他一定永远都在棋子 $2$ 的左侧。

接下来考虑每个棋子所在的格子颜色一样的问题：

黑格子和白格子的数量都是 $n$，棋子的数量也都是 $n$，那么最终状态无非只有两种情况：所有棋子在黑格子上和所有棋子在白格子上。所有黑格子和白格子的位置是一定的，棋子的相对位置也是一定的，那么我们可以分类讨论最终状态是黑格子和白格子的情况，确定每个棋子该在哪个格子上。

而每个棋子移动到对应位置的次数是两者的距离。最后在两种情况中取最小值即可。
```cpp
#include<iostream>
#include<algorithm> 
using namespace std;
int n,m;
int a[111];
int main(){
cin>>n;
m=n/2;
for(int i=1;i<=m;i++)cin>>a[i];
sort(a+1,a+m+1);
int black=1,white=2;
int ans1=0,ans2=0;
for(int i=1;i<=m;i++){
    ans1+=abs(a[i]-black);
    ans2+=abs(a[i]-white);
    black+=2;white+=2;
}
cout<<min(ans1,ans2);
return 0;
}
```

---

## 作者：OdtreePrince (赞：0)

# -排序-

本题先把输入的数据排序，然后分别用sum1,sum2统计把全部棋子移到黑，白两处的最短总距离，比较并输出。

HEIHEI , yeah！

代码不长，楼上多多关照！

~~~
#include<bits/stdc++.h>
using namespace std;
int p[55],n,sum1,sum2;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n/2;i++){
        scanf("%d",&p[i]);
    }
    sort(p+1,p+n/2+1);
    for(int i=1;i<=n/2;i++){
        sum1+=abs(p[i]-i*2+1);
    }
    for(int i=1;i<=n/2;i++){
        sum2+=abs(p[i]-i*2);
    }
    cout<<min(sum1,sum2);
    return 0;
}
~~~

---

