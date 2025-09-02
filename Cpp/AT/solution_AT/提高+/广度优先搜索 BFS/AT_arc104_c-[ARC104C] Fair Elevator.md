# [ARC104C] Fair Elevator

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc104/tasks/arc104_c

下の階から順に $ 1,\ 2,\ \ldots,\ 2N $ の番号がついた $ 2N $ 階から成る建物があります。

この建物のエレベーターが $ 1 $ 度だけ $ 1 $ 階から $ 2N $ 階まで動きました。

この途中で、 $ N $ 人が乗り降りしました。人 $ i\ (1\ \leq\ i\ \leq\ N) $ は、それぞれエレベーターに $ A_i $ 階で乗り、$ B_i $ 階で降りました。ただし、$ 1\ \leq\ A_i\ <\ B_i\ \leq\ 2N $ であり、それぞれの階で乗り降りした人はただ $ 1 $ 人です。

また、この $ N $ 人は気難しいため、以下の条件が満たされていました。

- 人 $ i\ (1\ \leq\ i\ \leq\ N) $ がエレベーターに乗っているとき、他の人が乗り降りした回数を $ C_i\ (=\ B_i\ -\ A_i\ -\ 1) $ で表すと、次の条件が成り立つ
  - 人 $ i $ と人 $ j $ が同時にエレベーターに乗っていた瞬間が存在するならば、$ C_i\ =\ C_j $ である

$ A,\ B $ は記録されていましたが、残念なことに、記録の一部が消えてしまいました。$ A_i,\ B_i $ が消えている場合は $ -1 $ として与えられます。

また、残っている記録も誤っている可能性があります。

残っている記録に矛盾しないような $ A,\ B $ の組み合わせが存在するかどうか判定してください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 100 $
- $ A_i\ =\ -1 $ または $ 1\ \leq\ A_i\ \leq\ 2N $
- $ B_i\ =\ -1 $ または $ 1\ \leq\ B_i\ \leq\ 2N $
- 入力は全て整数である

### Sample Explanation 1

例えば、$ B_1\ =\ 3,\ A_2\ =\ 2,\ A_3\ =\ 5 $ であった場合、全ての条件を満たします。 この場合、人 $ 1,\ 2 $ が同時にエレベーターに乗っている瞬間がありますが、$ C_1\ =\ C_2\ =\ 1 $ であるので問題ありません。

### Sample Explanation 2

人 $ 1,\ 2 $ が同時にエレベーターに乗っている瞬間がありますが、$ C_1\ =\ 2,\ C_2\ =\ 0 $ なのでいずれかの情報が誤っています。

### Sample Explanation 3

記録は全て残っているように見えますが、明らかに誤っています。

## 样例 #1

### 输入

```
3
1 -1
-1 4
-1 6```

### 输出

```
Yes```

## 样例 #2

### 输入

```
2
1 4
2 3```

### 输出

```
No```

## 样例 #3

### 输入

```
2
4 1
2 4```

### 输出

```
No```

# 题解

## 作者：james1BadCreeper (赞：7)

先考虑几个基本条件：必须有 $b>a$，每一个位置最多有一个人上下，否则显然不合法。

发现 $n\le 100$，因此可以想的暴力一点。想要给 $-1$ 的位置填数字不太好搞，那么就依次考虑楼层，给楼层安排上这一层上或者是下的人。

设 $f(i)$ 代表考虑前 $i$ 层楼是否可以做到合法，初始时 $f(0)=1$，目标为 $f(2n)$。转移显然是：

$$
f(i)=\vee\{f(j-1)\wedge \text{calc}(j,i)\}(1\le j<i,2\mid i-j+1)
$$

注意区间长度一定要是 $2$ 的倍数，否则是不可能合法的（根本填不进去）。

现在问题就是如何实现判断区间合法的 `calc` 函数。显然这段区间必须是"封闭"的当中的任何位置都不可以跑到区间外面去。再就是必须在前半段上电梯，后半段下电梯，否则必定可以划分成更小的区间。此时上下电梯的位置必须是前半段中的第 $i$ 个和后半段中的第 $i$ 个，这样才能保证坐电梯的层数是相等的。

时间复杂度 $O(n^3)$。

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int n;
int a[105], b[105];
int cnt[205], p[205];
bool f[205];

