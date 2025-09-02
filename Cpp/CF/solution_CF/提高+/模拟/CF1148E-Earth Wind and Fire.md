# Earth Wind and Fire

## 题目描述

有 $n$ 块石头排布在一条数轴上。初始时，第 $i$ 块石头位于坐标 $s_i$。同一个位置上可能有多块石头。

你可以进行零次或多次如下操作：

- 选择两块编号为 $i$ 和 $j$ 的石头，满足 $s_i \leq s_j$，选择一个整数 $d$（$0 \leq 2d \leq s_j - s_i$），将第 $i$ 块石头的位置替换为 $s_i + d$，将第 $j$ 块石头的位置替换为 $s_j - d$。也就是说，将两块石头相互靠近。

你希望通过若干次操作，使所有石头最终位于 $t_1, t_2, \ldots, t_n$ 这些位置。石头的顺序无关紧要——你只需要最终石头的位置的多重集合与 $t_1, t_2, \ldots, t_n$ 的多重集合相同即可。

请判断是否可以通过上述操作实现目标，如果可以，请构造一种操作方案。你不需要最小化操作次数。

## 说明/提示

请参考第一个样例。

- 第一次操作后，石头的位置为 $[2, 2, 6, 5, 9]$。
- 第二次操作后，石头的位置为 $[2, 3, 5, 5, 9]$。
- 第三次操作后，石头的位置为 $[2, 5, 5, 5, 7]$。
- 最后一次操作后，石头的位置为 $[4, 5, 5, 5, 5]$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
2 2 7 4 9
5 4 5 5 5
```

### 输出

```
YES
4
4 3 1
2 3 1
2 5 2
1 5 2```

## 样例 #2

### 输入

```
3
1 5 10
3 5 7
```

### 输出

```
NO```

# 题解

## 作者：duyi (赞：3)

## 题解 CF1148E Earth Wind and Fire

发现：如果有解，总存在一种移动方式，使得任意时刻，各个石子的相对位置顺序不变。也就是说**排好序**后，$s_i$这个位置上的石头，最后一定会移动到$t_i$的位置。因为你手动模拟一下就会发现，只要存在某两个石子的运动轨迹交叉，把它们终点交换以后，一定还是可行的。

设$\delta_i=t_i-s_i$，也就是第$i$个石子的位移。显然，有解的一个必要条件是$\sum\delta_i=0$。也就是向左移的和向右移的距离和要相等。

但这个条件并不充分。例如$\delta_1<0$的时候，显然是无解的，但可能还是满足$\sum\delta_i=0$这个条件。我们发现，向右走（$\delta_i>0$）的石子一定要在向左走（$\delta_i<0$）的石子左边，才能一起操作。具体来说，可以用**括号序列**来理解这个过程（向右走一步是左括号，向左走一步是右括号）。因此，我们得出另一个条件是：$\delta$数组的前缀和，要始终$\geq 0$。

总结地说，【所有石子的位移是一个能完美匹配的括号序列】是有解的充分必要条件。这等价于满足我们前面提出的两点：(1) $\sum\delta_i=0$；(2) $\delta$数组的前缀和，要始终$\geq 0$。

然后我们也可以用类似于括号序列匹配的方法来构造答案。从左向右扫描。维护一个栈。如果当前是向右移的石子，就入栈。如果当前是向左移的石子，就和栈里的石子匹配。显然，匹配时，两个石子的运动轨迹不可能交叉（因为$s$, $t$都是排好序后匹配的），所以只需要对两个石子到各种终点的路程取$\min$即可：要么当前石子走到终点，要么栈顶走到终点并将其弹掉。

时间复杂度$O(n)$。

参考代码：

```cpp
//problem:CF1148E
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int MAXN=3e5;
int n,d[MAXN+5],sta[MAXN+5],top;
struct Stone_t{
	int pos,id;
}a[MAXN+5],b[MAXN+5];
bool cmp(Stone_t a,Stone_t b){return a.pos<b.pos;}
struct Oper_t{
	int i,j,d;
	Oper_t(int _i,int _j,int _d){
		i=_i;j=_j;d=_d;
	}
};

