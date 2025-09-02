# Robbery

## 题目描述

It is nighttime and Joe the Elusive got into the country's main bank's safe. The safe has $ n $ cells positioned in a row, each of them contains some amount of diamonds. Let's make the problem more comfortable to work with and mark the cells with positive numbers from $ 1 $ to $ n $ from the left to the right.

Unfortunately, Joe didn't switch the last security system off. On the plus side, he knows the way it works.

Every minute the security system calculates the total amount of diamonds for each two adjacent cells (for the cells between whose numbers difference equals $ 1 $ ). As a result of this check we get an $ n-1 $ sums. If at least one of the sums differs from the corresponding sum received during the previous check, then the security system is triggered.

Joe can move the diamonds from one cell to another between the security system's checks. He manages to move them no more than $ m $ times between two checks. One of the three following operations is regarded as moving a diamond: moving a diamond from any cell to any other one, moving a diamond from any cell to Joe's pocket, moving a diamond from Joe's pocket to any cell. Initially Joe's pocket is empty, and it can carry an unlimited amount of diamonds. It is considered that before all Joe's actions the system performs at least one check.

In the morning the bank employees will come, which is why Joe has to leave the bank before that moment. Joe has only $ k $ minutes left before morning, and on each of these $ k $ minutes he can perform no more than $ m $ operations. All that remains in Joe's pocket, is considered his loot.

Calculate the largest amount of diamonds Joe can carry with him. Don't forget that the security system shouldn't be triggered (even after Joe leaves the bank) and Joe should leave before morning.

## 说明/提示

In the second sample Joe can act like this:

The diamonds' initial positions are $ 4 $ $ 1 $ $ 3 $ .

During the first period of time Joe moves a diamond from the $ 1 $ -th cell to the $ 2 $ -th one and a diamond from the $ 3 $ -th cell to his pocket.

By the end of the first period the diamonds' positions are $ 3 $ $ 2 $ $ 2 $ . The check finds no difference and the security system doesn't go off.

During the second period Joe moves a diamond from the $ 3 $ -rd cell to the $ 2 $ -nd one and puts a diamond from the $ 1 $ -st cell to his pocket.

By the end of the second period the diamonds' positions are $ 2 $ $ 3 $ $ 1 $ . The check finds no difference again and the security system doesn't go off.

Now Joe leaves with $ 2 $ diamonds in his pocket.

## 样例 #1

### 输入

```
2 3 1
2 3
```

### 输出

```
0```

## 样例 #2

### 输入

```
3 2 2
4 1 3
```

### 输出

```
2```

# 题解

## 作者：谦谦君子 (赞：2)

# 题目大意
### 有n个连续的房间，每个房间里放了a[i]个钻石。一共有k分钟，每分钟能做m次操作。可以的操作有：：把一颗钻石从某一堆移到另一堆 or 把一颗钻石从某一堆中装进口袋 or把一颗钻石从口袋取出放入某一堆钻石 。 
#### 要求：每分钟后，相邻两堆的钻石数量不变。问k分钟后最多可以带走多少钻石。

# 思路
### 偶数堆钻石无法拿走，奇数堆钻石每拿走一个，需要额外移位n/2次。所以，如果n/2+1>m则不能拿走钻石。 设奇数堆钻石数量不限制，则最多能拿走钻石的个数为m/(n/2+1)*k个。

```
#include<bits/stdc++.h>
using namespace std;
long long dia[10010];
int main()
{
   long long n,m,ans=0,mis=100000,k,need=0;
   cin>>n>>m>>k;
   for(int i=1;i<=n;++i)
   {
      cin>>dia[i];
      if(mis>dia[i]&&i%2==1)
      {
          mis=dia[i];
      }
   }
   need=n/2+1;
   if(n%2==0||need>m);
   else
   {
       ans=m/need*k;
       ans=min(mis,ans);
   }
   cout<<ans<<endl;
   return 0;
}
```


---

## 作者：dby_718 (赞：0)

# 题目大意：

有 $n$ 个房间，每个房间有 $ a_i $ 个钻石，现在有 $k$ 分钟，每分钟可以做 $m$ 次操作，可以执行的操作有：把一颗钻石从某一堆移到另一堆，把一颗钻石从某一堆装进口袋，把一颗钻石从口袋取出放入某一堆钻石。

现在问你，最多可以带走几颗钻石。

# 题目分析

这道题要用到分类讨论的思想。

当 $n$ 为偶数时，是拿不走钻石的。

