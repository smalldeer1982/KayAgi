# Fly, freebies, fly!

## 题目描述

Everyone loves a freebie. Especially students.

It is well-known that if in the night before exam a student opens window, opens the student's record-book and shouts loudly three times "Fly, freebie, fly!" — then flown freebie helps him to pass the upcoming exam.

In the night before the exam on mathematical analysis $ n $ students living in dormitory shouted treasured words. The $ i $ -th student made a sacrament at the time $ t_{i} $ , where $ t_{i} $ is the number of seconds elapsed since the beginning of the night.

It is known that the freebie is a capricious and willful lady. That night the freebie was near dormitory only for $ T $ seconds. Therefore, if for two students their sacrament times differ for more than $ T $ , then the freebie didn't visit at least one of them.

Since all students are optimists, they really want to know what is the maximal number of students visited by the freebie can be.

## 样例 #1

### 输入

```
6
4 1 7 8 3 8
1
```

### 输出

```
3
```

# 题解

## 作者：崔化博 (赞：4)

看题解里没有二分做法就上传了。
### 题目大意
给出一个序列和两个数 $n$ 和 $T$，求对于每个 $a_{i}$ 在 $a_{i}-a_{i}+T$ 之间的数的个数的最大值。
### 做法
考虑二分，先排序一遍，然后二分求得第一个大于 $a_{i}+T$ 的数，将他减一就是最后一个小于等于 $a_{i} +T$，然后再二分求第一个大于等于 $a_{i}$ 的数，将他们相减再加一就是答案，最后再求一个最大值就可以了。
### 代码
```cpp
#include <iostream> 
#include <cstdio>
#include <algorithm>
using namespace std;
long long n,a[105],t,maxn;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i)
    	cin>>a[i];
    cin>>t;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;++i){
    	//用STL就可以，减一再加一就等于没变所以可以去掉
    	maxn=max(maxn,(long long)(upper_bound(a+1,a+n+1,a[i]+t)-lower_bound(a+1,a+n+1,a[i])));
	}
	cout<<maxn;
    return 0;
}
```
复杂度：
$O(n \log n)$

---

## 作者：FreedomKing (赞：2)

