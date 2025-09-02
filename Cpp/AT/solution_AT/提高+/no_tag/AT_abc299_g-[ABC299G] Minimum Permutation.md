# [ABC299G] Minimum Permutation

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc299/tasks/abc299_g

$ 1 $ 以上 $ M $ 以下の整数からなる長さ $ N $ の数列 $ A $ があります。ここで、$ 1 $ 以上 $ M $ 以下のどの整数も $ A $ に $ 1 $ 回以上登場します。

$ A $ の長さ $ M $ の（連続とは限らない）部分列であって $ 1,\ \ldots,\ M $ が $ 1 $ 回ずつ登場するもののうち、辞書順最小のものを答えてください。

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i\ \leq\ M $
- $ 1 $ 以上 $ M $ 以下のどの整数も $ A $ に $ 1 $ 回以上登場する。
- 入力中の値はすべて整数である。
 
### Sample Explanation 1

$ A $ の長さ $ 3 $ の部分列であって $ 1,\ 2,\ 3 $ が $ 1 $ 回ずつ登場するものは $ (2,\ 3,\ 1) $ と $ (2,\ 1,\ 3) $ であり、このうち辞書順で小さいのは $ (2,\ 1,\ 3) $ です。

## 样例 #1

### 输入

```
4 3
2 3 1 3```

### 输出

```
2 1 3```

## 样例 #2

### 输入

```
4 4
2 3 1 4```

### 输出

```
2 3 1 4```

## 样例 #3

### 输入

```
20 10
6 3 8 5 8 10 9 3 6 1 8 3 3 7 4 7 2 7 8 5```

### 输出

```
3 5 8 10 9 6 1 4 2 7```

# 题解

## 作者：cannotdp (赞：9)

## 题目大意

给定一个长度为 $N$ 的序列 $A$，由 $1$ 到 $M$ 之间的整数组成。其中，$1$ 到 $M$ 每个整数都至少在 $A$ 中出现一次。

在满足 $1$ 到 $M$ 每个整数恰好在子序列中出现一次的条件下，找到字典序最小的长度为 $M$ 的子序列。

## 题目分析

很容易发现一个性质，**如果当前数字大于后一位的数字并且当前数字在后面重复出现过，那么选择当前数字一定不是最优的**。

举个简单的例子，在序列 $1,3,2,3$ 中，最优解显然是 $1,2,3$，而第一个出现的 $3$ 就不能选择。

有个这个性质就很好想了，直接记录每个数字最后一次出现的位置，并维护一个单调栈即可解决问题。

```
#include <bits/stdc++.h>
#define ll long long
#define PII pair<int,int>
using namespace std;

const int N=2e5+10,M=1e4+10,O=1e3+10,mod=1e9+7,INF=0x3f3f3f3f;
int n,m,t,q,cnt,num,tot;
int a[N],last[N],v[N];
stack<int>s;
vector<int>ans;

signed main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),last[a[i]]=i;//记录每个数字最后一次出现的位置 
	for(int i=1;i<=n;i++) {
		if(v[a[i]]) continue;//如果已经在栈里了就直接跳过 
		while(s.size()&&s.top()>a[i]&&last[s.top()]>i) {
			//同时满足三个条件：1.栈不为空 2.栈顶大于a[i] 3.栈顶元素后面还有出现 
			v[s.top()]=0;
			s.pop();//弹出 
		}
		s.push(a[i]);
		v[a[i]]=1;//标记 
	}
	while(s.size()) {
		ans.push_back(s.top());
		s.pop();
	}
	for(int i=ans.size()-1;~i;i--) printf("%d ",ans[i]);//倒序输出答案 
	return 0;
}

```


---

## 作者：Luciylove (赞：3)

给出一个很自然的想法。

考虑贪心按位选最小的数填下去，然后我们去找这一个位可以填下去的充要条件。

考虑记剩下没填的元素 $x$ 的最后一次出现的位置为 $lst_x$。


那么就是选出的位置 $p_x$ 要大于等于最小的 $lst_y$。考虑按照 $lst_y$ 从小到大取即可填完。

不妨记记这个 $lst_y$ 为 $r_p$，这个不难发现，结合上一个数的位置 $l_p$，那么我们选出的数在序列上出现的区间为 $[l_p + 1, r_p]$，我们对这些数取最小的填，使用线段树维护即可。每次注意删去取出的数，然后 $r_p$ 可以使用 set 维护。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define lc x << 1 
#define rc x << 1 | 1

