# Save More Mice

## 题目描述

坐标轴上有一只猫，$k$ 只老鼠和一个洞口。其中猫在坐标为 $0$ 的位置，洞口在坐标为 $n$ 的位置，所有的老鼠都在猫和洞口之间，其中第 $i$ 只老鼠在 $x_i$ 的位置。可能有多只老鼠在同一个位置上。

在每一秒钟，将会**依次**执行以下行动：

- **其中一只**老鼠会向右移动 $1$ 的位置，如果一个老鼠到达洞口，它会隐藏起来（这只老鼠将不会再移动到任何位置，也不会被猫吃掉）。
- 猫会向右移动 $1$ 的位置，并会吃掉它到达的位置上的老鼠（被吃掉的老鼠将不能再移动）。

直到所有的老鼠都已经隐藏起来或已经被吃掉。

每一秒钟，你都可以选择移动的老鼠，请你求出最多可以保护多少只老鼠安全到达洞口并隐藏起来。

## 说明/提示

- $1 \le t \le 10^4$；
- $2 \le n \le 10^9$；
- $1 \le k \le 4 \times 10^5$；
- $1 \le x_i <n$。

Translated by @BurningEnderDragon, 2021.10.14

## 样例 #1

### 输入

```
3
10 6
8 7 5 4 9 4
2 8
1 1 1 1 1 1 1 1
12 11
1 2 3 4 5 6 7 8 9 10 11```

### 输出

```
3
1
4```

# 题解

## 作者：Forever1507 (赞：1)

非常显然的贪心。先上结论：优先移动离洞近的老鼠。

从反面考虑，假设先让离洞远的老鼠进洞，猫的步数也会相应增多，只会让更多老鼠被吃，不会缩短其他老鼠进洞的速度，反而加大损失。

结论就显然了。

实现的话排序然后模拟即可。

代码：
```cpp
    #include<bits/stdc++.h>
    using namespace std;
    int t,n,k,a[400005];
    int main(){
    	cin>>t;
    	while(t--){
    		cin>>n>>k;
    		for(int i=1;i<=k;i++)cin>>a[i];
    		sort(a+1,a+k+1);
    		int cat=0,point=k,cnt=0;
    		while(a[point]>cat){
    			cat+=(n-a[point]);
    			point--;
    			cnt++;
    		}
    		cout<<cnt<<'\n';
    	}
    	return 0;
    }
```


---

## 作者：rhyyy1 (赞：1)

思考后很容易得到，应该使用贪心算法。

老鼠每走一步，猫也跟着走一步。所以得出结论老鼠应该一只一只救。

因为如果你将一只老鼠救到鼠洞门口，最后还是得花费一单位时间去将它放入洞内。所以如果一只老鼠能得救，直接将它移入洞内和分步移动的效果是一样的。

那么接下来考虑先救谁，明显先救靠近洞的。

所以只要按老鼠靠近洞的距离从小到大排序取就可以了。

最后如果都能获救，输出 $m$ 。

代码：
```
#include<bits/stdc++.h>
using namespace std;
const int N=4e5+50;
int a[N];
void solve(){
	int n,m; scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) a[i]=n-a[i];
	sort(a+1,a+m+1);
	long long sum=0;
	for(int i=1;i<=m;i++){
		sum+=a[i];
		if(sum==n-1){
			printf("%d\n",i);
			return ;
		}else if(sum>=n){
			printf("%d\n",i-1);
			return ;
		}
	}
	printf("%d\n",m);
}
int main(){
	int T; cin>>T;
	while(T--) solve();
}

```


---

## 作者：fls233666 (赞：0)

题目要求我们要尽可能多的保护老鼠。我们知道，老鼠移动一步，猫也会移动一步。所以，**在我们不断移动同一只老鼠的时候，猫是追不上这只老鼠的。** 因此，不断移动同一只老鼠直到它进洞一定是更优的。

我们进一步考虑按什么顺序移动老鼠。

如果移动靠近猫的老鼠，猫在追这只老鼠的时候一定会吃掉其他的很多老鼠。当这只老鼠进洞时，剩下的老鼠就很少了。显然这是不优的。

正确的想法是移动靠近洞的老鼠。这时老鼠离洞进，成功保护一只老鼠需要的步数就很少，牺牲的老鼠也就少。于是，一个合理的**贪心**策略出现了。

转换到代码实现，具体就是按每只老鼠离洞的距离排序。按离洞从近到远的顺序处理，记录每只老鼠进洞需要的步数，同时维护猫的位置。直到发现一个有老鼠的位置已经被猫走过了，说明这只老鼠及其前面的老鼠都被吃掉了。而后面的老鼠都被成功移到洞里了。这时结束程序，我们就成功保护的最多的老鼠。

