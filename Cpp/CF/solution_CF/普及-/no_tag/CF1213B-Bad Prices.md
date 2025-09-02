# Bad Prices

## 题目描述

Polycarp analyzes the prices of the new berPhone. At his disposal are the prices for $ n $ last days: $ a_1, a_2, \dots, a_n $ , where $ a_i $ is the price of berPhone on the day $ i $ .

Polycarp considers the price on the day $ i $ to be bad if later (that is, a day with a greater number) berPhone was sold at a lower price. For example, if $ n=6 $ and $ a=[3, 9, 4, 6, 7, 5] $ , then the number of days with a bad price is $ 3 $ — these are days $ 2 $ ( $ a_2=9 $ ), $ 4 $ ( $ a_4=6 $ ) and $ 5 $ ( $ a_5=7 $ ).

Print the number of days with a bad price.

You have to answer $ t $ independent data sets.

## 样例 #1

### 输入

```
5
6
3 9 4 6 7 5
1
1000000
2
2 1
10
31 41 59 26 53 58 97 93 23 84
7
3 2 1 2 3 4 5
```

### 输出

```
3
0
1
8
2
```

# 题解

## 作者：cqbztz2 (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1213B)

[不会更好的阅读体验](https://www.luogu.com.cn/blog/493271/solution-cf1213b)

# Thinking

观察时间复杂度 $ 1 \leq 10^4 , 1 \leq 150000 $，输入的时间复杂度为 $ O(T $ $ n ) $，因此最终的时间复杂度只能为 $ O(T $ $ n ) $。

要想一天的售价是“合算的”，要满足当前这天的售价为后面所有天的售价的最小值。

而求最小值只能用 $ O(n) $ 的算法，因此倒着遍历一次即可。

时间复杂度 $ O(T $ $ n ) $。

预计得分 $ 100 $ $ pts $

# Coding

```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int T,n,a[150005],ans,minn;
  signed main(){
      cin>>T;
      while(T--){
          minn=INT_MAX,ans=0;
          cin>>n;
          for(int i=1;i<=n;++i) cin>>a[i];
          for(int i=n;i>=1;--i){
              if(a[i]>minn) ++ans;
              else minn=a[i];
          }
          cout<<ans<<endl;
      }
      return 0;
  }
```


---

## 作者：andyli (赞：2)

题意：计算序列$a$中满足$a_i=min\{a_j, j\in [i,n]\}$的个数。  
使用类似滑动窗口的方法，每次输入数字时把队列中弹出所有比这个数字大的数，答案就是弹出的次数。注意需要使用优先队列。  
代码如下：  
```cpp
#include <cstdio>
#include <queue>
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        priority_queue<int> q;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            while (!q.empty() && x < q.top())
                q.pop(), ans++;
            q.push(x);
        }
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：GIFBMP (赞：2)

这题窝一开始想到了暴力，然后发现不行。

然后我发现，可以倒着扫一遍，判断这个数是否大于当前最小值，同时记录下当前最小值，就可以了。

Code:

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
int t,n,a[150010],b[150010],c[150010];
int min(int a,int b){
	return a<b?a:b; 
}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		int ans=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		int minn=2147483647;
		for(int i=n;i;i--){
			if(a[i]>minn)
				ans++;
			minn=min(minn,a[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：pandaSTT (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1213B)

[更好的阅读体验？](https://www.luogu.com.cn/blog/557117/solution-cf1213b)

## 思路

首先可以想到一个 $ O(n^2) $ 的算法，即对于每天都遍历查找一次，与在当天后所有天进行比较。

观察 $ n $ 的数据范围， $ 1 ≤ n ≤ 150000 $ ，显然 $ O(n^2) $ 的算法会超时，考虑优化。

与在当天后所有天进行比较，可以转化为与当天后所有天的最小值进行比较，而我们只需要预处理每天后的所有天的最小值即可，即倒着枚举天，一边枚举一边更新最小值。

时间复杂度 $ O(n) $ ，得分 $ 100 pts $ 。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline char gc(){
	static char buf[1000010],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000010,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	register int x=0,f=0;
	static char s=gc();
	while(s<'0'||s>'9')f|=s=='-',s=gc();
	while(s>='0'&&s<='9'){
		x=(x<<3)+(x<<1)+(s^48);s=gc();
	}return f?-x:x;
}
inline void write(register int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);putchar(x%10^48);
}//卡最优解用的
const int N=150005;
int t,n,a[N],ans,minn;
signed main(){
	t=read();
	while(t--){
		minn=0x3f3f3f3f;
		ans=0;
		n=read();
		for(int i=1;i<=n;a[i++]=read());
		for(int i=n;i>=1;i--){//倒着更新最小值
			if(a[i]>minn){
				ans++;
			}
			else{
				minn=a[i];
			}
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：Fan_Tuan (赞：1)

# 思路
用一个栈维护序列， $x$表示要进栈的元素， 如果它比栈顶大， 则说明栈顶元素是不合算的， $ans$++, 栈顶元素出栈， 一直到栈顶元素小于等于$x$为止，最后将$x$入栈。最终求得$ans$。
# 代码
```c
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
// #define d lld
// #define int long long
using namespace std;

int t, n;
 
signed main () {
    scanf ("%d", &t);
    while (t--) {
        stack<int> a;
        scanf ("%d", &n);
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            scanf ("%d", &x);
            while (!a.empty()) {
                int p = a.top();
                if (p > x) a.pop(), ans++;
                else break;
            }
            a.push(x);
        }
        printf ("%d\n", ans);
    }
    return 0;
}
```


---

## 作者：Ybocean_s (赞：0)

**题意**：给出每天售价，根据定义求出有几天的售价是不合理的。

------------
**思路**：根据“我们定义一天的售价是不合算的如果在他这一天后面的某一天中这个物品的售价小于这个物品这一天的售价，求有多少天的售价是不合算的”，进行思考，可以想到从后面开始进行循环，找出一个最小值，并不断更新最小值，若该天大于最小值，不合算的天数就多一天。

------------
**注意**：数据多组，按照题意输入输出，每次使用完的计数变量要归零再次使用。

------------
代码：

```cpp
#include<iostream>
using namespace std;
const int MAX=150000+1;
int a[MAX];
int main()
{
	int f,n,js=0;
	cin>>f;//数据组数。
	for(int l=1;l<=f;l++){
		cin>>n;//天数
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		int minn=999999999;//尽可能开大，方便后面比较。
		for(int i=n;i>=1;i--){
			if(a[i]>minn){//判断。
				js++;
			}
			minn=min(minn,a[i]);//更新最小值。
		}
		cout<<js<<endl;
		js=0,minn=999999999;//使用完归原。
	}
	return 0;
}
```
撒花。

---

## 作者：孑彧 (赞：0)

## B.Bad Prices

### 题意描述

有一个物品销售了$n$天，第$i$天的售价为$c_i$。我们定义一天的售价是“不合算的”如果在他这一天后面的某一天中这个物品的售价小于这个物品这一天的售价。求有多少天的售价是“不合算的”。

### 思路

假如一个数后面有比他小的，那么他就是不合算的数

所以我们想要知道每一个数后面是否有比它小的

于是我们就可以从后向前扫一遍，维护一个最小值，当当前的数大于最小值时，答案便累计，如果小于最小值，便更新我们的最小值

### 代码

```c++
#include<cstdio>
#include<iostream>
#include<cstring>
#define maxn 170000
using namespace std;
int T,n;
int a[maxn];
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		} 
		int now=10000000;
		int ans=0;
		for(int i=n;i>=1;i--){
			if(a[i]>now){
				ans++;
			}
			now=min(now,a[i]);
		}
		printf("%d\n",ans);
	}
}
```

---

## 作者：B_Qu1e7 (赞：0)

逆序对简化版。

分析题意可知，此题目标是求满足$a_i>a_j$并且$i<j$的$i$的数量。

由于是求$i$的数量而不是求$(i,j)$的个数，可以用一种简单的做法：

从后往前扫一遍，如果小于等于（也可以只小于，但这里方便$else$）当前最小值则更新，否则$ans+1$。

代码如下：

```
#include<cctype>
#include<cstdio>
int T,N,mini,x[150005],ans;
template<class D>inline void read(D &m)//无脑read
{
	m=0;
	char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))m=(m<<3)+(m<<1)+(c&15),c=getchar();
}
int main()
{
	read(T);
	while(T--)
	{
		read(N);
		mini=1000001;
		ans=0;
		for(int i=1;i<=N;++i)
		{
			read(x[i]);
		}
		while(N)
		{
			if(x[N]<=mini)
			{
				mini=x[N];
			}
			else
			{
				ans++;
			}
			N--;
		}
		printf("%d\n",ans);
	}
}
```

---

