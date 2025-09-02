# 「GMOI R2-T2」猫耳小（加强版）

## 题目背景

**本题与 [原题](https://www.luogu.com.cn/problem/P9199) 的区别在于数据范围和输出格式。在这一版本中，$n\le 10^6$，值域为 $10^9$，你需要给出构造。**

![](https://cdn.luogu.com.cn/upload/image_hosting/r8a6ylx3.png)

## 题目描述

小 R 是一个可爱的猫耳女孩子，她喜欢研究数列的 $\operatorname{mex}\text{*}$。

现在她有一个长度为 $n$ 的数列 $a$。她讨厌整数 $k$，因此她希望修改数列 $a$ 的若干个元素为任意**自然数**，使得 $a$ 的任意**连续非空子串**的 $\operatorname{mex}$ 都不等于 $k$。

请你求出最少需要修改多少个元素，并给出方案。

$\text{*}$ 本题中，数列的 $\operatorname{mex}$ 被定义为数列中最小未出现的**自然数**，例如：

- $\operatorname{mex}\{1,2,3\}=0$，因为 $0$ 是自然数。
- $\operatorname{mex}\{0,1,3\}=2$。
- $\operatorname{mex}\{0,1,2\}=3$。

## 说明/提示

**样例解释**

一种方案是将 $\{1,0,1,3,0\}$ 改为 $\{1,1,1,3,2\}$，共改动两个元素。

可以证明不存在更优的方案。

---

**评分方式**

本题采用自定义校验器（Special Judge）进行评测。

对于每个测试点，如果你的最小步数正确，可以得到 $30\%$ 的分数。在此基础上，如果方案也正确，可以得到满分。

请注意：即使你不会给出方案，也请按照输出格式在第二行输出 $n$ 个整数。

---

**本题采用捆绑测试，数据无梯度。**

对于 $100\%$ 的数据，$1\le n\le 10^6$，$0\le k,a_i\le 10^9$。

本题读写量较大，建议使用效率较高的读写方式。

## 样例 #1

### 输入

```
5 2
1 0 1 3 0```

### 输出

```
2
1 1 1 3 2```

# 题解

## 作者：sto_5k_orz (赞：6)

部分说明转载自 [P9199 题解](https://www.luogu.com.cn/blog/Stitch0711/p9199-ti-xie)。

考虑贪心求解。

显然，假如一段中缺少了任何一个 $<k$ 的数，则不成立。

或者 $k$ 在集合中，依旧不成立。

判断成不成立可以考虑用 set。

上一篇题解是先推满然后删除的，空了说明需要修改。

可是这题 $k\leq 10^9$。

所以我们应该先清空，再推进去，凑够 $k$ 个数再修改。

每次修改改成 $k$ 就可以了，因为只要让 $k$ 在集合中就肯定不成立。

还有就是不要把 $>k$ 的数推进 set。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc putchar
#define W while
#define I inline
#define int long long
namespace SlowIO{
    I int read() {
        int x = 0, f = 1; char ch = gc();
        W(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
        W(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
        return x * f;
    }
    I void Read(int &x) {x = read();}
    I void write(int x) {
        if(x < 0) pc('-'), x = -x;
        if(x > 9) write(x / 10);
        pc(x % 10 + '0');
    }
    I void Write(int x) {write(x); pc(' ');}
} using namespace SlowIO;
const int N = 1000010;
int n, k; int a[N], cnt[N]; set<int> st;
signed main() {
	cin >> n >> k; int ans = 0;
	for(int i = 1; i <= n; i++) Read(a[i]);
	for(int i = 1; i <= n; i++) {
		if(a[i] == k) {
			st.clear();
			continue;
		}
		if(a[i] < k) st.insert(a[i]);
		if(st.size() == k) {
			ans++; a[i] = k;
			st.clear();
		}
	}
	cout << ans << endl;
	for(int i = 1; i <= n; i++) Write(a[i]);
	return 0;
}
```

---

## 作者：QianRan_GG (赞：4)

## 题目大意

给定一个长为 $n$ 的数列 $a$ 和一个数 $k$，修改最少的数使其任意一个**连续非空子串**中第一个没出现的自然数（$\operatorname{mex}$）不为 $k$。

### 样例解释：  

数列 $a$ 为 $1\ 0\ 1\ 3\ 0$（下标设为 $1$ 到 $5$），$k=2$。  
其中子串 $1\ 0$ 和 $1\ 3\ 0$ 中第一个没出现的自然数都是 $2$，所以将 $a_2$ 修改为 $1$，$a_5$ 修改为 $2$，使修改后的子串为 $1\ 1$（$\operatorname{mex}$ 为 $0$）和 $1\ 3\ 2$（$\operatorname{mex}$ 为 $0$）。  
最少修改次数为 $2$，修改后子串为 $1\ 1\ 1\ 3\ 2$。

## 解题思路

首先我们需要知道若要修改 $a_i$ 时，修改为 $k$ 最优，因为含 $k$ 的子串的 $\operatorname{mex}$ 一定不为 $k$，而修改成其他值不一定能保证含 $a_i$ 的子串的 $\operatorname{mex}$ 一定不为 $k$。  
且因为子串要连续，所以 $a_i=k$ 时，判断 $a_i$ 之后的数要不要修改与 $a_i$ 之前的数无关，因为一个子串若首在 $a_i$ 前，尾在 $a_i$ 后，则必经过 $a_i$，因为 $a_i$ 被我们修改为 $k$，所以此子串的 $\operatorname{mex}$ 必不为 $k$。

然后我们考虑三种情况：$k=0$，$k>n$ 和 $1\le k\le n$。

### 第一类

$k=0$ 时，若 $a_i>0$，则**只**由 $a_i$ 构成的子串的 $\operatorname{mex}$ 必定为 $0$，所以要把所有此类 $a_i$ 修改为 $0$。

### 第二类

$k>n$ 时，因为只有 $n$ 个数，所以在 $0$ 到 $n$ 中（有 $n+1$ 个数）必有至少一个数没出现，所以不需要修改。

### 第三类

$1\le k\le n$ 时。  
$a_i>k$ 时，因为我们只要考虑 $0$ 到 $k-1$ 这几个数，所以直接跳过。

然后我们用一个 $cnt$ 数组记录在 $a_l$（$l$ 为 $a_i$ 之前最后一个 $=k$ 的数的下标)到 $a_{i-1}$ 中 $0$ 到 $k-1$ 出现的个数，$ans$ 记录修改次数。

$a_i<k$ 时，让 $cnt_{a_i}+1$，再进行判断：若对于每一个在 $0$ 到 $k-1$ 中的 $i$，$a_i$ 均不为 $0$，则清空 $cnt$ 数组，使 $l=i$，$ans+1$，将 $a_i$ 修改为 $k$。

$a_i=k$ 时，因为在 $a_l$ 到 $a_{i-1}$ 中，我们已经使其所有子串的 $\operatorname{mex}$ 不为 $k$，加上 $a_i$ 也必不为 $k$，所以直接清空 $cnt$，使 $l=i$。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;

int n, k, ans = 0, mex, a[N], b[N], cnt[N]; // a为原数组， b为修改后数组，mex 记录 0 ~ k - 1 最少没出现的数。 

signed main()
{
	//输入。 
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; ++ i) cin >> a[i];
	
	//三种情况分类。 
	if(!k)
	{
		for(int i = 1; i <= n; ++ i)
		{
			if(a[i]) ans ++;
			b[i] = 0;
		}
	}
	
	else if(k > n) 
	{
		for(int i = 1; i <= n; ++ i) b[i] = a[i];
		ans = 0;
	}
	
	else
	{
		for(int l = 0, i = 1; i <= n; ++ i)
		{
			b[i] = a[i];
			if(a[i] > k) continue;
			else if(a[i] == k)
			{
				while( ++ l < i) if(a[l] < k) cnt[a[l]] --; //既清空cnt数组， 又修改了l。 
				mex = 0;
			}
			else
			{
				cnt[a[i]] ++;
				while(cnt[mex]) mex ++;
				if(mex == k)
				{
					ans ++;
					while( ++ l < i) if(a[l] < k) cnt[a[l]] --;
					cnt[a[i]] --; //因为没修改a[i]， 所以还要再改一次。 
					b[i] = k;
					mex = 0;
				}
			}
		}
	}
	
	//输出。 
	cout << ans << '\n';
	for(int i = 1; i <= n; ++ i) cout << b[i] << ' ';
	return 0;
}
```


---

## 作者：GeorgeAAAADHD (赞：2)

题目大意：给定 $n,k$ 以及长度为 $n$ 的序列 $a$。求至少改变 $a$ 中的多少个数字，才能使 $a$ 中的**任意**一个**连续非空子串**中**最小未出现的自然数**都不等于 $k$。

那么我们秉持着骗分导论的原则，先做简单的部分：

------------
### 1. 当 $k=0$ 时，

很明显此时 $a$ 中的所有数字都要为 $0$，答案为 $a$ 中不为 $0$ 的数的个数。

------------
### 2. 当 $n < k$ 时，

很明显，就算 $a$ 中的所有数字都从 $0$ 开始升序排列，最终的数字还是小于 $k-1$ 的，因此答案为 $0$，直接输出原序列即可。

------------
### 3. 其他情况，

切入正题。

首先。我们发现，$a$ 中大于 $k$ 的数是无意义的，这是显而易见的。

其次，我们考虑几个贪心算法：

- 将要改的值都改为 $k$，因为这样，选择包含这个数的所有子串的 $\operatorname{mex}$ 都不会等于 $k$，因为这些子串中均包含 $k$，因此将要改的值改为 $k$ 一定不劣。

- 如果输入了 $k$，则 $k$ 左边的部分可分为一段，$k$ 右边的部分为一段。原理同上。

- 如果在第二个条件下，分成的每个段落中包含了 $0$ ~ $k-1$ 中的每一个数字，则该区间至少要修改一个数字。因为这个段落已不存在 $k$，它的 $\operatorname{mex}$ 必定为 $k$。

- 在第三个条件下，我们可以边读入边进行计数，如果在计数过程中出现了 $0$ ~ $k-1$ 均出现过大于一次的情况，则将该区间的右端点改为 $k$，因为这样可以最大程度地缩小剩下的区间的规模。特别地，如果中途输入 $k$，则要将计数数组全部重置为 $0$。

根据以上的贪心算法，可得到以下做法：

1. 每输入一个数判断一次，如果这个数大于 $k$，则这轮循环什么都不用做。

2. 如果这个数等于 $k$，将计数数组重置为 $0$。注意每一次用 `fill` 重置的时间复杂度是 $O(k)$，在此情况下，最坏的时间复杂度会达到 $O(nk)$，可能会超时，因此需要遍历区间，对当前区间的每一个数的计数减一，这样就不会超时了。

3. 否则，将该数的计数加上一。由于一个区间内的 $\operatorname{mex}$ 具有单调性，因此只需要从计数数组为 $\operatorname{mex}$ 的位置向后枚举，直到计 $\operatorname{mex}$ 的数为 $0$ 时停止。

4. 在 3 操作后，如果 $\operatorname{mex} = k$，则答案加上一，并将答案数组下标为右端点的值改为 $k$。此时用 `fill` 重置计数数组不会超时，时间复杂度最坏为  $O(n \div k \times k)$，即 $O(n)$。同时将左端点右移，最后重置 $\operatorname{mex}$ 即可。

于是根据这个思路，我们便可以愉快地 AC 本题啦！

Code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define f(i,j,k) for(int i=(j);i<=(k);i++)
using namespace std;
const int maxn = 1000010;
int n,k,a[maxn],b[maxn],tp[maxn]={0},ans=0,mex=0;
signed main(){
	ios::sync_with_stdio(false);//关闭与 stdio 的同步
	cin.tie(0);//输入优化
	cout.tie(0);//输出优化
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cin>>n>>k;
	if(k==0){//特判1
		f(i,1,n){
			cin>>a[i];
			if(a[i])ans++;
			b[i]=0;
		}
	}
	else if(n<k){//特判2
		f(i,1,n){
			cin>>a[i];
			b[i]=a[i];
		}
	}
	else{//正题
		int l=0;
		f(r,1,n){
			cin>>a[r];
			b[r]=a[r];
			if(a[r]>k)continue;//大于k的数无意义
			if(a[r]==k){
				while(++l<r)if(a[l]<k)tp[a[l]]--;//等于k时重置计数数组
				mex=0;//重置 mex
				continue;
			}
			else{
				tp[a[r]]++;//计数
				while(tp[mex])mex++;//由于 mex 具有单调性，因此可以从上一次的计数数组下标为 mex 的值进行查找
				if(mex==k){//mex 等于 k
					ans++;//答案加上1
					fill(tp,tp+k,0);//重置计数数组
					l=r;//修改左区间
					b[l]=k;//修改输出数组
					mex=0;//重置mex
				}
			}
		}
	}
	cout<<ans<<'\n';
	f(i,1,n)cout<<b[i]<<' ';
	return 0;
}
```

最后祝大家 AC 愉快！

---

## 作者：Iamzzr (赞：2)

首先发现一个显然的性质，如果一个区间内含有 $k$，那么这个区间的 $\operatorname{mex}$ 值一定不是 $k$。

同样，根据定义，如果一个区间内含有 $0\sim k - 1$ 的每个数，那么这个区间的 $\operatorname{mex}$ 为 $k$。

那么从头遍历数组，记录每个数的访问次数，如果一个数是第一次访问并且该数小于 $k$，那么计数器加一。如果在扫描某个数 $a_i$ 之后，计数器的值等于 $k$，说明该区间 $0\sim k-1$ 都存在过，根据开头的性质，可以将该数改为 $k$，这样，$a_{1\sim i}$ 中就不存在任意一个子区间使得 $\operatorname{mex}$ 为 $k$。同时，清空每个数的访问次数，将计数器归零，因为前面的已经通过 $a_i$ 的调整，与后面彻底断开了关系，不再考虑。

特殊地，如果扫描到 $a_i$ 的值是 $k$，则清空每个数的访问次数，将计数器归零，原因同上。

代码：

```cpp
namespace mex {
    int n, k; 
    int a[N], Ans[N];
    std::map<int, int> vis;
    int ans, num;

    void solve() {
        std::cin >> n >> k;
        for (int i = 1; i <= n; i++) std::cin >> a[i], Ans[i] = a[i];
        for (int i = 1; i <= n; i++) {
            if (a[i] == k) {
                vis.clear();
                num = 0;
                continue;
            }
            if (vis[a[i]] == 0 && a[i] < k) num++;
            vis[a[i]]++;
            if (num == k) {
                ans++, num = 0;
                vis.clear();
                Ans[i] = k;
            }
        }
        std::cout << ans << "\n";
        for (int i = 1; i <= n; i++) std::cout << Ans[i] << " ";
        puts("");
    }
}
```

---

## 作者：zjc5 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P9202)

**思路：**

介绍一种很神奇的做法。

如果一段区间里包含了 $k$，那么这段区间的 $mex$ 一定不是 $k$。大于 $k$ 的数对于 $mex$ 的结果是否等于 $k$ 无关。

所以，只需顺序加入每一个小于 $k$ 的数，并标为已出现。若等于 $k$，直接清空数组。

当 $0$ 到 $k-1$ 间的每一个数都已出现，则将最后加入的数改成 $k$，并清空数组。

用这个思路就可以把 [**原题**](https://www.luogu.com.cn/problem/P9199) $AC$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a;
bool c[5010];
int mx,cnt;
int main() {
	cin>>n>>k;
	for(int i=1; i<=n; i++) {
		cin>>a;
		if(a<k&&!c[a]) {
			cnt++;
			c[a]=true;
		}
		if(a==k) {
			memset(c,false,sizeof(c));
			cnt=0;
			continue;
		}
		if(cnt==k){
			mx++;
			cnt=0;
			memset(c,false,sizeof(c));
		}
	}
	printf("%d",mx);
	return 0;
}
```

但是，把 $c$ 数组清空太费时间了，可以用一种方法优化这一步。

定义一个数组 $cg$，用来保存每一个数被清零几次。再定义一个变量 $g$，用来存一共清零几次。

若 $cg_i<g$（未达到应有的清零次数），就让 $c_i=0$（清零），$cg_i=g$（达到应有的清零次数）。

最终代码时间复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a,g;
unordered_map<int,bool>c;
unordered_map<int,int>cg;//开map会TLE
int mx,cnt,ans[1000010];
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1; i<=n; i++) {
	    scanf("%d",&a);
	    ans[i]=a;
		if(a<k) {
			if(cg[a]<g) {
				cg[a]=g;
				c[a]=false;
			}
			if(!c[a]) {
				cnt++;
				c[a]=true;
			}
		}
		if(a==k) {
			g++;
			cnt=0;
			continue;
		}
		if(cnt==k) {
			g++;
			mx++;
			cnt=0;
			ans[i]=k;
		}
	}
	printf("%d\n",mx);
	for(int i=1; i<=n; i++)
		printf("%d ",ans[i]);
	return 0;
}
```

---

## 作者：许多 (赞：0)

分段考虑，如果一个子串中包含了 $k$，那他的 $mex$ 就不可能等于 $k$。而一个子串中包含大于 $k$ 的数对结果是否为 $k$ 没有影响。

我们维护一个范围是 $0$ 到 $k$ 的桶，如果 $a[i]=k$，则将桶清空，如果 $0$ 到 $k-1$ 中都有数字，则将当前数字改为 $k$，并清空桶。

但注意到，$k\leq10^9$，明显用数组存不下了，但我们仔细观看 $mex$ 定义，发现当 $k>n$ 时结果为 $0$，而 $n\geq10^6$，那就很好维护了。

# 代码

```cpp
#include<bits/stdc++.h>
#include<cstdio>
#define N 2000000
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
using namespace std;
int n,k;
int a[N],ans=0,p[N],cnt=0;
//ans为当前桶中有几种数字，cut为操作个数
int main(){
    n=read();k=read();k=min(k,n+1);
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(a[i]==k){
            for(int j=0;j<k;j++)p[j]=0;
            ans=0;
        }
        else {
            if(a[i]<k&&p[a[i]]==0){
               //cout<<i<<" ";
                p[a[i]]++;
                ans++;
            }
            if(ans==k){
                cnt++;
                a[i]=k;
                for(int j=0;j<k;j++)p[j]=0;
                ans=0;
            }
        }
        
    }
    cout<<cnt<<endl;
    for(int i=1;i<=n;i++)
        printf("%d ",a[i]);
    return 0;
}
```


---

## 作者：Nine_Suns (赞：0)

好玩的一道题。
## 

当 $k$ 为数列的 $\operatorname{mex}$ 时**当且仅当**数列中出现了 $0$ 到 $k-1$ 的所有数且数列中不存在 $k$。 

对于一个 $\operatorname{mex}$ 为 $k$ 的数列，只需将数列中的任意一项修改为 $k$ 即可令 $\operatorname{mex}$ 改变。

当 $a_1,a_2,...,a_{l-1},a_l$ **都不为 $k$** 时，若 $\{a_1,a_2,...,a_{l-1},a_l\}$ 的 $\operatorname{mex}$ 为 $k$ 且 $\{a_1,a_2,...,a_{l-2},a_{l-1}\}$ 的 $\operatorname{mex}$ 不为 $k$，则将 $a_l$ 修改为 $k$ 后，$\{a_1,a_2,...,a_{l-1},a_l\}$ **及它所有子串**的 $\operatorname{mex}$ **均不为** $k$。
##

显然，当 $k>n$ 时一定不存在 $k$ 为 $\operatorname{mex}$ 的情况，因为一共只有 $n$ 个数，不可能构成 $0$ 到 $k-1$ 的所有数，输出 $0$ 和原序列即可。
（实际上 $k=n$ 的时候也一定不存在）

当 $k<n$ 时，不考虑数据范围，可以将所有 $\operatorname{mex}$ 为 $k$ 的区间处理出来。对于每一个区间，都需要将这个区间内的一个数变为 $k$，问题转化为求最小点数，使每个区间都至少包含一个点，复杂度 $O(n^2)$，贪心求解即可。

但 $n\le10^6$，直接 T 飞。若数列中有一个数为 $k$，则可以将这个数列从这个位置分为左右两部分，不存在任何子串横跨左右且满足 $\operatorname{mex}$ 为 $k$，只需左右分开求解即可。依照这个思路，可以将整个数列分成若干部分，接下来对于每一个部分分别求解。

设立 $l,r$，一开始指向区间起始位置，$r$ 向右移动，移动过程中将经过的数添加到区间中，直到 $\{a_l,a_{l+1},...,a_{r-1},a_r\}$ 的 $\operatorname{mex}$ 为 $k$， 然后，将 $a_r$ 改为 $k$，答案加 $1$，令 $l$ 向左移动直到 $l>r$，移动过程中将经过的数从区间里删去。此时以 $a_r$ 为分界又将这个区间分为了两部分，左边部分及它所有子串的 $\operatorname{mex}$ 都不会为 $k$，在右边部分继续重复以上过程即可。

对于加数删数维护 $\operatorname{mex}$ 的操作，可以开桶记录每个小于 $k$ 的数的数量以及这些数的**数值数量**。具体地，当加入 $x$ 时，若 $x\ge k$，不执行任何操作，否则 $c_x\gets c_x+1$，若 $c_x=1$，则数值数量 $s\gets s+1$，当 $s=k$ 时，$\operatorname{mex}$ 为 $k$。删数与加数类似。

代码实现与题解略有出入。
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 1e6+5;
int n, a[N], c[N], k, s, b[N], ans;
inline int read () {
	int num = 0; char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9') num = (num<<1)+(num<<3)+(ch^48), ch = getchar();
	return num;
} 

inline void add (int idx) {
	if (a[idx] >= k) return;
	c[a[idx]]++; 
	if (c[a[idx]] == 1) s++; 
}

inline void del (int idx) {
	if (a[idx] >= k) return;
	c[a[idx]]--;
	if (!c[a[idx]]) s--;
}

int main () {
	n = read(); k = read();
	for (int i = 1;i <= n;i++) a[i] = read();
	if (k > n) {
		putchar('0'); putchar('\n');
		for (int i = 1;i <= n;i++) printf("%d ", a[i]);
		putchar('\n');
		return 0;
	}
	for (int i = 1, l = 1;i <= n;i++) {
		b[i] = a[i];
		add(i);
		if (s == k && b[i] != k) b[i] = k, ans++;
		if (b[i] == k) {
			while (l <= i) del(l++);
		}
	}
	printf("%d\n", ans);
	for (int i = 1;i <= n;i++) printf("%d ", b[i]);
	putchar('\n');
	return 0;
} 
```


---