完整代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 4e5+5;
int n,ans,nk,cat;
int xi[mxn];

int main(){
	int test;
	scanf("%d",&test);
    
	while(test--){
		ans=cat=0;  //重置答案和猫的坐标
        
		scanf("%d%d",&n,&nk);
		for(rgt i=1;i<=nk;i++)
			scanf("%d",&xi[i]);  //读入老鼠坐标
            
		sort(xi+1,xi+1+nk);  //按位置排序
        
		for(rgt d,i=nk;i>=1;i--){
			if(cat>=xi[i])  //这只老鼠及其前面的老鼠都被吃了，结束统计
				break;
			d=n-xi[i];  //计算保护这只老鼠需要的步数
			cat+=d;  //猫移动相应的步数
			ans++;  //救了一只老鼠，答案+1
		}
        
		printf("%d\n",ans);  //输出最终答案
	}
	return 0;
}
```


---

## 作者：Alkaid_Star (赞：0)

### 题目大意

> $T$ 组数据。
>
> 坐标轴上有一只猫，$k$ 只老鼠和一个洞口。其中猫在坐标为 $0$ 的位置，洞口在坐标为 $n$ 的位置，并且给定每只老鼠的坐标 $x_i$。
>
> 在每一秒钟，我们可以**选择一只老鼠**向右走一个位置，如果一个老鼠到达洞口，它就通关了（不会再被吃掉）。在老鼠移动之后，猫会向右移动一个位置，并会吃掉它到达的位置上的老鼠（被吃掉的老鼠将不能再移动）。
>
> 持续以上过程直到所有的老鼠都已经隐藏起来或已经被吃掉。请你求出最多可以保护多少只老鼠通关。
>
> $1 \le T \le 10^4$，$2 \le n \le 10^9$，$1 \le k \le 4 \times 10^5$，$1 \le x_i \le n$。

### 解题思路

首先，从贪心角度考虑，我们移动老鼠肯定是**选中这只老鼠就一定会把它送到洞口**（显然不送到洞口只是浪费步数）。

那么我们考虑现在选了 $k$ 只老鼠，可以发现一个结论：**如果我们这 $k$ 只老鼠到洞口所需的步数之和小于猫到洞口的步数（也就是 $n-1$），那么我们一定可以把这 $k$ 只老鼠都送到洞口**。

为什么呢？我们考虑每次选离猫最近的那一只往后跑，由于我们花费的总步数大于猫的步数，那么我们一定保证每一只老鼠都可以安全到达洞口（可以把这个理解成一个动态调配的过程）。

这样的话，问题就转化为了**选出最多的老鼠使得到洞口的总步数最小**。而这个只需要把老鼠到洞的距离排序，从小到大取就好了。时间复杂度 $O(n \log n)$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500005;

int n,k,a[N],b[N];

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

signed main(){
	freopen("CF1593C.in","r",stdin);
	freopen("CF1593C.out","w",stdout);
	int T=read();
	while (T--){
		n=read(),k=read();
		for (int i=1;i<=k;++i) a[i]=read(),b[i]=n-a[i];
		sort(b+1,b+k+1);
		// printf("b: "); for (int i=1;i<=k;++i) printf("%lld ",b[i]); printf("\n");
		int rem=n-1,ans=0;
		for (int i=1;i<=k;++i){
			rem=rem-b[i];
			// printf("rem=%lld\n",rem);
			if (rem<0) break;
			++ans;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：sycqwq (赞：0)

__题意：__

在一个数轴上

有 $k$ 只老鼠和 $1$ 只猫。

起始，第 $i$ 只老鼠在第 $x_i$ 的位置，猫在 $0$ 的位置，老鼠洞在 $n$ 的位置。

对于每一个时刻，猫和一只老鼠可以向正方向移动一个单位长度。

如果一只老鼠在猫追上它之前可以移到老鼠洞，则这只老鼠就获救了。

问最多有多少只老鼠可以获救。

__思路：__

一看题面就能想到，这是一个贪心。

__贪心策略__：

每一次先让离老鼠洞最近的老鼠移动到老鼠洞。

因为离老鼠洞越近的老鼠，逃生机会肯定更大。

如果选择的不是离老鼠洞最近的老鼠，那么移动的路程就会变大，答案就不是最优的。

__代码：__

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+5;
int t,a[maxn];
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int n,m,c=0;//c是猫的坐标
        cin>>n>>m;
        for(int j=1;j<=m;j++)
            cin>>a[j];
        sort(a+1,a+m+1);
        int s=0;
        for(int j=m;j>=1;j--)
        {
            if(c>=a[j])
                break;
            c+=n-a[j];
            ++s;
        }
        cout<<s<<endl;
    }
    return 0;
}
```

