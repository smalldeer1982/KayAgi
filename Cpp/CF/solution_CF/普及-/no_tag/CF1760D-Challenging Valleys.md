# Challenging Valleys

## 题目描述

You are given an array $ a[0 \dots n-1] $ of $ n $ integers. This array is called a "valley" if there exists exactly one subarray $ a[l \dots r] $ such that:

- $ 0 \le l \le r \le n-1 $ ,
- $ a_l = a_{l+1} = a_{l+2} = \dots = a_r $ ,
- $ l = 0 $ or $ a_{l-1} > a_{l} $ ,
- $ r = n-1 $ or $ a_r < a_{r+1} $ .

Here are three examples:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1760D/03a48b22ef3c4e8e328e6caa6008b87fe7824d84.png)The first image shows the array \[ $ 3, 2, 2, 1, 2, 2, 3 $ \], it is a valley because only subarray with indices $ l=r=3 $ satisfies the condition.

The second image shows the array \[ $ 1, 1, 1, 2, 3, 3, 4, 5, 6, 6, 6 $ \], it is a valley because only subarray with indices $ l=0, r=2 $ satisfies the codition.

The third image shows the array \[ $ 1, 2, 3, 4, 3, 2, 1 $ \], it is not a valley because two subarrays $ l=r=0 $ and $ l=r=6 $ that satisfy the condition.

You are asked whether the given array is a valley or not.

Note that we consider the array to be indexed from $ 0 $ .

## 说明/提示

The first three test cases are explained in the statement.

## 样例 #1

### 输入

```
6
7
3 2 2 1 2 2 3
11
1 1 1 2 3 3 4 5 6 6 6
7
1 2 3 4 3 2 1
7
9 7 4 6 9 9 10
1
1000000000
8
9 4 4 5 9 4 9 10```

### 输出

```
YES
YES
NO
YES
YES
NO```

# 题解

## 作者：cjh20090318 (赞：12)

大家好，我是 CQ-C2024 蒟蒻 CJH。

## 题意

给定数组 $a_0,\dots,a_{n-1}$，请你找出一段 $l \sim r$ 的序列满足以下条件：

1. $0 \le l \le r \le n-1$。

2. $a_l=a_{l+1}=a_{l+2}=\dots=a_{r}$。

3. $l=0$ 或 $a_{l-1} > a_{l}$。

4. $r=n-1$ 或 $a_r<a_{r+1}$。

如果**恰好只有一段**符合以上条件的序列则输出 `YES`，否则输出 `NO`。

## 分析思路

这里我们枚举在 $0 \sim n-1$ 中枚举左端点 $l$，再从 $l \sim n-1$ 中找到最大的右端点 $r$ 满足 $a_r=a_l$。

再判断是否满足条件 3 和条件 4 即可。

## 代码

```cpp
//the code is from chenjh
#include<bits/stdc++.h>
using namespace std;
int a[200002];
void solve(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
    //注意数组是从第 0 个开始输入。
	bool fl=0;//判断是否有解。
	for(int i=0;i<n;){//枚举左端点。
		int j;
		for(j=i;j<n && a[j]==a[i];j++);//右端点不断向右扩展。
		int l=i,r=j-1;//因为此时 j>=n 或 a[j]!=a[i]，所以右端点为 j-1。
		if((l==0||a[l-1]>a[l]) && (r==n-1||a[r]<a[r+1])){//判断是否满足条件。
			if(fl){puts("NO");return;}//已经有一个解，不满足恰好只有一个解。
			else fl=1;//标记为有解
		}
		i=j;
	}
	puts(fl?"YES":"NO");//有解输出 "YES"，无解输出 "NO"。
}
int main(){
	int t;scanf("%d",&t);
	while(t--) solve();
	return 0;
}
```

*谢谢大家！*

---

## 作者：srds_cbddl (赞：9)

- ### 暴力

对于每组数据，使用双层循环枚举每个 $l, r$，然后再用一层循环判断是否符合所有条件。

