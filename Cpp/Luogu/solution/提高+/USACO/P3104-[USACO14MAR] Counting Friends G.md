# [USACO14MAR] Counting Friends G

## 题目描述

FJ 的 $N(2 \le N \le 500)$ 头奶牛加入了社交网络“牛书”。

每一头奶牛在牛书上都有一个或多个朋友，于是 FJ 做了一个列表，列出了每头奶牛的朋友数量。但在这一过程中，他错误地将一个额外的数加入了列表（所以最终的列表包含 $N+1$ 个数，而不是预期的 $N$ 个数）。

请帮助 FJ 找出哪一个数可能是错误的那个数。

## 说明/提示

#### 样例解释

FJ 有四头奶牛。其中两头有一个朋友，两头有两个朋友，一头有三个朋友（当然，其中一个数字是错误的，不应出现在列表上）。

移除 FJ 列表上的第一个数字，余下的序列是 $2,2,1,3$，是合法的。如果我们把四头奶牛命名为 $A,B,C,D$，就有 $(A,B),(A,C),(A,D),(B,C)$ 的配对方式符合要求。同样的，移除列表中的第四、第五个数字，也可以形成合法的朋友关系，移除数字 $2$ 则无法形成合法的朋友关系。容易发现，若移除了数字 $2$，剩余的数字为奇数，显然无法形成合法的朋友关系。

## 样例 #1

### 输入

```
4 
1 
2 
2 
1 
3 
```

### 输出

```
3 
1 
4 
5 
```

# 题解

## 作者：小手冰凉 (赞：9)

这道题我们可以这么做


先从大到小排序，那么当前的操作是将序列中最大的变成0，然后顺次每个减一，可以发现如果一直这么做，最后全部是0就是可行解（为什么？显然啊（划掉））


但是有一个问题，这道题直接sort是最劣O(n3logn)的复杂度，十有八九要T（而且我真的T了QAQ）


