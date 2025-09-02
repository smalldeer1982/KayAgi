# Playlist

## 题目描述

Arkady has a playlist that initially consists of $ n $ songs, numerated from $ 1 $ to $ n $ in the order they appear in the playlist. Arkady starts listening to the songs in the playlist one by one, starting from song $ 1 $ . The playlist is cycled, i. e. after listening to the last song, Arkady will continue listening from the beginning.

Each song has a genre $ a_i $ , which is a positive integer. Let Arkady finish listening to a song with genre $ y $ , and the genre of the next-to-last listened song be $ x $ . If $ \operatorname{gcd}(x, y) = 1 $ , he deletes the last listened song (with genre $ y $ ) from the playlist. After that he continues listening normally, skipping the deleted songs, and forgetting about songs he listened to before. In other words, after he deletes a song, he can't delete the next song immediately.

Here $ \operatorname{gcd}(x, y) $ denotes the [greatest common divisor (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor) of integers $ x $ and $ y $ .

For example, if the initial songs' genres were $ [5, 9, 2, 10, 15] $ , then the playlist is converted as follows: \[5, 9, 2, 10, 15\] $ \to $ \[5, 9, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] (because $ \operatorname{gcd}(5, 9) = 1 $ ) $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 2, 10, 15\] $ \to $ \[5, 10, 15\] (because $ \operatorname{gcd}(5, 2) = 1 $ ) $ \to $ \[5, 10, 15\] $ \to $ \[5, 10, 15\] $ \to $ ... The bold numbers represent the two last played songs. Note that after a song is deleted, Arkady forgets that he listened to that and the previous songs.

Given the initial playlist, please determine which songs are eventually deleted and the order these songs are deleted.

## 说明/提示

Explanation of the first test case is given in the statement.

In the second test case, the playlist is converted as follows: \[1, 2, 4, 2, 4, 2\] $ \to $ \[1, 2, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] (because $ \operatorname{gcd}(1, 2) = 1 $ ) $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[1, 4, 2, 4, 2\] $ \to $ \[4, 2, 4, 2\] (because $ \operatorname{gcd}(2, 1) = 1 $ ) $ \to $ \[4, 2, 4, 2\] $ \to $ ...

In the third test case, the playlist is converted as follows: \[1, 2\] $ \to $ \[1, 2\] $ \to $ \[1\] (because $ \operatorname{gcd}(1, 2) = 1 $ ) $ \to $ \[1\] $ \to $ \[1\] (Arkady listened to the same song twice in a row) $ \to $ \[\] (because $ \operatorname{gcd}(1, 1) = 1 $ ).

The fourth test case is same as the third after deletion of the second song.

In the fifth test case, the same song is listened to over and over again, but since $ \operatorname{gcd}(2, 2) \ne 1 $ , it is not deleted.

## 样例 #1

### 输入

```
5
5
5 9 2 10 15
6
1 2 4 2 4 2
2
1 2
1
1
1
2```

### 输出

```
2 2 3 
2 2 1 
2 2 1 
1 1 
0```

# 题解

## 作者：vectorwyx (赞：4)

从最简单的暴力想起。不断循环，记一个变量 $last$ 表示上一首听的歌曲是哪一首，如果 $\gcd(a_i,last)=1$，就把 $last$ 清零（记 $\gcd(x,0)=0$），然后给第 $i$ 个位置打上删除标记，跳到下一个位置继续循环。如果所有歌曲都被删除或当前循环已经走到了上一轮循环走过的位置，就结束循环。这样子做是 $O(n^2k)$ 的（$k$ 是计算最大公约数的常数）。

如何优化呢？我们发现在循环的过程中会重复判断很多在之前就已经判断过的相邻歌曲对的 $\gcd$ 是否为 $1$。比如说 $15,20,10,5,9,2,10$，暴力会先判断 $(15,20),(20,10),(10,5),(5,9)$。然后判断 $(2,10),(10,15),(15,20),(20,10),(10,5),(5,2)$。然而 $(15,20),(20,10),(10,5)$ 这一段我们在第一轮循环时就已经知道它们判断的结果了，因此可以省去。

那么正解就呼之欲出了，我们用一个队列来存储需要判断且尚未判断的相邻歌曲对，然后不断弹出队首。如果当前这一对 $(x,y)$ 的 $\gcd$ 为 $1$，那么就删除 $y$，在队尾加入 $(x,z)$，其中 $z$ 是位于 $x$ 右邻的尚未删除的歌曲的编号。删除和查询右邻操作可以用链表来实现，不难看出这样的复杂度是 $O(nk)$ 的。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e6+5;
int a[N],s1[N],s2[N],top,ans[N],w,L[N],R[N],d[N];

void del(int x){
	R[L[x]]=R[x];
	L[R[x]]=L[x];
}

void work(){
	int n=read();
	top=w=0;
	fo(i,1,n) a[i]=read(),L[i]=i-1,R[i]=i+1,d[i]=0;
	L[1]=n,R[n]=1;
	fo(i,1,n-1) s1[++top]=i,s2[top]=i+1;
	s1[++top]=n,s2[top]=1;
	fo(i,1,top){
		if(w==n) break;
		if(d[s1[i]]||d[s2[i]]) continue;
		int g=__gcd(a[s1[i]],a[s2[i]]);
		//printf("%d %d %d\n",s1[i],s2[i],g);
		if(g==1){
			ans[++w]=s2[i];
			d[s2[i]]=1;
			s1[++top]=s1[i];
			s2[top]=R[s2[i]];
			del(s2[i]);
		} 
	}
	printf("%d ",w);fo(i,1,w) printf("%d ",ans[i]);puts("");
	//puts("");
}

int main(){
	int T=read();
	while(T--) work(); 
	return 0;
}
```


---

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1483B)

ARC掉分后脑子抽，2C卡了1h，最后2：05的时候pp了这个题最后成功上分

~~话说我是样例RE一个，就加个特判，然后最后一遍pp还A了？~~

不难想到维护一个链表代表当前的歌曲链表，然后问题就在与我们需要每次快速找到最近的需要删除的数，不妨先处理所有 $gcd(a_i,a_{i+1})=1$ 的 $i$ 写一个链表，从链表第一项开始计算，计算完以后看 $a_i$ 和 $next_{a_i}$（即第一个链表，实际中的下一项）是否为 $1$. 如果为 $1$，我们不删除链表二中的节点 $i$，遍历下一个。否则，$i$ 不会再删除它后面的，我们删除掉链表二中的节点 $i$，遍历下一个。

注意点：

1. 如果预处理时没有符合条件的 $i$（链表二为空），直接输出 $0$.

2. 注意删除链表和跳转的先后顺序等。

3. 不删除链表二的节点 $i$ 的时候，若链表二只剩下 $i$ 一项，下一次还是跳转到 $i$ 而不是跳转到 $0$ 导致错误的中断循环。

4. 若删除链表二的节点 $i$，出现 $3$ 的情况，那么直接中断循环。

这个 DS 题好像我用的 DS 是最平凡的，这个 D 比 C 友好多了吧，Div2好像都被 C 恶心到了都没人做 D 这个大水题（）

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define mapit map<int,int>::iterator
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10;
ll T,n,a[MAXN];
ll pre1[MAXN],next1[MAXN],pre2[MAXN],next2[MAXN],ret;
vector<int>ans;
ll gcd(ll a,ll b){
	if(!b)return a;
	return gcd(b,a%b);
}
void Delete(int i){
	int p=pre1[i],n=next1[i];
	pre1[i]=next1[i]=0;
	next1[p]=n;
	pre1[n]=p; 
}
void Delete2(int i){
	int p=pre2[i],n=next2[i];
	pre2[i]=next2[i]=0;
	next2[p]=n;
	pre2[n]=p;
}
int main(){
	cin>>T;
	while(T--){
		cin>>n;ret=0;ans.clear();
		rep(i,1,n){
			cin>>a[i];
			next1[i]=i+1;
			pre1[i]=i-1;
			pre2[i]=next2[i]=0;
		}
		pre1[1]=n;next1[n]=1;
		int last=0,head=0;
		rep(i,1,n){
			if(gcd(a[i],a[next1[i]])==1){
				if(!last){
					head=i;
				}else{
					pre2[i]=last;
					next2[last]=i;
				}
				last=i;
			}
		}
		pre2[head]=last;
		next2[last]=head;
		if(!head){
			printf("0\n");continue; 
		}
		int tmp=head;
		while(tmp){
			ret++,ans.pb(next1[tmp]);
			if(next1[tmp]==tmp)break;
			if(next2[tmp]==next1[tmp]){Delete2(next2[tmp]);}
			Delete(next1[tmp]);
			if(next2[tmp]){
				if(gcd(a[tmp],a[next1[tmp]])!=1){
					ll t=next2[tmp];
					Delete2(tmp);
					if(tmp==t)break;
					tmp=t;
				}else{
					tmp=(next2[tmp])?next2[tmp]:tmp;
				}
			}else break;
		}
		cout<<ret<<' ';
		for(vit it=ans.begin();it!=ans.end();it++){
			cout<<*it<<' ';
		}
		cout<<'\n';
	}
	return 0;
}
```


---

## 作者：tiger2005 (赞：3)

## 题意：

假设有一个歌曲列表，每个歌曲有一个流派 $a_i$。开启循环播放进行聆听，在听到的歌曲和上一首歌曲流派的 $\gcd$ 为 1 的时候，删除掉现在听到的歌曲（后一首），然后忘掉之前听过的歌，把下一首歌当作第一首歌继续听（遗忘就是下一首歌不计算 $\gcd$ 的条件）。询问被删掉的歌以及删掉的顺序。

## 解法：

这道题看到循环，首先可以想到维护删除过程中每一个人的下一个数字。通过这种方式，我们可以得到一首歌的下一首是哪首。我们可以使用并查集，为了不受路径压缩的影响，我们存下一首歌右边第一个没被删除的歌 **左边一个数**，这样在路径压缩的时候就可以保证正确性。当然，也可以使用单端链表的方法，本质相同。

然后维护一个队列，表示当前相邻两个 $\gcd$ 为 1 的数对。每次从队头取出一个，首先判断两个数字都没有被删除，然后我们就可以将数对中后一首歌删掉，将前一个的父亲指向后一个的父亲，然后再次计算 $\gcd$ ，如果还是 1，那么仍然丢到队尾。注：如果没有 遗忘 的条件，需要维护双端队列并且把这个数对放到队头。

最后记录下被删除的位置并且输出即可。时间复杂度 $O(n\log(a_i))$（实际为线性做法）。

```cpp
// Problem      : B. Playlist
// From         : Codeforces - Codeforces Round #709 (Div. 1, based on Technocup 2021 Final Round)
// URL          : https://codeforces.com/contest/1483/problem/B
// Memory Limit : 256 MB
// Time Limit   : 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
int T,N,A[100010],fa[100010];
inline int nxt(int x){
	return x%N+1;
}
int getF(int x){
	return x==fa[x]?x:fa[x]=getF(fa[x]);
}
int gcdd(int a,int b){
	return !b?a:gcdd(b,a%b);
}
queue<int> q;
bool del[100010];
vector<int> ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&N);
		for(int i=1;i<=N;i++)	scanf("%d",&A[i]),fa[i]=i,del[i]=false;
		for(int i=1;i<=N;i++)
			if(gcdd(A[i],A[nxt(i)])==1)
				q.push(i);
		while(!q.empty()){
			int x=q.front();q.pop();
			if(del[x])	continue;
			int y=nxt(getF(x));
			fa[x]=getF(y);del[y]=true;
			ans.push_back(y);
			if((int)ans.size()==N)	break;
			if(gcdd(A[x],A[nxt(fa[x])])==1)	q.push(x);
		}
		while(!q.empty())	q.pop();
		printf("%d ",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
			printf("%d ",ans[i]);
		printf("\n");ans.clear();
	}
	return 0;
}

```

---

## 作者：xuezhe (赞：3)

考虑用个 set 维护剩下的数按顺序排列的样子，再用个 set 维护满足 $\gcd(a_i,a_{(i \bmod n)+1})=1$ 的 $i$。

然后直接每次在后一个 set 中取出下一个会被删除的数，看一下前后的 $\gcd$ 是否为 $1$，维护一下就好了。

由于最多也只会删 $n$ 个数，时间复杂度 $O(n \log n)$。

```cpp
const int N(100005);
int T,n,a[N];
set<pii> b;
set<int> st;
vector<int> d;
int get(int t){
    set<int>::iterator it=st.upper_bound(t);
    return *(it==st.end()?st.begin():it);
}
int nxt(int t){
    set<pii>::iterator it=b.lower_bound(pii(t,0x7fffffff));
    return (it==b.end()?b.begin():it)->first;
}

void fakemain(){
    Read(T);
    while(T--){
        b.clear();
        st.clear();
        d.clear();
        Read(n);
        for(int i=0;i<n;++i){
            Read(a[i]);
            b.insert(pii(i,a[i]));
        }
        for(int i=0;i<n;++i)
            if(__gcd(a[i],a[(i+1)%n])==1)
                st.insert(i);
        int lst=-1;
        while(b.size() && st.size()){
            int x=get(lst);
            int y=nxt(x);
            int z=nxt(y);
            st.erase(x);
            if(st.count(y))
                st.erase(y);
            if(__gcd(a[x],a[z])==1)
                st.insert(x);
            d.push_back(y+1);
            b.erase(pii(y,a[y]));
            lst=y;
        }
        printf("%d",int(d.size()));
        for(int i:d)
            printf(" %d",i);
        putchar(10);
    }
}
```

---

## 作者：Dregen_Yor (赞：1)

### [更好的阅读体验](https://dregen-yor.eu.org/2022/11/21/cf1483b/)。

# 思路

我们考虑朴素的枚举做法，用一个链表暴力模拟，并判断当前的歌和上一首歌的风格的 GCD 是否为 $1$ 即可，一直到一轮下来没有任意一首歌被删除为止。

但这样做的话很显然会超时，我们发现有些歌在上面暴力枚举的时候被重复计算了多次，但有些歌被重复计算多次，我们考虑如何将重复的计算优化掉。

我们不难发现，判断歌曲风格的关系是按一定顺序的，而且这个顺序与队列的 First  in First out 的关系是相同的，我们考虑用一个队列进行维护，记录所有需要判断关系的歌曲的编号，这样在计算 GCD 时只需要计算队列中的，可以省去所有重复的计算。最后按队列模拟时删除的顺序输出即可。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,T,sum,maxn;
bool v[100010];
struct node{
    int a;
    int l,r;
}a[100010];
struct nod{
    int x,y;
};
vector <int>ans;
signed main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i].a);
            v[i]=0;
        }
        ans.clear();
        queue<nod>q;
        for(int i=1;i<n;i++){
            q.push(nod{i,i+1});
            a[i].l=i-1;
            a[i].r=i+1;
        }
        a[1].l=n;
        a[n].l=n-1;
        a[n].r=1;
        q.push(nod{n,1});
        sum=0;
        while(!q.empty()){
            int x=q.front().x,y=q.front().y;
            q.pop();
            if(v[x]){
                continue;
            }
            if(__gcd(a[x].a,a[y].a)==1){
                v[y]=1;
                int p=a[y].r;
                a[p].l=x,a[x].r=p;
                q.push(nod{x,p});
                ans.push_back(y);
            }
        }
        printf("%d ",(int)ans.size());
        for(int i=0;i<ans.size();i++){
            printf("%d ",ans[i]);
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：__galaxy_1202__ (赞：0)

**此题涉及知识：单向循环链表、队列。**  
## 解题思路：
对于这道题，首先能想到的就是建立一个单向循环链表，重复枚举每个点，当这个点的值与下一个点的值互质时删除下一个点。直到一轮后没进行任何操作后停止。

但很可惜，这个方法由于 $n \le 10^5$，并不能通过此题。  

那么怎么优化呢？注意到在有些情况，一对组合要被算很多次，而明显这些第二个数没被删除的组合是不互质的，**那我们为什么要算这些组合呢？**。

根据这个思路，我们可以发现以下规律：

- 当一对组合不互质的时候，这对组合就**没必要验证了**，无论如何都不互质。
- 如果这对组合互质的话，**那它的第二个值就会变成第二个值后面的那个值**，产生一个新的组合。

知道了这个方法后，我们就可以**用队列来维护组合**：定义一个含有两个值的队列，分别代表组合的第一个值和第二个值。把初始的 $n$ 对组合入队（也就是 $(1,2),(2,3)...(n - 1, n),(n, 1)$ 这些组合）。接着循环**直到队列为空**，每次验证这对组合的值**是否互质**，如果互质则**将新的组合入队**（见上文），**记录下原来组合的第二个点并把它删除**（用链表实现），而且别忘了**把这对组合弹出队列**。

**Tips**：
1. 记得多测清空。
2. 由于第二个数被删除，所以要标记一下，以它开头的组合要跳过。
3. 答案为了节省空间可以用 `vector`，记得 `clear()`。

## CODE：

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
int t, n, a, vis[100001], val[100001], r[100001];
vector <int> x;
queue < pair <int, int> > Q;
int main()
{
    cin >> t;
    while (t--)
    {
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> a;
            val[i] = a;
            r[i] = i + 1;
            if (i != n) Q.push({i, i + 1});
        }
        r[n] = 1;
        Q.push({n, 1});
        while (!(Q.empty()))
        {
            int ai = Q.front().first, bi = Q.front().second;
            Q.pop();
            if (vis[ai]) continue;
            if (__gcd(val[ai], val[bi]) == 1)
            {
                vis[bi] = 1;
                r[ai] = r[bi];
                Q.push({ai, r[ai]});
                x.push_back(bi);
            }
        }
        cout << x.size();
        for (auto it : x) cout << ' ' << it;
        cout << '\n';
        memset(vis, 0, sizeof(val));
        memset(val, 0, sizeof(vis));
        memset(r, 0, sizeof(r));
        x.clear();
    }
    return 0;
}
```

---

## 作者：tmp_get_zip_diff (赞：0)

思路：

一个元素，如果它的下一个元素和它的 $\gcd = 1$，那么我们把这个元素叫做关键元素

随着删除的过程，关键元素可能会变成非关键元素，但是非关键元素一定不会变成关键元素

我们维护一个关键元素的集合，每次通过 $upper_bound$ 找到下一个关键元素即可

每次删除元素后，可能要将相关的元素从关键元素集合中删除

>代码中有些奇怪的东西（链表指针），开始做暴力用的

```
#include <bits/stdc++.h>
using namespace std;

