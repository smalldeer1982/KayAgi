# WeirdSort

## 题目描述

给出一个长度为 $n$ 的序列 $a$ 和一个长度为 $m$ 的序列 $p$，你需要按照以下规则给序列 $a$ 排序

对于所有 $(1 \le i \le m)$，$p_i$ 表示你可以交换 $a[p_i]$ 和 $a[p_i+1]$ 的值（可以操作任意次）
请求出是否能在以上限制条件下，保证排序后的原序列 $a$ 内元素值严格不递减

除了交换 $a[p_i]$ 和 $a[p_i+1]$ 之外，不可以有其他任何操作

## 说明/提示

$1 \le T,a_i \le 100$  
$1\le m < n \le 100$
$1\le p_i <n$

感谢 @[_Wolverine](https://www.luogu.com.cn/user/120362) 提供的翻译

## 样例 #1

### 输入

```
6
3 2
3 2 1
1 2
4 2
4 1 2 3
3 2
5 1
1 2 3 4 5
1
4 2
2 1 4 3
1 3
4 2
4 3 2 1
1 3
5 2
2 1 2 3 3
1 4```

### 输出

```
YES
NO
YES
YES
NO
YES```

# 题解

## 作者：gyh20 (赞：2)

我们发现，如果 $a_i<=a_{i+1}$ 那么这个交换是没有意义的。

所以说只需要最原始的两两相比的冒泡排序即可，但只有可以交换且 $a_i>a_{i+1}$ 的位置才交换，这样是一定正确的。

最后检查一遍数组是否排序即可。

总复杂度 $O(Tn^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int t,n,a[102],p[102],m;
int main(){
	t=read();
	while(t--){
		bool ia=1;
		n=read();m=read();
		memset(p,0,sizeof(p));
		for(re int i=1;i<=n;++i)a[i]=read();
		for(re int j=1;j<=m;++j)p[read()]=1;
		for(re int i=1;i<=n;++i){
		
		for(re int j=1;j<n;++j){
			if(a[j]>a[j+1]){
				if(p[j])swap(a[j],a[j+1]);
			}
		}}
		for(re int i=1;i<=n;++i)if(a[i]<a[i-1]){
			ia=0;
			puts("NO");
			break;
		}
		if(ia){
			puts("YES");
		}
	}
}
```


---

## 作者：ShineEternal (赞：2)

[更佳的阅读效果。](https://blog.csdn.net/kkkksc03/article/details/104504289)

## description：
- 给定一个长度为 $n$ 的序列 $a_i$。
- 再给定一个长度为 $m$ 的序列 $p_i$。
- 对于每一个 $p_i$，你都可以选择将 $a_{p_i}$ 和 $a_{p_i+1}$ 交换位置，使用次数不限。
- 询问你能否找到一种方案，使得序列满足 $a_1\le a_2\le a_3\le...\le a_n$，输出 `YES` 或 `NO` 即可。
- **多组数据**，数据组数不超过 $100$，$1\le m<n\le 100$，$1\le a_i\le 100$，$1\le p_i< n$。
- translate by @[ShineEternal](https://www.luogu.com.cn/user/45475)。

## solution：
其实我们可以把 $p_i$ 看成一个个传送带。

首先如果有 $m=n-1$，那么任何情况都能传送，也就是说一定有解。

否则的话，我们可以先把传送带排序。

然后这时候传送带可能会有连成一块一块的。（即连续自然数列）

那么同一块的我们可以随便排序，直接 $\operatorname{sort}$ 即可。

每一块传送带都这么操作，最后对 $a$ 数组进行单调性判断。

## code：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int a[105],p[105];
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d",&p[i]);
		}
		sort(p+1,p+m+1);
		if(m==n-1)
		{
			printf("YES\n");
			continue;
		}
		int tmpl=p[1],tmpr=p[1]+1;
		for(int i=2;i<=m;i++)
		{
			if(p[i]>p[i-1]+1)
			{
				sort(a+tmpl,a+tmpr+1);
				tmpl=p[i];
				tmpr=p[i]+1;
			}
			else
			{
				tmpr++;
			}
		}
		sort(a+tmpl,a+tmpr+1);
		int flag=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i]<a[i-1])
			{
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
} 
```

---

## 作者：andyli (赞：1)

设当前操作区间为$[l,r]$，初始$l=1,r=n$。  
对于每次操作要将操作区间中最小的且最靠左的数移动到操作区间的最左边，最大的且最靠右的数移动到操作区间的最右边，必须确保所有的移动操作都在$p$中，若非则表明无解。  
时间复杂度$\mathcal O(n^2)$。  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
const int maxn = 105, INF = -1u / 2;

int A[maxn], P[maxn];
bool vis[maxn];
int main()
{
    int q;
    io.read(q);
    while (q--) {
        int n, m;
        io.read(n, m);
        for (int i = 1; i <= n; i++)
            io.read(A[i]);
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= m; i++)
            io.read(P[i]), vis[P[i]] = true;
        bool flag = true;
        int l = 1, r = n;
        while (l < r) {
            int p = 0, t = INF;
            for (int i = l; i <= r; i++)
                if (A[i] < t)
                    t = A[i], p = i;
            for (int i = l; i < p; i++)
                if (!vis[i]) {
                    flag = false;
                    break;
                }
            if (!flag)
                break;
            for (int i = p - 1; i >= l; i--)
                swap(A[i + 1], A[i]);
            t = -INF;
            for (int i = l; i <= r; i++)
                if (A[i] >= t)
                    t = A[i], p = i;
            for (int i = p; i < r; i++)
                if (!vis[i]) {
                    flag = false;
                    break;
                }
            for (int i = p; i < r; i++)
                swap(A[i], A[i + 1]);
            l++, r--;
            if (!flag)
                break;
        }
        writeln(flag ? "YES" : "NO");
    }
    return 0;
}
```

---

## 作者：LB_tq (赞：1)

# Solution
- 题解区中已经有了划分加快排的 $O(nlogn)$ 做法，我再提供一种冒泡排序的 $O(\mathbf{n}^2)$ 做法。

- 考虑题意中$p_{i}$只能交换$a_{i}$与$a_{i+1}$，就可以想到冒泡排序的过程：每次冒泡过程都会不断交换相邻两个数，每次可以将一个数交换到正确的位置。

- 于是我们可以对数列进行非递减排序，交换$a_{i}$和$a_{i+1}$时，若$p_{i}$不能交换，则不能成功。否则能成功。

# Code
```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=110;
int t,n,m,a[maxn],p[maxn];
bool flag;//flag存储是否成功
int main(){
    int x;
    cin>>t;
    while(t--){
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            cin>>a[i];
        memset(p,0,sizeof(p));
        for(int i=1;i<=m;i++){
            cin>>x;//读入位置
            p[x]=1;//将该位置标记为可交换
        }
        flag=true;//每次要重置flag
        for(int i=1;i<n;i++){
            for(int j=1;j<=n-i;j++)
                if(a[j]>a[j+1]){
                    swap(a[j],a[j+1]);
                    if(p[j]==0){//若该位置不能交换，则标记flag为false
                        flag=false;
                        break;
                    }
                }
            if(!flag)
                break;
        }
        if(flag)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    return 0;
}
```


---

## 作者：Cult_style (赞：0)

	这道题有点难度
    思路就是如果a[i]后面有比a[i]大的数，就看看在这一段区间里是不是都可以交换
    我们可以用一个数组k来看看，哪一个数不可以和后面的数交换
    如果不可以，就做一下标记，输出"NO"
    如果一直到最后都可以,标记的变量还是0的话，输出"YES"
    细节就在代码里说吧
```

#include<bits/stdc++.h>
using namespace std;
int t,n,m;
//t表示有几组数据，n表示有几个数，m表示可以和后面的数交换的数
int a[105];
//n个数
int z;
//用来做标记
int k[105];
//标记可以和后面的数交换的数
int y[105];
int main(){
	scanf("%d",&t);
	for(int u=1;u<=t;u++){
	    scanf("%d%d",&n,&m);
	    for(int i=1;i<=n;i++)
	        scanf("%d",&a[i]);
		memset(k,0,sizeof k);
        	z=0;
        	//因为有多组数据，所以要清空
		for(int i=1;i<=m;i++){
		    scanf("%d",&y[i]);
		    k[y[i]]++;
		}	
		for(int i=1;i<n;i++){
		    for(int j=i+1;j<=n;j++){
			if(a[i]>a[j]){
			    for(int e=i;e<j;e++){
                	    //只要i到j-1能交换就行了，因为a[j-1]可以和a[j]交换
				if(k[e]==0)
				    z=1;
                 		    //如果小于0就代表不能被交换，那就不可能让a数组有序
			    }
			}
		    }
		}
		if(z==1)//如果它不能，输出NO
		    printf("NO\n");
		else//不然输出YES
		    printf("YES\n");
	}
	
	
	return 0;
}
```


---

## 作者：AmamiyaYuuko (赞：0)

题目中给出的限制是 $a_{p}$ 与 $a_{p + 1}$ 交换位置，不难看出这种每次交换相邻元素的排序其实就是冒泡排序。

所以我们只需要对原数组进行冒泡排序，排序过程中检验题目中给出的限制是否满足可以交换需要交换的两个元素。

相当于检验冒泡排序能否进行。

时间复杂度 $O(tn^2)$。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

template <class T>
inline void read(T &x)
{
    x = 0;
    int f = 0;
    char ch = getchar();
    while (!isdigit(ch))    { f |= ch == '-'; ch = getchar(); }
    while (isdigit(ch))     { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
    x = f ? -x : x;
    return;
}

int a[110], p[110];
int t, n, m;
bool b[110];
bool flag;

int main()
{
    read(t);
    while (t--)
    {
        read(n), read(m);
        memset(b, false, sizeof(b));
        for (int i = 1; i <= n; ++i)    read(a[i]);
        for (int i = 1; i <= m; ++i)    read(p[i]), b[p[i]] = true;
        flag = true;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n - i; ++j)
            {
                if (a[j] > a[j + 1])
                {
                    if (b[j])
                    {
                        std::swap(a[j], a[j + 1]);
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                }
            }
            if (!flag)  break;
        }
        puts(flag ? "YES" : "NO");
    }
    return 0;
}

```

---

## 作者：Trilliverse (赞：0)

### 题意简述
- 给定一个长度为 n 的数组 $a$ 和一个数组 $p$ 。
- $p[i]$ 表示 $a[p[i]]$ 和 $a[p[i]+1]$ 可以交换。
- 通过任意次交换，问你能否把 $a$ 数组变成一个**非降**数列。

### 题目思路
- 暴力思维：不断的**交换**，只要前面的数**大于**后面的数，就交换这两个元素（~~因为题目要求非降~~）。
- 如果最终交换完以后满足题目要求，就是 `YES`；否则，就是 `NO` 。

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

#define mem(a, b) memset(a, b, sizeof(a))

int a[105],p[105];

int main() {
	int T;
	cin >> T;
	while(T--) {
		mem(a,0);mem(p,0);
		int n,m;
		cin >> n >> m;
		for(int i=1;i<=n;i++) cin >> a[i];
		for(int i=1;i<=m;i++) cin >> p[i];
		
		int t = n;
		while(t--) {//不断交换
			for(int i=1;i<=m;i++) {
				if(a[p[i]] > a[p[i]+1]) {
					int x = a[p[i]];
					a[p[i]] = a[p[i]+1];
					a[p[i]+1] = x;
				}
			}	
		}
		
		//判断是否为非降序列  
		bool flag = true;
		for(int i=1;i<n;i++) {
			if(a[i] > a[i+1]) flag = false;
		}
		
		if(flag) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
```


---