并且可以发现每次做完后原序列变成 0+有序+有序 ，所以可以归并优化时间复杂度到O(n3)，稳过


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int a[N],b[N],ans[N];
int t[N];
int n,tot;
bool com(int a,int b){return a>b;}//比较
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n+1;i++)scanf("%d",&a[i]);//读入
    for(int i=1;i<=n+1;i++){
        int k=0;
        for(int j=1;j<=n+1;j++)if(j!=i)b[++k]=a[j];
        sort(b+1,b+n+1,com);
        while(b[1]>0){//执行
            for(int j=2;j<=b[1]+1;j++)b[j]--;
            int l1=2,l2=b[1]+2;
            int r1=b[1]+1,r2=n;
            b[1]=0;k=0;
            while(l1<=r1&&l2<=r2){//归并
                if(b[l1]<=b[l2])t[++k]=b[l2],l2++;
                else t[++k]=b[l1],l1++;
            }
            while(l1<=r1)t[++k]=b[l1],l1++;
            while(l2<=r2)t[++k]=b[l2],l2++;
            for(int j=1;j<=n;j++)b[j]=t[j];
        }
        sort(b+1,b+n+1,com);
        if(b[n]==0)ans[++tot]=i;//判定
    }
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++)//输出
        printf("%d\n",ans[i]);
    return 0;
}
```

事实上还不够稳，经过@just_do_it的帮助，成功优化了许多常数
使用桶进行存储，因为每次都是最大的那几个数被减1，所以相同的数只要O(1)进行操作。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
    ll x = 0,f = 1;char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){x = x*10+ch-'0'; ch = getchar();}
    return x*f;
}

inline void write(ll x)
{
    if(x<0)putchar('-'),x=-x;
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
inline void writeln(ll x)
{
    write(x);
    puts("");
}
const int N = 505;
int a[N];
int c[N],d[N];
vector<int> b[N];
int n,tot;
int ans,p[N];
bool vis[N];
int num,to,op;

signed main(){
 	freopen("wrong.in","r",stdin);
 	freopen("wrong.out","w",stdout);
    n = read();
    for(int i = 1;i <= n+1;++i){
        int x = read();
        if(x >= n){++num; to = i; continue;}
        ++a[x];
        b[x].push_back(i);
        tot += x;
    }
    // printf("%d\n", num);
    if(num > 1){puts("0"); return 0;}
    else if(num == 1){
        if(tot%2 != 0){ puts("0"); return 0; }
        memcpy(c,a,sizeof(a));
        int top = n-1;
        bool flag = true;
        for(int t = 1;t <= n;++t){
            while(c[top] == 0) --top;	//top当前是最大的数。
            if(top == 0) break;
            int pos = top;
            c[top]--;		//当前数被取出
            for(int i = top;i >= 1;--i){
                if(pos > c[i]){
                    pos -= c[i];
                }else{
                    c[i-1] += pos; c[i] -= pos;
                    pos = 0;
                    for(int j = i;j <= top-1;++j){
                        c[j] += c[j+1];
                        c[j+1] = 0;
                    }
                    break;
                }
            }
            if(pos > 0){
                flag = false;
                break;
            }
        }
        if(flag){
            puts("1");
            printf("%d\n", to);
            return 0;
        }else{
            puts("0");
            return 0;
        }
    }
    for(int i = 0;i < n;++i){
        if(a[i] > 0){
            if((tot-i)%2 != 0) continue;
            for(int k = 0;k < n;++k) c[k] = a[k];	//将a转存到c中
            --c[i];	//该数字少一个
            int top = n-1;
            bool flag = true;
            for(int t = 1;t <= n;++t){
                while(c[top] == 0) --top;	//top当前是最大的数。
                if(top == 0) break;	//最大的数是0，说明已结束
                int pos = top;
                c[top]--;
                for(int k = top;k >= 1;--k){
                    if(pos > c[k]){
                        pos -= c[k];
                    }else{
                        c[k-1] += pos; c[k] -= pos;
                        pos = 0;
                        for(int j = k;j <= top-1;++j){
                            c[j] += c[j+1];
                            c[j+1] = 0;
                        }
                        break;
                    }
                }
                if(pos > 0){
                    // int sum = 0;
                    // for(int j = 1;j <= top;++j) sum += c[j];
                    // printf("# %d %d %d %d\n",i,pos,top,sum);
                    flag = false;
                    break;
                }
            }
            if(flag){	//说明删去当前数是可行的
                for(unsigned int j = 0;j < b[i].size();++j)
                    p[++ans] = b[i][j];
            }
        }
    }
    // puts("");
    printf("%d\n", ans);
    sort(p+1,p+ans+1);
    for(int i = 1;i <= ans;++i)
        printf("%d\n", p[i]);
    }
    return 0;
}
```


---

## 作者：大菜鸡fks (赞：5)

这题的话没什么可以多解释的。
主要就是要敢于打暴力。

solution：
我们可以枚举哪个数字出错了。转为对剩下数字的判定性问题。
容易发现我们要判断的是一个图的合法性：给出出度判断能否构成。

