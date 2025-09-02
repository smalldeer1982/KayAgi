# GCD Table

## 题目描述

有一个长度为$n$的数列$a$，它可以生成一个$n*n$的数表，数表的第$i$行第$j$列存放的数字是$\gcd(a[i],a[j])$ （即$a[i]$和$a[j]$的最大公因数）。

![一个例子：](https://cdn.luogu.com.cn/upload/image_hosting/zv3hmpih.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

举个例子，上面那个表，就是由数列$a[]=\{4,3,6,2\}$生成的。

现在我们要做这样一件事情：将这个数表中的这$n*n$ 个数打乱，得到一个长度为$n*n$的序列(可参考样例1)。在已知这个序列的情况下，请还原出数列$a$。

## 样例 #1

### 输入

```
4
2 1 2 3 4 3 2 6 1 1 2 2 1 2 3 2
```

### 输出

```
4 3 6 2```

## 样例 #2

### 输入

```
1
42
```

### 输出

```
42 ```

## 样例 #3

### 输入

```
2
1 1 1 1
```

### 输出

```
1 1 ```

# 题解

## 作者：Mine_King (赞：27)

首先我们有一个结论：$\gcd(a,b) \le \min(a,b)$  
这个应该是比较显然的吧 QwQ。

然后就可以发现，数表中最大的数一定是出现在原数列中的。  
证明：假设数表中最大的数是 $x$，那么它只可能是 $x = \gcd(x,x)$，否则必须要有一个更大的数 $y$ 与另一个大于等于 $y$ 的数 $\gcd$ 之后得到，但此时数表中又会出现一个更大的数 $\gcd(y,y)=y$，与实际不符，得证。  

然后还有一点就是，数表中次大的数也一定在原数列中出现。  
证明：我们已经知道原数列中最大的数是 $x$，如果数表中的次大值为 $\gcd(y,z)$ 且 $y \not= z$，那么 $\gcd(\max(y,z),\max(y,z))$一定比它更大，与实际不符。  
如果数表中的次大值为 $\gcd(x,k)$，那么它 $\le k$。  
如果数表中的次大值为 $\gcd(k,k)=k$，那么原数列中就有了 $k$。  
此时第二种情况无论是否成立（若成立则 $\gcd(x,k) = k$），次大值都为 $k$，也出现在原数列中。  
语文水平不好，不知道说得清不清楚 QwQ。

那么第三大值呢？它就不一定出现在原数列中了，它可能是 $\gcd(x,k)$。  
但是，如果我们把**两个** $\gcd(x,k)$ 都从数表中剔除，那么可以认为 $x,k$ 就不会对数表中的最大值产生影响了（因为开头的结论），那么此时数表中的最大值就又一定出现在原数列中了。  
再接下来的最大值呢？可能是上面三个的 $\gcd$，但只要把它们都剔除（**两个**），就又不会有影响了。

由此，我们得到了此题的解法：每次把数表中的最大值取出来，它是原数列中的数。然后，把它与之前被取出来的 $\gcd$ 都从数表中剔除。如此循环往复，直到取满 $n$ 个数或数表被取空为止。  
剔除 $\gcd$ 的操作需要用到桶，但是由于值域太大，我们用 $map$ 来实现。

具体实现可见代码：
```cpp
#include<map>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,cnt,ans,a[505],num[250005];
map<int,int>mp;
int gcd(int _a,int _b){return _b==0?_a:gcd(_b,_a%_b);}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n*n;i++)
	{
		int x;
		scanf("%d",&x);
		if(!mp[x]) num[++cnt]=x;
		mp[x]++;
	}
	sort(num+1,num+cnt+1);
	for(int i=cnt;i>=1&&ans<n;)
	{
		while(!mp[num[i]]) i--;
		a[++ans]=num[i];//把数表中的最大值记入答案
		mp[num[i]]--;//删掉它（因为它实际上是gcd(num[i],num[i])。
		for(int j=1;j<ans;j++) mp[gcd(num[i],a[j])]-=2;//删掉它与其他数的gcd
	}
	for(int i=1;i<=ans;i++) printf("%d ",a[i]);
	return 0;
}
```

---

## 作者：Guess00 (赞：7)

## $\texttt{CF582A}\ \text{GCD}\ \text{Table}$
明显$\gcd(x,y)\leq x,$于是可得数表中$n\times n$个数中最大的数肯定是序列$a$中的数(因为它不可能是比它小的两个数的$\gcd$).

于是重复以下操作便可得到序列$a$:
1. 将最大数$x$加入数列$a$,将$x$从初始读入的数中删除。

2. 将$x$与数列$a$中其他元素的$\gcd$在初始读入的数中删除两个(因为是表格，所以要删两个)。

如何实现上述过程?在读入时再用一个桶存每个数，统计出每个数的个数。给初始的$n\times n$个数从大到小排序，进行如上操作，删除时直接在桶上$-1$.

时间复杂度:$\Theta(n^2\log_2^n)$

$\mathbb{CODE:}$
```
#include <bits/stdc++.h>
using namespace std;
const int MAXN=250005;
int n,i,j,x,cnt,num,a[MAXN],ans[MAXN];
map<int,int> m;//桶 
inline void read(int &x)  //快读 
{
	short negative=1;
    x=0;
    char c=getchar();
    while(c<'0' || c>'9')
    {
    	if(c=='-')
			negative=-1;
		c=getchar();
	}
    while(c>='0' && c<='9')
        x=(x<<3)+(x<<1)+(c^48),c=getchar();
    x*=negative;
}
inline void print(int x)  //快输 
{
    if (x<0)
        putchar('-'),x=-x;
    if (x>9)
        print(x/10);
    putchar(x%10+'0');
}
inline int gcd(int a,int b){return (!a)?b:gcd(b%a,a);} 
inline bool cmp(int a,int b){return a>b;}
signed main(void)
{
	read(n);
	for (i=1;i<=n*n;i++)
	{
		read(x);
		if (!m[x])  //去重 
			a[++cnt]=x;
		m[x]++;
	}
	sort(a+1,a+cnt+1,cmp);//排序 
	for (i=1;i<=cnt && num<n;) //因为去重了,所以这里千万不要写i++ 
	{
		while (!m[a[i]])  //如果这个数已经被删完了 
			i++;
		ans[++num]=a[i];  //将最大的数加入序列 
		m[a[i]]--; 
		for (j=1;j<num;j++)
			m[gcd(ans[j],a[i])]-=2;  //删去最大数和序列中其他数的gcd(2个) 
	}
	for (i=1;i<=num;i++)  //输出 
		print(ans[i]),putchar(' ');
	return 0;
}
```
上面这个代码是用$\text{map}$做桶，对初始$n\times n$去重的版本。之所以去重是因为快，当然你也可以选择不去重。

[$\text{map}$做桶不去重的版本](https://www.luogu.com.cn/paste/utu30zjz)

---

## 作者：andyli (赞：3)

题意：  
对于一个长度为$n$的数列$a$，定义它的GCD Table $G$是一张$n\times n$的二维表，其中$G_{i,j}=\gcd(a_i,a_j)$，现在乱序给出$G$中所有$n^2$个数，求原数列$a$。  
数据保证有解，输出任意一种方案即可。  
$1\leq n\leq 500,G_{i,j}\leq 10^9$  

$G$中最大的数一定也是$a$中最大的数，$G$中次大的数一定也是$a$中次大的数。  
第三、第四大**可能**是由最大和次大的$\gcd$产生的。  

那么就不难想到下面的算法：  
1. 令$p$为$G$中最大的数，在$G$中删除$p$，$a$中加入$p$。  
2. 对于$a$中的所有其他数（设为$q$），在$G$中删除$2$个$\gcd(p,q)$。  
3. 若$G$为空则结束，否则回到(1)。  

时间复杂度$O(n^2\log n)$（使用`multiset`）  

代码如下（[快读模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
int main()
{
    int n;
    io.read(n);
    multiset<int> s;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int x;
            io.read(x);
            s.insert(x);
        }
    vector<int> ans;
    while (!s.empty()) {
        int p = *s.rbegin();
        auto it = s.end();
        it--;
        s.erase(it);
        for (auto q : ans) {
            int t = gcd(p, q);
            auto it = s.upper_bound(t), it2 = it;
            it2--, it2--;
            s.erase(it2, it);
        }
        ans.push_back(p);
    }
    for (auto x : ans)
        io.write(x, " ");
    writeln();
    return 0;
}
```

---

## 作者：谷民 (赞：1)

解题思路：在所有的数组成的集合中，最大的数一定为n个数中的一个，把这个数从集合中减去一个，并把这个数加入数组b中，然后找出第二大的数，将这个数与数组b中的数的最大公因数从集合中减去两个，再把这个数加入数组b中，接着重复上述步骤，找出第三，第四.....第n个数，数组b中的数即为答案。

```cpp
#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
#define N 250010
int a[N],num[N],b[N];
map<int,int>mp;
int n,tot,x;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n*n;++i)
        scanf("%d",&b[i]);
    mp.clear();
    sort(b+1,b+n*n+1);
    tot=0;
    for(int i=1;i<=n*n;++i)
    {
        x=b[i];
        if(mp.find(x)==mp.end())
        {
            mp[x]=++tot;
            a[tot]=x;
            num[tot]=1;
        }
        else ++num[mp[x]];
    }
    int z=1;
    b[1]=a[tot];
    printf("%d ",a[tot]);
    --num[tot];
    for(int i=tot;i>0;--i)
    {
        while(num[i]>0)
        {
            b[++z]=a[i];
            --num[i];
            printf("%d ",a[i]);
            for(int j=1;j<z;++j)
                num[mp[__gcd(b[z],b[j])]]-=2;
        }
    }
    return 0;
}