当 $n$ 为奇数时，拿走一颗钻石需要 $ n/2 + 1 $ 次操作。

所以，当 $ m < n/2 +1 $ 时，不能拿走钻石。

当 $ m > n/2 + 1 $ 时，每分钟拿走 $ m/(n/2+1) $ 个钻石。

又因为当奇数堆钻石个数为 $0$ 时就不能再拿了，所以最小数量应是 $a$ 数组的最小值与 $ m/(n/2+1) $ 的较小值。

下面给出代码。

```cpp
#include<iostream>
using namespace std;
#define int long long
int a[100005],qwq=100000000;// qwq 表示数组的最小值
signed main(){
    int x,y,z;// x 表示房间个数， y 表示每分钟可以进行的操作次数， z 表示分钟数
    cin>>x>>y>>z;
    for(int i=1;i<=x;i++){
        cin>>a[i];
        if(i%2==1) qwq=min(qwq,a[i]);//求最小值
    }
    if(x%2==0||y<(x+1)/2){//不能拿走的情形
        cout<<0;return 0;//直接结束程序
    }
    int ans=min(qwq,y/((x+1)/2)*z);
    cout<<ans<<endl;//输出
    return 0;
}
```

---

## 作者：Nozebry (赞：0)

## $Problems$
有 $n$ 个连续的房间，每个房间里放了 $a_i$个钻石。

现在有 $k$ 分钟，每分钟能做 $m$ 次操作。

可以的执行的操作有：

	1.把一颗钻石从某一堆移到另一堆;
	2.把一颗钻石从某一堆中装进口袋;
 	3.把一颗钻石从口袋取出放入某一堆钻石 。
要求：每分钟后，相邻两堆的钻石数量不变。

现在问你问 $k$ 分钟后最多可以带走多少钻石？
## $Answer$
这道题目我们先用分类讨论来解决：

**No.1**：当 $n$ 为偶数时，不难发现，是拿不走钻石的。所以我们只需要考虑当 $n$ 为奇数时的情况。

**No.2**：当 $n$ 为奇数时，每偷一颗钻石的移动次数应该是 $\frac{n}{2}+1$ ，即把第奇数堆的一颗钻石向后移动一位，再从最后一堆取走一个。

以上分析可以看出，最大的偷取数量还会受到奇数堆钻石的最小数量的约束。

故最小数量应该是数组 $a$ 中的最小值（且在奇数位上）与 $\frac{m}{(\frac{n}{2}+1)}*k$ 两个数中的较小数。
## $Code$
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[100010],minn=555555555;
int main()
{
    long long n,m,k;
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        if(i%2==1)minn=min(minn,a[i]);
    }
    if(n%2==0)
    {
        printf("0");
    }//当n位偶数时，无方案
    else
    {
        if(m<(n+1)/2)
        {
            printf("0");
        }
        else
        {
            long long ans1=m/((n+1)/2)*k,ans=min(minn,ans1);
            printf("%lld",ans);
        }
    }
}
```

---

## 作者：Provider (赞：0)

[Blog](https://www.luogu.com.cn/blog/foreverlovezxy/)

$2020/03/12$ 植树节发一篇题解吧

解析：

在钻石堆数为奇数时，执行如下步骤能拿走1颗钻石且警报不会触发。

1.选择某个序号为奇数的钻石堆，拿走其中一个钻石。

2.将其左侧的$2i$堆钻石分组：

从左端开始两个一组，对于所有组从左边堆拿1个钻石放到右边堆。

3.将其右侧的$2j$堆钻石分组：

同上


对于正常情况下，由于执行一次拿步骤需要$n/2+1$次操作。

1.对于$m<n/2+1$时，一颗也没法拿走。

2.$m>=n/2+1$，每分钟拿走$m/(n/2+1)$个

直到拿了$k$分钟或者在过程中某奇数序号堆钻石数为0时也不能再拿了。

注意：$n=1$时警报是不管用的，所以每分钟都可以拿$m$颗钻石直到拿光或者时间用光。

# CODE:

```
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
const int maxn=1e4+5;
long long n,m,k,minvalue=INT_MAX,a[maxn];
int main()
{
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(i&1)
        minvalue=min(minvalue,a[i]);
    }
    if(n==1)
    cout<<min(a[1],k*m);
	else
	if((n&1)==0)
    cout<<0;
	else
    {
    	long long tmp=(n>>1)+1;
    	if(m<tmp)
    	cout<<0;
		else
    	cout<<min(minvalue,k*(m/tmp));
    }
    return 0;
}
```

---