我们可以设想，连边必然是先连出度大的，再连出度小的（如果你先连出度小的。你出度大的边的选择就少了。那么方案的构造就很容易失败了。）于是我们每次连完一个点之后就排一次序。直至整个序列为0.
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=505;
int n,a[maxn];
inline void init(){
	scanf("%d",&n);
	for (int i=1;i<=n+1;i++){
		scanf("%d",&a[i]); 
	}
}
int ans,b[maxn],flag,q[maxn];
inline void solve(){
	for (int i=1;i<=n+1;i++){
		int tot=0;
		for (int j=1;j<=n+1;j++){
			if (j!=i) b[++tot]=a[j]; 
		}
		flag=1;
		for (int j=1;j<=n;j++){
			sort(b+1,b+1+n); int temp=n-1;
			while (b[temp]&&b[n]){
				b[n]--; b[temp]--; temp--;
			}
			if (b[n]) {
				flag=0; break;
			}
		}
		if (flag) q[++ans]=i;
	}
	printf("%d\n",ans);
	for (int i=1;i<=ans;i++) printf("%d\n",q[i]);
}
int main(){
	init();
	solve();
	return 0;
} 
```

---

## 作者：gesong (赞：4)

题目传送门：[P3104 [USACO14MAR] Counting Friends G](https://www.luogu.com.cn/problem/P3104)。
# 思路

首先我们花费 $O(n)$ 的代价枚举错误的朋友数，然后我就把题目转化为：给定 $n$ 个节点的度数，判断是否存在一个没有重边的合法的图。

考虑一种算法：每次都选择两个数 $a_i,a_j$，将这两个数均减一。如果最后所有数都为 $0$ 则合法，否则就不合法，由于不能有重边，因此每次选择的 $(i,j)$ 不能重复。

我们贪心的想：如果每次都先选择最大的 $a_i$，从大到小枚举其余的数，如果这个数不为 $0$，则这两个数都减去 $1$，直到 $a_i=0$，如果所有的数都枚举完了但是 $a_i$ 仍不为 $0$ 则不合法。

这样我们就得到了一个 $O(n^3\log n)$ 的做法。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int n,a[N],b[N];
int ans[N],tot;
int main(){
	scanf("%d",&n);
	for(int i=0;i<=n;i++) scanf("%d",&a[i]);
	for(int i=0;i<=n;i++){
		int cnt=0;
		for(int j=0;j<=n;j++) if(i!=j) b[++cnt]=a[j];
		stable_sort(b+1,b+n+1,greater<int>());
		int flag=1;
		for(int k=n;k>1;k--){
			for(int j=2;j<=k&&b[1]&&b[j];j++) b[1]--,b[j]--;
			if(b[1]){flag=0;break;} 
			for(int i=1;i<k;i++) b[i]=b[i+1];
			stable_sort(b+1,b+k,greater<int>());
		}
		if(flag) ans[++tot]=i+1;
	}
	printf("%d\n",tot);
	for(int i=1;i<=tot;i++) printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：Light_az (赞：4)

## 详细图解和样例讲解

这道题目难度评的有点高，应该是一道绿色题目。本题难度可能在于题意不容易理解，题目大概意思是一共有 $n + 1$ 个点，其中有一个点是多余的，问你那些点有可能是多余的。

忽略第一行，其中在第 $1$ 到 $n+1$ 行中 ，$a_i$ 代表编号为 $i$ 的点链接了多少条边，为什么会有多余的点呢？首先我们来分析一下样例：



- 当 $1$ 号点多余时，这张图是长这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/56kkdas3.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- 当 $4$ 号点多余时，这张图是长这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/69so9vko.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- 当 $5$ 号点多余时，这张图是长这样子的：

![](https://cdn.luogu.com.cn/upload/image_hosting/jzde69p4.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

- 当其它点多余时，无法组成一个图。

发现了吗 ？我们只需要用 $O(n+1)$ 的时间去枚举哪一个点不合法，然后再判断剩下的点构成的图是否合法即可。接下来，我们将问题转化成 $n$ 个点是否可以构成一张图，我们可以采用排序加模拟的方式，下面会演示一遍完整流程：

- 当 $1$ 号点是多余的，即使用 $2 $ 到 $ 5$ 号点构图时：

先进行边数排序，发现 $5$ 号点连接了 $3$ 条边，是最多的，因此我们先连接它：

![](https://cdn.luogu.com.cn/upload/image_hosting/cblz44jh.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

连接之后 $5$ 号点已经连接完了， $1,2,3$ 号各减少一条边。

我们再次进行排序，发现 $2$ 号点连接了 $1$ 条边，是最多的，因此我们连接它：

![](https://cdn.luogu.com.cn/upload/image_hosting/263c8g6d.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

连接之后 $1,2,3$ 号点已经连接完了，发现没有剩余边数，因此方案成立。

以此类推，我们可以求出其他方案是否合法，但是在判断过程中我们要注意：

- 保证连接的点还有剩余边数允许连接，我们不能连接一个边数为 $0$ 的点。

- 在特殊情况下，快速排序会退化成线性复杂度，因此我们可以使用归并排序。

最后，就是完整的代码实现了：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define F(i,j,n) for(int i=j;i<=n;i++)
#define Tr(v,e) for(int v:e)
#define D double
#define ps push_back
#define Test ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)
using namespace std;
const int N=1e6+10,NN=1e4+10;
ll n,m,k,x,y,u,v,w,cnt=0,t=0,l,r,len,T;
ll mini=INT_MAX,maxi=0,Mod;
string s1,s2;
ll a[N],b[N],ans[N];
void copy(ll id){
	ll t=0;
	F(i,1,n+1){
		if(i==id) continue;//去掉 i 点
		b[++t]=a[i];
	}
}
bool cmp(ll a,ll b){
	return a>b;
}
void print(){
	F(i,1,n) cout<<b[i]<<" ";
	cout<<"\n";
}
ll check(){
	ll k=n;
	stable_sort(b+1,b+1+n,cmp);//归并排序
	while(k){
		ll id=2;//从第 2 小的开始
		while(b[1]&&b[id]) b[1]--,b[id]--,id++;//两个点都有剩余的边允许连接，双方边数减少，进行下一条边
		if(b[1]) return 1;//有剩余边，不合法
		stable_sort(b+1,b+1+k,cmp);//归并排序
		k--;//有一个元素值变成 0，可以省略它的排序
	}
	return 0;//合法
}
int main(){
    Test;//输入优化
	cin>>n;
	F(i,1,n+1) cin>>a[i];
	F(i,1,n+1){
		copy(i);//枚举没有 i 点的情况
		if(!check()) cnt++,ans[++t]=i;//不合法情况多了一种
	}
	cout<<cnt<<"\n";
	F(i,1,cnt) cout<<ans[i]<<"\n";
	return 0;
}

```


