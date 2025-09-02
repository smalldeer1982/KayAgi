# Island Puzzle

## 题目描述

A remote island chain contains $ n $ islands, labeled $ 1 $ through $ n $ . Bidirectional bridges connect the islands to form a simple cycle — a bridge connects islands $ 1 $ and $ 2 $ , islands $ 2 $ and $ 3 $ , and so on, and additionally a bridge connects islands $ n $ and $ 1 $ . The center of each island contains an identical pedestal, and all but one of the islands has a fragile, uniquely colored statue currently held on the pedestal. The remaining island holds only an empty pedestal.

The islanders want to rearrange the statues in a new order. To do this, they repeat the following process: First, they choose an island directly adjacent to the island containing an empty pedestal. Then, they painstakingly carry the statue on this island across the adjoining bridge and place it on the empty pedestal.

Determine if it is possible for the islanders to arrange the statues in the desired order.

## 说明/提示

In the first sample, the islanders can first move statue $ 1 $ from island $ 1 $ to island $ 2 $ , then move statue $ 2 $ from island $ 3 $ to island $ 1 $ , and finally move statue $ 1 $ from island $ 2 $ to island $ 3 $ .

In the second sample, the islanders can simply move statue $ 1 $ from island $ 1 $ to island $ 2 $ .

In the third sample, no sequence of movements results in the desired position.

## 样例 #1

### 输入

```
3
1 0 2
2 0 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
2
1 0
0 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
4
1 2 3 0
0 3 2 1
```

### 输出

```
NO
```

# 题解

## 作者：封禁用户 (赞：1)