bool calc(int L, int R)
{
    for (int i = L; i <= R; ++i) {
        // 在此处下，上来的地方小于 L
        if (p[i] < 0 && a[-p[i]] != -1 && a[-p[i]] < L) return false;
        // 在此处上，下去的地方大于 R
        if (p[i] > 0 && b[p[i]] != -1 && b[p[i]] > R) return false;
    }
    int half = (R - L + 1) >> 1;
    for (int i = L; i <= L + half - 1; ++i) {
        if (p[i] < 0) return false; // 前半段下，不行
        if (p[i + half] > 0) return false; // 后半段上，不行
        if (p[i] && p[i + half] && p[i] + p[i + half]) return false; // 距离不相等，不行
    }
    return true;
}

int main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", a + i, b + i);
        if (a[i] != -1 && b[i] != -1 && a[i] >= b[i]) return puts("No"), 0;
        if (a[i] != -1) ++cnt[a[i]], p[a[i]] = i;
        if (b[i] != -1) ++cnt[b[i]], p[b[i]] = -i;
    }
    n <<= 1;
    for (int i = 1; i <= n; ++i)
        if (cnt[i] > 1) return puts("No"), 0;
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = ((i & 1) ? 2 : 1); j <= i; j += 2)
            if (f[j - 1]) f[i] |= calc(j, i);
    puts(f[n] ? "Yes" : "No");
    return 0;
}
```

---

## 作者：Ace_FutureDream (赞：2)

这里提供一个 $O(n^2)$ 的做法。

首先，分析题目易得最后的电梯一定是可以分为若干段，且每段都是 $(x,y),(x+1,y+1),\dots,(x+k,y+k)$ 这个样子的。我们把 $x\sim (x+k)$ 叫做第一分段，把 $y\sim (y+k)$ 叫做第二分段。

那么我们可以考虑一个状态：$f_{i,j,0/1}$ 表示前 $i$ 层电梯，目前段的长度 $k=j$，且当前属于第一分段或第二分段时是否可行。

然后考虑转移，分两种情况：

第一种：当前层已经有人占领了，那么可以直接枚举段的长度，看是否能接上，然后分开转移即可。

第二种：当前层还没有人占领。考虑这个楼层作为左端点的情况，那么 $f_{i,j,0}$ 可以分两种情况转移。第一种是 $a_k=-1$ 且 $b_k=-1$，这种情况需要满足 $i+j-1$ 不能已经被人占领了。第二种是 $a_k=-1$ 且 $b_k\ne -1$，这种情况需要满足 $b_k=i+j-1$。如果这两种情况满足任意一种，那么 $f_{i,j,0}$ 可以从 $f_{i-1,j,0}$ 或 $Or^{2n}_{k=1}\ f_{i-1,k,1}$（$Or$ 表示或），然后对于右端点同理。

答案即为 $Or^{2n}_{i=1}\ f_{2n,i,1}$。

然后来计算一下复杂度，首先第一种情况是 $O(n^2)$，然后第二种情况你可以发现每个 $j$ 对应的合法左端点和右端点最多只有一个，所以只需要预处理出来即可，复杂度也为 $O(n^2)$。

综上所述，复杂度为 $O(n^2)$。

## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

int mp[210],a[110],b[110],f[210][210][2],n;
int mp2[210],mp3[210];
void rp(int i){
	if(mp[i]<=2*n){
		int j=mp[i];
		int d=0;
		for(int k=0;k<=2*n;k++)if(f[i-1][k][1])d=1;
		for(int k=0;k<=2*n;k++){
			if(b[j]==-1&&mp[i+k+1]==0&&a[j]+k+1<=2*n){
				f[i][k][0]|=f[i-1][k][0];
				f[i][k][0]|=d;
			}else if(b[j]!=-1&&b[j]-a[j]-1==k){
				f[i][k][0]|=f[i-1][k][0];
				f[i][k][0]|=d;
			}
		}
	}else{
		int j=mp[i]-2*n;
		for(int k=0;k<i-1;k++){
			if(a[j]==-1&&mp[i-k-1]==0){
				f[i][k][1]|=f[i-1][k][0];
				f[i][k][1]|=f[i-1][k][1];
			}else if(a[j]!=-1&&b[j]-a[j]-1==k){
				f[i][k][1]|=f[i-1][k][0];
				f[i][k][1]|=f[i-1][k][1];
			}
		}	
	}	
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i]>>b[i];
		if(mp[a[i]]){
			cout<<"No\n";
			return 0;
		}
		if(a[i]!=-1)mp[a[i]]=i;
		if(mp[b[i]]){
			cout<<"No\n";
			return 0;
		}
		if(b[i]!=-1)mp[b[i]]=i+2*n; 
	}
	f[0][0][1]=1;
	for(int i=1;i<=2*n;i++){
		if(mp[i]){
			rp(i);
			continue;
		}
		int tot=0;
		for(int j=1;j<=n;j++){
			if(a[j]==-1&&b[j]==-1)tot++;
			if(a[j]==-1&&b[j]!=-1)mp2[b[j]]=1;
			if(a[j]!=-1&&b[j]==-1)mp3[a[j]]=1;
		}
		int d=0;
		for(int j=0;j<=2*n;j++)if(f[i-1][j][1])d=1;
		for(int j=0;j<=2*n;j++){
			if(tot&&mp[i+j+1]==0&&i+j+1<=2*n){
				f[i][j][0]|=f[i-1][j][0];
				f[i][j][0]|=d;
			}else if(mp2[i+j+1]){
				f[i][j][0]|=f[i-1][j][0];
				f[i][j][0]|=d;
			}
		}
		for(int j=0;j<i-1;j++){
			if(tot&&mp[i-j-1]==0){
				f[i][j][1]|=f[i-1][j][0];
				f[i][j][1]|=f[i-1][j][1];
			}else if(mp3[i-j-1]){
				f[i][j][1]|=f[i-1][j][0];
				f[i][j][1]|=f[i-1][j][1];
			}
		}
	}
	int ans=0;
	for(int i=0;i<=2*n;i++)ans|=f[2*n][i][1];
	if(ans)cout<<"Yes\n";
	else cout<<"No\n";
	return 0;
}
```