# 暴力
[注：blog 食用更佳](https://www.luogu.com.cn/blog/zhugeminhao/SP3394)

------------
### 题目大意
给定一个长度为 $n(1\leq n\leq 100)$ 的序列 $t$ ，一个整数 $T(1\leq T\leq 1000)$ ,存在一个在序列 $t$ 里的 $x$ ，使得序列 $t$ 中有更多的数大于等于 $x$ 且小于等于 $x+T$ ，求最多的出现次数。

------------
### 思路
由于这题的数据仅仅有 $1≤n≤100$ 的范围，所以我们可以采用暴力解法直接枚举每一个数，然后统计再取最大值。

那么思路清晰，开干！

------------
[CF386B Fly, freebies, fly!](https://www.luogu.com.cn/problem/CF386B)
### AC Code:
```cpp
#include<bits/stdc++.h>//不用万能头也可以，但个人觉得万能头方便
using namespace std;//必须得加，不然会报错
int t[105],n,x=0,s,T;
int main(){
	scanf("%d",&n);//输入n
	for(int i=1;i<=n;i++) scanf("%d",&t[i]);//输入t数组
	scanf("%d",&T);//输入T
	for(int i=1;i<=n;i++){
		s&=0;//小优化，用位运算初始化
		for(int j=1;j<=n;j++) if(t[i]<=t[j]&&t[j]<=t[i]+T) s++;//枚举+统计
		x=max(s,x);//更新最大值
	}
	printf("%d",x);//输出最大值
	return 0;
}
```
~~蒟蒻的第 5 篇题解，但还是求过 QwQ~~

---

## 作者：newbie_QwQ (赞：2)

题目大意:
给定一个长度为 $n(1\leq n\leq 100)$ 的序列 $\left\{ t_i\right\}(1\leq t_i\leq 1000)$，一个整数 $T(1\leq T\leq 1000)$，存在一个在 $t_i$ 中出现过的数 $x$，使得 $\left\{ t_i\right\}$ 中有更多的数大于等于 $x$ 且小于等于 $x+T$，求最多的出现次数。

------------
分析：
因为这道题的数据范围非常小，只有可怜的 $1\leq n\leq 100$。所以可以直接暴力枚举每一个数，统计满足条件的数有多少，直接取一下最大值就可以了。

------------
## AC 代码：
```cpp
#include<iostream>
using namespace std;
int t[105];
int main() 
{
	int i,j,n,ans=0,cnt,T;
	cin>>n;
	for(i=1;i<=n;i++) cin>>t[i];
	cin>>T;
	for(i=1;i<=n;i++)
	{
		cnt=0;//记得清零。
		for(j=1;j<=n;j++)
		{
			if(t[i]<=t[j]&&t[j]<=t[i]+T) cnt++;//统计个数。
		}
		ans=max(cnt,ans);//取最大值。
	}
	cout<<ans;
	return 0;//再见！
}
```

---

## 作者：Dfkuaid (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF386B)

## #1.0 题目大意

给出一个整数 $n$ 和一个长度为 $n$ 的数列 $\{a_i\}$ 以及一个整数 $t$，求数列 $\{a_i\}$ 中最多有几个元素 $\in[x,x+t]$，其中 $x\in\{a_i\}.$

## #2.0 朴素做法

打眼一看数据范围很小，可以使用 $O(n^2)$ 的朴素算法。

我们可以枚举 $x$ 的取值，之后遍历整个序列，记录答案即可。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

int n,t,a[N],cnt,ans;

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++)
      scanf("%d",&a[i]);
    scanf("%d",&t);
    for (int i = 1;i <= n;i ++){ //枚举每一个 a[i]
        int r = a[i] + t;cnt = 0;
        for (int j = 1;j <= n;j ++) //遍历数组
          if (a[i] <= a[j] && a[j] <= r)
            cnt ++;
        ans = max(ans,cnt);
    }
    cout << ans;
    return 0;
}
```

## #3.0 线段树优化

我们对 $O(n^2)$ 的时间复杂度不是很满意，~~虽然它能过这道题。~~

朴素算法的时间复杂度瓶颈是 **查询有多少数在区间 $[a_i,a_i+T]$ 中**，不由得联想到 **权值线段树**，它可以将单次查询的时间复杂度由 $O(n)$ 将至 $O(\log n).$

不过要注意，我们在建树的时候，权值线段树的维护范围应当为 $[1,M+T]$，其中 $M=\max\{a_i\}$，这是因为查询时的区间为 $[a_i,a_i + T]$，我们应当避免越界，防止出现未知的错误。

``` cpp
const int N = 100010;
const int MAX = 5000;
const int INF = 0x3fffffff;

struct Node{
    int l,r;
    int ls,rs;
    int sum;
};
Node p[N];

int cnt,n,T,root,a[N],mx,ans;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

inline int create(const int &l,const int &r){ //动态开点
    p[++ cnt].l = l,p[cnt].r = r;
    p[cnt].ls = p[cnt].rs = p[cnt].sum = 0;
    return cnt;
}

inline void insert(int k,int x){ //单点修改
    p[k].sum ++;
    /*因为是统计出现的数的个数，所以所经过的路径上
    的数的总数必然是 +1，之后便不需要 pushup()*/
    if (p[k].l == p[k].r)
      return; //到了叶节点
    int mid = (p[k].l + p[k].r) >> 1;
    if (x <= mid){
        if (!p[k].ls) p[k].ls = create(p[k].l,mid);
        /*如果该点未创建，应当先建点*/
        insert(p[k].ls,x);
    }
    else{
        if (!p[k].rs) p[k].rs = create(mid + 1,p[k].r);
        //同上
        insert(p[k].rs,x);
    }
}

