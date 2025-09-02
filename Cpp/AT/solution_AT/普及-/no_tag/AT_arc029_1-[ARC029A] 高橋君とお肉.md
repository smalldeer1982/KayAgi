# [ARC029A] 高橋君とお肉

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc029/tasks/arc029_1

高橋君は友達とキャンプに行くことになった。

高橋君と友達は性能が同じである $ 2 $ 個の肉焼き器を持っており、それぞれの肉焼き器にお肉を乗せて並行して焼くことができる。一旦肉焼き器にお肉を乗せたら、お肉が焼きあがるまではその肉焼き器からお肉を取り出したり、その肉焼き器に別のお肉を乗せたりはできない。お肉が焼けたらお肉を取り出すことができる。$ 2 $ つの肉焼き器にまたがって $ 1 $ つのお肉を置くことはできない。また、お肉は全部で $ N $ 個あり、お肉には $ 1 $ から $ N $ まで番号が付けられている。お肉 $ i $ を焼くのには、どちらの肉焼き器でも時間 $ t_i $ だけかかる。お肉を肉焼き器に置く動作、取り出す動作には時間がかからない。

高橋君はお肉を焼く係であり、$ N $ 個すべてのお肉を焼くことになった。みんなお腹が空いているので、すべてのお肉を焼くのにかかる時間を最小化させたい。

すべてのお肉を焼くのにかかる時間の最小値を求めよ。

## 说明/提示

### Sample Explanation 1

一方の肉焼き器でお肉 $ 1 $ とお肉 $ 4 $ を、他方の肉焼き器でお肉 $ 2 $ とお肉 $ 3 $ を順に焼きます (下の図は参考図)。 !\[\](/img/arc/029/1-1.png)

### Sample Explanation 2

一方の肉焼き器でお肉 $ 3 $ を焼いている間に、他方の肉焼き器で残りすべてのお肉を焼きます。

## 样例 #1

### 输入

```
4
4
6
7
10```

### 输出

```
14```

## 样例 #2

### 输入

```
3
1
2
4```

### 输出

```
4```

## 样例 #3

### 输入

```
1
29```

### 输出

```
29```

# 题解

## 作者：Ryan_Yu (赞：7)

由于输入的数据很小（$n≤4$），我们先用 $sort$ 排一下序再进行暴力枚举。

枚举共分为以下几种情况：

1.只有一块肉，没得选，输出烤那 $meat_1$ 所需的时间。

2.有两块肉可将两块肉分别放到两个烤肉机上，输出 $meat_2$ 所需的时间即可。

3.有三块肉时，将烤 $meat_1+meat_2$ 所需的时间和与$meat_3$的时间比较，输出较大的。

4.有四块肉时有二种搭配方法，一种为 $meat_1$ 与 $meat_4$ 搭配，$meat_2$ 与 $meat_3$ 搭配比较一下。

另一种为 $meat_1$ 、$meat_2$ 与 $meat_3$ 搭配和 $meat_4$ 比较。

最终求两种方案中时间花的最少的。

```cpp
#include<bits/stdc++.h>
using namespace std;
int meat[5],i,n;
int main()
{
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>meat[i];
    sort(meat+1,meat+1+n);
    if(n==1)
        cout<<meat[1];
    //第一种情况
    if(n==2)
        cout<<meat[2];
    //第二种情况
    if(n==3)
        cout<<max(meat[1]+meat[2],meat[3]);
    //第三种情况
    if(n==4)   
    	cout<<min(max(meat[1]+meat[4],meat[2]+meat[3]),max(meat[1]+meat[2]+meat[3],meat[4]));
    //第四种情况
        cout<<endl;//岛国题要输出回车
    return 0;
}
```


---

## 作者：Rocket_raccoon_ (赞：4)

其实刚刚看到题面，还是觉得有些难度的，似乎要用一下毒瘤算法来把数据分成大小相等的两部分然后取最大值（其实实现起来也不是很困难）。

但是看到数据范围n<=4......呵呵

最简（无）洁（脑）做法，把n从一到四的情况列举出来，讨论一下怎么分配就行了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>//sort需要的头文件
using namespace std;
int sum[6];