题目传送门：[CF634A Island Puzzle](https://www.luogu.com.cn/problem/CF634A)

**题目大意：** 有一个环，相邻两个和首位互通，其中的数字是$1$到$n-1$（$0$是空位），给出初始状态和目标状态，问初始状态是否可以经过若干次移动变为目标状态。

**题解：** 显然交换并不会影响字符串的相对位置，所以只需要记录一下相对位置就可以了。

$Code:$

```cpp
#include<cstdio>
using namespace std;
#define ll long long 
inline ll read(){
   ll s=0;bool w=1;char ch=getchar();
   while(ch<'0' || ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0' && ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int N=2e5+5;
int n,t,a[N],b[N],x;
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		x=read();
		if(x)a[t++]=x;
	}
	t=0;
	for(int i=1;i<=n;i++){
		x=read();
		if(x)b[t++]=x;
	}
	int sum=-1;
	for(int i=0;i<n;i++)
		if(b[i]==a[0]){
			sum=i;
			break;
		}
	for(int i=0;i<n-1;i++)
		if(a[i]!=b[(i+sum)%(n-1)]){
			printf("NO");
			return 0;
		}
	printf("YES");
	return 0;
}
```


---

## 作者：wurang (赞：0)

由于此题仅能使 ${0}$ 与相邻的数字交换，所以除了零的其它数相对的位置不会改变。

我们可以结合第三组样例理解：

```python
4
1 2 3 0
0 3 2 1

  1      0      2      2
0   2  1   2  1   0  1   3
  3      3      3      0
```
若去掉 ${0}$ 从数字 ${1}$ 顺时针数，无论是哪种情况，均只能得到 ${1\ 2\ 3}$ 的排列顺序。

那么我们可以将原状态和目标状态中的 ${0}$ 去掉，然后判断它们中的元素的相对位置是否相等即可。

实现：

令 ${j}$ 目标状态中与原状态第一个数相同的数的下标。

从 ${j}$ 和原状态第一个数往后找 ${n}$ 个，若有不同，则输出 NO，否则输出 YES。

细节见代码吧。


```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
int a[200005];
int f[200005];

int main()
{
	memset(a,-1,sizeof(a));//初始化，避免可能会与题目中的0冲突 
	memset(f,-1,sizeof(f));
	cin >> n;
    n--;//忽略0 
    for(int i = 0; i < n; i++)//数组从0开始，以便实现环（大于等于n的数可以直接 mod n） 
    {
        cin >> a[i];
        if(a[i] == 0)//若遇到0，则跳过 
        {
            a[i] = -1; 
            i--;
        }
    }
    for(int i = 0; i < n; i++)
    {
        cin >> f[i];
        if(f[i] == 0)
        {
            f[i] = -1;
            i--;
        }
    }
    int j;
    for(j = 0; j < n; j++)if(f[j]==a[0])break;//找出目标状态中 与 原状态第一个数相同的数的下标 
    for(int i = 0; i < n; i++,j++)
    {
        if(a[i] != f[j%n])//若不同，则无法达成指定状态 
        {
            cout << "NO";
            exit(0);//结束程序 
        }
    }
    cout << "YES";//若完全相等， 则能达成指定状态  
    return 0;
}
```

---

## 作者：_shine_ (赞：0)

只移动 $0$ 说明剩下的数的相对位置是不变的，又因为每个点的数均是唯一的，说明如果移动可以相同则从开始到最后都是一样的（不看 $0$），所以复制两遍并且枚举开始端点再扫一遍接下来的 $n-1$ 个数判断是否成立即可。
#### code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+10;
int n,a[maxn],b[maxn],idx;
signed main(){
	cin >> n;
	for(int i=1;i<=n;++i){cin >> a[i];if(a[i]!=0)a[++idx]=a[i];}idx=0;
	for(int i=1;i<=n;++i){cin >> b[i];if(b[i]!=0)b[++idx]=b[i];}idx=0;
	int id_idx=n-1,old_idx=0;
	for(int i=1;i<=n;++i){if(a[i]==0)continue;a[++id_idx]=a[i],a[++old_idx]=a[i];if(a[i]==b[1])idx=i;}
	for(int i=0;i<n-1;++i){
		if(a[i+idx]!=b[i+1]){puts("No");return 0;}
	}
	puts("Yes");
	return 0;
} 
```

---

## 作者：Ryan_Adam (赞：0)

## CF634A Island Puzzle 题解
### 分析
由于我们仅能移动 $0$，所以其它数字的相对顺序较原来应该是不变的，所以我们从环中删除 $0$ 再判断相对位置即可。

还有需要注意的是本题是一个环，找到末尾需要用取模操作回到开头继续比较。

### 示例代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5; 
int a[N],b[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin>>n;
	int aa,bb;
	for(int i=0;i<n-1;i++)
	{
		cin>>a[i];
		if(a[i]==0)i--;
		if(a[i]==1)aa=i;
	}
	for(int i=0;i<n-1;i++)
	{
		cin>>b[i];
		if(b[i]==0)i--;
		if(b[i]==1)bb=i;
	}
//	for(int i=0;i<n;i++)cout<<a[i]<<" ";
//	cout<<endl;
//	for(int i=0;i<n;i++)cout<<b[i]<<" ";
//	cout<<endl;
	bool flag=1;
	for(int i=0;i<n-1;i++)
	{
//		cout<<a[(i+aa)%(n-1)]<<" "<<b[(i+bb)%(n-1)]<<endl;
		if(a[(i+aa)%(n-1)]!=b[(i+bb)%(n-1)])
		{
			flag=0;
			break;
		}
	}
	if(flag)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

可以发现，无论怎么交换位置，除 $0$ 外的其它元素的相对位置不变。因此我们将原来的环和目标状态中的 $0$ 去掉，然后判断它们中的元素的相对位置是否相等即可。

判断方法：由于每个点上的数互不相同，我们循环找到一个相同的数，然后向后枚举 $n$ 个数判断是否都相等即可。

```c++
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+2;
int a[N],b[N];

int main(){
	int n;cin>>n;int k=0;
	for(int i=0; i<n; i++){
		cin>>a[i-k];
		if(a[i]==0) k=1;
	}
	k=0;
	for(int i=0; i<n; i++){
		cin>>b[i-k];
		if(b[i]==0) k=1;
	}
	bool f=true;
	for(int i=0; i<n-1; i++){
		if(b[i]==a[0]){
			for(int j=1; j<n-1; j++) if(a[j]!=b[(i+j)%(n-1)]) f=false;
			if(f){
				cout<<"YES";
				return 0;
			}
		}
	}
	cout<<"NO";
	return 0;
}
```

---

## 作者：Paracelestia (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF634A)

## $\texttt{Description}$

给你一个环，环上点的编号是 $[0, n - 1]$ 的一个排列。

编号为 $0$ 的点可以与相邻的点交换编号，问最终是否能使点的编号与目标排列相同。

## $\texttt{Solution}$

可以发现编号的相对位置不会变化。

那么只有去除 $0$ 后，目标排列是原排列的循环移位的结果时才有解。

实现十分丑陋，还请见谅。

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 114514 * 4
#define M 1919810
#define fi first
#define se second

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;

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

int n, a[N], b[N], p;

signed main() {
    n = read<int>();
    for(int i = 1, j = 0; i <= n; ++ i) {
        int x = read<int>();
        if(x) a[++ j] = x;
    }
    for(int i = 1, j = 0; i <= n; ++ i) {
        int x = read<int>();
        if(x) b[++ j] = x;
    }
    for(int i = 1; i < n; ++ i) {
        b[i + n - 1] = b[i];
        if(b[i] == a[1]) p = i;
    }
    for(int i = 1; i < n; ++ i) {
        if(b[p + i - 1] != a[i]) {
            puts("NO");
            return 0;
        }
    }
    puts("YES");
    return 0;
}
```


---

## 作者：yangzd (赞：0)

# 题目大意：

有 $n$ 个位置，相邻两个位置均互通， $n$ 和 $1$ 也互通，把 $1...n-1$ 放进去，一个数字只能移动到相邻的空位置上去，给出一个初始状态和一个目标状态，问是否初始状态是否可以经过适当移动变为目标状态。

# 分析：

把两个序列看作两个环，忽略 $0$ 的情况下这两个环旋转同构才有解，所以从 $1$ 开始依次把数拿出来判断是否相等即可

# 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[200005],b[200005];
bool flag;

signed main()
{
	ios::sync_with_stdio(0);

    cin >> n;
    int p1,p2;

    for(int i=0; i<n; i++)
    {
        cin >> a[i];

        if(a[i]==1)
            p1=i;
    }

    for(int i=0; i<n; i++)
    {
        cin >> b[i];

        if(b[i]==1)
            p2=i;
    }

    for(int i=p1,j=p2,k=0; k<n; i=(i+1)%n,j=(j+1)%n,k++)
    {
        if(a[i]==0)
            i=(i+1)%n;

        if(b[j]==0)
            j=(j+1)%n;

        if(a[i]!=b[j])
        {
            flag=true;

            break;
        }
    }

    if (flag)   
        cout << "NO" << endl;
        
    else
        cout << "YES" << endl;

    return 0;
}
```

---

## 作者：lizhixun (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF634A)

### $\texttt{Description}$

给定一个环，点的编号为 $1\sim n$，其中 $i$ 和 $i+1$ 相邻，且 $1$ 和 $n$ 相邻。每个点上有一个 $0 \sim n-1$ 范围内的数，且每个点上的数互不相同。每次可以交换 $0$ 所在的点和任意一个与其相邻的点的数，问能否达成指定的状态。

### $\texttt{Solution}$

$0$ 交换后肯定不会影响相对的位置，所以我们其实可以不用管 $0$，只需要找出相同的一项并向后对比就行了。

### $\texttt{Code}$

代码不是很难，只需要按照思路模拟就行了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 5;
int n, a[N], a1[N], QAQ, QWQ;

inline int read() {
	int x = 0, f = 1;
	char ch;
	
	while (isdigit(ch) == 0) {ch = getchar(), f = (ch == '-' ? -1 : 1);}
	while (isdigit(ch) == 1) {x = x * 10 + (ch ^ 48), ch = getchar();}
	return x * f;
}

inline void write(string s) { //自创字符串输出函数
	while (!s.empty()) {
		putchar(s[0]);
		s.erase(0, 1);
	}
}

signed main() {
	n = read();
	
	for (int i = 1; i <= n; i++) {
		int x = read();
		if (x) a[++QAQ] = x;
	}
	
	QAQ = 0;
	for (int i = 1; i <= n; i++) {
		int x = read();
		
		if (x != 0) a1[++QAQ] = x;
		if (a1[QAQ] == a[1]) QWQ = QAQ;
	}
	
	bool T_T = 1; //假设是 YES
	for (int i = 1; i <= QAQ; i++) {
		if (a[i] != a1[QWQ]) {
			T_T = 0; //不符合条件就直接break 
			break;
		}
		
		QWQ = QWQ % QAQ + 1;
	}
	
	write((T_T ? "YES" : "NO"));
	return 0;
}
```

完结。

---

## 作者：koukou (赞：0)

## 思路：
由于 $0$ 的交换并不会影响相对的位置，所以我们完全不用管它，找到两个序列中相同的一项并向后对比是否相同就可以了。

## 代码：
```cpp
#include<iostream>
using namespace std;
int n, s[200005], s1[200005], t, k;
int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
    {
		int x;
        cin >> x;
		if(x != 0)
        {
            s[++t] = x;
        }
	}
	t = 0;
	for(int i = 1; i <= n; i++)
    {
        int x;
		cin >> x;
		if(x != 0) 
        {
           s1[++t] = x;
        }
		if(s1[t] == s[1])
        {
            k = t;
        }
	}
	for(int i = 1; i <= t; i++)
    {
		if(s[i] != s1[k])
        {
			cout << "NO";
			return 0;
		}
		k = k % t + 1;
	}
	cout << "YES";
	return 0;
}
```


~~希望管理员审核通过~~

---

## 作者：JYX0924 (赞：0)

很显然可以得到的结论是，无论位置怎么变化，数的相对位置总是不变。因此，只需要用两个数组存储一下现在的状态和目标状态的相对位置，然后比较一下判断是否一样。

判断时任意找一个位置，然后循环一次就可以了。

下面是 AC 代码。
```c
#include<bits/stdc++.h>
using namespace std;
int n,a[200005],b[200005],x,tt,pos1,pos2;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>x; if(x>0) a[++tt]=x;
	}
	tt=0;
	for(int i=1;i<=n;i++)
	{
		cin>>x; if(x>0) b[++tt]=x;
	}
	for(int i=1;i<=tt;i++)
	{
		if(a[i]==1) pos1=i;
		if(b[i]==1) pos2=i;
	}
	int j=0;
	while(j<=tt)
	{
		if(a[pos1]!=b[pos2]) {cout<<"NO"; return 0;}
		pos1=pos1%tt+1; pos2=pos2%tt+1;
		j++;
	}
	cout<<"YES";
	return 0;
}
```
谢谢大家！！！

---

