# Two Large Bags

## 题目描述

你有两个装数字的大袋子。初始时，第一个袋子包含 $n$ 个数字：$a_1, a_2, \ldots, a_n$，而第二个袋子为空。你可以执行以下两种操作：

- 从第一个袋子中选择任意数字移动到第二个袋子。
- 从第一个袋子中选择一个同时在第二个袋子中存在的数字，并将其增加一。

你可以以任意顺序执行无限次上述两种操作。是否可能使两个袋子的内容完全相同？

## 说明/提示

让我们分析第六个测试用例：我们将展示使得袋子内容相等的操作序列。初始时，第一个袋子包含数字 $(3, 3, 4, 5, 3, 3)$，第二个袋子为空。

1. 第一次操作：将数字 $3$ 从第一个袋子移动到第二个袋子。状态：$(3, 4, 5, 3, 3)$ 和 $(3)$。
2. 第二次操作：将第一个袋子中的数字 $3$ 增加一。此操作可行因为第二个袋子包含 $3$。状态：$(4, 4, 5, 3, 3)$ 和 $(3)$。
3. 第三次操作：将数字 $4$ 从第一个袋子移动到第二个袋子。状态：$(4, 5, 3, 3)$ 和 $(3, 4)$。
4. 第四次操作：将第一个袋子中的数字 $4$ 增加一。状态：$(5, 5, 3, 3)$ 和 $(3, 4)$。
5. 第五次操作：将数字 $5$ 从第一个袋子移动到第二个袋子。状态：$(5, 3, 3)$ 和 $(3, 4, 5)$。
6. 第六次操作：将第一个袋子中的数字 $3$ 增加一。状态：$(5, 3, 4)$ 和 $(3, 4, 5)$。

由此可见，通过这些操作可以使两个袋子的内容相同，因此答案存在。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
2
1 1
2
2 1
4
1 1 4 4
4
3 4 3 3
4
2 3 4 4
6
3 3 4 5 3 3
6
2 2 2 4 4 4
8
1 1 1 1 1 1 1 4
10
9 9 9 10 10 10 10 10 10 10```

### 输出

```
Yes
No
Yes
Yes
No
Yes
No
Yes
Yes```

# 题解

## 作者：Cold_Eyes_bystander (赞：5)

不难发现，我们可以把一个数放进第二个袋子里，所有跟它一样大的数就都能加一。

但我们不能太贪心，为了让方案合法，我们还要一个数保持不动，来达到两个袋子平衡的目的。

假设有 $x$ 个一样大的数，那么就有 $x-2$ 个数能晋级，而我们知道，$x$ 和 $x-2$ 的奇偶性相同，所以一定不亏。

```c++
#include <bits/stdc++.h>
using namespace std;
int a[2002];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n*2;i++) a[i]=0;
		for(int i=1;i<=n;i++)
		{
			int x;
			cin>>x;
			a[x]++;
		}
		for(int i=1;i<=n*2;i++)
		{
			if(a[i]>=2)
			{
				a[i+1]+=a[i]-2;
				a[i]=2;
			}
		}
		bool f=0;
		for(int i=1;i<=n*2;i++)
		{
			if(a[i]%2==1)
			{
				cout<<"NO\n";
				f=1;
				break;
			}
		}
		if(!f) cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：GreenMelon (赞：4)

既然没有翻译，那就浅浅讲下大意吧。

### 题目大意

有两个袋子，第一个袋子有 $n$ 个数 $a_i$，第二个袋子没有数。你可以从第一个袋子选择一个数进行以下操作（二选一）：

- 将其移至第二个袋子；
- 如果第二个袋子中有与之相同的数，则可以将其加一。

经过若干次操作后，能否使两个袋子中的数相同？

### 思路

首先设一个桶数组记录两个袋子中每个数出现的个数，并从 $1$ 到 $n$ 遍历，若一个数只出现了 $1$ 次说明无解，输出 `NO`，否则至少留下两个，低于两个就无解了，其余全都加一。