---

## 作者：肖翔 (赞：2)

这题有点神，反正我对这种布尔值的动态规划一般都想不到。

首先当然保证输入合法，即每个位置只能有一个人上或下。

考虑构造一个方案，但是限制很多，做起来十分繁琐。

注意到题目只要求判断是否合法。

然后根据套路，考虑 $ dp_{i} $ 表示 $ [1,i] $ 的楼层是否可以合法。

转移比较好想，可参见 @james1BadCreeper 的博客

即枚举最后一个区间与前面区间的断点，判断前面的区间是否合法与最后一个区间是否合法。

重点落在了判断最后一个区间是否合法上。

先把代码给出，给一个写起来清晰点的做法。

（输入部分比较冗杂，为了大致的美观单独分了一个函数）


```cpp
#include<bits/stdc++.h>
using namespace std;
bool dp[1050];
const int maxn=205;
int n;int a[maxn],b[maxn];
int wh[maxn],p[maxn];
inline void init(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&b[i]);
		if(a[i]!=-1&&b[i]!=-1&&a[i]>=b[i]){
			puts("No");
			exit(0);
		}
		if(a[i]!=-1){
			if(p[a[i]]){
				puts("No");
				exit(0);
			}
			else p[a[i]]=i;
		}
		if(b[i]!=-1){
			if(p[b[i]]){
				puts("No");
				exit(0);
			}
			else p[b[i]]=i;
		}
	}
}

inline bool cal(int l,int r){
	int mid=(r-l+1)>>1;
	for(int i=l,j=l+mid;j<=r;i++,j++){
		if(p[i]&&p[j]&&p[i]!=p[j])return 0;	
		if(p[i]&&b[p[i]]==i)return 0;
		if(p[j]&&a[p[j]]==j)return 0;
	}
	return 1;
}
int main(){
	init();
	dp[0]=1;dp[1]=0;
	for(int i=2;i<=n*2;i++){
		for(int j=i-2;j>=0;j-=2){
			if(dp[j]&&cal(j+1,i)){
				dp[i]=1;
				break;
			}
		}
	}
	if(dp[2*n])puts("Yes");
	else puts("No");
	return 0;
}
```

在输入的同时，先标记好每一个位置已经被谁占了。

若 $ p_{i}=j $，则说明第 $ i $ 层楼被 $ j $ 这个人上电梯或下电梯用了。
 
并在此时顺便处理了显然不合法的情况。

到了 $ cal(l,r) $ 的时候，用了其他大佬在题解里提到的结论：这一个区间里的人乘坐距离都相同。则对于区间里的每个人 $ x $， 应当满足他一定能乘坐到 $x+k$，即 $ x $  转移到  $ x+k $ 这个操作是合法的。我们枚举了区间左右边界，可以确定  $ k=(r-l+1)/2 $
 
实现，类似归并排序，用两个指针 $i,j$ 扫过去，以 $i$ 指代 $x$，以 $j$ 指代 $i+k$。不合法情况有三:
 
 + 对于某个 $ x $，$ x+k $ 已经被使用过了，且在 $ x+k $ 处的不是他 
 
 + 某个人在前半段下电梯
 
 + 某个人在后半段上电梯
 
第一种是因为上面的推理，后两种显然无法保证人在区间里面。
 
