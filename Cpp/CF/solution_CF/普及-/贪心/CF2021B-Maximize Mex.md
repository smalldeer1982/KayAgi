# Maximize Mex

## 题目描述

You are given an array $ a $ of $ n $ positive integers and an integer $ x $ . You can do the following two-step operation any (possibly zero) number of times:

1. Choose an index $ i $ ( $ 1 \leq i \leq n $ ).
2. Increase $ a_i $ by $ x $ , in other words $ a_i := a_i + x $ .

Find the maximum value of the $ \operatorname{MEX} $ of $ a $ if you perform the operations optimally.

The $ \operatorname{MEX} $ (minimum excluded value) of an array is the smallest non-negative integer that is not in the array. For example:

- The $ \operatorname{MEX} $ of $ [2,2,1] $ is $ 0 $ because $ 0 $ is not in the array.
- The $ \operatorname{MEX} $ of $ [3,1,0,1] $ is $ 2 $ because $ 0 $ and $ 1 $ are in the array but $ 2 $ is not.
- The $ \operatorname{MEX} $ of $ [0,3,1,2] $ is $ 4 $ because $ 0 $ , $ 1 $ , $ 2 $ and $ 3 $ are in the array but $ 4 $ is not.

## 说明/提示

In the first test case, the $ \operatorname{MEX} $ of $ a $ is $ 4 $ without performing any operations, which is the maximum.

In the second test case, the $ \operatorname{MEX} $ of $ a $ is $ 5 $ without performing any operations. If we perform two operations both with $ i=1 $ , we will have the array $ a=[5,3,4,1,0,2] $ . Then, the $ \operatorname{MEX} $ of $ a $ will become $ 6 $ , which is the maximum.

In the third test case, the $ \operatorname{MEX} $ of $ a $ is $ 0 $ without performing any operations, which is the maximum.

## 样例 #1

### 输入

```
3
6 3
0 3 2 1 5 2
6 2
1 3 4 1 0 2
4 5
2 5 10 3```

### 输出

```
4
6
0```

# 题解

## 作者：chenxi2009 (赞：8)

# 形式化题意

可以给长度为 $n$ 的自然数列 $a$ 进行任意次操作，每次给选定的数加上 $x$，求最大的 $\text{mex}$。

- 一个数列的 $\text{mex}$ 为最小的未在这个数列中出现的自然数。

# 思路

若 $a$ 有 $\text{mex}$，$a$ 的元素集必然包含集合：$(0,1,2,\cdots,\text{mex}-1)$。让 $\text{mex}$ 最大，等价于让 $a$ 中存在最长的从 $0$ 开始的连续整数列长度最大。

略加研究发现：

- $a$ 中重复的元素肯定对增大 $\text{mex}$ 没有任何帮助，所以有重复的元素 $a_i$ 时一定执行操作 $a_i\leftarrow a_i+x$；
- $a$ 中只有一个的元素 $a_i$ 一定不执行操作，因为当它执行操作后，原先的 $a_i$ 在数列中不再出现，于是 $\text{mex}$ 将会不大于 $a_i$，对使其最大没有帮助。

所以贪心策略呼之欲出：从 $0$ 开始找一个数字是否出现，记 $i$ 的出现次数为 $apr_i$；

- 若 $apr_i=0$ 则该数字为 $\text{mex}$，结束；
- 若 $apr_i=1$ 则该数字出现一次，不进行操作；
- 若 $apr_i>1$ 则该数字出现多次，进行操作后有 $apr_{i+x}\leftarrow apr_{i+x}+apr_i-1,apr_i\leftarrow1$（即将 $apr_i-1$ 个 $i$ 进行一次操作，变为 $i+x$）。

显然 $\text{mex}\le n$，该算法复杂度为 $O(\sum n)$。

$apr$ 的实现可以忽略 $a_i\ge n$ 的数据，也可以离散化或用 map 实现。

# 注意事项