using namespace std;

const int _ = 4e5 + 5;

int n, m, lp;
int a[_], tr[_ << 2];
int seq[_];
int lst[_];
vector <int> ocr[_];

/*每次维护区间 min 就行乐？不用二分，支持删一个数查询最小值。*/

void build (int x, int l, int r) {
	if (l == r) return tr[x] = a[l], void();
	int mid = (l + r) >> 1;
	build(lc, l, mid), build(rc, mid + 1, r);
	tr[x] = min(tr[lc], tr[rc]);
}
int query (int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return tr[x];
	int mid = (l + r) >> 1, ans = 0x3f3f3f3f;
	if (ql <= mid) ans = query(lc, l, mid, ql, qr);
	if (qr > mid) ans = min(ans, query(rc, mid + 1, r, ql, qr));
	return ans;
}
void modify (int x, int l, int r, int v, int k) {
	if (l == r) return tr[x] = k, void();
	int mid = (l + r) >> 1;
	if (v <= mid) modify(lc, l, mid, v, k);
	else modify(rc, mid + 1, r, v, k);
	tr[x] = min(tr[lc], tr[rc]);
}
set <int> st;

int main () {
	cin >> n >> m;
	rep(i, 1, n) scanf("%d", & a[i]), lst[a[i]] = i, ocr[a[i]].push_back(i);
	build(1, 1, n);
	rep(i, 1, m) st.insert(lst[i]);
	lp = 1;
	rep(i, 1, m) {
		int p = *st.begin();
		int x = query(1, 1, n, lp, p);
		seq[i] = x;
		int flag = 1;
		for (int v : ocr[x]) {
			if (v >= lp && flag) lp = v, flag = 0;
			modify(1, 1, n, v, 0x3f3f3f3f);
		}
		st.erase(lst[x]);
	}
	rep(i, 1, m) printf("%d ", seq[i]);
	return 0;
}
```


---

## 作者：B612Dusk (赞：2)

# 思路

首先我们要明白这道题让我们**求什么**，很明显是一个包含了所有数的**字典序最小**的子序列，那么字典序最小就意味着越靠前面的越小肯定越好，同时也要记录下这个序列是什么，考虑使用**单调栈**进行维护。

# 实现

我们发现我们做这道题的矛盾点在哪，就是在不敢乱出栈，因为可能后面就没有这个数了，怎么办？

很明显，缺啥补啥，开一个 $lst_i$ 表示数字 $i$ 最后一次出现的位置是 $lst_i$。

然后我们就开始往后扫，每次扫到一个数，首先按照单调栈，如果他是一个小的数，那么肯定越往前插越好， 同时又需要考虑我们扔掉的数后面会不会再出现，如果说我们比较的是队伍中的第 $j$ 位与 序列的第 $i$ 个数， 那我们需要做的就是比较 $a_i$ 是否小于 $q_j$ ，这里 $q_j$ 不是说 $q$ 是数组， 而是表示 $q$ 的第 $j$ 位。

那么我们在连续弹栈的判断条件很容易得出就是
```c++
while(!sta.empty() && sta.top() > a[i] && lst[sta.top()] > i)	
	vis[sta.top()] = 0, sta.pop();