（如果人在后半段才上电梯却仍可以在区间里，那么这个区间一定可以按照这个人为界，划分为前后两个更小的区间。）
 
 对应着代码里的三个判断并返回 $0$



最后判断一下 $dp_{2n}$ 就做完了。

思考题：可以发现把 init 里的第一个特判删了也不影响结果（所以上面没提），为什么？   （答案在 cal 后面两个不合法情况里）


---

## 作者：StarRoam (赞：1)

我们前面现将诸如 $a_i \ge b_i$ 以及一个位置不止出现了一次的方案特判不合法。

我们记 $f_i$ 表示：前 $i$ 层是否合法。

有：

$$f_i=\exist \ \ f_{j} \ \ and \ \ calc(j+1,i)  $$

对与一个合法的方案，$i$ 与 $j$ 一定是偶数，且容易发现对于 $[j+1,i]$ 这一个区间，上电梯的人一定是在 $[j+1,mid]$，否则一定可以拆成类似的两个区间。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e2+5;
int n,a[N],b[N];
int num[N<<1],cnt[N<<1];
bool f[N<<1];
bool calc(int l,int r){
	int mid=(l+r)>>1;
	for(int i=l;i<=r;i++)
	{
		if(num[i]<0&&a[-num[i]]!=-1&&a[-num[i]]<l) return false;
		if(num[i]>0&&b[num[i]]!=-1&&b[num[i]]>r) return false;
	}
	int len=(r-l+1)>>1;
	for(int i=l;i<=l+len-1;i++)
	{
		if(num[i]<0) return false;
		if(num[i]>0&&num[i+len]<0&&num[i+len]+num[i]!=0) return false;
	}
	return true;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i]>>b[i];
		if(a[i]!=-1&&b[i]!=-1&&a[i]>=b[i]){
			cout<<"No";
			return 0;
		}
		if(a[i]!=-1) num[a[i]]=i,cnt[a[i]]++;
		if(b[i]!=-1) num[b[i]]=-i,cnt[b[i]]++;
	}
	n<<=1;
	for(int i=1;i<=n;i++)
	{
		if(cnt[i]>1){
			cout<<"No";
			return 0;
		}
	}
	f[0]=true;
	for(int i=2;i<=n;i+=2)
	{
		for(int j=0;j<i;j+=2)
			f[i]|=(f[j]&calc(j+1,i));
	}
	if(f[n]==true) cout<<"Yes";
	else cout<<"No";
	return 0;
}
```

---

## 作者：GGapa (赞：1)

### [ARC104C] Fair Elevator

https://www.luogu.com.cn/problem/AT_arc104_c

感觉很好想也很好写的 DP 做法，实现方法不太一样。

先把无解的判掉，定义 $F(i)$ 为，考虑前 $i$ 层，最少需要用到多少个 $(-1, -1)$ 使得能够填完，如果 $F(2n) \le cnt$，则合法，反之亦然，其中 $cnt$ 为输入中有多少个 $(-1, -1)$。

借个图，如果一个区间能够合法，其一定如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/sknkas92.png)

那么对于一个区间我们判断它要用多少个 $(-1, -1)$ 就只需要扫一遍看一看有没有符合要求的对即可，转移是背包的转移，代码中为了方便使用了 set，时间复杂度为 $O(n ^ 3 \log n)$，似乎可以做到 $O(n ^ 3)$。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
using LL = long long;
using VI = vector<int>;

constexpr int INF = 1e9;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    set<pair<int, int>> s;

    int cnt = 0;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        if(x > y && x != -1 && y != -1) return cout << "No" << '\n', 0;
        if(x == -1 && y == -1) {
            cnt++;
            continue;
        }
        if(s.count({x, y})) return cout << "No" << '\n', 0;
        s.insert({x, y});
    }

    auto check = [&](int r, int j) {
        int l = r - (j + 1) * 2 + 1;

        int ret = 0;
        rep(i, l, r - (j + 1)) 
            if(!s.count({-1, i + j + 1}) && !s.count({i, -1}) && !s.count({i, i + j + 1})) ret++;
        return ret;
    };

    vector<int> F(n * 2 + 1, INF);
    F[0] = 0;
    rep(i, 1, 2 * n) rep(j, 0, i) {
        if(i - (j + 1) * 2 < 0) break;
        F[i] = min(F[i], F[i - (j + 1) * 2] + check(i, j));
    }
    
    cout << (F[2 * n] <= cnt ? "Yes" : "No") << '\n';
    return 0;
}
```

---

## 作者：chenzhiyou12 (赞：1)

来考古了，发现题解区好多大佬的题解不适合像我这样的新手宝宝，于是来发一篇适合新手的题解。

