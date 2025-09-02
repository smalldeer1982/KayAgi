# Jumping on Tiles

## 题目描述

### 题目大意

给定一个字符串 $s$，polycarp 欲从字符串首跳到字符串末 ($s_1$ → $s_n$，其中 $n$ 表示该字符串长度)。

假设 polycarp 现从 $a_i$ 跳到了 $a_j$ 我们定义这一次跳跃的权值为 $|\operatorname{index}(a_i) - \operatorname{index}(a_j)|$，其中 $\operatorname{index}$
 表示该字符在字母表中的序号 ( 如 $\operatorname{index}('a') = 1, \; \operatorname{index}('z') = 26$ )。
 
 请构造出一种在保证**权值和最小**的情况下**经过的字符最多**的跳跃方案 ( 当然，同一个字符只能经过一次，其中同一个仅指在字符串中的位置相同 )。

## 样例 #1

### 输入

```
6
logic
codeforces
bca
aaaaaaaaaaa
adbaadabad
to```

### 输出

```
9 4
1 4 3 5
16 10
1 8 3 4 9 5 2 6 7 10
1 2
1 3
0 11
1 8 10 4 3 5 7 2 9 6 11
3 10
1 9 5 4 7 3 8 6 2 10
5 2
1 2```

# 题解

## 作者：CarroT1212 (赞：7)

### 题目大意

给定 $t$ 次询问，对于每次询问，给定一个字符串 $s$。设 $s$ 的长度为 $n$，且 $\operatorname{index}(\texttt{a})=1$，$\operatorname{index}(\texttt{b})=2$，……，$\operatorname{index}(\texttt{c})=26$，以此类推。Polycarp 现在位于 $s_1$，他可以花费 $|\operatorname{index}(s_i)-\operatorname{index}(s_j)|$ 的代价从 $s_i$ 移动到 $s_j$。每个 $s_i$ 只能走一遍。请你求出一种让他移动到 $s_n$ 的方式，使得代价最小的同时移动次数最大。分别输出代价、最多能移动到的位置数量和移动过程。

数据范围：$1 \le t \le 10^4$，$2 \le |s| \le 2 \times 10^5$，保证数据中 $s$ 长度的总和不超过 $2 \times 10^5$。

------------

### 解法分析

还是首先思考一个问题：代价最小可以是多少？

显然 $|\operatorname{index}(s_1)-\operatorname{index}(s_n)|$。

那在这个条件下，怎么才能使得移动步数最大？

分两种情况：

+ $\operatorname{index}(s_1)\le \operatorname{index}(s_n)$：将所有满足 $\operatorname{index}(s_1)\le \operatorname{index}(s_i) \le \operatorname{index}(s_n)$ 的 $s_i$ 都分别走一遍；

+ $\operatorname{index}(s_1)>\operatorname{index}(s_n)$：将所有满足 $\operatorname{index}(s_1)\ge \operatorname{index}(s_i) \ge \operatorname{index}(s_n)$ 的 $s_i$ 都分别走一遍。

然后就结束了，应该不难理解。

