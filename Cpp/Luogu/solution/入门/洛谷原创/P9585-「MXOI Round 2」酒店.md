# 「MXOI Round 2」酒店

## 题目描述

小 C 开了一家酒店，叫做 CC Hotel。

一天，CC Hotel 来了 $n$ 位客人。小 C 需要把他们都安排在酒店的某一层中。每个房间中只能安排一位客人。

这一层共有 $m$ 间房间，这 $m$ 间房间都是空的，且这 $m$ 间房间形成了一个环形，即对于所有的 $1 \le x \le m$，都有第 $x$ 间房间与第 $((x \bmod m)+1)$ 间房间相邻，第 $((x \bmod m)+1)$ 间房间与第 $x$ 间房间相邻，其中 $x \bmod m$ 表示 $x$ 除以 $m$ 得到的余数。

这 $n$ 位客人都十分挑剔，他们希望与自己的房间相邻的房间中没有人。对于某一位客人，若与他的房间相邻的房间中，有 $k$ 间房间有人，则这位客人会产生 $k$ 点愤怒值。

你需要帮助小 C 安排房间，使得所有客人的愤怒值之和最小，并输出所有客人的愤怒值之和的最小值。

## 说明/提示

#### 【样例解释 #1】

对于这 $5$ 间房间，其中一组满足条件的安排方案为：不住人、住人、住人、不住人、住人。

可以证明所有客人的愤怒值之和的最小值为 $2$。

#### 【数据范围】

对于 $100\%$ 的数据，$1 \le n \le 100$，$3 \le m \le 100$，保证 $n \le m$。

|测试点编号|特殊性质|
|:---:|:---:|
|$1\sim3$|保证 $2n\le m$|
|$4\sim6$|保证 $m=n+1$|
|$7\sim10$|无|

## 样例 #1

### 输入

```
3 5```

### 输出

```
2```

## 样例 #2

### 输入

```
1 4```

### 输出

```
0```

# 题解

## 作者：Coffee_zzz (赞：36)

### Task 1~3

容易发现，当 $2n\le m$ 时，一定可以做到任意一位客人的相邻的房间都没有人，所以答案为 $0$。

### Task 4~6

由于 $m=n+1$，所以只会空出一个房间。

与这个空房间相邻的客人的愤怒值显然为 $1$，而剩余 $(n-2)$ 位客人的愤怒值就为 $2$，所以答案为 $1+1+2(n-2)=2n-2$。

### Task 7~10

根据 Task 1~3 的结论，我们知道当 $2n\le m$ 时答案为 $0$。

我们思考 $2n\gt m$ 时的答案。

不好考虑有人的房间怎么安排，那我们可以考虑空房间怎么安排。

两个空房间相邻是没有用的，所以我们要让与空房间相邻的房间都为有人的房间。由于空房间数量比有人的房间的数量要少，所以这个条件是可以做到的。

当没有空房间时，每位客人的愤怒值都为 $2$；每一个空房间，可以使相邻的 $2$ 个房间内的客人的愤怒值减少 $1$。我们知道空房间的数量为 $m-n$，所以答案为 $2n-2(m-n)=4n-2m$。

### Code

```c++
#include <bits/stdc++.h>
using namespace std;
signed main(){
	int n,m;
	cin>>n>>m;
	if(n*2<=m) cout<<0;
	else cout<<4*n-2*m;
	return 0;
}
```

---

## 作者：zhang_Jimmy (赞：5)

这道题其实非常简单，不要被它的题面吓到了。

# 思路：

我们可以发现，使每个人的怒气值最小，肯定要隔一个房间放一个人，如果还有人没进房间，再往剩下的空房间里放人。

然后统计每个人的怒气值就可以了，如果一边的房间有人答案就加一，注意特殊处理第 $1$ 个房间和第 $m$ 个房间就可以了。

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
int a[110], n, m, sum;
int main(){
// 	freopen("hotel.in", "r", stdin);
//	freopen("hotel.out", "w", stdout);
	cin >> n >> m;
	for(int i = 1; i <= m; i += 2)
	if(sum == n) break;
	else a[i] = 1, sum ++;
	for(int i = 2; i <= m; i += 2)
	if(sum == n) break;
	else a[i] = 1, sum ++;
//	for(int i = 1; i <= m; i ++)
//	cout << a[i];
	int ans = 0;
	for(int i = 1; i <= m; i ++){
		if(a[i] == 0) continue;
		if(i == 1){
			if(a[m] == 1) ans ++;
			if(a[2] == 1) ans ++;
			continue;
		}
		if(i == m){
			if(a[i - 1] == 1) ans ++;
			if(a[1] == 1) ans ++;
			break;
		}
		if(a[i - 1] == 1) ans ++;
		if(a[i + 1] == 1) ans ++;
	}
	cout << ans;
	return 0;
}

```


---

## 作者：2huk (赞：5)

既然相邻不优，那么就尽量不要相邻，也就是说我们尽量隔着放，即放在 $1, 3, 5, \dots$ 这些位置。

那么如果能这样把所有格子放完，那样最好，否则如果还有剩余的只能把刚才剩下的位置依次填满，即填依次 $2, 4, 6, \dots$ 这些位置。

最后计算答案即可。

---

## 作者：zzx114514 (赞：3)

## [题目传送门](https://www.luogu.com.cn/problem/P9585)
# 题目大意
在一个长度为 $m$ 的圆环中放入 $n$ 个元素，使得相邻元素最少，输出所有元素相邻的元素数量之和。
# 解题思路
通过找规律可知，每个圆环最多可以放下 $\left \lfloor \frac{m}{2} \right \rfloor$ 个不相邻的元素，如果元素数量超过这个数，那么最小的总相邻数为 $(n\times2-m)\times2$。
# 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m;
int main()
{
	cin>>n>>m;
	if (n<=m/2) cout<<0;
	else cout<<(n*2-m)*2;
	return 0;
}
```