时间复杂度：$\mathcal {O} (n ^ 3)$。

- ### 去重

仔细阅读题目并化简题面，可得：

给定一个数组，求这个数组是否仅存在一个递增段和一个递减段。

并不难发现重复的数完全无用，我们只用构造一个数组 $b$，当且仅当 $b_0 \ne b_1 \ne \dots \ne b_{n - 1}$（即经过去重后的 $a$ 数组）。最后判断 $b$ 是否满足条件 3 及 4 即可。注意当 $n = 1$ 时也是一个 ```valley``` 数组。

时间复杂度：$\mathcal {O} (n)$。

Code：

```cpp
/*
 * @Author: Dream_Town
 * @Editor: Dev-C++ 5.11
 * @Platform: Luogu
 */

#include <bits/stdc++.h>
using namespace std;

const int maxn = 2 * 1e5 + 5;

int t;

void solve () {
    cin >> t;
    while (t --) {
        int n, a[maxn];
        cin >> n;
        for (int i = 0; i < n; i ++) {
            cin >> a[i];
        }
        if (n == 1) {
            cout << "YES\n";
            continue;
        }
        bool up = false, down = true;
        for (int i = 1; i < n; i ++) {
            if (a[i] > a[i - 1]) up = true;
            if (a[i] < a[i - 1]) {
                if (up) {
                    down = false;
                    break;
                }
            }
        }
        if (down) cout << "YES\n";
        else cout << "NO\n";
    }
}

signed main () {
	ios::sync_with_stdio (false);
	cin.tie (0);
	solve ();
	return 0;
}
```


---

## 作者：BLX32M_10 (赞：3)

观察峡谷的判断条件，不难发现不是峡谷的都有“上升-平地-下降”段或者“上升-下降”段。

也就是说不能出现以下两种情况：

```
 ___      /\
/   \    /  \

```

于是我们可以记录当前高度是大于、等于还是小于上一个高度，从而确定上下坡情况，然后扫描得到是否有上述两种情况。

扫描的大概过程（伪代码）：

```python
bool flag = 0;
for i = 2 → n:
	while 当前为上坡:
		i++
	if i - 1 是上坡:
		while 当前为平地:
			i++
		if 当前为下坡:
			flag = 1
			break
		i--   <------这里很重要！因为最外面循环还有一
		             个i++，不加就会跳过一个元素。
flag == 0 -> 是峡谷
flag == 1 -> 不是峡谷
```

对于上下坡，预处理就好了。

AC 代码：

