# Minimize Distance

## 题目描述

A total of $ n $ depots are located on a number line. Depot $ i $ lies at the point $ x_i $ for $ 1 \le i \le n $ .

You are a salesman with $ n $ bags of goods, attempting to deliver one bag to each of the $ n $ depots. You and the $ n $ bags are initially at the origin $ 0 $ . You can carry up to $ k $ bags at a time. You must collect the required number of goods from the origin, deliver them to the respective depots, and then return to the origin to collect your next batch of goods.

Calculate the minimum distance you need to cover to deliver all the bags of goods to the depots. You do not have to return to the origin after you have delivered all the bags.

## 说明/提示

In the first test case, you can carry only one bag at a time. Thus, the following is a solution sequence that gives a minimum travel distance: $ 0 \to 2 \to 0 \to 4 \to 0 \to 3 \to 0 \to 1 \to 0 \to 5 $ , where each $ 0 $ means you go the origin and grab one bag, and each positive integer means you deliver the bag to a depot at this coordinate, giving a total distance of $ 25 $ units. It must be noted that there are other sequences that give the same distance.

In the second test case, you can follow the following sequence, among multiple such sequences, to travel minimum distance: $ 0 \to 6 \to 8 \to 7 \to 0 \to 5 \to 4 \to 3 \to 0 \to (-5) \to (-10) \to (-15) $ , with distance $ 41 $ . It can be shown that $ 41 $ is the optimal distance for this test case.

## 样例 #1

### 输入

```
4
5 1
1 2 3 4 5
9 3
-5 -10 -15 6 5 8 3 7 4
5 3
2 2 3 3 3
4 2
1000000000 1000000000 1000000000 1000000000```

### 输出

```
25
41
7
3000000000```

# 题解

## 作者：封禁用户 (赞：2)

# CF1585C Minimize Distance 题解

## 解题思路
这题可以用贪心解决。

我们可以先让他去**正方向**最远的 $k$ 个仓库，交付第一轮，距离为 $\text{最远的仓库} \times 2$。

接下来在去剩下仓库里面最远的 $k$ 个仓库，交付第一轮，距离为 $\text{剩下仓库中最远的仓库}\times 2$。

如此往复，直到正方向的仓库都走完，再去负方向的仓库走一遍。

要注意，最后一次可以不回来。我们默认最远的一次是最后一次。

所以，我们的核心思路就是：

```
//a为正方向距离数组，b为负方向距离数组;
for(int i = atmp - 1 ; i >= 0 ; i -= k)
{
	cnt += a[i] + a[i];
}
for(int i = btmp - 1 ; i >= 0 ; i -= k)
{
	cnt += b[i] + b[i];
}
cnt -= max(a[atmp - 1] , b[btmp - 1]);
```

先去正方向，默认每一次去会走尽量多的仓库，每一次为最大的仓库;

再去负方向，重复上面的操作;

最后选取最长的一段不回来。

### 提示：用 $\texttt{int}$ 会爆掉哦！