------------

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const ll N=2e5+7;
struct node { char a; ll b; } sz[N];
bool cmp1(const node a,const node b) { return a.a==b.a?a.b<b.b:a.a<b.a; }
bool cmp2(const node a,const node b) { return a.a==b.a?a.b<b.b:a.a>b.a; }
void solve() {
	ll st,ed,n; string str;
	cin>>str;
	n=str.size();
	for (ll i=0;i<n;i++) sz[i+1]={str[i],i+1};
	if (str[0]<=str.back()) {
		sort(sz+1,sz+n+1,cmp1);
		for (ll i=1;i<=n;i++) if (sz[i].a==str[0]) { st=i; break; } //找到一个相同的就结束
		for (ll i=n;i;i--) if (sz[i].a==str.back()) { ed=i; break; }
		printf("%lld %lld\n",(ll)(str.back()-str[0]),ed-st+1);
		for (ll i=st;i<=ed;i++) printf("%lld ",sz[i].b);
	}
	else {
		sort(sz+1,sz+n+1,cmp2);
		for (ll i=1;i<=n;i++) if (sz[i].a==str[0]) { st=i; break; }
		for (ll i=n;i;i--) if (sz[i].a==str.back()) { ed=i; break; }
		printf("%lld %lld\n",(ll)(str[0]-str.back()),ed-st+1);
		for (ll i=st;i<=ed;i++) printf("%lld ",sz[i].b);
	}
	printf("\n");
}
int main() {
	ll t; scanf("%lld",&t); while (t--) solve();
	return 0;
}
```

---

## 作者：Cure_Wing (赞：5)

### 题目
* [CF1729C Jumping on Tiles](https://www.luogu.com.cn/problem/CF1729C)

### 解析
* **声明：以下讨论均以 $s_1\le s_n$（$n$ 为字符串长度） 为前提，$s_1\ge s_n$ 请自己根据推理过程自行解决。**
* 首先考虑只有两个字符 $s_1,s_2$ 的情况：
* 此时的答案只能是 $s_2-s_1$，路径为 $1→2$。
* 接下来考虑插入一个字符，此时可分两种情况讨论：

1. 路径 $1→3$：结果是 $s_3-s_1$。
2. 路径 $1→2→3$：此时可分三种情况讨论：

- $s_1\le s_3\le s_2$，结果是 $|s_2-s_1|+|s_2-s_3|=2s_2-s_1-s_3=2(s_2-s_3)+(s_3-s_1)\ge s_3-s_1$。
- $s_1\le s_2\le s_3$，结果是 $|s_2-s_1|+|s_2-s_3|=s_3-s_1$。
- $s_2\le s_1\le s_3$，结果是 $|s_2-s_1|+|s_2-s_3|=s_1+s_3-2s_2=(s_3-s_1)+2(s_1-s_2)\ge s_3-s_1$。

* 通过以上分类我们可以发现插入的字母满足能够保持序列单调性的方案是优秀的，且答案最小值永远为 $(s_n-s_1)$。
* 那么我们就可以把能维持序列原有单调性的字母取出再排序就可以啦，所得的序列就是答案序列。
* 还有就是别忘记分类讨论。

### 代码
* 时间复杂度 $\mathcal{O}\left(\sum |s|\log |s|\right)$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using std::cin;using std::cout;
int t,cnt;
struct node{
	int p,id;
}ans[200005];
char s[200005];
signed main(){
// 	freopen(".in","r",stdin);
// 	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	for(cin>>t;t--;cnt=0){
		cin>>s;
		int len=strlen(s);
		for(int i=1;i<len-1;++i) if(s[0]<=s[i]&&s[i]<=s[len-1]||s[0]>=s[i]&&s[i]>=s[len-1]) ans[++cnt].id=i+1,ans[cnt].p=s[i]-'a'+1;
        //分类讨论！
		if(s[0]>=s[len-1])
			std::sort(ans+1,ans+cnt+1,[](node x,node y){return x.p>y.p;});
		else
			std::sort(ans+1,ans+cnt+1,[](node x,node y){return x.p<y.p;});
		cout<<abs(int(s[len-1]-s[0]))<<' '<<cnt+2<<'\n'<<1<<' ';
		for(int i=1;i<=cnt;++i) cout<<ans[i].id<<' ';
		cout<<len<<'\n';
	}
    return 0;
}
```

---

## 作者：zhicheng (赞：3)

### 思路

很明显，如果只考虑花费最小，直接从第一个跳到最后一个是一定不劣的。因为你无论如何都至少要跨 $\left|\text{index}(s_0)-\text{index}(s_{len-1})\right|$ 个，花费也至少是这么多。

然后我们考虑其他的字符，很容易地发现如果 $\text{index}(s_i)$ 的值在 $\text{index}(s_0)$ 与 $\text{index}(s_{len-1})$ 之间，插入后就没有影响。

