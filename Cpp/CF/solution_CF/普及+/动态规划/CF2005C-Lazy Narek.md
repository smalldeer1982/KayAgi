# Lazy Narek

## 题目描述

$\text{Alice}$ 有 $n$ 个字符串，每个字符串长度为 $m$。

$\text{Alice}$ 会选择 $n$ 个字符串的一个子集，可以为空，将子集中的字符串首尾按原本的相对顺序拼接，然后她会在拼接的字符串中依次查找字符 "n","a","r","e","k"。当这五个字符全被找到后，$\text{Alice}$ 会将自己的分数 $+5$ 然后继续从当前位置向后查找。

之后 $\text{Bob}$ 会扫描整个字符串并查找，如果 $\text{Alice}$ 的查找中有未被访问的 "n","a","r","e" 或 "k"，$\text{Bob}$ 会将自己的分数 $+1$。

请你帮 $\text{Alice}$ 和 $\text{Bob}$ 求出 $\max\{score_{Alice} - score_{Bob}\}$。

## 样例 #1

### 输入

```
4
5 2
nn
aa
rr
ee
kk
1 5
narek
1 4
nare
5 7
nrrarek
nrnekan
uuuuuuu
ppppppp
nkarekz```

### 输出

```
0
5
0
7```

# 题解

## 作者：liugh_ (赞：4)

## [Lazy Narek](https://www.luogu.com.cn/problem/CF2005C)

我们每选一个字符串，都要从上一个选择的字符串以某个字符为结尾来接上来，考虑将此加入状态，于是一个显然的做法是设 $f(i,k)$ 为考虑完前 $i$ 个字符串，以字符 $k$ 为结尾，的最大答案。于是我们可以枚举上一个字符串 $j$ 和上一个结尾的字符 $h$，即
$$
f(i,k)=\max\{0,\max_{j<i} (f(j,h)+w)\}
$$
其中 $w$ 为从 $h$ 的下一个字符循环选择到 $k$ 所能选的最大个数（可能循环多次）。

因为枚举 $i$ 和 $j$，时间复杂度已经来到了 $O(n^2|\Sigma|^2)$，其中 $|\Sigma|=5$。复杂度几乎已经达到上限，我们只能通过比较复杂的预处理来快速检查是否合法。

考虑到我们真的需要 $i$ 这一维吗？实际转移中，$i$ 这一维只需满足 $j<i$ 即可，而这正好与我们枚举的顺序相符，只需记录下转移之前的状态，那么此限制就自然满足了，即设 $f(k)$ 为以字符 $k$ 为结尾，的最大答案。于是有
$$
f(k)=\max\{0,\max(f(h)+w)\}
$$
其中 $w$ 同上。

省去了枚举 $j$，我们有更多时间来更方便地判断转移是否合法了。具体地，从 $h$ 的下一个字符开始，循环依次对当前字符串暴力进行匹配，这部分时间复杂度 $O(m|\Sigma|)$。

至此，我们得到了一个时间复杂度 $O(nm|\Sigma|^2)$ 的做法，其中 $|\Sigma|=5$。

---

## 作者：chenxi2009 (赞：1)

# 思路

发现我们需要把若干个字符串拼接在一起得到最优的字符串，考虑简单动态规划。

由于我们在拼成最后的字符串后，其中某个 `narek` **有可能跨字符串**，比如说 `nare` 和 `k` 拼成之后就多了一个字符串，所以要用 $f_{i,j}$ 表示第 $i$ 个字符串以 `narek` 的第 $j$ 个字符为最后一个被 narek 统计到的字符时最高的分数，对于每个字符串操作一遍即可。思维难度不高，代码实现有些难度。