```

---

## 作者：Robin_kool (赞：0)

注意力惊人，发现最大值一定在原序列里面。

显然有 $\gcd(a,b)\leq \min(a,b)$，故得证。

再次注意力惊人，发现非严格次大值也在里面，因为除了最大值和它本身都比它小，同上。

已经得到了 $2$ 个数，那么它们的最大公因数一定要被删除 $2$ 次，因为原方阵对称。

删完以后，发现之前选出的数和剩下的数没有任何关系，于是剩下数的最大值也一定在原序列里，以此类推。

直接排序复杂度 $O(n^2 \log n^2)$，可以做到 $O(n^2 \log n)$。

---

## 作者：Melo_DDD (赞：0)

CF 已过，由于 RMJ 锅了所以没有在洛谷提交。

题目大意略过。

我们首先将这 $n^2$ 个数字排序，那么最大的数一定在原数组中，~~因为不会怎么证明~~，所以考虑反证法。

注意到 $\gcd(a,b)\le\min(a,b)$，所以我们设 $\gcd(x,y)$ 为最大的且 $x<y$，那么这个最大值一定小于等于 $x$，显然 $\gcd(y,y)=y>x\ge\gcd(x,y)$，所以 $\gcd(x,y)$ 一定不是最大值，矛盾，得证。

同理可得第二大的一定也属于答案。

所以我们每次寻找最大值并加入答案，并且去掉所有我们已经记录过的答案的 $\gcd$（这样可以避免已经记录过的数对原来的影响），剩下的数重复上述过程即可。

举个例子，设最大的数是 $m$，次大的数是 $n$，那么第三大的数可能是 $\gcd(m,n)$，显然不符合条件，所以我们把它去掉避免影响。

注意当 $a\ne b$ 时，$\gcd(a,b)$ 会被统计两次（因为是表格）。

---

## 作者：__qkj__ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF582A)

## 解题思路

因为 $\gcd(a_i,a_i)=a_i$，所以输入的 $n^2$ 个数中，一定包含所求的 $n$ 个数。

又因为 $\gcd(a_i,a_j)>a_i$ 且  $\gcd(a_i,a_j)>a_j$，所以只需要让 $i$ 从 $1$ 到 $n^2$ 遍历 $a$ 数组，分两种情况：

- 当前数未被记录，输出 $a_i$，并且在之前输出过的数中，和 $a_i$ 做一下 $\gcd$，并记录 $2$ 遍（$\gcd(a_i,a_j)$ 一遍，$\gcd(a_j,a_i)$ 一遍）。
- 当前数被记录，说明是被两个不同的数 $\gcd$，$q_{a_i}\gets q_{a_i}-1$（$q$ 为记录的数组）。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int ans[510],t,a[250010];
map<int,int>q;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	for(int i=1;i<=n*n;i++)cin>>a[i];
	sort(a+1,a+n*n+1,greater<int>());
	for(int i=1;i<=n*n;i++)
		if(q[a[i]])q[a[i]]--;
		else
		{
			cout<<(ans[++t]=a[i])<<' ';
			for(int j=1;j<t;j++)q[__gcd(a[i],ans[j])]+=2;
		}
	return 0;
}

```