一种错误的做法是统计某个数字是否出现，加入数字时若该数字已出现就不断 $+x$ 直至该数字未出现。这样的做法复杂度得不到保证，可以构造如下 Hack 数据：

```
1
200000 1
1 1 1 1 1 1 1 1 1 1......1 1 1 1 1
```

直接卡飞成 $O(\sum n^2)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a[200001],x,ans;
map<int,int>m;//m 统计数字的出现次数 
int main(){
	scanf("%d",&T);
	while(T --){
		m.clear();
		scanf("%d%d",&n,&x);
		ans = n;
		for(int i = 1;i <= n;i ++){
			scanf("%d",&a[i]);
			m[a[i]] ++;
		}
		for(int i = 0;i < n;i ++){
			if(!m[i]){//未出现，找到 mex 终止循环 
				ans = i;
				break;
			}
			if(m[i] > 1){//出现超过一次，执行操作 
				m[i + x] += m[i] - 1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：_H17_ (赞：3)

## 题外话

由于洛谷开始全球化，我决定练习英语，我在题解中加入英文版本。

Because of [Luogu's International Station](https://www.luogu.com)'s creating, I decided to practise my English, I adds English Statement in this solution.

## 题目大意

题目给定我们一个序列 $a$，其中有 $n$ 个非负整数。

给定 $x$ 你可以执行以下操作（每次操作 $x$ 相同）：

- $a_i\gets a_i+x$，其中 $1\le i \le n$。

求最大化的 $\operatorname{MEX}(a)$。

其中 $\operatorname{MEX}(S)$ 表示在集合 $S$ 中没有出现过的最小非负整数。

## 题目分析

显然，对于最大化的 $\operatorname{MEX}$ 序列 $a$（假设操作无限制），显然是 $0\sim n-1$ 最优。

如果必须挑出其中一些数踢出，显然小的数更需要优先选中。

于是考虑贪心：对于 $k$，如果在 $a$ 中出现过，则跳过；否则找之前满足 $k\equiv a_t\pmod{x}$ 的最小 $a_t$，让 $a_t$ 加上若干个 $x$（注意：$a_t<k$）。

我们发现上述过程主要运用了权值，所以考虑使用 `map` 来维护每个值对 $x$ 取余出现的次数，同时注意按照大小顺序来（保证上文中 $a_t<k$）。

## English Statement

### The main meaning

You are given an array $a$ with $n$ non-negative elements.

You can do following operation (in every operations the $x$ are the same):

- $a_i \gets a_i+x$ for $1\le i \le n$.

We should output the maximum of $\operatorname{MEX}(a)$.

$\operatorname{MEX}(S)$ is the smallest non-negative integer that is not in $S$.

### The problem analysis

Obviously, to reach the maximum $\operatorname{MEX}(a)$ that $a$ should to be $0\sim n-1$.

And if we must kick some of them out, the smaller integers are the more important.

Try Greedy Algorithm: For $k$, if $k$ is in $a$, continue; if $k$ isn't, find $a_t \equiv k\pmod{x}$(Pay attention that $a_t<k$ is necessary).

We find that all the information in the Greedy Algorithm is values, but not ID, we can use STL `map` to count the number of the values modulo $x$.

## 代码实现

Here is my code.

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int T,n,x,a[200001];
map<int,int>mp1,mp2;
void Main(){
	mp1.clear(),mp2.clear();
    cin>>n>>x;
    int pos=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        mp1[a[i]]++;//记录数出现的次数 Count the number of the values
    }
    sort(a+1,a+n+1);
    for(int i=0;i<=n;i++){
        if(mp1[i]){
        	mp1[i]--;
			mp2[i%x]+=mp1[i];//记录模x的剩余值 Count the rest of the numbers modolo x
            continue;
		}
    	if(mp2[i%x]>=1){
    		mp2[i%x]--;
    		goto g;//使用剩余值 Use the rest numbers
		}
        cout<<i<<'\n';//无法让 i 进入 a Can't let i get into a (the MEX will be i)
        break;
        g:continue;
    }
    return;
}
signed main(){
    for(cin>>T;T;--T)
        Main();
    return 0;
}
```

如有程序方面的问题、语法问题，欢迎私信。

If there are any mistakes about my program or grammar mistakes, pls [chat to me](/chat?uid=743014).

Updated: Edited some grammar mistakes.

---

## 作者：Butterfly_qwq (赞：1)

赛时脑子宕机想了 40min。

发现序列中的一个数有相对应重复的另一个数时，把这个数加上 $x$ 肯定不劣。

于是考虑枚举值域，把所有值等于当前值的元素加上 $x$。$O(nV)$ 过不了。

发现我们可以先统计每个数出现的次数，用一个 map 存，然后枚举值域，如果当前数字出现次数为 $0$ 则输出这个答案并退出枚举，否则将其留下 $1$ 个，剩下所有数字加 $x$。即 $a_{i+x}\leftarrow a_{i_x}+a_i-1$ 并 $a_i\leftarrow 1$。

看似是 $O(V)$ 的，其实可以发现答案不超过 $n$，所以时间复杂度为 $O(n)$，可以通过。

忘了 hack 用 unordered_map 存次数的人导致掉分，悲了。

```
#include<bits/stdc++.h>
using namespace std;
int t,n,x,a[200005];
map<int,int>bul;
int main()
{
	cin>>t;
	while(t--)
	{
		bul.clear();
		cin>>n>>x;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			bul[a[i]]++;
		}
		for(int i=0;;i++)
		{
			if(bul[i]==0)
			{
				cout<<i<<'\n';
				break;
			}
			bul[i+x]+=bul[i]-1;
			bul[i]=1;
		}
	}
}
```

---

## 作者：banglee (赞：0)

## CF2021B Maximize Mex 题解
[题目传送门](https://www.luogu.com.cn/problem/CF2021B)

## 正文
为了使 $\operatorname{MEX}$ 至少为 $k$ ，则从 $0$ 到 $k-1$ 的每个非负整数必须在数组中至少出现一次。

首先，由于数组中只有 $n$ 个元素，因此最多有 $n$ 个不同的值，因此 $\operatorname{MEX}$ 最多只能为 $n$ 。并且由于我们只能增加元素的值，这意味着可以忽略每个值大于 $n$ 的元素。

我们构造一个频率数组 $\text{a}$ ，其中 $\text{a}[k]$ 是 $a$ 中值为 $k$ 的元素数。

这些值只需出现至少一次即可对 $\operatorname{MEX}$ 做出贡献，因此应将两个或多个具有相同值的元素拆分为不同的值，以便找到最优解。

为了找到最大的可能值 $\operatorname{MEX}$ ，我们将数组 $a$ 中的每个索引 $k$ 从 $0$ 迭代到 $n$ 。在 $k$ 的每次迭代中，如果我们找到 $a_k > 0$ ，则意味着 $\operatorname{MEX}$ 可能大于 $k$ ，因此我们可以将 $k$ 迭代到下一个值。

在迭代到下一个值之前，如果发现 $a_k > 1$ ，则表示有重复项，因此我们应该对除其中一个值之外的所有值执行操作，并将它们更改为 $k+x$ ，这样，$a_{k+x}$ 就会增加 $a_k-1$ ，并将 $a_k$ 更改为 $1$ 。在 $k$ 的每次迭代中，如果发现 $a_k = 0$ ，则意味着 $k$ 是最优解，就可以退出循环，输出最优解了。

时间复杂度为 $O(n)$。

## Code
由于洛谷的 RemoteJudge 无法使用，所以建议前往 [这里](https://codeforces.com/problemset/problem/2021/B) 提交。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
signed main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>T;
    while(T--) {
        int n,X,p=0;
        bool flag=true;
        map<int,int> mp,mp2;
        cin>>n>>X;
        for(int i=1,x;i<=n;i++) {
            cin>>x;
            mp[x]++;
        }
        while(flag) {
            if(mp[p]) {
                mp[p]--,mp2[p%X]+=mp[p],p++;
                continue;
            }
            if(mp2[(p%X)]) {
                mp2[(p%X)]--,p++;
                continue;
            }
            flag=false;
        }
        cout<<p<<'\n';
    }
    return 0;
}
```
ps：本题解参考了部分 [官方题解](https://codeforces.com/blog/entry/134873)。

---

## 作者：YuYuanPQ (赞：0)

这题很水。

显然可以贪心地操作，优先让前面的数都有，即 $\operatorname{Mex}$ 值尽量大。

那么枚举一下每个数:

如果有多的就加到后面去，只留下一个占位就行。

如果当前数没有了，这个数就是最大的 $\operatorname{Mex}$ 值。

## Code

[Link](https://codeforces.com/contest/2021/submission/284550466)

---

## 作者：cly312 (赞：0)

使用 map 维护每个值出现的次数，设数字 $a$ 出现的次数为 $mp_a$。

遍历所有小于 $n$ 的非负整数，对于一个数 $a$，如果 $mp_a>1$ 那么就将它能影响到的后面的数加 $mp_a-1$ 即 $mp_{x+a}\gets mp_{x+a}+mp_a-1$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
	int n,x;
	cin>>n>>x;
	vector<int> a(n);
	map<int,int> mp;
	for(auto &i:a){
		cin>>i;
		mp[i]++;
	}
	int mex;
	for(int i=0;i<=n;i++){
		if(!mp[i]){
			mex=i;
			break;
		}else{
			mp[i+x]+=mp[i]-1;
		}
	}
	cout<<mex<<'\n';
}
signed main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

赛时思路：

先把 $a$ 排个序。

然后枚举到每个数 $a_i$ 的时候（假设 $a_0=0$），如果：

1. $a_i=a_{i-1}$：这个数是空闲的，先把 $a_i\bmod x$ 存下来。
2. $a_i=a_{i-1}+1$：能匹配，直接过。
3. $a_i=a_{i-1}+n,n>1$：看之前空闲下来的数能不能填满这个空缺，容易发现答案不会大于 $n$，所以暴力查找 $now\bmod x$ 即可，$now$ 是现在该填的数，如果填不满，答案即为最多能填到的数。

所有数都枚举完了，最后再填一次，答案即为最后能填到的数。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int t,n,x,a[N],now,vis[N];
signed main(){
    cin>>t;
    while(t--){
        memset(vis,0,sizeof vis);
        now=0;
        cin>>n>>x;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+1+n);
        for(int i=1;i<=n;i++){
            while(a[i]>now&&vis[now%x]) vis[now%x]--,now++;
            if(a[i]>now) break;
            if(a[i]==a[i-1]&&i!=1) vis[a[i]%x]++;
            now=a[i]+1;
        }
        while(vis[now%x]) vis[now%x]--,now++;
        cout<<now<<endl;
    }
}
```

---

## 作者：Colinxu2020 (赞：0)

观察到 $a_i+x \equiv a_i \pmod x$，因此操作不会影响 $a_i \bmod x$ 的值。另外，题目保证 $x \geq 1$，因此进行一次操作后 $a_i$ 的值单调增大

注意到 $\text{MEX} \leq n$，考虑枚举 $\text{MEX}$，设当前枚举到的为 $w$，若存在一个 $i$ 满足 $a_i \leq w$ 且 $a_i \equiv w \pmod x$，那么 $w$ 就可以通过消耗 $a_i$ 被构造出。

综上，若选点 $i$ 在当前的 $w$ 中可行，则 $i$ 在 $w+x$ 中一定也可行，而 $\left(w,w+x\right)$ 中的 $w'$ 因为条件二而不会受到影响，$w' \gt x$ 时可以通过数学归纳法证明，所以我们可以对于每一个 $w$ 任意的选择符合条件的 $i$ 而不会破坏 $w' \gt w$ 时 $w'$ 的抉择。

考虑对于 $a_i \bmod x$ 分组，进而发现 $a_i \leq w$ 的限制不断放宽，因此对于每个组从小到大排序即可，之后从小到大枚举 $\text{MEX}$ 的值 $w$，如果组 $w \bmod x$ 中最小的值小于或等于 $w$，那么继续尝试 $w+1$，并取出这个最小值，否则说明最优的 $\text{MEX}$ 就是 $w$。 

参考代码（为了方便实现使用了 `priority_queue` 而不是排序）：

```cpp
#include<iostream>
#include<queue>
#include<map>
using namespace std;

int t,n,x,ai;
map<int, priority_queue<int, vector<int>, greater<int>>> mp;

int main(){
    cin>>t;
    while(t--){
        cin>>n>>x;
        for(int i=1;i<=n;i++)cin>>ai,mp[ai%x].push(ai);
        for(int i=0;i<=n;i++){
            if(mp[i%x].empty()||mp[i%x].top()>i){
                cout<<i<<endl;
                break;
            }
            mp[i%x].pop();
        }
        mp.clear();
    }
}
```

---

## 作者：zhlzt (赞：0)

### 题解

可以想到通过从小到大逐个填补空缺的数值，增大 $\text{MEX}\{a\}$。

用来填补空缺的数值 $q$ 的数 $p$ 有以下要求：

- $p<q\land p\equiv q\pmod x$。

- 将 $p$ 修改为 $q$ 之后，序列 $a$ 中还有至少一个 $p$，避免使 $\text{MEX}\{a\}$ 减小。

我们可以根据元素模 $x$ 意义下的值，开一个 `std::unordered_map` 表示同余类，同时开一个计数器记录序列 $a$ 中 $0\sim n$ 的数分别的数量。

显然最终的 $\text{MEX}\{a\}\le n$，暴力枚举即可。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int cnt[maxn],a[maxn];
unordered_map<int,queue<int> >que;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n,mod;cin>>n>>mod;
		for(int i=0;i<=n;i++) cnt[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i]; if(a[i]<=n) cnt[a[i]]++;
		}
		sort(a+1,a+1+n);
		int ans=0,val,cur;
		que.clear();
		for(int i=1;i<=n;i++) que[a[i]%mod].push(a[i]);
		for(int i=0;i<=n;i++){
			if(cnt[i]) continue;
			val=i%mod;
			if(que.find(val)==que.end()){ans=i;break;}
			if(que[val].empty()){ans=i;break;}
			while(que[val].size()){
				cur=que[val].front(); que[val].pop();
				if(cur>i) continue;
				if(cnt[cur]<2) continue;
				break;
			}
			if(que[val].empty()){ans=i;break;}
			cnt[cur]--;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

一道有趣的思维题，[Dream__Sky](https://www.luogu.com.cn/user/554665) 说 TA 做过。。
## 思路
由于每一次加的数都是 $x$，也就是说加不加这个数它对 $x$ 取余后相同。可以从这方面思考。

为了让 $\operatorname{MEX}$ 最小，可以让 $a_i$ 互不相同。这样可以使答案大。

原因：对于一个 $a$，且数组已经至少有 $2$ 个 $a$ 了，若 $\operatorname{MEX}$ 不为 $a+x$，事实上这个数无论如何都没有贡献；为 $a+x$ 的话，加上去可以将 $\operatorname{MEX}$ 更大，因为 $a+x$ 存在了。

对数组排序，按顺序遍历，对于一个 $i$，若 $a_i$ 存在，则不断将 $a_i$ 加上 $x$ 即可。

最后求出 $a$ 的 $\operatorname{MEX}$。

---