int main() {
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i].pos,a[i].id=i;sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)cin>>b[i].pos,b[i].id=i;sort(b+1,b+n+1,cmp);
	ll sum=0;
	for(int i=1;i<=n;++i){
		d[i]=b[i].pos-a[i].pos;
		sum+=d[i];
		if(sum<0){cout<<"NO"<<endl;return 0;}
	}
	if(sum!=0){cout<<"NO"<<endl;return 0;}
	cout<<"YES"<<endl;
	vector<Oper_t>ans;
	for(int i=1;i<=n;++i){
		if(d[i]>0)sta[++top]=i;
		else if(d[i]<0){
			while(top){
				int delta=min(a[i].pos-b[i].pos,b[sta[top]].pos-a[sta[top]].pos);
				a[i].pos-=delta;
				a[sta[top]].pos+=delta;
				ans.pb(Oper_t(a[sta[top]].id,a[i].id,delta));
				if(a[i].pos==b[i].pos)break;
				--top;
			}
			assert(a[i].pos==b[i].pos);
		}
	}
	cout<<SZ(ans)<<endl;
	for(int i=0;i<SZ(ans);++i){
		cout<<ans[i].i<<" "<<ans[i].j<<" "<<ans[i].d<<endl;
	}
	return 0;
}
```





---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1148E)

## 思路

两篇题解好像都是神奇的括号匹配，不过这题有更简单的思路。

我们发现 $t$ 的顺序是我们自己定义的，所以我们让小的 $s_i$ 去匹配小的 $t_i$，也就是让 $s$ 排一遍序，$t$ 排一遍序。

然后我们设 $delta_i$ 表示 $s_i-t_i$ 的值，我们发现题目中的改变操作就相当于令 $delta_i+d,delta_j-d$，不难发现若我们改变数对 $i,j$ 且满足 $delta_i<0,delta_j>0$，那么修改操作一定合法，为什么呢，拆一拆柿子即可，也可以感性理解，留给读者自己思考。

于是我们从左往右扫，若 $delta_i<0$，找到若干个 $j$ 其中 $delta_j>0$，维护一个指针暴力更改即可。

时间复杂度 $\mathcal O(n)$，修改次数小于等于 $n$。

## 码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=1e6+10;
int t[N],delta[N];
struct node{int w,id;}s[N];
struct answ{int x,y,w;};vector<answ>Ans;
inline bool cmp(node x,node y){return x.w<y.w;}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n;cin>>n;int res=0;
    for (int i=1;i<=n;++i) cin>>s[i].w,s[i].id=i,res+=s[i].w;
    for (int i=1;i<=n;++i) cin>>t[i],res-=t[i];
    if (res){cout<<"NO\n";return 0;}
    sort(s+1,s+n+1,cmp);
    sort(t+1,t+n+1);
    for (int i=1;i<=n;++i) delta[i]=s[i].w-t[i];
    int l=1;while (delta[l]<=0 && l<=n) ++l;
    for (int i=1;i<=n;++i){
        int ccf=-delta[i];
        if (!ccf) continue;
        while (delta[l]<=0 && l<=n) ++l;
        if (ccf<0 || l==n+1){cout<<"NO\n";return 0;}
        while (ccf){
            int flg=0;while (delta[l]<=0) ++l;
            flg=1;int delt=min(ccf,delta[l]);
            ccf-=delt;delta[i]+=delt;delta[l]-=delt;
            Ans.push_back({s[i].id,s[l].id,delt});
            if (!flg || l==n+1){cout<<"NO\n";return 0;}
        }
    }
    cout<<"YES\n";
    cout<<Ans.size()<<'\n';
    for (auto i:Ans) cout<<i.x<<' '<<i.y<<' '<<i.w<<'\n';
    return 0;
}
```

---

## 作者：DiDi123 (赞：0)

对于这道题我们可以先把 $s_i$ 和 $t_i$ 都排个序。很显然的，挪石子的过程不会改变它们的相对位置，所以我们需要做的就是把每个 $s_i$ 变成 $t_i$。我们令 $p_i=s_i-t_i$，对于一次操作，我们相当于选择三个数 $i,j,d(i\leq j)$，并使得 $p_i+=d,p_j-=d$。我们尝试构造出一种合法的操作方案。我采用了**双指针+贪心**的办法，每次选取最近的两个 $i,j$ 满足 $i<j,p_i\leq0,p_j\geq0$，然后把 $p_i$ 和 $p_j$ 中一个数变到满足条件。如果操作完后发现仍有 $p_i\neq0$，那么就输出 `NO`。

