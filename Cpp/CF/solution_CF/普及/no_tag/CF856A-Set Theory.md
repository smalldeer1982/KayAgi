# Set Theory

## 题目描述

Masha and Grisha like studying sets of positive integers.

One day Grisha has written a set $ A $ containing $ n $ different integers $ a_{i} $ on a blackboard. Now he asks Masha to create a set $ B $ containing $ n $ different integers $ b_{j} $ such that all $ n^{2} $ integers that can be obtained by summing up $ a_{i} $ and $ b_{j} $ for all possible pairs of $ i $ and $ j $ are different.

Both Masha and Grisha don't like big numbers, so all numbers in $ A $ are from $ 1 $ to $ 10^{6} $ , and all numbers in $ B $ must also be in the same range.

Help Masha to create the set $ B $ that satisfies Grisha's requirement.

## 样例 #1

### 输入

```
3
3
1 10 100
1
1
2
2 4
```

### 输出

```
YES
1 2 3 
YES
1 
YES
1 2 
```

# 题解

## 作者：Redamancy_Lydic (赞：2)

看到 $n$ 只有 $100$，所以考虑 $\mathcal{O}(nV(A))$ 的算法。

我们在 $[1,10^6]$ 的范围内从小到大依次枚举每一个可能的值，同时开一个桶记录当前所有出现过的和。如果当前枚举到的值与 $a$ 中任何一个元素的和在桶里出现过，则说明该值不合法，跳过。否则存到答案数组里面。

当答案数组长度达到 $n$ 或者枚举完所有值时，跳出循环。

最后判断数组长度是否为 $n$ 然后输出即可。

```cpp
for(int i=1;i<=maxn;i++)
	{
		bool f=0;
		for(int j=1;j<=n;j++)f|=mp[i+a[j]];
		if(f)continue;
		ans.push_back(i);
		if(ans.size()==n)break;
	}
	if(ans.size()!=n)puts("NO");
	else {puts("YES");for(auto i : ans)cout<<i<<' ';}
```

---

## 作者：Bai_R_X (赞：1)

## 思路
暴力枚举 $1\sim10^6$ 的数，当作 $b$ 中的一个数，如果与 $a$ 所有数字的和不重复了话，把它置入 $b$ 数组内。

