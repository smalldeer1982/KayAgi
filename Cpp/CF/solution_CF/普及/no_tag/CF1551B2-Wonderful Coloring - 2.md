# Wonderful Coloring - 2

## 题目描述

This problem is an extension of the problem "Wonderful Coloring - 1". It has quite many differences, so you should read this statement completely.

Recently, Paul and Mary have found a new favorite sequence of integers $ a_1, a_2, \dots, a_n $ . They want to paint it using pieces of chalk of $ k $ colors. The coloring of a sequence is called wonderful if the following conditions are met:

1. each element of the sequence is either painted in one of $ k $ colors or isn't painted;
2. each two elements which are painted in the same color are different (i. e. there's no two equal values painted in the same color);
3. let's calculate for each of $ k $ colors the number of elements painted in the color — all calculated numbers must be equal;
4. the total number of painted elements of the sequence is the maximum among all colorings of the sequence which meet the first three conditions.

E. g. consider a sequence $ a=[3, 1, 1, 1, 1, 10, 3, 10, 10, 2] $ and $ k=3 $ . One of the wonderful colorings of the sequence is shown in the figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1551B2/dbd09f59a345c41308d3382019b949ebfdfed535.png)The example of a wonderful coloring of the sequence $ a=[3, 1, 1, 1, 1, 10, 3, 10, 10, 2] $ and $ k=3 $ . Note that one of the elements isn't painted.Help Paul and Mary to find a wonderful coloring of a given sequence $ a $ .

## 说明/提示

In the first test case, the answer is shown in the figure in the statement. The red color has number $ 1 $ , the blue color — $ 2 $ , the green — $ 3 $ .

## 样例 #1

### 输入

```
6
10 3
3 1 1 1 1 10 3 10 10 2
4 4
1 1 1 1
1 1
1
13 1
3 1 4 1 5 9 2 6 5 3 5 8 9
13 2
3 1 4 1 5 9 2 6 5 3 5 8 9
13 3
3 1 4 1 5 9 2 6 5 3 5 8 9```

### 输出

```
1 1 0 2 3 2 2 1 3 3
4 2 1 3
1
0 0 1 1 0 1 1 1 0 1 1 1 0
2 1 2 2 1 1 1 1 2 1 0 2 2
1 1 3 2 1 3 3 1 2 2 3 2 0```

# 题解

## 作者：Starlit_Night (赞：8)

#### 题目分析  
本题相比起B1题而言，颜色的数量不固定，并且要求输出的是染色情况。因此可以继续带着B1题的思路做。  
1. 用一个数组统计每个数字出现次数，若该数字出现次数小于颜色数量则可以给这个数字染色，反之，第 $k$ 次及以后出现的该数字无法被染色。用一个`vector`储存能被染色的数字及其输入顺序。
2. 将`vector`按照数字从小到大排序，然后依次染上 $k$ 种颜色。
3. 将结果输出。

#### 细节注意  
1. 给`vector`排序的目的
2. 最多能有多少数字被染色  

