# [ARC088E] Papple Sort

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc088/tasks/arc088_c

英小文字からなる文字列 $ S $ が与えられます。 隣り合う $ 2 $ つの文字を入れ替える操作を繰り返して $ S $ を回文にできるかどうか判定し、できる場合は操作の最小回数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ |S|\ \leq\ 2\ ×\ 10^5 $
- $ S $ は英小文字からなる

### Sample Explanation 1

以下の操作で、$ S $ を回文にすることができます。 - $ 2 $ 文字目と $ 3 $ 文字目を入れ替える。新しい $ S $ は `ele` となる。

### Sample Explanation 2

以下の操作で、$ S $ を回文にすることができます。 - $ 5 $ 文字目と $ 6 $ 文字目を入れ替える。新しい $ S $ は `ataamtma` となる。 - $ 4 $ 文字目と $ 5 $ 文字目を入れ替える。新しい $ S $ は `atamatma` となる。 - $ 3 $ 文字目と $ 4 $ 文字目を入れ替える。新しい $ S $ は `atmaatma` となる。 - $ 2 $ 文字目と $ 3 $ 文字目を入れ替える。新しい $ S $ は `amtaatma` となる。

### Sample Explanation 3

$ S $ を回文にすることはできません。

## 样例 #1

### 输入

```
eel```

### 输出

```
1```

## 样例 #2

### 输入

```
ataatmma```

### 输出

```
4```

## 样例 #3

### 输入

```
snuke```

### 输出

```
-1```

# 题解

## 作者：whiteqwq (赞：5)