---

## 作者：lemon_qwq (赞：2)

签到题。

很明显最优策略为先是空一格住一个，然后没有地方可以住了再插进空的位置。

如果空一格住一个都住不满，即 $n\times 2\le m$，则怒气值为 $0$。

否则，我们可以手搓一组样例找找规律，为了方便计算我们让插进去的几个人的下标尽量靠近，这样有怒气值的人都是相邻的了。

最边缘有怒气值的客人的怒气值一定是 $1$，被夹在中间的客人的怒气值一定是 $2$。

对于推出来的结论，我们可以列出如下式子：$\frac{(2\times n-m)\times 2+(2\times n-m-1)\times2+2}{2}$。

化简后为 $4\times n-2\times m$。

接下来直接套公式就可以啦！

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
	cin>>n>>m;
	if(2*n<=m){空一格住一个都坐不满
		cout<<0<<endl;
	}else{
		cout<<4*n-2*m<<endl;//计算怒气值，化简完后是这个式子
	}
	return 0;
}
```

完结撒花！

提一嘴，如果不想用数学的方法做，直接模拟也能过掉这题。

---

## 作者：zjjc1104111 (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/P9585)

# 思路

本题采用贪心算法。

不难想到，我们尽量把客人们交错开，便能得到最优解，但如果房间不够，我们只能把剩下的客人放在一起了，最后再计算出答案。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105];//0表示这个房间没人，1代表有人
int main(){
	int n,m,ans=0;
	cin>>n>>m;
	for(int i=2;i<=m && n;i+=2,n--) a[i]=1;//把客人交错开来
	for(int i=1;i<=m && n;i+=2,n--) a[i]=1;//如果客人分完了，就不会执行这行
	a[0]=a[m];
	a[m+1]=a[1];//方便后面的判断
	for(int i=1;i<=m;i++){
		if(a[i]) ans+=a[i-1]+a[i+1];
	}
	cout<<ans;
	return 0;
} 
```


---

## 作者：Vitamin_B (赞：1)

[题目传送门](/problem/P9585)
# 思路
这题我们分情况考虑：
1. 当 $n\times2\le m$ 时，我们只要间隔着放人就可以了，产生 $0$ 愤怒值；
1. 当 $m$ 为奇数时，先间隔着放 $\lceil\frac m2\rceil$ 个人，产生 $2$ 愤怒值，剩下的人放间隔里，每放一个人就会增加 $4$ 愤怒值，总共会产生 $2+4\times(n-\lceil\frac m2\rceil)$ 的愤怒值，简化一下就是 $n\times4-m\times2$。
1. 当 $m$ 为偶数时，先间隔着放 $\frac m2$ 个人，产生 $0$ 愤怒值，剩下的人放间隔里，每放一个人就会增加 $4$ 愤怒值，总共会产生 $2+4\times(n-\frac m2)$ 的愤怒值，简化一下也是 $n\times4-m\times2$。

# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
int n, m;
int main () {
	cin >> n >> m；
	cout << max (4 * n - 2 * m, 0);
	return 0;
}
```

---

## 作者：glx123 (赞：0)

# 分析
如果人数少于房间数除以二（向下取整），输出零，因为可以完全间隔开。
否则，如果房间数是偶数，那么在完全间隔的基础上加人，每加一个，总数加4，而如果是奇数，有个人加总值为二。
# 代码（挺短）
```
#include<bits/stdc++.h> 
using namespace std;
int main(){
	int n,m,ans;
	cin>>n>>m;
	ans=n-m/2;
	cout<<(ans<=0?0:(m&1?(ans-1)*4+2:ans*4));
	return 0;
}
```
思路同上。

---

## 作者：enyyyyyyy (赞：0)

- 
  思路：可以考率一个有人的房间和一个无人的房间一组，由此考虑答案。

-  
   实现：分类讨论。
   
   如果 $2$ 个房间一组搭配可以满足输出 $0$。
   
	如果 $2$ 个房间一组搭配不可以满足条件，将多余的房间记录下个数，输出是 $\times 2$，便为答案。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int main() {
	cin>>n>>m;
	if(n*2<=m){
		cout<<0;
		return 0;
	}
	k=n*2-m;
	cout<<2*k;
	return 0;
}
```


---

## 作者：ChenZQ (赞：0)

直接贪心就好了。

`for` 循环枚举每一次安排的位置，找到怒气值最小的，然后放下去。

最后等到安排好后，枚举数组，看怒气值为多少。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 110;
int flag[N];
int ans;
signed main()
{
	int n,m;scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int mi=4;
		int id=0;
		for(int j=1;j<=m;j++)
		{
			int cnt=flag[(j-1+m)%m]+flag[(j+1)%m];
			if(flag[j]==1) continue;
			if(cnt<mi)mi=cnt,id=j;//贪心，找目前怒气值最小的位置。
		}
		flag[id]=1;//打上标记。
	}
	for(int i=1;i<=m;i++)
	{
		if(flag[i])
		{
			int f=i-1;
			if(f==0) f=m;
			int l=i+1;
			if(l==m+1) l=1;
			ans=ans+flag[f]+flag[l];
		}
	}
	printf("%lld",ans);
}
```

---