以上两条是我认为细节上存在思维难度的地方，核心代码中的注释有详细解释。
#### 核心代码  
```cpp
int main() {
	int m,n,k;
	cin>>m;
	while(m--){
		int cnt[200005],ans[200005],inp;//cnt统计26个字母的个数,ans存储染色结果
		vector<pair <int,int> > v;
		cin>>n>>k;
		for(int i=0;i<=n;i++){
			ans[i]=0;cnt[i]=0;
		}
		for(int i=0;i<n;i++){
			cin>>inp;		
			//cout<<"cnt[inp]: "<<cnt[inp]<<" ";
			if(cnt[inp]<k){
				v.push_back({inp,i});
			}
            		cnt[inp]++;		
		}
		sort(v.begin(),v.end());//排序，目的是为了避免同个数字被染同样色
		int groups=v.size()/k;//把能染色的个数分成k组，设一次染色过程为把k种颜色各自用一遍，groups就是能有几次染色过程
		for(int i=0;i<groups*k;i++){//gruops*k即为保证用各种颜色次数相等时的最大染色数量
			ans[v[i].second]=i%k+1;//染色
		}
		for(int i=0;i<n;i++) cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：UperFicial (赞：3)

$\huge\text{Sol}$

题意应该很清晰了，直接说解法。

考虑抽象 $k+1$ 个长度无限的容器，每个容器内的数字各不相同，除了第 $0$ 个容器。

所以现在需要将 $a_1,a_2,\cdots,a_n$ 排着填入容器，发现这样做不太好，因为值相同的若干个元素不一定放到哪个容器中合适。

于是考虑对 $a$ 排序，并得到排序并去重后的序列 $b$，与 $b_i$ 在 $a$ 中出现几次。

然后问题就很简单了，枚举 $i$，并分情况讨论：

- $cnt[b_i]>k$。说明 $b_i$ 这个元素肯定不能全放到这 $k$ 个容器里，因为会有重复，于是我们将 $b_i$ 中的 $k$ 个元素放入 $k$ 个容器，其余放入 $0$ 号。

- $cnt[b_i]=k$。说明这个元素刚好可以排着将 $k$ 个容器依次放入。

- $cnt[b_i]<k$。不足 $k$ 个，那么我们维护当前空缺位置 $lst$，每次不管哪种情况放元素都从 $lst$ 开始放，相应更新 $lst$。然后这种情况就排着放就行了。

然后我们用 $\text{vector}$ 随便维护一下这个容器即可。

赛时出了个 $\text{sb}$ 错误，$\color{red}\texttt{WA}$ 了 $3$ 发，调了好久，没来得及做 $C$……菜死了/kk

---

## 作者：FwbAway (赞：2)

因为题目说同色的两个元素两两各不相同，所以任何元素在一种颜色中最多只能出现一次。一共有 $k$ 种颜色，所任何被染色的元素中一个值只能出现最多 $k$ 次。如果超过了 $k$ 次，题目运行将会发生错误。

贪心算法，按每个集合的下标 把 $a[k]$ 挨个分给每个集合，贪心加```vetcor```实现，是很好的选择。

两种颜色也就是说涂的颜色一定是偶数，是了之后记录一些元素下标就可以了。

---

## 作者：NXYorz (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1551B2)

---------
### 题目大意
给定序列 $a_n$ ，并用 $k$ 种颜色给它涂色。

规定:

- 每一个数字要么被涂一个颜色，要么不涂色。
- 相同的数字不会一个颜色。
- $k$ 种颜色所涂的数字的数量应该相同。

求出任意一组涂色后的序列。

--------
### 分析
与上道题目大致相同，仍要统计出每一个数字出现的次数，然后根据出现次数是否对于小于 $k$ 做出判断。~~感觉这道题在考代码实现。~~

感觉较难的地方是处理 出现次数小于 $k$ 的部分。

一开始考虑用 ```vector``` 然后放在队列里大力操作， MLE 了 /kk。

后来发现不用把相同的数字绑在一起，把他们看成一个个单独的个体，统统放到结构体(权值，位置)里，排序一下所有相同的数字都会在一起，然后依次涂色即可 qwq。

--------
### $Code$
```cpp
/*---------AC代码----------*/
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>

using namespace std;

const int N = 2e5 + 10;

int t,n,k,tot;
int a[N],ans[N],sum[N],cnt[N];
struct El
{
	int w;
	int loc;
	bool operator < (const El &B) const{
		return w < B.w;
	}
}b[N];