---

## 作者：QWQ_123 (赞：0)

因为两个数的 $\gcd$ 一定不大于这两个数。

所以考虑将原来的 $n\times n$ 个数从大到小排序。

然后最大的两个就是 $a_1,a_2$，然后将 $\gcd(a_1,a_2)$ 去掉两个后剩下的最大值就是 $a_3$，然后将新产生的 $\gcd$ 继续去掉即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 510 * 510;

int n;
int a[N];
map<int, int> cnt;
vector<int> v;

int gcd(int a, int b) {
	return !b ? a : gcd(b, a % b);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n * n; ++i) scanf("%d", &a[i]);
	sort(a + 1, a + 1 + n * n);
	reverse(a + 1, a + 1 + n * n);
	for (int i = 1; i <= n * n; ++i) {
		if (cnt[a[i]]) {
			--cnt[a[i]];
		} else {
			v.push_back(a[i]);
			for (int j = 0; j < (int)v.size() - 1; ++j) {
				cnt[gcd(v[j], a[i])] += 2;
				// cout << v[i] << ' ' << a[j] << ' ' << gcd(v[i], a[j]) << endl;
			}
		}
	}

	for (auto V : v) printf("%d ", V);

	return 0;
}
```

---

## 作者：luan341502 (赞：0)

由于 $\gcd(a_i,a_i)=a_i$ 也在数列中，因此我们要找的 $n$ 个数必然在数列中。

我们将数列从大到小排序，因为两个数的最大公约数一定小于等于这两个数，所以要选的数肯定是在数列中比较大的。

在选择数的过程中，我们要及时筛掉已选数的最大公约数，因为 $\gcd(a_i,a_j)$ 存在于数列两次，因此我们标记两次。

没被标记的就是可以选的数了。

时间复杂度为 $O(n^2)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,N,a[300005];
int cnt=0,now[505];
map<int,int> t;
void solve(){
	cin>>n;N=n*n;
	for(int i=1;i<=N;i++) cin>>a[i];
	sort(a+1,a+N+1);
	reverse(a+1,a+N+1);
	for(int i=1;i<=N;i++){
		if(t[a[i]]){t[a[i]]--;continue;}
		now[++cnt]=a[i];
		if(cnt==n) break;
		for(int j=1;j<cnt;j++) t[__gcd(a[i],now[j])]+=2;
	}
	for(int i=1;i<=n;i++) cout<<now[i]<<" ";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	solve();
	return 0;
} 
```