inline int query(int k,int x,int y){//区间查询
    if (x <= p[k].l && p[k].r <= y)
      return p[k].sum; //当前区间被包含，一定是解的一部分
    int mid = (p[k].l + p[k].r) >> 1,res = 0;
    /*下面要将当前区间分为左右两段*/
    /*如果左边的一段与待查询区间有交集，递归查询*/
    if (x <= mid) if (p[k].ls)
      res += query(p[k].ls,x,y);
    /*如果右边的一段与待查询区间有交集，递归查询*/
    if (y > mid) if (p[k].rs)
      res += query(p[k].rs,x,y);
    return res;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&a[i]);
        mx = Max(mx,a[i]);
    }
    scanf("%d",&T);
    root = create(1,mx + T + 10); 
    //防止超出界限，开大一点
    for (int i = 1;i <= n;i ++)
      insert(root,a[i]); //将点插入
    for (int i = 1;i <= n;i ++) //查询答案
      ans = Max(ans,query(root,a[i],a[i] + T));
    printf("%d",ans);
    return 0;
}
```

时间复杂度实际为 $O(n\log (M+T))$，其中 $M=\max\{a_i\}.$

## #4.0 继续优化

但是我仍旧不满意，单次查询的时间复杂度可不可以优化至 $O(1)$ 呢？

我们可以对每个数出现的次数进行统计，得到桶数组 ```b[i]```，再对 ```b[i]``` 做前缀和，得到前缀和数组 ```sum[i]```，之后，数列 $\{a_i\}$ 在区间 $[a_i,a_i+T]$ 内出现的数的个数便是 ```sum[a[i] + T] - sum[a[i] - 1]```，注意是 ```a[i] - 1```，因为我们所求的数组是闭区间。

``` cpp
const int N = 100010;
const int INF = 0x3fffffff;

int n,a[N],b[N],sum[N],T,mx,ans;

inline int Max(const int &a,const int &b){
    return a > b ? a : b;
}

int main(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&a[i]);
        b[a[i]] ++; //记录数量
        mx = Max(mx,a[i]);
    }
    scanf("%d",&T);
    for (int i = 1;i <= mx + T + 1;i ++)
      sum[i] = sum[i - 1] + b[i];//前缀和
    for (int i = 1;i <= n;i ++)
      ans = Max(ans,sum[a[i] + T] - sum[a[i] - 1]);
    printf("%d",ans);
    return 0;
}
```

时间复杂度应为 $O(n+M+T)$，其中 $M=\max\{a_i\}.$

不过要注意，因为用到了桶，所以如果 $a_i$ 的值可以特别大，那么这样做便不行了。

还有亿些有意思的事：**用 $O(n+M+T)$ 程序跑出的结果：**

![](https://pic.imgdb.cn/item/60b9859a8355f7f7182da50b.jpg)

![](https://pic.imgdb.cn/item/60b985c28355f7f718304060.jpg)

~~我：？？？这个用时？？？~~


## End

希望能给您带来帮助。



---

## 作者：Ninelife_Cat (赞：1)

这翻译我看了半天才看懂~~是不是我语文太差了~~。

### 个人认为稍微清晰一点的翻译：

给出一个整数 $n$ 和一个长度为 $n$ 的数列 $a$ 以及一个整数 $t$，求数列 $a$ 中最多有几个元素 $\in[x,x+t]$，其中 $x$ 可为任意整数。

### 思路：

因为 $n$ 和 $t$ 的范围比较小，所以我们可以枚举这个整数 $x$ 来寻找答案。

然后我们再加入一点点小优化。首先我们把数列 $a$ 从小到大排序，然后枚举 $a$ 的每一个元素，找它后面有几个元素与它的差小于等于 $t$，一旦差值大于 $t$ 的话就直接结束循环，这样可以大大减少枚举次数。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1001],t,maxn;
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	sort(a+1,a+n+1);
	cin>>t;
	for(int i=1;i<=n;i++)
	{
		int cnt=1;//cnt记录当前的最大值
		for(int j=i+1;j<=n;j++)
			if(a[j]-a[i]<=t) cnt++;
				else break;
		maxn=max(maxn,cnt); //更新答案
	}
	cout<<maxn;
	return 0;
}

---

## 作者：WilliamFranklin (赞：1)

这道题，简直无话可说，读完题看完数据也可以明白管理员为什么把它评为暂无评定了吧。 ~~因为连入门都不如~~

### 题目大意：
给定一个长度为 $n(1\leq n\leq 100)$ 的序列 $\left\{ t_i\right\}(1\leq t_i\leq 1000)$，一个整数 $T(1\leq T\leq 1000)$，存在一个在 $t$ 序列中出现过的数 $x$，使得 $\left\{ t_i\right\}$ 中有更多的数大于等于 $x$ 且小于等于 $x+T$，求最多的出现次数。

做这道题，我们不能忘了初心：

## 暴力出奇迹！

好了，贴代码。

### AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005]; //有着强迫症的我非开 1000 不可！
int main(){
    int n, T, ans = 0;
    cin>>n;
    for(int i = 1; i <= n; i++){
        cin>>a[i];
    }
    cin>>T;
    for(int i = 1; i <= n; i++){  //开始暴力，请注意
        int sum = 0;
        for(int j = 1; j <= n; j++){
            if(a[i] <= a[j] && a[j] <= a[i] + T){ //根据题意作判断
                sum++;
            }
        }
        ans = max(sum, ans);  //保留最大数值
    }
    cout<<ans<<endl; //拜拜！
    return 0;
}
```