void work()
{
	memset(ans , 0 , sizeof(ans));
	memset(sum , 0 , sizeof(sum));
	memset(cnt , 0 , sizeof(cnt));
	scanf("%d%d",&n,&k); tot = 0;
	for(int i = 1; i <= n; i++)
		scanf("%d",&a[i]) ;
	for(int i = 1; i <= n; i++)
		sum[a[i]]++;

	for(int i = 1; i <= n; i++)
		if(sum[a[i]] >= k && cnt[a[i]] + 1 <= k)
			ans[i] = ++cnt[a[i]];
		else if(sum[a[i]] < k) b[++tot].w = a[i] , b[tot].loc = i;
	sort(b + 1 , b + 1 + tot);

	int kkk = 0;
	for(int i = 1; i <= tot; i++)
	{
		if(tot - i + 1 < k && kkk == 0) break;
		ans[b[i].loc] = ++kkk;
		if(kkk  + 1 > k) kkk = 0;
	}
	for(int i = 1; i <= n; i++)
		printf("%d ",ans[i]);
	printf("\n");
}

int main()
{
//	freopen("aa.in","r",stdin);
	scanf("%d",&t);
	while(t--)
		work();
}
```

```cpp
/*----------MLE------------*/
#include<cstdio>
#include<vector>
#include<cstring>

using namespace std;

const int N = 2e5 + 10;

int t,n,k;
int a[N],ans[N];
vector<int> sum[N];

struct queue
{
	int head,tail,size;
	vector<int> a[N];

	void clear()
	{head = tail = 0;}

	bool empty()
	{return head == tail ? true : false;}

	void push(vector<int> x)
	{a[tail++] = x; size += x.size();}

	inline vector<int> front()
	{return a[head];}

	inline void pop() {size -= a[head].size();head++;}

}q;

void work()
{
	memset(ans , 0 , sizeof(ans));
	scanf("%d%d",&n,&k); q.clear();
	for(int i = 1; i <= n; i++)
		scanf("%d",&a[i]) , sum[i].clear();
	for(int i = 1; i <= n; i++)
		sum[a[i]].push_back(i);

	for(int i = 1; i <= n; i++)
		if(sum[i].size() >= k)
			for(int j = 1; j <= k; j++)
				ans[sum[i][j - 1]] = j;
		else q.push(sum[i]);
	
	while(q.size >= k)
	{
		int cnt = k;
		while(cnt)
		{
			vector<int> now = q.front(); q.pop();
			for(int i = 1; i <= now.size(); i++)
			{
				ans[now[i - 1]] = k - cnt + 1;
				cnt--; if(!cnt) break;
			}
		}	
	}

	for(int i = 1; i <= n; i++)
		printf("%d ",ans[i]);
	printf("\n");
}

int main()
{
//	freopen("aa.in","r",stdin);
	scanf("%d",&t);
	while(t--)
		work();
}
```

---

## 作者：Interstellar_Zhou (赞：1)

本题我们首先用桶扫一遍序列，由于需要存出下标，所以我们把桶定义成 vector 形式。接下来扫一遍桶。由于方便，我们将每种颜料所涂的下标用 vector 来存
- 若桶中数字数量 $>= k$，则将所有k个容器都加入一个，剩下来的就没办法了
- 若 $<k$ ，则先把其暂存在另一个序列里，我们称之为“暂存序列”，长度为 cnt

扫完我们遍历暂存序列，但是由于要满足"每一种颜色染的字母的数量全部相等"的条件，所以我们可以只遍历到 `cnt-cnt%k` ，感性理解就是最后一个不大于 cnt 且是 k 倍数的数。这样我们就依次放入容器就行了，我们就一个一个按顺序放，即为 `i%k+1`。

暂存序列搞定之后，剩下的就是把所有容器存的数下标取出来，把结果数组的相应位置赋上答案即可。

代码实现：

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 2e5 + 100;
int T, n, k, a[MAXN], b[MAXN], cnt, p[MAXN], vis[MAXN];
vector<int> bucket[MAXN], vec[MAXN];

int main() {
    scanf("%d", &T);
    while(T --) {
        scanf("%d%d", &n, &k);
        int cnt = 0;
        for(int i=1; i<=n; i++) {
            scanf("%d", &a[i]);
            bucket[a[i]].push_back(i);
        }
        for(int i=1; i<=n; i++) {
            if(bucket[a[i]].size() >= k && !vis[a[i]]) {
                for(int j=0; j<k; j++) {
                    vec[j+1].push_back(bucket[a[i]][j]);
                }
                vis[a[i]] = 1;
            } else if(bucket[a[i]].size() > 0 && !vis[a[i]]) {
                for(int j=0; j<bucket[a[i]].size(); j++) {
                    b[++cnt] = bucket[a[i]][j];
                }
                vis[a[i]] = 1;
            }
        }
        for(int i=1; i<=cnt-cnt%k; i++) {
            vec[i%k+1].push_back(b[i]); // 剩下的依次涂上各个颜色即可 无需考虑数字重复问题
        }
        for(int i=1; i<=k; i++) {
            for(int j=0; j<vec[i].size(); j++) {
                int id = vec[i][j];
                p[id] = i;
            }
        }
        for(int i=1; i<=n; i++) {
            printf("%d ", p[i]);
            // 小优化：memset比较慢 通过这种方式可以省一些常数
            bucket[i].clear();
            vec[i].clear();
            p[i] = 0;
            b[i] = 0;
            vis[i] = 0;
        }
        printf("\n");
    }
    return 0;
}
```