---

## 作者：Hadtsti (赞：0)

有意思的思维题。
### 题意简述
由一个数列 $\{a_1,a_2,\cdots,a_{n-1},a_n\}(1\le n\le 500)$ 构造数表 $b$，其中 $b_{i,j}=\gcd(a_i,a_j)$。现在给出打乱之后的 $b$ 的所有元素，要求还原 $a$。

### 题目分析
这个题的突破口在于这样一个结论：表中最大的数 $m$，一定在原序列中出现。

证明：设 $m=\gcd(a_i,a_j)$（不妨设 $a_i\le a_j$），则 $m\le a_i\le a_j=\gcd(a_j,a_j)$。而由于 $\gcd(a_j,a_j)$ 必为矩阵里的数，且 $m$ 是表中最大的数，因此 $m\ge \gcd(a_j,a_j)$。所以 $m=\gcd(a_j,a_j)=a_j$，必在原序列中出现。

找到最大值之后就十分简单了。我们找到了最大值 $m$，也就求出了一项 $a_j$。我们只需要从表中剔除目前已知的与 $a_j$ 有关的所有 $\gcd(a_i,a_j)$ 后重复执行该过程即可。

### 代码实现
~~STL 浓度过高不喜勿喷~~
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x;
map<int,int>S;
vector<int>ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n*n;i++)
		scanf("%d",&x),S[x]++;//把每个数直接扔进桶里
	while(!S.empty())//桶里还有就继续
	{
		auto i=S.end();
		i--;//找到最大的数对应的迭代器
		for(auto j:ans)//遍历 a 中已经确定的数
		{
			int tmp=__gcd(i->first,j);
			S[tmp]-=2;//删掉和当前最大数有关的所有 gcd(a_i,a_j)，注意每个数在表里都出现 2 次，所以个数-=2。
			if(!S[tmp])//删没了就把迭代器也给删了
				S.erase(tmp);
		}
		ans.push_back(i->first);//把最大数扔到答案里
		i->second--;//删掉 gcd(a_j,a_j)
		if(!i->second)
			S.erase(i);//删没了就把迭代器也给删了
	}
	for(auto i:ans)
		printf("%d ",i);//输出
	return 0;
}
```


---

## 作者：Jeremiahy (赞：0)

## 分析

显然有 $\gcd(x,y)\le\min(x,y)$，我们可以得到一个结论：表中最大的数是原数列中最大的数，表中次大的数是原数列中次大的数。

证明：设原数列中的最大数为 $x$，表中一定有 $\gcd(x,x)$，即 $x$。显然原数列中最大的数与自己取最大公约数是是表中最大值，因为与别的数取最大值不会更优（可能相等），只会更差。假设次大的数不是表中次大的数，设表中次大的数为 $\gcd(x,y)$（$x\ne y$，别的数的 $\gcd$ 只会更小），原数列中次大的数为 $z$（$y$ 可能等于 $z$），那么有 $\gcd(z,z)=z<\gcd(x,y)\le\min(x,y)$，这与 $z$ 为次大值不符，故假设不成立。

但是第三大值就不一定了，它可能是最大值与次大值的产物，而不在原数列中。一个直接的想法就是在表中把它去掉，然后再加入表中（已经去掉最大值与次大值）的最大值。

所以具体流程如下：用 ```map``` 维护表中每个数出现的次数，每次取表中的最大值，并将它与前面已经取出来的数的 $\gcd$ 在 ```map``` 中的次数减 $2$（因为可以将 $\gcd$ 的两边反过来，就是对称的），重复上述步骤直到找到 $n$ 个答案。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, tot, cnt, a[501], num[250001];//num 记录不同的数数列
map<int, int> m;
bool cmp(int a, int b) { return a > b; }
signed main() {
	cin >> n;
	for (register int i = 1, z; i <= n * n; i++) {
		cin >> z;
		if (m[z] == 0) //新的数
			num[++tot] = z;
		m[z]++;//出现次数 +1
	}
	sort(num + 1, num + tot + 1, cmp);//从大到小排序
	for (register int i = 1; i <= tot && cnt < n;) {//cnt 达到 n 立即退出
		while (!m[num[i]]) //直到有表中的元素
			i++;
		a[++cnt] = num[i], m[num[i]]--; // a 数组记录答案，m数组出现次数-1
		for (register int j = 1; j < cnt; j++) 
			m[__gcd(num[i], a[j])] -= 2;//与前面的已取出的数的gcd-2
	}
	for (register int i = 1; i <= cnt; i++) 
		cout << a[i] << ' ';
	return 0;
}
```