在拿到题之后，我们通常会开始模拟一些样例，争取得到一些性质，并想想类似于能不能贪心之类的。

所以不难发现：转化为区间问题，一个满足题意的区间应该是形如这样的：

![形如这样的](https://cdn.luogu.com.cn/upload/image_hosting/7wq7r8nz.png)

写成形式化的就是：

原区间由若干个小区间首尾连接而成，每个小区间 $[l,r]$ 的长度为偶数，且包含若干个区间，分别为 $[l, l + (r - l + 1) / 2],[l + 1, l + 1 + (r - l + 1 / 2)] \ldots [l + (r - l + 1) / 2 - 1, r]$。也就是若干个长度相等的区间顺次排开。

我们得到了一个性质，那么怎么入手这个题本身呢？我们观察题本身，是个判定性问题，再观察数据范围，$n \leq 100$。先想想贪，发现不对，因为有些 $(-1,-1),(a,-1),(-1,b)$ 可以有多种取法（可能会把 Yes 判成 No）。

所以再考虑动规，按照我的习惯，先把最终的答案表示出来，从而得出状态设计。$f_i$ 表示到第 $i$ 个坐标时，是否有解，最终答案就是 $f_{2n}$。考虑是否可以转移，发现转移可以接受 $O(n^2)$ 的复杂度，优势在我！

发现我们之所以要动态规划，为了解决贪心多种取法的问题，所以其实我们在转移的时候就是尝试所有的取法即可。具体来说，我们可以尝试从 $f_j$ 来转移，如果 $f_{j-1}=true$ 且 $[j,i]$ 合法，就可以转移。那么剩下的问题就是判 $[j,i]$ 是否合法了。

判断一个区间是否合法，其实就是判断这个区间中的每个小区间是否合法就行了。一共有几种情况：

- 左右端点都没有要求：直接就行了，因为可以连在一起。
- 对左端点或者右端点有要求，但是对另一个端点没有要求：只要这个端点并没有 $(a,b)$ 式的连接（它是一个 $(-1,b)$ 或者 $(a,-1)$ 就可以。
- 对于左右端点都有要求：两个端点正好配成一对。

然后就做完了，不懂的请看代码和注释。\
注意对于 $(a,-1)$ 类型的限制，$a$ 只能放在左端点上，需要判一下。$(-1,b)$ 的同理。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define For(i, j, k) for (int i = j; i <= k; ++ i)
#define Rof(i, j, k) for (int i = j; i >= k; -- i)
#define ll long long
#define db double
#define vi vector<int>
#define pb push_back
#define pii pair<int, int>
#define mkp make_pair

const int N = 210;

int n, a[N], b[N], mp[N], lk[N];
bool dp[N] = {false};
int st[N];
// lk 表示配对，st 表示有没有要求 

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);

	cin >> n;
	int m = n * 2;
	memset(lk, -1, sizeof(lk));
	For (i, 1, n) {
		cin >> a[i] >> b[i];
		if (a[i] >= b[i] && b[i] != -1) { // 特判无解 
			cout << "No\n";
			return 0;
		}
		if (mp[a[i]]) { // 特判无解 
			cout << "No\n";
			return 0;
		}
		if (mp[b[i]]) { // 特判无解 
			cout << "No\n"; 
			return 0;
		}
		if (a[i] == -1 && b[i] == -1) { continue; }
		if (a[i] != -1 && b[i] != -1) {
			lk[a[i]] = b[i];
			lk[b[i]] = a[i];
			st[a[i]] = st[b[i]] = 3;
		}
		if (a[i] != -1 && b[i] == -1) {
			st[a[i]] = 1;
		} 
		if (a[i] == -1 && b[i] != -1) {
			st[b[i]] = 2;
		}
		
		if (a[i] != -1) { mp[a[i]] ++ ;}
		if (b[i] != -1) { mp[b[i]] ++ ;}
	}
	
	dp[0] = 1;
	For (i, 1, m) {
		bool flg = false;
		For (j, 1, i - 1) {
			if (!dp[j - 1] || (i - j + 1) % 2) { continue; }
			// 可以发现，长度如果不是偶数，一定无解 
			bool flg2 = true;
			For (k, 1, (i - j + 1) / 2) {
				int p1 = j + k - 1, p2 = j + (i - j + 1) / 2 + k - 1;
				// 判断小区间 [p1, p2] 是否能匹配 
				if (!st[p1] && !st[p2]) { // 都没有要求 
					continue;
				}
				if (!st[p1] && st[p2] && lk[p2] == -1 && st[p2] == 2) { // 左端点有要求 
					continue;
				}
				if (!st[p2] && st[p1] && lk[p1] == -1 && st[p1] == 1) { // 右端点有要求 
					continue;
				}
				if (st[p1] && st[p2] && lk[p1] == p2) { // 两个都有要求 
					continue;
				}
				flg2 = false; 
				break;
			} 
			if (flg2) {
				flg = true;
				break;
			}
		}
		dp[i] = flg;
	}
	cout << (dp[m] ? "Yes\n" : "No\n") << '\n';

	return 0;     
}

