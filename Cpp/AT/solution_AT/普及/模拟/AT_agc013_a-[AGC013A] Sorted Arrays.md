# [AGC013A] Sorted Arrays

## 题目描述

## 题目翻译
给出长度为N的数列A，你需要把A划分成几个连续子串，要求每个子串都为单调不降子串或单调不升子串，求子串的最少个数。

## 样例 #1

### 输入

```
6
1 2 3 2 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
9
1 2 1 2 1 2 1 2 1```

### 输出

```
5```

## 样例 #3

### 输入

```
7
1 2 3 2 1 999999999 1000000000```

### 输出

```
3```

# 题解

## 作者：xieyikai2333 (赞：1)

# 提供一种简单的方法

- [题目传送门](https://www.luogu.com.cn/problem/AT4864)

- 代码很短，只有 $20$ 行左右，适合初学者食用。

---

### 做法概述

1. 我们需要对数列进行**去重**；

- 因为对于相邻的两个数，如果它们相等，那么它们一定可以在同一个子串里。

2. 这里包含了一个**贪心**的思想：如果两个数可以在一个子串里，那么我们必定把它们放到一个子串里；

- 贪心证明：

	选择一：对于两个相邻的，可以被放在一个子串里的数，如果我们把它们分开，那么总数必定加一；
    
   选择二：而如果我们把它们放在一个子串里，虽然可能使下一个数无法和当前的数放入同一个子串，但是总数最多也就加一，甚至可能更优。
   
   综上，选择二一定不会比选择一差。
   
---

### 具体做法

1. 对数列去重；

2. 定义一个变量 $flag$：

- $flag=0$：当前子串是一个单调不降子串；

- $flag=1$：当前子串是一个单调不升子串；

- $flag=2$：当前为子串的第一个数，子串类型待确定。

3. 若 $flag=2$，子串类型由下一个数和该数（子串的第一个数）之间的大小关系来决定；

	否则，如果下一个数不符合该子串类型，那就把 $flag$ 赋值为 $2$，并且把结果加上一。
    
---
### 代码实现

- 代码经过简化，简洁明了。

**AC 代码**：

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100005];
int main()
{
	int n,tot=1,flag=2,ans=1;
	scanf("%d %d",&n,&a[1]);
	for(int i=2;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if(x!=a[tot])a[++tot]=x;
	}
	for(int i=2;i<=tot;i++)
	{
		if(flag==2)flag=(a[i-1]>a[i]);
		else if(flag!=(a[i-1]>a[i]))flag=2,ans++;
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：qwcdim (赞：1)

## AT2367 [AGC013A] Sorted Arrays 题解

[安利博客](https://www.luogu.com.cn/blog/I-like-10/)

[题目传送门](https://www.luogu.com.cn/problem/AT2367)

### 思路
题目让我们求出不同的**单调不降子串**或**单调不升子串**的个数有多少。可以直接输入，然后从头到尾扫一遍，（因为子串的**顺序不变**，而且  $\texttt{string}$ 类型的排序是按照字典序排的，这样就可以把子串的长度忽略了。可以自己拿几个数据看看），用两个 $\texttt{bool}$ 类型的变量存储现在是上升还是下降。具体看代码。

### 高清可直接食用代码
```cpp
#include<iostream>
#include<cstdio>
#include<stdio.h>
using namespace std;
long long n,a[100010],ans;
bool shang,xia;
inline void check(int hhh){//判断当a[i],a[i+1]相同时，需要向下继续寻找是上升还是下降
	for(int i=hhh;i<=n;i++){
		if(a[i]<a[i+1]){
			shang=true;
			return;
		}else if(a[i]>a[i+1]){
			xia=true;
			return;
		}else continue;
	}
	return;
}
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=n;i++){
		if(i==n) break;//因为a[n]一定会小于a[n+1],所以特判
		if(shang==false&&xia==false){//判断是上升还是下降
			if(a[i]<a[i+1]) shang=true;//上升
			else if(a[i]>a[i+1]) xia=true;//下降
			else check(i);//相同
		}
		if(shang==true){
			if(a[i]>a[i+1]){///如果下降了
				ans++;//个数++
				shang=false;//设为false
			}
		}else{
			if(a[i]<a[i+1]){//同上
				ans++;
				xia=false;
			}
		}
	}
	printf("%lld",ans+1);//输出是要加1，自己可以用数据看看
	return 0;//完美的结束
}
```


---

## 作者：Su_Zipei (赞：1)

观察性质，发现是子串，子串有什么好处呢，就是连续的，所以尽量让每个段最长应该是一个最优决策。

原因在于，这个段如果被分开那么答案不会更优，由决策包容性可知，这样得到的是最优解。

```
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main(){
	int n;
	scanf("%d",&n);
	int typ=0,lst,res=1;
	scanf("%d",&lst);
	for(int i=2;i<=n;i++){
		int x;
		scanf("%d",&x);
		if(x==lst)continue;
		if(typ==0){
			if(x>lst)typ=1;
			else typ=2;
			lst=x;
		}else if(typ==1){
			if(x>lst)lst=x;
			else res++,typ=0,lst=x;
		}else {
			if(x<lst)lst=x;
			else res++,typ=0,lst=x;
		}
	}
	printf("%d\n",res);
	return 0;
}

```

---

## 作者：我是蒟弱 (赞：1)

## 模拟状态

#### 纵观样例：

*样例1*
```
input ：
6
1 2 3 3 2 1

分段：
6
1 2 3（上升）|3 2 1（下降）

两段，故输出2
```
*样例2*
```
input ：
9
1 2 1 2 1 2 1 2 1

分段：
9
1 2 （上升）|1 2 （上升）|1 2 （上升）|1 2 （上升）|1（上升/下降）

五段，故输出5
```
*样例3*
```
input ：
7
1 2 3 2 1 999999999 1000000000

分段：
7
1 2 3 （上升）|2 1 （下降）|999999999 1000000000（上升）

三段，故输出3
```
那么就是，一种数列到了头就要换一种数列，然后统计数列个数

具体操作见代码（写了好多注释~注释~注释~）
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
struct node{
	int x,note=0x3f;//x代表数字，note表示状态，是上升还是下降
	//note=0，下降序列；note=1，上升序列；note=2，起点 或 起点后不明上下的点 
}a[100005]; //声明一个数组 
int main(){//主函数 
	int n,ans=1;//n个数，ans统计答案 
	cin>>n;//输入个数 
	for(int i=1;i<=n;i++){//挨个输入 
		cin>>a[i].x;//把数输入 
	}
	a[1].note=2;//第一个数必然是起点，打好状态标记 
	for(int i=2;i<=n;i++){//从第二个数开始找状态 
		if(a[i-1].note==0){//前一个数状态为0（下降） 
			if(a[i].x>a[i-1].x) a[i].note=2,ans++;//如果不下降了，这个数就是下一个序列的起点，序列数++ 
			else a[i].note=0;//下降，标记成0 
		}else if(a[i-1].note==1){//前一个数状态为1（上升） 
			if(a[i].x>=a[i-1].x) a[i].note=1;//继续上升，标记成1 
			else a[i].note=2,ans++;//不上升了，标记成起点，序列数++ 
		}else if(a[i-1].note==2){//是起点或起点后的不明点（统一当起点即可） 
			if(a[i].x<a[i-1].x) a[i].note=0;//比前一个数小，证明是下降序列，标为0 
			else if(a[i].x==a[i-1].x) a[i].note=2;//相等，这个点是不明上升/下降的点 
			else a[i].note=1;//上升，标成1 
		}
	}
	cout<<ans<<endl;//输出（换行） 
	return 0;
}

```

---

## 作者：Electro_Master (赞：0)

这里给出一种动态规划解法。

序列 DP，当前状态又有两种，很容易想到的方程是 $dp_{i,0/1}$。

$dp_{i,0}$ 表示当前考虑到第 $i$ 个数了，当前子序列为单调不增序列的最少连续子串数，$dp_{i,1}$ 表示当前考虑到第 $i$ 个数了，当前子序列为单调不降序列的最少连续子串数。

有三种转移：

$\texttt{Case 1:}$ $a_{i-1}=a_i$ 

此时 $dp_{i,0}$ 有两种决策：
- 继续上一个数延伸的单调不增子序列，即 $dp_{i-1,0}$；
- 上一个数的单调不降子序列结尾，新开一个单调不增子序列，即 $dp_{i-1,1}+1$；

同理，$dp_{i,1}=\min(dp_{i-1,0}+1,dp_{i-1,1})$。


$\texttt{Case 2:}$ $a_{i-1}<a_i$


此时 $dp_{i,0}$ 有两种决策：
- 新开一个单调不增子序列，即 $dp_{i-1,0}+1$；
- 上一个数的单调不降子序列结尾，新开一个单调不增子序列，即 $dp_{i-1,1}+1$；

同理，$dp_{i,1}=\min(dp_{i-1,0}+1,dp_{i-1,1})$。

$\texttt{Case 3:}$ $a_{i-1}>a_i$


此时 $dp_{i,1}$ 有两种决策：
- 新开一个单调不降子序列，即 $dp_{i-1,1}+1$；
- 上一个数的单调不增子序列结尾，新开一个单调不降子序列，即 $dp_{i-1,1}+1$；

同理，$dp_{i,0}=\min(dp_{i-1,0},dp_{i-1,1}+1)$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=100005;
int n,a[maxn];
int dp[maxn][2];
int main()
{
    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;++i) cin>>a[i];
    dp[1][0]=dp[1][1]=1;
    for(int i=2;i<=n;++i) {
        if(a[i-1]==a[i]) {
            dp[i][0]=min(dp[i-1][0],dp[i-1][1]+1); 
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]+1);
        }
        if(a[i-1]<a[i]) {
            dp[i][0]=min(dp[i-1][0]+1,dp[i-1][1]+1);
            dp[i][1]=min(dp[i-1][1],dp[i-1][0]+1);
        }
        if(a[i-1]>a[i]) {
            dp[i][0]=min(dp[i-1][0],dp[i-1][1]+1);
            dp[i][1]=min(dp[i-1][1]+1,dp[i-1][0]+1);
        }
    }
    cout<<min(dp[n][0],dp[n][1])<<endl;
    return 0;
}
```


---

## 作者：tribool4_in (赞：0)

题意就是说把一个数组切成尽可能少的几段，每一段都是单调不降或单调不增的。

显然，要想使得段数最少，每一段都必须尽可能长，然后就可以遍历一遍，每次贪心考虑 **单调不降** 或 **单调不增** 两种情况，取尽可能长的一种即可。

代码：

```cpp
// Code By WLS
#include <bits/stdc++.h>
const int N = 1e5 + 5;
using namespace std;
inline int read() {
	int s=0, w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int n, a[N];
signed main() {
	n = read();
	for (int i = 1; i <= n; i++) {
		a[i] = read();
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		int aa = 0, bb = 0;
		for (int j = i + 1; j <= n; j++) { // 单调不降
			if (a[j - 1] > a[j]) {
				aa = j - 1;
				break;
			}
		}
		if (aa == 0) aa = n; // 取到末尾
		
		for (int j = i + 1; j <= n; j++) { // 单调不增
			if (a[j - 1] < a[j]) {
				bb = j - 1;
				break;
			}
		}
		if (bb == 0) bb = n; // 取到末尾
		
		i = max(aa, bb), cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}

```


---

## 作者：houpingze (赞：0)

~~蒟蒻又来水题解了~~

这题还算简单吧，就是枚举i，每次让i增加到：

`i以后可以组成的最多的连续的不上升字串的长度`和`i以后可以组成的最多的连续的不下降字串的长度`的最大值

具体见注释：
```cpp
#include<iostream> 
using namespace std; 
int n,cnt,m,a[100010],ans,tmp;
string s;
int s1(int x){//求i以后可以组成的最多的连续的不下降字串 
	for(int j=x+1;j<=n;j++){  
		if(a[j]<a[j-1]) return j-1;//不符合条件了 
	}
	return n;//i~n是一个 连续的不下降字串 
} 
int s2(int x){//求i以后可以组成的最多的连续的不上升字串 
	for(int j=x+1;j<=n;j++){ 
		if(a[j]>a[j-1]) return j-1;//不符合条件了 
	}
	return n;//i~n是一个 连续的不上升字串
} 
int main() { 
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];//读入 
	for(int i=1;i<=n;i++){
		i=max(s1(i),s2(i));//两者求最大，让i直接赋此值 
		cnt++;  //又多了一个字串 
	}  
	cout<<cnt;//输出答案 
	cout<<endl;
    return 0;
}
```

---

## 作者：槑小杨 (赞：0)

楼上那位大佬分析的好啊QAQ

**那我直接设一个变量表示当前是上升还是下降还是混沌，然后如果下一个观测目标与当前不符合就刷新，如果不一样了就把混沌弄成上升或者下降即可。**

但是大佬给的是Py的代码，那我再来一发C的吧QAQ

![](https://cdn.luogu.com.cn/upload/image_hosting/l1qyzpie.png)

---