---

## 作者：_H17_ (赞：0)

## 题目分析

看似很绕的思维题，首先 $\gcd(a,b)\le \max(a,b)$，最大的那个数一定是序列中最大的数。

原因：若 $x$ 是序列中最大的数，$y$ 是其他的一个数，$t$ 是公约数列表中最大的。$\gcd(x,x)=x=t\ge \gcd(x,y)$。

然后第二次使用相同的方法，继续取剩下的最大数，**然后和已有答案更新**。

举个例子，组成的最大公约数序列是 $\{1,1,1,1,2,2,2,4,5\}$。

- 首先答案序列有 $5$ 并且把 $5$ 移除，此时最大公约数序列是 $\{1,1,1,1,2,2,2,4\}$；

- 答案序列加入 $4$ 并且把 $4$ 移除，此时答案序列是 $\{4,5\}$，最大公约数序列是 $\{1,1,1,1,2,2,2\}$；

- 更新已有答案：去除**二个** $\gcd(4,5)$，最大公约数序列 $\{1,1,2,2,2\}$；

- 加入 $2$，去除序列中的 $2$，序列是 $\{1,1,2,2\}$；

- 更新，去掉二个 $\gcd(2,4),\gcd(2,5)$，序列无剩余；

- 答案是 $\{2,4,5\}$。

## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[250001];
map<int,int>mp;
vector<int>ans;
int main(){
    cin>>n;
    for(int i=1;i<=n*n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    n*=n;
    sort(a+1,a+n+1,greater<int>());
    for(int i=1,k;i<=n;i++){
        if(mp[a[i]]){
            ans.push_back(a[i]),mp[a[i]]--;
            for(auto p:ans){
            	if(mp[k=__gcd(a[i],p)])
                	mp[k]-=2;
    		}
        }
    }
    for(auto p:ans)
        cout<<p<<' ';
    return 0;
}
```

---

## 作者：_maple_leaf_ (赞：0)

### [$Luogu$](https://www.luogu.com.cn/problem/CF582A)$\&$[$CF$](http://codeforces.com/problemset/problem/582/A)
## 题意
对于一个长度为 $n$ 的数列 $a$，定义它的 GCD Table G 是一张 $n×n$ 的二维表，其中 $ G_{i,j},= \gcd (a_i,a_j)$，现在乱序给出 G 中所有 $n \times n$ 个数，求原数列 $a$，同时数据保证有解，输出任意一种方案即可。
## 思路
- 思考一下可以发现，这 $n \times n$ 个数中，最大的数一定为 $a$ 中的数，因为正整数与其他任何正整数取 $\gcd$，不会大于原来的数，即 $\gcd(a,b)\le a$，也就是说，这个最大的数（后设为 $x$）是取的 $\gcd(x,x)$，矩阵中也不会有比它更大的数了。

- 接着我们把他从矩阵中删掉。

- 那接下来呢？再思考一下，又可以发现，现在矩阵中最大的还是一定在 $a$ 中，还是那个原因，$\gcd(a,b)\le a$，同时，矩阵中比它大的也被删了，那么也不会有其他两个数能 $\gcd$ 出它了，那同样把他删了。

- 可已经找到的两个在 $a$ 中的数，会通过 $\gcd$ 产生其他的数啊？所以我们在删数后将现在被发现的 $a$ 中的数与其他已经被发现在 $a$ 中的数挨个取 $\gcd$，然后删掉两个每次取出来的 $\gcd$ 的数（两个是因为 $\gcd$ 前后可以交换位置），再依次重复操作，直到选出来 $n$ 为止。

- 同时，这些操作需用桶来完成。

## 代码

```cpp
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0' && ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
const int N=520;
int n,nn,x,mn;
int num[N*N],cnt;
int ans[N],tot;
map<int,int>mp;由于数字要到1e9普通数组存不下
int gcd(){}
int main(){
	n=read();nn=n*n;
	for(int i=1;i<=nn;i++){
		x=read();
		if(!mp[x])判重num[++cnt]=x;
		mp[x]++;累加
	}sort(num+1,num+cnt+1);排序
	for(int i=cnt;i>=1&&tot<n;){别用i++
		while(!mp[num[i]])i--;如果当前数字已被删完，那就跳过
		ans[++tot]=num[i];记录答案
		mp[num[i]]--;删数
		for(int j=1;j<tot;j++)mp[gcd(num[i],ans[j])]-=2;删数*2
	}for(int i=1;i<=tot;i++)cout<<ans[i]<<" ";输出
	return 0;~*完结撒花*~
}
```

---

## 作者：TheShuMo (赞：0)

## 思路

~~题意翻译的很清楚了这里就不讲了。~~

显然，有 $\gcd(a,b) \leq \min(a,b)$，因为一个数的最大因子不会超过它自身，所以两个数的最大公因数肯定也不会超过其中较小的那一个。

对输入的数列进行从大到小排序，记为 $p_1,p_2,\cdots p_{n^2}$。

那么就有结论，在输入的数列中，最大的一个数字 $p_1$ 一定是原数列中的。进而，次大的数字 $p_2$ 也一定是原数列中的，因为假设次大的数字 $p_2$ 不是原数列中的，它就必定是两个数 $a,b$ 的最大公因数，则由 $\gcd(a,b) \leq \min(a,b)$ 可得，$a \geq c, b \geq c$。所以 $c$ 就不是次大的数了，与假设相矛盾，所以次大的数字 $c$ 一定在原数列中。

但是第 $3$ 大的数字 $p_3$ 就不一定了，举个例子，原数列为 $1,2,8,4$。$\gcd(8,4) = 4$，但是 $4 > 2$。所以只要把 $\gcd(p_1,p_2)$ 从原数列中去除出去，剩下的最大值就一定在原数列内了。

接下来只需要找出一个剩余的最大的数，它一定是原数列中的数，把它与已找到的所有数做一个 $\gcd$，然后把桶中的这些数的个数减去 $2$（表中会重复计算两次相同的两个数的 $\gcd$，所以这里应该减去 $2$），剩下的最大的数就是下一个原数列中的数了。可能讲的不大清楚，具体的代码实现可以看下面的代码。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long

namespace IO {
    #define int long long 
    #define gh getchar
    inline int read(){char ch=gh();int x=0;bool t=0;while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();return t?-x:x;}
    inline char getc(){char ch=gh();while(ch<'a'||ch>'z') ch=gh();return ch;}
    inline void write(int x){if(x < 0){putchar('-');x = -x;}if(x > 9){write(x / 10);}putchar((x % 10 + '0'));}
}
using namespace IO;
using namespace std;
const int Maxn = 300010;
map<int,int> mp;// 值域太大了不能用桶
int tmp[Maxn],a[Maxn];
int answer[Maxn];
signed main(){
    int n = read();
    int N = n*n;
    int tot = 0;
    for(int i = 1; i <= N; i++){
        a[i] = read();
        if(!mp[a[i]])tmp[++tot] = a[i];
        mp[a[i]]++;
    }
    sort(tmp+1,tmp+1+tot);
    int ans = 0;
    for(int i = tot; i >= 1 && ans < n;){
        while(!mp[tmp[i]])i--; 
        answer[++ans] = tmp[i];
        mp[tmp[i]]--;
        for(int j = 1; j < ans; j++){
            mp[__gcd(tmp[i],answer[j])]-=2;
        }
    }
    for(int i = 1; i <= ans; i++){
        cout << answer[i] << " ";
    }
}

```


---