---

## 作者：S__X (赞：0)

### 思路：
本题直接暴力求解就可以了。

两个循环，判断 $t_i$ 是否符合条件，如果符合计数器 $+1$，再输出计数器的最大值就可以了。
### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,maxx;
int a[10005];
int main() {
    cin>>n;
    for(int i=1; i<=n; i++) cin>>a[i];
    cin>>t;
    for(int i=1; i<=n; i++) {
        int s=0;
        for(int k=1; k<=n; k++) 
            if(a[i]>=a[k]&&a[i]<=a[k]+t)
                s++;
        maxx=max(maxx,s);
    }
    cout<<maxx;
    return 0;
}
```

---

## 作者：_lzy_ (赞：0)

## 思路
1. 第一步我们可一以直接写一个双重循环，用暴力的方法来解这道题目。
1. 然后再在这个循环中写一个判断语句用来判断 $t_i$ 是否符合题目条件，如果符合，就将计数器 $+1$ 。然后再设个变量 $maxx$ 用来计算最大值。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,t,s=0,maxx=0;
int a[10005];
int main() 
{
    cin>>n;
    for(int i=1; i<=n; i++)cin>>a[i];
    cin>>t;
    for(int i=1; i<=n; i++) {
        s=0;
        for(int k=1; k<=n; k++) {
            if(a[i]>=a[k]) {
                if(a[i]<=a[k]+t) { //判断。
                    s++;
                }
            }
        }
        maxx=max(maxx,s);//计算最大值。
    }
    cout<<maxx;
    return 0;
}
```


---

## 作者：qfpjm (赞：0)

# 题解

- 数据很小，直接暴力。

- 暴力枚举每个数 $t_i$，再遍历一遍序列，求满足条件的数。

- 时间复杂度 $O(n^2)$。

- 听说有 $O(n)$ 的做法，但我不会，况且此题也没有必要再优化。

# 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, T, t[105];

int main()
{
	cin >> n;
	for (int i = 1 ; i <= n ; i ++)
	{
		cin >> t[i];
	}
	cin >> T;
	int ans = 0;
	for (int i = 1 ; i <= n ; i ++)
	{
		int cnt = 0;
		for (int j = 1 ; j <= n ; j ++)
		{
			if (t[j] >= t[i] && t[j] <= t[i] + T)
			{
				cnt ++;
			}
		}
		ans = max(ans, cnt);
	}
	cout << ans;
} 
```


---

## 作者：lrmlrm_ (赞：0)

# 题意

给出一个长度为 $ n $ 的数组 $ a _ i $ , 有一个整数 $ t $ , 存在一个在 $ a _ i $ 中的 $ x $ ， 使的 $ a _ i $ 中有更多的数 $ \geq x $ 且 $ \leq x + t $ , 求最多的出现次数 。

# 思路

这题的 $ n \leq 100 $ , 所以不难想到用直接暴力枚举每一个数 ， 然后统计再取 $ \max $ 。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,ans,k,a[110];
int main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    scanf("%lld",&m);
    for(int i=1;i<=n;i++){
        k=0;
        for(int j=1;j<=n;j++)if(a[i]<=a[j]&&a[j]<=a[i]+m)k++;
        if(k>ans)ans=k;
    }
    printf("%lld",ans);
    return 0;
}
```

---