如果 $b$ 数组长度不到 $n$，则无解。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,i,a[105],b[105],cnt;
bool vis[2000005];
signed main()
{
    cin>>T;
    while(T--)
    {
    	memset(vis,0,sizeof(vis));
    	cnt=0;
    	cin>>n;
    	for(i=1;i<=n;i++)cin>>a[i];
    	for(i=1;i<=1000000;i++)
    	{
    		bool f=0;
    		for(int j=1;j<=n;j++)
    		{
    			if(vis[a[j]+i])goto next;
			}
			for(int j=1;j<=n;j++)vis[a[j]+i]=1;
			b[++cnt]=i;
			if(cnt==n)break;
next:
			;
		}
		if(cnt<n)cout<<"NO"<<endl;
		else
		{
			cout<<"YES"<<endl;
			for(i=1;i<=n;i++)cout<<b[i]<<" ";
			cout<<endl;
		}
	}
    return 0;
}
```

---

## 作者：_Execution_ (赞：1)

## 思路

枚举 $1 \sim 10^6$，记录它与 $a_i$ 的和是否出现；若枚举完了没有找到解，既无解，输出 `NO`，否则输出 `YES`，输出枚举的解即可。

## 细节

记录相加和的数组（在我的代码中体现为 `k`）需要开两倍大，即 $2 \times 10^6$。

## 代码

```cpp
#include <bits/stdc++.h>
#define MAXN 105
using namespace std;
int n;
int a[MAXN];
bool k[(int)2e6 + 5];
int b[MAXN];
int main() {
  int T;
  cin >> T;
  while (T--) {
    int ans = 0, ansn = 0;
    memset(k, 0, sizeof k);
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= (int)1e6; i++) {
      if (ans == n) break;
      bool flag = 0;
      for (int j = 0; j < n; j++) {
        if (k[i + a[j]]) {
          flag = 1;
          break;
        }
      }
      if (!flag) {
        for (int j = 0; j < n; j++) {
          k[i + a[j]] = 1;
        }
        ans++;
        b[ansn++] = i;
      }
    }
    if (ans < n) {
      puts("NO");
      continue;
    }
    puts("YES");
    for (int i = 0; i < n; i++) {
      cout << b[i] << " ";
    }
    puts("");
  }
  return 0;
}
```

---

## 作者：xiazha (赞：1)

## 思路

暴力。直接枚举每一个答案，从 $1\sim 10^6$ 全试一遍，用桶标记，我将暴力过程分为三步。




------------



1. 将目前枚举的答案与每个 $a_i$ 相加，只要有一个 $a_i$ 与枚举的答案加起来在之前出现过，就说明当前这个答案不可行。

2. 如果当前答案满足条件，就将它存储到放答案的数组里，如果数组元素个数已经达到 $n$ 个就可以输出答案了，否则继续枚举下一个数。

3. 如果 $1\sim 10^6$ 都枚举了一遍，答案数组里的元素个数却还没有到 $n$ 个，就说明没有可行方案，输出 ```NO```。


## 代码
```
#include<bits/stdc++.h>
using namespace std;
int l,n,a[101],t[2000002],b[101],cnt,flag;
int main()
{
	cin>>l;
	while(l--)
	{
		cnt=0;
		memset(t,0,sizeof(t));
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		for(int i=1;i<=1000000;i++)
		{
			flag=0;
			for(int j=1;j<=n;j++)
				if(t[a[j]+i]==1)
				{
					flag=1;
					break;
				}
			if(flag==0)
			{
				b[++cnt]=i;
				for(int j=1;j<=n;j++) t[a[j]+i]=1;
			}
			if(cnt==n) break;
		}
		if(cnt<n) cout<<"NO\n";
		else
		{
			cout<<"YES\n";
			for(int i=1;i<=cnt;i++) cout<<b[i]<<" ";
			cout<<"\n"; 
		}
	}
	return 0;
}
```


---

## 作者：一叶知秋。 (赞：1)

题目是要使得 $a_i+b_j \ != \ a_x+b_y$

转换一下，其实就是求 $a_i-a_x \ != \ b_y-b_j$

就是使得 $B$ 里面的任意两个元素的差值不等于 $A$ 里面任意两个元素的差值即可

注意不是求 $mex$ 然后 $b_i=1+(i-1) \times mex$ ，因为可能 $A$ 中的差值可能会等于 $k \times mex$

$code$ :

```cpp
#include<cstdio>
#include<cctype>

#define maxn 111
#define MAX 1000000
#define maxv 2002002

#define abs(a) ((a)<0?(-(a)):(a))

inline int read(){
	int r=0,f=0;
	char c;
	while(!isdigit(c=getchar()))f|=(c=='-');
	while(isdigit(c))r=(r<<1)+(r<<3)+(c^48),c=getchar();
	return f?-r:r;
}

int n,s_ans,a[maxn],ans[maxn];

bool len[maxv];

inline void work(){
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
			len[abs(a[i]-a[j])]=0;
	s_ans=0;
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read();
	for(int x=1;x<=MAX&&s_ans<n;x++){
		if(len[x])continue;
		ans[++s_ans]=x;//每次加进一个元素就要防止后面的元素
		for(int i=1;i<n;i++)//与这个的差会等于A中的差
			for(int j=i+1;j<=n;j++)
				len[x+abs(a[i]-a[j])]=1;
	}
	if(s_ans<n)puts("NO");
	else {
		puts("YES");
		for(int i=1;i<=n;i++)
			printf("%d ",ans[i]);
		puts("");
	}
}

int main(){
	int t=read();
	while(t--)work();
	return 0;
}

