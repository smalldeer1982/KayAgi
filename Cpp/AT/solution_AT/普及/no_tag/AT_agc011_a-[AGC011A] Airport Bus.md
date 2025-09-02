# [AGC011A] Airport Bus

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc011/tasks/agc011_a

高橋空港には，毎日飛行機で $ N $ 人の乗客が到着します． $ i $ 番目の乗客は時刻 $ T_i $ に到着します．

高橋空港に到着する乗客は全員バスで市内へ移動します．どのバスも定員は $ C $ 人であり，$ C $ 人以下の乗客を乗せることができます． 飛行機の乗客は，飛行機の到着時刻よりも早く出発するバスには乗ることができません． また，飛行機の到着時刻から $ K $ の時間が経過した後にもバスに乗れていないと，怒り出してしまいます． そのため，$ i $ 番目の乗客は，出発時刻が $ T_i $ 以上 $ T_i\ +\ K $ 以下であるようなバスに乗れるようにしないといけません．

この条件のもとで，うまくバスの出発時刻を定めるとき，必要なバスの数の最小値を求めてください． ただし，バスの出発時刻は必ずしも整数である必要はなく，同じ時刻に出発するバスが複数あってもかまいません．

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 100000 $
- $ 1\ \leq\ C\ \leq\ 10^9 $
- $ 1\ \leq\ K\ \leq\ 10^9 $
- $ 1\ \leq\ T_i\ \leq\ 10^9 $
- $ C,\ K,\ T_i $ は整数

### Sample Explanation 1

例えば，時刻 $ 4.5 $, $ 6 $, $ 12 $ にバスを出発させ，次のように乗客をバスに乗せるとよいです． - 時刻 $ 4.5 $ に出発するバスには，時刻 $ 2,\ 3 $ に到着する乗客を乗せる． - 時刻 $ 6 $ に出発するバスには，時刻 $ 1,\ 6 $ に到着する乗客を乗せる． - 時刻 $ 12 $ に出発するバスには，時刻 $ 12 $ に到着する乗客を乗せる．

## 样例 #1

### 输入

```
5 3 5
1
2
3
6
12```

### 输出

```
3```

## 样例 #2

### 输入

```
6 3 3
7
6
2
8
10
6```

### 输出

```
3```

# 题解

## 作者：Xdl_rp (赞：1)

简要题意：
------------

- 你要在 $t$ 时间的时候发车，如果这一个乘客能上车（也就是$T_i \le t \le T_i+K$），使得上车的人最多，问最少要多少辆车才能将所有的乘客从机场运到城市。

solution：
------------

- 将所有乘客按 $T_i$ 从小到大排序，然后按这个顺序安排车，对于每辆车，往上面加乘客时，如果当前乘客数量等于 $C$，或者下一个要安排的乘客的 $T$ 值 减去这辆车上最早乘客的 $T$ 值超过 $K$（题目有说明），那么这辆车就应该出发，继续安排下一辆车，用一个 $cnt$ 来计算有多少人上了车，用一个 $ans$ 来记录开了几辆车，最后安排车的数量就是答案（也就是 $ans$)。