注意哈，如果这个数出现的次数低于 $2$ 就不能操作了，因为进行操作后下一个数增加的次数就可能是负数了。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1005
#define mod 998244353
#define ll long long
int t, n, a, b[N];
main(){
#ifdef GreenMelon
	freopen("", "r", stdin);
	freopen("", "w", stdout);
#endif
	cin>>t;
	while(t--){
		bool is=1;
		memset(b, 0, sizeof(b));
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a, b[a]++;
		for(int i=1;i<=n;i++){
			if(b[i]==1){
				is=0;
				break;
			}
			if(b[i]>=2) b[i+1]+=b[i]-2;//由于b[i]不会再遍历了，不必要再加b[i]=2这一操作。
		}
		if(is) cout<<"YES\n";
		else cout<<"NO\n";
	}
}
```

---

## 作者：fish_love_cat (赞：3)

首先发现要增加手上数字需要让对面有相同数字。

那么如果我们要将 $x$ 增加到 $y$，对面必然有数字 $[x,y-1]$。

从大到小枚举手上数字，如果发现无法两两配对，就要将小于当前数字的数字增加上来。

然后找到小数往后推即可。

开个桶处理可以通过。

---

## 作者：xiaobeng_0912 (赞：2)

## $\mathbf{Knowledge}$

1. 模拟

## $\mathbf{Solution}$

我们可以开一个桶记录每个数字出现的次数，然后依次遍历 $1$ 至 $n$，如果发现某个数字只出现了一次，我们发现会无法分配，于是直接输出 `NO`。否则如果某个数字出现了至少两次的话，给这个数字留下两个数就刚好可以分配了，多出来的数直接加一，交给比它大 $1$ 的数来处理，以此类推。

## $\mathbf{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[1001],flag;
int main(){
	scanf("%d",&t);
	while(t--){
        memset(a,0,sizeof(a));
		flag=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
            scanf("%d",&x);
            a[x]++; //该元素个数加一
        }
		for(int i=1;i<=n;i++){
			if(a[i]==1){ //如果某个数只出现了一次
				flag=1; //直接判定无解
				break; //后面的数就不用看了
			}else if(a[i]>=2){ //否则如果某个数出现了至少两次
                a[i+1]+=a[i]-2; //这个数只用留两个，多余的直接交给比它大一的数
            }
		}
		printf("%s\n",(flag)?"No":"Yes");
	}
    return 0;
}
```

---

## 作者：K_yuxiang_rose (赞：1)

先开个桶，$b_i$ 表示数字 $i$ 的数量，贪心地将多个小数变大，具体地，对于第 $i$ 个数，当 $b_i=1$ 时，显然已经无法做到让两个袋子相同，直接输出，否则将数字 $i$ 保留两个（如果没有数字 $i$ 则跳过），剩下的数字 $i$ 变为 $i+1$，如果没出现过 $b_i=1$ 的情况，说明可行。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1005];
int b[1005];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n,flag=0;
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],b[i]=0;
		for(int i=1;i<=n;i++) b[a[i]]++;
		for(int i=1;i<=n+1;i++)
		{
			if(b[i]==1)
			{
				cout<<"No\n";
				flag=1;
				break;
			}
			if(b[i]>=2) b[i+1]=b[i+1]+b[i]-2;
		}
		if(!flag) cout<<"Yes\n";
	}
    return 0;
}
```

---

## 作者：ZMQ_Ink6556 (赞：1)

## 题解：CF2067B Two Large Bags

### 题意翻译

您有两大袋号码。

最初，第一个袋子包含 $n$ 个数字：$a_1 , a_2 , \dots a_n$，而第二个袋子是空的。

您可以执行以下操作：

- 从第一个袋子中选择任意数字，然后将其移动到第二个袋子。
- 从第一个袋子中选择一个数字，若该数字也存在于第二个袋子中，则将其增加 $1$。

您可以按任意顺序执行不限数量的这两种类型的操作。

是否可以使第一个和第二个袋子的内容相同？

### 解题思路

**低等能变高等，高等不能变低等。**

所以我们从最低等开始考虑。

首先，若最低等个数是 $1$，那么无论如何也不可能，输出 `No`。

若最低等个数是 $2$，那么左边一个右边一个，很好解决。

若最低等个数是 $3$，不如试试把多余的那个升级，然后效仿最低等个数 $2$ 的情况操作。

若最低等个数是 $4$ 级以上，那么一定能够每轮升级 $2$ 个（因为升级 $2$ 个无论如何也不影响答案），直到剩下 $2$ 个或 $3$ 个，再仿照前面的办法操作。

此时我们发现最低等的处理方法可以向高等级沿用。

于是从低到高更新即可。

如果最高等级剩余 $1$ 个，输出 `NO`，如果剩余 $2$ 个，输出 `YES`。

**别忘了开双倍空间！**

### 参考代码

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int t , n , a[1005] , tong[2005];
bool flag;
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1 ; i <= 2 * n ; i++)
		{
			tong[i] = 0;
		}
		for(int i = 1 ; i <= n ; i++)
		{
			cin >> a[i];
			tong[a[i]]++;
		}
		flag = 0;
		for(int i = 1 ; i <= 2 * n ; i++)
		{
			if(tong[i] == 1)
			{
				flag = 1;
				break;
			}
			if(tong[i])
			{
				tong[i + 1] += tong[i] - 2;
			}
		}
		if(flag)
		{
			cout << "NO\n";
		}
		else
		{
			cout << "YES\n";
		}
	}
	return 0;
}
```

