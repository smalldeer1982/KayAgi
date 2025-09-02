# Serval and Toxel's Arrays

## 题目描述

Toxel likes arrays. Before traveling to the Paldea region, Serval gave him an array $ a $ as a gift. This array has $ n $ pairwise distinct elements.

In order to get more arrays, Toxel performed $ m $ operations with the initial array. In the $ i $ -th operation, he modified the $ p_{i} $ -th element of the $ (i-1) $ -th array to $ v_{i} $ , resulting in the $ i $ -th array (the initial array $ a $ is numbered as $ 0 $ ). During modifications, Toxel guaranteed that the elements of each array are still pairwise distinct after each operation.

Finally, Toxel got $ m+1 $ arrays and denoted them as $ A_{0}=a, A_{1},\ldots,A_{m} $ . For each pair $ (i,j) $ ( $ 0\le i<j\le m $ ), Toxel defines its value as the number of distinct elements of the concatenation of $ A_{i} $ and $ A_{j} $ . Now Toxel wonders, what is the sum of the values of all pairs? Please help him to calculate the answer.

## 说明/提示

In the first test case, the arrays change as follows: $ [1,2,3]\to[\underline{4},2,3]\to[4,\underline{5},3] $ .

The concatenation of the $ 0 $ -th array and the $ 1 $ -st array is $[1,2,3,4,\sout{2},\sout{3}]$ . There are $ 4 $ distinct elements.

The concatenation of the $ 0 $ -th array and the $ 2 $ -nd array is $[1,2,3,4,5,\sout{3}] $ . There are $ 5 $ distinct elements.

The concatenation of the $ 1 $ -st array and the $ 2 $ -nd array is $[4,2,3,\sout{4},5,\sout{3}] $ . There are $ 4 $ distinct elements.

Strikethrough elements are duplicates in the array.

Therefore, the answer is $ 4+5+4=13 $ .

In the second test case, note that the array may remain unchanged after operations.

## 样例 #1

### 输入

```
3
3 2
1 2 3
1 4
2 5
1 1
1
1 1
10 10
4 6 9 12 16 20 2 10 19 7
1 3
5 4
2 17
2 18
6 11
7 1
8 17
5 5
5 5
2 2```

### 输出

```
13
1
705```

# 题解

## 作者：Binary_Lee (赞：21)

## [题面传送门](https://www.luogu.com.cn/problem/CF1789C)

### 解决思路

因为每个数列内的数字不重复，所以我们考虑每个数在多少个数列中出现过。记数字 $x$ 的出现次数为 $cnt_x$，如何求它对答案的贡献呢？

已知一共有 $m+1$ 个数列，其中 $cnt_x$ 个含有 $x$。我们就行分类讨论：

- 取出一个含 $x$ 数列和一个不含 $x$ 数列，会对答案产生 $1$ 的贡献，这样取的方案数为 $cnt_x\times(m+1-cnt_x)$（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/jgnm012c.png)

- 取出两个含 $x$ 数列，会对答案产生 $1$ 的贡献，这样取的方案数为 $cnt_x\times(cnt_x-1)\div2$（如下图）。