int main(){
    int n,i;

    cin>>n;

    for (i=1; i<=n; i++){
        cin>>sum[i];
    }
    sort(sum+1,sum+1+n);//快排
    //分情况讨论
    if (n==1) cout<<sum[1];
    else if (n==2) cout<<sum[2];
    else if (n==3) cout<<max(sum[1]+sum[2],sum[3]);
    else if (n==4) cout<<min(max(sum[1]+sum[4],sum[2]+sum[3]),max(sum[1]+sum[2]+sum[3],sum[4]));

    return 0;
}
```

---

## 作者：1lgorithm (赞：2)

这个题让我们把一个数组分成两半，让这两半的和中最大的那个最小。

数据范围：$n\le4$

对于如此之小的数据范围，我们可以使用分类讨论的思想。

$Section1:$一个数

直接输出即可。

$Section2:$两个数

输出两个数中比较大的一个数。

$Section3:$三个数

三层循环枚举每一份烤肉放在哪一个烤肉机里，然后算出每一个烤肉机烤完肉的时间，取其最大值，然后统计最小值。

$Section4:$四个数

四层循环即可。

时间复杂度$O(2^n)$。

代码：

```cpp
#include<iostream>
using namespace std;
int a[5];
int t[5];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;++i) cin>>a[i];
	if(n==1){
		cout<<a[1]<<endl;
	}
	if(n==2){
		cout<<max(a[1],a[2])<<endl;
	}
	if(n==3){
		int ans[3]={0};
		int minx=1e9;
		for(int i=1;i<=2;++i){
			for(int j=1;j<=2;++j){
				for(int k=1;k<=2;++k){
					ans[1]=ans[2]=0;
					ans[i]+=a[1];
					ans[j]+=a[2];
					ans[k]+=a[3];
					minx=min(minx,max(ans[1],ans[2]));
				}
			}
		}
		cout<<minx<<endl; 
	}
	if(n==4){
		int ans[3]={0};
		int minx=1e9;
		for(int i=1;i<=2;++i){
			for(int j=1;j<=2;++j){
				for(int k=1;k<=2;++k){
					for(int l=1;l<=2;++l){
						ans[1]=ans[2]=0;
						ans[i]+=a[1];
						ans[j]+=a[2];
						ans[k]+=a[3];
						ans[l]+=a[4];
						minx=min(minx,max(ans[1],ans[2]));
					}
				}
			}
		}
		cout<<minx<<endl;
	}
}
```



---

## 作者：Obviathy (赞：1)

## 题意简述：
有 $n$ 个数 $a_1\sim a_n$，将它们分成两组，这两组的和的最大的那一个的最小值。
## 解题思路：
为了使烤肉总时间尽可能断，我们要尽量把时间平均分配给这两台机器，以减少机器空闲的时间浪费。

所以，解决思路大致为：将烤肉的时间由大到小排序（可能不排也可以，自己没试过），依次进入两个累加器 $ sum1 $ 和 $ sum2 $ 中，如果其中一个较大，那么就将其**加入另一个 $ sum $ 中**。最后输出 $ sum1 $ 和 $ sum2 $ 的**最大值**。
## code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,sum1,sum2;
int t[5];
int main(){
	cin >> n;
	for(int i = 1;i <= n;i ++)
		cin >> t[i];
	sort(t+1,t+1+n);
	sum1 = t[n];
	for(int i = n-1;i >= 1;i --){
		if(sum1 > sum2)sum2 += t[i];
		else sum1 += t[i];
	}
	cout<<max(sum1,sum2)<<endl;
	return 0;
}

```


---

## 作者：cherubim (赞：1)

### 题目  AT945 高橋君とお肉

读题。

题目大意是将一个数组 $k$ 分为两个数组 $c1$ 和 $c2$ ，让 $max (c1,c2)$ 有最小值。

那么考虑深搜。在题目的条件 $n \le 4$ 下可以使用枚举法，可当 $n >4 $ 时枚举法就不太现实了。

从第一块肉开始搜索。我们用 $dfs ( num,c1,c2)$ 来表示目前搜索到的状态。
如果 $num==n+1$ 则证明搜索完成更新 $minn$ 返回，否则继续搜索两种情况：

- 把第 $num+1$ 块烤肉放到 $c1$ 中。

- 把第 $num+1$ 块烤肉放到 $c2$ 中。

对应相加即可。

### CODE 
```CPP
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f ;
int n, a[10] ;
int minn = INF ;

inline void dfs ( int num, int c1, int c2 ) {
	if ( num == n + 1 ) {
		minn = min ( minn, max ( c1, c2 ) ) ;
		return ;
	}
	dfs ( num + 1, c1 + a[num], c2 ) ;
	dfs ( num + 1, c1, c2 + a[num] ) ;
	return ;
}

int main ( ) {
	scanf ( "%d", &n ) ;
	for ( int i = 1 ; i <= n ; ++ i )
		scanf ( "%d", &a[i] ) ;
	dfs ( 1, 0, 0 ) ;
	printf ( "%d\n", minn ) ;
	return 0 ;
}
```


---

## 作者：lxzy_ (赞：1)

大佬们都太强了，本蒟蒻只会用暴力写法——DFS

-------------------------------------------