内容来源：[赛时提交](https://mirror.codeforces.com/contest/2067/submission/305628628)。

---

## 作者：thedyingkai (赞：1)

### 思路
题目中每个球的处理只有三种操作：放在第一个袋子不动；把第一个袋子里的球移进第二个袋子；在第二个袋子已经有某号球时，把第一个袋子里的同号球球号数加一。

为了两个袋子中的球完全相同，有一半的球不动，剩下一半只能做后两种操作，球是一定会被拿到二号袋的，区别是在可以做第三种操作时要不要做。

对于操作三的条件，如果有 $1$ 或 $2$ 个 $x$ 号球，明显不可以；如果有 $n≥3$ 个 $x$ 号球，前两个球两个袋子各一个，其余 $n-2$ 个球全部可以进行操作三。

拿数据 $a_{n_1}=\{1,1,1,1\}$ 模拟，如果全不进行操作三，则一、二号袋都装着 $\{1,1\}$，如果能进行操作三的全进行操作三，则一、二号袋都装着 $\{1,2\}$，而对于 $a_{n_2}=\{1,1,1,2\}$，如果全不进行操作三，得不出正确结论，如果能进行操作三的全进行操作三，则一、二号袋都装着 $\{1,2\}$。

可以看出我们只需要尽可能多的执行操作三即可，只要有 $n≥3$ 个 $x$ 号球，就把其中 $n-2$ 个球变成 $x+1$ 号球，如果只有 $1$ 个 $x$ 号球，这个球无法平均分配，标记一下该方案不可能即可。
### AC code
```cpp
#include "iostream"
#include "cstring"
using namespace std;
int t,n,a,x[1001];
int main(){
    cin>>t;
    while(t--){
        cin>>n;
        memset(x,0,sizeof(x));
        for(int i=1;i<=n;i++){
            cin>>a;
            x[a]++;
        }
        int s=0;
        for(int i=1;i<=n;i++){
            if(x[i]>2) x[i+1]+=x[i]-2;
            if(x[i]==1) s=1;
        }
        if(s) cout<<"NO"<<endl;
        else cout<<"YES"<<endl;
    }
}
```

---

## 作者：what_can_I_do (赞：1)

[传送门](https://www.luogu.com.cn/problem/CF2067B)

先开一个桶记录每个数字出现的次数，然后从小到大对于一个数字在两个袋子中各留下一个，剩下的统一加一往后推。如果这个数字目前只出现了一次，那么就无法分配，答案就是 `No`。如果推到最后 $n+1$ 这个数有奇数个就不可行，否则就可行。

# CODE：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int t;
int n;
int v[1010];
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		int ans=1;
		scanf("%d",&n);
		for(register int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			v[x]++;
		}
		for(register int i=1;i<=n;i++)
		{
			if(!v[i]) continue;
			if(v[i]==1)
			{
				ans=0;
				break;
			}
			v[i+1]+=v[i]-2,v[i]=2;
		}
		if(v[n+1]&1) ans=0;
		if(ans) puts("Yes");
		else puts("No");
		for(register int i=1;i<=n+1;i++) v[i]=0;
	}
	return 0;
}
```

---

## 作者：Minecraft_BE (赞：0)

## 题解：CF2067B Two Large Bags

### 题面翻译以及概括

给定一个包含 $n$ 个数字的数组，通过以下两种操作，判断是否能使得两个袋子的内容相同：
1. 从第一个袋子中选择任意数字，然后将其移动到第二个袋子。
2. 从第一个袋子中选择一个数字，若该数字也存在于第二个袋子中，则将其增加 1。


### 思路


为了将手上的数字 $x$ 增加到 $y$，必须保证对面存在数字 $x$ 和 $y-1$。在处理时，可以按照从大到小的顺序枚举手上的数字。如果发现无法找到与当前数字匹配的数字，则需要将小于当前数字的数字增加到手上来进行匹配。之后，通过推导较小的数字来完成整个过程。可以通过使用一个桶来统计和处理这些数字，就可以做出这题了！

### code

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long;

ll t, n, f = 1;
ll a[1003];
string res[2] = {"No\n", "Yes\n"};

int main() {
    cin >> t;
    while (t--) {
        memset(a, 0, sizeof(a));
        cin >> n;
        for (ll i = 1, x; i <= n; ++i) {
            cin >> x;
            a[x]++;
        }
        for (ll i = 1; i <= n; ++i) {
            if (a[i] == 1) f = 0;
            else if (a[i] > 2) a[i + 1] += a[i] - 2;
        }
        cout << res[f];
        f = 1;
    }
    return 0;
}
```