# 代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int T,n,m,nxt[6] = {0,2,3,4,5,1},cnt1,cnt,s,ans,f[1001][6],maxn[6][2];
char pbm[1001][1001],name[6] = {0,'n','a','r','e','k'};
bool endw[1002][6];
set<char>se;
int main(){
	se.insert('n'),se.insert('a'),se.insert('r'),se.insert('e'),se.insert('k');
	scanf("%d",&T);
	while(T --){
		maxn[0][0] = 0;
		maxn[0][1] = maxn[1][1] = maxn[2][1] = maxn[3][1] = maxn[4][1] = maxn[1][0] = maxn[2][0] = maxn[3][0] = maxn[4][0] = -2e9;
		ans = 0;
		endw[0][0] = true;
		endw[0][1] = endw[0][2] = endw[0][3] = endw[0][4] = false;
		scanf("%d%d",&n,&m);
		for(int i = 1;i <= n;i ++){
			scanf("%s",pbm[i] + 1);
			endw[i][0] = endw[i][1] = endw[i][2] = endw[i][3] = endw[i][4] = false;
			f[i][0] = f[i][1] = f[i][2] = f[i][3] = f[i][4] = -2e9;
			for(int j = 0;j < 5;j ++){
				maxn[j][i % 2] = maxn[j][(i - 1) % 2];
			}
			for(int j = 1;j <= 5;j ++){ 
				s = j,cnt1 = cnt = 0;
				for(int k = 1;k <= m;k ++){
					if(!se.count(pbm[i][k])){
						continue;
					}
					cnt ++;
					if(pbm[i][k] == name[s]){
						s = nxt[s];
						if(s == 1){
							cnt1 ++;
						}
					}
				}
				cnt = cnt1 * 5 - (cnt - cnt1 * 5);
				bool find = false;
				if(maxn[j - 1][(i - 1) % 2] != -2e9){
					f[i][s - 1] = max(f[i][s - 1],maxn[j - 1][(i - 1) % 2] + cnt);
					maxn[s - 1][i % 2] = max(maxn[s - 1][i % 2],f[i][s - 1]);
					ans = max(ans,f[i][s - 1]);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：Yorg (赞：0)

# 算法
先转化题意。

$n$ 个长为 $m$ 的字符串，假设按顺序找到```n```，```a```，```r```，```e```，```k```这几个字符的数量为 $q$，```n```，```a```，```r```，```e```，```k```出现的总数量为 $p$，求最优的拼接方法，使得 $q - (p - q) = 2q - p \to \max$。

最初的考虑是 $f_{i, 0/1}$ 表示考虑了前 $i$ 个字符串，是否选择第 $i$ 个字符串，然而这样并不好设计。

注意到 $0/1$ 维是无必要的，我们考虑记录 $f_{i, s}$ 表示考虑了前 $i$ 个字符串，其中最后以字母 $s$ 结尾时的最优分差，其中，$s$ 只能取```n```，```a```，```r```，```e```，```k```。

显然的，我们可以预处理出每一个字符串以 $s$ 结尾时最远的可取字符和产生的分差，记为 $end_{i, s}$ 和 $val_{i, s}$，特别的，以```k```结尾相当于从```n```重新开始计算，预处理时间复杂度 $O(\omega^2 nm)$，其中 $\omega = 5$。

考虑转移，

$$
\begin{cases}
f_{i, end_{i, s}} \stackrel{\max}{\longleftarrow} f_{i - 1, s} + val_{i, s} \\
f_{i, s} \stackrel{\max}{\longleftarrow} f_{i - 1, s}
\end{cases}
$$

复杂度 $\mathcal{O}(\omega^2 nm)$，其中 $\omega = 5$。

初始化 $f_{0, s = \rm{'k'}} = 0$，其他都为负无穷。\
答案即为 $\displaystyle\max_{s \in \{\rm{n, a, r, e, k}\}} f_{n, s}$。

# 代码
```cpp
#include <bits/stdc++.h>
const int MAXN = 1e3 + 20;

int T;
int n, m;
std::string str[MAXN];

char mp[5] = {'n', 'a', 'r', 'e', 'k'};
int end[MAXN][5], val[MAXN][5];
/*预处理*/
void init()
{
    /*预处理 end 数组*/
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 5; j++) {
            char NowStart = (j == 4 ? -1 : j);
            for (int k = 1; k <= m; k++) {
                if (str[i][k] == mp[NowStart + 1]) NowStart = ((NowStart + 1) == 4 ? -1 : NowStart + 1);
            }

            end[i][j] = (NowStart == -1 ? 4 : NowStart);
        }

    /*预处理 val 数组*/
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 5; j++) {
            int Sum = 0; // 总出现的次数
            int Use = 0; // 可使用的次数
            char NowStart = (j == 4 ? -1 : j);
            for (int k = 1; k <= m; k++) {
                for (int w = 0; w < 5; w++) if (str[i][k] == mp[w]) Sum++;
                if (str[i][k] == mp[NowStart + 1]) NowStart = ((NowStart + 1) == 4 ? -1 : NowStart + 1), Use += (NowStart == -1 ? 5 : 0);
            }

            val[i][j] = 2 * Use - Sum;
        }
}

int dp[MAXN][5];
/*dp 转移*/
void solve()
{
    memset(dp, 128, sizeof(dp));
    dp[0][4] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            dp[i + 1][j] = std::max(dp[i + 1][j], dp[i][j]);
            dp[i + 1][end[i + 1][j]] = std::max(dp[i + 1][end[i + 1][j]], dp[i][j] + val[i + 1][j]);
        }
    }

    int Ans = 0;
    for (int j = 0; j < 5; j++) {
        Ans = std::max(Ans, dp[n][j]);
    }
    printf("%d\n", Ans);
}

int main()
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= n; i++) {
            std::cin >> str[i];
            str[i] = ' ' + str[i];
        }

        init();
        solve();
    }

    return 0;
}
```

# 总结
分析不必要的维度，考虑简化。

一定要设计特征状态。

预处理可以降低复杂度。

---

## 作者：daitangchen2008 (赞：0)

## 思路  
设 $dp_{i,j}$ 为枚举到第 $i$ 个字符串时需要字母 $j$。  
对于每个 $j$，我们对于此时枚举到的字符串进行遍历，计算出此时可以推到的位置 $x$。在此过程中，记分差为 $y$。  
计算分差时，为了能正确处理得分，我们可以每当遇到一个目标字母时，将分差减一。此外，在一个目标字符串拼接完成时，将分差加十，这样就可以正确处理之前未处理完成时的减一。  
由此则有状态转移方程   
$$dp_{i,x}=\max(dp_{i-1,x},dp_{i-1,j}+y)$$  
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
string s[N];
int dp[N][11];
int get(char ch)
{
	if(ch=='n')
		return 1;
	if(ch=='a')
		return 2;
	if(ch=='r')
		return 3;
	if(ch=='e')
		return 4;
	if(ch=='k')
		return 5;
	return -1;
}
int find(int x)
{
	if(x==5)
		return 1;
	return x+1;
}
signed main()
{
	int T;
	cin>>T;
	while(T--)
	{
		int n,m;
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			cin>>s[i],s[i]=" "+s[i];
		for(int i=2;i<=5;i++)
			dp[0][i]=-1e9;
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=5;j++)
				dp[i][j]=dp[i-1][j];
			dp[i][1]=max((long long)0,dp[i][1]);
			for(int j=1;j<=5;j++)
			{
				int x=j;
				int y=0;
				for(int k=1;k<=m;k++)
				{
					if(get(s[i][k])==-1)
						continue;
					if(x==get(s[i][k]))
					{
						if(x==5)
							y+=10;
						x=find(x);
					}
					y--;
				}
				dp[i][x]=max(dp[i][x],dp[i-1][j]+y);
			}
		}
		int ans=0;
		for(int i=1;i<=5;i++)
			ans=max(ans,dp[n][i]);
		cout<<ans<<endl;
	}
	return 0;
} 
```

---