---

## 作者：bliss_bug (赞：3)

## 题解
这道题我们可以将 $(n+1)$ 个边依次去掉，然后分别判断去掉后是否能满足。注意到一点， $n$ 个奶牛的朋友之和必定为偶数，所以去掉的那个数值的奇偶性必定与 $(n+1)$ 个数值之和的奇偶性相同。


接下来很明显的，尽量将朋友多的和朋友多的匹配，所以先从大到小排序，将第一个奶牛和后面的奶牛依次匹配，如果匹配结束，第一个奶牛还有剩余，则此情况必然不可能成立；否则匹配完之后再按照 $O(n)$ 复杂度的归并排序给数组重新排好序。依次循环 $n$ 次（当然如果数组中最大值已经为 $0$ ，则直接跳出循环）。

简单说一下为什么这样做是正确的，因为奶牛无法完成匹配只可能有一种情况，就是当某一个奶牛与其他所有还可以有朋友的奶牛都匹配结束后，此奶牛依然还有剩余的朋友要匹配。所以奶牛要尽量先与朋友多的奶牛相匹配，如果先与朋友较少的奶牛匹配，则会加大朋友较多的奶牛无法完成匹配的可能性。具体严格证明应该可以用数学归纳法来证，这里就不详述了。
## 代码
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int n, a[502], b[500],c[500],sum=0;
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++)
	{
		scanf("%d", &a[i]);
		sum += a[i];
	}
	int num = 0, res[501];
	for (int i = 1; i <= n + 1; i++)
	{
		if (sum % 2 != a[i] % 2)
			continue;
		int index = 0;
		for (int j = 1; j <= n + 1; j++)
			if (j != i)
				b[index++] = a[j];
		sort(b, b + n, [](const int x, const int y) {
			return x > y;
			});
		bool flag = 1;
		for (int j = 1; j <= n; j++)
		{
			if (b[0] == 0)
				break;
			int in = 1;
			while (b[0] > 0 && b[in] > 0)
			{
				b[0]--;
				b[in++]--;
			}
			if (b[0] > 0)
			{
				flag = 0;
				break;
			}
			int p = 1, q = in, cnt = 0;
			while (p < in && q < n)
				if (b[p] > b[q])
					c[cnt++] = b[p++];
				else
					c[cnt++] = b[q++];
			while (p < in)
				c[cnt++] = b[p++];
			while (q < n)
				c[cnt++] = b[q++];
			for (int k = 0; k < n - 1; k++)
				b[k] = c[k];
			b[n - 1] = 0;
		}
		if (flag)
			res[num++] = i;
	}
	printf("%d\n", num);
	for (int i = 0; i < num; i++)
		printf("%d\n", res[i]);
	return 0;
}
```


---

## 作者：ZPB2011 (赞：2)

# Counting Friends G

[题目传送门](https://www.luogu.com.cn/problem/P3104)。

读完题看眼数据，发现可以用 $\mathcal O(n^3\log n)$ 暴力，于是可以判断如果删掉一个点之后这个图的合法性。

题目中给出了每个点的出度，只需要将除多余的点外每个点按出度排序，然后挨个连上并将出度减一，最后判断是否的每个点的出度都为 $0$，那么这个图即为合法，增加答案 `cnt` 并记录。

AC code:
```cpp
#include <iostream>
#include <algorithm> 
using namespace std;