---

## 作者：Tsz1024_AK (赞：0)

### 题目翻译
你有两个袋子，第一个袋子里包含了 $a_1,a_2,...,a_n$，第二个袋子是空的，你可以进行以下操作：

- 从第一个袋子中选择任意数字，然后将其移动到第二个袋子。
- 从第一个袋子中选择一个数字，该数字也存在于第二个袋子中，然后将其增加 $1$。

您可以按照任何顺序执行若干次这两种类型的操作。问是否可以使两个袋子的数据相同？

### 题目思路
首先，我们知道主要的操作是操作二。而要满足操作二的条件，就要有 $3 \le n$ 个 $i$ 号球，而且前两个球两个袋子各一个，其余 $n−2$ 个球全部可以进行操作二。

### 片段代码
```cpp
//清空数组
for(int i=1;i<=n;i++){
    cin>>x;
    arr[x]++;
}
int cnt=0;
for(int i=1;i<=n;i++){
    if(arr[i]>2) arr[i+1]+=arr[i]-2;
    if(arr[i]==1) cnt=1;
}
//判断结果
```

---

## 作者：yhl110804 (赞：0)

可以贪心。

首先，由于要使两个袋子中的数相同，所以最后每一个数的个数都应是偶数。统计每一种数的个数，记录一个变量 ```sum``` 表示有多少数可以用，从小往大扫一遍，对于个数大于一的数，贪心地只留下两个数，剩余的数加入 ```sum``` 中，对于仅有一个的数，从 ```sum``` 中留下一个与其配对，对于没有的数，从 ```sum``` 中取出两个数留下，若此时 ```sum``` 为零则跳过，为一则输出 ```No```。最后统计 ```sum``` 奇偶性，是奇数输出 ```No``` 否则输出 ```Yes```。
## Code:
```cpp
#include<bits/stdc++.h>
//#define int long long
using namespace std;
inline int read()
{
   int x=0,f=1;char ch=getchar();
   while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
   while (ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-48;ch=getchar();}
   return x*f;
}
void write(int x)
{
   if(x<0)putchar('-'),x=-x;
   if(x<10)putchar(x+'0');
   else write(x/10),putchar(x%10+'0');
}
const int N=2e5;
const int mod=1e9+7;
int n;
int a[N];
int sum[N];
int ans;
int T;
signed main(){
	T=read();
	while(T--){
		int maxn=0,minn=INT_MAX;
		n=read();
		for(int i=1;i<=n;i++)a[i]=read(),sum[a[i]]++,maxn=max(maxn,a[i]),minn=min(minn,a[i]);
		for(int i=minn;i<=maxn;i++){
			if(sum[i]==0&&ans==0)continue;
			ans+=sum[i]-2;
			if(ans<0){
				ans=1;
				break;
			}
    	}
    	if(ans%2)cout<<"No\n";
    	else cout<<"Yes\n";
		memset(sum,0,sizeof sum);
		ans=0;
	}
	return 0;
}

```

---

## 作者：huanglihuan (赞：0)