所以我们得到如下策略：如果 $\text{index}(s_0)>\text{index}(s_{len-1})$，从大到小依次访问值在 $\text{index}(s_0)$ 与 $\text{index}(s_{len-1})$ 之间的字符。否则就从小到大。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
struct e{
	int id;
	char p;
}a[200010];
char s[200010];
bool cmp1(e a,e b){  //排序。记得要使编号小的在前面
	if(a.p!=b.p){
		return a.p<b.p;
	}
	return a.id<b.id;
}
bool cmp2(e a,e b){
	if(a.p!=b.p){
		return a.p>b.p;
	}
	return a.id<b.id;
}
int main(){
	int n,len,i,sum,u;
	scanf("%d",&n);
	while(n--){
		sum=0;
		scanf("%s",s);
		len=strlen(s);
		for(int i=0;i<=len-1;i++){
			a[i+1].id=i+1;  //结构体存编号
			a[i+1].p=s[i];
		}
		if(s[0]<s[len-1]){  //看大小关系排序
			sort(a+1,a+len+1,cmp1);  //从小到大
		}
		else{
			sort(a+1,a+len+1,cmp2);  //从大到小
		}
		for(i=1;i<=len;i++){
			if(a[i].id==1){  //找到第一个字符
				break;
			}
		}
		u=i;
		for(;;i++){
			sum++;  //记录一共有多少字符可以跳
			if(a[i].id==len){  //到了最后
				break;
			}
		}
		printf("%d %d\n",abs(s[0]-s[len-1]),sum);  //先输出总数
		for(i=u;;i++){
			printf("%d ",a[i].id);
			if(a[i].id==len){
				break;
			}
		}
		printf("\n");
	}
}
```

---

## 作者：thh_loser (赞：1)

# CF1729C Jumping on Tiles 题解

## 题目描述

给出一个字符串，字符串中的每一个字母的值为这个字母在字母表中的序号。现在从第 $1$ 个字符开始，每次可以跳到任一一个字符，代价为两个字符的值之差的绝对值，跳到最后一个字符时结束。问在满足跳到最后一个字符所用代价之和最小的前提下，最多能跳到哪些格子。

## 思路

可以证明，最小代价之和就是第一个与最后一个字符的值之差的绝对值，设第 $i$ 个字符的值为 $a_{i}$，共 $n$ 个字符，因为必须从第一个开始，从最后一个结束，那么至少所需代价就是 $\lvert a_{n}-a_{1} \rvert$，如果再插入一个 $a_{i}$，如果 $a_{i}$ 在 $a_{1}\sim a_{n}$（$a_{1}<a_{n}$）或 $a_{n}\sim a_{i}$（$a_{1}>a_{n}$）之间，那么代价之和不会改变，但如果不在范围内，那么代价和一定会增加。所以要取得低价最小，只要把所有在第一个和最后一个的值之间的数加入，按升序或降序排序，得到的结果就是最佳方案了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,sl,ans,ansl;
int sx[200010],tot;
string s;
priority_queue<pair<int,int> > q;//用优先队列来排列顺序 
int main(){
	scanf("%d",&t);
	while(t--){
		ans=0,ansl=0,tot=0;//初始化 
		cin>>s;
		sl=s.size()-1;
		char la=s[sl],fi=s[0];
		if(la>fi){//如果最后一个比第一个大 
			for(int i=1;i<sl;i++){
				if(s[i]<=la&&s[i]>=fi){
					q.push(make_pair(-(int)s[i],i));//压入负值，升序排列 
				}
			}
		}
		else{
			for(int i=1;i<sl;i++){
				if(s[i]>=la&&s[i]<=fi){
					q.push(make_pair((int)s[i],i));//降序排列 
				}
			}
		}
		int t,s=(int)fi;
		while(!q.empty()){
			ansl++;//一共的长度 
			t=abs(q.top().first);
			ans+=abs(t-s);//从上一个到现在所需代价 
			sx[tot++]=q.top().second;//跳的顺序 
			s=t;
			q.pop();
		}
		if(!ansl){
			ans=abs((int)la-(int)fi);//如果只有首尾两个元素，那么答案就是两个数之差 
		}
		else{
			ans+=abs(t-(int)la);//因为堆里没有加入最后一个数， 所以再加上 
		}
		printf("%d %d\n",ans,ansl+2);//答案和最多数量，最多数量因为没有算首尾所以要加2 
		cout<<"1 ";//首 
		for(int i=0;i<tot;i++){
			printf("%d ",sx[i]+1);
		}
		cout<<sl+1;//尾 
		printf("\n");
	}
}
```


---

## 作者：lrqlrq250 (赞：0)

## 解题思路
比较显然的结论是，最终的最小 $cost$ 一定是 $|\operatorname{index}(s_1) - \operatorname{index}(s_n)|$。

那么我们为了保持最小的 $cost$，能跳到的 $s_i$ 一定是在 $\operatorname{index}(s_1)$ 和 $\operatorname{index}(s_n)$ 之间的。

所以我们只需要分两种情况讨论：

- 当 $\operatorname{index}(s_1) \leq \operatorname{index}(s_n)$ 时，显然我们应该在从小到大排序后，跳所有满足 $\operatorname{index}(s_1) \leq \operatorname{index}(s_i) \leq \operatorname{index}(s_n)$ 的 $s_i$。

- 当 $\operatorname{index}(s_1) > \operatorname{index}(s_n)$ 时，则应该从大到小排序，然后跳所有满足 $\operatorname{index}(s_n) \leq \operatorname{index}(s_i) \leq \operatorname{index}(s_1)$ 的 $s_i$。

排序的时间复杂度为单次 $O(n \log n)$。

求出 $cost$ 和所有要跳到的点的复杂度为最坏单次 $O(n)$。

因此整个算法的时间复杂度是 $O(\sum n \log n)$。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node{int ind, id;}a[200001];
char s[200001];
int ans[200001];

inline int getindex(char c){return c - 'a' + 1;}
inline bool cmp_min(Node x, Node y){return x.ind < y.ind;}
inline bool cmp_max(Node x, Node y){return x.ind > y.ind;}