---

## 作者：feicheng (赞：0)

## C. Save More Mice



### Task

有一个长为 $n+1$ 的数轴，猫在 $0$ 号位置，洞在 $n$ 号位置，有 $k$ 只老鼠在猫和洞之间，第 $i$ 只坐标为 $x_i$。

每一秒你可以选择一只老鼠向右移动一格，然后猫将移动一格。

如果猫和老鼠同格，那么猫会吃掉老鼠。

最大化到达洞的老鼠数量。

多测。

**限制：**$2\le n\le 10^9$,$1\le k,\sum k\le 4\times 10^5$,$1\le t\le 10^4$

### Solution

容易发现老鼠走的步数一定**小于**猫的步数，那么考虑贪心，即先送离洞最近的老鼠，然后送次近的……

容易发现当走的步数和 $\gt n$ 的时候，剩下的老鼠便葬身猫围了，答案即为当前循环到的下标 $-1$。

时间复杂度：$\mathcal O(k\log k)$（单次） 

---

## 作者：智子 (赞：0)

## 题意

在数轴上有一只猫，$k$ 只老鼠和一个洞，猫在点 $0$，洞在点 $n$，第 $i$ 只老鼠在点 $x_i (0 < x_i < n)$。

每个时刻有且仅有一只老鼠可以向右移动一位，猫也会向右移动一位。如果猫的位置和一只老鼠重合，猫就会吃掉这只老鼠，已经在洞的位置上的老鼠不会被吃掉。

求最多有多少只老鼠可以不被猫吃掉。

## 思路

这道题的解法是贪心。

现将所有老鼠按照坐标排序，再依次从第 $n$ 个老鼠开始，从右到左依次尝试将每一个老鼠移动到洞里，如果当前的老鼠已经被吃掉了就停止（所有老鼠已经不是到了洞里就是被吃掉）。

如果不移动最右侧的老鼠而是移动其他老鼠，最右侧老鼠不动而猫向右移动，猫与所有老鼠构成的区间长度缩短，答案显然不会更优。

## 代码

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN = 400000 + 5;

int a[MAXN];
int n, k;

int main() {
    int T;

    cin >> T;
    while(T--) {
        cin >> n >> k;
        for(int i = 1; i <= k; i++) {
            cin >> a[i];
        }
        sort(a + 1, a + k + 1);
        int cat = 0, ans = 0;
        for(int i = k; i >= 1; i--) {
            if(cat >= a[i]) {
                break;
            }
            int dis = n - a[i];
            ans++;
            cat += dis;
        }
        cout << ans << endl;
    }

    return 0;
}
```

---

## 作者：ttq012 (赞：0)

贪心思想，对老鼠和洞的距离进行从远到近的排序。

然后每一轮将离洞最近的老鼠移动到洞里面去，然后猫咪的位置也更新（加上老鼠到洞的距离）

如果猫咪已经到达了洞穴，那么就停止循环，输出答案。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        int m = 0, s = 0;
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < k; i ++)
            scanf ("%d", &a[i]);
        sort (a, a + k); // 对老鼠的初始坐标进行排序，实际上是对老鼠的坐标进行排序
        while (n - m > n - a[k - 1])
        {
            s ++; // 能够逃到洞里面的老鼠的数量
            m += (n - a[k - 1]); // 猫咪的位置
            k --;
        }
        printf ("%d\n", s); 
    }
    return 0;
}

```


---

## 作者：happy_dengziyue (赞：0)

### 1 思路

这道题使用贪心解决。

很明显，让一个距离洞最近的老鼠先逃脱好过于距离远的。

所以，我们从坐标大到小枚举每一个老鼠。直到让这个老鼠和之前的老鼠逃脱的代价大于等于 $n$，这个老鼠就救不回来了。

简单的说，就是：

将 $a[i]$ 从大到小排序后，构造一个序列 $p$，令 $p[i]=n-a[i]$，试确定一个数 $ans$，使得满足 $\sum_{i=1}^{ans}p[i]<n$ 的情况下，$ans$ 最大。

### 2 代码与记录

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
#define max_n 400000
int t;
int d;
int n;
int a[max_n+2];
int sum;
int ans;
bool cmp(int a,int b){
	return a>b;
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1593C_1.in","r",stdin);
	freopen("CF1593C_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&d,&n);
		for(int i=1;i<=n;++i){
			scanf("%d",a+i);
		}
		sort(a+1,a+n+1,cmp);
		sum=0;
		ans=0;
		for(int i=1;i<=n;++i){
			sum+=d-a[i];
			if(sum>=d)break;
			++ans;
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/59838990)

By **dengziyue**

---