```

---

## 作者：Paracelestia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF856A)

## $\texttt{Solution}$

比较无脑的构造题。

由于 $n \leq 100$，$a$ 数组和 $b$ 数组只能产生 $O(n ^ 2)$ 种和，约 $10^4$，远小于值域 $10^6$，因此一定有解。

用一个数组 $vis_i$ 表示 $i$ 是否属于 $a$ 或者会由之前选择的 $b$ 元素产生。

暴力枚举 $[1, 10^6]$ 之间的数，若不与之前的选择产生冲突就加入 $b$，并标记其与 $a$ 的元素产生的和。

时间复杂度 $\mathcal{O}(nV)$。

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;

#define fi first
#define se second

template<typename T> inline T read() {
    T x = 0, f = 1; char ch = 0;
    for(; !isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = (x << 3) + (x << 1) + (ch - '0');
    return x * f;
}

template<typename T> inline void write(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

template<typename T> inline void print(T x, char ed = '\n') {
    write(x), putchar(ed);
}

const int N = 2e6 + 10;

namespace GoedelMachine {
    int n, a[N];
    bool vis[N];
    vector<int> ans;

    void init() {
        ans.clear();
        memset(vis, 0, sizeof vis);
    }
    void main() {
        n = read<int>();
        for(int i = 1; i <= n; ++ i) {
            a[i] = read<int>();
            vis[a[i]] = 1;
        }
        int k = n;
        for(int i = 1; i <= 1e6; ++ i) {
            bool f = 0;
            for(int j = 1; j <= n; ++ j) 
                f |= vis[a[j] + i];
            if(f) continue;
            ans.emplace_back(i);
            for(int j = 1; j <= n; ++ j) 
                vis[a[j] + i] = 1;
            if(-- k == 0) break;
        }
        if(k) puts("NO");
        puts("YES");
        for(auto p: ans) print(p, ' ');
        puts("");
    }
}

signed main() {
    int T = 1;
    T = read<int>();
    while(T --) {
        GoedelMachine::init();
        GoedelMachine::main();
    }
    return 0;
}
```


---

## 作者：jasonshen_ (赞：0)

[题面传送门](https://www.luogu.com.cn/problem/CF856A)

## 思路
其实很好理解，给定一个数组 $A$ 和 $n$ 个数，要在求出 $n$ 个数，使 $A_x+A_y\not=A_m+A_n$。理解了这些，其他的就很简单了，直接跟着思路模拟即可。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ss, a[111], s[111], t, z = 1;
bool l[2100000];
int main()
{
    for (cin >> t; z <= t; z++)
    {
        for (int i = 1; i < n; i++)
            for (int j = i + 1; j <= n; j++)
                l[abs(a[i] - a[j])] = 0;
        ss = 0;
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        for (int x = 1; x <= 1000000 && ss < n; x++)
        {
            if (l[x])
                continue;
            s[++ss] = x;
            for (int i = 1; i < n; i++)
                for (int j = i + 1; j <= n; j++)
                    l[abs(a[j] - a[i]) + x] = 1;
        }
        if (ss < n)
            cout << "NO\n";
        else
        {
            cout << "YES\n";
            for (int i = 1; i <= n; i++)
                cout << s[i] << ' ';
            cout << "\n";
        }
    }
    return 0;
}
			 			 		   		 	 	 		  	
```

---

## 作者：Tomato_Ya (赞：0)

## 题意
给出 $n$ 个数，让你再求出 $n$ 个数，使 $a_i+a_j\not=a_x+a_y$。
## 思路
首先定义两个数组，一个存放答案，另一个用来做标记，存放 $a_i$ 和 $a_j$ 的和之前有没有用过。

从 $1$ 开始枚举 $i$，求这 $n$ 个数中每一个和 $i$ 的和，并且判断这个和是否之前用过，如果用过了，标记 $b_1=1$，如果都没用过，也就说明和其他的和都不相等。
```cpp
for(int i=1;l<n&&i<=1000000;i++,b1=0)
  for(int j=1;j<=n;j++) {
      s1=a[j]+i;
      if(b[s1])b1=1;
  }
```
当枚举完后，如果 $b_1$ 仍然等于 $0$。说明这时的 $i$ 就是答案，把它存进答案数组，用 $l$ 记录数组的长度，并且把它与 $n$ 个数中每一个数的和都标记一遍。
```cpp
for(int i=1;l<n&&i<=1000000;i++,b1=0)
  if(b1==0){
      s[++l]=i;
      for(int j=1;j<=n;j++)b[a[j]+i]=true;
  }
```
最后，当答案数组长度 $l$ 小于 $n$ 时，说明找不到，输出 ```NO```。反之，则输出 ```YES```。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,t,z=1,a[105],b1,s[2000005],s1,l;bool b[210000];
int main() {
    for(cin>>t;z<=t;z++){
        cin>>n;l=0;
        for(int i=1;i<=n;i++)cin>>a[i];
        memset(b,0,sizeof(b));
        memset(a,0,sizeof(a));
        memset(s,0,sizeof(s));//数组记得清零
        for(int i=1;l<n&&i<=1000000;i++,b1=0){
            for(int j=1;j<=n;j++) {
                s1=a[j]+i;
                if(b[s1])b1=1;//如果两数和用过了，标记为1
            }
            if(b1==0){
                s[++l]=i;//把答案存进数组
                for(int j=1;j<=n;j++)b[a[j]+i]=true;//标记用过的和
            }
        }
        if(l<n)cout<<"NO\n";
        else{
            cout<<"YES\n";
            for (int i=1;i<=l;i++)cout<<s[i]<<' ';
            cout<<endl;
        }
    }
    return 0;
}
```


---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF856A)