---

## 作者：black_trees (赞：0)



整场比赛的题解：[Link](https://www.luogu.com.cn/blog/Junko-Youmu/cfr-734)（目前还没补完）。

因为B2的思路需要B1，所以此处加上了B1的题解。



## B1

题目大意：

>有两种颜色红和绿，现在给你一个只有小写字母的字符串。

>现在要求你给每个元素涂上一种颜色（可以不涂）。
   
>一个涂法是“漂亮的”，需要满足以下条件：
   
>1.涂上同一种颜色的所有字母不能相同。
   
>2.涂成红色的字母个数和涂成绿色的字母个数需要相等。
   
>给定一个字符串，请问它涂成红色（或绿色）的字母最多有多少个？

首先考虑第一个条件。

转化一下也就是说每一种字母最多只能有两个被涂上颜色。

所以我们开一个桶统计一下每一个字母的出现次数并对其进行判断。

再考虑第二个条件。

因为只会有两种颜色，所以涂上颜色的点的个数必须是偶数（ $2$ 的倍数）。

那么思路就出来了，统计一下每一个字母出现的次数，并且统计它最多有多少个字母可以被涂上颜色。

对于每一种字母，如果它的个数小于等于 $2$ 那么就都可以被涂色，如果大于等于 $3$ 就只有两个可以被涂上颜色。

因为有两种颜色，所以答案就是可以被涂上颜色的字母个数除以 $2$。

如果最后可以被涂上颜色的字母个数是个奇数，就需要先减 $1$ 再除 $2$。

Code略。

## B2：

题目大意：

>同B1。
    
>不过现在有 $k$ 种颜色而且要求你输出（任意合法）的方案。
   
>而且不再是字母而是数字。
   
>并且只需要输出方案，但仍然需要保证被涂上颜色的元素尽可能多。

从B1的角度考虑，现在有 $k$ 种不同颜色。

我们仍旧是统计每一个不同的元素出现多少次。

如果大于 $k$ 那么就只有 $k$ 个可以被涂色。

反之都可以。

然后统计完之后我们按 $a[i]$ 的大小排个序。

也就是把同一种都扔到一起处理。

对于每一种，我们只涂前 $k$ 个（保证不重复而且涂够），就可以了。

但是我们要输出方案，所以需要记录一下元素的位置。

Code：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int si=2e5+10;
int a[si];
int cnt[si];
int ans[si];
int tmp[si];

struct node{
	int fr,se;
	bool operator < (const node &u)const{
		return fr<u.fr;
	}
}rec[si];
int n,k,T;

signed main(){
	scanf("%lld",&T);
	while(T--){
		int s=0;
		scanf("%lld%lld",&n,&k);
		for(register int i=1;i<=n;i++){
			ans[i]=0;
			scanf("%lld",&a[i]);
			cnt[a[i]]++;
			if(cnt[a[i]]>k){
				rec[i].fr=rec[i].se=0;
			}
			else rec[i].fr=a[i],rec[i].se=i;
        //判一下能不能被涂色
		} 
		sort(rec+1,rec+n+1);
		int now=1;
		for(register int i=1;i<=n;i++){
			if(rec[i].fr){
				ans[rec[i].se]=now++;
				if(now>k) now=1;
			}
		}
		for(register int i=1;i<=n;i++){
			++tmp[ans[i]];
		}
		int fal=1e9;
		for(register int i=1;i<=k;i++){
			fal=min(fal,tmp[i]);
		}
		for(register int i=n;i>=1;i--){
			if(tmp[ans[i]]>fal){
				tmp[ans[i]]--,ans[i]=0;
			}
		}
		for(register int i=1;i<=n;i++){
			printf("%lld ",ans[i]);
		}
		puts("");
		for(register int i=1;i<=k;i++){
			tmp[i]=0;
		}
		for(register int i=1;i<=n;i++){
			cnt[a[i]]=0;
		}//多测，清空
	}
	return 0;
}

```

---

## 作者：KSToki (赞：0)

# 题目大意
给定一个长度为 $n$ 的数组 $a$，取出 $k$ 个相离的大小相同的下标集合，集合中每个下标对应的数字需不同，最大化集合的大小，并输出方案。
# 题目分析
首先统计每个数字出现的次数，如果大于等于 $k$ 那么显然每个集合分一个，否则待定。贪心地，最后将待定的数字依次 $k$ 个一组分配给每个集合即可，这里可以用 `vector` 实现。
# 代码
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,k,x,ans[200001];
vector<int>num[200001],vec;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		k=read();
		for(R int i=1;i<=n;++i)
		{
			num[i].clear();
			ans[i]=0;
		}
		vec.clear();
		for(R int i=1;i<=n;++i)
		{
			x=read();
			num[x].push_back(i);
		}
		for(R int i=1;i<=n;++i)
		{
			if(num[i].size()>k)
				for(R int j=0;j<k;++j)
					ans[num[i][j]]=j+1;
			else
			{
				for(R int j=0,up=num[i].size();j<up;++j)
					vec.push_back(num[i][j]);
			}
		}
		for(R int i=0,up=vec.size();i+k-1<up;i+=k)
		{
			for(R int j=i;j<i+k;++j)
				ans[vec[j]]=j-i+1;
		}
		for(R int i=1;i<=n;++i)
			printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}

```

---

## 作者：Mysterious_Mini (赞：0)

### 分析

由于同色的两个元素值各不相同，所以任何元素在一种颜色中最多只能出现一次。又因为一共有 $k$ 种颜色，所以任何被染色的元素中一个值只能出现最多 $k$ 次。

我们考虑在输入元素的同时进行记录。定义一个空数组 $x$，如果一个元素出现次数 $\le k$，则把该元素和其下标打包放到 $x$ 数组末尾。为了方便最后输出，我们需要记录下标，毕竟是按照输入的顺序进行输出的。至于为什么要打包，后面会进行解释。

接下来我们进行染色，为了防止把两个或者更多相同的元素染成同一种颜色，我们要把 $x$ 数组里的所有元素按元素值从小到大进行排序。因为染上每种颜色的元素个数要相同，所以 $x$ 数组里的元素个数必须是 $k$ 的倍数。在保证留下来的元素个数最大的情况下，还要移除一些元素。

之后挨个染上 $k$ 种颜色，按照输入时的下标输出即可。因为是多组数据，所以每次操作之后要记得清空数组。

时间复杂度 $O(Tn \log n)$，看着挺吓人，其实题目给了限制：输入的 $n$ 总和不超过 $2 \times 10^5$，显然可以过。这里吐槽一下：这句话没有翻译出来。

代码很好写，就不给了。

---