![](https://cdn.luogu.com.cn/upload/image_hosting/i9pjpcdm.png)

这样答案就很明了了。

然后考虑如何求出每个数出现的次数。

记 $lst_x$ 表示数字 $x$ 上一次出现的位置。初始存在为 $0$，没出现过为 $-1$。每次 $x$ 要被改成 $y$ 时，$cnt_x$ 要加上 $i-lst_x$，$i$ 为当前的位置，表示这一段中 $x$ 持续存在。然后把 $lst_x$ 改回 $-1$，将 $y$ 设为 $i$。注意所有操作完成后要扫一遍所有数，如果 $lst$ 不为 $-1$，还要加上最后一段的长度。具体可以看代码。

### AC Code

```cpp
//If, one day, I finally manage to make my dreams a reality...
//I wonder, will you still be there by my side?
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
#define y1 cyy
#define fi first
#define se second
#define cnt1(x) __builtin_popcount(x)
#define mk make_pair
#define pb push_back
#define pii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define lbt(x) (x&(-x))
using namespace std;
int T,n,m,a[200005],cnt[400005],lst[400005],x,y;
string s; 
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n+m;i++) cnt[i]=0,lst[i]=-1;
	for(int i=1;i<=n;i++) cin>>a[i],lst[a[i]]=0;
	for(int i=1;i<=m;i++){
		cin>>x>>y;
		if(a[x]!=y){
			cnt[a[x]]+=i-lst[a[x]],lst[a[x]]=-1;
			lst[y]=i,a[x]=y;
		}
	}
	for(int i=1;i<=n+m;i++) if(lst[i]!=-1) cnt[i]+=m-lst[i]+1;
	int ans=0;
	for(int i=1;i<=n+m;i++){
		ans+=cnt[i]*(m+1-cnt[i]);
		ans+=cnt[i]*(cnt[i]-1)/2;
	}
	cout<<ans<<endl;
}
signed main(){
	IOS;TIE;
	cin>>T;
	while(T--) solve();
	return 0;
}
```

---

## 作者：yuanruiqi (赞：4)

## 题意简述

给定一个不重的数组和 $m$ 次操作，每次操作更改数组中的一个数，时刻保证数组不重。求包括的初始数组的 $m+1$ 个数组两两的并集的元素个数之和。

## 题目分析

对于第 $i$ 次修改操作，计算当前数组与前 $i$ 个历史版本的贡献。因为数组不重，所以并集中一定有自身的 $n$ 个元素，可以先给答案增加 $i \times n$。接下来计算前 $i$ 个历史版本出现但是当前不存在的数字的个数，下文记为 $sum$。统计进答案即可。具体而言，在修改操作时同时维护 $sum$。如将 $p$ 位置更改为 $q$，我们就可以给 $sum$ 加上 $a_p$ 之前出现的次数，减去 $q$ 之前对 $sum$ 的贡献 $del_{q}$。维护这些信息，只需要记录每一个数字出现的时间和删除时给 $sum$ 的贡献即可。

## 代码

```cpp
void solve()
{
    i64 n, m;
    cin >> n >> m;
    vector<int> a(n+1), vis(n+m+1), del(n+m+1);
    for (int i=1;i<=n;++i)
        cin >> a[i];
    i64 ans = 0, sum = 0, p, q;
    for (int i=1;i<=m;++i)
    {
        cin >> p >> q;
        int tmp = i - vis[a[p]] + del[a[p]];
        sum += tmp;
        del[a[p]] = tmp;
        sum -= del[q];
        vis[q] = i;
        ans += n * i + sum;
        a[p] = q;
    }
    cout << ans << '\n';
}
```


---

## 作者：__vector__ (赞：1)

## 题外话  
本题解作者赛时由于漏了一个 -1，调了 1h，导致的分数损失约为 350，排名损失约为 600，最后还是把小号送上了 Specialist。  
## 题解  
为了方便表示，设 $f(i,j)$ 为 $A_i$ 与 $A_j$ 不同元素总数。  

### 解法一 
暴力计算 $\sum_{i=1}^{n} \sum_{j=0}^{i-1} f(i,j)$。  
复杂度 $O(n^3)$。  
### 解法二  
想想有没有什么优化。  

可以看到每次生成新序列，只从上一个序列修改一个数字，那就启发我们每个序列的答案可以从上一个序列转移，现在把它表示出来：设 $dp_i$ 为 $\sum_{j=0}^{i-1} f(i,j)$。  

设本次修改得到的序列为 $A_i$，现在分类讨论一下。  
1. 如果本次修改的元素，新值等于旧值，即没有改变原序列，那么 $\sum_{j=0}^{i-2} f(i,j) = dp_{i-1}$，而 $f(i,j-1)$ 显然等于 $n$，即 $dp_i = dp_{i-1} + n$。  
2. 如果本次修改的元素，新值不等于旧值，即改变了原序列，这时我们可以先假设本次修改没有改变原序列，先使用情况 $1$ 的答案，然后再根据修改的元素调整答案。我们可以先减去被改掉的旧值的贡献，再加上新值的贡献。而这个东西怎么计算呢，显然只需要分别统计对于所有的 $0 \le j \le i-1$，有多少个 $A_j$ 没有旧值，有多少个 $A_j$ 没有新值。  

至此，做法基本确定。  

但是问题来了，怎么快速统计每个元素没有出现在多少个序列里，它可以转化为快速统计每个元素出现在了多少个序列里。  

由于没有后效性，即对于每个 $dp_i$，只有 $0$ 到 $i-1$ 会进行转移，所以这个统计数值也可以动态转移。  

显然不能每增加一个序列就去修改所有的元素出现次数，我们发现修改操作每次只是让一个元素消失，让另一个元素出现，我们可以让它自己改。  

也就是设 $start_i$ 表示第 $i$ 种元素在第几个序列开始出现，如果为 $-1$ 代表没出现过；$end_i$ 表示第 $i$ 种元素在第几个序列最后一次出现，如果为 $-1$ 代表一直到现在还没有消失。  

第 $i$ 种元素总出现次数即 $end_i - start_i + 1$。  

修改的时候，如果是让某元素消失，直接标记上 $end = i-1$ 就行了。  

如果是让某元素出现，那分讨一下。  
1. 之前没出现过，标记上 $start = i$，$end = -1$。  
2. 之前出现过，那还得计算之前的贡献，然后再算上现在的贡献，同时因为从现在开始这个元素又重新出现了，$end$ 必须等于 $-1$，而为了使答案正确，我么可以让 $start = i-(end - start + 1) +1 - 1 = i-(end-start+1)$，形象地理解，这是把之前这个元素出现区间般过来，然后把右端点删掉。    

[CF 提交记录](https://codeforces.com/contest/1789/submission/194967159)  

---

## 作者：MspAInt (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1789C)

duel bot.duel bot.duel bot.

定义 $a_i$ 为 $i$ 时刻的序列，$s_i$ 表示 $i$ 在 $s_i$ 个序列中出现。

直接求很不好做啊！正难则反，考虑从每个数往答案上贡献。

$x$ 对答案造成贡献，有两种可能：

1. 统计 $f(i,j)$ 时，如果 $a_i$ 含有 $x$，且 $a_j$ 不含 $x$，则造成 $1$ 的贡献。两两贡献一次，总贡献为 $s_x\times(m+1-s_x)$。
1. 统计 $f(i,j)$ 时，如果 $a_i$ 含有 $x$，且 $a_j$ 也含有 $x$，则也造成 $1$ 的贡献。两两贡献一次，总贡献为 $\dfrac{s_x\times(s_x-1)}{2}$。

$s_x$ 很好统计，记录 $x$ 上一次出现的序列累加即可。最后还要再累加一遍。

记得清空数组。

Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int T,n,a[N],m,h[N<<1],s[N<<1];
long long ans;
long long solve(){
	scanf("%d%d",&n,&m);ans=0;
    for(int i=1;i<=n+m;i++)s[i]=0,h[i]=-1;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),h[a[i]]=0;
    for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
        if(a[x]==y)continue;
		s[a[x]]+=i-h[a[x]],h[a[x]]=-1;
        h[y]=i,a[x]=y;
	}
    for(int i=1;i<=n+m;i++)if(h[i]!=-1)s[i]+=m-h[i]+1;
    for(int i=1;i<=n+m;i++)ans+=1ll*s[i]*(s[i]-1)/2+1ll*s[i]*(m+1-s[i]);
    return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)printf("%lld\n",solve());
   return 0;
}
```

[record](https://www.luogu.com.cn/record/123612040)

---

