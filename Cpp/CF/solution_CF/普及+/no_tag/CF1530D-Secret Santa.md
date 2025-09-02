# Secret Santa

## 题目描述

Every December, VK traditionally holds an event for its employees named "Secret Santa". Here's how it happens.

 $ n $ employees numbered from $ 1 $ to $ n $ take part in the event. Each employee $ i $ is assigned a different employee $ b_i $ , to which employee $ i $ has to make a new year gift. Each employee is assigned to exactly one other employee, and nobody is assigned to themselves (but two employees may be assigned to each other). Formally, all $ b_i $ must be distinct integers between $ 1 $ and $ n $ , and for any $ i $ , $ b_i \ne i $ must hold.

The assignment is usually generated randomly. This year, as an experiment, all event participants have been asked who they wish to make a gift to. Each employee $ i $ has said that they wish to make a gift to employee $ a_i $ .

Find a valid assignment $ b $ that maximizes the number of fulfilled wishes of the employees.

## 说明/提示

In the first test case, two valid assignments exist: $ [3, 1, 2] $ and $ [2, 3, 1] $ . The former assignment fulfills two wishes, while the latter assignment fulfills only one. Therefore, $ k = 2 $ , and the only correct answer is $ [3, 1, 2] $ .

## 样例 #1

### 输入

```
2
3
2 1 2
7
6 4 6 2 4 5 6```

### 输出

```
2
3 1 2
4
6 4 7 2 3 5 1```

# 题解

## 作者：jiayixuan1205 (赞：4)

#  CF1530D Secret Santa
## 题目大意
$n$ 个人互送礼物，每个人都有一个想送礼物的对象，可能会有多个人同时想给一个人送礼物，也可能会有人收不到礼物，现在要求每个人都能收到礼物且每个人的礼物不能送给自己，求尽可能满足大家希望的方式。
## 分析
如果每个人希望送礼物的对象都不同，那么直接就是答案；如果希望送礼物的对象有冲突，容易想到让收到礼物多的人给没有礼物的人“匀”礼物。

在这样的安排下，就可能出现自己把礼物送给自己的情况。所以我们需要使两个人交换礼物。由题意得，每个人初始不会想把礼物送给自己，所以我们让把礼物送给自己的这个人把礼物送给他最初想送的人，再让原来决定的人选把礼物送给他，这样就不会产生冲突了。
## 细节处理
为方便理解，可以把每个人理解为一个点，把一个人“被希望送礼物”的个数理解为入度。

在记录每个人想把礼物送给谁的时候，可以用 `map`，便于记录查询。

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 1e5+50;
int T,n,cnt;

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n;
		cnt=0;//记录不改动的个数 
		vector<int> a(n+1),in(n+1),ans(n+1),v;//in用来存储每个人收到礼物的个数，可以理解为入度；ans存储的是最终结果 ，v记录的是没有礼物收的人 
		map<int,int> mp;//记录每个人初始想把礼物送给谁 
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
			in[a[i]]++;//入度++ 
			mp[a[i]]=i;
		}
		for(int i=1;i<=n;i++)
		{
			if(!in[i]) v.push_back(i);//如果这个人没有礼物收 
		}
		for(int i=1;i<=n;i++)
		{
			if(in[a[i]]==1)//如果刚好这个人能收到一份礼物 
			{
				cnt++;//无需改动 
				ans[i]=a[i];//不产生冲突，直接让这个人如愿， 
			}
			else
			{
				ans[i]=v.back();//如果一个人有很多礼物收，把礼物匀给没有礼物收的人 
				in[a[i]]--;//分完礼物后入度-- 
				v.pop_back();//收到礼物后出队 
			}
		}
		cout<<cnt<<endl;
		for(int i=1;i<=n;i++)
		{
			if(i==ans[i])//如果礼物送给了自己 
			{
				ans[i]=a[i];
				ans[mp[a[i]]]=i;//让他把礼物送给原本想送的人 
				mp[a[i]]=i;//交换礼物 
			}
		}
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：COsm0s (赞：3)

提供一种不同的做法。

题意本质上就是用未出现过的数去**替代**重复的数，并且需要满足 $i \neq a_i$。

我们将未出现过的数列出来。以第二组样例为例：