#define int long long

int xbound(const set<int> &s, int x)
{
    auto tmp = s.upper_bound(x);
    if (tmp == s.end())
        return *s.begin();
    return *tmp;
}

void solve()
{
    struct Node
    {
        int val;
        int id;
        Node *next;
    };
    int n;
    cin >> n;
    vector<Node> nodes(n + 2);
    for (int i = 1; i <= n; i++)
        cin >> nodes[i].val, nodes[i].id = i;
    for (int i = 1; i < n; i++)
        nodes[i].next = &nodes[i + 1];
    nodes[n].next = &nodes[1];

    int cnt = 0;
    vector<int> ans;
    int siz = n;

    set<int> s;

    for (int i = 1; i < n; i++)
        if (__gcd(nodes[i].val, nodes[i + 1].val) == 1)
            s.insert(i);
    if (__gcd(nodes[n].val, nodes[1].val) == 1)
        s.insert(n);

    if (s.size())
    {
        Node *p = &nodes[xbound(s, 0)];
        Node *q = p->next;
        int cnt = 0;
        while (siz >= 1 && cnt <= n)
        {
            if (__gcd(p->val, q->val) == 1)
            {
                p->next = q->next;
                ans.push_back(q->id);
                siz--;
                if (s.find(q->id) != s.end())
                    s.erase(q->id);
                if (s.size() == 0)
                    break;
                p = &nodes[xbound(s, p->id)];
                q = p->next;
                cnt = 0;
            }
            else
            {
                s.erase(p->id);
                p = p->next;
                q = q->next;
                cnt++;
            }
        }
    }

    cout << ans.size() << " ";
    for (auto i : ans)
        cout << i << " ";
    cout << endl;
}

signed main()
{
    ios::sync_with_stdio(false); //优化
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
}
```

-----------

希望看懂！

---