思路很简单，输入完毕后，分别枚举每块肉用第一个烤肉机与第二个烤肉机所需要的时间，然后再取最小的即可。

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int a[5];
int sum=0x3f3f3f3f;//总共用时，由于我们需要算最小值，因此sum必须开到0x3f3f3f3f那么大
void DFS(int k,int tot1,int tot2)//tot1和tot2表示当前状态下第一、二个烤肉机所用的时间，在最后汇总时，取他俩的最大值
{
	if(k==n)//所有烤肉都枚举完了
	{
		sum=min(max(tot1,tot2),sum);//比较当前方案与原先方案哪个时间更短
		return ;
	}
	DFS(k+1,tot1+a[k],tot2);//当这块烤肉用第一个烤肉机烤
	DFS(k+1,tot1,tot2+a[k]);//当这块烤肉用第二个烤肉机烤
}
int main()
{
	cin>>n;
	for(int i=0;i<=n-1;i++)
	{
		cin>>a[i];
	}
	DFS(0,0,0);
	cout<<sum<<endl;
	return 0;
}
```


烤肉的范围只到2^2 (4)，因此这个方法可行。但如果到达2^28 (268435456)就会TLE辣。所以本蒟蒻的深搜法仅供参考。

---

## 作者：Stella_Yan (赞：1)

这一题纯粹就是数论。。。

当n=1时,就输出输入的那个数。

当n=2时,输出较大的那个数（因为一块小的烤好了大的还没烤好,所以要等一会）

当n=3时,输出较小的两个数之和与剩下的那个数中较大的那个（因为有可能大的烤好了两个小的还没烤好,这时候输出两个小的之和.如果两个小的烤好了大的还没烤好,就输出大的）

当n=4时,输出最小和最大的和与剩下两块的和中的较大值与前三块的和与剩下一块的最大值的最小值。

~~是不是很懵逼~~

$1\ 2\ 3\ 4$

说白了就是排好序后第一块与最后一块的和,第二块与第三块的和取最大值

前三块的和与第四块的和取最大值

这两个最大值再取一个最小

~~还是很懵逼对不对~~

~~看代码吧~~

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int main(){
    int a[6];
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);//排序
    if(n==1)//只有一块时
        cout<<a[1];
    else if(n==2)//两块时
        cout<<a[2];
    else if(n==3)//三块时
        cout<<max(a[1]+a[2],a[3]);
    if(n==4)//四块时
        cout<<min(max(a[1]+a[4],a[2]+a[3]),max(a[1]+a[3]+a[2],a[4]));
    /*
    max(a[1]+a[4],a[2]+a[3])指的就是第一块与第四块的和,第二块与第三块的和取最大值,因为烤的比较久的要等一下
    max(a[1]+a[2]+a[3],a[4])就是前三块的和与第四块取最大值,如果第四块烤的比前三块的和还慢的话就要等等,否则就是前三块烤的慢,第四块要等前三块
    最后取一个最小,看一下哪一个烤的快
    */
    cout<<endl;
    return 0;
}
```

---

## 作者：Chtholly_L (赞：0)

看到这道题 $N$ 的数据范围，只有 $1 \le N \le 4$，说明这道题我们可以通过枚举这四种情况，再进行比较来解决。

---

我们先将这些时间按从小到大的顺序排好序。

首先，当 $n=1$ 时，用任意一个烤肉机把它烤完，直接输出所用时间即可。

其次，当 $n=2$ 时，两块肉分别放在两个烤肉机上，那么所用的时间就是烤的时间较长的那一个，输出这两个数中较大的即可。

然后，当 $n=3$ 时，我们可以将时间最长的放在一个烤肉机上烤，再将另外的两个烤肉依次在另一个烤肉上烤.

![](https://cdn.luogu.com.cn/upload/image_hosting/8p38gqr3.png)

如图所示，那么由图可以发现，需要的最小时间是花费时间最多的时间和剩下两个加起来的时间中的最小值，即 $t_{min}=\max(t1+t2,t3)$。


根据以上我们可以来枚举 $n=4$ 时的情况，将肉一加肉四与肉二加肉三比较。再将肉一加肉二加肉三与肉四比较，再将上一轮中得出来的两个较大的的情况比较出较小的那一个，就得出了答案。

---

还是上代码辅助理解吧。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

int a[10];

int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1);
    if(n==1)cout<<a[1]<<endl;
    if(n==2)cout<<a[2]<<endl;  // 因为已经排好序了，所以 a[2] 就是较大的。
    if(n==3)cout<<max(a[1]+a[2],a[3])<<endl;
    if(n==4)cout<<min(max(a[1]+a[4],a[2]+a[3]),max(a[1]+a[2]+a[3],a[4]))<<endl;
    return 0;
}
```


---