int main(){
	int t, n;
	scanf("%d", &t);
	while (t--){
		scanf("%s", s + 1);
		n = strlen(s + 1);
		for (int i=1; i<=n; i++) a[i] = (Node){getindex(s[i]), i};
		if (getindex(s[1]) <= getindex(s[n])) stable_sort(a + 1, a + n + 1, cmp_min);
		else stable_sort(a + 1, a + n + 1, cmp_max);
		int p = 1, q;
		while (a[p].id != 1) p++;
		q = p + 1;
		while (a[q].id != n) q++;
		ans[1] = a[p].id;
		int cost = 0;
		for (int i=p+1; i<=q; i++){
			ans[i - p + 1] = a[i].id;
			cost += abs(a[i].ind - a[i - 1].ind);
		}
		printf("%d %d\n", cost, q - p + 1);
		for (int i=1; i<=q-p+1; i++) printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}

```

PS：由于洛谷 RMJ 正在维护，Codeforces 上的 AC 记录在[这里](https://codeforces.com/contest/1729/submission/175328164)。

---

## 作者：BotDand (赞：0)

# $\text{Problems}$

给定一个字符串 $s$，polycarp 欲从字符串首跳到字符串末 ($s_1$ → $s_n$，其中 $n$ 表示该字符串长度)。

假设 polycarp 现从 $a_i$ 跳到了 $a_j$ 我们定义这一次跳跃的权值为 $|\operatorname{index}(a_i) - \operatorname{index}(a_j)|$，其中 $\operatorname{index}$
 表示该字符在字母表中的序号 ( 如 $\operatorname{index} = 1, \; \operatorname{index} = 26$ )。
 
 请构造出一种在保证**权值和最小**的情况下**经过的字符最多**的跳跃方案 ( 当然，同一个字符只能经过一次，其中同一个仅指在字符串中的位置相同 )。
 
 ### 输入格式
 
 第一行包含一个整数 $t \; (1 \leqslant t \leqslant 10^4)$ ，表示测试样例组数。
 
 对于每组测试样例，包含一行一个字符串 $s \; (2 \leqslant |s| \leqslant 2 \cdot 10^5)$，意义见题面。
 
 ### 输出格式
 
 对于每组测试样例，第一行包含两个用空格隔开的整数 $cost$ 和 $m$ 分别表示 最小权值和 和 最大经过的字符数。
 
 第二行包含 $m$ 个整数，分别表示沿途经过的所有字符位置。( 例如输出 $1 \; 4 \; 3 \; 5$ 表示跳跃路径为 $s_1$ → $s_4$ → $s_3$ → $s_5$ ) 数与数之间用空格隔开。
 
 $Translated \; by \; Zigh$
 
# $\text{Answer}$

考虑到有一个性质：如果 $c$ 满足 $c\in[a,b]$，那么有 $|c-a|+|c-b|=|a-b|$，可以通过考虑数轴证明。

那么可以从 $2$ 到 $n-1$ 中把所有 $a_{i}\in[a_{1},a_{n}]$ 都选出来，再将它们从小到大（或从大到小，这得考虑 $a$ 与 $b$ 的大小关系），如果 $a$ 大于 $b$，那么从大到小输出，反之则从小到大输出。

显然这样选一定是最优的。

# $\text{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
struct arr
{
    int sum,num;
}a[200002];
int t;
char s[200002];
int n;
bool cmp1(arr x,arr y)
{
    return x.sum>y.sum;
}
bool cmp2(arr x,arr y)
{
    return x.sum<y.sum;
}
void work()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;++i) a[i].sum=s[i]-96,a[i].num=i;
    cout<<abs(a[1].sum-a[n].sum)<<" ";
    if(a[1].sum>a[n].sum)
    {
        sort(a+2,a+n,cmp1);
        int x=0;
        for(int i=2;i<n;++i)
            if(a[i].sum<=a[1].sum)
            {
                x=i;
                break;
            }
        int y=n;
        for(int i=n-1;i>=2;--i)
            if(a[i].sum>=a[n].sum)
            {
                y=i;
                break;
            }
        if(x==0||y==n)
        {
            cout<<"2\n1 "<<n<<"\n";
            return;
        }
        cout<<y-x+1+2<<"\n"<<"1 ";
        for(int i=x;i<=y;++i) cout<<a[i].num<<" ";
        cout<<n<<"\n";
    }
    else
    {
        sort(a+2,a+n,cmp2);
        int x=0;
        for(int i=2;i<n;++i)
            if(a[i].sum>=a[1].sum)
            {
                x=i;
                break;
            }
        int y=n;
        for(int i=n-1;i>=2;--i)
            if(a[i].sum<=a[n].sum)
            {
                y=i;
                break;
            }
        if(x==0||y==n)
        {
            cout<<"2\n1 "<<n<<"\n";
            return;
        }
        cout<<y-x+1+2<<"\n"<<"1 ";
        for(int i=x;i<=y;++i) cout<<a[i].num<<" ";
        cout<<n<<"\n";
    }
}
int main()
{
    cin>>t;
    while(t--) work();
    return 0;
}
```

---

