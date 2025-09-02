# [ARC162A] Ekiden Race

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc162/tasks/arc162_a

$ 1 $ から $ N $ までの番号がつけられた $ N $ 人の人がある地点間を往復するレースを行いました。このレースについて、以下の情報が残されています。

- **往路**のタイムの早い順に順位をつけると、どの $ 2 $ 人のタイムも異なっており、人 $ i\ (1\ \leq\ i\ \leq\ N) $ は $ i $ 位であった。
- **往復**のタイム（往路のタイムと復路のタイムの合計）の早い順に順位をつけると、どの $ 2 $ 人のタイムも異なっており、人 $ i\ (1\ \leq\ i\ \leq\ N) $ は $ P_i $ 位であった。
- **復路**のタイムが最も早かった人（複数人いる場合はその全員）に**復路の区間賞**が与えられた。
 
ここで、$ P_1,\ P_2,\ \dots,\ P_N $ は $ 1,\ 2,\ \dots,\ N $ の並べ替えです。

このとき、**復路の区間賞**を与えられた可能性のある人は何人いるでしょうか？

$ T $ 個のテストケースが与えられるので、それぞれについて答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 500 $
- $ 2\ \leq\ N\ \leq\ 10^3 $
- $ P_1,\ P_2,\ \dots,\ P_N $ は $ 1,\ 2,\ \dots,\ N $ の並べ替えである
- 入力される数値は全て整数
- $ 1 $ つの入力に含まれるテストケースについて、$ N $ の総和は $ 10^3 $ 以下
 
### Sample Explanation 1

\- $ 1 $ つ目のテストケースでは、$ 2 $ 人でレースを行い、復路において人 $ 2 $ が人 $ 1 $ を抜かしています。この場合、復路の区間賞は人 $ 2 $ に与えられます。 - $ 2 $ つ目のテストケースでは、復路で順位が変動しておらず、どの人も復路の区間賞が与えられた可能性があります。

## 样例 #1

### 输入

```
3
2
2 1
4
1 2 3 4
20
13 2 7 1 5 9 3 4 12 10 15 6 8 14 20 16 19 18 11 17```

### 输出

```
1
4
7```

# 题解

## 作者：Sammy_prime (赞：3)