[AT3733 [ARC088C] Papple Sort](https://www.luogu.com.cn/problem/AT3733)解题报告：

[更好的阅读体验](https://zybuluo.com/xiaoziyao/note/1759552)

## 题意
- 给定一个字符串$S$，可以进行若干次操作使得某两个相邻字母交换，求最少需要多少次操作让这个字符串成为回文串。
- $1\leqslant |S|\leqslant 2\times 10^5$。

## 分析
我们考虑每一个字符在最后的回文串里会与什么字符配对，发现**从前往后第$x$个字符$c$一定会与从后往前第$x$个字符$c$匹配**。（因为交叉式的匹配一定不优于或等价与包含式的匹配）

```
解释：
c...c...c...c
第一个c与第四个c匹配一定比第一个c与第三个c匹配等价或更优
```

而确定了匹配的对象之后，我们不难发现**对于两对匹配了的字符，不交换位置一定比交换位置优**。
```
解释：
假设匹配后是：c...b...b...c
如果交换成匹配b...c...c...b，也不会对其他的匹配有任何帮助，还不如不交换位置
```

这样我们就有了一个基本的思路：枚举每一个没有匹配过的字符，找到与它对应的字符，然后把这两个字符移动到最外侧的位置，这样就可以把这一对字符视为已删除。

考虑当前字符之前的所有字符已经进行过了操作，所以$i$一定在最外侧，我们只需要把与它匹配的字符移动到末尾，我们只需要用一个树状数组维护当前的字符就好了。

对于单独的字符，我们标记一个flg，然后在之后的操作的费用都增加$1$就好了（因为之后的匹配的左端点需要向左移动一次）。

## 代码
```
#include<stdio.h>
#include<iostream>
#include<vector>
#define lowbit(x) x&-x
using namespace std;
const int maxn=200005,maxk=30;
int all,flg,n,now;
long long ans;
int a[maxn],used[maxn],t[maxn];
string s;
vector<int>v[maxk];
void update(int x,int v){
	for(int i=x;i<=n;i+=lowbit(i))
		t[i]+=v;
}
int query(int x){
	int res=0;
	for(int i=x;i;i-=lowbit(i))
		res+=t[i];
	return res;
}
int main(){
	cin>>s;
	n=s.size();
	for(int i=0;i<s.size();i++){
		a[i+1]=s[i]-96;
		v[s[i]-96].push_back(i+1);
	}
	for(int i=1;i<=26;i++)
		if(v[i].size()&1)
			all++;
	if(all>1){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=n;i++)
		update(i,1),now++;
	for(int i=1;i<=n;i++){
		if(used[i])
			continue;
		int x=v[a[i]][v[a[i]].size()-1];
		if(x==i){
			v[a[i]].pop_back(),flg=1;
			used[i]=1,update(i,-1),now--;
			continue;
		}
		v[a[i]].pop_back();
		ans+=1ll*(now-query(x))+flg;
		used[i]=used[x]=1;
		update(i,-1),update(x,-1),now-=2;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：LawrenceSivan (赞：3)

# AT3733 [ARC088C] Papple Sort

> 给定一个只有小写字母的字符串 $S$，请问最少经过多少次相邻两字母的交换，使得字符串变成回文？
>
> 如果不可以输出  $-1$
>
> $n\le 2e5$

逆序对。

~~其实挺水的而且这个思路应该是最好想的为啥没人写啊~~

---

看到了两两交换，容易想到冒泡排序。

也就是逆序对问题。

于是我们可以把字符串重新标号，变成一个数字序列，之后直接统计逆序对即可。

一条比较显然的小性质是我们需要尽量的满足配对的情况发生在最外侧。

交叉配对显然不优。

于是对于多次出现的字母，我们要找到两个最外侧的进行配对。

配对的具体做法是给两个位置分别赋一个顺序值。

并且两个顺序值满足一个从前面往后，一个从后面往前。

举个例子：

`ataatmma`

根据规则，应当赋值：

`1 2 3 6 7 4 5 8`

问题转化为在不高于 $\mathcal{O(n \log n)}$ 时间内完成对字符串的重标号。

事实上 $\mathcal{O(n)}$ 即可完成。

只需要记录一下每个位置的字母是什么，每种字母都在哪些位置出现。

每次扫到一个字母，将出现位置中最早的和最晚的配对。

这里使用了 `std::deque` 实现。

复杂度 $\mathcal{O(n \log n)}$ ，主要在于树状数组求逆序对。

代码太丑了扔剪切板好了

[代码](https://gitee.com/lawrencesivan/code-clipboard/blob/master/AT3733%20%5BARC088C%5D%20Papple%20Sort%EF%BC%88%E9%80%86%E5%BA%8F%E5%AF%B9%EF%BC%8C%E5%9B%9E%E6%96%87%EF%BC%8C%E5%AD%97%E7%AC%A6%E4%B8%B2%EF%BC%89)

---

## 作者：AC_love (赞：1)

考虑同样的字母一定会保持初始的顺序。

对于每个字母，一定是第一个和最后一个匹配，第二个和倒数第二个匹配……以此类推，如果这个字母有奇数个，它和自己匹配，放到字符串的中央。

每次枚举一个最左侧的字符，把它对应的字符扔到最右侧删掉。暴力做复杂度 $O(n^2)$，可以用树状数组优化做到 $O(n \log n)$。

如果某个字符出现了奇数次，最后只剩它一个，该怎么办呢？我们只要打一个标记就好，此后出现的每个左端点都需要额外向左移动一格，统计答案时加一即可。

[code](https://atcoder.jp/contests/arc088/submissions/59546581)

---

## 作者：LIUYC_C (赞：1)

[题目链接](https://www.luogu.com.cn/problem/AT_arc088_c)。



## 解决思路：

提供一种不是从逆序对的角度思考的办法，但作用似乎和逆序对没两样？

我们先假定肯定可以构造出回文串。

同时的，我们还有交换相邻字符的操作，那我们可以考虑每一个位置对答案的贡献何时最小，既然要构成回文，那么前后的字符应当是一一对应的，即第 $i$ 个位置上的字符应与第 $n-i+1$ 位置上的字符相同，那么我们何不大力贪心，对于前  $n/2$ 位置上的字符，我们钦定第 $i$ 位置上的字符就是最终的字符，因此，我们只需要把离第 $n-i+1$ 位置最近的，同时还和第 $i$ 位置上字符相同的，那个位置移到第 $n-i+1$ 位置，它此时对答案的贡献就是它的位置和最终位置之间数的个数，因为我要交换这么多次嘛。

**考虑证明这个贪心**，首先因为是回文，我们一定要一一对应，那么我若是同时移动前 $n/2$ 位置上的数和后面的数，很明显对答案没有任何贡献，而我们只移动后面的数的话，可以让还没有被匹配的字符越靠向内部，刚好的，我们还没有匹配的数正好就是在内部的，所以肯定更优。

**ps：有更好的解释欢迎指出。**

如果暴力的话是玄学 $O(n^2)$，考虑优化，我们因为是钦定前 $n/2$ 个字符不动，那么我们只需要移动那个离第 $n-i+1$ 位置最近的，同时还和第 $i$ 位置上字符相同的字符，这个字符的位置我们可以用一个 $deque$ 找到，我们只要预处理出对于每个字符在哪些位置出现过，放进队列里，每次取 back，再 popback 就好了。

找到这个位置后，我们记这个位置为 $l$，我们考虑计算答案，那肯定是看 $[l,n]$ 这个区间还剩下几个数，因此我们可以用树状数组解决，每次计算完后，把 $l$ 这个位置更新为 0，表示这个位置已经没字符了。

然后就是判无解，分情况，总共有奇数个字符的话，可以出现一次不成对，否则必须成对，然后对于奇数个字符时，记得还要加上最后把那个剩下的字符放到中间的贡献。

## 代码实现：
代码永远比文字好懂。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=201010;
#define int long long
unordered_map<char,deque<int>> q,p;
string s;
int n;
int tr[N];

int lobit(int x){
    return x&-x;
}

void update(int x,int c){
    while(x<=n){
        tr[x]+=c;
        x+=lobit(x);
    }
    return;
}

int query(int x){
    int res=0;
    while(x){
        res+=tr[x];
        x-=lobit(x);
    }
    return res;
}

bool st[N];
signed main(){
    /*freopen("bigdate.in","r",stdin);
    freopen("second.out","w",stdout);*/
    ios::sync_with_stdio(false);
    cin>>s;
    n=s.size();
    s='>'+s;

    for(int i=1;i<=n;i++){
        update(i,1);
        q[s[i]].push_back(i);
        p[s[i]].push_back(i);
    }
    
    int ans=0;
    int f=0;
    int id=-1;
    for(int i=1;i<=n;i++){
        if(st[i]){
            continue;
        }
        st[i]=1;
        if(q[s[i]].size()==1&&f==1){
            cout<<-1<<endl;
            return 0;
        }
        if(q[s[i]].size()==1){
            f=1;
            id=q[s[i]].back();
            continue;
        }
        ans+=query(n)-query(q[s[i]].back());
        update(q[s[i]].back(),-1);
        st[q[s[i]].back()]=1;
        q[s[i]].pop_back();
        q[s[i]].pop_front();
    }
    
    if(id!=-1){ 
        for(int i=1;i<=n;i++)st[i]=0;
        st[id]=1;
        int tim=0;
        for(int i=1;i<=n;i++){
            if(st[i]){
                continue;
            }
            st[p[s[i]].back()]=1;
            if(p[s[i]].back()<id)tim++;
            p[s[i]].pop_back();
            p[s[i]].pop_front();
        }
        id=id-tim;
        ans+=(n+1)/2-id;
    }
    cout<<ans<<endl;

}
```


---

## 作者：chlchl (赞：1)

## 前言
这道题我整整在学校 OJ 上交了一页，全是 84 pts。要不是能看数据我还真不一定能调出来。

## 做法
本题其实是个逆序对。

要做这种题，一般套路是先找到目标状态，即步数最少的目标回文串。

首先，包含式配对会比交叉式配对步数更少。这是一个可以感性理解的结论：比如字符串 $abbababa$，最优的肯定是第一个 $a$ 跟最后一个 $a$ 匹配，中间的两个 $a$ 匹配。如果第一个 $a$ 跟第三个 $a$ 匹配，其实模拟一下就知道，第三个 $a$ 还要往后挪到第四个 $a$ 的位置，显然劣于前面一种匹配方式。

也就是说，我们要**从外往内**匹配。

其次是一个简单的构造方式：外层的匹配，肯定位于目标字符串的外层。这个也很显然，你总不能让两个在最中间的匹配串挪 $n$ 次到最外边，然后让最外边的挪 $n$ 次来到最中间吧？

然后我们将每个字符在目标字符串中的位置记录下来。显然，一次挪动会减少一个逆序对，而最后的逆序对个数显然为 $0$（$p_i=i$ 的情况），那次数就是逆序对个数。

本题代码细节有点多，具体可以看看下面的代码注释。

思维性的好题！

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N = 2e5 + 10;
char s[N];
int n, ans, tot, cnt[N], p[N];//p[i]:每个字符最终出现在哪个位置 
int sum[N];
deque<int> q[N];

void update(int i, int x){for(;i<=n;i+=i&-i)	sum[i] += x;}

int query(int i){
	int res = 0;
	for(;i;i-=i&-i)	res += sum[i];
	return res;
}//树状数组求逆序对，不会的可用归并排序 

main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	for(int i=1;i<=n;i++)	cnt[s[i] - 'a']++, q[s[i] - 'a'].push_back(i);//利用双向队列存下每个字符的出现位置 
	for(int i=0;i<26;i++)	if(cnt[i] & 1)	tot++;
	if(tot >= 2) return printf("-1\n"), 0;//奇数个数>=2，无法构成回文 
	
	tot = 0;
	for(int i=1;i<=n;i++){
		if(p[i])	continue;
		int u = s[i] - 'a', f = q[u].front(), b = q[u].back();
		if(f == b)	continue;//这种情况只有奇数有，无论它在哪个位置，p[f]都会是(n+1)/2，故先不管 
		q[u].pop_back(), q[u].pop_front();
		if(n & 1){//n是奇数的情况 
			if(tot + 1 < (n + 1) / 2)	p[f] = ++tot, p[b] = n - tot + 1;
			else if(tot + 1 == (n + 1) / 2)	tot++;//这个位置空开，留给那个出现奇数次的字符 
			else	p[f] = ++tot, p[b] = n - tot;
		}else	p[f] = ++tot, p[b] = n - tot + 1;
	}
	if(n & 1)	for(int i=1;i<=n;i++)	if(!p[i]){p[i] = (n + 1) / 2; break;}//特殊字符 
//	for(int i=1;i<=n;i++)	printf("%lld ", p[i]);
	for(int i=1;i<=n;i++){
		ans += i - 1 - query(p[i]);
		update(p[i], 1);
	}//求逆序对，注意开 long long 
	printf("%lld\n", ans);
	return 0;
} 
```


---

## 作者：liuzhongrui (赞：0)

## 题意：

给定一个只包含小写字母的字符串 $ S $，我们需要判断是否可以通过相邻字符的交换将其变为回文字符串。如果可以，输出最少需要的交换次数；如果不可以，输出 `-1`。
## 思路：

我们先来看输出 `-1` 的情况。首先统计每个字符的出现次数，如果字符串长度为奇数，那么字符串中的字符只允许有一个字符出现的次数为奇数，如果字符串长度为偶数，所有的字符出现次数只能为偶数。如果不满足上述条件，我们就输出 `-1`。

接下来是合法的情况。我们可以使用双指针从字符串的两端向中间移动，比较左右两侧的字符。当左右字符不相等时，寻找可以交换的字符，并记录交换次数。

可以使用线段树来维护，时间复杂度为 $O(n\log n)$。

## Code:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct SegTree {
    vector<int> seg;
    int MAX;
    SegTree(int N) {
        int i;
        for(i=1;i<2*N;i*=2) {}
        seg.resize(i);
        MAX = i;
    }
    void Edit(int n, int a) {
        n += MAX/2;
        seg[n] += a;
        n /= 2;
        while(n) {
            seg[n] = seg[2*n] + seg[2*n+1];
            n /= 2;
        }
    }
    int sum(int s, int e, int n, int ns, int ne) {
        if(e<=ns||ne<=s) return 0;
        if(s<=ns&&ne<=e) return seg[n];
        int mid = ns + ne >> 1;
        return sum(s, e, 2*n, ns, mid) + sum(s, e, 2*n+1, mid, ne);
    }
    int kth(int k, int n, int ns, int ne) {
        if(n >= MAX/2) return n-MAX/2;
        int mid = ns + ne >> 1;
        if(seg[2*n] >= k) return kth(k, 2*n, ns, mid);
        return kth(k-seg[2*n], 2*n+1, mid, ne);
    }
};
deque<int> Q[26];
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    int i, j;
    string s;
    cin >> s;
    int N = s.length();
    for(i=0;i<N;i++) {
        Q[s[i]-'a'].push_back(i);
    }
    if(N%2==0) {
        bool isPos = true;
        for(i=0;i<26;i++) {
            if(Q[i].size() % 2 != 0) isPos = false;
        }
        if(!isPos) {
            cout << "-1";
            return 0;
        }
    }
    else {
        int cnt = 0;
        for(i=0;i<26;i++) {
            if(Q[i].size() % 2 == 1) cnt++;
        }
        if(cnt != 1) {
            cout << "-1";
            return 0;
        }
    }
    SegTree tree(N+3);
    int MAX = tree.MAX;
    for(i=0;i<N;i++) tree.Edit(i, 1);
    int l = 1, r = N;
    int ans = 0;
    while(l<r) {
        int x = tree.kth(1, 1, 0, MAX/2);
        int y = tree.kth(r-l+1, 1, 0, MAX/2);
        if(s[x]==s[y]) {
            Q[s[x]-'a'].pop_front();
            Q[s[y]-'a'].pop_back();
            tree.Edit(x, -1);
            tree.Edit(y, -1);
            l++, r--;
            continue;
        }
        int r1 = 1e18, r2 = 1e18;
        if(Q[s[x]-'a'].size() > 1) {
            int c = Q[s[x]-'a'].back();
            int csum = tree.sum(0, c+1, 1, 0, MAX/2);
            r1 = r-l+1 - csum;
        }
        if(Q[s[y]-'a'].size() > 1) {
            int c = Q[s[y]-'a'].front();
            int csum = tree.sum(0, c+1, 1, 0, MAX/2);
            r2 = csum - 1;
        }
        if(r1 < r2) {
            ans += r1;
            tree.Edit(Q[s[x]-'a'].back(), -1);
            tree.Edit(Q[s[x]-'a'].front(), -1);
            Q[s[x]-'a'].pop_back();
            Q[s[x]-'a'].pop_front();
        }
        else {
            ans += r2;
            tree.Edit(Q[s[y]-'a'].back(), -1);
            tree.Edit(Q[s[y]-'a'].front(),-1);
            Q[s[y]-'a'].pop_back();
            Q[s[y]-'a'].pop_front();
        }
        l++, r--;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：sodalyghat (赞：0)

### 分析
首先判断不可行的情况，即个数为奇数的字母最多有一种。

然后来看最小代价，这个题的数据范围比较大，不像可以 DP 的样子，因此我们尝试贪心。

先猜一个结论，我们从外往内匹配，每次一定是选择离目标点距离和最小的一对字母。也比较好证明，如果不选择它们，那么在这一次内产生的代价一定会变大，而这一对字母在之后选产生的代价却不一定会变小，所以不如不交换，因此结论成立了。

实现需要维护一个相对距离，我就直接用线段树了。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace Luo_ty{
	const int MAXN = 200005, inf = 0x7fffffff / 2;
	char ch[MAXN];
	int wz[26][MAXN], l[26], r[26];
	struct node{
		int lson, rson, tag;
	}seg[MAXN << 2];
	int cnt;
	void Build(int &x, int l, int r){
		x = ++cnt;
		if(l == r) return ;
		int mid = l + r >> 1;
		Build(seg[x].lson, l, mid);
		Build(seg[x].rson, mid + 1, r);
	}
	void change(int x, int l, int r, int L, int R){
		if(L <= l && r <= R){
			seg[x].tag++;
			return ;
		}
		if(l > R || r < L) return ;
		int mid = l + r >> 1;
		change(seg[x].lson, l, mid, L, R);
		change(seg[x].rson, mid + 1, r, L, R);
	}
	int query(int x, int l, int r, int w){
		if(l == r) return seg[x].tag;
		int mid = l + r >> 1;
		if(mid >= w) return seg[x].tag + query(seg[x].lson, l, mid, w);
		else return seg[x].tag + query(seg[x].rson, mid + 1, r, w);
	}
	int main(){
		scanf("%s", ch + 1);
		int n = strlen(ch + 1);
		for(int i = 1;i <= n;i++){
			wz[ch[i] - 'a'][++r[ch[i] - 'a']] = i;
		}
		int num = 0;
		for(int i = 0;i < 26;i++){
			l[i] = 1;
			if((r[i] - l[i] + 1) & 1) num++;
		}
		if(num > 1){
			printf("-1");
			return 0;
		}
		int rt1, rt2;
		Build(rt1, 1, n);
		Build(rt2, 1, n);
		long long ans = 0;
		for(int L = 1;L << 1 <= n;L++){
			int R = n - L + 1, Min = inf, w = 0;
			for(int i = 0;i < 26;i++){
				if(l[i] >= r[i]) continue;
				int w1 = wz[i][l[i]], w2 = wz[i][r[i]];
				int t1 = query(rt1, 1, n, w1), t2 = query(rt2, 1, n, w1);
				int wz1 = w1 + t1 - t2;
				t1 = query(rt1, 1, n, w2), t2 = query(rt2, 1, n, w2);
				int wz2 = w2 + t1 - t2;
				int now = wz1 - L + R - wz2;
//				printf("-%d %d %d %d-\n", w1, w2, wz1, wz2);
				if(now < Min){
					Min = now;
					w = i;
				}
			}
			ans += Min;
			int w1 = wz[w][l[w]], w2 = wz[w][r[w]];
			l[w]++;
			r[w]--;
			change(rt1, 1, n, 1, w1);
			change(rt2, 1, n, w2, n);
//			printf("%d %c\n", ans, 'a' + w);
		} 
		printf("%lld", ans);
		return 0;
	}
}
signed main(){
	return Luo_ty::main();
}
```

---

## 作者：Enoch006 (赞：0)

题意：交换相邻字符使字符串回文。

首先判断能不能变成回文串，这个容易。

如果可以，接着考虑每一个字符应当和哪一个字符匹配。

我们应当从左往右依次满足条件，并且应当让最右边的一个相同字符来满足条件，证明其余的题解已经提到了：

例如：

a.....a.......a....b

要满足条件一定是让离 b 最近的 a 交换到 b 的位置上。

这时，其他题解研究交换与逆序对的性质，进而模拟如何交换。

但是有一种不用思考的方法，发现文艺平衡树可以直接维护区间交换，所以直接用即可。

最后需要注意如果 $n$ 是奇数的情况下需要特判这一个数去另外一边继续模拟。

代码使用了 Fhq-Treap 进行实现。

```cpp
#include <bits/stdc++.h>
#define int long long
#define maxm 1000005
#define maxn 1005
#define inf 0x3f3f3f3f3f3f
using namespace std;
int T,n,m,ans,sum,cnt,rt,fl,pos;
int a[maxm],vis[100];
string s;
mt19937 rnd(time(0));
struct Fhq{
	int l,r,sz,rk;
	int key,mx[26];
}t[maxm];
int Newnode(int x){
	int k=++cnt;t[k].key=x;
	t[k].l=t[k].r=0;
	t[k].sz=1;t[k].rk=rnd();
	t[k].mx[x]=1;return k;
}
#define ls t[k].l
#define rs t[k].r
void Pushup(int k){
	for(int i=0;i<26;i++)t[k].mx[i]=!!(t[ls].mx[i]+t[rs].mx[i]);
	t[k].mx[t[k].key]=1;t[k].sz=t[ls].sz+t[rs].sz+1;
}
void Split(int k,int x,int &L,int &R){
	if(!k)return void(L=R=0);
	if(t[ls].sz+1<=x){
		L=k;
		Split(rs,x-t[ls].sz-1,rs,R);
	}else{
		R=k;
		Split(ls,x,L,ls);
	}
	Pushup(k);
} 
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(t[x].rk<t[y].rk){
		t[x].r=Merge(t[x].r,y);
		Pushup(x);return x;
	}else{
		t[y].l=Merge(x,t[y].l);
		Pushup(y);return y;
	}
}
void Indexr(int k,int x){
	if(t[rs].mx[x])sum+=t[ls].sz+1,Indexr(rs,x);
	else if(t[k].key==x)sum+=t[ls].sz+1;
	else Indexr(ls,x);
}
void Indexl(int k,int x){
	if(t[ls].mx[x])sum+=t[rs].sz+1,Indexl(ls,x);
	else if(t[k].key==x)sum+=t[rs].sz+1;
	else Indexl(rs,x);
}
int Find(int k,int x){
	if(t[ls].sz+1==x)return t[k].key;
	if(t[ls].sz>=x)return Find(ls,x);
	else return Find(rs,x-t[ls].sz-1); 
}
int Ask(int l,int r,int x,int op){
	int a,b,c,flag=0;
	Split(rt,r,a,c);
	Split(a,l-1,a,b);
	if(t[b].mx[x]&&op)flag=1,sum=l-1,Indexr(b,x);
	if(t[b].mx[x]&&!op)flag=1,sum=0,Indexl(b,x),sum=r+1-sum;
	rt=Merge(Merge(a,b),c);
	if(flag)return sum;
	else return -1;
}
void Swapl(int l,int r){
	int a,b,c,d,e;
	Split(rt,r,a,e);
	Split(a,r-1,a,d);
	Split(a,l,a,c);
	Split(a,l-1,a,b);
	rt=Merge(Merge(a,c),d);
	rt=Merge(Merge(rt,b),e);
}
void Swapr(int l,int r){
	int a,b,c,d,e;
	Split(rt,r,a,e);
	Split(a,r-1,a,d);
	Split(a,l,a,c);
	Split(a,l-1,a,b);
	rt=Merge(Merge(a,d),b);
	rt=Merge(Merge(rt,c),e);
}
signed main(){
//	freopen("in.in","r",stdin);
//	freopen("my.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
	cin>>s;n=s.size();
	for(int i=0;i<n;i++)vis[s[i]-'a']++;
	for(int i=0;i<26;i++)if(vis[i]%2)fl++;
	if(fl>=2){cout<<"-1\n";return 0;}
	for(int i=0;i<n;i++)rt=Merge(rt,Newnode(s[i]-'a'));
	s=' '+s;
	for(int i=1;i<=n/2;i++){
		int op=Ask(i+1,n-i+1,Find(rt,i),1);bool fl=0;
//		cout<<op<<"\n";
		if(op==-1)fl=1,op=Ask(i,n-i,Find(rt,n-i+1),0);
		if(!fl){
			if(op==n-i+1)continue;
			ans+=n-i+1-op;
			Swapl(op,n-i+1);
//			cout<<op<<" "<<n-i+1<<"\n";
		}else{
			if(op==i)continue;
			ans+=op-i;
			Swapr(i,op);
//			cout<<i<<" "<<op<<"\n";
		}
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：PCCP (赞：0)

## 思路

看到这个，想起前一天写过的[JOISC2014_B たのしい家庭菜園](https://www.luogu.com.cn/problem/AT_joisc2014_b)，很像啊，很像啊。发现回文串我们把他从两端向中间赋值，那他何尝不是个单峰的呢！

无解的情况学过信竞的都会判！

简单模拟可知，相同字符一定是第一个匹最后一个，第二个匹倒数第二个最优。同时，既移动左端点又右端点，一定比固定一端更劣。所以把左端点固定了，移动右端点。都赋个值，表示其本来应该在序列的某个位置，求个逆序对即可。

问题在于这个有奇数的情况，有奇数的话中间的位置必须留开来给出现奇数次的字符。

## 代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<stack>
#include<list>
#include<set>
using namespace std;
typedef pair<int,int> PII;
const int N=2e5+10;
const int M=30;
string s;
int n,a[N],cnt[M],tot,sum[N],c[N];
long long ans;
bool st[N];
list<int> pos[M];
int lowbit(int x){
	return x&-x;
}
void add(int x){
	while(x<=n){
		++c[x];
		x+=lowbit(x);
	}
}
int ask(int x){
	int res=0;
	while(x){
		res+=c[x];
		x-=lowbit(x);
	}
	return res;
}
int main(){
	cin>>s;
	n=s.size();
	for(int i=1;i<=n;i++){
		++cnt[s[i-1]-'a'];
		pos[s[i-1]-'a'].push_back(i);
	}
	int js=0;
	for(int i=0;i<26;i++){
		if(cnt[i]&1){
			js++;
		}
		if(js>1){
			puts("-1");
			return 0;
		}
	}
	bool flag=false;
	if(n&1){
		for(int i=1;i<=n;i++){
			if(!a[i]){
				int x=pos[s[i-1]-'a'].front(),y=pos[s[i-1]-'a'].back();
				if(x==y){
					continue;
				}
				if(tot+1==(n+1)/2){
					++tot,flag=true;
				}
				if(!flag){
					a[x]=++tot,a[y]=n-tot+1;
				}
				else{
					a[i]=++tot,a[y]=n-tot;
				}
				pos[s[i-1]-'a'].pop_front();
				pos[s[i-1]-'a'].pop_back();
			}
		}
		for(int i=1;i<=n;i++){
			if(!a[i]){
				a[i]=(n+1)/2;
			}
		}
	}
	else{
		for(int i=1;i<=n;i++){
			if(!a[i]){
				a[i]=++tot;
				pos[s[i-1]-'a'].pop_front();
				if(!pos[s[i-1]-'a'].empty()){
					a[pos[s[i-1]-'a'].back()]=n-tot+1;
					pos[s[i-1]-'a'].pop_back();
				}
			}
		}
	}
	for(int i=1;i<=n;i++){
		ans+=i-1-ask(a[i]);
		add(a[i]);
	}
	printf("%lld\n",ans);
}
```


---

## 作者：_Imaginary_ (赞：0)

[AT3733](https://www.luogu.com.cn/problem/AT3733)

## Problem

给定一个字符串 $S$，求最少的次数使它变成回文字符串。每次操作交换相邻两个字符。

记字符串长度为 $n$。

## Solution

第一步，显然要判断是否合法。

一个字符串不能变成回文串当且仅当这个字符串中出现奇数次的字母个数 $\ge 2$。

当然，如果字符串长度是奇数，那么最中间的（转成回文串后第 $\frac{n+1}{2}$ 个字符）出现奇数次的字母。

前面都很显然，关键是后面。

先考虑这样的一个字符串：`mhhamrahr`（这个字符串成功 hack 掉我一开始的假做法）

很明显，`m...m....` 要转化成 `m.......m` 或 `.m.....m.` 等等。
但是，我们看 `m` 和 `h`，是转化成 `mh..h..hm` 更优，还是转化成 `hm..h..mh` 更优呢？显然是前者。

也就是说，如果 `m` 在最外面（比如开头或结尾），我们强行将它搞到里面，不优。

再看另一个字符串 `ababacca`

如果我们让第一个 `a` 和第二个 `a` 配对，显然是不好的。

所以，对于每个字母，我们考虑最左侧的和最右侧的配对，然后去掉最左和最右后的最左和最右配对。

综上，我们就找到了字母的对应关系，还差最后一步：求次数。

次数其实就是逆序对，这里我用归并排序来求。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=200005;
char s[N];
int n;
int check_ok()
{
	int cnt[35],ta=0,tb=0;
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)
		cnt[s[i]-'a']++;
	for(int i=0;i<26;i++)
	{
		if(cnt[i]&1) ta++,tb=i;
		if(ta>=2) return -1;
	}
	if(ta==1) return tb;
	return -2;
}
int np[N];//new position
int pos[26][N],cnt[26];
int peidui[N];
int x[N],y[N];
ll ans;
void merge_sort(int L,int R)
{
	if(L==R) return;
	int mid=(L+R)/2;
	merge_sort(L,mid);
	merge_sort(mid+1,R);
	int ta=L,tb=mid+1,tmp=L;
	while(ta<=mid&&tb<=R)
	{
		if(x[ta]>x[tb])
		{
			ans+=(mid-ta+1);
			y[tmp++]=x[tb++];
		}
		else y[tmp++]=x[ta++];
	}
	while(ta<=mid) y[tmp++]=x[ta++];
	while(tb<=R) y[tmp++]=x[tb++];
	for(int i=L;i<=R;i++) x[i]=y[i];
}
int main()
{
	memset(np,0,sizeof(np));
	memset(cnt,0,sizeof(cnt));
	scanf("%s",s+1);
	n=strlen(s+1);
	int ta=check_ok();
	if(ta==-1)
	{
		printf("-1");
		return 0;
	}
	for(int i=1;i<=n;i++)
		pos[s[i]-'a'][++cnt[s[i]-'a']]=i;
	for(int i=0;i<26;i++)
	{
		if(!cnt[i]) continue;
		sort(pos[i]+1,pos[i]+cnt[i]+1);
		for(int j=1;j<=cnt[i];j++)
		{
			if(ta==i&&j==(cnt[i]+1)/2) np[pos[i][j]]=(n+1)/2;
			else peidui[pos[i][j]]=pos[i][cnt[i]-j+1];
		}
	}
	for(int i=1,cur=0;i<=n;i++)
	{
		if(np[i]) continue;
		np[i]=++cur;
		np[peidui[i]]=n-cur+1;
	}
	memcpy(x,np,sizeof(x));
	merge_sort(1,n);
	printf("%lld\n",ans);
	return 0;
}

```

---