## 参考代码
```
#include<bits\stdc++.h>
using namespace std;
long long t , n , k , x , a[200005] , b[200005] , atmp , btmp , cnt;
int main()
{
	cin >> t;
	while(t--)
	{
		scanf("%lld%lld" , &n , &k);
		atmp = btmp = cnt = 0;//初始化 
		for(int i = 0 ; i < n ; i++)
		{
			scanf("%lld" , &x);
			if(x >= 0) //正负数分开统计 
			{
				a[atmp] = x;//正 
				atmp++;
			}
			else
			{
				b[btmp] = abs(x);//负 
				btmp++;
			}
		}
		sort(a , a + atmp);
		sort(b , b + btmp);
		for(int i = atmp - 1 ; i >= 0 ; i -= k)//每次顺便送两轮间的货物 
		{
			cnt += a[i] + a[i];//统计正数
		}
		for(int i = btmp - 1 ; i >= 0 ; i -= k)//来回两趟 
		{
			cnt += b[i] + b[i];//统计负数
		}
		cnt -= max(a[atmp - 1] , b[btmp - 1]);//最长的一次不用回来
		printf("%lld\n" , cnt); 
	}
	return 0;
}

---

## 作者：xiaozeyu (赞：2)

[CF1585C Minimize Distance](https://www.luogu.com.cn/problem/CF1585C)

一道贪心题目。

在数轴上有很多的货物，每个货物有自己的坐标。

开始时自己在坐标轴原点。

每次最多能去拿起 $k$ 个货物，然后要把货物再拿回原点处。

所需的代价就是做过的路程长度。

在最后拿完了之后，不需要回到原点，也就是最终停留在最后拿起东西的地方。

这显然是一个贪心。

每次都可以拿上好几个货物，尽量每次都拿满。

每次拿连续的一段，这时最远的一个的距离就对应这单程的代价。

不该回头，回头再折返会浪费这重复的距离，要拿就顺路捎上。

从两端开始分别取正坐标物品与负坐标物品。保证拿上高代价的同时拿上其他高代价的物品，接下来的代价就会降低。

这时有了一个问题，靠近原点的两边的不满 $k$ 个的物品该怎么处理？

我们已经发现了单侧折返会亏。

在双侧情况下，越过零点折返去拿另一头的物品是不赚的，因为你本可以在经过原点时就把拿着的放下，再去另一端，这样你可以拿上另一头更多的物品，你的总代价是大于等于折返时的，也就是不劣。

最后是不用在取光之后返回的事情。

在正端与负端出现的最大值一定是在顶头的，我们只需要在最后去掉一个最大的单程即可。

在代码的实现上，我们只需要分别取完左右两边的物品，记录单程的代价，在最后翻倍，并且去除两头中最大的一次单程代价。

代码如下。



------------

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
int read()
{
	char c=getchar();int x=0;bool f=0;
	while(!isdigit(c))f^=!(c^45),c=getchar();
	while(isdigit(c))x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f)x=-x;return x;
}
const int maxn=200010;
int T,n,k,a[maxn];
int ans;
signed main()
{
	T=read();
	while(T--)
	{
		ans=0;
		n=read();k=read();
		For(i,1,n) a[i]=read();
		sort(a+1,a+n+1);
		for(int i=n;i>=1&&a[i]>0;i-=k) ans+=a[i];
		for(int i=1;i<=n&&a[i]<0;i+=k) ans-=a[i];
		printf("%lld\n",ans*2-max(abs(a[1]),a[n]));
	}	
}
```



---

## 作者：dd_d (赞：2)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/15712320.html)  

### 题意  

在数轴上有 $n$ 个点，有 $n$ 个人和一辆车。每个人要由车送去一个点。  
车一次最多能载 $k$ 个人。送完人后不用返回。求最小距离。  

### Sol  

将数轴左边与右边的点分开处理。  
每次都处理当前最靠右（左）且没到过的点。  
那么开两个数组分别存下正坐标和负坐标，暴力枚举即可。  
最后记得把返程的路减掉。  
时间复杂度 $O(n \log n)$，瓶颈在于排序。  

### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
#define int long long
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=2e5+10;
int n,m,n1,n2,ans,a[N],b[N];
signed main()
{
	int T=read();
	while (T--)
	{
		n=read(); m=read(); n1=n2=ans=0;
		for (int i=1;i<=n;i++)
		{
			int x=read();
			if (x>0) a[++n1]=x;
			else b[++n2]=-x;
		}
		sort(a+1,a+n1+1);
		sort(b+1,b+n2+1);
		for (int i=n1;i>=1;i-=m)
			ans+=a[i]*2;
		for (int i=n2;i>=1;i-=m)
			ans+=b[i]*2;
		if (n1&&n2) ans-=max(a[n1],b[n2]);
		else if (n1) ans-=a[n1];
		else if (n2) ans-=b[n2];
		writeln(ans);
	}
}