那么这样为什么正确呢？假设这个序列是合法的，考虑进行完一轮操作的状态，这时候我们的 $r$ 停在了一个位置，那么这个位置一定满足 $p_j\geq 0$ 且 $\forall i<j,p_i\leq 0$。如果通过我们的方法无法更新这个 $r$，说明 $l>r$，而此时小于 $r$ 的部分一定还有 $p$ 能够更新这个 $r$，就和我们每次选最近的矛盾了。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define MAXN 300010
struct node
{
	int x,y,z;
}ans[MAXN<<1];
typedef pair<int,int> pa;
pa a[MAXN];
int t[MAXN],n,s1,s2,tt;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i].fi,a[i].se=i;
	for(int i=1;i<=n;i++) cin>>t[i];
	sort(a+1,a+1+n),sort(t+1,t+1+n);
	for(int l=1,r=1;l<=n && r<=n;)
	{
		while(l<=n && a[l].fi>t[l]) l++;
		while(r<=n && a[r].fi<t[r]) r++;
		if(l>n || r>n || l>r) break;
		if(a[r].fi-t[r]<=t[l]-a[l].fi)
		{
			ans[++tt]={a[l].se,a[r].se,a[r].fi-t[r]};
			a[l].fi+=a[r].fi-t[r],a[r].fi=t[r],r++;
		}
		else
		{
			ans[++tt]={a[l].se,a[r].se,t[l]-a[l].fi};
			a[r].fi-=t[l]-a[l].fi,a[l].fi=t[l],l++;
		}
	}
	for(int i=1;i<=n;i++)
		if(a[i].fi!=t[i])
		{
			puts("NO");
			return 0;
		}
	puts("YES");
	cout<<tt<<endl;
	for(int i=1;i<=tt;i++) cout<<ans[i].x<<' '<<ans[i].y<<' '<<ans[i].z<<endl;
}
```


---

## 作者：kouylan (赞：0)

首先，通过观察样例我们可以发现，将两个序列排好序以后，原来的第 $i$ 项就对应最终的第 $i$ 项。我们就可以设 $d_i=b_i-a_i$，表示第 $i$ 项需要移动多少。又因为每一步操作是一个 $+d$，一个 $-d$，所以总和不变，即 $\Sigma d_i=0$。

然后我们又发现，我们是不可能让较小的往左移，较大的往右移的，所以一个 $d_i>0$ 的右边是肯定有 $d_i<0$ 的，并且 $d_i<0$ 不可能出现在 $d_i>0$ 的左边。这让我们联想到了括号串，这也类似，只有当 $d$ 序列的前缀和均大于 $0$ 时，才合法。

判断出合法之后，就需要构造方案了。我们还是跟括号串一样开一个栈，如果 $d_i>0$ 就入栈，如果 $d_i<0$ 就从栈中弹出对应大小的值，记录一下方案即可。这样每个元素进栈一次出栈一次，时间复杂度是 $O(n)$ 的，并且步数不可能超过 $5n$。

下面是 AC 代码
```cpp
/*
Codeforces 1148E
*/
#include <bits/stdc++.h>
using namespace std;

#define int long long

int n,d[300005];
struct ston{
	int p,u;
	bool operator < (const ston b) const
	{
		return p<b.p;
	}
}a[300005],b[300005];
vector<int> ans1,ans2,ans3;
int top,sk[300005];

signed main()
{
	cin>>n;
	for(int i=1;i<=n;scanf("%lld",&a[i].p),a[i].u=i,i++);
	for(int i=1;i<=n;scanf("%lld",&b[i].p),b[i].u=i,i++);
	sort(a+1,a+1+n), sort(b+1,b+1+n);
	for(int i=1;i<=n;i++)
		d[i] = b[i].p-a[i].p;
	int sum=0;
	for(int i=1;i<=n;i++)
	{
		sum += d[i];
		if(sum<0)
			return puts("NO"), 0;
	}
	if(sum!=0)
		return puts("NO"), 0;
	puts("YES");
	for(int i=1;i<=n;i++)
	{
		if(d[i]>0)
			sk[++top] = i;
		else if(d[i]<0)
		{
			while(top)
			{
				int dis=min(d[sk[top]],-d[i]);
				ans1.push_back(a[sk[top]].u), ans2.push_back(a[i].u);
				ans3.push_back(dis);
				d[sk[top]] -= dis, d[i] += dis;
				if(d[sk[top]]==0)
					top--;
				if(d[i]==0)
					break;
			}
		}
	}
	cout<<ans1.size()<<endl;
	for(int i=0;i<ans1.size();i++)
		printf("%lld %lld %lld\n",ans1[i],ans2[i],ans3[i]);
	
	return 0;
}
```

祝大家 AC 愉快！

---