```cpp
#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
int a[200005], c[200005]; //a 为原数组，c 为上下坡。
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, lc = 1, rc = 1, mi = 0;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			if (a[i] > a[i - 1])     //预处理上下坡。
				c[i] = 2;
			else if (a[i] == a[i - 1])
				c[i] = 1;
			else
				c[i] = 0;
		}
		bool xxx = 1;
		for (int i = 2; i <= n; i++)     //扫描。
		{
			bool b = 0;
			while (c[i] == 2 && i <= n)
				i++, b = 1;
			if (b && i <= n)
			{
				while (c[i] == 1 && i <= n)
					i++;
				if (c[i] == 0 && i <= n)
				{
					xxx = 0;
					break;
				}
				i--;     //不要忘掉这一行！
			}
		}
		if (xxx)
		{
			printf("YES\n");
		}
		else
			printf("NO\n");
	}
	return 0;
}

---

## 作者：oceanfish (赞：0)

## 题目
给定一个数组 $a$，判断 $a$ 的子序列 $a[l \ldots r]$ 中是否含有 `valley` 序列，其中，`valley` 序列应满足以下几点：

1. $0 \le l \le r \le n-1$，
2. $a_l = a_{l+1} = \cdots = a_r$，
3. $l = 0$ 或 $a_{l-1} > a_l$，
4. $r = n - 1$ 或 $a_{r-1} < a_r$。

------------

## 分析方法
其实 `valley` 的表面意思是山谷，而山谷具有中低两边高的特征，题目中要求数组满足有且只有一个递减段和递增段。

不难发现，在数组中相等的部分没用，因为我们只需要判断有无递减段和递增段，所以我们可以考虑先使用 `unique` 函数进行数组去重，然后判断数组中是否含有 `valley` 数组。

代码就不给出了，可以参考前面大佬的标程

---

## 作者：zgy_123 (赞：0)

CF 中少见的没有思维难度的模拟题！

首先吐槽翻译，少翻了一些重要句子，如 `It is guaranteed that the sum of $ n $ over all test cases is smaller than $ 2\cdot10^5 $ .` 意思是 $\sum n<2\times10^{5}$，没有这句话就会 TLE。

看见题解区的做法都是去重，复杂度较大，不如手写。

这里，我们可以用一个栈来代替数组（最好也是手写），如果新输入的元素与栈顶相同就入栈，否则不做改变。

还有一个技巧，可以将首尾两项标记为 $\infty $，就可以不用特判 $l=0$ 或 $r=n-1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int q[200005],k;
int main(){
	int t;
	cin>>t;
	while(t--){
		k=0;
		int n,cnt=0,x;
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>x;
			if(x!=q[k]) q[++k]=x;
		}
		q[0]=q[k+1]=2e9;
		for(int i=1;i<=k;i++)
			if(q[i]<q[i-1]&&q[i]<q[i+1]) cnt++;
		if(cnt==1) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

```

---

## 作者：Wander_E (赞：0)

这题其实不需要完整的考虑一整个区间，只要考虑谷底即可。

谷底有三种情况。

#### 1.完整谷底
该类谷底含有三个数 $a$，$b$，$c$。

$a > b$，$b < c$ 例如 $3$，$1$，$2$。
#### 2.开头谷底
该类谷底含两个数 $a$，$b$ 且 $a$，$b$ 分别为数组的 $1$，$2$ 项。

$a < b$ 例如 $2$，$1$。
#### 3.结尾谷底
此类谷底与与第二类类似，其中 $a > b$，$a$，$b$ 为数组的最后两项。

### 注意：这种方法必须去重否则会出现平坦的谷底。
### 例如： $4,3,3,3,4$ 就会被认为是不符合要求的。

------------