[ AT_arc162_a](https://www.luogu.com.cn/problem/AT_arc162_a)

# 思路
根据提供的描述，对于 $i$，如果存在某个 $i < j$，使得 $ P_i > P_j $，那么 $j$ 在回程途中超过了 $i$，因此 $i$ 肯定不能获得回程将。所以答案就是 $P$ 的的后缀最小元素的个数。
这种算法的时间复杂度是 $O(N)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int t,n,p[N]; 
int main(){
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
	scanf("%d",&t);
	while(t--){
		int ans=0,mn=N;
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",p+i);
		for(int i=n;i>0;--i)
			if(p[i]<mn) ans++,mn=p[i];
		printf("%d\n",ans);
	}
	return 0;
}

```





---

## 作者：linch (赞：2)

看到大佬们用的都是 C++，本蒟蒻就来篇 Python 的。

## 题意
简单来说，先输入一个整数 $t$，有 $t$ 组数据。每组数据有 $n$ 个人参加赛跑。我们可以反向思考：如果跑在一个人后面的人名次比前面还要好。那就说明这个人“復路”很慢，不可能拿到奖。

## 解决
既然如此，而且数据极小，$ 1\ \leq\ T\ \leq\ 500 $，$ 2\ \leq\ N\ \leq\ 10^3 $。$O(T\times N)$ 的复杂度肯定能过，直接模拟即可。

对于每组数据，先从 $1$ 循环到 $n$，枚举判断是否得奖：每次遍历他后面的人的成绩，判断如果没有跑在他后面的人比他用时更短，就说明这个人“復路”很快，直接将变量加一。每组数据遍历完成后输出。

## 代码
```python
t=0
# 输入组数。
t=int(input())
# 有 t 组数据，循环 t 次。
for i in range(t):
    # 每次输入人数。
    n=int(input())
    # 输入每个人的成绩到 a 数组中。
    a=list(map(int,input().split()))
    # 注意每组数据要清空。
    ans=0
    for j in range(n):
        # 每次都要初始化，False 代表没有后面的人总用时比第 j 个人短。
        y=False
        # 遍历当前排名在他后面的人。
        for k in range(j+1,n,+1):
            # 如果有后面的人总用时比第 j 个人短。
            if a[k]<a[j]:
                # 标记为 True。
                y=True
        # 如果没有跑在他后面的人比他用时更短，ans 变量加一。
        if y==False:
            ans=ans+1
    # 输出答案即可。
    print(ans)
```

---

## 作者：zhicheng (赞：1)

### 题意简述

$N$ 个人参加一个比赛，以 $1\sim N$ 的顺序出发，结束时第 $i$ 个人为第 $P_i$ 名，求有多少个人可能用时最短。

### 思路

因为出发时是按编号从小到大走的，所以结束时要是被比自己编号大的人超了就不可能最快，反之可能。所以我们先把每个人的名次换为最终的顺序，也即换成最后 $1\sim N$ 名分别是哪些人（$a_{p_i}\gets i$），再比较一个人的前面是否有编号比自己大的。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1010],p[1010];
int main(){
	int t,n,ans,maxx;
	scanf("%d",&t);
	while(t--){
		ans=maxx=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&p[i]);
			a[p[i]]=i;  //先把每个人的名次换为最终的顺序
		}
		for(int i=1;i<=n;i++){
			if(a[i]>maxx){  //是否被超了
				ans++;
			}
			maxx=max(a[i],maxx); //记录编号最大的
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：SunSammy (赞：0)

[AT_arc162_a](https://www.luogu.com.cn/problem/AT_arc162_a)

# 本题题意

根据题目描述，就是求有多少个人后面没有比他速度更快的人，那么这个人就获得了奖项。

# 本题思路

因为本题的数据很水，所以暴力枚举即可通过。

## 我的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n;
int main(){
	freopen("race.in","r",stdin);
	freopen("race.out","w",stdout);
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int ans=0,x;
		int a[100005];
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++){
			bool f=1;
			for(int j=i+1;j<=n;j++){
				if(a[i]>=a[j]){
					f=0;break;
				}
			}
			if(f)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Lavande (赞：0)

# 题目

[更好的阅读体验](https://www.luogu.com.cn/problem/AT_arc162_a)

# 思路

本题就是在求有多少个数后面没有比它小的数的个数。数据范围不大，我们可以直接暴力枚举。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, ans, f;
int a[10005]; //稍微开大一些 
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(false);
	cin >> t;
	while(t --){
		cin >> n;
		ans = 0, f = 0;
		//输出 
		for(int i = 1; i <= n; i ++){
			cin >> a[i];
		}
		//枚举比a[i]小的数的个数 
		for(int i = 1; i <= n; i ++){
			f = 0;
			for(int j = i + 1; j <= n; j ++){
				if(a[j] < a[i]){
					f = 1;
				}
			}
			if(!f) ans ++;
		}
		//输出 
		cout << ans << endl;
	}
	return 0;
}

```


---

## 作者：awdereye (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_arc162_a)
### 时间复杂度
本题的 $T \le 500$，$N \le 10 ^ 3$，所以本题时间复杂度为 $O(T \times N)$ 所以本题暴力可行。
### 解题思路
本题直接暴力枚举 $i$ 后面的所有人的復路的成绩，如果都没 $i$ 小的话 $i$ 就获得了復路奖项，而第 $N$ 个人由于后面压根没有人和他比较，直接加一即可。

- 注意每一次都要及时清空记录。

### 规则证明
输入的第二组样例为 `4 1 2 3 4`，输出结果为 `4` 。因为这 4 个人每一个人后面的人的復路的成绩都比自己大，所以说每个人都获得了復路奖项。
### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
long long cnt=0;
struct node{
		int p1;
}p[1005];
int main(){
		scanf("%d",&t);
		for(int i=1;i<=t;i++){
			int cnt=0;
			memset(p,0,sizeof(p));//清空
			scanf("%d",&n);
			for(int i=1;i<=n;i++){
				scanf("%d",&p[i].p1);
			}
			for(int i=1;i<=n-1;i++){//n不再进入循环（双层结构类似选择排序）
				bool f=1;
				for(int j=i+1;j<=n;j++){
						if(p[i].p1>=p[j].p1){
						f=0;
						break;
					}
				}
				if(f){
					cnt++;
				}
			}
			printf("%d\n",cnt+1);//注意换行
		}
		return 0;
} 
```

---

## 作者：beifa (赞：0)

## 写在最前
~~本题暴力出奇迹即可。~~ 欲知思路如何，且听下文分解。
## 思路：
首先我们不妨反着想：如果一个人拿不到“奖项”，需要满足什么条件？

显然如果跑在他后面的人最终名次比他好，那么他一定拿不到奖项，将他排除即可。

鉴于 $n$ 的范围比较小，直接暴力就能过。
#### 如何暴力？
其实很简单，嵌套循环，外循环枚举每一个人，内循环从 $i+1$ 开始一直到 $n$，表示在“往路”中跑的比第 $i$ 个人慢的，如果 $p_i$ 最后还比 $p_j$ 大，说明第 $i$ 个人在“返路”没有跑过第 $j$ 个人（因为“往路”快，“总路”慢，则“返路”一定慢），则这个人一定不会拿到奖项，排除即可。
## CODE:
```cpp
#include <bits/stdc++.h>
using namespace std;

int t , n;

signed main()
{
	cin >> t;
	while(t--)
	{
		cin >> n;
		int a[n+1];
		for(int i = 1 ; i <= n ; ++i)
		{
			cin >> a[i];
		}
		int ans = 0;
		for(int i = 1 ; i <= n ; ++i)
		{
			int f = 1;
			for(int j = i+1 ; j <= n ; ++j)
			{
				if(a[j] < a[i]) f = 0;
			}
			if(f == 1) ans++;
		}
		cout << ans << '\n';
	}
	return 0;
}
```


---

## 作者：code_hyx (赞：0)

这题就是不要想复杂了。  
考虑两个人的情况，如果第一个人比第二个人前半程跑得快，结果全程第一个人反而比第二个人跑得慢，那么第一个人的后半程一定比第二个人跑得慢，否则后半程就有可能跑得更快。  
而前半程的排名就是每个人的编号，所以该题转化为：求有多少个数，后面没有比它更小的数。  
代码：
```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[1005];
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		int cnt=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=n;i++)
		{
			bool flag=true;
			for(int j=i+1;j<=n;j++)
			{
				if(a[j]<a[i])
				{
					flag=false;
					break;
				}
			}
			if(flag==true)
			{
				cnt++;
			}
		}
		cout<<cnt<<"\n";
	}
	return 0;
} 
```


---

## 作者：KυρωVixen (赞：0)

## 题意：
一次折返跑，已知到达折返点时处于 $1 \sim N$ 名的人整个赛程结束时的名次，求返回时最多能有多少人回程速度并列第一。

数据范围：$T$ 组数据，$T\le 500$，$N\le 10^3$，$\sum N\le10^3$。
## 解法：
可以很明显地想到：对于每一个人向后枚举，只要没有一开始落后他的人在回程超过他，那他就可能回程速度并列第一。证明方法有待补充，但是手模样例即可看出。

直接模拟即可。
## 代码
```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define Puts(x) cout<<x<<'\n'
using namespace std;
int n,a[1005];
void exec(){
	int ans=0; cin>>n;
	rep(i,1,n) cin>>a[i];
	rep(i,1,n){
		bool flag=1;
		rep(j,i+1,n) if(a[i]>a[j]) flag=0;
		ans+=flag;
	}
	Puts(ans);
}
signed main(){
	int t; cin>>t; while(t--) exec();
}
```

---

