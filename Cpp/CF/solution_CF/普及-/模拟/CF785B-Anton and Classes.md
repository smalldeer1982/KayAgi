# Anton and Classes

## 题目描述

Anton很喜欢下棋，同时又很喜欢编程。难怪，他会想去参加棋艺班和编程班！

一共有n个棋艺班，m个编程班。第i个棋艺班的时间用$(l_{1,i},r_{1,i})$表示，第i个编程班的时间用$(l_{2,i},r_{2,i})$表示。

Anton需要在全部的棋艺班和编程班中间恰好各选一个。他想要在两个班之间有休息的时间，所以对于所有可能的选择，他希望两个时间段的距离（即他的休息时间）最大。

两个时间段$(l_1,r_1)$和$(l_2,r_2)$的距离是这样定义的：对于$l_1\le i\le r_1$，$l_2\le j\le r_2$，距离就是$|i-j|$的最小值。如果两个时间段相交，那么他们的距离当然就是$0$。

Anton很想知道，他的休息时间最大是多少。帮帮他解决这个问题吧！

## 样例 #1

### 输入

```
3
1 5
2 6
2 3
2
2 4
6 8
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3
1 5
2 6
3 7
2
2 4
1 4
```

### 输出

```
0
```

# 题解

## 作者：Luo_gu_ykc (赞：1)

~~一道大水题，竟然写了半小时~~

## 题目大意

有 $n$ 个编程班，和 $m$ 个棋艺班，告诉你每个班的上下课的时间，你需要在两个班中各选一个班，以达到休息时间最大。

## 思路

要不就是先上编程班，再上棋艺班，要不就是先上棋艺班，再上编程班，所以分类讨论。

### 第一种

找到最早下课的编程班，然后再找最晚上课的棋艺班即可。

### 第二种

同样，找到最早下课的棋艺班，然后再找最晚上课的编程班即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m, l, r, maxi = INT_MIN, maxx = INT_MIN, mini = INT_MAX, minn = INT_MAX; // INT_MAX, INT_MIN, 分别指的是 int 里的最大值和 int 里的最小值
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++){
		cin >> l >> r;
		maxi = max(maxi, l); // 编程班最晚的上课时间
		mini = min(mini, r); // 编程班最早的下课时间
	}
	cin >> m;
	for(int i = 1; i <= m; i++){
		cin >> l >> r;
		maxx = max(maxx, l); // 棋艺班最晚的上课时间
		minn = min(minn, r); // 棋艺班最早的下课时间
	}
	cout << max(max(maxx - mini, maxi - minn), 0); // 特判， 万一没有下课时间, 答案为负数， 会输出 0
	return 0;
}
```

---

## 作者：DPseud (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF785B)

# 题意

即在棋艺班与编程班之间各选一个让时间差距最大。

# 思路

想让时间差距最大，只有两种情况：要么是棋艺班的开头减编程班的结尾，要么是编程班的开头减棋艺班的结尾。我们可以将四个数组各从小到大排序一遍，这样 $a[0]$ 就相当于最小值，$a[n-1]$ 就相当于最大值，判断两种情况哪个大，此外，还需要特判小于 0 的情况，如果小于 0，那么就输出 0 即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    
    static int n,m,a[222222],b[222222],c[222222],d[222222];//四个数组容量加起来将近90万，需要用static，否则会RE
    cin>>n;
    for(int i=0;i<n;i++)scanf("%d %d",&a[i],&c[i]);//用cin会TLE
    cin>>m;
    for(int i=0;i<m;i++)scanf("%d %d",&b[i],&d[i]);
    sort(a,a+n),sort(c,c+n);//全部从小到大排序一遍
    sort(b,b+m),sort(d,d+m);
    if(max(b[m-1]-c[0],a[n-1]-d[0])>0)cout<<max(b[m-1]-c[0],a[n-1]-d[0]);//正常情况
    else cout<<0;//特殊情况
    return 0;
}
```


---

## 作者：lrmlrm_ (赞：0)

# 题意

  在 $ n $ 个棋艺班和 $ m $ 个编程班中各选一个 ， 让两个班之间的休息时间最大 。
  
# 思路

  不难发现 ， 只会有两种情况 ：
        
$ \ \ \ \ \     1 . $ 先上棋艺班 ， 再上编程班 ：
   
$ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $ 找到最早下课的棋艺班 ， 再找到最晚上课的编程班 ， 两个时间中间的间隔就是这种情况的最长休息时间 。
   
$ \ \ \ \ \     2 . $ 再上棋艺班 ， 先上编程班 ：
   
$ \ \ \ \ \ \ \ \ \ \ \ \ \ \ $ 找到最早下课的编程班 ， 再找到最晚上课的棋艺班 ， 两个时间中间的间隔就是这种情况的最长休息时间 。

**注意 ： 有可能没得休息 ， 上一节课还没下就上课 ， 需要输出 $ 0 $ 。**

# 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
int n,m,mi1=2147483647,ma1=-2147483647,mi2=2147483647,ma2=-2147483647,x,y; 
int mian()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&x,&y);
		ma2=max(ma2,x),mi1=min(mi1,y);
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		ma1=max(ma1,x),mi2=min(mi2,y);
	}
	printf("%d",max(0,max(ma1-mi1,ma2-mi2)));
	return 0;
}

```

---

## 作者：qjxqjx (赞：0)

## 题目大意：
给你 $n$ 个区间，和 $m$ 个区间。求两个区间的最大值。

## 题目思路：
水题，可以记录开始下棋最大开始时间和最小结束时间，我们同样还记录编程的时间，然后再比较一下谁大输出就可以了。

## 代码：
```c
#include<bits.stdc++.h>
using namespace std ; 
const int INF=0x3f3f3f3f ; 
int main(){
    long long ans; 
    int n,m; 
    cin>>n;
    long long  x,y ;
    long long endTime1 = INF ,endTime2 = INF;
    long long begTime2 = 0 , begTime1 = 0 ;
    while(n--){
        cin>>x>>y;           
        if(y<endTime1) endTime1 = y ;
        if(x>begTime1) begTime1 = x ;
    }
    cin>>m;
    while(m--){
        cin>>x>>y;
        if(x>begTime2) begTime2 = x ;
        if(y<endTime2) endTime2 = y ;
    }
    if(endTime1>begTime2&&endTime2>begTime1) printf("0\n");
    else{
       ans = max((begTime1-endTime2),(begTime2-endTime1));
            printf("%I64d\n",ans);
        } 
    return 0; 
}
```

---

