# Binary Path

## 题目描述

You are given a $ 2 \times n $ grid filled with zeros and ones. Let the number at the intersection of the $ i $ -th row and the $ j $ -th column be $ a_{ij} $ .

There is a grasshopper at the top-left cell $ (1, 1) $ that can only jump one cell right or downwards. It wants to reach the bottom-right cell $ (2, n) $ . Consider the binary string of length $ n+1 $ consisting of numbers written in cells of the path without changing their order.

Your goal is to:

1. Find the lexicographically smallest $ ^\dagger $ string you can attain by choosing any available path;
2. Find the number of paths that yield this lexicographically smallest string.

 $ ^\dagger $ If two strings $ s $ and $ t $ have the same length, then $ s $ is lexicographically smaller than $ t $ if and only if in the first position where $ s $ and $ t $ differ, the string $ s $ has a smaller element than the corresponding element in $ t $ .

## 说明/提示

In the first test case, the lexicographically smallest string is $ \mathtt{000} $ . There are two paths that yield this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/28bc26c21acb39dafc863512440b57a82f70d617.png)In the second test case, the lexicographically smallest string is $ \mathtt{11000} $ . There is only one path that yields this string:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1937B/f024d427300a33d2f71c9946e45249754a59348c.png)

## 样例 #1

### 输入

```
3
2
00
00
4
1101
1100
8
00100111
11101101```

### 输出

```
000
2
11000
1
001001101
4```

# 题解

## 作者：ZhongYuLin (赞：10)

记：$f_{i,j}$ 表示到达位置 $(i,j)$ 时的最小序列，$g_{i,j}$ 表示最小序列数量，显然有：

$$f_{i,j}=\min(f_{i-1,j},f_{i,j-1})+a_{i,j}$$