`6 4 6 2 4 5 6`

未出现过的数即 $1,2,3$，我们记为 $p$ 数组。

再把那些重复的数的位置列出来：$1,2,3,5,7$，其中 $1,3,7$ 位置上的数都为 $6$，而 $2,5$ 位置上的数为 $4$，这里我们记 $q$ 数组。

所以原问题就变成了要将 $p$ 数组和 $q$ 数组中的 $size_p$ 个数对应，且 $p_i \neq q_i$（$size_p$ 即为 p 数组的数字个数）。

显然我们不能让原来重复的数字全被替换，所以在对应时要注意判断序列中 $a_{q_i}$ 是否剩下一个。

那就考虑将 $p$ 从大到小排序，$q$ 从小到大排序进行替换，这样较大数与较小数对应，不合法的情况只有在 $size_p$ 为奇数时，最中间的数可能会产生 $p_i=q_i$。

遇到这种情况直接跳过当前 $q_i$ 对应下一个即可。

```cpp
void Solve() {
	cin >> n;
	for(int i = 1; i <= n; i ++)
		cnt[i] = 0;
	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		cnt[a[i]] ++;
	}
	int pos = 1, sum = 0;
	for(int i = n; i >= 1; i --) {
		if(!cnt[i]) {
			++ sum;
			while(cnt[a[pos]] < 2 || i == pos) pos ++;
			cnt[a[pos]] --, a[pos] = i;
		}
	}
	cout << n - sum << '\n';
	for(int i = 1; i <= n; i ++)
		cout << a[i] << ' ';
	cout << '\n';
}
```

---

## 作者：renWhale (赞：1)

# CF1530D

我们其实可以先分析一下要求。
1. 会输入给我们一个图，具体是什么图回头会讲。
2. 要求我们输出一个**错排列**，也就是许多大大小小的环，且不存在自环。

那么他输入进来的是什么图呢，其实分析一下，每一个点都有唯一出边，那么这就是**内向基环树森林**。

那么我们可以将这个图处理一下，就是将所有的**环**拆出来，然后就会剩下**树**与**自环**，**树**可以拆成若干条**链**。

1. 将所有的**环**拿出来，然后记录节点个数 $dx$ 然后将总答案 $ans=ans+dx$。
2. 然后对于所有的**链**头尾相接，记录节点个数 $dx$ 然后将总答案 $ans=ans+dx-1$ 。
3. 然后就要考虑所有的**自环**了，对于所有的自环，将它们全部相连，就可以成为新的链，记录节点个数 $dx$ 然后总答案 $ans=ans+dx-1$。
4. 接下来是最头疼的一种问题，正好**只有一个自环**，遇到这种问题，我们就找到它指向的那个节点，然后将它插进去，此时会影响答案，将答案更新 $ans=ans-1$

完结撒花*★,°*:.☆(￣▽￣)/$:*.°★* 。

---

## 作者：Vii_Truly (赞：1)

如果每个人想要送给的人都不一样，那皆大欢喜，直接就是答案。

想一下，如果有两个人都想送给同一个人呢？三个人都想送给同一个人呢？如果有这样中情况发生，只能满足一个人。那另外的人怎么办呢？

不难想到，如果有 $x$ 个人都想将礼物送给一个人，那么必然会有 $x-1$ 个人没有礼物收，然后就让那 $x-1$ 个人送给这没有礼物收的 $x-1$ 个人。

还有一种情况，就是自己送给自己，虽然题目中保证了输入中不会有这种情况，但是经过我们的一顿安排，这种情况可能就出现了。

例如：$1$ 想送给 $3$，$2$ 也想送给 $3$，$3$ 想送给 $2$。 按照上面的处理方法，会让 $2$ 送给 $3$，$3$ 送给 $2$，这样 $1$ 就只能送给自己，是不满足题目要求的。

那这种情况怎么处理呢？

如果送给自己了，就让这个人的愿望满足，这样的话就有两个人的礼物送给了同一个人了。这时，让那个人把礼物送给这个原本要把礼物送给自己的人，这样就可以了，也不会减少总数。