```

复杂度 $O(n^3)$。

---

## 作者：Starrykiller (赞：1)

**这是一篇非 dp 的题解。** 但是在本题的数据上表现不劣于 dp。

约定：本篇题解中，区间 $[l,r]$ 的**长度**定义为 $r-l+1$。

首先我们可以观察到一些性质。

若有解，则一组**两两相交**的区间族是这样的：

$$[l,r],[l+1,r+1],\cdots,[l+k,r+k]$$

其中 $l+k\lt r\implies 0\le k\le r-l-1$。

题目中给定了每个位置的限制（只能做左端点，只能做右端点，或者左右端点均可）。注意到对于每个位置而言，限制很多，所以合法的状态是很少的，我们可以直接搜索。

具体地说，首先判掉无解的情况。然后依次考虑 $i=1,2,\cdots,2n$，若 $i$ 没有被使用，则尝试让 $i$ 作为左端点，枚举右端点 $r$，若 $[i,r]$ 加入后合法，就继续向下搜索。

更为具体地，我们定义一个数组 $a$，$a_i$ 表示覆盖 $i$ 位置的区间的长度值（特别地，$a_i=0$ 表示没有要求）。加入 $[l,r]$ 后合法，当且仅当 $\forall i\in [l,r]$，$a_i=0$ 或 $a_i=r-l+1$。若加入 $[l,r]$ 后合法，我们就修改 $a$ 数组后继续向下搜索，回溯时撤销修改。

本题细节还是比较多的，需要仔细考虑。特别感谢 **skz** 的 debug。

[My implemention](https://atcoder.jp/contests/arc104/submissions/52143133)。写得可能比较丑陋，谨慎参考。

---

## 作者：User_Unauthorized (赞：1)

## 题意

有 $N$ 个区间 $[a_i,b_i](a_i<b_i)$，都是 $[1,2n]$ 内的整数且互不相同（$a_i\ne b_j,a_i\ne a_j,b_i\ne b_j$）。

现在给定一些 $a$ 和 $b$ 的值，剩下不知道的用 $-1$ 表示。问是否存在一种替换掉 $-1$ 的方案，使得：若两个区间**有交**，那么它们**长度相等**。

即 $\forall i,j,[a_i,b_i]\cap[a_j,b_j]\ne \varnothing\Rightarrow b_i-a_i=b_j-a_j$。

$N\le 100$。

## 题解

首先特判掉一些一定无解的情况，例如 $\exist i \neq j, a_i = a_j$，$a_i \ge b_i$ 等等。

可以发现若存在区间 $[l, r]$，设 $L = r - l$，那么对于任意 $l \ge i < r$，一定有区间 $[i, i + L]$ 存在。即整个区间 $[l, r + L - 1]$ 内的子区间内的元素都会被钦定值并且合法。

可以发现考察一个区间 $[l, r]$ 能否合法存在的复杂度为 $\mathcal{O}(N)$ 的。由于 $N$ 很小，故我们可以以 $\mathcal{O}(N^3)$ 处理出所有可以被钦定合法的区间。

根据上述分析，可以发现被钦定合法的区间一定补交，因此若一个区间没有被钦定合法，我们可以枚举其中的一个断点并判断左右两个区间是否可以合法，进而实现转移，复杂度为 $\mathcal{O}(N^3)$。

## Code

```cpp
#include <bits/stdc++.h>

typedef int valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<bool> bitset;
typedef std::vector<bitset> BitMatrix;

