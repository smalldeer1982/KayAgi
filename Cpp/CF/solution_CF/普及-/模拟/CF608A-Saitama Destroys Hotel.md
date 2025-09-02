# Saitama Destroys Hotel

## 题目描述

Saitama accidentally destroyed a hotel again. To repay the hotel company, Genos has volunteered to operate an elevator in one of its other hotels. The elevator is special — it starts on the top floor, can only move down, and has infinite capacity. Floors are numbered from $ 0 $ to $ s $ and elevator initially starts on floor $ s $ at time $ 0 $ .

The elevator takes exactly $ 1 $ second to move down exactly $ 1 $ floor and negligible time to pick up passengers. Genos is given a list detailing when and on which floor passengers arrive. Please determine how long in seconds it will take Genos to bring all passengers to floor $ 0 $ .

## 说明/提示

In the first sample, it takes at least $ 11 $ seconds to bring all passengers to floor $ 0 $ . Here is how this could be done:

1\. Move to floor $ 5 $ : takes $ 2 $ seconds.

2\. Pick up passenger $ 3 $ .

3\. Move to floor $ 3 $ : takes $ 2 $ seconds.

4\. Wait for passenger $ 2 $ to arrive: takes $ 4 $ seconds.

5\. Pick up passenger $ 2 $ .

6\. Go to floor $ 2 $ : takes $ 1 $ second.

7\. Pick up passenger $ 1 $ .

8\. Go to floor $ 0 $ : takes $ 2 $ seconds.

This gives a total of $ 2+2+4+1+2=11 $ seconds.

## 样例 #1

### 输入

```
3 7
2 1
3 8
5 2
```

### 输出

```
11
```

## 样例 #2

### 输入

```
5 10
2 77
3 33
8 21
9 12
10 64
```

### 输出

```
79
```

# 题解

## 作者：Grisses (赞：5)

[题面](https://www.luogu.com.cn/problem/CF608A)

本题是一道简单的模拟题，我们从第 $s$ 层向下遍历，如果在这一层有人，就看能否更新答案。每下一层再将答案加 1 就可以了。

假设我们现在到了第 $i$ 层，到达这一层的时间为 $cnt$，这一层有 $k$ 个人，到达电梯的时间是 $t_{i,j}(1\le j\le k)$。如果 $k$ 等于 0，那就表明这一层没有人，直接跳过。如果这一层有人，假设 $y=\max_{j=1}^{n}{t_{i,j}}$。那么，因为电梯只能往下走，所以我们必须等到最后一个，即 $t=\max(t,y)$。

代码
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  int n,s,ans,cnt=1;
  struct node{
      int a,t;
      bool operator<(const node &b)const{
          return a>b.a;//按楼层从大到小排序
      }
  }a[105];
  signed main()
  {
      scanf("%lld%lld",&n,&s);
      for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].a,&a[i].t);
      sort(a+1,a+n+1);
      for(int i=s;i>=0;i--,ans++){
          while(i==a[cnt].a){
              ans=max(ans,a[cnt].t);
              cnt++;//模拟
          }
      }
      printf("%lld",ans-1);//这里有一个细节就是ans从s到小于0一共加了s+1，但实际上只需要加s。所以要减去1
      return 0;
  }