边界和 $g_{i,j}$ 的维护是平凡的，不会的请去[过河卒](https://www.luogu.com.cn/problem/P1002)。

先考虑使用字符串进行模拟，发现时空复杂度都无法保证。

**注意到：** 一个状态与转移过来的状态有很多重合部分，例如假设 $f_{i,j}$ 从 $f_{i-1,j}$ 转移过来，那么 $f_{i,j}$ 只是在 $f_{i-1,j}$ 后添上 $a_{i,j}$。于是我们选择使用可持久化线段树维护 $f_{i,j}$ 的**哈希**，比较时进行二分即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
using ull=unsigned long long;
const int N=2e5+10;
int ls[N<<6],rs[N<<6],f[2][N],g[2][N];
ull h[N<<6];
bool a[2][N];
int n,cnt;
char c;
void push_up(int p){
    h[p]=(h[ls[p]]*230945+h[rs[p]]*1283)^12;
}
void update(int x,int k,int l,int r,int lst,int &p){
    p=++cnt;ls[p]=ls[lst];rs[p]=rs[lst];h[p]=h[lst];
    if(l==r){h[p]=l*k;return;}
    int mid=l+r>>1;
    if(x<=mid)update(x,k,l,mid,ls[lst],ls[p]);
    else update(x,k,mid+1,r,rs[lst],rs[p]);
    push_up(p);
}
int cmp(int x,int y,int l,int r){
    if(l==r)
        if(h[x]==h[y])return 0;
        else if(h[x]>h[y])return 1;
        else return -1;
    int mid=l+r>>1;
    if(h[ls[x]]==h[ls[y]])return cmp(rs[x],rs[y],mid+1,r);
    return cmp(ls[x],ls[y],l,mid);
}
void out(int l,int r,int p){
    if(l==r){printf(h[p]?"1":"0");return;}
    int mid=l+r>>1;
    out(l,mid,ls[p]);out(mid+1,r,rs[p]);
}
inline int read(){
    int k=0;char c=getchar();
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9')k=(k<<3)+(k<<1)+(c^48),c=getchar();
    return k;
}
void solve(){
    n=read();
    for(int i=1;i<=n;++i){c=getchar();while(c<'0'||c>'9')c=getchar();a[0][i]=c-'0';}
    for(int i=1;i<=n;++i){c=getchar();while(c<'0'||c>'9')c=getchar();a[1][i]=c-'0';}
    update(1,a[0][1],1,n+1,f[0][1],f[0][1]);f[1][1]=f[0][1];
    update(2,a[1][1],1,n+1,f[1][1],f[1][1]);g[1][1]=g[0][1]=1;
    for(int i=2;i<=n;++i)g[0][i]=g[0][i-1],f[0][i]=f[0][i-1],update(i,a[0][i],1,n+1,f[0][i],f[0][i]);
    for(int i=2;i<=n;++i){
        int x=cmp(f[0][i],f[1][i-1],1,n+1);
        if(x==0)f[1][i]=f[0][i],g[1][i]=g[0][i]+g[1][i-1];
        else if(x==1)f[1][i]=f[1][i-1],g[1][i]=g[1][i-1];
        else f[1][i]=f[0][i],g[1][i]=g[0][i];
        update(1+i,a[1][i],1,n+1,f[1][i],f[1][i]);
    }
    out(1,n+1,f[1][n]);puts("");
    printf("%d\n",g[1][n]);
}
int main(){
    int T;for(T=read();T--;)solve();
    return 0;
}
```

不错，这道题有更为优异的做法，但是这种做法扩展性极高，例如在 $n\times n$ 的网格图上、在一张图上，都可以使用这个方法。现在你已经会了最基础的，来试试加强版吧！

[P8860 动态图连通性](https://www.luogu.com.cn/problem/P8860)

[The Classic Problem](https://www.luogu.com.cn/problem/CF464E)

---

## 作者：AK_400 (赞：10)

# [CF1973B](https://codeforces.com/problemset/problem/1937/B) 题解
## 题意： 
给你一个 $n \times 2 (n \le 2 \times 10^5)$ 的矩阵，问你一蚱蜢从 $ (1,1)$ 到 $(2,n)$ 经过的字典序最小的字符串是什么（每次只能向右或向下），有几种方法得到这个字符串。
## 提示 1（建议看之前先思考）
想想从第 $k$ 格向下走和从第 $k+1$ 格向下走有什么区别。
## 提示 2
想想右侧是 `0` 且下方是 `1` 怎么走。
## 提示 3
想想右侧是 `1` 且下方是 `0` 怎么走。
## 题解
发现从第 $k$ 格向下走和从第 $k+1$ 格向下走两种情况在 $k$ 之前和在 $k+1$ 之后是一样的，于是我们贪心地优先选 `0` 。

但是相等怎么办呢？我们发现向右走的选择是包含向下走的，即向右走后可以向右和向下，可向下后只能向右，于是我们优先向右走。

于是我们记向下走最早和最晚分别为 $l$、$r$，那么当在 $i$ 必须向右时，$l\gets i+1$，必须向下时，$r\gets i-1$，且 $l\le r$。

为方便，记 $a$ 为此矩阵，于是第一行为 $s_{1,i}(i\in [0,r-1])+s_{2,j}(j\in[r-1,n-1])$，第二行为$r-l+1$。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n;
string a[2];
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>a[0]>>a[1];
        int l=0,r=n-1;
        for(int i=n-1;i>0;i--){
            if(a[0][i]=='1'&&a[1][i-1]=='0')r=i-1;
        }
        for(int i=0;i<=r;i++){
            if(a[0][i+1]=='0'&&a[1][i]=='1')l=i+1;
        }
        for(int i=0;i<=r;i++){
            cout<<a[0][i];
        }
        for(int i=r;i<n;i++){
            cout<<a[1][i];
        }
        cout<<endl<<r-l+1<<endl;
    }
    return 0;
}
```

---

## 作者：风中の菜鸡 (赞：5)

这本就不是一道困难的题，但大多数人高估了字符串的效率。事实上，字符串的复制与比大小并没有那么快，所以我们只能考虑直接贪心找出最优解，再统计答案。

由于只能向下走一次，所以我们可以直接模拟整个走的过程。开头与结尾已经确定，中间部分我们不妨贪心选择，具体的，当这一步向右比向下优时，我们向右走；当这一步向下比向右优时，我们向下走；向右与向下一样时，向右走肯定不比向下走劣。（这是因为在上面会有更多的选择权）

统计答案是平凡的，只需要枚举从哪里向下走，用哈希比较在这里向下走的答案是否与之前贪到的答案一样就可以了。

[code](https://www.luogu.com.cn/paste/vz82cz8u)

---

## 作者：_299817_ (赞：2)

## Part 0：前言
过题人数比较抽象的一场

## Part 1：思路
首先，我们考虑怎么求出字典序最小的路线。

不难发现，字典序最小是一个贪心问题，我们当先能选择 $0$ 就绝对不选择 $1$。

同时，这题还有一个要点，就是我们只有一次机会能往下走。

于是我们根据这个思想，考虑我们啥时候往下走，这个很简单，只要 $a_{1,i+1}$ 比 $a_{2,i}$ 大的时候往下走即可，剩余的时间往右走。

这段代码比较好写。
```cpp
int flag = 1;
int cnt = 0;
int num;
rep(i, 1, n){
    if(a[1][i + 1] > a[2][i] && flag == 1){
        flag++;
        num = i;
        ans[++cnt] = a[1][i], ans[++cnt] = a[2][i];
    }else{
        ans[++cnt] = a[flag][i];
    }
}
if(flag == 1){
    ans[++cnt] = a[2][n];
    num = n;
}
rep(i, 1, cnt) cout << ans[i];
cout << endl;
```

然后我们就需要考虑它的重复情况了。

这时候还是需要用到我们上述的性质，就是只能往下走一次。

我们画个图，看看不同时间往下走但是最后答案一样需要满足什么条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/v8ckizdj.png)

不难发现，我们如果需要使两个答案相同的话，就要使绿色和红色箭头上的数一一对应。

而且我们也可以发现我们上面求解答案的方法中，往下走的机会一定是最右边的。

于是我们可以从我们求答案时往下走的地方开始往左搜，如果 $a_{1,i} = a_{2,i-1}$ 那么答案加一，否则退出循环。

于是这题我们就做完了。

## Part 2：代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<cstring>
#include<unordered_map>
#include<map>
#include<queue>
#include<stack>
#include<bitset>
#include<list>
#define rep(i, l, r) for(int i = signed(l); i <= signed(r); i++)
#define per(i, l, r) for(int i = signed(l); i >= signed(r); i--)
#define sort stable_sort
#define map unordered_map
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 200010;

int T, n;
int a[10][MAXN];
int ans[MAXN];

int main(){
    #ifdef QwQ_ATM
        freopen("input.in", "r", stdin);
        freopen("output.out", "w", stdout);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    while(T--){
        cin >> n;
        rep(i, 1, 2){
            rep(j, 1, n){
                char c;
                cin >> c;
                a[i][j] = c - '0';
            }
        }
        // cout << a[1][4] << endl;
        int flag = 1;
        int cnt = 0;
        int num;
        rep(i, 1, n){
            if(a[1][i + 1] > a[2][i] && flag == 1){
                flag++;
                num = i;
                ans[++cnt] = a[1][i], ans[++cnt] = a[2][i];
            }else{
                ans[++cnt] = a[flag][i];
            }
        }
        if(flag == 1){
            ans[++cnt] = a[2][n];
            num = n;
        }
        rep(i, 1, cnt) cout << ans[i];
        cout << endl;
        int aans = 1;
        per(i, num, 2){
            if(a[1][i] == a[2][i - 1]) aans++;
            else break;
        }
        cout << aans << endl;
    }
    return 0;
}
```

---

## 作者：wuyin331 (赞：2)

# 题解
这把被吃大分了。

首先分析题目，因为是 $2 \times n$ 的网格，因此肯定存在且仅有一次向下的操作，我们根据这点进行分析。

假设还没进行向下的操作，当前所在网格为 $(1,i)$，且 $i \neq n$。此时我们可以向右或者向下操作。因此如果有 $a_{1,i+1} = a_{2,i}$，那么相当于最小字典序的字符串的个数加一。同时我们要求字典序最小，也就是如果存在 $a_{1,i+1} \neq a_{2,i}$，我们必定要向 $0$ 那边操作，因为是 $2 \times n$ 的网格，如果有 $a_{2,i} = 0$，之后不会有更优的操作了，如果有 $a_{1,i+1} = 0$，那么代表只能往右边操作，而我们字典序最小的字符串个数是由于向下和向右得到的，而此时出现 $a_{1,i+1} = 0$，代表我们之前不能向下操作了，因此我们字典序最小的字符串个数为 $1$。

# 代码
```cpp
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    T = 1;
    cin >> T;

    while (T--)
    {

        string s;
        string t;

        cin>>n;
        cin>>s;
        cin>>t;

        int k=-1,cnt=1;
        for(int i=0;i<n-1;i++){
            if(t[i]!=s[i+1]){
                if(t[i]=='0'){
                    if(k==-1){
                        k=i;
                    }
                    break;
                }
                k=i+1;
                cnt=1;
            }
            if(t[i]==s[i+1]){
                cnt++;
            }
            
        }

        string res;
        if(k==-1) k=n-1,cnt=n;
        for(int i=0;i<=k;i++) res+=s[i];
        for(int i=k;i<n;i++) res+=t[i];

        cout<<res<<'\n';
        cout<<cnt<<'\n';
    }
    return 0;
}
```

---

## 作者：MhxMa (赞：1)

### 题意
题目要求在一个二维网格中，从左上角出发，只能向右或向下移动，到达右下角的格子。网格中的每个格子包含一个二进制数。经过的路径上的数字按顺序连接成一个二进制字符串。现在要根据题意求解两个问题。

字典序是指字符串的大小关系，如果两个字符串长度相同，那么在第一个不同的字符处，较小的字符串对应的字符值要小于较大字符串对应的字符值。  

### 分析
做这道题可以用 dp 求解，当然也可以用贪心，这里只讲 dp 的做法。

读入后，可以将 $a$ 的第一个字符添加到一个临时字符串中（即初始化路径），同时将 $b$ 中的字符添加到这个灵时字符串的末尾（即模拟移动过程），同时使用一个计数器标记至少有多少条路径。

接下来，使用一个队列来跟踪临时字符串中的字符是否需要更改，依次检查+判断：  
- 如果后面的字符比当前字符大，那么我们已经得到了字典序最小的字符串，此时输出字符串和计数器的值，并结束程序。
- 如果后面的字符和当前字符相等，我们增加计数器的值。
- 如果后面的字符比当前字符小，我们将当前字符替换为后面的字符，并将需要更改的字符的下标加入队列中。

遍历队列元素，将队列中下标对应的位置对应的字符替换为 $a$ 中下标相对的的字符，输出即可，输出的即为路径数量。

同时建议使用 char 读入。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[200005], b[200001];
void solv() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	string cur, ans;
	int cnt = 0;
	cur += a[1];
	for (int i = 1; i <= n; i++) {
		cur += b[i];
	}
	ans = cur;
	cnt = 1;
	queue<int> q;
	for (int i = 1; i < n; i++) {
		char pre = cur[i], nxt = a[i + 1];
		if (nxt > pre) {
			cout << cur << endl;
			cout << cnt << endl;
			return;
		} else if (nxt == pre)
			cnt++;
		else {
			cur[i] = nxt;
			q.push(i);
			while (!q.empty()) {
				ans[q.front()] = a[q.front() + 1];
				q.pop();
			}
			cnt = 1;
		}
	}
	cout << ans << endl;
	cout << cnt << endl;
}
int main() {
	int t;
	cin >> t;
	while (t--) {
		solv();
	}
}
```

---

## 作者：Wf_yjqd (赞：1)

容易困于如何压缩 dp 状态忽略了其他做法。

赛时耗时过长。

------------

最终路径一定是第一行的一个前缀和第二行的一个后缀。

在第一行时，若当前位置右边和下边值相同，显然选择右边不劣。

我们找到第一个右边大于下边的位置到第二行，这一定是答案中的一个。

考虑其他答案，一定是在上面方案基础上左移到第二行的列数。

想让路径权值不变，必须满足右边等于左边，而答案个数就是连续满足的个数 $+1$。

复杂度 $\operatorname{O}(n)$。

------------

注意特判第一行最后一个到第二行的走法。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+26;
int T,n,a[2][maxn];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%1d",&a[0][i]);
        for(int i=1;i<=n;i++)
            scanf("%1d",&a[1][i]);
        for(int i=1,j;i<=n;i++){
            printf("%d",a[0][i]);
            if(a[1][i]<a[0][i+1]||i==n){
                for(j=i;j<=n;j++)
                    printf("%d",a[1][j]);
                puts("");
                for(j=i-1;j>=1;j--)
                    if(a[1][j]!=a[0][j+1])
                        break;
                printf("%d\n",i-j);
                break;
            }
        }
    }
    return 0;
}
```

---