bool check(valueType N, ValueVector A, ValueVector B) {
    bitset exist(2 * N + 1, false);

    for (valueType i = 1; i <= N; ++i) {
        if (A[i] != -1 && B[i] != -1 && A[i] >= B[i])
            return false;

        if (A[i] != -1) {
            if (exist[A[i]])
                return false;

            exist[A[i]] = true;
        }

        if (B[i] != -1) {
            if (exist[B[i]])
                return false;

            exist[B[i]] = true;
        }
    }

    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    valueType const M = 2 * N;

    ValueVector A(N + 1), B(N + 1);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> A[i] >> B[i];

    if (!check(N, A, B)) {
        std::cout << "No" << std::endl;

        return 0;
    }

    ValueVector left(M + 1, -1), right(M + 1, -1), belong(M + 1, -1);
    bitset exist(M + 1, false);

    for (valueType i = 1; i <= N; ++i) {
        if (A[i] != -1) {
            right[A[i]] = B[i];
            exist[A[i]] = true;
            belong[A[i]] = i;
        }

        if (B[i] != -1) {
            left[B[i]] = A[i];
            exist[B[i]] = true;
            belong[B[i]] = i;
        }
    }

    BitMatrix F(M + 1, bitset(M + 1, false));

    for (valueType l = 1; l <= M; ++l) {
        for (valueType r = l + 1; r <= M; ++r) {
            valueType len = r - l;

            if (r + len - 1 > M)
                continue;

            bool ok = true;

            for (valueType i = l; i < r && ok; ++i) {
                if (right[i] != -1 && right[i] != i + len)
                    ok = false;

                if (left[i + len] != -1 && left[i + len] != i)
                    ok = false;

                if (exist[i] && exist[i + len] && belong[i] != belong[i + len])
                    ok = false;
            }

            if (ok)
                F[l][r + len - 1] = true;
        }
    }

    for (valueType len = 1; len <= M; ++len) {
        for (valueType l = 1; l + len <= M; ++l) {
            valueType const r = l + len;

            for (valueType mid = l + 1; mid < r; ++mid) {
                if (F[l][mid] && F[mid + 1][r]) {
                    F[l][r] = true;

                    break;
                }
            }
        }
    }

    if (F[1][M])
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;
}
```

---

## 作者：Liyunze123 (赞：0)

# 题解
考虑 $f_i$ 表示前 $i$ 层是否满足条件。首先，若第 $i$ 层是某人上，那肯定不对。所以，枚举这层是某人下的情况。

考虑这个人在哪一层上的。设为 $i-L$ 层。那 $i-2L+1$ 到 $i$ 的上下情况就确定了，前半段全是上，后半段全是下，就连后半段下的顺序和上的一样。判断是否合法即可。
# 几个可能会被质疑的点澄清
## 后半段有上时也可能最终合法
举一个例子。$i=6,L=3$，此时第 $5$ 层是上，则第 $8$ 层下。考虑 $f_8$，这种情况会被转移到。
## 第 $i$ 层下的那个人不在第 $i-L$ 层上
可证无论如何判断函数返回 `false`。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,a[110],b[110],cnt[210],p[210],f[210];
int g(int l,int r){
	for(int w=l;w<=r;w++)if(p[w]<0&&a[-p[w]]!=-1&&a[-p[w]]<l||p[w]>0&&b[p[w]]>r)return 0;
	int h=(r-l+1)/2;
	for(int w=l;w<=l+h-1;w++)if(p[w]<0||p[w+h]>0||p[w]&&p[w+h]&&p[w]+p[w+h])return 0;
	return 1;
}
int main(){
	scanf("%d",&n);
	for(int w=1;w<=n;w++){
		scanf("%d%d",&a[w],&b[w]);
		if(b[w]!=-1&&a[w]>b[w]){printf("No");return 0;}
		if(a[w]!=-1)cnt[a[w]]++,p[a[w]]=w;
		if(b[w]!=-1)cnt[b[w]]++,p[b[w]]=-w;
	}
	n*=2,f[0]=1;
	for(int w=1;w<=n;w++)if(cnt[w]>1){printf("No");return 0;}
	for(int w=1;w<=n;w++)for(int x=1;x<w;x++)if((w-x+1)%2==0&&f[x-1])f[w]|=g(x,w);
	printf("%s",((f[n])?"Yes":"No"));
	return 0;
}
```

---

## 作者：henrytb (赞：0)

这个题数据范围告诉我们是 dp。然后就是发现性质了。。。

经过观察发现，对于一段有交的东西，一定长成这样的形状：