```

---

## 作者：Jr_Zlw (赞：2)

## CF608A 题解

嗯，这道灰题很水的，我来社区贡献了（~~赚估值了~~）。

首先我们分析一下，这题我是用模拟做的（数学方法亦可，不过我脑子不太好使）具体构思如下;


1.在输入的时候记录好第i层最晚的旅客的到达时间（题目描述怪怪的，不能肯定没有重复楼层的数据出现）用$f_i$表示（取$floor$的意思）。

2.定义一个变量$t$(取$time$的意思)用来记录当前的时间，定义$ans=s$（因为电梯就算不等人也需要$s$秒到达$0$层）

3.倒着从$s$开始循环，i的值即表示当前电梯所在楼层

4.比较当前时间以及当前楼层的最晚时间（即$f_i$的值），如果$f_i$值较大，则说明电梯应该等人。此时多余的时间为该层停留总时间-1，而该层停留总时间即为$f_i-t+1$，所以相抵消以后有多余了($f_i-t$)秒，于是我们给$ans$加上($f_i-t$)（这一小段代特殊值证明亦可），而且使现在的t=$f_i$(因为在第$f_i$秒电梯才继续往下)。如果电梯可以顺畅的往下(即$f_i$值较小）则直接使$t++$过这一层即可。

下面双手奉上$ACcode$

```cpp
#include<bits/stdc++.h>
using namespace std;
int f[1001]; 
int main()
{
	int n,s;
	cin>>n>>s;
	int ans=s,t=0;
	for(int i=1;i<=n;++i)
	{
		int a,b;
		cin>>a>>b;
		f[a]=max(f[a],b);
	}//输入并标记
    for(int i=s;i>=0;--i)
    {
        if(f[i]>t)
        {
        	ans+=(f[i]-t);//加上多余的时间
        	t=f[i];//刷新时间值
		}
		t++;//电梯的正常运营时间
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：WA_sir (赞：1)

## [题目](https://codeforces.com/problemset/problem/608/A)[链接](https://www.luogu.com.cn/problem/CF608A)

本题的关键点：

1. 电梯**只能向下移动**，也就是说，电梯从顶楼 S 往下移动到 $0$ 楼后就不再移动了。所以，**必须在这一次移动中让所有乘客到达 $0$ 楼**。每层楼中，要等到最后一位乘客到达电梯才能继续移动。
1. 电梯**有无限的容量**，表明必定有解，也不需要考虑电梯的承重问题。
1. 电梯需1秒钟就可以向下移动1层楼，说明**每经过一层楼时间就要增加 $1$**。

考虑完关键点，这题的做法就一目了然了。

首先在输入时记录每个楼层最晚到的乘客的到达时间，若没有乘客则记为 $0$。

然后从 S 楼开始依次往低楼层模拟，每经过一层就用现在的时间 $t$ 与当前楼层到达最晚的乘客所到的时间取最小值。

最后直接输出时间 $t$ 就好了。

## 代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,s,a[1005],t;
int main()
{
	scanf("%d%d",&n,&s);
	for(int i=1;i<=n;i++)
	{
		int ax,ay;
		scanf("%d%d",&ax,&ay);
		a[ax]=max(a[ax],ay);//每层楼乘客所到时间最大值
	}
	for(int i=s;i;i--,t++)t=max(t,a[i]);//模拟
	printf("%d",t);
	return 0;
}
```
感谢阅读，写得不好请见谅！

---

## 作者：VitrelosTia (赞：0)

题链：[CF](https://codeforces.com/contest/608/problem/A)/[Luogu](https://www.luogu.com.cn/problem/CF608A)

### 题意
电梯从 $s$ 层到 $0$ 层只往下走，有 $n$ 个人要坐电梯要到 $0$ 层并且必须搭载完这些人，每个人给你所在的楼层和来搭电梯的时间，求最少多少时间能把这些人搭载到 $0$ 层？

### 思路
首先由于电梯只往下走，所以必须从上往下等到这层楼的人来齐了再到下一层。

每层楼的情况只有两种，一是电梯来了人没到，二是人来了电梯没到，每层楼的两种情况中取最大值即可。

### code
```
#include <bits/stdc++.h>
using namespace std;
int n,s;
struct node {int lc,tim;}a[105];
bool cmp(node x,node y){return x.lc>y.lc;}
int ans;
int main(){
	cin>>n>>s;
	for(int i=1;i<=n;i++) cin>>a[i].lc>>a[i].tim;
	sort(a+1,a+n+1,cmp);
	a[0].lc=s;
	for(int i=1;i<=n;i++){
        ans+=abs(a[i-1].lc-a[i].lc);
        ans=max(ans,a[i].tim);
    }
	cout<<ans+a[n].lc;
}
```


---

## 作者：cqbzjyh (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF608A)

### Solution.

因为电梯不能向上移动，这道题就变成了一道模拟题。

如果电梯到了但人没到，电梯就必须等人。

如果人到了但电梯没得，人就必须等电梯。

在这两种情况中取一个最大值即可。

需要从小到大排序。

### Code.

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
template <typename T>
void read(T &x) {
	x = 0; T f = 1;
	char c;
	c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 1) + (x << 3) + c - '0';
		c = getchar();
	}
	x *= f;
} 

int n, s;
struct node {
	int t, r;
} a[105];
bool cmp(node x, node y) {
	return x.t > y.t;
}
int ans;
signed main() {
	read(n), read(s);
	for (int i = 1; i <= n; i++) {
		read(a[i].t), read(a[i].r);
	}
	stable_sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		ans = max(ans + s - a[i].t, a[i].r);
		s = a[i].t;
	}
	printf("%d", ans + s);
    return 0;
}
```

---

## 作者：yangzd (赞：0)

# 题目大意

一共有 $n$ 个人，$s$ 层高的大楼，电梯起初在顶层 $S$；每个人所在楼层和到达电梯口的时间可能不同，求把所有人 带到底楼（就是 $1$ 层），所用的最小时间。

# 分析

从顶楼开始往一楼接人 电梯只降不升，如果在该层的人还没来 就等到他来，原因是因为：就算你先下去接先到的人，但是你还是要返回来接高楼层的人，如果返回用的时间太大,大于高楼层人到达楼梯口时间那就错了。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
 
struct node
{
    int f;
    int t;
};
 
bool cmp(node a,node b)
{
    return a.f>b.f;
}
 
signed main()
{
	ios::sync_with_stdio(0);
	
    int n,s;
    struct node a[205];
    
	cin >> n >> s;
	
    for(int i=1; i<=n; i++)
        cin >> a[i].f >> a[i].t;
        
    sort(a+1,a+n+1,cmp);
    
    int ans=0;
    
    a[0].f=s;
    
    for(int i=1; i<=n; i++)
    {
        ans=ans+abs(a[i-1].f-a[i].f);
        
        if(ans<a[i].t)
            ans=a[i].t;
    }
    
    cout << ans+a[n].f << endl; 
    
    return 0;
}
```

---