### Solution
建一个桶 $b$，储存数组 $a$，考虑对于 $i\in[1,n)$，考虑分讨 $b_i$：
- 对于 $b_i=1$，显然无解。
- 对于 $b_i=2$，显然有解（即两袋各一个）。
- 对于 $b_i>2$，可以通过 $b_i-2$ 次操作二使得 $b_i=2,b_{i+1}=b_{i+1}+b_i-2$。
### Code
```cpp
#include <bits/stdc++.h>
#include <cstdio>
#define int long long
#define ull unsigned long long
#define mod 988444333
#define MOD 1000000007
#define in(x,y,z) x>=y&&x<=z
using namespace std;
const int N = 2e6 + 5;
inline int read ()
{
	int x = 0;
	char c = getchar ();
	while (c < '0' || c > '9') c = getchar ();
	while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48),c = getchar ();
	return x;
}
inline void write (int x)
{
	if (x > 9) write (x / 10);
	putchar (x % 10 + '0');
	return ;
}
void solve ()
{
	int n;
	cin >> n;
	map <int,int> bucket;
	for (int i = 1;i <= n;i ++)
	{
		int x;
		cin >> x;
		bucket [x] ++;
	}
	for (int i = 1;i <= n;i ++)
	{
		if (bucket [i] == 1)
		{
			cout << "NO\n";
			return ;
		}
		else if (bucket [i] > 2) bucket [i + 1] += bucket [i] - 2;
	}
	cout << "YES\n";
}
signed main ()
{
	int T;
	cin >> T;
	while (T --) solve ();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 闲话
本文同步发布在 [cnblogs](https://www.cnblogs.com/zhangzirui66)。

---

容易发现，若想要让两个袋子物品相同，每种数字都应有偶数个。

这只是根据操作一得出的结论，我们还有操作二。

对于一个数字，我们有以下的贪心策略，其中 $b_i$ 表示 $i$ 在数组 $a$ 中出现的次数，即一个桶：

- 若 $b_i \ge 2$，可以转移 $b_i - 2$ 个数字给 $b_{i + 1}$，即 $b_{i + 1} \gets b_{i + 1} + (b_i - 2)$，$b_i \gets 2$。

- **接下来**，若 $b_i$ 仍为奇数，即无解。

这个贪心需要证明，第二项显然，第一项证明如下：

首先，一个数只能留下偶数个数，这里我们留下了 $2$ 个，符合性质。

其次，由于剩下的是偶数，转移的奇偶性是已经确定了的，在这种情况下，多继承一部分，可以更好地填上后面的空缺，不比原转移更少劣。

得到证明，实现代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n, a[1005], b[1005];
int main(){
    cin >> t;
    while(t --){
        int flag = 0;
        cin >> n;
        for(int i = 1; i <= n; i ++){
            b[i] = 0;
        }
        for(int i = 1; i <= n; i ++) cin >> a[i], b[a[i]] ++;
        for(int i = 1; i <= n; i ++){
            if(b[i] >= 2){
                b[i + 1] += (b[i] - 2);
                b[i] = 0;// 这里主要是为了应付下面两句不被判到，改成任意偶数均可
            }
            if(b[i] & 1){
                cout << "NO\n";
                flag = 1; break;
            }
        }
        if(!flag){
            cout << "YES\n";
        }
    }
    return 0;
}
```

---

## 作者：AstaVenti_ (赞：0)

# $\mathbf{0x00}$ 启

蒟蒻的第 $\color{red}\mathbf{44}$ 篇题解。

# $\mathbf{0x01}$ 承

两个可重集 $A,B$，初始时 $A$ 里有 $n$ 个数，进行以下两种操作任意多次：

- 把一个数从 $A$ 放到 $B$；
- 在 $A$ 中选取一个 $A$ 和 $B$ 中都有的数并将其 $+1$。

问你在若干次操作之后能否使两个可重集相同。

# $\mathbf{0x02}$ 转

我们显然可以知道，如果一个数 $x$ 在 $A$ 中重复出现了 $2k(k\in\mathbb N)$ 次，则可以把其中的 $k$ 个放到 $B$ 里面；如果 $x$ 出现了 $2k+1(k\in\mathbb N)$ 次，且 $x-1$ 出现的次数大于 $2$（也就是 $x-1$ 可以平均分到两个可重集中还能在 $A$ 中加成 $x$），就把大于 $2$ 的部分全部 $+1$。

最后判断数组里是否有某个数只出现过一次即可。

# $\mathbf{0x03}$ 合


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,c[1003],flg=1;
string ans[]={"No\n","Yes\n"};
int main(){
	cin>>T;
	while(T--){
		memset(c,0,sizeof(c));
		cin>>n;
		for(int i=1,a;i<=n;i++){
			cin>>a;
			c[a]++;
		}
		for(int i=1;i<=n;i++){
			if(c[i]==1)flg=0;
			else if(c[i]>2)c[i+1]+=c[i]-2;
		}
		cout<<ans[flg];
		flg=1;
	}
	
}

```

---