![此处应有图](https://cdn.luogu.com.cn/upload/image_hosting/sknkas92.png)

这个是怎么发现的呢？考虑从边角开始看这个东西长什么样。假如说以 $1$ 为左端点的区间长得很长，那么以他中间的为左端点的首先不能被包含，然后还得长得和以 $1$ 为左端点的这个一样长。那就只能长成这样了。然后断掉之后，下一个又是一个完全一样的子问题，这样就可以预处理一下可以做到这个程度的区间们，然后直接 dp。

我蠢了，写了个区间 dp。事实上直接平方的一维 dp 就行了。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 105;
int n, a[N], b[N];
int f[N << 1], id[N << 1];
bool valid[N << 1][N << 1];
bool dp[N << 1][N << 1];
inline bool calc(int l, int r) {
    if ((r - l + 1) & 1) return 0;
    int ned = (r - l + 1) >> 1;
    rep(i, l, l + ned - 1) {
        if (f[i] && f[i] != 1) return 0;
        if (f[i + ned] && f[i + ned] != 2) return 0;
        if (f[i] && f[i + ned] && id[i] != id[i + ned]) return 0;
        if (f[i] && (~b[id[i]]) && b[id[i]] != i + ned) return 0;
        if (f[i + ned] && (~a[id[i + ned]]) && a[id[i + ned]] != i) return 0;
    }
    return 1;
}
int main() {
    scanf("%d", &n);
    rep(i, 1, n) {
        scanf("%d%d", &a[i], &b[i]);
        if ((~a[i]) && (~b[i]) && a[i] >= b[i]) { puts("No"); return 0; }
        if (~a[i]) {
            if (f[a[i]]) { puts("No"); return 0; }
            f[a[i]] = 1, id[a[i]] = i;
        }
        if (~b[i]) {
            if (f[b[i]]) { puts("No"); return 0; }
            f[b[i]] = 2, id[b[i]] = i;
        }
    }
    rep(i, 1, n + n) rep(j, i + 1, n + n) valid[i][j] = calc(i, j);
    rep(len, 2, n + n) if (len & 1 ^ 1) {
        rep(i, 1, n + n - len + 1) {
            int j = i + len - 1;
            if (len == 2) dp[i][j] = valid[i][j];
            else {
                dp[i][j] = valid[i][j];
                rep(k, i + 1, j - 2) if ((k - i) & 1) {
                    dp[i][j] |= (dp[i][k] & valid[k + 1][j]);
                }
            }
        }
    }
    puts(dp[1][n + n] ? "Yes" : "No");
    return 0;
}
```

---

## 作者：hinin (赞：0)

考虑数轴上连续的一段区间 $[l, r]$，记 $L = r - l + 1$，若该区间内能够满足条件，则显然有：

  * $2 \mid L$。
  * $[i, i + \frac{L}{2}]$ 可以存在于区间集合中。
  * 输入可能多点重合。
  * 若有区间 $[l, ?]$ 或 $[?, r]$，注意不能组成 $[l, r]$。

对于每个人，检查是否存在矛盾：
   
   *   如果 $A_i$ 和 $B_i$ 都存在，且 $A_i \geq B_i$，则不符合题意。
   *   如果 $A_i$ 或 $B_i$ 为 $-1$，进行特殊处理。

需要处理的特判

  *  处理 $A_i $ 或 $B_i $ 缺失的情况，将在电梯中的位置分别设置电梯的最高楼层或空。
  *  处理 $A_i$ 或 $B_i$ 已经被记录过情况，表明有人在这一层上下电梯，不符合题意。

### 代码：
``` cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int, int>

using namespace std;

const int N = 2e2 + 1; 
int n, mat[N], f[N], vls[N]; 

inline int check(int l, int r)
{
	int stp = r - l + 1 >> 1; 
	for(int i = l, j; (j = i + stp) <= r; i ++) {
		bool it = 1 <= mat[i] && mat[i] <= n << 1;
		bool jt = 1 <= mat[j] && mat[j] <= n << 1;
		if(mat[i] == -1 || (it && mat[i] ^ j)
		|| mat[j] == (n << 1 | 1) || (jt && mat[j] ^ i)
		|| (!it && !jt && mat[i] && mat[j])) 
		{ return false; }
	}

	return true; 
}

int main()
{
	ios::sync_with_stdio(false); 
	cin.tie(nullptr); 

	cin >> n; 
	for(int i = 1, a, b; i <= n; i ++) {
		cin >> a >> b; 
		if(~a && ~b && a >= b) {
			cout << "No" << endl; 
			return 0; 
		}
		if (~a && ~b) {
			mat[a] = b;
			mat[b] = a;
		} else if(~a) { mat[a] = n << 1 | 1; }
		else if(~b) { mat[b] = -1; }

		if(~a) {
			if(vls[a]) { 
				cout << "No"; 
				return 0; 
			} vls[a] = true; 
		}
		if(~b) {
			if(vls[b]) { 
				cout << "No"; 
				return 0; 
			} vls[b] = true; 
		}
	}

	f[0] = true; 
	for(int i = 2; i <= n << 1; i += 2) {
		for(int j = 0; j < i && not f[i]; j += 2)
		{ f[i] = f[j] && check(j + 1, i); }
	}

	cout << (f[n << 1] ? "Yes" : "No") << endl; 

	return 0;
}
```

---