### $\texttt{Description}$

给定一个长度为 $n$ 的 $A$ 数组并让你构造一个新的长度为 $n$ 的 $B$ 数组，满足 $A_i+B_j \ (i,j \in [1,n])$ 都互不相同，且需满足 $1 \le A_i,b_i \le 10^6$ 的条件，如果有这样的序列，输出 `YES` 和方案，否则输出 `NO` 就行了。

本题有多组数据。

### $\texttt{Solution}$

这题只需要用桶数组标记，然后从 $1$ 到 $10^6$ 循环枚举，如果满足条件就加进 $B$ 数组，如果最后 $B$ 数组里面没有 $n$  个元素，就输出 `NO` ，否则输出 `YES` 。

### $\texttt{Code}$

```cpp 
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e2 + 5;
const int maxn = 2e6 + 5;
const int M = 1e6;

int t, n, a[N], b[N];
int tong[maxn];
int cnt, flag;

void init() {
	cnt = flag = 0;
	memset(tong, 0, sizeof(tong)); // 清空桶数组
	
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	// 读入
	
	return;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> t;
	
	while (t--) {
		init(); // 初始化并输入数据
		
		for (int i = 1; i <= M; i++) {
			flag = 0; // 假设一开始满足条件
			
			for (int j = 1; j <= n; j++) {
				int num = a[j] + i;
				
				if (tong[num] == 1) {
					flag = 1; // 如果有重复，就标记
					break; // 已经不符合条件，没有必要继续循环
				}
			}
			
			if (!flag) { // 满足条件
				b[++cnt] = i; // 将 i 加入 b 数组
				
				for (int j = 1; j <= n; j++) { // 标记
					int num = a[j] + i;
					tong[num] = 1;
				}
			}
			
			if (cnt == n) break; // 优化，如果已经有 n 个就直接结束循环
		}
		
		if (cnt < n) { // 没有找到 n 个满足条件的数
			cout << "NO\n";
			continue;
		}
		
		cout << "YES\n";
		for (int i = 1; i <= cnt; i++) {
			cout << b[i] << (i == cnt ? "\n" : " ");
			// 输出方案 如果是最后一个就换行
		}
	}
	
	return 0;
}
```

完结。

---