去重代码（这里使用 vector 的 unique 也行）：
```cpp
for (int i = 1; i <= n; i++) 
{
	int t;
	cin >> t;
	if(t == a[k]) 	continue;
	a[++k] = t;
}
```
找谷底代码：
```cpp
for(int i = 1; i <= k; i++)
{
	if ((i == 1 || a[i] < a[i - 1]) && (i == k || a[i] < a[i + 1]))
		cnt++;
}
```
完整 ACode：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t;
int n;
int a[10005];
bool up, down;
signed main()
{
	cin >> t;
	while(t--)
	{
		int k = 0;
		cin >> n;
		for (int i = 1; i <= n; i++) 
		{
			int t;
			cin >> t;
			if(t == a[k]) 	continue;
			a[++k] = t;
		}
		int cnt = 0;
		for(int i = 1; i <= k; i++)
		{
			if ((i == 1 || a[i] < a[i - 1]) && (i == k || a[i] < a[i + 1]))
				cnt++;
		}
		if(cnt == 1) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
} 
```

---

## 作者：PeaceSunset (赞：0)

这题是一个**模拟**题。

#### 思路：
对于每个数组，我们让 $l$ 从 0 开始，一直遍历到 $n-1$。

再让 $r$ 从 $l+1$ 开始，如果 $r$ 小于 $n$ 且 $a_r=a_l$ 时，就让 $r$ 继续向后遍历。

然后通过 $l$ 和 $r$，就能得出整个子序列的长度，接着判断 $l$ 和 $r$ 是否满足第三条和第四条要求。

最后判断整个数组是否只有一个满足要求的子序列，然后输出就行了。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t,n,a[N];
void solve(){
	cin>>n;
	for(int i=0;i<n;i++)cin>>a[i];
	bool flag=false,fll=false;
	for(int l=0;l<n;l++){
		int r=l+1;
		while(r<n&&a[r]==a[l])r++;
		r--;
		if((l==0||a[l-1]>a[l])&&(r==n-1||a[r+1]>a[r])){
			if(flag){cout<<"NO\n";return;}
			flag=true;
		}
		l=r;
	}
	if(flag)cout<<"YES\n";
}
signed main(){
	cin>>t;
	while(t--)solve();
	return 0;
}
```


---

## 作者：zfx_VeXl6 (赞：0)

因为要求的区间是 $a_l=a_{l+1}=a_{l+2}=\cdots=a_r$ 的一段，所以可以先去重后来判断，这样要求的区间就缩成了一个满足 $a_i<a_{i-1}$ 且 $a_i<a_{i+1}$ 的点。设去重后数组的长度为 $m$，由于 $a_1$ 前和 $a_m$ 后没有元素，因此设置虚拟元素 $a_0=a_{m+1}=\inf$，保证 $a_1<a_0$ 且 $a_m<a_{m+1}$，可以不用特判。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
int t,n,a[200002],m,s;
int main()
{
    cin>>t;
    //虚拟元素a[0]
    a[0]=INF;
    while(t--)
    {
        cin>>n;
        m=s=0;
        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            //去重
            if(a[i]!=a[i-1])
                a[++m]=a[i];
        }
        //虚拟元素a[m+1]
        a[m+1]=INF;
        //统计区间个数
        for(int i=1;i<=m;i++)
            if(a[i]<a[i-1]&&a[i]<a[i+1])
                s++;
        cout<<(s<=1?"YES\n":"NO\n");
    }
    return 0;
}
```

---

## 作者：litachloveyou (赞：0)

题目中的 $a_l=a_{l+1}=...=a_r$ 可以使用 unique 函数将连续相同的数留下一个，这样也不会影响判断。

然后就非常简单了，只需要简单粗暴地判断题目所要求的区间是否只有一个即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve()
{
	int n;
	cin >> n;
	vector<int>a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	n = unique(a.begin(), a.end()) - a.begin();
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if ((i == 0 || a[i] < a[i - 1]) && (i == n - 1 || a[i] < a[i + 1]))
		{
			cnt++;
		}
	}
	puts(cnt == 1 ? "YES" : "NO");
}
int main()
{
	int T = 1;
	scanf("%d", &T);
	while (T--)solve();
	return 0;
}
```


---

## 作者：_Remake_ (赞：0)

## 题目分析
给定一个序列，定义序列外的数为无穷大，判断所有数字是否**有且仅有**一个上升段和一个下降段。

可以发现，序列初的状态为下降状态，而序列末的状态为上升状态，所以只需要判断序列内部是否出现先上升后下降的段即可。
## 代码

```cpp

#include<bits/stdc++.h>
using namespace std;
//#define int long long
long long read()
{
    long long n=0,k=1;
    char ch=getchar();
    while(ch>'9'||ch<'0')
    {
        if(ch=='-')
        {
            k=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        n=n*10+ch-'0';
        ch=getchar();
    }
    return n*k;
}
int n,m,T;
int A[200001];
int B[200001];
std::string S;
signed main()
{
	T=read();
	while(T--)
	{
		n=read();
		for(int r=0;r<n;r++)
		{
			A[r]=read();
		}
		int cnt=0;
		bool up=0;
		for(int r=0;r<n-1;r++)
		{
			if(A[r+1]>A[r])
			{
				if(up==0)
				{
					cnt++;
				}
				up=1;
			}
			else if(A[r+1]<A[r])
			{
				up=0;
			}
		}
		if(up==0)
		{
			cnt++;
		}
		if(cnt!=1)
		{
			puts("NO");
		}
		else
		{
			puts("YES");
		}
	}
    return 0;
}

```


---