如果上面的方法你没理解，体现到刚才的例子上，就是让 $1$ 把礼物送给 $3$，然后让 $2$ 把礼物送给 $1$，这样就是 $1$ 送给 $3$，$2$ 送给 $1$，$3$ 送给 $2$，这样就能理解了。

对于多个人想要送给同一个人，我的代码是满足最后一个人，代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
//    freopen("in", "r", stdin);
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, cnt = 0;
        scanf("%d", &n);
        vector<int>p(n + 1), st(n + 1), ans(n + 1), v;
        map<int, int>mp;
        for (int i = 1;i <= n; i++) {
            scanf("%d", &p[i]);
            st[p[i]]++; //想要给 p[i] 送礼物的人数
            mp[p[i]] = i; //最后一个想要给p[i] 送礼的人的编号
        }
        for (int i = 1;i <= n; i++) if (!st[i]) v.push_back(i);//没有人想要给i送礼物
        for (int i = 1;i <= n; i++) {
            if (st[p[i]] == 1) ans[i] = p[i], cnt++; //没有人和i争了，那就让i如愿以偿
            else { //有多个人想要给p[i]送，那就让i送给那些没有礼物收的人
                ans[i] = v.back();
                st[p[i]]--;
                v.pop_back();
            }
        }
        printf("%d\n", cnt);
        for (int i = 1;i <= n; i++) {
            if (i != 1) printf(" ");
            if (i == ans[i]) { //出现了自己送给自己
                ans[i] = p[i]; //满足这个人的想法
                ans[mp[p[i]]] = i; //让原本送给p[i]的那个人将礼物送给i
                mp[p[i]] = i;
            }
            printf("%d", ans[i]);
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：hellhell (赞：1)

### 题目描述

每年 $12$ 月，VK 传统上都会为其员工举办一场名为“秘密圣诞老人”的活动。 这是如何发生的。

$n$ 个编号从 $1$ 到 $n$ 的员工参加了此次活动。 每个员工 $i$ 都被分配了一个不同的员工 $b_i$，员工 $i$ 必须向该员工制作新年礼物。 每个员工被分配给另一个员工，没有人被分配给他们自己（但两个员工可能被分配给对方）。 形式上，所有 $b_i$ 必须是 $1$ 和 $n$ 之间的不同整数，并且对于任何 $i$，$b_i\neq i$ 必须成立。

分配通常是随机生成的。今年，作为一项实验，所有活动参与者都被问到他们想给谁送礼物。 每位员工 $i$ 都表示想给员工 $a_i$ 做礼物。

找到一个有效的分配 $b$ 来最大限度地满足员工的愿望。

### 思路分析

对于每个 $a_i$，如果还没被选择，直接让员工 $i$ 选。

后面让所有还未分配 $b_i$ 的员工去选没有被选择员工。

按照循环顺序分配即可。

这样会有的人选择自己，我们分两种情况讨论。

第一种情况是，只有一个人自己选择了自己。

这种情况我们只需要选择一个没有选到 $a_i$ 的员工或者 $a_i$ 与这个员工相同的员工交换他们两个的 $b_i$ 即可。

第二种情况是有多个员工选择了自己，我们直接内部两两交换他们的选择即可。

常数很大，注意优化。

### 代码实现

```cpp
#include<bits/stdc++.h>

using namespace std;

inline int read(){
    int res=0;
    int f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9'){
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res*f;
}

const int maxn=2e5+5;

int t;
int n;
int a[maxn];
int ans[maxn];
bool Win[maxn];//选到了自己想送礼物的员工，人赢
bool checked[maxn];
int loser[maxn],tag;//只能自己给自己送礼物，活得太失败了

inline void init(){
	memset(Win,false,sizeof(Win));
	memset(checked,false,sizeof(checked));
	tag=0;
}

void out(int x){
	if(x>=10)
		out(x/10);
	putchar(x%10+'0');
}

signed main(){
	t=read();
	while(t--){
		n=read();
		int ans_cnt=0;
		init();
		for(int i=1;i<=n;++i){
			a[i]=read();
			if(!checked[a[i]]){
				Win[i]=true;
				ans_cnt++;
				ans[i]=a[i];
				checked[a[i]]=true;
			}
		}
		int p=1;
		for(int i=1;i<=n;++i){
			if(Win[i])
				continue;
			while(p<=n && checked[p])
				p++;
			ans[i]=p++;
			if(ans[i]==i){
				loser[++tag]=i;
			}
		}
		if(tag==1){
			for(int i=1;i<=n;++i){
				if(!Win[i]){
					swap(ans[loser[tag]],ans[i]);
					break;	
				}
				else{
					if(a[i]==a[loser[tag]]){
						swap(ans[loser[tag]],ans[i]);
						break;	
					}
				}
			}
		}else{
			for(int i=1;i<tag;++i){
				swap(ans[loser[i]],ans[loser[i+1]]);
			}
		}
		out(ans_cnt);
		putchar('\n');
		for(int i=1;i<=n;++i){
			out(ans[i]);
			putchar(' ');
		}		
		putchar('\n');
	}
    return 0;    
}
```


---

## 作者：kradcigam (赞：1)

这道题挺有意思的。

首先答案为 $b_i$ 中不同数字的个数，现在我们来考虑如何构造这个东西。

首先，我们把图建出来，每个点连向它要送礼物的人，我们会发现最终的答案中这个图由若干个环组成，切环的大小不能为 $1$。

那么，我们可以让对于每个点 $i$ 任意一个在题目中想送 $i$ 礼物的人向 $i$ 连边，这样答案就保证了。

我们考虑剩下的，我们让入度为 $1$，出度为 $0$ 的点，连向它所在的链的最后方构成环，由于入度和出度都不超过 $1$，所有非常好维护。

还有的点是入度和出度都为 $0$ 的。如果这样的点数量为 $0$ 不需要任何操作；如果这样的点数量为 $>1$，则连成一个环；如果数量为 $1$，我们就让这个点强行加入这个图中。

```cpp
#include<bits/stdc++.h>
#define log(a) cerr<<"\033[32m[DEBUG] "<<#a<<'='<<(a)<<" @ line "<<__LINE__<<"\033[0m"<<endl
#define LL long long
#define SZ(x) ((int)x.size()-1)
#define ms(a,b) memset(a,b,sizeof a)
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=2e5+10;
int a[N],ans[N],h[N],l[N];
int find(int x){
	if(!h[x])return x;
	return h[x]=find(h[x]);
}
signed main(){
	int _=read();
	while(_--){
		int n=read(),s=0;
		vector<int>v;
		F(i,1,n)h[i]=ans[i]=0;
		F(i,1,n){
			a[i]=read();
			if(!h[a[i]]){
				s++;
				h[a[i]]=l[a[i]]=i;
				ans[i]=a[i];
			}
		}
		F(i,1,n)
			if(!ans[i]){
				if(find(i)!=i)ans[i]=find(i);
				else v.push_back(i);
			}
		if(v.size()==1){
			// log(v[0]);
			ans[v[0]]=a[v[0]];
			ans[l[a[v[0]]]]=v[0];
		}else{
			if(v.size()){
				F(i,0,SZ(v)-1)ans[v[i]]=v[i+1];
				ans[v[SZ(v)]]=v[0];
			}
		}
		cout<<s<<endl;
		F(i,1,n)cout<<ans[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：bryce (赞：0)

## [Secret Santa](https://www.luogu.com.cn/problem/CF1530D)
### 思路
这是一个需要深思熟虑的贪心，总之还算有点复杂。

首先，如果一个数不在它自己数值的下标上，就可以填进去，将剩下的还未填的数记录下来，此时情况如下（样例1，第一组）：

当前：2 1 _

剩余：3

然后将剩余的数的那个数组反过来，即从大到小排序，填满空位，这样可能会有冲突，但是，可以证明只会有一个冲突。

证明：$x,y,z$ 为下标，$a,b,c$ 分别为 $x,y,z$ 上的数值，假设 $y = b$，因为 $x < y < z$ 且 $a > b > c$，所以其余任何位置都无冲突。

那么如何解决掉冲突呢，将冲突位置上的值替换为之前这个位置上的值即可，再将之前这个位置上的值的现在的位置上的值改为冲突位置的值，这样就不会有冲突。

原来：2 1 3 位置 3 上有冲突

更改后：3 1 2 (第三个位置改为原来的值，第一个位置改为 3)

显然这种方案变换次数最少。
### 代码
```cpp
#include<iostream>
#include<vector>
using namespace std;

inline int read(){register int x = 0, f = 1;register char c = getchar();while (c < '0' || c > '9'){if (c == '-') f = -1;c = getchar();}while (c >= '0' && c <= '9'){x = (x << 1) + (x << 3) + (c ^ 48);c = getchar();}return x * f;}
inline void write(int x){if (x < 0) putchar('-'), x = -x;if (x > 9) write(x / 10);putchar(x % 10 + '0');}

const int N = 2e5 + 10;
int T, n, ans;
int a[N], b[N], cnt[N], tot;
vector<int> v[N];
bool vis[N], f[N];

int main(){
    T = read();
    while (T--){
        n = read();
        for (int i = 1; i <= n; i++) a[i] = read(), v[a[i]].push_back(i);
        for (int i = 1; i <= n; i++){
            for (auto j : v[i]){
                if (!vis[j] && i != j){
                    b[j] = i;
                    vis[j] = 1;
                    f[i] = 1;
                    break;
                }
            }
            if (!f[i]) cnt[++tot] = i;
        }
        for (int i = 1, l = tot; i <= n && l >= 1; i++){
            if (!vis[i]) b[i] = cnt[l], l--;
        }
        for (int i = 1; i <= n; i++){
            if (b[i] == i) swap(b[i], b[v[a[i]][0]]);
        }
        for (int i = 1; i <= n; i++){
            if (a[i] == b[i]) ans++;
        }
        cout << ans << '\n';
        for (int i = 1; i <= n; i++) cout << b[i] << ' ';
        cout << '\n';
        for (int i = 1; i <= n; i++) a[i] = b[i] = cnt[i] = vis[i] = f[i] = 0;
        for (int i = 1; i <= n; i++) v[i].clear();
        tot = ans = 0;
    }
    return 0;
}
```

---

## 作者：Tiago (赞：0)

## Solution

**每个人初始不会给自己送礼物**。

如果每人要送礼的人都不一样，答案即为 $n$。

如果有两个或以上的人要送给同一个人礼物，假设有 $x$ 个人要给同一个人送礼物，那么必有 $x-1$ 个人要更改送礼的人，并将礼物送个 $x-1$ 个没有礼物收的人。然而这样送礼物可能会导致有人送礼物给自己，对于这种情况，我们不妨让这个人就送礼给自己本来要送的人，而这样的操作也不会影响不改变送礼的人的数量。

于是我们定义一个 $t_i$ 表示最后一个要给 $i$ 送礼的人，再定义 $in_i$ 表示要给 $i$ 送礼的人数，先统计没人给其送礼的人，再处理有人要给其送礼的人，分两种情况：

1. 只有一人要给其送礼，该位置不改变；

2. 有多人要给其送礼，满足最后一人（这里是满足最后一人，也可以满足别人），即 $t_i$，同时 $in$ 数组减一。

最后扫一遍判断是否有要送给自己的人并处理即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define For(i,a,b) for(int i=(a);i<=(b);i++)
#define FOR(i,a,b) for(int i=(a);i>=(b);i--)
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define elif else if

const int N=2e5+4;
int n,a[N],in[N],t[N],same[N],sum,ans[N];
void solve()
{
	cin>>n;
	For(i,1,n)in[i]=t[i]=0;
	For(i,1,n)cin>>a[i],in[a[i]]++,t[a[i]]=i;
	same[0]=0;
	For(i,1,n)if(in[i]==0)same[++same[0]]=i;
	sum=0;
	For(i,1,n)
		if(in[a[i]]==1)ans[i]=a[i],sum++;
		elif(in[a[i]]!=0)
		{
			ans[i]=same[same[0]--];
			in[a[i]]--;
		}
	For(i,1,n)
		if(ans[i]==i)
		{
			ans[i]=a[i];
			ans[t[a[i]]]=i;
			t[a[i]]=i;
		}
	cout<<sum<<"\n";
	For(i,1,n)cout<<ans[i]<<" ";
	cout<<"\n";
}
int main()
{
	IOS;
	int T;cin>>T;
	while(T--)solve();

	return 0;
}
```

---