int a[1005], b[1005], ans[1005];

int main() {
	int n, cnt = 0;
	cin >> n;
	for(int i = 1; i <= n + 1; i++) cin >> a[i];
	for(int i = 1; i <= n + 1; i++) {
		int pos = 0;
		for(int j = 1; j <= n + 1; j++) {
			if(j != i) b[++pos] = a[j];
		}
		bool flag = true;
		for(int j = 1; j <= n; j++) {
			sort(b + 1, b + n + 1);
			int tail = n - 1;
			while(b[tail] != 0 && b[n] != 0) {
				b[n]--;
				b[tail]--;
				tail--;
			}
			if(b[n]) {
				flag = 0;
				break;
			}
		}
		if(flag) ans[++cnt] = i;	
	}
	cout << cnt << endl;
	for(int i = 1; i <= cnt; i++) cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：yzxoi (赞：2)

[$$\large\texttt{My Blog}$$](https://yzxoi.top/archives/1624)
## Description
> [题目链接](https://www.luogu.com.cn/problem/P3104)

$n(1\leq n\leq 500)$ 头奶牛都有一个或一个以上的朋友。 记录每头牛的朋友数，但他傻不小心混入了一个错的数字，请找出。
## Solution
不得不说O2大法好（

![](https://i.loli.net/2021/02/09/gQz3knJMipAGfbo.png)

~~然而为啥我的暴力是跑得最慢的呀（~~

首先我们可以考虑一下暴力怎么打。

直接枚举哪一个点是多余的，然后暴力判断。

可是暴力判断怎么写呢（别跟我说你要写 $dfs$

显然对于每一个需要匹配的点来说，肯定贪心地优先匹配剩下的需要匹配最多的那个点。

那么只要开个堆，每次找剩下匹配最大的即可。

然后我写了个暴力交上去，开了个 O2 就过了

然后这个暴力的最劣复杂度为 $O(N^3logN)$。

所以接下来考虑正解，最起码得把这个 $log$ 优掉。

显然我们可以开一个桶来代替堆，每次直接从大到小枚举，能合并的直接合并即可。

注意合并的时候要先记录下，不然下传的时候会产生冲突。

然后就一瞬拿到了最优解つ﹏⊂。

![](https://i.loli.net/2021/02/09/jFRbTMcQhYy691l.png)
## Code
### 暴力
```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=510;
int n,a[N],vis[N],b[N],g[N];
vector<int> Ans;
#define P pair<int,int>
#define MP make_pair
#define Dx(x) a[(x)]-vis[(x)]
#define p j.second
priority_queue<P> q;
vector<P>t;
I void find(int x){if(Dx(x)>min(n-x+1,q.size())) return ;t.clear();P j;W(vis[x]<a[x]&&!q.empty()) j=q.top(),q.pop(),p^x&&Dx(p)>0&&((++vis[p])^a[p]&&(t.push_back(MP(Dx(p),p)),0),vis[x]++);for(auto o:t) o.second>x&&(q.push(o),0);}//寻找可以匹配的点
int main(){
	RI i,j,flg;read(n);for(i=1;i<=n+1;i++) read(a[i]),g[a[i]]=-1;for(i=1;i<=n+1;i++) if(~g[a[i]]) g[a[i]]&&(Ans.push_back(i),0);else{//开个桶，记忆化是否之前做过
		W(!q.empty()) q.pop();for(memset(vis,0,sizeof(vis)),vis[i]=a[i],j=1;j<=n+1;j++) vis[j]<a[j]&&(q.push(make_pair(Dx(j),j)),0);
		for(flg=0,j=1;j<=n+1;j++){vis[j]<a[j]&&(find(j),0);if(vis[j]^a[j]){flg=1;break ;}};g[a[i]]=!flg;if(!flg) Ans.push_back(i);
	}sort(Ans.begin(),Ans.end()),write(Ans.size()),pc('\n');for(auto j:Ans) write(j),pc('\n');return 0;
}
```
### 正解
```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define W while
#define I inline
#define RI register int
#define LL long long
#define Cn const
#define gc getchar
#define D isdigit(c=gc())
#define pc(c) putchar((c))
#define min(x,y) ((x)<(y)?(x):(y))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
namespace Debug{
	Tp I void _debug(Cn char* f,Ty t){cerr<<f<<'='<<t<<endl;}
	Ts I void _debug(Cn char* f,Ty x,Ar... y){W(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	Tp ostream& operator<<(ostream& os,Cn vector<Ty>& V){os<<"[";for(Cn auto& vv:V) os<<vv<<",";os<<"]";return os;}
	#define gdb(...) _debug(#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
namespace FastIO{
	Tp I void read(Ty& x){char c;int f=1;x=0;W(!D) f=c^'-'?1:-1;W(x=(x<<3)+(x<<1)+(c&15),D);x*=f;}
	Ts I void read(Ty& x,Ar&... y){read(x),read(y...);}
	Tp I void write(Ty x){x<0&&(pc('-'),x=-x,0),x<10?(pc(x+'0'),0):(write(x/10),pc(x%10+'0'),0);}
	Tp I void writeln(Cn Ty& x){write(x),pc('\n');}
}using namespace FastIO;
Cn int N=510;
int n,a[N],b[N],g[N],stk[N],top,f[N];
vector<int> Ans;
int main(){
	RI i,j,k,flg,d,t;read(n);for(i=1;i<=n+1;i++) read(a[i]),g[a[i]]=-1;for(i=1;i<=n+1;i++) if(~g[a[i]]) g[a[i]]&&(Ans.push_back(i),0);else{
		for(top=0,memset(stk,0,sizeof(stk)),j=1;j<=n+1;j++) i^j&&(stk[a[j]]++,top=max(top,a[j]));
		for(flg=0,j=top;j>=1;j--) W(stk[j]--){
			for(k=j,t=j;k>=1&&t;k--) f[k]=min(stk[k],t),stk[k]-=f[k],t-=f[k];
			for(k=j;k>=1;k--) stk[k-1]+=f[k],f[k]=0;if(t){flg=1;break ;}
		}if(g[a[i]]=!flg) Ans.push_back(i);
	}write(Ans.size()),pc('\n');for(auto j:Ans) write(j),pc('\n');return 0;
}
```

---

## 作者：Linshey (赞：2)

主题：审题、根据每个点的度数判断图的合法性

# 1.首先这题强调了审题的重要性

我多次弄错了题意
，多次修改，甚至没看样例就开始做题。

# 2.根据每个点的度数判断图的合法性

我记得我们1月一号的数学考试上有完完整整的这道题

只不过当时我的方法从现在来看是错的

正确做法是：每次挑出剩余度数最多的那个点，将它和第二、第三、……连边，如果连不完就判错。这里实际上涉及一个动态排序的问题，可以用平衡树实现，$O(m*logn)$

但其实有$O(m + n^2)$的做法:

每处理完一个点，一定有：{刚刚连上的}和{刚刚没连的}各自单调，所以用一个归并就可以$O(n)$动态排序，一共操作n次

$ \color{red}\text{一定要记得是要从大到小} $

---

## 作者：denominator (赞：1)

> [原题](https://www.luogu.com.cn/problem/P3104)
>
> - 假设有一个 $n$ 个点的图，给出每个点的度数。
> - 现在这个序列不小心添加了一个数值。
> - 请求出删去哪些数值，序列符合题意。

---

## Part \#1 Erdős-Gallai 定理

如果你翻了 2014 年这道题的题解，会发现这样一行字：

> As a further note, valid degree sequences can be characterized using a result known as the Erdos-Gallai Theorem. Using this, the running time can be reduced even further (e.g., to $O(N^2)$).

接下来就来讲讲这个 $\mathcal O(n^2)$ 的解法。首先需要了解提到的 Erdős-Gallai 定理。

设度序列 $\{d_n\}$ 为 $n$ 阶图中所有节点的度 **从大到小排序** 的结果，即 $d_1\geq d_2\geq\cdots\geq d_n\geq0$。

一个序列 $\{d_n\}$ 是度序列，当且仅当以下条件同时成立：

- $2\left|\sum\limits_{i=1}^nd_i\right.$；
- $\sum\limits_{i=1}^kd_i\leq k(k-1)+\sum\limits_{i=k+1}^n\min\{d_i,k\}$。

这个定理的必要性非常好证，即 $k(k-1)$ 为前 $k$ 个节点最多连的边，$\sum\limits_{i=k+1}^n\min\{d_i,k\}$ 为后 $n-k+1$ 个节点与前 $k$ 个节点最多连的边。

Erdős 和 Gallai 证明了这个定理的充分性，但作为一个优秀的 OIer，我们并不需要考虑这一点。

## Part \#2 利用这一结论的做法

令输入从大到小排序。

枚举删的数值，然后直接套上面的公式算就完了，时间复杂度 $\mathcal O(n^3)$。代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int n, a[N], p[N], sum, ans[N], deg[N];
int main () {
	scanf ("%d", &n);
	for (int i = 1; i <= n + 1; i++) {
		scanf ("%d", &a[i]);
		p[i] = i;
		sum += a[i];
	}
	sort (p + 1, p + n + 2, [] (int x, int y) {return a[x] > a[y];});
	for (int d = 1; d <= n + 1; d++) {
		if ((sum - a[p[d]]) & 1) {
			continue;
		}
		deg[0] = 0;
		for (int i = 1; i <= n + 1; i++) {
			if (i == d) {
				continue;
			}
			deg[++deg[0]] = a[p[i]];
		}
		bool flag = true;
		for (int k = 1; k <= n; k++) {
			int ans1 = 0, ans2 = k * (k - 1);
			for (int i = 1; i <= k; i++) {
				ans1 += deg[i];
			}
			for (int i = k + 1; i <= n; i++) {
				ans2 += min (deg[i], k);
			}
			if (ans1 > ans2) {
				flag = false;
			}
		}
		if (flag) {
			ans[++ans[0]] = p[d];
		}
	}
	sort (ans + 1, ans + ans[0] + 1);
	printf ("%d\n", ans[0]);
	for (int i = 1; i <= ans[0]; i++) {
		printf ("%d\n", ans[i]);
	}
	return 0;
}
```

但是考虑到每次的求和式都有很多相同，于是可以预处理。设删除 $x$。

其中，$\sum\limits_{i=1}^kd_i$ 非常好处理，直接求排序后的前缀和，并视情况减掉 $d_x$ 即可。

为维护 $\sum\limits_{i=k+1}^n\min\{d_i,k\}$，我们令 $S_k=\sum\limits_{i=k+1}^{n+1}\min\{d_i,k\}$，这东西可以 $\mathcal O(n^2)$ 预处理。

若 $x<k$，这一项即 $S_{k-1}-\min\{d_k,k-1\}$；否则，即为 $S_k-\min\{d_x,k\}$。于是可以 $\mathcal O(n)$ 判断。

于是总时间复杂度为 $\mathcal O(n^2)$，成为自写作完成（2024/6/17 11:10:53）的最优解。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 510;
int n, a[N], p[N], sum, ans[N], pre[N], suf[N];
int main () {
	scanf ("%d", &n);
	n++;
	for (int i = 1; i <= n; i++) {
		scanf ("%d", &a[i]);
		p[i] = i;
	}
	sort (p + 1, p + n + 1, [] (int x, int y) {return a[x] > a[y];});
	for (int i = 1; i <= n; i++) {
		pre[i] = pre[i - 1] + a[p[i]];
	}
	for (int k = 1; k <= n; k++) {
		for (int i = k + 1; i <= n; i++) {
			suf[k] += min (a[p[i]], k);
		}
	}
	for (int d = 1; d <= n; d++) {
		if ((pre[n] - a[p[d]]) & 1) {
			continue;
		}
		bool flag = true;
		for (int k = 1; k <= n; k++) {
			if (d == k) {
				continue;
			}
			int kt = k - (d < k);
			int ans1 = pre[k] - (d < k) * a[p[d]], ans2 = kt * (kt - 1) + suf[kt] - (d < k) * min (a[kt + 1], kt) - (d > kt) * min (a[p[d]], kt);
			if (ans1 > ans2) {
				flag = false;
				break;
			}
		}
		if (flag) {
			ans[++ans[0]] = p[d];
		}
	}
	sort (ans + 1, ans + ans[0] + 1);
	printf ("%d\n", ans[0]);
	for (int i = 1; i <= ans[0]; i++) {
		printf ("%d\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：kuikuidadi (赞：0)

# 思路
枚举每个数字是否能被删去，然后就是如何判定图是否存在。应该按度数从大到小排序，从最大的顺次向其他点连边（先连度数小的可能会把一些可以和大度数点来连接的点用掉）。但是这个排序每连一次都要做一次，而 $N\le 500$ 的情况下 $O(n^3\log n)$ 并不能过。但是发现度数最多只有 $n$，所以可以桶排。

---

## 作者：P_VICVIC_R (赞：0)

~~顺着生成树标签来的我发现了这一道不错的水题~~

---

### 题意

这道题蓝就蓝在它的题意（以下是机翻）：

![](https://cdn.luogu.com.cn/upload/image_hosting/rjdgaccu.png)

人话+抽象：**把牛想象成点，把朋友关系想象成边**，题意为：有一个 $n$ 个点的联通图，给你 $n+1$ 个度数，其中有一个是多余的，问哪些度数可能是多余的。（即去除该多余数据后连通图依然成立） 

### 思路

看眼数据范围，发现 $n$ 小的可怜，那么我们 $O(n)$ 枚举当第 $i$ 个数据是多余时，判断图是否成立就行。

判断图是否成立也很简单，先将所有 $n$ 个点排序，从最大的依次向小的连边，如果有任意一个点连完所有比它小的点后，度数不为 $0$，那么就不成立，反之成立。

### 代码

```
#include <bits/stdc++.h>
#define itn long long 
using namespace std;
static const int N=1000005;
static const int mod=998244353;
int n,m;
int a[N];
priority_queue<int> ql;//我用的优先队列，减少排序次数。
list<int> li;//临时存储优先队列里的数据。
inline bool judge(){
	while(!ql.empty()){
		int tp=ql.top();//当前度数最大的一个。
		ql.pop();
		for(int i=1;i<=tp;i++){
			if(ql.empty())
				return false;//如果当前度数还没跑完，队列里没点了，说明其他点已经连好了，图不成立。
			if(ql.top()==0){
				ql.pop();
				i--;
				continue;
			}//如果这个点的度数是0，那么出队。
			li.push_front(ql.top()-1);//临时存储。
			ql.pop();
		}
		for(auto i:li){
			ql.push(i);
		}//转移数据。
		li.clear();
	}
	return true;
}
signed main(){
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout.tie(nullptr)->sync_with_stdio(false);
	cin>>n;
	for(int i=1;i<=n+1;i++)
		cin>>a[i];
	vector<int> ans;
	for(int l=1;l<=n+1;l++){
		li.clear();
		while(!ql.empty())
			ql.pop();
		for(int i=1;i<=n+1;i++){
			if(i==l)
				continue;
			ql.push(a[i]);
		}
		if(judge()){
			ans.push_back(l);
		}//图合法说明这个点可以不要
	}
	cout<<ans.size()<<'\n';
	for(auto i:ans){
		cout<<i<<'\n';
	}
	return 0;
}
```

复杂度不大会算，大概不会低于 $O(n^2\log n)$，但是能过……

---