代码：
------------

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int q[100005];
signed main() {
	int n, c, k;
	cin >> n >> c >> k;
	for (int i = 1; i <= n; i++) {
		cin >> q[i];
	}
	sort(q + 1, q + n + 1);
	int t = q[1] + k, cnt = 0, ans = 1;
	for (int i = 1; i <= n; i++) {
		if (q[i] <= t && t <= q[i] + k && cnt < c) cnt++;
		else {
			ans++;
			cnt = 1;
			t = q[i] + k;
		}
	}
	cout << ans;
	return 0;
}
```

记得点个赞再走哦！

---

## 作者：上杉越 (赞：1)

 ~~这题为啥是黄题~~

[传送门](https://www.luogu.com.cn/problem/AT2337)

## 题目描述：
有$ N$ 位乘客，第 $i$ 位将在时刻 $Ti$ 抵达机场。

你需要发出一些公交，将所有乘客从机场送到城市。如果一班公交在时刻 $t$ 出发，那么所有满足 $Ti$ $≤$ $t$ $≤$ $Ti$ $+$ $K$ 的乘客 $i$ 可以坐上这一班公交。但是一班公交只能坐 $c$ 人。

你可以在任意时刻发出公交（可以同时发车）求最少发车次数。

## 算法：贪心

## 思路：
将每一个人的上车时间进行排序，时间早的在前。设 $time$ 为发车时间， $time$ 越晚越好，因为这样可以尽可能的使公交的乘客更多。

当公交的乘客达到上限或这个公交无法满足这位乘客时，增加一辆公交。

## Coding:
```cpp
#include<bits/stdc++.h>//懒人头文件
using namespace std;
int n,k,c,t[100086];
int main(){
	cin>>n>>c>>k;
	for(int i=1;i<=n;i++)cin>>t[i];
	sort(t+1,t+n+1);
	int time=t[1]+k,sum=1,ans=1;
    /*time为发车时间，sum为此时公交上的人数，ans为已发车辆。*/
	for(int i=2;i<=n;i++){
		if(sum==c){//当公交坐满时
			ans++,sum=1;//需要发出的车加一，车上人数变为一。
			time=t[i]+k;//更改发车时间
		}
		else{
			if(t[i]<=time&&time<=t[i]+k)sum++;//公交人数加一
			else{
				ans++,sum=1;//同上
				time=t[i]+k;
			}
		}
	}
	cout<<ans;
	return 0;
}
```
~~点个赞再走呗！~~


---

## 作者：scp020 (赞：0)

### 题意

共有 $n$ 位乘客，每位乘客在 $T_i$ 到达机场，可以在任意时刻发一辆车，车在机场等待 $k$ 分钟，这期间到达的乘客可上车，且一辆车的运载量为 $c$ 人，如果超载乘客将不可上车。

求至少要发多少辆车。

### 解决

贪心加模拟。

我们先把 $T_i$ 按照从小到大排序，这样方便贪心。

排序后，我们依次遍历数组中的元素。
- 如果时间超过了 $t+k$ 或运载人数达到上限，就考虑把 $ans$ 计数器自增 $1$，也就是再发一辆车，让这个人做上下一辆车。

- 如果正好被本班车覆盖，则让这个人坐上这辆车。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,c,k,a[100010],ans,num,tim;
int main()
{
    ios::sync_with_stdio(false);
    cin>>n>>c>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
    {
        if(num>=c || a[i]>tim) tim=a[i]+k,ans++,num=1;
        else num++;
    }
    cout<<ans;
    return 0;
}
```


---

## 作者：Night_sea_64 (赞：0)

本蒟蒻又来写题解了~~~

~~只有 AT 的黄题才这么简单！！！~~

#### 知识点：贪心 + 模拟。

[题目](https://www.luogu.com.cn/problem/AT2337)

贪心策略非常简单。一句话概括，就是能不发车尽量不发车。也就是在当前这一趟车时间还没过，也没有超载的情况下，就让当前这个人上这辆车。剩下的就全是模拟了，非常简单。AC 代码如下：

```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int a[100010];
int main()
{
    int n,c,k;
    cin>>n>>c>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    sort(a+1,a+n+1);
    int beg=-1e9,cnt=1,ans=0;
    //beg 记录的是当前这趟车的发车时间。因为 k<=1e9，所以初值要设成 -1e9。
    //cnt 记录的是上了这趟车的人数。
    //ans 记录的是发了几趟车。
    for(int i=1;i<=n;i++)
    {
        cnt++;//先让他上这辆车，后面再判断
        if(a[i]-beg>k||cnt>c)
            beg=a[i],cnt=1,ans++;//需要新发一辆车的情况。注意这里 cnt 要赋值为 1，因为这个人已经上了这辆车。
    }
    cout<<ans<<endl;
    return 0;
}
```

#### 求各位 dalao 点个赞吧~~~

---

## 作者：Mr_WA的大号 (赞：0)

光阴似箭，日月如梭。小学生又来发题解了！

题号：AT2337

难度：★★

算法：模拟、贪心

## 开课了！

这一道题要求的是最少的发车次数，所以我们很容易就会想到这道题其实就是一道贪心题，要让尽量多的人坐一辆车。

我们输入后第一步就是排序，这样我们才能进行贪心。

接下来我们就要开始贪心了。先赋初值：

```cpp
people=1;//当前公交车上的人数赋为1
bus=1;//公交车数赋为1
sign=timer[1]+k;//最后的时间赋为timer[1]+k
```

接着从2开始枚举，如果当前这个人超时了（也就是不能坐这趟公交）或者公交已经被坐满了，就新开一辆公交，让那个人坐进去。否则那个人就坐当前那辆公交。

课讲完了，上代码：
```cpp
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int n,c,k,people,sign,bus;
int timer[100010];
int main()
{
	cin>>n>>c>>k;
	for(int i=1; i<=n; i++)
		scanf("%d",&timer[i]);
	sort(timer+1,timer+1+n);//排序
	people=1;
	bus=1;
	sign=timer[1]+k;//赋初值
	for(int i=2; i<=n; i++)//贪心
		if(sign<timer[i]||people==c)//如果超时了或者人满了
		{
			bus++;//新开一辆车
			people=1;//人数为1
			sign=timer[i]+k;//赋终止时间
		}
		else people++;//不然的话人数++
	cout<<bus<<endl;//输出
	return 0;
}
```
祝大家能AC！

---