```

---

## 作者：liyp (赞：0)

## 思路
很明显的贪心。

外站上有一道题，和这道题类似，但是第 $i$ 个仓库不是放 $1$ 件货物，而是 $e_i$ 件。

这道题相对而言就好一些，我们只需要用最简单的贪心。

由于仓库的位置中存在负数，而我们的出发点是在 $0$ 的位置，因此我们可以把位置是正数的仓库和位置是负数的仓库分开处理。

经过分析样例一的第一、二组数据和题意我们不难发现，最优方案往往是出发时尽可能多拿货物，能多走远点就多走远点，除非没货了或者出发点这一侧的货物已经派送完了，否则不走回头路，可以证明这是最优的。也就是说，在不考虑全部配送完不需要回头的情况下，我们的最小路程和就是我们到每一个手中货物送完地点路程之和的两倍（回头取货）！

那么我们在派送货物时按照上述理论执行，在哪些位置会发现货物派送完会起点的情况呢？

正像我开头说的一样，这一题每一个仓库只需要派送一个货物，我们直接进行循环，每 $k$ 个仓库处理一次，就可以解决了。

```cpp
// 改示范代码仅展示思路，并不能直接套用于本题
for(int i=1;i<=n;i+=k){
    //do
}
```

解决了！

## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
int a[MAXN], n, k;
void solve()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);//懒得打 cmp 了
    long long ans = 0;
    for (int i = 1; i <= n; i += k) {
        if (a[i] > 0) break;
        ans += abs(a[i])*2;
    }
    for (int i = n; i > 0; i -= k) {
        if (a[i] < 0) break;
        ans += a[i] * 2;
    }
    ans -= max(abs(a[1]), a[n]);
    cout << ans << endl;
}
signed main()
{
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
}
```

---

## 作者：lpx666666 (赞：0)

题意
------------

在一条数轴上，你开始位于 $0$，数轴上有的点有仓库，你要将货物放过去，但每次能拿的货物数量有限，放完之后要回来再拿。

思路
------------

本题代码量不大，只要想到思路就出来了。

首先，这道题有负数，而到 $0$ 就交货，所以正负是完全独立的，输入后可以用两个数组储存，然后分开处理。

拿东西用到了“贪心”算法 ，只要你走过去，放东西距离最小化就行，不能一个一个遍历，一是时间复杂度高，二是不好统计，可以 $k$ 个 $k$ 个遍历，但不能从最开始遍历，因为要让距离最小，所以每次越近越好，从 $d \bmod k$ 开始就是最小值。

最后用一个变量存下最远距离，题中说明，最后一次可以不回来，所以最后减去最远距离，得出结果。

代码
------------
我的代码很水，没有优化，要看代码的可以看楼上的，但这里代码思路我自认还算清晰。
```cpp
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=2*1e5+5;
long long t,a[N],arr[N],brr[N];
int main(){
    ios::sync_with_stdio(0),cin.tie(0);  
    cin>>t;
    while(t--){
        long long n,k,c=0,d=0,ans=0,max_=-1;
        cin>>n>>k;
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        for(int i=0;i<n;i++){
            if(a[i]<0){
                arr[++c]=abs(a[i]);
            }
            else{
                brr[++d]=abs(a[i]);
            }
        }
        sort(arr+1,arr+c+1);
        sort(brr+1,brr+d+1);
        for(int i=d%k;i<=d;i+=k){
            ans+=brr[i]*2;
            max_=max(max_,brr[i]);
        }
        for(int i=c%k;i<=c;i+=k){
            ans+=arr[i]*2;
            max_=max(max_,arr[i]);
        }
        ans-=max_;
        cout<<ans<<endl;
    }
    return 0;
}
```

---

## 作者：TPJX (赞：0)

### 题目分析
这是一道贪心题。

按照贪心策略，我们从最远的仓库开始，每次尽可能携带最多的 $k$ 个货物。这意味着如果有 $k$ 个或更少的仓库在某一方向（正或负），我们将这几个仓库的货物一次性全部带到，再回到原点获取下一批货物。这种策略的核心思想是减少不必要的来回次数，从而最小化总距离。
### C++ 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 200010;
long long pos[MAXN], neg[MAXN];

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int pc = 0, nc = 0;
        for (int i = 1; i <= n; ++i) {
            int x;
            cin >> x;
            if (x > 0) pos[++pc] = x;
            else if (x < 0) neg[++nc] = -x;
        }
        sort(pos + 1, pos + pc + 1);
        sort(neg + 1, neg + nc + 1);        
        long long td = 0;
        for (int i = pc; i >= 1; i -= k)
            td += 2 * pos[i];
        for (int i = nc; i >= 1; i -= k)
            td += 2 * neg[i];
        long long md = 0;
        if (pc > 0) md = max(md, pos[pc]);
        if (nc > 0) md = max(md, neg[nc]);
        td -= md;
        cout << td << endl;
	}
    return 0;
}
```
#### 时间复杂度
- 输入：$O(n)$
- 分类和绝对值处理：$O(n)$
- 排序：$O(n \log n)$
- 贪心计算最短距离：$O(n)$

感谢观看。

---