```

那么这道题...其实就迎刃而解了。

## Code 

```c++
#include<bits/stdc++.h>
#define N 200010
int o = N;
#define reg register
using namespace std;
//char in[1 << 20] ,*ss = in,*tt = in;
//#define getchar() (tt == ss && (tt = (ss = in) + fread(in, 1, 1 << 20,stdin),ss == tt) ? EOF : *ss++)
inline int read(){
	int x = 0, f = 1;  char ch = getchar();
	while(ch > '9' || ch < '0'){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9'){
		x = (x << 3) + (x << 1) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
stack<int>	sta;
map<int, int>	lst, vis;
int n ,m, cnt;
int a[N], ans[N];
signed main(){
	n = read(), m = read();
	for(reg int i = 1;i <= n;i = -~i) a[i] = read(), lst[a[i]] = i;
	for(reg int i = 1;i <= n;i = -~i) {
		if(vis[a[i]])	continue;
		while(!sta.empty() && sta.top() > a[i] && lst[sta.top()] > i)	vis[sta.top()] = 0, sta.pop();
		sta.push(a[i]);
		vis[a[i]] = 1;
	}
	while(!sta.empty())	{
		int h = sta.top();
		ans[++ cnt] = h;
		sta.pop();
	}
	for(reg int i = cnt;i >= 1;-- i)	printf("%d ", ans[i]);	
    return o;
```

---

## 作者：heaksicn (赞：2)

## 1 description

给定一个长度为 $n$ 并且每个数不超过 $m$ 的序列 $a$，找出所有子序列满足其长度为 $m$ 并且是一个排列中字典序最小的。

$n,m\leq 2\times 10^5$。

## 2 solution

由于需要保证字典序最小，所以我们一位一位地考虑。

假设我们当前已经选了 $i-1$ 个数，现在选的第 $i$ 个数位于 $j$，那么当前的选法是合法的当且仅当剩下的 $m-i$ 个数在 $[j+1,n]$ 中均有出现。

在所有合法的情况中我们应该选择数字最小且排位尽量靠前的数。

分别用两棵线段树维护当前剩下的数最后出现的位置和可选区间中最小且最靠前的数即可。

时间复杂度 $O((m+n)\log n)$。

### 3 code

```
//Man always remember love because of romance only!
#include<bits/stdc++.h>
using namespace std;
#define pa pair<int,int>
#define mp make_pair
#define fi first
#define se second
inline int read(){
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x){
	if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int tr1[800001];
int lst[200001],a[200001];
int n,m;
void pushup1(int x){
	tr1[x]=min(tr1[x<<1],tr1[x<<1|1]);
}
void build1(int x,int l,int r){
	if(l==r){
		tr1[x]=lst[l];
		return;
	}
	int mid=(l+r)/2;
	build1(x<<1,l,mid);
	build1(x<<1|1,mid+1,r);
	pushup1(x);
}
void update1(int x,int l,int r,int tp){
	if(l==tp&&r==tp){
		tr1[x]=1e9;
		return;
	}
	int mid=(l+r)/2;
	if(mid>=tp) update1(x<<1,l,mid,tp);
	else update1(x<<1|1,mid+1,r,tp);
	pushup1(x);
}

int tr[800001][2];
void pushup(int x){
	tr[x][0]=min(tr[x<<1][0],tr[x<<1|1][0]);
	if(tr[x<<1][0]<tr[x<<1|1][0]) tr[x][1]=tr[x<<1][1];
	else if(tr[x<<1][0]==tr[x<<1|1][0]) tr[x][1]=min(tr[x<<1][1],tr[x<<1|1][1]);
	else tr[x][1]=tr[x<<1|1][1];
}
void build(int x,int l,int r){
	if(l==r){
		tr[x][0]=a[l];
		tr[x][1]=l;
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int l,int r,int tp){
	if(l==tp&&r==tp){
		tr[x][0]=1e9;
		return;
	}
	int mid=(l+r)/2;
	if(mid>=tp) update(x<<1,l,mid,tp);
	else update(x<<1|1,mid+1,r,tp);
	pushup(x);
}
pa query(int x,int l,int r,int nl,int nr){
	if(nl<=l&&nr>=r) return mp(tr[x][0],tr[x][1]);
	int mid=(l+r)/2;
	int res=1e9,ress;
	if(mid>=nl){
		pa tp=query(x<<1,l,mid,nl,nr);
		if(res>tp.fi){
			res=tp.fi;
			ress=tp.se;
		}
	}
	if(mid<nr){
		pa tp=query(x<<1|1,mid+1,r,nl,nr);
		if(res>tp.fi){
			res=tp.fi;
			ress=tp.se;
		}
	}
	return mp(res,ress);
}
int ans[200001];
vector<int> v[200001];
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		lst[a[i]]=i;//最后一次出现的位置
		v[a[i]].push_back(i);
	}
	build(1,1,n);
	build1(1,1,m);
	int l=1;
	for(int i=1;i<=m;i++){
		int r=tr1[1];//剩下数中最后一次出现的位置
//		cout<<l<<" "<<r<<endl;
		pa now=query(1,1,n,l,r);//最小且最靠前
		l=now.se+1;//更新左端点
		update1(1,1,m,now.fi);//去掉当前选择的数
		ans[i]=now.fi;//记录答案
		for(int j=0;j<v[now.fi].size();j++){
			int sb=v[now.fi][j];
			update(1,1,n,sb);//去掉当前选择的数
		}
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<" ";
	return 0;
}

```


---

## 作者：解方橙 (赞：1)

这道题的标算竟然是 $\operatorname{O(nlogn)}$ 的！！？

那就来个 $\operatorname{O(n)}$ 的做法。

考虑贪心。遍历 $a$ 数组，维护一个队列 $q$ 表示答案的序列，遍历到一个元素的时候尝试替换掉队列里比它小的元素。什么时候不能替换成功或更劣呢？要么当前元素比它小，要么当前元素再替换就加不回来了。因此我们对于每个元素记录出现但未遍历到的次数 $cnt$，如果想要被替换的元素大于当前元素 $cnt>0$ ，则放心替换（因为以后还能加回来，因此这么换一定是更优的）。最后替换掉所有能替换的元素后就把它加入队列。

时间复杂度 $\operatorname{O(n)}$ 。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[200010],cnt[200010];
int q[200010],t;
bool vis[200010];
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        cnt[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(vis[a[i]]){
            cnt[a[i]]--;
            continue;
        }
        if(a[i]>q[t]) q[++t]=a[i],vis[a[i]]=true,cnt[a[i]]--;
        else{
            while(t){
                if(!cnt[q[t]]){
                    q[++t]=a[i];vis[a[i]]=true;cnt[a[i]]--;
                    break;
                }
                if(q[t]<a[i]){
                    q[++t]=a[i];
                    vis[a[i]]=true;
                    cnt[a[i]]--;
                    break;
                }
                vis[q[t]]=false;t--;
            }
            if(!t){
                q[++t]=a[i];
                vis[a[i]]=true;
                cnt[a[i]]--;
            }
        }
    }
    for(int i=1;i<=m;i++) printf("%d ",q[i]);printf("\n");
}

```

---

## 作者：3580_YY (赞：0)

### 算法分析
贪心。

遍历数组，用一个栈（或双端队列）来按顺序保存需要保留的数字。如果栈顶元素比当前遍历到的元素 $a_i$ 大，并且栈顶元素在 $(i,n)$ 还会出现，就弹出栈顶，不选它。因此预处理出每个数字最后出现的位置，然后遍历一遍数组，用栈来维护需要保留的元素即可。

### 复杂度分析
遍历了一遍数组，每个元素最多经历一次压栈一次弹栈，因此时间复杂度为 $O(n)$。



---

## 作者：Butterfly___qwq (赞：0)

# 题目简述
给出一个序列，序列中的每个数字不超过这个序列的长度大小，而且都是正整数，要求从中找出字典序最小的由 $1$ 到 $n$ 中所有数字组成的序列。
# 思路
这道题有点像最长上升子序列之类的问题，于是我们考虑单调栈。我们先用两个数组来维护这个序列的信息，其中 $vis$ 数组的意思是表明这个数是否被访问，$cnt$ 数组的意思是一个数字出现的次数。我们先拿一个简单的序列实验一下，如 `2 1 2 ` 这个序列，下面给出过程。
## 实验
- 把 $2$ 压入栈，标记被访问，目前答案栈中的数字只有 $2$，数量减一。
- 再把 $1$ 压入栈，数量加一，标记访问，然后遍历，发现仍然有数字比他大的还在，于是把第一个数字先弹出再压入。
- 把最后一个数字压入，于是找到了字典序最小序列。

现在可以总结出一套方法了，具体看一下代码。
# 代码
```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <bitset>
#include <stack>
using namespace std;
const int M=114514;
bool vis[2*M];
int ans[2*M];
int cnt[2*M];
int a[2*M];
stack <int> st;
int main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		cnt[a[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(!vis[a[i]]){
			while(!st.empty()&&cnt[st.top()]&&st.top()>a[i]){
				vis[st.top()]=0;
				st.pop();
			}
			st.push(a[i]);
			vis[a[i]]=1;
		}
		cnt[a[i]]--;
	}
	int l=st.size();
	for(int i=1;i<=l;i++){
		ans[l-i+1]=st.top();
		st.pop();
	}
	for(int i=1;i<=l;i++){
		cout<<ans[i]<<" ";
	}
	return 0;
}
```

---

## 作者：Kylin_ZHH (赞：0)

这个题赛时没做出来（~~怎么可能做出来，最多也就到E~~）

从左到右依次考虑数组 $a$，对于当前的数字 $a_i$，一个朴素的想法是，选不选它，如果不选它，剩下的序列还能不能组成一个排列，如果不能，则一定要选它，那问题就剩下如何判断能不能组成，以及如果不一定选择，该怎么办。

能不能组成一个排列，就是看剩下序列的数字包不包含还没选择的数，设还没选择的数为 $left$。

然后对于不是一定要选的数，我们可以先存起来，这样就有一个由满足要求的$a_i$ 组成的候选集合。

继续往右遍历，会遇到第一个不满足要求的位置 $a_r$，此时可以从候选集合里选数字最小的数，放到答案里，此时 $left$ 就少了一个数。

因为(left)是判断某个数是不是一定要选的条件，当 $left$ 少 $1$ 时，说明这个条件变得更容易满足，因此 $a_r$ 可能会满足，因此可以继续往右边遍历，往候选集合里添加新的数。而之前满足要求的还是满足。

由此就循环就可以得到最终答案了。

看个代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main(void) {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> cnt(m + 1);
    int ok = 0;
    auto add = [&](int x, int val){
        if (cnt[x] == 0)
            ok ++;
        cnt[x] += val;
    };
    auto sub = [&](int x, int val){
        cnt[x] -= val;
        if (cnt[x] == 0)
            ok --;
    };
    for(auto &i : a){
        cin >> i;
        add(i, 1);
    }
    vector<int> ans;
    vector<int> used(m + 1, 0);
    priority_queue<array<int, 2>> candidate;
    int target = m;
    int l = -1;
    for(int i = 0; i < n; ++ i){
        if (used[a[i]])
            continue;
        if (ok != target){
            while(-candidate.top()[1] < l || used[-candidate.top()[0]])
                candidate.pop();
            int val = -candidate.top()[0];
            int pos = -candidate.top()[1];
            ans.push_back(val);
            used[val] = 1;
            l = pos;
            if (cnt[val])
                sub(val, cnt[val]);
            candidate.pop();
            -- i;
            -- target;
            continue;
        }
        sub(a[i], 1);
        candidate.push({-a[i], -i});
    }
    while(ans.size() < m){
        int val = -candidate.top()[0];
        int pos = -candidate.top()[1];
        candidate.pop();
        if (pos < l || used[val])
            continue;
        ans.push_back(val);
        used[val] = 1;
        l = pos;
    }
    for(int i = 0; i < m; ++ i){
        cout << ans[i] << ' ';
    }
    cout << 'n';

    return 0;
}

```

禁止复制，撒花

---

## 作者：2huk (赞：0)

## 题目描述

有一个长 $N$ 的序列，保证其中包含 $1 \sim M$，请你找到一个长 $M$ 的子序列，使得其中每个数字都出现了一次，并使得排列的字典序最小。

## 分析

由于题目保证一定出现过 $1 \sim M$，所以我们放心的考虑贪心策略即可。

我们以一个栈来存储最终答案。由于输出时需要用到栈中间的元素，所以我们手写一个栈。定义 $s_i$ 表示栈中的第 $i$ 个元素，$tt$ 表示当前栈顶元素在栈中的位置。

假设我们已经处理好了前 $i-1$ 个元素的顺序，但是它不一定是最终的最优答案，但一定是当前的最优答案。那么，如果来了一个新元素 $a_i$，我们该如何处理这个元素呢？

如果 $a_i$ 在当前的栈中已经出现过，不做考虑，退出当前轮的抉择。

下面的讨论都建立在 $a_i$ 不在当前栈中的基础上。

如果 $a_i > s_{tt}$，也就是 $a_i$ 比当前的栈顶元素要大，那么显然要将 $a_i$ 插入栈顶。因为题目要求排列的字典序最小，所以越大的元素就要越往后放，所以把当前的更大的元素放到后面。

否则，如果 $a_i < s_{tt}$，那么此时放入不一定是当前最优解，所以还要分情况讨论。

如果当前的栈顶元素在后面有过出现，那么此时可以放心的把栈顶元素删掉，并把 $a_i$ 插入栈中。同理，如果删掉之后仍然满足这个条件，可以循环删除。

反之，如果当前的栈顶元素在后面没有出现，那么也就不存在更优的解法，直接放入栈中即可。

## 代码

```cpp
#include <iostream>

using namespace std;

const int N = 2e5 + 10;

int n, m, a[N], s[N], tt, d[N];		// s 表示栈，tt 表示当前栈顶的位置，d[i] 表示 i 数字出现的次数 
bool st[N];		// st[i] 表示 i 数字是否在当前的栈中 

int main()
{
	// 读入 
	cin >> n >> m;
	
	for (int i = 1; i <= n; i ++ )
	{
		cin >> a[i];
		d[a[i]] ++ ;		// a[i] 出现的次数多 1 
	}
	
	for (int i = 1; i <= n; i ++ )
	{
		d[a[i]] -- ;		// 这个数字出现过了一次 
		if (st[a[i]]) continue;		// 如果这个数字在当前的栈中，不做处理 
		while (s[tt] > a[i] && d[s[tt]]) st[s[tt]] = 0, tt -- ;	
		// 如果当前的栈顶元素在后面有过出现，那么此时可以放心的把栈顶元素删掉，并把 a[i] 插入栈中
		
		s[ ++ tt] = a[i];
		st[a[i]] = 1;
	}
	
	for (int i = 1; i <= m; i ++ ) cout << s[i] << ' ';			// 输出栈中元素 
	
	return 0;
}
```


---

## 作者：DaydreamWarrior (赞：0)

[至少是阅读体验](https://rainlycoris.github.io/#/post/24)

## 分析

维护一个栈，每次加入一个值。

如果栈顶在之后也会出现并且比加入的值大就弹出。

这样使得每个值尽可能放在前面。

粗略的证明一下。假设有两个序列 $A,B$，$A$ 的字典序小于 $B$，且 $A$ 是字典序最小的。

$A$ 的第一个与 $B$ 不同的位置为 $x$，$A_x$ 在 $B$ 中出现的位置 $y$ 一定在 $x$ 之后。

$B_y$ 能移动到 $x$，在处理 $B$ 的时候 $B_y$ 会被移动到 $x$，所以不会找到 $B$ 序列。

那么找到的序列是字典序最小的。

不过一个排列的置换字典序最小不一定代表这个排列的字典序最小。

## 代码
```cpp
const int N = 200005;
int a[N],pos[N];
int stk[N],top;
bool b[N];
int n,m;

int main(){
    cin >> n >> m;
    for(int k=1;k<=n;k++){
        cin >> a[k];
        pos[a[k]] = k;
    }
    for(int k=1;k<=n;k++){
        if(b[a[k]])
            continue;
        while(top&&stk[top]>a[k]&&pos[stk[top]]>k){
            b[stk[top]] = false;
            top--;
        }
        stk[++top] = a[k];
        b[a[k]] = true;
    }
    for(int k=1;k<=m;k++)
        cout << stk[k] << " ";
    return 0;
}
```

---

## 作者：ケロシ (赞：0)

# 题意
给出一个长度为 $n$ 且每个数都在 $1$ 到 $m$ 的序列 $A$。   
$1$ 到 $m$ 中的每一个数保证在序列 $n$ 中出现过。  
要求找出一个 $A$ 子序列，保证 $1$ 到 $m$ 都出现过一次，长度为 $m$，且字典序最小。
# 解题思路
首先需要保证序列中 $1$ 到 $m$ 中的数全部出现，记录每个数最后出现的位置，记作 $B$。   
那么就优先选择 $A_1$ 到 $A_{\min(B)}$ 的数就能保证所有数都出现。   
那么字典序最小就需要选最小的数，直接开两个集合。   
第一个记录未选的数中最后出现的位置，在这些位置最小值前可以选数。   
第二个记录可以选的数，数作为第一关键字，位置作为第二关键字。   
选定一个数后这个数之前的数都不能选，需要在第二个集合中删除。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int n, m, a[N], b[N], vis[N];
set<int> st1;
set<pair<int, int> > st2; 
vector<int> ans;
void solve() {
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=n;i++) b[a[i]] = i; // 每个数最后出现的位置
    for(int i=1;i<=m;i++) st1.insert(b[i]); // 插入第一个集合
    int l = 1,r = 0;
    for(int i=1;i<=m;i++) {
        while(r < *st1.begin()) { // 可以选的数
            r++;
            st2.insert(make_pair(a[r], r));
        }
        while(1) {
            auto val = *st2.begin();
            st2.erase(st2.begin());
            if(vis[val.first]) continue; // 已经选过了
            vis[val.first] = 1;
            ans.push_back(val.first); // 记录答案
            st1.erase(b[val.first]); // 选过后删除
            while(l < val.second) { // 之前的都不能选了
                st2.erase(make_pair(a[l], l));
                l++;
            }
            break;
        }
    }
    // 输出答案
    for(auto i : ans) cout << i << " ";
    cout << endl;
}
int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
```

---

